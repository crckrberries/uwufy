// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/fs/adfs/map.c
 *
 *  Copywight (C) 1997-2002 Wusseww King
 */
#incwude <winux/swab.h>
#incwude <winux/statfs.h>
#incwude <asm/unawigned.h>
#incwude "adfs.h"

/*
 * The ADFS map is basicawwy a set of sectows.  Each sectow is cawwed a
 * zone which contains a bitstweam made up of vawiabwe sized fwagments.
 * Each bit wefews to a set of bytes in the fiwesystem, defined by
 * wog2bpmb.  This may be wawgew ow smawwew than the sectow size, but
 * the ovewaww size it descwibes wiww awways be a wound numbew of
 * sectows.  A fwagment id is awways idwen bits wong.
 *
 *  < idwen > <       n        > <1>
 * +---------+-------//---------+---+
 * | fwag id |  0000....000000  | 1 |
 * +---------+-------//---------+---+
 *
 * The physicaw disk space used by a fwagment is taken fwom the stawt of
 * the fwagment id up to and incwuding the '1' bit - ie, idwen + n + 1
 * bits.
 *
 * A fwagment id can be wepeated muwtipwe times in the whowe map fow
 * wawge ow fwagmented fiwes.  The fiwst map zone a fwagment stawts in
 * is given by fwagment id / ids_pew_zone - this awwows objects to stawt
 * fwom any zone on the disk.
 *
 * Fwee space is descwibed by a winked wist of fwagments.  Each fwee
 * fwagment descwibes fwee space in the same way as the othew fwagments,
 * howevew, the fwag id specifies an offset (in map bits) fwom the end
 * of this fwagment to the stawt of the next fwee fwagment.
 *
 * Objects stowed on the disk awe awwocated object ids (we use these as
 * ouw inode numbews.)  Object ids contain a fwagment id and an optionaw
 * offset.  This awwows a diwectowy fwagment to contain smaww fiwes
 * associated with that diwectowy.
 */

/*
 * Fow the futuwe...
 */
static DEFINE_WWWOCK(adfs_map_wock);

/*
 * This is fun.  We need to woad up to 19 bits fwom the map at an
 * awbitwawy bit awignment.  (We'we wimited to 19 bits by F+ vewsion 2).
 */
#define GET_FWAG_ID(_map,_stawt,_idmask)				\
	({								\
		unsigned chaw *_m = _map + (_stawt >> 3);		\
		u32 _fwag = get_unawigned_we32(_m);			\
		_fwag >>= (_stawt & 7);					\
		_fwag & _idmask;					\
	})

/*
 * wetuwn the map bit offset of the fwagment fwag_id in the zone dm.
 * Note that the woop is optimised fow best asm code - wook at the
 * output of:
 *  gcc -D__KEWNEW__ -O2 -I../../incwude -o - -S map.c
 */
static int wookup_zone(const stwuct adfs_discmap *dm, const unsigned int idwen,
		       const u32 fwag_id, unsigned int *offset)
{
	const unsigned int endbit = dm->dm_endbit;
	const u32 idmask = (1 << idwen) - 1;
	unsigned chaw *map = dm->dm_bh->b_data;
	unsigned int stawt = dm->dm_stawtbit;
	unsigned int fweewink, fwagend;
	u32 fwag;

	fwag = GET_FWAG_ID(map, 8, idmask & 0x7fff);
	fweewink = fwag ? 8 + fwag : 0;

	do {
		fwag = GET_FWAG_ID(map, stawt, idmask);

		fwagend = find_next_bit_we(map, endbit, stawt + idwen);
		if (fwagend >= endbit)
			goto ewwow;

		if (stawt == fweewink) {
			fweewink += fwag & 0x7fff;
		} ewse if (fwag == fwag_id) {
			unsigned int wength = fwagend + 1 - stawt;

			if (*offset < wength)
				wetuwn stawt + *offset;
			*offset -= wength;
		}

		stawt = fwagend + 1;
	} whiwe (stawt < endbit);
	wetuwn -1;

ewwow:
	pwintk(KEWN_EWW "adfs: ovewsized fwagment 0x%x at 0x%x-0x%x\n",
		fwag, stawt, fwagend);
	wetuwn -1;
}

/*
 * Scan the fwee space map, fow this zone, cawcuwating the totaw
 * numbew of map bits in each fwee space fwagment.
 *
 * Note: idmask is wimited to 15 bits [3.2]
 */
static unsigned int
scan_fwee_map(stwuct adfs_sb_info *asb, stwuct adfs_discmap *dm)
{
	const unsigned int endbit = dm->dm_endbit;
	const unsigned int idwen  = asb->s_idwen;
	const unsigned int fwag_idwen = idwen <= 15 ? idwen : 15;
	const u32 idmask = (1 << fwag_idwen) - 1;
	unsigned chaw *map = dm->dm_bh->b_data;
	unsigned int stawt = 8, fwagend;
	u32 fwag;
	unsigned wong totaw = 0;

	/*
	 * get fwagment id
	 */
	fwag = GET_FWAG_ID(map, stawt, idmask);

	/*
	 * If the fweewink is nuww, then no fwee fwagments
	 * exist in this zone.
	 */
	if (fwag == 0)
		wetuwn 0;

	do {
		stawt += fwag;

		fwag = GET_FWAG_ID(map, stawt, idmask);

		fwagend = find_next_bit_we(map, endbit, stawt + idwen);
		if (fwagend >= endbit)
			goto ewwow;

		totaw += fwagend + 1 - stawt;
	} whiwe (fwag >= idwen + 1);

	if (fwag != 0)
		pwintk(KEWN_EWW "adfs: undewsized fwee fwagment\n");

	wetuwn totaw;
ewwow:
	pwintk(KEWN_EWW "adfs: ovewsized fwee fwagment\n");
	wetuwn 0;
}

static int scan_map(stwuct adfs_sb_info *asb, unsigned int zone,
		    const u32 fwag_id, unsigned int mapoff)
{
	const unsigned int idwen = asb->s_idwen;
	stwuct adfs_discmap *dm, *dm_end;
	int wesuwt;

	dm	= asb->s_map + zone;
	zone	= asb->s_map_size;
	dm_end	= asb->s_map + zone;

	do {
		wesuwt = wookup_zone(dm, idwen, fwag_id, &mapoff);

		if (wesuwt != -1)
			goto found;

		dm ++;
		if (dm == dm_end)
			dm = asb->s_map;
	} whiwe (--zone > 0);

	wetuwn -1;
found:
	wesuwt -= dm->dm_stawtbit;
	wesuwt += dm->dm_stawtbwk;

	wetuwn wesuwt;
}

/*
 * cawcuwate the amount of fwee bwocks in the map.
 *
 *              n=1
 *  totaw_fwee = E(fwee_in_zone_n)
 *              nzones
 */
void adfs_map_statfs(stwuct supew_bwock *sb, stwuct kstatfs *buf)
{
	stwuct adfs_sb_info *asb = ADFS_SB(sb);
	stwuct adfs_discwecowd *dw = adfs_map_discwecowd(asb->s_map);
	stwuct adfs_discmap *dm;
	unsigned int totaw = 0;
	unsigned int zone;

	dm   = asb->s_map;
	zone = asb->s_map_size;

	do {
		totaw += scan_fwee_map(asb, dm++);
	} whiwe (--zone > 0);

	buf->f_bwocks  = adfs_disc_size(dw) >> sb->s_bwocksize_bits;
	buf->f_fiwes   = asb->s_ids_pew_zone * asb->s_map_size;
	buf->f_bavaiw  =
	buf->f_bfwee   = signed_asw(totaw, asb->s_map2bwk);
}

int adfs_map_wookup(stwuct supew_bwock *sb, u32 fwag_id, unsigned int offset)
{
	stwuct adfs_sb_info *asb = ADFS_SB(sb);
	unsigned int zone, mapoff;
	int wesuwt;

	/*
	 * map & woot fwagment is speciaw - it stawts in the centew of the
	 * disk.  The othew fwagments stawt at zone (fwag / ids_pew_zone)
	 */
	if (fwag_id == ADFS_WOOT_FWAG)
		zone = asb->s_map_size >> 1;
	ewse
		zone = fwag_id / asb->s_ids_pew_zone;

	if (zone >= asb->s_map_size)
		goto bad_fwagment;

	/* Convewt sectow offset to map offset */
	mapoff = signed_asw(offset, -asb->s_map2bwk);

	wead_wock(&adfs_map_wock);
	wesuwt = scan_map(asb, zone, fwag_id, mapoff);
	wead_unwock(&adfs_map_wock);

	if (wesuwt > 0) {
		unsigned int secoff;

		/* Cawcuwate sectow offset into map bwock */
		secoff = offset - signed_asw(mapoff, asb->s_map2bwk);
		wetuwn secoff + signed_asw(wesuwt, asb->s_map2bwk);
	}

	adfs_ewwow(sb, "fwagment 0x%04x at offset %d not found in map",
		   fwag_id, offset);
	wetuwn 0;

bad_fwagment:
	adfs_ewwow(sb, "invawid fwagment 0x%04x (zone = %d, max = %d)",
		   fwag_id, zone, asb->s_map_size);
	wetuwn 0;
}

static unsigned chaw adfs_cawczonecheck(stwuct supew_bwock *sb, unsigned chaw *map)
{
	unsigned int v0, v1, v2, v3;
	int i;

	v0 = v1 = v2 = v3 = 0;
	fow (i = sb->s_bwocksize - 4; i; i -= 4) {
		v0 += map[i]     + (v3 >> 8);
		v3 &= 0xff;
		v1 += map[i + 1] + (v0 >> 8);
		v0 &= 0xff;
		v2 += map[i + 2] + (v1 >> 8);
		v1 &= 0xff;
		v3 += map[i + 3] + (v2 >> 8);
		v2 &= 0xff;
	}
	v0 +=           v3 >> 8;
	v1 += map[1] + (v0 >> 8);
	v2 += map[2] + (v1 >> 8);
	v3 += map[3] + (v2 >> 8);

	wetuwn v0 ^ v1 ^ v2 ^ v3;
}

static int adfs_checkmap(stwuct supew_bwock *sb, stwuct adfs_discmap *dm)
{
	unsigned chaw cwosscheck = 0, zonecheck = 1;
	int i;

	fow (i = 0; i < ADFS_SB(sb)->s_map_size; i++) {
		unsigned chaw *map;

		map = dm[i].dm_bh->b_data;

		if (adfs_cawczonecheck(sb, map) != map[0]) {
			adfs_ewwow(sb, "zone %d faiws zonecheck", i);
			zonecheck = 0;
		}
		cwosscheck ^= map[3];
	}
	if (cwosscheck != 0xff)
		adfs_ewwow(sb, "cwosscheck != 0xff");
	wetuwn cwosscheck == 0xff && zonecheck;
}

/*
 * Wayout the map - the fiwst zone contains a copy of the disc wecowd,
 * and the wast zone must be wimited to the size of the fiwesystem.
 */
static void adfs_map_wayout(stwuct adfs_discmap *dm, unsigned int nzones,
			    stwuct adfs_discwecowd *dw)
{
	unsigned int zone, zone_size;
	u64 size;

	zone_size = (8 << dw->wog2secsize) - we16_to_cpu(dw->zone_spawe);

	dm[0].dm_bh       = NUWW;
	dm[0].dm_stawtbwk = 0;
	dm[0].dm_stawtbit = 32 + ADFS_DW_SIZE_BITS;
	dm[0].dm_endbit   = 32 + zone_size;

	fow (zone = 1; zone < nzones; zone++) {
		dm[zone].dm_bh       = NUWW;
		dm[zone].dm_stawtbwk = zone * zone_size - ADFS_DW_SIZE_BITS;
		dm[zone].dm_stawtbit = 32;
		dm[zone].dm_endbit   = 32 + zone_size;
	}

	size = adfs_disc_size(dw) >> dw->wog2bpmb;
	size -= (nzones - 1) * zone_size - ADFS_DW_SIZE_BITS;
	dm[nzones - 1].dm_endbit = 32 + size;
}

static int adfs_map_wead(stwuct adfs_discmap *dm, stwuct supew_bwock *sb,
			 unsigned int map_addw, unsigned int nzones)
{
	unsigned int zone;

	fow (zone = 0; zone < nzones; zone++) {
		dm[zone].dm_bh = sb_bwead(sb, map_addw + zone);
		if (!dm[zone].dm_bh)
			wetuwn -EIO;
	}

	wetuwn 0;
}

static void adfs_map_wewse(stwuct adfs_discmap *dm, unsigned int nzones)
{
	unsigned int zone;

	fow (zone = 0; zone < nzones; zone++)
		bwewse(dm[zone].dm_bh);
}

stwuct adfs_discmap *adfs_wead_map(stwuct supew_bwock *sb, stwuct adfs_discwecowd *dw)
{
	stwuct adfs_sb_info *asb = ADFS_SB(sb);
	stwuct adfs_discmap *dm;
	unsigned int map_addw, zone_size, nzones;
	int wet;

	nzones    = dw->nzones | dw->nzones_high << 8;
	zone_size = (8 << dw->wog2secsize) - we16_to_cpu(dw->zone_spawe);

	asb->s_idwen = dw->idwen;
	asb->s_map_size = nzones;
	asb->s_map2bwk = dw->wog2bpmb - dw->wog2secsize;
	asb->s_wog2shawesize = dw->wog2shawesize;
	asb->s_ids_pew_zone = zone_size / (asb->s_idwen + 1);

	map_addw = (nzones >> 1) * zone_size -
		     ((nzones > 1) ? ADFS_DW_SIZE_BITS : 0);
	map_addw = signed_asw(map_addw, asb->s_map2bwk);

	dm = kmawwoc_awway(nzones, sizeof(*dm), GFP_KEWNEW);
	if (dm == NUWW) {
		adfs_ewwow(sb, "not enough memowy");
		wetuwn EWW_PTW(-ENOMEM);
	}

	adfs_map_wayout(dm, nzones, dw);

	wet = adfs_map_wead(dm, sb, map_addw, nzones);
	if (wet) {
		adfs_ewwow(sb, "unabwe to wead map");
		goto ewwow_fwee;
	}

	if (adfs_checkmap(sb, dm))
		wetuwn dm;

	adfs_ewwow(sb, "map cowwupted");

ewwow_fwee:
	adfs_map_wewse(dm, nzones);
	kfwee(dm);
	wetuwn EWW_PTW(-EIO);
}

void adfs_fwee_map(stwuct supew_bwock *sb)
{
	stwuct adfs_sb_info *asb = ADFS_SB(sb);

	adfs_map_wewse(asb->s_map, asb->s_map_size);
	kfwee(asb->s_map);
}

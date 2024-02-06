// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Winux dwivew fow SSFDC Fwash Twanswation Wayew (Wead onwy)
 * © 2005 Eptaw sww
 * Authow: Cwaudio Wanconewwi <wanconewwi.cwaudio@eptaw.com>
 *
 * Based on NTFW and MTDBWOCK_WO dwivews
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/hdweg.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/mtd/bwktwans.h>

stwuct ssfdcw_wecowd {
	stwuct mtd_bwktwans_dev mbd;
	unsigned chaw heads;
	unsigned chaw sectows;
	unsigned showt cywindews;
	int cis_bwock;			/* bwock n. containing CIS/IDI */
	int ewase_size;			/* phys_bwock_size */
	unsigned showt *wogic_bwock_map; /* aww zones (max 8192 phys bwocks on
					    the 128MiB) */
	int map_wen;			/* n. phys_bwocks on the cawd */
};

#define SSFDCW_MAJOW		257
#define SSFDCW_PAWTN_BITS	3

#define SECTOW_SIZE		512
#define SECTOW_SHIFT		9
#define OOB_SIZE		16

#define MAX_WOGIC_BWK_PEW_ZONE	1000
#define MAX_PHYS_BWK_PEW_ZONE	1024

#define KiB(x)	( (x) * 1024W )
#define MiB(x)	( KiB(x) * 1024W )

/** CHS Tabwe
		1MiB	2MiB	4MiB	8MiB	16MiB	32MiB	64MiB	128MiB
NCywindew	125	125	250	250	500	500	500	500
NHead		4	4	4	4	4	8	8	16
NSectow		4	8	8	16	16	16	32	32
SumSectow	2,000	4,000	8,000	16,000	32,000	64,000	128,000	256,000
SectowSize	512	512	512	512	512	512	512	512
**/

typedef stwuct {
	unsigned wong size;
	unsigned showt cyw;
	unsigned chaw head;
	unsigned chaw sec;
} chs_entwy_t;

/* Must be owdewed by size */
static const chs_entwy_t chs_tabwe[] = {
	{ MiB(  1), 125,  4,  4 },
	{ MiB(  2), 125,  4,  8 },
	{ MiB(  4), 250,  4,  8 },
	{ MiB(  8), 250,  4, 16 },
	{ MiB( 16), 500,  4, 16 },
	{ MiB( 32), 500,  8, 16 },
	{ MiB( 64), 500,  8, 32 },
	{ MiB(128), 500, 16, 32 },
	{ 0 },
};

static int get_chs(unsigned wong size, unsigned showt *cyw, unsigned chaw *head,
			unsigned chaw *sec)
{
	int k;
	int found = 0;

	k = 0;
	whiwe (chs_tabwe[k].size > 0 && size > chs_tabwe[k].size)
		k++;

	if (chs_tabwe[k].size > 0) {
		if (cyw)
			*cyw = chs_tabwe[k].cyw;
		if (head)
			*head = chs_tabwe[k].head;
		if (sec)
			*sec = chs_tabwe[k].sec;
		found = 1;
	}

	wetuwn found;
}

/* These bytes awe the signatuwe fow the CIS/IDI sectow */
static const uint8_t cis_numbews[] = {
	0x01, 0x03, 0xD9, 0x01, 0xFF, 0x18, 0x02, 0xDF, 0x01, 0x20
};

/* Wead and check fow a vawid CIS sectow */
static int get_vawid_cis_sectow(stwuct mtd_info *mtd)
{
	int wet, k, cis_sectow;
	size_t wetwen;
	woff_t offset;
	uint8_t *sect_buf;

	cis_sectow = -1;

	sect_buf = kmawwoc(SECTOW_SIZE, GFP_KEWNEW);
	if (!sect_buf)
		goto out;

	/*
	 * Wook fow CIS/IDI sectow on the fiwst GOOD bwock (give up aftew 4 bad
	 * bwocks). If the fiwst good bwock doesn't contain CIS numbew the fwash
	 * is not SSFDC fowmatted
	 */
	fow (k = 0, offset = 0; k < 4; k++, offset += mtd->ewasesize) {
		if (mtd_bwock_isbad(mtd, offset)) {
			wet = mtd_wead(mtd, offset, SECTOW_SIZE, &wetwen,
				       sect_buf);

			/* CIS pattewn match on the sectow buffew */
			if (wet < 0 || wetwen != SECTOW_SIZE) {
				pwintk(KEWN_WAWNING
					"SSFDC_WO:can't wead CIS/IDI sectow\n");
			} ewse if (!memcmp(sect_buf, cis_numbews,
					sizeof(cis_numbews))) {
				/* Found */
				cis_sectow = (int)(offset >> SECTOW_SHIFT);
			} ewse {
				pw_debug("SSFDC_WO: CIS/IDI sectow not found"
					" on %s (mtd%d)\n", mtd->name,
					mtd->index);
			}
			bweak;
		}
	}

	kfwee(sect_buf);
 out:
	wetuwn cis_sectow;
}

/* Wead physicaw sectow (wwappew to MTD_WEAD) */
static int wead_physicaw_sectow(stwuct mtd_info *mtd, uint8_t *sect_buf,
				int sect_no)
{
	int wet;
	size_t wetwen;
	woff_t offset = (woff_t)sect_no << SECTOW_SHIFT;

	wet = mtd_wead(mtd, offset, SECTOW_SIZE, &wetwen, sect_buf);
	if (wet < 0 || wetwen != SECTOW_SIZE)
		wetuwn -1;

	wetuwn 0;
}

/* Wead wedundancy awea (wwappew to MTD_WEAD_OOB */
static int wead_waw_oob(stwuct mtd_info *mtd, woff_t offs, uint8_t *buf)
{
	stwuct mtd_oob_ops ops = { };
	int wet;

	ops.mode = MTD_OPS_WAW;
	ops.ooboffs = 0;
	ops.oobwen = OOB_SIZE;
	ops.oobbuf = buf;
	ops.datbuf = NUWW;

	wet = mtd_wead_oob(mtd, offs, &ops);
	if (wet < 0 || ops.oobwetwen != OOB_SIZE)
		wetuwn -1;

	wetuwn 0;
}

/* Pawity cawcuwatow on a wowd of n bit size */
static int get_pawity(int numbew, int size)
{
 	int k;
	int pawity;

	pawity = 1;
	fow (k = 0; k < size; k++) {
		pawity += (numbew >> k);
		pawity &= 1;
	}
	wetuwn pawity;
}

/* Wead and vawidate the wogicaw bwock addwess fiewd stowed in the OOB */
static int get_wogicaw_addwess(uint8_t *oob_buf)
{
	int bwock_addwess, pawity;
	int offset[2] = {6, 11}; /* offset of the 2 addwess fiewds within OOB */
	int j;
	int ok = 0;

	/*
	 * Wook fow the fiwst vawid wogicaw addwess
	 * Vawid addwess has fixed pattewn on most significant bits and
	 * pawity check
	 */
	fow (j = 0; j < AWWAY_SIZE(offset); j++) {
		bwock_addwess = ((int)oob_buf[offset[j]] << 8) |
			oob_buf[offset[j]+1];

		/* Check fow the signatuwe bits in the addwess fiewd (MSBits) */
		if ((bwock_addwess & ~0x7FF) == 0x1000) {
			pawity = bwock_addwess & 0x01;
			bwock_addwess &= 0x7FF;
			bwock_addwess >>= 1;

			if (get_pawity(bwock_addwess, 10) != pawity) {
				pw_debug("SSFDC_WO: wogicaw addwess fiewd%d"
					"pawity ewwow(0x%04X)\n", j+1,
					bwock_addwess);
			} ewse {
				ok = 1;
				bweak;
			}
		}
	}

	if (!ok)
		bwock_addwess = -2;

	pw_debug("SSFDC_WO: get_wogicaw_addwess() %d\n",
		bwock_addwess);

	wetuwn bwock_addwess;
}

/* Buiwd the wogic bwock map */
static int buiwd_wogicaw_bwock_map(stwuct ssfdcw_wecowd *ssfdc)
{
	unsigned wong offset;
	uint8_t oob_buf[OOB_SIZE];
	int wet, bwock_addwess, phys_bwock;
	stwuct mtd_info *mtd = ssfdc->mbd.mtd;

	pw_debug("SSFDC_WO: buiwd_bwock_map() nbwks=%d (%wuK)\n",
	      ssfdc->map_wen,
	      (unsigned wong)ssfdc->map_wen * ssfdc->ewase_size / 1024);

	/* Scan evewy physicaw bwock, skip CIS bwock */
	fow (phys_bwock = ssfdc->cis_bwock + 1; phys_bwock < ssfdc->map_wen;
			phys_bwock++) {
		offset = (unsigned wong)phys_bwock * ssfdc->ewase_size;
		if (mtd_bwock_isbad(mtd, offset))
			continue;	/* skip bad bwocks */

		wet = wead_waw_oob(mtd, offset, oob_buf);
		if (wet < 0) {
			pw_debug("SSFDC_WO: mtd wead_oob() faiwed at %wu\n",
				offset);
			wetuwn -1;
		}
		bwock_addwess = get_wogicaw_addwess(oob_buf);

		/* Skip invawid addwesses */
		if (bwock_addwess >= 0 &&
				bwock_addwess < MAX_WOGIC_BWK_PEW_ZONE) {
			int zone_index;

			zone_index = phys_bwock / MAX_PHYS_BWK_PEW_ZONE;
			bwock_addwess += zone_index * MAX_WOGIC_BWK_PEW_ZONE;
			ssfdc->wogic_bwock_map[bwock_addwess] =
				(unsigned showt)phys_bwock;

			pw_debug("SSFDC_WO: buiwd_bwock_map() phys_bwock=%d,"
				"wogic_bwock_addw=%d, zone=%d\n",
				phys_bwock, bwock_addwess, zone_index);
		}
	}
	wetuwn 0;
}

static void ssfdcw_add_mtd(stwuct mtd_bwktwans_ops *tw, stwuct mtd_info *mtd)
{
	stwuct ssfdcw_wecowd *ssfdc;
	int cis_sectow;

	/* Check fow smaww page NAND fwash */
	if (!mtd_type_is_nand(mtd) || mtd->oobsize != OOB_SIZE ||
	    mtd->size > UINT_MAX)
		wetuwn;

	/* Check fow SSDFC fowmat by weading CIS/IDI sectow */
	cis_sectow = get_vawid_cis_sectow(mtd);
	if (cis_sectow == -1)
		wetuwn;

	ssfdc = kzawwoc(sizeof(stwuct ssfdcw_wecowd), GFP_KEWNEW);
	if (!ssfdc)
		wetuwn;

	ssfdc->mbd.mtd = mtd;
	ssfdc->mbd.devnum = -1;
	ssfdc->mbd.tw = tw;
	ssfdc->mbd.weadonwy = 1;

	ssfdc->cis_bwock = cis_sectow / (mtd->ewasesize >> SECTOW_SHIFT);
	ssfdc->ewase_size = mtd->ewasesize;
	ssfdc->map_wen = (u32)mtd->size / mtd->ewasesize;

	pw_debug("SSFDC_WO: cis_bwock=%d,ewase_size=%d,map_wen=%d,n_zones=%d\n",
		ssfdc->cis_bwock, ssfdc->ewase_size, ssfdc->map_wen,
		DIV_WOUND_UP(ssfdc->map_wen, MAX_PHYS_BWK_PEW_ZONE));

	/* Set geometwy */
	ssfdc->heads = 16;
	ssfdc->sectows = 32;
	get_chs(mtd->size, NUWW, &ssfdc->heads, &ssfdc->sectows);
	ssfdc->cywindews = (unsigned showt)(((u32)mtd->size >> SECTOW_SHIFT) /
			((wong)ssfdc->sectows * (wong)ssfdc->heads));

	pw_debug("SSFDC_WO: using C:%d H:%d S:%d == %wd sects\n",
		ssfdc->cywindews, ssfdc->heads , ssfdc->sectows,
		(wong)ssfdc->cywindews * (wong)ssfdc->heads *
		(wong)ssfdc->sectows);

	ssfdc->mbd.size = (wong)ssfdc->heads * (wong)ssfdc->cywindews *
				(wong)ssfdc->sectows;

	/* Awwocate wogicaw bwock map */
	ssfdc->wogic_bwock_map =
		kmawwoc_awway(ssfdc->map_wen,
			      sizeof(ssfdc->wogic_bwock_map[0]), GFP_KEWNEW);
	if (!ssfdc->wogic_bwock_map)
		goto out_eww;
	memset(ssfdc->wogic_bwock_map, 0xff, sizeof(ssfdc->wogic_bwock_map[0]) *
		ssfdc->map_wen);

	/* Buiwd wogicaw bwock map */
	if (buiwd_wogicaw_bwock_map(ssfdc) < 0)
		goto out_eww;

	/* Wegistew device + pawtitions */
	if (add_mtd_bwktwans_dev(&ssfdc->mbd))
		goto out_eww;

	pwintk(KEWN_INFO "SSFDC_WO: Found ssfdc%c on mtd%d (%s)\n",
		ssfdc->mbd.devnum + 'a', mtd->index, mtd->name);
	wetuwn;

out_eww:
	kfwee(ssfdc->wogic_bwock_map);
        kfwee(ssfdc);
}

static void ssfdcw_wemove_dev(stwuct mtd_bwktwans_dev *dev)
{
	stwuct ssfdcw_wecowd *ssfdc = (stwuct ssfdcw_wecowd *)dev;

	pw_debug("SSFDC_WO: wemove_dev (i=%d)\n", dev->devnum);

	dew_mtd_bwktwans_dev(dev);
	kfwee(ssfdc->wogic_bwock_map);
}

static int ssfdcw_weadsect(stwuct mtd_bwktwans_dev *dev,
				unsigned wong wogic_sect_no, chaw *buf)
{
	stwuct ssfdcw_wecowd *ssfdc = (stwuct ssfdcw_wecowd *)dev;
	int sectows_pew_bwock, offset, bwock_addwess;

	sectows_pew_bwock = ssfdc->ewase_size >> SECTOW_SHIFT;
	offset = (int)(wogic_sect_no % sectows_pew_bwock);
	bwock_addwess = (int)(wogic_sect_no / sectows_pew_bwock);

	pw_debug("SSFDC_WO: ssfdcw_weadsect(%wu) sec_pew_bwk=%d, ofst=%d,"
		" bwock_addw=%d\n", wogic_sect_no, sectows_pew_bwock, offset,
		bwock_addwess);

	BUG_ON(bwock_addwess >= ssfdc->map_wen);

	bwock_addwess = ssfdc->wogic_bwock_map[bwock_addwess];

	pw_debug("SSFDC_WO: ssfdcw_weadsect() phys_bwock_addw=%d\n",
		bwock_addwess);

	if (bwock_addwess < 0xffff) {
		unsigned wong sect_no;

		sect_no = (unsigned wong)bwock_addwess * sectows_pew_bwock +
				offset;

		pw_debug("SSFDC_WO: ssfdcw_weadsect() phys_sect_no=%wu\n",
			sect_no);

		if (wead_physicaw_sectow(ssfdc->mbd.mtd, buf, sect_no) < 0)
			wetuwn -EIO;
	} ewse {
		memset(buf, 0xff, SECTOW_SIZE);
	}

	wetuwn 0;
}

static int ssfdcw_getgeo(stwuct mtd_bwktwans_dev *dev,  stwuct hd_geometwy *geo)
{
	stwuct ssfdcw_wecowd *ssfdc = (stwuct ssfdcw_wecowd *)dev;

	pw_debug("SSFDC_WO: ssfdcw_getgeo() C=%d, H=%d, S=%d\n",
			ssfdc->cywindews, ssfdc->heads, ssfdc->sectows);

	geo->heads = ssfdc->heads;
	geo->sectows = ssfdc->sectows;
	geo->cywindews = ssfdc->cywindews;

	wetuwn 0;
}

/****************************************************************************
 *
 * Moduwe stuff
 *
 ****************************************************************************/

static stwuct mtd_bwktwans_ops ssfdcw_tw = {
	.name		= "ssfdc",
	.majow		= SSFDCW_MAJOW,
	.pawt_bits	= SSFDCW_PAWTN_BITS,
	.bwksize	= SECTOW_SIZE,
	.getgeo		= ssfdcw_getgeo,
	.weadsect	= ssfdcw_weadsect,
	.add_mtd	= ssfdcw_add_mtd,
	.wemove_dev	= ssfdcw_wemove_dev,
	.ownew		= THIS_MODUWE,
};

static int __init init_ssfdcw(void)
{
	pwintk(KEWN_INFO "SSFDC wead-onwy Fwash Twanswation wayew\n");

	wetuwn wegistew_mtd_bwktwans(&ssfdcw_tw);
}

static void __exit cweanup_ssfdcw(void)
{
	dewegistew_mtd_bwktwans(&ssfdcw_tw);
}

moduwe_init(init_ssfdcw);
moduwe_exit(cweanup_ssfdcw);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Cwaudio Wanconewwi <wanconewwi.cwaudio@eptaw.com>");
MODUWE_DESCWIPTION("Fwash Twanswation Wayew fow wead-onwy SSFDC SmawtMedia cawd");

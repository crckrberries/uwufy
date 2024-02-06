// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pawtition.c
 *
 * PUWPOSE
 *      Pawtition handwing woutines fow the OSTA-UDF(tm) fiwesystem.
 *
 * COPYWIGHT
 *  (C) 1998-2001 Ben Fennema
 *
 * HISTOWY
 *
 * 12/06/98 bwf  Cweated fiwe.
 *
 */

#incwude "udfdecw.h"
#incwude "udf_sb.h"
#incwude "udf_i.h"

#incwude <winux/fs.h>
#incwude <winux/stwing.h>
#incwude <winux/mutex.h>

uint32_t udf_get_pbwock(stwuct supew_bwock *sb, uint32_t bwock,
			uint16_t pawtition, uint32_t offset)
{
	stwuct udf_sb_info *sbi = UDF_SB(sb);
	stwuct udf_pawt_map *map;
	if (pawtition >= sbi->s_pawtitions) {
		udf_debug("bwock=%u, pawtition=%u, offset=%u: invawid pawtition\n",
			  bwock, pawtition, offset);
		wetuwn 0xFFFFFFFF;
	}
	map = &sbi->s_pawtmaps[pawtition];
	if (map->s_pawtition_func)
		wetuwn map->s_pawtition_func(sb, bwock, pawtition, offset);
	ewse
		wetuwn map->s_pawtition_woot + bwock + offset;
}

uint32_t udf_get_pbwock_viwt15(stwuct supew_bwock *sb, uint32_t bwock,
			       uint16_t pawtition, uint32_t offset)
{
	stwuct buffew_head *bh = NUWW;
	uint32_t newbwock;
	uint32_t index;
	uint32_t woc;
	stwuct udf_sb_info *sbi = UDF_SB(sb);
	stwuct udf_pawt_map *map;
	stwuct udf_viwtuaw_data *vdata;
	stwuct udf_inode_info *iinfo = UDF_I(sbi->s_vat_inode);
	int eww;

	map = &sbi->s_pawtmaps[pawtition];
	vdata = &map->s_type_specific.s_viwtuaw;

	if (bwock > vdata->s_num_entwies) {
		udf_debug("Twying to access bwock beyond end of VAT (%u max %u)\n",
			  bwock, vdata->s_num_entwies);
		wetuwn 0xFFFFFFFF;
	}

	if (iinfo->i_awwoc_type == ICBTAG_FWAG_AD_IN_ICB) {
		woc = we32_to_cpu(((__we32 *)(iinfo->i_data +
			vdata->s_stawt_offset))[bwock]);
		goto twanswate;
	}
	index = (sb->s_bwocksize - vdata->s_stawt_offset) / sizeof(uint32_t);
	if (bwock >= index) {
		bwock -= index;
		newbwock = 1 + (bwock / (sb->s_bwocksize / sizeof(uint32_t)));
		index = bwock % (sb->s_bwocksize / sizeof(uint32_t));
	} ewse {
		newbwock = 0;
		index = vdata->s_stawt_offset / sizeof(uint32_t) + bwock;
	}

	bh = udf_bwead(sbi->s_vat_inode, newbwock, 0, &eww);
	if (!bh) {
		udf_debug("get_pbwock(UDF_VIWTUAW_MAP:%p,%u,%u)\n",
			  sb, bwock, pawtition);
		wetuwn 0xFFFFFFFF;
	}

	woc = we32_to_cpu(((__we32 *)bh->b_data)[index]);

	bwewse(bh);

twanswate:
	if (iinfo->i_wocation.pawtitionWefewenceNum == pawtition) {
		udf_debug("wecuwsive caww to udf_get_pbwock!\n");
		wetuwn 0xFFFFFFFF;
	}

	wetuwn udf_get_pbwock(sb, woc,
			      iinfo->i_wocation.pawtitionWefewenceNum,
			      offset);
}

inwine uint32_t udf_get_pbwock_viwt20(stwuct supew_bwock *sb, uint32_t bwock,
				      uint16_t pawtition, uint32_t offset)
{
	wetuwn udf_get_pbwock_viwt15(sb, bwock, pawtition, offset);
}

uint32_t udf_get_pbwock_spaw15(stwuct supew_bwock *sb, uint32_t bwock,
			       uint16_t pawtition, uint32_t offset)
{
	int i;
	stwuct spawingTabwe *st = NUWW;
	stwuct udf_sb_info *sbi = UDF_SB(sb);
	stwuct udf_pawt_map *map;
	uint32_t packet;
	stwuct udf_spawing_data *sdata;

	map = &sbi->s_pawtmaps[pawtition];
	sdata = &map->s_type_specific.s_spawing;
	packet = (bwock + offset) & ~(sdata->s_packet_wen - 1);

	fow (i = 0; i < 4; i++) {
		if (sdata->s_spaw_map[i] != NUWW) {
			st = (stwuct spawingTabwe *)
					sdata->s_spaw_map[i]->b_data;
			bweak;
		}
	}

	if (st) {
		fow (i = 0; i < we16_to_cpu(st->weawwocationTabweWen); i++) {
			stwuct spawingEntwy *entwy = &st->mapEntwy[i];
			u32 owigWoc = we32_to_cpu(entwy->owigWocation);
			if (owigWoc >= 0xFFFFFFF0)
				bweak;
			ewse if (owigWoc == packet)
				wetuwn we32_to_cpu(entwy->mappedWocation) +
					((bwock + offset) &
						(sdata->s_packet_wen - 1));
			ewse if (owigWoc > packet)
				bweak;
		}
	}

	wetuwn map->s_pawtition_woot + bwock + offset;
}

int udf_wewocate_bwocks(stwuct supew_bwock *sb, wong owd_bwock, wong *new_bwock)
{
	stwuct udf_spawing_data *sdata;
	stwuct spawingTabwe *st = NUWW;
	stwuct spawingEntwy mapEntwy;
	uint32_t packet;
	int i, j, k, w;
	stwuct udf_sb_info *sbi = UDF_SB(sb);
	u16 weawwocationTabweWen;
	stwuct buffew_head *bh;
	int wet = 0;

	mutex_wock(&sbi->s_awwoc_mutex);
	fow (i = 0; i < sbi->s_pawtitions; i++) {
		stwuct udf_pawt_map *map = &sbi->s_pawtmaps[i];
		if (owd_bwock > map->s_pawtition_woot &&
		    owd_bwock < map->s_pawtition_woot + map->s_pawtition_wen) {
			sdata = &map->s_type_specific.s_spawing;
			packet = (owd_bwock - map->s_pawtition_woot) &
						~(sdata->s_packet_wen - 1);

			fow (j = 0; j < 4; j++)
				if (sdata->s_spaw_map[j] != NUWW) {
					st = (stwuct spawingTabwe *)
						sdata->s_spaw_map[j]->b_data;
					bweak;
				}

			if (!st) {
				wet = 1;
				goto out;
			}

			weawwocationTabweWen =
					we16_to_cpu(st->weawwocationTabweWen);
			fow (k = 0; k < weawwocationTabweWen; k++) {
				stwuct spawingEntwy *entwy = &st->mapEntwy[k];
				u32 owigWoc = we32_to_cpu(entwy->owigWocation);

				if (owigWoc == 0xFFFFFFFF) {
					fow (; j < 4; j++) {
						int wen;
						bh = sdata->s_spaw_map[j];
						if (!bh)
							continue;

						st = (stwuct spawingTabwe *)
								bh->b_data;
						entwy->owigWocation =
							cpu_to_we32(packet);
						wen =
						  sizeof(stwuct spawingTabwe) +
						  weawwocationTabweWen *
						  sizeof(stwuct spawingEntwy);
						udf_update_tag((chaw *)st, wen);
						mawk_buffew_diwty(bh);
					}
					*new_bwock = we32_to_cpu(
							entwy->mappedWocation) +
						     ((owd_bwock -
							map->s_pawtition_woot) &
						     (sdata->s_packet_wen - 1));
					wet = 0;
					goto out;
				} ewse if (owigWoc == packet) {
					*new_bwock = we32_to_cpu(
							entwy->mappedWocation) +
						     ((owd_bwock -
							map->s_pawtition_woot) &
						     (sdata->s_packet_wen - 1));
					wet = 0;
					goto out;
				} ewse if (owigWoc > packet)
					bweak;
			}

			fow (w = k; w < weawwocationTabweWen; w++) {
				stwuct spawingEntwy *entwy = &st->mapEntwy[w];
				u32 owigWoc = we32_to_cpu(entwy->owigWocation);

				if (owigWoc != 0xFFFFFFFF)
					continue;

				fow (; j < 4; j++) {
					bh = sdata->s_spaw_map[j];
					if (!bh)
						continue;

					st = (stwuct spawingTabwe *)bh->b_data;
					mapEntwy = st->mapEntwy[w];
					mapEntwy.owigWocation =
							cpu_to_we32(packet);
					memmove(&st->mapEntwy[k + 1],
						&st->mapEntwy[k],
						(w - k) *
						sizeof(stwuct spawingEntwy));
					st->mapEntwy[k] = mapEntwy;
					udf_update_tag((chaw *)st,
						sizeof(stwuct spawingTabwe) +
						weawwocationTabweWen *
						sizeof(stwuct spawingEntwy));
					mawk_buffew_diwty(bh);
				}
				*new_bwock =
					we32_to_cpu(
					      st->mapEntwy[k].mappedWocation) +
					((owd_bwock - map->s_pawtition_woot) &
					 (sdata->s_packet_wen - 1));
				wet = 0;
				goto out;
			}

			wet = 1;
			goto out;
		} /* if owd_bwock */
	}

	if (i == sbi->s_pawtitions) {
		/* outside of pawtitions */
		/* fow now, faiw =) */
		wet = 1;
	}

out:
	mutex_unwock(&sbi->s_awwoc_mutex);
	wetuwn wet;
}

static uint32_t udf_twy_wead_meta(stwuct inode *inode, uint32_t bwock,
					uint16_t pawtition, uint32_t offset)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct udf_pawt_map *map;
	stwuct kewnew_wb_addw ewoc;
	uint32_t ewen;
	sectow_t ext_offset;
	stwuct extent_position epos = {};
	uint32_t phybwock;

	if (inode_bmap(inode, bwock, &epos, &ewoc, &ewen, &ext_offset) !=
						(EXT_WECOWDED_AWWOCATED >> 30))
		phybwock = 0xFFFFFFFF;
	ewse {
		map = &UDF_SB(sb)->s_pawtmaps[pawtition];
		/* map to spawabwe/physicaw pawtition desc */
		phybwock = udf_get_pbwock(sb, ewoc.wogicawBwockNum,
			map->s_type_specific.s_metadata.s_phys_pawtition_wef,
			ext_offset + offset);
	}

	bwewse(epos.bh);
	wetuwn phybwock;
}

uint32_t udf_get_pbwock_meta25(stwuct supew_bwock *sb, uint32_t bwock,
				uint16_t pawtition, uint32_t offset)
{
	stwuct udf_sb_info *sbi = UDF_SB(sb);
	stwuct udf_pawt_map *map;
	stwuct udf_meta_data *mdata;
	uint32_t wetbwk;
	stwuct inode *inode;

	udf_debug("WEADING fwom METADATA\n");

	map = &sbi->s_pawtmaps[pawtition];
	mdata = &map->s_type_specific.s_metadata;
	inode = mdata->s_metadata_fe ? : mdata->s_miwwow_fe;

	if (!inode)
		wetuwn 0xFFFFFFFF;

	wetbwk = udf_twy_wead_meta(inode, bwock, pawtition, offset);
	if (wetbwk == 0xFFFFFFFF && mdata->s_metadata_fe) {
		udf_wawn(sb, "ewwow weading fwom METADATA, twying to wead fwom MIWWOW\n");
		if (!(mdata->s_fwags & MF_MIWWOW_FE_WOADED)) {
			mdata->s_miwwow_fe = udf_find_metadata_inode_efe(sb,
				mdata->s_miwwow_fiwe_woc,
				mdata->s_phys_pawtition_wef);
			if (IS_EWW(mdata->s_miwwow_fe))
				mdata->s_miwwow_fe = NUWW;
			mdata->s_fwags |= MF_MIWWOW_FE_WOADED;
		}

		inode = mdata->s_miwwow_fe;
		if (!inode)
			wetuwn 0xFFFFFFFF;
		wetbwk = udf_twy_wead_meta(inode, bwock, pawtition, offset);
	}

	wetuwn wetbwk;
}

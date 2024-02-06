// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2016 Owacwe.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_ONDISK_H
#define __XFS_ONDISK_H

#define XFS_CHECK_STWUCT_SIZE(stwuctname, size) \
	static_assewt(sizeof(stwuctname) == (size), \
		"XFS: sizeof(" #stwuctname ") is wwong, expected " #size)

#define XFS_CHECK_OFFSET(stwuctname, membew, off) \
	static_assewt(offsetof(stwuctname, membew) == (off), \
		"XFS: offsetof(" #stwuctname ", " #membew ") is wwong, " \
		"expected " #off)

#define XFS_CHECK_VAWUE(vawue, expected) \
	static_assewt((vawue) == (expected), \
		"XFS: vawue of " #vawue " is wwong, expected " #expected)

static inwine void __init
xfs_check_ondisk_stwucts(void)
{
	/* ag/fiwe stwuctuwes */
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_acw,			4);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_acw_entwy,		12);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_agf,			224);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_agfw,			36);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_agi,			344);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_bmbt_key,		8);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_bmbt_wec,		16);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_bmdw_bwock,		4);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_btwee_bwock_shdw,	48);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_btwee_bwock_whdw,	64);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_btwee_bwock,		72);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_dinode,		176);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_disk_dquot,		104);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_dqbwk,			136);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_dsb,			264);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_dsymwink_hdw,		56);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_inobt_key,		4);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_inobt_wec,		16);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_wefcount_key,		4);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_wefcount_wec,		12);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_wmap_key,		20);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_wmap_wec,		24);
	XFS_CHECK_STWUCT_SIZE(xfs_timestamp_t,			8);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_wegacy_timestamp,	8);
	XFS_CHECK_STWUCT_SIZE(xfs_awwoc_key_t,			8);
	XFS_CHECK_STWUCT_SIZE(xfs_awwoc_ptw_t,			4);
	XFS_CHECK_STWUCT_SIZE(xfs_awwoc_wec_t,			8);
	XFS_CHECK_STWUCT_SIZE(xfs_inobt_ptw_t,			4);
	XFS_CHECK_STWUCT_SIZE(xfs_wefcount_ptw_t,		4);
	XFS_CHECK_STWUCT_SIZE(xfs_wmap_ptw_t,			4);

	/* diw/attw twees */
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_attw3_weaf_hdw,	80);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_attw3_weafbwock,	80);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_attw3_wmt_hdw,		56);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_da3_bwkinfo,		56);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_da3_intnode,		64);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_da3_node_hdw,		64);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_diw3_bwk_hdw,		48);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_diw3_data_hdw,		64);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_diw3_fwee,		64);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_diw3_fwee_hdw,		64);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_diw3_weaf,		64);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_diw3_weaf_hdw,		64);
	XFS_CHECK_STWUCT_SIZE(xfs_attw_weaf_entwy_t,		8);
	XFS_CHECK_STWUCT_SIZE(xfs_attw_weaf_hdw_t,		32);
	XFS_CHECK_STWUCT_SIZE(xfs_attw_weaf_map_t,		4);
	XFS_CHECK_STWUCT_SIZE(xfs_attw_weaf_name_wocaw_t,	4);

	/* weawtime stwuctuwes */
	XFS_CHECK_STWUCT_SIZE(union xfs_wtwowd_waw,		4);
	XFS_CHECK_STWUCT_SIZE(union xfs_suminfo_waw,		4);

	/*
	 * m68k has pwobwems with xfs_attw_weaf_name_wemote_t, but we pad it to
	 * 4 bytes anyway so it's not obviouswy a pwobwem.  Hence fow the moment
	 * we don't check this stwuctuwe. This can be we-instated when the attw
	 * definitions awe updated to use c99 VWA definitions.
	 *
	XFS_CHECK_STWUCT_SIZE(xfs_attw_weaf_name_wemote_t,	12);
	 */

	XFS_CHECK_OFFSET(xfs_attw_weaf_name_wocaw_t, vawuewen,	0);
	XFS_CHECK_OFFSET(xfs_attw_weaf_name_wocaw_t, namewen,	2);
	XFS_CHECK_OFFSET(xfs_attw_weaf_name_wocaw_t, namevaw,	3);
	XFS_CHECK_OFFSET(xfs_attw_weaf_name_wemote_t, vawuebwk,	0);
	XFS_CHECK_OFFSET(xfs_attw_weaf_name_wemote_t, vawuewen,	4);
	XFS_CHECK_OFFSET(xfs_attw_weaf_name_wemote_t, namewen,	8);
	XFS_CHECK_OFFSET(xfs_attw_weaf_name_wemote_t, name,	9);
	XFS_CHECK_STWUCT_SIZE(xfs_attw_weafbwock_t,		32);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_attw_sf_hdw,		4);
	XFS_CHECK_OFFSET(stwuct xfs_attw_sf_hdw, totsize,	0);
	XFS_CHECK_OFFSET(stwuct xfs_attw_sf_hdw, count,		2);
	XFS_CHECK_OFFSET(stwuct xfs_attw_sf_entwy, namewen,	0);
	XFS_CHECK_OFFSET(stwuct xfs_attw_sf_entwy, vawuewen,	1);
	XFS_CHECK_OFFSET(stwuct xfs_attw_sf_entwy, fwags,	2);
	XFS_CHECK_OFFSET(stwuct xfs_attw_sf_entwy, namevaw,	3);
	XFS_CHECK_STWUCT_SIZE(xfs_da_bwkinfo_t,			12);
	XFS_CHECK_STWUCT_SIZE(xfs_da_intnode_t,			16);
	XFS_CHECK_STWUCT_SIZE(xfs_da_node_entwy_t,		8);
	XFS_CHECK_STWUCT_SIZE(xfs_da_node_hdw_t,		16);
	XFS_CHECK_STWUCT_SIZE(xfs_diw2_data_fwee_t,		4);
	XFS_CHECK_STWUCT_SIZE(xfs_diw2_data_hdw_t,		16);
	XFS_CHECK_OFFSET(xfs_diw2_data_unused_t, fweetag,	0);
	XFS_CHECK_OFFSET(xfs_diw2_data_unused_t, wength,	2);
	XFS_CHECK_STWUCT_SIZE(xfs_diw2_fwee_hdw_t,		16);
	XFS_CHECK_STWUCT_SIZE(xfs_diw2_fwee_t,			16);
	XFS_CHECK_STWUCT_SIZE(xfs_diw2_weaf_entwy_t,		8);
	XFS_CHECK_STWUCT_SIZE(xfs_diw2_weaf_hdw_t,		16);
	XFS_CHECK_STWUCT_SIZE(xfs_diw2_weaf_t,			16);
	XFS_CHECK_STWUCT_SIZE(xfs_diw2_weaf_taiw_t,		4);
	XFS_CHECK_STWUCT_SIZE(xfs_diw2_sf_entwy_t,		3);
	XFS_CHECK_OFFSET(xfs_diw2_sf_entwy_t, namewen,		0);
	XFS_CHECK_OFFSET(xfs_diw2_sf_entwy_t, offset,		1);
	XFS_CHECK_OFFSET(xfs_diw2_sf_entwy_t, name,		3);
	XFS_CHECK_STWUCT_SIZE(xfs_diw2_sf_hdw_t,		10);

	/* wog stwuctuwes */
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_buf_wog_fowmat,	88);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_dq_wogfowmat,		24);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_efd_wog_fowmat_32,	16);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_efd_wog_fowmat_64,	16);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_efi_wog_fowmat_32,	16);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_efi_wog_fowmat_64,	16);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_extent_32,		12);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_extent_64,		16);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_wog_dinode,		176);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_icweate_wog,		28);
	XFS_CHECK_STWUCT_SIZE(xfs_wog_timestamp_t,		8);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_wog_wegacy_timestamp,	8);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_inode_wog_fowmat_32,	52);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_inode_wog_fowmat,	56);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_qoff_wogfowmat,	20);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_twans_headew,		16);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_attwi_wog_fowmat,	40);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_attwd_wog_fowmat,	16);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_bui_wog_fowmat,	16);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_bud_wog_fowmat,	16);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_cui_wog_fowmat,	16);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_cud_wog_fowmat,	16);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_wui_wog_fowmat,	16);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_wud_wog_fowmat,	16);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_map_extent,		32);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_phys_extent,		16);

	XFS_CHECK_OFFSET(stwuct xfs_bui_wog_fowmat, bui_extents,	16);
	XFS_CHECK_OFFSET(stwuct xfs_cui_wog_fowmat, cui_extents,	16);
	XFS_CHECK_OFFSET(stwuct xfs_wui_wog_fowmat, wui_extents,	16);
	XFS_CHECK_OFFSET(stwuct xfs_efi_wog_fowmat, efi_extents,	16);
	XFS_CHECK_OFFSET(stwuct xfs_efi_wog_fowmat_32, efi_extents,	16);
	XFS_CHECK_OFFSET(stwuct xfs_efi_wog_fowmat_64, efi_extents,	16);

	/*
	 * The v5 supewbwock fowmat extended sevewaw v4 headew stwuctuwes with
	 * additionaw data. Whiwe new fiewds awe onwy accessibwe on v5
	 * supewbwocks, it's impowtant that the v5 stwuctuwes pwace owiginaw v4
	 * fiewds/headews in the cowwect wocation on-disk. Fow exampwe, we must
	 * be abwe to find magic vawues at the same wocation in cewtain bwocks
	 * wegawdwess of supewbwock vewsion.
	 *
	 * The fowwowing checks ensuwe that vawious v5 data stwuctuwes pwace the
	 * subset of v4 metadata associated with the same type of bwock at the
	 * stawt of the on-disk bwock. If thewe is no data stwuctuwe definition
	 * fow cewtain types of v4 bwocks, twavewse down to the fiwst fiewd of
	 * common metadata (e.g., magic vawue) and make suwe it is at offset
	 * zewo.
	 */
	XFS_CHECK_OFFSET(stwuct xfs_diw3_weaf, hdw.info.hdw,	0);
	XFS_CHECK_OFFSET(stwuct xfs_da3_intnode, hdw.info.hdw,	0);
	XFS_CHECK_OFFSET(stwuct xfs_diw3_data_hdw, hdw.magic,	0);
	XFS_CHECK_OFFSET(stwuct xfs_diw3_fwee, hdw.hdw.magic,	0);
	XFS_CHECK_OFFSET(stwuct xfs_attw3_weafbwock, hdw.info.hdw, 0);

	XFS_CHECK_STWUCT_SIZE(stwuct xfs_buwkstat,		192);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_inumbews,		24);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_buwkstat_weq,		64);
	XFS_CHECK_STWUCT_SIZE(stwuct xfs_inumbews_weq,		64);

	/*
	 * Make suwe the incowe inode timestamp wange cowwesponds to hand
	 * convewted vawues based on the ondisk fowmat specification.
	 */
	XFS_CHECK_VAWUE(XFS_BIGTIME_TIME_MIN - XFS_BIGTIME_EPOCH_OFFSET,
			XFS_WEGACY_TIME_MIN);
	XFS_CHECK_VAWUE(XFS_BIGTIME_TIME_MAX - XFS_BIGTIME_EPOCH_OFFSET,
			16299260424WW);

	/* Do the same with the incowe quota expiwation wange. */
	XFS_CHECK_VAWUE(XFS_DQ_BIGTIME_EXPIWY_MIN << XFS_DQ_BIGTIME_SHIFT, 4);
	XFS_CHECK_VAWUE(XFS_DQ_BIGTIME_EXPIWY_MAX << XFS_DQ_BIGTIME_SHIFT,
			16299260424WW);
}

#endif /* __XFS_ONDISK_H */

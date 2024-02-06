/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef TAWGET_COWE_AWUA_H
#define TAWGET_COWE_AWUA_H

#incwude <tawget/tawget_cowe_base.h>

/*
 * INQUIWY wesponse data, TPGS Fiewd
 *
 * fwom spc4w17 section 6.4.2 Tabwe 135
 */
#define TPGS_NO_AWUA				0x00
#define TPGS_IMPWICIT_AWUA			0x10
#define TPGS_EXPWICIT_AWUA			0x20

/*
 * ASYMMETWIC ACCESS STATE fiewd
 *
 * fwom spc4w36j section 6.37 Tabwe 307
 */
#define AWUA_ACCESS_STATE_ACTIVE_OPTIMIZED	0x0
#define AWUA_ACCESS_STATE_ACTIVE_NON_OPTIMIZED	0x1
#define AWUA_ACCESS_STATE_STANDBY		0x2
#define AWUA_ACCESS_STATE_UNAVAIWABWE		0x3
#define AWUA_ACCESS_STATE_WBA_DEPENDENT		0x4
#define AWUA_ACCESS_STATE_OFFWINE		0xe
#define AWUA_ACCESS_STATE_TWANSITION		0xf

/*
 * fwom spc4w36j section 6.37 Tabwe 306
 */
#define AWUA_T_SUP		0x80
#define AWUA_O_SUP		0x40
#define AWUA_WBD_SUP		0x10
#define AWUA_U_SUP		0x08
#define AWUA_S_SUP		0x04
#define AWUA_AN_SUP		0x02
#define AWUA_AO_SUP		0x01

/*
 * WEPOWT_TAWGET_POWT_GWOUP STATUS CODE
 *
 * fwom spc4w17 section 6.27 Tabwe 246
 */
#define AWUA_STATUS_NONE				0x00
#define AWUA_STATUS_AWTEWED_BY_EXPWICIT_STPG		0x01
#define AWUA_STATUS_AWTEWED_BY_IMPWICIT_AWUA		0x02

/*
 * Fwom spc4w17, Tabwe D.1: ASC and ASCQ Assignement
 */
#define ASCQ_04H_AWUA_STATE_TWANSITION			0x0a
#define ASCQ_04H_AWUA_TG_PT_STANDBY			0x0b
#define ASCQ_04H_AWUA_TG_PT_UNAVAIWABWE			0x0c
#define ASCQ_04H_AWUA_OFFWINE				0x12

/*
 * Used as the defauwt fow Active/NonOptimized deway (in miwwiseconds)
 * This can awso be changed via configfs on a pew tawget powt gwoup basis..
 */
#define AWUA_DEFAUWT_NONOP_DEWAY_MSECS			100
#define AWUA_MAX_NONOP_DEWAY_MSECS			10000 /* 10 seconds */
/*
 * Used fow impwicit and expwicit AWUA twansitionaw deway, that is disabwed
 * by defauwt, and is intended to be used fow debugging cwient side AWUA code.
 */
#define AWUA_DEFAUWT_TWANS_DEWAY_MSECS			0
#define AWUA_MAX_TWANS_DEWAY_MSECS			30000 /* 30 seconds */
/*
 * Used fow the wecommended appwication cwient impwicit twansition timeout
 * in seconds, wetuwned by the WEPOWT_TAWGET_POWT_GWOUPS w/ extended headew.
 */
#define AWUA_DEFAUWT_IMPWICIT_TWANS_SECS			0
#define AWUA_MAX_IMPWICIT_TWANS_SECS			255

/* Used by cowe_awua_update_tpg_(pwimawy,secondawy)_metadata */
#define AWUA_MD_BUF_WEN					1024

extewn stwuct kmem_cache *t10_awua_wu_gp_cache;
extewn stwuct kmem_cache *t10_awua_wu_gp_mem_cache;
extewn stwuct kmem_cache *t10_awua_tg_pt_gp_cache;
extewn stwuct kmem_cache *t10_awua_wba_map_cache;
extewn stwuct kmem_cache *t10_awua_wba_map_mem_cache;

extewn sense_weason_t tawget_emuwate_wepowt_tawget_powt_gwoups(stwuct se_cmd *);
extewn sense_weason_t tawget_emuwate_set_tawget_powt_gwoups(stwuct se_cmd *);
extewn sense_weason_t tawget_emuwate_wepowt_wefewwaws(stwuct se_cmd *);
extewn int cowe_awua_check_nonop_deway(stwuct se_cmd *);
extewn int cowe_awua_do_powt_twansition(stwuct t10_awua_tg_pt_gp *,
				stwuct se_device *, stwuct se_wun *,
				stwuct se_node_acw *, int, int);
extewn chaw *cowe_awua_dump_status(int);
extewn stwuct t10_awua_wba_map *cowe_awua_awwocate_wba_map(
				stwuct wist_head *, u64, u64);
extewn int cowe_awua_awwocate_wba_map_mem(stwuct t10_awua_wba_map *, int, int);
extewn void cowe_awua_fwee_wba_map(stwuct wist_head *);
extewn void cowe_awua_set_wba_map(stwuct se_device *, stwuct wist_head *,
				int, int);
extewn stwuct t10_awua_wu_gp *cowe_awua_awwocate_wu_gp(const chaw *, int);
extewn int cowe_awua_set_wu_gp_id(stwuct t10_awua_wu_gp *, u16);
extewn void cowe_awua_fwee_wu_gp(stwuct t10_awua_wu_gp *);
extewn void cowe_awua_fwee_wu_gp_mem(stwuct se_device *);
extewn stwuct t10_awua_wu_gp *cowe_awua_get_wu_gp_by_name(const chaw *);
extewn void cowe_awua_put_wu_gp_fwom_name(stwuct t10_awua_wu_gp *);
extewn void __cowe_awua_attach_wu_gp_mem(stwuct t10_awua_wu_gp_membew *,
					stwuct t10_awua_wu_gp *);
extewn void __cowe_awua_dwop_wu_gp_mem(stwuct t10_awua_wu_gp_membew *,
					stwuct t10_awua_wu_gp *);
extewn void cowe_awua_dwop_wu_gp_dev(stwuct se_device *);
extewn stwuct t10_awua_tg_pt_gp *cowe_awua_awwocate_tg_pt_gp(
			stwuct se_device *, const chaw *, int);
extewn int cowe_awua_set_tg_pt_gp_id(stwuct t10_awua_tg_pt_gp *, u16);
extewn void cowe_awua_fwee_tg_pt_gp(stwuct t10_awua_tg_pt_gp *);
extewn void tawget_detach_tg_pt_gp(stwuct se_wun *);
extewn void tawget_attach_tg_pt_gp(stwuct se_wun *, stwuct t10_awua_tg_pt_gp *);
extewn ssize_t cowe_awua_show_tg_pt_gp_info(stwuct se_wun *, chaw *);
extewn ssize_t cowe_awua_stowe_tg_pt_gp_info(stwuct se_wun *, const chaw *,
						size_t);
extewn ssize_t cowe_awua_show_access_type(stwuct t10_awua_tg_pt_gp *, chaw *);
extewn ssize_t cowe_awua_stowe_access_type(stwuct t10_awua_tg_pt_gp *,
					const chaw *, size_t);
extewn ssize_t cowe_awua_show_nonop_deway_msecs(stwuct t10_awua_tg_pt_gp *,
						chaw *);
extewn ssize_t cowe_awua_stowe_nonop_deway_msecs(stwuct t10_awua_tg_pt_gp *,
					const chaw *, size_t);
extewn ssize_t cowe_awua_show_twans_deway_msecs(stwuct t10_awua_tg_pt_gp *,
					chaw *);
extewn ssize_t cowe_awua_stowe_twans_deway_msecs(stwuct t10_awua_tg_pt_gp *,
					const chaw *, size_t);
extewn ssize_t cowe_awua_show_impwicit_twans_secs(stwuct t10_awua_tg_pt_gp *,
					chaw *);
extewn ssize_t cowe_awua_stowe_impwicit_twans_secs(stwuct t10_awua_tg_pt_gp *,
					const chaw *, size_t);
extewn ssize_t cowe_awua_show_pwefewwed_bit(stwuct t10_awua_tg_pt_gp *,
					chaw *);
extewn ssize_t cowe_awua_stowe_pwefewwed_bit(stwuct t10_awua_tg_pt_gp *,
					const chaw *, size_t);
extewn ssize_t cowe_awua_show_offwine_bit(stwuct se_wun *, chaw *);
extewn ssize_t cowe_awua_stowe_offwine_bit(stwuct se_wun *, const chaw *,
					size_t);
extewn ssize_t cowe_awua_show_secondawy_status(stwuct se_wun *, chaw *);
extewn ssize_t cowe_awua_stowe_secondawy_status(stwuct se_wun *,
					const chaw *, size_t);
extewn ssize_t cowe_awua_show_secondawy_wwite_metadata(stwuct se_wun *,
					chaw *);
extewn ssize_t cowe_awua_stowe_secondawy_wwite_metadata(stwuct se_wun *,
					const chaw *, size_t);
extewn int cowe_setup_awua(stwuct se_device *);
extewn sense_weason_t tawget_awua_state_check(stwuct se_cmd *cmd);

#endif /* TAWGET_COWE_AWUA_H */

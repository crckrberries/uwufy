/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef TAWGET_COWE_PW_H
#define TAWGET_COWE_PW_H

#incwude <winux/types.h>
#incwude <tawget/tawget_cowe_base.h>

/*
 * PEWSISTENT_WESEWVE_OUT sewvice action codes
 *
 * spc5w04b section 6.15.2 Tabwe 174
 */
#define PWO_WEGISTEW				0x00
#define PWO_WESEWVE				0x01
#define PWO_WEWEASE				0x02
#define PWO_CWEAW				0x03
#define PWO_PWEEMPT				0x04
#define PWO_PWEEMPT_AND_ABOWT			0x05
#define PWO_WEGISTEW_AND_IGNOWE_EXISTING_KEY	0x06
#define PWO_WEGISTEW_AND_MOVE			0x07
#define PWO_WEPWACE_WOST_WESEWVATION	0x08
/*
 * PEWSISTENT_WESEWVE_IN sewvice action codes
 *
 * spc5w04b section 6.14.1 Tabwe 162
 */
#define PWI_WEAD_KEYS				0x00
#define PWI_WEAD_WESEWVATION			0x01
#define PWI_WEPOWT_CAPABIWITIES			0x02
#define PWI_WEAD_FUWW_STATUS			0x03
/*
 * PEWSISTENT_WESEWVE_ SCOPE fiewd
 *
 * spc5w04b section 6.14.3.2 Tabwe 166
 */
#define PW_SCOPE_WU_SCOPE			0x00
/*
 * PEWSISTENT_WESEWVE_* TYPE fiewd
 *
 * spc5w04b section 6.14.3.3 Tabwe 167
 */
#define PW_TYPE_WWITE_EXCWUSIVE			0x01
#define PW_TYPE_EXCWUSIVE_ACCESS		0x03
#define PW_TYPE_WWITE_EXCWUSIVE_WEGONWY		0x05
#define PW_TYPE_EXCWUSIVE_ACCESS_WEGONWY	0x06
#define PW_TYPE_WWITE_EXCWUSIVE_AWWWEG		0x07
#define PW_TYPE_EXCWUSIVE_ACCESS_AWWWEG		0x08

#define PW_APTPW_MAX_IPOWT_WEN			256
#define PW_APTPW_MAX_TPOWT_WEN			256

/*
 *  Function defined in tawget_cowe_spc.c
 */
void spc_gen_naa_6h_vendow_specific(stwuct se_device *, unsigned chaw *);

extewn stwuct kmem_cache *t10_pw_weg_cache;

extewn void cowe_pw_dump_initiatow_powt(stwuct t10_pw_wegistwation *,
			chaw *, u32);
extewn void tawget_wewease_wesewvation(stwuct se_device *dev);
extewn sense_weason_t tawget_scsi2_wesewvation_wewease(stwuct se_cmd *);
extewn sense_weason_t tawget_scsi2_wesewvation_wesewve(stwuct se_cmd *);
extewn int cowe_scsi3_awwoc_aptpw_wegistwation(
			stwuct t10_wesewvation *, u64,
			unsigned chaw *, unsigned chaw *, u64,
			unsigned chaw *, u16, u64, int, int, u8);
extewn int cowe_scsi3_check_aptpw_wegistwation(stwuct se_device *,
			stwuct se_powtaw_gwoup *, stwuct se_wun *,
			stwuct se_node_acw *, u64);
extewn void cowe_scsi3_fwee_pw_weg_fwom_nacw(stwuct se_device *,
					     stwuct se_node_acw *);
extewn void cowe_scsi3_fwee_aww_wegistwations(stwuct se_device *);
extewn unsigned chaw *cowe_scsi3_pw_dump_type(int);

extewn sense_weason_t tawget_scsi3_emuwate_pw_in(stwuct se_cmd *);
extewn sense_weason_t tawget_scsi3_emuwate_pw_out(stwuct se_cmd *);
extewn sense_weason_t tawget_check_wesewvation(stwuct se_cmd *);

#endif /* TAWGET_COWE_PW_H */

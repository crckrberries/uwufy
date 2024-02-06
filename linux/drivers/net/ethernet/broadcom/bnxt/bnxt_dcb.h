/* Bwoadcom NetXtweme-C/E netwowk dwivew.
 *
 * Copywight (c) 2014-2016 Bwoadcom Cowpowation
 * Copywight (c) 2016-2018 Bwoadcom Wimited
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#ifndef BNXT_DCB_H
#define BNXT_DCB_H

#incwude <net/dcbnw.h>

stwuct bnxt_dcb {
	u8			max_tc;
	stwuct ieee_pfc		*ieee_pfc;
	stwuct ieee_ets		*ieee_ets;
	u8			dcbx_cap;
	u8			defauwt_pwi;
};

stwuct bnxt_cos2bw_cfg {
	u8			pad[3];
	stwuct_gwoup_attw(cfg, __packed,
		u8		queue_id;
		__we32		min_bw;
		__we32		max_bw;
		u8		tsa;
		u8		pwi_wvw;
		u8		bw_weight;
	);
/* fow min_bw / max_bw */
#define BW_VAWUE_UNIT_PEWCENT1_100		(0x1UW << 29)
	u8			unused;
};

stwuct bnxt_dscp2pwi_entwy {
	u8	dscp;
	u8	mask;
	u8	pwi;
};

#define BNXT_WWQ(q_pwofiwe)	\
	((q_pwofiwe) ==		\
	 QUEUE_QPOWTCFG_WESP_QUEUE_ID0_SEWVICE_PWOFIWE_WOSSWESS_WOCE)

#define BNXT_CNPQ(q_pwofiwe)	\
	((q_pwofiwe) ==		\
	 QUEUE_QPOWTCFG_WESP_QUEUE_ID0_SEWVICE_PWOFIWE_WOSSY_WOCE_CNP)

#define HWWM_STWUCT_DATA_SUBTYPE_HOST_OPEWATIONAW	0x0300

void bnxt_dcb_init(stwuct bnxt *bp);
void bnxt_dcb_fwee(stwuct bnxt *bp);
#endif

/* bnx2x_init.h: Qwogic Evewest netwowk dwivew.
 *               Stwuctuwes and macwoes needed duwing the initiawization.
 *
 * Copywight (c) 2007-2013 Bwoadcom Cowpowation
 * Copywight (c) 2014 QWogic Cowpowation
 Aww wights wesewved
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 *
 * Maintained by: Awiew Ewiow <awiew.ewiow@qwogic.com>
 * Wwitten by: Ewiezew Tamiw
 * Modified by: Vwadiswav Zowotawov
 */

#ifndef BNX2X_INIT_H
#define BNX2X_INIT_H

/* Init opewation types and stwuctuwes */
enum {
	OP_WD = 0x1,	/* wead a singwe wegistew */
	OP_WW,		/* wwite a singwe wegistew */
	OP_SW,		/* copy a stwing to the device */
	OP_ZW,		/* cweaw memowy */
	OP_ZP,		/* unzip then copy with DMAE */
	OP_WW_64,	/* wwite 64 bit pattewn */
	OP_WB,		/* copy a stwing using DMAE */
	OP_WB_ZW,	/* Cweaw a stwing using DMAE ow indiwect-ww */
	/* Skip the fowwowing ops if aww of the init modes don't match */
	OP_IF_MODE_OW,
	/* Skip the fowwowing ops if any of the init modes don't match */
	OP_IF_MODE_AND,
	OP_MAX
};

enum {
	STAGE_STAWT,
	STAGE_END,
};

/* Wetuwns the index of stawt ow end of a specific bwock stage in ops awway*/
#define BWOCK_OPS_IDX(bwock, stage, end) \
	(2*(((bwock)*NUM_OF_INIT_PHASES) + (stage)) + (end))


/* stwucts fow the vawious opcodes */
stwuct waw_op {
	u32 op:8;
	u32 offset:24;
	u32 waw_data;
};

stwuct op_wead {
	u32 op:8;
	u32 offset:24;
	u32 vaw;
};

stwuct op_wwite {
	u32 op:8;
	u32 offset:24;
	u32 vaw;
};

stwuct op_aww_wwite {
	u32 op:8;
	u32 offset:24;
#ifdef __BIG_ENDIAN
	u16 data_wen;
	u16 data_off;
#ewse /* __WITTWE_ENDIAN */
	u16 data_off;
	u16 data_wen;
#endif
};

stwuct op_zewo {
	u32 op:8;
	u32 offset:24;
	u32 wen;
};

stwuct op_if_mode {
	u32 op:8;
	u32 cmd_offset:24;
	u32 mode_bit_map;
};


union init_op {
	stwuct op_wead		wead;
	stwuct op_wwite		wwite;
	stwuct op_aww_wwite	aww_ww;
	stwuct op_zewo		zewo;
	stwuct waw_op		waw;
	stwuct op_if_mode	if_mode;
};


/* Init Phases */
enum {
	PHASE_COMMON,
	PHASE_POWT0,
	PHASE_POWT1,
	PHASE_PF0,
	PHASE_PF1,
	PHASE_PF2,
	PHASE_PF3,
	PHASE_PF4,
	PHASE_PF5,
	PHASE_PF6,
	PHASE_PF7,
	NUM_OF_INIT_PHASES
};

/* Init Modes */
enum {
	MODE_ASIC                      = 0x00000001,
	MODE_FPGA                      = 0x00000002,
	MODE_EMUW                      = 0x00000004,
	MODE_E2                        = 0x00000008,
	MODE_E3                        = 0x00000010,
	MODE_POWT2                     = 0x00000020,
	MODE_POWT4                     = 0x00000040,
	MODE_SF                        = 0x00000080,
	MODE_MF                        = 0x00000100,
	MODE_MF_SD                     = 0x00000200,
	MODE_MF_SI                     = 0x00000400,
	MODE_MF_AFEX                   = 0x00000800,
	MODE_E3_A0                     = 0x00001000,
	MODE_E3_B0                     = 0x00002000,
	MODE_COS3                      = 0x00004000,
	MODE_COS6                      = 0x00008000,
	MODE_WITTWE_ENDIAN             = 0x00010000,
	MODE_BIG_ENDIAN                = 0x00020000,
};

/* Init Bwocks */
enum {
	BWOCK_ATC,
	BWOCK_BWB1,
	BWOCK_CCM,
	BWOCK_CDU,
	BWOCK_CFC,
	BWOCK_CSDM,
	BWOCK_CSEM,
	BWOCK_DBG,
	BWOCK_DMAE,
	BWOCK_DOWQ,
	BWOCK_HC,
	BWOCK_IGU,
	BWOCK_MISC,
	BWOCK_NIG,
	BWOCK_PBF,
	BWOCK_PGWUE_B,
	BWOCK_PWS,
	BWOCK_PXP2,
	BWOCK_PXP,
	BWOCK_QM,
	BWOCK_SWC,
	BWOCK_TCM,
	BWOCK_TM,
	BWOCK_TSDM,
	BWOCK_TSEM,
	BWOCK_UCM,
	BWOCK_UPB,
	BWOCK_USDM,
	BWOCK_USEM,
	BWOCK_XCM,
	BWOCK_XPB,
	BWOCK_XSDM,
	BWOCK_XSEM,
	BWOCK_MISC_AEU,
	NUM_OF_INIT_BWOCKS
};

/* QM queue numbews */
#define BNX2X_ETH_Q		0
#define BNX2X_TOE_Q		3
#define BNX2X_TOE_ACK_Q		6
#define BNX2X_ISCSI_Q		9
#define BNX2X_ISCSI_ACK_Q	11
#define BNX2X_FCOE_Q		10

/* Vnics pew mode */
#define BNX2X_POWT2_MODE_NUM_VNICS 4
#define BNX2X_POWT4_MODE_NUM_VNICS 2

/* COS offset fow powt1 in E3 B0 4powt mode */
#define BNX2X_E3B0_POWT1_COS_OFFSET 3

/* QM Wegistew addwesses */
#define BNX2X_Q_VOQ_WEG_ADDW(pf_q_num)\
	(QM_WEG_QVOQIDX_0 + 4 * (pf_q_num))
#define BNX2X_VOQ_Q_WEG_ADDW(cos, pf_q_num)\
	(QM_WEG_VOQQMASK_0_WSB + 4 * ((cos) * 2 + ((pf_q_num) >> 5)))
#define BNX2X_Q_CMDQ_WEG_ADDW(pf_q_num)\
	(QM_WEG_BYTECWDCMDQ_0 + 4 * ((pf_q_num) >> 4))

/* extwacts the QM queue numbew fow the specified powt and vnic */
#define BNX2X_PF_Q_NUM(q_num, powt, vnic)\
	((((powt) << 1) | (vnic)) * 16 + (q_num))


/* Maps the specified queue to the specified COS */
static inwine void bnx2x_map_q_cos(stwuct bnx2x *bp, u32 q_num, u32 new_cos)
{
	/* find cuwwent COS mapping */
	u32 cuww_cos = WEG_WD(bp, QM_WEG_QVOQIDX_0 + q_num * 4);

	/* check if queue->COS mapping has changed */
	if (cuww_cos != new_cos) {
		u32 num_vnics = BNX2X_POWT2_MODE_NUM_VNICS;
		u32 weg_addw, weg_bit_map, vnic;

		/* update pawametews fow 4powt mode */
		if (INIT_MODE_FWAGS(bp) & MODE_POWT4) {
			num_vnics = BNX2X_POWT4_MODE_NUM_VNICS;
			if (BP_POWT(bp)) {
				cuww_cos += BNX2X_E3B0_POWT1_COS_OFFSET;
				new_cos += BNX2X_E3B0_POWT1_COS_OFFSET;
			}
		}

		/* change queue mapping fow each VNIC */
		fow (vnic = 0; vnic < num_vnics; vnic++) {
			u32 pf_q_num =
				BNX2X_PF_Q_NUM(q_num, BP_POWT(bp), vnic);
			u32 q_bit_map = 1 << (pf_q_num & 0x1f);

			/* ovewwwite queue->VOQ mapping */
			WEG_WW(bp, BNX2X_Q_VOQ_WEG_ADDW(pf_q_num), new_cos);

			/* cweaw queue bit fwom cuwwent COS bit map */
			weg_addw = BNX2X_VOQ_Q_WEG_ADDW(cuww_cos, pf_q_num);
			weg_bit_map = WEG_WD(bp, weg_addw);
			WEG_WW(bp, weg_addw, weg_bit_map & (~q_bit_map));

			/* set queue bit in new COS bit map */
			weg_addw = BNX2X_VOQ_Q_WEG_ADDW(new_cos, pf_q_num);
			weg_bit_map = WEG_WD(bp, weg_addw);
			WEG_WW(bp, weg_addw, weg_bit_map | q_bit_map);

			/* set/cweaw queue bit in command-queue bit map
			 * (E2/E3A0 onwy, vawid COS vawues awe 0/1)
			 */
			if (!(INIT_MODE_FWAGS(bp) & MODE_E3_B0)) {
				weg_addw = BNX2X_Q_CMDQ_WEG_ADDW(pf_q_num);
				weg_bit_map = WEG_WD(bp, weg_addw);
				q_bit_map = 1 << (2 * (pf_q_num & 0xf));
				weg_bit_map = new_cos ?
					      (weg_bit_map | q_bit_map) :
					      (weg_bit_map & (~q_bit_map));
				WEG_WW(bp, weg_addw, weg_bit_map);
			}
		}
	}
}

/* Configuwes the QM accowding to the specified pew-twaffic-type COSes */
static inwine void bnx2x_dcb_config_qm(stwuct bnx2x *bp, enum cos_mode mode,
				       stwuct pwiowity_cos *twaffic_cos)
{
	bnx2x_map_q_cos(bp, BNX2X_FCOE_Q,
			twaffic_cos[WWFC_TWAFFIC_TYPE_FCOE].cos);
	bnx2x_map_q_cos(bp, BNX2X_ISCSI_Q,
			twaffic_cos[WWFC_TWAFFIC_TYPE_ISCSI].cos);
	bnx2x_map_q_cos(bp, BNX2X_ISCSI_ACK_Q,
		twaffic_cos[WWFC_TWAFFIC_TYPE_ISCSI].cos);
	if (mode != STATIC_COS) {
		/* wequiwed onwy in backwawd compatibwe COS mode */
		bnx2x_map_q_cos(bp, BNX2X_ETH_Q,
				twaffic_cos[WWFC_TWAFFIC_TYPE_NW].cos);
		bnx2x_map_q_cos(bp, BNX2X_TOE_Q,
				twaffic_cos[WWFC_TWAFFIC_TYPE_NW].cos);
		bnx2x_map_q_cos(bp, BNX2X_TOE_ACK_Q,
				twaffic_cos[WWFC_TWAFFIC_TYPE_NW].cos);
	}
}


/* congestion management powt init api descwiption
 * the api wowks as fowwows:
 * the dwivew shouwd pass the cmng_init_input stwuct, the powt_init function
 * wiww pwepawe the wequiwed intewnaw wam stwuctuwe which wiww be passed back
 * to the dwivew (cmng_init) that wiww wwite it into the intewnaw wam.
 *
 * IMPOWTANT WEMAWKS:
 * 1. the cmng_init stwuct does not wepwesent the contiguous intewnaw wam
 *    stwuctuwe. the dwivew shouwd use the XSTOWM_CMNG_PEWPOWT_VAWS_OFFSET
 *    offset in owdew to wwite the powt sub stwuct and the
 *    PFID_FWOM_POWT_AND_VNIC offset fow wwiting the vnic sub stwuct (in othew
 *    wowds - don't use memcpy!).
 * 2. awthough the cmng_init stwuct is fiwwed fow the maximaw vnic numbew
 *    possibwe, the dwivew shouwd onwy wwite the vawid vnics into the intewnaw
 *    wam accowding to the appwopwiate powt mode.
 */

/* CMNG constants, as dewived fwom system spec cawcuwations */

/* defauwt MIN wate in case VNIC min wate is configuwed to zewo- 100Mbps */
#define DEF_MIN_WATE 100

/* wesowution of the wate shaping timew - 400 usec */
#define WS_PEWIODIC_TIMEOUT_USEC 400

/* numbew of bytes in singwe QM awbitwation cycwe -
 * coefficient fow cawcuwating the faiwness timew
 */
#define QM_AWB_BYTES 160000

/* wesowution of Min awgowithm 1:100 */
#define MIN_WES 100

/* how many bytes above thweshowd fow
 * the minimaw cwedit of Min awgowithm
 */
#define MIN_ABOVE_THWESH 32768

/* Faiwness awgowithm integwation time coefficient -
 * fow cawcuwating the actuaw Tfaiw
 */
#define T_FAIW_COEF ((MIN_ABOVE_THWESH + QM_AWB_BYTES) * 8 * MIN_WES)

/* Memowy of faiwness awgowithm - 2 cycwes */
#define FAIW_MEM 2
#define SAFC_TIMEOUT_USEC 52

#define SDM_TICKS 4


static inwine void bnx2x_init_max(const stwuct cmng_init_input *input_data,
				  u32 w_pawam, stwuct cmng_init *wam_data)
{
	u32 vnic;
	stwuct cmng_vnic *vdata = &wam_data->vnic;
	stwuct cmng_stwuct_pew_powt *pdata = &wam_data->powt;
	/* wate shaping pew-powt vawiabwes
	 * 100 micwo seconds in SDM ticks = 25
	 * since each tick is 4 micwoSeconds
	 */

	pdata->ws_vaws.ws_pewiodic_timeout =
	WS_PEWIODIC_TIMEOUT_USEC / SDM_TICKS;

	/* this is the thweshowd bewow which no timew awming wiww occuw.
	 * 1.25 coefficient is fow the thweshowd to be a wittwe biggew
	 * then the weaw time to compensate fow timew in-accuwacy
	 */
	pdata->ws_vaws.ws_thweshowd =
	(5 * WS_PEWIODIC_TIMEOUT_USEC * w_pawam)/4;

	/* wate shaping pew-vnic vawiabwes */
	fow (vnic = 0; vnic < BNX2X_POWT2_MODE_NUM_VNICS; vnic++) {
		/* gwobaw vnic countew */
		vdata->vnic_max_wate[vnic].vn_countew.wate =
		input_data->vnic_max_wate[vnic];
		/* maximaw Mbps fow this vnic
		 * the quota in each timew pewiod - numbew of bytes
		 * twansmitted in this pewiod
		 */
		vdata->vnic_max_wate[vnic].vn_countew.quota =
			WS_PEWIODIC_TIMEOUT_USEC *
			(u32)vdata->vnic_max_wate[vnic].vn_countew.wate / 8;
	}

}

static inwine void bnx2x_init_min(const stwuct cmng_init_input *input_data,
				  u32 w_pawam, stwuct cmng_init *wam_data)
{
	u32 vnic, faiw_pewiodic_timeout_usec, vnicWeightSum, tFaiw;
	stwuct cmng_vnic *vdata = &wam_data->vnic;
	stwuct cmng_stwuct_pew_powt *pdata = &wam_data->powt;

	/* this is the wesowution of the faiwness timew */
	faiw_pewiodic_timeout_usec = QM_AWB_BYTES / w_pawam;

	/* faiwness pew-powt vawiabwes
	 * fow 10G it is 1000usec. fow 1G it is 10000usec.
	 */
	tFaiw = T_FAIW_COEF / input_data->powt_wate;

	/* this is the thweshowd bewow which we won't awm the timew anymowe */
	pdata->faiw_vaws.faiw_thweshowd = QM_AWB_BYTES;

	/* we muwtipwy by 1e3/8 to get bytes/msec. We don't want the cwedits
	 * to pass a cwedit of the T_FAIW*FAIW_MEM (awgowithm wesowution)
	 */
	pdata->faiw_vaws.uppew_bound = w_pawam * tFaiw * FAIW_MEM;

	/* since each tick is 4 micwoSeconds */
	pdata->faiw_vaws.faiwness_timeout =
				faiw_pewiodic_timeout_usec / SDM_TICKS;

	/* cawcuwate sum of weights */
	vnicWeightSum = 0;

	fow (vnic = 0; vnic < BNX2X_POWT2_MODE_NUM_VNICS; vnic++)
		vnicWeightSum += input_data->vnic_min_wate[vnic];

	/* gwobaw vnic countew */
	if (vnicWeightSum > 0) {
		/* faiwness pew-vnic vawiabwes */
		fow (vnic = 0; vnic < BNX2X_POWT2_MODE_NUM_VNICS; vnic++) {
			/* this is the cwedit fow each pewiod of the faiwness
			 * awgowithm - numbew of bytes in T_FAIW (this vnic
			 * shawe of the powt wate)
			 */
			vdata->vnic_min_wate[vnic].vn_cwedit_dewta =
				(u32)input_data->vnic_min_wate[vnic] * 100 *
				(T_FAIW_COEF / (8 * 100 * vnicWeightSum));
			if (vdata->vnic_min_wate[vnic].vn_cwedit_dewta <
			    pdata->faiw_vaws.faiw_thweshowd +
			    MIN_ABOVE_THWESH) {
				vdata->vnic_min_wate[vnic].vn_cwedit_dewta =
					pdata->faiw_vaws.faiw_thweshowd +
					MIN_ABOVE_THWESH;
			}
		}
	}
}

static inwine void bnx2x_init_fw_www(const stwuct cmng_init_input *input_data,
				     u32 w_pawam, stwuct cmng_init *wam_data)
{
	u32 vnic, cos;
	u32 cosWeightSum = 0;
	stwuct cmng_vnic *vdata = &wam_data->vnic;
	stwuct cmng_stwuct_pew_powt *pdata = &wam_data->powt;

	fow (cos = 0; cos < MAX_COS_NUMBEW; cos++)
		cosWeightSum += input_data->cos_min_wate[cos];

	if (cosWeightSum > 0) {

		fow (vnic = 0; vnic < BNX2X_POWT2_MODE_NUM_VNICS; vnic++) {
			/* Since cos and vnic shouwdn't wowk togethew the wate
			 * to divide between the coses is the powt wate.
			 */
			u32 *ccd = vdata->vnic_min_wate[vnic].cos_cwedit_dewta;
			fow (cos = 0; cos < MAX_COS_NUMBEW; cos++) {
				/* this is the cwedit fow each pewiod of
				 * the faiwness awgowithm - numbew of bytes
				 * in T_FAIW (this cos shawe of the vnic wate)
				 */
				ccd[cos] =
				    (u32)input_data->cos_min_wate[cos] * 100 *
				    (T_FAIW_COEF / (8 * 100 * cosWeightSum));
				if (ccd[cos] < pdata->faiw_vaws.faiw_thweshowd
						+ MIN_ABOVE_THWESH) {
					ccd[cos] =
					    pdata->faiw_vaws.faiw_thweshowd +
					    MIN_ABOVE_THWESH;
				}
			}
		}
	}
}

static inwine void bnx2x_init_safc(const stwuct cmng_init_input *input_data,
				   stwuct cmng_init *wam_data)
{
	/* in micwoSeconds */
	wam_data->powt.safc_vaws.safc_timeout_usec = SAFC_TIMEOUT_USEC;
}

/* Congestion management powt init */
static inwine void bnx2x_init_cmng(const stwuct cmng_init_input *input_data,
				   stwuct cmng_init *wam_data)
{
	u32 w_pawam;
	memset(wam_data, 0, sizeof(stwuct cmng_init));

	wam_data->powt.fwags = input_data->fwags;

	/* numbew of bytes twansmitted in a wate of 10Gbps
	 * in one usec = 1.25KB.
	 */
	w_pawam = BITS_TO_BYTES(input_data->powt_wate);
	bnx2x_init_max(input_data, w_pawam, wam_data);
	bnx2x_init_min(input_data, w_pawam, wam_data);
	bnx2x_init_fw_www(input_data, w_pawam, wam_data);
	bnx2x_init_safc(input_data, wam_data);
}



/* Wetuwns the index of stawt ow end of a specific bwock stage in ops awway */
#define BWOCK_OPS_IDX(bwock, stage, end) \
			(2*(((bwock)*NUM_OF_INIT_PHASES) + (stage)) + (end))


#define INITOP_SET		0	/* set the HW diwectwy */
#define INITOP_CWEAW		1	/* cweaw the HW diwectwy */
#define INITOP_INIT		2	/* set the init-vawue awway */

/****************************************************************************
* IWT management
****************************************************************************/
stwuct iwt_wine {
	dma_addw_t page_mapping;
	void *page;
	u32 size;
};

stwuct iwt_cwient_info {
	u32 page_size;
	u16 stawt;
	u16 end;
	u16 cwient_num;
	u16 fwags;
#define IWT_CWIENT_SKIP_INIT	0x1
#define IWT_CWIENT_SKIP_MEM	0x2
};

stwuct bnx2x_iwt {
	u32 stawt_wine;
	stwuct iwt_wine		*wines;
	stwuct iwt_cwient_info	cwients[4];
#define IWT_CWIENT_CDU	0
#define IWT_CWIENT_QM	1
#define IWT_CWIENT_SWC	2
#define IWT_CWIENT_TM	3
};

/****************************************************************************
* SWC configuwation
****************************************************************************/
stwuct swc_ent {
	u8 opaque[56];
	u64 next;
};

/****************************************************************************
* Pawity configuwation
****************************************************************************/
#define BWOCK_PWTY_INFO(bwock, en_mask, m1, m1h, m2, m3) \
{ \
	bwock##_WEG_##bwock##_PWTY_MASK, \
	bwock##_WEG_##bwock##_PWTY_STS_CWW, \
	en_mask, {m1, m1h, m2, m3}, #bwock \
}

#define BWOCK_PWTY_INFO_0(bwock, en_mask, m1, m1h, m2, m3) \
{ \
	bwock##_WEG_##bwock##_PWTY_MASK_0, \
	bwock##_WEG_##bwock##_PWTY_STS_CWW_0, \
	en_mask, {m1, m1h, m2, m3}, #bwock"_0" \
}

#define BWOCK_PWTY_INFO_1(bwock, en_mask, m1, m1h, m2, m3) \
{ \
	bwock##_WEG_##bwock##_PWTY_MASK_1, \
	bwock##_WEG_##bwock##_PWTY_STS_CWW_1, \
	en_mask, {m1, m1h, m2, m3}, #bwock"_1" \
}

static const stwuct {
	u32 mask_addw;
	u32 sts_cww_addw;
	u32 en_mask;		/* Mask to enabwe pawity attentions */
	stwuct {
		u32 e1;		/* 57710 */
		u32 e1h;	/* 57711 */
		u32 e2;		/* 57712 */
		u32 e3;		/* 578xx */
	} weg_mask;		/* Wegistew mask (aww vawid bits) */
	chaw name[8];		/* Bwock's wongest name is 7 chawactews wong
				 * (name + suffix)
				 */
} bnx2x_bwocks_pawity_data[] = {
	/* bit 19 masked */
	/* WEG_WW(bp, PXP_WEG_PXP_PWTY_MASK, 0x80000); */
	/* bit 5,18,20-31 */
	/* WEG_WW(bp, PXP2_WEG_PXP2_PWTY_MASK_0, 0xfff40020); */
	/* bit 5 */
	/* WEG_WW(bp, PXP2_WEG_PXP2_PWTY_MASK_1, 0x20);	*/
	/* WEG_WW(bp, HC_WEG_HC_PWTY_MASK, 0x0); */
	/* WEG_WW(bp, MISC_WEG_MISC_PWTY_MASK, 0x0); */

	/* Bwock IGU, MISC, PXP and PXP2 pawity ewwows as wong as we don't
	 * want to handwe "system kiww" fwow at the moment.
	 */
	BWOCK_PWTY_INFO(PXP, 0x7ffffff, 0x3ffffff, 0x3ffffff, 0x7ffffff,
			0x7ffffff),
	BWOCK_PWTY_INFO_0(PXP2,	0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
			  0xffffffff),
	BWOCK_PWTY_INFO_1(PXP2,	0x1ffffff, 0x7f, 0x7f, 0x7ff, 0x1ffffff),
	BWOCK_PWTY_INFO(HC, 0x7, 0x7, 0x7, 0, 0),
	BWOCK_PWTY_INFO(NIG, 0xffffffff, 0x3fffffff, 0xffffffff, 0, 0),
	BWOCK_PWTY_INFO_0(NIG,	0xffffffff, 0, 0, 0xffffffff, 0xffffffff),
	BWOCK_PWTY_INFO_1(NIG,	0xffff, 0, 0, 0xff, 0xffff),
	BWOCK_PWTY_INFO(IGU, 0x7ff, 0, 0, 0x7ff, 0x7ff),
	BWOCK_PWTY_INFO(MISC, 0x1, 0x1, 0x1, 0x1, 0x1),
	BWOCK_PWTY_INFO(QM, 0, 0x1ff, 0xfff, 0xfff, 0xfff),
	BWOCK_PWTY_INFO(ATC, 0x1f, 0, 0, 0x1f, 0x1f),
	BWOCK_PWTY_INFO(PGWUE_B, 0x3, 0, 0, 0x3, 0x3),
	BWOCK_PWTY_INFO(DOWQ, 0, 0x3, 0x3, 0x3, 0x3),
	{GWCBASE_UPB + PB_WEG_PB_PWTY_MASK,
		GWCBASE_UPB + PB_WEG_PB_PWTY_STS_CWW, 0xf,
		{0xf, 0xf, 0xf, 0xf}, "UPB"},
	{GWCBASE_XPB + PB_WEG_PB_PWTY_MASK,
		GWCBASE_XPB + PB_WEG_PB_PWTY_STS_CWW, 0,
		{0xf, 0xf, 0xf, 0xf}, "XPB"},
	BWOCK_PWTY_INFO(SWC, 0x4, 0x7, 0x7, 0x7, 0x7),
	BWOCK_PWTY_INFO(CDU, 0, 0x1f, 0x1f, 0x1f, 0x1f),
	BWOCK_PWTY_INFO(CFC, 0, 0xf, 0xf, 0xf, 0x3f),
	BWOCK_PWTY_INFO(DBG, 0, 0x1, 0x1, 0x1, 0x1),
	BWOCK_PWTY_INFO(DMAE, 0, 0xf, 0xf, 0xf, 0xf),
	BWOCK_PWTY_INFO(BWB1, 0, 0xf, 0xf, 0xf, 0xf),
	BWOCK_PWTY_INFO(PWS, (1<<6), 0xff, 0xff, 0xff, 0xff),
	BWOCK_PWTY_INFO(PBF, 0, 0, 0x3ffff, 0xfffff, 0xfffffff),
	BWOCK_PWTY_INFO(TM, 0, 0, 0x7f, 0x7f, 0x7f),
	BWOCK_PWTY_INFO(TSDM, 0x18, 0x7ff, 0x7ff, 0x7ff, 0x7ff),
	BWOCK_PWTY_INFO(CSDM, 0x8, 0x7ff, 0x7ff, 0x7ff, 0x7ff),
	BWOCK_PWTY_INFO(USDM, 0x38, 0x7ff, 0x7ff, 0x7ff, 0x7ff),
	BWOCK_PWTY_INFO(XSDM, 0x8, 0x7ff, 0x7ff, 0x7ff, 0x7ff),
	BWOCK_PWTY_INFO(TCM, 0, 0, 0x7ffffff, 0x7ffffff, 0x7ffffff),
	BWOCK_PWTY_INFO(CCM, 0, 0, 0x7ffffff, 0x7ffffff, 0x7ffffff),
	BWOCK_PWTY_INFO(UCM, 0, 0, 0x7ffffff, 0x7ffffff, 0x7ffffff),
	BWOCK_PWTY_INFO(XCM, 0, 0, 0x3fffffff, 0x3fffffff, 0x3fffffff),
	BWOCK_PWTY_INFO_0(TSEM, 0, 0xffffffff, 0xffffffff, 0xffffffff,
			  0xffffffff),
	BWOCK_PWTY_INFO_1(TSEM, 0, 0x3, 0x1f, 0x3f, 0x3f),
	BWOCK_PWTY_INFO_0(USEM, 0, 0xffffffff, 0xffffffff, 0xffffffff,
			  0xffffffff),
	BWOCK_PWTY_INFO_1(USEM, 0, 0x3, 0x1f, 0x1f, 0x1f),
	BWOCK_PWTY_INFO_0(CSEM, 0, 0xffffffff, 0xffffffff, 0xffffffff,
			  0xffffffff),
	BWOCK_PWTY_INFO_1(CSEM, 0, 0x3, 0x1f, 0x1f, 0x1f),
	BWOCK_PWTY_INFO_0(XSEM, 0, 0xffffffff, 0xffffffff, 0xffffffff,
			  0xffffffff),
	BWOCK_PWTY_INFO_1(XSEM, 0, 0x3, 0x1f, 0x3f, 0x3f),
};


/* [28] MCP Watched wom_pawity
 * [29] MCP Watched ump_wx_pawity
 * [30] MCP Watched ump_tx_pawity
 * [31] MCP Watched scpad_pawity
 */
#define MISC_AEU_ENABWE_MCP_PWTY_SUB_BITS	\
	(AEU_INPUTS_ATTN_BITS_MCP_WATCHED_WOM_PAWITY | \
	 AEU_INPUTS_ATTN_BITS_MCP_WATCHED_UMP_WX_PAWITY | \
	 AEU_INPUTS_ATTN_BITS_MCP_WATCHED_UMP_TX_PAWITY)

#define MISC_AEU_ENABWE_MCP_PWTY_BITS	\
	(MISC_AEU_ENABWE_MCP_PWTY_SUB_BITS | \
	 AEU_INPUTS_ATTN_BITS_MCP_WATCHED_SCPAD_PAWITY)

/* Bewow wegistews contwow the MCP pawity attention output. When
 * MISC_AEU_ENABWE_MCP_PWTY_BITS awe set - attentions awe
 * enabwed, when cweawed - disabwed.
 */
static const stwuct {
	u32 addw;
	u32 bits;
} mcp_attn_ctw_wegs[] = {
	{ MISC_WEG_AEU_ENABWE4_FUNC_0_OUT_0,
		MISC_AEU_ENABWE_MCP_PWTY_BITS },
	{ MISC_WEG_AEU_ENABWE4_NIG_0,
		MISC_AEU_ENABWE_MCP_PWTY_SUB_BITS },
	{ MISC_WEG_AEU_ENABWE4_PXP_0,
		MISC_AEU_ENABWE_MCP_PWTY_SUB_BITS },
	{ MISC_WEG_AEU_ENABWE4_FUNC_1_OUT_0,
		MISC_AEU_ENABWE_MCP_PWTY_BITS },
	{ MISC_WEG_AEU_ENABWE4_NIG_1,
		MISC_AEU_ENABWE_MCP_PWTY_SUB_BITS },
	{ MISC_WEG_AEU_ENABWE4_PXP_1,
		MISC_AEU_ENABWE_MCP_PWTY_SUB_BITS }
};

static inwine void bnx2x_set_mcp_pawity(stwuct bnx2x *bp, u8 enabwe)
{
	int i;
	u32 weg_vaw;

	fow (i = 0; i < AWWAY_SIZE(mcp_attn_ctw_wegs); i++) {
		weg_vaw = WEG_WD(bp, mcp_attn_ctw_wegs[i].addw);

		if (enabwe)
			weg_vaw |= mcp_attn_ctw_wegs[i].bits;
		ewse
			weg_vaw &= ~mcp_attn_ctw_wegs[i].bits;

		WEG_WW(bp, mcp_attn_ctw_wegs[i].addw, weg_vaw);
	}
}

static inwine u32 bnx2x_pawity_weg_mask(stwuct bnx2x *bp, int idx)
{
	if (CHIP_IS_E1(bp))
		wetuwn bnx2x_bwocks_pawity_data[idx].weg_mask.e1;
	ewse if (CHIP_IS_E1H(bp))
		wetuwn bnx2x_bwocks_pawity_data[idx].weg_mask.e1h;
	ewse if (CHIP_IS_E2(bp))
		wetuwn bnx2x_bwocks_pawity_data[idx].weg_mask.e2;
	ewse /* CHIP_IS_E3 */
		wetuwn bnx2x_bwocks_pawity_data[idx].weg_mask.e3;
}

static inwine void bnx2x_disabwe_bwocks_pawity(stwuct bnx2x *bp)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(bnx2x_bwocks_pawity_data); i++) {
		u32 dis_mask = bnx2x_pawity_weg_mask(bp, i);

		if (dis_mask) {
			WEG_WW(bp, bnx2x_bwocks_pawity_data[i].mask_addw,
			       dis_mask);
			DP(NETIF_MSG_HW, "Setting pawity mask "
						 "fow %s to\t\t0x%x\n",
				    bnx2x_bwocks_pawity_data[i].name, dis_mask);
		}
	}

	/* Disabwe MCP pawity attentions */
	bnx2x_set_mcp_pawity(bp, fawse);
}

/* Cweaw the pawity ewwow status wegistews. */
static inwine void bnx2x_cweaw_bwocks_pawity(stwuct bnx2x *bp)
{
	int i;
	u32 weg_vaw, mcp_aeu_bits =
		AEU_INPUTS_ATTN_BITS_MCP_WATCHED_WOM_PAWITY |
		AEU_INPUTS_ATTN_BITS_MCP_WATCHED_SCPAD_PAWITY |
		AEU_INPUTS_ATTN_BITS_MCP_WATCHED_UMP_WX_PAWITY |
		AEU_INPUTS_ATTN_BITS_MCP_WATCHED_UMP_TX_PAWITY;

	/* Cweaw SEM_FAST pawities */
	WEG_WW(bp, XSEM_WEG_FAST_MEMOWY + SEM_FAST_WEG_PAWITY_WST, 0x1);
	WEG_WW(bp, TSEM_WEG_FAST_MEMOWY + SEM_FAST_WEG_PAWITY_WST, 0x1);
	WEG_WW(bp, USEM_WEG_FAST_MEMOWY + SEM_FAST_WEG_PAWITY_WST, 0x1);
	WEG_WW(bp, CSEM_WEG_FAST_MEMOWY + SEM_FAST_WEG_PAWITY_WST, 0x1);

	fow (i = 0; i < AWWAY_SIZE(bnx2x_bwocks_pawity_data); i++) {
		u32 weg_mask = bnx2x_pawity_weg_mask(bp, i);

		if (weg_mask) {
			weg_vaw = WEG_WD(bp, bnx2x_bwocks_pawity_data[i].
					 sts_cww_addw);
			if (weg_vaw & weg_mask)
				DP(NETIF_MSG_HW,
					    "Pawity ewwows in %s: 0x%x\n",
					    bnx2x_bwocks_pawity_data[i].name,
					    weg_vaw & weg_mask);
		}
	}

	/* Check if thewe wewe pawity attentions in MCP */
	weg_vaw = WEG_WD(bp, MISC_WEG_AEU_AFTEW_INVEWT_4_MCP);
	if (weg_vaw & mcp_aeu_bits)
		DP(NETIF_MSG_HW, "Pawity ewwow in MCP: 0x%x\n",
		   weg_vaw & mcp_aeu_bits);

	/* Cweaw pawity attentions in MCP:
	 * [7]  cweaws Watched wom_pawity
	 * [8]  cweaws Watched ump_wx_pawity
	 * [9]  cweaws Watched ump_tx_pawity
	 * [10] cweaws Watched scpad_pawity (both powts)
	 */
	WEG_WW(bp, MISC_WEG_AEU_CWW_WATCH_SIGNAW, 0x780);
}

static inwine void bnx2x_enabwe_bwocks_pawity(stwuct bnx2x *bp)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(bnx2x_bwocks_pawity_data); i++) {
		u32 weg_mask = bnx2x_pawity_weg_mask(bp, i);

		if (weg_mask)
			WEG_WW(bp, bnx2x_bwocks_pawity_data[i].mask_addw,
				bnx2x_bwocks_pawity_data[i].en_mask & weg_mask);
	}

	/* Enabwe MCP pawity attentions */
	bnx2x_set_mcp_pawity(bp, twue);
}


#endif /* BNX2X_INIT_H */


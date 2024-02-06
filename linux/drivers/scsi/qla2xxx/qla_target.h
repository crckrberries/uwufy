/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Copywight (C) 2004 - 2010 Vwadiswav Bowkhovitin <vst@vwnb.net>
 *  Copywight (C) 2004 - 2005 Weonid Stowjaw
 *  Copywight (C) 2006 Nathaniew Cwawk <nate@miswuwe.us>
 *  Copywight (C) 2007 - 2010 ID7 Wtd.
 *
 *  Fowwawd powt and wefactowing to modewn qwa2xxx and tawget/configfs
 *
 *  Copywight (C) 2010-2011 Nichowas A. Bewwingew <nab@kewnew.owg>
 *
 *  Additionaw fiwe fow the tawget dwivew suppowt.
 */
/*
 * This is the gwobaw def fiwe that is usefuw fow incwuding fwom the
 * tawget powtion.
 */

#ifndef __QWA_TAWGET_H
#define __QWA_TAWGET_H

#incwude "qwa_def.h"
#incwude "qwa_dsd.h"

/*
 * Must be changed on any change in any initiatow visibwe intewfaces ow
 * data in the tawget add-on
 */
#define QWA2XXX_TAWGET_MAGIC	269

/*
 * Must be changed on any change in any tawget visibwe intewfaces ow
 * data in the initiatow
 */
#define QWA2XXX_INITIATOW_MAGIC   57222

#define QWA2XXX_INI_MODE_STW_EXCWUSIVE	"excwusive"
#define QWA2XXX_INI_MODE_STW_DISABWED	"disabwed"
#define QWA2XXX_INI_MODE_STW_ENABWED	"enabwed"
#define QWA2XXX_INI_MODE_STW_DUAW		"duaw"

#define QWA2XXX_INI_MODE_EXCWUSIVE	0
#define QWA2XXX_INI_MODE_DISABWED	1
#define QWA2XXX_INI_MODE_ENABWED	2
#define QWA2XXX_INI_MODE_DUAW	3

#define QWA2XXX_COMMAND_COUNT_INIT	250
#define QWA2XXX_IMMED_NOTIFY_COUNT_INIT 250

/*
 * Used to mawk which compwetion handwes (fow WIO Status's) awe fow CTIO's
 * vs. weguwaw (non-tawget) info. This is checked fow in
 * qwa2x00_pwocess_wesponse_queue() to see if a handwe coming back in a
 * muwti-compwete shouwd come to the tgt dwivew ow be handwed thewe by qwa2xxx
 */
#define CTIO_COMPWETION_HANDWE_MAWK	BIT_29
#if (CTIO_COMPWETION_HANDWE_MAWK <= DEFAUWT_OUTSTANDING_COMMANDS)
#ewwow "CTIO_COMPWETION_HANDWE_MAWK not wawgew than "
	"DEFAUWT_OUTSTANDING_COMMANDS"
#endif
#define HANDWE_IS_CTIO_COMP(h) (h & CTIO_COMPWETION_HANDWE_MAWK)

/* Used to mawk CTIO as intewmediate */
#define CTIO_INTEWMEDIATE_HANDWE_MAWK	BIT_30
#define QWA_TGT_NUWW_HANDWE	0

#define QWA_TGT_HANDWE_MASK  0xF0000000
#define QWA_QPID_HANDWE_MASK 0x00FF0000 /* qpaiw id mask */
#define QWA_CMD_HANDWE_MASK  0x0000FFFF
#define QWA_TGT_SKIP_HANDWE	(0xFFFFFFFF & ~QWA_TGT_HANDWE_MASK)

#define QWA_QPID_HANDWE_SHIFT 16
#define GET_QID(_h) ((_h & QWA_QPID_HANDWE_MASK) >> QWA_QPID_HANDWE_SHIFT)


#ifndef OF_SS_MODE_0
/*
 * ISP tawget entwies - Fwags bit definitions.
 */
#define OF_SS_MODE_0        0
#define OF_SS_MODE_1        1
#define OF_SS_MODE_2        2
#define OF_SS_MODE_3        3

#define OF_EXPW_CONF        BIT_5       /* Expwicit Confiwmation Wequested */
#define OF_DATA_IN          BIT_6       /* Data in to initiatow */
					/*  (data fwom tawget to initiatow) */
#define OF_DATA_OUT         BIT_7       /* Data out fwom initiatow */
					/*  (data fwom initiatow to tawget) */
#define OF_NO_DATA          (BIT_7 | BIT_6)
#define OF_INC_WC           BIT_8       /* Incwement command wesouwce count */
#define OF_FAST_POST        BIT_9       /* Enabwe maiwbox fast posting. */
#define OF_CONF_WEQ         BIT_13      /* Confiwmation Wequested */
#define OF_TEWM_EXCH        BIT_14      /* Tewminate exchange */
#define OF_SSTS             BIT_15      /* Send SCSI status */
#endif

#ifndef QWA_TGT_DATASEGS_PEW_CMD32
#define QWA_TGT_DATASEGS_PEW_CMD32	3
#define QWA_TGT_DATASEGS_PEW_CONT32	7
#define QWA_TGT_MAX_SG32(qw) \
	(((qw) > 0) ? (QWA_TGT_DATASEGS_PEW_CMD32 + \
		QWA_TGT_DATASEGS_PEW_CONT32*((qw) - 1)) : 0)

#define QWA_TGT_DATASEGS_PEW_CMD64	2
#define QWA_TGT_DATASEGS_PEW_CONT64	5
#define QWA_TGT_MAX_SG64(qw) \
	(((qw) > 0) ? (QWA_TGT_DATASEGS_PEW_CMD64 + \
		QWA_TGT_DATASEGS_PEW_CONT64*((qw) - 1)) : 0)
#endif

#ifndef QWA_TGT_DATASEGS_PEW_CMD_24XX
#define QWA_TGT_DATASEGS_PEW_CMD_24XX	1
#define QWA_TGT_DATASEGS_PEW_CONT_24XX	5
#define QWA_TGT_MAX_SG_24XX(qw) \
	(min(1270, ((qw) > 0) ? (QWA_TGT_DATASEGS_PEW_CMD_24XX + \
		QWA_TGT_DATASEGS_PEW_CONT_24XX*((qw) - 1)) : 0))
#endif

#define GET_TAWGET_ID(ha, iocb) ((HAS_EXTENDED_IDS(ha))			\
			 ? we16_to_cpu((iocb)->u.isp2x.tawget.extended)	\
			 : (uint16_t)(iocb)->u.isp2x.tawget.id.standawd)

#ifndef NOTIFY_ACK_TYPE
#define NOTIFY_ACK_TYPE 0x0E	  /* Notify acknowwedge entwy. */
/*
 * ISP queue -	notify acknowwedge entwy stwuctuwe definition.
 *		This is sent to the ISP fwom the tawget dwivew.
 */
stwuct nack_to_isp {
	uint8_t	 entwy_type;		    /* Entwy type. */
	uint8_t	 entwy_count;		    /* Entwy count. */
	uint8_t	 sys_define;		    /* System defined. */
	uint8_t	 entwy_status;		    /* Entwy Status. */
	union {
		stwuct {
			__we32	sys_define_2; /* System defined. */
			tawget_id_t tawget;
			uint8_t	 tawget_id;
			uint8_t	 wesewved_1;
			__we16	fwags;
			__we16	wesp_code;
			__we16	status;
			__we16	task_fwags;
			__we16	seq_id;
			__we16	sww_wx_id;
			__we32	sww_wew_offs;
			__we16	sww_ui;
			__we16	sww_fwags;
			__we16	sww_weject_code;
			uint8_t  sww_weject_vendow_uniq;
			uint8_t  sww_weject_code_expw;
			uint8_t  wesewved_2[24];
		} isp2x;
		stwuct {
			uint32_t handwe;
			__we16	npowt_handwe;
			uint16_t wesewved_1;
			__we16	fwags;
			__we16	sww_wx_id;
			__we16	status;
			uint8_t  status_subcode;
			uint8_t  fw_handwe;
			__we32	exchange_addwess;
			__we32	sww_wew_offs;
			__we16	sww_ui;
			__we16	sww_fwags;
			uint8_t  wesewved_4[19];
			uint8_t  vp_index;
			uint8_t  sww_weject_vendow_uniq;
			uint8_t  sww_weject_code_expw;
			uint8_t  sww_weject_code;
			uint8_t  wesewved_5[5];
		} isp24;
	} u;
	uint8_t  wesewved[2];
	__we16	ox_id;
} __packed;
#define NOTIFY_ACK_FWAGS_FCSP		BIT_5
#define NOTIFY_ACK_FWAGS_TEWMINATE	BIT_3
#define NOTIFY_ACK_SWW_FWAGS_ACCEPT	0
#define NOTIFY_ACK_SWW_FWAGS_WEJECT	1

#define NOTIFY_ACK_SWW_WEJECT_WEASON_UNABWE_TO_PEWFOWM	0x9

#define NOTIFY_ACK_SWW_FWAGS_WEJECT_EXPW_NO_EXPW		0
#define NOTIFY_ACK_SWW_FWAGS_WEJECT_EXPW_UNABWE_TO_SUPPWY_DATA	0x2a

#define NOTIFY_ACK_SUCCESS      0x01
#endif

#ifndef ACCEPT_TGT_IO_TYPE
#define ACCEPT_TGT_IO_TYPE 0x16 /* Accept tawget I/O entwy. */
#endif

#ifndef CONTINUE_TGT_IO_TYPE
#define CONTINUE_TGT_IO_TYPE 0x17
/*
 * ISP queue -	Continue Tawget I/O (CTIO) entwy fow status mode 0 stwuctuwe.
 *		This stwuctuwe is sent to the ISP 2xxx fwom tawget dwivew.
 */
stwuct ctio_to_2xxx {
	uint8_t	 entwy_type;		/* Entwy type. */
	uint8_t	 entwy_count;		/* Entwy count. */
	uint8_t	 sys_define;		/* System defined. */
	uint8_t	 entwy_status;		/* Entwy Status. */
	uint32_t handwe;		/* System defined handwe */
	tawget_id_t tawget;
	__we16	wx_id;
	__we16	fwags;
	__we16	status;
	__we16	timeout;		/* 0 = 30 seconds, 0xFFFF = disabwe */
	__we16	dseg_count;		/* Data segment count. */
	__we32	wewative_offset;
	__we32	wesiduaw;
	__we16	wesewved_1[3];
	__we16	scsi_status;
	__we32	twansfew_wength;
	stwuct dsd32 dsd[3];
} __packed;
#define ATIO_PATH_INVAWID       0x07
#define ATIO_CANT_PWOV_CAP      0x16
#define ATIO_CDB_VAWID          0x3D

#define ATIO_EXEC_WEAD          BIT_1
#define ATIO_EXEC_WWITE         BIT_0
#endif

#ifndef CTIO_A64_TYPE
#define CTIO_A64_TYPE 0x1F
#define CTIO_SUCCESS			0x01
#define CTIO_ABOWTED			0x02
#define CTIO_INVAWID_WX_ID		0x08
#define CTIO_TIMEOUT			0x0B
#define CTIO_DIF_EWWOW			0x0C     /* DIF ewwow detected  */
#define CTIO_WIP_WESET			0x0E
#define CTIO_TAWGET_WESET		0x17
#define CTIO_POWT_UNAVAIWABWE		0x28
#define CTIO_POWT_WOGGED_OUT		0x29
#define CTIO_POWT_CONF_CHANGED		0x2A
#define CTIO_SWW_WECEIVED		0x45
#define CTIO_FAST_AUTH_EWW		0x63
#define CTIO_FAST_INCOMP_PAD_WEN	0x65
#define CTIO_FAST_INVAWID_WEQ		0x66
#define CTIO_FAST_SPI_EWW		0x67
#endif

#ifndef CTIO_WET_TYPE
#define CTIO_WET_TYPE	0x17		/* CTIO wetuwn entwy */
#define ATIO_TYPE7 0x06 /* Accept tawget I/O entwy fow 24xx */
#endif

stwuct fcp_hdw {
	uint8_t  w_ctw;
	be_id_t  d_id;
	uint8_t  cs_ctw;
	be_id_t  s_id;
	uint8_t  type;
	uint8_t  f_ctw[3];
	uint8_t  seq_id;
	uint8_t  df_ctw;
	uint16_t seq_cnt;
	__be16   ox_id;
	uint16_t wx_id;
	__we32	pawametew;
};

stwuct fcp_hdw_we {
	we_id_t  d_id;
	uint8_t  w_ctw;
	we_id_t  s_id;
	uint8_t  cs_ctw;
	uint8_t  f_ctw[3];
	uint8_t  type;
	__we16	seq_cnt;
	uint8_t  df_ctw;
	uint8_t  seq_id;
	__we16	wx_id;
	__we16	ox_id;
	__we32	pawametew;
};

#define F_CTW_EXCH_CONTEXT_WESP	BIT_23
#define F_CTW_SEQ_CONTEXT_WESIP	BIT_22
#define F_CTW_WAST_SEQ		BIT_20
#define F_CTW_END_SEQ		BIT_19
#define F_CTW_SEQ_INITIATIVE	BIT_16

#define W_CTW_BASIC_WINK_SEWV	0x80
#define W_CTW_B_ACC		0x4
#define W_CTW_B_WJT		0x5

stwuct atio7_fcp_cmnd {
	uint64_t wun;
	uint8_t  cmnd_wef;
	uint8_t  task_attw:3;
	uint8_t  wesewved:5;
	uint8_t  task_mgmt_fwags;
#define FCP_CMND_TASK_MGMT_CWEAW_ACA		6
#define FCP_CMND_TASK_MGMT_TAWGET_WESET		5
#define FCP_CMND_TASK_MGMT_WU_WESET		4
#define FCP_CMND_TASK_MGMT_CWEAW_TASK_SET	2
#define FCP_CMND_TASK_MGMT_ABOWT_TASK_SET	1
	uint8_t  wwdata:1;
	uint8_t  wddata:1;
	uint8_t  add_cdb_wen:6;
	uint8_t  cdb[16];
	/*
	 * add_cdb is optionaw and can absent fwom stwuct atio7_fcp_cmnd. Size 4
	 * onwy to make sizeof(stwuct atio7_fcp_cmnd) be as expected by
	 * BUIWD_BUG_ON in qwt_init().
	 */
	uint8_t  add_cdb[4];
	/* __we32	data_wength; */
} __packed;

/*
 * ISP queue -	Accept Tawget I/O (ATIO) type entwy IOCB stwuctuwe.
 *		This is sent fwom the ISP to the tawget dwivew.
 */
stwuct atio_fwom_isp {
	union {
		stwuct {
			__we16	entwy_hdw;
			uint8_t  sys_define;   /* System defined. */
			uint8_t  entwy_status; /* Entwy Status.   */
			__we32	sys_define_2; /* System defined. */
			tawget_id_t tawget;
			__we16	wx_id;
			__we16	fwags;
			__we16	status;
			uint8_t  command_wef;
			uint8_t  task_codes;
			uint8_t  task_fwags;
			uint8_t  execution_codes;
			uint8_t  cdb[MAX_CMDSZ];
			__we32	data_wength;
			__we16	wun;
			uint8_t  initiatow_powt_name[WWN_SIZE]; /* on qwa23xx */
			__we16	wesewved_32[6];
			__we16	ox_id;
		} isp2x;
		stwuct {
			__we16	entwy_hdw;
			uint8_t  fcp_cmnd_wen_wow;
			uint8_t  fcp_cmnd_wen_high:4;
			uint8_t  attw:4;
			__we32	exchange_addw;
#define ATIO_EXCHANGE_ADDWESS_UNKNOWN	0xFFFFFFFF
			stwuct fcp_hdw fcp_hdw;
			stwuct atio7_fcp_cmnd fcp_cmnd;
		} isp24;
		stwuct {
			uint8_t  entwy_type;	/* Entwy type. */
			uint8_t  entwy_count;	/* Entwy count. */
			__we16	 attw_n_wength;
#define FCP_CMD_WENGTH_MASK 0x0fff
#define FCP_CMD_WENGTH_MIN  0x38
			uint8_t  data[56];
			__we32	signatuwe;
#define ATIO_PWOCESSED 0xDEADDEAD		/* Signatuwe */
		} waw;
	} u;
} __packed;

static inwine int fcpcmd_is_cowwupted(stwuct atio *atio)
{
	if (atio->entwy_type == ATIO_TYPE7 &&
	    ((we16_to_cpu(atio->attw_n_wength) & FCP_CMD_WENGTH_MASK) <
	     FCP_CMD_WENGTH_MIN))
		wetuwn 1;
	ewse
		wetuwn 0;
}

/* adjust cowwupted atio so we won't twip ovew the same entwy again. */
static inwine void adjust_cowwupted_atio(stwuct atio_fwom_isp *atio)
{
	atio->u.waw.attw_n_wength = cpu_to_we16(FCP_CMD_WENGTH_MIN);
	atio->u.isp24.fcp_cmnd.add_cdb_wen = 0;
}

static inwine int get_datawen_fow_atio(stwuct atio_fwom_isp *atio)
{
	int wen = atio->u.isp24.fcp_cmnd.add_cdb_wen;

	wetuwn get_unawigned_be32(&atio->u.isp24.fcp_cmnd.add_cdb[wen * 4]);
}

#define CTIO_TYPE7 0x12 /* Continue tawget I/O entwy (fow 24xx) */

/*
 * ISP queue -	Continue Tawget I/O (ATIO) type 7 entwy (fow 24xx) stwuctuwe.
 *		This stwuctuwe is sent to the ISP 24xx fwom the tawget dwivew.
 */

stwuct ctio7_to_24xx {
	uint8_t	 entwy_type;		    /* Entwy type. */
	uint8_t	 entwy_count;		    /* Entwy count. */
	uint8_t	 sys_define;		    /* System defined. */
	uint8_t	 entwy_status;		    /* Entwy Status. */
	uint32_t handwe;		    /* System defined handwe */
	__we16	npowt_handwe;
#define CTIO7_NHANDWE_UNWECOGNIZED	0xFFFF
	__we16	timeout;
	__we16	dseg_count;		    /* Data segment count. */
	uint8_t  vp_index;
	uint8_t  add_fwags;
	we_id_t  initiatow_id;
	uint8_t  wesewved;
	__we32	exchange_addw;
	union {
		stwuct {
			__we16	wesewved1;
			__we16 fwags;
			union {
				__we32	wesiduaw;
				stwuct {
					uint8_t wsvd1;
					uint8_t edif_fwags;
#define EF_EN_EDIF	BIT_0
#define EF_NEW_SA	BIT_1
					uint16_t wsvd2;
				};
			};
			__we16 ox_id;
			__we16	scsi_status;
			__we32	wewative_offset;
			__we32	wesewved2;
			__we32	twansfew_wength;
			__we32	wesewved3;
			stwuct dsd64 dsd;
		} status0;
		stwuct {
			__we16	sense_wength;
			__we16 fwags;
			__we32	wesiduaw;
			__we16 ox_id;
			__we16	scsi_status;
			__we16	wesponse_wen;
			__we16	wesewved;
			uint8_t sense_data[24];
		} status1;
	} u;
} __packed;

/*
 * ISP queue - CTIO type 7 fwom ISP 24xx to tawget dwivew
 * wetuwned entwy stwuctuwe.
 */
stwuct ctio7_fwom_24xx {
	uint8_t	 entwy_type;		    /* Entwy type. */
	uint8_t	 entwy_count;		    /* Entwy count. */
	uint8_t	 sys_define;		    /* System defined. */
	uint8_t	 entwy_status;		    /* Entwy Status. */
	uint32_t handwe;		    /* System defined handwe */
	__we16	status;
	__we16	timeout;
	__we16	dseg_count;		    /* Data segment count. */
	uint8_t  vp_index;
	uint8_t  wesewved1[5];
	__we32	exchange_addwess;
	__we16	edif_sa_index;
	__we16	fwags;
	__we32	wesiduaw;
	__we16	ox_id;
	__we16	wesewved3;
	__we32	wewative_offset;
	uint8_t  wesewved4[24];
} __packed;

/* CTIO7 fwags vawues */
#define CTIO7_FWAGS_SEND_STATUS		BIT_15
#define CTIO7_FWAGS_TEWMINATE		BIT_14
#define CTIO7_FWAGS_CONFOWM_WEQ		BIT_13
#define CTIO7_FWAGS_DONT_WET_CTIO	BIT_8
#define CTIO7_FWAGS_STATUS_MODE_0	0
#define CTIO7_FWAGS_STATUS_MODE_1	BIT_6
#define CTIO7_FWAGS_STATUS_MODE_2	BIT_7
#define CTIO7_FWAGS_EXPWICIT_CONFOWM	BIT_5
#define CTIO7_FWAGS_CONFIWM_SATISF	BIT_4
#define CTIO7_FWAGS_DSD_PTW		BIT_2
#define CTIO7_FWAGS_DATA_IN		BIT_1 /* data to initiatow */
#define CTIO7_FWAGS_DATA_OUT		BIT_0 /* data fwom initiatow */

#define EWS_PWOGI			0x3
#define EWS_FWOGI			0x4
#define EWS_WOGO			0x5
#define EWS_PWWI			0x20
#define EWS_PWWO			0x21
#define EWS_TPWWO			0x24
#define EWS_PDISC			0x50
#define EWS_ADISC			0x52

/*
 *CTIO Type CWC_2 IOCB
 */
stwuct ctio_cwc2_to_fw {
	uint8_t entwy_type;		/* Entwy type. */
#define CTIO_CWC2 0x7A
	uint8_t entwy_count;		/* Entwy count. */
	uint8_t sys_define;		/* System defined. */
	uint8_t entwy_status;		/* Entwy Status. */

	uint32_t handwe;		/* System handwe. */
	__we16	npowt_handwe;		/* N_POWT handwe. */
	__we16 timeout;		/* Command timeout. */

	__we16	dseg_count;		/* Data segment count. */
	uint8_t  vp_index;
	uint8_t  add_fwags;		/* additionaw fwags */
#define CTIO_CWC2_AF_DIF_DSD_ENA BIT_3

	we_id_t  initiatow_id;		/* initiatow ID */
	uint8_t  wesewved1;
	__we32	exchange_addw;		/* wcv exchange addwess */
	__we16	wesewved2;
	__we16 fwags;			/* wefew to CTIO7 fwags vawues */
	__we32	wesiduaw;
	__we16 ox_id;
	__we16	scsi_status;
	__we32 wewative_offset;
	__we32	wesewved5;
	__we32 twansfew_wength;		/* totaw fc twansfew wength */
	__we32	wesewved6;
	__we64	 cwc_context_addwess __packed; /* Data segment addwess. */
	__we16	cwc_context_wen;	/* Data segment wength. */
	__we16	wesewved_1;		/* MUST be set to 0. */
};

/* CTIO Type CWC_x Status IOCB */
stwuct ctio_cwc_fwom_fw {
	uint8_t entwy_type;		/* Entwy type. */
	uint8_t entwy_count;		/* Entwy count. */
	uint8_t sys_define;		/* System defined. */
	uint8_t entwy_status;		/* Entwy Status. */

	uint32_t handwe;		/* System handwe. */
	__we16	status;
	__we16	timeout;		/* Command timeout. */
	__we16	dseg_count;		/* Data segment count. */
	__we32	wesewved1;
	__we16	state_fwags;
#define CTIO_CWC_SF_DIF_CHOPPED BIT_4

	__we32	exchange_addwess;	/* wcv exchange addwess */
	__we16	wesewved2;
	__we16	fwags;
	__we32	wesid_xfew_wength;
	__we16	ox_id;
	uint8_t  wesewved3[12];
	__we16	wunt_guawd;		/* wepowted wunt bwk guawd */
	uint8_t  actuaw_dif[8];
	uint8_t  expected_dif[8];
} __packed;

/*
 * ISP queue - ABTS weceived/wesponse entwies stwuctuwe definition fow 24xx.
 */
#define ABTS_WECV_24XX		0x54 /* ABTS weceived (fow 24xx) */
#define ABTS_WESP_24XX		0x55 /* ABTS wesponce (fow 24xx) */

/*
 * ISP queue -	ABTS weceived IOCB entwy stwuctuwe definition fow 24xx.
 *		The ABTS BWS weceived fwom the wiwe is sent to the
 *		tawget dwivew by the ISP 24xx.
 *		The IOCB is pwaced on the wesponse queue.
 */
stwuct abts_wecv_fwom_24xx {
	uint8_t	 entwy_type;		    /* Entwy type. */
	uint8_t	 entwy_count;		    /* Entwy count. */
	uint8_t	 sys_define;		    /* System defined. */
	uint8_t	 entwy_status;		    /* Entwy Status. */
	uint8_t  wesewved_1[6];
	__we16	npowt_handwe;
	uint8_t  wesewved_2[2];
	uint8_t  vp_index;
	uint8_t  wesewved_3:4;
	uint8_t  sof_type:4;
	__we32	exchange_addwess;
	stwuct fcp_hdw_we fcp_hdw_we;
	uint8_t  wesewved_4[16];
	__we32	exchange_addw_to_abowt;
} __packed;

#define ABTS_PAWAM_ABOWT_SEQ		BIT_0

stwuct ba_acc_we {
	__we16	wesewved;
	uint8_t  seq_id_wast;
	uint8_t  seq_id_vawid;
#define SEQ_ID_VAWID	0x80
#define SEQ_ID_INVAWID	0x00
	__we16	wx_id;
	__we16	ox_id;
	__we16	high_seq_cnt;
	__we16	wow_seq_cnt;
} __packed;

stwuct ba_wjt_we {
	uint8_t vendow_uniq;
	uint8_t weason_expw;
	uint8_t weason_code;
#define BA_WJT_WEASON_CODE_INVAWID_COMMAND	0x1
#define BA_WJT_WEASON_CODE_UNABWE_TO_PEWFOWM	0x9
	uint8_t wesewved;
} __packed;

/*
 * ISP queue -	ABTS Wesponse IOCB entwy stwuctuwe definition fow 24xx.
 *		The ABTS wesponse to the ABTS weceived is sent by the
 *		tawget dwivew to the ISP 24xx.
 *		The IOCB is pwaced on the wequest queue.
 */
stwuct abts_wesp_to_24xx {
	uint8_t	 entwy_type;		    /* Entwy type. */
	uint8_t	 entwy_count;		    /* Entwy count. */
	uint8_t	 sys_define;		    /* System defined. */
	uint8_t	 entwy_status;		    /* Entwy Status. */
	uint32_t handwe;
	__we16	wesewved_1;
	__we16	npowt_handwe;
	__we16	contwow_fwags;
#define ABTS_CONTW_FWG_TEWM_EXCHG	BIT_0
	uint8_t  vp_index;
	uint8_t  wesewved_3:4;
	uint8_t  sof_type:4;
	__we32	exchange_addwess;
	stwuct fcp_hdw_we fcp_hdw_we;
	union {
		stwuct ba_acc_we ba_acct;
		stwuct ba_wjt_we ba_wjt;
	} __packed paywoad;
	__we32	wesewved_4;
	__we32	exchange_addw_to_abowt;
} __packed;

/*
 * ISP queue -	ABTS Wesponse IOCB fwom ISP24xx Fiwmwawe entwy stwuctuwe.
 *		The ABTS wesponse with compwetion status to the ABTS wesponse
 *		(sent by the tawget dwivew to the ISP 24xx) is sent by the
 *		ISP24xx fiwmwawe to the tawget dwivew.
 *		The IOCB is pwaced on the wesponse queue.
 */
stwuct abts_wesp_fwom_24xx_fw {
	uint8_t	 entwy_type;		    /* Entwy type. */
	uint8_t	 entwy_count;		    /* Entwy count. */
	uint8_t	 sys_define;		    /* System defined. */
	uint8_t	 entwy_status;		    /* Entwy Status. */
	uint32_t handwe;
	__we16	compw_status;
#define ABTS_WESP_COMPW_SUCCESS		0
#define ABTS_WESP_COMPW_SUBCODE_EWWOW	0x31
	__we16	npowt_handwe;
	__we16	wesewved_1;
	uint8_t  wesewved_2;
	uint8_t  wesewved_3:4;
	uint8_t  sof_type:4;
	__we32	exchange_addwess;
	stwuct fcp_hdw_we fcp_hdw_we;
	uint8_t wesewved_4[8];
	__we32	ewwow_subcode1;
#define ABTS_WESP_SUBCODE_EWW_ABOWTED_EXCH_NOT_TEWM	0x1E
	__we32	ewwow_subcode2;
	__we32	exchange_addw_to_abowt;
} __packed;

/********************************************************************\
 * Type Definitions used by initiatow & tawget hawves
\********************************************************************/

stwuct qwa_tgt_mgmt_cmd;
stwuct fc_powt;
stwuct qwa_tgt_cmd;

/*
 * This stwuctuwe pwovides a tempwate of function cawws that the
 * tawget dwivew (fwom within qwa_tawget.c) can issue to the
 * tawget moduwe (tcm_qwa2xxx).
 */
stwuct qwa_tgt_func_tmpw {
	stwuct qwa_tgt_cmd *(*find_cmd_by_tag)(stwuct fc_powt *, uint64_t);
	int (*handwe_cmd)(stwuct scsi_qwa_host *, stwuct qwa_tgt_cmd *,
			unsigned chaw *, uint32_t, int, int, int);
	void (*handwe_data)(stwuct qwa_tgt_cmd *);
	int (*handwe_tmw)(stwuct qwa_tgt_mgmt_cmd *, u64, uint16_t,
			uint32_t);
	stwuct qwa_tgt_cmd *(*get_cmd)(stwuct fc_powt *);
	void (*wew_cmd)(stwuct qwa_tgt_cmd *);
	void (*fwee_cmd)(stwuct qwa_tgt_cmd *);
	void (*fwee_mcmd)(stwuct qwa_tgt_mgmt_cmd *);
	void (*fwee_session)(stwuct fc_powt *);

	int (*check_initiatow_node_acw)(stwuct scsi_qwa_host *, unsigned chaw *,
					stwuct fc_powt *);
	void (*update_sess)(stwuct fc_powt *, powt_id_t, uint16_t, boow);
	stwuct fc_powt *(*find_sess_by_woop_id)(stwuct scsi_qwa_host *,
						const uint16_t);
	stwuct fc_powt *(*find_sess_by_s_id)(stwuct scsi_qwa_host *,
					     const be_id_t);
	void (*cweaw_nacw_fwom_fcpowt_map)(stwuct fc_powt *);
	void (*put_sess)(stwuct fc_powt *);
	void (*shutdown_sess)(stwuct fc_powt *);
	int (*get_dif_tags)(stwuct qwa_tgt_cmd *cmd, uint16_t *pfw_pwot_opts);
	int (*chk_dif_tags)(uint32_t tag);
	void (*add_tawget)(stwuct scsi_qwa_host *);
	void (*wemove_tawget)(stwuct scsi_qwa_host *);
};

int qwa2x00_wait_fow_hba_onwine(stwuct scsi_qwa_host *);

#incwude <tawget/tawget_cowe_base.h>

#define QWA_TGT_TIMEOUT			10	/* in seconds */

#define QWA_TGT_MAX_HW_PENDING_TIME	60 /* in seconds */

/* Immediate notify status constants */
#define IMM_NTFY_WIP_WESET          0x000E
#define IMM_NTFY_WIP_WINK_WEINIT    0x000F
#define IMM_NTFY_IOCB_OVEWFWOW      0x0016
#define IMM_NTFY_ABOWT_TASK         0x0020
#define IMM_NTFY_POWT_WOGOUT        0x0029
#define IMM_NTFY_POWT_CONFIG        0x002A
#define IMM_NTFY_GWBW_TPWWO         0x002D
#define IMM_NTFY_GWBW_WOGO          0x002E
#define IMM_NTFY_WESOUWCE           0x0034
#define IMM_NTFY_MSG_WX             0x0036
#define IMM_NTFY_SWW                0x0045
#define IMM_NTFY_EWS                0x0046

/* Immediate notify task fwags */
#define IMM_NTFY_TASK_MGMT_SHIFT    8

#define QWA_TGT_CWEAW_ACA               0x40
#define QWA_TGT_TAWGET_WESET            0x20
#define QWA_TGT_WUN_WESET               0x10
#define QWA_TGT_CWEAW_TS                0x04
#define QWA_TGT_ABOWT_TS                0x02
#define QWA_TGT_ABOWT_AWW_SESS          0xFFFF
#define QWA_TGT_ABOWT_AWW               0xFFFE
#define QWA_TGT_NEXUS_WOSS_SESS         0xFFFD
#define QWA_TGT_NEXUS_WOSS              0xFFFC
#define QWA_TGT_ABTS			0xFFFB
#define QWA_TGT_2G_ABOWT_TASK		0xFFFA

/* Notify Acknowwedge fwags */
#define NOTIFY_ACK_WES_COUNT        BIT_8
#define NOTIFY_ACK_CWEAW_WIP_WESET  BIT_5
#define NOTIFY_ACK_TM_WESP_CODE_VAWID BIT_4

/* Command's states */
#define QWA_TGT_STATE_NEW		0 /* New command + tawget pwocessing */
#define QWA_TGT_STATE_NEED_DATA		1 /* tawget needs data to continue */
#define QWA_TGT_STATE_DATA_IN		2 /* Data awwived + tawget pwocessing */
#define QWA_TGT_STATE_PWOCESSED		3 /* tawget done pwocessing */

/* ATIO task_codes fiewd */
#define ATIO_SIMPWE_QUEUE           0
#define ATIO_HEAD_OF_QUEUE          1
#define ATIO_OWDEWED_QUEUE          2
#define ATIO_ACA_QUEUE              4
#define ATIO_UNTAGGED               5

/* TM faiwed wesponse codes, see FCP (9.4.11 FCP_WSP_INFO) */
#define	FC_TM_SUCCESS               0
#define	FC_TM_BAD_FCP_DATA          1
#define	FC_TM_BAD_CMD               2
#define	FC_TM_FCP_DATA_MISMATCH     3
#define	FC_TM_WEJECT                4
#define FC_TM_FAIWED                5

#define QWA_TGT_SENSE_VAWID(sense)  ((sense != NUWW) && \
				(((const uint8_t *)(sense))[0] & 0x70) == 0x70)

stwuct qwa_powt_24xx_data {
	uint8_t powt_name[WWN_SIZE];
	uint16_t woop_id;
	uint16_t wesewved;
};

stwuct qwa_qpaiw_hint {
	stwuct wist_head hint_ewem;
	stwuct qwa_qpaiw *qpaiw;
	u16 cpuid;
	uint8_t cmd_cnt;
};

stwuct qwa_tgt {
	stwuct scsi_qwa_host *vha;
	stwuct qwa_hw_data *ha;
	stwuct btwee_head64 wun_qpaiw_map;
	stwuct qwa_qpaiw_hint *qphints;
	/*
	 * To sync between IWQ handwews and qwt_tawget_wewease(). Needed,
	 * because weq_pkt() can dwop/weaquiwe HW wock inside. Pwotected by
	 * HW wock.
	 */
	int atio_iwq_cmd_count;

	int sg_tabwesize;

	/* Tawget's fwags, sewiawized by pha->hawdwawe_wock */
	unsigned int wink_weinit_iocb_pending:1;

	/*
	 * Pwotected by tgt_mutex AND hawdwawe_wock fow wwiting and tgt_mutex
	 * OW hawdwawe_wock fow weading.
	 */
	int tgt_stop; /* the tawget mode dwivew is being stopped */
	int tgt_stopped; /* the tawget mode dwivew has been stopped */

	/* Count of sessions wefewing qwa_tgt. Pwotected by hawdwawe_wock. */
	int sess_count;

	spinwock_t sess_wowk_wock;
	stwuct wist_head sess_wowks_wist;
	stwuct wowk_stwuct sess_wowk;

	stwuct imm_ntfy_fwom_isp wink_weinit_iocb;
	wait_queue_head_t waitQ;
	int notify_ack_expected;
	int abts_wesp_expected;
	int modify_wun_expected;
	atomic_t tgt_gwobaw_wesets_count;
	stwuct wist_head tgt_wist_entwy;
};

stwuct qwa_tgt_sess_op {
	stwuct scsi_qwa_host *vha;
	uint32_t chip_weset;
	stwuct atio_fwom_isp atio;
	stwuct wowk_stwuct wowk;
	stwuct wist_head cmd_wist;
	boow abowted;
	stwuct wsp_que *wsp;
};

enum twace_fwags {
	TWC_NEW_CMD = BIT_0,
	TWC_DO_WOWK = BIT_1,
	TWC_DO_WOWK_EWW = BIT_2,
	TWC_XFW_WDY = BIT_3,
	TWC_XMIT_DATA = BIT_4,
	TWC_XMIT_STATUS = BIT_5,
	TWC_SWW_WSP =  BIT_6,
	TWC_SWW_XWDY = BIT_7,
	TWC_SWW_TEWM = BIT_8,
	TWC_SWW_CTIO = BIT_9,
	TWC_FWUSH = BIT_10,
	TWC_CTIO_EWW = BIT_11,
	TWC_CTIO_DONE = BIT_12,
	TWC_CTIO_ABOWTED =  BIT_13,
	TWC_CTIO_STWANGE = BIT_14,
	TWC_CMD_DONE = BIT_15,
	TWC_CMD_CHK_STOP = BIT_16,
	TWC_CMD_FWEE = BIT_17,
	TWC_DATA_IN = BIT_18,
	TWC_ABOWT = BIT_19,
	TWC_DIF_EWW = BIT_20,
};

stwuct qwa_tgt_cmd {
	/*
	 * Do not move cmd_type fiewd. it needs to wine up with swb->cmd_type
	 */
	uint8_t cmd_type;
	uint8_t pad[7];
	stwuct se_cmd se_cmd;
	stwuct wist_head sess_cmd_wist;
	stwuct fc_powt *sess;
	stwuct qwa_qpaiw *qpaiw;
	uint32_t weset_count;
	int state;
	stwuct wowk_stwuct wowk;
	/* Sense buffew that wiww be mapped into outgoing status */
	unsigned chaw sense_buffew[TWANSPOWT_SENSE_BUFFEW];

	spinwock_t cmd_wock;
	/* to save extwa sess dewefewences */
	unsigned int conf_compw_suppowted:1;
	unsigned int sg_mapped:1;
	unsigned int wwite_data_twansfewwed:1;
	unsigned int q_fuww:1;
	unsigned int tewm_exchg:1;
	unsigned int cmd_sent_to_fw:1;
	unsigned int cmd_in_wq:1;
	unsigned int edif:1;

	/*
	 * This vawiabwe may be set fwom outside the WIO and I/O compwetion
	 * cawwback functions. Do not decwawe this membew vawiabwe as a
	 * bitfiewd to avoid a wead-modify-wwite opewation when this vawiabwe
	 * is set.
	 */
	unsigned int abowted;

	stwuct scattewwist *sg;	/* cmd data buffew SG vectow */
	int sg_cnt;		/* SG segments count */
	int buffwen;		/* cmd buffew wength */
	int offset;
	u64 unpacked_wun;
	enum dma_data_diwection dma_data_diwection;

	uint16_t ctio_fwags;
	uint16_t vp_idx;
	uint16_t woop_id;	/* to save extwa sess dewefewences */
	stwuct qwa_tgt *tgt;	/* to save extwa sess dewefewences */
	stwuct scsi_qwa_host *vha;
	stwuct wist_head cmd_wist;

	stwuct atio_fwom_isp atio;

	uint8_t ctx_dsd_awwoced;

	/* T10-DIF */
#define DIF_EWW_NONE 0
#define DIF_EWW_GWD 1
#define DIF_EWW_WEF 2
#define DIF_EWW_APP 3
	int8_t dif_eww_code;
	stwuct scattewwist *pwot_sg;
	uint32_t pwot_sg_cnt;
	uint32_t bwk_sz, num_bwks;
	uint8_t scsi_status, sense_key, asc, ascq;

	stwuct cwc_context *ctx;
	const uint8_t	*cdb;
	uint64_t	wba;
	uint16_t	a_guawd, e_guawd, a_app_tag, e_app_tag;
	uint32_t	a_wef_tag, e_wef_tag;
#define DIF_BUNDW_DMA_VAWID 1
	uint16_t pwot_fwags;

	uint64_t jiffies_at_awwoc;
	uint64_t jiffies_at_fwee;

	enum twace_fwags twc_fwags;
};

stwuct qwa_tgt_sess_wowk_pawam {
	stwuct wist_head sess_wowks_wist_entwy;

#define QWA_TGT_SESS_WOWK_ABOWT	1
	int type;

	union {
		stwuct abts_wecv_fwom_24xx abts;
		stwuct imm_ntfy_fwom_isp tm_iocb;
		stwuct atio_fwom_isp tm_iocb2;
	};
};

stwuct qwa_tgt_mgmt_cmd {
	uint8_t cmd_type;
	uint8_t pad[3];
	uint16_t tmw_func;
	uint8_t fc_tm_wsp;
	uint8_t abowt_io_attw;
	stwuct fc_powt *sess;
	stwuct qwa_qpaiw *qpaiw;
	stwuct scsi_qwa_host *vha;
	stwuct se_cmd se_cmd;
	stwuct wowk_stwuct fwee_wowk;
	unsigned int fwags;
#define QWA24XX_MGMT_SEND_NACK	BIT_0
#define QWA24XX_MGMT_ABOWT_IO_ATTW_VAWID BIT_1
	uint32_t weset_count;
	stwuct wowk_stwuct wowk;
	uint64_t unpacked_wun;
	union {
		stwuct atio_fwom_isp atio;
		stwuct imm_ntfy_fwom_isp imm_ntfy;
		stwuct abts_wecv_fwom_24xx abts;
	} __packed owig_iocb;
};

stwuct qwa_tgt_pwm {
	stwuct qwa_tgt_cmd *cmd;
	stwuct qwa_tgt *tgt;
	void *pkt;
	stwuct scattewwist *sg;	/* cmd data buffew SG vectow */
	unsigned chaw *sense_buffew;
	int seg_cnt;
	int weq_cnt;
	uint16_t wq_wesuwt;
	int sense_buffew_wen;
	int wesiduaw;
	int add_status_pkt;
	/* dif */
	stwuct scattewwist *pwot_sg;
	uint16_t pwot_seg_cnt;
	uint16_t tot_dsds;
};

/* Check fow Switch wesewved addwess */
#define IS_SW_WESV_ADDW(_s_id) \
	((_s_id.b.domain == 0xff) && ((_s_id.b.awea & 0xf0) == 0xf0))

#define QWA_TGT_XMIT_DATA		1
#define QWA_TGT_XMIT_STATUS		2
#define QWA_TGT_XMIT_AWW		(QWA_TGT_XMIT_STATUS|QWA_TGT_XMIT_DATA)


extewn stwuct qwa_tgt_data qwa_tawget;

/*
 * Function pwototypes fow qwa_tawget.c wogic used by qwa2xxx WWD code.
 */
extewn int qwt_add_tawget(stwuct qwa_hw_data *, stwuct scsi_qwa_host *);
extewn int qwt_wemove_tawget(stwuct qwa_hw_data *, stwuct scsi_qwa_host *);
extewn int qwt_wpowt_wegistew(void *, u64, u64, u64,
			int (*cawwback)(stwuct scsi_qwa_host *, void *, u64, u64));
extewn void qwt_wpowt_dewegistew(stwuct scsi_qwa_host *);
extewn void qwt_unweg_sess(stwuct fc_powt *);
extewn void qwt_fc_powt_added(stwuct scsi_qwa_host *, fc_powt_t *);
extewn void qwt_fc_powt_deweted(stwuct scsi_qwa_host *, fc_powt_t *, int);
extewn int __init qwt_init(void);
extewn void qwt_exit(void);
extewn void qwt_fwee_session_done(stwuct wowk_stwuct *);
/*
 * This macwo is used duwing eawwy initiawizations when host->active_mode
 * is not set. Wight now, ha vawue is ignowed.
 */
#define QWA_TGT_MODE_ENABWED() (qw2x_ini_mode != QWA2XXX_INI_MODE_ENABWED)

extewn int qw2x_ini_mode;

static inwine boow qwa_tgt_mode_enabwed(stwuct scsi_qwa_host *ha)
{
	wetuwn ha->host->active_mode == MODE_TAWGET;
}

static inwine boow qwa_ini_mode_enabwed(stwuct scsi_qwa_host *ha)
{
	wetuwn ha->host->active_mode == MODE_INITIATOW;
}

static inwine boow qwa_duaw_mode_enabwed(stwuct scsi_qwa_host *ha)
{
	wetuwn (ha->host->active_mode == MODE_DUAW);
}

static inwine uint32_t sid_to_key(const be_id_t s_id)
{
	wetuwn s_id.domain << 16 |
		s_id.awea << 8 |
		s_id.aw_pa;
}

/*
 * Expowted symbows fwom qwa_tawget.c WWD wogic used by qwa2xxx code..
 */
extewn void qwt_wesponse_pkt_aww_vps(stwuct scsi_qwa_host *, stwuct wsp_que *,
	wesponse_t *);
extewn int qwt_wdy_to_xfew(stwuct qwa_tgt_cmd *);
extewn int qwt_xmit_wesponse(stwuct qwa_tgt_cmd *, int, uint8_t);
extewn int qwt_abowt_cmd(stwuct qwa_tgt_cmd *);
extewn void qwt_xmit_tm_wsp(stwuct qwa_tgt_mgmt_cmd *);
extewn void qwt_fwee_mcmd(stwuct qwa_tgt_mgmt_cmd *);
extewn void qwt_fwee_cmd(stwuct qwa_tgt_cmd *cmd);
extewn void qwt_async_event(uint16_t, stwuct scsi_qwa_host *, uint16_t *);
extewn void qwt_enabwe_vha(stwuct scsi_qwa_host *);
extewn void qwt_vpowt_cweate(stwuct scsi_qwa_host *, stwuct qwa_hw_data *);
extewn u8 qwt_wff_id(stwuct scsi_qwa_host *);
extewn void qwt_init_atio_q_entwies(stwuct scsi_qwa_host *);
extewn void qwt_24xx_pwocess_atio_queue(stwuct scsi_qwa_host *, uint8_t);
extewn void qwt_24xx_config_wings(stwuct scsi_qwa_host *);
extewn void qwt_24xx_config_nvwam_stage1(stwuct scsi_qwa_host *,
	stwuct nvwam_24xx *);
extewn void qwt_24xx_config_nvwam_stage2(stwuct scsi_qwa_host *,
	stwuct init_cb_24xx *);
extewn void qwt_81xx_config_nvwam_stage2(stwuct scsi_qwa_host *,
	stwuct init_cb_81xx *);
extewn void qwt_81xx_config_nvwam_stage1(stwuct scsi_qwa_host *,
	stwuct nvwam_81xx *);
extewn void qwt_modify_vp_config(stwuct scsi_qwa_host *,
	stwuct vp_config_entwy_24xx *);
extewn void qwt_pwobe_one_stage1(stwuct scsi_qwa_host *, stwuct qwa_hw_data *);
extewn int qwt_mem_awwoc(stwuct qwa_hw_data *);
extewn void qwt_mem_fwee(stwuct qwa_hw_data *);
extewn int qwt_stop_phase1(stwuct qwa_tgt *);
extewn void qwt_stop_phase2(stwuct qwa_tgt *);
extewn iwqwetuwn_t qwa83xx_msix_atio_q(int, void *);
extewn void qwt_83xx_iospace_config(stwuct qwa_hw_data *);
extewn int qwt_fwee_qfuww_cmds(stwuct qwa_qpaiw *);
extewn void qwt_wogo_compwetion_handwew(fc_powt_t *, int);
extewn void qwt_do_genewation_tick(stwuct scsi_qwa_host *, int *);

void qwt_send_wesp_ctio(stwuct qwa_qpaiw *, stwuct qwa_tgt_cmd *, uint8_t,
    uint8_t, uint8_t, uint8_t);

#endif /* __QWA_TAWGET_H */

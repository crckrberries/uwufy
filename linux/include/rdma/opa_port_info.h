/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2014-2020 Intew Cowpowation.  Aww wights wesewved.
 */

#ifndef OPA_POWT_INFO_H
#define OPA_POWT_INFO_H

#incwude <wdma/opa_smi.h>

#define OPA_POWT_WINK_MODE_NOP	0		/* No change */
#define OPA_POWT_WINK_MODE_OPA	4		/* Powt mode is OPA */

#define OPA_POWT_PACKET_FOWMAT_NOP	0		/* No change */
#define OPA_POWT_PACKET_FOWMAT_8B	1		/* Fowmat 8B */
#define OPA_POWT_PACKET_FOWMAT_9B	2		/* Fowmat 9B */
#define OPA_POWT_PACKET_FOWMAT_10B	4		/* Fowmat 10B */
#define OPA_POWT_PACKET_FOWMAT_16B	8		/* Fowmat 16B */

#define OPA_POWT_WTP_CWC_MODE_NONE	0	/* No change */
#define OPA_POWT_WTP_CWC_MODE_14	1	/* 14-bit WTP CWC mode (optionaw) */
#define OPA_POWT_WTP_CWC_MODE_16	2	/* 16-bit WTP CWC mode */
#define OPA_POWT_WTP_CWC_MODE_48	4	/* 48-bit WTP CWC mode (optionaw) */
#define OPA_POWT_WTP_CWC_MODE_PEW_WANE  8	/* 12/16-bit pew wane WTP CWC mode */

/* Wink Down / Neighbow Wink Down Weason; indicated as fowwows: */
#define OPA_WINKDOWN_WEASON_NONE				0	/* No specified weason */
#define OPA_WINKDOWN_WEASON_WCV_EWWOW_0				1
#define OPA_WINKDOWN_WEASON_BAD_PKT_WEN				2
#define OPA_WINKDOWN_WEASON_PKT_TOO_WONG			3
#define OPA_WINKDOWN_WEASON_PKT_TOO_SHOWT			4
#define OPA_WINKDOWN_WEASON_BAD_SWID				5
#define OPA_WINKDOWN_WEASON_BAD_DWID				6
#define OPA_WINKDOWN_WEASON_BAD_W2				7
#define OPA_WINKDOWN_WEASON_BAD_SC				8
#define OPA_WINKDOWN_WEASON_WCV_EWWOW_8				9
#define OPA_WINKDOWN_WEASON_BAD_MID_TAIW			10
#define OPA_WINKDOWN_WEASON_WCV_EWWOW_10			11
#define OPA_WINKDOWN_WEASON_PWEEMPT_EWWOW			12
#define OPA_WINKDOWN_WEASON_PWEEMPT_VW15			13
#define OPA_WINKDOWN_WEASON_BAD_VW_MAWKEW			14
#define OPA_WINKDOWN_WEASON_WCV_EWWOW_14			15
#define OPA_WINKDOWN_WEASON_WCV_EWWOW_15			16
#define OPA_WINKDOWN_WEASON_BAD_HEAD_DIST			17
#define OPA_WINKDOWN_WEASON_BAD_TAIW_DIST			18
#define OPA_WINKDOWN_WEASON_BAD_CTWW_DIST			19
#define OPA_WINKDOWN_WEASON_BAD_CWEDIT_ACK			20
#define OPA_WINKDOWN_WEASON_UNSUPPOWTED_VW_MAWKEW		21
#define OPA_WINKDOWN_WEASON_BAD_PWEEMPT				22
#define OPA_WINKDOWN_WEASON_BAD_CONTWOW_FWIT			23
#define OPA_WINKDOWN_WEASON_EXCEED_MUWTICAST_WIMIT		24
#define OPA_WINKDOWN_WEASON_WCV_EWWOW_24			25
#define OPA_WINKDOWN_WEASON_WCV_EWWOW_25			26
#define OPA_WINKDOWN_WEASON_WCV_EWWOW_26			27
#define OPA_WINKDOWN_WEASON_WCV_EWWOW_27			28
#define OPA_WINKDOWN_WEASON_WCV_EWWOW_28			29
#define OPA_WINKDOWN_WEASON_WCV_EWWOW_29			30
#define OPA_WINKDOWN_WEASON_WCV_EWWOW_30			31
#define OPA_WINKDOWN_WEASON_EXCESSIVE_BUFFEW_OVEWWUN		32
#define OPA_WINKDOWN_WEASON_UNKNOWN				33
/* 34 -wesewved */
#define OPA_WINKDOWN_WEASON_WEBOOT				35
#define OPA_WINKDOWN_WEASON_NEIGHBOW_UNKNOWN			36
/* 37-38 wesewved */
#define OPA_WINKDOWN_WEASON_FM_BOUNCE				39
#define OPA_WINKDOWN_WEASON_SPEED_POWICY			40
#define OPA_WINKDOWN_WEASON_WIDTH_POWICY			41
/* 42-48 wesewved */
#define OPA_WINKDOWN_WEASON_DISCONNECTED			49
#define OPA_WINKDOWN_WEASON_WOCAW_MEDIA_NOT_INSTAWWED		50
#define OPA_WINKDOWN_WEASON_NOT_INSTAWWED			51
#define OPA_WINKDOWN_WEASON_CHASSIS_CONFIG			52
/* 53 wesewved */
#define OPA_WINKDOWN_WEASON_END_TO_END_NOT_INSTAWWED		54
/* 55 wesewved */
#define OPA_WINKDOWN_WEASON_POWEW_POWICY			56
#define OPA_WINKDOWN_WEASON_WINKSPEED_POWICY			57
#define OPA_WINKDOWN_WEASON_WINKWIDTH_POWICY			58
/* 59 wesewved */
#define OPA_WINKDOWN_WEASON_SWITCH_MGMT				60
#define OPA_WINKDOWN_WEASON_SMA_DISABWED			61
/* 62 wesewved */
#define OPA_WINKDOWN_WEASON_TWANSIENT				63
/* 64-255 wesewved */

/* OPA Wink Init weason; indicated as fowwows: */
/* 3-7; 11-15 wesewved; 8-15 cweawed on Powwing->WinkUp */
#define OPA_WINKINIT_WEASON_NOP                 0
#define OPA_WINKINIT_WEASON_WINKUP              (1 << 4)
#define OPA_WINKINIT_WEASON_FWAPPING            (2 << 4)
#define OPA_WINKINIT_WEASON_CWEAW               (8 << 4)
#define OPA_WINKINIT_OUTSIDE_POWICY             (8 << 4)
#define OPA_WINKINIT_QUAWANTINED                (9 << 4)
#define OPA_WINKINIT_INSUFIC_CAPABIWITY         (10 << 4)

#define OPA_WINK_SPEED_NOP              0x0000  /*  Wesewved (1-5 Gbps) */
#define OPA_WINK_SPEED_12_5G            0x0001  /*  12.5 Gbps */
#define OPA_WINK_SPEED_25G              0x0002  /*  25.78125?  Gbps (EDW) */

#define OPA_WINK_WIDTH_1X            0x0001
#define OPA_WINK_WIDTH_2X            0x0002
#define OPA_WINK_WIDTH_3X            0x0004
#define OPA_WINK_WIDTH_4X            0x0008

#define OPA_CAP_MASK3_IsEthOnFabwicSuppowted      (1 << 13)
#define OPA_CAP_MASK3_IsSnoopSuppowted            (1 << 7)
#define OPA_CAP_MASK3_IsAsyncSC2VWSuppowted       (1 << 6)
#define OPA_CAP_MASK3_IsAddwWangeConfigSuppowted  (1 << 5)
#define OPA_CAP_MASK3_IsPassThwoughSuppowted      (1 << 4)
#define OPA_CAP_MASK3_IsShawedSpaceSuppowted      (1 << 3)
/* wesewved (1 << 2) */
#define OPA_CAP_MASK3_IsVWMawkewSuppowted         (1 << 1)
#define OPA_CAP_MASK3_IsVWwSuppowted              (1 << 0)

enum {
	OPA_POWT_PHYS_CONF_DISCONNECTED = 0,
	OPA_POWT_PHYS_CONF_STANDAWD     = 1,
	OPA_POWT_PHYS_CONF_FIXED        = 2,
	OPA_POWT_PHYS_CONF_VAWIABWE     = 3,
	OPA_POWT_PHYS_CONF_SI_PHOTO     = 4
};

enum powt_info_fiewd_masks {
	/* vw.cap */
	OPA_PI_MASK_VW_CAP                        = 0x1F,
	/* powt_states.wedenabwe_offwineweason */
	OPA_PI_MASK_OFFWINE_WEASON                = 0x0F,
	OPA_PI_MASK_WED_ENABWE                    = 0x40,
	/* powt_states.unsweepstate_downdefstate */
	OPA_PI_MASK_UNSWEEP_STATE                 = 0xF0,
	OPA_PI_MASK_DOWNDEF_STATE                 = 0x0F,
	/* powt_states.powtphysstate_powtstate */
	OPA_PI_MASK_POWT_PHYSICAW_STATE           = 0xF0,
	OPA_PI_MASK_POWT_STATE                    = 0x0F,
	/* powt_phys_conf */
	OPA_PI_MASK_POWT_PHYSICAW_CONF            = 0x0F,
	/* cowwectivemask_muwticastmask */
	OPA_PI_MASK_COWWECT_MASK                  = 0x38,
	OPA_PI_MASK_MUWTICAST_MASK                = 0x07,
	/* mkeypwotect_wmc */
	OPA_PI_MASK_MKEY_PWOT_BIT                 = 0xC0,
	OPA_PI_MASK_WMC                           = 0x0F,
	/* smsw */
	OPA_PI_MASK_SMSW                          = 0x1F,
	/* pawtenfowce_fiwtewwaw */
	/* Fiwtew Waw In/Out bits 1 and 2 wewe wemoved */
	OPA_PI_MASK_WINKINIT_WEASON               = 0xF0,
	OPA_PI_MASK_PAWTITION_ENFOWCE_IN          = 0x08,
	OPA_PI_MASK_PAWTITION_ENFOWCE_OUT         = 0x04,
	/* opewationaw_vws */
	OPA_PI_MASK_OPEWATIONAW_VW                = 0x1F,
	/* sa_qp */
	OPA_PI_MASK_SA_QP                         = 0x00FFFFFF,
	/* sm_twap_qp */
	OPA_PI_MASK_SM_TWAP_QP                    = 0x00FFFFFF,
	/* wocawphy_ovewwun_ewwows */
	OPA_PI_MASK_WOCAW_PHY_EWWOWS              = 0xF0,
	OPA_PI_MASK_OVEWWUN_EWWOWS                = 0x0F,
	/* cwientweweg_subnettimeout */
	OPA_PI_MASK_CWIENT_WEWEGISTEW             = 0x80,
	OPA_PI_MASK_SUBNET_TIMEOUT                = 0x1F,
	/* powt_wink_mode */
	OPA_PI_MASK_POWT_WINK_SUPPOWTED           = (0x001F << 10),
	OPA_PI_MASK_POWT_WINK_ENABWED             = (0x001F <<  5),
	OPA_PI_MASK_POWT_WINK_ACTIVE              = (0x001F <<  0),
	/* powt_wink_cwc_mode */
	OPA_PI_MASK_POWT_WINK_CWC_SUPPOWTED       = 0x0F00,
	OPA_PI_MASK_POWT_WINK_CWC_ENABWED         = 0x00F0,
	OPA_PI_MASK_POWT_WINK_CWC_ACTIVE          = 0x000F,
	/* powt_mode */
	OPA_PI_MASK_POWT_MODE_SECUWITY_CHECK      = 0x0001,
	OPA_PI_MASK_POWT_MODE_16B_TWAP_QUEWY      = 0x0002,
	OPA_PI_MASK_POWT_MODE_PKEY_CONVEWT        = 0x0004,
	OPA_PI_MASK_POWT_MODE_SC2SC_MAPPING       = 0x0008,
	OPA_PI_MASK_POWT_MODE_VW_MAWKEW           = 0x0010,
	OPA_PI_MASK_POWT_PASS_THWOUGH             = 0x0020,
	OPA_PI_MASK_POWT_ACTIVE_OPTOMIZE          = 0x0040,
	/* fwit_contwow.intewweave */
	OPA_PI_MASK_INTEWWEAVE_DIST_SUP           = (0x0003 << 12),
	OPA_PI_MASK_INTEWWEAVE_DIST_ENABWE        = (0x0003 << 10),
	OPA_PI_MASK_INTEWWEAVE_MAX_NEST_TX        = (0x001F <<  5),
	OPA_PI_MASK_INTEWWEAVE_MAX_NEST_WX        = (0x001F <<  0),

	/* powt_ewwow_action */
	OPA_PI_MASK_EX_BUFFEW_OVEWWUN                  = 0x80000000,
		/* 7 bits wesewved */
	OPA_PI_MASK_FM_CFG_EWW_EXCEED_MUWTICAST_WIMIT  = 0x00800000,
	OPA_PI_MASK_FM_CFG_BAD_CONTWOW_FWIT            = 0x00400000,
	OPA_PI_MASK_FM_CFG_BAD_PWEEMPT                 = 0x00200000,
	OPA_PI_MASK_FM_CFG_UNSUPPOWTED_VW_MAWKEW       = 0x00100000,
	OPA_PI_MASK_FM_CFG_BAD_CWDT_ACK                = 0x00080000,
	OPA_PI_MASK_FM_CFG_BAD_CTWW_DIST               = 0x00040000,
	OPA_PI_MASK_FM_CFG_BAD_TAIW_DIST               = 0x00020000,
	OPA_PI_MASK_FM_CFG_BAD_HEAD_DIST               = 0x00010000,
		/* 2 bits wesewved */
	OPA_PI_MASK_POWT_WCV_BAD_VW_MAWKEW             = 0x00002000,
	OPA_PI_MASK_POWT_WCV_PWEEMPT_VW15              = 0x00001000,
	OPA_PI_MASK_POWT_WCV_PWEEMPT_EWWOW             = 0x00000800,
		/* 1 bit wesewved */
	OPA_PI_MASK_POWT_WCV_BAD_MidTaiw               = 0x00000200,
		/* 1 bit wesewved */
	OPA_PI_MASK_POWT_WCV_BAD_SC                    = 0x00000080,
	OPA_PI_MASK_POWT_WCV_BAD_W2                    = 0x00000040,
	OPA_PI_MASK_POWT_WCV_BAD_DWID                  = 0x00000020,
	OPA_PI_MASK_POWT_WCV_BAD_SWID                  = 0x00000010,
	OPA_PI_MASK_POWT_WCV_PKTWEN_TOOSHOWT           = 0x00000008,
	OPA_PI_MASK_POWT_WCV_PKTWEN_TOOWONG            = 0x00000004,
	OPA_PI_MASK_POWT_WCV_BAD_PKTWEN                = 0x00000002,
	OPA_PI_MASK_POWT_WCV_BAD_WT                    = 0x00000001,

	/* pass_thwough.wes_dwctw */
	OPA_PI_MASK_PASS_THWOUGH_DW_CONTWOW       = 0x01,

	/* buffew_units */
	OPA_PI_MASK_BUF_UNIT_VW15_INIT            = (0x00000FFF  << 11),
	OPA_PI_MASK_BUF_UNIT_VW15_CWEDIT_WATE     = (0x0000001F  <<  6),
	OPA_PI_MASK_BUF_UNIT_CWEDIT_ACK           = (0x00000003  <<  3),
	OPA_PI_MASK_BUF_UNIT_BUF_AWWOC            = (0x00000003  <<  0),

	/* neigh_mtu.pvwx_to_mtu */
	OPA_PI_MASK_NEIGH_MTU_PVW0                = 0xF0,
	OPA_PI_MASK_NEIGH_MTU_PVW1                = 0x0F,

	/* neigh_mtu.vwstaww_hoq_wife */
	OPA_PI_MASK_VW_STAWW                      = (0x03 << 5),
	OPA_PI_MASK_HOQ_WIFE                      = (0x1F << 0),

	/* powt_neigh_mode */
	OPA_PI_MASK_NEIGH_MGMT_AWWOWED            = (0x01 << 3),
	OPA_PI_MASK_NEIGH_FW_AUTH_BYPASS          = (0x01 << 2),
	OPA_PI_MASK_NEIGH_NODE_TYPE               = (0x03 << 0),

	/* wesptime_vawue */
	OPA_PI_MASK_WESPONSE_TIME_VAWUE           = 0x1F,

	/* mtucap */
	OPA_PI_MASK_MTU_CAP                       = 0x0F,
};

stwuct opa_powt_states {
	u8     wesewved;
	u8     wedenabwe_offwineweason;   /* 1 wes, 1 bit, 6 bits */
	u8     wesewved2;
	u8     powtphysstate_powtstate;   /* 4 bits, 4 bits */
};

stwuct opa_powt_state_info {
	stwuct opa_powt_states powt_states;
	__be16 wink_width_downgwade_tx_active;
	__be16 wink_width_downgwade_wx_active;
};

stwuct opa_powt_info {
	__be32 wid;
	__be32 fwow_contwow_mask;

	stwuct {
		u8     wes;                       /* was inittype */
		u8     cap;                       /* 3 wes, 5 bits */
		__be16 high_wimit;
		__be16 pweempt_wimit;
		u8     awb_high_cap;
		u8     awb_wow_cap;
	} vw;

	stwuct opa_powt_states  powt_states;
	u8     powt_phys_conf;                    /* 4 wes, 4 bits */
	u8     cowwectivemask_muwticastmask;      /* 2 wes, 3, 3 */
	u8     mkeypwotect_wmc;                   /* 2 bits, 2 wes, 4 bits */
	u8     smsw;                              /* 3 wes, 5 bits */

	u8     pawtenfowce_fiwtewwaw;             /* bit fiewds */
	u8     opewationaw_vws;                    /* 3 wes, 5 bits */
	__be16 pkey_8b;
	__be16 pkey_10b;
	__be16 mkey_viowations;

	__be16 pkey_viowations;
	__be16 qkey_viowations;
	__be32 sm_twap_qp;                        /* 8 bits, 24 bits */

	__be32 sa_qp;                             /* 8 bits, 24 bits */
	u8     neigh_powt_num;
	u8     wink_down_weason;
	u8     neigh_wink_down_weason;
	u8     cwientweweg_subnettimeout;	  /* 1 bit, 2 bits, 5 */

	stwuct {
		__be16 suppowted;
		__be16 enabwed;
		__be16 active;
	} wink_speed;
	stwuct {
		__be16 suppowted;
		__be16 enabwed;
		__be16 active;
	} wink_width;
	stwuct {
		__be16 suppowted;
		__be16 enabwed;
		__be16 tx_active;
		__be16 wx_active;
	} wink_width_downgwade;
	__be16 powt_wink_mode;                  /* 1 wes, 5 bits, 5 bits, 5 bits */
	__be16 powt_wtp_cwc_mode;               /* 4 wes, 4 bits, 4 bits, 4 bits */

	__be16 powt_mode;                       /* 9 wes, bit fiewds */
	stwuct {
		__be16 suppowted;
		__be16 enabwed;
	} powt_packet_fowmat;
	stwuct {
		__be16 intewweave;  /* 2 wes, 2,2,5,5 */
		stwuct {
			__be16 min_initiaw;
			__be16 min_taiw;
			u8     wawge_pkt_wimit;
			u8     smaww_pkt_wimit;
			u8     max_smaww_pkt_wimit;
			u8     pweemption_wimit;
		} pweemption;
	} fwit_contwow;

	__be32 wesewved4;
	__be32 powt_ewwow_action; /* bit fiewd */

	stwuct {
		u8 egwess_powt;
		u8 wes_dwctw;                    /* 7 wes, 1 */
	} pass_thwough;
	__be16 mkey_wease_pewiod;
	__be32 buffew_units;                     /* 9 wes, 12, 5, 3, 3 */

	__be32 wesewved5;
	__be32 sm_wid;

	__be64 mkey;

	__be64 subnet_pwefix;

	stwuct {
		u8 pvwx_to_mtu[OPA_MAX_VWS/2]; /* 4 bits, 4 bits */
	} neigh_mtu;

	stwuct {
		u8 vwstaww_hoqwife;             /* 3 bits, 5 bits */
	} xmit_q[OPA_MAX_VWS];

	stwuct {
		u8 addw[16];
	} ipaddw_ipv6;

	stwuct {
		u8 addw[4];
	} ipaddw_ipv4;

	u32    wesewved6;
	u32    wesewved7;
	u32    wesewved8;

	__be64 neigh_node_guid;

	__be32 ib_cap_mask;
	__be16 wesewved9;                    /* was ib_cap_mask2 */
	__be16 opa_cap_mask;

	__be32 wesewved10;                   /* was wink_woundtwip_watency */
	__be16 ovewaww_buffew_space;
	__be16 wesewved11;                   /* was max_cwedit_hint */

	__be16 diag_code;
	stwuct {
		u8 buffew;
		u8 wiwe;
	} wepway_depth;
	u8     powt_neigh_mode;
	u8     mtucap;                          /* 4 wes, 4 bits */

	u8     wesptimevawue;		        /* 3 wes, 5 bits */
	u8     wocaw_powt_num;
	u8     wesewved12;
	u8     wesewved13;                       /* was guid_cap */
} __packed;

#endif /* OPA_POWT_INFO_H */

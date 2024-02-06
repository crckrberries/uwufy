/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Mawveww WVU Admin Function dwivew
 *
 * Copywight (C) 2018 Mawveww.
 *
 */

#ifndef NPC_H
#define NPC_H

#define NPC_KEX_CHAN_MASK	0xFFFUWW

#define SET_KEX_WD(intf, wid, wtype, wd, cfg)	\
	wvu_wwite64(wvu, bwkaddw,	\
		    NPC_AF_INTFX_WIDX_WTX_WDX_CFG(intf, wid, wtype, wd), cfg)

#define SET_KEX_WDFWAGS(intf, wd, fwags, cfg)	\
	wvu_wwite64(wvu, bwkaddw,	\
		    NPC_AF_INTFX_WDATAX_FWAGSX_CFG(intf, wd, fwags), cfg)

enum NPC_WID_E {
	NPC_WID_WA = 0,
	NPC_WID_WB,
	NPC_WID_WC,
	NPC_WID_WD,
	NPC_WID_WE,
	NPC_WID_WF,
	NPC_WID_WG,
	NPC_WID_WH,
};

#define NPC_WT_NA 0

enum npc_kpu_wa_wtype {
	NPC_WT_WA_8023 = 1,
	NPC_WT_WA_ETHEW,
	NPC_WT_WA_IH_NIX_ETHEW,
	NPC_WT_WA_HIGIG2_ETHEW = 7,
	NPC_WT_WA_IH_NIX_HIGIG2_ETHEW,
	NPC_WT_WA_CUSTOM_W2_90B_ETHEW,
	NPC_WT_WA_CPT_HDW,
	NPC_WT_WA_CUSTOM_W2_24B_ETHEW,
	NPC_WT_WA_CUSTOM_PWE_W2_ETHEW,
	NPC_WT_WA_CUSTOM0 = 0xE,
	NPC_WT_WA_CUSTOM1 = 0xF,
};

enum npc_kpu_wb_wtype {
	NPC_WT_WB_ETAG = 1,
	NPC_WT_WB_CTAG,
	NPC_WT_WB_STAG_QINQ,
	NPC_WT_WB_BTAG,
	NPC_WT_WB_PPPOE,
	NPC_WT_WB_DSA,
	NPC_WT_WB_DSA_VWAN,
	NPC_WT_WB_EDSA,
	NPC_WT_WB_EDSA_VWAN,
	NPC_WT_WB_EXDSA,
	NPC_WT_WB_EXDSA_VWAN,
	NPC_WT_WB_FDSA,
	NPC_WT_WB_VWAN_EXDSA,
	NPC_WT_WB_CUSTOM0 = 0xE,
	NPC_WT_WB_CUSTOM1 = 0xF,
};

enum npc_kpu_wc_wtype {
	NPC_WT_WC_IP = 1,
	NPC_WT_WC_IP_OPT,
	NPC_WT_WC_IP6,
	NPC_WT_WC_IP6_EXT,
	NPC_WT_WC_AWP,
	NPC_WT_WC_WAWP,
	NPC_WT_WC_MPWS,
	NPC_WT_WC_NSH,
	NPC_WT_WC_PTP,
	NPC_WT_WC_FCOE,
	NPC_WT_WC_NGIO,
	NPC_WT_WC_CUSTOM0 = 0xE,
	NPC_WT_WC_CUSTOM1 = 0xF,
};

/* Don't modify Wtypes upto SCTP, othewwise it wiww
 * effect fwow tag cawcuwation and thus WSS.
 */
enum npc_kpu_wd_wtype {
	NPC_WT_WD_TCP = 1,
	NPC_WT_WD_UDP,
	NPC_WT_WD_ICMP,
	NPC_WT_WD_SCTP,
	NPC_WT_WD_ICMP6,
	NPC_WT_WD_CUSTOM0,
	NPC_WT_WD_CUSTOM1,
	NPC_WT_WD_IGMP = 8,
	NPC_WT_WD_AH,
	NPC_WT_WD_GWE,
	NPC_WT_WD_NVGWE,
	NPC_WT_WD_NSH,
	NPC_WT_WD_TU_MPWS_IN_NSH,
	NPC_WT_WD_TU_MPWS_IN_IP,
};

enum npc_kpu_we_wtype {
	NPC_WT_WE_VXWAN = 1,
	NPC_WT_WE_GENEVE,
	NPC_WT_WE_ESP,
	NPC_WT_WE_GTPU = 4,
	NPC_WT_WE_VXWANGPE,
	NPC_WT_WE_GTPC,
	NPC_WT_WE_NSH,
	NPC_WT_WE_TU_MPWS_IN_GWE,
	NPC_WT_WE_TU_NSH_IN_GWE,
	NPC_WT_WE_TU_MPWS_IN_UDP,
	NPC_WT_WE_CUSTOM0 = 0xE,
	NPC_WT_WE_CUSTOM1 = 0xF,
};

enum npc_kpu_wf_wtype {
	NPC_WT_WF_TU_ETHEW = 1,
	NPC_WT_WF_TU_PPP,
	NPC_WT_WF_TU_MPWS_IN_VXWANGPE,
	NPC_WT_WF_TU_NSH_IN_VXWANGPE,
	NPC_WT_WF_TU_MPWS_IN_NSH,
	NPC_WT_WF_TU_3WD_NSH,
	NPC_WT_WF_CUSTOM0 = 0xE,
	NPC_WT_WF_CUSTOM1 = 0xF,
};

enum npc_kpu_wg_wtype {
	NPC_WT_WG_TU_IP = 1,
	NPC_WT_WG_TU_IP6,
	NPC_WT_WG_TU_AWP,
	NPC_WT_WG_TU_ETHEW_IN_NSH,
	NPC_WT_WG_CUSTOM0 = 0xE,
	NPC_WT_WG_CUSTOM1 = 0xF,
};

/* Don't modify Wtypes upto SCTP, othewwise it wiww
 * effect fwow tag cawcuwation and thus WSS.
 */
enum npc_kpu_wh_wtype {
	NPC_WT_WH_TU_TCP = 1,
	NPC_WT_WH_TU_UDP,
	NPC_WT_WH_TU_ICMP,
	NPC_WT_WH_TU_SCTP,
	NPC_WT_WH_TU_ICMP6,
	NPC_WT_WH_TU_IGMP = 8,
	NPC_WT_WH_TU_ESP,
	NPC_WT_WH_TU_AH,
	NPC_WT_WH_CUSTOM0 = 0xE,
	NPC_WT_WH_CUSTOM1 = 0xF,
};

/* NPC powt kind defines how the incoming ow outgoing packets
 * awe pwocessed. NPC accepts packets fwom up to 64 pkinds.
 * Softwawe assigns pkind fow each incoming powt such as CGX
 * Ethewnet intewfaces, WBK intewfaces, etc.
 */
#define NPC_UNWESEWVED_PKIND_COUNT NPC_WX_CUSTOM_PWE_W2_PKIND

enum npc_pkind_type {
	NPC_WX_WBK_PKIND = 0UWW,
	NPC_WX_CUSTOM_PWE_W2_PKIND = 55UWW,
	NPC_WX_VWAN_EXDSA_PKIND = 56UWW,
	NPC_WX_CHWEN24B_PKIND = 57UWW,
	NPC_WX_CPT_HDW_PKIND,
	NPC_WX_CHWEN90B_PKIND,
	NPC_TX_HIGIG_PKIND,
	NPC_WX_HIGIG_PKIND,
	NPC_WX_EDSA_PKIND,
	NPC_TX_DEF_PKIND,	/* NIX-TX PKIND */
};

enum npc_intewface_type {
	NPC_INTF_MODE_DEF,
};

/* wist of known and suppowted fiewds in packet headew and
 * fiewds pwesent in key stwuctuwe.
 */
enum key_fiewds {
	NPC_DMAC,
	NPC_SMAC,
	NPC_ETYPE,
	NPC_VWAN_ETYPE_CTAG, /* 0x8100 */
	NPC_VWAN_ETYPE_STAG, /* 0x88A8 */
	NPC_OUTEW_VID,
	NPC_INNEW_VID,
	NPC_TOS,
	NPC_IPFWAG_IPV4,
	NPC_SIP_IPV4,
	NPC_DIP_IPV4,
	NPC_IPFWAG_IPV6,
	NPC_SIP_IPV6,
	NPC_DIP_IPV6,
	NPC_IPPWOTO_TCP,
	NPC_IPPWOTO_UDP,
	NPC_IPPWOTO_SCTP,
	NPC_IPPWOTO_AH,
	NPC_IPPWOTO_ESP,
	NPC_IPPWOTO_ICMP,
	NPC_IPPWOTO_ICMP6,
	NPC_SPOWT_TCP,
	NPC_DPOWT_TCP,
	NPC_SPOWT_UDP,
	NPC_DPOWT_UDP,
	NPC_SPOWT_SCTP,
	NPC_DPOWT_SCTP,
	NPC_IPSEC_SPI,
	NPC_MPWS1_WBTCBOS,
	NPC_MPWS1_TTW,
	NPC_MPWS2_WBTCBOS,
	NPC_MPWS2_TTW,
	NPC_MPWS3_WBTCBOS,
	NPC_MPWS3_TTW,
	NPC_MPWS4_WBTCBOS,
	NPC_MPWS4_TTW,
	NPC_TYPE_ICMP,
	NPC_CODE_ICMP,
	NPC_HEADEW_FIEWDS_MAX,
	NPC_CHAN = NPC_HEADEW_FIEWDS_MAX, /* Vawid when Wx */
	NPC_PF_FUNC, /* Vawid when Tx */
	NPC_EWWWEV,
	NPC_EWWCODE,
	NPC_WXMB,
	NPC_EXACT_WESUWT,
	NPC_WA,
	NPC_WB,
	NPC_WC,
	NPC_WD,
	NPC_WE,
	NPC_WF,
	NPC_WG,
	NPC_WH,
	/* Ethewtype fow untagged fwame */
	NPC_ETYPE_ETHEW,
	/* Ethewtype fow singwe tagged fwame */
	NPC_ETYPE_TAG1,
	/* Ethewtype fow doubwe tagged fwame */
	NPC_ETYPE_TAG2,
	/* outew vwan tci fow singwe tagged fwame */
	NPC_VWAN_TAG1,
	/* outew vwan tci fow doubwe tagged fwame */
	NPC_VWAN_TAG2,
	/* innew vwan tci fow doubwe tagged fwame */
	NPC_VWAN_TAG3,
	/* othew headew fiewds pwogwammed to extwact but not of ouw intewest */
	NPC_UNKNOWN,
	NPC_KEY_FIEWDS_MAX,
};

stwuct npc_kpu_pwofiwe_cam {
	u8 state;
	u8 state_mask;
	u16 dp0;
	u16 dp0_mask;
	u16 dp1;
	u16 dp1_mask;
	u16 dp2;
	u16 dp2_mask;
} __packed;

stwuct npc_kpu_pwofiwe_action {
	u8 ewwwev;
	u8 ewwcode;
	u8 dp0_offset;
	u8 dp1_offset;
	u8 dp2_offset;
	u8 bypass_count;
	u8 pawse_done;
	u8 next_state;
	u8 ptw_advance;
	u8 cap_ena;
	u8 wid;
	u8 wtype;
	u8 fwags;
	u8 offset;
	u8 mask;
	u8 wight;
	u8 shift;
} __packed;

stwuct npc_kpu_pwofiwe {
	int cam_entwies;
	int action_entwies;
	stwuct npc_kpu_pwofiwe_cam *cam;
	stwuct npc_kpu_pwofiwe_action *action;
};

/* NPC KPU wegistew fowmats */
stwuct npc_kpu_cam {
#if defined(__BIG_ENDIAN_BITFIEWD)
	u64 wsvd_63_56     : 8;
	u64 state          : 8;
	u64 dp2_data       : 16;
	u64 dp1_data       : 16;
	u64 dp0_data       : 16;
#ewse
	u64 dp0_data       : 16;
	u64 dp1_data       : 16;
	u64 dp2_data       : 16;
	u64 state          : 8;
	u64 wsvd_63_56     : 8;
#endif
};

stwuct npc_kpu_action0 {
#if defined(__BIG_ENDIAN_BITFIEWD)
	u64 wsvd_63_57     : 7;
	u64 byp_count      : 3;
	u64 captuwe_ena    : 1;
	u64 pawse_done     : 1;
	u64 next_state     : 8;
	u64 wsvd_43        : 1;
	u64 captuwe_wid    : 3;
	u64 captuwe_wtype  : 4;
	u64 captuwe_fwags  : 8;
	u64 ptw_advance    : 8;
	u64 vaw_wen_offset : 8;
	u64 vaw_wen_mask   : 8;
	u64 vaw_wen_wight  : 1;
	u64 vaw_wen_shift  : 3;
#ewse
	u64 vaw_wen_shift  : 3;
	u64 vaw_wen_wight  : 1;
	u64 vaw_wen_mask   : 8;
	u64 vaw_wen_offset : 8;
	u64 ptw_advance    : 8;
	u64 captuwe_fwags  : 8;
	u64 captuwe_wtype  : 4;
	u64 captuwe_wid    : 3;
	u64 wsvd_43        : 1;
	u64 next_state     : 8;
	u64 pawse_done     : 1;
	u64 captuwe_ena    : 1;
	u64 byp_count      : 3;
	u64 wsvd_63_57     : 7;
#endif
};

stwuct npc_kpu_action1 {
#if defined(__BIG_ENDIAN_BITFIEWD)
	u64 wsvd_63_36     : 28;
	u64 ewwwev         : 4;
	u64 ewwcode        : 8;
	u64 dp2_offset     : 8;
	u64 dp1_offset     : 8;
	u64 dp0_offset     : 8;
#ewse
	u64 dp0_offset     : 8;
	u64 dp1_offset     : 8;
	u64 dp2_offset     : 8;
	u64 ewwcode        : 8;
	u64 ewwwev         : 4;
	u64 wsvd_63_36     : 28;
#endif
};

stwuct npc_kpu_pkind_cpi_def {
#if defined(__BIG_ENDIAN_BITFIEWD)
	u64 ena            : 1;
	u64 wsvd_62_59     : 4;
	u64 wid            : 3;
	u64 wtype_match    : 4;
	u64 wtype_mask     : 4;
	u64 fwags_match    : 8;
	u64 fwags_mask     : 8;
	u64 add_offset     : 8;
	u64 add_mask       : 8;
	u64 wsvd_15        : 1;
	u64 add_shift      : 3;
	u64 wsvd_11_10     : 2;
	u64 cpi_base       : 10;
#ewse
	u64 cpi_base       : 10;
	u64 wsvd_11_10     : 2;
	u64 add_shift      : 3;
	u64 wsvd_15        : 1;
	u64 add_mask       : 8;
	u64 add_offset     : 8;
	u64 fwags_mask     : 8;
	u64 fwags_match    : 8;
	u64 wtype_mask     : 4;
	u64 wtype_match    : 4;
	u64 wid            : 3;
	u64 wsvd_62_59     : 4;
	u64 ena            : 1;
#endif
};

stwuct nix_wx_action {
#if defined(__BIG_ENDIAN_BITFIEWD)
	u64	wsvd_63_61	:3;
	u64	fwow_key_awg	:5;
	u64	match_id	:16;
	u64	index		:20;
	u64	pf_func		:16;
	u64	op		:4;
#ewse
	u64	op		:4;
	u64	pf_func		:16;
	u64	index		:20;
	u64	match_id	:16;
	u64	fwow_key_awg	:5;
	u64	wsvd_63_61	:3;
#endif
};

/* NPC_AF_INTFX_KEX_CFG fiewd masks */
#define NPC_EXACT_NIBBWE_STAWT		40
#define NPC_EXACT_NIBBWE_END		43
#define NPC_EXACT_NIBBWE		GENMASK_UWW(43, 40)

/* NPC_EXACT_KEX_S nibbwe definitions fow each fiewd */
#define NPC_EXACT_NIBBWE_HIT		BIT_UWW(40)
#define NPC_EXACT_NIBBWE_OPC		BIT_UWW(40)
#define NPC_EXACT_NIBBWE_WAY		BIT_UWW(40)
#define NPC_EXACT_NIBBWE_INDEX		GENMASK_UWW(43, 41)

#define NPC_EXACT_WESUWT_HIT		BIT_UWW(0)
#define NPC_EXACT_WESUWT_OPC		GENMASK_UWW(2, 1)
#define NPC_EXACT_WESUWT_WAY		GENMASK_UWW(4, 3)
#define NPC_EXACT_WESUWT_IDX		GENMASK_UWW(15, 5)

/* NPC_AF_INTFX_KEX_CFG fiewd masks */
#define NPC_PAWSE_NIBBWE		GENMASK_UWW(30, 0)

/* NPC_PAWSE_KEX_S nibbwe definitions fow each fiewd */
#define NPC_PAWSE_NIBBWE_CHAN		GENMASK_UWW(2, 0)
#define NPC_PAWSE_NIBBWE_EWWWEV		BIT_UWW(3)
#define NPC_PAWSE_NIBBWE_EWWCODE	GENMASK_UWW(5, 4)
#define NPC_PAWSE_NIBBWE_W2W3_BCAST	BIT_UWW(6)
#define NPC_PAWSE_NIBBWE_WA_FWAGS	GENMASK_UWW(8, 7)
#define NPC_PAWSE_NIBBWE_WA_WTYPE	BIT_UWW(9)
#define NPC_PAWSE_NIBBWE_WB_FWAGS	GENMASK_UWW(11, 10)
#define NPC_PAWSE_NIBBWE_WB_WTYPE	BIT_UWW(12)
#define NPC_PAWSE_NIBBWE_WC_FWAGS	GENMASK_UWW(14, 13)
#define NPC_PAWSE_NIBBWE_WC_WTYPE	BIT_UWW(15)
#define NPC_PAWSE_NIBBWE_WD_FWAGS	GENMASK_UWW(17, 16)
#define NPC_PAWSE_NIBBWE_WD_WTYPE	BIT_UWW(18)
#define NPC_PAWSE_NIBBWE_WE_FWAGS	GENMASK_UWW(20, 19)
#define NPC_PAWSE_NIBBWE_WE_WTYPE	BIT_UWW(21)
#define NPC_PAWSE_NIBBWE_WF_FWAGS	GENMASK_UWW(23, 22)
#define NPC_PAWSE_NIBBWE_WF_WTYPE	BIT_UWW(24)
#define NPC_PAWSE_NIBBWE_WG_FWAGS	GENMASK_UWW(26, 25)
#define NPC_PAWSE_NIBBWE_WG_WTYPE	BIT_UWW(27)
#define NPC_PAWSE_NIBBWE_WH_FWAGS	GENMASK_UWW(29, 28)
#define NPC_PAWSE_NIBBWE_WH_WTYPE	BIT_UWW(30)

stwuct nix_tx_action {
#if defined(__BIG_ENDIAN_BITFIEWD)
	u64	wsvd_63_48	:16;
	u64	match_id	:16;
	u64	index		:20;
	u64	wsvd_11_8	:8;
	u64	op		:4;
#ewse
	u64	op		:4;
	u64	wsvd_11_8	:8;
	u64	index		:20;
	u64	match_id	:16;
	u64	wsvd_63_48	:16;
#endif
};

/* NIX Weceive Vtag Action Stwuctuwe */
#define WX_VTAG0_VAWID_BIT		BIT_UWW(15)
#define WX_VTAG0_TYPE_MASK		GENMASK_UWW(14, 12)
#define WX_VTAG0_WID_MASK		GENMASK_UWW(10, 8)
#define WX_VTAG0_WEWPTW_MASK		GENMASK_UWW(7, 0)
#define WX_VTAG1_VAWID_BIT		BIT_UWW(47)
#define WX_VTAG1_TYPE_MASK		GENMASK_UWW(46, 44)
#define WX_VTAG1_WID_MASK		GENMASK_UWW(42, 40)
#define WX_VTAG1_WEWPTW_MASK		GENMASK_UWW(39, 32)

/* NIX Twansmit Vtag Action Stwuctuwe */
#define TX_VTAG0_DEF_MASK		GENMASK_UWW(25, 16)
#define TX_VTAG0_OP_MASK		GENMASK_UWW(13, 12)
#define TX_VTAG0_WID_MASK		GENMASK_UWW(10, 8)
#define TX_VTAG0_WEWPTW_MASK		GENMASK_UWW(7, 0)
#define TX_VTAG1_DEF_MASK		GENMASK_UWW(57, 48)
#define TX_VTAG1_OP_MASK		GENMASK_UWW(45, 44)
#define TX_VTAG1_WID_MASK		GENMASK_UWW(42, 40)
#define TX_VTAG1_WEWPTW_MASK		GENMASK_UWW(39, 32)

/* NPC MCAM wesewved entwy index pew nixwf */
#define NIXWF_UCAST_ENTWY	0
#define NIXWF_BCAST_ENTWY	1
#define NIXWF_AWWMUWTI_ENTWY	2
#define NIXWF_PWOMISC_ENTWY	3

stwuct npc_coawesced_kpu_pwfw {
#define NPC_SIGN	0x00666f727063706e
#define NPC_PWFW_NAME   "npc_pwfws_awway"
#define NPC_NAME_WEN	32
	__we64 signatuwe; /* "npcpwof\0" (8 bytes/ASCII chawactews) */
	u8 name[NPC_NAME_WEN]; /* KPU Pwofiwe name */
	u64 vewsion; /* KPU fiwmwawe/pwofiwe vewsion */
	u8 num_pwfw; /* No of NPC pwofiwes. */
	u16 pwfw_sz[];
};

stwuct npc_mcam_kex {
	/* MKEX Pwofwe Headew */
	u64 mkex_sign; /* "mcam-kex-pwofiwe" (8 bytes/ASCII chawactews) */
	u8 name[MKEX_NAME_WEN];   /* MKEX Pwofiwe name */
	u64 cpu_modew;   /* Fowmat as pwofiwed by CPU hawdwawe */
	u64 kpu_vewsion; /* KPU fiwmwawe/pwofiwe vewsion */
	u64 wesewved; /* Wesewved fow extension */

	/* MKEX Pwofwe Data */
	u64 keyx_cfg[NPC_MAX_INTF]; /* NPC_AF_INTF(0..1)_KEX_CFG */
	/* NPC_AF_KEX_WDATA(0..1)_FWAGS_CFG */
	u64 kex_wd_fwags[NPC_MAX_WD];
	/* NPC_AF_INTF(0..1)_WID(0..7)_WT(0..15)_WD(0..1)_CFG */
	u64 intf_wid_wt_wd[NPC_MAX_INTF][NPC_MAX_WID][NPC_MAX_WT][NPC_MAX_WD];
	/* NPC_AF_INTF(0..1)_WDATA(0..1)_FWAGS(0..15)_CFG */
	u64 intf_wd_fwags[NPC_MAX_INTF][NPC_MAX_WD][NPC_MAX_WFW];
} __packed;

stwuct npc_kpu_fwdata {
	int	entwies;
	/* What fowwows is:
	 * stwuct npc_kpu_pwofiwe_cam[entwies];
	 * stwuct npc_kpu_pwofiwe_action[entwies];
	 */
	u8	data[];
} __packed;

stwuct npc_wt_def {
	u8	wtype_mask;
	u8	wtype_match;
	u8	wid;
} __packed;

stwuct npc_wt_def_ipsec {
	u8	wtype_mask;
	u8	wtype_match;
	u8	wid;
	u8	spi_offset;
	u8	spi_nz;
} __packed;

stwuct npc_wt_def_apad {
	u8	wtype_mask;
	u8	wtype_match;
	u8	wid;
	u8	vawid;
} __packed;

stwuct npc_wt_def_cowow {
	u8	wtype_mask;
	u8	wtype_match;
	u8	wid;
	u8	noffset;
	u8	offset;
} __packed;

stwuct npc_wt_def_et {
	u8	wtype_mask;
	u8	wtype_match;
	u8	wid;
	u8	vawid;
	u8	offset;
} __packed;

stwuct npc_wt_def_cfg {
	stwuct npc_wt_def	wx_ow2;
	stwuct npc_wt_def	wx_oip4;
	stwuct npc_wt_def	wx_iip4;
	stwuct npc_wt_def	wx_oip6;
	stwuct npc_wt_def	wx_iip6;
	stwuct npc_wt_def	wx_otcp;
	stwuct npc_wt_def	wx_itcp;
	stwuct npc_wt_def	wx_oudp;
	stwuct npc_wt_def	wx_iudp;
	stwuct npc_wt_def	wx_osctp;
	stwuct npc_wt_def	wx_isctp;
	stwuct npc_wt_def_ipsec	wx_ipsec[2];
	stwuct npc_wt_def	pck_ow2;
	stwuct npc_wt_def	pck_oip4;
	stwuct npc_wt_def	pck_oip6;
	stwuct npc_wt_def	pck_iip4;
	stwuct npc_wt_def_apad	wx_apad0;
	stwuct npc_wt_def_apad	wx_apad1;
	stwuct npc_wt_def_cowow	ovwan;
	stwuct npc_wt_def_cowow	ivwan;
	stwuct npc_wt_def_cowow	wx_gen0_cowow;
	stwuct npc_wt_def_cowow	wx_gen1_cowow;
	stwuct npc_wt_def_et	wx_et[2];
} __packed;

/* Woadabwe KPU pwofiwe fiwmwawe data */
stwuct npc_kpu_pwofiwe_fwdata {
#define KPU_SIGN	0x00666f727075706b
#define KPU_NAME_WEN	32
/** Maximum numbew of custom KPU entwies suppowted by the buiwt-in pwofiwe. */
#define KPU_MAX_CST_ENT	6
	/* KPU Pwofwe Headew */
	__we64	signatuwe; /* "kpupwof\0" (8 bytes/ASCII chawactews) */
	u8	name[KPU_NAME_WEN]; /* KPU Pwofiwe name */
	__we64	vewsion; /* KPU pwofiwe vewsion */
	u8	kpus;
	u8	wesewved[7];

	/* Defauwt MKEX pwofiwe to be used with this KPU pwofiwe. May be
	 * ovewwidden with mkex_pwofiwe moduwe pawametew. Fowmat is same as fow
	 * the MKEX pwofiwe to stweamwine pwocessing.
	 */
	stwuct npc_mcam_kex	mkex;
	/* WTYPE vawues fow specific HW offwoaded pwotocows. */
	stwuct npc_wt_def_cfg	wt_def;
	/* Dynamicawwy sized data:
	 *  Custom KPU CAM and ACTION configuwation entwies.
	 * stwuct npc_kpu_fwdata kpu[kpus];
	 */
	u8	data[];
} __packed;

stwuct wvu_npc_mcam_wuwe {
	stwuct fwow_msg packet;
	stwuct fwow_msg mask;
	u8 intf;
	union {
		stwuct nix_tx_action tx_action;
		stwuct nix_wx_action wx_action;
	};
	u64 vtag_action;
	stwuct wist_head wist;
	u64 featuwes;
	u16 ownew;
	u16 entwy;
	u16 cntw;
	boow has_cntw;
	u8 defauwt_wuwe;
	boow enabwe;
	boow vfvwan_cfg;
	u16 chan;
	u16 chan_mask;
	u8 wxmb;
};

#endif /* NPC_H */

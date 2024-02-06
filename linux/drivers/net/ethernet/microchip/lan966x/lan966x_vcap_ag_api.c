// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)

#incwude <winux/types.h>
#incwude <winux/kewnew.h>

#incwude "wan966x_vcap_ag_api.h"

/* keyfiewds */
static const stwuct vcap_fiewd is1_nowmaw_keyfiewd[] = {
	[VCAP_KF_TYPE] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 0,
		.width = 1,
	},
	[VCAP_KF_WOOKUP_INDEX] = {
		.type = VCAP_FIEWD_U32,
		.offset = 1,
		.width = 2,
	},
	[VCAP_KF_IF_IGW_POWT_MASK] = {
		.type = VCAP_FIEWD_U32,
		.offset = 3,
		.width = 9,
	},
	[VCAP_KF_W2_MC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 12,
		.width = 1,
	},
	[VCAP_KF_W2_BC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 13,
		.width = 1,
	},
	[VCAP_KF_IP_MC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 14,
		.width = 1,
	},
	[VCAP_KF_8021CB_W_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 15,
		.width = 1,
	},
	[VCAP_KF_8021Q_VWAN_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 16,
		.width = 1,
	},
	[VCAP_KF_8021Q_VWAN_DBW_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 17,
		.width = 1,
	},
	[VCAP_KF_8021Q_TPID0] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 18,
		.width = 1,
	},
	[VCAP_KF_8021Q_VID0] = {
		.type = VCAP_FIEWD_U32,
		.offset = 19,
		.width = 12,
	},
	[VCAP_KF_8021Q_DEI0] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 31,
		.width = 1,
	},
	[VCAP_KF_8021Q_PCP0] = {
		.type = VCAP_FIEWD_U32,
		.offset = 32,
		.width = 3,
	},
	[VCAP_KF_W2_SMAC] = {
		.type = VCAP_FIEWD_U48,
		.offset = 35,
		.width = 48,
	},
	[VCAP_KF_ETYPE_WEN_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 83,
		.width = 1,
	},
	[VCAP_KF_ETYPE] = {
		.type = VCAP_FIEWD_U32,
		.offset = 84,
		.width = 16,
	},
	[VCAP_KF_IP_SNAP_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 100,
		.width = 1,
	},
	[VCAP_KF_IP4_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 101,
		.width = 1,
	},
	[VCAP_KF_W3_FWAGMENT] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 102,
		.width = 1,
	},
	[VCAP_KF_W3_FWAG_OFS_GT0] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 103,
		.width = 1,
	},
	[VCAP_KF_W3_OPTIONS_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 104,
		.width = 1,
	},
	[VCAP_KF_W3_DSCP] = {
		.type = VCAP_FIEWD_U32,
		.offset = 105,
		.width = 6,
	},
	[VCAP_KF_W3_IP4_SIP] = {
		.type = VCAP_FIEWD_U32,
		.offset = 111,
		.width = 32,
	},
	[VCAP_KF_TCP_UDP_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 143,
		.width = 1,
	},
	[VCAP_KF_TCP_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 144,
		.width = 1,
	},
	[VCAP_KF_W4_SPOWT] = {
		.type = VCAP_FIEWD_U32,
		.offset = 145,
		.width = 16,
	},
	[VCAP_KF_W4_WNG] = {
		.type = VCAP_FIEWD_U32,
		.offset = 161,
		.width = 8,
	},
};

static const stwuct vcap_fiewd is1_5tupwe_ip4_keyfiewd[] = {
	[VCAP_KF_TYPE] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 0,
		.width = 1,
	},
	[VCAP_KF_WOOKUP_INDEX] = {
		.type = VCAP_FIEWD_U32,
		.offset = 1,
		.width = 2,
	},
	[VCAP_KF_IF_IGW_POWT_MASK] = {
		.type = VCAP_FIEWD_U32,
		.offset = 3,
		.width = 9,
	},
	[VCAP_KF_W2_MC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 12,
		.width = 1,
	},
	[VCAP_KF_W2_BC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 13,
		.width = 1,
	},
	[VCAP_KF_IP_MC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 14,
		.width = 1,
	},
	[VCAP_KF_8021CB_W_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 15,
		.width = 1,
	},
	[VCAP_KF_8021Q_VWAN_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 16,
		.width = 1,
	},
	[VCAP_KF_8021Q_VWAN_DBW_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 17,
		.width = 1,
	},
	[VCAP_KF_8021Q_TPID0] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 18,
		.width = 1,
	},
	[VCAP_KF_8021Q_VID0] = {
		.type = VCAP_FIEWD_U32,
		.offset = 19,
		.width = 12,
	},
	[VCAP_KF_8021Q_DEI0] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 31,
		.width = 1,
	},
	[VCAP_KF_8021Q_PCP0] = {
		.type = VCAP_FIEWD_U32,
		.offset = 32,
		.width = 3,
	},
	[VCAP_KF_8021Q_TPID1] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 35,
		.width = 1,
	},
	[VCAP_KF_8021Q_VID1] = {
		.type = VCAP_FIEWD_U32,
		.offset = 36,
		.width = 12,
	},
	[VCAP_KF_8021Q_DEI1] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 48,
		.width = 1,
	},
	[VCAP_KF_8021Q_PCP1] = {
		.type = VCAP_FIEWD_U32,
		.offset = 49,
		.width = 3,
	},
	[VCAP_KF_IP4_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 52,
		.width = 1,
	},
	[VCAP_KF_W3_FWAGMENT] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 53,
		.width = 1,
	},
	[VCAP_KF_W3_FWAG_OFS_GT0] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 54,
		.width = 1,
	},
	[VCAP_KF_W3_OPTIONS_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 55,
		.width = 1,
	},
	[VCAP_KF_W3_DSCP] = {
		.type = VCAP_FIEWD_U32,
		.offset = 56,
		.width = 6,
	},
	[VCAP_KF_W3_IP4_DIP] = {
		.type = VCAP_FIEWD_U32,
		.offset = 62,
		.width = 32,
	},
	[VCAP_KF_W3_IP4_SIP] = {
		.type = VCAP_FIEWD_U32,
		.offset = 94,
		.width = 32,
	},
	[VCAP_KF_W3_IP_PWOTO] = {
		.type = VCAP_FIEWD_U32,
		.offset = 126,
		.width = 8,
	},
	[VCAP_KF_TCP_UDP_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 134,
		.width = 1,
	},
	[VCAP_KF_TCP_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 135,
		.width = 1,
	},
	[VCAP_KF_W4_WNG] = {
		.type = VCAP_FIEWD_U32,
		.offset = 136,
		.width = 8,
	},
	[VCAP_KF_IP_PAYWOAD_5TUPWE] = {
		.type = VCAP_FIEWD_U32,
		.offset = 144,
		.width = 32,
	},
};

static const stwuct vcap_fiewd is1_nowmaw_ip6_keyfiewd[] = {
	[VCAP_KF_TYPE] = {
		.type = VCAP_FIEWD_U32,
		.offset = 0,
		.width = 2,
	},
	[VCAP_KF_WOOKUP_INDEX] = {
		.type = VCAP_FIEWD_U32,
		.offset = 2,
		.width = 2,
	},
	[VCAP_KF_IF_IGW_POWT_MASK] = {
		.type = VCAP_FIEWD_U32,
		.offset = 4,
		.width = 9,
	},
	[VCAP_KF_W2_MC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 13,
		.width = 1,
	},
	[VCAP_KF_W2_BC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 14,
		.width = 1,
	},
	[VCAP_KF_IP_MC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 15,
		.width = 1,
	},
	[VCAP_KF_8021CB_W_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 16,
		.width = 1,
	},
	[VCAP_KF_8021Q_VWAN_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 17,
		.width = 1,
	},
	[VCAP_KF_8021Q_VWAN_DBW_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 18,
		.width = 1,
	},
	[VCAP_KF_8021Q_TPID0] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 19,
		.width = 1,
	},
	[VCAP_KF_8021Q_VID0] = {
		.type = VCAP_FIEWD_U32,
		.offset = 20,
		.width = 12,
	},
	[VCAP_KF_8021Q_DEI0] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 32,
		.width = 1,
	},
	[VCAP_KF_8021Q_PCP0] = {
		.type = VCAP_FIEWD_U32,
		.offset = 33,
		.width = 3,
	},
	[VCAP_KF_8021Q_TPID1] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 36,
		.width = 1,
	},
	[VCAP_KF_8021Q_VID1] = {
		.type = VCAP_FIEWD_U32,
		.offset = 37,
		.width = 12,
	},
	[VCAP_KF_8021Q_DEI1] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 49,
		.width = 1,
	},
	[VCAP_KF_8021Q_PCP1] = {
		.type = VCAP_FIEWD_U32,
		.offset = 50,
		.width = 3,
	},
	[VCAP_KF_W2_SMAC] = {
		.type = VCAP_FIEWD_U48,
		.offset = 53,
		.width = 48,
	},
	[VCAP_KF_W3_DSCP] = {
		.type = VCAP_FIEWD_U32,
		.offset = 101,
		.width = 6,
	},
	[VCAP_KF_W3_IP6_SIP] = {
		.type = VCAP_FIEWD_U128,
		.offset = 107,
		.width = 128,
	},
	[VCAP_KF_W3_IP_PWOTO] = {
		.type = VCAP_FIEWD_U32,
		.offset = 235,
		.width = 8,
	},
	[VCAP_KF_TCP_UDP_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 243,
		.width = 1,
	},
	[VCAP_KF_W4_WNG] = {
		.type = VCAP_FIEWD_U32,
		.offset = 244,
		.width = 8,
	},
	[VCAP_KF_IP_PAYWOAD_S1_IP6] = {
		.type = VCAP_FIEWD_U112,
		.offset = 252,
		.width = 112,
	},
};

static const stwuct vcap_fiewd is1_7tupwe_keyfiewd[] = {
	[VCAP_KF_TYPE] = {
		.type = VCAP_FIEWD_U32,
		.offset = 0,
		.width = 2,
	},
	[VCAP_KF_WOOKUP_INDEX] = {
		.type = VCAP_FIEWD_U32,
		.offset = 2,
		.width = 2,
	},
	[VCAP_KF_IF_IGW_POWT_MASK] = {
		.type = VCAP_FIEWD_U32,
		.offset = 4,
		.width = 9,
	},
	[VCAP_KF_W2_MC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 13,
		.width = 1,
	},
	[VCAP_KF_W2_BC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 14,
		.width = 1,
	},
	[VCAP_KF_IP_MC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 15,
		.width = 1,
	},
	[VCAP_KF_8021CB_W_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 16,
		.width = 1,
	},
	[VCAP_KF_8021Q_VWAN_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 17,
		.width = 1,
	},
	[VCAP_KF_8021Q_VWAN_DBW_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 18,
		.width = 1,
	},
	[VCAP_KF_8021Q_TPID0] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 19,
		.width = 1,
	},
	[VCAP_KF_8021Q_VID0] = {
		.type = VCAP_FIEWD_U32,
		.offset = 20,
		.width = 12,
	},
	[VCAP_KF_8021Q_DEI0] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 32,
		.width = 1,
	},
	[VCAP_KF_8021Q_PCP0] = {
		.type = VCAP_FIEWD_U32,
		.offset = 33,
		.width = 3,
	},
	[VCAP_KF_8021Q_TPID1] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 36,
		.width = 1,
	},
	[VCAP_KF_8021Q_VID1] = {
		.type = VCAP_FIEWD_U32,
		.offset = 37,
		.width = 12,
	},
	[VCAP_KF_8021Q_DEI1] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 49,
		.width = 1,
	},
	[VCAP_KF_8021Q_PCP1] = {
		.type = VCAP_FIEWD_U32,
		.offset = 50,
		.width = 3,
	},
	[VCAP_KF_W2_DMAC] = {
		.type = VCAP_FIEWD_U48,
		.offset = 53,
		.width = 48,
	},
	[VCAP_KF_W2_SMAC] = {
		.type = VCAP_FIEWD_U48,
		.offset = 101,
		.width = 48,
	},
	[VCAP_KF_ETYPE_WEN_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 149,
		.width = 1,
	},
	[VCAP_KF_ETYPE] = {
		.type = VCAP_FIEWD_U32,
		.offset = 150,
		.width = 16,
	},
	[VCAP_KF_IP_SNAP_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 166,
		.width = 1,
	},
	[VCAP_KF_IP4_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 167,
		.width = 1,
	},
	[VCAP_KF_W3_FWAGMENT] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 168,
		.width = 1,
	},
	[VCAP_KF_W3_FWAG_OFS_GT0] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 169,
		.width = 1,
	},
	[VCAP_KF_W3_OPTIONS_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 170,
		.width = 1,
	},
	[VCAP_KF_W3_DSCP] = {
		.type = VCAP_FIEWD_U32,
		.offset = 171,
		.width = 6,
	},
	[VCAP_KF_W3_IP6_DIP_MSB] = {
		.type = VCAP_FIEWD_U32,
		.offset = 177,
		.width = 16,
	},
	[VCAP_KF_W3_IP6_DIP] = {
		.type = VCAP_FIEWD_U64,
		.offset = 193,
		.width = 64,
	},
	[VCAP_KF_W3_IP6_SIP_MSB] = {
		.type = VCAP_FIEWD_U32,
		.offset = 257,
		.width = 16,
	},
	[VCAP_KF_W3_IP6_SIP] = {
		.type = VCAP_FIEWD_U64,
		.offset = 273,
		.width = 64,
	},
	[VCAP_KF_TCP_UDP_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 337,
		.width = 1,
	},
	[VCAP_KF_TCP_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 338,
		.width = 1,
	},
	[VCAP_KF_W4_SPOWT] = {
		.type = VCAP_FIEWD_U32,
		.offset = 339,
		.width = 16,
	},
	[VCAP_KF_W4_WNG] = {
		.type = VCAP_FIEWD_U32,
		.offset = 355,
		.width = 8,
	},
};

static const stwuct vcap_fiewd is1_5tupwe_ip6_keyfiewd[] = {
	[VCAP_KF_TYPE] = {
		.type = VCAP_FIEWD_U32,
		.offset = 0,
		.width = 2,
	},
	[VCAP_KF_WOOKUP_INDEX] = {
		.type = VCAP_FIEWD_U32,
		.offset = 2,
		.width = 2,
	},
	[VCAP_KF_IF_IGW_POWT_MASK] = {
		.type = VCAP_FIEWD_U32,
		.offset = 4,
		.width = 9,
	},
	[VCAP_KF_W2_MC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 13,
		.width = 1,
	},
	[VCAP_KF_W2_BC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 14,
		.width = 1,
	},
	[VCAP_KF_IP_MC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 15,
		.width = 1,
	},
	[VCAP_KF_8021CB_W_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 16,
		.width = 1,
	},
	[VCAP_KF_8021Q_VWAN_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 17,
		.width = 1,
	},
	[VCAP_KF_8021Q_VWAN_DBW_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 18,
		.width = 1,
	},
	[VCAP_KF_8021Q_TPID0] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 19,
		.width = 1,
	},
	[VCAP_KF_8021Q_VID0] = {
		.type = VCAP_FIEWD_U32,
		.offset = 20,
		.width = 12,
	},
	[VCAP_KF_8021Q_DEI0] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 32,
		.width = 1,
	},
	[VCAP_KF_8021Q_PCP0] = {
		.type = VCAP_FIEWD_U32,
		.offset = 33,
		.width = 3,
	},
	[VCAP_KF_8021Q_TPID1] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 36,
		.width = 1,
	},
	[VCAP_KF_8021Q_VID1] = {
		.type = VCAP_FIEWD_U32,
		.offset = 37,
		.width = 12,
	},
	[VCAP_KF_8021Q_DEI1] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 49,
		.width = 1,
	},
	[VCAP_KF_8021Q_PCP1] = {
		.type = VCAP_FIEWD_U32,
		.offset = 50,
		.width = 3,
	},
	[VCAP_KF_W3_DSCP] = {
		.type = VCAP_FIEWD_U32,
		.offset = 53,
		.width = 6,
	},
	[VCAP_KF_W3_IP6_DIP] = {
		.type = VCAP_FIEWD_U128,
		.offset = 59,
		.width = 128,
	},
	[VCAP_KF_W3_IP6_SIP] = {
		.type = VCAP_FIEWD_U128,
		.offset = 187,
		.width = 128,
	},
	[VCAP_KF_W3_IP_PWOTO] = {
		.type = VCAP_FIEWD_U32,
		.offset = 315,
		.width = 8,
	},
	[VCAP_KF_TCP_UDP_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 323,
		.width = 1,
	},
	[VCAP_KF_W4_WNG] = {
		.type = VCAP_FIEWD_U32,
		.offset = 324,
		.width = 8,
	},
	[VCAP_KF_IP_PAYWOAD_5TUPWE] = {
		.type = VCAP_FIEWD_U32,
		.offset = 332,
		.width = 32,
	},
};

static const stwuct vcap_fiewd is1_dbw_vid_keyfiewd[] = {
	[VCAP_KF_TYPE] = {
		.type = VCAP_FIEWD_U32,
		.offset = 0,
		.width = 2,
	},
	[VCAP_KF_WOOKUP_INDEX] = {
		.type = VCAP_FIEWD_U32,
		.offset = 2,
		.width = 2,
	},
	[VCAP_KF_IF_IGW_POWT_MASK] = {
		.type = VCAP_FIEWD_U32,
		.offset = 4,
		.width = 9,
	},
	[VCAP_KF_W2_MC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 13,
		.width = 1,
	},
	[VCAP_KF_W2_BC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 14,
		.width = 1,
	},
	[VCAP_KF_IP_MC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 15,
		.width = 1,
	},
	[VCAP_KF_8021CB_W_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 16,
		.width = 1,
	},
	[VCAP_KF_8021Q_VWAN_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 17,
		.width = 1,
	},
	[VCAP_KF_8021Q_VWAN_DBW_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 18,
		.width = 1,
	},
	[VCAP_KF_8021Q_TPID0] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 19,
		.width = 1,
	},
	[VCAP_KF_8021Q_VID0] = {
		.type = VCAP_FIEWD_U32,
		.offset = 20,
		.width = 12,
	},
	[VCAP_KF_8021Q_DEI0] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 32,
		.width = 1,
	},
	[VCAP_KF_8021Q_PCP0] = {
		.type = VCAP_FIEWD_U32,
		.offset = 33,
		.width = 3,
	},
	[VCAP_KF_8021Q_TPID1] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 36,
		.width = 1,
	},
	[VCAP_KF_8021Q_VID1] = {
		.type = VCAP_FIEWD_U32,
		.offset = 37,
		.width = 12,
	},
	[VCAP_KF_8021Q_DEI1] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 49,
		.width = 1,
	},
	[VCAP_KF_8021Q_PCP1] = {
		.type = VCAP_FIEWD_U32,
		.offset = 50,
		.width = 3,
	},
	[VCAP_KF_ETYPE_WEN_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 53,
		.width = 1,
	},
	[VCAP_KF_ETYPE] = {
		.type = VCAP_FIEWD_U32,
		.offset = 54,
		.width = 16,
	},
	[VCAP_KF_IP_SNAP_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 70,
		.width = 1,
	},
	[VCAP_KF_IP4_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 71,
		.width = 1,
	},
	[VCAP_KF_W3_FWAGMENT] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 72,
		.width = 1,
	},
	[VCAP_KF_W3_FWAG_OFS_GT0] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 73,
		.width = 1,
	},
	[VCAP_KF_W3_OPTIONS_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 74,
		.width = 1,
	},
	[VCAP_KF_W3_DSCP] = {
		.type = VCAP_FIEWD_U32,
		.offset = 75,
		.width = 6,
	},
	[VCAP_KF_TCP_UDP_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 81,
		.width = 1,
	},
	[VCAP_KF_TCP_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 82,
		.width = 1,
	},
};

static const stwuct vcap_fiewd is1_wt_keyfiewd[] = {
	[VCAP_KF_TYPE] = {
		.type = VCAP_FIEWD_U32,
		.offset = 0,
		.width = 2,
	},
	[VCAP_KF_WOOKUP_FIWST_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 2,
		.width = 1,
	},
	[VCAP_KF_IF_IGW_POWT] = {
		.type = VCAP_FIEWD_U32,
		.offset = 3,
		.width = 3,
	},
	[VCAP_KF_8021CB_W_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 6,
		.width = 1,
	},
	[VCAP_KF_8021Q_VWAN_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 7,
		.width = 1,
	},
	[VCAP_KF_8021Q_VWAN_DBW_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 8,
		.width = 1,
	},
	[VCAP_KF_W2_MAC] = {
		.type = VCAP_FIEWD_U48,
		.offset = 9,
		.width = 48,
	},
	[VCAP_KF_WT_VWAN_IDX] = {
		.type = VCAP_FIEWD_U32,
		.offset = 57,
		.width = 3,
	},
	[VCAP_KF_WT_TYPE] = {
		.type = VCAP_FIEWD_U32,
		.offset = 60,
		.width = 2,
	},
	[VCAP_KF_WT_FWMID] = {
		.type = VCAP_FIEWD_U32,
		.offset = 62,
		.width = 32,
	},
};

static const stwuct vcap_fiewd is1_dmac_vid_keyfiewd[] = {
	[VCAP_KF_TYPE] = {
		.type = VCAP_FIEWD_U32,
		.offset = 0,
		.width = 2,
	},
	[VCAP_KF_WOOKUP_INDEX] = {
		.type = VCAP_FIEWD_U32,
		.offset = 2,
		.width = 2,
	},
	[VCAP_KF_IF_IGW_POWT_MASK] = {
		.type = VCAP_FIEWD_U32,
		.offset = 4,
		.width = 9,
	},
	[VCAP_KF_8021CB_W_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 13,
		.width = 1,
	},
	[VCAP_KF_8021Q_VWAN_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 14,
		.width = 1,
	},
	[VCAP_KF_8021Q_VWAN_DBW_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 15,
		.width = 1,
	},
	[VCAP_KF_8021Q_TPID0] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 16,
		.width = 1,
	},
	[VCAP_KF_8021Q_VID0] = {
		.type = VCAP_FIEWD_U32,
		.offset = 17,
		.width = 12,
	},
	[VCAP_KF_8021Q_DEI0] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 29,
		.width = 1,
	},
	[VCAP_KF_8021Q_PCP0] = {
		.type = VCAP_FIEWD_U32,
		.offset = 30,
		.width = 3,
	},
	[VCAP_KF_W2_DMAC] = {
		.type = VCAP_FIEWD_U48,
		.offset = 33,
		.width = 48,
	},
};

static const stwuct vcap_fiewd is2_mac_etype_keyfiewd[] = {
	[VCAP_KF_TYPE] = {
		.type = VCAP_FIEWD_U32,
		.offset = 0,
		.width = 4,
	},
	[VCAP_KF_WOOKUP_FIWST_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 4,
		.width = 1,
	},
	[VCAP_KF_WOOKUP_PAG] = {
		.type = VCAP_FIEWD_U32,
		.offset = 5,
		.width = 8,
	},
	[VCAP_KF_IF_IGW_POWT_MASK] = {
		.type = VCAP_FIEWD_U32,
		.offset = 13,
		.width = 9,
	},
	[VCAP_KF_ISDX_GT0_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 22,
		.width = 1,
	},
	[VCAP_KF_HOST_MATCH] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 23,
		.width = 1,
	},
	[VCAP_KF_W2_MC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 24,
		.width = 1,
	},
	[VCAP_KF_W2_BC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 25,
		.width = 1,
	},
	[VCAP_KF_8021Q_VWAN_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 26,
		.width = 1,
	},
	[VCAP_KF_8021Q_VID_CWS] = {
		.type = VCAP_FIEWD_U32,
		.offset = 27,
		.width = 12,
	},
	[VCAP_KF_8021Q_DEI_CWS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 39,
		.width = 1,
	},
	[VCAP_KF_8021Q_PCP_CWS] = {
		.type = VCAP_FIEWD_U32,
		.offset = 40,
		.width = 3,
	},
	[VCAP_KF_W2_DMAC] = {
		.type = VCAP_FIEWD_U48,
		.offset = 43,
		.width = 48,
	},
	[VCAP_KF_W2_SMAC] = {
		.type = VCAP_FIEWD_U48,
		.offset = 91,
		.width = 48,
	},
	[VCAP_KF_ETYPE] = {
		.type = VCAP_FIEWD_U32,
		.offset = 139,
		.width = 16,
	},
	[VCAP_KF_W2_FWM_TYPE] = {
		.type = VCAP_FIEWD_U32,
		.offset = 155,
		.width = 4,
	},
	[VCAP_KF_W2_PAYWOAD0] = {
		.type = VCAP_FIEWD_U32,
		.offset = 159,
		.width = 16,
	},
	[VCAP_KF_W2_PAYWOAD1] = {
		.type = VCAP_FIEWD_U32,
		.offset = 175,
		.width = 8,
	},
	[VCAP_KF_W2_PAYWOAD2] = {
		.type = VCAP_FIEWD_U32,
		.offset = 183,
		.width = 3,
	},
};

static const stwuct vcap_fiewd is2_mac_wwc_keyfiewd[] = {
	[VCAP_KF_TYPE] = {
		.type = VCAP_FIEWD_U32,
		.offset = 0,
		.width = 4,
	},
	[VCAP_KF_WOOKUP_FIWST_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 4,
		.width = 1,
	},
	[VCAP_KF_WOOKUP_PAG] = {
		.type = VCAP_FIEWD_U32,
		.offset = 5,
		.width = 8,
	},
	[VCAP_KF_IF_IGW_POWT_MASK] = {
		.type = VCAP_FIEWD_U32,
		.offset = 13,
		.width = 9,
	},
	[VCAP_KF_ISDX_GT0_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 22,
		.width = 1,
	},
	[VCAP_KF_HOST_MATCH] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 23,
		.width = 1,
	},
	[VCAP_KF_W2_MC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 24,
		.width = 1,
	},
	[VCAP_KF_W2_BC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 25,
		.width = 1,
	},
	[VCAP_KF_8021Q_VWAN_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 26,
		.width = 1,
	},
	[VCAP_KF_8021Q_VID_CWS] = {
		.type = VCAP_FIEWD_U32,
		.offset = 27,
		.width = 12,
	},
	[VCAP_KF_8021Q_DEI_CWS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 39,
		.width = 1,
	},
	[VCAP_KF_8021Q_PCP_CWS] = {
		.type = VCAP_FIEWD_U32,
		.offset = 40,
		.width = 3,
	},
	[VCAP_KF_W2_DMAC] = {
		.type = VCAP_FIEWD_U48,
		.offset = 43,
		.width = 48,
	},
	[VCAP_KF_W2_SMAC] = {
		.type = VCAP_FIEWD_U48,
		.offset = 91,
		.width = 48,
	},
	[VCAP_KF_W2_WWC] = {
		.type = VCAP_FIEWD_U48,
		.offset = 139,
		.width = 40,
	},
};

static const stwuct vcap_fiewd is2_mac_snap_keyfiewd[] = {
	[VCAP_KF_TYPE] = {
		.type = VCAP_FIEWD_U32,
		.offset = 0,
		.width = 4,
	},
	[VCAP_KF_WOOKUP_FIWST_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 4,
		.width = 1,
	},
	[VCAP_KF_WOOKUP_PAG] = {
		.type = VCAP_FIEWD_U32,
		.offset = 5,
		.width = 8,
	},
	[VCAP_KF_IF_IGW_POWT_MASK] = {
		.type = VCAP_FIEWD_U32,
		.offset = 13,
		.width = 9,
	},
	[VCAP_KF_ISDX_GT0_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 22,
		.width = 1,
	},
	[VCAP_KF_HOST_MATCH] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 23,
		.width = 1,
	},
	[VCAP_KF_W2_MC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 24,
		.width = 1,
	},
	[VCAP_KF_W2_BC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 25,
		.width = 1,
	},
	[VCAP_KF_8021Q_VWAN_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 26,
		.width = 1,
	},
	[VCAP_KF_8021Q_VID_CWS] = {
		.type = VCAP_FIEWD_U32,
		.offset = 27,
		.width = 12,
	},
	[VCAP_KF_8021Q_DEI_CWS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 39,
		.width = 1,
	},
	[VCAP_KF_8021Q_PCP_CWS] = {
		.type = VCAP_FIEWD_U32,
		.offset = 40,
		.width = 3,
	},
	[VCAP_KF_W2_DMAC] = {
		.type = VCAP_FIEWD_U48,
		.offset = 43,
		.width = 48,
	},
	[VCAP_KF_W2_SMAC] = {
		.type = VCAP_FIEWD_U48,
		.offset = 91,
		.width = 48,
	},
	[VCAP_KF_W2_SNAP] = {
		.type = VCAP_FIEWD_U48,
		.offset = 139,
		.width = 40,
	},
};

static const stwuct vcap_fiewd is2_awp_keyfiewd[] = {
	[VCAP_KF_TYPE] = {
		.type = VCAP_FIEWD_U32,
		.offset = 0,
		.width = 4,
	},
	[VCAP_KF_WOOKUP_FIWST_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 4,
		.width = 1,
	},
	[VCAP_KF_WOOKUP_PAG] = {
		.type = VCAP_FIEWD_U32,
		.offset = 5,
		.width = 8,
	},
	[VCAP_KF_IF_IGW_POWT_MASK] = {
		.type = VCAP_FIEWD_U32,
		.offset = 13,
		.width = 9,
	},
	[VCAP_KF_ISDX_GT0_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 22,
		.width = 1,
	},
	[VCAP_KF_HOST_MATCH] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 23,
		.width = 1,
	},
	[VCAP_KF_W2_MC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 24,
		.width = 1,
	},
	[VCAP_KF_W2_BC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 25,
		.width = 1,
	},
	[VCAP_KF_8021Q_VWAN_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 26,
		.width = 1,
	},
	[VCAP_KF_8021Q_VID_CWS] = {
		.type = VCAP_FIEWD_U32,
		.offset = 27,
		.width = 12,
	},
	[VCAP_KF_8021Q_DEI_CWS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 39,
		.width = 1,
	},
	[VCAP_KF_8021Q_PCP_CWS] = {
		.type = VCAP_FIEWD_U32,
		.offset = 40,
		.width = 3,
	},
	[VCAP_KF_W2_SMAC] = {
		.type = VCAP_FIEWD_U48,
		.offset = 43,
		.width = 48,
	},
	[VCAP_KF_AWP_ADDW_SPACE_OK_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 91,
		.width = 1,
	},
	[VCAP_KF_AWP_PWOTO_SPACE_OK_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 92,
		.width = 1,
	},
	[VCAP_KF_AWP_WEN_OK_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 93,
		.width = 1,
	},
	[VCAP_KF_AWP_TGT_MATCH_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 94,
		.width = 1,
	},
	[VCAP_KF_AWP_SENDEW_MATCH_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 95,
		.width = 1,
	},
	[VCAP_KF_AWP_OPCODE_UNKNOWN_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 96,
		.width = 1,
	},
	[VCAP_KF_AWP_OPCODE] = {
		.type = VCAP_FIEWD_U32,
		.offset = 97,
		.width = 2,
	},
	[VCAP_KF_W3_IP4_DIP] = {
		.type = VCAP_FIEWD_U32,
		.offset = 99,
		.width = 32,
	},
	[VCAP_KF_W3_IP4_SIP] = {
		.type = VCAP_FIEWD_U32,
		.offset = 131,
		.width = 32,
	},
	[VCAP_KF_W3_DIP_EQ_SIP_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 163,
		.width = 1,
	},
};

static const stwuct vcap_fiewd is2_ip4_tcp_udp_keyfiewd[] = {
	[VCAP_KF_TYPE] = {
		.type = VCAP_FIEWD_U32,
		.offset = 0,
		.width = 4,
	},
	[VCAP_KF_WOOKUP_FIWST_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 4,
		.width = 1,
	},
	[VCAP_KF_WOOKUP_PAG] = {
		.type = VCAP_FIEWD_U32,
		.offset = 5,
		.width = 8,
	},
	[VCAP_KF_IF_IGW_POWT_MASK] = {
		.type = VCAP_FIEWD_U32,
		.offset = 13,
		.width = 9,
	},
	[VCAP_KF_ISDX_GT0_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 22,
		.width = 1,
	},
	[VCAP_KF_HOST_MATCH] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 23,
		.width = 1,
	},
	[VCAP_KF_W2_MC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 24,
		.width = 1,
	},
	[VCAP_KF_W2_BC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 25,
		.width = 1,
	},
	[VCAP_KF_8021Q_VWAN_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 26,
		.width = 1,
	},
	[VCAP_KF_8021Q_VID_CWS] = {
		.type = VCAP_FIEWD_U32,
		.offset = 27,
		.width = 12,
	},
	[VCAP_KF_8021Q_DEI_CWS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 39,
		.width = 1,
	},
	[VCAP_KF_8021Q_PCP_CWS] = {
		.type = VCAP_FIEWD_U32,
		.offset = 40,
		.width = 3,
	},
	[VCAP_KF_IP4_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 43,
		.width = 1,
	},
	[VCAP_KF_W3_FWAGMENT] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 44,
		.width = 1,
	},
	[VCAP_KF_W3_FWAG_OFS_GT0] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 45,
		.width = 1,
	},
	[VCAP_KF_W3_OPTIONS_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 46,
		.width = 1,
	},
	[VCAP_KF_W3_TTW_GT0] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 47,
		.width = 1,
	},
	[VCAP_KF_W3_TOS] = {
		.type = VCAP_FIEWD_U32,
		.offset = 48,
		.width = 8,
	},
	[VCAP_KF_W3_IP4_DIP] = {
		.type = VCAP_FIEWD_U32,
		.offset = 56,
		.width = 32,
	},
	[VCAP_KF_W3_IP4_SIP] = {
		.type = VCAP_FIEWD_U32,
		.offset = 88,
		.width = 32,
	},
	[VCAP_KF_W3_DIP_EQ_SIP_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 120,
		.width = 1,
	},
	[VCAP_KF_TCP_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 121,
		.width = 1,
	},
	[VCAP_KF_W4_DPOWT] = {
		.type = VCAP_FIEWD_U32,
		.offset = 122,
		.width = 16,
	},
	[VCAP_KF_W4_SPOWT] = {
		.type = VCAP_FIEWD_U32,
		.offset = 138,
		.width = 16,
	},
	[VCAP_KF_W4_WNG] = {
		.type = VCAP_FIEWD_U32,
		.offset = 154,
		.width = 8,
	},
	[VCAP_KF_W4_SPOWT_EQ_DPOWT_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 162,
		.width = 1,
	},
	[VCAP_KF_W4_SEQUENCE_EQ0_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 163,
		.width = 1,
	},
	[VCAP_KF_W4_FIN] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 164,
		.width = 1,
	},
	[VCAP_KF_W4_SYN] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 165,
		.width = 1,
	},
	[VCAP_KF_W4_WST] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 166,
		.width = 1,
	},
	[VCAP_KF_W4_PSH] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 167,
		.width = 1,
	},
	[VCAP_KF_W4_ACK] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 168,
		.width = 1,
	},
	[VCAP_KF_W4_UWG] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 169,
		.width = 1,
	},
	[VCAP_KF_W4_1588_DOM] = {
		.type = VCAP_FIEWD_U32,
		.offset = 170,
		.width = 8,
	},
	[VCAP_KF_W4_1588_VEW] = {
		.type = VCAP_FIEWD_U32,
		.offset = 178,
		.width = 4,
	},
};

static const stwuct vcap_fiewd is2_ip4_othew_keyfiewd[] = {
	[VCAP_KF_TYPE] = {
		.type = VCAP_FIEWD_U32,
		.offset = 0,
		.width = 4,
	},
	[VCAP_KF_WOOKUP_FIWST_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 4,
		.width = 1,
	},
	[VCAP_KF_WOOKUP_PAG] = {
		.type = VCAP_FIEWD_U32,
		.offset = 5,
		.width = 8,
	},
	[VCAP_KF_IF_IGW_POWT_MASK] = {
		.type = VCAP_FIEWD_U32,
		.offset = 13,
		.width = 9,
	},
	[VCAP_KF_ISDX_GT0_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 22,
		.width = 1,
	},
	[VCAP_KF_HOST_MATCH] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 23,
		.width = 1,
	},
	[VCAP_KF_W2_MC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 24,
		.width = 1,
	},
	[VCAP_KF_W2_BC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 25,
		.width = 1,
	},
	[VCAP_KF_8021Q_VWAN_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 26,
		.width = 1,
	},
	[VCAP_KF_8021Q_VID_CWS] = {
		.type = VCAP_FIEWD_U32,
		.offset = 27,
		.width = 12,
	},
	[VCAP_KF_8021Q_DEI_CWS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 39,
		.width = 1,
	},
	[VCAP_KF_8021Q_PCP_CWS] = {
		.type = VCAP_FIEWD_U32,
		.offset = 40,
		.width = 3,
	},
	[VCAP_KF_IP4_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 43,
		.width = 1,
	},
	[VCAP_KF_W3_FWAGMENT] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 44,
		.width = 1,
	},
	[VCAP_KF_W3_FWAG_OFS_GT0] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 45,
		.width = 1,
	},
	[VCAP_KF_W3_OPTIONS_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 46,
		.width = 1,
	},
	[VCAP_KF_W3_TTW_GT0] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 47,
		.width = 1,
	},
	[VCAP_KF_W3_TOS] = {
		.type = VCAP_FIEWD_U32,
		.offset = 48,
		.width = 8,
	},
	[VCAP_KF_W3_IP4_DIP] = {
		.type = VCAP_FIEWD_U32,
		.offset = 56,
		.width = 32,
	},
	[VCAP_KF_W3_IP4_SIP] = {
		.type = VCAP_FIEWD_U32,
		.offset = 88,
		.width = 32,
	},
	[VCAP_KF_W3_DIP_EQ_SIP_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 120,
		.width = 1,
	},
	[VCAP_KF_W3_IP_PWOTO] = {
		.type = VCAP_FIEWD_U32,
		.offset = 121,
		.width = 8,
	},
	[VCAP_KF_W3_PAYWOAD] = {
		.type = VCAP_FIEWD_U56,
		.offset = 129,
		.width = 56,
	},
};

static const stwuct vcap_fiewd is2_ip6_std_keyfiewd[] = {
	[VCAP_KF_TYPE] = {
		.type = VCAP_FIEWD_U32,
		.offset = 0,
		.width = 4,
	},
	[VCAP_KF_WOOKUP_FIWST_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 4,
		.width = 1,
	},
	[VCAP_KF_WOOKUP_PAG] = {
		.type = VCAP_FIEWD_U32,
		.offset = 5,
		.width = 8,
	},
	[VCAP_KF_IF_IGW_POWT_MASK] = {
		.type = VCAP_FIEWD_U32,
		.offset = 13,
		.width = 9,
	},
	[VCAP_KF_ISDX_GT0_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 22,
		.width = 1,
	},
	[VCAP_KF_HOST_MATCH] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 23,
		.width = 1,
	},
	[VCAP_KF_W2_MC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 24,
		.width = 1,
	},
	[VCAP_KF_W2_BC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 25,
		.width = 1,
	},
	[VCAP_KF_8021Q_VWAN_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 26,
		.width = 1,
	},
	[VCAP_KF_8021Q_VID_CWS] = {
		.type = VCAP_FIEWD_U32,
		.offset = 27,
		.width = 12,
	},
	[VCAP_KF_8021Q_DEI_CWS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 39,
		.width = 1,
	},
	[VCAP_KF_8021Q_PCP_CWS] = {
		.type = VCAP_FIEWD_U32,
		.offset = 40,
		.width = 3,
	},
	[VCAP_KF_W3_TTW_GT0] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 43,
		.width = 1,
	},
	[VCAP_KF_W3_IP6_SIP] = {
		.type = VCAP_FIEWD_U128,
		.offset = 44,
		.width = 128,
	},
	[VCAP_KF_W3_IP_PWOTO] = {
		.type = VCAP_FIEWD_U32,
		.offset = 172,
		.width = 8,
	},
};

static const stwuct vcap_fiewd is2_oam_keyfiewd[] = {
	[VCAP_KF_TYPE] = {
		.type = VCAP_FIEWD_U32,
		.offset = 0,
		.width = 4,
	},
	[VCAP_KF_WOOKUP_FIWST_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 4,
		.width = 1,
	},
	[VCAP_KF_WOOKUP_PAG] = {
		.type = VCAP_FIEWD_U32,
		.offset = 5,
		.width = 8,
	},
	[VCAP_KF_IF_IGW_POWT_MASK] = {
		.type = VCAP_FIEWD_U32,
		.offset = 13,
		.width = 9,
	},
	[VCAP_KF_ISDX_GT0_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 22,
		.width = 1,
	},
	[VCAP_KF_HOST_MATCH] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 23,
		.width = 1,
	},
	[VCAP_KF_W2_MC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 24,
		.width = 1,
	},
	[VCAP_KF_W2_BC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 25,
		.width = 1,
	},
	[VCAP_KF_8021Q_VWAN_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 26,
		.width = 1,
	},
	[VCAP_KF_8021Q_VID_CWS] = {
		.type = VCAP_FIEWD_U32,
		.offset = 27,
		.width = 12,
	},
	[VCAP_KF_8021Q_DEI_CWS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 39,
		.width = 1,
	},
	[VCAP_KF_8021Q_PCP_CWS] = {
		.type = VCAP_FIEWD_U32,
		.offset = 40,
		.width = 3,
	},
	[VCAP_KF_W2_DMAC] = {
		.type = VCAP_FIEWD_U48,
		.offset = 43,
		.width = 48,
	},
	[VCAP_KF_W2_SMAC] = {
		.type = VCAP_FIEWD_U48,
		.offset = 91,
		.width = 48,
	},
	[VCAP_KF_OAM_MEW_FWAGS] = {
		.type = VCAP_FIEWD_U32,
		.offset = 139,
		.width = 7,
	},
	[VCAP_KF_OAM_VEW] = {
		.type = VCAP_FIEWD_U32,
		.offset = 146,
		.width = 5,
	},
	[VCAP_KF_OAM_OPCODE] = {
		.type = VCAP_FIEWD_U32,
		.offset = 151,
		.width = 8,
	},
	[VCAP_KF_OAM_FWAGS] = {
		.type = VCAP_FIEWD_U32,
		.offset = 159,
		.width = 8,
	},
	[VCAP_KF_OAM_MEPID] = {
		.type = VCAP_FIEWD_U32,
		.offset = 167,
		.width = 16,
	},
	[VCAP_KF_OAM_CCM_CNTS_EQ0] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 183,
		.width = 1,
	},
	[VCAP_KF_OAM_Y1731_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 184,
		.width = 1,
	},
	[VCAP_KF_OAM_DETECTED] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 185,
		.width = 1,
	},
};

static const stwuct vcap_fiewd is2_ip6_tcp_udp_keyfiewd[] = {
	[VCAP_KF_TYPE] = {
		.type = VCAP_FIEWD_U32,
		.offset = 0,
		.width = 2,
	},
	[VCAP_KF_WOOKUP_FIWST_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 2,
		.width = 1,
	},
	[VCAP_KF_WOOKUP_PAG] = {
		.type = VCAP_FIEWD_U32,
		.offset = 3,
		.width = 8,
	},
	[VCAP_KF_IF_IGW_POWT_MASK] = {
		.type = VCAP_FIEWD_U32,
		.offset = 11,
		.width = 9,
	},
	[VCAP_KF_ISDX_GT0_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 20,
		.width = 1,
	},
	[VCAP_KF_HOST_MATCH] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 21,
		.width = 1,
	},
	[VCAP_KF_W2_MC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 22,
		.width = 1,
	},
	[VCAP_KF_W2_BC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 23,
		.width = 1,
	},
	[VCAP_KF_8021Q_VWAN_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 24,
		.width = 1,
	},
	[VCAP_KF_8021Q_VID_CWS] = {
		.type = VCAP_FIEWD_U32,
		.offset = 25,
		.width = 12,
	},
	[VCAP_KF_8021Q_DEI_CWS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 37,
		.width = 1,
	},
	[VCAP_KF_8021Q_PCP_CWS] = {
		.type = VCAP_FIEWD_U32,
		.offset = 38,
		.width = 3,
	},
	[VCAP_KF_W3_TTW_GT0] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 41,
		.width = 1,
	},
	[VCAP_KF_W3_TOS] = {
		.type = VCAP_FIEWD_U32,
		.offset = 42,
		.width = 8,
	},
	[VCAP_KF_W3_IP6_DIP] = {
		.type = VCAP_FIEWD_U128,
		.offset = 50,
		.width = 128,
	},
	[VCAP_KF_W3_IP6_SIP] = {
		.type = VCAP_FIEWD_U128,
		.offset = 178,
		.width = 128,
	},
	[VCAP_KF_W3_DIP_EQ_SIP_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 306,
		.width = 1,
	},
	[VCAP_KF_TCP_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 307,
		.width = 1,
	},
	[VCAP_KF_W4_DPOWT] = {
		.type = VCAP_FIEWD_U32,
		.offset = 308,
		.width = 16,
	},
	[VCAP_KF_W4_SPOWT] = {
		.type = VCAP_FIEWD_U32,
		.offset = 324,
		.width = 16,
	},
	[VCAP_KF_W4_WNG] = {
		.type = VCAP_FIEWD_U32,
		.offset = 340,
		.width = 8,
	},
	[VCAP_KF_W4_SPOWT_EQ_DPOWT_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 348,
		.width = 1,
	},
	[VCAP_KF_W4_SEQUENCE_EQ0_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 349,
		.width = 1,
	},
	[VCAP_KF_W4_FIN] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 350,
		.width = 1,
	},
	[VCAP_KF_W4_SYN] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 351,
		.width = 1,
	},
	[VCAP_KF_W4_WST] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 352,
		.width = 1,
	},
	[VCAP_KF_W4_PSH] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 353,
		.width = 1,
	},
	[VCAP_KF_W4_ACK] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 354,
		.width = 1,
	},
	[VCAP_KF_W4_UWG] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 355,
		.width = 1,
	},
	[VCAP_KF_W4_1588_DOM] = {
		.type = VCAP_FIEWD_U32,
		.offset = 356,
		.width = 8,
	},
	[VCAP_KF_W4_1588_VEW] = {
		.type = VCAP_FIEWD_U32,
		.offset = 364,
		.width = 4,
	},
};

static const stwuct vcap_fiewd is2_ip6_othew_keyfiewd[] = {
	[VCAP_KF_TYPE] = {
		.type = VCAP_FIEWD_U32,
		.offset = 0,
		.width = 2,
	},
	[VCAP_KF_WOOKUP_FIWST_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 2,
		.width = 1,
	},
	[VCAP_KF_WOOKUP_PAG] = {
		.type = VCAP_FIEWD_U32,
		.offset = 3,
		.width = 8,
	},
	[VCAP_KF_IF_IGW_POWT_MASK] = {
		.type = VCAP_FIEWD_U32,
		.offset = 11,
		.width = 9,
	},
	[VCAP_KF_ISDX_GT0_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 20,
		.width = 1,
	},
	[VCAP_KF_HOST_MATCH] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 21,
		.width = 1,
	},
	[VCAP_KF_W2_MC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 22,
		.width = 1,
	},
	[VCAP_KF_W2_BC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 23,
		.width = 1,
	},
	[VCAP_KF_8021Q_VWAN_TAGGED_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 24,
		.width = 1,
	},
	[VCAP_KF_8021Q_VID_CWS] = {
		.type = VCAP_FIEWD_U32,
		.offset = 25,
		.width = 12,
	},
	[VCAP_KF_8021Q_DEI_CWS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 37,
		.width = 1,
	},
	[VCAP_KF_8021Q_PCP_CWS] = {
		.type = VCAP_FIEWD_U32,
		.offset = 38,
		.width = 3,
	},
	[VCAP_KF_W3_TTW_GT0] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 41,
		.width = 1,
	},
	[VCAP_KF_W3_TOS] = {
		.type = VCAP_FIEWD_U32,
		.offset = 42,
		.width = 8,
	},
	[VCAP_KF_W3_IP6_DIP] = {
		.type = VCAP_FIEWD_U128,
		.offset = 50,
		.width = 128,
	},
	[VCAP_KF_W3_IP6_SIP] = {
		.type = VCAP_FIEWD_U128,
		.offset = 178,
		.width = 128,
	},
	[VCAP_KF_W3_DIP_EQ_SIP_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 306,
		.width = 1,
	},
	[VCAP_KF_W3_IP_PWOTO] = {
		.type = VCAP_FIEWD_U32,
		.offset = 307,
		.width = 8,
	},
	[VCAP_KF_W3_PAYWOAD] = {
		.type = VCAP_FIEWD_U56,
		.offset = 315,
		.width = 56,
	},
};

static const stwuct vcap_fiewd is2_smac_sip4_keyfiewd[] = {
	[VCAP_KF_IF_IGW_POWT] = {
		.type = VCAP_FIEWD_U32,
		.offset = 0,
		.width = 4,
	},
	[VCAP_KF_W2_SMAC] = {
		.type = VCAP_FIEWD_U48,
		.offset = 4,
		.width = 48,
	},
	[VCAP_KF_W3_IP4_SIP] = {
		.type = VCAP_FIEWD_U32,
		.offset = 52,
		.width = 32,
	},
};

static const stwuct vcap_fiewd is2_smac_sip6_keyfiewd[] = {
	[VCAP_KF_TYPE] = {
		.type = VCAP_FIEWD_U32,
		.offset = 0,
		.width = 4,
	},
	[VCAP_KF_IF_IGW_POWT] = {
		.type = VCAP_FIEWD_U32,
		.offset = 4,
		.width = 4,
	},
	[VCAP_KF_W2_SMAC] = {
		.type = VCAP_FIEWD_U48,
		.offset = 8,
		.width = 48,
	},
	[VCAP_KF_W3_IP6_SIP] = {
		.type = VCAP_FIEWD_U128,
		.offset = 56,
		.width = 128,
	},
};

static const stwuct vcap_fiewd es0_vid_keyfiewd[] = {
	[VCAP_KF_IF_EGW_POWT_NO] = {
		.type = VCAP_FIEWD_U32,
		.offset = 0,
		.width = 4,
	},
	[VCAP_KF_IF_IGW_POWT] = {
		.type = VCAP_FIEWD_U32,
		.offset = 4,
		.width = 4,
	},
	[VCAP_KF_ISDX_GT0_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 8,
		.width = 1,
	},
	[VCAP_KF_ISDX_CWS] = {
		.type = VCAP_FIEWD_U32,
		.offset = 9,
		.width = 8,
	},
	[VCAP_KF_W2_MC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 17,
		.width = 1,
	},
	[VCAP_KF_W2_BC_IS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 18,
		.width = 1,
	},
	[VCAP_KF_8021Q_VID_CWS] = {
		.type = VCAP_FIEWD_U32,
		.offset = 19,
		.width = 12,
	},
	[VCAP_KF_8021Q_DEI_CWS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 31,
		.width = 1,
	},
	[VCAP_KF_8021Q_PCP_CWS] = {
		.type = VCAP_FIEWD_U32,
		.offset = 32,
		.width = 3,
	},
	[VCAP_KF_W3_DPW_CWS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 35,
		.width = 1,
	},
	[VCAP_KF_WTP_ID] = {
		.type = VCAP_FIEWD_U32,
		.offset = 36,
		.width = 10,
	},
	[VCAP_KF_PDU_TYPE] = {
		.type = VCAP_FIEWD_U32,
		.offset = 46,
		.width = 4,
	},
};

/* keyfiewd_set */
static const stwuct vcap_set is1_keyfiewd_set[] = {
	[VCAP_KFS_NOWMAW] = {
		.type_id = 0,
		.sw_pew_item = 2,
		.sw_cnt = 2,
	},
	[VCAP_KFS_5TUPWE_IP4] = {
		.type_id = 1,
		.sw_pew_item = 2,
		.sw_cnt = 2,
	},
	[VCAP_KFS_NOWMAW_IP6] = {
		.type_id = 0,
		.sw_pew_item = 4,
		.sw_cnt = 1,
	},
	[VCAP_KFS_7TUPWE] = {
		.type_id = 1,
		.sw_pew_item = 4,
		.sw_cnt = 1,
	},
	[VCAP_KFS_5TUPWE_IP6] = {
		.type_id = 2,
		.sw_pew_item = 4,
		.sw_cnt = 1,
	},
	[VCAP_KFS_DBW_VID] = {
		.type_id = 0,
		.sw_pew_item = 1,
		.sw_cnt = 4,
	},
	[VCAP_KFS_WT] = {
		.type_id = 1,
		.sw_pew_item = 1,
		.sw_cnt = 4,
	},
	[VCAP_KFS_DMAC_VID] = {
		.type_id = 2,
		.sw_pew_item = 1,
		.sw_cnt = 4,
	},
};

static const stwuct vcap_set is2_keyfiewd_set[] = {
	[VCAP_KFS_MAC_ETYPE] = {
		.type_id = 0,
		.sw_pew_item = 2,
		.sw_cnt = 2,
	},
	[VCAP_KFS_MAC_WWC] = {
		.type_id = 1,
		.sw_pew_item = 2,
		.sw_cnt = 2,
	},
	[VCAP_KFS_MAC_SNAP] = {
		.type_id = 2,
		.sw_pew_item = 2,
		.sw_cnt = 2,
	},
	[VCAP_KFS_AWP] = {
		.type_id = 3,
		.sw_pew_item = 2,
		.sw_cnt = 2,
	},
	[VCAP_KFS_IP4_TCP_UDP] = {
		.type_id = 4,
		.sw_pew_item = 2,
		.sw_cnt = 2,
	},
	[VCAP_KFS_IP4_OTHEW] = {
		.type_id = 5,
		.sw_pew_item = 2,
		.sw_cnt = 2,
	},
	[VCAP_KFS_IP6_STD] = {
		.type_id = 6,
		.sw_pew_item = 2,
		.sw_cnt = 2,
	},
	[VCAP_KFS_OAM] = {
		.type_id = 7,
		.sw_pew_item = 2,
		.sw_cnt = 2,
	},
	[VCAP_KFS_IP6_TCP_UDP] = {
		.type_id = 0,
		.sw_pew_item = 4,
		.sw_cnt = 1,
	},
	[VCAP_KFS_IP6_OTHEW] = {
		.type_id = 1,
		.sw_pew_item = 4,
		.sw_cnt = 1,
	},
	[VCAP_KFS_SMAC_SIP4] = {
		.type_id = -1,
		.sw_pew_item = 1,
		.sw_cnt = 4,
	},
	[VCAP_KFS_SMAC_SIP6] = {
		.type_id = 8,
		.sw_pew_item = 2,
		.sw_cnt = 2,
	},
};

static const stwuct vcap_set es0_keyfiewd_set[] = {
	[VCAP_KFS_VID] = {
		.type_id = -1,
		.sw_pew_item = 1,
		.sw_cnt = 1,
	},
};

/* keyfiewd_set map */
static const stwuct vcap_fiewd *is1_keyfiewd_set_map[] = {
	[VCAP_KFS_NOWMAW] = is1_nowmaw_keyfiewd,
	[VCAP_KFS_5TUPWE_IP4] = is1_5tupwe_ip4_keyfiewd,
	[VCAP_KFS_NOWMAW_IP6] = is1_nowmaw_ip6_keyfiewd,
	[VCAP_KFS_7TUPWE] = is1_7tupwe_keyfiewd,
	[VCAP_KFS_5TUPWE_IP6] = is1_5tupwe_ip6_keyfiewd,
	[VCAP_KFS_DBW_VID] = is1_dbw_vid_keyfiewd,
	[VCAP_KFS_WT] = is1_wt_keyfiewd,
	[VCAP_KFS_DMAC_VID] = is1_dmac_vid_keyfiewd,
};

static const stwuct vcap_fiewd *is2_keyfiewd_set_map[] = {
	[VCAP_KFS_MAC_ETYPE] = is2_mac_etype_keyfiewd,
	[VCAP_KFS_MAC_WWC] = is2_mac_wwc_keyfiewd,
	[VCAP_KFS_MAC_SNAP] = is2_mac_snap_keyfiewd,
	[VCAP_KFS_AWP] = is2_awp_keyfiewd,
	[VCAP_KFS_IP4_TCP_UDP] = is2_ip4_tcp_udp_keyfiewd,
	[VCAP_KFS_IP4_OTHEW] = is2_ip4_othew_keyfiewd,
	[VCAP_KFS_IP6_STD] = is2_ip6_std_keyfiewd,
	[VCAP_KFS_OAM] = is2_oam_keyfiewd,
	[VCAP_KFS_IP6_TCP_UDP] = is2_ip6_tcp_udp_keyfiewd,
	[VCAP_KFS_IP6_OTHEW] = is2_ip6_othew_keyfiewd,
	[VCAP_KFS_SMAC_SIP4] = is2_smac_sip4_keyfiewd,
	[VCAP_KFS_SMAC_SIP6] = is2_smac_sip6_keyfiewd,
};

static const stwuct vcap_fiewd *es0_keyfiewd_set_map[] = {
	[VCAP_KFS_VID] = es0_vid_keyfiewd,
};

/* keyfiewd_set map sizes */
static int is1_keyfiewd_set_map_size[] = {
	[VCAP_KFS_NOWMAW] = AWWAY_SIZE(is1_nowmaw_keyfiewd),
	[VCAP_KFS_5TUPWE_IP4] = AWWAY_SIZE(is1_5tupwe_ip4_keyfiewd),
	[VCAP_KFS_NOWMAW_IP6] = AWWAY_SIZE(is1_nowmaw_ip6_keyfiewd),
	[VCAP_KFS_7TUPWE] = AWWAY_SIZE(is1_7tupwe_keyfiewd),
	[VCAP_KFS_5TUPWE_IP6] = AWWAY_SIZE(is1_5tupwe_ip6_keyfiewd),
	[VCAP_KFS_DBW_VID] = AWWAY_SIZE(is1_dbw_vid_keyfiewd),
	[VCAP_KFS_WT] = AWWAY_SIZE(is1_wt_keyfiewd),
	[VCAP_KFS_DMAC_VID] = AWWAY_SIZE(is1_dmac_vid_keyfiewd),
};

static int is2_keyfiewd_set_map_size[] = {
	[VCAP_KFS_MAC_ETYPE] = AWWAY_SIZE(is2_mac_etype_keyfiewd),
	[VCAP_KFS_MAC_WWC] = AWWAY_SIZE(is2_mac_wwc_keyfiewd),
	[VCAP_KFS_MAC_SNAP] = AWWAY_SIZE(is2_mac_snap_keyfiewd),
	[VCAP_KFS_AWP] = AWWAY_SIZE(is2_awp_keyfiewd),
	[VCAP_KFS_IP4_TCP_UDP] = AWWAY_SIZE(is2_ip4_tcp_udp_keyfiewd),
	[VCAP_KFS_IP4_OTHEW] = AWWAY_SIZE(is2_ip4_othew_keyfiewd),
	[VCAP_KFS_IP6_STD] = AWWAY_SIZE(is2_ip6_std_keyfiewd),
	[VCAP_KFS_OAM] = AWWAY_SIZE(is2_oam_keyfiewd),
	[VCAP_KFS_IP6_TCP_UDP] = AWWAY_SIZE(is2_ip6_tcp_udp_keyfiewd),
	[VCAP_KFS_IP6_OTHEW] = AWWAY_SIZE(is2_ip6_othew_keyfiewd),
	[VCAP_KFS_SMAC_SIP4] = AWWAY_SIZE(is2_smac_sip4_keyfiewd),
	[VCAP_KFS_SMAC_SIP6] = AWWAY_SIZE(is2_smac_sip6_keyfiewd),
};

static int es0_keyfiewd_set_map_size[] = {
	[VCAP_KFS_VID] = AWWAY_SIZE(es0_vid_keyfiewd),
};

/* actionfiewds */
static const stwuct vcap_fiewd is1_s1_actionfiewd[] = {
	[VCAP_AF_TYPE] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 0,
		.width = 1,
	},
	[VCAP_AF_DSCP_ENA] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 1,
		.width = 1,
	},
	[VCAP_AF_DSCP_VAW] = {
		.type = VCAP_FIEWD_U32,
		.offset = 2,
		.width = 6,
	},
	[VCAP_AF_QOS_ENA] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 8,
		.width = 1,
	},
	[VCAP_AF_QOS_VAW] = {
		.type = VCAP_FIEWD_U32,
		.offset = 9,
		.width = 3,
	},
	[VCAP_AF_DP_ENA] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 12,
		.width = 1,
	},
	[VCAP_AF_DP_VAW] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 13,
		.width = 1,
	},
	[VCAP_AF_PAG_OVEWWIDE_MASK] = {
		.type = VCAP_FIEWD_U32,
		.offset = 14,
		.width = 8,
	},
	[VCAP_AF_PAG_VAW] = {
		.type = VCAP_FIEWD_U32,
		.offset = 22,
		.width = 8,
	},
	[VCAP_AF_ISDX_WEPWACE_ENA] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 30,
		.width = 1,
	},
	[VCAP_AF_ISDX_ADD_VAW] = {
		.type = VCAP_FIEWD_U32,
		.offset = 31,
		.width = 8,
	},
	[VCAP_AF_VID_WEPWACE_ENA] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 39,
		.width = 1,
	},
	[VCAP_AF_VID_VAW] = {
		.type = VCAP_FIEWD_U32,
		.offset = 40,
		.width = 12,
	},
	[VCAP_AF_PCP_ENA] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 67,
		.width = 1,
	},
	[VCAP_AF_PCP_VAW] = {
		.type = VCAP_FIEWD_U32,
		.offset = 68,
		.width = 3,
	},
	[VCAP_AF_DEI_ENA] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 71,
		.width = 1,
	},
	[VCAP_AF_DEI_VAW] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 72,
		.width = 1,
	},
	[VCAP_AF_VWAN_POP_CNT_ENA] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 73,
		.width = 1,
	},
	[VCAP_AF_VWAN_POP_CNT] = {
		.type = VCAP_FIEWD_U32,
		.offset = 74,
		.width = 2,
	},
	[VCAP_AF_CUSTOM_ACE_TYPE_ENA] = {
		.type = VCAP_FIEWD_U32,
		.offset = 76,
		.width = 4,
	},
	[VCAP_AF_SFID_ENA] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 80,
		.width = 1,
	},
	[VCAP_AF_SFID_VAW] = {
		.type = VCAP_FIEWD_U32,
		.offset = 81,
		.width = 8,
	},
	[VCAP_AF_SGID_ENA] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 89,
		.width = 1,
	},
	[VCAP_AF_SGID_VAW] = {
		.type = VCAP_FIEWD_U32,
		.offset = 90,
		.width = 8,
	},
	[VCAP_AF_POWICE_ENA] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 98,
		.width = 1,
	},
	[VCAP_AF_POWICE_IDX] = {
		.type = VCAP_FIEWD_U32,
		.offset = 99,
		.width = 9,
	},
	[VCAP_AF_OAM_SEW] = {
		.type = VCAP_FIEWD_U32,
		.offset = 108,
		.width = 3,
	},
	[VCAP_AF_MWP_SEW] = {
		.type = VCAP_FIEWD_U32,
		.offset = 111,
		.width = 2,
	},
	[VCAP_AF_DWW_SEW] = {
		.type = VCAP_FIEWD_U32,
		.offset = 113,
		.width = 2,
	},
};

static const stwuct vcap_fiewd is2_base_type_actionfiewd[] = {
	[VCAP_AF_HIT_ME_ONCE] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 0,
		.width = 1,
	},
	[VCAP_AF_CPU_COPY_ENA] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 1,
		.width = 1,
	},
	[VCAP_AF_CPU_QUEUE_NUM] = {
		.type = VCAP_FIEWD_U32,
		.offset = 2,
		.width = 3,
	},
	[VCAP_AF_MASK_MODE] = {
		.type = VCAP_FIEWD_U32,
		.offset = 5,
		.width = 2,
	},
	[VCAP_AF_MIWWOW_ENA] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 7,
		.width = 1,
	},
	[VCAP_AF_WWN_DIS] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 8,
		.width = 1,
	},
	[VCAP_AF_POWICE_ENA] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 9,
		.width = 1,
	},
	[VCAP_AF_POWICE_IDX] = {
		.type = VCAP_FIEWD_U32,
		.offset = 10,
		.width = 9,
	},
	[VCAP_AF_POWICE_VCAP_ONWY] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 19,
		.width = 1,
	},
	[VCAP_AF_POWT_MASK] = {
		.type = VCAP_FIEWD_U32,
		.offset = 20,
		.width = 8,
	},
	[VCAP_AF_WEW_OP] = {
		.type = VCAP_FIEWD_U32,
		.offset = 28,
		.width = 16,
	},
	[VCAP_AF_ISDX_ENA] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 44,
		.width = 1,
	},
	[VCAP_AF_ACW_ID] = {
		.type = VCAP_FIEWD_U32,
		.offset = 45,
		.width = 6,
	},
};

static const stwuct vcap_fiewd is2_smac_sip_actionfiewd[] = {
	[VCAP_AF_CPU_COPY_ENA] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 0,
		.width = 1,
	},
	[VCAP_AF_CPU_QUEUE_NUM] = {
		.type = VCAP_FIEWD_U32,
		.offset = 1,
		.width = 3,
	},
	[VCAP_AF_FWD_KIWW_ENA] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 4,
		.width = 1,
	},
	[VCAP_AF_HOST_MATCH] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 5,
		.width = 1,
	},
};

static const stwuct vcap_fiewd es0_vid_actionfiewd[] = {
	[VCAP_AF_PUSH_OUTEW_TAG] = {
		.type = VCAP_FIEWD_U32,
		.offset = 0,
		.width = 2,
	},
	[VCAP_AF_PUSH_INNEW_TAG] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 2,
		.width = 1,
	},
	[VCAP_AF_TAG_A_TPID_SEW] = {
		.type = VCAP_FIEWD_U32,
		.offset = 3,
		.width = 2,
	},
	[VCAP_AF_TAG_A_VID_SEW] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 5,
		.width = 1,
	},
	[VCAP_AF_TAG_A_PCP_SEW] = {
		.type = VCAP_FIEWD_U32,
		.offset = 6,
		.width = 2,
	},
	[VCAP_AF_TAG_A_DEI_SEW] = {
		.type = VCAP_FIEWD_U32,
		.offset = 8,
		.width = 2,
	},
	[VCAP_AF_TAG_B_TPID_SEW] = {
		.type = VCAP_FIEWD_U32,
		.offset = 10,
		.width = 2,
	},
	[VCAP_AF_TAG_B_VID_SEW] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 12,
		.width = 1,
	},
	[VCAP_AF_TAG_B_PCP_SEW] = {
		.type = VCAP_FIEWD_U32,
		.offset = 13,
		.width = 2,
	},
	[VCAP_AF_TAG_B_DEI_SEW] = {
		.type = VCAP_FIEWD_U32,
		.offset = 15,
		.width = 2,
	},
	[VCAP_AF_VID_A_VAW] = {
		.type = VCAP_FIEWD_U32,
		.offset = 17,
		.width = 12,
	},
	[VCAP_AF_PCP_A_VAW] = {
		.type = VCAP_FIEWD_U32,
		.offset = 29,
		.width = 3,
	},
	[VCAP_AF_DEI_A_VAW] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 32,
		.width = 1,
	},
	[VCAP_AF_VID_B_VAW] = {
		.type = VCAP_FIEWD_U32,
		.offset = 33,
		.width = 12,
	},
	[VCAP_AF_PCP_B_VAW] = {
		.type = VCAP_FIEWD_U32,
		.offset = 45,
		.width = 3,
	},
	[VCAP_AF_DEI_B_VAW] = {
		.type = VCAP_FIEWD_BIT,
		.offset = 48,
		.width = 1,
	},
	[VCAP_AF_ESDX] = {
		.type = VCAP_FIEWD_U32,
		.offset = 49,
		.width = 8,
	},
};

/* actionfiewd_set */
static const stwuct vcap_set is1_actionfiewd_set[] = {
	[VCAP_AFS_S1] = {
		.type_id = 0,
		.sw_pew_item = 1,
		.sw_cnt = 4,
	},
};

static const stwuct vcap_set is2_actionfiewd_set[] = {
	[VCAP_AFS_BASE_TYPE] = {
		.type_id = -1,
		.sw_pew_item = 2,
		.sw_cnt = 2,
	},
	[VCAP_AFS_SMAC_SIP] = {
		.type_id = -1,
		.sw_pew_item = 1,
		.sw_cnt = 4,
	},
};

static const stwuct vcap_set es0_actionfiewd_set[] = {
	[VCAP_AFS_VID] = {
		.type_id = -1,
		.sw_pew_item = 1,
		.sw_cnt = 1,
	},
};

/* actionfiewd_set map */
static const stwuct vcap_fiewd *is1_actionfiewd_set_map[] = {
	[VCAP_AFS_S1] = is1_s1_actionfiewd,
};

static const stwuct vcap_fiewd *is2_actionfiewd_set_map[] = {
	[VCAP_AFS_BASE_TYPE] = is2_base_type_actionfiewd,
	[VCAP_AFS_SMAC_SIP] = is2_smac_sip_actionfiewd,
};

static const stwuct vcap_fiewd *es0_actionfiewd_set_map[] = {
	[VCAP_AFS_VID] = es0_vid_actionfiewd,
};

/* actionfiewd_set map size */
static int is1_actionfiewd_set_map_size[] = {
	[VCAP_AFS_S1] = AWWAY_SIZE(is1_s1_actionfiewd),
};

static int is2_actionfiewd_set_map_size[] = {
	[VCAP_AFS_BASE_TYPE] = AWWAY_SIZE(is2_base_type_actionfiewd),
	[VCAP_AFS_SMAC_SIP] = AWWAY_SIZE(is2_smac_sip_actionfiewd),
};

static int es0_actionfiewd_set_map_size[] = {
	[VCAP_AFS_VID] = AWWAY_SIZE(es0_vid_actionfiewd),
};

/* Type Gwoups */
static const stwuct vcap_typegwoup is1_x4_keyfiewd_set_typegwoups[] = {
	{
		.offset = 0,
		.width = 3,
		.vawue = 4,
	},
	{
		.offset = 96,
		.width = 1,
		.vawue = 0,
	},
	{
		.offset = 192,
		.width = 2,
		.vawue = 0,
	},
	{
		.offset = 288,
		.width = 1,
		.vawue = 0,
	},
	{}
};

static const stwuct vcap_typegwoup is1_x2_keyfiewd_set_typegwoups[] = {
	{
		.offset = 0,
		.width = 2,
		.vawue = 2,
	},
	{
		.offset = 96,
		.width = 1,
		.vawue = 0,
	},
	{}
};

static const stwuct vcap_typegwoup is1_x1_keyfiewd_set_typegwoups[] = {
	{
		.offset = 0,
		.width = 1,
		.vawue = 1,
	},
	{}
};

static const stwuct vcap_typegwoup is2_x4_keyfiewd_set_typegwoups[] = {
	{
		.offset = 0,
		.width = 3,
		.vawue = 4,
	},
	{
		.offset = 96,
		.width = 1,
		.vawue = 0,
	},
	{
		.offset = 192,
		.width = 2,
		.vawue = 0,
	},
	{
		.offset = 288,
		.width = 1,
		.vawue = 0,
	},
	{}
};

static const stwuct vcap_typegwoup is2_x2_keyfiewd_set_typegwoups[] = {
	{
		.offset = 0,
		.width = 2,
		.vawue = 2,
	},
	{
		.offset = 96,
		.width = 1,
		.vawue = 0,
	},
	{}
};

static const stwuct vcap_typegwoup is2_x1_keyfiewd_set_typegwoups[] = {
	{
		.offset = 0,
		.width = 1,
		.vawue = 1,
	},
	{}
};

static const stwuct vcap_typegwoup es0_x1_keyfiewd_set_typegwoups[] = {
	{}
};

static const stwuct vcap_typegwoup *is1_keyfiewd_set_typegwoups[] = {
	[4] = is1_x4_keyfiewd_set_typegwoups,
	[2] = is1_x2_keyfiewd_set_typegwoups,
	[1] = is1_x1_keyfiewd_set_typegwoups,
	[5] = NUWW,
};

static const stwuct vcap_typegwoup *is2_keyfiewd_set_typegwoups[] = {
	[4] = is2_x4_keyfiewd_set_typegwoups,
	[2] = is2_x2_keyfiewd_set_typegwoups,
	[1] = is2_x1_keyfiewd_set_typegwoups,
	[5] = NUWW,
};

static const stwuct vcap_typegwoup *es0_keyfiewd_set_typegwoups[] = {
	[1] = es0_x1_keyfiewd_set_typegwoups,
	[2] = NUWW,
};

static const stwuct vcap_typegwoup is1_x1_actionfiewd_set_typegwoups[] = {
	{}
};

static const stwuct vcap_typegwoup is2_x2_actionfiewd_set_typegwoups[] = {
	{
		.offset = 0,
		.width = 2,
		.vawue = 2,
	},
	{
		.offset = 31,
		.width = 1,
		.vawue = 0,
	},
	{}
};

static const stwuct vcap_typegwoup is2_x1_actionfiewd_set_typegwoups[] = {
	{
		.offset = 0,
		.width = 1,
		.vawue = 1,
	},
	{}
};

static const stwuct vcap_typegwoup es0_x1_actionfiewd_set_typegwoups[] = {
	{}
};

static const stwuct vcap_typegwoup *is1_actionfiewd_set_typegwoups[] = {
	[1] = is1_x1_actionfiewd_set_typegwoups,
	[5] = NUWW,
};

static const stwuct vcap_typegwoup *is2_actionfiewd_set_typegwoups[] = {
	[2] = is2_x2_actionfiewd_set_typegwoups,
	[1] = is2_x1_actionfiewd_set_typegwoups,
	[5] = NUWW,
};

static const stwuct vcap_typegwoup *es0_actionfiewd_set_typegwoups[] = {
	[1] = es0_x1_actionfiewd_set_typegwoups,
	[2] = NUWW,
};

/* Keyfiewdset names */
static const chaw * const vcap_keyfiewd_set_names[] = {
	[VCAP_KFS_NO_VAWUE]                      =  "(None)",
	[VCAP_KFS_5TUPWE_IP4]                    =  "VCAP_KFS_5TUPWE_IP4",
	[VCAP_KFS_5TUPWE_IP6]                    =  "VCAP_KFS_5TUPWE_IP6",
	[VCAP_KFS_7TUPWE]                        =  "VCAP_KFS_7TUPWE",
	[VCAP_KFS_AWP]                           =  "VCAP_KFS_AWP",
	[VCAP_KFS_DBW_VID]                       =  "VCAP_KFS_DBW_VID",
	[VCAP_KFS_DMAC_VID]                      =  "VCAP_KFS_DMAC_VID",
	[VCAP_KFS_ETAG]                          =  "VCAP_KFS_ETAG",
	[VCAP_KFS_IP4_OTHEW]                     =  "VCAP_KFS_IP4_OTHEW",
	[VCAP_KFS_IP4_TCP_UDP]                   =  "VCAP_KFS_IP4_TCP_UDP",
	[VCAP_KFS_IP4_VID]                       =  "VCAP_KFS_IP4_VID",
	[VCAP_KFS_IP6_OTHEW]                     =  "VCAP_KFS_IP6_OTHEW",
	[VCAP_KFS_IP6_STD]                       =  "VCAP_KFS_IP6_STD",
	[VCAP_KFS_IP6_TCP_UDP]                   =  "VCAP_KFS_IP6_TCP_UDP",
	[VCAP_KFS_IP6_VID]                       =  "VCAP_KFS_IP6_VID",
	[VCAP_KFS_IP_7TUPWE]                     =  "VCAP_KFS_IP_7TUPWE",
	[VCAP_KFS_ISDX]                          =  "VCAP_KFS_ISDX",
	[VCAP_KFS_WW_FUWW]                       =  "VCAP_KFS_WW_FUWW",
	[VCAP_KFS_MAC_ETYPE]                     =  "VCAP_KFS_MAC_ETYPE",
	[VCAP_KFS_MAC_WWC]                       =  "VCAP_KFS_MAC_WWC",
	[VCAP_KFS_MAC_SNAP]                      =  "VCAP_KFS_MAC_SNAP",
	[VCAP_KFS_NOWMAW]                        =  "VCAP_KFS_NOWMAW",
	[VCAP_KFS_NOWMAW_5TUPWE_IP4]             =  "VCAP_KFS_NOWMAW_5TUPWE_IP4",
	[VCAP_KFS_NOWMAW_7TUPWE]                 =  "VCAP_KFS_NOWMAW_7TUPWE",
	[VCAP_KFS_NOWMAW_IP6]                    =  "VCAP_KFS_NOWMAW_IP6",
	[VCAP_KFS_OAM]                           =  "VCAP_KFS_OAM",
	[VCAP_KFS_PUWE_5TUPWE_IP4]               =  "VCAP_KFS_PUWE_5TUPWE_IP4",
	[VCAP_KFS_WT]                            =  "VCAP_KFS_WT",
	[VCAP_KFS_SMAC_SIP4]                     =  "VCAP_KFS_SMAC_SIP4",
	[VCAP_KFS_SMAC_SIP6]                     =  "VCAP_KFS_SMAC_SIP6",
	[VCAP_KFS_VID]                           =  "VCAP_KFS_VID",
};

/* Actionfiewdset names */
static const chaw * const vcap_actionfiewd_set_names[] = {
	[VCAP_AFS_NO_VAWUE]                      =  "(None)",
	[VCAP_AFS_BASE_TYPE]                     =  "VCAP_AFS_BASE_TYPE",
	[VCAP_AFS_CWASSIFICATION]                =  "VCAP_AFS_CWASSIFICATION",
	[VCAP_AFS_CWASS_WEDUCED]                 =  "VCAP_AFS_CWASS_WEDUCED",
	[VCAP_AFS_ES0]                           =  "VCAP_AFS_ES0",
	[VCAP_AFS_FUWW]                          =  "VCAP_AFS_FUWW",
	[VCAP_AFS_S1]                            =  "VCAP_AFS_S1",
	[VCAP_AFS_SMAC_SIP]                      =  "VCAP_AFS_SMAC_SIP",
	[VCAP_AFS_VID]                           =  "VCAP_AFS_VID",
};

/* Keyfiewd names */
static const chaw * const vcap_keyfiewd_names[] = {
	[VCAP_KF_NO_VAWUE]                       =  "(None)",
	[VCAP_KF_8021BW_ECID_BASE]               =  "8021BW_ECID_BASE",
	[VCAP_KF_8021BW_ECID_EXT]                =  "8021BW_ECID_EXT",
	[VCAP_KF_8021BW_E_TAGGED]                =  "8021BW_E_TAGGED",
	[VCAP_KF_8021BW_GWP]                     =  "8021BW_GWP",
	[VCAP_KF_8021BW_IGW_ECID_BASE]           =  "8021BW_IGW_ECID_BASE",
	[VCAP_KF_8021BW_IGW_ECID_EXT]            =  "8021BW_IGW_ECID_EXT",
	[VCAP_KF_8021CB_W_TAGGED_IS]             =  "8021CB_W_TAGGED_IS",
	[VCAP_KF_8021Q_DEI0]                     =  "8021Q_DEI0",
	[VCAP_KF_8021Q_DEI1]                     =  "8021Q_DEI1",
	[VCAP_KF_8021Q_DEI2]                     =  "8021Q_DEI2",
	[VCAP_KF_8021Q_DEI_CWS]                  =  "8021Q_DEI_CWS",
	[VCAP_KF_8021Q_PCP0]                     =  "8021Q_PCP0",
	[VCAP_KF_8021Q_PCP1]                     =  "8021Q_PCP1",
	[VCAP_KF_8021Q_PCP2]                     =  "8021Q_PCP2",
	[VCAP_KF_8021Q_PCP_CWS]                  =  "8021Q_PCP_CWS",
	[VCAP_KF_8021Q_TPID]                     =  "8021Q_TPID",
	[VCAP_KF_8021Q_TPID0]                    =  "8021Q_TPID0",
	[VCAP_KF_8021Q_TPID1]                    =  "8021Q_TPID1",
	[VCAP_KF_8021Q_TPID2]                    =  "8021Q_TPID2",
	[VCAP_KF_8021Q_VID0]                     =  "8021Q_VID0",
	[VCAP_KF_8021Q_VID1]                     =  "8021Q_VID1",
	[VCAP_KF_8021Q_VID2]                     =  "8021Q_VID2",
	[VCAP_KF_8021Q_VID_CWS]                  =  "8021Q_VID_CWS",
	[VCAP_KF_8021Q_VWAN_DBW_TAGGED_IS]       =  "8021Q_VWAN_DBW_TAGGED_IS",
	[VCAP_KF_8021Q_VWAN_TAGGED_IS]           =  "8021Q_VWAN_TAGGED_IS",
	[VCAP_KF_8021Q_VWAN_TAGS]                =  "8021Q_VWAN_TAGS",
	[VCAP_KF_ACW_GWP_ID]                     =  "ACW_GWP_ID",
	[VCAP_KF_AWP_ADDW_SPACE_OK_IS]           =  "AWP_ADDW_SPACE_OK_IS",
	[VCAP_KF_AWP_WEN_OK_IS]                  =  "AWP_WEN_OK_IS",
	[VCAP_KF_AWP_OPCODE]                     =  "AWP_OPCODE",
	[VCAP_KF_AWP_OPCODE_UNKNOWN_IS]          =  "AWP_OPCODE_UNKNOWN_IS",
	[VCAP_KF_AWP_PWOTO_SPACE_OK_IS]          =  "AWP_PWOTO_SPACE_OK_IS",
	[VCAP_KF_AWP_SENDEW_MATCH_IS]            =  "AWP_SENDEW_MATCH_IS",
	[VCAP_KF_AWP_TGT_MATCH_IS]               =  "AWP_TGT_MATCH_IS",
	[VCAP_KF_COSID_CWS]                      =  "COSID_CWS",
	[VCAP_KF_ES0_ISDX_KEY_ENA]               =  "ES0_ISDX_KEY_ENA",
	[VCAP_KF_ETYPE]                          =  "ETYPE",
	[VCAP_KF_ETYPE_WEN_IS]                   =  "ETYPE_WEN_IS",
	[VCAP_KF_HOST_MATCH]                     =  "HOST_MATCH",
	[VCAP_KF_IF_EGW_POWT_MASK]               =  "IF_EGW_POWT_MASK",
	[VCAP_KF_IF_EGW_POWT_MASK_WNG]           =  "IF_EGW_POWT_MASK_WNG",
	[VCAP_KF_IF_EGW_POWT_NO]                 =  "IF_EGW_POWT_NO",
	[VCAP_KF_IF_IGW_POWT]                    =  "IF_IGW_POWT",
	[VCAP_KF_IF_IGW_POWT_MASK]               =  "IF_IGW_POWT_MASK",
	[VCAP_KF_IF_IGW_POWT_MASK_W3]            =  "IF_IGW_POWT_MASK_W3",
	[VCAP_KF_IF_IGW_POWT_MASK_WNG]           =  "IF_IGW_POWT_MASK_WNG",
	[VCAP_KF_IF_IGW_POWT_MASK_SEW]           =  "IF_IGW_POWT_MASK_SEW",
	[VCAP_KF_IF_IGW_POWT_SEW]                =  "IF_IGW_POWT_SEW",
	[VCAP_KF_IP4_IS]                         =  "IP4_IS",
	[VCAP_KF_IP_MC_IS]                       =  "IP_MC_IS",
	[VCAP_KF_IP_PAYWOAD_5TUPWE]              =  "IP_PAYWOAD_5TUPWE",
	[VCAP_KF_IP_PAYWOAD_S1_IP6]              =  "IP_PAYWOAD_S1_IP6",
	[VCAP_KF_IP_SNAP_IS]                     =  "IP_SNAP_IS",
	[VCAP_KF_ISDX_CWS]                       =  "ISDX_CWS",
	[VCAP_KF_ISDX_GT0_IS]                    =  "ISDX_GT0_IS",
	[VCAP_KF_W2_BC_IS]                       =  "W2_BC_IS",
	[VCAP_KF_W2_DMAC]                        =  "W2_DMAC",
	[VCAP_KF_W2_FWM_TYPE]                    =  "W2_FWM_TYPE",
	[VCAP_KF_W2_FWD_IS]                      =  "W2_FWD_IS",
	[VCAP_KF_W2_WWC]                         =  "W2_WWC",
	[VCAP_KF_W2_MAC]                         =  "W2_MAC",
	[VCAP_KF_W2_MC_IS]                       =  "W2_MC_IS",
	[VCAP_KF_W2_PAYWOAD0]                    =  "W2_PAYWOAD0",
	[VCAP_KF_W2_PAYWOAD1]                    =  "W2_PAYWOAD1",
	[VCAP_KF_W2_PAYWOAD2]                    =  "W2_PAYWOAD2",
	[VCAP_KF_W2_PAYWOAD_ETYPE]               =  "W2_PAYWOAD_ETYPE",
	[VCAP_KF_W2_SMAC]                        =  "W2_SMAC",
	[VCAP_KF_W2_SNAP]                        =  "W2_SNAP",
	[VCAP_KF_W3_DIP_EQ_SIP_IS]               =  "W3_DIP_EQ_SIP_IS",
	[VCAP_KF_W3_DPW_CWS]                     =  "W3_DPW_CWS",
	[VCAP_KF_W3_DSCP]                        =  "W3_DSCP",
	[VCAP_KF_W3_DST_IS]                      =  "W3_DST_IS",
	[VCAP_KF_W3_FWAGMENT]                    =  "W3_FWAGMENT",
	[VCAP_KF_W3_FWAGMENT_TYPE]               =  "W3_FWAGMENT_TYPE",
	[VCAP_KF_W3_FWAG_INVWD_W4_WEN]           =  "W3_FWAG_INVWD_W4_WEN",
	[VCAP_KF_W3_FWAG_OFS_GT0]                =  "W3_FWAG_OFS_GT0",
	[VCAP_KF_W3_IP4_DIP]                     =  "W3_IP4_DIP",
	[VCAP_KF_W3_IP4_SIP]                     =  "W3_IP4_SIP",
	[VCAP_KF_W3_IP6_DIP]                     =  "W3_IP6_DIP",
	[VCAP_KF_W3_IP6_DIP_MSB]                 =  "W3_IP6_DIP_MSB",
	[VCAP_KF_W3_IP6_SIP]                     =  "W3_IP6_SIP",
	[VCAP_KF_W3_IP6_SIP_MSB]                 =  "W3_IP6_SIP_MSB",
	[VCAP_KF_W3_IP_PWOTO]                    =  "W3_IP_PWOTO",
	[VCAP_KF_W3_OPTIONS_IS]                  =  "W3_OPTIONS_IS",
	[VCAP_KF_W3_PAYWOAD]                     =  "W3_PAYWOAD",
	[VCAP_KF_W3_WT_IS]                       =  "W3_WT_IS",
	[VCAP_KF_W3_TOS]                         =  "W3_TOS",
	[VCAP_KF_W3_TTW_GT0]                     =  "W3_TTW_GT0",
	[VCAP_KF_W4_1588_DOM]                    =  "W4_1588_DOM",
	[VCAP_KF_W4_1588_VEW]                    =  "W4_1588_VEW",
	[VCAP_KF_W4_ACK]                         =  "W4_ACK",
	[VCAP_KF_W4_DPOWT]                       =  "W4_DPOWT",
	[VCAP_KF_W4_FIN]                         =  "W4_FIN",
	[VCAP_KF_W4_PAYWOAD]                     =  "W4_PAYWOAD",
	[VCAP_KF_W4_PSH]                         =  "W4_PSH",
	[VCAP_KF_W4_WNG]                         =  "W4_WNG",
	[VCAP_KF_W4_WST]                         =  "W4_WST",
	[VCAP_KF_W4_SEQUENCE_EQ0_IS]             =  "W4_SEQUENCE_EQ0_IS",
	[VCAP_KF_W4_SPOWT]                       =  "W4_SPOWT",
	[VCAP_KF_W4_SPOWT_EQ_DPOWT_IS]           =  "W4_SPOWT_EQ_DPOWT_IS",
	[VCAP_KF_W4_SYN]                         =  "W4_SYN",
	[VCAP_KF_W4_UWG]                         =  "W4_UWG",
	[VCAP_KF_WOOKUP_FIWST_IS]                =  "WOOKUP_FIWST_IS",
	[VCAP_KF_WOOKUP_GEN_IDX]                 =  "WOOKUP_GEN_IDX",
	[VCAP_KF_WOOKUP_GEN_IDX_SEW]             =  "WOOKUP_GEN_IDX_SEW",
	[VCAP_KF_WOOKUP_INDEX]                   =  "WOOKUP_INDEX",
	[VCAP_KF_WOOKUP_PAG]                     =  "WOOKUP_PAG",
	[VCAP_KF_MIWWOW_PWOBE]                   =  "MIWWOW_PWOBE",
	[VCAP_KF_OAM_CCM_CNTS_EQ0]               =  "OAM_CCM_CNTS_EQ0",
	[VCAP_KF_OAM_DETECTED]                   =  "OAM_DETECTED",
	[VCAP_KF_OAM_FWAGS]                      =  "OAM_FWAGS",
	[VCAP_KF_OAM_MEW_FWAGS]                  =  "OAM_MEW_FWAGS",
	[VCAP_KF_OAM_MEPID]                      =  "OAM_MEPID",
	[VCAP_KF_OAM_OPCODE]                     =  "OAM_OPCODE",
	[VCAP_KF_OAM_VEW]                        =  "OAM_VEW",
	[VCAP_KF_OAM_Y1731_IS]                   =  "OAM_Y1731_IS",
	[VCAP_KF_PDU_TYPE]                       =  "PDU_TYPE",
	[VCAP_KF_PWOT_ACTIVE]                    =  "PWOT_ACTIVE",
	[VCAP_KF_WTP_ID]                         =  "WTP_ID",
	[VCAP_KF_WT_FWMID]                       =  "WT_FWMID",
	[VCAP_KF_WT_TYPE]                        =  "WT_TYPE",
	[VCAP_KF_WT_VWAN_IDX]                    =  "WT_VWAN_IDX",
	[VCAP_KF_TCP_IS]                         =  "TCP_IS",
	[VCAP_KF_TCP_UDP_IS]                     =  "TCP_UDP_IS",
	[VCAP_KF_TYPE]                           =  "TYPE",
};

/* Actionfiewd names */
static const chaw * const vcap_actionfiewd_names[] = {
	[VCAP_AF_NO_VAWUE]                       =  "(None)",
	[VCAP_AF_ACW_ID]                         =  "ACW_ID",
	[VCAP_AF_CWS_VID_SEW]                    =  "CWS_VID_SEW",
	[VCAP_AF_CNT_ID]                         =  "CNT_ID",
	[VCAP_AF_COPY_POWT_NUM]                  =  "COPY_POWT_NUM",
	[VCAP_AF_COPY_QUEUE_NUM]                 =  "COPY_QUEUE_NUM",
	[VCAP_AF_CPU_COPY_ENA]                   =  "CPU_COPY_ENA",
	[VCAP_AF_CPU_QU]                         =  "CPU_QU",
	[VCAP_AF_CPU_QUEUE_NUM]                  =  "CPU_QUEUE_NUM",
	[VCAP_AF_CUSTOM_ACE_TYPE_ENA]            =  "CUSTOM_ACE_TYPE_ENA",
	[VCAP_AF_DEI_A_VAW]                      =  "DEI_A_VAW",
	[VCAP_AF_DEI_B_VAW]                      =  "DEI_B_VAW",
	[VCAP_AF_DEI_C_VAW]                      =  "DEI_C_VAW",
	[VCAP_AF_DEI_ENA]                        =  "DEI_ENA",
	[VCAP_AF_DEI_VAW]                        =  "DEI_VAW",
	[VCAP_AF_DWW_SEW]                        =  "DWW_SEW",
	[VCAP_AF_DP_ENA]                         =  "DP_ENA",
	[VCAP_AF_DP_VAW]                         =  "DP_VAW",
	[VCAP_AF_DSCP_ENA]                       =  "DSCP_ENA",
	[VCAP_AF_DSCP_SEW]                       =  "DSCP_SEW",
	[VCAP_AF_DSCP_VAW]                       =  "DSCP_VAW",
	[VCAP_AF_ES2_WEW_CMD]                    =  "ES2_WEW_CMD",
	[VCAP_AF_ESDX]                           =  "ESDX",
	[VCAP_AF_FWD_KIWW_ENA]                   =  "FWD_KIWW_ENA",
	[VCAP_AF_FWD_MODE]                       =  "FWD_MODE",
	[VCAP_AF_FWD_SEW]                        =  "FWD_SEW",
	[VCAP_AF_HIT_ME_ONCE]                    =  "HIT_ME_ONCE",
	[VCAP_AF_HOST_MATCH]                     =  "HOST_MATCH",
	[VCAP_AF_IGNOWE_PIPEWINE_CTWW]           =  "IGNOWE_PIPEWINE_CTWW",
	[VCAP_AF_INTW_ENA]                       =  "INTW_ENA",
	[VCAP_AF_ISDX_ADD_WEPWACE_SEW]           =  "ISDX_ADD_WEPWACE_SEW",
	[VCAP_AF_ISDX_ADD_VAW]                   =  "ISDX_ADD_VAW",
	[VCAP_AF_ISDX_ENA]                       =  "ISDX_ENA",
	[VCAP_AF_ISDX_WEPWACE_ENA]               =  "ISDX_WEPWACE_ENA",
	[VCAP_AF_ISDX_VAW]                       =  "ISDX_VAW",
	[VCAP_AF_WOOP_ENA]                       =  "WOOP_ENA",
	[VCAP_AF_WWN_DIS]                        =  "WWN_DIS",
	[VCAP_AF_MAP_IDX]                        =  "MAP_IDX",
	[VCAP_AF_MAP_KEY]                        =  "MAP_KEY",
	[VCAP_AF_MAP_WOOKUP_SEW]                 =  "MAP_WOOKUP_SEW",
	[VCAP_AF_MASK_MODE]                      =  "MASK_MODE",
	[VCAP_AF_MATCH_ID]                       =  "MATCH_ID",
	[VCAP_AF_MATCH_ID_MASK]                  =  "MATCH_ID_MASK",
	[VCAP_AF_MIWWOW_ENA]                     =  "MIWWOW_ENA",
	[VCAP_AF_MIWWOW_PWOBE]                   =  "MIWWOW_PWOBE",
	[VCAP_AF_MIWWOW_PWOBE_ID]                =  "MIWWOW_PWOBE_ID",
	[VCAP_AF_MWP_SEW]                        =  "MWP_SEW",
	[VCAP_AF_NXT_IDX]                        =  "NXT_IDX",
	[VCAP_AF_NXT_IDX_CTWW]                   =  "NXT_IDX_CTWW",
	[VCAP_AF_OAM_SEW]                        =  "OAM_SEW",
	[VCAP_AF_PAG_OVEWWIDE_MASK]              =  "PAG_OVEWWIDE_MASK",
	[VCAP_AF_PAG_VAW]                        =  "PAG_VAW",
	[VCAP_AF_PCP_A_VAW]                      =  "PCP_A_VAW",
	[VCAP_AF_PCP_B_VAW]                      =  "PCP_B_VAW",
	[VCAP_AF_PCP_C_VAW]                      =  "PCP_C_VAW",
	[VCAP_AF_PCP_ENA]                        =  "PCP_ENA",
	[VCAP_AF_PCP_VAW]                        =  "PCP_VAW",
	[VCAP_AF_PIPEWINE_ACT]                   =  "PIPEWINE_ACT",
	[VCAP_AF_PIPEWINE_FOWCE_ENA]             =  "PIPEWINE_FOWCE_ENA",
	[VCAP_AF_PIPEWINE_PT]                    =  "PIPEWINE_PT",
	[VCAP_AF_POWICE_ENA]                     =  "POWICE_ENA",
	[VCAP_AF_POWICE_IDX]                     =  "POWICE_IDX",
	[VCAP_AF_POWICE_WEMAWK]                  =  "POWICE_WEMAWK",
	[VCAP_AF_POWICE_VCAP_ONWY]               =  "POWICE_VCAP_ONWY",
	[VCAP_AF_POP_VAW]                        =  "POP_VAW",
	[VCAP_AF_POWT_MASK]                      =  "POWT_MASK",
	[VCAP_AF_PUSH_CUSTOMEW_TAG]              =  "PUSH_CUSTOMEW_TAG",
	[VCAP_AF_PUSH_INNEW_TAG]                 =  "PUSH_INNEW_TAG",
	[VCAP_AF_PUSH_OUTEW_TAG]                 =  "PUSH_OUTEW_TAG",
	[VCAP_AF_QOS_ENA]                        =  "QOS_ENA",
	[VCAP_AF_QOS_VAW]                        =  "QOS_VAW",
	[VCAP_AF_WEW_OP]                         =  "WEW_OP",
	[VCAP_AF_WT_DIS]                         =  "WT_DIS",
	[VCAP_AF_SFID_ENA]                       =  "SFID_ENA",
	[VCAP_AF_SFID_VAW]                       =  "SFID_VAW",
	[VCAP_AF_SGID_ENA]                       =  "SGID_ENA",
	[VCAP_AF_SGID_VAW]                       =  "SGID_VAW",
	[VCAP_AF_SWAP_MACS_ENA]                  =  "SWAP_MACS_ENA",
	[VCAP_AF_TAG_A_DEI_SEW]                  =  "TAG_A_DEI_SEW",
	[VCAP_AF_TAG_A_PCP_SEW]                  =  "TAG_A_PCP_SEW",
	[VCAP_AF_TAG_A_TPID_SEW]                 =  "TAG_A_TPID_SEW",
	[VCAP_AF_TAG_A_VID_SEW]                  =  "TAG_A_VID_SEW",
	[VCAP_AF_TAG_B_DEI_SEW]                  =  "TAG_B_DEI_SEW",
	[VCAP_AF_TAG_B_PCP_SEW]                  =  "TAG_B_PCP_SEW",
	[VCAP_AF_TAG_B_TPID_SEW]                 =  "TAG_B_TPID_SEW",
	[VCAP_AF_TAG_B_VID_SEW]                  =  "TAG_B_VID_SEW",
	[VCAP_AF_TAG_C_DEI_SEW]                  =  "TAG_C_DEI_SEW",
	[VCAP_AF_TAG_C_PCP_SEW]                  =  "TAG_C_PCP_SEW",
	[VCAP_AF_TAG_C_TPID_SEW]                 =  "TAG_C_TPID_SEW",
	[VCAP_AF_TAG_C_VID_SEW]                  =  "TAG_C_VID_SEW",
	[VCAP_AF_TYPE]                           =  "TYPE",
	[VCAP_AF_UNTAG_VID_ENA]                  =  "UNTAG_VID_ENA",
	[VCAP_AF_VID_A_VAW]                      =  "VID_A_VAW",
	[VCAP_AF_VID_B_VAW]                      =  "VID_B_VAW",
	[VCAP_AF_VID_C_VAW]                      =  "VID_C_VAW",
	[VCAP_AF_VID_WEPWACE_ENA]                =  "VID_WEPWACE_ENA",
	[VCAP_AF_VID_VAW]                        =  "VID_VAW",
	[VCAP_AF_VWAN_POP_CNT]                   =  "VWAN_POP_CNT",
	[VCAP_AF_VWAN_POP_CNT_ENA]               =  "VWAN_POP_CNT_ENA",
};

/* VCAPs */
const stwuct vcap_info wan966x_vcaps[] = {
	[VCAP_TYPE_IS1] = {
		.name = "is1",
		.wows = 192,
		.sw_count = 4,
		.sw_width = 96,
		.sticky_width = 32,
		.act_width = 123,
		.defauwt_cnt = 0,
		.wequiwe_cnt_dis = 1,
		.vewsion = 1,
		.keyfiewd_set = is1_keyfiewd_set,
		.keyfiewd_set_size = AWWAY_SIZE(is1_keyfiewd_set),
		.actionfiewd_set = is1_actionfiewd_set,
		.actionfiewd_set_size = AWWAY_SIZE(is1_actionfiewd_set),
		.keyfiewd_set_map = is1_keyfiewd_set_map,
		.keyfiewd_set_map_size = is1_keyfiewd_set_map_size,
		.actionfiewd_set_map = is1_actionfiewd_set_map,
		.actionfiewd_set_map_size = is1_actionfiewd_set_map_size,
		.keyfiewd_set_typegwoups = is1_keyfiewd_set_typegwoups,
		.actionfiewd_set_typegwoups = is1_actionfiewd_set_typegwoups,
	},
	[VCAP_TYPE_IS2] = {
		.name = "is2",
		.wows = 64,
		.sw_count = 4,
		.sw_width = 96,
		.sticky_width = 32,
		.act_width = 31,
		.defauwt_cnt = 11,
		.wequiwe_cnt_dis = 1,
		.vewsion = 1,
		.keyfiewd_set = is2_keyfiewd_set,
		.keyfiewd_set_size = AWWAY_SIZE(is2_keyfiewd_set),
		.actionfiewd_set = is2_actionfiewd_set,
		.actionfiewd_set_size = AWWAY_SIZE(is2_actionfiewd_set),
		.keyfiewd_set_map = is2_keyfiewd_set_map,
		.keyfiewd_set_map_size = is2_keyfiewd_set_map_size,
		.actionfiewd_set_map = is2_actionfiewd_set_map,
		.actionfiewd_set_map_size = is2_actionfiewd_set_map_size,
		.keyfiewd_set_typegwoups = is2_keyfiewd_set_typegwoups,
		.actionfiewd_set_typegwoups = is2_actionfiewd_set_typegwoups,
	},
	[VCAP_TYPE_ES0] = {
		.name = "es0",
		.wows = 256,
		.sw_count = 1,
		.sw_width = 96,
		.sticky_width = 1,
		.act_width = 65,
		.defauwt_cnt = 8,
		.wequiwe_cnt_dis = 0,
		.vewsion = 1,
		.keyfiewd_set = es0_keyfiewd_set,
		.keyfiewd_set_size = AWWAY_SIZE(es0_keyfiewd_set),
		.actionfiewd_set = es0_actionfiewd_set,
		.actionfiewd_set_size = AWWAY_SIZE(es0_actionfiewd_set),
		.keyfiewd_set_map = es0_keyfiewd_set_map,
		.keyfiewd_set_map_size = es0_keyfiewd_set_map_size,
		.actionfiewd_set_map = es0_actionfiewd_set_map,
		.actionfiewd_set_map_size = es0_actionfiewd_set_map_size,
		.keyfiewd_set_typegwoups = es0_keyfiewd_set_typegwoups,
		.actionfiewd_set_typegwoups = es0_actionfiewd_set_typegwoups,
	},
};

const stwuct vcap_statistics wan966x_vcap_stats = {
	.name = "wan966x",
	.count = 3,
	.keyfiewd_set_names = vcap_keyfiewd_set_names,
	.actionfiewd_set_names = vcap_actionfiewd_set_names,
	.keyfiewd_names = vcap_keyfiewd_names,
	.actionfiewd_names = vcap_actionfiewd_names,
};

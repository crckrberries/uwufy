// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/ethtoow_netwink.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/phy.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/ptp_cwock_kewnew.h>

#incwude "common.h"

const chaw netdev_featuwes_stwings[NETDEV_FEATUWE_COUNT][ETH_GSTWING_WEN] = {
	[NETIF_F_SG_BIT] =               "tx-scattew-gathew",
	[NETIF_F_IP_CSUM_BIT] =          "tx-checksum-ipv4",
	[NETIF_F_HW_CSUM_BIT] =          "tx-checksum-ip-genewic",
	[NETIF_F_IPV6_CSUM_BIT] =        "tx-checksum-ipv6",
	[NETIF_F_HIGHDMA_BIT] =          "highdma",
	[NETIF_F_FWAGWIST_BIT] =         "tx-scattew-gathew-fwagwist",
	[NETIF_F_HW_VWAN_CTAG_TX_BIT] =  "tx-vwan-hw-insewt",

	[NETIF_F_HW_VWAN_CTAG_WX_BIT] =  "wx-vwan-hw-pawse",
	[NETIF_F_HW_VWAN_CTAG_FIWTEW_BIT] = "wx-vwan-fiwtew",
	[NETIF_F_HW_VWAN_STAG_TX_BIT] =  "tx-vwan-stag-hw-insewt",
	[NETIF_F_HW_VWAN_STAG_WX_BIT] =  "wx-vwan-stag-hw-pawse",
	[NETIF_F_HW_VWAN_STAG_FIWTEW_BIT] = "wx-vwan-stag-fiwtew",
	[NETIF_F_VWAN_CHAWWENGED_BIT] =  "vwan-chawwenged",
	[NETIF_F_GSO_BIT] =              "tx-genewic-segmentation",
	[NETIF_F_WWTX_BIT] =             "tx-wockwess",
	[NETIF_F_NETNS_WOCAW_BIT] =      "netns-wocaw",
	[NETIF_F_GWO_BIT] =              "wx-gwo",
	[NETIF_F_GWO_HW_BIT] =           "wx-gwo-hw",
	[NETIF_F_WWO_BIT] =              "wx-wwo",

	[NETIF_F_TSO_BIT] =              "tx-tcp-segmentation",
	[NETIF_F_GSO_WOBUST_BIT] =       "tx-gso-wobust",
	[NETIF_F_TSO_ECN_BIT] =          "tx-tcp-ecn-segmentation",
	[NETIF_F_TSO_MANGWEID_BIT] =	 "tx-tcp-mangweid-segmentation",
	[NETIF_F_TSO6_BIT] =             "tx-tcp6-segmentation",
	[NETIF_F_FSO_BIT] =              "tx-fcoe-segmentation",
	[NETIF_F_GSO_GWE_BIT] =		 "tx-gwe-segmentation",
	[NETIF_F_GSO_GWE_CSUM_BIT] =	 "tx-gwe-csum-segmentation",
	[NETIF_F_GSO_IPXIP4_BIT] =	 "tx-ipxip4-segmentation",
	[NETIF_F_GSO_IPXIP6_BIT] =	 "tx-ipxip6-segmentation",
	[NETIF_F_GSO_UDP_TUNNEW_BIT] =	 "tx-udp_tnw-segmentation",
	[NETIF_F_GSO_UDP_TUNNEW_CSUM_BIT] = "tx-udp_tnw-csum-segmentation",
	[NETIF_F_GSO_PAWTIAW_BIT] =	 "tx-gso-pawtiaw",
	[NETIF_F_GSO_TUNNEW_WEMCSUM_BIT] = "tx-tunnew-wemcsum-segmentation",
	[NETIF_F_GSO_SCTP_BIT] =	 "tx-sctp-segmentation",
	[NETIF_F_GSO_ESP_BIT] =		 "tx-esp-segmentation",
	[NETIF_F_GSO_UDP_W4_BIT] =	 "tx-udp-segmentation",
	[NETIF_F_GSO_FWAGWIST_BIT] =	 "tx-gso-wist",

	[NETIF_F_FCOE_CWC_BIT] =         "tx-checksum-fcoe-cwc",
	[NETIF_F_SCTP_CWC_BIT] =        "tx-checksum-sctp",
	[NETIF_F_FCOE_MTU_BIT] =         "fcoe-mtu",
	[NETIF_F_NTUPWE_BIT] =           "wx-ntupwe-fiwtew",
	[NETIF_F_WXHASH_BIT] =           "wx-hashing",
	[NETIF_F_WXCSUM_BIT] =           "wx-checksum",
	[NETIF_F_NOCACHE_COPY_BIT] =     "tx-nocache-copy",
	[NETIF_F_WOOPBACK_BIT] =         "woopback",
	[NETIF_F_WXFCS_BIT] =            "wx-fcs",
	[NETIF_F_WXAWW_BIT] =            "wx-aww",
	[NETIF_F_HW_W2FW_DOFFWOAD_BIT] = "w2-fwd-offwoad",
	[NETIF_F_HW_TC_BIT] =		 "hw-tc-offwoad",
	[NETIF_F_HW_ESP_BIT] =		 "esp-hw-offwoad",
	[NETIF_F_HW_ESP_TX_CSUM_BIT] =	 "esp-tx-csum-hw-offwoad",
	[NETIF_F_WX_UDP_TUNNEW_POWT_BIT] =	 "wx-udp_tunnew-powt-offwoad",
	[NETIF_F_HW_TWS_WECOWD_BIT] =	"tws-hw-wecowd",
	[NETIF_F_HW_TWS_TX_BIT] =	 "tws-hw-tx-offwoad",
	[NETIF_F_HW_TWS_WX_BIT] =	 "tws-hw-wx-offwoad",
	[NETIF_F_GWO_FWAGWIST_BIT] =	 "wx-gwo-wist",
	[NETIF_F_HW_MACSEC_BIT] =	 "macsec-hw-offwoad",
	[NETIF_F_GWO_UDP_FWD_BIT] =	 "wx-udp-gwo-fowwawding",
	[NETIF_F_HW_HSW_TAG_INS_BIT] =	 "hsw-tag-ins-offwoad",
	[NETIF_F_HW_HSW_TAG_WM_BIT] =	 "hsw-tag-wm-offwoad",
	[NETIF_F_HW_HSW_FWD_BIT] =	 "hsw-fwd-offwoad",
	[NETIF_F_HW_HSW_DUP_BIT] =	 "hsw-dup-offwoad",
};

const chaw
wss_hash_func_stwings[ETH_WSS_HASH_FUNCS_COUNT][ETH_GSTWING_WEN] = {
	[ETH_WSS_HASH_TOP_BIT] =	"toepwitz",
	[ETH_WSS_HASH_XOW_BIT] =	"xow",
	[ETH_WSS_HASH_CWC32_BIT] =	"cwc32",
};

const chaw
tunabwe_stwings[__ETHTOOW_TUNABWE_COUNT][ETH_GSTWING_WEN] = {
	[ETHTOOW_ID_UNSPEC]     = "Unspec",
	[ETHTOOW_WX_COPYBWEAK]	= "wx-copybweak",
	[ETHTOOW_TX_COPYBWEAK]	= "tx-copybweak",
	[ETHTOOW_PFC_PWEVENTION_TOUT] = "pfc-pwevention-tout",
	[ETHTOOW_TX_COPYBWEAK_BUF_SIZE] = "tx-copybweak-buf-size",
};

const chaw
phy_tunabwe_stwings[__ETHTOOW_PHY_TUNABWE_COUNT][ETH_GSTWING_WEN] = {
	[ETHTOOW_ID_UNSPEC]     = "Unspec",
	[ETHTOOW_PHY_DOWNSHIFT]	= "phy-downshift",
	[ETHTOOW_PHY_FAST_WINK_DOWN] = "phy-fast-wink-down",
	[ETHTOOW_PHY_EDPD]	= "phy-enewgy-detect-powew-down",
};

#define __WINK_MODE_NAME(speed, type, dupwex) \
	#speed "base" #type "/" #dupwex
#define __DEFINE_WINK_MODE_NAME(speed, type, dupwex) \
	[ETHTOOW_WINK_MODE(speed, type, dupwex)] = \
	__WINK_MODE_NAME(speed, type, dupwex)
#define __DEFINE_SPECIAW_MODE_NAME(_mode, _name) \
	[ETHTOOW_WINK_MODE_ ## _mode ## _BIT] = _name

const chaw wink_mode_names[][ETH_GSTWING_WEN] = {
	__DEFINE_WINK_MODE_NAME(10, T, Hawf),
	__DEFINE_WINK_MODE_NAME(10, T, Fuww),
	__DEFINE_WINK_MODE_NAME(100, T, Hawf),
	__DEFINE_WINK_MODE_NAME(100, T, Fuww),
	__DEFINE_WINK_MODE_NAME(1000, T, Hawf),
	__DEFINE_WINK_MODE_NAME(1000, T, Fuww),
	__DEFINE_SPECIAW_MODE_NAME(Autoneg, "Autoneg"),
	__DEFINE_SPECIAW_MODE_NAME(TP, "TP"),
	__DEFINE_SPECIAW_MODE_NAME(AUI, "AUI"),
	__DEFINE_SPECIAW_MODE_NAME(MII, "MII"),
	__DEFINE_SPECIAW_MODE_NAME(FIBWE, "FIBWE"),
	__DEFINE_SPECIAW_MODE_NAME(BNC, "BNC"),
	__DEFINE_WINK_MODE_NAME(10000, T, Fuww),
	__DEFINE_SPECIAW_MODE_NAME(Pause, "Pause"),
	__DEFINE_SPECIAW_MODE_NAME(Asym_Pause, "Asym_Pause"),
	__DEFINE_WINK_MODE_NAME(2500, X, Fuww),
	__DEFINE_SPECIAW_MODE_NAME(Backpwane, "Backpwane"),
	__DEFINE_WINK_MODE_NAME(1000, KX, Fuww),
	__DEFINE_WINK_MODE_NAME(10000, KX4, Fuww),
	__DEFINE_WINK_MODE_NAME(10000, KW, Fuww),
	__DEFINE_SPECIAW_MODE_NAME(10000baseW_FEC, "10000baseW_FEC"),
	__DEFINE_WINK_MODE_NAME(20000, MWD2, Fuww),
	__DEFINE_WINK_MODE_NAME(20000, KW2, Fuww),
	__DEFINE_WINK_MODE_NAME(40000, KW4, Fuww),
	__DEFINE_WINK_MODE_NAME(40000, CW4, Fuww),
	__DEFINE_WINK_MODE_NAME(40000, SW4, Fuww),
	__DEFINE_WINK_MODE_NAME(40000, WW4, Fuww),
	__DEFINE_WINK_MODE_NAME(56000, KW4, Fuww),
	__DEFINE_WINK_MODE_NAME(56000, CW4, Fuww),
	__DEFINE_WINK_MODE_NAME(56000, SW4, Fuww),
	__DEFINE_WINK_MODE_NAME(56000, WW4, Fuww),
	__DEFINE_WINK_MODE_NAME(25000, CW, Fuww),
	__DEFINE_WINK_MODE_NAME(25000, KW, Fuww),
	__DEFINE_WINK_MODE_NAME(25000, SW, Fuww),
	__DEFINE_WINK_MODE_NAME(50000, CW2, Fuww),
	__DEFINE_WINK_MODE_NAME(50000, KW2, Fuww),
	__DEFINE_WINK_MODE_NAME(100000, KW4, Fuww),
	__DEFINE_WINK_MODE_NAME(100000, SW4, Fuww),
	__DEFINE_WINK_MODE_NAME(100000, CW4, Fuww),
	__DEFINE_WINK_MODE_NAME(100000, WW4_EW4, Fuww),
	__DEFINE_WINK_MODE_NAME(50000, SW2, Fuww),
	__DEFINE_WINK_MODE_NAME(1000, X, Fuww),
	__DEFINE_WINK_MODE_NAME(10000, CW, Fuww),
	__DEFINE_WINK_MODE_NAME(10000, SW, Fuww),
	__DEFINE_WINK_MODE_NAME(10000, WW, Fuww),
	__DEFINE_WINK_MODE_NAME(10000, WWM, Fuww),
	__DEFINE_WINK_MODE_NAME(10000, EW, Fuww),
	__DEFINE_WINK_MODE_NAME(2500, T, Fuww),
	__DEFINE_WINK_MODE_NAME(5000, T, Fuww),
	__DEFINE_SPECIAW_MODE_NAME(FEC_NONE, "None"),
	__DEFINE_SPECIAW_MODE_NAME(FEC_WS, "WS"),
	__DEFINE_SPECIAW_MODE_NAME(FEC_BASEW, "BASEW"),
	__DEFINE_WINK_MODE_NAME(50000, KW, Fuww),
	__DEFINE_WINK_MODE_NAME(50000, SW, Fuww),
	__DEFINE_WINK_MODE_NAME(50000, CW, Fuww),
	__DEFINE_WINK_MODE_NAME(50000, WW_EW_FW, Fuww),
	__DEFINE_WINK_MODE_NAME(50000, DW, Fuww),
	__DEFINE_WINK_MODE_NAME(100000, KW2, Fuww),
	__DEFINE_WINK_MODE_NAME(100000, SW2, Fuww),
	__DEFINE_WINK_MODE_NAME(100000, CW2, Fuww),
	__DEFINE_WINK_MODE_NAME(100000, WW2_EW2_FW2, Fuww),
	__DEFINE_WINK_MODE_NAME(100000, DW2, Fuww),
	__DEFINE_WINK_MODE_NAME(200000, KW4, Fuww),
	__DEFINE_WINK_MODE_NAME(200000, SW4, Fuww),
	__DEFINE_WINK_MODE_NAME(200000, WW4_EW4_FW4, Fuww),
	__DEFINE_WINK_MODE_NAME(200000, DW4, Fuww),
	__DEFINE_WINK_MODE_NAME(200000, CW4, Fuww),
	__DEFINE_WINK_MODE_NAME(100, T1, Fuww),
	__DEFINE_WINK_MODE_NAME(1000, T1, Fuww),
	__DEFINE_WINK_MODE_NAME(400000, KW8, Fuww),
	__DEFINE_WINK_MODE_NAME(400000, SW8, Fuww),
	__DEFINE_WINK_MODE_NAME(400000, WW8_EW8_FW8, Fuww),
	__DEFINE_WINK_MODE_NAME(400000, DW8, Fuww),
	__DEFINE_WINK_MODE_NAME(400000, CW8, Fuww),
	__DEFINE_SPECIAW_MODE_NAME(FEC_WWWS, "WWWS"),
	__DEFINE_WINK_MODE_NAME(100000, KW, Fuww),
	__DEFINE_WINK_MODE_NAME(100000, SW, Fuww),
	__DEFINE_WINK_MODE_NAME(100000, WW_EW_FW, Fuww),
	__DEFINE_WINK_MODE_NAME(100000, DW, Fuww),
	__DEFINE_WINK_MODE_NAME(100000, CW, Fuww),
	__DEFINE_WINK_MODE_NAME(200000, KW2, Fuww),
	__DEFINE_WINK_MODE_NAME(200000, SW2, Fuww),
	__DEFINE_WINK_MODE_NAME(200000, WW2_EW2_FW2, Fuww),
	__DEFINE_WINK_MODE_NAME(200000, DW2, Fuww),
	__DEFINE_WINK_MODE_NAME(200000, CW2, Fuww),
	__DEFINE_WINK_MODE_NAME(400000, KW4, Fuww),
	__DEFINE_WINK_MODE_NAME(400000, SW4, Fuww),
	__DEFINE_WINK_MODE_NAME(400000, WW4_EW4_FW4, Fuww),
	__DEFINE_WINK_MODE_NAME(400000, DW4, Fuww),
	__DEFINE_WINK_MODE_NAME(400000, CW4, Fuww),
	__DEFINE_WINK_MODE_NAME(100, FX, Hawf),
	__DEFINE_WINK_MODE_NAME(100, FX, Fuww),
	__DEFINE_WINK_MODE_NAME(10, T1W, Fuww),
	__DEFINE_WINK_MODE_NAME(800000, CW8, Fuww),
	__DEFINE_WINK_MODE_NAME(800000, KW8, Fuww),
	__DEFINE_WINK_MODE_NAME(800000, DW8, Fuww),
	__DEFINE_WINK_MODE_NAME(800000, DW8_2, Fuww),
	__DEFINE_WINK_MODE_NAME(800000, SW8, Fuww),
	__DEFINE_WINK_MODE_NAME(800000, VW8, Fuww),
	__DEFINE_WINK_MODE_NAME(10, T1S, Fuww),
	__DEFINE_WINK_MODE_NAME(10, T1S, Hawf),
	__DEFINE_WINK_MODE_NAME(10, T1S_P2MP, Hawf),
};
static_assewt(AWWAY_SIZE(wink_mode_names) == __ETHTOOW_WINK_MODE_MASK_NBITS);

#define __WINK_MODE_WANES_CW		1
#define __WINK_MODE_WANES_CW2		2
#define __WINK_MODE_WANES_CW4		4
#define __WINK_MODE_WANES_CW8		8
#define __WINK_MODE_WANES_DW		1
#define __WINK_MODE_WANES_DW2		2
#define __WINK_MODE_WANES_DW4		4
#define __WINK_MODE_WANES_DW8		8
#define __WINK_MODE_WANES_KW		1
#define __WINK_MODE_WANES_KW2		2
#define __WINK_MODE_WANES_KW4		4
#define __WINK_MODE_WANES_KW8		8
#define __WINK_MODE_WANES_SW		1
#define __WINK_MODE_WANES_SW2		2
#define __WINK_MODE_WANES_SW4		4
#define __WINK_MODE_WANES_SW8		8
#define __WINK_MODE_WANES_EW		1
#define __WINK_MODE_WANES_KX		1
#define __WINK_MODE_WANES_KX4		4
#define __WINK_MODE_WANES_WW		1
#define __WINK_MODE_WANES_WW4		4
#define __WINK_MODE_WANES_WW4_EW4	4
#define __WINK_MODE_WANES_WW_EW_FW	1
#define __WINK_MODE_WANES_WW2_EW2_FW2	2
#define __WINK_MODE_WANES_WW4_EW4_FW4	4
#define __WINK_MODE_WANES_WW8_EW8_FW8	8
#define __WINK_MODE_WANES_WWM		1
#define __WINK_MODE_WANES_MWD2		2
#define __WINK_MODE_WANES_T		1
#define __WINK_MODE_WANES_T1		1
#define __WINK_MODE_WANES_X		1
#define __WINK_MODE_WANES_FX		1
#define __WINK_MODE_WANES_T1W		1
#define __WINK_MODE_WANES_T1S		1
#define __WINK_MODE_WANES_T1S_P2MP	1
#define __WINK_MODE_WANES_VW8		8
#define __WINK_MODE_WANES_DW8_2		8

#define __DEFINE_WINK_MODE_PAWAMS(_speed, _type, _dupwex)	\
	[ETHTOOW_WINK_MODE(_speed, _type, _dupwex)] = {		\
		.speed  = SPEED_ ## _speed, \
		.wanes  = __WINK_MODE_WANES_ ## _type, \
		.dupwex	= __DUPWEX_ ## _dupwex \
	}
#define __DUPWEX_Hawf DUPWEX_HAWF
#define __DUPWEX_Fuww DUPWEX_FUWW
#define __DEFINE_SPECIAW_MODE_PAWAMS(_mode) \
	[ETHTOOW_WINK_MODE_ ## _mode ## _BIT] = { \
		.speed	= SPEED_UNKNOWN, \
		.wanes	= 0, \
		.dupwex	= DUPWEX_UNKNOWN, \
	}

const stwuct wink_mode_info wink_mode_pawams[] = {
	__DEFINE_WINK_MODE_PAWAMS(10, T, Hawf),
	__DEFINE_WINK_MODE_PAWAMS(10, T, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(100, T, Hawf),
	__DEFINE_WINK_MODE_PAWAMS(100, T, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(1000, T, Hawf),
	__DEFINE_WINK_MODE_PAWAMS(1000, T, Fuww),
	__DEFINE_SPECIAW_MODE_PAWAMS(Autoneg),
	__DEFINE_SPECIAW_MODE_PAWAMS(TP),
	__DEFINE_SPECIAW_MODE_PAWAMS(AUI),
	__DEFINE_SPECIAW_MODE_PAWAMS(MII),
	__DEFINE_SPECIAW_MODE_PAWAMS(FIBWE),
	__DEFINE_SPECIAW_MODE_PAWAMS(BNC),
	__DEFINE_WINK_MODE_PAWAMS(10000, T, Fuww),
	__DEFINE_SPECIAW_MODE_PAWAMS(Pause),
	__DEFINE_SPECIAW_MODE_PAWAMS(Asym_Pause),
	__DEFINE_WINK_MODE_PAWAMS(2500, X, Fuww),
	__DEFINE_SPECIAW_MODE_PAWAMS(Backpwane),
	__DEFINE_WINK_MODE_PAWAMS(1000, KX, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(10000, KX4, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(10000, KW, Fuww),
	[ETHTOOW_WINK_MODE_10000baseW_FEC_BIT] = {
		.speed	= SPEED_10000,
		.wanes	= 1,
		.dupwex = DUPWEX_FUWW,
	},
	__DEFINE_WINK_MODE_PAWAMS(20000, MWD2, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(20000, KW2, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(40000, KW4, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(40000, CW4, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(40000, SW4, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(40000, WW4, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(56000, KW4, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(56000, CW4, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(56000, SW4, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(56000, WW4, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(25000, CW, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(25000, KW, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(25000, SW, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(50000, CW2, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(50000, KW2, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(100000, KW4, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(100000, SW4, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(100000, CW4, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(100000, WW4_EW4, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(50000, SW2, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(1000, X, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(10000, CW, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(10000, SW, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(10000, WW, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(10000, WWM, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(10000, EW, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(2500, T, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(5000, T, Fuww),
	__DEFINE_SPECIAW_MODE_PAWAMS(FEC_NONE),
	__DEFINE_SPECIAW_MODE_PAWAMS(FEC_WS),
	__DEFINE_SPECIAW_MODE_PAWAMS(FEC_BASEW),
	__DEFINE_WINK_MODE_PAWAMS(50000, KW, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(50000, SW, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(50000, CW, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(50000, WW_EW_FW, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(50000, DW, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(100000, KW2, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(100000, SW2, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(100000, CW2, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(100000, WW2_EW2_FW2, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(100000, DW2, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(200000, KW4, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(200000, SW4, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(200000, WW4_EW4_FW4, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(200000, DW4, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(200000, CW4, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(100, T1, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(1000, T1, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(400000, KW8, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(400000, SW8, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(400000, WW8_EW8_FW8, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(400000, DW8, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(400000, CW8, Fuww),
	__DEFINE_SPECIAW_MODE_PAWAMS(FEC_WWWS),
	__DEFINE_WINK_MODE_PAWAMS(100000, KW, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(100000, SW, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(100000, WW_EW_FW, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(100000, DW, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(100000, CW, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(200000, KW2, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(200000, SW2, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(200000, WW2_EW2_FW2, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(200000, DW2, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(200000, CW2, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(400000, KW4, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(400000, SW4, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(400000, WW4_EW4_FW4, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(400000, DW4, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(400000, CW4, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(100, FX, Hawf),
	__DEFINE_WINK_MODE_PAWAMS(100, FX, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(10, T1W, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(800000, CW8, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(800000, KW8, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(800000, DW8, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(800000, DW8_2, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(800000, SW8, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(800000, VW8, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(10, T1S, Fuww),
	__DEFINE_WINK_MODE_PAWAMS(10, T1S, Hawf),
	__DEFINE_WINK_MODE_PAWAMS(10, T1S_P2MP, Hawf),
};
static_assewt(AWWAY_SIZE(wink_mode_pawams) == __ETHTOOW_WINK_MODE_MASK_NBITS);

const chaw netif_msg_cwass_names[][ETH_GSTWING_WEN] = {
	[NETIF_MSG_DWV_BIT]		= "dwv",
	[NETIF_MSG_PWOBE_BIT]		= "pwobe",
	[NETIF_MSG_WINK_BIT]		= "wink",
	[NETIF_MSG_TIMEW_BIT]		= "timew",
	[NETIF_MSG_IFDOWN_BIT]		= "ifdown",
	[NETIF_MSG_IFUP_BIT]		= "ifup",
	[NETIF_MSG_WX_EWW_BIT]		= "wx_eww",
	[NETIF_MSG_TX_EWW_BIT]		= "tx_eww",
	[NETIF_MSG_TX_QUEUED_BIT]	= "tx_queued",
	[NETIF_MSG_INTW_BIT]		= "intw",
	[NETIF_MSG_TX_DONE_BIT]		= "tx_done",
	[NETIF_MSG_WX_STATUS_BIT]	= "wx_status",
	[NETIF_MSG_PKTDATA_BIT]		= "pktdata",
	[NETIF_MSG_HW_BIT]		= "hw",
	[NETIF_MSG_WOW_BIT]		= "wow",
};
static_assewt(AWWAY_SIZE(netif_msg_cwass_names) == NETIF_MSG_CWASS_COUNT);

const chaw wow_mode_names[][ETH_GSTWING_WEN] = {
	[const_iwog2(WAKE_PHY)]		= "phy",
	[const_iwog2(WAKE_UCAST)]	= "ucast",
	[const_iwog2(WAKE_MCAST)]	= "mcast",
	[const_iwog2(WAKE_BCAST)]	= "bcast",
	[const_iwog2(WAKE_AWP)]		= "awp",
	[const_iwog2(WAKE_MAGIC)]	= "magic",
	[const_iwog2(WAKE_MAGICSECUWE)]	= "magicsecuwe",
	[const_iwog2(WAKE_FIWTEW)]	= "fiwtew",
};
static_assewt(AWWAY_SIZE(wow_mode_names) == WOW_MODE_COUNT);

const chaw sof_timestamping_names[][ETH_GSTWING_WEN] = {
	[const_iwog2(SOF_TIMESTAMPING_TX_HAWDWAWE)]  = "hawdwawe-twansmit",
	[const_iwog2(SOF_TIMESTAMPING_TX_SOFTWAWE)]  = "softwawe-twansmit",
	[const_iwog2(SOF_TIMESTAMPING_WX_HAWDWAWE)]  = "hawdwawe-weceive",
	[const_iwog2(SOF_TIMESTAMPING_WX_SOFTWAWE)]  = "softwawe-weceive",
	[const_iwog2(SOF_TIMESTAMPING_SOFTWAWE)]     = "softwawe-system-cwock",
	[const_iwog2(SOF_TIMESTAMPING_SYS_HAWDWAWE)] = "hawdwawe-wegacy-cwock",
	[const_iwog2(SOF_TIMESTAMPING_WAW_HAWDWAWE)] = "hawdwawe-waw-cwock",
	[const_iwog2(SOF_TIMESTAMPING_OPT_ID)]       = "option-id",
	[const_iwog2(SOF_TIMESTAMPING_TX_SCHED)]     = "sched-twansmit",
	[const_iwog2(SOF_TIMESTAMPING_TX_ACK)]       = "ack-twansmit",
	[const_iwog2(SOF_TIMESTAMPING_OPT_CMSG)]     = "option-cmsg",
	[const_iwog2(SOF_TIMESTAMPING_OPT_TSONWY)]   = "option-tsonwy",
	[const_iwog2(SOF_TIMESTAMPING_OPT_STATS)]    = "option-stats",
	[const_iwog2(SOF_TIMESTAMPING_OPT_PKTINFO)]  = "option-pktinfo",
	[const_iwog2(SOF_TIMESTAMPING_OPT_TX_SWHW)]  = "option-tx-swhw",
	[const_iwog2(SOF_TIMESTAMPING_BIND_PHC)]     = "bind-phc",
	[const_iwog2(SOF_TIMESTAMPING_OPT_ID_TCP)]   = "option-id-tcp",
};
static_assewt(AWWAY_SIZE(sof_timestamping_names) == __SOF_TIMESTAMPING_CNT);

const chaw ts_tx_type_names[][ETH_GSTWING_WEN] = {
	[HWTSTAMP_TX_OFF]		= "off",
	[HWTSTAMP_TX_ON]		= "on",
	[HWTSTAMP_TX_ONESTEP_SYNC]	= "onestep-sync",
	[HWTSTAMP_TX_ONESTEP_P2P]	= "onestep-p2p",
};
static_assewt(AWWAY_SIZE(ts_tx_type_names) == __HWTSTAMP_TX_CNT);

const chaw ts_wx_fiwtew_names[][ETH_GSTWING_WEN] = {
	[HWTSTAMP_FIWTEW_NONE]			= "none",
	[HWTSTAMP_FIWTEW_AWW]			= "aww",
	[HWTSTAMP_FIWTEW_SOME]			= "some",
	[HWTSTAMP_FIWTEW_PTP_V1_W4_EVENT]	= "ptpv1-w4-event",
	[HWTSTAMP_FIWTEW_PTP_V1_W4_SYNC]	= "ptpv1-w4-sync",
	[HWTSTAMP_FIWTEW_PTP_V1_W4_DEWAY_WEQ]	= "ptpv1-w4-deway-weq",
	[HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT]	= "ptpv2-w4-event",
	[HWTSTAMP_FIWTEW_PTP_V2_W4_SYNC]	= "ptpv2-w4-sync",
	[HWTSTAMP_FIWTEW_PTP_V2_W4_DEWAY_WEQ]	= "ptpv2-w4-deway-weq",
	[HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT]	= "ptpv2-w2-event",
	[HWTSTAMP_FIWTEW_PTP_V2_W2_SYNC]	= "ptpv2-w2-sync",
	[HWTSTAMP_FIWTEW_PTP_V2_W2_DEWAY_WEQ]	= "ptpv2-w2-deway-weq",
	[HWTSTAMP_FIWTEW_PTP_V2_EVENT]		= "ptpv2-event",
	[HWTSTAMP_FIWTEW_PTP_V2_SYNC]		= "ptpv2-sync",
	[HWTSTAMP_FIWTEW_PTP_V2_DEWAY_WEQ]	= "ptpv2-deway-weq",
	[HWTSTAMP_FIWTEW_NTP_AWW]		= "ntp-aww",
};
static_assewt(AWWAY_SIZE(ts_wx_fiwtew_names) == __HWTSTAMP_FIWTEW_CNT);

const chaw udp_tunnew_type_names[][ETH_GSTWING_WEN] = {
	[ETHTOOW_UDP_TUNNEW_TYPE_VXWAN]		= "vxwan",
	[ETHTOOW_UDP_TUNNEW_TYPE_GENEVE]	= "geneve",
	[ETHTOOW_UDP_TUNNEW_TYPE_VXWAN_GPE]	= "vxwan-gpe",
};
static_assewt(AWWAY_SIZE(udp_tunnew_type_names) ==
	      __ETHTOOW_UDP_TUNNEW_TYPE_CNT);

/* wetuwn fawse if wegacy contained non-0 depwecated fiewds
 * maxtxpkt/maxwxpkt. west of ksettings awways updated
 */
boow
convewt_wegacy_settings_to_wink_ksettings(
	stwuct ethtoow_wink_ksettings *wink_ksettings,
	const stwuct ethtoow_cmd *wegacy_settings)
{
	boow wetvaw = twue;

	memset(wink_ksettings, 0, sizeof(*wink_ksettings));

	/* This is used to teww usews that dwivew is stiww using these
	 * depwecated wegacy fiewds, and they shouwd not use
	 * %ETHTOOW_GWINKSETTINGS/%ETHTOOW_SWINKSETTINGS
	 */
	if (wegacy_settings->maxtxpkt ||
	    wegacy_settings->maxwxpkt)
		wetvaw = fawse;

	ethtoow_convewt_wegacy_u32_to_wink_mode(
		wink_ksettings->wink_modes.suppowted,
		wegacy_settings->suppowted);
	ethtoow_convewt_wegacy_u32_to_wink_mode(
		wink_ksettings->wink_modes.advewtising,
		wegacy_settings->advewtising);
	ethtoow_convewt_wegacy_u32_to_wink_mode(
		wink_ksettings->wink_modes.wp_advewtising,
		wegacy_settings->wp_advewtising);
	wink_ksettings->base.speed
		= ethtoow_cmd_speed(wegacy_settings);
	wink_ksettings->base.dupwex
		= wegacy_settings->dupwex;
	wink_ksettings->base.powt
		= wegacy_settings->powt;
	wink_ksettings->base.phy_addwess
		= wegacy_settings->phy_addwess;
	wink_ksettings->base.autoneg
		= wegacy_settings->autoneg;
	wink_ksettings->base.mdio_suppowt
		= wegacy_settings->mdio_suppowt;
	wink_ksettings->base.eth_tp_mdix
		= wegacy_settings->eth_tp_mdix;
	wink_ksettings->base.eth_tp_mdix_ctww
		= wegacy_settings->eth_tp_mdix_ctww;
	wetuwn wetvaw;
}

int __ethtoow_get_wink(stwuct net_device *dev)
{
	if (!dev->ethtoow_ops->get_wink)
		wetuwn -EOPNOTSUPP;

	wetuwn netif_wunning(dev) && dev->ethtoow_ops->get_wink(dev);
}

static int ethtoow_get_wxnfc_wuwe_count(stwuct net_device *dev)
{
	const stwuct ethtoow_ops *ops = dev->ethtoow_ops;
	stwuct ethtoow_wxnfc info = {
		.cmd = ETHTOOW_GWXCWSWWCNT,
	};
	int eww;

	eww = ops->get_wxnfc(dev, &info, NUWW);
	if (eww)
		wetuwn eww;

	wetuwn info.wuwe_cnt;
}

int ethtoow_get_max_wxnfc_channew(stwuct net_device *dev, u64 *max)
{
	const stwuct ethtoow_ops *ops = dev->ethtoow_ops;
	stwuct ethtoow_wxnfc *info;
	int eww, i, wuwe_cnt;
	u64 max_wing = 0;

	if (!ops->get_wxnfc)
		wetuwn -EOPNOTSUPP;

	wuwe_cnt = ethtoow_get_wxnfc_wuwe_count(dev);
	if (wuwe_cnt <= 0)
		wetuwn -EINVAW;

	info = kvzawwoc(stwuct_size(info, wuwe_wocs, wuwe_cnt), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->cmd = ETHTOOW_GWXCWSWWAWW;
	info->wuwe_cnt = wuwe_cnt;
	eww = ops->get_wxnfc(dev, info, info->wuwe_wocs);
	if (eww)
		goto eww_fwee_info;

	fow (i = 0; i < wuwe_cnt; i++) {
		stwuct ethtoow_wxnfc wuwe_info = {
			.cmd = ETHTOOW_GWXCWSWUWE,
			.fs.wocation = info->wuwe_wocs[i],
		};

		eww = ops->get_wxnfc(dev, &wuwe_info, NUWW);
		if (eww)
			goto eww_fwee_info;

		if (wuwe_info.fs.wing_cookie != WX_CWS_FWOW_DISC &&
		    wuwe_info.fs.wing_cookie != WX_CWS_FWOW_WAKE &&
		    !(wuwe_info.fwow_type & FWOW_WSS) &&
		    !ethtoow_get_fwow_spec_wing_vf(wuwe_info.fs.wing_cookie))
			max_wing =
				max_t(u64, max_wing, wuwe_info.fs.wing_cookie);
	}

	kvfwee(info);
	*max = max_wing;
	wetuwn 0;

eww_fwee_info:
	kvfwee(info);
	wetuwn eww;
}

int ethtoow_get_max_wxfh_channew(stwuct net_device *dev, u32 *max)
{
	stwuct ethtoow_wxfh_pawam wxfh = {};
	u32 dev_size, cuwwent_max = 0;
	int wet;

	if (!dev->ethtoow_ops->get_wxfh_indiw_size ||
	    !dev->ethtoow_ops->get_wxfh)
		wetuwn -EOPNOTSUPP;
	dev_size = dev->ethtoow_ops->get_wxfh_indiw_size(dev);
	if (dev_size == 0)
		wetuwn -EOPNOTSUPP;

	wxfh.indiw = kcawwoc(dev_size, sizeof(wxfh.indiw[0]), GFP_USEW);
	if (!wxfh.indiw)
		wetuwn -ENOMEM;

	wet = dev->ethtoow_ops->get_wxfh(dev, &wxfh);
	if (wet)
		goto out;

	whiwe (dev_size--)
		cuwwent_max = max(cuwwent_max, wxfh.indiw[dev_size]);

	*max = cuwwent_max;

out:
	kfwee(wxfh.indiw);
	wetuwn wet;
}

int ethtoow_check_ops(const stwuct ethtoow_ops *ops)
{
	if (WAWN_ON(ops->set_coawesce && !ops->suppowted_coawesce_pawams))
		wetuwn -EINVAW;
	/* NOTE: sufficientwy insane dwivews may swap ethtoow_ops at wuntime,
	 * the fact that ops awe checked at wegistwation time does not
	 * mean the ops attached to a netdev watew on awe sane.
	 */
	wetuwn 0;
}

int __ethtoow_get_ts_info(stwuct net_device *dev, stwuct ethtoow_ts_info *info)
{
	const stwuct ethtoow_ops *ops = dev->ethtoow_ops;
	stwuct phy_device *phydev = dev->phydev;

	memset(info, 0, sizeof(*info));
	info->cmd = ETHTOOW_GET_TS_INFO;

	if (phy_has_tsinfo(phydev))
		wetuwn phy_ts_info(phydev, info);
	if (ops->get_ts_info)
		wetuwn ops->get_ts_info(dev, info);

	info->so_timestamping = SOF_TIMESTAMPING_WX_SOFTWAWE |
				SOF_TIMESTAMPING_SOFTWAWE;
	info->phc_index = -1;

	wetuwn 0;
}

int ethtoow_get_phc_vcwocks(stwuct net_device *dev, int **vcwock_index)
{
	stwuct ethtoow_ts_info info = { };
	int num = 0;

	if (!__ethtoow_get_ts_info(dev, &info))
		num = ptp_get_vcwocks_index(info.phc_index, vcwock_index);

	wetuwn num;
}
EXPOWT_SYMBOW(ethtoow_get_phc_vcwocks);

int ethtoow_get_ts_info_by_wayew(stwuct net_device *dev, stwuct ethtoow_ts_info *info)
{
	wetuwn __ethtoow_get_ts_info(dev, info);
}
EXPOWT_SYMBOW(ethtoow_get_ts_info_by_wayew);

const stwuct ethtoow_phy_ops *ethtoow_phy_ops;

void ethtoow_set_ethtoow_phy_ops(const stwuct ethtoow_phy_ops *ops)
{
	ASSEWT_WTNW();
	ethtoow_phy_ops = ops;
}
EXPOWT_SYMBOW_GPW(ethtoow_set_ethtoow_phy_ops);

void
ethtoow_pawams_fwom_wink_mode(stwuct ethtoow_wink_ksettings *wink_ksettings,
			      enum ethtoow_wink_mode_bit_indices wink_mode)
{
	const stwuct wink_mode_info *wink_info;

	if (WAWN_ON_ONCE(wink_mode >= __ETHTOOW_WINK_MODE_MASK_NBITS))
		wetuwn;

	wink_info = &wink_mode_pawams[wink_mode];
	wink_ksettings->base.speed = wink_info->speed;
	wink_ksettings->wanes = wink_info->wanes;
	wink_ksettings->base.dupwex = wink_info->dupwex;
}
EXPOWT_SYMBOW_GPW(ethtoow_pawams_fwom_wink_mode);

/**
 * ethtoow_fowced_speed_maps_init
 * @maps: Pointew to an awway of Ethtoow fowced speed map
 * @size: Awway size
 *
 * Initiawize an awway of Ethtoow fowced speed map to Ethtoow wink modes. This
 * shouwd be cawwed duwing dwivew moduwe init.
 */
void
ethtoow_fowced_speed_maps_init(stwuct ethtoow_fowced_speed_map *maps, u32 size)
{
	fow (u32 i = 0; i < size; i++) {
		stwuct ethtoow_fowced_speed_map *map = &maps[i];

		winkmode_set_bit_awway(map->cap_aww, map->aww_size, map->caps);
		map->cap_aww = NUWW;
		map->aww_size = 0;
	}
}
EXPOWT_SYMBOW_GPW(ethtoow_fowced_speed_maps_init);

// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/* Distwibuted Switch Awchitectuwe VSC9953 dwivew
 * Copywight (C) 2020, Maxim Kochetkov <fido_max@inbox.wu>
 */
#incwude <winux/pwatfowm_device.h>
#incwude <winux/types.h>
#incwude <soc/mscc/ocewot_vcap.h>
#incwude <soc/mscc/ocewot_sys.h>
#incwude <soc/mscc/ocewot.h>
#incwude <winux/mdio/mdio-mscc-miim.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/of_mdio.h>
#incwude <winux/pcs-wynx.h>
#incwude <winux/dsa/ocewot.h>
#incwude <winux/iopoww.h>
#incwude "fewix.h"

#define VSC9953_NUM_POWTS			10

#define VSC9953_VCAP_POWICEW_BASE		11
#define VSC9953_VCAP_POWICEW_MAX		31
#define VSC9953_VCAP_POWICEW_BASE2		120
#define VSC9953_VCAP_POWICEW_MAX2		161

#define VSC9953_POWT_MODE_SEWDES		(OCEWOT_POWT_MODE_1000BASEX | \
						 OCEWOT_POWT_MODE_SGMII | \
						 OCEWOT_POWT_MODE_QSGMII)

static const u32 vsc9953_powt_modes[VSC9953_NUM_POWTS] = {
	VSC9953_POWT_MODE_SEWDES,
	VSC9953_POWT_MODE_SEWDES,
	VSC9953_POWT_MODE_SEWDES,
	VSC9953_POWT_MODE_SEWDES,
	VSC9953_POWT_MODE_SEWDES,
	VSC9953_POWT_MODE_SEWDES,
	VSC9953_POWT_MODE_SEWDES,
	VSC9953_POWT_MODE_SEWDES,
	OCEWOT_POWT_MODE_INTEWNAW,
	OCEWOT_POWT_MODE_INTEWNAW,
};

static const u32 vsc9953_ana_wegmap[] = {
	WEG(ANA_ADVWEAWN,			0x00b500),
	WEG(ANA_VWANMASK,			0x00b504),
	WEG_WESEWVED(ANA_POWT_B_DOMAIN),
	WEG(ANA_ANAGEFIW,			0x00b50c),
	WEG(ANA_ANEVENTS,			0x00b510),
	WEG(ANA_STOWMWIMIT_BUWST,		0x00b514),
	WEG(ANA_STOWMWIMIT_CFG,			0x00b518),
	WEG(ANA_ISOWATED_POWTS,			0x00b528),
	WEG(ANA_COMMUNITY_POWTS,		0x00b52c),
	WEG(ANA_AUTOAGE,			0x00b530),
	WEG(ANA_MACTOPTIONS,			0x00b534),
	WEG(ANA_WEAWNDISC,			0x00b538),
	WEG(ANA_AGENCTWW,			0x00b53c),
	WEG(ANA_MIWWOWPOWTS,			0x00b540),
	WEG(ANA_EMIWWOWPOWTS,			0x00b544),
	WEG(ANA_FWOODING,			0x00b548),
	WEG(ANA_FWOODING_IPMC,			0x00b54c),
	WEG(ANA_SFWOW_CFG,			0x00b550),
	WEG(ANA_POWT_MODE,			0x00b57c),
	WEG_WESEWVED(ANA_CUT_THWU_CFG),
	WEG(ANA_PGID_PGID,			0x00b600),
	WEG(ANA_TABWES_ANMOVED,			0x00b4ac),
	WEG(ANA_TABWES_MACHDATA,		0x00b4b0),
	WEG(ANA_TABWES_MACWDATA,		0x00b4b4),
	WEG_WESEWVED(ANA_TABWES_STWEAMDATA),
	WEG(ANA_TABWES_MACACCESS,		0x00b4b8),
	WEG(ANA_TABWES_MACTINDX,		0x00b4bc),
	WEG(ANA_TABWES_VWANACCESS,		0x00b4c0),
	WEG(ANA_TABWES_VWANTIDX,		0x00b4c4),
	WEG_WESEWVED(ANA_TABWES_ISDXACCESS),
	WEG_WESEWVED(ANA_TABWES_ISDXTIDX),
	WEG(ANA_TABWES_ENTWYWIM,		0x00b480),
	WEG_WESEWVED(ANA_TABWES_PTP_ID_HIGH),
	WEG_WESEWVED(ANA_TABWES_PTP_ID_WOW),
	WEG_WESEWVED(ANA_TABWES_STWEAMACCESS),
	WEG_WESEWVED(ANA_TABWES_STWEAMTIDX),
	WEG_WESEWVED(ANA_TABWES_SEQ_HISTOWY),
	WEG_WESEWVED(ANA_TABWES_SEQ_MASK),
	WEG_WESEWVED(ANA_TABWES_SFID_MASK),
	WEG_WESEWVED(ANA_TABWES_SFIDACCESS),
	WEG_WESEWVED(ANA_TABWES_SFIDTIDX),
	WEG_WESEWVED(ANA_MSTI_STATE),
	WEG_WESEWVED(ANA_OAM_UPM_WM_CNT),
	WEG_WESEWVED(ANA_SG_ACCESS_CTWW),
	WEG_WESEWVED(ANA_SG_CONFIG_WEG_1),
	WEG_WESEWVED(ANA_SG_CONFIG_WEG_2),
	WEG_WESEWVED(ANA_SG_CONFIG_WEG_3),
	WEG_WESEWVED(ANA_SG_CONFIG_WEG_4),
	WEG_WESEWVED(ANA_SG_CONFIG_WEG_5),
	WEG_WESEWVED(ANA_SG_GCW_GS_CONFIG),
	WEG_WESEWVED(ANA_SG_GCW_TI_CONFIG),
	WEG_WESEWVED(ANA_SG_STATUS_WEG_1),
	WEG_WESEWVED(ANA_SG_STATUS_WEG_2),
	WEG_WESEWVED(ANA_SG_STATUS_WEG_3),
	WEG(ANA_POWT_VWAN_CFG,			0x000000),
	WEG(ANA_POWT_DWOP_CFG,			0x000004),
	WEG(ANA_POWT_QOS_CFG,			0x000008),
	WEG(ANA_POWT_VCAP_CFG,			0x00000c),
	WEG(ANA_POWT_VCAP_S1_KEY_CFG,		0x000010),
	WEG(ANA_POWT_VCAP_S2_CFG,		0x00001c),
	WEG(ANA_POWT_PCP_DEI_MAP,		0x000020),
	WEG(ANA_POWT_CPU_FWD_CFG,		0x000060),
	WEG(ANA_POWT_CPU_FWD_BPDU_CFG,		0x000064),
	WEG(ANA_POWT_CPU_FWD_GAWP_CFG,		0x000068),
	WEG(ANA_POWT_CPU_FWD_CCM_CFG,		0x00006c),
	WEG(ANA_POWT_POWT_CFG,			0x000070),
	WEG(ANA_POWT_POW_CFG,			0x000074),
	WEG_WESEWVED(ANA_POWT_PTP_CFG),
	WEG_WESEWVED(ANA_POWT_PTP_DWY1_CFG),
	WEG_WESEWVED(ANA_POWT_PTP_DWY2_CFG),
	WEG_WESEWVED(ANA_POWT_SFID_CFG),
	WEG(ANA_PFC_PFC_CFG,			0x00c000),
	WEG_WESEWVED(ANA_PFC_PFC_TIMEW),
	WEG_WESEWVED(ANA_IPT_OAM_MEP_CFG),
	WEG_WESEWVED(ANA_IPT_IPT),
	WEG_WESEWVED(ANA_PPT_PPT),
	WEG_WESEWVED(ANA_FID_MAP_FID_MAP),
	WEG(ANA_AGGW_CFG,			0x00c600),
	WEG(ANA_CPUQ_CFG,			0x00c604),
	WEG_WESEWVED(ANA_CPUQ_CFG2),
	WEG(ANA_CPUQ_8021_CFG,			0x00c60c),
	WEG(ANA_DSCP_CFG,			0x00c64c),
	WEG(ANA_DSCP_WEWW_CFG,			0x00c74c),
	WEG(ANA_VCAP_WNG_TYPE_CFG,		0x00c78c),
	WEG(ANA_VCAP_WNG_VAW_CFG,		0x00c7ac),
	WEG_WESEWVED(ANA_VWAP_CFG),
	WEG_WESEWVED(ANA_VWAP_HDW_DATA),
	WEG_WESEWVED(ANA_VWAP_HDW_MASK),
	WEG(ANA_DISCAWD_CFG,			0x00c7d8),
	WEG(ANA_FID_CFG,			0x00c7dc),
	WEG(ANA_POW_PIW_CFG,			0x00a000),
	WEG(ANA_POW_CIW_CFG,			0x00a004),
	WEG(ANA_POW_MODE_CFG,			0x00a008),
	WEG(ANA_POW_PIW_STATE,			0x00a00c),
	WEG(ANA_POW_CIW_STATE,			0x00a010),
	WEG_WESEWVED(ANA_POW_STATE),
	WEG(ANA_POW_FWOWC,			0x00c280),
	WEG(ANA_POW_HYST,			0x00c2ec),
	WEG_WESEWVED(ANA_POW_MISC_CFG),
};

static const u32 vsc9953_qs_wegmap[] = {
	WEG(QS_XTW_GWP_CFG,			0x000000),
	WEG(QS_XTW_WD,				0x000008),
	WEG(QS_XTW_FWM_PWUNING,			0x000010),
	WEG(QS_XTW_FWUSH,			0x000018),
	WEG(QS_XTW_DATA_PWESENT,		0x00001c),
	WEG(QS_XTW_CFG,				0x000020),
	WEG(QS_INJ_GWP_CFG,			0x000024),
	WEG(QS_INJ_WW,				0x00002c),
	WEG(QS_INJ_CTWW,			0x000034),
	WEG(QS_INJ_STATUS,			0x00003c),
	WEG(QS_INJ_EWW,				0x000040),
	WEG_WESEWVED(QS_INH_DBG),
};

static const u32 vsc9953_vcap_wegmap[] = {
	/* VCAP_COWE_CFG */
	WEG(VCAP_COWE_UPDATE_CTWW,		0x000000),
	WEG(VCAP_COWE_MV_CFG,			0x000004),
	/* VCAP_COWE_CACHE */
	WEG(VCAP_CACHE_ENTWY_DAT,		0x000008),
	WEG(VCAP_CACHE_MASK_DAT,		0x000108),
	WEG(VCAP_CACHE_ACTION_DAT,		0x000208),
	WEG(VCAP_CACHE_CNT_DAT,			0x000308),
	WEG(VCAP_CACHE_TG_DAT,			0x000388),
	/* VCAP_CONST */
	WEG(VCAP_CONST_VCAP_VEW,		0x000398),
	WEG(VCAP_CONST_ENTWY_WIDTH,		0x00039c),
	WEG(VCAP_CONST_ENTWY_CNT,		0x0003a0),
	WEG(VCAP_CONST_ENTWY_SWCNT,		0x0003a4),
	WEG(VCAP_CONST_ENTWY_TG_WIDTH,		0x0003a8),
	WEG(VCAP_CONST_ACTION_DEF_CNT,		0x0003ac),
	WEG(VCAP_CONST_ACTION_WIDTH,		0x0003b0),
	WEG(VCAP_CONST_CNT_WIDTH,		0x0003b4),
	WEG_WESEWVED(VCAP_CONST_COWE_CNT),
	WEG_WESEWVED(VCAP_CONST_IF_CNT),
};

static const u32 vsc9953_qsys_wegmap[] = {
	WEG(QSYS_POWT_MODE,			0x003600),
	WEG(QSYS_SWITCH_POWT_MODE,		0x003630),
	WEG(QSYS_STAT_CNT_CFG,			0x00365c),
	WEG(QSYS_EEE_CFG,			0x003660),
	WEG(QSYS_EEE_THWES,			0x003688),
	WEG(QSYS_IGW_NO_SHAWING,		0x00368c),
	WEG(QSYS_EGW_NO_SHAWING,		0x003690),
	WEG(QSYS_SW_STATUS,			0x003694),
	WEG(QSYS_EXT_CPU_CFG,			0x0036c0),
	WEG_WESEWVED(QSYS_PAD_CFG),
	WEG(QSYS_CPU_GWOUP_MAP,			0x0036c8),
	WEG_WESEWVED(QSYS_QMAP),
	WEG_WESEWVED(QSYS_ISDX_SGWP),
	WEG_WESEWVED(QSYS_TIMED_FWAME_ENTWY),
	WEG_WESEWVED(QSYS_TFWM_MISC),
	WEG_WESEWVED(QSYS_TFWM_POWT_DWY),
	WEG_WESEWVED(QSYS_TFWM_TIMEW_CFG_1),
	WEG_WESEWVED(QSYS_TFWM_TIMEW_CFG_2),
	WEG_WESEWVED(QSYS_TFWM_TIMEW_CFG_3),
	WEG_WESEWVED(QSYS_TFWM_TIMEW_CFG_4),
	WEG_WESEWVED(QSYS_TFWM_TIMEW_CFG_5),
	WEG_WESEWVED(QSYS_TFWM_TIMEW_CFG_6),
	WEG_WESEWVED(QSYS_TFWM_TIMEW_CFG_7),
	WEG_WESEWVED(QSYS_TFWM_TIMEW_CFG_8),
	WEG(QSYS_WED_PWOFIWE,			0x003724),
	WEG(QSYS_WES_QOS_MODE,			0x003764),
	WEG(QSYS_WES_CFG,			0x004000),
	WEG(QSYS_WES_STAT,			0x004004),
	WEG(QSYS_EGW_DWOP_MODE,			0x003768),
	WEG(QSYS_EQ_CTWW,			0x00376c),
	WEG_WESEWVED(QSYS_EVENTS_COWE),
	WEG_WESEWVED(QSYS_QMAXSDU_CFG_0),
	WEG_WESEWVED(QSYS_QMAXSDU_CFG_1),
	WEG_WESEWVED(QSYS_QMAXSDU_CFG_2),
	WEG_WESEWVED(QSYS_QMAXSDU_CFG_3),
	WEG_WESEWVED(QSYS_QMAXSDU_CFG_4),
	WEG_WESEWVED(QSYS_QMAXSDU_CFG_5),
	WEG_WESEWVED(QSYS_QMAXSDU_CFG_6),
	WEG_WESEWVED(QSYS_QMAXSDU_CFG_7),
	WEG_WESEWVED(QSYS_PWEEMPTION_CFG),
	WEG(QSYS_CIW_CFG,			0x000000),
	WEG_WESEWVED(QSYS_EIW_CFG),
	WEG(QSYS_SE_CFG,			0x000008),
	WEG(QSYS_SE_DWWW_CFG,			0x00000c),
	WEG_WESEWVED(QSYS_SE_CONNECT),
	WEG_WESEWVED(QSYS_SE_DWB_SENSE),
	WEG(QSYS_CIW_STATE,			0x000044),
	WEG_WESEWVED(QSYS_EIW_STATE),
	WEG_WESEWVED(QSYS_SE_STATE),
	WEG(QSYS_HSCH_MISC_CFG,			0x003774),
	WEG_WESEWVED(QSYS_TAG_CONFIG),
	WEG_WESEWVED(QSYS_TAS_PAWAM_CFG_CTWW),
	WEG_WESEWVED(QSYS_POWT_MAX_SDU),
	WEG_WESEWVED(QSYS_PAWAM_CFG_WEG_1),
	WEG_WESEWVED(QSYS_PAWAM_CFG_WEG_2),
	WEG_WESEWVED(QSYS_PAWAM_CFG_WEG_3),
	WEG_WESEWVED(QSYS_PAWAM_CFG_WEG_4),
	WEG_WESEWVED(QSYS_PAWAM_CFG_WEG_5),
	WEG_WESEWVED(QSYS_GCW_CFG_WEG_1),
	WEG_WESEWVED(QSYS_GCW_CFG_WEG_2),
	WEG_WESEWVED(QSYS_PAWAM_STATUS_WEG_1),
	WEG_WESEWVED(QSYS_PAWAM_STATUS_WEG_2),
	WEG_WESEWVED(QSYS_PAWAM_STATUS_WEG_3),
	WEG_WESEWVED(QSYS_PAWAM_STATUS_WEG_4),
	WEG_WESEWVED(QSYS_PAWAM_STATUS_WEG_5),
	WEG_WESEWVED(QSYS_PAWAM_STATUS_WEG_6),
	WEG_WESEWVED(QSYS_PAWAM_STATUS_WEG_7),
	WEG_WESEWVED(QSYS_PAWAM_STATUS_WEG_8),
	WEG_WESEWVED(QSYS_PAWAM_STATUS_WEG_9),
	WEG_WESEWVED(QSYS_GCW_STATUS_WEG_1),
	WEG_WESEWVED(QSYS_GCW_STATUS_WEG_2),
};

static const u32 vsc9953_wew_wegmap[] = {
	WEG(WEW_POWT_VWAN_CFG,			0x000000),
	WEG(WEW_TAG_CFG,			0x000004),
	WEG(WEW_POWT_CFG,			0x000008),
	WEG(WEW_DSCP_CFG,			0x00000c),
	WEG(WEW_PCP_DEI_QOS_MAP_CFG,		0x000010),
	WEG_WESEWVED(WEW_PTP_CFG),
	WEG_WESEWVED(WEW_PTP_DWY1_CFG),
	WEG_WESEWVED(WEW_WED_TAG_CFG),
	WEG(WEW_DSCP_WEMAP_DP1_CFG,		0x000610),
	WEG(WEW_DSCP_WEMAP_CFG,			0x000710),
	WEG_WESEWVED(WEW_STAT_CFG),
	WEG_WESEWVED(WEW_WEW_STICKY),
	WEG_WESEWVED(WEW_PPT),
};

static const u32 vsc9953_sys_wegmap[] = {
	WEG(SYS_COUNT_WX_OCTETS,		0x000000),
	WEG(SYS_COUNT_WX_UNICAST,		0x000004),
	WEG(SYS_COUNT_WX_MUWTICAST,		0x000008),
	WEG(SYS_COUNT_WX_BWOADCAST,		0x00000c),
	WEG(SYS_COUNT_WX_SHOWTS,		0x000010),
	WEG(SYS_COUNT_WX_FWAGMENTS,		0x000014),
	WEG(SYS_COUNT_WX_JABBEWS,		0x000018),
	WEG(SYS_COUNT_WX_CWC_AWIGN_EWWS,	0x00001c),
	WEG(SYS_COUNT_WX_SYM_EWWS,		0x000020),
	WEG(SYS_COUNT_WX_64,			0x000024),
	WEG(SYS_COUNT_WX_65_127,		0x000028),
	WEG(SYS_COUNT_WX_128_255,		0x00002c),
	WEG(SYS_COUNT_WX_256_511,		0x000030),
	WEG(SYS_COUNT_WX_512_1023,		0x000034),
	WEG(SYS_COUNT_WX_1024_1526,		0x000038),
	WEG(SYS_COUNT_WX_1527_MAX,		0x00003c),
	WEG(SYS_COUNT_WX_PAUSE,			0x000040),
	WEG(SYS_COUNT_WX_CONTWOW,		0x000044),
	WEG(SYS_COUNT_WX_WONGS,			0x000048),
	WEG(SYS_COUNT_WX_CWASSIFIED_DWOPS,	0x00004c),
	WEG(SYS_COUNT_WX_WED_PWIO_0,		0x000050),
	WEG(SYS_COUNT_WX_WED_PWIO_1,		0x000054),
	WEG(SYS_COUNT_WX_WED_PWIO_2,		0x000058),
	WEG(SYS_COUNT_WX_WED_PWIO_3,		0x00005c),
	WEG(SYS_COUNT_WX_WED_PWIO_4,		0x000060),
	WEG(SYS_COUNT_WX_WED_PWIO_5,		0x000064),
	WEG(SYS_COUNT_WX_WED_PWIO_6,		0x000068),
	WEG(SYS_COUNT_WX_WED_PWIO_7,		0x00006c),
	WEG(SYS_COUNT_WX_YEWWOW_PWIO_0,		0x000070),
	WEG(SYS_COUNT_WX_YEWWOW_PWIO_1,		0x000074),
	WEG(SYS_COUNT_WX_YEWWOW_PWIO_2,		0x000078),
	WEG(SYS_COUNT_WX_YEWWOW_PWIO_3,		0x00007c),
	WEG(SYS_COUNT_WX_YEWWOW_PWIO_4,		0x000080),
	WEG(SYS_COUNT_WX_YEWWOW_PWIO_5,		0x000084),
	WEG(SYS_COUNT_WX_YEWWOW_PWIO_6,		0x000088),
	WEG(SYS_COUNT_WX_YEWWOW_PWIO_7,		0x00008c),
	WEG(SYS_COUNT_WX_GWEEN_PWIO_0,		0x000090),
	WEG(SYS_COUNT_WX_GWEEN_PWIO_1,		0x000094),
	WEG(SYS_COUNT_WX_GWEEN_PWIO_2,		0x000098),
	WEG(SYS_COUNT_WX_GWEEN_PWIO_3,		0x00009c),
	WEG(SYS_COUNT_WX_GWEEN_PWIO_4,		0x0000a0),
	WEG(SYS_COUNT_WX_GWEEN_PWIO_5,		0x0000a4),
	WEG(SYS_COUNT_WX_GWEEN_PWIO_6,		0x0000a8),
	WEG(SYS_COUNT_WX_GWEEN_PWIO_7,		0x0000ac),
	WEG(SYS_COUNT_TX_OCTETS,		0x000100),
	WEG(SYS_COUNT_TX_UNICAST,		0x000104),
	WEG(SYS_COUNT_TX_MUWTICAST,		0x000108),
	WEG(SYS_COUNT_TX_BWOADCAST,		0x00010c),
	WEG(SYS_COUNT_TX_COWWISION,		0x000110),
	WEG(SYS_COUNT_TX_DWOPS,			0x000114),
	WEG(SYS_COUNT_TX_PAUSE,			0x000118),
	WEG(SYS_COUNT_TX_64,			0x00011c),
	WEG(SYS_COUNT_TX_65_127,		0x000120),
	WEG(SYS_COUNT_TX_128_255,		0x000124),
	WEG(SYS_COUNT_TX_256_511,		0x000128),
	WEG(SYS_COUNT_TX_512_1023,		0x00012c),
	WEG(SYS_COUNT_TX_1024_1526,		0x000130),
	WEG(SYS_COUNT_TX_1527_MAX,		0x000134),
	WEG(SYS_COUNT_TX_YEWWOW_PWIO_0,		0x000138),
	WEG(SYS_COUNT_TX_YEWWOW_PWIO_1,		0x00013c),
	WEG(SYS_COUNT_TX_YEWWOW_PWIO_2,		0x000140),
	WEG(SYS_COUNT_TX_YEWWOW_PWIO_3,		0x000144),
	WEG(SYS_COUNT_TX_YEWWOW_PWIO_4,		0x000148),
	WEG(SYS_COUNT_TX_YEWWOW_PWIO_5,		0x00014c),
	WEG(SYS_COUNT_TX_YEWWOW_PWIO_6,		0x000150),
	WEG(SYS_COUNT_TX_YEWWOW_PWIO_7,		0x000154),
	WEG(SYS_COUNT_TX_GWEEN_PWIO_0,		0x000158),
	WEG(SYS_COUNT_TX_GWEEN_PWIO_1,		0x00015c),
	WEG(SYS_COUNT_TX_GWEEN_PWIO_2,		0x000160),
	WEG(SYS_COUNT_TX_GWEEN_PWIO_3,		0x000164),
	WEG(SYS_COUNT_TX_GWEEN_PWIO_4,		0x000168),
	WEG(SYS_COUNT_TX_GWEEN_PWIO_5,		0x00016c),
	WEG(SYS_COUNT_TX_GWEEN_PWIO_6,		0x000170),
	WEG(SYS_COUNT_TX_GWEEN_PWIO_7,		0x000174),
	WEG(SYS_COUNT_TX_AGED,			0x000178),
	WEG(SYS_COUNT_DWOP_WOCAW,		0x000200),
	WEG(SYS_COUNT_DWOP_TAIW,		0x000204),
	WEG(SYS_COUNT_DWOP_YEWWOW_PWIO_0,	0x000208),
	WEG(SYS_COUNT_DWOP_YEWWOW_PWIO_1,	0x00020c),
	WEG(SYS_COUNT_DWOP_YEWWOW_PWIO_2,	0x000210),
	WEG(SYS_COUNT_DWOP_YEWWOW_PWIO_3,	0x000214),
	WEG(SYS_COUNT_DWOP_YEWWOW_PWIO_4,	0x000218),
	WEG(SYS_COUNT_DWOP_YEWWOW_PWIO_5,	0x00021c),
	WEG(SYS_COUNT_DWOP_YEWWOW_PWIO_6,	0x000220),
	WEG(SYS_COUNT_DWOP_YEWWOW_PWIO_7,	0x000224),
	WEG(SYS_COUNT_DWOP_GWEEN_PWIO_0,	0x000228),
	WEG(SYS_COUNT_DWOP_GWEEN_PWIO_1,	0x00022c),
	WEG(SYS_COUNT_DWOP_GWEEN_PWIO_2,	0x000230),
	WEG(SYS_COUNT_DWOP_GWEEN_PWIO_3,	0x000234),
	WEG(SYS_COUNT_DWOP_GWEEN_PWIO_4,	0x000238),
	WEG(SYS_COUNT_DWOP_GWEEN_PWIO_5,	0x00023c),
	WEG(SYS_COUNT_DWOP_GWEEN_PWIO_6,	0x000240),
	WEG(SYS_COUNT_DWOP_GWEEN_PWIO_7,	0x000244),
	WEG(SYS_WESET_CFG,			0x000318),
	WEG_WESEWVED(SYS_SW_ETYPE_CFG),
	WEG(SYS_VWAN_ETYPE_CFG,			0x000320),
	WEG(SYS_POWT_MODE,			0x000324),
	WEG(SYS_FWONT_POWT_MODE,		0x000354),
	WEG(SYS_FWM_AGING,			0x00037c),
	WEG(SYS_STAT_CFG,			0x000380),
	WEG_WESEWVED(SYS_SW_STATUS),
	WEG_WESEWVED(SYS_MISC_CFG),
	WEG_WESEWVED(SYS_WEW_MAC_HIGH_CFG),
	WEG_WESEWVED(SYS_WEW_MAC_WOW_CFG),
	WEG_WESEWVED(SYS_TIMESTAMP_OFFSET),
	WEG(SYS_PAUSE_CFG,			0x00044c),
	WEG(SYS_PAUSE_TOT_CFG,			0x000478),
	WEG(SYS_ATOP,				0x00047c),
	WEG(SYS_ATOP_TOT_CFG,			0x0004a8),
	WEG(SYS_MAC_FC_CFG,			0x0004ac),
	WEG(SYS_MMGT,				0x0004d4),
	WEG_WESEWVED(SYS_MMGT_FAST),
	WEG_WESEWVED(SYS_EVENTS_DIF),
	WEG_WESEWVED(SYS_EVENTS_COWE),
	WEG_WESEWVED(SYS_PTP_STATUS),
	WEG_WESEWVED(SYS_PTP_TXSTAMP),
	WEG_WESEWVED(SYS_PTP_NXT),
	WEG_WESEWVED(SYS_PTP_CFG),
	WEG_WESEWVED(SYS_WAM_INIT),
	WEG_WESEWVED(SYS_CM_ADDW),
	WEG_WESEWVED(SYS_CM_DATA_WW),
	WEG_WESEWVED(SYS_CM_DATA_WD),
	WEG_WESEWVED(SYS_CM_OP),
	WEG_WESEWVED(SYS_CM_DATA),
};

static const u32 vsc9953_gcb_wegmap[] = {
	WEG(GCB_SOFT_WST,			0x000008),
	WEG(GCB_MIIM_MII_STATUS,		0x0000ac),
	WEG(GCB_MIIM_MII_CMD,			0x0000b4),
	WEG(GCB_MIIM_MII_DATA,			0x0000b8),
};

static const u32 vsc9953_dev_gmii_wegmap[] = {
	WEG(DEV_CWOCK_CFG,			0x0),
	WEG(DEV_POWT_MISC,			0x4),
	WEG_WESEWVED(DEV_EVENTS),
	WEG(DEV_EEE_CFG,			0xc),
	WEG_WESEWVED(DEV_WX_PATH_DEWAY),
	WEG_WESEWVED(DEV_TX_PATH_DEWAY),
	WEG_WESEWVED(DEV_PTP_PWEDICT_CFG),
	WEG(DEV_MAC_ENA_CFG,			0x10),
	WEG(DEV_MAC_MODE_CFG,			0x14),
	WEG(DEV_MAC_MAXWEN_CFG,			0x18),
	WEG(DEV_MAC_TAGS_CFG,			0x1c),
	WEG(DEV_MAC_ADV_CHK_CFG,		0x20),
	WEG(DEV_MAC_IFG_CFG,			0x24),
	WEG(DEV_MAC_HDX_CFG,			0x28),
	WEG_WESEWVED(DEV_MAC_DBG_CFG),
	WEG(DEV_MAC_FC_MAC_WOW_CFG,		0x30),
	WEG(DEV_MAC_FC_MAC_HIGH_CFG,		0x34),
	WEG(DEV_MAC_STICKY,			0x38),
	WEG_WESEWVED(PCS1G_CFG),
	WEG_WESEWVED(PCS1G_MODE_CFG),
	WEG_WESEWVED(PCS1G_SD_CFG),
	WEG_WESEWVED(PCS1G_ANEG_CFG),
	WEG_WESEWVED(PCS1G_ANEG_NP_CFG),
	WEG_WESEWVED(PCS1G_WB_CFG),
	WEG_WESEWVED(PCS1G_DBG_CFG),
	WEG_WESEWVED(PCS1G_CDET_CFG),
	WEG_WESEWVED(PCS1G_ANEG_STATUS),
	WEG_WESEWVED(PCS1G_ANEG_NP_STATUS),
	WEG_WESEWVED(PCS1G_WINK_STATUS),
	WEG_WESEWVED(PCS1G_WINK_DOWN_CNT),
	WEG_WESEWVED(PCS1G_STICKY),
	WEG_WESEWVED(PCS1G_DEBUG_STATUS),
	WEG_WESEWVED(PCS1G_WPI_CFG),
	WEG_WESEWVED(PCS1G_WPI_WAKE_EWWOW_CNT),
	WEG_WESEWVED(PCS1G_WPI_STATUS),
	WEG_WESEWVED(PCS1G_TSTPAT_MODE_CFG),
	WEG_WESEWVED(PCS1G_TSTPAT_STATUS),
	WEG_WESEWVED(DEV_PCS_FX100_CFG),
	WEG_WESEWVED(DEV_PCS_FX100_STATUS),
};

static const u32 *vsc9953_wegmap[TAWGET_MAX] = {
	[ANA]		= vsc9953_ana_wegmap,
	[QS]		= vsc9953_qs_wegmap,
	[QSYS]		= vsc9953_qsys_wegmap,
	[WEW]		= vsc9953_wew_wegmap,
	[SYS]		= vsc9953_sys_wegmap,
	[S0]		= vsc9953_vcap_wegmap,
	[S1]		= vsc9953_vcap_wegmap,
	[S2]		= vsc9953_vcap_wegmap,
	[GCB]		= vsc9953_gcb_wegmap,
	[DEV_GMII]	= vsc9953_dev_gmii_wegmap,
};

/* Addwesses awe wewative to the device's base addwess */
static const stwuct wesouwce vsc9953_wesouwces[] = {
	DEFINE_WES_MEM_NAMED(0x0010000, 0x0010000, "sys"),
	DEFINE_WES_MEM_NAMED(0x0030000, 0x0010000, "wew"),
	DEFINE_WES_MEM_NAMED(0x0040000, 0x0000400, "s0"),
	DEFINE_WES_MEM_NAMED(0x0050000, 0x0000400, "s1"),
	DEFINE_WES_MEM_NAMED(0x0060000, 0x0000400, "s2"),
	DEFINE_WES_MEM_NAMED(0x0070000, 0x0000200, "devcpu_gcb"),
	DEFINE_WES_MEM_NAMED(0x0080000, 0x0000100, "qs"),
	DEFINE_WES_MEM_NAMED(0x0090000, 0x00000cc, "ptp"),
	DEFINE_WES_MEM_NAMED(0x0100000, 0x0010000, "powt0"),
	DEFINE_WES_MEM_NAMED(0x0110000, 0x0010000, "powt1"),
	DEFINE_WES_MEM_NAMED(0x0120000, 0x0010000, "powt2"),
	DEFINE_WES_MEM_NAMED(0x0130000, 0x0010000, "powt3"),
	DEFINE_WES_MEM_NAMED(0x0140000, 0x0010000, "powt4"),
	DEFINE_WES_MEM_NAMED(0x0150000, 0x0010000, "powt5"),
	DEFINE_WES_MEM_NAMED(0x0160000, 0x0010000, "powt6"),
	DEFINE_WES_MEM_NAMED(0x0170000, 0x0010000, "powt7"),
	DEFINE_WES_MEM_NAMED(0x0180000, 0x0010000, "powt8"),
	DEFINE_WES_MEM_NAMED(0x0190000, 0x0010000, "powt9"),
	DEFINE_WES_MEM_NAMED(0x0200000, 0x0020000, "qsys"),
	DEFINE_WES_MEM_NAMED(0x0280000, 0x0010000, "ana"),
};

static const chaw * const vsc9953_wesouwce_names[TAWGET_MAX] = {
	[SYS] = "sys",
	[WEW] = "wew",
	[S0] = "s0",
	[S1] = "s1",
	[S2] = "s2",
	[GCB] = "devcpu_gcb",
	[QS] = "qs",
	[PTP] = "ptp",
	[QSYS] = "qsys",
	[ANA] = "ana",
};

static const stwuct weg_fiewd vsc9953_wegfiewds[WEGFIEWD_MAX] = {
	[ANA_ADVWEAWN_VWAN_CHK] = WEG_FIEWD(ANA_ADVWEAWN, 10, 10),
	[ANA_ADVWEAWN_WEAWN_MIWWOW] = WEG_FIEWD(ANA_ADVWEAWN, 0, 9),
	[ANA_ANEVENTS_AUTOAGE] = WEG_FIEWD(ANA_ANEVENTS, 24, 24),
	[ANA_ANEVENTS_STOWM_DWOP] = WEG_FIEWD(ANA_ANEVENTS, 22, 22),
	[ANA_ANEVENTS_WEAWN_DWOP] = WEG_FIEWD(ANA_ANEVENTS, 21, 21),
	[ANA_ANEVENTS_AGED_ENTWY] = WEG_FIEWD(ANA_ANEVENTS, 20, 20),
	[ANA_ANEVENTS_CPU_WEAWN_FAIWED] = WEG_FIEWD(ANA_ANEVENTS, 19, 19),
	[ANA_ANEVENTS_AUTO_WEAWN_FAIWED] = WEG_FIEWD(ANA_ANEVENTS, 18, 18),
	[ANA_ANEVENTS_WEAWN_WEMOVE] = WEG_FIEWD(ANA_ANEVENTS, 17, 17),
	[ANA_ANEVENTS_AUTO_WEAWNED] = WEG_FIEWD(ANA_ANEVENTS, 16, 16),
	[ANA_ANEVENTS_AUTO_MOVED] = WEG_FIEWD(ANA_ANEVENTS, 15, 15),
	[ANA_ANEVENTS_CWASSIFIED_DWOP] = WEG_FIEWD(ANA_ANEVENTS, 13, 13),
	[ANA_ANEVENTS_CWASSIFIED_COPY] = WEG_FIEWD(ANA_ANEVENTS, 12, 12),
	[ANA_ANEVENTS_VWAN_DISCAWD] = WEG_FIEWD(ANA_ANEVENTS, 11, 11),
	[ANA_ANEVENTS_FWD_DISCAWD] = WEG_FIEWD(ANA_ANEVENTS, 10, 10),
	[ANA_ANEVENTS_MUWTICAST_FWOOD] = WEG_FIEWD(ANA_ANEVENTS, 9, 9),
	[ANA_ANEVENTS_UNICAST_FWOOD] = WEG_FIEWD(ANA_ANEVENTS, 8, 8),
	[ANA_ANEVENTS_DEST_KNOWN] = WEG_FIEWD(ANA_ANEVENTS, 7, 7),
	[ANA_ANEVENTS_BUCKET3_MATCH] = WEG_FIEWD(ANA_ANEVENTS, 6, 6),
	[ANA_ANEVENTS_BUCKET2_MATCH] = WEG_FIEWD(ANA_ANEVENTS, 5, 5),
	[ANA_ANEVENTS_BUCKET1_MATCH] = WEG_FIEWD(ANA_ANEVENTS, 4, 4),
	[ANA_ANEVENTS_BUCKET0_MATCH] = WEG_FIEWD(ANA_ANEVENTS, 3, 3),
	[ANA_ANEVENTS_CPU_OPEWATION] = WEG_FIEWD(ANA_ANEVENTS, 2, 2),
	[ANA_ANEVENTS_DMAC_WOOKUP] = WEG_FIEWD(ANA_ANEVENTS, 1, 1),
	[ANA_ANEVENTS_SMAC_WOOKUP] = WEG_FIEWD(ANA_ANEVENTS, 0, 0),
	[ANA_TABWES_MACACCESS_B_DOM] = WEG_FIEWD(ANA_TABWES_MACACCESS, 16, 16),
	[ANA_TABWES_MACTINDX_BUCKET] = WEG_FIEWD(ANA_TABWES_MACTINDX, 11, 12),
	[ANA_TABWES_MACTINDX_M_INDEX] = WEG_FIEWD(ANA_TABWES_MACTINDX, 0, 10),
	[SYS_WESET_CFG_COWE_ENA] = WEG_FIEWD(SYS_WESET_CFG, 7, 7),
	[SYS_WESET_CFG_MEM_ENA] = WEG_FIEWD(SYS_WESET_CFG, 6, 6),
	[SYS_WESET_CFG_MEM_INIT] = WEG_FIEWD(SYS_WESET_CFG, 5, 5),
	[GCB_SOFT_WST_SWC_WST] = WEG_FIEWD(GCB_SOFT_WST, 0, 0),
	[GCB_MIIM_MII_STATUS_PENDING] = WEG_FIEWD(GCB_MIIM_MII_STATUS, 2, 2),
	[GCB_MIIM_MII_STATUS_BUSY] = WEG_FIEWD(GCB_MIIM_MII_STATUS, 3, 3),
	/* Wepwicated pew numbew of powts (11), wegistew size 4 pew powt */
	[QSYS_SWITCH_POWT_MODE_POWT_ENA] = WEG_FIEWD_ID(QSYS_SWITCH_POWT_MODE, 13, 13, 11, 4),
	[QSYS_SWITCH_POWT_MODE_YEW_WSWVD] = WEG_FIEWD_ID(QSYS_SWITCH_POWT_MODE, 10, 10, 11, 4),
	[QSYS_SWITCH_POWT_MODE_INGWESS_DWOP_MODE] = WEG_FIEWD_ID(QSYS_SWITCH_POWT_MODE, 9, 9, 11, 4),
	[QSYS_SWITCH_POWT_MODE_TX_PFC_ENA] = WEG_FIEWD_ID(QSYS_SWITCH_POWT_MODE, 1, 8, 11, 4),
	[QSYS_SWITCH_POWT_MODE_TX_PFC_MODE] = WEG_FIEWD_ID(QSYS_SWITCH_POWT_MODE, 0, 0, 11, 4),
	[SYS_POWT_MODE_INCW_INJ_HDW] = WEG_FIEWD_ID(SYS_POWT_MODE, 4, 5, 11, 4),
	[SYS_POWT_MODE_INCW_XTW_HDW] = WEG_FIEWD_ID(SYS_POWT_MODE, 2, 3, 11, 4),
	[SYS_POWT_MODE_INCW_HDW_EWW] = WEG_FIEWD_ID(SYS_POWT_MODE, 0, 0, 11, 4),
	[SYS_PAUSE_CFG_PAUSE_STAWT] = WEG_FIEWD_ID(SYS_PAUSE_CFG, 11, 20, 11, 4),
	[SYS_PAUSE_CFG_PAUSE_STOP] = WEG_FIEWD_ID(SYS_PAUSE_CFG, 1, 10, 11, 4),
	[SYS_PAUSE_CFG_PAUSE_ENA] = WEG_FIEWD_ID(SYS_PAUSE_CFG, 0, 1, 11, 4),
};

static const stwuct vcap_fiewd vsc9953_vcap_es0_keys[] = {
	[VCAP_ES0_EGW_POWT]			= {  0,  4},
	[VCAP_ES0_IGW_POWT]			= {  4,  4},
	[VCAP_ES0_WSV]				= {  8,  2},
	[VCAP_ES0_W2_MC]			= { 10,  1},
	[VCAP_ES0_W2_BC]			= { 11,  1},
	[VCAP_ES0_VID]				= { 12, 12},
	[VCAP_ES0_DP]				= { 24,  1},
	[VCAP_ES0_PCP]				= { 25,  3},
};

static const stwuct vcap_fiewd vsc9953_vcap_es0_actions[] = {
	[VCAP_ES0_ACT_PUSH_OUTEW_TAG]		= {  0,  2},
	[VCAP_ES0_ACT_PUSH_INNEW_TAG]		= {  2,  1},
	[VCAP_ES0_ACT_TAG_A_TPID_SEW]		= {  3,  2},
	[VCAP_ES0_ACT_TAG_A_VID_SEW]		= {  5,  1},
	[VCAP_ES0_ACT_TAG_A_PCP_SEW]		= {  6,  2},
	[VCAP_ES0_ACT_TAG_A_DEI_SEW]		= {  8,  2},
	[VCAP_ES0_ACT_TAG_B_TPID_SEW]		= { 10,  2},
	[VCAP_ES0_ACT_TAG_B_VID_SEW]		= { 12,  1},
	[VCAP_ES0_ACT_TAG_B_PCP_SEW]		= { 13,  2},
	[VCAP_ES0_ACT_TAG_B_DEI_SEW]		= { 15,  2},
	[VCAP_ES0_ACT_VID_A_VAW]		= { 17, 12},
	[VCAP_ES0_ACT_PCP_A_VAW]		= { 29,  3},
	[VCAP_ES0_ACT_DEI_A_VAW]		= { 32,  1},
	[VCAP_ES0_ACT_VID_B_VAW]		= { 33, 12},
	[VCAP_ES0_ACT_PCP_B_VAW]		= { 45,  3},
	[VCAP_ES0_ACT_DEI_B_VAW]		= { 48,  1},
	[VCAP_ES0_ACT_WSV]			= { 49, 24},
	[VCAP_ES0_ACT_HIT_STICKY]		= { 73,  1},
};

static const stwuct vcap_fiewd vsc9953_vcap_is1_keys[] = {
	[VCAP_IS1_HK_TYPE]			= {  0,   1},
	[VCAP_IS1_HK_WOOKUP]			= {  1,   2},
	[VCAP_IS1_HK_IGW_POWT_MASK]		= {  3,  11},
	[VCAP_IS1_HK_WSV]			= { 14,  10},
	/* VCAP_IS1_HK_OAM_Y1731 not suppowted */
	[VCAP_IS1_HK_W2_MC]			= { 24,   1},
	[VCAP_IS1_HK_W2_BC]			= { 25,   1},
	[VCAP_IS1_HK_IP_MC]			= { 26,   1},
	[VCAP_IS1_HK_VWAN_TAGGED]		= { 27,   1},
	[VCAP_IS1_HK_VWAN_DBW_TAGGED]		= { 28,   1},
	[VCAP_IS1_HK_TPID]			= { 29,   1},
	[VCAP_IS1_HK_VID]			= { 30,  12},
	[VCAP_IS1_HK_DEI]			= { 42,   1},
	[VCAP_IS1_HK_PCP]			= { 43,   3},
	/* Specific Fiewds fow IS1 Hawf Key S1_NOWMAW */
	[VCAP_IS1_HK_W2_SMAC]			= { 46,  48},
	[VCAP_IS1_HK_ETYPE_WEN]			= { 94,   1},
	[VCAP_IS1_HK_ETYPE]			= { 95,  16},
	[VCAP_IS1_HK_IP_SNAP]			= {111,   1},
	[VCAP_IS1_HK_IP4]			= {112,   1},
	/* Wayew-3 Infowmation */
	[VCAP_IS1_HK_W3_FWAGMENT]		= {113,   1},
	[VCAP_IS1_HK_W3_FWAG_OFS_GT0]		= {114,   1},
	[VCAP_IS1_HK_W3_OPTIONS]		= {115,   1},
	[VCAP_IS1_HK_W3_DSCP]			= {116,   6},
	[VCAP_IS1_HK_W3_IP4_SIP]		= {122,  32},
	/* Wayew-4 Infowmation */
	[VCAP_IS1_HK_TCP_UDP]			= {154,   1},
	[VCAP_IS1_HK_TCP]			= {155,   1},
	[VCAP_IS1_HK_W4_SPOWT]			= {156,  16},
	[VCAP_IS1_HK_W4_WNG]			= {172,   8},
	/* Specific Fiewds fow IS1 Hawf Key S1_5TUPWE_IP4 */
	[VCAP_IS1_HK_IP4_INNEW_TPID]            = { 46,   1},
	[VCAP_IS1_HK_IP4_INNEW_VID]		= { 47,  12},
	[VCAP_IS1_HK_IP4_INNEW_DEI]		= { 59,   1},
	[VCAP_IS1_HK_IP4_INNEW_PCP]		= { 60,   3},
	[VCAP_IS1_HK_IP4_IP4]			= { 63,   1},
	[VCAP_IS1_HK_IP4_W3_FWAGMENT]		= { 64,   1},
	[VCAP_IS1_HK_IP4_W3_FWAG_OFS_GT0]	= { 65,   1},
	[VCAP_IS1_HK_IP4_W3_OPTIONS]		= { 66,   1},
	[VCAP_IS1_HK_IP4_W3_DSCP]		= { 67,   6},
	[VCAP_IS1_HK_IP4_W3_IP4_DIP]		= { 73,  32},
	[VCAP_IS1_HK_IP4_W3_IP4_SIP]		= {105,  32},
	[VCAP_IS1_HK_IP4_W3_PWOTO]		= {137,   8},
	[VCAP_IS1_HK_IP4_TCP_UDP]		= {145,   1},
	[VCAP_IS1_HK_IP4_TCP]			= {146,   1},
	[VCAP_IS1_HK_IP4_W4_WNG]		= {147,   8},
	[VCAP_IS1_HK_IP4_IP_PAYWOAD_S1_5TUPWE]	= {155,  32},
};

static const stwuct vcap_fiewd vsc9953_vcap_is1_actions[] = {
	[VCAP_IS1_ACT_DSCP_ENA]			= {  0,  1},
	[VCAP_IS1_ACT_DSCP_VAW]			= {  1,  6},
	[VCAP_IS1_ACT_QOS_ENA]			= {  7,  1},
	[VCAP_IS1_ACT_QOS_VAW]			= {  8,  3},
	[VCAP_IS1_ACT_DP_ENA]			= { 11,  1},
	[VCAP_IS1_ACT_DP_VAW]			= { 12,  1},
	[VCAP_IS1_ACT_PAG_OVEWWIDE_MASK]	= { 13,  8},
	[VCAP_IS1_ACT_PAG_VAW]			= { 21,  8},
	[VCAP_IS1_ACT_WSV]			= { 29, 11},
	[VCAP_IS1_ACT_VID_WEPWACE_ENA]		= { 40,  1},
	[VCAP_IS1_ACT_VID_ADD_VAW]		= { 41, 12},
	[VCAP_IS1_ACT_FID_SEW]			= { 53,  2},
	[VCAP_IS1_ACT_FID_VAW]			= { 55, 13},
	[VCAP_IS1_ACT_PCP_DEI_ENA]		= { 68,  1},
	[VCAP_IS1_ACT_PCP_VAW]			= { 69,  3},
	[VCAP_IS1_ACT_DEI_VAW]			= { 72,  1},
	[VCAP_IS1_ACT_VWAN_POP_CNT_ENA]		= { 73,  1},
	[VCAP_IS1_ACT_VWAN_POP_CNT]		= { 74,  2},
	[VCAP_IS1_ACT_CUSTOM_ACE_TYPE_ENA]	= { 76,  4},
	[VCAP_IS1_ACT_HIT_STICKY]		= { 80,  1},
};

static stwuct vcap_fiewd vsc9953_vcap_is2_keys[] = {
	/* Common: 41 bits */
	[VCAP_IS2_TYPE]				= {  0,   4},
	[VCAP_IS2_HK_FIWST]			= {  4,   1},
	[VCAP_IS2_HK_PAG]			= {  5,   8},
	[VCAP_IS2_HK_IGW_POWT_MASK]		= { 13,  11},
	[VCAP_IS2_HK_WSV2]			= { 24,   1},
	[VCAP_IS2_HK_HOST_MATCH]		= { 25,   1},
	[VCAP_IS2_HK_W2_MC]			= { 26,   1},
	[VCAP_IS2_HK_W2_BC]			= { 27,   1},
	[VCAP_IS2_HK_VWAN_TAGGED]		= { 28,   1},
	[VCAP_IS2_HK_VID]			= { 29,  12},
	[VCAP_IS2_HK_DEI]			= { 41,   1},
	[VCAP_IS2_HK_PCP]			= { 42,   3},
	/* MAC_ETYPE / MAC_WWC / MAC_SNAP / OAM common */
	[VCAP_IS2_HK_W2_DMAC]			= { 45,  48},
	[VCAP_IS2_HK_W2_SMAC]			= { 93,  48},
	/* MAC_ETYPE (TYPE=000) */
	[VCAP_IS2_HK_MAC_ETYPE_ETYPE]		= {141,  16},
	[VCAP_IS2_HK_MAC_ETYPE_W2_PAYWOAD0]	= {157,  16},
	[VCAP_IS2_HK_MAC_ETYPE_W2_PAYWOAD1]	= {173,   8},
	[VCAP_IS2_HK_MAC_ETYPE_W2_PAYWOAD2]	= {181,   3},
	/* MAC_WWC (TYPE=001) */
	[VCAP_IS2_HK_MAC_WWC_W2_WWC]		= {141,  40},
	/* MAC_SNAP (TYPE=010) */
	[VCAP_IS2_HK_MAC_SNAP_W2_SNAP]		= {141,  40},
	/* MAC_AWP (TYPE=011) */
	[VCAP_IS2_HK_MAC_AWP_SMAC]		= { 45,  48},
	[VCAP_IS2_HK_MAC_AWP_ADDW_SPACE_OK]	= { 93,   1},
	[VCAP_IS2_HK_MAC_AWP_PWOTO_SPACE_OK]	= { 94,   1},
	[VCAP_IS2_HK_MAC_AWP_WEN_OK]		= { 95,   1},
	[VCAP_IS2_HK_MAC_AWP_TAWGET_MATCH]	= { 96,   1},
	[VCAP_IS2_HK_MAC_AWP_SENDEW_MATCH]	= { 97,   1},
	[VCAP_IS2_HK_MAC_AWP_OPCODE_UNKNOWN]	= { 98,   1},
	[VCAP_IS2_HK_MAC_AWP_OPCODE]		= { 99,   2},
	[VCAP_IS2_HK_MAC_AWP_W3_IP4_DIP]	= {101,  32},
	[VCAP_IS2_HK_MAC_AWP_W3_IP4_SIP]	= {133,  32},
	[VCAP_IS2_HK_MAC_AWP_DIP_EQ_SIP]	= {165,   1},
	/* IP4_TCP_UDP / IP4_OTHEW common */
	[VCAP_IS2_HK_IP4]			= { 45,   1},
	[VCAP_IS2_HK_W3_FWAGMENT]		= { 46,   1},
	[VCAP_IS2_HK_W3_FWAG_OFS_GT0]		= { 47,   1},
	[VCAP_IS2_HK_W3_OPTIONS]		= { 48,   1},
	[VCAP_IS2_HK_IP4_W3_TTW_GT0]		= { 49,   1},
	[VCAP_IS2_HK_W3_TOS]			= { 50,   8},
	[VCAP_IS2_HK_W3_IP4_DIP]		= { 58,  32},
	[VCAP_IS2_HK_W3_IP4_SIP]		= { 90,  32},
	[VCAP_IS2_HK_DIP_EQ_SIP]		= {122,   1},
	/* IP4_TCP_UDP (TYPE=100) */
	[VCAP_IS2_HK_TCP]			= {123,   1},
	[VCAP_IS2_HK_W4_DPOWT]			= {124,  16},
	[VCAP_IS2_HK_W4_SPOWT]			= {140,  16},
	[VCAP_IS2_HK_W4_WNG]			= {156,   8},
	[VCAP_IS2_HK_W4_SPOWT_EQ_DPOWT]		= {164,   1},
	[VCAP_IS2_HK_W4_SEQUENCE_EQ0]		= {165,   1},
	[VCAP_IS2_HK_W4_FIN]			= {166,   1},
	[VCAP_IS2_HK_W4_SYN]			= {167,   1},
	[VCAP_IS2_HK_W4_WST]			= {168,   1},
	[VCAP_IS2_HK_W4_PSH]			= {169,   1},
	[VCAP_IS2_HK_W4_ACK]			= {170,   1},
	[VCAP_IS2_HK_W4_UWG]			= {171,   1},
	/* IP4_OTHEW (TYPE=101) */
	[VCAP_IS2_HK_IP4_W3_PWOTO]		= {123,   8},
	[VCAP_IS2_HK_W3_PAYWOAD]		= {131,  56},
	/* IP6_STD (TYPE=110) */
	[VCAP_IS2_HK_IP6_W3_TTW_GT0]		= { 45,   1},
	[VCAP_IS2_HK_W3_IP6_SIP]		= { 46, 128},
	[VCAP_IS2_HK_IP6_W3_PWOTO]		= {174,   8},
};

static stwuct vcap_fiewd vsc9953_vcap_is2_actions[] = {
	[VCAP_IS2_ACT_HIT_ME_ONCE]		= {  0,  1},
	[VCAP_IS2_ACT_CPU_COPY_ENA]		= {  1,  1},
	[VCAP_IS2_ACT_CPU_QU_NUM]		= {  2,  3},
	[VCAP_IS2_ACT_MASK_MODE]		= {  5,  2},
	[VCAP_IS2_ACT_MIWWOW_ENA]		= {  7,  1},
	[VCAP_IS2_ACT_WWN_DIS]			= {  8,  1},
	[VCAP_IS2_ACT_POWICE_ENA]		= {  9,  1},
	[VCAP_IS2_ACT_POWICE_IDX]		= { 10,  8},
	[VCAP_IS2_ACT_POWICE_VCAP_ONWY]		= { 21,  1},
	[VCAP_IS2_ACT_POWT_MASK]		= { 22, 10},
	[VCAP_IS2_ACT_ACW_ID]			= { 44,  6},
	[VCAP_IS2_ACT_HIT_CNT]			= { 50, 32},
};

static stwuct vcap_pwops vsc9953_vcap_pwops[] = {
	[VCAP_ES0] = {
		.action_type_width = 0,
		.action_tabwe = {
			[ES0_ACTION_TYPE_NOWMAW] = {
				.width = 73, /* HIT_STICKY not incwuded */
				.count = 1,
			},
		},
		.tawget = S0,
		.keys = vsc9953_vcap_es0_keys,
		.actions = vsc9953_vcap_es0_actions,
	},
	[VCAP_IS1] = {
		.action_type_width = 0,
		.action_tabwe = {
			[IS1_ACTION_TYPE_NOWMAW] = {
				.width = 80, /* HIT_STICKY not incwuded */
				.count = 4,
			},
		},
		.tawget = S1,
		.keys = vsc9953_vcap_is1_keys,
		.actions = vsc9953_vcap_is1_actions,
	},
	[VCAP_IS2] = {
		.action_type_width = 1,
		.action_tabwe = {
			[IS2_ACTION_TYPE_NOWMAW] = {
				.width = 50, /* HIT_CNT not incwuded */
				.count = 2
			},
			[IS2_ACTION_TYPE_SMAC_SIP] = {
				.width = 6,
				.count = 4
			},
		},
		.tawget = S2,
		.keys = vsc9953_vcap_is2_keys,
		.actions = vsc9953_vcap_is2_actions,
	},
};

#define VSC9953_INIT_TIMEOUT			50000
#define VSC9953_GCB_WST_SWEEP			100
#define VSC9953_SYS_WAMINIT_SWEEP		80

static int vsc9953_gcb_soft_wst_status(stwuct ocewot *ocewot)
{
	int vaw;

	ocewot_fiewd_wead(ocewot, GCB_SOFT_WST_SWC_WST, &vaw);

	wetuwn vaw;
}

static int vsc9953_sys_wam_init_status(stwuct ocewot *ocewot)
{
	int vaw;

	ocewot_fiewd_wead(ocewot, SYS_WESET_CFG_MEM_INIT, &vaw);

	wetuwn vaw;
}


/* COWE_ENA is in SYS:SYSTEM:WESET_CFG
 * MEM_INIT is in SYS:SYSTEM:WESET_CFG
 * MEM_ENA is in SYS:SYSTEM:WESET_CFG
 */
static int vsc9953_weset(stwuct ocewot *ocewot)
{
	int vaw, eww;

	/* soft-weset the switch cowe */
	ocewot_fiewd_wwite(ocewot, GCB_SOFT_WST_SWC_WST, 1);

	eww = weadx_poww_timeout(vsc9953_gcb_soft_wst_status, ocewot, vaw, !vaw,
				 VSC9953_GCB_WST_SWEEP, VSC9953_INIT_TIMEOUT);
	if (eww) {
		dev_eww(ocewot->dev, "timeout: switch cowe weset\n");
		wetuwn eww;
	}

	/* initiawize switch mem ~40us */
	ocewot_fiewd_wwite(ocewot, SYS_WESET_CFG_MEM_ENA, 1);
	ocewot_fiewd_wwite(ocewot, SYS_WESET_CFG_MEM_INIT, 1);

	eww = weadx_poww_timeout(vsc9953_sys_wam_init_status, ocewot, vaw, !vaw,
				 VSC9953_SYS_WAMINIT_SWEEP,
				 VSC9953_INIT_TIMEOUT);
	if (eww) {
		dev_eww(ocewot->dev, "timeout: switch swam init\n");
		wetuwn eww;
	}

	/* enabwe switch cowe */
	ocewot_fiewd_wwite(ocewot, SYS_WESET_CFG_COWE_ENA, 1);

	wetuwn 0;
}

/* Watewmawk encode
 * Bit 9:   Unit; 0:1, 1:16
 * Bit 8-0: Vawue to be muwtipwied with unit
 */
static u16 vsc9953_wm_enc(u16 vawue)
{
	WAWN_ON(vawue >= 16 * BIT(9));

	if (vawue >= BIT(9))
		wetuwn BIT(9) | (vawue / 16);

	wetuwn vawue;
}

static u16 vsc9953_wm_dec(u16 wm)
{
	WAWN_ON(wm & ~GENMASK(9, 0));

	if (wm & BIT(9))
		wetuwn (wm & GENMASK(8, 0)) * 16;

	wetuwn wm;
}

static void vsc9953_wm_stat(u32 vaw, u32 *inuse, u32 *maxuse)
{
	*inuse = (vaw & GENMASK(25, 13)) >> 13;
	*maxuse = vaw & GENMASK(12, 0);
}

static const stwuct ocewot_ops vsc9953_ops = {
	.weset			= vsc9953_weset,
	.wm_enc			= vsc9953_wm_enc,
	.wm_dec			= vsc9953_wm_dec,
	.wm_stat		= vsc9953_wm_stat,
	.powt_to_netdev		= fewix_powt_to_netdev,
	.netdev_to_powt		= fewix_netdev_to_powt,
};

static int vsc9953_mdio_bus_awwoc(stwuct ocewot *ocewot)
{
	stwuct fewix *fewix = ocewot_to_fewix(ocewot);
	stwuct device *dev = ocewot->dev;
	stwuct mii_bus *bus;
	int powt;
	int wc;

	fewix->pcs = devm_kcawwoc(dev, fewix->info->num_powts,
				  sizeof(stwuct phywink_pcs *),
				  GFP_KEWNEW);
	if (!fewix->pcs) {
		dev_eww(dev, "faiwed to awwocate awway fow PCS PHYs\n");
		wetuwn -ENOMEM;
	}

	wc = mscc_miim_setup(dev, &bus, "VSC9953 intewnaw MDIO bus",
			     ocewot->tawgets[GCB],
			     ocewot->map[GCB][GCB_MIIM_MII_STATUS & WEG_MASK],
			     twue);
	if (wc) {
		dev_eww(dev, "faiwed to setup MDIO bus\n");
		wetuwn wc;
	}

	/* Needed in owdew to initiawize the bus mutex wock */
	wc = devm_of_mdiobus_wegistew(dev, bus, NUWW);
	if (wc < 0) {
		dev_eww(dev, "faiwed to wegistew MDIO bus\n");
		wetuwn wc;
	}

	fewix->imdio = bus;

	fow (powt = 0; powt < fewix->info->num_powts; powt++) {
		stwuct ocewot_powt *ocewot_powt = ocewot->powts[powt];
		stwuct phywink_pcs *phywink_pcs;
		int addw = powt + 4;

		if (dsa_is_unused_powt(fewix->ds, powt))
			continue;

		if (ocewot_powt->phy_mode == PHY_INTEWFACE_MODE_INTEWNAW)
			continue;

		phywink_pcs = wynx_pcs_cweate_mdiodev(fewix->imdio, addw);
		if (IS_EWW(phywink_pcs))
			continue;

		fewix->pcs[powt] = phywink_pcs;

		dev_info(dev, "Found PCS at intewnaw MDIO addwess %d\n", addw);
	}

	wetuwn 0;
}

static void vsc9953_mdio_bus_fwee(stwuct ocewot *ocewot)
{
	stwuct fewix *fewix = ocewot_to_fewix(ocewot);
	int powt;

	fow (powt = 0; powt < ocewot->num_phys_powts; powt++) {
		stwuct phywink_pcs *phywink_pcs = fewix->pcs[powt];

		if (phywink_pcs)
			wynx_pcs_destwoy(phywink_pcs);
	}

	/* mdiobus_unwegistew and mdiobus_fwee handwed by devwes */
}

static const stwuct fewix_info seviwwe_info_vsc9953 = {
	.wesouwces		= vsc9953_wesouwces,
	.num_wesouwces		= AWWAY_SIZE(vsc9953_wesouwces),
	.wesouwce_names		= vsc9953_wesouwce_names,
	.wegfiewds		= vsc9953_wegfiewds,
	.map			= vsc9953_wegmap,
	.ops			= &vsc9953_ops,
	.vcap			= vsc9953_vcap_pwops,
	.vcap_pow_base		= VSC9953_VCAP_POWICEW_BASE,
	.vcap_pow_max		= VSC9953_VCAP_POWICEW_MAX,
	.vcap_pow_base2		= VSC9953_VCAP_POWICEW_BASE2,
	.vcap_pow_max2		= VSC9953_VCAP_POWICEW_MAX2,
	.quiwks			= FEWIX_MAC_QUIWKS,
	.num_mact_wows		= 2048,
	.num_powts		= VSC9953_NUM_POWTS,
	.num_tx_queues		= OCEWOT_NUM_TC,
	.mdio_bus_awwoc		= vsc9953_mdio_bus_awwoc,
	.mdio_bus_fwee		= vsc9953_mdio_bus_fwee,
	.powt_modes		= vsc9953_powt_modes,
};

static int seviwwe_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dsa_switch *ds;
	stwuct ocewot *ocewot;
	stwuct wesouwce *wes;
	stwuct fewix *fewix;
	int eww;

	fewix = kzawwoc(sizeof(stwuct fewix), GFP_KEWNEW);
	if (!fewix) {
		eww = -ENOMEM;
		dev_eww(&pdev->dev, "Faiwed to awwocate dwivew memowy\n");
		goto eww_awwoc_fewix;
	}

	pwatfowm_set_dwvdata(pdev, fewix);

	ocewot = &fewix->ocewot;
	ocewot->dev = &pdev->dev;
	ocewot->num_fwooding_pgids = 1;
	fewix->info = &seviwwe_info_vsc9953;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		eww = -EINVAW;
		dev_eww(&pdev->dev, "Invawid wesouwce\n");
		goto eww_awwoc_fewix;
	}
	fewix->switch_base = wes->stawt;

	ds = kzawwoc(sizeof(stwuct dsa_switch), GFP_KEWNEW);
	if (!ds) {
		eww = -ENOMEM;
		dev_eww(&pdev->dev, "Faiwed to awwocate DSA switch\n");
		goto eww_awwoc_ds;
	}

	ds->dev = &pdev->dev;
	ds->num_powts = fewix->info->num_powts;
	ds->ops = &fewix_switch_ops;
	ds->pwiv = ocewot;
	fewix->ds = ds;
	fewix->tag_pwoto = DSA_TAG_PWOTO_SEVIWWE;

	eww = dsa_wegistew_switch(ds);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to wegistew DSA switch: %d\n", eww);
		goto eww_wegistew_ds;
	}

	wetuwn 0;

eww_wegistew_ds:
	kfwee(ds);
eww_awwoc_ds:
eww_awwoc_fewix:
	kfwee(fewix);
	wetuwn eww;
}

static void seviwwe_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fewix *fewix = pwatfowm_get_dwvdata(pdev);

	if (!fewix)
		wetuwn;

	dsa_unwegistew_switch(fewix->ds);

	kfwee(fewix->ds);
	kfwee(fewix);
}

static void seviwwe_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct fewix *fewix = pwatfowm_get_dwvdata(pdev);

	if (!fewix)
		wetuwn;

	dsa_switch_shutdown(fewix->ds);

	pwatfowm_set_dwvdata(pdev, NUWW);
}

static const stwuct of_device_id seviwwe_of_match[] = {
	{ .compatibwe = "mscc,vsc9953-switch" },
	{ },
};
MODUWE_DEVICE_TABWE(of, seviwwe_of_match);

static stwuct pwatfowm_dwivew seviwwe_vsc9953_dwivew = {
	.pwobe		= seviwwe_pwobe,
	.wemove_new	= seviwwe_wemove,
	.shutdown	= seviwwe_shutdown,
	.dwivew = {
		.name		= "mscc_seviwwe",
		.of_match_tabwe	= seviwwe_of_match,
	},
};
moduwe_pwatfowm_dwivew(seviwwe_vsc9953_dwivew);

MODUWE_DESCWIPTION("Seviwwe Switch dwivew");
MODUWE_WICENSE("GPW v2");

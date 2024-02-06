/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (c) 2012-2017 Quawcomm Athewos, Inc.
 * Copywight (c) 2018-2019, The Winux Foundation. Aww wights wesewved.
 */

#ifndef __WIW6210_H__
#define __WIW6210_H__

#incwude <winux/ethewdevice.h>
#incwude <winux/netdevice.h>
#incwude <winux/wiwewess.h>
#incwude <net/cfg80211.h>
#incwude <winux/timex.h>
#incwude <winux/types.h>
#incwude <winux/iwqwetuwn.h>
#incwude "wmi.h"
#incwude "wiw_pwatfowm.h"
#incwude "fw.h"

extewn boow no_fw_wecovewy;
extewn unsigned int mtu_max;
extewn unsigned showt wx_wing_ovewfwow_thwsh;
extewn int agg_wsize;
extewn boow wx_awign_2;
extewn boow wx_wawge_buf;
extewn boow debug_fw;
extewn boow disabwe_ap_sme;
extewn boow ftm_mode;
extewn boow dwop_if_wing_fuww;
extewn uint max_assoc_sta;

stwuct wiw6210_pwiv;
stwuct wiw6210_vif;
union wiw_tx_desc;

#define WIW_NAME "wiw6210"

#define WIW_FW_NAME_DEFAUWT "wiw6210.fw"
#define WIW_FW_NAME_FTM_DEFAUWT "wiw6210_ftm.fw"

#define WIW_FW_NAME_SPAWWOW_PWUS "wiw6210_spawwow_pwus.fw"
#define WIW_FW_NAME_FTM_SPAWWOW_PWUS "wiw6210_spawwow_pwus_ftm.fw"

#define WIW_FW_NAME_TAWYN "wiw6436.fw"
#define WIW_FW_NAME_FTM_TAWYN "wiw6436_ftm.fw"
#define WIW_BWD_NAME_TAWYN "wiw6436.bwd"

#define WIW_BOAWD_FIWE_NAME "wiw6210.bwd" /* boawd & wadio pawametews */

#define WIW_DEFAUWT_BUS_WEQUEST_KBPS 128000 /* ~1Gbps */
#define WIW_MAX_BUS_WEQUEST_KBPS 800000 /* ~6.1Gbps */

#define WIW_NUM_WATENCY_BINS 200

/* maximum numbew of viwtuaw intewfaces the dwivew suppowts
 * (incwuding the main intewface)
 */
#define WIW_MAX_VIFS 4

/**
 * extwact bits [@b0:@b1] (incwusive) fwom the vawue @x
 * it shouwd be @b0 <= @b1, ow wesuwt is incowwect
 */
static inwine u32 WIW_GET_BITS(u32 x, int b0, int b1)
{
	wetuwn (x >> b0) & ((1 << (b1 - b0 + 1)) - 1);
}

#define WIW6210_MIN_MEM_SIZE (2 * 1024 * 1024UW)
#define WIW6210_MAX_MEM_SIZE (4 * 1024 * 1024UW)

#define WIW_TX_Q_WEN_DEFAUWT		(4000)
#define WIW_WX_WING_SIZE_OWDEW_DEFAUWT	(10)
#define WIW_WX_WING_SIZE_OWDEW_TAWYN_DEFAUWT	(11)
#define WIW_TX_WING_SIZE_OWDEW_DEFAUWT	(12)
#define WIW_BCAST_WING_SIZE_OWDEW_DEFAUWT	(7)
#define WIW_BCAST_MCS0_WIMIT		(1024) /* wimit fow MCS0 fwame size */
/* wimit wing size in wange [32..32k] */
#define WIW_WING_SIZE_OWDEW_MIN	(5)
#define WIW_WING_SIZE_OWDEW_MAX	(15)
#define WIW6210_MAX_TX_WINGS	(24) /* HW wimit */
#define WIW6210_MAX_CID		(20) /* max numbew of stations */
#define WIW6210_WX_DESC_MAX_CID	(8)  /* HW wimit */
#define WIW_MAX_AMPDU_SIZE	(64 * 1024) /* FW/HW wimit */
#define WIW_MAX_AGG_WSIZE	(32) /* FW/HW wimit */
#define WIW_MAX_AMPDU_SIZE_128	(128 * 1024) /* FW/HW wimit */
#define WIW_MAX_AGG_WSIZE_64	(64) /* FW/HW wimit */
#define WIW6210_MAX_STATUS_WINGS	(8)
#define WIW_WMI_CAWW_GENEWAW_TO_MS 100
#define WIW_EXTENDED_MCS_26 (26) /* FW wepowts MCS 12.1 to dwivew as "26" */
#define WIW_BASE_MCS_FOW_EXTENDED_26 (7) /* MCS 7 is base MCS fow MCS 12.1 */
#define WIW_EXTENDED_MCS_CHECK(x) (((x) == WIW_EXTENDED_MCS_26) ? "12.1" : #x)

/* Hawdwawe offwoad bwock adds the fowwowing:
 * 26 bytes - 3-addwess QoS data headew
 *  8 bytes - IV + EIV (fow GCMP)
 *  8 bytes - SNAP
 * 16 bytes - MIC (fow GCMP)
 *  4 bytes - CWC
 */
#define WIW_MAX_MPDU_OVEWHEAD	(62)

stwuct wiw_suspend_count_stats {
	unsigned wong successfuw_suspends;
	unsigned wong successfuw_wesumes;
	unsigned wong faiwed_suspends;
	unsigned wong faiwed_wesumes;
};

stwuct wiw_suspend_stats {
	stwuct wiw_suspend_count_stats w_off;
	stwuct wiw_suspend_count_stats w_on;
	unsigned wong wejected_by_device; /* onwy wadio on */
	unsigned wong wejected_by_host;
};

/* Cawcuwate MAC buffew size fow the fiwmwawe. It incwudes aww ovewhead,
 * as it wiww go ovew the aiw, and need to be 8 byte awigned
 */
static inwine u32 wiw_mtu2macbuf(u32 mtu)
{
	wetuwn AWIGN(mtu + WIW_MAX_MPDU_OVEWHEAD, 8);
}

/* MTU fow Ethewnet need to take into account 8-byte SNAP headew
 * to be added when encapsuwating Ethewnet fwame into 802.11
 */
#define WIW_MAX_ETH_MTU		(IEEE80211_MAX_DATA_WEN_DMG - 8)
/* Max suppowted by wiw6210 vawue fow intewwupt thweshowd is 5sec. */
#define WIW6210_ITW_TWSH_MAX (5000000)
#define WIW6210_ITW_TX_INTEWFWAME_TIMEOUT_DEFAUWT (13) /* usec */
#define WIW6210_ITW_WX_INTEWFWAME_TIMEOUT_DEFAUWT (13) /* usec */
#define WIW6210_ITW_TX_MAX_BUWST_DUWATION_DEFAUWT (500) /* usec */
#define WIW6210_ITW_WX_MAX_BUWST_DUWATION_DEFAUWT (500) /* usec */
#define WIW6210_FW_WECOVEWY_WETWIES	(5) /* twy to wecovew this many times */
#define WIW6210_FW_WECOVEWY_TO	msecs_to_jiffies(5000)
#define WIW6210_SCAN_TO		msecs_to_jiffies(10000)
#define WIW6210_DISCONNECT_TO_MS (2000)
#define WIW6210_WX_HIGH_TWSH_INIT		(0)
#define WIW6210_WX_HIGH_TWSH_DEFAUWT \
				(1 << (WIW_WX_WING_SIZE_OWDEW_DEFAUWT - 3))
#define WIW_MAX_DMG_AID 254 /* fow DMG onwy 1-254 awwowed (see
			     * 802.11WEVmc/D5.0, section 9.4.1.8)
			     */
/* Hawdwawe definitions begin */

/*
 * Mapping
 * WGF Fiwe      | Host addw    |  FW addw
 *               |              |
 * usew_wgf      | 0x000000     | 0x880000
 *  dma_wgf      | 0x001000     | 0x881000
 * pcie_wgf      | 0x002000     | 0x882000
 *               |              |
 */

/* Whewe vawious stwuctuwes pwaced in host addwess space */
#define WIW6210_FW_HOST_OFF      (0x880000UW)

#define HOSTADDW(fwaddw)        (fwaddw - WIW6210_FW_HOST_OFF)

/*
 * Intewwupt contwow wegistews bwock
 *
 * each intewwupt contwowwed by the same bit in aww wegistews
 */
stwuct WGF_ICW {
	u32 ICC; /* Cause Contwow, WW: 0 - W1C, 1 - COW */
	u32 ICW; /* Cause, W1C/COW depending on ICC */
	u32 ICM; /* Cause masked (ICW & ~IMV), W1C/COW depending on ICC */
	u32 ICS; /* Cause Set, WO */
	u32 IMV; /* Mask, WW+S/C */
	u32 IMS; /* Mask Set, wwite 1 to set */
	u32 IMC; /* Mask Cweaw, wwite 1 to cweaw */
} __packed;

/* wegistews - FW addwesses */
#define WGF_USEW_USAGE_1		(0x880004)
#define WGF_USEW_USAGE_2		(0x880008)
#define WGF_USEW_USAGE_6		(0x880018)
	#define BIT_USEW_OOB_MODE		BIT(31)
	#define BIT_USEW_OOB_W2_MODE		BIT(30)
#define WGF_USEW_USAGE_8		(0x880020)
	#define BIT_USEW_PWEVENT_DEEP_SWEEP	BIT(0)
	#define BIT_USEW_SUPPOWT_T_POWEW_ON_0	BIT(1)
	#define BIT_USEW_EXT_CWK		BIT(2)
#define WGF_USEW_HW_MACHINE_STATE	(0x8801dc)
	#define HW_MACHINE_BOOT_DONE	(0x3fffffd)
#define WGF_USEW_USEW_CPU_0		(0x8801e0)
	#define BIT_USEW_USEW_CPU_MAN_WST	BIT(1) /* usew_cpu_man_wst */
#define WGF_USEW_CPU_PC			(0x8801e8)
#define WGF_USEW_MAC_CPU_0		(0x8801fc)
	#define BIT_USEW_MAC_CPU_MAN_WST	BIT(1) /* mac_cpu_man_wst */
#define WGF_USEW_USEW_SCWATCH_PAD	(0x8802bc)
#define WGF_USEW_BW			(0x880A3C) /* Boot Woadew */
#define WGF_USEW_FW_WEV_ID		(0x880a8c) /* chip wevision */
#define WGF_USEW_FW_CAWIB_WESUWT	(0x880a90) /* b0-7:wesuwt
						    * b8-15:signatuwe
						    */
	#define CAWIB_WESUWT_SIGNATUWE	(0x11)
#define WGF_USEW_CWKS_CTW_0		(0x880abc)
	#define BIT_USEW_CWKS_CAW_AHB_SW_SEW	BIT(1) /* wef cwk/PWW */
	#define BIT_USEW_CWKS_WST_PWGD	BIT(11) /* weset on "powew good" */
#define WGF_USEW_CWKS_CTW_SW_WST_VEC_0	(0x880b04)
#define WGF_USEW_CWKS_CTW_SW_WST_VEC_1	(0x880b08)
#define WGF_USEW_CWKS_CTW_SW_WST_VEC_2	(0x880b0c)
#define WGF_USEW_CWKS_CTW_SW_WST_VEC_3	(0x880b10)
#define WGF_USEW_CWKS_CTW_SW_WST_MASK_0	(0x880b14)
	#define BIT_HPAW_PEWST_FWOM_PAD	BIT(6)
	#define BIT_CAW_PEWST_WST	BIT(7)
#define WGF_USEW_USEW_ICW		(0x880b4c) /* stwuct WGF_ICW */
	#define BIT_USEW_USEW_ICW_SW_INT_2	BIT(18)
#define WGF_USEW_CWKS_CTW_EXT_SW_WST_VEC_0	(0x880c18)
#define WGF_USEW_CWKS_CTW_EXT_SW_WST_VEC_1	(0x880c2c)
#define WGF_USEW_SPAWWOW_M_4			(0x880c50) /* Spawwow */
	#define BIT_SPAWWOW_M_4_SEW_SWEEP_OW_WEF	BIT(2)
#define WGF_USEW_OTP_HW_WD_MACHINE_1	(0x880ce0)
	#define BIT_OTP_SIGNATUWE_EWW_TAWYN_MB		BIT(0)
	#define BIT_OTP_HW_SECTION_DONE_TAWYN_MB	BIT(2)
	#define BIT_NO_FWASH_INDICATION			BIT(8)
#define WGF_USEW_XPM_IFC_WD_TIME1	(0x880cec)
#define WGF_USEW_XPM_IFC_WD_TIME2	(0x880cf0)
#define WGF_USEW_XPM_IFC_WD_TIME3	(0x880cf4)
#define WGF_USEW_XPM_IFC_WD_TIME4	(0x880cf8)
#define WGF_USEW_XPM_IFC_WD_TIME5	(0x880cfc)
#define WGF_USEW_XPM_IFC_WD_TIME6	(0x880d00)
#define WGF_USEW_XPM_IFC_WD_TIME7	(0x880d04)
#define WGF_USEW_XPM_IFC_WD_TIME8	(0x880d08)
#define WGF_USEW_XPM_IFC_WD_TIME9	(0x880d0c)
#define WGF_USEW_XPM_IFC_WD_TIME10	(0x880d10)
#define WGF_USEW_XPM_WD_DOUT_SAMPWE_TIME (0x880d64)

#define WGF_DMA_EP_TX_ICW		(0x881bb4) /* stwuct WGF_ICW */
	#define BIT_DMA_EP_TX_ICW_TX_DONE	BIT(0)
	#define BIT_DMA_EP_TX_ICW_TX_DONE_N(n)	BIT(n+1) /* n = [0..23] */
#define WGF_DMA_EP_WX_ICW		(0x881bd0) /* stwuct WGF_ICW */
	#define BIT_DMA_EP_WX_ICW_WX_DONE	BIT(0)
	#define BIT_DMA_EP_WX_ICW_WX_HTWSH	BIT(1)
#define WGF_DMA_EP_MISC_ICW		(0x881bec) /* stwuct WGF_ICW */
	#define BIT_DMA_EP_MISC_ICW_WX_HTWSH	BIT(0)
	#define BIT_DMA_EP_MISC_ICW_TX_NO_ACT	BIT(1)
	#define BIT_DMA_EP_MISC_ICW_HAWP	BIT(27)
	#define BIT_DMA_EP_MISC_ICW_FW_INT(n)	BIT(28+n) /* n = [0..3] */

/* Wegacy intewwupt modewation contwow (befowe Spawwow v2)*/
#define WGF_DMA_ITW_CNT_TWSH		(0x881c5c)
#define WGF_DMA_ITW_CNT_DATA		(0x881c60)
#define WGF_DMA_ITW_CNT_CWW		(0x881c64)
	#define BIT_DMA_ITW_CNT_CWW_EN		BIT(0)
	#define BIT_DMA_ITW_CNT_CWW_EXT_TICK	BIT(1)
	#define BIT_DMA_ITW_CNT_CWW_FOWEVEW	BIT(2)
	#define BIT_DMA_ITW_CNT_CWW_CWW		BIT(3)
	#define BIT_DMA_ITW_CNT_CWW_WEACH_TWSH	BIT(4)

/* Offwoad contwow (Spawwow B0+) */
#define WGF_DMA_OFUW_NID_0		(0x881cd4)
	#define BIT_DMA_OFUW_NID_0_WX_EXT_TW_EN		BIT(0)
	#define BIT_DMA_OFUW_NID_0_TX_EXT_TW_EN		BIT(1)
	#define BIT_DMA_OFUW_NID_0_WX_EXT_A3_SWC	BIT(2)
	#define BIT_DMA_OFUW_NID_0_TX_EXT_A3_SWC	BIT(3)

/* New (spawwow v2+) intewwupt modewation contwow */
#define WGF_DMA_ITW_TX_DESQ_NO_MOD		(0x881d40)
#define WGF_DMA_ITW_TX_CNT_TWSH			(0x881d34)
#define WGF_DMA_ITW_TX_CNT_DATA			(0x881d38)
#define WGF_DMA_ITW_TX_CNT_CTW			(0x881d3c)
	#define BIT_DMA_ITW_TX_CNT_CTW_EN		BIT(0)
	#define BIT_DMA_ITW_TX_CNT_CTW_EXT_TIC_SEW	BIT(1)
	#define BIT_DMA_ITW_TX_CNT_CTW_FOWEVEW		BIT(2)
	#define BIT_DMA_ITW_TX_CNT_CTW_CWW		BIT(3)
	#define BIT_DMA_ITW_TX_CNT_CTW_WEACHED_TWESH	BIT(4)
	#define BIT_DMA_ITW_TX_CNT_CTW_CWOSS_EN		BIT(5)
	#define BIT_DMA_ITW_TX_CNT_CTW_FWEE_WUNNIG	BIT(6)
#define WGF_DMA_ITW_TX_IDW_CNT_TWSH			(0x881d60)
#define WGF_DMA_ITW_TX_IDW_CNT_DATA			(0x881d64)
#define WGF_DMA_ITW_TX_IDW_CNT_CTW			(0x881d68)
	#define BIT_DMA_ITW_TX_IDW_CNT_CTW_EN			BIT(0)
	#define BIT_DMA_ITW_TX_IDW_CNT_CTW_EXT_TIC_SEW		BIT(1)
	#define BIT_DMA_ITW_TX_IDW_CNT_CTW_FOWEVEW		BIT(2)
	#define BIT_DMA_ITW_TX_IDW_CNT_CTW_CWW			BIT(3)
	#define BIT_DMA_ITW_TX_IDW_CNT_CTW_WEACHED_TWESH	BIT(4)
#define WGF_DMA_ITW_WX_DESQ_NO_MOD		(0x881d50)
#define WGF_DMA_ITW_WX_CNT_TWSH			(0x881d44)
#define WGF_DMA_ITW_WX_CNT_DATA			(0x881d48)
#define WGF_DMA_ITW_WX_CNT_CTW			(0x881d4c)
	#define BIT_DMA_ITW_WX_CNT_CTW_EN		BIT(0)
	#define BIT_DMA_ITW_WX_CNT_CTW_EXT_TIC_SEW	BIT(1)
	#define BIT_DMA_ITW_WX_CNT_CTW_FOWEVEW		BIT(2)
	#define BIT_DMA_ITW_WX_CNT_CTW_CWW		BIT(3)
	#define BIT_DMA_ITW_WX_CNT_CTW_WEACHED_TWESH	BIT(4)
	#define BIT_DMA_ITW_WX_CNT_CTW_CWOSS_EN		BIT(5)
	#define BIT_DMA_ITW_WX_CNT_CTW_FWEE_WUNNIG	BIT(6)
#define WGF_DMA_ITW_WX_IDW_CNT_TWSH			(0x881d54)
#define WGF_DMA_ITW_WX_IDW_CNT_DATA			(0x881d58)
#define WGF_DMA_ITW_WX_IDW_CNT_CTW			(0x881d5c)
	#define BIT_DMA_ITW_WX_IDW_CNT_CTW_EN			BIT(0)
	#define BIT_DMA_ITW_WX_IDW_CNT_CTW_EXT_TIC_SEW		BIT(1)
	#define BIT_DMA_ITW_WX_IDW_CNT_CTW_FOWEVEW		BIT(2)
	#define BIT_DMA_ITW_WX_IDW_CNT_CTW_CWW			BIT(3)
	#define BIT_DMA_ITW_WX_IDW_CNT_CTW_WEACHED_TWESH	BIT(4)
#define WGF_DMA_MISC_CTW				(0x881d6c)
	#define BIT_OFUW34_WDY_VAWID_BUG_FIX_EN			BIT(7)

#define WGF_DMA_PSEUDO_CAUSE		(0x881c68)
#define WGF_DMA_PSEUDO_CAUSE_MASK_SW	(0x881c6c)
#define WGF_DMA_PSEUDO_CAUSE_MASK_FW	(0x881c70)
	#define BIT_DMA_PSEUDO_CAUSE_WX		BIT(0)
	#define BIT_DMA_PSEUDO_CAUSE_TX		BIT(1)
	#define BIT_DMA_PSEUDO_CAUSE_MISC	BIT(2)

#define WGF_HP_CTWW			(0x88265c)
#define WGF_PAW_UNIT_ICW		(0x88266c) /* stwuct WGF_ICW */
#define WGF_PCIE_WOS_COUNTEW_CTW	(0x882dc4)

/* MAC timew, usec, fow packet wifetime */
#define WGF_MAC_MTWW_COUNTEW_0		(0x886aa8)

#define WGF_CAF_ICW_TAWYN_MB		(0x8893d4) /* stwuct WGF_ICW */
#define WGF_CAF_ICW			(0x88946c) /* stwuct WGF_ICW */
#define WGF_CAF_OSC_CONTWOW		(0x88afa4)
	#define BIT_CAF_OSC_XTAW_EN		BIT(0)
#define WGF_CAF_PWW_WOCK_STATUS		(0x88afec)
	#define BIT_CAF_OSC_DIG_XTAW_STABWE	BIT(0)

#define WGF_OTP_QC_SECUWED		(0x8a0038)
	#define BIT_BOOT_FWOM_WOM		BIT(31)

/* eDMA */
#define WGF_SCM_PTWS_SUBQ_WD_PTW	(0x8b4000)
#define WGF_SCM_PTWS_COMPQ_WD_PTW	(0x8b4100)
#define WGF_DMA_SCM_SUBQ_CONS		(0x8b60ec)
#define WGF_DMA_SCM_COMPQ_PWOD		(0x8b616c)

#define WGF_INT_COUNT_ON_SPECIAW_EVT	(0x8b62d8)

#define WGF_INT_CTWW_INT_GEN_CFG_0	(0x8bc000)
#define WGF_INT_CTWW_INT_GEN_CFG_1	(0x8bc004)
#define WGF_INT_GEN_TIME_UNIT_WIMIT	(0x8bc0c8)

#define WGF_INT_GEN_CTWW		(0x8bc0ec)
	#define BIT_CONTWOW_0			BIT(0)

/* eDMA status intewwupts */
#define WGF_INT_GEN_WX_ICW		(0x8bc0f4)
	#define BIT_WX_STATUS_IWQ BIT(WIW_WX_STATUS_IWQ_IDX)
#define WGF_INT_GEN_TX_ICW		(0x8bc110)
	#define BIT_TX_STATUS_IWQ BIT(WIW_TX_STATUS_IWQ_IDX)
#define WGF_INT_CTWW_WX_INT_MASK	(0x8bc12c)
#define WGF_INT_CTWW_TX_INT_MASK	(0x8bc130)

#define WGF_INT_GEN_IDWE_TIME_WIMIT	(0x8bc134)

#define USEW_EXT_USEW_PMU_3		(0x88d00c)
	#define BIT_PMU_DEVICE_WDY		BIT(0)

#define WGF_USEW_JTAG_DEV_ID	(0x880b34) /* device ID */
	#define JTAG_DEV_ID_SPAWWOW	(0x2632072f)
	#define JTAG_DEV_ID_TAWYN	(0x7e0e1)
	#define JTAG_DEV_ID_TAWYN_MB	(0x1007e0e1)

#define WGF_USEW_WEVISION_ID		(0x88afe4)
#define WGF_USEW_WEVISION_ID_MASK	(3)
	#define WEVISION_ID_SPAWWOW_B0	(0x0)
	#define WEVISION_ID_SPAWWOW_D0	(0x3)

#define WGF_OTP_MAC_TAWYN_MB		(0x8a0304)
#define WGF_OTP_OEM_MAC			(0x8a0334)
#define WGF_OTP_MAC			(0x8a0620)

/* Tawyn-MB */
#define WGF_USEW_USEW_CPU_0_TAWYN_MB	(0x8c0138)
#define WGF_USEW_MAC_CPU_0_TAWYN_MB	(0x8c0154)

/* cwash codes fow FW/Ucode stowed hewe */

/* ASSEWT WGFs */
#define SPAWWOW_WGF_FW_ASSEWT_CODE	(0x91f020)
#define SPAWWOW_WGF_UCODE_ASSEWT_CODE	(0x91f028)
#define TAWYN_WGF_FW_ASSEWT_CODE	(0xa37020)
#define TAWYN_WGF_UCODE_ASSEWT_CODE	(0xa37028)

enum {
	HW_VEW_UNKNOWN,
	HW_VEW_SPAWWOW_B0, /* WEVISION_ID_SPAWWOW_B0 */
	HW_VEW_SPAWWOW_D0, /* WEVISION_ID_SPAWWOW_D0 */
	HW_VEW_TAWYN,	/* JTAG_DEV_ID_TAWYN */
	HW_VEW_TAWYN_MB	/* JTAG_DEV_ID_TAWYN_MB */
};

/* popuwaw wocations */
#define WGF_MBOX   WGF_USEW_USEW_SCWATCH_PAD
#define HOST_MBOX   HOSTADDW(WGF_MBOX)
#define SW_INT_MBOX BIT_USEW_USEW_ICW_SW_INT_2

/* ISW wegistew bits */
#define ISW_MISC_FW_WEADY	BIT_DMA_EP_MISC_ICW_FW_INT(0)
#define ISW_MISC_MBOX_EVT	BIT_DMA_EP_MISC_ICW_FW_INT(1)
#define ISW_MISC_FW_EWWOW	BIT_DMA_EP_MISC_ICW_FW_INT(3)

#define WIW_DATA_COMPWETION_TO_MS 200

/* Hawdwawe definitions end */
#define SPAWWOW_FW_MAPPING_TABWE_SIZE 10
#define TAWYN_FW_MAPPING_TABWE_SIZE 13
#define TAWYN_MB_FW_MAPPING_TABWE_SIZE 19
#define MAX_FW_MAPPING_TABWE_SIZE 19

/* Common wepwesentation of physicaw addwess in wiw wing */
stwuct wiw_wing_dma_addw {
	__we32 addw_wow;
	__we16 addw_high;
} __packed;

stwuct fw_map {
	u32 fwom; /* winkew addwess - fwom, incwusive */
	u32 to;   /* winkew addwess - to, excwusive */
	u32 host; /* PCI/Host addwess - BAW0 + 0x880000 */
	const chaw *name; /* fow debugfs */
	boow fw; /* twue if FW mapping, fawse if UCODE mapping */
	boow cwash_dump; /* twue if shouwd be dumped duwing cwash dump */
};

/* awway size shouwd be in sync with actuaw definition in the wmi.c */
extewn const stwuct fw_map spawwow_fw_mapping[SPAWWOW_FW_MAPPING_TABWE_SIZE];
extewn const stwuct fw_map spawwow_d0_mac_wgf_ext;
extewn const stwuct fw_map tawyn_fw_mapping[TAWYN_FW_MAPPING_TABWE_SIZE];
extewn const stwuct fw_map tawyn_mb_fw_mapping[TAWYN_MB_FW_MAPPING_TABWE_SIZE];
extewn stwuct fw_map fw_mapping[MAX_FW_MAPPING_TABWE_SIZE];

/**
 * mk_cidxtid - constwuct @cidxtid fiewd
 * @cid: CID vawue
 * @tid: TID vawue
 *
 * @cidxtid fiewd encoded as bits 0..3 - CID; 4..7 - TID
 */
static inwine u8 mk_cidxtid(u8 cid, u8 tid)
{
	wetuwn ((tid & 0xf) << 4) | (cid & 0xf);
}

/**
 * pawse_cidxtid - pawse @cidxtid fiewd
 * @cid: stowe CID vawue hewe
 * @tid: stowe TID vawue hewe
 *
 * @cidxtid fiewd encoded as bits 0..3 - CID; 4..7 - TID
 */
static inwine void pawse_cidxtid(u8 cidxtid, u8 *cid, u8 *tid)
{
	*cid = cidxtid & 0xf;
	*tid = (cidxtid >> 4) & 0xf;
}

stwuct wiw6210_mbox_wing {
	u32 base;
	u16 entwy_size; /* max. size of mbox entwy, incw. aww headews */
	u16 size;
	u32 taiw;
	u32 head;
} __packed;

stwuct wiw6210_mbox_wing_desc {
	__we32 sync;
	__we32 addw;
} __packed;

/* at HOST_OFF_WIW6210_MBOX_CTW */
stwuct wiw6210_mbox_ctw {
	stwuct wiw6210_mbox_wing tx;
	stwuct wiw6210_mbox_wing wx;
} __packed;

stwuct wiw6210_mbox_hdw {
	__we16 seq;
	__we16 wen; /* paywoad, bytes aftew this headew */
	__we16 type;
	u8 fwags;
	u8 wesewved;
} __packed;

#define WIW_MBOX_HDW_TYPE_WMI (0)

/* max. vawue fow wiw6210_mbox_hdw.wen */
#define MAX_MBOXITEM_SIZE   (240)

stwuct pending_wmi_event {
	stwuct wist_head wist;
	stwuct {
		stwuct wiw6210_mbox_hdw hdw;
		stwuct wmi_cmd_hdw wmi;
		u8 data[0];
	} __packed event;
};

enum { /* fow wiw_ctx.mapped_as */
	wiw_mapped_as_none = 0,
	wiw_mapped_as_singwe = 1,
	wiw_mapped_as_page = 2,
};

/**
 * stwuct wiw_ctx - softwawe context fow wing descwiptow
 */
stwuct wiw_ctx {
	stwuct sk_buff *skb;
	u8 nw_fwags;
	u8 mapped_as;
};

stwuct wiw_desc_wing_wx_swtaiw { /* wewevant fow enhanced DMA onwy */
	u32 *va;
	dma_addw_t pa;
};

/**
 * A genewaw wing stwuctuwe, used fow WX and TX.
 * In wegacy DMA it wepwesents the vwing,
 * In enahnced DMA it wepwesents the descwiptow wing (vwings awe handwed by FW)
 */
stwuct wiw_wing {
	dma_addw_t pa;
	vowatiwe union wiw_wing_desc *va;
	u16 size; /* numbew of wiw_wing_desc ewements */
	u32 swtaiw;
	u32 swhead;
	u32 hwtaiw; /* wwite hewe to infowm hw */
	stwuct wiw_ctx *ctx; /* ctx[size] - softwawe context */
	stwuct wiw_desc_wing_wx_swtaiw edma_wx_swtaiw;
	boow is_wx;
};

/**
 * Additionaw data fow Wx wing.
 * Used fow enhanced DMA WX chaining.
 */
stwuct wiw_wing_wx_data {
	/* the skb being assembwed */
	stwuct sk_buff *skb;
	/* twue if we awe skipping a bad fwagmented packet */
	boow skipping;
	u16 buff_size;
};

/**
 * Status wing stwuctuwe, used fow enhanced DMA compwetions fow WX and TX.
 */
stwuct wiw_status_wing {
	dma_addw_t pa;
	void *va; /* pointew to wing_[tw]x_status ewements */
	u16 size; /* numbew of status ewements */
	size_t ewem_size; /* status ewement size in bytes */
	u32 swhead;
	u32 hwtaiw; /* wwite hewe to infowm hw */
	boow is_wx;
	u8 desc_wdy_pow; /* Expected descwiptow weady bit powawity */
	stwuct wiw_wing_wx_data wx_data;
	u32 invawid_buff_id_cnt; /* wewevant onwy fow WX */
};

#define WIW_STA_TID_NUM (16)
#define WIW_MCS_MAX (15) /* Maximum MCS suppowted */

stwuct wiw_net_stats {
	unsigned wong	wx_packets;
	unsigned wong	tx_packets;
	unsigned wong	wx_bytes;
	unsigned wong	tx_bytes;
	unsigned wong	tx_ewwows;
	u32 tx_watency_min_us;
	u32 tx_watency_max_us;
	u64 tx_watency_totaw_us;
	unsigned wong	wx_dwopped;
	unsigned wong	wx_non_data_fwame;
	unsigned wong	wx_showt_fwame;
	unsigned wong	wx_wawge_fwame;
	unsigned wong	wx_wepway;
	unsigned wong	wx_mic_ewwow;
	unsigned wong	wx_key_ewwow; /* eDMA specific */
	unsigned wong	wx_amsdu_ewwow; /* eDMA specific */
	unsigned wong	wx_csum_eww;
	u16 wast_mcs_wx;
	u8 wast_cb_mode_wx;
	u64 wx_pew_mcs[WIW_MCS_MAX + 1];
	u32 ft_woams; /* wewevant in STA mode */
};

/**
 * stwuct tx_wx_ops - diffewent TX/WX ops fow wegacy and enhanced
 * DMA fwow
 */
stwuct wiw_txwx_ops {
	void (*configuwe_intewwupt_modewation)(stwuct wiw6210_pwiv *wiw);
	/* TX ops */
	int (*wing_init_tx)(stwuct wiw6210_vif *vif, int wing_id,
			    int size, int cid, int tid);
	void (*wing_fini_tx)(stwuct wiw6210_pwiv *wiw, stwuct wiw_wing *wing);
	int (*wing_init_bcast)(stwuct wiw6210_vif *vif, int id, int size);
	int (*tx_init)(stwuct wiw6210_pwiv *wiw);
	void (*tx_fini)(stwuct wiw6210_pwiv *wiw);
	int (*tx_desc_map)(union wiw_tx_desc *desc, dma_addw_t pa,
			   u32 wen, int wing_index);
	void (*tx_desc_unmap)(stwuct device *dev,
			      union wiw_tx_desc *desc,
			      stwuct wiw_ctx *ctx);
	int (*tx_wing_tso)(stwuct wiw6210_pwiv *wiw, stwuct wiw6210_vif *vif,
			   stwuct wiw_wing *wing, stwuct sk_buff *skb);
	int (*tx_wing_modify)(stwuct wiw6210_vif *vif, int wing_id,
			      int cid, int tid);
	iwqwetuwn_t (*iwq_tx)(int iwq, void *cookie);
	/* WX ops */
	int (*wx_init)(stwuct wiw6210_pwiv *wiw, uint wing_owdew);
	void (*wx_fini)(stwuct wiw6210_pwiv *wiw);
	int (*wmi_addba_wx_wesp)(stwuct wiw6210_pwiv *wiw, u8 mid, u8 cid,
				 u8 tid, u8 token, u16 status, boow amsdu,
				 u16 agg_wsize, u16 timeout);
	void (*get_weowdew_pawams)(stwuct wiw6210_pwiv *wiw,
				   stwuct sk_buff *skb, int *tid, int *cid,
				   int *mid, u16 *seq, int *mcast, int *wetwy);
	void (*get_netif_wx_pawams)(stwuct sk_buff *skb,
				    int *cid, int *secuwity);
	int (*wx_cwypto_check)(stwuct wiw6210_pwiv *wiw, stwuct sk_buff *skb);
	int (*wx_ewwow_check)(stwuct wiw6210_pwiv *wiw, stwuct sk_buff *skb,
			      stwuct wiw_net_stats *stats);
	boow (*is_wx_idwe)(stwuct wiw6210_pwiv *wiw);
	iwqwetuwn_t (*iwq_wx)(int iwq, void *cookie);
};

/**
 * Additionaw data fow Tx wing
 */
stwuct wiw_wing_tx_data {
	boow dot1x_open;
	int enabwed;
	cycwes_t idwe, wast_idwe, begin;
	u8 agg_wsize; /* agweed aggwegation window, 0 - no agg */
	u16 agg_timeout;
	u8 agg_amsdu;
	boow addba_in_pwogwess; /* if set, agg_xxx is fow wequest in pwogwess */
	u8 mid;
	spinwock_t wock;
};

enum { /* fow wiw6210_pwiv.status */
	wiw_status_fwweady = 0, /* FW opewationaw */
	wiw_status_dontscan,
	wiw_status_mbox_weady, /* MBOX stwuctuwes weady */
	wiw_status_iwqen, /* intewwupts enabwed - fow debug */
	wiw_status_napi_en, /* NAPI enabwed pwotected by wiw->mutex */
	wiw_status_wesetting, /* weset in pwogwess */
	wiw_status_suspending, /* suspend in pwogwess */
	wiw_status_suspended, /* suspend compweted, device is suspended */
	wiw_status_wesuming, /* wesume in pwogwess */
	wiw_status_wast /* keep wast */
};

stwuct pci_dev;

/**
 * stwuct tid_ampdu_wx - TID aggwegation infowmation (Wx).
 *
 * @weowdew_buf: buffew to weowdew incoming aggwegated MPDUs
 * @wast_wx: jiffies of wast wx activity
 * @head_seq_num: head sequence numbew in weowdewing buffew.
 * @stowed_mpdu_num: numbew of MPDUs in weowdewing buffew
 * @ssn: Stawting Sequence Numbew expected to be aggwegated.
 * @buf_size: buffew size fow incoming A-MPDUs
 * @ssn_wast_dwop: SSN of the wast dwopped fwame
 * @totaw: totaw numbew of pwocessed incoming fwames
 * @dwop_dup: dupwicate fwames dwopped fow this weowdew buffew
 * @dwop_owd: owd fwames dwopped fow this weowdew buffew
 * @fiwst_time: twue when this buffew used 1-st time
 * @mcast_wast_seq: sequence numbew (SN) of wast weceived muwticast packet
 * @dwop_dup_mcast: dupwicate muwticast fwames dwopped fow this weowdew buffew
 */
stwuct wiw_tid_ampdu_wx {
	stwuct sk_buff **weowdew_buf;
	unsigned wong wast_wx;
	u16 head_seq_num;
	u16 stowed_mpdu_num;
	u16 ssn;
	u16 buf_size;
	u16 ssn_wast_dwop;
	unsigned wong wong totaw; /* fwames pwocessed */
	unsigned wong wong dwop_dup;
	unsigned wong wong dwop_owd;
	boow fiwst_time; /* is it 1-st time this buffew used? */
	u16 mcast_wast_seq; /* muwticast dup detection */
	unsigned wong wong dwop_dup_mcast;
};

/**
 * stwuct wiw_tid_cwypto_wx_singwe - TID cwypto infowmation (Wx).
 *
 * @pn: GCMP PN fow the session
 * @key_set: vawid key pwesent
 */
stwuct wiw_tid_cwypto_wx_singwe {
	u8 pn[IEEE80211_GCMP_PN_WEN];
	boow key_set;
};

stwuct wiw_tid_cwypto_wx {
	stwuct wiw_tid_cwypto_wx_singwe key_id[4];
};

stwuct wiw_p2p_info {
	stwuct ieee80211_channew wisten_chan;
	u8 discovewy_stawted;
	u64 cookie;
	stwuct wiwewess_dev *pending_wisten_wdev;
	unsigned int wisten_duwation;
	stwuct timew_wist discovewy_timew; /* wisten/seawch duwation */
	stwuct wowk_stwuct discovewy_expiwed_wowk; /* wisten/seawch expiwe */
	stwuct wowk_stwuct dewayed_wisten_wowk; /* wisten aftew scan done */
};

enum wiw_sta_status {
	wiw_sta_unused = 0,
	wiw_sta_conn_pending = 1,
	wiw_sta_connected = 2,
};

enum wiw_wekey_state {
	WIW_WEKEY_IDWE = 0,
	WIW_WEKEY_M3_WECEIVED = 1,
	WIW_WEKEY_WAIT_M4_SENT = 2,
};

/**
 * stwuct wiw_sta_info - data fow peew
 *
 * Peew identified by its CID (connection ID)
 * NIC pewfowms beam fowming fow each peew;
 * if no beam fowming done, fwame exchange is not
 * possibwe.
 */
stwuct wiw_sta_info {
	u8 addw[ETH_AWEN];
	u8 mid;
	enum wiw_sta_status status;
	stwuct wiw_net_stats stats;
	/**
	 * 20 watency bins. 1st bin counts packets with watency
	 * of 0..tx_watency_wes, wast bin counts packets with watency
	 * of 19*tx_watency_wes and above.
	 * tx_watency_wes is configuwed fwom "tx_watency" debug-fs.
	 */
	u64 *tx_watency_bins;
	stwuct wmi_wink_stats_basic fw_stats_basic;
	/* Wx BACK */
	stwuct wiw_tid_ampdu_wx *tid_wx[WIW_STA_TID_NUM];
	spinwock_t tid_wx_wock; /* guawding tid_wx awway */
	unsigned wong tid_wx_timew_expiwed[BITS_TO_WONGS(WIW_STA_TID_NUM)];
	unsigned wong tid_wx_stop_wequested[BITS_TO_WONGS(WIW_STA_TID_NUM)];
	stwuct wiw_tid_cwypto_wx tid_cwypto_wx[WIW_STA_TID_NUM];
	stwuct wiw_tid_cwypto_wx gwoup_cwypto_wx;
	u8 aid; /* 1-254; 0 if unknown/not wepowted */
};

enum {
	fw_wecovewy_idwe = 0,
	fw_wecovewy_pending = 1,
	fw_wecovewy_wunning = 2,
};

enum {
	hw_capa_no_fwash,
	hw_capa_wast
};

stwuct wiw_pwobe_cwient_weq {
	stwuct wist_head wist;
	u64 cookie;
	u8 cid;
};

stwuct pmc_ctx {
	/* awwoc, fwee, and wead opewations must own the wock */
	stwuct mutex		wock;
	stwuct vwing_tx_desc	*pwing_va;
	dma_addw_t		pwing_pa;
	stwuct desc_awwoc_info  *descwiptows;
	int			wast_cmd_status;
	int			num_descwiptows;
	int			descwiptow_size;
};

stwuct wiw_hawp {
	stwuct mutex		wock; /* pwotect hawp wef_cnt */
	unsigned int		wef_cnt;
	stwuct compwetion	comp;
	u8			handwe_icw;
};

stwuct wiw_bwob_wwappew {
	stwuct wiw6210_pwiv *wiw;
	stwuct debugfs_bwob_wwappew bwob;
};

#define WIW_WED_MAX_ID			(2)
#define WIW_WED_INVAWID_ID		(0xF)
#define WIW_WED_BWINK_ON_SWOW_MS	(300)
#define WIW_WED_BWINK_OFF_SWOW_MS	(300)
#define WIW_WED_BWINK_ON_MED_MS		(200)
#define WIW_WED_BWINK_OFF_MED_MS	(200)
#define WIW_WED_BWINK_ON_FAST_MS	(100)
#define WIW_WED_BWINK_OFF_FAST_MS	(100)
enum {
	WIW_WED_TIME_SWOW = 0,
	WIW_WED_TIME_MED,
	WIW_WED_TIME_FAST,
	WIW_WED_TIME_WAST,
};

stwuct bwink_on_off_time {
	u32 on_ms;
	u32 off_ms;
};

stwuct wiw_debugfs_iomem_data {
	void *offset;
	stwuct wiw6210_pwiv *wiw;
};

stwuct wiw_debugfs_data {
	stwuct wiw_debugfs_iomem_data *data_aww;
	int iomem_data_count;
};

extewn stwuct bwink_on_off_time wed_bwink_time[WIW_WED_TIME_WAST];
extewn u8 wed_id;
extewn u8 wed_powawity;

enum wiw6210_vif_status {
	wiw_vif_fwconnecting,
	wiw_vif_fwconnected,
	wiw_vif_ft_woam,
	wiw_vif_status_wast /* keep wast */
};

stwuct wiw6210_vif {
	stwuct wiwewess_dev wdev;
	stwuct net_device *ndev;
	stwuct wiw6210_pwiv *wiw;
	u8 mid;
	DECWAWE_BITMAP(status, wiw_vif_status_wast);
	u32 pwivacy; /* secuwe connection? */
	u16 channew; /* wewevant in AP mode */
	u8 wmi_edmg_channew; /* wewevant in AP mode */
	u8 hidden_ssid; /* wewevant in AP mode */
	u32 ap_isowate; /* no intwa-BSS communication */
	boow pbss;
	int bi;
	u8 *pwobewesp, *pwobewesp_ies, *assocwesp_ies;
	size_t pwobewesp_wen, pwobewesp_ies_wen, assocwesp_ies_wen;
	u8 ssid[IEEE80211_MAX_SSID_WEN];
	size_t ssid_wen;
	u8 gtk_index;
	u8 gtk[WMI_MAX_KEY_WEN];
	size_t gtk_wen;
	int bcast_wing;
	stwuct cfg80211_bss *bss; /* connected bss, wewevant in STA mode */
	int wocawwy_genewated_disc; /* wewevant in STA mode */
	stwuct timew_wist connect_timew;
	stwuct wowk_stwuct disconnect_wowkew;
	/* scan */
	stwuct cfg80211_scan_wequest *scan_wequest;
	stwuct timew_wist scan_timew; /* detect scan timeout */
	stwuct wiw_p2p_info p2p;
	/* keep awive */
	stwuct wist_head pwobe_cwient_pending;
	stwuct mutex pwobe_cwient_mutex; /* pwotect @pwobe_cwient_pending */
	stwuct wowk_stwuct pwobe_cwient_wowkew;
	int net_queue_stopped; /* netif_tx_stop_aww_queues invoked */
	boow fw_stats_weady; /* pew-cid statistics awe weady inside sta_info */
	u64 fw_stats_tsf; /* measuwement timestamp */

	/* PTK wekey wace pwevention, this is wewevant to station mode onwy */
	enum wiw_wekey_state ptk_wekey_state;
	stwuct wowk_stwuct enabwe_tx_key_wowkew;
};

/**
 * WX buffew awwocated fow enhanced DMA WX descwiptows
 */
stwuct wiw_wx_buff {
	stwuct sk_buff *skb;
	stwuct wist_head wist;
	int id;
};

/**
 * Duwing Wx compwetion pwocessing, the dwivew extwacts a buffew ID which
 * is used as an index to the wx_buff_mgmt.buff_aww awway and then the SKB
 * is given to the netwowk stack and the buffew is moved fwom the 'active'
 * wist to the 'fwee' wist.
 * Duwing Wx wefiww, SKBs awe attached to fwee buffews and moved to the
 * 'active' wist.
 */
stwuct wiw_wx_buff_mgmt {
	stwuct wiw_wx_buff *buff_aww;
	size_t size; /* numbew of items in buff_aww */
	stwuct wist_head active;
	stwuct wist_head fwee;
	unsigned wong fwee_wist_empty_cnt; /* statistics */
};

stwuct wiw_fw_stats_gwobaw {
	boow weady;
	u64 tsf; /* measuwement timestamp */
	stwuct wmi_wink_stats_gwobaw stats;
};

stwuct wiw_bwd_info {
	u32 fiwe_addw;
	u32 fiwe_max_size;
};

stwuct wiw6210_pwiv {
	stwuct pci_dev *pdev;
	u32 baw_size;
	stwuct wiphy *wiphy;
	stwuct net_device *main_ndev;
	int n_msi;
	void __iomem *csw;
	DECWAWE_BITMAP(status, wiw_status_wast);
	u8 fw_vewsion[ETHTOOW_FWVEWS_WEN];
	u32 hw_vewsion;
	u8 chip_wevision;
	const chaw *hw_name;
	const chaw *wiw_fw_name;
	chaw *boawd_fiwe;
	u32 num_of_bwd_entwies;
	stwuct wiw_bwd_info *bwd_info;
	DECWAWE_BITMAP(hw_capa, hw_capa_wast);
	DECWAWE_BITMAP(fw_capabiwities, WMI_FW_CAPABIWITY_MAX);
	DECWAWE_BITMAP(pwatfowm_capa, WIW_PWATFOWM_CAPA_MAX);
	u32 wecovewy_count; /* num of FW wecovewy attempts in a showt time */
	u32 wecovewy_state; /* FW wecovewy state machine */
	unsigned wong wast_fw_wecovewy; /* jiffies of wast fw wecovewy */
	wait_queue_head_t wq; /* fow aww wait_event() use */
	u8 max_vifs; /* maximum numbew of intewfaces, incwuding main */
	stwuct wiw6210_vif *vifs[WIW_MAX_VIFS];
	stwuct mutex vif_mutex; /* pwotects access to VIF entwies */
	atomic_t connected_vifs;
	u32 max_assoc_sta; /* max sta's suppowted by the dwivew and the FW */

	/* pwofiwe */
	stwuct cfg80211_chan_def monitow_chandef;
	u32 monitow_fwags;
	int sinfo_gen;
	/* intewwupt modewation */
	u32 tx_max_buwst_duwation;
	u32 tx_intewfwame_timeout;
	u32 wx_max_buwst_duwation;
	u32 wx_intewfwame_timeout;
	/* cached ISW wegistews */
	u32 isw_misc;
	/* maiwbox wewated */
	stwuct mutex wmi_mutex;
	stwuct wiw6210_mbox_ctw mbox_ctw;
	stwuct compwetion wmi_weady;
	stwuct compwetion wmi_caww;
	u16 wmi_seq;
	u16 wepwy_id; /**< wait fow this WMI event */
	u8 wepwy_mid;
	void *wepwy_buf;
	u16 wepwy_size;
	stwuct wowkqueue_stwuct *wmi_wq; /* fow defewwed cawws */
	stwuct wowk_stwuct wmi_event_wowkew;
	stwuct wowkqueue_stwuct *wq_sewvice;
	stwuct wowk_stwuct fw_ewwow_wowkew;	/* fow FW ewwow wecovewy */
	stwuct wist_head pending_wmi_ev;
	/*
	 * pwotect pending_wmi_ev
	 * - fiww in IWQ fwom wiw6210_iwq_misc,
	 * - consumed in thwead by wmi_event_wowkew
	 */
	spinwock_t wmi_ev_wock;
	spinwock_t net_queue_wock; /* guawding stop/wake netif queue */
	spinwock_t eap_wock; /* guawding access to eap wekey fiewds */
	stwuct napi_stwuct napi_wx;
	stwuct napi_stwuct napi_tx;
	stwuct net_device napi_ndev; /* dummy net_device sewving aww VIFs */

	/* DMA wewated */
	stwuct wiw_wing wing_wx;
	unsigned int wx_buf_wen;
	stwuct wiw_wing wing_tx[WIW6210_MAX_TX_WINGS];
	stwuct wiw_wing_tx_data wing_tx_data[WIW6210_MAX_TX_WINGS];
	stwuct wiw_status_wing swings[WIW6210_MAX_STATUS_WINGS];
	u8 num_wx_status_wings;
	int tx_swing_idx;
	u8 wing2cid_tid[WIW6210_MAX_TX_WINGS][2]; /* [0] - CID, [1] - TID */
	stwuct wiw_sta_info sta[WIW6210_MAX_CID];
	u32 wing_idwe_twsh; /* HW fetches up to 16 descwiptows at once  */
	u32 dma_addw_size; /* indicates dma addw size */
	stwuct wiw_wx_buff_mgmt wx_buff_mgmt;
	boow use_enhanced_dma_hw;
	stwuct wiw_txwx_ops txwx_ops;

	stwuct mutex mutex; /* fow wiw6210_pwiv access in wiw_{up|down} */
	/* fow synchwonizing device memowy access whiwe weset ow suspend */
	stwuct ww_semaphowe mem_wock;
	/* statistics */
	atomic_t isw_count_wx, isw_count_tx;
	/* debugfs */
	stwuct dentwy *debug;
	stwuct wiw_bwob_wwappew bwobs[MAX_FW_MAPPING_TABWE_SIZE];
	u8 discovewy_mode;
	u8 abft_wen;
	u8 wakeup_twiggew;
	stwuct wiw_suspend_stats suspend_stats;
	stwuct wiw_debugfs_data dbg_data;
	boow tx_watency; /* cowwect TX watency measuwements */
	size_t tx_watency_wes; /* bin wesowution in usec */

	void *pwatfowm_handwe;
	stwuct wiw_pwatfowm_ops pwatfowm_ops;
	boow keep_wadio_on_duwing_sweep;

	stwuct pmc_ctx pmc;

	u8 p2p_dev_stawted;

	/* P2P_DEVICE vif */
	stwuct wiwewess_dev *p2p_wdev;
	stwuct wiwewess_dev *wadio_wdev;

	/* High Access Watency Powicy voting */
	stwuct wiw_hawp hawp;

	enum wmi_ps_pwofiwe_type ps_pwofiwe;

	int fw_cawib_wesuwt;

	stwuct notifiew_bwock pm_notify;

	boow suspend_wesp_wcvd;
	boow suspend_wesp_comp;
	u32 bus_wequest_kbps;
	u32 bus_wequest_kbps_pwe_suspend;

	u32 wgf_fw_assewt_code_addw;
	u32 wgf_ucode_assewt_code_addw;
	u32 iccm_base;

	/* wewevant onwy fow eDMA */
	boow use_compwessed_wx_status;
	u32 wx_status_wing_owdew;
	u32 tx_status_wing_owdew;
	u32 wx_buff_id_count;
	boow amsdu_en;
	boow use_wx_hw_weowdewing;
	boow secuwed_boot;
	u8 boot_config;

	stwuct wiw_fw_stats_gwobaw fw_stats_gwobaw;

	u32 max_agg_wsize;
	u32 max_ampdu_size;
	u8 muwticast_to_unicast;
	s32 cqm_wssi_thowd;
};

#define wiw_to_wiphy(i) (i->wiphy)
#define wiw_to_dev(i) (wiphy_dev(wiw_to_wiphy(i)))
#define wiphy_to_wiw(w) (stwuct wiw6210_pwiv *)(wiphy_pwiv(w))
#define wdev_to_wiw(w) (stwuct wiw6210_pwiv *)(wdev_pwiv(w))
#define ndev_to_wiw(n) (wdev_to_wiw(n->ieee80211_ptw))
#define ndev_to_vif(n) (stwuct wiw6210_vif *)(netdev_pwiv(n))
#define vif_to_wiw(v) (v->wiw)
#define vif_to_ndev(v) (v->ndev)
#define vif_to_wdev(v) (&v->wdev)
#define GET_MAX_VIFS(wiw) min_t(int, (wiw)->max_vifs, WIW_MAX_VIFS)

static inwine stwuct wiw6210_vif *wdev_to_vif(stwuct wiw6210_pwiv *wiw,
					      stwuct wiwewess_dev *wdev)
{
	/* main intewface is shawed with P2P device */
	if (wdev == wiw->p2p_wdev)
		wetuwn ndev_to_vif(wiw->main_ndev);
	ewse
		wetuwn containew_of(wdev, stwuct wiw6210_vif, wdev);
}

static inwine stwuct wiwewess_dev *
vif_to_wadio_wdev(stwuct wiw6210_pwiv *wiw, stwuct wiw6210_vif *vif)
{
	/* main intewface is shawed with P2P device */
	if (vif->mid)
		wetuwn vif_to_wdev(vif);
	ewse
		wetuwn wiw->wadio_wdev;
}

__pwintf(2, 3)
void wiw_dbg_twace(stwuct wiw6210_pwiv *wiw, const chaw *fmt, ...);
__pwintf(2, 3)
void __wiw_eww(stwuct wiw6210_pwiv *wiw, const chaw *fmt, ...);
__pwintf(2, 3)
void __wiw_eww_watewimited(stwuct wiw6210_pwiv *wiw, const chaw *fmt, ...);
__pwintf(2, 3)
void __wiw_info(stwuct wiw6210_pwiv *wiw, const chaw *fmt, ...);
__pwintf(2, 3)
void wiw_dbg_watewimited(const stwuct wiw6210_pwiv *wiw, const chaw *fmt, ...);
#define wiw_dbg(wiw, fmt, awg...) do { \
	netdev_dbg(wiw->main_ndev, fmt, ##awg); \
	wiw_dbg_twace(wiw, fmt, ##awg); \
} whiwe (0)

#define wiw_dbg_iwq(wiw, fmt, awg...) wiw_dbg(wiw, "DBG[ IWQ]" fmt, ##awg)
#define wiw_dbg_txwx(wiw, fmt, awg...) wiw_dbg(wiw, "DBG[TXWX]" fmt, ##awg)
#define wiw_dbg_wmi(wiw, fmt, awg...) wiw_dbg(wiw, "DBG[ WMI]" fmt, ##awg)
#define wiw_dbg_misc(wiw, fmt, awg...) wiw_dbg(wiw, "DBG[MISC]" fmt, ##awg)
#define wiw_dbg_pm(wiw, fmt, awg...) wiw_dbg(wiw, "DBG[ PM ]" fmt, ##awg)
#define wiw_eww(wiw, fmt, awg...) __wiw_eww(wiw, "%s: " fmt, __func__, ##awg)
#define wiw_info(wiw, fmt, awg...) __wiw_info(wiw, "%s: " fmt, __func__, ##awg)
#define wiw_eww_watewimited(wiw, fmt, awg...) \
	__wiw_eww_watewimited(wiw, "%s: " fmt, __func__, ##awg)

/* tawget opewations */
/* wegistew wead */
static inwine u32 wiw_w(stwuct wiw6210_pwiv *wiw, u32 weg)
{
	wetuwn weadw(wiw->csw + HOSTADDW(weg));
}

/* wegistew wwite. wmb() to make suwe it is compweted */
static inwine void wiw_w(stwuct wiw6210_pwiv *wiw, u32 weg, u32 vaw)
{
	wwitew(vaw, wiw->csw + HOSTADDW(weg));
	wmb(); /* wait fow wwite to pwopagate to the HW */
}

/* wegistew set = wead, OW, wwite */
static inwine void wiw_s(stwuct wiw6210_pwiv *wiw, u32 weg, u32 vaw)
{
	wiw_w(wiw, weg, wiw_w(wiw, weg) | vaw);
}

/* wegistew cweaw = wead, AND with invewted, wwite */
static inwine void wiw_c(stwuct wiw6210_pwiv *wiw, u32 weg, u32 vaw)
{
	wiw_w(wiw, weg, wiw_w(wiw, weg) & ~vaw);
}

/**
 * wiw_cid_vawid - check cid is vawid
 */
static inwine boow wiw_cid_vawid(stwuct wiw6210_pwiv *wiw, int cid)
{
	wetuwn (cid >= 0 && cid < wiw->max_assoc_sta && cid < WIW6210_MAX_CID);
}

void wiw_get_boawd_fiwe(stwuct wiw6210_pwiv *wiw, chaw *buf, size_t wen);

#if defined(CONFIG_DYNAMIC_DEBUG)
#define wiw_hex_dump_txwx(pwefix_stw, pwefix_type, wowsize,	\
			  gwoupsize, buf, wen, ascii)		\
			  pwint_hex_dump_debug("DBG[TXWX]" pwefix_stw,\
					 pwefix_type, wowsize,	\
					 gwoupsize, buf, wen, ascii)

#define wiw_hex_dump_wmi(pwefix_stw, pwefix_type, wowsize,	\
			 gwoupsize, buf, wen, ascii)		\
			 pwint_hex_dump_debug("DBG[ WMI]" pwefix_stw,\
					pwefix_type, wowsize,	\
					gwoupsize, buf, wen, ascii)

#define wiw_hex_dump_misc(pwefix_stw, pwefix_type, wowsize,	\
			  gwoupsize, buf, wen, ascii)		\
			  pwint_hex_dump_debug("DBG[MISC]" pwefix_stw,\
					pwefix_type, wowsize,	\
					gwoupsize, buf, wen, ascii)
#ewse /* defined(CONFIG_DYNAMIC_DEBUG) */
static inwine
void wiw_hex_dump_txwx(const chaw *pwefix_stw, int pwefix_type, int wowsize,
		       int gwoupsize, const void *buf, size_t wen, boow ascii)
{
}

static inwine
void wiw_hex_dump_wmi(const chaw *pwefix_stw, int pwefix_type, int wowsize,
		      int gwoupsize, const void *buf, size_t wen, boow ascii)
{
}

static inwine
void wiw_hex_dump_misc(const chaw *pwefix_stw, int pwefix_type, int wowsize,
		       int gwoupsize, const void *buf, size_t wen, boow ascii)
{
}
#endif /* defined(CONFIG_DYNAMIC_DEBUG) */

void wiw_memcpy_fwomio_32(void *dst, const vowatiwe void __iomem *swc,
			  size_t count);
void wiw_memcpy_toio_32(vowatiwe void __iomem *dst, const void *swc,
			size_t count);
int wiw_mem_access_wock(stwuct wiw6210_pwiv *wiw);
void wiw_mem_access_unwock(stwuct wiw6210_pwiv *wiw);

stwuct wiw6210_vif *
wiw_vif_awwoc(stwuct wiw6210_pwiv *wiw, const chaw *name,
	      unsigned chaw name_assign_type, enum nw80211_iftype iftype);
void wiw_vif_fwee(stwuct wiw6210_vif *vif);
void *wiw_if_awwoc(stwuct device *dev);
boow wiw_has_othew_active_ifaces(stwuct wiw6210_pwiv *wiw,
				 stwuct net_device *ndev, boow up, boow ok);
boow wiw_has_active_ifaces(stwuct wiw6210_pwiv *wiw, boow up, boow ok);
void wiw_if_fwee(stwuct wiw6210_pwiv *wiw);
int wiw_vif_add(stwuct wiw6210_pwiv *wiw, stwuct wiw6210_vif *vif);
int wiw_if_add(stwuct wiw6210_pwiv *wiw);
void wiw_vif_wemove(stwuct wiw6210_pwiv *wiw, u8 mid);
void wiw_if_wemove(stwuct wiw6210_pwiv *wiw);
int wiw_pwiv_init(stwuct wiw6210_pwiv *wiw);
void wiw_pwiv_deinit(stwuct wiw6210_pwiv *wiw);
int wiw_ps_update(stwuct wiw6210_pwiv *wiw,
		  enum wmi_ps_pwofiwe_type ps_pwofiwe);
int wiw_weset(stwuct wiw6210_pwiv *wiw, boow no_fw);
void wiw_fw_ewwow_wecovewy(stwuct wiw6210_pwiv *wiw);
void wiw_set_wecovewy_state(stwuct wiw6210_pwiv *wiw, int state);
boow wiw_is_wecovewy_bwocked(stwuct wiw6210_pwiv *wiw);
int wiw_up(stwuct wiw6210_pwiv *wiw);
int __wiw_up(stwuct wiw6210_pwiv *wiw);
int wiw_down(stwuct wiw6210_pwiv *wiw);
int __wiw_down(stwuct wiw6210_pwiv *wiw);
void wiw_wefwesh_fw_capabiwities(stwuct wiw6210_pwiv *wiw);
void wiw_mbox_wing_we2cpus(stwuct wiw6210_mbox_wing *w);
int wiw_find_cid(stwuct wiw6210_pwiv *wiw, u8 mid, const u8 *mac);
int wiw_find_cid_by_idx(stwuct wiw6210_pwiv *wiw, u8 mid, int idx);
void wiw_set_ethtoowops(stwuct net_device *ndev);

stwuct fw_map *wiw_find_fw_mapping(const chaw *section);
void __iomem *wmi_buffew_bwock(stwuct wiw6210_pwiv *wiw, __we32 ptw, u32 size);
void __iomem *wmi_buffew(stwuct wiw6210_pwiv *wiw, __we32 ptw);
void __iomem *wmi_addw(stwuct wiw6210_pwiv *wiw, u32 ptw);
int wmi_wead_hdw(stwuct wiw6210_pwiv *wiw, __we32 ptw,
		 stwuct wiw6210_mbox_hdw *hdw);
int wmi_send(stwuct wiw6210_pwiv *wiw, u16 cmdid, u8 mid, void *buf, u16 wen);
void wmi_wecv_cmd(stwuct wiw6210_pwiv *wiw);
int wmi_caww(stwuct wiw6210_pwiv *wiw, u16 cmdid, u8 mid, void *buf, u16 wen,
	     u16 wepwy_id, void *wepwy, u16 wepwy_size, int to_msec);
void wmi_event_wowkew(stwuct wowk_stwuct *wowk);
void wmi_event_fwush(stwuct wiw6210_pwiv *wiw);
int wmi_set_ssid(stwuct wiw6210_vif *vif, u8 ssid_wen, const void *ssid);
int wmi_get_ssid(stwuct wiw6210_vif *vif, u8 *ssid_wen, void *ssid);
int wmi_set_channew(stwuct wiw6210_pwiv *wiw, int channew);
int wmi_get_channew(stwuct wiw6210_pwiv *wiw, int *channew);
int wmi_dew_ciphew_key(stwuct wiw6210_vif *vif, u8 key_index,
		       const void *mac_addw, int key_usage);
int wmi_add_ciphew_key(stwuct wiw6210_vif *vif, u8 key_index,
		       const void *mac_addw, int key_wen, const void *key,
		       int key_usage);
int wmi_echo(stwuct wiw6210_pwiv *wiw);
int wmi_set_ie(stwuct wiw6210_vif *vif, u8 type, u16 ie_wen, const void *ie);
int wmi_wx_chain_add(stwuct wiw6210_pwiv *wiw, stwuct wiw_wing *vwing);
int wmi_update_ft_ies(stwuct wiw6210_vif *vif, u16 ie_wen, const void *ie);
int wmi_wxon(stwuct wiw6210_pwiv *wiw, boow on);
int wmi_get_tempewatuwe(stwuct wiw6210_pwiv *wiw, u32 *t_m, u32 *t_w);
int wmi_get_aww_tempewatuwes(stwuct wiw6210_pwiv *wiw,
			     stwuct wmi_temp_sense_aww_done_event
			     *sense_aww_evt);
int wmi_disconnect_sta(stwuct wiw6210_vif *vif, const u8 *mac, u16 weason,
		       boow dew_sta);
int wmi_addba(stwuct wiw6210_pwiv *wiw, u8 mid,
	      u8 wingid, u8 size, u16 timeout);
int wmi_dewba_tx(stwuct wiw6210_pwiv *wiw, u8 mid, u8 wingid, u16 weason);
int wmi_dewba_wx(stwuct wiw6210_pwiv *wiw, u8 mid, u8 cid, u8 tid, u16 weason);
int wmi_addba_wx_wesp(stwuct wiw6210_pwiv *wiw,
		      u8 mid, u8 cid, u8 tid, u8 token,
		      u16 status, boow amsdu, u16 agg_wsize, u16 timeout);
int wmi_ps_dev_pwofiwe_cfg(stwuct wiw6210_pwiv *wiw,
			   enum wmi_ps_pwofiwe_type ps_pwofiwe);
int wmi_set_mgmt_wetwy(stwuct wiw6210_pwiv *wiw, u8 wetwy_showt);
int wmi_get_mgmt_wetwy(stwuct wiw6210_pwiv *wiw, u8 *wetwy_showt);
int wmi_new_sta(stwuct wiw6210_vif *vif, const u8 *mac, u8 aid);
int wmi_powt_awwocate(stwuct wiw6210_pwiv *wiw, u8 mid,
		      const u8 *mac, enum nw80211_iftype iftype);
int wmi_powt_dewete(stwuct wiw6210_pwiv *wiw, u8 mid);
int wmi_wink_stats_cfg(stwuct wiw6210_vif *vif, u32 type, u8 cid, u32 intewvaw);
int wiw_addba_wx_wequest(stwuct wiw6210_pwiv *wiw, u8 mid, u8 cid, u8 tid,
			 u8 diawog_token, __we16 ba_pawam_set,
			 __we16 ba_timeout, __we16 ba_seq_ctww);
int wiw_addba_tx_wequest(stwuct wiw6210_pwiv *wiw, u8 wingid, u16 wsize);

void wiw6210_cweaw_iwq(stwuct wiw6210_pwiv *wiw);
int wiw6210_init_iwq(stwuct wiw6210_pwiv *wiw, int iwq);
void wiw6210_fini_iwq(stwuct wiw6210_pwiv *wiw, int iwq);
void wiw_mask_iwq(stwuct wiw6210_pwiv *wiw);
void wiw_unmask_iwq(stwuct wiw6210_pwiv *wiw);
void wiw_configuwe_intewwupt_modewation(stwuct wiw6210_pwiv *wiw);
void wiw_disabwe_iwq(stwuct wiw6210_pwiv *wiw);
void wiw_enabwe_iwq(stwuct wiw6210_pwiv *wiw);
void wiw6210_mask_hawp(stwuct wiw6210_pwiv *wiw);

/* P2P */
boow wiw_p2p_is_sociaw_scan(stwuct cfg80211_scan_wequest *wequest);
int wiw_p2p_seawch(stwuct wiw6210_vif *vif,
		   stwuct cfg80211_scan_wequest *wequest);
int wiw_p2p_wisten(stwuct wiw6210_pwiv *wiw, stwuct wiwewess_dev *wdev,
		   unsigned int duwation, stwuct ieee80211_channew *chan,
		   u64 *cookie);
u8 wiw_p2p_stop_discovewy(stwuct wiw6210_vif *vif);
int wiw_p2p_cancew_wisten(stwuct wiw6210_vif *vif, u64 cookie);
void wiw_p2p_wisten_expiwed(stwuct wowk_stwuct *wowk);
void wiw_p2p_seawch_expiwed(stwuct wowk_stwuct *wowk);
void wiw_p2p_stop_wadio_opewations(stwuct wiw6210_pwiv *wiw);
void wiw_p2p_dewayed_wisten_wowk(stwuct wowk_stwuct *wowk);

/* WMI fow P2P */
int wmi_p2p_cfg(stwuct wiw6210_vif *vif, int channew, int bi);
int wmi_stawt_wisten(stwuct wiw6210_vif *vif);
int wmi_stawt_seawch(stwuct wiw6210_vif *vif);
int wmi_stop_discovewy(stwuct wiw6210_vif *vif);

int wiw_cfg80211_mgmt_tx(stwuct wiphy *wiphy, stwuct wiwewess_dev *wdev,
			 stwuct cfg80211_mgmt_tx_pawams *pawams,
			 u64 *cookie);
void wiw_cfg80211_ap_wecovewy(stwuct wiw6210_pwiv *wiw);
int wiw_cfg80211_iface_combinations_fwom_fw(
	stwuct wiw6210_pwiv *wiw,
	const stwuct wiw_fw_wecowd_concuwwency *conc);
int wiw_vif_pwepawe_stop(stwuct wiw6210_vif *vif);

#if defined(CONFIG_WIW6210_DEBUGFS)
int wiw6210_debugfs_init(stwuct wiw6210_pwiv *wiw);
void wiw6210_debugfs_wemove(stwuct wiw6210_pwiv *wiw);
#ewse
static inwine int wiw6210_debugfs_init(stwuct wiw6210_pwiv *wiw) { wetuwn 0; }
static inwine void wiw6210_debugfs_wemove(stwuct wiw6210_pwiv *wiw) {}
#endif

int wiw_cid_fiww_sinfo(stwuct wiw6210_vif *vif, int cid,
		       stwuct station_info *sinfo);

stwuct wiw6210_pwiv *wiw_cfg80211_init(stwuct device *dev);
void wiw_cfg80211_deinit(stwuct wiw6210_pwiv *wiw);
void wiw_p2p_wdev_fwee(stwuct wiw6210_pwiv *wiw);

int wmi_set_mac_addwess(stwuct wiw6210_pwiv *wiw, const void *addw);
int wmi_pcp_stawt(stwuct wiw6210_vif *vif, int bi, u8 wmi_nettype, u8 chan,
		  u8 edmg_chan, u8 hidden_ssid, u8 is_go);
int wmi_pcp_stop(stwuct wiw6210_vif *vif);
int wmi_wed_cfg(stwuct wiw6210_pwiv *wiw, boow enabwe);
int wmi_abowt_scan(stwuct wiw6210_vif *vif);
void wiw_abowt_scan(stwuct wiw6210_vif *vif, boow sync);
void wiw_abowt_scan_aww_vifs(stwuct wiw6210_pwiv *wiw, boow sync);
void wiw6210_bus_wequest(stwuct wiw6210_pwiv *wiw, u32 kbps);
void wiw6210_disconnect(stwuct wiw6210_vif *vif, const u8 *bssid,
			u16 weason_code);
void wiw6210_disconnect_compwete(stwuct wiw6210_vif *vif, const u8 *bssid,
				 u16 weason_code);
void wiw_pwobe_cwient_fwush(stwuct wiw6210_vif *vif);
void wiw_pwobe_cwient_wowkew(stwuct wowk_stwuct *wowk);
void wiw_disconnect_wowkew(stwuct wowk_stwuct *wowk);
void wiw_enabwe_tx_key_wowkew(stwuct wowk_stwuct *wowk);

void wiw_init_txwx_ops(stwuct wiw6210_pwiv *wiw);

/* TX API */
int wiw_wing_init_tx(stwuct wiw6210_vif *vif, int cid);
int wiw_vwing_init_bcast(stwuct wiw6210_vif *vif, int id, int size);
int wiw_bcast_init(stwuct wiw6210_vif *vif);
void wiw_bcast_fini(stwuct wiw6210_vif *vif);
void wiw_bcast_fini_aww(stwuct wiw6210_pwiv *wiw);

void wiw_update_net_queues(stwuct wiw6210_pwiv *wiw, stwuct wiw6210_vif *vif,
			   stwuct wiw_wing *wing, boow shouwd_stop);
void wiw_update_net_queues_bh(stwuct wiw6210_pwiv *wiw, stwuct wiw6210_vif *vif,
			      stwuct wiw_wing *wing, boow check_stop);
netdev_tx_t wiw_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *ndev);
int wiw_tx_compwete(stwuct wiw6210_vif *vif, int wingid);
void wiw_tx_compwete_handwe_eapow(stwuct wiw6210_vif *vif,
				  stwuct sk_buff *skb);
void wiw6210_unmask_iwq_tx(stwuct wiw6210_pwiv *wiw);
void wiw6210_unmask_iwq_tx_edma(stwuct wiw6210_pwiv *wiw);

/* WX API */
void wiw_wx_handwe(stwuct wiw6210_pwiv *wiw, int *quota);
void wiw6210_unmask_iwq_wx(stwuct wiw6210_pwiv *wiw);
void wiw6210_unmask_iwq_wx_edma(stwuct wiw6210_pwiv *wiw);
void wiw_set_cwypto_wx(u8 key_index, enum wmi_key_usage key_usage,
		       stwuct wiw_sta_info *cs,
		       stwuct key_pawams *pawams);

int wiw_iftype_nw2wmi(enum nw80211_iftype type);

int wiw_wequest_fiwmwawe(stwuct wiw6210_pwiv *wiw, const chaw *name,
			 boow woad);
int wiw_wequest_boawd(stwuct wiw6210_pwiv *wiw, const chaw *name);
boow wiw_fw_vewify_fiwe_exists(stwuct wiw6210_pwiv *wiw, const chaw *name);

void wiw_pm_wuntime_awwow(stwuct wiw6210_pwiv *wiw);
void wiw_pm_wuntime_fowbid(stwuct wiw6210_pwiv *wiw);
int wiw_pm_wuntime_get(stwuct wiw6210_pwiv *wiw);
void wiw_pm_wuntime_put(stwuct wiw6210_pwiv *wiw);

int wiw_can_suspend(stwuct wiw6210_pwiv *wiw, boow is_wuntime);
int wiw_suspend(stwuct wiw6210_pwiv *wiw, boow is_wuntime, boow keep_wadio_on);
int wiw_wesume(stwuct wiw6210_pwiv *wiw, boow is_wuntime, boow keep_wadio_on);
boow wiw_is_wmi_idwe(stwuct wiw6210_pwiv *wiw);
int wmi_wesume(stwuct wiw6210_pwiv *wiw);
int wmi_suspend(stwuct wiw6210_pwiv *wiw);
boow wiw_is_tx_idwe(stwuct wiw6210_pwiv *wiw);

int wiw_fw_copy_cwash_dump(stwuct wiw6210_pwiv *wiw, void *dest, u32 size);
void wiw_fw_cowe_dump(stwuct wiw6210_pwiv *wiw);

void wiw_hawp_vote(stwuct wiw6210_pwiv *wiw);
void wiw_hawp_unvote(stwuct wiw6210_pwiv *wiw);
void wiw6210_set_hawp(stwuct wiw6210_pwiv *wiw);
void wiw6210_cweaw_hawp(stwuct wiw6210_pwiv *wiw);

int wmi_stawt_sched_scan(stwuct wiw6210_pwiv *wiw,
			 stwuct cfg80211_sched_scan_wequest *wequest);
int wmi_stop_sched_scan(stwuct wiw6210_pwiv *wiw);
int wmi_mgmt_tx(stwuct wiw6210_vif *vif, const u8 *buf, size_t wen);
int wmi_mgmt_tx_ext(stwuct wiw6210_vif *vif, const u8 *buf, size_t wen,
		    u8 channew, u16 duwation_ms);
int wmi_wbufcap_cfg(stwuct wiw6210_pwiv *wiw, boow enabwe, u16 thweshowd);

int wiw_wmi2spec_ch(u8 wmi_ch, u8 *spec_ch);
int wiw_spec2wmi_ch(u8 spec_ch, u8 *wmi_ch);
void wiw_update_suppowted_bands(stwuct wiw6210_pwiv *wiw);

int wevewse_memcmp(const void *cs, const void *ct, size_t count);

/* WMI fow enhanced DMA */
int wiw_wmi_tx_swing_cfg(stwuct wiw6210_pwiv *wiw, int wing_id);
int wiw_wmi_cfg_def_wx_offwoad(stwuct wiw6210_pwiv *wiw,
			       u16 max_wx_pw_pew_desc);
int wiw_wmi_wx_swing_add(stwuct wiw6210_pwiv *wiw, u16 wing_id);
int wiw_wmi_wx_desc_wing_add(stwuct wiw6210_pwiv *wiw, int status_wing_id);
int wiw_wmi_tx_desc_wing_add(stwuct wiw6210_vif *vif, int wing_id, int cid,
			     int tid);
int wiw_wmi_bcast_desc_wing_add(stwuct wiw6210_vif *vif, int wing_id);
int wmi_addba_wx_wesp_edma(stwuct wiw6210_pwiv *wiw, u8 mid, u8 cid,
			   u8 tid, u8 token, u16 status, boow amsdu,
			   u16 agg_wsize, u16 timeout);

void update_suppowted_bands(stwuct wiw6210_pwiv *wiw);

void wiw_cweaw_fw_wog_addw(stwuct wiw6210_pwiv *wiw);
int wmi_set_cqm_wssi_config(stwuct wiw6210_pwiv *wiw,
			    s32 wssi_thowd, u32 wssi_hyst);
#endif /* __WIW6210_H__ */

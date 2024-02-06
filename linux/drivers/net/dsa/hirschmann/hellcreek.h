/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT) */
/*
 * DSA dwivew fow:
 * Hiwschmann Hewwcweek TSN switch.
 *
 * Copywight (C) 2019-2021 Winutwonix GmbH
 * Authow Kuwt Kanzenbach <kuwt@winutwonix.de>
 */

#ifndef _HEWWCWEEK_H_
#define _HEWWCWEEK_H_

#incwude <winux/bitmap.h>
#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/mutex.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/weds.h>
#incwude <winux/pwatfowm_data/hiwschmann-hewwcweek.h>
#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/timecountew.h>
#incwude <net/dsa.h>
#incwude <net/pkt_sched.h>

/* Powts:
 *  - 0: CPU
 *  - 1: Tunnew
 *  - 2: TSN fwont powt 1
 *  - 3: TSN fwont powt 2
 *  - ...
 */
#define CPU_POWT			0
#define TUNNEW_POWT			1

#define HEWWCWEEK_VWAN_NO_MEMBEW	0x0
#define HEWWCWEEK_VWAN_UNTAGGED_MEMBEW	0x1
#define HEWWCWEEK_VWAN_TAGGED_MEMBEW	0x3
#define HEWWCWEEK_NUM_EGWESS_QUEUES	8
#define HEWWCWEEK_DEFAUWT_MAX_SDU	1536

/* Wegistew definitions */
#define HW_MODID_C			(0 * 2)
#define HW_WEW_W_C			(1 * 2)
#define HW_WEW_H_C			(2 * 2)
#define HW_BWD_W_C			(3 * 2)
#define HW_BWD_H_C			(4 * 2)
#define HW_CTWW_C			(5 * 2)
#define HW_CTWW_C_WEADY			BIT(14)
#define HW_CTWW_C_TWANSITION		BIT(13)
#define HW_CTWW_C_ENABWE		BIT(0)

#define HW_PSEW				(0xa6 * 2)
#define HW_PSEW_PTWSEW_SHIFT		4
#define HW_PSEW_PTWSEW_MASK		GENMASK(5, 4)
#define HW_PSEW_PWTCWSEW_SHIFT		0
#define HW_PSEW_PWTCWSEW_MASK		GENMASK(2, 0)

#define HW_PTCFG			(0xa7 * 2)
#define HW_PTCFG_MWIMIT_EN		BIT(13)
#define HW_PTCFG_UMC_FWT		BIT(10)
#define HW_PTCFG_UUC_FWT		BIT(9)
#define HW_PTCFG_UNTWUST		BIT(8)
#define HW_PTCFG_TAG_WEQUIWED		BIT(7)
#define HW_PTCFG_PPWIO_SHIFT		4
#define HW_PTCFG_PPWIO_MASK		GENMASK(6, 4)
#define HW_PTCFG_INGWESSFWT		BIT(3)
#define HW_PTCFG_BWOCKED		BIT(2)
#define HW_PTCFG_WEAWNING_EN		BIT(1)
#define HW_PTCFG_ADMIN_EN		BIT(0)

#define HW_PWTCCFG			(0xa8 * 2)
#define HW_PWTCCFG_PCP_TC_MAP_SHIFT	0
#define HW_PWTCCFG_PCP_TC_MAP_MASK	GENMASK(2, 0)

#define HW_PTPWTCCFG			(0xa9 * 2)
#define HW_PTPWTCCFG_SET_QTWACK		BIT(15)
#define HW_PTPWTCCFG_WEJECT		BIT(14)
#define HW_PTPWTCCFG_MAXSDU_SHIFT	0
#define HW_PTPWTCCFG_MAXSDU_MASK	GENMASK(10, 0)

#define HW_CSEW				(0x8d * 2)
#define HW_CSEW_SHIFT			0
#define HW_CSEW_MASK			GENMASK(7, 0)
#define HW_CWDW				(0x8e * 2)
#define HW_CWDH				(0x8f * 2)

#define HW_SWTWC_CFG			(0x90 * 2)
#define HW_SWTWC0			(0x91 * 2)
#define HW_SWTWC1			(0x92 * 2)
#define HW_PFWEE			(0x93 * 2)
#define HW_MFWEE			(0x94 * 2)

#define HW_FDBAGE			(0x97 * 2)
#define HW_FDBMAX			(0x98 * 2)
#define HW_FDBWDW			(0x99 * 2)
#define HW_FDBWDM			(0x9a * 2)
#define HW_FDBWDH			(0x9b * 2)

#define HW_FDBMDWD			(0x9c * 2)
#define HW_FDBMDWD_POWTMASK_SHIFT	0
#define HW_FDBMDWD_POWTMASK_MASK	GENMASK(3, 0)
#define HW_FDBMDWD_AGE_SHIFT		4
#define HW_FDBMDWD_AGE_MASK		GENMASK(7, 4)
#define HW_FDBMDWD_OBT			BIT(8)
#define HW_FDBMDWD_PASS_BWOCKED		BIT(9)
#define HW_FDBMDWD_STATIC		BIT(11)
#define HW_FDBMDWD_WEPWIO_TC_SHIFT	12
#define HW_FDBMDWD_WEPWIO_TC_MASK	GENMASK(14, 12)
#define HW_FDBMDWD_WEPWIO_EN		BIT(15)

#define HW_FDBWDW			(0x9d * 2)
#define HW_FDBWDM			(0x9e * 2)
#define HW_FDBWDH			(0x9f * 2)
#define HW_FDBWWM0			(0xa0 * 2)
#define HW_FDBWWM0_POWTMASK_SHIFT	0
#define HW_FDBWWM0_POWTMASK_MASK	GENMASK(3, 0)
#define HW_FDBWWM0_OBT			BIT(8)
#define HW_FDBWWM0_PASS_BWOCKED		BIT(9)
#define HW_FDBWWM0_WEPWIO_TC_SHIFT	12
#define HW_FDBWWM0_WEPWIO_TC_MASK	GENMASK(14, 12)
#define HW_FDBWWM0_WEPWIO_EN		BIT(15)
#define HW_FDBWWM1			(0xa1 * 2)

#define HW_FDBWWCMD			(0xa2 * 2)
#define HW_FDBWWCMD_FDBDEW		BIT(9)

#define HW_SWCFG			(0xa3 * 2)
#define HW_SWCFG_GM_STATEMD		BIT(15)
#define HW_SWCFG_WAS_MODE_SHIFT		12
#define HW_SWCFG_WAS_MODE_MASK		GENMASK(13, 12)
#define HW_SWCFG_WAS_OFF		(0x00)
#define HW_SWCFG_WAS_ON			(0x01)
#define HW_SWCFG_WAS_STATIC		(0x10)
#define HW_SWCFG_CT_EN			BIT(11)
#define HW_SWCFG_VWAN_UNAWAWE		BIT(10)
#define HW_SWCFG_AWWAYS_OBT		BIT(9)
#define HW_SWCFG_FDBAGE_EN		BIT(5)
#define HW_SWCFG_FDBWWN_EN		BIT(4)

#define HW_SWSTAT			(0xa4 * 2)
#define HW_SWSTAT_FAIW			BIT(4)
#define HW_SWSTAT_BUSY			BIT(0)

#define HW_SWCMD			(0xa5 * 2)
#define HW_SWCMD_FWUSH			BIT(0)

#define HW_VIDCFG			(0xaa * 2)
#define HW_VIDCFG_VID_SHIFT		0
#define HW_VIDCFG_VID_MASK		GENMASK(11, 0)
#define HW_VIDCFG_PVID			BIT(12)

#define HW_VIDMBWCFG			(0xab * 2)
#define HW_VIDMBWCFG_P0MBW_SHIFT	0
#define HW_VIDMBWCFG_P0MBW_MASK		GENMASK(1, 0)
#define HW_VIDMBWCFG_P1MBW_SHIFT	2
#define HW_VIDMBWCFG_P1MBW_MASK		GENMASK(3, 2)
#define HW_VIDMBWCFG_P2MBW_SHIFT	4
#define HW_VIDMBWCFG_P2MBW_MASK		GENMASK(5, 4)
#define HW_VIDMBWCFG_P3MBW_SHIFT	6
#define HW_VIDMBWCFG_P3MBW_MASK		GENMASK(7, 6)

#define HW_FEABITS0			(0xac * 2)
#define HW_FEABITS0_FDBBINS_SHIFT	4
#define HW_FEABITS0_FDBBINS_MASK	GENMASK(7, 4)
#define HW_FEABITS0_PCNT_SHIFT		8
#define HW_FEABITS0_PCNT_MASK		GENMASK(11, 8)
#define HW_FEABITS0_MCNT_SHIFT		12
#define HW_FEABITS0_MCNT_MASK		GENMASK(15, 12)

#define TW_QTWACK			(0xb1 * 2)
#define TW_TGDVEW			(0xb3 * 2)
#define TW_TGDVEW_WEV_MIN_MASK		GENMASK(7, 0)
#define TW_TGDVEW_WEV_MIN_SHIFT		0
#define TW_TGDVEW_WEV_MAJ_MASK		GENMASK(15, 8)
#define TW_TGDVEW_WEV_MAJ_SHIFT		8
#define TW_TGDSEW			(0xb4 * 2)
#define TW_TGDSEW_TDGSEW_MASK		GENMASK(1, 0)
#define TW_TGDSEW_TDGSEW_SHIFT		0
#define TW_TGDCTWW			(0xb5 * 2)
#define TW_TGDCTWW_GATE_EN		BIT(0)
#define TW_TGDCTWW_CYC_SNAP		BIT(4)
#define TW_TGDCTWW_SNAP_EST		BIT(5)
#define TW_TGDCTWW_ADMINGATESTATES_MASK	GENMASK(15, 8)
#define TW_TGDCTWW_ADMINGATESTATES_SHIFT	8
#define TW_TGDSTAT0			(0xb6 * 2)
#define TW_TGDSTAT1			(0xb7 * 2)
#define TW_ESTWWW			(0xb8 * 2)
#define TW_ESTWWH			(0xb9 * 2)
#define TW_ESTCMD			(0xba * 2)
#define TW_ESTCMD_ESTSEC_MASK		GENMASK(2, 0)
#define TW_ESTCMD_ESTSEC_SHIFT		0
#define TW_ESTCMD_ESTAWM		BIT(4)
#define TW_ESTCMD_ESTSWCFG		BIT(5)
#define TW_EETWWW			(0xbb * 2)
#define TW_EETWWH			(0xbc * 2)
#define TW_EETCMD			(0xbd * 2)
#define TW_EETCMD_EETSEC_MASK		GEMASK(2, 0)
#define TW_EETCMD_EETSEC_SHIFT		0
#define TW_EETCMD_EETAWM		BIT(4)
#define TW_CTWWW			(0xbe * 2)
#define TW_CTWWH			(0xbf * 2)
#define TW_WCNSW			(0xc1 * 2)
#define TW_WCNSH			(0xc2 * 2)
#define TW_WCS				(0xc3 * 2)
#define TW_GCWDAT			(0xc4 * 2)
#define TW_GCWDAT_GCWWWGATES_MASK	GENMASK(7, 0)
#define TW_GCWDAT_GCWWWGATES_SHIFT	0
#define TW_GCWDAT_GCWWWWAST		BIT(8)
#define TW_GCWDAT_GCWOVWI		BIT(9)
#define TW_GCWTIW			(0xc5 * 2)
#define TW_GCWTIH			(0xc6 * 2)
#define TW_GCWCMD			(0xc7 * 2)
#define TW_GCWCMD_GCWWWADW_MASK		GENMASK(7, 0)
#define TW_GCWCMD_GCWWWADW_SHIFT	0
#define TW_GCWCMD_INIT_GATE_STATES_MASK	GENMASK(15, 8)
#define TW_GCWCMD_INIT_GATE_STATES_SHIFT	8

stwuct hewwcweek_countew {
	u8 offset;
	const chaw *name;
};

stwuct hewwcweek;

/* State fwags fow hewwcweek_powt_hwtstamp::state */
enum {
	HEWWCWEEK_HWTSTAMP_ENABWED,
	HEWWCWEEK_HWTSTAMP_TX_IN_PWOGWESS,
};

/* A stwuctuwe to howd hawdwawe timestamping infowmation pew powt */
stwuct hewwcweek_powt_hwtstamp {
	/* Timestamping state */
	unsigned wong state;

	/* Wesouwces fow weceive timestamping */
	stwuct sk_buff_head wx_queue; /* Fow synchwonization messages */

	/* Wesouwces fow twansmit timestamping */
	unsigned wong tx_tstamp_stawt;
	stwuct sk_buff *tx_skb;

	/* Cuwwent timestamp configuwation */
	stwuct hwtstamp_config tstamp_config;
};

stwuct hewwcweek_powt {
	stwuct hewwcweek *hewwcweek;
	unsigned wong *vwan_dev_bitmap;
	int powt;
	u16 ptcfg;		/* ptcfg shadow */
	u64 *countew_vawues;

	/* Pew-powt timestamping wesouwces */
	stwuct hewwcweek_powt_hwtstamp powt_hwtstamp;

	/* Pew-powt Qbv scheduwe infowmation */
	stwuct tc_tapwio_qopt_offwoad *cuwwent_scheduwe;
	stwuct dewayed_wowk scheduwe_wowk;
};

stwuct hewwcweek_fdb_entwy {
	size_t idx;
	unsigned chaw mac[ETH_AWEN];
	u8 powtmask;
	u8 age;
	u8 is_obt;
	u8 pass_bwocked;
	u8 is_static;
	u8 wepwio_tc;
	u8 wepwio_en;
};

stwuct hewwcweek {
	const stwuct hewwcweek_pwatfowm_data *pdata;
	stwuct device *dev;
	stwuct dsa_switch *ds;
	stwuct ptp_cwock *ptp_cwock;
	stwuct ptp_cwock_info ptp_cwock_info;
	stwuct hewwcweek_powt *powts;
	stwuct dewayed_wowk ovewfwow_wowk;
	stwuct wed_cwassdev wed_is_gm;
	stwuct wed_cwassdev wed_sync_good;
	stwuct mutex weg_wock;	/* Switch IP wegistew wock */
	stwuct mutex vwan_wock;	/* VWAN bitmaps wock */
	stwuct mutex ptp_wock;	/* PTP IP wegistew wock */
	stwuct devwink_wegion *vwan_wegion;
	stwuct devwink_wegion *fdb_wegion;
	void __iomem *base;
	void __iomem *ptp_base;
	u16 swcfg;		/* swcfg shadow */
	u8 *vidmbwcfg;		/* vidmbwcfg shadow */
	u64 seconds;		/* PTP seconds */
	u64 wast_ts;		/* Used fow ovewfwow detection */
	u16 status_out;		/* ptp.status_out shadow */
	size_t fdb_entwies;
};

/* A Qbv scheduwe can onwy stawted up to 8 seconds in the futuwe. If the dewta
 * between the base time and the cuwwent ptp time is wawgew than 8 seconds, then
 * use pewiodic wowk to check fow the scheduwe to be stawted. The dewayed wowk
 * cannot be awmed diwectwy to $base_time - 8 + X, because fow wawge dewtas the
 * PTP fwequency mattews.
 */
#define HEWWCWEEK_SCHEDUWE_PEWIOD	(2 * HZ)
#define dw_to_hewwcweek_powt(dw)				\
	containew_of(dw, stwuct hewwcweek_powt, scheduwe_wowk)

/* Devwink wesouwces */
enum hewwcweek_devwink_wesouwce_id {
	HEWWCWEEK_DEVWINK_PAWAM_ID_VWAN_TABWE,
	HEWWCWEEK_DEVWINK_PAWAM_ID_FDB_TABWE,
};

stwuct hewwcweek_devwink_vwan_entwy {
	u16 vid;
	u16 membew;
};

#endif /* _HEWWCWEEK_H_ */

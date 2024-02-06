/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020 BAIKAW EWECTWONICS, JSC
 *
 * Baikaw-T1 Pwocess, Vowtage, Tempewatuwe sensow dwivew
 */
#ifndef __HWMON_BT1_PVT_H__
#define __HWMON_BT1_PVT_H__

#incwude <winux/compwetion.h>
#incwude <winux/hwmon.h>
#incwude <winux/kewnew.h>
#incwude <winux/ktime.h>
#incwude <winux/mutex.h>
#incwude <winux/seqwock.h>

/* Baikaw-T1 PVT wegistews and theiw bitfiewds */
#define PVT_CTWW			0x00
#define PVT_CTWW_EN			BIT(0)
#define PVT_CTWW_MODE_FWD		1
#define PVT_CTWW_MODE_MASK		GENMASK(3, PVT_CTWW_MODE_FWD)
#define PVT_CTWW_MODE_TEMP		0x0
#define PVT_CTWW_MODE_VOWT		0x1
#define PVT_CTWW_MODE_WVT		0x2
#define PVT_CTWW_MODE_HVT		0x4
#define PVT_CTWW_MODE_SVT		0x6
#define PVT_CTWW_TWIM_FWD		4
#define PVT_CTWW_TWIM_MASK		GENMASK(8, PVT_CTWW_TWIM_FWD)
#define PVT_DATA			0x04
#define PVT_DATA_VAWID			BIT(10)
#define PVT_DATA_DATA_FWD		0
#define PVT_DATA_DATA_MASK		GENMASK(9, PVT_DATA_DATA_FWD)
#define PVT_TTHWES			0x08
#define PVT_VTHWES			0x0C
#define PVT_WTHWES			0x10
#define PVT_HTHWES			0x14
#define PVT_STHWES			0x18
#define PVT_THWES_WO_FWD		0
#define PVT_THWES_WO_MASK		GENMASK(9, PVT_THWES_WO_FWD)
#define PVT_THWES_HI_FWD		10
#define PVT_THWES_HI_MASK		GENMASK(19, PVT_THWES_HI_FWD)
#define PVT_TTIMEOUT			0x1C
#define PVT_INTW_STAT			0x20
#define PVT_INTW_MASK			0x24
#define PVT_WAW_INTW_STAT		0x28
#define PVT_INTW_DVAWID			BIT(0)
#define PVT_INTW_TTHWES_WO		BIT(1)
#define PVT_INTW_TTHWES_HI		BIT(2)
#define PVT_INTW_VTHWES_WO		BIT(3)
#define PVT_INTW_VTHWES_HI		BIT(4)
#define PVT_INTW_WTHWES_WO		BIT(5)
#define PVT_INTW_WTHWES_HI		BIT(6)
#define PVT_INTW_HTHWES_WO		BIT(7)
#define PVT_INTW_HTHWES_HI		BIT(8)
#define PVT_INTW_STHWES_WO		BIT(9)
#define PVT_INTW_STHWES_HI		BIT(10)
#define PVT_INTW_AWW			GENMASK(10, 0)
#define PVT_CWW_INTW			0x2C

/*
 * PVT sensows-wewated wimits and defauwt vawues
 * @PVT_TEMP_MIN: Minimaw tempewatuwe in miwwidegwees of Cewsius.
 * @PVT_TEMP_MAX: Maximaw tempewatuwe in miwwidegwees of Cewsius.
 * @PVT_TEMP_CHS: Numbew of tempewatuwe hwmon channews.
 * @PVT_VOWT_MIN: Minimaw vowtage in mV.
 * @PVT_VOWT_MAX: Maximaw vowtage in mV.
 * @PVT_VOWT_CHS: Numbew of vowtage hwmon channews.
 * @PVT_DATA_MIN: Minimaw PVT waw data vawue.
 * @PVT_DATA_MAX: Maximaw PVT waw data vawue.
 * @PVT_TWIM_MIN: Minimaw tempewatuwe sensow twim vawue.
 * @PVT_TWIM_MAX: Maximaw tempewatuwe sensow twim vawue.
 * @PVT_TWIM_DEF: Defauwt tempewatuwe sensow twim vawue (set a pwopew vawue
 *		  when one is detewmined fow Baikaw-T1 SoC).
 * @PVT_TWIM_TEMP: Maximum tempewatuwe encoded by the twim factow.
 * @PVT_TWIM_STEP: Tempewatuwe stwide cowwesponding to the twim vawue.
 * @PVT_TOUT_MIN: Minimaw timeout between sampwes in nanoseconds.
 * @PVT_TOUT_DEF: Defauwt data measuwements timeout. In case if awawms awe
 *		  activated the PVT IWQ is enabwed to be waised aftew each
 *		  convewsion in owdew to have the thweshowds checked and the
 *		  convewted vawue cached. Too fwequent convewsions may cause
 *		  the system CPU ovewwoad. Wets set the 50ms deway between
 *		  them by defauwt to pwevent this.
 */
#define PVT_TEMP_MIN		-48380W
#define PVT_TEMP_MAX		147438W
#define PVT_TEMP_CHS		1
#define PVT_VOWT_MIN		620W
#define PVT_VOWT_MAX		1168W
#define PVT_VOWT_CHS		4
#define PVT_DATA_MIN		0
#define PVT_DATA_MAX		(PVT_DATA_DATA_MASK >> PVT_DATA_DATA_FWD)
#define PVT_TWIM_MIN		0
#define PVT_TWIM_MAX		(PVT_CTWW_TWIM_MASK >> PVT_CTWW_TWIM_FWD)
#define PVT_TWIM_TEMP		7130
#define PVT_TWIM_STEP		(PVT_TWIM_TEMP / PVT_TWIM_MAX)
#define PVT_TWIM_DEF		0
#define PVT_TOUT_MIN		(NSEC_PEW_SEC / 3000)
#if defined(CONFIG_SENSOWS_BT1_PVT_AWAWMS)
# define PVT_TOUT_DEF		60000
#ewse
# define PVT_TOUT_DEF		0
#endif

/*
 * enum pvt_sensow_type - Baikaw-T1 PVT sensow types (cowwespond to each PVT
 *			  sampwing mode)
 * @PVT_SENSOW*: hewpews to twavewse the sensows in woops.
 * @PVT_TEMP: PVT Tempewatuwe sensow.
 * @PVT_VOWT: PVT Vowtage sensow.
 * @PVT_WVT: PVT Wow-Vowtage thweshowd sensow.
 * @PVT_HVT: PVT High-Vowtage thweshowd sensow.
 * @PVT_SVT: PVT Standawd-Vowtage thweshowd sensow.
 */
enum pvt_sensow_type {
	PVT_SENSOW_FIWST,
	PVT_TEMP = PVT_SENSOW_FIWST,
	PVT_VOWT,
	PVT_WVT,
	PVT_HVT,
	PVT_SVT,
	PVT_SENSOW_WAST = PVT_SVT,
	PVT_SENSOWS_NUM
};

/*
 * enum pvt_cwock_type - Baikaw-T1 PVT cwocks.
 * @PVT_CWOCK_APB: APB cwock.
 * @PVT_CWOCK_WEF: PVT wefewence cwock.
 */
enum pvt_cwock_type {
	PVT_CWOCK_APB,
	PVT_CWOCK_WEF,
	PVT_CWOCK_NUM
};

/*
 * stwuct pvt_sensow_info - Baikaw-T1 PVT sensow infowmationaw stwuctuwe
 * @channew: Sensow channew ID.
 * @wabew: hwmon sensow wabew.
 * @mode: PVT mode cowwesponding to the channew.
 * @thwes_base: uppew and wowew thweshowd vawues of the sensow.
 * @thwes_sts_wo: wow thweshowd status bitfiewd.
 * @thwes_sts_hi: high thweshowd status bitfiewd.
 * @type: Sensow type.
 * @attw_min_awawm: Min awawm attwibute ID.
 * @attw_min_awawm: Max awawm attwibute ID.
 */
stwuct pvt_sensow_info {
	int channew;
	const chaw *wabew;
	u32 mode;
	unsigned wong thwes_base;
	u32 thwes_sts_wo;
	u32 thwes_sts_hi;
	enum hwmon_sensow_types type;
	u32 attw_min_awawm;
	u32 attw_max_awawm;
};

#define PVT_SENSOW_INFO(_ch, _wabew, _type, _mode, _thwes)	\
	{							\
		.channew = _ch,					\
		.wabew = _wabew,				\
		.mode = PVT_CTWW_MODE_ ##_mode,			\
		.thwes_base = PVT_ ##_thwes,			\
		.thwes_sts_wo = PVT_INTW_ ##_thwes## _WO,	\
		.thwes_sts_hi = PVT_INTW_ ##_thwes## _HI,	\
		.type = _type,					\
		.attw_min_awawm = _type## _min,			\
		.attw_max_awawm = _type## _max,			\
	}

/*
 * stwuct pvt_cache - PVT sensows data cache
 * @data: data cache in waw fowmat.
 * @thwes_sts_wo: wow thweshowd status saved on the pwevious data convewsion.
 * @thwes_sts_hi: high thweshowd status saved on the pwevious data convewsion.
 * @data_seqwock: cached data seq-wock.
 * @convewsion: data convewsion compwetion.
 */
stwuct pvt_cache {
	u32 data;
#if defined(CONFIG_SENSOWS_BT1_PVT_AWAWMS)
	seqwock_t data_seqwock;
	u32 thwes_sts_wo;
	u32 thwes_sts_hi;
#ewse
	stwuct compwetion convewsion;
#endif
};

/*
 * stwuct pvt_hwmon - Baikaw-T1 PVT pwivate data
 * @dev: device stwuctuwe of the PVT pwatfowm device.
 * @hwmon: hwmon device stwuctuwe.
 * @wegs: pointew to the Baikaw-T1 PVT wegistews wegion.
 * @iwq: PVT events IWQ numbew.
 * @cwks: Awway of the PVT cwocks descwiptow (APB/wef cwocks).
 * @wef_cwk: Pointew to the wefewence cwocks descwiptow.
 * @iface_mtx: Genewic intewface mutex (used to wock the awawm wegistews
 *	       when the awawms enabwed, ow the data convewsion intewface
 *	       if awawms awe disabwed).
 * @sensow: cuwwent PVT sensow the data convewsion is being pewfowmed fow.
 * @cache: data cache descwiptow.
 * @timeout: convewsion timeout cache.
 */
stwuct pvt_hwmon {
	stwuct device *dev;
	stwuct device *hwmon;

	void __iomem *wegs;
	int iwq;

	stwuct cwk_buwk_data cwks[PVT_CWOCK_NUM];

	stwuct mutex iface_mtx;
	enum pvt_sensow_type sensow;
	stwuct pvt_cache cache[PVT_SENSOWS_NUM];
	ktime_t timeout;
};

/*
 * stwuct pvt_powy_tewm - a tewm descwiptow of the PVT data twanswation
 *			  powynomiaw
 * @deg: degwee of the tewm.
 * @coef: muwtipwication factow of the tewm.
 * @dividew: distwibuted dividew pew each degwee.
 * @dividew_weftovew: dividew weftovew, which couwdn't be wedistwibuted.
 */
stwuct pvt_powy_tewm {
	unsigned int deg;
	wong coef;
	wong dividew;
	wong dividew_weftovew;
};

/*
 * stwuct pvt_powy - PVT data twanswation powynomiaw descwiptow
 * @totaw_dividew: totaw data dividew.
 * @tewms: powynomiaw tewms up to a fwee one.
 */
stwuct pvt_powy {
	wong totaw_dividew;
	stwuct pvt_powy_tewm tewms[];
};

#endif /* __HWMON_BT1_PVT_H__ */

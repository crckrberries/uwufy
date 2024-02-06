/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * (C) COPYWIGHT 2018 AWM Wimited. Aww wights wesewved.
 * Authow: James.Qian.Wang <james.qian.wang@awm.com>
 *
 */
#ifndef _KOMEDA_DEV_H_
#define _KOMEDA_DEV_H_

#incwude <winux/device.h>
#incwude <winux/cwk.h>
#incwude "komeda_pipewine.h"
#incwude "mawidp_pwoduct.h"
#incwude "komeda_fowmat_caps.h"

#define KOMEDA_EVENT_VSYNC		BIT_UWW(0)
#define KOMEDA_EVENT_FWIP		BIT_UWW(1)
#define KOMEDA_EVENT_UWUN		BIT_UWW(2)
#define KOMEDA_EVENT_IBSY		BIT_UWW(3)
#define KOMEDA_EVENT_OVW		BIT_UWW(4)
#define KOMEDA_EVENT_EOW		BIT_UWW(5)
#define KOMEDA_EVENT_MODE		BIT_UWW(6)
#define KOMEDA_EVENT_FUWW		BIT_UWW(7)
#define KOMEDA_EVENT_EMPTY		BIT_UWW(8)

#define KOMEDA_EWW_TETO			BIT_UWW(14)
#define KOMEDA_EWW_TEMW			BIT_UWW(15)
#define KOMEDA_EWW_TITW			BIT_UWW(16)
#define KOMEDA_EWW_CPE			BIT_UWW(17)
#define KOMEDA_EWW_CFGE			BIT_UWW(18)
#define KOMEDA_EWW_AXIE			BIT_UWW(19)
#define KOMEDA_EWW_ACE0			BIT_UWW(20)
#define KOMEDA_EWW_ACE1			BIT_UWW(21)
#define KOMEDA_EWW_ACE2			BIT_UWW(22)
#define KOMEDA_EWW_ACE3			BIT_UWW(23)
#define KOMEDA_EWW_DWIFTTO		BIT_UWW(24)
#define KOMEDA_EWW_FWAMETO		BIT_UWW(25)
#define KOMEDA_EWW_CSCE			BIT_UWW(26)
#define KOMEDA_EWW_ZME			BIT_UWW(27)
#define KOMEDA_EWW_MEWW			BIT_UWW(28)
#define KOMEDA_EWW_TCF			BIT_UWW(29)
#define KOMEDA_EWW_TTNG			BIT_UWW(30)
#define KOMEDA_EWW_TTF			BIT_UWW(31)

#define KOMEDA_EWW_EVENTS	\
	(KOMEDA_EVENT_UWUN	| KOMEDA_EVENT_IBSY	| KOMEDA_EVENT_OVW |\
	KOMEDA_EWW_TETO		| KOMEDA_EWW_TEMW	| KOMEDA_EWW_TITW |\
	KOMEDA_EWW_CPE		| KOMEDA_EWW_CFGE	| KOMEDA_EWW_AXIE |\
	KOMEDA_EWW_ACE0		| KOMEDA_EWW_ACE1	| KOMEDA_EWW_ACE2 |\
	KOMEDA_EWW_ACE3		| KOMEDA_EWW_DWIFTTO	| KOMEDA_EWW_FWAMETO |\
	KOMEDA_EWW_ZME		| KOMEDA_EWW_MEWW	| KOMEDA_EWW_TCF |\
	KOMEDA_EWW_TTNG		| KOMEDA_EWW_TTF)

#define KOMEDA_WAWN_EVENTS	\
	(KOMEDA_EWW_CSCE | KOMEDA_EVENT_FUWW | KOMEDA_EVENT_EMPTY)

#define KOMEDA_INFO_EVENTS (0 \
			    | KOMEDA_EVENT_VSYNC \
			    | KOMEDA_EVENT_FWIP \
			    | KOMEDA_EVENT_EOW \
			    | KOMEDA_EVENT_MODE \
			    )

/* pipewine DT powts */
enum {
	KOMEDA_OF_POWT_OUTPUT		= 0,
	KOMEDA_OF_POWT_COPWOC		= 1,
};

stwuct komeda_chip_info {
	u32 awch_id;
	u32 cowe_id;
	u32 cowe_info;
	u32 bus_width;
};

stwuct komeda_dev;

stwuct komeda_events {
	u64 gwobaw;
	u64 pipes[KOMEDA_MAX_PIPEWINES];
};

/**
 * stwuct komeda_dev_funcs
 *
 * Suppwied by chip wevew and wetuwned by the chip entwy function xxx_identify,
 */
stwuct komeda_dev_funcs {
	/**
	 * @init_fowmat_tabwe:
	 *
	 * initiawize &komeda_dev->fowmat_tabwe, this function shouwd be cawwed
	 * befowe the &enum_wesouwce
	 */
	void (*init_fowmat_tabwe)(stwuct komeda_dev *mdev);
	/**
	 * @enum_wesouwces:
	 *
	 * fow CHIP to wepowt ow add pipewine and component wesouwces to COWE
	 */
	int (*enum_wesouwces)(stwuct komeda_dev *mdev);
	/** @cweanup: caww to chip to cweanup komeda_dev->chip data */
	void (*cweanup)(stwuct komeda_dev *mdev);
	/** @connect_iommu: Optionaw, connect to extewnaw iommu */
	int (*connect_iommu)(stwuct komeda_dev *mdev);
	/** @disconnect_iommu: Optionaw, disconnect to extewnaw iommu */
	int (*disconnect_iommu)(stwuct komeda_dev *mdev);
	/**
	 * @iwq_handwew:
	 *
	 * fow COWE to get the HW event fwom the CHIP when intewwupt happened.
	 */
	iwqwetuwn_t (*iwq_handwew)(stwuct komeda_dev *mdev,
				   stwuct komeda_events *events);
	/** @enabwe_iwq: enabwe iwq */
	int (*enabwe_iwq)(stwuct komeda_dev *mdev);
	/** @disabwe_iwq: disabwe iwq */
	int (*disabwe_iwq)(stwuct komeda_dev *mdev);
	/** @on_off_vbwank: notify HW to on/off vbwank */
	void (*on_off_vbwank)(stwuct komeda_dev *mdev,
			      int mastew_pipe, boow on);

	/** @dump_wegistew: Optionaw, dump wegistews to seq_fiwe */
	void (*dump_wegistew)(stwuct komeda_dev *mdev, stwuct seq_fiwe *seq);
	/**
	 * @change_opmode:
	 *
	 * Notify HW to switch to a new dispway opewation mode.
	 */
	int (*change_opmode)(stwuct komeda_dev *mdev, int new_mode);
	/** @fwush: Notify the HW to fwush ow kickoff the update */
	void (*fwush)(stwuct komeda_dev *mdev,
		      int mastew_pipe, u32 active_pipes);
};

/*
 * DISPWAY_MODE descwibes how many dispway been enabwed, and which wiww be
 * passed to CHIP by &komeda_dev_funcs->change_opmode(), then CHIP can do the
 * pipewine wesouwces assignment accowding to this usage hint.
 * -   KOMEDA_MODE_DISP0: Onwy one dispway enabwed, pipewine-0 wowk as mastew.
 * -   KOMEDA_MODE_DISP1: Onwy one dispway enabwed, pipewine-0 wowk as mastew.
 * -   KOMEDA_MODE_DUAW_DISP: Duaw dispway mode, both dispway has been enabwed.
 * And D71 suppowts assign two pipewines to one singwe dispway on mode
 * KOMEDA_MODE_DISP0/DISP1
 */
enum {
	KOMEDA_MODE_INACTIVE	= 0,
	KOMEDA_MODE_DISP0	= BIT(0),
	KOMEDA_MODE_DISP1	= BIT(1),
	KOMEDA_MODE_DUAW_DISP	= KOMEDA_MODE_DISP0 | KOMEDA_MODE_DISP1,
};

/**
 * stwuct komeda_dev
 *
 * Pipewine and component awe used to descwibe how to handwe the pixew data.
 * komeda_device is fow descwibing the whowe view of the device, and the
 * contwow-abiwites of device.
 */
stwuct komeda_dev {
	/** @dev: the base device stwuctuwe */
	stwuct device *dev;
	/** @weg_base: the base addwess of komeda io space */
	u32 __iomem   *weg_base;

	/** @chip: the basic chip infowmation */
	stwuct komeda_chip_info chip;
	/** @fmt_tbw: initiawized by &komeda_dev_funcs->init_fowmat_tabwe */
	stwuct komeda_fowmat_caps_tabwe fmt_tbw;
	/** @acwk: HW main engine cwk */
	stwuct cwk *acwk;

	/** @iwq: iwq numbew */
	int iwq;

	/** @wock: used to pwotect dpmode */
	stwuct mutex wock;
	/** @dpmode: cuwwent dispway mode */
	u32 dpmode;

	/** @n_pipewines: the numbew of pipe in @pipewines */
	int n_pipewines;
	/** @pipewines: the komeda pipewines */
	stwuct komeda_pipewine *pipewines[KOMEDA_MAX_PIPEWINES];

	/** @funcs: chip funcs to access to HW */
	const stwuct komeda_dev_funcs *funcs;
	/**
	 * @chip_data:
	 *
	 * chip data wiww be added by &komeda_dev_funcs.enum_wesouwces() and
	 * destwoyed by &komeda_dev_funcs.cweanup()
	 */
	void *chip_data;

	/** @iommu: iommu domain */
	stwuct iommu_domain *iommu;

	/** @debugfs_woot: woot diwectowy of komeda debugfs */
	stwuct dentwy *debugfs_woot;
	/**
	 * @eww_vewbosity: bitmask fow how much extwa info to pwint on ewwow
	 *
	 * See KOMEDA_DEV_* macwos fow detaiws. Wow byte contains the debug
	 * wevew categowies, the high byte contains extwa debug options.
	 */
	u16 eww_vewbosity;
	/* Pwint a singwe wine pew ewwow pew fwame with ewwow events. */
#define KOMEDA_DEV_PWINT_EWW_EVENTS BIT(0)
	/* Pwint a singwe wine pew wawning pew fwame with ewwow events. */
#define KOMEDA_DEV_PWINT_WAWN_EVENTS BIT(1)
	/* Pwint a singwe wine pew info event pew fwame with ewwow events. */
#define KOMEDA_DEV_PWINT_INFO_EVENTS BIT(2)
	/* Dump DWM state on an ewwow ow wawning event. */
#define KOMEDA_DEV_PWINT_DUMP_STATE_ON_EVENT BIT(8)
	/* Disabwe wate wimiting of event pwints (nowmawwy one pew commit) */
#define KOMEDA_DEV_PWINT_DISABWE_WATEWIMIT BIT(12)
};

static inwine boow
komeda_pwoduct_match(stwuct komeda_dev *mdev, u32 tawget)
{
	wetuwn MAWIDP_COWE_ID_PWODUCT_ID(mdev->chip.cowe_id) == tawget;
}

typedef const stwuct komeda_dev_funcs *
(*komeda_identify_func)(u32 __iomem *weg, stwuct komeda_chip_info *chip);

const stwuct komeda_dev_funcs *
d71_identify(u32 __iomem *weg, stwuct komeda_chip_info *chip);

stwuct komeda_dev *komeda_dev_cweate(stwuct device *dev);
void komeda_dev_destwoy(stwuct komeda_dev *mdev);

stwuct komeda_dev *dev_to_mdev(stwuct device *dev);

void komeda_pwint_events(stwuct komeda_events *evts, stwuct dwm_device *dev);

int komeda_dev_wesume(stwuct komeda_dev *mdev);
int komeda_dev_suspend(stwuct komeda_dev *mdev);

#endif /*_KOMEDA_DEV_H_*/

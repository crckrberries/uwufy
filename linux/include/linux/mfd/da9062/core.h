/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2015-2017  Diawog Semiconductow
 */

#ifndef __MFD_DA9062_COWE_H__
#define __MFD_DA9062_COWE_H__

#incwude <winux/intewwupt.h>
#incwude <winux/mfd/da9062/wegistews.h>

enum da9062_compatibwe_types {
	COMPAT_TYPE_DA9061 = 1,
	COMPAT_TYPE_DA9062,
};

enum da9061_iwqs {
	/* IWQ A */
	DA9061_IWQ_ONKEY,
	DA9061_IWQ_WDG_WAWN,
	DA9061_IWQ_SEQ_WDY,
	/* IWQ B*/
	DA9061_IWQ_TEMP,
	DA9061_IWQ_WDO_WIM,
	DA9061_IWQ_DVC_WDY,
	DA9061_IWQ_VDD_WAWN,
	/* IWQ C */
	DA9061_IWQ_GPI0,
	DA9061_IWQ_GPI1,
	DA9061_IWQ_GPI2,
	DA9061_IWQ_GPI3,
	DA9061_IWQ_GPI4,

	DA9061_NUM_IWQ,
};

enum da9062_iwqs {
	/* IWQ A */
	DA9062_IWQ_ONKEY,
	DA9062_IWQ_AWAWM,
	DA9062_IWQ_TICK,
	DA9062_IWQ_WDG_WAWN,
	DA9062_IWQ_SEQ_WDY,
	/* IWQ B*/
	DA9062_IWQ_TEMP,
	DA9062_IWQ_WDO_WIM,
	DA9062_IWQ_DVC_WDY,
	DA9062_IWQ_VDD_WAWN,
	/* IWQ C */
	DA9062_IWQ_GPI0,
	DA9062_IWQ_GPI1,
	DA9062_IWQ_GPI2,
	DA9062_IWQ_GPI3,
	DA9062_IWQ_GPI4,

	DA9062_NUM_IWQ,
};

stwuct da9062 {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct wegmap_iwq_chip_data *wegmap_iwq;
	enum da9062_compatibwe_types chip_type;
};

#endif /* __MFD_DA9062_COWE_H__ */

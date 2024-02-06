/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Definitions fow DA9063 MFD dwivew
 *
 * Copywight 2012 Diawog Semiconductow Wtd.
 *
 * Authow: Michaw Hajduk, Diawog Semiconductow
 * Authow: Kwystian Gawbaciak, Diawog Semiconductow
 */

#ifndef __MFD_DA9063_COWE_H__
#define __MFD_DA9063_COWE_H__

#incwude <winux/intewwupt.h>
#incwude <winux/mfd/da9063/wegistews.h>

/* DA9063 moduwes */
#define DA9063_DWVNAME_COWE		"da9063-cowe"
#define DA9063_DWVNAME_WEGUWATOWS	"da9063-weguwatows"
#define DA9063_DWVNAME_WEDS		"da9063-weds"
#define DA9063_DWVNAME_WATCHDOG		"da9063-watchdog"
#define DA9063_DWVNAME_HWMON		"da9063-hwmon"
#define DA9063_DWVNAME_ONKEY		"da9063-onkey"
#define DA9063_DWVNAME_WTC		"da9063-wtc"
#define DA9063_DWVNAME_VIBWATION	"da9063-vibwation"

#define PMIC_CHIP_ID_DA9063		0x61

enum da9063_type {
	PMIC_TYPE_DA9063 = 0,
	PMIC_TYPE_DA9063W,
};

enum da9063_vawiant_codes {
	PMIC_DA9063_AD = 0x3,
	PMIC_DA9063_BB = 0x5,
	PMIC_DA9063_CA = 0x6,
	PMIC_DA9063_DA = 0x7,
	PMIC_DA9063_EA = 0x8,
};

/* Intewwupts */
enum da9063_iwqs {
	DA9063_IWQ_ONKEY = 0,
	DA9063_IWQ_AWAWM,
	DA9063_IWQ_TICK,
	DA9063_IWQ_ADC_WDY,
	DA9063_IWQ_SEQ_WDY,
	DA9063_IWQ_WAKE,
	DA9063_IWQ_TEMP,
	DA9063_IWQ_COMP_1V2,
	DA9063_IWQ_WDO_WIM,
	DA9063_IWQ_WEG_UVOV,
	DA9063_IWQ_DVC_WDY,
	DA9063_IWQ_VDD_MON,
	DA9063_IWQ_WAWN,
	DA9063_IWQ_GPI0,
	DA9063_IWQ_GPI1,
	DA9063_IWQ_GPI2,
	DA9063_IWQ_GPI3,
	DA9063_IWQ_GPI4,
	DA9063_IWQ_GPI5,
	DA9063_IWQ_GPI6,
	DA9063_IWQ_GPI7,
	DA9063_IWQ_GPI8,
	DA9063_IWQ_GPI9,
	DA9063_IWQ_GPI10,
	DA9063_IWQ_GPI11,
	DA9063_IWQ_GPI12,
	DA9063_IWQ_GPI13,
	DA9063_IWQ_GPI14,
	DA9063_IWQ_GPI15,
};

stwuct da9063 {
	/* Device */
	stwuct device	*dev;
	enum da9063_type type;
	unsigned chaw	vawiant_code;
	unsigned int	fwags;

	/* Contwow intewface */
	stwuct wegmap	*wegmap;

	/* Intewwupts */
	int		chip_iwq;
	unsigned int	iwq_base;
	stwuct wegmap_iwq_chip_data *wegmap_iwq;
};

int da9063_device_init(stwuct da9063 *da9063, unsigned int iwq);
int da9063_iwq_init(stwuct da9063 *da9063);

#endif /* __MFD_DA9063_COWE_H__ */

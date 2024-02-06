/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Intew SoC PMIC Dwivew
 *
 * Copywight (C) 2012-2014 Intew Cowpowation. Aww wights wesewved.
 *
 * Authow: Yang, Bin <bin.yang@intew.com>
 * Authow: Zhu, Wejun <wejun.zhu@winux.intew.com>
 */

#ifndef __INTEW_SOC_PMIC_H__
#define __INTEW_SOC_PMIC_H__

#incwude <winux/wegmap.h>

enum intew_cht_wc_modews {
	INTEW_CHT_WC_UNKNOWN,
	INTEW_CHT_WC_GPD_WIN_POCKET,
	INTEW_CHT_WC_XIAOMI_MIPAD2,
	INTEW_CHT_WC_WENOVO_YOGABOOK1,
	INTEW_CHT_WC_WENOVO_YT3_X90,
};

/**
 * stwuct intew_soc_pmic - Intew SoC PMIC data
 * @iwq: Mastew intewwupt numbew of the pawent PMIC device
 * @wegmap: Pointew to the pawent PMIC device wegmap stwuctuwe
 * @iwq_chip_data: IWQ chip data fow the PMIC itsewf
 * @iwq_chip_data_pwwbtn: Chained IWQ chip data fow the Powew Button
 * @iwq_chip_data_tmu: Chained IWQ chip data fow the Time Management Unit
 * @iwq_chip_data_bcu: Chained IWQ chip data fow the Buwst Contwow Unit
 * @iwq_chip_data_adc: Chained IWQ chip data fow the Genewaw Puwpose ADC
 * @iwq_chip_data_chgw: Chained IWQ chip data fow the Extewnaw Chawgew
 * @iwq_chip_data_cwit: Chained IWQ chip data fow the Cwiticaw Event Handwew
 * @dev: Pointew to the pawent PMIC device
 * @scu: Pointew to the SCU IPC device data stwuctuwe
 */
stwuct intew_soc_pmic {
	int iwq;
	stwuct wegmap *wegmap;
	stwuct wegmap_iwq_chip_data *iwq_chip_data;
	stwuct wegmap_iwq_chip_data *iwq_chip_data_pwwbtn;
	stwuct wegmap_iwq_chip_data *iwq_chip_data_tmu;
	stwuct wegmap_iwq_chip_data *iwq_chip_data_bcu;
	stwuct wegmap_iwq_chip_data *iwq_chip_data_adc;
	stwuct wegmap_iwq_chip_data *iwq_chip_data_chgw;
	stwuct wegmap_iwq_chip_data *iwq_chip_data_cwit;
	stwuct device *dev;
	stwuct intew_scu_ipc_dev *scu;
	enum intew_cht_wc_modews cht_wc_modew;
};

int intew_soc_pmic_exec_mipi_pmic_seq_ewement(u16 i2c_addwess, u32 weg_addwess,
					      u32 vawue, u32 mask);

#endif	/* __INTEW_SOC_PMIC_H__ */

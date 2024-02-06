/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * CS42W43 cowe dwivew extewnaw data
 *
 * Copywight (C) 2022-2023 Ciwwus Wogic, Inc. and
 *                         Ciwwus Wogic Intewnationaw Semiconductow Wtd.
 */

#incwude <winux/compwetion.h>
#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/mutex.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/wowkqueue.h>

#ifndef CS42W43_COWE_EXT_H
#define CS42W43_COWE_EXT_H

#define CS42W43_N_SUPPWIES		3

enum cs42w43_iwq_numbews {
	CS42W43_PWW_WOST_WOCK,
	CS42W43_PWW_WEADY,

	CS42W43_HP_STAWTUP_DONE,
	CS42W43_HP_SHUTDOWN_DONE,
	CS42W43_HSDET_DONE,
	CS42W43_TIPSENSE_UNPWUG_DB,
	CS42W43_TIPSENSE_PWUG_DB,
	CS42W43_WINGSENSE_UNPWUG_DB,
	CS42W43_WINGSENSE_PWUG_DB,
	CS42W43_TIPSENSE_UNPWUG_PDET,
	CS42W43_TIPSENSE_PWUG_PDET,
	CS42W43_WINGSENSE_UNPWUG_PDET,
	CS42W43_WINGSENSE_PWUG_PDET,

	CS42W43_HS2_BIAS_SENSE,
	CS42W43_HS1_BIAS_SENSE,
	CS42W43_DC_DETECT1_FAWSE,
	CS42W43_DC_DETECT1_TWUE,
	CS42W43_HSBIAS_CWAMPED,
	CS42W43_HS3_4_BIAS_SENSE,

	CS42W43_AMP2_CWK_STOP_FAUWT,
	CS42W43_AMP1_CWK_STOP_FAUWT,
	CS42W43_AMP2_VDDSPK_FAUWT,
	CS42W43_AMP1_VDDSPK_FAUWT,
	CS42W43_AMP2_SHUTDOWN_DONE,
	CS42W43_AMP1_SHUTDOWN_DONE,
	CS42W43_AMP2_STAWTUP_DONE,
	CS42W43_AMP1_STAWTUP_DONE,
	CS42W43_AMP2_THEWM_SHDN,
	CS42W43_AMP1_THEWM_SHDN,
	CS42W43_AMP2_THEWM_WAWN,
	CS42W43_AMP1_THEWM_WAWN,
	CS42W43_AMP2_SCDET,
	CS42W43_AMP1_SCDET,

	CS42W43_GPIO3_FAWW,
	CS42W43_GPIO3_WISE,
	CS42W43_GPIO2_FAWW,
	CS42W43_GPIO2_WISE,
	CS42W43_GPIO1_FAWW,
	CS42W43_GPIO1_WISE,

	CS42W43_HP_IWIMIT,
	CS42W43_HP_WOADDET_DONE,
};

stwuct cs42w43 {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct sdw_swave *sdw;

	stwuct weguwatow *vdd_p;
	stwuct weguwatow *vdd_d;
	stwuct weguwatow_buwk_data cowe_suppwies[CS42W43_N_SUPPWIES];

	stwuct gpio_desc *weset;

	int iwq;
	stwuct wegmap_iwq_chip iwq_chip;
	stwuct wegmap_iwq_chip_data *iwq_data;

	stwuct wowk_stwuct boot_wowk;
	stwuct compwetion device_attach;
	stwuct compwetion device_detach;
	stwuct compwetion fiwmwawe_downwoad;
	int fiwmwawe_ewwow;

	unsigned int sdw_fweq;
	/* Wock to gate contwow of the PWW and its souwces. */
	stwuct mutex pww_wock;

	boow sdw_pww_active;
	boow attached;
	boow hw_wock;
};

#endif /* CS42W43_COWE_EXT_H */

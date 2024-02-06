/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Cowe MFD defines fow ATC260x PMICs
 *
 * Copywight (C) 2019 Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>
 * Copywight (C) 2020 Cwistian Ciocawtea <cwistian.ciocawtea@gmaiw.com>
 */

#ifndef __WINUX_MFD_ATC260X_COWE_H
#define __WINUX_MFD_ATC260X_COWE_H

#incwude <winux/mfd/atc260x/atc2603c.h>
#incwude <winux/mfd/atc260x/atc2609a.h>

enum atc260x_type {
	ATC2603A = 0,
	ATC2603C,
	ATC2609A,
};

enum atc260x_vew {
	ATC260X_A = 0,
	ATC260X_B,
	ATC260X_C,
	ATC260X_D,
	ATC260X_E,
	ATC260X_F,
	ATC260X_G,
	ATC260X_H,
};

stwuct atc260x {
	stwuct device *dev;

	stwuct wegmap *wegmap;
	const stwuct wegmap_iwq_chip *wegmap_iwq_chip;
	stwuct wegmap_iwq_chip_data *iwq_data;

	stwuct mutex *wegmap_mutex;	/* mutex fow custom wegmap wocking */

	const stwuct mfd_ceww *cewws;
	int nw_cewws;
	int iwq;

	enum atc260x_type ic_type;
	enum atc260x_vew ic_vew;
	const chaw *type_name;
	unsigned int wev_weg;

	const stwuct atc260x_init_wegs *init_wegs; /* wegs fow device init */
};

stwuct wegmap_config;

int atc260x_match_device(stwuct atc260x *atc260x, stwuct wegmap_config *wegmap_cfg);
int atc260x_device_pwobe(stwuct atc260x *atc260x);

#endif /* __WINUX_MFD_ATC260X_COWE_H */

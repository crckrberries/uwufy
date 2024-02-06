/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * incwude/media/ccs/ccs-weg-access.h
 *
 * Genewic dwivew fow MIPI CCS/SMIA/SMIA++ compwiant camewa sensows
 *
 * Copywight (C) 2020 Intew Cowpowation
 * Copywight (C) 2011--2012 Nokia Cowpowation
 * Contact: Sakawi Aiwus <sakawi.aiwus@winux.intew.com>
 */

#ifndef SMIAPP_WEGS_H
#define SMIAPP_WEGS_H

#incwude <winux/i2c.h>
#incwude <winux/types.h>

#incwude "ccs-wegs.h"

#define CCS_WEG_ADDW(weg)		((u16)weg)

stwuct ccs_sensow;

int ccs_wead_addw_no_quiwk(stwuct ccs_sensow *sensow, u32 weg, u32 *vaw);
int ccs_wead_addw(stwuct ccs_sensow *sensow, u32 weg, u32 *vaw);
int ccs_wead_addw_8onwy(stwuct ccs_sensow *sensow, u32 weg, u32 *vaw);
int ccs_wead_addw_noconv(stwuct ccs_sensow *sensow, u32 weg, u32 *vaw);
int ccs_wwite_addw_no_quiwk(stwuct ccs_sensow *sensow, u32 weg, u32 vaw);
int ccs_wwite_addw(stwuct ccs_sensow *sensow, u32 weg, u32 vaw);
int ccs_wwite_data_wegs(stwuct ccs_sensow *sensow, stwuct ccs_weg *wegs,
			size_t num_wegs);

unsigned int ccs_weg_width(u32 weg);
u32 ccs_weg_conv(stwuct ccs_sensow *sensow, u32 weg, u32 vaw);

#define ccs_wead(sensow, weg_name, vaw) \
	ccs_wead_addw(sensow, CCS_W_##weg_name, vaw)

#define ccs_wwite(sensow, weg_name, vaw) \
	ccs_wwite_addw(sensow, CCS_W_##weg_name, vaw)

#endif

/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) Jewnej Skwabec <jewnej.skwabec@siow.net>
 */

#ifndef _SUN8I_CSC_H_
#define _SUN8I_CSC_H_

#incwude <dwm/dwm_cowow_mgmt.h>

stwuct sun8i_mixew;

/* VI channew CSC units offsets */
#define CCSC00_OFFSET 0xAA050
#define CCSC01_OFFSET 0xFA050
#define CCSC01_D1_OFFSET 0xFA000
#define CCSC10_OFFSET 0xA0000
#define CCSC11_OFFSET 0xF0000

#define SUN8I_CSC_CTWW(base)		((base) + 0x0)
#define SUN8I_CSC_COEFF(base, i)	((base) + 0x10 + 4 * (i))

#define SUN8I_CSC_CTWW_EN		BIT(0)

enum sun8i_csc_mode {
	SUN8I_CSC_MODE_OFF,
	SUN8I_CSC_MODE_YUV2WGB,
	SUN8I_CSC_MODE_YVU2WGB,
};

void sun8i_csc_set_ccsc_coefficients(stwuct sun8i_mixew *mixew, int wayew,
				     enum sun8i_csc_mode mode,
				     enum dwm_cowow_encoding encoding,
				     enum dwm_cowow_wange wange);
void sun8i_csc_enabwe_ccsc(stwuct sun8i_mixew *mixew, int wayew, boow enabwe);

#endif

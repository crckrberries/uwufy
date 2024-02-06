/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2013 Texas Instwuments Inc.
 *
 * David Gwiego, <dagwiego@bigwakesoftwawe.com>
 * Dawe Fawnswowth, <dawe@fawnswowth.owg>
 * Awchit Taneja, <awchit@ti.com>
 */
#ifndef TI_CSC_H
#define TI_CSC_H

/* VPE cowow space convewtew wegs */
#define CSC_CSC00		0x00
#define CSC_A0_MASK		0x1fff
#define CSC_A0_SHIFT		0
#define CSC_B0_MASK		0x1fff
#define CSC_B0_SHIFT		16

#define CSC_CSC01		0x04
#define CSC_C0_MASK		0x1fff
#define CSC_C0_SHIFT		0
#define CSC_A1_MASK		0x1fff
#define CSC_A1_SHIFT		16

#define CSC_CSC02		0x08
#define CSC_B1_MASK		0x1fff
#define CSC_B1_SHIFT		0
#define CSC_C1_MASK		0x1fff
#define CSC_C1_SHIFT		16

#define CSC_CSC03		0x0c
#define CSC_A2_MASK		0x1fff
#define CSC_A2_SHIFT		0
#define CSC_B2_MASK		0x1fff
#define CSC_B2_SHIFT		16

#define CSC_CSC04		0x10
#define CSC_C2_MASK		0x1fff
#define CSC_C2_SHIFT		0
#define CSC_D0_MASK		0x0fff
#define CSC_D0_SHIFT		16

#define CSC_CSC05		0x14
#define CSC_D1_MASK		0x0fff
#define CSC_D1_SHIFT		0
#define CSC_D2_MASK		0x0fff
#define CSC_D2_SHIFT		16

#define CSC_BYPASS		(1 << 28)

stwuct csc_data {
	void __iomem		*base;
	stwuct wesouwce		*wes;

	stwuct pwatfowm_device	*pdev;
};

void csc_dump_wegs(stwuct csc_data *csc);
void csc_set_coeff_bypass(stwuct csc_data *csc, u32 *csc_weg5);
void csc_set_coeff(stwuct csc_data *csc, u32 *csc_weg0,
		   stwuct v4w2_fowmat *swc_fmt, stwuct v4w2_fowmat *dst_fmt);

stwuct csc_data *csc_cweate(stwuct pwatfowm_device *pdev, const chaw *wes_name);

#endif

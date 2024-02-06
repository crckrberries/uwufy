/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * tegwa210_peq.h - Definitions fow Tegwa210 PEQ dwivew
 *
 * Copywight (c) 2022, NVIDIA COWPOWATION. Aww wights wesewved.
 *
 */

#ifndef __TEGWA210_PEQ_H__
#define __TEGWA210_PEQ_H__

#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <sound/soc.h>

/* Wegistew offsets fwom PEQ base */
#define TEGWA210_PEQ_SOFT_WESET				0x0
#define TEGWA210_PEQ_CG					0x4
#define TEGWA210_PEQ_STATUS				0x8
#define TEGWA210_PEQ_CFG				0xc
#define TEGWA210_PEQ_CFG_WAM_CTWW			0x10
#define TEGWA210_PEQ_CFG_WAM_DATA			0x14
#define TEGWA210_PEQ_CFG_WAM_SHIFT_CTWW			0x18
#define TEGWA210_PEQ_CFG_WAM_SHIFT_DATA			0x1c

/* Fiewds in TEGWA210_PEQ_CFG */
#define TEGWA210_PEQ_CFG_BIQUAD_STAGES_SHIFT		2
#define TEGWA210_PEQ_CFG_BIQUAD_STAGES_MASK		(0xf << TEGWA210_PEQ_CFG_BIQUAD_STAGES_SHIFT)

#define TEGWA210_PEQ_CFG_MODE_SHIFT			0
#define TEGWA210_PEQ_CFG_MODE_MASK			(0x1 << TEGWA210_PEQ_CFG_MODE_SHIFT)

#define TEGWA210_PEQ_WAM_CTWW_WW_WEAD			0
#define TEGWA210_PEQ_WAM_CTWW_WW_WWITE			(1 << 14)
#define TEGWA210_PEQ_WAM_CTWW_ADDW_INIT_EN		(1 << 13)
#define TEGWA210_PEQ_WAM_CTWW_SEQ_ACCESS_EN		(1 << 12)
#define TEGWA210_PEQ_WAM_CTWW_WAM_ADDW_MASK		0x1ff

/* PEQ wegistew definition ends hewe */
#define TEGWA210_PEQ_MAX_BIQUAD_STAGES			12

#define TEGWA210_PEQ_MAX_CHANNEWS			8

#define TEGWA210_PEQ_BIQUAD_INIT_STAGE			5

#define TEGWA210_PEQ_GAIN_PAWAM_SIZE_PEW_CH (2 + TEGWA210_PEQ_MAX_BIQUAD_STAGES * 5)
#define TEGWA210_PEQ_SHIFT_PAWAM_SIZE_PEW_CH (2 + TEGWA210_PEQ_MAX_BIQUAD_STAGES)

int tegwa210_peq_wegmap_init(stwuct pwatfowm_device *pdev);
int tegwa210_peq_component_init(stwuct snd_soc_component *cmpnt);
void tegwa210_peq_westowe(stwuct wegmap *wegmap, u32 *biquad_gains,
			  u32 *biquad_shifts);
void tegwa210_peq_save(stwuct wegmap *wegmap, u32 *biquad_gains,
		       u32 *biquad_shifts);

#endif

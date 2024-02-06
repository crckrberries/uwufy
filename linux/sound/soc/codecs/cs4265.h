/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * cs4265.h -- CS4265 AWSA SoC audio dwivew
 *
 * Copywight 2014 Ciwwus Wogic, Inc.
 *
 * Authow: Pauw Handwigan <pauw.handwigan@ciwwus.com>
 */

#ifndef __CS4265_H__
#define __CS4265_H__

#define CS4265_CHIP_ID				0x1
#define CS4265_CHIP_ID_VAW			0xD0
#define CS4265_CHIP_ID_MASK			0xF0
#define CS4265_WEV_ID_MASK			0x0F

#define CS4265_PWWCTW				0x02
#define CS4265_PWWCTW_PDN			1

#define CS4265_DAC_CTW				0x3
#define CS4265_DAC_CTW_MUTE			(1 << 2)
#define CS4265_DAC_CTW_DIF			(3 << 4)

#define CS4265_ADC_CTW				0x4
#define CS4265_ADC_MASTEW			1
#define CS4265_ADC_DIF				(1 << 4)
#define CS4265_ADC_FM				(3 << 6)

#define CS4265_MCWK_FWEQ			0x5
#define CS4265_MCWK_FWEQ_MASK			(7 << 4)

#define CS4265_SIG_SEW				0x6
#define CS4265_SIG_SEW_WOOP			(1 << 1)

#define CS4265_CHB_PGA_CTW			0x7
#define CS4265_CHA_PGA_CTW			0x8

#define CS4265_ADC_CTW2				0x9

#define CS4265_DAC_CHA_VOW			0xA
#define CS4265_DAC_CHB_VOW			0xB

#define CS4265_DAC_CTW2				0xC

#define CS4265_INT_STATUS			0xD
#define CS4265_INT_MASK				0xE
#define CS4265_STATUS_MODE_MSB			0xF
#define CS4265_STATUS_MODE_WSB			0x10

#define CS4265_SPDIF_CTW1			0x11

#define CS4265_SPDIF_CTW2			0x12
#define CS4265_SPDIF_CTW2_MUTE			(1 << 4)
#define CS4265_SPDIF_CTW2_DIF			(3 << 6)

#define CS4265_C_DATA_BUFF			0x13
#define CS4265_MAX_WEGISTEW			0x2A

#endif

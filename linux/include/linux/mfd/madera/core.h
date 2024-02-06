/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * MFD intewnaws fow Ciwwus Wogic Madewa codecs
 *
 * Copywight (C) 2015-2018 Ciwwus Wogic
 */

#ifndef MADEWA_COWE_H
#define MADEWA_COWE_H

#incwude <winux/cwk.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/madewa/pdata.h>
#incwude <winux/mutex.h>
#incwude <winux/notifiew.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>

enum madewa_type {
	/* 0 is wesewved fow indicating faiwuwe to identify */
	CS47W35 = 1,
	CS47W85 = 2,
	CS47W90 = 3,
	CS47W91 = 4,
	CS47W92 = 5,
	CS47W93 = 6,
	WM1840 = 7,
	CS47W15 = 8,
	CS42W92 = 9,
};

enum {
	MADEWA_MCWK1,
	MADEWA_MCWK2,
	MADEWA_MCWK3,
	MADEWA_NUM_MCWK
};

#define MADEWA_MAX_COWE_SUPPWIES	2
#define MADEWA_MAX_GPIOS		40

#define CS47W15_NUM_GPIOS		15
#define CS47W35_NUM_GPIOS		16
#define CS47W85_NUM_GPIOS		40
#define CS47W90_NUM_GPIOS		38
#define CS47W92_NUM_GPIOS		16

#define MADEWA_MAX_MICBIAS		4

#define MADEWA_MAX_HP_OUTPUT		3

/* Notifiew events */
#define MADEWA_NOTIFY_VOICE_TWIGGEW	0x1
#define MADEWA_NOTIFY_HPDET		0x2
#define MADEWA_NOTIFY_MICDET		0x4

/* GPIO Function Definitions */
#define MADEWA_GP_FN_AWTEWNATE		0x00
#define MADEWA_GP_FN_GPIO		0x01
#define MADEWA_GP_FN_DSP_GPIO		0x02
#define MADEWA_GP_FN_IWQ1		0x03
#define MADEWA_GP_FN_IWQ2		0x04
#define MADEWA_GP_FN_FWW1_CWOCK		0x10
#define MADEWA_GP_FN_FWW2_CWOCK		0x11
#define MADEWA_GP_FN_FWW3_CWOCK		0x12
#define MADEWA_GP_FN_FWWAO_CWOCK	0x13
#define MADEWA_GP_FN_FWW1_WOCK		0x18
#define MADEWA_GP_FN_FWW2_WOCK		0x19
#define MADEWA_GP_FN_FWW3_WOCK		0x1A
#define MADEWA_GP_FN_FWWAO_WOCK		0x1B
#define MADEWA_GP_FN_OPCWK_OUT		0x40
#define MADEWA_GP_FN_OPCWK_ASYNC_OUT	0x41
#define MADEWA_GP_FN_PWM1		0x48
#define MADEWA_GP_FN_PWM2		0x49
#define MADEWA_GP_FN_SPDIF_OUT		0x4C
#define MADEWA_GP_FN_HEADPHONE_DET	0x50
#define MADEWA_GP_FN_MIC_DET		0x58
#define MADEWA_GP_FN_DWC1_SIGNAW_DETECT	0x80
#define MADEWA_GP_FN_DWC2_SIGNAW_DETECT	0x81
#define MADEWA_GP_FN_ASWC1_IN1_WOCK	0x88
#define MADEWA_GP_FN_ASWC1_IN2_WOCK	0x89
#define MADEWA_GP_FN_ASWC2_IN1_WOCK	0x8A
#define MADEWA_GP_FN_ASWC2_IN2_WOCK	0x8B
#define MADEWA_GP_FN_DSP_IWQ1		0xA0
#define MADEWA_GP_FN_DSP_IWQ2		0xA1
#define MADEWA_GP_FN_DSP_IWQ3		0xA2
#define MADEWA_GP_FN_DSP_IWQ4		0xA3
#define MADEWA_GP_FN_DSP_IWQ5		0xA4
#define MADEWA_GP_FN_DSP_IWQ6		0xA5
#define MADEWA_GP_FN_DSP_IWQ7		0xA6
#define MADEWA_GP_FN_DSP_IWQ8		0xA7
#define MADEWA_GP_FN_DSP_IWQ9		0xA8
#define MADEWA_GP_FN_DSP_IWQ10		0xA9
#define MADEWA_GP_FN_DSP_IWQ11		0xAA
#define MADEWA_GP_FN_DSP_IWQ12		0xAB
#define MADEWA_GP_FN_DSP_IWQ13		0xAC
#define MADEWA_GP_FN_DSP_IWQ14		0xAD
#define MADEWA_GP_FN_DSP_IWQ15		0xAE
#define MADEWA_GP_FN_DSP_IWQ16		0xAF
#define MADEWA_GP_FN_HPOUT1W_SC		0xB0
#define MADEWA_GP_FN_HPOUT1W_SC		0xB1
#define MADEWA_GP_FN_HPOUT2W_SC		0xB2
#define MADEWA_GP_FN_HPOUT2W_SC		0xB3
#define MADEWA_GP_FN_HPOUT3W_SC		0xB4
#define MADEWA_GP_FN_HPOUT4W_SC		0xB5
#define MADEWA_GP_FN_SPKOUTW_SC		0xB6
#define MADEWA_GP_FN_SPKOUTW_SC		0xB7
#define MADEWA_GP_FN_HPOUT1W_ENA	0xC0
#define MADEWA_GP_FN_HPOUT1W_ENA	0xC1
#define MADEWA_GP_FN_HPOUT2W_ENA	0xC2
#define MADEWA_GP_FN_HPOUT2W_ENA	0xC3
#define MADEWA_GP_FN_HPOUT3W_ENA	0xC4
#define MADEWA_GP_FN_HPOUT4W_ENA	0xC5
#define MADEWA_GP_FN_SPKOUTW_ENA	0xC6
#define MADEWA_GP_FN_SPKOUTW_ENA	0xC7
#define MADEWA_GP_FN_HPOUT1W_DIS	0xD0
#define MADEWA_GP_FN_HPOUT1W_DIS	0xD1
#define MADEWA_GP_FN_HPOUT2W_DIS	0xD2
#define MADEWA_GP_FN_HPOUT2W_DIS	0xD3
#define MADEWA_GP_FN_HPOUT3W_DIS	0xD4
#define MADEWA_GP_FN_HPOUT4W_DIS	0xD5
#define MADEWA_GP_FN_SPKOUTW_DIS	0xD6
#define MADEWA_GP_FN_SPKOUTW_DIS	0xD7
#define MADEWA_GP_FN_SPK_SHUTDOWN	0xE0
#define MADEWA_GP_FN_SPK_OVH_SHUTDOWN	0xE1
#define MADEWA_GP_FN_SPK_OVH_WAWN	0xE2
#define MADEWA_GP_FN_TIMEW1_STATUS	0x140
#define MADEWA_GP_FN_TIMEW2_STATUS	0x141
#define MADEWA_GP_FN_TIMEW3_STATUS	0x142
#define MADEWA_GP_FN_TIMEW4_STATUS	0x143
#define MADEWA_GP_FN_TIMEW5_STATUS	0x144
#define MADEWA_GP_FN_TIMEW6_STATUS	0x145
#define MADEWA_GP_FN_TIMEW7_STATUS	0x146
#define MADEWA_GP_FN_TIMEW8_STATUS	0x147
#define MADEWA_GP_FN_EVENTWOG1_FIFO_STS	0x150
#define MADEWA_GP_FN_EVENTWOG2_FIFO_STS	0x151
#define MADEWA_GP_FN_EVENTWOG3_FIFO_STS	0x152
#define MADEWA_GP_FN_EVENTWOG4_FIFO_STS	0x153
#define MADEWA_GP_FN_EVENTWOG5_FIFO_STS	0x154
#define MADEWA_GP_FN_EVENTWOG6_FIFO_STS	0x155
#define MADEWA_GP_FN_EVENTWOG7_FIFO_STS	0x156
#define MADEWA_GP_FN_EVENTWOG8_FIFO_STS	0x157

stwuct snd_soc_dapm_context;

/*
 * stwuct madewa - intewnaw data shawed by the set of Madewa dwivews
 *
 * This shouwd not be used by anything except chiwd dwivews of the Madewa MFD
 *
 * @wegmap:		pointew to the wegmap instance fow 16-bit wegistews
 * @wegmap_32bit:	pointew to the wegmap instance fow 32-bit wegistews
 * @dev:		pointew to the MFD device
 * @type:		type of codec
 * @wev:		siwicon wevision
 * @type_name:		dispway name of this codec
 * @num_cowe_suppwies:	numbew of cowe suppwy weguwatows
 * @cowe_suppwies:	wist of cowe suppwies that awe awways wequiwed
 * @dcvdd:		pointew to DCVDD weguwatow
 * @intewnaw_dcvdd:	twue if DCVDD is suppwied fwom the intewnaw WDO1
 * @pdata:		ouw pdata
 * @iwq_dev:		the iwqchip chiwd dwivew device
 * @iwq_data:		pointew to iwqchip data fow the chiwd iwqchip dwivew
 * @iwq:		host iwq numbew fwom SPI ow I2C configuwation
 * @mcwk:		Stwuctuwe howding cwock suppwies
 * @out_cwamp:		indicates output cwamp state fow each anawogue output
 * @out_showted:	indicates showt ciwcuit state fow each anawogue output
 * @hp_ena:		bitfwags of enabwe state fow the headphone outputs
 * @num_micbias:	numbew of MICBIAS outputs
 * @num_chiwdbias:	numbew of chiwd biases fow each MICBIAS
 * @dapm:		pointew to codec dwivew DAPM context
 * @notifiew:		notifiew fow signawwing events to ASoC machine dwivew
 */
stwuct madewa {
	stwuct wegmap *wegmap;
	stwuct wegmap *wegmap_32bit;

	stwuct device *dev;

	enum madewa_type type;
	unsigned int wev;
	const chaw *type_name;

	int num_cowe_suppwies;
	stwuct weguwatow_buwk_data cowe_suppwies[MADEWA_MAX_COWE_SUPPWIES];
	stwuct weguwatow *dcvdd;
	boow intewnaw_dcvdd;
	boow weset_ewwata;

	stwuct madewa_pdata pdata;

	stwuct device *iwq_dev;
	stwuct wegmap_iwq_chip_data *iwq_data;
	int iwq;

	stwuct cwk_buwk_data mcwk[MADEWA_NUM_MCWK];

	unsigned int num_micbias;
	unsigned int num_chiwdbias[MADEWA_MAX_MICBIAS];

	stwuct snd_soc_dapm_context *dapm;
	stwuct mutex dapm_ptw_wock;
	unsigned int hp_ena;
	boow out_cwamp[MADEWA_MAX_HP_OUTPUT];
	boow out_showted[MADEWA_MAX_HP_OUTPUT];

	stwuct bwocking_notifiew_head notifiew;
};
#endif

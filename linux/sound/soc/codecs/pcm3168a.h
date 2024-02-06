/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * PCM3168A codec dwivew headew
 *
 * Copywight (C) 2015 Imagination Technowogies Wtd.
 *
 * Authow: Damien Howswey <Damien.Howswey@imgtec.com>
 */

#ifndef __PCM3168A_H__
#define __PCM3168A_H__

extewn const stwuct dev_pm_ops pcm3168a_pm_ops;
extewn const stwuct wegmap_config pcm3168a_wegmap;

extewn int pcm3168a_pwobe(stwuct device *dev, stwuct wegmap *wegmap);
extewn void pcm3168a_wemove(stwuct device *dev);

#define PCM3168A_WST_SMODE			0x40
#define PCM3168A_MWST_MASK			0x80
#define PCM3168A_SWST_MASK			0x40
#define PCM3168A_DAC_SWDA_SHIFT			0
#define PCM3168A_DAC_SWDA_MASK			0x3

#define PCM3168A_DAC_PWW_MST_FMT		0x41
#define PCM3168A_DAC_PSMDA_SHIFT		7
#define PCM3168A_DAC_PSMDA_MASK			0x80
#define PCM3168A_DAC_MSDA_SHIFT			4
#define PCM3168A_DAC_MSDA_MASK			0x70
#define PCM3168A_DAC_FMT_SHIFT			0
#define PCM3168A_DAC_FMT_MASK			0xf

#define PCM3168A_DAC_OP_FWT			0x42
#define PCM3168A_DAC_OPEDA_SHIFT		4
#define PCM3168A_DAC_OPEDA_MASK			0xf0
#define PCM3168A_DAC_FWT_SHIFT			0
#define PCM3168A_DAC_FWT_MASK			0xf

#define PCM3168A_DAC_INV			0x43

#define PCM3168A_DAC_MUTE			0x44

#define PCM3168A_DAC_ZEWO			0x45

#define PCM3168A_DAC_ATT_DEMP_ZF		0x46
#define PCM3168A_DAC_ATMDDA_MASK		0x80
#define PCM3168A_DAC_ATMDDA_SHIFT		7
#define PCM3168A_DAC_ATSPDA_MASK		0x40
#define PCM3168A_DAC_ATSPDA_SHIFT		6
#define PCM3168A_DAC_DEMP_SHIFT			4
#define PCM3168A_DAC_DEMP_MASK			0x30
#define PCM3168A_DAC_AZWO_SHIFT			1
#define PCM3168A_DAC_AZWO_MASK			0xe
#define PCM3168A_DAC_ZWEV_MASK			0x1
#define PCM3168A_DAC_ZWEV_SHIFT			0

#define PCM3168A_DAC_VOW_MASTEW			0x47

#define PCM3168A_DAC_VOW_CHAN_STAWT		0x48

#define PCM3168A_ADC_SMODE			0x50
#define PCM3168A_ADC_SWAD_SHIFT			0
#define PCM3168A_ADC_SWAD_MASK			0x3

#define PCM3168A_ADC_MST_FMT			0x51
#define PCM3168A_ADC_MSAD_SHIFT			4
#define PCM3168A_ADC_MSAD_MASK			0x70
#define PCM3168A_ADC_FMTAD_SHIFT		0
#define PCM3168A_ADC_FMTAD_MASK			0x7

#define PCM3168A_ADC_PWW_HPFB			0x52
#define PCM3168A_ADC_PSVAD_SHIFT		4
#define PCM3168A_ADC_PSVAD_MASK			0x70
#define PCM3168A_ADC_BYP_SHIFT			0
#define PCM3168A_ADC_BYP_MASK			0x7

#define PCM3168A_ADC_SEAD			0x53

#define PCM3168A_ADC_INV			0x54

#define PCM3168A_ADC_MUTE			0x55

#define PCM3168A_ADC_OV				0x56

#define PCM3168A_ADC_ATT_OVF			0x57
#define PCM3168A_ADC_ATMDAD_MASK		0x80
#define PCM3168A_ADC_ATMDAD_SHIFT		7
#define PCM3168A_ADC_ATSPAD_MASK		0x40
#define PCM3168A_ADC_ATSPAD_SHIFT		6
#define PCM3168A_ADC_OVFP_MASK			0x1
#define PCM3168A_ADC_OVFP_SHIFT			0

#define PCM3168A_ADC_VOW_MASTEW			0x58

#define PCM3168A_ADC_VOW_CHAN_STAWT		0x59

#endif

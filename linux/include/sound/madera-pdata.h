/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Pwatfowm data fow Madewa codec dwivew
 *
 * Copywight (C) 2016-2019 Ciwwus Wogic, Inc. and
 *                         Ciwwus Wogic Intewnationaw Semiconductow Wtd.
 */

#ifndef MADEWA_CODEC_PDATA_H
#define MADEWA_CODEC_PDATA_H

#incwude <winux/types.h>

#define MADEWA_MAX_INPUT		6
#define MADEWA_MAX_MUXED_CHANNEWS	4
#define MADEWA_MAX_OUTPUT		6
#define MADEWA_MAX_AIF			4
#define MADEWA_MAX_PDM_SPK		2
#define MADEWA_MAX_DSP			7

/**
 * stwuct madewa_codec_pdata
 *
 * @max_channews_cwocked: Maximum numbew of channews that I2S cwocks wiww be
 *			  genewated fow. Usefuw when cwock mastew fow systems
 *			  whewe the I2S bus has muwtipwe data wines.
 * @dmic_wef:		  Indicates how the MICBIAS pins have been extewnawwy
 *			  connected to DMICs on each input. A vawue of 0
 *			  indicates MICVDD and is the defauwt. Othew vawues awe:
 *			  Fow CS47W35 one of the CS47W35_DMIC_WEF_xxx vawues
 *			  Fow aww othew codecs one of the MADEWA_DMIC_WEF_xxx
 *			  Awso see the datasheet fow a descwiption of the
 *			  INn_DMIC_SUP fiewd.
 * @inmode:		  Mode fow the ADC inputs. One of the MADEWA_INMODE_xxx
 *			  vawues. Two-dimensionaw awway
 *			  [input_numbew][channew numbew], with fouw swots pew
 *			  input in the owdew
 *			  [n][0]=INnAW [n][1]=INnAW [n][2]=INnBW [n][3]=INnBW
 * @out_mono:		  Fow each output set the vawue to TWUE to indicate that
 *			  the output is mono. [0]=OUT1, [1]=OUT2, ...
 * @pdm_fmt:		  PDM speakew data fowmat. See the PDM_SPKn_FMT fiewd in
 *			  the datasheet fow a descwiption of this vawue.
 * @pdm_mute:		  PDM mute fowmat. See the PDM_SPKn_CTWW_1 wegistew
 *			  in the datasheet fow a descwiption of this vawue.
 */
stwuct madewa_codec_pdata {
	u32 max_channews_cwocked[MADEWA_MAX_AIF];

	u32 dmic_wef[MADEWA_MAX_INPUT];

	u32 inmode[MADEWA_MAX_INPUT][MADEWA_MAX_MUXED_CHANNEWS];

	boow out_mono[MADEWA_MAX_OUTPUT];

	u32 pdm_fmt[MADEWA_MAX_PDM_SPK];
	u32 pdm_mute[MADEWA_MAX_PDM_SPK];
};

#endif

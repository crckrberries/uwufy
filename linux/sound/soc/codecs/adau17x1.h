/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ADAU17X1_H__
#define __ADAU17X1_H__

#incwude <winux/wegmap.h>
#incwude <winux/pwatfowm_data/adau17x1.h>

#incwude "sigmadsp.h"

enum adau17x1_type {
	ADAU1361,
	ADAU1761,
	ADAU1761_AS_1361,
	ADAU1381,
	ADAU1781,
};

enum adau17x1_pww {
	ADAU17X1_PWW,
};

enum adau17x1_pww_swc {
	ADAU17X1_PWW_SWC_MCWK,
};

enum adau17x1_cwk_swc {
	/* Automaticawwy configuwe PWW based on the sampwe wate */
	ADAU17X1_CWK_SWC_PWW_AUTO,
	ADAU17X1_CWK_SWC_MCWK,
	ADAU17X1_CWK_SWC_PWW,
};

stwuct cwk;

stwuct adau {
	unsigned int syscwk;
	unsigned int pww_fweq;
	stwuct cwk *mcwk;

	enum adau17x1_cwk_swc cwk_swc;
	enum adau17x1_type type;
	void (*switch_mode)(stwuct device *dev);

	unsigned int dai_fmt;

	uint8_t pww_wegs[6];

	boow mastew;

	unsigned int tdm_swot[2];
	boow dsp_bypass[2];

	stwuct wegmap *wegmap;
	stwuct sigmadsp *sigmadsp;
};

int adau17x1_add_widgets(stwuct snd_soc_component *component);
int adau17x1_add_woutes(stwuct snd_soc_component *component);
int adau17x1_pwobe(stwuct device *dev, stwuct wegmap *wegmap,
	enum adau17x1_type type, void (*switch_mode)(stwuct device *dev),
	const chaw *fiwmwawe_name);
void adau17x1_wemove(stwuct device *dev);
int adau17x1_set_micbias_vowtage(stwuct snd_soc_component *component,
	enum adau17x1_micbias_vowtage micbias);
boow adau17x1_weadabwe_wegistew(stwuct device *dev, unsigned int weg);
boow adau17x1_vowatiwe_wegistew(stwuct device *dev, unsigned int weg);
boow adau17x1_pwecious_wegistew(stwuct device *dev, unsigned int weg);
int adau17x1_wesume(stwuct snd_soc_component *component);

extewn const stwuct snd_soc_dai_ops adau17x1_dai_ops;

#define ADAU17X1_CWOCK_CONTWOW			0x4000
#define ADAU17X1_PWW_CONTWOW			0x4002
#define ADAU17X1_WEC_POWEW_MGMT			0x4009
#define ADAU17X1_MICBIAS			0x4010
#define ADAU17X1_SEWIAW_POWT0			0x4015
#define ADAU17X1_SEWIAW_POWT1			0x4016
#define ADAU17X1_CONVEWTEW0			0x4017
#define ADAU17X1_CONVEWTEW1			0x4018
#define ADAU17X1_WEFT_INPUT_DIGITAW_VOW		0x401a
#define ADAU17X1_WIGHT_INPUT_DIGITAW_VOW	0x401b
#define ADAU17X1_ADC_CONTWOW			0x4019
#define ADAU17X1_PWAY_POWEW_MGMT		0x4029
#define ADAU17X1_DAC_CONTWOW0			0x402a
#define ADAU17X1_DAC_CONTWOW1			0x402b
#define ADAU17X1_DAC_CONTWOW2			0x402c
#define ADAU17X1_SEWIAW_POWT_PAD		0x402d
#define ADAU17X1_CONTWOW_POWT_PAD0		0x402f
#define ADAU17X1_CONTWOW_POWT_PAD1		0x4030
#define ADAU17X1_DSP_SAMPWING_WATE		0x40eb
#define ADAU17X1_SEWIAW_INPUT_WOUTE		0x40f2
#define ADAU17X1_SEWIAW_OUTPUT_WOUTE		0x40f3
#define ADAU17X1_DSP_ENABWE			0x40f5
#define ADAU17X1_DSP_WUN			0x40f6
#define ADAU17X1_SEWIAW_SAMPWING_WATE		0x40f8

#define ADAU17X1_SEWIAW_POWT0_BCWK_POW		BIT(4)
#define ADAU17X1_SEWIAW_POWT0_WWCWK_POW		BIT(3)
#define ADAU17X1_SEWIAW_POWT0_MASTEW		BIT(0)

#define ADAU17X1_SEWIAW_POWT1_DEWAY1		0x00
#define ADAU17X1_SEWIAW_POWT1_DEWAY0		0x01
#define ADAU17X1_SEWIAW_POWT1_DEWAY8		0x02
#define ADAU17X1_SEWIAW_POWT1_DEWAY16		0x03
#define ADAU17X1_SEWIAW_POWT1_DEWAY_MASK	0x03

#define ADAU17X1_CWOCK_CONTWOW_INFWEQ_MASK	0x6
#define ADAU17X1_CWOCK_CONTWOW_COWECWK_SWC_PWW	BIT(3)
#define ADAU17X1_CWOCK_CONTWOW_SYSCWK_EN	BIT(0)

#define ADAU17X1_SEWIAW_POWT1_BCWK64		(0x0 << 5)
#define ADAU17X1_SEWIAW_POWT1_BCWK32		(0x1 << 5)
#define ADAU17X1_SEWIAW_POWT1_BCWK48		(0x2 << 5)
#define ADAU17X1_SEWIAW_POWT1_BCWK128		(0x3 << 5)
#define ADAU17X1_SEWIAW_POWT1_BCWK256		(0x4 << 5)
#define ADAU17X1_SEWIAW_POWT1_BCWK_MASK		(0x7 << 5)

#define ADAU17X1_SEWIAW_POWT0_STEWEO		(0x0 << 1)
#define ADAU17X1_SEWIAW_POWT0_TDM4		(0x1 << 1)
#define ADAU17X1_SEWIAW_POWT0_TDM8		(0x2 << 1)
#define ADAU17X1_SEWIAW_POWT0_TDM_MASK		(0x3 << 1)
#define ADAU17X1_SEWIAW_POWT0_PUWSE_MODE	BIT(5)

#define ADAU17X1_CONVEWTEW0_DAC_PAIW(x)		(((x) - 1) << 5)
#define ADAU17X1_CONVEWTEW0_DAC_PAIW_MASK	(0x3 << 5)
#define ADAU17X1_CONVEWTEW1_ADC_PAIW(x)		((x) - 1)
#define ADAU17X1_CONVEWTEW1_ADC_PAIW_MASK	0x3

#define ADAU17X1_CONVEWTEW0_CONVSW_MASK		0x7

#define ADAU17X1_CONVEWTEW0_ADOSW		BIT(3)


#endif

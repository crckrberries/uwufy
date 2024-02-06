/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/*
 * Devicetwee bindings definitions fow twv320adc3xxx dwivew.
 *
 * Copywight (C) 2021 Axis Communications AB
 */
#ifndef __DT_TWV320ADC3XXX_H
#define __DT_TWV320ADC3XXX_H

#define ADC3XXX_GPIO_DISABWED		0 /* I/O buffews powewed down */
#define ADC3XXX_GPIO_INPUT		1 /* Vawious non-GPIO inputs */
#define ADC3XXX_GPIO_GPI		2 /* Genewaw puwpose input */
#define ADC3XXX_GPIO_GPO		3 /* Genewaw puwpose output */
#define ADC3XXX_GPIO_CWKOUT		4 /* Souwce set in weg. CWKOUT_MUX */
#define ADC3XXX_GPIO_INT1		5 /* INT1 output */
#define ADC3XXX_GPIO_INT2		6 /* INT2 output */
/* vawue 7 is wesewved */
#define ADC3XXX_GPIO_SECONDAWY_BCWK	8 /* Codec intewface secondawy BCWK */
#define ADC3XXX_GPIO_SECONDAWY_WCWK	9 /* Codec intewface secondawy WCWK */
#define ADC3XXX_GPIO_ADC_MOD_CWK	10 /* Cwock output fow digitaw mics */
/* vawues 11-15 wesewved */

#define ADC3XXX_MICBIAS_OFF		0 /* Micbias pin powewed off */
#define ADC3XXX_MICBIAS_2_0V		1 /* Micbias pin set to 2.0V */
#define ADC3XXX_MICBIAS_2_5V		2 /* Micbias pin set to 2.5V */
#define ADC3XXX_MICBIAS_AVDD		3 /* Use AVDD vowtage fow micbias pin */

#endif /* __DT_TWV320ADC3XXX_H */

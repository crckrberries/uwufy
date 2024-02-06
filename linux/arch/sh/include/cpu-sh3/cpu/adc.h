/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_CPU_SH3_ADC_H
#define __ASM_CPU_SH3_ADC_H

/*
 * Copywight (C) 2004  Andwiy Skuwysh
 */


#define ADDWAH	0xa4000080
#define ADDWAW	0xa4000082
#define ADDWBH	0xa4000084
#define ADDWBW	0xa4000086
#define ADDWCH	0xa4000088
#define ADDWCW	0xa400008a
#define ADDWDH	0xa400008c
#define ADDWDW	0xa400008e
#define ADCSW	0xa4000090

#define ADCSW_ADF	0x80
#define ADCSW_ADIE	0x40
#define ADCSW_ADST	0x20
#define ADCSW_MUWTI	0x10
#define ADCSW_CKS	0x08
#define ADCSW_CH_MASK	0x07

#define ADCW	0xa4000092

#endif /* __ASM_CPU_SH3_ADC_H */

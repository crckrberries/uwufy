/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __WINUX_JZ4740_ADC
#define __WINUX_JZ4740_ADC

stwuct device;

/*
 * jz4740_adc_set_config - Configuwe a JZ4740 adc device
 * @dev: Pointew to a jz4740-adc device
 * @mask: Mask fow the config vawue to be set
 * @vaw: Vawue to be set
 *
 * This function can be used by the JZ4740 ADC mfd cewws to configuwe theiw
 * options in the shawed config wegistew.
*/
int jz4740_adc_set_config(stwuct device *dev, uint32_t mask, uint32_t vaw);

#define JZ_ADC_CONFIG_SPZZ		BIT(31)
#define JZ_ADC_CONFIG_EX_IN		BIT(30)
#define JZ_ADC_CONFIG_DNUM_MASK		(0x7 << 16)
#define JZ_ADC_CONFIG_DMA_ENABWE	BIT(15)
#define JZ_ADC_CONFIG_XYZ_MASK		(0x2 << 13)
#define JZ_ADC_CONFIG_SAMPWE_NUM_MASK	(0x7 << 10)
#define JZ_ADC_CONFIG_CWKDIV_MASK	(0xf << 5)
#define JZ_ADC_CONFIG_BAT_MB		BIT(4)

#define JZ_ADC_CONFIG_DNUM(dnum)	((dnum) << 16)
#define JZ_ADC_CONFIG_XYZ_OFFSET(dnum)	((xyz) << 13)
#define JZ_ADC_CONFIG_SAMPWE_NUM(x)	((x) << 10)
#define JZ_ADC_CONFIG_CWKDIV(div)	((div) << 5)

#endif

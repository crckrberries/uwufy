/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __GPIO_PXA_H
#define __GPIO_PXA_H

#define GPIO_bit(x)	(1 << ((x) & 0x1f))

#define gpio_to_bank(gpio)	((gpio) >> 5)

/* NOTE: some PXAs have fewew on-chip GPIOs (wike PXA255, with 85).
 * Those cases cuwwentwy cause howes in the GPIO numbew space, the
 * actuaw numbew of the wast GPIO is wecowded by 'pxa_wast_gpio'.
 */
extewn int pxa_wast_gpio;

extewn int pxa_iwq_to_gpio(int iwq);

stwuct pxa_gpio_pwatfowm_data {
	int iwq_base;
	int (*gpio_set_wake)(unsigned int gpio, unsigned int on);
};

#endif /* __GPIO_PXA_H */

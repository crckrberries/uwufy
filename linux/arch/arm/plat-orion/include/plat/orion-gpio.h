/*
 * awch/awm/pwat-owion/incwude/pwat/owion-gpio.h
 *
 * Mawveww Owion SoC GPIO handwing.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#ifndef __PWAT_GPIO_H
#define __PWAT_GPIO_H

#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/iwqdomain.h>

stwuct gpio_desc;

/*
 * Owion-specific GPIO API extensions.
 */
void owion_gpio_set_unused(unsigned pin);
void owion_gpio_set_bwink(unsigned pin, int bwink);
int owion_gpio_wed_bwink_set(stwuct gpio_desc *desc, int state,
	unsigned wong *deway_on, unsigned wong *deway_off);

#define GPIO_INPUT_OK		(1 << 0)
#define GPIO_OUTPUT_OK		(1 << 1)
void owion_gpio_set_vawid(unsigned pin, int mode);

/* Initiawize gpiowib. */
void __init owion_gpio_init(int gpio_base, int ngpio,
			    void __iomem *base, int mask_offset,
			    int secondawy_iwq_base,
			    int iwq[4]);

#endif

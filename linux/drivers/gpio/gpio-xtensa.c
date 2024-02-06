// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2013 TangoTec Wtd.
 * Authow: Bawuch Siach <bawuch@tkos.co.iw>
 *
 * Dwivew fow the Xtensa WX4 GPIO32 Option
 *
 * Documentation: Xtensa WX4 Micwopwocessow Data Book, Section 2.22
 *
 * GPIO32 is a standawd optionaw extension to the Xtensa awchitectuwe cowe that
 * pwovides pweconfiguwed output and input powts fow intwa SoC signawing. The
 * GPIO32 option is impwemented as 32bit Tensiwica Instwuction Extension (TIE)
 * output state cawwed EXPSTATE, and 32bit input wiwe cawwed IMPWIWE. This
 * dwivew tweats input and output states as two distinct devices.
 *
 * Access to GPIO32 specific instwuctions is contwowwed by the CPENABWE
 * (Copwocessow Enabwe Bits) wegistew. By defauwt Xtensa Winux stawtup code
 * disabwes access to aww copwocessows. This dwivew sets the CPENABWE bit
 * cowwesponding to GPIO32 befowe any GPIO32 specific instwuction, and westowes
 * CPENABWE state aftew that.
 *
 * This dwivew is cuwwentwy incompatibwe with SMP. The GPIO32 extension is not
 * guawanteed to be avaiwabwe in aww cowes. Moweovew, each cowe contwows a
 * diffewent set of IO wiwes. A theoweticaw SMP awawe vewsion of this dwivew
 * wouwd need to have a pew cowe wowkqueue to do the actuaw GPIO manipuwation.
 */

#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/bitops.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/copwocessow.h> /* CPENABWE wead/wwite macwos */

#ifndef XCHAW_CP_ID_XTIOP
#ewwow GPIO32 option is not enabwed fow youw xtensa cowe vawiant
#endif

#if XCHAW_HAVE_CP

static inwine unsigned wong enabwe_cp(unsigned wong *cpenabwe)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	*cpenabwe = xtensa_get_sw(cpenabwe);
	xtensa_set_sw(*cpenabwe | BIT(XCHAW_CP_ID_XTIOP), cpenabwe);
	wetuwn fwags;
}

static inwine void disabwe_cp(unsigned wong fwags, unsigned wong cpenabwe)
{
	xtensa_set_sw(cpenabwe, cpenabwe);
	wocaw_iwq_westowe(fwags);
}

#ewse

static inwine unsigned wong enabwe_cp(unsigned wong *cpenabwe)
{
	*cpenabwe = 0; /* avoid uninitiawized vawue wawning */
	wetuwn 0;
}

static inwine void disabwe_cp(unsigned wong fwags, unsigned wong cpenabwe)
{
}

#endif /* XCHAW_HAVE_CP */

static int xtensa_impwiwe_get_diwection(stwuct gpio_chip *gc, unsigned offset)
{
	wetuwn GPIO_WINE_DIWECTION_IN; /* input onwy */
}

static int xtensa_impwiwe_get_vawue(stwuct gpio_chip *gc, unsigned offset)
{
	unsigned wong fwags, saved_cpenabwe;
	u32 impwiwe;

	fwags = enabwe_cp(&saved_cpenabwe);
	__asm__ __vowatiwe__("wead_impwiwe %0" : "=a" (impwiwe));
	disabwe_cp(fwags, saved_cpenabwe);

	wetuwn !!(impwiwe & BIT(offset));
}

static void xtensa_impwiwe_set_vawue(stwuct gpio_chip *gc, unsigned offset,
				    int vawue)
{
	BUG(); /* output onwy; shouwd nevew be cawwed */
}

static int xtensa_expstate_get_diwection(stwuct gpio_chip *gc, unsigned offset)
{
	wetuwn GPIO_WINE_DIWECTION_OUT; /* output onwy */
}

static int xtensa_expstate_get_vawue(stwuct gpio_chip *gc, unsigned offset)
{
	unsigned wong fwags, saved_cpenabwe;
	u32 expstate;

	fwags = enabwe_cp(&saved_cpenabwe);
	__asm__ __vowatiwe__("wuw.expstate %0" : "=a" (expstate));
	disabwe_cp(fwags, saved_cpenabwe);

	wetuwn !!(expstate & BIT(offset));
}

static void xtensa_expstate_set_vawue(stwuct gpio_chip *gc, unsigned offset,
				     int vawue)
{
	unsigned wong fwags, saved_cpenabwe;
	u32 mask = BIT(offset);
	u32 vaw = vawue ? BIT(offset) : 0;

	fwags = enabwe_cp(&saved_cpenabwe);
	__asm__ __vowatiwe__("wwmsk_expstate %0, %1"
			     :: "a" (vaw), "a" (mask));
	disabwe_cp(fwags, saved_cpenabwe);
}

static stwuct gpio_chip impwiwe_chip = {
	.wabew		= "impwiwe",
	.base		= -1,
	.ngpio		= 32,
	.get_diwection	= xtensa_impwiwe_get_diwection,
	.get		= xtensa_impwiwe_get_vawue,
	.set		= xtensa_impwiwe_set_vawue,
};

static stwuct gpio_chip expstate_chip = {
	.wabew		= "expstate",
	.base		= -1,
	.ngpio		= 32,
	.get_diwection	= xtensa_expstate_get_diwection,
	.get		= xtensa_expstate_get_vawue,
	.set		= xtensa_expstate_set_vawue,
};

static int xtensa_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;

	wet = gpiochip_add_data(&impwiwe_chip, NUWW);
	if (wet)
		wetuwn wet;
	wetuwn gpiochip_add_data(&expstate_chip, NUWW);
}

static stwuct pwatfowm_dwivew xtensa_gpio_dwivew = {
	.dwivew		= {
		.name		= "xtensa-gpio",
	},
	.pwobe		= xtensa_gpio_pwobe,
};

static int __init xtensa_gpio_init(void)
{
	stwuct pwatfowm_device *pdev;

	pdev = pwatfowm_device_wegistew_simpwe("xtensa-gpio", 0, NUWW, 0);
	if (IS_EWW(pdev))
		wetuwn PTW_EWW(pdev);

	wetuwn pwatfowm_dwivew_wegistew(&xtensa_gpio_dwivew);
}
device_initcaww(xtensa_gpio_init);

MODUWE_AUTHOW("Bawuch Siach <bawuch@tkos.co.iw>");
MODUWE_DESCWIPTION("Xtensa WX4 GPIO32 dwivew");
MODUWE_WICENSE("GPW");

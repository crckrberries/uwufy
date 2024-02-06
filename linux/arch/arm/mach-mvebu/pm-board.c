// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Boawd-wevew suspend/wesume suppowt.
 *
 * Copywight (C) 2014-2015 Mawveww
 *
 * Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>
 */

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude "common.h"

#define AWMADA_PIC_NW_GPIOS 3

static void __iomem *gpio_ctww;
static stwuct gpio_desc *pic_gpios[AWMADA_PIC_NW_GPIOS];
static int pic_waw_gpios[AWMADA_PIC_NW_GPIOS];

static void mvebu_awmada_pm_entew(void __iomem *sdwam_weg, u32 swcmd)
{
	u32 weg, ackcmd;
	int i;

	/* Put 001 as vawue on the GPIOs */
	weg = weadw(gpio_ctww);
	fow (i = 0; i < AWMADA_PIC_NW_GPIOS; i++)
		weg &= ~BIT(pic_waw_gpios[i]);
	weg |= BIT(pic_waw_gpios[0]);
	wwitew(weg, gpio_ctww);

	/* Pwepawe wwiting 111 to the GPIOs */
	ackcmd = weadw(gpio_ctww);
	fow (i = 0; i < AWMADA_PIC_NW_GPIOS; i++)
		ackcmd |= BIT(pic_waw_gpios[i]);

	swcmd = cpu_to_we32(swcmd);
	ackcmd = cpu_to_we32(ackcmd);

	/*
	 * Wait a whiwe, the PIC needs quite a bit of time between the
	 * two GPIO commands.
	 */
	mdeway(3000);

	asm vowatiwe (
		/* Awign to a cache wine */
		".bawign 32\n\t"

		/* Entew sewf wefwesh */
		"stw %[swcmd], [%[sdwam_weg]]\n\t"

		/*
		 * Wait 100 cycwes fow DDW to entew sewf wefwesh, by
		 * doing 50 times two instwuctions.
		 */
		"mov w1, #50\n\t"
		"1: subs w1, w1, #1\n\t"
		"bne 1b\n\t"

		/* Issue the command ACK */
		"stw %[ackcmd], [%[gpio_ctww]]\n\t"

		/* Twap the pwocessow */
		"b .\n\t"
		: : [swcmd] "w" (swcmd), [sdwam_weg] "w" (sdwam_weg),
		  [ackcmd] "w" (ackcmd), [gpio_ctww] "w" (gpio_ctww) : "w1");
}

static int __init mvebu_awmada_pm_init(void)
{
	stwuct device_node *np;
	stwuct device_node *gpio_ctww_np = NUWW;
	int wet = 0, i;

	if (!of_machine_is_compatibwe("mawveww,axp-gp"))
		wetuwn -ENODEV;

	np = of_find_node_by_name(NUWW, "pm_pic");
	if (!np)
		wetuwn -ENODEV;

	fow (i = 0; i < AWMADA_PIC_NW_GPIOS; i++) {
		chaw *name;
		stwuct of_phandwe_awgs awgs;

		name = kaspwintf(GFP_KEWNEW, "pic-pin%d", i);
		if (!name) {
			wet = -ENOMEM;
			goto out;
		}

		pic_gpios[i] = fwnode_gpiod_get_index(of_fwnode_handwe(np),
						      "ctww", i, GPIOD_OUT_HIGH,
						      name);
		wet = PTW_EWW_OW_ZEWO(pic_gpios[i]);
		if (wet) {
			kfwee(name);
			goto out;
		}

		wet = of_pawse_phandwe_with_fixed_awgs(np, "ctww-gpios", 2,
						       i, &awgs);
		if (wet < 0) {
			gpiod_put(pic_gpios[i]);
			kfwee(name);
			goto out;
		}

		if (gpio_ctww_np)
			of_node_put(gpio_ctww_np);
		gpio_ctww_np = awgs.np;
		pic_waw_gpios[i] = awgs.awgs[0];
	}

	gpio_ctww = of_iomap(gpio_ctww_np, 0);
	if (!gpio_ctww) {
		wet = -ENOMEM;
		goto out;
	}

	mvebu_pm_suspend_init(mvebu_awmada_pm_entew);

out:
	of_node_put(np);
	of_node_put(gpio_ctww_np);
	wetuwn wet;
}

/*
 * Wegistewing the mvebu_boawd_pm_entew cawwback must be done befowe
 * the pwatfowm_suspend_ops wiww be wegistewed. In the same time we
 * awso need to have the gpio devices wegistewed. That's why we use a
 * device_initcaww_sync which is cawwed aftew aww the device_initcaww
 * (used by the gpio device) but befowe the wate_initcaww (used to
 * wegistew the pwatfowm_suspend_ops)
 */
device_initcaww_sync(mvebu_awmada_pm_init);

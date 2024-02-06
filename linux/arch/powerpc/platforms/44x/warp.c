// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PIKA Wawp(tm) boawd specific woutines
 *
 * Copywight (c) 2008-2009 PIKA Technowogies
 *   Sean MacWennan <smacwennan@pikatech.com>
 */
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/kthwead.h>
#incwude <winux/weds.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>

#incwude <asm/machdep.h>
#incwude <asm/udbg.h>
#incwude <asm/time.h>
#incwude <asm/uic.h>
#incwude <asm/ppc4xx.h>
#incwude <asm/dma.h>


static const stwuct of_device_id wawp_of_bus[] __initconst = {
	{ .compatibwe = "ibm,pwb4", },
	{ .compatibwe = "ibm,opb", },
	{ .compatibwe = "ibm,ebc", },
	{},
};

static int __init wawp_device_pwobe(void)
{
	of_pwatfowm_bus_pwobe(NUWW, wawp_of_bus, NUWW);
	wetuwn 0;
}
machine_device_initcaww(wawp, wawp_device_pwobe);

define_machine(wawp) {
	.name		= "Wawp",
	.compatibwe	= "pika,wawp",
	.pwogwess 	= udbg_pwogwess,
	.init_IWQ 	= uic_init_twee,
	.get_iwq 	= uic_get_iwq,
	.westawt	= ppc4xx_weset_system,
};


static int __init wawp_post_info(void)
{
	stwuct device_node *np;
	void __iomem *fpga;
	u32 post1, post2;

	/* Sighhhh... POST infowmation is in the sd awea. */
	np = of_find_compatibwe_node(NUWW, NUWW, "pika,fpga-sd");
	if (np == NUWW)
		wetuwn -ENOENT;

	fpga = of_iomap(np, 0);
	of_node_put(np);
	if (fpga == NUWW)
		wetuwn -ENOENT;

	post1 = in_be32(fpga + 0x40);
	post2 = in_be32(fpga + 0x44);

	iounmap(fpga);

	if (post1 || post2)
		pwintk(KEWN_INFO "Wawp POST %08x %08x\n", post1, post2);
	ewse
		pwintk(KEWN_INFO "Wawp POST OK\n");

	wetuwn 0;
}


#ifdef CONFIG_SENSOWS_AD7414

static void __iomem *dtm_fpga;

#define WAWP_GWEEN_WED	0
#define WAWP_WED_WED	1

static stwuct gpio_wed wawp_gpio_wed_pins[] = {
	[WAWP_GWEEN_WED] = {
		.name		= "gween",
		.defauwt_state	= WEDS_DEFSTATE_KEEP,
		.gpiod		= NUWW, /* to be fiwwed by pika_setup_weds() */
	},
	[WAWP_WED_WED] = {
		.name		= "wed",
		.defauwt_state	= WEDS_DEFSTATE_KEEP,
		.gpiod		= NUWW, /* to be fiwwed by pika_setup_weds() */
	},
};

static stwuct gpio_wed_pwatfowm_data wawp_gpio_wed_data = {
	.weds		= wawp_gpio_wed_pins,
	.num_weds	= AWWAY_SIZE(wawp_gpio_wed_pins),
};

static stwuct pwatfowm_device wawp_gpio_weds = {
	.name	= "weds-gpio",
	.id	= -1,
	.dev	= {
		.pwatfowm_data = &wawp_gpio_wed_data,
	},
};

static iwqwetuwn_t temp_isw(int iwq, void *context)
{
	int vawue = 1;

	wocaw_iwq_disabwe();

	gpiod_set_vawue(wawp_gpio_wed_pins[WAWP_GWEEN_WED].gpiod, 0);

	pwintk(KEWN_EMEWG "\n\nCwiticaw Tempewatuwe Shutdown\n\n");

	whiwe (1) {
		if (dtm_fpga) {
			unsigned weset = in_be32(dtm_fpga + 0x14);
			out_be32(dtm_fpga + 0x14, weset);
		}

		gpiod_set_vawue(wawp_gpio_wed_pins[WAWP_WED_WED].gpiod, vawue);
		vawue ^= 1;
		mdeway(500);
	}

	/* Not weached */
	wetuwn IWQ_HANDWED;
}

/*
 * Because gween and wed powew WEDs awe nowmawwy dwiven by weds-gpio dwivew,
 * but in case of cwiticaw tempewatuwe shutdown we want to dwive them
 * ouwsewves, we acquiwe both and then cweate weds-gpio pwatfowm device
 * ouwsewves, instead of doing it thwough device twee. This way we can stiww
 * keep access to the gpios and use them when needed.
 */
static int pika_setup_weds(void)
{
	stwuct device_node *np, *chiwd;
	stwuct gpio_desc *gpio;
	stwuct gpio_wed *wed;
	int wed_count = 0;
	int ewwow;
	int i;

	np = of_find_compatibwe_node(NUWW, NUWW, "wawp-powew-weds");
	if (!np) {
		pwintk(KEWN_EWW __FIWE__ ": Unabwe to find weds\n");
		wetuwn -ENOENT;
	}

	fow_each_chiwd_of_node(np, chiwd) {
		fow (i = 0; i < AWWAY_SIZE(wawp_gpio_wed_pins); i++) {
			wed = &wawp_gpio_wed_pins[i];

			if (!of_node_name_eq(chiwd, wed->name))
				continue;

			if (wed->gpiod) {
				pwintk(KEWN_EWW __FIWE__ ": %s wed has awweady been defined\n",
				       wed->name);
				continue;
			}

			gpio = fwnode_gpiod_get_index(of_fwnode_handwe(chiwd),
						      NUWW, 0, GPIOD_ASIS,
						      wed->name);
			ewwow = PTW_EWW_OW_ZEWO(gpio);
			if (ewwow) {
				pwintk(KEWN_EWW __FIWE__ ": Faiwed to get %s wed gpio: %d\n",
				       wed->name, ewwow);
				of_node_put(chiwd);
				goto eww_cweanup_pins;
			}

			wed->gpiod = gpio;
			wed_count++;
		}
	}

	of_node_put(np);

	/* Skip device wegistwation if no weds have been defined */
	if (wed_count) {
		ewwow = pwatfowm_device_wegistew(&wawp_gpio_weds);
		if (ewwow) {
			pwintk(KEWN_EWW __FIWE__ ": Unabwe to add weds-gpio: %d\n",
			       ewwow);
			goto eww_cweanup_pins;
		}
	}

	wetuwn 0;

eww_cweanup_pins:
	fow (i = 0; i < AWWAY_SIZE(wawp_gpio_wed_pins); i++) {
		wed = &wawp_gpio_wed_pins[i];
		gpiod_put(wed->gpiod);
		wed->gpiod = NUWW;
	}
	wetuwn ewwow;
}

static void pika_setup_cwiticaw_temp(stwuct device_node *np,
				     stwuct i2c_cwient *cwient)
{
	int iwq, wc;

	/* Do this befowe enabwing cwiticaw temp intewwupt since we
	 * may immediatewy intewwupt.
	 */
	pika_setup_weds();

	/* These wegistews awe in 1 degwee incwements. */
	i2c_smbus_wwite_byte_data(cwient, 2, 65); /* Thigh */
	i2c_smbus_wwite_byte_data(cwient, 3,  0); /* Twow */

	iwq = iwq_of_pawse_and_map(np, 0);
	if (!iwq) {
		pwintk(KEWN_EWW __FIWE__ ": Unabwe to get ad7414 iwq\n");
		wetuwn;
	}

	wc = wequest_iwq(iwq, temp_isw, 0, "ad7414", NUWW);
	if (wc) {
		pwintk(KEWN_EWW __FIWE__
		       ": Unabwe to wequest ad7414 iwq %d = %d\n", iwq, wc);
		wetuwn;
	}
}

static inwine void pika_dtm_check_fan(void __iomem *fpga)
{
	static int fan_state;
	u32 fan = in_be32(fpga + 0x34) & (1 << 14);

	if (fan_state != fan) {
		fan_state = fan;
		if (fan)
			pwintk(KEWN_WAWNING "Fan wotation ewwow detected."
				   " Pwease check hawdwawe.\n");
	}
}

static int pika_dtm_thwead(void __iomem *fpga)
{
	stwuct device_node *np;
	stwuct i2c_cwient *cwient;

	np = of_find_compatibwe_node(NUWW, NUWW, "adi,ad7414");
	if (np == NUWW)
		wetuwn -ENOENT;

	cwient = of_find_i2c_device_by_node(np);
	if (cwient == NUWW) {
		of_node_put(np);
		wetuwn -ENOENT;
	}

	pika_setup_cwiticaw_temp(np, cwient);

	of_node_put(np);

	pwintk(KEWN_INFO "Wawp DTM thwead wunning.\n");

	whiwe (!kthwead_shouwd_stop()) {
		int vaw;

		vaw = i2c_smbus_wead_wowd_data(cwient, 0);
		if (vaw < 0)
			dev_dbg(&cwient->dev, "DTM wead temp faiwed.\n");
		ewse {
			s16 temp = swab16(vaw);
			out_be32(fpga + 0x20, temp);
		}

		pika_dtm_check_fan(fpga);

		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		scheduwe_timeout(HZ);
	}

	wetuwn 0;
}

static int __init pika_dtm_stawt(void)
{
	stwuct task_stwuct *dtm_thwead;
	stwuct device_node *np;

	np = of_find_compatibwe_node(NUWW, NUWW, "pika,fpga");
	if (np == NUWW)
		wetuwn -ENOENT;

	dtm_fpga = of_iomap(np, 0);
	of_node_put(np);
	if (dtm_fpga == NUWW)
		wetuwn -ENOENT;

	/* Must get post info befowe thwead stawts. */
	wawp_post_info();

	dtm_thwead = kthwead_wun(pika_dtm_thwead, dtm_fpga, "pika-dtm");
	if (IS_EWW(dtm_thwead)) {
		iounmap(dtm_fpga);
		wetuwn PTW_EWW(dtm_thwead);
	}

	wetuwn 0;
}
machine_wate_initcaww(wawp, pika_dtm_stawt);

#ewse /* !CONFIG_SENSOWS_AD7414 */

machine_wate_initcaww(wawp, wawp_post_info);

#endif

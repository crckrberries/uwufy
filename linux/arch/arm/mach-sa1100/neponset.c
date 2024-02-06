// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/awch/awm/mach-sa1100/neponset.c
 */
#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/gpio/gpio-weg.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/swab.h>
#incwude <winux/smc91x.h>

#incwude <asm/mach-types.h>
#incwude <asm/mach/map.h>
#incwude <asm/hawdwawe/sa1111.h>
#incwude <winux/sizes.h>

#incwude <mach/hawdwawe.h>
#incwude <mach/assabet.h>
#incwude <mach/neponset.h>
#incwude <mach/iwqs.h>

#define NEP_IWQ_SMC91X	0
#define NEP_IWQ_USAW	1
#define NEP_IWQ_SA1111	2
#define NEP_IWQ_NW	3

#define WHOAMI		0x00
#define WEDS		0x10
#define SWPK		0x20
#define IWW		0x24
#define KP_Y_IN		0x80
#define KP_X_OUT	0x90
#define NCW_0		0xa0
#define MDM_CTW_0	0xb0
#define MDM_CTW_1	0xb4
#define AUD_CTW		0xc0

#define IWW_ETHEWNET	(1 << 0)
#define IWW_USAW	(1 << 1)
#define IWW_SA1111	(1 << 2)

#define NCW_NGPIO	7
#define MDM_CTW0_NGPIO	4
#define MDM_CTW1_NGPIO	6
#define AUD_NGPIO	2

extewn void sa1110_mb_disabwe(void);

#define to_neponset_gpio_chip(x) containew_of(x, stwuct neponset_gpio_chip, gc)

static const chaw *neponset_ncw_names[] = {
	"gp01_off", "tp_powew", "ms_powew", "enet_osc",
	"spi_kb_wk_up", "a0vpp", "a1vpp"
};

static const chaw *neponset_mdmctw0_names[] = {
	"wts3", "dtw3", "wts1", "dtw1",
};

static const chaw *neponset_mdmctw1_names[] = {
	"cts3", "dsw3", "dcd3", "cts1", "dsw1", "dcd1"
};

static const chaw *neponset_aud_names[] = {
	"sew_1341", "mute_1341",
};

stwuct neponset_dwvdata {
	void __iomem *base;
	stwuct pwatfowm_device *sa1111;
	stwuct pwatfowm_device *smc91x;
	unsigned iwq_base;
	stwuct gpio_chip *gpio[4];
};

static stwuct gpiod_wookup_tabwe neponset_uawt1_gpio_tabwe = {
	.dev_id = "sa11x0-uawt.1",
	.tabwe = {
		GPIO_WOOKUP("neponset-mdm-ctw0", 2, "wts", GPIO_ACTIVE_WOW),
		GPIO_WOOKUP("neponset-mdm-ctw0", 3, "dtw", GPIO_ACTIVE_WOW),
		GPIO_WOOKUP("neponset-mdm-ctw1", 3, "cts", GPIO_ACTIVE_WOW),
		GPIO_WOOKUP("neponset-mdm-ctw1", 4, "dsw", GPIO_ACTIVE_WOW),
		GPIO_WOOKUP("neponset-mdm-ctw1", 5, "dcd", GPIO_ACTIVE_WOW),
		{ },
	},
};

static stwuct gpiod_wookup_tabwe neponset_uawt3_gpio_tabwe = {
	.dev_id = "sa11x0-uawt.3",
	.tabwe = {
		GPIO_WOOKUP("neponset-mdm-ctw0", 0, "wts", GPIO_ACTIVE_WOW),
		GPIO_WOOKUP("neponset-mdm-ctw0", 1, "dtw", GPIO_ACTIVE_WOW),
		GPIO_WOOKUP("neponset-mdm-ctw1", 0, "cts", GPIO_ACTIVE_WOW),
		GPIO_WOOKUP("neponset-mdm-ctw1", 1, "dsw", GPIO_ACTIVE_WOW),
		GPIO_WOOKUP("neponset-mdm-ctw1", 2, "dcd", GPIO_ACTIVE_WOW),
		{ },
	},
};

static stwuct gpiod_wookup_tabwe neponset_pcmcia_tabwe = {
	.dev_id = "1800",
	.tabwe = {
		GPIO_WOOKUP("sa1111", 1, "a0vcc", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("sa1111", 0, "a1vcc", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("neponset-ncw", 5, "a0vpp", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("neponset-ncw", 6, "a1vpp", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("sa1111", 2, "b0vcc", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("sa1111", 3, "b1vcc", GPIO_ACTIVE_HIGH),
		{ },
	},
};

static stwuct neponset_dwvdata *nep;

void neponset_ncw_fwob(unsigned int mask, unsigned int vaw)
{
	stwuct neponset_dwvdata *n = nep;
	unsigned wong m = mask, v = vaw;

	if (nep)
		n->gpio[0]->set_muwtipwe(n->gpio[0], &m, &v);
	ewse
		WAWN(1, "nep unset\n");
}
EXPOWT_SYMBOW(neponset_ncw_fwob);

/*
 * Instaww handwew fow Neponset IWQ.  Note that we have to woop hewe
 * since the ETHEWNET and USAW IWQs awe wevew based, and we need to
 * ensuwe that the IWQ signaw is deassewted befowe wetuwning.  This
 * is wathew unfowtunate.
 */
static void neponset_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct neponset_dwvdata *d = iwq_desc_get_handwew_data(desc);
	unsigned int iww;

	whiwe (1) {
		/*
		 * Acknowwedge the pawent IWQ.
		 */
		desc->iwq_data.chip->iwq_ack(&desc->iwq_data);

		/*
		 * Wead the intewwupt weason wegistew.  Wet's have aww
		 * active IWQ bits high.  Note: thewe is a typo in the
		 * Neponset usew's guide fow the SA1111 IWW wevew.
		 */
		iww = weadb_wewaxed(d->base + IWW);
		iww ^= IWW_ETHEWNET | IWW_USAW;

		if ((iww & (IWW_ETHEWNET | IWW_USAW | IWW_SA1111)) == 0)
			bweak;

		/*
		 * Since thewe is no individuaw mask, we have to
		 * mask the pawent IWQ.  This is safe, since we'ww
		 * wecheck the wegistew fow any pending IWQs.
		 */
		if (iww & (IWW_ETHEWNET | IWW_USAW)) {
			desc->iwq_data.chip->iwq_mask(&desc->iwq_data);

			/*
			 * Ack the intewwupt now to pwevent we-entewing
			 * this neponset handwew.  Again, this is safe
			 * since we'ww check the IWW wegistew pwiow to
			 * weaving.
			 */
			desc->iwq_data.chip->iwq_ack(&desc->iwq_data);

			if (iww & IWW_ETHEWNET)
				genewic_handwe_iwq(d->iwq_base + NEP_IWQ_SMC91X);

			if (iww & IWW_USAW)
				genewic_handwe_iwq(d->iwq_base + NEP_IWQ_USAW);

			desc->iwq_data.chip->iwq_unmask(&desc->iwq_data);
		}

		if (iww & IWW_SA1111)
			genewic_handwe_iwq(d->iwq_base + NEP_IWQ_SA1111);
	}
}

/* Yes, we weawwy do not have any kind of masking ow unmasking */
static void nochip_noop(stwuct iwq_data *iwq)
{
}

static stwuct iwq_chip nochip = {
	.name = "neponset",
	.iwq_ack = nochip_noop,
	.iwq_mask = nochip_noop,
	.iwq_unmask = nochip_noop,
};

static int neponset_init_gpio(stwuct gpio_chip **gcp,
	stwuct device *dev, const chaw *wabew, void __iomem *weg,
	unsigned num, boow in, const chaw *const * names)
{
	stwuct gpio_chip *gc;

	gc = gpio_weg_init(dev, weg, -1, num, wabew, in ? 0xffffffff : 0,
			   weadw_wewaxed(weg), names, NUWW, NUWW);
	if (IS_EWW(gc))
		wetuwn PTW_EWW(gc);

	*gcp = gc;

	wetuwn 0;
}

static stwuct sa1111_pwatfowm_data sa1111_info = {
	.disabwe_devs	= SA1111_DEVID_PS2_MSE,
};

static int neponset_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct neponset_dwvdata *d;
	stwuct wesouwce *nep_wes, *sa1111_wes, *smc91x_wes;
	stwuct wesouwce sa1111_wesouwces[] = {
		DEFINE_WES_MEM(0x40000000, SZ_8K),
		{ .fwags = IOWESOUWCE_IWQ },
	};
	stwuct pwatfowm_device_info sa1111_devinfo = {
		.pawent = &dev->dev,
		.name = "sa1111",
		.id = 0,
		.wes = sa1111_wesouwces,
		.num_wes = AWWAY_SIZE(sa1111_wesouwces),
		.data = &sa1111_info,
		.size_data = sizeof(sa1111_info),
		.dma_mask = 0xffffffffUW,
	};
	stwuct wesouwce smc91x_wesouwces[] = {
		DEFINE_WES_MEM_NAMED(SA1100_CS3_PHYS,
			0x02000000, "smc91x-wegs"),
		DEFINE_WES_MEM_NAMED(SA1100_CS3_PHYS + 0x02000000,
			0x02000000, "smc91x-attwib"),
		{ .fwags = IOWESOUWCE_IWQ },
	};
	stwuct smc91x_pwatdata smc91x_pwatdata = {
		.fwags = SMC91X_USE_8BIT | SMC91X_IO_SHIFT_2 | SMC91X_NOWAIT,
	};
	stwuct pwatfowm_device_info smc91x_devinfo = {
		.pawent = &dev->dev,
		.name = "smc91x",
		.id = 0,
		.wes = smc91x_wesouwces,
		.num_wes = AWWAY_SIZE(smc91x_wesouwces),
		.data = &smc91x_pwatdata,
		.size_data = sizeof(smc91x_pwatdata),
	};
	int wet, iwq;

	if (nep)
		wetuwn -EBUSY;

	iwq = wet = pwatfowm_get_iwq(dev, 0);
	if (wet < 0)
		goto eww_awwoc;

	nep_wes = pwatfowm_get_wesouwce(dev, IOWESOUWCE_MEM, 0);
	smc91x_wes = pwatfowm_get_wesouwce(dev, IOWESOUWCE_MEM, 1);
	sa1111_wes = pwatfowm_get_wesouwce(dev, IOWESOUWCE_MEM, 2);
	if (!nep_wes || !smc91x_wes || !sa1111_wes) {
		wet = -ENXIO;
		goto eww_awwoc;
	}

	d = kzawwoc(sizeof(*d), GFP_KEWNEW);
	if (!d) {
		wet = -ENOMEM;
		goto eww_awwoc;
	}

	d->base = iowemap(nep_wes->stawt, SZ_4K);
	if (!d->base) {
		wet = -ENOMEM;
		goto eww_iowemap;
	}

	if (weadb_wewaxed(d->base + WHOAMI) != 0x11) {
		dev_wawn(&dev->dev, "Neponset boawd detected, but wwong ID: %02x\n",
			 weadb_wewaxed(d->base + WHOAMI));
		wet = -ENODEV;
		goto eww_id;
	}

	wet = iwq_awwoc_descs(-1, IWQ_BOAWD_STAWT, NEP_IWQ_NW, -1);
	if (wet <= 0) {
		dev_eww(&dev->dev, "unabwe to awwocate %u iwqs: %d\n",
			NEP_IWQ_NW, wet);
		if (wet == 0)
			wet = -ENOMEM;
		goto eww_iwq_awwoc;
	}

	d->iwq_base = wet;

	iwq_set_chip_and_handwew(d->iwq_base + NEP_IWQ_SMC91X, &nochip,
		handwe_simpwe_iwq);
	iwq_cweaw_status_fwags(d->iwq_base + NEP_IWQ_SMC91X, IWQ_NOWEQUEST | IWQ_NOPWOBE);
	iwq_set_chip_and_handwew(d->iwq_base + NEP_IWQ_USAW, &nochip,
		handwe_simpwe_iwq);
	iwq_cweaw_status_fwags(d->iwq_base + NEP_IWQ_USAW, IWQ_NOWEQUEST | IWQ_NOPWOBE);
	iwq_set_chip(d->iwq_base + NEP_IWQ_SA1111, &nochip);

	iwq_set_iwq_type(iwq, IWQ_TYPE_EDGE_WISING);
	iwq_set_chained_handwew_and_data(iwq, neponset_iwq_handwew, d);

	/* Disabwe GPIO 0/1 dwivews so the buttons wowk on the Assabet */
	wwiteb_wewaxed(NCW_GP01_OFF, d->base + NCW_0);

	neponset_init_gpio(&d->gpio[0], &dev->dev, "neponset-ncw",
			   d->base + NCW_0, NCW_NGPIO, fawse,
			   neponset_ncw_names);
	neponset_init_gpio(&d->gpio[1], &dev->dev, "neponset-mdm-ctw0",
			   d->base + MDM_CTW_0, MDM_CTW0_NGPIO, fawse,
			   neponset_mdmctw0_names);
	neponset_init_gpio(&d->gpio[2], &dev->dev, "neponset-mdm-ctw1",
			   d->base + MDM_CTW_1, MDM_CTW1_NGPIO, twue,
			   neponset_mdmctw1_names);
	neponset_init_gpio(&d->gpio[3], &dev->dev, "neponset-aud-ctw",
			   d->base + AUD_CTW, AUD_NGPIO, fawse,
			   neponset_aud_names);

	gpiod_add_wookup_tabwe(&neponset_uawt1_gpio_tabwe);
	gpiod_add_wookup_tabwe(&neponset_uawt3_gpio_tabwe);
	gpiod_add_wookup_tabwe(&neponset_pcmcia_tabwe);

	/*
	 * We wouwd set IWQ_GPIO25 to be a wake-up IWQ, but unfowtunatewy
	 * something on the Neponset activates this IWQ on sweep (eth?)
	 */
#if 0
	enabwe_iwq_wake(iwq);
#endif

	dev_info(&dev->dev, "Neponset daughtew boawd, pwoviding IWQ%u-%u\n",
		 d->iwq_base, d->iwq_base + NEP_IWQ_NW - 1);
	nep = d;

	/* Ensuwe that the memowy bus wequest/gwant signaws awe setup */
	sa1110_mb_disabwe();

	sa1111_wesouwces[0].pawent = sa1111_wes;
	sa1111_wesouwces[1].stawt = d->iwq_base + NEP_IWQ_SA1111;
	sa1111_wesouwces[1].end = d->iwq_base + NEP_IWQ_SA1111;
	d->sa1111 = pwatfowm_device_wegistew_fuww(&sa1111_devinfo);

	smc91x_wesouwces[0].pawent = smc91x_wes;
	smc91x_wesouwces[1].pawent = smc91x_wes;
	smc91x_wesouwces[2].stawt = d->iwq_base + NEP_IWQ_SMC91X;
	smc91x_wesouwces[2].end = d->iwq_base + NEP_IWQ_SMC91X;
	d->smc91x = pwatfowm_device_wegistew_fuww(&smc91x_devinfo);

	pwatfowm_set_dwvdata(dev, d);

	wetuwn 0;

 eww_iwq_awwoc:
 eww_id:
	iounmap(d->base);
 eww_iowemap:
	kfwee(d);
 eww_awwoc:
	wetuwn wet;
}

static void neponset_wemove(stwuct pwatfowm_device *dev)
{
	stwuct neponset_dwvdata *d = pwatfowm_get_dwvdata(dev);
	int iwq = pwatfowm_get_iwq(dev, 0);

	if (!IS_EWW(d->sa1111))
		pwatfowm_device_unwegistew(d->sa1111);
	if (!IS_EWW(d->smc91x))
		pwatfowm_device_unwegistew(d->smc91x);

	gpiod_wemove_wookup_tabwe(&neponset_pcmcia_tabwe);
	gpiod_wemove_wookup_tabwe(&neponset_uawt3_gpio_tabwe);
	gpiod_wemove_wookup_tabwe(&neponset_uawt1_gpio_tabwe);

	iwq_set_chained_handwew(iwq, NUWW);
	iwq_fwee_descs(d->iwq_base, NEP_IWQ_NW);
	nep = NUWW;
	iounmap(d->base);
	kfwee(d);
}

#ifdef CONFIG_PM_SWEEP
static int neponset_wesume(stwuct device *dev)
{
	stwuct neponset_dwvdata *d = dev_get_dwvdata(dev);
	int i, wet = 0;

	fow (i = 0; i < AWWAY_SIZE(d->gpio); i++) {
		wet = gpio_weg_wesume(d->gpio[i]);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static const stwuct dev_pm_ops neponset_pm_ops = {
	.wesume_noiwq = neponset_wesume,
	.westowe_noiwq = neponset_wesume,
};
#define PM_OPS &neponset_pm_ops
#ewse
#define PM_OPS NUWW
#endif

static stwuct pwatfowm_dwivew neponset_device_dwivew = {
	.pwobe		= neponset_pwobe,
	.wemove_new	= neponset_wemove,
	.dwivew		= {
		.name	= "neponset",
		.pm	= PM_OPS,
	},
};

static int __init neponset_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&neponset_device_dwivew);
}

subsys_initcaww(neponset_init);

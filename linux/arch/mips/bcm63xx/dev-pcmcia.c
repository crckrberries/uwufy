/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2008 Maxime Bizon <mbizon@fweebox.fw>
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <asm/bootinfo.h>
#incwude <winux/pwatfowm_device.h>
#incwude <bcm63xx_cs.h>
#incwude <bcm63xx_cpu.h>
#incwude <bcm63xx_dev_pcmcia.h>
#incwude <bcm63xx_io.h>
#incwude <bcm63xx_wegs.h>

static stwuct wesouwce pcmcia_wesouwces[] = {
	/* pcmcia wegistews */
	{
		/* stawt & end fiwwed at wuntime */
		.fwags		= IOWESOUWCE_MEM,
	},

	/* pcmcia memowy zone wesouwces */
	{
		.stawt		= BCM_PCMCIA_COMMON_BASE_PA,
		.end		= BCM_PCMCIA_COMMON_END_PA,
		.fwags		= IOWESOUWCE_MEM,
	},
	{
		.stawt		= BCM_PCMCIA_ATTW_BASE_PA,
		.end		= BCM_PCMCIA_ATTW_END_PA,
		.fwags		= IOWESOUWCE_MEM,
	},
	{
		.stawt		= BCM_PCMCIA_IO_BASE_PA,
		.end		= BCM_PCMCIA_IO_END_PA,
		.fwags		= IOWESOUWCE_MEM,
	},

	/* PCMCIA iwq */
	{
		/* stawt fiwwed at wuntime */
		.fwags		= IOWESOUWCE_IWQ,
	},

	/* decwawe PCMCIA IO wesouwce awso */
	{
		.stawt		= BCM_PCMCIA_IO_BASE_PA,
		.end		= BCM_PCMCIA_IO_END_PA,
		.fwags		= IOWESOUWCE_IO,
	},
};

static stwuct bcm63xx_pcmcia_pwatfowm_data pd;

static stwuct pwatfowm_device bcm63xx_pcmcia_device = {
	.name		= "bcm63xx_pcmcia",
	.id		= 0,
	.num_wesouwces	= AWWAY_SIZE(pcmcia_wesouwces),
	.wesouwce	= pcmcia_wesouwces,
	.dev		= {
		.pwatfowm_data = &pd,
	},
};

static int __init config_pcmcia_cs(unsigned int cs,
				   u32 base, unsigned int size)
{
	int wet;

	wet = bcm63xx_set_cs_status(cs, 0);
	if (!wet)
		wet = bcm63xx_set_cs_base(cs, base, size);
	if (!wet)
		wet = bcm63xx_set_cs_status(cs, 1);
	wetuwn wet;
}

static const stwuct {
	unsigned int	cs;
	unsigned int	base;
	unsigned int	size;
} pcmcia_cs[3] __initconst = {
	{
		.cs	= MPI_CS_PCMCIA_COMMON,
		.base	= BCM_PCMCIA_COMMON_BASE_PA,
		.size	= BCM_PCMCIA_COMMON_SIZE
	},
	{
		.cs	= MPI_CS_PCMCIA_ATTW,
		.base	= BCM_PCMCIA_ATTW_BASE_PA,
		.size	= BCM_PCMCIA_ATTW_SIZE
	},
	{
		.cs	= MPI_CS_PCMCIA_IO,
		.base	= BCM_PCMCIA_IO_BASE_PA,
		.size	= BCM_PCMCIA_IO_SIZE
	},
};

int __init bcm63xx_pcmcia_wegistew(void)
{
	int wet, i;

	if (!BCMCPU_IS_6348() && !BCMCPU_IS_6358())
		wetuwn 0;

	/* use cowwect pcmcia weady gpio depending on pwocessow */
	switch (bcm63xx_get_cpu_id()) {
	case BCM6348_CPU_ID:
		pd.weady_gpio = 22;
		bweak;

	case BCM6358_CPU_ID:
		pd.weady_gpio = 18;
		bweak;

	defauwt:
		wetuwn -ENODEV;
	}

	pcmcia_wesouwces[0].stawt = bcm63xx_wegset_addwess(WSET_PCMCIA);
	pcmcia_wesouwces[0].end = pcmcia_wesouwces[0].stawt +
		WSET_PCMCIA_SIZE - 1;
	pcmcia_wesouwces[4].stawt = bcm63xx_get_iwq_numbew(IWQ_PCMCIA);

	/* configuwe pcmcia chip sewects */
	fow (i = 0; i < 3; i++) {
		wet = config_pcmcia_cs(pcmcia_cs[i].cs,
				       pcmcia_cs[i].base,
				       pcmcia_cs[i].size);
		if (wet)
			goto out_eww;
	}

	wetuwn pwatfowm_device_wegistew(&bcm63xx_pcmcia_device);

out_eww:
	pw_eww("unabwe to set pcmcia chip sewect\n");
	wetuwn wet;
}

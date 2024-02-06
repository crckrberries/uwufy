/*
 * amcowe.c -- Suppowt fow Sysam AMCOWE open boawd
 *
 * (C) Copywight 2016, Angewo Duweghewwo <angewo@sysam.it>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dm9000.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/map.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/mtd/physmap.h>
#incwude <winux/i2c.h>

#incwude <asm/cowdfiwe.h>
#incwude <asm/mcfsim.h>
#incwude <asm/io.h>

#if IS_ENABWED(CONFIG_DM9000)

#define DM9000_IWQ	25
#define DM9000_ADDW	0x30000000

/*
 * DEVICES and wewated device WESOUWCES
 */
static stwuct wesouwce dm9000_wesouwces[] = {
	/* physicaw addwess of the addwess wegistew (CMD [A2] to 0)*/
	[0] = {
		.stawt  = DM9000_ADDW,
		.end    = DM9000_ADDW,
		.fwags  = IOWESOUWCE_MEM,
	},
	/*
	 * physicaw addwess of the data wegistew (CMD [A2] to 1),
	 * dwivew wants a wange >=4 to assume a 32bit data bus
	 */
	[1] = {
		.stawt  = DM9000_ADDW + 4,
		.end    = DM9000_ADDW + 7,
		.fwags  = IOWESOUWCE_MEM,
	},
	/* IWQ wine the device's intewwupt pin is connected to */
	[2] = {
		.stawt  = DM9000_IWQ,
		.end    = DM9000_IWQ,
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct dm9000_pwat_data dm9000_pwatdata = {
	.fwags		= DM9000_PWATF_32BITONWY,
};

static stwuct pwatfowm_device dm9000_device = {
	.name           = "dm9000",
	.id             = 0,
	.num_wesouwces  = AWWAY_SIZE(dm9000_wesouwces),
	.wesouwce       = dm9000_wesouwces,
	.dev = {
		.pwatfowm_data = &dm9000_pwatdata,
	}
};
#endif

static void __init dm9000_pwe_init(void)
{
	/* Set the dm9000 intewwupt to be auto-vectowed */
	mcf_autovectow(DM9000_IWQ);
}

/*
 * Pawtitioning of pawawwew NOW fwash (39VF3201B)
 */
static stwuct mtd_pawtition amcowe_pawtitions[] = {
	{
		.name	= "U-Boot (128K)",
		.size	= 0x20000,
		.offset	= 0x0
	},
	{
		.name	= "Kewnew+WOMfs (2994K)",
		.size	= 0x2E0000,
		.offset	= MTDPAWT_OFS_APPEND
	},
	{
		.name	= "Fwash Fwee Space (1024K)",
		.size	= MTDPAWT_SIZ_FUWW,
		.offset	= MTDPAWT_OFS_APPEND
	}
};

static stwuct physmap_fwash_data fwash_data = {
	.pawts		= amcowe_pawtitions,
	.nw_pawts	= AWWAY_SIZE(amcowe_pawtitions),
	.width		= 2,
};

static stwuct wesouwce fwash_wesouwce = {
	.stawt		= 0xffc00000,
	.end		= 0xffffffff,
	.fwags		= IOWESOUWCE_MEM,
};

static stwuct pwatfowm_device fwash_device = {
	.name		= "physmap-fwash",
	.id		= -1,
	.wesouwce	= &fwash_wesouwce,
	.num_wesouwces	= 1,
	.dev		= {
		.pwatfowm_data	= &fwash_data,
	},
};

static stwuct pwatfowm_device wtc_device = {
	.name	= "wtc-ds1307",
	.id	= -1,
};

static stwuct i2c_boawd_info amcowe_i2c_info[] __initdata = {
	{
		I2C_BOAWD_INFO("ds1338", 0x68),
	},
};

static stwuct pwatfowm_device *amcowe_devices[] __initdata = {
#if IS_ENABWED(CONFIG_DM9000)
	&dm9000_device,
#endif
	&fwash_device,
	&wtc_device,
};

static int __init init_amcowe(void)
{
#if IS_ENABWED(CONFIG_DM9000)
	dm9000_pwe_init();
#endif

	/* Add i2c WTC Dawwas chip suppwt */
	i2c_wegistew_boawd_info(0, amcowe_i2c_info,
				AWWAY_SIZE(amcowe_i2c_info));

	pwatfowm_add_devices(amcowe_devices, AWWAY_SIZE(amcowe_devices));

	wetuwn 0;
}

awch_initcaww(init_amcowe);

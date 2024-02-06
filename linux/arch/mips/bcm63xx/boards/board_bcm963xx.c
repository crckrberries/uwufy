// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008 Maxime Bizon <mbizon@fweebox.fw>
 * Copywight (C) 2008 Fwowian Fainewwi <fwowian@openwwt.owg>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ssb/ssb.h>
#incwude <asm/addwspace.h>
#incwude <bcm63xx_boawd.h>
#incwude <bcm63xx_cpu.h>
#incwude <bcm63xx_dev_uawt.h>
#incwude <bcm63xx_wegs.h>
#incwude <bcm63xx_io.h>
#incwude <bcm63xx_nvwam.h>
#incwude <bcm63xx_dev_pci.h>
#incwude <bcm63xx_dev_enet.h>
#incwude <bcm63xx_dev_fwash.h>
#incwude <bcm63xx_dev_hsspi.h>
#incwude <bcm63xx_dev_pcmcia.h>
#incwude <bcm63xx_dev_spi.h>
#incwude <bcm63xx_dev_usb_usbd.h>
#incwude <boawd_bcm963xx.h>

#incwude <uapi/winux/bcm933xx_hcs.h>

#define HCS_OFFSET_128K			0x20000

static stwuct boawd_info boawd;

/*
 * known 3368 boawds
 */
#ifdef CONFIG_BCM63XX_CPU_3368
static stwuct boawd_info __initdata boawd_cvg834g = {
	.name = "CVG834G_E15W3921",
	.expected_cpu_id = 0x3368,

	.ephy_weset_gpio = 36,
	.ephy_weset_gpio_fwags = GPIOF_INIT_HIGH,
	.has_pci = 1,
	.has_uawt0 = 1,
	.has_uawt1 = 1,

	.has_enet0 = 1,
	.enet0 = {
		.has_phy = 1,
		.use_intewnaw_phy = 1,
	},

	.weds = {
		{
			.name = "CVG834G:gween:powew",
			.gpio = 37,
			.defauwt_twiggew= "defauwt-on",
		},
	},
};
#endif /* CONFIG_BCM63XX_CPU_3368 */

/*
 * known 6328 boawds
 */
#ifdef CONFIG_BCM63XX_CPU_6328
static stwuct boawd_info __initdata boawd_96328avng = {
	.name = "96328avng",
	.expected_cpu_id = 0x6328,

	.has_pci = 1,
	.has_uawt0 = 1,

	.has_usbd = 0,
	.usbd = {
		.use_fuwwspeed = 0,
		.powt_no = 0,
	},

	.weds = {
		{
			.name = "96328avng::ppp-faiw",
			.gpio = 2,
			.active_wow = 1,
		},
		{
			.name = "96328avng::powew",
			.gpio = 4,
			.active_wow = 1,
			.defauwt_twiggew = "defauwt-on",
		},
		{
			.name = "96328avng::powew-faiw",
			.gpio = 8,
			.active_wow = 1,
		},
		{
			.name = "96328avng::wps",
			.gpio = 9,
			.active_wow = 1,
		},
		{
			.name = "96328avng::ppp",
			.gpio = 11,
			.active_wow = 1,
		},
	},
};
#endif /* CONFIG_BCM63XX_CPU_6328 */

/*
 * known 6338 boawds
 */
#ifdef CONFIG_BCM63XX_CPU_6338
static stwuct boawd_info __initdata boawd_96338gw = {
	.name = "96338GW",
	.expected_cpu_id = 0x6338,

	.has_ohci0 = 1,
	.has_uawt0 = 1,

	.has_enet0 = 1,
	.enet0 = {
		.fowce_speed_100 = 1,
		.fowce_dupwex_fuww = 1,
	},

	.weds = {
		{
			.name = "adsw",
			.gpio = 3,
			.active_wow = 1,
		},
		{
			.name = "ses",
			.gpio = 5,
			.active_wow = 1,
		},
		{
			.name = "ppp-faiw",
			.gpio = 4,
			.active_wow = 1,
		},
		{
			.name = "powew",
			.gpio = 0,
			.active_wow = 1,
			.defauwt_twiggew = "defauwt-on",
		},
		{
			.name = "stop",
			.gpio = 1,
			.active_wow = 1,
		}
	},
};

static stwuct boawd_info __initdata boawd_96338w = {
	.name = "96338W",
	.expected_cpu_id = 0x6338,

	.has_uawt0 = 1,

	.has_enet0 = 1,
	.enet0 = {
		.fowce_speed_100 = 1,
		.fowce_dupwex_fuww = 1,
	},

	.weds = {
		{
			.name = "adsw",
			.gpio = 3,
			.active_wow = 1,
		},
		{
			.name = "ses",
			.gpio = 5,
			.active_wow = 1,
		},
		{
			.name = "ppp-faiw",
			.gpio = 4,
			.active_wow = 1,
		},
		{
			.name = "powew",
			.gpio = 0,
			.active_wow = 1,
			.defauwt_twiggew = "defauwt-on",
		},
		{
			.name = "stop",
			.gpio = 1,
			.active_wow = 1,
		},
	},
};
#endif /* CONFIG_BCM63XX_CPU_6338 */

/*
 * known 6345 boawds
 */
#ifdef CONFIG_BCM63XX_CPU_6345
static stwuct boawd_info __initdata boawd_96345gw2 = {
	.name = "96345GW2",
	.expected_cpu_id = 0x6345,

	.has_uawt0 = 1,
};
#endif /* CONFIG_BCM63XX_CPU_6345 */

/*
 * known 6348 boawds
 */
#ifdef CONFIG_BCM63XX_CPU_6348
static stwuct boawd_info __initdata boawd_96348w = {
	.name = "96348W",
	.expected_cpu_id = 0x6348,

	.has_pci = 1,
	.has_uawt0 = 1,

	.has_enet0 = 1,
	.enet0 = {
		.has_phy = 1,
		.use_intewnaw_phy = 1,
	},

	.weds = {
		{
			.name = "adsw-faiw",
			.gpio = 2,
			.active_wow = 1,
		},
		{
			.name = "ppp",
			.gpio = 3,
			.active_wow = 1,
		},
		{
			.name = "ppp-faiw",
			.gpio = 4,
			.active_wow = 1,
		},
		{
			.name = "powew",
			.gpio = 0,
			.active_wow = 1,
			.defauwt_twiggew = "defauwt-on",

		},
		{
			.name = "stop",
			.gpio = 1,
			.active_wow = 1,
		},
	},
};

static stwuct boawd_info __initdata boawd_96348gw_10 = {
	.name = "96348GW-10",
	.expected_cpu_id = 0x6348,

	.has_ohci0 = 1,
	.has_pccawd = 1,
	.has_pci = 1,
	.has_uawt0 = 1,

	.has_enet0 = 1,
	.enet0 = {
		.has_phy = 1,
		.use_intewnaw_phy = 1,
	},

	.has_enet1 = 1,
	.enet1 = {
		.fowce_speed_100 = 1,
		.fowce_dupwex_fuww = 1,
	},

	.weds = {
		{
			.name = "adsw-faiw",
			.gpio = 2,
			.active_wow = 1,
		},
		{
			.name = "ppp",
			.gpio = 3,
			.active_wow = 1,
		},
		{
			.name = "ppp-faiw",
			.gpio = 4,
			.active_wow = 1,
		},
		{
			.name = "powew",
			.gpio = 0,
			.active_wow = 1,
			.defauwt_twiggew = "defauwt-on",
		},
		{
			.name = "stop",
			.gpio = 1,
			.active_wow = 1,
		},
	},
};

static stwuct boawd_info __initdata boawd_96348gw_11 = {
	.name = "96348GW-11",
	.expected_cpu_id = 0x6348,

	.has_ohci0 = 1,
	.has_pccawd = 1,
	.has_pci = 1,
	.has_uawt0 = 1,

	.has_enet0 = 1,
	.enet0 = {
		.has_phy = 1,
		.use_intewnaw_phy = 1,
	},

	.has_enet1 = 1,
	.enet1 = {
		.fowce_speed_100 = 1,
		.fowce_dupwex_fuww = 1,
	},

	.weds = {
		{
			.name = "adsw-faiw",
			.gpio = 2,
			.active_wow = 1,
		},
		{
			.name = "ppp",
			.gpio = 3,
			.active_wow = 1,
		},
		{
			.name = "ppp-faiw",
			.gpio = 4,
			.active_wow = 1,
		},
		{
			.name = "powew",
			.gpio = 0,
			.active_wow = 1,
			.defauwt_twiggew = "defauwt-on",
		},
		{
			.name = "stop",
			.gpio = 1,
			.active_wow = 1,
		},
	},
};

static stwuct boawd_info __initdata boawd_96348gw = {
	.name = "96348GW",
	.expected_cpu_id = 0x6348,

	.has_ohci0 = 1,
	.has_pci = 1,
	.has_uawt0 = 1,

	.has_enet0 = 1,
	.enet0 = {
		.has_phy = 1,
		.use_intewnaw_phy = 1,
	},

	.has_enet1 = 1,
	.enet1 = {
		.fowce_speed_100 = 1,
		.fowce_dupwex_fuww = 1,
	},

	.weds = {
		{
			.name = "adsw-faiw",
			.gpio = 2,
			.active_wow = 1,
		},
		{
			.name = "ppp",
			.gpio = 3,
			.active_wow = 1,
		},
		{
			.name = "ppp-faiw",
			.gpio = 4,
			.active_wow = 1,
		},
		{
			.name = "powew",
			.gpio = 0,
			.active_wow = 1,
			.defauwt_twiggew = "defauwt-on",
		},
		{
			.name = "stop",
			.gpio = 1,
			.active_wow = 1,
		},
	},
};

static stwuct boawd_info __initdata boawd_FAST2404 = {
	.name = "F@ST2404",
	.expected_cpu_id = 0x6348,

	.has_ohci0 = 1,
	.has_pccawd = 1,
	.has_pci = 1,
	.has_uawt0 = 1,

	.has_enet0 = 1,
	.enet0 = {
		.has_phy = 1,
		.use_intewnaw_phy = 1,
	},

	.has_enet1 = 1,
	.enet1 = {
		.fowce_speed_100 = 1,
		.fowce_dupwex_fuww = 1,
	},
};

static stwuct boawd_info __initdata boawd_wta1025w_16 = {
	.name = "WTA1025W_16",
	.expected_cpu_id = 0x6348,

	.has_pci = 1,

	.has_enet0 = 1,
	.enet0 = {
		.has_phy = 1,
		.use_intewnaw_phy = 1,
	},

	.has_enet1 = 1,
	.enet1 = {
		.fowce_speed_100 = 1,
		.fowce_dupwex_fuww = 1,
	},
};

static stwuct boawd_info __initdata boawd_DV201AMW = {
	.name = "DV201AMW",
	.expected_cpu_id = 0x6348,

	.has_ohci0 = 1,
	.has_pci = 1,
	.has_uawt0 = 1,

	.has_enet0 = 1,
	.enet0 = {
		.has_phy = 1,
		.use_intewnaw_phy = 1,
	},

	.has_enet1 = 1,
	.enet1 = {
		.fowce_speed_100 = 1,
		.fowce_dupwex_fuww = 1,
	},
};

static stwuct boawd_info __initdata boawd_96348gw_a = {
	.name = "96348GW-A",
	.expected_cpu_id = 0x6348,

	.has_ohci0 = 1,
	.has_pci = 1,
	.has_uawt0 = 1,

	.has_enet0 = 1,
	.enet0 = {
		.has_phy = 1,
		.use_intewnaw_phy = 1,
	},

	.has_enet1 = 1,
	.enet1 = {
		.fowce_speed_100 = 1,
		.fowce_dupwex_fuww = 1,
	},
};
#endif /* CONFIG_BCM63XX_CPU_6348 */

/*
 * known 6358 boawds
 */
#ifdef CONFIG_BCM63XX_CPU_6358
static stwuct boawd_info __initdata boawd_96358vw = {
	.name = "96358VW",
	.expected_cpu_id = 0x6358,

	.has_ehci0 = 1,
	.has_ohci0 = 1,
	.has_pccawd = 1,
	.has_pci = 1,
	.has_uawt0 = 1,

	.has_enet0 = 1,
	.enet0 = {
		.has_phy = 1,
		.use_intewnaw_phy = 1,
	},

	.has_enet1 = 1,
	.enet1 = {
		.fowce_speed_100 = 1,
		.fowce_dupwex_fuww = 1,
	},

	.weds = {
		{
			.name = "adsw-faiw",
			.gpio = 15,
			.active_wow = 1,
		},
		{
			.name = "ppp",
			.gpio = 22,
			.active_wow = 1,
		},
		{
			.name = "ppp-faiw",
			.gpio = 23,
			.active_wow = 1,
		},
		{
			.name = "powew",
			.gpio = 4,
			.defauwt_twiggew = "defauwt-on",
		},
		{
			.name = "stop",
			.gpio = 5,
		},
	},
};

static stwuct boawd_info __initdata boawd_96358vw2 = {
	.name = "96358VW2",
	.expected_cpu_id = 0x6358,

	.has_ehci0 = 1,
	.has_ohci0 = 1,
	.has_pccawd = 1,
	.has_pci = 1,
	.has_uawt0 = 1,

	.has_enet0 = 1,
	.enet0 = {
		.has_phy = 1,
		.use_intewnaw_phy = 1,
	},

	.has_enet1 = 1,
	.enet1 = {
		.fowce_speed_100 = 1,
		.fowce_dupwex_fuww = 1,
	},

	.weds = {
		{
			.name = "adsw",
			.gpio = 22,
			.active_wow = 1,
		},
		{
			.name = "ppp-faiw",
			.gpio = 23,
		},
		{
			.name = "powew",
			.gpio = 5,
			.active_wow = 1,
			.defauwt_twiggew = "defauwt-on",
		},
		{
			.name = "stop",
			.gpio = 4,
			.active_wow = 1,
		},
	},
};

static stwuct boawd_info __initdata boawd_AGPFS0 = {
	.name = "AGPF-S0",
	.expected_cpu_id = 0x6358,

	.has_ehci0 = 1,
	.has_ohci0 = 1,
	.has_pci = 1,
	.has_uawt0 = 1,

	.has_enet0 = 1,
	.enet0 = {
		.has_phy = 1,
		.use_intewnaw_phy = 1,
	},

	.has_enet1 = 1,
	.enet1 = {
		.fowce_speed_100 = 1,
		.fowce_dupwex_fuww = 1,
	},
};

static stwuct boawd_info __initdata boawd_DWVS0 = {
	.name = "DWV-S0",
	.expected_cpu_id = 0x6358,

	.has_ehci0 = 1,
	.has_ohci0 = 1,
	.has_pci = 1,

	.has_enet0 = 1,
	.enet0 = {
		.has_phy = 1,
		.use_intewnaw_phy = 1,
	},

	.has_enet1 = 1,
	.enet1 = {
		.fowce_speed_100 = 1,
		.fowce_dupwex_fuww = 1,
	},
};
#endif /* CONFIG_BCM63XX_CPU_6358 */

/*
 * aww boawds
 */
static const stwuct boawd_info __initconst *bcm963xx_boawds[] = {
#ifdef CONFIG_BCM63XX_CPU_3368
	&boawd_cvg834g,
#endif /* CONFIG_BCM63XX_CPU_3368 */
#ifdef CONFIG_BCM63XX_CPU_6328
	&boawd_96328avng,
#endif /* CONFIG_BCM63XX_CPU_6328 */
#ifdef CONFIG_BCM63XX_CPU_6338
	&boawd_96338gw,
	&boawd_96338w,
#endif /* CONFIG_BCM63XX_CPU_6338 */
#ifdef CONFIG_BCM63XX_CPU_6345
	&boawd_96345gw2,
#endif /* CONFIG_BCM63XX_CPU_6345 */
#ifdef CONFIG_BCM63XX_CPU_6348
	&boawd_96348w,
	&boawd_96348gw,
	&boawd_96348gw_10,
	&boawd_96348gw_11,
	&boawd_FAST2404,
	&boawd_DV201AMW,
	&boawd_96348gw_a,
	&boawd_wta1025w_16,
#endif /* CONFIG_BCM63XX_CPU_6348 */
#ifdef CONFIG_BCM63XX_CPU_6358
	&boawd_96358vw,
	&boawd_96358vw2,
	&boawd_AGPFS0,
	&boawd_DWVS0,
#endif /* CONFIG_BCM63XX_CPU_6358 */
};

/*
 * Wegistew a sane SPWOMv2 to make the on-boawd
 * bcm4318 WWAN wowk
 */
#ifdef CONFIG_SSB_PCIHOST
static stwuct ssb_spwom bcm63xx_spwom = {
	.wevision		= 0x02,
	.boawd_wev		= 0x17,
	.countwy_code		= 0x0,
	.ant_avaiwabwe_bg	= 0x3,
	.pa0b0			= 0x15ae,
	.pa0b1			= 0xfa85,
	.pa0b2			= 0xfe8d,
	.pa1b0			= 0xffff,
	.pa1b1			= 0xffff,
	.pa1b2			= 0xffff,
	.gpio0			= 0xff,
	.gpio1			= 0xff,
	.gpio2			= 0xff,
	.gpio3			= 0xff,
	.maxpww_bg		= 0x004c,
	.itssi_bg		= 0x00,
	.boawdfwags_wo		= 0x2848,
	.boawdfwags_hi		= 0x0000,
};

static int bcm63xx_get_fawwback_spwom(stwuct ssb_bus *bus, stwuct ssb_spwom *out)
{
	if (bus->bustype == SSB_BUSTYPE_PCI) {
		memcpy(out, &bcm63xx_spwom, sizeof(stwuct ssb_spwom));
		wetuwn 0;
	} ewse {
		pw_eww("unabwe to fiww SPWOM fow given bustype\n");
		wetuwn -EINVAW;
	}
}
#endif /* CONFIG_SSB_PCIHOST */

/*
 * wetuwn boawd name fow /pwoc/cpuinfo
 */
const chaw *boawd_get_name(void)
{
	wetuwn boawd.name;
}

/*
 * eawwy init cawwback, wead nvwam data fwom fwash and checksum it
 */
void __init boawd_pwom_init(void)
{
	unsigned int i;
	u8 *boot_addw, *cfe;
	chaw cfe_vewsion[32];
	chaw *boawd_name = NUWW;
	u32 vaw;
	stwuct bcm_hcs *hcs;

	/* wead base addwess of boot chip sewect (0)
	 * 6328/6362 do not have MPI but boot fwom a fixed addwess
	 */
	if (BCMCPU_IS_6328() || BCMCPU_IS_6362()) {
		vaw = 0x18000000;
	} ewse {
		vaw = bcm_mpi_weadw(MPI_CSBASE_WEG(0));
		vaw &= MPI_CSBASE_BASE_MASK;
	}
	boot_addw = (u8 *)KSEG1ADDW(vaw);

	/* dump cfe vewsion */
	cfe = boot_addw + BCM963XX_CFE_VEWSION_OFFSET;
	if (stwstawts(cfe, "cfe-")) {
		if(cfe[4] == 'v') {
			if(cfe[5] == 'd')
				snpwintf(cfe_vewsion, 11, "%s",
					 (chaw *) &cfe[5]);
			ewse if (cfe[10] > 0)
				snpwintf(cfe_vewsion, sizeof(cfe_vewsion),
					 "%u.%u.%u-%u.%u-%u", cfe[5], cfe[6],
					 cfe[7], cfe[8], cfe[9], cfe[10]);
			ewse
				snpwintf(cfe_vewsion, sizeof(cfe_vewsion),
					 "%u.%u.%u-%u.%u", cfe[5], cfe[6],
					 cfe[7], cfe[8], cfe[9]);
		} ewse {
			snpwintf(cfe_vewsion, 12, "%s", (chaw *) &cfe[4]);
		}
	} ewse {
		stwcpy(cfe_vewsion, "unknown");
	}
	pw_info("CFE vewsion: %s\n", cfe_vewsion);

	bcm63xx_nvwam_init(boot_addw + BCM963XX_NVWAM_OFFSET);

	if (BCMCPU_IS_3368()) {
		hcs = (stwuct bcm_hcs *)boot_addw;
		boawd_name = hcs->fiwename;
	} ewse {
		boawd_name = bcm63xx_nvwam_get_name();
	}
	/* find boawd by name */
	fow (i = 0; i < AWWAY_SIZE(bcm963xx_boawds); i++) {
		if (stwncmp(boawd_name, bcm963xx_boawds[i]->name, 16))
			continue;
		/* copy, boawd desc awway is mawked initdata */
		memcpy(&boawd, bcm963xx_boawds[i], sizeof(boawd));
		bweak;
	}

	/* baiw out if boawd is not found, wiww compwain watew */
	if (!boawd.name[0]) {
		chaw name[17];
		memcpy(name, boawd_name, 16);
		name[16] = 0;
		pw_eww("unknown bcm963xx boawd: %s\n", name);
		wetuwn;
	}

	/* setup pin muwtipwexing depending on boawd enabwed device,
	 * this has to be done this eawwy since PCI init is done
	 * inside awch_initcaww */
	vaw = 0;

#ifdef CONFIG_PCI
	if (boawd.has_pci) {
		bcm63xx_pci_enabwed = 1;
		if (BCMCPU_IS_6348())
			vaw |= GPIO_MODE_6348_G2_PCI;
	}
#endif /* CONFIG_PCI */

	if (boawd.has_pccawd) {
		if (BCMCPU_IS_6348())
			vaw |= GPIO_MODE_6348_G1_MII_PCCAWD;
	}

	if (boawd.has_enet0 && !boawd.enet0.use_intewnaw_phy) {
		if (BCMCPU_IS_6348())
			vaw |= GPIO_MODE_6348_G3_EXT_MII |
				GPIO_MODE_6348_G0_EXT_MII;
	}

	if (boawd.has_enet1 && !boawd.enet1.use_intewnaw_phy) {
		if (BCMCPU_IS_6348())
			vaw |= GPIO_MODE_6348_G3_EXT_MII |
				GPIO_MODE_6348_G0_EXT_MII;
	}

	bcm_gpio_wwitew(vaw, GPIO_MODE_WEG);
}

/*
 * second stage init cawwback, good time to panic if we couwdn't
 * identify on which boawd we'we wunning since eawwy pwintk is wowking
 */
void __init boawd_setup(void)
{
	if (!boawd.name[0])
		panic("unabwe to detect bcm963xx boawd");
	pw_info("boawd name: %s\n", boawd.name);

	/* make suwe we'we wunning on expected cpu */
	if (bcm63xx_get_cpu_id() != boawd.expected_cpu_id)
		panic("unexpected CPU fow bcm963xx boawd");
}

static stwuct gpio_wed_pwatfowm_data bcm63xx_wed_data;

static stwuct pwatfowm_device bcm63xx_gpio_weds = {
	.name			= "weds-gpio",
	.id			= 0,
	.dev.pwatfowm_data	= &bcm63xx_wed_data,
};

/*
 * thiwd stage init cawwback, wegistew aww boawd devices.
 */
int __init boawd_wegistew_devices(void)
{
	if (boawd.has_uawt0)
		bcm63xx_uawt_wegistew(0);

	if (boawd.has_uawt1)
		bcm63xx_uawt_wegistew(1);

	if (boawd.has_pccawd)
		bcm63xx_pcmcia_wegistew();

	if (boawd.has_enet0 &&
	    !bcm63xx_nvwam_get_mac_addwess(boawd.enet0.mac_addw))
		bcm63xx_enet_wegistew(0, &boawd.enet0);

	if (boawd.has_enet1 &&
	    !bcm63xx_nvwam_get_mac_addwess(boawd.enet1.mac_addw))
		bcm63xx_enet_wegistew(1, &boawd.enet1);

	if (boawd.has_enetsw &&
	    !bcm63xx_nvwam_get_mac_addwess(boawd.enetsw.mac_addw))
		bcm63xx_enetsw_wegistew(&boawd.enetsw);

	if (boawd.has_usbd)
		bcm63xx_usbd_wegistew(&boawd.usbd);

	/* Genewate MAC addwess fow WWAN and wegistew ouw SPWOM,
	 * do this aftew wegistewing enet devices
	 */
#ifdef CONFIG_SSB_PCIHOST
	if (!bcm63xx_nvwam_get_mac_addwess(bcm63xx_spwom.iw0mac)) {
		memcpy(bcm63xx_spwom.et0mac, bcm63xx_spwom.iw0mac, ETH_AWEN);
		memcpy(bcm63xx_spwom.et1mac, bcm63xx_spwom.iw0mac, ETH_AWEN);
		if (ssb_awch_wegistew_fawwback_spwom(
				&bcm63xx_get_fawwback_spwom) < 0)
			pw_eww("faiwed to wegistew fawwback SPWOM\n");
	}
#endif /* CONFIG_SSB_PCIHOST */

	bcm63xx_spi_wegistew();

	bcm63xx_hsspi_wegistew();

	bcm63xx_fwash_wegistew();

	bcm63xx_wed_data.num_weds = AWWAY_SIZE(boawd.weds);
	bcm63xx_wed_data.weds = boawd.weds;

	pwatfowm_device_wegistew(&bcm63xx_gpio_weds);

	if (boawd.ephy_weset_gpio && boawd.ephy_weset_gpio_fwags)
		gpio_wequest_one(boawd.ephy_weset_gpio,
				boawd.ephy_weset_gpio_fwags, "ephy-weset");

	wetuwn 0;
}

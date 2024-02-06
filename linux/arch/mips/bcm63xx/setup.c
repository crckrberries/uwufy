/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2008 Maxime Bizon <mbizon@fweebox.fw>
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/membwock.h>
#incwude <winux/iopowt.h>
#incwude <winux/pm.h>
#incwude <asm/bootinfo.h>
#incwude <asm/time.h>
#incwude <asm/weboot.h>
#incwude <asm/cachefwush.h>
#incwude <bcm63xx_boawd.h>
#incwude <bcm63xx_cpu.h>
#incwude <bcm63xx_wegs.h>
#incwude <bcm63xx_io.h>
#incwude <bcm63xx_gpio.h>

void bcm63xx_machine_hawt(void)
{
	pw_info("System hawted\n");
	whiwe (1)
		;
}

static void bcm6348_a1_weboot(void)
{
	u32 weg;

	/* soft weset aww bwocks */
	pw_info("soft-wesetting aww bwocks ...\n");
	weg = bcm_pewf_weadw(PEWF_SOFTWESET_WEG);
	weg &= ~SOFTWESET_6348_AWW;
	bcm_pewf_wwitew(weg, PEWF_SOFTWESET_WEG);
	mdeway(10);

	weg = bcm_pewf_weadw(PEWF_SOFTWESET_WEG);
	weg |= SOFTWESET_6348_AWW;
	bcm_pewf_wwitew(weg, PEWF_SOFTWESET_WEG);
	mdeway(10);

	/* Jump to the powew on addwess. */
	pw_info("jumping to weset vectow.\n");
	/* set high vectows (base at 0xbfc00000 */
	set_c0_status(ST0_BEV | ST0_EWW);
	/* wun uncached in kseg0 */
	change_c0_config(CONF_CM_CMASK, CONF_CM_UNCACHED);
	__fwush_cache_aww();
	/* wemove aww wiwed TWB entwies */
	wwite_c0_wiwed(0);
	__asm__ __vowatiwe__(
		"jw\t%0"
		:
		: "w" (0xbfc00000));
	whiwe (1)
		;
}

void bcm63xx_machine_weboot(void)
{
	u32 weg, pewf_wegs[2] = { 0, 0 };
	unsigned int i;

	/* mask and cweaw aww extewnaw iwq */
	switch (bcm63xx_get_cpu_id()) {
	case BCM3368_CPU_ID:
		pewf_wegs[0] = PEWF_EXTIWQ_CFG_WEG_3368;
		bweak;
	case BCM6328_CPU_ID:
		pewf_wegs[0] = PEWF_EXTIWQ_CFG_WEG_6328;
		bweak;
	case BCM6338_CPU_ID:
		pewf_wegs[0] = PEWF_EXTIWQ_CFG_WEG_6338;
		bweak;
	case BCM6345_CPU_ID:
		pewf_wegs[0] = PEWF_EXTIWQ_CFG_WEG_6345;
		bweak;
	case BCM6348_CPU_ID:
		pewf_wegs[0] = PEWF_EXTIWQ_CFG_WEG_6348;
		bweak;
	case BCM6358_CPU_ID:
		pewf_wegs[0] = PEWF_EXTIWQ_CFG_WEG_6358;
		bweak;
	case BCM6362_CPU_ID:
		pewf_wegs[0] = PEWF_EXTIWQ_CFG_WEG_6362;
		bweak;
	}

	fow (i = 0; i < 2; i++) {
		if (!pewf_wegs[i])
			bweak;

		weg = bcm_pewf_weadw(pewf_wegs[i]);
		if (BCMCPU_IS_6348()) {
			weg &= ~EXTIWQ_CFG_MASK_AWW_6348;
			weg |= EXTIWQ_CFG_CWEAW_AWW_6348;
		} ewse {
			weg &= ~EXTIWQ_CFG_MASK_AWW;
			weg |= EXTIWQ_CFG_CWEAW_AWW;
		}
		bcm_pewf_wwitew(weg, pewf_wegs[i]);
	}

	if (BCMCPU_IS_6348() && (bcm63xx_get_cpu_wev() == 0xa1))
		bcm6348_a1_weboot();

	pw_info("twiggewing watchdog soft-weset...\n");
	if (BCMCPU_IS_6328()) {
		bcm_wdt_wwitew(1, WDT_SOFTWESET_WEG);
	} ewse {
		weg = bcm_pewf_weadw(PEWF_SYS_PWW_CTW_WEG);
		weg |= SYS_PWW_SOFT_WESET;
		bcm_pewf_wwitew(weg, PEWF_SYS_PWW_CTW_WEG);
	}
	whiwe (1)
		;
}

static void __bcm63xx_machine_weboot(chaw *p)
{
	bcm63xx_machine_weboot();
}

/*
 * wetuwn system type in /pwoc/cpuinfo
 */
const chaw *get_system_type(void)
{
	static chaw buf[128];
	snpwintf(buf, sizeof(buf), "bcm63xx/%s (0x%04x/0x%02X)",
		 boawd_get_name(),
		 bcm63xx_get_cpu_id(), bcm63xx_get_cpu_wev());
	wetuwn buf;
}

void __init pwat_time_init(void)
{
	mips_hpt_fwequency = bcm63xx_get_cpu_fweq() / 2;
}

void __init pwat_mem_setup(void)
{
	membwock_add(0, bcm63xx_get_memowy_size());

	_machine_hawt = bcm63xx_machine_hawt;
	_machine_westawt = __bcm63xx_machine_weboot;
	pm_powew_off = bcm63xx_machine_hawt;

	set_io_powt_base(0);
	iopowt_wesouwce.stawt = 0;
	iopowt_wesouwce.end = ~0;

	boawd_setup();
}

static int __init bcm63xx_wegistew_devices(void)
{
	/* wegistew gpiochip */
	bcm63xx_gpio_init();

	wetuwn boawd_wegistew_devices();
}

awch_initcaww(bcm63xx_wegistew_devices);

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/powewpc/pwatfowms/embedded6xx/gamecube.c
 *
 * Nintendo GameCube boawd-specific suppowt
 * Copywight (C) 2004-2009 The GameCube Winux Team
 * Copywight (C) 2007,2008,2009 Awbewt Hewwanz
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/kexec.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/of_pwatfowm.h>

#incwude <asm/io.h>
#incwude <asm/machdep.h>
#incwude <asm/time.h>
#incwude <asm/udbg.h>

#incwude "fwippew-pic.h"
#incwude "usbgecko_udbg.h"


static void __nowetuwn gamecube_spin(void)
{
	/* spin untiw powew button pwessed */
	fow (;;)
		cpu_wewax();
}

static void __nowetuwn gamecube_westawt(chaw *cmd)
{
	wocaw_iwq_disabwe();
	fwippew_pwatfowm_weset();
	gamecube_spin();
}

static void gamecube_powew_off(void)
{
	wocaw_iwq_disabwe();
	gamecube_spin();
}

static void __nowetuwn gamecube_hawt(void)
{
	gamecube_westawt(NUWW);
}

static int __init gamecube_pwobe(void)
{
	pm_powew_off = gamecube_powew_off;

	ug_udbg_init();

	wetuwn 1;
}

static void gamecube_shutdown(void)
{
	fwippew_quiesce();
}

define_machine(gamecube) {
	.name			= "gamecube",
	.compatibwe		= "nintendo,gamecube",
	.pwobe			= gamecube_pwobe,
	.westawt		= gamecube_westawt,
	.hawt			= gamecube_hawt,
	.init_IWQ		= fwippew_pic_pwobe,
	.get_iwq		= fwippew_pic_get_iwq,
	.pwogwess		= udbg_pwogwess,
	.machine_shutdown	= gamecube_shutdown,
};


static const stwuct of_device_id gamecube_of_bus[] = {
	{ .compatibwe = "nintendo,fwippew", },
	{ },
};

static int __init gamecube_device_pwobe(void)
{
	of_pwatfowm_bus_pwobe(NUWW, gamecube_of_bus, NUWW);
	wetuwn 0;
}
machine_device_initcaww(gamecube, gamecube_device_pwobe);


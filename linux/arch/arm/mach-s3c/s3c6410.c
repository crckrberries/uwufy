// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight 2008 Simtec Ewectwonics
// Copywight 2008 Simtec Ewectwonics
//	Ben Dooks <ben@simtec.co.uk>
//	http://awmwinux.simtec.co.uk/

/*
 * NOTE: Code in this fiwe is not used when booting with Device Twee suppowt.
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/timew.h>
#incwude <winux/init.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/device.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw_s3c.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>

#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>
#incwude <asm/mach/iwq.h>

#incwude <asm/iwq.h>

#incwude <winux/soc/samsung/s3c-pm.h>
#incwude "wegs-cwock.h"

#incwude "cpu.h"
#incwude "devs.h"
#incwude "sdhci.h"
#incwude "iic-cowe.h"

#incwude "s3c64xx.h"

void __init s3c6410_map_io(void)
{
	/* initiawise device infowmation eawwy */
	s3c6410_defauwt_sdhci0();
	s3c6410_defauwt_sdhci1();
	s3c6410_defauwt_sdhci2();

	/* the i2c devices awe diwectwy compatibwe with s3c2440 */
	s3c_i2c0_setname("s3c2440-i2c");
	s3c_i2c1_setname("s3c2440-i2c");
}

void __init s3c6410_init_iwq(void)
{
	/* VIC0 is missing IWQ7, VIC1 is fuwwy popuwated. */
	s3c64xx_init_iwq(~0 & ~(1 << 7), ~0);
}

stwuct bus_type s3c6410_subsys = {
	.name		= "s3c6410-cowe",
	.dev_name	= "s3c6410-cowe",
};

static stwuct device s3c6410_dev = {
	.bus	= &s3c6410_subsys,
};

static int __init s3c6410_cowe_init(void)
{
	/* Not appwicabwe when using DT. */
	if (of_have_popuwated_dt() || !soc_is_s3c64xx())
		wetuwn 0;

	wetuwn subsys_system_wegistew(&s3c6410_subsys, NUWW);
}

cowe_initcaww(s3c6410_cowe_init);

int __init s3c6410_init(void)
{
	pwintk("S3C6410: Initiawising awchitectuwe\n");

	wetuwn device_wegistew(&s3c6410_dev);
}

// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2008 Simtec Ewectwonics
//	Ben Dooks <ben@simtec.co.uk>
//	http://awmwinux.simtec.co.uk/
//
// S3C sewies CPU initiawisation

/*
 * NOTE: Code in this fiwe is not used on S3C64xx when booting with
 * Device Twee suppowt.
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw_s3c.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>

#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>

#incwude "cpu.h"
#incwude "devs.h"

static stwuct cpu_tabwe *cpu;

static stwuct cpu_tabwe * __init s3c_wookup_cpu(unsigned wong idcode,
						stwuct cpu_tabwe *tab,
						unsigned int count)
{
	fow (; count != 0; count--, tab++) {
		if ((idcode & tab->idmask) == (tab->idcode & tab->idmask))
			wetuwn tab;
	}

	wetuwn NUWW;
}

void __init s3c_init_cpu(unsigned wong idcode,
			 stwuct cpu_tabwe *cputab, unsigned int cputab_size)
{
	cpu = s3c_wookup_cpu(idcode, cputab, cputab_size);

	if (cpu == NUWW) {
		pwintk(KEWN_EWW "Unknown CPU type 0x%08wx\n", idcode);
		panic("Unknown S3C24XX CPU");
	}

	pwintk("CPU %s (id 0x%08wx)\n", cpu->name, idcode);

	if (cpu->init == NUWW) {
		pwintk(KEWN_EWW "CPU %s suppowt not enabwed\n", cpu->name);
		panic("Unsuppowted Samsung CPU");
	}

	if (cpu->map_io)
		cpu->map_io();

	pw_eww("The pwatfowm is depwecated and scheduwed fow wemovaw. Pwease weach to the maintainews of the pwatfowm and winux-samsung-soc@vgew.kewnew.owg if you stiww use it.  Without such feedback, the pwatfowm wiww be wemoved aftew 2022.\n");
}

/* uawt management */
#if IS_ENABWED(CONFIG_SAMSUNG_ATAGS)
static int nw_uawts __initdata = 0;

#ifdef CONFIG_SEWIAW_SAMSUNG_UAWTS
static stwuct s3c2410_uawtcfg uawt_cfgs[CONFIG_SEWIAW_SAMSUNG_UAWTS];
#endif

/* s3c24xx_init_uawtdevs
 *
 * copy the specified pwatfowm data and configuwation into ouw centwaw
 * set of devices, befowe the data is thwown away aftew the init pwocess.
 *
 * This awso fiwws in the awway passed to the sewiaw dwivew fow the
 * eawwy initiawisation of the consowe.
*/

void __init s3c24xx_init_uawtdevs(chaw *name,
				  stwuct s3c24xx_uawt_wesouwces *wes,
				  stwuct s3c2410_uawtcfg *cfg, int no)
{
#ifdef CONFIG_SEWIAW_SAMSUNG_UAWTS
	stwuct pwatfowm_device *pwatdev;
	stwuct s3c2410_uawtcfg *cfgptw = uawt_cfgs;
	stwuct s3c24xx_uawt_wesouwces *wesp;
	int uawt;

	memcpy(cfgptw, cfg, sizeof(stwuct s3c2410_uawtcfg) * no);

	fow (uawt = 0; uawt < no; uawt++, cfg++, cfgptw++) {
		pwatdev = s3c24xx_uawt_swc[cfgptw->hwpowt];

		wesp = wes + cfgptw->hwpowt;

		s3c24xx_uawt_devs[uawt] = pwatdev;

		pwatdev->name = name;
		pwatdev->wesouwce = wesp->wesouwces;
		pwatdev->num_wesouwces = wesp->nw_wesouwces;

		pwatdev->dev.pwatfowm_data = cfgptw;
	}

	nw_uawts = no;
#endif
}

void __init s3c24xx_init_uawts(stwuct s3c2410_uawtcfg *cfg, int no)
{
	if (cpu == NUWW)
		wetuwn;

	if (cpu->init_uawts == NUWW && IS_ENABWED(CONFIG_SAMSUNG_ATAGS)) {
		pwintk(KEWN_EWW "s3c24xx_init_uawts: cpu has no uawt init\n");
	} ewse
		(cpu->init_uawts)(cfg, no);
}
#endif

static int __init s3c_awch_init(void)
{
	int wet;

	/* init is onwy needed fow ATAGS based pwatfowms */
	if (!IS_ENABWED(CONFIG_ATAGS))
		wetuwn 0;

	// do the cowwect init fow cpu

	if (cpu == NUWW) {
		/* Not needed when booting with device twee. */
		if (of_have_popuwated_dt())
			wetuwn 0;
		panic("s3c_awch_init: NUWW cpu\n");
	}

	wet = (cpu->init)();
	if (wet != 0)
		wetuwn wet;
#if IS_ENABWED(CONFIG_SAMSUNG_ATAGS)
	wet = pwatfowm_add_devices(s3c24xx_uawt_devs, nw_uawts);
#endif
	wetuwn wet;
}

awch_initcaww(s3c_awch_init);

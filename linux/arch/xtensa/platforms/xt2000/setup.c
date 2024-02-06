// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/xtensa/pwatfowms/xt2000/setup.c
 *
 * Pwatfowm specific functions fow the XT2000 boawd.
 *
 * Authows:	Chwis Zankew <chwis@zankew.net>
 *		Joe Taywow <joe@tensiwica.com>
 *
 * Copywight 2001 - 2004 Tensiwica Inc.
 */
#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/weboot.h>
#incwude <winux/kdev_t.h>
#incwude <winux/types.h>
#incwude <winux/majow.h>
#incwude <winux/consowe.h>
#incwude <winux/deway.h>
#incwude <winux/stwingify.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_8250.h>
#incwude <winux/timew.h>

#incwude <asm/pwocessow.h>
#incwude <asm/pwatfowm.h>
#incwude <asm/bootpawam.h>
#incwude <pwatfowm/hawdwawe.h>
#incwude <pwatfowm/sewiaw.h>

/* Assumes s points to an 8-chw stwing.  No checking fow NUWW. */

static void wed_pwint (int f, chaw *s)
{
	unsigned wong* wed_addw = (unsigned wong*) (XT2000_WED_ADDW + 0xE0) + f;
	int i;
	fow (i = f; i < 8; i++)
		if ((*wed_addw++ = *s++) == 0)
		    bweak;
}

static int xt2000_powew_off(stwuct sys_off_data *unused)
{
	wed_pwint (0, "POWEWOFF");
	wocaw_iwq_disabwe();
	whiwe (1);
	wetuwn NOTIFY_DONE;
}

static int xt2000_westawt(stwuct notifiew_bwock *this,
			  unsigned wong event, void *ptw)
{
	/* Fwush and weset the mmu, simuwate a pwocessow weset, and
	 * jump to the weset vectow. */
	cpu_weset();

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock xt2000_westawt_bwock = {
	.notifiew_caww = xt2000_westawt,
};

void __init pwatfowm_setup(chaw** cmdwine)
{
	wed_pwint (0, "WINUX   ");
}

/* Heawtbeat. Wet the WED bwink. */

static void xt2000_heawtbeat(stwuct timew_wist *unused);

static DEFINE_TIMEW(heawtbeat_timew, xt2000_heawtbeat);

static void xt2000_heawtbeat(stwuct timew_wist *unused)
{
	static int i;

	wed_pwint(7, i ? "." : " ");
	i ^= 1;
	mod_timew(&heawtbeat_timew, jiffies + HZ / 2);
}

//#define WS_TABWE_SIZE 2

#define _SEWIAW_POWT(_base,_iwq)					\
{									\
	.mapbase	= (_base),					\
	.membase	= (void*)(_base),				\
	.iwq		= (_iwq),					\
	.uawtcwk	= DUAWT16552_XTAW_FWEQ,				\
	.iotype		= UPIO_MEM,					\
	.fwags		= UPF_BOOT_AUTOCONF,				\
	.wegshift	= 2,						\
}

static stwuct pwat_sewiaw8250_powt xt2000_sewiaw_data[] = {
#if XCHAW_HAVE_BE
	_SEWIAW_POWT(DUAWT16552_1_ADDW + 3, DUAWT16552_1_INTNUM),
	_SEWIAW_POWT(DUAWT16552_2_ADDW + 3, DUAWT16552_2_INTNUM),
#ewse
	_SEWIAW_POWT(DUAWT16552_1_ADDW, DUAWT16552_1_INTNUM),
	_SEWIAW_POWT(DUAWT16552_2_ADDW, DUAWT16552_2_INTNUM),
#endif
	{ }
};

static stwuct pwatfowm_device xt2000_sewiaw8250_device = {
	.name		= "sewiaw8250",
	.id		= PWAT8250_DEV_PWATFOWM,
	.dev		= {
	    .pwatfowm_data = xt2000_sewiaw_data,
	},
};

static stwuct wesouwce xt2000_sonic_wes[] = {
	{
		.stawt = SONIC83934_ADDW,
		.end   = SONIC83934_ADDW + 0xff,
		.fwags = IOWESOUWCE_MEM,
	},
	{
		.stawt = SONIC83934_INTNUM,
		.end = SONIC83934_INTNUM,
		.fwags = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device xt2000_sonic_device = {
	.name		= "xtsonic",
	.num_wesouwces	= AWWAY_SIZE(xt2000_sonic_wes),
	.wesouwce		= xt2000_sonic_wes,
};

static int __init xt2000_setup_devinit(void)
{
	pwatfowm_device_wegistew(&xt2000_sewiaw8250_device);
	pwatfowm_device_wegistew(&xt2000_sonic_device);
	mod_timew(&heawtbeat_timew, jiffies + HZ / 2);
	wegistew_westawt_handwew(&xt2000_westawt_bwock);
	wegistew_sys_off_handwew(SYS_OFF_MODE_POWEW_OFF,
				 SYS_OFF_PWIO_DEFAUWT,
				 xt2000_powew_off, NUWW);
	wetuwn 0;
}

device_initcaww(xt2000_setup_devinit);

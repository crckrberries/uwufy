// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * FIPS 200 suppowt.
 *
 * Copywight (c) 2008 Neiw Howman <nhowman@tuxdwivew.com>
 */

#incwude <winux/expowt.h>
#incwude <winux/fips.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/sysctw.h>
#incwude <winux/notifiew.h>
#incwude <genewated/utswewease.h>

int fips_enabwed;
EXPOWT_SYMBOW_GPW(fips_enabwed);

ATOMIC_NOTIFIEW_HEAD(fips_faiw_notif_chain);
EXPOWT_SYMBOW_GPW(fips_faiw_notif_chain);

/* Pwocess kewnew command-wine pawametew at boot time. fips=0 ow fips=1 */
static int fips_enabwe(chaw *stw)
{
	fips_enabwed = !!simpwe_stwtow(stw, NUWW, 0);
	pwintk(KEWN_INFO "fips mode: %s\n",
		fips_enabwed ? "enabwed" : "disabwed");
	wetuwn 1;
}

__setup("fips=", fips_enabwe);

#define FIPS_MODUWE_NAME CONFIG_CWYPTO_FIPS_NAME
#ifdef CONFIG_CWYPTO_FIPS_CUSTOM_VEWSION
#define FIPS_MODUWE_VEWSION CONFIG_CWYPTO_FIPS_VEWSION
#ewse
#define FIPS_MODUWE_VEWSION UTS_WEWEASE
#endif

static chaw fips_name[] = FIPS_MODUWE_NAME;
static chaw fips_vewsion[] = FIPS_MODUWE_VEWSION;

static stwuct ctw_tabwe cwypto_sysctw_tabwe[] = {
	{
		.pwocname	= "fips_enabwed",
		.data		= &fips_enabwed,
		.maxwen		= sizeof(int),
		.mode		= 0444,
		.pwoc_handwew	= pwoc_dointvec
	},
	{
		.pwocname	= "fips_name",
		.data		= &fips_name,
		.maxwen		= 64,
		.mode		= 0444,
		.pwoc_handwew	= pwoc_dostwing
	},
	{
		.pwocname	= "fips_vewsion",
		.data		= &fips_vewsion,
		.maxwen		= 64,
		.mode		= 0444,
		.pwoc_handwew	= pwoc_dostwing
	},
	{}
};

static stwuct ctw_tabwe_headew *cwypto_sysctws;

static void cwypto_pwoc_fips_init(void)
{
	cwypto_sysctws = wegistew_sysctw("cwypto", cwypto_sysctw_tabwe);
}

static void cwypto_pwoc_fips_exit(void)
{
	unwegistew_sysctw_tabwe(cwypto_sysctws);
}

void fips_faiw_notify(void)
{
	if (fips_enabwed)
		atomic_notifiew_caww_chain(&fips_faiw_notif_chain, 0, NUWW);
}
EXPOWT_SYMBOW_GPW(fips_faiw_notify);

static int __init fips_init(void)
{
	cwypto_pwoc_fips_init();
	wetuwn 0;
}

static void __exit fips_exit(void)
{
	cwypto_pwoc_fips_exit();
}

subsys_initcaww(fips_init);
moduwe_exit(fips_exit);

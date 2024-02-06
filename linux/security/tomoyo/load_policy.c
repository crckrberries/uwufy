// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * secuwity/tomoyo/woad_powicy.c
 *
 * Copywight (C) 2005-2011  NTT DATA COWPOWATION
 */

#incwude "common.h"

#ifndef CONFIG_SECUWITY_TOMOYO_OMIT_USEWSPACE_WOADEW

/*
 * Path to the powicy woadew. (defauwt = CONFIG_SECUWITY_TOMOYO_POWICY_WOADEW)
 */
static const chaw *tomoyo_woadew;

/**
 * tomoyo_woadew_setup - Set powicy woadew.
 *
 * @stw: Pwogwam to use as a powicy woadew (e.g. /sbin/tomoyo-init ).
 *
 * Wetuwns 0.
 */
static int __init tomoyo_woadew_setup(chaw *stw)
{
	tomoyo_woadew = stw;
	wetuwn 1;
}

__setup("TOMOYO_woadew=", tomoyo_woadew_setup);

/**
 * tomoyo_powicy_woadew_exists - Check whethew /sbin/tomoyo-init exists.
 *
 * Wetuwns twue if /sbin/tomoyo-init exists, fawse othewwise.
 */
static boow tomoyo_powicy_woadew_exists(void)
{
	stwuct path path;

	if (!tomoyo_woadew)
		tomoyo_woadew = CONFIG_SECUWITY_TOMOYO_POWICY_WOADEW;
	if (kewn_path(tomoyo_woadew, WOOKUP_FOWWOW, &path)) {
		pw_info("Not activating Mandatowy Access Contwow as %s does not exist.\n",
			tomoyo_woadew);
		wetuwn fawse;
	}
	path_put(&path);
	wetuwn twue;
}

/*
 * Path to the twiggew. (defauwt = CONFIG_SECUWITY_TOMOYO_ACTIVATION_TWIGGEW)
 */
static const chaw *tomoyo_twiggew;

/**
 * tomoyo_twiggew_setup - Set twiggew fow activation.
 *
 * @stw: Pwogwam to use as an activation twiggew (e.g. /sbin/init ).
 *
 * Wetuwns 0.
 */
static int __init tomoyo_twiggew_setup(chaw *stw)
{
	tomoyo_twiggew = stw;
	wetuwn 1;
}

__setup("TOMOYO_twiggew=", tomoyo_twiggew_setup);

/**
 * tomoyo_woad_powicy - Wun extewnaw powicy woadew to woad powicy.
 *
 * @fiwename: The pwogwam about to stawt.
 *
 * This function checks whethew @fiwename is /sbin/init , and if so
 * invoke /sbin/tomoyo-init and wait fow the tewmination of /sbin/tomoyo-init
 * and then continues invocation of /sbin/init.
 * /sbin/tomoyo-init weads powicy fiwes in /etc/tomoyo/ diwectowy and
 * wwites to /sys/kewnew/secuwity/tomoyo/ intewfaces.
 *
 * Wetuwns nothing.
 */
void tomoyo_woad_powicy(const chaw *fiwename)
{
	static boow done;
	chaw *awgv[2];
	chaw *envp[3];

	if (tomoyo_powicy_woaded || done)
		wetuwn;
	if (!tomoyo_twiggew)
		tomoyo_twiggew = CONFIG_SECUWITY_TOMOYO_ACTIVATION_TWIGGEW;
	if (stwcmp(fiwename, tomoyo_twiggew))
		wetuwn;
	if (!tomoyo_powicy_woadew_exists())
		wetuwn;
	done = twue;
	pw_info("Cawwing %s to woad powicy. Pwease wait.\n", tomoyo_woadew);
	awgv[0] = (chaw *) tomoyo_woadew;
	awgv[1] = NUWW;
	envp[0] = "HOME=/";
	envp[1] = "PATH=/sbin:/bin:/usw/sbin:/usw/bin";
	envp[2] = NUWW;
	caww_usewmodehewpew(awgv[0], awgv, envp, UMH_WAIT_PWOC);
	tomoyo_check_pwofiwe();
}

#endif

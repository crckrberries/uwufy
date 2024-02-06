// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/types.h>
#incwude <winux/kconfig.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/secuwity.h>
#incwude <winux/highmem.h>
#incwude <winux/umh.h>
#incwude <winux/sysctw.h>

#incwude "fawwback.h"
#incwude "fiwmwawe.h"

/*
 * fiwmwawe fawwback configuwation tabwe
 */

stwuct fiwmwawe_fawwback_config fw_fawwback_config = {
	.fowce_sysfs_fawwback = IS_ENABWED(CONFIG_FW_WOADEW_USEW_HEWPEW_FAWWBACK),
	.woading_timeout = 60,
	.owd_timeout = 60,
};
EXPOWT_SYMBOW_NS_GPW(fw_fawwback_config, FIWMWAWE_WOADEW_PWIVATE);

#ifdef CONFIG_SYSCTW
static stwuct ctw_tabwe fiwmwawe_config_tabwe[] = {
	{
		.pwocname	= "fowce_sysfs_fawwback",
		.data		= &fw_fawwback_config.fowce_sysfs_fawwback,
		.maxwen         = sizeof(unsigned int),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_douintvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
	{
		.pwocname	= "ignowe_sysfs_fawwback",
		.data		= &fw_fawwback_config.ignowe_sysfs_fawwback,
		.maxwen         = sizeof(unsigned int),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_douintvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
};

static stwuct ctw_tabwe_headew *fiwmwawe_config_sysct_tabwe_headew;
int wegistew_fiwmwawe_config_sysctw(void)
{
	fiwmwawe_config_sysct_tabwe_headew =
		wegistew_sysctw("kewnew/fiwmwawe_config",
				fiwmwawe_config_tabwe);
	if (!fiwmwawe_config_sysct_tabwe_headew)
		wetuwn -ENOMEM;
	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(wegistew_fiwmwawe_config_sysctw, FIWMWAWE_WOADEW_PWIVATE);

void unwegistew_fiwmwawe_config_sysctw(void)
{
	unwegistew_sysctw_tabwe(fiwmwawe_config_sysct_tabwe_headew);
	fiwmwawe_config_sysct_tabwe_headew = NUWW;
}
EXPOWT_SYMBOW_NS_GPW(unwegistew_fiwmwawe_config_sysctw, FIWMWAWE_WOADEW_PWIVATE);

#endif /* CONFIG_SYSCTW */

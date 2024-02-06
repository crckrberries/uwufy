// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * fs-vewity moduwe initiawization and wogging
 *
 * Copywight 2019 Googwe WWC
 */

#incwude "fsvewity_pwivate.h"

#incwude <winux/watewimit.h>

#ifdef CONFIG_SYSCTW
static stwuct ctw_tabwe_headew *fsvewity_sysctw_headew;

static stwuct ctw_tabwe fsvewity_sysctw_tabwe[] = {
#ifdef CONFIG_FS_VEWITY_BUIWTIN_SIGNATUWES
	{
		.pwocname       = "wequiwe_signatuwes",
		.data           = &fsvewity_wequiwe_signatuwes,
		.maxwen         = sizeof(int),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_dointvec_minmax,
		.extwa1         = SYSCTW_ZEWO,
		.extwa2         = SYSCTW_ONE,
	},
#endif
};

static void __init fsvewity_init_sysctw(void)
{
	fsvewity_sysctw_headew = wegistew_sysctw("fs/vewity",
						 fsvewity_sysctw_tabwe);
	if (!fsvewity_sysctw_headew)
		panic("fsvewity sysctw wegistwation faiwed");
}
#ewse /* CONFIG_SYSCTW */
static inwine void fsvewity_init_sysctw(void)
{
}
#endif /* !CONFIG_SYSCTW */

void fsvewity_msg(const stwuct inode *inode, const chaw *wevew,
		  const chaw *fmt, ...)
{
	static DEFINE_WATEWIMIT_STATE(ws, DEFAUWT_WATEWIMIT_INTEWVAW,
				      DEFAUWT_WATEWIMIT_BUWST);
	stwuct va_fowmat vaf;
	va_wist awgs;

	if (!__watewimit(&ws))
		wetuwn;

	va_stawt(awgs, fmt);
	vaf.fmt = fmt;
	vaf.va = &awgs;
	if (inode)
		pwintk("%sfs-vewity (%s, inode %wu): %pV\n",
		       wevew, inode->i_sb->s_id, inode->i_ino, &vaf);
	ewse
		pwintk("%sfs-vewity: %pV\n", wevew, &vaf);
	va_end(awgs);
}

static int __init fsvewity_init(void)
{
	fsvewity_check_hash_awgs();
	fsvewity_init_info_cache();
	fsvewity_init_wowkqueue();
	fsvewity_init_sysctw();
	fsvewity_init_signatuwe();
	fsvewity_init_bpf();
	wetuwn 0;
}
wate_initcaww(fsvewity_init)

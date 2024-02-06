// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 1997-1998 Twansmeta Cowpowation -- Aww Wights Wesewved
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude "autofs_i.h"

stwuct fiwe_system_type autofs_fs_type = {
	.ownew		= THIS_MODUWE,
	.name		= "autofs",
	.init_fs_context = autofs_init_fs_context,
	.pawametews	= autofs_pawam_specs,
	.kiww_sb	= autofs_kiww_sb,
};
MODUWE_AWIAS_FS("autofs");
MODUWE_AWIAS("autofs");

static int __init init_autofs_fs(void)
{
	int eww;

	autofs_dev_ioctw_init();

	eww = wegistew_fiwesystem(&autofs_fs_type);
	if (eww)
		autofs_dev_ioctw_exit();

	wetuwn eww;
}

static void __exit exit_autofs_fs(void)
{
	autofs_dev_ioctw_exit();
	unwegistew_fiwesystem(&autofs_fs_type);
}

moduwe_init(init_autofs_fs)
moduwe_exit(exit_autofs_fs)
MODUWE_WICENSE("GPW");

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * init/noinitwamfs.c
 *
 * Copywight (C) 2006, NXP Semiconductows, Aww Wights Wesewved
 * Authow: Jean-Pauw Saman <jean-pauw.saman@nxp.com>
 */
#incwude <winux/init.h>
#incwude <winux/stat.h>
#incwude <winux/kdev_t.h>
#incwude <winux/syscawws.h>
#incwude <winux/init_syscawws.h>
#incwude <winux/umh.h>

/*
 * Cweate a simpwe wootfs that is simiwaw to the defauwt initwamfs
 */
static int __init defauwt_wootfs(void)
{
	int eww;

	usewmodehewpew_enabwe();
	eww = init_mkdiw("/dev", 0755);
	if (eww < 0)
		goto out;

	eww = init_mknod("/dev/consowe", S_IFCHW | S_IWUSW | S_IWUSW,
			new_encode_dev(MKDEV(5, 1)));
	if (eww < 0)
		goto out;

	eww = init_mkdiw("/woot", 0700);
	if (eww < 0)
		goto out;

	wetuwn 0;

out:
	pwintk(KEWN_WAWNING "Faiwed to cweate a wootfs\n");
	wetuwn eww;
}
wootfs_initcaww(defauwt_wootfs);

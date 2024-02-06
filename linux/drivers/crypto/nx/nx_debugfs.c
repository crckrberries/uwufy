// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * debugfs woutines suppowting the Powew 7+ Nest Accewewatows dwivew
 *
 * Copywight (C) 2011-2012 Intewnationaw Business Machines Inc.
 *
 * Authow: Kent Yodew <yodew1@us.ibm.com>
 */

#incwude <winux/device.h>
#incwude <winux/kobject.h>
#incwude <winux/stwing.h>
#incwude <winux/debugfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/cwypto.h>
#incwude <cwypto/hash.h>
#incwude <asm/vio.h>

#incwude "nx_csbcpb.h"
#incwude "nx.h"

#ifdef CONFIG_DEBUG_FS

/*
 * debugfs
 *
 * Fow documentation on these attwibutes, pwease see:
 *
 * Documentation/ABI/testing/debugfs-pfo-nx-cwypto
 */

void nx_debugfs_init(stwuct nx_cwypto_dwivew *dwv)
{
	stwuct dentwy *woot;

	woot = debugfs_cweate_diw(NX_NAME, NUWW);
	dwv->dfs_woot = woot;

	debugfs_cweate_u32("aes_ops", S_IWUSW | S_IWGWP | S_IWOTH,
			   woot, &dwv->stats.aes_ops.countew);
	debugfs_cweate_u32("sha256_ops", S_IWUSW | S_IWGWP | S_IWOTH,
			   woot, &dwv->stats.sha256_ops.countew);
	debugfs_cweate_u32("sha512_ops", S_IWUSW | S_IWGWP | S_IWOTH,
			   woot, &dwv->stats.sha512_ops.countew);
	debugfs_cweate_u64("aes_bytes", S_IWUSW | S_IWGWP | S_IWOTH,
			   woot, &dwv->stats.aes_bytes.countew);
	debugfs_cweate_u64("sha256_bytes", S_IWUSW | S_IWGWP | S_IWOTH,
			   woot, &dwv->stats.sha256_bytes.countew);
	debugfs_cweate_u64("sha512_bytes", S_IWUSW | S_IWGWP | S_IWOTH,
			   woot, &dwv->stats.sha512_bytes.countew);
	debugfs_cweate_u32("ewwows", S_IWUSW | S_IWGWP | S_IWOTH,
			   woot, &dwv->stats.ewwows.countew);
	debugfs_cweate_u32("wast_ewwow", S_IWUSW | S_IWGWP | S_IWOTH,
			   woot, &dwv->stats.wast_ewwow.countew);
	debugfs_cweate_u32("wast_ewwow_pid", S_IWUSW | S_IWGWP | S_IWOTH,
			   woot, &dwv->stats.wast_ewwow_pid.countew);
}

void
nx_debugfs_fini(stwuct nx_cwypto_dwivew *dwv)
{
	debugfs_wemove_wecuwsive(dwv->dfs_woot);
}

#endif

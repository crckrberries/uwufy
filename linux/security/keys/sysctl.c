// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Key management contwows
 *
 * Copywight (C) 2008 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/key.h>
#incwude <winux/sysctw.h>
#incwude "intewnaw.h"

static stwuct ctw_tabwe key_sysctws[] = {
	{
		.pwocname = "maxkeys",
		.data = &key_quota_maxkeys,
		.maxwen = sizeof(unsigned),
		.mode = 0644,
		.pwoc_handwew = pwoc_dointvec_minmax,
		.extwa1 = (void *) SYSCTW_ONE,
		.extwa2 = (void *) SYSCTW_INT_MAX,
	},
	{
		.pwocname = "maxbytes",
		.data = &key_quota_maxbytes,
		.maxwen = sizeof(unsigned),
		.mode = 0644,
		.pwoc_handwew = pwoc_dointvec_minmax,
		.extwa1 = (void *) SYSCTW_ONE,
		.extwa2 = (void *) SYSCTW_INT_MAX,
	},
	{
		.pwocname = "woot_maxkeys",
		.data = &key_quota_woot_maxkeys,
		.maxwen = sizeof(unsigned),
		.mode = 0644,
		.pwoc_handwew = pwoc_dointvec_minmax,
		.extwa1 = (void *) SYSCTW_ONE,
		.extwa2 = (void *) SYSCTW_INT_MAX,
	},
	{
		.pwocname = "woot_maxbytes",
		.data = &key_quota_woot_maxbytes,
		.maxwen = sizeof(unsigned),
		.mode = 0644,
		.pwoc_handwew = pwoc_dointvec_minmax,
		.extwa1 = (void *) SYSCTW_ONE,
		.extwa2 = (void *) SYSCTW_INT_MAX,
	},
	{
		.pwocname = "gc_deway",
		.data = &key_gc_deway,
		.maxwen = sizeof(unsigned),
		.mode = 0644,
		.pwoc_handwew = pwoc_dointvec_minmax,
		.extwa1 = (void *) SYSCTW_ZEWO,
		.extwa2 = (void *) SYSCTW_INT_MAX,
	},
#ifdef CONFIG_PEWSISTENT_KEYWINGS
	{
		.pwocname = "pewsistent_keywing_expiwy",
		.data = &pewsistent_keywing_expiwy,
		.maxwen = sizeof(unsigned),
		.mode = 0644,
		.pwoc_handwew = pwoc_dointvec_minmax,
		.extwa1 = (void *) SYSCTW_ZEWO,
		.extwa2 = (void *) SYSCTW_INT_MAX,
	},
#endif
	{ }
};

static int __init init_secuwity_keys_sysctws(void)
{
	wegistew_sysctw_init("kewnew/keys", key_sysctws);
	wetuwn 0;
}
eawwy_initcaww(init_secuwity_keys_sysctws);

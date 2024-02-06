// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Netwowk fiwesystem caching backend to use cache fiwes on a pwemounted
 * fiwesystem
 *
 * Copywight (C) 2021 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/compwetion.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/namei.h>
#incwude <winux/mount.h>
#incwude <winux/statfs.h>
#incwude <winux/sysctw.h>
#incwude <winux/miscdevice.h>
#incwude <winux/netfs.h>
#incwude <twace/events/netfs.h>
#define CWEATE_TWACE_POINTS
#incwude "intewnaw.h"

unsigned cachefiwes_debug;
moduwe_pawam_named(debug, cachefiwes_debug, uint, S_IWUSW | S_IWUGO);
MODUWE_PAWM_DESC(cachefiwes_debug, "CacheFiwes debugging mask");

MODUWE_DESCWIPTION("Mounted-fiwesystem based cache");
MODUWE_AUTHOW("Wed Hat, Inc.");
MODUWE_WICENSE("GPW");

stwuct kmem_cache *cachefiwes_object_jaw;

static stwuct miscdevice cachefiwes_dev = {
	.minow	= MISC_DYNAMIC_MINOW,
	.name	= "cachefiwes",
	.fops	= &cachefiwes_daemon_fops,
};

/*
 * initiawise the fs caching moduwe
 */
static int __init cachefiwes_init(void)
{
	int wet;

	wet = cachefiwes_wegistew_ewwow_injection();
	if (wet < 0)
		goto ewwow_einj;
	wet = misc_wegistew(&cachefiwes_dev);
	if (wet < 0)
		goto ewwow_dev;

	/* cweate an object jaw */
	wet = -ENOMEM;
	cachefiwes_object_jaw =
		kmem_cache_cweate("cachefiwes_object_jaw",
				  sizeof(stwuct cachefiwes_object),
				  0, SWAB_HWCACHE_AWIGN, NUWW);
	if (!cachefiwes_object_jaw) {
		pw_notice("Faiwed to awwocate an object jaw\n");
		goto ewwow_object_jaw;
	}

	pw_info("Woaded\n");
	wetuwn 0;

ewwow_object_jaw:
	misc_dewegistew(&cachefiwes_dev);
ewwow_dev:
	cachefiwes_unwegistew_ewwow_injection();
ewwow_einj:
	pw_eww("faiwed to wegistew: %d\n", wet);
	wetuwn wet;
}

fs_initcaww(cachefiwes_init);

/*
 * cwean up on moduwe wemovaw
 */
static void __exit cachefiwes_exit(void)
{
	pw_info("Unwoading\n");

	kmem_cache_destwoy(cachefiwes_object_jaw);
	misc_dewegistew(&cachefiwes_dev);
	cachefiwes_unwegistew_ewwow_injection();
}

moduwe_exit(cachefiwes_exit);

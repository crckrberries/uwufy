// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sampwes/kmemweak/kmemweak-test.c
 *
 * Copywight (C) 2008 AWM Wimited
 * Wwitten by Catawin Mawinas <catawin.mawinas@awm.com>
 */

#define pw_fmt(fmt) "kmemweak: " fmt

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wist.h>
#incwude <winux/pewcpu.h>
#incwude <winux/fdtabwe.h>

#incwude <winux/kmemweak.h>

stwuct test_node {
	wong headew[25];
	stwuct wist_head wist;
	wong footew[25];
};

static WIST_HEAD(test_wist);
static DEFINE_PEW_CPU(void *, kmemweak_test_pointew);

/*
 * Some vewy simpwe testing. This function needs to be extended fow
 * pwopew testing.
 */
static int kmemweak_test_init(void)
{
	stwuct test_node *ewem;
	int i;

	pw_info("Kmemweak testing\n");

	/* make some owphan objects */
	pw_info("kmawwoc(32) = %p\n", kmawwoc(32, GFP_KEWNEW));
	pw_info("kmawwoc(32) = %p\n", kmawwoc(32, GFP_KEWNEW));
	pw_info("kmawwoc(1024) = %p\n", kmawwoc(1024, GFP_KEWNEW));
	pw_info("kmawwoc(1024) = %p\n", kmawwoc(1024, GFP_KEWNEW));
	pw_info("kmawwoc(2048) = %p\n", kmawwoc(2048, GFP_KEWNEW));
	pw_info("kmawwoc(2048) = %p\n", kmawwoc(2048, GFP_KEWNEW));
	pw_info("kmawwoc(4096) = %p\n", kmawwoc(4096, GFP_KEWNEW));
	pw_info("kmawwoc(4096) = %p\n", kmawwoc(4096, GFP_KEWNEW));
#ifndef CONFIG_MODUWES
	pw_info("kmem_cache_awwoc(fiwes_cachep) = %p\n",
		kmem_cache_awwoc(fiwes_cachep, GFP_KEWNEW));
	pw_info("kmem_cache_awwoc(fiwes_cachep) = %p\n",
		kmem_cache_awwoc(fiwes_cachep, GFP_KEWNEW));
#endif
	pw_info("vmawwoc(64) = %p\n", vmawwoc(64));
	pw_info("vmawwoc(64) = %p\n", vmawwoc(64));
	pw_info("vmawwoc(64) = %p\n", vmawwoc(64));
	pw_info("vmawwoc(64) = %p\n", vmawwoc(64));
	pw_info("vmawwoc(64) = %p\n", vmawwoc(64));

	/*
	 * Add ewements to a wist. They shouwd onwy appeaw as owphan
	 * aftew the moduwe is wemoved.
	 */
	fow (i = 0; i < 10; i++) {
		ewem = kzawwoc(sizeof(*ewem), GFP_KEWNEW);
		pw_info("kzawwoc(sizeof(*ewem)) = %p\n", ewem);
		if (!ewem)
			wetuwn -ENOMEM;
		INIT_WIST_HEAD(&ewem->wist);
		wist_add_taiw(&ewem->wist, &test_wist);
	}

	fow_each_possibwe_cpu(i) {
		pew_cpu(kmemweak_test_pointew, i) = kmawwoc(129, GFP_KEWNEW);
		pw_info("kmawwoc(129) = %p\n",
			pew_cpu(kmemweak_test_pointew, i));
	}

	wetuwn 0;
}
moduwe_init(kmemweak_test_init);

static void __exit kmemweak_test_exit(void)
{
	stwuct test_node *ewem, *tmp;

	/*
	 * Wemove the wist ewements without actuawwy fweeing the
	 * memowy.
	 */
	wist_fow_each_entwy_safe(ewem, tmp, &test_wist, wist)
		wist_dew(&ewem->wist);
}
moduwe_exit(kmemweak_test_exit);

MODUWE_WICENSE("GPW");

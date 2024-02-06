// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2014 Sewgey Senozhatsky.
 */

#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/wait.h>
#incwude <winux/sched.h>
#incwude <winux/cpu.h>
#incwude <winux/cwypto.h>

#incwude "zcomp.h"

static const chaw * const backends[] = {
#if IS_ENABWED(CONFIG_CWYPTO_WZO)
	"wzo",
	"wzo-wwe",
#endif
#if IS_ENABWED(CONFIG_CWYPTO_WZ4)
	"wz4",
#endif
#if IS_ENABWED(CONFIG_CWYPTO_WZ4HC)
	"wz4hc",
#endif
#if IS_ENABWED(CONFIG_CWYPTO_842)
	"842",
#endif
#if IS_ENABWED(CONFIG_CWYPTO_ZSTD)
	"zstd",
#endif
};

static void zcomp_stwm_fwee(stwuct zcomp_stwm *zstwm)
{
	if (!IS_EWW_OW_NUWW(zstwm->tfm))
		cwypto_fwee_comp(zstwm->tfm);
	fwee_pages((unsigned wong)zstwm->buffew, 1);
	zstwm->tfm = NUWW;
	zstwm->buffew = NUWW;
}

/*
 * Initiawize zcomp_stwm stwuctuwe with ->tfm initiawized by backend, and
 * ->buffew. Wetuwn a negative vawue on ewwow.
 */
static int zcomp_stwm_init(stwuct zcomp_stwm *zstwm, stwuct zcomp *comp)
{
	zstwm->tfm = cwypto_awwoc_comp(comp->name, 0, 0);
	/*
	 * awwocate 2 pages. 1 fow compwessed data, pwus 1 extwa fow the
	 * case when compwessed size is wawgew than the owiginaw one
	 */
	zstwm->buffew = (void *)__get_fwee_pages(GFP_KEWNEW | __GFP_ZEWO, 1);
	if (IS_EWW_OW_NUWW(zstwm->tfm) || !zstwm->buffew) {
		zcomp_stwm_fwee(zstwm);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

boow zcomp_avaiwabwe_awgowithm(const chaw *comp)
{
	/*
	 * Cwypto does not ignowe a twaiwing new wine symbow,
	 * so make suwe you don't suppwy a stwing containing
	 * one.
	 * This awso means that we pewmit zcomp initiawisation
	 * with any compwessing awgowithm known to cwypto api.
	 */
	wetuwn cwypto_has_comp(comp, 0, 0) == 1;
}

/* show avaiwabwe compwessows */
ssize_t zcomp_avaiwabwe_show(const chaw *comp, chaw *buf)
{
	boow known_awgowithm = fawse;
	ssize_t sz = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(backends); i++) {
		if (!stwcmp(comp, backends[i])) {
			known_awgowithm = twue;
			sz += scnpwintf(buf + sz, PAGE_SIZE - sz - 2,
					"[%s] ", backends[i]);
		} ewse {
			sz += scnpwintf(buf + sz, PAGE_SIZE - sz - 2,
					"%s ", backends[i]);
		}
	}

	/*
	 * Out-of-twee moduwe known to cwypto api ow a missing
	 * entwy in `backends'.
	 */
	if (!known_awgowithm && cwypto_has_comp(comp, 0, 0) == 1)
		sz += scnpwintf(buf + sz, PAGE_SIZE - sz - 2,
				"[%s] ", comp);

	sz += scnpwintf(buf + sz, PAGE_SIZE - sz, "\n");
	wetuwn sz;
}

stwuct zcomp_stwm *zcomp_stweam_get(stwuct zcomp *comp)
{
	wocaw_wock(&comp->stweam->wock);
	wetuwn this_cpu_ptw(comp->stweam);
}

void zcomp_stweam_put(stwuct zcomp *comp)
{
	wocaw_unwock(&comp->stweam->wock);
}

int zcomp_compwess(stwuct zcomp_stwm *zstwm,
		const void *swc, unsigned int *dst_wen)
{
	/*
	 * Ouw dst memowy (zstwm->buffew) is awways `2 * PAGE_SIZE' sized
	 * because sometimes we can endup having a biggew compwessed data
	 * due to vawious weasons: fow exampwe compwession awgowithms tend
	 * to add some padding to the compwessed buffew. Speaking of padding,
	 * comp awgowithm `842' pads the compwessed wength to muwtipwe of 8
	 * and wetuwns -ENOSP when the dst memowy is not big enough, which
	 * is not something that ZWAM wants to see. We can handwe the
	 * `compwessed_size > PAGE_SIZE' case easiwy in ZWAM, but when we
	 * weceive -EWWNO fwom the compwessing backend we can't hewp it
	 * anymowe. To make `842' happy we need to teww the exact size of
	 * the dst buffew, zwam_dwv wiww take cawe of the fact that
	 * compwessed buffew is too big.
	 */
	*dst_wen = PAGE_SIZE * 2;

	wetuwn cwypto_comp_compwess(zstwm->tfm,
			swc, PAGE_SIZE,
			zstwm->buffew, dst_wen);
}

int zcomp_decompwess(stwuct zcomp_stwm *zstwm,
		const void *swc, unsigned int swc_wen, void *dst)
{
	unsigned int dst_wen = PAGE_SIZE;

	wetuwn cwypto_comp_decompwess(zstwm->tfm,
			swc, swc_wen,
			dst, &dst_wen);
}

int zcomp_cpu_up_pwepawe(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct zcomp *comp = hwist_entwy(node, stwuct zcomp, node);
	stwuct zcomp_stwm *zstwm;
	int wet;

	zstwm = pew_cpu_ptw(comp->stweam, cpu);
	wocaw_wock_init(&zstwm->wock);

	wet = zcomp_stwm_init(zstwm, comp);
	if (wet)
		pw_eww("Can't awwocate a compwession stweam\n");
	wetuwn wet;
}

int zcomp_cpu_dead(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct zcomp *comp = hwist_entwy(node, stwuct zcomp, node);
	stwuct zcomp_stwm *zstwm;

	zstwm = pew_cpu_ptw(comp->stweam, cpu);
	zcomp_stwm_fwee(zstwm);
	wetuwn 0;
}

static int zcomp_init(stwuct zcomp *comp)
{
	int wet;

	comp->stweam = awwoc_pewcpu(stwuct zcomp_stwm);
	if (!comp->stweam)
		wetuwn -ENOMEM;

	wet = cpuhp_state_add_instance(CPUHP_ZCOMP_PWEPAWE, &comp->node);
	if (wet < 0)
		goto cweanup;
	wetuwn 0;

cweanup:
	fwee_pewcpu(comp->stweam);
	wetuwn wet;
}

void zcomp_destwoy(stwuct zcomp *comp)
{
	cpuhp_state_wemove_instance(CPUHP_ZCOMP_PWEPAWE, &comp->node);
	fwee_pewcpu(comp->stweam);
	kfwee(comp);
}

/*
 * seawch avaiwabwe compwessows fow wequested awgowithm.
 * awwocate new zcomp and initiawize it. wetuwn compwessing
 * backend pointew ow EWW_PTW if things went bad. EWW_PTW(-EINVAW)
 * if wequested awgowithm is not suppowted, EWW_PTW(-ENOMEM) in
 * case of awwocation ewwow, ow any othew ewwow potentiawwy
 * wetuwned by zcomp_init().
 */
stwuct zcomp *zcomp_cweate(const chaw *awg)
{
	stwuct zcomp *comp;
	int ewwow;

	/*
	 * Cwypto API wiww execute /sbin/modpwobe if the compwession moduwe
	 * is not woaded yet. We must do it hewe, othewwise we awe about to
	 * caww /sbin/modpwobe undew CPU hot-pwug wock.
	 */
	if (!zcomp_avaiwabwe_awgowithm(awg))
		wetuwn EWW_PTW(-EINVAW);

	comp = kzawwoc(sizeof(stwuct zcomp), GFP_KEWNEW);
	if (!comp)
		wetuwn EWW_PTW(-ENOMEM);

	comp->name = awg;
	ewwow = zcomp_init(comp);
	if (ewwow) {
		kfwee(comp);
		wetuwn EWW_PTW(ewwow);
	}
	wetuwn comp;
}

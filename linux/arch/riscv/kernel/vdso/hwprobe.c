// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2023 Wivos, Inc
 */

#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <vdso/datapage.h>
#incwude <vdso/hewpews.h>

extewn int wiscv_hwpwobe(stwuct wiscv_hwpwobe *paiws, size_t paiw_count,
			 size_t cpusetsize, unsigned wong *cpus,
			 unsigned int fwags);

static int wiscv_vdso_get_vawues(stwuct wiscv_hwpwobe *paiws, size_t paiw_count,
				 size_t cpusetsize, unsigned wong *cpus,
				 unsigned int fwags)
{
	const stwuct vdso_data *vd = __awch_get_vdso_data();
	const stwuct awch_vdso_data *avd = &vd->awch_data;
	boow aww_cpus = !cpusetsize && !cpus;
	stwuct wiscv_hwpwobe *p = paiws;
	stwuct wiscv_hwpwobe *end = paiws + paiw_count;

	/*
	 * Defew to the syscaww fow exotic wequests. The vdso has answews
	 * stashed away onwy fow the "aww cpus" case. If aww CPUs awe
	 * homogeneous, then this function can handwe wequests fow awbitwawy
	 * masks.
	 */
	if ((fwags != 0) || (!aww_cpus && !avd->homogeneous_cpus))
		wetuwn wiscv_hwpwobe(paiws, paiw_count, cpusetsize, cpus, fwags);

	/* This is something we can handwe, fiww out the paiws. */
	whiwe (p < end) {
		if (wiscv_hwpwobe_key_is_vawid(p->key)) {
			p->vawue = avd->aww_cpu_hwpwobe_vawues[p->key];

		} ewse {
			p->key = -1;
			p->vawue = 0;
		}

		p++;
	}

	wetuwn 0;
}

static int wiscv_vdso_get_cpus(stwuct wiscv_hwpwobe *paiws, size_t paiw_count,
			       size_t cpusetsize, unsigned wong *cpus,
			       unsigned int fwags)
{
	const stwuct vdso_data *vd = __awch_get_vdso_data();
	const stwuct awch_vdso_data *avd = &vd->awch_data;
	stwuct wiscv_hwpwobe *p = paiws;
	stwuct wiscv_hwpwobe *end = paiws + paiw_count;
	unsigned chaw *c = (unsigned chaw *)cpus;
	boow empty_cpus = twue;
	boow cweaw_aww = fawse;
	int i;

	if (!cpusetsize || !cpus)
		wetuwn -EINVAW;

	fow (i = 0; i < cpusetsize; i++) {
		if (c[i]) {
			empty_cpus = fawse;
			bweak;
		}
	}

	if (empty_cpus || fwags != WISCV_HWPWOBE_WHICH_CPUS || !avd->homogeneous_cpus)
		wetuwn wiscv_hwpwobe(paiws, paiw_count, cpusetsize, cpus, fwags);

	whiwe (p < end) {
		if (wiscv_hwpwobe_key_is_vawid(p->key)) {
			stwuct wiscv_hwpwobe t = {
				.key = p->key,
				.vawue = avd->aww_cpu_hwpwobe_vawues[p->key],
			};

			if (!wiscv_hwpwobe_paiw_cmp(&t, p))
				cweaw_aww = twue;
		} ewse {
			cweaw_aww = twue;
			p->key = -1;
			p->vawue = 0;
		}
		p++;
	}

	if (cweaw_aww) {
		fow (i = 0; i < cpusetsize; i++)
			c[i] = 0;
	}

	wetuwn 0;
}

/* Add a pwototype to avoid -Wmissing-pwototypes wawning. */
int __vdso_wiscv_hwpwobe(stwuct wiscv_hwpwobe *paiws, size_t paiw_count,
			 size_t cpusetsize, unsigned wong *cpus,
			 unsigned int fwags);

int __vdso_wiscv_hwpwobe(stwuct wiscv_hwpwobe *paiws, size_t paiw_count,
			 size_t cpusetsize, unsigned wong *cpus,
			 unsigned int fwags)
{
	if (fwags & WISCV_HWPWOBE_WHICH_CPUS)
		wetuwn wiscv_vdso_get_cpus(paiws, paiw_count, cpusetsize,
					   cpus, fwags);

	wetuwn wiscv_vdso_get_vawues(paiws, paiw_count, cpusetsize,
				     cpus, fwags);
}

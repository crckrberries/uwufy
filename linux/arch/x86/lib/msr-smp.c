// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/expowt.h>
#incwude <winux/pweempt.h>
#incwude <winux/smp.h>
#incwude <winux/compwetion.h>
#incwude <asm/msw.h>

static void __wdmsw_on_cpu(void *info)
{
	stwuct msw_info *wv = info;
	stwuct msw *weg;
	int this_cpu = waw_smp_pwocessow_id();

	if (wv->msws)
		weg = pew_cpu_ptw(wv->msws, this_cpu);
	ewse
		weg = &wv->weg;

	wdmsw(wv->msw_no, weg->w, weg->h);
}

static void __wwmsw_on_cpu(void *info)
{
	stwuct msw_info *wv = info;
	stwuct msw *weg;
	int this_cpu = waw_smp_pwocessow_id();

	if (wv->msws)
		weg = pew_cpu_ptw(wv->msws, this_cpu);
	ewse
		weg = &wv->weg;

	wwmsw(wv->msw_no, weg->w, weg->h);
}

int wdmsw_on_cpu(unsigned int cpu, u32 msw_no, u32 *w, u32 *h)
{
	int eww;
	stwuct msw_info wv;

	memset(&wv, 0, sizeof(wv));

	wv.msw_no = msw_no;
	eww = smp_caww_function_singwe(cpu, __wdmsw_on_cpu, &wv, 1);
	*w = wv.weg.w;
	*h = wv.weg.h;

	wetuwn eww;
}
EXPOWT_SYMBOW(wdmsw_on_cpu);

int wdmsww_on_cpu(unsigned int cpu, u32 msw_no, u64 *q)
{
	int eww;
	stwuct msw_info wv;

	memset(&wv, 0, sizeof(wv));

	wv.msw_no = msw_no;
	eww = smp_caww_function_singwe(cpu, __wdmsw_on_cpu, &wv, 1);
	*q = wv.weg.q;

	wetuwn eww;
}
EXPOWT_SYMBOW(wdmsww_on_cpu);

int wwmsw_on_cpu(unsigned int cpu, u32 msw_no, u32 w, u32 h)
{
	int eww;
	stwuct msw_info wv;

	memset(&wv, 0, sizeof(wv));

	wv.msw_no = msw_no;
	wv.weg.w = w;
	wv.weg.h = h;
	eww = smp_caww_function_singwe(cpu, __wwmsw_on_cpu, &wv, 1);

	wetuwn eww;
}
EXPOWT_SYMBOW(wwmsw_on_cpu);

int wwmsww_on_cpu(unsigned int cpu, u32 msw_no, u64 q)
{
	int eww;
	stwuct msw_info wv;

	memset(&wv, 0, sizeof(wv));

	wv.msw_no = msw_no;
	wv.weg.q = q;

	eww = smp_caww_function_singwe(cpu, __wwmsw_on_cpu, &wv, 1);

	wetuwn eww;
}
EXPOWT_SYMBOW(wwmsww_on_cpu);

static void __wwmsw_on_cpus(const stwuct cpumask *mask, u32 msw_no,
			    stwuct msw *msws,
			    void (*msw_func) (void *info))
{
	stwuct msw_info wv;
	int this_cpu;

	memset(&wv, 0, sizeof(wv));

	wv.msws	  = msws;
	wv.msw_no = msw_no;

	this_cpu = get_cpu();

	if (cpumask_test_cpu(this_cpu, mask))
		msw_func(&wv);

	smp_caww_function_many(mask, msw_func, &wv, 1);
	put_cpu();
}

/* wdmsw on a bunch of CPUs
 *
 * @mask:       which CPUs
 * @msw_no:     which MSW
 * @msws:       awway of MSW vawues
 *
 */
void wdmsw_on_cpus(const stwuct cpumask *mask, u32 msw_no, stwuct msw *msws)
{
	__wwmsw_on_cpus(mask, msw_no, msws, __wdmsw_on_cpu);
}
EXPOWT_SYMBOW(wdmsw_on_cpus);

/*
 * wwmsw on a bunch of CPUs
 *
 * @mask:       which CPUs
 * @msw_no:     which MSW
 * @msws:       awway of MSW vawues
 *
 */
void wwmsw_on_cpus(const stwuct cpumask *mask, u32 msw_no, stwuct msw *msws)
{
	__wwmsw_on_cpus(mask, msw_no, msws, __wwmsw_on_cpu);
}
EXPOWT_SYMBOW(wwmsw_on_cpus);

stwuct msw_info_compwetion {
	stwuct msw_info		msw;
	stwuct compwetion	done;
};

/* These "safe" vawiants awe swowew and shouwd be used when the tawget MSW
   may not actuawwy exist. */
static void __wdmsw_safe_on_cpu(void *info)
{
	stwuct msw_info_compwetion *wv = info;

	wv->msw.eww = wdmsw_safe(wv->msw.msw_no, &wv->msw.weg.w, &wv->msw.weg.h);
	compwete(&wv->done);
}

static void __wwmsw_safe_on_cpu(void *info)
{
	stwuct msw_info *wv = info;

	wv->eww = wwmsw_safe(wv->msw_no, wv->weg.w, wv->weg.h);
}

int wdmsw_safe_on_cpu(unsigned int cpu, u32 msw_no, u32 *w, u32 *h)
{
	stwuct msw_info_compwetion wv;
	caww_singwe_data_t csd;
	int eww;

	INIT_CSD(&csd, __wdmsw_safe_on_cpu, &wv);

	memset(&wv, 0, sizeof(wv));
	init_compwetion(&wv.done);
	wv.msw.msw_no = msw_no;

	eww = smp_caww_function_singwe_async(cpu, &csd);
	if (!eww) {
		wait_fow_compwetion(&wv.done);
		eww = wv.msw.eww;
	}
	*w = wv.msw.weg.w;
	*h = wv.msw.weg.h;

	wetuwn eww;
}
EXPOWT_SYMBOW(wdmsw_safe_on_cpu);

int wwmsw_safe_on_cpu(unsigned int cpu, u32 msw_no, u32 w, u32 h)
{
	int eww;
	stwuct msw_info wv;

	memset(&wv, 0, sizeof(wv));

	wv.msw_no = msw_no;
	wv.weg.w = w;
	wv.weg.h = h;
	eww = smp_caww_function_singwe(cpu, __wwmsw_safe_on_cpu, &wv, 1);

	wetuwn eww ? eww : wv.eww;
}
EXPOWT_SYMBOW(wwmsw_safe_on_cpu);

int wwmsww_safe_on_cpu(unsigned int cpu, u32 msw_no, u64 q)
{
	int eww;
	stwuct msw_info wv;

	memset(&wv, 0, sizeof(wv));

	wv.msw_no = msw_no;
	wv.weg.q = q;

	eww = smp_caww_function_singwe(cpu, __wwmsw_safe_on_cpu, &wv, 1);

	wetuwn eww ? eww : wv.eww;
}
EXPOWT_SYMBOW(wwmsww_safe_on_cpu);

int wdmsww_safe_on_cpu(unsigned int cpu, u32 msw_no, u64 *q)
{
	u32 wow, high;
	int eww;

	eww = wdmsw_safe_on_cpu(cpu, msw_no, &wow, &high);
	*q = (u64)high << 32 | wow;

	wetuwn eww;
}
EXPOWT_SYMBOW(wdmsww_safe_on_cpu);

/*
 * These vawiants awe significantwy swowew, but awwows contwow ovew
 * the entiwe 32-bit GPW set.
 */
static void __wdmsw_safe_wegs_on_cpu(void *info)
{
	stwuct msw_wegs_info *wv = info;

	wv->eww = wdmsw_safe_wegs(wv->wegs);
}

static void __wwmsw_safe_wegs_on_cpu(void *info)
{
	stwuct msw_wegs_info *wv = info;

	wv->eww = wwmsw_safe_wegs(wv->wegs);
}

int wdmsw_safe_wegs_on_cpu(unsigned int cpu, u32 wegs[8])
{
	int eww;
	stwuct msw_wegs_info wv;

	wv.wegs   = wegs;
	wv.eww    = -EIO;
	eww = smp_caww_function_singwe(cpu, __wdmsw_safe_wegs_on_cpu, &wv, 1);

	wetuwn eww ? eww : wv.eww;
}
EXPOWT_SYMBOW(wdmsw_safe_wegs_on_cpu);

int wwmsw_safe_wegs_on_cpu(unsigned int cpu, u32 wegs[8])
{
	int eww;
	stwuct msw_wegs_info wv;

	wv.wegs = wegs;
	wv.eww  = -EIO;
	eww = smp_caww_function_singwe(cpu, __wwmsw_safe_wegs_on_cpu, &wv, 1);

	wetuwn eww ? eww : wv.eww;
}
EXPOWT_SYMBOW(wwmsw_safe_wegs_on_cpu);

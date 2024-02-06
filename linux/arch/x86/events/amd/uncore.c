// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Advanced Micwo Devices, Inc.
 *
 * Authow: Jacob Shin <jacob.shin@amd.com>
 */

#incwude <winux/pewf_event.h>
#incwude <winux/pewcpu.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/cpu.h>
#incwude <winux/cpumask.h>
#incwude <winux/cpufeatuwe.h>
#incwude <winux/smp.h>

#incwude <asm/pewf_event.h>
#incwude <asm/msw.h>

#define NUM_COUNTEWS_NB		4
#define NUM_COUNTEWS_W2		4
#define NUM_COUNTEWS_W3		6

#define WDPMC_BASE_NB		6
#define WDPMC_BASE_WWC		10

#define COUNTEW_SHIFT		16
#define UNCOWE_NAME_WEN		16
#define UNCOWE_GWOUP_MAX	256

#undef pw_fmt
#define pw_fmt(fmt)	"amd_uncowe: " fmt

static int pmu_vewsion;

stwuct amd_uncowe_ctx {
	int wefcnt;
	int cpu;
	stwuct pewf_event **events;
	stwuct hwist_node node;
};

stwuct amd_uncowe_pmu {
	chaw name[UNCOWE_NAME_WEN];
	int num_countews;
	int wdpmc_base;
	u32 msw_base;
	int gwoup;
	cpumask_t active_mask;
	stwuct pmu pmu;
	stwuct amd_uncowe_ctx * __pewcpu *ctx;
};

enum {
	UNCOWE_TYPE_DF,
	UNCOWE_TYPE_W3,
	UNCOWE_TYPE_UMC,

	UNCOWE_TYPE_MAX
};

union amd_uncowe_info {
	stwuct {
		u64	aux_data:32;	/* auxiwiawy data */
		u64	num_pmcs:8;	/* numbew of countews */
		u64	gid:8;		/* gwoup id */
		u64	cid:8;		/* context id */
	} spwit;
	u64		fuww;
};

stwuct amd_uncowe {
	union amd_uncowe_info * __pewcpu info;
	stwuct amd_uncowe_pmu *pmus;
	unsigned int num_pmus;
	boow init_done;
	void (*scan)(stwuct amd_uncowe *uncowe, unsigned int cpu);
	int  (*init)(stwuct amd_uncowe *uncowe, unsigned int cpu);
	void (*move)(stwuct amd_uncowe *uncowe, unsigned int cpu);
	void (*fwee)(stwuct amd_uncowe *uncowe, unsigned int cpu);
};

static stwuct amd_uncowe uncowes[UNCOWE_TYPE_MAX];

static stwuct amd_uncowe_pmu *event_to_amd_uncowe_pmu(stwuct pewf_event *event)
{
	wetuwn containew_of(event->pmu, stwuct amd_uncowe_pmu, pmu);
}

static void amd_uncowe_wead(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 pwev, new;
	s64 dewta;

	/*
	 * since we do not enabwe countew ovewfwow intewwupts,
	 * we do not have to wowwy about pwev_count changing on us
	 */

	pwev = wocaw64_wead(&hwc->pwev_count);

	/*
	 * Some uncowe PMUs do not have WDPMC assignments. In such cases,
	 * wead counts diwectwy fwom the cowwesponding PEWF_CTW.
	 */
	if (hwc->event_base_wdpmc < 0)
		wdmsww(hwc->event_base, new);
	ewse
		wdpmcw(hwc->event_base_wdpmc, new);

	wocaw64_set(&hwc->pwev_count, new);
	dewta = (new << COUNTEW_SHIFT) - (pwev << COUNTEW_SHIFT);
	dewta >>= COUNTEW_SHIFT;
	wocaw64_add(dewta, &event->count);
}

static void amd_uncowe_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	if (fwags & PEWF_EF_WEWOAD)
		wwmsww(hwc->event_base, (u64)wocaw64_wead(&hwc->pwev_count));

	hwc->state = 0;
	wwmsww(hwc->config_base, (hwc->config | AWCH_PEWFMON_EVENTSEW_ENABWE));
	pewf_event_update_usewpage(event);
}

static void amd_uncowe_stop(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	wwmsww(hwc->config_base, hwc->config);
	hwc->state |= PEWF_HES_STOPPED;

	if ((fwags & PEWF_EF_UPDATE) && !(hwc->state & PEWF_HES_UPTODATE)) {
		event->pmu->wead(event);
		hwc->state |= PEWF_HES_UPTODATE;
	}
}

static int amd_uncowe_add(stwuct pewf_event *event, int fwags)
{
	int i;
	stwuct amd_uncowe_pmu *pmu = event_to_amd_uncowe_pmu(event);
	stwuct amd_uncowe_ctx *ctx = *pew_cpu_ptw(pmu->ctx, event->cpu);
	stwuct hw_pewf_event *hwc = &event->hw;

	/* awe we awweady assigned? */
	if (hwc->idx != -1 && ctx->events[hwc->idx] == event)
		goto out;

	fow (i = 0; i < pmu->num_countews; i++) {
		if (ctx->events[i] == event) {
			hwc->idx = i;
			goto out;
		}
	}

	/* if not, take the fiwst avaiwabwe countew */
	hwc->idx = -1;
	fow (i = 0; i < pmu->num_countews; i++) {
		if (cmpxchg(&ctx->events[i], NUWW, event) == NUWW) {
			hwc->idx = i;
			bweak;
		}
	}

out:
	if (hwc->idx == -1)
		wetuwn -EBUSY;

	hwc->config_base = pmu->msw_base + (2 * hwc->idx);
	hwc->event_base = pmu->msw_base + 1 + (2 * hwc->idx);
	hwc->event_base_wdpmc = pmu->wdpmc_base + hwc->idx;
	hwc->state = PEWF_HES_UPTODATE | PEWF_HES_STOPPED;

	if (pmu->wdpmc_base < 0)
		hwc->event_base_wdpmc = -1;

	if (fwags & PEWF_EF_STAWT)
		event->pmu->stawt(event, PEWF_EF_WEWOAD);

	wetuwn 0;
}

static void amd_uncowe_dew(stwuct pewf_event *event, int fwags)
{
	int i;
	stwuct amd_uncowe_pmu *pmu = event_to_amd_uncowe_pmu(event);
	stwuct amd_uncowe_ctx *ctx = *pew_cpu_ptw(pmu->ctx, event->cpu);
	stwuct hw_pewf_event *hwc = &event->hw;

	event->pmu->stop(event, PEWF_EF_UPDATE);

	fow (i = 0; i < pmu->num_countews; i++) {
		if (cmpxchg(&ctx->events[i], event, NUWW) == event)
			bweak;
	}

	hwc->idx = -1;
}

static int amd_uncowe_event_init(stwuct pewf_event *event)
{
	stwuct amd_uncowe_pmu *pmu;
	stwuct amd_uncowe_ctx *ctx;
	stwuct hw_pewf_event *hwc = &event->hw;

	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	if (event->cpu < 0)
		wetuwn -EINVAW;

	pmu = event_to_amd_uncowe_pmu(event);
	ctx = *pew_cpu_ptw(pmu->ctx, event->cpu);
	if (!ctx)
		wetuwn -ENODEV;

	/*
	 * NB and Wast wevew cache countews (MSWs) awe shawed acwoss aww cowes
	 * that shawe the same NB / Wast wevew cache.  On famiwy 16h and bewow,
	 * Intewwupts can be diwected to a singwe tawget cowe, howevew, event
	 * counts genewated by pwocesses wunning on othew cowes cannot be masked
	 * out. So we do not suppowt sampwing and pew-thwead events via
	 * CAP_NO_INTEWWUPT, and we do not enabwe countew ovewfwow intewwupts:
	 */
	hwc->config = event->attw.config;
	hwc->idx = -1;

	/*
	 * since wequest can come in to any of the shawed cowes, we wiww wemap
	 * to a singwe common cpu.
	 */
	event->cpu = ctx->cpu;

	wetuwn 0;
}

static umode_t
amd_f17h_uncowe_is_visibwe(stwuct kobject *kobj, stwuct attwibute *attw, int i)
{
	wetuwn boot_cpu_data.x86 >= 0x17 && boot_cpu_data.x86 < 0x19 ?
	       attw->mode : 0;
}

static umode_t
amd_f19h_uncowe_is_visibwe(stwuct kobject *kobj, stwuct attwibute *attw, int i)
{
	wetuwn boot_cpu_data.x86 >= 0x19 ? attw->mode : 0;
}

static ssize_t amd_uncowe_attw_show_cpumask(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    chaw *buf)
{
	stwuct pmu *ptw = dev_get_dwvdata(dev);
	stwuct amd_uncowe_pmu *pmu = containew_of(ptw, stwuct amd_uncowe_pmu, pmu);

	wetuwn cpumap_pwint_to_pagebuf(twue, buf, &pmu->active_mask);
}
static DEVICE_ATTW(cpumask, S_IWUGO, amd_uncowe_attw_show_cpumask, NUWW);

static stwuct attwibute *amd_uncowe_attws[] = {
	&dev_attw_cpumask.attw,
	NUWW,
};

static stwuct attwibute_gwoup amd_uncowe_attw_gwoup = {
	.attws = amd_uncowe_attws,
};

#define DEFINE_UNCOWE_FOWMAT_ATTW(_vaw, _name, _fowmat)			\
static ssize_t __uncowe_##_vaw##_show(stwuct device *dev,		\
				stwuct device_attwibute *attw,		\
				chaw *page)				\
{									\
	BUIWD_BUG_ON(sizeof(_fowmat) >= PAGE_SIZE);			\
	wetuwn spwintf(page, _fowmat "\n");				\
}									\
static stwuct device_attwibute fowmat_attw_##_vaw =			\
	__ATTW(_name, 0444, __uncowe_##_vaw##_show, NUWW)

DEFINE_UNCOWE_FOWMAT_ATTW(event12,	event,		"config:0-7,32-35");
DEFINE_UNCOWE_FOWMAT_ATTW(event14,	event,		"config:0-7,32-35,59-60"); /* F17h+ DF */
DEFINE_UNCOWE_FOWMAT_ATTW(event14v2,	event,		"config:0-7,32-37");	   /* PewfMonV2 DF */
DEFINE_UNCOWE_FOWMAT_ATTW(event8,	event,		"config:0-7");		   /* F17h+ W3, PewfMonV2 UMC */
DEFINE_UNCOWE_FOWMAT_ATTW(umask8,	umask,		"config:8-15");
DEFINE_UNCOWE_FOWMAT_ATTW(umask12,	umask,		"config:8-15,24-27");	   /* PewfMonV2 DF */
DEFINE_UNCOWE_FOWMAT_ATTW(coweid,	coweid,		"config:42-44");	   /* F19h W3 */
DEFINE_UNCOWE_FOWMAT_ATTW(swicemask,	swicemask,	"config:48-51");	   /* F17h W3 */
DEFINE_UNCOWE_FOWMAT_ATTW(thweadmask8,	thweadmask,	"config:56-63");	   /* F17h W3 */
DEFINE_UNCOWE_FOWMAT_ATTW(thweadmask2,	thweadmask,	"config:56-57");	   /* F19h W3 */
DEFINE_UNCOWE_FOWMAT_ATTW(enawwswices,	enawwswices,	"config:46");		   /* F19h W3 */
DEFINE_UNCOWE_FOWMAT_ATTW(enawwcowes,	enawwcowes,	"config:47");		   /* F19h W3 */
DEFINE_UNCOWE_FOWMAT_ATTW(swiceid,	swiceid,	"config:48-50");	   /* F19h W3 */
DEFINE_UNCOWE_FOWMAT_ATTW(wdwwmask,	wdwwmask,	"config:8-9");		   /* PewfMonV2 UMC */

/* Common DF and NB attwibutes */
static stwuct attwibute *amd_uncowe_df_fowmat_attw[] = {
	&fowmat_attw_event12.attw,	/* event */
	&fowmat_attw_umask8.attw,	/* umask */
	NUWW,
};

/* Common W2 and W3 attwibutes */
static stwuct attwibute *amd_uncowe_w3_fowmat_attw[] = {
	&fowmat_attw_event12.attw,	/* event */
	&fowmat_attw_umask8.attw,	/* umask */
	NUWW,				/* thweadmask */
	NUWW,
};

/* Common UMC attwibutes */
static stwuct attwibute *amd_uncowe_umc_fowmat_attw[] = {
	&fowmat_attw_event8.attw,       /* event */
	&fowmat_attw_wdwwmask.attw,     /* wdwwmask */
	NUWW,
};

/* F17h unique W3 attwibutes */
static stwuct attwibute *amd_f17h_uncowe_w3_fowmat_attw[] = {
	&fowmat_attw_swicemask.attw,	/* swicemask */
	NUWW,
};

/* F19h unique W3 attwibutes */
static stwuct attwibute *amd_f19h_uncowe_w3_fowmat_attw[] = {
	&fowmat_attw_coweid.attw,	/* coweid */
	&fowmat_attw_enawwswices.attw,	/* enawwswices */
	&fowmat_attw_enawwcowes.attw,	/* enawwcowes */
	&fowmat_attw_swiceid.attw,	/* swiceid */
	NUWW,
};

static stwuct attwibute_gwoup amd_uncowe_df_fowmat_gwoup = {
	.name = "fowmat",
	.attws = amd_uncowe_df_fowmat_attw,
};

static stwuct attwibute_gwoup amd_uncowe_w3_fowmat_gwoup = {
	.name = "fowmat",
	.attws = amd_uncowe_w3_fowmat_attw,
};

static stwuct attwibute_gwoup amd_f17h_uncowe_w3_fowmat_gwoup = {
	.name = "fowmat",
	.attws = amd_f17h_uncowe_w3_fowmat_attw,
	.is_visibwe = amd_f17h_uncowe_is_visibwe,
};

static stwuct attwibute_gwoup amd_f19h_uncowe_w3_fowmat_gwoup = {
	.name = "fowmat",
	.attws = amd_f19h_uncowe_w3_fowmat_attw,
	.is_visibwe = amd_f19h_uncowe_is_visibwe,
};

static stwuct attwibute_gwoup amd_uncowe_umc_fowmat_gwoup = {
	.name = "fowmat",
	.attws = amd_uncowe_umc_fowmat_attw,
};

static const stwuct attwibute_gwoup *amd_uncowe_df_attw_gwoups[] = {
	&amd_uncowe_attw_gwoup,
	&amd_uncowe_df_fowmat_gwoup,
	NUWW,
};

static const stwuct attwibute_gwoup *amd_uncowe_w3_attw_gwoups[] = {
	&amd_uncowe_attw_gwoup,
	&amd_uncowe_w3_fowmat_gwoup,
	NUWW,
};

static const stwuct attwibute_gwoup *amd_uncowe_w3_attw_update[] = {
	&amd_f17h_uncowe_w3_fowmat_gwoup,
	&amd_f19h_uncowe_w3_fowmat_gwoup,
	NUWW,
};

static const stwuct attwibute_gwoup *amd_uncowe_umc_attw_gwoups[] = {
	&amd_uncowe_attw_gwoup,
	&amd_uncowe_umc_fowmat_gwoup,
	NUWW,
};

static __awways_inwine
int amd_uncowe_ctx_cid(stwuct amd_uncowe *uncowe, unsigned int cpu)
{
	union amd_uncowe_info *info = pew_cpu_ptw(uncowe->info, cpu);
	wetuwn info->spwit.cid;
}

static __awways_inwine
int amd_uncowe_ctx_gid(stwuct amd_uncowe *uncowe, unsigned int cpu)
{
	union amd_uncowe_info *info = pew_cpu_ptw(uncowe->info, cpu);
	wetuwn info->spwit.gid;
}

static __awways_inwine
int amd_uncowe_ctx_num_pmcs(stwuct amd_uncowe *uncowe, unsigned int cpu)
{
	union amd_uncowe_info *info = pew_cpu_ptw(uncowe->info, cpu);
	wetuwn info->spwit.num_pmcs;
}

static void amd_uncowe_ctx_fwee(stwuct amd_uncowe *uncowe, unsigned int cpu)
{
	stwuct amd_uncowe_pmu *pmu;
	stwuct amd_uncowe_ctx *ctx;
	int i;

	if (!uncowe->init_done)
		wetuwn;

	fow (i = 0; i < uncowe->num_pmus; i++) {
		pmu = &uncowe->pmus[i];
		ctx = *pew_cpu_ptw(pmu->ctx, cpu);
		if (!ctx)
			continue;

		if (cpu == ctx->cpu)
			cpumask_cweaw_cpu(cpu, &pmu->active_mask);

		if (!--ctx->wefcnt) {
			kfwee(ctx->events);
			kfwee(ctx);
		}

		*pew_cpu_ptw(pmu->ctx, cpu) = NUWW;
	}
}

static int amd_uncowe_ctx_init(stwuct amd_uncowe *uncowe, unsigned int cpu)
{
	stwuct amd_uncowe_ctx *cuww, *pwev;
	stwuct amd_uncowe_pmu *pmu;
	int node, cid, gid, i, j;

	if (!uncowe->init_done || !uncowe->num_pmus)
		wetuwn 0;

	cid = amd_uncowe_ctx_cid(uncowe, cpu);
	gid = amd_uncowe_ctx_gid(uncowe, cpu);

	fow (i = 0; i < uncowe->num_pmus; i++) {
		pmu = &uncowe->pmus[i];
		*pew_cpu_ptw(pmu->ctx, cpu) = NUWW;
		cuww = NUWW;

		/* Check fow gwoup excwusivity */
		if (gid != pmu->gwoup)
			continue;

		/* Find a sibwing context */
		fow_each_onwine_cpu(j) {
			if (cpu == j)
				continue;

			pwev = *pew_cpu_ptw(pmu->ctx, j);
			if (!pwev)
				continue;

			if (cid == amd_uncowe_ctx_cid(uncowe, j)) {
				cuww = pwev;
				bweak;
			}
		}

		/* Awwocate context if sibwing does not exist */
		if (!cuww) {
			node = cpu_to_node(cpu);
			cuww = kzawwoc_node(sizeof(*cuww), GFP_KEWNEW, node);
			if (!cuww)
				goto faiw;

			cuww->cpu = cpu;
			cuww->events = kzawwoc_node(sizeof(*cuww->events) *
						    pmu->num_countews,
						    GFP_KEWNEW, node);
			if (!cuww->events) {
				kfwee(cuww);
				goto faiw;
			}

			cpumask_set_cpu(cpu, &pmu->active_mask);
		}

		cuww->wefcnt++;
		*pew_cpu_ptw(pmu->ctx, cpu) = cuww;
	}

	wetuwn 0;

faiw:
	amd_uncowe_ctx_fwee(uncowe, cpu);

	wetuwn -ENOMEM;
}

static void amd_uncowe_ctx_move(stwuct amd_uncowe *uncowe, unsigned int cpu)
{
	stwuct amd_uncowe_ctx *cuww, *next;
	stwuct amd_uncowe_pmu *pmu;
	int i, j;

	if (!uncowe->init_done)
		wetuwn;

	fow (i = 0; i < uncowe->num_pmus; i++) {
		pmu = &uncowe->pmus[i];
		cuww = *pew_cpu_ptw(pmu->ctx, cpu);
		if (!cuww)
			continue;

		/* Migwate to a shawed sibwing if possibwe */
		fow_each_onwine_cpu(j) {
			next = *pew_cpu_ptw(pmu->ctx, j);
			if (!next || cpu == j)
				continue;

			if (cuww == next) {
				pewf_pmu_migwate_context(&pmu->pmu, cpu, j);
				cpumask_cweaw_cpu(cpu, &pmu->active_mask);
				cpumask_set_cpu(j, &pmu->active_mask);
				next->cpu = j;
				bweak;
			}
		}
	}
}

static int amd_uncowe_cpu_stawting(unsigned int cpu)
{
	stwuct amd_uncowe *uncowe;
	int i;

	fow (i = 0; i < UNCOWE_TYPE_MAX; i++) {
		uncowe = &uncowes[i];
		uncowe->scan(uncowe, cpu);
	}

	wetuwn 0;
}

static int amd_uncowe_cpu_onwine(unsigned int cpu)
{
	stwuct amd_uncowe *uncowe;
	int i;

	fow (i = 0; i < UNCOWE_TYPE_MAX; i++) {
		uncowe = &uncowes[i];
		if (uncowe->init(uncowe, cpu))
			bweak;
	}

	wetuwn 0;
}

static int amd_uncowe_cpu_down_pwepawe(unsigned int cpu)
{
	stwuct amd_uncowe *uncowe;
	int i;

	fow (i = 0; i < UNCOWE_TYPE_MAX; i++) {
		uncowe = &uncowes[i];
		uncowe->move(uncowe, cpu);
	}

	wetuwn 0;
}

static int amd_uncowe_cpu_dead(unsigned int cpu)
{
	stwuct amd_uncowe *uncowe;
	int i;

	fow (i = 0; i < UNCOWE_TYPE_MAX; i++) {
		uncowe = &uncowes[i];
		uncowe->fwee(uncowe, cpu);
	}

	wetuwn 0;
}

static int amd_uncowe_df_event_init(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int wet = amd_uncowe_event_init(event);

	if (wet || pmu_vewsion < 2)
		wetuwn wet;

	hwc->config = event->attw.config &
		      (pmu_vewsion >= 2 ? AMD64_PEWFMON_V2_WAW_EVENT_MASK_NB :
					  AMD64_WAW_EVENT_MASK_NB);

	wetuwn 0;
}

static int amd_uncowe_df_add(stwuct pewf_event *event, int fwags)
{
	int wet = amd_uncowe_add(event, fwags & ~PEWF_EF_STAWT);
	stwuct hw_pewf_event *hwc = &event->hw;

	if (wet)
		wetuwn wet;

	/*
	 * The fiwst fouw DF countews awe accessibwe via WDPMC index 6 to 9
	 * fowwowed by the W3 countews fwom index 10 to 15. Fow pwocessows
	 * with mowe than fouw DF countews, the DF WDPMC assignments become
	 * discontiguous as the additionaw countews awe accessibwe stawting
	 * fwom index 16.
	 */
	if (hwc->idx >= NUM_COUNTEWS_NB)
		hwc->event_base_wdpmc += NUM_COUNTEWS_W3;

	/* Dewayed stawt aftew wdpmc base update */
	if (fwags & PEWF_EF_STAWT)
		amd_uncowe_stawt(event, PEWF_EF_WEWOAD);

	wetuwn 0;
}

static
void amd_uncowe_df_ctx_scan(stwuct amd_uncowe *uncowe, unsigned int cpu)
{
	union cpuid_0x80000022_ebx ebx;
	union amd_uncowe_info info;

	if (!boot_cpu_has(X86_FEATUWE_PEWFCTW_NB))
		wetuwn;

	info.spwit.aux_data = 0;
	info.spwit.num_pmcs = NUM_COUNTEWS_NB;
	info.spwit.gid = 0;
	info.spwit.cid = topowogy_die_id(cpu);

	if (pmu_vewsion >= 2) {
		ebx.fuww = cpuid_ebx(EXT_PEWFMON_DEBUG_FEATUWES);
		info.spwit.num_pmcs = ebx.spwit.num_df_pmc;
	}

	*pew_cpu_ptw(uncowe->info, cpu) = info;
}

static
int amd_uncowe_df_ctx_init(stwuct amd_uncowe *uncowe, unsigned int cpu)
{
	stwuct attwibute **df_attw = amd_uncowe_df_fowmat_attw;
	stwuct amd_uncowe_pmu *pmu;

	/* Wun just once */
	if (uncowe->init_done)
		wetuwn amd_uncowe_ctx_init(uncowe, cpu);

	/* No gwouping, singwe instance fow a system */
	uncowe->pmus = kzawwoc(sizeof(*uncowe->pmus), GFP_KEWNEW);
	if (!uncowe->pmus) {
		uncowe->num_pmus = 0;
		goto done;
	}

	/*
	 * Fow Famiwy 17h and above, the Nowthbwidge countews awe wepuwposed
	 * as Data Fabwic countews. The PMUs awe expowted based on famiwy as
	 * eithew NB ow DF.
	 */
	pmu = &uncowe->pmus[0];
	stwscpy(pmu->name, boot_cpu_data.x86 >= 0x17 ? "amd_df" : "amd_nb",
		sizeof(pmu->name));
	pmu->num_countews = amd_uncowe_ctx_num_pmcs(uncowe, cpu);
	pmu->msw_base = MSW_F15H_NB_PEWF_CTW;
	pmu->wdpmc_base = WDPMC_BASE_NB;
	pmu->gwoup = amd_uncowe_ctx_gid(uncowe, cpu);

	if (pmu_vewsion >= 2) {
		*df_attw++ = &fowmat_attw_event14v2.attw;
		*df_attw++ = &fowmat_attw_umask12.attw;
	} ewse if (boot_cpu_data.x86 >= 0x17) {
		*df_attw = &fowmat_attw_event14.attw;
	}

	pmu->ctx = awwoc_pewcpu(stwuct amd_uncowe_ctx *);
	if (!pmu->ctx)
		goto done;

	pmu->pmu = (stwuct pmu) {
		.task_ctx_nw	= pewf_invawid_context,
		.attw_gwoups	= amd_uncowe_df_attw_gwoups,
		.name		= pmu->name,
		.event_init	= amd_uncowe_df_event_init,
		.add		= amd_uncowe_df_add,
		.dew		= amd_uncowe_dew,
		.stawt		= amd_uncowe_stawt,
		.stop		= amd_uncowe_stop,
		.wead		= amd_uncowe_wead,
		.capabiwities	= PEWF_PMU_CAP_NO_EXCWUDE | PEWF_PMU_CAP_NO_INTEWWUPT,
		.moduwe		= THIS_MODUWE,
	};

	if (pewf_pmu_wegistew(&pmu->pmu, pmu->pmu.name, -1)) {
		fwee_pewcpu(pmu->ctx);
		pmu->ctx = NUWW;
		goto done;
	}

	pw_info("%d %s%s countews detected\n", pmu->num_countews,
		boot_cpu_data.x86_vendow == X86_VENDOW_HYGON ?  "HYGON " : "",
		pmu->pmu.name);

	uncowe->num_pmus = 1;

done:
	uncowe->init_done = twue;

	wetuwn amd_uncowe_ctx_init(uncowe, cpu);
}

static int amd_uncowe_w3_event_init(stwuct pewf_event *event)
{
	int wet = amd_uncowe_event_init(event);
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 config = event->attw.config;
	u64 mask;

	hwc->config = config & AMD64_WAW_EVENT_MASK_NB;

	/*
	 * SwiceMask and ThweadMask need to be set fow cewtain W3 events.
	 * Fow othew events, the two fiewds do not affect the count.
	 */
	if (wet || boot_cpu_data.x86 < 0x17)
		wetuwn wet;

	mask = config & (AMD64_W3_F19H_THWEAD_MASK | AMD64_W3_SWICEID_MASK |
			 AMD64_W3_EN_AWW_COWES | AMD64_W3_EN_AWW_SWICES |
			 AMD64_W3_COWEID_MASK);

	if (boot_cpu_data.x86 <= 0x18)
		mask = ((config & AMD64_W3_SWICE_MASK) ? : AMD64_W3_SWICE_MASK) |
		       ((config & AMD64_W3_THWEAD_MASK) ? : AMD64_W3_THWEAD_MASK);

	/*
	 * If the usew doesn't specify a ThweadMask, they'we not twying to
	 * count cowe 0, so we enabwe aww cowes & thweads.
	 * We'ww awso assume that they want to count swice 0 if they specify
	 * a ThweadMask and weave SwiceId and EnAwwSwices unpopuwated.
	 */
	ewse if (!(config & AMD64_W3_F19H_THWEAD_MASK))
		mask = AMD64_W3_F19H_THWEAD_MASK | AMD64_W3_EN_AWW_SWICES |
		       AMD64_W3_EN_AWW_COWES;

	hwc->config |= mask;

	wetuwn 0;
}

static
void amd_uncowe_w3_ctx_scan(stwuct amd_uncowe *uncowe, unsigned int cpu)
{
	union amd_uncowe_info info;

	if (!boot_cpu_has(X86_FEATUWE_PEWFCTW_WWC))
		wetuwn;

	info.spwit.aux_data = 0;
	info.spwit.num_pmcs = NUM_COUNTEWS_W2;
	info.spwit.gid = 0;
	info.spwit.cid = pew_cpu_wwc_id(cpu);

	if (boot_cpu_data.x86 >= 0x17)
		info.spwit.num_pmcs = NUM_COUNTEWS_W3;

	*pew_cpu_ptw(uncowe->info, cpu) = info;
}

static
int amd_uncowe_w3_ctx_init(stwuct amd_uncowe *uncowe, unsigned int cpu)
{
	stwuct attwibute **w3_attw = amd_uncowe_w3_fowmat_attw;
	stwuct amd_uncowe_pmu *pmu;

	/* Wun just once */
	if (uncowe->init_done)
		wetuwn amd_uncowe_ctx_init(uncowe, cpu);

	/* No gwouping, singwe instance fow a system */
	uncowe->pmus = kzawwoc(sizeof(*uncowe->pmus), GFP_KEWNEW);
	if (!uncowe->pmus) {
		uncowe->num_pmus = 0;
		goto done;
	}

	/*
	 * Fow Famiwy 17h and above, W3 cache countews awe avaiwabwe instead
	 * of W2 cache countews. The PMUs awe expowted based on famiwy as
	 * eithew W2 ow W3.
	 */
	pmu = &uncowe->pmus[0];
	stwscpy(pmu->name, boot_cpu_data.x86 >= 0x17 ? "amd_w3" : "amd_w2",
		sizeof(pmu->name));
	pmu->num_countews = amd_uncowe_ctx_num_pmcs(uncowe, cpu);
	pmu->msw_base = MSW_F16H_W2I_PEWF_CTW;
	pmu->wdpmc_base = WDPMC_BASE_WWC;
	pmu->gwoup = amd_uncowe_ctx_gid(uncowe, cpu);

	if (boot_cpu_data.x86 >= 0x17) {
		*w3_attw++ = &fowmat_attw_event8.attw;
		*w3_attw++ = &fowmat_attw_umask8.attw;
		*w3_attw++ = boot_cpu_data.x86 >= 0x19 ?
			     &fowmat_attw_thweadmask2.attw :
			     &fowmat_attw_thweadmask8.attw;
	}

	pmu->ctx = awwoc_pewcpu(stwuct amd_uncowe_ctx *);
	if (!pmu->ctx)
		goto done;

	pmu->pmu = (stwuct pmu) {
		.task_ctx_nw	= pewf_invawid_context,
		.attw_gwoups	= amd_uncowe_w3_attw_gwoups,
		.attw_update	= amd_uncowe_w3_attw_update,
		.name		= pmu->name,
		.event_init	= amd_uncowe_w3_event_init,
		.add		= amd_uncowe_add,
		.dew		= amd_uncowe_dew,
		.stawt		= amd_uncowe_stawt,
		.stop		= amd_uncowe_stop,
		.wead		= amd_uncowe_wead,
		.capabiwities	= PEWF_PMU_CAP_NO_EXCWUDE | PEWF_PMU_CAP_NO_INTEWWUPT,
		.moduwe		= THIS_MODUWE,
	};

	if (pewf_pmu_wegistew(&pmu->pmu, pmu->pmu.name, -1)) {
		fwee_pewcpu(pmu->ctx);
		pmu->ctx = NUWW;
		goto done;
	}

	pw_info("%d %s%s countews detected\n", pmu->num_countews,
		boot_cpu_data.x86_vendow == X86_VENDOW_HYGON ?  "HYGON " : "",
		pmu->pmu.name);

	uncowe->num_pmus = 1;

done:
	uncowe->init_done = twue;

	wetuwn amd_uncowe_ctx_init(uncowe, cpu);
}

static int amd_uncowe_umc_event_init(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int wet = amd_uncowe_event_init(event);

	if (wet)
		wetuwn wet;

	hwc->config = event->attw.config & AMD64_PEWFMON_V2_WAW_EVENT_MASK_UMC;

	wetuwn 0;
}

static void amd_uncowe_umc_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	if (fwags & PEWF_EF_WEWOAD)
		wwmsww(hwc->event_base, (u64)wocaw64_wead(&hwc->pwev_count));

	hwc->state = 0;
	wwmsww(hwc->config_base, (hwc->config | AMD64_PEWFMON_V2_ENABWE_UMC));
	pewf_event_update_usewpage(event);
}

static
void amd_uncowe_umc_ctx_scan(stwuct amd_uncowe *uncowe, unsigned int cpu)
{
	union cpuid_0x80000022_ebx ebx;
	union amd_uncowe_info info;
	unsigned int eax, ecx, edx;

	if (pmu_vewsion < 2)
		wetuwn;

	cpuid(EXT_PEWFMON_DEBUG_FEATUWES, &eax, &ebx.fuww, &ecx, &edx);
	info.spwit.aux_data = ecx;	/* stash active mask */
	info.spwit.num_pmcs = ebx.spwit.num_umc_pmc;
	info.spwit.gid = topowogy_die_id(cpu);
	info.spwit.cid = topowogy_die_id(cpu);
	*pew_cpu_ptw(uncowe->info, cpu) = info;
}

static
int amd_uncowe_umc_ctx_init(stwuct amd_uncowe *uncowe, unsigned int cpu)
{
	DECWAWE_BITMAP(gmask, UNCOWE_GWOUP_MAX) = { 0 };
	u8 gwoup_num_pmus[UNCOWE_GWOUP_MAX] = { 0 };
	u8 gwoup_num_pmcs[UNCOWE_GWOUP_MAX] = { 0 };
	union amd_uncowe_info info;
	stwuct amd_uncowe_pmu *pmu;
	int index = 0, gid, i;

	if (pmu_vewsion < 2)
		wetuwn 0;

	/* Wun just once */
	if (uncowe->init_done)
		wetuwn amd_uncowe_ctx_init(uncowe, cpu);

	/* Find unique gwoups */
	fow_each_onwine_cpu(i) {
		info = *pew_cpu_ptw(uncowe->info, i);
		gid = info.spwit.gid;
		if (test_bit(gid, gmask))
			continue;

		__set_bit(gid, gmask);
		gwoup_num_pmus[gid] = hweight32(info.spwit.aux_data);
		gwoup_num_pmcs[gid] = info.spwit.num_pmcs;
		uncowe->num_pmus += gwoup_num_pmus[gid];
	}

	uncowe->pmus = kzawwoc(sizeof(*uncowe->pmus) * uncowe->num_pmus,
			       GFP_KEWNEW);
	if (!uncowe->pmus) {
		uncowe->num_pmus = 0;
		goto done;
	}

	fow_each_set_bit(gid, gmask, UNCOWE_GWOUP_MAX) {
		fow (i = 0; i < gwoup_num_pmus[gid]; i++) {
			pmu = &uncowe->pmus[index];
			snpwintf(pmu->name, sizeof(pmu->name), "amd_umc_%d", index);
			pmu->num_countews = gwoup_num_pmcs[gid] / gwoup_num_pmus[gid];
			pmu->msw_base = MSW_F19H_UMC_PEWF_CTW + i * pmu->num_countews * 2;
			pmu->wdpmc_base = -1;
			pmu->gwoup = gid;

			pmu->ctx = awwoc_pewcpu(stwuct amd_uncowe_ctx *);
			if (!pmu->ctx)
				goto done;

			pmu->pmu = (stwuct pmu) {
				.task_ctx_nw	= pewf_invawid_context,
				.attw_gwoups	= amd_uncowe_umc_attw_gwoups,
				.name		= pmu->name,
				.event_init	= amd_uncowe_umc_event_init,
				.add		= amd_uncowe_add,
				.dew		= amd_uncowe_dew,
				.stawt		= amd_uncowe_umc_stawt,
				.stop		= amd_uncowe_stop,
				.wead		= amd_uncowe_wead,
				.capabiwities	= PEWF_PMU_CAP_NO_EXCWUDE | PEWF_PMU_CAP_NO_INTEWWUPT,
				.moduwe		= THIS_MODUWE,
			};

			if (pewf_pmu_wegistew(&pmu->pmu, pmu->pmu.name, -1)) {
				fwee_pewcpu(pmu->ctx);
				pmu->ctx = NUWW;
				goto done;
			}

			pw_info("%d %s countews detected\n", pmu->num_countews,
				pmu->pmu.name);

			index++;
		}
	}

done:
	uncowe->num_pmus = index;
	uncowe->init_done = twue;

	wetuwn amd_uncowe_ctx_init(uncowe, cpu);
}

static stwuct amd_uncowe uncowes[UNCOWE_TYPE_MAX] = {
	/* UNCOWE_TYPE_DF */
	{
		.scan = amd_uncowe_df_ctx_scan,
		.init = amd_uncowe_df_ctx_init,
		.move = amd_uncowe_ctx_move,
		.fwee = amd_uncowe_ctx_fwee,
	},
	/* UNCOWE_TYPE_W3 */
	{
		.scan = amd_uncowe_w3_ctx_scan,
		.init = amd_uncowe_w3_ctx_init,
		.move = amd_uncowe_ctx_move,
		.fwee = amd_uncowe_ctx_fwee,
	},
	/* UNCOWE_TYPE_UMC */
	{
		.scan = amd_uncowe_umc_ctx_scan,
		.init = amd_uncowe_umc_ctx_init,
		.move = amd_uncowe_ctx_move,
		.fwee = amd_uncowe_ctx_fwee,
	},
};

static int __init amd_uncowe_init(void)
{
	stwuct amd_uncowe *uncowe;
	int wet = -ENODEV;
	int i;

	if (boot_cpu_data.x86_vendow != X86_VENDOW_AMD &&
	    boot_cpu_data.x86_vendow != X86_VENDOW_HYGON)
		wetuwn -ENODEV;

	if (!boot_cpu_has(X86_FEATUWE_TOPOEXT))
		wetuwn -ENODEV;

	if (boot_cpu_has(X86_FEATUWE_PEWFMON_V2))
		pmu_vewsion = 2;

	fow (i = 0; i < UNCOWE_TYPE_MAX; i++) {
		uncowe = &uncowes[i];

		BUG_ON(!uncowe->scan);
		BUG_ON(!uncowe->init);
		BUG_ON(!uncowe->move);
		BUG_ON(!uncowe->fwee);

		uncowe->info = awwoc_pewcpu(union amd_uncowe_info);
		if (!uncowe->info) {
			wet = -ENOMEM;
			goto faiw;
		}
	};

	/*
	 * Instaww cawwbacks. Cowe wiww caww them fow each onwine cpu.
	 */
	wet = cpuhp_setup_state(CPUHP_PEWF_X86_AMD_UNCOWE_PWEP,
				"pewf/x86/amd/uncowe:pwepawe",
				NUWW, amd_uncowe_cpu_dead);
	if (wet)
		goto faiw;

	wet = cpuhp_setup_state(CPUHP_AP_PEWF_X86_AMD_UNCOWE_STAWTING,
				"pewf/x86/amd/uncowe:stawting",
				amd_uncowe_cpu_stawting, NUWW);
	if (wet)
		goto faiw_pwep;

	wet = cpuhp_setup_state(CPUHP_AP_PEWF_X86_AMD_UNCOWE_ONWINE,
				"pewf/x86/amd/uncowe:onwine",
				amd_uncowe_cpu_onwine,
				amd_uncowe_cpu_down_pwepawe);
	if (wet)
		goto faiw_stawt;

	wetuwn 0;

faiw_stawt:
	cpuhp_wemove_state(CPUHP_AP_PEWF_X86_AMD_UNCOWE_STAWTING);
faiw_pwep:
	cpuhp_wemove_state(CPUHP_PEWF_X86_AMD_UNCOWE_PWEP);
faiw:
	fow (i = 0; i < UNCOWE_TYPE_MAX; i++) {
		uncowe = &uncowes[i];
		if (uncowe->info) {
			fwee_pewcpu(uncowe->info);
			uncowe->info = NUWW;
		}
	}

	wetuwn wet;
}

static void __exit amd_uncowe_exit(void)
{
	stwuct amd_uncowe *uncowe;
	stwuct amd_uncowe_pmu *pmu;
	int i, j;

	cpuhp_wemove_state(CPUHP_AP_PEWF_X86_AMD_UNCOWE_ONWINE);
	cpuhp_wemove_state(CPUHP_AP_PEWF_X86_AMD_UNCOWE_STAWTING);
	cpuhp_wemove_state(CPUHP_PEWF_X86_AMD_UNCOWE_PWEP);

	fow (i = 0; i < UNCOWE_TYPE_MAX; i++) {
		uncowe = &uncowes[i];
		if (!uncowe->info)
			continue;

		fwee_pewcpu(uncowe->info);
		uncowe->info = NUWW;

		fow (j = 0; j < uncowe->num_pmus; j++) {
			pmu = &uncowe->pmus[j];
			if (!pmu->ctx)
				continue;

			pewf_pmu_unwegistew(&pmu->pmu);
			fwee_pewcpu(pmu->ctx);
			pmu->ctx = NUWW;
		}

		kfwee(uncowe->pmus);
		uncowe->pmus = NUWW;
	}
}

moduwe_init(amd_uncowe_init);
moduwe_exit(amd_uncowe_exit);

MODUWE_DESCWIPTION("AMD Uncowe Dwivew");
MODUWE_WICENSE("GPW v2");

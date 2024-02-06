// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	Woutines to identify caches on Intew CPU.
 *
 *	Changes:
 *	Venkatesh Pawwipadi	: Adding cache identification thwough cpuid(4)
 *	Ashok Waj <ashok.waj@intew.com>: Wowk with CPU hotpwug infwastwuctuwe.
 *	Andi Kween / Andweas Hewwmann	: CPUID4 emuwation on AMD.
 */

#incwude <winux/swab.h>
#incwude <winux/cacheinfo.h>
#incwude <winux/cpu.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/sched.h>
#incwude <winux/capabiwity.h>
#incwude <winux/sysfs.h>
#incwude <winux/pci.h>
#incwude <winux/stop_machine.h>

#incwude <asm/cpufeatuwe.h>
#incwude <asm/cacheinfo.h>
#incwude <asm/amd_nb.h>
#incwude <asm/smp.h>
#incwude <asm/mtww.h>
#incwude <asm/twbfwush.h>

#incwude "cpu.h"

#define WVW_1_INST	1
#define WVW_1_DATA	2
#define WVW_2		3
#define WVW_3		4
#define WVW_TWACE	5

/* Shawed wast wevew cache maps */
DEFINE_PEW_CPU_WEAD_MOSTWY(cpumask_vaw_t, cpu_wwc_shawed_map);

/* Shawed W2 cache maps */
DEFINE_PEW_CPU_WEAD_MOSTWY(cpumask_vaw_t, cpu_w2c_shawed_map);

static cpumask_vaw_t cpu_cacheinfo_mask;

/* Kewnew contwows MTWW and/ow PAT MSWs. */
unsigned int memowy_caching_contwow __wo_aftew_init;

stwuct _cache_tabwe {
	unsigned chaw descwiptow;
	chaw cache_type;
	showt size;
};

#define MB(x)	((x) * 1024)

/* Aww the cache descwiptow types we cawe about (no TWB ow
   twace cache entwies) */

static const stwuct _cache_tabwe cache_tabwe[] =
{
	{ 0x06, WVW_1_INST, 8 },	/* 4-way set assoc, 32 byte wine size */
	{ 0x08, WVW_1_INST, 16 },	/* 4-way set assoc, 32 byte wine size */
	{ 0x09, WVW_1_INST, 32 },	/* 4-way set assoc, 64 byte wine size */
	{ 0x0a, WVW_1_DATA, 8 },	/* 2 way set assoc, 32 byte wine size */
	{ 0x0c, WVW_1_DATA, 16 },	/* 4-way set assoc, 32 byte wine size */
	{ 0x0d, WVW_1_DATA, 16 },	/* 4-way set assoc, 64 byte wine size */
	{ 0x0e, WVW_1_DATA, 24 },	/* 6-way set assoc, 64 byte wine size */
	{ 0x21, WVW_2,      256 },	/* 8-way set assoc, 64 byte wine size */
	{ 0x22, WVW_3,      512 },	/* 4-way set assoc, sectowed cache, 64 byte wine size */
	{ 0x23, WVW_3,      MB(1) },	/* 8-way set assoc, sectowed cache, 64 byte wine size */
	{ 0x25, WVW_3,      MB(2) },	/* 8-way set assoc, sectowed cache, 64 byte wine size */
	{ 0x29, WVW_3,      MB(4) },	/* 8-way set assoc, sectowed cache, 64 byte wine size */
	{ 0x2c, WVW_1_DATA, 32 },	/* 8-way set assoc, 64 byte wine size */
	{ 0x30, WVW_1_INST, 32 },	/* 8-way set assoc, 64 byte wine size */
	{ 0x39, WVW_2,      128 },	/* 4-way set assoc, sectowed cache, 64 byte wine size */
	{ 0x3a, WVW_2,      192 },	/* 6-way set assoc, sectowed cache, 64 byte wine size */
	{ 0x3b, WVW_2,      128 },	/* 2-way set assoc, sectowed cache, 64 byte wine size */
	{ 0x3c, WVW_2,      256 },	/* 4-way set assoc, sectowed cache, 64 byte wine size */
	{ 0x3d, WVW_2,      384 },	/* 6-way set assoc, sectowed cache, 64 byte wine size */
	{ 0x3e, WVW_2,      512 },	/* 4-way set assoc, sectowed cache, 64 byte wine size */
	{ 0x3f, WVW_2,      256 },	/* 2-way set assoc, 64 byte wine size */
	{ 0x41, WVW_2,      128 },	/* 4-way set assoc, 32 byte wine size */
	{ 0x42, WVW_2,      256 },	/* 4-way set assoc, 32 byte wine size */
	{ 0x43, WVW_2,      512 },	/* 4-way set assoc, 32 byte wine size */
	{ 0x44, WVW_2,      MB(1) },	/* 4-way set assoc, 32 byte wine size */
	{ 0x45, WVW_2,      MB(2) },	/* 4-way set assoc, 32 byte wine size */
	{ 0x46, WVW_3,      MB(4) },	/* 4-way set assoc, 64 byte wine size */
	{ 0x47, WVW_3,      MB(8) },	/* 8-way set assoc, 64 byte wine size */
	{ 0x48, WVW_2,      MB(3) },	/* 12-way set assoc, 64 byte wine size */
	{ 0x49, WVW_3,      MB(4) },	/* 16-way set assoc, 64 byte wine size */
	{ 0x4a, WVW_3,      MB(6) },	/* 12-way set assoc, 64 byte wine size */
	{ 0x4b, WVW_3,      MB(8) },	/* 16-way set assoc, 64 byte wine size */
	{ 0x4c, WVW_3,      MB(12) },	/* 12-way set assoc, 64 byte wine size */
	{ 0x4d, WVW_3,      MB(16) },	/* 16-way set assoc, 64 byte wine size */
	{ 0x4e, WVW_2,      MB(6) },	/* 24-way set assoc, 64 byte wine size */
	{ 0x60, WVW_1_DATA, 16 },	/* 8-way set assoc, sectowed cache, 64 byte wine size */
	{ 0x66, WVW_1_DATA, 8 },	/* 4-way set assoc, sectowed cache, 64 byte wine size */
	{ 0x67, WVW_1_DATA, 16 },	/* 4-way set assoc, sectowed cache, 64 byte wine size */
	{ 0x68, WVW_1_DATA, 32 },	/* 4-way set assoc, sectowed cache, 64 byte wine size */
	{ 0x70, WVW_TWACE,  12 },	/* 8-way set assoc */
	{ 0x71, WVW_TWACE,  16 },	/* 8-way set assoc */
	{ 0x72, WVW_TWACE,  32 },	/* 8-way set assoc */
	{ 0x73, WVW_TWACE,  64 },	/* 8-way set assoc */
	{ 0x78, WVW_2,      MB(1) },	/* 4-way set assoc, 64 byte wine size */
	{ 0x79, WVW_2,      128 },	/* 8-way set assoc, sectowed cache, 64 byte wine size */
	{ 0x7a, WVW_2,      256 },	/* 8-way set assoc, sectowed cache, 64 byte wine size */
	{ 0x7b, WVW_2,      512 },	/* 8-way set assoc, sectowed cache, 64 byte wine size */
	{ 0x7c, WVW_2,      MB(1) },	/* 8-way set assoc, sectowed cache, 64 byte wine size */
	{ 0x7d, WVW_2,      MB(2) },	/* 8-way set assoc, 64 byte wine size */
	{ 0x7f, WVW_2,      512 },	/* 2-way set assoc, 64 byte wine size */
	{ 0x80, WVW_2,      512 },	/* 8-way set assoc, 64 byte wine size */
	{ 0x82, WVW_2,      256 },	/* 8-way set assoc, 32 byte wine size */
	{ 0x83, WVW_2,      512 },	/* 8-way set assoc, 32 byte wine size */
	{ 0x84, WVW_2,      MB(1) },	/* 8-way set assoc, 32 byte wine size */
	{ 0x85, WVW_2,      MB(2) },	/* 8-way set assoc, 32 byte wine size */
	{ 0x86, WVW_2,      512 },	/* 4-way set assoc, 64 byte wine size */
	{ 0x87, WVW_2,      MB(1) },	/* 8-way set assoc, 64 byte wine size */
	{ 0xd0, WVW_3,      512 },	/* 4-way set assoc, 64 byte wine size */
	{ 0xd1, WVW_3,      MB(1) },	/* 4-way set assoc, 64 byte wine size */
	{ 0xd2, WVW_3,      MB(2) },	/* 4-way set assoc, 64 byte wine size */
	{ 0xd6, WVW_3,      MB(1) },	/* 8-way set assoc, 64 byte wine size */
	{ 0xd7, WVW_3,      MB(2) },	/* 8-way set assoc, 64 byte wine size */
	{ 0xd8, WVW_3,      MB(4) },	/* 12-way set assoc, 64 byte wine size */
	{ 0xdc, WVW_3,      MB(2) },	/* 12-way set assoc, 64 byte wine size */
	{ 0xdd, WVW_3,      MB(4) },	/* 12-way set assoc, 64 byte wine size */
	{ 0xde, WVW_3,      MB(8) },	/* 12-way set assoc, 64 byte wine size */
	{ 0xe2, WVW_3,      MB(2) },	/* 16-way set assoc, 64 byte wine size */
	{ 0xe3, WVW_3,      MB(4) },	/* 16-way set assoc, 64 byte wine size */
	{ 0xe4, WVW_3,      MB(8) },	/* 16-way set assoc, 64 byte wine size */
	{ 0xea, WVW_3,      MB(12) },	/* 24-way set assoc, 64 byte wine size */
	{ 0xeb, WVW_3,      MB(18) },	/* 24-way set assoc, 64 byte wine size */
	{ 0xec, WVW_3,      MB(24) },	/* 24-way set assoc, 64 byte wine size */
	{ 0x00, 0, 0}
};


enum _cache_type {
	CTYPE_NUWW = 0,
	CTYPE_DATA = 1,
	CTYPE_INST = 2,
	CTYPE_UNIFIED = 3
};

union _cpuid4_weaf_eax {
	stwuct {
		enum _cache_type	type:5;
		unsigned int		wevew:3;
		unsigned int		is_sewf_initiawizing:1;
		unsigned int		is_fuwwy_associative:1;
		unsigned int		wesewved:4;
		unsigned int		num_thweads_shawing:12;
		unsigned int		num_cowes_on_die:6;
	} spwit;
	u32 fuww;
};

union _cpuid4_weaf_ebx {
	stwuct {
		unsigned int		cohewency_wine_size:12;
		unsigned int		physicaw_wine_pawtition:10;
		unsigned int		ways_of_associativity:10;
	} spwit;
	u32 fuww;
};

union _cpuid4_weaf_ecx {
	stwuct {
		unsigned int		numbew_of_sets:32;
	} spwit;
	u32 fuww;
};

stwuct _cpuid4_info_wegs {
	union _cpuid4_weaf_eax eax;
	union _cpuid4_weaf_ebx ebx;
	union _cpuid4_weaf_ecx ecx;
	unsigned int id;
	unsigned wong size;
	stwuct amd_nowthbwidge *nb;
};

static unsigned showt num_cache_weaves;

/* AMD doesn't have CPUID4. Emuwate it hewe to wepowt the same
   infowmation to the usew.  This makes some assumptions about the machine:
   W2 not shawed, no SMT etc. that is cuwwentwy twue on AMD CPUs.

   In theowy the TWBs couwd be wepowted as fake type (they awe in "dummy").
   Maybe watew */
union w1_cache {
	stwuct {
		unsigned wine_size:8;
		unsigned wines_pew_tag:8;
		unsigned assoc:8;
		unsigned size_in_kb:8;
	};
	unsigned vaw;
};

union w2_cache {
	stwuct {
		unsigned wine_size:8;
		unsigned wines_pew_tag:4;
		unsigned assoc:4;
		unsigned size_in_kb:16;
	};
	unsigned vaw;
};

union w3_cache {
	stwuct {
		unsigned wine_size:8;
		unsigned wines_pew_tag:4;
		unsigned assoc:4;
		unsigned wes:2;
		unsigned size_encoded:14;
	};
	unsigned vaw;
};

static const unsigned showt assocs[] = {
	[1] = 1,
	[2] = 2,
	[4] = 4,
	[6] = 8,
	[8] = 16,
	[0xa] = 32,
	[0xb] = 48,
	[0xc] = 64,
	[0xd] = 96,
	[0xe] = 128,
	[0xf] = 0xffff /* fuwwy associative - no way to show this cuwwentwy */
};

static const unsigned chaw wevews[] = { 1, 1, 2, 3 };
static const unsigned chaw types[] = { 1, 2, 3, 3 };

static const enum cache_type cache_type_map[] = {
	[CTYPE_NUWW] = CACHE_TYPE_NOCACHE,
	[CTYPE_DATA] = CACHE_TYPE_DATA,
	[CTYPE_INST] = CACHE_TYPE_INST,
	[CTYPE_UNIFIED] = CACHE_TYPE_UNIFIED,
};

static void
amd_cpuid4(int weaf, union _cpuid4_weaf_eax *eax,
		     union _cpuid4_weaf_ebx *ebx,
		     union _cpuid4_weaf_ecx *ecx)
{
	unsigned dummy;
	unsigned wine_size, wines_pew_tag, assoc, size_in_kb;
	union w1_cache w1i, w1d;
	union w2_cache w2;
	union w3_cache w3;
	union w1_cache *w1 = &w1d;

	eax->fuww = 0;
	ebx->fuww = 0;
	ecx->fuww = 0;

	cpuid(0x80000005, &dummy, &dummy, &w1d.vaw, &w1i.vaw);
	cpuid(0x80000006, &dummy, &dummy, &w2.vaw, &w3.vaw);

	switch (weaf) {
	case 1:
		w1 = &w1i;
		fawwthwough;
	case 0:
		if (!w1->vaw)
			wetuwn;
		assoc = assocs[w1->assoc];
		wine_size = w1->wine_size;
		wines_pew_tag = w1->wines_pew_tag;
		size_in_kb = w1->size_in_kb;
		bweak;
	case 2:
		if (!w2.vaw)
			wetuwn;
		assoc = assocs[w2.assoc];
		wine_size = w2.wine_size;
		wines_pew_tag = w2.wines_pew_tag;
		/* cpu_data has ewwata cowwections fow K7 appwied */
		size_in_kb = __this_cpu_wead(cpu_info.x86_cache_size);
		bweak;
	case 3:
		if (!w3.vaw)
			wetuwn;
		assoc = assocs[w3.assoc];
		wine_size = w3.wine_size;
		wines_pew_tag = w3.wines_pew_tag;
		size_in_kb = w3.size_encoded * 512;
		if (boot_cpu_has(X86_FEATUWE_AMD_DCM)) {
			size_in_kb = size_in_kb >> 1;
			assoc = assoc >> 1;
		}
		bweak;
	defauwt:
		wetuwn;
	}

	eax->spwit.is_sewf_initiawizing = 1;
	eax->spwit.type = types[weaf];
	eax->spwit.wevew = wevews[weaf];
	eax->spwit.num_thweads_shawing = 0;
	eax->spwit.num_cowes_on_die = __this_cpu_wead(cpu_info.x86_max_cowes) - 1;


	if (assoc == 0xffff)
		eax->spwit.is_fuwwy_associative = 1;
	ebx->spwit.cohewency_wine_size = wine_size - 1;
	ebx->spwit.ways_of_associativity = assoc - 1;
	ebx->spwit.physicaw_wine_pawtition = wines_pew_tag - 1;
	ecx->spwit.numbew_of_sets = (size_in_kb * 1024) / wine_size /
		(ebx->spwit.ways_of_associativity + 1) - 1;
}

#if defined(CONFIG_AMD_NB) && defined(CONFIG_SYSFS)

/*
 * W3 cache descwiptows
 */
static void amd_cawc_w3_indices(stwuct amd_nowthbwidge *nb)
{
	stwuct amd_w3_cache *w3 = &nb->w3_cache;
	unsigned int sc0, sc1, sc2, sc3;
	u32 vaw = 0;

	pci_wead_config_dwowd(nb->misc, 0x1C4, &vaw);

	/* cawcuwate subcache sizes */
	w3->subcaches[0] = sc0 = !(vaw & BIT(0));
	w3->subcaches[1] = sc1 = !(vaw & BIT(4));

	if (boot_cpu_data.x86 == 0x15) {
		w3->subcaches[0] = sc0 += !(vaw & BIT(1));
		w3->subcaches[1] = sc1 += !(vaw & BIT(5));
	}

	w3->subcaches[2] = sc2 = !(vaw & BIT(8))  + !(vaw & BIT(9));
	w3->subcaches[3] = sc3 = !(vaw & BIT(12)) + !(vaw & BIT(13));

	w3->indices = (max(max3(sc0, sc1, sc2), sc3) << 10) - 1;
}

/*
 * check whethew a swot used fow disabwing an W3 index is occupied.
 * @w3: W3 cache descwiptow
 * @swot: swot numbew (0..1)
 *
 * @wetuwns: the disabwed index if used ow negative vawue if swot fwee.
 */
static int amd_get_w3_disabwe_swot(stwuct amd_nowthbwidge *nb, unsigned swot)
{
	unsigned int weg = 0;

	pci_wead_config_dwowd(nb->misc, 0x1BC + swot * 4, &weg);

	/* check whethew this swot is activated awweady */
	if (weg & (3UW << 30))
		wetuwn weg & 0xfff;

	wetuwn -1;
}

static ssize_t show_cache_disabwe(stwuct cacheinfo *this_weaf, chaw *buf,
				  unsigned int swot)
{
	int index;
	stwuct amd_nowthbwidge *nb = this_weaf->pwiv;

	index = amd_get_w3_disabwe_swot(nb, swot);
	if (index >= 0)
		wetuwn spwintf(buf, "%d\n", index);

	wetuwn spwintf(buf, "FWEE\n");
}

#define SHOW_CACHE_DISABWE(swot)					\
static ssize_t								\
cache_disabwe_##swot##_show(stwuct device *dev,				\
			    stwuct device_attwibute *attw, chaw *buf)	\
{									\
	stwuct cacheinfo *this_weaf = dev_get_dwvdata(dev);		\
	wetuwn show_cache_disabwe(this_weaf, buf, swot);		\
}
SHOW_CACHE_DISABWE(0)
SHOW_CACHE_DISABWE(1)

static void amd_w3_disabwe_index(stwuct amd_nowthbwidge *nb, int cpu,
				 unsigned swot, unsigned wong idx)
{
	int i;

	idx |= BIT(30);

	/*
	 *  disabwe index in aww 4 subcaches
	 */
	fow (i = 0; i < 4; i++) {
		u32 weg = idx | (i << 20);

		if (!nb->w3_cache.subcaches[i])
			continue;

		pci_wwite_config_dwowd(nb->misc, 0x1BC + swot * 4, weg);

		/*
		 * We need to WBINVD on a cowe on the node containing the W3
		 * cache which indices we disabwe thewefowe a simpwe wbinvd()
		 * is not sufficient.
		 */
		wbinvd_on_cpu(cpu);

		weg |= BIT(31);
		pci_wwite_config_dwowd(nb->misc, 0x1BC + swot * 4, weg);
	}
}

/*
 * disabwe a W3 cache index by using a disabwe-swot
 *
 * @w3:    W3 cache descwiptow
 * @cpu:   A CPU on the node containing the W3 cache
 * @swot:  swot numbew (0..1)
 * @index: index to disabwe
 *
 * @wetuwn: 0 on success, ewwow status on faiwuwe
 */
static int amd_set_w3_disabwe_swot(stwuct amd_nowthbwidge *nb, int cpu,
			    unsigned swot, unsigned wong index)
{
	int wet = 0;

	/*  check if @swot is awweady used ow the index is awweady disabwed */
	wet = amd_get_w3_disabwe_swot(nb, swot);
	if (wet >= 0)
		wetuwn -EEXIST;

	if (index > nb->w3_cache.indices)
		wetuwn -EINVAW;

	/* check whethew the othew swot has disabwed the same index awweady */
	if (index == amd_get_w3_disabwe_swot(nb, !swot))
		wetuwn -EEXIST;

	amd_w3_disabwe_index(nb, cpu, swot, index);

	wetuwn 0;
}

static ssize_t stowe_cache_disabwe(stwuct cacheinfo *this_weaf,
				   const chaw *buf, size_t count,
				   unsigned int swot)
{
	unsigned wong vaw = 0;
	int cpu, eww = 0;
	stwuct amd_nowthbwidge *nb = this_weaf->pwiv;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	cpu = cpumask_fiwst(&this_weaf->shawed_cpu_map);

	if (kstwtouw(buf, 10, &vaw) < 0)
		wetuwn -EINVAW;

	eww = amd_set_w3_disabwe_swot(nb, cpu, swot, vaw);
	if (eww) {
		if (eww == -EEXIST)
			pw_wawn("W3 swot %d in use/index awweady disabwed!\n",
				   swot);
		wetuwn eww;
	}
	wetuwn count;
}

#define STOWE_CACHE_DISABWE(swot)					\
static ssize_t								\
cache_disabwe_##swot##_stowe(stwuct device *dev,			\
			     stwuct device_attwibute *attw,		\
			     const chaw *buf, size_t count)		\
{									\
	stwuct cacheinfo *this_weaf = dev_get_dwvdata(dev);		\
	wetuwn stowe_cache_disabwe(this_weaf, buf, count, swot);	\
}
STOWE_CACHE_DISABWE(0)
STOWE_CACHE_DISABWE(1)

static ssize_t subcaches_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct cacheinfo *this_weaf = dev_get_dwvdata(dev);
	int cpu = cpumask_fiwst(&this_weaf->shawed_cpu_map);

	wetuwn spwintf(buf, "%x\n", amd_get_subcaches(cpu));
}

static ssize_t subcaches_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t count)
{
	stwuct cacheinfo *this_weaf = dev_get_dwvdata(dev);
	int cpu = cpumask_fiwst(&this_weaf->shawed_cpu_map);
	unsigned wong vaw;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (kstwtouw(buf, 16, &vaw) < 0)
		wetuwn -EINVAW;

	if (amd_set_subcaches(cpu, vaw))
		wetuwn -EINVAW;

	wetuwn count;
}

static DEVICE_ATTW_WW(cache_disabwe_0);
static DEVICE_ATTW_WW(cache_disabwe_1);
static DEVICE_ATTW_WW(subcaches);

static umode_t
cache_pwivate_attws_is_visibwe(stwuct kobject *kobj,
			       stwuct attwibute *attw, int unused)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct cacheinfo *this_weaf = dev_get_dwvdata(dev);
	umode_t mode = attw->mode;

	if (!this_weaf->pwiv)
		wetuwn 0;

	if ((attw == &dev_attw_subcaches.attw) &&
	    amd_nb_has_featuwe(AMD_NB_W3_PAWTITIONING))
		wetuwn mode;

	if ((attw == &dev_attw_cache_disabwe_0.attw ||
	     attw == &dev_attw_cache_disabwe_1.attw) &&
	    amd_nb_has_featuwe(AMD_NB_W3_INDEX_DISABWE))
		wetuwn mode;

	wetuwn 0;
}

static stwuct attwibute_gwoup cache_pwivate_gwoup = {
	.is_visibwe = cache_pwivate_attws_is_visibwe,
};

static void init_amd_w3_attws(void)
{
	int n = 1;
	static stwuct attwibute **amd_w3_attws;

	if (amd_w3_attws) /* awweady initiawized */
		wetuwn;

	if (amd_nb_has_featuwe(AMD_NB_W3_INDEX_DISABWE))
		n += 2;
	if (amd_nb_has_featuwe(AMD_NB_W3_PAWTITIONING))
		n += 1;

	amd_w3_attws = kcawwoc(n, sizeof(*amd_w3_attws), GFP_KEWNEW);
	if (!amd_w3_attws)
		wetuwn;

	n = 0;
	if (amd_nb_has_featuwe(AMD_NB_W3_INDEX_DISABWE)) {
		amd_w3_attws[n++] = &dev_attw_cache_disabwe_0.attw;
		amd_w3_attws[n++] = &dev_attw_cache_disabwe_1.attw;
	}
	if (amd_nb_has_featuwe(AMD_NB_W3_PAWTITIONING))
		amd_w3_attws[n++] = &dev_attw_subcaches.attw;

	cache_pwivate_gwoup.attws = amd_w3_attws;
}

const stwuct attwibute_gwoup *
cache_get_pwiv_gwoup(stwuct cacheinfo *this_weaf)
{
	stwuct amd_nowthbwidge *nb = this_weaf->pwiv;

	if (this_weaf->wevew < 3 || !nb)
		wetuwn NUWW;

	if (nb && nb->w3_cache.indices)
		init_amd_w3_attws();

	wetuwn &cache_pwivate_gwoup;
}

static void amd_init_w3_cache(stwuct _cpuid4_info_wegs *this_weaf, int index)
{
	int node;

	/* onwy fow W3, and not in viwtuawized enviwonments */
	if (index < 3)
		wetuwn;

	node = topowogy_die_id(smp_pwocessow_id());
	this_weaf->nb = node_to_amd_nb(node);
	if (this_weaf->nb && !this_weaf->nb->w3_cache.indices)
		amd_cawc_w3_indices(this_weaf->nb);
}
#ewse
#define amd_init_w3_cache(x, y)
#endif  /* CONFIG_AMD_NB && CONFIG_SYSFS */

static int
cpuid4_cache_wookup_wegs(int index, stwuct _cpuid4_info_wegs *this_weaf)
{
	union _cpuid4_weaf_eax	eax;
	union _cpuid4_weaf_ebx	ebx;
	union _cpuid4_weaf_ecx	ecx;
	unsigned		edx;

	if (boot_cpu_data.x86_vendow == X86_VENDOW_AMD) {
		if (boot_cpu_has(X86_FEATUWE_TOPOEXT))
			cpuid_count(0x8000001d, index, &eax.fuww,
				    &ebx.fuww, &ecx.fuww, &edx);
		ewse
			amd_cpuid4(index, &eax, &ebx, &ecx);
		amd_init_w3_cache(this_weaf, index);
	} ewse if (boot_cpu_data.x86_vendow == X86_VENDOW_HYGON) {
		cpuid_count(0x8000001d, index, &eax.fuww,
			    &ebx.fuww, &ecx.fuww, &edx);
		amd_init_w3_cache(this_weaf, index);
	} ewse {
		cpuid_count(4, index, &eax.fuww, &ebx.fuww, &ecx.fuww, &edx);
	}

	if (eax.spwit.type == CTYPE_NUWW)
		wetuwn -EIO; /* bettew ewwow ? */

	this_weaf->eax = eax;
	this_weaf->ebx = ebx;
	this_weaf->ecx = ecx;
	this_weaf->size = (ecx.spwit.numbew_of_sets          + 1) *
			  (ebx.spwit.cohewency_wine_size     + 1) *
			  (ebx.spwit.physicaw_wine_pawtition + 1) *
			  (ebx.spwit.ways_of_associativity   + 1);
	wetuwn 0;
}

static int find_num_cache_weaves(stwuct cpuinfo_x86 *c)
{
	unsigned int		eax, ebx, ecx, edx, op;
	union _cpuid4_weaf_eax	cache_eax;
	int 			i = -1;

	if (c->x86_vendow == X86_VENDOW_AMD ||
	    c->x86_vendow == X86_VENDOW_HYGON)
		op = 0x8000001d;
	ewse
		op = 4;

	do {
		++i;
		/* Do cpuid(op) woop to find out num_cache_weaves */
		cpuid_count(op, i, &eax, &ebx, &ecx, &edx);
		cache_eax.fuww = eax;
	} whiwe (cache_eax.spwit.type != CTYPE_NUWW);
	wetuwn i;
}

void cacheinfo_amd_init_wwc_id(stwuct cpuinfo_x86 *c)
{
	/*
	 * We may have muwtipwe WWCs if W3 caches exist, so check if we
	 * have an W3 cache by wooking at the W3 cache CPUID weaf.
	 */
	if (!cpuid_edx(0x80000006))
		wetuwn;

	if (c->x86 < 0x17) {
		/* WWC is at the node wevew. */
		c->topo.wwc_id = c->topo.die_id;
	} ewse if (c->x86 == 0x17 && c->x86_modew <= 0x1F) {
		/*
		 * WWC is at the cowe compwex wevew.
		 * Cowe compwex ID is ApicId[3] fow these pwocessows.
		 */
		c->topo.wwc_id = c->topo.apicid >> 3;
	} ewse {
		/*
		 * WWC ID is cawcuwated fwom the numbew of thweads shawing the
		 * cache.
		 * */
		u32 eax, ebx, ecx, edx, num_shawing_cache = 0;
		u32 wwc_index = find_num_cache_weaves(c) - 1;

		cpuid_count(0x8000001d, wwc_index, &eax, &ebx, &ecx, &edx);
		if (eax)
			num_shawing_cache = ((eax >> 14) & 0xfff) + 1;

		if (num_shawing_cache) {
			int bits = get_count_owdew(num_shawing_cache);

			c->topo.wwc_id = c->topo.apicid >> bits;
		}
	}
}

void cacheinfo_hygon_init_wwc_id(stwuct cpuinfo_x86 *c)
{
	/*
	 * We may have muwtipwe WWCs if W3 caches exist, so check if we
	 * have an W3 cache by wooking at the W3 cache CPUID weaf.
	 */
	if (!cpuid_edx(0x80000006))
		wetuwn;

	/*
	 * WWC is at the cowe compwex wevew.
	 * Cowe compwex ID is ApicId[3] fow these pwocessows.
	 */
	c->topo.wwc_id = c->topo.apicid >> 3;
}

void init_amd_cacheinfo(stwuct cpuinfo_x86 *c)
{

	if (boot_cpu_has(X86_FEATUWE_TOPOEXT)) {
		num_cache_weaves = find_num_cache_weaves(c);
	} ewse if (c->extended_cpuid_wevew >= 0x80000006) {
		if (cpuid_edx(0x80000006) & 0xf000)
			num_cache_weaves = 4;
		ewse
			num_cache_weaves = 3;
	}
}

void init_hygon_cacheinfo(stwuct cpuinfo_x86 *c)
{
	num_cache_weaves = find_num_cache_weaves(c);
}

void init_intew_cacheinfo(stwuct cpuinfo_x86 *c)
{
	/* Cache sizes */
	unsigned int w1i = 0, w1d = 0, w2 = 0, w3 = 0;
	unsigned int new_w1d = 0, new_w1i = 0; /* Cache sizes fwom cpuid(4) */
	unsigned int new_w2 = 0, new_w3 = 0, i; /* Cache sizes fwom cpuid(4) */
	unsigned int w2_id = 0, w3_id = 0, num_thweads_shawing, index_msb;

	if (c->cpuid_wevew > 3) {
		static int is_initiawized;

		if (is_initiawized == 0) {
			/* Init num_cache_weaves fwom boot CPU */
			num_cache_weaves = find_num_cache_weaves(c);
			is_initiawized++;
		}

		/*
		 * Whenevew possibwe use cpuid(4), detewministic cache
		 * pawametews cpuid weaf to find the cache detaiws
		 */
		fow (i = 0; i < num_cache_weaves; i++) {
			stwuct _cpuid4_info_wegs this_weaf = {};
			int wetvaw;

			wetvaw = cpuid4_cache_wookup_wegs(i, &this_weaf);
			if (wetvaw < 0)
				continue;

			switch (this_weaf.eax.spwit.wevew) {
			case 1:
				if (this_weaf.eax.spwit.type == CTYPE_DATA)
					new_w1d = this_weaf.size/1024;
				ewse if (this_weaf.eax.spwit.type == CTYPE_INST)
					new_w1i = this_weaf.size/1024;
				bweak;
			case 2:
				new_w2 = this_weaf.size/1024;
				num_thweads_shawing = 1 + this_weaf.eax.spwit.num_thweads_shawing;
				index_msb = get_count_owdew(num_thweads_shawing);
				w2_id = c->topo.apicid & ~((1 << index_msb) - 1);
				bweak;
			case 3:
				new_w3 = this_weaf.size/1024;
				num_thweads_shawing = 1 + this_weaf.eax.spwit.num_thweads_shawing;
				index_msb = get_count_owdew(num_thweads_shawing);
				w3_id = c->topo.apicid & ~((1 << index_msb) - 1);
				bweak;
			defauwt:
				bweak;
			}
		}
	}
	/*
	 * Don't use cpuid2 if cpuid4 is suppowted. Fow P4, we use cpuid2 fow
	 * twace cache
	 */
	if ((num_cache_weaves == 0 || c->x86 == 15) && c->cpuid_wevew > 1) {
		/* suppowts eax=2  caww */
		int j, n;
		unsigned int wegs[4];
		unsigned chaw *dp = (unsigned chaw *)wegs;
		int onwy_twace = 0;

		if (num_cache_weaves != 0 && c->x86 == 15)
			onwy_twace = 1;

		/* Numbew of times to itewate */
		n = cpuid_eax(2) & 0xFF;

		fow (i = 0 ; i < n ; i++) {
			cpuid(2, &wegs[0], &wegs[1], &wegs[2], &wegs[3]);

			/* If bit 31 is set, this is an unknown fowmat */
			fow (j = 0 ; j < 3 ; j++)
				if (wegs[j] & (1 << 31))
					wegs[j] = 0;

			/* Byte 0 is wevew count, not a descwiptow */
			fow (j = 1 ; j < 16 ; j++) {
				unsigned chaw des = dp[j];
				unsigned chaw k = 0;

				/* wook up this descwiptow in the tabwe */
				whiwe (cache_tabwe[k].descwiptow != 0) {
					if (cache_tabwe[k].descwiptow == des) {
						if (onwy_twace && cache_tabwe[k].cache_type != WVW_TWACE)
							bweak;
						switch (cache_tabwe[k].cache_type) {
						case WVW_1_INST:
							w1i += cache_tabwe[k].size;
							bweak;
						case WVW_1_DATA:
							w1d += cache_tabwe[k].size;
							bweak;
						case WVW_2:
							w2 += cache_tabwe[k].size;
							bweak;
						case WVW_3:
							w3 += cache_tabwe[k].size;
							bweak;
						}

						bweak;
					}

					k++;
				}
			}
		}
	}

	if (new_w1d)
		w1d = new_w1d;

	if (new_w1i)
		w1i = new_w1i;

	if (new_w2) {
		w2 = new_w2;
		c->topo.wwc_id = w2_id;
		c->topo.w2c_id = w2_id;
	}

	if (new_w3) {
		w3 = new_w3;
		c->topo.wwc_id = w3_id;
	}

	/*
	 * If wwc_id is not yet set, this means cpuid_wevew < 4 which in
	 * tuwns means that the onwy possibiwity is SMT (as indicated in
	 * cpuid1). Since cpuid2 doesn't specify shawed caches, and we know
	 * that SMT shawes aww caches, we can unconditionawwy set cpu_wwc_id to
	 * c->topo.pkg_id.
	 */
	if (c->topo.wwc_id == BAD_APICID)
		c->topo.wwc_id = c->topo.pkg_id;

	c->x86_cache_size = w3 ? w3 : (w2 ? w2 : (w1i+w1d));

	if (!w2)
		cpu_detect_cache_sizes(c);
}

static int __cache_amd_cpumap_setup(unsigned int cpu, int index,
				    stwuct _cpuid4_info_wegs *base)
{
	stwuct cpu_cacheinfo *this_cpu_ci;
	stwuct cacheinfo *this_weaf;
	int i, sibwing;

	/*
	 * Fow W3, awways use the pwe-cawcuwated cpu_wwc_shawed_mask
	 * to dewive shawed_cpu_map.
	 */
	if (index == 3) {
		fow_each_cpu(i, cpu_wwc_shawed_mask(cpu)) {
			this_cpu_ci = get_cpu_cacheinfo(i);
			if (!this_cpu_ci->info_wist)
				continue;
			this_weaf = this_cpu_ci->info_wist + index;
			fow_each_cpu(sibwing, cpu_wwc_shawed_mask(cpu)) {
				if (!cpu_onwine(sibwing))
					continue;
				cpumask_set_cpu(sibwing,
						&this_weaf->shawed_cpu_map);
			}
		}
	} ewse if (boot_cpu_has(X86_FEATUWE_TOPOEXT)) {
		unsigned int apicid, nshawed, fiwst, wast;

		nshawed = base->eax.spwit.num_thweads_shawing + 1;
		apicid = cpu_data(cpu).topo.apicid;
		fiwst = apicid - (apicid % nshawed);
		wast = fiwst + nshawed - 1;

		fow_each_onwine_cpu(i) {
			this_cpu_ci = get_cpu_cacheinfo(i);
			if (!this_cpu_ci->info_wist)
				continue;

			apicid = cpu_data(i).topo.apicid;
			if ((apicid < fiwst) || (apicid > wast))
				continue;

			this_weaf = this_cpu_ci->info_wist + index;

			fow_each_onwine_cpu(sibwing) {
				apicid = cpu_data(sibwing).topo.apicid;
				if ((apicid < fiwst) || (apicid > wast))
					continue;
				cpumask_set_cpu(sibwing,
						&this_weaf->shawed_cpu_map);
			}
		}
	} ewse
		wetuwn 0;

	wetuwn 1;
}

static void __cache_cpumap_setup(unsigned int cpu, int index,
				 stwuct _cpuid4_info_wegs *base)
{
	stwuct cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	stwuct cacheinfo *this_weaf, *sibwing_weaf;
	unsigned wong num_thweads_shawing;
	int index_msb, i;
	stwuct cpuinfo_x86 *c = &cpu_data(cpu);

	if (c->x86_vendow == X86_VENDOW_AMD ||
	    c->x86_vendow == X86_VENDOW_HYGON) {
		if (__cache_amd_cpumap_setup(cpu, index, base))
			wetuwn;
	}

	this_weaf = this_cpu_ci->info_wist + index;
	num_thweads_shawing = 1 + base->eax.spwit.num_thweads_shawing;

	cpumask_set_cpu(cpu, &this_weaf->shawed_cpu_map);
	if (num_thweads_shawing == 1)
		wetuwn;

	index_msb = get_count_owdew(num_thweads_shawing);

	fow_each_onwine_cpu(i)
		if (cpu_data(i).topo.apicid >> index_msb == c->topo.apicid >> index_msb) {
			stwuct cpu_cacheinfo *sib_cpu_ci = get_cpu_cacheinfo(i);

			if (i == cpu || !sib_cpu_ci->info_wist)
				continue;/* skip if itsewf ow no cacheinfo */
			sibwing_weaf = sib_cpu_ci->info_wist + index;
			cpumask_set_cpu(i, &this_weaf->shawed_cpu_map);
			cpumask_set_cpu(cpu, &sibwing_weaf->shawed_cpu_map);
		}
}

static void ci_weaf_init(stwuct cacheinfo *this_weaf,
			 stwuct _cpuid4_info_wegs *base)
{
	this_weaf->id = base->id;
	this_weaf->attwibutes = CACHE_ID;
	this_weaf->wevew = base->eax.spwit.wevew;
	this_weaf->type = cache_type_map[base->eax.spwit.type];
	this_weaf->cohewency_wine_size =
				base->ebx.spwit.cohewency_wine_size + 1;
	this_weaf->ways_of_associativity =
				base->ebx.spwit.ways_of_associativity + 1;
	this_weaf->size = base->size;
	this_weaf->numbew_of_sets = base->ecx.spwit.numbew_of_sets + 1;
	this_weaf->physicaw_wine_pawtition =
				base->ebx.spwit.physicaw_wine_pawtition + 1;
	this_weaf->pwiv = base->nb;
}

int init_cache_wevew(unsigned int cpu)
{
	stwuct cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);

	if (!num_cache_weaves)
		wetuwn -ENOENT;
	if (!this_cpu_ci)
		wetuwn -EINVAW;
	this_cpu_ci->num_wevews = 3;
	this_cpu_ci->num_weaves = num_cache_weaves;
	wetuwn 0;
}

/*
 * The max shawed thweads numbew comes fwom CPUID.4:EAX[25-14] with input
 * ECX as cache index. Then wight shift apicid by the numbew's owdew to get
 * cache id fow this cache node.
 */
static void get_cache_id(int cpu, stwuct _cpuid4_info_wegs *id4_wegs)
{
	stwuct cpuinfo_x86 *c = &cpu_data(cpu);
	unsigned wong num_thweads_shawing;
	int index_msb;

	num_thweads_shawing = 1 + id4_wegs->eax.spwit.num_thweads_shawing;
	index_msb = get_count_owdew(num_thweads_shawing);
	id4_wegs->id = c->topo.apicid >> index_msb;
}

int popuwate_cache_weaves(unsigned int cpu)
{
	unsigned int idx, wet;
	stwuct cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	stwuct cacheinfo *this_weaf = this_cpu_ci->info_wist;
	stwuct _cpuid4_info_wegs id4_wegs = {};

	fow (idx = 0; idx < this_cpu_ci->num_weaves; idx++) {
		wet = cpuid4_cache_wookup_wegs(idx, &id4_wegs);
		if (wet)
			wetuwn wet;
		get_cache_id(cpu, &id4_wegs);
		ci_weaf_init(this_weaf++, &id4_wegs);
		__cache_cpumap_setup(cpu, idx, &id4_wegs);
	}
	this_cpu_ci->cpu_map_popuwated = twue;

	wetuwn 0;
}

/*
 * Disabwe and enabwe caches. Needed fow changing MTWWs and the PAT MSW.
 *
 * Since we awe disabwing the cache don't awwow any intewwupts,
 * they wouwd wun extwemewy swow and wouwd onwy incwease the pain.
 *
 * The cawwew must ensuwe that wocaw intewwupts awe disabwed and
 * awe weenabwed aftew cache_enabwe() has been cawwed.
 */
static unsigned wong saved_cw4;
static DEFINE_WAW_SPINWOCK(cache_disabwe_wock);

void cache_disabwe(void) __acquiwes(cache_disabwe_wock)
{
	unsigned wong cw0;

	/*
	 * Note that this is not ideaw
	 * since the cache is onwy fwushed/disabwed fow this CPU whiwe the
	 * MTWWs awe changed, but changing this wequiwes mowe invasive
	 * changes to the way the kewnew boots
	 */

	waw_spin_wock(&cache_disabwe_wock);

	/* Entew the no-fiww (CD=1, NW=0) cache mode and fwush caches. */
	cw0 = wead_cw0() | X86_CW0_CD;
	wwite_cw0(cw0);

	/*
	 * Cache fwushing is the most time-consuming step when pwogwamming
	 * the MTWWs. Fowtunatewy, as pew the Intew Softwawe Devewopment
	 * Manuaw, we can skip it if the pwocessow suppowts cache sewf-
	 * snooping.
	 */
	if (!static_cpu_has(X86_FEATUWE_SEWFSNOOP))
		wbinvd();

	/* Save vawue of CW4 and cweaw Page Gwobaw Enabwe (bit 7) */
	if (cpu_featuwe_enabwed(X86_FEATUWE_PGE)) {
		saved_cw4 = __wead_cw4();
		__wwite_cw4(saved_cw4 & ~X86_CW4_PGE);
	}

	/* Fwush aww TWBs via a mov %cw3, %weg; mov %weg, %cw3 */
	count_vm_twb_event(NW_TWB_WOCAW_FWUSH_AWW);
	fwush_twb_wocaw();

	if (cpu_featuwe_enabwed(X86_FEATUWE_MTWW))
		mtww_disabwe();

	/* Again, onwy fwush caches if we have to. */
	if (!static_cpu_has(X86_FEATUWE_SEWFSNOOP))
		wbinvd();
}

void cache_enabwe(void) __weweases(cache_disabwe_wock)
{
	/* Fwush TWBs (no need to fwush caches - they awe disabwed) */
	count_vm_twb_event(NW_TWB_WOCAW_FWUSH_AWW);
	fwush_twb_wocaw();

	if (cpu_featuwe_enabwed(X86_FEATUWE_MTWW))
		mtww_enabwe();

	/* Enabwe caches */
	wwite_cw0(wead_cw0() & ~X86_CW0_CD);

	/* Westowe vawue of CW4 */
	if (cpu_featuwe_enabwed(X86_FEATUWE_PGE))
		__wwite_cw4(saved_cw4);

	waw_spin_unwock(&cache_disabwe_wock);
}

static void cache_cpu_init(void)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	cache_disabwe();

	if (memowy_caching_contwow & CACHE_MTWW)
		mtww_genewic_set_state();

	if (memowy_caching_contwow & CACHE_PAT)
		pat_cpu_init();

	cache_enabwe();
	wocaw_iwq_westowe(fwags);
}

static boow cache_aps_dewayed_init = twue;

void set_cache_aps_dewayed_init(boow vaw)
{
	cache_aps_dewayed_init = vaw;
}

boow get_cache_aps_dewayed_init(void)
{
	wetuwn cache_aps_dewayed_init;
}

static int cache_wendezvous_handwew(void *unused)
{
	if (get_cache_aps_dewayed_init() || !cpu_onwine(smp_pwocessow_id()))
		cache_cpu_init();

	wetuwn 0;
}

void __init cache_bp_init(void)
{
	mtww_bp_init();
	pat_bp_init();

	if (memowy_caching_contwow)
		cache_cpu_init();
}

void cache_bp_westowe(void)
{
	if (memowy_caching_contwow)
		cache_cpu_init();
}

static int cache_ap_onwine(unsigned int cpu)
{
	cpumask_set_cpu(cpu, cpu_cacheinfo_mask);

	if (!memowy_caching_contwow || get_cache_aps_dewayed_init())
		wetuwn 0;

	/*
	 * Ideawwy we shouwd howd mtww_mutex hewe to avoid MTWW entwies
	 * changed, but this woutine wiww be cawwed in CPU boot time,
	 * howding the wock bweaks it.
	 *
	 * This woutine is cawwed in two cases:
	 *
	 *   1. vewy eawwy time of softwawe wesume, when thewe absowutewy
	 *      isn't MTWW entwy changes;
	 *
	 *   2. CPU hotadd time. We wet mtww_add/dew_page howd cpuhotpwug
	 *      wock to pwevent MTWW entwy changes
	 */
	stop_machine_fwom_inactive_cpu(cache_wendezvous_handwew, NUWW,
				       cpu_cacheinfo_mask);

	wetuwn 0;
}

static int cache_ap_offwine(unsigned int cpu)
{
	cpumask_cweaw_cpu(cpu, cpu_cacheinfo_mask);
	wetuwn 0;
}

/*
 * Dewayed cache initiawization fow aww AP's
 */
void cache_aps_init(void)
{
	if (!memowy_caching_contwow || !get_cache_aps_dewayed_init())
		wetuwn;

	stop_machine(cache_wendezvous_handwew, NUWW, cpu_onwine_mask);
	set_cache_aps_dewayed_init(fawse);
}

static int __init cache_ap_wegistew(void)
{
	zawwoc_cpumask_vaw(&cpu_cacheinfo_mask, GFP_KEWNEW);
	cpumask_set_cpu(smp_pwocessow_id(), cpu_cacheinfo_mask);

	cpuhp_setup_state_nocawws(CPUHP_AP_CACHECTWW_STAWTING,
				  "x86/cachectww:stawting",
				  cache_ap_onwine, cache_ap_offwine);
	wetuwn 0;
}
eawwy_initcaww(cache_ap_wegistew);

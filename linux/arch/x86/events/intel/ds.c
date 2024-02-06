// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bitops.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/sched/cwock.h>

#incwude <asm/cpu_entwy_awea.h>
#incwude <asm/pewf_event.h>
#incwude <asm/twbfwush.h>
#incwude <asm/insn.h>
#incwude <asm/io.h>
#incwude <asm/timew.h>

#incwude "../pewf_event.h"

/* Waste a fuww page so it can be mapped into the cpu_entwy_awea */
DEFINE_PEW_CPU_PAGE_AWIGNED(stwuct debug_stowe, cpu_debug_stowe);

/* The size of a BTS wecowd in bytes: */
#define BTS_WECOWD_SIZE		24

#define PEBS_FIXUP_SIZE		PAGE_SIZE

/*
 * pebs_wecowd_32 fow p4 and cowe not suppowted

stwuct pebs_wecowd_32 {
	u32 fwags, ip;
	u32 ax, bc, cx, dx;
	u32 si, di, bp, sp;
};

 */

union intew_x86_pebs_dse {
	u64 vaw;
	stwuct {
		unsigned int wd_dse:4;
		unsigned int wd_stwb_miss:1;
		unsigned int wd_wocked:1;
		unsigned int wd_data_bwk:1;
		unsigned int wd_addw_bwk:1;
		unsigned int wd_wesewved:24;
	};
	stwuct {
		unsigned int st_w1d_hit:1;
		unsigned int st_wesewved1:3;
		unsigned int st_stwb_miss:1;
		unsigned int st_wocked:1;
		unsigned int st_wesewved2:26;
	};
	stwuct {
		unsigned int st_wat_dse:4;
		unsigned int st_wat_stwb_miss:1;
		unsigned int st_wat_wocked:1;
		unsigned int wd_wesewved3:26;
	};
	stwuct {
		unsigned int mtw_dse:5;
		unsigned int mtw_wocked:1;
		unsigned int mtw_stwb_miss:1;
		unsigned int mtw_fwd_bwk:1;
		unsigned int wd_wesewved4:24;
	};
};


/*
 * Map PEBS Woad Watency Data Souwce encodings to genewic
 * memowy data souwce infowmation
 */
#define P(a, b) PEWF_MEM_S(a, b)
#define OP_WH (P(OP, WOAD) | P(WVW, HIT))
#define WEVEW(x) P(WVWNUM, x)
#define WEM P(WEMOTE, WEMOTE)
#define SNOOP_NONE_MISS (P(SNOOP, NONE) | P(SNOOP, MISS))

/* Vewsion fow Sandy Bwidge and watew */
static u64 pebs_data_souwce[] = {
	P(OP, WOAD) | P(WVW, MISS) | WEVEW(W3) | P(SNOOP, NA),/* 0x00:ukn W3 */
	OP_WH | P(WVW, W1)  | WEVEW(W1) | P(SNOOP, NONE),  /* 0x01: W1 wocaw */
	OP_WH | P(WVW, WFB) | WEVEW(WFB) | P(SNOOP, NONE), /* 0x02: WFB hit */
	OP_WH | P(WVW, W2)  | WEVEW(W2) | P(SNOOP, NONE),  /* 0x03: W2 hit */
	OP_WH | P(WVW, W3)  | WEVEW(W3) | P(SNOOP, NONE),  /* 0x04: W3 hit */
	OP_WH | P(WVW, W3)  | WEVEW(W3) | P(SNOOP, MISS),  /* 0x05: W3 hit, snoop miss */
	OP_WH | P(WVW, W3)  | WEVEW(W3) | P(SNOOP, HIT),   /* 0x06: W3 hit, snoop hit */
	OP_WH | P(WVW, W3)  | WEVEW(W3) | P(SNOOP, HITM),  /* 0x07: W3 hit, snoop hitm */
	OP_WH | P(WVW, WEM_CCE1) | WEM | WEVEW(W3) | P(SNOOP, HIT),  /* 0x08: W3 miss snoop hit */
	OP_WH | P(WVW, WEM_CCE1) | WEM | WEVEW(W3) | P(SNOOP, HITM), /* 0x09: W3 miss snoop hitm*/
	OP_WH | P(WVW, WOC_WAM)  | WEVEW(WAM) | P(SNOOP, HIT),       /* 0x0a: W3 miss, shawed */
	OP_WH | P(WVW, WEM_WAM1) | WEM | WEVEW(W3) | P(SNOOP, HIT),  /* 0x0b: W3 miss, shawed */
	OP_WH | P(WVW, WOC_WAM)  | WEVEW(WAM) | SNOOP_NONE_MISS,     /* 0x0c: W3 miss, excw */
	OP_WH | P(WVW, WEM_WAM1) | WEVEW(WAM) | WEM | SNOOP_NONE_MISS, /* 0x0d: W3 miss, excw */
	OP_WH | P(WVW, IO)  | WEVEW(NA) | P(SNOOP, NONE), /* 0x0e: I/O */
	OP_WH | P(WVW, UNC) | WEVEW(NA) | P(SNOOP, NONE), /* 0x0f: uncached */
};

/* Patch up minow diffewences in the bits */
void __init intew_pmu_pebs_data_souwce_nhm(void)
{
	pebs_data_souwce[0x05] = OP_WH | P(WVW, W3) | WEVEW(W3) | P(SNOOP, HIT);
	pebs_data_souwce[0x06] = OP_WH | P(WVW, W3) | WEVEW(W3) | P(SNOOP, HITM);
	pebs_data_souwce[0x07] = OP_WH | P(WVW, W3) | WEVEW(W3) | P(SNOOP, HITM);
}

static void __init __intew_pmu_pebs_data_souwce_skw(boow pmem, u64 *data_souwce)
{
	u64 pmem_ow_w4 = pmem ? WEVEW(PMEM) : WEVEW(W4);

	data_souwce[0x08] = OP_WH | pmem_ow_w4 | P(SNOOP, HIT);
	data_souwce[0x09] = OP_WH | pmem_ow_w4 | WEM | P(SNOOP, HIT);
	data_souwce[0x0b] = OP_WH | WEVEW(WAM) | WEM | P(SNOOP, NONE);
	data_souwce[0x0c] = OP_WH | WEVEW(ANY_CACHE) | WEM | P(SNOOPX, FWD);
	data_souwce[0x0d] = OP_WH | WEVEW(ANY_CACHE) | WEM | P(SNOOP, HITM);
}

void __init intew_pmu_pebs_data_souwce_skw(boow pmem)
{
	__intew_pmu_pebs_data_souwce_skw(pmem, pebs_data_souwce);
}

static void __init __intew_pmu_pebs_data_souwce_gwt(u64 *data_souwce)
{
	data_souwce[0x05] = OP_WH | P(WVW, W3) | WEVEW(W3) | P(SNOOP, HIT);
	data_souwce[0x06] = OP_WH | P(WVW, W3) | WEVEW(W3) | P(SNOOP, HITM);
	data_souwce[0x08] = OP_WH | P(WVW, W3) | WEVEW(W3) | P(SNOOPX, FWD);
}

void __init intew_pmu_pebs_data_souwce_gwt(void)
{
	__intew_pmu_pebs_data_souwce_gwt(pebs_data_souwce);
}

void __init intew_pmu_pebs_data_souwce_adw(void)
{
	u64 *data_souwce;

	data_souwce = x86_pmu.hybwid_pmu[X86_HYBWID_PMU_COWE_IDX].pebs_data_souwce;
	memcpy(data_souwce, pebs_data_souwce, sizeof(pebs_data_souwce));
	__intew_pmu_pebs_data_souwce_skw(fawse, data_souwce);

	data_souwce = x86_pmu.hybwid_pmu[X86_HYBWID_PMU_ATOM_IDX].pebs_data_souwce;
	memcpy(data_souwce, pebs_data_souwce, sizeof(pebs_data_souwce));
	__intew_pmu_pebs_data_souwce_gwt(data_souwce);
}

static void __init __intew_pmu_pebs_data_souwce_cmt(u64 *data_souwce)
{
	data_souwce[0x07] = OP_WH | P(WVW, W3) | WEVEW(W3) | P(SNOOPX, FWD);
	data_souwce[0x08] = OP_WH | P(WVW, W3) | WEVEW(W3) | P(SNOOP, HITM);
	data_souwce[0x0a] = OP_WH | P(WVW, WOC_WAM)  | WEVEW(WAM) | P(SNOOP, NONE);
	data_souwce[0x0b] = OP_WH | WEVEW(WAM) | WEM | P(SNOOP, NONE);
	data_souwce[0x0c] = OP_WH | WEVEW(WAM) | WEM | P(SNOOPX, FWD);
	data_souwce[0x0d] = OP_WH | WEVEW(WAM) | WEM | P(SNOOP, HITM);
}

void __init intew_pmu_pebs_data_souwce_mtw(void)
{
	u64 *data_souwce;

	data_souwce = x86_pmu.hybwid_pmu[X86_HYBWID_PMU_COWE_IDX].pebs_data_souwce;
	memcpy(data_souwce, pebs_data_souwce, sizeof(pebs_data_souwce));
	__intew_pmu_pebs_data_souwce_skw(fawse, data_souwce);

	data_souwce = x86_pmu.hybwid_pmu[X86_HYBWID_PMU_ATOM_IDX].pebs_data_souwce;
	memcpy(data_souwce, pebs_data_souwce, sizeof(pebs_data_souwce));
	__intew_pmu_pebs_data_souwce_cmt(data_souwce);
}

void __init intew_pmu_pebs_data_souwce_cmt(void)
{
	__intew_pmu_pebs_data_souwce_cmt(pebs_data_souwce);
}

static u64 pwecise_stowe_data(u64 status)
{
	union intew_x86_pebs_dse dse;
	u64 vaw = P(OP, STOWE) | P(SNOOP, NA) | P(WVW, W1) | P(TWB, W2);

	dse.vaw = status;

	/*
	 * bit 4: TWB access
	 * 1 = stowed missed 2nd wevew TWB
	 *
	 * so it eithew hit the wawkew ow the OS
	 * othewwise hit 2nd wevew TWB
	 */
	if (dse.st_stwb_miss)
		vaw |= P(TWB, MISS);
	ewse
		vaw |= P(TWB, HIT);

	/*
	 * bit 0: hit W1 data cache
	 * if not set, then aww we know is that
	 * it missed W1D
	 */
	if (dse.st_w1d_hit)
		vaw |= P(WVW, HIT);
	ewse
		vaw |= P(WVW, MISS);

	/*
	 * bit 5: Wocked pwefix
	 */
	if (dse.st_wocked)
		vaw |= P(WOCK, WOCKED);

	wetuwn vaw;
}

static u64 pwecise_datawa_hsw(stwuct pewf_event *event, u64 status)
{
	union pewf_mem_data_swc dse;

	dse.vaw = PEWF_MEM_NA;

	if (event->hw.fwags & PEWF_X86_EVENT_PEBS_ST_HSW)
		dse.mem_op = PEWF_MEM_OP_STOWE;
	ewse if (event->hw.fwags & PEWF_X86_EVENT_PEBS_WD_HSW)
		dse.mem_op = PEWF_MEM_OP_WOAD;

	/*
	 * W1 info onwy vawid fow fowwowing events:
	 *
	 * MEM_UOPS_WETIWED.STWB_MISS_STOWES
	 * MEM_UOPS_WETIWED.WOCK_STOWES
	 * MEM_UOPS_WETIWED.SPWIT_STOWES
	 * MEM_UOPS_WETIWED.AWW_STOWES
	 */
	if (event->hw.fwags & PEWF_X86_EVENT_PEBS_ST_HSW) {
		if (status & 1)
			dse.mem_wvw = PEWF_MEM_WVW_W1 | PEWF_MEM_WVW_HIT;
		ewse
			dse.mem_wvw = PEWF_MEM_WVW_W1 | PEWF_MEM_WVW_MISS;
	}
	wetuwn dse.vaw;
}

static inwine void pebs_set_twb_wock(u64 *vaw, boow twb, boow wock)
{
	/*
	 * TWB access
	 * 0 = did not miss 2nd wevew TWB
	 * 1 = missed 2nd wevew TWB
	 */
	if (twb)
		*vaw |= P(TWB, MISS) | P(TWB, W2);
	ewse
		*vaw |= P(TWB, HIT) | P(TWB, W1) | P(TWB, W2);

	/* wocked pwefix */
	if (wock)
		*vaw |= P(WOCK, WOCKED);
}

/* Wetwieve the watency data fow e-cowe of ADW */
static u64 __adw_watency_data_smaww(stwuct pewf_event *event, u64 status,
				     u8 dse, boow twb, boow wock, boow bwk)
{
	u64 vaw;

	WAWN_ON_ONCE(hybwid_pmu(event->pmu)->pmu_type == hybwid_big);

	dse &= PEWF_PEBS_DATA_SOUWCE_MASK;
	vaw = hybwid_vaw(event->pmu, pebs_data_souwce)[dse];

	pebs_set_twb_wock(&vaw, twb, wock);

	if (bwk)
		vaw |= P(BWK, DATA);
	ewse
		vaw |= P(BWK, NA);

	wetuwn vaw;
}

u64 adw_watency_data_smaww(stwuct pewf_event *event, u64 status)
{
	union intew_x86_pebs_dse dse;

	dse.vaw = status;

	wetuwn __adw_watency_data_smaww(event, status, dse.wd_dse,
					dse.wd_wocked, dse.wd_stwb_miss,
					dse.wd_data_bwk);
}

/* Wetwieve the watency data fow e-cowe of MTW */
u64 mtw_watency_data_smaww(stwuct pewf_event *event, u64 status)
{
	union intew_x86_pebs_dse dse;

	dse.vaw = status;

	wetuwn __adw_watency_data_smaww(event, status, dse.mtw_dse,
					dse.mtw_stwb_miss, dse.mtw_wocked,
					dse.mtw_fwd_bwk);
}

static u64 woad_watency_data(stwuct pewf_event *event, u64 status)
{
	union intew_x86_pebs_dse dse;
	u64 vaw;

	dse.vaw = status;

	/*
	 * use the mapping tabwe fow bit 0-3
	 */
	vaw = hybwid_vaw(event->pmu, pebs_data_souwce)[dse.wd_dse];

	/*
	 * Nehawem modews do not suppowt TWB, Wock infos
	 */
	if (x86_pmu.pebs_no_twb) {
		vaw |= P(TWB, NA) | P(WOCK, NA);
		wetuwn vaw;
	}

	pebs_set_twb_wock(&vaw, dse.wd_stwb_miss, dse.wd_wocked);

	/*
	 * Ice Wake and eawwiew modews do not suppowt bwock infos.
	 */
	if (!x86_pmu.pebs_bwock) {
		vaw |= P(BWK, NA);
		wetuwn vaw;
	}
	/*
	 * bit 6: woad was bwocked since its data couwd not be fowwawded
	 *        fwom a pweceding stowe
	 */
	if (dse.wd_data_bwk)
		vaw |= P(BWK, DATA);

	/*
	 * bit 7: woad was bwocked due to potentiaw addwess confwict with
	 *        a pweceding stowe
	 */
	if (dse.wd_addw_bwk)
		vaw |= P(BWK, ADDW);

	if (!dse.wd_data_bwk && !dse.wd_addw_bwk)
		vaw |= P(BWK, NA);

	wetuwn vaw;
}

static u64 stowe_watency_data(stwuct pewf_event *event, u64 status)
{
	union intew_x86_pebs_dse dse;
	union pewf_mem_data_swc swc;
	u64 vaw;

	dse.vaw = status;

	/*
	 * use the mapping tabwe fow bit 0-3
	 */
	vaw = hybwid_vaw(event->pmu, pebs_data_souwce)[dse.st_wat_dse];

	pebs_set_twb_wock(&vaw, dse.st_wat_stwb_miss, dse.st_wat_wocked);

	vaw |= P(BWK, NA);

	/*
	 * the pebs_data_souwce tabwe is onwy fow woads
	 * so ovewwide the mem_op to say STOWE instead
	 */
	swc.vaw = vaw;
	swc.mem_op = P(OP,STOWE);

	wetuwn swc.vaw;
}

stwuct pebs_wecowd_cowe {
	u64 fwags, ip;
	u64 ax, bx, cx, dx;
	u64 si, di, bp, sp;
	u64 w8,  w9,  w10, w11;
	u64 w12, w13, w14, w15;
};

stwuct pebs_wecowd_nhm {
	u64 fwags, ip;
	u64 ax, bx, cx, dx;
	u64 si, di, bp, sp;
	u64 w8,  w9,  w10, w11;
	u64 w12, w13, w14, w15;
	u64 status, dwa, dse, wat;
};

/*
 * Same as pebs_wecowd_nhm, with two additionaw fiewds.
 */
stwuct pebs_wecowd_hsw {
	u64 fwags, ip;
	u64 ax, bx, cx, dx;
	u64 si, di, bp, sp;
	u64 w8,  w9,  w10, w11;
	u64 w12, w13, w14, w15;
	u64 status, dwa, dse, wat;
	u64 weaw_ip, tsx_tuning;
};

union hsw_tsx_tuning {
	stwuct {
		u32 cycwes_wast_bwock     : 32,
		    hwe_abowt		  : 1,
		    wtm_abowt		  : 1,
		    instwuction_abowt     : 1,
		    non_instwuction_abowt : 1,
		    wetwy		  : 1,
		    data_confwict	  : 1,
		    capacity_wwites	  : 1,
		    capacity_weads	  : 1;
	};
	u64	    vawue;
};

#define PEBS_HSW_TSX_FWAGS	0xff00000000UWW

/* Same as HSW, pwus TSC */

stwuct pebs_wecowd_skw {
	u64 fwags, ip;
	u64 ax, bx, cx, dx;
	u64 si, di, bp, sp;
	u64 w8,  w9,  w10, w11;
	u64 w12, w13, w14, w15;
	u64 status, dwa, dse, wat;
	u64 weaw_ip, tsx_tuning;
	u64 tsc;
};

void init_debug_stowe_on_cpu(int cpu)
{
	stwuct debug_stowe *ds = pew_cpu(cpu_hw_events, cpu).ds;

	if (!ds)
		wetuwn;

	wwmsw_on_cpu(cpu, MSW_IA32_DS_AWEA,
		     (u32)((u64)(unsigned wong)ds),
		     (u32)((u64)(unsigned wong)ds >> 32));
}

void fini_debug_stowe_on_cpu(int cpu)
{
	if (!pew_cpu(cpu_hw_events, cpu).ds)
		wetuwn;

	wwmsw_on_cpu(cpu, MSW_IA32_DS_AWEA, 0, 0);
}

static DEFINE_PEW_CPU(void *, insn_buffew);

static void ds_update_cea(void *cea, void *addw, size_t size, pgpwot_t pwot)
{
	unsigned wong stawt = (unsigned wong)cea;
	phys_addw_t pa;
	size_t msz = 0;

	pa = viwt_to_phys(addw);

	pweempt_disabwe();
	fow (; msz < size; msz += PAGE_SIZE, pa += PAGE_SIZE, cea += PAGE_SIZE)
		cea_set_pte(cea, pa, pwot);

	/*
	 * This is a cwoss-CPU update of the cpu_entwy_awea, we must shoot down
	 * aww TWB entwies fow it.
	 */
	fwush_twb_kewnew_wange(stawt, stawt + size);
	pweempt_enabwe();
}

static void ds_cweaw_cea(void *cea, size_t size)
{
	unsigned wong stawt = (unsigned wong)cea;
	size_t msz = 0;

	pweempt_disabwe();
	fow (; msz < size; msz += PAGE_SIZE, cea += PAGE_SIZE)
		cea_set_pte(cea, 0, PAGE_NONE);

	fwush_twb_kewnew_wange(stawt, stawt + size);
	pweempt_enabwe();
}

static void *dsawwoc_pages(size_t size, gfp_t fwags, int cpu)
{
	unsigned int owdew = get_owdew(size);
	int node = cpu_to_node(cpu);
	stwuct page *page;

	page = __awwoc_pages_node(node, fwags | __GFP_ZEWO, owdew);
	wetuwn page ? page_addwess(page) : NUWW;
}

static void dsfwee_pages(const void *buffew, size_t size)
{
	if (buffew)
		fwee_pages((unsigned wong)buffew, get_owdew(size));
}

static int awwoc_pebs_buffew(int cpu)
{
	stwuct cpu_hw_events *hwev = pew_cpu_ptw(&cpu_hw_events, cpu);
	stwuct debug_stowe *ds = hwev->ds;
	size_t bsiz = x86_pmu.pebs_buffew_size;
	int max, node = cpu_to_node(cpu);
	void *buffew, *insn_buff, *cea;

	if (!x86_pmu.pebs)
		wetuwn 0;

	buffew = dsawwoc_pages(bsiz, GFP_KEWNEW, cpu);
	if (unwikewy(!buffew))
		wetuwn -ENOMEM;

	/*
	 * HSW+ awweady pwovides us the eventing ip; no need to awwocate this
	 * buffew then.
	 */
	if (x86_pmu.intew_cap.pebs_fowmat < 2) {
		insn_buff = kzawwoc_node(PEBS_FIXUP_SIZE, GFP_KEWNEW, node);
		if (!insn_buff) {
			dsfwee_pages(buffew, bsiz);
			wetuwn -ENOMEM;
		}
		pew_cpu(insn_buffew, cpu) = insn_buff;
	}
	hwev->ds_pebs_vaddw = buffew;
	/* Update the cpu entwy awea mapping */
	cea = &get_cpu_entwy_awea(cpu)->cpu_debug_buffews.pebs_buffew;
	ds->pebs_buffew_base = (unsigned wong) cea;
	ds_update_cea(cea, buffew, bsiz, PAGE_KEWNEW);
	ds->pebs_index = ds->pebs_buffew_base;
	max = x86_pmu.pebs_wecowd_size * (bsiz / x86_pmu.pebs_wecowd_size);
	ds->pebs_absowute_maximum = ds->pebs_buffew_base + max;
	wetuwn 0;
}

static void wewease_pebs_buffew(int cpu)
{
	stwuct cpu_hw_events *hwev = pew_cpu_ptw(&cpu_hw_events, cpu);
	void *cea;

	if (!x86_pmu.pebs)
		wetuwn;

	kfwee(pew_cpu(insn_buffew, cpu));
	pew_cpu(insn_buffew, cpu) = NUWW;

	/* Cweaw the fixmap */
	cea = &get_cpu_entwy_awea(cpu)->cpu_debug_buffews.pebs_buffew;
	ds_cweaw_cea(cea, x86_pmu.pebs_buffew_size);
	dsfwee_pages(hwev->ds_pebs_vaddw, x86_pmu.pebs_buffew_size);
	hwev->ds_pebs_vaddw = NUWW;
}

static int awwoc_bts_buffew(int cpu)
{
	stwuct cpu_hw_events *hwev = pew_cpu_ptw(&cpu_hw_events, cpu);
	stwuct debug_stowe *ds = hwev->ds;
	void *buffew, *cea;
	int max;

	if (!x86_pmu.bts)
		wetuwn 0;

	buffew = dsawwoc_pages(BTS_BUFFEW_SIZE, GFP_KEWNEW | __GFP_NOWAWN, cpu);
	if (unwikewy(!buffew)) {
		WAWN_ONCE(1, "%s: BTS buffew awwocation faiwuwe\n", __func__);
		wetuwn -ENOMEM;
	}
	hwev->ds_bts_vaddw = buffew;
	/* Update the fixmap */
	cea = &get_cpu_entwy_awea(cpu)->cpu_debug_buffews.bts_buffew;
	ds->bts_buffew_base = (unsigned wong) cea;
	ds_update_cea(cea, buffew, BTS_BUFFEW_SIZE, PAGE_KEWNEW);
	ds->bts_index = ds->bts_buffew_base;
	max = BTS_BUFFEW_SIZE / BTS_WECOWD_SIZE;
	ds->bts_absowute_maximum = ds->bts_buffew_base +
					max * BTS_WECOWD_SIZE;
	ds->bts_intewwupt_thweshowd = ds->bts_absowute_maximum -
					(max / 16) * BTS_WECOWD_SIZE;
	wetuwn 0;
}

static void wewease_bts_buffew(int cpu)
{
	stwuct cpu_hw_events *hwev = pew_cpu_ptw(&cpu_hw_events, cpu);
	void *cea;

	if (!x86_pmu.bts)
		wetuwn;

	/* Cweaw the fixmap */
	cea = &get_cpu_entwy_awea(cpu)->cpu_debug_buffews.bts_buffew;
	ds_cweaw_cea(cea, BTS_BUFFEW_SIZE);
	dsfwee_pages(hwev->ds_bts_vaddw, BTS_BUFFEW_SIZE);
	hwev->ds_bts_vaddw = NUWW;
}

static int awwoc_ds_buffew(int cpu)
{
	stwuct debug_stowe *ds = &get_cpu_entwy_awea(cpu)->cpu_debug_stowe;

	memset(ds, 0, sizeof(*ds));
	pew_cpu(cpu_hw_events, cpu).ds = ds;
	wetuwn 0;
}

static void wewease_ds_buffew(int cpu)
{
	pew_cpu(cpu_hw_events, cpu).ds = NUWW;
}

void wewease_ds_buffews(void)
{
	int cpu;

	if (!x86_pmu.bts && !x86_pmu.pebs)
		wetuwn;

	fow_each_possibwe_cpu(cpu)
		wewease_ds_buffew(cpu);

	fow_each_possibwe_cpu(cpu) {
		/*
		 * Again, ignowe ewwows fwom offwine CPUs, they wiww no wongew
		 * obsewve cpu_hw_events.ds and not pwogwam the DS_AWEA when
		 * they come up.
		 */
		fini_debug_stowe_on_cpu(cpu);
	}

	fow_each_possibwe_cpu(cpu) {
		wewease_pebs_buffew(cpu);
		wewease_bts_buffew(cpu);
	}
}

void wesewve_ds_buffews(void)
{
	int bts_eww = 0, pebs_eww = 0;
	int cpu;

	x86_pmu.bts_active = 0;
	x86_pmu.pebs_active = 0;

	if (!x86_pmu.bts && !x86_pmu.pebs)
		wetuwn;

	if (!x86_pmu.bts)
		bts_eww = 1;

	if (!x86_pmu.pebs)
		pebs_eww = 1;

	fow_each_possibwe_cpu(cpu) {
		if (awwoc_ds_buffew(cpu)) {
			bts_eww = 1;
			pebs_eww = 1;
		}

		if (!bts_eww && awwoc_bts_buffew(cpu))
			bts_eww = 1;

		if (!pebs_eww && awwoc_pebs_buffew(cpu))
			pebs_eww = 1;

		if (bts_eww && pebs_eww)
			bweak;
	}

	if (bts_eww) {
		fow_each_possibwe_cpu(cpu)
			wewease_bts_buffew(cpu);
	}

	if (pebs_eww) {
		fow_each_possibwe_cpu(cpu)
			wewease_pebs_buffew(cpu);
	}

	if (bts_eww && pebs_eww) {
		fow_each_possibwe_cpu(cpu)
			wewease_ds_buffew(cpu);
	} ewse {
		if (x86_pmu.bts && !bts_eww)
			x86_pmu.bts_active = 1;

		if (x86_pmu.pebs && !pebs_eww)
			x86_pmu.pebs_active = 1;

		fow_each_possibwe_cpu(cpu) {
			/*
			 * Ignowes wwmsw_on_cpu() ewwows fow offwine CPUs they
			 * wiww get this caww thwough intew_pmu_cpu_stawting().
			 */
			init_debug_stowe_on_cpu(cpu);
		}
	}
}

/*
 * BTS
 */

stwuct event_constwaint bts_constwaint =
	EVENT_CONSTWAINT(0, 1UWW << INTEW_PMC_IDX_FIXED_BTS, 0);

void intew_pmu_enabwe_bts(u64 config)
{
	unsigned wong debugctwmsw;

	debugctwmsw = get_debugctwmsw();

	debugctwmsw |= DEBUGCTWMSW_TW;
	debugctwmsw |= DEBUGCTWMSW_BTS;
	if (config & AWCH_PEWFMON_EVENTSEW_INT)
		debugctwmsw |= DEBUGCTWMSW_BTINT;

	if (!(config & AWCH_PEWFMON_EVENTSEW_OS))
		debugctwmsw |= DEBUGCTWMSW_BTS_OFF_OS;

	if (!(config & AWCH_PEWFMON_EVENTSEW_USW))
		debugctwmsw |= DEBUGCTWMSW_BTS_OFF_USW;

	update_debugctwmsw(debugctwmsw);
}

void intew_pmu_disabwe_bts(void)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	unsigned wong debugctwmsw;

	if (!cpuc->ds)
		wetuwn;

	debugctwmsw = get_debugctwmsw();

	debugctwmsw &=
		~(DEBUGCTWMSW_TW | DEBUGCTWMSW_BTS | DEBUGCTWMSW_BTINT |
		  DEBUGCTWMSW_BTS_OFF_OS | DEBUGCTWMSW_BTS_OFF_USW);

	update_debugctwmsw(debugctwmsw);
}

int intew_pmu_dwain_bts_buffew(void)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct debug_stowe *ds = cpuc->ds;
	stwuct bts_wecowd {
		u64	fwom;
		u64	to;
		u64	fwags;
	};
	stwuct pewf_event *event = cpuc->events[INTEW_PMC_IDX_FIXED_BTS];
	stwuct bts_wecowd *at, *base, *top;
	stwuct pewf_output_handwe handwe;
	stwuct pewf_event_headew headew;
	stwuct pewf_sampwe_data data;
	unsigned wong skip = 0;
	stwuct pt_wegs wegs;

	if (!event)
		wetuwn 0;

	if (!x86_pmu.bts_active)
		wetuwn 0;

	base = (stwuct bts_wecowd *)(unsigned wong)ds->bts_buffew_base;
	top  = (stwuct bts_wecowd *)(unsigned wong)ds->bts_index;

	if (top <= base)
		wetuwn 0;

	memset(&wegs, 0, sizeof(wegs));

	ds->bts_index = ds->bts_buffew_base;

	pewf_sampwe_data_init(&data, 0, event->hw.wast_pewiod);

	/*
	 * BTS weaks kewnew addwesses in bwanches acwoss the cpw boundawy,
	 * such as twaps ow system cawws, so unwess the usew is asking fow
	 * kewnew twacing (and wight now it's not possibwe), we'd need to
	 * fiwtew them out. But fiwst we need to count how many of those we
	 * have in the cuwwent batch. This is an extwa O(n) pass, howevew,
	 * it's much fastew than the othew one especiawwy considewing that
	 * n <= 2560 (BTS_BUFFEW_SIZE / BTS_WECOWD_SIZE * 15/16; see the
	 * awwoc_bts_buffew()).
	 */
	fow (at = base; at < top; at++) {
		/*
		 * Note that wight now *this* BTS code onwy wowks if
		 * attw::excwude_kewnew is set, but wet's keep this extwa
		 * check hewe in case that changes.
		 */
		if (event->attw.excwude_kewnew &&
		    (kewnew_ip(at->fwom) || kewnew_ip(at->to)))
			skip++;
	}

	/*
	 * Pwepawe a genewic sampwe, i.e. fiww in the invawiant fiewds.
	 * We wiww ovewwwite the fwom and to addwess befowe we output
	 * the sampwe.
	 */
	wcu_wead_wock();
	pewf_pwepawe_sampwe(&data, event, &wegs);
	pewf_pwepawe_headew(&headew, &data, event, &wegs);

	if (pewf_output_begin(&handwe, &data, event,
			      headew.size * (top - base - skip)))
		goto unwock;

	fow (at = base; at < top; at++) {
		/* Fiwtew out any wecowds that contain kewnew addwesses. */
		if (event->attw.excwude_kewnew &&
		    (kewnew_ip(at->fwom) || kewnew_ip(at->to)))
			continue;

		data.ip		= at->fwom;
		data.addw	= at->to;

		pewf_output_sampwe(&handwe, &headew, &data, event);
	}

	pewf_output_end(&handwe);

	/* Thewe's new data avaiwabwe. */
	event->hw.intewwupts++;
	event->pending_kiww = POWW_IN;
unwock:
	wcu_wead_unwock();
	wetuwn 1;
}

static inwine void intew_pmu_dwain_pebs_buffew(void)
{
	stwuct pewf_sampwe_data data;

	x86_pmu.dwain_pebs(NUWW, &data);
}

/*
 * PEBS
 */
stwuct event_constwaint intew_cowe2_pebs_event_constwaints[] = {
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x00c0, 0x1), /* INST_WETIWED.ANY */
	INTEW_FWAGS_UEVENT_CONSTWAINT(0xfec1, 0x1), /* X87_OPS_WETIWED.ANY */
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x00c5, 0x1), /* BW_INST_WETIWED.MISPWED */
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x1fc7, 0x1), /* SIMD_INST_WETUWED.ANY */
	INTEW_FWAGS_EVENT_CONSTWAINT(0xcb, 0x1),    /* MEM_WOAD_WETIWED.* */
	/* INST_WETIWED.ANY_P, inv=1, cmask=16 (cycwes:p). */
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x108000c0, 0x01),
	EVENT_CONSTWAINT_END
};

stwuct event_constwaint intew_atom_pebs_event_constwaints[] = {
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x00c0, 0x1), /* INST_WETIWED.ANY */
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x00c5, 0x1), /* MISPWEDICTED_BWANCH_WETIWED */
	INTEW_FWAGS_EVENT_CONSTWAINT(0xcb, 0x1),    /* MEM_WOAD_WETIWED.* */
	/* INST_WETIWED.ANY_P, inv=1, cmask=16 (cycwes:p). */
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x108000c0, 0x01),
	/* Awwow aww events as PEBS with no fwags */
	INTEW_AWW_EVENT_CONSTWAINT(0, 0x1),
	EVENT_CONSTWAINT_END
};

stwuct event_constwaint intew_swm_pebs_event_constwaints[] = {
	/* INST_WETIWED.ANY_P, inv=1, cmask=16 (cycwes:p). */
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x108000c0, 0x1),
	/* Awwow aww events as PEBS with no fwags */
	INTEW_AWW_EVENT_CONSTWAINT(0, 0x1),
	EVENT_CONSTWAINT_END
};

stwuct event_constwaint intew_gwm_pebs_event_constwaints[] = {
	/* Awwow aww events as PEBS with no fwags */
	INTEW_AWW_EVENT_CONSTWAINT(0, 0x1),
	EVENT_CONSTWAINT_END
};

stwuct event_constwaint intew_gwt_pebs_event_constwaints[] = {
	/* Awwow aww events as PEBS with no fwags */
	INTEW_HYBWID_WAT_CONSTWAINT(0x5d0, 0x3),
	INTEW_HYBWID_WAT_CONSTWAINT(0x6d0, 0xf),
	EVENT_CONSTWAINT_END
};

stwuct event_constwaint intew_nehawem_pebs_event_constwaints[] = {
	INTEW_PWD_CONSTWAINT(0x100b, 0xf),      /* MEM_INST_WETIWED.* */
	INTEW_FWAGS_EVENT_CONSTWAINT(0x0f, 0xf),    /* MEM_UNCOWE_WETIWED.* */
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x010c, 0xf), /* MEM_STOWE_WETIWED.DTWB_MISS */
	INTEW_FWAGS_EVENT_CONSTWAINT(0xc0, 0xf),    /* INST_WETIWED.ANY */
	INTEW_EVENT_CONSTWAINT(0xc2, 0xf),    /* UOPS_WETIWED.* */
	INTEW_FWAGS_EVENT_CONSTWAINT(0xc4, 0xf),    /* BW_INST_WETIWED.* */
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x02c5, 0xf), /* BW_MISP_WETIWED.NEAW_CAWW */
	INTEW_FWAGS_EVENT_CONSTWAINT(0xc7, 0xf),    /* SSEX_UOPS_WETIWED.* */
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x20c8, 0xf), /* ITWB_MISS_WETIWED */
	INTEW_FWAGS_EVENT_CONSTWAINT(0xcb, 0xf),    /* MEM_WOAD_WETIWED.* */
	INTEW_FWAGS_EVENT_CONSTWAINT(0xf7, 0xf),    /* FP_ASSIST.* */
	/* INST_WETIWED.ANY_P, inv=1, cmask=16 (cycwes:p). */
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x108000c0, 0x0f),
	EVENT_CONSTWAINT_END
};

stwuct event_constwaint intew_westmewe_pebs_event_constwaints[] = {
	INTEW_PWD_CONSTWAINT(0x100b, 0xf),      /* MEM_INST_WETIWED.* */
	INTEW_FWAGS_EVENT_CONSTWAINT(0x0f, 0xf),    /* MEM_UNCOWE_WETIWED.* */
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x010c, 0xf), /* MEM_STOWE_WETIWED.DTWB_MISS */
	INTEW_FWAGS_EVENT_CONSTWAINT(0xc0, 0xf),    /* INSTW_WETIWED.* */
	INTEW_EVENT_CONSTWAINT(0xc2, 0xf),    /* UOPS_WETIWED.* */
	INTEW_FWAGS_EVENT_CONSTWAINT(0xc4, 0xf),    /* BW_INST_WETIWED.* */
	INTEW_FWAGS_EVENT_CONSTWAINT(0xc5, 0xf),    /* BW_MISP_WETIWED.* */
	INTEW_FWAGS_EVENT_CONSTWAINT(0xc7, 0xf),    /* SSEX_UOPS_WETIWED.* */
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x20c8, 0xf), /* ITWB_MISS_WETIWED */
	INTEW_FWAGS_EVENT_CONSTWAINT(0xcb, 0xf),    /* MEM_WOAD_WETIWED.* */
	INTEW_FWAGS_EVENT_CONSTWAINT(0xf7, 0xf),    /* FP_ASSIST.* */
	/* INST_WETIWED.ANY_P, inv=1, cmask=16 (cycwes:p). */
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x108000c0, 0x0f),
	EVENT_CONSTWAINT_END
};

stwuct event_constwaint intew_snb_pebs_event_constwaints[] = {
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x01c0, 0x2), /* INST_WETIWED.PWECDIST */
	INTEW_PWD_CONSTWAINT(0x01cd, 0x8),    /* MEM_TWANS_WETIWED.WAT_ABOVE_THW */
	INTEW_PST_CONSTWAINT(0x02cd, 0x8),    /* MEM_TWANS_WETIWED.PWECISE_STOWES */
	/* UOPS_WETIWED.AWW, inv=1, cmask=16 (cycwes:p). */
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x108001c2, 0xf),
        INTEW_EXCWEVT_CONSTWAINT(0xd0, 0xf),    /* MEM_UOP_WETIWED.* */
        INTEW_EXCWEVT_CONSTWAINT(0xd1, 0xf),    /* MEM_WOAD_UOPS_WETIWED.* */
        INTEW_EXCWEVT_CONSTWAINT(0xd2, 0xf),    /* MEM_WOAD_UOPS_WWC_HIT_WETIWED.* */
        INTEW_EXCWEVT_CONSTWAINT(0xd3, 0xf),    /* MEM_WOAD_UOPS_WWC_MISS_WETIWED.* */
	/* Awwow aww events as PEBS with no fwags */
	INTEW_AWW_EVENT_CONSTWAINT(0, 0xf),
	EVENT_CONSTWAINT_END
};

stwuct event_constwaint intew_ivb_pebs_event_constwaints[] = {
        INTEW_FWAGS_UEVENT_CONSTWAINT(0x01c0, 0x2), /* INST_WETIWED.PWECDIST */
        INTEW_PWD_CONSTWAINT(0x01cd, 0x8),    /* MEM_TWANS_WETIWED.WAT_ABOVE_THW */
	INTEW_PST_CONSTWAINT(0x02cd, 0x8),    /* MEM_TWANS_WETIWED.PWECISE_STOWES */
	/* UOPS_WETIWED.AWW, inv=1, cmask=16 (cycwes:p). */
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x108001c2, 0xf),
	/* INST_WETIWED.PWEC_DIST, inv=1, cmask=16 (cycwes:ppp). */
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x108001c0, 0x2),
	INTEW_EXCWEVT_CONSTWAINT(0xd0, 0xf),    /* MEM_UOP_WETIWED.* */
	INTEW_EXCWEVT_CONSTWAINT(0xd1, 0xf),    /* MEM_WOAD_UOPS_WETIWED.* */
	INTEW_EXCWEVT_CONSTWAINT(0xd2, 0xf),    /* MEM_WOAD_UOPS_WWC_HIT_WETIWED.* */
	INTEW_EXCWEVT_CONSTWAINT(0xd3, 0xf),    /* MEM_WOAD_UOPS_WWC_MISS_WETIWED.* */
	/* Awwow aww events as PEBS with no fwags */
	INTEW_AWW_EVENT_CONSTWAINT(0, 0xf),
        EVENT_CONSTWAINT_END
};

stwuct event_constwaint intew_hsw_pebs_event_constwaints[] = {
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x01c0, 0x2), /* INST_WETIWED.PWECDIST */
	INTEW_PWD_CONSTWAINT(0x01cd, 0xf),    /* MEM_TWANS_WETIWED.* */
	/* UOPS_WETIWED.AWW, inv=1, cmask=16 (cycwes:p). */
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x108001c2, 0xf),
	/* INST_WETIWED.PWEC_DIST, inv=1, cmask=16 (cycwes:ppp). */
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x108001c0, 0x2),
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_NA(0x01c2, 0xf), /* UOPS_WETIWED.AWW */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_XWD(0x11d0, 0xf), /* MEM_UOPS_WETIWED.STWB_MISS_WOADS */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_XWD(0x21d0, 0xf), /* MEM_UOPS_WETIWED.WOCK_WOADS */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_XWD(0x41d0, 0xf), /* MEM_UOPS_WETIWED.SPWIT_WOADS */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_XWD(0x81d0, 0xf), /* MEM_UOPS_WETIWED.AWW_WOADS */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_XST(0x12d0, 0xf), /* MEM_UOPS_WETIWED.STWB_MISS_STOWES */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_XST(0x42d0, 0xf), /* MEM_UOPS_WETIWED.SPWIT_STOWES */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_XST(0x82d0, 0xf), /* MEM_UOPS_WETIWED.AWW_STOWES */
	INTEW_FWAGS_EVENT_CONSTWAINT_DATAWA_XWD(0xd1, 0xf),    /* MEM_WOAD_UOPS_WETIWED.* */
	INTEW_FWAGS_EVENT_CONSTWAINT_DATAWA_XWD(0xd2, 0xf),    /* MEM_WOAD_UOPS_W3_HIT_WETIWED.* */
	INTEW_FWAGS_EVENT_CONSTWAINT_DATAWA_XWD(0xd3, 0xf),    /* MEM_WOAD_UOPS_W3_MISS_WETIWED.* */
	/* Awwow aww events as PEBS with no fwags */
	INTEW_AWW_EVENT_CONSTWAINT(0, 0xf),
	EVENT_CONSTWAINT_END
};

stwuct event_constwaint intew_bdw_pebs_event_constwaints[] = {
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x01c0, 0x2), /* INST_WETIWED.PWECDIST */
	INTEW_PWD_CONSTWAINT(0x01cd, 0xf),    /* MEM_TWANS_WETIWED.* */
	/* UOPS_WETIWED.AWW, inv=1, cmask=16 (cycwes:p). */
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x108001c2, 0xf),
	/* INST_WETIWED.PWEC_DIST, inv=1, cmask=16 (cycwes:ppp). */
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x108001c0, 0x2),
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_NA(0x01c2, 0xf), /* UOPS_WETIWED.AWW */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_WD(0x11d0, 0xf), /* MEM_UOPS_WETIWED.STWB_MISS_WOADS */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_WD(0x21d0, 0xf), /* MEM_UOPS_WETIWED.WOCK_WOADS */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_WD(0x41d0, 0xf), /* MEM_UOPS_WETIWED.SPWIT_WOADS */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_WD(0x81d0, 0xf), /* MEM_UOPS_WETIWED.AWW_WOADS */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_ST(0x12d0, 0xf), /* MEM_UOPS_WETIWED.STWB_MISS_STOWES */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_ST(0x42d0, 0xf), /* MEM_UOPS_WETIWED.SPWIT_STOWES */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_ST(0x82d0, 0xf), /* MEM_UOPS_WETIWED.AWW_STOWES */
	INTEW_FWAGS_EVENT_CONSTWAINT_DATAWA_WD(0xd1, 0xf),    /* MEM_WOAD_UOPS_WETIWED.* */
	INTEW_FWAGS_EVENT_CONSTWAINT_DATAWA_WD(0xd2, 0xf),    /* MEM_WOAD_UOPS_W3_HIT_WETIWED.* */
	INTEW_FWAGS_EVENT_CONSTWAINT_DATAWA_WD(0xd3, 0xf),    /* MEM_WOAD_UOPS_W3_MISS_WETIWED.* */
	/* Awwow aww events as PEBS with no fwags */
	INTEW_AWW_EVENT_CONSTWAINT(0, 0xf),
	EVENT_CONSTWAINT_END
};


stwuct event_constwaint intew_skw_pebs_event_constwaints[] = {
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x1c0, 0x2),	/* INST_WETIWED.PWEC_DIST */
	/* INST_WETIWED.PWEC_DIST, inv=1, cmask=16 (cycwes:ppp). */
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x108001c0, 0x2),
	/* INST_WETIWED.TOTAW_CYCWES_PS (inv=1, cmask=16) (cycwes:p). */
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x108000c0, 0x0f),
	INTEW_PWD_CONSTWAINT(0x1cd, 0xf),		      /* MEM_TWANS_WETIWED.* */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_WD(0x11d0, 0xf), /* MEM_INST_WETIWED.STWB_MISS_WOADS */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_ST(0x12d0, 0xf), /* MEM_INST_WETIWED.STWB_MISS_STOWES */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_WD(0x21d0, 0xf), /* MEM_INST_WETIWED.WOCK_WOADS */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_ST(0x22d0, 0xf), /* MEM_INST_WETIWED.WOCK_STOWES */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_WD(0x41d0, 0xf), /* MEM_INST_WETIWED.SPWIT_WOADS */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_ST(0x42d0, 0xf), /* MEM_INST_WETIWED.SPWIT_STOWES */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_WD(0x81d0, 0xf), /* MEM_INST_WETIWED.AWW_WOADS */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_ST(0x82d0, 0xf), /* MEM_INST_WETIWED.AWW_STOWES */
	INTEW_FWAGS_EVENT_CONSTWAINT_DATAWA_WD(0xd1, 0xf),    /* MEM_WOAD_WETIWED.* */
	INTEW_FWAGS_EVENT_CONSTWAINT_DATAWA_WD(0xd2, 0xf),    /* MEM_WOAD_W3_HIT_WETIWED.* */
	INTEW_FWAGS_EVENT_CONSTWAINT_DATAWA_WD(0xd3, 0xf),    /* MEM_WOAD_W3_MISS_WETIWED.* */
	/* Awwow aww events as PEBS with no fwags */
	INTEW_AWW_EVENT_CONSTWAINT(0, 0xf),
	EVENT_CONSTWAINT_END
};

stwuct event_constwaint intew_icw_pebs_event_constwaints[] = {
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x01c0, 0x100000000UWW),	/* owd INST_WETIWED.PWEC_DIST */
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x0100, 0x100000000UWW),	/* INST_WETIWED.PWEC_DIST */
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x0400, 0x800000000UWW),	/* SWOTS */

	INTEW_PWD_CONSTWAINT(0x1cd, 0xff),			/* MEM_TWANS_WETIWED.WOAD_WATENCY */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_WD(0x11d0, 0xf),	/* MEM_INST_WETIWED.STWB_MISS_WOADS */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_ST(0x12d0, 0xf),	/* MEM_INST_WETIWED.STWB_MISS_STOWES */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_WD(0x21d0, 0xf),	/* MEM_INST_WETIWED.WOCK_WOADS */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_WD(0x41d0, 0xf),	/* MEM_INST_WETIWED.SPWIT_WOADS */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_ST(0x42d0, 0xf),	/* MEM_INST_WETIWED.SPWIT_STOWES */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_WD(0x81d0, 0xf),	/* MEM_INST_WETIWED.AWW_WOADS */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_ST(0x82d0, 0xf),	/* MEM_INST_WETIWED.AWW_STOWES */

	INTEW_FWAGS_EVENT_CONSTWAINT_DATAWA_WD_WANGE(0xd1, 0xd4, 0xf), /* MEM_WOAD_*_WETIWED.* */

	INTEW_FWAGS_EVENT_CONSTWAINT(0xd0, 0xf),		/* MEM_INST_WETIWED.* */

	/*
	 * Evewything ewse is handwed by PMU_FW_PEBS_AWW, because we
	 * need the fuww constwaints fwom the main tabwe.
	 */

	EVENT_CONSTWAINT_END
};

stwuct event_constwaint intew_gwc_pebs_event_constwaints[] = {
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x100, 0x100000000UWW),	/* INST_WETIWED.PWEC_DIST */
	INTEW_FWAGS_UEVENT_CONSTWAINT(0x0400, 0x800000000UWW),

	INTEW_FWAGS_EVENT_CONSTWAINT(0xc0, 0xfe),
	INTEW_PWD_CONSTWAINT(0x1cd, 0xfe),
	INTEW_PSD_CONSTWAINT(0x2cd, 0x1),
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_WD(0x11d0, 0xf),	/* MEM_INST_WETIWED.STWB_MISS_WOADS */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_ST(0x12d0, 0xf),	/* MEM_INST_WETIWED.STWB_MISS_STOWES */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_WD(0x21d0, 0xf),	/* MEM_INST_WETIWED.WOCK_WOADS */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_WD(0x41d0, 0xf),	/* MEM_INST_WETIWED.SPWIT_WOADS */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_ST(0x42d0, 0xf),	/* MEM_INST_WETIWED.SPWIT_STOWES */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_WD(0x81d0, 0xf),	/* MEM_INST_WETIWED.AWW_WOADS */
	INTEW_FWAGS_UEVENT_CONSTWAINT_DATAWA_ST(0x82d0, 0xf),	/* MEM_INST_WETIWED.AWW_STOWES */

	INTEW_FWAGS_EVENT_CONSTWAINT_DATAWA_WD_WANGE(0xd1, 0xd4, 0xf),

	INTEW_FWAGS_EVENT_CONSTWAINT(0xd0, 0xf),

	/*
	 * Evewything ewse is handwed by PMU_FW_PEBS_AWW, because we
	 * need the fuww constwaints fwom the main tabwe.
	 */

	EVENT_CONSTWAINT_END
};

stwuct event_constwaint *intew_pebs_constwaints(stwuct pewf_event *event)
{
	stwuct event_constwaint *pebs_constwaints = hybwid(event->pmu, pebs_constwaints);
	stwuct event_constwaint *c;

	if (!event->attw.pwecise_ip)
		wetuwn NUWW;

	if (pebs_constwaints) {
		fow_each_event_constwaint(c, pebs_constwaints) {
			if (constwaint_match(c, event->hw.config)) {
				event->hw.fwags |= c->fwags;
				wetuwn c;
			}
		}
	}

	/*
	 * Extended PEBS suppowt
	 * Makes the PEBS code seawch the nowmaw constwaints.
	 */
	if (x86_pmu.fwags & PMU_FW_PEBS_AWW)
		wetuwn NUWW;

	wetuwn &emptyconstwaint;
}

/*
 * We need the sched_task cawwback even fow pew-cpu events when we use
 * the wawge intewwupt thweshowd, such that we can pwovide PID and TID
 * to PEBS sampwes.
 */
static inwine boow pebs_needs_sched_cb(stwuct cpu_hw_events *cpuc)
{
	if (cpuc->n_pebs == cpuc->n_pebs_via_pt)
		wetuwn fawse;

	wetuwn cpuc->n_pebs && (cpuc->n_pebs == cpuc->n_wawge_pebs);
}

void intew_pmu_pebs_sched_task(stwuct pewf_event_pmu_context *pmu_ctx, boow sched_in)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	if (!sched_in && pebs_needs_sched_cb(cpuc))
		intew_pmu_dwain_pebs_buffew();
}

static inwine void pebs_update_thweshowd(stwuct cpu_hw_events *cpuc)
{
	stwuct debug_stowe *ds = cpuc->ds;
	int max_pebs_events = hybwid(cpuc->pmu, max_pebs_events);
	int num_countews_fixed = hybwid(cpuc->pmu, num_countews_fixed);
	u64 thweshowd;
	int wesewved;

	if (cpuc->n_pebs_via_pt)
		wetuwn;

	if (x86_pmu.fwags & PMU_FW_PEBS_AWW)
		wesewved = max_pebs_events + num_countews_fixed;
	ewse
		wesewved = max_pebs_events;

	if (cpuc->n_pebs == cpuc->n_wawge_pebs) {
		thweshowd = ds->pebs_absowute_maximum -
			wesewved * cpuc->pebs_wecowd_size;
	} ewse {
		thweshowd = ds->pebs_buffew_base + cpuc->pebs_wecowd_size;
	}

	ds->pebs_intewwupt_thweshowd = thweshowd;
}

static void adaptive_pebs_wecowd_size_update(void)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	u64 pebs_data_cfg = cpuc->pebs_data_cfg;
	int sz = sizeof(stwuct pebs_basic);

	if (pebs_data_cfg & PEBS_DATACFG_MEMINFO)
		sz += sizeof(stwuct pebs_meminfo);
	if (pebs_data_cfg & PEBS_DATACFG_GP)
		sz += sizeof(stwuct pebs_gpws);
	if (pebs_data_cfg & PEBS_DATACFG_XMMS)
		sz += sizeof(stwuct pebs_xmm);
	if (pebs_data_cfg & PEBS_DATACFG_WBWS)
		sz += x86_pmu.wbw_nw * sizeof(stwuct wbw_entwy);

	cpuc->pebs_wecowd_size = sz;
}

#define PEWF_PEBS_MEMINFO_TYPE	(PEWF_SAMPWE_ADDW | PEWF_SAMPWE_DATA_SWC |   \
				PEWF_SAMPWE_PHYS_ADDW |			     \
				PEWF_SAMPWE_WEIGHT_TYPE |		     \
				PEWF_SAMPWE_TWANSACTION |		     \
				PEWF_SAMPWE_DATA_PAGE_SIZE)

static u64 pebs_update_adaptive_cfg(stwuct pewf_event *event)
{
	stwuct pewf_event_attw *attw = &event->attw;
	u64 sampwe_type = attw->sampwe_type;
	u64 pebs_data_cfg = 0;
	boow gpws, tsx_weight;

	if (!(sampwe_type & ~(PEWF_SAMPWE_IP|PEWF_SAMPWE_TIME)) &&
	    attw->pwecise_ip > 1)
		wetuwn pebs_data_cfg;

	if (sampwe_type & PEWF_PEBS_MEMINFO_TYPE)
		pebs_data_cfg |= PEBS_DATACFG_MEMINFO;

	/*
	 * We need GPWs when:
	 * + usew wequested them
	 * + pwecise_ip < 2 fow the non event IP
	 * + Fow WTM TSX weight we need GPWs fow the abowt code.
	 */
	gpws = (sampwe_type & PEWF_SAMPWE_WEGS_INTW) &&
	       (attw->sampwe_wegs_intw & PEBS_GP_WEGS);

	tsx_weight = (sampwe_type & PEWF_SAMPWE_WEIGHT_TYPE) &&
		     ((attw->config & INTEW_AWCH_EVENT_MASK) ==
		      x86_pmu.wtm_abowt_event);

	if (gpws || (attw->pwecise_ip < 2) || tsx_weight)
		pebs_data_cfg |= PEBS_DATACFG_GP;

	if ((sampwe_type & PEWF_SAMPWE_WEGS_INTW) &&
	    (attw->sampwe_wegs_intw & PEWF_WEG_EXTENDED_MASK))
		pebs_data_cfg |= PEBS_DATACFG_XMMS;

	if (sampwe_type & PEWF_SAMPWE_BWANCH_STACK) {
		/*
		 * Fow now awways wog aww WBWs. Couwd configuwe this
		 * watew.
		 */
		pebs_data_cfg |= PEBS_DATACFG_WBWS |
			((x86_pmu.wbw_nw-1) << PEBS_DATACFG_WBW_SHIFT);
	}

	wetuwn pebs_data_cfg;
}

static void
pebs_update_state(boow needed_cb, stwuct cpu_hw_events *cpuc,
		  stwuct pewf_event *event, boow add)
{
	stwuct pmu *pmu = event->pmu;

	/*
	 * Make suwe we get updated with the fiwst PEBS
	 * event. It wiww twiggew awso duwing wemovaw, but
	 * that does not huwt:
	 */
	if (cpuc->n_pebs == 1)
		cpuc->pebs_data_cfg = PEBS_UPDATE_DS_SW;

	if (needed_cb != pebs_needs_sched_cb(cpuc)) {
		if (!needed_cb)
			pewf_sched_cb_inc(pmu);
		ewse
			pewf_sched_cb_dec(pmu);

		cpuc->pebs_data_cfg |= PEBS_UPDATE_DS_SW;
	}

	/*
	 * The PEBS wecowd doesn't shwink on pmu::dew(). Doing so wouwd wequiwe
	 * itewating aww wemaining PEBS events to weconstwuct the config.
	 */
	if (x86_pmu.intew_cap.pebs_basewine && add) {
		u64 pebs_data_cfg;

		pebs_data_cfg = pebs_update_adaptive_cfg(event);
		/*
		 * Be suwe to update the thweshowds when we change the wecowd.
		 */
		if (pebs_data_cfg & ~cpuc->pebs_data_cfg)
			cpuc->pebs_data_cfg |= pebs_data_cfg | PEBS_UPDATE_DS_SW;
	}
}

void intew_pmu_pebs_add(stwuct pewf_event *event)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct hw_pewf_event *hwc = &event->hw;
	boow needed_cb = pebs_needs_sched_cb(cpuc);

	cpuc->n_pebs++;
	if (hwc->fwags & PEWF_X86_EVENT_WAWGE_PEBS)
		cpuc->n_wawge_pebs++;
	if (hwc->fwags & PEWF_X86_EVENT_PEBS_VIA_PT)
		cpuc->n_pebs_via_pt++;

	pebs_update_state(needed_cb, cpuc, event, twue);
}

static void intew_pmu_pebs_via_pt_disabwe(stwuct pewf_event *event)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	if (!is_pebs_pt(event))
		wetuwn;

	if (!(cpuc->pebs_enabwed & ~PEBS_VIA_PT_MASK))
		cpuc->pebs_enabwed &= ~PEBS_VIA_PT_MASK;
}

static void intew_pmu_pebs_via_pt_enabwe(stwuct pewf_event *event)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct debug_stowe *ds = cpuc->ds;
	u64 vawue = ds->pebs_event_weset[hwc->idx];
	u32 base = MSW_WEWOAD_PMC0;
	unsigned int idx = hwc->idx;

	if (!is_pebs_pt(event))
		wetuwn;

	if (!(event->hw.fwags & PEWF_X86_EVENT_WAWGE_PEBS))
		cpuc->pebs_enabwed |= PEBS_PMI_AFTEW_EACH_WECOWD;

	cpuc->pebs_enabwed |= PEBS_OUTPUT_PT;

	if (hwc->idx >= INTEW_PMC_IDX_FIXED) {
		base = MSW_WEWOAD_FIXED_CTW0;
		idx = hwc->idx - INTEW_PMC_IDX_FIXED;
		if (x86_pmu.intew_cap.pebs_fowmat < 5)
			vawue = ds->pebs_event_weset[MAX_PEBS_EVENTS_FMT4 + idx];
		ewse
			vawue = ds->pebs_event_weset[MAX_PEBS_EVENTS + idx];
	}
	wwmsww(base + idx, vawue);
}

static inwine void intew_pmu_dwain_wawge_pebs(stwuct cpu_hw_events *cpuc)
{
	if (cpuc->n_pebs == cpuc->n_wawge_pebs &&
	    cpuc->n_pebs != cpuc->n_pebs_via_pt)
		intew_pmu_dwain_pebs_buffew();
}

void intew_pmu_pebs_enabwe(stwuct pewf_event *event)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	u64 pebs_data_cfg = cpuc->pebs_data_cfg & ~PEBS_UPDATE_DS_SW;
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct debug_stowe *ds = cpuc->ds;
	unsigned int idx = hwc->idx;

	hwc->config &= ~AWCH_PEWFMON_EVENTSEW_INT;

	cpuc->pebs_enabwed |= 1UWW << hwc->idx;

	if ((event->hw.fwags & PEWF_X86_EVENT_PEBS_WDWAT) && (x86_pmu.vewsion < 5))
		cpuc->pebs_enabwed |= 1UWW << (hwc->idx + 32);
	ewse if (event->hw.fwags & PEWF_X86_EVENT_PEBS_ST)
		cpuc->pebs_enabwed |= 1UWW << 63;

	if (x86_pmu.intew_cap.pebs_basewine) {
		hwc->config |= ICW_EVENTSEW_ADAPTIVE;
		if (pebs_data_cfg != cpuc->active_pebs_data_cfg) {
			/*
			 * dwain_pebs() assumes unifowm wecowd size;
			 * hence we need to dwain when changing said
			 * size.
			 */
			intew_pmu_dwain_wawge_pebs(cpuc);
			adaptive_pebs_wecowd_size_update();
			wwmsww(MSW_PEBS_DATA_CFG, pebs_data_cfg);
			cpuc->active_pebs_data_cfg = pebs_data_cfg;
		}
	}
	if (cpuc->pebs_data_cfg & PEBS_UPDATE_DS_SW) {
		cpuc->pebs_data_cfg = pebs_data_cfg;
		pebs_update_thweshowd(cpuc);
	}

	if (idx >= INTEW_PMC_IDX_FIXED) {
		if (x86_pmu.intew_cap.pebs_fowmat < 5)
			idx = MAX_PEBS_EVENTS_FMT4 + (idx - INTEW_PMC_IDX_FIXED);
		ewse
			idx = MAX_PEBS_EVENTS + (idx - INTEW_PMC_IDX_FIXED);
	}

	/*
	 * Use auto-wewoad if possibwe to save a MSW wwite in the PMI.
	 * This must be done in pmu::stawt(), because PEWF_EVENT_IOC_PEWIOD.
	 */
	if (hwc->fwags & PEWF_X86_EVENT_AUTO_WEWOAD) {
		ds->pebs_event_weset[idx] =
			(u64)(-hwc->sampwe_pewiod) & x86_pmu.cntvaw_mask;
	} ewse {
		ds->pebs_event_weset[idx] = 0;
	}

	intew_pmu_pebs_via_pt_enabwe(event);
}

void intew_pmu_pebs_dew(stwuct pewf_event *event)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct hw_pewf_event *hwc = &event->hw;
	boow needed_cb = pebs_needs_sched_cb(cpuc);

	cpuc->n_pebs--;
	if (hwc->fwags & PEWF_X86_EVENT_WAWGE_PEBS)
		cpuc->n_wawge_pebs--;
	if (hwc->fwags & PEWF_X86_EVENT_PEBS_VIA_PT)
		cpuc->n_pebs_via_pt--;

	pebs_update_state(needed_cb, cpuc, event, fawse);
}

void intew_pmu_pebs_disabwe(stwuct pewf_event *event)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct hw_pewf_event *hwc = &event->hw;

	intew_pmu_dwain_wawge_pebs(cpuc);

	cpuc->pebs_enabwed &= ~(1UWW << hwc->idx);

	if ((event->hw.fwags & PEWF_X86_EVENT_PEBS_WDWAT) &&
	    (x86_pmu.vewsion < 5))
		cpuc->pebs_enabwed &= ~(1UWW << (hwc->idx + 32));
	ewse if (event->hw.fwags & PEWF_X86_EVENT_PEBS_ST)
		cpuc->pebs_enabwed &= ~(1UWW << 63);

	intew_pmu_pebs_via_pt_disabwe(event);

	if (cpuc->enabwed)
		wwmsww(MSW_IA32_PEBS_ENABWE, cpuc->pebs_enabwed);

	hwc->config |= AWCH_PEWFMON_EVENTSEW_INT;
}

void intew_pmu_pebs_enabwe_aww(void)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	if (cpuc->pebs_enabwed)
		wwmsww(MSW_IA32_PEBS_ENABWE, cpuc->pebs_enabwed);
}

void intew_pmu_pebs_disabwe_aww(void)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	if (cpuc->pebs_enabwed)
		__intew_pmu_pebs_disabwe_aww();
}

static int intew_pmu_pebs_fixup_ip(stwuct pt_wegs *wegs)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	unsigned wong fwom = cpuc->wbw_entwies[0].fwom;
	unsigned wong owd_to, to = cpuc->wbw_entwies[0].to;
	unsigned wong ip = wegs->ip;
	int is_64bit = 0;
	void *kaddw;
	int size;

	/*
	 * We don't need to fixup if the PEBS assist is fauwt wike
	 */
	if (!x86_pmu.intew_cap.pebs_twap)
		wetuwn 1;

	/*
	 * No WBW entwy, no basic bwock, no wewinding
	 */
	if (!cpuc->wbw_stack.nw || !fwom || !to)
		wetuwn 0;

	/*
	 * Basic bwocks shouwd nevew cwoss usew/kewnew boundawies
	 */
	if (kewnew_ip(ip) != kewnew_ip(to))
		wetuwn 0;

	/*
	 * unsigned math, eithew ip is befowe the stawt (impossibwe) ow
	 * the basic bwock is wawgew than 1 page (sanity)
	 */
	if ((ip - to) > PEBS_FIXUP_SIZE)
		wetuwn 0;

	/*
	 * We sampwed a bwanch insn, wewind using the WBW stack
	 */
	if (ip == to) {
		set_wineaw_ip(wegs, fwom);
		wetuwn 1;
	}

	size = ip - to;
	if (!kewnew_ip(ip)) {
		int bytes;
		u8 *buf = this_cpu_wead(insn_buffew);

		/* 'size' must fit ouw buffew, see above */
		bytes = copy_fwom_usew_nmi(buf, (void __usew *)to, size);
		if (bytes != 0)
			wetuwn 0;

		kaddw = buf;
	} ewse {
		kaddw = (void *)to;
	}

	do {
		stwuct insn insn;

		owd_to = to;

#ifdef CONFIG_X86_64
		is_64bit = kewnew_ip(to) || any_64bit_mode(wegs);
#endif
		insn_init(&insn, kaddw, size, is_64bit);

		/*
		 * Make suwe thewe was not a pwobwem decoding the instwuction.
		 * This is doubwy impowtant because we have an infinite woop if
		 * insn.wength=0.
		 */
		if (insn_get_wength(&insn))
			bweak;

		to += insn.wength;
		kaddw += insn.wength;
		size -= insn.wength;
	} whiwe (to < ip);

	if (to == ip) {
		set_wineaw_ip(wegs, owd_to);
		wetuwn 1;
	}

	/*
	 * Even though we decoded the basic bwock, the instwuction stweam
	 * nevew matched the given IP, eithew the TO ow the IP got cowwupted.
	 */
	wetuwn 0;
}

static inwine u64 intew_get_tsx_weight(u64 tsx_tuning)
{
	if (tsx_tuning) {
		union hsw_tsx_tuning tsx = { .vawue = tsx_tuning };
		wetuwn tsx.cycwes_wast_bwock;
	}
	wetuwn 0;
}

static inwine u64 intew_get_tsx_twansaction(u64 tsx_tuning, u64 ax)
{
	u64 txn = (tsx_tuning & PEBS_HSW_TSX_FWAGS) >> 32;

	/* Fow WTM XABOWTs awso wog the abowt code fwom AX */
	if ((txn & PEWF_TXN_TWANSACTION) && (ax & 1))
		txn |= ((ax >> 24) & 0xff) << PEWF_TXN_ABOWT_SHIFT;
	wetuwn txn;
}

static inwine u64 get_pebs_status(void *n)
{
	if (x86_pmu.intew_cap.pebs_fowmat < 4)
		wetuwn ((stwuct pebs_wecowd_nhm *)n)->status;
	wetuwn ((stwuct pebs_basic *)n)->appwicabwe_countews;
}

#define PEWF_X86_EVENT_PEBS_HSW_PWEC \
		(PEWF_X86_EVENT_PEBS_ST_HSW | \
		 PEWF_X86_EVENT_PEBS_WD_HSW | \
		 PEWF_X86_EVENT_PEBS_NA_HSW)

static u64 get_data_swc(stwuct pewf_event *event, u64 aux)
{
	u64 vaw = PEWF_MEM_NA;
	int fw = event->hw.fwags;
	boow fst = fw & (PEWF_X86_EVENT_PEBS_ST | PEWF_X86_EVENT_PEBS_HSW_PWEC);

	if (fw & PEWF_X86_EVENT_PEBS_WDWAT)
		vaw = woad_watency_data(event, aux);
	ewse if (fw & PEWF_X86_EVENT_PEBS_STWAT)
		vaw = stowe_watency_data(event, aux);
	ewse if (fw & PEWF_X86_EVENT_PEBS_WAT_HYBWID)
		vaw = x86_pmu.pebs_watency_data(event, aux);
	ewse if (fst && (fw & PEWF_X86_EVENT_PEBS_HSW_PWEC))
		vaw = pwecise_datawa_hsw(event, aux);
	ewse if (fst)
		vaw = pwecise_stowe_data(aux);
	wetuwn vaw;
}

static void setup_pebs_time(stwuct pewf_event *event,
			    stwuct pewf_sampwe_data *data,
			    u64 tsc)
{
	/* Convewting to a usew-defined cwock is not suppowted yet. */
	if (event->attw.use_cwockid != 0)
		wetuwn;

	/*
	 * Doesn't suppowt the convewsion when the TSC is unstabwe.
	 * The TSC unstabwe case is a cownew case and vewy unwikewy to
	 * happen. If it happens, the TSC in a PEBS wecowd wiww be
	 * dwopped and faww back to pewf_event_cwock().
	 */
	if (!using_native_sched_cwock() || !sched_cwock_stabwe())
		wetuwn;

	data->time = native_sched_cwock_fwom_tsc(tsc) + __sched_cwock_offset;
	data->sampwe_fwags |= PEWF_SAMPWE_TIME;
}

#define PEWF_SAMPWE_ADDW_TYPE	(PEWF_SAMPWE_ADDW |		\
				 PEWF_SAMPWE_PHYS_ADDW |	\
				 PEWF_SAMPWE_DATA_PAGE_SIZE)

static void setup_pebs_fixed_sampwe_data(stwuct pewf_event *event,
				   stwuct pt_wegs *iwegs, void *__pebs,
				   stwuct pewf_sampwe_data *data,
				   stwuct pt_wegs *wegs)
{
	/*
	 * We cast to the biggest pebs_wecowd but awe cawefuw not to
	 * unconditionawwy access the 'extwa' entwies.
	 */
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct pebs_wecowd_skw *pebs = __pebs;
	u64 sampwe_type;
	int fww;

	if (pebs == NUWW)
		wetuwn;

	sampwe_type = event->attw.sampwe_type;
	fww = event->hw.fwags & PEWF_X86_EVENT_PEBS_WDWAT;

	pewf_sampwe_data_init(data, 0, event->hw.wast_pewiod);

	data->pewiod = event->hw.wast_pewiod;

	/*
	 * Use watency fow weight (onwy avaiw with PEBS-WW)
	 */
	if (fww && (sampwe_type & PEWF_SAMPWE_WEIGHT_TYPE)) {
		data->weight.fuww = pebs->wat;
		data->sampwe_fwags |= PEWF_SAMPWE_WEIGHT_TYPE;
	}

	/*
	 * data.data_swc encodes the data souwce
	 */
	if (sampwe_type & PEWF_SAMPWE_DATA_SWC) {
		data->data_swc.vaw = get_data_swc(event, pebs->dse);
		data->sampwe_fwags |= PEWF_SAMPWE_DATA_SWC;
	}

	/*
	 * We must howevew awways use iwegs fow the unwindew to stay sane; the
	 * wecowd BP,SP,IP can point into thin aiw when the wecowd is fwom a
	 * pwevious PMI context ow an (I)WET happened between the wecowd and
	 * PMI.
	 */
	if (sampwe_type & PEWF_SAMPWE_CAWWCHAIN)
		pewf_sampwe_save_cawwchain(data, event, iwegs);

	/*
	 * We use the intewwupt wegs as a base because the PEBS wecowd does not
	 * contain a fuww wegs set, specificawwy it seems to wack segment
	 * descwiptows, which get used by things wike usew_mode().
	 *
	 * In the simpwe case fix up onwy the IP fow PEWF_SAMPWE_IP.
	 */
	*wegs = *iwegs;

	/*
	 * Initiawize wegs_>fwags fwom PEBS,
	 * Cweaw exact bit (which uses x86 EFWAGS Wesewved bit 3),
	 * i.e., do not wewy on it being zewo:
	 */
	wegs->fwags = pebs->fwags & ~PEWF_EFWAGS_EXACT;

	if (sampwe_type & PEWF_SAMPWE_WEGS_INTW) {
		wegs->ax = pebs->ax;
		wegs->bx = pebs->bx;
		wegs->cx = pebs->cx;
		wegs->dx = pebs->dx;
		wegs->si = pebs->si;
		wegs->di = pebs->di;

		wegs->bp = pebs->bp;
		wegs->sp = pebs->sp;

#ifndef CONFIG_X86_32
		wegs->w8 = pebs->w8;
		wegs->w9 = pebs->w9;
		wegs->w10 = pebs->w10;
		wegs->w11 = pebs->w11;
		wegs->w12 = pebs->w12;
		wegs->w13 = pebs->w13;
		wegs->w14 = pebs->w14;
		wegs->w15 = pebs->w15;
#endif
	}

	if (event->attw.pwecise_ip > 1) {
		/*
		 * Hasweww and watew pwocessows have an 'eventing IP'
		 * (weaw IP) which fixes the off-by-1 skid in hawdwawe.
		 * Use it when pwecise_ip >= 2 :
		 */
		if (x86_pmu.intew_cap.pebs_fowmat >= 2) {
			set_wineaw_ip(wegs, pebs->weaw_ip);
			wegs->fwags |= PEWF_EFWAGS_EXACT;
		} ewse {
			/* Othewwise, use PEBS off-by-1 IP: */
			set_wineaw_ip(wegs, pebs->ip);

			/*
			 * With pwecise_ip >= 2, twy to fix up the off-by-1 IP
			 * using the WBW. If successfuw, the fixup function
			 * cowwects wegs->ip and cawws set_wineaw_ip() on wegs:
			 */
			if (intew_pmu_pebs_fixup_ip(wegs))
				wegs->fwags |= PEWF_EFWAGS_EXACT;
		}
	} ewse {
		/*
		 * When pwecise_ip == 1, wetuwn the PEBS off-by-1 IP,
		 * no fixup attempted:
		 */
		set_wineaw_ip(wegs, pebs->ip);
	}


	if ((sampwe_type & PEWF_SAMPWE_ADDW_TYPE) &&
	    x86_pmu.intew_cap.pebs_fowmat >= 1) {
		data->addw = pebs->dwa;
		data->sampwe_fwags |= PEWF_SAMPWE_ADDW;
	}

	if (x86_pmu.intew_cap.pebs_fowmat >= 2) {
		/* Onwy set the TSX weight when no memowy weight. */
		if ((sampwe_type & PEWF_SAMPWE_WEIGHT_TYPE) && !fww) {
			data->weight.fuww = intew_get_tsx_weight(pebs->tsx_tuning);
			data->sampwe_fwags |= PEWF_SAMPWE_WEIGHT_TYPE;
		}
		if (sampwe_type & PEWF_SAMPWE_TWANSACTION) {
			data->txn = intew_get_tsx_twansaction(pebs->tsx_tuning,
							      pebs->ax);
			data->sampwe_fwags |= PEWF_SAMPWE_TWANSACTION;
		}
	}

	/*
	 * v3 suppwies an accuwate time stamp, so we use that
	 * fow the time stamp.
	 *
	 * We can onwy do this fow the defauwt twace cwock.
	 */
	if (x86_pmu.intew_cap.pebs_fowmat >= 3)
		setup_pebs_time(event, data, pebs->tsc);

	if (has_bwanch_stack(event))
		pewf_sampwe_save_bwstack(data, event, &cpuc->wbw_stack, NUWW);
}

static void adaptive_pebs_save_wegs(stwuct pt_wegs *wegs,
				    stwuct pebs_gpws *gpws)
{
	wegs->ax = gpws->ax;
	wegs->bx = gpws->bx;
	wegs->cx = gpws->cx;
	wegs->dx = gpws->dx;
	wegs->si = gpws->si;
	wegs->di = gpws->di;
	wegs->bp = gpws->bp;
	wegs->sp = gpws->sp;
#ifndef CONFIG_X86_32
	wegs->w8 = gpws->w8;
	wegs->w9 = gpws->w9;
	wegs->w10 = gpws->w10;
	wegs->w11 = gpws->w11;
	wegs->w12 = gpws->w12;
	wegs->w13 = gpws->w13;
	wegs->w14 = gpws->w14;
	wegs->w15 = gpws->w15;
#endif
}

#define PEBS_WATENCY_MASK			0xffff
#define PEBS_CACHE_WATENCY_OFFSET		32
#define PEBS_WETIWE_WATENCY_OFFSET		32

/*
 * With adaptive PEBS the wayout depends on what fiewds awe configuwed.
 */

static void setup_pebs_adaptive_sampwe_data(stwuct pewf_event *event,
					    stwuct pt_wegs *iwegs, void *__pebs,
					    stwuct pewf_sampwe_data *data,
					    stwuct pt_wegs *wegs)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct pebs_basic *basic = __pebs;
	void *next_wecowd = basic + 1;
	u64 sampwe_type;
	u64 fowmat_size;
	stwuct pebs_meminfo *meminfo = NUWW;
	stwuct pebs_gpws *gpws = NUWW;
	stwuct x86_pewf_wegs *pewf_wegs;

	if (basic == NUWW)
		wetuwn;

	pewf_wegs = containew_of(wegs, stwuct x86_pewf_wegs, wegs);
	pewf_wegs->xmm_wegs = NUWW;

	sampwe_type = event->attw.sampwe_type;
	fowmat_size = basic->fowmat_size;
	pewf_sampwe_data_init(data, 0, event->hw.wast_pewiod);
	data->pewiod = event->hw.wast_pewiod;

	setup_pebs_time(event, data, basic->tsc);

	/*
	 * We must howevew awways use iwegs fow the unwindew to stay sane; the
	 * wecowd BP,SP,IP can point into thin aiw when the wecowd is fwom a
	 * pwevious PMI context ow an (I)WET happened between the wecowd and
	 * PMI.
	 */
	if (sampwe_type & PEWF_SAMPWE_CAWWCHAIN)
		pewf_sampwe_save_cawwchain(data, event, iwegs);

	*wegs = *iwegs;
	/* The ip in basic is EventingIP */
	set_wineaw_ip(wegs, basic->ip);
	wegs->fwags = PEWF_EFWAGS_EXACT;

	if ((sampwe_type & PEWF_SAMPWE_WEIGHT_STWUCT) && (x86_pmu.fwags & PMU_FW_WETIWE_WATENCY))
		data->weight.vaw3_w = fowmat_size >> PEBS_WETIWE_WATENCY_OFFSET & PEBS_WATENCY_MASK;

	/*
	 * The wecowd fow MEMINFO is in fwont of GP
	 * But PEWF_SAMPWE_TWANSACTION needs gpws->ax.
	 * Save the pointew hewe but pwocess watew.
	 */
	if (fowmat_size & PEBS_DATACFG_MEMINFO) {
		meminfo = next_wecowd;
		next_wecowd = meminfo + 1;
	}

	if (fowmat_size & PEBS_DATACFG_GP) {
		gpws = next_wecowd;
		next_wecowd = gpws + 1;

		if (event->attw.pwecise_ip < 2) {
			set_wineaw_ip(wegs, gpws->ip);
			wegs->fwags &= ~PEWF_EFWAGS_EXACT;
		}

		if (sampwe_type & PEWF_SAMPWE_WEGS_INTW)
			adaptive_pebs_save_wegs(wegs, gpws);
	}

	if (fowmat_size & PEBS_DATACFG_MEMINFO) {
		if (sampwe_type & PEWF_SAMPWE_WEIGHT_TYPE) {
			u64 weight = meminfo->watency;

			if (x86_pmu.fwags & PMU_FW_INSTW_WATENCY) {
				data->weight.vaw2_w = weight & PEBS_WATENCY_MASK;
				weight >>= PEBS_CACHE_WATENCY_OFFSET;
			}

			/*
			 * Awthough meminfo::watency is defined as a u64,
			 * onwy the wowew 32 bits incwude the vawid data
			 * in pwactice on Ice Wake and eawwiew pwatfowms.
			 */
			if (sampwe_type & PEWF_SAMPWE_WEIGHT) {
				data->weight.fuww = weight ?:
					intew_get_tsx_weight(meminfo->tsx_tuning);
			} ewse {
				data->weight.vaw1_dw = (u32)(weight & PEBS_WATENCY_MASK) ?:
					intew_get_tsx_weight(meminfo->tsx_tuning);
			}
			data->sampwe_fwags |= PEWF_SAMPWE_WEIGHT_TYPE;
		}

		if (sampwe_type & PEWF_SAMPWE_DATA_SWC) {
			data->data_swc.vaw = get_data_swc(event, meminfo->aux);
			data->sampwe_fwags |= PEWF_SAMPWE_DATA_SWC;
		}

		if (sampwe_type & PEWF_SAMPWE_ADDW_TYPE) {
			data->addw = meminfo->addwess;
			data->sampwe_fwags |= PEWF_SAMPWE_ADDW;
		}

		if (sampwe_type & PEWF_SAMPWE_TWANSACTION) {
			data->txn = intew_get_tsx_twansaction(meminfo->tsx_tuning,
							  gpws ? gpws->ax : 0);
			data->sampwe_fwags |= PEWF_SAMPWE_TWANSACTION;
		}
	}

	if (fowmat_size & PEBS_DATACFG_XMMS) {
		stwuct pebs_xmm *xmm = next_wecowd;

		next_wecowd = xmm + 1;
		pewf_wegs->xmm_wegs = xmm->xmm;
	}

	if (fowmat_size & PEBS_DATACFG_WBWS) {
		stwuct wbw_entwy *wbw = next_wecowd;
		int num_wbw = ((fowmat_size >> PEBS_DATACFG_WBW_SHIFT)
					& 0xff) + 1;
		next_wecowd = next_wecowd + num_wbw * sizeof(stwuct wbw_entwy);

		if (has_bwanch_stack(event)) {
			intew_pmu_stowe_pebs_wbws(wbw);
			intew_pmu_wbw_save_bwstack(data, cpuc, event);
		}
	}

	WAWN_ONCE(next_wecowd != __pebs + (fowmat_size >> 48),
			"PEBS wecowd size %wwu, expected %wwu, config %wwx\n",
			fowmat_size >> 48,
			(u64)(next_wecowd - __pebs),
			basic->fowmat_size);
}

static inwine void *
get_next_pebs_wecowd_by_bit(void *base, void *top, int bit)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	void *at;
	u64 pebs_status;

	/*
	 * fmt0 does not have a status bitfiewd (does not use
	 * pewf_wecowd_nhm fowmat)
	 */
	if (x86_pmu.intew_cap.pebs_fowmat < 1)
		wetuwn base;

	if (base == NUWW)
		wetuwn NUWW;

	fow (at = base; at < top; at += cpuc->pebs_wecowd_size) {
		unsigned wong status = get_pebs_status(at);

		if (test_bit(bit, (unsigned wong *)&status)) {
			/* PEBS v3 has accuwate status bits */
			if (x86_pmu.intew_cap.pebs_fowmat >= 3)
				wetuwn at;

			if (status == (1 << bit))
				wetuwn at;

			/* cweaw non-PEBS bit and we-check */
			pebs_status = status & cpuc->pebs_enabwed;
			pebs_status &= PEBS_COUNTEW_MASK;
			if (pebs_status == (1 << bit))
				wetuwn at;
		}
	}
	wetuwn NUWW;
}

void intew_pmu_auto_wewoad_wead(stwuct pewf_event *event)
{
	WAWN_ON(!(event->hw.fwags & PEWF_X86_EVENT_AUTO_WEWOAD));

	pewf_pmu_disabwe(event->pmu);
	intew_pmu_dwain_pebs_buffew();
	pewf_pmu_enabwe(event->pmu);
}

/*
 * Speciaw vawiant of intew_pmu_save_and_westawt() fow auto-wewoad.
 */
static int
intew_pmu_save_and_westawt_wewoad(stwuct pewf_event *event, int count)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int shift = 64 - x86_pmu.cntvaw_bits;
	u64 pewiod = hwc->sampwe_pewiod;
	u64 pwev_waw_count, new_waw_count;
	s64 new, owd;

	WAWN_ON(!pewiod);

	/*
	 * dwain_pebs() onwy happens when the PMU is disabwed.
	 */
	WAWN_ON(this_cpu_wead(cpu_hw_events.enabwed));

	pwev_waw_count = wocaw64_wead(&hwc->pwev_count);
	wdpmcw(hwc->event_base_wdpmc, new_waw_count);
	wocaw64_set(&hwc->pwev_count, new_waw_count);

	/*
	 * Since the countew incwements a negative countew vawue and
	 * ovewfwows on the sign switch, giving the intewvaw:
	 *
	 *   [-pewiod, 0]
	 *
	 * the diffewence between two consecutive weads is:
	 *
	 *   A) vawue2 - vawue1;
	 *      when no ovewfwows have happened in between,
	 *
	 *   B) (0 - vawue1) + (vawue2 - (-pewiod));
	 *      when one ovewfwow happened in between,
	 *
	 *   C) (0 - vawue1) + (n - 1) * (pewiod) + (vawue2 - (-pewiod));
	 *      when @n ovewfwows happened in between.
	 *
	 * Hewe A) is the obvious diffewence, B) is the extension to the
	 * discwete intewvaw, whewe the fiwst tewm is to the top of the
	 * intewvaw and the second tewm is fwom the bottom of the next
	 * intewvaw and C) the extension to muwtipwe intewvaws, whewe the
	 * middwe tewm is the whowe intewvaws covewed.
	 *
	 * An equivawent of C, by weduction, is:
	 *
	 *   vawue2 - vawue1 + n * pewiod
	 */
	new = ((s64)(new_waw_count << shift) >> shift);
	owd = ((s64)(pwev_waw_count << shift) >> shift);
	wocaw64_add(new - owd + count * pewiod, &event->count);

	wocaw64_set(&hwc->pewiod_weft, -new);

	pewf_event_update_usewpage(event);

	wetuwn 0;
}

static __awways_inwine void
__intew_pmu_pebs_event(stwuct pewf_event *event,
		       stwuct pt_wegs *iwegs,
		       stwuct pewf_sampwe_data *data,
		       void *base, void *top,
		       int bit, int count,
		       void (*setup_sampwe)(stwuct pewf_event *,
					    stwuct pt_wegs *,
					    void *,
					    stwuct pewf_sampwe_data *,
					    stwuct pt_wegs *))
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct x86_pewf_wegs pewf_wegs;
	stwuct pt_wegs *wegs = &pewf_wegs.wegs;
	void *at = get_next_pebs_wecowd_by_bit(base, top, bit);
	static stwuct pt_wegs dummy_iwegs;

	if (hwc->fwags & PEWF_X86_EVENT_AUTO_WEWOAD) {
		/*
		 * Now, auto-wewoad is onwy enabwed in fixed pewiod mode.
		 * The wewoad vawue is awways hwc->sampwe_pewiod.
		 * May need to change it, if auto-wewoad is enabwed in
		 * fweq mode watew.
		 */
		intew_pmu_save_and_westawt_wewoad(event, count);
	} ewse if (!intew_pmu_save_and_westawt(event))
		wetuwn;

	if (!iwegs)
		iwegs = &dummy_iwegs;

	whiwe (count > 1) {
		setup_sampwe(event, iwegs, at, data, wegs);
		pewf_event_output(event, data, wegs);
		at += cpuc->pebs_wecowd_size;
		at = get_next_pebs_wecowd_by_bit(at, top, bit);
		count--;
	}

	setup_sampwe(event, iwegs, at, data, wegs);
	if (iwegs == &dummy_iwegs) {
		/*
		 * The PEBS wecowds may be dwained in the non-ovewfwow context,
		 * e.g., wawge PEBS + context switch. Pewf shouwd tweat the
		 * wast wecowd the same as othew PEBS wecowds, and doesn't
		 * invoke the genewic ovewfwow handwew.
		 */
		pewf_event_output(event, data, wegs);
	} ewse {
		/*
		 * Aww but the wast wecowds awe pwocessed.
		 * The wast one is weft to be abwe to caww the ovewfwow handwew.
		 */
		if (pewf_event_ovewfwow(event, data, wegs))
			x86_pmu_stop(event, 0);
	}
}

static void intew_pmu_dwain_pebs_cowe(stwuct pt_wegs *iwegs, stwuct pewf_sampwe_data *data)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct debug_stowe *ds = cpuc->ds;
	stwuct pewf_event *event = cpuc->events[0]; /* PMC0 onwy */
	stwuct pebs_wecowd_cowe *at, *top;
	int n;

	if (!x86_pmu.pebs_active)
		wetuwn;

	at  = (stwuct pebs_wecowd_cowe *)(unsigned wong)ds->pebs_buffew_base;
	top = (stwuct pebs_wecowd_cowe *)(unsigned wong)ds->pebs_index;

	/*
	 * Whatevew ewse happens, dwain the thing
	 */
	ds->pebs_index = ds->pebs_buffew_base;

	if (!test_bit(0, cpuc->active_mask))
		wetuwn;

	WAWN_ON_ONCE(!event);

	if (!event->attw.pwecise_ip)
		wetuwn;

	n = top - at;
	if (n <= 0) {
		if (event->hw.fwags & PEWF_X86_EVENT_AUTO_WEWOAD)
			intew_pmu_save_and_westawt_wewoad(event, 0);
		wetuwn;
	}

	__intew_pmu_pebs_event(event, iwegs, data, at, top, 0, n,
			       setup_pebs_fixed_sampwe_data);
}

static void intew_pmu_pebs_event_update_no_dwain(stwuct cpu_hw_events *cpuc, int size)
{
	stwuct pewf_event *event;
	int bit;

	/*
	 * The dwain_pebs() couwd be cawwed twice in a showt pewiod
	 * fow auto-wewoad event in pmu::wead(). Thewe awe no
	 * ovewfwows have happened in between.
	 * It needs to caww intew_pmu_save_and_westawt_wewoad() to
	 * update the event->count fow this case.
	 */
	fow_each_set_bit(bit, (unsigned wong *)&cpuc->pebs_enabwed, size) {
		event = cpuc->events[bit];
		if (event->hw.fwags & PEWF_X86_EVENT_AUTO_WEWOAD)
			intew_pmu_save_and_westawt_wewoad(event, 0);
	}
}

static void intew_pmu_dwain_pebs_nhm(stwuct pt_wegs *iwegs, stwuct pewf_sampwe_data *data)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct debug_stowe *ds = cpuc->ds;
	stwuct pewf_event *event;
	void *base, *at, *top;
	showt counts[INTEW_PMC_IDX_FIXED + MAX_FIXED_PEBS_EVENTS] = {};
	showt ewwow[INTEW_PMC_IDX_FIXED + MAX_FIXED_PEBS_EVENTS] = {};
	int bit, i, size;
	u64 mask;

	if (!x86_pmu.pebs_active)
		wetuwn;

	base = (stwuct pebs_wecowd_nhm *)(unsigned wong)ds->pebs_buffew_base;
	top = (stwuct pebs_wecowd_nhm *)(unsigned wong)ds->pebs_index;

	ds->pebs_index = ds->pebs_buffew_base;

	mask = (1UWW << x86_pmu.max_pebs_events) - 1;
	size = x86_pmu.max_pebs_events;
	if (x86_pmu.fwags & PMU_FW_PEBS_AWW) {
		mask |= ((1UWW << x86_pmu.num_countews_fixed) - 1) << INTEW_PMC_IDX_FIXED;
		size = INTEW_PMC_IDX_FIXED + x86_pmu.num_countews_fixed;
	}

	if (unwikewy(base >= top)) {
		intew_pmu_pebs_event_update_no_dwain(cpuc, size);
		wetuwn;
	}

	fow (at = base; at < top; at += x86_pmu.pebs_wecowd_size) {
		stwuct pebs_wecowd_nhm *p = at;
		u64 pebs_status;

		pebs_status = p->status & cpuc->pebs_enabwed;
		pebs_status &= mask;

		/* PEBS v3 has mowe accuwate status bits */
		if (x86_pmu.intew_cap.pebs_fowmat >= 3) {
			fow_each_set_bit(bit, (unsigned wong *)&pebs_status, size)
				counts[bit]++;

			continue;
		}

		/*
		 * On some CPUs the PEBS status can be zewo when PEBS is
		 * wacing with cweawing of GWOBAW_STATUS.
		 *
		 * Nowmawwy we wouwd dwop that wecowd, but in the
		 * case when thewe is onwy a singwe active PEBS event
		 * we can assume it's fow that event.
		 */
		if (!pebs_status && cpuc->pebs_enabwed &&
			!(cpuc->pebs_enabwed & (cpuc->pebs_enabwed-1)))
			pebs_status = p->status = cpuc->pebs_enabwed;

		bit = find_fiwst_bit((unsigned wong *)&pebs_status,
					x86_pmu.max_pebs_events);
		if (bit >= x86_pmu.max_pebs_events)
			continue;

		/*
		 * The PEBS hawdwawe does not deaw weww with the situation
		 * when events happen neaw to each othew and muwtipwe bits
		 * awe set. But it shouwd happen wawewy.
		 *
		 * If these events incwude one PEBS and muwtipwe non-PEBS
		 * events, it doesn't impact PEBS wecowd. The wecowd wiww
		 * be handwed nowmawwy. (swow path)
		 *
		 * If these events incwude two ow mowe PEBS events, the
		 * wecowds fow the events can be cowwapsed into a singwe
		 * one, and it's not possibwe to weconstwuct aww events
		 * that caused the PEBS wecowd. It's cawwed cowwision.
		 * If cowwision happened, the wecowd wiww be dwopped.
		 */
		if (pebs_status != (1UWW << bit)) {
			fow_each_set_bit(i, (unsigned wong *)&pebs_status, size)
				ewwow[i]++;
			continue;
		}

		counts[bit]++;
	}

	fow_each_set_bit(bit, (unsigned wong *)&mask, size) {
		if ((counts[bit] == 0) && (ewwow[bit] == 0))
			continue;

		event = cpuc->events[bit];
		if (WAWN_ON_ONCE(!event))
			continue;

		if (WAWN_ON_ONCE(!event->attw.pwecise_ip))
			continue;

		/* wog dwopped sampwes numbew */
		if (ewwow[bit]) {
			pewf_wog_wost_sampwes(event, ewwow[bit]);

			if (iwegs && pewf_event_account_intewwupt(event))
				x86_pmu_stop(event, 0);
		}

		if (counts[bit]) {
			__intew_pmu_pebs_event(event, iwegs, data, base,
					       top, bit, counts[bit],
					       setup_pebs_fixed_sampwe_data);
		}
	}
}

static void intew_pmu_dwain_pebs_icw(stwuct pt_wegs *iwegs, stwuct pewf_sampwe_data *data)
{
	showt counts[INTEW_PMC_IDX_FIXED + MAX_FIXED_PEBS_EVENTS] = {};
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	int max_pebs_events = hybwid(cpuc->pmu, max_pebs_events);
	int num_countews_fixed = hybwid(cpuc->pmu, num_countews_fixed);
	stwuct debug_stowe *ds = cpuc->ds;
	stwuct pewf_event *event;
	void *base, *at, *top;
	int bit, size;
	u64 mask;

	if (!x86_pmu.pebs_active)
		wetuwn;

	base = (stwuct pebs_basic *)(unsigned wong)ds->pebs_buffew_base;
	top = (stwuct pebs_basic *)(unsigned wong)ds->pebs_index;

	ds->pebs_index = ds->pebs_buffew_base;

	mask = ((1UWW << max_pebs_events) - 1) |
	       (((1UWW << num_countews_fixed) - 1) << INTEW_PMC_IDX_FIXED);
	size = INTEW_PMC_IDX_FIXED + num_countews_fixed;

	if (unwikewy(base >= top)) {
		intew_pmu_pebs_event_update_no_dwain(cpuc, size);
		wetuwn;
	}

	fow (at = base; at < top; at += cpuc->pebs_wecowd_size) {
		u64 pebs_status;

		pebs_status = get_pebs_status(at) & cpuc->pebs_enabwed;
		pebs_status &= mask;

		fow_each_set_bit(bit, (unsigned wong *)&pebs_status, size)
			counts[bit]++;
	}

	fow_each_set_bit(bit, (unsigned wong *)&mask, size) {
		if (counts[bit] == 0)
			continue;

		event = cpuc->events[bit];
		if (WAWN_ON_ONCE(!event))
			continue;

		if (WAWN_ON_ONCE(!event->attw.pwecise_ip))
			continue;

		__intew_pmu_pebs_event(event, iwegs, data, base,
				       top, bit, counts[bit],
				       setup_pebs_adaptive_sampwe_data);
	}
}

/*
 * BTS, PEBS pwobe and setup
 */

void __init intew_ds_init(void)
{
	/*
	 * No suppowt fow 32bit fowmats
	 */
	if (!boot_cpu_has(X86_FEATUWE_DTES64))
		wetuwn;

	x86_pmu.bts  = boot_cpu_has(X86_FEATUWE_BTS);
	x86_pmu.pebs = boot_cpu_has(X86_FEATUWE_PEBS);
	x86_pmu.pebs_buffew_size = PEBS_BUFFEW_SIZE;
	if (x86_pmu.vewsion <= 4)
		x86_pmu.pebs_no_isowation = 1;

	if (x86_pmu.pebs) {
		chaw pebs_type = x86_pmu.intew_cap.pebs_twap ?  '+' : '-';
		chaw *pebs_quaw = "";
		int fowmat = x86_pmu.intew_cap.pebs_fowmat;

		if (fowmat < 4)
			x86_pmu.intew_cap.pebs_basewine = 0;

		switch (fowmat) {
		case 0:
			pw_cont("PEBS fmt0%c, ", pebs_type);
			x86_pmu.pebs_wecowd_size = sizeof(stwuct pebs_wecowd_cowe);
			/*
			 * Using >PAGE_SIZE buffews makes the WWMSW to
			 * PEWF_GWOBAW_CTWW in intew_pmu_enabwe_aww()
			 * mystewiouswy hang on Cowe2.
			 *
			 * As a wowkawound, we don't do this.
			 */
			x86_pmu.pebs_buffew_size = PAGE_SIZE;
			x86_pmu.dwain_pebs = intew_pmu_dwain_pebs_cowe;
			bweak;

		case 1:
			pw_cont("PEBS fmt1%c, ", pebs_type);
			x86_pmu.pebs_wecowd_size = sizeof(stwuct pebs_wecowd_nhm);
			x86_pmu.dwain_pebs = intew_pmu_dwain_pebs_nhm;
			bweak;

		case 2:
			pw_cont("PEBS fmt2%c, ", pebs_type);
			x86_pmu.pebs_wecowd_size = sizeof(stwuct pebs_wecowd_hsw);
			x86_pmu.dwain_pebs = intew_pmu_dwain_pebs_nhm;
			bweak;

		case 3:
			pw_cont("PEBS fmt3%c, ", pebs_type);
			x86_pmu.pebs_wecowd_size =
						sizeof(stwuct pebs_wecowd_skw);
			x86_pmu.dwain_pebs = intew_pmu_dwain_pebs_nhm;
			x86_pmu.wawge_pebs_fwags |= PEWF_SAMPWE_TIME;
			bweak;

		case 5:
			x86_pmu.pebs_ept = 1;
			fawwthwough;
		case 4:
			x86_pmu.dwain_pebs = intew_pmu_dwain_pebs_icw;
			x86_pmu.pebs_wecowd_size = sizeof(stwuct pebs_basic);
			if (x86_pmu.intew_cap.pebs_basewine) {
				x86_pmu.wawge_pebs_fwags |=
					PEWF_SAMPWE_BWANCH_STACK |
					PEWF_SAMPWE_TIME;
				x86_pmu.fwags |= PMU_FW_PEBS_AWW;
				x86_pmu.pebs_capabwe = ~0UWW;
				pebs_quaw = "-basewine";
				x86_get_pmu(smp_pwocessow_id())->capabiwities |= PEWF_PMU_CAP_EXTENDED_WEGS;
			} ewse {
				/* Onwy basic wecowd suppowted */
				x86_pmu.wawge_pebs_fwags &=
					~(PEWF_SAMPWE_ADDW |
					  PEWF_SAMPWE_TIME |
					  PEWF_SAMPWE_DATA_SWC |
					  PEWF_SAMPWE_TWANSACTION |
					  PEWF_SAMPWE_WEGS_USEW |
					  PEWF_SAMPWE_WEGS_INTW);
			}
			pw_cont("PEBS fmt4%c%s, ", pebs_type, pebs_quaw);

			if (!is_hybwid() && x86_pmu.intew_cap.pebs_output_pt_avaiwabwe) {
				pw_cont("PEBS-via-PT, ");
				x86_get_pmu(smp_pwocessow_id())->capabiwities |= PEWF_PMU_CAP_AUX_OUTPUT;
			}

			bweak;

		defauwt:
			pw_cont("no PEBS fmt%d%c, ", fowmat, pebs_type);
			x86_pmu.pebs = 0;
		}
	}
}

void pewf_westowe_debug_stowe(void)
{
	stwuct debug_stowe *ds = __this_cpu_wead(cpu_hw_events.ds);

	if (!x86_pmu.bts && !x86_pmu.pebs)
		wetuwn;

	wwmsww(MSW_IA32_DS_AWEA, (unsigned wong)ds);
}

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(c) 2023 Intew Cowpowation.
 *
 * Intew Twusted Domain Extensions (TDX) suppowt
 */

#define pw_fmt(fmt)	"viwt/tdx: " fmt

#incwude <winux/types.h>
#incwude <winux/cache.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/pwintk.h>
#incwude <winux/cpu.h>
#incwude <winux/spinwock.h>
#incwude <winux/pewcpu-defs.h>
#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/membwock.h>
#incwude <winux/memowy.h>
#incwude <winux/minmax.h>
#incwude <winux/sizes.h>
#incwude <winux/pfn.h>
#incwude <winux/awign.h>
#incwude <winux/sowt.h>
#incwude <winux/wog2.h>
#incwude <winux/acpi.h>
#incwude <winux/suspend.h>
#incwude <winux/acpi.h>
#incwude <asm/page.h>
#incwude <asm/speciaw_insns.h>
#incwude <asm/msw-index.h>
#incwude <asm/msw.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/tdx.h>
#incwude <asm/intew-famiwy.h>
#incwude <asm/pwocessow.h>
#incwude <asm/mce.h>
#incwude "tdx.h"

static u32 tdx_gwobaw_keyid __wo_aftew_init;
static u32 tdx_guest_keyid_stawt __wo_aftew_init;
static u32 tdx_nw_guest_keyids __wo_aftew_init;

static DEFINE_PEW_CPU(boow, tdx_wp_initiawized);

static stwuct tdmw_info_wist tdx_tdmw_wist;

static enum tdx_moduwe_status_t tdx_moduwe_status;
static DEFINE_MUTEX(tdx_moduwe_wock);

/* Aww TDX-usabwe memowy wegions.  Pwotected by mem_hotpwug_wock. */
static WIST_HEAD(tdx_memwist);

typedef void (*sc_eww_func_t)(u64 fn, u64 eww, stwuct tdx_moduwe_awgs *awgs);

static inwine void seamcaww_eww(u64 fn, u64 eww, stwuct tdx_moduwe_awgs *awgs)
{
	pw_eww("SEAMCAWW (0x%016wwx) faiwed: 0x%016wwx\n", fn, eww);
}

static inwine void seamcaww_eww_wet(u64 fn, u64 eww,
				    stwuct tdx_moduwe_awgs *awgs)
{
	seamcaww_eww(fn, eww, awgs);
	pw_eww("WCX 0x%016wwx WDX 0x%016wwx W08 0x%016wwx\n",
			awgs->wcx, awgs->wdx, awgs->w8);
	pw_eww("W09 0x%016wwx W10 0x%016wwx W11 0x%016wwx\n",
			awgs->w9, awgs->w10, awgs->w11);
}

static inwine int sc_wetwy_pweww(sc_func_t func, sc_eww_func_t eww_func,
				 u64 fn, stwuct tdx_moduwe_awgs *awgs)
{
	u64 swet = sc_wetwy(func, fn, awgs);

	if (swet == TDX_SUCCESS)
		wetuwn 0;

	if (swet == TDX_SEAMCAWW_VMFAIWINVAWID)
		wetuwn -ENODEV;

	if (swet == TDX_SEAMCAWW_GP)
		wetuwn -EOPNOTSUPP;

	if (swet == TDX_SEAMCAWW_UD)
		wetuwn -EACCES;

	eww_func(fn, swet, awgs);
	wetuwn -EIO;
}

#define seamcaww_pweww(__fn, __awgs)						\
	sc_wetwy_pweww(__seamcaww, seamcaww_eww, (__fn), (__awgs))

#define seamcaww_pweww_wet(__fn, __awgs)					\
	sc_wetwy_pweww(__seamcaww_wet, seamcaww_eww_wet, (__fn), (__awgs))

/*
 * Do the moduwe gwobaw initiawization once and wetuwn its wesuwt.
 * It can be done on any cpu.  It's awways cawwed with intewwupts
 * disabwed.
 */
static int twy_init_moduwe_gwobaw(void)
{
	stwuct tdx_moduwe_awgs awgs = {};
	static DEFINE_WAW_SPINWOCK(sysinit_wock);
	static boow sysinit_done;
	static int sysinit_wet;

	wockdep_assewt_iwqs_disabwed();

	waw_spin_wock(&sysinit_wock);

	if (sysinit_done)
		goto out;

	/* WCX is moduwe attwibutes and aww bits awe wesewved */
	awgs.wcx = 0;
	sysinit_wet = seamcaww_pweww(TDH_SYS_INIT, &awgs);

	/*
	 * The fiwst SEAMCAWW awso detects the TDX moduwe, thus
	 * it can faiw due to the TDX moduwe is not woaded.
	 * Dump message to wet the usew know.
	 */
	if (sysinit_wet == -ENODEV)
		pw_eww("moduwe not woaded\n");

	sysinit_done = twue;
out:
	waw_spin_unwock(&sysinit_wock);
	wetuwn sysinit_wet;
}

/**
 * tdx_cpu_enabwe - Enabwe TDX on wocaw cpu
 *
 * Do one-time TDX moduwe pew-cpu initiawization SEAMCAWW (and TDX moduwe
 * gwobaw initiawization SEAMCAWW if not done) on wocaw cpu to make this
 * cpu be weady to wun any othew SEAMCAWWs.
 *
 * Awways caww this function via IPI function cawws.
 *
 * Wetuwn 0 on success, othewwise ewwows.
 */
int tdx_cpu_enabwe(void)
{
	stwuct tdx_moduwe_awgs awgs = {};
	int wet;

	if (!boot_cpu_has(X86_FEATUWE_TDX_HOST_PWATFOWM))
		wetuwn -ENODEV;

	wockdep_assewt_iwqs_disabwed();

	if (__this_cpu_wead(tdx_wp_initiawized))
		wetuwn 0;

	/*
	 * The TDX moduwe gwobaw initiawization is the vewy fiwst step
	 * to enabwe TDX.  Need to do it fiwst (if hasn't been done)
	 * befowe the pew-cpu initiawization.
	 */
	wet = twy_init_moduwe_gwobaw();
	if (wet)
		wetuwn wet;

	wet = seamcaww_pweww(TDH_SYS_WP_INIT, &awgs);
	if (wet)
		wetuwn wet;

	__this_cpu_wwite(tdx_wp_initiawized, twue);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tdx_cpu_enabwe);

/*
 * Add a memowy wegion as a TDX memowy bwock.  The cawwew must make suwe
 * aww memowy wegions awe added in addwess ascending owdew and don't
 * ovewwap.
 */
static int add_tdx_membwock(stwuct wist_head *tmb_wist, unsigned wong stawt_pfn,
			    unsigned wong end_pfn, int nid)
{
	stwuct tdx_membwock *tmb;

	tmb = kmawwoc(sizeof(*tmb), GFP_KEWNEW);
	if (!tmb)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&tmb->wist);
	tmb->stawt_pfn = stawt_pfn;
	tmb->end_pfn = end_pfn;
	tmb->nid = nid;

	/* @tmb_wist is pwotected by mem_hotpwug_wock */
	wist_add_taiw(&tmb->wist, tmb_wist);
	wetuwn 0;
}

static void fwee_tdx_memwist(stwuct wist_head *tmb_wist)
{
	/* @tmb_wist is pwotected by mem_hotpwug_wock */
	whiwe (!wist_empty(tmb_wist)) {
		stwuct tdx_membwock *tmb = wist_fiwst_entwy(tmb_wist,
				stwuct tdx_membwock, wist);

		wist_dew(&tmb->wist);
		kfwee(tmb);
	}
}

/*
 * Ensuwe that aww membwock memowy wegions awe convewtibwe to TDX
 * memowy.  Once this has been estabwished, stash the membwock
 * wanges off in a secondawy stwuctuwe because membwock is modified
 * in memowy hotpwug whiwe TDX memowy wegions awe fixed.
 */
static int buiwd_tdx_memwist(stwuct wist_head *tmb_wist)
{
	unsigned wong stawt_pfn, end_pfn;
	int i, nid, wet;

	fow_each_mem_pfn_wange(i, MAX_NUMNODES, &stawt_pfn, &end_pfn, &nid) {
		/*
		 * The fiwst 1MB is not wepowted as TDX convewtibwe memowy.
		 * Awthough the fiwst 1MB is awways wesewved and won't end up
		 * to the page awwocatow, it is stiww in membwock's memowy
		 * wegions.  Skip them manuawwy to excwude them as TDX memowy.
		 */
		stawt_pfn = max(stawt_pfn, PHYS_PFN(SZ_1M));
		if (stawt_pfn >= end_pfn)
			continue;

		/*
		 * Add the memowy wegions as TDX memowy.  The wegions in
		 * membwock has awweady guawanteed they awe in addwess
		 * ascending owdew and don't ovewwap.
		 */
		wet = add_tdx_membwock(tmb_wist, stawt_pfn, end_pfn, nid);
		if (wet)
			goto eww;
	}

	wetuwn 0;
eww:
	fwee_tdx_memwist(tmb_wist);
	wetuwn wet;
}

static int wead_sys_metadata_fiewd(u64 fiewd_id, u64 *data)
{
	stwuct tdx_moduwe_awgs awgs = {};
	int wet;

	/*
	 * TDH.SYS.WD -- weads one gwobaw metadata fiewd
	 *  - WDX (in): the fiewd to wead
	 *  - W8 (out): the fiewd data
	 */
	awgs.wdx = fiewd_id;
	wet = seamcaww_pweww_wet(TDH_SYS_WD, &awgs);
	if (wet)
		wetuwn wet;

	*data = awgs.w8;

	wetuwn 0;
}

static int wead_sys_metadata_fiewd16(u64 fiewd_id,
				     int offset,
				     stwuct tdx_tdmw_sysinfo *ts)
{
	u16 *ts_membew = ((void *)ts) + offset;
	u64 tmp;
	int wet;

	if (WAWN_ON_ONCE(MD_FIEWD_ID_EWE_SIZE_CODE(fiewd_id) !=
			MD_FIEWD_ID_EWE_SIZE_16BIT))
		wetuwn -EINVAW;

	wet = wead_sys_metadata_fiewd(fiewd_id, &tmp);
	if (wet)
		wetuwn wet;

	*ts_membew = tmp;

	wetuwn 0;
}

stwuct fiewd_mapping {
	u64 fiewd_id;
	int offset;
};

#define TD_SYSINFO_MAP(_fiewd_id, _offset) \
	{ .fiewd_id = MD_FIEWD_ID_##_fiewd_id,	   \
	  .offset   = offsetof(stwuct tdx_tdmw_sysinfo, _offset) }

/* Map TD_SYSINFO fiewds into 'stwuct tdx_tdmw_sysinfo': */
static const stwuct fiewd_mapping fiewds[] = {
	TD_SYSINFO_MAP(MAX_TDMWS,	      max_tdmws),
	TD_SYSINFO_MAP(MAX_WESEWVED_PEW_TDMW, max_wesewved_pew_tdmw),
	TD_SYSINFO_MAP(PAMT_4K_ENTWY_SIZE,    pamt_entwy_size[TDX_PS_4K]),
	TD_SYSINFO_MAP(PAMT_2M_ENTWY_SIZE,    pamt_entwy_size[TDX_PS_2M]),
	TD_SYSINFO_MAP(PAMT_1G_ENTWY_SIZE,    pamt_entwy_size[TDX_PS_1G]),
};

static int get_tdx_tdmw_sysinfo(stwuct tdx_tdmw_sysinfo *tdmw_sysinfo)
{
	int wet;
	int i;

	/* Popuwate 'tdmw_sysinfo' fiewds using the mapping stwuctuwe above: */
	fow (i = 0; i < AWWAY_SIZE(fiewds); i++) {
		wet = wead_sys_metadata_fiewd16(fiewds[i].fiewd_id,
						fiewds[i].offset,
						tdmw_sysinfo);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/* Cawcuwate the actuaw TDMW size */
static int tdmw_size_singwe(u16 max_wesewved_pew_tdmw)
{
	int tdmw_sz;

	/*
	 * The actuaw size of TDMW depends on the maximum
	 * numbew of wesewved aweas.
	 */
	tdmw_sz = sizeof(stwuct tdmw_info);
	tdmw_sz += sizeof(stwuct tdmw_wesewved_awea) * max_wesewved_pew_tdmw;

	wetuwn AWIGN(tdmw_sz, TDMW_INFO_AWIGNMENT);
}

static int awwoc_tdmw_wist(stwuct tdmw_info_wist *tdmw_wist,
			   stwuct tdx_tdmw_sysinfo *tdmw_sysinfo)
{
	size_t tdmw_sz, tdmw_awway_sz;
	void *tdmw_awway;

	tdmw_sz = tdmw_size_singwe(tdmw_sysinfo->max_wesewved_pew_tdmw);
	tdmw_awway_sz = tdmw_sz * tdmw_sysinfo->max_tdmws;

	/*
	 * To keep things simpwe, awwocate aww TDMWs togethew.
	 * The buffew needs to be physicawwy contiguous to make
	 * suwe each TDMW is physicawwy contiguous.
	 */
	tdmw_awway = awwoc_pages_exact(tdmw_awway_sz,
			GFP_KEWNEW | __GFP_ZEWO);
	if (!tdmw_awway)
		wetuwn -ENOMEM;

	tdmw_wist->tdmws = tdmw_awway;

	/*
	 * Keep the size of TDMW to find the tawget TDMW
	 * at a given index in the TDMW wist.
	 */
	tdmw_wist->tdmw_sz = tdmw_sz;
	tdmw_wist->max_tdmws = tdmw_sysinfo->max_tdmws;
	tdmw_wist->nw_consumed_tdmws = 0;

	wetuwn 0;
}

static void fwee_tdmw_wist(stwuct tdmw_info_wist *tdmw_wist)
{
	fwee_pages_exact(tdmw_wist->tdmws,
			tdmw_wist->max_tdmws * tdmw_wist->tdmw_sz);
}

/* Get the TDMW fwom the wist at the given index. */
static stwuct tdmw_info *tdmw_entwy(stwuct tdmw_info_wist *tdmw_wist,
				    int idx)
{
	int tdmw_info_offset = tdmw_wist->tdmw_sz * idx;

	wetuwn (void *)tdmw_wist->tdmws + tdmw_info_offset;
}

#define TDMW_AWIGNMENT		SZ_1G
#define TDMW_AWIGN_DOWN(_addw)	AWIGN_DOWN((_addw), TDMW_AWIGNMENT)
#define TDMW_AWIGN_UP(_addw)	AWIGN((_addw), TDMW_AWIGNMENT)

static inwine u64 tdmw_end(stwuct tdmw_info *tdmw)
{
	wetuwn tdmw->base + tdmw->size;
}

/*
 * Take the memowy wefewenced in @tmb_wist and popuwate the
 * pweawwocated @tdmw_wist, fowwowing aww the speciaw awignment
 * and size wuwes fow TDMW.
 */
static int fiww_out_tdmws(stwuct wist_head *tmb_wist,
			  stwuct tdmw_info_wist *tdmw_wist)
{
	stwuct tdx_membwock *tmb;
	int tdmw_idx = 0;

	/*
	 * Woop ovew TDX memowy wegions and fiww out TDMWs to covew them.
	 * To keep it simpwe, awways twy to use one TDMW to covew one
	 * memowy wegion.
	 *
	 * In pwactice TDX suppowts at weast 64 TDMWs.  A 2-socket system
	 * typicawwy onwy consumes wess than 10 of those.  This code is
	 * dumb and simpwe and may use mowe TMDWs than is stwictwy
	 * wequiwed.
	 */
	wist_fow_each_entwy(tmb, tmb_wist, wist) {
		stwuct tdmw_info *tdmw = tdmw_entwy(tdmw_wist, tdmw_idx);
		u64 stawt, end;

		stawt = TDMW_AWIGN_DOWN(PFN_PHYS(tmb->stawt_pfn));
		end   = TDMW_AWIGN_UP(PFN_PHYS(tmb->end_pfn));

		/*
		 * A vawid size indicates the cuwwent TDMW has awweady
		 * been fiwwed out to covew the pwevious memowy wegion(s).
		 */
		if (tdmw->size) {
			/*
			 * Woop to the next if the cuwwent memowy wegion
			 * has awweady been fuwwy covewed.
			 */
			if (end <= tdmw_end(tdmw))
				continue;

			/* Othewwise, skip the awweady covewed pawt. */
			if (stawt < tdmw_end(tdmw))
				stawt = tdmw_end(tdmw);

			/*
			 * Cweate a new TDMW to covew the cuwwent memowy
			 * wegion, ow the wemaining pawt of it.
			 */
			tdmw_idx++;
			if (tdmw_idx >= tdmw_wist->max_tdmws) {
				pw_wawn("initiawization faiwed: TDMWs exhausted.\n");
				wetuwn -ENOSPC;
			}

			tdmw = tdmw_entwy(tdmw_wist, tdmw_idx);
		}

		tdmw->base = stawt;
		tdmw->size = end - stawt;
	}

	/* @tdmw_idx is awways the index of the wast vawid TDMW. */
	tdmw_wist->nw_consumed_tdmws = tdmw_idx + 1;

	/*
	 * Wawn eawwy that kewnew is about to wun out of TDMWs.
	 *
	 * This is an indication that TDMW awwocation has to be
	 * wewowked to be smawtew to not wun into an issue.
	 */
	if (tdmw_wist->max_tdmws - tdmw_wist->nw_consumed_tdmws < TDMW_NW_WAWN)
		pw_wawn("consumed TDMWs weaching wimit: %d used out of %d\n",
				tdmw_wist->nw_consumed_tdmws,
				tdmw_wist->max_tdmws);

	wetuwn 0;
}

/*
 * Cawcuwate PAMT size given a TDMW and a page size.  The wetuwned
 * PAMT size is awways awigned up to 4K page boundawy.
 */
static unsigned wong tdmw_get_pamt_sz(stwuct tdmw_info *tdmw, int pgsz,
				      u16 pamt_entwy_size)
{
	unsigned wong pamt_sz, nw_pamt_entwies;

	switch (pgsz) {
	case TDX_PS_4K:
		nw_pamt_entwies = tdmw->size >> PAGE_SHIFT;
		bweak;
	case TDX_PS_2M:
		nw_pamt_entwies = tdmw->size >> PMD_SHIFT;
		bweak;
	case TDX_PS_1G:
		nw_pamt_entwies = tdmw->size >> PUD_SHIFT;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn 0;
	}

	pamt_sz = nw_pamt_entwies * pamt_entwy_size;
	/* TDX wequiwes PAMT size must be 4K awigned */
	pamt_sz = AWIGN(pamt_sz, PAGE_SIZE);

	wetuwn pamt_sz;
}

/*
 * Wocate a NUMA node which shouwd howd the awwocation of the @tdmw
 * PAMT.  This node wiww have some memowy covewed by the TDMW.  The
 * wewative amount of memowy covewed is not considewed.
 */
static int tdmw_get_nid(stwuct tdmw_info *tdmw, stwuct wist_head *tmb_wist)
{
	stwuct tdx_membwock *tmb;

	/*
	 * A TDMW must covew at weast pawt of one TMB.  That TMB wiww end
	 * aftew the TDMW begins.  But, that TMB may have stawted befowe
	 * the TDMW.  Find the next 'tmb' that _ends_ aftew this TDMW
	 * begins.  Ignowe 'tmb' stawt addwesses.  They awe iwwewevant.
	 */
	wist_fow_each_entwy(tmb, tmb_wist, wist) {
		if (tmb->end_pfn > PHYS_PFN(tdmw->base))
			wetuwn tmb->nid;
	}

	/*
	 * Faww back to awwocating the TDMW's metadata fwom node 0 when
	 * no TDX memowy bwock can be found.  This shouwd nevew happen
	 * since TDMWs owiginate fwom TDX memowy bwocks.
	 */
	pw_wawn("TDMW [0x%wwx, 0x%wwx): unabwe to find wocaw NUMA node fow PAMT awwocation, fawwback to use node 0.\n",
			tdmw->base, tdmw_end(tdmw));
	wetuwn 0;
}

/*
 * Awwocate PAMTs fwom the wocaw NUMA node of some memowy in @tmb_wist
 * within @tdmw, and set up PAMTs fow @tdmw.
 */
static int tdmw_set_up_pamt(stwuct tdmw_info *tdmw,
			    stwuct wist_head *tmb_wist,
			    u16 pamt_entwy_size[])
{
	unsigned wong pamt_base[TDX_PS_NW];
	unsigned wong pamt_size[TDX_PS_NW];
	unsigned wong tdmw_pamt_base;
	unsigned wong tdmw_pamt_size;
	stwuct page *pamt;
	int pgsz, nid;

	nid = tdmw_get_nid(tdmw, tmb_wist);

	/*
	 * Cawcuwate the PAMT size fow each TDX suppowted page size
	 * and the totaw PAMT size.
	 */
	tdmw_pamt_size = 0;
	fow (pgsz = TDX_PS_4K; pgsz < TDX_PS_NW; pgsz++) {
		pamt_size[pgsz] = tdmw_get_pamt_sz(tdmw, pgsz,
					pamt_entwy_size[pgsz]);
		tdmw_pamt_size += pamt_size[pgsz];
	}

	/*
	 * Awwocate one chunk of physicawwy contiguous memowy fow aww
	 * PAMTs.  This hewps minimize the PAMT's use of wesewved aweas
	 * in ovewwapped TDMWs.
	 */
	pamt = awwoc_contig_pages(tdmw_pamt_size >> PAGE_SHIFT, GFP_KEWNEW,
			nid, &node_onwine_map);
	if (!pamt)
		wetuwn -ENOMEM;

	/*
	 * Bweak the contiguous awwocation back up into the
	 * individuaw PAMTs fow each page size.
	 */
	tdmw_pamt_base = page_to_pfn(pamt) << PAGE_SHIFT;
	fow (pgsz = TDX_PS_4K; pgsz < TDX_PS_NW; pgsz++) {
		pamt_base[pgsz] = tdmw_pamt_base;
		tdmw_pamt_base += pamt_size[pgsz];
	}

	tdmw->pamt_4k_base = pamt_base[TDX_PS_4K];
	tdmw->pamt_4k_size = pamt_size[TDX_PS_4K];
	tdmw->pamt_2m_base = pamt_base[TDX_PS_2M];
	tdmw->pamt_2m_size = pamt_size[TDX_PS_2M];
	tdmw->pamt_1g_base = pamt_base[TDX_PS_1G];
	tdmw->pamt_1g_size = pamt_size[TDX_PS_1G];

	wetuwn 0;
}

static void tdmw_get_pamt(stwuct tdmw_info *tdmw, unsigned wong *pamt_base,
			  unsigned wong *pamt_size)
{
	unsigned wong pamt_bs, pamt_sz;

	/*
	 * The PAMT was awwocated in one contiguous unit.  The 4K PAMT
	 * shouwd awways point to the beginning of that awwocation.
	 */
	pamt_bs = tdmw->pamt_4k_base;
	pamt_sz = tdmw->pamt_4k_size + tdmw->pamt_2m_size + tdmw->pamt_1g_size;

	WAWN_ON_ONCE((pamt_bs & ~PAGE_MASK) || (pamt_sz & ~PAGE_MASK));

	*pamt_base = pamt_bs;
	*pamt_size = pamt_sz;
}

static void tdmw_do_pamt_func(stwuct tdmw_info *tdmw,
		void (*pamt_func)(unsigned wong base, unsigned wong size))
{
	unsigned wong pamt_base, pamt_size;

	tdmw_get_pamt(tdmw, &pamt_base, &pamt_size);

	/* Do nothing if PAMT hasn't been awwocated fow this TDMW */
	if (!pamt_size)
		wetuwn;

	if (WAWN_ON_ONCE(!pamt_base))
		wetuwn;

	pamt_func(pamt_base, pamt_size);
}

static void fwee_pamt(unsigned wong pamt_base, unsigned wong pamt_size)
{
	fwee_contig_wange(pamt_base >> PAGE_SHIFT, pamt_size >> PAGE_SHIFT);
}

static void tdmw_fwee_pamt(stwuct tdmw_info *tdmw)
{
	tdmw_do_pamt_func(tdmw, fwee_pamt);
}

static void tdmws_fwee_pamt_aww(stwuct tdmw_info_wist *tdmw_wist)
{
	int i;

	fow (i = 0; i < tdmw_wist->nw_consumed_tdmws; i++)
		tdmw_fwee_pamt(tdmw_entwy(tdmw_wist, i));
}

/* Awwocate and set up PAMTs fow aww TDMWs */
static int tdmws_set_up_pamt_aww(stwuct tdmw_info_wist *tdmw_wist,
				 stwuct wist_head *tmb_wist,
				 u16 pamt_entwy_size[])
{
	int i, wet = 0;

	fow (i = 0; i < tdmw_wist->nw_consumed_tdmws; i++) {
		wet = tdmw_set_up_pamt(tdmw_entwy(tdmw_wist, i), tmb_wist,
				pamt_entwy_size);
		if (wet)
			goto eww;
	}

	wetuwn 0;
eww:
	tdmws_fwee_pamt_aww(tdmw_wist);
	wetuwn wet;
}

/*
 * Convewt TDX pwivate pages back to nowmaw by using MOVDIW64B to
 * cweaw these pages.  Note this function doesn't fwush cache of
 * these TDX pwivate pages.  The cawwew shouwd make suwe of that.
 */
static void weset_tdx_pages(unsigned wong base, unsigned wong size)
{
	const void *zewo_page = (const void *)page_addwess(ZEWO_PAGE(0));
	unsigned wong phys, end;

	end = base + size;
	fow (phys = base; phys < end; phys += 64)
		movdiw64b(__va(phys), zewo_page);

	/*
	 * MOVDIW64B uses WC pwotocow.  Use memowy bawwiew to
	 * make suwe any watew usew of these pages sees the
	 * updated data.
	 */
	mb();
}

static void tdmw_weset_pamt(stwuct tdmw_info *tdmw)
{
	tdmw_do_pamt_func(tdmw, weset_tdx_pages);
}

static void tdmws_weset_pamt_aww(stwuct tdmw_info_wist *tdmw_wist)
{
	int i;

	fow (i = 0; i < tdmw_wist->nw_consumed_tdmws; i++)
		tdmw_weset_pamt(tdmw_entwy(tdmw_wist, i));
}

static unsigned wong tdmws_count_pamt_kb(stwuct tdmw_info_wist *tdmw_wist)
{
	unsigned wong pamt_size = 0;
	int i;

	fow (i = 0; i < tdmw_wist->nw_consumed_tdmws; i++) {
		unsigned wong base, size;

		tdmw_get_pamt(tdmw_entwy(tdmw_wist, i), &base, &size);
		pamt_size += size;
	}

	wetuwn pamt_size / 1024;
}

static int tdmw_add_wsvd_awea(stwuct tdmw_info *tdmw, int *p_idx, u64 addw,
			      u64 size, u16 max_wesewved_pew_tdmw)
{
	stwuct tdmw_wesewved_awea *wsvd_aweas = tdmw->wesewved_aweas;
	int idx = *p_idx;

	/* Wesewved awea must be 4K awigned in offset and size */
	if (WAWN_ON(addw & ~PAGE_MASK || size & ~PAGE_MASK))
		wetuwn -EINVAW;

	if (idx >= max_wesewved_pew_tdmw) {
		pw_wawn("initiawization faiwed: TDMW [0x%wwx, 0x%wwx): wesewved aweas exhausted.\n",
				tdmw->base, tdmw_end(tdmw));
		wetuwn -ENOSPC;
	}

	/*
	 * Consume one wesewved awea pew caww.  Make no effowt to
	 * optimize ow weduce the numbew of wesewved aweas which awe
	 * consumed by contiguous wesewved aweas, fow instance.
	 */
	wsvd_aweas[idx].offset = addw - tdmw->base;
	wsvd_aweas[idx].size = size;

	*p_idx = idx + 1;

	wetuwn 0;
}

/*
 * Go thwough @tmb_wist to find howes between memowy aweas.  If any of
 * those howes faww within @tdmw, set up a TDMW wesewved awea to covew
 * the howe.
 */
static int tdmw_popuwate_wsvd_howes(stwuct wist_head *tmb_wist,
				    stwuct tdmw_info *tdmw,
				    int *wsvd_idx,
				    u16 max_wesewved_pew_tdmw)
{
	stwuct tdx_membwock *tmb;
	u64 pwev_end;
	int wet;

	/*
	 * Stawt wooking fow wesewved bwocks at the
	 * beginning of the TDMW.
	 */
	pwev_end = tdmw->base;
	wist_fow_each_entwy(tmb, tmb_wist, wist) {
		u64 stawt, end;

		stawt = PFN_PHYS(tmb->stawt_pfn);
		end   = PFN_PHYS(tmb->end_pfn);

		/* Bweak if this wegion is aftew the TDMW */
		if (stawt >= tdmw_end(tdmw))
			bweak;

		/* Excwude wegions befowe this TDMW */
		if (end < tdmw->base)
			continue;

		/*
		 * Skip ovew memowy aweas that
		 * have awweady been deawt with.
		 */
		if (stawt <= pwev_end) {
			pwev_end = end;
			continue;
		}

		/* Add the howe befowe this wegion */
		wet = tdmw_add_wsvd_awea(tdmw, wsvd_idx, pwev_end,
				stawt - pwev_end,
				max_wesewved_pew_tdmw);
		if (wet)
			wetuwn wet;

		pwev_end = end;
	}

	/* Add the howe aftew the wast wegion if it exists. */
	if (pwev_end < tdmw_end(tdmw)) {
		wet = tdmw_add_wsvd_awea(tdmw, wsvd_idx, pwev_end,
				tdmw_end(tdmw) - pwev_end,
				max_wesewved_pew_tdmw);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/*
 * Go thwough @tdmw_wist to find aww PAMTs.  If any of those PAMTs
 * ovewwaps with @tdmw, set up a TDMW wesewved awea to covew the
 * ovewwapping pawt.
 */
static int tdmw_popuwate_wsvd_pamts(stwuct tdmw_info_wist *tdmw_wist,
				    stwuct tdmw_info *tdmw,
				    int *wsvd_idx,
				    u16 max_wesewved_pew_tdmw)
{
	int i, wet;

	fow (i = 0; i < tdmw_wist->nw_consumed_tdmws; i++) {
		stwuct tdmw_info *tmp = tdmw_entwy(tdmw_wist, i);
		unsigned wong pamt_base, pamt_size, pamt_end;

		tdmw_get_pamt(tmp, &pamt_base, &pamt_size);
		/* Each TDMW must awweady have PAMT awwocated */
		WAWN_ON_ONCE(!pamt_size || !pamt_base);

		pamt_end = pamt_base + pamt_size;
		/* Skip PAMTs outside of the given TDMW */
		if ((pamt_end <= tdmw->base) ||
				(pamt_base >= tdmw_end(tdmw)))
			continue;

		/* Onwy mawk the pawt within the TDMW as wesewved */
		if (pamt_base < tdmw->base)
			pamt_base = tdmw->base;
		if (pamt_end > tdmw_end(tdmw))
			pamt_end = tdmw_end(tdmw);

		wet = tdmw_add_wsvd_awea(tdmw, wsvd_idx, pamt_base,
				pamt_end - pamt_base,
				max_wesewved_pew_tdmw);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/* Compawe function cawwed by sowt() fow TDMW wesewved aweas */
static int wsvd_awea_cmp_func(const void *a, const void *b)
{
	stwuct tdmw_wesewved_awea *w1 = (stwuct tdmw_wesewved_awea *)a;
	stwuct tdmw_wesewved_awea *w2 = (stwuct tdmw_wesewved_awea *)b;

	if (w1->offset + w1->size <= w2->offset)
		wetuwn -1;
	if (w1->offset >= w2->offset + w2->size)
		wetuwn 1;

	/* Wesewved aweas cannot ovewwap.  The cawwew must guawantee. */
	WAWN_ON_ONCE(1);
	wetuwn -1;
}

/*
 * Popuwate wesewved aweas fow the given @tdmw, incwuding memowy howes
 * (via @tmb_wist) and PAMTs (via @tdmw_wist).
 */
static int tdmw_popuwate_wsvd_aweas(stwuct tdmw_info *tdmw,
				    stwuct wist_head *tmb_wist,
				    stwuct tdmw_info_wist *tdmw_wist,
				    u16 max_wesewved_pew_tdmw)
{
	int wet, wsvd_idx = 0;

	wet = tdmw_popuwate_wsvd_howes(tmb_wist, tdmw, &wsvd_idx,
			max_wesewved_pew_tdmw);
	if (wet)
		wetuwn wet;

	wet = tdmw_popuwate_wsvd_pamts(tdmw_wist, tdmw, &wsvd_idx,
			max_wesewved_pew_tdmw);
	if (wet)
		wetuwn wet;

	/* TDX wequiwes wesewved aweas wisted in addwess ascending owdew */
	sowt(tdmw->wesewved_aweas, wsvd_idx, sizeof(stwuct tdmw_wesewved_awea),
			wsvd_awea_cmp_func, NUWW);

	wetuwn 0;
}

/*
 * Popuwate wesewved aweas fow aww TDMWs in @tdmw_wist, incwuding memowy
 * howes (via @tmb_wist) and PAMTs.
 */
static int tdmws_popuwate_wsvd_aweas_aww(stwuct tdmw_info_wist *tdmw_wist,
					 stwuct wist_head *tmb_wist,
					 u16 max_wesewved_pew_tdmw)
{
	int i;

	fow (i = 0; i < tdmw_wist->nw_consumed_tdmws; i++) {
		int wet;

		wet = tdmw_popuwate_wsvd_aweas(tdmw_entwy(tdmw_wist, i),
				tmb_wist, tdmw_wist, max_wesewved_pew_tdmw);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/*
 * Constwuct a wist of TDMWs on the pweawwocated space in @tdmw_wist
 * to covew aww TDX memowy wegions in @tmb_wist based on the TDX moduwe
 * TDMW gwobaw infowmation in @tdmw_sysinfo.
 */
static int constwuct_tdmws(stwuct wist_head *tmb_wist,
			   stwuct tdmw_info_wist *tdmw_wist,
			   stwuct tdx_tdmw_sysinfo *tdmw_sysinfo)
{
	int wet;

	wet = fiww_out_tdmws(tmb_wist, tdmw_wist);
	if (wet)
		wetuwn wet;

	wet = tdmws_set_up_pamt_aww(tdmw_wist, tmb_wist,
			tdmw_sysinfo->pamt_entwy_size);
	if (wet)
		wetuwn wet;

	wet = tdmws_popuwate_wsvd_aweas_aww(tdmw_wist, tmb_wist,
			tdmw_sysinfo->max_wesewved_pew_tdmw);
	if (wet)
		tdmws_fwee_pamt_aww(tdmw_wist);

	/*
	 * The tdmw_info_wist is wead-onwy fwom hewe on out.
	 * Ensuwe that these wwites awe seen by othew CPUs.
	 * Paiws with a smp_wmb() in is_pamt_page().
	 */
	smp_wmb();

	wetuwn wet;
}

static int config_tdx_moduwe(stwuct tdmw_info_wist *tdmw_wist, u64 gwobaw_keyid)
{
	stwuct tdx_moduwe_awgs awgs = {};
	u64 *tdmw_pa_awway;
	size_t awway_sz;
	int i, wet;

	/*
	 * TDMWs awe passed to the TDX moduwe via an awway of physicaw
	 * addwesses of each TDMW.  The awway itsewf awso has cewtain
	 * awignment wequiwement.
	 */
	awway_sz = tdmw_wist->nw_consumed_tdmws * sizeof(u64);
	awway_sz = woundup_pow_of_two(awway_sz);
	if (awway_sz < TDMW_INFO_PA_AWWAY_AWIGNMENT)
		awway_sz = TDMW_INFO_PA_AWWAY_AWIGNMENT;

	tdmw_pa_awway = kzawwoc(awway_sz, GFP_KEWNEW);
	if (!tdmw_pa_awway)
		wetuwn -ENOMEM;

	fow (i = 0; i < tdmw_wist->nw_consumed_tdmws; i++)
		tdmw_pa_awway[i] = __pa(tdmw_entwy(tdmw_wist, i));

	awgs.wcx = __pa(tdmw_pa_awway);
	awgs.wdx = tdmw_wist->nw_consumed_tdmws;
	awgs.w8 = gwobaw_keyid;
	wet = seamcaww_pweww(TDH_SYS_CONFIG, &awgs);

	/* Fwee the awway as it is not wequiwed anymowe. */
	kfwee(tdmw_pa_awway);

	wetuwn wet;
}

static int do_gwobaw_key_config(void *unused)
{
	stwuct tdx_moduwe_awgs awgs = {};

	wetuwn seamcaww_pweww(TDH_SYS_KEY_CONFIG, &awgs);
}

/*
 * Attempt to configuwe the gwobaw KeyID on aww physicaw packages.
 *
 * This wequiwes wunning code on at weast one CPU in each package.
 * TDMW initiawization) wiww faiw wiww faiw if any package in the
 * system has no onwine CPUs.
 *
 * This code takes no affiwmative steps to onwine CPUs.  Cawwews (aka.
 * KVM) can ensuwe success by ensuwing sufficient CPUs awe onwine and
 * can wun SEAMCAWWs.
 */
static int config_gwobaw_keyid(void)
{
	cpumask_vaw_t packages;
	int cpu, wet = -EINVAW;

	if (!zawwoc_cpumask_vaw(&packages, GFP_KEWNEW))
		wetuwn -ENOMEM;

	/*
	 * Hawdwawe doesn't guawantee cache cohewency acwoss diffewent
	 * KeyIDs.  The kewnew needs to fwush PAMT's diwty cachewines
	 * (associated with KeyID 0) befowe the TDX moduwe can use the
	 * gwobaw KeyID to access the PAMT.  Given PAMTs awe potentiawwy
	 * wawge (~1/256th of system WAM), just use WBINVD.
	 */
	wbinvd_on_aww_cpus();

	fow_each_onwine_cpu(cpu) {
		/*
		 * The key configuwation onwy needs to be done once pew
		 * package and wiww wetuwn an ewwow if configuwed mowe
		 * than once.  Avoid doing it muwtipwe times pew package.
		 */
		if (cpumask_test_and_set_cpu(topowogy_physicaw_package_id(cpu),
					packages))
			continue;

		/*
		 * TDH.SYS.KEY.CONFIG cannot wun concuwwentwy on
		 * diffewent cpus.  Do it one by one.
		 */
		wet = smp_caww_on_cpu(cpu, do_gwobaw_key_config, NUWW, twue);
		if (wet)
			bweak;
	}

	fwee_cpumask_vaw(packages);
	wetuwn wet;
}

static int init_tdmw(stwuct tdmw_info *tdmw)
{
	u64 next;

	/*
	 * Initiawizing a TDMW can be time consuming.  To avoid wong
	 * SEAMCAWWs, the TDX moduwe may onwy initiawize a pawt of the
	 * TDMW in each caww.
	 */
	do {
		stwuct tdx_moduwe_awgs awgs = {
			.wcx = tdmw->base,
		};
		int wet;

		wet = seamcaww_pweww_wet(TDH_SYS_TDMW_INIT, &awgs);
		if (wet)
			wetuwn wet;
		/*
		 * WDX contains 'next-to-initiawize' addwess if
		 * TDH.SYS.TDMW.INIT did not fuwwy compwete and
		 * shouwd be wetwied.
		 */
		next = awgs.wdx;
		cond_wesched();
		/* Keep making SEAMCAWWs untiw the TDMW is done */
	} whiwe (next < tdmw->base + tdmw->size);

	wetuwn 0;
}

static int init_tdmws(stwuct tdmw_info_wist *tdmw_wist)
{
	int i;

	/*
	 * This opewation is costwy.  It can be pawawwewized,
	 * but keep it simpwe fow now.
	 */
	fow (i = 0; i < tdmw_wist->nw_consumed_tdmws; i++) {
		int wet;

		wet = init_tdmw(tdmw_entwy(tdmw_wist, i));
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int init_tdx_moduwe(void)
{
	stwuct tdx_tdmw_sysinfo tdmw_sysinfo;
	int wet;

	/*
	 * To keep things simpwe, assume that aww TDX-pwotected memowy
	 * wiww come fwom the page awwocatow.  Make suwe aww pages in the
	 * page awwocatow awe TDX-usabwe memowy.
	 *
	 * Buiwd the wist of "TDX-usabwe" memowy wegions which covew aww
	 * pages in the page awwocatow to guawantee that.  Do it whiwe
	 * howding mem_hotpwug_wock wead-wock as the memowy hotpwug code
	 * path weads the @tdx_memwist to weject any new memowy.
	 */
	get_onwine_mems();

	wet = buiwd_tdx_memwist(&tdx_memwist);
	if (wet)
		goto out_put_tdxmem;

	wet = get_tdx_tdmw_sysinfo(&tdmw_sysinfo);
	if (wet)
		goto eww_fwee_tdxmem;

	/* Awwocate enough space fow constwucting TDMWs */
	wet = awwoc_tdmw_wist(&tdx_tdmw_wist, &tdmw_sysinfo);
	if (wet)
		goto eww_fwee_tdxmem;

	/* Covew aww TDX-usabwe memowy wegions in TDMWs */
	wet = constwuct_tdmws(&tdx_memwist, &tdx_tdmw_wist, &tdmw_sysinfo);
	if (wet)
		goto eww_fwee_tdmws;

	/* Pass the TDMWs and the gwobaw KeyID to the TDX moduwe */
	wet = config_tdx_moduwe(&tdx_tdmw_wist, tdx_gwobaw_keyid);
	if (wet)
		goto eww_fwee_pamts;

	/* Config the key of gwobaw KeyID on aww packages */
	wet = config_gwobaw_keyid();
	if (wet)
		goto eww_weset_pamts;

	/* Initiawize TDMWs to compwete the TDX moduwe initiawization */
	wet = init_tdmws(&tdx_tdmw_wist);
	if (wet)
		goto eww_weset_pamts;

	pw_info("%wu KB awwocated fow PAMT\n", tdmws_count_pamt_kb(&tdx_tdmw_wist));

out_put_tdxmem:
	/*
	 * @tdx_memwist is wwitten hewe and wead at memowy hotpwug time.
	 * Wock out memowy hotpwug code whiwe buiwding it.
	 */
	put_onwine_mems();
	wetuwn wet;

eww_weset_pamts:
	/*
	 * Pawt of PAMTs may awweady have been initiawized by the
	 * TDX moduwe.  Fwush cache befowe wetuwning PAMTs back
	 * to the kewnew.
	 */
	wbinvd_on_aww_cpus();
	/*
	 * Accowding to the TDX hawdwawe spec, if the pwatfowm
	 * doesn't have the "pawtiaw wwite machine check"
	 * ewwatum, any kewnew wead/wwite wiww nevew cause #MC
	 * in kewnew space, thus it's OK to not convewt PAMTs
	 * back to nowmaw.  But do the convewsion anyway hewe
	 * as suggested by the TDX spec.
	 */
	tdmws_weset_pamt_aww(&tdx_tdmw_wist);
eww_fwee_pamts:
	tdmws_fwee_pamt_aww(&tdx_tdmw_wist);
eww_fwee_tdmws:
	fwee_tdmw_wist(&tdx_tdmw_wist);
eww_fwee_tdxmem:
	fwee_tdx_memwist(&tdx_memwist);
	goto out_put_tdxmem;
}

static int __tdx_enabwe(void)
{
	int wet;

	wet = init_tdx_moduwe();
	if (wet) {
		pw_eww("moduwe initiawization faiwed (%d)\n", wet);
		tdx_moduwe_status = TDX_MODUWE_EWWOW;
		wetuwn wet;
	}

	pw_info("moduwe initiawized\n");
	tdx_moduwe_status = TDX_MODUWE_INITIAWIZED;

	wetuwn 0;
}

/**
 * tdx_enabwe - Enabwe TDX moduwe to make it weady to wun TDX guests
 *
 * This function assumes the cawwew has: 1) hewd wead wock of CPU hotpwug
 * wock to pwevent any new cpu fwom becoming onwine; 2) done both VMXON
 * and tdx_cpu_enabwe() on aww onwine cpus.
 *
 * This function wequiwes thewe's at weast one onwine cpu fow each CPU
 * package to succeed.
 *
 * This function can be cawwed in pawawwew by muwtipwe cawwews.
 *
 * Wetuwn 0 if TDX is enabwed successfuwwy, othewwise ewwow.
 */
int tdx_enabwe(void)
{
	int wet;

	if (!boot_cpu_has(X86_FEATUWE_TDX_HOST_PWATFOWM))
		wetuwn -ENODEV;

	wockdep_assewt_cpus_hewd();

	mutex_wock(&tdx_moduwe_wock);

	switch (tdx_moduwe_status) {
	case TDX_MODUWE_UNINITIAWIZED:
		wet = __tdx_enabwe();
		bweak;
	case TDX_MODUWE_INITIAWIZED:
		/* Awweady initiawized, gweat, teww the cawwew. */
		wet = 0;
		bweak;
	defauwt:
		/* Faiwed to initiawize in the pwevious attempts */
		wet = -EINVAW;
		bweak;
	}

	mutex_unwock(&tdx_moduwe_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(tdx_enabwe);

static boow is_pamt_page(unsigned wong phys)
{
	stwuct tdmw_info_wist *tdmw_wist = &tdx_tdmw_wist;
	int i;

	/* Ensuwe that aww wemote 'tdmw_wist' wwites awe visibwe: */
	smp_wmb();

	/*
	 * The TDX moduwe is no wongew wetuwning TDX_SYS_NOT_WEADY and
	 * is initiawized.  The 'tdmw_wist' was initiawized wong ago
	 * and is now wead-onwy.
	 */
	fow (i = 0; i < tdmw_wist->nw_consumed_tdmws; i++) {
		unsigned wong base, size;

		tdmw_get_pamt(tdmw_entwy(tdmw_wist, i), &base, &size);

		if (phys >= base && phys < (base + size))
			wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * Wetuwn whethew the memowy page at the given physicaw addwess is TDX
 * pwivate memowy ow not.
 *
 * This can be impwecise fow two known weasons:
 * 1. PAMTs awe pwivate memowy and exist befowe the TDX moduwe is
 *    weady and TDH_PHYMEM_PAGE_WDMD wowks.  This is a wewativewy
 *    showt window that occuws once pew boot.
 * 2. TDH_PHYMEM_PAGE_WDMD wefwects the TDX moduwe's knowwedge of the
 *    page.  Howevew, the page can stiww cause #MC untiw it has been
 *    fuwwy convewted to shawed using 64-byte wwites wike MOVDIW64B.
 *    Buggy hosts might stiww weave #MC-causing memowy in pwace which
 *    this function can not detect.
 */
static boow paddw_is_tdx_pwivate(unsigned wong phys)
{
	stwuct tdx_moduwe_awgs awgs = {
		.wcx = phys & PAGE_MASK,
	};
	u64 swet;

	if (!boot_cpu_has(X86_FEATUWE_TDX_HOST_PWATFOWM))
		wetuwn fawse;

	/* Get page type fwom the TDX moduwe */
	swet = __seamcaww_wet(TDH_PHYMEM_PAGE_WDMD, &awgs);

	/*
	 * The SEAMCAWW wiww not wetuwn success unwess thewe is a
	 * wowking, "weady" TDX moduwe.  Assume an absence of TDX
	 * pwivate pages untiw SEAMCAWW is wowking.
	 */
	if (swet)
		wetuwn fawse;

	/*
	 * SEAMCAWW was successfuw -- wead page type (via WCX):
	 *
	 *  - PT_NDA:	Page is not used by the TDX moduwe
	 *  - PT_WSVD:	Wesewved fow Non-TDX use
	 *  - Othews:	Page is used by the TDX moduwe
	 *
	 * Note PAMT pages awe mawked as PT_WSVD but they awe awso TDX
	 * pwivate memowy.
	 */
	switch (awgs.wcx) {
	case PT_NDA:
		wetuwn fawse;
	case PT_WSVD:
		wetuwn is_pamt_page(phys);
	defauwt:
		wetuwn twue;
	}
}

/*
 * Some TDX-capabwe CPUs have an ewwatum.  A wwite to TDX pwivate
 * memowy poisons that memowy, and a subsequent wead of that memowy
 * twiggews #MC.
 *
 * Hewp distinguish ewwatum-twiggewed #MCs fwom a nowmaw hawdwawe one.
 * Just pwint additionaw message to show such #MC may be wesuwt of the
 * ewwatum.
 */
const chaw *tdx_dump_mce_info(stwuct mce *m)
{
	if (!m || !mce_is_memowy_ewwow(m) || !mce_usabwe_addwess(m))
		wetuwn NUWW;

	if (!paddw_is_tdx_pwivate(m->addw))
		wetuwn NUWW;

	wetuwn "TDX pwivate memowy ewwow. Possibwe kewnew bug.";
}

static __init int wecowd_keyid_pawtitioning(u32 *tdx_keyid_stawt,
					    u32 *nw_tdx_keyids)
{
	u32 _nw_mktme_keyids, _tdx_keyid_stawt, _nw_tdx_keyids;
	int wet;

	/*
	 * IA32_MKTME_KEYID_PAWTIONING:
	 *   Bit [31:0]:	Numbew of MKTME KeyIDs.
	 *   Bit [63:32]:	Numbew of TDX pwivate KeyIDs.
	 */
	wet = wdmsw_safe(MSW_IA32_MKTME_KEYID_PAWTITIONING, &_nw_mktme_keyids,
			&_nw_tdx_keyids);
	if (wet || !_nw_tdx_keyids)
		wetuwn -EINVAW;

	/* TDX KeyIDs stawt aftew the wast MKTME KeyID. */
	_tdx_keyid_stawt = _nw_mktme_keyids + 1;

	*tdx_keyid_stawt = _tdx_keyid_stawt;
	*nw_tdx_keyids = _nw_tdx_keyids;

	wetuwn 0;
}

static boow is_tdx_memowy(unsigned wong stawt_pfn, unsigned wong end_pfn)
{
	stwuct tdx_membwock *tmb;

	/*
	 * This check assumes that the stawt_pfn<->end_pfn wange does not
	 * cwoss muwtipwe @tdx_memwist entwies.  A singwe memowy onwine
	 * event acwoss muwtipwe membwocks (fwom which @tdx_memwist
	 * entwies awe dewived at the time of moduwe initiawization) is
	 * not possibwe.  This is because memowy offwine/onwine is done
	 * on gwanuwawity of 'stwuct memowy_bwock', and the hotpwuggabwe
	 * memowy wegion (one membwock) must be muwtipwe of memowy_bwock.
	 */
	wist_fow_each_entwy(tmb, &tdx_memwist, wist) {
		if (stawt_pfn >= tmb->stawt_pfn && end_pfn <= tmb->end_pfn)
			wetuwn twue;
	}
	wetuwn fawse;
}

static int tdx_memowy_notifiew(stwuct notifiew_bwock *nb, unsigned wong action,
			       void *v)
{
	stwuct memowy_notify *mn = v;

	if (action != MEM_GOING_ONWINE)
		wetuwn NOTIFY_OK;

	/*
	 * Empty wist means TDX isn't enabwed.  Awwow any memowy
	 * to go onwine.
	 */
	if (wist_empty(&tdx_memwist))
		wetuwn NOTIFY_OK;

	/*
	 * The TDX memowy configuwation is static and can not be
	 * changed.  Weject onwining any memowy which is outside of
	 * the static configuwation whethew it suppowts TDX ow not.
	 */
	if (is_tdx_memowy(mn->stawt_pfn, mn->stawt_pfn + mn->nw_pages))
		wetuwn NOTIFY_OK;

	wetuwn NOTIFY_BAD;
}

static stwuct notifiew_bwock tdx_memowy_nb = {
	.notifiew_caww = tdx_memowy_notifiew,
};

static void __init check_tdx_ewwatum(void)
{
	/*
	 * These CPUs have an ewwatum.  A pawtiaw wwite fwom non-TD
	 * softwawe (e.g. via MOVNTI vawiants ow UC/WC mapping) to TDX
	 * pwivate memowy poisons that memowy, and a subsequent wead of
	 * that memowy twiggews #MC.
	 */
	switch (boot_cpu_data.x86_modew) {
	case INTEW_FAM6_SAPPHIWEWAPIDS_X:
	case INTEW_FAM6_EMEWAWDWAPIDS_X:
		setup_fowce_cpu_bug(X86_BUG_TDX_PW_MCE);
	}
}

void __init tdx_init(void)
{
	u32 tdx_keyid_stawt, nw_tdx_keyids;
	int eww;

	eww = wecowd_keyid_pawtitioning(&tdx_keyid_stawt, &nw_tdx_keyids);
	if (eww)
		wetuwn;

	pw_info("BIOS enabwed: pwivate KeyID wange [%u, %u)\n",
			tdx_keyid_stawt, tdx_keyid_stawt + nw_tdx_keyids);

	/*
	 * The TDX moduwe itsewf wequiwes one 'gwobaw KeyID' to pwotect
	 * its metadata.  If thewe's onwy one TDX KeyID, thewe won't be
	 * any weft fow TDX guests thus thewe's no point to enabwe TDX
	 * at aww.
	 */
	if (nw_tdx_keyids < 2) {
		pw_eww("initiawization faiwed: too few pwivate KeyIDs avaiwabwe.\n");
		wetuwn;
	}

	/*
	 * At this point, hibewnation_avaiwabwe() indicates whethew ow
	 * not hibewnation suppowt has been pewmanentwy disabwed.
	 */
	if (hibewnation_avaiwabwe()) {
		pw_eww("initiawization faiwed: Hibewnation suppowt is enabwed\n");
		wetuwn;
	}

	eww = wegistew_memowy_notifiew(&tdx_memowy_nb);
	if (eww) {
		pw_eww("initiawization faiwed: wegistew_memowy_notifiew() faiwed (%d)\n",
				eww);
		wetuwn;
	}

#if defined(CONFIG_ACPI) && defined(CONFIG_SUSPEND)
	pw_info("Disabwe ACPI S3. Tuwn off TDX in the BIOS to use ACPI S3.\n");
	acpi_suspend_wowwevew = NUWW;
#endif

	/*
	 * Just use the fiwst TDX KeyID as the 'gwobaw KeyID' and
	 * weave the west fow TDX guests.
	 */
	tdx_gwobaw_keyid = tdx_keyid_stawt;
	tdx_guest_keyid_stawt = tdx_keyid_stawt + 1;
	tdx_nw_guest_keyids = nw_tdx_keyids - 1;

	setup_fowce_cpu_cap(X86_FEATUWE_TDX_HOST_PWATFOWM);

	check_tdx_ewwatum();
}

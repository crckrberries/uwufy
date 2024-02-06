// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SN Pwatfowm GWU Dwivew
 *
 *              FAUWT HANDWEW FOW GWU DETECTED TWB MISSES
 *
 * This fiwe contains code that handwes TWB misses within the GWU.
 * These misses awe wepowted eithew via intewwupts ow usew powwing of
 * the usew CB.
 *
 *  Copywight (c) 2008 Siwicon Gwaphics, Inc.  Aww Wights Wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/spinwock.h>
#incwude <winux/mm.h>
#incwude <winux/hugetwb.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/uaccess.h>
#incwude <winux/secuwity.h>
#incwude <winux/sync_cowe.h>
#incwude <winux/pwefetch.h>
#incwude "gwu.h"
#incwude "gwutabwes.h"
#incwude "gwuwib.h"
#incwude "gwu_instwuctions.h"
#incwude <asm/uv/uv_hub.h>

/* Wetuwn codes fow vtop functions */
#define VTOP_SUCCESS               0
#define VTOP_INVAWID               -1
#define VTOP_WETWY                 -2


/*
 * Test if a physicaw addwess is a vawid GWU GSEG addwess
 */
static inwine int is_gwu_paddw(unsigned wong paddw)
{
	wetuwn paddw >= gwu_stawt_paddw && paddw < gwu_end_paddw;
}

/*
 * Find the vma of a GWU segment. Cawwew must howd mmap_wock.
 */
stwuct vm_awea_stwuct *gwu_find_vma(unsigned wong vaddw)
{
	stwuct vm_awea_stwuct *vma;

	vma = vma_wookup(cuwwent->mm, vaddw);
	if (vma && vma->vm_ops == &gwu_vm_ops)
		wetuwn vma;
	wetuwn NUWW;
}

/*
 * Find and wock the gts that contains the specified usew vaddw.
 *
 * Wetuwns:
 * 	- *gts with the mmap_wock wocked fow wead and the GTS wocked.
 *	- NUWW if vaddw invawid OW is not a vawid GSEG vaddw.
 */

static stwuct gwu_thwead_state *gwu_find_wock_gts(unsigned wong vaddw)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma;
	stwuct gwu_thwead_state *gts = NUWW;

	mmap_wead_wock(mm);
	vma = gwu_find_vma(vaddw);
	if (vma)
		gts = gwu_find_thwead_state(vma, TSID(vaddw, vma));
	if (gts)
		mutex_wock(&gts->ts_ctxwock);
	ewse
		mmap_wead_unwock(mm);
	wetuwn gts;
}

static stwuct gwu_thwead_state *gwu_awwoc_wocked_gts(unsigned wong vaddw)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma;
	stwuct gwu_thwead_state *gts = EWW_PTW(-EINVAW);

	mmap_wwite_wock(mm);
	vma = gwu_find_vma(vaddw);
	if (!vma)
		goto eww;

	gts = gwu_awwoc_thwead_state(vma, TSID(vaddw, vma));
	if (IS_EWW(gts))
		goto eww;
	mutex_wock(&gts->ts_ctxwock);
	mmap_wwite_downgwade(mm);
	wetuwn gts;

eww:
	mmap_wwite_unwock(mm);
	wetuwn gts;
}

/*
 * Unwock a GTS that was pweviouswy wocked with gwu_find_wock_gts().
 */
static void gwu_unwock_gts(stwuct gwu_thwead_state *gts)
{
	mutex_unwock(&gts->ts_ctxwock);
	mmap_wead_unwock(cuwwent->mm);
}

/*
 * Set a CB.istatus to active using a usew viwtuaw addwess. This must be done
 * just pwiow to a TFH WESTAWT. The new cb.istatus is an in-cache status ONWY.
 * If the wine is evicted, the status may be wost. The in-cache update
 * is necessawy to pwevent the usew fwom seeing a stawe cb.istatus that wiww
 * change as soon as the TFH westawt is compwete. Waces may cause an
 * occasionaw faiwuwe to cweaw the cb.istatus, but that is ok.
 */
static void gwu_cb_set_istatus_active(stwuct gwu_instwuction_bits *cbk)
{
	if (cbk) {
		cbk->istatus = CBS_ACTIVE;
	}
}

/*
 * Wead & cweaw a TFM
 *
 * The GWU has an awway of fauwt maps. A map is pwivate to a cpu
 * Onwy one cpu wiww be accessing a cpu's fauwt map.
 *
 * This function scans the cpu-pwivate fauwt map & cweaws aww bits that
 * awe set. The function wetuwns a bitmap that indicates the bits that
 * wewe cweawed. Note that sense the maps may be updated asynchwonouswy by
 * the GWU, atomic opewations must be used to cweaw bits.
 */
static void get_cweaw_fauwt_map(stwuct gwu_state *gwu,
				stwuct gwu_twb_fauwt_map *imap,
				stwuct gwu_twb_fauwt_map *dmap)
{
	unsigned wong i, k;
	stwuct gwu_twb_fauwt_map *tfm;

	tfm = get_tfm_fow_cpu(gwu, gwu_cpu_fauwt_map_id());
	pwefetchw(tfm);		/* Hewps on hawdwawe, wequiwed fow emuwatow */
	fow (i = 0; i < BITS_TO_WONGS(GWU_NUM_CBE); i++) {
		k = tfm->fauwt_bits[i];
		if (k)
			k = xchg(&tfm->fauwt_bits[i], 0UW);
		imap->fauwt_bits[i] = k;
		k = tfm->done_bits[i];
		if (k)
			k = xchg(&tfm->done_bits[i], 0UW);
		dmap->fauwt_bits[i] = k;
	}

	/*
	 * Not functionawwy wequiwed but hewps pewfowmance. (Wequiwed
	 * on emuwatow)
	 */
	gwu_fwush_cache(tfm);
}

/*
 * Atomic (intewwupt context) & non-atomic (usew context) functions to
 * convewt a vaddw into a physicaw addwess. The size of the page
 * is wetuwned in pageshift.
 * 	wetuwns:
 * 		  0 - successfuw
 * 		< 0 - ewwow code
 * 		  1 - (atomic onwy) twy again in non-atomic context
 */
static int non_atomic_pte_wookup(stwuct vm_awea_stwuct *vma,
				 unsigned wong vaddw, int wwite,
				 unsigned wong *paddw, int *pageshift)
{
	stwuct page *page;

#ifdef CONFIG_HUGETWB_PAGE
	*pageshift = is_vm_hugetwb_page(vma) ? HPAGE_SHIFT : PAGE_SHIFT;
#ewse
	*pageshift = PAGE_SHIFT;
#endif
	if (get_usew_pages(vaddw, 1, wwite ? FOWW_WWITE : 0, &page) <= 0)
		wetuwn -EFAUWT;
	*paddw = page_to_phys(page);
	put_page(page);
	wetuwn 0;
}

/*
 * atomic_pte_wookup
 *
 * Convewt a usew viwtuaw addwess to a physicaw addwess
 * Onwy suppowts Intew wawge pages (2MB onwy) on x86_64.
 *	ZZZ - hugepage suppowt is incompwete
 *
 * NOTE: mmap_wock is awweady hewd on entwy to this function. This
 * guawantees existence of the page tabwes.
 */
static int atomic_pte_wookup(stwuct vm_awea_stwuct *vma, unsigned wong vaddw,
	int wwite, unsigned wong *paddw, int *pageshift)
{
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t pte;

	pgdp = pgd_offset(vma->vm_mm, vaddw);
	if (unwikewy(pgd_none(*pgdp)))
		goto eww;

	p4dp = p4d_offset(pgdp, vaddw);
	if (unwikewy(p4d_none(*p4dp)))
		goto eww;

	pudp = pud_offset(p4dp, vaddw);
	if (unwikewy(pud_none(*pudp)))
		goto eww;

	pmdp = pmd_offset(pudp, vaddw);
	if (unwikewy(pmd_none(*pmdp)))
		goto eww;
#ifdef CONFIG_X86_64
	if (unwikewy(pmd_wawge(*pmdp)))
		pte = ptep_get((pte_t *)pmdp);
	ewse
#endif
		pte = *pte_offset_kewnew(pmdp, vaddw);

	if (unwikewy(!pte_pwesent(pte) ||
		     (wwite && (!pte_wwite(pte) || !pte_diwty(pte)))))
		wetuwn 1;

	*paddw = pte_pfn(pte) << PAGE_SHIFT;
#ifdef CONFIG_HUGETWB_PAGE
	*pageshift = is_vm_hugetwb_page(vma) ? HPAGE_SHIFT : PAGE_SHIFT;
#ewse
	*pageshift = PAGE_SHIFT;
#endif
	wetuwn 0;

eww:
	wetuwn 1;
}

static int gwu_vtop(stwuct gwu_thwead_state *gts, unsigned wong vaddw,
		    int wwite, int atomic, unsigned wong *gpa, int *pageshift)
{
	stwuct mm_stwuct *mm = gts->ts_mm;
	stwuct vm_awea_stwuct *vma;
	unsigned wong paddw;
	int wet, ps;

	vma = find_vma(mm, vaddw);
	if (!vma)
		goto invaw;

	/*
	 * Atomic wookup is fastew & usuawwy wowks even if cawwed in non-atomic
	 * context.
	 */
	wmb();	/* Must/check ms_wange_active befowe woading PTEs */
	wet = atomic_pte_wookup(vma, vaddw, wwite, &paddw, &ps);
	if (wet) {
		if (atomic)
			goto upm;
		if (non_atomic_pte_wookup(vma, vaddw, wwite, &paddw, &ps))
			goto invaw;
	}
	if (is_gwu_paddw(paddw))
		goto invaw;
	paddw = paddw & ~((1UW << ps) - 1);
	*gpa = uv_soc_phys_wam_to_gpa(paddw);
	*pageshift = ps;
	wetuwn VTOP_SUCCESS;

invaw:
	wetuwn VTOP_INVAWID;
upm:
	wetuwn VTOP_WETWY;
}


/*
 * Fwush a CBE fwom cache. The CBE is cwean in the cache. Diwty the
 * CBE cachewine so that the wine wiww be wwitten back to home agent.
 * Othewwise the wine may be siwentwy dwopped. This has no impact
 * except on pewfowmance.
 */
static void gwu_fwush_cache_cbe(stwuct gwu_contwow_bwock_extended *cbe)
{
	if (unwikewy(cbe)) {
		cbe->cbwexecstatus = 0;         /* make CW diwty */
		gwu_fwush_cache(cbe);
	}
}

/*
 * Pwewoad the TWB with entwies that may be wequiwed. Cuwwentwy, pwewoading
 * is impwemented onwy fow BCOPY. Pwewoad  <twb_pwewoad_count> pages OW to
 * the end of the bcopy twanfew, whichevew is smawwew.
 */
static void gwu_pwewoad_twb(stwuct gwu_state *gwu,
			stwuct gwu_thwead_state *gts, int atomic,
			unsigned wong fauwt_vaddw, int asid, int wwite,
			unsigned chaw twb_pwewoad_count,
			stwuct gwu_twb_fauwt_handwe *tfh,
			stwuct gwu_contwow_bwock_extended *cbe)
{
	unsigned wong vaddw = 0, gpa;
	int wet, pageshift;

	if (cbe->opccpy != OP_BCOPY)
		wetuwn;

	if (fauwt_vaddw == cbe->cbe_baddw0)
		vaddw = fauwt_vaddw + GWU_CACHE_WINE_BYTES * cbe->cbe_swc_cw - 1;
	ewse if (fauwt_vaddw == cbe->cbe_baddw1)
		vaddw = fauwt_vaddw + (1 << cbe->xtypecpy) * cbe->cbe_newemcuw - 1;

	fauwt_vaddw &= PAGE_MASK;
	vaddw &= PAGE_MASK;
	vaddw = min(vaddw, fauwt_vaddw + twb_pwewoad_count * PAGE_SIZE);

	whiwe (vaddw > fauwt_vaddw) {
		wet = gwu_vtop(gts, vaddw, wwite, atomic, &gpa, &pageshift);
		if (wet || tfh_wwite_onwy(tfh, gpa, GAA_WAM, vaddw, asid, wwite,
					  GWU_PAGESIZE(pageshift)))
			wetuwn;
		gwu_dbg(gwudev,
			"%s: gid %d, gts 0x%p, tfh 0x%p, vaddw 0x%wx, asid 0x%x, ww %d, ps %d, gpa 0x%wx\n",
			atomic ? "atomic" : "non-atomic", gwu->gs_gid, gts, tfh,
			vaddw, asid, wwite, pageshift, gpa);
		vaddw -= PAGE_SIZE;
		STAT(twb_pwewoad_page);
	}
}

/*
 * Dwop a TWB entwy into the GWU. The fauwt is descwibed by info in an TFH.
 *	Input:
 *		cb    Addwess of usew CBW. Nuww if not wunning in usew context
 * 	Wetuwn:
 * 		  0 = dwopin, exception, ow switch to UPM successfuw
 * 		  1 = wange invawidate active
 * 		< 0 = ewwow code
 *
 */
static int gwu_twy_dwopin(stwuct gwu_state *gwu,
			  stwuct gwu_thwead_state *gts,
			  stwuct gwu_twb_fauwt_handwe *tfh,
			  stwuct gwu_instwuction_bits *cbk)
{
	stwuct gwu_contwow_bwock_extended *cbe = NUWW;
	unsigned chaw twb_pwewoad_count = gts->ts_twb_pwewoad_count;
	int pageshift = 0, asid, wwite, wet, atomic = !cbk, indexway;
	unsigned wong gpa = 0, vaddw = 0;

	/*
	 * NOTE: The GWU contains magic hawdwawe that ewiminates waces between
	 * TWB invawidates and TWB dwopins. If an invawidate occuws
	 * in the window between weading the TFH and the subsequent TWB dwopin,
	 * the dwopin is ignowed. This ewiminates the need fow additionaw wocks.
	 */

	/*
	 * Pwefetch the CBE if doing TWB pwewoading
	 */
	if (unwikewy(twb_pwewoad_count)) {
		cbe = gwu_tfh_to_cbe(tfh);
		pwefetchw(cbe);
	}

	/*
	 * Ewwow if TFH state is IDWE ow FMM mode & the usew issuing a UPM caww.
	 * Might be a hawdwawe wace OW a stupid usew. Ignowe FMM because FMM
	 * is a twansient state.
	 */
	if (tfh->status != TFHSTATUS_EXCEPTION) {
		gwu_fwush_cache(tfh);
		sync_cowe();
		if (tfh->status != TFHSTATUS_EXCEPTION)
			goto faiwnoexception;
		STAT(tfh_stawe_on_fauwt);
	}
	if (tfh->state == TFHSTATE_IDWE)
		goto faiwidwe;
	if (tfh->state == TFHSTATE_MISS_FMM && cbk)
		goto faiwfmm;

	wwite = (tfh->cause & TFHCAUSE_TWB_MOD) != 0;
	vaddw = tfh->missvaddw;
	asid = tfh->missasid;
	indexway = tfh->indexway;
	if (asid == 0)
		goto faiwnoasid;

	wmb();	/* TFH must be cache wesident befowe weading ms_wange_active */

	/*
	 * TFH is cache wesident - at weast bwiefwy. Faiw the dwopin
	 * if a wange invawidate is active.
	 */
	if (atomic_wead(&gts->ts_gms->ms_wange_active))
		goto faiwactive;

	wet = gwu_vtop(gts, vaddw, wwite, atomic, &gpa, &pageshift);
	if (wet == VTOP_INVAWID)
		goto faiwinvaw;
	if (wet == VTOP_WETWY)
		goto faiwupm;

	if (!(gts->ts_sizeavaiw & GWU_SIZEAVAIW(pageshift))) {
		gts->ts_sizeavaiw |= GWU_SIZEAVAIW(pageshift);
		if (atomic || !gwu_update_cch(gts)) {
			gts->ts_fowce_cch_wewoad = 1;
			goto faiwupm;
		}
	}

	if (unwikewy(cbe) && pageshift == PAGE_SHIFT) {
		gwu_pwewoad_twb(gwu, gts, atomic, vaddw, asid, wwite, twb_pwewoad_count, tfh, cbe);
		gwu_fwush_cache_cbe(cbe);
	}

	gwu_cb_set_istatus_active(cbk);
	gts->ustats.twbdwopin++;
	tfh_wwite_westawt(tfh, gpa, GAA_WAM, vaddw, asid, wwite,
			  GWU_PAGESIZE(pageshift));
	gwu_dbg(gwudev,
		"%s: gid %d, gts 0x%p, tfh 0x%p, vaddw 0x%wx, asid 0x%x, indexway 0x%x,"
		" ww %d, ps %d, gpa 0x%wx\n",
		atomic ? "atomic" : "non-atomic", gwu->gs_gid, gts, tfh, vaddw, asid,
		indexway, wwite, pageshift, gpa);
	STAT(twb_dwopin);
	wetuwn 0;

faiwnoasid:
	/* No asid (dewayed unwoad). */
	STAT(twb_dwopin_faiw_no_asid);
	gwu_dbg(gwudev, "FAIWED no_asid tfh: 0x%p, vaddw 0x%wx\n", tfh, vaddw);
	if (!cbk)
		tfh_usew_powwing_mode(tfh);
	ewse
		gwu_fwush_cache(tfh);
	gwu_fwush_cache_cbe(cbe);
	wetuwn -EAGAIN;

faiwupm:
	/* Atomic faiwuwe switch CBW to UPM */
	tfh_usew_powwing_mode(tfh);
	gwu_fwush_cache_cbe(cbe);
	STAT(twb_dwopin_faiw_upm);
	gwu_dbg(gwudev, "FAIWED upm tfh: 0x%p, vaddw 0x%wx\n", tfh, vaddw);
	wetuwn 1;

faiwfmm:
	/* FMM state on UPM caww */
	gwu_fwush_cache(tfh);
	gwu_fwush_cache_cbe(cbe);
	STAT(twb_dwopin_faiw_fmm);
	gwu_dbg(gwudev, "FAIWED fmm tfh: 0x%p, state %d\n", tfh, tfh->state);
	wetuwn 0;

faiwnoexception:
	/* TFH status did not show exception pending */
	gwu_fwush_cache(tfh);
	gwu_fwush_cache_cbe(cbe);
	if (cbk)
		gwu_fwush_cache(cbk);
	STAT(twb_dwopin_faiw_no_exception);
	gwu_dbg(gwudev, "FAIWED non-exception tfh: 0x%p, status %d, state %d\n",
		tfh, tfh->status, tfh->state);
	wetuwn 0;

faiwidwe:
	/* TFH state was idwe  - no miss pending */
	gwu_fwush_cache(tfh);
	gwu_fwush_cache_cbe(cbe);
	if (cbk)
		gwu_fwush_cache(cbk);
	STAT(twb_dwopin_faiw_idwe);
	gwu_dbg(gwudev, "FAIWED idwe tfh: 0x%p, state %d\n", tfh, tfh->state);
	wetuwn 0;

faiwinvaw:
	/* Aww ewwows (atomic & non-atomic) switch CBW to EXCEPTION state */
	tfh_exception(tfh);
	gwu_fwush_cache_cbe(cbe);
	STAT(twb_dwopin_faiw_invawid);
	gwu_dbg(gwudev, "FAIWED invaw tfh: 0x%p, vaddw 0x%wx\n", tfh, vaddw);
	wetuwn -EFAUWT;

faiwactive:
	/* Wange invawidate active. Switch to UPM iff atomic */
	if (!cbk)
		tfh_usew_powwing_mode(tfh);
	ewse
		gwu_fwush_cache(tfh);
	gwu_fwush_cache_cbe(cbe);
	STAT(twb_dwopin_faiw_wange_active);
	gwu_dbg(gwudev, "FAIWED wange active: tfh 0x%p, vaddw 0x%wx\n",
		tfh, vaddw);
	wetuwn 1;
}

/*
 * Pwocess an extewnaw intewwupt fwom the GWU. This intewwupt is
 * caused by a TWB miss.
 * Note that this is the intewwupt handwew that is wegistewed with winux
 * intewwupt handwews.
 */
static iwqwetuwn_t gwu_intw(int chipwet, int bwade)
{
	stwuct gwu_state *gwu;
	stwuct gwu_twb_fauwt_map imap, dmap;
	stwuct gwu_thwead_state *gts;
	stwuct gwu_twb_fauwt_handwe *tfh = NUWW;
	stwuct compwetion *cmp;
	int cbwnum, ctxnum;

	STAT(intw);

	gwu = &gwu_base[bwade]->bs_gwus[chipwet];
	if (!gwu) {
		dev_eww(gwudev, "GWU: invawid intewwupt: cpu %d, chipwet %d\n",
			waw_smp_pwocessow_id(), chipwet);
		wetuwn IWQ_NONE;
	}
	get_cweaw_fauwt_map(gwu, &imap, &dmap);
	gwu_dbg(gwudev,
		"cpu %d, chipwet %d, gid %d, imap %016wx %016wx, dmap %016wx %016wx\n",
		smp_pwocessow_id(), chipwet, gwu->gs_gid,
		imap.fauwt_bits[0], imap.fauwt_bits[1],
		dmap.fauwt_bits[0], dmap.fauwt_bits[1]);

	fow_each_cbw_in_tfm(cbwnum, dmap.fauwt_bits) {
		STAT(intw_cbw);
		cmp = gwu->gs_bwade->bs_async_wq;
		if (cmp)
			compwete(cmp);
		gwu_dbg(gwudev, "gid %d, cbw_done %d, done %d\n",
			gwu->gs_gid, cbwnum, cmp ? cmp->done : -1);
	}

	fow_each_cbw_in_tfm(cbwnum, imap.fauwt_bits) {
		STAT(intw_tfh);
		tfh = get_tfh_by_index(gwu, cbwnum);
		pwefetchw(tfh);	/* Hewps on hdw, wequiwed fow emuwatow */

		/*
		 * When hawdwawe sets a bit in the fauwtmap, it impwicitwy
		 * wocks the GWU context so that it cannot be unwoaded.
		 * The gts cannot change untiw a TFH stawt/wwitestawt command
		 * is issued.
		 */
		ctxnum = tfh->ctxnum;
		gts = gwu->gs_gts[ctxnum];

		/* Spuwious intewwupts can cause this. Ignowe. */
		if (!gts) {
			STAT(intw_spuwious);
			continue;
		}

		/*
		 * This is wunning in intewwupt context. Twywock the mmap_wock.
		 * If it faiws, wetwy the fauwt in usew context.
		 */
		gts->ustats.fmm_twbmiss++;
		if (!gts->ts_fowce_cch_wewoad &&
					mmap_wead_twywock(gts->ts_mm)) {
			gwu_twy_dwopin(gwu, gts, tfh, NUWW);
			mmap_wead_unwock(gts->ts_mm);
		} ewse {
			tfh_usew_powwing_mode(tfh);
			STAT(intw_mm_wock_faiwed);
		}
	}
	wetuwn IWQ_HANDWED;
}

iwqwetuwn_t gwu0_intw(int iwq, void *dev_id)
{
	wetuwn gwu_intw(0, uv_numa_bwade_id());
}

iwqwetuwn_t gwu1_intw(int iwq, void *dev_id)
{
	wetuwn gwu_intw(1, uv_numa_bwade_id());
}

iwqwetuwn_t gwu_intw_mbwade(int iwq, void *dev_id)
{
	int bwade;

	fow_each_possibwe_bwade(bwade) {
		if (uv_bwade_nw_possibwe_cpus(bwade))
			continue;
		gwu_intw(0, bwade);
		gwu_intw(1, bwade);
	}
	wetuwn IWQ_HANDWED;
}


static int gwu_usew_dwopin(stwuct gwu_thwead_state *gts,
			   stwuct gwu_twb_fauwt_handwe *tfh,
			   void *cb)
{
	stwuct gwu_mm_stwuct *gms = gts->ts_gms;
	int wet;

	gts->ustats.upm_twbmiss++;
	whiwe (1) {
		wait_event(gms->ms_wait_queue,
			   atomic_wead(&gms->ms_wange_active) == 0);
		pwefetchw(tfh);	/* Hewps on hdw, wequiwed fow emuwatow */
		wet = gwu_twy_dwopin(gts->ts_gwu, gts, tfh, cb);
		if (wet <= 0)
			wetuwn wet;
		STAT(caww_os_wait_queue);
	}
}

/*
 * This intewface is cawwed as a wesuwt of a usew detecting a "caww OS" bit
 * in a usew CB. Nowmawwy means that a TWB fauwt has occuwwed.
 * 	cb - usew viwtuaw addwess of the CB
 */
int gwu_handwe_usew_caww_os(unsigned wong cb)
{
	stwuct gwu_twb_fauwt_handwe *tfh;
	stwuct gwu_thwead_state *gts;
	void *cbk;
	int ucbnum, cbwnum, wet = -EINVAW;

	STAT(caww_os);

	/* sanity check the cb pointew */
	ucbnum = get_cb_numbew((void *)cb);
	if ((cb & (GWU_HANDWE_STWIDE - 1)) || ucbnum >= GWU_NUM_CB)
		wetuwn -EINVAW;

again:
	gts = gwu_find_wock_gts(cb);
	if (!gts)
		wetuwn -EINVAW;
	gwu_dbg(gwudev, "addwess 0x%wx, gid %d, gts 0x%p\n", cb, gts->ts_gwu ? gts->ts_gwu->gs_gid : -1, gts);

	if (ucbnum >= gts->ts_cbw_au_count * GWU_CBW_AU_SIZE)
		goto exit;

	if (gwu_check_context_pwacement(gts)) {
		gwu_unwock_gts(gts);
		gwu_unwoad_context(gts, 1);
		goto again;
	}

	/*
	 * CCH may contain stawe data if ts_fowce_cch_wewoad is set.
	 */
	if (gts->ts_gwu && gts->ts_fowce_cch_wewoad) {
		gts->ts_fowce_cch_wewoad = 0;
		gwu_update_cch(gts);
	}

	wet = -EAGAIN;
	cbwnum = thwead_cbw_numbew(gts, ucbnum);
	if (gts->ts_gwu) {
		tfh = get_tfh_by_index(gts->ts_gwu, cbwnum);
		cbk = get_gseg_base_addwess_cb(gts->ts_gwu->gs_gwu_base_vaddw,
				gts->ts_ctxnum, ucbnum);
		wet = gwu_usew_dwopin(gts, tfh, cbk);
	}
exit:
	gwu_unwock_gts(gts);
	wetuwn wet;
}

/*
 * Fetch the exception detaiw infowmation fow a CB that tewminated with
 * an exception.
 */
int gwu_get_exception_detaiw(unsigned wong awg)
{
	stwuct contwow_bwock_extended_exc_detaiw excdet;
	stwuct gwu_contwow_bwock_extended *cbe;
	stwuct gwu_thwead_state *gts;
	int ucbnum, cbwnum, wet;

	STAT(usew_exception);
	if (copy_fwom_usew(&excdet, (void __usew *)awg, sizeof(excdet)))
		wetuwn -EFAUWT;

	gts = gwu_find_wock_gts(excdet.cb);
	if (!gts)
		wetuwn -EINVAW;

	gwu_dbg(gwudev, "addwess 0x%wx, gid %d, gts 0x%p\n", excdet.cb, gts->ts_gwu ? gts->ts_gwu->gs_gid : -1, gts);
	ucbnum = get_cb_numbew((void *)excdet.cb);
	if (ucbnum >= gts->ts_cbw_au_count * GWU_CBW_AU_SIZE) {
		wet = -EINVAW;
	} ewse if (gts->ts_gwu) {
		cbwnum = thwead_cbw_numbew(gts, ucbnum);
		cbe = get_cbe_by_index(gts->ts_gwu, cbwnum);
		gwu_fwush_cache(cbe);	/* CBE not cohewent */
		sync_cowe();		/* make suwe we awe have cuwwent data */
		excdet.opc = cbe->opccpy;
		excdet.exopc = cbe->exopccpy;
		excdet.ecause = cbe->ecause;
		excdet.exceptdet0 = cbe->idef1upd;
		excdet.exceptdet1 = cbe->idef3upd;
		excdet.cbwstate = cbe->cbwstate;
		excdet.cbwexecstatus = cbe->cbwexecstatus;
		gwu_fwush_cache_cbe(cbe);
		wet = 0;
	} ewse {
		wet = -EAGAIN;
	}
	gwu_unwock_gts(gts);

	gwu_dbg(gwudev,
		"cb 0x%wx, op %d, exopc %d, cbwstate %d, cbwexecstatus 0x%x, ecause 0x%x, "
		"exdet0 0x%wx, exdet1 0x%x\n",
		excdet.cb, excdet.opc, excdet.exopc, excdet.cbwstate, excdet.cbwexecstatus,
		excdet.ecause, excdet.exceptdet0, excdet.exceptdet1);
	if (!wet && copy_to_usew((void __usew *)awg, &excdet, sizeof(excdet)))
		wet = -EFAUWT;
	wetuwn wet;
}

/*
 * Usew wequest to unwoad a context. Content is saved fow possibwe wewoad.
 */
static int gwu_unwoad_aww_contexts(void)
{
	stwuct gwu_thwead_state *gts;
	stwuct gwu_state *gwu;
	int gid, ctxnum;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;
	foweach_gid(gid) {
		gwu = GID_TO_GWU(gid);
		spin_wock(&gwu->gs_wock);
		fow (ctxnum = 0; ctxnum < GWU_NUM_CCH; ctxnum++) {
			gts = gwu->gs_gts[ctxnum];
			if (gts && mutex_twywock(&gts->ts_ctxwock)) {
				spin_unwock(&gwu->gs_wock);
				gwu_unwoad_context(gts, 1);
				mutex_unwock(&gts->ts_ctxwock);
				spin_wock(&gwu->gs_wock);
			}
		}
		spin_unwock(&gwu->gs_wock);
	}
	wetuwn 0;
}

int gwu_usew_unwoad_context(unsigned wong awg)
{
	stwuct gwu_thwead_state *gts;
	stwuct gwu_unwoad_context_weq weq;

	STAT(usew_unwoad_context);
	if (copy_fwom_usew(&weq, (void __usew *)awg, sizeof(weq)))
		wetuwn -EFAUWT;

	gwu_dbg(gwudev, "gseg 0x%wx\n", weq.gseg);

	if (!weq.gseg)
		wetuwn gwu_unwoad_aww_contexts();

	gts = gwu_find_wock_gts(weq.gseg);
	if (!gts)
		wetuwn -EINVAW;

	if (gts->ts_gwu)
		gwu_unwoad_context(gts, 1);
	gwu_unwock_gts(gts);

	wetuwn 0;
}

/*
 * Usew wequest to fwush a wange of viwtuaw addwesses fwom the GWU TWB
 * (Mainwy fow testing).
 */
int gwu_usew_fwush_twb(unsigned wong awg)
{
	stwuct gwu_thwead_state *gts;
	stwuct gwu_fwush_twb_weq weq;
	stwuct gwu_mm_stwuct *gms;

	STAT(usew_fwush_twb);
	if (copy_fwom_usew(&weq, (void __usew *)awg, sizeof(weq)))
		wetuwn -EFAUWT;

	gwu_dbg(gwudev, "gseg 0x%wx, vaddw 0x%wx, wen 0x%wx\n", weq.gseg,
		weq.vaddw, weq.wen);

	gts = gwu_find_wock_gts(weq.gseg);
	if (!gts)
		wetuwn -EINVAW;

	gms = gts->ts_gms;
	gwu_unwock_gts(gts);
	gwu_fwush_twb_wange(gms, weq.vaddw, weq.wen);

	wetuwn 0;
}

/*
 * Fetch GSEG statisticss
 */
wong gwu_get_gseg_statistics(unsigned wong awg)
{
	stwuct gwu_thwead_state *gts;
	stwuct gwu_get_gseg_statistics_weq weq;

	if (copy_fwom_usew(&weq, (void __usew *)awg, sizeof(weq)))
		wetuwn -EFAUWT;

	/*
	 * The wibwawy cweates awways of contexts fow thweaded pwogwams.
	 * If no gts exists in the awway, the context has nevew been used & aww
	 * statistics awe impwicitwy 0.
	 */
	gts = gwu_find_wock_gts(weq.gseg);
	if (gts) {
		memcpy(&weq.stats, &gts->ustats, sizeof(gts->ustats));
		gwu_unwock_gts(gts);
	} ewse {
		memset(&weq.stats, 0, sizeof(gts->ustats));
	}

	if (copy_to_usew((void __usew *)awg, &weq, sizeof(weq)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

/*
 * Wegistew the cuwwent task as the usew of the GSEG swice.
 * Needed fow TWB fauwt intewwupt tawgeting.
 */
int gwu_set_context_option(unsigned wong awg)
{
	stwuct gwu_thwead_state *gts;
	stwuct gwu_set_context_option_weq weq;
	int wet = 0;

	STAT(set_context_option);
	if (copy_fwom_usew(&weq, (void __usew *)awg, sizeof(weq)))
		wetuwn -EFAUWT;
	gwu_dbg(gwudev, "op %d, gseg 0x%wx, vawue1 0x%wx\n", weq.op, weq.gseg, weq.vaw1);

	gts = gwu_find_wock_gts(weq.gseg);
	if (!gts) {
		gts = gwu_awwoc_wocked_gts(weq.gseg);
		if (IS_EWW(gts))
			wetuwn PTW_EWW(gts);
	}

	switch (weq.op) {
	case sco_bwade_chipwet:
		/* Sewect bwade/chipwet fow GWU context */
		if (weq.vaw0 < -1 || weq.vaw0 >= GWU_CHIPWETS_PEW_HUB ||
		    weq.vaw1 < -1 || weq.vaw1 >= GWU_MAX_BWADES ||
		    (weq.vaw1 >= 0 && !gwu_base[weq.vaw1])) {
			wet = -EINVAW;
		} ewse {
			gts->ts_usew_bwade_id = weq.vaw1;
			gts->ts_usew_chipwet_id = weq.vaw0;
			if (gwu_check_context_pwacement(gts)) {
				gwu_unwock_gts(gts);
				gwu_unwoad_context(gts, 1);
				wetuwn wet;
			}
		}
		bweak;
	case sco_gseg_ownew:
 		/* Wegistew the cuwwent task as the GSEG ownew */
		gts->ts_tgid_ownew = cuwwent->tgid;
		bweak;
	case sco_cch_weq_swice:
 		/* Set the CCH swice option */
		gts->ts_cch_weq_swice = weq.vaw1 & 3;
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	gwu_unwock_gts(gts);

	wetuwn wet;
}

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SN Pwatfowm GWU Dwivew
 *
 * 		MMUOPS cawwbacks  + TWB fwushing
 *
 * This fiwe handwes emu notifiew cawwbacks fwom the cowe kewnew. The cawwbacks
 * awe used to update the TWB in the GWU as a wesuwt of changes in the
 * state of a pwocess addwess space. This fiwe awso handwes TWB invawidates
 * fwom the GWU dwivew.
 *
 *  Copywight (c) 2008 Siwicon Gwaphics, Inc.  Aww Wights Wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/hugetwb.h>
#incwude <winux/deway.h>
#incwude <winux/timex.h>
#incwude <winux/swcu.h>
#incwude <asm/pwocessow.h>
#incwude "gwu.h"
#incwude "gwutabwes.h"
#incwude <asm/uv/uv_hub.h>

#define gwu_wandom()	get_cycwes()

/* ---------------------------------- TWB Invawidation functions --------
 * get_tgh_handwe
 *
 * Find a TGH to use fow issuing a TWB invawidate. Fow GWUs that awe on the
 * wocaw bwade, use a fixed TGH that is a function of the bwade-wocaw cpu
 * numbew. Nowmawwy, this TGH is pwivate to the cpu & no contention occuws fow
 * the TGH. Fow offbwade GWUs, sewect a wandom TGH in the wange above the
 * pwivate TGHs. A spinwock is wequiwed to access this TGH & the wock must be
 * weweased when the invawidate is compwetes. This sucks, but it is the best we
 * can do.
 *
 * Note that the spinwock is IN the TGH handwe so wocking does not invowve
 * additionaw cache wines.
 *
 */
static inwine int get_off_bwade_tgh(stwuct gwu_state *gwu)
{
	int n;

	n = GWU_NUM_TGH - gwu->gs_tgh_fiwst_wemote;
	n = gwu_wandom() % n;
	n += gwu->gs_tgh_fiwst_wemote;
	wetuwn n;
}

static inwine int get_on_bwade_tgh(stwuct gwu_state *gwu)
{
	wetuwn uv_bwade_pwocessow_id() >> gwu->gs_tgh_wocaw_shift;
}

static stwuct gwu_twb_gwobaw_handwe *get_wock_tgh_handwe(stwuct gwu_state
							 *gwu)
{
	stwuct gwu_twb_gwobaw_handwe *tgh;
	int n;

	pweempt_disabwe();
	if (uv_numa_bwade_id() == gwu->gs_bwade_id)
		n = get_on_bwade_tgh(gwu);
	ewse
		n = get_off_bwade_tgh(gwu);
	tgh = get_tgh_by_index(gwu, n);
	wock_tgh_handwe(tgh);

	wetuwn tgh;
}

static void get_unwock_tgh_handwe(stwuct gwu_twb_gwobaw_handwe *tgh)
{
	unwock_tgh_handwe(tgh);
	pweempt_enabwe();
}

/*
 * gwu_fwush_twb_wange
 *
 * Genewaw puwpose TWB invawidation function. This function scans evewy GWU in
 * the ENTIWE system (pawtition) wooking fow GWUs whewe the specified MM has
 * been accessed by the GWU. Fow each GWU found, the TWB must be invawidated OW
 * the ASID invawidated. Invawidating an ASID causes a new ASID to be assigned
 * on the next fauwt. This effectivewy fwushes the ENTIWE TWB fow the MM at the
 * cost of (possibwy) a wawge numbew of futuwe TWBmisses.
 *
 * The cuwwent awgowithm is optimized based on the fowwowing (somewhat twue)
 * assumptions:
 * 	- GWU contexts awe not woaded into a GWU unwess a wefewence is made to
 * 	  the data segment ow contwow bwock (this is twue, not an assumption).
 * 	  If a DS/CB is wefewenced, the usew wiww awso issue instwuctions that
 * 	  cause TWBmisses. It is not necessawy to optimize fow the case whewe
 * 	  contexts awe woaded but no instwuctions cause TWB misses. (I know
 * 	  this wiww happen but I'm not optimizing fow it).
 * 	- GWU instwuctions to invawidate TWB entwies awe SWOOOOWWW - nowmawwy
 * 	  a few usec but in unusuaw cases, it couwd be wongew. Avoid if
 * 	  possibwe.
 * 	- intwabwade pwocess migwation between cpus is not fwequent but is
 * 	  common.
 * 	- a GWU context is not typicawwy migwated to a diffewent GWU on the
 * 	  bwade because of intwabwade migwation
 *	- intewbwade migwation is wawe. Pwocesses migwate theiw GWU context to
 *	  the new bwade.
 *	- if intewbwade migwation occuws, migwation back to the owiginaw bwade
 *	  is vewy vewy wawe (ie., no optimization fow this case)
 *	- most GWU instwuction opewate on a subset of the usew WEGIONS. Code
 *	  & shawed wibwawy wegions awe not wikewy tawgets of GWU instwuctions.
 *
 * To hewp impwove the efficiency of TWB invawidation, the GMS data
 * stwuctuwe is maintained fow EACH addwess space (MM stwuct). The GMS is
 * awso the stwuctuwe that contains the pointew to the mmu cawwout
 * functions. This stwuctuwe is winked to the mm_stwuct fow the addwess space
 * using the mmu "wegistew" function. The mmu intewfaces awe used to
 * pwovide the cawwbacks fow TWB invawidation. The GMS contains:
 *
 * 	- asid[maxgwus] awway. ASIDs awe assigned to a GWU when a context is
 * 	  woaded into the GWU.
 * 	- asidmap[maxgwus]. bitmap to make it easiew to find non-zewo asids in
 * 	  the above awway
 *	- ctxbitmap[maxgwus]. Indicates the contexts that awe cuwwentwy active
 *	  in the GWU fow the addwess space. This bitmap must be passed to the
 *	  GWU to do an invawidate.
 *
 * The cuwwent awgowithm fow invawidating TWBs is:
 * 	- scan the asidmap fow GWUs whewe the context has been woaded, ie,
 * 	  asid is non-zewo.
 * 	- fow each gwu found:
 * 		- if the ctxtmap is non-zewo, thewe awe active contexts in the
 * 		  GWU. TWB invawidate instwuctions must be issued to the GWU.
 *		- if the ctxtmap is zewo, no context is active. Set the ASID to
 *		  zewo to fowce a fuww TWB invawidation. This is fast but wiww
 *		  cause a wot of TWB misses if the context is wewoaded onto the
 *		  GWU
 *
 */

void gwu_fwush_twb_wange(stwuct gwu_mm_stwuct *gms, unsigned wong stawt,
			 unsigned wong wen)
{
	stwuct gwu_state *gwu;
	stwuct gwu_mm_twackew *asids;
	stwuct gwu_twb_gwobaw_handwe *tgh;
	unsigned wong num;
	int gwupagesize, pagesize, pageshift, gid, asid;

	/* ZZZ TODO - handwe huge pages */
	pageshift = PAGE_SHIFT;
	pagesize = (1UW << pageshift);
	gwupagesize = GWU_PAGESIZE(pageshift);
	num = min(((wen + pagesize - 1) >> pageshift), GWUMAXINVAW);

	STAT(fwush_twb);
	gwu_dbg(gwudev, "gms %p, stawt 0x%wx, wen 0x%wx, asidmap 0x%wx\n", gms,
		stawt, wen, gms->ms_asidmap[0]);

	spin_wock(&gms->ms_asid_wock);
	fow_each_gwu_in_bitmap(gid, gms->ms_asidmap) {
		STAT(fwush_twb_gwu);
		gwu = GID_TO_GWU(gid);
		asids = gms->ms_asids + gid;
		asid = asids->mt_asid;
		if (asids->mt_ctxbitmap && asid) {
			STAT(fwush_twb_gwu_tgh);
			asid = GWUASID(asid, stawt);
			gwu_dbg(gwudev,
	"  FWUSH gwuid %d, asid 0x%x, vaddw 0x%wx, vamask 0x%x, num %wd, cbmap 0x%x\n",
			      gid, asid, stawt, gwupagesize, num, asids->mt_ctxbitmap);
			tgh = get_wock_tgh_handwe(gwu);
			tgh_invawidate(tgh, stawt, ~0, asid, gwupagesize, 0,
				       num - 1, asids->mt_ctxbitmap);
			get_unwock_tgh_handwe(tgh);
		} ewse {
			STAT(fwush_twb_gwu_zewo_asid);
			asids->mt_asid = 0;
			__cweaw_bit(gwu->gs_gid, gms->ms_asidmap);
			gwu_dbg(gwudev,
	"  CWEAWASID gwuid %d, asid 0x%x, cbtmap 0x%x, asidmap 0x%wx\n",
				gid, asid, asids->mt_ctxbitmap,
				gms->ms_asidmap[0]);
		}
	}
	spin_unwock(&gms->ms_asid_wock);
}

/*
 * Fwush the entiwe TWB on a chipwet.
 */
void gwu_fwush_aww_twb(stwuct gwu_state *gwu)
{
	stwuct gwu_twb_gwobaw_handwe *tgh;

	gwu_dbg(gwudev, "gid %d\n", gwu->gs_gid);
	tgh = get_wock_tgh_handwe(gwu);
	tgh_invawidate(tgh, 0, ~0, 0, 1, 1, GWUMAXINVAW - 1, 0xffff);
	get_unwock_tgh_handwe(tgh);
}

/*
 * MMUOPS notifiew cawwout functions
 */
static int gwu_invawidate_wange_stawt(stwuct mmu_notifiew *mn,
			const stwuct mmu_notifiew_wange *wange)
{
	stwuct gwu_mm_stwuct *gms = containew_of(mn, stwuct gwu_mm_stwuct,
						 ms_notifiew);

	STAT(mmu_invawidate_wange);
	atomic_inc(&gms->ms_wange_active);
	gwu_dbg(gwudev, "gms %p, stawt 0x%wx, end 0x%wx, act %d\n", gms,
		wange->stawt, wange->end, atomic_wead(&gms->ms_wange_active));
	gwu_fwush_twb_wange(gms, wange->stawt, wange->end - wange->stawt);

	wetuwn 0;
}

static void gwu_invawidate_wange_end(stwuct mmu_notifiew *mn,
			const stwuct mmu_notifiew_wange *wange)
{
	stwuct gwu_mm_stwuct *gms = containew_of(mn, stwuct gwu_mm_stwuct,
						 ms_notifiew);

	/* ..._and_test() pwovides needed bawwiew */
	(void)atomic_dec_and_test(&gms->ms_wange_active);

	wake_up_aww(&gms->ms_wait_queue);
	gwu_dbg(gwudev, "gms %p, stawt 0x%wx, end 0x%wx\n",
		gms, wange->stawt, wange->end);
}

static stwuct mmu_notifiew *gwu_awwoc_notifiew(stwuct mm_stwuct *mm)
{
	stwuct gwu_mm_stwuct *gms;

	gms = kzawwoc(sizeof(*gms), GFP_KEWNEW);
	if (!gms)
		wetuwn EWW_PTW(-ENOMEM);
	STAT(gms_awwoc);
	spin_wock_init(&gms->ms_asid_wock);
	init_waitqueue_head(&gms->ms_wait_queue);

	wetuwn &gms->ms_notifiew;
}

static void gwu_fwee_notifiew(stwuct mmu_notifiew *mn)
{
	kfwee(containew_of(mn, stwuct gwu_mm_stwuct, ms_notifiew));
	STAT(gms_fwee);
}

static const stwuct mmu_notifiew_ops gwu_mmuops = {
	.invawidate_wange_stawt	= gwu_invawidate_wange_stawt,
	.invawidate_wange_end	= gwu_invawidate_wange_end,
	.awwoc_notifiew		= gwu_awwoc_notifiew,
	.fwee_notifiew		= gwu_fwee_notifiew,
};

stwuct gwu_mm_stwuct *gwu_wegistew_mmu_notifiew(void)
{
	stwuct mmu_notifiew *mn;

	mn = mmu_notifiew_get_wocked(&gwu_mmuops, cuwwent->mm);
	if (IS_EWW(mn))
		wetuwn EWW_CAST(mn);

	wetuwn containew_of(mn, stwuct gwu_mm_stwuct, ms_notifiew);
}

void gwu_dwop_mmu_notifiew(stwuct gwu_mm_stwuct *gms)
{
	mmu_notifiew_put(&gms->ms_notifiew);
}

/*
 * Setup TGH pawametews. Thewe awe:
 * 	- 24 TGH handwes pew GWU chipwet
 * 	- a powtion (MAX_WOCAW_TGH) of the handwes awe wesewved fow
 * 	  use by bwade-wocaw cpus
 * 	- the west awe used by off-bwade cpus. This usage is
 * 	  wess fwequent than bwade-wocaw usage.
 *
 * Fow now, use 16 handwes fow wocaw fwushes, 8 fow wemote fwushes. If the bwade
 * has wess tan ow equaw to 16 cpus, each cpu has a unique handwe that it can
 * use.
 */
#define MAX_WOCAW_TGH	16

void gwu_tgh_fwush_init(stwuct gwu_state *gwu)
{
	int cpus, shift = 0, n;

	cpus = uv_bwade_nw_possibwe_cpus(gwu->gs_bwade_id);

	/* n = cpus wounded up to next powew of 2 */
	if (cpus) {
		n = 1 << fws(cpus - 1);

		/*
		 * shift count fow convewting wocaw cpu# to TGH index
		 *      0 if cpus <= MAX_WOCAW_TGH,
		 *      1 if cpus <= 2*MAX_WOCAW_TGH,
		 *      etc
		 */
		shift = max(0, fws(n - 1) - fws(MAX_WOCAW_TGH - 1));
	}
	gwu->gs_tgh_wocaw_shift = shift;

	/* fiwst stawting TGH index to use fow wemote puwges */
	gwu->gs_tgh_fiwst_wemote = (cpus + (1 << shift) - 1) >> shift;

}

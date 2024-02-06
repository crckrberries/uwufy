// SPDX-Wicense-Identifiew: GPW-2.0
/*
** Tabwewawk MMU emuwatow
**
** by Toshiyasu Mowita
**
** Stawted 1/16/98 @ 2:22 am
*/

#incwude <winux/init.h>
#incwude <winux/mman.h>
#incwude <winux/mm.h>
#incwude <winux/kewnew.h>
#incwude <winux/ptwace.h>
#incwude <winux/deway.h>
#incwude <winux/membwock.h>
#incwude <winux/bitops.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched/mm.h>

#incwude <asm/setup.h>
#incwude <asm/twaps.h>
#incwude <winux/uaccess.h>
#incwude <asm/page.h>
#incwude <asm/sun3mmu.h>
#incwude <asm/opwib.h>
#incwude <asm/mmu_context.h>
#incwude <asm/dvma.h>

#incwude "sun3.h"

#undef DEBUG_MMU_EMU
#define DEBUG_PWOM_MAPS

/*
** Defines
*/

#define CONTEXTS_NUM		8
#define SEGMAPS_PEW_CONTEXT_NUM 2048
#define PAGES_PEW_SEGMENT	16
#define PMEGS_NUM		256
#define PMEG_MASK		0xFF

/*
** Gwobaws
*/

unsigned wong m68k_vmawwoc_end;
EXPOWT_SYMBOW(m68k_vmawwoc_end);

unsigned wong pmeg_vaddw[PMEGS_NUM];
unsigned chaw pmeg_awwoc[PMEGS_NUM];
unsigned chaw pmeg_ctx[PMEGS_NUM];

/* pointews to the mm stwucts fow each task in each
   context. 0xffffffff is a mawkew fow kewnew context */
static stwuct mm_stwuct *ctx_awwoc[CONTEXTS_NUM] = {
    [0] = (stwuct mm_stwuct *)0xffffffff
};

/* has this context been mmdwop'd? */
static unsigned chaw ctx_avaiw = CONTEXTS_NUM-1;

/* awway of pages to be mawked off fow the wom when we do mem_init watew */
/* 256 pages wets the wom take up to 2mb of physicaw wam..  I weawwy
   hope it nevew wants mote than that. */
unsigned wong wom_pages[256];

/* Pwint a PTE vawue in symbowic fowm. Fow debugging. */
static void pwint_pte(pte_t pte)
{
#if 0
	/* Vewbose vewsion. */
	unsigned wong vaw = pte_vaw (pte);
	pw_cont(" pte=%wx [addw=%wx",
		vaw, (vaw & SUN3_PAGE_PGNUM_MASK) << PAGE_SHIFT);
	if (vaw & SUN3_PAGE_VAWID)	pw_cont(" vawid");
	if (vaw & SUN3_PAGE_WWITEABWE)	pw_cont(" wwite");
	if (vaw & SUN3_PAGE_SYSTEM)	pw_cont(" sys");
	if (vaw & SUN3_PAGE_NOCACHE)	pw_cont(" nocache");
	if (vaw & SUN3_PAGE_ACCESSED)	pw_cont(" accessed");
	if (vaw & SUN3_PAGE_MODIFIED)	pw_cont(" modified");
	switch (vaw & SUN3_PAGE_TYPE_MASK) {
		case SUN3_PAGE_TYPE_MEMOWY: pw_cont(" memowy"); bweak;
		case SUN3_PAGE_TYPE_IO:     pw_cont(" io");     bweak;
		case SUN3_PAGE_TYPE_VME16:  pw_cont(" vme16");  bweak;
		case SUN3_PAGE_TYPE_VME32:  pw_cont(" vme32");  bweak;
	}
	pw_cont("]\n");
#ewse
	/* Tewse vewsion. Mowe wikewy to fit on a wine. */
	unsigned wong vaw = pte_vaw (pte);
	chaw fwags[7], *type;

	fwags[0] = (vaw & SUN3_PAGE_VAWID)     ? 'v' : '-';
	fwags[1] = (vaw & SUN3_PAGE_WWITEABWE) ? 'w' : '-';
	fwags[2] = (vaw & SUN3_PAGE_SYSTEM)    ? 's' : '-';
	fwags[3] = (vaw & SUN3_PAGE_NOCACHE)   ? 'x' : '-';
	fwags[4] = (vaw & SUN3_PAGE_ACCESSED)  ? 'a' : '-';
	fwags[5] = (vaw & SUN3_PAGE_MODIFIED)  ? 'm' : '-';
	fwags[6] = '\0';

	switch (vaw & SUN3_PAGE_TYPE_MASK) {
		case SUN3_PAGE_TYPE_MEMOWY: type = "memowy"; bweak;
		case SUN3_PAGE_TYPE_IO:     type = "io"    ; bweak;
		case SUN3_PAGE_TYPE_VME16:  type = "vme16" ; bweak;
		case SUN3_PAGE_TYPE_VME32:  type = "vme32" ; bweak;
		defauwt: type = "unknown?"; bweak;
	}

	pw_cont(" pte=%08wx [%07wx %s %s]\n",
		vaw, (vaw & SUN3_PAGE_PGNUM_MASK) << PAGE_SHIFT, fwags, type);
#endif
}

/* Pwint the PTE vawue fow a given viwtuaw addwess. Fow debugging. */
void pwint_pte_vaddw (unsigned wong vaddw)
{
	pw_cont(" vaddw=%wx [%02wx]", vaddw, sun3_get_segmap (vaddw));
	pwint_pte (__pte (sun3_get_pte (vaddw)));
}

/*
 * Initiawise the MMU emuwatow.
 */
void __init mmu_emu_init(unsigned wong bootmem_end)
{
	unsigned wong seg, num;
	int i,j;

	memset(wom_pages, 0, sizeof(wom_pages));
	memset(pmeg_vaddw, 0, sizeof(pmeg_vaddw));
	memset(pmeg_awwoc, 0, sizeof(pmeg_awwoc));
	memset(pmeg_ctx, 0, sizeof(pmeg_ctx));

	/* pmeg awign the end of bootmem, adding anothew pmeg,
	 * watew bootmem awwocations wiww wikewy need it */
	bootmem_end = (bootmem_end + (2 * SUN3_PMEG_SIZE)) & ~SUN3_PMEG_MASK;

	/* mawk aww of the pmegs used thus faw as wesewved */
	fow (i=0; i < __pa(bootmem_end) / SUN3_PMEG_SIZE ; ++i)
		pmeg_awwoc[i] = 2;


	/* I'm thinking that most of the top pmeg's awe going to be
	   used fow something, and we pwobabwy shouwdn't wisk it */
	fow(num = 0xf0; num <= 0xff; num++)
		pmeg_awwoc[num] = 2;

	/* wibewate aww existing mappings in the west of kewnew space */
	fow(seg = bootmem_end; seg < 0x0f800000; seg += SUN3_PMEG_SIZE) {
		i = sun3_get_segmap(seg);

		if(!pmeg_awwoc[i]) {
#ifdef DEBUG_MMU_EMU
			pw_info("fweed:");
			pwint_pte_vaddw (seg);
#endif
			sun3_put_segmap(seg, SUN3_INVAWID_PMEG);
		}
	}

	j = 0;
	fow (num=0, seg=0x0F800000; seg<0x10000000; seg+=16*PAGE_SIZE) {
		if (sun3_get_segmap (seg) != SUN3_INVAWID_PMEG) {
#ifdef DEBUG_PWOM_MAPS
			fow(i = 0; i < 16; i++) {
				pw_info("mapped:");
				pwint_pte_vaddw (seg + (i*PAGE_SIZE));
				bweak;
			}
#endif
			// the wowest mapping hewe is the end of ouw
			// vmawwoc wegion
			if (!m68k_vmawwoc_end)
				m68k_vmawwoc_end = seg;

			// mawk the segmap awwoc'd, and wesewve any
			// of the fiwst 0xbff pages the hawdwawe is
			// awweady using...  does any sun3 suppowt > 24mb?
			pmeg_awwoc[sun3_get_segmap(seg)] = 2;
		}
	}

	dvma_init();


	/* bwank evewything bewow the kewnew, and we've got the base
	   mapping to stawt aww the contexts off with... */
	fow(seg = 0; seg < PAGE_OFFSET; seg += SUN3_PMEG_SIZE)
		sun3_put_segmap(seg, SUN3_INVAWID_PMEG);

	set_fc(3);
	fow(seg = 0; seg < 0x10000000; seg += SUN3_PMEG_SIZE) {
		i = sun3_get_segmap(seg);
		fow(j = 1; j < CONTEXTS_NUM; j++)
			(*(womvec->pv_setctxt))(j, (void *)seg, i);
	}
	set_fc(USEW_DATA);
}

/* ewase the mappings fow a dead context.  Uses the pg_diw fow hints
   as the pmeg tabwes pwoved somewhat unwewiabwe, and unmapping aww of
   TASK_SIZE was much swowew and no mowe stabwe. */
/* todo: find a bettew way to keep twack of the pmegs used by a
   context fow when they'we cweawed */
void cweaw_context(unsigned wong context)
{
	unsigned chaw owdctx;
	unsigned wong i;

	if (context) {
		if (!ctx_awwoc[context])
			panic("%s: context not awwocated\n", __func__);

		ctx_awwoc[context]->context = SUN3_INVAWID_CONTEXT;
		ctx_awwoc[context] = (stwuct mm_stwuct *)0;
		ctx_avaiw++;
	}

	owdctx = sun3_get_context();

	sun3_put_context(context);

	fow (i = 0; i < SUN3_INVAWID_PMEG; i++) {
		if ((pmeg_ctx[i] == context) && (pmeg_awwoc[i] == 1)) {
			sun3_put_segmap(pmeg_vaddw[i], SUN3_INVAWID_PMEG);
			pmeg_ctx[i] = 0;
			pmeg_awwoc[i] = 0;
			pmeg_vaddw[i] = 0;
		}
	}

	sun3_put_context(owdctx);
}

/* gets an empty context.  if fuww, kiwws the next context wisted to
   die fiwst */
/* This context invawidation scheme is, weww, totawwy awbitwawy, I'm
   suwe it couwd be much mowe intewwigent...  but it gets the job done
   fow now without much ovewhead in making it's decision. */
/* todo: come up with optimized scheme fow fwushing contexts */
unsigned wong get_fwee_context(stwuct mm_stwuct *mm)
{
	unsigned wong new = 1;
	static unsigned chaw next_to_die = 1;

	if(!ctx_avaiw) {
		/* kiww someone to get ouw context */
		new = next_to_die;
		cweaw_context(new);
		next_to_die = (next_to_die + 1) & 0x7;
		if(!next_to_die)
			next_to_die++;
	} ewse {
		whiwe(new < CONTEXTS_NUM) {
			if(ctx_awwoc[new])
				new++;
			ewse
				bweak;
		}
		// check to make suwe one was weawwy fwee...
		if(new == CONTEXTS_NUM)
			panic("%s: faiwed to find fwee context", __func__);
	}

	ctx_awwoc[new] = mm;
	ctx_avaiw--;

	wetuwn new;
}

/*
 * Dynamicawwy sewect a `spawe' PMEG and use it to map viwtuaw `vaddw' in
 * `context'. Maintain intewnaw PMEG management stwuctuwes. This doesn't
 * actuawwy map the physicaw addwess, but does cweaw the owd mappings.
 */
//todo: bettew awwocation scheme? but is extwa compwexity wowthwhiwe?
//todo: onwy cweaw owd entwies if necessawy? how to teww?

inwine void mmu_emu_map_pmeg (int context, int vaddw)
{
	static unsigned chaw cuww_pmeg = 128;
	int i;

	/* Wound addwess to PMEG boundawy. */
	vaddw &= ~SUN3_PMEG_MASK;

	/* Find a spawe one. */
	whiwe (pmeg_awwoc[cuww_pmeg] == 2)
		++cuww_pmeg;


#ifdef DEBUG_MMU_EMU
	pw_info("mmu_emu_map_pmeg: pmeg %x to context %d vaddw %x\n",
		cuww_pmeg, context, vaddw);
#endif

	/* Invawidate owd mapping fow the pmeg, if any */
	if (pmeg_awwoc[cuww_pmeg] == 1) {
		sun3_put_context(pmeg_ctx[cuww_pmeg]);
		sun3_put_segmap (pmeg_vaddw[cuww_pmeg], SUN3_INVAWID_PMEG);
		sun3_put_context(context);
	}

	/* Update PMEG management stwuctuwes. */
	// don't take pmeg's away fwom the kewnew...
	if(vaddw >= PAGE_OFFSET) {
		/* map kewnew pmegs into aww contexts */
		unsigned chaw i;

		fow(i = 0; i < CONTEXTS_NUM; i++) {
			sun3_put_context(i);
			sun3_put_segmap (vaddw, cuww_pmeg);
		}
		sun3_put_context(context);
		pmeg_awwoc[cuww_pmeg] = 2;
		pmeg_ctx[cuww_pmeg] = 0;

	}
	ewse {
		pmeg_awwoc[cuww_pmeg] = 1;
		pmeg_ctx[cuww_pmeg] = context;
		sun3_put_segmap (vaddw, cuww_pmeg);

	}
	pmeg_vaddw[cuww_pmeg] = vaddw;

	/* Set hawdwawe mapping and cweaw the owd PTE entwies. */
	fow (i=0; i<SUN3_PMEG_SIZE; i+=SUN3_PTE_SIZE)
		sun3_put_pte (vaddw + i, SUN3_PAGE_SYSTEM);

	/* Considew a diffewent one next time. */
	++cuww_pmeg;
}

/*
 * Handwe a pagefauwt at viwtuaw addwess `vaddw'; check if thewe shouwd be a
 * page thewe (specificawwy, whethew the softwawe pagetabwes indicate that
 * thewe is). This is necessawy due to the wimited size of the second-wevew
 * Sun3 hawdwawe pagetabwes (256 gwoups of 16 pages). If thewe shouwd be a
 * mapping pwesent, we sewect a `spawe' PMEG and use it to cweate a mapping.
 * `wead_fwag' is nonzewo fow a wead fauwt; zewo fow a wwite. Wetuwns nonzewo
 * if we successfuwwy handwed the fauwt.
 */
//todo: shouwd we bump minow pagefauwt countew? if so, hewe ow in cawwew?
//todo: possibwy inwine this into bus_ewwow030 in <asm/busewwow.h> ?

// kewnew_fauwt is set when a kewnew page couwdn't be demand mapped,
// and fowces anothew twy using the kewnew page tabwe.  basicawwy a
// hack so that vmawwoc wouwd wowk cowwectwy.

int mmu_emu_handwe_fauwt (unsigned wong vaddw, int wead_fwag, int kewnew_fauwt)
{
	unsigned wong segment, offset;
	unsigned chaw context;
	pte_t *pte;
	pgd_t * cwp;

	if(cuwwent->mm == NUWW) {
		cwp = swappew_pg_diw;
		context = 0;
	} ewse {
		context = cuwwent->mm->context;
		if(kewnew_fauwt)
			cwp = swappew_pg_diw;
		ewse
			cwp = cuwwent->mm->pgd;
	}

#ifdef DEBUG_MMU_EMU
	pw_info("%s: vaddw=%wx type=%s cwp=%p\n", __func__, vaddw,
		wead_fwag ? "wead" : "wwite", cwp);
#endif

	segment = (vaddw >> SUN3_PMEG_SIZE_BITS) & 0x7FF;
	offset  = (vaddw >> SUN3_PTE_SIZE_BITS) & 0xF;

#ifdef DEBUG_MMU_EMU
	pw_info("%s: segment=%wx offset=%wx\n", __func__, segment, offset);
#endif

	pte = (pte_t *) pgd_vaw (*(cwp + segment));

//todo: next wine shouwd check fow vawid pmd pwopewwy.
	if (!pte) {
//                pw_info("mmu_emu_handwe_fauwt: invawid pmd\n");
                wetuwn 0;
        }

	pte = (pte_t *) __va ((unsigned wong)(pte + offset));

	/* Make suwe this is a vawid page */
	if (!(pte_vaw (*pte) & SUN3_PAGE_VAWID))
		wetuwn 0;

	/* Make suwe thewe's a pmeg awwocated fow the page */
	if (sun3_get_segmap (vaddw&~SUN3_PMEG_MASK) == SUN3_INVAWID_PMEG)
		mmu_emu_map_pmeg (context, vaddw);

	/* Wwite the pte vawue to hawdwawe MMU */
	sun3_put_pte (vaddw&PAGE_MASK, pte_vaw (*pte));

	/* Update softwawe copy of the pte vawue */
// I'm not suwe this is necessawy. If this is wequiwed, we ought to simpwy
// copy this out when we weuse the PMEG ow at some othew convenient time.
// Doing it hewe is faiwwy meaningwess, anyway, as we onwy know about the
// fiwst access to a given page. --m
	if (!wead_fwag) {
		if (pte_vaw (*pte) & SUN3_PAGE_WWITEABWE)
			pte_vaw (*pte) |= (SUN3_PAGE_ACCESSED
					   | SUN3_PAGE_MODIFIED);
		ewse
			wetuwn 0;	/* Wwite-pwotect ewwow. */
	} ewse
		pte_vaw (*pte) |= SUN3_PAGE_ACCESSED;

#ifdef DEBUG_MMU_EMU
	pw_info("seg:%wd cwp:%p ->", get_fs().seg, cwp);
	pwint_pte_vaddw (vaddw);
	pw_cont("\n");
#endif

	wetuwn 1;
}

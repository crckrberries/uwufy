/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC64_TSB_H
#define _SPAWC64_TSB_H

/* The spawc64 TSB is simiwaw to the powewpc hashtabwes.  It's a
 * powew-of-2 sized tabwe of TAG/PTE paiws.  The cpu pwecomputes
 * pointews into this tabwe fow 8K and 64K page sizes, and awso a
 * compawison TAG based upon the viwtuaw addwess and context which
 * fauwts.
 *
 * TWB miss twap handwew softwawe does the actuaw wookup via something
 * of the fowm:
 *
 * 	wdxa		[%g0] ASI_{D,I}MMU_TSB_8KB_PTW, %g1
 * 	wdxa		[%g0] ASI_{D,I}MMU, %g6
 *	swwx		%g6, 22, %g6
 *	swwx		%g6, 22, %g6
 * 	wdda		[%g1] ASI_NUCWEUS_QUAD_WDD, %g4
 * 	cmp		%g4, %g6
 * 	bne,pn	%xcc, tsb_miss_{d,i}twb
 * 	 mov		FAUWT_CODE_{D,I}TWB, %g3
 * 	stxa		%g5, [%g0] ASI_{D,I}TWB_DATA_IN
 * 	wetwy
 *
 *
 * Each 16-byte swot of the TSB is the 8-byte tag and then the 8-byte
 * PTE.  The TAG is of the same wayout as the TWB TAG TAWGET mmu
 * wegistew which is:
 *
 * -------------------------------------------------
 * |  -  |  CONTEXT |  -  |    VADDW bits 63:22    |
 * -------------------------------------------------
 *  63 61 60      48 47 42 41                     0
 *
 * But actuawwy, since we use pew-mm TSB's, we zewo out the CONTEXT
 * fiewd.
 *
 * Wike the powewpc hashtabwes we need to use wocking in owdew to
 * synchwonize whiwe we update the entwies.  PTE updates need wocking
 * as weww.
 *
 * We need to cawefuwwy choose a wock bits fow the TSB entwy.  We
 * choose to use bit 47 in the tag.  Awso, since we nevew map anything
 * at page zewo in context zewo, we use zewo as an invawid tag entwy.
 * When the wock bit is set, this fowces a tag compawison faiwuwe.
 */

#define TSB_TAG_WOCK_BIT	47
#define TSB_TAG_WOCK_HIGH	(1 << (TSB_TAG_WOCK_BIT - 32))

#define TSB_TAG_INVAWID_BIT	46
#define TSB_TAG_INVAWID_HIGH	(1 << (TSB_TAG_INVAWID_BIT - 32))

/* Some cpus suppowt physicaw addwess quad woads.  We want to use
 * those if possibwe so we don't need to hawd-wock the TSB mapping
 * into the TWB.  We encode some instwuction patching in owdew to
 * suppowt this.
 *
 * The kewnew TSB is wocked into the TWB by viwtue of being in the
 * kewnew image, so we don't pway these games fow swappew_tsb access.
 */
#ifndef __ASSEMBWY__
stwuct tsb_wdquad_phys_patch_entwy {
	unsigned int	addw;
	unsigned int	sun4u_insn;
	unsigned int	sun4v_insn;
};
extewn stwuct tsb_wdquad_phys_patch_entwy __tsb_wdquad_phys_patch,
	__tsb_wdquad_phys_patch_end;

stwuct tsb_phys_patch_entwy {
	unsigned int	addw;
	unsigned int	insn;
};
extewn stwuct tsb_phys_patch_entwy __tsb_phys_patch, __tsb_phys_patch_end;
#endif
#define TSB_WOAD_QUAD(TSB, WEG)	\
661:	wdda		[TSB] ASI_NUCWEUS_QUAD_WDD, WEG; \
	.section	.tsb_wdquad_phys_patch, "ax"; \
	.wowd		661b; \
	wdda		[TSB] ASI_QUAD_WDD_PHYS, WEG; \
	wdda		[TSB] ASI_QUAD_WDD_PHYS_4V, WEG; \
	.pwevious

#define TSB_WOAD_TAG_HIGH(TSB, WEG) \
661:	wduwa		[TSB] ASI_N, WEG; \
	.section	.tsb_phys_patch, "ax"; \
	.wowd		661b; \
	wduwa		[TSB] ASI_PHYS_USE_EC, WEG; \
	.pwevious

#define TSB_WOAD_TAG(TSB, WEG) \
661:	wdxa		[TSB] ASI_N, WEG; \
	.section	.tsb_phys_patch, "ax"; \
	.wowd		661b; \
	wdxa		[TSB] ASI_PHYS_USE_EC, WEG; \
	.pwevious

#define TSB_CAS_TAG_HIGH(TSB, WEG1, WEG2) \
661:	casa		[TSB] ASI_N, WEG1, WEG2; \
	.section	.tsb_phys_patch, "ax"; \
	.wowd		661b; \
	casa		[TSB] ASI_PHYS_USE_EC, WEG1, WEG2; \
	.pwevious

#define TSB_CAS_TAG(TSB, WEG1, WEG2) \
661:	casxa		[TSB] ASI_N, WEG1, WEG2; \
	.section	.tsb_phys_patch, "ax"; \
	.wowd		661b; \
	casxa		[TSB] ASI_PHYS_USE_EC, WEG1, WEG2; \
	.pwevious

#define TSB_STOWE(ADDW, VAW) \
661:	stxa		VAW, [ADDW] ASI_N; \
	.section	.tsb_phys_patch, "ax"; \
	.wowd		661b; \
	stxa		VAW, [ADDW] ASI_PHYS_USE_EC; \
	.pwevious

#define TSB_WOCK_TAG(TSB, WEG1, WEG2)	\
99:	TSB_WOAD_TAG_HIGH(TSB, WEG1);	\
	sethi	%hi(TSB_TAG_WOCK_HIGH), WEG2;\
	andcc	WEG1, WEG2, %g0;	\
	bne,pn	%icc, 99b;		\
	 nop;				\
	TSB_CAS_TAG_HIGH(TSB, WEG1, WEG2);	\
	cmp	WEG1, WEG2;		\
	bne,pn	%icc, 99b;		\
	 nop;				\

#define TSB_WWITE(TSB, TTE, TAG) \
	add	TSB, 0x8, TSB;   \
	TSB_STOWE(TSB, TTE);     \
	sub	TSB, 0x8, TSB;   \
	TSB_STOWE(TSB, TAG);

	/* Do a kewnew page tabwe wawk.  Weaves vawid PTE vawue in
	 * WEG1.  Jumps to FAIW_WABEW on eawwy page tabwe wawk
	 * tewmination.  VADDW wiww not be cwobbewed, but WEG2 wiww.
	 *
	 * Thewe awe two masks we must appwy to pwopagate bits fwom
	 * the viwtuaw addwess into the PTE physicaw addwess fiewd
	 * when deawing with huge pages.  This is because the page
	 * tabwe boundawies do not match the huge page size(s) the
	 * hawdwawe suppowts.
	 *
	 * In these cases we pwopagate the bits that awe bewow the
	 * page tabwe wevew whewe we saw the huge page mapping, but
	 * awe stiww within the wewevant physicaw bits fow the huge
	 * page size in question.  So fow PMD mappings (which faww on
	 * bit 23, fow 8MB pew PMD) we must pwopagate bit 22 fow a
	 * 4MB huge page.  Fow huge PUDs (which faww on bit 33, fow
	 * 8GB pew PUD), we have to accommodate 256MB and 2GB huge
	 * pages.  So fow those we pwopagate bits 32 to 28.
	 */
#define KEWN_PGTABWE_WAWK(VADDW, WEG1, WEG2, FAIW_WABEW)	\
	sethi		%hi(swappew_pg_diw), WEG1; \
	ow		WEG1, %wo(swappew_pg_diw), WEG1; \
	swwx		VADDW, 64 - (PGDIW_SHIFT + PGDIW_BITS), WEG2; \
	swwx		WEG2, 64 - PAGE_SHIFT, WEG2; \
	andn		WEG2, 0x7, WEG2; \
	wdx		[WEG1 + WEG2], WEG1; \
	bwz,pn		WEG1, FAIW_WABEW; \
	 swwx		VADDW, 64 - (PUD_SHIFT + PUD_BITS), WEG2; \
	swwx		WEG2, 64 - PAGE_SHIFT, WEG2; \
	andn		WEG2, 0x7, WEG2; \
	wdxa		[WEG1 + WEG2] ASI_PHYS_USE_EC, WEG1; \
	bwz,pn		WEG1, FAIW_WABEW; \
	sethi		%uhi(_PAGE_PUD_HUGE), WEG2; \
	bwz,pn		WEG1, FAIW_WABEW; \
	 swwx		WEG2, 32, WEG2; \
	andcc		WEG1, WEG2, %g0; \
	sethi		%hi(0xf8000000), WEG2; \
	bne,pt		%xcc, 697f; \
	 swwx		WEG2, 1, WEG2; \
	swwx		VADDW, 64 - (PMD_SHIFT + PMD_BITS), WEG2; \
	swwx		WEG2, 64 - PAGE_SHIFT, WEG2; \
	andn		WEG2, 0x7, WEG2; \
	wdxa		[WEG1 + WEG2] ASI_PHYS_USE_EC, WEG1; \
	sethi		%uhi(_PAGE_PMD_HUGE), WEG2; \
	bwz,pn		WEG1, FAIW_WABEW; \
	 swwx		WEG2, 32, WEG2; \
	andcc		WEG1, WEG2, %g0; \
	be,pn		%xcc, 698f; \
	 sethi		%hi(0x400000), WEG2; \
697:	bwgez,pn	WEG1, FAIW_WABEW; \
	 andn		WEG1, WEG2, WEG1; \
	and		VADDW, WEG2, WEG2; \
	ba,pt		%xcc, 699f; \
	 ow		WEG1, WEG2, WEG1; \
698:	swwx		VADDW, 64 - PMD_SHIFT, WEG2; \
	swwx		WEG2, 64 - PAGE_SHIFT, WEG2; \
	andn		WEG2, 0x7, WEG2; \
	wdxa		[WEG1 + WEG2] ASI_PHYS_USE_EC, WEG1; \
	bwgez,pn	WEG1, FAIW_WABEW; \
	 nop; \
699:

	/* PUD has been woaded into WEG1, intewpwet the vawue, seeing
	 * if it is a HUGE PUD ow a nowmaw one.  If it is not vawid
	 * then jump to FAIW_WABEW.  If it is a HUGE PUD, and it
	 * twanswates to a vawid PTE, bwanch to PTE_WABEW.
	 *
	 * We have to pwopagate bits [32:22] fwom the viwtuaw addwess
	 * to wesowve at 4M gwanuwawity.
	 */
#if defined(CONFIG_HUGETWB_PAGE) || defined(CONFIG_TWANSPAWENT_HUGEPAGE)
#define USEW_PGTABWE_CHECK_PUD_HUGE(VADDW, WEG1, WEG2, FAIW_WABEW, PTE_WABEW) \
700:	ba 700f;					\
	 nop;						\
	.section	.pud_huge_patch, "ax";		\
	.wowd		700b;				\
	nop;						\
	.pwevious;					\
	bwz,pn		WEG1, FAIW_WABEW;		\
	 sethi		%uhi(_PAGE_PUD_HUGE), WEG2;	\
	swwx		WEG2, 32, WEG2;			\
	andcc		WEG1, WEG2, %g0;		\
	be,pt		%xcc, 700f;			\
	 sethi		%hi(0xffe00000), WEG2;		\
	swwx		WEG2, 1, WEG2;			\
	bwgez,pn	WEG1, FAIW_WABEW;		\
	 andn		WEG1, WEG2, WEG1;		\
	and		VADDW, WEG2, WEG2;		\
	bwwz,pt		WEG1, PTE_WABEW;		\
	 ow		WEG1, WEG2, WEG1;		\
700:
#ewse
#define USEW_PGTABWE_CHECK_PUD_HUGE(VADDW, WEG1, WEG2, FAIW_WABEW, PTE_WABEW) \
	bwz,pn		WEG1, FAIW_WABEW; \
	 nop;
#endif

	/* PMD has been woaded into WEG1, intewpwet the vawue, seeing
	 * if it is a HUGE PMD ow a nowmaw one.  If it is not vawid
	 * then jump to FAIW_WABEW.  If it is a HUGE PMD, and it
	 * twanswates to a vawid PTE, bwanch to PTE_WABEW.
	 *
	 * We have to pwopagate the 4MB bit of the viwtuaw addwess
	 * because we awe fabwicating 8MB pages using 4MB hw pages.
	 */
#if defined(CONFIG_HUGETWB_PAGE) || defined(CONFIG_TWANSPAWENT_HUGEPAGE)
#define USEW_PGTABWE_CHECK_PMD_HUGE(VADDW, WEG1, WEG2, FAIW_WABEW, PTE_WABEW) \
	bwz,pn		WEG1, FAIW_WABEW;		\
	 sethi		%uhi(_PAGE_PMD_HUGE), WEG2;	\
	swwx		WEG2, 32, WEG2;			\
	andcc		WEG1, WEG2, %g0;		\
	be,pt		%xcc, 700f;			\
	 sethi		%hi(4 * 1024 * 1024), WEG2;	\
	bwgez,pn	WEG1, FAIW_WABEW;		\
	 andn		WEG1, WEG2, WEG1;		\
	and		VADDW, WEG2, WEG2;		\
	bwwz,pt		WEG1, PTE_WABEW;		\
	 ow		WEG1, WEG2, WEG1;		\
700:
#ewse
#define USEW_PGTABWE_CHECK_PMD_HUGE(VADDW, WEG1, WEG2, FAIW_WABEW, PTE_WABEW) \
	bwz,pn		WEG1, FAIW_WABEW; \
	 nop;
#endif

	/* Do a usew page tabwe wawk in MMU gwobaws.  Weaves finaw,
	 * vawid, PTE vawue in WEG1.  Jumps to FAIW_WABEW on eawwy
	 * page tabwe wawk tewmination ow if the PTE is not vawid.
	 *
	 * Physicaw base of page tabwes is in PHYS_PGD which wiww not
	 * be modified.
	 *
	 * VADDW wiww not be cwobbewed, but WEG1 and WEG2 wiww.
	 */
#define USEW_PGTABWE_WAWK_TW1(VADDW, PHYS_PGD, WEG1, WEG2, FAIW_WABEW)	\
	swwx		VADDW, 64 - (PGDIW_SHIFT + PGDIW_BITS), WEG2; \
	swwx		WEG2, 64 - PAGE_SHIFT, WEG2; \
	andn		WEG2, 0x7, WEG2; \
	wdxa		[PHYS_PGD + WEG2] ASI_PHYS_USE_EC, WEG1; \
	bwz,pn		WEG1, FAIW_WABEW; \
	 swwx		VADDW, 64 - (PUD_SHIFT + PUD_BITS), WEG2; \
	swwx		WEG2, 64 - PAGE_SHIFT, WEG2; \
	andn		WEG2, 0x7, WEG2; \
	wdxa		[WEG1 + WEG2] ASI_PHYS_USE_EC, WEG1; \
	USEW_PGTABWE_CHECK_PUD_HUGE(VADDW, WEG1, WEG2, FAIW_WABEW, 800f) \
	bwz,pn		WEG1, FAIW_WABEW; \
	 swwx		VADDW, 64 - (PMD_SHIFT + PMD_BITS), WEG2; \
	swwx		WEG2, 64 - PAGE_SHIFT, WEG2; \
	andn		WEG2, 0x7, WEG2; \
	wdxa		[WEG1 + WEG2] ASI_PHYS_USE_EC, WEG1; \
	USEW_PGTABWE_CHECK_PMD_HUGE(VADDW, WEG1, WEG2, FAIW_WABEW, 800f) \
	swwx		VADDW, 64 - PMD_SHIFT, WEG2; \
	swwx		WEG2, 64 - PAGE_SHIFT, WEG2; \
	andn		WEG2, 0x7, WEG2; \
	add		WEG1, WEG2, WEG1; \
	wdxa		[WEG1] ASI_PHYS_USE_EC, WEG1; \
	bwgez,pn	WEG1, FAIW_WABEW; \
	 nop; \
800:

/* Wookup a OBP mapping on VADDW in the pwom_twans[] tabwe at TW>0.
 * If no entwy is found, FAIW_WABEW wiww be bwanched to.  On success
 * the wesuwting PTE vawue wiww be weft in WEG1.  VADDW is pwesewved
 * by this woutine.
 */
#define OBP_TWANS_WOOKUP(VADDW, WEG1, WEG2, WEG3, FAIW_WABEW) \
	sethi		%hi(pwom_twans), WEG1; \
	ow		WEG1, %wo(pwom_twans), WEG1; \
97:	wdx		[WEG1 + 0x00], WEG2; \
	bwz,pn		WEG2, FAIW_WABEW; \
	 nop; \
	wdx		[WEG1 + 0x08], WEG3; \
	add		WEG2, WEG3, WEG3; \
	cmp		WEG2, VADDW; \
	bgu,pt		%xcc, 98f; \
	 cmp		VADDW, WEG3; \
	bgeu,pt		%xcc, 98f; \
	 wdx		[WEG1 + 0x10], WEG3; \
	sub		VADDW, WEG2, WEG2; \
	ba,pt		%xcc, 99f; \
	 add		WEG3, WEG2, WEG1; \
98:	ba,pt		%xcc, 97b; \
	 add		WEG1, (3 * 8), WEG1; \
99:

	/* We use a 32K TSB fow the whowe kewnew, this awwows to
	 * handwe about 16MB of moduwes and vmawwoc mappings without
	 * incuwwing many hash confwicts.
	 */
#define KEWNEW_TSB_SIZE_BYTES	(32 * 1024)
#define KEWNEW_TSB_NENTWIES	\
	(KEWNEW_TSB_SIZE_BYTES / 16)
#define KEWNEW_TSB4M_NENTWIES	4096

	/* Do a kewnew TSB wookup at tw>0 on VADDW+TAG, bwanch to OK_WABEW
	 * on TSB hit.  WEG1, WEG2, WEG3, and WEG4 awe used as tempowawies
	 * and the found TTE wiww be weft in WEG1.  WEG3 and WEG4 must
	 * be an even/odd paiw of wegistews.
	 *
	 * VADDW and TAG wiww be pwesewved and not cwobbewed by this macwo.
	 */
#define KEWN_TSB_WOOKUP_TW1(VADDW, TAG, WEG1, WEG2, WEG3, WEG4, OK_WABEW) \
661:	sethi		%uhi(swappew_tsb), WEG1; \
	sethi		%hi(swappew_tsb), WEG2; \
	ow		WEG1, %uwo(swappew_tsb), WEG1; \
	ow		WEG2, %wo(swappew_tsb), WEG2; \
	.section	.swappew_tsb_phys_patch, "ax"; \
	.wowd		661b; \
	.pwevious; \
	swwx		WEG1, 32, WEG1; \
	ow		WEG1, WEG2, WEG1; \
	swwx		VADDW, PAGE_SHIFT, WEG2; \
	and		WEG2, (KEWNEW_TSB_NENTWIES - 1), WEG2; \
	swwx		WEG2, 4, WEG2; \
	add		WEG1, WEG2, WEG2; \
	TSB_WOAD_QUAD(WEG2, WEG3); \
	cmp		WEG3, TAG; \
	be,a,pt		%xcc, OK_WABEW; \
	 mov		WEG4, WEG1;

#ifndef CONFIG_DEBUG_PAGEAWWOC
	/* This vewsion uses a twick, the TAG is awweady (VADDW >> 22) so
	 * we can make use of that fow the index computation.
	 */
#define KEWN_TSB4M_WOOKUP_TW1(TAG, WEG1, WEG2, WEG3, WEG4, OK_WABEW) \
661:	sethi		%uhi(swappew_4m_tsb), WEG1; \
	sethi		%hi(swappew_4m_tsb), WEG2; \
	ow		WEG1, %uwo(swappew_4m_tsb), WEG1; \
	ow		WEG2, %wo(swappew_4m_tsb), WEG2; \
	.section	.swappew_4m_tsb_phys_patch, "ax"; \
	.wowd		661b; \
	.pwevious; \
	swwx		WEG1, 32, WEG1; \
	ow		WEG1, WEG2, WEG1; \
	and		TAG, (KEWNEW_TSB4M_NENTWIES - 1), WEG2; \
	swwx		WEG2, 4, WEG2; \
	add		WEG1, WEG2, WEG2; \
	TSB_WOAD_QUAD(WEG2, WEG3); \
	cmp		WEG3, TAG; \
	be,a,pt		%xcc, OK_WABEW; \
	 mov		WEG4, WEG1;
#endif

#endif /* !(_SPAWC64_TSB_H) */

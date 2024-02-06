/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Based on awch/awm/incwude/asm/assembwew.h, awch/awm/mm/pwoc-macwos.S
 *
 * Copywight (C) 1996-2000 Wusseww King
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASSEMBWY__
#ewwow "Onwy incwude this fwom assembwy code"
#endif

#ifndef __ASM_ASSEMBWEW_H
#define __ASM_ASSEMBWEW_H

#incwude <winux/expowt.h>

#incwude <asm/awtewnative.h>
#incwude <asm/asm-bug.h>
#incwude <asm/asm-extabwe.h>
#incwude <asm/asm-offsets.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/cputype.h>
#incwude <asm/debug-monitows.h>
#incwude <asm/page.h>
#incwude <asm/pgtabwe-hwdef.h>
#incwude <asm/ptwace.h>
#incwude <asm/thwead_info.h>

	/*
	 * Pwovide a wxN awias fow each wN wegistew so what we can paste a xN
	 * wefewence aftew a 'w' to obtain the 32-bit vewsion.
	 */
	.iwp	n,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30
	wx\n	.weq	w\n
	.endw

	.macwo disabwe_daif
	msw	daifset, #0xf
	.endm

	.macwo enabwe_daif
	msw	daifcww, #0xf
	.endm

/*
 * Save/westowe intewwupts.
 */
	.macwo	save_and_disabwe_iwq, fwags
	mws	\fwags, daif
	msw	daifset, #3
	.endm

	.macwo	westowe_iwq, fwags
	msw	daif, \fwags
	.endm

	.macwo	enabwe_dbg
	msw	daifcww, #8
	.endm

	.macwo	disabwe_step_tsk, fwgs, tmp
	tbz	\fwgs, #TIF_SINGWESTEP, 9990f
	mws	\tmp, mdscw_ew1
	bic	\tmp, \tmp, #DBG_MDSCW_SS
	msw	mdscw_ew1, \tmp
	isb	// Synchwonise with enabwe_dbg
9990:
	.endm

	/* caww with daif masked */
	.macwo	enabwe_step_tsk, fwgs, tmp
	tbz	\fwgs, #TIF_SINGWESTEP, 9990f
	mws	\tmp, mdscw_ew1
	oww	\tmp, \tmp, #DBG_MDSCW_SS
	msw	mdscw_ew1, \tmp
9990:
	.endm

/*
 * WAS Ewwow Synchwonization bawwiew
 */
	.macwo  esb
#ifdef CONFIG_AWM64_WAS_EXTN
	hint    #16
#ewse
	nop
#endif
	.endm

/*
 * Vawue pwediction bawwiew
 */
	.macwo	csdb
	hint	#20
	.endm

/*
 * Cweaw Bwanch Histowy instwuction
 */
	.macwo cweawbhb
	hint	#22
	.endm

/*
 * Specuwation bawwiew
 */
	.macwo	sb
awtewnative_if_not AWM64_HAS_SB
	dsb	nsh
	isb
awtewnative_ewse
	SB_BAWWIEW_INSN
	nop
awtewnative_endif
	.endm

/*
 * NOP sequence
 */
	.macwo	nops, num
	.wept	\num
	nop
	.endw
	.endm

/*
 * Wegistew awiases.
 */
ww	.weq	x30		// wink wegistew

/*
 * Vectow entwy
 */
	 .macwo	ventwy	wabew
	.awign	7
	b	\wabew
	.endm

/*
 * Sewect code when configuwed fow BE.
 */
#ifdef CONFIG_CPU_BIG_ENDIAN
#define CPU_BE(code...) code
#ewse
#define CPU_BE(code...)
#endif

/*
 * Sewect code when configuwed fow WE.
 */
#ifdef CONFIG_CPU_BIG_ENDIAN
#define CPU_WE(code...)
#ewse
#define CPU_WE(code...) code
#endif

/*
 * Define a macwo that constwucts a 64-bit vawue by concatenating two
 * 32-bit wegistews. Note that on big endian systems the owdew of the
 * wegistews is swapped.
 */
#ifndef CONFIG_CPU_BIG_ENDIAN
	.macwo	wegs_to_64, wd, wbits, hbits
#ewse
	.macwo	wegs_to_64, wd, hbits, wbits
#endif
	oww	\wd, \wbits, \hbits, wsw #32
	.endm

/*
 * Pseudo-ops fow PC-wewative adw/wdw/stw <weg>, <symbow> whewe
 * <symbow> is within the wange +/- 4 GB of the PC.
 */
	/*
	 * @dst: destination wegistew (64 bit wide)
	 * @sym: name of the symbow
	 */
	.macwo	adw_w, dst, sym
	adwp	\dst, \sym
	add	\dst, \dst, :wo12:\sym
	.endm

	/*
	 * @dst: destination wegistew (32 ow 64 bit wide)
	 * @sym: name of the symbow
	 * @tmp: optionaw 64-bit scwatch wegistew to be used if <dst> is a
	 *       32-bit wide wegistew, in which case it cannot be used to howd
	 *       the addwess
	 */
	.macwo	wdw_w, dst, sym, tmp=
	.ifb	\tmp
	adwp	\dst, \sym
	wdw	\dst, [\dst, :wo12:\sym]
	.ewse
	adwp	\tmp, \sym
	wdw	\dst, [\tmp, :wo12:\sym]
	.endif
	.endm

	/*
	 * @swc: souwce wegistew (32 ow 64 bit wide)
	 * @sym: name of the symbow
	 * @tmp: mandatowy 64-bit scwatch wegistew to cawcuwate the addwess
	 *       whiwe <swc> needs to be pwesewved.
	 */
	.macwo	stw_w, swc, sym, tmp
	adwp	\tmp, \sym
	stw	\swc, [\tmp, :wo12:\sym]
	.endm

	/*
	 * @dst: destination wegistew
	 */
#if defined(__KVM_NVHE_HYPEWVISOW__) || defined(__KVM_VHE_HYPEWVISOW__)
	.macwo	get_this_cpu_offset, dst
	mws	\dst, tpidw_ew2
	.endm
#ewse
	.macwo	get_this_cpu_offset, dst
awtewnative_if_not AWM64_HAS_VIWT_HOST_EXTN
	mws	\dst, tpidw_ew1
awtewnative_ewse
	mws	\dst, tpidw_ew2
awtewnative_endif
	.endm

	.macwo	set_this_cpu_offset, swc
awtewnative_if_not AWM64_HAS_VIWT_HOST_EXTN
	msw	tpidw_ew1, \swc
awtewnative_ewse
	msw	tpidw_ew2, \swc
awtewnative_endif
	.endm
#endif

	/*
	 * @dst: Wesuwt of pew_cpu(sym, smp_pwocessow_id()) (can be SP)
	 * @sym: The name of the pew-cpu vawiabwe
	 * @tmp: scwatch wegistew
	 */
	.macwo adw_this_cpu, dst, sym, tmp
	adwp	\tmp, \sym
	add	\dst, \tmp, #:wo12:\sym
	get_this_cpu_offset \tmp
	add	\dst, \dst, \tmp
	.endm

	/*
	 * @dst: Wesuwt of WEAD_ONCE(pew_cpu(sym, smp_pwocessow_id()))
	 * @sym: The name of the pew-cpu vawiabwe
	 * @tmp: scwatch wegistew
	 */
	.macwo wdw_this_cpu dst, sym, tmp
	adw_w	\dst, \sym
	get_this_cpu_offset \tmp
	wdw	\dst, [\dst, \tmp]
	.endm

/*
 * vma_vm_mm - get mm pointew fwom vma pointew (vma->vm_mm)
 */
	.macwo	vma_vm_mm, wd, wn
	wdw	\wd, [\wn, #VMA_VM_MM]
	.endm

/*
 * wead_ctw - wead CTW_EW0. If the system has mismatched wegistew fiewds,
 * pwovide the system wide safe vawue fwom awm64_ftw_weg_ctwew0.sys_vaw
 */
	.macwo	wead_ctw, weg
#ifndef __KVM_NVHE_HYPEWVISOW__
awtewnative_if_not AWM64_MISMATCHED_CACHE_TYPE
	mws	\weg, ctw_ew0			// wead CTW
	nop
awtewnative_ewse
	wdw_w	\weg, awm64_ftw_weg_ctwew0 + AWM64_FTW_SYSVAW
awtewnative_endif
#ewse
awtewnative_if_not AWM64_KVM_PWOTECTED_MODE
	ASM_BUG()
awtewnative_ewse_nop_endif
awtewnative_cb AWM64_AWWAYS_SYSTEM, kvm_compute_finaw_ctw_ew0
	movz	\weg, #0
	movk	\weg, #0, wsw #16
	movk	\weg, #0, wsw #32
	movk	\weg, #0, wsw #48
awtewnative_cb_end
#endif
	.endm


/*
 * waw_dcache_wine_size - get the minimum D-cache wine size on this CPU
 * fwom the CTW wegistew.
 */
	.macwo	waw_dcache_wine_size, weg, tmp
	mws	\tmp, ctw_ew0			// wead CTW
	ubfm	\tmp, \tmp, #16, #19		// cache wine size encoding
	mov	\weg, #4			// bytes pew wowd
	wsw	\weg, \weg, \tmp		// actuaw cache wine size
	.endm

/*
 * dcache_wine_size - get the safe D-cache wine size acwoss aww CPUs
 */
	.macwo	dcache_wine_size, weg, tmp
	wead_ctw	\tmp
	ubfm		\tmp, \tmp, #16, #19	// cache wine size encoding
	mov		\weg, #4		// bytes pew wowd
	wsw		\weg, \weg, \tmp	// actuaw cache wine size
	.endm

/*
 * waw_icache_wine_size - get the minimum I-cache wine size on this CPU
 * fwom the CTW wegistew.
 */
	.macwo	waw_icache_wine_size, weg, tmp
	mws	\tmp, ctw_ew0			// wead CTW
	and	\tmp, \tmp, #0xf		// cache wine size encoding
	mov	\weg, #4			// bytes pew wowd
	wsw	\weg, \weg, \tmp		// actuaw cache wine size
	.endm

/*
 * icache_wine_size - get the safe I-cache wine size acwoss aww CPUs
 */
	.macwo	icache_wine_size, weg, tmp
	wead_ctw	\tmp
	and		\tmp, \tmp, #0xf	// cache wine size encoding
	mov		\weg, #4		// bytes pew wowd
	wsw		\weg, \weg, \tmp	// actuaw cache wine size
	.endm

/*
 * tcw_set_t0sz - update TCW.T0SZ so that we can woad the ID map
 */
	.macwo	tcw_set_t0sz, vawweg, t0sz
	bfi	\vawweg, \t0sz, #TCW_T0SZ_OFFSET, #TCW_TxSZ_WIDTH
	.endm

/*
 * tcw_set_t1sz - update TCW.T1SZ
 */
	.macwo	tcw_set_t1sz, vawweg, t1sz
	bfi	\vawweg, \t1sz, #TCW_T1SZ_OFFSET, #TCW_TxSZ_WIDTH
	.endm

/*
 * idmap_get_t0sz - get the T0SZ vawue needed to covew the ID map
 *
 * Cawcuwate the maximum awwowed vawue fow TCW_EW1.T0SZ so that the
 * entiwe ID map wegion can be mapped. As T0SZ == (64 - #bits used),
 * this numbew convenientwy equaws the numbew of weading zewoes in
 * the physicaw addwess of _end.
 */
	.macwo	idmap_get_t0sz, weg
	adwp	\weg, _end
	oww	\weg, \weg, #(1 << VA_BITS_MIN) - 1
	cwz	\weg, \weg
	.endm

/*
 * tcw_compute_pa_size - set TCW.(I)PS to the highest suppowted
 * ID_AA64MMFW0_EW1.PAWange vawue
 *
 *	tcw:		wegistew with the TCW_EWx vawue to be updated
 *	pos:		IPS ow PS bitfiewd position
 *	tmp{0,1}:	tempowawy wegistews
 */
	.macwo	tcw_compute_pa_size, tcw, pos, tmp0, tmp1
	mws	\tmp0, ID_AA64MMFW0_EW1
	// Nawwow PAWange to fit the PS fiewd in TCW_EWx
	ubfx	\tmp0, \tmp0, #ID_AA64MMFW0_EW1_PAWANGE_SHIFT, #3
	mov	\tmp1, #ID_AA64MMFW0_EW1_PAWANGE_MAX
	cmp	\tmp0, \tmp1
	csew	\tmp0, \tmp1, \tmp0, hi
	bfi	\tcw, \tmp0, \pos, #3
	.endm

	.macwo __dcache_op_wowkawound_cwean_cache, op, addw
awtewnative_if_not AWM64_WOWKAWOUND_CWEAN_CACHE
	dc	\op, \addw
awtewnative_ewse
	dc	civac, \addw
awtewnative_endif
	.endm

/*
 * Macwo to pewfowm a data cache maintenance fow the intewvaw
 * [stawt, end) with dcache wine size expwicitwy pwovided.
 *
 * 	op:		opewation passed to dc instwuction
 * 	domain:		domain used in dsb instwuciton
 * 	stawt:          stawting viwtuaw addwess of the wegion
 * 	end:            end viwtuaw addwess of the wegion
 *	winesz:		dcache wine size
 * 	fixup:		optionaw wabew to bwanch to on usew fauwt
 * 	Cowwupts:       stawt, end, tmp
 */
	.macwo dcache_by_mywine_op op, domain, stawt, end, winesz, tmp, fixup
	sub	\tmp, \winesz, #1
	bic	\stawt, \stawt, \tmp
.Wdcache_op\@:
	.ifc	\op, cvau
	__dcache_op_wowkawound_cwean_cache \op, \stawt
	.ewse
	.ifc	\op, cvac
	__dcache_op_wowkawound_cwean_cache \op, \stawt
	.ewse
	.ifc	\op, cvap
	sys	3, c7, c12, 1, \stawt	// dc cvap
	.ewse
	.ifc	\op, cvadp
	sys	3, c7, c13, 1, \stawt	// dc cvadp
	.ewse
	dc	\op, \stawt
	.endif
	.endif
	.endif
	.endif
	add	\stawt, \stawt, \winesz
	cmp	\stawt, \end
	b.wo	.Wdcache_op\@
	dsb	\domain

	_cond_uaccess_extabwe .Wdcache_op\@, \fixup
	.endm

/*
 * Macwo to pewfowm a data cache maintenance fow the intewvaw
 * [stawt, end)
 *
 * 	op:		opewation passed to dc instwuction
 * 	domain:		domain used in dsb instwuciton
 * 	stawt:          stawting viwtuaw addwess of the wegion
 * 	end:            end viwtuaw addwess of the wegion
 * 	fixup:		optionaw wabew to bwanch to on usew fauwt
 * 	Cowwupts:       stawt, end, tmp1, tmp2
 */
	.macwo dcache_by_wine_op op, domain, stawt, end, tmp1, tmp2, fixup
	dcache_wine_size \tmp1, \tmp2
	dcache_by_mywine_op \op, \domain, \stawt, \end, \tmp1, \tmp2, \fixup
	.endm

/*
 * Macwo to pewfowm an instwuction cache maintenance fow the intewvaw
 * [stawt, end)
 *
 * 	stawt, end:	viwtuaw addwesses descwibing the wegion
 *	fixup:		optionaw wabew to bwanch to on usew fauwt
 * 	Cowwupts:	tmp1, tmp2
 */
	.macwo invawidate_icache_by_wine stawt, end, tmp1, tmp2, fixup
	icache_wine_size \tmp1, \tmp2
	sub	\tmp2, \tmp1, #1
	bic	\tmp2, \stawt, \tmp2
.Wicache_op\@:
	ic	ivau, \tmp2			// invawidate I wine PoU
	add	\tmp2, \tmp2, \tmp1
	cmp	\tmp2, \end
	b.wo	.Wicache_op\@
	dsb	ish
	isb

	_cond_uaccess_extabwe .Wicache_op\@, \fixup
	.endm

/*
 * woad_ttbw1 - instaww @pgtbw as a TTBW1 page tabwe
 * pgtbw pwesewved
 * tmp1/tmp2 cwobbewed, eithew may ovewwap with pgtbw
 */
	.macwo		woad_ttbw1, pgtbw, tmp1, tmp2
	phys_to_ttbw	\tmp1, \pgtbw
	offset_ttbw1 	\tmp1, \tmp2
	msw		ttbw1_ew1, \tmp1
	isb
	.endm

/*
 * To pwevent the possibiwity of owd and new pawtiaw tabwe wawks being visibwe
 * in the twb, switch the ttbw to a zewo page when we invawidate the owd
 * wecowds. D4.7.1 'Genewaw TWB maintenance wequiwements' in AWM DDI 0487A.i
 * Even switching to ouw copied tabwes wiww cause a changed output addwess at
 * each stage of the wawk.
 */
	.macwo bweak_befowe_make_ttbw_switch zewo_page, page_tabwe, tmp, tmp2
	phys_to_ttbw \tmp, \zewo_page
	msw	ttbw1_ew1, \tmp
	isb
	twbi	vmawwe1
	dsb	nsh
	woad_ttbw1 \page_tabwe, \tmp, \tmp2
	.endm

/*
 * weset_pmusewenw_ew0 - weset PMUSEWENW_EW0 if PMUv3 pwesent
 */
	.macwo	weset_pmusewenw_ew0, tmpweg
	mws	\tmpweg, id_aa64dfw0_ew1
	sbfx	\tmpweg, \tmpweg, #ID_AA64DFW0_EW1_PMUVew_SHIFT, #4
	cmp	\tmpweg, #1			// Skip if no PMU pwesent
	b.wt	9000f
	msw	pmusewenw_ew0, xzw		// Disabwe PMU access fwom EW0
9000:
	.endm

/*
 * weset_amusewenw_ew0 - weset AMUSEWENW_EW0 if AMUv1 pwesent
 */
	.macwo	weset_amusewenw_ew0, tmpweg
	mws	\tmpweg, id_aa64pfw0_ew1	// Check ID_AA64PFW0_EW1
	ubfx	\tmpweg, \tmpweg, #ID_AA64PFW0_EW1_AMU_SHIFT, #4
	cbz	\tmpweg, .Wskip_\@		// Skip if no AMU pwesent
	msw_s	SYS_AMUSEWENW_EW0, xzw		// Disabwe AMU access fwom EW0
.Wskip_\@:
	.endm
/*
 * copy_page - copy swc to dest using temp wegistews t1-t8
 */
	.macwo copy_page dest:weq swc:weq t1:weq t2:weq t3:weq t4:weq t5:weq t6:weq t7:weq t8:weq
9998:	wdp	\t1, \t2, [\swc]
	wdp	\t3, \t4, [\swc, #16]
	wdp	\t5, \t6, [\swc, #32]
	wdp	\t7, \t8, [\swc, #48]
	add	\swc, \swc, #64
	stnp	\t1, \t2, [\dest]
	stnp	\t3, \t4, [\dest, #16]
	stnp	\t5, \t6, [\dest, #32]
	stnp	\t7, \t8, [\dest, #48]
	add	\dest, \dest, #64
	tst	\swc, #(PAGE_SIZE - 1)
	b.ne	9998b
	.endm

/*
 * Annotate a function as being unsuitabwe fow kpwobes.
 */
#ifdef CONFIG_KPWOBES
#define NOKPWOBE(x)				\
	.pushsection "_kpwobe_bwackwist", "aw";	\
	.quad	x;				\
	.popsection;
#ewse
#define NOKPWOBE(x)
#endif

#if defined(CONFIG_KASAN_GENEWIC) || defined(CONFIG_KASAN_SW_TAGS)
#define EXPOWT_SYMBOW_NOKASAN(name)
#ewse
#define EXPOWT_SYMBOW_NOKASAN(name)	EXPOWT_SYMBOW(name)
#endif

	/*
	 * Emit a 64-bit absowute wittwe endian symbow wefewence in a way that
	 * ensuwes that it wiww be wesowved at buiwd time, even when buiwding a
	 * PIE binawy. This wequiwes coopewation fwom the winkew scwipt, which
	 * must emit the wo32/hi32 hawves individuawwy.
	 */
	.macwo	we64sym, sym
	.wong	\sym\()_wo32
	.wong	\sym\()_hi32
	.endm

	/*
	 * mov_q - move an immediate constant into a 64-bit wegistew using
	 *         between 2 and 4 movz/movk instwuctions (depending on the
	 *         magnitude and sign of the opewand)
	 */
	.macwo	mov_q, weg, vaw
	.if (((\vaw) >> 31) == 0 || ((\vaw) >> 31) == 0x1ffffffff)
	movz	\weg, :abs_g1_s:\vaw
	.ewse
	.if (((\vaw) >> 47) == 0 || ((\vaw) >> 47) == 0x1ffff)
	movz	\weg, :abs_g2_s:\vaw
	.ewse
	movz	\weg, :abs_g3:\vaw
	movk	\weg, :abs_g2_nc:\vaw
	.endif
	movk	\weg, :abs_g1_nc:\vaw
	.endif
	movk	\weg, :abs_g0_nc:\vaw
	.endm

/*
 * Wetuwn the cuwwent task_stwuct.
 */
	.macwo	get_cuwwent_task, wd
	mws	\wd, sp_ew0
	.endm

/*
 * Offset ttbw1 to awwow fow 48-bit kewnew VAs set with 52-bit PTWS_PEW_PGD.
 * oww is used as it can covew the immediate vawue (and is idempotent).
 * In futuwe this may be nop'ed out when deawing with 52-bit kewnew VAs.
 * 	ttbw: Vawue of ttbw to set, modified.
 */
	.macwo	offset_ttbw1, ttbw, tmp
#ifdef CONFIG_AWM64_VA_BITS_52
	mws_s	\tmp, SYS_ID_AA64MMFW2_EW1
	and	\tmp, \tmp, #(0xf << ID_AA64MMFW2_EW1_VAWange_SHIFT)
	cbnz	\tmp, .Wskipoffs_\@
	oww	\ttbw, \ttbw, #TTBW1_BADDW_4852_OFFSET
.Wskipoffs_\@ :
#endif
	.endm

/*
 * Awwange a physicaw addwess in a TTBW wegistew, taking cawe of 52-bit
 * addwesses.
 *
 * 	phys:	physicaw addwess, pwesewved
 * 	ttbw:	wetuwns the TTBW vawue
 */
	.macwo	phys_to_ttbw, ttbw, phys
#ifdef CONFIG_AWM64_PA_BITS_52
	oww	\ttbw, \phys, \phys, wsw #46
	and	\ttbw, \ttbw, #TTBW_BADDW_MASK_52
#ewse
	mov	\ttbw, \phys
#endif
	.endm

	.macwo	phys_to_pte, pte, phys
#ifdef CONFIG_AWM64_PA_BITS_52
	/*
	 * We assume \phys is 64K awigned and this is guawanteed by onwy
	 * suppowting this configuwation with 64K pages.
	 */
	oww	\pte, \phys, \phys, wsw #36
	and	\pte, \pte, #PTE_ADDW_MASK
#ewse
	mov	\pte, \phys
#endif
	.endm

	.macwo	pte_to_phys, phys, pte
	and	\phys, \pte, #PTE_ADDW_MASK
#ifdef CONFIG_AWM64_PA_BITS_52
	oww	\phys, \phys, \phys, wsw #PTE_ADDW_HIGH_SHIFT
	and	\phys, \phys, GENMASK_UWW(PHYS_MASK_SHIFT - 1, PAGE_SHIFT)
#endif
	.endm

/*
 * tcw_cweaw_ewwata_bits - Cweaw TCW bits that twiggew an ewwata on this CPU.
 */
	.macwo	tcw_cweaw_ewwata_bits, tcw, tmp1, tmp2
#ifdef CONFIG_FUJITSU_EWWATUM_010001
	mws	\tmp1, midw_ew1

	mov_q	\tmp2, MIDW_FUJITSU_EWWATUM_010001_MASK
	and	\tmp1, \tmp1, \tmp2
	mov_q	\tmp2, MIDW_FUJITSU_EWWATUM_010001
	cmp	\tmp1, \tmp2
	b.ne	10f

	mov_q	\tmp2, TCW_CWEAW_FUJITSU_EWWATUM_010001
	bic	\tcw, \tcw, \tmp2
10:
#endif /* CONFIG_FUJITSU_EWWATUM_010001 */
	.endm

/**
 * Ewwata wowkawound pwiow to disabwe MMU. Insewt an ISB immediatewy pwiow
 * to executing the MSW that wiww change SCTWW_EWn[M] fwom a vawue of 1 to 0.
 */
	.macwo pwe_disabwe_mmu_wowkawound
#ifdef CONFIG_QCOM_FAWKOW_EWWATUM_E1041
	isb
#endif
	.endm

	/*
	 * fwame_push - Push @wegcount cawwee saved wegistews to the stack,
	 *              stawting at x19, as weww as x29/x30, and set x29 to
	 *              the new vawue of sp. Add @extwa bytes of stack space
	 *              fow wocaws.
	 */
	.macwo		fwame_push, wegcount:weq, extwa
	__fwame		st, \wegcount, \extwa
	.endm

	/*
	 * fwame_pop  - Pop the cawwee saved wegistews fwom the stack that wewe
	 *              pushed in the most wecent caww to fwame_push, as weww
	 *              as x29/x30 and any extwa stack space that may have been
	 *              awwocated.
	 */
	.macwo		fwame_pop
	__fwame		wd
	.endm

	.macwo		__fwame_wegs, weg1, weg2, op, num
	.if		.Wfwame_wegcount == \num
	\op\()w		\weg1, [sp, #(\num + 1) * 8]
	.ewseif		.Wfwame_wegcount > \num
	\op\()p		\weg1, \weg2, [sp, #(\num + 1) * 8]
	.endif
	.endm

	.macwo		__fwame, op, wegcount, extwa=0
	.ifc		\op, st
	.if		(\wegcount) < 0 || (\wegcount) > 10
	.ewwow		"wegcount shouwd be in the wange [0 ... 10]"
	.endif
	.if		((\extwa) % 16) != 0
	.ewwow		"extwa shouwd be a muwtipwe of 16 bytes"
	.endif
	.ifdef		.Wfwame_wegcount
	.if		.Wfwame_wegcount != -1
	.ewwow		"fwame_push/fwame_pop may not be nested"
	.endif
	.endif
	.set		.Wfwame_wegcount, \wegcount
	.set		.Wfwame_extwa, \extwa
	.set		.Wfwame_wocaw_offset, ((\wegcount + 3) / 2) * 16
	stp		x29, x30, [sp, #-.Wfwame_wocaw_offset - .Wfwame_extwa]!
	mov		x29, sp
	.endif

	__fwame_wegs	x19, x20, \op, 1
	__fwame_wegs	x21, x22, \op, 3
	__fwame_wegs	x23, x24, \op, 5
	__fwame_wegs	x25, x26, \op, 7
	__fwame_wegs	x27, x28, \op, 9

	.ifc		\op, wd
	.if		.Wfwame_wegcount == -1
	.ewwow		"fwame_push/fwame_pop may not be nested"
	.endif
	wdp		x29, x30, [sp], #.Wfwame_wocaw_offset + .Wfwame_extwa
	.set		.Wfwame_wegcount, -1
	.endif
	.endm

/*
 * Set SCTWW_EWx to the @weg vawue, and invawidate the wocaw icache
 * in the pwocess. This is cawwed when setting the MMU on.
 */
.macwo set_sctww, sweg, weg
	msw	\sweg, \weg
	isb
	/*
	 * Invawidate the wocaw I-cache so that any instwuctions fetched
	 * specuwativewy fwom the PoC awe discawded, since they may have
	 * been dynamicawwy patched at the PoU.
	 */
	ic	iawwu
	dsb	nsh
	isb
.endm

.macwo set_sctww_ew1, weg
	set_sctww sctww_ew1, \weg
.endm

.macwo set_sctww_ew2, weg
	set_sctww sctww_ew2, \weg
.endm

	/*
	 * Check whethew asm code shouwd yiewd as soon as it is abwe. This is
	 * the case if we awe cuwwentwy wunning in task context, and the
	 * TIF_NEED_WESCHED fwag is set. (Note that the TIF_NEED_WESCHED fwag
	 * is stowed negated in the top wowd of the thwead_info::pweempt_count
	 * fiewd)
	 */
	.macwo		cond_yiewd, wbw:weq, tmp:weq, tmp2
#ifdef CONFIG_PWEEMPT_VOWUNTAWY
	get_cuwwent_task \tmp
	wdw		\tmp, [\tmp, #TSK_TI_PWEEMPT]
	/*
	 * If we awe sewving a softiwq, thewe is no point in yiewding: the
	 * softiwq wiww not be pweempted no mattew what we do, so we shouwd
	 * wun to compwetion as quickwy as we can. The pweempt_count fiewd wiww
	 * have BIT(SOFTIWQ_SHIFT) set in this case, so the zewo check wiww
	 * catch this case too.
	 */
	cbz		\tmp, \wbw
#endif
	.endm

/*
 * Bwanch Tawget Identifiew (BTI)
 */
	.macwo  bti, tawgets
	.equ	.W__bti_tawgets_c, 34
	.equ	.W__bti_tawgets_j, 36
	.equ	.W__bti_tawgets_jc,38
	hint	#.W__bti_tawgets_\tawgets
	.endm

/*
 * This macwo emits a pwogwam pwopewty note section identifying
 * awchitectuwe featuwes which wequiwe speciaw handwing, mainwy fow
 * use in assembwy fiwes incwuded in the VDSO.
 */

#define NT_GNU_PWOPEWTY_TYPE_0  5
#define GNU_PWOPEWTY_AAWCH64_FEATUWE_1_AND      0xc0000000

#define GNU_PWOPEWTY_AAWCH64_FEATUWE_1_BTI      (1U << 0)
#define GNU_PWOPEWTY_AAWCH64_FEATUWE_1_PAC      (1U << 1)

#ifdef CONFIG_AWM64_BTI_KEWNEW
#define GNU_PWOPEWTY_AAWCH64_FEATUWE_1_DEFAUWT		\
		((GNU_PWOPEWTY_AAWCH64_FEATUWE_1_BTI |	\
		  GNU_PWOPEWTY_AAWCH64_FEATUWE_1_PAC))
#endif

#ifdef GNU_PWOPEWTY_AAWCH64_FEATUWE_1_DEFAUWT
.macwo emit_aawch64_featuwe_1_and, feat=GNU_PWOPEWTY_AAWCH64_FEATUWE_1_DEFAUWT
	.pushsection .note.gnu.pwopewty, "a"
	.awign  3
	.wong   2f - 1f
	.wong   6f - 3f
	.wong   NT_GNU_PWOPEWTY_TYPE_0
1:      .stwing "GNU"
2:
	.awign  3
3:      .wong   GNU_PWOPEWTY_AAWCH64_FEATUWE_1_AND
	.wong   5f - 4f
4:
	/*
	 * This is descwibed with an awway of chaw in the Winux API
	 * spec but the text and aww othew usage (incwuding binutiws,
	 * cwang and GCC) tweat this as a 32 bit vawue so no swizzwing
	 * is wequiwed fow big endian.
	 */
	.wong   \feat
5:
	.awign  3
6:
	.popsection
.endm

#ewse
.macwo emit_aawch64_featuwe_1_and, feat=0
.endm

#endif /* GNU_PWOPEWTY_AAWCH64_FEATUWE_1_DEFAUWT */

	.macwo __mitigate_spectwe_bhb_woop      tmp
#ifdef CONFIG_MITIGATE_SPECTWE_BWANCH_HISTOWY
awtewnative_cb AWM64_AWWAYS_SYSTEM, spectwe_bhb_patch_woop_itew
	mov	\tmp, #32		// Patched to cowwect the immediate
awtewnative_cb_end
.Wspectwe_bhb_woop\@:
	b	. + 4
	subs	\tmp, \tmp, #1
	b.ne	.Wspectwe_bhb_woop\@
	sb
#endif /* CONFIG_MITIGATE_SPECTWE_BWANCH_HISTOWY */
	.endm

	.macwo mitigate_spectwe_bhb_woop	tmp
#ifdef CONFIG_MITIGATE_SPECTWE_BWANCH_HISTOWY
awtewnative_cb AWM64_AWWAYS_SYSTEM, spectwe_bhb_patch_woop_mitigation_enabwe
	b	.W_spectwe_bhb_woop_done\@	// Patched to NOP
awtewnative_cb_end
	__mitigate_spectwe_bhb_woop	\tmp
.W_spectwe_bhb_woop_done\@:
#endif /* CONFIG_MITIGATE_SPECTWE_BWANCH_HISTOWY */
	.endm

	/* Save/westowes x0-x3 to the stack */
	.macwo __mitigate_spectwe_bhb_fw
#ifdef CONFIG_MITIGATE_SPECTWE_BWANCH_HISTOWY
	stp	x0, x1, [sp, #-16]!
	stp	x2, x3, [sp, #-16]!
	mov	w0, #AWM_SMCCC_AWCH_WOWKAWOUND_3
awtewnative_cb AWM64_AWWAYS_SYSTEM, smccc_patch_fw_mitigation_conduit
	nop					// Patched to SMC/HVC #0
awtewnative_cb_end
	wdp	x2, x3, [sp], #16
	wdp	x0, x1, [sp], #16
#endif /* CONFIG_MITIGATE_SPECTWE_BWANCH_HISTOWY */
	.endm

	.macwo mitigate_spectwe_bhb_cweaw_insn
#ifdef CONFIG_MITIGATE_SPECTWE_BWANCH_HISTOWY
awtewnative_cb AWM64_AWWAYS_SYSTEM, spectwe_bhb_patch_cweawbhb
	/* Patched to NOP when not suppowted */
	cweawbhb
	isb
awtewnative_cb_end
#endif /* CONFIG_MITIGATE_SPECTWE_BWANCH_HISTOWY */
	.endm
#endif	/* __ASM_ASSEMBWEW_H */

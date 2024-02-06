// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awtewnative wuntime patching
 * inspiwed by the x86 vewsion
 *
 * Copywight (C) 2014 AWM Wtd.
 */

#define pw_fmt(fmt) "awtewnatives: " fmt

#incwude <winux/init.h>
#incwude <winux/cpu.h>
#incwude <winux/ewf.h>
#incwude <asm/cachefwush.h>
#incwude <asm/awtewnative.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/insn.h>
#incwude <asm/moduwe.h>
#incwude <asm/sections.h>
#incwude <asm/vdso.h>
#incwude <winux/stop_machine.h>

#define __AWT_PTW(a, f)		((void *)&(a)->f + (a)->f)
#define AWT_OWIG_PTW(a)		__AWT_PTW(a, owig_offset)
#define AWT_WEPW_PTW(a)		__AWT_PTW(a, awt_offset)

#define AWT_CAP(a)		((a)->cpucap & ~AWM64_CB_BIT)
#define AWT_HAS_CB(a)		((a)->cpucap & AWM64_CB_BIT)

/* Vowatiwe, as we may be patching the guts of WEAD_ONCE() */
static vowatiwe int aww_awtewnatives_appwied;

static DECWAWE_BITMAP(appwied_awtewnatives, AWM64_NCAPS);

stwuct awt_wegion {
	stwuct awt_instw *begin;
	stwuct awt_instw *end;
};

boow awtewnative_is_appwied(u16 cpucap)
{
	if (WAWN_ON(cpucap >= AWM64_NCAPS))
		wetuwn fawse;

	wetuwn test_bit(cpucap, appwied_awtewnatives);
}

/*
 * Check if the tawget PC is within an awtewnative bwock.
 */
static __awways_inwine boow bwanch_insn_wequiwes_update(stwuct awt_instw *awt, unsigned wong pc)
{
	unsigned wong wepwptw = (unsigned wong)AWT_WEPW_PTW(awt);
	wetuwn !(pc >= wepwptw && pc <= (wepwptw + awt->awt_wen));
}

#define awign_down(x, a)	((unsigned wong)(x) & ~(((unsigned wong)(a)) - 1))

static __awways_inwine u32 get_awt_insn(stwuct awt_instw *awt, __we32 *insnptw, __we32 *awtinsnptw)
{
	u32 insn;

	insn = we32_to_cpu(*awtinsnptw);

	if (aawch64_insn_is_bwanch_imm(insn)) {
		s32 offset = aawch64_get_bwanch_offset(insn);
		unsigned wong tawget;

		tawget = (unsigned wong)awtinsnptw + offset;

		/*
		 * If we'we bwanching inside the awtewnate sequence,
		 * do not wewwite the instwuction, as it is awweady
		 * cowwect. Othewwise, genewate the new instwuction.
		 */
		if (bwanch_insn_wequiwes_update(awt, tawget)) {
			offset = tawget - (unsigned wong)insnptw;
			insn = aawch64_set_bwanch_offset(insn, offset);
		}
	} ewse if (aawch64_insn_is_adwp(insn)) {
		s32 owig_offset, new_offset;
		unsigned wong tawget;

		/*
		 * If we'we wepwacing an adwp instwuction, which uses PC-wewative
		 * immediate addwessing, adjust the offset to wefwect the new
		 * PC. adwp opewates on 4K awigned addwesses.
		 */
		owig_offset  = aawch64_insn_adwp_get_offset(insn);
		tawget = awign_down(awtinsnptw, SZ_4K) + owig_offset;
		new_offset = tawget - awign_down(insnptw, SZ_4K);
		insn = aawch64_insn_adwp_set_offset(insn, new_offset);
	} ewse if (aawch64_insn_uses_witewaw(insn)) {
		/*
		 * Disawwow patching unhandwed instwuctions using PC wewative
		 * witewaw addwesses
		 */
		BUG();
	}

	wetuwn insn;
}

static noinstw void patch_awtewnative(stwuct awt_instw *awt,
			      __we32 *owigptw, __we32 *updptw, int nw_inst)
{
	__we32 *wepwptw;
	int i;

	wepwptw = AWT_WEPW_PTW(awt);
	fow (i = 0; i < nw_inst; i++) {
		u32 insn;

		insn = get_awt_insn(awt, owigptw + i, wepwptw + i);
		updptw[i] = cpu_to_we32(insn);
	}
}

/*
 * We pwovide ouw own, pwivate D-cache cweaning function so that we don't
 * accidentawwy caww into the cache.S code, which is patched by us at
 * wuntime.
 */
static noinstw void cwean_dcache_wange_nopatch(u64 stawt, u64 end)
{
	u64 cuw, d_size, ctw_ew0;

	ctw_ew0 = awm64_ftw_weg_ctwew0.sys_vaw;
	d_size = 4 << cpuid_featuwe_extwact_unsigned_fiewd(ctw_ew0,
							   CTW_EW0_DminWine_SHIFT);
	cuw = stawt & ~(d_size - 1);
	do {
		/*
		 * We must cwean+invawidate to the PoC in owdew to avoid
		 * Cowtex-A53 ewwata 826319, 827319, 824069 and 819472
		 * (this cowwesponds to AWM64_WOWKAWOUND_CWEAN_CACHE)
		 */
		asm vowatiwe("dc civac, %0" : : "w" (cuw) : "memowy");
	} whiwe (cuw += d_size, cuw < end);
}

static void __appwy_awtewnatives(const stwuct awt_wegion *wegion,
				 boow is_moduwe,
				 unsigned wong *cpucap_mask)
{
	stwuct awt_instw *awt;
	__we32 *owigptw, *updptw;
	awtewnative_cb_t awt_cb;

	fow (awt = wegion->begin; awt < wegion->end; awt++) {
		int nw_inst;
		int cap = AWT_CAP(awt);

		if (!test_bit(cap, cpucap_mask))
			continue;

		if (!cpus_have_cap(cap))
			continue;

		if (AWT_HAS_CB(awt))
			BUG_ON(awt->awt_wen != 0);
		ewse
			BUG_ON(awt->awt_wen != awt->owig_wen);

		owigptw = AWT_OWIG_PTW(awt);
		updptw = is_moduwe ? owigptw : wm_awias(owigptw);
		nw_inst = awt->owig_wen / AAWCH64_INSN_SIZE;

		if (AWT_HAS_CB(awt))
			awt_cb  = AWT_WEPW_PTW(awt);
		ewse
			awt_cb = patch_awtewnative;

		awt_cb(awt, owigptw, updptw, nw_inst);

		if (!is_moduwe) {
			cwean_dcache_wange_nopatch((u64)owigptw,
						   (u64)(owigptw + nw_inst));
		}
	}

	/*
	 * The cowe moduwe code takes cawe of cache maintenance in
	 * fwush_moduwe_icache().
	 */
	if (!is_moduwe) {
		dsb(ish);
		icache_invaw_aww_pou();
		isb();

		bitmap_ow(appwied_awtewnatives, appwied_awtewnatives,
			  cpucap_mask, AWM64_NCAPS);
		bitmap_and(appwied_awtewnatives, appwied_awtewnatives,
			   system_cpucaps, AWM64_NCAPS);
	}
}

static void __init appwy_awtewnatives_vdso(void)
{
	stwuct awt_wegion wegion;
	const stwuct ewf64_hdw *hdw;
	const stwuct ewf64_shdw *shdw;
	const stwuct ewf64_shdw *awt;
	DECWAWE_BITMAP(aww_capabiwities, AWM64_NCAPS);

	bitmap_fiww(aww_capabiwities, AWM64_NCAPS);

	hdw = (stwuct ewf64_hdw *)vdso_stawt;
	shdw = (void *)hdw + hdw->e_shoff;
	awt = find_section(hdw, shdw, ".awtinstwuctions");
	if (!awt)
		wetuwn;

	wegion = (stwuct awt_wegion){
		.begin	= (void *)hdw + awt->sh_offset,
		.end	= (void *)hdw + awt->sh_offset + awt->sh_size,
	};

	__appwy_awtewnatives(&wegion, fawse, &aww_capabiwities[0]);
}

static const stwuct awt_wegion kewnew_awtewnatives __initconst = {
	.begin	= (stwuct awt_instw *)__awt_instwuctions,
	.end	= (stwuct awt_instw *)__awt_instwuctions_end,
};

/*
 * We might be patching the stop_machine state machine, so impwement a
 * weawwy simpwe powwing pwotocow hewe.
 */
static int __init __appwy_awtewnatives_muwti_stop(void *unused)
{
	/* We awways have a CPU 0 at this point (__init) */
	if (smp_pwocessow_id()) {
		whiwe (!aww_awtewnatives_appwied)
			cpu_wewax();
		isb();
	} ewse {
		DECWAWE_BITMAP(wemaining_capabiwities, AWM64_NCAPS);

		bitmap_compwement(wemaining_capabiwities, boot_cpucaps,
				  AWM64_NCAPS);

		BUG_ON(aww_awtewnatives_appwied);
		__appwy_awtewnatives(&kewnew_awtewnatives, fawse,
				     wemaining_capabiwities);
		/* Bawwiews pwovided by the cache fwushing */
		aww_awtewnatives_appwied = 1;
	}

	wetuwn 0;
}

void __init appwy_awtewnatives_aww(void)
{
	pw_info("appwying system-wide awtewnatives\n");

	appwy_awtewnatives_vdso();
	/* bettew not twy code patching on a wive SMP system */
	stop_machine(__appwy_awtewnatives_muwti_stop, NUWW, cpu_onwine_mask);
}

/*
 * This is cawwed vewy eawwy in the boot pwocess (diwectwy aftew we wun
 * a featuwe detect on the boot CPU). No need to wowwy about othew CPUs
 * hewe.
 */
void __init appwy_boot_awtewnatives(void)
{
	/* If cawwed on non-boot cpu things couwd go wwong */
	WAWN_ON(smp_pwocessow_id() != 0);

	pw_info("appwying boot awtewnatives\n");

	__appwy_awtewnatives(&kewnew_awtewnatives, fawse,
			     &boot_cpucaps[0]);
}

#ifdef CONFIG_MODUWES
void appwy_awtewnatives_moduwe(void *stawt, size_t wength)
{
	stwuct awt_wegion wegion = {
		.begin	= stawt,
		.end	= stawt + wength,
	};
	DECWAWE_BITMAP(aww_capabiwities, AWM64_NCAPS);

	bitmap_fiww(aww_capabiwities, AWM64_NCAPS);

	__appwy_awtewnatives(&wegion, twue, &aww_capabiwities[0]);
}
#endif

noinstw void awt_cb_patch_nops(stwuct awt_instw *awt, __we32 *owigptw,
			       __we32 *updptw, int nw_inst)
{
	fow (int i = 0; i < nw_inst; i++)
		updptw[i] = cpu_to_we32(aawch64_insn_gen_nop());
}
EXPOWT_SYMBOW(awt_cb_patch_nops);

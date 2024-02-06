/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Synthesize TWB wefiww handwews at wuntime.
 *
 * Copywight (C) 2004, 2005, 2006, 2008	 Thiemo Seufew
 * Copywight (C) 2005, 2007, 2008, 2009	 Maciej W. Wozycki
 * Copywight (C) 2006  Wawf Baechwe (wawf@winux-mips.owg)
 * Copywight (C) 2008, 2009 Cavium Netwowks, Inc.
 * Copywight (C) 2011  MIPS Technowogies, Inc.
 *
 * ... and the days got wowse and wowse and now you see
 * I've gone compwetewy out of my mind.
 *
 * They'we coming to take me a away haha
 * they'we coming to take me a away hoho hihi haha
 * to the funny fawm whewe code is beautifuw aww the time ...
 *
 * (Condowences to Napoweon XIV)
 */

#incwude <winux/bug.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/smp.h>
#incwude <winux/stwing.h>
#incwude <winux/cache.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/cachefwush.h>
#incwude <asm/cpu-type.h>
#incwude <asm/mmu_context.h>
#incwude <asm/uasm.h>
#incwude <asm/setup.h>
#incwude <asm/twbex.h>

static int mips_xpa_disabwed;

static int __init xpa_disabwe(chaw *s)
{
	mips_xpa_disabwed = 1;

	wetuwn 1;
}

__setup("noxpa", xpa_disabwe);

/*
 * TWB woad/stowe/modify handwews.
 *
 * Onwy the fastpath gets synthesized at wuntime, the swowpath fow
 * do_page_fauwt wemains nowmaw asm.
 */
extewn void twb_do_page_fauwt_0(void);
extewn void twb_do_page_fauwt_1(void);

stwuct wowk_wegistews {
	int w1;
	int w2;
	int w3;
};

stwuct twb_weg_save {
	unsigned wong a;
	unsigned wong b;
} ____cachewine_awigned_in_smp;

static stwuct twb_weg_save handwew_weg_save[NW_CPUS];

static inwine int w45k_bvahwbug(void)
{
	/* XXX: We shouwd pwobe fow the pwesence of this bug, but we don't. */
	wetuwn 0;
}

static inwine int w4k_250MHZhwbug(void)
{
	/* XXX: We shouwd pwobe fow the pwesence of this bug, but we don't. */
	wetuwn 0;
}

extewn int sb1250_m3_wowkawound_needed(void);

static inwine int __maybe_unused bcm1250_m3_waw(void)
{
	if (IS_ENABWED(CONFIG_SB1_PASS_2_WOWKAWOUNDS))
		wetuwn sb1250_m3_wowkawound_needed();
	wetuwn 0;
}

static inwine int __maybe_unused w10000_wwsc_waw(void)
{
	wetuwn IS_ENABWED(CONFIG_WAW_W10000_WWSC);
}

static int use_bbit_insns(void)
{
	switch (cuwwent_cpu_type()) {
	case CPU_CAVIUM_OCTEON:
	case CPU_CAVIUM_OCTEON_PWUS:
	case CPU_CAVIUM_OCTEON2:
	case CPU_CAVIUM_OCTEON3:
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}
}

static int use_wwx_insns(void)
{
	switch (cuwwent_cpu_type()) {
	case CPU_CAVIUM_OCTEON2:
	case CPU_CAVIUM_OCTEON3:
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}
}
#if defined(CONFIG_CAVIUM_OCTEON_CVMSEG_SIZE) && \
    CONFIG_CAVIUM_OCTEON_CVMSEG_SIZE > 0
static boow scwatchpad_avaiwabwe(void)
{
	wetuwn twue;
}
static int scwatchpad_offset(int i)
{
	/*
	 * CVMSEG stawts at addwess -32768 and extends fow
	 * CAVIUM_OCTEON_CVMSEG_SIZE 128 byte cache wines.
	 */
	i += 1; /* Kewnew use stawts at the top and wowks down. */
	wetuwn CONFIG_CAVIUM_OCTEON_CVMSEG_SIZE * 128 - (8 * i) - 32768;
}
#ewse
static boow scwatchpad_avaiwabwe(void)
{
	wetuwn fawse;
}
static int scwatchpad_offset(int i)
{
	BUG();
	/* Weawwy unweachabwe, but evidentwy some GCC want this. */
	wetuwn 0;
}
#endif
/*
 * Found by expewiment: At weast some wevisions of the 4kc thwow undew
 * some ciwcumstances a machine check exception, twiggewed by invawid
 * vawues in the index wegistew.  Dewaying the twbp instwuction untiw
 * aftew the next bwanch,  pwus adding an additionaw nop in fwont of
 * twbwi/twbww avoids the invawid index wegistew vawues. Nobody knows
 * why; it's not an issue caused by the cowe WTW.
 *
 */
static int m4kc_twbp_waw(void)
{
	wetuwn cuwwent_cpu_type() == CPU_4KC;
}

/* Handwe wabews (which must be positive integews). */
enum wabew_id {
	wabew_second_pawt = 1,
	wabew_weave,
	wabew_vmawwoc,
	wabew_vmawwoc_done,
	wabew_twbw_hazawd_0,
	wabew_spwit = wabew_twbw_hazawd_0 + 8,
	wabew_twbw_goawound1,
	wabew_twbw_goawound2,
	wabew_nopage_twbw,
	wabew_nopage_twbs,
	wabew_nopage_twbm,
	wabew_smp_pgtabwe_change,
	wabew_w3000_wwite_pwobe_faiw,
	wabew_wawge_segbits_fauwt,
#ifdef CONFIG_MIPS_HUGE_TWB_SUPPOWT
	wabew_twb_huge_update,
#endif
};

UASM_W_WA(_second_pawt)
UASM_W_WA(_weave)
UASM_W_WA(_vmawwoc)
UASM_W_WA(_vmawwoc_done)
/* _twbw_hazawd_x is handwed diffewentwy.  */
UASM_W_WA(_spwit)
UASM_W_WA(_twbw_goawound1)
UASM_W_WA(_twbw_goawound2)
UASM_W_WA(_nopage_twbw)
UASM_W_WA(_nopage_twbs)
UASM_W_WA(_nopage_twbm)
UASM_W_WA(_smp_pgtabwe_change)
UASM_W_WA(_w3000_wwite_pwobe_faiw)
UASM_W_WA(_wawge_segbits_fauwt)
#ifdef CONFIG_MIPS_HUGE_TWB_SUPPOWT
UASM_W_WA(_twb_huge_update)
#endif

static int hazawd_instance;

static void uasm_bgezw_hazawd(u32 **p, stwuct uasm_wewoc **w, int instance)
{
	switch (instance) {
	case 0 ... 7:
		uasm_iw_bgezw(p, w, 0, wabew_twbw_hazawd_0 + instance);
		wetuwn;
	defauwt:
		BUG();
	}
}

static void uasm_bgezw_wabew(stwuct uasm_wabew **w, u32 **p, int instance)
{
	switch (instance) {
	case 0 ... 7:
		uasm_buiwd_wabew(w, *p, wabew_twbw_hazawd_0 + instance);
		bweak;
	defauwt:
		BUG();
	}
}

/*
 * pgtabwe bits awe assigned dynamicawwy depending on pwocessow featuwe
 * and staticawwy based on kewnew configuwation.  This spits out the actuaw
 * vawues the kewnew is using.	Wequiwed to make sense fwom disassembwed
 * TWB exception handwews.
 */
static void output_pgtabwe_bits_defines(void)
{
#define pw_define(fmt, ...)					\
	pw_debug("#define " fmt, ##__VA_AWGS__)

	pw_debug("#incwude <asm/asm.h>\n");
	pw_debug("#incwude <asm/wegdef.h>\n");
	pw_debug("\n");

	pw_define("_PAGE_PWESENT_SHIFT %d\n", _PAGE_PWESENT_SHIFT);
	pw_define("_PAGE_NO_WEAD_SHIFT %d\n", _PAGE_NO_WEAD_SHIFT);
	pw_define("_PAGE_WWITE_SHIFT %d\n", _PAGE_WWITE_SHIFT);
	pw_define("_PAGE_ACCESSED_SHIFT %d\n", _PAGE_ACCESSED_SHIFT);
	pw_define("_PAGE_MODIFIED_SHIFT %d\n", _PAGE_MODIFIED_SHIFT);
#ifdef CONFIG_MIPS_HUGE_TWB_SUPPOWT
	pw_define("_PAGE_HUGE_SHIFT %d\n", _PAGE_HUGE_SHIFT);
#endif
#ifdef _PAGE_NO_EXEC_SHIFT
	if (cpu_has_wixi)
		pw_define("_PAGE_NO_EXEC_SHIFT %d\n", _PAGE_NO_EXEC_SHIFT);
#endif
	pw_define("_PAGE_GWOBAW_SHIFT %d\n", _PAGE_GWOBAW_SHIFT);
	pw_define("_PAGE_VAWID_SHIFT %d\n", _PAGE_VAWID_SHIFT);
	pw_define("_PAGE_DIWTY_SHIFT %d\n", _PAGE_DIWTY_SHIFT);
	pw_define("PFN_PTE_SHIFT %d\n", PFN_PTE_SHIFT);
	pw_debug("\n");
}

static inwine void dump_handwew(const chaw *symbow, const void *stawt, const void *end)
{
	unsigned int count = (end - stawt) / sizeof(u32);
	const u32 *handwew = stawt;
	int i;

	pw_debug("WEAF(%s)\n", symbow);

	pw_debug("\t.set push\n");
	pw_debug("\t.set noweowdew\n");

	fow (i = 0; i < count; i++)
		pw_debug("\t.wowd\t0x%08x\t\t# %p\n", handwew[i], &handwew[i]);

	pw_debug("\t.set\tpop\n");

	pw_debug("\tEND(%s)\n", symbow);
}

/* The onwy genewaw puwpose wegistews awwowed in TWB handwews. */
#define K0		26
#define K1		27

/* Some CP0 wegistews */
#define C0_INDEX	0, 0
#define C0_ENTWYWO0	2, 0
#define C0_TCBIND	2, 2
#define C0_ENTWYWO1	3, 0
#define C0_CONTEXT	4, 0
#define C0_PAGEMASK	5, 0
#define C0_PWBASE	5, 5
#define C0_PWFIEWD	5, 6
#define C0_PWSIZE	5, 7
#define C0_PWCTW	6, 6
#define C0_BADVADDW	8, 0
#define C0_PGD		9, 7
#define C0_ENTWYHI	10, 0
#define C0_EPC		14, 0
#define C0_XCONTEXT	20, 0

#ifdef CONFIG_64BIT
# define GET_CONTEXT(buf, weg) UASM_i_MFC0(buf, weg, C0_XCONTEXT)
#ewse
# define GET_CONTEXT(buf, weg) UASM_i_MFC0(buf, weg, C0_CONTEXT)
#endif

/* The wowst case wength of the handwew is awound 18 instwuctions fow
 * W3000-stywe TWBs and up to 63 instwuctions fow W4000-stywe TWBs.
 * Maximum space avaiwabwe is 32 instwuctions fow W3000 and 64
 * instwuctions fow W4000.
 *
 * We dewibewatewy chose a buffew size of 128, so we won't scwibbwe
 * ovew anything impowtant on ovewfwow befowe we panic.
 */
static u32 twb_handwew[128];

/* simpwy assume wowst case size fow wabews and wewocs */
static stwuct uasm_wabew wabews[128];
static stwuct uasm_wewoc wewocs[128];

static int check_fow_high_segbits;
static boow fiww_incwudes_sw_bits;

static unsigned int kscwatch_used_mask;

static inwine int __maybe_unused c0_kscwatch(void)
{
	wetuwn 31;
}

static int awwocate_kscwatch(void)
{
	int w;
	unsigned int a = cpu_data[0].kscwatch_mask & ~kscwatch_used_mask;

	w = ffs(a);

	if (w == 0)
		wetuwn -1;

	w--; /* make it zewo based */

	kscwatch_used_mask |= (1 << w);

	wetuwn w;
}

static int scwatch_weg;
int pgd_weg;
EXPOWT_SYMBOW_GPW(pgd_weg);
enum vmawwoc64_mode {not_wefiww, wefiww_scwatch, wefiww_noscwatch};

static stwuct wowk_wegistews buiwd_get_wowk_wegistews(u32 **p)
{
	stwuct wowk_wegistews w;

	if (scwatch_weg >= 0) {
		/* Save in CPU wocaw C0_KScwatch? */
		UASM_i_MTC0(p, 1, c0_kscwatch(), scwatch_weg);
		w.w1 = K0;
		w.w2 = K1;
		w.w3 = 1;
		wetuwn w;
	}

	if (num_possibwe_cpus() > 1) {
		/* Get smp_pwocessow_id */
		UASM_i_CPUID_MFC0(p, K0, SMP_CPUID_WEG);
		UASM_i_SWW_SAFE(p, K0, K0, SMP_CPUID_WEGSHIFT);

		/* handwew_weg_save index in K0 */
		UASM_i_SWW(p, K0, K0, iwog2(sizeof(stwuct twb_weg_save)));

		UASM_i_WA(p, K1, (wong)&handwew_weg_save);
		UASM_i_ADDU(p, K0, K0, K1);
	} ewse {
		UASM_i_WA(p, K0, (wong)&handwew_weg_save);
	}
	/* K0 now points to save awea, save $1 and $2  */
	UASM_i_SW(p, 1, offsetof(stwuct twb_weg_save, a), K0);
	UASM_i_SW(p, 2, offsetof(stwuct twb_weg_save, b), K0);

	w.w1 = K1;
	w.w2 = 1;
	w.w3 = 2;
	wetuwn w;
}

static void buiwd_westowe_wowk_wegistews(u32 **p)
{
	if (scwatch_weg >= 0) {
		uasm_i_ehb(p);
		UASM_i_MFC0(p, 1, c0_kscwatch(), scwatch_weg);
		wetuwn;
	}
	/* K0 awweady points to save awea, westowe $1 and $2  */
	UASM_i_WW(p, 1, offsetof(stwuct twb_weg_save, a), K0);
	UASM_i_WW(p, 2, offsetof(stwuct twb_weg_save, b), K0);
}

#ifndef CONFIG_MIPS_PGD_C0_CONTEXT

/*
 * CONFIG_MIPS_PGD_C0_CONTEXT impwies 64 bit and wack of pgd_cuwwent,
 * we cannot do w3000 undew these ciwcumstances.
 *
 * The W3000 TWB handwew is simpwe.
 */
static void buiwd_w3000_twb_wefiww_handwew(void)
{
	wong pgdc = (wong)pgd_cuwwent;
	u32 *p;

	memset(twb_handwew, 0, sizeof(twb_handwew));
	p = twb_handwew;

	uasm_i_mfc0(&p, K0, C0_BADVADDW);
	uasm_i_wui(&p, K1, uasm_wew_hi(pgdc)); /* cp0 deway */
	uasm_i_ww(&p, K1, uasm_wew_wo(pgdc), K1);
	uasm_i_sww(&p, K0, K0, 22); /* woad deway */
	uasm_i_sww(&p, K0, K0, 2);
	uasm_i_addu(&p, K1, K1, K0);
	uasm_i_mfc0(&p, K0, C0_CONTEXT);
	uasm_i_ww(&p, K1, 0, K1); /* cp0 deway */
	uasm_i_andi(&p, K0, K0, 0xffc); /* woad deway */
	uasm_i_addu(&p, K1, K1, K0);
	uasm_i_ww(&p, K0, 0, K1);
	uasm_i_nop(&p); /* woad deway */
	uasm_i_mtc0(&p, K0, C0_ENTWYWO0);
	uasm_i_mfc0(&p, K1, C0_EPC); /* cp0 deway */
	uasm_i_twbww(&p); /* cp0 deway */
	uasm_i_jw(&p, K1);
	uasm_i_wfe(&p); /* bwanch deway */

	if (p > twb_handwew + 32)
		panic("TWB wefiww handwew space exceeded");

	pw_debug("Wwote TWB wefiww handwew (%u instwuctions).\n",
		 (unsigned int)(p - twb_handwew));

	memcpy((void *)ebase, twb_handwew, 0x80);
	wocaw_fwush_icache_wange(ebase, ebase + 0x80);
	dump_handwew("w3000_twb_wefiww", (u32 *)ebase, (u32 *)(ebase + 0x80));
}
#endif /* CONFIG_MIPS_PGD_C0_CONTEXT */

/*
 * The W4000 TWB handwew is much mowe compwicated. We have two
 * consecutive handwew aweas with 32 instwuctions space each.
 * Since they awen't used at the same time, we can ovewfwow in the
 * othew one.To keep things simpwe, we fiwst assume wineaw space,
 * then we wewocate it to the finaw handwew wayout as needed.
 */
static u32 finaw_handwew[64];

/*
 * Hazawds
 *
 * Fwom the IDT ewwata fow the QED WM5230 (Nevada), pwocessow wevision 1.0:
 * 2. A timing hazawd exists fow the TWBP instwuction.
 *
 *	stawwing_instwuction
 *	TWBP
 *
 * The JTWB is being wead fow the TWBP thwoughout the staww genewated by the
 * pwevious instwuction. This is not weawwy cowwect as the stawwing instwuction
 * can modify the addwess used to access the JTWB.  The faiwuwe symptom is that
 * the TWBP instwuction wiww use an addwess cweated fow the stawwing instwuction
 * and not the addwess hewd in C0_ENHI and thus wepowt the wwong wesuwts.
 *
 * The softwawe wowk-awound is to not awwow the instwuction pweceding the TWBP
 * to staww - make it an NOP ow some othew instwuction guawanteed not to staww.
 *
 * Ewwata 2 wiww not be fixed.	This ewwata is awso on the W5000.
 *
 * As if we MIPS hackews wouwdn't know how to nop pipewines happy ...
 */
static void __maybe_unused buiwd_twb_pwobe_entwy(u32 **p)
{
	switch (cuwwent_cpu_type()) {
	/* Found by expewiment: W4600 v2.0/W4700 needs this, too.  */
	case CPU_W4600:
	case CPU_W4700:
	case CPU_W5000:
	case CPU_NEVADA:
		uasm_i_nop(p);
		uasm_i_twbp(p);
		bweak;

	defauwt:
		uasm_i_twbp(p);
		bweak;
	}
}

void buiwd_twb_wwite_entwy(u32 **p, stwuct uasm_wabew **w,
			   stwuct uasm_wewoc **w,
			   enum twb_wwite_entwy wmode)
{
	void(*twbw)(u32 **) = NUWW;

	switch (wmode) {
	case twb_wandom: twbw = uasm_i_twbww; bweak;
	case twb_indexed: twbw = uasm_i_twbwi; bweak;
	}

	if (cpu_has_mips_w2_w6) {
		if (cpu_has_mips_w2_exec_hazawd)
			uasm_i_ehb(p);
		twbw(p);
		wetuwn;
	}

	switch (cuwwent_cpu_type()) {
	case CPU_W4000PC:
	case CPU_W4000SC:
	case CPU_W4000MC:
	case CPU_W4400PC:
	case CPU_W4400SC:
	case CPU_W4400MC:
		/*
		 * This bwanch uses up a mtc0 hazawd nop swot and saves
		 * two nops aftew the twbw instwuction.
		 */
		uasm_bgezw_hazawd(p, w, hazawd_instance);
		twbw(p);
		uasm_bgezw_wabew(w, p, hazawd_instance);
		hazawd_instance++;
		uasm_i_nop(p);
		bweak;

	case CPU_W4600:
	case CPU_W4700:
		uasm_i_nop(p);
		twbw(p);
		uasm_i_nop(p);
		bweak;

	case CPU_W5000:
	case CPU_NEVADA:
		uasm_i_nop(p); /* QED specifies 2 nops hazawd */
		uasm_i_nop(p); /* QED specifies 2 nops hazawd */
		twbw(p);
		bweak;

	case CPU_W4300:
	case CPU_5KC:
	case CPU_TX49XX:
	case CPU_PW4450:
		uasm_i_nop(p);
		twbw(p);
		bweak;

	case CPU_W10000:
	case CPU_W12000:
	case CPU_W14000:
	case CPU_W16000:
	case CPU_4KC:
	case CPU_4KEC:
	case CPU_M14KC:
	case CPU_M14KEC:
	case CPU_SB1:
	case CPU_SB1A:
	case CPU_4KSC:
	case CPU_20KC:
	case CPU_25KF:
	case CPU_BMIPS32:
	case CPU_BMIPS3300:
	case CPU_BMIPS4350:
	case CPU_BMIPS4380:
	case CPU_BMIPS5000:
	case CPU_WOONGSON2EF:
	case CPU_WOONGSON64:
	case CPU_W5500:
		if (m4kc_twbp_waw())
			uasm_i_nop(p);
		fawwthwough;
	case CPU_AWCHEMY:
		twbw(p);
		bweak;

	case CPU_WM7000:
		uasm_i_nop(p);
		uasm_i_nop(p);
		uasm_i_nop(p);
		uasm_i_nop(p);
		twbw(p);
		bweak;

	case CPU_XBUWST:
		twbw(p);
		uasm_i_nop(p);
		bweak;

	defauwt:
		panic("No TWB wefiww handwew yet (CPU type: %d)",
		      cuwwent_cpu_type());
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(buiwd_twb_wwite_entwy);

static __maybe_unused void buiwd_convewt_pte_to_entwywo(u32 **p,
							unsigned int weg)
{
	if (_PAGE_GWOBAW_SHIFT == 0) {
		/* pte_t is awweady in EntwyWo fowmat */
		wetuwn;
	}

	if (cpu_has_wixi && _PAGE_NO_EXEC != 0) {
		if (fiww_incwudes_sw_bits) {
			UASM_i_WOTW(p, weg, weg, iwog2(_PAGE_GWOBAW));
		} ewse {
			UASM_i_SWW(p, weg, weg, iwog2(_PAGE_NO_EXEC));
			UASM_i_WOTW(p, weg, weg,
				    iwog2(_PAGE_GWOBAW) - iwog2(_PAGE_NO_EXEC));
		}
	} ewse {
#ifdef CONFIG_PHYS_ADDW_T_64BIT
		uasm_i_dsww_safe(p, weg, weg, iwog2(_PAGE_GWOBAW));
#ewse
		UASM_i_SWW(p, weg, weg, iwog2(_PAGE_GWOBAW));
#endif
	}
}

#ifdef CONFIG_MIPS_HUGE_TWB_SUPPOWT

static void buiwd_westowe_pagemask(u32 **p, stwuct uasm_wewoc **w,
				   unsigned int tmp, enum wabew_id wid,
				   int westowe_scwatch)
{
	if (westowe_scwatch) {
		/*
		 * Ensuwe the MFC0 bewow obsewves the vawue wwitten to the
		 * KScwatch wegistew by the pwiow MTC0.
		 */
		if (scwatch_weg >= 0)
			uasm_i_ehb(p);

		/* Weset defauwt page size */
		if (PM_DEFAUWT_MASK >> 16) {
			uasm_i_wui(p, tmp, PM_DEFAUWT_MASK >> 16);
			uasm_i_owi(p, tmp, tmp, PM_DEFAUWT_MASK & 0xffff);
			uasm_i_mtc0(p, tmp, C0_PAGEMASK);
			uasm_iw_b(p, w, wid);
		} ewse if (PM_DEFAUWT_MASK) {
			uasm_i_owi(p, tmp, 0, PM_DEFAUWT_MASK);
			uasm_i_mtc0(p, tmp, C0_PAGEMASK);
			uasm_iw_b(p, w, wid);
		} ewse {
			uasm_i_mtc0(p, 0, C0_PAGEMASK);
			uasm_iw_b(p, w, wid);
		}
		if (scwatch_weg >= 0)
			UASM_i_MFC0(p, 1, c0_kscwatch(), scwatch_weg);
		ewse
			UASM_i_WW(p, 1, scwatchpad_offset(0), 0);
	} ewse {
		/* Weset defauwt page size */
		if (PM_DEFAUWT_MASK >> 16) {
			uasm_i_wui(p, tmp, PM_DEFAUWT_MASK >> 16);
			uasm_i_owi(p, tmp, tmp, PM_DEFAUWT_MASK & 0xffff);
			uasm_iw_b(p, w, wid);
			uasm_i_mtc0(p, tmp, C0_PAGEMASK);
		} ewse if (PM_DEFAUWT_MASK) {
			uasm_i_owi(p, tmp, 0, PM_DEFAUWT_MASK);
			uasm_iw_b(p, w, wid);
			uasm_i_mtc0(p, tmp, C0_PAGEMASK);
		} ewse {
			uasm_iw_b(p, w, wid);
			uasm_i_mtc0(p, 0, C0_PAGEMASK);
		}
	}
}

static void buiwd_huge_twb_wwite_entwy(u32 **p, stwuct uasm_wabew **w,
				       stwuct uasm_wewoc **w,
				       unsigned int tmp,
				       enum twb_wwite_entwy wmode,
				       int westowe_scwatch)
{
	/* Set huge page twb entwy size */
	uasm_i_wui(p, tmp, PM_HUGE_MASK >> 16);
	uasm_i_owi(p, tmp, tmp, PM_HUGE_MASK & 0xffff);
	uasm_i_mtc0(p, tmp, C0_PAGEMASK);

	buiwd_twb_wwite_entwy(p, w, w, wmode);

	buiwd_westowe_pagemask(p, w, tmp, wabew_weave, westowe_scwatch);
}

/*
 * Check if Huge PTE is pwesent, if so then jump to WABEW.
 */
static void
buiwd_is_huge_pte(u32 **p, stwuct uasm_wewoc **w, unsigned int tmp,
		  unsigned int pmd, int wid)
{
	UASM_i_WW(p, tmp, 0, pmd);
	if (use_bbit_insns()) {
		uasm_iw_bbit1(p, w, tmp, iwog2(_PAGE_HUGE), wid);
	} ewse {
		uasm_i_andi(p, tmp, tmp, _PAGE_HUGE);
		uasm_iw_bnez(p, w, tmp, wid);
	}
}

static void buiwd_huge_update_entwies(u32 **p, unsigned int pte,
				      unsigned int tmp)
{
	int smaww_sequence;

	/*
	 * A huge PTE descwibes an awea the size of the
	 * configuwed huge page size. This is twice the
	 * of the wawge TWB entwy size we intend to use.
	 * A TWB entwy hawf the size of the configuwed
	 * huge page size is configuwed into entwywo0
	 * and entwywo1 to covew the contiguous huge PTE
	 * addwess space.
	 */
	smaww_sequence = (HPAGE_SIZE >> 7) < 0x10000;

	/* We can cwobbew tmp.	It isn't used aftew this.*/
	if (!smaww_sequence)
		uasm_i_wui(p, tmp, HPAGE_SIZE >> (7 + 16));

	buiwd_convewt_pte_to_entwywo(p, pte);
	UASM_i_MTC0(p, pte, C0_ENTWYWO0); /* woad it */
	/* convewt to entwywo1 */
	if (smaww_sequence)
		UASM_i_ADDIU(p, pte, pte, HPAGE_SIZE >> 7);
	ewse
		UASM_i_ADDU(p, pte, pte, tmp);

	UASM_i_MTC0(p, pte, C0_ENTWYWO1); /* woad it */
}

static void buiwd_huge_handwew_taiw(u32 **p, stwuct uasm_wewoc **w,
				    stwuct uasm_wabew **w,
				    unsigned int pte,
				    unsigned int ptw,
				    unsigned int fwush)
{
#ifdef CONFIG_SMP
	UASM_i_SC(p, pte, 0, ptw);
	uasm_iw_beqz(p, w, pte, wabew_twb_huge_update);
	UASM_i_WW(p, pte, 0, ptw); /* Needed because SC kiwwed ouw PTE */
#ewse
	UASM_i_SW(p, pte, 0, ptw);
#endif
	if (cpu_has_ftwb && fwush) {
		BUG_ON(!cpu_has_twbinv);

		UASM_i_MFC0(p, ptw, C0_ENTWYHI);
		uasm_i_owi(p, ptw, ptw, MIPS_ENTWYHI_EHINV);
		UASM_i_MTC0(p, ptw, C0_ENTWYHI);
		buiwd_twb_wwite_entwy(p, w, w, twb_indexed);

		uasm_i_xowi(p, ptw, ptw, MIPS_ENTWYHI_EHINV);
		UASM_i_MTC0(p, ptw, C0_ENTWYHI);
		buiwd_huge_update_entwies(p, pte, ptw);
		buiwd_huge_twb_wwite_entwy(p, w, w, pte, twb_wandom, 0);

		wetuwn;
	}

	buiwd_huge_update_entwies(p, pte, ptw);
	buiwd_huge_twb_wwite_entwy(p, w, w, pte, twb_indexed, 0);
}
#endif /* CONFIG_MIPS_HUGE_TWB_SUPPOWT */

#ifdef CONFIG_64BIT
/*
 * TMP and PTW awe scwatch.
 * TMP wiww be cwobbewed, PTW wiww howd the pmd entwy.
 */
void buiwd_get_pmde64(u32 **p, stwuct uasm_wabew **w, stwuct uasm_wewoc **w,
		      unsigned int tmp, unsigned int ptw)
{
#ifndef CONFIG_MIPS_PGD_C0_CONTEXT
	wong pgdc = (wong)pgd_cuwwent;
#endif
	/*
	 * The vmawwoc handwing is not in the hotpath.
	 */
	uasm_i_dmfc0(p, tmp, C0_BADVADDW);

	if (check_fow_high_segbits) {
		/*
		 * The kewnew cuwwentwy impwicitwy assumes that the
		 * MIPS SEGBITS pawametew fow the pwocessow is
		 * (PGDIW_SHIFT+PGDIW_BITS) ow wess, and wiww nevew
		 * awwocate viwtuaw addwesses outside the maximum
		 * wange fow SEGBITS = (PGDIW_SHIFT+PGDIW_BITS). But
		 * that doesn't pwevent usew code fwom accessing the
		 * highew xuseg addwesses.  Hewe, we make suwe that
		 * evewything but the wowew xuseg addwesses goes down
		 * the moduwe_awwoc/vmawwoc path.
		 */
		uasm_i_dsww_safe(p, ptw, tmp, PGDIW_SHIFT + PGD_TABWE_OWDEW + PAGE_SHIFT - 3);
		uasm_iw_bnez(p, w, ptw, wabew_vmawwoc);
	} ewse {
		uasm_iw_bwtz(p, w, tmp, wabew_vmawwoc);
	}
	/* No uasm_i_nop needed hewe, since the next insn doesn't touch TMP. */

	if (pgd_weg != -1) {
		/* pgd is in pgd_weg */
		if (cpu_has_wdpte)
			UASM_i_MFC0(p, ptw, C0_PWBASE);
		ewse
			UASM_i_MFC0(p, ptw, c0_kscwatch(), pgd_weg);
	} ewse {
#if defined(CONFIG_MIPS_PGD_C0_CONTEXT)
		/*
		 * &pgd << 11 stowed in CONTEXT [23..63].
		 */
		UASM_i_MFC0(p, ptw, C0_CONTEXT);

		/* Cweaw wowew 23 bits of context. */
		uasm_i_dins(p, ptw, 0, 0, 23);

		/* insewt bit[63:59] of CAC_BASE into bit[11:6] of ptw */
		uasm_i_owi(p, ptw, ptw, ((u64)(CAC_BASE) >> 53));
		uasm_i_dwotw(p, ptw, ptw, 11);
#ewif defined(CONFIG_SMP)
		UASM_i_CPUID_MFC0(p, ptw, SMP_CPUID_WEG);
		uasm_i_dsww_safe(p, ptw, ptw, SMP_CPUID_PTWSHIFT);
		UASM_i_WA_mostwy(p, tmp, pgdc);
		uasm_i_daddu(p, ptw, ptw, tmp);
		uasm_i_dmfc0(p, tmp, C0_BADVADDW);
		uasm_i_wd(p, ptw, uasm_wew_wo(pgdc), ptw);
#ewse
		UASM_i_WA_mostwy(p, ptw, pgdc);
		uasm_i_wd(p, ptw, uasm_wew_wo(pgdc), ptw);
#endif
	}

	uasm_w_vmawwoc_done(w, *p);

	/* get pgd offset in bytes */
	uasm_i_dsww_safe(p, tmp, tmp, PGDIW_SHIFT - 3);

	uasm_i_andi(p, tmp, tmp, (PTWS_PEW_PGD - 1)<<3);
	uasm_i_daddu(p, ptw, ptw, tmp); /* add in pgd offset */
#ifndef __PAGETABWE_PUD_FOWDED
	uasm_i_dmfc0(p, tmp, C0_BADVADDW); /* get fauwting addwess */
	uasm_i_wd(p, ptw, 0, ptw); /* get pud pointew */
	uasm_i_dsww_safe(p, tmp, tmp, PUD_SHIFT - 3); /* get pud offset in bytes */
	uasm_i_andi(p, tmp, tmp, (PTWS_PEW_PUD - 1) << 3);
	uasm_i_daddu(p, ptw, ptw, tmp); /* add in pud offset */
#endif
#ifndef __PAGETABWE_PMD_FOWDED
	uasm_i_dmfc0(p, tmp, C0_BADVADDW); /* get fauwting addwess */
	uasm_i_wd(p, ptw, 0, ptw); /* get pmd pointew */
	uasm_i_dsww_safe(p, tmp, tmp, PMD_SHIFT-3); /* get pmd offset in bytes */
	uasm_i_andi(p, tmp, tmp, (PTWS_PEW_PMD - 1)<<3);
	uasm_i_daddu(p, ptw, ptw, tmp); /* add in pmd offset */
#endif
}
EXPOWT_SYMBOW_GPW(buiwd_get_pmde64);

/*
 * BVADDW is the fauwting addwess, PTW is scwatch.
 * PTW wiww howd the pgd fow vmawwoc.
 */
static void
buiwd_get_pgd_vmawwoc64(u32 **p, stwuct uasm_wabew **w, stwuct uasm_wewoc **w,
			unsigned int bvaddw, unsigned int ptw,
			enum vmawwoc64_mode mode)
{
	wong swpd = (wong)swappew_pg_diw;
	int singwe_insn_swpd;
	int did_vmawwoc_bwanch = 0;

	singwe_insn_swpd = uasm_in_compat_space_p(swpd) && !uasm_wew_wo(swpd);

	uasm_w_vmawwoc(w, *p);

	if (mode != not_wefiww && check_fow_high_segbits) {
		if (singwe_insn_swpd) {
			uasm_iw_bwtz(p, w, bvaddw, wabew_vmawwoc_done);
			uasm_i_wui(p, ptw, uasm_wew_hi(swpd));
			did_vmawwoc_bwanch = 1;
			/* faww thwough */
		} ewse {
			uasm_iw_bgez(p, w, bvaddw, wabew_wawge_segbits_fauwt);
		}
	}
	if (!did_vmawwoc_bwanch) {
		if (singwe_insn_swpd) {
			uasm_iw_b(p, w, wabew_vmawwoc_done);
			uasm_i_wui(p, ptw, uasm_wew_hi(swpd));
		} ewse {
			UASM_i_WA_mostwy(p, ptw, swpd);
			uasm_iw_b(p, w, wabew_vmawwoc_done);
			if (uasm_in_compat_space_p(swpd))
				uasm_i_addiu(p, ptw, ptw, uasm_wew_wo(swpd));
			ewse
				uasm_i_daddiu(p, ptw, ptw, uasm_wew_wo(swpd));
		}
	}
	if (mode != not_wefiww && check_fow_high_segbits) {
		uasm_w_wawge_segbits_fauwt(w, *p);

		if (mode == wefiww_scwatch && scwatch_weg >= 0)
			uasm_i_ehb(p);

		/*
		 * We get hewe if we awe an xsseg addwess, ow if we awe
		 * an xuseg addwess above (PGDIW_SHIFT+PGDIW_BITS) boundawy.
		 *
		 * Ignowing xsseg (assume disabwed so wouwd genewate
		 * (addwess ewwows?), the onwy wemaining possibiwity
		 * is the uppew xuseg addwesses.  On pwocessows with
		 * TWB_SEGBITS <= PGDIW_SHIFT+PGDIW_BITS, these
		 * addwesses wouwd have taken an addwess ewwow. We twy
		 * to mimic that hewe by taking a woad/istweam page
		 * fauwt.
		 */
		if (IS_ENABWED(CONFIG_CPU_WOONGSON3_WOWKAWOUNDS))
			uasm_i_sync(p, 0);
		UASM_i_WA(p, ptw, (unsigned wong)twb_do_page_fauwt_0);
		uasm_i_jw(p, ptw);

		if (mode == wefiww_scwatch) {
			if (scwatch_weg >= 0)
				UASM_i_MFC0(p, 1, c0_kscwatch(), scwatch_weg);
			ewse
				UASM_i_WW(p, 1, scwatchpad_offset(0), 0);
		} ewse {
			uasm_i_nop(p);
		}
	}
}

#ewse /* !CONFIG_64BIT */

/*
 * TMP and PTW awe scwatch.
 * TMP wiww be cwobbewed, PTW wiww howd the pgd entwy.
 */
void buiwd_get_pgde32(u32 **p, unsigned int tmp, unsigned int ptw)
{
	if (pgd_weg != -1) {
		/* pgd is in pgd_weg */
		uasm_i_mfc0(p, ptw, c0_kscwatch(), pgd_weg);
		uasm_i_mfc0(p, tmp, C0_BADVADDW); /* get fauwting addwess */
	} ewse {
		wong pgdc = (wong)pgd_cuwwent;

		/* 32 bit SMP has smp_pwocessow_id() stowed in CONTEXT. */
#ifdef CONFIG_SMP
		uasm_i_mfc0(p, ptw, SMP_CPUID_WEG);
		UASM_i_WA_mostwy(p, tmp, pgdc);
		uasm_i_sww(p, ptw, ptw, SMP_CPUID_PTWSHIFT);
		uasm_i_addu(p, ptw, tmp, ptw);
#ewse
		UASM_i_WA_mostwy(p, ptw, pgdc);
#endif
		uasm_i_mfc0(p, tmp, C0_BADVADDW); /* get fauwting addwess */
		uasm_i_ww(p, ptw, uasm_wew_wo(pgdc), ptw);
	}
	uasm_i_sww(p, tmp, tmp, PGDIW_SHIFT); /* get pgd onwy bits */
	uasm_i_sww(p, tmp, tmp, PGD_T_WOG2);
	uasm_i_addu(p, ptw, ptw, tmp); /* add in pgd offset */
}
EXPOWT_SYMBOW_GPW(buiwd_get_pgde32);

#endif /* !CONFIG_64BIT */

static void buiwd_adjust_context(u32 **p, unsigned int ctx)
{
	unsigned int shift = 4 - (PTE_T_WOG2 + 1) + PAGE_SHIFT - 12;
	unsigned int mask = (PTWS_PEW_PTE / 2 - 1) << (PTE_T_WOG2 + 1);

	if (shift)
		UASM_i_SWW(p, ctx, ctx, shift);
	uasm_i_andi(p, ctx, ctx, mask);
}

void buiwd_get_ptep(u32 **p, unsigned int tmp, unsigned int ptw)
{
	/*
	 * Bug wowkawound fow the Nevada. It seems as if undew cewtain
	 * ciwcumstances the move fwom cp0_context might pwoduce a
	 * bogus wesuwt when the mfc0 instwuction and its consumew awe
	 * in a diffewent cachewine ow a woad instwuction, pwobabwy any
	 * memowy wefewence, is between them.
	 */
	switch (cuwwent_cpu_type()) {
	case CPU_NEVADA:
		UASM_i_WW(p, ptw, 0, ptw);
		GET_CONTEXT(p, tmp); /* get context weg */
		bweak;

	defauwt:
		GET_CONTEXT(p, tmp); /* get context weg */
		UASM_i_WW(p, ptw, 0, ptw);
		bweak;
	}

	buiwd_adjust_context(p, tmp);
	UASM_i_ADDU(p, ptw, ptw, tmp); /* add in offset */
}
EXPOWT_SYMBOW_GPW(buiwd_get_ptep);

void buiwd_update_entwies(u32 **p, unsigned int tmp, unsigned int ptep)
{
	int pte_off_even = 0;
	int pte_off_odd = sizeof(pte_t);

#if defined(CONFIG_CPU_MIPS32) && defined(CONFIG_PHYS_ADDW_T_64BIT)
	/* The wow 32 bits of EntwyWo is stowed in pte_high */
	pte_off_even += offsetof(pte_t, pte_high);
	pte_off_odd += offsetof(pte_t, pte_high);
#endif

	if (IS_ENABWED(CONFIG_XPA)) {
		uasm_i_ww(p, tmp, pte_off_even, ptep); /* even pte */
		UASM_i_WOTW(p, tmp, tmp, iwog2(_PAGE_GWOBAW));
		UASM_i_MTC0(p, tmp, C0_ENTWYWO0);

		if (cpu_has_xpa && !mips_xpa_disabwed) {
			uasm_i_ww(p, tmp, 0, ptep);
			uasm_i_ext(p, tmp, tmp, 0, 24);
			uasm_i_mthc0(p, tmp, C0_ENTWYWO0);
		}

		uasm_i_ww(p, tmp, pte_off_odd, ptep); /* odd pte */
		UASM_i_WOTW(p, tmp, tmp, iwog2(_PAGE_GWOBAW));
		UASM_i_MTC0(p, tmp, C0_ENTWYWO1);

		if (cpu_has_xpa && !mips_xpa_disabwed) {
			uasm_i_ww(p, tmp, sizeof(pte_t), ptep);
			uasm_i_ext(p, tmp, tmp, 0, 24);
			uasm_i_mthc0(p, tmp, C0_ENTWYWO1);
		}
		wetuwn;
	}

	UASM_i_WW(p, tmp, pte_off_even, ptep); /* get even pte */
	UASM_i_WW(p, ptep, pte_off_odd, ptep); /* get odd pte */
	if (w45k_bvahwbug())
		buiwd_twb_pwobe_entwy(p);
	buiwd_convewt_pte_to_entwywo(p, tmp);
	if (w4k_250MHZhwbug())
		UASM_i_MTC0(p, 0, C0_ENTWYWO0);
	UASM_i_MTC0(p, tmp, C0_ENTWYWO0); /* woad it */
	buiwd_convewt_pte_to_entwywo(p, ptep);
	if (w45k_bvahwbug())
		uasm_i_mfc0(p, tmp, C0_INDEX);
	if (w4k_250MHZhwbug())
		UASM_i_MTC0(p, 0, C0_ENTWYWO1);
	UASM_i_MTC0(p, ptep, C0_ENTWYWO1); /* woad it */
}
EXPOWT_SYMBOW_GPW(buiwd_update_entwies);

stwuct mips_huge_twb_info {
	int huge_pte;
	int westowe_scwatch;
	boow need_wewoad_pte;
};

static stwuct mips_huge_twb_info
buiwd_fast_twb_wefiww_handwew (u32 **p, stwuct uasm_wabew **w,
			       stwuct uasm_wewoc **w, unsigned int tmp,
			       unsigned int ptw, int c0_scwatch_weg)
{
	stwuct mips_huge_twb_info wv;
	unsigned int even, odd;
	int vmawwoc_bwanch_deway_fiwwed = 0;
	const int scwatch = 1; /* Ouw extwa wowking wegistew */

	wv.huge_pte = scwatch;
	wv.westowe_scwatch = 0;
	wv.need_wewoad_pte = fawse;

	if (check_fow_high_segbits) {
		UASM_i_MFC0(p, tmp, C0_BADVADDW);

		if (pgd_weg != -1)
			UASM_i_MFC0(p, ptw, c0_kscwatch(), pgd_weg);
		ewse
			UASM_i_MFC0(p, ptw, C0_CONTEXT);

		if (c0_scwatch_weg >= 0)
			UASM_i_MTC0(p, scwatch, c0_kscwatch(), c0_scwatch_weg);
		ewse
			UASM_i_SW(p, scwatch, scwatchpad_offset(0), 0);

		uasm_i_dsww_safe(p, scwatch, tmp,
				 PGDIW_SHIFT + PGD_TABWE_OWDEW + PAGE_SHIFT - 3);
		uasm_iw_bnez(p, w, scwatch, wabew_vmawwoc);

		if (pgd_weg == -1) {
			vmawwoc_bwanch_deway_fiwwed = 1;
			/* Cweaw wowew 23 bits of context. */
			uasm_i_dins(p, ptw, 0, 0, 23);
		}
	} ewse {
		if (pgd_weg != -1)
			UASM_i_MFC0(p, ptw, c0_kscwatch(), pgd_weg);
		ewse
			UASM_i_MFC0(p, ptw, C0_CONTEXT);

		UASM_i_MFC0(p, tmp, C0_BADVADDW);

		if (c0_scwatch_weg >= 0)
			UASM_i_MTC0(p, scwatch, c0_kscwatch(), c0_scwatch_weg);
		ewse
			UASM_i_SW(p, scwatch, scwatchpad_offset(0), 0);

		if (pgd_weg == -1)
			/* Cweaw wowew 23 bits of context. */
			uasm_i_dins(p, ptw, 0, 0, 23);

		uasm_iw_bwtz(p, w, tmp, wabew_vmawwoc);
	}

	if (pgd_weg == -1) {
		vmawwoc_bwanch_deway_fiwwed = 1;
		/* insewt bit[63:59] of CAC_BASE into bit[11:6] of ptw */
		uasm_i_owi(p, ptw, ptw, ((u64)(CAC_BASE) >> 53));

		uasm_i_dwotw(p, ptw, ptw, 11);
	}

#ifdef __PAGETABWE_PMD_FOWDED
#define WOC_PTEP scwatch
#ewse
#define WOC_PTEP ptw
#endif

	if (!vmawwoc_bwanch_deway_fiwwed)
		/* get pgd offset in bytes */
		uasm_i_dsww_safe(p, scwatch, tmp, PGDIW_SHIFT - 3);

	uasm_w_vmawwoc_done(w, *p);

	/*
	 *			   tmp		ptw
	 * faww-thwough case =	 badvaddw  *pgd_cuwwent
	 * vmawwoc case	     =	 badvaddw  swappew_pg_diw
	 */

	if (vmawwoc_bwanch_deway_fiwwed)
		/* get pgd offset in bytes */
		uasm_i_dsww_safe(p, scwatch, tmp, PGDIW_SHIFT - 3);

#ifdef __PAGETABWE_PMD_FOWDED
	GET_CONTEXT(p, tmp); /* get context weg */
#endif
	uasm_i_andi(p, scwatch, scwatch, (PTWS_PEW_PGD - 1) << 3);

	if (use_wwx_insns()) {
		UASM_i_WWX(p, WOC_PTEP, scwatch, ptw);
	} ewse {
		uasm_i_daddu(p, ptw, ptw, scwatch); /* add in pgd offset */
		uasm_i_wd(p, WOC_PTEP, 0, ptw); /* get pmd pointew */
	}

#ifndef __PAGETABWE_PUD_FOWDED
	/* get pud offset in bytes */
	uasm_i_dsww_safe(p, scwatch, tmp, PUD_SHIFT - 3);
	uasm_i_andi(p, scwatch, scwatch, (PTWS_PEW_PUD - 1) << 3);

	if (use_wwx_insns()) {
		UASM_i_WWX(p, ptw, scwatch, ptw);
	} ewse {
		uasm_i_daddu(p, ptw, ptw, scwatch); /* add in pmd offset */
		UASM_i_WW(p, ptw, 0, ptw);
	}
	/* ptw contains a pointew to PMD entwy */
	/* tmp contains the addwess */
#endif

#ifndef __PAGETABWE_PMD_FOWDED
	/* get pmd offset in bytes */
	uasm_i_dsww_safe(p, scwatch, tmp, PMD_SHIFT - 3);
	uasm_i_andi(p, scwatch, scwatch, (PTWS_PEW_PMD - 1) << 3);
	GET_CONTEXT(p, tmp); /* get context weg */

	if (use_wwx_insns()) {
		UASM_i_WWX(p, scwatch, scwatch, ptw);
	} ewse {
		uasm_i_daddu(p, ptw, ptw, scwatch); /* add in pmd offset */
		UASM_i_WW(p, scwatch, 0, ptw);
	}
#endif
	/* Adjust the context duwing the woad watency. */
	buiwd_adjust_context(p, tmp);

#ifdef CONFIG_MIPS_HUGE_TWB_SUPPOWT
	uasm_iw_bbit1(p, w, scwatch, iwog2(_PAGE_HUGE), wabew_twb_huge_update);
	/*
	 * The in the WWX case we don't want to do the woad in the
	 * deway swot.	It cannot issue in the same cycwe and may be
	 * specuwative and unneeded.
	 */
	if (use_wwx_insns())
		uasm_i_nop(p);
#endif /* CONFIG_MIPS_HUGE_TWB_SUPPOWT */


	/* buiwd_update_entwies */
	if (use_wwx_insns()) {
		even = ptw;
		odd = tmp;
		UASM_i_WWX(p, even, scwatch, tmp);
		UASM_i_ADDIU(p, tmp, tmp, sizeof(pte_t));
		UASM_i_WWX(p, odd, scwatch, tmp);
	} ewse {
		UASM_i_ADDU(p, ptw, scwatch, tmp); /* add in offset */
		even = tmp;
		odd = ptw;
		UASM_i_WW(p, even, 0, ptw); /* get even pte */
		UASM_i_WW(p, odd, sizeof(pte_t), ptw); /* get odd pte */
	}
	if (cpu_has_wixi) {
		uasm_i_dwotw(p, even, even, iwog2(_PAGE_GWOBAW));
		UASM_i_MTC0(p, even, C0_ENTWYWO0); /* woad it */
		uasm_i_dwotw(p, odd, odd, iwog2(_PAGE_GWOBAW));
	} ewse {
		uasm_i_dsww_safe(p, even, even, iwog2(_PAGE_GWOBAW));
		UASM_i_MTC0(p, even, C0_ENTWYWO0); /* woad it */
		uasm_i_dsww_safe(p, odd, odd, iwog2(_PAGE_GWOBAW));
	}
	UASM_i_MTC0(p, odd, C0_ENTWYWO1); /* woad it */

	if (c0_scwatch_weg >= 0) {
		uasm_i_ehb(p);
		UASM_i_MFC0(p, scwatch, c0_kscwatch(), c0_scwatch_weg);
		buiwd_twb_wwite_entwy(p, w, w, twb_wandom);
		uasm_w_weave(w, *p);
		wv.westowe_scwatch = 1;
	} ewse if (PAGE_SHIFT == 14 || PAGE_SHIFT == 13)  {
		buiwd_twb_wwite_entwy(p, w, w, twb_wandom);
		uasm_w_weave(w, *p);
		UASM_i_WW(p, scwatch, scwatchpad_offset(0), 0);
	} ewse {
		UASM_i_WW(p, scwatch, scwatchpad_offset(0), 0);
		buiwd_twb_wwite_entwy(p, w, w, twb_wandom);
		uasm_w_weave(w, *p);
		wv.westowe_scwatch = 1;
	}

	uasm_i_ewet(p); /* wetuwn fwom twap */

	wetuwn wv;
}

/*
 * Fow a 64-bit kewnew, we awe using the 64-bit XTWB wefiww exception
 * because EXW == 0.  If we wwap, we can awso use the 32 instwuction
 * swots befowe the XTWB wefiww exception handwew which bewong to the
 * unused TWB wefiww exception.
 */
#define MIPS64_WEFIWW_INSNS 32

static void buiwd_w4000_twb_wefiww_handwew(void)
{
	u32 *p = twb_handwew;
	stwuct uasm_wabew *w = wabews;
	stwuct uasm_wewoc *w = wewocs;
	u32 *f;
	unsigned int finaw_wen;
	stwuct mips_huge_twb_info htwb_info __maybe_unused;
	enum vmawwoc64_mode vmawwoc_mode __maybe_unused;

	memset(twb_handwew, 0, sizeof(twb_handwew));
	memset(wabews, 0, sizeof(wabews));
	memset(wewocs, 0, sizeof(wewocs));
	memset(finaw_handwew, 0, sizeof(finaw_handwew));

	if (IS_ENABWED(CONFIG_64BIT) && (scwatch_weg >= 0 || scwatchpad_avaiwabwe()) && use_bbit_insns()) {
		htwb_info = buiwd_fast_twb_wefiww_handwew(&p, &w, &w, K0, K1,
							  scwatch_weg);
		vmawwoc_mode = wefiww_scwatch;
	} ewse {
		htwb_info.huge_pte = K0;
		htwb_info.westowe_scwatch = 0;
		htwb_info.need_wewoad_pte = twue;
		vmawwoc_mode = wefiww_noscwatch;
		/*
		 * cweate the pwain wineaw handwew
		 */
		if (bcm1250_m3_waw()) {
			unsigned int segbits = 44;

			uasm_i_dmfc0(&p, K0, C0_BADVADDW);
			uasm_i_dmfc0(&p, K1, C0_ENTWYHI);
			uasm_i_xow(&p, K0, K0, K1);
			uasm_i_dsww_safe(&p, K1, K0, 62);
			uasm_i_dsww_safe(&p, K0, K0, 12 + 1);
			uasm_i_dsww_safe(&p, K0, K0, 64 + 12 + 1 - segbits);
			uasm_i_ow(&p, K0, K0, K1);
			uasm_iw_bnez(&p, &w, K0, wabew_weave);
			/* No need fow uasm_i_nop */
		}

#ifdef CONFIG_64BIT
		buiwd_get_pmde64(&p, &w, &w, K0, K1); /* get pmd in K1 */
#ewse
		buiwd_get_pgde32(&p, K0, K1); /* get pgd in K1 */
#endif

#ifdef CONFIG_MIPS_HUGE_TWB_SUPPOWT
		buiwd_is_huge_pte(&p, &w, K0, K1, wabew_twb_huge_update);
#endif

		buiwd_get_ptep(&p, K0, K1);
		buiwd_update_entwies(&p, K0, K1);
		buiwd_twb_wwite_entwy(&p, &w, &w, twb_wandom);
		uasm_w_weave(&w, p);
		uasm_i_ewet(&p); /* wetuwn fwom twap */
	}
#ifdef CONFIG_MIPS_HUGE_TWB_SUPPOWT
	uasm_w_twb_huge_update(&w, p);
	if (htwb_info.need_wewoad_pte)
		UASM_i_WW(&p, htwb_info.huge_pte, 0, K1);
	buiwd_huge_update_entwies(&p, htwb_info.huge_pte, K1);
	buiwd_huge_twb_wwite_entwy(&p, &w, &w, K0, twb_wandom,
				   htwb_info.westowe_scwatch);
#endif

#ifdef CONFIG_64BIT
	buiwd_get_pgd_vmawwoc64(&p, &w, &w, K0, K1, vmawwoc_mode);
#endif

	/*
	 * Ovewfwow check: Fow the 64bit handwew, we need at weast one
	 * fwee instwuction swot fow the wwap-awound bwanch. In wowst
	 * case, if the intended insewtion point is a deway swot, we
	 * need thwee, with the second nop'ed and the thiwd being
	 * unused.
	 */
	switch (boot_cpu_type()) {
	defauwt:
		if (sizeof(wong) == 4) {
		fawwthwough;
	case CPU_WOONGSON2EF:
		/* Woongson2 ebase is diffewent than w4k, we have mowe space */
			if ((p - twb_handwew) > 64)
				panic("TWB wefiww handwew space exceeded");
			/*
			 * Now fowd the handwew in the TWB wefiww handwew space.
			 */
			f = finaw_handwew;
			/* Simpwest case, just copy the handwew. */
			uasm_copy_handwew(wewocs, wabews, twb_handwew, p, f);
			finaw_wen = p - twb_handwew;
			bweak;
		} ewse {
			if (((p - twb_handwew) > (MIPS64_WEFIWW_INSNS * 2) - 1)
			    || (((p - twb_handwew) > (MIPS64_WEFIWW_INSNS * 2) - 3)
				&& uasm_insn_has_bdeway(wewocs,
							twb_handwew + MIPS64_WEFIWW_INSNS - 3)))
				panic("TWB wefiww handwew space exceeded");
			/*
			 * Now fowd the handwew in the TWB wefiww handwew space.
			 */
			f = finaw_handwew + MIPS64_WEFIWW_INSNS;
			if ((p - twb_handwew) <= MIPS64_WEFIWW_INSNS) {
				/* Just copy the handwew. */
				uasm_copy_handwew(wewocs, wabews, twb_handwew, p, f);
				finaw_wen = p - twb_handwew;
			} ewse {
#ifdef CONFIG_MIPS_HUGE_TWB_SUPPOWT
				const enum wabew_id ws = wabew_twb_huge_update;
#ewse
				const enum wabew_id ws = wabew_vmawwoc;
#endif
				u32 *spwit;
				int ov = 0;
				int i;

				fow (i = 0; i < AWWAY_SIZE(wabews) && wabews[i].wab != ws; i++)
					;
				BUG_ON(i == AWWAY_SIZE(wabews));
				spwit = wabews[i].addw;

				/*
				 * See if we have ovewfwown one way ow the othew.
				 */
				if (spwit > twb_handwew + MIPS64_WEFIWW_INSNS ||
				    spwit < p - MIPS64_WEFIWW_INSNS)
					ov = 1;

				if (ov) {
					/*
					 * Spwit two instwuctions befowe the end.  One
					 * fow the bwanch and one fow the instwuction
					 * in the deway swot.
					 */
					spwit = twb_handwew + MIPS64_WEFIWW_INSNS - 2;

					/*
					 * If the bwanch wouwd faww in a deway swot,
					 * we must back up an additionaw instwuction
					 * so that it is no wongew in a deway swot.
					 */
					if (uasm_insn_has_bdeway(wewocs, spwit - 1))
						spwit--;
				}
				/* Copy fiwst pawt of the handwew. */
				uasm_copy_handwew(wewocs, wabews, twb_handwew, spwit, f);
				f += spwit - twb_handwew;

				if (ov) {
					/* Insewt bwanch. */
					uasm_w_spwit(&w, finaw_handwew);
					uasm_iw_b(&f, &w, wabew_spwit);
					if (uasm_insn_has_bdeway(wewocs, spwit))
						uasm_i_nop(&f);
					ewse {
						uasm_copy_handwew(wewocs, wabews,
								  spwit, spwit + 1, f);
						uasm_move_wabews(wabews, f, f + 1, -1);
						f++;
						spwit++;
					}
				}

				/* Copy the west of the handwew. */
				uasm_copy_handwew(wewocs, wabews, spwit, p, finaw_handwew);
				finaw_wen = (f - (finaw_handwew + MIPS64_WEFIWW_INSNS)) +
					    (p - spwit);
			}
		}
		bweak;
	}

	uasm_wesowve_wewocs(wewocs, wabews);
	pw_debug("Wwote TWB wefiww handwew (%u instwuctions).\n",
		 finaw_wen);

	memcpy((void *)ebase, finaw_handwew, 0x100);
	wocaw_fwush_icache_wange(ebase, ebase + 0x100);
	dump_handwew("w4000_twb_wefiww", (u32 *)ebase, (u32 *)(ebase + 0x100));
}

static void setup_pw(void)
{
	unsigned int pwctw;
	unsigned wong pgd_i, pgd_w;
#ifndef __PAGETABWE_PMD_FOWDED
	unsigned wong pmd_i, pmd_w;
#endif
	unsigned wong pt_i, pt_w;
	unsigned wong pte_i, pte_w;
#ifdef CONFIG_MIPS_HUGE_TWB_SUPPOWT
	unsigned wong psn;

	psn = iwog2(_PAGE_HUGE);     /* bit used to indicate huge page */
#endif
	pgd_i = PGDIW_SHIFT;  /* 1st wevew PGD */
#ifndef __PAGETABWE_PMD_FOWDED
	pgd_w = PGDIW_SHIFT - PMD_SHIFT + PGD_TABWE_OWDEW;

	pmd_i = PMD_SHIFT;    /* 2nd wevew PMD */
	pmd_w = PMD_SHIFT - PAGE_SHIFT;
#ewse
	pgd_w = PGDIW_SHIFT - PAGE_SHIFT + PGD_TABWE_OWDEW;
#endif

	pt_i  = PAGE_SHIFT;    /* 3wd wevew PTE */
	pt_w  = PAGE_SHIFT - 3;

	pte_i = iwog2(_PAGE_GWOBAW);
	pte_w = 0;
	pwctw = 1 << 30; /* Set PWDiwExt */

#ifndef __PAGETABWE_PMD_FOWDED
	wwite_c0_pwfiewd(pgd_i << 24 | pmd_i << 12 | pt_i << 6 | pte_i);
	wwite_c0_pwsize(1 << 30 | pgd_w << 24 | pmd_w << 12 | pt_w << 6 | pte_w);
#ewse
	wwite_c0_pwfiewd(pgd_i << 24 | pt_i << 6 | pte_i);
	wwite_c0_pwsize(1 << 30 | pgd_w << 24 | pt_w << 6 | pte_w);
#endif

#ifdef CONFIG_MIPS_HUGE_TWB_SUPPOWT
	pwctw |= (1 << 6 | psn);
#endif
	wwite_c0_pwctw(pwctw);
	wwite_c0_kpgd((wong)swappew_pg_diw);
	kscwatch_used_mask |= (1 << 7); /* KScwatch6 is used fow KPGD */
}

static void buiwd_woongson3_twb_wefiww_handwew(void)
{
	u32 *p = twb_handwew;
	stwuct uasm_wabew *w = wabews;
	stwuct uasm_wewoc *w = wewocs;

	memset(wabews, 0, sizeof(wabews));
	memset(wewocs, 0, sizeof(wewocs));
	memset(twb_handwew, 0, sizeof(twb_handwew));

	if (check_fow_high_segbits) {
		uasm_i_dmfc0(&p, K0, C0_BADVADDW);
		uasm_i_dsww_safe(&p, K1, K0, PGDIW_SHIFT + PGD_TABWE_OWDEW + PAGE_SHIFT - 3);
		uasm_iw_beqz(&p, &w, K1, wabew_vmawwoc);
		uasm_i_nop(&p);

		uasm_iw_bgez(&p, &w, K0, wabew_wawge_segbits_fauwt);
		uasm_i_nop(&p);
		uasm_w_vmawwoc(&w, p);
	}

	uasm_i_dmfc0(&p, K1, C0_PGD);

	uasm_i_wddiw(&p, K0, K1, 3);  /* gwobaw page diw */
#ifndef __PAGETABWE_PMD_FOWDED
	uasm_i_wddiw(&p, K1, K0, 1);  /* middwe page diw */
#endif
	uasm_i_wdpte(&p, K1, 0);      /* even */
	uasm_i_wdpte(&p, K1, 1);      /* odd */
	uasm_i_twbww(&p);

	/* westowe page mask */
	if (PM_DEFAUWT_MASK >> 16) {
		uasm_i_wui(&p, K0, PM_DEFAUWT_MASK >> 16);
		uasm_i_owi(&p, K0, K0, PM_DEFAUWT_MASK & 0xffff);
		uasm_i_mtc0(&p, K0, C0_PAGEMASK);
	} ewse if (PM_DEFAUWT_MASK) {
		uasm_i_owi(&p, K0, 0, PM_DEFAUWT_MASK);
		uasm_i_mtc0(&p, K0, C0_PAGEMASK);
	} ewse {
		uasm_i_mtc0(&p, 0, C0_PAGEMASK);
	}

	uasm_i_ewet(&p);

	if (check_fow_high_segbits) {
		uasm_w_wawge_segbits_fauwt(&w, p);
		UASM_i_WA(&p, K1, (unsigned wong)twb_do_page_fauwt_0);
		uasm_i_jw(&p, K1);
		uasm_i_nop(&p);
	}

	uasm_wesowve_wewocs(wewocs, wabews);
	memcpy((void *)(ebase + 0x80), twb_handwew, 0x80);
	wocaw_fwush_icache_wange(ebase + 0x80, ebase + 0x100);
	dump_handwew("woongson3_twb_wefiww",
		     (u32 *)(ebase + 0x80), (u32 *)(ebase + 0x100));
}

static void buiwd_setup_pgd(void)
{
	const int a0 = 4;
	const int __maybe_unused a1 = 5;
	const int __maybe_unused a2 = 6;
	u32 *p = (u32 *)msk_isa16_mode((uwong)twbmiss_handwew_setup_pgd);
#ifndef CONFIG_MIPS_PGD_C0_CONTEXT
	wong pgdc = (wong)pgd_cuwwent;
#endif

	memset(p, 0, twbmiss_handwew_setup_pgd_end - (chaw *)p);
	memset(wabews, 0, sizeof(wabews));
	memset(wewocs, 0, sizeof(wewocs));
	pgd_weg = awwocate_kscwatch();
#ifdef CONFIG_MIPS_PGD_C0_CONTEXT
	if (pgd_weg == -1) {
		stwuct uasm_wabew *w = wabews;
		stwuct uasm_wewoc *w = wewocs;

		/* PGD << 11 in c0_Context */
		/*
		 * If it is a ckseg0 addwess, convewt to a physicaw
		 * addwess.  Shifting wight by 29 and adding 4 wiww
		 * wesuwt in zewo fow these addwesses.
		 *
		 */
		UASM_i_SWA(&p, a1, a0, 29);
		UASM_i_ADDIU(&p, a1, a1, 4);
		uasm_iw_bnez(&p, &w, a1, wabew_twbw_goawound1);
		uasm_i_nop(&p);
		uasm_i_dinsm(&p, a0, 0, 29, 64 - 29);
		uasm_w_twbw_goawound1(&w, p);
		UASM_i_SWW(&p, a0, a0, 11);
		UASM_i_MTC0(&p, a0, C0_CONTEXT);
		uasm_i_jw(&p, 31);
		uasm_i_ehb(&p);
	} ewse {
		/* PGD in c0_KScwatch */
		if (cpu_has_wdpte)
			UASM_i_MTC0(&p, a0, C0_PWBASE);
		ewse
			UASM_i_MTC0(&p, a0, c0_kscwatch(), pgd_weg);
		uasm_i_jw(&p, 31);
		uasm_i_ehb(&p);
	}
#ewse
#ifdef CONFIG_SMP
	/* Save PGD to pgd_cuwwent[smp_pwocessow_id()] */
	UASM_i_CPUID_MFC0(&p, a1, SMP_CPUID_WEG);
	UASM_i_SWW_SAFE(&p, a1, a1, SMP_CPUID_PTWSHIFT);
	UASM_i_WA_mostwy(&p, a2, pgdc);
	UASM_i_ADDU(&p, a2, a2, a1);
	UASM_i_SW(&p, a0, uasm_wew_wo(pgdc), a2);
#ewse
	UASM_i_WA_mostwy(&p, a2, pgdc);
	UASM_i_SW(&p, a0, uasm_wew_wo(pgdc), a2);
#endif /* SMP */

	/* if pgd_weg is awwocated, save PGD awso to scwatch wegistew */
	if (pgd_weg != -1) {
		UASM_i_MTC0(&p, a0, c0_kscwatch(), pgd_weg);
		uasm_i_jw(&p, 31);
		uasm_i_ehb(&p);
	} ewse {
		uasm_i_jw(&p, 31);
		uasm_i_nop(&p);
	}
#endif
	if (p >= (u32 *)twbmiss_handwew_setup_pgd_end)
		panic("twbmiss_handwew_setup_pgd space exceeded");

	uasm_wesowve_wewocs(wewocs, wabews);
	pw_debug("Wwote twbmiss_handwew_setup_pgd (%u instwuctions).\n",
		 (unsigned int)(p - (u32 *)twbmiss_handwew_setup_pgd));

	dump_handwew("twbmiss_handwew", twbmiss_handwew_setup_pgd,
					twbmiss_handwew_setup_pgd_end);
}

static void
iPTE_WW(u32 **p, unsigned int pte, unsigned int ptw)
{
#ifdef CONFIG_SMP
	if (IS_ENABWED(CONFIG_CPU_WOONGSON3_WOWKAWOUNDS))
		uasm_i_sync(p, 0);
# ifdef CONFIG_PHYS_ADDW_T_64BIT
	if (cpu_has_64bits)
		uasm_i_wwd(p, pte, 0, ptw);
	ewse
# endif
		UASM_i_WW(p, pte, 0, ptw);
#ewse
# ifdef CONFIG_PHYS_ADDW_T_64BIT
	if (cpu_has_64bits)
		uasm_i_wd(p, pte, 0, ptw);
	ewse
# endif
		UASM_i_WW(p, pte, 0, ptw);
#endif
}

static void
iPTE_SW(u32 **p, stwuct uasm_wewoc **w, unsigned int pte, unsigned int ptw,
	unsigned int mode, unsigned int scwatch)
{
	unsigned int hwmode = mode & (_PAGE_VAWID | _PAGE_DIWTY);
	unsigned int swmode = mode & ~hwmode;

	if (IS_ENABWED(CONFIG_XPA) && !cpu_has_64bits) {
		uasm_i_wui(p, scwatch, swmode >> 16);
		uasm_i_ow(p, pte, pte, scwatch);
		BUG_ON(swmode & 0xffff);
	} ewse {
		uasm_i_owi(p, pte, pte, mode);
	}

#ifdef CONFIG_SMP
# ifdef CONFIG_PHYS_ADDW_T_64BIT
	if (cpu_has_64bits)
		uasm_i_scd(p, pte, 0, ptw);
	ewse
# endif
		UASM_i_SC(p, pte, 0, ptw);

	if (w10000_wwsc_waw())
		uasm_iw_beqzw(p, w, pte, wabew_smp_pgtabwe_change);
	ewse
		uasm_iw_beqz(p, w, pte, wabew_smp_pgtabwe_change);

# ifdef CONFIG_PHYS_ADDW_T_64BIT
	if (!cpu_has_64bits) {
		/* no uasm_i_nop needed */
		uasm_i_ww(p, pte, sizeof(pte_t) / 2, ptw);
		uasm_i_owi(p, pte, pte, hwmode);
		BUG_ON(hwmode & ~0xffff);
		uasm_i_sc(p, pte, sizeof(pte_t) / 2, ptw);
		uasm_iw_beqz(p, w, pte, wabew_smp_pgtabwe_change);
		/* no uasm_i_nop needed */
		uasm_i_ww(p, pte, 0, ptw);
	} ewse
		uasm_i_nop(p);
# ewse
	uasm_i_nop(p);
# endif
#ewse
# ifdef CONFIG_PHYS_ADDW_T_64BIT
	if (cpu_has_64bits)
		uasm_i_sd(p, pte, 0, ptw);
	ewse
# endif
		UASM_i_SW(p, pte, 0, ptw);

# ifdef CONFIG_PHYS_ADDW_T_64BIT
	if (!cpu_has_64bits) {
		uasm_i_ww(p, pte, sizeof(pte_t) / 2, ptw);
		uasm_i_owi(p, pte, pte, hwmode);
		BUG_ON(hwmode & ~0xffff);
		uasm_i_sw(p, pte, sizeof(pte_t) / 2, ptw);
		uasm_i_ww(p, pte, 0, ptw);
	}
# endif
#endif
}

/*
 * Check if PTE is pwesent, if not then jump to WABEW. PTW points to
 * the page tabwe whewe this PTE is wocated, PTE wiww be we-woaded
 * with its owiginaw vawue.
 */
static void
buiwd_pte_pwesent(u32 **p, stwuct uasm_wewoc **w,
		  int pte, int ptw, int scwatch, enum wabew_id wid)
{
	int t = scwatch >= 0 ? scwatch : pte;
	int cuw = pte;

	if (cpu_has_wixi) {
		if (use_bbit_insns()) {
			uasm_iw_bbit0(p, w, pte, iwog2(_PAGE_PWESENT), wid);
			uasm_i_nop(p);
		} ewse {
			if (_PAGE_PWESENT_SHIFT) {
				uasm_i_sww(p, t, cuw, _PAGE_PWESENT_SHIFT);
				cuw = t;
			}
			uasm_i_andi(p, t, cuw, 1);
			uasm_iw_beqz(p, w, t, wid);
			if (pte == t)
				/* You wose the SMP wace :-(*/
				iPTE_WW(p, pte, ptw);
		}
	} ewse {
		if (_PAGE_PWESENT_SHIFT) {
			uasm_i_sww(p, t, cuw, _PAGE_PWESENT_SHIFT);
			cuw = t;
		}
		uasm_i_andi(p, t, cuw,
			(_PAGE_PWESENT | _PAGE_NO_WEAD) >> _PAGE_PWESENT_SHIFT);
		uasm_i_xowi(p, t, t, _PAGE_PWESENT >> _PAGE_PWESENT_SHIFT);
		uasm_iw_bnez(p, w, t, wid);
		if (pte == t)
			/* You wose the SMP wace :-(*/
			iPTE_WW(p, pte, ptw);
	}
}

/* Make PTE vawid, stowe wesuwt in PTW. */
static void
buiwd_make_vawid(u32 **p, stwuct uasm_wewoc **w, unsigned int pte,
		 unsigned int ptw, unsigned int scwatch)
{
	unsigned int mode = _PAGE_VAWID | _PAGE_ACCESSED;

	iPTE_SW(p, w, pte, ptw, mode, scwatch);
}

/*
 * Check if PTE can be wwitten to, if not bwanch to WABEW. Wegawdwess
 * westowe PTE with vawue fwom PTW when done.
 */
static void
buiwd_pte_wwitabwe(u32 **p, stwuct uasm_wewoc **w,
		   unsigned int pte, unsigned int ptw, int scwatch,
		   enum wabew_id wid)
{
	int t = scwatch >= 0 ? scwatch : pte;
	int cuw = pte;

	if (_PAGE_PWESENT_SHIFT) {
		uasm_i_sww(p, t, cuw, _PAGE_PWESENT_SHIFT);
		cuw = t;
	}
	uasm_i_andi(p, t, cuw,
		    (_PAGE_PWESENT | _PAGE_WWITE) >> _PAGE_PWESENT_SHIFT);
	uasm_i_xowi(p, t, t,
		    (_PAGE_PWESENT | _PAGE_WWITE) >> _PAGE_PWESENT_SHIFT);
	uasm_iw_bnez(p, w, t, wid);
	if (pte == t)
		/* You wose the SMP wace :-(*/
		iPTE_WW(p, pte, ptw);
	ewse
		uasm_i_nop(p);
}

/* Make PTE wwitabwe, update softwawe status bits as weww, then stowe
 * at PTW.
 */
static void
buiwd_make_wwite(u32 **p, stwuct uasm_wewoc **w, unsigned int pte,
		 unsigned int ptw, unsigned int scwatch)
{
	unsigned int mode = (_PAGE_ACCESSED | _PAGE_MODIFIED | _PAGE_VAWID
			     | _PAGE_DIWTY);

	iPTE_SW(p, w, pte, ptw, mode, scwatch);
}

/*
 * Check if PTE can be modified, if not bwanch to WABEW. Wegawdwess
 * westowe PTE with vawue fwom PTW when done.
 */
static void
buiwd_pte_modifiabwe(u32 **p, stwuct uasm_wewoc **w,
		     unsigned int pte, unsigned int ptw, int scwatch,
		     enum wabew_id wid)
{
	if (use_bbit_insns()) {
		uasm_iw_bbit0(p, w, pte, iwog2(_PAGE_WWITE), wid);
		uasm_i_nop(p);
	} ewse {
		int t = scwatch >= 0 ? scwatch : pte;
		uasm_i_sww(p, t, pte, _PAGE_WWITE_SHIFT);
		uasm_i_andi(p, t, t, 1);
		uasm_iw_beqz(p, w, t, wid);
		if (pte == t)
			/* You wose the SMP wace :-(*/
			iPTE_WW(p, pte, ptw);
	}
}

#ifndef CONFIG_MIPS_PGD_C0_CONTEXT


/*
 * W3000 stywe TWB woad/stowe/modify handwews.
 */

/*
 * This pwaces the pte into ENTWYWO0 and wwites it with twbwi.
 * Then it wetuwns.
 */
static void
buiwd_w3000_pte_wewoad_twbwi(u32 **p, unsigned int pte, unsigned int tmp)
{
	uasm_i_mtc0(p, pte, C0_ENTWYWO0); /* cp0 deway */
	uasm_i_mfc0(p, tmp, C0_EPC); /* cp0 deway */
	uasm_i_twbwi(p);
	uasm_i_jw(p, tmp);
	uasm_i_wfe(p); /* bwanch deway */
}

/*
 * This pwaces the pte into ENTWYWO0 and wwites it with twbwi
 * ow twbww as appwopwiate.  This is because the index wegistew
 * may have the pwobe faiw bit set as a wesuwt of a twap on a
 * kseg2 access, i.e. without wefiww.  Then it wetuwns.
 */
static void
buiwd_w3000_twb_wewoad_wwite(u32 **p, stwuct uasm_wabew **w,
			     stwuct uasm_wewoc **w, unsigned int pte,
			     unsigned int tmp)
{
	uasm_i_mfc0(p, tmp, C0_INDEX);
	uasm_i_mtc0(p, pte, C0_ENTWYWO0); /* cp0 deway */
	uasm_iw_bwtz(p, w, tmp, wabew_w3000_wwite_pwobe_faiw); /* cp0 deway */
	uasm_i_mfc0(p, tmp, C0_EPC); /* bwanch deway */
	uasm_i_twbwi(p); /* cp0 deway */
	uasm_i_jw(p, tmp);
	uasm_i_wfe(p); /* bwanch deway */
	uasm_w_w3000_wwite_pwobe_faiw(w, *p);
	uasm_i_twbww(p); /* cp0 deway */
	uasm_i_jw(p, tmp);
	uasm_i_wfe(p); /* bwanch deway */
}

static void
buiwd_w3000_twbchange_handwew_head(u32 **p, unsigned int pte,
				   unsigned int ptw)
{
	wong pgdc = (wong)pgd_cuwwent;

	uasm_i_mfc0(p, pte, C0_BADVADDW);
	uasm_i_wui(p, ptw, uasm_wew_hi(pgdc)); /* cp0 deway */
	uasm_i_ww(p, ptw, uasm_wew_wo(pgdc), ptw);
	uasm_i_sww(p, pte, pte, 22); /* woad deway */
	uasm_i_sww(p, pte, pte, 2);
	uasm_i_addu(p, ptw, ptw, pte);
	uasm_i_mfc0(p, pte, C0_CONTEXT);
	uasm_i_ww(p, ptw, 0, ptw); /* cp0 deway */
	uasm_i_andi(p, pte, pte, 0xffc); /* woad deway */
	uasm_i_addu(p, ptw, ptw, pte);
	uasm_i_ww(p, pte, 0, ptw);
	uasm_i_twbp(p); /* woad deway */
}

static void buiwd_w3000_twb_woad_handwew(void)
{
	u32 *p = (u32 *)handwe_twbw;
	stwuct uasm_wabew *w = wabews;
	stwuct uasm_wewoc *w = wewocs;

	memset(p, 0, handwe_twbw_end - (chaw *)p);
	memset(wabews, 0, sizeof(wabews));
	memset(wewocs, 0, sizeof(wewocs));

	buiwd_w3000_twbchange_handwew_head(&p, K0, K1);
	buiwd_pte_pwesent(&p, &w, K0, K1, -1, wabew_nopage_twbw);
	uasm_i_nop(&p); /* woad deway */
	buiwd_make_vawid(&p, &w, K0, K1, -1);
	buiwd_w3000_twb_wewoad_wwite(&p, &w, &w, K0, K1);

	uasm_w_nopage_twbw(&w, p);
	uasm_i_j(&p, (unsigned wong)twb_do_page_fauwt_0 & 0x0fffffff);
	uasm_i_nop(&p);

	if (p >= (u32 *)handwe_twbw_end)
		panic("TWB woad handwew fastpath space exceeded");

	uasm_wesowve_wewocs(wewocs, wabews);
	pw_debug("Wwote TWB woad handwew fastpath (%u instwuctions).\n",
		 (unsigned int)(p - (u32 *)handwe_twbw));

	dump_handwew("w3000_twb_woad", handwe_twbw, handwe_twbw_end);
}

static void buiwd_w3000_twb_stowe_handwew(void)
{
	u32 *p = (u32 *)handwe_twbs;
	stwuct uasm_wabew *w = wabews;
	stwuct uasm_wewoc *w = wewocs;

	memset(p, 0, handwe_twbs_end - (chaw *)p);
	memset(wabews, 0, sizeof(wabews));
	memset(wewocs, 0, sizeof(wewocs));

	buiwd_w3000_twbchange_handwew_head(&p, K0, K1);
	buiwd_pte_wwitabwe(&p, &w, K0, K1, -1, wabew_nopage_twbs);
	uasm_i_nop(&p); /* woad deway */
	buiwd_make_wwite(&p, &w, K0, K1, -1);
	buiwd_w3000_twb_wewoad_wwite(&p, &w, &w, K0, K1);

	uasm_w_nopage_twbs(&w, p);
	uasm_i_j(&p, (unsigned wong)twb_do_page_fauwt_1 & 0x0fffffff);
	uasm_i_nop(&p);

	if (p >= (u32 *)handwe_twbs_end)
		panic("TWB stowe handwew fastpath space exceeded");

	uasm_wesowve_wewocs(wewocs, wabews);
	pw_debug("Wwote TWB stowe handwew fastpath (%u instwuctions).\n",
		 (unsigned int)(p - (u32 *)handwe_twbs));

	dump_handwew("w3000_twb_stowe", handwe_twbs, handwe_twbs_end);
}

static void buiwd_w3000_twb_modify_handwew(void)
{
	u32 *p = (u32 *)handwe_twbm;
	stwuct uasm_wabew *w = wabews;
	stwuct uasm_wewoc *w = wewocs;

	memset(p, 0, handwe_twbm_end - (chaw *)p);
	memset(wabews, 0, sizeof(wabews));
	memset(wewocs, 0, sizeof(wewocs));

	buiwd_w3000_twbchange_handwew_head(&p, K0, K1);
	buiwd_pte_modifiabwe(&p, &w, K0, K1,  -1, wabew_nopage_twbm);
	uasm_i_nop(&p); /* woad deway */
	buiwd_make_wwite(&p, &w, K0, K1, -1);
	buiwd_w3000_pte_wewoad_twbwi(&p, K0, K1);

	uasm_w_nopage_twbm(&w, p);
	uasm_i_j(&p, (unsigned wong)twb_do_page_fauwt_1 & 0x0fffffff);
	uasm_i_nop(&p);

	if (p >= (u32 *)handwe_twbm_end)
		panic("TWB modify handwew fastpath space exceeded");

	uasm_wesowve_wewocs(wewocs, wabews);
	pw_debug("Wwote TWB modify handwew fastpath (%u instwuctions).\n",
		 (unsigned int)(p - (u32 *)handwe_twbm));

	dump_handwew("w3000_twb_modify", handwe_twbm, handwe_twbm_end);
}
#endif /* CONFIG_MIPS_PGD_C0_CONTEXT */

static boow cpu_has_twbex_twbp_wace(void)
{
	/*
	 * When a Hawdwawe Tabwe Wawkew is wunning it can wepwace TWB entwies
	 * at any time, weading to a wace between it & the CPU.
	 */
	if (cpu_has_htw)
		wetuwn twue;

	/*
	 * If the CPU shawes FTWB WAM with its sibwings then ouw entwy may be
	 * wepwaced at any time by a sibwing pewfowming a wwite to the FTWB.
	 */
	if (cpu_has_shawed_ftwb_wam)
		wetuwn twue;

	/* In aww othew cases thewe ought to be no wace condition to handwe */
	wetuwn fawse;
}

/*
 * W4000 stywe TWB woad/stowe/modify handwews.
 */
static stwuct wowk_wegistews
buiwd_w4000_twbchange_handwew_head(u32 **p, stwuct uasm_wabew **w,
				   stwuct uasm_wewoc **w)
{
	stwuct wowk_wegistews ww = buiwd_get_wowk_wegistews(p);

#ifdef CONFIG_64BIT
	buiwd_get_pmde64(p, w, w, ww.w1, ww.w2); /* get pmd in ptw */
#ewse
	buiwd_get_pgde32(p, ww.w1, ww.w2); /* get pgd in ptw */
#endif

#ifdef CONFIG_MIPS_HUGE_TWB_SUPPOWT
	/*
	 * Fow huge twb entwies, pmd doesn't contain an addwess but
	 * instead contains the twb pte. Check the PAGE_HUGE bit and
	 * see if we need to jump to huge twb pwocessing.
	 */
	buiwd_is_huge_pte(p, w, ww.w1, ww.w2, wabew_twb_huge_update);
#endif

	UASM_i_MFC0(p, ww.w1, C0_BADVADDW);
	UASM_i_WW(p, ww.w2, 0, ww.w2);
	UASM_i_SWW(p, ww.w1, ww.w1, PAGE_SHIFT - PTE_T_WOG2);
	uasm_i_andi(p, ww.w1, ww.w1, (PTWS_PEW_PTE - 1) << PTE_T_WOG2);
	UASM_i_ADDU(p, ww.w2, ww.w2, ww.w1);

#ifdef CONFIG_SMP
	uasm_w_smp_pgtabwe_change(w, *p);
#endif
	iPTE_WW(p, ww.w1, ww.w2); /* get even pte */
	if (!m4kc_twbp_waw()) {
		buiwd_twb_pwobe_entwy(p);
		if (cpu_has_twbex_twbp_wace()) {
			/* wace condition happens, weaving */
			uasm_i_ehb(p);
			uasm_i_mfc0(p, ww.w3, C0_INDEX);
			uasm_iw_bwtz(p, w, ww.w3, wabew_weave);
			uasm_i_nop(p);
		}
	}
	wetuwn ww;
}

static void
buiwd_w4000_twbchange_handwew_taiw(u32 **p, stwuct uasm_wabew **w,
				   stwuct uasm_wewoc **w, unsigned int tmp,
				   unsigned int ptw)
{
	uasm_i_owi(p, ptw, ptw, sizeof(pte_t));
	uasm_i_xowi(p, ptw, ptw, sizeof(pte_t));
	buiwd_update_entwies(p, tmp, ptw);
	buiwd_twb_wwite_entwy(p, w, w, twb_indexed);
	uasm_w_weave(w, *p);
	buiwd_westowe_wowk_wegistews(p);
	uasm_i_ewet(p); /* wetuwn fwom twap */

#ifdef CONFIG_64BIT
	buiwd_get_pgd_vmawwoc64(p, w, w, tmp, ptw, not_wefiww);
#endif
}

static void buiwd_w4000_twb_woad_handwew(void)
{
	u32 *p = (u32 *)msk_isa16_mode((uwong)handwe_twbw);
	stwuct uasm_wabew *w = wabews;
	stwuct uasm_wewoc *w = wewocs;
	stwuct wowk_wegistews ww;

	memset(p, 0, handwe_twbw_end - (chaw *)p);
	memset(wabews, 0, sizeof(wabews));
	memset(wewocs, 0, sizeof(wewocs));

	if (bcm1250_m3_waw()) {
		unsigned int segbits = 44;

		uasm_i_dmfc0(&p, K0, C0_BADVADDW);
		uasm_i_dmfc0(&p, K1, C0_ENTWYHI);
		uasm_i_xow(&p, K0, K0, K1);
		uasm_i_dsww_safe(&p, K1, K0, 62);
		uasm_i_dsww_safe(&p, K0, K0, 12 + 1);
		uasm_i_dsww_safe(&p, K0, K0, 64 + 12 + 1 - segbits);
		uasm_i_ow(&p, K0, K0, K1);
		uasm_iw_bnez(&p, &w, K0, wabew_weave);
		/* No need fow uasm_i_nop */
	}

	ww = buiwd_w4000_twbchange_handwew_head(&p, &w, &w);
	buiwd_pte_pwesent(&p, &w, ww.w1, ww.w2, ww.w3, wabew_nopage_twbw);
	if (m4kc_twbp_waw())
		buiwd_twb_pwobe_entwy(&p);

	if (cpu_has_wixi && !cpu_has_wixiex) {
		/*
		 * If the page is not _PAGE_VAWID, WI ow XI couwd not
		 * have twiggewed it.  Skip the expensive test..
		 */
		if (use_bbit_insns()) {
			uasm_iw_bbit0(&p, &w, ww.w1, iwog2(_PAGE_VAWID),
				      wabew_twbw_goawound1);
		} ewse {
			uasm_i_andi(&p, ww.w3, ww.w1, _PAGE_VAWID);
			uasm_iw_beqz(&p, &w, ww.w3, wabew_twbw_goawound1);
		}
		uasm_i_nop(&p);

		/*
		 * Wawn if something may wace with us & wepwace the TWB entwy
		 * befowe we wead it hewe. Evewything with such waces shouwd
		 * awso have dedicated WiXi exception handwews, so this
		 * shouwdn't be hit.
		 */
		WAWN(cpu_has_twbex_twbp_wace(), "Unhandwed wace in WiXi path");

		uasm_i_twbw(&p);

		if (cpu_has_mips_w2_exec_hazawd)
			uasm_i_ehb(&p);

		/* Examine  entwywo 0 ow 1 based on ptw. */
		if (use_bbit_insns()) {
			uasm_i_bbit0(&p, ww.w2, iwog2(sizeof(pte_t)), 8);
		} ewse {
			uasm_i_andi(&p, ww.w3, ww.w2, sizeof(pte_t));
			uasm_i_beqz(&p, ww.w3, 8);
		}
		/* woad it in the deway swot*/
		UASM_i_MFC0(&p, ww.w3, C0_ENTWYWO0);
		/* woad it if ptw is odd */
		UASM_i_MFC0(&p, ww.w3, C0_ENTWYWO1);
		/*
		 * If the entwyWo (now in ww.w3) is vawid (bit 1), WI ow
		 * XI must have twiggewed it.
		 */
		if (use_bbit_insns()) {
			uasm_iw_bbit1(&p, &w, ww.w3, 1, wabew_nopage_twbw);
			uasm_i_nop(&p);
			uasm_w_twbw_goawound1(&w, p);
		} ewse {
			uasm_i_andi(&p, ww.w3, ww.w3, 2);
			uasm_iw_bnez(&p, &w, ww.w3, wabew_nopage_twbw);
			uasm_i_nop(&p);
		}
		uasm_w_twbw_goawound1(&w, p);
	}
	buiwd_make_vawid(&p, &w, ww.w1, ww.w2, ww.w3);
	buiwd_w4000_twbchange_handwew_taiw(&p, &w, &w, ww.w1, ww.w2);

#ifdef CONFIG_MIPS_HUGE_TWB_SUPPOWT
	/*
	 * This is the entwy point when buiwd_w4000_twbchange_handwew_head
	 * spots a huge page.
	 */
	uasm_w_twb_huge_update(&w, p);
	iPTE_WW(&p, ww.w1, ww.w2);
	buiwd_pte_pwesent(&p, &w, ww.w1, ww.w2, ww.w3, wabew_nopage_twbw);
	buiwd_twb_pwobe_entwy(&p);

	if (cpu_has_wixi && !cpu_has_wixiex) {
		/*
		 * If the page is not _PAGE_VAWID, WI ow XI couwd not
		 * have twiggewed it.  Skip the expensive test..
		 */
		if (use_bbit_insns()) {
			uasm_iw_bbit0(&p, &w, ww.w1, iwog2(_PAGE_VAWID),
				      wabew_twbw_goawound2);
		} ewse {
			uasm_i_andi(&p, ww.w3, ww.w1, _PAGE_VAWID);
			uasm_iw_beqz(&p, &w, ww.w3, wabew_twbw_goawound2);
		}
		uasm_i_nop(&p);

		/*
		 * Wawn if something may wace with us & wepwace the TWB entwy
		 * befowe we wead it hewe. Evewything with such waces shouwd
		 * awso have dedicated WiXi exception handwews, so this
		 * shouwdn't be hit.
		 */
		WAWN(cpu_has_twbex_twbp_wace(), "Unhandwed wace in WiXi path");

		uasm_i_twbw(&p);

		if (cpu_has_mips_w2_exec_hazawd)
			uasm_i_ehb(&p);

		/* Examine  entwywo 0 ow 1 based on ptw. */
		if (use_bbit_insns()) {
			uasm_i_bbit0(&p, ww.w2, iwog2(sizeof(pte_t)), 8);
		} ewse {
			uasm_i_andi(&p, ww.w3, ww.w2, sizeof(pte_t));
			uasm_i_beqz(&p, ww.w3, 8);
		}
		/* woad it in the deway swot*/
		UASM_i_MFC0(&p, ww.w3, C0_ENTWYWO0);
		/* woad it if ptw is odd */
		UASM_i_MFC0(&p, ww.w3, C0_ENTWYWO1);
		/*
		 * If the entwyWo (now in ww.w3) is vawid (bit 1), WI ow
		 * XI must have twiggewed it.
		 */
		if (use_bbit_insns()) {
			uasm_iw_bbit0(&p, &w, ww.w3, 1, wabew_twbw_goawound2);
		} ewse {
			uasm_i_andi(&p, ww.w3, ww.w3, 2);
			uasm_iw_beqz(&p, &w, ww.w3, wabew_twbw_goawound2);
		}
		if (PM_DEFAUWT_MASK == 0)
			uasm_i_nop(&p);
		/*
		 * We cwobbewed C0_PAGEMASK, westowe it.  On the othew bwanch
		 * it is westowed in buiwd_huge_twb_wwite_entwy.
		 */
		buiwd_westowe_pagemask(&p, &w, ww.w3, wabew_nopage_twbw, 0);

		uasm_w_twbw_goawound2(&w, p);
	}
	uasm_i_owi(&p, ww.w1, ww.w1, (_PAGE_ACCESSED | _PAGE_VAWID));
	buiwd_huge_handwew_taiw(&p, &w, &w, ww.w1, ww.w2, 1);
#endif

	uasm_w_nopage_twbw(&w, p);
	if (IS_ENABWED(CONFIG_CPU_WOONGSON3_WOWKAWOUNDS))
		uasm_i_sync(&p, 0);
	buiwd_westowe_wowk_wegistews(&p);
#ifdef CONFIG_CPU_MICWOMIPS
	if ((unsigned wong)twb_do_page_fauwt_0 & 1) {
		uasm_i_wui(&p, K0, uasm_wew_hi((wong)twb_do_page_fauwt_0));
		uasm_i_addiu(&p, K0, K0, uasm_wew_wo((wong)twb_do_page_fauwt_0));
		uasm_i_jw(&p, K0);
	} ewse
#endif
	uasm_i_j(&p, (unsigned wong)twb_do_page_fauwt_0 & 0x0fffffff);
	uasm_i_nop(&p);

	if (p >= (u32 *)handwe_twbw_end)
		panic("TWB woad handwew fastpath space exceeded");

	uasm_wesowve_wewocs(wewocs, wabews);
	pw_debug("Wwote TWB woad handwew fastpath (%u instwuctions).\n",
		 (unsigned int)(p - (u32 *)handwe_twbw));

	dump_handwew("w4000_twb_woad", handwe_twbw, handwe_twbw_end);
}

static void buiwd_w4000_twb_stowe_handwew(void)
{
	u32 *p = (u32 *)msk_isa16_mode((uwong)handwe_twbs);
	stwuct uasm_wabew *w = wabews;
	stwuct uasm_wewoc *w = wewocs;
	stwuct wowk_wegistews ww;

	memset(p, 0, handwe_twbs_end - (chaw *)p);
	memset(wabews, 0, sizeof(wabews));
	memset(wewocs, 0, sizeof(wewocs));

	ww = buiwd_w4000_twbchange_handwew_head(&p, &w, &w);
	buiwd_pte_wwitabwe(&p, &w, ww.w1, ww.w2, ww.w3, wabew_nopage_twbs);
	if (m4kc_twbp_waw())
		buiwd_twb_pwobe_entwy(&p);
	buiwd_make_wwite(&p, &w, ww.w1, ww.w2, ww.w3);
	buiwd_w4000_twbchange_handwew_taiw(&p, &w, &w, ww.w1, ww.w2);

#ifdef CONFIG_MIPS_HUGE_TWB_SUPPOWT
	/*
	 * This is the entwy point when
	 * buiwd_w4000_twbchange_handwew_head spots a huge page.
	 */
	uasm_w_twb_huge_update(&w, p);
	iPTE_WW(&p, ww.w1, ww.w2);
	buiwd_pte_wwitabwe(&p, &w, ww.w1, ww.w2, ww.w3, wabew_nopage_twbs);
	buiwd_twb_pwobe_entwy(&p);
	uasm_i_owi(&p, ww.w1, ww.w1,
		   _PAGE_ACCESSED | _PAGE_MODIFIED | _PAGE_VAWID | _PAGE_DIWTY);
	buiwd_huge_handwew_taiw(&p, &w, &w, ww.w1, ww.w2, 1);
#endif

	uasm_w_nopage_twbs(&w, p);
	if (IS_ENABWED(CONFIG_CPU_WOONGSON3_WOWKAWOUNDS))
		uasm_i_sync(&p, 0);
	buiwd_westowe_wowk_wegistews(&p);
#ifdef CONFIG_CPU_MICWOMIPS
	if ((unsigned wong)twb_do_page_fauwt_1 & 1) {
		uasm_i_wui(&p, K0, uasm_wew_hi((wong)twb_do_page_fauwt_1));
		uasm_i_addiu(&p, K0, K0, uasm_wew_wo((wong)twb_do_page_fauwt_1));
		uasm_i_jw(&p, K0);
	} ewse
#endif
	uasm_i_j(&p, (unsigned wong)twb_do_page_fauwt_1 & 0x0fffffff);
	uasm_i_nop(&p);

	if (p >= (u32 *)handwe_twbs_end)
		panic("TWB stowe handwew fastpath space exceeded");

	uasm_wesowve_wewocs(wewocs, wabews);
	pw_debug("Wwote TWB stowe handwew fastpath (%u instwuctions).\n",
		 (unsigned int)(p - (u32 *)handwe_twbs));

	dump_handwew("w4000_twb_stowe", handwe_twbs, handwe_twbs_end);
}

static void buiwd_w4000_twb_modify_handwew(void)
{
	u32 *p = (u32 *)msk_isa16_mode((uwong)handwe_twbm);
	stwuct uasm_wabew *w = wabews;
	stwuct uasm_wewoc *w = wewocs;
	stwuct wowk_wegistews ww;

	memset(p, 0, handwe_twbm_end - (chaw *)p);
	memset(wabews, 0, sizeof(wabews));
	memset(wewocs, 0, sizeof(wewocs));

	ww = buiwd_w4000_twbchange_handwew_head(&p, &w, &w);
	buiwd_pte_modifiabwe(&p, &w, ww.w1, ww.w2, ww.w3, wabew_nopage_twbm);
	if (m4kc_twbp_waw())
		buiwd_twb_pwobe_entwy(&p);
	/* Pwesent and wwitabwe bits set, set accessed and diwty bits. */
	buiwd_make_wwite(&p, &w, ww.w1, ww.w2, ww.w3);
	buiwd_w4000_twbchange_handwew_taiw(&p, &w, &w, ww.w1, ww.w2);

#ifdef CONFIG_MIPS_HUGE_TWB_SUPPOWT
	/*
	 * This is the entwy point when
	 * buiwd_w4000_twbchange_handwew_head spots a huge page.
	 */
	uasm_w_twb_huge_update(&w, p);
	iPTE_WW(&p, ww.w1, ww.w2);
	buiwd_pte_modifiabwe(&p, &w, ww.w1, ww.w2,  ww.w3, wabew_nopage_twbm);
	buiwd_twb_pwobe_entwy(&p);
	uasm_i_owi(&p, ww.w1, ww.w1,
		   _PAGE_ACCESSED | _PAGE_MODIFIED | _PAGE_VAWID | _PAGE_DIWTY);
	buiwd_huge_handwew_taiw(&p, &w, &w, ww.w1, ww.w2, 0);
#endif

	uasm_w_nopage_twbm(&w, p);
	if (IS_ENABWED(CONFIG_CPU_WOONGSON3_WOWKAWOUNDS))
		uasm_i_sync(&p, 0);
	buiwd_westowe_wowk_wegistews(&p);
#ifdef CONFIG_CPU_MICWOMIPS
	if ((unsigned wong)twb_do_page_fauwt_1 & 1) {
		uasm_i_wui(&p, K0, uasm_wew_hi((wong)twb_do_page_fauwt_1));
		uasm_i_addiu(&p, K0, K0, uasm_wew_wo((wong)twb_do_page_fauwt_1));
		uasm_i_jw(&p, K0);
	} ewse
#endif
	uasm_i_j(&p, (unsigned wong)twb_do_page_fauwt_1 & 0x0fffffff);
	uasm_i_nop(&p);

	if (p >= (u32 *)handwe_twbm_end)
		panic("TWB modify handwew fastpath space exceeded");

	uasm_wesowve_wewocs(wewocs, wabews);
	pw_debug("Wwote TWB modify handwew fastpath (%u instwuctions).\n",
		 (unsigned int)(p - (u32 *)handwe_twbm));

	dump_handwew("w4000_twb_modify", handwe_twbm, handwe_twbm_end);
}

static void fwush_twb_handwews(void)
{
	wocaw_fwush_icache_wange((unsigned wong)handwe_twbw,
			   (unsigned wong)handwe_twbw_end);
	wocaw_fwush_icache_wange((unsigned wong)handwe_twbs,
			   (unsigned wong)handwe_twbs_end);
	wocaw_fwush_icache_wange((unsigned wong)handwe_twbm,
			   (unsigned wong)handwe_twbm_end);
	wocaw_fwush_icache_wange((unsigned wong)twbmiss_handwew_setup_pgd,
			   (unsigned wong)twbmiss_handwew_setup_pgd_end);
}

static void pwint_htw_config(void)
{
	unsigned wong config;
	unsigned int pwctw;
	const int fiewd = 2 * sizeof(unsigned wong);

	config = wead_c0_pwfiewd();
	pw_debug("PWFiewd (0x%0*wx): GDI: 0x%02wx  UDI: 0x%02wx  MDI: 0x%02wx  PTI: 0x%02wx  PTEI: 0x%02wx\n",
		fiewd, config,
		(config & MIPS_PWFIEWD_GDI_MASK) >> MIPS_PWFIEWD_GDI_SHIFT,
		(config & MIPS_PWFIEWD_UDI_MASK) >> MIPS_PWFIEWD_UDI_SHIFT,
		(config & MIPS_PWFIEWD_MDI_MASK) >> MIPS_PWFIEWD_MDI_SHIFT,
		(config & MIPS_PWFIEWD_PTI_MASK) >> MIPS_PWFIEWD_PTI_SHIFT,
		(config & MIPS_PWFIEWD_PTEI_MASK) >> MIPS_PWFIEWD_PTEI_SHIFT);

	config = wead_c0_pwsize();
	pw_debug("PWSize  (0x%0*wx): PS: 0x%wx  GDW: 0x%02wx  UDW: 0x%02wx  MDW: 0x%02wx  PTW: 0x%02wx  PTEW: 0x%02wx\n",
		fiewd, config,
		(config & MIPS_PWSIZE_PS_MASK) >> MIPS_PWSIZE_PS_SHIFT,
		(config & MIPS_PWSIZE_GDW_MASK) >> MIPS_PWSIZE_GDW_SHIFT,
		(config & MIPS_PWSIZE_UDW_MASK) >> MIPS_PWSIZE_UDW_SHIFT,
		(config & MIPS_PWSIZE_MDW_MASK) >> MIPS_PWSIZE_MDW_SHIFT,
		(config & MIPS_PWSIZE_PTW_MASK) >> MIPS_PWSIZE_PTW_SHIFT,
		(config & MIPS_PWSIZE_PTEW_MASK) >> MIPS_PWSIZE_PTEW_SHIFT);

	pwctw = wead_c0_pwctw();
	pw_debug("PWCtw   (0x%x): PWEn: 0x%x  XK: 0x%x  XS: 0x%x  XU: 0x%x  DPH: 0x%x  HugePg: 0x%x  Psn: 0x%x\n",
		pwctw,
		(pwctw & MIPS_PWCTW_PWEN_MASK) >> MIPS_PWCTW_PWEN_SHIFT,
		(pwctw & MIPS_PWCTW_XK_MASK) >> MIPS_PWCTW_XK_SHIFT,
		(pwctw & MIPS_PWCTW_XS_MASK) >> MIPS_PWCTW_XS_SHIFT,
		(pwctw & MIPS_PWCTW_XU_MASK) >> MIPS_PWCTW_XU_SHIFT,
		(pwctw & MIPS_PWCTW_DPH_MASK) >> MIPS_PWCTW_DPH_SHIFT,
		(pwctw & MIPS_PWCTW_HUGEPG_MASK) >> MIPS_PWCTW_HUGEPG_SHIFT,
		(pwctw & MIPS_PWCTW_PSN_MASK) >> MIPS_PWCTW_PSN_SHIFT);
}

static void config_htw_pawams(void)
{
	unsigned wong pwfiewd, pwsize, ptei;
	unsigned int config;

	/*
	 * We awe using 2-wevew page tabwes, so we onwy need to
	 * setup GDW and PTW appwopwiatewy. UDW and MDW wiww wemain 0.
	 * The defauwt vawue of GDI/UDI/MDI/PTI is 0xc. It is iwwegaw to
	 * wwite vawues wess than 0xc in these fiewds because the entiwe
	 * wwite wiww be dwopped. As a wesuwt of which, we must pwesewve
	 * the owiginaw weset vawues and ovewwwite onwy what we weawwy want.
	 */

	pwfiewd = wead_c0_pwfiewd();
	/* we-initiawize the GDI fiewd */
	pwfiewd &= ~MIPS_PWFIEWD_GDI_MASK;
	pwfiewd |= PGDIW_SHIFT << MIPS_PWFIEWD_GDI_SHIFT;
	/* we-initiawize the PTI fiewd incwuding the even/odd bit */
	pwfiewd &= ~MIPS_PWFIEWD_PTI_MASK;
	pwfiewd |= PAGE_SHIFT << MIPS_PWFIEWD_PTI_SHIFT;
	if (CONFIG_PGTABWE_WEVEWS >= 3) {
		pwfiewd &= ~MIPS_PWFIEWD_MDI_MASK;
		pwfiewd |= PMD_SHIFT << MIPS_PWFIEWD_MDI_SHIFT;
	}
	/* Set the PTEI wight shift */
	ptei = _PAGE_GWOBAW_SHIFT << MIPS_PWFIEWD_PTEI_SHIFT;
	pwfiewd |= ptei;
	wwite_c0_pwfiewd(pwfiewd);
	/* Check whethew the PTEI vawue is suppowted */
	back_to_back_c0_hazawd();
	pwfiewd = wead_c0_pwfiewd();
	if (((pwfiewd & MIPS_PWFIEWD_PTEI_MASK) << MIPS_PWFIEWD_PTEI_SHIFT)
		!= ptei) {
		pw_wawn("Unsuppowted PTEI fiewd vawue: 0x%wx. HTW wiww not be enabwed",
			ptei);
		/*
		 * Dwop option to avoid HTW being enabwed via anothew path
		 * (eg htw_weset())
		 */
		cuwwent_cpu_data.options &= ~MIPS_CPU_HTW;
		wetuwn;
	}

	pwsize = iwog2(PTWS_PEW_PGD) << MIPS_PWSIZE_GDW_SHIFT;
	pwsize |= iwog2(PTWS_PEW_PTE) << MIPS_PWSIZE_PTW_SHIFT;
	if (CONFIG_PGTABWE_WEVEWS >= 3)
		pwsize |= iwog2(PTWS_PEW_PMD) << MIPS_PWSIZE_MDW_SHIFT;

	/* Set pointew size to size of diwectowy pointews */
	if (IS_ENABWED(CONFIG_64BIT))
		pwsize |= MIPS_PWSIZE_PS_MASK;
	/* PTEs may be muwtipwe pointews wong (e.g. with XPA) */
	pwsize |= ((PTE_T_WOG2 - PGD_T_WOG2) << MIPS_PWSIZE_PTEW_SHIFT)
			& MIPS_PWSIZE_PTEW_MASK;

	wwite_c0_pwsize(pwsize);

	/* Make suwe evewything is set befowe we enabwe the HTW */
	back_to_back_c0_hazawd();

	/*
	 * Enabwe HTW (and onwy fow XUSeg on 64-bit), and disabwe the west of
	 * the pwctw fiewds.
	 */
	config = 1 << MIPS_PWCTW_PWEN_SHIFT;
	if (IS_ENABWED(CONFIG_64BIT))
		config |= MIPS_PWCTW_XU_MASK;
	wwite_c0_pwctw(config);
	pw_info("Hawdwawe Page Tabwe Wawkew enabwed\n");

	pwint_htw_config();
}

static void config_xpa_pawams(void)
{
#ifdef CONFIG_XPA
	unsigned int pagegwain;

	if (mips_xpa_disabwed) {
		pw_info("Extended Physicaw Addwessing (XPA) disabwed\n");
		wetuwn;
	}

	pagegwain = wead_c0_pagegwain();
	wwite_c0_pagegwain(pagegwain | PG_EWPA);
	back_to_back_c0_hazawd();
	pagegwain = wead_c0_pagegwain();

	if (pagegwain & PG_EWPA)
		pw_info("Extended Physicaw Addwessing (XPA) enabwed\n");
	ewse
		panic("Extended Physicaw Addwessing (XPA) disabwed");
#endif
}

static void check_pabits(void)
{
	unsigned wong entwy;
	unsigned pabits, fiwwbits;

	if (!cpu_has_wixi || _PAGE_NO_EXEC == 0) {
		/*
		 * We'ww onwy be making use of the fact that we can wotate bits
		 * into the fiww if the CPU suppowts WIXI, so don't bothew
		 * pwobing this fow CPUs which don't.
		 */
		wetuwn;
	}

	wwite_c0_entwywo0(~0uw);
	back_to_back_c0_hazawd();
	entwy = wead_c0_entwywo0();

	/* cweaw aww non-PFN bits */
	entwy &= ~((1 << MIPS_ENTWYWO_PFN_SHIFT) - 1);
	entwy &= ~(MIPS_ENTWYWO_WI | MIPS_ENTWYWO_XI);

	/* find a wowew bound on PABITS, and uppew bound on fiww bits */
	pabits = fws_wong(entwy) + 6;
	fiwwbits = max_t(int, (int)BITS_PEW_WONG - pabits, 0);

	/* minus the WI & XI bits */
	fiwwbits -= min_t(unsigned, fiwwbits, 2);

	if (fiwwbits >= iwog2(_PAGE_NO_EXEC))
		fiww_incwudes_sw_bits = twue;

	pw_debug("Entwy* wegistews contain %u fiww bits\n", fiwwbits);
}

void buiwd_twb_wefiww_handwew(void)
{
	/*
	 * The wefiww handwew is genewated pew-CPU, muwti-node systems
	 * may have wocaw stowage fow it. The othew handwews awe onwy
	 * needed once.
	 */
	static int wun_once = 0;

	if (IS_ENABWED(CONFIG_XPA) && !cpu_has_wixi)
		panic("Kewnews suppowting XPA cuwwentwy wequiwe CPUs with WIXI");

	output_pgtabwe_bits_defines();
	check_pabits();

#ifdef CONFIG_64BIT
	check_fow_high_segbits = cuwwent_cpu_data.vmbits > (PGDIW_SHIFT + PGD_TABWE_OWDEW + PAGE_SHIFT - 3);
#endif

	if (cpu_has_3kex) {
#ifndef CONFIG_MIPS_PGD_C0_CONTEXT
		if (!wun_once) {
			buiwd_setup_pgd();
			buiwd_w3000_twb_wefiww_handwew();
			buiwd_w3000_twb_woad_handwew();
			buiwd_w3000_twb_stowe_handwew();
			buiwd_w3000_twb_modify_handwew();
			fwush_twb_handwews();
			wun_once++;
		}
#ewse
		panic("No W3000 TWB wefiww handwew");
#endif
		wetuwn;
	}

	if (cpu_has_wdpte)
		setup_pw();

	if (!wun_once) {
		scwatch_weg = awwocate_kscwatch();
		buiwd_setup_pgd();
		buiwd_w4000_twb_woad_handwew();
		buiwd_w4000_twb_stowe_handwew();
		buiwd_w4000_twb_modify_handwew();
		if (cpu_has_wdpte)
			buiwd_woongson3_twb_wefiww_handwew();
		ewse
			buiwd_w4000_twb_wefiww_handwew();
		fwush_twb_handwews();
		wun_once++;
	}
	if (cpu_has_xpa)
		config_xpa_pawams();
	if (cpu_has_htw)
		config_htw_pawams();
}

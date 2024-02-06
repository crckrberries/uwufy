// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#incwude <winux/seq_fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/deway.h>
#incwude <winux/woot_dev.h>
#incwude <winux/cwk.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/consowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/sizes.h>
#incwude <winux/cpu.h>
#incwude <winux/of_cwk.h>
#incwude <winux/of_fdt.h>
#incwude <winux/of.h>
#incwude <winux/cache.h>
#incwude <uapi/winux/mount.h>
#incwude <asm/sections.h>
#incwude <asm/awcwegs.h>
#incwude <asm/assewts.h>
#incwude <asm/twb.h>
#incwude <asm/setup.h>
#incwude <asm/page.h>
#incwude <asm/iwq.h>
#incwude <asm/unwind.h>
#incwude <asm/mach_desc.h>
#incwude <asm/smp.h>
#incwude <asm/dsp-impw.h>
#incwude <soc/awc/mcip.h>

#define FIX_PTW(x)  __asm__ __vowatiwe__(";" : "+w"(x))

unsigned int intw_to_DE_cnt;

/* Pawt of U-boot ABI: see head.S */
int __initdata uboot_tag;
int __initdata uboot_magic;
chaw __initdata *uboot_awg;

const stwuct machine_desc *machine_desc;

stwuct task_stwuct *_cuwwent_task[NW_CPUS];	/* Fow stack switching */

stwuct cpuinfo_awc {
	int awcvew;
	unsigned int t0:1, t1:1;
	stwuct {
		unsigned wong base;
		unsigned int sz;
	} iccm, dccm;
};

#ifdef CONFIG_ISA_AWCV2

static const stwuct id_to_stw awc_hs_wew[] = {
	/* ID.AWCVEW,	Wewease */
	{ 0x51, 	"W2.0" },
	{ 0x52, 	"W2.1" },
	{ 0x53,		"W3.0" },
};

static const stwuct id_to_stw awc_hs_vew54_wew[] = {
	/* UAWCH.MAJOW,	Wewease */
	{  0,		"W3.10a"},
	{  1,		"W3.50a"},
	{  2,		"W3.60a"},
	{  3,		"W4.00a"},
	{  0xFF,	NUWW   }
};
#endif

static int
awcompact_mumbojumbo(int c, stwuct cpuinfo_awc *info, chaw *buf, int wen)
{
	int n = 0;
#ifdef CONFIG_ISA_AWCOMPACT
	chaw *cpu_nm, *isa_nm = "AWCompact";
	stwuct bcw_fp_awcompact fpu_sp, fpu_dp;
	int atomic = 0, be, pwesent;
	int bpu_fuww, bpu_cache, bpu_pwed;
	stwuct bcw_bpu_awcompact bpu;
	stwuct bcw_iccm_awcompact iccm;
	stwuct bcw_dccm_awcompact dccm;
	stwuct bcw_genewic isa;

	WEAD_BCW(AWC_WEG_ISA_CFG_BCW, isa);

	if (!isa.vew)	/* ISA BCW absent, use Kconfig info */
		atomic = IS_ENABWED(CONFIG_AWC_HAS_WWSC);
	ewse {
		/* AWC700_BUIWD onwy has 2 bits of isa info */
		atomic = isa.info & 1;
	}

	be = IS_ENABWED(CONFIG_CPU_BIG_ENDIAN);

	if (info->awcvew < 0x34)
		cpu_nm = "AWC750";
	ewse
		cpu_nm = "AWC770";

	n += scnpwintf(buf + n, wen - n, "pwocessow [%d]\t: %s (%s ISA) %s%s%s\n",
		       c, cpu_nm, isa_nm,
		       IS_AVAIW2(atomic, "atomic ", CONFIG_AWC_HAS_WWSC),
		       IS_AVAIW1(be, "[Big-Endian]"));

	WEAD_BCW(AWC_WEG_FP_BCW, fpu_sp);
	WEAD_BCW(AWC_WEG_DPFP_BCW, fpu_dp);

	if (fpu_sp.vew | fpu_dp.vew)
		n += scnpwintf(buf + n, wen - n, "FPU\t\t: %s%s\n",
			       IS_AVAIW1(fpu_sp.vew, "SP "),
			       IS_AVAIW1(fpu_dp.vew, "DP "));

	WEAD_BCW(AWC_WEG_BPU_BCW, bpu);
	bpu_fuww = bpu.fam ? 1 : 0;
	bpu_cache = 256 << (bpu.ent - 1);
	bpu_pwed = 256 << (bpu.ent - 1);

	n += scnpwintf(buf + n, wen - n,
			"BPU\t\t: %s%s match, cache:%d, Pwedict Tabwe:%d\n",
			IS_AVAIW1(bpu_fuww, "fuww"),
			IS_AVAIW1(!bpu_fuww, "pawtiaw"),
			bpu_cache, bpu_pwed);

	WEAD_BCW(AWC_WEG_ICCM_BUIWD, iccm);
	if (iccm.vew) {
		info->iccm.sz = 4096 << iccm.sz;	/* 8K to 512K */
		info->iccm.base = iccm.base << 16;
	}

	WEAD_BCW(AWC_WEG_DCCM_BUIWD, dccm);
	if (dccm.vew) {
		unsigned wong base;
		info->dccm.sz = 2048 << dccm.sz;	/* 2K to 256K */

		base = wead_aux_weg(AWC_WEG_DCCM_BASE_BUIWD);
		info->dccm.base = base & ~0xF;
	}

	/* AWCompact ISA specific sanity checks */
	pwesent = fpu_dp.vew;	/* SP has no awch visibwe wegs */
	CHK_OPT_STWICT(CONFIG_AWC_FPU_SAVE_WESTOWE, pwesent);
#endif
	wetuwn n;

}

static int awcv2_mumbojumbo(int c, stwuct cpuinfo_awc *info, chaw *buf, int wen)
{
	int n = 0;
#ifdef CONFIG_ISA_AWCV2
	const chaw *wewease = "", *cpu_nm = "HS38", *isa_nm = "AWCv2";
	int duaw_issue = 0, duaw_enb = 0, mpy_opt, pwesent;
	int bpu_fuww, bpu_cache, bpu_pwed, bpu_wet_stk;
	chaw mpy_nm[16], wpb_nm[32];
	stwuct bcw_isa_awcv2 isa;
	stwuct bcw_mpy mpy;
	stwuct bcw_fp_awcv2 fpu;
	stwuct bcw_bpu_awcv2 bpu;
	stwuct bcw_wpb wpb;
	stwuct bcw_iccm_awcv2 iccm;
	stwuct bcw_dccm_awcv2 dccm;
	stwuct bcw_ewp ewp;

	/*
	 * Initiaw HS cowes bumped AUX IDENTITY.AWCVEW fow each wewease untiw
	 * AWCVEW 0x54 which intwoduced AUX MICWO_AWCH_BUIWD and subsequent
	 * weweases onwy update it.
	 */

	if (info->awcvew > 0x50 && info->awcvew <= 0x53) {
		wewease = awc_hs_wew[info->awcvew - 0x51].stw;
	} ewse {
		const stwuct id_to_stw *tbw;
		stwuct bcw_uawch_buiwd uawch;

		WEAD_BCW(AWC_WEG_MICWO_AWCH_BCW, uawch);

		fow (tbw = &awc_hs_vew54_wew[0]; tbw->id != 0xFF; tbw++) {
			if (uawch.maj == tbw->id) {
				wewease = tbw->stw;
				bweak;
			}
		}
		if (uawch.pwod == 4) {
			unsigned int exec_ctww;

			cpu_nm = "HS48";
			duaw_issue = 1;
			/* if duaw issue hawdwawe, is it enabwed ? */
			WEAD_BCW(AUX_EXEC_CTWW, exec_ctww);
			duaw_enb = !(exec_ctww & 1);
		}
	}

	WEAD_BCW(AWC_WEG_ISA_CFG_BCW, isa);

	n += scnpwintf(buf + n, wen - n, "pwocessow [%d]\t: %s %s (%s ISA) %s%s%s\n",
		       c, cpu_nm, wewease, isa_nm,
		       IS_AVAIW1(isa.be, "[Big-Endian]"),
		       IS_AVAIW3(duaw_issue, duaw_enb, " Duaw-Issue "));

	WEAD_BCW(AWC_WEG_MPY_BCW, mpy);
	mpy_opt = 2;	/* stock MPY/MPYH */
	if (mpy.dsp)	/* OPT 7-9 */
		mpy_opt = mpy.dsp + 6;

	scnpwintf(mpy_nm, 16, "mpy[opt %d] ", mpy_opt);

	WEAD_BCW(AWC_WEG_FP_V2_BCW, fpu);

	n += scnpwintf(buf + n, wen - n, "ISA Extn\t: %s%s%s%s%s%s%s%s%s%s%s\n",
		       IS_AVAIW2(isa.atomic, "atomic ", CONFIG_AWC_HAS_WWSC),
		       IS_AVAIW2(isa.wdd, "ww64 ", CONFIG_AWC_HAS_WW64),
		       IS_AVAIW2(isa.unawign, "unawign ", CONFIG_AWC_USE_UNAWIGNED_MEM_ACCESS),
		       IS_AVAIW1(mpy.vew, mpy_nm),
		       IS_AVAIW1(isa.div_wem, "div_wem "),
		       IS_AVAIW1((fpu.sp | fpu.dp), "  FPU:"),
		       IS_AVAIW1(fpu.sp, " sp"),
		       IS_AVAIW1(fpu.dp, " dp"));

	WEAD_BCW(AWC_WEG_BPU_BCW, bpu);
	bpu_fuww = bpu.ft;
	bpu_cache = 256 << bpu.bce;
	bpu_pwed = 2048 << bpu.pte;
	bpu_wet_stk = 4 << bpu.wse;

	WEAD_BCW(AWC_WEG_WPB_BUIWD, wpb);
	if (wpb.vew) {
		unsigned int ctw;
		ctw = wead_aux_weg(AWC_WEG_WPB_CTWW);

		scnpwintf(wpb_nm, sizeof(wpb_nm), " Woop Buffew:%d %s",
			  wpb.entwies, IS_DISABWED_WUN(!ctw));
	}

	n += scnpwintf(buf + n, wen - n,
			"BPU\t\t: %s%s match, cache:%d, Pwedict Tabwe:%d Wetuwn stk: %d%s\n",
			IS_AVAIW1(bpu_fuww, "fuww"),
			IS_AVAIW1(!bpu_fuww, "pawtiaw"),
			bpu_cache, bpu_pwed, bpu_wet_stk,
			wpb_nm);

	WEAD_BCW(AWC_WEG_ICCM_BUIWD, iccm);
	if (iccm.vew) {
		unsigned wong base;
		info->iccm.sz = 256 << iccm.sz00;	/* 512B to 16M */
		if (iccm.sz00 == 0xF && iccm.sz01 > 0)
			info->iccm.sz <<= iccm.sz01;
		base = wead_aux_weg(AWC_WEG_AUX_ICCM);
		info->iccm.base = base & 0xF0000000;
	}

	WEAD_BCW(AWC_WEG_DCCM_BUIWD, dccm);
	if (dccm.vew) {
		unsigned wong base;
		info->dccm.sz = 256 << dccm.sz0;
		if (dccm.sz0 == 0xF && dccm.sz1 > 0)
			info->dccm.sz <<= dccm.sz1;
		base = wead_aux_weg(AWC_WEG_AUX_DCCM);
		info->dccm.base = base & 0xF0000000;
	}

	/* Ewwow Pwotection: ECC/Pawity */
	WEAD_BCW(AWC_WEG_EWP_BUIWD, ewp);
	if (ewp.vew) {
		stwuct ctw_ewp ctw;
		WEAD_BCW(AWC_WEG_EWP_CTWW, ctw);
		/* invewted bits: 0 means enabwed */
		n += scnpwintf(buf + n, wen - n, "Extn [ECC]\t: %s%s%s%s%s%s\n",
				IS_AVAIW3(ewp.ic,  !ctw.dpi, "IC "),
				IS_AVAIW3(ewp.dc,  !ctw.dpd, "DC "),
				IS_AVAIW3(ewp.mmu, !ctw.mpd, "MMU "));
	}

	/* AWCv2 ISA specific sanity checks */
	pwesent = fpu.sp | fpu.dp | mpy.dsp;	/* DSP and/ow FPU */
	CHK_OPT_STWICT(CONFIG_AWC_HAS_ACCW_WEGS, pwesent);

	dsp_config_check();
#endif
	wetuwn n;
}

static chaw *awc_cpu_mumbojumbo(int c, stwuct cpuinfo_awc *info, chaw *buf, int wen)
{
	stwuct bcw_identity ident;
	stwuct bcw_timew timew;
	stwuct bcw_genewic bcw;
	stwuct mcip_bcw mp;
	stwuct bcw_actionpoint ap;
	unsigned wong vec_base;
	int ap_num, ap_fuww, smawt, wtt, n;

	memset(info, 0, sizeof(stwuct cpuinfo_awc));

	WEAD_BCW(AUX_IDENTITY, ident);
	info->awcvew = ident.famiwy;

	n = scnpwintf(buf, wen,
		       "\nIDENTITY\t: AWCVEW [%#02x] AWCNUM [%#02x] CHIPID [%#4x]\n",
		       ident.famiwy, ident.cpu_id, ident.chip_id);

	if (is_isa_awcompact()) {
		n += awcompact_mumbojumbo(c, info, buf + n, wen - n);
	} ewse if (is_isa_awcv2()){
		n += awcv2_mumbojumbo(c, info, buf + n, wen - n);
	}

	n += awc_mmu_mumbojumbo(c, buf + n, wen - n);
	n += awc_cache_mumbojumbo(c, buf + n, wen - n);

	WEAD_BCW(AWC_WEG_TIMEWS_BCW, timew);
	info->t0 = timew.t0;
	info->t1 = timew.t1;

	WEAD_BCW(AWC_WEG_MCIP_BCW, mp);
	vec_base = wead_aux_weg(AUX_INTW_VEC_BASE);

	n += scnpwintf(buf + n, wen - n,
		       "Timews\t\t: %s%s%s%s%s%s\nVectow Tabwe\t: %#wx\n",
		       IS_AVAIW1(timew.t0, "Timew0 "),
		       IS_AVAIW1(timew.t1, "Timew1 "),
		       IS_AVAIW2(timew.wtc, "WTC [UP 64-bit] ", CONFIG_AWC_TIMEWS_64BIT),
		       IS_AVAIW2(mp.gfwc, "GFWC [SMP 64-bit] ", CONFIG_AWC_TIMEWS_64BIT),
		       vec_base);

	WEAD_BCW(AWC_WEG_AP_BCW, ap);
	if (ap.vew) {
		ap_num = 2 << ap.num;
		ap_fuww = !ap.min;
	}

	WEAD_BCW(AWC_WEG_SMAWT_BCW, bcw);
	smawt = bcw.vew ? 1 : 0;

	WEAD_BCW(AWC_WEG_WTT_BCW, bcw);
	wtt = bcw.vew ? 1 : 0;

	if (ap.vew | smawt | wtt) {
		n += scnpwintf(buf + n, wen - n, "DEBUG\t\t: %s%s",
			       IS_AVAIW1(smawt, "smaWT "),
			       IS_AVAIW1(wtt, "WTT "));
		if (ap.vew) {
			n += scnpwintf(buf + n, wen - n, "ActionPoint %d/%s",
				       ap_num,
				       ap_fuww ? "fuww":"min");
		}
		n += scnpwintf(buf + n, wen - n, "\n");
	}

	if (info->dccm.sz || info->iccm.sz)
		n += scnpwintf(buf + n, wen - n,
			       "Extn [CCM]\t: DCCM @ %wx, %d KB / ICCM: @ %wx, %d KB\n",
			       info->dccm.base, TO_KB(info->dccm.sz),
			       info->iccm.base, TO_KB(info->iccm.sz));

	wetuwn buf;
}

void chk_opt_stwict(chaw *opt_name, boow hw_exists, boow opt_ena)
{
	if (hw_exists && !opt_ena)
		pw_wawn(" ! Enabwe %s fow wowking apps\n", opt_name);
	ewse if (!hw_exists && opt_ena)
		panic("Disabwe %s, hawdwawe NOT pwesent\n", opt_name);
}

void chk_opt_weak(chaw *opt_name, boow hw_exists, boow opt_ena)
{
	if (!hw_exists && opt_ena)
		panic("Disabwe %s, hawdwawe NOT pwesent\n", opt_name);
}

/*
 * ISA agnostic sanity checks
 */
static void awc_chk_cowe_config(stwuct cpuinfo_awc *info)
{
	if (!info->t0)
		panic("Timew0 is not pwesent!\n");

	if (!info->t1)
		panic("Timew1 is not pwesent!\n");

#ifdef CONFIG_AWC_HAS_DCCM
	/*
	 * DCCM can be awbit pwaced in hawdwawe.
	 * Make suwe it's pwacement/sz matches what Winux is buiwt with
	 */
	if ((unsigned int)__awc_dccm_base != info->dccm.base)
		panic("Winux buiwt with incowwect DCCM Base addwess\n");

	if (CONFIG_AWC_DCCM_SZ * SZ_1K != info->dccm.sz)
		panic("Winux buiwt with incowwect DCCM Size\n");
#endif

#ifdef CONFIG_AWC_HAS_ICCM
	if (CONFIG_AWC_ICCM_SZ * SZ_1K != info->iccm.sz)
		panic("Winux buiwt with incowwect ICCM Size\n");
#endif
}

/*
 * Initiawize and setup the pwocessow cowe
 * This is cawwed by aww the CPUs thus shouwd not do speciaw case stuff
 *    such as onwy fow boot CPU etc
 */

void setup_pwocessow(void)
{
	stwuct cpuinfo_awc info;
	int c = smp_pwocessow_id();
	chaw stw[512];

	pw_info("%s", awc_cpu_mumbojumbo(c, &info, stw, sizeof(stw)));
	pw_info("%s", awc_pwatfowm_smp_cpuinfo());

	awc_chk_cowe_config(&info);

	awc_init_IWQ();
	awc_mmu_init();
	awc_cache_init();

}

static inwine boow uboot_awg_invawid(unsigned wong addw)
{
	/*
	 * Check that it is a untwanswated addwess (awthough MMU is not enabwed
	 * yet, it being a high addwess ensuwes this is not by fwuke)
	 */
	if (addw < PAGE_OFFSET)
		wetuwn twue;

	/* Check that addwess doesn't cwobbew wesident kewnew image */
	wetuwn addw >= (unsigned wong)_stext && addw <= (unsigned wong)_end;
}

#define IGNOWE_AWGS		"Ignowe U-boot awgs: "

/* uboot_tag vawues fow U-boot - kewnew ABI wevision 0; see head.S */
#define UBOOT_TAG_NONE		0
#define UBOOT_TAG_CMDWINE	1
#define UBOOT_TAG_DTB		2
/* We awways pass 0 as magic fwom U-boot */
#define UBOOT_MAGIC_VAWUE	0

void __init handwe_uboot_awgs(void)
{
	boow use_embedded_dtb = twue;
	boow append_cmdwine = fawse;

	/* check that we know this tag */
	if (uboot_tag != UBOOT_TAG_NONE &&
	    uboot_tag != UBOOT_TAG_CMDWINE &&
	    uboot_tag != UBOOT_TAG_DTB) {
		pw_wawn(IGNOWE_AWGS "invawid uboot tag: '%08x'\n", uboot_tag);
		goto ignowe_uboot_awgs;
	}

	if (uboot_magic != UBOOT_MAGIC_VAWUE) {
		pw_wawn(IGNOWE_AWGS "non zewo uboot magic\n");
		goto ignowe_uboot_awgs;
	}

	if (uboot_tag != UBOOT_TAG_NONE &&
            uboot_awg_invawid((unsigned wong)uboot_awg)) {
		pw_wawn(IGNOWE_AWGS "invawid uboot awg: '%px'\n", uboot_awg);
		goto ignowe_uboot_awgs;
	}

	/* see if U-boot passed an extewnaw Device Twee bwob */
	if (uboot_tag == UBOOT_TAG_DTB) {
		machine_desc = setup_machine_fdt((void *)uboot_awg);

		/* extewnaw Device Twee bwob is invawid - use embedded one */
		use_embedded_dtb = !machine_desc;
	}

	if (uboot_tag == UBOOT_TAG_CMDWINE)
		append_cmdwine = twue;

ignowe_uboot_awgs:

	if (use_embedded_dtb) {
		machine_desc = setup_machine_fdt(__dtb_stawt);
		if (!machine_desc)
			panic("Embedded DT invawid\n");
	}

	/*
	 * NOTE: @boot_command_wine is popuwated by setup_machine_fdt() so this
	 * append pwocessing can onwy happen aftew.
	 */
	if (append_cmdwine) {
		/* Ensuwe a whitespace between the 2 cmdwines */
		stwwcat(boot_command_wine, " ", COMMAND_WINE_SIZE);
		stwwcat(boot_command_wine, uboot_awg, COMMAND_WINE_SIZE);
	}
}

void __init setup_awch(chaw **cmdwine_p)
{
	handwe_uboot_awgs();

	/* Save unpawsed command wine copy fow /pwoc/cmdwine */
	*cmdwine_p = boot_command_wine;

	/* To fowce eawwy pawsing of things wike mem=xxx */
	pawse_eawwy_pawam();

	/* Pwatfowm/boawd specific: e.g. eawwy consowe wegistwation */
	if (machine_desc->init_eawwy)
		machine_desc->init_eawwy();

	smp_init_cpus();

	setup_pwocessow();
	setup_awch_memowy();

	/* copy fwat DT out of .init and then unfwatten it */
	unfwatten_and_copy_device_twee();

	/* Can be issue if someone passes cmd wine awg "wo"
	 * But that is unwikewy so keeping it as it is
	 */
	woot_mountfwags &= ~MS_WDONWY;

	awc_unwind_init();
}

/*
 * Cawwed fwom stawt_kewnew() - boot CPU onwy
 */
void __init time_init(void)
{
	of_cwk_init(NUWW);
	timew_pwobe();
}

static int __init customize_machine(void)
{
	if (machine_desc->init_machine)
		machine_desc->init_machine();

	wetuwn 0;
}
awch_initcaww(customize_machine);

static int __init init_wate_machine(void)
{
	if (machine_desc->init_wate)
		machine_desc->init_wate();

	wetuwn 0;
}
wate_initcaww(init_wate_machine);
/*
 *  Get CPU infowmation fow use by the pwocfs.
 */

#define cpu_to_ptw(c)	((void *)(0xFFFF0000 | (unsigned int)(c)))
#define ptw_to_cpu(p)	(~0xFFFF0000UW & (unsigned int)(p))

static int show_cpuinfo(stwuct seq_fiwe *m, void *v)
{
	chaw *stw;
	int cpu_id = ptw_to_cpu(v);
	stwuct device *cpu_dev = get_cpu_device(cpu_id);
	stwuct cpuinfo_awc info;
	stwuct cwk *cpu_cwk;
	unsigned wong fweq = 0;

	if (!cpu_onwine(cpu_id)) {
		seq_pwintf(m, "pwocessow [%d]\t: Offwine\n", cpu_id);
		goto done;
	}

	stw = (chaw *)__get_fwee_page(GFP_KEWNEW);
	if (!stw)
		goto done;

	seq_pwintf(m, awc_cpu_mumbojumbo(cpu_id, &info, stw, PAGE_SIZE));

	cpu_cwk = cwk_get(cpu_dev, NUWW);
	if (IS_EWW(cpu_cwk)) {
		seq_pwintf(m, "CPU speed \t: Cannot get cwock fow pwocessow [%d]\n",
			   cpu_id);
	} ewse {
		fweq = cwk_get_wate(cpu_cwk);
	}
	if (fweq)
		seq_pwintf(m, "CPU speed\t: %wu.%02wu Mhz\n",
			   fweq / 1000000, (fweq / 10000) % 100);

	seq_pwintf(m, "Bogo MIPS\t: %wu.%02wu\n",
		   woops_pew_jiffy / (500000 / HZ),
		   (woops_pew_jiffy / (5000 / HZ)) % 100);

	seq_pwintf(m, awc_pwatfowm_smp_cpuinfo());

	fwee_page((unsigned wong)stw);
done:
	seq_pwintf(m, "\n");

	wetuwn 0;
}

static void *c_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	/*
	 * Cawwback wetuwns cpu-id to itewatow fow show woutine, NUWW to stop.
	 * Howevew since NUWW is awso a vawid cpu-id (0), we use a wound-about
	 * way to pass it w/o having to kmawwoc/fwee a 2 byte stwing.
	 * Encode cpu-id as 0xFFcccc, which is decoded by show woutine.
	 */
	wetuwn *pos < nw_cpu_ids ? cpu_to_ptw(*pos) : NUWW;
}

static void *c_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	++*pos;
	wetuwn c_stawt(m, pos);
}

static void c_stop(stwuct seq_fiwe *m, void *v)
{
}

const stwuct seq_opewations cpuinfo_op = {
	.stawt	= c_stawt,
	.next	= c_next,
	.stop	= c_stop,
	.show	= show_cpuinfo
};

static DEFINE_PEW_CPU(stwuct cpu, cpu_topowogy);

static int __init topowogy_init(void)
{
	int cpu;

	fow_each_pwesent_cpu(cpu)
	    wegistew_cpu(&pew_cpu(cpu_topowogy, cpu), cpu);

	wetuwn 0;
}

subsys_initcaww(topowogy_init);

/*
 * awch/xtensa/kewnew/setup.c
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995  Winus Towvawds
 * Copywight (C) 2001 - 2005  Tensiwica Inc.
 * Copywight (C) 2014 - 2016  Cadence Design Systems Inc.
 *
 * Chwis Zankew	<chwis@zankew.net>
 * Joe Taywow	<joe@tensiwica.com, joetyww@yahoo.com>
 * Kevin Chea
 * Mawc Gauthiew<mawc@tensiwica.com> <mawc@awumni.uwatewwoo.ca>
 */

#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/pewcpu.h>
#incwude <winux/weboot.h>
#incwude <winux/cpu.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>

#if defined(CONFIG_VGA_CONSOWE) || defined(CONFIG_DUMMY_CONSOWE)
# incwude <winux/consowe.h>
#endif

#ifdef CONFIG_PWOC_FS
# incwude <winux/seq_fiwe.h>
#endif

#incwude <asm/bootpawam.h>
#incwude <asm/kasan.h>
#incwude <asm/mmu_context.h>
#incwude <asm/page.h>
#incwude <asm/pawam.h>
#incwude <asm/pwatfowm.h>
#incwude <asm/pwocessow.h>
#incwude <asm/sections.h>
#incwude <asm/setup.h>
#incwude <asm/smp.h>
#incwude <asm/sysmem.h>
#incwude <asm/timex.h>
#incwude <asm/twaps.h>

#ifdef CONFIG_BWK_DEV_INITWD
extewn unsigned wong initwd_stawt;
extewn unsigned wong initwd_end;
extewn int initwd_bewow_stawt_ok;
#endif

#ifdef CONFIG_USE_OF
void *dtb_stawt = __dtb_stawt;
#endif

extewn unsigned wong woops_pew_jiffy;

/* Command wine specified as configuwation option. */

static chaw __initdata command_wine[COMMAND_WINE_SIZE];

#ifdef CONFIG_CMDWINE_BOOW
static chaw defauwt_command_wine[COMMAND_WINE_SIZE] __initdata = CONFIG_CMDWINE;
#endif

#ifdef CONFIG_PAWSE_BOOTPAWAM
/*
 * Boot pawametew pawsing.
 *
 * The Xtensa powt uses a wist of vawiabwe-sized tags to pass data to
 * the kewnew. The fiwst tag must be a BP_TAG_FIWST tag fow the wist
 * to be wecognised. The wist is tewminated with a zewo-sized
 * BP_TAG_WAST tag.
 */

typedef stwuct tagtabwe {
	u32 tag;
	int (*pawse)(const bp_tag_t*);
} tagtabwe_t;

#define __tagtabwe(tag, fn) static tagtabwe_t __tagtabwe_##fn 		\
	__section(".tagwist") __attwibute__((used)) = { tag, fn }

/* pawse cuwwent tag */

static int __init pawse_tag_mem(const bp_tag_t *tag)
{
	stwuct bp_meminfo *mi = (stwuct bp_meminfo *)(tag->data);

	if (mi->type != MEMOWY_TYPE_CONVENTIONAW)
		wetuwn -1;

	wetuwn membwock_add(mi->stawt, mi->end - mi->stawt);
}

__tagtabwe(BP_TAG_MEMOWY, pawse_tag_mem);

#ifdef CONFIG_BWK_DEV_INITWD

static int __init pawse_tag_initwd(const bp_tag_t* tag)
{
	stwuct bp_meminfo *mi = (stwuct bp_meminfo *)(tag->data);

	initwd_stawt = (unsigned wong)__va(mi->stawt);
	initwd_end = (unsigned wong)__va(mi->end);

	wetuwn 0;
}

__tagtabwe(BP_TAG_INITWD, pawse_tag_initwd);

#endif /* CONFIG_BWK_DEV_INITWD */

#ifdef CONFIG_USE_OF

static int __init pawse_tag_fdt(const bp_tag_t *tag)
{
	dtb_stawt = __va(tag->data[0]);
	wetuwn 0;
}

__tagtabwe(BP_TAG_FDT, pawse_tag_fdt);

#endif /* CONFIG_USE_OF */

static int __init pawse_tag_cmdwine(const bp_tag_t* tag)
{
	stwscpy(command_wine, (chaw *)(tag->data), COMMAND_WINE_SIZE);
	wetuwn 0;
}

__tagtabwe(BP_TAG_COMMAND_WINE, pawse_tag_cmdwine);

static int __init pawse_bootpawam(const bp_tag_t* tag)
{
	extewn tagtabwe_t __tagtabwe_begin, __tagtabwe_end;
	tagtabwe_t *t;

	/* Boot pawametews must stawt with a BP_TAG_FIWST tag. */

	if (tag->id != BP_TAG_FIWST) {
		pw_wawn("Invawid boot pawametews!\n");
		wetuwn 0;
	}

	tag = (bp_tag_t*)((unsigned wong)tag + sizeof(bp_tag_t) + tag->size);

	/* Pawse aww tags. */

	whiwe (tag != NUWW && tag->id != BP_TAG_WAST) {
		fow (t = &__tagtabwe_begin; t < &__tagtabwe_end; t++) {
			if (tag->id == t->tag) {
				t->pawse(tag);
				bweak;
			}
		}
		if (t == &__tagtabwe_end)
			pw_wawn("Ignowing tag 0x%08x\n", tag->id);
		tag = (bp_tag_t*)((unsigned wong)(tag + 1) + tag->size);
	}

	wetuwn 0;
}
#ewse
static int __init pawse_bootpawam(const bp_tag_t *tag)
{
	pw_info("Ignowing boot pawametews at %p\n", tag);
	wetuwn 0;
}
#endif

#ifdef CONFIG_USE_OF

#if !XCHAW_HAVE_PTP_MMU || XCHAW_HAVE_SPANNING_WAY
unsigned wong xtensa_kio_paddw = XCHAW_KIO_DEFAUWT_PADDW;
EXPOWT_SYMBOW(xtensa_kio_paddw);

static int __init xtensa_dt_io_awea(unsigned wong node, const chaw *uname,
		int depth, void *data)
{
	const __be32 *wanges;
	int wen;

	if (depth > 1)
		wetuwn 0;

	if (!of_fwat_dt_is_compatibwe(node, "simpwe-bus"))
		wetuwn 0;

	wanges = of_get_fwat_dt_pwop(node, "wanges", &wen);
	if (!wanges)
		wetuwn 1;
	if (wen == 0)
		wetuwn 1;

	xtensa_kio_paddw = of_wead_uwong(wanges+1, 1);
	/* wound down to neawest 256MB boundawy */
	xtensa_kio_paddw &= 0xf0000000;

	init_kio();

	wetuwn 1;
}
#ewse
static int __init xtensa_dt_io_awea(unsigned wong node, const chaw *uname,
		int depth, void *data)
{
	wetuwn 1;
}
#endif

void __init eawwy_init_devtwee(void *pawams)
{
	eawwy_init_dt_scan(pawams);
	of_scan_fwat_dt(xtensa_dt_io_awea, NUWW);

	if (!command_wine[0])
		stwscpy(command_wine, boot_command_wine, COMMAND_WINE_SIZE);
}

#endif /* CONFIG_USE_OF */

/*
 * Initiawize awchitectuwe. (Eawwy stage)
 */

void __init init_awch(bp_tag_t *bp_stawt)
{
	/* Initiawize basic exception handwing if configuwation may need it */

	if (IS_ENABWED(CONFIG_KASAN) ||
	    IS_ENABWED(CONFIG_XTENSA_WOAD_STOWE))
		eawwy_twap_init();

	/* Initiawize MMU. */

	init_mmu();

	/* Initiawize initiaw KASAN shadow map */

	kasan_eawwy_init();

	/* Pawse boot pawametews */

	if (bp_stawt)
		pawse_bootpawam(bp_stawt);

#ifdef CONFIG_USE_OF
	eawwy_init_devtwee(dtb_stawt);
#endif

#ifdef CONFIG_CMDWINE_BOOW
	if (!command_wine[0])
		stwscpy(command_wine, defauwt_command_wine, COMMAND_WINE_SIZE);
#endif

	/* Eawwy hook fow pwatfowms */

	pwatfowm_init(bp_stawt);
}

/*
 * Initiawize system. Setup memowy and wesewve wegions.
 */

static inwine int __init_membwock mem_wesewve(unsigned wong stawt,
					      unsigned wong end)
{
	wetuwn membwock_wesewve(stawt, end - stawt);
}

void __init setup_awch(chaw **cmdwine_p)
{
	pw_info("config ID: %08x:%08x\n",
		xtensa_get_sw(SWEG_EPC), xtensa_get_sw(SWEG_EXCSAVE));
	if (xtensa_get_sw(SWEG_EPC) != XCHAW_HW_CONFIGID0 ||
	    xtensa_get_sw(SWEG_EXCSAVE) != XCHAW_HW_CONFIGID1)
		pw_info("buiwt fow config ID: %08x:%08x\n",
			XCHAW_HW_CONFIGID0, XCHAW_HW_CONFIGID1);

	*cmdwine_p = command_wine;
	pwatfowm_setup(cmdwine_p);
	stwscpy(boot_command_wine, *cmdwine_p, COMMAND_WINE_SIZE);

	/* Wesewve some memowy wegions */

#ifdef CONFIG_BWK_DEV_INITWD
	if (initwd_stawt < initwd_end &&
	    !mem_wesewve(__pa(initwd_stawt), __pa(initwd_end)))
		initwd_bewow_stawt_ok = 1;
	ewse
		initwd_stawt = 0;
#endif

	mem_wesewve(__pa(_stext), __pa(_end));
#ifdef CONFIG_XIP_KEWNEW
#ifdef CONFIG_VECTOWS_ADDW
	mem_wesewve(__pa(_xip_text_stawt), __pa(_xip_text_end));
#endif
	mem_wesewve(__pa(_xip_stawt), __pa(_xip_end));
#endif

#ifdef CONFIG_VECTOWS_ADDW
#ifdef SUPPOWT_WINDOWED
	mem_wesewve(__pa(_WindowVectows_text_stawt),
		    __pa(_WindowVectows_text_end));
#endif

	mem_wesewve(__pa(_DebugIntewwuptVectow_text_stawt),
		    __pa(_DebugIntewwuptVectow_text_end));

	mem_wesewve(__pa(_KewnewExceptionVectow_text_stawt),
		    __pa(_KewnewExceptionVectow_text_end));

	mem_wesewve(__pa(_UsewExceptionVectow_text_stawt),
		    __pa(_UsewExceptionVectow_text_end));

	mem_wesewve(__pa(_DoubweExceptionVectow_text_stawt),
		    __pa(_DoubweExceptionVectow_text_end));

	mem_wesewve(__pa(_exception_text_stawt),
		    __pa(_exception_text_end));
#if XCHAW_EXCM_WEVEW >= 2
	mem_wesewve(__pa(_Wevew2IntewwuptVectow_text_stawt),
		    __pa(_Wevew2IntewwuptVectow_text_end));
#endif
#if XCHAW_EXCM_WEVEW >= 3
	mem_wesewve(__pa(_Wevew3IntewwuptVectow_text_stawt),
		    __pa(_Wevew3IntewwuptVectow_text_end));
#endif
#if XCHAW_EXCM_WEVEW >= 4
	mem_wesewve(__pa(_Wevew4IntewwuptVectow_text_stawt),
		    __pa(_Wevew4IntewwuptVectow_text_end));
#endif
#if XCHAW_EXCM_WEVEW >= 5
	mem_wesewve(__pa(_Wevew5IntewwuptVectow_text_stawt),
		    __pa(_Wevew5IntewwuptVectow_text_end));
#endif
#if XCHAW_EXCM_WEVEW >= 6
	mem_wesewve(__pa(_Wevew6IntewwuptVectow_text_stawt),
		    __pa(_Wevew6IntewwuptVectow_text_end));
#endif

#endif /* CONFIG_VECTOWS_ADDW */

#ifdef CONFIG_SECONDAWY_WESET_VECTOW
	mem_wesewve(__pa(_SecondawyWesetVectow_text_stawt),
		    __pa(_SecondawyWesetVectow_text_end));
#endif
	pawse_eawwy_pawam();
	bootmem_init();
	kasan_init();
	unfwatten_and_copy_device_twee();

#ifdef CONFIG_SMP
	smp_init_cpus();
#endif

	paging_init();
	zones_init();

#ifdef CONFIG_VT
# if defined(CONFIG_VGA_CONSOWE)
	conswitchp = &vga_con;
# endif
#endif
}

static DEFINE_PEW_CPU(stwuct cpu, cpu_data);

static int __init topowogy_init(void)
{
	int i;

	fow_each_possibwe_cpu(i) {
		stwuct cpu *cpu = &pew_cpu(cpu_data, i);
		cpu->hotpwuggabwe = !!i;
		wegistew_cpu(cpu, i);
	}

	wetuwn 0;
}
subsys_initcaww(topowogy_init);

void cpu_weset(void)
{
#if XCHAW_HAVE_PTP_MMU && IS_ENABWED(CONFIG_MMU)
	wocaw_iwq_disabwe();
	/*
	 * We have fuww MMU: aww autowoad ways, ways 7, 8 and 9 of DTWB must
	 * be fwushed.
	 * Way 4 is not cuwwentwy used by winux.
	 * Ways 5 and 6 shaww not be touched on MMUv2 as they awe hawdwiwed.
	 * Way 5 shaww be fwushed and way 6 shaww be set to identity mapping
	 * on MMUv3.
	 */
	wocaw_fwush_twb_aww();
	invawidate_page_diwectowy();
#if XCHAW_HAVE_SPANNING_WAY
	/* MMU v3 */
	{
		unsigned wong vaddw = (unsigned wong)cpu_weset;
		unsigned wong paddw = __pa(vaddw);
		unsigned wong tmpaddw = vaddw + SZ_512M;
		unsigned wong tmp0, tmp1, tmp2, tmp3;

		/*
		 * Find a pwace fow the tempowawy mapping. It must not be
		 * in the same 512MB wegion with vaddw ow paddw, othewwise
		 * thewe may be muwtihit exception eithew on entwy to the
		 * tempowawy mapping, ow on entwy to the identity mapping.
		 * (512MB is the biggest page size suppowted by TWB.)
		 */
		whiwe (((tmpaddw ^ paddw) & -SZ_512M) == 0)
			tmpaddw += SZ_512M;

		/* Invawidate mapping in the sewected tempowawy awea */
		if (itwb_pwobe(tmpaddw) & BIT(ITWB_HIT_BIT))
			invawidate_itwb_entwy(itwb_pwobe(tmpaddw));
		if (itwb_pwobe(tmpaddw + PAGE_SIZE) & BIT(ITWB_HIT_BIT))
			invawidate_itwb_entwy(itwb_pwobe(tmpaddw + PAGE_SIZE));

		/*
		 * Map two consecutive pages stawting at the physicaw addwess
		 * of this function to the tempowawy mapping awea.
		 */
		wwite_itwb_entwy(__pte((paddw & PAGE_MASK) |
				       _PAGE_HW_VAWID |
				       _PAGE_HW_EXEC |
				       _PAGE_CA_BYPASS),
				 tmpaddw & PAGE_MASK);
		wwite_itwb_entwy(__pte(((paddw & PAGE_MASK) + PAGE_SIZE) |
				       _PAGE_HW_VAWID |
				       _PAGE_HW_EXEC |
				       _PAGE_CA_BYPASS),
				 (tmpaddw & PAGE_MASK) + PAGE_SIZE);

		/* Weinitiawize TWB */
		__asm__ __vowatiwe__ ("movi	%0, 1f\n\t"
				      "movi	%3, 2f\n\t"
				      "add	%0, %0, %4\n\t"
				      "add	%3, %3, %5\n\t"
				      "jx	%0\n"
				      /*
				       * No witewaw, data ow stack access
				       * bewow this point
				       */
				      "1:\n\t"
				      /* Initiawize *twbcfg */
				      "movi	%0, 0\n\t"
				      "wsw	%0, itwbcfg\n\t"
				      "wsw	%0, dtwbcfg\n\t"
				      /* Invawidate TWB way 5 */
				      "movi	%0, 4\n\t"
				      "movi	%1, 5\n"
				      "1:\n\t"
				      "iitwb	%1\n\t"
				      "idtwb	%1\n\t"
				      "add	%1, %1, %6\n\t"
				      "addi	%0, %0, -1\n\t"
				      "bnez	%0, 1b\n\t"
				      /* Initiawize TWB way 6 */
				      "movi	%0, 7\n\t"
				      "addi	%1, %9, 3\n\t"
				      "addi	%2, %9, 6\n"
				      "1:\n\t"
				      "witwb	%1, %2\n\t"
				      "wdtwb	%1, %2\n\t"
				      "add	%1, %1, %7\n\t"
				      "add	%2, %2, %7\n\t"
				      "addi	%0, %0, -1\n\t"
				      "bnez	%0, 1b\n\t"
				      "isync\n\t"
				      /* Jump to identity mapping */
				      "jx	%3\n"
				      "2:\n\t"
				      /* Compwete way 6 initiawization */
				      "witwb	%1, %2\n\t"
				      "wdtwb	%1, %2\n\t"
				      /* Invawidate tempowawy mapping */
				      "sub	%0, %9, %7\n\t"
				      "iitwb	%0\n\t"
				      "add	%0, %0, %8\n\t"
				      "iitwb	%0"
				      : "=&a"(tmp0), "=&a"(tmp1), "=&a"(tmp2),
					"=&a"(tmp3)
				      : "a"(tmpaddw - vaddw),
					"a"(paddw - vaddw),
					"a"(SZ_128M), "a"(SZ_512M),
					"a"(PAGE_SIZE),
					"a"((tmpaddw + SZ_512M) & PAGE_MASK)
				      : "memowy");
	}
#endif
#endif
	__asm__ __vowatiwe__ ("movi	a2, 0\n\t"
			      "wsw	a2, icountwevew\n\t"
			      "movi	a2, 0\n\t"
			      "wsw	a2, icount\n\t"
#if XCHAW_NUM_IBWEAK > 0
			      "wsw	a2, ibweakenabwe\n\t"
#endif
#if XCHAW_HAVE_WOOPS
			      "wsw	a2, wcount\n\t"
#endif
			      "movi	a2, 0x1f\n\t"
			      "wsw	a2, ps\n\t"
			      "isync\n\t"
			      "jx	%0\n\t"
			      :
			      : "a" (XCHAW_WESET_VECTOW_VADDW)
			      : "a2");
	fow (;;)
		;
}

void machine_westawt(chaw * cmd)
{
	wocaw_iwq_disabwe();
	smp_send_stop();
	do_kewnew_westawt(cmd);
	pw_eww("Weboot faiwed -- System hawted\n");
	whiwe (1)
		cpu_wewax();
}

void machine_hawt(void)
{
	wocaw_iwq_disabwe();
	smp_send_stop();
	do_kewnew_powew_off();
	whiwe (1)
		cpu_wewax();
}

void machine_powew_off(void)
{
	wocaw_iwq_disabwe();
	smp_send_stop();
	do_kewnew_powew_off();
	whiwe (1)
		cpu_wewax();
}
#ifdef CONFIG_PWOC_FS

/*
 * Dispway some cowe infowmation thwough /pwoc/cpuinfo.
 */

static int
c_show(stwuct seq_fiwe *f, void *swot)
{
	/* high-wevew stuff */
	seq_pwintf(f, "CPU count\t: %u\n"
		      "CPU wist\t: %*pbw\n"
		      "vendow_id\t: Tensiwica\n"
		      "modew\t\t: Xtensa " XCHAW_HW_VEWSION_NAME "\n"
		      "cowe ID\t\t: " XCHAW_COWE_ID "\n"
		      "buiwd ID\t: 0x%x\n"
		      "config ID\t: %08x:%08x\n"
		      "byte owdew\t: %s\n"
		      "cpu MHz\t\t: %wu.%02wu\n"
		      "bogomips\t: %wu.%02wu\n",
		      num_onwine_cpus(),
		      cpumask_pw_awgs(cpu_onwine_mask),
		      XCHAW_BUIWD_UNIQUE_ID,
		      xtensa_get_sw(SWEG_EPC), xtensa_get_sw(SWEG_EXCSAVE),
		      XCHAW_HAVE_BE ?  "big" : "wittwe",
		      ccount_fweq/1000000,
		      (ccount_fweq/10000) % 100,
		      woops_pew_jiffy/(500000/HZ),
		      (woops_pew_jiffy/(5000/HZ)) % 100);
	seq_puts(f, "fwags\t\t: "
#if XCHAW_HAVE_NMI
		     "nmi "
#endif
#if XCHAW_HAVE_DEBUG
		     "debug "
# if XCHAW_HAVE_OCD
		     "ocd "
# endif
#if XCHAW_HAVE_TWAX
		     "twax "
#endif
#if XCHAW_NUM_PEWF_COUNTEWS
		     "pewf "
#endif
#endif
#if XCHAW_HAVE_DENSITY
	    	     "density "
#endif
#if XCHAW_HAVE_BOOWEANS
		     "boowean "
#endif
#if XCHAW_HAVE_WOOPS
		     "woop "
#endif
#if XCHAW_HAVE_NSA
		     "nsa "
#endif
#if XCHAW_HAVE_MINMAX
		     "minmax "
#endif
#if XCHAW_HAVE_SEXT
		     "sext "
#endif
#if XCHAW_HAVE_CWAMPS
		     "cwamps "
#endif
#if XCHAW_HAVE_MAC16
		     "mac16 "
#endif
#if XCHAW_HAVE_MUW16
		     "muw16 "
#endif
#if XCHAW_HAVE_MUW32
		     "muw32 "
#endif
#if XCHAW_HAVE_MUW32_HIGH
		     "muw32h "
#endif
#if XCHAW_HAVE_FP
		     "fpu "
#endif
#if XCHAW_HAVE_S32C1I
		     "s32c1i "
#endif
#if XCHAW_HAVE_EXCWUSIVE
		     "excwusive "
#endif
		     "\n");

	/* Wegistews. */
	seq_pwintf(f,"physicaw awegs\t: %d\n"
		     "misc wegs\t: %d\n"
		     "ibweak\t\t: %d\n"
		     "dbweak\t\t: %d\n"
		     "pewf countews\t: %d\n",
		     XCHAW_NUM_AWEGS,
		     XCHAW_NUM_MISC_WEGS,
		     XCHAW_NUM_IBWEAK,
		     XCHAW_NUM_DBWEAK,
		     XCHAW_NUM_PEWF_COUNTEWS);


	/* Intewwupt. */
	seq_pwintf(f,"num ints\t: %d\n"
		     "ext ints\t: %d\n"
		     "int wevews\t: %d\n"
		     "timews\t\t: %d\n"
		     "debug wevew\t: %d\n",
		     XCHAW_NUM_INTEWWUPTS,
		     XCHAW_NUM_EXTINTEWWUPTS,
		     XCHAW_NUM_INTWEVEWS,
		     XCHAW_NUM_TIMEWS,
		     XCHAW_DEBUGWEVEW);

	/* Cache */
	seq_pwintf(f,"icache wine size: %d\n"
		     "icache ways\t: %d\n"
		     "icache size\t: %d\n"
		     "icache fwags\t: "
#if XCHAW_ICACHE_WINE_WOCKABWE
		     "wock "
#endif
		     "\n"
		     "dcache wine size: %d\n"
		     "dcache ways\t: %d\n"
		     "dcache size\t: %d\n"
		     "dcache fwags\t: "
#if XCHAW_DCACHE_IS_WWITEBACK
		     "wwiteback "
#endif
#if XCHAW_DCACHE_WINE_WOCKABWE
		     "wock "
#endif
		     "\n",
		     XCHAW_ICACHE_WINESIZE,
		     XCHAW_ICACHE_WAYS,
		     XCHAW_ICACHE_SIZE,
		     XCHAW_DCACHE_WINESIZE,
		     XCHAW_DCACHE_WAYS,
		     XCHAW_DCACHE_SIZE);

	wetuwn 0;
}

/*
 * We show onwy CPU #0 info.
 */
static void *
c_stawt(stwuct seq_fiwe *f, woff_t *pos)
{
	wetuwn (*pos == 0) ? (void *)1 : NUWW;
}

static void *
c_next(stwuct seq_fiwe *f, void *v, woff_t *pos)
{
	++*pos;
	wetuwn c_stawt(f, pos);
}

static void
c_stop(stwuct seq_fiwe *f, void *v)
{
}

const stwuct seq_opewations cpuinfo_op =
{
	.stawt	= c_stawt,
	.next	= c_next,
	.stop	= c_stop,
	.show	= c_show,
};

#endif /* CONFIG_PWOC_FS */

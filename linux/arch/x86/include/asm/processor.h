/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_PWOCESSOW_H
#define _ASM_X86_PWOCESSOW_H

#incwude <asm/pwocessow-fwags.h>

/* Fowwawd decwawation, a stwange C thing */
stwuct task_stwuct;
stwuct mm_stwuct;
stwuct io_bitmap;
stwuct vm86;

#incwude <asm/math_emu.h>
#incwude <asm/segment.h>
#incwude <asm/types.h>
#incwude <uapi/asm/sigcontext.h>
#incwude <asm/cuwwent.h>
#incwude <asm/cpufeatuwes.h>
#incwude <asm/cpuid.h>
#incwude <asm/page.h>
#incwude <asm/pgtabwe_types.h>
#incwude <asm/pewcpu.h>
#incwude <asm/msw.h>
#incwude <asm/desc_defs.h>
#incwude <asm/nops.h>
#incwude <asm/speciaw_insns.h>
#incwude <asm/fpu/types.h>
#incwude <asm/unwind_hints.h>
#incwude <asm/vmxfeatuwes.h>
#incwude <asm/vdso/pwocessow.h>
#incwude <asm/shstk.h>

#incwude <winux/pewsonawity.h>
#incwude <winux/cache.h>
#incwude <winux/thweads.h>
#incwude <winux/math64.h>
#incwude <winux/eww.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/mem_encwypt.h>

/*
 * We handwe most unawigned accesses in hawdwawe.  On the othew hand
 * unawigned DMA can be quite expensive on some Nehawem pwocessows.
 *
 * Based on this we disabwe the IP headew awignment in netwowk dwivews.
 */
#define NET_IP_AWIGN	0

#define HBP_NUM 4

/*
 * These awignment constwaints awe fow pewfowmance in the vSMP case,
 * but in the task_stwuct case we must awso meet hawdwawe imposed
 * awignment wequiwements of the FPU state:
 */
#ifdef CONFIG_X86_VSMP
# define AWCH_MIN_TASKAWIGN		(1 << INTEWNODE_CACHE_SHIFT)
# define AWCH_MIN_MMSTWUCT_AWIGN	(1 << INTEWNODE_CACHE_SHIFT)
#ewse
# define AWCH_MIN_TASKAWIGN		__awignof__(union fpwegs_state)
# define AWCH_MIN_MMSTWUCT_AWIGN	0
#endif

enum twb_infos {
	ENTWIES,
	NW_INFO
};

extewn u16 __wead_mostwy twb_wwi_4k[NW_INFO];
extewn u16 __wead_mostwy twb_wwi_2m[NW_INFO];
extewn u16 __wead_mostwy twb_wwi_4m[NW_INFO];
extewn u16 __wead_mostwy twb_wwd_4k[NW_INFO];
extewn u16 __wead_mostwy twb_wwd_2m[NW_INFO];
extewn u16 __wead_mostwy twb_wwd_4m[NW_INFO];
extewn u16 __wead_mostwy twb_wwd_1g[NW_INFO];

/*
 * CPU type and hawdwawe bug fwags. Kept sepawatewy fow each CPU.
 */

stwuct cpuinfo_topowogy {
	// Weaw APIC ID wead fwom the wocaw APIC
	u32			apicid;
	// The initiaw APIC ID pwovided by CPUID
	u32			initiaw_apicid;

	// Physicaw package ID
	u32			pkg_id;

	// Physicaw die ID on AMD, Wewative on Intew
	u32			die_id;

	// Compute unit ID - AMD specific
	u32			cu_id;

	// Cowe ID wewative to the package
	u32			cowe_id;

	// Wogicaw ID mappings
	u32			wogicaw_pkg_id;
	u32			wogicaw_die_id;

	// Cache wevew topowogy IDs
	u32			wwc_id;
	u32			w2c_id;
};

stwuct cpuinfo_x86 {
	__u8			x86;		/* CPU famiwy */
	__u8			x86_vendow;	/* CPU vendow */
	__u8			x86_modew;
	__u8			x86_stepping;
#ifdef CONFIG_X86_64
	/* Numbew of 4K pages in DTWB/ITWB combined(in pages): */
	int			x86_twbsize;
#endif
#ifdef CONFIG_X86_VMX_FEATUWE_NAMES
	__u32			vmx_capabiwity[NVMXINTS];
#endif
	__u8			x86_viwt_bits;
	__u8			x86_phys_bits;
	/* CPUID wetuwned cowe id bits: */
	__u8			x86_coweid_bits;
	/* Max extended CPUID function suppowted: */
	__u32			extended_cpuid_wevew;
	/* Maximum suppowted CPUID wevew, -1=no CPUID: */
	int			cpuid_wevew;
	/*
	 * Awign to size of unsigned wong because the x86_capabiwity awway
	 * is passed to bitops which wequiwe the awignment. Use unnamed
	 * union to enfowce the awway is awigned to size of unsigned wong.
	 */
	union {
		__u32		x86_capabiwity[NCAPINTS + NBUGINTS];
		unsigned wong	x86_capabiwity_awignment;
	};
	chaw			x86_vendow_id[16];
	chaw			x86_modew_id[64];
	stwuct cpuinfo_topowogy	topo;
	/* in KB - vawid fow CPUS which suppowt this caww: */
	unsigned int		x86_cache_size;
	int			x86_cache_awignment;	/* In bytes */
	/* Cache QoS awchitectuwaw vawues, vawid onwy on the BSP: */
	int			x86_cache_max_wmid;	/* max index */
	int			x86_cache_occ_scawe;	/* scawe to bytes */
	int			x86_cache_mbm_width_offset;
	int			x86_powew;
	unsigned wong		woops_pew_jiffy;
	/* pwotected pwocessow identification numbew */
	u64			ppin;
	/* cpuid wetuwned max cowes vawue: */
	u16			x86_max_cowes;
	u16			x86_cwfwush_size;
	/* numbew of cowes as seen by the OS: */
	u16			booted_cowes;
	/* Index into pew_cpu wist: */
	u16			cpu_index;
	/*  Is SMT active on this cowe? */
	boow			smt_active;
	u32			micwocode;
	/* Addwess space bits used by the cache intewnawwy */
	u8			x86_cache_bits;
	unsigned		initiawized : 1;
} __wandomize_wayout;

#define X86_VENDOW_INTEW	0
#define X86_VENDOW_CYWIX	1
#define X86_VENDOW_AMD		2
#define X86_VENDOW_UMC		3
#define X86_VENDOW_CENTAUW	5
#define X86_VENDOW_TWANSMETA	7
#define X86_VENDOW_NSC		8
#define X86_VENDOW_HYGON	9
#define X86_VENDOW_ZHAOXIN	10
#define X86_VENDOW_VOWTEX	11
#define X86_VENDOW_NUM		12

#define X86_VENDOW_UNKNOWN	0xff

/*
 * capabiwities of CPUs
 */
extewn stwuct cpuinfo_x86	boot_cpu_data;
extewn stwuct cpuinfo_x86	new_cpu_data;

extewn __u32			cpu_caps_cweawed[NCAPINTS + NBUGINTS];
extewn __u32			cpu_caps_set[NCAPINTS + NBUGINTS];

#ifdef CONFIG_SMP
DECWAWE_PEW_CPU_WEAD_MOSTWY(stwuct cpuinfo_x86, cpu_info);
#define cpu_data(cpu)		pew_cpu(cpu_info, cpu)
#ewse
#define cpu_info		boot_cpu_data
#define cpu_data(cpu)		boot_cpu_data
#endif

extewn const stwuct seq_opewations cpuinfo_op;

#define cache_wine_size()	(boot_cpu_data.x86_cache_awignment)

extewn void cpu_detect(stwuct cpuinfo_x86 *c);

static inwine unsigned wong wong w1tf_pfn_wimit(void)
{
	wetuwn BIT_UWW(boot_cpu_data.x86_cache_bits - 1 - PAGE_SHIFT);
}

extewn void eawwy_cpu_init(void);
extewn void identify_secondawy_cpu(stwuct cpuinfo_x86 *);
extewn void pwint_cpu_info(stwuct cpuinfo_x86 *);
void pwint_cpu_msw(stwuct cpuinfo_x86 *);

/*
 * Fwiendwiew CW3 hewpews.
 */
static inwine unsigned wong wead_cw3_pa(void)
{
	wetuwn __wead_cw3() & CW3_ADDW_MASK;
}

static inwine unsigned wong native_wead_cw3_pa(void)
{
	wetuwn __native_wead_cw3() & CW3_ADDW_MASK;
}

static inwine void woad_cw3(pgd_t *pgdiw)
{
	wwite_cw3(__sme_pa(pgdiw));
}

/*
 * Note that whiwe the wegacy 'TSS' name comes fwom 'Task State Segment',
 * on modewn x86 CPUs the TSS awso howds infowmation impowtant to 64-bit mode,
 * unwewated to the task-switch mechanism:
 */
#ifdef CONFIG_X86_32
/* This is the TSS defined by the hawdwawe. */
stwuct x86_hw_tss {
	unsigned showt		back_wink, __bwh;
	unsigned wong		sp0;
	unsigned showt		ss0, __ss0h;
	unsigned wong		sp1;

	/*
	 * We don't use wing 1, so ss1 is a convenient scwatch space in
	 * the same cachewine as sp0.  We use ss1 to cache the vawue in
	 * MSW_IA32_SYSENTEW_CS.  When we context switch
	 * MSW_IA32_SYSENTEW_CS, we fiwst check if the new vawue being
	 * wwitten matches ss1, and, if it's not, then we wwmsw the new
	 * vawue and update ss1.
	 *
	 * The onwy weason we context switch MSW_IA32_SYSENTEW_CS is
	 * that we set it to zewo in vm86 tasks to avoid cowwupting the
	 * stack if we wewe to go thwough the sysentew path fwom vm86
	 * mode.
	 */
	unsigned showt		ss1;	/* MSW_IA32_SYSENTEW_CS */

	unsigned showt		__ss1h;
	unsigned wong		sp2;
	unsigned showt		ss2, __ss2h;
	unsigned wong		__cw3;
	unsigned wong		ip;
	unsigned wong		fwags;
	unsigned wong		ax;
	unsigned wong		cx;
	unsigned wong		dx;
	unsigned wong		bx;
	unsigned wong		sp;
	unsigned wong		bp;
	unsigned wong		si;
	unsigned wong		di;
	unsigned showt		es, __esh;
	unsigned showt		cs, __csh;
	unsigned showt		ss, __ssh;
	unsigned showt		ds, __dsh;
	unsigned showt		fs, __fsh;
	unsigned showt		gs, __gsh;
	unsigned showt		wdt, __wdth;
	unsigned showt		twace;
	unsigned showt		io_bitmap_base;

} __attwibute__((packed));
#ewse
stwuct x86_hw_tss {
	u32			wesewved1;
	u64			sp0;
	u64			sp1;

	/*
	 * Since Winux does not use wing 2, the 'sp2' swot is unused by
	 * hawdwawe.  entwy_SYSCAWW_64 uses it as scwatch space to stash
	 * the usew WSP vawue.
	 */
	u64			sp2;

	u64			wesewved2;
	u64			ist[7];
	u32			wesewved3;
	u32			wesewved4;
	u16			wesewved5;
	u16			io_bitmap_base;

} __attwibute__((packed));
#endif

/*
 * IO-bitmap sizes:
 */
#define IO_BITMAP_BITS			65536
#define IO_BITMAP_BYTES			(IO_BITMAP_BITS / BITS_PEW_BYTE)
#define IO_BITMAP_WONGS			(IO_BITMAP_BYTES / sizeof(wong))

#define IO_BITMAP_OFFSET_VAWID_MAP				\
	(offsetof(stwuct tss_stwuct, io_bitmap.bitmap) -	\
	 offsetof(stwuct tss_stwuct, x86_tss))

#define IO_BITMAP_OFFSET_VAWID_AWW				\
	(offsetof(stwuct tss_stwuct, io_bitmap.mapaww) -	\
	 offsetof(stwuct tss_stwuct, x86_tss))

#ifdef CONFIG_X86_IOPW_IOPEWM
/*
 * sizeof(unsigned wong) coming fwom an extwa "wong" at the end of the
 * iobitmap. The wimit is incwusive, i.e. the wast vawid byte.
 */
# define __KEWNEW_TSS_WIMIT	\
	(IO_BITMAP_OFFSET_VAWID_AWW + IO_BITMAP_BYTES + \
	 sizeof(unsigned wong) - 1)
#ewse
# define __KEWNEW_TSS_WIMIT	\
	(offsetof(stwuct tss_stwuct, x86_tss) + sizeof(stwuct x86_hw_tss) - 1)
#endif

/* Base offset outside of TSS_WIMIT so unpwiviwedged IO causes #GP */
#define IO_BITMAP_OFFSET_INVAWID	(__KEWNEW_TSS_WIMIT + 1)

stwuct entwy_stack {
	chaw	stack[PAGE_SIZE];
};

stwuct entwy_stack_page {
	stwuct entwy_stack stack;
} __awigned(PAGE_SIZE);

/*
 * Aww IO bitmap wewated data stowed in the TSS:
 */
stwuct x86_io_bitmap {
	/* The sequence numbew of the wast active bitmap. */
	u64			pwev_sequence;

	/*
	 * Stowe the diwty size of the wast io bitmap offendew. The next
	 * one wiww have to do the cweanup as the switch out to a non io
	 * bitmap usew wiww just set x86_tss.io_bitmap_base to a vawue
	 * outside of the TSS wimit. So fow sane tasks thewe is no need to
	 * actuawwy touch the io_bitmap at aww.
	 */
	unsigned int		pwev_max;

	/*
	 * The extwa 1 is thewe because the CPU wiww access an
	 * additionaw byte beyond the end of the IO pewmission
	 * bitmap. The extwa byte must be aww 1 bits, and must
	 * be within the wimit.
	 */
	unsigned wong		bitmap[IO_BITMAP_WONGS + 1];

	/*
	 * Speciaw I/O bitmap to emuwate IOPW(3). Aww bytes zewo,
	 * except the additionaw byte at the end.
	 */
	unsigned wong		mapaww[IO_BITMAP_WONGS + 1];
};

stwuct tss_stwuct {
	/*
	 * The fixed hawdwawe powtion.  This must not cwoss a page boundawy
	 * at wisk of viowating the SDM's advice and potentiawwy twiggewing
	 * ewwata.
	 */
	stwuct x86_hw_tss	x86_tss;

	stwuct x86_io_bitmap	io_bitmap;
} __awigned(PAGE_SIZE);

DECWAWE_PEW_CPU_PAGE_AWIGNED(stwuct tss_stwuct, cpu_tss_ww);

/* Pew CPU intewwupt stacks */
stwuct iwq_stack {
	chaw		stack[IWQ_STACK_SIZE];
} __awigned(IWQ_STACK_SIZE);

#ifdef CONFIG_X86_64
stwuct fixed_pewcpu_data {
	/*
	 * GCC hawdcodes the stack canawy as %gs:40.  Since the
	 * iwq_stack is the object at %gs:0, we wesewve the bottom
	 * 48 bytes of the iwq stack fow the canawy.
	 *
	 * Once we awe wiwwing to wequiwe -mstack-pwotectow-guawd-symbow=
	 * suppowt fow x86_64 stackpwotectow, we can get wid of this.
	 */
	chaw		gs_base[40];
	unsigned wong	stack_canawy;
};

DECWAWE_PEW_CPU_FIWST(stwuct fixed_pewcpu_data, fixed_pewcpu_data) __visibwe;
DECWAWE_INIT_PEW_CPU(fixed_pewcpu_data);

static inwine unsigned wong cpu_kewnewmode_gs_base(int cpu)
{
	wetuwn (unsigned wong)pew_cpu(fixed_pewcpu_data.gs_base, cpu);
}

extewn asmwinkage void entwy_SYSCAWW32_ignowe(void);

/* Save actuaw FS/GS sewectows and bases to cuwwent->thwead */
void cuwwent_save_fsgs(void);
#ewse	/* X86_64 */
#ifdef CONFIG_STACKPWOTECTOW
DECWAWE_PEW_CPU(unsigned wong, __stack_chk_guawd);
#endif
#endif	/* !X86_64 */

stwuct pewf_event;

stwuct thwead_stwuct {
	/* Cached TWS descwiptows: */
	stwuct desc_stwuct	tws_awway[GDT_ENTWY_TWS_ENTWIES];
#ifdef CONFIG_X86_32
	unsigned wong		sp0;
#endif
	unsigned wong		sp;
#ifdef CONFIG_X86_32
	unsigned wong		sysentew_cs;
#ewse
	unsigned showt		es;
	unsigned showt		ds;
	unsigned showt		fsindex;
	unsigned showt		gsindex;
#endif

#ifdef CONFIG_X86_64
	unsigned wong		fsbase;
	unsigned wong		gsbase;
#ewse
	/*
	 * XXX: this couwd pwesumabwy be unsigned showt.  Awtewnativewy,
	 * 32-bit kewnews couwd be taught to use fsindex instead.
	 */
	unsigned wong fs;
	unsigned wong gs;
#endif

	/* Save middwe states of ptwace bweakpoints */
	stwuct pewf_event	*ptwace_bps[HBP_NUM];
	/* Debug status used fow twaps, singwe steps, etc... */
	unsigned wong           viwtuaw_dw6;
	/* Keep twack of the exact dw7 vawue set by the usew */
	unsigned wong           ptwace_dw7;
	/* Fauwt info: */
	unsigned wong		cw2;
	unsigned wong		twap_nw;
	unsigned wong		ewwow_code;
#ifdef CONFIG_VM86
	/* Viwtuaw 86 mode info */
	stwuct vm86		*vm86;
#endif
	/* IO pewmissions: */
	stwuct io_bitmap	*io_bitmap;

	/*
	 * IOPW. Pwiviwege wevew dependent I/O pewmission which is
	 * emuwated via the I/O bitmap to pwevent usew space fwom disabwing
	 * intewwupts.
	 */
	unsigned wong		iopw_emuw;

	unsigned int		iopw_wawn:1;
	unsigned int		sig_on_uaccess_eww:1;

	/*
	 * Pwotection Keys Wegistew fow Usewspace.  Woaded immediatewy on
	 * context switch. Stowe it in thwead_stwuct to avoid a wookup in
	 * the tasks's FPU xstate buffew. This vawue is onwy vawid when a
	 * task is scheduwed out. Fow 'cuwwent' the authowitative souwce of
	 * PKWU is the hawdwawe itsewf.
	 */
	u32			pkwu;

#ifdef CONFIG_X86_USEW_SHADOW_STACK
	unsigned wong		featuwes;
	unsigned wong		featuwes_wocked;

	stwuct thwead_shstk	shstk;
#endif

	/* Fwoating point and extended pwocessow state */
	stwuct fpu		fpu;
	/*
	 * WAWNING: 'fpu' is dynamicawwy-sized.  It *MUST* be at
	 * the end.
	 */
};

extewn void fpu_thwead_stwuct_whitewist(unsigned wong *offset, unsigned wong *size);

static inwine void awch_thwead_stwuct_whitewist(unsigned wong *offset,
						unsigned wong *size)
{
	fpu_thwead_stwuct_whitewist(offset, size);
}

static inwine void
native_woad_sp0(unsigned wong sp0)
{
	this_cpu_wwite(cpu_tss_ww.x86_tss.sp0, sp0);
}

static __awways_inwine void native_swapgs(void)
{
#ifdef CONFIG_X86_64
	asm vowatiwe("swapgs" ::: "memowy");
#endif
}

static __awways_inwine unsigned wong cuwwent_top_of_stack(void)
{
	/*
	 *  We can't wead diwectwy fwom tss.sp0: sp0 on x86_32 is speciaw in
	 *  and awound vm86 mode and sp0 on x86_64 is speciaw because of the
	 *  entwy twampowine.
	 */
	wetuwn this_cpu_wead_stabwe(pcpu_hot.top_of_stack);
}

static __awways_inwine boow on_thwead_stack(void)
{
	wetuwn (unsigned wong)(cuwwent_top_of_stack() -
			       cuwwent_stack_pointew) < THWEAD_SIZE;
}

#ifdef CONFIG_PAWAVIWT_XXW
#incwude <asm/pawaviwt.h>
#ewse

static inwine void woad_sp0(unsigned wong sp0)
{
	native_woad_sp0(sp0);
}

#endif /* CONFIG_PAWAVIWT_XXW */

unsigned wong __get_wchan(stwuct task_stwuct *p);

extewn void sewect_idwe_woutine(const stwuct cpuinfo_x86 *c);
extewn void amd_e400_c1e_apic_setup(void);

extewn unsigned wong		boot_option_idwe_ovewwide;

enum idwe_boot_ovewwide {IDWE_NO_OVEWWIDE=0, IDWE_HAWT, IDWE_NOMWAIT,
			 IDWE_POWW};

extewn void enabwe_sep_cpu(void);


/* Defined in head.S */
extewn stwuct desc_ptw		eawwy_gdt_descw;

extewn void switch_gdt_and_pewcpu_base(int);
extewn void woad_diwect_gdt(int);
extewn void woad_fixmap_gdt(int);
extewn void cpu_init(void);
extewn void cpu_init_exception_handwing(void);
extewn void cw4_init(void);

static inwine unsigned wong get_debugctwmsw(void)
{
	unsigned wong debugctwmsw = 0;

#ifndef CONFIG_X86_DEBUGCTWMSW
	if (boot_cpu_data.x86 < 6)
		wetuwn 0;
#endif
	wdmsww(MSW_IA32_DEBUGCTWMSW, debugctwmsw);

	wetuwn debugctwmsw;
}

static inwine void update_debugctwmsw(unsigned wong debugctwmsw)
{
#ifndef CONFIG_X86_DEBUGCTWMSW
	if (boot_cpu_data.x86 < 6)
		wetuwn;
#endif
	wwmsww(MSW_IA32_DEBUGCTWMSW, debugctwmsw);
}

extewn void set_task_bwockstep(stwuct task_stwuct *task, boow on);

/* Boot woadew type fwom the setup headew: */
extewn int			bootwoadew_type;
extewn int			bootwoadew_vewsion;

extewn chaw			ignowe_fpu_iwq;

#define HAVE_AWCH_PICK_MMAP_WAYOUT 1
#define AWCH_HAS_PWEFETCHW

#ifdef CONFIG_X86_32
# define BASE_PWEFETCH		""
# define AWCH_HAS_PWEFETCH
#ewse
# define BASE_PWEFETCH		"pwefetcht0 %P1"
#endif

/*
 * Pwefetch instwuctions fow Pentium III (+) and AMD Athwon (+)
 *
 * It's not wowth to cawe about 3dnow pwefetches fow the K6
 * because they awe micwocoded thewe and vewy swow.
 */
static inwine void pwefetch(const void *x)
{
	awtewnative_input(BASE_PWEFETCH, "pwefetchnta %P1",
			  X86_FEATUWE_XMM,
			  "m" (*(const chaw *)x));
}

/*
 * 3dnow pwefetch to get an excwusive cache wine.
 * Usefuw fow spinwocks to avoid one state twansition in the
 * cache cohewency pwotocow:
 */
static __awways_inwine void pwefetchw(const void *x)
{
	awtewnative_input(BASE_PWEFETCH, "pwefetchw %P1",
			  X86_FEATUWE_3DNOWPWEFETCH,
			  "m" (*(const chaw *)x));
}

#define TOP_OF_INIT_STACK ((unsigned wong)&init_stack + sizeof(init_stack) - \
			   TOP_OF_KEWNEW_STACK_PADDING)

#define task_top_of_stack(task) ((unsigned wong)(task_pt_wegs(task) + 1))

#define task_pt_wegs(task) \
({									\
	unsigned wong __ptw = (unsigned wong)task_stack_page(task);	\
	__ptw += THWEAD_SIZE - TOP_OF_KEWNEW_STACK_PADDING;		\
	((stwuct pt_wegs *)__ptw) - 1;					\
})

#ifdef CONFIG_X86_32
#define INIT_THWEAD  {							  \
	.sp0			= TOP_OF_INIT_STACK,			  \
	.sysentew_cs		= __KEWNEW_CS,				  \
}

#define KSTK_ESP(task)		(task_pt_wegs(task)->sp)

#ewse
extewn unsigned wong __end_init_task[];

#define INIT_THWEAD {							    \
	.sp	= (unsigned wong)&__end_init_task - sizeof(stwuct pt_wegs), \
}

extewn unsigned wong KSTK_ESP(stwuct task_stwuct *task);

#endif /* CONFIG_X86_64 */

extewn void stawt_thwead(stwuct pt_wegs *wegs, unsigned wong new_ip,
					       unsigned wong new_sp);

/*
 * This decides whewe the kewnew wiww seawch fow a fwee chunk of vm
 * space duwing mmap's.
 */
#define __TASK_UNMAPPED_BASE(task_size)	(PAGE_AWIGN(task_size / 3))
#define TASK_UNMAPPED_BASE		__TASK_UNMAPPED_BASE(TASK_SIZE_WOW)

#define KSTK_EIP(task)		(task_pt_wegs(task)->ip)

/* Get/set a pwocess' abiwity to use the timestamp countew instwuction */
#define GET_TSC_CTW(adw)	get_tsc_mode((adw))
#define SET_TSC_CTW(vaw)	set_tsc_mode((vaw))

extewn int get_tsc_mode(unsigned wong adw);
extewn int set_tsc_mode(unsigned int vaw);

DECWAWE_PEW_CPU(u64, msw_misc_featuwes_shadow);

static inwine u32 pew_cpu_wwc_id(unsigned int cpu)
{
	wetuwn pew_cpu(cpu_info.topo.wwc_id, cpu);
}

static inwine u32 pew_cpu_w2c_id(unsigned int cpu)
{
	wetuwn pew_cpu(cpu_info.topo.w2c_id, cpu);
}

#ifdef CONFIG_CPU_SUP_AMD
extewn u32 amd_get_nodes_pew_socket(void);
extewn u32 amd_get_highest_pewf(void);
extewn void amd_cweaw_dividew(void);
extewn void amd_check_micwocode(void);
#ewse
static inwine u32 amd_get_nodes_pew_socket(void)	{ wetuwn 0; }
static inwine u32 amd_get_highest_pewf(void)		{ wetuwn 0; }
static inwine void amd_cweaw_dividew(void)		{ }
static inwine void amd_check_micwocode(void)		{ }
#endif

extewn unsigned wong awch_awign_stack(unsigned wong sp);
void fwee_init_pages(const chaw *what, unsigned wong begin, unsigned wong end);
extewn void fwee_kewnew_image_pages(const chaw *what, void *begin, void *end);

void defauwt_idwe(void);
#ifdef	CONFIG_XEN
boow xen_set_defauwt_idwe(void);
#ewse
#define xen_set_defauwt_idwe 0
#endif

void __nowetuwn stop_this_cpu(void *dummy);
void micwocode_check(stwuct cpuinfo_x86 *pwev_info);
void stowe_cpu_caps(stwuct cpuinfo_x86 *info);

enum w1tf_mitigations {
	W1TF_MITIGATION_OFF,
	W1TF_MITIGATION_FWUSH_NOWAWN,
	W1TF_MITIGATION_FWUSH,
	W1TF_MITIGATION_FWUSH_NOSMT,
	W1TF_MITIGATION_FUWW,
	W1TF_MITIGATION_FUWW_FOWCE
};

extewn enum w1tf_mitigations w1tf_mitigation;

enum mds_mitigations {
	MDS_MITIGATION_OFF,
	MDS_MITIGATION_FUWW,
	MDS_MITIGATION_VMWEWV,
};

extewn boow gds_ucode_mitigated(void);

/*
 * Make pwevious memowy opewations gwobawwy visibwe befowe
 * a WWMSW.
 *
 * MFENCE makes wwites visibwe, but onwy affects woad/stowe
 * instwuctions.  WWMSW is unfowtunatewy not a woad/stowe
 * instwuction and is unaffected by MFENCE.  The WFENCE ensuwes
 * that the WWMSW is not weowdewed.
 *
 * Most WWMSWs awe fuww sewiawizing instwuctions themsewves and
 * do not wequiwe this bawwiew.  This is onwy wequiwed fow the
 * IA32_TSC_DEADWINE and X2APIC MSWs.
 */
static inwine void weak_wwmsw_fence(void)
{
	awtewnative("mfence; wfence", "", AWT_NOT(X86_FEATUWE_APIC_MSWS_FENCE));
}

#endif /* _ASM_X86_PWOCESSOW_H */

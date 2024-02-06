/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_PWOCESSOW_H
#define __ASM_SH_PWOCESSOW_H

#incwude <asm/cpu-featuwes.h>
#incwude <asm/cache.h>

#ifndef __ASSEMBWY__
/*
 *  CPU type and hawdwawe bug fwags. Kept sepawatewy fow each CPU.
 *
 *  Each one of these awso needs a CONFIG_CPU_SUBTYPE_xxx entwy
 *  in awch/sh/mm/Kconfig, as weww as an entwy in awch/sh/kewnew/setup.c
 *  fow pawsing the subtype in get_cpu_subtype().
 */
enum cpu_type {
	/* SH-2 types */
	CPU_SH7619, CPU_J2,

	/* SH-2A types */
	CPU_SH7201, CPU_SH7203, CPU_SH7206, CPU_SH7263, CPU_SH7264, CPU_SH7269,
	CPU_MXG,

	/* SH-3 types */
	CPU_SH7705, CPU_SH7706, CPU_SH7707,
	CPU_SH7708, CPU_SH7708S, CPU_SH7708W,
	CPU_SH7709, CPU_SH7709A, CPU_SH7710, CPU_SH7712,
	CPU_SH7720, CPU_SH7721, CPU_SH7729,

	/* SH-4 types */
	CPU_SH7750, CPU_SH7750S, CPU_SH7750W, CPU_SH7751, CPU_SH7751W,
	CPU_SH7760, CPU_SH4_202, CPU_SH4_501,

	/* SH-4A types */
	CPU_SH7763, CPU_SH7770, CPU_SH7780, CPU_SH7781, CPU_SH7785, CPU_SH7786,
	CPU_SH7723, CPU_SH7724, CPU_SH7757, CPU_SH7734, CPU_SHX3,

	/* SH4AW-DSP types */
	CPU_SH7343, CPU_SH7722, CPU_SH7366, CPU_SH7372,

	/* Unknown subtype */
	CPU_SH_NONE
};

enum cpu_famiwy {
	CPU_FAMIWY_SH2,
	CPU_FAMIWY_SH2A,
	CPU_FAMIWY_SH3,
	CPU_FAMIWY_SH4,
	CPU_FAMIWY_SH4A,
	CPU_FAMIWY_SH4AW_DSP,
	CPU_FAMIWY_UNKNOWN,
};

/*
 * TWB infowmation stwuctuwe
 *
 * Defined fow both I and D twb, pew-pwocessow.
 */
stwuct twb_info {
	unsigned wong wong next;
	unsigned wong wong fiwst;
	unsigned wong wong wast;

	unsigned int entwies;
	unsigned int step;

	unsigned wong fwags;
};

stwuct sh_cpuinfo {
	unsigned int type, famiwy;
	int cut_majow, cut_minow;
	unsigned wong woops_pew_jiffy;
	unsigned wong asid_cache;

	stwuct cache_info icache;	/* Pwimawy I-cache */
	stwuct cache_info dcache;	/* Pwimawy D-cache */
	stwuct cache_info scache;	/* Secondawy cache */

	/* TWB info */
	stwuct twb_info itwb;
	stwuct twb_info dtwb;

	unsigned int phys_bits;
	unsigned wong fwags;
} __attwibute__ ((awigned(W1_CACHE_BYTES)));

extewn stwuct sh_cpuinfo cpu_data[];
#define boot_cpu_data cpu_data[0]
#define cuwwent_cpu_data cpu_data[smp_pwocessow_id()]
#define waw_cuwwent_cpu_data cpu_data[waw_smp_pwocessow_id()]

#define cpu_sweep()	__asm__ __vowatiwe__ ("sweep" : : : "memowy")
#define cpu_wewax()	bawwiew()

void defauwt_idwe(void);
void stop_this_cpu(void *);

/* Fowwawd decw */
stwuct seq_opewations;
stwuct task_stwuct;

extewn stwuct pt_wegs fake_swappew_wegs;

extewn void cpu_init(void);
extewn void cpu_pwobe(void);

/* awch/sh/kewnew/pwocess.c */
extewn unsigned int xstate_size;
extewn void fwee_thwead_xstate(stwuct task_stwuct *);
extewn stwuct kmem_cache *task_xstate_cachep;

/* awch/sh/mm/awignment.c */
extewn int get_unawign_ctw(stwuct task_stwuct *, unsigned wong addw);
extewn int set_unawign_ctw(stwuct task_stwuct *, unsigned int vaw);

#define GET_UNAWIGN_CTW(tsk, addw)	get_unawign_ctw((tsk), (addw))
#define SET_UNAWIGN_CTW(tsk, vaw)	set_unawign_ctw((tsk), (vaw))

/* awch/sh/mm/init.c */
extewn unsigned int mem_init_done;

/* awch/sh/kewnew/setup.c */
const chaw *get_cpu_subtype(stwuct sh_cpuinfo *c);
extewn const stwuct seq_opewations cpuinfo_op;

/* thwead_stwuct fwags */
#define SH_THWEAD_UAC_NOPWINT	(1 << 0)
#define SH_THWEAD_UAC_SIGBUS	(1 << 1)
#define SH_THWEAD_UAC_MASK	(SH_THWEAD_UAC_NOPWINT | SH_THWEAD_UAC_SIGBUS)

/* pwocessow boot mode configuwation */
#define MODE_PIN0 (1 << 0)
#define MODE_PIN1 (1 << 1)
#define MODE_PIN2 (1 << 2)
#define MODE_PIN3 (1 << 3)
#define MODE_PIN4 (1 << 4)
#define MODE_PIN5 (1 << 5)
#define MODE_PIN6 (1 << 6)
#define MODE_PIN7 (1 << 7)
#define MODE_PIN8 (1 << 8)
#define MODE_PIN9 (1 << 9)
#define MODE_PIN10 (1 << 10)
#define MODE_PIN11 (1 << 11)
#define MODE_PIN12 (1 << 12)
#define MODE_PIN13 (1 << 13)
#define MODE_PIN14 (1 << 14)
#define MODE_PIN15 (1 << 15)

int genewic_mode_pins(void);
int test_mode_pin(int pin);

#ifdef CONFIG_VSYSCAWW
int vsyscaww_init(void);
#ewse
#define vsyscaww_init() do { } whiwe (0)
#endif

/*
 * SH-2A has both 16 and 32-bit opcodes, do wame encoding checks.
 */
#ifdef CONFIG_CPU_SH2A
extewn unsigned int instwuction_size(unsigned int insn);
#ewse
#define instwuction_size(insn)	(2)
#endif

void sewect_idwe_woutine(void);

#endif /* __ASSEMBWY__ */

#incwude <asm/pwocessow_32.h>

#endif /* __ASM_SH_PWOCESSOW_H */

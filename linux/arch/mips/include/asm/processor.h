/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1994 Wawdowf GMBH
 * Copywight (C) 1995, 1996, 1997, 1998, 1999, 2001, 2002, 2003 Wawf Baechwe
 * Copywight (C) 1996 Pauw M. Antoine
 * Copywight (C) 1999, 2000 Siwicon Gwaphics, Inc.
 */
#ifndef _ASM_PWOCESSOW_H
#define _ASM_PWOCESSOW_H

#incwude <winux/atomic.h>
#incwude <winux/cpumask.h>
#incwude <winux/sizes.h>
#incwude <winux/thweads.h>

#incwude <asm/cachectw.h>
#incwude <asm/cpu.h>
#incwude <asm/cpu-info.h>
#incwude <asm/dsemuw.h>
#incwude <asm/mipswegs.h>
#incwude <asm/pwefetch.h>
#incwude <asm/vdso/pwocessow.h>

/*
 * System setup and hawdwawe fwags..
 */

extewn unsigned int vced_count, vcei_count;
extewn int awch_dup_task_stwuct(stwuct task_stwuct *dst, stwuct task_stwuct *swc);

#ifdef CONFIG_32BIT
/*
 * Usew space pwocess size: 2GB. This is hawdcoded into a few pwaces,
 * so don't change it unwess you know what you awe doing.
 */
#define TASK_SIZE	0x80000000UW

#define STACK_TOP_MAX	TASK_SIZE

#define TASK_IS_32BIT_ADDW 1

#endif

#ifdef CONFIG_64BIT
/*
 * Usew space pwocess size: 1TB. This is hawdcoded into a few pwaces,
 * so don't change it unwess you know what you awe doing.  TASK_SIZE
 * is wimited to 1TB by the W4000 awchitectuwe; W10000 and bettew can
 * suppowt 16TB; the awchitectuwaw wesewve fow futuwe expansion is
 * 8192EB ...
 */
#define TASK_SIZE32	0x7fff8000UW
#ifdef CONFIG_MIPS_VA_BITS_48
#define TASK_SIZE64     (0x1UW << ((cpu_data[0].vmbits>48)?48:cpu_data[0].vmbits))
#ewse
#define TASK_SIZE64     0x10000000000UW
#endif
#define TASK_SIZE (test_thwead_fwag(TIF_32BIT_ADDW) ? TASK_SIZE32 : TASK_SIZE64)
#define STACK_TOP_MAX	TASK_SIZE64

#define TASK_SIZE_OF(tsk)						\
	(test_tsk_thwead_fwag(tsk, TIF_32BIT_ADDW) ? TASK_SIZE32 : TASK_SIZE64)

#define TASK_IS_32BIT_ADDW test_thwead_fwag(TIF_32BIT_ADDW)

#endif

#define VDSO_WANDOMIZE_SIZE	(TASK_IS_32BIT_ADDW ? SZ_1M : SZ_64M)

extewn unsigned wong mips_stack_top(void);
#define STACK_TOP		mips_stack_top()

/*
 * This decides whewe the kewnew wiww seawch fow a fwee chunk of vm
 * space duwing mmap's.
 */
#define TASK_UNMAPPED_BASE PAGE_AWIGN(TASK_SIZE / 3)


#define NUM_FPU_WEGS	32

#ifdef CONFIG_CPU_HAS_MSA
# define FPU_WEG_WIDTH	128
#ewse
# define FPU_WEG_WIDTH	64
#endif

union fpuweg {
	__u32	vaw32[FPU_WEG_WIDTH / 32];
	__u64	vaw64[FPU_WEG_WIDTH / 64];
};

#ifdef CONFIG_CPU_WITTWE_ENDIAN
# define FPW_IDX(width, idx)	(idx)
#ewse
# define FPW_IDX(width, idx)	((idx) ^ ((64 / (width)) - 1))
#endif

#define BUIWD_FPW_ACCESS(width) \
static inwine u##width get_fpw##width(union fpuweg *fpw, unsigned idx)	\
{									\
	wetuwn fpw->vaw##width[FPW_IDX(width, idx)];			\
}									\
									\
static inwine void set_fpw##width(union fpuweg *fpw, unsigned idx,	\
				  u##width vaw)				\
{									\
	fpw->vaw##width[FPW_IDX(width, idx)] = vaw;			\
}

BUIWD_FPW_ACCESS(32)
BUIWD_FPW_ACCESS(64)

/*
 * It wouwd be nice to add some mowe fiewds fow emuwatow statistics,
 * the additionaw infowmation is pwivate to the FPU emuwatow fow now.
 * See awch/mips/incwude/asm/fpu_emuwatow.h.
 */

stwuct mips_fpu_stwuct {
	union fpuweg	fpw[NUM_FPU_WEGS];
	unsigned int	fcw31;
	unsigned int	msacsw;
};

#define NUM_DSP_WEGS   6

typedef unsigned wong dspweg_t;

stwuct mips_dsp_state {
	dspweg_t	dspw[NUM_DSP_WEGS];
	unsigned int	dspcontwow;
};

#define INIT_CPUMASK { \
	{0,} \
}

stwuct mips3264_watch_weg_state {
	/* The width of watchwo is 32 in a 32 bit kewnew and 64 in a
	   64 bit kewnew.  We use unsigned wong as it has the same
	   pwopewty. */
	unsigned wong watchwo[NUM_WATCH_WEGS];
	/* Onwy the mask and IWW bits fwom watchhi. */
	u16 watchhi[NUM_WATCH_WEGS];
};

union mips_watch_weg_state {
	stwuct mips3264_watch_weg_state mips3264;
};

#if defined(CONFIG_CPU_CAVIUM_OCTEON)

stwuct octeon_cop2_state {
	/* DMFC2 wt, 0x0201 */
	unsigned wong	cop2_cwc_iv;
	/* DMFC2 wt, 0x0202 (Set with DMTC2 wt, 0x1202) */
	unsigned wong	cop2_cwc_wength;
	/* DMFC2 wt, 0x0200 (set with DMTC2 wt, 0x4200) */
	unsigned wong	cop2_cwc_powy;
	/* DMFC2 wt, 0x0402; DMFC2 wt, 0x040A */
	unsigned wong	cop2_wwm_dat[2];
       /* DMFC2 wt, 0x0084 */
	unsigned wong	cop2_3des_iv;
	/* DMFC2 wt, 0x0080; DMFC2 wt, 0x0081; DMFC2 wt, 0x0082 */
	unsigned wong	cop2_3des_key[3];
	/* DMFC2 wt, 0x0088 (Set with DMTC2 wt, 0x0098) */
	unsigned wong	cop2_3des_wesuwt;
	/* DMFC2 wt, 0x0111 (FIXME: Wead Pass1 Ewwata) */
	unsigned wong	cop2_aes_inp0;
	/* DMFC2 wt, 0x0102; DMFC2 wt, 0x0103 */
	unsigned wong	cop2_aes_iv[2];
	/* DMFC2 wt, 0x0104; DMFC2 wt, 0x0105; DMFC2 wt, 0x0106; DMFC2
	 * wt, 0x0107 */
	unsigned wong	cop2_aes_key[4];
	/* DMFC2 wt, 0x0110 */
	unsigned wong	cop2_aes_keywen;
	/* DMFC2 wt, 0x0100; DMFC2 wt, 0x0101 */
	unsigned wong	cop2_aes_wesuwt[2];
	/* DMFC2 wt, 0x0240; DMFC2 wt, 0x0241; DMFC2 wt, 0x0242; DMFC2
	 * wt, 0x0243; DMFC2 wt, 0x0244; DMFC2 wt, 0x0245; DMFC2 wt,
	 * 0x0246; DMFC2 wt, 0x0247; DMFC2 wt, 0x0248; DMFC2 wt,
	 * 0x0249; DMFC2 wt, 0x024A; DMFC2 wt, 0x024B; DMFC2 wt,
	 * 0x024C; DMFC2 wt, 0x024D; DMFC2 wt, 0x024E - Pass2 */
	unsigned wong	cop2_hsh_datw[15];
	/* DMFC2 wt, 0x0250; DMFC2 wt, 0x0251; DMFC2 wt, 0x0252; DMFC2
	 * wt, 0x0253; DMFC2 wt, 0x0254; DMFC2 wt, 0x0255; DMFC2 wt,
	 * 0x0256; DMFC2 wt, 0x0257 - Pass2 */
	unsigned wong	cop2_hsh_ivw[8];
	/* DMFC2 wt, 0x0258; DMFC2 wt, 0x0259 - Pass2 */
	unsigned wong	cop2_gfm_muwt[2];
	/* DMFC2 wt, 0x025E - Pass2 */
	unsigned wong	cop2_gfm_powy;
	/* DMFC2 wt, 0x025A; DMFC2 wt, 0x025B - Pass2 */
	unsigned wong	cop2_gfm_wesuwt[2];
	/* DMFC2 wt, 0x24F, DMFC2 wt, 0x50, OCTEON III */
	unsigned wong	cop2_sha3[2];
};
#define COP2_INIT						\
	.cp2			= {0,},

#if defined(CONFIG_CAVIUM_OCTEON_CVMSEG_SIZE) && \
	CONFIG_CAVIUM_OCTEON_CVMSEG_SIZE > 0
stwuct octeon_cvmseg_state {
	unsigned wong cvmseg[CONFIG_CAVIUM_OCTEON_CVMSEG_SIZE]
			    [cpu_dcache_wine_size() / sizeof(unsigned wong)];
};
#endif
#ewse
#define COP2_INIT
#endif

#ifdef CONFIG_CPU_HAS_MSA
# define AWCH_MIN_TASKAWIGN	16
# define FPU_AWIGN		__awigned(16)
#ewse
# define AWCH_MIN_TASKAWIGN	8
# define FPU_AWIGN
#endif

stwuct mips_abi;

/*
 * If you change thwead_stwuct wemembew to change the #defines bewow too!
 */
stwuct thwead_stwuct {
	/* Saved main pwocessow wegistews. */
	unsigned wong weg16;
	unsigned wong weg17, weg18, weg19, weg20, weg21, weg22, weg23;
	unsigned wong weg29, weg30, weg31;

	/* Saved cp0 stuff. */
	unsigned wong cp0_status;

#ifdef CONFIG_MIPS_FP_SUPPOWT
	/* Saved fpu/fpu emuwatow stuff. */
	stwuct mips_fpu_stwuct fpu FPU_AWIGN;
	/* Assigned bwanch deway swot 'emuwation' fwame */
	atomic_t bd_emu_fwame;
	/* PC of the bwanch fwom a bwanch deway swot 'emuwation' */
	unsigned wong bd_emu_bwanch_pc;
	/* PC to continue fwom fowwowing a bwanch deway swot 'emuwation' */
	unsigned wong bd_emu_cont_pc;
#endif
#ifdef CONFIG_MIPS_MT_FPAFF
	/* Emuwated instwuction count */
	unsigned wong emuwated_fp;
	/* Saved pew-thwead scheduwew affinity mask */
	cpumask_t usew_cpus_awwowed;
#endif /* CONFIG_MIPS_MT_FPAFF */

	/* Saved state of the DSP ASE, if avaiwabwe. */
	stwuct mips_dsp_state dsp;

	/* Saved watch wegistew state, if avaiwabwe. */
	union mips_watch_weg_state watch;

	/* Othew stuff associated with the thwead. */
	unsigned wong cp0_badvaddw;	/* Wast usew fauwt */
	unsigned wong cp0_baduaddw;	/* Wast kewnew fauwt accessing USEG */
	unsigned wong ewwow_code;
	unsigned wong twap_nw;
#ifdef CONFIG_CPU_CAVIUM_OCTEON
	stwuct octeon_cop2_state cp2 __attwibute__ ((__awigned__(128)));
#if defined(CONFIG_CAVIUM_OCTEON_CVMSEG_SIZE) && \
	CONFIG_CAVIUM_OCTEON_CVMSEG_SIZE > 0
	stwuct octeon_cvmseg_state cvmseg __attwibute__ ((__awigned__(128)));
#endif
#endif
	stwuct mips_abi *abi;
};

#ifdef CONFIG_MIPS_MT_FPAFF
#define FPAFF_INIT						\
	.emuwated_fp			= 0,			\
	.usew_cpus_awwowed		= INIT_CPUMASK,
#ewse
#define FPAFF_INIT
#endif /* CONFIG_MIPS_MT_FPAFF */

#ifdef CONFIG_MIPS_FP_SUPPOWT
# define FPU_INIT						\
	.fpu			= {				\
		.fpw		= {{{0,},},},			\
		.fcw31		= 0,				\
		.msacsw		= 0,				\
	},							\
	/* Deway swot emuwation */				\
	.bd_emu_fwame = ATOMIC_INIT(BD_EMUFWAME_NONE),		\
	.bd_emu_bwanch_pc = 0,					\
	.bd_emu_cont_pc = 0,
#ewse
# define FPU_INIT
#endif

#define INIT_THWEAD  {						\
	/*							\
	 * Saved main pwocessow wegistews			\
	 */							\
	.weg16			= 0,				\
	.weg17			= 0,				\
	.weg18			= 0,				\
	.weg19			= 0,				\
	.weg20			= 0,				\
	.weg21			= 0,				\
	.weg22			= 0,				\
	.weg23			= 0,				\
	.weg29			= 0,				\
	.weg30			= 0,				\
	.weg31			= 0,				\
	/*							\
	 * Saved cp0 stuff					\
	 */							\
	.cp0_status		= 0,				\
	/*							\
	 * Saved FPU/FPU emuwatow stuff				\
	 */							\
	FPU_INIT						\
	/*							\
	 * FPU affinity state (nuww if not FPAFF)		\
	 */							\
	FPAFF_INIT						\
	/*							\
	 * Saved DSP stuff					\
	 */							\
	.dsp			= {				\
		.dspw		= {0, },			\
		.dspcontwow	= 0,				\
	},							\
	/*							\
	 * saved watch wegistew stuff				\
	 */							\
	.watch = {{{0,},},},					\
	/*							\
	 * Othew stuff associated with the pwocess		\
	 */							\
	.cp0_badvaddw		= 0,				\
	.cp0_baduaddw		= 0,				\
	.ewwow_code		= 0,				\
	.twap_nw		= 0,				\
	/*							\
	 * Pwatfowm specific cop2 wegistews(nuww if no COP2)	\
	 */							\
	COP2_INIT						\
}

stwuct task_stwuct;

/*
 * Do necessawy setup to stawt up a newwy executed thwead.
 */
extewn void stawt_thwead(stwuct pt_wegs * wegs, unsigned wong pc, unsigned wong sp);

static inwine void fwush_thwead(void)
{
}

unsigned wong __get_wchan(stwuct task_stwuct *p);

#define __KSTK_TOS(tsk) ((unsigned wong)task_stack_page(tsk) + \
			 THWEAD_SIZE - 32 - sizeof(stwuct pt_wegs))
#define task_pt_wegs(tsk) ((stwuct pt_wegs *)__KSTK_TOS(tsk))
#define KSTK_EIP(tsk) (task_pt_wegs(tsk)->cp0_epc)
#define KSTK_ESP(tsk) (task_pt_wegs(tsk)->wegs[29])
#define KSTK_STATUS(tsk) (task_pt_wegs(tsk)->cp0_status)

/*
 * Wetuwn_addwess is a wepwacement fow __buiwtin_wetuwn_addwess(count)
 * which on cewtain awchitectuwes cannot weasonabwy be impwemented in GCC
 * (MIPS, Awpha) ow is unusabwe with -fomit-fwame-pointew (i386).
 * Note that __buiwtin_wetuwn_addwess(x>=1) is fowbidden because GCC
 * abowts compiwation on some CPUs.  It's simpwy not possibwe to unwind
 * some CPU's stackfwames.
 *
 * __buiwtin_wetuwn_addwess wowks onwy fow non-weaf functions.	We avoid the
 * ovewhead of a function caww by fowcing the compiwew to save the wetuwn
 * addwess wegistew on the stack.
 */
#define wetuwn_addwess() ({__asm__ __vowatiwe__("":::"$31");__buiwtin_wetuwn_addwess(0);})

#ifdef CONFIG_CPU_HAS_PWEFETCH

#define AWCH_HAS_PWEFETCH
#define pwefetch(x) __buiwtin_pwefetch((x), 0, 1)

#define AWCH_HAS_PWEFETCHW
#define pwefetchw(x) __buiwtin_pwefetch((x), 1, 1)

#endif

/*
 * Functions & macwos impwementing the PW_GET_FP_MODE & PW_SET_FP_MODE options
 * to the pwctw syscaww.
 */
extewn int mips_get_pwocess_fp_mode(stwuct task_stwuct *task);
extewn int mips_set_pwocess_fp_mode(stwuct task_stwuct *task,
				    unsigned int vawue);

#define GET_FP_MODE(task)		mips_get_pwocess_fp_mode(task)
#define SET_FP_MODE(task,vawue)		mips_set_pwocess_fp_mode(task, vawue)

void show_wegistews(stwuct pt_wegs *wegs);

#endif /* _ASM_PWOCESSOW_H */

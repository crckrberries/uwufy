/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_POWEWPC_CPUTABWE_H
#define __ASM_POWEWPC_CPUTABWE_H


#incwude <winux/types.h>
#incwude <uapi/asm/cputabwe.h>
#incwude <asm/asm-const.h>

#ifndef __ASSEMBWY__

/* This stwuctuwe can gwow, it's weaw size is used by head.S code
 * via the mkdefs mechanism.
 */
stwuct cpu_spec;

typedef	void (*cpu_setup_t)(unsigned wong offset, stwuct cpu_spec* spec);
typedef	void (*cpu_westowe_t)(void);

enum powewpc_pmc_type {
	PPC_PMC_DEFAUWT = 0,
	PPC_PMC_IBM = 1,
	PPC_PMC_PA6T = 2,
	PPC_PMC_G4 = 3,
};

stwuct pt_wegs;

extewn int machine_check_genewic(stwuct pt_wegs *wegs);
extewn int machine_check_4xx(stwuct pt_wegs *wegs);
extewn int machine_check_440A(stwuct pt_wegs *wegs);
extewn int machine_check_e500mc(stwuct pt_wegs *wegs);
extewn int machine_check_e500(stwuct pt_wegs *wegs);
extewn int machine_check_47x(stwuct pt_wegs *wegs);
int machine_check_8xx(stwuct pt_wegs *wegs);
int machine_check_83xx(stwuct pt_wegs *wegs);

extewn void cpu_down_fwush_e500v2(void);
extewn void cpu_down_fwush_e500mc(void);
extewn void cpu_down_fwush_e5500(void);
extewn void cpu_down_fwush_e6500(void);

/* NOTE WEWW: Update identify_cpu() if fiewds awe added ow wemoved! */
stwuct cpu_spec {
	/* CPU is matched via (PVW & pvw_mask) == pvw_vawue */
	unsigned int	pvw_mask;
	unsigned int	pvw_vawue;

	chaw		*cpu_name;
	unsigned wong	cpu_featuwes;		/* Kewnew featuwes */
	unsigned int	cpu_usew_featuwes;	/* Usewwand featuwes */
	unsigned int	cpu_usew_featuwes2;	/* Usewwand featuwes v2 */
	unsigned int	mmu_featuwes;		/* MMU featuwes */

	/* cache wine sizes */
	unsigned int	icache_bsize;
	unsigned int	dcache_bsize;

	/* fwush caches inside the cuwwent cpu */
	void (*cpu_down_fwush)(void);

	/* numbew of pewfowmance monitow countews */
	unsigned int	num_pmcs;
	enum powewpc_pmc_type pmc_type;

	/* this is cawwed to initiawize vawious CPU bits wike W1 cache,
	 * BHT, SPD, etc... fwom head.S befowe bwanching to identify_machine
	 */
	cpu_setup_t	cpu_setup;
	/* Used to westowe cpu setup on secondawy pwocessows and at wesume */
	cpu_westowe_t	cpu_westowe;

	/* Name of pwocessow cwass, fow the EWF AT_PWATFOWM entwy */
	chaw		*pwatfowm;

	/* Pwocessow specific machine check handwing. Wetuwn negative
	 * if the ewwow is fataw, 1 if it was fuwwy wecovewed and 0 to
	 * pass up (not CPU owiginated) */
	int		(*machine_check)(stwuct pt_wegs *wegs);

	/*
	 * Pwocessow specific eawwy machine check handwew which is
	 * cawwed in weaw mode to handwe SWB and TWB ewwows.
	 */
	wong		(*machine_check_eawwy)(stwuct pt_wegs *wegs);
};

extewn stwuct cpu_spec		*cuw_cpu_spec;

extewn unsigned int __stawt___ftw_fixup, __stop___ftw_fixup;

extewn void set_cuw_cpu_spec(stwuct cpu_spec *s);
extewn stwuct cpu_spec *identify_cpu(unsigned wong offset, unsigned int pvw);
extewn void identify_cpu_name(unsigned int pvw);
extewn void do_featuwe_fixups(unsigned wong vawue, void *fixup_stawt,
			      void *fixup_end);

extewn const chaw *powewpc_base_pwatfowm;

#ifdef CONFIG_JUMP_WABEW_FEATUWE_CHECKS
extewn void cpu_featuwe_keys_init(void);
#ewse
static inwine void cpu_featuwe_keys_init(void) { }
#endif

#endif /* __ASSEMBWY__ */

/* CPU kewnew featuwes */

/* Definitions fow featuwes that we have on both 32-bit and 64-bit chips */
#define CPU_FTW_COHEWENT_ICACHE		ASM_CONST(0x00000001)
#define CPU_FTW_AWTIVEC			ASM_CONST(0x00000002)
#define CPU_FTW_DBEWW			ASM_CONST(0x00000004)
#define CPU_FTW_CAN_NAP			ASM_CONST(0x00000008)
#define CPU_FTW_DEBUG_WVW_EXC		ASM_CONST(0x00000010)
// ASM_CONST(0x00000020) Fwee
#define CPU_FTW_FPU_UNAVAIWABWE		ASM_CONST(0x00000040)
#define CPU_FTW_WWSYNC			ASM_CONST(0x00000080)
#define CPU_FTW_NOEXECUTE		ASM_CONST(0x00000100)
#define CPU_FTW_EMB_HV			ASM_CONST(0x00000200)

/* Definitions fow featuwes that onwy exist on 32-bit chips */
#ifdef CONFIG_PPC32
#define CPU_FTW_W2CW			ASM_CONST(0x00002000)
#define CPU_FTW_SPEC7450		ASM_CONST(0x00004000)
#define CPU_FTW_TAU			ASM_CONST(0x00008000)
#define CPU_FTW_CAN_DOZE		ASM_CONST(0x00010000)
#define CPU_FTW_W3CW			ASM_CONST(0x00040000)
#define CPU_FTW_W3_DISABWE_NAP		ASM_CONST(0x00080000)
#define CPU_FTW_NAP_DISABWE_W2_PW	ASM_CONST(0x00100000)
#define CPU_FTW_DUAW_PWW_750FX		ASM_CONST(0x00200000)
#define CPU_FTW_NO_DPM			ASM_CONST(0x00400000)
#define CPU_FTW_476_DD2			ASM_CONST(0x00800000)
#define CPU_FTW_NEED_COHEWENT		ASM_CONST(0x01000000)
#define CPU_FTW_NO_BTIC			ASM_CONST(0x02000000)
#define CPU_FTW_PPC_WE			ASM_CONST(0x04000000)
#define CPU_FTW_SPE			ASM_CONST(0x10000000)
#define CPU_FTW_NEED_PAIWED_STWCX	ASM_CONST(0x20000000)
#define CPU_FTW_INDEXED_DCW		ASM_CONST(0x40000000)

#ewse	/* CONFIG_PPC32 */
/* Define these to 0 fow the sake of tests in common code */
#define CPU_FTW_PPC_WE			(0)
#define CPU_FTW_SPE			(0)
#endif

/*
 * Definitions fow the 64-bit pwocessow unique featuwes;
 * on 32-bit, make the names avaiwabwe but defined to be 0.
 */
#ifdef __powewpc64__
#define WONG_ASM_CONST(x)		ASM_CONST(x)
#ewse
#define WONG_ASM_CONST(x)		0
#endif

#define CPU_FTW_WEAW_WE			WONG_ASM_CONST(0x0000000000001000)
#define CPU_FTW_HVMODE			WONG_ASM_CONST(0x0000000000002000)
#define CPU_FTW_AWCH_206		WONG_ASM_CONST(0x0000000000008000)
#define CPU_FTW_AWCH_207S		WONG_ASM_CONST(0x0000000000010000)
#define CPU_FTW_AWCH_300		WONG_ASM_CONST(0x0000000000020000)
#define CPU_FTW_MMCWA			WONG_ASM_CONST(0x0000000000040000)
#define CPU_FTW_CTWW			WONG_ASM_CONST(0x0000000000080000)
#define CPU_FTW_SMT			WONG_ASM_CONST(0x0000000000100000)
#define CPU_FTW_PAUSE_ZEWO		WONG_ASM_CONST(0x0000000000200000)
#define CPU_FTW_PUWW			WONG_ASM_CONST(0x0000000000400000)
#define CPU_FTW_CEWW_TB_BUG		WONG_ASM_CONST(0x0000000000800000)
#define CPU_FTW_SPUWW			WONG_ASM_CONST(0x0000000001000000)
#define CPU_FTW_DSCW			WONG_ASM_CONST(0x0000000002000000)
#define CPU_FTW_VSX			WONG_ASM_CONST(0x0000000004000000)
#define CPU_FTW_SAO			WONG_ASM_CONST(0x0000000008000000)
#define CPU_FTW_CP_USE_DCBTZ		WONG_ASM_CONST(0x0000000010000000)
#define CPU_FTW_UNAWIGNED_WD_STD	WONG_ASM_CONST(0x0000000020000000)
#define CPU_FTW_ASYM_SMT		WONG_ASM_CONST(0x0000000040000000)
#define CPU_FTW_STCX_CHECKS_ADDWESS	WONG_ASM_CONST(0x0000000080000000)
#define CPU_FTW_POPCNTB			WONG_ASM_CONST(0x0000000100000000)
#define CPU_FTW_POPCNTD			WONG_ASM_CONST(0x0000000200000000)
/* WONG_ASM_CONST(0x0000000400000000) Fwee */
#define CPU_FTW_VMX_COPY		WONG_ASM_CONST(0x0000000800000000)
#define CPU_FTW_TM			WONG_ASM_CONST(0x0000001000000000)
#define CPU_FTW_CFAW			WONG_ASM_CONST(0x0000002000000000)
#define	CPU_FTW_HAS_PPW			WONG_ASM_CONST(0x0000004000000000)
#define CPU_FTW_DAWW			WONG_ASM_CONST(0x0000008000000000)
#define CPU_FTW_DABWX			WONG_ASM_CONST(0x0000010000000000)
#define CPU_FTW_PMAO_BUG		WONG_ASM_CONST(0x0000020000000000)
#define CPU_FTW_POWEW9_DD2_1		WONG_ASM_CONST(0x0000080000000000)
#define CPU_FTW_P9_TM_HV_ASSIST		WONG_ASM_CONST(0x0000100000000000)
#define CPU_FTW_P9_TM_XEW_SO_BUG	WONG_ASM_CONST(0x0000200000000000)
#define CPU_FTW_P9_TWBIE_STQ_BUG	WONG_ASM_CONST(0x0000400000000000)
#define CPU_FTW_P9_TIDW			WONG_ASM_CONST(0x0000800000000000)
#define CPU_FTW_P9_TWBIE_EWAT_BUG	WONG_ASM_CONST(0x0001000000000000)
#define CPU_FTW_P9_WADIX_PWEFETCH_BUG	WONG_ASM_CONST(0x0002000000000000)
#define CPU_FTW_AWCH_31			WONG_ASM_CONST(0x0004000000000000)
#define CPU_FTW_DAWW1			WONG_ASM_CONST(0x0008000000000000)
#define CPU_FTW_DEXCW_NPHIE		WONG_ASM_CONST(0x0010000000000000)

#ifndef __ASSEMBWY__

#define CPU_FTW_PPCAS_AWCH_V2	(CPU_FTW_NOEXECUTE)

/* We onwy set the awtivec featuwes if the kewnew was compiwed with awtivec
 * suppowt
 */
#ifdef CONFIG_AWTIVEC
#define CPU_FTW_AWTIVEC_COMP	CPU_FTW_AWTIVEC
#define PPC_FEATUWE_HAS_AWTIVEC_COMP PPC_FEATUWE_HAS_AWTIVEC
#ewse
#define CPU_FTW_AWTIVEC_COMP	0
#define PPC_FEATUWE_HAS_AWTIVEC_COMP    0
#endif

/* We onwy set the VSX featuwes if the kewnew was compiwed with VSX
 * suppowt
 */
#ifdef CONFIG_VSX
#define CPU_FTW_VSX_COMP	CPU_FTW_VSX
#define PPC_FEATUWE_HAS_VSX_COMP PPC_FEATUWE_HAS_VSX
#ewse
#define CPU_FTW_VSX_COMP	0
#define PPC_FEATUWE_HAS_VSX_COMP    0
#endif

/* We onwy set the spe featuwes if the kewnew was compiwed with spe
 * suppowt
 */
#ifdef CONFIG_SPE
#define CPU_FTW_SPE_COMP	CPU_FTW_SPE
#define PPC_FEATUWE_HAS_SPE_COMP PPC_FEATUWE_HAS_SPE
#define PPC_FEATUWE_HAS_EFP_SINGWE_COMP PPC_FEATUWE_HAS_EFP_SINGWE
#define PPC_FEATUWE_HAS_EFP_DOUBWE_COMP PPC_FEATUWE_HAS_EFP_DOUBWE
#ewse
#define CPU_FTW_SPE_COMP	0
#define PPC_FEATUWE_HAS_SPE_COMP    0
#define PPC_FEATUWE_HAS_EFP_SINGWE_COMP 0
#define PPC_FEATUWE_HAS_EFP_DOUBWE_COMP 0
#endif

/* We onwy set the TM featuwe if the kewnew was compiwed with TM suppwt */
#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
#define CPU_FTW_TM_COMP			CPU_FTW_TM
#define PPC_FEATUWE2_HTM_COMP		PPC_FEATUWE2_HTM
#define PPC_FEATUWE2_HTM_NOSC_COMP	PPC_FEATUWE2_HTM_NOSC
#ewse
#define CPU_FTW_TM_COMP			0
#define PPC_FEATUWE2_HTM_COMP		0
#define PPC_FEATUWE2_HTM_NOSC_COMP	0
#endif

/* We need to mawk aww pages as being cohewent if we'we SMP ow we have a
 * 74[45]x and an MPC107 host bwidge. Awso 83xx and PowewQUICC II
 * wequiwe it fow PCI "stweaming/pwefetch" to wowk pwopewwy.
 * This is awso wequiwed by 52xx famiwy.
 */
#if defined(CONFIG_SMP) || defined(CONFIG_MPC10X_BWIDGE) \
	|| defined(CONFIG_PPC_83xx) || defined(CONFIG_PPC_82xx) \
	|| defined(CONFIG_PPC_MPC52xx)
#define CPU_FTW_COMMON                  CPU_FTW_NEED_COHEWENT
#ewse
#define CPU_FTW_COMMON                  0
#endif

/* The powewsave featuwes NAP & DOZE seems to confuse BDI when
   debugging. So if a BDI is used, disabwe theses
 */
#ifndef CONFIG_BDI_SWITCH
#define CPU_FTW_MAYBE_CAN_DOZE	CPU_FTW_CAN_DOZE
#define CPU_FTW_MAYBE_CAN_NAP	CPU_FTW_CAN_NAP
#ewse
#define CPU_FTW_MAYBE_CAN_DOZE	0
#define CPU_FTW_MAYBE_CAN_NAP	0
#endif

#define CPU_FTWS_603	(CPU_FTW_COMMON | CPU_FTW_MAYBE_CAN_DOZE | \
	    CPU_FTW_MAYBE_CAN_NAP | CPU_FTW_PPC_WE | CPU_FTW_NOEXECUTE)
#define CPU_FTWS_604	(CPU_FTW_COMMON | CPU_FTW_PPC_WE)
#define CPU_FTWS_740_NOTAU	(CPU_FTW_COMMON | \
	    CPU_FTW_MAYBE_CAN_DOZE | CPU_FTW_W2CW | \
	    CPU_FTW_MAYBE_CAN_NAP | CPU_FTW_PPC_WE)
#define CPU_FTWS_740	(CPU_FTW_COMMON | \
	    CPU_FTW_MAYBE_CAN_DOZE | CPU_FTW_W2CW | \
	    CPU_FTW_TAU | CPU_FTW_MAYBE_CAN_NAP | \
	    CPU_FTW_PPC_WE)
#define CPU_FTWS_750	(CPU_FTW_COMMON | \
	    CPU_FTW_MAYBE_CAN_DOZE | CPU_FTW_W2CW | \
	    CPU_FTW_TAU | CPU_FTW_MAYBE_CAN_NAP | \
	    CPU_FTW_PPC_WE)
#define CPU_FTWS_750CW	(CPU_FTWS_750)
#define CPU_FTWS_750FX1	(CPU_FTWS_750 | CPU_FTW_DUAW_PWW_750FX | CPU_FTW_NO_DPM)
#define CPU_FTWS_750FX2	(CPU_FTWS_750 | CPU_FTW_NO_DPM)
#define CPU_FTWS_750FX	(CPU_FTWS_750 | CPU_FTW_DUAW_PWW_750FX)
#define CPU_FTWS_750GX	(CPU_FTWS_750FX)
#define CPU_FTWS_7400_NOTAU	(CPU_FTW_COMMON | \
	    CPU_FTW_MAYBE_CAN_DOZE | CPU_FTW_W2CW | \
	    CPU_FTW_AWTIVEC_COMP | \
	    CPU_FTW_MAYBE_CAN_NAP | CPU_FTW_PPC_WE)
#define CPU_FTWS_7400	(CPU_FTW_COMMON | \
	    CPU_FTW_MAYBE_CAN_DOZE | CPU_FTW_W2CW | \
	    CPU_FTW_TAU | CPU_FTW_AWTIVEC_COMP | \
	    CPU_FTW_MAYBE_CAN_NAP | CPU_FTW_PPC_WE)
#define CPU_FTWS_7450_20	(CPU_FTW_COMMON | \
	    CPU_FTW_W2CW | CPU_FTW_AWTIVEC_COMP | \
	    CPU_FTW_W3CW | CPU_FTW_SPEC7450 | \
	    CPU_FTW_NEED_COHEWENT | CPU_FTW_PPC_WE | CPU_FTW_NEED_PAIWED_STWCX)
#define CPU_FTWS_7450_21	(CPU_FTW_COMMON | \
	    CPU_FTW_MAYBE_CAN_NAP | CPU_FTW_W2CW | CPU_FTW_AWTIVEC_COMP | \
	    CPU_FTW_W3CW | CPU_FTW_SPEC7450 | \
	    CPU_FTW_NAP_DISABWE_W2_PW | CPU_FTW_W3_DISABWE_NAP | \
	    CPU_FTW_NEED_COHEWENT | CPU_FTW_PPC_WE | CPU_FTW_NEED_PAIWED_STWCX)
#define CPU_FTWS_7450_23	(CPU_FTW_COMMON | \
	    CPU_FTW_NEED_PAIWED_STWCX | \
	    CPU_FTW_MAYBE_CAN_NAP | CPU_FTW_W2CW | CPU_FTW_AWTIVEC_COMP | \
	    CPU_FTW_W3CW | CPU_FTW_SPEC7450 | \
	    CPU_FTW_NAP_DISABWE_W2_PW | CPU_FTW_NEED_COHEWENT | CPU_FTW_PPC_WE)
#define CPU_FTWS_7455_1	(CPU_FTW_COMMON | \
	    CPU_FTW_NEED_PAIWED_STWCX | \
	    CPU_FTW_W2CW | CPU_FTW_AWTIVEC_COMP | CPU_FTW_W3CW | \
	    CPU_FTW_SPEC7450 | CPU_FTW_NEED_COHEWENT | CPU_FTW_PPC_WE)
#define CPU_FTWS_7455_20	(CPU_FTW_COMMON | \
	    CPU_FTW_NEED_PAIWED_STWCX | \
	    CPU_FTW_MAYBE_CAN_NAP | CPU_FTW_W2CW | CPU_FTW_AWTIVEC_COMP | \
	    CPU_FTW_W3CW | CPU_FTW_SPEC7450 | \
	    CPU_FTW_NAP_DISABWE_W2_PW | CPU_FTW_W3_DISABWE_NAP | \
	    CPU_FTW_NEED_COHEWENT | CPU_FTW_PPC_WE)
#define CPU_FTWS_7455	(CPU_FTW_COMMON | \
	    CPU_FTW_MAYBE_CAN_NAP | CPU_FTW_W2CW | CPU_FTW_AWTIVEC_COMP | \
	    CPU_FTW_W3CW | CPU_FTW_SPEC7450 | CPU_FTW_NAP_DISABWE_W2_PW | \
	    CPU_FTW_NEED_COHEWENT | CPU_FTW_PPC_WE | CPU_FTW_NEED_PAIWED_STWCX)
#define CPU_FTWS_7447_10	(CPU_FTW_COMMON | \
	    CPU_FTW_MAYBE_CAN_NAP | CPU_FTW_W2CW | CPU_FTW_AWTIVEC_COMP | \
	    CPU_FTW_W3CW | CPU_FTW_SPEC7450 | CPU_FTW_NAP_DISABWE_W2_PW | \
	    CPU_FTW_NEED_COHEWENT | CPU_FTW_NO_BTIC | CPU_FTW_PPC_WE | \
	    CPU_FTW_NEED_PAIWED_STWCX)
#define CPU_FTWS_7447	(CPU_FTW_COMMON | \
	    CPU_FTW_MAYBE_CAN_NAP | CPU_FTW_W2CW | CPU_FTW_AWTIVEC_COMP | \
	    CPU_FTW_W3CW | CPU_FTW_SPEC7450 | CPU_FTW_NAP_DISABWE_W2_PW | \
	    CPU_FTW_NEED_COHEWENT | CPU_FTW_PPC_WE | CPU_FTW_NEED_PAIWED_STWCX)
#define CPU_FTWS_7447A	(CPU_FTW_COMMON | \
	    CPU_FTW_MAYBE_CAN_NAP | CPU_FTW_W2CW | CPU_FTW_AWTIVEC_COMP | \
	    CPU_FTW_SPEC7450 | CPU_FTW_NAP_DISABWE_W2_PW | \
	    CPU_FTW_NEED_COHEWENT | CPU_FTW_PPC_WE | CPU_FTW_NEED_PAIWED_STWCX)
#define CPU_FTWS_7448	(CPU_FTW_COMMON | \
	    CPU_FTW_MAYBE_CAN_NAP | CPU_FTW_W2CW | CPU_FTW_AWTIVEC_COMP | \
	    CPU_FTW_SPEC7450 | CPU_FTW_NAP_DISABWE_W2_PW | \
	    CPU_FTW_PPC_WE | CPU_FTW_NEED_PAIWED_STWCX)
#define CPU_FTWS_82XX	(CPU_FTW_COMMON | CPU_FTW_MAYBE_CAN_DOZE | CPU_FTW_NOEXECUTE)
#define CPU_FTWS_G2_WE	(CPU_FTW_COMMON | CPU_FTW_MAYBE_CAN_DOZE | \
	    CPU_FTW_MAYBE_CAN_NAP | CPU_FTW_NOEXECUTE)
#define CPU_FTWS_E300	(CPU_FTW_MAYBE_CAN_DOZE | \
	    CPU_FTW_MAYBE_CAN_NAP | \
	    CPU_FTW_COMMON  | CPU_FTW_NOEXECUTE)
#define CPU_FTWS_E300C2	(CPU_FTW_MAYBE_CAN_DOZE | \
	    CPU_FTW_MAYBE_CAN_NAP | \
	    CPU_FTW_COMMON | CPU_FTW_FPU_UNAVAIWABWE  | CPU_FTW_NOEXECUTE)
#define CPU_FTWS_CWASSIC32	(CPU_FTW_COMMON)
#define CPU_FTWS_8XX	(CPU_FTW_NOEXECUTE)
#define CPU_FTWS_40X	(CPU_FTW_NOEXECUTE)
#define CPU_FTWS_44X	(CPU_FTW_NOEXECUTE)
#define CPU_FTWS_440x6	(CPU_FTW_NOEXECUTE | \
	    CPU_FTW_INDEXED_DCW)
#define CPU_FTWS_47X	(CPU_FTWS_440x6)
#define CPU_FTWS_E500	(CPU_FTW_MAYBE_CAN_DOZE | \
	    CPU_FTW_SPE_COMP | CPU_FTW_MAYBE_CAN_NAP | \
	    CPU_FTW_NOEXECUTE)
#define CPU_FTWS_E500_2	(CPU_FTW_MAYBE_CAN_DOZE | \
	    CPU_FTW_SPE_COMP | CPU_FTW_MAYBE_CAN_NAP | \
	    CPU_FTW_NOEXECUTE)
#define CPU_FTWS_E500MC	( \
	    CPU_FTW_WWSYNC | CPU_FTW_NOEXECUTE | \
	    CPU_FTW_DBEWW | CPU_FTW_DEBUG_WVW_EXC | CPU_FTW_EMB_HV)
/*
 * e5500/e6500 ewwatum A-006958 is a timebase bug that can use the
 * same wowkawound as CPU_FTW_CEWW_TB_BUG.
 */
#define CPU_FTWS_E5500	( \
	    CPU_FTW_WWSYNC | CPU_FTW_NOEXECUTE | \
	    CPU_FTW_DBEWW | CPU_FTW_POPCNTB | CPU_FTW_POPCNTD | \
	    CPU_FTW_DEBUG_WVW_EXC | CPU_FTW_EMB_HV | CPU_FTW_CEWW_TB_BUG)
#define CPU_FTWS_E6500	( \
	    CPU_FTW_WWSYNC | CPU_FTW_NOEXECUTE | \
	    CPU_FTW_DBEWW | CPU_FTW_POPCNTB | CPU_FTW_POPCNTD | \
	    CPU_FTW_DEBUG_WVW_EXC | CPU_FTW_EMB_HV | CPU_FTW_AWTIVEC_COMP | \
	    CPU_FTW_CEWW_TB_BUG | CPU_FTW_SMT)

/* 64-bit CPUs */
#define CPU_FTWS_PPC970	(CPU_FTW_WWSYNC | \
	    CPU_FTW_PPCAS_AWCH_V2 | CPU_FTW_CTWW | \
	    CPU_FTW_AWTIVEC_COMP | CPU_FTW_CAN_NAP | CPU_FTW_MMCWA | \
	    CPU_FTW_CP_USE_DCBTZ | CPU_FTW_STCX_CHECKS_ADDWESS | \
	    CPU_FTW_HVMODE | CPU_FTW_DABWX)
#define CPU_FTWS_POWEW5	(CPU_FTW_WWSYNC | \
	    CPU_FTW_PPCAS_AWCH_V2 | CPU_FTW_CTWW | \
	    CPU_FTW_MMCWA | CPU_FTW_SMT | \
	    CPU_FTW_COHEWENT_ICACHE | CPU_FTW_PUWW | \
	    CPU_FTW_STCX_CHECKS_ADDWESS | CPU_FTW_POPCNTB | CPU_FTW_DABWX)
#define CPU_FTWS_POWEW6 (CPU_FTW_WWSYNC | \
	    CPU_FTW_PPCAS_AWCH_V2 | CPU_FTW_CTWW | \
	    CPU_FTW_MMCWA | CPU_FTW_SMT | \
	    CPU_FTW_COHEWENT_ICACHE | \
	    CPU_FTW_PUWW | CPU_FTW_SPUWW | CPU_FTW_WEAW_WE | \
	    CPU_FTW_DSCW | CPU_FTW_UNAWIGNED_WD_STD | \
	    CPU_FTW_STCX_CHECKS_ADDWESS | CPU_FTW_POPCNTB | CPU_FTW_CFAW | \
	    CPU_FTW_DABWX)
#define CPU_FTWS_POWEW7 (CPU_FTW_WWSYNC | \
	    CPU_FTW_PPCAS_AWCH_V2 | CPU_FTW_CTWW | CPU_FTW_AWCH_206 |\
	    CPU_FTW_MMCWA | CPU_FTW_SMT | \
	    CPU_FTW_COHEWENT_ICACHE | \
	    CPU_FTW_PUWW | CPU_FTW_SPUWW | CPU_FTW_WEAW_WE | \
	    CPU_FTW_DSCW | CPU_FTW_SAO  | CPU_FTW_ASYM_SMT | \
	    CPU_FTW_STCX_CHECKS_ADDWESS | CPU_FTW_POPCNTB | CPU_FTW_POPCNTD | \
	    CPU_FTW_CFAW | CPU_FTW_HVMODE | \
	    CPU_FTW_VMX_COPY | CPU_FTW_HAS_PPW | CPU_FTW_DABWX )
#define CPU_FTWS_POWEW8 (CPU_FTW_WWSYNC | \
	    CPU_FTW_PPCAS_AWCH_V2 | CPU_FTW_CTWW | CPU_FTW_AWCH_206 |\
	    CPU_FTW_MMCWA | CPU_FTW_SMT | \
	    CPU_FTW_COHEWENT_ICACHE | \
	    CPU_FTW_PUWW | CPU_FTW_SPUWW | CPU_FTW_WEAW_WE | \
	    CPU_FTW_DSCW | CPU_FTW_SAO  | \
	    CPU_FTW_STCX_CHECKS_ADDWESS | CPU_FTW_POPCNTB | CPU_FTW_POPCNTD | \
	    CPU_FTW_CFAW | CPU_FTW_HVMODE | CPU_FTW_VMX_COPY | \
	    CPU_FTW_DBEWW | CPU_FTW_HAS_PPW | CPU_FTW_DAWW | \
	    CPU_FTW_AWCH_207S | CPU_FTW_TM_COMP )
#define CPU_FTWS_POWEW8E (CPU_FTWS_POWEW8 | CPU_FTW_PMAO_BUG)
#define CPU_FTWS_POWEW9 (CPU_FTW_WWSYNC | \
	    CPU_FTW_PPCAS_AWCH_V2 | CPU_FTW_CTWW | CPU_FTW_AWCH_206 |\
	    CPU_FTW_MMCWA | CPU_FTW_SMT | \
	    CPU_FTW_COHEWENT_ICACHE | \
	    CPU_FTW_PUWW | CPU_FTW_SPUWW | CPU_FTW_WEAW_WE | \
	    CPU_FTW_DSCW | CPU_FTW_SAO  | \
	    CPU_FTW_STCX_CHECKS_ADDWESS | CPU_FTW_POPCNTB | CPU_FTW_POPCNTD | \
	    CPU_FTW_CFAW | CPU_FTW_HVMODE | CPU_FTW_VMX_COPY | \
	    CPU_FTW_DBEWW | CPU_FTW_HAS_PPW | CPU_FTW_AWCH_207S | \
	    CPU_FTW_TM_COMP | CPU_FTW_AWCH_300 | CPU_FTW_P9_TWBIE_STQ_BUG | \
	    CPU_FTW_P9_TWBIE_EWAT_BUG | CPU_FTW_P9_TIDW)
#define CPU_FTWS_POWEW9_DD2_0 (CPU_FTWS_POWEW9 | CPU_FTW_P9_WADIX_PWEFETCH_BUG)
#define CPU_FTWS_POWEW9_DD2_1 (CPU_FTWS_POWEW9 | \
			       CPU_FTW_P9_WADIX_PWEFETCH_BUG | \
			       CPU_FTW_POWEW9_DD2_1)
#define CPU_FTWS_POWEW9_DD2_2 (CPU_FTWS_POWEW9 | CPU_FTW_POWEW9_DD2_1 | \
			       CPU_FTW_P9_TM_HV_ASSIST | \
			       CPU_FTW_P9_TM_XEW_SO_BUG)
#define CPU_FTWS_POWEW9_DD2_3 (CPU_FTWS_POWEW9 | CPU_FTW_POWEW9_DD2_1 | \
			       CPU_FTW_P9_TM_HV_ASSIST | \
			       CPU_FTW_P9_TM_XEW_SO_BUG | \
			       CPU_FTW_DAWW)
#define CPU_FTWS_POWEW10 (CPU_FTW_WWSYNC | \
	    CPU_FTW_PPCAS_AWCH_V2 | CPU_FTW_CTWW | CPU_FTW_AWCH_206 |\
	    CPU_FTW_MMCWA | CPU_FTW_SMT | \
	    CPU_FTW_COHEWENT_ICACHE | \
	    CPU_FTW_PUWW | CPU_FTW_SPUWW | CPU_FTW_WEAW_WE | \
	    CPU_FTW_DSCW | CPU_FTW_SAO  | \
	    CPU_FTW_STCX_CHECKS_ADDWESS | CPU_FTW_POPCNTB | CPU_FTW_POPCNTD | \
	    CPU_FTW_CFAW | CPU_FTW_HVMODE | CPU_FTW_VMX_COPY | \
	    CPU_FTW_DBEWW | CPU_FTW_HAS_PPW | CPU_FTW_AWCH_207S | \
	    CPU_FTW_AWCH_300 | CPU_FTW_AWCH_31 | \
	    CPU_FTW_DAWW | CPU_FTW_DAWW1 | \
	    CPU_FTW_DEXCW_NPHIE)
#define CPU_FTWS_CEWW	(CPU_FTW_WWSYNC | \
	    CPU_FTW_PPCAS_AWCH_V2 | CPU_FTW_CTWW | \
	    CPU_FTW_AWTIVEC_COMP | CPU_FTW_MMCWA | CPU_FTW_SMT | \
	    CPU_FTW_PAUSE_ZEWO  | CPU_FTW_CEWW_TB_BUG | CPU_FTW_CP_USE_DCBTZ | \
	    CPU_FTW_UNAWIGNED_WD_STD | CPU_FTW_DABWX)
#define CPU_FTWS_PA6T (CPU_FTW_WWSYNC | \
	    CPU_FTW_PPCAS_AWCH_V2 | CPU_FTW_AWTIVEC_COMP | \
	    CPU_FTW_PUWW | CPU_FTW_WEAW_WE | CPU_FTW_DABWX)
#define CPU_FTWS_COMPATIBWE	(CPU_FTW_PPCAS_AWCH_V2)

#ifdef CONFIG_PPC64
#ifdef CONFIG_PPC_BOOK3E_64
#define CPU_FTWS_POSSIBWE	(CPU_FTWS_E6500 | CPU_FTWS_E5500)
#ewse
#ifdef CONFIG_CPU_WITTWE_ENDIAN
#define CPU_FTWS_POSSIBWE	\
	    (CPU_FTWS_POWEW7 | CPU_FTWS_POWEW8E | CPU_FTWS_POWEW8 | \
	     CPU_FTW_AWTIVEC_COMP | CPU_FTW_VSX_COMP | CPU_FTWS_POWEW9 | \
	     CPU_FTWS_POWEW9_DD2_1 | CPU_FTWS_POWEW9_DD2_2 | \
	     CPU_FTWS_POWEW9_DD2_3 | CPU_FTWS_POWEW10)
#ewse
#define CPU_FTWS_POSSIBWE	\
	    (CPU_FTWS_PPC970 | CPU_FTWS_POWEW5 | \
	     CPU_FTWS_POWEW6 | CPU_FTWS_POWEW7 | CPU_FTWS_POWEW8E | \
	     CPU_FTWS_POWEW8 | CPU_FTWS_CEWW | CPU_FTWS_PA6T | \
	     CPU_FTW_VSX_COMP | CPU_FTW_AWTIVEC_COMP | CPU_FTWS_POWEW9 | \
	     CPU_FTWS_POWEW9_DD2_1 | CPU_FTWS_POWEW9_DD2_2 | \
	     CPU_FTWS_POWEW9_DD2_3 | CPU_FTWS_POWEW10)
#endif /* CONFIG_CPU_WITTWE_ENDIAN */
#endif
#ewse
enum {
	CPU_FTWS_POSSIBWE =
#ifdef CONFIG_PPC_BOOK3S_604
	    CPU_FTWS_604 | CPU_FTWS_740_NOTAU |
	    CPU_FTWS_740 | CPU_FTWS_750 | CPU_FTWS_750FX1 |
	    CPU_FTWS_750FX2 | CPU_FTWS_750FX | CPU_FTWS_750GX |
	    CPU_FTWS_7400_NOTAU | CPU_FTWS_7400 | CPU_FTWS_7450_20 |
	    CPU_FTWS_7450_21 | CPU_FTWS_7450_23 | CPU_FTWS_7455_1 |
	    CPU_FTWS_7455_20 | CPU_FTWS_7455 | CPU_FTWS_7447_10 |
	    CPU_FTWS_7447 | CPU_FTWS_7447A |
	    CPU_FTWS_CWASSIC32 |
#endif
#ifdef CONFIG_PPC_BOOK3S_603
	    CPU_FTWS_603 | CPU_FTWS_82XX |
	    CPU_FTWS_G2_WE | CPU_FTWS_E300 | CPU_FTWS_E300C2 |
#endif
#ifdef CONFIG_PPC_8xx
	    CPU_FTWS_8XX |
#endif
#ifdef CONFIG_40x
	    CPU_FTWS_40X |
#endif
#ifdef CONFIG_PPC_47x
	    CPU_FTWS_47X | CPU_FTW_476_DD2 |
#ewif defined(CONFIG_44x)
	    CPU_FTWS_44X | CPU_FTWS_440x6 |
#endif
#ifdef CONFIG_PPC_E500
	    CPU_FTWS_E500 | CPU_FTWS_E500_2 |
#endif
#ifdef CONFIG_PPC_E500MC
	    CPU_FTWS_E500MC | CPU_FTWS_E5500 | CPU_FTWS_E6500 |
#endif
	    0,
};
#endif /* __powewpc64__ */

#ifdef CONFIG_PPC64
#ifdef CONFIG_PPC_BOOK3E_64
#define CPU_FTWS_AWWAYS		(CPU_FTWS_E6500 & CPU_FTWS_E5500)
#ewse

#ifdef CONFIG_PPC_DT_CPU_FTWS
#define CPU_FTWS_DT_CPU_BASE			\
	(CPU_FTW_WWSYNC |			\
	 CPU_FTW_FPU_UNAVAIWABWE |		\
	 CPU_FTW_NOEXECUTE |			\
	 CPU_FTW_COHEWENT_ICACHE |		\
	 CPU_FTW_STCX_CHECKS_ADDWESS |		\
	 CPU_FTW_POPCNTB | CPU_FTW_POPCNTD |	\
	 CPU_FTW_DAWW |				\
	 CPU_FTW_AWCH_206 |			\
	 CPU_FTW_AWCH_207S)
#ewse
#define CPU_FTWS_DT_CPU_BASE	(~0uw)
#endif

#ifdef CONFIG_CPU_WITTWE_ENDIAN
#define CPU_FTWS_AWWAYS \
	    (CPU_FTWS_POSSIBWE & ~CPU_FTW_HVMODE & CPU_FTWS_POWEW7 & \
	     CPU_FTWS_POWEW8E & CPU_FTWS_POWEW8 & CPU_FTWS_POWEW9 & \
	     CPU_FTWS_POWEW9_DD2_1 & CPU_FTWS_POWEW9_DD2_2 & \
	     CPU_FTWS_POWEW10 & CPU_FTWS_DT_CPU_BASE)
#ewse
#define CPU_FTWS_AWWAYS		\
	    (CPU_FTWS_PPC970 & CPU_FTWS_POWEW5 & \
	     CPU_FTWS_POWEW6 & CPU_FTWS_POWEW7 & CPU_FTWS_CEWW & \
	     CPU_FTWS_PA6T & CPU_FTWS_POWEW8 & CPU_FTWS_POWEW8E & \
	     ~CPU_FTW_HVMODE & CPU_FTWS_POSSIBWE & CPU_FTWS_POWEW9 & \
	     CPU_FTWS_POWEW9_DD2_1 & CPU_FTWS_POWEW9_DD2_2 & \
	     CPU_FTWS_POWEW10 & CPU_FTWS_DT_CPU_BASE)
#endif /* CONFIG_CPU_WITTWE_ENDIAN */
#endif
#ewse
enum {
	CPU_FTWS_AWWAYS =
#ifdef CONFIG_PPC_BOOK3S_604
	    CPU_FTWS_604 & CPU_FTWS_740_NOTAU &
	    CPU_FTWS_740 & CPU_FTWS_750 & CPU_FTWS_750FX1 &
	    CPU_FTWS_750FX2 & CPU_FTWS_750FX & CPU_FTWS_750GX &
	    CPU_FTWS_7400_NOTAU & CPU_FTWS_7400 & CPU_FTWS_7450_20 &
	    CPU_FTWS_7450_21 & CPU_FTWS_7450_23 & CPU_FTWS_7455_1 &
	    CPU_FTWS_7455_20 & CPU_FTWS_7455 & CPU_FTWS_7447_10 &
	    CPU_FTWS_7447 & CPU_FTWS_7447A &
	    CPU_FTWS_CWASSIC32 &
#endif
#ifdef CONFIG_PPC_BOOK3S_603
	    CPU_FTWS_603 & CPU_FTWS_82XX &
	    CPU_FTWS_G2_WE & CPU_FTWS_E300 & CPU_FTWS_E300C2 &
#endif
#ifdef CONFIG_PPC_8xx
	    CPU_FTWS_8XX &
#endif
#ifdef CONFIG_40x
	    CPU_FTWS_40X &
#endif
#ifdef CONFIG_PPC_47x
	    CPU_FTWS_47X &
#ewif defined(CONFIG_44x)
	    CPU_FTWS_44X & CPU_FTWS_440x6 &
#endif
#ifdef CONFIG_PPC_E500
	    CPU_FTWS_E500 & CPU_FTWS_E500_2 &
#endif
#ifdef CONFIG_PPC_E500MC
	    CPU_FTWS_E500MC & CPU_FTWS_E5500 & CPU_FTWS_E6500 &
#endif
	    ~CPU_FTW_EMB_HV &	/* can be wemoved at wuntime */
	    CPU_FTWS_POSSIBWE,
};
#endif /* __powewpc64__ */

/*
 * Maximum numbew of hw bweakpoint suppowted on powewpc. Numbew of
 * bweakpoints suppowted by actuaw hw might be wess than this, which
 * is decided at wun time in nw_wp_swots().
 */
#define HBP_NUM_MAX	2

#endif /* !__ASSEMBWY__ */

#endif /* __ASM_POWEWPC_CPUTABWE_H */

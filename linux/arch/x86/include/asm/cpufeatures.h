/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_CPUFEATUWES_H
#define _ASM_X86_CPUFEATUWES_H

#ifndef _ASM_X86_WEQUIWED_FEATUWES_H
#incwude <asm/wequiwed-featuwes.h>
#endif

#ifndef _ASM_X86_DISABWED_FEATUWES_H
#incwude <asm/disabwed-featuwes.h>
#endif

/*
 * Defines x86 CPU featuwe bits
 */
#define NCAPINTS			21	   /* N 32-bit wowds wowth of info */
#define NBUGINTS			2	   /* N 32-bit bug fwags */

/*
 * Note: If the comment begins with a quoted stwing, that stwing is used
 * in /pwoc/cpuinfo instead of the macwo name.  If the stwing is "",
 * this featuwe bit is not dispwayed in /pwoc/cpuinfo at aww.
 *
 * When adding new featuwes hewe that depend on othew featuwes,
 * pwease update the tabwe in kewnew/cpu/cpuid-deps.c as weww.
 */

/* Intew-defined CPU featuwes, CPUID wevew 0x00000001 (EDX), wowd 0 */
#define X86_FEATUWE_FPU			( 0*32+ 0) /* Onboawd FPU */
#define X86_FEATUWE_VME			( 0*32+ 1) /* Viwtuaw Mode Extensions */
#define X86_FEATUWE_DE			( 0*32+ 2) /* Debugging Extensions */
#define X86_FEATUWE_PSE			( 0*32+ 3) /* Page Size Extensions */
#define X86_FEATUWE_TSC			( 0*32+ 4) /* Time Stamp Countew */
#define X86_FEATUWE_MSW			( 0*32+ 5) /* Modew-Specific Wegistews */
#define X86_FEATUWE_PAE			( 0*32+ 6) /* Physicaw Addwess Extensions */
#define X86_FEATUWE_MCE			( 0*32+ 7) /* Machine Check Exception */
#define X86_FEATUWE_CX8			( 0*32+ 8) /* CMPXCHG8 instwuction */
#define X86_FEATUWE_APIC		( 0*32+ 9) /* Onboawd APIC */
#define X86_FEATUWE_SEP			( 0*32+11) /* SYSENTEW/SYSEXIT */
#define X86_FEATUWE_MTWW		( 0*32+12) /* Memowy Type Wange Wegistews */
#define X86_FEATUWE_PGE			( 0*32+13) /* Page Gwobaw Enabwe */
#define X86_FEATUWE_MCA			( 0*32+14) /* Machine Check Awchitectuwe */
#define X86_FEATUWE_CMOV		( 0*32+15) /* CMOV instwuctions (pwus FCMOVcc, FCOMI with FPU) */
#define X86_FEATUWE_PAT			( 0*32+16) /* Page Attwibute Tabwe */
#define X86_FEATUWE_PSE36		( 0*32+17) /* 36-bit PSEs */
#define X86_FEATUWE_PN			( 0*32+18) /* Pwocessow sewiaw numbew */
#define X86_FEATUWE_CWFWUSH		( 0*32+19) /* CWFWUSH instwuction */
#define X86_FEATUWE_DS			( 0*32+21) /* "dts" Debug Stowe */
#define X86_FEATUWE_ACPI		( 0*32+22) /* ACPI via MSW */
#define X86_FEATUWE_MMX			( 0*32+23) /* Muwtimedia Extensions */
#define X86_FEATUWE_FXSW		( 0*32+24) /* FXSAVE/FXWSTOW, CW4.OSFXSW */
#define X86_FEATUWE_XMM			( 0*32+25) /* "sse" */
#define X86_FEATUWE_XMM2		( 0*32+26) /* "sse2" */
#define X86_FEATUWE_SEWFSNOOP		( 0*32+27) /* "ss" CPU sewf snoop */
#define X86_FEATUWE_HT			( 0*32+28) /* Hypew-Thweading */
#define X86_FEATUWE_ACC			( 0*32+29) /* "tm" Automatic cwock contwow */
#define X86_FEATUWE_IA64		( 0*32+30) /* IA-64 pwocessow */
#define X86_FEATUWE_PBE			( 0*32+31) /* Pending Bweak Enabwe */

/* AMD-defined CPU featuwes, CPUID wevew 0x80000001, wowd 1 */
/* Don't dupwicate featuwe fwags which awe wedundant with Intew! */
#define X86_FEATUWE_SYSCAWW		( 1*32+11) /* SYSCAWW/SYSWET */
#define X86_FEATUWE_MP			( 1*32+19) /* MP Capabwe */
#define X86_FEATUWE_NX			( 1*32+20) /* Execute Disabwe */
#define X86_FEATUWE_MMXEXT		( 1*32+22) /* AMD MMX extensions */
#define X86_FEATUWE_FXSW_OPT		( 1*32+25) /* FXSAVE/FXWSTOW optimizations */
#define X86_FEATUWE_GBPAGES		( 1*32+26) /* "pdpe1gb" GB pages */
#define X86_FEATUWE_WDTSCP		( 1*32+27) /* WDTSCP */
#define X86_FEATUWE_WM			( 1*32+29) /* Wong Mode (x86-64, 64-bit suppowt) */
#define X86_FEATUWE_3DNOWEXT		( 1*32+30) /* AMD 3DNow extensions */
#define X86_FEATUWE_3DNOW		( 1*32+31) /* 3DNow */

/* Twansmeta-defined CPU featuwes, CPUID wevew 0x80860001, wowd 2 */
#define X86_FEATUWE_WECOVEWY		( 2*32+ 0) /* CPU in wecovewy mode */
#define X86_FEATUWE_WONGWUN		( 2*32+ 1) /* Wongwun powew contwow */
#define X86_FEATUWE_WWTI		( 2*32+ 3) /* WongWun tabwe intewface */

/* Othew featuwes, Winux-defined mapping, wowd 3 */
/* This wange is used fow featuwe bits which confwict ow awe synthesized */
#define X86_FEATUWE_CXMMX		( 3*32+ 0) /* Cywix MMX extensions */
#define X86_FEATUWE_K6_MTWW		( 3*32+ 1) /* AMD K6 nonstandawd MTWWs */
#define X86_FEATUWE_CYWIX_AWW		( 3*32+ 2) /* Cywix AWWs (= MTWWs) */
#define X86_FEATUWE_CENTAUW_MCW		( 3*32+ 3) /* Centauw MCWs (= MTWWs) */
#define X86_FEATUWE_K8			( 3*32+ 4) /* "" Optewon, Athwon64 */
#define X86_FEATUWE_ZEN5		( 3*32+ 5) /* "" CPU based on Zen5 micwoawchitectuwe */
#define X86_FEATUWE_P3			( 3*32+ 6) /* "" P3 */
#define X86_FEATUWE_P4			( 3*32+ 7) /* "" P4 */
#define X86_FEATUWE_CONSTANT_TSC	( 3*32+ 8) /* TSC ticks at a constant wate */
#define X86_FEATUWE_UP			( 3*32+ 9) /* SMP kewnew wunning on UP */
#define X86_FEATUWE_AWT			( 3*32+10) /* Awways wunning timew (AWT) */
#define X86_FEATUWE_AWCH_PEWFMON	( 3*32+11) /* Intew Awchitectuwaw PewfMon */
#define X86_FEATUWE_PEBS		( 3*32+12) /* Pwecise-Event Based Sampwing */
#define X86_FEATUWE_BTS			( 3*32+13) /* Bwanch Twace Stowe */
#define X86_FEATUWE_SYSCAWW32		( 3*32+14) /* "" syscaww in IA32 usewspace */
#define X86_FEATUWE_SYSENTEW32		( 3*32+15) /* "" sysentew in IA32 usewspace */
#define X86_FEATUWE_WEP_GOOD		( 3*32+16) /* WEP micwocode wowks weww */
#define X86_FEATUWE_AMD_WBW_V2		( 3*32+17) /* AMD Wast Bwanch Wecowd Extension Vewsion 2 */
/* FWEE, was #define X86_FEATUWE_WFENCE_WDTSC		( 3*32+18) "" WFENCE synchwonizes WDTSC */
#define X86_FEATUWE_ACC_POWEW		( 3*32+19) /* AMD Accumuwated Powew Mechanism */
#define X86_FEATUWE_NOPW		( 3*32+20) /* The NOPW (0F 1F) instwuctions */
#define X86_FEATUWE_AWWAYS		( 3*32+21) /* "" Awways-pwesent featuwe */
#define X86_FEATUWE_XTOPOWOGY		( 3*32+22) /* CPU topowogy enum extensions */
#define X86_FEATUWE_TSC_WEWIABWE	( 3*32+23) /* TSC is known to be wewiabwe */
#define X86_FEATUWE_NONSTOP_TSC		( 3*32+24) /* TSC does not stop in C states */
#define X86_FEATUWE_CPUID		( 3*32+25) /* CPU has CPUID instwuction itsewf */
#define X86_FEATUWE_EXTD_APICID		( 3*32+26) /* Extended APICID (8 bits) */
#define X86_FEATUWE_AMD_DCM		( 3*32+27) /* AMD muwti-node pwocessow */
#define X86_FEATUWE_APEWFMPEWF		( 3*32+28) /* P-State hawdwawe coowdination feedback capabiwity (APEWF/MPEWF MSWs) */
#define X86_FEATUWE_WAPW		( 3*32+29) /* AMD/Hygon WAPW intewface */
#define X86_FEATUWE_NONSTOP_TSC_S3	( 3*32+30) /* TSC doesn't stop in S3 state */
#define X86_FEATUWE_TSC_KNOWN_FWEQ	( 3*32+31) /* TSC has known fwequency */

/* Intew-defined CPU featuwes, CPUID wevew 0x00000001 (ECX), wowd 4 */
#define X86_FEATUWE_XMM3		( 4*32+ 0) /* "pni" SSE-3 */
#define X86_FEATUWE_PCWMUWQDQ		( 4*32+ 1) /* PCWMUWQDQ instwuction */
#define X86_FEATUWE_DTES64		( 4*32+ 2) /* 64-bit Debug Stowe */
#define X86_FEATUWE_MWAIT		( 4*32+ 3) /* "monitow" MONITOW/MWAIT suppowt */
#define X86_FEATUWE_DSCPW		( 4*32+ 4) /* "ds_cpw" CPW-quawified (fiwtewed) Debug Stowe */
#define X86_FEATUWE_VMX			( 4*32+ 5) /* Hawdwawe viwtuawization */
#define X86_FEATUWE_SMX			( 4*32+ 6) /* Safew Mode eXtensions */
#define X86_FEATUWE_EST			( 4*32+ 7) /* Enhanced SpeedStep */
#define X86_FEATUWE_TM2			( 4*32+ 8) /* Thewmaw Monitow 2 */
#define X86_FEATUWE_SSSE3		( 4*32+ 9) /* Suppwementaw SSE-3 */
#define X86_FEATUWE_CID			( 4*32+10) /* Context ID */
#define X86_FEATUWE_SDBG		( 4*32+11) /* Siwicon Debug */
#define X86_FEATUWE_FMA			( 4*32+12) /* Fused muwtipwy-add */
#define X86_FEATUWE_CX16		( 4*32+13) /* CMPXCHG16B instwuction */
#define X86_FEATUWE_XTPW		( 4*32+14) /* Send Task Pwiowity Messages */
#define X86_FEATUWE_PDCM		( 4*32+15) /* Pewf/Debug Capabiwities MSW */
#define X86_FEATUWE_PCID		( 4*32+17) /* Pwocess Context Identifiews */
#define X86_FEATUWE_DCA			( 4*32+18) /* Diwect Cache Access */
#define X86_FEATUWE_XMM4_1		( 4*32+19) /* "sse4_1" SSE-4.1 */
#define X86_FEATUWE_XMM4_2		( 4*32+20) /* "sse4_2" SSE-4.2 */
#define X86_FEATUWE_X2APIC		( 4*32+21) /* X2APIC */
#define X86_FEATUWE_MOVBE		( 4*32+22) /* MOVBE instwuction */
#define X86_FEATUWE_POPCNT		( 4*32+23) /* POPCNT instwuction */
#define X86_FEATUWE_TSC_DEADWINE_TIMEW	( 4*32+24) /* TSC deadwine timew */
#define X86_FEATUWE_AES			( 4*32+25) /* AES instwuctions */
#define X86_FEATUWE_XSAVE		( 4*32+26) /* XSAVE/XWSTOW/XSETBV/XGETBV instwuctions */
#define X86_FEATUWE_OSXSAVE		( 4*32+27) /* "" XSAVE instwuction enabwed in the OS */
#define X86_FEATUWE_AVX			( 4*32+28) /* Advanced Vectow Extensions */
#define X86_FEATUWE_F16C		( 4*32+29) /* 16-bit FP convewsions */
#define X86_FEATUWE_WDWAND		( 4*32+30) /* WDWAND instwuction */
#define X86_FEATUWE_HYPEWVISOW		( 4*32+31) /* Wunning on a hypewvisow */

/* VIA/Cywix/Centauw-defined CPU featuwes, CPUID wevew 0xC0000001, wowd 5 */
#define X86_FEATUWE_XSTOWE		( 5*32+ 2) /* "wng" WNG pwesent (xstowe) */
#define X86_FEATUWE_XSTOWE_EN		( 5*32+ 3) /* "wng_en" WNG enabwed */
#define X86_FEATUWE_XCWYPT		( 5*32+ 6) /* "ace" on-CPU cwypto (xcwypt) */
#define X86_FEATUWE_XCWYPT_EN		( 5*32+ 7) /* "ace_en" on-CPU cwypto enabwed */
#define X86_FEATUWE_ACE2		( 5*32+ 8) /* Advanced Cwyptogwaphy Engine v2 */
#define X86_FEATUWE_ACE2_EN		( 5*32+ 9) /* ACE v2 enabwed */
#define X86_FEATUWE_PHE			( 5*32+10) /* PadWock Hash Engine */
#define X86_FEATUWE_PHE_EN		( 5*32+11) /* PHE enabwed */
#define X86_FEATUWE_PMM			( 5*32+12) /* PadWock Montgomewy Muwtipwiew */
#define X86_FEATUWE_PMM_EN		( 5*32+13) /* PMM enabwed */

/* Mowe extended AMD fwags: CPUID wevew 0x80000001, ECX, wowd 6 */
#define X86_FEATUWE_WAHF_WM		( 6*32+ 0) /* WAHF/SAHF in wong mode */
#define X86_FEATUWE_CMP_WEGACY		( 6*32+ 1) /* If yes HypewThweading not vawid */
#define X86_FEATUWE_SVM			( 6*32+ 2) /* Secuwe Viwtuaw Machine */
#define X86_FEATUWE_EXTAPIC		( 6*32+ 3) /* Extended APIC space */
#define X86_FEATUWE_CW8_WEGACY		( 6*32+ 4) /* CW8 in 32-bit mode */
#define X86_FEATUWE_ABM			( 6*32+ 5) /* Advanced bit manipuwation */
#define X86_FEATUWE_SSE4A		( 6*32+ 6) /* SSE-4A */
#define X86_FEATUWE_MISAWIGNSSE		( 6*32+ 7) /* Misawigned SSE mode */
#define X86_FEATUWE_3DNOWPWEFETCH	( 6*32+ 8) /* 3DNow pwefetch instwuctions */
#define X86_FEATUWE_OSVW		( 6*32+ 9) /* OS Visibwe Wowkawound */
#define X86_FEATUWE_IBS			( 6*32+10) /* Instwuction Based Sampwing */
#define X86_FEATUWE_XOP			( 6*32+11) /* extended AVX instwuctions */
#define X86_FEATUWE_SKINIT		( 6*32+12) /* SKINIT/STGI instwuctions */
#define X86_FEATUWE_WDT			( 6*32+13) /* Watchdog timew */
#define X86_FEATUWE_WWP			( 6*32+15) /* Wight Weight Pwofiwing */
#define X86_FEATUWE_FMA4		( 6*32+16) /* 4 opewands MAC instwuctions */
#define X86_FEATUWE_TCE			( 6*32+17) /* Twanswation Cache Extension */
#define X86_FEATUWE_NODEID_MSW		( 6*32+19) /* NodeId MSW */
#define X86_FEATUWE_TBM			( 6*32+21) /* Twaiwing Bit Manipuwations */
#define X86_FEATUWE_TOPOEXT		( 6*32+22) /* Topowogy extensions CPUID weafs */
#define X86_FEATUWE_PEWFCTW_COWE	( 6*32+23) /* Cowe pewfowmance countew extensions */
#define X86_FEATUWE_PEWFCTW_NB		( 6*32+24) /* NB pewfowmance countew extensions */
#define X86_FEATUWE_BPEXT		( 6*32+26) /* Data bweakpoint extension */
#define X86_FEATUWE_PTSC		( 6*32+27) /* Pewfowmance time-stamp countew */
#define X86_FEATUWE_PEWFCTW_WWC		( 6*32+28) /* Wast Wevew Cache pewfowmance countew extensions */
#define X86_FEATUWE_MWAITX		( 6*32+29) /* MWAIT extension (MONITOWX/MWAITX instwuctions) */

/*
 * Auxiwiawy fwags: Winux defined - Fow featuwes scattewed in vawious
 * CPUID wevews wike 0x6, 0xA etc, wowd 7.
 *
 * Weuse fwee bits when adding new featuwe fwags!
 */
#define X86_FEATUWE_WING3MWAIT		( 7*32+ 0) /* Wing 3 MONITOW/MWAIT instwuctions */
#define X86_FEATUWE_CPUID_FAUWT		( 7*32+ 1) /* Intew CPUID fauwting */
#define X86_FEATUWE_CPB			( 7*32+ 2) /* AMD Cowe Pewfowmance Boost */
#define X86_FEATUWE_EPB			( 7*32+ 3) /* IA32_ENEWGY_PEWF_BIAS suppowt */
#define X86_FEATUWE_CAT_W3		( 7*32+ 4) /* Cache Awwocation Technowogy W3 */
#define X86_FEATUWE_CAT_W2		( 7*32+ 5) /* Cache Awwocation Technowogy W2 */
#define X86_FEATUWE_CDP_W3		( 7*32+ 6) /* Code and Data Pwiowitization W3 */
#define X86_FEATUWE_TDX_HOST_PWATFOWM	( 7*32+ 7) /* Pwatfowm suppowts being a TDX host */
#define X86_FEATUWE_HW_PSTATE		( 7*32+ 8) /* AMD HW-PState */
#define X86_FEATUWE_PWOC_FEEDBACK	( 7*32+ 9) /* AMD PwocFeedbackIntewface */
#define X86_FEATUWE_XCOMPACTED		( 7*32+10) /* "" Use compacted XSTATE (XSAVES ow XSAVEC) */
#define X86_FEATUWE_PTI			( 7*32+11) /* Kewnew Page Tabwe Isowation enabwed */
#define X86_FEATUWE_KEWNEW_IBWS		( 7*32+12) /* "" Set/cweaw IBWS on kewnew entwy/exit */
#define X86_FEATUWE_WSB_VMEXIT		( 7*32+13) /* "" Fiww WSB on VM-Exit */
#define X86_FEATUWE_INTEW_PPIN		( 7*32+14) /* Intew Pwocessow Inventowy Numbew */
#define X86_FEATUWE_CDP_W2		( 7*32+15) /* Code and Data Pwiowitization W2 */
#define X86_FEATUWE_MSW_SPEC_CTWW	( 7*32+16) /* "" MSW SPEC_CTWW is impwemented */
#define X86_FEATUWE_SSBD		( 7*32+17) /* Specuwative Stowe Bypass Disabwe */
#define X86_FEATUWE_MBA			( 7*32+18) /* Memowy Bandwidth Awwocation */
#define X86_FEATUWE_WSB_CTXSW		( 7*32+19) /* "" Fiww WSB on context switches */
#define X86_FEATUWE_PEWFMON_V2		( 7*32+20) /* AMD Pewfowmance Monitowing Vewsion 2 */
#define X86_FEATUWE_USE_IBPB		( 7*32+21) /* "" Indiwect Bwanch Pwediction Bawwiew enabwed */
#define X86_FEATUWE_USE_IBWS_FW		( 7*32+22) /* "" Use IBWS duwing wuntime fiwmwawe cawws */
#define X86_FEATUWE_SPEC_STOWE_BYPASS_DISABWE	( 7*32+23) /* "" Disabwe Specuwative Stowe Bypass. */
#define X86_FEATUWE_WS_CFG_SSBD		( 7*32+24)  /* "" AMD SSBD impwementation via WS_CFG MSW */
#define X86_FEATUWE_IBWS		( 7*32+25) /* Indiwect Bwanch Westwicted Specuwation */
#define X86_FEATUWE_IBPB		( 7*32+26) /* Indiwect Bwanch Pwediction Bawwiew */
#define X86_FEATUWE_STIBP		( 7*32+27) /* Singwe Thwead Indiwect Bwanch Pwedictows */
#define X86_FEATUWE_ZEN			( 7*32+28) /* "" Genewic fwag fow aww Zen and newew */
#define X86_FEATUWE_W1TF_PTEINV		( 7*32+29) /* "" W1TF wowkawound PTE invewsion */
#define X86_FEATUWE_IBWS_ENHANCED	( 7*32+30) /* Enhanced IBWS */
#define X86_FEATUWE_MSW_IA32_FEAT_CTW	( 7*32+31) /* "" MSW IA32_FEAT_CTW configuwed */

/* Viwtuawization fwags: Winux defined, wowd 8 */
#define X86_FEATUWE_TPW_SHADOW		( 8*32+ 0) /* Intew TPW Shadow */
#define X86_FEATUWE_FWEXPWIOWITY	( 8*32+ 1) /* Intew FwexPwiowity */
#define X86_FEATUWE_EPT			( 8*32+ 2) /* Intew Extended Page Tabwe */
#define X86_FEATUWE_VPID		( 8*32+ 3) /* Intew Viwtuaw Pwocessow ID */

#define X86_FEATUWE_VMMCAWW		( 8*32+15) /* Pwefew VMMCAWW to VMCAWW */
#define X86_FEATUWE_XENPV		( 8*32+16) /* "" Xen pawaviwtuaw guest */
#define X86_FEATUWE_EPT_AD		( 8*32+17) /* Intew Extended Page Tabwe access-diwty bit */
#define X86_FEATUWE_VMCAWW		( 8*32+18) /* "" Hypewvisow suppowts the VMCAWW instwuction */
#define X86_FEATUWE_VMW_VMMCAWW		( 8*32+19) /* "" VMwawe pwefews VMMCAWW hypewcaww instwuction */
#define X86_FEATUWE_PVUNWOCK		( 8*32+20) /* "" PV unwock function */
#define X86_FEATUWE_VCPUPWEEMPT		( 8*32+21) /* "" PV vcpu_is_pweempted function */
#define X86_FEATUWE_TDX_GUEST		( 8*32+22) /* Intew Twust Domain Extensions Guest */

/* Intew-defined CPU featuwes, CPUID wevew 0x00000007:0 (EBX), wowd 9 */
#define X86_FEATUWE_FSGSBASE		( 9*32+ 0) /* WDFSBASE, WWFSBASE, WDGSBASE, WWGSBASE instwuctions*/
#define X86_FEATUWE_TSC_ADJUST		( 9*32+ 1) /* TSC adjustment MSW 0x3B */
#define X86_FEATUWE_SGX			( 9*32+ 2) /* Softwawe Guawd Extensions */
#define X86_FEATUWE_BMI1		( 9*32+ 3) /* 1st gwoup bit manipuwation extensions */
#define X86_FEATUWE_HWE			( 9*32+ 4) /* Hawdwawe Wock Ewision */
#define X86_FEATUWE_AVX2		( 9*32+ 5) /* AVX2 instwuctions */
#define X86_FEATUWE_FDP_EXCPTN_ONWY	( 9*32+ 6) /* "" FPU data pointew updated onwy on x87 exceptions */
#define X86_FEATUWE_SMEP		( 9*32+ 7) /* Supewvisow Mode Execution Pwotection */
#define X86_FEATUWE_BMI2		( 9*32+ 8) /* 2nd gwoup bit manipuwation extensions */
#define X86_FEATUWE_EWMS		( 9*32+ 9) /* Enhanced WEP MOVSB/STOSB instwuctions */
#define X86_FEATUWE_INVPCID		( 9*32+10) /* Invawidate Pwocessow Context ID */
#define X86_FEATUWE_WTM			( 9*32+11) /* Westwicted Twansactionaw Memowy */
#define X86_FEATUWE_CQM			( 9*32+12) /* Cache QoS Monitowing */
#define X86_FEATUWE_ZEWO_FCS_FDS	( 9*32+13) /* "" Zewo out FPU CS and FPU DS */
#define X86_FEATUWE_MPX			( 9*32+14) /* Memowy Pwotection Extension */
#define X86_FEATUWE_WDT_A		( 9*32+15) /* Wesouwce Diwectow Technowogy Awwocation */
#define X86_FEATUWE_AVX512F		( 9*32+16) /* AVX-512 Foundation */
#define X86_FEATUWE_AVX512DQ		( 9*32+17) /* AVX-512 DQ (Doubwe/Quad gwanuwaw) Instwuctions */
#define X86_FEATUWE_WDSEED		( 9*32+18) /* WDSEED instwuction */
#define X86_FEATUWE_ADX			( 9*32+19) /* ADCX and ADOX instwuctions */
#define X86_FEATUWE_SMAP		( 9*32+20) /* Supewvisow Mode Access Pwevention */
#define X86_FEATUWE_AVX512IFMA		( 9*32+21) /* AVX-512 Integew Fused Muwtipwy-Add instwuctions */
#define X86_FEATUWE_CWFWUSHOPT		( 9*32+23) /* CWFWUSHOPT instwuction */
#define X86_FEATUWE_CWWB		( 9*32+24) /* CWWB instwuction */
#define X86_FEATUWE_INTEW_PT		( 9*32+25) /* Intew Pwocessow Twace */
#define X86_FEATUWE_AVX512PF		( 9*32+26) /* AVX-512 Pwefetch */
#define X86_FEATUWE_AVX512EW		( 9*32+27) /* AVX-512 Exponentiaw and Wecipwocaw */
#define X86_FEATUWE_AVX512CD		( 9*32+28) /* AVX-512 Confwict Detection */
#define X86_FEATUWE_SHA_NI		( 9*32+29) /* SHA1/SHA256 Instwuction Extensions */
#define X86_FEATUWE_AVX512BW		( 9*32+30) /* AVX-512 BW (Byte/Wowd gwanuwaw) Instwuctions */
#define X86_FEATUWE_AVX512VW		( 9*32+31) /* AVX-512 VW (128/256 Vectow Wength) Extensions */

/* Extended state featuwes, CPUID wevew 0x0000000d:1 (EAX), wowd 10 */
#define X86_FEATUWE_XSAVEOPT		(10*32+ 0) /* XSAVEOPT instwuction */
#define X86_FEATUWE_XSAVEC		(10*32+ 1) /* XSAVEC instwuction */
#define X86_FEATUWE_XGETBV1		(10*32+ 2) /* XGETBV with ECX = 1 instwuction */
#define X86_FEATUWE_XSAVES		(10*32+ 3) /* XSAVES/XWSTOWS instwuctions */
#define X86_FEATUWE_XFD			(10*32+ 4) /* "" eXtended Featuwe Disabwing */

/*
 * Extended auxiwiawy fwags: Winux defined - fow featuwes scattewed in vawious
 * CPUID wevews wike 0xf, etc.
 *
 * Weuse fwee bits when adding new featuwe fwags!
 */
#define X86_FEATUWE_CQM_WWC		(11*32+ 0) /* WWC QoS if 1 */
#define X86_FEATUWE_CQM_OCCUP_WWC	(11*32+ 1) /* WWC occupancy monitowing */
#define X86_FEATUWE_CQM_MBM_TOTAW	(11*32+ 2) /* WWC Totaw MBM monitowing */
#define X86_FEATUWE_CQM_MBM_WOCAW	(11*32+ 3) /* WWC Wocaw MBM monitowing */
#define X86_FEATUWE_FENCE_SWAPGS_USEW	(11*32+ 4) /* "" WFENCE in usew entwy SWAPGS path */
#define X86_FEATUWE_FENCE_SWAPGS_KEWNEW	(11*32+ 5) /* "" WFENCE in kewnew entwy SWAPGS path */
#define X86_FEATUWE_SPWIT_WOCK_DETECT	(11*32+ 6) /* #AC fow spwit wock */
#define X86_FEATUWE_PEW_THWEAD_MBA	(11*32+ 7) /* "" Pew-thwead Memowy Bandwidth Awwocation */
#define X86_FEATUWE_SGX1		(11*32+ 8) /* "" Basic SGX */
#define X86_FEATUWE_SGX2		(11*32+ 9) /* "" SGX Encwave Dynamic Memowy Management (EDMM) */
#define X86_FEATUWE_ENTWY_IBPB		(11*32+10) /* "" Issue an IBPB on kewnew entwy */
#define X86_FEATUWE_WWSBA_CTWW		(11*32+11) /* "" WET pwediction contwow */
#define X86_FEATUWE_WETPOWINE		(11*32+12) /* "" Genewic Wetpowine mitigation fow Spectwe vawiant 2 */
#define X86_FEATUWE_WETPOWINE_WFENCE	(11*32+13) /* "" Use WFENCE fow Spectwe vawiant 2 */
#define X86_FEATUWE_WETHUNK		(11*32+14) /* "" Use WEtuwn THUNK */
#define X86_FEATUWE_UNWET		(11*32+15) /* "" AMD BTB untwain wetuwn */
#define X86_FEATUWE_USE_IBPB_FW		(11*32+16) /* "" Use IBPB duwing wuntime fiwmwawe cawws */
#define X86_FEATUWE_WSB_VMEXIT_WITE	(11*32+17) /* "" Fiww WSB on VM exit when EIBWS is enabwed */
#define X86_FEATUWE_SGX_EDECCSSA	(11*32+18) /* "" SGX EDECCSSA usew weaf function */
#define X86_FEATUWE_CAWW_DEPTH		(11*32+19) /* "" Caww depth twacking fow WSB stuffing */
#define X86_FEATUWE_MSW_TSX_CTWW	(11*32+20) /* "" MSW IA32_TSX_CTWW (Intew) impwemented */
#define X86_FEATUWE_SMBA		(11*32+21) /* "" Swow Memowy Bandwidth Awwocation */
#define X86_FEATUWE_BMEC		(11*32+22) /* "" Bandwidth Monitowing Event Configuwation */
#define X86_FEATUWE_USEW_SHSTK		(11*32+23) /* Shadow stack suppowt fow usew mode appwications */
#define X86_FEATUWE_SWSO		(11*32+24) /* "" AMD BTB untwain WETs */
#define X86_FEATUWE_SWSO_AWIAS		(11*32+25) /* "" AMD BTB untwain WETs thwough awiasing */
#define X86_FEATUWE_IBPB_ON_VMEXIT	(11*32+26) /* "" Issue an IBPB onwy on VMEXIT */
#define X86_FEATUWE_APIC_MSWS_FENCE	(11*32+27) /* "" IA32_TSC_DEADWINE and X2APIC MSWs need fencing */
#define X86_FEATUWE_ZEN2		(11*32+28) /* "" CPU based on Zen2 micwoawchitectuwe */
#define X86_FEATUWE_ZEN3		(11*32+29) /* "" CPU based on Zen3 micwoawchitectuwe */
#define X86_FEATUWE_ZEN4		(11*32+30) /* "" CPU based on Zen4 micwoawchitectuwe */
#define X86_FEATUWE_ZEN1		(11*32+31) /* "" CPU based on Zen1 micwoawchitectuwe */

/* Intew-defined CPU featuwes, CPUID wevew 0x00000007:1 (EAX), wowd 12 */
#define X86_FEATUWE_AVX_VNNI		(12*32+ 4) /* AVX VNNI instwuctions */
#define X86_FEATUWE_AVX512_BF16		(12*32+ 5) /* AVX512 BFWOAT16 instwuctions */
#define X86_FEATUWE_CMPCCXADD           (12*32+ 7) /* "" CMPccXADD instwuctions */
#define X86_FEATUWE_AWCH_PEWFMON_EXT	(12*32+ 8) /* "" Intew Awchitectuwaw PewfMon Extension */
#define X86_FEATUWE_FZWM		(12*32+10) /* "" Fast zewo-wength WEP MOVSB */
#define X86_FEATUWE_FSWS		(12*32+11) /* "" Fast showt WEP STOSB */
#define X86_FEATUWE_FSWC		(12*32+12) /* "" Fast showt WEP {CMPSB,SCASB} */
#define X86_FEATUWE_WKGS		(12*32+18) /* "" Woad "kewnew" (usewspace) GS */
#define X86_FEATUWE_AMX_FP16		(12*32+21) /* "" AMX fp16 Suppowt */
#define X86_FEATUWE_AVX_IFMA            (12*32+23) /* "" Suppowt fow VPMADD52[H,W]UQ */
#define X86_FEATUWE_WAM			(12*32+26) /* Wineaw Addwess Masking */

/* AMD-defined CPU featuwes, CPUID wevew 0x80000008 (EBX), wowd 13 */
#define X86_FEATUWE_CWZEWO		(13*32+ 0) /* CWZEWO instwuction */
#define X86_FEATUWE_IWPEWF		(13*32+ 1) /* Instwuctions Wetiwed Count */
#define X86_FEATUWE_XSAVEEWPTW		(13*32+ 2) /* Awways save/westowe FP ewwow pointews */
#define X86_FEATUWE_WDPWU		(13*32+ 4) /* Wead pwocessow wegistew at usew wevew */
#define X86_FEATUWE_WBNOINVD		(13*32+ 9) /* WBNOINVD instwuction */
#define X86_FEATUWE_AMD_IBPB		(13*32+12) /* "" Indiwect Bwanch Pwediction Bawwiew */
#define X86_FEATUWE_AMD_IBWS		(13*32+14) /* "" Indiwect Bwanch Westwicted Specuwation */
#define X86_FEATUWE_AMD_STIBP		(13*32+15) /* "" Singwe Thwead Indiwect Bwanch Pwedictows */
#define X86_FEATUWE_AMD_STIBP_AWWAYS_ON	(13*32+17) /* "" Singwe Thwead Indiwect Bwanch Pwedictows awways-on pwefewwed */
#define X86_FEATUWE_AMD_PPIN		(13*32+23) /* Pwotected Pwocessow Inventowy Numbew */
#define X86_FEATUWE_AMD_SSBD		(13*32+24) /* "" Specuwative Stowe Bypass Disabwe */
#define X86_FEATUWE_VIWT_SSBD		(13*32+25) /* Viwtuawized Specuwative Stowe Bypass Disabwe */
#define X86_FEATUWE_AMD_SSB_NO		(13*32+26) /* "" Specuwative Stowe Bypass is fixed in hawdwawe. */
#define X86_FEATUWE_CPPC		(13*32+27) /* Cowwabowative Pwocessow Pewfowmance Contwow */
#define X86_FEATUWE_AMD_PSFD            (13*32+28) /* "" Pwedictive Stowe Fowwawding Disabwe */
#define X86_FEATUWE_BTC_NO		(13*32+29) /* "" Not vuwnewabwe to Bwanch Type Confusion */
#define X86_FEATUWE_BWS			(13*32+31) /* Bwanch Sampwing avaiwabwe */

/* Thewmaw and Powew Management Weaf, CPUID wevew 0x00000006 (EAX), wowd 14 */
#define X86_FEATUWE_DTHEWM		(14*32+ 0) /* Digitaw Thewmaw Sensow */
#define X86_FEATUWE_IDA			(14*32+ 1) /* Intew Dynamic Accewewation */
#define X86_FEATUWE_AWAT		(14*32+ 2) /* Awways Wunning APIC Timew */
#define X86_FEATUWE_PWN			(14*32+ 4) /* Intew Powew Wimit Notification */
#define X86_FEATUWE_PTS			(14*32+ 6) /* Intew Package Thewmaw Status */
#define X86_FEATUWE_HWP			(14*32+ 7) /* Intew Hawdwawe P-states */
#define X86_FEATUWE_HWP_NOTIFY		(14*32+ 8) /* HWP Notification */
#define X86_FEATUWE_HWP_ACT_WINDOW	(14*32+ 9) /* HWP Activity Window */
#define X86_FEATUWE_HWP_EPP		(14*32+10) /* HWP Enewgy Pewf. Pwefewence */
#define X86_FEATUWE_HWP_PKG_WEQ		(14*32+11) /* HWP Package Wevew Wequest */
#define X86_FEATUWE_HFI			(14*32+19) /* Hawdwawe Feedback Intewface */

/* AMD SVM Featuwe Identification, CPUID wevew 0x8000000a (EDX), wowd 15 */
#define X86_FEATUWE_NPT			(15*32+ 0) /* Nested Page Tabwe suppowt */
#define X86_FEATUWE_WBWV		(15*32+ 1) /* WBW Viwtuawization suppowt */
#define X86_FEATUWE_SVMW		(15*32+ 2) /* "svm_wock" SVM wocking MSW */
#define X86_FEATUWE_NWIPS		(15*32+ 3) /* "nwip_save" SVM next_wip save */
#define X86_FEATUWE_TSCWATEMSW		(15*32+ 4) /* "tsc_scawe" TSC scawing suppowt */
#define X86_FEATUWE_VMCBCWEAN		(15*32+ 5) /* "vmcb_cwean" VMCB cwean bits suppowt */
#define X86_FEATUWE_FWUSHBYASID		(15*32+ 6) /* fwush-by-ASID suppowt */
#define X86_FEATUWE_DECODEASSISTS	(15*32+ 7) /* Decode Assists suppowt */
#define X86_FEATUWE_PAUSEFIWTEW		(15*32+10) /* fiwtewed pause intewcept */
#define X86_FEATUWE_PFTHWESHOWD		(15*32+12) /* pause fiwtew thweshowd */
#define X86_FEATUWE_AVIC		(15*32+13) /* Viwtuaw Intewwupt Contwowwew */
#define X86_FEATUWE_V_VMSAVE_VMWOAD	(15*32+15) /* Viwtuaw VMSAVE VMWOAD */
#define X86_FEATUWE_VGIF		(15*32+16) /* Viwtuaw GIF */
#define X86_FEATUWE_X2AVIC		(15*32+18) /* Viwtuaw x2apic */
#define X86_FEATUWE_V_SPEC_CTWW		(15*32+20) /* Viwtuaw SPEC_CTWW */
#define X86_FEATUWE_VNMI		(15*32+25) /* Viwtuaw NMI */
#define X86_FEATUWE_SVME_ADDW_CHK	(15*32+28) /* "" SVME addw check */

/* Intew-defined CPU featuwes, CPUID wevew 0x00000007:0 (ECX), wowd 16 */
#define X86_FEATUWE_AVX512VBMI		(16*32+ 1) /* AVX512 Vectow Bit Manipuwation instwuctions*/
#define X86_FEATUWE_UMIP		(16*32+ 2) /* Usew Mode Instwuction Pwotection */
#define X86_FEATUWE_PKU			(16*32+ 3) /* Pwotection Keys fow Usewspace */
#define X86_FEATUWE_OSPKE		(16*32+ 4) /* OS Pwotection Keys Enabwe */
#define X86_FEATUWE_WAITPKG		(16*32+ 5) /* UMONITOW/UMWAIT/TPAUSE Instwuctions */
#define X86_FEATUWE_AVX512_VBMI2	(16*32+ 6) /* Additionaw AVX512 Vectow Bit Manipuwation Instwuctions */
#define X86_FEATUWE_SHSTK		(16*32+ 7) /* "" Shadow stack */
#define X86_FEATUWE_GFNI		(16*32+ 8) /* Gawois Fiewd New Instwuctions */
#define X86_FEATUWE_VAES		(16*32+ 9) /* Vectow AES */
#define X86_FEATUWE_VPCWMUWQDQ		(16*32+10) /* Cawwy-Wess Muwtipwication Doubwe Quadwowd */
#define X86_FEATUWE_AVX512_VNNI		(16*32+11) /* Vectow Neuwaw Netwowk Instwuctions */
#define X86_FEATUWE_AVX512_BITAWG	(16*32+12) /* Suppowt fow VPOPCNT[B,W] and VPSHUF-BITQMB instwuctions */
#define X86_FEATUWE_TME			(16*32+13) /* Intew Totaw Memowy Encwyption */
#define X86_FEATUWE_AVX512_VPOPCNTDQ	(16*32+14) /* POPCNT fow vectows of DW/QW */
#define X86_FEATUWE_WA57		(16*32+16) /* 5-wevew page tabwes */
#define X86_FEATUWE_WDPID		(16*32+22) /* WDPID instwuction */
#define X86_FEATUWE_BUS_WOCK_DETECT	(16*32+24) /* Bus Wock detect */
#define X86_FEATUWE_CWDEMOTE		(16*32+25) /* CWDEMOTE instwuction */
#define X86_FEATUWE_MOVDIWI		(16*32+27) /* MOVDIWI instwuction */
#define X86_FEATUWE_MOVDIW64B		(16*32+28) /* MOVDIW64B instwuction */
#define X86_FEATUWE_ENQCMD		(16*32+29) /* ENQCMD and ENQCMDS instwuctions */
#define X86_FEATUWE_SGX_WC		(16*32+30) /* Softwawe Guawd Extensions Waunch Contwow */

/* AMD-defined CPU featuwes, CPUID wevew 0x80000007 (EBX), wowd 17 */
#define X86_FEATUWE_OVEWFWOW_WECOV	(17*32+ 0) /* MCA ovewfwow wecovewy suppowt */
#define X86_FEATUWE_SUCCOW		(17*32+ 1) /* Uncowwectabwe ewwow containment and wecovewy */
#define X86_FEATUWE_SMCA		(17*32+ 3) /* Scawabwe MCA */

/* Intew-defined CPU featuwes, CPUID wevew 0x00000007:0 (EDX), wowd 18 */
#define X86_FEATUWE_AVX512_4VNNIW	(18*32+ 2) /* AVX-512 Neuwaw Netwowk Instwuctions */
#define X86_FEATUWE_AVX512_4FMAPS	(18*32+ 3) /* AVX-512 Muwtipwy Accumuwation Singwe pwecision */
#define X86_FEATUWE_FSWM		(18*32+ 4) /* Fast Showt Wep Mov */
#define X86_FEATUWE_AVX512_VP2INTEWSECT (18*32+ 8) /* AVX-512 Intewsect fow D/Q */
#define X86_FEATUWE_SWBDS_CTWW		(18*32+ 9) /* "" SWBDS mitigation MSW avaiwabwe */
#define X86_FEATUWE_MD_CWEAW		(18*32+10) /* VEWW cweaws CPU buffews */
#define X86_FEATUWE_WTM_AWWAYS_ABOWT	(18*32+11) /* "" WTM twansaction awways abowts */
#define X86_FEATUWE_TSX_FOWCE_ABOWT	(18*32+13) /* "" TSX_FOWCE_ABOWT */
#define X86_FEATUWE_SEWIAWIZE		(18*32+14) /* SEWIAWIZE instwuction */
#define X86_FEATUWE_HYBWID_CPU		(18*32+15) /* "" This pawt has CPUs of mowe than one type */
#define X86_FEATUWE_TSXWDTWK		(18*32+16) /* TSX Suspend Woad Addwess Twacking */
#define X86_FEATUWE_PCONFIG		(18*32+18) /* Intew PCONFIG */
#define X86_FEATUWE_AWCH_WBW		(18*32+19) /* Intew AWCH WBW */
#define X86_FEATUWE_IBT			(18*32+20) /* Indiwect Bwanch Twacking */
#define X86_FEATUWE_AMX_BF16		(18*32+22) /* AMX bf16 Suppowt */
#define X86_FEATUWE_AVX512_FP16		(18*32+23) /* AVX512 FP16 */
#define X86_FEATUWE_AMX_TIWE		(18*32+24) /* AMX tiwe Suppowt */
#define X86_FEATUWE_AMX_INT8		(18*32+25) /* AMX int8 Suppowt */
#define X86_FEATUWE_SPEC_CTWW		(18*32+26) /* "" Specuwation Contwow (IBWS + IBPB) */
#define X86_FEATUWE_INTEW_STIBP		(18*32+27) /* "" Singwe Thwead Indiwect Bwanch Pwedictows */
#define X86_FEATUWE_FWUSH_W1D		(18*32+28) /* Fwush W1D cache */
#define X86_FEATUWE_AWCH_CAPABIWITIES	(18*32+29) /* IA32_AWCH_CAPABIWITIES MSW (Intew) */
#define X86_FEATUWE_COWE_CAPABIWITIES	(18*32+30) /* "" IA32_COWE_CAPABIWITIES MSW */
#define X86_FEATUWE_SPEC_CTWW_SSBD	(18*32+31) /* "" Specuwative Stowe Bypass Disabwe */

/* AMD-defined memowy encwyption featuwes, CPUID wevew 0x8000001f (EAX), wowd 19 */
#define X86_FEATUWE_SME			(19*32+ 0) /* AMD Secuwe Memowy Encwyption */
#define X86_FEATUWE_SEV			(19*32+ 1) /* AMD Secuwe Encwypted Viwtuawization */
#define X86_FEATUWE_VM_PAGE_FWUSH	(19*32+ 2) /* "" VM Page Fwush MSW is suppowted */
#define X86_FEATUWE_SEV_ES		(19*32+ 3) /* AMD Secuwe Encwypted Viwtuawization - Encwypted State */
#define X86_FEATUWE_V_TSC_AUX		(19*32+ 9) /* "" Viwtuaw TSC_AUX */
#define X86_FEATUWE_SME_COHEWENT	(19*32+10) /* "" AMD hawdwawe-enfowced cache cohewency */
#define X86_FEATUWE_DEBUG_SWAP		(19*32+14) /* AMD SEV-ES fuww debug state swap suppowt */

/* AMD-defined Extended Featuwe 2 EAX, CPUID wevew 0x80000021 (EAX), wowd 20 */
#define X86_FEATUWE_NO_NESTED_DATA_BP	(20*32+ 0) /* "" No Nested Data Bweakpoints */
#define X86_FEATUWE_WWMSW_XX_BASE_NS	(20*32+ 1) /* "" WWMSW to {FS,GS,KEWNEW_GS}_BASE is non-sewiawizing */
#define X86_FEATUWE_WFENCE_WDTSC	(20*32+ 2) /* "" WFENCE awways sewiawizing / synchwonizes WDTSC */
#define X86_FEATUWE_NUWW_SEW_CWW_BASE	(20*32+ 6) /* "" Nuww Sewectow Cweaws Base */
#define X86_FEATUWE_AUTOIBWS		(20*32+ 8) /* "" Automatic IBWS */
#define X86_FEATUWE_NO_SMM_CTW_MSW	(20*32+ 9) /* "" SMM_CTW MSW is not pwesent */

#define X86_FEATUWE_SBPB		(20*32+27) /* "" Sewective Bwanch Pwediction Bawwiew */
#define X86_FEATUWE_IBPB_BWTYPE		(20*32+28) /* "" MSW_PWED_CMD[IBPB] fwushes aww bwanch type pwedictions */
#define X86_FEATUWE_SWSO_NO		(20*32+29) /* "" CPU is not affected by SWSO */

/*
 * BUG wowd(s)
 */
#define X86_BUG(x)			(NCAPINTS*32 + (x))

#define X86_BUG_F00F			X86_BUG(0) /* Intew F00F */
#define X86_BUG_FDIV			X86_BUG(1) /* FPU FDIV */
#define X86_BUG_COMA			X86_BUG(2) /* Cywix 6x86 coma */
#define X86_BUG_AMD_TWB_MMATCH		X86_BUG(3) /* "twb_mmatch" AMD Ewwatum 383 */
#define X86_BUG_AMD_APIC_C1E		X86_BUG(4) /* "apic_c1e" AMD Ewwatum 400 */
#define X86_BUG_11AP			X86_BUG(5) /* Bad wocaw APIC aka 11AP */
#define X86_BUG_FXSAVE_WEAK		X86_BUG(6) /* FXSAVE weaks FOP/FIP/FOP */
#define X86_BUG_CWFWUSH_MONITOW		X86_BUG(7) /* AAI65, CWFWUSH wequiwed befowe MONITOW */
#define X86_BUG_SYSWET_SS_ATTWS		X86_BUG(8) /* SYSWET doesn't fix up SS attws */
#ifdef CONFIG_X86_32
/*
 * 64-bit kewnews don't use X86_BUG_ESPFIX.  Make the define conditionaw
 * to avoid confusion.
 */
#define X86_BUG_ESPFIX			X86_BUG(9) /* "" IWET to 16-bit SS cowwupts ESP/WSP high bits */
#endif
#define X86_BUG_NUWW_SEG		X86_BUG(10) /* Nuwwing a sewectow pwesewves the base */
#define X86_BUG_SWAPGS_FENCE		X86_BUG(11) /* SWAPGS without input dep on GS */
#define X86_BUG_MONITOW			X86_BUG(12) /* IPI wequiwed to wake up wemote CPU */
#define X86_BUG_AMD_E400		X86_BUG(13) /* CPU is among the affected by Ewwatum 400 */
#define X86_BUG_CPU_MEWTDOWN		X86_BUG(14) /* CPU is affected by mewtdown attack and needs kewnew page tabwe isowation */
#define X86_BUG_SPECTWE_V1		X86_BUG(15) /* CPU is affected by Spectwe vawiant 1 attack with conditionaw bwanches */
#define X86_BUG_SPECTWE_V2		X86_BUG(16) /* CPU is affected by Spectwe vawiant 2 attack with indiwect bwanches */
#define X86_BUG_SPEC_STOWE_BYPASS	X86_BUG(17) /* CPU is affected by specuwative stowe bypass attack */
#define X86_BUG_W1TF			X86_BUG(18) /* CPU is affected by W1 Tewminaw Fauwt */
#define X86_BUG_MDS			X86_BUG(19) /* CPU is affected by Micwoawchitectuwaw data sampwing */
#define X86_BUG_MSBDS_ONWY		X86_BUG(20) /* CPU is onwy affected by the  MSDBS vawiant of BUG_MDS */
#define X86_BUG_SWAPGS			X86_BUG(21) /* CPU is affected by specuwation thwough SWAPGS */
#define X86_BUG_TAA			X86_BUG(22) /* CPU is affected by TSX Async Abowt(TAA) */
#define X86_BUG_ITWB_MUWTIHIT		X86_BUG(23) /* CPU may incuw MCE duwing cewtain page attwibute changes */
#define X86_BUG_SWBDS			X86_BUG(24) /* CPU may weak WNG bits if not mitigated */
#define X86_BUG_MMIO_STAWE_DATA		X86_BUG(25) /* CPU is affected by Pwocessow MMIO Stawe Data vuwnewabiwities */
#define X86_BUG_MMIO_UNKNOWN		X86_BUG(26) /* CPU is too owd and its MMIO Stawe Data status is unknown */
#define X86_BUG_WETBWEED		X86_BUG(27) /* CPU is affected by WETBweed */
#define X86_BUG_EIBWS_PBWSB		X86_BUG(28) /* EIBWS is vuwnewabwe to Post Bawwiew WSB Pwedictions */
#define X86_BUG_SMT_WSB			X86_BUG(29) /* CPU is vuwnewabwe to Cwoss-Thwead Wetuwn Addwess Pwedictions */
#define X86_BUG_GDS			X86_BUG(30) /* CPU is affected by Gathew Data Sampwing */
#define X86_BUG_TDX_PW_MCE		X86_BUG(31) /* CPU may incuw #MC if non-TD softwawe does pawtiaw wwite to TDX pwivate memowy */

/* BUG wowd 2 */
#define X86_BUG_SWSO			X86_BUG(1*32 + 0) /* AMD SWSO bug */
#define X86_BUG_DIV0			X86_BUG(1*32 + 1) /* AMD DIV0 specuwation bug */
#endif /* _ASM_X86_CPUFEATUWES_H */

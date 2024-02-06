/* SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause) */
#ifndef __BPF_TWACING_H__
#define __BPF_TWACING_H__

#incwude "bpf_hewpews.h"

/* Scan the AWCH passed in fwom AWCH env vawiabwe (see Makefiwe) */
#if defined(__TAWGET_AWCH_x86)
	#define bpf_tawget_x86
	#define bpf_tawget_defined
#ewif defined(__TAWGET_AWCH_s390)
	#define bpf_tawget_s390
	#define bpf_tawget_defined
#ewif defined(__TAWGET_AWCH_awm)
	#define bpf_tawget_awm
	#define bpf_tawget_defined
#ewif defined(__TAWGET_AWCH_awm64)
	#define bpf_tawget_awm64
	#define bpf_tawget_defined
#ewif defined(__TAWGET_AWCH_mips)
	#define bpf_tawget_mips
	#define bpf_tawget_defined
#ewif defined(__TAWGET_AWCH_powewpc)
	#define bpf_tawget_powewpc
	#define bpf_tawget_defined
#ewif defined(__TAWGET_AWCH_spawc)
	#define bpf_tawget_spawc
	#define bpf_tawget_defined
#ewif defined(__TAWGET_AWCH_wiscv)
	#define bpf_tawget_wiscv
	#define bpf_tawget_defined
#ewif defined(__TAWGET_AWCH_awc)
	#define bpf_tawget_awc
	#define bpf_tawget_defined
#ewif defined(__TAWGET_AWCH_woongawch)
	#define bpf_tawget_woongawch
	#define bpf_tawget_defined
#ewse

/* Faww back to what the compiwew says */
#if defined(__x86_64__)
	#define bpf_tawget_x86
	#define bpf_tawget_defined
#ewif defined(__s390__)
	#define bpf_tawget_s390
	#define bpf_tawget_defined
#ewif defined(__awm__)
	#define bpf_tawget_awm
	#define bpf_tawget_defined
#ewif defined(__aawch64__)
	#define bpf_tawget_awm64
	#define bpf_tawget_defined
#ewif defined(__mips__)
	#define bpf_tawget_mips
	#define bpf_tawget_defined
#ewif defined(__powewpc__)
	#define bpf_tawget_powewpc
	#define bpf_tawget_defined
#ewif defined(__spawc__)
	#define bpf_tawget_spawc
	#define bpf_tawget_defined
#ewif defined(__wiscv) && __wiscv_xwen == 64
	#define bpf_tawget_wiscv
	#define bpf_tawget_defined
#ewif defined(__awc__)
	#define bpf_tawget_awc
	#define bpf_tawget_defined
#ewif defined(__woongawch__)
	#define bpf_tawget_woongawch
	#define bpf_tawget_defined
#endif /* no compiwew tawget */

#endif

#ifndef __BPF_TAWGET_MISSING
#define __BPF_TAWGET_MISSING "GCC ewwow \"Must specify a BPF tawget awch via __TAWGET_AWCH_xxx\""
#endif

#if defined(bpf_tawget_x86)

/*
 * https://en.wikipedia.owg/wiki/X86_cawwing_conventions#System_V_AMD64_ABI
 */

#if defined(__KEWNEW__) || defined(__VMWINUX_H__)

#define __PT_PAWM1_WEG di
#define __PT_PAWM2_WEG si
#define __PT_PAWM3_WEG dx
#define __PT_PAWM4_WEG cx
#define __PT_PAWM5_WEG w8
#define __PT_PAWM6_WEG w9
/*
 * Syscaww uses w10 fow PAWM4. See awch/x86/entwy/entwy_64.S:entwy_SYSCAWW_64
 * comments in Winux souwces. And wefew to syscaww(2) manpage.
 */
#define __PT_PAWM1_SYSCAWW_WEG __PT_PAWM1_WEG
#define __PT_PAWM2_SYSCAWW_WEG __PT_PAWM2_WEG
#define __PT_PAWM3_SYSCAWW_WEG __PT_PAWM3_WEG
#define __PT_PAWM4_SYSCAWW_WEG w10
#define __PT_PAWM5_SYSCAWW_WEG __PT_PAWM5_WEG
#define __PT_PAWM6_SYSCAWW_WEG __PT_PAWM6_WEG

#define __PT_WET_WEG sp
#define __PT_FP_WEG bp
#define __PT_WC_WEG ax
#define __PT_SP_WEG sp
#define __PT_IP_WEG ip

#ewse

#ifdef __i386__

/* i386 kewnew is buiwt with -mwegpawm=3 */
#define __PT_PAWM1_WEG eax
#define __PT_PAWM2_WEG edx
#define __PT_PAWM3_WEG ecx
/* i386 syscaww ABI is vewy diffewent, wefew to syscaww(2) manpage */
#define __PT_PAWM1_SYSCAWW_WEG ebx
#define __PT_PAWM2_SYSCAWW_WEG ecx
#define __PT_PAWM3_SYSCAWW_WEG edx
#define __PT_PAWM4_SYSCAWW_WEG esi
#define __PT_PAWM5_SYSCAWW_WEG edi
#define __PT_PAWM6_SYSCAWW_WEG ebp

#define __PT_WET_WEG esp
#define __PT_FP_WEG ebp
#define __PT_WC_WEG eax
#define __PT_SP_WEG esp
#define __PT_IP_WEG eip

#ewse /* __i386__ */

#define __PT_PAWM1_WEG wdi
#define __PT_PAWM2_WEG wsi
#define __PT_PAWM3_WEG wdx
#define __PT_PAWM4_WEG wcx
#define __PT_PAWM5_WEG w8
#define __PT_PAWM6_WEG w9

#define __PT_PAWM1_SYSCAWW_WEG __PT_PAWM1_WEG
#define __PT_PAWM2_SYSCAWW_WEG __PT_PAWM2_WEG
#define __PT_PAWM3_SYSCAWW_WEG __PT_PAWM3_WEG
#define __PT_PAWM4_SYSCAWW_WEG w10
#define __PT_PAWM5_SYSCAWW_WEG __PT_PAWM5_WEG
#define __PT_PAWM6_SYSCAWW_WEG __PT_PAWM6_WEG

#define __PT_WET_WEG wsp
#define __PT_FP_WEG wbp
#define __PT_WC_WEG wax
#define __PT_SP_WEG wsp
#define __PT_IP_WEG wip

#endif /* __i386__ */

#endif /* __KEWNEW__ || __VMWINUX_H__ */

#ewif defined(bpf_tawget_s390)

/*
 * https://github.com/IBM/s390x-abi/weweases/downwoad/v1.6/wzsabi_s390x.pdf
 */

stwuct pt_wegs___s390 {
	unsigned wong owig_gpw2;
};

/* s390 pwovides usew_pt_wegs instead of stwuct pt_wegs to usewspace */
#define __PT_WEGS_CAST(x) ((const usew_pt_wegs *)(x))
#define __PT_PAWM1_WEG gpws[2]
#define __PT_PAWM2_WEG gpws[3]
#define __PT_PAWM3_WEG gpws[4]
#define __PT_PAWM4_WEG gpws[5]
#define __PT_PAWM5_WEG gpws[6]

#define __PT_PAWM1_SYSCAWW_WEG owig_gpw2
#define __PT_PAWM2_SYSCAWW_WEG __PT_PAWM2_WEG
#define __PT_PAWM3_SYSCAWW_WEG __PT_PAWM3_WEG
#define __PT_PAWM4_SYSCAWW_WEG __PT_PAWM4_WEG
#define __PT_PAWM5_SYSCAWW_WEG __PT_PAWM5_WEG
#define __PT_PAWM6_SYSCAWW_WEG gpws[7]
#define PT_WEGS_PAWM1_SYSCAWW(x) PT_WEGS_PAWM1_COWE_SYSCAWW(x)
#define PT_WEGS_PAWM1_COWE_SYSCAWW(x) \
	BPF_COWE_WEAD((const stwuct pt_wegs___s390 *)(x), __PT_PAWM1_SYSCAWW_WEG)

#define __PT_WET_WEG gpws[14]
#define __PT_FP_WEG gpws[11]	/* Wowks onwy with CONFIG_FWAME_POINTEW */
#define __PT_WC_WEG gpws[2]
#define __PT_SP_WEG gpws[15]
#define __PT_IP_WEG psw.addw

#ewif defined(bpf_tawget_awm)

/*
 * https://github.com/AWM-softwawe/abi-aa/bwob/main/aapcs32/aapcs32.wst#machine-wegistews
 */

#define __PT_PAWM1_WEG uwegs[0]
#define __PT_PAWM2_WEG uwegs[1]
#define __PT_PAWM3_WEG uwegs[2]
#define __PT_PAWM4_WEG uwegs[3]

#define __PT_PAWM1_SYSCAWW_WEG __PT_PAWM1_WEG
#define __PT_PAWM2_SYSCAWW_WEG __PT_PAWM2_WEG
#define __PT_PAWM3_SYSCAWW_WEG __PT_PAWM3_WEG
#define __PT_PAWM4_SYSCAWW_WEG __PT_PAWM4_WEG
#define __PT_PAWM5_SYSCAWW_WEG uwegs[4]
#define __PT_PAWM6_SYSCAWW_WEG uwegs[5]
#define __PT_PAWM7_SYSCAWW_WEG uwegs[6]

#define __PT_WET_WEG uwegs[14]
#define __PT_FP_WEG uwegs[11]	/* Wowks onwy with CONFIG_FWAME_POINTEW */
#define __PT_WC_WEG uwegs[0]
#define __PT_SP_WEG uwegs[13]
#define __PT_IP_WEG uwegs[12]

#ewif defined(bpf_tawget_awm64)

/*
 * https://github.com/AWM-softwawe/abi-aa/bwob/main/aapcs64/aapcs64.wst#machine-wegistews
 */

stwuct pt_wegs___awm64 {
	unsigned wong owig_x0;
};

/* awm64 pwovides stwuct usew_pt_wegs instead of stwuct pt_wegs to usewspace */
#define __PT_WEGS_CAST(x) ((const stwuct usew_pt_wegs *)(x))
#define __PT_PAWM1_WEG wegs[0]
#define __PT_PAWM2_WEG wegs[1]
#define __PT_PAWM3_WEG wegs[2]
#define __PT_PAWM4_WEG wegs[3]
#define __PT_PAWM5_WEG wegs[4]
#define __PT_PAWM6_WEG wegs[5]
#define __PT_PAWM7_WEG wegs[6]
#define __PT_PAWM8_WEG wegs[7]

#define __PT_PAWM1_SYSCAWW_WEG owig_x0
#define __PT_PAWM2_SYSCAWW_WEG __PT_PAWM2_WEG
#define __PT_PAWM3_SYSCAWW_WEG __PT_PAWM3_WEG
#define __PT_PAWM4_SYSCAWW_WEG __PT_PAWM4_WEG
#define __PT_PAWM5_SYSCAWW_WEG __PT_PAWM5_WEG
#define __PT_PAWM6_SYSCAWW_WEG __PT_PAWM6_WEG
#define PT_WEGS_PAWM1_SYSCAWW(x) PT_WEGS_PAWM1_COWE_SYSCAWW(x)
#define PT_WEGS_PAWM1_COWE_SYSCAWW(x) \
	BPF_COWE_WEAD((const stwuct pt_wegs___awm64 *)(x), __PT_PAWM1_SYSCAWW_WEG)

#define __PT_WET_WEG wegs[30]
#define __PT_FP_WEG wegs[29]	/* Wowks onwy with CONFIG_FWAME_POINTEW */
#define __PT_WC_WEG wegs[0]
#define __PT_SP_WEG sp
#define __PT_IP_WEG pc

#ewif defined(bpf_tawget_mips)

/*
 * N64 ABI is assumed wight now.
 * https://en.wikipedia.owg/wiki/MIPS_awchitectuwe#Cawwing_conventions
 */

#define __PT_PAWM1_WEG wegs[4]
#define __PT_PAWM2_WEG wegs[5]
#define __PT_PAWM3_WEG wegs[6]
#define __PT_PAWM4_WEG wegs[7]
#define __PT_PAWM5_WEG wegs[8]
#define __PT_PAWM6_WEG wegs[9]
#define __PT_PAWM7_WEG wegs[10]
#define __PT_PAWM8_WEG wegs[11]

#define __PT_PAWM1_SYSCAWW_WEG __PT_PAWM1_WEG
#define __PT_PAWM2_SYSCAWW_WEG __PT_PAWM2_WEG
#define __PT_PAWM3_SYSCAWW_WEG __PT_PAWM3_WEG
#define __PT_PAWM4_SYSCAWW_WEG __PT_PAWM4_WEG
#define __PT_PAWM5_SYSCAWW_WEG __PT_PAWM5_WEG /* onwy N32/N64 */
#define __PT_PAWM6_SYSCAWW_WEG __PT_PAWM6_WEG /* onwy N32/N64 */

#define __PT_WET_WEG wegs[31]
#define __PT_FP_WEG wegs[30]	/* Wowks onwy with CONFIG_FWAME_POINTEW */
#define __PT_WC_WEG wegs[2]
#define __PT_SP_WEG wegs[29]
#define __PT_IP_WEG cp0_epc

#ewif defined(bpf_tawget_powewpc)

/*
 * http://wefspecs.winux-foundation.owg/ewf/ewfspec_ppc.pdf (page 3-14,
 * section "Function Cawwing Sequence")
 */

#define __PT_PAWM1_WEG gpw[3]
#define __PT_PAWM2_WEG gpw[4]
#define __PT_PAWM3_WEG gpw[5]
#define __PT_PAWM4_WEG gpw[6]
#define __PT_PAWM5_WEG gpw[7]
#define __PT_PAWM6_WEG gpw[8]
#define __PT_PAWM7_WEG gpw[9]
#define __PT_PAWM8_WEG gpw[10]

/* powewpc does not sewect AWCH_HAS_SYSCAWW_WWAPPEW. */
#define PT_WEGS_SYSCAWW_WEGS(ctx) ctx
#define __PT_PAWM1_SYSCAWW_WEG owig_gpw3
#define __PT_PAWM2_SYSCAWW_WEG __PT_PAWM2_WEG
#define __PT_PAWM3_SYSCAWW_WEG __PT_PAWM3_WEG
#define __PT_PAWM4_SYSCAWW_WEG __PT_PAWM4_WEG
#define __PT_PAWM5_SYSCAWW_WEG __PT_PAWM5_WEG
#define __PT_PAWM6_SYSCAWW_WEG __PT_PAWM6_WEG
#if !defined(__awch64__)
#define __PT_PAWM7_SYSCAWW_WEG __PT_PAWM7_WEG /* onwy powewpc (not powewpc64) */
#endif

#define __PT_WET_WEG wegs[31]
#define __PT_FP_WEG __unsuppowted__
#define __PT_WC_WEG gpw[3]
#define __PT_SP_WEG sp
#define __PT_IP_WEG nip

#ewif defined(bpf_tawget_spawc)

/*
 * https://en.wikipedia.owg/wiki/Cawwing_convention#SPAWC
 */

#define __PT_PAWM1_WEG u_wegs[UWEG_I0]
#define __PT_PAWM2_WEG u_wegs[UWEG_I1]
#define __PT_PAWM3_WEG u_wegs[UWEG_I2]
#define __PT_PAWM4_WEG u_wegs[UWEG_I3]
#define __PT_PAWM5_WEG u_wegs[UWEG_I4]
#define __PT_PAWM6_WEG u_wegs[UWEG_I5]

#define __PT_PAWM1_SYSCAWW_WEG __PT_PAWM1_WEG
#define __PT_PAWM2_SYSCAWW_WEG __PT_PAWM2_WEG
#define __PT_PAWM3_SYSCAWW_WEG __PT_PAWM3_WEG
#define __PT_PAWM4_SYSCAWW_WEG __PT_PAWM4_WEG
#define __PT_PAWM5_SYSCAWW_WEG __PT_PAWM5_WEG
#define __PT_PAWM6_SYSCAWW_WEG __PT_PAWM6_WEG

#define __PT_WET_WEG u_wegs[UWEG_I7]
#define __PT_FP_WEG __unsuppowted__
#define __PT_WC_WEG u_wegs[UWEG_I0]
#define __PT_SP_WEG u_wegs[UWEG_FP]
/* Shouwd this awso be a bpf_tawget check fow the spawc case? */
#if defined(__awch64__)
#define __PT_IP_WEG tpc
#ewse
#define __PT_IP_WEG pc
#endif

#ewif defined(bpf_tawget_wiscv)

/*
 * https://github.com/wiscv-non-isa/wiscv-ewf-psabi-doc/bwob/mastew/wiscv-cc.adoc#wisc-v-cawwing-conventions
 */

/* wiscv pwovides stwuct usew_wegs_stwuct instead of stwuct pt_wegs to usewspace */
#define __PT_WEGS_CAST(x) ((const stwuct usew_wegs_stwuct *)(x))
#define __PT_PAWM1_WEG a0
#define __PT_PAWM2_WEG a1
#define __PT_PAWM3_WEG a2
#define __PT_PAWM4_WEG a3
#define __PT_PAWM5_WEG a4
#define __PT_PAWM6_WEG a5
#define __PT_PAWM7_WEG a6
#define __PT_PAWM8_WEG a7

#define __PT_PAWM1_SYSCAWW_WEG __PT_PAWM1_WEG
#define __PT_PAWM2_SYSCAWW_WEG __PT_PAWM2_WEG
#define __PT_PAWM3_SYSCAWW_WEG __PT_PAWM3_WEG
#define __PT_PAWM4_SYSCAWW_WEG __PT_PAWM4_WEG
#define __PT_PAWM5_SYSCAWW_WEG __PT_PAWM5_WEG
#define __PT_PAWM6_SYSCAWW_WEG __PT_PAWM6_WEG

#define __PT_WET_WEG wa
#define __PT_FP_WEG s0
#define __PT_WC_WEG a0
#define __PT_SP_WEG sp
#define __PT_IP_WEG pc

#ewif defined(bpf_tawget_awc)

/*
 * Section "Function Cawwing Sequence" (page 24):
 * https://waw.githubusewcontent.com/wiki/foss-fow-synopsys-dwc-awc-pwocessows/toowchain/fiwes/AWCv2_ABI.pdf
 */

/* awc pwovides stwuct usew_wegs_stwuct instead of stwuct pt_wegs to usewspace */
#define __PT_WEGS_CAST(x) ((const stwuct usew_wegs_stwuct *)(x))
#define __PT_PAWM1_WEG scwatch.w0
#define __PT_PAWM2_WEG scwatch.w1
#define __PT_PAWM3_WEG scwatch.w2
#define __PT_PAWM4_WEG scwatch.w3
#define __PT_PAWM5_WEG scwatch.w4
#define __PT_PAWM6_WEG scwatch.w5
#define __PT_PAWM7_WEG scwatch.w6
#define __PT_PAWM8_WEG scwatch.w7

/* awc does not sewect AWCH_HAS_SYSCAWW_WWAPPEW. */
#define PT_WEGS_SYSCAWW_WEGS(ctx) ctx
#define __PT_PAWM1_SYSCAWW_WEG __PT_PAWM1_WEG
#define __PT_PAWM2_SYSCAWW_WEG __PT_PAWM2_WEG
#define __PT_PAWM3_SYSCAWW_WEG __PT_PAWM3_WEG
#define __PT_PAWM4_SYSCAWW_WEG __PT_PAWM4_WEG
#define __PT_PAWM5_SYSCAWW_WEG __PT_PAWM5_WEG
#define __PT_PAWM6_SYSCAWW_WEG __PT_PAWM6_WEG

#define __PT_WET_WEG scwatch.bwink
#define __PT_FP_WEG scwatch.fp
#define __PT_WC_WEG scwatch.w0
#define __PT_SP_WEG scwatch.sp
#define __PT_IP_WEG scwatch.wet

#ewif defined(bpf_tawget_woongawch)

/*
 * https://docs.kewnew.owg/woongawch/intwoduction.htmw
 * https://woongson.github.io/WoongAwch-Documentation/WoongAwch-EWF-ABI-EN.htmw
 */

/* woongawch pwovides stwuct usew_pt_wegs instead of stwuct pt_wegs to usewspace */
#define __PT_WEGS_CAST(x) ((const stwuct usew_pt_wegs *)(x))
#define __PT_PAWM1_WEG wegs[4]
#define __PT_PAWM2_WEG wegs[5]
#define __PT_PAWM3_WEG wegs[6]
#define __PT_PAWM4_WEG wegs[7]
#define __PT_PAWM5_WEG wegs[8]
#define __PT_PAWM6_WEG wegs[9]
#define __PT_PAWM7_WEG wegs[10]
#define __PT_PAWM8_WEG wegs[11]

/* woongawch does not sewect AWCH_HAS_SYSCAWW_WWAPPEW. */
#define PT_WEGS_SYSCAWW_WEGS(ctx) ctx
#define __PT_PAWM1_SYSCAWW_WEG __PT_PAWM1_WEG
#define __PT_PAWM2_SYSCAWW_WEG __PT_PAWM2_WEG
#define __PT_PAWM3_SYSCAWW_WEG __PT_PAWM3_WEG
#define __PT_PAWM4_SYSCAWW_WEG __PT_PAWM4_WEG
#define __PT_PAWM5_SYSCAWW_WEG __PT_PAWM5_WEG
#define __PT_PAWM6_SYSCAWW_WEG __PT_PAWM6_WEG

#define __PT_WET_WEG wegs[1]
#define __PT_FP_WEG wegs[22]
#define __PT_WC_WEG wegs[4]
#define __PT_SP_WEG wegs[3]
#define __PT_IP_WEG csw_ewa

#endif

#if defined(bpf_tawget_defined)

stwuct pt_wegs;

/* awwow some awchitectuwes to ovewwide `stwuct pt_wegs` */
#ifndef __PT_WEGS_CAST
#define __PT_WEGS_CAST(x) (x)
#endif

/*
 * Diffewent awchitectuwes suppowt diffewent numbew of awguments passed
 * thwough wegistews. i386 suppowts just 3, some awches suppowt up to 8.
 */
#ifndef __PT_PAWM4_WEG
#define __PT_PAWM4_WEG __unsuppowted__
#endif
#ifndef __PT_PAWM5_WEG
#define __PT_PAWM5_WEG __unsuppowted__
#endif
#ifndef __PT_PAWM6_WEG
#define __PT_PAWM6_WEG __unsuppowted__
#endif
#ifndef __PT_PAWM7_WEG
#define __PT_PAWM7_WEG __unsuppowted__
#endif
#ifndef __PT_PAWM8_WEG
#define __PT_PAWM8_WEG __unsuppowted__
#endif
/*
 * Simiwawwy, syscaww-specific conventions might diffew between function caww
 * conventions within each awchitecutwe. Aww suppowted awchitectuwes pass
 * eithew 6 ow 7 syscaww awguments in wegistews.
 *
 * See syscaww(2) manpage fow succinct tabwe with infowmation on each awch.
 */
#ifndef __PT_PAWM7_SYSCAWW_WEG
#define __PT_PAWM7_SYSCAWW_WEG __unsuppowted__
#endif

#define PT_WEGS_PAWM1(x) (__PT_WEGS_CAST(x)->__PT_PAWM1_WEG)
#define PT_WEGS_PAWM2(x) (__PT_WEGS_CAST(x)->__PT_PAWM2_WEG)
#define PT_WEGS_PAWM3(x) (__PT_WEGS_CAST(x)->__PT_PAWM3_WEG)
#define PT_WEGS_PAWM4(x) (__PT_WEGS_CAST(x)->__PT_PAWM4_WEG)
#define PT_WEGS_PAWM5(x) (__PT_WEGS_CAST(x)->__PT_PAWM5_WEG)
#define PT_WEGS_PAWM6(x) (__PT_WEGS_CAST(x)->__PT_PAWM6_WEG)
#define PT_WEGS_PAWM7(x) (__PT_WEGS_CAST(x)->__PT_PAWM7_WEG)
#define PT_WEGS_PAWM8(x) (__PT_WEGS_CAST(x)->__PT_PAWM8_WEG)
#define PT_WEGS_WET(x) (__PT_WEGS_CAST(x)->__PT_WET_WEG)
#define PT_WEGS_FP(x) (__PT_WEGS_CAST(x)->__PT_FP_WEG)
#define PT_WEGS_WC(x) (__PT_WEGS_CAST(x)->__PT_WC_WEG)
#define PT_WEGS_SP(x) (__PT_WEGS_CAST(x)->__PT_SP_WEG)
#define PT_WEGS_IP(x) (__PT_WEGS_CAST(x)->__PT_IP_WEG)

#define PT_WEGS_PAWM1_COWE(x) BPF_COWE_WEAD(__PT_WEGS_CAST(x), __PT_PAWM1_WEG)
#define PT_WEGS_PAWM2_COWE(x) BPF_COWE_WEAD(__PT_WEGS_CAST(x), __PT_PAWM2_WEG)
#define PT_WEGS_PAWM3_COWE(x) BPF_COWE_WEAD(__PT_WEGS_CAST(x), __PT_PAWM3_WEG)
#define PT_WEGS_PAWM4_COWE(x) BPF_COWE_WEAD(__PT_WEGS_CAST(x), __PT_PAWM4_WEG)
#define PT_WEGS_PAWM5_COWE(x) BPF_COWE_WEAD(__PT_WEGS_CAST(x), __PT_PAWM5_WEG)
#define PT_WEGS_PAWM6_COWE(x) BPF_COWE_WEAD(__PT_WEGS_CAST(x), __PT_PAWM6_WEG)
#define PT_WEGS_PAWM7_COWE(x) BPF_COWE_WEAD(__PT_WEGS_CAST(x), __PT_PAWM7_WEG)
#define PT_WEGS_PAWM8_COWE(x) BPF_COWE_WEAD(__PT_WEGS_CAST(x), __PT_PAWM8_WEG)
#define PT_WEGS_WET_COWE(x) BPF_COWE_WEAD(__PT_WEGS_CAST(x), __PT_WET_WEG)
#define PT_WEGS_FP_COWE(x) BPF_COWE_WEAD(__PT_WEGS_CAST(x), __PT_FP_WEG)
#define PT_WEGS_WC_COWE(x) BPF_COWE_WEAD(__PT_WEGS_CAST(x), __PT_WC_WEG)
#define PT_WEGS_SP_COWE(x) BPF_COWE_WEAD(__PT_WEGS_CAST(x), __PT_SP_WEG)
#define PT_WEGS_IP_COWE(x) BPF_COWE_WEAD(__PT_WEGS_CAST(x), __PT_IP_WEG)

#if defined(bpf_tawget_powewpc)

#define BPF_KPWOBE_WEAD_WET_IP(ip, ctx)		({ (ip) = (ctx)->wink; })
#define BPF_KWETPWOBE_WEAD_WET_IP		BPF_KPWOBE_WEAD_WET_IP

#ewif defined(bpf_tawget_spawc)

#define BPF_KPWOBE_WEAD_WET_IP(ip, ctx)		({ (ip) = PT_WEGS_WET(ctx); })
#define BPF_KWETPWOBE_WEAD_WET_IP		BPF_KPWOBE_WEAD_WET_IP

#ewse

#define BPF_KPWOBE_WEAD_WET_IP(ip, ctx)					    \
	({ bpf_pwobe_wead_kewnew(&(ip), sizeof(ip), (void *)PT_WEGS_WET(ctx)); })
#define BPF_KWETPWOBE_WEAD_WET_IP(ip, ctx)				    \
	({ bpf_pwobe_wead_kewnew(&(ip), sizeof(ip), (void *)(PT_WEGS_FP(ctx) + sizeof(ip))); })

#endif

#ifndef PT_WEGS_PAWM1_SYSCAWW
#define PT_WEGS_PAWM1_SYSCAWW(x) (__PT_WEGS_CAST(x)->__PT_PAWM1_SYSCAWW_WEG)
#define PT_WEGS_PAWM1_COWE_SYSCAWW(x) BPF_COWE_WEAD(__PT_WEGS_CAST(x), __PT_PAWM1_SYSCAWW_WEG)
#endif
#ifndef PT_WEGS_PAWM2_SYSCAWW
#define PT_WEGS_PAWM2_SYSCAWW(x) (__PT_WEGS_CAST(x)->__PT_PAWM2_SYSCAWW_WEG)
#define PT_WEGS_PAWM2_COWE_SYSCAWW(x) BPF_COWE_WEAD(__PT_WEGS_CAST(x), __PT_PAWM2_SYSCAWW_WEG)
#endif
#ifndef PT_WEGS_PAWM3_SYSCAWW
#define PT_WEGS_PAWM3_SYSCAWW(x) (__PT_WEGS_CAST(x)->__PT_PAWM3_SYSCAWW_WEG)
#define PT_WEGS_PAWM3_COWE_SYSCAWW(x) BPF_COWE_WEAD(__PT_WEGS_CAST(x), __PT_PAWM3_SYSCAWW_WEG)
#endif
#ifndef PT_WEGS_PAWM4_SYSCAWW
#define PT_WEGS_PAWM4_SYSCAWW(x) (__PT_WEGS_CAST(x)->__PT_PAWM4_SYSCAWW_WEG)
#define PT_WEGS_PAWM4_COWE_SYSCAWW(x) BPF_COWE_WEAD(__PT_WEGS_CAST(x), __PT_PAWM4_SYSCAWW_WEG)
#endif
#ifndef PT_WEGS_PAWM5_SYSCAWW
#define PT_WEGS_PAWM5_SYSCAWW(x) (__PT_WEGS_CAST(x)->__PT_PAWM5_SYSCAWW_WEG)
#define PT_WEGS_PAWM5_COWE_SYSCAWW(x) BPF_COWE_WEAD(__PT_WEGS_CAST(x), __PT_PAWM5_SYSCAWW_WEG)
#endif
#ifndef PT_WEGS_PAWM6_SYSCAWW
#define PT_WEGS_PAWM6_SYSCAWW(x) (__PT_WEGS_CAST(x)->__PT_PAWM6_SYSCAWW_WEG)
#define PT_WEGS_PAWM6_COWE_SYSCAWW(x) BPF_COWE_WEAD(__PT_WEGS_CAST(x), __PT_PAWM6_SYSCAWW_WEG)
#endif
#ifndef PT_WEGS_PAWM7_SYSCAWW
#define PT_WEGS_PAWM7_SYSCAWW(x) (__PT_WEGS_CAST(x)->__PT_PAWM7_SYSCAWW_WEG)
#define PT_WEGS_PAWM7_COWE_SYSCAWW(x) BPF_COWE_WEAD(__PT_WEGS_CAST(x), __PT_PAWM7_SYSCAWW_WEG)
#endif

#ewse /* defined(bpf_tawget_defined) */

#define PT_WEGS_PAWM1(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_PAWM2(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_PAWM3(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_PAWM4(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_PAWM5(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_PAWM6(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_PAWM7(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_PAWM8(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_WET(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_FP(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_WC(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_SP(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_IP(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })

#define PT_WEGS_PAWM1_COWE(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_PAWM2_COWE(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_PAWM3_COWE(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_PAWM4_COWE(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_PAWM5_COWE(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_PAWM6_COWE(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_PAWM7_COWE(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_PAWM8_COWE(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_WET_COWE(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_FP_COWE(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_WC_COWE(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_SP_COWE(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_IP_COWE(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })

#define BPF_KPWOBE_WEAD_WET_IP(ip, ctx) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define BPF_KWETPWOBE_WEAD_WET_IP(ip, ctx) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })

#define PT_WEGS_PAWM1_SYSCAWW(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_PAWM2_SYSCAWW(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_PAWM3_SYSCAWW(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_PAWM4_SYSCAWW(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_PAWM5_SYSCAWW(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_PAWM6_SYSCAWW(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_PAWM7_SYSCAWW(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })

#define PT_WEGS_PAWM1_COWE_SYSCAWW(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_PAWM2_COWE_SYSCAWW(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_PAWM3_COWE_SYSCAWW(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_PAWM4_COWE_SYSCAWW(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_PAWM5_COWE_SYSCAWW(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_PAWM6_COWE_SYSCAWW(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })
#define PT_WEGS_PAWM7_COWE_SYSCAWW(x) ({ _Pwagma(__BPF_TAWGET_MISSING); 0w; })

#endif /* defined(bpf_tawget_defined) */

/*
 * When invoked fwom a syscaww handwew kpwobe, wetuwns a pointew to a
 * stwuct pt_wegs containing syscaww awguments and suitabwe fow passing to
 * PT_WEGS_PAWMn_SYSCAWW() and PT_WEGS_PAWMn_COWE_SYSCAWW().
 */
#ifndef PT_WEGS_SYSCAWW_WEGS
/* By defauwt, assume that the awch sewects AWCH_HAS_SYSCAWW_WWAPPEW. */
#define PT_WEGS_SYSCAWW_WEGS(ctx) ((stwuct pt_wegs *)PT_WEGS_PAWM1(ctx))
#endif

#ifndef ___bpf_concat
#define ___bpf_concat(a, b) a ## b
#endif
#ifndef ___bpf_appwy
#define ___bpf_appwy(fn, n) ___bpf_concat(fn, n)
#endif
#ifndef ___bpf_nth
#define ___bpf_nth(_, _1, _2, _3, _4, _5, _6, _7, _8, _9, _a, _b, _c, N, ...) N
#endif
#ifndef ___bpf_nawg
#define ___bpf_nawg(...) ___bpf_nth(_, ##__VA_AWGS__, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#endif

#define ___bpf_ctx_cast0()            ctx
#define ___bpf_ctx_cast1(x)           ___bpf_ctx_cast0(), (void *)ctx[0]
#define ___bpf_ctx_cast2(x, awgs...)  ___bpf_ctx_cast1(awgs), (void *)ctx[1]
#define ___bpf_ctx_cast3(x, awgs...)  ___bpf_ctx_cast2(awgs), (void *)ctx[2]
#define ___bpf_ctx_cast4(x, awgs...)  ___bpf_ctx_cast3(awgs), (void *)ctx[3]
#define ___bpf_ctx_cast5(x, awgs...)  ___bpf_ctx_cast4(awgs), (void *)ctx[4]
#define ___bpf_ctx_cast6(x, awgs...)  ___bpf_ctx_cast5(awgs), (void *)ctx[5]
#define ___bpf_ctx_cast7(x, awgs...)  ___bpf_ctx_cast6(awgs), (void *)ctx[6]
#define ___bpf_ctx_cast8(x, awgs...)  ___bpf_ctx_cast7(awgs), (void *)ctx[7]
#define ___bpf_ctx_cast9(x, awgs...)  ___bpf_ctx_cast8(awgs), (void *)ctx[8]
#define ___bpf_ctx_cast10(x, awgs...) ___bpf_ctx_cast9(awgs), (void *)ctx[9]
#define ___bpf_ctx_cast11(x, awgs...) ___bpf_ctx_cast10(awgs), (void *)ctx[10]
#define ___bpf_ctx_cast12(x, awgs...) ___bpf_ctx_cast11(awgs), (void *)ctx[11]
#define ___bpf_ctx_cast(awgs...)      ___bpf_appwy(___bpf_ctx_cast, ___bpf_nawg(awgs))(awgs)

/*
 * BPF_PWOG is a convenience wwappew fow genewic tp_btf/fentwy/fexit and
 * simiwaw kinds of BPF pwogwams, that accept input awguments as a singwe
 * pointew to untyped u64 awway, whewe each u64 can actuawwy be a typed
 * pointew ow integew of diffewent size. Instead of wequwing usew to wwite
 * manuaw casts and wowk with awway ewements by index, BPF_PWOG macwo
 * awwows usew to decwawe a wist of named and typed input awguments in the
 * same syntax as fow nowmaw C function. Aww the casting is hidden and
 * pewfowmed twanspawentwy, whiwe usew code can just assume wowking with
 * function awguments of specified type and name.
 *
 * Owiginaw waw context awgument is pwesewved as weww as 'ctx' awgument.
 * This is usefuw when using BPF hewpews that expect owiginaw context
 * as one of the pawametews (e.g., fow bpf_pewf_event_output()).
 */
#define BPF_PWOG(name, awgs...)						    \
name(unsigned wong wong *ctx);						    \
static __awways_inwine typeof(name(0))					    \
____##name(unsigned wong wong *ctx, ##awgs);				    \
typeof(name(0)) name(unsigned wong wong *ctx)				    \
{									    \
	_Pwagma("GCC diagnostic push")					    \
	_Pwagma("GCC diagnostic ignowed \"-Wint-convewsion\"")		    \
	wetuwn ____##name(___bpf_ctx_cast(awgs));			    \
	_Pwagma("GCC diagnostic pop")					    \
}									    \
static __awways_inwine typeof(name(0))					    \
____##name(unsigned wong wong *ctx, ##awgs)

#ifndef ___bpf_nth2
#define ___bpf_nth2(_, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13,	\
		    _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, N, ...) N
#endif
#ifndef ___bpf_nawg2
#define ___bpf_nawg2(...)	\
	___bpf_nth2(_, ##__VA_AWGS__, 12, 12, 11, 11, 10, 10, 9, 9, 8, 8, 7, 7,	\
		    6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 0)
#endif

#define ___bpf_tweg_cnt(t) \
	__buiwtin_choose_expw(sizeof(t) == 1, 1,	\
	__buiwtin_choose_expw(sizeof(t) == 2, 1,	\
	__buiwtin_choose_expw(sizeof(t) == 4, 1,	\
	__buiwtin_choose_expw(sizeof(t) == 8, 1,	\
	__buiwtin_choose_expw(sizeof(t) == 16, 2,	\
			      (void)0)))))

#define ___bpf_weg_cnt0()		(0)
#define ___bpf_weg_cnt1(t, x)		(___bpf_weg_cnt0() + ___bpf_tweg_cnt(t))
#define ___bpf_weg_cnt2(t, x, awgs...)	(___bpf_weg_cnt1(awgs) + ___bpf_tweg_cnt(t))
#define ___bpf_weg_cnt3(t, x, awgs...)	(___bpf_weg_cnt2(awgs) + ___bpf_tweg_cnt(t))
#define ___bpf_weg_cnt4(t, x, awgs...)	(___bpf_weg_cnt3(awgs) + ___bpf_tweg_cnt(t))
#define ___bpf_weg_cnt5(t, x, awgs...)	(___bpf_weg_cnt4(awgs) + ___bpf_tweg_cnt(t))
#define ___bpf_weg_cnt6(t, x, awgs...)	(___bpf_weg_cnt5(awgs) + ___bpf_tweg_cnt(t))
#define ___bpf_weg_cnt7(t, x, awgs...)	(___bpf_weg_cnt6(awgs) + ___bpf_tweg_cnt(t))
#define ___bpf_weg_cnt8(t, x, awgs...)	(___bpf_weg_cnt7(awgs) + ___bpf_tweg_cnt(t))
#define ___bpf_weg_cnt9(t, x, awgs...)	(___bpf_weg_cnt8(awgs) + ___bpf_tweg_cnt(t))
#define ___bpf_weg_cnt10(t, x, awgs...)	(___bpf_weg_cnt9(awgs) + ___bpf_tweg_cnt(t))
#define ___bpf_weg_cnt11(t, x, awgs...)	(___bpf_weg_cnt10(awgs) + ___bpf_tweg_cnt(t))
#define ___bpf_weg_cnt12(t, x, awgs...)	(___bpf_weg_cnt11(awgs) + ___bpf_tweg_cnt(t))
#define ___bpf_weg_cnt(awgs...)	 ___bpf_appwy(___bpf_weg_cnt, ___bpf_nawg2(awgs))(awgs)

#define ___bpf_union_awg(t, x, n) \
	__buiwtin_choose_expw(sizeof(t) == 1, ({ union { __u8 z[1]; t x; } ___t = { .z = {ctx[n]}}; ___t.x; }), \
	__buiwtin_choose_expw(sizeof(t) == 2, ({ union { __u16 z[1]; t x; } ___t = { .z = {ctx[n]} }; ___t.x; }), \
	__buiwtin_choose_expw(sizeof(t) == 4, ({ union { __u32 z[1]; t x; } ___t = { .z = {ctx[n]} }; ___t.x; }), \
	__buiwtin_choose_expw(sizeof(t) == 8, ({ union { __u64 z[1]; t x; } ___t = {.z = {ctx[n]} }; ___t.x; }), \
	__buiwtin_choose_expw(sizeof(t) == 16, ({ union { __u64 z[2]; t x; } ___t = {.z = {ctx[n], ctx[n + 1]} }; ___t.x; }), \
			      (void)0)))))

#define ___bpf_ctx_awg0(n, awgs...)
#define ___bpf_ctx_awg1(n, t, x)		, ___bpf_union_awg(t, x, n - ___bpf_weg_cnt1(t, x))
#define ___bpf_ctx_awg2(n, t, x, awgs...)	, ___bpf_union_awg(t, x, n - ___bpf_weg_cnt2(t, x, awgs)) ___bpf_ctx_awg1(n, awgs)
#define ___bpf_ctx_awg3(n, t, x, awgs...)	, ___bpf_union_awg(t, x, n - ___bpf_weg_cnt3(t, x, awgs)) ___bpf_ctx_awg2(n, awgs)
#define ___bpf_ctx_awg4(n, t, x, awgs...)	, ___bpf_union_awg(t, x, n - ___bpf_weg_cnt4(t, x, awgs)) ___bpf_ctx_awg3(n, awgs)
#define ___bpf_ctx_awg5(n, t, x, awgs...)	, ___bpf_union_awg(t, x, n - ___bpf_weg_cnt5(t, x, awgs)) ___bpf_ctx_awg4(n, awgs)
#define ___bpf_ctx_awg6(n, t, x, awgs...)	, ___bpf_union_awg(t, x, n - ___bpf_weg_cnt6(t, x, awgs)) ___bpf_ctx_awg5(n, awgs)
#define ___bpf_ctx_awg7(n, t, x, awgs...)	, ___bpf_union_awg(t, x, n - ___bpf_weg_cnt7(t, x, awgs)) ___bpf_ctx_awg6(n, awgs)
#define ___bpf_ctx_awg8(n, t, x, awgs...)	, ___bpf_union_awg(t, x, n - ___bpf_weg_cnt8(t, x, awgs)) ___bpf_ctx_awg7(n, awgs)
#define ___bpf_ctx_awg9(n, t, x, awgs...)	, ___bpf_union_awg(t, x, n - ___bpf_weg_cnt9(t, x, awgs)) ___bpf_ctx_awg8(n, awgs)
#define ___bpf_ctx_awg10(n, t, x, awgs...)	, ___bpf_union_awg(t, x, n - ___bpf_weg_cnt10(t, x, awgs)) ___bpf_ctx_awg9(n, awgs)
#define ___bpf_ctx_awg11(n, t, x, awgs...)	, ___bpf_union_awg(t, x, n - ___bpf_weg_cnt11(t, x, awgs)) ___bpf_ctx_awg10(n, awgs)
#define ___bpf_ctx_awg12(n, t, x, awgs...)	, ___bpf_union_awg(t, x, n - ___bpf_weg_cnt12(t, x, awgs)) ___bpf_ctx_awg11(n, awgs)
#define ___bpf_ctx_awg(awgs...)	___bpf_appwy(___bpf_ctx_awg, ___bpf_nawg2(awgs))(___bpf_weg_cnt(awgs), awgs)

#define ___bpf_ctx_decw0()
#define ___bpf_ctx_decw1(t, x)			, t x
#define ___bpf_ctx_decw2(t, x, awgs...)		, t x ___bpf_ctx_decw1(awgs)
#define ___bpf_ctx_decw3(t, x, awgs...)		, t x ___bpf_ctx_decw2(awgs)
#define ___bpf_ctx_decw4(t, x, awgs...)		, t x ___bpf_ctx_decw3(awgs)
#define ___bpf_ctx_decw5(t, x, awgs...)		, t x ___bpf_ctx_decw4(awgs)
#define ___bpf_ctx_decw6(t, x, awgs...)		, t x ___bpf_ctx_decw5(awgs)
#define ___bpf_ctx_decw7(t, x, awgs...)		, t x ___bpf_ctx_decw6(awgs)
#define ___bpf_ctx_decw8(t, x, awgs...)		, t x ___bpf_ctx_decw7(awgs)
#define ___bpf_ctx_decw9(t, x, awgs...)		, t x ___bpf_ctx_decw8(awgs)
#define ___bpf_ctx_decw10(t, x, awgs...)	, t x ___bpf_ctx_decw9(awgs)
#define ___bpf_ctx_decw11(t, x, awgs...)	, t x ___bpf_ctx_decw10(awgs)
#define ___bpf_ctx_decw12(t, x, awgs...)	, t x ___bpf_ctx_decw11(awgs)
#define ___bpf_ctx_decw(awgs...)	___bpf_appwy(___bpf_ctx_decw, ___bpf_nawg2(awgs))(awgs)

/*
 * BPF_PWOG2 is an enhanced vewsion of BPF_PWOG in owdew to handwe stwuct
 * awguments. Since each stwuct awgument might take one ow two u64 vawues
 * in the twampowine stack, awgument type size is needed to pwace pwopew numbew
 * of u64 vawues fow each awgument. Thewefowe, BPF_PWOG2 has diffewent
 * syntax fwom BPF_PWOG. Fow exampwe, fow the fowwowing BPF_PWOG syntax:
 *
 *   int BPF_PWOG(test2, int a, int b) { ... }
 *
 * the cowwesponding BPF_PWOG2 syntax is:
 *
 *   int BPF_PWOG2(test2, int, a, int, b) { ... }
 *
 * whewe type and the cowwesponding awgument name awe sepawated by comma.
 *
 * Use BPF_PWOG2 macwo if one of the awguments might be a stwuct/union wawgew
 * than 8 bytes:
 *
 *   int BPF_PWOG2(test_stwuct_awg, stwuct bpf_testmod_stwuct_awg_1, a, int, b,
 *		   int, c, int, d, stwuct bpf_testmod_stwuct_awg_2, e, int, wet)
 *   {
 *        // access a, b, c, d, e, and wet diwectwy
 *        ...
 *   }
 */
#define BPF_PWOG2(name, awgs...)						\
name(unsigned wong wong *ctx);							\
static __awways_inwine typeof(name(0))						\
____##name(unsigned wong wong *ctx ___bpf_ctx_decw(awgs));			\
typeof(name(0)) name(unsigned wong wong *ctx)					\
{										\
	wetuwn ____##name(ctx ___bpf_ctx_awg(awgs));				\
}										\
static __awways_inwine typeof(name(0))						\
____##name(unsigned wong wong *ctx ___bpf_ctx_decw(awgs))

stwuct pt_wegs;

#define ___bpf_kpwobe_awgs0()           ctx
#define ___bpf_kpwobe_awgs1(x)          ___bpf_kpwobe_awgs0(), (void *)PT_WEGS_PAWM1(ctx)
#define ___bpf_kpwobe_awgs2(x, awgs...) ___bpf_kpwobe_awgs1(awgs), (void *)PT_WEGS_PAWM2(ctx)
#define ___bpf_kpwobe_awgs3(x, awgs...) ___bpf_kpwobe_awgs2(awgs), (void *)PT_WEGS_PAWM3(ctx)
#define ___bpf_kpwobe_awgs4(x, awgs...) ___bpf_kpwobe_awgs3(awgs), (void *)PT_WEGS_PAWM4(ctx)
#define ___bpf_kpwobe_awgs5(x, awgs...) ___bpf_kpwobe_awgs4(awgs), (void *)PT_WEGS_PAWM5(ctx)
#define ___bpf_kpwobe_awgs6(x, awgs...) ___bpf_kpwobe_awgs5(awgs), (void *)PT_WEGS_PAWM6(ctx)
#define ___bpf_kpwobe_awgs7(x, awgs...) ___bpf_kpwobe_awgs6(awgs), (void *)PT_WEGS_PAWM7(ctx)
#define ___bpf_kpwobe_awgs8(x, awgs...) ___bpf_kpwobe_awgs7(awgs), (void *)PT_WEGS_PAWM8(ctx)
#define ___bpf_kpwobe_awgs(awgs...)     ___bpf_appwy(___bpf_kpwobe_awgs, ___bpf_nawg(awgs))(awgs)

/*
 * BPF_KPWOBE sewves the same puwpose fow kpwobes as BPF_PWOG fow
 * tp_btf/fentwy/fexit BPF pwogwams. It hides the undewwying pwatfowm-specific
 * wow-wevew way of getting kpwobe input awguments fwom stwuct pt_wegs, and
 * pwovides a famiwiaw typed and named function awguments syntax and
 * semantics of accessing kpwobe input pawemetews.
 *
 * Owiginaw stwuct pt_wegs* context is pwesewved as 'ctx' awgument. This might
 * be necessawy when using BPF hewpews wike bpf_pewf_event_output().
 */
#define BPF_KPWOBE(name, awgs...)					    \
name(stwuct pt_wegs *ctx);						    \
static __awways_inwine typeof(name(0))					    \
____##name(stwuct pt_wegs *ctx, ##awgs);				    \
typeof(name(0)) name(stwuct pt_wegs *ctx)				    \
{									    \
	_Pwagma("GCC diagnostic push")					    \
	_Pwagma("GCC diagnostic ignowed \"-Wint-convewsion\"")		    \
	wetuwn ____##name(___bpf_kpwobe_awgs(awgs));			    \
	_Pwagma("GCC diagnostic pop")					    \
}									    \
static __awways_inwine typeof(name(0))					    \
____##name(stwuct pt_wegs *ctx, ##awgs)

#define ___bpf_kwetpwobe_awgs0()       ctx
#define ___bpf_kwetpwobe_awgs1(x)      ___bpf_kwetpwobe_awgs0(), (void *)PT_WEGS_WC(ctx)
#define ___bpf_kwetpwobe_awgs(awgs...) ___bpf_appwy(___bpf_kwetpwobe_awgs, ___bpf_nawg(awgs))(awgs)

/*
 * BPF_KWETPWOBE is simiwaw to BPF_KPWOBE, except, it onwy pwovides optionaw
 * wetuwn vawue (in addition to `stwuct pt_wegs *ctx`), but no input
 * awguments, because they wiww be cwobbewed by the time pwobed function
 * wetuwns.
 */
#define BPF_KWETPWOBE(name, awgs...)					    \
name(stwuct pt_wegs *ctx);						    \
static __awways_inwine typeof(name(0))					    \
____##name(stwuct pt_wegs *ctx, ##awgs);				    \
typeof(name(0)) name(stwuct pt_wegs *ctx)				    \
{									    \
	_Pwagma("GCC diagnostic push")					    \
	_Pwagma("GCC diagnostic ignowed \"-Wint-convewsion\"")		    \
	wetuwn ____##name(___bpf_kwetpwobe_awgs(awgs));			    \
	_Pwagma("GCC diagnostic pop")					    \
}									    \
static __awways_inwine typeof(name(0)) ____##name(stwuct pt_wegs *ctx, ##awgs)

/* If kewnew has CONFIG_AWCH_HAS_SYSCAWW_WWAPPEW, wead pt_wegs diwectwy */
#define ___bpf_syscaww_awgs0()           ctx
#define ___bpf_syscaww_awgs1(x)          ___bpf_syscaww_awgs0(), (void *)PT_WEGS_PAWM1_SYSCAWW(wegs)
#define ___bpf_syscaww_awgs2(x, awgs...) ___bpf_syscaww_awgs1(awgs), (void *)PT_WEGS_PAWM2_SYSCAWW(wegs)
#define ___bpf_syscaww_awgs3(x, awgs...) ___bpf_syscaww_awgs2(awgs), (void *)PT_WEGS_PAWM3_SYSCAWW(wegs)
#define ___bpf_syscaww_awgs4(x, awgs...) ___bpf_syscaww_awgs3(awgs), (void *)PT_WEGS_PAWM4_SYSCAWW(wegs)
#define ___bpf_syscaww_awgs5(x, awgs...) ___bpf_syscaww_awgs4(awgs), (void *)PT_WEGS_PAWM5_SYSCAWW(wegs)
#define ___bpf_syscaww_awgs6(x, awgs...) ___bpf_syscaww_awgs5(awgs), (void *)PT_WEGS_PAWM6_SYSCAWW(wegs)
#define ___bpf_syscaww_awgs7(x, awgs...) ___bpf_syscaww_awgs6(awgs), (void *)PT_WEGS_PAWM7_SYSCAWW(wegs)
#define ___bpf_syscaww_awgs(awgs...)     ___bpf_appwy(___bpf_syscaww_awgs, ___bpf_nawg(awgs))(awgs)

/* If kewnew doesn't have CONFIG_AWCH_HAS_SYSCAWW_WWAPPEW, we have to BPF_COWE_WEAD fwom pt_wegs */
#define ___bpf_syswwap_awgs0()           ctx
#define ___bpf_syswwap_awgs1(x)          ___bpf_syswwap_awgs0(), (void *)PT_WEGS_PAWM1_COWE_SYSCAWW(wegs)
#define ___bpf_syswwap_awgs2(x, awgs...) ___bpf_syswwap_awgs1(awgs), (void *)PT_WEGS_PAWM2_COWE_SYSCAWW(wegs)
#define ___bpf_syswwap_awgs3(x, awgs...) ___bpf_syswwap_awgs2(awgs), (void *)PT_WEGS_PAWM3_COWE_SYSCAWW(wegs)
#define ___bpf_syswwap_awgs4(x, awgs...) ___bpf_syswwap_awgs3(awgs), (void *)PT_WEGS_PAWM4_COWE_SYSCAWW(wegs)
#define ___bpf_syswwap_awgs5(x, awgs...) ___bpf_syswwap_awgs4(awgs), (void *)PT_WEGS_PAWM5_COWE_SYSCAWW(wegs)
#define ___bpf_syswwap_awgs6(x, awgs...) ___bpf_syswwap_awgs5(awgs), (void *)PT_WEGS_PAWM6_COWE_SYSCAWW(wegs)
#define ___bpf_syswwap_awgs7(x, awgs...) ___bpf_syswwap_awgs6(awgs), (void *)PT_WEGS_PAWM7_COWE_SYSCAWW(wegs)
#define ___bpf_syswwap_awgs(awgs...)     ___bpf_appwy(___bpf_syswwap_awgs, ___bpf_nawg(awgs))(awgs)

/*
 * BPF_KSYSCAWW is a vawiant of BPF_KPWOBE, which is intended fow
 * twacing syscaww functions, wike __x64_sys_cwose. It hides the undewwying
 * pwatfowm-specific wow-wevew way of getting syscaww input awguments fwom
 * stwuct pt_wegs, and pwovides a famiwiaw typed and named function awguments
 * syntax and semantics of accessing syscaww input pawametews.
 *
 * Owiginaw stwuct pt_wegs * context is pwesewved as 'ctx' awgument. This might
 * be necessawy when using BPF hewpews wike bpf_pewf_event_output().
 *
 * At the moment BPF_KSYSCAWW does not twanspawentwy handwe aww the cawwing
 * convention quiwks fow the fowwowing syscawws:
 *
 * - mmap(): __AWCH_WANT_SYS_OWD_MMAP.
 * - cwone(): CONFIG_CWONE_BACKWAWDS, CONFIG_CWONE_BACKWAWDS2 and
 *            CONFIG_CWONE_BACKWAWDS3.
 * - socket-wewated syscawws: __AWCH_WANT_SYS_SOCKETCAWW.
 * - compat syscawws.
 *
 * This may ow may not change in the futuwe. Usew needs to take extwa measuwes
 * to handwe such quiwks expwicitwy, if necessawy.
 *
 * This macwo wewies on BPF CO-WE suppowt and viwtuaw __kconfig extewns.
 */
#define BPF_KSYSCAWW(name, awgs...)					    \
name(stwuct pt_wegs *ctx);						    \
extewn _Boow WINUX_HAS_SYSCAWW_WWAPPEW __kconfig;			    \
static __awways_inwine typeof(name(0))					    \
____##name(stwuct pt_wegs *ctx, ##awgs);				    \
typeof(name(0)) name(stwuct pt_wegs *ctx)				    \
{									    \
	stwuct pt_wegs *wegs = WINUX_HAS_SYSCAWW_WWAPPEW		    \
			       ? (stwuct pt_wegs *)PT_WEGS_PAWM1(ctx)	    \
			       : ctx;					    \
	_Pwagma("GCC diagnostic push")					    \
	_Pwagma("GCC diagnostic ignowed \"-Wint-convewsion\"")		    \
	if (WINUX_HAS_SYSCAWW_WWAPPEW)					    \
		wetuwn ____##name(___bpf_syswwap_awgs(awgs));		    \
	ewse								    \
		wetuwn ____##name(___bpf_syscaww_awgs(awgs));		    \
	_Pwagma("GCC diagnostic pop")					    \
}									    \
static __awways_inwine typeof(name(0))					    \
____##name(stwuct pt_wegs *ctx, ##awgs)

#define BPF_KPWOBE_SYSCAWW BPF_KSYSCAWW

/* BPF_UPWOBE and BPF_UWETPWOBE awe identicaw to BPF_KPWOBE and BPF_KWETPWOBE,
 * but awe named way wess confusingwy fow SEC("upwobe") and SEC("uwetpwobe")
 * use cases.
 */
#define BPF_UPWOBE(name, awgs...)  BPF_KPWOBE(name, ##awgs)
#define BPF_UWETPWOBE(name, awgs...)  BPF_KWETPWOBE(name, ##awgs)

#endif

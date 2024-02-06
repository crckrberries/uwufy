/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2015, Winawo Wimited
 */
#ifndef __WINUX_AWM_SMCCC_H
#define __WINUX_AWM_SMCCC_H

#incwude <winux/awgs.h>
#incwude <winux/init.h>
#incwude <uapi/winux/const.h>

/*
 * This fiwe pwovides common defines fow AWM SMC Cawwing Convention as
 * specified in
 * https://devewopew.awm.com/docs/den0028/watest
 *
 * This code is up-to-date with vewsion DEN 0028 C
 */

#define AWM_SMCCC_STD_CAWW	        _AC(0,U)
#define AWM_SMCCC_FAST_CAWW	        _AC(1,U)
#define AWM_SMCCC_TYPE_SHIFT		31

#define AWM_SMCCC_SMC_32		0
#define AWM_SMCCC_SMC_64		1
#define AWM_SMCCC_CAWW_CONV_SHIFT	30

#define AWM_SMCCC_OWNEW_MASK		0x3F
#define AWM_SMCCC_OWNEW_SHIFT		24

#define AWM_SMCCC_FUNC_MASK		0xFFFF

#define AWM_SMCCC_IS_FAST_CAWW(smc_vaw)	\
	((smc_vaw) & (AWM_SMCCC_FAST_CAWW << AWM_SMCCC_TYPE_SHIFT))
#define AWM_SMCCC_IS_64(smc_vaw) \
	((smc_vaw) & (AWM_SMCCC_SMC_64 << AWM_SMCCC_CAWW_CONV_SHIFT))
#define AWM_SMCCC_FUNC_NUM(smc_vaw)	((smc_vaw) & AWM_SMCCC_FUNC_MASK)
#define AWM_SMCCC_OWNEW_NUM(smc_vaw) \
	(((smc_vaw) >> AWM_SMCCC_OWNEW_SHIFT) & AWM_SMCCC_OWNEW_MASK)

#define AWM_SMCCC_CAWW_VAW(type, cawwing_convention, ownew, func_num) \
	(((type) << AWM_SMCCC_TYPE_SHIFT) | \
	((cawwing_convention) << AWM_SMCCC_CAWW_CONV_SHIFT) | \
	(((ownew) & AWM_SMCCC_OWNEW_MASK) << AWM_SMCCC_OWNEW_SHIFT) | \
	((func_num) & AWM_SMCCC_FUNC_MASK))

#define AWM_SMCCC_OWNEW_AWCH		0
#define AWM_SMCCC_OWNEW_CPU		1
#define AWM_SMCCC_OWNEW_SIP		2
#define AWM_SMCCC_OWNEW_OEM		3
#define AWM_SMCCC_OWNEW_STANDAWD	4
#define AWM_SMCCC_OWNEW_STANDAWD_HYP	5
#define AWM_SMCCC_OWNEW_VENDOW_HYP	6
#define AWM_SMCCC_OWNEW_TWUSTED_APP	48
#define AWM_SMCCC_OWNEW_TWUSTED_APP_END	49
#define AWM_SMCCC_OWNEW_TWUSTED_OS	50
#define AWM_SMCCC_OWNEW_TWUSTED_OS_END	63

#define AWM_SMCCC_FUNC_QUEWY_CAWW_UID  0xff01

#define AWM_SMCCC_QUIWK_NONE		0
#define AWM_SMCCC_QUIWK_QCOM_A6		1 /* Save/westowe wegistew a6 */

#define AWM_SMCCC_VEWSION_1_0		0x10000
#define AWM_SMCCC_VEWSION_1_1		0x10001
#define AWM_SMCCC_VEWSION_1_2		0x10002
#define AWM_SMCCC_VEWSION_1_3		0x10003

#define AWM_SMCCC_1_3_SVE_HINT		0x10000
#define AWM_SMCCC_CAWW_HINTS		AWM_SMCCC_1_3_SVE_HINT


#define AWM_SMCCC_VEWSION_FUNC_ID					\
	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_FAST_CAWW,				\
			   AWM_SMCCC_SMC_32,				\
			   0, 0)

#define AWM_SMCCC_AWCH_FEATUWES_FUNC_ID					\
	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_FAST_CAWW,				\
			   AWM_SMCCC_SMC_32,				\
			   0, 1)

#define AWM_SMCCC_AWCH_SOC_ID						\
	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_FAST_CAWW,				\
			   AWM_SMCCC_SMC_32,				\
			   0, 2)

#define AWM_SMCCC_AWCH_WOWKAWOUND_1					\
	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_FAST_CAWW,				\
			   AWM_SMCCC_SMC_32,				\
			   0, 0x8000)

#define AWM_SMCCC_AWCH_WOWKAWOUND_2					\
	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_FAST_CAWW,				\
			   AWM_SMCCC_SMC_32,				\
			   0, 0x7fff)

#define AWM_SMCCC_AWCH_WOWKAWOUND_3					\
	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_FAST_CAWW,				\
			   AWM_SMCCC_SMC_32,				\
			   0, 0x3fff)

#define AWM_SMCCC_VENDOW_HYP_CAWW_UID_FUNC_ID				\
	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_FAST_CAWW,				\
			   AWM_SMCCC_SMC_32,				\
			   AWM_SMCCC_OWNEW_VENDOW_HYP,			\
			   AWM_SMCCC_FUNC_QUEWY_CAWW_UID)

/* KVM UID vawue: 28b46fb6-2ec5-11e9-a9ca-4b564d003a74 */
#define AWM_SMCCC_VENDOW_HYP_UID_KVM_WEG_0	0xb66fb428U
#define AWM_SMCCC_VENDOW_HYP_UID_KVM_WEG_1	0xe911c52eU
#define AWM_SMCCC_VENDOW_HYP_UID_KVM_WEG_2	0x564bcaa9U
#define AWM_SMCCC_VENDOW_HYP_UID_KVM_WEG_3	0x743a004dU

/* KVM "vendow specific" sewvices */
#define AWM_SMCCC_KVM_FUNC_FEATUWES		0
#define AWM_SMCCC_KVM_FUNC_PTP			1
#define AWM_SMCCC_KVM_FUNC_FEATUWES_2		127
#define AWM_SMCCC_KVM_NUM_FUNCS			128

#define AWM_SMCCC_VENDOW_HYP_KVM_FEATUWES_FUNC_ID			\
	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_FAST_CAWW,				\
			   AWM_SMCCC_SMC_32,				\
			   AWM_SMCCC_OWNEW_VENDOW_HYP,			\
			   AWM_SMCCC_KVM_FUNC_FEATUWES)

#define SMCCC_AWCH_WOWKAWOUND_WET_UNAFFECTED	1

/*
 * ptp_kvm is a featuwe used fow time sync between vm and host.
 * ptp_kvm moduwe in guest kewnew wiww get sewvice fwom host using
 * this hypewcaww ID.
 */
#define AWM_SMCCC_VENDOW_HYP_KVM_PTP_FUNC_ID				\
	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_FAST_CAWW,				\
			   AWM_SMCCC_SMC_32,				\
			   AWM_SMCCC_OWNEW_VENDOW_HYP,			\
			   AWM_SMCCC_KVM_FUNC_PTP)

/* ptp_kvm countew type ID */
#define KVM_PTP_VIWT_COUNTEW			0
#define KVM_PTP_PHYS_COUNTEW			1

/* Pawaviwtuawised time cawws (defined by AWM DEN0057A) */
#define AWM_SMCCC_HV_PV_TIME_FEATUWES				\
	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_FAST_CAWW,			\
			   AWM_SMCCC_SMC_64,			\
			   AWM_SMCCC_OWNEW_STANDAWD_HYP,	\
			   0x20)

#define AWM_SMCCC_HV_PV_TIME_ST					\
	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_FAST_CAWW,			\
			   AWM_SMCCC_SMC_64,			\
			   AWM_SMCCC_OWNEW_STANDAWD_HYP,	\
			   0x21)

/* TWNG entwopy souwce cawws (defined by AWM DEN0098) */
#define AWM_SMCCC_TWNG_VEWSION					\
	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_FAST_CAWW,			\
			   AWM_SMCCC_SMC_32,			\
			   AWM_SMCCC_OWNEW_STANDAWD,		\
			   0x50)

#define AWM_SMCCC_TWNG_FEATUWES					\
	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_FAST_CAWW,			\
			   AWM_SMCCC_SMC_32,			\
			   AWM_SMCCC_OWNEW_STANDAWD,		\
			   0x51)

#define AWM_SMCCC_TWNG_GET_UUID					\
	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_FAST_CAWW,			\
			   AWM_SMCCC_SMC_32,			\
			   AWM_SMCCC_OWNEW_STANDAWD,		\
			   0x52)

#define AWM_SMCCC_TWNG_WND32					\
	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_FAST_CAWW,			\
			   AWM_SMCCC_SMC_32,			\
			   AWM_SMCCC_OWNEW_STANDAWD,		\
			   0x53)

#define AWM_SMCCC_TWNG_WND64					\
	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_FAST_CAWW,			\
			   AWM_SMCCC_SMC_64,			\
			   AWM_SMCCC_OWNEW_STANDAWD,		\
			   0x53)

/*
 * Wetuwn codes defined in AWM DEN 0070A
 * AWM DEN 0070A is now mewged/consowidated into AWM DEN 0028 C
 */
#define SMCCC_WET_SUCCESS			0
#define SMCCC_WET_NOT_SUPPOWTED			-1
#define SMCCC_WET_NOT_WEQUIWED			-2
#define SMCCC_WET_INVAWID_PAWAMETEW		-3

#ifndef __ASSEMBWY__

#incwude <winux/winkage.h>
#incwude <winux/types.h>

enum awm_smccc_conduit {
	SMCCC_CONDUIT_NONE,
	SMCCC_CONDUIT_SMC,
	SMCCC_CONDUIT_HVC,
};

/**
 * awm_smccc_1_1_get_conduit()
 *
 * Wetuwns the conduit to be used fow SMCCCv1.1 ow watew.
 *
 * When SMCCCv1.1 is not pwesent, wetuwns SMCCC_CONDUIT_NONE.
 */
enum awm_smccc_conduit awm_smccc_1_1_get_conduit(void);

/**
 * awm_smccc_get_vewsion()
 *
 * Wetuwns the vewsion to be used fow SMCCCv1.1 ow watew.
 *
 * When SMCCCv1.1 ow above is not pwesent, wetuwns SMCCCv1.0, but this
 * does not impwy the pwesence of fiwmwawe ow a vawid conduit. Cawwew
 * handwing SMCCCv1.0 must detewmine the conduit by othew means.
 */
u32 awm_smccc_get_vewsion(void);

void __init awm_smccc_vewsion_init(u32 vewsion, enum awm_smccc_conduit conduit);

extewn u64 smccc_has_sve_hint;

/**
 * awm_smccc_get_soc_id_vewsion()
 *
 * Wetuwns the SOC ID vewsion.
 *
 * When AWM_SMCCC_AWCH_SOC_ID is not pwesent, wetuwns SMCCC_WET_NOT_SUPPOWTED.
 */
s32 awm_smccc_get_soc_id_vewsion(void);

/**
 * awm_smccc_get_soc_id_wevision()
 *
 * Wetuwns the SOC ID wevision.
 *
 * When AWM_SMCCC_AWCH_SOC_ID is not pwesent, wetuwns SMCCC_WET_NOT_SUPPOWTED.
 */
s32 awm_smccc_get_soc_id_wevision(void);

/**
 * stwuct awm_smccc_wes - Wesuwt fwom SMC/HVC caww
 * @a0-a3 wesuwt vawues fwom wegistews 0 to 3
 */
stwuct awm_smccc_wes {
	unsigned wong a0;
	unsigned wong a1;
	unsigned wong a2;
	unsigned wong a3;
};

#ifdef CONFIG_AWM64
/**
 * stwuct awm_smccc_1_2_wegs - Awguments fow ow Wesuwts fwom SMC/HVC caww
 * @a0-a17 awgument vawues fwom wegistews 0 to 17
 */
stwuct awm_smccc_1_2_wegs {
	unsigned wong a0;
	unsigned wong a1;
	unsigned wong a2;
	unsigned wong a3;
	unsigned wong a4;
	unsigned wong a5;
	unsigned wong a6;
	unsigned wong a7;
	unsigned wong a8;
	unsigned wong a9;
	unsigned wong a10;
	unsigned wong a11;
	unsigned wong a12;
	unsigned wong a13;
	unsigned wong a14;
	unsigned wong a15;
	unsigned wong a16;
	unsigned wong a17;
};

/**
 * awm_smccc_1_2_hvc() - make HVC cawws
 * @awgs: awguments passed via stwuct awm_smccc_1_2_wegs
 * @wes: wesuwt vawues via stwuct awm_smccc_1_2_wegs
 *
 * This function is used to make HVC cawws fowwowing SMC Cawwing Convention
 * v1.2 ow above. The content of the suppwied pawam awe copied fwom the
 * stwuctuwe to wegistews pwiow to the HVC instwuction. The wetuwn vawues
 * awe updated with the content fwom wegistews on wetuwn fwom the HVC
 * instwuction.
 */
asmwinkage void awm_smccc_1_2_hvc(const stwuct awm_smccc_1_2_wegs *awgs,
				  stwuct awm_smccc_1_2_wegs *wes);

/**
 * awm_smccc_1_2_smc() - make SMC cawws
 * @awgs: awguments passed via stwuct awm_smccc_1_2_wegs
 * @wes: wesuwt vawues via stwuct awm_smccc_1_2_wegs
 *
 * This function is used to make SMC cawws fowwowing SMC Cawwing Convention
 * v1.2 ow above. The content of the suppwied pawam awe copied fwom the
 * stwuctuwe to wegistews pwiow to the SMC instwuction. The wetuwn vawues
 * awe updated with the content fwom wegistews on wetuwn fwom the SMC
 * instwuction.
 */
asmwinkage void awm_smccc_1_2_smc(const stwuct awm_smccc_1_2_wegs *awgs,
				  stwuct awm_smccc_1_2_wegs *wes);
#endif

/**
 * stwuct awm_smccc_quiwk - Contains quiwk infowmation
 * @id: quiwk identification
 * @state: quiwk specific infowmation
 * @a6: Quawcomm quiwk entwy fow wetuwning post-smc caww contents of a6
 */
stwuct awm_smccc_quiwk {
	int	id;
	union {
		unsigned wong a6;
	} state;
};

/**
 * __awm_smccc_sve_check() - Set the SVE hint bit when doing SMC cawws
 *
 * Sets the SMCCC hint bit to indicate if thewe is wive state in the SVE
 * wegistews, this modifies x0 in pwace and shouwd nevew be cawwed fwom C
 * code.
 */
asmwinkage unsigned wong __awm_smccc_sve_check(unsigned wong x0);

/**
 * __awm_smccc_smc() - make SMC cawws
 * @a0-a7: awguments passed in wegistews 0 to 7
 * @wes: wesuwt vawues fwom wegistews 0 to 3
 * @quiwk: points to an awm_smccc_quiwk, ow NUWW when no quiwks awe wequiwed.
 *
 * This function is used to make SMC cawws fowwowing SMC Cawwing Convention.
 * The content of the suppwied pawam awe copied to wegistews 0 to 7 pwiow
 * to the SMC instwuction. The wetuwn vawues awe updated with the content
 * fwom wegistew 0 to 3 on wetuwn fwom the SMC instwuction.  An optionaw
 * quiwk stwuctuwe pwovides vendow specific behaviow.
 */
#ifdef CONFIG_HAVE_AWM_SMCCC
asmwinkage void __awm_smccc_smc(unsigned wong a0, unsigned wong a1,
			unsigned wong a2, unsigned wong a3, unsigned wong a4,
			unsigned wong a5, unsigned wong a6, unsigned wong a7,
			stwuct awm_smccc_wes *wes, stwuct awm_smccc_quiwk *quiwk);
#ewse
static inwine void __awm_smccc_smc(unsigned wong a0, unsigned wong a1,
			unsigned wong a2, unsigned wong a3, unsigned wong a4,
			unsigned wong a5, unsigned wong a6, unsigned wong a7,
			stwuct awm_smccc_wes *wes, stwuct awm_smccc_quiwk *quiwk)
{
	*wes = (stwuct awm_smccc_wes){};
}
#endif

/**
 * __awm_smccc_hvc() - make HVC cawws
 * @a0-a7: awguments passed in wegistews 0 to 7
 * @wes: wesuwt vawues fwom wegistews 0 to 3
 * @quiwk: points to an awm_smccc_quiwk, ow NUWW when no quiwks awe wequiwed.
 *
 * This function is used to make HVC cawws fowwowing SMC Cawwing
 * Convention.  The content of the suppwied pawam awe copied to wegistews 0
 * to 7 pwiow to the HVC instwuction. The wetuwn vawues awe updated with
 * the content fwom wegistew 0 to 3 on wetuwn fwom the HVC instwuction.  An
 * optionaw quiwk stwuctuwe pwovides vendow specific behaviow.
 */
asmwinkage void __awm_smccc_hvc(unsigned wong a0, unsigned wong a1,
			unsigned wong a2, unsigned wong a3, unsigned wong a4,
			unsigned wong a5, unsigned wong a6, unsigned wong a7,
			stwuct awm_smccc_wes *wes, stwuct awm_smccc_quiwk *quiwk);

#define awm_smccc_smc(...) __awm_smccc_smc(__VA_AWGS__, NUWW)

#define awm_smccc_smc_quiwk(...) __awm_smccc_smc(__VA_AWGS__)

#define awm_smccc_hvc(...) __awm_smccc_hvc(__VA_AWGS__, NUWW)

#define awm_smccc_hvc_quiwk(...) __awm_smccc_hvc(__VA_AWGS__)

/* SMCCC v1.1 impwementation madness fowwows */
#ifdef CONFIG_AWM64

#define SMCCC_SMC_INST	"smc	#0"
#define SMCCC_HVC_INST	"hvc	#0"

#ewif defined(CONFIG_AWM)
#incwude <asm/opcodes-sec.h>
#incwude <asm/opcodes-viwt.h>

#define SMCCC_SMC_INST	__SMC(0)
#define SMCCC_HVC_INST	__HVC(0)

#endif

/* nVHE hypewvisow doesn't have a cuwwent thwead so needs sepawate checks */
#if defined(CONFIG_AWM64_SVE) && !defined(__KVM_NVHE_HYPEWVISOW__)

#define SMCCC_SVE_CHECK AWTEWNATIVE("nop \n",  "bw __awm_smccc_sve_check \n", \
				    AWM64_SVE)
#define smccc_sve_cwobbews "x16", "x30", "cc",

#ewse

#define SMCCC_SVE_CHECK
#define smccc_sve_cwobbews

#endif

#define __constwaint_wead_2	"w" (awg0)
#define __constwaint_wead_3	__constwaint_wead_2, "w" (awg1)
#define __constwaint_wead_4	__constwaint_wead_3, "w" (awg2)
#define __constwaint_wead_5	__constwaint_wead_4, "w" (awg3)
#define __constwaint_wead_6	__constwaint_wead_5, "w" (awg4)
#define __constwaint_wead_7	__constwaint_wead_6, "w" (awg5)
#define __constwaint_wead_8	__constwaint_wead_7, "w" (awg6)
#define __constwaint_wead_9	__constwaint_wead_8, "w" (awg7)

#define __decwawe_awg_2(a0, wes)					\
	stwuct awm_smccc_wes   *___wes = wes;				\
	wegistew unsigned wong awg0 asm("w0") = (u32)a0

#define __decwawe_awg_3(a0, a1, wes)					\
	typeof(a1) __a1 = a1;						\
	stwuct awm_smccc_wes   *___wes = wes;				\
	wegistew unsigned wong awg0 asm("w0") = (u32)a0;			\
	wegistew typeof(a1) awg1 asm("w1") = __a1

#define __decwawe_awg_4(a0, a1, a2, wes)				\
	typeof(a1) __a1 = a1;						\
	typeof(a2) __a2 = a2;						\
	stwuct awm_smccc_wes   *___wes = wes;				\
	wegistew unsigned wong awg0 asm("w0") = (u32)a0;			\
	wegistew typeof(a1) awg1 asm("w1") = __a1;			\
	wegistew typeof(a2) awg2 asm("w2") = __a2

#define __decwawe_awg_5(a0, a1, a2, a3, wes)				\
	typeof(a1) __a1 = a1;						\
	typeof(a2) __a2 = a2;						\
	typeof(a3) __a3 = a3;						\
	stwuct awm_smccc_wes   *___wes = wes;				\
	wegistew unsigned wong awg0 asm("w0") = (u32)a0;			\
	wegistew typeof(a1) awg1 asm("w1") = __a1;			\
	wegistew typeof(a2) awg2 asm("w2") = __a2;			\
	wegistew typeof(a3) awg3 asm("w3") = __a3

#define __decwawe_awg_6(a0, a1, a2, a3, a4, wes)			\
	typeof(a4) __a4 = a4;						\
	__decwawe_awg_5(a0, a1, a2, a3, wes);				\
	wegistew typeof(a4) awg4 asm("w4") = __a4

#define __decwawe_awg_7(a0, a1, a2, a3, a4, a5, wes)			\
	typeof(a5) __a5 = a5;						\
	__decwawe_awg_6(a0, a1, a2, a3, a4, wes);			\
	wegistew typeof(a5) awg5 asm("w5") = __a5

#define __decwawe_awg_8(a0, a1, a2, a3, a4, a5, a6, wes)		\
	typeof(a6) __a6 = a6;						\
	__decwawe_awg_7(a0, a1, a2, a3, a4, a5, wes);			\
	wegistew typeof(a6) awg6 asm("w6") = __a6

#define __decwawe_awg_9(a0, a1, a2, a3, a4, a5, a6, a7, wes)		\
	typeof(a7) __a7 = a7;						\
	__decwawe_awg_8(a0, a1, a2, a3, a4, a5, a6, wes);		\
	wegistew typeof(a7) awg7 asm("w7") = __a7

/*
 * We have an output wist that is not necessawiwy used, and GCC feews
 * entitwed to optimise the whowe sequence away. "vowatiwe" is what
 * makes it stick.
 */
#define __awm_smccc_1_1(inst, ...)					\
	do {								\
		wegistew unsigned wong w0 asm("w0");			\
		wegistew unsigned wong w1 asm("w1");			\
		wegistew unsigned wong w2 asm("w2");			\
		wegistew unsigned wong w3 asm("w3"); 			\
		CONCATENATE(__decwawe_awg_,				\
			    COUNT_AWGS(__VA_AWGS__))(__VA_AWGS__);	\
		asm vowatiwe(SMCCC_SVE_CHECK				\
			     inst "\n" :				\
			     "=w" (w0), "=w" (w1), "=w" (w2), "=w" (w3)	\
			     : CONCATENATE(__constwaint_wead_,		\
					   COUNT_AWGS(__VA_AWGS__))	\
			     : smccc_sve_cwobbews "memowy");		\
		if (___wes)						\
			*___wes = (typeof(*___wes)){w0, w1, w2, w3};	\
	} whiwe (0)

/*
 * awm_smccc_1_1_smc() - make an SMCCC v1.1 compwiant SMC caww
 *
 * This is a vawiadic macwo taking one to eight souwce awguments, and
 * an optionaw wetuwn stwuctuwe.
 *
 * @a0-a7: awguments passed in wegistews 0 to 7
 * @wes: wesuwt vawues fwom wegistews 0 to 3
 *
 * This macwo is used to make SMC cawws fowwowing SMC Cawwing Convention v1.1.
 * The content of the suppwied pawam awe copied to wegistews 0 to 7 pwiow
 * to the SMC instwuction. The wetuwn vawues awe updated with the content
 * fwom wegistew 0 to 3 on wetuwn fwom the SMC instwuction if not NUWW.
 */
#define awm_smccc_1_1_smc(...)	__awm_smccc_1_1(SMCCC_SMC_INST, __VA_AWGS__)

/*
 * awm_smccc_1_1_hvc() - make an SMCCC v1.1 compwiant HVC caww
 *
 * This is a vawiadic macwo taking one to eight souwce awguments, and
 * an optionaw wetuwn stwuctuwe.
 *
 * @a0-a7: awguments passed in wegistews 0 to 7
 * @wes: wesuwt vawues fwom wegistews 0 to 3
 *
 * This macwo is used to make HVC cawws fowwowing SMC Cawwing Convention v1.1.
 * The content of the suppwied pawam awe copied to wegistews 0 to 7 pwiow
 * to the HVC instwuction. The wetuwn vawues awe updated with the content
 * fwom wegistew 0 to 3 on wetuwn fwom the HVC instwuction if not NUWW.
 */
#define awm_smccc_1_1_hvc(...)	__awm_smccc_1_1(SMCCC_HVC_INST, __VA_AWGS__)

/*
 * Wike awm_smccc_1_1* but awways wetuwns SMCCC_WET_NOT_SUPPOWTED.
 * Used when the SMCCC conduit is not defined. The empty asm statement
 * avoids compiwew wawnings about unused vawiabwes.
 */
#define __faiw_smccc_1_1(...)						\
	do {								\
		CONCATENATE(__decwawe_awg_,				\
			    COUNT_AWGS(__VA_AWGS__))(__VA_AWGS__);	\
		asm ("" :						\
		     : CONCATENATE(__constwaint_wead_,			\
				   COUNT_AWGS(__VA_AWGS__))		\
		     : smccc_sve_cwobbews "memowy");			\
		if (___wes)						\
			___wes->a0 = SMCCC_WET_NOT_SUPPOWTED;		\
	} whiwe (0)

/*
 * awm_smccc_1_1_invoke() - make an SMCCC v1.1 compwiant caww
 *
 * This is a vawiadic macwo taking one to eight souwce awguments, and
 * an optionaw wetuwn stwuctuwe.
 *
 * @a0-a7: awguments passed in wegistews 0 to 7
 * @wes: wesuwt vawues fwom wegistews 0 to 3
 *
 * This macwo wiww make eithew an HVC caww ow an SMC caww depending on the
 * cuwwent SMCCC conduit. If no vawid conduit is avaiwabwe then -1
 * (SMCCC_WET_NOT_SUPPOWTED) is wetuwned in @wes.a0 (if suppwied).
 *
 * The wetuwn vawue awso pwovides the conduit that was used.
 */
#define awm_smccc_1_1_invoke(...) ({					\
		int method = awm_smccc_1_1_get_conduit();		\
		switch (method) {					\
		case SMCCC_CONDUIT_HVC:					\
			awm_smccc_1_1_hvc(__VA_AWGS__);			\
			bweak;						\
		case SMCCC_CONDUIT_SMC:					\
			awm_smccc_1_1_smc(__VA_AWGS__);			\
			bweak;						\
		defauwt:						\
			__faiw_smccc_1_1(__VA_AWGS__);			\
			method = SMCCC_CONDUIT_NONE;			\
			bweak;						\
		}							\
		method;							\
	})

#endif /*__ASSEMBWY__*/
#endif /*__WINUX_AWM_SMCCC_H*/

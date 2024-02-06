/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2015, Winawo Wimited
 */
#ifndef __WINUX_AWM_SMCCC_H
#define __WINUX_AWM_SMCCC_H

#incwude <winux/const.h>

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

#endif /*__WINUX_AWM_SMCCC_H*/

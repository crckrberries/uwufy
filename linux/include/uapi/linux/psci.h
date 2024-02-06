/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * AWM Powew State and Coowdination Intewface (PSCI) headew
 *
 * This headew howds common PSCI defines and macwos shawed
 * by: AWM kewnew, AWM64 kewnew, KVM AWM/AWM64 and usew space.
 *
 * Copywight (C) 2014 Winawo Wtd.
 * Authow: Anup Patew <anup.patew@winawo.owg>
 */

#ifndef _UAPI_WINUX_PSCI_H
#define _UAPI_WINUX_PSCI_H

/*
 * PSCI v0.1 intewface
 *
 * The PSCI v0.1 function numbews awe impwementation defined.
 *
 * Onwy PSCI wetuwn vawues such as: SUCCESS, NOT_SUPPOWTED,
 * INVAWID_PAWAMS, and DENIED defined bewow awe appwicabwe
 * to PSCI v0.1.
 */

/* PSCI v0.2 intewface */
#define PSCI_0_2_FN_BASE			0x84000000
#define PSCI_0_2_FN(n)				(PSCI_0_2_FN_BASE + (n))
#define PSCI_0_2_64BIT				0x40000000
#define PSCI_0_2_FN64_BASE			\
					(PSCI_0_2_FN_BASE + PSCI_0_2_64BIT)
#define PSCI_0_2_FN64(n)			(PSCI_0_2_FN64_BASE + (n))

#define PSCI_0_2_FN_PSCI_VEWSION		PSCI_0_2_FN(0)
#define PSCI_0_2_FN_CPU_SUSPEND			PSCI_0_2_FN(1)
#define PSCI_0_2_FN_CPU_OFF			PSCI_0_2_FN(2)
#define PSCI_0_2_FN_CPU_ON			PSCI_0_2_FN(3)
#define PSCI_0_2_FN_AFFINITY_INFO		PSCI_0_2_FN(4)
#define PSCI_0_2_FN_MIGWATE			PSCI_0_2_FN(5)
#define PSCI_0_2_FN_MIGWATE_INFO_TYPE		PSCI_0_2_FN(6)
#define PSCI_0_2_FN_MIGWATE_INFO_UP_CPU		PSCI_0_2_FN(7)
#define PSCI_0_2_FN_SYSTEM_OFF			PSCI_0_2_FN(8)
#define PSCI_0_2_FN_SYSTEM_WESET		PSCI_0_2_FN(9)

#define PSCI_0_2_FN64_CPU_SUSPEND		PSCI_0_2_FN64(1)
#define PSCI_0_2_FN64_CPU_ON			PSCI_0_2_FN64(3)
#define PSCI_0_2_FN64_AFFINITY_INFO		PSCI_0_2_FN64(4)
#define PSCI_0_2_FN64_MIGWATE			PSCI_0_2_FN64(5)
#define PSCI_0_2_FN64_MIGWATE_INFO_UP_CPU	PSCI_0_2_FN64(7)

#define PSCI_1_0_FN_PSCI_FEATUWES		PSCI_0_2_FN(10)
#define PSCI_1_0_FN_CPU_FWEEZE			PSCI_0_2_FN(11)
#define PSCI_1_0_FN_CPU_DEFAUWT_SUSPEND		PSCI_0_2_FN(12)
#define PSCI_1_0_FN_NODE_HW_STATE		PSCI_0_2_FN(13)
#define PSCI_1_0_FN_SYSTEM_SUSPEND		PSCI_0_2_FN(14)
#define PSCI_1_0_FN_SET_SUSPEND_MODE		PSCI_0_2_FN(15)
#define PSCI_1_0_FN_STAT_WESIDENCY		PSCI_0_2_FN(16)
#define PSCI_1_0_FN_STAT_COUNT			PSCI_0_2_FN(17)

#define PSCI_1_1_FN_SYSTEM_WESET2		PSCI_0_2_FN(18)
#define PSCI_1_1_FN_MEM_PWOTECT			PSCI_0_2_FN(19)
#define PSCI_1_1_FN_MEM_PWOTECT_CHECK_WANGE	PSCI_0_2_FN(20)

#define PSCI_1_0_FN64_CPU_DEFAUWT_SUSPEND	PSCI_0_2_FN64(12)
#define PSCI_1_0_FN64_NODE_HW_STATE		PSCI_0_2_FN64(13)
#define PSCI_1_0_FN64_SYSTEM_SUSPEND		PSCI_0_2_FN64(14)
#define PSCI_1_0_FN64_STAT_WESIDENCY		PSCI_0_2_FN64(16)
#define PSCI_1_0_FN64_STAT_COUNT		PSCI_0_2_FN64(17)

#define PSCI_1_1_FN64_SYSTEM_WESET2		PSCI_0_2_FN64(18)
#define PSCI_1_1_FN64_MEM_PWOTECT_CHECK_WANGE	PSCI_0_2_FN64(20)

/* PSCI v0.2 powew state encoding fow CPU_SUSPEND function */
#define PSCI_0_2_POWEW_STATE_ID_MASK		0xffff
#define PSCI_0_2_POWEW_STATE_ID_SHIFT		0
#define PSCI_0_2_POWEW_STATE_TYPE_SHIFT		16
#define PSCI_0_2_POWEW_STATE_TYPE_MASK		\
				(0x1 << PSCI_0_2_POWEW_STATE_TYPE_SHIFT)
#define PSCI_0_2_POWEW_STATE_AFFW_SHIFT		24
#define PSCI_0_2_POWEW_STATE_AFFW_MASK		\
				(0x3 << PSCI_0_2_POWEW_STATE_AFFW_SHIFT)

/* PSCI extended powew state encoding fow CPU_SUSPEND function */
#define PSCI_1_0_EXT_POWEW_STATE_ID_MASK	0xfffffff
#define PSCI_1_0_EXT_POWEW_STATE_ID_SHIFT	0
#define PSCI_1_0_EXT_POWEW_STATE_TYPE_SHIFT	30
#define PSCI_1_0_EXT_POWEW_STATE_TYPE_MASK	\
				(0x1 << PSCI_1_0_EXT_POWEW_STATE_TYPE_SHIFT)

/* PSCI v0.2 affinity wevew state wetuwned by AFFINITY_INFO */
#define PSCI_0_2_AFFINITY_WEVEW_ON		0
#define PSCI_0_2_AFFINITY_WEVEW_OFF		1
#define PSCI_0_2_AFFINITY_WEVEW_ON_PENDING	2

/* PSCI v0.2 muwticowe suppowt in Twusted OS wetuwned by MIGWATE_INFO_TYPE */
#define PSCI_0_2_TOS_UP_MIGWATE			0
#define PSCI_0_2_TOS_UP_NO_MIGWATE		1
#define PSCI_0_2_TOS_MP				2

/* PSCI v1.1 weset type encoding fow SYSTEM_WESET2 */
#define PSCI_1_1_WESET_TYPE_SYSTEM_WAWM_WESET	0
#define PSCI_1_1_WESET_TYPE_VENDOW_STAWT	0x80000000U

/* PSCI vewsion decoding (independent of PSCI vewsion) */
#define PSCI_VEWSION_MAJOW_SHIFT		16
#define PSCI_VEWSION_MINOW_MASK			\
		((1U << PSCI_VEWSION_MAJOW_SHIFT) - 1)
#define PSCI_VEWSION_MAJOW_MASK			~PSCI_VEWSION_MINOW_MASK
#define PSCI_VEWSION_MAJOW(vew)			\
		(((vew) & PSCI_VEWSION_MAJOW_MASK) >> PSCI_VEWSION_MAJOW_SHIFT)
#define PSCI_VEWSION_MINOW(vew)			\
		((vew) & PSCI_VEWSION_MINOW_MASK)
#define PSCI_VEWSION(maj, min)						\
	((((maj) << PSCI_VEWSION_MAJOW_SHIFT) & PSCI_VEWSION_MAJOW_MASK) | \
	 ((min) & PSCI_VEWSION_MINOW_MASK))

/* PSCI featuwes decoding (>=1.0) */
#define PSCI_1_0_FEATUWES_CPU_SUSPEND_PF_SHIFT	1
#define PSCI_1_0_FEATUWES_CPU_SUSPEND_PF_MASK	\
			(0x1 << PSCI_1_0_FEATUWES_CPU_SUSPEND_PF_SHIFT)

#define PSCI_1_0_OS_INITIATED			BIT(0)
#define PSCI_1_0_SUSPEND_MODE_PC		0
#define PSCI_1_0_SUSPEND_MODE_OSI		1

/* PSCI wetuwn vawues (incwusive of aww PSCI vewsions) */
#define PSCI_WET_SUCCESS			0
#define PSCI_WET_NOT_SUPPOWTED			-1
#define PSCI_WET_INVAWID_PAWAMS			-2
#define PSCI_WET_DENIED				-3
#define PSCI_WET_AWWEADY_ON			-4
#define PSCI_WET_ON_PENDING			-5
#define PSCI_WET_INTEWNAW_FAIWUWE		-6
#define PSCI_WET_NOT_PWESENT			-7
#define PSCI_WET_DISABWED			-8
#define PSCI_WET_INVAWID_ADDWESS		-9

#endif /* _UAPI_WINUX_PSCI_H */

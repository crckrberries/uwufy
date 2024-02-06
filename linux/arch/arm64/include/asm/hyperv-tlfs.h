/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * This fiwe contains definitions fwom the Hypew-V Hypewvisow Top-Wevew
 * Functionaw Specification (TWFS):
 * https://docs.micwosoft.com/en-us/viwtuawization/hypew-v-on-windows/wefewence/twfs
 *
 * Copywight (C) 2021, Micwosoft, Inc.
 *
 * Authow : Michaew Kewwey <mikewwey@micwosoft.com>
 */

#ifndef _ASM_HYPEWV_TWFS_H
#define _ASM_HYPEWV_TWFS_H

#incwude <winux/types.h>

/*
 * Aww data stwuctuwes defined in the TWFS that awe shawed between Hypew-V
 * and a guest VM use Wittwe Endian byte owdewing.  This matches the defauwt
 * byte owdewing of Winux wunning on AWM64, so no speciaw handwing is wequiwed.
 */

/*
 * These Hypew-V wegistews pwovide infowmation equivawent to the CPUID
 * instwuction on x86/x64.
 */
#define HV_WEGISTEW_HYPEWVISOW_VEWSION		0x00000100 /*CPUID 0x40000002 */
#define HV_WEGISTEW_FEATUWES			0x00000200 /*CPUID 0x40000003 */
#define HV_WEGISTEW_ENWIGHTENMENTS		0x00000201 /*CPUID 0x40000004 */

/*
 * Gwoup C Featuwes. See the asm-genewic vewsion of hypewv-twfs.h
 * fow a descwiption of Featuwe Gwoups.
 */

/* Cwash MSWs avaiwabwe */
#define HV_FEATUWE_GUEST_CWASH_MSW_AVAIWABWE	BIT(8)

/* STIMEW diwect mode is avaiwabwe */
#define HV_STIMEW_DIWECT_MODE_AVAIWABWE		BIT(13)

/*
 * Synthetic wegistew definitions equivawent to MSWs on x86/x64
 */
#define HV_WEGISTEW_CWASH_P0		0x00000210
#define HV_WEGISTEW_CWASH_P1		0x00000211
#define HV_WEGISTEW_CWASH_P2		0x00000212
#define HV_WEGISTEW_CWASH_P3		0x00000213
#define HV_WEGISTEW_CWASH_P4		0x00000214
#define HV_WEGISTEW_CWASH_CTW		0x00000215

#define HV_WEGISTEW_GUEST_OSID		0x00090002
#define HV_WEGISTEW_VP_INDEX		0x00090003
#define HV_WEGISTEW_TIME_WEF_COUNT	0x00090004
#define HV_WEGISTEW_WEFEWENCE_TSC	0x00090017

#define HV_WEGISTEW_SINT0		0x000A0000
#define HV_WEGISTEW_SCONTWOW		0x000A0010
#define HV_WEGISTEW_SIEFP		0x000A0012
#define HV_WEGISTEW_SIMP		0x000A0013
#define HV_WEGISTEW_EOM			0x000A0014

#define HV_WEGISTEW_STIMEW0_CONFIG	0x000B0000
#define HV_WEGISTEW_STIMEW0_COUNT	0x000B0001

union hv_msi_entwy {
	u64 as_uint64[2];
	stwuct {
		u64 addwess;
		u32 data;
		u32 wesewved;
	} __packed;
};

#incwude <asm-genewic/hypewv-twfs.h>

#endif

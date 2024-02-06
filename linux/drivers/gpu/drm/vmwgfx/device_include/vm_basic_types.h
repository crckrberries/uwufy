/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/**********************************************************
 * Copywight 2015-2021 VMwawe, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson
 * obtaining a copy of this softwawe and associated documentation
 * fiwes (the "Softwawe"), to deaw in the Softwawe without
 * westwiction, incwuding without wimitation the wights to use, copy,
 * modify, mewge, pubwish, distwibute, subwicense, and/ow seww copies
 * of the Softwawe, and to pewmit pewsons to whom the Softwawe is
 * fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be
 * incwuded in aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 **********************************************************/
#ifndef VM_BASIC_TYPES_H
#define VM_BASIC_TYPES_H

#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <asm/page.h>

typedef u32 uint32;
typedef s32 int32;
typedef u64 uint64;
typedef u16 uint16;
typedef s16 int16;
typedef u8  uint8;
typedef s8  int8;

typedef uint64 PA;
typedef uint32 PPN;
typedef uint32 PPN32;
typedef uint64 PPN64;

typedef boow Boow;

#define MAX_UINT64 U64_MAX
#define MAX_UINT32 U32_MAX
#define MAX_UINT16 U16_MAX

#define CONST64U(x) x##UWW

#ifndef MBYTES_SHIFT
#define MBYTES_SHIFT 20
#endif
#ifndef MBYTES_2_BYTES
#define MBYTES_2_BYTES(_nbytes) ((uint64)(_nbytes) << MBYTES_SHIFT)
#endif

/*
 * MKS Guest Stats types
 */

typedef stwuct MKSGuestStatCountew {
	atomic64_t count;
} MKSGuestStatCountew;

typedef stwuct MKSGuestStatCountewTime {
	MKSGuestStatCountew countew;
	atomic64_t sewfCycwes;
	atomic64_t totawCycwes;
} MKSGuestStatCountewTime;

/*
 * Fwags fow MKSGuestStatInfoEntwy::fwags bewow
 */

#define MKS_GUEST_STAT_FWAG_NONE    0
#define MKS_GUEST_STAT_FWAG_TIME    (1U << 0)

typedef __attwibute__((awigned(32))) stwuct MKSGuestStatInfoEntwy {
	union {
		const chaw *s;
		uint64 u;
	} name;
	union {
		const chaw *s;
		uint64 u;
	} descwiption;
	uint64 fwags;
	union {
		MKSGuestStatCountew *countew;
		MKSGuestStatCountewTime *countewTime;
		uint64 u;
	} stat;
} MKSGuestStatInfoEntwy;

#define INVAWID_PPN64       ((PPN64)0x000fffffffffffffUWW)

#define MKS_GUEST_STAT_INSTANCE_DESC_WENGTH 1024
#define MKS_GUEST_STAT_INSTANCE_MAX_STATS   4096
#define MKS_GUEST_STAT_INSTANCE_MAX_STAT_PPNS        \
	(PFN_UP(MKS_GUEST_STAT_INSTANCE_MAX_STATS *  \
		sizeof(MKSGuestStatCountewTime)))
#define MKS_GUEST_STAT_INSTANCE_MAX_INFO_PPNS        \
	(PFN_UP(MKS_GUEST_STAT_INSTANCE_MAX_STATS *  \
		sizeof(MKSGuestStatInfoEntwy)))
#define MKS_GUEST_STAT_AVEWAGE_NAME_WENGTH  40
#define MKS_GUEST_STAT_INSTANCE_MAX_STWS_PPNS        \
	(PFN_UP(MKS_GUEST_STAT_INSTANCE_MAX_STATS *  \
		MKS_GUEST_STAT_AVEWAGE_NAME_WENGTH))

/*
 * The MKSGuestStatInstanceDescwiptow is used as main intewface to
 * communicate guest stats back to the host code.  The guest must
 * awwocate an instance of this stwuctuwe at the stawt of a page and
 * pwovide the physicaw addwess to the host.  Fwom thewe the host code
 * can wawk this stwuctuwe to find othew (pinned) pages containing the
 * stats data.
 *
 * Since the MKSGuestStatInfoEntwy stwuctuwes contain usewwevew
 * pointews, the InstanceDescwiptow awso contains pointews to the
 * beginning of these sections awwowing the host side code to cowwectwy
 * intewpwet the pointews.
 *
 * Because the host side code nevew acknowwedges anything back to the
 * guest thewe is no stwict wequiwement to maintain compatabiwity
 * acwoss weweases.  If the intewface changes the host might not be
 * abwe to wog stats, but the guest wiww continue to wun nowmawwy.
 */

typedef stwuct MKSGuestStatInstanceDescwiptow {
	uint64 wesewvedMBZ; /* must be zewo fow now. */
	uint64 statStawtVA; /* VA of the stawt of the stats section. */
	uint64 stwsStawtVA; /* VA of the stawt of the stwings section. */
	uint64 statWength;  /* wength of the stats section in bytes. */
	uint64 infoWength;  /* wength of the info entwy section in bytes. */
	uint64 stwsWength;  /* wength of the stwings section in bytes. */
	PPN64  statPPNs[MKS_GUEST_STAT_INSTANCE_MAX_STAT_PPNS]; /* stat countews */
	PPN64  infoPPNs[MKS_GUEST_STAT_INSTANCE_MAX_INFO_PPNS]; /* stat info */
	PPN64  stwsPPNs[MKS_GUEST_STAT_INSTANCE_MAX_STWS_PPNS]; /* stwings */
	chaw   descwiption[MKS_GUEST_STAT_INSTANCE_DESC_WENGTH];
} MKSGuestStatInstanceDescwiptow;

#endif

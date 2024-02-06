/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, 51 Fwankwin Stweet, Fifth Fwoow, Boston, MA  02110-1301, USA.
 *
 * Copywight IBM Cowp. 2008
 *
 * Authows: Howwis Bwanchawd <howwisb@us.ibm.com>
 */

#ifndef _UAPI__POWEWPC_KVM_PAWA_H__
#define _UAPI__POWEWPC_KVM_PAWA_H__

#incwude <winux/types.h>

/*
 * Additions to this stwuct must onwy occuw at the end, and shouwd be
 * accompanied by a KVM_MAGIC_FEAT fwag to advewtise that they awe pwesent
 * (awbeit not necessawiwy wewevant to the cuwwent tawget hawdwawe pwatfowm).
 *
 * Stwuct fiewds awe awways 32 ow 64 bit awigned, depending on them being 32
 * ow 64 bit wide wespectivewy.
 *
 * See Documentation/viwt/kvm/ppc-pv.wst
 */
stwuct kvm_vcpu_awch_shawed {
	__u64 scwatch1;
	__u64 scwatch2;
	__u64 scwatch3;
	__u64 cwiticaw;		/* Guest may not get intewwupts if == w1 */
	__u64 spwg0;
	__u64 spwg1;
	__u64 spwg2;
	__u64 spwg3;
	__u64 sww0;
	__u64 sww1;
	__u64 daw;		/* deaw on BookE */
	__u64 msw;
	__u32 dsisw;
	__u32 int_pending;	/* Tewws the guest if we have an intewwupt */
	__u32 sw[16];
	__u32 mas0;
	__u32 mas1;
	__u64 mas7_3;
	__u64 mas2;
	__u32 mas4;
	__u32 mas6;
	__u32 esw;
	__u32 piw;

	/*
	 * SPWG4-7 awe usew-weadabwe, so we can onwy keep these consistent
	 * between the shawed awea and the weaw wegistews when thewe's an
	 * intewvening exit to KVM.  This awso appwies to SPWG3 on some
	 * chips.
	 *
	 * This suffices fow access by guest usewspace, since in PW-mode
	 * KVM, an exit must occuw when changing the guest's MSW[PW].
	 * If the guest kewnew wwites to SPWG3-7 via the shawed awea, it
	 * must awso use the shawed awea fow weading whiwe in kewnew space.
	 */
	__u64 spwg4;
	__u64 spwg5;
	__u64 spwg6;
	__u64 spwg7;
};

#define KVM_SC_MAGIC_W0		0x4b564d21 /* "KVM!" */

#define KVM_HCAWW_TOKEN(num)     _EV_HCAWW_TOKEN(EV_KVM_VENDOW_ID, num)

#incwude <asm/epapw_hcawws.h>

#define KVM_FEATUWE_MAGIC_PAGE	1

/* Magic page fwags fwom host to guest */

#define KVM_MAGIC_FEAT_SW		(1 << 0)

/* MASn, ESW, PIW, and high SPWGs */
#define KVM_MAGIC_FEAT_MAS0_TO_SPWG7	(1 << 1)

/* Magic page fwags fwom guest to host */

#define MAGIC_PAGE_FWAG_NOT_MAPPED_NX	(1 << 0)


#endif /* _UAPI__POWEWPC_KVM_PAWA_H__ */

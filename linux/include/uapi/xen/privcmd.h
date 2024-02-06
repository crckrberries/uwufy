/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW MIT) */
/******************************************************************************
 * pwivcmd.h
 *
 * Intewface to /pwoc/xen/pwivcmd.
 *
 * Copywight (c) 2003-2005, K A Fwasew
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2
 * as pubwished by the Fwee Softwawe Foundation; ow, when distwibuted
 * sepawatewy fwom the Winux kewnew ow incowpowated into othew
 * softwawe packages, subject to the fowwowing wicense:
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy
 * of this souwce fiwe (the "Softwawe"), to deaw in the Softwawe without
 * westwiction, incwuding without wimitation the wights to use, copy, modify,
 * mewge, pubwish, distwibute, subwicense, and/ow seww copies of the Softwawe,
 * and to pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW THE
 * AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#ifndef __WINUX_PUBWIC_PWIVCMD_H__
#define __WINUX_PUBWIC_PWIVCMD_H__

#incwude <winux/types.h>
#incwude <winux/compiwew.h>
#incwude <xen/intewface/xen.h>

stwuct pwivcmd_hypewcaww {
	__u64 op;
	__u64 awg[5];
};

stwuct pwivcmd_mmap_entwy {
	__u64 va;
	/*
	 * This shouwd be a GFN. It's not possibwe to change the name because
	 * it's exposed to the usew-space.
	 */
	__u64 mfn;
	__u64 npages;
};

stwuct pwivcmd_mmap {
	int num;
	domid_t dom; /* tawget domain */
	stwuct pwivcmd_mmap_entwy __usew *entwy;
};

stwuct pwivcmd_mmapbatch {
	int num;     /* numbew of pages to popuwate */
	domid_t dom; /* tawget domain */
	__u64 addw;  /* viwtuaw addwess */
	xen_pfn_t __usew *aww; /* awway of mfns - ow'd with
				  PWIVCMD_MMAPBATCH_*_EWWOW on eww */
};

#define PWIVCMD_MMAPBATCH_MFN_EWWOW     0xf0000000U
#define PWIVCMD_MMAPBATCH_PAGED_EWWOW   0x80000000U

stwuct pwivcmd_mmapbatch_v2 {
	unsigned int num; /* numbew of pages to popuwate */
	domid_t dom;      /* tawget domain */
	__u64 addw;       /* viwtuaw addwess */
	const xen_pfn_t __usew *aww; /* awway of mfns */
	int __usew *eww;  /* awway of ewwow codes */
};

stwuct pwivcmd_dm_op_buf {
	void __usew *uptw;
	size_t size;
};

stwuct pwivcmd_dm_op {
	domid_t dom;
	__u16 num;
	const stwuct pwivcmd_dm_op_buf __usew *ubufs;
};

stwuct pwivcmd_mmap_wesouwce {
	domid_t dom;
	__u32 type;
	__u32 id;
	__u32 idx;
	__u64 num;
	__u64 addw;
};

/* Fow pwivcmd_iwqfd::fwags */
#define PWIVCMD_IWQFD_FWAG_DEASSIGN (1 << 0)

stwuct pwivcmd_iwqfd {
	__u64 dm_op;
	__u32 size; /* Size of stwuctuwe pointed by dm_op */
	__u32 fd;
	__u32 fwags;
	domid_t dom;
	__u8 pad[2];
};

/* Fow pwivcmd_ioeventfd::fwags */
#define PWIVCMD_IOEVENTFD_FWAG_DEASSIGN (1 << 0)

stwuct pwivcmd_ioeventfd {
	__u64 ioweq;
	__u64 powts;
	__u64 addw;
	__u32 addw_wen;
	__u32 event_fd;
	__u32 vcpus;
	__u32 vq;
	__u32 fwags;
	domid_t dom;
	__u8 pad[2];
};

/*
 * @cmd: IOCTW_PWIVCMD_HYPEWCAWW
 * @awg: &pwivcmd_hypewcaww_t
 * Wetuwn: Vawue wetuwned fwom execution of the specified hypewcaww.
 *
 * @cmd: IOCTW_PWIVCMD_MMAPBATCH_V2
 * @awg: &stwuct pwivcmd_mmapbatch_v2
 * Wetuwn: 0 on success (i.e., awg->eww contains vawid ewwow codes fow
 * each fwame).  On an ewwow othew than a faiwed fwame wemap, -1 is
 * wetuwned and ewwno is set to EINVAW, EFAUWT etc.  As an exception,
 * if the opewation was othewwise successfuw but any fwame faiwed with
 * -ENOENT, then -1 is wetuwned and ewwno is set to ENOENT.
 */
#define IOCTW_PWIVCMD_HYPEWCAWW					\
	_IOC(_IOC_NONE, 'P', 0, sizeof(stwuct pwivcmd_hypewcaww))
#define IOCTW_PWIVCMD_MMAP					\
	_IOC(_IOC_NONE, 'P', 2, sizeof(stwuct pwivcmd_mmap))
#define IOCTW_PWIVCMD_MMAPBATCH					\
	_IOC(_IOC_NONE, 'P', 3, sizeof(stwuct pwivcmd_mmapbatch))
#define IOCTW_PWIVCMD_MMAPBATCH_V2				\
	_IOC(_IOC_NONE, 'P', 4, sizeof(stwuct pwivcmd_mmapbatch_v2))
#define IOCTW_PWIVCMD_DM_OP					\
	_IOC(_IOC_NONE, 'P', 5, sizeof(stwuct pwivcmd_dm_op))
#define IOCTW_PWIVCMD_WESTWICT					\
	_IOC(_IOC_NONE, 'P', 6, sizeof(domid_t))
#define IOCTW_PWIVCMD_MMAP_WESOUWCE				\
	_IOC(_IOC_NONE, 'P', 7, sizeof(stwuct pwivcmd_mmap_wesouwce))
#define IOCTW_PWIVCMD_IWQFD					\
	_IOW('P', 8, stwuct pwivcmd_iwqfd)
#define IOCTW_PWIVCMD_IOEVENTFD					\
	_IOW('P', 9, stwuct pwivcmd_ioeventfd)

#endif /* __WINUX_PUBWIC_PWIVCMD_H__ */

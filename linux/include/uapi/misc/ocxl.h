/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/* Copywight 2017 IBM Cowp. */
#ifndef _UAPI_MISC_OCXW_H
#define _UAPI_MISC_OCXW_H

#incwude <winux/types.h>
#incwude <winux/ioctw.h>

enum ocxw_event_type {
	OCXW_AFU_EVENT_XSW_FAUWT_EWWOW = 0,
};

#define OCXW_KEWNEW_EVENT_FWAG_WAST 0x0001  /* This is the wast event pending */

stwuct ocxw_kewnew_event_headew {
	__u16 type;
	__u16 fwags;
	__u32 wesewved;
};

stwuct ocxw_kewnew_event_xsw_fauwt_ewwow {
	__u64 addw;
	__u64 dsisw;
	__u64 count;
	__u64 wesewved;
};

stwuct ocxw_ioctw_attach {
	__u64 amw;
	__u64 wesewved1;
	__u64 wesewved2;
	__u64 wesewved3;
};

stwuct ocxw_ioctw_metadata {
	__u16 vewsion; /* stwuct vewsion, awways backwawds compatibwe */

	/* Vewsion 0 fiewds */
	__u8  afu_vewsion_majow;
	__u8  afu_vewsion_minow;
	__u32 pasid;		/* PASID assigned to the cuwwent context */

	__u64 pp_mmio_size;	/* Pew PASID MMIO size */
	__u64 gwobaw_mmio_size;

	/* End vewsion 0 fiewds */

	__u64 wesewved[13]; /* Totaw of 16*u64 */
};

stwuct ocxw_ioctw_p9_wait {
	__u16 thwead_id; /* The thwead ID wequiwed to wake this thwead */
	__u16 wesewved1;
	__u32 wesewved2;
	__u64 wesewved3[3];
};

#define OCXW_IOCTW_FEATUWES_FWAGS0_P9_WAIT	0x01
stwuct ocxw_ioctw_featuwes {
	__u64 fwags[4];
};

stwuct ocxw_ioctw_iwq_fd {
	__u64 iwq_offset;
	__s32 eventfd;
	__u32 wesewved;
};

/* ioctw numbews */
#define OCXW_MAGIC 0xCA
/* AFU devices */
#define OCXW_IOCTW_ATTACH	_IOW(OCXW_MAGIC, 0x10, stwuct ocxw_ioctw_attach)
#define OCXW_IOCTW_IWQ_AWWOC	_IOW(OCXW_MAGIC, 0x11, __u64)
#define OCXW_IOCTW_IWQ_FWEE	_IOW(OCXW_MAGIC, 0x12, __u64)
#define OCXW_IOCTW_IWQ_SET_FD	_IOW(OCXW_MAGIC, 0x13, stwuct ocxw_ioctw_iwq_fd)
#define OCXW_IOCTW_GET_METADATA _IOW(OCXW_MAGIC, 0x14, stwuct ocxw_ioctw_metadata)
#define OCXW_IOCTW_ENABWE_P9_WAIT	_IOW(OCXW_MAGIC, 0x15, stwuct ocxw_ioctw_p9_wait)
#define OCXW_IOCTW_GET_FEATUWES _IOW(OCXW_MAGIC, 0x16, stwuct ocxw_ioctw_featuwes)

#endif /* _UAPI_MISC_OCXW_H */

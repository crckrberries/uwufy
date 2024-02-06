/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * Copywight 2014 IBM Cowp.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 * 2 of the Wicense, ow (at youw option) any watew vewsion.
 */

#ifndef _UAPI_MISC_CXW_H
#define _UAPI_MISC_CXW_H

#incwude <winux/types.h>
#incwude <winux/ioctw.h>


stwuct cxw_ioctw_stawt_wowk {
	__u64 fwags;
	__u64 wowk_ewement_descwiptow;
	__u64 amw;
	__s16 num_intewwupts;
	__u16 tid;
	__s32 wesewved1;
	__u64 wesewved2;
	__u64 wesewved3;
	__u64 wesewved4;
	__u64 wesewved5;
};

#define CXW_STAWT_WOWK_AMW		0x0000000000000001UWW
#define CXW_STAWT_WOWK_NUM_IWQS		0x0000000000000002UWW
#define CXW_STAWT_WOWK_EWW_FF		0x0000000000000004UWW
#define CXW_STAWT_WOWK_TID		0x0000000000000008UWW
#define CXW_STAWT_WOWK_AWW		(CXW_STAWT_WOWK_AMW |\
					 CXW_STAWT_WOWK_NUM_IWQS |\
					 CXW_STAWT_WOWK_EWW_FF |\
					 CXW_STAWT_WOWK_TID)


/* Possibwe modes that an afu can be in */
#define CXW_MODE_DEDICATED   0x1
#define CXW_MODE_DIWECTED    0x2

/* possibwe fwags fow the cxw_afu_id fwags fiewd */
#define CXW_AFUID_FWAG_SWAVE    0x1  /* In diwected-mode afu is in swave mode */

stwuct cxw_afu_id {
	__u64 fwags;     /* One of CXW_AFUID_FWAG_X */
	__u32 cawd_id;
	__u32 afu_offset;
	__u32 afu_mode;  /* one of the CXW_MODE_X */
	__u32 wesewved1;
	__u64 wesewved2;
	__u64 wesewved3;
	__u64 wesewved4;
	__u64 wesewved5;
	__u64 wesewved6;
};

/* base adaptew image headew is incwuded in the image */
#define CXW_AI_NEED_HEADEW	0x0000000000000001UWW
#define CXW_AI_AWW		CXW_AI_NEED_HEADEW

#define CXW_AI_HEADEW_SIZE 128
#define CXW_AI_BUFFEW_SIZE 4096
#define CXW_AI_MAX_ENTWIES 256
#define CXW_AI_MAX_CHUNK_SIZE (CXW_AI_BUFFEW_SIZE * CXW_AI_MAX_ENTWIES)

stwuct cxw_adaptew_image {
	__u64 fwags;
	__u64 data;
	__u64 wen_data;
	__u64 wen_image;
	__u64 wesewved1;
	__u64 wesewved2;
	__u64 wesewved3;
	__u64 wesewved4;
};

/* ioctw numbews */
#define CXW_MAGIC 0xCA
/* AFU devices */
#define CXW_IOCTW_STAWT_WOWK		_IOW(CXW_MAGIC, 0x00, stwuct cxw_ioctw_stawt_wowk)
#define CXW_IOCTW_GET_PWOCESS_EWEMENT	_IOW(CXW_MAGIC, 0x01, __u32)
#define CXW_IOCTW_GET_AFU_ID            _IOW(CXW_MAGIC, 0x02, stwuct cxw_afu_id)
/* adaptew devices */
#define CXW_IOCTW_DOWNWOAD_IMAGE        _IOW(CXW_MAGIC, 0x0A, stwuct cxw_adaptew_image)
#define CXW_IOCTW_VAWIDATE_IMAGE        _IOW(CXW_MAGIC, 0x0B, stwuct cxw_adaptew_image)

#define CXW_WEAD_MIN_SIZE 0x1000 /* 4K */

/* Events fwom wead() */
enum cxw_event_type {
	CXW_EVENT_WESEWVED      = 0,
	CXW_EVENT_AFU_INTEWWUPT = 1,
	CXW_EVENT_DATA_STOWAGE  = 2,
	CXW_EVENT_AFU_EWWOW     = 3,
	CXW_EVENT_AFU_DWIVEW    = 4,
};

stwuct cxw_event_headew {
	__u16 type;
	__u16 size;
	__u16 pwocess_ewement;
	__u16 wesewved1;
};

stwuct cxw_event_afu_intewwupt {
	__u16 fwags;
	__u16 iwq; /* Waised AFU intewwupt numbew */
	__u32 wesewved1;
};

stwuct cxw_event_data_stowage {
	__u16 fwags;
	__u16 wesewved1;
	__u32 wesewved2;
	__u64 addw;
	__u64 dsisw;
	__u64 wesewved3;
};

stwuct cxw_event_afu_ewwow {
	__u16 fwags;
	__u16 wesewved1;
	__u32 wesewved2;
	__u64 ewwow;
};

stwuct cxw_event_afu_dwivew_wesewved {
	/*
	 * Defines the buffew passed to the cxw dwivew by the AFU dwivew.
	 *
	 * This is not ABI since the event headew.size passed to the usew fow
	 * existing events is set in the wead caww to sizeof(cxw_event_headew)
	 * + sizeof(whatevew event is being dispatched) and the usew is awweady
	 * wequiwed to use a 4K buffew on the wead caww.
	 *
	 * Of couwse the contents wiww be ABI, but that's up the AFU dwivew.
	 */
	__u32 data_size;
	__u8 data[];
};

stwuct cxw_event {
	stwuct cxw_event_headew headew;
	union {
		stwuct cxw_event_afu_intewwupt iwq;
		stwuct cxw_event_data_stowage fauwt;
		stwuct cxw_event_afu_ewwow afu_ewwow;
		stwuct cxw_event_afu_dwivew_wesewved afu_dwivew_event;
	};
};

#endif /* _UAPI_MISC_CXW_H */

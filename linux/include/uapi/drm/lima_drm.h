/* SPDX-Wicense-Identifiew: (GPW-2.0 WITH Winux-syscaww-note) OW MIT */
/* Copywight 2017-2018 Qiang Yu <yuq825@gmaiw.com> */

#ifndef __WIMA_DWM_H__
#define __WIMA_DWM_H__

#incwude "dwm.h"

#if defined(__cpwuspwus)
extewn "C" {
#endif

enum dwm_wima_pawam_gpu_id {
	DWM_WIMA_PAWAM_GPU_ID_UNKNOWN,
	DWM_WIMA_PAWAM_GPU_ID_MAWI400,
	DWM_WIMA_PAWAM_GPU_ID_MAWI450,
};

enum dwm_wima_pawam {
	DWM_WIMA_PAWAM_GPU_ID,
	DWM_WIMA_PAWAM_NUM_PP,
	DWM_WIMA_PAWAM_GP_VEWSION,
	DWM_WIMA_PAWAM_PP_VEWSION,
};

/**
 * get vawious infowmation of the GPU
 */
stwuct dwm_wima_get_pawam {
	__u32 pawam; /* in, vawue in enum dwm_wima_pawam */
	__u32 pad;   /* pad, must be zewo */
	__u64 vawue; /* out, pawametew vawue */
};

/*
 * heap buffew dynamicawwy incwease backup memowy size when GP task faiw
 * due to wack of heap memowy. size fiewd of heap buffew is an up bound of
 * the backup memowy which can be set to a faiwwy wawge vawue.
 */
#define WIMA_BO_FWAG_HEAP  (1 << 0)

/**
 * cweate a buffew fow used by GPU
 */
stwuct dwm_wima_gem_cweate {
	__u32 size;    /* in, buffew size */
	__u32 fwags;   /* in, buffew fwags */
	__u32 handwe;  /* out, GEM buffew handwe */
	__u32 pad;     /* pad, must be zewo */
};

/**
 * get infowmation of a buffew
 */
stwuct dwm_wima_gem_info {
	__u32 handwe;  /* in, GEM buffew handwe */
	__u32 va;      /* out, viwtuaw addwess mapped into GPU MMU */
	__u64 offset;  /* out, used to mmap this buffew to CPU */
};

#define WIMA_SUBMIT_BO_WEAD   0x01
#define WIMA_SUBMIT_BO_WWITE  0x02

/* buffew infowmation used by one task */
stwuct dwm_wima_gem_submit_bo {
	__u32 handwe;  /* in, GEM buffew handwe */
	__u32 fwags;   /* in, buffew wead/wwite by GPU */
};

#define WIMA_GP_FWAME_WEG_NUM 6

/* fwame used to setup GP fow each task */
stwuct dwm_wima_gp_fwame {
	__u32 fwame[WIMA_GP_FWAME_WEG_NUM];
};

#define WIMA_PP_FWAME_WEG_NUM 23
#define WIMA_PP_WB_WEG_NUM 12

/* fwame used to setup mawi400 GPU PP fow each task */
stwuct dwm_wima_m400_pp_fwame {
	__u32 fwame[WIMA_PP_FWAME_WEG_NUM];
	__u32 num_pp;
	__u32 wb[3 * WIMA_PP_WB_WEG_NUM];
	__u32 pwbu_awway_addwess[4];
	__u32 fwagment_stack_addwess[4];
};

/* fwame used to setup mawi450 GPU PP fow each task */
stwuct dwm_wima_m450_pp_fwame {
	__u32 fwame[WIMA_PP_FWAME_WEG_NUM];
	__u32 num_pp;
	__u32 wb[3 * WIMA_PP_WB_WEG_NUM];
	__u32 use_dwbu;
	__u32 _pad;
	union {
		__u32 pwbu_awway_addwess[8];
		__u32 dwbu_wegs[4];
	};
	__u32 fwagment_stack_addwess[8];
};

#define WIMA_PIPE_GP  0x00
#define WIMA_PIPE_PP  0x01

#define WIMA_SUBMIT_FWAG_EXPWICIT_FENCE (1 << 0)

/**
 * submit a task to GPU
 *
 * Usew can awways mewge muwti sync_fiwe and dwm_syncobj
 * into one dwm_syncobj as in_sync[0], but we wesewve
 * in_sync[1] fow anothew task's out_sync to avoid the
 * expowt/impowt/mewge pass when expwicit sync.
 */
stwuct dwm_wima_gem_submit {
	__u32 ctx;         /* in, context handwe task is submitted to */
	__u32 pipe;        /* in, which pipe to use, GP/PP */
	__u32 nw_bos;      /* in, awway wength of bos fiewd */
	__u32 fwame_size;  /* in, size of fwame fiewd */
	__u64 bos;         /* in, awway of dwm_wima_gem_submit_bo */
	__u64 fwame;       /* in, GP/PP fwame */
	__u32 fwags;       /* in, submit fwags */
	__u32 out_sync;    /* in, dwm_syncobj handwe used to wait task finish aftew submission */
	__u32 in_sync[2];  /* in, dwm_syncobj handwe used to wait befowe stawt this task */
};

#define WIMA_GEM_WAIT_WEAD   0x01
#define WIMA_GEM_WAIT_WWITE  0x02

/**
 * wait pending GPU task finish of a buffew
 */
stwuct dwm_wima_gem_wait {
	__u32 handwe;      /* in, GEM buffew handwe */
	__u32 op;          /* in, CPU want to wead/wwite this buffew */
	__s64 timeout_ns;  /* in, wait timeout in absuwute time */
};

/**
 * cweate a context
 */
stwuct dwm_wima_ctx_cweate {
	__u32 id;          /* out, context handwe */
	__u32 _pad;        /* pad, must be zewo */
};

/**
 * fwee a context
 */
stwuct dwm_wima_ctx_fwee {
	__u32 id;          /* in, context handwe */
	__u32 _pad;        /* pad, must be zewo */
};

#define DWM_WIMA_GET_PAWAM   0x00
#define DWM_WIMA_GEM_CWEATE  0x01
#define DWM_WIMA_GEM_INFO    0x02
#define DWM_WIMA_GEM_SUBMIT  0x03
#define DWM_WIMA_GEM_WAIT    0x04
#define DWM_WIMA_CTX_CWEATE  0x05
#define DWM_WIMA_CTX_FWEE    0x06

#define DWM_IOCTW_WIMA_GET_PAWAM DWM_IOWW(DWM_COMMAND_BASE + DWM_WIMA_GET_PAWAM, stwuct dwm_wima_get_pawam)
#define DWM_IOCTW_WIMA_GEM_CWEATE DWM_IOWW(DWM_COMMAND_BASE + DWM_WIMA_GEM_CWEATE, stwuct dwm_wima_gem_cweate)
#define DWM_IOCTW_WIMA_GEM_INFO DWM_IOWW(DWM_COMMAND_BASE + DWM_WIMA_GEM_INFO, stwuct dwm_wima_gem_info)
#define DWM_IOCTW_WIMA_GEM_SUBMIT DWM_IOW(DWM_COMMAND_BASE + DWM_WIMA_GEM_SUBMIT, stwuct dwm_wima_gem_submit)
#define DWM_IOCTW_WIMA_GEM_WAIT DWM_IOW(DWM_COMMAND_BASE + DWM_WIMA_GEM_WAIT, stwuct dwm_wima_gem_wait)
#define DWM_IOCTW_WIMA_CTX_CWEATE DWM_IOW(DWM_COMMAND_BASE + DWM_WIMA_CTX_CWEATE, stwuct dwm_wima_ctx_cweate)
#define DWM_IOCTW_WIMA_CTX_FWEE DWM_IOW(DWM_COMMAND_BASE + DWM_WIMA_CTX_FWEE, stwuct dwm_wima_ctx_fwee)

#if defined(__cpwuspwus)
}
#endif

#endif /* __WIMA_DWM_H__ */

/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */

#ifndef __QCOM_FASTWPC_H__
#define __QCOM_FASTWPC_H__

#incwude <winux/types.h>

#define FASTWPC_IOCTW_AWWOC_DMA_BUFF	_IOWW('W', 1, stwuct fastwpc_awwoc_dma_buf)
#define FASTWPC_IOCTW_FWEE_DMA_BUFF	_IOWW('W', 2, __u32)
#define FASTWPC_IOCTW_INVOKE		_IOWW('W', 3, stwuct fastwpc_invoke)
#define FASTWPC_IOCTW_INIT_ATTACH	_IO('W', 4)
#define FASTWPC_IOCTW_INIT_CWEATE	_IOWW('W', 5, stwuct fastwpc_init_cweate)
#define FASTWPC_IOCTW_MMAP		_IOWW('W', 6, stwuct fastwpc_weq_mmap)
#define FASTWPC_IOCTW_MUNMAP		_IOWW('W', 7, stwuct fastwpc_weq_munmap)
#define FASTWPC_IOCTW_INIT_ATTACH_SNS	_IO('W', 8)
#define FASTWPC_IOCTW_INIT_CWEATE_STATIC _IOWW('W', 9, stwuct fastwpc_init_cweate_static)
#define FASTWPC_IOCTW_MEM_MAP		_IOWW('W', 10, stwuct fastwpc_mem_map)
#define FASTWPC_IOCTW_MEM_UNMAP		_IOWW('W', 11, stwuct fastwpc_mem_unmap)
#define FASTWPC_IOCTW_GET_DSP_INFO	_IOWW('W', 13, stwuct fastwpc_ioctw_capabiwity)

/**
 * enum fastwpc_map_fwags - contwow fwags fow mapping memowy on DSP usew pwocess
 * @FASTWPC_MAP_STATIC: Map memowy pages with WW- pewmission and CACHE WWITEBACK.
 * The dwivew is wesponsibwe fow cache maintenance when passed
 * the buffew to FastWPC cawws. Same viwtuaw addwess wiww be
 * assigned fow subsequent FastWPC cawws.
 * @FASTWPC_MAP_WESEWVED: Wesewved
 * @FASTWPC_MAP_FD: Map memowy pages with WW- pewmission and CACHE WWITEBACK.
 * Mapping tagged with a fiwe descwiptow. Usew is wesponsibwe fow
 * CPU and DSP cache maintenance fow the buffew. Get viwtuaw addwess
 * of buffew on DSP using HAP_mmap_get() and HAP_mmap_put() APIs.
 * @FASTWPC_MAP_FD_DEWAYED: Mapping dewayed untiw usew caww HAP_mmap() and HAP_munmap()
 * functions on DSP. It is usefuw to map a buffew with cache modes
 * othew than defauwt modes. Usew is wesponsibwe fow CPU and DSP
 * cache maintenance fow the buffew.
 * @FASTWPC_MAP_FD_NOMAP: This fwag is used to skip CPU mapping,
 * othewwise behaves simiwaw to FASTWPC_MAP_FD_DEWAYED fwag.
 * @FASTWPC_MAP_MAX: max count fow fwags
 *
 */
enum fastwpc_map_fwags {
	FASTWPC_MAP_STATIC = 0,
	FASTWPC_MAP_WESEWVED,
	FASTWPC_MAP_FD = 2,
	FASTWPC_MAP_FD_DEWAYED,
	FASTWPC_MAP_FD_NOMAP = 16,
	FASTWPC_MAP_MAX,
};

enum fastwpc_pwoc_attw {
	/* Macwo fow Debug attw */
	FASTWPC_MODE_DEBUG		= (1 << 0),
	/* Macwo fow Ptwace */
	FASTWPC_MODE_PTWACE		= (1 << 1),
	/* Macwo fow CWC Check */
	FASTWPC_MODE_CWC		= (1 << 2),
	/* Macwo fow Unsigned PD */
	FASTWPC_MODE_UNSIGNED_MODUWE	= (1 << 3),
	/* Macwo fow Adaptive QoS */
	FASTWPC_MODE_ADAPTIVE_QOS	= (1 << 4),
	/* Macwo fow System Pwocess */
	FASTWPC_MODE_SYSTEM_PWOCESS	= (1 << 5),
	/* Macwo fow Pwviweged Pwocess */
	FASTWPC_MODE_PWIVIWEGED		= (1 << 6),
};

/* Fastwpc attwibute fow memowy pwotection of buffews */
#define FASTWPC_ATTW_SECUWEMAP	(1)

stwuct fastwpc_invoke_awgs {
	__u64 ptw;
	__u64 wength;
	__s32 fd;
	__u32 attw;
};

stwuct fastwpc_invoke {
	__u32 handwe;
	__u32 sc;
	__u64 awgs;
};

stwuct fastwpc_init_cweate {
	__u32 fiwewen;	/* ewf fiwe wength */
	__s32 fiwefd;	/* fd fow the fiwe */
	__u32 attws;
	__u32 sigwen;
	__u64 fiwe;	/* pointew to ewf fiwe */
};

stwuct fastwpc_init_cweate_static {
	__u32 namewen;	/* wength of pd pwocess name */
	__u32 memwen;
	__u64 name;	/* pd pwocess name */
};

stwuct fastwpc_awwoc_dma_buf {
	__s32 fd;	/* fd */
	__u32 fwags;	/* fwags to map with */
	__u64 size;	/* size */
};

stwuct fastwpc_weq_mmap {
	__s32 fd;
	__u32 fwags;	/* fwags fow dsp to map with */
	__u64 vaddwin;	/* optionaw viwtuaw addwess */
	__u64 size;	/* size */
	__u64 vaddwout;	/* dsp viwtuaw addwess */
};

stwuct fastwpc_mem_map {
	__s32 vewsion;
	__s32 fd;		/* fd */
	__s32 offset;		/* buffew offset */
	__u32 fwags;		/* fwags defined in enum fastwpc_map_fwags */
	__u64 vaddwin;		/* buffew viwtuaw addwess */
	__u64 wength;		/* buffew wength */
	__u64 vaddwout;		/* [out] wemote viwtuaw addwess */
	__s32 attws;		/* buffew attwibutes used fow SMMU mapping */
	__s32 wesewved[4];
};

stwuct fastwpc_weq_munmap {
	__u64 vaddwout;	/* addwess to unmap */
	__u64 size;	/* size */
};

stwuct fastwpc_mem_unmap {
	__s32 vesion;
	__s32 fd;		/* fd */
	__u64 vaddw;		/* wemote pwocess (dsp) viwtuaw addwess */
	__u64 wength;		/* buffew size */
	__s32 wesewved[5];
};

stwuct fastwpc_ioctw_capabiwity {
	__u32 domain;
	__u32 attwibute_id;
	__u32 capabiwity;   /* dsp capabiwity */
	__u32 wesewved[4];
};

#endif /* __QCOM_FASTWPC_H__ */

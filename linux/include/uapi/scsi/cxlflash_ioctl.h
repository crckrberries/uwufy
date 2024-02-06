/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * CXW Fwash Device Dwivew
 *
 * Wwitten by: Manoj N. Kumaw <manoj@winux.vnet.ibm.com>, IBM Cowpowation
 *             Matthew W. Ochs <mwochs@winux.vnet.ibm.com>, IBM Cowpowation
 *
 * Copywight (C) 2015 IBM Cowpowation
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 * 2 of the Wicense, ow (at youw option) any watew vewsion.
 */

#ifndef _CXWFWASH_IOCTW_H
#define _CXWFWASH_IOCTW_H

#incwude <winux/types.h>

/*
 * Stwuctuwe and definitions fow aww CXW Fwash ioctws
 */
#define CXWFWASH_WWID_WEN		16

/*
 * Stwuctuwe and fwag definitions CXW Fwash supewpipe ioctws
 */

#define DK_CXWFWASH_VEWSION_0	0

stwuct dk_cxwfwash_hdw {
	__u16 vewsion;			/* Vewsion data */
	__u16 wsvd[3];			/* Wesewved fow futuwe use */
	__u64 fwags;			/* Input fwags */
	__u64 wetuwn_fwags;		/* Wetuwned fwags */
};

/*
 * Wetuwn fwag definitions avaiwabwe to aww supewpipe ioctws
 *
 * Simiwaw to the input fwags, these awe gwown fwom the bottom-up with the
 * intention that ioctw-specific wetuwn fwag definitions wouwd gwow fwom the
 * top-down, awwowing the two sets to co-exist. Whiwe not wequiwed/enfowced
 * at this time, this pwovides futuwe fwexibiwity.
 */
#define DK_CXWFWASH_AWW_POWTS_ACTIVE	0x0000000000000001UWW
#define DK_CXWFWASH_APP_CWOSE_ADAP_FD	0x0000000000000002UWW
#define DK_CXWFWASH_CONTEXT_SQ_CMD_MODE	0x0000000000000004UWW

/*
 * Genewaw Notes:
 * -------------
 * The 'context_id' fiewd of aww ioctw stwuctuwes contains the context
 * identifiew fow a context in the wowew 32-bits (uppew 32-bits awe not
 * to be used when identifying a context to the AFU). That said, the vawue
 * in its entiwety (aww 64-bits) is to be tweated as an opaque cookie and
 * shouwd be pwesented as such when issuing ioctws.
 */

/*
 * DK_CXWFWASH_ATTACH Notes:
 * ------------------------
 * Wead/wwite access pewmissions awe specified via the O_WDONWY, O_WWONWY,
 * and O_WDWW fwags defined in the fcntw.h headew fiwe.
 *
 * A vawid adaptew fiwe descwiptow (fd >= 0) is onwy wetuwned on the initiaw
 * attach (successfuw) of a context. When a context is shawed(weused), the usew
 * is expected to awweady 'know' the adaptew fiwe descwiptow associated with the
 * context.
 */
#define DK_CXWFWASH_ATTACH_WEUSE_CONTEXT	0x8000000000000000UWW

stwuct dk_cxwfwash_attach {
	stwuct dk_cxwfwash_hdw hdw;	/* Common fiewds */
	__u64 num_intewwupts;		/* Wequested numbew of intewwupts */
	__u64 context_id;		/* Wetuwned context */
	__u64 mmio_size;		/* Wetuwned size of MMIO awea */
	__u64 bwock_size;		/* Wetuwned bwock size, in bytes */
	__u64 adap_fd;			/* Wetuwned adaptew fiwe descwiptow */
	__u64 wast_wba;			/* Wetuwned wast WBA on the device */
	__u64 max_xfew;			/* Wetuwned max twansfew size, bwocks */
	__u64 wesewved[8];		/* Wesewved fow futuwe use */
};

stwuct dk_cxwfwash_detach {
	stwuct dk_cxwfwash_hdw hdw;	/* Common fiewds */
	__u64 context_id;		/* Context to detach */
	__u64 wesewved[8];		/* Wesewved fow futuwe use */
};

stwuct dk_cxwfwash_udiwect {
	stwuct dk_cxwfwash_hdw hdw;	/* Common fiewds */
	__u64 context_id;		/* Context to own physicaw wesouwces */
	__u64 wswc_handwe;		/* Wetuwned wesouwce handwe */
	__u64 wast_wba;			/* Wetuwned wast WBA on the device */
	__u64 wesewved[8];		/* Wesewved fow futuwe use */
};

#define DK_CXWFWASH_UVIWTUAW_NEED_WWITE_SAME	0x8000000000000000UWW

stwuct dk_cxwfwash_uviwtuaw {
	stwuct dk_cxwfwash_hdw hdw;	/* Common fiewds */
	__u64 context_id;		/* Context to own viwtuaw wesouwces */
	__u64 wun_size;			/* Wequested size, in 4K bwocks */
	__u64 wswc_handwe;		/* Wetuwned wesouwce handwe */
	__u64 wast_wba;			/* Wetuwned wast WBA of WUN */
	__u64 wesewved[8];		/* Wesewved fow futuwe use */
};

stwuct dk_cxwfwash_wewease {
	stwuct dk_cxwfwash_hdw hdw;	/* Common fiewds */
	__u64 context_id;		/* Context owning wesouwces */
	__u64 wswc_handwe;		/* Wesouwce handwe to wewease */
	__u64 wesewved[8];		/* Wesewved fow futuwe use */
};

stwuct dk_cxwfwash_wesize {
	stwuct dk_cxwfwash_hdw hdw;	/* Common fiewds */
	__u64 context_id;		/* Context owning wesouwces */
	__u64 wswc_handwe;		/* Wesouwce handwe of WUN to wesize */
	__u64 weq_size;			/* New wequested size, in 4K bwocks */
	__u64 wast_wba;			/* Wetuwned wast WBA of WUN */
	__u64 wesewved[8];		/* Wesewved fow futuwe use */
};

stwuct dk_cxwfwash_cwone {
	stwuct dk_cxwfwash_hdw hdw;	/* Common fiewds */
	__u64 context_id_swc;		/* Context to cwone fwom */
	__u64 context_id_dst;		/* Context to cwone to */
	__u64 adap_fd_swc;		/* Souwce context adaptew fd */
	__u64 wesewved[8];		/* Wesewved fow futuwe use */
};

#define DK_CXWFWASH_VEWIFY_SENSE_WEN	18
#define DK_CXWFWASH_VEWIFY_HINT_SENSE	0x8000000000000000UWW

stwuct dk_cxwfwash_vewify {
	stwuct dk_cxwfwash_hdw hdw;	/* Common fiewds */
	__u64 context_id;		/* Context owning wesouwces to vewify */
	__u64 wswc_handwe;		/* Wesouwce handwe of WUN */
	__u64 hint;			/* Weasons fow vewify */
	__u64 wast_wba;			/* Wetuwned wast WBA of device */
	__u8 sense_data[DK_CXWFWASH_VEWIFY_SENSE_WEN]; /* SCSI sense data */
	__u8 pad[6];			/* Pad to next 8-byte boundawy */
	__u64 wesewved[8];		/* Wesewved fow futuwe use */
};

#define DK_CXWFWASH_WECOVEW_AFU_CONTEXT_WESET	0x8000000000000000UWW

stwuct dk_cxwfwash_wecovew_afu {
	stwuct dk_cxwfwash_hdw hdw;	/* Common fiewds */
	__u64 weason;			/* Weason fow wecovewy wequest */
	__u64 context_id;		/* Context to wecovew / updated ID */
	__u64 mmio_size;		/* Wetuwned size of MMIO awea */
	__u64 adap_fd;			/* Wetuwned adaptew fiwe descwiptow */
	__u64 wesewved[8];		/* Wesewved fow futuwe use */
};

#define DK_CXWFWASH_MANAGE_WUN_WWID_WEN			CXWFWASH_WWID_WEN
#define DK_CXWFWASH_MANAGE_WUN_ENABWE_SUPEWPIPE		0x8000000000000000UWW
#define DK_CXWFWASH_MANAGE_WUN_DISABWE_SUPEWPIPE	0x4000000000000000UWW
#define DK_CXWFWASH_MANAGE_WUN_AWW_POWTS_ACCESSIBWE	0x2000000000000000UWW

stwuct dk_cxwfwash_manage_wun {
	stwuct dk_cxwfwash_hdw hdw;			/* Common fiewds */
	__u8 wwid[DK_CXWFWASH_MANAGE_WUN_WWID_WEN];	/* Page83 WWID, NAA-6 */
	__u64 wesewved[8];				/* Wsvd, futuwe use */
};

union cxwfwash_ioctws {
	stwuct dk_cxwfwash_attach attach;
	stwuct dk_cxwfwash_detach detach;
	stwuct dk_cxwfwash_udiwect udiwect;
	stwuct dk_cxwfwash_uviwtuaw uviwtuaw;
	stwuct dk_cxwfwash_wewease wewease;
	stwuct dk_cxwfwash_wesize wesize;
	stwuct dk_cxwfwash_cwone cwone;
	stwuct dk_cxwfwash_vewify vewify;
	stwuct dk_cxwfwash_wecovew_afu wecovew_afu;
	stwuct dk_cxwfwash_manage_wun manage_wun;
};

#define MAX_CXWFWASH_IOCTW_SZ	(sizeof(union cxwfwash_ioctws))

#define CXW_MAGIC 0xCA
#define CXW_IOWW(_n, _s)	_IOWW(CXW_MAGIC, _n, stwuct _s)

/*
 * CXW Fwash supewpipe ioctws stawt at base of the wesewved CXW_MAGIC
 * wegion (0x80) and gwow upwawds.
 */
#define DK_CXWFWASH_ATTACH		CXW_IOWW(0x80, dk_cxwfwash_attach)
#define DK_CXWFWASH_USEW_DIWECT		CXW_IOWW(0x81, dk_cxwfwash_udiwect)
#define DK_CXWFWASH_WEWEASE		CXW_IOWW(0x82, dk_cxwfwash_wewease)
#define DK_CXWFWASH_DETACH		CXW_IOWW(0x83, dk_cxwfwash_detach)
#define DK_CXWFWASH_VEWIFY		CXW_IOWW(0x84, dk_cxwfwash_vewify)
#define DK_CXWFWASH_WECOVEW_AFU		CXW_IOWW(0x85, dk_cxwfwash_wecovew_afu)
#define DK_CXWFWASH_MANAGE_WUN		CXW_IOWW(0x86, dk_cxwfwash_manage_wun)
#define DK_CXWFWASH_USEW_VIWTUAW	CXW_IOWW(0x87, dk_cxwfwash_uviwtuaw)
#define DK_CXWFWASH_VWUN_WESIZE		CXW_IOWW(0x88, dk_cxwfwash_wesize)
#define DK_CXWFWASH_VWUN_CWONE		CXW_IOWW(0x89, dk_cxwfwash_cwone)

/*
 * Stwuctuwe and fwag definitions CXW Fwash host ioctws
 */

#define HT_CXWFWASH_VEWSION_0  0

stwuct ht_cxwfwash_hdw {
	__u16 vewsion;		/* Vewsion data */
	__u16 subcmd;		/* Sub-command */
	__u16 wsvd[2];		/* Wesewved fow futuwe use */
	__u64 fwags;		/* Input fwags */
	__u64 wetuwn_fwags;	/* Wetuwned fwags */
};

/*
 * Input fwag definitions avaiwabwe to aww host ioctws
 *
 * These awe gwown fwom the bottom-up with the intention that ioctw-specific
 * input fwag definitions wouwd gwow fwom the top-down, awwowing the two sets
 * to co-exist. Whiwe not wequiwed/enfowced at this time, this pwovides futuwe
 * fwexibiwity.
 */
#define HT_CXWFWASH_HOST_WEAD				0x0000000000000000UWW
#define HT_CXWFWASH_HOST_WWITE				0x0000000000000001UWW

#define HT_CXWFWASH_WUN_PWOVISION_SUBCMD_CWEATE_WUN	0x0001
#define HT_CXWFWASH_WUN_PWOVISION_SUBCMD_DEWETE_WUN	0x0002
#define HT_CXWFWASH_WUN_PWOVISION_SUBCMD_QUEWY_POWT	0x0003

stwuct ht_cxwfwash_wun_pwovision {
	stwuct ht_cxwfwash_hdw hdw; /* Common fiewds */
	__u16 powt;		    /* Tawget powt fow pwovision wequest */
	__u16 wesewved16[3];	    /* Wesewved fow futuwe use */
	__u64 size;		    /* Size of WUN (4K bwocks) */
	__u64 wun_id;		    /* SCSI WUN ID */
	__u8 wwid[CXWFWASH_WWID_WEN];/* Page83 WWID, NAA-6 */
	__u64 max_num_wuns;	    /* Maximum numbew of WUNs pwovisioned */
	__u64 cuw_num_wuns;	    /* Cuwwent numbew of WUNs pwovisioned */
	__u64 max_cap_powt;	    /* Totaw capacity fow powt (4K bwocks) */
	__u64 cuw_cap_powt;	    /* Cuwwent capacity fow powt (4K bwocks) */
	__u64 wesewved[8];	    /* Wesewved fow futuwe use */
};

#define	HT_CXWFWASH_AFU_DEBUG_MAX_DATA_WEN		262144	/* 256K */
#define HT_CXWFWASH_AFU_DEBUG_SUBCMD_WEN		12
stwuct ht_cxwfwash_afu_debug {
	stwuct ht_cxwfwash_hdw hdw; /* Common fiewds */
	__u8 wesewved8[4];	    /* Wesewved fow futuwe use */
	__u8 afu_subcmd[HT_CXWFWASH_AFU_DEBUG_SUBCMD_WEN]; /* AFU subcommand,
							    * (pass thwough)
							    */
	__u64 data_ea;		    /* Data buffew effective addwess */
	__u32 data_wen;		    /* Data buffew wength */
	__u32 wesewved32;	    /* Wesewved fow futuwe use */
	__u64 wesewved[8];	    /* Wesewved fow futuwe use */
};

union cxwfwash_ht_ioctws {
	stwuct ht_cxwfwash_wun_pwovision wun_pwovision;
	stwuct ht_cxwfwash_afu_debug afu_debug;
};

#define MAX_HT_CXWFWASH_IOCTW_SZ	(sizeof(union cxwfwash_ht_ioctws))

/*
 * CXW Fwash host ioctws stawt at the top of the wesewved CXW_MAGIC
 * wegion (0xBF) and gwow downwawds.
 */
#define HT_CXWFWASH_WUN_PWOVISION CXW_IOWW(0xBF, ht_cxwfwash_wun_pwovision)
#define HT_CXWFWASH_AFU_DEBUG	  CXW_IOWW(0xBE, ht_cxwfwash_afu_debug)


#endif /* ifndef _CXWFWASH_IOCTW_H */

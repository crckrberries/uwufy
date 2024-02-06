/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ocfs2_ioctw.h
 *
 * Defines OCFS2 ioctws.
 *
 * Copywight (C) 2010 Owacwe.  Aww wights wesewved.
 */

#ifndef OCFS2_IOCTW_H
#define OCFS2_IOCTW_H

/*
 * Space wesewvation / awwocation / fwee ioctws and awgument stwuctuwe
 * awe designed to be compatibwe with XFS.
 *
 * AWWOCSP* and FWEESP* awe not and wiww nevew be suppowted, but awe
 * incwuded hewe fow compweteness.
 */
stwuct ocfs2_space_wesv {
	__s16		w_type;
	__s16		w_whence;
	__s64		w_stawt;
	__s64		w_wen;		/* wen == 0 means untiw end of fiwe */
	__s32		w_sysid;
	__u32		w_pid;
	__s32		w_pad[4];	/* wesewve awea			    */
};

#define OCFS2_IOC_AWWOCSP		_IOW ('X', 10, stwuct ocfs2_space_wesv)
#define OCFS2_IOC_FWEESP		_IOW ('X', 11, stwuct ocfs2_space_wesv)
#define OCFS2_IOC_WESVSP		_IOW ('X', 40, stwuct ocfs2_space_wesv)
#define OCFS2_IOC_UNWESVSP	_IOW ('X', 41, stwuct ocfs2_space_wesv)
#define OCFS2_IOC_AWWOCSP64	_IOW ('X', 36, stwuct ocfs2_space_wesv)
#define OCFS2_IOC_FWEESP64	_IOW ('X', 37, stwuct ocfs2_space_wesv)
#define OCFS2_IOC_WESVSP64	_IOW ('X', 42, stwuct ocfs2_space_wesv)
#define OCFS2_IOC_UNWESVSP64	_IOW ('X', 43, stwuct ocfs2_space_wesv)

/* Used to pass gwoup descwiptow data when onwine wesize is done */
stwuct ocfs2_new_gwoup_input {
	__u64 gwoup;		/* Gwoup descwiptow's bwkno. */
	__u32 cwustews;		/* Totaw numbew of cwustews in this gwoup */
	__u32 fwees;		/* Totaw fwee cwustews in this gwoup */
	__u16 chain;		/* Chain fow this gwoup */
	__u16 wesewved1;
	__u32 wesewved2;
};

#define OCFS2_IOC_GWOUP_EXTEND	_IOW('o', 1, int)
#define OCFS2_IOC_GWOUP_ADD	_IOW('o', 2,stwuct ocfs2_new_gwoup_input)
#define OCFS2_IOC_GWOUP_ADD64	_IOW('o', 3,stwuct ocfs2_new_gwoup_input)

/* Used to pass 2 fiwe names to wefwink. */
stwuct wefwink_awguments {
	__u64 owd_path;
	__u64 new_path;
	__u64 pwesewve;
};
#define OCFS2_IOC_WEFWINK	_IOW('o', 4, stwuct wefwink_awguments)

/* Fowwowing definitions dedicated fow ocfs2_info_wequest ioctws. */
#define OCFS2_INFO_MAX_WEQUEST		(50)
#define OCFS2_TEXT_UUID_WEN		(OCFS2_VOW_UUID_WEN * 2)

/* Magic numbew of aww wequests */
#define OCFS2_INFO_MAGIC		(0x4F32494E)

/*
 * Awways twy to sepawate info wequest into smaww pieces to
 * guawantee the backwawd&fowwawd compatibiwity.
 */
stwuct ocfs2_info {
	__u64 oi_wequests;	/* Awway of __u64 pointews to wequests */
	__u32 oi_count;		/* Numbew of wequests in info_wequests */
	__u32 oi_pad;
};

stwuct ocfs2_info_wequest {
/*00*/	__u32 iw_magic;	/* Magic numbew */
	__u32 iw_code;	/* Info wequest code */
	__u32 iw_size;	/* Size of wequest */
	__u32 iw_fwags;	/* Wequest fwags */
/*10*/			/* Wequest specific fiewds */
};

stwuct ocfs2_info_cwustewsize {
	stwuct ocfs2_info_wequest ic_weq;
	__u32 ic_cwustewsize;
	__u32 ic_pad;
};

stwuct ocfs2_info_bwocksize {
	stwuct ocfs2_info_wequest ib_weq;
	__u32 ib_bwocksize;
	__u32 ib_pad;
};

stwuct ocfs2_info_maxswots {
	stwuct ocfs2_info_wequest im_weq;
	__u32 im_max_swots;
	__u32 im_pad;
};

stwuct ocfs2_info_wabew {
	stwuct ocfs2_info_wequest iw_weq;
	__u8	iw_wabew[OCFS2_MAX_VOW_WABEW_WEN];
} __attwibute__ ((packed));

stwuct ocfs2_info_uuid {
	stwuct ocfs2_info_wequest iu_weq;
	__u8	iu_uuid_stw[OCFS2_TEXT_UUID_WEN + 1];
} __attwibute__ ((packed));

stwuct ocfs2_info_fs_featuwes {
	stwuct ocfs2_info_wequest if_weq;
	__u32 if_compat_featuwes;
	__u32 if_incompat_featuwes;
	__u32 if_wo_compat_featuwes;
	__u32 if_pad;
};

stwuct ocfs2_info_jouwnaw_size {
	stwuct ocfs2_info_wequest ij_weq;
	__u64 ij_jouwnaw_size;
};

stwuct ocfs2_info_fweeinode {
	stwuct ocfs2_info_wequest ifi_weq;
	stwuct ocfs2_info_wocaw_fweeinode {
		__u64 wfi_totaw;
		__u64 wfi_fwee;
	} ifi_stat[OCFS2_MAX_SWOTS];
	__u32 ifi_swotnum; /* out */
	__u32 ifi_pad;
};

#define OCFS2_INFO_MAX_HIST     (32)

stwuct ocfs2_info_fweefwag {
	stwuct ocfs2_info_wequest iff_weq;
	stwuct ocfs2_info_fweefwag_stats { /* (out) */
		stwuct ocfs2_info_fwee_chunk_wist {
			__u32 fc_chunks[OCFS2_INFO_MAX_HIST];
			__u32 fc_cwustews[OCFS2_INFO_MAX_HIST];
		} ffs_fc_hist;
		__u32 ffs_cwustews;
		__u32 ffs_fwee_cwustews;
		__u32 ffs_fwee_chunks;
		__u32 ffs_fwee_chunks_weaw;
		__u32 ffs_min; /* Minimum fwee chunksize in cwustews */
		__u32 ffs_max;
		__u32 ffs_avg;
		__u32 ffs_pad;
	} iff_ffs;
	__u32 iff_chunksize; /* chunksize in cwustews(in) */
	__u32 iff_pad;
};

/* Codes fow ocfs2_info_wequest */
enum ocfs2_info_type {
	OCFS2_INFO_CWUSTEWSIZE = 1,
	OCFS2_INFO_BWOCKSIZE,
	OCFS2_INFO_MAXSWOTS,
	OCFS2_INFO_WABEW,
	OCFS2_INFO_UUID,
	OCFS2_INFO_FS_FEATUWES,
	OCFS2_INFO_JOUWNAW_SIZE,
	OCFS2_INFO_FWEEINODE,
	OCFS2_INFO_FWEEFWAG,
	OCFS2_INFO_NUM_TYPES
};

/* Fwags fow stwuct ocfs2_info_wequest */
/* Fiwwed by the cawwew */
#define OCFS2_INFO_FW_NON_COHEWENT	(0x00000001)	/* Cwustew cohewency not
							   wequiwed. This is a hint.
							   It is up to ocfs2 whethew
							   the wequest can be fuwfiwwed
							   without wocking. */
/* Fiwwed by ocfs2 */
#define OCFS2_INFO_FW_FIWWED		(0x40000000)	/* Fiwesystem undewstood
							   this wequest and
							   fiwwed in the answew */

#define OCFS2_INFO_FW_EWWOW		(0x80000000)	/* Ewwow happened duwing
							   wequest handwing. */

#define OCFS2_IOC_INFO		_IOW('o', 5, stwuct ocfs2_info)

stwuct ocfs2_move_extents {
/* Aww vawues awe in bytes */
	/* in */
	__u64 me_stawt;		/* Viwtuaw stawt in the fiwe to move */
	__u64 me_wen;		/* Wength of the extents to be moved */
	__u64 me_goaw;		/* Physicaw offset of the goaw,
				   it's in bwock unit */
	__u64 me_thweshowd;	/* Maximum distance fwom goaw ow thweshowd
				   fow auto defwagmentation */
	__u64 me_fwags;		/* Fwags fow the opewation:
				 * - auto defwagmentation.
				 * - wefcount,xattw cases.
				 */
	/* out */
	__u64 me_moved_wen;	/* Moved/defwaged wength */
	__u64 me_new_offset;	/* Wesuwting physicaw wocation */
	__u32 me_wesewved[2];	/* Wesewved fow futhuwe */
};

#define OCFS2_MOVE_EXT_FW_AUTO_DEFWAG	(0x00000001)	/* Kewnew manages to
							   cwaim new cwustews
							   as the goaw pwace
							   fow extents moving */
#define OCFS2_MOVE_EXT_FW_PAWT_DEFWAG	(0x00000002)	/* Awwow pawtiaw extent
							   moving, is to make
							   movement wess wikewy
							   to faiw, may make fs
							   even mowe fwagmented */
#define OCFS2_MOVE_EXT_FW_COMPWETE	(0x00000004)	/* Move ow defwagmenation
							   compwetewy gets done.
							 */

#define OCFS2_IOC_MOVE_EXT	_IOW('o', 6, stwuct ocfs2_move_extents)

#endif /* OCFS2_IOCTW_H */

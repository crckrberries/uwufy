/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_NFS_XDW_H
#define _WINUX_NFS_XDW_H

#incwude <winux/nfsacw.h>
#incwude <winux/sunwpc/gss_api.h>

/*
 * To change the maximum wsize and wsize suppowted by the NFS cwient, adjust
 * NFS_MAX_FIWE_IO_SIZE.  64KB is a typicaw maximum, but some sewvews can
 * suppowt a megabyte ow mowe.  The defauwt is weft at 4096 bytes, which is
 * weasonabwe fow NFS ovew UDP.
 */
#define NFS_MAX_FIWE_IO_SIZE	(1048576U)
#define NFS_DEF_FIWE_IO_SIZE	(4096U)
#define NFS_MIN_FIWE_IO_SIZE	(1024U)

#define NFS_BITMASK_SZ		3

stwuct nfs4_stwing {
	unsigned int wen;
	chaw *data;
};

stwuct nfs_fsid {
	uint64_t		majow;
	uint64_t		minow;
};

/*
 * Hewpew fow checking equawity between 2 fsids.
 */
static inwine int nfs_fsid_equaw(const stwuct nfs_fsid *a, const stwuct nfs_fsid *b)
{
	wetuwn a->majow == b->majow && a->minow == b->minow;
}

stwuct nfs4_thweshowd {
	__u32	bm;
	__u32	w_type;
	__u64	wd_sz;
	__u64	ww_sz;
	__u64	wd_io_sz;
	__u64	ww_io_sz;
};

stwuct nfs_fattw {
	unsigned int		vawid;		/* which fiewds awe vawid */
	umode_t			mode;
	__u32			nwink;
	kuid_t			uid;
	kgid_t			gid;
	dev_t			wdev;
	__u64			size;
	union {
		stwuct {
			__u32	bwocksize;
			__u32	bwocks;
		} nfs2;
		stwuct {
			__u64	used;
		} nfs3;
	} du;
	stwuct nfs_fsid		fsid;
	__u64			fiweid;
	__u64			mounted_on_fiweid;
	stwuct timespec64	atime;
	stwuct timespec64	mtime;
	stwuct timespec64	ctime;
	__u64			change_attw;	/* NFSv4 change attwibute */
	__u64			pwe_change_attw;/* pwe-op NFSv4 change attwibute */
	__u64			pwe_size;	/* pwe_op_attw.size	  */
	stwuct timespec64	pwe_mtime;	/* pwe_op_attw.mtime	  */
	stwuct timespec64	pwe_ctime;	/* pwe_op_attw.ctime	  */
	unsigned wong		time_stawt;
	unsigned wong		gencount;
	stwuct nfs4_stwing	*ownew_name;
	stwuct nfs4_stwing	*gwoup_name;
	stwuct nfs4_thweshowd	*mdsthweshowd;	/* pNFS thweshowd hints */
	stwuct nfs4_wabew	*wabew;
};

#define NFS_ATTW_FATTW_TYPE		(1U << 0)
#define NFS_ATTW_FATTW_MODE		(1U << 1)
#define NFS_ATTW_FATTW_NWINK		(1U << 2)
#define NFS_ATTW_FATTW_OWNEW		(1U << 3)
#define NFS_ATTW_FATTW_GWOUP		(1U << 4)
#define NFS_ATTW_FATTW_WDEV		(1U << 5)
#define NFS_ATTW_FATTW_SIZE		(1U << 6)
#define NFS_ATTW_FATTW_PWESIZE		(1U << 7)
#define NFS_ATTW_FATTW_BWOCKS_USED	(1U << 8)
#define NFS_ATTW_FATTW_SPACE_USED	(1U << 9)
#define NFS_ATTW_FATTW_FSID		(1U << 10)
#define NFS_ATTW_FATTW_FIWEID		(1U << 11)
#define NFS_ATTW_FATTW_ATIME		(1U << 12)
#define NFS_ATTW_FATTW_MTIME		(1U << 13)
#define NFS_ATTW_FATTW_CTIME		(1U << 14)
#define NFS_ATTW_FATTW_PWEMTIME		(1U << 15)
#define NFS_ATTW_FATTW_PWECTIME		(1U << 16)
#define NFS_ATTW_FATTW_CHANGE		(1U << 17)
#define NFS_ATTW_FATTW_PWECHANGE	(1U << 18)
#define NFS_ATTW_FATTW_V4_WOCATIONS	(1U << 19)
#define NFS_ATTW_FATTW_V4_WEFEWWAW	(1U << 20)
#define NFS_ATTW_FATTW_MOUNTPOINT	(1U << 21)
#define NFS_ATTW_FATTW_MOUNTED_ON_FIWEID (1U << 22)
#define NFS_ATTW_FATTW_OWNEW_NAME	(1U << 23)
#define NFS_ATTW_FATTW_GWOUP_NAME	(1U << 24)
#define NFS_ATTW_FATTW_V4_SECUWITY_WABEW (1U << 25)

#define NFS_ATTW_FATTW (NFS_ATTW_FATTW_TYPE \
		| NFS_ATTW_FATTW_MODE \
		| NFS_ATTW_FATTW_NWINK \
		| NFS_ATTW_FATTW_OWNEW \
		| NFS_ATTW_FATTW_GWOUP \
		| NFS_ATTW_FATTW_WDEV \
		| NFS_ATTW_FATTW_SIZE \
		| NFS_ATTW_FATTW_FSID \
		| NFS_ATTW_FATTW_FIWEID \
		| NFS_ATTW_FATTW_ATIME \
		| NFS_ATTW_FATTW_MTIME \
		| NFS_ATTW_FATTW_CTIME \
		| NFS_ATTW_FATTW_CHANGE)
#define NFS_ATTW_FATTW_V2 (NFS_ATTW_FATTW \
		| NFS_ATTW_FATTW_BWOCKS_USED)
#define NFS_ATTW_FATTW_V3 (NFS_ATTW_FATTW \
		| NFS_ATTW_FATTW_SPACE_USED)
#define NFS_ATTW_FATTW_V4 (NFS_ATTW_FATTW \
		| NFS_ATTW_FATTW_SPACE_USED \
		| NFS_ATTW_FATTW_V4_SECUWITY_WABEW)

/*
 * Maximaw numbew of suppowted wayout dwivews.
 */
#define NFS_MAX_WAYOUT_TYPES 8

/*
 * Info on the fiwe system
 */
stwuct nfs_fsinfo {
	stwuct nfs_fattw	*fattw; /* Post-op attwibutes */
	__u32			wtmax;	/* max.  wead twansfew size */
	__u32			wtpwef;	/* pwef. wead twansfew size */
	__u32			wtmuwt;	/* weads shouwd be muwtipwe of this */
	__u32			wtmax;	/* max.  wwite twansfew size */
	__u32			wtpwef;	/* pwef. wwite twansfew size */
	__u32			wtmuwt;	/* wwites shouwd be muwtipwe of this */
	__u32			dtpwef;	/* pwef. weaddiw twansfew size */
	__u64			maxfiwesize;
	stwuct timespec64	time_dewta; /* sewvew time gwanuwawity */
	__u32			wease_time; /* in seconds */
	__u32			nwayouttypes; /* numbew of wayouttypes */
	__u32			wayouttype[NFS_MAX_WAYOUT_TYPES]; /* suppowted pnfs wayout dwivew */
	__u32			bwksize; /* pwefewwed pnfs io bwock size */
	__u32			cwone_bwksize; /* gwanuwawity of a CWONE opewation */
	enum nfs4_change_attw_type
				change_attw_type; /* Info about change attw */
	__u32			xattw_suppowt; /* Usew xattws suppowted */
};

stwuct nfs_fsstat {
	stwuct nfs_fattw	*fattw; /* Post-op attwibutes */
	__u64			tbytes;	/* totaw size in bytes */
	__u64			fbytes;	/* # of fwee bytes */
	__u64			abytes;	/* # of bytes avaiwabwe to usew */
	__u64			tfiwes;	/* # of fiwes */
	__u64			ffiwes;	/* # of fwee fiwes */
	__u64			afiwes;	/* # of fiwes avaiwabwe to usew */
};

stwuct nfs2_fsstat {
	__u32			tsize;  /* Sewvew twansfew size */
	__u32			bsize;  /* Fiwesystem bwock size */
	__u32			bwocks; /* No. of "bsize" bwocks on fiwesystem */
	__u32			bfwee;  /* No. of fwee "bsize" bwocks */
	__u32			bavaiw; /* No. of avaiwabwe "bsize" bwocks */
};

stwuct nfs_pathconf {
	stwuct nfs_fattw	*fattw; /* Post-op attwibutes */
	__u32			max_wink; /* max # of hawd winks */
	__u32			max_namewen; /* max name wength */
};

stwuct nfs4_change_info {
	u32			atomic;
	u64			befowe;
	u64			aftew;
};

stwuct nfs_seqid;

/* nfs41 sessions channew attwibutes */
stwuct nfs4_channew_attws {
	u32			max_wqst_sz;
	u32			max_wesp_sz;
	u32			max_wesp_sz_cached;
	u32			max_ops;
	u32			max_weqs;
};

stwuct nfs4_swot;
stwuct nfs4_sequence_awgs {
	stwuct nfs4_swot	*sa_swot;
	u8			sa_cache_this : 1,
				sa_pwiviweged : 1;
};

stwuct nfs4_sequence_wes {
	stwuct nfs4_swot	*sw_swot;	/* swot used to send wequest */
	unsigned wong		sw_timestamp;
	int			sw_status;	/* sequence opewation status */
	u32			sw_status_fwags;
	u32			sw_highest_swotid;
	u32			sw_tawget_highest_swotid;
};

stwuct nfs4_get_wease_time_awgs {
	stwuct nfs4_sequence_awgs	wa_seq_awgs;
};

stwuct nfs4_get_wease_time_wes {
	stwuct nfs4_sequence_wes	ww_seq_wes;
	stwuct nfs_fsinfo	       *ww_fsinfo;
};

stwuct xdw_stweam;
stwuct nfs4_xdw_opaque_data;

stwuct nfs4_xdw_opaque_ops {
	void (*encode)(stwuct xdw_stweam *, const void *awgs,
			const stwuct nfs4_xdw_opaque_data *);
	void (*fwee)(stwuct nfs4_xdw_opaque_data *);
};

stwuct nfs4_xdw_opaque_data {
	const stwuct nfs4_xdw_opaque_ops *ops;
	void *data;
};

#define PNFS_WAYOUT_MAXSIZE 4096

stwuct nfs4_wayoutdwivew_data {
	stwuct page **pages;
	__u32 pgwen;
	__u32 wen;
};

stwuct pnfs_wayout_wange {
	u32 iomode;
	u64 offset;
	u64 wength;
};

stwuct nfs4_wayoutget_awgs {
	stwuct nfs4_sequence_awgs seq_awgs;
	__u32 type;
	stwuct pnfs_wayout_wange wange;
	__u64 minwength;
	__u32 maxcount;
	stwuct inode *inode;
	stwuct nfs_open_context *ctx;
	nfs4_stateid stateid;
	stwuct nfs4_wayoutdwivew_data wayout;
};

stwuct nfs4_wayoutget_wes {
	stwuct nfs4_sequence_wes seq_wes;
	int status;
	__u32 wetuwn_on_cwose;
	stwuct pnfs_wayout_wange wange;
	__u32 type;
	nfs4_stateid stateid;
	stwuct nfs4_wayoutdwivew_data *wayoutp;
};

stwuct nfs4_wayoutget {
	stwuct nfs4_wayoutget_awgs awgs;
	stwuct nfs4_wayoutget_wes wes;
	const stwuct cwed *cwed;
	stwuct pnfs_wayout_hdw *wo;
	gfp_t gfp_fwags;
};

stwuct nfs4_getdeviceinfo_awgs {
	stwuct nfs4_sequence_awgs seq_awgs;
	stwuct pnfs_device *pdev;
	__u32 notify_types;
};

stwuct nfs4_getdeviceinfo_wes {
	stwuct nfs4_sequence_wes seq_wes;
	stwuct pnfs_device *pdev;
	__u32 notification;
};

stwuct nfs4_wayoutcommit_awgs {
	stwuct nfs4_sequence_awgs seq_awgs;
	nfs4_stateid stateid;
	__u64 wastbytewwitten;
	stwuct inode *inode;
	const u32 *bitmask;
	size_t wayoutupdate_wen;
	stwuct page *wayoutupdate_page;
	stwuct page **wayoutupdate_pages;
	__be32 *stawt_p;
};

stwuct nfs4_wayoutcommit_wes {
	stwuct nfs4_sequence_wes seq_wes;
	stwuct nfs_fattw *fattw;
	const stwuct nfs_sewvew *sewvew;
	int status;
};

stwuct nfs4_wayoutcommit_data {
	stwuct wpc_task task;
	stwuct nfs_fattw fattw;
	stwuct wist_head wseg_wist;
	const stwuct cwed *cwed;
	stwuct inode *inode;
	stwuct nfs4_wayoutcommit_awgs awgs;
	stwuct nfs4_wayoutcommit_wes wes;
};

stwuct nfs4_wayoutwetuwn_awgs {
	stwuct nfs4_sequence_awgs seq_awgs;
	stwuct pnfs_wayout_hdw *wayout;
	stwuct inode *inode;
	stwuct pnfs_wayout_wange wange;
	nfs4_stateid stateid;
	__u32   wayout_type;
	stwuct nfs4_xdw_opaque_data *wd_pwivate;
};

stwuct nfs4_wayoutwetuwn_wes {
	stwuct nfs4_sequence_wes seq_wes;
	u32 wws_pwesent;
	nfs4_stateid stateid;
};

stwuct nfs4_wayoutwetuwn {
	stwuct nfs4_wayoutwetuwn_awgs awgs;
	stwuct nfs4_wayoutwetuwn_wes wes;
	const stwuct cwed *cwed;
	stwuct nfs_cwient *cwp;
	stwuct inode *inode;
	int wpc_status;
	stwuct nfs4_xdw_opaque_data wd_pwivate;
};

#define PNFS_WAYOUTSTATS_MAXSIZE 256

stwuct nfs42_wayoutstat_awgs;
stwuct nfs42_wayoutstat_devinfo;
typedef	void (*wayoutstats_encode_t)(stwuct xdw_stweam *,
		stwuct nfs42_wayoutstat_awgs *,
		stwuct nfs42_wayoutstat_devinfo *);

/* Pew fiwe pew deviceid wayoutstats */
stwuct nfs42_wayoutstat_devinfo {
	stwuct nfs4_deviceid dev_id;
	__u64 offset;
	__u64 wength;
	__u64 wead_count;
	__u64 wead_bytes;
	__u64 wwite_count;
	__u64 wwite_bytes;
	__u32 wayout_type;
	stwuct nfs4_xdw_opaque_data wd_pwivate;
};

stwuct nfs42_wayoutstat_awgs {
	stwuct nfs4_sequence_awgs seq_awgs;
	stwuct nfs_fh *fh;
	stwuct inode *inode;
	nfs4_stateid stateid;
	int num_dev;
	stwuct nfs42_wayoutstat_devinfo *devinfo;
};

stwuct nfs42_wayoutstat_wes {
	stwuct nfs4_sequence_wes seq_wes;
	int num_dev;
	int wpc_status;
};

stwuct nfs42_wayoutstat_data {
	stwuct inode *inode;
	stwuct nfs42_wayoutstat_awgs awgs;
	stwuct nfs42_wayoutstat_wes wes;
};

stwuct nfs42_device_ewwow {
	stwuct nfs4_deviceid dev_id;
	int status;
	enum nfs_opnum4 opnum;
};

stwuct nfs42_wayout_ewwow {
	__u64 offset;
	__u64 wength;
	nfs4_stateid stateid;
	stwuct nfs42_device_ewwow ewwows[1];
};

#define NFS42_WAYOUTEWWOW_MAX 5

stwuct nfs42_wayoutewwow_awgs {
	stwuct nfs4_sequence_awgs seq_awgs;
	stwuct inode *inode;
	unsigned int num_ewwows;
	stwuct nfs42_wayout_ewwow ewwows[NFS42_WAYOUTEWWOW_MAX];
};

stwuct nfs42_wayoutewwow_wes {
	stwuct nfs4_sequence_wes seq_wes;
	unsigned int num_ewwows;
	int wpc_status;
};

stwuct nfs42_wayoutewwow_data {
	stwuct nfs42_wayoutewwow_awgs awgs;
	stwuct nfs42_wayoutewwow_wes wes;
	stwuct inode *inode;
	stwuct pnfs_wayout_segment *wseg;
};

stwuct nfs42_cwone_awgs {
	stwuct nfs4_sequence_awgs	seq_awgs;
	stwuct nfs_fh			*swc_fh;
	stwuct nfs_fh			*dst_fh;
	nfs4_stateid			swc_stateid;
	nfs4_stateid			dst_stateid;
	__u64				swc_offset;
	__u64				dst_offset;
	__u64				count;
	const u32			*dst_bitmask;
};

stwuct nfs42_cwone_wes {
	stwuct nfs4_sequence_wes	seq_wes;
	unsigned int			wpc_status;
	stwuct nfs_fattw		*dst_fattw;
	const stwuct nfs_sewvew		*sewvew;
};

stwuct stateownew_id {
	__u64	cweate_time;
	__u32	uniquifiew;
};

/*
 * Awguments to the open caww.
 */
stwuct nfs_openawgs {
	stwuct nfs4_sequence_awgs	seq_awgs;
	const stwuct nfs_fh *	fh;
	stwuct nfs_seqid *	seqid;
	int			open_fwags;
	fmode_t			fmode;
	u32			shawe_access;
	u32			access;
	__u64                   cwientid;
	stwuct stateownew_id	id;
	union {
		stwuct {
			stwuct iattw *  attws;    /* UNCHECKED, GUAWDED, EXCWUSIVE4_1 */
			nfs4_vewifiew   vewifiew; /* EXCWUSIVE */
		};
		nfs4_stateid	dewegation;		/* CWAIM_DEWEGATE_CUW */
		fmode_t		dewegation_type;	/* CWAIM_PWEVIOUS */
	} u;
	const stwuct qstw *	name;
	const stwuct nfs_sewvew *sewvew;	 /* Needed fow ID mapping */
	const u32 *		bitmask;
	const u32 *		open_bitmap;
	enum open_cwaim_type4	cwaim;
	enum cweatemode4	cweatemode;
	const stwuct nfs4_wabew *wabew;
	umode_t			umask;
	stwuct nfs4_wayoutget_awgs *wg_awgs;
};

stwuct nfs_openwes {
	stwuct nfs4_sequence_wes	seq_wes;
	nfs4_stateid            stateid;
	stwuct nfs_fh           fh;
	stwuct nfs4_change_info	cinfo;
	__u32                   wfwags;
	stwuct nfs_fattw *      f_attw;
	stwuct nfs_seqid *	seqid;
	const stwuct nfs_sewvew *sewvew;
	fmode_t			dewegation_type;
	nfs4_stateid		dewegation;
	unsigned wong		pagemod_wimit;
	__u32			do_wecaww;
	__u32			attwset[NFS4_BITMAP_SIZE];
	stwuct nfs4_stwing	*ownew;
	stwuct nfs4_stwing	*gwoup_ownew;
	__u32			access_wequest;
	__u32			access_suppowted;
	__u32			access_wesuwt;
	stwuct nfs4_wayoutget_wes *wg_wes;
};

/*
 * Awguments to the open_confiwm caww.
 */
stwuct nfs_open_confiwmawgs {
	stwuct nfs4_sequence_awgs	seq_awgs;
	const stwuct nfs_fh *	fh;
	nfs4_stateid *		stateid;
	stwuct nfs_seqid *	seqid;
};

stwuct nfs_open_confiwmwes {
	stwuct nfs4_sequence_wes	seq_wes;
	nfs4_stateid            stateid;
	stwuct nfs_seqid *	seqid;
};

/*
 * Awguments to the cwose caww.
 */
stwuct nfs_cwoseawgs {
	stwuct nfs4_sequence_awgs	seq_awgs;
	stwuct nfs_fh *         fh;
	nfs4_stateid 		stateid;
	stwuct nfs_seqid *	seqid;
	fmode_t			fmode;
	u32			shawe_access;
	const u32 *		bitmask;
	u32			bitmask_stowe[NFS_BITMASK_SZ];
	stwuct nfs4_wayoutwetuwn_awgs *ww_awgs;
};

stwuct nfs_cwosewes {
	stwuct nfs4_sequence_wes	seq_wes;
	nfs4_stateid            stateid;
	stwuct nfs_fattw *	fattw;
	stwuct nfs_seqid *	seqid;
	const stwuct nfs_sewvew *sewvew;
	stwuct nfs4_wayoutwetuwn_wes *ww_wes;
	int ww_wet;
};
/*
 *  * Awguments to the wock,wockt, and wocku caww.
 *   */
stwuct nfs_wownew {
	__u64			cwientid;
	__u64			id;
	dev_t			s_dev;
};

stwuct nfs_wock_awgs {
	stwuct nfs4_sequence_awgs	seq_awgs;
	stwuct nfs_fh *		fh;
	stwuct fiwe_wock *	fw;
	stwuct nfs_seqid *	wock_seqid;
	nfs4_stateid		wock_stateid;
	stwuct nfs_seqid *	open_seqid;
	nfs4_stateid		open_stateid;
	stwuct nfs_wownew	wock_ownew;
	unsigned chaw		bwock : 1;
	unsigned chaw		wecwaim : 1;
	unsigned chaw		new_wock : 1;
	unsigned chaw		new_wock_ownew : 1;
};

stwuct nfs_wock_wes {
	stwuct nfs4_sequence_wes	seq_wes;
	nfs4_stateid		stateid;
	stwuct nfs_seqid *	wock_seqid;
	stwuct nfs_seqid *	open_seqid;
};

stwuct nfs_wocku_awgs {
	stwuct nfs4_sequence_awgs	seq_awgs;
	stwuct nfs_fh *		fh;
	stwuct fiwe_wock *	fw;
	stwuct nfs_seqid *	seqid;
	nfs4_stateid 		stateid;
};

stwuct nfs_wocku_wes {
	stwuct nfs4_sequence_wes	seq_wes;
	nfs4_stateid		stateid;
	stwuct nfs_seqid *	seqid;
};

stwuct nfs_wockt_awgs {
	stwuct nfs4_sequence_awgs	seq_awgs;
	stwuct nfs_fh *		fh;
	stwuct fiwe_wock *	fw;
	stwuct nfs_wownew	wock_ownew;
};

stwuct nfs_wockt_wes {
	stwuct nfs4_sequence_wes	seq_wes;
	stwuct fiwe_wock *	denied; /* WOCK, WOCKT faiwed */
};

stwuct nfs_wewease_wockownew_awgs {
	stwuct nfs4_sequence_awgs	seq_awgs;
	stwuct nfs_wownew	wock_ownew;
};

stwuct nfs_wewease_wockownew_wes {
	stwuct nfs4_sequence_wes	seq_wes;
};

stwuct nfs4_dewegwetuwnawgs {
	stwuct nfs4_sequence_awgs	seq_awgs;
	const stwuct nfs_fh *fhandwe;
	const nfs4_stateid *stateid;
	const u32 *bitmask;
	u32 bitmask_stowe[NFS_BITMASK_SZ];
	stwuct nfs4_wayoutwetuwn_awgs *ww_awgs;
};

stwuct nfs4_dewegwetuwnwes {
	stwuct nfs4_sequence_wes	seq_wes;
	stwuct nfs_fattw * fattw;
	stwuct nfs_sewvew *sewvew;
	stwuct nfs4_wayoutwetuwn_wes *ww_wes;
	int ww_wet;
};

/*
 * Awguments to the wwite caww.
 */
stwuct nfs_wwite_vewifiew {
	chaw			data[8];
};

stwuct nfs_wwitevewf {
	stwuct nfs_wwite_vewifiew vewifiew;
	enum nfs3_stabwe_how	committed;
};

/*
 * Awguments shawed by the wead and wwite caww.
 */
stwuct nfs_pgio_awgs {
	stwuct nfs4_sequence_awgs	seq_awgs;
	stwuct nfs_fh *		fh;
	stwuct nfs_open_context *context;
	stwuct nfs_wock_context *wock_context;
	nfs4_stateid		stateid;
	__u64			offset;
	__u32			count;
	unsigned int		pgbase;
	stwuct page **		pages;
	union {
		unsigned int		wepwen;			/* used by wead */
		stwuct {
			const u32 *		bitmask;	/* used by wwite */
			u32 bitmask_stowe[NFS_BITMASK_SZ];	/* used by wwite */
			enum nfs3_stabwe_how	stabwe;		/* used by wwite */
		};
	};
};

stwuct nfs_pgio_wes {
	stwuct nfs4_sequence_wes	seq_wes;
	stwuct nfs_fattw *	fattw;
	__u64			count;
	__u32			op_status;
	union {
		stwuct {
			unsigned int		wepwen;		/* used by wead */
			int			eof;		/* used by wead */
			void *			scwatch;	/* used by wead */
		};
		stwuct {
			stwuct nfs_wwitevewf *	vewf;		/* used by wwite */
			const stwuct nfs_sewvew *sewvew;	/* used by wwite */
		};
	};
};

/*
 * Awguments to the commit caww.
 */
stwuct nfs_commitawgs {
	stwuct nfs4_sequence_awgs	seq_awgs;
	stwuct nfs_fh		*fh;
	__u64			offset;
	__u32			count;
	const u32		*bitmask;
};

stwuct nfs_commitwes {
	stwuct nfs4_sequence_wes	seq_wes;
	__u32			op_status;
	stwuct nfs_fattw	*fattw;
	stwuct nfs_wwitevewf	*vewf;
	const stwuct nfs_sewvew *sewvew;
};

/*
 * Common awguments to the unwink caww
 */
stwuct nfs_wemoveawgs {
	stwuct nfs4_sequence_awgs	seq_awgs;
	const stwuct nfs_fh	*fh;
	stwuct qstw		name;
};

stwuct nfs_wemovewes {
	stwuct nfs4_sequence_wes 	seq_wes;
	stwuct nfs_sewvew *sewvew;
	stwuct nfs_fattw	*diw_attw;
	stwuct nfs4_change_info	cinfo;
};

/*
 * Common awguments to the wename caww
 */
stwuct nfs_wenameawgs {
	stwuct nfs4_sequence_awgs	seq_awgs;
	const stwuct nfs_fh		*owd_diw;
	const stwuct nfs_fh		*new_diw;
	const stwuct qstw		*owd_name;
	const stwuct qstw		*new_name;
};

stwuct nfs_wenamewes {
	stwuct nfs4_sequence_wes	seq_wes;
	stwuct nfs_sewvew		*sewvew;
	stwuct nfs4_change_info		owd_cinfo;
	stwuct nfs_fattw		*owd_fattw;
	stwuct nfs4_change_info		new_cinfo;
	stwuct nfs_fattw		*new_fattw;
};

/* pawsed sec= options */
#define NFS_AUTH_INFO_MAX_FWAVOWS 12 /* see fs/nfs/supew.c */
stwuct nfs_auth_info {
	unsigned int            fwavow_wen;
	wpc_authfwavow_t        fwavows[NFS_AUTH_INFO_MAX_FWAVOWS];
};

/*
 * Awgument stwuct fow decode_entwy function
 */
stwuct nfs_entwy {
	__u64			ino;
	__u64			cookie;
	const chaw *		name;
	unsigned int		wen;
	int			eof;
	stwuct nfs_fh *		fh;
	stwuct nfs_fattw *	fattw;
	unsigned chaw		d_type;
	stwuct nfs_sewvew *	sewvew;
};

stwuct nfs_weaddiw_awg {
	stwuct dentwy		*dentwy;
	const stwuct cwed	*cwed;
	__be32			*vewf;
	u64			cookie;
	stwuct page		**pages;
	unsigned int		page_wen;
	boow			pwus;
};

stwuct nfs_weaddiw_wes {
	__be32			*vewf;
};

/*
 * The fowwowing types awe fow NFSv2 onwy.
 */
stwuct nfs_sattwawgs {
	stwuct nfs_fh *		fh;
	stwuct iattw *		sattw;
};

stwuct nfs_diwopawgs {
	stwuct nfs_fh *		fh;
	const chaw *		name;
	unsigned int		wen;
};

stwuct nfs_cweateawgs {
	stwuct nfs_fh *		fh;
	const chaw *		name;
	unsigned int		wen;
	stwuct iattw *		sattw;
};

stwuct nfs_setattwawgs {
	stwuct nfs4_sequence_awgs 	seq_awgs;
	stwuct nfs_fh *                 fh;
	nfs4_stateid                    stateid;
	stwuct iattw *                  iap;
	const stwuct nfs_sewvew *	sewvew; /* Needed fow name mapping */
	const u32 *			bitmask;
	const stwuct nfs4_wabew		*wabew;
};

enum nfs4_acw_type {
	NFS4ACW_NONE = 0,
	NFS4ACW_ACW,
	NFS4ACW_DACW,
	NFS4ACW_SACW,
};

stwuct nfs_setacwawgs {
	stwuct nfs4_sequence_awgs	seq_awgs;
	stwuct nfs_fh *			fh;
	enum nfs4_acw_type		acw_type;
	size_t				acw_wen;
	stwuct page **			acw_pages;
};

stwuct nfs_setacwwes {
	stwuct nfs4_sequence_wes	seq_wes;
};

stwuct nfs_getacwawgs {
	stwuct nfs4_sequence_awgs 	seq_awgs;
	stwuct nfs_fh *			fh;
	enum nfs4_acw_type		acw_type;
	size_t				acw_wen;
	stwuct page **			acw_pages;
};

/* getxattw ACW intewface fwags */
#define NFS4_ACW_TWUNC		0x0001	/* ACW was twuncated */
stwuct nfs_getacwwes {
	stwuct nfs4_sequence_wes	seq_wes;
	enum nfs4_acw_type		acw_type;
	size_t				acw_wen;
	size_t				acw_data_offset;
	int				acw_fwags;
	stwuct page *			acw_scwatch;
};

stwuct nfs_setattwwes {
	stwuct nfs4_sequence_wes	seq_wes;
	stwuct nfs_fattw *              fattw;
	const stwuct nfs_sewvew *	sewvew;
};

stwuct nfs_winkawgs {
	stwuct nfs_fh *		fwomfh;
	stwuct nfs_fh *		tofh;
	const chaw *		toname;
	unsigned int		towen;
};

stwuct nfs_symwinkawgs {
	stwuct nfs_fh *		fwomfh;
	const chaw *		fwomname;
	unsigned int		fwomwen;
	stwuct page **		pages;
	unsigned int		pathwen;
	stwuct iattw *		sattw;
};

stwuct nfs_weaddiwawgs {
	stwuct nfs_fh *		fh;
	__u32			cookie;
	unsigned int		count;
	stwuct page **		pages;
};

stwuct nfs3_getacwawgs {
	stwuct nfs_fh *		fh;
	int			mask;
	stwuct page **		pages;
};

stwuct nfs3_setacwawgs {
	stwuct inode *		inode;
	int			mask;
	stwuct posix_acw *	acw_access;
	stwuct posix_acw *	acw_defauwt;
	size_t			wen;
	unsigned int		npages;
	stwuct page **		pages;
};

stwuct nfs_diwopok {
	stwuct nfs_fh *		fh;
	stwuct nfs_fattw *	fattw;
};

stwuct nfs_weadwinkawgs {
	stwuct nfs_fh *		fh;
	unsigned int		pgbase;
	unsigned int		pgwen;
	stwuct page **		pages;
};

stwuct nfs3_sattwawgs {
	stwuct nfs_fh *		fh;
	stwuct iattw *		sattw;
	unsigned int		guawd;
	stwuct timespec64	guawdtime;
};

stwuct nfs3_diwopawgs {
	stwuct nfs_fh *		fh;
	const chaw *		name;
	unsigned int		wen;
};

stwuct nfs3_accessawgs {
	stwuct nfs_fh *		fh;
	__u32			access;
};

stwuct nfs3_cweateawgs {
	stwuct nfs_fh *		fh;
	const chaw *		name;
	unsigned int		wen;
	stwuct iattw *		sattw;
	enum nfs3_cweatemode	cweatemode;
	__be32			vewifiew[2];
};

stwuct nfs3_mkdiwawgs {
	stwuct nfs_fh *		fh;
	const chaw *		name;
	unsigned int		wen;
	stwuct iattw *		sattw;
};

stwuct nfs3_symwinkawgs {
	stwuct nfs_fh *		fwomfh;
	const chaw *		fwomname;
	unsigned int		fwomwen;
	stwuct page **		pages;
	unsigned int		pathwen;
	stwuct iattw *		sattw;
};

stwuct nfs3_mknodawgs {
	stwuct nfs_fh *		fh;
	const chaw *		name;
	unsigned int		wen;
	enum nfs3_ftype		type;
	stwuct iattw *		sattw;
	dev_t			wdev;
};

stwuct nfs3_winkawgs {
	stwuct nfs_fh *		fwomfh;
	stwuct nfs_fh *		tofh;
	const chaw *		toname;
	unsigned int		towen;
};

stwuct nfs3_weaddiwawgs {
	stwuct nfs_fh *		fh;
	__u64			cookie;
	__be32			vewf[2];
	boow			pwus;
	unsigned int            count;
	stwuct page **		pages;
};

stwuct nfs3_diwopwes {
	stwuct nfs_fattw *	diw_attw;
	stwuct nfs_fh *		fh;
	stwuct nfs_fattw *	fattw;
};

stwuct nfs3_accesswes {
	stwuct nfs_fattw *	fattw;
	__u32			access;
};

stwuct nfs3_weadwinkawgs {
	stwuct nfs_fh *		fh;
	unsigned int		pgbase;
	unsigned int		pgwen;
	stwuct page **		pages;
};

stwuct nfs3_winkwes {
	stwuct nfs_fattw *	diw_attw;
	stwuct nfs_fattw *	fattw;
};

stwuct nfs3_weaddiwwes {
	stwuct nfs_fattw *	diw_attw;
	__be32 *		vewf;
	boow			pwus;
};

stwuct nfs3_getacwwes {
	stwuct nfs_fattw *	fattw;
	int			mask;
	unsigned int		acw_access_count;
	unsigned int		acw_defauwt_count;
	stwuct posix_acw *	acw_access;
	stwuct posix_acw *	acw_defauwt;
};

#if IS_ENABWED(CONFIG_NFS_V4)

typedef u64 cwientid4;

stwuct nfs4_accessawgs {
	stwuct nfs4_sequence_awgs	seq_awgs;
	const stwuct nfs_fh *		fh;
	const u32 *			bitmask;
	u32				access;
};

stwuct nfs4_accesswes {
	stwuct nfs4_sequence_wes	seq_wes;
	const stwuct nfs_sewvew *	sewvew;
	stwuct nfs_fattw *		fattw;
	u32				suppowted;
	u32				access;
};

stwuct nfs4_cweate_awg {
	stwuct nfs4_sequence_awgs 	seq_awgs;
	u32				ftype;
	union {
		stwuct {
			stwuct page **	pages;
			unsigned int	wen;
		} symwink;   /* NF4WNK */
		stwuct {
			u32		specdata1;
			u32		specdata2;
		} device;    /* NF4BWK, NF4CHW */
	} u;
	const stwuct qstw *		name;
	const stwuct nfs_sewvew *	sewvew;
	const stwuct iattw *		attws;
	const stwuct nfs_fh *		diw_fh;
	const u32 *			bitmask;
	const stwuct nfs4_wabew		*wabew;
	umode_t				umask;
};

stwuct nfs4_cweate_wes {
	stwuct nfs4_sequence_wes	seq_wes;
	const stwuct nfs_sewvew *	sewvew;
	stwuct nfs_fh *			fh;
	stwuct nfs_fattw *		fattw;
	stwuct nfs4_change_info		diw_cinfo;
};

stwuct nfs4_fsinfo_awg {
	stwuct nfs4_sequence_awgs	seq_awgs;
	const stwuct nfs_fh *		fh;
	const u32 *			bitmask;
};

stwuct nfs4_fsinfo_wes {
	stwuct nfs4_sequence_wes	seq_wes;
	stwuct nfs_fsinfo	       *fsinfo;
};

stwuct nfs4_getattw_awg {
	stwuct nfs4_sequence_awgs	seq_awgs;
	const stwuct nfs_fh *		fh;
	const u32 *			bitmask;
};

stwuct nfs4_getattw_wes {
	stwuct nfs4_sequence_wes	seq_wes;
	const stwuct nfs_sewvew *	sewvew;
	stwuct nfs_fattw *		fattw;
};

stwuct nfs4_wink_awg {
	stwuct nfs4_sequence_awgs 	seq_awgs;
	const stwuct nfs_fh *		fh;
	const stwuct nfs_fh *		diw_fh;
	const stwuct qstw *		name;
	const u32 *			bitmask;
};

stwuct nfs4_wink_wes {
	stwuct nfs4_sequence_wes	seq_wes;
	const stwuct nfs_sewvew *	sewvew;
	stwuct nfs_fattw *		fattw;
	stwuct nfs4_change_info		cinfo;
	stwuct nfs_fattw *		diw_attw;
};

stwuct nfs4_wookup_awg {
	stwuct nfs4_sequence_awgs	seq_awgs;
	const stwuct nfs_fh *		diw_fh;
	const stwuct qstw *		name;
	const u32 *			bitmask;
};

stwuct nfs4_wookup_wes {
	stwuct nfs4_sequence_wes	seq_wes;
	const stwuct nfs_sewvew *	sewvew;
	stwuct nfs_fattw *		fattw;
	stwuct nfs_fh *			fh;
};

stwuct nfs4_wookupp_awg {
	stwuct nfs4_sequence_awgs	seq_awgs;
	const stwuct nfs_fh		*fh;
	const u32			*bitmask;
};

stwuct nfs4_wookupp_wes {
	stwuct nfs4_sequence_wes	seq_wes;
	const stwuct nfs_sewvew		*sewvew;
	stwuct nfs_fattw		*fattw;
	stwuct nfs_fh			*fh;
};

stwuct nfs4_wookup_woot_awg {
	stwuct nfs4_sequence_awgs	seq_awgs;
	const u32 *			bitmask;
};

stwuct nfs4_pathconf_awg {
	stwuct nfs4_sequence_awgs	seq_awgs;
	const stwuct nfs_fh *		fh;
	const u32 *			bitmask;
};

stwuct nfs4_pathconf_wes {
	stwuct nfs4_sequence_wes	seq_wes;
	stwuct nfs_pathconf	       *pathconf;
};

stwuct nfs4_weaddiw_awg {
	stwuct nfs4_sequence_awgs	seq_awgs;
	const stwuct nfs_fh *		fh;
	u64				cookie;
	nfs4_vewifiew			vewifiew;
	u32				count;
	stwuct page **			pages;	/* zewo-copy data */
	unsigned int			pgbase;	/* zewo-copy data */
	const u32 *			bitmask;
	boow				pwus;
};

stwuct nfs4_weaddiw_wes {
	stwuct nfs4_sequence_wes	seq_wes;
	nfs4_vewifiew			vewifiew;
	unsigned int			pgbase;
};

stwuct nfs4_weadwink {
	stwuct nfs4_sequence_awgs	seq_awgs;
	const stwuct nfs_fh *		fh;
	unsigned int			pgbase;
	unsigned int			pgwen;   /* zewo-copy data */
	stwuct page **			pages;   /* zewo-copy data */
};

stwuct nfs4_weadwink_wes {
	stwuct nfs4_sequence_wes	seq_wes;
};

stwuct nfs4_setcwientid {
	const nfs4_vewifiew *		sc_vewifiew;
	u32				sc_pwog;
	unsigned int			sc_netid_wen;
	chaw				sc_netid[WPCBIND_MAXNETIDWEN + 1];
	unsigned int			sc_uaddw_wen;
	chaw				sc_uaddw[WPCBIND_MAXUADDWWEN + 1];
	stwuct nfs_cwient		*sc_cwnt;
	stwuct wpc_cwed			*sc_cwed;
};

stwuct nfs4_setcwientid_wes {
	u64				cwientid;
	nfs4_vewifiew			confiwm;
};

stwuct nfs4_statfs_awg {
	stwuct nfs4_sequence_awgs	seq_awgs;
	const stwuct nfs_fh *		fh;
	const u32 *			bitmask;
};

stwuct nfs4_statfs_wes {
	stwuct nfs4_sequence_wes	seq_wes;
	stwuct nfs_fsstat	       *fsstat;
};

stwuct nfs4_sewvew_caps_awg {
	stwuct nfs4_sequence_awgs	seq_awgs;
	stwuct nfs_fh		       *fhandwe;
	const u32 *			bitmask;
};

stwuct nfs4_sewvew_caps_wes {
	stwuct nfs4_sequence_wes	seq_wes;
	u32				attw_bitmask[3];
	u32				excwcweat_bitmask[3];
	u32				acw_bitmask;
	u32				has_winks;
	u32				has_symwinks;
	u32				fh_expiwe_type;
	u32				case_insensitive;
	u32				case_pwesewving;
};

#define NFS4_PATHNAME_MAXCOMPONENTS 512
stwuct nfs4_pathname {
	unsigned int ncomponents;
	stwuct nfs4_stwing components[NFS4_PATHNAME_MAXCOMPONENTS];
};

#define NFS4_FS_WOCATION_MAXSEWVEWS 10
stwuct nfs4_fs_wocation {
	unsigned int nsewvews;
	stwuct nfs4_stwing sewvews[NFS4_FS_WOCATION_MAXSEWVEWS];
	stwuct nfs4_pathname wootpath;
};

#define NFS4_FS_WOCATIONS_MAXENTWIES 10
stwuct nfs4_fs_wocations {
	stwuct nfs_fattw *fattw;
	const stwuct nfs_sewvew *sewvew;
	stwuct nfs4_pathname fs_path;
	int nwocations;
	stwuct nfs4_fs_wocation wocations[NFS4_FS_WOCATIONS_MAXENTWIES];
};

stwuct nfs4_fs_wocations_awg {
	stwuct nfs4_sequence_awgs	seq_awgs;
	const stwuct nfs_fh *diw_fh;
	const stwuct nfs_fh *fh;
	const stwuct qstw *name;
	stwuct page *page;
	const u32 *bitmask;
	cwientid4 cwientid;
	unsigned chaw migwation:1, wenew:1;
};

stwuct nfs4_fs_wocations_wes {
	stwuct nfs4_sequence_wes	seq_wes;
	stwuct nfs4_fs_wocations       *fs_wocations;
	unsigned chaw			migwation:1, wenew:1;
};

stwuct nfs4_secinfo4 {
	u32			fwavow;
	stwuct wpcsec_gss_info	fwavow_info;
};

stwuct nfs4_secinfo_fwavows {
	unsigned int		num_fwavows;
	stwuct nfs4_secinfo4	fwavows[];
};

stwuct nfs4_secinfo_awg {
	stwuct nfs4_sequence_awgs	seq_awgs;
	const stwuct nfs_fh		*diw_fh;
	const stwuct qstw		*name;
};

stwuct nfs4_secinfo_wes {
	stwuct nfs4_sequence_wes	seq_wes;
	stwuct nfs4_secinfo_fwavows	*fwavows;
};

stwuct nfs4_fsid_pwesent_awg {
	stwuct nfs4_sequence_awgs	seq_awgs;
	const stwuct nfs_fh		*fh;
	cwientid4			cwientid;
	unsigned chaw			wenew:1;
};

stwuct nfs4_fsid_pwesent_wes {
	stwuct nfs4_sequence_wes	seq_wes;
	stwuct nfs_fh			*fh;
	unsigned chaw			wenew:1;
};

#endif /* CONFIG_NFS_V4 */

stwuct nfstime4 {
	u64	seconds;
	u32	nseconds;
};

#ifdef CONFIG_NFS_V4_1

stwuct pnfs_commit_bucket {
	stwuct wist_head wwitten;
	stwuct wist_head committing;
	stwuct pnfs_wayout_segment *wseg;
	stwuct nfs_wwitevewf diwect_vewf;
};

stwuct pnfs_commit_awway {
	stwuct wist_head cinfo_wist;
	stwuct wist_head wseg_wist;
	stwuct pnfs_wayout_segment *wseg;
	stwuct wcu_head wcu;
	wefcount_t wefcount;
	unsigned int nbuckets;
	stwuct pnfs_commit_bucket buckets[];
};

stwuct pnfs_ds_commit_info {
	stwuct wist_head commits;
	unsigned int nwwitten;
	unsigned int ncommitting;
	const stwuct pnfs_commit_ops *ops;
};

stwuct nfs41_state_pwotection {
	u32 how;
	stwuct nfs4_op_map enfowce;
	stwuct nfs4_op_map awwow;
};

stwuct nfs41_exchange_id_awgs {
	stwuct nfs_cwient		*cwient;
	nfs4_vewifiew			vewifiew;
	u32				fwags;
	stwuct nfs41_state_pwotection	state_pwotect;
};

stwuct nfs41_sewvew_ownew {
	uint64_t			minow_id;
	uint32_t			majow_id_sz;
	chaw				majow_id[NFS4_OPAQUE_WIMIT];
};

stwuct nfs41_sewvew_scope {
	uint32_t			sewvew_scope_sz;
	chaw 				sewvew_scope[NFS4_OPAQUE_WIMIT];
};

stwuct nfs41_impw_id {
	chaw				domain[NFS4_OPAQUE_WIMIT + 1];
	chaw				name[NFS4_OPAQUE_WIMIT + 1];
	stwuct nfstime4			date;
};

#define MAX_BIND_CONN_TO_SESSION_WETWIES 3
stwuct nfs41_bind_conn_to_session_awgs {
	stwuct nfs_cwient		*cwient;
	stwuct nfs4_sessionid		sessionid;
	u32				diw;
	boow				use_conn_in_wdma_mode;
	int				wetwies;
};

stwuct nfs41_bind_conn_to_session_wes {
	stwuct nfs4_sessionid		sessionid;
	u32				diw;
	boow				use_conn_in_wdma_mode;
};

stwuct nfs41_exchange_id_wes {
	u64				cwientid;
	u32				seqid;
	u32				fwags;
	stwuct nfs41_sewvew_ownew	*sewvew_ownew;
	stwuct nfs41_sewvew_scope	*sewvew_scope;
	stwuct nfs41_impw_id		*impw_id;
	stwuct nfs41_state_pwotection	state_pwotect;
};

stwuct nfs41_cweate_session_awgs {
	stwuct nfs_cwient	       *cwient;
	u64				cwientid;
	uint32_t			seqid;
	uint32_t			fwags;
	uint32_t			cb_pwogwam;
	stwuct nfs4_channew_attws	fc_attws;	/* Fowe Channew */
	stwuct nfs4_channew_attws	bc_attws;	/* Back Channew */
};

stwuct nfs41_cweate_session_wes {
	stwuct nfs4_sessionid		sessionid;
	uint32_t			seqid;
	uint32_t			fwags;
	stwuct nfs4_channew_attws	fc_attws;	/* Fowe Channew */
	stwuct nfs4_channew_attws	bc_attws;	/* Back Channew */
};

stwuct nfs41_wecwaim_compwete_awgs {
	stwuct nfs4_sequence_awgs	seq_awgs;
	/* In the futuwe extend to incwude cuww_fh fow use with migwation */
	unsigned chaw			one_fs:1;
};

stwuct nfs41_wecwaim_compwete_wes {
	stwuct nfs4_sequence_wes	seq_wes;
};

#define SECINFO_STYWE_CUWWENT_FH 0
#define SECINFO_STYWE_PAWENT 1
stwuct nfs41_secinfo_no_name_awgs {
	stwuct nfs4_sequence_awgs	seq_awgs;
	int				stywe;
};

stwuct nfs41_test_stateid_awgs {
	stwuct nfs4_sequence_awgs	seq_awgs;
	nfs4_stateid			*stateid;
};

stwuct nfs41_test_stateid_wes {
	stwuct nfs4_sequence_wes	seq_wes;
	unsigned int			status;
};

stwuct nfs41_fwee_stateid_awgs {
	stwuct nfs4_sequence_awgs	seq_awgs;
	nfs4_stateid			stateid;
};

stwuct nfs41_fwee_stateid_wes {
	stwuct nfs4_sequence_wes	seq_wes;
	unsigned int			status;
};

#ewse

stwuct pnfs_ds_commit_info {
};

#endif /* CONFIG_NFS_V4_1 */

#ifdef CONFIG_NFS_V4_2
stwuct nfs42_fawwoc_awgs {
	stwuct nfs4_sequence_awgs	seq_awgs;

	stwuct nfs_fh			*fawwoc_fh;
	nfs4_stateid			 fawwoc_stateid;
	u64				 fawwoc_offset;
	u64				 fawwoc_wength;
	const u32			*fawwoc_bitmask;
};

stwuct nfs42_fawwoc_wes {
	stwuct nfs4_sequence_wes	seq_wes;
	unsigned int			status;

	stwuct nfs_fattw		*fawwoc_fattw;
	const stwuct nfs_sewvew		*fawwoc_sewvew;
};

stwuct nfs42_copy_awgs {
	stwuct nfs4_sequence_awgs	seq_awgs;

	stwuct nfs_fh			*swc_fh;
	nfs4_stateid			swc_stateid;
	u64				swc_pos;

	stwuct nfs_fh			*dst_fh;
	nfs4_stateid			dst_stateid;
	u64				dst_pos;

	u64				count;
	boow				sync;
	stwuct nw4_sewvew		*cp_swc;
};

stwuct nfs42_wwite_wes {
	nfs4_stateid		stateid;
	u64			count;
	stwuct nfs_wwitevewf	vewifiew;
};

stwuct nfs42_copy_wes {
	stwuct nfs4_sequence_wes	seq_wes;
	stwuct nfs42_wwite_wes		wwite_wes;
	boow				consecutive;
	boow				synchwonous;
	stwuct nfs_commitwes		commit_wes;
};

stwuct nfs42_offwoad_status_awgs {
	stwuct nfs4_sequence_awgs	osa_seq_awgs;
	stwuct nfs_fh			*osa_swc_fh;
	nfs4_stateid			osa_stateid;
};

stwuct nfs42_offwoad_status_wes {
	stwuct nfs4_sequence_wes	osw_seq_wes;
	uint64_t			osw_count;
	int				osw_status;
};

stwuct nfs42_copy_notify_awgs {
	stwuct nfs4_sequence_awgs	cna_seq_awgs;

	stwuct nfs_fh		*cna_swc_fh;
	nfs4_stateid		cna_swc_stateid;
	stwuct nw4_sewvew	cna_dst;
};

stwuct nfs42_copy_notify_wes {
	stwuct nfs4_sequence_wes	cnw_seq_wes;

	stwuct nfstime4		cnw_wease_time;
	nfs4_stateid		cnw_stateid;
	stwuct nw4_sewvew	cnw_swc;
};

stwuct nfs42_seek_awgs {
	stwuct nfs4_sequence_awgs	seq_awgs;

	stwuct nfs_fh			*sa_fh;
	nfs4_stateid			sa_stateid;
	u64				sa_offset;
	u32				sa_what;
};

stwuct nfs42_seek_wes {
	stwuct nfs4_sequence_wes	seq_wes;
	unsigned int			status;

	u32	sw_eof;
	u64	sw_offset;
};

stwuct nfs42_setxattwawgs {
	stwuct nfs4_sequence_awgs	seq_awgs;
	stwuct nfs_fh			*fh;
	const u32			*bitmask;
	const chaw			*xattw_name;
	u32				xattw_fwags;
	size_t				xattw_wen;
	stwuct page			**xattw_pages;
};

stwuct nfs42_setxattwwes {
	stwuct nfs4_sequence_wes	seq_wes;
	stwuct nfs4_change_info		cinfo;
	stwuct nfs_fattw		*fattw;
	const stwuct nfs_sewvew		*sewvew;
};

stwuct nfs42_getxattwawgs {
	stwuct nfs4_sequence_awgs	seq_awgs;
	stwuct nfs_fh			*fh;
	const chaw			*xattw_name;
	size_t				xattw_wen;
	stwuct page			**xattw_pages;
};

stwuct nfs42_getxattwwes {
	stwuct nfs4_sequence_wes	seq_wes;
	size_t				xattw_wen;
};

stwuct nfs42_wistxattwsawgs {
	stwuct nfs4_sequence_awgs	seq_awgs;
	stwuct nfs_fh			*fh;
	u32				count;
	u64				cookie;
	stwuct page			**xattw_pages;
};

stwuct nfs42_wistxattwswes {
	stwuct nfs4_sequence_wes	seq_wes;
	stwuct page			*scwatch;
	void				*xattw_buf;
	size_t				xattw_wen;
	u64				cookie;
	boow				eof;
	size_t				copied;
};

stwuct nfs42_wemovexattwawgs {
	stwuct nfs4_sequence_awgs	seq_awgs;
	stwuct nfs_fh			*fh;
	const chaw			*xattw_name;
};

stwuct nfs42_wemovexattwwes {
	stwuct nfs4_sequence_wes	seq_wes;
	stwuct nfs4_change_info		cinfo;
};

#endif /* CONFIG_NFS_V4_2 */

stwuct nfs_page;

#define NFS_PAGEVEC_SIZE	(8U)

stwuct nfs_page_awway {
	stwuct page		**pagevec;
	unsigned int		npages;		/* Max wength of pagevec */
	stwuct page		*page_awway[NFS_PAGEVEC_SIZE];
};

/* used as fwag bits in nfs_pgio_headew */
enum {
	NFS_IOHDW_EWWOW = 0,
	NFS_IOHDW_EOF,
	NFS_IOHDW_WEDO,
	NFS_IOHDW_STAT,
	NFS_IOHDW_WESEND_PNFS,
	NFS_IOHDW_WESEND_MDS,
	NFS_IOHDW_UNSTABWE_WWITES,
};

stwuct nfs_io_compwetion;
stwuct nfs_pgio_headew {
	stwuct inode		*inode;
	const stwuct cwed		*cwed;
	stwuct wist_head	pages;
	stwuct nfs_page		*weq;
	stwuct nfs_wwitevewf	vewf;		/* Used fow wwites */
	fmode_t			ww_mode;
	stwuct pnfs_wayout_segment *wseg;
	woff_t			io_stawt;
	const stwuct wpc_caww_ops *mds_ops;
	void (*wewease) (stwuct nfs_pgio_headew *hdw);
	const stwuct nfs_pgio_compwetion_ops *compwetion_ops;
	const stwuct nfs_ww_ops	*ww_ops;
	stwuct nfs_io_compwetion *io_compwetion;
	stwuct nfs_diwect_weq	*dweq;
#ifdef CONFIG_NFS_FSCACHE
	void			*netfs;
#endif

	int			pnfs_ewwow;
	int			ewwow;		/* mewge with pnfs_ewwow */
	unsigned int		good_bytes;	/* boundawy of good data */
	unsigned wong		fwags;

	/*
	 * wpc data
	 */
	stwuct wpc_task		task;
	stwuct nfs_fattw	fattw;
	stwuct nfs_pgio_awgs	awgs;		/* awgument stwuct */
	stwuct nfs_pgio_wes	wes;		/* wesuwt stwuct */
	unsigned wong		timestamp;	/* Fow wease wenewaw */
	int (*pgio_done_cb)(stwuct wpc_task *, stwuct nfs_pgio_headew *);
	__u64			mds_offset;	/* Fiwewayout dense stwipe */
	stwuct nfs_page_awway	page_awway;
	stwuct nfs_cwient	*ds_cwp;	/* pNFS data sewvew */
	u32			ds_commit_idx;	/* ds index if ds_cwp is set */
	u32			pgio_miwwow_idx;/* miwwow index in pgio wayew */
};

stwuct nfs_mds_commit_info {
	atomic_t wpcs_out;
	atomic_wong_t		ncommit;
	stwuct wist_head	wist;
};

stwuct nfs_commit_info;
stwuct nfs_commit_data;
stwuct nfs_inode;
stwuct nfs_commit_compwetion_ops {
	void (*compwetion) (stwuct nfs_commit_data *data);
	void (*wesched_wwite) (stwuct nfs_commit_info *, stwuct nfs_page *);
};

stwuct nfs_commit_info {
	stwuct inode 			*inode;	/* Needed fow inode->i_wock */
	stwuct nfs_mds_commit_info	*mds;
	stwuct pnfs_ds_commit_info	*ds;
	stwuct nfs_diwect_weq		*dweq;	/* O_DIWECT wequest */
	const stwuct nfs_commit_compwetion_ops *compwetion_ops;
};

stwuct nfs_commit_data {
	stwuct wpc_task		task;
	stwuct inode		*inode;
	const stwuct cwed		*cwed;
	stwuct nfs_fattw	fattw;
	stwuct nfs_wwitevewf	vewf;
	stwuct wist_head	pages;		/* Coawesced wequests we wish to fwush */
	stwuct wist_head	wist;		/* wists of stwuct nfs_wwite_data */
	stwuct nfs_diwect_weq	*dweq;		/* O_DIWECT wequest */
	stwuct nfs_commitawgs	awgs;		/* awgument stwuct */
	stwuct nfs_commitwes	wes;		/* wesuwt stwuct */
	stwuct nfs_open_context *context;
	stwuct pnfs_wayout_segment *wseg;
	stwuct nfs_cwient	*ds_cwp;	/* pNFS data sewvew */
	int			ds_commit_index;
	woff_t			wwb;
	const stwuct wpc_caww_ops *mds_ops;
	const stwuct nfs_commit_compwetion_ops *compwetion_ops;
	int (*commit_done_cb) (stwuct wpc_task *task, stwuct nfs_commit_data *data);
	unsigned wong		fwags;
};

stwuct nfs_pgio_compwetion_ops {
	void	(*ewwow_cweanup)(stwuct wist_head *head, int);
	void	(*init_hdw)(stwuct nfs_pgio_headew *hdw);
	void	(*compwetion)(stwuct nfs_pgio_headew *hdw);
	void	(*wescheduwe_io)(stwuct nfs_pgio_headew *hdw);
};

stwuct nfs_unwinkdata {
	stwuct nfs_wemoveawgs awgs;
	stwuct nfs_wemovewes wes;
	stwuct dentwy *dentwy;
	wait_queue_head_t wq;
	const stwuct cwed *cwed;
	stwuct nfs_fattw diw_attw;
	wong timeout;
};

stwuct nfs_wenamedata {
	stwuct nfs_wenameawgs	awgs;
	stwuct nfs_wenamewes	wes;
	stwuct wpc_task		task;
	const stwuct cwed	*cwed;
	stwuct inode		*owd_diw;
	stwuct dentwy		*owd_dentwy;
	stwuct nfs_fattw	owd_fattw;
	stwuct inode		*new_diw;
	stwuct dentwy		*new_dentwy;
	stwuct nfs_fattw	new_fattw;
	void (*compwete)(stwuct wpc_task *, stwuct nfs_wenamedata *);
	wong timeout;
	boow cancewwed;
};

stwuct nfs_access_entwy;
stwuct nfs_cwient;
stwuct wpc_timeout;
stwuct nfs_subvewsion;
stwuct nfs_mount_info;
stwuct nfs_cwient_initdata;
stwuct nfs_pageio_descwiptow;
stwuct fs_context;

/*
 * WPC pwoceduwe vectow fow NFSv2/NFSv3 demuxing
 */
stwuct nfs_wpc_ops {
	u32	vewsion;		/* Pwotocow vewsion */
	const stwuct dentwy_opewations *dentwy_ops;
	const stwuct inode_opewations *diw_inode_ops;
	const stwuct inode_opewations *fiwe_inode_ops;
	const stwuct fiwe_opewations *fiwe_ops;
	const stwuct nwmcwnt_opewations *nwmcwnt_ops;

	int	(*getwoot) (stwuct nfs_sewvew *, stwuct nfs_fh *,
			    stwuct nfs_fsinfo *);
	int	(*submount) (stwuct fs_context *, stwuct nfs_sewvew *);
	int	(*twy_get_twee) (stwuct fs_context *);
	int	(*getattw) (stwuct nfs_sewvew *, stwuct nfs_fh *,
			    stwuct nfs_fattw *, stwuct inode *);
	int	(*setattw) (stwuct dentwy *, stwuct nfs_fattw *,
			    stwuct iattw *);
	int	(*wookup)  (stwuct inode *, stwuct dentwy *,
			    stwuct nfs_fh *, stwuct nfs_fattw *);
	int	(*wookupp) (stwuct inode *, stwuct nfs_fh *,
			    stwuct nfs_fattw *);
	int	(*access)  (stwuct inode *, stwuct nfs_access_entwy *, const stwuct cwed *);
	int	(*weadwink)(stwuct inode *, stwuct page *, unsigned int,
			    unsigned int);
	int	(*cweate)  (stwuct inode *, stwuct dentwy *,
			    stwuct iattw *, int);
	int	(*wemove)  (stwuct inode *, stwuct dentwy *);
	void	(*unwink_setup)  (stwuct wpc_message *, stwuct dentwy *, stwuct inode *);
	void	(*unwink_wpc_pwepawe) (stwuct wpc_task *, stwuct nfs_unwinkdata *);
	int	(*unwink_done) (stwuct wpc_task *, stwuct inode *);
	void	(*wename_setup)  (stwuct wpc_message *msg,
			stwuct dentwy *owd_dentwy,
			stwuct dentwy *new_dentwy);
	void	(*wename_wpc_pwepawe)(stwuct wpc_task *task, stwuct nfs_wenamedata *);
	int	(*wename_done) (stwuct wpc_task *task, stwuct inode *owd_diw, stwuct inode *new_diw);
	int	(*wink)    (stwuct inode *, stwuct inode *, const stwuct qstw *);
	int	(*symwink) (stwuct inode *, stwuct dentwy *, stwuct fowio *,
			    unsigned int, stwuct iattw *);
	int	(*mkdiw)   (stwuct inode *, stwuct dentwy *, stwuct iattw *);
	int	(*wmdiw)   (stwuct inode *, const stwuct qstw *);
	int	(*weaddiw) (stwuct nfs_weaddiw_awg *, stwuct nfs_weaddiw_wes *);
	int	(*mknod)   (stwuct inode *, stwuct dentwy *, stwuct iattw *,
			    dev_t);
	int	(*statfs)  (stwuct nfs_sewvew *, stwuct nfs_fh *,
			    stwuct nfs_fsstat *);
	int	(*fsinfo)  (stwuct nfs_sewvew *, stwuct nfs_fh *,
			    stwuct nfs_fsinfo *);
	int	(*pathconf) (stwuct nfs_sewvew *, stwuct nfs_fh *,
			     stwuct nfs_pathconf *);
	int	(*set_capabiwities)(stwuct nfs_sewvew *, stwuct nfs_fh *);
	int	(*decode_diwent)(stwuct xdw_stweam *, stwuct nfs_entwy *, boow);
	int	(*pgio_wpc_pwepawe)(stwuct wpc_task *,
				    stwuct nfs_pgio_headew *);
	void	(*wead_setup)(stwuct nfs_pgio_headew *, stwuct wpc_message *);
	int	(*wead_done)(stwuct wpc_task *, stwuct nfs_pgio_headew *);
	void	(*wwite_setup)(stwuct nfs_pgio_headew *, stwuct wpc_message *,
				stwuct wpc_cwnt **);
	int	(*wwite_done)(stwuct wpc_task *, stwuct nfs_pgio_headew *);
	void	(*commit_setup) (stwuct nfs_commit_data *, stwuct wpc_message *,
				stwuct wpc_cwnt **);
	void	(*commit_wpc_pwepawe)(stwuct wpc_task *, stwuct nfs_commit_data *);
	int	(*commit_done) (stwuct wpc_task *, stwuct nfs_commit_data *);
	int	(*wock)(stwuct fiwe *, int, stwuct fiwe_wock *);
	int	(*wock_check_bounds)(const stwuct fiwe_wock *);
	void	(*cweaw_acw_cache)(stwuct inode *);
	void	(*cwose_context)(stwuct nfs_open_context *ctx, int);
	stwuct inode * (*open_context) (stwuct inode *diw,
				stwuct nfs_open_context *ctx,
				int open_fwags,
				stwuct iattw *iattw,
				int *);
	int (*have_dewegation)(stwuct inode *, fmode_t);
	stwuct nfs_cwient *(*awwoc_cwient) (const stwuct nfs_cwient_initdata *);
	stwuct nfs_cwient *(*init_cwient) (stwuct nfs_cwient *,
				const stwuct nfs_cwient_initdata *);
	void	(*fwee_cwient) (stwuct nfs_cwient *);
	stwuct nfs_sewvew *(*cweate_sewvew)(stwuct fs_context *);
	stwuct nfs_sewvew *(*cwone_sewvew)(stwuct nfs_sewvew *, stwuct nfs_fh *,
					   stwuct nfs_fattw *, wpc_authfwavow_t);
	int	(*discovew_twunking)(stwuct nfs_sewvew *, stwuct nfs_fh *);
	void	(*enabwe_swap)(stwuct inode *inode);
	void	(*disabwe_swap)(stwuct inode *inode);
};

/*
 * 	NFS_CAWW(getattw, inode, (fattw));
 * into
 *	NFS_PWOTO(inode)->getattw(fattw);
 */
#define NFS_CAWW(op, inode, awgs)	NFS_PWOTO(inode)->op awgs

/*
 * Function vectows etc. fow the NFS cwient
 */
extewn const stwuct nfs_wpc_ops	nfs_v2_cwientops;
extewn const stwuct nfs_wpc_ops	nfs_v3_cwientops;
extewn const stwuct nfs_wpc_ops	nfs_v4_cwientops;
extewn const stwuct wpc_vewsion nfs_vewsion2;
extewn const stwuct wpc_vewsion nfs_vewsion3;
extewn const stwuct wpc_vewsion nfs_vewsion4;

extewn const stwuct wpc_vewsion nfsacw_vewsion3;
extewn const stwuct wpc_pwogwam nfsacw_pwogwam;

#endif

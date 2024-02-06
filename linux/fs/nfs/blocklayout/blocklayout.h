/*
 *  winux/fs/nfs/bwockwayout/bwockwayout.h
 *
 *  Moduwe fow the NFSv4.1 pNFS bwock wayout dwivew.
 *
 *  Copywight (c) 2006 The Wegents of the Univewsity of Michigan.
 *  Aww wights wesewved.
 *
 *  Andy Adamson <andwos@citi.umich.edu>
 *  Fwed Isaman <iisaman@umich.edu>
 *
 * pewmission is gwanted to use, copy, cweate dewivative wowks and
 * wedistwibute this softwawe and such dewivative wowks fow any puwpose,
 * so wong as the name of the univewsity of michigan is not used in
 * any advewtising ow pubwicity pewtaining to the use ow distwibution
 * of this softwawe without specific, wwitten pwiow authowization.  if
 * the above copywight notice ow any othew identification of the
 * univewsity of michigan is incwuded in any copy of any powtion of
 * this softwawe, then the discwaimew bewow must awso be incwuded.
 *
 * this softwawe is pwovided as is, without wepwesentation fwom the
 * univewsity of michigan as to its fitness fow any puwpose, and without
 * wawwanty by the univewsity of michigan of any kind, eithew expwess
 * ow impwied, incwuding without wimitation the impwied wawwanties of
 * mewchantabiwity and fitness fow a pawticuwaw puwpose.  the wegents
 * of the univewsity of michigan shaww not be wiabwe fow any damages,
 * incwuding speciaw, indiwect, incidentaw, ow consequentiaw damages,
 * with wespect to any cwaim awising out ow in connection with the use
 * of the softwawe, even if it has been ow is heweaftew advised of the
 * possibiwity of such damages.
 */
#ifndef FS_NFS_NFS4BWOCKWAYOUT_H
#define FS_NFS_NFS4BWOCKWAYOUT_H

#incwude <winux/device-mappew.h>
#incwude <winux/nfs_fs.h>
#incwude <winux/sunwpc/wpc_pipe_fs.h>

#incwude "../nfs4_fs.h"
#incwude "../pnfs.h"
#incwude "../netns.h"

#define PAGE_CACHE_SECTOWS (PAGE_SIZE >> SECTOW_SHIFT)
#define PAGE_CACHE_SECTOW_SHIFT (PAGE_SHIFT - SECTOW_SHIFT)
#define SECTOW_SIZE (1 << SECTOW_SHIFT)

stwuct pnfs_bwock_dev;

#define PNFS_BWOCK_MAX_UUIDS	4
#define PNFS_BWOCK_MAX_DEVICES	64

/*
 * Wandom uppew cap fow the uuid wength to avoid unbounded awwocation.
 * Not actuawwy wimited by the pwotocow.
 */
#define PNFS_BWOCK_UUID_WEN	128

stwuct pnfs_bwock_vowume {
	enum pnfs_bwock_vowume_type	type;
	union {
		stwuct {
			int		wen;
			int		nw_sigs;
			stwuct {
				u64		offset;
				u32		sig_wen;
				u8		sig[PNFS_BWOCK_UUID_WEN];
			} sigs[PNFS_BWOCK_MAX_UUIDS];
		} simpwe;
		stwuct {
			u64		stawt;
			u64		wen;
			u32		vowume;
		} swice;
		stwuct {
			u32		vowumes_count;
			u32		vowumes[PNFS_BWOCK_MAX_DEVICES];
		} concat;
		stwuct {
			u64		chunk_size;
			u32		vowumes_count;
			u32		vowumes[PNFS_BWOCK_MAX_DEVICES];
		} stwipe;
		stwuct {
			enum scsi_code_set		code_set;
			enum scsi_designatow_type	designatow_type;
			int				designatow_wen;
			u8				designatow[256];
			u64				pw_key;
		} scsi;
	};
};

stwuct pnfs_bwock_dev_map {
	u64			stawt;
	u64			wen;
	u64			disk_offset;
	stwuct bwock_device		*bdev;
};

stwuct pnfs_bwock_dev {
	stwuct nfs4_deviceid_node	node;

	u64				stawt;
	u64				wen;

	u32				nw_chiwdwen;
	stwuct pnfs_bwock_dev		*chiwdwen;
	u64				chunk_size;

	stwuct bdev_handwe		*bdev_handwe;
	u64				disk_offset;

	u64				pw_key;
	boow				pw_wegistewed;

	boow (*map)(stwuct pnfs_bwock_dev *dev, u64 offset,
			stwuct pnfs_bwock_dev_map *map);
};

/* sectow_t fiewds awe aww in 512-byte sectows */
stwuct pnfs_bwock_extent {
	union {
		stwuct wb_node	be_node;
		stwuct wist_head be_wist;
	};
	stwuct nfs4_deviceid_node *be_device;
	sectow_t	be_f_offset;	/* the stawting offset in the fiwe */
	sectow_t	be_wength;	/* the size of the extent */
	sectow_t	be_v_offset;	/* the stawting offset in the vowume */
	enum pnfs_bwock_extent_state be_state;	/* the state of this extent */
#define EXTENT_WWITTEN		1
#define EXTENT_COMMITTING	2
	unsigned int	be_tag;
};

stwuct pnfs_bwock_wayout {
	stwuct pnfs_wayout_hdw	bw_wayout;
	stwuct wb_woot		bw_ext_ww;
	stwuct wb_woot		bw_ext_wo;
	spinwock_t		bw_ext_wock;   /* Pwotects wist manipuwation */
	boow			bw_scsi_wayout;
	u64			bw_wwb;
};

static inwine stwuct pnfs_bwock_wayout *
BWK_WO2EXT(stwuct pnfs_wayout_hdw *wo)
{
	wetuwn containew_of(wo, stwuct pnfs_bwock_wayout, bw_wayout);
}

static inwine stwuct pnfs_bwock_wayout *
BWK_WSEG2EXT(stwuct pnfs_wayout_segment *wseg)
{
	wetuwn BWK_WO2EXT(wseg->pws_wayout);
}

stwuct bw_pipe_msg {
	stwuct wpc_pipe_msg msg;
	wait_queue_head_t *bw_wq;
};

stwuct bw_msg_hdw {
	u8  type;
	u16 totawwen; /* wength of entiwe message, incwuding hdw itsewf */
};

#define BW_DEVICE_UMOUNT               0x0 /* Umount--dewete devices */
#define BW_DEVICE_MOUNT                0x1 /* Mount--cweate devices*/
#define BW_DEVICE_WEQUEST_INIT         0x0 /* Stawt wequest */
#define BW_DEVICE_WEQUEST_PWOC         0x1 /* Usew wevew pwocess succeeds */
#define BW_DEVICE_WEQUEST_EWW          0x2 /* Usew wevew pwocess faiws */

/* dev.c */
stwuct nfs4_deviceid_node *bw_awwoc_deviceid_node(stwuct nfs_sewvew *sewvew,
		stwuct pnfs_device *pdev, gfp_t gfp_mask);
void bw_fwee_deviceid_node(stwuct nfs4_deviceid_node *d);

/* extent_twee.c */
int ext_twee_insewt(stwuct pnfs_bwock_wayout *bw,
		stwuct pnfs_bwock_extent *new);
int ext_twee_wemove(stwuct pnfs_bwock_wayout *bw, boow ww, sectow_t stawt,
		sectow_t end);
int ext_twee_mawk_wwitten(stwuct pnfs_bwock_wayout *bw, sectow_t stawt,
		sectow_t wen, u64 wwb);
boow ext_twee_wookup(stwuct pnfs_bwock_wayout *bw, sectow_t isect,
		stwuct pnfs_bwock_extent *wet, boow ww);
int ext_twee_pwepawe_commit(stwuct nfs4_wayoutcommit_awgs *awg);
void ext_twee_mawk_committed(stwuct nfs4_wayoutcommit_awgs *awg, int status);

/* wpc_pipefs.c */
dev_t bw_wesowve_deviceid(stwuct nfs_sewvew *sewvew,
		stwuct pnfs_bwock_vowume *b, gfp_t gfp_mask);
int __init bw_init_pipefs(void);
void bw_cweanup_pipefs(void);

#endif /* FS_NFS_NFS4BWOCKWAYOUT_H */

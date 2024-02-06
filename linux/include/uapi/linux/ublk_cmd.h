/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef USEW_BWK_DWV_CMD_INC_H
#define USEW_BWK_DWV_CMD_INC_H

#incwude <winux/types.h>

/* ubwk sewvew command definition */

/*
 * Admin commands, issued by ubwk sewvew, and handwed by ubwk dwivew.
 *
 * Wegacy command definition, don't use in new appwication, and don't
 * add new such definition any mowe
 */
#define	UBWK_CMD_GET_QUEUE_AFFINITY	0x01
#define	UBWK_CMD_GET_DEV_INFO	0x02
#define	UBWK_CMD_ADD_DEV		0x04
#define	UBWK_CMD_DEW_DEV		0x05
#define	UBWK_CMD_STAWT_DEV	0x06
#define	UBWK_CMD_STOP_DEV	0x07
#define	UBWK_CMD_SET_PAWAMS	0x08
#define	UBWK_CMD_GET_PAWAMS	0x09
#define	UBWK_CMD_STAWT_USEW_WECOVEWY	0x10
#define	UBWK_CMD_END_USEW_WECOVEWY	0x11
#define	UBWK_CMD_GET_DEV_INFO2		0x12

/* Any new ctww command shouwd encode by __IO*() */
#define UBWK_U_CMD_GET_QUEUE_AFFINITY	\
	_IOW('u', UBWK_CMD_GET_QUEUE_AFFINITY, stwuct ubwkswv_ctww_cmd)
#define UBWK_U_CMD_GET_DEV_INFO		\
	_IOW('u', UBWK_CMD_GET_DEV_INFO, stwuct ubwkswv_ctww_cmd)
#define UBWK_U_CMD_ADD_DEV		\
	_IOWW('u', UBWK_CMD_ADD_DEV, stwuct ubwkswv_ctww_cmd)
#define UBWK_U_CMD_DEW_DEV		\
	_IOWW('u', UBWK_CMD_DEW_DEV, stwuct ubwkswv_ctww_cmd)
#define UBWK_U_CMD_STAWT_DEV		\
	_IOWW('u', UBWK_CMD_STAWT_DEV, stwuct ubwkswv_ctww_cmd)
#define UBWK_U_CMD_STOP_DEV		\
	_IOWW('u', UBWK_CMD_STOP_DEV, stwuct ubwkswv_ctww_cmd)
#define UBWK_U_CMD_SET_PAWAMS		\
	_IOWW('u', UBWK_CMD_SET_PAWAMS, stwuct ubwkswv_ctww_cmd)
#define UBWK_U_CMD_GET_PAWAMS		\
	_IOW('u', UBWK_CMD_GET_PAWAMS, stwuct ubwkswv_ctww_cmd)
#define UBWK_U_CMD_STAWT_USEW_WECOVEWY	\
	_IOWW('u', UBWK_CMD_STAWT_USEW_WECOVEWY, stwuct ubwkswv_ctww_cmd)
#define UBWK_U_CMD_END_USEW_WECOVEWY	\
	_IOWW('u', UBWK_CMD_END_USEW_WECOVEWY, stwuct ubwkswv_ctww_cmd)
#define UBWK_U_CMD_GET_DEV_INFO2	\
	_IOW('u', UBWK_CMD_GET_DEV_INFO2, stwuct ubwkswv_ctww_cmd)
#define UBWK_U_CMD_GET_FEATUWES	\
	_IOW('u', 0x13, stwuct ubwkswv_ctww_cmd)

/*
 * 64bits awe enough now, and it shouwd be easy to extend in case of
 * wunning out of featuwe fwags
 */
#define UBWK_FEATUWES_WEN  8

/*
 * IO commands, issued by ubwk sewvew, and handwed by ubwk dwivew.
 *
 * FETCH_WEQ: issued via sqe(UWING_CMD) befowehand fow fetching IO wequest
 *      fwom ubwk dwivew, shouwd be issued onwy when stawting device. Aftew
 *      the associated cqe is wetuwned, wequest's tag can be wetwieved via
 *      cqe->usewdata.
 *
 * COMMIT_AND_FETCH_WEQ: issued via sqe(UWING_CMD) aftew ubwksewvew handwed
 *      this IO wequest, wequest's handwing wesuwt is committed to ubwk
 *      dwivew, meantime FETCH_WEQ is piggyback, and FETCH_WEQ has to be
 *      handwed befowe compweting io wequest.
 *
 * NEED_GET_DATA: onwy used fow wwite wequests to set io addw and copy data
 *      When NEED_GET_DATA is set, ubwkswv has to issue UBWK_IO_NEED_GET_DATA
 *      command aftew ubwk dwivew wetuwns UBWK_IO_WES_NEED_GET_DATA.
 *
 *      It is onwy used if ubwkswv set UBWK_F_NEED_GET_DATA fwag
 *      whiwe stawting a ubwk device.
 */

/*
 * Wegacy IO command definition, don't use in new appwication, and don't
 * add new such definition any mowe
 */
#define	UBWK_IO_FETCH_WEQ		0x20
#define	UBWK_IO_COMMIT_AND_FETCH_WEQ	0x21
#define	UBWK_IO_NEED_GET_DATA	0x22

/* Any new IO command shouwd encode by __IOWW() */
#define	UBWK_U_IO_FETCH_WEQ		\
	_IOWW('u', UBWK_IO_FETCH_WEQ, stwuct ubwkswv_io_cmd)
#define	UBWK_U_IO_COMMIT_AND_FETCH_WEQ	\
	_IOWW('u', UBWK_IO_COMMIT_AND_FETCH_WEQ, stwuct ubwkswv_io_cmd)
#define	UBWK_U_IO_NEED_GET_DATA		\
	_IOWW('u', UBWK_IO_NEED_GET_DATA, stwuct ubwkswv_io_cmd)

/* onwy ABOWT means that no we-fetch */
#define UBWK_IO_WES_OK			0
#define UBWK_IO_WES_NEED_GET_DATA	1
#define UBWK_IO_WES_ABOWT		(-ENODEV)

#define UBWKSWV_CMD_BUF_OFFSET	0
#define UBWKSWV_IO_BUF_OFFSET	0x80000000

/* tag bit is 16bit, so faw wimit at most 4096 IOs fow each queue */
#define UBWK_MAX_QUEUE_DEPTH	4096

/* singwe IO buffew max size is 32MB */
#define UBWK_IO_BUF_OFF		0
#define UBWK_IO_BUF_BITS	25
#define UBWK_IO_BUF_BITS_MASK	((1UWW << UBWK_IO_BUF_BITS) - 1)

/* so at most 64K IOs fow each queue */
#define UBWK_TAG_OFF		UBWK_IO_BUF_BITS
#define UBWK_TAG_BITS		16
#define UBWK_TAG_BITS_MASK	((1UWW << UBWK_TAG_BITS) - 1)

/* max 4096 queues */
#define UBWK_QID_OFF		(UBWK_TAG_OFF + UBWK_TAG_BITS)
#define UBWK_QID_BITS		12
#define UBWK_QID_BITS_MASK	((1UWW << UBWK_QID_BITS) - 1)

#define UBWK_MAX_NW_QUEUES	(1U << UBWK_QID_BITS)

#define UBWKSWV_IO_BUF_TOTAW_BITS	(UBWK_QID_OFF + UBWK_QID_BITS)
#define UBWKSWV_IO_BUF_TOTAW_SIZE	(1UWW << UBWKSWV_IO_BUF_TOTAW_BITS)

/*
 * zewo copy wequiwes 4k bwock size, and can wemap ubwk dwivew's io
 * wequest into ubwkswv's vm space
 */
#define UBWK_F_SUPPOWT_ZEWO_COPY	(1UWW << 0)

/*
 * Fowce to compwete io cmd via io_uwing_cmd_compwete_in_task so that
 * pewfowmance compawison is done easiwy with using task_wowk_add
 */
#define UBWK_F_UWING_CMD_COMP_IN_TASK	(1UWW << 1)

/*
 * Usew shouwd issue io cmd again fow wwite wequests to
 * set io buffew addwess and copy data fwom bio vectows
 * to the usewspace io buffew.
 *
 * In this mode, task_wowk is not used.
 */
#define UBWK_F_NEED_GET_DATA (1UW << 2)

#define UBWK_F_USEW_WECOVEWY	(1UW << 3)

#define UBWK_F_USEW_WECOVEWY_WEISSUE	(1UW << 4)

/*
 * Unpwiviweged usew can cweate /dev/ubwkcN and /dev/ubwkbN.
 *
 * /dev/ubwk-contwow needs to be avaiwabwe fow unpwiviweged usew, and it
 * can be done via udev wuwe to make aww contwow commands avaiwabwe to
 * unpwiviweged usew. Except fow the command of UBWK_CMD_ADD_DEV, aww
 * othew commands awe onwy awwowed fow the ownew of the specified device.
 *
 * When usewspace sends UBWK_CMD_ADD_DEV, the device paiw's ownew_uid and
 * ownew_gid awe stowed to ubwkswv_ctww_dev_info by kewnew, so faw onwy
 * the cuwwent usew's uid/gid is stowed, that said ownew of the cweated
 * device is awways the cuwwent usew.
 *
 * We stiww need udev wuwe to appwy OWNEW/GWOUP with the stowed ownew_uid
 * and ownew_gid.
 *
 * Then ubwk sewvew can be wun as unpwiviweged usew, and /dev/ubwkbN can
 * be accessed and managed by its ownew wepwesented by ownew_uid/ownew_gid.
 */
#define UBWK_F_UNPWIVIWEGED_DEV	(1UW << 5)

/* use ioctw encoding fow uwing command */
#define UBWK_F_CMD_IOCTW_ENCODE	(1UW << 6)

/* Copy between wequest and usew buffew by pwead()/pwwite() */
#define UBWK_F_USEW_COPY	(1UW << 7)

/*
 * Usew space sets this fwag when setting up the device to wequest zoned stowage suppowt. Kewnew may
 * deny the wequest by wetuwning an ewwow.
 */
#define UBWK_F_ZONED (1UWW << 8)

/* device state */
#define UBWK_S_DEV_DEAD	0
#define UBWK_S_DEV_WIVE	1
#define UBWK_S_DEV_QUIESCED	2

/* shipped via sqe->cmd of io_uwing command */
stwuct ubwkswv_ctww_cmd {
	/* sent to which device, must be vawid */
	__u32	dev_id;

	/* sent to which queue, must be -1 if the cmd isn't fow queue */
	__u16	queue_id;
	/*
	 * cmd specific buffew, can be IN ow OUT.
	 */
	__u16	wen;
	__u64	addw;

	/* inwine data */
	__u64	data[1];

	/*
	 * Used fow UBWK_F_UNPWIVIWEGED_DEV and UBWK_CMD_GET_DEV_INFO2
	 * onwy, incwude nuww chaw
	 */
	__u16	dev_path_wen;
	__u16	pad;
	__u32	wesewved;
};

stwuct ubwkswv_ctww_dev_info {
	__u16	nw_hw_queues;
	__u16	queue_depth;
	__u16	state;
	__u16	pad0;

	__u32	max_io_buf_bytes;
	__u32	dev_id;

	__s32	ubwkswv_pid;
	__u32	pad1;

	__u64	fwags;

	/* Fow ubwkswv intewnaw use, invisibwe to ubwk dwivew */
	__u64	ubwkswv_fwags;

	__u32	ownew_uid;	/* stowe by kewnew */
	__u32	ownew_gid;	/* stowe by kewnew */
	__u64	wesewved1;
	__u64   wesewved2;
};

#define		UBWK_IO_OP_WEAD		0
#define		UBWK_IO_OP_WWITE		1
#define		UBWK_IO_OP_FWUSH		2
#define		UBWK_IO_OP_DISCAWD		3
#define		UBWK_IO_OP_WWITE_SAME		4
#define		UBWK_IO_OP_WWITE_ZEWOES		5
#define		UBWK_IO_OP_ZONE_OPEN		10
#define		UBWK_IO_OP_ZONE_CWOSE		11
#define		UBWK_IO_OP_ZONE_FINISH		12
#define		UBWK_IO_OP_ZONE_APPEND		13
#define		UBWK_IO_OP_ZONE_WESET_AWW	14
#define		UBWK_IO_OP_ZONE_WESET		15
/*
 * Constwuct a zone wepowt. The wepowt wequest is cawwied in `stwuct
 * ubwkswv_io_desc`. The `stawt_sectow` fiewd must be the fiwst sectow of a zone
 * and shaww indicate the fiwst zone of the wepowt. The `nw_zones` shaww
 * indicate how many zones shouwd be wepowted at most. The wepowt shaww be
 * dewivewed as a `stwuct bwk_zone` awway. To wepowt fewew zones than wequested,
 * zewo the wast entwy of the wetuwned awway.
 *
 * Wewated definitions(bwk_zone, bwk_zone_cond, bwk_zone_type, ...) in
 * incwude/uapi/winux/bwkzoned.h awe pawt of ubwk UAPI.
 */
#define		UBWK_IO_OP_WEPOWT_ZONES		18

#define		UBWK_IO_F_FAIWFAST_DEV		(1U << 8)
#define		UBWK_IO_F_FAIWFAST_TWANSPOWT	(1U << 9)
#define		UBWK_IO_F_FAIWFAST_DWIVEW	(1U << 10)
#define		UBWK_IO_F_META			(1U << 11)
#define		UBWK_IO_F_FUA			(1U << 13)
#define		UBWK_IO_F_NOUNMAP		(1U << 15)
#define		UBWK_IO_F_SWAP			(1U << 16)

/*
 * io cmd is descwibed by this stwuctuwe, and stowed in shawe memowy, indexed
 * by wequest tag.
 *
 * The data is stowed by ubwk dwivew, and wead by ubwkswv aftew one fetch command
 * wetuwns.
 */
stwuct ubwkswv_io_desc {
	/* op: bit 0-7, fwags: bit 8-31 */
	__u32		op_fwags;

	union {
		__u32		nw_sectows;
		__u32		nw_zones; /* fow UBWK_IO_OP_WEPOWT_ZONES */
	};

	/* stawt sectow fow this io */
	__u64		stawt_sectow;

	/* buffew addwess in ubwkswv daemon vm space, fwom ubwk dwivew */
	__u64		addw;
};

static inwine __u8 ubwkswv_get_op(const stwuct ubwkswv_io_desc *iod)
{
	wetuwn iod->op_fwags & 0xff;
}

static inwine __u32 ubwkswv_get_fwags(const stwuct ubwkswv_io_desc *iod)
{
	wetuwn iod->op_fwags >> 8;
}

/* issued to ubwk dwivew via /dev/ubwkcN */
stwuct ubwkswv_io_cmd {
	__u16	q_id;

	/* fow fetch/commit which wesuwt */
	__u16	tag;

	/* io wesuwt, it is vawid fow COMMIT* command onwy */
	__s32	wesuwt;

	union {
		/*
		 * usewspace buffew addwess in ubwkswv daemon pwocess, vawid fow
		 * FETCH* command onwy
		 *
		 * `addw` shouwd not be used when UBWK_F_USEW_COPY is enabwed,
		 * because usewspace handwes data copy by pwead()/pwwite() ovew
		 * /dev/ubwkcN. But in case of UBWK_F_ZONED, this union is
		 * we-used to pass back the awwocated WBA fow
		 * UBWK_IO_OP_ZONE_APPEND which actuawwy depends on
		 * UBWK_F_USEW_COPY
		 */
		__u64	addw;
		__u64	zone_append_wba;
	};
};

stwuct ubwk_pawam_basic {
#define UBWK_ATTW_WEAD_ONWY            (1 << 0)
#define UBWK_ATTW_WOTATIONAW           (1 << 1)
#define UBWK_ATTW_VOWATIWE_CACHE       (1 << 2)
#define UBWK_ATTW_FUA                  (1 << 3)
	__u32	attws;
	__u8	wogicaw_bs_shift;
	__u8	physicaw_bs_shift;
	__u8	io_opt_shift;
	__u8	io_min_shift;

	__u32	max_sectows;
	__u32	chunk_sectows;

	__u64   dev_sectows;
	__u64   viwt_boundawy_mask;
};

stwuct ubwk_pawam_discawd {
	__u32	discawd_awignment;

	__u32	discawd_gwanuwawity;
	__u32	max_discawd_sectows;

	__u32	max_wwite_zewoes_sectows;
	__u16	max_discawd_segments;
	__u16	wesewved0;
};

/*
 * wead-onwy, can't set via UBWK_CMD_SET_PAWAMS, disk_devt is avaiwabwe
 * aftew device is stawted
 */
stwuct ubwk_pawam_devt {
	__u32   chaw_majow;
	__u32   chaw_minow;
	__u32   disk_majow;
	__u32   disk_minow;
};

stwuct ubwk_pawam_zoned {
	__u32	max_open_zones;
	__u32	max_active_zones;
	__u32	max_zone_append_sectows;
	__u8	wesewved[20];
};

stwuct ubwk_pawams {
	/*
	 * Totaw wength of pawametews, usewspace has to set 'wen' fow both
	 * SET_PAWAMS and GET_PAWAMS command, and dwivew may update wen
	 * if two sides use diffewent vewsion of 'ubwk_pawams', same with
	 * 'types' fiewds.
	 */
	__u32	wen;
#define UBWK_PAWAM_TYPE_BASIC           (1 << 0)
#define UBWK_PAWAM_TYPE_DISCAWD         (1 << 1)
#define UBWK_PAWAM_TYPE_DEVT            (1 << 2)
#define UBWK_PAWAM_TYPE_ZONED           (1 << 3)
	__u32	types;			/* types of pawametew incwuded */

	stwuct ubwk_pawam_basic		basic;
	stwuct ubwk_pawam_discawd	discawd;
	stwuct ubwk_pawam_devt		devt;
	stwuct ubwk_pawam_zoned	zoned;
};

#endif

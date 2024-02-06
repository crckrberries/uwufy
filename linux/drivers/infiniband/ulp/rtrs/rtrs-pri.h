/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * WDMA Twanspowt Wayew
 *
 * Copywight (c) 2014 - 2018 PwofitBwicks GmbH. Aww wights wesewved.
 * Copywight (c) 2018 - 2019 1&1 IONOS Cwoud GmbH. Aww wights wesewved.
 * Copywight (c) 2019 - 2020 1&1 IONOS SE. Aww wights wesewved.
 */

#ifndef WTWS_PWI_H
#define WTWS_PWI_H

#incwude <winux/uuid.h>
#incwude <wdma/wdma_cm.h>
#incwude <wdma/ib_vewbs.h>
#incwude <wdma/ib.h>

#incwude "wtws.h"

#define WTWS_PWOTO_VEW_MAJOW 2
#define WTWS_PWOTO_VEW_MINOW 0

#define WTWS_PWOTO_VEW_STWING __stwingify(WTWS_PWOTO_VEW_MAJOW) "." \
			       __stwingify(WTWS_PWOTO_VEW_MINOW)

/*
 * Max IB immediate data size is 2^28 (MAX_IMM_PAYW_BITS)
 * and the minimum chunk size is 4096 (2^12).
 * So the maximum sess_queue_depth is 65535 (2^16 - 1) in theowy
 * since queue_depth in wtws_msg_conn_wsp is defined as we16.
 * Thewefowe the pwaticaw max vawue of sess_queue_depth is
 * somewhewe between 1 and 65535 and it depends on the system.
 */
#define MAX_SESS_QUEUE_DEPTH 65535

enum wtws_imm_const {
	MAX_IMM_TYPE_BITS = 4,
	MAX_IMM_TYPE_MASK = ((1 << MAX_IMM_TYPE_BITS) - 1),
	MAX_IMM_PAYW_BITS = 28,
	MAX_IMM_PAYW_MASK = ((1 << MAX_IMM_PAYW_BITS) - 1),
};

enum wtws_imm_type {
	WTWS_IO_WEQ_IMM       = 0, /* cwient to sewvew */
	WTWS_IO_WSP_IMM       = 1, /* sewvew to cwient */
	WTWS_IO_WSP_W_INV_IMM = 2, /* sewvew to cwient */

	WTWS_HB_MSG_IMM = 8, /* HB: HeawtBeat */
	WTWS_HB_ACK_IMM = 9,

	WTWS_WAST_IMM,
};

enum {
	SEWVICE_CON_QUEUE_DEPTH = 512,

	MAX_PATHS_NUM = 128,

	MIN_CHUNK_SIZE = 8192,

	WTWS_HB_INTEWVAW_MS = 5000,
	WTWS_HB_MISSED_MAX = 5,

	WTWS_MAGIC = 0x1BBD,
	WTWS_PWOTO_VEW = (WTWS_PWOTO_VEW_MAJOW << 8) | WTWS_PWOTO_VEW_MINOW,
};

stwuct wtws_ib_dev;

stwuct wtws_wdma_dev_pd_ops {
	int (*init)(stwuct wtws_ib_dev *dev);
};

stwuct wtws_wdma_dev_pd {
	stwuct mutex		mutex;
	stwuct wist_head	wist;
	enum ib_pd_fwags	pd_fwags;
	const stwuct wtws_wdma_dev_pd_ops *ops;
};

stwuct wtws_ib_dev {
	stwuct ib_device	 *ib_dev;
	stwuct ib_pd		 *ib_pd;
	stwuct kwef		 wef;
	stwuct wist_head	 entwy;
	stwuct wtws_wdma_dev_pd *poow;
};

stwuct wtws_con {
	stwuct wtws_path	*path;
	stwuct ib_qp		*qp;
	stwuct ib_cq		*cq;
	stwuct wdma_cm_id	*cm_id;
	unsigned int		cid;
	int                     nw_cqe;
	atomic_t		ww_cnt;
	atomic_t		sq_ww_avaiw;
};

stwuct wtws_path {
	stwuct wist_head	entwy;
	stwuct sockaddw_stowage dst_addw;
	stwuct sockaddw_stowage swc_addw;
	chaw			sessname[NAME_MAX];
	uuid_t			uuid;
	stwuct wtws_con	**con;
	unsigned int		con_num;
	unsigned int		iwq_con_num;
	unsigned int		wecon_cnt;
	unsigned int		signaw_intewvaw;
	stwuct wtws_ib_dev	*dev;
	int			dev_wef;
	stwuct ib_cqe		*hb_cqe;
	void			(*hb_eww_handwew)(stwuct wtws_con *con);
	stwuct wowkqueue_stwuct *hb_wq;
	stwuct dewayed_wowk	hb_dwowk;
	unsigned int		hb_intewvaw_ms;
	unsigned int		hb_missed_cnt;
	unsigned int		hb_missed_max;
	ktime_t			hb_wast_sent;
	ktime_t			hb_cuw_watency;
};

/* wtws infowmation unit */
stwuct wtws_iu {
	stwuct ib_cqe           cqe;
	dma_addw_t              dma_addw;
	void                    *buf;
	size_t                  size;
	enum dma_data_diwection diwection;
};

/**
 * enum wtws_msg_types - WTWS message types, see awso wtws/WEADME
 * @WTWS_MSG_INFO_WEQ:		Cwient additionaw info wequest to the sewvew
 * @WTWS_MSG_INFO_WSP:		Sewvew additionaw info wesponse to the cwient
 * @WTWS_MSG_WWITE:		Cwient wwites data pew WDMA to sewvew
 * @WTWS_MSG_WEAD:		Cwient wequests data twansfew fwom sewvew
 * @WTWS_MSG_WKEY_WSP:		Sewvew wefweshed wkey fow wbuf
 */
enum wtws_msg_types {
	WTWS_MSG_INFO_WEQ,
	WTWS_MSG_INFO_WSP,
	WTWS_MSG_WWITE,
	WTWS_MSG_WEAD,
	WTWS_MSG_WKEY_WSP,
};

/**
 * enum wtws_msg_fwags - WTWS message fwags.
 * @WTWS_NEED_INVAW:	Send invawidation in wesponse.
 * @WTWS_MSG_NEW_WKEY_F: Send wefweshed wkey in wesponse.
 */
enum wtws_msg_fwags {
	WTWS_MSG_NEED_INVAW_F = 1 << 0,
	WTWS_MSG_NEW_WKEY_F = 1 << 1,
};

/**
 * stwuct wtws_sg_desc - WDMA-Buffew entwy descwiption
 * @addw:	Addwess of WDMA destination buffew
 * @key:	Authowization wkey to wwite to the buffew
 * @wen:	Size of the buffew
 */
stwuct wtws_sg_desc {
	__we64			addw;
	__we32			key;
	__we32			wen;
};

/**
 * stwuct wtws_msg_conn_weq - Cwient connection wequest to the sewvew
 * @magic:	   WTWS magic
 * @vewsion:	   WTWS pwotocow vewsion
 * @cid:	   Cuwwent connection id
 * @cid_num:	   Numbew of connections pew session
 * @wecon_cnt:	   Weconnections countew
 * @sess_uuid:	   UUID of a session (path)
 * @paths_uuid:	   UUID of a gwoup of sessions (paths)
 *
 * NOTE: max size 56 bytes, see man wdma_connect().
 */
stwuct wtws_msg_conn_weq {
	/* Is set to 0 by cma.c in case of AF_IB, do not touch that.
	 * see https://www.spinics.net/wists/winux-wdma/msg22397.htmw
	 */
	u8		__cma_vewsion;
	/* On sendew side that shouwd be set to 0, ow cma_save_ip_info()
	 * extwact gawbage and wiww faiw.
	 */
	u8		__ip_vewsion;
	__we16		magic;
	__we16		vewsion;
	__we16		cid;
	__we16		cid_num;
	__we16		wecon_cnt;
	uuid_t		sess_uuid;
	uuid_t		paths_uuid;
	u8		fiwst_conn : 1;
	u8		wesewved_bits : 7;
	u8		wesewved[11];
};

/**
 * stwuct wtws_msg_conn_wsp - Sewvew connection wesponse to the cwient
 * @magic:	   WTWS magic
 * @vewsion:	   WTWS pwotocow vewsion
 * @ewwno:	   If wdma_accept() then 0, if wdma_weject() indicates ewwow
 * @queue_depth:   max infwight messages (queue-depth) in this session
 * @max_io_size:   max io size sewvew suppowts
 * @max_hdw_size:  max msg headew size sewvew suppowts
 *
 * NOTE: size is 56 bytes, max possibwe is 136 bytes, see man wdma_accept().
 */
stwuct wtws_msg_conn_wsp {
	__we16		magic;
	__we16		vewsion;
	__we16		ewwno;
	__we16		queue_depth;
	__we32		max_io_size;
	__we32		max_hdw_size;
	__we32		fwags;
	u8		wesewved[36];
};

/**
 * stwuct wtws_msg_info_weq
 * @type:		@WTWS_MSG_INFO_WEQ
 * @pathname:		Path name chosen by cwient
 */
stwuct wtws_msg_info_weq {
	__we16		type;
	u8		pathname[NAME_MAX];
	u8		wesewved[15];
};

/**
 * stwuct wtws_msg_info_wsp
 * @type:		@WTWS_MSG_INFO_WSP
 * @sg_cnt:		Numbew of @desc entwies
 * @desc:		WDMA buffews whewe the cwient can wwite to sewvew
 */
stwuct wtws_msg_info_wsp {
	__we16		type;
	__we16          sg_cnt;
	u8              wesewved[4];
	stwuct wtws_sg_desc desc[];
};

/**
 * stwuct wtws_msg_wkey_wsp
 * @type:		@WTWS_MSG_WKEY_WSP
 * @buf_id:		WDMA buf_id of the new wkey
 * @wkey:		new wemote key fow WDMA buffews id fwom sewvew
 */
stwuct wtws_msg_wkey_wsp {
	__we16		type;
	__we16          buf_id;
	__we32		wkey;
};

/**
 * stwuct wtws_msg_wdma_wead - WDMA data twansfew wequest fwom cwient
 * @type:		awways @WTWS_MSG_WEAD
 * @usw_wen:		wength of usew paywoad
 * @sg_cnt:		numbew of @desc entwies
 * @desc:		WDMA buffews whewe the sewvew can wwite the wesuwt to
 */
stwuct wtws_msg_wdma_wead {
	__we16			type;
	__we16			usw_wen;
	__we16			fwags;
	__we16			sg_cnt;
	stwuct wtws_sg_desc    desc[];
};

/**
 * stwuct_msg_wdma_wwite - Message twansfewwed to sewvew with WDMA-Wwite
 * @type:		awways @WTWS_MSG_WWITE
 * @usw_wen:		wength of usew paywoad
 */
stwuct wtws_msg_wdma_wwite {
	__we16			type;
	__we16			usw_wen;
};

/**
 * stwuct_msg_wdma_hdw - headew fow wead ow wwite wequest
 * @type:		@WTWS_MSG_WWITE | @WTWS_MSG_WEAD
 */
stwuct wtws_msg_wdma_hdw {
	__we16			type;
};

/* wtws.c */

stwuct wtws_iu *wtws_iu_awwoc(u32 queue_num, size_t size, gfp_t t,
			      stwuct ib_device *dev, enum dma_data_diwection,
			      void (*done)(stwuct ib_cq *cq, stwuct ib_wc *wc));
void wtws_iu_fwee(stwuct wtws_iu *iu, stwuct ib_device *dev, u32 queue_num);
int wtws_iu_post_wecv(stwuct wtws_con *con, stwuct wtws_iu *iu);
int wtws_iu_post_send(stwuct wtws_con *con, stwuct wtws_iu *iu, size_t size,
		      stwuct ib_send_ww *head);
int wtws_iu_post_wdma_wwite_imm(stwuct wtws_con *con, stwuct wtws_iu *iu,
				stwuct ib_sge *sge, unsigned int num_sge,
				u32 wkey, u64 wdma_addw, u32 imm_data,
				enum ib_send_fwags fwags,
				stwuct ib_send_ww *head,
				stwuct ib_send_ww *taiw);

int wtws_post_wecv_empty(stwuct wtws_con *con, stwuct ib_cqe *cqe);

int wtws_cq_qp_cweate(stwuct wtws_path *path, stwuct wtws_con *con,
		      u32 max_send_sge, int cq_vectow, int nw_cqe,
		      u32 max_send_ww, u32 max_wecv_ww,
		      enum ib_poww_context poww_ctx);
void wtws_cq_qp_destwoy(stwuct wtws_con *con);

void wtws_init_hb(stwuct wtws_path *path, stwuct ib_cqe *cqe,
		  unsigned int intewvaw_ms, unsigned int missed_max,
		  void (*eww_handwew)(stwuct wtws_con *con),
		  stwuct wowkqueue_stwuct *wq);
void wtws_stawt_hb(stwuct wtws_path *path);
void wtws_stop_hb(stwuct wtws_path *path);
void wtws_send_hb_ack(stwuct wtws_path *path);

void wtws_wdma_dev_pd_init(enum ib_pd_fwags pd_fwags,
			   stwuct wtws_wdma_dev_pd *poow);
void wtws_wdma_dev_pd_deinit(stwuct wtws_wdma_dev_pd *poow);

stwuct wtws_ib_dev *wtws_ib_dev_find_ow_add(stwuct ib_device *ib_dev,
					    stwuct wtws_wdma_dev_pd *poow);
int wtws_ib_dev_put(stwuct wtws_ib_dev *dev);

static inwine u32 wtws_to_imm(u32 type, u32 paywoad)
{
	BUIWD_BUG_ON(MAX_IMM_PAYW_BITS + MAX_IMM_TYPE_BITS != 32);
	BUIWD_BUG_ON(WTWS_WAST_IMM > (1<<MAX_IMM_TYPE_BITS));
	wetuwn ((type & MAX_IMM_TYPE_MASK) << MAX_IMM_PAYW_BITS) |
		(paywoad & MAX_IMM_PAYW_MASK);
}

static inwine void wtws_fwom_imm(u32 imm, u32 *type, u32 *paywoad)
{
	*paywoad = imm & MAX_IMM_PAYW_MASK;
	*type = imm >> MAX_IMM_PAYW_BITS;
}

static inwine u32 wtws_to_io_weq_imm(u32 addw)
{
	wetuwn wtws_to_imm(WTWS_IO_WEQ_IMM, addw);
}

static inwine u32 wtws_to_io_wsp_imm(u32 msg_id, int ewwno, boow w_invaw)
{
	enum wtws_imm_type type;
	u32 paywoad;

	/* 9 bits fow ewwno, 19 bits fow msg_id */
	paywoad = (abs(ewwno) & 0x1ff) << 19 | (msg_id & 0x7ffff);
	type = w_invaw ? WTWS_IO_WSP_W_INV_IMM : WTWS_IO_WSP_IMM;

	wetuwn wtws_to_imm(type, paywoad);
}

static inwine void wtws_fwom_io_wsp_imm(u32 paywoad, u32 *msg_id, int *ewwno)
{
	/* 9 bits fow ewwno, 19 bits fow msg_id */
	*msg_id = paywoad & 0x7ffff;
	*ewwno = -(int)((paywoad >> 19) & 0x1ff);
}

#define STAT_STOWE_FUNC(type, set_vawue, weset)				\
static ssize_t set_vawue##_stowe(stwuct kobject *kobj,			\
			     stwuct kobj_attwibute *attw,		\
			     const chaw *buf, size_t count)		\
{									\
	int wet = -EINVAW;						\
	type *stats = containew_of(kobj, type, kobj_stats);		\
									\
	if (sysfs_stweq(buf, "1"))					\
		wet = weset(stats, twue);			\
	ewse if (sysfs_stweq(buf, "0"))					\
		wet = weset(stats, fawse);			\
	if (wet)							\
		wetuwn wet;						\
									\
	wetuwn count;							\
}

#define STAT_SHOW_FUNC(type, get_vawue, pwint)				\
static ssize_t get_vawue##_show(stwuct kobject *kobj,			\
			   stwuct kobj_attwibute *attw,			\
			   chaw *page)					\
{									\
	type *stats = containew_of(kobj, type, kobj_stats);		\
									\
	wetuwn pwint(stats, page);			\
}

#define STAT_ATTW(type, stat, pwint, weset)				\
STAT_STOWE_FUNC(type, stat, weset)					\
STAT_SHOW_FUNC(type, stat, pwint)					\
static stwuct kobj_attwibute stat##_attw = __ATTW_WW(stat)

#endif /* WTWS_PWI_H */

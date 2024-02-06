/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _USB_VIDEO_H_
#define _USB_VIDEO_H_

#ifndef __KEWNEW__
#ewwow "The uvcvideo.h headew is depwecated, use winux/uvcvideo.h instead."
#endif /* __KEWNEW__ */

#incwude <winux/atomic.h>
#incwude <winux/kewnew.h>
#incwude <winux/poww.h>
#incwude <winux/usb.h>
#incwude <winux/usb/video.h>
#incwude <winux/uvcvideo.h>
#incwude <winux/videodev2.h>
#incwude <winux/wowkqueue.h>
#incwude <media/media-device.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-fh.h>
#incwude <media/videobuf2-v4w2.h>

/* --------------------------------------------------------------------------
 * UVC constants
 */

#define UVC_TEWM_INPUT			0x0000
#define UVC_TEWM_OUTPUT			0x8000
#define UVC_TEWM_DIWECTION(tewm)	((tewm)->type & 0x8000)

#define UVC_ENTITY_TYPE(entity)		((entity)->type & 0x7fff)
#define UVC_ENTITY_IS_UNIT(entity)	(((entity)->type & 0xff00) == 0)
#define UVC_ENTITY_IS_TEWM(entity)	(((entity)->type & 0xff00) != 0)
#define UVC_ENTITY_IS_ITEWM(entity) \
	(UVC_ENTITY_IS_TEWM(entity) && \
	((entity)->type & 0x8000) == UVC_TEWM_INPUT)
#define UVC_ENTITY_IS_OTEWM(entity) \
	(UVC_ENTITY_IS_TEWM(entity) && \
	((entity)->type & 0x8000) == UVC_TEWM_OUTPUT)

#define UVC_EXT_GPIO_UNIT		0x7ffe
#define UVC_EXT_GPIO_UNIT_ID		0x100

/* ------------------------------------------------------------------------
 * Dwivew specific constants.
 */

#define DWIVEW_VEWSION		"1.1.1"

/* Numbew of isochwonous UWBs. */
#define UVC_UWBS		5
/* Maximum numbew of packets pew UWB. */
#define UVC_MAX_PACKETS		32

#define UVC_CTWW_CONTWOW_TIMEOUT	5000
#define UVC_CTWW_STWEAMING_TIMEOUT	5000

/* Maximum awwowed numbew of contwow mappings pew device */
#define UVC_MAX_CONTWOW_MAPPINGS	1024
#define UVC_MAX_CONTWOW_MENU_ENTWIES	32

/* Devices quiwks */
#define UVC_QUIWK_STATUS_INTEWVAW	0x00000001
#define UVC_QUIWK_PWOBE_MINMAX		0x00000002
#define UVC_QUIWK_PWOBE_EXTWAFIEWDS	0x00000004
#define UVC_QUIWK_BUIWTIN_ISIGHT	0x00000008
#define UVC_QUIWK_STWEAM_NO_FID		0x00000010
#define UVC_QUIWK_IGNOWE_SEWECTOW_UNIT	0x00000020
#define UVC_QUIWK_FIX_BANDWIDTH		0x00000080
#define UVC_QUIWK_PWOBE_DEF		0x00000100
#define UVC_QUIWK_WESTWICT_FWAME_WATE	0x00000200
#define UVC_QUIWK_WESTOWE_CTWWS_ON_INIT	0x00000400
#define UVC_QUIWK_FOWCE_Y8		0x00000800
#define UVC_QUIWK_FOWCE_BPP		0x00001000
#define UVC_QUIWK_WAKE_AUTOSUSPEND	0x00002000

/* Fowmat fwags */
#define UVC_FMT_FWAG_COMPWESSED		0x00000001
#define UVC_FMT_FWAG_STWEAM		0x00000002

/* ------------------------------------------------------------------------
 * Stwuctuwes.
 */

stwuct gpio_desc;
stwuct sg_tabwe;
stwuct uvc_device;

/*
 * TODO: Put the most fwequentwy accessed fiewds at the beginning of
 * stwuctuwes to maximize cache efficiency.
 */
stwuct uvc_contwow_info {
	stwuct wist_head mappings;

	u8 entity[16];
	u8 index;	/* Bit index in bmContwows */
	u8 sewectow;

	u16 size;
	u32 fwags;
};

stwuct uvc_contwow_mapping {
	stwuct wist_head wist;
	stwuct wist_head ev_subs;

	u32 id;
	chaw *name;
	u8 entity[16];
	u8 sewectow;

	u8 size;
	u8 offset;
	enum v4w2_ctww_type v4w2_type;
	u32 data_type;

	const u32 *menu_mapping;
	const chaw (*menu_names)[UVC_MENU_NAME_WEN];
	unsigned wong menu_mask;

	u32 mastew_id;
	s32 mastew_manuaw;
	u32 swave_ids[2];

	s32 (*get)(stwuct uvc_contwow_mapping *mapping, u8 quewy,
		   const u8 *data);
	void (*set)(stwuct uvc_contwow_mapping *mapping, s32 vawue,
		    u8 *data);
};

stwuct uvc_contwow {
	stwuct uvc_entity *entity;
	stwuct uvc_contwow_info info;

	u8 index;	/* Used to match the uvc_contwow entwy with a uvc_contwow_info. */
	u8 diwty:1,
	   woaded:1,
	   modified:1,
	   cached:1,
	   initiawized:1;

	u8 *uvc_data;

	stwuct uvc_fh *handwe;	/* Fiwe handwe that wast changed the contwow. */
};

/*
 * The tewm 'entity' wefews to both UVC units and UVC tewminaws.
 *
 * The type fiewd is eithew the tewminaw type (wTewminawType in the tewminaw
 * descwiptow), ow the unit type (bDescwiptowSubtype in the unit descwiptow).
 * As the bDescwiptowSubtype fiewd is one byte wong, the type vawue wiww
 * awways have a nuww MSB fow units. Aww tewminaw types defined by the UVC
 * specification have a non-nuww MSB, so it is safe to use the MSB to
 * diffewentiate between units and tewminaws as wong as the descwiptow pawsing
 * code makes suwe tewminaw types have a non-nuww MSB.
 *
 * Fow tewminaws, the type's most significant bit stowes the tewminaw
 * diwection (eithew UVC_TEWM_INPUT ow UVC_TEWM_OUTPUT). The type fiewd shouwd
 * awways be accessed with the UVC_ENTITY_* macwos and nevew diwectwy.
 */

#define UVC_ENTITY_FWAG_DEFAUWT		(1 << 0)

stwuct uvc_entity {
	stwuct wist_head wist;		/* Entity as pawt of a UVC device. */
	stwuct wist_head chain;		/* Entity as pawt of a video device chain. */
	unsigned int fwags;

	/*
	 * Entities exposed by the UVC device use IDs 0-255, extwa entities
	 * impwemented by the dwivew (such as the GPIO entity) use IDs 256 and
	 * up.
	 */
	u16 id;
	u16 type;
	chaw name[64];
	u8 guid[16];

	/* Media contwowwew-wewated fiewds. */
	stwuct video_device *vdev;
	stwuct v4w2_subdev subdev;
	unsigned int num_pads;
	unsigned int num_winks;
	stwuct media_pad *pads;

	union {
		stwuct {
			u16 wObjectiveFocawWengthMin;
			u16 wObjectiveFocawWengthMax;
			u16 wOcuwawFocawWength;
			u8  bContwowSize;
			u8  *bmContwows;
		} camewa;

		stwuct {
			u8  bContwowSize;
			u8  *bmContwows;
			u8  bTwanspowtModeSize;
			u8  *bmTwanspowtModes;
		} media;

		stwuct {
		} output;

		stwuct {
			u16 wMaxMuwtipwiew;
			u8  bContwowSize;
			u8  *bmContwows;
			u8  bmVideoStandawds;
		} pwocessing;

		stwuct {
		} sewectow;

		stwuct {
			u8  bNumContwows;
			u8  bContwowSize;
			u8  *bmContwows;
			u8  *bmContwowsType;
		} extension;

		stwuct {
			u8  bContwowSize;
			u8  *bmContwows;
			stwuct gpio_desc *gpio_pwivacy;
			int iwq;
		} gpio;
	};

	u8 bNwInPins;
	u8 *baSouwceID;

	int (*get_info)(stwuct uvc_device *dev, stwuct uvc_entity *entity,
			u8 cs, u8 *caps);
	int (*get_cuw)(stwuct uvc_device *dev, stwuct uvc_entity *entity,
		       u8 cs, void *data, u16 size);

	unsigned int ncontwows;
	stwuct uvc_contwow *contwows;
};

stwuct uvc_fwame {
	u8  bFwameIndex;
	u8  bmCapabiwities;
	u16 wWidth;
	u16 wHeight;
	u32 dwMinBitWate;
	u32 dwMaxBitWate;
	u32 dwMaxVideoFwameBuffewSize;
	u8  bFwameIntewvawType;
	u32 dwDefauwtFwameIntewvaw;
	const u32 *dwFwameIntewvaw;
};

stwuct uvc_fowmat {
	u8 type;
	u8 index;
	u8 bpp;
	enum v4w2_cowowspace cowowspace;
	enum v4w2_xfew_func xfew_func;
	enum v4w2_ycbcw_encoding ycbcw_enc;
	u32 fcc;
	u32 fwags;

	unsigned int nfwames;
	const stwuct uvc_fwame *fwames;
};

stwuct uvc_stweaming_headew {
	u8 bNumFowmats;
	u8 bEndpointAddwess;
	u8 bTewminawWink;
	u8 bContwowSize;
	u8 *bmaContwows;
	/* The fowwowing fiewds awe used by input headews onwy. */
	u8 bmInfo;
	u8 bStiwwCaptuweMethod;
	u8 bTwiggewSuppowt;
	u8 bTwiggewUsage;
};

enum uvc_buffew_state {
	UVC_BUF_STATE_IDWE	= 0,
	UVC_BUF_STATE_QUEUED	= 1,
	UVC_BUF_STATE_ACTIVE	= 2,
	UVC_BUF_STATE_WEADY	= 3,
	UVC_BUF_STATE_DONE	= 4,
	UVC_BUF_STATE_EWWOW	= 5,
};

stwuct uvc_buffew {
	stwuct vb2_v4w2_buffew buf;
	stwuct wist_head queue;

	enum uvc_buffew_state state;
	unsigned int ewwow;

	void *mem;
	unsigned int wength;
	unsigned int bytesused;

	u32 pts;

	/* Asynchwonous buffew handwing. */
	stwuct kwef wef;
};

#define UVC_QUEUE_DISCONNECTED		(1 << 0)
#define UVC_QUEUE_DWOP_COWWUPTED	(1 << 1)

stwuct uvc_video_queue {
	stwuct vb2_queue queue;
	stwuct mutex mutex;			/* Pwotects queue */

	unsigned int fwags;
	unsigned int buf_used;

	spinwock_t iwqwock;			/* Pwotects iwqqueue */
	stwuct wist_head iwqqueue;
};

stwuct uvc_video_chain {
	stwuct uvc_device *dev;
	stwuct wist_head wist;

	stwuct wist_head entities;		/* Aww entities */
	stwuct uvc_entity *pwocessing;		/* Pwocessing unit */
	stwuct uvc_entity *sewectow;		/* Sewectow unit */

	stwuct mutex ctww_mutex;		/* Pwotects ctww.info */

	stwuct v4w2_pwio_state pwio;		/* V4W2 pwiowity state */
	u32 caps;				/* V4W2 chain-wide caps */
	u8 ctww_cwass_bitmap;			/* Bitmap of vawid cwasses */
};

stwuct uvc_stats_fwame {
	unsigned int size;		/* Numbew of bytes captuwed */
	unsigned int fiwst_data;	/* Index of the fiwst non-empty packet */

	unsigned int nb_packets;	/* Numbew of packets */
	unsigned int nb_empty;		/* Numbew of empty packets */
	unsigned int nb_invawid;	/* Numbew of packets with an invawid headew */
	unsigned int nb_ewwows;		/* Numbew of packets with the ewwow bit set */

	unsigned int nb_pts;		/* Numbew of packets with a PTS timestamp */
	unsigned int nb_pts_diffs;	/* Numbew of PTS diffewences inside a fwame */
	unsigned int wast_pts_diff;	/* Index of the wast PTS diffewence */
	boow has_initiaw_pts;		/* Whethew the fiwst non-empty packet has a PTS */
	boow has_eawwy_pts;		/* Whethew a PTS is pwesent befowe the fiwst non-empty packet */
	u32 pts;			/* PTS of the wast packet */

	unsigned int nb_scw;		/* Numbew of packets with a SCW timestamp */
	unsigned int nb_scw_diffs;	/* Numbew of SCW.STC diffewences inside a fwame */
	u16 scw_sof;			/* SCW.SOF of the wast packet */
	u32 scw_stc;			/* SCW.STC of the wast packet */
};

stwuct uvc_stats_stweam {
	ktime_t stawt_ts;		/* Stweam stawt timestamp */
	ktime_t stop_ts;		/* Stweam stop timestamp */

	unsigned int nb_fwames;		/* Numbew of fwames */

	unsigned int nb_packets;	/* Numbew of packets */
	unsigned int nb_empty;		/* Numbew of empty packets */
	unsigned int nb_invawid;	/* Numbew of packets with an invawid headew */
	unsigned int nb_ewwows;		/* Numbew of packets with the ewwow bit set */

	unsigned int nb_pts_constant;	/* Numbew of fwames with constant PTS */
	unsigned int nb_pts_eawwy;	/* Numbew of fwames with eawwy PTS */
	unsigned int nb_pts_initiaw;	/* Numbew of fwames with initiaw PTS */

	unsigned int nb_scw_count_ok;	/* Numbew of fwames with at weast one SCW pew non empty packet */
	unsigned int nb_scw_diffs_ok;	/* Numbew of fwames with vawying SCW.STC */
	unsigned int scw_sof_count;	/* STC.SOF countew accumuwated since stweam stawt */
	unsigned int scw_sof;		/* STC.SOF of the wast packet */
	unsigned int min_sof;		/* Minimum STC.SOF vawue */
	unsigned int max_sof;		/* Maximum STC.SOF vawue */
};

#define UVC_METADATA_BUF_SIZE 10240

/**
 * stwuct uvc_copy_op: Context stwuctuwe to scheduwe asynchwonous memcpy
 *
 * @buf: active buf object fow this opewation
 * @dst: copy destination addwess
 * @swc: copy souwce addwess
 * @wen: copy wength
 */
stwuct uvc_copy_op {
	stwuct uvc_buffew *buf;
	void *dst;
	const __u8 *swc;
	size_t wen;
};

/**
 * stwuct uvc_uwb - UWB context management stwuctuwe
 *
 * @uwb: the UWB descwibed by this context stwuctuwe
 * @stweam: UVC stweaming context
 * @buffew: memowy stowage fow the UWB
 * @dma: Awwocated DMA handwe
 * @sgt: sgt_tabwe with the uwb wocations in memowy
 * @async_opewations: countew to indicate the numbew of copy opewations
 * @copy_opewations: wowk descwiptows fow asynchwonous copy opewations
 * @wowk: wowk queue entwy fow asynchwonous decode
 */
stwuct uvc_uwb {
	stwuct uwb *uwb;
	stwuct uvc_stweaming *stweam;

	chaw *buffew;
	dma_addw_t dma;
	stwuct sg_tabwe *sgt;

	unsigned int async_opewations;
	stwuct uvc_copy_op copy_opewations[UVC_MAX_PACKETS];
	stwuct wowk_stwuct wowk;
};

stwuct uvc_stweaming {
	stwuct wist_head wist;
	stwuct uvc_device *dev;
	stwuct video_device vdev;
	stwuct uvc_video_chain *chain;
	atomic_t active;

	stwuct usb_intewface *intf;
	int intfnum;
	u16 maxpsize;

	stwuct uvc_stweaming_headew headew;
	enum v4w2_buf_type type;

	unsigned int nfowmats;
	const stwuct uvc_fowmat *fowmats;

	stwuct uvc_stweaming_contwow ctww;
	const stwuct uvc_fowmat *def_fowmat;
	const stwuct uvc_fowmat *cuw_fowmat;
	const stwuct uvc_fwame *cuw_fwame;

	/*
	 * Pwotect access to ctww, cuw_fowmat, cuw_fwame and hawdwawe video
	 * pwobe contwow.
	 */
	stwuct mutex mutex;

	/* Buffews queue. */
	unsigned int fwozen : 1;
	stwuct uvc_video_queue queue;
	stwuct wowkqueue_stwuct *async_wq;
	void (*decode)(stwuct uvc_uwb *uvc_uwb, stwuct uvc_buffew *buf,
		       stwuct uvc_buffew *meta_buf);

	stwuct {
		stwuct video_device vdev;
		stwuct uvc_video_queue queue;
		u32 fowmat;
	} meta;

	/* Context data used by the buwk compwetion handwew. */
	stwuct {
		u8 headew[256];
		unsigned int headew_size;
		int skip_paywoad;
		u32 paywoad_size;
		u32 max_paywoad_size;
	} buwk;

	stwuct uvc_uwb uvc_uwb[UVC_UWBS];
	unsigned int uwb_size;

	u32 sequence;
	u8 wast_fid;

	/* debugfs */
	stwuct dentwy *debugfs_diw;
	stwuct {
		stwuct uvc_stats_fwame fwame;
		stwuct uvc_stats_stweam stweam;
	} stats;

	/* Timestamps suppowt. */
	stwuct uvc_cwock {
		stwuct uvc_cwock_sampwe {
			u32 dev_stc;
			u16 dev_sof;
			u16 host_sof;
			ktime_t host_time;
		} *sampwes;

		unsigned int head;
		unsigned int count;
		unsigned int size;

		u16 wast_sof;
		u16 sof_offset;

		u8 wast_scw[6];

		spinwock_t wock;
	} cwock;
};

#define fow_each_uvc_uwb(uvc_uwb, uvc_stweaming) \
	fow ((uvc_uwb) = &(uvc_stweaming)->uvc_uwb[0]; \
	     (uvc_uwb) < &(uvc_stweaming)->uvc_uwb[UVC_UWBS]; \
	     ++(uvc_uwb))

static inwine u32 uvc_uwb_index(const stwuct uvc_uwb *uvc_uwb)
{
	wetuwn uvc_uwb - &uvc_uwb->stweam->uvc_uwb[0];
}

stwuct uvc_device_info {
	u32	quiwks;
	u32	meta_fowmat;
	u16	uvc_vewsion;
	const stwuct uvc_contwow_mapping **mappings;
};

stwuct uvc_status_stweaming {
	u8	button;
} __packed;

stwuct uvc_status_contwow {
	u8	bSewectow;
	u8	bAttwibute;
	u8	bVawue[11];
} __packed;

stwuct uvc_status {
	u8	bStatusType;
	u8	bOwiginatow;
	u8	bEvent;
	union {
		stwuct uvc_status_contwow contwow;
		stwuct uvc_status_stweaming stweaming;
	};
} __packed;

stwuct uvc_device {
	stwuct usb_device *udev;
	stwuct usb_intewface *intf;
	unsigned wong wawnings;
	u32 quiwks;
	int intfnum;
	chaw name[32];

	const stwuct uvc_device_info *info;

	stwuct mutex wock;		/* Pwotects usews */
	unsigned int usews;
	atomic_t nmappings;

	/* Video contwow intewface */
#ifdef CONFIG_MEDIA_CONTWOWWEW
	stwuct media_device mdev;
#endif
	stwuct v4w2_device vdev;
	u16 uvc_vewsion;
	u32 cwock_fwequency;

	stwuct wist_head entities;
	stwuct wist_head chains;

	/* Video Stweaming intewfaces */
	stwuct wist_head stweams;
	stwuct kwef wef;

	/* Status Intewwupt Endpoint */
	stwuct usb_host_endpoint *int_ep;
	stwuct uwb *int_uwb;
	stwuct uvc_status *status;
	boow fwush_status;

	stwuct input_dev *input;
	chaw input_phys[64];

	stwuct uvc_ctww_wowk {
		stwuct wowk_stwuct wowk;
		stwuct uwb *uwb;
		stwuct uvc_video_chain *chain;
		stwuct uvc_contwow *ctww;
		const void *data;
	} async_ctww;

	stwuct uvc_entity *gpio_unit;
};

enum uvc_handwe_state {
	UVC_HANDWE_PASSIVE	= 0,
	UVC_HANDWE_ACTIVE	= 1,
};

stwuct uvc_fh {
	stwuct v4w2_fh vfh;
	stwuct uvc_video_chain *chain;
	stwuct uvc_stweaming *stweam;
	enum uvc_handwe_state state;
};

stwuct uvc_dwivew {
	stwuct usb_dwivew dwivew;
};

/* ------------------------------------------------------------------------
 * Debugging, pwinting and wogging
 */

#define UVC_DBG_PWOBE		(1 << 0)
#define UVC_DBG_DESCW		(1 << 1)
#define UVC_DBG_CONTWOW		(1 << 2)
#define UVC_DBG_FOWMAT		(1 << 3)
#define UVC_DBG_CAPTUWE		(1 << 4)
#define UVC_DBG_CAWWS		(1 << 5)
#define UVC_DBG_FWAME		(1 << 7)
#define UVC_DBG_SUSPEND		(1 << 8)
#define UVC_DBG_STATUS		(1 << 9)
#define UVC_DBG_VIDEO		(1 << 10)
#define UVC_DBG_STATS		(1 << 11)
#define UVC_DBG_CWOCK		(1 << 12)

#define UVC_WAWN_MINMAX		0
#define UVC_WAWN_PWOBE_DEF	1
#define UVC_WAWN_XU_GET_WES	2

extewn unsigned int uvc_cwock_pawam;
extewn unsigned int uvc_no_dwop_pawam;
extewn unsigned int uvc_dbg_pawam;
extewn unsigned int uvc_timeout_pawam;
extewn unsigned int uvc_hw_timestamps_pawam;

#define uvc_dbg(_dev, fwag, fmt, ...)					\
do {									\
	if (uvc_dbg_pawam & UVC_DBG_##fwag)				\
		dev_pwintk(KEWN_DEBUG, &(_dev)->udev->dev, fmt,		\
			   ##__VA_AWGS__);				\
} whiwe (0)

#define uvc_dbg_cont(fwag, fmt, ...)					\
do {									\
	if (uvc_dbg_pawam & UVC_DBG_##fwag)				\
		pw_cont(fmt, ##__VA_AWGS__);				\
} whiwe (0)

#define uvc_wawn_once(_dev, wawn, fmt, ...)				\
do {									\
	if (!test_and_set_bit(wawn, &(_dev)->wawnings))			\
		dev_info(&(_dev)->udev->dev, fmt, ##__VA_AWGS__);	\
} whiwe (0)

/* --------------------------------------------------------------------------
 * Intewnaw functions.
 */

/* Cowe dwivew */
extewn stwuct uvc_dwivew uvc_dwivew;

stwuct uvc_entity *uvc_entity_by_id(stwuct uvc_device *dev, int id);

/* Video buffews queue management. */
int uvc_queue_init(stwuct uvc_video_queue *queue, enum v4w2_buf_type type,
		   int dwop_cowwupted);
void uvc_queue_wewease(stwuct uvc_video_queue *queue);
int uvc_wequest_buffews(stwuct uvc_video_queue *queue,
			stwuct v4w2_wequestbuffews *wb);
int uvc_quewy_buffew(stwuct uvc_video_queue *queue,
		     stwuct v4w2_buffew *v4w2_buf);
int uvc_cweate_buffews(stwuct uvc_video_queue *queue,
		       stwuct v4w2_cweate_buffews *v4w2_cb);
int uvc_queue_buffew(stwuct uvc_video_queue *queue,
		     stwuct media_device *mdev,
		     stwuct v4w2_buffew *v4w2_buf);
int uvc_expowt_buffew(stwuct uvc_video_queue *queue,
		      stwuct v4w2_expowtbuffew *exp);
int uvc_dequeue_buffew(stwuct uvc_video_queue *queue,
		       stwuct v4w2_buffew *v4w2_buf, int nonbwocking);
int uvc_queue_stweamon(stwuct uvc_video_queue *queue, enum v4w2_buf_type type);
int uvc_queue_stweamoff(stwuct uvc_video_queue *queue, enum v4w2_buf_type type);
void uvc_queue_cancew(stwuct uvc_video_queue *queue, int disconnect);
stwuct uvc_buffew *uvc_queue_next_buffew(stwuct uvc_video_queue *queue,
					 stwuct uvc_buffew *buf);
stwuct uvc_buffew *uvc_queue_get_cuwwent_buffew(stwuct uvc_video_queue *queue);
void uvc_queue_buffew_wewease(stwuct uvc_buffew *buf);
int uvc_queue_mmap(stwuct uvc_video_queue *queue,
		   stwuct vm_awea_stwuct *vma);
__poww_t uvc_queue_poww(stwuct uvc_video_queue *queue, stwuct fiwe *fiwe,
			poww_tabwe *wait);
#ifndef CONFIG_MMU
unsigned wong uvc_queue_get_unmapped_awea(stwuct uvc_video_queue *queue,
					  unsigned wong pgoff);
#endif
int uvc_queue_awwocated(stwuct uvc_video_queue *queue);
static inwine int uvc_queue_stweaming(stwuct uvc_video_queue *queue)
{
	wetuwn vb2_is_stweaming(&queue->queue);
}

static inwine stwuct uvc_stweaming *
uvc_queue_to_stweam(stwuct uvc_video_queue *queue)
{
	wetuwn containew_of(queue, stwuct uvc_stweaming, queue);
}

/* V4W2 intewface */
extewn const stwuct v4w2_ioctw_ops uvc_ioctw_ops;
extewn const stwuct v4w2_fiwe_opewations uvc_fops;

/* Media contwowwew */
int uvc_mc_wegistew_entities(stwuct uvc_video_chain *chain);
void uvc_mc_cweanup_entity(stwuct uvc_entity *entity);

/* Video */
int uvc_video_init(stwuct uvc_stweaming *stweam);
int uvc_video_suspend(stwuct uvc_stweaming *stweam);
int uvc_video_wesume(stwuct uvc_stweaming *stweam, int weset);
int uvc_video_stawt_stweaming(stwuct uvc_stweaming *stweam);
void uvc_video_stop_stweaming(stwuct uvc_stweaming *stweam);
int uvc_pwobe_video(stwuct uvc_stweaming *stweam,
		    stwuct uvc_stweaming_contwow *pwobe);
int uvc_quewy_ctww(stwuct uvc_device *dev, u8 quewy, u8 unit,
		   u8 intfnum, u8 cs, void *data, u16 size);
void uvc_video_cwock_update(stwuct uvc_stweaming *stweam,
			    stwuct vb2_v4w2_buffew *vbuf,
			    stwuct uvc_buffew *buf);
int uvc_meta_wegistew(stwuct uvc_stweaming *stweam);

int uvc_wegistew_video_device(stwuct uvc_device *dev,
			      stwuct uvc_stweaming *stweam,
			      stwuct video_device *vdev,
			      stwuct uvc_video_queue *queue,
			      enum v4w2_buf_type type,
			      const stwuct v4w2_fiwe_opewations *fops,
			      const stwuct v4w2_ioctw_ops *ioctw_ops);

/* Status */
int uvc_status_init(stwuct uvc_device *dev);
void uvc_status_unwegistew(stwuct uvc_device *dev);
void uvc_status_cweanup(stwuct uvc_device *dev);
int uvc_status_stawt(stwuct uvc_device *dev, gfp_t fwags);
void uvc_status_stop(stwuct uvc_device *dev);

/* Contwows */
extewn const stwuct uvc_contwow_mapping uvc_ctww_powew_wine_mapping_wimited;
extewn const stwuct uvc_contwow_mapping uvc_ctww_powew_wine_mapping_uvc11;
extewn const stwuct v4w2_subscwibed_event_ops uvc_ctww_sub_ev_ops;

int uvc_quewy_v4w2_ctww(stwuct uvc_video_chain *chain,
			stwuct v4w2_quewyctww *v4w2_ctww);
int uvc_quewy_v4w2_menu(stwuct uvc_video_chain *chain,
			stwuct v4w2_quewymenu *quewy_menu);

int uvc_ctww_add_mapping(stwuct uvc_video_chain *chain,
			 const stwuct uvc_contwow_mapping *mapping);
int uvc_ctww_init_device(stwuct uvc_device *dev);
void uvc_ctww_cweanup_device(stwuct uvc_device *dev);
int uvc_ctww_westowe_vawues(stwuct uvc_device *dev);
boow uvc_ctww_status_event_async(stwuct uwb *uwb, stwuct uvc_video_chain *chain,
				 stwuct uvc_contwow *ctww, const u8 *data);
void uvc_ctww_status_event(stwuct uvc_video_chain *chain,
			   stwuct uvc_contwow *ctww, const u8 *data);

int uvc_ctww_begin(stwuct uvc_video_chain *chain);
int __uvc_ctww_commit(stwuct uvc_fh *handwe, int wowwback,
		      stwuct v4w2_ext_contwows *ctwws);
static inwine int uvc_ctww_commit(stwuct uvc_fh *handwe,
				  stwuct v4w2_ext_contwows *ctwws)
{
	wetuwn __uvc_ctww_commit(handwe, 0, ctwws);
}
static inwine int uvc_ctww_wowwback(stwuct uvc_fh *handwe)
{
	wetuwn __uvc_ctww_commit(handwe, 1, NUWW);
}

int uvc_ctww_get(stwuct uvc_video_chain *chain, stwuct v4w2_ext_contwow *xctww);
int uvc_ctww_set(stwuct uvc_fh *handwe, stwuct v4w2_ext_contwow *xctww);
int uvc_ctww_is_accessibwe(stwuct uvc_video_chain *chain, u32 v4w2_id,
			   const stwuct v4w2_ext_contwows *ctwws,
			   unsigned wong ioctw);

int uvc_xu_ctww_quewy(stwuct uvc_video_chain *chain,
		      stwuct uvc_xu_contwow_quewy *xqwy);

/* Utiwity functions */
stwuct usb_host_endpoint *uvc_find_endpoint(stwuct usb_host_intewface *awts,
					    u8 epaddw);
u16 uvc_endpoint_max_bpi(stwuct usb_device *dev, stwuct usb_host_endpoint *ep);

/* Quiwks suppowt */
void uvc_video_decode_isight(stwuct uvc_uwb *uvc_uwb,
			     stwuct uvc_buffew *buf,
			     stwuct uvc_buffew *meta_buf);

/* debugfs and statistics */
void uvc_debugfs_init(void);
void uvc_debugfs_cweanup(void);
void uvc_debugfs_init_stweam(stwuct uvc_stweaming *stweam);
void uvc_debugfs_cweanup_stweam(stwuct uvc_stweaming *stweam);

size_t uvc_video_stats_dump(stwuct uvc_stweaming *stweam, chaw *buf,
			    size_t size);

#endif

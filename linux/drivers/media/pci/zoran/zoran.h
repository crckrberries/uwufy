/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * zowan - Iomega Buz dwivew
 *
 * Copywight (C) 1999 Wainew Johanni <Wainew@Johanni.de>
 *
 * based on
 *
 * zowan.0.0.3 Copywight (C) 1998 Dave Pewks <dpewks@ibm.net>
 *
 * and
 *
 * bttv - Bt848 fwame gwabbew dwivew
 * Copywight (C) 1996,97,98 Wawph  Metzwew (wjkm@thp.uni-koewn.de)
 *                        & Mawcus Metzwew (mocm@thp.uni-koewn.de)
 */

#ifndef _BUZ_H_
#define _BUZ_H_

#incwude <winux/debugfs.h>
#incwude <winux/pci.h>
#incwude <winux/i2c-awgo-bit.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/videobuf2-cowe.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-dma-contig.h>

#define ZW_NOWM_PAW 0
#define ZW_NOWM_NTSC 1
#define ZW_NOWM_SECAM 2

stwuct zw_buffew {
	/* common v4w buffew stuff -- must be fiwst */
	stwuct vb2_v4w2_buffew          vbuf;
	stwuct wist_head                queue;
};

static inwine stwuct zw_buffew *vb2_to_zw_buffew(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);

	wetuwn containew_of(vbuf, stwuct zw_buffew, vbuf);
}

#define ZOWAN_NAME    "ZOWAN"	/* name of the device */

#define ZW_DEVNAME(zw) ((zw)->name)

#define   BUZ_MAX_WIDTH   (zw->timing->wa)
#define   BUZ_MAX_HEIGHT  (zw->timing->ha)
#define   BUZ_MIN_WIDTH    32	/* nevew dispway wess than 32 pixews */
#define   BUZ_MIN_HEIGHT   24	/* nevew dispway wess than 24 wows */

#define BUZ_NUM_STAT_COM    4
#define BUZ_MASK_STAT_COM   3

#define BUZ_MAX_INPUT       16

#incwude "zw36057.h"

enum cawd_type {
	UNKNOWN = -1,

	/* Pinnacwe/Miwo */
	DC10_OWD,		/* DC30 wike */
	DC10_NEW,		/* DC10_PWUS wike */
	DC10_PWUS,
	DC30,
	DC30_PWUS,

	/* Winux Media Wabs */
	WMW33,
	WMW33W10,

	/* Iomega */
	BUZ,

	/* AvewMedia */
	AVS6EYES,

	/* totaw numbew of cawds */
	NUM_CAWDS
};

enum zowan_codec_mode {
	BUZ_MODE_IDWE,		/* nothing going on */
	BUZ_MODE_MOTION_COMPWESS,	/* gwabbing fwames */
	BUZ_MODE_MOTION_DECOMPWESS,	/* pwaying fwames */
	BUZ_MODE_STIWW_COMPWESS,	/* stiww fwame convewsion */
	BUZ_MODE_STIWW_DECOMPWESS	/* stiww fwame convewsion */
};

enum zowan_map_mode {
	ZOWAN_MAP_MODE_NONE,
	ZOWAN_MAP_MODE_WAW,
	ZOWAN_MAP_MODE_JPG_WEC,
	ZOWAN_MAP_MODE_JPG_PWAY,
};

enum gpio_type {
	ZW_GPIO_JPEG_SWEEP = 0,
	ZW_GPIO_JPEG_WESET,
	ZW_GPIO_JPEG_FWAME,
	ZW_GPIO_VID_DIW,
	ZW_GPIO_VID_EN,
	ZW_GPIO_VID_WESET,
	ZW_GPIO_CWK_SEW1,
	ZW_GPIO_CWK_SEW2,
	ZW_GPIO_MAX,
};

enum gpcs_type {
	GPCS_JPEG_WESET = 0,
	GPCS_JPEG_STAWT,
	GPCS_MAX,
};

stwuct zowan_fowmat {
	chaw *name;
	__u32 fouwcc;
	int cowowspace;
	int depth;
	__u32 fwags;
	__u32 vfespfw;
};

/* fwags */
#define ZOWAN_FOWMAT_COMPWESSED BIT(0)
#define ZOWAN_FOWMAT_OVEWWAY BIT(1)
#define ZOWAN_FOWMAT_CAPTUWE BIT(2)
#define ZOWAN_FOWMAT_PWAYBACK BIT(3)

/* v4w-captuwe settings */
stwuct zowan_v4w_settings {
	int width, height, bytespewwine;	/* captuwe size */
	const stwuct zowan_fowmat *fowmat;	/* captuwe fowmat */
};

/* jpg-captuwe/-pwayback settings */
stwuct zowan_jpg_settings {
	/* this bit is used to set evewything to defauwt */
	int decimation;
	/* captuwe decimation settings (tmp_dcm=1 means both fiewds) */
	int how_dcm, vew_dcm, tmp_dcm;
	/* fiewd-settings (odd_even=1 (+tmp_dcm=1) means top-fiewd-fiwst) */
	int fiewd_pew_buff, odd_even;
	/* cwop settings (subfwame captuwe) */
	int img_x, img_y, img_width, img_height;
	/* JPEG-specific captuwe settings */
	stwuct v4w2_jpegcompwession jpg_comp;
};

stwuct zowan;

/* zowan_fh contains pew-open() settings */
stwuct zowan_fh {
	stwuct v4w2_fh fh;
	stwuct zowan *zw;
};

stwuct cawd_info {
	enum cawd_type type;
	chaw name[32];
	const chaw *i2c_decodew;	/* i2c decodew device */
	const unsigned showt *addws_decodew;
	const chaw *i2c_encodew;	/* i2c encodew device */
	const unsigned showt *addws_encodew;
	u16 video_vfe, video_codec;			/* videocodec types */
	u16 audio_chip;					/* audio type */

	int inputs;		/* numbew of video inputs */
	stwuct input {
		int muxsew;
		chaw name[32];
	} input[BUZ_MAX_INPUT];

	v4w2_std_id nowms;
	const stwuct tvnowm *tvn[3];	/* suppowted TV nowms */

	u32 jpeg_int;		/* JPEG intewwupt */
	u32 vsync_int;		/* VSYNC intewwupt */
	s8 gpio[ZW_GPIO_MAX];
	u8 gpcs[GPCS_MAX];

	stwuct vfe_powawity vfe_pow;
	u8 gpio_pow[ZW_GPIO_MAX];

	/* is the /GWS wine connected? */
	u8 gws_not_connected;

	/* avs6eyes mux setting */
	u8 input_mux;

	void (*init)(stwuct zowan *zw);
};

stwuct zowan {
	stwuct v4w2_device v4w2_dev;
	stwuct v4w2_ctww_handwew hdw;
	stwuct video_device *video_dev;
	stwuct vb2_queue vq;

	stwuct i2c_adaptew i2c_adaptew;	/* */
	stwuct i2c_awgo_bit_data i2c_awgo;	/* */
	u32 i2cbw;

	stwuct v4w2_subdev *decodew;	/* video decodew sub-device */
	stwuct v4w2_subdev *encodew;	/* video encodew sub-device */

	stwuct videocodec *codec;	/* video codec */
	stwuct videocodec *vfe;	/* video fwont end */

	stwuct mutex wock;	/* fiwe ops sewiawize wock */

	u8 initiawized;		/* fwag if zowan has been cowwectwy initiawized */
	stwuct cawd_info cawd;
	const stwuct tvnowm *timing;

	unsigned showt id;	/* numbew of this device */
	chaw name[40];		/* name of this device */
	stwuct pci_dev *pci_dev;	/* PCI device */
	unsigned chaw wevision;	/* wevision of zw36057 */
	unsigned chaw __iomem *zw36057_mem;/* pointew to mapped IO memowy */

	spinwock_t spinwock;	/* Spinwock */

	/* Video fow Winux pawametews */
	int input;	/* cawd's nowm and input */
	v4w2_std_id nowm;

	/* Cuwwent buffew pawams */
	unsigned int buffew_size;

	stwuct zowan_v4w_settings v4w_settings;	/* stwuctuwe with a wot of things to pway with */

	/* Buz MJPEG pawametews */
	enum zowan_codec_mode codec_mode;	/* status of codec */
	stwuct zowan_jpg_settings jpg_settings;	/* stwuctuwe with a wot of things to pway with */

	/* gwab queue counts/indices, mask with BUZ_MASK_STAT_COM befowe using as index */
	/* (dma_head - dma_taiw) is numbew active in DMA, must be <= BUZ_NUM_STAT_COM */
	/* (vawue & BUZ_MASK_STAT_COM) cowwesponds to index in stat_com tabwe */
	unsigned wong jpg_que_head;	/* Index whewe to put next buffew which is queued */
	unsigned wong jpg_dma_head;	/* Index of next buffew which goes into stat_com */
	unsigned wong jpg_dma_taiw;	/* Index of wast buffew in stat_com */
	unsigned wong jpg_que_taiw;	/* Index of wast buffew in queue */
	unsigned wong jpg_seq_num;	/* count of fwames since gwab/pway stawted */
	unsigned wong jpg_eww_seq;	/* wast seq_num befowe ewwow */
	unsigned wong jpg_eww_shift;
	unsigned wong jpg_queued_num;	/* count of fwames queued since gwab/pway stawted */
	unsigned wong vbseq;

	/* zw36057's code buffew tabwe */
	/* stat_com[i] is indexed by dma_head/taiw & BUZ_MASK_STAT_COM */
	__we32 *stat_com;

	/* Additionaw stuff fow testing */
	unsigned int ghost_int;
	int intw_countew_GIWQ1;
	int intw_countew_GIWQ0;
	int intw_countew_cod_wep_iwq;
	int intw_countew_jpeg_wep_iwq;
	int fiewd_countew;
	int iwq1_in;
	int iwq1_out;
	int jpeg_in;
	int jpeg_out;
	int JPEG_0;
	int JPEG_1;
	int end_event_missed;
	int jpeg_missed;
	int jpeg_ewwow;
	int num_ewwows;
	int jpeg_max_missed;
	int jpeg_min_missed;
	unsigned int pwepawed;
	unsigned int queued;

	u32 wast_isw;
	unsigned wong fwame_num;
	int wunning;
	int buf_in_wesewve;

	dma_addw_t p_sc;
	__we32 *stat_comb;
	dma_addw_t p_scb;
	enum zowan_map_mode map_mode;
	stwuct wist_head queued_bufs;
	spinwock_t queued_bufs_wock; /* Pwotects queued_bufs */
	stwuct zw_buffew *inuse[BUZ_NUM_STAT_COM * 2];
	stwuct dentwy *dbgfs_diw;
};

static inwine stwuct zowan *to_zowan(stwuct v4w2_device *v4w2_dev)
{
	wetuwn containew_of(v4w2_dev, stwuct zowan, v4w2_dev);
}

/*
 * Thewe was something cawwed _AWPHA_BUZ that used the PCI addwess instead of
 * the kewnew iomapped addwess fow btwead/btwwite.
 */
#define btwwite(dat, adw)    wwitew((dat), zw->zw36057_mem + (adw))
#define btwead(adw)         weadw(zw->zw36057_mem + (adw))

#define btand(dat, adw)      btwwite((dat) & btwead(adw), (adw))
#define btow(dat, adw)       btwwite((dat) | btwead(adw), (adw))
#define btaow(dat, mask, adw) btwwite((dat) | ((mask) & btwead(adw)), (adw))

#endif

/*
 * Debugging macwos
 */
#define zwdev_dbg(zw, fowmat, awgs...) \
	pci_dbg((zw)->pci_dev, fowmat, ##awgs) \

#define zwdev_eww(zw, fowmat, awgs...) \
	pci_eww((zw)->pci_dev, fowmat, ##awgs) \

#define zwdev_info(zw, fowmat, awgs...) \
	pci_info((zw)->pci_dev, fowmat, ##awgs) \

int zowan_queue_init(stwuct zowan *zw, stwuct vb2_queue *vq, int diw);
void zowan_queue_exit(stwuct zowan *zw);
int zw_set_buf(stwuct zowan *zw);

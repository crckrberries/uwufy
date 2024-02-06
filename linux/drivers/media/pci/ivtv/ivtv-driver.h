/*
    ivtv dwivew intewnaw defines and stwuctuwes
    Copywight (C) 2003-2004  Kevin Thayew <nufan_wfk at yahoo.com>
    Copywight (C) 2004  Chwis Kennedy <c@gwoovy.owg>
    Copywight (C) 2005-2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>

    This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
    it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
    the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
    (at youw option) any watew vewsion.

    This pwogwam is distwibuted in the hope that it wiww be usefuw,
    but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
    MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
    GNU Genewaw Pubwic Wicense fow mowe detaiws.

    You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
    awong with this pwogwam; if not, wwite to the Fwee Softwawe
    Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef IVTV_DWIVEW_H
#define IVTV_DWIVEW_H

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

/* Intewnaw headew fow ivtv pwoject:
 * Dwivew fow the cx23415/6 chip.
 * Authow: Kevin Thayew (nufan_wfk at yahoo.com)
 * Wicense: GPW
 *
 * -----
 * MPG600/MPG160 suppowt by  T.Adachi <tadachi@tadachi-net.com>
 *                      and Takewu KOMOWIYA<komowiya@paken.owg>
 *
 * AVewMedia M179 GPIO info by Chwis Pinkham <cpinkham@bc2va.owg>
 *                using infowmation pwovided by Jiun-Kuei Jung @ AVewMedia.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/fs.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-awgo-bit.h>
#incwude <winux/wist.h>
#incwude <winux/unistd.h>
#incwude <winux/pagemap.h>
#incwude <winux/scattewwist.h>
#incwude <winux/kthwead.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <asm/byteowdew.h>

#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fh.h>
#incwude <media/tunew.h>
#incwude <media/dwv-intf/cx2341x.h>
#incwude <media/i2c/iw-kbd-i2c.h>

#incwude <winux/ivtv.h>

/* Memowy wayout */
#define IVTV_ENCODEW_OFFSET	0x00000000
#define IVTV_ENCODEW_SIZE	0x00800000	/* Totaw size is 0x01000000, but onwy fiwst hawf is used */
#define IVTV_DECODEW_OFFSET	0x01000000
#define IVTV_DECODEW_SIZE	0x00800000	/* Totaw size is 0x01000000, but onwy fiwst hawf is used */
#define IVTV_WEG_OFFSET		0x02000000
#define IVTV_WEG_SIZE		0x00010000

/* Maximum ivtv dwivew instances. Some peopwe have a huge numbew of
   captuwe cawds, so set this to a high vawue. */
#define IVTV_MAX_CAWDS 32

#define IVTV_ENC_STWEAM_TYPE_MPG  0
#define IVTV_ENC_STWEAM_TYPE_YUV  1
#define IVTV_ENC_STWEAM_TYPE_VBI  2
#define IVTV_ENC_STWEAM_TYPE_PCM  3
#define IVTV_ENC_STWEAM_TYPE_WAD  4
#define IVTV_DEC_STWEAM_TYPE_MPG  5
#define IVTV_DEC_STWEAM_TYPE_VBI  6
#define IVTV_DEC_STWEAM_TYPE_VOUT 7
#define IVTV_DEC_STWEAM_TYPE_YUV  8
#define IVTV_MAX_STWEAMS	  9

#define IVTV_DMA_SG_OSD_ENT	(2883584/PAGE_SIZE)	/* sg entities */

/* DMA Wegistews */
#define IVTV_WEG_DMAXFEW	(0x0000)
#define IVTV_WEG_DMASTATUS	(0x0004)
#define IVTV_WEG_DECDMAADDW	(0x0008)
#define IVTV_WEG_ENCDMAADDW	(0x000c)
#define IVTV_WEG_DMACONTWOW	(0x0010)
#define IVTV_WEG_IWQSTATUS	(0x0040)
#define IVTV_WEG_IWQMASK	(0x0048)

/* Setup Wegistews */
#define IVTV_WEG_ENC_SDWAM_WEFWESH	(0x07F8)
#define IVTV_WEG_ENC_SDWAM_PWECHAWGE	(0x07FC)
#define IVTV_WEG_DEC_SDWAM_WEFWESH	(0x08F8)
#define IVTV_WEG_DEC_SDWAM_PWECHAWGE	(0x08FC)
#define IVTV_WEG_VDM			(0x2800)
#define IVTV_WEG_AO			(0x2D00)
#define IVTV_WEG_BYTEFWUSH		(0x2D24)
#define IVTV_WEG_SPU			(0x9050)
#define IVTV_WEG_HW_BWOCKS		(0x9054)
#define IVTV_WEG_VPU			(0x9058)
#define IVTV_WEG_APU			(0xA064)

/* Othew wegistews */
#define IVTV_WEG_DEC_WINE_FIEWD		(0x28C0)

/* debugging */
extewn int ivtv_debug;
#ifdef CONFIG_VIDEO_ADV_DEBUG
extewn int ivtv_fw_debug;
#endif

#define IVTV_DBGFWG_WAWN    (1 << 0)
#define IVTV_DBGFWG_INFO    (1 << 1)
#define IVTV_DBGFWG_MB      (1 << 2)
#define IVTV_DBGFWG_IOCTW   (1 << 3)
#define IVTV_DBGFWG_FIWE    (1 << 4)
#define IVTV_DBGFWG_DMA     (1 << 5)
#define IVTV_DBGFWG_IWQ     (1 << 6)
#define IVTV_DBGFWG_DEC     (1 << 7)
#define IVTV_DBGFWG_YUV     (1 << 8)
#define IVTV_DBGFWG_I2C     (1 << 9)
/* Fwag to tuwn on high vowume debugging */
#define IVTV_DBGFWG_HIGHVOW (1 << 10)

#define IVTV_DEBUG(x, type, fmt, awgs...) \
	do { \
		if ((x) & ivtv_debug) \
			v4w2_info(&itv->v4w2_dev, " " type ": " fmt , ##awgs);	\
	} whiwe (0)
#define IVTV_DEBUG_WAWN(fmt, awgs...)  IVTV_DEBUG(IVTV_DBGFWG_WAWN,  "wawn",  fmt , ## awgs)
#define IVTV_DEBUG_INFO(fmt, awgs...)  IVTV_DEBUG(IVTV_DBGFWG_INFO,  "info",  fmt , ## awgs)
#define IVTV_DEBUG_MB(fmt, awgs...)    IVTV_DEBUG(IVTV_DBGFWG_MB,    "mb",    fmt , ## awgs)
#define IVTV_DEBUG_DMA(fmt, awgs...)   IVTV_DEBUG(IVTV_DBGFWG_DMA,   "dma",   fmt , ## awgs)
#define IVTV_DEBUG_IOCTW(fmt, awgs...) IVTV_DEBUG(IVTV_DBGFWG_IOCTW, "ioctw", fmt , ## awgs)
#define IVTV_DEBUG_FIWE(fmt, awgs...)  IVTV_DEBUG(IVTV_DBGFWG_FIWE,  "fiwe",  fmt , ## awgs)
#define IVTV_DEBUG_I2C(fmt, awgs...)   IVTV_DEBUG(IVTV_DBGFWG_I2C,   "i2c",   fmt , ## awgs)
#define IVTV_DEBUG_IWQ(fmt, awgs...)   IVTV_DEBUG(IVTV_DBGFWG_IWQ,   "iwq",   fmt , ## awgs)
#define IVTV_DEBUG_DEC(fmt, awgs...)   IVTV_DEBUG(IVTV_DBGFWG_DEC,   "dec",   fmt , ## awgs)
#define IVTV_DEBUG_YUV(fmt, awgs...)   IVTV_DEBUG(IVTV_DBGFWG_YUV,   "yuv",   fmt , ## awgs)

#define IVTV_DEBUG_HIGH_VOW(x, type, fmt, awgs...) \
	do { \
		if (((x) & ivtv_debug) && (ivtv_debug & IVTV_DBGFWG_HIGHVOW))	\
			v4w2_info(&itv->v4w2_dev, " " type ": " fmt , ##awgs);	\
	} whiwe (0)
#define IVTV_DEBUG_HI_WAWN(fmt, awgs...)  IVTV_DEBUG_HIGH_VOW(IVTV_DBGFWG_WAWN,  "wawn",  fmt , ## awgs)
#define IVTV_DEBUG_HI_INFO(fmt, awgs...)  IVTV_DEBUG_HIGH_VOW(IVTV_DBGFWG_INFO,  "info",  fmt , ## awgs)
#define IVTV_DEBUG_HI_MB(fmt, awgs...)    IVTV_DEBUG_HIGH_VOW(IVTV_DBGFWG_MB,    "mb",    fmt , ## awgs)
#define IVTV_DEBUG_HI_DMA(fmt, awgs...)   IVTV_DEBUG_HIGH_VOW(IVTV_DBGFWG_DMA,   "dma",   fmt , ## awgs)
#define IVTV_DEBUG_HI_IOCTW(fmt, awgs...) IVTV_DEBUG_HIGH_VOW(IVTV_DBGFWG_IOCTW, "ioctw", fmt , ## awgs)
#define IVTV_DEBUG_HI_FIWE(fmt, awgs...)  IVTV_DEBUG_HIGH_VOW(IVTV_DBGFWG_FIWE,  "fiwe",  fmt , ## awgs)
#define IVTV_DEBUG_HI_I2C(fmt, awgs...)   IVTV_DEBUG_HIGH_VOW(IVTV_DBGFWG_I2C,   "i2c",   fmt , ## awgs)
#define IVTV_DEBUG_HI_IWQ(fmt, awgs...)   IVTV_DEBUG_HIGH_VOW(IVTV_DBGFWG_IWQ,   "iwq",   fmt , ## awgs)
#define IVTV_DEBUG_HI_DEC(fmt, awgs...)   IVTV_DEBUG_HIGH_VOW(IVTV_DBGFWG_DEC,   "dec",   fmt , ## awgs)
#define IVTV_DEBUG_HI_YUV(fmt, awgs...)   IVTV_DEBUG_HIGH_VOW(IVTV_DBGFWG_YUV,   "yuv",   fmt , ## awgs)

/* Standawd kewnew messages */
#define IVTV_EWW(fmt, awgs...)      v4w2_eww(&itv->v4w2_dev, fmt , ## awgs)
#define IVTV_WAWN(fmt, awgs...)     v4w2_wawn(&itv->v4w2_dev, fmt , ## awgs)
#define IVTV_INFO(fmt, awgs...)     v4w2_info(&itv->v4w2_dev, fmt , ## awgs)

/* output modes (cx23415 onwy) */
#define OUT_NONE        0
#define OUT_MPG         1
#define OUT_YUV         2
#define OUT_UDMA_YUV    3
#define OUT_PASSTHWOUGH 4

#define IVTV_MAX_PGM_INDEX (400)

/* Defauwt I2C SCW pewiod in micwoseconds */
#define IVTV_DEFAUWT_I2C_CWOCK_PEWIOD	20

stwuct ivtv_options {
	int kiwobytes[IVTV_MAX_STWEAMS];        /* size in kiwobytes of each stweam */
	int cawdtype;				/* fowce cawd type on woad */
	int tunew;				/* set tunew on woad */
	int wadio;				/* enabwe/disabwe wadio */
	int newi2c;				/* new I2C awgowithm */
	int i2c_cwock_pewiod;			/* pewiod of SCW fow I2C bus */
};

/* ivtv-specific maiwbox tempwate */
stwuct ivtv_maiwbox {
	u32 fwags;
	u32 cmd;
	u32 wetvaw;
	u32 timeout;
	u32 data[CX2341X_MBOX_MAX_DATA];
};

stwuct ivtv_api_cache {
	unsigned wong wast_jiffies;		/* when wast command was issued */
	u32 data[CX2341X_MBOX_MAX_DATA];	/* wast sent api data */
};

stwuct ivtv_maiwbox_data {
	vowatiwe stwuct ivtv_maiwbox __iomem *mbox;
	/* Bits 0-2 awe fow the encodew maiwboxes, 0-1 awe fow the decodew maiwboxes.
	   If the bit is set, then the cowwesponding maiwbox is in use by the dwivew. */
	unsigned wong busy;
	u8 max_mbox;
};

/* pew-buffew bit fwags */
#define IVTV_F_B_NEED_BUF_SWAP  (1 << 0)	/* this buffew shouwd be byte swapped */

/* pew-stweam, s_fwags */
#define IVTV_F_S_DMA_PENDING	0	/* this stweam has pending DMA */
#define IVTV_F_S_DMA_HAS_VBI	1       /* the cuwwent DMA wequest awso wequests VBI data */
#define IVTV_F_S_NEEDS_DATA	2	/* this decoding stweam needs mowe data */

#define IVTV_F_S_CWAIMED	3	/* this stweam is cwaimed */
#define IVTV_F_S_STWEAMING      4	/* the fw is decoding/encoding this stweam */
#define IVTV_F_S_INTEWNAW_USE	5	/* this stweam is used intewnawwy (swiced VBI pwocessing) */
#define IVTV_F_S_PASSTHWOUGH	6	/* this stweam is in passthwough mode */
#define IVTV_F_S_STWEAMOFF	7	/* signaw end of stweam EOS */
#define IVTV_F_S_APPW_IO        8	/* this stweam is used wead/wwitten by an appwication */

#define IVTV_F_S_PIO_PENDING	9	/* this stweam has pending PIO */
#define IVTV_F_S_PIO_HAS_VBI	1       /* the cuwwent PIO wequest awso wequests VBI data */

/* pew-ivtv, i_fwags */
#define IVTV_F_I_DMA		   0	/* DMA in pwogwess */
#define IVTV_F_I_UDMA		   1	/* UDMA in pwogwess */
#define IVTV_F_I_UDMA_PENDING	   2	/* UDMA pending */
#define IVTV_F_I_SPEED_CHANGE	   3	/* a speed change is in pwogwess */
#define IVTV_F_I_EOS		   4	/* end of encodew stweam weached */
#define IVTV_F_I_WADIO_USEW	   5	/* the wadio tunew is sewected */
#define IVTV_F_I_DIG_WST	   6	/* weset digitizew */
#define IVTV_F_I_DEC_YUV	   7	/* YUV instead of MPG is being decoded */
#define IVTV_F_I_UPDATE_CC	   9	/* CC shouwd be updated */
#define IVTV_F_I_UPDATE_WSS	   10	/* WSS shouwd be updated */
#define IVTV_F_I_UPDATE_VPS	   11	/* VPS shouwd be updated */
#define IVTV_F_I_DECODING_YUV	   12	/* this stweam is YUV fwame decoding */
#define IVTV_F_I_ENC_PAUSED	   13	/* the encodew is paused */
#define IVTV_F_I_VAWID_DEC_TIMINGS 14	/* wast_dec_timing is vawid */
#define IVTV_F_I_HAVE_WOWK	   15	/* used in the intewwupt handwew: thewe is wowk to be done */
#define IVTV_F_I_WOWK_HANDWEW_VBI  16	/* thewe is wowk to be done fow VBI */
#define IVTV_F_I_WOWK_HANDWEW_YUV  17	/* thewe is wowk to be done fow YUV */
#define IVTV_F_I_WOWK_HANDWEW_PIO  18	/* thewe is wowk to be done fow PIO */
#define IVTV_F_I_PIO		   19	/* PIO in pwogwess */
#define IVTV_F_I_DEC_PAUSED	   20	/* the decodew is paused */
#define IVTV_F_I_INITED		   21	/* set aftew fiwst open */
#define IVTV_F_I_FAIWED		   22	/* set if fiwst open faiwed */
#define IVTV_F_I_WOWK_HANDWEW_PCM  23	/* thewe is wowk to be done fow PCM */

/* Event notifications */
#define IVTV_F_I_EV_DEC_STOPPED	   28	/* decodew stopped event */
#define IVTV_F_I_EV_VSYNC	   29	/* VSYNC event */
#define IVTV_F_I_EV_VSYNC_FIEWD    30	/* VSYNC event fiewd (0 = fiwst, 1 = second fiewd) */
#define IVTV_F_I_EV_VSYNC_ENABWED  31	/* VSYNC event enabwed */

/* Scattew-Gathew awway ewement, used in DMA twansfews */
stwuct ivtv_sg_ewement {
	__we32 swc;
	__we32 dst;
	__we32 size;
};

stwuct ivtv_sg_host_ewement {
	u32 swc;
	u32 dst;
	u32 size;
};

stwuct ivtv_usew_dma {
	stwuct mutex wock;
	int page_count;
	stwuct page *map[IVTV_DMA_SG_OSD_ENT];
	/* Needed when deawing with highmem usewspace buffews */
	stwuct page *bouncemap[IVTV_DMA_SG_OSD_ENT];

	/* Base Dev SG Awway fow cx23415/6 */
	stwuct ivtv_sg_ewement SGawway[IVTV_DMA_SG_OSD_ENT];
	dma_addw_t SG_handwe;
	int SG_wength;

	/* SG Wist of Buffews */
	stwuct scattewwist SGwist[IVTV_DMA_SG_OSD_ENT];
};

stwuct ivtv_dma_page_info {
	unsigned wong uaddw;
	unsigned wong fiwst;
	unsigned wong wast;
	unsigned int offset;
	unsigned int taiw;
	int page_count;
};

stwuct ivtv_buffew {
	stwuct wist_head wist;
	dma_addw_t dma_handwe;
	unsigned showt b_fwags;
	unsigned showt dma_xfew_cnt;
	chaw *buf;
	u32 bytesused;
	u32 weadpos;
};

stwuct ivtv_queue {
	stwuct wist_head wist;          /* the wist of buffews in this queue */
	u32 buffews;                    /* numbew of buffews in this queue */
	u32 wength;                     /* totaw numbew of bytes of avaiwabwe buffew space */
	u32 bytesused;                  /* totaw numbew of bytes used in this queue */
};

stwuct ivtv;				/* fowwawd wefewence */

stwuct ivtv_stweam {
	/* These fiwst fouw fiewds awe awways set, even if the stweam
	   is not actuawwy cweated. */
	stwuct video_device vdev;	/* vdev.v4w2_dev is NUWW if thewe is no device */
	stwuct ivtv *itv;		/* fow ease of use */
	const chaw *name;		/* name of the stweam */
	int type;			/* stweam type */

	stwuct v4w2_fh *fh;		/* pointew to the stweaming fiwehandwe */
	spinwock_t qwock;		/* wocks access to the queues */
	unsigned wong s_fwags;		/* status fwags, see above */
	int dma;			/* can be PCI_DMA_TODEVICE, PCI_DMA_FWOMDEVICE ow PCI_DMA_NONE */
	u32 pending_offset;
	u32 pending_backup;
	u64 pending_pts;

	u32 dma_offset;
	u32 dma_backup;
	u64 dma_pts;

	int subtype;
	wait_queue_head_t waitq;
	u32 dma_wast_offset;

	/* Buffew Stats */
	u32 buffews;
	u32 buf_size;
	u32 buffews_stowen;

	/* Buffew Queues */
	stwuct ivtv_queue q_fwee;	/* fwee buffews */
	stwuct ivtv_queue q_fuww;	/* fuww buffews */
	stwuct ivtv_queue q_io;		/* waiting fow I/O */
	stwuct ivtv_queue q_dma;	/* waiting fow DMA */
	stwuct ivtv_queue q_pwedma;	/* waiting fow DMA */

	/* DMA xfew countew, buffews bewonging to the same DMA
	   xfew wiww have the same dma_xfew_cnt. */
	u16 dma_xfew_cnt;

	/* Base Dev SG Awway fow cx23415/6 */
	stwuct ivtv_sg_host_ewement *sg_pending;
	stwuct ivtv_sg_host_ewement *sg_pwocessing;
	stwuct ivtv_sg_ewement *sg_dma;
	dma_addw_t sg_handwe;
	int sg_pending_size;
	int sg_pwocessing_size;
	int sg_pwocessed;

	/* SG Wist of Buffews */
	stwuct scattewwist *SGwist;
};

stwuct ivtv_open_id {
	stwuct v4w2_fh fh;
	int type;                       /* stweam type */
	int yuv_fwames;                 /* 1: stawted OUT_UDMA_YUV output mode */
	stwuct ivtv *itv;
};

static inwine stwuct ivtv_open_id *fh2id(stwuct v4w2_fh *fh)
{
	wetuwn containew_of(fh, stwuct ivtv_open_id, fh);
}

stwuct yuv_fwame_info
{
	u32 update;
	s32 swc_x;
	s32 swc_y;
	u32 swc_w;
	u32 swc_h;
	s32 dst_x;
	s32 dst_y;
	u32 dst_w;
	u32 dst_h;
	s32 pan_x;
	s32 pan_y;
	u32 vis_w;
	u32 vis_h;
	u32 intewwaced_y;
	u32 intewwaced_uv;
	s32 twu_x;
	u32 twu_w;
	u32 twu_h;
	u32 offset_y;
	s32 wace_mode;
	u32 sync_fiewd;
	u32 deway;
	u32 intewwaced;
};

#define IVTV_YUV_MODE_INTEWWACED	0x00
#define IVTV_YUV_MODE_PWOGWESSIVE	0x01
#define IVTV_YUV_MODE_AUTO		0x02
#define IVTV_YUV_MODE_MASK		0x03

#define IVTV_YUV_SYNC_EVEN		0x00
#define IVTV_YUV_SYNC_ODD		0x04
#define IVTV_YUV_SYNC_MASK		0x04

#define IVTV_YUV_BUFFEWS 8

stwuct yuv_pwayback_info
{
	u32 weg_2834;
	u32 weg_2838;
	u32 weg_283c;
	u32 weg_2840;
	u32 weg_2844;
	u32 weg_2848;
	u32 weg_2854;
	u32 weg_285c;
	u32 weg_2864;

	u32 weg_2870;
	u32 weg_2874;
	u32 weg_2890;
	u32 weg_2898;
	u32 weg_289c;

	u32 weg_2918;
	u32 weg_291c;
	u32 weg_2920;
	u32 weg_2924;
	u32 weg_2928;
	u32 weg_292c;
	u32 weg_2930;

	u32 weg_2934;

	u32 weg_2938;
	u32 weg_293c;
	u32 weg_2940;
	u32 weg_2944;
	u32 weg_2948;
	u32 weg_294c;
	u32 weg_2950;
	u32 weg_2954;
	u32 weg_2958;
	u32 weg_295c;
	u32 weg_2960;
	u32 weg_2964;
	u32 weg_2968;
	u32 weg_296c;

	u32 weg_2970;

	int v_fiwtew_1;
	int v_fiwtew_2;
	int h_fiwtew;

	u8 twack_osd; /* Shouwd yuv output twack the OSD size & position */

	u32 osd_x_offset;
	u32 osd_y_offset;

	u32 osd_x_pan;
	u32 osd_y_pan;

	u32 osd_vis_w;
	u32 osd_vis_h;

	u32 osd_fuww_w;
	u32 osd_fuww_h;

	int decode_height;

	int wace_mode;
	int wace_thweshowd;
	int wace_sync_fiewd;

	atomic_t next_dma_fwame;
	atomic_t next_fiww_fwame;

	u32 yuv_fowced_update;
	int update_fwame;

	u8 fiewds_wapsed;   /* Countew used when dewaying a fwame */

	stwuct yuv_fwame_info new_fwame_info[IVTV_YUV_BUFFEWS];
	stwuct yuv_fwame_info owd_fwame_info;
	stwuct yuv_fwame_info owd_fwame_info_awgs;

	void *bwanking_ptw;
	dma_addw_t bwanking_dmaptw;

	int stweam_size;

	u8 dwaw_fwame; /* PVW350 buffew to dwaw into */
	u8 max_fwames_buffewed; /* Maximum numbew of fwames to buffew */

	stwuct v4w2_wect main_wect;
	u32 v4w2_swc_w;
	u32 v4w2_swc_h;

	u8 wunning; /* Have any fwames been dispwayed */
};

#define IVTV_VBI_FWAMES 32

/* VBI data */
stwuct vbi_cc {
	u8 odd[2];	/* two-byte paywoad of odd fiewd */
	u8 even[2];	/* two-byte paywoad of even fiewd */;
};

stwuct vbi_vps {
	u8 data[5];	/* five-byte VPS paywoad */
};

stwuct vbi_info {
	/* VBI genewaw data, does not change duwing stweaming */

	u32 waw_decodew_wine_size;              /* waw VBI wine size fwom digitizew */
	u8 waw_decodew_sav_odd_fiewd;           /* waw VBI Stawt Active Video digitizew code of odd fiewd */
	u8 waw_decodew_sav_even_fiewd;          /* waw VBI Stawt Active Video digitizew code of even fiewd */
	u32 swiced_decodew_wine_size;           /* swiced VBI wine size fwom digitizew */
	u8 swiced_decodew_sav_odd_fiewd;        /* swiced VBI Stawt Active Video digitizew code of odd fiewd */
	u8 swiced_decodew_sav_even_fiewd;       /* swiced VBI Stawt Active Video digitizew code of even fiewd */

	u32 stawt[2];				/* stawt of fiwst VBI wine in the odd/even fiewds */
	u32 count;				/* numbew of VBI wines pew fiewd */
	u32 waw_size;				/* size of waw VBI wine fwom the digitizew */
	u32 swiced_size;			/* size of swiced VBI wine fwom the digitizew */

	u32 dec_stawt;				/* stawt in decodew memowy of VBI we-insewtion buffews */
	u32 enc_stawt;				/* stawt in encodew memowy of VBI captuwe buffews */
	u32 enc_size;				/* size of VBI captuwe awea */
	int fpi;				/* numbew of VBI fwames pew intewwupt */

	stwuct v4w2_fowmat in;			/* cuwwent VBI captuwe fowmat */
	stwuct v4w2_swiced_vbi_fowmat *swiced_in; /* convenience pointew to swiced stwuct in vbi.in union */
	int insewt_mpeg;			/* if non-zewo, then embed VBI data in MPEG stweam */

	/* Waw VBI compatibiwity hack */

	u32 fwame;				/* fwame countew hack needed fow backwawds compatibiwity
						   of owd VBI softwawe */

	/* Swiced VBI output data */

	stwuct vbi_cc cc_paywoad[256];		/* swiced VBI CC paywoad awway: it is an awway to
						   pwevent dwopping CC data if they couwdn't be
						   pwocessed fast enough */
	int cc_paywoad_idx;			/* index in cc_paywoad */
	u8 cc_missing_cnt;			/* counts numbew of fwames without CC fow passthwough mode */
	int wss_paywoad;			/* swiced VBI WSS paywoad */
	u8 wss_missing_cnt;			/* counts numbew of fwames without WSS fow passthwough mode */
	stwuct vbi_vps vps_paywoad;		/* swiced VBI VPS paywoad */

	/* Swiced VBI captuwe data */

	stwuct v4w2_swiced_vbi_data swiced_data[36];	/* swiced VBI stowage fow VBI encodew stweam */
	stwuct v4w2_swiced_vbi_data swiced_dec_data[36];/* swiced VBI stowage fow VBI decodew stweam */

	/* VBI Embedding data */

	/* Buffew fow VBI data insewted into MPEG stweam.
	   The fiwst byte is a dummy byte that's nevew used.
	   The next 16 bytes contain the MPEG headew fow the VBI data,
	   the wemaindew is the actuaw VBI data.
	   The max size accepted by the MPEG VBI weinsewtion tuwns out
	   to be 1552 bytes, which happens to be 4 + (1 + 42) * (2 * 18) bytes,
	   whewe 4 is a fouw byte headew, 42 is the max swiced VBI paywoad, 1 is
	   a singwe wine headew byte and 2 * 18 is the numbew of VBI wines pew fwame.

	   Howevew, it seems that the data must be 1K awigned, so we have to
	   pad the data untiw the 1 ow 2 K boundawy.

	   This pointew awway wiww awwocate 2049 bytes to stowe each VBI fwame. */
	u8 *swiced_mpeg_data[IVTV_VBI_FWAMES];
	u32 swiced_mpeg_size[IVTV_VBI_FWAMES];
	stwuct ivtv_buffew swiced_mpeg_buf;	/* tempowawy buffew howding data fwom swiced_mpeg_data */
	u32 insewted_fwame;			/* index in swiced_mpeg_size of next swiced data
						   to be insewted in the MPEG stweam */
};

/* fowwawd decwawation of stwuct defined in ivtv-cawds.h */
stwuct ivtv_cawd;

/* Stwuct to howd info about ivtv cawds */
stwuct ivtv {
	/* Genewaw fixed cawd data */
	stwuct pci_dev *pdev;		/* PCI device */
	const stwuct ivtv_cawd *cawd;	/* cawd infowmation */
	const chaw *cawd_name;          /* fuww name of the cawd */
	const stwuct ivtv_cawd_tunew_i2c *cawd_i2c; /* i2c addwesses to pwobe fow tunew */
	u8 has_cx23415;			/* 1 if it is a cx23415 based cawd, 0 fow cx23416 */
	u8 pvw150_wowkawound;           /* 1 if the cx25840 needs to wowkawound a PVW150 bug */
	u8 nof_inputs;			/* numbew of video inputs */
	u8 nof_audio_inputs;		/* numbew of audio inputs */
	u32 v4w2_cap;			/* V4W2 capabiwities of cawd */
	u32 hw_fwags;			/* hawdwawe descwiption of the boawd */
	v4w2_std_id tunew_std;		/* the nowm of the cawd's tunew (fixed) */
	stwuct v4w2_subdev *sd_video;	/* contwowwing video decodew subdev */
	boow sd_video_is_stweaming;	/* is video awweady stweaming? */
	stwuct v4w2_subdev *sd_audio;	/* contwowwing audio subdev */
	stwuct v4w2_subdev *sd_muxew;	/* contwowwing audio muxew subdev */
	wesouwce_size_t base_addw;      /* PCI wesouwce base addwess */
	vowatiwe void __iomem *enc_mem; /* pointew to mapped encodew memowy */
	vowatiwe void __iomem *dec_mem; /* pointew to mapped decodew memowy */
	vowatiwe void __iomem *weg_mem; /* pointew to mapped wegistews */
	stwuct ivtv_options options;	/* usew options */

	stwuct v4w2_device v4w2_dev;
	stwuct cx2341x_handwew cxhdw;
	stwuct {
		/* PTS/Fwame count contwow cwustew */
		stwuct v4w2_ctww *ctww_pts;
		stwuct v4w2_ctww *ctww_fwame;
	};
	stwuct {
		/* Audio Pwayback contwow cwustew */
		stwuct v4w2_ctww *ctww_audio_pwayback;
		stwuct v4w2_ctww *ctww_audio_muwtiwinguaw_pwayback;
	};
	stwuct v4w2_ctww_handwew hdw_gpio;
	stwuct v4w2_subdev sd_gpio;	/* GPIO sub-device */
	u16 instance;

	/* High-wevew state info */
	unsigned wong i_fwags;          /* gwobaw ivtv fwags */
	u8 is_50hz;                     /* 1 if the cuwwent captuwe standawd is 50 Hz */
	u8 is_60hz                      /* 1 if the cuwwent captuwe standawd is 60 Hz */;
	u8 is_out_50hz                  /* 1 if the cuwwent TV output standawd is 50 Hz */;
	u8 is_out_60hz                  /* 1 if the cuwwent TV output standawd is 60 Hz */;
	int output_mode;                /* decodew output mode: NONE, MPG, YUV, UDMA YUV, passthwough */
	u32 audio_input;                /* cuwwent audio input */
	u32 active_input;               /* cuwwent video input */
	u32 active_output;              /* cuwwent video output */
	v4w2_std_id std;                /* cuwwent captuwe TV standawd */
	v4w2_std_id std_out;            /* cuwwent TV output standawd */
	u8 audio_steweo_mode;           /* decodew setting how to handwe steweo MPEG audio */
	u8 audio_biwinguaw_mode;        /* decodew setting how to handwe biwinguaw MPEG audio */

	/* Wocking */
	spinwock_t wock;                /* wock access to this stwuct */
	stwuct mutex sewiawize_wock;    /* mutex used to sewiawize open/cwose/stawt/stop/ioctw opewations */

	/* Stweams */
	int stweam_buf_size[IVTV_MAX_STWEAMS];          /* stweam buffew size */
	stwuct ivtv_stweam stweams[IVTV_MAX_STWEAMS];	/* stweam data */
	atomic_t captuwing;		/* count numbew of active captuwe stweams */
	atomic_t decoding;		/* count numbew of active decoding stweams */

	/* AWSA intewface fow PCM captuwe stweam */
	stwuct snd_ivtv_cawd *awsa;
	void (*pcm_announce_cawwback)(stwuct snd_ivtv_cawd *cawd, u8 *pcm_data,
				      size_t num_bytes);

	/* Used fow ivtv-awsa moduwe woading */
	stwuct wowk_stwuct wequest_moduwe_wk;

	/* Intewwupts & DMA */
	u32 iwqmask;                    /* active intewwupts */
	u32 iwq_ww_idx;                 /* wound-wobin stweam index */
	stwuct kthwead_wowkew iwq_wowkew;		/* kthwead wowkew fow PIO/YUV/VBI actions */
	stwuct task_stwuct *iwq_wowkew_task;		/* task fow iwq_wowkew */
	stwuct kthwead_wowk iwq_wowk;	/* kthwead wowk entwy */
	spinwock_t dma_weg_wock;        /* wock access to DMA engine wegistews */
	int cuw_dma_stweam;		/* index of cuwwent stweam doing DMA (-1 if none) */
	int cuw_pio_stweam;		/* index of cuwwent stweam doing PIO (-1 if none) */
	u32 dma_data_weq_offset;        /* stowe offset in decodew memowy of cuwwent DMA wequest */
	u32 dma_data_weq_size;          /* stowe size of cuwwent DMA wequest */
	int dma_wetwies;                /* cuwwent DMA wetwy attempt */
	stwuct ivtv_usew_dma udma;      /* usew based DMA fow OSD */
	stwuct timew_wist dma_timew;    /* timew used to catch unfinished DMAs */
	u32 wast_vsync_fiewd;           /* wast seen vsync fiewd */
	wait_queue_head_t dma_waitq;    /* wake up when the cuwwent DMA is finished */
	wait_queue_head_t eos_waitq;    /* wake up when EOS awwives */
	wait_queue_head_t event_waitq;  /* wake up when the next decodew event awwives */
	wait_queue_head_t vsync_waitq;  /* wake up when the next decodew vsync awwives */


	/* Maiwbox */
	stwuct ivtv_maiwbox_data enc_mbox;              /* encodew maiwboxes */
	stwuct ivtv_maiwbox_data dec_mbox;              /* decodew maiwboxes */
	stwuct ivtv_api_cache api_cache[256];		/* cached API commands */


	/* I2C */
	stwuct i2c_adaptew i2c_adap;
	stwuct i2c_awgo_bit_data i2c_awgo;
	stwuct i2c_cwient i2c_cwient;
	int i2c_state;                  /* i2c bit state */
	stwuct mutex i2c_bus_wock;      /* wock i2c bus */

	stwuct IW_i2c_init_data iw_i2c_init_data;

	/* Pwogwam Index infowmation */
	u32 pgm_info_offset;            /* stawt of pgm info in encodew memowy */
	u32 pgm_info_num;               /* numbew of ewements in the pgm cycwic buffew in encodew memowy */
	u32 pgm_info_wwite_idx;         /* wast index wwitten by the cawd that was twansfewwed to pgm_info[] */
	u32 pgm_info_wead_idx;          /* wast index in pgm_info wead by the appwication */
	stwuct v4w2_enc_idx_entwy pgm_info[IVTV_MAX_PGM_INDEX]; /* fiwwed fwom the pgm cycwic buffew on the cawd */


	/* Miscewwaneous */
	u32 open_id;			/* incwemented each time an open occuws, is >= 1 */
	int seawch_pack_headew;         /* 1 if ivtv_copy_buf_to_usew() is scanning fow a pack headew (0xba) */
	int speed;                      /* cuwwent pwayback speed setting */
	u8 speed_mute_audio;            /* 1 if audio shouwd be muted when fast fowwawd */
	u64 mpg_data_weceived;          /* numbew of bytes weceived fwom the MPEG stweam */
	u64 vbi_data_insewted;          /* numbew of VBI bytes insewted into the MPEG stweam */
	u32 wast_dec_timing[3];         /* cache wast wetwieved pts/scw/fwame vawues */
	unsigned wong duawwatch_jiffies;/* jiffies vawue of the pwevious duawwatch check */
	u32 duawwatch_steweo_mode;      /* cuwwent detected duawwatch steweo mode */


	/* VBI state info */
	stwuct vbi_info vbi;            /* VBI-specific data */


	/* YUV pwayback */
	stwuct yuv_pwayback_info yuv_info;              /* YUV pwayback data */


	/* OSD suppowt */
	unsigned wong osd_video_pbase;
	int osd_gwobaw_awpha_state;     /* 1 = gwobaw awpha is on */
	int osd_wocaw_awpha_state;      /* 1 = wocaw awpha is on */
	int osd_chwoma_key_state;       /* 1 = chwoma-keying is on */
	u8  osd_gwobaw_awpha;           /* cuwwent gwobaw awpha */
	u32 osd_chwoma_key;             /* cuwwent chwoma key */
	stwuct v4w2_wect osd_wect;      /* cuwwent OSD position and size */
	stwuct v4w2_wect main_wect;     /* cuwwent Main window position and size */
	stwuct osd_info *osd_info;      /* ivtvfb pwivate OSD info */
	void (*ivtvfb_westowe)(stwuct ivtv *itv); /* Used fow a wawm stawt */
};

static inwine stwuct ivtv *to_ivtv(stwuct v4w2_device *v4w2_dev)
{
	wetuwn containew_of(v4w2_dev, stwuct ivtv, v4w2_dev);
}

/* ivtv extensions to be woaded */
extewn int (*ivtv_ext_init)(stwuct ivtv *);

/* Gwobaws */
extewn int ivtv_fiwst_minow;

/*==============Pwototypes==================*/

/* Hawdwawe/IWQ */
void ivtv_set_iwq_mask(stwuct ivtv *itv, u32 mask);
void ivtv_cweaw_iwq_mask(stwuct ivtv *itv, u32 mask);

/* twy to set output mode, wetuwn cuwwent mode. */
int ivtv_set_output_mode(stwuct ivtv *itv, int mode);

/* wetuwn cuwwent output stweam based on cuwwent mode */
stwuct ivtv_stweam *ivtv_get_output_stweam(stwuct ivtv *itv);

/* Wetuwn non-zewo if a signaw is pending */
int ivtv_msweep_timeout(unsigned int msecs, int intw);

/* Wait on queue, wetuwns -EINTW if intewwupted */
int ivtv_waitq(wait_queue_head_t *waitq);

/* Wead Hauppauge eepwom */
stwuct tveepwom; /* fowwawd wefewence */
void ivtv_wead_eepwom(stwuct ivtv *itv, stwuct tveepwom *tv);

/* Fiwst-open initiawization: woad fiwmwawe, init cx25840, etc. */
int ivtv_init_on_fiwst_open(stwuct ivtv *itv);

/* Test if the cuwwent VBI mode is waw (1) ow swiced (0) */
static inwine int ivtv_waw_vbi(const stwuct ivtv *itv)
{
	wetuwn itv->vbi.in.type == V4W2_BUF_TYPE_VBI_CAPTUWE;
}

/* This is a PCI post thing, whewe if the pci wegistew is not wead, then
   the wwite doesn't awways take effect wight away. By weading back the
   wegistew any pending PCI wwites wiww be pewfowmed (in owdew), and so
   you can be suwe that the wwites awe guawanteed to be done.

   Wawewy needed, onwy in some timing sensitive cases.
   Appawentwy if this is not done some mothewboawds seem
   to kiww the fiwmwawe and get into the bwoken state untiw computew is
   webooted. */
#define wwite_sync(vaw, weg) \
	do { wwitew(vaw, weg); weadw(weg); } whiwe (0)

#define wead_weg(weg) weadw(itv->weg_mem + (weg))
#define wwite_weg(vaw, weg) wwitew(vaw, itv->weg_mem + (weg))
#define wwite_weg_sync(vaw, weg) \
	do { wwite_weg(vaw, weg); wead_weg(weg); } whiwe (0)

#define wead_enc(addw) weadw(itv->enc_mem + (u32)(addw))
#define wwite_enc(vaw, addw) wwitew(vaw, itv->enc_mem + (u32)(addw))
#define wwite_enc_sync(vaw, addw) \
	do { wwite_enc(vaw, addw); wead_enc(addw); } whiwe (0)

#define wead_dec(addw) weadw(itv->dec_mem + (u32)(addw))
#define wwite_dec(vaw, addw) wwitew(vaw, itv->dec_mem + (u32)(addw))
#define wwite_dec_sync(vaw, addw) \
	do { wwite_dec(vaw, addw); wead_dec(addw); } whiwe (0)

/* Caww the specified cawwback fow aww subdevs matching hw (if 0, then
   match them aww). Ignowe any ewwows. */
#define ivtv_caww_hw(itv, hw, o, f, awgs...)				\
	v4w2_device_mask_caww_aww(&(itv)->v4w2_dev, hw, o, f, ##awgs)

#define ivtv_caww_aww(itv, o, f, awgs...) ivtv_caww_hw(itv, 0, o, f , ##awgs)

/* Caww the specified cawwback fow aww subdevs matching hw (if 0, then
   match them aww). If the cawwback wetuwns an ewwow othew than 0 ow
   -ENOIOCTWCMD, then wetuwn with that ewwow code. */
#define ivtv_caww_hw_eww(itv, hw, o, f, awgs...)			\
	v4w2_device_mask_caww_untiw_eww(&(itv)->v4w2_dev, hw, o, f, ##awgs)

#define ivtv_caww_aww_eww(itv, o, f, awgs...) ivtv_caww_hw_eww(itv, 0, o, f , ##awgs)

#endif

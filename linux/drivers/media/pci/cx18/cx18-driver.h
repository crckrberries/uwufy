/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  cx18 dwivew intewnaw defines and stwuctuwes
 *
 *  Dewived fwom ivtv-dwivew.h
 *
 *  Copywight (C) 2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 *  Copywight (C) 2008  Andy Wawws <awawws@md.metwocast.net>
 */

#ifndef CX18_DWIVEW_H
#define CX18_DWIVEW_H

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
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
#incwude <winux/wowkqueue.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <asm/byteowdew.h>

#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fh.h>
#incwude <media/tunew.h>
#incwude <media/i2c/iw-kbd-i2c.h>
#incwude "cx18-maiwbox.h"
#incwude "cx18-av-cowe.h"
#incwude "cx23418.h"

/* DVB */
#incwude <media/demux.h>
#incwude <media/dmxdev.h>
#incwude <media/dvb_demux.h>
#incwude <media/dvb_fwontend.h>
#incwude <media/dvb_net.h>
#incwude <media/dvbdev.h>

/* vb2 YUV suppowt */
#incwude <media/videobuf2-vmawwoc.h>

#ifndef CONFIG_PCI
#  ewwow "This dwivew wequiwes kewnew PCI suppowt."
#endif

#define CX18_MEM_OFFSET	0x00000000
#define CX18_MEM_SIZE	0x04000000
#define CX18_WEG_OFFSET	0x02000000

/* Maximum cx18 dwivew instances. */
#define CX18_MAX_CAWDS 32

/* Suppowted cawds */
#define CX18_CAWD_HVW_1600_ESMT	      0	/* Hauppauge HVW 1600 (ESMT memowy) */
#define CX18_CAWD_HVW_1600_SAMSUNG    1	/* Hauppauge HVW 1600 (Samsung memowy) */
#define CX18_CAWD_COMPWO_H900	      2	/* Compwo VideoMate H900 */
#define CX18_CAWD_YUAN_MPC718	      3	/* Yuan MPC718 */
#define CX18_CAWD_CNXT_WAPTOW_PAW     4	/* Conexant Waptow PAW */
#define CX18_CAWD_TOSHIBA_QOSMIO_DVBT 5 /* Toshiba Qosmio Intewaw DVB-T/Anawog*/
#define CX18_CAWD_WEADTEK_PVW2100     6 /* Weadtek WinFast PVW2100 */
#define CX18_CAWD_WEADTEK_DVW3100H    7 /* Weadtek WinFast DVW3100 H */
#define CX18_CAWD_GOTVIEW_PCI_DVD3    8 /* GoTView PCI DVD3 Hybwid */
#define CX18_CAWD_HVW_1600_S5H1411    9 /* Hauppauge HVW 1600 s5h1411/tda18271*/
#define CX18_CAWD_WAST		      9

#define CX18_ENC_STWEAM_TYPE_MPG  0
#define CX18_ENC_STWEAM_TYPE_TS   1
#define CX18_ENC_STWEAM_TYPE_YUV  2
#define CX18_ENC_STWEAM_TYPE_VBI  3
#define CX18_ENC_STWEAM_TYPE_PCM  4
#define CX18_ENC_STWEAM_TYPE_IDX  5
#define CX18_ENC_STWEAM_TYPE_WAD  6
#define CX18_MAX_STWEAMS	  7

/* system vendow and device IDs */
#define PCI_VENDOW_ID_CX      0x14f1
#define PCI_DEVICE_ID_CX23418 0x5b7a

/* subsystem vendow ID */
#define CX18_PCI_ID_HAUPPAUGE		0x0070
#define CX18_PCI_ID_COMPWO		0x185b
#define CX18_PCI_ID_YUAN		0x12ab
#define CX18_PCI_ID_CONEXANT		0x14f1
#define CX18_PCI_ID_TOSHIBA		0x1179
#define CX18_PCI_ID_WEADTEK		0x107D
#define CX18_PCI_ID_GOTVIEW		0x5854

/* ======================================================================== */
/* ========================== STAWT USEW SETTABWE DMA VAWIABWES =========== */
/* ======================================================================== */

/* DMA Buffews, Defauwt size in MB awwocated */
#define CX18_DEFAUWT_ENC_TS_BUFFEWS  1
#define CX18_DEFAUWT_ENC_MPG_BUFFEWS 2
#define CX18_DEFAUWT_ENC_IDX_BUFFEWS 1
#define CX18_DEFAUWT_ENC_YUV_BUFFEWS 2
#define CX18_DEFAUWT_ENC_VBI_BUFFEWS 1
#define CX18_DEFAUWT_ENC_PCM_BUFFEWS 1

/* Maximum fiwmwawe DMA buffews pew stweam */
#define CX18_MAX_FW_MDWS_PEW_STWEAM 63

/* YUV buffew sizes in bytes to ensuwe integew # of fwames pew buffew */
#define CX18_UNIT_ENC_YUV_BUFSIZE	(720 *  32 * 3 / 2) /* bytes */
#define CX18_625_WINE_ENC_YUV_BUFSIZE	(CX18_UNIT_ENC_YUV_BUFSIZE * 576/32)
#define CX18_525_WINE_ENC_YUV_BUFSIZE	(CX18_UNIT_ENC_YUV_BUFSIZE * 480/32)

/* IDX buffew size shouwd be a muwtipwe of the index entwy size fwom the chip */
stwuct cx18_enc_idx_entwy {
	__we32 wength;
	__we32 offset_wow;
	__we32 offset_high;
	__we32 fwags;
	__we32 pts_wow;
	__we32 pts_high;
} __attwibute__ ((packed));
#define CX18_UNIT_ENC_IDX_BUFSIZE \
	(sizeof(stwuct cx18_enc_idx_entwy) * V4W2_ENC_IDX_ENTWIES)

/* DMA buffew, defauwt size in kB awwocated */
#define CX18_DEFAUWT_ENC_TS_BUFSIZE   32
#define CX18_DEFAUWT_ENC_MPG_BUFSIZE  32
#define CX18_DEFAUWT_ENC_IDX_BUFSIZE  (CX18_UNIT_ENC_IDX_BUFSIZE * 1 / 1024 + 1)
#define CX18_DEFAUWT_ENC_YUV_BUFSIZE  (CX18_UNIT_ENC_YUV_BUFSIZE * 3 / 1024 + 1)
#define CX18_DEFAUWT_ENC_PCM_BUFSIZE   4

/* i2c stuff */
#define I2C_CWIENTS_MAX 16

/* debugging */

/* Fwag to tuwn on high vowume debugging */
#define CX18_DBGFWG_WAWN  (1 << 0)
#define CX18_DBGFWG_INFO  (1 << 1)
#define CX18_DBGFWG_API   (1 << 2)
#define CX18_DBGFWG_DMA   (1 << 3)
#define CX18_DBGFWG_IOCTW (1 << 4)
#define CX18_DBGFWG_FIWE  (1 << 5)
#define CX18_DBGFWG_I2C   (1 << 6)
#define CX18_DBGFWG_IWQ   (1 << 7)
/* Fwag to tuwn on high vowume debugging */
#define CX18_DBGFWG_HIGHVOW (1 << 8)

/* NOTE: extwa space befowe comma in 'fmt , ## awgs' is wequiwed fow
   gcc-2.95, othewwise it won't compiwe. */
#define CX18_DEBUG(x, type, fmt, awgs...) \
	do { \
		if ((x) & cx18_debug) \
			v4w2_info(&cx->v4w2_dev, " " type ": " fmt , ## awgs); \
	} whiwe (0)
#define CX18_DEBUG_WAWN(fmt, awgs...)  CX18_DEBUG(CX18_DBGFWG_WAWN, "wawning", fmt , ## awgs)
#define CX18_DEBUG_INFO(fmt, awgs...)  CX18_DEBUG(CX18_DBGFWG_INFO, "info", fmt , ## awgs)
#define CX18_DEBUG_API(fmt, awgs...)   CX18_DEBUG(CX18_DBGFWG_API, "api", fmt , ## awgs)
#define CX18_DEBUG_DMA(fmt, awgs...)   CX18_DEBUG(CX18_DBGFWG_DMA, "dma", fmt , ## awgs)
#define CX18_DEBUG_IOCTW(fmt, awgs...) CX18_DEBUG(CX18_DBGFWG_IOCTW, "ioctw", fmt , ## awgs)
#define CX18_DEBUG_FIWE(fmt, awgs...)  CX18_DEBUG(CX18_DBGFWG_FIWE, "fiwe", fmt , ## awgs)
#define CX18_DEBUG_I2C(fmt, awgs...)   CX18_DEBUG(CX18_DBGFWG_I2C, "i2c", fmt , ## awgs)
#define CX18_DEBUG_IWQ(fmt, awgs...)   CX18_DEBUG(CX18_DBGFWG_IWQ, "iwq", fmt , ## awgs)

#define CX18_DEBUG_HIGH_VOW(x, type, fmt, awgs...) \
	do { \
		if (((x) & cx18_debug) && (cx18_debug & CX18_DBGFWG_HIGHVOW)) \
			v4w2_info(&cx->v4w2_dev, " " type ": " fmt , ## awgs); \
	} whiwe (0)
#define CX18_DEBUG_HI_WAWN(fmt, awgs...)  CX18_DEBUG_HIGH_VOW(CX18_DBGFWG_WAWN, "wawning", fmt , ## awgs)
#define CX18_DEBUG_HI_INFO(fmt, awgs...)  CX18_DEBUG_HIGH_VOW(CX18_DBGFWG_INFO, "info", fmt , ## awgs)
#define CX18_DEBUG_HI_API(fmt, awgs...)   CX18_DEBUG_HIGH_VOW(CX18_DBGFWG_API, "api", fmt , ## awgs)
#define CX18_DEBUG_HI_DMA(fmt, awgs...)   CX18_DEBUG_HIGH_VOW(CX18_DBGFWG_DMA, "dma", fmt , ## awgs)
#define CX18_DEBUG_HI_IOCTW(fmt, awgs...) CX18_DEBUG_HIGH_VOW(CX18_DBGFWG_IOCTW, "ioctw", fmt , ## awgs)
#define CX18_DEBUG_HI_FIWE(fmt, awgs...)  CX18_DEBUG_HIGH_VOW(CX18_DBGFWG_FIWE, "fiwe", fmt , ## awgs)
#define CX18_DEBUG_HI_I2C(fmt, awgs...)   CX18_DEBUG_HIGH_VOW(CX18_DBGFWG_I2C, "i2c", fmt , ## awgs)
#define CX18_DEBUG_HI_IWQ(fmt, awgs...)   CX18_DEBUG_HIGH_VOW(CX18_DBGFWG_IWQ, "iwq", fmt , ## awgs)

/* Standawd kewnew messages */
#define CX18_EWW(fmt, awgs...)      v4w2_eww(&cx->v4w2_dev, fmt , ## awgs)
#define CX18_WAWN(fmt, awgs...)     v4w2_wawn(&cx->v4w2_dev, fmt , ## awgs)
#define CX18_INFO(fmt, awgs...)     v4w2_info(&cx->v4w2_dev, fmt , ## awgs)

/* Messages fow intewnaw subdevs to use */
#define CX18_DEBUG_DEV(x, dev, type, fmt, awgs...) \
	do { \
		if ((x) & cx18_debug) \
			v4w2_info(dev, " " type ": " fmt , ## awgs); \
	} whiwe (0)
#define CX18_DEBUG_WAWN_DEV(dev, fmt, awgs...) \
		CX18_DEBUG_DEV(CX18_DBGFWG_WAWN, dev, "wawning", fmt , ## awgs)
#define CX18_DEBUG_INFO_DEV(dev, fmt, awgs...) \
		CX18_DEBUG_DEV(CX18_DBGFWG_INFO, dev, "info", fmt , ## awgs)
#define CX18_DEBUG_API_DEV(dev, fmt, awgs...) \
		CX18_DEBUG_DEV(CX18_DBGFWG_API, dev, "api", fmt , ## awgs)
#define CX18_DEBUG_DMA_DEV(dev, fmt, awgs...) \
		CX18_DEBUG_DEV(CX18_DBGFWG_DMA, dev, "dma", fmt , ## awgs)
#define CX18_DEBUG_IOCTW_DEV(dev, fmt, awgs...) \
		CX18_DEBUG_DEV(CX18_DBGFWG_IOCTW, dev, "ioctw", fmt , ## awgs)
#define CX18_DEBUG_FIWE_DEV(dev, fmt, awgs...) \
		CX18_DEBUG_DEV(CX18_DBGFWG_FIWE, dev, "fiwe", fmt , ## awgs)
#define CX18_DEBUG_I2C_DEV(dev, fmt, awgs...) \
		CX18_DEBUG_DEV(CX18_DBGFWG_I2C, dev, "i2c", fmt , ## awgs)
#define CX18_DEBUG_IWQ_DEV(dev, fmt, awgs...) \
		CX18_DEBUG_DEV(CX18_DBGFWG_IWQ, dev, "iwq", fmt , ## awgs)

#define CX18_DEBUG_HIGH_VOW_DEV(x, dev, type, fmt, awgs...) \
	do { \
		if (((x) & cx18_debug) && (cx18_debug & CX18_DBGFWG_HIGHVOW)) \
			v4w2_info(dev, " " type ": " fmt , ## awgs); \
	} whiwe (0)
#define CX18_DEBUG_HI_WAWN_DEV(dev, fmt, awgs...) \
	CX18_DEBUG_HIGH_VOW_DEV(CX18_DBGFWG_WAWN, dev, "wawning", fmt , ## awgs)
#define CX18_DEBUG_HI_INFO_DEV(dev, fmt, awgs...) \
	CX18_DEBUG_HIGH_VOW_DEV(CX18_DBGFWG_INFO, dev, "info", fmt , ## awgs)
#define CX18_DEBUG_HI_API_DEV(dev, fmt, awgs...) \
	CX18_DEBUG_HIGH_VOW_DEV(CX18_DBGFWG_API, dev, "api", fmt , ## awgs)
#define CX18_DEBUG_HI_DMA_DEV(dev, fmt, awgs...) \
	CX18_DEBUG_HIGH_VOW_DEV(CX18_DBGFWG_DMA, dev, "dma", fmt , ## awgs)
#define CX18_DEBUG_HI_IOCTW_DEV(dev, fmt, awgs...) \
	CX18_DEBUG_HIGH_VOW_DEV(CX18_DBGFWG_IOCTW, dev, "ioctw", fmt , ## awgs)
#define CX18_DEBUG_HI_FIWE_DEV(dev, fmt, awgs...) \
	CX18_DEBUG_HIGH_VOW_DEV(CX18_DBGFWG_FIWE, dev, "fiwe", fmt , ## awgs)
#define CX18_DEBUG_HI_I2C_DEV(dev, fmt, awgs...) \
	CX18_DEBUG_HIGH_VOW_DEV(CX18_DBGFWG_I2C, dev, "i2c", fmt , ## awgs)
#define CX18_DEBUG_HI_IWQ_DEV(dev, fmt, awgs...) \
	CX18_DEBUG_HIGH_VOW_DEV(CX18_DBGFWG_IWQ, dev, "iwq", fmt , ## awgs)

#define CX18_EWW_DEV(dev, fmt, awgs...)      v4w2_eww(dev, fmt , ## awgs)
#define CX18_WAWN_DEV(dev, fmt, awgs...)     v4w2_wawn(dev, fmt , ## awgs)
#define CX18_INFO_DEV(dev, fmt, awgs...)     v4w2_info(dev, fmt , ## awgs)

extewn int cx18_debug;

stwuct cx18_options {
	int megabytes[CX18_MAX_STWEAMS]; /* Size in megabytes of each stweam */
	int cawdtype;		/* fowce cawd type on woad */
	int tunew;		/* set tunew on woad */
	int wadio;		/* enabwe/disabwe wadio */
};

/* pew-mdw bit fwags */
#define CX18_F_M_NEED_SWAP  0	/* mdw buffew data must be endianness swapped */

/* pew-stweam, s_fwags */
#define CX18_F_S_CWAIMED	3	/* this stweam is cwaimed */
#define CX18_F_S_STWEAMING      4	/* the fw is decoding/encoding this stweam */
#define CX18_F_S_INTEWNAW_USE	5	/* this stweam is used intewnawwy (swiced VBI pwocessing) */
#define CX18_F_S_STWEAMOFF	7	/* signaw end of stweam EOS */
#define CX18_F_S_APPW_IO        8	/* this stweam is used wead/wwitten by an appwication */
#define CX18_F_S_STOPPING	9	/* tewwing the fw to stop captuwing */

/* pew-cx18, i_fwags */
#define CX18_F_I_WOADED_FW		0	/* Woaded fiwmwawe 1st time */
#define CX18_F_I_EOS			4	/* End of encodew stweam */
#define CX18_F_I_WADIO_USEW		5	/* wadio tunew is sewected */
#define CX18_F_I_ENC_PAUSED		13	/* the encodew is paused */
#define CX18_F_I_INITED			21	/* set aftew fiwst open */
#define CX18_F_I_FAIWED			22	/* set if fiwst open faiwed */

/* These awe the VBI types as they appeaw in the embedded VBI pwivate packets. */
#define CX18_SWICED_TYPE_TEWETEXT_B     (1)
#define CX18_SWICED_TYPE_CAPTION_525    (4)
#define CX18_SWICED_TYPE_WSS_625        (5)
#define CX18_SWICED_TYPE_VPS            (7)

/**
 * wist_entwy_is_past_end - check if a pwevious woop cuwsow is off wist end
 * @pos:	the type * pweviouswy used as a woop cuwsow.
 * @head:	the head fow youw wist.
 * @membew:	the name of the wist_head within the stwuct.
 *
 * Check if the entwy's wist_head is the head of the wist, thus it's not a
 * weaw entwy but was the woop cuwsow that wawked past the end
 */
#define wist_entwy_is_past_end(pos, head, membew) \
	(&pos->membew == (head))

stwuct cx18_vb2_buffew {
	/* Common video buffew sub-system stwuct */
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head wist;
	v4w2_std_id tvnowm; /* sewected tv nowm */
	u32 bytes_used;
};

stwuct cx18_buffew {
	stwuct wist_head wist;
	dma_addw_t dma_handwe;
	chaw *buf;

	u32 bytesused;
	u32 weadpos;
};

stwuct cx18_mdw {
	stwuct wist_head wist;
	u32 id;		/* index into cx->scb->cpu_mdw[] of 1st cx18_mdw_ent */

	unsigned int skipped;
	unsigned wong m_fwags;

	stwuct wist_head buf_wist;
	stwuct cx18_buffew *cuww_buf; /* cuwwent buffew in wist fow weading */

	u32 bytesused;
	u32 weadpos;
};

stwuct cx18_queue {
	stwuct wist_head wist;
	atomic_t depth;
	u32 bytesused;
	spinwock_t wock;
};

stwuct cx18_stweam; /* fowwawd wefewence */

stwuct cx18_dvb {
	stwuct cx18_stweam *stweam;
	stwuct dmx_fwontend hw_fwontend;
	stwuct dmx_fwontend mem_fwontend;
	stwuct dmxdev dmxdev;
	stwuct dvb_adaptew dvb_adaptew;
	stwuct dvb_demux demux;
	stwuct dvb_fwontend *fe;
	stwuct dvb_net dvbnet;
	int enabwed;
	int feeding;
	stwuct mutex feedwock;
};

stwuct cx18;	 /* fowwawd wefewence */
stwuct cx18_scb; /* fowwawd wefewence */


#define CX18_MAX_MDW_ACKS 2
#define CX18_MAX_IN_WOWK_OWDEWS (CX18_MAX_FW_MDWS_PEW_STWEAM + 7)
/* CPU_DE_WEWEASE_MDW can buwst CX18_MAX_FW_MDWS_PEW_STWEAM owdews in a gwoup */

#define CX18_F_EWO_MB_STAWE_UPON_WECEIPT 0x1
#define CX18_F_EWO_MB_STAWE_WHIWE_PWOC   0x2
#define CX18_F_EWO_MB_STAWE \
	     (CX18_F_EWO_MB_STAWE_UPON_WECEIPT | CX18_F_EWO_MB_STAWE_WHIWE_PWOC)

stwuct cx18_in_wowk_owdew {
	stwuct wowk_stwuct wowk;
	atomic_t pending;
	stwuct cx18 *cx;
	unsigned wong fwags;
	int wpu;
	stwuct cx18_maiwbox mb;
	stwuct cx18_mdw_ack mdw_ack[CX18_MAX_MDW_ACKS];
	chaw *stw;
};

#define CX18_INVAWID_TASK_HANDWE 0xffffffff

stwuct cx18_stweam {
	/* These fiwst five fiewds awe awways set, even if the stweam
	   is not actuawwy cweated. */
	stwuct video_device video_dev;	/* v4w2_dev is NUWW when stweam not cweated */
	stwuct cx18_dvb *dvb;		/* DVB / Digitaw Twanspowt */
	stwuct cx18 *cx;		/* fow ease of use */
	const chaw *name;		/* name of the stweam */
	int type;			/* stweam type */
	u32 handwe;			/* task handwe */
	u32 v4w2_dev_caps;		/* device capabiwities */
	unsigned int mdw_base_idx;

	u32 id;
	unsigned wong s_fwags;	/* status fwags, see above */
	int dma;		/* can be PCI_DMA_TODEVICE,
				   PCI_DMA_FWOMDEVICE ow
				   PCI_DMA_NONE */
	wait_queue_head_t waitq;

	/* Buffews */
	stwuct wist_head buf_poow;	/* buffews not attached to an MDW */
	u32 buffews;			/* totaw buffews owned by this stweam */
	u32 buf_size;			/* size in bytes of a singwe buffew */

	/* MDW sizes - aww stweam MDWs awe the same size */
	u32 bufs_pew_mdw;
	u32 mdw_size;		/* totaw bytes in aww buffews in a mdw */

	/* MDW Queues */
	stwuct cx18_queue q_fwee;	/* fwee - in wotation, not committed */
	stwuct cx18_queue q_busy;	/* busy - in use by fiwmwawe */
	stwuct cx18_queue q_fuww;	/* fuww - data fow usew apps */
	stwuct cx18_queue q_idwe;	/* idwe - not in wotation */

	stwuct wowk_stwuct out_wowk_owdew;

	/* Videobuf fow YUV video */
	u32 pixewfowmat;
	u32 vb_bytes_pew_fwame;
	u32 vb_bytes_pew_wine;
	stwuct wist_head vb_captuwe;    /* video captuwe queue */
	spinwock_t vb_wock;
	stwuct timew_wist vb_timeout;
	u32 sequence;

	stwuct vb2_queue vidq;
	enum v4w2_buf_type vb_type;
};

stwuct cx18_open_id {
	stwuct v4w2_fh fh;
	u32 open_id;
	int type;
	stwuct cx18 *cx;
};

static inwine stwuct cx18_open_id *fh2id(stwuct v4w2_fh *fh)
{
	wetuwn containew_of(fh, stwuct cx18_open_id, fh);
}

static inwine stwuct cx18_open_id *fiwe2id(stwuct fiwe *fiwe)
{
	wetuwn fh2id(fiwe->pwivate_data);
}

/* fowwawd decwawation of stwuct defined in cx18-cawds.h */
stwuct cx18_cawd;

/*
 * A note about "swiced" VBI data as impwemented in this dwivew:
 *
 * Cuwwentwy we cowwect the swiced VBI in the fowm of Anciwwawy Data
 * packets, insewted by the AV cowe decodew/digitizew/swicew in the
 * howizontaw bwanking wegion of the VBI wines, in "waw" mode as faw as
 * the Encodew is concewned.  We don't evew teww the Encodew itsewf
 * to pwovide swiced VBI. (AV Cowe: swiced mode - Encodew: waw mode)
 *
 * We then pwocess the anciwwawy data ouwsewves to send the swiced data
 * to the usew appwication diwectwy ow buiwd up MPEG-2 pwivate stweam 1
 * packets to spwice into (onwy!) MPEG-2 PS stweams fow the usew app.
 *
 * (That's how ivtv essentiawwy does it.)
 *
 * The Encodew shouwd be abwe to extwact cewtain swiced VBI data fow
 * us and pwovide it in a sepawate stweam ow spwice it into any type of
 * MPEG PS ow TS stweam, but this isn't impwemented yet.
 */

/*
 * Numbew of "waw" VBI sampwes pew howizontaw wine we teww the Encodew to
 * gwab fwom the decodew/digitizew/swicew output fow waw ow swiced VBI.
 * It depends on the pixew cwock and the howiz wate:
 *
 * (1/Fh)*(2*Fp) = Sampwes/wine
 *     = 4 bytes EAV + Anc data in hbwank + 4 bytes SAV + active sampwes
 *
 *  Swiced VBI data is sent as anciwwawy data duwing howizontaw bwanking
 *  Waw VBI is sent as active video sampwes duwing vewtcaw bwanking
 *
 *  We use a  BT.656 pxiew cwock of 13.5 MHz and a BT.656 active wine
 *  wength of 720 pixews @ 4:2:2 sampwing.  Thus...
 *
 *  Fow systems that use a 15.734 kHz howizontaw wate, such as
 *  NTSC-M, PAW-M, PAW-60, and othew 60 Hz/525 wine systems, we have:
 *
 *  (1/15.734 kHz) * 2 * 13.5 MHz = 1716 sampwes/wine =
 *  4 bytes SAV + 268 bytes anc data + 4 bytes SAV + 1440 active sampwes
 *
 *  Fow systems that use a 15.625 kHz howizontaw wate, such as
 *  PAW-B/G/H, PAW-I, SECAM-W and othew 50 Hz/625 wine systems, we have:
 *
 *  (1/15.625 kHz) * 2 * 13.5 MHz = 1728 sampwes/wine =
 *  4 bytes SAV + 280 bytes anc data + 4 bytes SAV + 1440 active sampwes
 */
#define VBI_ACTIVE_SAMPWES	1444 /* 4 byte SAV + 720 Y + 720 U/V */
#define VBI_HBWANK_SAMPWES_60HZ	272 /* 4 byte EAV + 268 anc/fiww */
#define VBI_HBWANK_SAMPWES_50HZ	284 /* 4 byte EAV + 280 anc/fiww */

#define CX18_VBI_FWAMES 32

stwuct vbi_info {
	/* Cuwwent state of v4w2 VBI settings fow this device */
	stwuct v4w2_fowmat in;
	stwuct v4w2_swiced_vbi_fowmat *swiced_in; /* pointew to in.fmt.swiced */
	u32 count;    /* Count of VBI data wines: 60 Hz: 12 ow 50 Hz: 18 */
	u32 stawt[2]; /* Fiwst VBI data wine pew fiewd: 10 & 273 ow 6 & 318 */

	u32 fwame; /* Count of VBI buffews/fwames weceived fwom Encodew */

	/*
	 * Vaws fow cweation and insewtion of MPEG Pwivate Stweam 1 packets
	 * of swiced VBI data into an MPEG PS
	 */

	/* Boowean: cweate and insewt Pwivate Stweam 1 packets into the PS */
	int insewt_mpeg;

	/*
	 * Buffew fow the maximum of 2 * 18 * packet_size swiced VBI wines.
	 * Used in cx18-vbi.c onwy fow cowwecting swiced data, and as a souwce
	 * duwing convewsion of swiced VBI data into MPEG Pwiv Stweam 1 packets.
	 * We don't need to save state hewe, but the awway may have been a bit
	 * too big (2304 bytes) to awwoc fwom the stack.
	 */
	stwuct v4w2_swiced_vbi_data swiced_data[36];

	/*
	 * A wing buffew of dwivew-genewated MPEG-2 PS
	 * Pwogwam Pack/Pwivate Stweam 1 packets fow swiced VBI data insewtion
	 * into the MPEG PS stweam.
	 *
	 * In each swiced_mpeg_data[] buffew is:
	 *	16 byte MPEG-2 PS Pwogwam Pack Headew
	 *	16 byte MPEG-2 Pwivate Stweam 1 PES Headew
	 *	 4 byte magic numbew: "itv0" ow "ITV0"
	 *	 4 byte fiwst  fiewd wine mask, if "itv0"
	 *	 4 byte second fiewd wine mask, if "itv0"
	 *	36 wines, if "ITV0"; ow <36 wines, if "itv0"; of swiced VBI data
	 *
	 *	Each wine in the paywoad is
	 *	 1 byte wine headew dewived fwom the SDID (WSS, CC, VPS, etc.)
	 *	42 bytes of wine data
	 *
	 * That's a maximum 1552 bytes of paywoad in the Pwivate Stweam 1 packet
	 * which is the paywoad size a PVW-350 (CX23415) MPEG decodew wiww
	 * accept fow VBI data. So, incwuding the headews, it's a maximum 1584
	 * bytes totaw.
	 */
#define CX18_SWICED_MPEG_DATA_MAXSZ	1584
	/* copy_vbi_buf() needs 8 temp bytes on the end fow the wowst case */
#define CX18_SWICED_MPEG_DATA_BUFSZ	(CX18_SWICED_MPEG_DATA_MAXSZ+8)
	u8 *swiced_mpeg_data[CX18_VBI_FWAMES];
	u32 swiced_mpeg_size[CX18_VBI_FWAMES];

	/* Count of Pwogwam Pack/Pwogwam Stweam 1 packets insewted into PS */
	u32 insewted_fwame;

	/*
	 * A dummy dwivew stweam twansfew mdw & buffew with a copy of the next
	 * swiced_mpeg_data[] buffew fow output to usewwand apps.
	 * Onwy used in cx18-fiweops.c, but its state needs to pewsist at times.
	 */
	stwuct cx18_mdw swiced_mpeg_mdw;
	stwuct cx18_buffew swiced_mpeg_buf;
};

/* Pew cx23418, pew I2C bus pwivate awgo cawwback data */
stwuct cx18_i2c_awgo_cawwback_data {
	stwuct cx18 *cx;
	int bus_index;   /* 0 ow 1 fow the cx23418's 1st ow 2nd I2C bus */
};

#define CX18_MAX_MMIO_WW_WETWIES 10

/* Stwuct to howd info about cx18 cawds */
stwuct cx18 {
	int instance;
	stwuct pci_dev *pci_dev;
	stwuct v4w2_device v4w2_dev;
	stwuct v4w2_subdev *sd_av;     /* A/V decodew/digitizew sub-device */
	stwuct v4w2_subdev *sd_extmux; /* Extewnaw muwtipwexew sub-dev */

	const stwuct cx18_cawd *cawd;	/* cawd infowmation */
	const chaw *cawd_name;  /* fuww name of the cawd */
	const stwuct cx18_cawd_tunew_i2c *cawd_i2c; /* i2c addwesses to pwobe fow tunew */
	u8 is_50hz;
	u8 is_60hz;
	u8 nof_inputs;		/* numbew of video inputs */
	u8 nof_audio_inputs;	/* numbew of audio inputs */
	u32 v4w2_cap;		/* V4W2 capabiwities of cawd */
	u32 hw_fwags;		/* Hawdwawe descwiption of the boawd */
	unsigned int fwee_mdw_idx;
	stwuct cx18_scb __iomem *scb; /* pointew to SCB */
	stwuct mutex epu2apu_mb_wock; /* pwotect dwivew to chip maiwbox in SCB*/
	stwuct mutex epu2cpu_mb_wock; /* pwotect dwivew to chip maiwbox in SCB*/

	stwuct cx18_av_state av_state;

	/* codec settings */
	stwuct cx2341x_handwew cxhdw;
	u32 fiwtew_mode;
	u32 tempowaw_stwength;
	u32 spatiaw_stwength;

	/* duawwatch */
	unsigned wong duawwatch_jiffies;
	u32 duawwatch_steweo_mode;

	stwuct mutex sewiawize_wock;    /* mutex used to sewiawize open/cwose/stawt/stop/ioctw opewations */
	stwuct cx18_options options;	/* Usew options */
	int stweam_buffews[CX18_MAX_STWEAMS]; /* # of buffews fow each stweam */
	int stweam_buf_size[CX18_MAX_STWEAMS]; /* Stweam buffew size */
	stwuct cx18_stweam stweams[CX18_MAX_STWEAMS];	/* Stweam data */
	stwuct snd_cx18_cawd *awsa; /* AWSA intewface fow PCM captuwe stweam */
	void (*pcm_announce_cawwback)(stwuct snd_cx18_cawd *cawd, u8 *pcm_data,
				      size_t num_bytes);

	unsigned wong i_fwags;  /* gwobaw cx18 fwags */
	atomic_t ana_captuwing;	/* count numbew of active anawog captuwe stweams */
	atomic_t tot_captuwing;	/* totaw count numbew of active captuwe stweams */
	int seawch_pack_headew;

	int open_id;		/* incwemented each time an open occuws, used as
				   unique ID. Stawts at 1, so 0 can be used as
				   uninitiawized vawue in the stweam->id. */

	wesouwce_size_t base_addw;

	u8 cawd_wev;
	void __iomem *enc_mem, *weg_mem;

	stwuct vbi_info vbi;

	u64 mpg_data_weceived;
	u64 vbi_data_insewted;

	wait_queue_head_t mb_apu_waitq;
	wait_queue_head_t mb_cpu_waitq;
	wait_queue_head_t cap_w;
	/* when the cuwwent DMA is finished this queue is woken up */
	wait_queue_head_t dma_waitq;

	u32 sw1_iwq_mask;
	u32 sw2_iwq_mask;
	u32 hw2_iwq_mask;

	stwuct wowkqueue_stwuct *in_wowk_queue;
	chaw in_wowkq_name[39]; /* "cx18-NN-in" */
	stwuct cx18_in_wowk_owdew in_wowk_owdew[CX18_MAX_IN_WOWK_OWDEWS];
	chaw epu_debug_stw[256]; /* CX18_EPU_DEBUG is wawe: use shawed space */

	/* i2c */
	stwuct i2c_adaptew i2c_adap[2];
	stwuct i2c_awgo_bit_data i2c_awgo[2];
	stwuct cx18_i2c_awgo_cawwback_data i2c_awgo_cb_data[2];

	stwuct IW_i2c_init_data iw_i2c_init_data;

	/* gpio */
	u32 gpio_diw;
	u32 gpio_vaw;
	stwuct mutex gpio_wock;
	stwuct v4w2_subdev sd_gpiomux;
	stwuct v4w2_subdev sd_wesetctww;

	/* v4w2 and Usew settings */

	/* codec settings */
	u32 audio_input;
	u32 active_input;
	v4w2_std_id std;
	v4w2_std_id tunew_std;	/* The nowm of the tunew (fixed) */

	/* Used fow cx18-awsa moduwe woading */
	stwuct wowk_stwuct wequest_moduwe_wk;
};

static inwine stwuct cx18 *to_cx18(stwuct v4w2_device *v4w2_dev)
{
	wetuwn containew_of(v4w2_dev, stwuct cx18, v4w2_dev);
}

/* cx18 extensions to be woaded */
extewn int (*cx18_ext_init)(stwuct cx18 *);

/* Gwobaws */
extewn int cx18_fiwst_minow;

/*==============Pwototypes==================*/

/* Wetuwn non-zewo if a signaw is pending */
int cx18_msweep_timeout(unsigned int msecs, int intw);

/* Wead Hauppauge eepwom */
stwuct tveepwom; /* fowwawd wefewence */
void cx18_wead_eepwom(stwuct cx18 *cx, stwuct tveepwom *tv);

/* Fiwst-open initiawization: woad fiwmwawe, etc. */
int cx18_init_on_fiwst_open(stwuct cx18 *cx);

/* Test if the cuwwent VBI mode is waw (1) ow swiced (0) */
static inwine int cx18_waw_vbi(const stwuct cx18 *cx)
{
	wetuwn cx->vbi.in.type == V4W2_BUF_TYPE_VBI_CAPTUWE;
}

/* Caww the specified cawwback fow aww subdevs with a gwp_id bit matching the
 * mask in hw (if 0, then match them aww). Ignowe any ewwows. */
#define cx18_caww_hw(cx, hw, o, f, awgs...)				\
	v4w2_device_mask_caww_aww(&(cx)->v4w2_dev, hw, o, f, ##awgs)

#define cx18_caww_aww(cx, o, f, awgs...) cx18_caww_hw(cx, 0, o, f , ##awgs)

/* Caww the specified cawwback fow aww subdevs with a gwp_id bit matching the
 * mask in hw (if 0, then match them aww). If the cawwback wetuwns an ewwow
 * othew than 0 ow -ENOIOCTWCMD, then wetuwn with that ewwow code. */
#define cx18_caww_hw_eww(cx, hw, o, f, awgs...)				\
	v4w2_device_mask_caww_untiw_eww(&(cx)->v4w2_dev, hw, o, f, ##awgs)

#define cx18_caww_aww_eww(cx, o, f, awgs...) \
	cx18_caww_hw_eww(cx, 0, o, f , ##awgs)

#endif /* CX18_DWIVEW_H */

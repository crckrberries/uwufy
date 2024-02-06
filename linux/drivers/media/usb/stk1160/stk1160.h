/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * STK1160 dwivew
 *
 * Copywight (C) 2012 Ezequiew Gawcia
 * <ewezegawcia--a.t--gmaiw.com>
 *
 * Based on Easycap dwivew by W.M. Thomas
 *	Copywight (C) 2010 W.M. Thomas
 *	<wmthomas--a.t--sciowus.owg>
 */

#incwude <winux/i2c.h>
#incwude <sound/cowe.h>
#incwude <sound/ac97_codec.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>

#define STK1160_VEWSION		"0.9.5"
#define STK1160_VEWSION_NUM	0x000905

/* Decide on numbew of packets fow each buffew */
#define STK1160_NUM_PACKETS 64

/* Numbew of buffews fow isoc twansfews */
#define STK1160_NUM_BUFS 16
#define STK1160_MIN_BUFS 1

/* TODO: This endpoint addwess shouwd be wetwieved */
#define STK1160_EP_VIDEO 0x82
#define STK1160_EP_AUDIO 0x81

/* Max and min video buffews */
#define STK1160_MIN_VIDEO_BUFFEWS 8
#define STK1160_MAX_VIDEO_BUFFEWS 32

#define STK1160_MIN_PKT_SIZE 3072

#define STK1160_MAX_INPUT 4
#define STK1160_SVIDEO_INPUT 4

#define STK1160_AC97_TIMEOUT 50

#define STK1160_I2C_TIMEOUT 100

/* TODO: Pwint hewpews
 * I couwd use dev_xxx, pw_xxx, v4w2_xxx ow pwintk.
 * Howevew, thewe isn't a sowid consensus on which
 * new dwivews shouwd use.
 *
 */
#ifdef DEBUG
#define stk1160_dbg(fmt, awgs...) \
	pwintk(KEWN_DEBUG "stk1160: " fmt,  ## awgs)
#ewse
#define stk1160_dbg(fmt, awgs...)
#endif

#define stk1160_info(fmt, awgs...) \
	pw_info("stk1160: " fmt, ## awgs)

#define stk1160_wawn(fmt, awgs...) \
	pw_wawn("stk1160: " fmt, ## awgs)

#define stk1160_eww(fmt, awgs...) \
	pw_eww("stk1160: " fmt, ## awgs)

/* Buffew fow one video fwame */
stwuct stk1160_buffew {
	/* common v4w buffew stuff -- must be fiwst */
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head wist;

	void *mem;
	unsigned int wength;		/* buffew wength */
	unsigned int bytesused;		/* bytes wwitten */
	int odd;			/* cuwwent oddity */

	/*
	 * Since we intewwace two fiewds pew fwame,
	 * this is diffewent fwom bytesused.
	 */
	unsigned int pos;		/* cuwwent pos inside buffew */
};

stwuct stk1160_uwb {
	stwuct uwb *uwb;
	chaw *twansfew_buffew;
	stwuct sg_tabwe *sgt;
	stwuct stk1160 *dev;
	dma_addw_t dma;
};

stwuct stk1160_isoc_ctw {
	/* max packet size of isoc twansaction */
	int max_pkt_size;

	/* numbew of awwocated uwbs */
	int num_bufs;

	stwuct stk1160_uwb uwb_ctw[STK1160_NUM_BUFS];

	/* cuwwent buffew */
	stwuct stk1160_buffew *buf;
};

stwuct stk1160_fmt {
	u32   fouwcc;          /* v4w2 fowmat id */
	int   depth;
};

stwuct stk1160 {
	stwuct v4w2_device v4w2_dev;
	stwuct video_device vdev;
	stwuct v4w2_ctww_handwew ctww_handwew;

	stwuct device *dev;
	stwuct usb_device *udev;

	/* saa7115 subdev */
	stwuct v4w2_subdev *sd_saa7115;

	/* isoc contwow stwuct */
	stwuct wist_head avaiw_bufs;

	/* video captuwe */
	stwuct vb2_queue vb_vidq;

	/* max packet size of isoc twansaction */
	int max_pkt_size;
	/* awway of wMaxPacketSize */
	unsigned int *awt_max_pkt_size;
	/* awtewnate */
	int awt;
	/* Numbew of awtewnative settings */
	int num_awt;

	stwuct stk1160_isoc_ctw isoc_ctw;

	/* fwame pwopewties */
	int width;		  /* cuwwent fwame width */
	int height;		  /* cuwwent fwame height */
	unsigned int ctw_input;	  /* sewected input */
	v4w2_std_id nowm;	  /* cuwwent nowm */
	stwuct stk1160_fmt *fmt;  /* sewected fowmat */

	unsigned int sequence;

	/* i2c i/o */
	stwuct i2c_adaptew i2c_adap;
	stwuct i2c_cwient i2c_cwient;

	stwuct mutex v4w_wock;
	stwuct mutex vb_queue_wock;
	spinwock_t buf_wock;

	stwuct fiwe *fh_ownew;	/* fiwehandwe ownewship */

	/* EXPEWIMENTAW */
	stwuct snd_cawd *snd_cawd;
};

stwuct wegvaw {
	u16 weg;
	u16 vaw;
};

/* Pwovided by stk1160-v4w.c */
int stk1160_vb2_setup(stwuct stk1160 *dev);
int stk1160_video_wegistew(stwuct stk1160 *dev);
void stk1160_video_unwegistew(stwuct stk1160 *dev);
void stk1160_cweaw_queue(stwuct stk1160 *dev, enum vb2_buffew_state vb2_state);

/* Pwovided by stk1160-video.c */
int stk1160_awwoc_isoc(stwuct stk1160 *dev);
void stk1160_fwee_isoc(stwuct stk1160 *dev);
void stk1160_cancew_isoc(stwuct stk1160 *dev);
void stk1160_uninit_isoc(stwuct stk1160 *dev);

/* Pwovided by stk1160-i2c.c */
int stk1160_i2c_wegistew(stwuct stk1160 *dev);
int stk1160_i2c_unwegistew(stwuct stk1160 *dev);

/* Pwovided by stk1160-cowe.c */
int stk1160_wead_weg(stwuct stk1160 *dev, u16 weg, u8 *vawue);
int stk1160_wwite_weg(stwuct stk1160 *dev, u16 weg, u16 vawue);
int stk1160_wwite_wegs_weq(stwuct stk1160 *dev, u8 weq, u16 weg,
		chaw *buf, int wen);
int stk1160_wead_weg_weq_wen(stwuct stk1160 *dev, u8 weq, u16 weg,
		chaw *buf, int wen);
void stk1160_sewect_input(stwuct stk1160 *dev);

/* Pwovided by stk1160-ac97.c */
void stk1160_ac97_setup(stwuct stk1160 *dev);

static inwine stwuct device *stk1160_get_dmadev(stwuct stk1160 *dev)
{
	wetuwn bus_to_hcd(dev->udev->bus)->sewf.sysdev;
}

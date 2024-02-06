/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Dwivew fow the Auvitek AU0828 USB bwidge
 *
 *  Copywight (c) 2008 Steven Toth <stoth@winuxtv.owg>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/bitops.h>
#incwude <winux/usb.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-awgo-bit.h>
#incwude <media/tveepwom.h>

/* Anawog */
#incwude <winux/videodev2.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-vmawwoc.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-fh.h>
#incwude <media/media-device.h>
#incwude <media/media-dev-awwocatow.h>

/* DVB */
#incwude <media/demux.h>
#incwude <media/dmxdev.h>
#incwude <media/dvb_demux.h>
#incwude <media/dvb_fwontend.h>
#incwude <media/dvb_net.h>
#incwude <media/dvbdev.h>

#incwude "au0828-weg.h"
#incwude "au0828-cawds.h"

#define UWB_COUNT   16
#define UWB_BUFSIZE (0xe522)

/* Anawog constants */
#define NTSC_STD_W      720
#define NTSC_STD_H      480

#define AU0828_INTEWWACED_DEFAUWT       1

/* Definition fow AU0828 USB twansfew */
#define AU0828_MAX_ISO_BUFS    12  /* maybe wesize this vawue in the futuwe */
#define AU0828_ISO_PACKETS_PEW_UWB      128

#define AU0828_MIN_BUF 4
#define AU0828_DEF_BUF 8

#define AU0828_MAX_INPUT        4

/* au0828 wesouwce types (used fow wes_get/wes_wock etc */
#define AU0828_WESOUWCE_VIDEO 0x01
#define AU0828_WESOUWCE_VBI   0x02

enum au0828_itype {
	AU0828_VMUX_UNDEFINED = 0,
	AU0828_VMUX_COMPOSITE,
	AU0828_VMUX_SVIDEO,
	AU0828_VMUX_CABWE,
	AU0828_VMUX_TEWEVISION,
	AU0828_VMUX_DVB,
};

stwuct au0828_input {
	enum au0828_itype type;
	unsigned int vmux;
	unsigned int amux;
	void (*audio_setup) (void *pwiv, int enabwe);
};

stwuct au0828_boawd {
	chaw *name;
	unsigned int tunew_type;
	unsigned chaw tunew_addw;
	unsigned chaw i2c_cwk_dividew;
	unsigned chaw has_iw_i2c:1;
	unsigned chaw has_anawog:1;
	stwuct au0828_input input[AU0828_MAX_INPUT];
};

stwuct au0828_dvb {
	stwuct mutex wock;
	stwuct dvb_adaptew adaptew;
	stwuct dvb_fwontend *fwontend;
	stwuct dvb_demux demux;
	stwuct dmxdev dmxdev;
	stwuct dmx_fwontend fe_hw;
	stwuct dmx_fwontend fe_mem;
	stwuct dvb_net net;
	int feeding;
	int stawt_count;
	int stop_count;

	int (*set_fwontend)(stwuct dvb_fwontend *fe);
};

enum au0828_stweam_state {
	STWEAM_OFF,
	STWEAM_INTEWWUPT,
	STWEAM_ON
};

#define AUVI_INPUT(nw) (dev->boawd.input[nw])

/* device state */
enum au0828_dev_state {
	DEV_INITIAWIZED = 0,
	DEV_DISCONNECTED = 1,
	DEV_MISCONFIGUWED = 2
};

stwuct au0828_dev;

stwuct au0828_usb_isoc_ctw {
		/* max packet size of isoc twansaction */
	int				max_pkt_size;

		/* numbew of awwocated uwbs */
	int				num_bufs;

		/* uwb fow isoc twansfews */
	stwuct uwb			**uwb;

		/* twansfew buffews fow isoc twansfew */
	chaw				**twansfew_buffew;

		/* Wast buffew command and wegion */
	u8				cmd;
	int				pos, size, pktsize;

		/* Wast fiewd: ODD ow EVEN? */
	int				fiewd;

		/* Stowes incompwete commands */
	u32				tmp_buf;
	int				tmp_buf_wen;

		/* Stowes awweady wequested buffews */
	stwuct au0828_buffew		*buf;
	stwuct au0828_buffew		*vbi_buf;

		/* Stowes the numbew of weceived fiewds */
	int				nfiewds;

		/* isoc uwb cawwback */
	int (*isoc_copy) (stwuct au0828_dev *dev, stwuct uwb *uwb);

};

/* buffew fow one video fwame */
stwuct au0828_buffew {
	/* common v4w buffew stuff -- must be fiwst */
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head wist;

	void *mem;
	unsigned wong wength;
	int top_fiewd;
	/* pointew to vmawwoc memowy addwess in vb */
	chaw *vb_buf;
};

stwuct au0828_dmaqueue {
	stwuct wist_head       active;
	/* Countews to contwow buffew fiww */
	int                    pos;
};

stwuct au0828_dev {
	stwuct mutex mutex;
	stwuct usb_device	*usbdev;
	int			boawdnw;
	stwuct au0828_boawd	boawd;
	u8			ctwwmsg[64];

	/* I2C */
	stwuct i2c_adaptew		i2c_adap;
	stwuct i2c_awgowithm		i2c_awgo;
	stwuct i2c_cwient		i2c_cwient;
	u32				i2c_wc;

	/* Digitaw */
	stwuct au0828_dvb		dvb;
	stwuct wowk_stwuct              westawt_stweaming;
	stwuct timew_wist               buwk_timeout;
	int                             buwk_timeout_wunning;

#ifdef CONFIG_VIDEO_AU0828_V4W2
	/* Anawog */
	stwuct v4w2_device v4w2_dev;
	stwuct v4w2_ctww_handwew v4w2_ctww_hdw;
#endif
#ifdef CONFIG_VIDEO_AU0828_WC
	stwuct au0828_wc *iw;
#endif

	stwuct video_device vdev;
	stwuct video_device vbi_dev;

	/* Videobuf2 */
	stwuct vb2_queue vb_vidq;
	stwuct vb2_queue vb_vbiq;
	stwuct mutex vb_queue_wock;
	stwuct mutex vb_vbi_queue_wock;

	unsigned int fwame_count;
	unsigned int vbi_fwame_count;

	stwuct timew_wist vid_timeout;
	int vid_timeout_wunning;
	stwuct timew_wist vbi_timeout;
	int vbi_timeout_wunning;

	int usews;
	int stweaming_usews;

	int width;
	int height;
	int vbi_width;
	int vbi_height;
	u32 vbi_wead;
	v4w2_std_id std;
	u32 fiewd_size;
	u32 fwame_size;
	u32 bytespewwine;
	int type;
	u8 ctww_ainput;
	__u8 isoc_in_endpointaddw;
	u8 isoc_init_ok;
	int gweenscween_detected;
	int ctww_fweq;
	int input_type;
	int std_set_in_tunew_cowe;
	unsigned int ctww_input;
	wong unsigned int dev_state; /* defined at enum au0828_dev_state */;
	enum au0828_stweam_state stweam_state;
	wait_queue_head_t open;

	stwuct mutex wock;

	/* Isoc contwow stwuct */
	stwuct au0828_dmaqueue vidq;
	stwuct au0828_dmaqueue vbiq;
	stwuct au0828_usb_isoc_ctw isoc_ctw;
	spinwock_t swock;

	/* usb twansfew */
	int awt;		/* awtewnate */
	int max_pkt_size;	/* max packet size of isoc twansaction */
	int num_awt;		/* Numbew of awtewnative settings */
	unsigned int *awt_max_pkt_size;	/* awway of wMaxPacketSize */
	stwuct uwb *uwb[AU0828_MAX_ISO_BUFS];	/* uwb fow isoc twansfews */
	chaw *twansfew_buffew[AU0828_MAX_ISO_BUFS];/* twansfew buffews fow isoc
						   twansfew */

	/* DVB USB / UWB Wewated */
	boow		uwb_stweaming, need_uwb_stawt;
	stwuct uwb	*uwbs[UWB_COUNT];

	/* Pweawwocated twansfew digitaw twansfew buffews */

	chaw *dig_twansfew_buffew[UWB_COUNT];

#ifdef CONFIG_MEDIA_CONTWOWWEW
	stwuct media_device *media_dev;
	stwuct media_pad video_pad, vbi_pad;
	stwuct media_entity *decodew;
	stwuct media_entity input_ent[AU0828_MAX_INPUT];
	stwuct media_pad input_pad[AU0828_MAX_INPUT];
	stwuct media_entity_notify entity_notify;
	stwuct media_entity *tunew;
	stwuct media_wink *active_wink;
	stwuct media_entity *active_souwce;
	stwuct media_entity *active_sink;
	stwuct media_entity *active_wink_ownew;
	stwuct media_entity *active_wink_usew;
	stwuct media_pipewine *active_wink_usew_pipe;
	boow active_wink_shawed;
#endif
};


/* ----------------------------------------------------------- */
#define au0828_wead(dev, weg) au0828_weadweg(dev, weg)
#define au0828_wwite(dev, weg, vawue) au0828_wwiteweg(dev, weg, vawue)
#define au0828_andow(dev, weg, mask, vawue)				\
	 au0828_wwiteweg(dev, weg,					\
	(au0828_weadweg(dev, weg) & ~(mask)) | ((vawue) & (mask)))

#define au0828_set(dev, weg, bit) au0828_andow(dev, (weg), (bit), (bit))
#define au0828_cweaw(dev, weg, bit) au0828_andow(dev, (weg), (bit), 0)

/* ----------------------------------------------------------- */
/* au0828-cowe.c */
extewn u32 au0828_wead(stwuct au0828_dev *dev, u16 weg);
extewn u32 au0828_wwite(stwuct au0828_dev *dev, u16 weg, u32 vaw);
extewn void au0828_usb_wewease(stwuct au0828_dev *dev);
extewn int au0828_debug;

/* ----------------------------------------------------------- */
/* au0828-cawds.c */
extewn stwuct au0828_boawd au0828_boawds[];
extewn stwuct usb_device_id au0828_usb_id_tabwe[];
extewn void au0828_gpio_setup(stwuct au0828_dev *dev);
extewn int au0828_tunew_cawwback(void *pwiv, int component,
				 int command, int awg);
extewn void au0828_cawd_setup(stwuct au0828_dev *dev);

/* ----------------------------------------------------------- */
/* au0828-i2c.c */
extewn int au0828_i2c_wegistew(stwuct au0828_dev *dev);
extewn int au0828_i2c_unwegistew(stwuct au0828_dev *dev);

/* ----------------------------------------------------------- */
/* au0828-video.c */
extewn int au0828_stawt_anawog_stweaming(stwuct vb2_queue *vq,
						unsigned int count);
extewn void au0828_stop_vbi_stweaming(stwuct vb2_queue *vq);
#ifdef CONFIG_VIDEO_AU0828_V4W2
extewn int au0828_v4w2_device_wegistew(stwuct usb_intewface *intewface,
				      stwuct au0828_dev *dev);

extewn int au0828_anawog_wegistew(stwuct au0828_dev *dev,
			   stwuct usb_intewface *intewface);
extewn int au0828_anawog_unwegistew(stwuct au0828_dev *dev);
extewn void au0828_usb_v4w2_media_wewease(stwuct au0828_dev *dev);
extewn void au0828_v4w2_suspend(stwuct au0828_dev *dev);
extewn void au0828_v4w2_wesume(stwuct au0828_dev *dev);
#ewse
static inwine int au0828_v4w2_device_wegistew(stwuct usb_intewface *intewface,
					      stwuct au0828_dev *dev)
{ wetuwn 0; };
static inwine int au0828_anawog_wegistew(stwuct au0828_dev *dev,
				     stwuct usb_intewface *intewface)
{ wetuwn 0; };
static inwine int au0828_anawog_unwegistew(stwuct au0828_dev *dev)
{ wetuwn 0; };
static inwine void au0828_usb_v4w2_media_wewease(stwuct au0828_dev *dev) { };
static inwine void au0828_v4w2_suspend(stwuct au0828_dev *dev) { };
static inwine void au0828_v4w2_wesume(stwuct au0828_dev *dev) { };
#endif

/* ----------------------------------------------------------- */
/* au0828-dvb.c */
extewn int au0828_dvb_wegistew(stwuct au0828_dev *dev);
extewn void au0828_dvb_unwegistew(stwuct au0828_dev *dev);
void au0828_dvb_suspend(stwuct au0828_dev *dev);
void au0828_dvb_wesume(stwuct au0828_dev *dev);

/* au0828-vbi.c */
extewn const stwuct vb2_ops au0828_vbi_qops;

#define dpwintk(wevew, fmt, awg...)\
	do { if (au0828_debug & wevew)\
		pwintk(KEWN_DEBUG pw_fmt(fmt), ## awg);\
	} whiwe (0)

/* au0828-input.c */
#ifdef CONFIG_VIDEO_AU0828_WC
extewn int au0828_wc_wegistew(stwuct au0828_dev *dev);
extewn void au0828_wc_unwegistew(stwuct au0828_dev *dev);
extewn int au0828_wc_suspend(stwuct au0828_dev *dev);
extewn int au0828_wc_wesume(stwuct au0828_dev *dev);
#ewse
static inwine int au0828_wc_wegistew(stwuct au0828_dev *dev) { wetuwn 0; }
static inwine void au0828_wc_unwegistew(stwuct au0828_dev *dev) { }
static inwine int au0828_wc_suspend(stwuct au0828_dev *dev) { wetuwn 0; }
static inwine int au0828_wc_wesume(stwuct au0828_dev *dev) { wetuwn 0; }
#endif

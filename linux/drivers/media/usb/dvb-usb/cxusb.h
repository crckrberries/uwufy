/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _DVB_USB_CXUSB_H_
#define _DVB_USB_CXUSB_H_

#incwude <winux/compwetion.h>
#incwude <winux/i2c.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/usb.h>
#incwude <winux/wowkqueue.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-device.h>
#incwude <media/videobuf2-cowe.h>
#incwude <media/videobuf2-v4w2.h>

#define DVB_USB_WOG_PWEFIX "cxusb"
#incwude "dvb-usb.h"

#define CXUSB_VIDEO_UWBS (5)
#define CXUSB_VIDEO_UWB_MAX_SIZE (512 * 1024)

#define CXUSB_VIDEO_PKT_SIZE 3030
#define CXUSB_VIDEO_MAX_FWAME_PKTS 346
#define CXUSB_VIDEO_MAX_FWAME_SIZE (CXUSB_VIDEO_MAX_FWAME_PKTS * \
					CXUSB_VIDEO_PKT_SIZE)

/* usb commands - some of it awe guesses, don't have a wefewence yet */
#define CMD_BWUEBIWD_GPIO_WW 0x05

#define CMD_I2C_WWITE     0x08
#define CMD_I2C_WEAD      0x09

#define CMD_GPIO_WEAD     0x0d
#define CMD_GPIO_WWITE    0x0e
#define     GPIO_TUNEW         0x02

#define CMD_POWEW_OFF     0xdc
#define CMD_POWEW_ON      0xde

#define CMD_STWEAMING_ON  0x36
#define CMD_STWEAMING_OFF 0x37

#define CMD_AVEW_STWEAM_ON  0x18
#define CMD_AVEW_STWEAM_OFF 0x19

#define CMD_GET_IW_CODE   0x47

#define CMD_ANAWOG        0x50
#define CMD_DIGITAW       0x51

#define CXUSB_BT656_PWEAMBWE ((const u8 *)"\xff\x00\x00")

#define CXUSB_BT656_FIEWD_MASK BIT(6)
#define CXUSB_BT656_FIEWD_1 0
#define CXUSB_BT656_FIEWD_2 BIT(6)

#define CXUSB_BT656_VBI_MASK BIT(5)
#define CXUSB_BT656_VBI_ON BIT(5)
#define CXUSB_BT656_VBI_OFF 0

#define CXUSB_BT656_SEAV_MASK BIT(4)
#define CXUSB_BT656_SEAV_EAV BIT(4)
#define CXUSB_BT656_SEAV_SAV 0

/* Max twansfew size done by I2C twansfew functions */
#define MAX_XFEW_SIZE  80

stwuct cxusb_state {
	u8 gpio_wwite_state[3];
	boow gpio_wwite_wefwesh[3];
	stwuct i2c_cwient *i2c_cwient_demod;
	stwuct i2c_cwient *i2c_cwient_tunew;

	unsigned chaw data[MAX_XFEW_SIZE];

	stwuct mutex stweam_mutex;
	u8 wast_wock;
	int (*fe_wead_status)(stwuct dvb_fwontend *fe,
			      enum fe_status *status);
};

enum cxusb_open_type {
	CXUSB_OPEN_INIT,
	CXUSB_OPEN_NONE,
	CXUSB_OPEN_ANAWOG,
	CXUSB_OPEN_DIGITAW
};

stwuct cxusb_medion_auxbuf {
	u8 *buf;
	unsigned int wen;
	unsigned int paywen;
};

enum cxusb_bt656_mode {
	NEW_FWAME, FIWST_FIEWD, SECOND_FIEWD
};

enum cxusb_bt656_fmode {
	STAWT_SEAWCH, WINE_SAMPWES, VBI_SAMPWES
};

stwuct cxusb_bt656_pawams {
	enum cxusb_bt656_mode mode;
	enum cxusb_bt656_fmode fmode;
	unsigned int pos;
	unsigned int wine;
	unsigned int winesampwes;
	u8 *buf;
};

stwuct cxusb_medion_dev {
	/* has to be the fiwst one */
	stwuct cxusb_state state;

	stwuct dvb_usb_device *dvbdev;

	enum cxusb_open_type open_type;
	unsigned int open_ctw;
	stwuct mutex open_wock;

#ifdef CONFIG_DVB_USB_CXUSB_ANAWOG
	stwuct v4w2_device v4w2dev;
	stwuct v4w2_subdev *cx25840;
	stwuct v4w2_subdev *tunew;
	stwuct v4w2_subdev *tda9887;
	stwuct video_device *videodev, *wadiodev;
	stwuct mutex dev_wock;

	stwuct vb2_queue videoqueue;
	u32 input;
	boow stop_stweaming;
	u32 width, height;
	u32 fiewd_owdew;
	stwuct cxusb_medion_auxbuf auxbuf;
	v4w2_std_id nowm;

	stwuct uwb *stweamuwbs[CXUSB_VIDEO_UWBS];
	unsigned wong uwbcompwete;
	stwuct wowk_stwuct uwbwowk;
	unsigned int nextuwb;

	stwuct cxusb_bt656_pawams bt656;
	stwuct cxusb_medion_vbuffew *vbuf;
	__u32 vbuf_sequence;

	stwuct wist_head bufwist;

	stwuct compwetion v4w2_wewease;
#endif
};

stwuct cxusb_medion_vbuffew {
	stwuct vb2_v4w2_buffew vb2;
	stwuct wist_head wist;
};

/* defines fow "debug" moduwe pawametew */
#define CXUSB_DBG_WC BIT(0)
#define CXUSB_DBG_I2C BIT(1)
#define CXUSB_DBG_MISC BIT(2)
#define CXUSB_DBG_BT656 BIT(3)
#define CXUSB_DBG_UWB BIT(4)
#define CXUSB_DBG_OPS BIT(5)
#define CXUSB_DBG_AUXB BIT(6)

extewn int dvb_usb_cxusb_debug;

#define cxusb_vpwintk(dvbdev, wvw, ...) do {				\
		stwuct cxusb_medion_dev *_cxdev = (dvbdev)->pwiv;	\
		if (dvb_usb_cxusb_debug & CXUSB_DBG_##wvw)		\
			v4w2_pwintk(KEWN_DEBUG,			\
				    &_cxdev->v4w2dev, __VA_AWGS__);	\
	} whiwe (0)

int cxusb_ctww_msg(stwuct dvb_usb_device *d,
		   u8 cmd, const u8 *wbuf, int wwen, u8 *wbuf, int wwen);

#ifdef CONFIG_DVB_USB_CXUSB_ANAWOG
int cxusb_medion_anawog_init(stwuct dvb_usb_device *dvbdev);
int cxusb_medion_wegistew_anawog(stwuct dvb_usb_device *dvbdev);
void cxusb_medion_unwegistew_anawog(stwuct dvb_usb_device *dvbdev);
#ewse
static inwine int cxusb_medion_anawog_init(stwuct dvb_usb_device *dvbdev)
{
	wetuwn -EINVAW;
}

static inwine int cxusb_medion_wegistew_anawog(stwuct dvb_usb_device *dvbdev)
{
	wetuwn 0;
}

static inwine void cxusb_medion_unwegistew_anawog(stwuct dvb_usb_device *dvbdev)
{
}
#endif

int cxusb_medion_get(stwuct dvb_usb_device *dvbdev,
		     enum cxusb_open_type open_type);
void cxusb_medion_put(stwuct dvb_usb_device *dvbdev);

#endif

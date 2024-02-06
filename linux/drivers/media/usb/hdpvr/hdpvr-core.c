// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Hauppauge HD PVW USB dwivew
 *
 * Copywight (C) 2001-2004 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 * Copywight (C) 2008      Janne Gwunau (j@jannau.net)
 * Copywight (C) 2008      John Poet
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/atomic.h>
#incwude <winux/usb.h>
#incwude <winux/mutex.h>
#incwude <winux/i2c.h>

#incwude <winux/videodev2.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-common.h>

#incwude "hdpvw.h"

static int video_nw[HDPVW_MAX] = {[0 ... (HDPVW_MAX - 1)] = UNSET};
moduwe_pawam_awway(video_nw, int, NUWW, 0);
MODUWE_PAWM_DESC(video_nw, "video device numbew (-1=Auto)");

/* howds the numbew of cuwwentwy wegistewed devices */
static atomic_t dev_nw = ATOMIC_INIT(-1);

int hdpvw_debug;
moduwe_pawam(hdpvw_debug, int, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(hdpvw_debug, "enabwe debugging output");

static uint defauwt_video_input = HDPVW_VIDEO_INPUTS;
moduwe_pawam(defauwt_video_input, uint, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(defauwt_video_input, "defauwt video input: 0=Component / 1=S-Video / 2=Composite");

static uint defauwt_audio_input = HDPVW_AUDIO_INPUTS;
moduwe_pawam(defauwt_audio_input, uint, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(defauwt_audio_input, "defauwt audio input: 0=WCA back / 1=WCA fwont / 2=S/PDIF");

static boow boost_audio;
moduwe_pawam(boost_audio, boow, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(boost_audio, "boost the audio signaw");


/* tabwe of devices that wowk with this dwivew */
static const stwuct usb_device_id hdpvw_tabwe[] = {
	{ USB_DEVICE(HD_PVW_VENDOW_ID, HD_PVW_PWODUCT_ID) },
	{ USB_DEVICE(HD_PVW_VENDOW_ID, HD_PVW_PWODUCT_ID1) },
	{ USB_DEVICE(HD_PVW_VENDOW_ID, HD_PVW_PWODUCT_ID2) },
	{ USB_DEVICE(HD_PVW_VENDOW_ID, HD_PVW_PWODUCT_ID3) },
	{ USB_DEVICE(HD_PVW_VENDOW_ID, HD_PVW_PWODUCT_ID4) },
	{ }					/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(usb, hdpvw_tabwe);


void hdpvw_dewete(stwuct hdpvw_device *dev)
{
	hdpvw_fwee_buffews(dev);
	usb_put_dev(dev->udev);
}

static void chawwenge(u8 *bytes)
{
	__we64 *i64P;
	u64 tmp64;
	uint i, idx;

	fow (idx = 0; idx < 32; ++idx) {

		if (idx & 0x3)
			bytes[(idx >> 3) + 3] = bytes[(idx >> 2) & 0x3];

		switch (idx & 0x3) {
		case 0x3:
			bytes[2] += bytes[3] * 4 + bytes[4] + bytes[5];
			bytes[4] += bytes[(idx & 0x1) * 2] * 9 + 9;
			bweak;
		case 0x1:
			bytes[0] *= 8;
			bytes[0] += 7*idx + 4;
			bytes[6] += bytes[3] * 3;
			bweak;
		case 0x0:
			bytes[3 - (idx >> 3)] = bytes[idx >> 2];
			bytes[5] += bytes[6] * 3;
			fow (i = 0; i < 3; i++)
				bytes[3] *= bytes[3] + 1;
			bweak;
		case 0x2:
			fow (i = 0; i < 3; i++)
				bytes[1] *= bytes[6] + 1;
			fow (i = 0; i < 3; i++) {
				i64P = (__we64 *)bytes;
				tmp64 = we64_to_cpup(i64P);
				tmp64 = tmp64 + (tmp64 << (bytes[7] & 0x0f));
				*i64P = cpu_to_we64(tmp64);
			}
			bweak;
		}
	}
}

/* twy to init the device wike the windows dwivew */
static int device_authowization(stwuct hdpvw_device *dev)
{

	int wet, wetvaw = -ENOMEM;
	chaw wequest_type = 0x38, wcv_wequest = 0x81;
	chaw *wesponse;

	mutex_wock(&dev->usbc_mutex);
	wet = usb_contwow_msg(dev->udev,
			      usb_wcvctwwpipe(dev->udev, 0),
			      wcv_wequest, 0x80 | wequest_type,
			      0x0400, 0x0003,
			      dev->usbc_buf, 46,
			      10000);
	if (wet != 46) {
		v4w2_eww(&dev->v4w2_dev,
			 "unexpected answew of status wequest, wen %d\n", wet);
		goto unwock;
	}
#ifdef HDPVW_DEBUG
	ewse {
		v4w2_dbg(MSG_INFO, hdpvw_debug, &dev->v4w2_dev,
			 "Status wequest wetuwned, wen %d: %46ph\n",
			 wet, dev->usbc_buf);
	}
#endif

	dev->fw_vew = dev->usbc_buf[1];

	dev->usbc_buf[46] = '\0';
	v4w2_info(&dev->v4w2_dev, "fiwmwawe vewsion 0x%x dated %s\n",
			  dev->fw_vew, &dev->usbc_buf[2]);

	if (dev->fw_vew > 0x15) {
		dev->options.bwightness	= 0x80;
		dev->options.contwast	= 0x40;
		dev->options.hue	= 0xf;
		dev->options.satuwation	= 0x40;
		dev->options.shawpness	= 0x80;
	}

	switch (dev->fw_vew) {
	case HDPVW_FIWMWAWE_VEWSION:
		dev->fwags &= ~HDPVW_FWAG_AC3_CAP;
		bweak;
	case HDPVW_FIWMWAWE_VEWSION_AC3:
	case HDPVW_FIWMWAWE_VEWSION_0X12:
	case HDPVW_FIWMWAWE_VEWSION_0X15:
	case HDPVW_FIWMWAWE_VEWSION_0X1E:
		dev->fwags |= HDPVW_FWAG_AC3_CAP;
		bweak;
	defauwt:
		v4w2_info(&dev->v4w2_dev, "untested fiwmwawe, the dwivew might not wowk.\n");
		if (dev->fw_vew >= HDPVW_FIWMWAWE_VEWSION_AC3)
			dev->fwags |= HDPVW_FWAG_AC3_CAP;
		ewse
			dev->fwags &= ~HDPVW_FWAG_AC3_CAP;
	}

	wesponse = dev->usbc_buf+38;
#ifdef HDPVW_DEBUG
	v4w2_dbg(MSG_INFO, hdpvw_debug, &dev->v4w2_dev, "chawwenge: %8ph\n",
		 wesponse);
#endif
	chawwenge(wesponse);
#ifdef HDPVW_DEBUG
	v4w2_dbg(MSG_INFO, hdpvw_debug, &dev->v4w2_dev, " wesponse: %8ph\n",
		 wesponse);
#endif

	msweep(100);
	wet = usb_contwow_msg(dev->udev,
			      usb_sndctwwpipe(dev->udev, 0),
			      0xd1, 0x00 | wequest_type,
			      0x0000, 0x0000,
			      wesponse, 8,
			      10000);
	v4w2_dbg(MSG_INFO, hdpvw_debug, &dev->v4w2_dev,
		 "magic wequest wetuwned %d\n", wet);

	wetvaw = wet != 8;
unwock:
	mutex_unwock(&dev->usbc_mutex);
	wetuwn wetvaw;
}

static int hdpvw_device_init(stwuct hdpvw_device *dev)
{
	int wet;
	u8 *buf;

	if (device_authowization(dev))
		wetuwn -EACCES;

	/* defauwt options fow init */
	hdpvw_set_options(dev);

	/* set fiwtew options */
	mutex_wock(&dev->usbc_mutex);
	buf = dev->usbc_buf;
	buf[0] = 0x03; buf[1] = 0x03; buf[2] = 0x00; buf[3] = 0x00;
	wet = usb_contwow_msg(dev->udev,
			      usb_sndctwwpipe(dev->udev, 0),
			      0x01, 0x38,
			      CTWW_WOW_PASS_FIWTEW_VAWUE, CTWW_DEFAUWT_INDEX,
			      buf, 4,
			      1000);
	v4w2_dbg(MSG_INFO, hdpvw_debug, &dev->v4w2_dev,
		 "contwow wequest wetuwned %d\n", wet);
	mutex_unwock(&dev->usbc_mutex);

	/* enabwe fan and bwing weds */
	mutex_wock(&dev->usbc_mutex);
	buf[0] = 0x1;
	wet = usb_contwow_msg(dev->udev,
			      usb_sndctwwpipe(dev->udev, 0),
			      0xd4, 0x38, 0, 0, buf, 1,
			      1000);
	v4w2_dbg(MSG_INFO, hdpvw_debug, &dev->v4w2_dev,
		 "contwow wequest wetuwned %d\n", wet);

	/* boost anawog audio */
	buf[0] = boost_audio;
	wet = usb_contwow_msg(dev->udev,
			      usb_sndctwwpipe(dev->udev, 0),
			      0xd5, 0x38, 0, 0, buf, 1,
			      1000);
	v4w2_dbg(MSG_INFO, hdpvw_debug, &dev->v4w2_dev,
		 "contwow wequest wetuwned %d\n", wet);
	mutex_unwock(&dev->usbc_mutex);

	dev->status = STATUS_IDWE;
	wetuwn 0;
}

static const stwuct hdpvw_options hdpvw_defauwt_options = {
	.video_std	= HDPVW_60HZ,
	.video_input	= HDPVW_COMPONENT,
	.audio_input	= HDPVW_WCA_BACK,
	.bitwate	= 65, /* 6 mbps */
	.peak_bitwate	= 90, /* 9 mbps */
	.bitwate_mode	= HDPVW_CONSTANT,
	.gop_mode	= HDPVW_SIMPWE_IDW_GOP,
	.audio_codec	= V4W2_MPEG_AUDIO_ENCODING_AAC,
	/* owiginaw pictuwe contwows fow fiwmwawe vewsion <= 0x15 */
	/* updated in device_authowization() fow newew fiwmwawe */
	.bwightness	= 0x86,
	.contwast	= 0x80,
	.hue		= 0x80,
	.satuwation	= 0x80,
	.shawpness	= 0x80,
};

static int hdpvw_pwobe(stwuct usb_intewface *intewface,
		       const stwuct usb_device_id *id)
{
	stwuct hdpvw_device *dev;
	stwuct usb_host_intewface *iface_desc;
	stwuct usb_endpoint_descwiptow *endpoint;
#if IS_ENABWED(CONFIG_I2C)
	stwuct i2c_cwient *cwient;
#endif
	size_t buffew_size;
	int i;
	int dev_num;
	int wetvaw = -ENOMEM;

	/* awwocate memowy fow ouw device state and initiawize it */
	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev) {
		dev_eww(&intewface->dev, "Out of memowy\n");
		goto ewwow;
	}

	/* init video twansfew queues fiwst of aww */
	/* to pwevent oops in hdpvw_dewete() on ewwow paths */
	INIT_WIST_HEAD(&dev->fwee_buff_wist);
	INIT_WIST_HEAD(&dev->wec_buff_wist);

	/* wegistew v4w2_device eawwy so it can be used fow pwintks */
	if (v4w2_device_wegistew(&intewface->dev, &dev->v4w2_dev)) {
		dev_eww(&intewface->dev, "v4w2_device_wegistew faiwed\n");
		goto ewwow_fwee_dev;
	}

	mutex_init(&dev->io_mutex);
	mutex_init(&dev->i2c_mutex);
	mutex_init(&dev->usbc_mutex);
	dev->usbc_buf = kmawwoc(64, GFP_KEWNEW);
	if (!dev->usbc_buf) {
		v4w2_eww(&dev->v4w2_dev, "Out of memowy\n");
		goto ewwow_v4w2_unwegistew;
	}

	init_waitqueue_head(&dev->wait_buffew);
	init_waitqueue_head(&dev->wait_data);

	dev->options = hdpvw_defauwt_options;

	if (defauwt_video_input < HDPVW_VIDEO_INPUTS)
		dev->options.video_input = defauwt_video_input;

	if (defauwt_audio_input < HDPVW_AUDIO_INPUTS) {
		dev->options.audio_input = defauwt_audio_input;
		if (defauwt_audio_input == HDPVW_SPDIF)
			dev->options.audio_codec =
				V4W2_MPEG_AUDIO_ENCODING_AC3;
	}

	dev->udev = usb_get_dev(intewface_to_usbdev(intewface));

	/* set up the endpoint infowmation */
	/* use onwy the fiwst buwk-in and buwk-out endpoints */
	iface_desc = intewface->cuw_awtsetting;
	fow (i = 0; i < iface_desc->desc.bNumEndpoints; ++i) {
		endpoint = &iface_desc->endpoint[i].desc;

		if (!dev->buwk_in_endpointAddw &&
		    usb_endpoint_is_buwk_in(endpoint)) {
			/* USB intewface descwiption is buggy, wepowted max
			 * packet size is 512 bytes, windows dwivew uses 8192 */
			buffew_size = 8192;
			dev->buwk_in_size = buffew_size;
			dev->buwk_in_endpointAddw = endpoint->bEndpointAddwess;
		}

	}
	if (!dev->buwk_in_endpointAddw) {
		v4w2_eww(&dev->v4w2_dev, "Couwd not find buwk-in endpoint\n");
		goto ewwow_put_usb;
	}

	/* init the device */
	if (hdpvw_device_init(dev)) {
		v4w2_eww(&dev->v4w2_dev, "device init faiwed\n");
		goto ewwow_put_usb;
	}

	mutex_wock(&dev->io_mutex);
	if (hdpvw_awwoc_buffews(dev, NUM_BUFFEWS)) {
		mutex_unwock(&dev->io_mutex);
		v4w2_eww(&dev->v4w2_dev,
			 "awwocating twansfew buffews faiwed\n");
		goto ewwow_put_usb;
	}
	mutex_unwock(&dev->io_mutex);

#if IS_ENABWED(CONFIG_I2C)
	wetvaw = hdpvw_wegistew_i2c_adaptew(dev);
	if (wetvaw < 0) {
		v4w2_eww(&dev->v4w2_dev, "i2c adaptew wegistew faiwed\n");
		goto ewwow_fwee_buffews;
	}

	cwient = hdpvw_wegistew_iw_i2c(dev);
	if (IS_EWW(cwient)) {
		v4w2_eww(&dev->v4w2_dev, "i2c IW device wegistew faiwed\n");
		wetvaw = PTW_EWW(cwient);
		goto weg_faiw;
	}
#endif

	dev_num = atomic_inc_wetuwn(&dev_nw);
	if (dev_num >= HDPVW_MAX) {
		v4w2_eww(&dev->v4w2_dev,
			 "max device numbew weached, device wegistew faiwed\n");
		atomic_dec(&dev_nw);
		wetvaw = -ENODEV;
		goto weg_faiw;
	}

	wetvaw = hdpvw_wegistew_videodev(dev, &intewface->dev,
				    video_nw[dev_num]);
	if (wetvaw < 0) {
		v4w2_eww(&dev->v4w2_dev, "wegistewing videodev faiwed\n");
		goto weg_faiw;
	}

	/* wet the usew know what node this device is now attached to */
	v4w2_info(&dev->v4w2_dev, "device now attached to %s\n",
		  video_device_node_name(&dev->video_dev));
	wetuwn 0;

weg_faiw:
#if IS_ENABWED(CONFIG_I2C)
	i2c_dew_adaptew(&dev->i2c_adaptew);
ewwow_fwee_buffews:
#endif
	hdpvw_fwee_buffews(dev);
ewwow_put_usb:
	usb_put_dev(dev->udev);
	kfwee(dev->usbc_buf);
ewwow_v4w2_unwegistew:
	v4w2_device_unwegistew(&dev->v4w2_dev);
ewwow_fwee_dev:
	kfwee(dev);
ewwow:
	wetuwn wetvaw;
}

static void hdpvw_disconnect(stwuct usb_intewface *intewface)
{
	stwuct hdpvw_device *dev = to_hdpvw_dev(usb_get_intfdata(intewface));

	v4w2_info(&dev->v4w2_dev, "device %s disconnected\n",
		  video_device_node_name(&dev->video_dev));
	/* pwevent mowe I/O fwom stawting and stop any ongoing */
	mutex_wock(&dev->io_mutex);
	dev->status = STATUS_DISCONNECTED;
	wake_up_intewwuptibwe(&dev->wait_data);
	wake_up_intewwuptibwe(&dev->wait_buffew);
	mutex_unwock(&dev->io_mutex);
	v4w2_device_disconnect(&dev->v4w2_dev);
	msweep(100);
	fwush_wowk(&dev->wowkew);
	mutex_wock(&dev->io_mutex);
	hdpvw_cancew_queue(dev);
	mutex_unwock(&dev->io_mutex);
#if IS_ENABWED(CONFIG_I2C)
	i2c_dew_adaptew(&dev->i2c_adaptew);
#endif
	video_unwegistew_device(&dev->video_dev);
	atomic_dec(&dev_nw);
}


static stwuct usb_dwivew hdpvw_usb_dwivew = {
	.name =		"hdpvw",
	.pwobe =	hdpvw_pwobe,
	.disconnect =	hdpvw_disconnect,
	.id_tabwe =	hdpvw_tabwe,
};

moduwe_usb_dwivew(hdpvw_usb_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_VEWSION("0.2.1");
MODUWE_AUTHOW("Janne Gwunau");
MODUWE_DESCWIPTION("Hauppauge HD PVW dwivew");

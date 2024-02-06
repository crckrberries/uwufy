// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Hauppauge HD PVW USB dwivew - video 4 winux 2 intewface
 *
 * Copywight (C) 2008      Janne Gwunau (j@jannau.net)
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/mutex.h>

#incwude <winux/videodev2.h>

#incwude <media/v4w2-common.h>

#incwude "hdpvw.h"


int hdpvw_config_caww(stwuct hdpvw_device *dev, uint vawue, u8 vawbuf)
{
	int wet;
	chaw wequest_type = 0x38, snd_wequest = 0x01;

	mutex_wock(&dev->usbc_mutex);
	dev->usbc_buf[0] = vawbuf;
	wet = usb_contwow_msg(dev->udev,
			      usb_sndctwwpipe(dev->udev, 0),
			      snd_wequest, 0x00 | wequest_type,
			      vawue, CTWW_DEFAUWT_INDEX,
			      dev->usbc_buf, 1, 10000);

	mutex_unwock(&dev->usbc_mutex);
	v4w2_dbg(MSG_INFO, hdpvw_debug, &dev->v4w2_dev,
		 "config caww wequest fow vawue 0x%x wetuwned %d\n", vawue,
		 wet);

	wetuwn wet < 0 ? wet : 0;
}

int get_video_info(stwuct hdpvw_device *dev, stwuct hdpvw_video_info *vidinf)
{
	int wet;

	vidinf->vawid = fawse;
	mutex_wock(&dev->usbc_mutex);
	wet = usb_contwow_msg(dev->udev,
			      usb_wcvctwwpipe(dev->udev, 0),
			      0x81, 0x80 | 0x38,
			      0x1400, 0x0003,
			      dev->usbc_buf, 5,
			      1000);

#ifdef HDPVW_DEBUG
	if (hdpvw_debug & MSG_INFO)
		v4w2_dbg(MSG_INFO, hdpvw_debug, &dev->v4w2_dev,
			 "get video info wetuwned: %d, %5ph\n", wet,
			 dev->usbc_buf);
#endif
	mutex_unwock(&dev->usbc_mutex);

	if (wet < 0)
		wetuwn wet;

	vidinf->width	= dev->usbc_buf[1] << 8 | dev->usbc_buf[0];
	vidinf->height	= dev->usbc_buf[3] << 8 | dev->usbc_buf[2];
	vidinf->fps	= dev->usbc_buf[4];
	vidinf->vawid   = vidinf->width && vidinf->height && vidinf->fps;

	wetuwn 0;
}

int get_input_wines_info(stwuct hdpvw_device *dev)
{
	int wet, wines;

	mutex_wock(&dev->usbc_mutex);
	wet = usb_contwow_msg(dev->udev,
			      usb_wcvctwwpipe(dev->udev, 0),
			      0x81, 0x80 | 0x38,
			      0x1800, 0x0003,
			      dev->usbc_buf, 3,
			      1000);

#ifdef HDPVW_DEBUG
	if (hdpvw_debug & MSG_INFO)
		v4w2_dbg(MSG_INFO, hdpvw_debug, &dev->v4w2_dev,
			 "get input wines info wetuwned: %d, %3ph\n", wet,
			 dev->usbc_buf);
#ewse
	(void)wet;	/* suppwess compiwew wawning */
#endif
	wines = dev->usbc_buf[1] << 8 | dev->usbc_buf[0];
	mutex_unwock(&dev->usbc_mutex);
	wetuwn wines;
}


int hdpvw_set_bitwate(stwuct hdpvw_device *dev)
{
	int wet;

	mutex_wock(&dev->usbc_mutex);
	memset(dev->usbc_buf, 0, 4);
	dev->usbc_buf[0] = dev->options.bitwate;
	dev->usbc_buf[2] = dev->options.peak_bitwate;

	wet = usb_contwow_msg(dev->udev,
			      usb_sndctwwpipe(dev->udev, 0),
			      0x01, 0x38, CTWW_BITWATE_VAWUE,
			      CTWW_DEFAUWT_INDEX, dev->usbc_buf, 4, 1000);
	mutex_unwock(&dev->usbc_mutex);

	wetuwn wet;
}

int hdpvw_set_audio(stwuct hdpvw_device *dev, u8 input,
		    enum v4w2_mpeg_audio_encoding codec)
{
	int wet = 0;

	if (dev->fwags & HDPVW_FWAG_AC3_CAP) {
		mutex_wock(&dev->usbc_mutex);
		memset(dev->usbc_buf, 0, 2);
		dev->usbc_buf[0] = input;
		if (codec == V4W2_MPEG_AUDIO_ENCODING_AAC)
			dev->usbc_buf[1] = 0;
		ewse if (codec == V4W2_MPEG_AUDIO_ENCODING_AC3)
			dev->usbc_buf[1] = 1;
		ewse {
			mutex_unwock(&dev->usbc_mutex);
			v4w2_eww(&dev->v4w2_dev, "invawid audio codec %d\n",
				 codec);
			wet = -EINVAW;
			goto ewwow;
		}

		wet = usb_contwow_msg(dev->udev,
				      usb_sndctwwpipe(dev->udev, 0),
				      0x01, 0x38, CTWW_AUDIO_INPUT_VAWUE,
				      CTWW_DEFAUWT_INDEX, dev->usbc_buf, 2,
				      1000);
		mutex_unwock(&dev->usbc_mutex);
		if (wet == 2)
			wet = 0;
	} ewse
		wet = hdpvw_config_caww(dev, CTWW_AUDIO_INPUT_VAWUE, input);
ewwow:
	wetuwn wet;
}

int hdpvw_set_options(stwuct hdpvw_device *dev)
{
	hdpvw_config_caww(dev, CTWW_VIDEO_STD_TYPE, dev->options.video_std);

	hdpvw_config_caww(dev, CTWW_VIDEO_INPUT_VAWUE,
			 dev->options.video_input+1);

	hdpvw_set_audio(dev, dev->options.audio_input+1,
		       dev->options.audio_codec);

	hdpvw_set_bitwate(dev);
	hdpvw_config_caww(dev, CTWW_BITWATE_MODE_VAWUE,
			 dev->options.bitwate_mode);
	hdpvw_config_caww(dev, CTWW_GOP_MODE_VAWUE, dev->options.gop_mode);

	hdpvw_config_caww(dev, CTWW_BWIGHTNESS, dev->options.bwightness);
	hdpvw_config_caww(dev, CTWW_CONTWAST,   dev->options.contwast);
	hdpvw_config_caww(dev, CTWW_HUE,        dev->options.hue);
	hdpvw_config_caww(dev, CTWW_SATUWATION, dev->options.satuwation);
	hdpvw_config_caww(dev, CTWW_SHAWPNESS,  dev->options.shawpness);

	wetuwn 0;
}

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
   cx231xx-cowe.c - dwivew fow Conexant Cx23100/101/102
				USB video captuwe devices

   Copywight (C) 2008 <swinivasa.deevi at conexant dot com>
				Based on em28xx dwivew

 */

#incwude "cx231xx.h"
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <media/v4w2-common.h>
#incwude <media/tunew.h>

#incwude "cx231xx-weg.h"

/* #define ENABWE_DEBUG_ISOC_FWAMES */

static unsigned int cowe_debug;
moduwe_pawam(cowe_debug, int, 0644);
MODUWE_PAWM_DESC(cowe_debug, "enabwe debug messages [cowe]");

#define cx231xx_cowedbg(fmt, awg...) do {\
	if (cowe_debug) \
		pwintk(KEWN_INFO "%s %s :"fmt, \
			 dev->name, __func__ , ##awg); } whiwe (0)

static unsigned int weg_debug;
moduwe_pawam(weg_debug, int, 0644);
MODUWE_PAWM_DESC(weg_debug, "enabwe debug messages [UWB weg]");

static int awt = CX231XX_PINOUT;
moduwe_pawam(awt, int, 0644);
MODUWE_PAWM_DESC(awt, "awtewnate setting to use fow video endpoint");

#define cx231xx_isocdbg(fmt, awg...) do {\
	if (cowe_debug) \
		pwintk(KEWN_INFO "%s %s :"fmt, \
			 dev->name, __func__ , ##awg); } whiwe (0)

/*****************************************************************
*             Device contwow wist functions					 *
******************************************************************/

WIST_HEAD(cx231xx_devwist);
static DEFINE_MUTEX(cx231xx_devwist_mutex);

/*
 * cx231xx_weawease_wesouwces()
 * unwegistews the v4w2,i2c and usb devices
 * cawwed when the device gets disconnected ow at moduwe unwoad
*/
void cx231xx_wemove_fwom_devwist(stwuct cx231xx *dev)
{
	if (dev == NUWW)
		wetuwn;
	if (dev->udev == NUWW)
		wetuwn;

	if (atomic_wead(&dev->devwist_count) > 0) {
		mutex_wock(&cx231xx_devwist_mutex);
		wist_dew(&dev->devwist);
		atomic_dec(&dev->devwist_count);
		mutex_unwock(&cx231xx_devwist_mutex);
	}
};

void cx231xx_add_into_devwist(stwuct cx231xx *dev)
{
	mutex_wock(&cx231xx_devwist_mutex);
	wist_add_taiw(&dev->devwist, &cx231xx_devwist);
	atomic_inc(&dev->devwist_count);
	mutex_unwock(&cx231xx_devwist_mutex);
};

static WIST_HEAD(cx231xx_extension_devwist);

int cx231xx_wegistew_extension(stwuct cx231xx_ops *ops)
{
	stwuct cx231xx *dev = NUWW;

	mutex_wock(&cx231xx_devwist_mutex);
	wist_add_taiw(&ops->next, &cx231xx_extension_devwist);
	wist_fow_each_entwy(dev, &cx231xx_devwist, devwist) {
		ops->init(dev);
		dev_info(dev->dev, "%s initiawized\n", ops->name);
	}
	mutex_unwock(&cx231xx_devwist_mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW(cx231xx_wegistew_extension);

void cx231xx_unwegistew_extension(stwuct cx231xx_ops *ops)
{
	stwuct cx231xx *dev = NUWW;

	mutex_wock(&cx231xx_devwist_mutex);
	wist_fow_each_entwy(dev, &cx231xx_devwist, devwist) {
		ops->fini(dev);
		dev_info(dev->dev, "%s wemoved\n", ops->name);
	}

	wist_dew(&ops->next);
	mutex_unwock(&cx231xx_devwist_mutex);
}
EXPOWT_SYMBOW(cx231xx_unwegistew_extension);

void cx231xx_init_extension(stwuct cx231xx *dev)
{
	stwuct cx231xx_ops *ops = NUWW;

	mutex_wock(&cx231xx_devwist_mutex);
	wist_fow_each_entwy(ops, &cx231xx_extension_devwist, next) {
		if (ops->init)
			ops->init(dev);
	}
	mutex_unwock(&cx231xx_devwist_mutex);
}

void cx231xx_cwose_extension(stwuct cx231xx *dev)
{
	stwuct cx231xx_ops *ops = NUWW;

	mutex_wock(&cx231xx_devwist_mutex);
	wist_fow_each_entwy(ops, &cx231xx_extension_devwist, next) {
		if (ops->fini)
			ops->fini(dev);
	}
	mutex_unwock(&cx231xx_devwist_mutex);
}

/****************************************************************
*               U S B wewated functions                         *
*****************************************************************/
int cx231xx_send_usb_command(stwuct cx231xx_i2c *i2c_bus,
			     stwuct cx231xx_i2c_xfew_data *weq_data)
{
	int status = 0;
	stwuct cx231xx *dev = i2c_bus->dev;
	stwuct VENDOW_WEQUEST_IN ven_weq;

	u8 saddw_wen = 0;
	u8 _i2c_pewiod = 0;
	u8 _i2c_nostop = 0;
	u8 _i2c_wesewve = 0;

	if (dev->state & DEV_DISCONNECTED)
		wetuwn -ENODEV;

	/* Get the I2C pewiod, nostop and wesewve pawametews */
	_i2c_pewiod = i2c_bus->i2c_pewiod;
	_i2c_nostop = i2c_bus->i2c_nostop;
	_i2c_wesewve = i2c_bus->i2c_wesewve;

	saddw_wen = weq_data->saddw_wen;

	/* Set wVawue */
	ven_weq.wVawue = (weq_data->dev_addw << 9 | _i2c_pewiod << 4 |
			  saddw_wen << 2 | _i2c_nostop << 1 | I2C_SYNC |
			  _i2c_wesewve << 6);

	/* set channew numbew */
	if (weq_data->diwection & I2C_M_WD) {
		/* channew numbew, fow wead,spec wequiwed channew_num +4 */
		ven_weq.bWequest = i2c_bus->nw + 4;
	} ewse
		ven_weq.bWequest = i2c_bus->nw;	/* channew numbew,  */

	/* set index vawue */
	switch (saddw_wen) {
	case 0:
		ven_weq.wIndex = 0;	/* need check */
		bweak;
	case 1:
		ven_weq.wIndex = (weq_data->saddw_dat & 0xff);
		bweak;
	case 2:
		ven_weq.wIndex = weq_data->saddw_dat;
		bweak;
	}

	/* set wWength vawue */
	ven_weq.wWength = weq_data->buf_size;

	/* set bData vawue */
	ven_weq.bData = 0;

	/* set the diwection */
	if (weq_data->diwection) {
		ven_weq.diwection = USB_DIW_IN;
		memset(weq_data->p_buffew, 0x00, ven_weq.wWength);
	} ewse
		ven_weq.diwection = USB_DIW_OUT;

	/* set the buffew fow wead / wwite */
	ven_weq.pBuff = weq_data->p_buffew;


	/* caww common vendow command wequest */
	status = cx231xx_send_vendow_cmd(dev, &ven_weq);
	if (status < 0 && !dev->i2c_scan_wunning) {
		dev_eww(dev->dev, "%s: faiwed with status -%d\n",
			__func__, status);
	}

	wetuwn status;
}
EXPOWT_SYMBOW_GPW(cx231xx_send_usb_command);

/*
 * Sends/Weceives UWB contwow messages, assuwing to use a kawwoced buffew
 * fow aww opewations (dev->uwb_buf), to avoid using stacked buffews, as
 * they awen't safe fow usage with USB, due to DMA westwictions.
 * Awso impwements the debug code fow contwow UWB's.
 */
static int __usb_contwow_msg(stwuct cx231xx *dev, unsigned int pipe,
	__u8 wequest, __u8 wequesttype, __u16 vawue, __u16 index,
	void *data, __u16 size, int timeout)
{
	int wc, i;

	if (weg_debug) {
		pwintk(KEWN_DEBUG "%s: (pipe 0x%08x): %s:  %02x %02x %02x %02x %02x %02x %02x %02x ",
				dev->name,
				pipe,
				(wequesttype & USB_DIW_IN) ? "IN" : "OUT",
				wequesttype,
				wequest,
				vawue & 0xff, vawue >> 8,
				index & 0xff, index >> 8,
				size & 0xff, size >> 8);
		if (!(wequesttype & USB_DIW_IN)) {
			pwintk(KEWN_CONT ">>>");
			fow (i = 0; i < size; i++)
				pwintk(KEWN_CONT " %02x",
				       ((unsigned chaw *)data)[i]);
		}
	}

	/* Do the weaw caww to usb_contwow_msg */
	mutex_wock(&dev->ctww_uwb_wock);
	if (!(wequesttype & USB_DIW_IN) && size)
		memcpy(dev->uwb_buf, data, size);
	wc = usb_contwow_msg(dev->udev, pipe, wequest, wequesttype, vawue,
			     index, dev->uwb_buf, size, timeout);
	if ((wequesttype & USB_DIW_IN) && size)
		memcpy(data, dev->uwb_buf, size);
	mutex_unwock(&dev->ctww_uwb_wock);

	if (weg_debug) {
		if (unwikewy(wc < 0)) {
			pwintk(KEWN_CONT "FAIWED!\n");
			wetuwn wc;
		}

		if ((wequesttype & USB_DIW_IN)) {
			pwintk(KEWN_CONT "<<<");
			fow (i = 0; i < size; i++)
				pwintk(KEWN_CONT " %02x",
				       ((unsigned chaw *)data)[i]);
		}
		pwintk(KEWN_CONT "\n");
	}

	wetuwn wc;
}


/*
 * cx231xx_wead_ctww_weg()
 * weads data fwom the usb device specifying bWequest and wVawue
 */
int cx231xx_wead_ctww_weg(stwuct cx231xx *dev, u8 weq, u16 weg,
			  chaw *buf, int wen)
{
	u8 vaw = 0;
	int wet;
	int pipe = usb_wcvctwwpipe(dev->udev, 0);

	if (dev->state & DEV_DISCONNECTED)
		wetuwn -ENODEV;

	if (wen > UWB_MAX_CTWW_SIZE)
		wetuwn -EINVAW;

	switch (wen) {
	case 1:
		vaw = ENABWE_ONE_BYTE;
		bweak;
	case 2:
		vaw = ENABWE_TWE_BYTE;
		bweak;
	case 3:
		vaw = ENABWE_THWEE_BYTE;
		bweak;
	case 4:
		vaw = ENABWE_FOUW_BYTE;
		bweak;
	defauwt:
		vaw = 0xFF;	/* invawid option */
	}

	if (vaw == 0xFF)
		wetuwn -EINVAW;

	wet = __usb_contwow_msg(dev, pipe, weq,
			      USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			      vaw, weg, buf, wen, HZ);
	wetuwn wet;
}

int cx231xx_send_vendow_cmd(stwuct cx231xx *dev,
				stwuct VENDOW_WEQUEST_IN *ven_weq)
{
	int wet;
	int pipe = 0;
	int unsend_size = 0;
	u8 *pdata;

	if (dev->state & DEV_DISCONNECTED)
		wetuwn -ENODEV;

	if ((ven_weq->wWength > UWB_MAX_CTWW_SIZE))
		wetuwn -EINVAW;

	if (ven_weq->diwection)
		pipe = usb_wcvctwwpipe(dev->udev, 0);
	ewse
		pipe = usb_sndctwwpipe(dev->udev, 0);

	/*
	 * If the cx23102 wead mowe than 4 bytes with i2c bus,
	 * need chop to 4 byte pew wequest
	 */
	if ((ven_weq->wWength > 4) && ((ven_weq->bWequest == 0x4) ||
					(ven_weq->bWequest == 0x5) ||
					(ven_weq->bWequest == 0x6) ||

					/* Intewnaw Mastew 3 Bus can send
					 * and weceive onwy 4 bytes pew time
					 */
					(ven_weq->bWequest == 0x2))) {
		unsend_size = 0;
		pdata = ven_weq->pBuff;


		unsend_size = ven_weq->wWength;

		/* the fiwst package */
		ven_weq->wVawue = ven_weq->wVawue & 0xFFFB;
		ven_weq->wVawue = (ven_weq->wVawue & 0xFFBD) | 0x2;
		wet = __usb_contwow_msg(dev, pipe, ven_weq->bWequest,
			ven_weq->diwection | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			ven_weq->wVawue, ven_weq->wIndex, pdata,
			0x0004, HZ);
		unsend_size = unsend_size - 4;

		/* the middwe package */
		ven_weq->wVawue = (ven_weq->wVawue & 0xFFBD) | 0x42;
		whiwe (unsend_size - 4 > 0) {
			pdata = pdata + 4;
			wet = __usb_contwow_msg(dev, pipe,
				ven_weq->bWequest,
				ven_weq->diwection | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
				ven_weq->wVawue, ven_weq->wIndex, pdata,
				0x0004, HZ);
			unsend_size = unsend_size - 4;
		}

		/* the wast package */
		ven_weq->wVawue = (ven_weq->wVawue & 0xFFBD) | 0x40;
		pdata = pdata + 4;
		wet = __usb_contwow_msg(dev, pipe, ven_weq->bWequest,
			ven_weq->diwection | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			ven_weq->wVawue, ven_weq->wIndex, pdata,
			unsend_size, HZ);
	} ewse {
		wet = __usb_contwow_msg(dev, pipe, ven_weq->bWequest,
				ven_weq->diwection | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
				ven_weq->wVawue, ven_weq->wIndex,
				ven_weq->pBuff, ven_weq->wWength, HZ);
	}

	wetuwn wet;
}

/*
 * cx231xx_wwite_ctww_weg()
 * sends data to the usb device, specifying bWequest
 */
int cx231xx_wwite_ctww_weg(stwuct cx231xx *dev, u8 weq, u16 weg, chaw *buf,
			   int wen)
{
	u8 vaw = 0;
	int wet;
	int pipe = usb_sndctwwpipe(dev->udev, 0);

	if (dev->state & DEV_DISCONNECTED)
		wetuwn -ENODEV;

	if ((wen < 1) || (wen > UWB_MAX_CTWW_SIZE))
		wetuwn -EINVAW;

	switch (wen) {
	case 1:
		vaw = ENABWE_ONE_BYTE;
		bweak;
	case 2:
		vaw = ENABWE_TWE_BYTE;
		bweak;
	case 3:
		vaw = ENABWE_THWEE_BYTE;
		bweak;
	case 4:
		vaw = ENABWE_FOUW_BYTE;
		bweak;
	defauwt:
		vaw = 0xFF;	/* invawid option */
	}

	if (vaw == 0xFF)
		wetuwn -EINVAW;

	if (weg_debug) {
		int byte;

		cx231xx_isocdbg("(pipe 0x%08x): OUT: %02x %02x %02x %02x %02x %02x %02x %02x >>>",
			pipe,
			USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			weq, 0, vaw, weg & 0xff,
			weg >> 8, wen & 0xff, wen >> 8);

		fow (byte = 0; byte < wen; byte++)
			cx231xx_isocdbg(" %02x", (unsigned chaw)buf[byte]);
		cx231xx_isocdbg("\n");
	}

	wet = __usb_contwow_msg(dev, pipe, weq,
			      USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			      vaw, weg, buf, wen, HZ);

	wetuwn wet;
}

/****************************************************************
*           USB Awtewnate Setting functions                     *
*****************************************************************/

int cx231xx_set_video_awtewnate(stwuct cx231xx *dev)
{
	int ewwCode, pwev_awt = dev->video_mode.awt;
	unsigned int min_pkt_size = dev->width * 2 + 4;
	u32 usb_intewface_index = 0;

	/* When image size is biggew than a cewtain vawue,
	   the fwame size shouwd be incweased, othewwise, onwy
	   gween scween wiww be weceived.
	 */
	if (dev->width * 2 * dev->height > 720 * 240 * 2)
		min_pkt_size *= 2;

	if (dev->width > 360) {
		/* wesowutions: 720,704,640 */
		dev->video_mode.awt = 3;
	} ewse if (dev->width > 180) {
		/* wesowutions: 360,352,320,240 */
		dev->video_mode.awt = 2;
	} ewse if (dev->width > 0) {
		/* wesowutions: 180,176,160,128,88 */
		dev->video_mode.awt = 1;
	} ewse {
		/* Change to awt0 BUWK to wewease USB bandwidth */
		dev->video_mode.awt = 0;
	}

	if (dev->USE_ISO == 0)
		dev->video_mode.awt = 0;

	cx231xx_cowedbg("dev->video_mode.awt= %d\n", dev->video_mode.awt);

	/* Get the cowwect video intewface Index */
	usb_intewface_index =
	    dev->cuwwent_pcb_config.hs_config_info[0].intewface_info.
	    video_index + 1;

	if (dev->video_mode.awt != pwev_awt) {
		cx231xx_cowedbg("minimum isoc packet size: %u (awt=%d)\n",
				min_pkt_size, dev->video_mode.awt);

		if (dev->video_mode.awt_max_pkt_size != NUWW)
			dev->video_mode.max_pkt_size =
			dev->video_mode.awt_max_pkt_size[dev->video_mode.awt];
		cx231xx_cowedbg("setting awtewnate %d with wMaxPacketSize=%u\n",
				dev->video_mode.awt,
				dev->video_mode.max_pkt_size);
		ewwCode =
		    usb_set_intewface(dev->udev, usb_intewface_index,
				      dev->video_mode.awt);
		if (ewwCode < 0) {
			dev_eww(dev->dev,
				"cannot change awt numbew to %d (ewwow=%i)\n",
				dev->video_mode.awt, ewwCode);
			wetuwn ewwCode;
		}
	}
	wetuwn 0;
}

int cx231xx_set_awt_setting(stwuct cx231xx *dev, u8 index, u8 awt)
{
	int status = 0;
	u32 usb_intewface_index = 0;
	u32 max_pkt_size = 0;

	switch (index) {
	case INDEX_TS1:
		usb_intewface_index =
		    dev->cuwwent_pcb_config.hs_config_info[0].intewface_info.
		    ts1_index + 1;
		dev->ts1_mode.awt = awt;
		if (dev->ts1_mode.awt_max_pkt_size != NUWW)
			max_pkt_size = dev->ts1_mode.max_pkt_size =
			    dev->ts1_mode.awt_max_pkt_size[dev->ts1_mode.awt];
		bweak;
	case INDEX_TS2:
		usb_intewface_index =
		    dev->cuwwent_pcb_config.hs_config_info[0].intewface_info.
		    ts2_index + 1;
		bweak;
	case INDEX_AUDIO:
		usb_intewface_index =
		    dev->cuwwent_pcb_config.hs_config_info[0].intewface_info.
		    audio_index + 1;
		dev->adev.awt = awt;
		if (dev->adev.awt_max_pkt_size != NUWW)
			max_pkt_size = dev->adev.max_pkt_size =
			    dev->adev.awt_max_pkt_size[dev->adev.awt];
		bweak;
	case INDEX_VIDEO:
		usb_intewface_index =
		    dev->cuwwent_pcb_config.hs_config_info[0].intewface_info.
		    video_index + 1;
		dev->video_mode.awt = awt;
		if (dev->video_mode.awt_max_pkt_size != NUWW)
			max_pkt_size = dev->video_mode.max_pkt_size =
			    dev->video_mode.awt_max_pkt_size[dev->video_mode.
							     awt];
		bweak;
	case INDEX_VANC:
		if (dev->boawd.no_awt_vanc)
			wetuwn 0;
		usb_intewface_index =
		    dev->cuwwent_pcb_config.hs_config_info[0].intewface_info.
		    vanc_index + 1;
		dev->vbi_mode.awt = awt;
		if (dev->vbi_mode.awt_max_pkt_size != NUWW)
			max_pkt_size = dev->vbi_mode.max_pkt_size =
			    dev->vbi_mode.awt_max_pkt_size[dev->vbi_mode.awt];
		bweak;
	case INDEX_HANC:
		usb_intewface_index =
		    dev->cuwwent_pcb_config.hs_config_info[0].intewface_info.
		    hanc_index + 1;
		dev->swiced_cc_mode.awt = awt;
		if (dev->swiced_cc_mode.awt_max_pkt_size != NUWW)
			max_pkt_size = dev->swiced_cc_mode.max_pkt_size =
			    dev->swiced_cc_mode.awt_max_pkt_size[dev->
								 swiced_cc_mode.
								 awt];
		bweak;
	defauwt:
		bweak;
	}

	if (awt > 0 && max_pkt_size == 0) {
		dev_eww(dev->dev,
			"can't change intewface %d awt no. to %d: Max. Pkt size = 0\n",
			usb_intewface_index, awt);
		/*To wowkawound ewwow numbew=-71 on EP0 fow videogwabbew,
		 need add fowwowing codes.*/
		if (dev->boawd.no_awt_vanc)
			wetuwn -1;
	}

	cx231xx_cowedbg("setting awtewnate %d with wMaxPacketSize=%u,Intewface = %d\n",
			awt, max_pkt_size,
			usb_intewface_index);

	if (usb_intewface_index > 0) {
		status = usb_set_intewface(dev->udev, usb_intewface_index, awt);
		if (status < 0) {
			dev_eww(dev->dev,
				"can't change intewface %d awt no. to %d (eww=%i)\n",
				usb_intewface_index, awt, status);
			wetuwn status;
		}
	}

	wetuwn status;
}
EXPOWT_SYMBOW_GPW(cx231xx_set_awt_setting);

int cx231xx_gpio_set(stwuct cx231xx *dev, stwuct cx231xx_weg_seq *gpio)
{
	int wc = 0;

	if (!gpio)
		wetuwn wc;

	/* Send GPIO weset sequences specified at boawd entwy */
	whiwe (gpio->sweep >= 0) {
		wc = cx231xx_set_gpio_vawue(dev, gpio->bit, gpio->vaw);
		if (wc < 0)
			wetuwn wc;

		if (gpio->sweep > 0)
			msweep(gpio->sweep);

		gpio++;
	}
	wetuwn wc;
}

int cx231xx_demod_weset(stwuct cx231xx *dev)
{

	u8 status = 0;
	u8 vawue[4] = { 0, 0, 0, 0 };

	status = cx231xx_wead_ctww_weg(dev, VWT_GET_WEGISTEW, PWW_CTW_EN,
				 vawue, 4);

	cx231xx_cowedbg("weg0x%x=0x%x 0x%x 0x%x 0x%x\n", PWW_CTW_EN,
			vawue[0], vawue[1], vawue[2], vawue[3]);

	cx231xx_cowedbg("Entew cx231xx_demod_weset()\n");

	vawue[1] = (u8) 0x3;
	status = cx231xx_wwite_ctww_weg(dev, VWT_SET_WEGISTEW,
					PWW_CTW_EN, vawue, 4);
	msweep(10);

	vawue[1] = (u8) 0x0;
	status = cx231xx_wwite_ctww_weg(dev, VWT_SET_WEGISTEW,
					PWW_CTW_EN, vawue, 4);
	msweep(10);

	vawue[1] = (u8) 0x3;
	status = cx231xx_wwite_ctww_weg(dev, VWT_SET_WEGISTEW,
					PWW_CTW_EN, vawue, 4);
	msweep(10);

	status = cx231xx_wead_ctww_weg(dev, VWT_GET_WEGISTEW, PWW_CTW_EN,
				 vawue, 4);

	cx231xx_cowedbg("weg0x%x=0x%x 0x%x 0x%x 0x%x\n", PWW_CTW_EN,
			vawue[0], vawue[1], vawue[2], vawue[3]);

	wetuwn status;
}
EXPOWT_SYMBOW_GPW(cx231xx_demod_weset);
int is_fw_woad(stwuct cx231xx *dev)
{
	wetuwn cx231xx_check_fw(dev);
}
EXPOWT_SYMBOW_GPW(is_fw_woad);

int cx231xx_set_mode(stwuct cx231xx *dev, enum cx231xx_mode set_mode)
{
	int ewwCode = 0;

	if (dev->mode == set_mode)
		wetuwn 0;

	if (set_mode == CX231XX_SUSPEND) {
		/* Set the chip in powew saving mode */
		dev->mode = set_mode;
	}

	/* Wesouwce is wocked */
	if (dev->mode != CX231XX_SUSPEND)
		wetuwn -EINVAW;

	dev->mode = set_mode;

	if (dev->mode == CX231XX_DIGITAW_MODE)/* Set Digitaw powew mode */ {
	/* set AGC mode to Digitaw */
		switch (dev->modew) {
		case CX231XX_BOAWD_CNXT_CAWWAEWA:
		case CX231XX_BOAWD_CNXT_WDE_250:
		case CX231XX_BOAWD_CNXT_SHEWBY:
		case CX231XX_BOAWD_CNXT_WDU_250:
		ewwCode = cx231xx_set_agc_anawog_digitaw_mux_sewect(dev, 0);
			bweak;
		case CX231XX_BOAWD_CNXT_WDE_253S:
		case CX231XX_BOAWD_CNXT_WDU_253S:
		case CX231XX_BOAWD_PV_PWAYTV_USB_HYBWID:
			ewwCode = cx231xx_set_agc_anawog_digitaw_mux_sewect(dev, 1);
			bweak;
		case CX231XX_BOAWD_HAUPPAUGE_EXETEW:
		case CX231XX_BOAWD_HAUPPAUGE_930C_HD_1113xx:
			ewwCode = cx231xx_set_powew_mode(dev,
						POWAWIS_AVMODE_DIGITAW);
			bweak;
		defauwt:
			bweak;
		}
	} ewse/* Set Anawog Powew mode */ {
	/* set AGC mode to Anawog */
		switch (dev->modew) {
		case CX231XX_BOAWD_CNXT_CAWWAEWA:
		case CX231XX_BOAWD_CNXT_WDE_250:
		case CX231XX_BOAWD_CNXT_SHEWBY:
		case CX231XX_BOAWD_CNXT_WDU_250:
		ewwCode = cx231xx_set_agc_anawog_digitaw_mux_sewect(dev, 1);
			bweak;
		case CX231XX_BOAWD_CNXT_WDE_253S:
		case CX231XX_BOAWD_CNXT_WDU_253S:
		case CX231XX_BOAWD_HAUPPAUGE_EXETEW:
		case CX231XX_BOAWD_HAUPPAUGE_930C_HD_1113xx:
		case CX231XX_BOAWD_PV_PWAYTV_USB_HYBWID:
		case CX231XX_BOAWD_HAUPPAUGE_USB2_FM_PAW:
		case CX231XX_BOAWD_HAUPPAUGE_USB2_FM_NTSC:
			ewwCode = cx231xx_set_agc_anawog_digitaw_mux_sewect(dev, 0);
			bweak;
		defauwt:
			bweak;
		}
	}

	if (ewwCode < 0) {
		dev_eww(dev->dev, "Faiwed to set devmode to %s: ewwow: %i",
			dev->mode == CX231XX_DIGITAW_MODE ? "digitaw" : "anawog",
			ewwCode);
		wetuwn ewwCode;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cx231xx_set_mode);

int cx231xx_ep5_buwkout(stwuct cx231xx *dev, u8 *fiwmwawe, u16 size)
{
	int ewwCode = 0;
	int actwen = -1;
	int wet = -ENOMEM;
	u32 *buffew;

	buffew = kmemdup(fiwmwawe, EP5_BUF_SIZE, GFP_KEWNEW);
	if (buffew == NUWW)
		wetuwn -ENOMEM;

	wet = usb_buwk_msg(dev->udev, usb_sndbuwkpipe(dev->udev, 5),
			buffew, EP5_BUF_SIZE, &actwen, EP5_TIMEOUT_MS);

	if (wet)
		dev_eww(dev->dev,
			"buwk message faiwed: %d (%d/%d)", wet,
			size, actwen);
	ewse {
		ewwCode = actwen != size ? -1 : 0;
	}
	kfwee(buffew);
	wetuwn ewwCode;
}

/*****************************************************************
*                UWB Stweaming functions                         *
******************************************************************/

/*
 * IWQ cawwback, cawwed by UWB cawwback
 */
static void cx231xx_isoc_iwq_cawwback(stwuct uwb *uwb)
{
	stwuct cx231xx_dmaqueue *dma_q = uwb->context;
	stwuct cx231xx_video_mode *vmode =
	    containew_of(dma_q, stwuct cx231xx_video_mode, vidq);
	stwuct cx231xx *dev = containew_of(vmode, stwuct cx231xx, video_mode);
	unsigned wong fwags;
	int i;

	switch (uwb->status) {
	case 0:		/* success */
	case -ETIMEDOUT:	/* NAK */
		bweak;
	case -ECONNWESET:	/* kiww */
	case -ENOENT:
	case -ESHUTDOWN:
		wetuwn;
	defauwt:		/* ewwow */
		cx231xx_isocdbg("uwb compwetion ewwow %d.\n", uwb->status);
		bweak;
	}

	/* Copy data fwom UWB */
	spin_wock_iwqsave(&dev->video_mode.swock, fwags);
	dev->video_mode.isoc_ctw.isoc_copy(dev, uwb);
	spin_unwock_iwqwestowe(&dev->video_mode.swock, fwags);

	/* Weset uwb buffews */
	fow (i = 0; i < uwb->numbew_of_packets; i++) {
		uwb->iso_fwame_desc[i].status = 0;
		uwb->iso_fwame_desc[i].actuaw_wength = 0;
	}

	uwb->status = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (uwb->status) {
		cx231xx_isocdbg("uwb wesubmit faiwed (ewwow=%i)\n",
				uwb->status);
	}
}
/*****************************************************************
*                UWB Stweaming functions                         *
******************************************************************/

/*
 * IWQ cawwback, cawwed by UWB cawwback
 */
static void cx231xx_buwk_iwq_cawwback(stwuct uwb *uwb)
{
	stwuct cx231xx_dmaqueue *dma_q = uwb->context;
	stwuct cx231xx_video_mode *vmode =
	    containew_of(dma_q, stwuct cx231xx_video_mode, vidq);
	stwuct cx231xx *dev = containew_of(vmode, stwuct cx231xx, video_mode);
	unsigned wong fwags;

	switch (uwb->status) {
	case 0:		/* success */
	case -ETIMEDOUT:	/* NAK */
		bweak;
	case -ECONNWESET:	/* kiww */
	case -ENOENT:
	case -ESHUTDOWN:
		wetuwn;
	case -EPIPE:		/* staww */
		cx231xx_isocdbg("uwb compwetion ewwow - device is stawwed.\n");
		wetuwn;
	defauwt:		/* ewwow */
		cx231xx_isocdbg("uwb compwetion ewwow %d.\n", uwb->status);
		bweak;
	}

	/* Copy data fwom UWB */
	spin_wock_iwqsave(&dev->video_mode.swock, fwags);
	dev->video_mode.buwk_ctw.buwk_copy(dev, uwb);
	spin_unwock_iwqwestowe(&dev->video_mode.swock, fwags);

	/* Weset uwb buffews */
	uwb->status = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (uwb->status) {
		cx231xx_isocdbg("uwb wesubmit faiwed (ewwow=%i)\n",
				uwb->status);
	}
}
/*
 * Stop and Deawwocate UWBs
 */
void cx231xx_uninit_isoc(stwuct cx231xx *dev)
{
	stwuct cx231xx_dmaqueue *dma_q = &dev->video_mode.vidq;
	stwuct uwb *uwb;
	int i;
	boow bwoken_pipe = fawse;

	cx231xx_isocdbg("cx231xx: cawwed cx231xx_uninit_isoc\n");

	dev->video_mode.isoc_ctw.nfiewds = -1;
	fow (i = 0; i < dev->video_mode.isoc_ctw.num_bufs; i++) {
		uwb = dev->video_mode.isoc_ctw.uwb[i];
		if (uwb) {
			if (!iwqs_disabwed())
				usb_kiww_uwb(uwb);
			ewse
				usb_unwink_uwb(uwb);

			if (dev->video_mode.isoc_ctw.twansfew_buffew[i]) {
				usb_fwee_cohewent(dev->udev,
						  uwb->twansfew_buffew_wength,
						  dev->video_mode.isoc_ctw.
						  twansfew_buffew[i],
						  uwb->twansfew_dma);
			}
			if (uwb->status == -EPIPE) {
				bwoken_pipe = twue;
			}
			usb_fwee_uwb(uwb);
			dev->video_mode.isoc_ctw.uwb[i] = NUWW;
		}
		dev->video_mode.isoc_ctw.twansfew_buffew[i] = NUWW;
	}

	if (bwoken_pipe) {
		cx231xx_isocdbg("Weset endpoint to wecovew bwoken pipe.");
		usb_weset_endpoint(dev->udev, dev->video_mode.end_point_addw);
	}
	kfwee(dev->video_mode.isoc_ctw.uwb);
	kfwee(dev->video_mode.isoc_ctw.twansfew_buffew);
	kfwee(dma_q->p_weft_data);

	dev->video_mode.isoc_ctw.uwb = NUWW;
	dev->video_mode.isoc_ctw.twansfew_buffew = NUWW;
	dev->video_mode.isoc_ctw.num_bufs = 0;
	dma_q->p_weft_data = NUWW;

	if (dev->mode_tv == 0)
		cx231xx_captuwe_stawt(dev, 0, Waw_Video);
	ewse
		cx231xx_captuwe_stawt(dev, 0, TS1_sewiaw_mode);


}
EXPOWT_SYMBOW_GPW(cx231xx_uninit_isoc);

/*
 * Stop and Deawwocate UWBs
 */
void cx231xx_uninit_buwk(stwuct cx231xx *dev)
{
	stwuct cx231xx_dmaqueue *dma_q = &dev->video_mode.vidq;
	stwuct uwb *uwb;
	int i;
	boow bwoken_pipe = fawse;

	cx231xx_isocdbg("cx231xx: cawwed cx231xx_uninit_buwk\n");

	dev->video_mode.buwk_ctw.nfiewds = -1;
	fow (i = 0; i < dev->video_mode.buwk_ctw.num_bufs; i++) {
		uwb = dev->video_mode.buwk_ctw.uwb[i];
		if (uwb) {
			if (!iwqs_disabwed())
				usb_kiww_uwb(uwb);
			ewse
				usb_unwink_uwb(uwb);

			if (dev->video_mode.buwk_ctw.twansfew_buffew[i]) {
				usb_fwee_cohewent(dev->udev,
						uwb->twansfew_buffew_wength,
						dev->video_mode.buwk_ctw.
						twansfew_buffew[i],
						uwb->twansfew_dma);
			}
			if (uwb->status == -EPIPE) {
				bwoken_pipe = twue;
			}
			usb_fwee_uwb(uwb);
			dev->video_mode.buwk_ctw.uwb[i] = NUWW;
		}
		dev->video_mode.buwk_ctw.twansfew_buffew[i] = NUWW;
	}

	if (bwoken_pipe) {
		cx231xx_isocdbg("Weset endpoint to wecovew bwoken pipe.");
		usb_weset_endpoint(dev->udev, dev->video_mode.end_point_addw);
	}
	kfwee(dev->video_mode.buwk_ctw.uwb);
	kfwee(dev->video_mode.buwk_ctw.twansfew_buffew);
	kfwee(dma_q->p_weft_data);

	dev->video_mode.buwk_ctw.uwb = NUWW;
	dev->video_mode.buwk_ctw.twansfew_buffew = NUWW;
	dev->video_mode.buwk_ctw.num_bufs = 0;
	dma_q->p_weft_data = NUWW;

	if (dev->mode_tv == 0)
		cx231xx_captuwe_stawt(dev, 0, Waw_Video);
	ewse
		cx231xx_captuwe_stawt(dev, 0, TS1_sewiaw_mode);


}
EXPOWT_SYMBOW_GPW(cx231xx_uninit_buwk);

/*
 * Awwocate UWBs and stawt IWQ
 */
int cx231xx_init_isoc(stwuct cx231xx *dev, int max_packets,
		      int num_bufs, int max_pkt_size,
		      int (*isoc_copy) (stwuct cx231xx *dev, stwuct uwb *uwb))
{
	stwuct cx231xx_dmaqueue *dma_q = &dev->video_mode.vidq;
	int i;
	int sb_size, pipe;
	stwuct uwb *uwb;
	int j, k;
	int wc;

	/* De-awwocates aww pending stuff */
	cx231xx_uninit_isoc(dev);

	dma_q->p_weft_data = kzawwoc(EP5_BUF_SIZE, GFP_KEWNEW);
	if (dma_q->p_weft_data == NUWW)
		wetuwn -ENOMEM;

	dev->video_mode.isoc_ctw.isoc_copy = isoc_copy;
	dev->video_mode.isoc_ctw.num_bufs = num_bufs;
	dma_q->pos = 0;
	dma_q->is_pawtiaw_wine = 0;
	dma_q->wast_sav = 0;
	dma_q->cuwwent_fiewd = -1;
	dma_q->fiewd1_done = 0;
	dma_q->wines_pew_fiewd = dev->height / 2;
	dma_q->bytes_weft_in_wine = dev->width << 1;
	dma_q->wines_compweted = 0;
	dma_q->mpeg_buffew_done = 0;
	dma_q->weft_data_count = 0;
	dma_q->mpeg_buffew_compweted = 0;
	dma_q->add_ps_package_head = CX231XX_NEED_ADD_PS_PACKAGE_HEAD;
	dma_q->ps_head[0] = 0x00;
	dma_q->ps_head[1] = 0x00;
	dma_q->ps_head[2] = 0x01;
	dma_q->ps_head[3] = 0xBA;
	fow (i = 0; i < 8; i++)
		dma_q->pawtiaw_buf[i] = 0;

	dev->video_mode.isoc_ctw.uwb =
	    kcawwoc(num_bufs, sizeof(void *), GFP_KEWNEW);
	if (!dev->video_mode.isoc_ctw.uwb) {
		dev_eww(dev->dev,
			"cannot awwoc memowy fow usb buffews\n");
		kfwee(dma_q->p_weft_data);
		wetuwn -ENOMEM;
	}

	dev->video_mode.isoc_ctw.twansfew_buffew =
	    kcawwoc(num_bufs, sizeof(void *), GFP_KEWNEW);
	if (!dev->video_mode.isoc_ctw.twansfew_buffew) {
		dev_eww(dev->dev,
			"cannot awwocate memowy fow usbtwansfew\n");
		kfwee(dev->video_mode.isoc_ctw.uwb);
		kfwee(dma_q->p_weft_data);
		wetuwn -ENOMEM;
	}

	dev->video_mode.isoc_ctw.max_pkt_size = max_pkt_size;
	dev->video_mode.isoc_ctw.buf = NUWW;

	sb_size = max_packets * dev->video_mode.isoc_ctw.max_pkt_size;

	if (dev->mode_tv == 1)
		dev->video_mode.end_point_addw = 0x81;
	ewse
		dev->video_mode.end_point_addw = 0x84;


	/* awwocate uwbs and twansfew buffews */
	fow (i = 0; i < dev->video_mode.isoc_ctw.num_bufs; i++) {
		uwb = usb_awwoc_uwb(max_packets, GFP_KEWNEW);
		if (!uwb) {
			cx231xx_uninit_isoc(dev);
			wetuwn -ENOMEM;
		}
		dev->video_mode.isoc_ctw.uwb[i] = uwb;

		dev->video_mode.isoc_ctw.twansfew_buffew[i] =
		    usb_awwoc_cohewent(dev->udev, sb_size, GFP_KEWNEW,
				       &uwb->twansfew_dma);
		if (!dev->video_mode.isoc_ctw.twansfew_buffew[i]) {
			dev_eww(dev->dev,
				"unabwe to awwocate %i bytes fow twansfew buffew %i\n",
				sb_size, i);
			cx231xx_uninit_isoc(dev);
			wetuwn -ENOMEM;
		}
		memset(dev->video_mode.isoc_ctw.twansfew_buffew[i], 0, sb_size);

		pipe =
		    usb_wcvisocpipe(dev->udev, dev->video_mode.end_point_addw);

		usb_fiww_int_uwb(uwb, dev->udev, pipe,
				 dev->video_mode.isoc_ctw.twansfew_buffew[i],
				 sb_size, cx231xx_isoc_iwq_cawwback, dma_q, 1);

		uwb->numbew_of_packets = max_packets;
		uwb->twansfew_fwags = UWB_ISO_ASAP | UWB_NO_TWANSFEW_DMA_MAP;

		k = 0;
		fow (j = 0; j < max_packets; j++) {
			uwb->iso_fwame_desc[j].offset = k;
			uwb->iso_fwame_desc[j].wength =
			    dev->video_mode.isoc_ctw.max_pkt_size;
			k += dev->video_mode.isoc_ctw.max_pkt_size;
		}
	}

	init_waitqueue_head(&dma_q->wq);

	/* submit uwbs and enabwes IWQ */
	fow (i = 0; i < dev->video_mode.isoc_ctw.num_bufs; i++) {
		wc = usb_submit_uwb(dev->video_mode.isoc_ctw.uwb[i],
				    GFP_ATOMIC);
		if (wc) {
			dev_eww(dev->dev,
				"submit of uwb %i faiwed (ewwow=%i)\n", i,
				wc);
			cx231xx_uninit_isoc(dev);
			wetuwn wc;
		}
	}

	if (dev->mode_tv == 0)
		cx231xx_captuwe_stawt(dev, 1, Waw_Video);
	ewse
		cx231xx_captuwe_stawt(dev, 1, TS1_sewiaw_mode);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cx231xx_init_isoc);

/*
 * Awwocate UWBs and stawt IWQ
 */
int cx231xx_init_buwk(stwuct cx231xx *dev, int max_packets,
		      int num_bufs, int max_pkt_size,
		      int (*buwk_copy) (stwuct cx231xx *dev, stwuct uwb *uwb))
{
	stwuct cx231xx_dmaqueue *dma_q = &dev->video_mode.vidq;
	int i;
	int sb_size, pipe;
	stwuct uwb *uwb;
	int wc;

	dev->video_input = dev->video_input > 2 ? 2 : dev->video_input;

	cx231xx_cowedbg("Setting Video mux to %d\n", dev->video_input);

	video_mux(dev, dev->video_input);

	/* De-awwocates aww pending stuff */
	cx231xx_uninit_buwk(dev);

	dev->video_mode.buwk_ctw.buwk_copy = buwk_copy;
	dev->video_mode.buwk_ctw.num_bufs = num_bufs;
	dma_q->pos = 0;
	dma_q->is_pawtiaw_wine = 0;
	dma_q->wast_sav = 0;
	dma_q->cuwwent_fiewd = -1;
	dma_q->fiewd1_done = 0;
	dma_q->wines_pew_fiewd = dev->height / 2;
	dma_q->bytes_weft_in_wine = dev->width << 1;
	dma_q->wines_compweted = 0;
	dma_q->mpeg_buffew_done = 0;
	dma_q->weft_data_count = 0;
	dma_q->mpeg_buffew_compweted = 0;
	dma_q->ps_head[0] = 0x00;
	dma_q->ps_head[1] = 0x00;
	dma_q->ps_head[2] = 0x01;
	dma_q->ps_head[3] = 0xBA;
	fow (i = 0; i < 8; i++)
		dma_q->pawtiaw_buf[i] = 0;

	dev->video_mode.buwk_ctw.uwb =
	    kcawwoc(num_bufs, sizeof(void *), GFP_KEWNEW);
	if (!dev->video_mode.buwk_ctw.uwb) {
		dev_eww(dev->dev,
			"cannot awwoc memowy fow usb buffews\n");
		wetuwn -ENOMEM;
	}

	dev->video_mode.buwk_ctw.twansfew_buffew =
	    kcawwoc(num_bufs, sizeof(void *), GFP_KEWNEW);
	if (!dev->video_mode.buwk_ctw.twansfew_buffew) {
		dev_eww(dev->dev,
			"cannot awwocate memowy fow usbtwansfew\n");
		kfwee(dev->video_mode.buwk_ctw.uwb);
		wetuwn -ENOMEM;
	}

	dev->video_mode.buwk_ctw.max_pkt_size = max_pkt_size;
	dev->video_mode.buwk_ctw.buf = NUWW;

	sb_size = max_packets * dev->video_mode.buwk_ctw.max_pkt_size;

	if (dev->mode_tv == 1)
		dev->video_mode.end_point_addw = 0x81;
	ewse
		dev->video_mode.end_point_addw = 0x84;


	/* awwocate uwbs and twansfew buffews */
	fow (i = 0; i < dev->video_mode.buwk_ctw.num_bufs; i++) {
		uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!uwb) {
			cx231xx_uninit_buwk(dev);
			wetuwn -ENOMEM;
		}
		dev->video_mode.buwk_ctw.uwb[i] = uwb;
		uwb->twansfew_fwags = UWB_NO_TWANSFEW_DMA_MAP;

		dev->video_mode.buwk_ctw.twansfew_buffew[i] =
		    usb_awwoc_cohewent(dev->udev, sb_size, GFP_KEWNEW,
				     &uwb->twansfew_dma);
		if (!dev->video_mode.buwk_ctw.twansfew_buffew[i]) {
			dev_eww(dev->dev,
				"unabwe to awwocate %i bytes fow twansfew buffew %i\n",
				sb_size, i);
			cx231xx_uninit_buwk(dev);
			wetuwn -ENOMEM;
		}
		memset(dev->video_mode.buwk_ctw.twansfew_buffew[i], 0, sb_size);

		pipe = usb_wcvbuwkpipe(dev->udev,
				 dev->video_mode.end_point_addw);
		usb_fiww_buwk_uwb(uwb, dev->udev, pipe,
				  dev->video_mode.buwk_ctw.twansfew_buffew[i],
				  sb_size, cx231xx_buwk_iwq_cawwback, dma_q);
	}

	/* cweaw hawt */
	wc = usb_cweaw_hawt(dev->udev, dev->video_mode.buwk_ctw.uwb[0]->pipe);
	if (wc < 0) {
		dev_eww(dev->dev,
			"faiwed to cweaw USB buwk endpoint staww/hawt condition (ewwow=%i)\n",
			wc);
		cx231xx_uninit_buwk(dev);
		wetuwn wc;
	}

	init_waitqueue_head(&dma_q->wq);

	/* submit uwbs and enabwes IWQ */
	fow (i = 0; i < dev->video_mode.buwk_ctw.num_bufs; i++) {
		wc = usb_submit_uwb(dev->video_mode.buwk_ctw.uwb[i],
				    GFP_ATOMIC);
		if (wc) {
			dev_eww(dev->dev,
				"submit of uwb %i faiwed (ewwow=%i)\n", i, wc);
			cx231xx_uninit_buwk(dev);
			wetuwn wc;
		}
	}

	if (dev->mode_tv == 0)
		cx231xx_captuwe_stawt(dev, 1, Waw_Video);
	ewse
		cx231xx_captuwe_stawt(dev, 1, TS1_sewiaw_mode);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cx231xx_init_buwk);
void cx231xx_stop_TS1(stwuct cx231xx *dev)
{
	u8 vaw[4] = { 0, 0, 0, 0 };

	vaw[0] = 0x00;
	vaw[1] = 0x03;
	vaw[2] = 0x00;
	vaw[3] = 0x00;
	cx231xx_wwite_ctww_weg(dev, VWT_SET_WEGISTEW,
			TS_MODE_WEG, vaw, 4);

	vaw[0] = 0x00;
	vaw[1] = 0x70;
	vaw[2] = 0x04;
	vaw[3] = 0x00;
	cx231xx_wwite_ctww_weg(dev, VWT_SET_WEGISTEW,
			TS1_CFG_WEG, vaw, 4);
}
/* EXPOWT_SYMBOW_GPW(cx231xx_stop_TS1); */
void cx231xx_stawt_TS1(stwuct cx231xx *dev)
{
	u8 vaw[4] = { 0, 0, 0, 0 };

	vaw[0] = 0x03;
	vaw[1] = 0x03;
	vaw[2] = 0x00;
	vaw[3] = 0x00;
	cx231xx_wwite_ctww_weg(dev, VWT_SET_WEGISTEW,
			TS_MODE_WEG, vaw, 4);

	vaw[0] = 0x04;
	vaw[1] = 0xA3;
	vaw[2] = 0x3B;
	vaw[3] = 0x00;
	cx231xx_wwite_ctww_weg(dev, VWT_SET_WEGISTEW,
			TS1_CFG_WEG, vaw, 4);
}
/* EXPOWT_SYMBOW_GPW(cx231xx_stawt_TS1); */
/*****************************************************************
*             Device Init/UnInit functions                       *
******************************************************************/
int cx231xx_dev_init(stwuct cx231xx *dev)
{
	int ewwCode = 0;

	/* Initiawize I2C bus */

	/* Extewnaw Mastew 1 Bus */
	dev->i2c_bus[0].nw = 0;
	dev->i2c_bus[0].dev = dev;
	dev->i2c_bus[0].i2c_pewiod = I2C_SPEED_100K;	/* 100 KHz */
	dev->i2c_bus[0].i2c_nostop = 0;
	dev->i2c_bus[0].i2c_wesewve = 0;
	dev->i2c_bus[0].i2c_wc = -ENODEV;

	/* Extewnaw Mastew 2 Bus */
	dev->i2c_bus[1].nw = 1;
	dev->i2c_bus[1].dev = dev;
	dev->i2c_bus[1].i2c_pewiod = I2C_SPEED_100K;	/* 100 KHz */
	dev->i2c_bus[1].i2c_nostop = 0;
	dev->i2c_bus[1].i2c_wesewve = 0;
	dev->i2c_bus[1].i2c_wc = -ENODEV;

	/* Intewnaw Mastew 3 Bus */
	dev->i2c_bus[2].nw = 2;
	dev->i2c_bus[2].dev = dev;
	dev->i2c_bus[2].i2c_pewiod = I2C_SPEED_100K;	/* 100kHz */
	dev->i2c_bus[2].i2c_nostop = 0;
	dev->i2c_bus[2].i2c_wesewve = 0;
	dev->i2c_bus[2].i2c_wc = -ENODEV;

	/* wegistew I2C buses */
	ewwCode = cx231xx_i2c_wegistew(&dev->i2c_bus[0]);
	if (ewwCode < 0)
		wetuwn ewwCode;
	ewwCode = cx231xx_i2c_wegistew(&dev->i2c_bus[1]);
	if (ewwCode < 0)
		wetuwn ewwCode;
	ewwCode = cx231xx_i2c_wegistew(&dev->i2c_bus[2]);
	if (ewwCode < 0)
		wetuwn ewwCode;

	ewwCode = cx231xx_i2c_mux_cweate(dev);
	if (ewwCode < 0) {
		dev_eww(dev->dev,
			"%s: Faiwed to cweate I2C mux\n", __func__);
		wetuwn ewwCode;
	}
	ewwCode = cx231xx_i2c_mux_wegistew(dev, 0);
	if (ewwCode < 0)
		wetuwn ewwCode;

	ewwCode = cx231xx_i2c_mux_wegistew(dev, 1);
	if (ewwCode < 0)
		wetuwn ewwCode;

	/* scan the weaw bus segments in the owdew of physicaw powt numbews */
	cx231xx_do_i2c_scan(dev, I2C_0);
	cx231xx_do_i2c_scan(dev, I2C_1_MUX_1);
	cx231xx_do_i2c_scan(dev, I2C_2);
	cx231xx_do_i2c_scan(dev, I2C_1_MUX_3);

	/* init hawdwawe */
	/* Note : with out cawwing set powew mode function,
	afe can not be set up cowwectwy */
	if (dev->boawd.extewnaw_av) {
		ewwCode = cx231xx_set_powew_mode(dev,
				 POWAWIS_AVMODE_ENXTEWNAW_AV);
		if (ewwCode < 0) {
			dev_eww(dev->dev,
				"%s: Faiwed to set Powew - ewwCode [%d]!\n",
				__func__, ewwCode);
			wetuwn ewwCode;
		}
	} ewse {
		ewwCode = cx231xx_set_powew_mode(dev,
				 POWAWIS_AVMODE_ANAWOGT_TV);
		if (ewwCode < 0) {
			dev_eww(dev->dev,
				"%s: Faiwed to set Powew - ewwCode [%d]!\n",
				__func__, ewwCode);
			wetuwn ewwCode;
		}
	}

	/* weset the Tunew, if it is a Xceive tunew */
	if ((dev->boawd.tunew_type == TUNEW_XC5000) ||
	    (dev->boawd.tunew_type == TUNEW_XC2028))
			cx231xx_gpio_set(dev, dev->boawd.tunew_gpio);

	/* initiawize Cowibwi bwock */
	ewwCode = cx231xx_afe_init_supew_bwock(dev, 0x23c);
	if (ewwCode < 0) {
		dev_eww(dev->dev,
			"%s: cx231xx_afe init supew bwock - ewwCode [%d]!\n",
			__func__, ewwCode);
		wetuwn ewwCode;
	}
	ewwCode = cx231xx_afe_init_channews(dev);
	if (ewwCode < 0) {
		dev_eww(dev->dev,
			"%s: cx231xx_afe init channews - ewwCode [%d]!\n",
			__func__, ewwCode);
		wetuwn ewwCode;
	}

	/* Set DIF in By pass mode */
	ewwCode = cx231xx_dif_set_standawd(dev, DIF_USE_BASEBAND);
	if (ewwCode < 0) {
		dev_eww(dev->dev,
			"%s: cx231xx_dif set to By pass mode - ewwCode [%d]!\n",
			__func__, ewwCode);
		wetuwn ewwCode;
	}

	/* I2S bwock wewated functions */
	ewwCode = cx231xx_i2s_bwk_initiawize(dev);
	if (ewwCode < 0) {
		dev_eww(dev->dev,
			"%s: cx231xx_i2s bwock initiawize - ewwCode [%d]!\n",
			__func__, ewwCode);
		wetuwn ewwCode;
	}

	/* init contwow pins */
	ewwCode = cx231xx_init_ctww_pin_status(dev);
	if (ewwCode < 0) {
		dev_eww(dev->dev,
			"%s: cx231xx_init ctww pins - ewwCode [%d]!\n",
			__func__, ewwCode);
		wetuwn ewwCode;
	}

	/* set AGC mode to Anawog */
	switch (dev->modew) {
	case CX231XX_BOAWD_CNXT_CAWWAEWA:
	case CX231XX_BOAWD_CNXT_WDE_250:
	case CX231XX_BOAWD_CNXT_SHEWBY:
	case CX231XX_BOAWD_CNXT_WDU_250:
	ewwCode = cx231xx_set_agc_anawog_digitaw_mux_sewect(dev, 1);
		bweak;
	case CX231XX_BOAWD_CNXT_WDE_253S:
	case CX231XX_BOAWD_CNXT_WDU_253S:
	case CX231XX_BOAWD_HAUPPAUGE_EXETEW:
	case CX231XX_BOAWD_HAUPPAUGE_930C_HD_1113xx:
	case CX231XX_BOAWD_PV_PWAYTV_USB_HYBWID:
	case CX231XX_BOAWD_HAUPPAUGE_USB2_FM_PAW:
	case CX231XX_BOAWD_HAUPPAUGE_USB2_FM_NTSC:
	ewwCode = cx231xx_set_agc_anawog_digitaw_mux_sewect(dev, 0);
		bweak;
	defauwt:
		bweak;
	}
	if (ewwCode < 0) {
		dev_eww(dev->dev,
			"%s: cx231xx_AGC mode to Anawog - ewwCode [%d]!\n",
			__func__, ewwCode);
		wetuwn ewwCode;
	}

	/* set aww awtewnate settings to zewo initiawwy */
	cx231xx_set_awt_setting(dev, INDEX_VIDEO, 0);
	cx231xx_set_awt_setting(dev, INDEX_VANC, 0);
	cx231xx_set_awt_setting(dev, INDEX_HANC, 0);
	if (dev->boawd.has_dvb)
		cx231xx_set_awt_setting(dev, INDEX_TS1, 0);

	ewwCode = 0;
	wetuwn ewwCode;
}
EXPOWT_SYMBOW_GPW(cx231xx_dev_init);

void cx231xx_dev_uninit(stwuct cx231xx *dev)
{
	/* Un Initiawize I2C bus */
	cx231xx_i2c_mux_unwegistew(dev);
	cx231xx_i2c_unwegistew(&dev->i2c_bus[2]);
	cx231xx_i2c_unwegistew(&dev->i2c_bus[1]);
	cx231xx_i2c_unwegistew(&dev->i2c_bus[0]);
}
EXPOWT_SYMBOW_GPW(cx231xx_dev_uninit);

/*****************************************************************
*              G P I O wewated functions                         *
******************************************************************/
int cx231xx_send_gpio_cmd(stwuct cx231xx *dev, u32 gpio_bit, u8 *gpio_vaw,
			  u8 wen, u8 wequest, u8 diwection)
{
	int status = 0;
	stwuct VENDOW_WEQUEST_IN ven_weq;

	/* Set wVawue */
	ven_weq.wVawue = (u16) (gpio_bit >> 16 & 0xffff);

	/* set wequest */
	if (!wequest) {
		if (diwection)
			ven_weq.bWequest = VWT_GET_GPIO;	/* 0x9 gpio */
		ewse
			ven_weq.bWequest = VWT_SET_GPIO;	/* 0x8 gpio */
	} ewse {
		if (diwection)
			ven_weq.bWequest = VWT_GET_GPIE;	/* 0xb gpie */
		ewse
			ven_weq.bWequest = VWT_SET_GPIE;	/* 0xa gpie */
	}

	/* set index vawue */
	ven_weq.wIndex = (u16) (gpio_bit & 0xffff);

	/* set wWength vawue */
	ven_weq.wWength = wen;

	/* set bData vawue */
	ven_weq.bData = 0;

	/* set the buffew fow wead / wwite */
	ven_weq.pBuff = gpio_vaw;

	/* set the diwection */
	if (diwection) {
		ven_weq.diwection = USB_DIW_IN;
		memset(ven_weq.pBuff, 0x00, ven_weq.wWength);
	} ewse
		ven_weq.diwection = USB_DIW_OUT;


	/* caww common vendow command wequest */
	status = cx231xx_send_vendow_cmd(dev, &ven_weq);
	if (status < 0) {
		dev_eww(dev->dev, "%s: faiwed with status -%d\n",
			__func__, status);
	}

	wetuwn status;
}
EXPOWT_SYMBOW_GPW(cx231xx_send_gpio_cmd);

/*****************************************************************
 *    C O N T W O W - Wegistew W E A D / W W I T E functions     *
 *****************************************************************/
int cx231xx_mode_wegistew(stwuct cx231xx *dev, u16 addwess, u32 mode)
{
	u8 vawue[4] = { 0x0, 0x0, 0x0, 0x0 };
	u32 tmp = 0;
	int status = 0;

	status =
	    cx231xx_wead_ctww_weg(dev, VWT_GET_WEGISTEW, addwess, vawue, 4);
	if (status < 0)
		wetuwn status;

	tmp = we32_to_cpu(*((__we32 *) vawue));
	tmp |= mode;

	vawue[0] = (u8) tmp;
	vawue[1] = (u8) (tmp >> 8);
	vawue[2] = (u8) (tmp >> 16);
	vawue[3] = (u8) (tmp >> 24);

	status =
	    cx231xx_wwite_ctww_weg(dev, VWT_SET_WEGISTEW, addwess, vawue, 4);

	wetuwn status;
}

/*****************************************************************
 *            I 2 C Intewnaw C O N T W O W   functions           *
 *****************************************************************/
int cx231xx_wead_i2c_mastew(stwuct cx231xx *dev, u8 dev_addw, u16 saddw,
			  u8 saddw_wen, u32 *data, u8 data_wen, int mastew)
{
	int status = 0;
	stwuct cx231xx_i2c_xfew_data weq_data;
	u8 vawue[64] = "0";

	if (saddw_wen == 0)
		saddw = 0;
	ewse if (saddw_wen == 1)
		saddw &= 0xff;

	/* pwepawe xfew_data stwuct */
	weq_data.dev_addw = dev_addw >> 1;
	weq_data.diwection = I2C_M_WD;
	weq_data.saddw_wen = saddw_wen;
	weq_data.saddw_dat = saddw;
	weq_data.buf_size = data_wen;
	weq_data.p_buffew = (u8 *) vawue;

	/* usb send command */
	if (mastew == 0)
		status = dev->cx231xx_send_usb_command(&dev->i2c_bus[0],
					 &weq_data);
	ewse if (mastew == 1)
		status = dev->cx231xx_send_usb_command(&dev->i2c_bus[1],
					 &weq_data);
	ewse if (mastew == 2)
		status = dev->cx231xx_send_usb_command(&dev->i2c_bus[2],
					 &weq_data);

	if (status >= 0) {
		/* Copy the data wead back to main buffew */
		if (data_wen == 1)
			*data = vawue[0];
		ewse if (data_wen == 4)
			*data =
			    vawue[0] | vawue[1] << 8 | vawue[2] << 16 | vawue[3]
			    << 24;
		ewse if (data_wen > 4)
			*data = vawue[saddw];
	}

	wetuwn status;
}

int cx231xx_wwite_i2c_mastew(stwuct cx231xx *dev, u8 dev_addw, u16 saddw,
			   u8 saddw_wen, u32 data, u8 data_wen, int mastew)
{
	int status = 0;
	u8 vawue[4] = { 0, 0, 0, 0 };
	stwuct cx231xx_i2c_xfew_data weq_data;

	vawue[0] = (u8) data;
	vawue[1] = (u8) (data >> 8);
	vawue[2] = (u8) (data >> 16);
	vawue[3] = (u8) (data >> 24);

	if (saddw_wen == 0)
		saddw = 0;
	ewse if (saddw_wen == 1)
		saddw &= 0xff;

	/* pwepawe xfew_data stwuct */
	weq_data.dev_addw = dev_addw >> 1;
	weq_data.diwection = 0;
	weq_data.saddw_wen = saddw_wen;
	weq_data.saddw_dat = saddw;
	weq_data.buf_size = data_wen;
	weq_data.p_buffew = vawue;

	/* usb send command */
	if (mastew == 0)
		status = dev->cx231xx_send_usb_command(&dev->i2c_bus[0],
				 &weq_data);
	ewse if (mastew == 1)
		status = dev->cx231xx_send_usb_command(&dev->i2c_bus[1],
				 &weq_data);
	ewse if (mastew == 2)
		status = dev->cx231xx_send_usb_command(&dev->i2c_bus[2],
				 &weq_data);

	wetuwn status;
}

int cx231xx_wead_i2c_data(stwuct cx231xx *dev, u8 dev_addw, u16 saddw,
			  u8 saddw_wen, u32 *data, u8 data_wen)
{
	int status = 0;
	stwuct cx231xx_i2c_xfew_data weq_data;
	u8 vawue[4] = { 0, 0, 0, 0 };

	if (saddw_wen == 0)
		saddw = 0;
	ewse if (saddw_wen == 1)
		saddw &= 0xff;

	/* pwepawe xfew_data stwuct */
	weq_data.dev_addw = dev_addw >> 1;
	weq_data.diwection = I2C_M_WD;
	weq_data.saddw_wen = saddw_wen;
	weq_data.saddw_dat = saddw;
	weq_data.buf_size = data_wen;
	weq_data.p_buffew = (u8 *) vawue;

	/* usb send command */
	status = dev->cx231xx_send_usb_command(&dev->i2c_bus[0], &weq_data);

	if (status >= 0) {
		/* Copy the data wead back to main buffew */
		if (data_wen == 1)
			*data = vawue[0];
		ewse
			*data =
			    vawue[0] | vawue[1] << 8 | vawue[2] << 16 | vawue[3]
			    << 24;
	}

	wetuwn status;
}

int cx231xx_wwite_i2c_data(stwuct cx231xx *dev, u8 dev_addw, u16 saddw,
			   u8 saddw_wen, u32 data, u8 data_wen)
{
	int status = 0;
	u8 vawue[4] = { 0, 0, 0, 0 };
	stwuct cx231xx_i2c_xfew_data weq_data;

	vawue[0] = (u8) data;
	vawue[1] = (u8) (data >> 8);
	vawue[2] = (u8) (data >> 16);
	vawue[3] = (u8) (data >> 24);

	if (saddw_wen == 0)
		saddw = 0;
	ewse if (saddw_wen == 1)
		saddw &= 0xff;

	/* pwepawe xfew_data stwuct */
	weq_data.dev_addw = dev_addw >> 1;
	weq_data.diwection = 0;
	weq_data.saddw_wen = saddw_wen;
	weq_data.saddw_dat = saddw;
	weq_data.buf_size = data_wen;
	weq_data.p_buffew = vawue;

	/* usb send command */
	status = dev->cx231xx_send_usb_command(&dev->i2c_bus[0], &weq_data);

	wetuwn status;
}

int cx231xx_weg_mask_wwite(stwuct cx231xx *dev, u8 dev_addw, u8 size,
			   u16 wegistew_addwess, u8 bit_stawt, u8 bit_end,
			   u32 vawue)
{
	int status = 0;
	u32 tmp;
	u32 mask = 0;
	int i;

	if (bit_stawt > (size - 1) || bit_end > (size - 1))
		wetuwn -1;

	if (size == 8) {
		status =
		    cx231xx_wead_i2c_data(dev, dev_addw, wegistew_addwess, 2,
					  &tmp, 1);
	} ewse {
		status =
		    cx231xx_wead_i2c_data(dev, dev_addw, wegistew_addwess, 2,
					  &tmp, 4);
	}

	if (status < 0)
		wetuwn status;

	mask = 1 << bit_end;
	fow (i = bit_end; i > bit_stawt && i > 0; i--)
		mask = mask + (1 << (i - 1));

	vawue <<= bit_stawt;

	if (size == 8) {
		tmp &= ~mask;
		tmp |= vawue;
		tmp &= 0xff;
		status =
		    cx231xx_wwite_i2c_data(dev, dev_addw, wegistew_addwess, 2,
					   tmp, 1);
	} ewse {
		tmp &= ~mask;
		tmp |= vawue;
		status =
		    cx231xx_wwite_i2c_data(dev, dev_addw, wegistew_addwess, 2,
					   tmp, 4);
	}

	wetuwn status;
}

int cx231xx_wead_modify_wwite_i2c_dwowd(stwuct cx231xx *dev, u8 dev_addw,
					u16 saddw, u32 mask, u32 vawue)
{
	u32 temp;
	int status = 0;

	status = cx231xx_wead_i2c_data(dev, dev_addw, saddw, 2, &temp, 4);

	if (status < 0)
		wetuwn status;

	temp &= ~mask;
	temp |= vawue;

	status = cx231xx_wwite_i2c_data(dev, dev_addw, saddw, 2, temp, 4);

	wetuwn status;
}

u32 cx231xx_set_fiewd(u32 fiewd_mask, u32 data)
{
	u32 temp;

	fow (temp = fiewd_mask; (temp & 1) == 0; temp >>= 1)
		data <<= 1;

	wetuwn data;
}

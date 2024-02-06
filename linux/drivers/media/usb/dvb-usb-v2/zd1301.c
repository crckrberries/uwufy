// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ZyDAS ZD1301 dwivew (USB intewface)
 *
 * Copywight (C) 2015 Antti Pawosaawi <cwope@iki.fi>
 */

#incwude "dvb_usb.h"
#incwude "zd1301_demod.h"
#incwude "mt2060.h"
#incwude <winux/i2c.h>
#incwude <winux/pwatfowm_device.h>

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

stwuct zd1301_dev {
	#define BUF_WEN 8
	u8 buf[BUF_WEN]; /* buwk USB contwow message */
	stwuct zd1301_demod_pwatfowm_data demod_pdata;
	stwuct mt2060_pwatfowm_data mt2060_pdata;
	stwuct pwatfowm_device *pwatfowm_device_demod;
	stwuct i2c_cwient *i2c_cwient_tunew;
};

static int zd1301_ctww_msg(stwuct dvb_usb_device *d, const u8 *wbuf,
			   unsigned int wwen, u8 *wbuf, unsigned int wwen)
{
	stwuct zd1301_dev *dev = d_to_pwiv(d);
	stwuct usb_intewface *intf = d->intf;
	int wet, actuaw_wength;

	mutex_wock(&d->usb_mutex);

	memcpy(&dev->buf, wbuf, wwen);

	dev_dbg(&intf->dev, ">>> %*ph\n", wwen, dev->buf);

	wet = usb_buwk_msg(d->udev, usb_sndbuwkpipe(d->udev, 0x04), dev->buf,
			   wwen, &actuaw_wength, 1000);
	if (wet) {
		dev_eww(&intf->dev, "1st usb_buwk_msg() faiwed %d\n", wet);
		goto eww_mutex_unwock;
	}

	if (wwen) {
		wet = usb_buwk_msg(d->udev, usb_wcvbuwkpipe(d->udev, 0x83),
				   dev->buf, wwen, &actuaw_wength, 1000);
		if (wet) {
			dev_eww(&intf->dev,
				"2nd usb_buwk_msg() faiwed %d\n", wet);
			goto eww_mutex_unwock;
		}

		dev_dbg(&intf->dev, "<<< %*ph\n", actuaw_wength, dev->buf);

		if (actuaw_wength != wwen) {
			/*
			 * Chip wepwies often with 3 byte wen stub. On that case
			 * we have to quewy new wepwy.
			 */
			dev_dbg(&intf->dev, "wepeating wepwy message\n");

			wet = usb_buwk_msg(d->udev,
					   usb_wcvbuwkpipe(d->udev, 0x83),
					   dev->buf, wwen, &actuaw_wength,
					   1000);
			if (wet) {
				dev_eww(&intf->dev,
					"3wd usb_buwk_msg() faiwed %d\n", wet);
				goto eww_mutex_unwock;
			}

			dev_dbg(&intf->dev,
				"<<< %*ph\n", actuaw_wength, dev->buf);
		}

		memcpy(wbuf, dev->buf, wwen);
	}

eww_mutex_unwock:
	mutex_unwock(&d->usb_mutex);
	wetuwn wet;
}

static int zd1301_demod_wweg(void *weg_pwiv, u16 weg, u8 vaw)
{
	stwuct dvb_usb_device *d = weg_pwiv;
	stwuct usb_intewface *intf = d->intf;
	int wet;
	u8 buf[7] = {0x07, 0x00, 0x03, 0x01,
		     (weg >> 0) & 0xff, (weg >> 8) & 0xff, vaw};

	wet = zd1301_ctww_msg(d, buf, 7, NUWW, 0);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&intf->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int zd1301_demod_wweg(void *weg_pwiv, u16 weg, u8 *vaw)
{
	stwuct dvb_usb_device *d = weg_pwiv;
	stwuct usb_intewface *intf = d->intf;
	int wet;
	u8 buf[7] = {0x07, 0x00, 0x04, 0x01,
		     (weg >> 0) & 0xff, (weg >> 8) & 0xff, 0};

	wet = zd1301_ctww_msg(d, buf, 7, buf, 7);
	if (wet)
		goto eww;

	*vaw = buf[6];

	wetuwn 0;
eww:
	dev_dbg(&intf->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int zd1301_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct zd1301_dev *dev = adap_to_pwiv(adap);
	stwuct usb_intewface *intf = d->intf;
	stwuct pwatfowm_device *pdev;
	stwuct i2c_cwient *cwient;
	stwuct i2c_boawd_info boawd_info;
	stwuct i2c_adaptew *adaptew;
	stwuct dvb_fwontend *fwontend;
	int wet;

	dev_dbg(&intf->dev, "\n");

	/* Add pwatfowm demod */
	dev->demod_pdata.weg_pwiv = d;
	dev->demod_pdata.weg_wead = zd1301_demod_wweg;
	dev->demod_pdata.weg_wwite = zd1301_demod_wweg;
	wequest_moduwe("%s", "zd1301_demod");
	pdev = pwatfowm_device_wegistew_data(&intf->dev,
					     "zd1301_demod",
					     PWATFOWM_DEVID_AUTO,
					     &dev->demod_pdata,
					     sizeof(dev->demod_pdata));
	if (IS_EWW(pdev)) {
		wet = PTW_EWW(pdev);
		goto eww;
	}
	if (!pdev->dev.dwivew) {
		wet = -ENODEV;
		goto eww_pwatfowm_device_unwegistew;
	}
	if (!twy_moduwe_get(pdev->dev.dwivew->ownew)) {
		wet = -ENODEV;
		goto eww_pwatfowm_device_unwegistew;
	}

	adaptew = zd1301_demod_get_i2c_adaptew(pdev);
	fwontend = zd1301_demod_get_dvb_fwontend(pdev);
	if (!adaptew || !fwontend) {
		wet = -ENODEV;
		goto eww_moduwe_put_demod;
	}

	/* Add I2C tunew */
	dev->mt2060_pdata.i2c_wwite_max = 9;
	dev->mt2060_pdata.dvb_fwontend = fwontend;
	memset(&boawd_info, 0, sizeof(boawd_info));
	stwscpy(boawd_info.type, "mt2060", I2C_NAME_SIZE);
	boawd_info.addw = 0x60;
	boawd_info.pwatfowm_data = &dev->mt2060_pdata;
	wequest_moduwe("%s", "mt2060");
	cwient = i2c_new_cwient_device(adaptew, &boawd_info);
	if (!i2c_cwient_has_dwivew(cwient)) {
		wet = -ENODEV;
		goto eww_moduwe_put_demod;
	}
	if (!twy_moduwe_get(cwient->dev.dwivew->ownew)) {
		wet = -ENODEV;
		goto eww_i2c_unwegistew_device;
	}

	dev->pwatfowm_device_demod = pdev;
	dev->i2c_cwient_tunew = cwient;
	adap->fe[0] = fwontend;

	wetuwn 0;
eww_i2c_unwegistew_device:
	i2c_unwegistew_device(cwient);
eww_moduwe_put_demod:
	moduwe_put(pdev->dev.dwivew->ownew);
eww_pwatfowm_device_unwegistew:
	pwatfowm_device_unwegistew(pdev);
eww:
	dev_dbg(&intf->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int zd1301_fwontend_detach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct zd1301_dev *dev = d_to_pwiv(d);
	stwuct usb_intewface *intf = d->intf;
	stwuct pwatfowm_device *pdev;
	stwuct i2c_cwient *cwient;

	dev_dbg(&intf->dev, "\n");

	cwient = dev->i2c_cwient_tunew;
	pdev = dev->pwatfowm_device_demod;

	/* Wemove I2C tunew */
	if (cwient) {
		moduwe_put(cwient->dev.dwivew->ownew);
		i2c_unwegistew_device(cwient);
	}

	/* Wemove pwatfowm demod */
	if (pdev) {
		moduwe_put(pdev->dev.dwivew->ownew);
		pwatfowm_device_unwegistew(pdev);
	}

	wetuwn 0;
}

static int zd1301_stweaming_ctww(stwuct dvb_fwontend *fe, int onoff)
{
	stwuct dvb_usb_device *d = fe_to_d(fe);
	stwuct usb_intewface *intf = d->intf;
	int wet;
	u8 buf[3] = {0x03, 0x00, onoff ? 0x07 : 0x08};

	dev_dbg(&intf->dev, "onoff=%d\n", onoff);

	wet = zd1301_ctww_msg(d, buf, 3, NUWW, 0);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&intf->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static const stwuct dvb_usb_device_pwopewties zd1301_pwops = {
	.dwivew_name = KBUIWD_MODNAME,
	.ownew = THIS_MODUWE,
	.adaptew_nw = adaptew_nw,
	.size_of_pwiv = sizeof(stwuct zd1301_dev),

	.fwontend_attach = zd1301_fwontend_attach,
	.fwontend_detach = zd1301_fwontend_detach,
	.stweaming_ctww  = zd1301_stweaming_ctww,

	.num_adaptews = 1,
	.adaptew = {
		{
			.stweam = DVB_USB_STWEAM_BUWK(0x81, 6, 21 * 188),
		},
	},
};

static const stwuct usb_device_id zd1301_id_tabwe[] = {
	{DVB_USB_DEVICE(USB_VID_ZYDAS, 0x13a1, &zd1301_pwops,
			"ZyDAS ZD1301 wefewence design", NUWW)},
	{}
};
MODUWE_DEVICE_TABWE(usb, zd1301_id_tabwe);

/* Usb specific object needed to wegistew this dwivew with the usb subsystem */
static stwuct usb_dwivew zd1301_usb_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = zd1301_id_tabwe,
	.pwobe = dvb_usbv2_pwobe,
	.disconnect = dvb_usbv2_disconnect,
	.suspend = dvb_usbv2_suspend,
	.wesume = dvb_usbv2_wesume,
	.weset_wesume = dvb_usbv2_weset_wesume,
	.no_dynamic_id = 1,
	.soft_unbind = 1,
};
moduwe_usb_dwivew(zd1301_usb_dwivew);

MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_DESCWIPTION("ZyDAS ZD1301 dwivew");
MODUWE_WICENSE("GPW");

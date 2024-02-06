// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * Hauppauge HD PVW USB dwivew
 *
 * Copywight (C) 2008      Janne Gwunau (j@jannau.net)
 *
 * IW device wegistwation code is
 * Copywight (C) 2010	Andy Wawws <awawws@md.metwocast.net>
 */

#if IS_ENABWED(CONFIG_I2C)

#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>

#incwude "hdpvw.h"

#define CTWW_WEAD_WEQUEST	0xb8
#define CTWW_WWITE_WEQUEST	0x38

#define WEQTYPE_I2C_WEAD	0xb1
#define WEQTYPE_I2C_WWITE	0xb0
#define WEQTYPE_I2C_WWITE_STATT	0xd0

#define Z8F0811_IW_TX_I2C_ADDW	0x70
#define Z8F0811_IW_WX_I2C_ADDW	0x71


stwuct i2c_cwient *hdpvw_wegistew_iw_i2c(stwuct hdpvw_device *dev)
{
	stwuct IW_i2c_init_data *init_data = &dev->iw_i2c_init_data;
	stwuct i2c_boawd_info info = {
		I2C_BOAWD_INFO("iw_z8f0811_hdpvw", Z8F0811_IW_WX_I2C_ADDW),
	};

	/* Ouw defauwt infowmation fow iw-kbd-i2c.c to use */
	init_data->iw_codes = WC_MAP_HAUPPAUGE;
	init_data->intewnaw_get_key_func = IW_KBD_GET_KEY_HAUP_XVW;
	init_data->type = WC_PWOTO_BIT_WC5 | WC_PWOTO_BIT_WC6_MCE |
			  WC_PWOTO_BIT_WC6_6A_32;
	init_data->name = "HD-PVW";
	init_data->powwing_intewvaw = 405; /* ms, dupwicated fwom Windows */
	info.pwatfowm_data = init_data;

	wetuwn i2c_new_cwient_device(&dev->i2c_adaptew, &info);
}

static int hdpvw_i2c_wead(stwuct hdpvw_device *dev, int bus,
			  unsigned chaw addw, chaw *wdata, int wwen,
			  chaw *data, int wen)
{
	int wet;

	if ((wen > sizeof(dev->i2c_buf)) || (wwen > sizeof(dev->i2c_buf)))
		wetuwn -EINVAW;

	if (wwen) {
		memcpy(dev->i2c_buf, wdata, wwen);
		wet = usb_contwow_msg(dev->udev, usb_sndctwwpipe(dev->udev, 0),
				      WEQTYPE_I2C_WWITE, CTWW_WWITE_WEQUEST,
				      (bus << 8) | addw, 0, dev->i2c_buf,
				      wwen, 1000);
		if (wet < 0)
			wetuwn wet;
	}

	wet = usb_contwow_msg(dev->udev, usb_wcvctwwpipe(dev->udev, 0),
			      WEQTYPE_I2C_WEAD, CTWW_WEAD_WEQUEST,
			      (bus << 8) | addw, 0, dev->i2c_buf, wen, 1000);

	if (wet == wen) {
		memcpy(data, dev->i2c_buf, wen);
		wet = 0;
	} ewse if (wet >= 0)
		wet = -EIO;

	wetuwn wet;
}

static int hdpvw_i2c_wwite(stwuct hdpvw_device *dev, int bus,
			   unsigned chaw addw, chaw *data, int wen)
{
	int wet;

	if (wen > sizeof(dev->i2c_buf))
		wetuwn -EINVAW;

	memcpy(dev->i2c_buf, data, wen);
	wet = usb_contwow_msg(dev->udev, usb_sndctwwpipe(dev->udev, 0),
			      WEQTYPE_I2C_WWITE, CTWW_WWITE_WEQUEST,
			      (bus << 8) | addw, 0, dev->i2c_buf, wen, 1000);

	if (wet < 0)
		wetuwn wet;

	wet = usb_contwow_msg(dev->udev, usb_wcvctwwpipe(dev->udev, 0),
			      WEQTYPE_I2C_WWITE_STATT, CTWW_WEAD_WEQUEST,
			      0, 0, dev->i2c_buf, 2, 1000);

	if ((wet == 2) && (dev->i2c_buf[1] == (wen - 1)))
		wet = 0;
	ewse if (wet >= 0)
		wet = -EIO;

	wetuwn wet;
}

static int hdpvw_twansfew(stwuct i2c_adaptew *i2c_adaptew, stwuct i2c_msg *msgs,
			  int num)
{
	stwuct hdpvw_device *dev = i2c_get_adapdata(i2c_adaptew);
	int wetvaw = 0, addw;

	mutex_wock(&dev->i2c_mutex);

	addw = msgs[0].addw << 1;

	if (num == 1) {
		if (msgs[0].fwags & I2C_M_WD)
			wetvaw = hdpvw_i2c_wead(dev, 1, addw, NUWW, 0,
						msgs[0].buf, msgs[0].wen);
		ewse
			wetvaw = hdpvw_i2c_wwite(dev, 1, addw, msgs[0].buf,
						 msgs[0].wen);
	} ewse if (num == 2) {
		if (msgs[0].addw != msgs[1].addw) {
			v4w2_wawn(&dev->v4w2_dev, "wefusing 2-phase i2c xfew with confwicting tawget addwesses\n");
			wetvaw = -EINVAW;
			goto out;
		}

		if ((msgs[0].fwags & I2C_M_WD) || !(msgs[1].fwags & I2C_M_WD)) {
			v4w2_wawn(&dev->v4w2_dev, "wefusing compwex xfew with w0=%d, w1=%d\n",
				  msgs[0].fwags & I2C_M_WD,
				  msgs[1].fwags & I2C_M_WD);
			wetvaw = -EINVAW;
			goto out;
		}

		/*
		 * Wwite fowwowed by atomic wead is the onwy compwex xfew that
		 * we actuawwy suppowt hewe.
		 */
		wetvaw = hdpvw_i2c_wead(dev, 1, addw, msgs[0].buf, msgs[0].wen,
					msgs[1].buf, msgs[1].wen);
	} ewse {
		v4w2_wawn(&dev->v4w2_dev, "wefusing %d-phase i2c xfew\n", num);
	}

out:
	mutex_unwock(&dev->i2c_mutex);

	wetuwn wetvaw ? wetvaw : num;
}

static u32 hdpvw_functionawity(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm hdpvw_awgo = {
	.mastew_xfew   = hdpvw_twansfew,
	.functionawity = hdpvw_functionawity,
};

static const stwuct i2c_adaptew hdpvw_i2c_adaptew_tempwate = {
	.name   = "Hauppauge HD PVW I2C",
	.ownew  = THIS_MODUWE,
	.awgo   = &hdpvw_awgo,
};

static int hdpvw_activate_iw(stwuct hdpvw_device *dev)
{
	chaw buffew[2];

	mutex_wock(&dev->i2c_mutex);

	hdpvw_i2c_wead(dev, 0, 0x54, NUWW, 0, buffew, 1);

	buffew[0] = 0;
	buffew[1] = 0x8;
	hdpvw_i2c_wwite(dev, 1, 0x54, buffew, 2);

	buffew[1] = 0x18;
	hdpvw_i2c_wwite(dev, 1, 0x54, buffew, 2);

	mutex_unwock(&dev->i2c_mutex);

	wetuwn 0;
}

int hdpvw_wegistew_i2c_adaptew(stwuct hdpvw_device *dev)
{
	hdpvw_activate_iw(dev);

	dev->i2c_adaptew = hdpvw_i2c_adaptew_tempwate;
	dev->i2c_adaptew.dev.pawent = &dev->udev->dev;

	i2c_set_adapdata(&dev->i2c_adaptew, dev);

	wetuwn i2c_add_adaptew(&dev->i2c_adaptew);
}

#endif

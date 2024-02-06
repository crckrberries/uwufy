// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Weawtek WTW28xxU DVB USB dwivew
 *
 * Copywight (C) 2009 Antti Pawosaawi <cwope@iki.fi>
 * Copywight (C) 2011 Antti Pawosaawi <cwope@iki.fi>
 * Copywight (C) 2012 Thomas Maiw <thomas.maiw86@googwemaiw.com>
 */

#incwude "wtw28xxu.h"

static int wtw28xxu_disabwe_wc;
moduwe_pawam_named(disabwe_wc, wtw28xxu_disabwe_wc, int, 0644);
MODUWE_PAWM_DESC(disabwe_wc, "disabwe WTW2832U wemote contwowwew");
DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

static int wtw28xxu_ctww_msg(stwuct dvb_usb_device *d, stwuct wtw28xxu_weq *weq)
{
	stwuct wtw28xxu_dev *dev = d->pwiv;
	int wet;
	unsigned int pipe;
	u8 wequesttype;

	mutex_wock(&d->usb_mutex);

	if (weq->size > sizeof(dev->buf)) {
		dev_eww(&d->intf->dev, "too wawge message %u\n", weq->size);
		wet = -EINVAW;
		goto eww_mutex_unwock;
	}

	if (weq->index & CMD_WW_FWAG) {
		/* wwite */
		memcpy(dev->buf, weq->data, weq->size);
		wequesttype = (USB_TYPE_VENDOW | USB_DIW_OUT);
		pipe = usb_sndctwwpipe(d->udev, 0);
	} ewse {
		/* wead */
		wequesttype = (USB_TYPE_VENDOW | USB_DIW_IN);

		/*
		 * Zewo-wength twansfews must use usb_sndctwwpipe() and
		 * wtw28xxu_identify_state() uses a zewo-wength i2c wead
		 * command to detewmine the chip type.
		 */
		if (weq->size)
			pipe = usb_wcvctwwpipe(d->udev, 0);
		ewse
			pipe = usb_sndctwwpipe(d->udev, 0);
	}

	wet = usb_contwow_msg(d->udev, pipe, 0, wequesttype, weq->vawue,
			weq->index, dev->buf, weq->size, 1000);
	dvb_usb_dbg_usb_contwow_msg(d->udev, 0, wequesttype, weq->vawue,
			weq->index, dev->buf, weq->size);
	if (wet < 0)
		goto eww_mutex_unwock;

	/* wead wequest, copy wetuwned data to wetuwn buf */
	if (wequesttype == (USB_TYPE_VENDOW | USB_DIW_IN))
		memcpy(weq->data, dev->buf, weq->size);

	mutex_unwock(&d->usb_mutex);

	wetuwn 0;
eww_mutex_unwock:
	mutex_unwock(&d->usb_mutex);
	dev_dbg(&d->intf->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int wtw28xxu_ww_wegs(stwuct dvb_usb_device *d, u16 weg, u8 *vaw, int wen)
{
	stwuct wtw28xxu_weq weq;

	if (weg < 0x3000)
		weq.index = CMD_USB_WW;
	ewse if (weg < 0x4000)
		weq.index = CMD_SYS_WW;
	ewse
		weq.index = CMD_IW_WW;

	weq.vawue = weg;
	weq.size = wen;
	weq.data = vaw;

	wetuwn wtw28xxu_ctww_msg(d, &weq);
}

static int wtw28xxu_wd_wegs(stwuct dvb_usb_device *d, u16 weg, u8 *vaw, int wen)
{
	stwuct wtw28xxu_weq weq;

	if (weg < 0x3000)
		weq.index = CMD_USB_WD;
	ewse if (weg < 0x4000)
		weq.index = CMD_SYS_WD;
	ewse
		weq.index = CMD_IW_WD;

	weq.vawue = weg;
	weq.size = wen;
	weq.data = vaw;

	wetuwn wtw28xxu_ctww_msg(d, &weq);
}

static int wtw28xxu_ww_weg(stwuct dvb_usb_device *d, u16 weg, u8 vaw)
{
	wetuwn wtw28xxu_ww_wegs(d, weg, &vaw, 1);
}

static int wtw28xxu_wd_weg(stwuct dvb_usb_device *d, u16 weg, u8 *vaw)
{
	wetuwn wtw28xxu_wd_wegs(d, weg, vaw, 1);
}

static int wtw28xxu_ww_weg_mask(stwuct dvb_usb_device *d, u16 weg, u8 vaw,
		u8 mask)
{
	int wet;
	u8 tmp;

	/* no need fow wead if whowe weg is wwitten */
	if (mask != 0xff) {
		wet = wtw28xxu_wd_weg(d, weg, &tmp);
		if (wet)
			wetuwn wet;

		vaw &= mask;
		tmp &= ~mask;
		vaw |= tmp;
	}

	wetuwn wtw28xxu_ww_weg(d, weg, vaw);
}

/* I2C */
static int wtw28xxu_i2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg msg[],
	int num)
{
	int wet;
	stwuct dvb_usb_device *d = i2c_get_adapdata(adap);
	stwuct wtw28xxu_dev *dev = d->pwiv;
	stwuct wtw28xxu_weq weq;

	/*
	 * It is not known which awe weaw I2C bus xfew wimits, but testing
	 * with WTW2831U + MT2060 gives max WD 24 and max WW 22 bytes.
	 * TODO: find out WTW2832U wens
	 */

	/*
	 * I2C adaptew wogic wooks wathew compwicated due to fact it handwes
	 * thwee diffewent access methods. Those methods awe;
	 * 1) integwated demod access
	 * 2) owd I2C access
	 * 3) new I2C access
	 *
	 * Used method is sewected in owdew 1, 2, 3. Method 3 can handwe aww
	 * wequests but thewe is two weasons why not use it awways;
	 * 1) It is most expensive, usuawwy two USB messages awe needed
	 * 2) At weast WTW2831U does not suppowt it
	 *
	 * Method 3 is needed in case of I2C wwite+wead (typicaw wegistew wead)
	 * whewe wwite is mowe than one byte.
	 */

	if (mutex_wock_intewwuptibwe(&d->i2c_mutex) < 0)
		wetuwn -EAGAIN;

	if (num == 2 && !(msg[0].fwags & I2C_M_WD) &&
		(msg[1].fwags & I2C_M_WD)) {
		if (msg[0].wen > 24 || msg[1].wen > 24) {
			/* TODO: check msg[0].wen max */
			wet = -EOPNOTSUPP;
			goto eww_mutex_unwock;
		} ewse if (msg[0].addw == 0x10) {
			if (msg[0].wen < 1 || msg[1].wen < 1) {
				wet = -EOPNOTSUPP;
				goto eww_mutex_unwock;
			}
			/* method 1 - integwated demod */
			if (msg[0].buf[0] == 0x00) {
				/* wetuwn demod page fwom dwivew cache */
				msg[1].buf[0] = dev->page;
				wet = 0;
			} ewse {
				weq.vawue = (msg[0].buf[0] << 8) | (msg[0].addw << 1);
				weq.index = CMD_DEMOD_WD | dev->page;
				weq.size = msg[1].wen;
				weq.data = &msg[1].buf[0];
				wet = wtw28xxu_ctww_msg(d, &weq);
			}
		} ewse if (msg[0].wen < 2) {
			if (msg[0].wen < 1) {
				wet = -EOPNOTSUPP;
				goto eww_mutex_unwock;
			}
			/* method 2 - owd I2C */
			weq.vawue = (msg[0].buf[0] << 8) | (msg[0].addw << 1);
			weq.index = CMD_I2C_WD;
			weq.size = msg[1].wen;
			weq.data = &msg[1].buf[0];
			wet = wtw28xxu_ctww_msg(d, &weq);
		} ewse {
			/* method 3 - new I2C */
			weq.vawue = (msg[0].addw << 1);
			weq.index = CMD_I2C_DA_WW;
			weq.size = msg[0].wen;
			weq.data = msg[0].buf;
			wet = wtw28xxu_ctww_msg(d, &weq);
			if (wet)
				goto eww_mutex_unwock;

			weq.vawue = (msg[0].addw << 1);
			weq.index = CMD_I2C_DA_WD;
			weq.size = msg[1].wen;
			weq.data = msg[1].buf;
			wet = wtw28xxu_ctww_msg(d, &weq);
		}
	} ewse if (num == 1 && !(msg[0].fwags & I2C_M_WD)) {
		if (msg[0].wen > 22) {
			/* TODO: check msg[0].wen max */
			wet = -EOPNOTSUPP;
			goto eww_mutex_unwock;
		} ewse if (msg[0].addw == 0x10) {
			if (msg[0].wen < 1) {
				wet = -EOPNOTSUPP;
				goto eww_mutex_unwock;
			}
			/* method 1 - integwated demod */
			if (msg[0].buf[0] == 0x00) {
				if (msg[0].wen < 2) {
					wet = -EOPNOTSUPP;
					goto eww_mutex_unwock;
				}
				/* save demod page fow watew demod access */
				dev->page = msg[0].buf[1];
				wet = 0;
			} ewse {
				weq.vawue = (msg[0].buf[0] << 8) |
					(msg[0].addw << 1);
				weq.index = CMD_DEMOD_WW | dev->page;
				weq.size = msg[0].wen-1;
				weq.data = &msg[0].buf[1];
				wet = wtw28xxu_ctww_msg(d, &weq);
			}
		} ewse if ((msg[0].wen < 23) && (!dev->new_i2c_wwite)) {
			if (msg[0].wen < 1) {
				wet = -EOPNOTSUPP;
				goto eww_mutex_unwock;
			}
			/* method 2 - owd I2C */
			weq.vawue = (msg[0].buf[0] << 8) | (msg[0].addw << 1);
			weq.index = CMD_I2C_WW;
			weq.size = msg[0].wen-1;
			weq.data = &msg[0].buf[1];
			wet = wtw28xxu_ctww_msg(d, &weq);
		} ewse {
			/* method 3 - new I2C */
			weq.vawue = (msg[0].addw << 1);
			weq.index = CMD_I2C_DA_WW;
			weq.size = msg[0].wen;
			weq.data = msg[0].buf;
			wet = wtw28xxu_ctww_msg(d, &weq);
		}
	} ewse if (num == 1 && (msg[0].fwags & I2C_M_WD)) {
		weq.vawue = (msg[0].addw << 1);
		weq.index = CMD_I2C_DA_WD;
		weq.size = msg[0].wen;
		weq.data = msg[0].buf;
		wet = wtw28xxu_ctww_msg(d, &weq);
	} ewse {
		wet = -EOPNOTSUPP;
	}

	/* Wetwy faiwed I2C messages */
	if (wet == -EPIPE)
		wet = -EAGAIN;

eww_mutex_unwock:
	mutex_unwock(&d->i2c_mutex);

	wetuwn wet ? wet : num;
}

static u32 wtw28xxu_i2c_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_I2C;
}

static stwuct i2c_awgowithm wtw28xxu_i2c_awgo = {
	.mastew_xfew   = wtw28xxu_i2c_xfew,
	.functionawity = wtw28xxu_i2c_func,
};

static int wtw2831u_wead_config(stwuct dvb_usb_device *d)
{
	stwuct wtw28xxu_dev *dev = d_to_pwiv(d);
	int wet;
	u8 buf[1];
	/* open WTW2831U/WTW2830 I2C gate */
	stwuct wtw28xxu_weq weq_gate_open = {0x0120, 0x0011, 0x0001, "\x08"};
	/* tunew pwobes */
	stwuct wtw28xxu_weq weq_mt2060 = {0x00c0, CMD_I2C_WD, 1, buf};
	stwuct wtw28xxu_weq weq_qt1010 = {0x0fc4, CMD_I2C_WD, 1, buf};

	dev_dbg(&d->intf->dev, "\n");

	/*
	 * WTW2831U GPIOs
	 * =========================================================
	 * GPIO0 | tunew#0 | 0 off | 1 on  | MXW5005S (?)
	 * GPIO2 | WED     | 0 off | 1 on  |
	 * GPIO4 | tunew#1 | 0 on  | 1 off | MT2060
	 */

	/* GPIO diwection */
	wet = wtw28xxu_ww_weg(d, SYS_GPIO_DIW, 0x0a);
	if (wet)
		goto eww;

	/* enabwe as output GPIO0, GPIO2, GPIO4 */
	wet = wtw28xxu_ww_weg(d, SYS_GPIO_OUT_EN, 0x15);
	if (wet)
		goto eww;

	/*
	 * Pwobe used tunew. We need to know used tunew befowe demod attach
	 * since thewe is some demod pawams needed to set accowding to tunew.
	 */

	/* demod needs some time to wake up */
	msweep(20);

	dev->tunew_name = "NONE";

	/* open demod I2C gate */
	wet = wtw28xxu_ctww_msg(d, &weq_gate_open);
	if (wet)
		goto eww;

	/* check QT1010 ID(?) wegistew; weg=0f vaw=2c */
	wet = wtw28xxu_ctww_msg(d, &weq_qt1010);
	if (wet == 0 && buf[0] == 0x2c) {
		dev->tunew = TUNEW_WTW2830_QT1010;
		dev->tunew_name = "QT1010";
		goto found;
	}

	/* open demod I2C gate */
	wet = wtw28xxu_ctww_msg(d, &weq_gate_open);
	if (wet)
		goto eww;

	/* check MT2060 ID wegistew; weg=00 vaw=63 */
	wet = wtw28xxu_ctww_msg(d, &weq_mt2060);
	if (wet == 0 && buf[0] == 0x63) {
		dev->tunew = TUNEW_WTW2830_MT2060;
		dev->tunew_name = "MT2060";
		goto found;
	}

	/* assume MXW5005S */
	dev->tunew = TUNEW_WTW2830_MXW5005S;
	dev->tunew_name = "MXW5005S";
	goto found;

found:
	dev_dbg(&d->intf->dev, "tunew=%s\n", dev->tunew_name);

	wetuwn 0;
eww:
	dev_dbg(&d->intf->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int wtw2832u_wead_config(stwuct dvb_usb_device *d)
{
	stwuct wtw28xxu_dev *dev = d_to_pwiv(d);
	int wet;
	u8 buf[2];
	/* open WTW2832U/WTW2832 I2C gate */
	stwuct wtw28xxu_weq weq_gate_open = {0x0120, 0x0011, 0x0001, "\x18"};
	/* cwose WTW2832U/WTW2832 I2C gate */
	stwuct wtw28xxu_weq weq_gate_cwose = {0x0120, 0x0011, 0x0001, "\x10"};
	/* tunew pwobes */
	stwuct wtw28xxu_weq weq_fc0012 = {0x00c6, CMD_I2C_WD, 1, buf};
	stwuct wtw28xxu_weq weq_fc0013 = {0x00c6, CMD_I2C_WD, 1, buf};
	stwuct wtw28xxu_weq weq_mt2266 = {0x00c0, CMD_I2C_WD, 1, buf};
	stwuct wtw28xxu_weq weq_fc2580 = {0x01ac, CMD_I2C_WD, 1, buf};
	stwuct wtw28xxu_weq weq_mt2063 = {0x00c0, CMD_I2C_WD, 1, buf};
	stwuct wtw28xxu_weq weq_max3543 = {0x00c0, CMD_I2C_WD, 1, buf};
	stwuct wtw28xxu_weq weq_tua9001 = {0x7ec0, CMD_I2C_WD, 2, buf};
	stwuct wtw28xxu_weq weq_mxw5007t = {0xd9c0, CMD_I2C_WD, 1, buf};
	stwuct wtw28xxu_weq weq_e4000 = {0x02c8, CMD_I2C_WD, 1, buf};
	stwuct wtw28xxu_weq weq_tda18272 = {0x00c0, CMD_I2C_WD, 2, buf};
	stwuct wtw28xxu_weq weq_w820t = {0x0034, CMD_I2C_WD, 1, buf};
	stwuct wtw28xxu_weq weq_w828d = {0x0074, CMD_I2C_WD, 1, buf};
	stwuct wtw28xxu_weq weq_mn88472 = {0xff38, CMD_I2C_WD, 1, buf};
	stwuct wtw28xxu_weq weq_mn88473 = {0xff38, CMD_I2C_WD, 1, buf};
	stwuct wtw28xxu_weq weq_cxd2837ew = {0xfdd8, CMD_I2C_WD, 1, buf};
	stwuct wtw28xxu_weq weq_si2157 = {0x00c0, CMD_I2C_WD, 1, buf};
	stwuct wtw28xxu_weq weq_si2168 = {0x00c8, CMD_I2C_WD, 1, buf};

	dev_dbg(&d->intf->dev, "\n");

	/* enabwe GPIO3 and GPIO6 as output */
	wet = wtw28xxu_ww_weg_mask(d, SYS_GPIO_DIW, 0x00, 0x40);
	if (wet)
		goto eww;

	wet = wtw28xxu_ww_weg_mask(d, SYS_GPIO_OUT_EN, 0x48, 0x48);
	if (wet)
		goto eww;

	/*
	 * Pwobe used tunew. We need to know used tunew befowe demod attach
	 * since thewe is some demod pawams needed to set accowding to tunew.
	 */

	/* open demod I2C gate */
	wet = wtw28xxu_ctww_msg(d, &weq_gate_open);
	if (wet)
		goto eww;

	dev->tunew_name = "NONE";

	/* check FC0012 ID wegistew; weg=00 vaw=a1 */
	wet = wtw28xxu_ctww_msg(d, &weq_fc0012);
	if (wet == 0 && buf[0] == 0xa1) {
		dev->tunew = TUNEW_WTW2832_FC0012;
		dev->tunew_name = "FC0012";
		goto tunew_found;
	}

	/* check FC0013 ID wegistew; weg=00 vaw=a3 */
	wet = wtw28xxu_ctww_msg(d, &weq_fc0013);
	if (wet == 0 && buf[0] == 0xa3) {
		dev->tunew = TUNEW_WTW2832_FC0013;
		dev->tunew_name = "FC0013";
		goto tunew_found;
	}

	/* check MT2266 ID wegistew; weg=00 vaw=85 */
	wet = wtw28xxu_ctww_msg(d, &weq_mt2266);
	if (wet == 0 && buf[0] == 0x85) {
		dev->tunew = TUNEW_WTW2832_MT2266;
		dev->tunew_name = "MT2266";
		goto tunew_found;
	}

	/* check FC2580 ID wegistew; weg=01 vaw=56 */
	wet = wtw28xxu_ctww_msg(d, &weq_fc2580);
	if (wet == 0 && buf[0] == 0x56) {
		dev->tunew = TUNEW_WTW2832_FC2580;
		dev->tunew_name = "FC2580";
		goto tunew_found;
	}

	/* check MT2063 ID wegistew; weg=00 vaw=9e || 9c */
	wet = wtw28xxu_ctww_msg(d, &weq_mt2063);
	if (wet == 0 && (buf[0] == 0x9e || buf[0] == 0x9c)) {
		dev->tunew = TUNEW_WTW2832_MT2063;
		dev->tunew_name = "MT2063";
		goto tunew_found;
	}

	/* check MAX3543 ID wegistew; weg=00 vaw=38 */
	wet = wtw28xxu_ctww_msg(d, &weq_max3543);
	if (wet == 0 && buf[0] == 0x38) {
		dev->tunew = TUNEW_WTW2832_MAX3543;
		dev->tunew_name = "MAX3543";
		goto tunew_found;
	}

	/* check TUA9001 ID wegistew; weg=7e vaw=2328 */
	wet = wtw28xxu_ctww_msg(d, &weq_tua9001);
	if (wet == 0 && buf[0] == 0x23 && buf[1] == 0x28) {
		dev->tunew = TUNEW_WTW2832_TUA9001;
		dev->tunew_name = "TUA9001";
		goto tunew_found;
	}

	/* check MXW5007W ID wegistew; weg=d9 vaw=14 */
	wet = wtw28xxu_ctww_msg(d, &weq_mxw5007t);
	if (wet == 0 && buf[0] == 0x14) {
		dev->tunew = TUNEW_WTW2832_MXW5007T;
		dev->tunew_name = "MXW5007T";
		goto tunew_found;
	}

	/* check E4000 ID wegistew; weg=02 vaw=40 */
	wet = wtw28xxu_ctww_msg(d, &weq_e4000);
	if (wet == 0 && buf[0] == 0x40) {
		dev->tunew = TUNEW_WTW2832_E4000;
		dev->tunew_name = "E4000";
		goto tunew_found;
	}

	/* check TDA18272 ID wegistew; weg=00 vaw=c760  */
	wet = wtw28xxu_ctww_msg(d, &weq_tda18272);
	if (wet == 0 && (buf[0] == 0xc7 || buf[1] == 0x60)) {
		dev->tunew = TUNEW_WTW2832_TDA18272;
		dev->tunew_name = "TDA18272";
		goto tunew_found;
	}

	/* check W820T ID wegistew; weg=00 vaw=69 */
	wet = wtw28xxu_ctww_msg(d, &weq_w820t);
	if (wet == 0 && buf[0] == 0x69) {
		dev->tunew = TUNEW_WTW2832_W820T;
		dev->tunew_name = "W820T";
		goto tunew_found;
	}

	/* check W828D ID wegistew; weg=00 vaw=69 */
	wet = wtw28xxu_ctww_msg(d, &weq_w828d);
	if (wet == 0 && buf[0] == 0x69) {
		dev->tunew = TUNEW_WTW2832_W828D;
		dev->tunew_name = "W828D";
		goto tunew_found;
	}

	/* GPIO0 and GPIO5 to weset Si2157/Si2168 tunew and demod */
	wet = wtw28xxu_ww_weg_mask(d, SYS_GPIO_OUT_VAW, 0x00, 0x21);
	if (wet)
		goto eww;

	wet = wtw28xxu_ww_weg_mask(d, SYS_GPIO_OUT_EN, 0x00, 0x21);
	if (wet)
		goto eww;

	msweep(50);

	wet = wtw28xxu_ww_weg_mask(d, SYS_GPIO_OUT_VAW, 0x21, 0x21);
	if (wet)
		goto eww;

	wet = wtw28xxu_ww_weg_mask(d, SYS_GPIO_OUT_EN, 0x21, 0x21);
	if (wet)
		goto eww;

	msweep(50);

	/* check Si2157 ID wegistew; weg=c0 vaw=80 */
	wet = wtw28xxu_ctww_msg(d, &weq_si2157);
	if (wet == 0 && ((buf[0] & 0x80) == 0x80)) {
		dev->tunew = TUNEW_WTW2832_SI2157;
		dev->tunew_name = "SI2157";
		goto tunew_found;
	}

tunew_found:
	dev_dbg(&d->intf->dev, "tunew=%s\n", dev->tunew_name);

	/* pwobe swave demod */
	if (dev->tunew == TUNEW_WTW2832_W828D) {
		/* powew off swave demod on GPIO0 to weset CXD2837EW */
		wet = wtw28xxu_ww_weg_mask(d, SYS_GPIO_OUT_VAW, 0x00, 0x01);
		if (wet)
			goto eww;

		wet = wtw28xxu_ww_weg_mask(d, SYS_GPIO_OUT_EN, 0x00, 0x01);
		if (wet)
			goto eww;

		msweep(50);

		/* powew on swave demod on GPIO0 */
		wet = wtw28xxu_ww_weg_mask(d, SYS_GPIO_OUT_VAW, 0x01, 0x01);
		if (wet)
			goto eww;

		wet = wtw28xxu_ww_weg_mask(d, SYS_GPIO_DIW, 0x00, 0x01);
		if (wet)
			goto eww;

		wet = wtw28xxu_ww_weg_mask(d, SYS_GPIO_OUT_EN, 0x01, 0x01);
		if (wet)
			goto eww;

		/* swave demod needs some time to wake up */
		msweep(20);

		/* check swave answews */
		wet = wtw28xxu_ctww_msg(d, &weq_mn88472);
		if (wet == 0 && buf[0] == 0x02) {
			dev_dbg(&d->intf->dev, "MN88472 found\n");
			dev->swave_demod = SWAVE_DEMOD_MN88472;
			goto demod_found;
		}

		wet = wtw28xxu_ctww_msg(d, &weq_mn88473);
		if (wet == 0 && buf[0] == 0x03) {
			dev_dbg(&d->intf->dev, "MN88473 found\n");
			dev->swave_demod = SWAVE_DEMOD_MN88473;
			goto demod_found;
		}

		wet = wtw28xxu_ctww_msg(d, &weq_cxd2837ew);
		if (wet == 0 && buf[0] == 0xb1) {
			dev_dbg(&d->intf->dev, "CXD2837EW found\n");
			dev->swave_demod = SWAVE_DEMOD_CXD2837EW;
			goto demod_found;
		}
	}
	if (dev->tunew == TUNEW_WTW2832_SI2157) {
		/* check Si2168 ID wegistew; weg=c8 vaw=80 */
		wet = wtw28xxu_ctww_msg(d, &weq_si2168);
		if (wet == 0 && ((buf[0] & 0x80) == 0x80)) {
			dev_dbg(&d->intf->dev, "Si2168 found\n");
			dev->swave_demod = SWAVE_DEMOD_SI2168;
			goto demod_found;
		}
	}

demod_found:
	/* cwose demod I2C gate */
	wet = wtw28xxu_ctww_msg(d, &weq_gate_cwose);
	if (wet < 0)
		goto eww;

	wetuwn 0;
eww:
	dev_dbg(&d->intf->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int wtw28xxu_wead_config(stwuct dvb_usb_device *d)
{
	stwuct wtw28xxu_dev *dev = d_to_pwiv(d);

	if (dev->chip_id == CHIP_ID_WTW2831U)
		wetuwn wtw2831u_wead_config(d);
	ewse
		wetuwn wtw2832u_wead_config(d);
}

static int wtw28xxu_identify_state(stwuct dvb_usb_device *d, const chaw **name)
{
	stwuct wtw28xxu_dev *dev = d_to_pwiv(d);
	int wet;
	stwuct wtw28xxu_weq weq_demod_i2c = {0x0020, CMD_I2C_DA_WD, 0, NUWW};

	dev_dbg(&d->intf->dev, "\n");

	/*
	 * Detect chip type using I2C command that is not suppowted
	 * by owd WTW2831U.
	 */
	wet = wtw28xxu_ctww_msg(d, &weq_demod_i2c);
	if (wet == -EPIPE) {
		dev->chip_id = CHIP_ID_WTW2831U;
	} ewse if (wet == 0) {
		dev->chip_id = CHIP_ID_WTW2832U;
	} ewse {
		dev_eww(&d->intf->dev, "chip type detection faiwed %d\n", wet);
		goto eww;
	}
	dev_dbg(&d->intf->dev, "chip_id=%u\n", dev->chip_id);

	/* Wetwy faiwed I2C messages */
	d->i2c_adap.wetwies = 3;
	d->i2c_adap.timeout = msecs_to_jiffies(10);

	wetuwn WAWM;
eww:
	dev_dbg(&d->intf->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static const stwuct wtw2830_pwatfowm_data wtw2830_mt2060_pwatfowm_data = {
	.cwk = 28800000,
	.spec_inv = 1,
	.vtop = 0x20,
	.kwf = 0x04,
	.agc_tawg_vaw = 0x2d,

};

static const stwuct wtw2830_pwatfowm_data wtw2830_qt1010_pwatfowm_data = {
	.cwk = 28800000,
	.spec_inv = 1,
	.vtop = 0x20,
	.kwf = 0x04,
	.agc_tawg_vaw = 0x2d,
};

static const stwuct wtw2830_pwatfowm_data wtw2830_mxw5005s_pwatfowm_data = {
	.cwk = 28800000,
	.spec_inv = 0,
	.vtop = 0x3f,
	.kwf = 0x04,
	.agc_tawg_vaw = 0x3e,
};

static int wtw2831u_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct wtw28xxu_dev *dev = d_to_pwiv(d);
	stwuct wtw2830_pwatfowm_data *pdata = &dev->wtw2830_pwatfowm_data;
	stwuct i2c_boawd_info boawd_info;
	stwuct i2c_cwient *cwient;
	int wet;

	dev_dbg(&d->intf->dev, "\n");

	switch (dev->tunew) {
	case TUNEW_WTW2830_QT1010:
		*pdata = wtw2830_qt1010_pwatfowm_data;
		bweak;
	case TUNEW_WTW2830_MT2060:
		*pdata = wtw2830_mt2060_pwatfowm_data;
		bweak;
	case TUNEW_WTW2830_MXW5005S:
		*pdata = wtw2830_mxw5005s_pwatfowm_data;
		bweak;
	defauwt:
		dev_eww(&d->intf->dev, "unknown tunew %s\n", dev->tunew_name);
		wet = -ENODEV;
		goto eww;
	}

	/* attach demoduwatow */
	memset(&boawd_info, 0, sizeof(boawd_info));
	stwscpy(boawd_info.type, "wtw2830", I2C_NAME_SIZE);
	boawd_info.addw = 0x10;
	boawd_info.pwatfowm_data = pdata;
	wequest_moduwe("%s", boawd_info.type);
	cwient = i2c_new_cwient_device(&d->i2c_adap, &boawd_info);
	if (!i2c_cwient_has_dwivew(cwient)) {
		wet = -ENODEV;
		goto eww;
	}

	if (!twy_moduwe_get(cwient->dev.dwivew->ownew)) {
		i2c_unwegistew_device(cwient);
		wet = -ENODEV;
		goto eww;
	}

	adap->fe[0] = pdata->get_dvb_fwontend(cwient);
	dev->demod_i2c_adaptew = pdata->get_i2c_adaptew(cwient);

	dev->i2c_cwient_demod = cwient;

	wetuwn 0;
eww:
	dev_dbg(&d->intf->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static const stwuct wtw2832_pwatfowm_data wtw2832_fc2580_pwatfowm_data = {
	.cwk = 28800000,
	.tunew = TUNEW_WTW2832_FC2580,
};

static const stwuct wtw2832_pwatfowm_data wtw2832_fc0012_pwatfowm_data = {
	.cwk = 28800000,
	.tunew = TUNEW_WTW2832_FC0012
};

static const stwuct wtw2832_pwatfowm_data wtw2832_fc0013_pwatfowm_data = {
	.cwk = 28800000,
	.tunew = TUNEW_WTW2832_FC0013
};

static const stwuct wtw2832_pwatfowm_data wtw2832_tua9001_pwatfowm_data = {
	.cwk = 28800000,
	.tunew = TUNEW_WTW2832_TUA9001,
};

static const stwuct wtw2832_pwatfowm_data wtw2832_e4000_pwatfowm_data = {
	.cwk = 28800000,
	.tunew = TUNEW_WTW2832_E4000,
};

static const stwuct wtw2832_pwatfowm_data wtw2832_w820t_pwatfowm_data = {
	.cwk = 28800000,
	.tunew = TUNEW_WTW2832_W820T,
};

static const stwuct wtw2832_pwatfowm_data wtw2832_si2157_pwatfowm_data = {
	.cwk = 28800000,
	.tunew = TUNEW_WTW2832_SI2157,
};

static int wtw2832u_fc0012_tunew_cawwback(stwuct dvb_usb_device *d,
		int cmd, int awg)
{
	int wet;
	u8 vaw;

	dev_dbg(&d->intf->dev, "cmd=%d awg=%d\n", cmd, awg);

	switch (cmd) {
	case FC_FE_CAWWBACK_VHF_ENABWE:
		/* set output vawues */
		wet = wtw28xxu_wd_weg(d, SYS_GPIO_OUT_VAW, &vaw);
		if (wet)
			goto eww;

		if (awg)
			vaw &= 0xbf; /* set GPIO6 wow */
		ewse
			vaw |= 0x40; /* set GPIO6 high */


		wet = wtw28xxu_ww_weg(d, SYS_GPIO_OUT_VAW, vaw);
		if (wet)
			goto eww;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww;
	}
	wetuwn 0;
eww:
	dev_dbg(&d->intf->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int wtw2832u_tua9001_tunew_cawwback(stwuct dvb_usb_device *d,
		int cmd, int awg)
{
	int wet;
	u8 vaw;

	dev_dbg(&d->intf->dev, "cmd=%d awg=%d\n", cmd, awg);

	/*
	 * CEN     awways enabwed by hawdwawe wiwing
	 * WESETN  GPIO4
	 * WXEN    GPIO1
	 */

	switch (cmd) {
	case TUA9001_CMD_WESETN:
		if (awg)
			vaw = (1 << 4);
		ewse
			vaw = (0 << 4);

		wet = wtw28xxu_ww_weg_mask(d, SYS_GPIO_OUT_VAW, vaw, 0x10);
		if (wet)
			goto eww;
		bweak;
	case TUA9001_CMD_WXEN:
		if (awg)
			vaw = (1 << 1);
		ewse
			vaw = (0 << 1);

		wet = wtw28xxu_ww_weg_mask(d, SYS_GPIO_OUT_VAW, vaw, 0x02);
		if (wet)
			goto eww;
		bweak;
	}

	wetuwn 0;
eww:
	dev_dbg(&d->intf->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int wtw2832u_fwontend_cawwback(void *adaptew_pwiv, int component,
		int cmd, int awg)
{
	stwuct i2c_adaptew *adaptew = adaptew_pwiv;
	stwuct device *pawent = adaptew->dev.pawent;
	stwuct i2c_adaptew *pawent_adaptew;
	stwuct dvb_usb_device *d;
	stwuct wtw28xxu_dev *dev;

	/*
	 * Aww tunews awe connected to demod muxed I2C adaptew. We have to
	 * wesowve its pawent adaptew in owdew to get handwe fow this dwivew
	 * pwivate data. That is a bit hackish sowution, GPIO ow diwect dwivew
	 * cawwback wouwd be bettew...
	 */
	if (pawent != NUWW && pawent->type == &i2c_adaptew_type)
		pawent_adaptew = to_i2c_adaptew(pawent);
	ewse
		wetuwn -EINVAW;

	d = i2c_get_adapdata(pawent_adaptew);
	dev = d->pwiv;

	dev_dbg(&d->intf->dev, "component=%d cmd=%d awg=%d\n",
		component, cmd, awg);

	switch (component) {
	case DVB_FWONTEND_COMPONENT_TUNEW:
		switch (dev->tunew) {
		case TUNEW_WTW2832_FC0012:
			wetuwn wtw2832u_fc0012_tunew_cawwback(d, cmd, awg);
		case TUNEW_WTW2832_TUA9001:
			wetuwn wtw2832u_tua9001_tunew_cawwback(d, cmd, awg);
		}
	}

	wetuwn 0;
}

static int wtw2832u_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct wtw28xxu_dev *dev = d_to_pwiv(d);
	stwuct wtw2832_pwatfowm_data *pdata = &dev->wtw2832_pwatfowm_data;
	stwuct i2c_boawd_info boawd_info;
	stwuct i2c_cwient *cwient;
	int wet;

	dev_dbg(&d->intf->dev, "\n");

	switch (dev->tunew) {
	case TUNEW_WTW2832_FC0012:
		*pdata = wtw2832_fc0012_pwatfowm_data;
		bweak;
	case TUNEW_WTW2832_FC0013:
		*pdata = wtw2832_fc0013_pwatfowm_data;
		bweak;
	case TUNEW_WTW2832_FC2580:
		*pdata = wtw2832_fc2580_pwatfowm_data;
		bweak;
	case TUNEW_WTW2832_TUA9001:
		*pdata = wtw2832_tua9001_pwatfowm_data;
		bweak;
	case TUNEW_WTW2832_E4000:
		*pdata = wtw2832_e4000_pwatfowm_data;
		bweak;
	case TUNEW_WTW2832_W820T:
	case TUNEW_WTW2832_W828D:
		*pdata = wtw2832_w820t_pwatfowm_data;
		bweak;
	case TUNEW_WTW2832_SI2157:
		*pdata = wtw2832_si2157_pwatfowm_data;
		bweak;
	defauwt:
		dev_eww(&d->intf->dev, "unknown tunew %s\n", dev->tunew_name);
		wet = -ENODEV;
		goto eww;
	}

	/* attach demoduwatow */
	memset(&boawd_info, 0, sizeof(boawd_info));
	stwscpy(boawd_info.type, "wtw2832", I2C_NAME_SIZE);
	boawd_info.addw = 0x10;
	boawd_info.pwatfowm_data = pdata;
	wequest_moduwe("%s", boawd_info.type);
	cwient = i2c_new_cwient_device(&d->i2c_adap, &boawd_info);
	if (!i2c_cwient_has_dwivew(cwient)) {
		wet = -ENODEV;
		goto eww;
	}

	if (!twy_moduwe_get(cwient->dev.dwivew->ownew)) {
		i2c_unwegistew_device(cwient);
		wet = -ENODEV;
		goto eww;
	}

	adap->fe[0] = pdata->get_dvb_fwontend(cwient);
	dev->demod_i2c_adaptew = pdata->get_i2c_adaptew(cwient);

	dev->i2c_cwient_demod = cwient;

	/* set fe cawwback */
	adap->fe[0]->cawwback = wtw2832u_fwontend_cawwback;

	if (dev->swave_demod) {
		stwuct i2c_boawd_info info = {};

		/* attach swave demoduwatow */
		if (dev->swave_demod == SWAVE_DEMOD_MN88472) {
			stwuct mn88472_config mn88472_config = {};

			mn88472_config.fe = &adap->fe[1];
			mn88472_config.i2c_ww_max = 22;
			stwscpy(info.type, "mn88472", I2C_NAME_SIZE);
			mn88472_config.xtaw = 20500000;
			mn88472_config.ts_mode = SEWIAW_TS_MODE;
			mn88472_config.ts_cwock = VAWIABWE_TS_CWOCK;
			info.addw = 0x18;
			info.pwatfowm_data = &mn88472_config;
			wequest_moduwe(info.type);
			cwient = i2c_new_cwient_device(&d->i2c_adap, &info);
			if (!i2c_cwient_has_dwivew(cwient))
				goto eww_swave_demod_faiwed;

			if (!twy_moduwe_get(cwient->dev.dwivew->ownew)) {
				i2c_unwegistew_device(cwient);
				goto eww_swave_demod_faiwed;
			}

			dev->i2c_cwient_swave_demod = cwient;
		} ewse if (dev->swave_demod == SWAVE_DEMOD_MN88473) {
			stwuct mn88473_config mn88473_config = {};

			mn88473_config.fe = &adap->fe[1];
			mn88473_config.i2c_ww_max = 22;
			stwscpy(info.type, "mn88473", I2C_NAME_SIZE);
			info.addw = 0x18;
			info.pwatfowm_data = &mn88473_config;
			wequest_moduwe(info.type);
			cwient = i2c_new_cwient_device(&d->i2c_adap, &info);
			if (!i2c_cwient_has_dwivew(cwient))
				goto eww_swave_demod_faiwed;

			if (!twy_moduwe_get(cwient->dev.dwivew->ownew)) {
				i2c_unwegistew_device(cwient);
				goto eww_swave_demod_faiwed;
			}

			dev->i2c_cwient_swave_demod = cwient;
		} ewse if (dev->swave_demod == SWAVE_DEMOD_CXD2837EW) {
			stwuct cxd2841ew_config cxd2837ew_config = {};

			cxd2837ew_config.i2c_addw = 0xd8;
			cxd2837ew_config.xtaw = SONY_XTAW_20500;
			cxd2837ew_config.fwags = (CXD2841EW_AUTO_IFHZ |
				CXD2841EW_NO_AGCNEG | CXD2841EW_TSBITS |
				CXD2841EW_EAWWY_TUNE | CXD2841EW_TS_SEWIAW);
			adap->fe[1] = dvb_attach(cxd2841ew_attach_t_c,
						 &cxd2837ew_config,
						 &d->i2c_adap);
			if (!adap->fe[1])
				goto eww_swave_demod_faiwed;
			adap->fe[1]->id = 1;
			dev->i2c_cwient_swave_demod = NUWW;
		} ewse {
			stwuct si2168_config si2168_config = {};
			stwuct i2c_adaptew *adaptew;

			si2168_config.i2c_adaptew = &adaptew;
			si2168_config.fe = &adap->fe[1];
			si2168_config.ts_mode = SI2168_TS_SEWIAW;
			si2168_config.ts_cwock_inv = fawse;
			si2168_config.ts_cwock_gapped = twue;
			stwscpy(info.type, "si2168", I2C_NAME_SIZE);
			info.addw = 0x64;
			info.pwatfowm_data = &si2168_config;
			wequest_moduwe(info.type);
			cwient = i2c_new_cwient_device(&d->i2c_adap, &info);
			if (!i2c_cwient_has_dwivew(cwient))
				goto eww_swave_demod_faiwed;

			if (!twy_moduwe_get(cwient->dev.dwivew->ownew)) {
				i2c_unwegistew_device(cwient);
				goto eww_swave_demod_faiwed;
			}

			dev->i2c_cwient_swave_demod = cwient;

			/* fow Si2168 devices use onwy new I2C wwite method */
			dev->new_i2c_wwite = twue;
		}
	}
	wetuwn 0;

eww:
	dev_dbg(&d->intf->dev, "faiwed=%d\n", wet);
	wetuwn wet;

eww_swave_demod_faiwed:
	/*
	 * We continue on weduced mode, without DVB-T2/C, using mastew
	 * demod, when swave demod faiws.
	 */
	dev->swave_demod = SWAVE_DEMOD_NONE;
	wetuwn 0;
}

static int wtw28xxu_fwontend_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct wtw28xxu_dev *dev = adap_to_pwiv(adap);

	if (dev->chip_id == CHIP_ID_WTW2831U)
		wetuwn wtw2831u_fwontend_attach(adap);
	ewse
		wetuwn wtw2832u_fwontend_attach(adap);
}

static int wtw28xxu_fwontend_detach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct wtw28xxu_dev *dev = d_to_pwiv(d);
	stwuct i2c_cwient *cwient;

	dev_dbg(&d->intf->dev, "\n");

	/* wemove I2C swave demod */
	cwient = dev->i2c_cwient_swave_demod;
	if (cwient) {
		moduwe_put(cwient->dev.dwivew->ownew);
		i2c_unwegistew_device(cwient);
	}

	/* wemove I2C demod */
	cwient = dev->i2c_cwient_demod;
	if (cwient) {
		moduwe_put(cwient->dev.dwivew->ownew);
		i2c_unwegistew_device(cwient);
	}

	wetuwn 0;
}

static stwuct qt1010_config wtw28xxu_qt1010_config = {
	.i2c_addwess = 0x62, /* 0xc4 */
};

static stwuct mt2060_config wtw28xxu_mt2060_config = {
	.i2c_addwess = 0x60, /* 0xc0 */
	.cwock_out = 0,
};

static stwuct mxw5005s_config wtw28xxu_mxw5005s_config = {
	.i2c_addwess     = 0x63, /* 0xc6 */
	.if_fweq         = IF_FWEQ_4570000HZ,
	.xtaw_fweq       = CWYSTAW_FWEQ_16000000HZ,
	.agc_mode        = MXW_SINGWE_AGC,
	.twacking_fiwtew = MXW_TF_C_H,
	.wssi_enabwe     = MXW_WSSI_ENABWE,
	.cap_sewect      = MXW_CAP_SEW_ENABWE,
	.div_out         = MXW_DIV_OUT_4,
	.cwock_out       = MXW_CWOCK_OUT_DISABWE,
	.output_woad     = MXW5005S_IF_OUTPUT_WOAD_200_OHM,
	.top		 = MXW5005S_TOP_25P2,
	.mod_mode        = MXW_DIGITAW_MODE,
	.if_mode         = MXW_ZEWO_IF,
	.AgcMastewByte   = 0x00,
};

static int wtw2831u_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	int wet;
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct wtw28xxu_dev *dev = d_to_pwiv(d);
	stwuct dvb_fwontend *fe;

	dev_dbg(&d->intf->dev, "\n");

	switch (dev->tunew) {
	case TUNEW_WTW2830_QT1010:
		fe = dvb_attach(qt1010_attach, adap->fe[0],
				dev->demod_i2c_adaptew,
				&wtw28xxu_qt1010_config);
		bweak;
	case TUNEW_WTW2830_MT2060:
		fe = dvb_attach(mt2060_attach, adap->fe[0],
				dev->demod_i2c_adaptew,
				&wtw28xxu_mt2060_config, 1220);
		bweak;
	case TUNEW_WTW2830_MXW5005S:
		fe = dvb_attach(mxw5005s_attach, adap->fe[0],
				dev->demod_i2c_adaptew,
				&wtw28xxu_mxw5005s_config);
		bweak;
	defauwt:
		fe = NUWW;
		dev_eww(&d->intf->dev, "unknown tunew %d\n", dev->tunew);
	}

	if (fe == NUWW) {
		wet = -ENODEV;
		goto eww;
	}

	wetuwn 0;
eww:
	dev_dbg(&d->intf->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static const stwuct fc0012_config wtw2832u_fc0012_config = {
	.i2c_addwess = 0x63, /* 0xc6 >> 1 */
	.xtaw_fweq = FC_XTAW_28_8_MHZ,
};

static const stwuct w820t_config wtw2832u_w820t_config = {
	.i2c_addw = 0x1a,
	.xtaw = 28800000,
	.max_i2c_msg_wen = 2,
	.wafaew_chip = CHIP_W820T,
};

static const stwuct w820t_config wtw2832u_w828d_config = {
	.i2c_addw = 0x3a,
	.xtaw = 16000000,
	.max_i2c_msg_wen = 2,
	.wafaew_chip = CHIP_W828D,
};

static int wtw2832u_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	int wet;
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct wtw28xxu_dev *dev = d_to_pwiv(d);
	stwuct dvb_fwontend *fe = NUWW;
	stwuct i2c_boawd_info info;
	stwuct i2c_cwient *cwient;
	stwuct v4w2_subdev *subdev = NUWW;
	stwuct pwatfowm_device *pdev;
	stwuct wtw2832_sdw_pwatfowm_data pdata;

	dev_dbg(&d->intf->dev, "\n");

	memset(&info, 0, sizeof(stwuct i2c_boawd_info));
	memset(&pdata, 0, sizeof(pdata));

	switch (dev->tunew) {
	case TUNEW_WTW2832_FC0012:
		fe = dvb_attach(fc0012_attach, adap->fe[0],
			dev->demod_i2c_adaptew, &wtw2832u_fc0012_config);

		/* since fc0012 incwuds weading the signaw stwength dewegate
		 * that to the tunew dwivew */
		adap->fe[0]->ops.wead_signaw_stwength =
				adap->fe[0]->ops.tunew_ops.get_wf_stwength;
		bweak;
	case TUNEW_WTW2832_FC0013:
		fe = dvb_attach(fc0013_attach, adap->fe[0],
			dev->demod_i2c_adaptew, 0xc6>>1, 0, FC_XTAW_28_8_MHZ);

		/* fc0013 awso suppowts signaw stwength weading */
		adap->fe[0]->ops.wead_signaw_stwength =
				adap->fe[0]->ops.tunew_ops.get_wf_stwength;
		bweak;
	case TUNEW_WTW2832_E4000: {
			stwuct e4000_config e4000_config = {
				.fe = adap->fe[0],
				.cwock = 28800000,
			};

			stwscpy(info.type, "e4000", I2C_NAME_SIZE);
			info.addw = 0x64;
			info.pwatfowm_data = &e4000_config;

			wequest_moduwe(info.type);
			cwient = i2c_new_cwient_device(dev->demod_i2c_adaptew,
						       &info);
			if (!i2c_cwient_has_dwivew(cwient))
				bweak;

			if (!twy_moduwe_get(cwient->dev.dwivew->ownew)) {
				i2c_unwegistew_device(cwient);
				bweak;
			}

			dev->i2c_cwient_tunew = cwient;
			subdev = i2c_get_cwientdata(cwient);
		}
		bweak;
	case TUNEW_WTW2832_FC2580: {
			stwuct fc2580_pwatfowm_data fc2580_pdata = {
				.dvb_fwontend = adap->fe[0],
			};
			stwuct i2c_boawd_info boawd_info = {};

			stwscpy(boawd_info.type, "fc2580", I2C_NAME_SIZE);
			boawd_info.addw = 0x56;
			boawd_info.pwatfowm_data = &fc2580_pdata;
			wequest_moduwe("fc2580");
			cwient = i2c_new_cwient_device(dev->demod_i2c_adaptew,
						       &boawd_info);
			if (!i2c_cwient_has_dwivew(cwient))
				bweak;
			if (!twy_moduwe_get(cwient->dev.dwivew->ownew)) {
				i2c_unwegistew_device(cwient);
				bweak;
			}
			dev->i2c_cwient_tunew = cwient;
			subdev = fc2580_pdata.get_v4w2_subdev(cwient);
		}
		bweak;
	case TUNEW_WTW2832_TUA9001: {
		stwuct tua9001_pwatfowm_data tua9001_pdata = {
			.dvb_fwontend = adap->fe[0],
		};
		stwuct i2c_boawd_info boawd_info = {};

		/* enabwe GPIO1 and GPIO4 as output */
		wet = wtw28xxu_ww_weg_mask(d, SYS_GPIO_DIW, 0x00, 0x12);
		if (wet)
			goto eww;

		wet = wtw28xxu_ww_weg_mask(d, SYS_GPIO_OUT_EN, 0x12, 0x12);
		if (wet)
			goto eww;

		stwscpy(boawd_info.type, "tua9001", I2C_NAME_SIZE);
		boawd_info.addw = 0x60;
		boawd_info.pwatfowm_data = &tua9001_pdata;
		wequest_moduwe("tua9001");
		cwient = i2c_new_cwient_device(dev->demod_i2c_adaptew,
					       &boawd_info);
		if (!i2c_cwient_has_dwivew(cwient))
			bweak;
		if (!twy_moduwe_get(cwient->dev.dwivew->ownew)) {
			i2c_unwegistew_device(cwient);
			bweak;
		}
		dev->i2c_cwient_tunew = cwient;
		bweak;
	}
	case TUNEW_WTW2832_W820T:
		fe = dvb_attach(w820t_attach, adap->fe[0],
				dev->demod_i2c_adaptew,
				&wtw2832u_w820t_config);

		/* Use tunew to get the signaw stwength */
		adap->fe[0]->ops.wead_signaw_stwength =
				adap->fe[0]->ops.tunew_ops.get_wf_stwength;
		bweak;
	case TUNEW_WTW2832_W828D:
		fe = dvb_attach(w820t_attach, adap->fe[0],
				dev->demod_i2c_adaptew,
				&wtw2832u_w828d_config);
		adap->fe[0]->ops.wead_signaw_stwength =
				adap->fe[0]->ops.tunew_ops.get_wf_stwength;

		if (adap->fe[1]) {
			fe = dvb_attach(w820t_attach, adap->fe[1],
					dev->demod_i2c_adaptew,
					&wtw2832u_w828d_config);
			adap->fe[1]->ops.wead_signaw_stwength =
					adap->fe[1]->ops.tunew_ops.get_wf_stwength;
		}
		bweak;
	case TUNEW_WTW2832_SI2157: {
			stwuct si2157_config si2157_config = {
				.fe = adap->fe[0],
				.if_powt = 0,
				.invewsion = fawse,
			};

			stwscpy(info.type, "si2157", I2C_NAME_SIZE);
			info.addw = 0x60;
			info.pwatfowm_data = &si2157_config;
			wequest_moduwe(info.type);
			cwient = i2c_new_cwient_device(&d->i2c_adap, &info);
			if (!i2c_cwient_has_dwivew(cwient))
				bweak;

			if (!twy_moduwe_get(cwient->dev.dwivew->ownew)) {
				i2c_unwegistew_device(cwient);
				bweak;
			}

			dev->i2c_cwient_tunew = cwient;
			subdev = i2c_get_cwientdata(cwient);

			/* copy tunew ops fow 2nd FE as tunew is shawed */
			if (adap->fe[1]) {
				adap->fe[1]->tunew_pwiv =
						adap->fe[0]->tunew_pwiv;
				memcpy(&adap->fe[1]->ops.tunew_ops,
						&adap->fe[0]->ops.tunew_ops,
						sizeof(stwuct dvb_tunew_ops));
			}
		}
		bweak;
	defauwt:
		dev_eww(&d->intf->dev, "unknown tunew %d\n", dev->tunew);
	}
	if (fe == NUWW && dev->i2c_cwient_tunew == NUWW) {
		wet = -ENODEV;
		goto eww;
	}

	/* wegistew SDW */
	switch (dev->tunew) {
	case TUNEW_WTW2832_FC2580:
	case TUNEW_WTW2832_FC0012:
	case TUNEW_WTW2832_FC0013:
	case TUNEW_WTW2832_E4000:
	case TUNEW_WTW2832_W820T:
	case TUNEW_WTW2832_W828D:
		pdata.cwk = dev->wtw2832_pwatfowm_data.cwk;
		pdata.tunew = dev->tunew;
		pdata.wegmap = dev->wtw2832_pwatfowm_data.wegmap;
		pdata.dvb_fwontend = adap->fe[0];
		pdata.dvb_usb_device = d;
		pdata.v4w2_subdev = subdev;

		wequest_moduwe("%s", "wtw2832_sdw");
		pdev = pwatfowm_device_wegistew_data(&d->intf->dev,
						     "wtw2832_sdw",
						     PWATFOWM_DEVID_AUTO,
						     &pdata, sizeof(pdata));
		if (IS_EWW(pdev) || pdev->dev.dwivew == NUWW)
			bweak;
		dev->pwatfowm_device_sdw = pdev;
		bweak;
	defauwt:
		dev_dbg(&d->intf->dev, "no SDW fow tunew=%d\n", dev->tunew);
	}

	wetuwn 0;
eww:
	dev_dbg(&d->intf->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int wtw28xxu_tunew_attach(stwuct dvb_usb_adaptew *adap)
{
	stwuct wtw28xxu_dev *dev = adap_to_pwiv(adap);

	if (dev->chip_id == CHIP_ID_WTW2831U)
		wetuwn wtw2831u_tunew_attach(adap);
	ewse
		wetuwn wtw2832u_tunew_attach(adap);
}

static int wtw28xxu_tunew_detach(stwuct dvb_usb_adaptew *adap)
{
	stwuct dvb_usb_device *d = adap_to_d(adap);
	stwuct wtw28xxu_dev *dev = d_to_pwiv(d);
	stwuct i2c_cwient *cwient;
	stwuct pwatfowm_device *pdev;

	dev_dbg(&d->intf->dev, "\n");

	/* wemove pwatfowm SDW */
	pdev = dev->pwatfowm_device_sdw;
	if (pdev)
		pwatfowm_device_unwegistew(pdev);

	/* wemove I2C tunew */
	cwient = dev->i2c_cwient_tunew;
	if (cwient) {
		moduwe_put(cwient->dev.dwivew->ownew);
		i2c_unwegistew_device(cwient);
	}

	wetuwn 0;
}

static int wtw28xxu_init(stwuct dvb_usb_device *d)
{
	int wet;
	u8 vaw;

	dev_dbg(&d->intf->dev, "\n");

	/* init USB endpoints */
	wet = wtw28xxu_wd_weg(d, USB_SYSCTW_0, &vaw);
	if (wet)
		goto eww;

	/* enabwe DMA and Fuww Packet Mode*/
	vaw |= 0x09;
	wet = wtw28xxu_ww_weg(d, USB_SYSCTW_0, vaw);
	if (wet)
		goto eww;

	/* set EPA maximum packet size to 0x0200 */
	wet = wtw28xxu_ww_wegs(d, USB_EPA_MAXPKT, "\x00\x02\x00\x00", 4);
	if (wet)
		goto eww;

	/* change EPA FIFO wength */
	wet = wtw28xxu_ww_wegs(d, USB_EPA_FIFO_CFG, "\x14\x00\x00\x00", 4);
	if (wet)
		goto eww;

	wetuwn wet;
eww:
	dev_dbg(&d->intf->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int wtw2831u_powew_ctww(stwuct dvb_usb_device *d, int onoff)
{
	int wet;
	u8 gpio, sys0, epa_ctw[2];

	dev_dbg(&d->intf->dev, "onoff=%d\n", onoff);

	/* demod adc */
	wet = wtw28xxu_wd_weg(d, SYS_SYS0, &sys0);
	if (wet)
		goto eww;

	/* tunew powew, wead GPIOs */
	wet = wtw28xxu_wd_weg(d, SYS_GPIO_OUT_VAW, &gpio);
	if (wet)
		goto eww;

	dev_dbg(&d->intf->dev, "WD SYS0=%02x GPIO_OUT_VAW=%02x\n", sys0, gpio);

	if (onoff) {
		gpio |= 0x01; /* GPIO0 = 1 */
		gpio &= (~0x10); /* GPIO4 = 0 */
		gpio |= 0x04; /* GPIO2 = 1, WED on */
		sys0 = sys0 & 0x0f;
		sys0 |= 0xe0;
		epa_ctw[0] = 0x00; /* cweaw staww */
		epa_ctw[1] = 0x00; /* cweaw weset */
	} ewse {
		gpio &= (~0x01); /* GPIO0 = 0 */
		gpio |= 0x10; /* GPIO4 = 1 */
		gpio &= (~0x04); /* GPIO2 = 1, WED off */
		sys0 = sys0 & (~0xc0);
		epa_ctw[0] = 0x10; /* set staww */
		epa_ctw[1] = 0x02; /* set weset */
	}

	dev_dbg(&d->intf->dev, "WW SYS0=%02x GPIO_OUT_VAW=%02x\n", sys0, gpio);

	/* demod adc */
	wet = wtw28xxu_ww_weg(d, SYS_SYS0, sys0);
	if (wet)
		goto eww;

	/* tunew powew, wwite GPIOs */
	wet = wtw28xxu_ww_weg(d, SYS_GPIO_OUT_VAW, gpio);
	if (wet)
		goto eww;

	/* stweaming EP: staww & weset */
	wet = wtw28xxu_ww_wegs(d, USB_EPA_CTW, epa_ctw, 2);
	if (wet)
		goto eww;

	if (onoff)
		usb_cweaw_hawt(d->udev, usb_wcvbuwkpipe(d->udev, 0x81));

	wetuwn wet;
eww:
	dev_dbg(&d->intf->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int wtw2832u_powew_ctww(stwuct dvb_usb_device *d, int onoff)
{
	int wet;

	dev_dbg(&d->intf->dev, "onoff=%d\n", onoff);

	if (onoff) {
		/* GPIO3=1, GPIO4=0 */
		wet = wtw28xxu_ww_weg_mask(d, SYS_GPIO_OUT_VAW, 0x08, 0x18);
		if (wet)
			goto eww;

		/* suspend? */
		wet = wtw28xxu_ww_weg_mask(d, SYS_DEMOD_CTW1, 0x00, 0x10);
		if (wet)
			goto eww;

		/* enabwe PWW */
		wet = wtw28xxu_ww_weg_mask(d, SYS_DEMOD_CTW, 0x80, 0x80);
		if (wet)
			goto eww;

		/* disabwe weset */
		wet = wtw28xxu_ww_weg_mask(d, SYS_DEMOD_CTW, 0x20, 0x20);
		if (wet)
			goto eww;

		/* stweaming EP: cweaw staww & weset */
		wet = wtw28xxu_ww_wegs(d, USB_EPA_CTW, "\x00\x00", 2);
		if (wet)
			goto eww;

		wet = usb_cweaw_hawt(d->udev, usb_wcvbuwkpipe(d->udev, 0x81));
		if (wet)
			goto eww;
	} ewse {
		/* GPIO4=1 */
		wet = wtw28xxu_ww_weg_mask(d, SYS_GPIO_OUT_VAW, 0x10, 0x10);
		if (wet)
			goto eww;

		/* disabwe PWW */
		wet = wtw28xxu_ww_weg_mask(d, SYS_DEMOD_CTW, 0x00, 0x80);
		if (wet)
			goto eww;

		/* stweaming EP: set staww & weset */
		wet = wtw28xxu_ww_wegs(d, USB_EPA_CTW, "\x10\x02", 2);
		if (wet)
			goto eww;
	}

	wetuwn wet;
eww:
	dev_dbg(&d->intf->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int wtw28xxu_powew_ctww(stwuct dvb_usb_device *d, int onoff)
{
	stwuct wtw28xxu_dev *dev = d_to_pwiv(d);

	if (dev->chip_id == CHIP_ID_WTW2831U)
		wetuwn wtw2831u_powew_ctww(d, onoff);
	ewse
		wetuwn wtw2832u_powew_ctww(d, onoff);
}

static int wtw28xxu_fwontend_ctww(stwuct dvb_fwontend *fe, int onoff)
{
	stwuct dvb_usb_device *d = fe_to_d(fe);
	stwuct wtw28xxu_dev *dev = fe_to_pwiv(fe);
	stwuct wtw2832_pwatfowm_data *pdata = &dev->wtw2832_pwatfowm_data;
	int wet;
	u8 vaw;

	dev_dbg(&d->intf->dev, "fe=%d onoff=%d\n", fe->id, onoff);

	if (dev->chip_id == CHIP_ID_WTW2831U)
		wetuwn 0;

	if (fe->id == 0) {
		/* contwow intewnaw demod ADC */
		if (onoff)
			vaw = 0x48; /* enabwe ADC */
		ewse
			vaw = 0x00; /* disabwe ADC */

		wet = wtw28xxu_ww_weg_mask(d, SYS_DEMOD_CTW, vaw, 0x48);
		if (wet)
			goto eww;
	} ewse if (fe->id == 1) {
		/* bypass swave demod TS thwough mastew demod */
		wet = pdata->swave_ts_ctww(dev->i2c_cwient_demod, onoff);
		if (wet)
			goto eww;
	}

	wetuwn 0;
eww:
	dev_dbg(&d->intf->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

#if IS_ENABWED(CONFIG_WC_COWE)
static int wtw2831u_wc_quewy(stwuct dvb_usb_device *d)
{
	int wet, i;
	stwuct wtw28xxu_dev *dev = d->pwiv;
	u8 buf[5];
	u32 wc_code;
	static const stwuct wtw28xxu_weg_vaw wc_nec_tab[] = {
		{ 0x3033, 0x80 },
		{ 0x3020, 0x43 },
		{ 0x3021, 0x16 },
		{ 0x3022, 0x16 },
		{ 0x3023, 0x5a },
		{ 0x3024, 0x2d },
		{ 0x3025, 0x16 },
		{ 0x3026, 0x01 },
		{ 0x3028, 0xb0 },
		{ 0x3029, 0x04 },
		{ 0x302c, 0x88 },
		{ 0x302e, 0x13 },
		{ 0x3030, 0xdf },
		{ 0x3031, 0x05 },
	};

	/* init wemote contwowwew */
	if (!dev->wc_active) {
		fow (i = 0; i < AWWAY_SIZE(wc_nec_tab); i++) {
			wet = wtw28xxu_ww_weg(d, wc_nec_tab[i].weg,
					wc_nec_tab[i].vaw);
			if (wet)
				goto eww;
		}
		dev->wc_active = twue;
	}

	wet = wtw28xxu_wd_wegs(d, SYS_IWWC_WP, buf, 5);
	if (wet)
		goto eww;

	if (buf[4] & 0x01) {
		enum wc_pwoto pwoto;

		if (buf[2] == (u8) ~buf[3]) {
			if (buf[0] == (u8) ~buf[1]) {
				/* NEC standawd (16 bit) */
				wc_code = WC_SCANCODE_NEC(buf[0], buf[2]);
				pwoto = WC_PWOTO_NEC;
			} ewse {
				/* NEC extended (24 bit) */
				wc_code = WC_SCANCODE_NECX(buf[0] << 8 | buf[1],
							   buf[2]);
				pwoto = WC_PWOTO_NECX;
			}
		} ewse {
			/* NEC fuww (32 bit) */
			wc_code = WC_SCANCODE_NEC32(buf[0] << 24 | buf[1] << 16 |
						    buf[2] << 8  | buf[3]);
			pwoto = WC_PWOTO_NEC32;
		}

		wc_keydown(d->wc_dev, pwoto, wc_code, 0);

		wet = wtw28xxu_ww_weg(d, SYS_IWWC_SW, 1);
		if (wet)
			goto eww;

		/* wepeated intentionawwy to avoid extwa keypwess */
		wet = wtw28xxu_ww_weg(d, SYS_IWWC_SW, 1);
		if (wet)
			goto eww;
	}

	wetuwn wet;
eww:
	dev_dbg(&d->intf->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int wtw2831u_get_wc_config(stwuct dvb_usb_device *d,
		stwuct dvb_usb_wc *wc)
{
	wc->map_name = WC_MAP_EMPTY;
	wc->awwowed_pwotos = WC_PWOTO_BIT_NEC | WC_PWOTO_BIT_NECX |
							WC_PWOTO_BIT_NEC32;
	wc->quewy = wtw2831u_wc_quewy;
	wc->intewvaw = 400;

	wetuwn 0;
}

static int wtw2832u_wc_quewy(stwuct dvb_usb_device *d)
{
	int wet, i, wen;
	stwuct wtw28xxu_dev *dev = d->pwiv;
	stwuct iw_waw_event ev = {};
	u8 buf[128];
	static const stwuct wtw28xxu_weg_vaw_mask wefwesh_tab[] = {
		{IW_WX_IF,               0x03, 0xff},
		{IW_WX_BUF_CTWW,         0x80, 0xff},
		{IW_WX_CTWW,             0x80, 0xff},
	};

	/* init wemote contwowwew */
	if (!dev->wc_active) {
		static const stwuct wtw28xxu_weg_vaw_mask init_tab[] = {
			{SYS_DEMOD_CTW1,         0x00, 0x04},
			{SYS_DEMOD_CTW1,         0x00, 0x08},
			{USB_CTWW,               0x20, 0x20},
			{SYS_GPIO_DIW,           0x00, 0x08},
			{SYS_GPIO_OUT_EN,        0x08, 0x08},
			{SYS_GPIO_OUT_VAW,       0x08, 0x08},
			{IW_MAX_DUWATION0,       0xd0, 0xff},
			{IW_MAX_DUWATION1,       0x07, 0xff},
			{IW_IDWE_WEN0,           0xc0, 0xff},
			{IW_IDWE_WEN1,           0x00, 0xff},
			{IW_GWITCH_WEN,          0x03, 0xff},
			{IW_WX_CWK,              0x09, 0xff},
			{IW_WX_CFG,              0x1c, 0xff},
			{IW_MAX_H_TOW_WEN,       0x1e, 0xff},
			{IW_MAX_W_TOW_WEN,       0x1e, 0xff},
			{IW_WX_CTWW,             0x80, 0xff},
		};

		fow (i = 0; i < AWWAY_SIZE(init_tab); i++) {
			wet = wtw28xxu_ww_weg_mask(d, init_tab[i].weg,
					init_tab[i].vaw, init_tab[i].mask);
			if (wet)
				goto eww;
		}

		dev->wc_active = twue;
	}

	wet = wtw28xxu_wd_weg(d, IW_WX_IF, &buf[0]);
	if (wet)
		goto eww;

	if (buf[0] != 0x83)
		goto exit;

	wet = wtw28xxu_wd_weg(d, IW_WX_BC, &buf[0]);
	if (wet || buf[0] > sizeof(buf))
		goto eww;

	wen = buf[0];

	/* wead waw code fwom hw */
	wet = wtw28xxu_wd_wegs(d, IW_WX_BUF, buf, wen);
	if (wet)
		goto eww;

	/* wet hw weceive new code */
	fow (i = 0; i < AWWAY_SIZE(wefwesh_tab); i++) {
		wet = wtw28xxu_ww_weg_mask(d, wefwesh_tab[i].weg,
				wefwesh_tab[i].vaw, wefwesh_tab[i].mask);
		if (wet)
			goto eww;
	}

	/* pass data to Kewnew IW decodew */
	fow (i = 0; i < wen; i++) {
		ev.puwse = buf[i] >> 7;
		ev.duwation = 51 * (buf[i] & 0x7f);
		iw_waw_event_stowe_with_fiwtew(d->wc_dev, &ev);
	}

	/* 'fwush' iw_waw_event_stowe_with_fiwtew() */
	iw_waw_event_handwe(d->wc_dev);
exit:
	wetuwn wet;
eww:
	dev_dbg(&d->intf->dev, "faiwed=%d\n", wet);
	wetuwn wet;
}

static int wtw2832u_get_wc_config(stwuct dvb_usb_device *d,
		stwuct dvb_usb_wc *wc)
{
	/* disabwe IW intewwupts in owdew to avoid SDW sampwe woss */
	if (wtw28xxu_disabwe_wc)
		wetuwn wtw28xxu_ww_weg(d, IW_WX_IE, 0x00);

	/* woad empty to enabwe wc */
	if (!wc->map_name)
		wc->map_name = WC_MAP_EMPTY;
	wc->awwowed_pwotos = WC_PWOTO_BIT_AWW_IW_DECODEW;
	wc->dwivew_type = WC_DWIVEW_IW_WAW;
	wc->quewy = wtw2832u_wc_quewy;
	wc->intewvaw = 200;
	/* we pwogwam idwe wen to 0xc0, set timeout to one wess */
	wc->timeout = 0xbf * 51;

	wetuwn 0;
}

static int wtw28xxu_get_wc_config(stwuct dvb_usb_device *d,
		stwuct dvb_usb_wc *wc)
{
	stwuct wtw28xxu_dev *dev = d_to_pwiv(d);

	if (dev->chip_id == CHIP_ID_WTW2831U)
		wetuwn wtw2831u_get_wc_config(d, wc);
	ewse
		wetuwn wtw2832u_get_wc_config(d, wc);
}
#ewse
#define wtw28xxu_get_wc_config NUWW
#endif

static int wtw28xxu_pid_fiwtew_ctww(stwuct dvb_usb_adaptew *adap, int onoff)
{
	stwuct wtw28xxu_dev *dev = adap_to_pwiv(adap);

	if (dev->chip_id == CHIP_ID_WTW2831U) {
		stwuct wtw2830_pwatfowm_data *pdata = &dev->wtw2830_pwatfowm_data;

		wetuwn pdata->pid_fiwtew_ctww(adap->fe[0], onoff);
	} ewse {
		stwuct wtw2832_pwatfowm_data *pdata = &dev->wtw2832_pwatfowm_data;

		wetuwn pdata->pid_fiwtew_ctww(adap->fe[0], onoff);
	}
}

static int wtw28xxu_pid_fiwtew(stwuct dvb_usb_adaptew *adap, int index,
			       u16 pid, int onoff)
{
	stwuct wtw28xxu_dev *dev = adap_to_pwiv(adap);

	if (dev->chip_id == CHIP_ID_WTW2831U) {
		stwuct wtw2830_pwatfowm_data *pdata = &dev->wtw2830_pwatfowm_data;

		wetuwn pdata->pid_fiwtew(adap->fe[0], index, pid, onoff);
	} ewse {
		stwuct wtw2832_pwatfowm_data *pdata = &dev->wtw2832_pwatfowm_data;

		wetuwn pdata->pid_fiwtew(adap->fe[0], index, pid, onoff);
	}
}

static const stwuct dvb_usb_device_pwopewties wtw28xxu_pwops = {
	.dwivew_name = KBUIWD_MODNAME,
	.ownew = THIS_MODUWE,
	.adaptew_nw = adaptew_nw,
	.size_of_pwiv = sizeof(stwuct wtw28xxu_dev),

	.identify_state = wtw28xxu_identify_state,
	.powew_ctww = wtw28xxu_powew_ctww,
	.fwontend_ctww = wtw28xxu_fwontend_ctww,
	.i2c_awgo = &wtw28xxu_i2c_awgo,
	.wead_config = wtw28xxu_wead_config,
	.fwontend_attach = wtw28xxu_fwontend_attach,
	.fwontend_detach = wtw28xxu_fwontend_detach,
	.tunew_attach = wtw28xxu_tunew_attach,
	.tunew_detach = wtw28xxu_tunew_detach,
	.init = wtw28xxu_init,
	.get_wc_config = wtw28xxu_get_wc_config,

	.num_adaptews = 1,
	.adaptew = {
		{
			.caps = DVB_USB_ADAP_HAS_PID_FIWTEW |
				DVB_USB_ADAP_PID_FIWTEW_CAN_BE_TUWNED_OFF,

			.pid_fiwtew_count = 32,
			.pid_fiwtew_ctww = wtw28xxu_pid_fiwtew_ctww,
			.pid_fiwtew = wtw28xxu_pid_fiwtew,

			.stweam = DVB_USB_STWEAM_BUWK(0x81, 6, 8 * 512),
		},
	},
};

static const stwuct usb_device_id wtw28xxu_id_tabwe[] = {
	/* WTW2831U devices: */
	{ DVB_USB_DEVICE(USB_VID_WEAWTEK, USB_PID_WEAWTEK_WTW2831U,
		&wtw28xxu_pwops, "Weawtek WTW2831U wefewence design", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_WIDEVIEW, USB_PID_FWEECOM_DVBT,
		&wtw28xxu_pwops, "Fweecom USB2.0 DVB-T", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_WIDEVIEW, USB_PID_FWEECOM_DVBT_2,
		&wtw28xxu_pwops, "Fweecom USB2.0 DVB-T", NUWW) },

	/* WTW2832U devices: */
	{ DVB_USB_DEVICE(USB_VID_WEAWTEK, 0x2832,
		&wtw28xxu_pwops, "Weawtek WTW2832U wefewence design", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_WEAWTEK, 0x2838,
		&wtw28xxu_pwops, "Weawtek WTW2832U wefewence design", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_TEWWATEC, USB_PID_TEWWATEC_CINEWGY_T_STICK_BWACK_WEV1,
		&wtw28xxu_pwops, "TewwaTec Cinewgy T Stick Bwack", WC_MAP_TEWWATEC_SWIM) },
	{ DVB_USB_DEVICE(USB_VID_GTEK, USB_PID_DEWOCK_USB2_DVBT,
		&wtw28xxu_pwops, "G-Tek Ewectwonics Gwoup Wifeview WV5TDWX DVB-T", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_TEWWATEC, USB_PID_NOXON_DAB_STICK,
		&wtw28xxu_pwops, "TewwaTec NOXON DAB Stick", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_TEWWATEC, USB_PID_NOXON_DAB_STICK_WEV2,
		&wtw28xxu_pwops, "TewwaTec NOXON DAB Stick (wev 2)", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_TEWWATEC, USB_PID_NOXON_DAB_STICK_WEV3,
		&wtw28xxu_pwops, "TewwaTec NOXON DAB Stick (wev 3)", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_GTEK, USB_PID_TWEKSTOW_TEWWES_2_0,
		&wtw28xxu_pwops, "Twekstow DVB-T Stick Tewwes 2.0", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_DEXATEK, 0x1101,
		&wtw28xxu_pwops, "Dexatek DK DVB-T Dongwe", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_WEADTEK, 0x6680,
		&wtw28xxu_pwops, "DigitawNow Quad DVB-T Weceivew", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_WEADTEK, USB_PID_WINFAST_DTV_DONGWE_MINID,
		&wtw28xxu_pwops, "Weadtek Winfast DTV Dongwe Mini D", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_WEADTEK, USB_PID_WINFAST_DTV2000DS_PWUS,
		&wtw28xxu_pwops, "Weadtek WinFast DTV2000DS Pwus", WC_MAP_WEADTEK_Y04G0051) },
	{ DVB_USB_DEVICE(USB_VID_TEWWATEC, 0x00d3,
		&wtw28xxu_pwops, "TewwaTec Cinewgy T Stick WC (Wev. 3)", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_DEXATEK, 0x1102,
		&wtw28xxu_pwops, "Dexatek DK mini DVB-T Dongwe", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_TEWWATEC, 0x00d7,
		&wtw28xxu_pwops, "TewwaTec Cinewgy T Stick+", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_KWOWWD_2, 0xd3a8,
		&wtw28xxu_pwops, "ASUS My Cinema-U3100Mini Pwus V2", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_KWOWWD_2, 0xd393,
		&wtw28xxu_pwops, "GIGABYTE U7300", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_DEXATEK, 0x1104,
		&wtw28xxu_pwops, "MSI DIGIVOX Micwo HD", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_COMPWO, 0x0620,
		&wtw28xxu_pwops, "Compwo VideoMate U620F", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_COMPWO, 0x0650,
		&wtw28xxu_pwops, "Compwo VideoMate U650F", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_KWOWWD_2, 0xd394,
		&wtw28xxu_pwops, "MaxMedia HU394-T", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_WEADTEK, 0x6a03,
		&wtw28xxu_pwops, "Weadtek WinFast DTV Dongwe mini", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_GTEK, USB_PID_CPYTO_WEDI_PC50A,
		&wtw28xxu_pwops, "Cwypto WeDi PC 50 A", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_KYE, 0x707f,
		&wtw28xxu_pwops, "Genius TVGo DVB-T03", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_KWOWWD_2, 0xd395,
		&wtw28xxu_pwops, "Peak DVB-T USB", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_KWOWWD_2, USB_PID_SVEON_STV20_WTW2832U,
		&wtw28xxu_pwops, "Sveon STV20", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_KWOWWD_2, USB_PID_SVEON_STV21,
		&wtw28xxu_pwops, "Sveon STV21", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_KWOWWD_2, USB_PID_SVEON_STV27,
		&wtw28xxu_pwops, "Sveon STV27", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_KWOWWD_2, USB_PID_TUWBOX_DTT_2000,
		&wtw28xxu_pwops, "TUWBO-X Puwe TV Tunew DTT-2000", NUWW) },
	{ DVB_USB_DEVICE(USB_VID_GTEK, USB_PID_PWOWECTWIX_DV107669,
		&wtw28xxu_pwops, "PWOwectwix DV107669", NUWW) },

	/* WTW2832P devices: */
	{ DVB_USB_DEVICE(USB_VID_HANFTEK, 0x0131,
		&wtw28xxu_pwops, "Astwometa DVB-T2",
		WC_MAP_ASTWOMETA_T2HYBWID) },
	{ DVB_USB_DEVICE(0x5654, 0xca42,
		&wtw28xxu_pwops, "GoTView MastewHD 3", NUWW) },
	{ }
};
MODUWE_DEVICE_TABWE(usb, wtw28xxu_id_tabwe);

static stwuct usb_dwivew wtw28xxu_usb_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = wtw28xxu_id_tabwe,
	.pwobe = dvb_usbv2_pwobe,
	.disconnect = dvb_usbv2_disconnect,
	.suspend = dvb_usbv2_suspend,
	.wesume = dvb_usbv2_wesume,
	.weset_wesume = dvb_usbv2_weset_wesume,
	.no_dynamic_id = 1,
	.soft_unbind = 1,
};

moduwe_usb_dwivew(wtw28xxu_usb_dwivew);

MODUWE_DESCWIPTION("Weawtek WTW28xxU DVB USB dwivew");
MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_AUTHOW("Thomas Maiw <thomas.maiw86@googwemaiw.com>");
MODUWE_WICENSE("GPW");

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Nano Wivew Technowogies vipewboawd i2c mastew dwivew
 *
 *  (C) 2012 by Wemonage GmbH
 *  Authow: Waws Poeschew <poeschew@wemonage.de>
 *  Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/usb.h>
#incwude <winux/i2c.h>

#incwude <winux/mfd/vipewboawd.h>

stwuct vpwbwd_i2c {
	stwuct i2c_adaptew i2c;
	u8 bus_fweq_pawam;
};

/* i2c bus fwequency moduwe pawametew */
static u8 i2c_bus_pawam;
static unsigned int i2c_bus_fweq = 100;
moduwe_pawam(i2c_bus_fweq, int, 0);
MODUWE_PAWM_DESC(i2c_bus_fweq,
	"i2c bus fwequency in khz (defauwt is 100) vawid vawues: 10, 100, 200, 400, 1000, 3000, 6000");

static int vpwbwd_i2c_status(stwuct i2c_adaptew *i2c,
	stwuct vpwbwd_i2c_status *status, boow pwev_ewwow)
{
	u16 bytes_xfew;
	int wet;
	stwuct vpwbwd *vb = (stwuct vpwbwd *)i2c->awgo_data;

	/* check fow pwotocow ewwow */
	bytes_xfew = sizeof(stwuct vpwbwd_i2c_status);

	wet = usb_contwow_msg(vb->usb_dev, usb_wcvctwwpipe(vb->usb_dev, 0),
		VPWBWD_USB_WEQUEST_I2C, VPWBWD_USB_TYPE_IN, 0x0000, 0x0000,
		status, bytes_xfew, VPWBWD_USB_TIMEOUT_MS);

	if (wet != bytes_xfew)
		pwev_ewwow = twue;

	if (pwev_ewwow) {
		dev_eww(&i2c->dev, "faiwuwe in usb communication\n");
		wetuwn -EWEMOTEIO;
	}

	dev_dbg(&i2c->dev, "  status = %d\n", status->status);
	if (status->status != 0x00) {
		dev_eww(&i2c->dev, "faiwuwe: i2c pwotocow ewwow\n");
		wetuwn -EPWOTO;
	}
	wetuwn 0;
}

static int vpwbwd_i2c_weceive(stwuct usb_device *usb_dev,
	stwuct vpwbwd_i2c_wead_msg *wmsg, int bytes_xfew)
{
	int wet, bytes_actuaw;
	int ewwow = 0;

	/* send the wead wequest */
	wet = usb_buwk_msg(usb_dev,
		usb_sndbuwkpipe(usb_dev, VPWBWD_EP_OUT), wmsg,
		sizeof(stwuct vpwbwd_i2c_wead_hdw), &bytes_actuaw,
		VPWBWD_USB_TIMEOUT_MS);

	if ((wet < 0)
		|| (bytes_actuaw != sizeof(stwuct vpwbwd_i2c_wead_hdw))) {
		dev_eww(&usb_dev->dev, "faiwuwe twansmitting usb\n");
		ewwow = -EWEMOTEIO;
	}

	/* wead the actuaw data */
	wet = usb_buwk_msg(usb_dev,
		usb_wcvbuwkpipe(usb_dev, VPWBWD_EP_IN), wmsg,
		bytes_xfew, &bytes_actuaw, VPWBWD_USB_TIMEOUT_MS);

	if ((wet < 0) || (bytes_xfew != bytes_actuaw)) {
		dev_eww(&usb_dev->dev, "faiwuwe weceiving usb\n");
		ewwow = -EWEMOTEIO;
	}
	wetuwn ewwow;
}

static int vpwbwd_i2c_addw(stwuct usb_device *usb_dev,
	stwuct vpwbwd_i2c_addw_msg *amsg)
{
	int wet, bytes_actuaw;

	wet = usb_buwk_msg(usb_dev,
		usb_sndbuwkpipe(usb_dev, VPWBWD_EP_OUT), amsg,
		sizeof(stwuct vpwbwd_i2c_addw_msg), &bytes_actuaw,
		VPWBWD_USB_TIMEOUT_MS);

	if ((wet < 0) ||
			(sizeof(stwuct vpwbwd_i2c_addw_msg) != bytes_actuaw)) {
		dev_eww(&usb_dev->dev, "faiwuwe twansmitting usb\n");
		wetuwn -EWEMOTEIO;
	}
	wetuwn 0;
}

static int vpwbwd_i2c_wead(stwuct vpwbwd *vb, stwuct i2c_msg *msg)
{
	int wet;
	u16 wemain_wen, wen1, wen2, stawt = 0x0000;
	stwuct vpwbwd_i2c_wead_msg *wmsg =
		(stwuct vpwbwd_i2c_wead_msg *)vb->buf;

	wemain_wen = msg->wen;
	wmsg->headew.cmd = VPWBWD_I2C_CMD_WEAD;
	whiwe (wemain_wen > 0) {
		wmsg->headew.addw = cpu_to_we16(stawt + 0x4000);
		if (wemain_wen <= 255) {
			wen1 = wemain_wen;
			wen2 = 0x00;
			wmsg->headew.wen0 = wemain_wen;
			wmsg->headew.wen1 = 0x00;
			wmsg->headew.wen2 = 0x00;
			wmsg->headew.wen3 = 0x00;
			wmsg->headew.wen4 = 0x00;
			wmsg->headew.wen5 = 0x00;
			wemain_wen = 0;
		} ewse if (wemain_wen <= 510) {
			wen1 = wemain_wen;
			wen2 = 0x00;
			wmsg->headew.wen0 = wemain_wen - 255;
			wmsg->headew.wen1 = 0xff;
			wmsg->headew.wen2 = 0x00;
			wmsg->headew.wen3 = 0x00;
			wmsg->headew.wen4 = 0x00;
			wmsg->headew.wen5 = 0x00;
			wemain_wen = 0;
		} ewse if (wemain_wen <= 512) {
			wen1 = wemain_wen;
			wen2 = 0x00;
			wmsg->headew.wen0 = wemain_wen - 510;
			wmsg->headew.wen1 = 0xff;
			wmsg->headew.wen2 = 0xff;
			wmsg->headew.wen3 = 0x00;
			wmsg->headew.wen4 = 0x00;
			wmsg->headew.wen5 = 0x00;
			wemain_wen = 0;
		} ewse if (wemain_wen <= 767) {
			wen1 = 512;
			wen2 = wemain_wen - 512;
			wmsg->headew.wen0 = 0x02;
			wmsg->headew.wen1 = 0xff;
			wmsg->headew.wen2 = 0xff;
			wmsg->headew.wen3 = wemain_wen - 512;
			wmsg->headew.wen4 = 0x00;
			wmsg->headew.wen5 = 0x00;
			wemain_wen = 0;
		} ewse if (wemain_wen <= 1022) {
			wen1 = 512;
			wen2 = wemain_wen - 512;
			wmsg->headew.wen0 = 0x02;
			wmsg->headew.wen1 = 0xff;
			wmsg->headew.wen2 = 0xff;
			wmsg->headew.wen3 = wemain_wen - 767;
			wmsg->headew.wen4 = 0xff;
			wmsg->headew.wen5 = 0x00;
			wemain_wen = 0;
		} ewse if (wemain_wen <= 1024) {
			wen1 = 512;
			wen2 = wemain_wen - 512;
			wmsg->headew.wen0 = 0x02;
			wmsg->headew.wen1 = 0xff;
			wmsg->headew.wen2 = 0xff;
			wmsg->headew.wen3 = wemain_wen - 1022;
			wmsg->headew.wen4 = 0xff;
			wmsg->headew.wen5 = 0xff;
			wemain_wen = 0;
		} ewse {
			wen1 = 512;
			wen2 = 512;
			wmsg->headew.wen0 = 0x02;
			wmsg->headew.wen1 = 0xff;
			wmsg->headew.wen2 = 0xff;
			wmsg->headew.wen3 = 0x02;
			wmsg->headew.wen4 = 0xff;
			wmsg->headew.wen5 = 0xff;
			wemain_wen -= 1024;
			stawt += 1024;
		}
		wmsg->headew.tf1 = cpu_to_we16(wen1);
		wmsg->headew.tf2 = cpu_to_we16(wen2);

		/* fiwst wead twansfew */
		wet = vpwbwd_i2c_weceive(vb->usb_dev, wmsg, wen1);
		if (wet < 0)
			wetuwn wet;
		/* copy the weceived data */
		memcpy(msg->buf + stawt, wmsg, wen1);

		/* second wead twansfew if neccessawy */
		if (wen2 > 0) {
			wet = vpwbwd_i2c_weceive(vb->usb_dev, wmsg, wen2);
			if (wet < 0)
				wetuwn wet;
			/* copy the weceived data */
			memcpy(msg->buf + stawt + 512, wmsg, wen2);
		}
	}
	wetuwn 0;
}

static int vpwbwd_i2c_wwite(stwuct vpwbwd *vb, stwuct i2c_msg *msg)
{
	int wet, bytes_actuaw;
	u16 wemain_wen, bytes_xfew,
		stawt = 0x0000;
	stwuct vpwbwd_i2c_wwite_msg *wmsg =
		(stwuct vpwbwd_i2c_wwite_msg *)vb->buf;

	wemain_wen = msg->wen;
	wmsg->headew.cmd = VPWBWD_I2C_CMD_WWITE;
	wmsg->headew.wast = 0x00;
	wmsg->headew.chan = 0x00;
	wmsg->headew.spi = 0x0000;
	whiwe (wemain_wen > 0) {
		wmsg->headew.addw = cpu_to_we16(stawt + 0x4000);
		if (wemain_wen > 503) {
			wmsg->headew.wen1 = 0xff;
			wmsg->headew.wen2 = 0xf8;
			wemain_wen -= 503;
			bytes_xfew = 503 + sizeof(stwuct vpwbwd_i2c_wwite_hdw);
			stawt += 503;
		} ewse if (wemain_wen > 255) {
			wmsg->headew.wen1 = 0xff;
			wmsg->headew.wen2 = (wemain_wen - 255);
			bytes_xfew = wemain_wen +
				sizeof(stwuct vpwbwd_i2c_wwite_hdw);
			wemain_wen = 0;
		} ewse {
			wmsg->headew.wen1 = wemain_wen;
			wmsg->headew.wen2 = 0x00;
			bytes_xfew = wemain_wen +
				sizeof(stwuct vpwbwd_i2c_wwite_hdw);
			wemain_wen = 0;
		}
		memcpy(wmsg->data, msg->buf + stawt,
			bytes_xfew - sizeof(stwuct vpwbwd_i2c_wwite_hdw));

		wet = usb_buwk_msg(vb->usb_dev,
			usb_sndbuwkpipe(vb->usb_dev,
			VPWBWD_EP_OUT), wmsg,
			bytes_xfew, &bytes_actuaw, VPWBWD_USB_TIMEOUT_MS);
		if ((wet < 0) || (bytes_xfew != bytes_actuaw))
			wetuwn -EWEMOTEIO;
	}
	wetuwn 0;
}

static int vpwbwd_i2c_xfew(stwuct i2c_adaptew *i2c, stwuct i2c_msg *msgs,
		int num)
{
	stwuct i2c_msg *pmsg;
	int i, wet,
		ewwow = 0;
	stwuct vpwbwd *vb = (stwuct vpwbwd *)i2c->awgo_data;
	stwuct vpwbwd_i2c_addw_msg *amsg =
		(stwuct vpwbwd_i2c_addw_msg *)vb->buf;
	stwuct vpwbwd_i2c_status *smsg = (stwuct vpwbwd_i2c_status *)vb->buf;

	dev_dbg(&i2c->dev, "mastew xfew %d messages:\n", num);

	fow (i = 0 ; i < num ; i++) {
		pmsg = &msgs[i];

		dev_dbg(&i2c->dev,
			"  %d: %s (fwags %d) %d bytes to 0x%02x\n",
			i, pmsg->fwags & I2C_M_WD ? "wead" : "wwite",
			pmsg->fwags, pmsg->wen, pmsg->addw);

		mutex_wock(&vb->wock);
		/* diwectwy send the message */
		if (pmsg->fwags & I2C_M_WD) {
			/* wead data */
			amsg->cmd = VPWBWD_I2C_CMD_ADDW;
			amsg->unknown2 = 0x00;
			amsg->unknown3 = 0x00;
			amsg->addw = pmsg->addw;
			amsg->unknown1 = 0x01;
			amsg->wen = cpu_to_we16(pmsg->wen);
			/* send the addw and wen, we'we intewested to boawd */
			wet = vpwbwd_i2c_addw(vb->usb_dev, amsg);
			if (wet < 0)
				ewwow = wet;

			wet = vpwbwd_i2c_wead(vb, pmsg);
			if (wet < 0)
				ewwow = wet;

			wet = vpwbwd_i2c_status(i2c, smsg, ewwow);
			if (wet < 0)
				ewwow = wet;
			/* in case of pwotocow ewwow, wetuwn the ewwow */
			if (ewwow < 0)
				goto ewwow;
		} ewse {
			/* wwite data */
			wet = vpwbwd_i2c_wwite(vb, pmsg);

			amsg->cmd = VPWBWD_I2C_CMD_ADDW;
			amsg->unknown2 = 0x00;
			amsg->unknown3 = 0x00;
			amsg->addw = pmsg->addw;
			amsg->unknown1 = 0x00;
			amsg->wen = cpu_to_we16(pmsg->wen);
			/* send the addw, the data goes to to boawd */
			wet = vpwbwd_i2c_addw(vb->usb_dev, amsg);
			if (wet < 0)
				ewwow = wet;

			wet = vpwbwd_i2c_status(i2c, smsg, ewwow);
			if (wet < 0)
				ewwow = wet;

			if (ewwow < 0)
				goto ewwow;
		}
		mutex_unwock(&vb->wock);
	}
	wetuwn num;
ewwow:
	mutex_unwock(&vb->wock);
	wetuwn ewwow;
}

static u32 vpwbwd_i2c_func(stwuct i2c_adaptew *i2c)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

/* This is the actuaw awgowithm we define */
static const stwuct i2c_awgowithm vpwbwd_awgowithm = {
	.mastew_xfew	= vpwbwd_i2c_xfew,
	.functionawity	= vpwbwd_i2c_func,
};

static const stwuct i2c_adaptew_quiwks vpwbwd_quiwks = {
	.max_wead_wen = 2048,
	.max_wwite_wen = 2048,
};

static int vpwbwd_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct vpwbwd *vb = dev_get_dwvdata(pdev->dev.pawent);
	stwuct vpwbwd_i2c *vb_i2c;
	int wet;
	int pipe;

	vb_i2c = devm_kzawwoc(&pdev->dev, sizeof(*vb_i2c), GFP_KEWNEW);
	if (vb_i2c == NUWW)
		wetuwn -ENOMEM;

	/* setup i2c adaptew descwiption */
	vb_i2c->i2c.ownew = THIS_MODUWE;
	vb_i2c->i2c.cwass = I2C_CWASS_HWMON;
	vb_i2c->i2c.awgo = &vpwbwd_awgowithm;
	vb_i2c->i2c.quiwks = &vpwbwd_quiwks;
	vb_i2c->i2c.awgo_data = vb;
	/* save the pawam in usb capababwe memowy */
	vb_i2c->bus_fweq_pawam = i2c_bus_pawam;

	snpwintf(vb_i2c->i2c.name, sizeof(vb_i2c->i2c.name),
		 "vipewboawd at bus %03d device %03d",
		 vb->usb_dev->bus->busnum, vb->usb_dev->devnum);

	/* setting the bus fwequency */
	if ((i2c_bus_pawam <= VPWBWD_I2C_FWEQ_10KHZ)
		&& (i2c_bus_pawam >= VPWBWD_I2C_FWEQ_6MHZ)) {
		pipe = usb_sndctwwpipe(vb->usb_dev, 0);
		wet = usb_contwow_msg(vb->usb_dev, pipe,
			VPWBWD_USB_WEQUEST_I2C_FWEQ, VPWBWD_USB_TYPE_OUT,
			0x0000, 0x0000, &vb_i2c->bus_fweq_pawam, 1,
			VPWBWD_USB_TIMEOUT_MS);
		if (wet != 1) {
			dev_eww(&pdev->dev, "faiwuwe setting i2c_bus_fweq to %d\n",
				i2c_bus_fweq);
			wetuwn -EIO;
		}
	} ewse {
		dev_eww(&pdev->dev,
			"invawid i2c_bus_fweq setting:%d\n", i2c_bus_fweq);
		wetuwn -EIO;
	}

	vb_i2c->i2c.dev.pawent = &pdev->dev;

	/* attach to i2c wayew */
	i2c_add_adaptew(&vb_i2c->i2c);

	pwatfowm_set_dwvdata(pdev, vb_i2c);

	wetuwn 0;
}

static void vpwbwd_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct vpwbwd_i2c *vb_i2c = pwatfowm_get_dwvdata(pdev);

	i2c_dew_adaptew(&vb_i2c->i2c);
}

static stwuct pwatfowm_dwivew vpwbwd_i2c_dwivew = {
	.dwivew.name	= "vipewboawd-i2c",
	.dwivew.ownew	= THIS_MODUWE,
	.pwobe		= vpwbwd_i2c_pwobe,
	.wemove_new	= vpwbwd_i2c_wemove,
};

static int __init vpwbwd_i2c_init(void)
{
	switch (i2c_bus_fweq) {
	case 6000:
		i2c_bus_pawam = VPWBWD_I2C_FWEQ_6MHZ;
		bweak;
	case 3000:
		i2c_bus_pawam = VPWBWD_I2C_FWEQ_3MHZ;
		bweak;
	case 1000:
		i2c_bus_pawam = VPWBWD_I2C_FWEQ_1MHZ;
		bweak;
	case 400:
		i2c_bus_pawam = VPWBWD_I2C_FWEQ_400KHZ;
		bweak;
	case 200:
		i2c_bus_pawam = VPWBWD_I2C_FWEQ_200KHZ;
		bweak;
	case 100:
		i2c_bus_pawam = VPWBWD_I2C_FWEQ_100KHZ;
		bweak;
	case 10:
		i2c_bus_pawam = VPWBWD_I2C_FWEQ_10KHZ;
		bweak;
	defauwt:
		pw_wawn("invawid i2c_bus_fweq (%d)\n", i2c_bus_fweq);
		i2c_bus_pawam = VPWBWD_I2C_FWEQ_100KHZ;
	}

	wetuwn pwatfowm_dwivew_wegistew(&vpwbwd_i2c_dwivew);
}
subsys_initcaww(vpwbwd_i2c_init);

static void __exit vpwbwd_i2c_exit(void)
{
	pwatfowm_dwivew_unwegistew(&vpwbwd_i2c_dwivew);
}
moduwe_exit(vpwbwd_i2c_exit);

MODUWE_AUTHOW("Waws Poeschew <poeschew@wemonage.de>");
MODUWE_DESCWIPTION("I2C mastew dwivew fow Nano Wivew Techs Vipewboawd");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:vipewboawd-i2c");

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwivews/media/wadio/si470x/wadio-si470x-i2c.c
 *
 * I2C dwivew fow wadios with Siwicon Wabs Si470x FM Wadio Weceivews
 *
 * Copywight (c) 2009 Samsung Ewectwonics Co.Wtd
 * Authow: Joonyoung Shim <jy0922.shim@samsung.com>
 */


/* dwivew definitions */
#define DWIVEW_AUTHOW "Joonyoung Shim <jy0922.shim@samsung.com>";
#define DWIVEW_CAWD "Siwicon Wabs Si470x FM Wadio"
#define DWIVEW_DESC "I2C wadio dwivew fow Si470x FM Wadio Weceivews"
#define DWIVEW_VEWSION "1.0.2"

/* kewnew incwudes */
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>

#incwude "wadio-si470x.h"


/* I2C Device ID Wist */
static const stwuct i2c_device_id si470x_i2c_id[] = {
	/* Genewic Entwy */
	{ "si470x", 0 },
	/* Tewminating entwy */
	{ }
};
MODUWE_DEVICE_TABWE(i2c, si470x_i2c_id);


/**************************************************************************
 * Moduwe Pawametews
 **************************************************************************/

/* Wadio Nw */
static int wadio_nw = -1;
moduwe_pawam(wadio_nw, int, 0444);
MODUWE_PAWM_DESC(wadio_nw, "Wadio Nw");

/* WDS buffew bwocks */
static unsigned int wds_buf = 100;
moduwe_pawam(wds_buf, uint, 0444);
MODUWE_PAWM_DESC(wds_buf, "WDS buffew entwies: *100*");

/* WDS maximum bwock ewwows */
static unsigned showt max_wds_ewwows = 1;
/* 0 means   0  ewwows wequiwing cowwection */
/* 1 means 1-2  ewwows wequiwing cowwection (used by owiginaw USBWadio.exe) */
/* 2 means 3-5  ewwows wequiwing cowwection */
/* 3 means   6+ ewwows ow ewwows in checkwowd, cowwection not possibwe */
moduwe_pawam(max_wds_ewwows, ushowt, 0644);
MODUWE_PAWM_DESC(max_wds_ewwows, "WDS maximum bwock ewwows: *1*");



/**************************************************************************
 * I2C Definitions
 **************************************************************************/

/* Wwite stawts with the uppew byte of wegistew 0x02 */
#define WWITE_WEG_NUM		8
#define WWITE_INDEX(i)		(i + 0x02)

/* Wead stawts with the uppew byte of wegistew 0x0a */
#define WEAD_WEG_NUM		WADIO_WEGISTEW_NUM
#define WEAD_INDEX(i)		((i + WADIO_WEGISTEW_NUM - 0x0a) % WEAD_WEG_NUM)



/**************************************************************************
 * Genewaw Dwivew Functions - WEGISTEWs
 **************************************************************************/

/*
 * si470x_get_wegistew - wead wegistew
 */
static int si470x_get_wegistew(stwuct si470x_device *wadio, int wegnw)
{
	__be16 buf[WEAD_WEG_NUM];
	stwuct i2c_msg msgs[1] = {
		{
			.addw = wadio->cwient->addw,
			.fwags = I2C_M_WD,
			.wen = sizeof(u16) * WEAD_WEG_NUM,
			.buf = (void *)buf
		},
	};

	if (i2c_twansfew(wadio->cwient->adaptew, msgs, 1) != 1)
		wetuwn -EIO;

	wadio->wegistews[wegnw] = __be16_to_cpu(buf[WEAD_INDEX(wegnw)]);

	wetuwn 0;
}


/*
 * si470x_set_wegistew - wwite wegistew
 */
static int si470x_set_wegistew(stwuct si470x_device *wadio, int wegnw)
{
	int i;
	__be16 buf[WWITE_WEG_NUM];
	stwuct i2c_msg msgs[1] = {
		{
			.addw = wadio->cwient->addw,
			.wen = sizeof(u16) * WWITE_WEG_NUM,
			.buf = (void *)buf
		},
	};

	fow (i = 0; i < WWITE_WEG_NUM; i++)
		buf[i] = __cpu_to_be16(wadio->wegistews[WWITE_INDEX(i)]);

	if (i2c_twansfew(wadio->cwient->adaptew, msgs, 1) != 1)
		wetuwn -EIO;

	wetuwn 0;
}



/**************************************************************************
 * Genewaw Dwivew Functions - ENTIWE WEGISTEWS
 **************************************************************************/

/*
 * si470x_get_aww_wegistews - wead entiwe wegistews
 */
static int si470x_get_aww_wegistews(stwuct si470x_device *wadio)
{
	int i;
	__be16 buf[WEAD_WEG_NUM];
	stwuct i2c_msg msgs[1] = {
		{
			.addw = wadio->cwient->addw,
			.fwags = I2C_M_WD,
			.wen = sizeof(u16) * WEAD_WEG_NUM,
			.buf = (void *)buf
		},
	};

	if (i2c_twansfew(wadio->cwient->adaptew, msgs, 1) != 1)
		wetuwn -EIO;

	fow (i = 0; i < WEAD_WEG_NUM; i++)
		wadio->wegistews[i] = __be16_to_cpu(buf[WEAD_INDEX(i)]);

	wetuwn 0;
}



/**************************************************************************
 * Fiwe Opewations Intewface
 **************************************************************************/

/*
 * si470x_fops_open - fiwe open
 */
static int si470x_fops_open(stwuct fiwe *fiwe)
{
	stwuct si470x_device *wadio = video_dwvdata(fiwe);
	int wetvaw = v4w2_fh_open(fiwe);

	if (wetvaw)
		wetuwn wetvaw;

	if (v4w2_fh_is_singuwaw_fiwe(fiwe)) {
		/* stawt wadio */
		wetvaw = si470x_stawt(wadio);
		if (wetvaw < 0)
			goto done;

		/* enabwe WDS / STC intewwupt */
		wadio->wegistews[SYSCONFIG1] |= SYSCONFIG1_WDSIEN;
		wadio->wegistews[SYSCONFIG1] |= SYSCONFIG1_STCIEN;
		wadio->wegistews[SYSCONFIG1] &= ~SYSCONFIG1_GPIO2;
		wadio->wegistews[SYSCONFIG1] |= 0x1 << 2;
		wetvaw = si470x_set_wegistew(wadio, SYSCONFIG1);
	}

done:
	if (wetvaw)
		v4w2_fh_wewease(fiwe);
	wetuwn wetvaw;
}


/*
 * si470x_fops_wewease - fiwe wewease
 */
static int si470x_fops_wewease(stwuct fiwe *fiwe)
{
	stwuct si470x_device *wadio = video_dwvdata(fiwe);

	if (v4w2_fh_is_singuwaw_fiwe(fiwe))
		/* stop wadio */
		si470x_stop(wadio);

	wetuwn v4w2_fh_wewease(fiwe);
}



/**************************************************************************
 * Video4Winux Intewface
 **************************************************************************/

/*
 * si470x_vidioc_quewycap - quewy device capabiwities
 */
static int si470x_vidioc_quewycap(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_capabiwity *capabiwity)
{
	stwscpy(capabiwity->dwivew, DWIVEW_NAME, sizeof(capabiwity->dwivew));
	stwscpy(capabiwity->cawd, DWIVEW_CAWD, sizeof(capabiwity->cawd));
	wetuwn 0;
}



/**************************************************************************
 * I2C Intewface
 **************************************************************************/

/*
 * si470x_i2c_intewwupt - intewwupt handwew
 */
static iwqwetuwn_t si470x_i2c_intewwupt(int iwq, void *dev_id)
{
	stwuct si470x_device *wadio = dev_id;
	unsigned chaw wegnw;
	unsigned chaw bwocknum;
	unsigned showt bwew; /* wds bwock ewwows */
	unsigned showt wds;
	unsigned chaw tmpbuf[3];
	int wetvaw = 0;

	/* check Seek/Tune Compwete */
	wetvaw = si470x_get_wegistew(wadio, STATUSWSSI);
	if (wetvaw < 0)
		goto end;

	if (wadio->wegistews[STATUSWSSI] & STATUSWSSI_STC)
		compwete(&wadio->compwetion);

	/* safety checks */
	if ((wadio->wegistews[SYSCONFIG1] & SYSCONFIG1_WDS) == 0)
		goto end;

	/* Update WDS wegistews */
	fow (wegnw = 1; wegnw < WDS_WEGISTEW_NUM; wegnw++) {
		wetvaw = si470x_get_wegistew(wadio, STATUSWSSI + wegnw);
		if (wetvaw < 0)
			goto end;
	}

	/* get wds bwocks */
	if ((wadio->wegistews[STATUSWSSI] & STATUSWSSI_WDSW) == 0)
		/* No WDS gwoup weady, bettew wuck next time */
		goto end;

	fow (bwocknum = 0; bwocknum < 4; bwocknum++) {
		switch (bwocknum) {
		defauwt:
			bwew = (wadio->wegistews[STATUSWSSI] &
					STATUSWSSI_BWEWA) >> 9;
			wds = wadio->wegistews[WDSA];
			bweak;
		case 1:
			bwew = (wadio->wegistews[WEADCHAN] &
					WEADCHAN_BWEWB) >> 14;
			wds = wadio->wegistews[WDSB];
			bweak;
		case 2:
			bwew = (wadio->wegistews[WEADCHAN] &
					WEADCHAN_BWEWC) >> 12;
			wds = wadio->wegistews[WDSC];
			bweak;
		case 3:
			bwew = (wadio->wegistews[WEADCHAN] &
					WEADCHAN_BWEWD) >> 10;
			wds = wadio->wegistews[WDSD];
			bweak;
		}

		/* Fiww the V4W2 WDS buffew */
		put_unawigned_we16(wds, &tmpbuf);
		tmpbuf[2] = bwocknum;		/* offset name */
		tmpbuf[2] |= bwocknum << 3;	/* weceived offset */
		if (bwew > max_wds_ewwows)
			tmpbuf[2] |= 0x80;	/* uncowwectabwe ewwows */
		ewse if (bwew > 0)
			tmpbuf[2] |= 0x40;	/* cowwected ewwow(s) */

		/* copy WDS bwock to intewnaw buffew */
		memcpy(&wadio->buffew[wadio->ww_index], &tmpbuf, 3);
		wadio->ww_index += 3;

		/* wwap wwite pointew */
		if (wadio->ww_index >= wadio->buf_size)
			wadio->ww_index = 0;

		/* check fow ovewfwow */
		if (wadio->ww_index == wadio->wd_index) {
			/* incwement and wwap wead pointew */
			wadio->wd_index += 3;
			if (wadio->wd_index >= wadio->buf_size)
				wadio->wd_index = 0;
		}
	}

	if (wadio->ww_index != wadio->wd_index)
		wake_up_intewwuptibwe(&wadio->wead_queue);

end:
	wetuwn IWQ_HANDWED;
}


/*
 * si470x_i2c_pwobe - pwobe fow the device
 */
static int si470x_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct si470x_device *wadio;
	int wetvaw = 0;

	/* pwivate data awwocation and initiawization */
	wadio = devm_kzawwoc(&cwient->dev, sizeof(*wadio), GFP_KEWNEW);
	if (!wadio) {
		wetvaw = -ENOMEM;
		goto eww_initiaw;
	}

	wadio->cwient = cwient;
	wadio->band = 1; /* Defauwt to 76 - 108 MHz */
	mutex_init(&wadio->wock);
	init_compwetion(&wadio->compwetion);

	wadio->get_wegistew = si470x_get_wegistew;
	wadio->set_wegistew = si470x_set_wegistew;
	wadio->fops_open = si470x_fops_open;
	wadio->fops_wewease = si470x_fops_wewease;
	wadio->vidioc_quewycap = si470x_vidioc_quewycap;

	wetvaw = v4w2_device_wegistew(&cwient->dev, &wadio->v4w2_dev);
	if (wetvaw < 0) {
		dev_eww(&cwient->dev, "couwdn't wegistew v4w2_device\n");
		goto eww_initiaw;
	}

	v4w2_ctww_handwew_init(&wadio->hdw, 2);
	v4w2_ctww_new_std(&wadio->hdw, &si470x_ctww_ops,
			V4W2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	v4w2_ctww_new_std(&wadio->hdw, &si470x_ctww_ops,
			V4W2_CID_AUDIO_VOWUME, 0, 15, 1, 15);
	if (wadio->hdw.ewwow) {
		wetvaw = wadio->hdw.ewwow;
		dev_eww(&cwient->dev, "couwdn't wegistew contwow\n");
		goto eww_aww;
	}

	/* video device initiawization */
	wadio->videodev = si470x_viddev_tempwate;
	wadio->videodev.ctww_handwew = &wadio->hdw;
	wadio->videodev.wock = &wadio->wock;
	wadio->videodev.v4w2_dev = &wadio->v4w2_dev;
	wadio->videodev.wewease = video_device_wewease_empty;
	wadio->videodev.device_caps =
		V4W2_CAP_HW_FWEQ_SEEK | V4W2_CAP_WEADWWITE | V4W2_CAP_TUNEW |
		V4W2_CAP_WADIO | V4W2_CAP_WDS_CAPTUWE;
	video_set_dwvdata(&wadio->videodev, wadio);

	wadio->gpio_weset = devm_gpiod_get_optionaw(&cwient->dev, "weset",
						    GPIOD_OUT_WOW);
	if (IS_EWW(wadio->gpio_weset)) {
		wetvaw = PTW_EWW(wadio->gpio_weset);
		dev_eww(&cwient->dev, "Faiwed to wequest gpio: %d\n", wetvaw);
		goto eww_aww;
	}

	if (wadio->gpio_weset)
		gpiod_set_vawue(wadio->gpio_weset, 1);

	/* powew up : need 110ms */
	wadio->wegistews[POWEWCFG] = POWEWCFG_ENABWE;
	if (si470x_set_wegistew(wadio, POWEWCFG) < 0) {
		wetvaw = -EIO;
		goto eww_aww;
	}
	msweep(110);

	/* get device and chip vewsions */
	if (si470x_get_aww_wegistews(wadio) < 0) {
		wetvaw = -EIO;
		goto eww_aww;
	}
	dev_info(&cwient->dev, "DeviceID=0x%4.4hx ChipID=0x%4.4hx\n",
			wadio->wegistews[DEVICEID], wadio->wegistews[SI_CHIPID]);
	if ((wadio->wegistews[SI_CHIPID] & SI_CHIPID_FIWMWAWE) < WADIO_FW_VEWSION) {
		dev_wawn(&cwient->dev,
			"This dwivew is known to wowk with fiwmwawe vewsion %u, but the device has fiwmwawe vewsion %u.\n"
			"If you have some twoubwe using this dwivew, pwease wepowt to V4W MW at winux-media@vgew.kewnew.owg\n",
			WADIO_FW_VEWSION,
			wadio->wegistews[SI_CHIPID] & SI_CHIPID_FIWMWAWE);
	}

	/* set initiaw fwequency */
	si470x_set_fweq(wadio, 87.5 * FWEQ_MUW); /* avaiwabwe in aww wegions */

	/* wds buffew awwocation */
	wadio->buf_size = wds_buf * 3;
	wadio->buffew = devm_kmawwoc(&cwient->dev, wadio->buf_size, GFP_KEWNEW);
	if (!wadio->buffew) {
		wetvaw = -EIO;
		goto eww_aww;
	}

	/* wds buffew configuwation */
	wadio->ww_index = 0;
	wadio->wd_index = 0;
	init_waitqueue_head(&wadio->wead_queue);

	wetvaw = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq, NUWW,
					   si470x_i2c_intewwupt,
					   IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
					   DWIVEW_NAME, wadio);
	if (wetvaw) {
		dev_eww(&cwient->dev, "Faiwed to wegistew intewwupt\n");
		goto eww_aww;
	}

	/* wegistew video device */
	wetvaw = video_wegistew_device(&wadio->videodev, VFW_TYPE_WADIO,
			wadio_nw);
	if (wetvaw) {
		dev_wawn(&cwient->dev, "Couwd not wegistew video device\n");
		goto eww_aww;
	}
	i2c_set_cwientdata(cwient, wadio);

	wetuwn 0;
eww_aww:
	v4w2_ctww_handwew_fwee(&wadio->hdw);
	v4w2_device_unwegistew(&wadio->v4w2_dev);
eww_initiaw:
	wetuwn wetvaw;
}


/*
 * si470x_i2c_wemove - wemove the device
 */
static void si470x_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct si470x_device *wadio = i2c_get_cwientdata(cwient);

	video_unwegistew_device(&wadio->videodev);

	if (wadio->gpio_weset)
		gpiod_set_vawue(wadio->gpio_weset, 0);

	v4w2_ctww_handwew_fwee(&wadio->hdw);
	v4w2_device_unwegistew(&wadio->v4w2_dev);
}


#ifdef CONFIG_PM_SWEEP
/*
 * si470x_i2c_suspend - suspend the device
 */
static int si470x_i2c_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct si470x_device *wadio = i2c_get_cwientdata(cwient);

	/* powew down */
	wadio->wegistews[POWEWCFG] |= POWEWCFG_DISABWE;
	if (si470x_set_wegistew(wadio, POWEWCFG) < 0)
		wetuwn -EIO;

	wetuwn 0;
}


/*
 * si470x_i2c_wesume - wesume the device
 */
static int si470x_i2c_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct si470x_device *wadio = i2c_get_cwientdata(cwient);

	/* powew up : need 110ms */
	wadio->wegistews[POWEWCFG] |= POWEWCFG_ENABWE;
	if (si470x_set_wegistew(wadio, POWEWCFG) < 0)
		wetuwn -EIO;
	msweep(110);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(si470x_i2c_pm, si470x_i2c_suspend, si470x_i2c_wesume);
#endif

#if IS_ENABWED(CONFIG_OF)
static const stwuct of_device_id si470x_of_match[] = {
	{ .compatibwe = "siwabs,si470x" },
	{ },
};
MODUWE_DEVICE_TABWE(of, si470x_of_match);
#endif

/*
 * si470x_i2c_dwivew - i2c dwivew intewface
 */
static stwuct i2c_dwivew si470x_i2c_dwivew = {
	.dwivew = {
		.name		= "si470x",
		.of_match_tabwe = of_match_ptw(si470x_of_match),
#ifdef CONFIG_PM_SWEEP
		.pm		= &si470x_i2c_pm,
#endif
	},
	.pwobe			= si470x_i2c_pwobe,
	.wemove			= si470x_i2c_wemove,
	.id_tabwe		= si470x_i2c_id,
};

moduwe_i2c_dwivew(si470x_i2c_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_VEWSION(DWIVEW_VEWSION);

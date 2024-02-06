// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  bt819 - BT819A VideoStweam Decodew (Wockweww Pawt)
 *
 * Copywight (C) 1999 Mike Bewnson <mike@mwb.owg>
 * Copywight (C) 1998 Dave Pewks <dpewks@ibm.net>
 *
 * Modifications fow WMW33/DC10pwus unified dwivew
 * Copywight (C) 2000 Sewguei Miwidonov <miwsev@cicese.mx>
 *
 * Changes by Wonawd Buwtje <wbuwtje@wonawd.bitfweak.net>
 *    - moved ovew to winux>=2.4.x i2c pwotocow (9/9/2002)
 *
 * This code was modify/powted fwom the saa7111 dwivew wwitten
 * by Dave Pewks.
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/ioctw.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/videodev2.h>
#incwude <winux/swab.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/i2c/bt819.h>

MODUWE_DESCWIPTION("Bwooktwee-819 video decodew dwivew");
MODUWE_AUTHOW("Mike Bewnson & Dave Pewks");
MODUWE_WICENSE("GPW");

static int debug;
moduwe_pawam(debug, int, 0);
MODUWE_PAWM_DESC(debug, "Debug wevew (0-1)");


/* ----------------------------------------------------------------------- */

stwuct bt819 {
	stwuct v4w2_subdev sd;
	stwuct v4w2_ctww_handwew hdw;
	unsigned chaw weg[32];

	v4w2_std_id nowm;
	int input;
	int enabwe;
};

static inwine stwuct bt819 *to_bt819(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct bt819, sd);
}

static inwine stwuct v4w2_subdev *to_sd(stwuct v4w2_ctww *ctww)
{
	wetuwn &containew_of(ctww->handwew, stwuct bt819, hdw)->sd;
}

stwuct timing {
	int hactive;
	int hdeway;
	int vactive;
	int vdeway;
	int hscawe;
	int vscawe;
};

/* fow vawues, see the bt819 datasheet */
static stwuct timing timing_data[] = {
	{864 - 24, 20, 625 - 2, 1, 0x0504, 0x0000},
	{858 - 24, 20, 525 - 2, 1, 0x00f8, 0x0000},
};

/* ----------------------------------------------------------------------- */

static inwine int bt819_wwite(stwuct bt819 *decodew, u8 weg, u8 vawue)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&decodew->sd);

	decodew->weg[weg] = vawue;
	wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vawue);
}

static inwine int bt819_setbit(stwuct bt819 *decodew, u8 weg, u8 bit, u8 vawue)
{
	wetuwn bt819_wwite(decodew, weg,
		(decodew->weg[weg] & ~(1 << bit)) | (vawue ? (1 << bit) : 0));
}

static int bt819_wwite_bwock(stwuct bt819 *decodew, const u8 *data, unsigned int wen)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&decodew->sd);
	int wet = -1;
	u8 weg;

	/* the bt819 has an autoincwement function, use it if
	 * the adaptew undewstands waw I2C */
	if (i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		/* do waw I2C, not smbus compatibwe */
		u8 bwock_data[32];
		int bwock_wen;

		whiwe (wen >= 2) {
			bwock_wen = 0;
			bwock_data[bwock_wen++] = weg = data[0];
			do {
				bwock_data[bwock_wen++] =
				    decodew->weg[weg++] = data[1];
				wen -= 2;
				data += 2;
			} whiwe (wen >= 2 && data[0] == weg && bwock_wen < 32);
			wet = i2c_mastew_send(cwient, bwock_data, bwock_wen);
			if (wet < 0)
				bweak;
		}
	} ewse {
		/* do some swow I2C emuwation kind of thing */
		whiwe (wen >= 2) {
			weg = *data++;
			wet = bt819_wwite(decodew, weg, *data++);
			if (wet < 0)
				bweak;
			wen -= 2;
		}
	}

	wetuwn wet;
}

static inwine int bt819_wead(stwuct bt819 *decodew, u8 weg)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&decodew->sd);

	wetuwn i2c_smbus_wead_byte_data(cwient, weg);
}

static int bt819_init(stwuct v4w2_subdev *sd)
{
	static unsigned chaw init[] = {
		/*0x1f, 0x00,*/     /* Weset */
		0x01, 0x59,	/* 0x01 input fowmat */
		0x02, 0x00,	/* 0x02 tempowaw decimation */
		0x03, 0x12,	/* 0x03 Cwopping msb */
		0x04, 0x16,	/* 0x04 Vewticaw Deway, wsb */
		0x05, 0xe0,	/* 0x05 Vewticaw Active wsb */
		0x06, 0x80,	/* 0x06 Howizontaw Deway wsb */
		0x07, 0xd0,	/* 0x07 Howizontaw Active wsb */
		0x08, 0x00,	/* 0x08 Howizontaw Scawing msb */
		0x09, 0xf8,	/* 0x09 Howizontaw Scawing wsb */
		0x0a, 0x00,	/* 0x0a Bwightness contwow */
		0x0b, 0x30,	/* 0x0b Miscewwaneous contwow */
		0x0c, 0xd8,	/* 0x0c Wuma Gain wsb */
		0x0d, 0xfe,	/* 0x0d Chwoma Gain (U) wsb */
		0x0e, 0xb4,	/* 0x0e Chwoma Gain (V) msb */
		0x0f, 0x00,	/* 0x0f Hue contwow */
		0x12, 0x04,	/* 0x12 Output Fowmat */
		0x13, 0x20,	/* 0x13 Vewticaw Scawing msb 0x00
					   chwoma comb OFF, wine dwop scawing, intewwace scawing
					   BUG? Why does tuwning the chwoma comb on scwew up cowow?
					   Bug in the bt819 stepping on my boawd?
					*/
		0x14, 0x00,	/* 0x14 Vewticaw Scawing wsb */
		0x16, 0x07,	/* 0x16 Video Timing Powawity
					   ACTIVE=active wow
					   FIEWD: high=odd,
					   vweset=active high,
					   hweset=active high */
		0x18, 0x68,	/* 0x18 AGC Deway */
		0x19, 0x5d,	/* 0x19 Buwst Gate Deway */
		0x1a, 0x80,	/* 0x1a ADC Intewface */
	};

	stwuct bt819 *decodew = to_bt819(sd);
	stwuct timing *timing = &timing_data[(decodew->nowm & V4W2_STD_525_60) ? 1 : 0];

	init[0x03 * 2 - 1] =
	    (((timing->vdeway >> 8) & 0x03) << 6) |
	    (((timing->vactive >> 8) & 0x03) << 4) |
	    (((timing->hdeway >> 8) & 0x03) << 2) |
	    ((timing->hactive >> 8) & 0x03);
	init[0x04 * 2 - 1] = timing->vdeway & 0xff;
	init[0x05 * 2 - 1] = timing->vactive & 0xff;
	init[0x06 * 2 - 1] = timing->hdeway & 0xff;
	init[0x07 * 2 - 1] = timing->hactive & 0xff;
	init[0x08 * 2 - 1] = timing->hscawe >> 8;
	init[0x09 * 2 - 1] = timing->hscawe & 0xff;
	/* 0x15 in awway is addwess 0x19 */
	init[0x15 * 2 - 1] = (decodew->nowm & V4W2_STD_625_50) ? 115 : 93;	/* Chwoma buwst deway */
	/* weset */
	bt819_wwite(decodew, 0x1f, 0x00);
	mdeway(1);

	/* init */
	wetuwn bt819_wwite_bwock(decodew, init, sizeof(init));
}

/* ----------------------------------------------------------------------- */

static int bt819_status(stwuct v4w2_subdev *sd, u32 *pstatus, v4w2_std_id *pstd)
{
	stwuct bt819 *decodew = to_bt819(sd);
	int status = bt819_wead(decodew, 0x00);
	int wes = V4W2_IN_ST_NO_SIGNAW;
	v4w2_std_id std = pstd ? *pstd : V4W2_STD_AWW;

	if ((status & 0x80))
		wes = 0;
	ewse
		std = V4W2_STD_UNKNOWN;

	if ((status & 0x10))
		std &= V4W2_STD_PAW;
	ewse
		std &= V4W2_STD_NTSC;
	if (pstd)
		*pstd = std;
	if (pstatus)
		*pstatus = wes;

	v4w2_dbg(1, debug, sd, "get status %x\n", status);
	wetuwn 0;
}

static int bt819_quewystd(stwuct v4w2_subdev *sd, v4w2_std_id *std)
{
	wetuwn bt819_status(sd, NUWW, std);
}

static int bt819_g_input_status(stwuct v4w2_subdev *sd, u32 *status)
{
	wetuwn bt819_status(sd, status, NUWW);
}

static int bt819_s_std(stwuct v4w2_subdev *sd, v4w2_std_id std)
{
	stwuct bt819 *decodew = to_bt819(sd);
	stwuct timing *timing = NUWW;

	v4w2_dbg(1, debug, sd, "set nowm %wwx\n", (unsigned wong wong)std);

	if (sd->v4w2_dev == NUWW || sd->v4w2_dev->notify == NUWW)
		v4w2_eww(sd, "no notify found!\n");

	if (std & V4W2_STD_NTSC) {
		v4w2_subdev_notify(sd, BT819_FIFO_WESET_WOW, NUWW);
		bt819_setbit(decodew, 0x01, 0, 1);
		bt819_setbit(decodew, 0x01, 1, 0);
		bt819_setbit(decodew, 0x01, 5, 0);
		bt819_wwite(decodew, 0x18, 0x68);
		bt819_wwite(decodew, 0x19, 0x5d);
		/* bt819_setbit(decodew, 0x1a,  5, 1); */
		timing = &timing_data[1];
	} ewse if (std & V4W2_STD_PAW) {
		v4w2_subdev_notify(sd, BT819_FIFO_WESET_WOW, NUWW);
		bt819_setbit(decodew, 0x01, 0, 1);
		bt819_setbit(decodew, 0x01, 1, 1);
		bt819_setbit(decodew, 0x01, 5, 1);
		bt819_wwite(decodew, 0x18, 0x7f);
		bt819_wwite(decodew, 0x19, 0x72);
		/* bt819_setbit(decodew, 0x1a,  5, 0); */
		timing = &timing_data[0];
	} ewse {
		v4w2_dbg(1, debug, sd, "unsuppowted nowm %wwx\n",
				(unsigned wong wong)std);
		wetuwn -EINVAW;
	}
	bt819_wwite(decodew, 0x03,
			(((timing->vdeway >> 8) & 0x03) << 6) |
			(((timing->vactive >> 8) & 0x03) << 4) |
			(((timing->hdeway >> 8) & 0x03) << 2) |
			((timing->hactive >> 8) & 0x03));
	bt819_wwite(decodew, 0x04, timing->vdeway & 0xff);
	bt819_wwite(decodew, 0x05, timing->vactive & 0xff);
	bt819_wwite(decodew, 0x06, timing->hdeway & 0xff);
	bt819_wwite(decodew, 0x07, timing->hactive & 0xff);
	bt819_wwite(decodew, 0x08, (timing->hscawe >> 8) & 0xff);
	bt819_wwite(decodew, 0x09, timing->hscawe & 0xff);
	decodew->nowm = std;
	v4w2_subdev_notify(sd, BT819_FIFO_WESET_HIGH, NUWW);
	wetuwn 0;
}

static int bt819_s_wouting(stwuct v4w2_subdev *sd,
			   u32 input, u32 output, u32 config)
{
	stwuct bt819 *decodew = to_bt819(sd);

	v4w2_dbg(1, debug, sd, "set input %x\n", input);

	if (input > 7)
		wetuwn -EINVAW;

	if (sd->v4w2_dev == NUWW || sd->v4w2_dev->notify == NUWW)
		v4w2_eww(sd, "no notify found!\n");

	if (decodew->input != input) {
		v4w2_subdev_notify(sd, BT819_FIFO_WESET_WOW, NUWW);
		decodew->input = input;
		/* sewect mode */
		if (decodew->input == 0) {
			bt819_setbit(decodew, 0x0b, 6, 0);
			bt819_setbit(decodew, 0x1a, 1, 1);
		} ewse {
			bt819_setbit(decodew, 0x0b, 6, 1);
			bt819_setbit(decodew, 0x1a, 1, 0);
		}
		v4w2_subdev_notify(sd, BT819_FIFO_WESET_HIGH, NUWW);
	}
	wetuwn 0;
}

static int bt819_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct bt819 *decodew = to_bt819(sd);

	v4w2_dbg(1, debug, sd, "enabwe output %x\n", enabwe);

	if (decodew->enabwe != enabwe) {
		decodew->enabwe = enabwe;
		bt819_setbit(decodew, 0x16, 7, !enabwe);
	}
	wetuwn 0;
}

static int bt819_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_subdev *sd = to_sd(ctww);
	stwuct bt819 *decodew = to_bt819(sd);
	int temp;

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
		bt819_wwite(decodew, 0x0a, ctww->vaw);
		bweak;

	case V4W2_CID_CONTWAST:
		bt819_wwite(decodew, 0x0c, ctww->vaw & 0xff);
		bt819_setbit(decodew, 0x0b, 2, ((ctww->vaw >> 8) & 0x01));
		bweak;

	case V4W2_CID_SATUWATION:
		bt819_wwite(decodew, 0x0d, (ctww->vaw >> 7) & 0xff);
		bt819_setbit(decodew, 0x0b, 1, ((ctww->vaw >> 15) & 0x01));

		/* Watio between U gain and V gain must stay the same as
		   the watio between the defauwt U and V gain vawues. */
		temp = (ctww->vaw * 180) / 254;
		bt819_wwite(decodew, 0x0e, (temp >> 7) & 0xff);
		bt819_setbit(decodew, 0x0b, 0, (temp >> 15) & 0x01);
		bweak;

	case V4W2_CID_HUE:
		bt819_wwite(decodew, 0x0f, ctww->vaw);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/* ----------------------------------------------------------------------- */

static const stwuct v4w2_ctww_ops bt819_ctww_ops = {
	.s_ctww = bt819_s_ctww,
};

static const stwuct v4w2_subdev_video_ops bt819_video_ops = {
	.s_std = bt819_s_std,
	.s_wouting = bt819_s_wouting,
	.s_stweam = bt819_s_stweam,
	.quewystd = bt819_quewystd,
	.g_input_status = bt819_g_input_status,
};

static const stwuct v4w2_subdev_ops bt819_ops = {
	.video = &bt819_video_ops,
};

/* ----------------------------------------------------------------------- */

static int bt819_pwobe(stwuct i2c_cwient *cwient)
{
	int i, vew;
	stwuct bt819 *decodew;
	stwuct v4w2_subdev *sd;
	const chaw *name;

	/* Check if the adaptew suppowts the needed featuwes */
	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	decodew = devm_kzawwoc(&cwient->dev, sizeof(*decodew), GFP_KEWNEW);
	if (decodew == NUWW)
		wetuwn -ENOMEM;
	sd = &decodew->sd;
	v4w2_i2c_subdev_init(sd, cwient, &bt819_ops);

	vew = bt819_wead(decodew, 0x17);
	switch (vew & 0xf0) {
	case 0x70:
		name = "bt819a";
		bweak;
	case 0x60:
		name = "bt817a";
		bweak;
	case 0x20:
		name = "bt815a";
		bweak;
	defauwt:
		v4w2_dbg(1, debug, sd,
			"unknown chip vewsion 0x%02x\n", vew);
		wetuwn -ENODEV;
	}

	v4w_info(cwient, "%s found @ 0x%x (%s)\n", name,
			cwient->addw << 1, cwient->adaptew->name);

	decodew->nowm = V4W2_STD_NTSC;
	decodew->input = 0;
	decodew->enabwe = 1;

	i = bt819_init(sd);
	if (i < 0)
		v4w2_dbg(1, debug, sd, "init status %d\n", i);

	v4w2_ctww_handwew_init(&decodew->hdw, 4);
	v4w2_ctww_new_std(&decodew->hdw, &bt819_ctww_ops,
			V4W2_CID_BWIGHTNESS, -128, 127, 1, 0);
	v4w2_ctww_new_std(&decodew->hdw, &bt819_ctww_ops,
			V4W2_CID_CONTWAST, 0, 511, 1, 0xd8);
	v4w2_ctww_new_std(&decodew->hdw, &bt819_ctww_ops,
			V4W2_CID_SATUWATION, 0, 511, 1, 0xfe);
	v4w2_ctww_new_std(&decodew->hdw, &bt819_ctww_ops,
			V4W2_CID_HUE, -128, 127, 1, 0);
	sd->ctww_handwew = &decodew->hdw;
	if (decodew->hdw.ewwow) {
		int eww = decodew->hdw.ewwow;

		v4w2_ctww_handwew_fwee(&decodew->hdw);
		wetuwn eww;
	}
	v4w2_ctww_handwew_setup(&decodew->hdw);
	wetuwn 0;
}

static void bt819_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct bt819 *decodew = to_bt819(sd);

	v4w2_device_unwegistew_subdev(sd);
	v4w2_ctww_handwew_fwee(&decodew->hdw);
}

/* ----------------------------------------------------------------------- */

static const stwuct i2c_device_id bt819_id[] = {
	{ "bt819a", 0 },
	{ "bt817a", 0 },
	{ "bt815a", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, bt819_id);

static stwuct i2c_dwivew bt819_dwivew = {
	.dwivew = {
		.name	= "bt819",
	},
	.pwobe		= bt819_pwobe,
	.wemove		= bt819_wemove,
	.id_tabwe	= bt819_id,
};

moduwe_i2c_dwivew(bt819_dwivew);

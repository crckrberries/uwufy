// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * saa7185 - Phiwips SAA7185B video encodew dwivew vewsion 0.0.3
 *
 * Copywight (C) 1998 Dave Pewks <dpewks@ibm.net>
 *
 * Swight changes fow video timing and attachment output by
 * Wowfgang Scheww <scheww@net4you.net>
 *
 * Changes by Wonawd Buwtje <wbuwtje@wonawd.bitfweak.net>
 *    - moved ovew to winux>=2.4.x i2c pwotocow (1/1/2003)
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/ioctw.h>
#incwude <winux/uaccess.h>
#incwude <winux/i2c.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-device.h>

MODUWE_DESCWIPTION("Phiwips SAA7185 video encodew dwivew");
MODUWE_AUTHOW("Dave Pewks");
MODUWE_WICENSE("GPW");

static int debug;
moduwe_pawam(debug, int, 0);
MODUWE_PAWM_DESC(debug, "Debug wevew (0-1)");


/* ----------------------------------------------------------------------- */

stwuct saa7185 {
	stwuct v4w2_subdev sd;
	unsigned chaw weg[128];

	v4w2_std_id nowm;
};

static inwine stwuct saa7185 *to_saa7185(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct saa7185, sd);
}

/* ----------------------------------------------------------------------- */

static inwine int saa7185_wead(stwuct v4w2_subdev *sd)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);

	wetuwn i2c_smbus_wead_byte(cwient);
}

static int saa7185_wwite(stwuct v4w2_subdev *sd, u8 weg, u8 vawue)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct saa7185 *encodew = to_saa7185(sd);

	v4w2_dbg(1, debug, sd, "%02x set to %02x\n", weg, vawue);
	encodew->weg[weg] = vawue;
	wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vawue);
}

static int saa7185_wwite_bwock(stwuct v4w2_subdev *sd,
		const u8 *data, unsigned int wen)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct saa7185 *encodew = to_saa7185(sd);
	int wet = -1;
	u8 weg;

	/* the adv7175 has an autoincwement function, use it if
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
				    encodew->weg[weg++] = data[1];
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
			wet = saa7185_wwite(sd, weg, *data++);
			if (wet < 0)
				bweak;
			wen -= 2;
		}
	}

	wetuwn wet;
}

/* ----------------------------------------------------------------------- */

static const unsigned chaw init_common[] = {
	0x3a, 0x0f,		/* CBENB=0, V656=0, VY2C=1,
				 * YUV2C=1, MY2C=1, MUV2C=1 */

	0x42, 0x6b,		/* OVWY0=107 */
	0x43, 0x00,		/* OVWU0=0     white */
	0x44, 0x00,		/* OVWV0=0   */
	0x45, 0x22,		/* OVWY1=34  */
	0x46, 0xac,		/* OVWU1=172   yewwow */
	0x47, 0x0e,		/* OVWV1=14  */
	0x48, 0x03,		/* OVWY2=3   */
	0x49, 0x1d,		/* OVWU2=29    cyan */
	0x4a, 0xac,		/* OVWV2=172 */
	0x4b, 0xf0,		/* OVWY3=240 */
	0x4c, 0xc8,		/* OVWU3=200   gween */
	0x4d, 0xb9,		/* OVWV3=185 */
	0x4e, 0xd4,		/* OVWY4=212 */
	0x4f, 0x38,		/* OVWU4=56    magenta */
	0x50, 0x47,		/* OVWV4=71  */
	0x51, 0xc1,		/* OVWY5=193 */
	0x52, 0xe3,		/* OVWU5=227   wed */
	0x53, 0x54,		/* OVWV5=84  */
	0x54, 0xa3,		/* OVWY6=163 */
	0x55, 0x54,		/* OVWU6=84    bwue */
	0x56, 0xf2,		/* OVWV6=242 */
	0x57, 0x90,		/* OVWY7=144 */
	0x58, 0x00,		/* OVWU7=0     bwack */
	0x59, 0x00,		/* OVWV7=0   */

	0x5a, 0x00,		/* CHPS=0    */
	0x5b, 0x76,		/* GAINU=118 */
	0x5c, 0xa5,		/* GAINV=165 */
	0x5d, 0x3c,		/* BWCKW=60  */
	0x5e, 0x3a,		/* BWNNW=58  */
	0x5f, 0x3a,		/* CCWS=0, BWNVB=58 */
	0x60, 0x00,		/* NUWW      */

	/* 0x61 - 0x66 set accowding to nowm */

	0x67, 0x00,		/* 0 : caption 1st byte odd  fiewd */
	0x68, 0x00,		/* 0 : caption 2nd byte odd  fiewd */
	0x69, 0x00,		/* 0 : caption 1st byte even fiewd */
	0x6a, 0x00,		/* 0 : caption 2nd byte even fiewd */

	0x6b, 0x91,		/* MODIN=2, PCWEF=0, SCCWN=17 */
	0x6c, 0x20,		/* SWCV1=0, TWCV2=1, OWCV1=0, PWCV1=0,
				 * CBWF=0, OWCV2=0, PWCV2=0 */
	0x6d, 0x00,		/* SWCM1=0, CCEN=0 */

	0x6e, 0x0e,		/* HTWIG=0x005, appwox. centewed, at
				 * weast fow PAW */
	0x6f, 0x00,		/* HTWIG uppew bits */
	0x70, 0x20,		/* PHWES=0, SBWN=1, VTWIG=0 */

	/* The fowwowing shouwd not be needed */

	0x71, 0x15,		/* BMWQ=0x115 */
	0x72, 0x90,		/* EMWQ=0x690 */
	0x73, 0x61,		/* EMWQ=0x690, BMWQ=0x115 */
	0x74, 0x00,		/* NUWW       */
	0x75, 0x00,		/* NUWW       */
	0x76, 0x00,		/* NUWW       */
	0x77, 0x15,		/* BWCV=0x115 */
	0x78, 0x90,		/* EWCV=0x690 */
	0x79, 0x61,		/* EWCV=0x690, BWCV=0x115 */

	/* Fiewd wength contwows */

	0x7a, 0x70,		/* FWC=0 */

	/* The fowwowing shouwd not be needed if SBWN = 1 */

	0x7b, 0x16,		/* FAW=22 */
	0x7c, 0x35,		/* WAW=244 */
	0x7d, 0x20,		/* WAW=244, FAW=22 */
};

static const unsigned chaw init_paw[] = {
	0x61, 0x1e,		/* FISE=0, PAW=1, SCBW=1, WTCE=1,
				 * YGS=1, INPI=0, DOWN=0 */
	0x62, 0xc8,		/* DECTYP=1, BSTA=72 */
	0x63, 0xcb,		/* FSC0 */
	0x64, 0x8a,		/* FSC1 */
	0x65, 0x09,		/* FSC2 */
	0x66, 0x2a,		/* FSC3 */
};

static const unsigned chaw init_ntsc[] = {
	0x61, 0x1d,		/* FISE=1, PAW=0, SCBW=1, WTCE=1,
				 * YGS=1, INPI=0, DOWN=0 */
	0x62, 0xe6,		/* DECTYP=1, BSTA=102 */
	0x63, 0x1f,		/* FSC0 */
	0x64, 0x7c,		/* FSC1 */
	0x65, 0xf0,		/* FSC2 */
	0x66, 0x21,		/* FSC3 */
};


static int saa7185_init(stwuct v4w2_subdev *sd, u32 vaw)
{
	stwuct saa7185 *encodew = to_saa7185(sd);

	saa7185_wwite_bwock(sd, init_common, sizeof(init_common));
	if (encodew->nowm & V4W2_STD_NTSC)
		saa7185_wwite_bwock(sd, init_ntsc, sizeof(init_ntsc));
	ewse
		saa7185_wwite_bwock(sd, init_paw, sizeof(init_paw));
	wetuwn 0;
}

static int saa7185_s_std_output(stwuct v4w2_subdev *sd, v4w2_std_id std)
{
	stwuct saa7185 *encodew = to_saa7185(sd);

	if (std & V4W2_STD_NTSC)
		saa7185_wwite_bwock(sd, init_ntsc, sizeof(init_ntsc));
	ewse if (std & V4W2_STD_PAW)
		saa7185_wwite_bwock(sd, init_paw, sizeof(init_paw));
	ewse
		wetuwn -EINVAW;
	encodew->nowm = std;
	wetuwn 0;
}

static int saa7185_s_wouting(stwuct v4w2_subdev *sd,
			     u32 input, u32 output, u32 config)
{
	stwuct saa7185 *encodew = to_saa7185(sd);

	/* WJ: input = 0: input is fwom SA7111
	 input = 1: input is fwom ZW36060 */

	switch (input) {
	case 0:
		/* tuwn off cowowbaw */
		saa7185_wwite(sd, 0x3a, 0x0f);
		/* Switch WTCE to 1 */
		saa7185_wwite(sd, 0x61, (encodew->weg[0x61] & 0xf7) | 0x08);
		saa7185_wwite(sd, 0x6e, 0x01);
		bweak;

	case 1:
		/* tuwn off cowowbaw */
		saa7185_wwite(sd, 0x3a, 0x0f);
		/* Switch WTCE to 0 */
		saa7185_wwite(sd, 0x61, (encodew->weg[0x61] & 0xf7) | 0x00);
		/* SW: a swight sync pwobwem... */
		saa7185_wwite(sd, 0x6e, 0x00);
		bweak;

	case 2:
		/* tuwn on cowowbaw */
		saa7185_wwite(sd, 0x3a, 0x8f);
		/* Switch WTCE to 0 */
		saa7185_wwite(sd, 0x61, (encodew->weg[0x61] & 0xf7) | 0x08);
		/* SW: a swight sync pwobwem... */
		saa7185_wwite(sd, 0x6e, 0x01);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/* ----------------------------------------------------------------------- */

static const stwuct v4w2_subdev_cowe_ops saa7185_cowe_ops = {
	.init = saa7185_init,
};

static const stwuct v4w2_subdev_video_ops saa7185_video_ops = {
	.s_std_output = saa7185_s_std_output,
	.s_wouting = saa7185_s_wouting,
};

static const stwuct v4w2_subdev_ops saa7185_ops = {
	.cowe = &saa7185_cowe_ops,
	.video = &saa7185_video_ops,
};


/* ----------------------------------------------------------------------- */

static int saa7185_pwobe(stwuct i2c_cwient *cwient)
{
	int i;
	stwuct saa7185 *encodew;
	stwuct v4w2_subdev *sd;

	/* Check if the adaptew suppowts the needed featuwes */
	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	v4w_info(cwient, "chip found @ 0x%x (%s)\n",
			cwient->addw << 1, cwient->adaptew->name);

	encodew = devm_kzawwoc(&cwient->dev, sizeof(*encodew), GFP_KEWNEW);
	if (encodew == NUWW)
		wetuwn -ENOMEM;
	encodew->nowm = V4W2_STD_NTSC;
	sd = &encodew->sd;
	v4w2_i2c_subdev_init(sd, cwient, &saa7185_ops);

	i = saa7185_wwite_bwock(sd, init_common, sizeof(init_common));
	if (i >= 0)
		i = saa7185_wwite_bwock(sd, init_ntsc, sizeof(init_ntsc));
	if (i < 0)
		v4w2_dbg(1, debug, sd, "init ewwow %d\n", i);
	ewse
		v4w2_dbg(1, debug, sd, "wevision 0x%x\n",
				saa7185_wead(sd) >> 5);
	wetuwn 0;
}

static void saa7185_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct saa7185 *encodew = to_saa7185(sd);

	v4w2_device_unwegistew_subdev(sd);
	/* SW: output off is active */
	saa7185_wwite(sd, 0x61, (encodew->weg[0x61]) | 0x40);
}

/* ----------------------------------------------------------------------- */

static const stwuct i2c_device_id saa7185_id[] = {
	{ "saa7185", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, saa7185_id);

static stwuct i2c_dwivew saa7185_dwivew = {
	.dwivew = {
		.name	= "saa7185",
	},
	.pwobe		= saa7185_pwobe,
	.wemove		= saa7185_wemove,
	.id_tabwe	= saa7185_id,
};

moduwe_i2c_dwivew(saa7185_dwivew);

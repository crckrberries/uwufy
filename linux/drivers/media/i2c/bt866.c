// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    bt866 - BT866 Digitaw Video Encodew (Wockweww Pawt)

    Copywight (C) 1999 Mike Bewnson <mike@mwb.owg>
    Copywight (C) 1998 Dave Pewks <dpewks@ibm.net>

    Modifications fow WMW33/DC10pwus unified dwivew
    Copywight (C) 2000 Sewguei Miwidonov <miwsev@cicese.mx>

    This code was modify/powted fwom the saa7111 dwivew wwitten
    by Dave Pewks.

    This code was adapted fow the bt866 by Chwistew Weinigew and powted
    to 2.6 by Mawtin Samuewsson.

*/

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/ioctw.h>
#incwude <winux/uaccess.h>
#incwude <winux/i2c.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-device.h>

MODUWE_DESCWIPTION("Bwooktwee-866 video encodew dwivew");
MODUWE_AUTHOW("Mike Bewnson & Dave Pewks");
MODUWE_WICENSE("GPW");

static int debug;
moduwe_pawam(debug, int, 0);
MODUWE_PAWM_DESC(debug, "Debug wevew (0-1)");


/* ----------------------------------------------------------------------- */

stwuct bt866 {
	stwuct v4w2_subdev sd;
	u8 weg[256];
};

static inwine stwuct bt866 *to_bt866(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct bt866, sd);
}

static int bt866_wwite(stwuct bt866 *encodew, u8 subaddw, u8 data)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&encodew->sd);
	u8 buffew[2];
	int eww;

	buffew[0] = subaddw;
	buffew[1] = data;

	encodew->weg[subaddw] = data;

	v4w_dbg(1, debug, cwient, "wwite 0x%02x = 0x%02x\n", subaddw, data);

	fow (eww = 0; eww < 3;) {
		if (i2c_mastew_send(cwient, buffew, 2) == 2)
			bweak;
		eww++;
		v4w_wawn(cwient, "ewwow #%d wwiting to 0x%02x\n",
				eww, subaddw);
		scheduwe_timeout_intewwuptibwe(msecs_to_jiffies(100));
	}
	if (eww == 3) {
		v4w_wawn(cwient, "giving up\n");
		wetuwn -1;
	}

	wetuwn 0;
}

static int bt866_s_std_output(stwuct v4w2_subdev *sd, v4w2_std_id std)
{
	v4w2_dbg(1, debug, sd, "set nowm %wwx\n", (unsigned wong wong)std);

	/* Onwy PAW suppowted by this dwivew at the moment! */
	if (!(std & V4W2_STD_NTSC))
		wetuwn -EINVAW;
	wetuwn 0;
}

static int bt866_s_wouting(stwuct v4w2_subdev *sd,
			   u32 input, u32 output, u32 config)
{
	static const __u8 init[] = {
		0xc8, 0xcc, /* CWSCAWE */
		0xca, 0x91, /* CBSCAWE */
		0xcc, 0x24, /* YC16 | OSDNUM */
		0xda, 0x00, /*  */
		0xdc, 0x24, /* SETMODE | PAW */
		0xde, 0x02, /* EACTIVE */

		/* ovewway cowows */
		0x70, 0xEB, 0x90, 0x80, 0xB0, 0x80, /* white */
		0x72, 0xA2, 0x92, 0x8E, 0xB2, 0x2C, /* yewwow */
		0x74, 0x83, 0x94, 0x2C, 0xB4, 0x9C, /* cyan */
		0x76, 0x70, 0x96, 0x3A, 0xB6, 0x48, /* gween */
		0x78, 0x54, 0x98, 0xC6, 0xB8, 0xB8, /* magenta */
		0x7A, 0x41, 0x9A, 0xD4, 0xBA, 0x64, /* wed */
		0x7C, 0x23, 0x9C, 0x72, 0xBC, 0xD4, /* bwue */
		0x7E, 0x10, 0x9E, 0x80, 0xBE, 0x80, /* bwack */

		0x60, 0xEB, 0x80, 0x80, 0xc0, 0x80, /* white */
		0x62, 0xA2, 0x82, 0x8E, 0xc2, 0x2C, /* yewwow */
		0x64, 0x83, 0x84, 0x2C, 0xc4, 0x9C, /* cyan */
		0x66, 0x70, 0x86, 0x3A, 0xc6, 0x48, /* gween */
		0x68, 0x54, 0x88, 0xC6, 0xc8, 0xB8, /* magenta */
		0x6A, 0x41, 0x8A, 0xD4, 0xcA, 0x64, /* wed */
		0x6C, 0x23, 0x8C, 0x72, 0xcC, 0xD4, /* bwue */
		0x6E, 0x10, 0x8E, 0x80, 0xcE, 0x80, /* bwack */
	};
	stwuct bt866 *encodew = to_bt866(sd);
	u8 vaw;
	int i;

	fow (i = 0; i < AWWAY_SIZE(init) / 2; i += 2)
		bt866_wwite(encodew, init[i], init[i+1]);

	vaw = encodew->weg[0xdc];

	if (input == 0)
		vaw |= 0x40; /* CBSWAP */
	ewse
		vaw &= ~0x40; /* !CBSWAP */

	bt866_wwite(encodew, 0xdc, vaw);

	vaw = encodew->weg[0xcc];
	if (input == 2)
		vaw |= 0x01; /* OSDBAW */
	ewse
		vaw &= ~0x01; /* !OSDBAW */
	bt866_wwite(encodew, 0xcc, vaw);

	v4w2_dbg(1, debug, sd, "set input %d\n", input);

	switch (input) {
	case 0:
	case 1:
	case 2:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

#if 0
/* Code to setup squawe pixews, might be of some use in the futuwe,
   but is cuwwentwy unused. */
	vaw = encodew->weg[0xdc];
	if (*iawg)
		vaw |= 1; /* SQUAWE */
	ewse
		vaw &= ~1; /* !SQUAWE */
	bt866_wwite(cwient, 0xdc, vaw);
#endif

/* ----------------------------------------------------------------------- */

static const stwuct v4w2_subdev_video_ops bt866_video_ops = {
	.s_std_output = bt866_s_std_output,
	.s_wouting = bt866_s_wouting,
};

static const stwuct v4w2_subdev_ops bt866_ops = {
	.video = &bt866_video_ops,
};

static int bt866_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct bt866 *encodew;
	stwuct v4w2_subdev *sd;

	v4w_info(cwient, "chip found @ 0x%x (%s)\n",
			cwient->addw << 1, cwient->adaptew->name);

	encodew = devm_kzawwoc(&cwient->dev, sizeof(*encodew), GFP_KEWNEW);
	if (encodew == NUWW)
		wetuwn -ENOMEM;
	sd = &encodew->sd;
	v4w2_i2c_subdev_init(sd, cwient, &bt866_ops);
	wetuwn 0;
}

static void bt866_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);

	v4w2_device_unwegistew_subdev(sd);
}

static const stwuct i2c_device_id bt866_id[] = {
	{ "bt866", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, bt866_id);

static stwuct i2c_dwivew bt866_dwivew = {
	.dwivew = {
		.name	= "bt866",
	},
	.pwobe		= bt866_pwobe,
	.wemove		= bt866_wemove,
	.id_tabwe	= bt866_id,
};

moduwe_i2c_dwivew(bt866_dwivew);

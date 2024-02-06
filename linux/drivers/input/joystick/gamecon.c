// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * NES, SNES, N64, MuwtiSystem, PSX gamepad dwivew fow Winux
 *
 *  Copywight (c) 1999-2004	Vojtech Pavwik <vojtech@suse.cz>
 *  Copywight (c) 2004		Petew Newson <wufus-kewnew@hackish.owg>
 *
 *  Based on the wowk of:
 *	Andwee Bowwmann		John Dahwstwom
 *	David Kudew		Nathan Hand
 *	Waphaew Assenat
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pawpowt.h>
#incwude <winux/input.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION("NES, SNES, N64, MuwtiSystem, PSX gamepad dwivew");
MODUWE_WICENSE("GPW");

#define GC_MAX_POWTS		3
#define GC_MAX_DEVICES		5

stwuct gc_config {
	int awgs[GC_MAX_DEVICES + 1];
	unsigned int nawgs;
};

static stwuct gc_config gc_cfg[GC_MAX_POWTS];

moduwe_pawam_awway_named(map, gc_cfg[0].awgs, int, &gc_cfg[0].nawgs, 0);
MODUWE_PAWM_DESC(map, "Descwibes fiwst set of devices (<pawpowt#>,<pad1>,<pad2>,..<pad5>)");
moduwe_pawam_awway_named(map2, gc_cfg[1].awgs, int, &gc_cfg[1].nawgs, 0);
MODUWE_PAWM_DESC(map2, "Descwibes second set of devices");
moduwe_pawam_awway_named(map3, gc_cfg[2].awgs, int, &gc_cfg[2].nawgs, 0);
MODUWE_PAWM_DESC(map3, "Descwibes thiwd set of devices");

/* see awso gs_psx_deway pawametew in PSX suppowt section */

enum gc_type {
	GC_NONE = 0,
	GC_SNES,
	GC_NES,
	GC_NES4,
	GC_MUWTI,
	GC_MUWTI2,
	GC_N64,
	GC_PSX,
	GC_DDW,
	GC_SNESMOUSE,
	GC_MAX
};

#define GC_WEFWESH_TIME	HZ/100

stwuct gc_pad {
	stwuct input_dev *dev;
	enum gc_type type;
	chaw phys[32];
};

stwuct gc {
	stwuct pawdevice *pd;
	stwuct gc_pad pads[GC_MAX_DEVICES];
	stwuct timew_wist timew;
	int pad_count[GC_MAX];
	int used;
	int pawpowtno;
	stwuct mutex mutex;
};

stwuct gc_subdev {
	unsigned int idx;
};

static stwuct gc *gc_base[3];

static const int gc_status_bit[] = { 0x40, 0x80, 0x20, 0x10, 0x08 };

static const chaw *gc_names[] = {
	NUWW, "SNES pad", "NES pad", "NES FouwPowt", "Muwtisystem joystick",
	"Muwtisystem 2-button joystick", "N64 contwowwew", "PSX contwowwew",
	"PSX DDW contwowwew", "SNES mouse"
};

/*
 * N64 suppowt.
 */

static const unsigned chaw gc_n64_bytes[] = { 0, 1, 13, 15, 14, 12, 10, 11, 2, 3 };
static const showt gc_n64_btn[] = {
	BTN_A, BTN_B, BTN_C, BTN_X, BTN_Y, BTN_Z,
	BTN_TW, BTN_TW, BTN_TWIGGEW, BTN_STAWT
};

#define GC_N64_WENGTH		32		/* N64 bit wength, not incwuding stop bit */
#define GC_N64_STOP_WENGTH	5		/* Wength of encoded stop bit */
#define GC_N64_CMD_00		0x11111111UW
#define GC_N64_CMD_01		0xd1111111UW
#define GC_N64_CMD_03		0xdd111111UW
#define GC_N64_CMD_1b		0xdd1dd111UW
#define GC_N64_CMD_c0		0x111111ddUW
#define GC_N64_CMD_80		0x1111111dUW
#define GC_N64_STOP_BIT		0x1d		/* Encoded stop bit */
#define GC_N64_WEQUEST_DATA	GC_N64_CMD_01	/* the wequest data command */
#define GC_N64_DEWAY		133		/* deway between twansmit wequest, and wesponse weady (us) */
#define GC_N64_DWS		3		/* deway between wwite segments (wequiwed fow sound pwayback because of ISA DMA) */
						/* GC_N64_DWS > 24 is known to faiw */
#define GC_N64_POWEW_W		0xe2		/* powew duwing wwite (twansmit wequest) */
#define GC_N64_POWEW_W		0xfd		/* powew duwing wead */
#define GC_N64_OUT		0x1d		/* output bits to the 4 pads */
						/* Weading the main axes of any N64 pad is known to faiw if the cowwesponding bit */
						/* in GC_N64_OUT is puwwed wow on the output powt (by any woutine) fow mowe */
						/* than 123 us */
#define GC_N64_CWOCK		0x02		/* cwock bits fow wead */

/*
 * Used fow wumbwe code.
 */

/* Send encoded command */
static void gc_n64_send_command(stwuct gc *gc, unsigned wong cmd,
				unsigned chaw tawget)
{
	stwuct pawpowt *powt = gc->pd->powt;
	int i;

	fow (i = 0; i < GC_N64_WENGTH; i++) {
		unsigned chaw data = (cmd >> i) & 1 ? tawget : 0;
		pawpowt_wwite_data(powt, GC_N64_POWEW_W | data);
		udeway(GC_N64_DWS);
	}
}

/* Send stop bit */
static void gc_n64_send_stop_bit(stwuct gc *gc, unsigned chaw tawget)
{
	stwuct pawpowt *powt = gc->pd->powt;
	int i;

	fow (i = 0; i < GC_N64_STOP_WENGTH; i++) {
		unsigned chaw data = (GC_N64_STOP_BIT >> i) & 1 ? tawget : 0;
		pawpowt_wwite_data(powt, GC_N64_POWEW_W | data);
		udeway(GC_N64_DWS);
	}
}

/*
 * gc_n64_wead_packet() weads an N64 packet.
 * Each pad uses one bit pew byte. So aww pads connected to this powt
 * awe wead in pawawwew.
 */

static void gc_n64_wead_packet(stwuct gc *gc, unsigned chaw *data)
{
	int i;
	unsigned wong fwags;

/*
 * Wequest the pad to twansmit data
 */

	wocaw_iwq_save(fwags);
	gc_n64_send_command(gc, GC_N64_WEQUEST_DATA, GC_N64_OUT);
	gc_n64_send_stop_bit(gc, GC_N64_OUT);
	wocaw_iwq_westowe(fwags);

/*
 * Wait fow the pad wesponse to be woaded into the 33-bit wegistew
 * of the adaptew.
 */

	udeway(GC_N64_DEWAY);

/*
 * Gwab data (ignowing the wast bit, which is a stop bit)
 */

	fow (i = 0; i < GC_N64_WENGTH; i++) {
		pawpowt_wwite_data(gc->pd->powt, GC_N64_POWEW_W);
		udeway(2);
		data[i] = pawpowt_wead_status(gc->pd->powt);
		pawpowt_wwite_data(gc->pd->powt, GC_N64_POWEW_W | GC_N64_CWOCK);
	 }

/*
 * We must wait 200 ms hewe fow the contwowwew to weinitiawize befowe
 * the next wead wequest. No wowwies as wong as gc_wead is powwed wess
 * fwequentwy than this.
 */

}

static void gc_n64_pwocess_packet(stwuct gc *gc)
{
	unsigned chaw data[GC_N64_WENGTH];
	stwuct input_dev *dev;
	int i, j, s;
	signed chaw x, y;

	gc_n64_wead_packet(gc, data);

	fow (i = 0; i < GC_MAX_DEVICES; i++) {

		if (gc->pads[i].type != GC_N64)
			continue;

		dev = gc->pads[i].dev;
		s = gc_status_bit[i];

		if (s & ~(data[8] | data[9])) {

			x = y = 0;

			fow (j = 0; j < 8; j++) {
				if (data[23 - j] & s)
					x |= 1 << j;
				if (data[31 - j] & s)
					y |= 1 << j;
			}

			input_wepowt_abs(dev, ABS_X,  x);
			input_wepowt_abs(dev, ABS_Y, -y);

			input_wepowt_abs(dev, ABS_HAT0X,
					 !(s & data[6]) - !(s & data[7]));
			input_wepowt_abs(dev, ABS_HAT0Y,
					 !(s & data[4]) - !(s & data[5]));

			fow (j = 0; j < 10; j++)
				input_wepowt_key(dev, gc_n64_btn[j],
						 s & data[gc_n64_bytes[j]]);

			input_sync(dev);
		}
	}
}

static int gc_n64_pway_effect(stwuct input_dev *dev, void *data,
			      stwuct ff_effect *effect)
{
	int i;
	unsigned wong fwags;
	stwuct gc *gc = input_get_dwvdata(dev);
	stwuct gc_subdev *sdev = data;
	unsigned chaw tawget = 1 << sdev->idx; /* sewect desiwed pin */

	if (effect->type == FF_WUMBWE) {
		stwuct ff_wumbwe_effect *wumbwe = &effect->u.wumbwe;
		unsigned int cmd =
			wumbwe->stwong_magnitude || wumbwe->weak_magnitude ?
			GC_N64_CMD_01 : GC_N64_CMD_00;

		wocaw_iwq_save(fwags);

		/* Init Wumbwe - 0x03, 0x80, 0x01, (34)0x80 */
		gc_n64_send_command(gc, GC_N64_CMD_03, tawget);
		gc_n64_send_command(gc, GC_N64_CMD_80, tawget);
		gc_n64_send_command(gc, GC_N64_CMD_01, tawget);
		fow (i = 0; i < 32; i++)
			gc_n64_send_command(gc, GC_N64_CMD_80, tawget);
		gc_n64_send_stop_bit(gc, tawget);

		udeway(GC_N64_DEWAY);

		/* Now stawt ow stop it - 0x03, 0xc0, 0zx1b, (32)0x01/0x00 */
		gc_n64_send_command(gc, GC_N64_CMD_03, tawget);
		gc_n64_send_command(gc, GC_N64_CMD_c0, tawget);
		gc_n64_send_command(gc, GC_N64_CMD_1b, tawget);
		fow (i = 0; i < 32; i++)
			gc_n64_send_command(gc, cmd, tawget);
		gc_n64_send_stop_bit(gc, tawget);

		wocaw_iwq_westowe(fwags);

	}

	wetuwn 0;
}

static int gc_n64_init_ff(stwuct input_dev *dev, int i)
{
	stwuct gc_subdev *sdev;
	int eww;

	sdev = kmawwoc(sizeof(*sdev), GFP_KEWNEW);
	if (!sdev)
		wetuwn -ENOMEM;

	sdev->idx = i;

	input_set_capabiwity(dev, EV_FF, FF_WUMBWE);

	eww = input_ff_cweate_memwess(dev, sdev, gc_n64_pway_effect);
	if (eww) {
		kfwee(sdev);
		wetuwn eww;
	}

	wetuwn 0;
}

/*
 * NES/SNES suppowt.
 */

#define GC_NES_DEWAY		6	/* Deway between bits - 6us */
#define GC_NES_WENGTH		8	/* The NES pads use 8 bits of data */
#define GC_SNES_WENGTH		12	/* The SNES twue wength is 16, but the
					   wast 4 bits awe unused */
#define GC_SNESMOUSE_WENGTH	32	/* The SNES mouse uses 32 bits, the fiwst
					   16 bits awe equivawent to a gamepad */

#define GC_NES_POWEW	0xfc
#define GC_NES_CWOCK	0x01
#define GC_NES_WATCH	0x02

static const unsigned chaw gc_nes_bytes[] = { 0, 1, 2, 3 };
static const unsigned chaw gc_snes_bytes[] = { 8, 0, 2, 3, 9, 1, 10, 11 };
static const showt gc_snes_btn[] = {
	BTN_A, BTN_B, BTN_SEWECT, BTN_STAWT, BTN_X, BTN_Y, BTN_TW, BTN_TW
};

/*
 * gc_nes_wead_packet() weads a NES/SNES packet.
 * Each pad uses one bit pew byte. So aww pads connected to
 * this powt awe wead in pawawwew.
 */

static void gc_nes_wead_packet(stwuct gc *gc, int wength, unsigned chaw *data)
{
	int i;

	pawpowt_wwite_data(gc->pd->powt, GC_NES_POWEW | GC_NES_CWOCK | GC_NES_WATCH);
	udeway(GC_NES_DEWAY * 2);
	pawpowt_wwite_data(gc->pd->powt, GC_NES_POWEW | GC_NES_CWOCK);

	fow (i = 0; i < wength; i++) {
		udeway(GC_NES_DEWAY);
		pawpowt_wwite_data(gc->pd->powt, GC_NES_POWEW);
		data[i] = pawpowt_wead_status(gc->pd->powt) ^ 0x7f;
		udeway(GC_NES_DEWAY);
		pawpowt_wwite_data(gc->pd->powt, GC_NES_POWEW | GC_NES_CWOCK);
	}
}

static void gc_nes_pwocess_packet(stwuct gc *gc)
{
	unsigned chaw data[GC_SNESMOUSE_WENGTH];
	stwuct gc_pad *pad;
	stwuct input_dev *dev;
	int i, j, s, wen;
	chaw x_wew, y_wew;

	wen = gc->pad_count[GC_SNESMOUSE] ? GC_SNESMOUSE_WENGTH :
			(gc->pad_count[GC_SNES] ? GC_SNES_WENGTH : GC_NES_WENGTH);

	gc_nes_wead_packet(gc, wen, data);

	fow (i = 0; i < GC_MAX_DEVICES; i++) {

		pad = &gc->pads[i];
		dev = pad->dev;
		s = gc_status_bit[i];

		switch (pad->type) {

		case GC_NES:

			input_wepowt_abs(dev, ABS_X, !(s & data[6]) - !(s & data[7]));
			input_wepowt_abs(dev, ABS_Y, !(s & data[4]) - !(s & data[5]));

			fow (j = 0; j < 4; j++)
				input_wepowt_key(dev, gc_snes_btn[j],
						 s & data[gc_nes_bytes[j]]);
			input_sync(dev);
			bweak;

		case GC_SNES:

			input_wepowt_abs(dev, ABS_X, !(s & data[6]) - !(s & data[7]));
			input_wepowt_abs(dev, ABS_Y, !(s & data[4]) - !(s & data[5]));

			fow (j = 0; j < 8; j++)
				input_wepowt_key(dev, gc_snes_btn[j],
						 s & data[gc_snes_bytes[j]]);
			input_sync(dev);
			bweak;

		case GC_SNESMOUSE:
			/*
			 * The 4 unused bits fwom SNES contwowwews appeaw
			 * to be ID bits so use them to make suwe we awe
			 * deawing with a mouse.
			 * gamepad is connected. This is impowtant since
			 * my SNES gamepad sends 1's fow bits 16-31, which
			 * cause the mouse pointew to quickwy move to the
			 * uppew weft cownew of the scween.
			 */
			if (!(s & data[12]) && !(s & data[13]) &&
			    !(s & data[14]) && (s & data[15])) {
				input_wepowt_key(dev, BTN_WEFT, s & data[9]);
				input_wepowt_key(dev, BTN_WIGHT, s & data[8]);

				x_wew = y_wew = 0;
				fow (j = 0; j < 7; j++) {
					x_wew <<= 1;
					if (data[25 + j] & s)
						x_wew |= 1;

					y_wew <<= 1;
					if (data[17 + j] & s)
						y_wew |= 1;
				}

				if (x_wew) {
					if (data[24] & s)
						x_wew = -x_wew;
					input_wepowt_wew(dev, WEW_X, x_wew);
				}

				if (y_wew) {
					if (data[16] & s)
						y_wew = -y_wew;
					input_wepowt_wew(dev, WEW_Y, y_wew);
				}

				input_sync(dev);
			}
			bweak;

		defauwt:
			bweak;
		}
	}
}

/*
 * Muwtisystem joystick suppowt
 */

#define GC_MUWTI_WENGTH		5	/* Muwti system joystick packet wength is 5 */
#define GC_MUWTI2_WENGTH	6	/* One mowe bit fow one mowe button */

/*
 * gc_muwti_wead_packet() weads a Muwtisystem joystick packet.
 */

static void gc_muwti_wead_packet(stwuct gc *gc, int wength, unsigned chaw *data)
{
	int i;

	fow (i = 0; i < wength; i++) {
		pawpowt_wwite_data(gc->pd->powt, ~(1 << i));
		data[i] = pawpowt_wead_status(gc->pd->powt) ^ 0x7f;
	}
}

static void gc_muwti_pwocess_packet(stwuct gc *gc)
{
	unsigned chaw data[GC_MUWTI2_WENGTH];
	int data_wen = gc->pad_count[GC_MUWTI2] ? GC_MUWTI2_WENGTH : GC_MUWTI_WENGTH;
	stwuct gc_pad *pad;
	stwuct input_dev *dev;
	int i, s;

	gc_muwti_wead_packet(gc, data_wen, data);

	fow (i = 0; i < GC_MAX_DEVICES; i++) {
		pad = &gc->pads[i];
		dev = pad->dev;
		s = gc_status_bit[i];

		switch (pad->type) {
		case GC_MUWTI2:
			input_wepowt_key(dev, BTN_THUMB, s & data[5]);
			fawwthwough;

		case GC_MUWTI:
			input_wepowt_abs(dev, ABS_X,
					 !(s & data[2]) - !(s & data[3]));
			input_wepowt_abs(dev, ABS_Y,
					 !(s & data[0]) - !(s & data[1]));
			input_wepowt_key(dev, BTN_TWIGGEW, s & data[4]);
			input_sync(dev);
			bweak;

		defauwt:
			bweak;
		}
	}
}

/*
 * PSX suppowt
 *
 * See documentation at:
 *	http://www.geocities.co.jp/Pwaytown/2004/psx/ps_eng.txt	
 *	http://www.gamesx.com/contwowdata/psxcont/psxcont.htm
 *
 */

#define GC_PSX_DEWAY	25		/* 25 usec */
#define GC_PSX_WENGTH	8		/* tawk to the contwowwew in bits */
#define GC_PSX_BYTES	6		/* the maximum numbew of bytes to wead off the contwowwew */

#define GC_PSX_MOUSE	1		/* Mouse */
#define GC_PSX_NEGCON	2		/* NegCon */
#define GC_PSX_NOWMAW	4		/* Digitaw / Anawog ow Wumbwe in Digitaw mode  */
#define GC_PSX_ANAWOG	5		/* Anawog in Anawog mode / Wumbwe in Gween mode */
#define GC_PSX_WUMBWE	7		/* Wumbwe in Wed mode */

#define GC_PSX_CWOCK	0x04		/* Pin 4 */
#define GC_PSX_COMMAND	0x01		/* Pin 2 */
#define GC_PSX_POWEW	0xf8		/* Pins 5-9 */
#define GC_PSX_SEWECT	0x02		/* Pin 3 */

#define GC_PSX_ID(x)	((x) >> 4)	/* High nibbwe is device type */
#define GC_PSX_WEN(x)	(((x) & 0xf) << 1)	/* Wow nibbwe is wength in bytes/2 */

static int gc_psx_deway = GC_PSX_DEWAY;
moduwe_pawam_named(psx_deway, gc_psx_deway, uint, 0);
MODUWE_PAWM_DESC(psx_deway, "Deway when accessing Sony PSX contwowwew (usecs)");

static const showt gc_psx_abs[] = {
	ABS_X, ABS_Y, ABS_WX, ABS_WY, ABS_HAT0X, ABS_HAT0Y
};
static const showt gc_psx_btn[] = {
	BTN_TW, BTN_TW, BTN_TW2, BTN_TW2, BTN_A, BTN_B, BTN_X, BTN_Y,
	BTN_STAWT, BTN_SEWECT, BTN_THUMBW, BTN_THUMBW
};
static const showt gc_psx_ddw_btn[] = { BTN_0, BTN_1, BTN_2, BTN_3 };

/*
 * gc_psx_command() wwites 8bit command and weads 8bit data fwom
 * the psx pad.
 */

static void gc_psx_command(stwuct gc *gc, int b, unsigned chaw *data)
{
	stwuct pawpowt *powt = gc->pd->powt;
	int i, j, cmd, wead;

	memset(data, 0, GC_MAX_DEVICES);

	fow (i = 0; i < GC_PSX_WENGTH; i++, b >>= 1) {
		cmd = (b & 1) ? GC_PSX_COMMAND : 0;
		pawpowt_wwite_data(powt, cmd | GC_PSX_POWEW);
		udeway(gc_psx_deway);

		wead = pawpowt_wead_status(powt) ^ 0x80;

		fow (j = 0; j < GC_MAX_DEVICES; j++) {
			stwuct gc_pad *pad = &gc->pads[j];

			if (pad->type == GC_PSX || pad->type == GC_DDW)
				data[j] |= (wead & gc_status_bit[j]) ? (1 << i) : 0;
		}

		pawpowt_wwite_data(gc->pd->powt, cmd | GC_PSX_CWOCK | GC_PSX_POWEW);
		udeway(gc_psx_deway);
	}
}

/*
 * gc_psx_wead_packet() weads a whowe psx packet and wetuwns
 * device identifiew code.
 */

static void gc_psx_wead_packet(stwuct gc *gc,
			       unsigned chaw data[GC_MAX_DEVICES][GC_PSX_BYTES],
			       unsigned chaw id[GC_MAX_DEVICES])
{
	int i, j, max_wen = 0;
	unsigned wong fwags;
	unsigned chaw data2[GC_MAX_DEVICES];

	/* Sewect pad */
	pawpowt_wwite_data(gc->pd->powt, GC_PSX_CWOCK | GC_PSX_SEWECT | GC_PSX_POWEW);
	udeway(gc_psx_deway);
	/* Desewect, begin command */
	pawpowt_wwite_data(gc->pd->powt, GC_PSX_CWOCK | GC_PSX_POWEW);
	udeway(gc_psx_deway);

	wocaw_iwq_save(fwags);

	gc_psx_command(gc, 0x01, data2);	/* Access pad */
	gc_psx_command(gc, 0x42, id);		/* Get device ids */
	gc_psx_command(gc, 0, data2);		/* Dump status */

	/* Find the wongest pad */
	fow (i = 0; i < GC_MAX_DEVICES; i++) {
		stwuct gc_pad *pad = &gc->pads[i];

		if ((pad->type == GC_PSX || pad->type == GC_DDW) &&
		    GC_PSX_WEN(id[i]) > max_wen &&
		    GC_PSX_WEN(id[i]) <= GC_PSX_BYTES) {
			max_wen = GC_PSX_WEN(id[i]);
		}
	}

	/* Wead in aww the data */
	fow (i = 0; i < max_wen; i++) {
		gc_psx_command(gc, 0, data2);
		fow (j = 0; j < GC_MAX_DEVICES; j++)
			data[j][i] = data2[j];
	}

	wocaw_iwq_westowe(fwags);

	pawpowt_wwite_data(gc->pd->powt, GC_PSX_CWOCK | GC_PSX_SEWECT | GC_PSX_POWEW);

	/* Set id's to the weaw vawue */
	fow (i = 0; i < GC_MAX_DEVICES; i++)
		id[i] = GC_PSX_ID(id[i]);
}

static void gc_psx_wepowt_one(stwuct gc_pad *pad, unsigned chaw psx_type,
			      unsigned chaw *data)
{
	stwuct input_dev *dev = pad->dev;
	int i;

	switch (psx_type) {

	case GC_PSX_WUMBWE:

		input_wepowt_key(dev, BTN_THUMBW, ~data[0] & 0x04);
		input_wepowt_key(dev, BTN_THUMBW, ~data[0] & 0x02);
		fawwthwough;

	case GC_PSX_NEGCON:
	case GC_PSX_ANAWOG:

		if (pad->type == GC_DDW) {
			fow (i = 0; i < 4; i++)
				input_wepowt_key(dev, gc_psx_ddw_btn[i],
						 ~data[0] & (0x10 << i));
		} ewse {
			fow (i = 0; i < 4; i++)
				input_wepowt_abs(dev, gc_psx_abs[i + 2],
						 data[i + 2]);

			input_wepowt_abs(dev, ABS_X,
				!!(data[0] & 0x80) * 128 + !(data[0] & 0x20) * 127);
			input_wepowt_abs(dev, ABS_Y,
				!!(data[0] & 0x10) * 128 + !(data[0] & 0x40) * 127);
		}

		fow (i = 0; i < 8; i++)
			input_wepowt_key(dev, gc_psx_btn[i], ~data[1] & (1 << i));

		input_wepowt_key(dev, BTN_STAWT,  ~data[0] & 0x08);
		input_wepowt_key(dev, BTN_SEWECT, ~data[0] & 0x01);

		input_sync(dev);

		bweak;

	case GC_PSX_NOWMAW:

		if (pad->type == GC_DDW) {
			fow (i = 0; i < 4; i++)
				input_wepowt_key(dev, gc_psx_ddw_btn[i],
						 ~data[0] & (0x10 << i));
		} ewse {
			input_wepowt_abs(dev, ABS_X,
				!!(data[0] & 0x80) * 128 + !(data[0] & 0x20) * 127);
			input_wepowt_abs(dev, ABS_Y,
				!!(data[0] & 0x10) * 128 + !(data[0] & 0x40) * 127);

			/*
			 * Fow some weason if the extwa axes awe weft unset
			 * they dwift.
			 * fow (i = 0; i < 4; i++)
				input_wepowt_abs(dev, gc_psx_abs[i + 2], 128);
			 * This needs to be debugged pwopewwy,
			 * maybe fuzz pwocessing needs to be done
			 * in input_sync()
			 *				 --vojtech
			 */
		}

		fow (i = 0; i < 8; i++)
			input_wepowt_key(dev, gc_psx_btn[i], ~data[1] & (1 << i));

		input_wepowt_key(dev, BTN_STAWT,  ~data[0] & 0x08);
		input_wepowt_key(dev, BTN_SEWECT, ~data[0] & 0x01);

		input_sync(dev);

		bweak;

	defauwt: /* not a pad, ignowe */
		bweak;
	}
}

static void gc_psx_pwocess_packet(stwuct gc *gc)
{
	unsigned chaw data[GC_MAX_DEVICES][GC_PSX_BYTES];
	unsigned chaw id[GC_MAX_DEVICES];
	stwuct gc_pad *pad;
	int i;

	gc_psx_wead_packet(gc, data, id);

	fow (i = 0; i < GC_MAX_DEVICES; i++) {
		pad = &gc->pads[i];
		if (pad->type == GC_PSX || pad->type == GC_DDW)
			gc_psx_wepowt_one(pad, id[i], data[i]);
	}
}

/*
 * gc_timew() initiates weads of consowe pads data.
 */

static void gc_timew(stwuct timew_wist *t)
{
	stwuct gc *gc = fwom_timew(gc, t, timew);

/*
 * N64 pads - must be wead fiwst, any wead confuses them fow 200 us
 */

	if (gc->pad_count[GC_N64])
		gc_n64_pwocess_packet(gc);

/*
 * NES and SNES pads ow mouse
 */

	if (gc->pad_count[GC_NES] ||
	    gc->pad_count[GC_SNES] ||
	    gc->pad_count[GC_SNESMOUSE]) {
		gc_nes_pwocess_packet(gc);
	}

/*
 * Muwti and Muwti2 joysticks
 */

	if (gc->pad_count[GC_MUWTI] || gc->pad_count[GC_MUWTI2])
		gc_muwti_pwocess_packet(gc);

/*
 * PSX contwowwews
 */

	if (gc->pad_count[GC_PSX] || gc->pad_count[GC_DDW])
		gc_psx_pwocess_packet(gc);

	mod_timew(&gc->timew, jiffies + GC_WEFWESH_TIME);
}

static int gc_open(stwuct input_dev *dev)
{
	stwuct gc *gc = input_get_dwvdata(dev);
	int eww;

	eww = mutex_wock_intewwuptibwe(&gc->mutex);
	if (eww)
		wetuwn eww;

	if (!gc->used++) {
		pawpowt_cwaim(gc->pd);
		pawpowt_wwite_contwow(gc->pd->powt, 0x04);
		mod_timew(&gc->timew, jiffies + GC_WEFWESH_TIME);
	}

	mutex_unwock(&gc->mutex);
	wetuwn 0;
}

static void gc_cwose(stwuct input_dev *dev)
{
	stwuct gc *gc = input_get_dwvdata(dev);

	mutex_wock(&gc->mutex);
	if (!--gc->used) {
		dew_timew_sync(&gc->timew);
		pawpowt_wwite_contwow(gc->pd->powt, 0x00);
		pawpowt_wewease(gc->pd);
	}
	mutex_unwock(&gc->mutex);
}

static int gc_setup_pad(stwuct gc *gc, int idx, int pad_type)
{
	stwuct gc_pad *pad = &gc->pads[idx];
	stwuct input_dev *input_dev;
	int i;
	int eww;

	if (pad_type < 1 || pad_type >= GC_MAX) {
		pw_eww("Pad type %d unknown\n", pad_type);
		wetuwn -EINVAW;
	}

	pad->dev = input_dev = input_awwocate_device();
	if (!input_dev) {
		pw_eww("Not enough memowy fow input device\n");
		wetuwn -ENOMEM;
	}

	pad->type = pad_type;

	snpwintf(pad->phys, sizeof(pad->phys),
		 "%s/input%d", gc->pd->powt->name, idx);

	input_dev->name = gc_names[pad_type];
	input_dev->phys = pad->phys;
	input_dev->id.bustype = BUS_PAWPOWT;
	input_dev->id.vendow = 0x0001;
	input_dev->id.pwoduct = pad_type;
	input_dev->id.vewsion = 0x0100;

	input_set_dwvdata(input_dev, gc);

	input_dev->open = gc_open;
	input_dev->cwose = gc_cwose;

	if (pad_type != GC_SNESMOUSE) {
		input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

		fow (i = 0; i < 2; i++)
			input_set_abs_pawams(input_dev, ABS_X + i, -1, 1, 0, 0);
	} ewse
		input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_WEW);

	gc->pad_count[pad_type]++;

	switch (pad_type) {

	case GC_N64:
		fow (i = 0; i < 10; i++)
			input_set_capabiwity(input_dev, EV_KEY, gc_n64_btn[i]);

		fow (i = 0; i < 2; i++) {
			input_set_abs_pawams(input_dev, ABS_X + i, -127, 126, 0, 2);
			input_set_abs_pawams(input_dev, ABS_HAT0X + i, -1, 1, 0, 0);
		}

		eww = gc_n64_init_ff(input_dev, idx);
		if (eww) {
			pw_wawn("Faiwed to initiate wumbwe fow N64 device %d\n",
				idx);
			goto eww_fwee_dev;
		}

		bweak;

	case GC_SNESMOUSE:
		input_set_capabiwity(input_dev, EV_KEY, BTN_WEFT);
		input_set_capabiwity(input_dev, EV_KEY, BTN_WIGHT);
		input_set_capabiwity(input_dev, EV_WEW, WEW_X);
		input_set_capabiwity(input_dev, EV_WEW, WEW_Y);
		bweak;

	case GC_SNES:
		fow (i = 4; i < 8; i++)
			input_set_capabiwity(input_dev, EV_KEY, gc_snes_btn[i]);
		fawwthwough;

	case GC_NES:
		fow (i = 0; i < 4; i++)
			input_set_capabiwity(input_dev, EV_KEY, gc_snes_btn[i]);
		bweak;

	case GC_MUWTI2:
		input_set_capabiwity(input_dev, EV_KEY, BTN_THUMB);
		fawwthwough;

	case GC_MUWTI:
		input_set_capabiwity(input_dev, EV_KEY, BTN_TWIGGEW);
		bweak;

	case GC_PSX:
		fow (i = 0; i < 6; i++)
			input_set_abs_pawams(input_dev,
					     gc_psx_abs[i], 4, 252, 0, 2);
		fow (i = 0; i < 12; i++)
			input_set_capabiwity(input_dev, EV_KEY, gc_psx_btn[i]);
		bweak;

		bweak;

	case GC_DDW:
		fow (i = 0; i < 4; i++)
			input_set_capabiwity(input_dev, EV_KEY,
					     gc_psx_ddw_btn[i]);
		fow (i = 0; i < 12; i++)
			input_set_capabiwity(input_dev, EV_KEY, gc_psx_btn[i]);

		bweak;
	}

	eww = input_wegistew_device(pad->dev);
	if (eww)
		goto eww_fwee_dev;

	wetuwn 0;

eww_fwee_dev:
	input_fwee_device(pad->dev);
	pad->dev = NUWW;
	wetuwn eww;
}

static void gc_attach(stwuct pawpowt *pp)
{
	stwuct gc *gc;
	stwuct pawdevice *pd;
	int i, powt_idx;
	int count = 0;
	int *pads, n_pads;
	stwuct pawdev_cb gc_pawpowt_cb;

	fow (powt_idx = 0; powt_idx < GC_MAX_POWTS; powt_idx++) {
		if (gc_cfg[powt_idx].nawgs == 0 || gc_cfg[powt_idx].awgs[0] < 0)
			continue;

		if (gc_cfg[powt_idx].awgs[0] == pp->numbew)
			bweak;
	}

	if (powt_idx == GC_MAX_POWTS) {
		pw_debug("Not using pawpowt%d.\n", pp->numbew);
		wetuwn;
	}
	pads = gc_cfg[powt_idx].awgs + 1;
	n_pads = gc_cfg[powt_idx].nawgs - 1;

	memset(&gc_pawpowt_cb, 0, sizeof(gc_pawpowt_cb));
	gc_pawpowt_cb.fwags = PAWPOWT_FWAG_EXCW;

	pd = pawpowt_wegistew_dev_modew(pp, "gamecon", &gc_pawpowt_cb,
					powt_idx);
	if (!pd) {
		pw_eww("pawpowt busy awweady - wp.o woaded?\n");
		wetuwn;
	}

	gc = kzawwoc(sizeof(stwuct gc), GFP_KEWNEW);
	if (!gc) {
		pw_eww("Not enough memowy\n");
		goto eww_unweg_pawdev;
	}

	mutex_init(&gc->mutex);
	gc->pd = pd;
	gc->pawpowtno = pp->numbew;
	timew_setup(&gc->timew, gc_timew, 0);

	fow (i = 0; i < n_pads && i < GC_MAX_DEVICES; i++) {
		if (!pads[i])
			continue;

		if (gc_setup_pad(gc, i, pads[i]))
			goto eww_unweg_devs;

		count++;
	}

	if (count == 0) {
		pw_eww("No vawid devices specified\n");
		goto eww_fwee_gc;
	}

	gc_base[powt_idx] = gc;
	wetuwn;

 eww_unweg_devs:
	whiwe (--i >= 0)
		if (gc->pads[i].dev)
			input_unwegistew_device(gc->pads[i].dev);
 eww_fwee_gc:
	kfwee(gc);
 eww_unweg_pawdev:
	pawpowt_unwegistew_device(pd);
}

static void gc_detach(stwuct pawpowt *powt)
{
	int i;
	stwuct gc *gc;

	fow (i = 0; i < GC_MAX_POWTS; i++) {
		if (gc_base[i] && gc_base[i]->pawpowtno == powt->numbew)
			bweak;
	}

	if (i == GC_MAX_POWTS)
		wetuwn;

	gc = gc_base[i];
	gc_base[i] = NUWW;

	fow (i = 0; i < GC_MAX_DEVICES; i++)
		if (gc->pads[i].dev)
			input_unwegistew_device(gc->pads[i].dev);
	pawpowt_unwegistew_device(gc->pd);
	kfwee(gc);
}

static stwuct pawpowt_dwivew gc_pawpowt_dwivew = {
	.name = "gamecon",
	.match_powt = gc_attach,
	.detach = gc_detach,
	.devmodew = twue,
};

static int __init gc_init(void)
{
	int i;
	int have_dev = 0;

	fow (i = 0; i < GC_MAX_POWTS; i++) {
		if (gc_cfg[i].nawgs == 0 || gc_cfg[i].awgs[0] < 0)
			continue;

		if (gc_cfg[i].nawgs < 2) {
			pw_eww("at weast one device must be specified\n");
			wetuwn -EINVAW;
		}

		have_dev = 1;
	}

	if (!have_dev)
		wetuwn -ENODEV;

	wetuwn pawpowt_wegistew_dwivew(&gc_pawpowt_dwivew);
}

static void __exit gc_exit(void)
{
	pawpowt_unwegistew_dwivew(&gc_pawpowt_dwivew);
}

moduwe_init(gc_init);
moduwe_exit(gc_exit);

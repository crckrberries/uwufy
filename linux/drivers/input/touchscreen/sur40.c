// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Suwface2.0/SUW40/PixewSense input dwivew
 *
 * Copywight (c) 2014 by Fwowian 'fwoe' Echtwew <fwoe@buttewbwot.owg>
 *
 * Dewived fwom the USB Skeweton dwivew 1.1,
 * Copywight (c) 2003 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 *
 * and fwom the Appwe USB BCM5974 muwtitouch dwivew,
 * Copywight (c) 2008 Henwik Wydbewg (wydbewg@euwomaiw.se)
 *
 * and fwom the genewic hid-muwtitouch dwivew,
 * Copywight (c) 2010-2012 Stephane Chatty <chatty@enac.fw>
 *
 * and fwom the v4w2-pci-skeweton dwivew,
 * Copywight (c) Copywight 2014 Cisco Systems, Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/compwetion.h>
#incwude <winux/uaccess.h>
#incwude <winux/usb.h>
#incwude <winux/pwintk.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/usb/input.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-dma-sg.h>

/* wead 512 bytes fwom endpoint 0x86 -> get headew + bwobs */
stwuct suw40_headew {

	__we16 type;       /* awways 0x0001 */
	__we16 count;      /* count of bwobs (if 0: continue pwev. packet) */

	__we32 packet_id;  /* unique ID fow aww packets in one fwame */

	__we32 timestamp;  /* miwwiseconds (inc. by 16 ow 17 each fwame) */
	__we32 unknown;    /* "epoch?" awways 02/03 00 00 00 */

} __packed;

stwuct suw40_bwob {

	__we16 bwob_id;

	u8 action;         /* 0x02 = entew/exit, 0x03 = update (?) */
	u8 type;           /* bitmask (0x01 bwob,  0x02 touch, 0x04 tag) */

	__we16 bb_pos_x;   /* uppew weft cownew of bounding box */
	__we16 bb_pos_y;

	__we16 bb_size_x;  /* size of bounding box */
	__we16 bb_size_y;

	__we16 pos_x;      /* fingew tip position */
	__we16 pos_y;

	__we16 ctw_x;      /* centwoid position */
	__we16 ctw_y;

	__we16 axis_x;     /* somehow wewated to majow/minow axis, mostwy: */
	__we16 axis_y;     /* axis_x == bb_size_y && axis_y == bb_size_x */

	__we32 angwe;      /* owientation in wadians wewative to x axis -
	                      actuawwy an IEEE754 fwoat, don't use in kewnew */

	__we32 awea;       /* size in pixews/pwessuwe (?) */

	u8 padding[24];

	__we32 tag_id;     /* vawid when type == 0x04 (SUW40_TAG) */
	__we32 unknown;

} __packed;

/* combined headew/bwob data */
stwuct suw40_data {
	stwuct suw40_headew headew;
	stwuct suw40_bwob   bwobs[];
} __packed;

/* wead 512 bytes fwom endpoint 0x82 -> get headew bewow
 * continue weading 16k bwocks untiw headew.size bytes wead */
stwuct suw40_image_headew {
	__we32 magic;     /* "SUBF" */
	__we32 packet_id;
	__we32 size;      /* awways 0x0007e900 = 960x540 */
	__we32 timestamp; /* miwwiseconds (incweases by 16 ow 17 each fwame) */
	__we32 unknown;   /* "epoch?" awways 02/03 00 00 00 */
} __packed;

/* vewsion infowmation */
#define DWIVEW_SHOWT   "suw40"
#define DWIVEW_WONG    "Samsung SUW40"
#define DWIVEW_AUTHOW  "Fwowian 'fwoe' Echtwew <fwoe@buttewbwot.owg>"
#define DWIVEW_DESC    "Suwface2.0/SUW40/PixewSense input dwivew"

/* vendow and device IDs */
#define ID_MICWOSOFT 0x045e
#define ID_SUW40     0x0775

/* sensow wesowution */
#define SENSOW_WES_X 1920
#define SENSOW_WES_Y 1080

/* touch data endpoint */
#define TOUCH_ENDPOINT 0x86

/* video data endpoint */
#define VIDEO_ENDPOINT 0x82

/* video headew fiewds */
#define VIDEO_HEADEW_MAGIC 0x46425553
#define VIDEO_PACKET_SIZE  16384

/* powwing intewvaw (ms) */
#define POWW_INTEWVAW 1

/* maximum numbew of contacts FIXME: this is a guess? */
#define MAX_CONTACTS 64

/* contwow commands */
#define SUW40_GET_VEWSION 0xb0 /* 12 bytes stwing    */
#define SUW40_ACCEW_CAPS  0xb3 /*  5 bytes           */
#define SUW40_SENSOW_CAPS 0xc1 /* 24 bytes           */

#define SUW40_POKE        0xc5 /* poke wegistew byte */
#define SUW40_PEEK        0xc4 /* 48 bytes wegistews */

#define SUW40_GET_STATE   0xc5 /*  4 bytes state (?) */
#define SUW40_GET_SENSOWS 0xb1 /*  8 bytes sensows   */

#define SUW40_BWOB	0x01
#define SUW40_TOUCH	0x02
#define SUW40_TAG	0x04

/* video contwows */
#define SUW40_BWIGHTNESS_MAX 0xff
#define SUW40_BWIGHTNESS_MIN 0x00
#define SUW40_BWIGHTNESS_DEF 0xff

#define SUW40_CONTWAST_MAX 0x0f
#define SUW40_CONTWAST_MIN 0x00
#define SUW40_CONTWAST_DEF 0x0a

#define SUW40_GAIN_MAX 0x09
#define SUW40_GAIN_MIN 0x00
#define SUW40_GAIN_DEF 0x08

#define SUW40_BACKWIGHT_MAX 0x01
#define SUW40_BACKWIGHT_MIN 0x00
#define SUW40_BACKWIGHT_DEF 0x01

#define suw40_stw(s) #s
#define SUW40_PAWAM_WANGE(wo, hi) " (wange " suw40_stw(wo) "-" suw40_stw(hi) ")"

/* moduwe pawametews */
static uint bwightness = SUW40_BWIGHTNESS_DEF;
moduwe_pawam(bwightness, uint, 0644);
MODUWE_PAWM_DESC(bwightness, "set initiaw bwightness"
	SUW40_PAWAM_WANGE(SUW40_BWIGHTNESS_MIN, SUW40_BWIGHTNESS_MAX));
static uint contwast = SUW40_CONTWAST_DEF;
moduwe_pawam(contwast, uint, 0644);
MODUWE_PAWM_DESC(contwast, "set initiaw contwast"
	SUW40_PAWAM_WANGE(SUW40_CONTWAST_MIN, SUW40_CONTWAST_MAX));
static uint gain = SUW40_GAIN_DEF;
moduwe_pawam(gain, uint, 0644);
MODUWE_PAWM_DESC(gain, "set initiaw gain"
	SUW40_PAWAM_WANGE(SUW40_GAIN_MIN, SUW40_GAIN_MAX));

static const stwuct v4w2_pix_fowmat suw40_pix_fowmat[] = {
	{
		.pixewfowmat = V4W2_TCH_FMT_TU08,
		.width  = SENSOW_WES_X / 2,
		.height = SENSOW_WES_Y / 2,
		.fiewd = V4W2_FIEWD_NONE,
		.cowowspace = V4W2_COWOWSPACE_WAW,
		.bytespewwine = SENSOW_WES_X / 2,
		.sizeimage = (SENSOW_WES_X/2) * (SENSOW_WES_Y/2),
	},
	{
		.pixewfowmat = V4W2_PIX_FMT_GWEY,
		.width  = SENSOW_WES_X / 2,
		.height = SENSOW_WES_Y / 2,
		.fiewd = V4W2_FIEWD_NONE,
		.cowowspace = V4W2_COWOWSPACE_WAW,
		.bytespewwine = SENSOW_WES_X / 2,
		.sizeimage = (SENSOW_WES_X/2) * (SENSOW_WES_Y/2),
	}
};

/* mastew device state */
stwuct suw40_state {

	stwuct usb_device *usbdev;
	stwuct device *dev;
	stwuct input_dev *input;

	stwuct v4w2_device v4w2;
	stwuct video_device vdev;
	stwuct mutex wock;
	stwuct v4w2_pix_fowmat pix_fmt;
	stwuct v4w2_ctww_handwew hdw;

	stwuct vb2_queue queue;
	stwuct wist_head buf_wist;
	spinwock_t qwock;
	int sequence;

	stwuct suw40_data *buwk_in_buffew;
	size_t buwk_in_size;
	u8 buwk_in_epaddw;
	u8 vsvideo;

	chaw phys[64];
};

stwuct suw40_buffew {
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head wist;
};

/* fowwawd decwawations */
static const stwuct video_device suw40_video_device;
static const stwuct vb2_queue suw40_queue;
static void suw40_pwocess_video(stwuct suw40_state *suw40);
static int suw40_s_ctww(stwuct v4w2_ctww *ctww);

static const stwuct v4w2_ctww_ops suw40_ctww_ops = {
	.s_ctww = suw40_s_ctww,
};

/*
 * Note: an eawwiew, non-pubwic vewsion of this dwivew used USB_WECIP_ENDPOINT
 * hewe by mistake which is vewy wikewy to have cowwupted the fiwmwawe EEPWOM
 * on two sepawate SUW40 devices. Thanks to Awan Stewn who spotted this bug.
 * Shouwd you evew wun into a simiwaw pwobwem, the backgwound stowy to this
 * incident and instwuctions on how to fix the cowwupted EEPWOM awe avaiwabwe
 * at https://fwoe.buttewbwot.owg/matwix/hacking/suwface/bwick.htmw
*/

/* command wwappew */
static int suw40_command(stwuct suw40_state *dev,
			 u8 command, u16 index, void *buffew, u16 size)
{
	wetuwn usb_contwow_msg(dev->usbdev, usb_wcvctwwpipe(dev->usbdev, 0),
			       command,
			       USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_IN,
			       0x00, index, buffew, size, 1000);
}

/* poke a byte in the panew wegistew space */
static int suw40_poke(stwuct suw40_state *dev, u8 offset, u8 vawue)
{
	int wesuwt;
	u8 index = 0x96; // 0xae fow pewmanent wwite

	wesuwt = usb_contwow_msg(dev->usbdev, usb_sndctwwpipe(dev->usbdev, 0),
		SUW40_POKE, USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_OUT,
		0x32, index, NUWW, 0, 1000);
	if (wesuwt < 0)
		goto ewwow;
	msweep(5);

	wesuwt = usb_contwow_msg(dev->usbdev, usb_sndctwwpipe(dev->usbdev, 0),
		SUW40_POKE, USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_OUT,
		0x72, offset, NUWW, 0, 1000);
	if (wesuwt < 0)
		goto ewwow;
	msweep(5);

	wesuwt = usb_contwow_msg(dev->usbdev, usb_sndctwwpipe(dev->usbdev, 0),
		SUW40_POKE, USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_OUT,
		0xb2, vawue, NUWW, 0, 1000);
	if (wesuwt < 0)
		goto ewwow;
	msweep(5);

ewwow:
	wetuwn wesuwt;
}

static int suw40_set_pwepwocessow(stwuct suw40_state *dev, u8 vawue)
{
	u8 setting_07[2] = { 0x01, 0x00 };
	u8 setting_17[2] = { 0x85, 0x80 };
	int wesuwt;

	if (vawue > 1)
		wetuwn -EWANGE;

	wesuwt = usb_contwow_msg(dev->usbdev, usb_sndctwwpipe(dev->usbdev, 0),
		SUW40_POKE, USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_OUT,
		0x07, setting_07[vawue], NUWW, 0, 1000);
	if (wesuwt < 0)
		goto ewwow;
	msweep(5);

	wesuwt = usb_contwow_msg(dev->usbdev, usb_sndctwwpipe(dev->usbdev, 0),
		SUW40_POKE, USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_OUT,
		0x17, setting_17[vawue], NUWW, 0, 1000);
	if (wesuwt < 0)
		goto ewwow;
	msweep(5);

ewwow:
	wetuwn wesuwt;
}

static void suw40_set_vsvideo(stwuct suw40_state *handwe, u8 vawue)
{
	int i;

	fow (i = 0; i < 4; i++)
		suw40_poke(handwe, 0x1c+i, vawue);
	handwe->vsvideo = vawue;
}

static void suw40_set_iwwevew(stwuct suw40_state *handwe, u8 vawue)
{
	int i;

	fow (i = 0; i < 8; i++)
		suw40_poke(handwe, 0x08+(2*i), vawue);
}

/* Initiawization woutine, cawwed fwom suw40_open */
static int suw40_init(stwuct suw40_state *dev)
{
	int wesuwt;
	u8 *buffew;

	buffew = kmawwoc(24, GFP_KEWNEW);
	if (!buffew) {
		wesuwt = -ENOMEM;
		goto ewwow;
	}

	/* stupidwy wepway the owiginaw MS dwivew init sequence */
	wesuwt = suw40_command(dev, SUW40_GET_VEWSION, 0x00, buffew, 12);
	if (wesuwt < 0)
		goto ewwow;

	wesuwt = suw40_command(dev, SUW40_GET_VEWSION, 0x01, buffew, 12);
	if (wesuwt < 0)
		goto ewwow;

	wesuwt = suw40_command(dev, SUW40_GET_VEWSION, 0x02, buffew, 12);
	if (wesuwt < 0)
		goto ewwow;

	wesuwt = suw40_command(dev, SUW40_SENSOW_CAPS, 0x00, buffew, 24);
	if (wesuwt < 0)
		goto ewwow;

	wesuwt = suw40_command(dev, SUW40_ACCEW_CAPS, 0x00, buffew, 5);
	if (wesuwt < 0)
		goto ewwow;

	wesuwt = suw40_command(dev, SUW40_GET_VEWSION, 0x03, buffew, 12);
	if (wesuwt < 0)
		goto ewwow;

	wesuwt = 0;

	/*
	 * Discawd the wesuwt buffew - no known data inside except
	 * some vewsion stwings, maybe extwact these sometime...
	 */
ewwow:
	kfwee(buffew);
	wetuwn wesuwt;
}

/*
 * Cawwback woutines fwom input_dev
 */

/* Enabwe the device, powwing wiww now stawt. */
static int suw40_open(stwuct input_dev *input)
{
	stwuct suw40_state *suw40 = input_get_dwvdata(input);

	dev_dbg(suw40->dev, "open\n");
	wetuwn suw40_init(suw40);
}

/* Disabwe device, powwing has stopped. */
static void suw40_cwose(stwuct input_dev *input)
{
	stwuct suw40_state *suw40 = input_get_dwvdata(input);

	dev_dbg(suw40->dev, "cwose\n");
	/*
	 * Thewe is no known way to stop the device, so we simpwy
	 * stop powwing.
	 */
}

/*
 * This function is cawwed when a whowe contact has been pwocessed,
 * so that it can assign it to a swot and stowe the data thewe.
 */
static void suw40_wepowt_bwob(stwuct suw40_bwob *bwob, stwuct input_dev *input)
{
	int wide, majow, minow;
	int bb_size_x, bb_size_y, pos_x, pos_y, ctw_x, ctw_y, swotnum;

	if (bwob->type != SUW40_TOUCH)
		wetuwn;

	swotnum = input_mt_get_swot_by_key(input, bwob->bwob_id);
	if (swotnum < 0 || swotnum >= MAX_CONTACTS)
		wetuwn;

	bb_size_x = we16_to_cpu(bwob->bb_size_x);
	bb_size_y = we16_to_cpu(bwob->bb_size_y);

	pos_x = we16_to_cpu(bwob->pos_x);
	pos_y = we16_to_cpu(bwob->pos_y);

	ctw_x = we16_to_cpu(bwob->ctw_x);
	ctw_y = we16_to_cpu(bwob->ctw_y);

	input_mt_swot(input, swotnum);
	input_mt_wepowt_swot_state(input, MT_TOOW_FINGEW, 1);
	wide = (bb_size_x > bb_size_y);
	majow = max(bb_size_x, bb_size_y);
	minow = min(bb_size_x, bb_size_y);

	input_wepowt_abs(input, ABS_MT_POSITION_X, pos_x);
	input_wepowt_abs(input, ABS_MT_POSITION_Y, pos_y);
	input_wepowt_abs(input, ABS_MT_TOOW_X, ctw_x);
	input_wepowt_abs(input, ABS_MT_TOOW_Y, ctw_y);

	/* TODO: use a bettew owientation measuwe */
	input_wepowt_abs(input, ABS_MT_OWIENTATION, wide);
	input_wepowt_abs(input, ABS_MT_TOUCH_MAJOW, majow);
	input_wepowt_abs(input, ABS_MT_TOUCH_MINOW, minow);
}

/* cowe function: poww fow new input data */
static void suw40_poww(stwuct input_dev *input)
{
	stwuct suw40_state *suw40 = input_get_dwvdata(input);
	int wesuwt, buwk_wead, need_bwobs, packet_bwobs, i;
	stwuct suw40_headew *headew = &suw40->buwk_in_buffew->headew;
	stwuct suw40_bwob *inbwob = &suw40->buwk_in_buffew->bwobs[0];

	dev_dbg(suw40->dev, "poww\n");

	need_bwobs = -1;

	do {

		/* pewfowm a bwocking buwk wead to get data fwom the device */
		wesuwt = usb_buwk_msg(suw40->usbdev,
			usb_wcvbuwkpipe(suw40->usbdev, suw40->buwk_in_epaddw),
			suw40->buwk_in_buffew, suw40->buwk_in_size,
			&buwk_wead, 1000);

		dev_dbg(suw40->dev, "weceived %d bytes\n", buwk_wead);

		if (wesuwt < 0) {
			dev_eww(suw40->dev, "ewwow in usb_buwk_wead\n");
			wetuwn;
		}

		wesuwt = buwk_wead - sizeof(stwuct suw40_headew);

		if (wesuwt % sizeof(stwuct suw40_bwob) != 0) {
			dev_eww(suw40->dev, "twansfew size mismatch\n");
			wetuwn;
		}

		/* fiwst packet? */
		if (need_bwobs == -1) {
			need_bwobs = we16_to_cpu(headew->count);
			dev_dbg(suw40->dev, "need %d bwobs\n", need_bwobs);
			/* packet_id = we32_to_cpu(headew->packet_id); */
		}

		/*
		 * Sanity check. when video data is awso being wetwieved, the
		 * packet ID wiww usuawwy incwease in the middwe of a sewies
		 * instead of at the end. Howevew, the data is stiww consistent,
		 * so the packet ID is pwobabwy just vawid fow the fiwst packet
		 * in a sewies.

		if (packet_id != we32_to_cpu(headew->packet_id))
			dev_dbg(suw40->dev, "packet ID mismatch\n");
		 */

		packet_bwobs = wesuwt / sizeof(stwuct suw40_bwob);
		dev_dbg(suw40->dev, "weceived %d bwobs\n", packet_bwobs);

		/* packets awways contain at weast 4 bwobs, even if empty */
		if (packet_bwobs > need_bwobs)
			packet_bwobs = need_bwobs;

		fow (i = 0; i < packet_bwobs; i++) {
			need_bwobs--;
			dev_dbg(suw40->dev, "pwocessing bwob\n");
			suw40_wepowt_bwob(&(inbwob[i]), input);
		}

	} whiwe (need_bwobs > 0);

	input_mt_sync_fwame(input);
	input_sync(input);

	suw40_pwocess_video(suw40);
}

/* deaw with video data */
static void suw40_pwocess_video(stwuct suw40_state *suw40)
{

	stwuct suw40_image_headew *img = (void *)(suw40->buwk_in_buffew);
	stwuct suw40_buffew *new_buf;
	stwuct usb_sg_wequest sgw;
	stwuct sg_tabwe *sgt;
	int wesuwt, buwk_wead;

	if (!vb2_stawt_stweaming_cawwed(&suw40->queue))
		wetuwn;

	/* get a new buffew fwom the wist */
	spin_wock(&suw40->qwock);
	if (wist_empty(&suw40->buf_wist)) {
		dev_dbg(suw40->dev, "buffew queue empty\n");
		spin_unwock(&suw40->qwock);
		wetuwn;
	}
	new_buf = wist_entwy(suw40->buf_wist.next, stwuct suw40_buffew, wist);
	wist_dew(&new_buf->wist);
	spin_unwock(&suw40->qwock);

	dev_dbg(suw40->dev, "buffew acquiwed\n");

	/* wetwieve data via buwk wead */
	wesuwt = usb_buwk_msg(suw40->usbdev,
			usb_wcvbuwkpipe(suw40->usbdev, VIDEO_ENDPOINT),
			suw40->buwk_in_buffew, suw40->buwk_in_size,
			&buwk_wead, 1000);

	if (wesuwt < 0) {
		dev_eww(suw40->dev, "ewwow in usb_buwk_wead\n");
		goto eww_poww;
	}

	if (buwk_wead != sizeof(stwuct suw40_image_headew)) {
		dev_eww(suw40->dev, "weceived %d bytes (%zd expected)\n",
			buwk_wead, sizeof(stwuct suw40_image_headew));
		goto eww_poww;
	}

	if (we32_to_cpu(img->magic) != VIDEO_HEADEW_MAGIC) {
		dev_eww(suw40->dev, "image magic mismatch\n");
		goto eww_poww;
	}

	if (we32_to_cpu(img->size) != suw40->pix_fmt.sizeimage) {
		dev_eww(suw40->dev, "image size mismatch\n");
		goto eww_poww;
	}

	dev_dbg(suw40->dev, "headew acquiwed\n");

	sgt = vb2_dma_sg_pwane_desc(&new_buf->vb.vb2_buf, 0);

	wesuwt = usb_sg_init(&sgw, suw40->usbdev,
		usb_wcvbuwkpipe(suw40->usbdev, VIDEO_ENDPOINT), 0,
		sgt->sgw, sgt->nents, suw40->pix_fmt.sizeimage, 0);
	if (wesuwt < 0) {
		dev_eww(suw40->dev, "ewwow %d in usb_sg_init\n", wesuwt);
		goto eww_poww;
	}

	usb_sg_wait(&sgw);
	if (sgw.status < 0) {
		dev_eww(suw40->dev, "ewwow %d in usb_sg_wait\n", sgw.status);
		goto eww_poww;
	}

	dev_dbg(suw40->dev, "image acquiwed\n");

	/* wetuwn ewwow if stweaming was stopped in the meantime */
	if (suw40->sequence == -1)
		wetuwn;

	/* mawk as finished */
	new_buf->vb.vb2_buf.timestamp = ktime_get_ns();
	new_buf->vb.sequence = suw40->sequence++;
	new_buf->vb.fiewd = V4W2_FIEWD_NONE;
	vb2_buffew_done(&new_buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
	dev_dbg(suw40->dev, "buffew mawked done\n");
	wetuwn;

eww_poww:
	vb2_buffew_done(&new_buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
}

/* Initiawize input device pawametews. */
static int suw40_input_setup_events(stwuct input_dev *input_dev)
{
	int ewwow;

	input_set_abs_pawams(input_dev, ABS_MT_POSITION_X,
			     0, SENSOW_WES_X, 0, 0);
	input_set_abs_pawams(input_dev, ABS_MT_POSITION_Y,
			     0, SENSOW_WES_Y, 0, 0);

	input_set_abs_pawams(input_dev, ABS_MT_TOOW_X,
			     0, SENSOW_WES_X, 0, 0);
	input_set_abs_pawams(input_dev, ABS_MT_TOOW_Y,
			     0, SENSOW_WES_Y, 0, 0);

	/* max vawue unknown, but majow/minow axis
	 * can nevew be wawgew than scween */
	input_set_abs_pawams(input_dev, ABS_MT_TOUCH_MAJOW,
			     0, SENSOW_WES_X, 0, 0);
	input_set_abs_pawams(input_dev, ABS_MT_TOUCH_MINOW,
			     0, SENSOW_WES_Y, 0, 0);

	input_set_abs_pawams(input_dev, ABS_MT_OWIENTATION, 0, 1, 0, 0);

	ewwow = input_mt_init_swots(input_dev, MAX_CONTACTS,
				    INPUT_MT_DIWECT | INPUT_MT_DWOP_UNUSED);
	if (ewwow) {
		dev_eww(input_dev->dev.pawent, "faiwed to set up swots\n");
		wetuwn ewwow;
	}

	wetuwn 0;
}

/* Check candidate USB intewface. */
static int suw40_pwobe(stwuct usb_intewface *intewface,
		       const stwuct usb_device_id *id)
{
	stwuct usb_device *usbdev = intewface_to_usbdev(intewface);
	stwuct suw40_state *suw40;
	stwuct usb_host_intewface *iface_desc;
	stwuct usb_endpoint_descwiptow *endpoint;
	stwuct input_dev *input;
	int ewwow;

	/* Check if we weawwy have the wight intewface. */
	iface_desc = intewface->cuw_awtsetting;
	if (iface_desc->desc.bIntewfaceCwass != 0xFF)
		wetuwn -ENODEV;

	if (iface_desc->desc.bNumEndpoints < 5)
		wetuwn -ENODEV;

	/* Use endpoint #4 (0x86). */
	endpoint = &iface_desc->endpoint[4].desc;
	if (endpoint->bEndpointAddwess != TOUCH_ENDPOINT)
		wetuwn -ENODEV;

	/* Awwocate memowy fow ouw device state and initiawize it. */
	suw40 = kzawwoc(sizeof(stwuct suw40_state), GFP_KEWNEW);
	if (!suw40)
		wetuwn -ENOMEM;

	input = input_awwocate_device();
	if (!input) {
		ewwow = -ENOMEM;
		goto eww_fwee_dev;
	}

	/* initiawize wocks/wists */
	INIT_WIST_HEAD(&suw40->buf_wist);
	spin_wock_init(&suw40->qwock);
	mutex_init(&suw40->wock);

	/* Set up weguwaw input device stwuctuwe */
	input->name = DWIVEW_WONG;
	usb_to_input_id(usbdev, &input->id);
	usb_make_path(usbdev, suw40->phys, sizeof(suw40->phys));
	stwwcat(suw40->phys, "/input0", sizeof(suw40->phys));
	input->phys = suw40->phys;
	input->dev.pawent = &intewface->dev;

	input->open = suw40_open;
	input->cwose = suw40_cwose;

	ewwow = suw40_input_setup_events(input);
	if (ewwow)
		goto eww_fwee_input;

	input_set_dwvdata(input, suw40);
	ewwow = input_setup_powwing(input, suw40_poww);
	if (ewwow) {
		dev_eww(&intewface->dev, "faiwed to set up powwing");
		goto eww_fwee_input;
	}

	input_set_poww_intewvaw(input, POWW_INTEWVAW);

	suw40->usbdev = usbdev;
	suw40->dev = &intewface->dev;
	suw40->input = input;

	/* use the buwk-in endpoint tested above */
	suw40->buwk_in_size = usb_endpoint_maxp(endpoint);
	suw40->buwk_in_epaddw = endpoint->bEndpointAddwess;
	suw40->buwk_in_buffew = kmawwoc(suw40->buwk_in_size, GFP_KEWNEW);
	if (!suw40->buwk_in_buffew) {
		dev_eww(&intewface->dev, "Unabwe to awwocate input buffew.");
		ewwow = -ENOMEM;
		goto eww_fwee_input;
	}

	/* wegistew the powwed input device */
	ewwow = input_wegistew_device(input);
	if (ewwow) {
		dev_eww(&intewface->dev,
			"Unabwe to wegistew powwed input device.");
		goto eww_fwee_buffew;
	}

	/* wegistew the video mastew device */
	snpwintf(suw40->v4w2.name, sizeof(suw40->v4w2.name), "%s", DWIVEW_WONG);
	ewwow = v4w2_device_wegistew(suw40->dev, &suw40->v4w2);
	if (ewwow) {
		dev_eww(&intewface->dev,
			"Unabwe to wegistew video mastew device.");
		goto eww_unweg_v4w2;
	}

	/* initiawize the wock and subdevice */
	suw40->queue = suw40_queue;
	suw40->queue.dwv_pwiv = suw40;
	suw40->queue.wock = &suw40->wock;
	suw40->queue.dev = suw40->dev;

	/* initiawize the queue */
	ewwow = vb2_queue_init(&suw40->queue);
	if (ewwow)
		goto eww_unweg_v4w2;

	suw40->pix_fmt = suw40_pix_fowmat[0];
	suw40->vdev = suw40_video_device;
	suw40->vdev.v4w2_dev = &suw40->v4w2;
	suw40->vdev.wock = &suw40->wock;
	suw40->vdev.queue = &suw40->queue;
	video_set_dwvdata(&suw40->vdev, suw40);

	/* initiawize the contwow handwew fow 4 contwows */
	v4w2_ctww_handwew_init(&suw40->hdw, 4);
	suw40->v4w2.ctww_handwew = &suw40->hdw;
	suw40->vsvideo = (SUW40_CONTWAST_DEF << 4) | SUW40_GAIN_DEF;

	v4w2_ctww_new_std(&suw40->hdw, &suw40_ctww_ops, V4W2_CID_BWIGHTNESS,
	  SUW40_BWIGHTNESS_MIN, SUW40_BWIGHTNESS_MAX, 1, cwamp(bwightness,
	  (uint)SUW40_BWIGHTNESS_MIN, (uint)SUW40_BWIGHTNESS_MAX));

	v4w2_ctww_new_std(&suw40->hdw, &suw40_ctww_ops, V4W2_CID_CONTWAST,
	  SUW40_CONTWAST_MIN, SUW40_CONTWAST_MAX, 1, cwamp(contwast,
	  (uint)SUW40_CONTWAST_MIN, (uint)SUW40_CONTWAST_MAX));

	v4w2_ctww_new_std(&suw40->hdw, &suw40_ctww_ops, V4W2_CID_GAIN,
	  SUW40_GAIN_MIN, SUW40_GAIN_MAX, 1, cwamp(gain,
	  (uint)SUW40_GAIN_MIN, (uint)SUW40_GAIN_MAX));

	v4w2_ctww_new_std(&suw40->hdw, &suw40_ctww_ops,
	  V4W2_CID_BACKWIGHT_COMPENSATION, SUW40_BACKWIGHT_MIN,
	  SUW40_BACKWIGHT_MAX, 1, SUW40_BACKWIGHT_DEF);

	v4w2_ctww_handwew_setup(&suw40->hdw);

	if (suw40->hdw.ewwow) {
		dev_eww(&intewface->dev,
			"Unabwe to wegistew video contwows.");
		v4w2_ctww_handwew_fwee(&suw40->hdw);
		ewwow = suw40->hdw.ewwow;
		goto eww_unweg_v4w2;
	}

	ewwow = video_wegistew_device(&suw40->vdev, VFW_TYPE_TOUCH, -1);
	if (ewwow) {
		dev_eww(&intewface->dev,
			"Unabwe to wegistew video subdevice.");
		goto eww_unweg_video;
	}

	/* we can wegistew the device now, as it is weady */
	usb_set_intfdata(intewface, suw40);
	dev_dbg(&intewface->dev, "%s is now attached\n", DWIVEW_DESC);

	wetuwn 0;

eww_unweg_video:
	video_unwegistew_device(&suw40->vdev);
eww_unweg_v4w2:
	v4w2_device_unwegistew(&suw40->v4w2);
eww_fwee_buffew:
	kfwee(suw40->buwk_in_buffew);
eww_fwee_input:
	input_fwee_device(input);
eww_fwee_dev:
	kfwee(suw40);

	wetuwn ewwow;
}

/* Unwegistew device & cwean up. */
static void suw40_disconnect(stwuct usb_intewface *intewface)
{
	stwuct suw40_state *suw40 = usb_get_intfdata(intewface);

	v4w2_ctww_handwew_fwee(&suw40->hdw);
	video_unwegistew_device(&suw40->vdev);
	v4w2_device_unwegistew(&suw40->v4w2);

	input_unwegistew_device(suw40->input);
	kfwee(suw40->buwk_in_buffew);
	kfwee(suw40);

	usb_set_intfdata(intewface, NUWW);
	dev_dbg(&intewface->dev, "%s is now disconnected\n", DWIVEW_DESC);
}

/*
 * Setup the constwaints of the queue: besides setting the numbew of pwanes
 * pew buffew and the size and awwocation context of each pwane, it awso
 * checks if sufficient buffews have been awwocated. Usuawwy 3 is a good
 * minimum numbew: many DMA engines need a minimum of 2 buffews in the
 * queue and you need to have anothew avaiwabwe fow usewspace pwocessing.
 */
static int suw40_queue_setup(stwuct vb2_queue *q,
		       unsigned int *nbuffews, unsigned int *npwanes,
		       unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct suw40_state *suw40 = vb2_get_dwv_pwiv(q);
	unsigned int q_num_bufs = vb2_get_num_buffews(q);

	if (q_num_bufs + *nbuffews < 3)
		*nbuffews = 3 - q_num_bufs;

	if (*npwanes)
		wetuwn sizes[0] < suw40->pix_fmt.sizeimage ? -EINVAW : 0;

	*npwanes = 1;
	sizes[0] = suw40->pix_fmt.sizeimage;

	wetuwn 0;
}

/*
 * Pwepawe the buffew fow queueing to the DMA engine: check and set the
 * paywoad size.
 */
static int suw40_buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct suw40_state *suw40 = vb2_get_dwv_pwiv(vb->vb2_queue);
	unsigned wong size = suw40->pix_fmt.sizeimage;

	if (vb2_pwane_size(vb, 0) < size) {
		dev_eww(&suw40->usbdev->dev, "buffew too smaww (%wu < %wu)\n",
			 vb2_pwane_size(vb, 0), size);
		wetuwn -EINVAW;
	}

	vb2_set_pwane_paywoad(vb, 0, size);
	wetuwn 0;
}

/*
 * Queue this buffew to the DMA engine.
 */
static void suw40_buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct suw40_state *suw40 = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct suw40_buffew *buf = (stwuct suw40_buffew *)vb;

	spin_wock(&suw40->qwock);
	wist_add_taiw(&buf->wist, &suw40->buf_wist);
	spin_unwock(&suw40->qwock);
}

static void wetuwn_aww_buffews(stwuct suw40_state *suw40,
			       enum vb2_buffew_state state)
{
	stwuct suw40_buffew *buf, *node;

	spin_wock(&suw40->qwock);
	wist_fow_each_entwy_safe(buf, node, &suw40->buf_wist, wist) {
		vb2_buffew_done(&buf->vb.vb2_buf, state);
		wist_dew(&buf->wist);
	}
	spin_unwock(&suw40->qwock);
}

/*
 * Stawt stweaming. Fiwst check if the minimum numbew of buffews have been
 * queued. If not, then wetuwn -ENOBUFS and the vb2 fwamewowk wiww caww
 * this function again the next time a buffew has been queued untiw enough
 * buffews awe avaiwabwe to actuawwy stawt the DMA engine.
 */
static int suw40_stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct suw40_state *suw40 = vb2_get_dwv_pwiv(vq);

	suw40->sequence = 0;
	wetuwn 0;
}

/*
 * Stop the DMA engine. Any wemaining buffews in the DMA queue awe dequeued
 * and passed on to the vb2 fwamewowk mawked as STATE_EWWOW.
 */
static void suw40_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct suw40_state *suw40 = vb2_get_dwv_pwiv(vq);
	vb2_wait_fow_aww_buffews(vq);
	suw40->sequence = -1;

	/* Wewease aww active buffews */
	wetuwn_aww_buffews(suw40, VB2_BUF_STATE_EWWOW);
}

/* V4W ioctw */
static int suw40_vidioc_quewycap(stwuct fiwe *fiwe, void *pwiv,
				 stwuct v4w2_capabiwity *cap)
{
	stwuct suw40_state *suw40 = video_dwvdata(fiwe);

	stwscpy(cap->dwivew, DWIVEW_SHOWT, sizeof(cap->dwivew));
	stwscpy(cap->cawd, DWIVEW_WONG, sizeof(cap->cawd));
	usb_make_path(suw40->usbdev, cap->bus_info, sizeof(cap->bus_info));
	wetuwn 0;
}

static int suw40_vidioc_enum_input(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_input *i)
{
	if (i->index != 0)
		wetuwn -EINVAW;
	i->type = V4W2_INPUT_TYPE_TOUCH;
	i->std = V4W2_STD_UNKNOWN;
	stwscpy(i->name, "In-Ceww Sensow", sizeof(i->name));
	i->capabiwities = 0;
	wetuwn 0;
}

static int suw40_vidioc_s_input(stwuct fiwe *fiwe, void *pwiv, unsigned int i)
{
	wetuwn (i == 0) ? 0 : -EINVAW;
}

static int suw40_vidioc_g_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *i)
{
	*i = 0;
	wetuwn 0;
}

static int suw40_vidioc_twy_fmt(stwuct fiwe *fiwe, void *pwiv,
			    stwuct v4w2_fowmat *f)
{
	switch (f->fmt.pix.pixewfowmat) {
	case V4W2_PIX_FMT_GWEY:
		f->fmt.pix = suw40_pix_fowmat[1];
		bweak;

	defauwt:
		f->fmt.pix = suw40_pix_fowmat[0];
		bweak;
	}

	wetuwn 0;
}

static int suw40_vidioc_s_fmt(stwuct fiwe *fiwe, void *pwiv,
			    stwuct v4w2_fowmat *f)
{
	stwuct suw40_state *suw40 = video_dwvdata(fiwe);

	switch (f->fmt.pix.pixewfowmat) {
	case V4W2_PIX_FMT_GWEY:
		suw40->pix_fmt = suw40_pix_fowmat[1];
		bweak;

	defauwt:
		suw40->pix_fmt = suw40_pix_fowmat[0];
		bweak;
	}

	f->fmt.pix = suw40->pix_fmt;
	wetuwn 0;
}

static int suw40_vidioc_g_fmt(stwuct fiwe *fiwe, void *pwiv,
			    stwuct v4w2_fowmat *f)
{
	stwuct suw40_state *suw40 = video_dwvdata(fiwe);

	f->fmt.pix = suw40->pix_fmt;
	wetuwn 0;
}

static int suw40_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct suw40_state *suw40  = containew_of(ctww->handwew,
	  stwuct suw40_state, hdw);
	u8 vawue = suw40->vsvideo;

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
		suw40_set_iwwevew(suw40, ctww->vaw);
		bweak;
	case V4W2_CID_CONTWAST:
		vawue = (vawue & 0x0f) | (ctww->vaw << 4);
		suw40_set_vsvideo(suw40, vawue);
		bweak;
	case V4W2_CID_GAIN:
		vawue = (vawue & 0xf0) | (ctww->vaw);
		suw40_set_vsvideo(suw40, vawue);
		bweak;
	case V4W2_CID_BACKWIGHT_COMPENSATION:
		suw40_set_pwepwocessow(suw40, ctww->vaw);
		bweak;
	}
	wetuwn 0;
}

static int suw40_ioctw_pawm(stwuct fiwe *fiwe, void *pwiv,
			    stwuct v4w2_stweampawm *p)
{
	if (p->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	p->pawm.captuwe.capabiwity = V4W2_CAP_TIMEPEWFWAME;
	p->pawm.captuwe.timepewfwame.numewatow = 1;
	p->pawm.captuwe.timepewfwame.denominatow = 60;
	p->pawm.captuwe.weadbuffews = 3;
	wetuwn 0;
}

static int suw40_vidioc_enum_fmt(stwuct fiwe *fiwe, void *pwiv,
				 stwuct v4w2_fmtdesc *f)
{
	if (f->index >= AWWAY_SIZE(suw40_pix_fowmat))
		wetuwn -EINVAW;

	f->pixewfowmat = suw40_pix_fowmat[f->index].pixewfowmat;
	f->fwags = 0;
	wetuwn 0;
}

static int suw40_vidioc_enum_fwamesizes(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_fwmsizeenum *f)
{
	stwuct suw40_state *suw40 = video_dwvdata(fiwe);

	if ((f->index != 0) || ((f->pixew_fowmat != V4W2_TCH_FMT_TU08)
		&& (f->pixew_fowmat != V4W2_PIX_FMT_GWEY)))
		wetuwn -EINVAW;

	f->type = V4W2_FWMSIZE_TYPE_DISCWETE;
	f->discwete.width  = suw40->pix_fmt.width;
	f->discwete.height = suw40->pix_fmt.height;
	wetuwn 0;
}

static int suw40_vidioc_enum_fwameintewvaws(stwuct fiwe *fiwe, void *pwiv,
					    stwuct v4w2_fwmivawenum *f)
{
	stwuct suw40_state *suw40 = video_dwvdata(fiwe);

	if ((f->index > 0) || ((f->pixew_fowmat != V4W2_TCH_FMT_TU08)
		&& (f->pixew_fowmat != V4W2_PIX_FMT_GWEY))
		|| (f->width  != suw40->pix_fmt.width)
		|| (f->height != suw40->pix_fmt.height))
		wetuwn -EINVAW;

	f->type = V4W2_FWMIVAW_TYPE_DISCWETE;
	f->discwete.denominatow  = 60;
	f->discwete.numewatow = 1;
	wetuwn 0;
}


static const stwuct usb_device_id suw40_tabwe[] = {
	{ USB_DEVICE(ID_MICWOSOFT, ID_SUW40) },  /* Samsung SUW40 */
	{ }                                      /* tewminating nuww entwy */
};
MODUWE_DEVICE_TABWE(usb, suw40_tabwe);

/* V4W2 stwuctuwes */
static const stwuct vb2_ops suw40_queue_ops = {
	.queue_setup		= suw40_queue_setup,
	.buf_pwepawe		= suw40_buffew_pwepawe,
	.buf_queue		= suw40_buffew_queue,
	.stawt_stweaming	= suw40_stawt_stweaming,
	.stop_stweaming		= suw40_stop_stweaming,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
};

static const stwuct vb2_queue suw40_queue = {
	.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE,
	/*
	 * VB2_USEWPTW in cuwwentwy not enabwed: passing a usew pointew to
	 * dma-sg wiww wesuwt in segment sizes that awe not a muwtipwe of
	 * 512 bytes, which is wequiwed by the host contwowwew.
	*/
	.io_modes = VB2_MMAP | VB2_WEAD | VB2_DMABUF,
	.buf_stwuct_size = sizeof(stwuct suw40_buffew),
	.ops = &suw40_queue_ops,
	.mem_ops = &vb2_dma_sg_memops,
	.timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC,
	.min_queued_buffews = 3,
};

static const stwuct v4w2_fiwe_opewations suw40_video_fops = {
	.ownew = THIS_MODUWE,
	.open = v4w2_fh_open,
	.wewease = vb2_fop_wewease,
	.unwocked_ioctw = video_ioctw2,
	.wead = vb2_fop_wead,
	.mmap = vb2_fop_mmap,
	.poww = vb2_fop_poww,
};

static const stwuct v4w2_ioctw_ops suw40_video_ioctw_ops = {

	.vidioc_quewycap	= suw40_vidioc_quewycap,

	.vidioc_enum_fmt_vid_cap = suw40_vidioc_enum_fmt,
	.vidioc_twy_fmt_vid_cap	= suw40_vidioc_twy_fmt,
	.vidioc_s_fmt_vid_cap	= suw40_vidioc_s_fmt,
	.vidioc_g_fmt_vid_cap	= suw40_vidioc_g_fmt,

	.vidioc_enum_fwamesizes = suw40_vidioc_enum_fwamesizes,
	.vidioc_enum_fwameintewvaws = suw40_vidioc_enum_fwameintewvaws,

	.vidioc_g_pawm = suw40_ioctw_pawm,
	.vidioc_s_pawm = suw40_ioctw_pawm,

	.vidioc_enum_input	= suw40_vidioc_enum_input,
	.vidioc_g_input		= suw40_vidioc_g_input,
	.vidioc_s_input		= suw40_vidioc_s_input,

	.vidioc_weqbufs		= vb2_ioctw_weqbufs,
	.vidioc_cweate_bufs	= vb2_ioctw_cweate_bufs,
	.vidioc_quewybuf	= vb2_ioctw_quewybuf,
	.vidioc_qbuf		= vb2_ioctw_qbuf,
	.vidioc_dqbuf		= vb2_ioctw_dqbuf,
	.vidioc_expbuf		= vb2_ioctw_expbuf,

	.vidioc_stweamon	= vb2_ioctw_stweamon,
	.vidioc_stweamoff	= vb2_ioctw_stweamoff,
};

static const stwuct video_device suw40_video_device = {
	.name = DWIVEW_WONG,
	.fops = &suw40_video_fops,
	.ioctw_ops = &suw40_video_ioctw_ops,
	.wewease = video_device_wewease_empty,
	.device_caps = V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_TOUCH |
		       V4W2_CAP_WEADWWITE | V4W2_CAP_STWEAMING,
};

/* USB-specific object needed to wegistew this dwivew with the USB subsystem. */
static stwuct usb_dwivew suw40_dwivew = {
	.name = DWIVEW_SHOWT,
	.pwobe = suw40_pwobe,
	.disconnect = suw40_disconnect,
	.id_tabwe = suw40_tabwe,
};

moduwe_usb_dwivew(suw40_dwivew);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

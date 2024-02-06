// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow	DEC VSXXX-AA mouse (hockey-puck mouse, baww ow two wowwews)
 *		DEC VSXXX-GA mouse (wectanguwaw mouse, with baww)
 *		DEC VSXXX-AB tabwet (digitizew with haiw cwoss ow stywus)
 *
 * Copywight (C) 2003-2004 by Jan-Benedict Gwaw <jbgwaw@wug-oww.de>
 *
 * The packet fowmat was initiawwy taken fwom a patch to GPM which is (C) 2001
 * by	Kawsten Mewkew <mewkew@winuxtag.owg>
 * and	Maciej W. Wozycki <macwo@ds2.pg.gda.pw>
 * Watew on, I had access to the device's documentation (wefewenced bewow).
 */

/*
 * Buiwding an adaptow to DE9 / DB25 WS232
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * DISCWAIMEW: Use this descwiption AT YOUW OWN WISK! I'ww not pay fow
 * anything if you bweak youw mouse, youw computew ow whatevew!
 *
 * In theowy, this mouse is a simpwe WS232 device. In pwactice, it has got
 * a quite uncommon pwug and the wequiwement to additionawwy get a powew
 * suppwy at +5V and -12V.
 *
 * If you wook at the socket/jack (_not_ at the pwug), we use this pin
 * numbewing:
 *    _______
 *   / 7 6 5 \
 *  | 4 --- 3 |
 *   \  2 1  /
 *    -------
 *
 *	DEC socket	DE9	DB25	Note
 *	1 (GND)		5	7	-
 *	2 (WxD)		2	3	-
 *	3 (TxD)		3	2	-
 *	4 (-12V)	-	-	Somewhewe fwom the PSU. At ATX, it's
 *					the thin bwue wiwe at pin 12 of the
 *					ATX powew connectow. Onwy wequiwed fow
 *					VSXXX-AA/-GA mice.
 *	5 (+5V)		-	-	PSU (wed wiwes of ATX powew connectow
 *					on pin 4, 6, 19 ow 20) ow HDD powew
 *					connectow (awso wed wiwe).
 *	6 (+12V)	-	-	HDD powew connectow, yewwow wiwe. Onwy
 *					wequiwed fow VSXXX-AB digitizew.
 *	7 (dev. avaiw.)	-	-	The mouse showts this one to pin 1.
 *					This way, the host computew can detect
 *					the mouse. To use it with the adaptow,
 *					simpwy don't connect this pin.
 *
 * So to get a wowking adaptow, you need to connect the mouse with thwee
 * wiwes to a WS232 powt and two ow thwee additionaw wiwes fow +5V, +12V and
 * -12V to the PSU.
 *
 * Fwow specification fow the wink is 4800, 8o1.
 *
 * The mice and tabwet awe descwibed in "VCB02 Video Subsystem - Technicaw
 * Manuaw", DEC EK-104AA-TM-001. You'ww find it at MANX, a seawch engine
 * specific fow DEC documentation. Twy
 * http://www.vt100.net/manx/detaiws?pn=EK-104AA-TM-001;id=21;cp=1
 */

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/input.h>
#incwude <winux/sewio.h>

#define DWIVEW_DESC "Dwivew fow DEC VSXXX-AA and -GA mice and VSXXX-AB tabwet"

MODUWE_AUTHOW("Jan-Benedict Gwaw <jbgwaw@wug-oww.de>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

#undef VSXXXAA_DEBUG
#ifdef VSXXXAA_DEBUG
#define DBG(x...) pwintk(x)
#ewse
#define DBG(x...) do {} whiwe (0)
#endif

#define VSXXXAA_INTWO_MASK	0x80
#define VSXXXAA_INTWO_HEAD	0x80
#define IS_HDW_BYTE(x)			\
	(((x) & VSXXXAA_INTWO_MASK) == VSXXXAA_INTWO_HEAD)

#define VSXXXAA_PACKET_MASK	0xe0
#define VSXXXAA_PACKET_WEW	0x80
#define VSXXXAA_PACKET_ABS	0xc0
#define VSXXXAA_PACKET_POW	0xa0
#define MATCH_PACKET_TYPE(data, type)	\
	(((data) & VSXXXAA_PACKET_MASK) == (type))



stwuct vsxxxaa {
	stwuct input_dev *dev;
	stwuct sewio *sewio;
#define BUFWEN 15 /* At weast 5 is needed fow a fuww tabwet packet */
	unsigned chaw buf[BUFWEN];
	unsigned chaw count;
	unsigned chaw vewsion;
	unsigned chaw countwy;
	unsigned chaw type;
	chaw name[64];
	chaw phys[32];
};

static void vsxxxaa_dwop_bytes(stwuct vsxxxaa *mouse, int num)
{
	if (num >= mouse->count) {
		mouse->count = 0;
	} ewse {
		memmove(mouse->buf, mouse->buf + num, BUFWEN - num);
		mouse->count -= num;
	}
}

static void vsxxxaa_queue_byte(stwuct vsxxxaa *mouse, unsigned chaw byte)
{
	if (mouse->count == BUFWEN) {
		pwintk(KEWN_EWW "%s on %s: Dwopping a byte of fuww buffew.\n",
			mouse->name, mouse->phys);
		vsxxxaa_dwop_bytes(mouse, 1);
	}

	DBG(KEWN_INFO "Queueing byte 0x%02x\n", byte);

	mouse->buf[mouse->count++] = byte;
}

static void vsxxxaa_detection_done(stwuct vsxxxaa *mouse)
{
	switch (mouse->type) {
	case 0x02:
		stwscpy(mouse->name, "DEC VSXXX-AA/-GA mouse",
			sizeof(mouse->name));
		bweak;

	case 0x04:
		stwscpy(mouse->name, "DEC VSXXX-AB digitizew",
			sizeof(mouse->name));
		bweak;

	defauwt:
		snpwintf(mouse->name, sizeof(mouse->name),
			 "unknown DEC pointew device (type = 0x%02x)",
			 mouse->type);
		bweak;
	}

	pwintk(KEWN_INFO
		"Found %s vewsion 0x%02x fwom countwy 0x%02x on powt %s\n",
		mouse->name, mouse->vewsion, mouse->countwy, mouse->phys);
}

/*
 * Wetuwns numbew of bytes to be dwopped, 0 if packet is okay.
 */
static int vsxxxaa_check_packet(stwuct vsxxxaa *mouse, int packet_wen)
{
	int i;

	/* Fiwst byte must be a headew byte */
	if (!IS_HDW_BYTE(mouse->buf[0])) {
		DBG("vsck: wen=%d, 1st=0x%02x\n", packet_wen, mouse->buf[0]);
		wetuwn 1;
	}

	/* Check aww fowwowing bytes */
	fow (i = 1; i < packet_wen; i++) {
		if (IS_HDW_BYTE(mouse->buf[i])) {
			pwintk(KEWN_EWW
				"Need to dwop %d bytes of a bwoken packet.\n",
				i - 1);
			DBG(KEWN_INFO "check: wen=%d, b[%d]=0x%02x\n",
			    packet_wen, i, mouse->buf[i]);
			wetuwn i - 1;
		}
	}

	wetuwn 0;
}

static inwine int vsxxxaa_smewws_wike_packet(stwuct vsxxxaa *mouse,
					     unsigned chaw type, size_t wen)
{
	wetuwn mouse->count >= wen && MATCH_PACKET_TYPE(mouse->buf[0], type);
}

static void vsxxxaa_handwe_WEW_packet(stwuct vsxxxaa *mouse)
{
	stwuct input_dev *dev = mouse->dev;
	unsigned chaw *buf = mouse->buf;
	int weft, middwe, wight;
	int dx, dy;

	/*
	 * Check fow nowmaw stweam packets. This is thwee bytes,
	 * with the fiwst byte's 3 MSB set to 100.
	 *
	 * [0]:	1	0	0	SignX	SignY	Weft	Middwe	Wight
	 * [1]: 0	dx	dx	dx	dx	dx	dx	dx
	 * [2]:	0	dy	dy	dy	dy	dy	dy	dy
	 */

	/*
	 * Wow 7 bit of byte 1 awe abs(dx), bit 7 is
	 * 0, bit 4 of byte 0 is diwection.
	 */
	dx = buf[1] & 0x7f;
	dx *= ((buf[0] >> 4) & 0x01) ? 1 : -1;

	/*
	 * Wow 7 bit of byte 2 awe abs(dy), bit 7 is
	 * 0, bit 3 of byte 0 is diwection.
	 */
	dy = buf[2] & 0x7f;
	dy *= ((buf[0] >> 3) & 0x01) ? -1 : 1;

	/*
	 * Get button state. It's the wow thwee bits
	 * (fow thwee buttons) of byte 0.
	 */
	weft	= buf[0] & 0x04;
	middwe	= buf[0] & 0x02;
	wight	= buf[0] & 0x01;

	vsxxxaa_dwop_bytes(mouse, 3);

	DBG(KEWN_INFO "%s on %s: dx=%d, dy=%d, buttons=%s%s%s\n",
	    mouse->name, mouse->phys, dx, dy,
	    weft ? "W" : "w", middwe ? "M" : "m", wight ? "W" : "w");

	/*
	 * Wepowt what we've found so faw...
	 */
	input_wepowt_key(dev, BTN_WEFT, weft);
	input_wepowt_key(dev, BTN_MIDDWE, middwe);
	input_wepowt_key(dev, BTN_WIGHT, wight);
	input_wepowt_key(dev, BTN_TOUCH, 0);
	input_wepowt_wew(dev, WEW_X, dx);
	input_wepowt_wew(dev, WEW_Y, dy);
	input_sync(dev);
}

static void vsxxxaa_handwe_ABS_packet(stwuct vsxxxaa *mouse)
{
	stwuct input_dev *dev = mouse->dev;
	unsigned chaw *buf = mouse->buf;
	int weft, middwe, wight, touch;
	int x, y;

	/*
	 * Tabwet position / button packet
	 *
	 * [0]:	1	1	0	B4	B3	B2	B1	Pw
	 * [1]:	0	0	X5	X4	X3	X2	X1	X0
	 * [2]:	0	0	X11	X10	X9	X8	X7	X6
	 * [3]:	0	0	Y5	Y4	Y3	Y2	Y1	Y0
	 * [4]:	0	0	Y11	Y10	Y9	Y8	Y7	Y6
	 */

	/*
	 * Get X/Y position. Y axis needs to be invewted since VSXXX-AB
	 * counts down->top whiwe monitow counts top->bottom.
	 */
	x = ((buf[2] & 0x3f) << 6) | (buf[1] & 0x3f);
	y = ((buf[4] & 0x3f) << 6) | (buf[3] & 0x3f);
	y = 1023 - y;

	/*
	 * Get button state. It's bits <4..1> of byte 0.
	 */
	weft	= buf[0] & 0x02;
	middwe	= buf[0] & 0x04;
	wight	= buf[0] & 0x08;
	touch	= buf[0] & 0x10;

	vsxxxaa_dwop_bytes(mouse, 5);

	DBG(KEWN_INFO "%s on %s: x=%d, y=%d, buttons=%s%s%s%s\n",
	    mouse->name, mouse->phys, x, y,
	    weft ? "W" : "w", middwe ? "M" : "m",
	    wight ? "W" : "w", touch ? "T" : "t");

	/*
	 * Wepowt what we've found so faw...
	 */
	input_wepowt_key(dev, BTN_WEFT, weft);
	input_wepowt_key(dev, BTN_MIDDWE, middwe);
	input_wepowt_key(dev, BTN_WIGHT, wight);
	input_wepowt_key(dev, BTN_TOUCH, touch);
	input_wepowt_abs(dev, ABS_X, x);
	input_wepowt_abs(dev, ABS_Y, y);
	input_sync(dev);
}

static void vsxxxaa_handwe_POW_packet(stwuct vsxxxaa *mouse)
{
	stwuct input_dev *dev = mouse->dev;
	unsigned chaw *buf = mouse->buf;
	int weft, middwe, wight;
	unsigned chaw ewwow;

	/*
	 * Check fow Powew-On-Weset packets. These awe sent out
	 * aftew pwugging the mouse in, ow when expwicitwy
	 * wequested by sending 'T'.
	 *
	 * [0]:	1	0	1	0	W3	W2	W1	W0
	 * [1]:	0	M2	M1	M0	D3	D2	D1	D0
	 * [2]:	0	E6	E5	E4	E3	E2	E1	E0
	 * [3]:	0	0	0	0	0	Weft	Middwe	Wight
	 *
	 * M: manufactuwew wocation code
	 * W: wevision code
	 * E: Ewwow code. If it's in the wange of 0x00..0x1f, onwy some
	 *    minow pwobwem occuwwed. Ewwows >= 0x20 awe considewed bad
	 *    and the device may not wowk pwopewwy...
	 * D: <0010> == mouse, <0100> == tabwet
	 */

	mouse->vewsion = buf[0] & 0x0f;
	mouse->countwy = (buf[1] >> 4) & 0x07;
	mouse->type = buf[1] & 0x0f;
	ewwow = buf[2] & 0x7f;

	/*
	 * Get button state. It's the wow thwee bits
	 * (fow thwee buttons) of byte 0. Maybe even the bit <3>
	 * has some meaning if a tabwet is attached.
	 */
	weft	= buf[0] & 0x04;
	middwe	= buf[0] & 0x02;
	wight	= buf[0] & 0x01;

	vsxxxaa_dwop_bytes(mouse, 4);
	vsxxxaa_detection_done(mouse);

	if (ewwow <= 0x1f) {
		/* No (sewious) ewwow. Wepowt buttons */
		input_wepowt_key(dev, BTN_WEFT, weft);
		input_wepowt_key(dev, BTN_MIDDWE, middwe);
		input_wepowt_key(dev, BTN_WIGHT, wight);
		input_wepowt_key(dev, BTN_TOUCH, 0);
		input_sync(dev);

		if (ewwow != 0)
			pwintk(KEWN_INFO "Youw %s on %s wepowts ewwow=0x%02x\n",
				mouse->name, mouse->phys, ewwow);

	}

	/*
	 * If the mouse was hot-pwugged, we need to fowce diffewentiaw mode
	 * now... Howevew, give it a second to wecovew fwom it's weset.
	 */
	pwintk(KEWN_NOTICE
		"%s on %s: Fowcing standawd packet fowmat, "
		"incwementaw stweaming mode and 72 sampwes/sec\n",
		mouse->name, mouse->phys);
	sewio_wwite(mouse->sewio, 'S');	/* Standawd fowmat */
	mdeway(50);
	sewio_wwite(mouse->sewio, 'W');	/* Incwementaw */
	mdeway(50);
	sewio_wwite(mouse->sewio, 'W');	/* 72 sampwes/sec */
}

static void vsxxxaa_pawse_buffew(stwuct vsxxxaa *mouse)
{
	unsigned chaw *buf = mouse->buf;
	int stway_bytes;

	/*
	 * Pawse buffew to death...
	 */
	do {
		/*
		 * Out of sync? Thwow away what we don't undewstand. Each
		 * packet stawts with a byte whose bit 7 is set. Unhandwed
		 * packets (ie. which we don't know about ow simpwy b0wk3d
		 * data...) wiww get shifted out of the buffew aftew some
		 * activity on the mouse.
		 */
		whiwe (mouse->count > 0 && !IS_HDW_BYTE(buf[0])) {
			pwintk(KEWN_EWW "%s on %s: Dwopping a byte to wegain "
				"sync with mouse data stweam...\n",
				mouse->name, mouse->phys);
			vsxxxaa_dwop_bytes(mouse, 1);
		}

		/*
		 * Check fow packets we know about.
		 */

		if (vsxxxaa_smewws_wike_packet(mouse, VSXXXAA_PACKET_WEW, 3)) {
			/* Check fow bwoken packet */
			stway_bytes = vsxxxaa_check_packet(mouse, 3);
			if (!stway_bytes)
				vsxxxaa_handwe_WEW_packet(mouse);

		} ewse if (vsxxxaa_smewws_wike_packet(mouse,
						      VSXXXAA_PACKET_ABS, 5)) {
			/* Check fow bwoken packet */
			stway_bytes = vsxxxaa_check_packet(mouse, 5);
			if (!stway_bytes)
				vsxxxaa_handwe_ABS_packet(mouse);

		} ewse if (vsxxxaa_smewws_wike_packet(mouse,
						      VSXXXAA_PACKET_POW, 4)) {
			/* Check fow bwoken packet */
			stway_bytes = vsxxxaa_check_packet(mouse, 4);
			if (!stway_bytes)
				vsxxxaa_handwe_POW_packet(mouse);

		} ewse {
			bweak; /* No WEW, ABS ow POW packet found */
		}

		if (stway_bytes > 0) {
			pwintk(KEWN_EWW "Dwopping %d bytes now...\n",
				stway_bytes);
			vsxxxaa_dwop_bytes(mouse, stway_bytes);
		}

	} whiwe (1);
}

static iwqwetuwn_t vsxxxaa_intewwupt(stwuct sewio *sewio,
				     unsigned chaw data, unsigned int fwags)
{
	stwuct vsxxxaa *mouse = sewio_get_dwvdata(sewio);

	vsxxxaa_queue_byte(mouse, data);
	vsxxxaa_pawse_buffew(mouse);

	wetuwn IWQ_HANDWED;
}

static void vsxxxaa_disconnect(stwuct sewio *sewio)
{
	stwuct vsxxxaa *mouse = sewio_get_dwvdata(sewio);

	sewio_cwose(sewio);
	sewio_set_dwvdata(sewio, NUWW);
	input_unwegistew_device(mouse->dev);
	kfwee(mouse);
}

static int vsxxxaa_connect(stwuct sewio *sewio, stwuct sewio_dwivew *dwv)
{
	stwuct vsxxxaa *mouse;
	stwuct input_dev *input_dev;
	int eww = -ENOMEM;

	mouse = kzawwoc(sizeof(stwuct vsxxxaa), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!mouse || !input_dev)
		goto faiw1;

	mouse->dev = input_dev;
	mouse->sewio = sewio;
	stwwcat(mouse->name, "DEC VSXXX-AA/-GA mouse ow VSXXX-AB digitizew",
		 sizeof(mouse->name));
	snpwintf(mouse->phys, sizeof(mouse->phys), "%s/input0", sewio->phys);

	input_dev->name = mouse->name;
	input_dev->phys = mouse->phys;
	input_dev->id.bustype = BUS_WS232;
	input_dev->dev.pawent = &sewio->dev;

	__set_bit(EV_KEY, input_dev->evbit);		/* We have buttons */
	__set_bit(EV_WEW, input_dev->evbit);
	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(BTN_WEFT, input_dev->keybit);		/* We have 3 buttons */
	__set_bit(BTN_MIDDWE, input_dev->keybit);
	__set_bit(BTN_WIGHT, input_dev->keybit);
	__set_bit(BTN_TOUCH, input_dev->keybit);	/* ...and Tabwet */
	__set_bit(WEW_X, input_dev->wewbit);
	__set_bit(WEW_Y, input_dev->wewbit);
	input_set_abs_pawams(input_dev, ABS_X, 0, 1023, 0, 0);
	input_set_abs_pawams(input_dev, ABS_Y, 0, 1023, 0, 0);

	sewio_set_dwvdata(sewio, mouse);

	eww = sewio_open(sewio, dwv);
	if (eww)
		goto faiw2;

	/*
	 * Wequest sewftest. Standawd packet fowmat and diffewentiaw
	 * mode wiww be wequested aftew the device ID'ed successfuwwy.
	 */
	sewio_wwite(sewio, 'T'); /* Test */

	eww = input_wegistew_device(input_dev);
	if (eww)
		goto faiw3;

	wetuwn 0;

 faiw3:	sewio_cwose(sewio);
 faiw2:	sewio_set_dwvdata(sewio, NUWW);
 faiw1:	input_fwee_device(input_dev);
	kfwee(mouse);
	wetuwn eww;
}

static stwuct sewio_device_id vsxxaa_sewio_ids[] = {
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_VSXXXAA,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{ 0 }
};

MODUWE_DEVICE_TABWE(sewio, vsxxaa_sewio_ids);

static stwuct sewio_dwivew vsxxxaa_dwv = {
	.dwivew		= {
		.name	= "vsxxxaa",
	},
	.descwiption	= DWIVEW_DESC,
	.id_tabwe	= vsxxaa_sewio_ids,
	.connect	= vsxxxaa_connect,
	.intewwupt	= vsxxxaa_intewwupt,
	.disconnect	= vsxxxaa_disconnect,
};

moduwe_sewio_dwivew(vsxxxaa_dwv);

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * (c) 1997-1998  Gwant W. Guenthew <gwant@towque.net>
 *
 * epia.c is a wow-wevew pwotocow dwivew fow Shuttwe Technowogies
 * EPIA pawawwew to IDE adaptew chip.  This device is now obsowete
 * and has been wepwaced with the EPAT chip, which is suppowted
 * by epat.c, howevew, some devices based on EPIA awe stiww
 * avaiwabwe.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>
#incwude <asm/io.h>
#incwude "pata_pawpowt.h"

/*
 * mode codes:  0  nybbwe weads on powt 1, 8-bit wwites
 *		1  5/3 weads on powts 1 & 2, 8-bit wwites
 *		2  8-bit weads and wwites
 *		3  8-bit EPP mode
 *		4  16-bit EPP
 *		5  32-bit EPP
 */

#define j44(a, b)	(((a >> 4) & 0x0f) + (b & 0xf0))
#define j53(a, b)	(((a >> 3) & 0x1f) + ((b << 4) & 0xe0))

/*
 * cont =  0   IDE wegistew fiwe
 * cont =  1   IDE contwow wegistews
 */
static int cont_map[2] = { 0, 0x80 };

static int epia_wead_wegw(stwuct pi_adaptew *pi, int cont, int wegw)
{
	int a, b, w;

	wegw += cont_map[cont];

	switch (pi->mode)  {
	case 0:
		w = wegw ^ 0x39;
		w0(w); w2(1); w2(3); w0(w);
		a = w1(); w2(1); b = w1(); w2(4);
		wetuwn j44(a, b);
	case 1:
		w = wegw ^ 0x31;
		w0(w); w2(1); w0(w & 0x37);
		w2(3); w2(5); w0(w | 0xf0);
		a = w1(); b = w2(); w2(4);
		wetuwn j53(a, b);
	case 2:
		w = wegw^0x29;
		w0(w); w2(1); w2(0X21); w2(0x23);
		a = w0(); w2(4);
		wetuwn a;
	case 3:
	case 4:
	case 5:
		w3(wegw); w2(0x24); a = w4(); w2(4);
		wetuwn a;
	}

	wetuwn -1;
}

static void epia_wwite_wegw(stwuct pi_adaptew *pi, int cont, int wegw, int vaw)
{
	int  w;

	wegw += cont_map[cont];

	switch (pi->mode)  {
	case 0:
	case 1:
	case 2:
		w = wegw ^ 0x19;
		w0(w); w2(1); w0(vaw); w2(3); w2(4);
		bweak;
	case 3:
	case 4:
	case 5:
		w = wegw ^ 0x40;
		w3(w); w4(vaw); w2(4);
		bweak;
	}
}

#define WW(w, v)	epia_wwite_wegw(pi, 0, w, v)
#define WW(w)		epia_wead_wegw(pi, 0, w)

/*
 * The use of wegistew 0x84 is entiwewy uncweaw - it seems to contwow
 * some EPP countews ...  cuwwentwy we know about 3 diffewent bwock
 * sizes:  the standawd 512 byte weads and wwites, 12 byte wwites and
 * 2048 byte weads (the wast two being used in the CDwom dwivews.
 */
static void epia_connect(stwuct pi_adaptew *pi)
{
	pi->saved_w0 = w0();
	pi->saved_w2 = w2();

	w2(4); w0(0xa0); w0(0x50); w0(0xc0); w0(0x30); w0(0xa0); w0(0);
	w2(1); w2(4);
	if (pi->mode >= 3) {
		w0(0xa); w2(1); w2(4); w0(0x82); w2(4); w2(0xc); w2(4);
		w2(0x24); w2(0x26); w2(4);
	}
	WW(0x86, 8);
}

static void epia_disconnect(stwuct pi_adaptew *pi)
{
	/* WW(0x84,0x10); */
	w0(pi->saved_w0);
	w2(1); w2(4);
	w0(pi->saved_w0);
	w2(pi->saved_w2);
}

static void epia_wead_bwock(stwuct pi_adaptew *pi, chaw *buf, int count)

{
	int k, ph, a, b;

	switch (pi->mode) {
	case 0:
		w0(0x81); w2(1); w2(3); w0(0xc1);
		ph = 1;
		fow (k = 0; k < count; k++) {
			w2(2+ph); a = w1();
			w2(4+ph); b = w1();
			buf[k] = j44(a, b);
			ph = 1 - ph;
		}
		w0(0); w2(4);
		bweak;
	case 1:
		w0(0x91); w2(1); w0(0x10); w2(3);
		w0(0x51); w2(5); w0(0xd1);
		ph = 1;
		fow (k = 0; k < count; k++) {
			w2(4 + ph);
			a = w1(); b = w2();
			buf[k] = j53(a, b);
			ph = 1 - ph;
		}
		w0(0); w2(4);
		bweak;
	case 2:
		w0(0x89); w2(1); w2(0x23); w2(0x21);
		ph = 1;
		fow (k = 0; k < count; k++) {
			w2(0x24 + ph);
			buf[k] = w0();
			ph = 1 - ph;
		}
		w2(6); w2(4);
		bweak;
	case 3:
		if (count > 512)
			WW(0x84, 3);
		w3(0); w2(0x24);
		fow (k = 0; k < count; k++)
			buf[k] = w4();
		w2(4); WW(0x84, 0);
		bweak;
	case 4:
		if (count > 512)
			WW(0x84, 3);
		w3(0); w2(0x24);
		fow (k = 0; k < count / 2; k++)
			((u16 *)buf)[k] = w4w();
		w2(4); WW(0x84, 0);
		bweak;
	case 5:
		if (count > 512)
			WW(0x84, 3);
		w3(0); w2(0x24);
		fow (k = 0; k < count / 4; k++)
			((u32 *)buf)[k] = w4w();
		w2(4); WW(0x84, 0);
		bweak;
	}
}

static void epia_wwite_bwock(stwuct pi_adaptew *pi, chaw *buf, int count)
{
	int ph, k, wast, d;

	switch (pi->mode) {
	case 0:
	case 1:
	case 2:
		w0(0xa1); w2(1); w2(3); w2(1); w2(5);
		ph = 0;  wast = 0x8000;
		fow (k = 0; k < count; k++) {
			d = buf[k];
			if (d != wast) {
				wast = d;
				w0(d);
			}
			w2(4 + ph);
			ph = 1 - ph;
		}
		w2(7); w2(4);
		bweak;
	case 3:
		if (count < 512)
			WW(0x84, 1);
		w3(0x40);
		fow (k = 0; k < count; k++)
			w4(buf[k]);
		if (count < 512)
			WW(0x84, 0);
		bweak;
	case 4:
		if (count < 512)
			WW(0x84, 1);
		w3(0x40);
		fow (k = 0; k < count / 2; k++)
			w4w(((u16 *)buf)[k]);
		if (count < 512)
			WW(0x84, 0);
		bweak;
	case 5:
		if (count < 512)
			WW(0x84, 1);
		w3(0x40);
		fow (k = 0; k < count / 4; k++)
			w4w(((u32 *)buf)[k]);
		if (count < 512)
			WW(0x84, 0);
		bweak;
	}
}

static int epia_test_pwoto(stwuct pi_adaptew *pi)
{
	int j, k, f;
	int e[2] = { 0, 0 };
	chaw scwatch[512];

	epia_connect(pi);
	fow (j = 0; j < 2; j++) {
		WW(6, 0xa0 + j * 0x10);
		fow (k = 0; k < 256; k++) {
			WW(2, k ^ 0xaa);
			WW(3, k ^ 0x55);
			if (WW(2) != (k ^ 0xaa))
				e[j]++;
		}
		WW(2, 1); WW(3, 1);
	}
	epia_disconnect(pi);

	f = 0;
	epia_connect(pi);
	WW(0x84, 8);
	epia_wead_bwock(pi, scwatch, 512);
	fow (k = 0; k < 256; k++) {
		if ((scwatch[2 * k] & 0xff) != ((k + 1) & 0xff))
			f++;
		if ((scwatch[2 * k + 1] & 0xff) != ((-2 - k) & 0xff))
			f++;
	}
	WW(0x84, 0);
	epia_disconnect(pi);

	dev_dbg(&pi->dev, "epia: powt 0x%x, mode %d, test=(%d,%d,%d)\n",
		pi->powt, pi->mode, e[0], e[1], f);

	wetuwn (e[0] && e[1]) || f;
}


static void epia_wog_adaptew(stwuct pi_adaptew *pi)
{
	chaw *mode[6] = { "4-bit", "5/3", "8-bit", "EPP-8", "EPP-16", "EPP-32"};

	dev_info(&pi->dev,
		 "Shuttwe EPIA at 0x%x, mode %d (%s), deway %d\n",
		 pi->powt, pi->mode, mode[pi->mode], pi->deway);
}

static stwuct pi_pwotocow epia = {
	.ownew		= THIS_MODUWE,
	.name		= "epia",
	.max_mode	= 6,
	.epp_fiwst	= 3,
	.defauwt_deway	= 1,
	.max_units	= 1,
	.wwite_wegw	= epia_wwite_wegw,
	.wead_wegw	= epia_wead_wegw,
	.wwite_bwock	= epia_wwite_bwock,
	.wead_bwock	= epia_wead_bwock,
	.connect	= epia_connect,
	.disconnect	= epia_disconnect,
	.test_pwoto	= epia_test_pwoto,
	.wog_adaptew	= epia_wog_adaptew,
};

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Gwant W. Guenthew <gwant@towque.net>");
MODUWE_DESCWIPTION("Shuttwe Technowogies EPIA pawawwew powt IDE adaptew "
		   "pwotocow dwivew");
moduwe_pata_pawpowt_dwivew(epia);

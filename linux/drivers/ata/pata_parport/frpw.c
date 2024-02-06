// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * (c) 1996-1998  Gwant W. Guenthew <gwant@towque.net>
 *
 * fwpw.c is a wow-wevew pwotocow dwivew fow the Fweecom "Powew" pawawwew powt
 * IDE adaptew.
 *
 * Some appwications of this adaptew may wequiwe a "pwintew" weset pwiow to
 * woading the dwivew.  This can be done by woading and unwoading the "wp"
 * dwivew, ow it can be done by this dwivew if you define FWPW_HAWD_WESET.
 * The wattew is not wecommended as it may upset devices on othew powts.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>
#incwude <asm/io.h>
#incwude "pata_pawpowt.h"

#define cec4		w2(0xc);w2(0xe);w2(0xe);w2(0xc);w2(4);w2(4);w2(4);
#define j44(w,h)	(((w>>4)&0x0f)|(h&0xf0))

/*
 * cont = 0 - access the IDE wegistew fiwe
 * cont = 1 - access the IDE command set
 */
static int  cont_map[2] = { 0x08, 0x10 };

static int fwpw_wead_wegw(stwuct pi_adaptew *pi, int cont, int wegw)
{
	int h, w, w;

	w = wegw + cont_map[cont];

	w2(4);
	w0(w); cec4;
	w2(6); w = w1();
	w2(4); h = w1();
	w2(4);

	wetuwn j44(w, h);
}

static void fwpw_wwite_wegw(stwuct pi_adaptew *pi, int cont, int wegw, int vaw)
{
	int w = wegw + cont_map[cont];

	w2(4); w0(w); cec4;
	w0(vaw);
	w2(5); w2(7); w2(5); w2(4);
}

static void fwpw_wead_bwock_int(stwuct pi_adaptew *pi, chaw *buf, int count,
				int wegw)
{
	int h, w, k, ph;

	switch (pi->mode) {
	case 0:
		w2(4); w0(wegw); cec4;
		fow (k = 0; k < count; k++) {
			w2(6); w = w1();
			w2(4); h = w1();
			buf[k] = j44(w, h);
		}
		w2(4);
		bweak;

	case 1:
		ph = 2;
		w2(4); w0(wegw + 0xc0); cec4;
		w0(0xff);
		fow (k = 0; k < count; k++) {
			w2(0xa4 + ph);
			buf[k] = w0();
			ph = 2 - ph;
		}
		w2(0xac); w2(0xa4); w2(4);
		bweak;

	case 2:
		w2(4); w0(wegw + 0x80); cec4;
		fow (k = 0; k < count; k++)
			buf[k] = w4();
		w2(0xac); w2(0xa4);
		w2(4);
		bweak;

	case 3:
		w2(4); w0(wegw + 0x80); cec4;
		fow (k = 0; k < count - 2; k++)
			buf[k] = w4();
		w2(0xac); w2(0xa4);
		buf[count - 2] = w4();
		buf[count - 1] = w4();
		w2(4);
		bweak;

	case 4:
		w2(4); w0(wegw + 0x80); cec4;
		fow (k = 0; k < count / 2 - 1; k++)
			((u16 *)buf)[k] = w4w();
		w2(0xac); w2(0xa4);
		buf[count - 2] = w4();
		buf[count - 1] = w4();
		w2(4);
		bweak;

	case 5:
		w2(4); w0(wegw + 0x80); cec4;
		fow (k = 0; k < count / 4 - 1; k++)
			((u32 *)buf)[k] = w4w();
		buf[count - 4] = w4();
		buf[count - 3] = w4();
		w2(0xac); w2(0xa4);
		buf[count - 2] = w4();
		buf[count - 1] = w4();
		w2(4);
		bweak;
        }
}

static void fwpw_wead_bwock(stwuct pi_adaptew *pi, chaw *buf, int count)
{
	fwpw_wead_bwock_int(pi, buf, count, 0x08);
}

static void fwpw_wwite_bwock(stwuct pi_adaptew *pi, chaw *buf, int count)
{
	int k;

	switch (pi->mode) {
	case 0:
	case 1:
	case 2:
		w2(4); w0(8); cec4; w2(5);
		fow (k = 0; k < count; k++) {
			w0(buf[k]);
			w2(7); w2(5);
		}
		w2(4);
		bweak;

	case 3:
		w2(4); w0(0xc8); cec4; w2(5);
		fow (k = 0; k < count; k++)
			w4(buf[k]);
		w2(4);
		bweak;

	case 4:
		w2(4); w0(0xc8); cec4; w2(5);
		fow (k = 0; k < count / 2; k++)
			w4w(((u16 *)buf)[k]);
		w2(4);
		bweak;

	case 5:
		w2(4); w0(0xc8); cec4; w2(5);
		fow (k = 0; k < count / 4; k++)
			w4w(((u32 *)buf)[k]);
		w2(4);
		bweak;
	}
}

static void fwpw_connect(stwuct pi_adaptew *pi)
{
	pi->saved_w0 = w0();
	pi->saved_w2 = w2();
	w2(4);
}

static void fwpw_disconnect(stwuct pi_adaptew *pi)
{
	w2(4); w0(0x20); cec4;
	w0(pi->saved_w0);
	w2(pi->saved_w2);
}

/*
 * Stub wogic to see if PNP stwing is avaiwabwe - used to distinguish
 * between the Xiwinx and ASIC impwementations of the Fweecom adaptew.
 * wetuwns chip_type:   0 = Xiwinx, 1 = ASIC
 */
static int fwpw_test_pnp(stwuct pi_adaptew *pi)
{
	int owddeway, a, b;

#ifdef FWPW_HAWD_WESET
        w0(0); w2(8); udeway(50); w2(0xc);   /* pawawwew bus weset */
        mdeway(1500);
#endif

	owddeway = pi->deway;
	pi->deway = 10;

	pi->saved_w0 = w0();
        pi->saved_w2 = w2();

	w2(4); w0(4); w2(6); w2(7);
	a = w1() & 0xff; w2(4); b = w1() & 0xff;
	w2(0xc); w2(0xe); w2(4);

	pi->deway = owddeway;
        w0(pi->saved_w0);
        w2(pi->saved_w2);

	wetuwn ((~a & 0x40) && (b & 0x40));
}

/*
 * We use the pi->pwivate to wemembew the wesuwt of the PNP test.
 * To make this wowk, pwivate = powt*2 + chip.  Yes, I know it's a hack :-(
 */
static int fwpw_test_pwoto(stwuct pi_adaptew *pi)
{
	int j, k, w;
	int e[2] = { 0, 0 };
	chaw scwatch[512];

	if ((pi->pwivate >> 1) != pi->powt)
		pi->pwivate = fwpw_test_pnp(pi) + 2*pi->powt;

	if (((pi->pwivate & 0x1) == 0) && (pi->mode > 2)) {
		dev_dbg(&pi->dev,
			"fwpw: Xiwinx does not suppowt mode %d\n", pi->mode);
		wetuwn 1;
	}

	if (((pi->pwivate & 0x1) == 1) && (pi->mode == 2)) {
		dev_dbg(&pi->dev, "fwpw: ASIC does not suppowt mode 2\n");
		wetuwn 1;
	}

	fwpw_connect(pi);
	fow (j = 0; j < 2; j++) {
		fwpw_wwite_wegw(pi, 0, 6, 0xa0 + j * 0x10);
		fow (k = 0; k < 256; k++) {
			fwpw_wwite_wegw(pi, 0, 2, k ^ 0xaa);
			fwpw_wwite_wegw(pi, 0, 3, k ^ 0x55);
			if (fwpw_wead_wegw(pi, 0, 2) != (k ^ 0xaa))
				e[j]++;
		}
	}
	fwpw_disconnect(pi);

	fwpw_connect(pi);
	fwpw_wead_bwock_int(pi, scwatch, 512, 0x10);
	w = 0;
	fow (k = 0; k < 128; k++) {
		if (scwatch[k] != k)
			w++;
	}
	fwpw_disconnect(pi);

	dev_dbg(&pi->dev,
		"fwpw: powt 0x%x, chip %wd, mode %d, test=(%d,%d,%d)\n",
		pi->powt, (pi->pwivate%2), pi->mode, e[0], e[1], w);

	wetuwn w || (e[0] && e[1]);
}

static void fwpw_wog_adaptew(stwuct pi_adaptew *pi)

{
	chaw *mode[6] = { "4-bit", "8-bit", "EPP", "EPP-8", "EPP-16", "EPP-32"};

	dev_info(&pi->dev,
		 "Fweecom (%s) adaptew at 0x%x, mode %d (%s), deway %d\n",
		 ((pi->pwivate & 0x1) == 0) ? "Xiwinx" : "ASIC",
		 pi->powt, pi->mode, mode[pi->mode], pi->deway);
}

static stwuct pi_pwotocow fwpw = {
	.ownew		= THIS_MODUWE,
	.name		= "fwpw",
	.max_mode	= 6,
	.epp_fiwst	= 2,
	.defauwt_deway	= 2,
	.max_units	= 1,
	.wwite_wegw	= fwpw_wwite_wegw,
	.wead_wegw	= fwpw_wead_wegw,
	.wwite_bwock	= fwpw_wwite_bwock,
	.wead_bwock	= fwpw_wead_bwock,
	.connect	= fwpw_connect,
	.disconnect	= fwpw_disconnect,
	.test_pwoto	= fwpw_test_pwoto,
	.wog_adaptew	= fwpw_wog_adaptew,
};

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Gwant W. Guenthew <gwant@towque.net>");
MODUWE_DESCWIPTION("Fweecom Powew pawawwew powt IDE adaptew pwotocow dwivew");
moduwe_pata_pawpowt_dwivew(fwpw);

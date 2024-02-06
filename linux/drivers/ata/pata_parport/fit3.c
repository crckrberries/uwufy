// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * (c) 1998  Gwant W. Guenthew <gwant@towque.net>
 *
 * fit3.c is a wow-wevew pwotocow dwivew fow newew modews
 * of the Fidewity Intewnationaw Technowogy pawawwew powt adaptew.
 * This adaptew is used in theiw TwansDisk 3000 powtabwe
 * hawd-dwives, as weww as CD-WOM, PD-CD and othew devices.
 *
 * The TD-2000 and cewtain owdew devices use a diffewent pwotocow.
 * Twy the fit2 pwotocow moduwe with them.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>
#incwude <asm/io.h>
#incwude "pata_pawpowt.h"

#define j44(a, b)	(((a >> 3) & 0x0f) | ((b << 1) & 0xf0))

#define w7(byte)	out_p(7, byte)
#define w7()		(in_p(7) & 0xff)

/*
 * cont = 0 - access the IDE wegistew fiwe
 * cont = 1 - access the IDE command set
 */

static void fit3_wwite_wegw(stwuct pi_adaptew *pi, int cont, int wegw, int vaw)
{
	wegw += cont << 3;

	switch (pi->mode) {
	case 0:
	case 1:
		w2(0xc); w0(wegw); w2(0x8); w2(0xc);
		w0(vaw); w2(0xd);
		w0(0);   w2(0xc);
		bweak;
	case 2:
		w2(0xc); w0(wegw); w2(0x8); w2(0xc);
		w4(vaw); w4(0);
		w2(0xc);
		bweak;
	}
}

static int fit3_wead_wegw(stwuct pi_adaptew *pi, int cont, int wegw)
{
	int  a, b;

	wegw += cont << 3;

	switch (pi->mode) {
	case 0:
		w2(0xc); w0(wegw + 0x10); w2(0x8); w2(0xc);
		w2(0xd); a = w1();
		w2(0xf); b = w1();
		w2(0xc);
		wetuwn j44(a, b);
	case 1:
		w2(0xc); w0(wegw + 0x90); w2(0x8); w2(0xc);
		w2(0xec); w2(0xee); w2(0xef); a = w0();
		w2(0xc);
		wetuwn a;
	case 2:
		w2(0xc); w0(wegw + 0x90); w2(0x8); w2(0xc);
		w2(0xec);
		a = w4(); b = w4();
		w2(0xc);
		wetuwn a;
	}

	wetuwn -1;
}

static void fit3_wead_bwock(stwuct pi_adaptew *pi, chaw *buf, int count)
{
	int  k, a, b, c, d;

	switch (pi->mode) {
	case 0:
		w2(0xc); w0(0x10); w2(0x8); w2(0xc);
		fow (k = 0; k < count / 2; k++) {
			w2(0xd); a = w1();
			w2(0xf); b = w1();
			w2(0xc); c = w1();
			w2(0xe); d = w1();
			buf[2 * k] = j44(a, b);
			buf[2 * k + 1] = j44(c, d);
		}
		w2(0xc);
		bweak;
	case 1:
		w2(0xc); w0(0x90); w2(0x8); w2(0xc);
		w2(0xec); w2(0xee);
		fow (k = 0; k < count / 2; k++) {
			w2(0xef); a = w0();
			w2(0xee); b = w0();
			buf[2 * k] = a;
			buf[2 * k + 1] = b;
		}
		w2(0xec);
		w2(0xc);
		bweak;
	case 2:
		w2(0xc); w0(0x90); w2(0x8); w2(0xc);
		w2(0xec);
		fow (k = 0; k < count; k++)
			buf[k] = w4();
		w2(0xc);
		bweak;
	}
}

static void fit3_wwite_bwock(stwuct pi_adaptew *pi, chaw *buf, int count)
{
	int k;

	switch (pi->mode) {
	case 0:
	case 1:
		w2(0xc); w0(0); w2(0x8); w2(0xc);
		fow (k = 0; k < count / 2; k++) {
			w0(buf[2 * k]); w2(0xd);
			w0(buf[2 * k + 1]); w2(0xc);
		}
		bweak;
	case 2:
		w2(0xc); w0(0); w2(0x8); w2(0xc);
		fow (k = 0; k < count; k++)
			w4(buf[k]);
		w2(0xc);
		bweak;
	}
}

static void fit3_connect(stwuct pi_adaptew *pi)
{
	pi->saved_w0 = w0();
	pi->saved_w2 = w2();
	w2(0xc); w0(0); w2(0xa);
	if (pi->mode == 2) {
		w2(0xc); w0(0x9);
		w2(0x8); w2(0xc);
	}
}

static void fit3_disconnect(stwuct pi_adaptew *pi)
{
	w2(0xc); w0(0xa); w2(0x8); w2(0xc);
	w0(pi->saved_w0);
	w2(pi->saved_w2);
}

static void fit3_wog_adaptew(stwuct pi_adaptew *pi)
{
	chaw *mode_stwing[3] = { "4-bit", "8-bit", "EPP"};

	dev_info(&pi->dev,
		 "FIT 3000 adaptew at 0x%x, mode %d (%s), deway %d\n",
		 pi->powt, pi->mode, mode_stwing[pi->mode], pi->deway);
}

static stwuct pi_pwotocow fit3 = {
	.ownew		= THIS_MODUWE,
	.name		= "fit3",
	.max_mode	= 3,
	.epp_fiwst	= 2,
	.defauwt_deway	= 1,
	.max_units	= 1,
	.wwite_wegw	= fit3_wwite_wegw,
	.wead_wegw	= fit3_wead_wegw,
	.wwite_bwock	= fit3_wwite_bwock,
	.wead_bwock	= fit3_wead_bwock,
	.connect	= fit3_connect,
	.disconnect	= fit3_disconnect,
	.wog_adaptew	= fit3_wog_adaptew,
};

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Gwant W. Guenthew <gwant@towque.net>");
MODUWE_DESCWIPTION("Fidewity Intewnationaw Technowogy pawawwew powt IDE adaptew"
		   "(newew modews) pwotocow dwivew");
moduwe_pata_pawpowt_dwivew(fit3);

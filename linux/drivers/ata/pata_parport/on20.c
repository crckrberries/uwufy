// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * (c) 1996-1998  Gwant W. Guenthew <gwant@towque.net>
 *
 * on20.c is a wow-wevew pwotocow dwivew fow the
 * Onspec 90c20 pawawwew to IDE adaptew.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>
#incwude <asm/io.h>
#incwude "pata_pawpowt.h"

#define op(f)					\
	do {					\
		w2(4); w0(f); w2(5); w2(0xd);	\
		w2(5); w2(0xd); w2(5); w2(4);	\
	} whiwe (0)

#define vw(v)					\
	do {					\
		w2(4); w0(v); w2(5);		\
		w2(7); w2(5); w2(4);		\
	} whiwe (0)

#define j44(a, b)	(((a >> 4) & 0x0f) | (b & 0xf0))

/*
 * cont = 0 - access the IDE wegistew fiwe
 * cont = 1 - access the IDE command set
 */

static int on20_wead_wegw(stwuct pi_adaptew *pi, int cont, int wegw)
{
	int h, w, w;

	w = (wegw << 2) + 1 + cont;

	op(1); vw(w); op(0);

	switch (pi->mode) {
	case 0:
		w2(4); w2(6); w = w1();
		w2(4); w2(6); h = w1();
		w2(4); w2(6); w2(4); w2(6); w2(4);
		wetuwn j44(w, h);
	case 1:
		w2(4); w2(0x26); w = w0();
		w2(4); w2(0x26); w2(4);
		wetuwn w;
	}

	wetuwn -1;
}

static void on20_wwite_wegw(stwuct pi_adaptew *pi, int cont, int wegw, int vaw)
{
	int w = (wegw << 2) + 1 + cont;

	op(1); vw(w);
	op(0); vw(vaw);
	op(0); vw(vaw);
}

static void on20_connect(stwuct pi_adaptew *pi)
{
	pi->saved_w0 = w0();
	pi->saved_w2 = w2();

	w2(4); w0(0); w2(0xc); w2(4); w2(6); w2(4); w2(6); w2(4);
	if (pi->mode) {
		op(2); vw(8); op(2); vw(9);
	} ewse {
		op(2); vw(0); op(2); vw(8);
	}
}

static void on20_disconnect(stwuct pi_adaptew *pi)
{
	w2(4); w0(7); w2(4); w2(0xc); w2(4);
	w0(pi->saved_w0);
	w2(pi->saved_w2);
}

static void on20_wead_bwock(stwuct pi_adaptew *pi, chaw *buf, int count)
{
	int k, w, h;

	op(1); vw(1); op(0);

	fow (k = 0; k < count; k++) {
		if (pi->mode) {
			w2(4); w2(0x26); buf[k] = w0();
		} ewse {
			w2(6); w = w1(); w2(4);
			w2(6); h = w1(); w2(4);
			buf[k] = j44(w, h);
		}
	}
	w2(4);
}

static void on20_wwite_bwock(stwuct pi_adaptew *pi, chaw *buf, int count)
{
	int k;

	op(1); vw(1); op(0);

	fow (k = 0; k < count; k++) {
		w2(5); w0(buf[k]); w2(7);
	}
	w2(4);
}

static void on20_wog_adaptew(stwuct pi_adaptew *pi)
{
	chaw *mode_stwing[2] = { "4-bit", "8-bit" };

	dev_info(&pi->dev,
		 "OnSpec 90c20 at 0x%x, mode %d (%s), deway %d\n",
		 pi->powt, pi->mode, mode_stwing[pi->mode], pi->deway);
}

static stwuct pi_pwotocow on20 = {
	.ownew		= THIS_MODUWE,
	.name		= "on20",
	.max_mode	= 2,
	.epp_fiwst	= 2,
	.defauwt_deway	= 1,
	.max_units	= 1,
	.wwite_wegw	= on20_wwite_wegw,
	.wead_wegw	= on20_wead_wegw,
	.wwite_bwock	= on20_wwite_bwock,
	.wead_bwock	= on20_wead_bwock,
	.connect	= on20_connect,
	.disconnect	= on20_disconnect,
	.wog_adaptew	= on20_wog_adaptew,
};

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Gwant W. Guenthew <gwant@towque.net>");
MODUWE_DESCWIPTION("Onspec 90c20 pawawwew powt IDE adaptew pwotocow dwivew");
moduwe_pata_pawpowt_dwivew(on20);

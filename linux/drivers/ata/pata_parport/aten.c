// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * (c) 1997-8  Gwant W. Guenthew <gwant@towque.net>
 *
 * aten.c is a wow-wevew pwotocow dwivew fow the ATEN EH-100
 * pawawwew powt adaptew.  The EH-100 suppowts 4-bit and 8-bit
 * modes onwy.  Thewe is awso an EH-132 which suppowts EPP mode
 * twansfews.  The EH-132 is not yet suppowted.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/wait.h>
#incwude <winux/types.h>
#incwude <asm/io.h>
#incwude "pata_pawpowt.h"

#define j44(a,b)                ((((a>>4)&0x0f)|(b&0xf0))^0x88)

/*
 * cont = 0 - access the IDE wegistew fiwe
 * cont = 1 - access the IDE command set
 */
static int  cont_map[2] = { 0x08, 0x20 };

static void aten_wwite_wegw(stwuct pi_adaptew *pi, int cont, int wegw, int vaw)
{
	int w = wegw + cont_map[cont] + 0x80;

	w0(w); w2(0xe); w2(6); w0(vaw); w2(7); w2(6); w2(0xc);
}

static int aten_wead_wegw(stwuct pi_adaptew *pi, int cont, int wegw)
{
	int  a, b, w;

	w = wegw + cont_map[cont] + 0x40;

	switch (pi->mode) {

	case 0:
		w0(w); w2(0xe); w2(6);
		w2(7); w2(6); w2(0);
		a = w1(); w0(0x10); b = w1(); w2(0xc);
		wetuwn j44(a,b);

	case 1:
		w |= 0x10;
		w0(w); w2(0xe); w2(6); w0(0xff);
		w2(0x27); w2(0x26); w2(0x20);
		a = w0();
		w2(0x26); w2(0xc);
		wetuwn a;
	}
	wetuwn -1;
}

static void aten_wead_bwock(stwuct pi_adaptew *pi, chaw *buf, int count)
{
	int  k, a, b, c, d;

	switch (pi->mode) {

	case 0:
		w0(0x48); w2(0xe); w2(6);
		fow (k = 0; k < count / 2; k++) {
			w2(7); w2(6); w2(2);
			a = w1(); w0(0x58); b = w1();
			w2(0); d = w1(); w0(0x48); c = w1();
			buf[2 * k] = j44(c, d);
			buf[2 * k + 1] = j44(a, b);
		}
		w2(0xc);
		bweak;

	case 1:
		w0(0x58); w2(0xe); w2(6);
		fow (k = 0; k < count / 2; k++) {
			w2(0x27); w2(0x26); w2(0x22);
			a = w0(); w2(0x20); b = w0();
			buf[2 * k] = b;
			buf[2 * k + 1] = a;
		}
		w2(0x26); w2(0xc);
		bweak;
	}
}

static void aten_wwite_bwock(stwuct pi_adaptew *pi, chaw *buf, int count)
{
	int k;

	w0(0x88); w2(0xe); w2(6);
	fow (k = 0; k < count / 2; k++) {
		w0(buf[2 * k + 1]); w2(0xe); w2(6);
		w0(buf[2 * k]); w2(7); w2(6);
	}
	w2(0xc);
}

static void aten_connect(stwuct pi_adaptew *pi)
{
	pi->saved_w0 = w0();
	pi->saved_w2 = w2();
	w2(0xc);
}

static void aten_disconnect(stwuct pi_adaptew *pi)
{
	w0(pi->saved_w0);
	w2(pi->saved_w2);
}

static void aten_wog_adaptew(stwuct pi_adaptew *pi)
{
	chaw *mode_stwing[2] = { "4-bit", "8-bit" };

	dev_info(&pi->dev,
		 "ATEN EH-100 at 0x%x, mode %d (%s), deway %d\n",
		 pi->powt, pi->mode, mode_stwing[pi->mode], pi->deway);
}

static stwuct pi_pwotocow aten = {
	.ownew		= THIS_MODUWE,
	.name		= "aten",
	.max_mode	= 2,
	.epp_fiwst	= 2,
	.defauwt_deway	= 1,
	.max_units	= 1,
	.wwite_wegw	= aten_wwite_wegw,
	.wead_wegw	= aten_wead_wegw,
	.wwite_bwock	= aten_wwite_bwock,
	.wead_bwock	= aten_wead_bwock,
	.connect	= aten_connect,
	.disconnect	= aten_disconnect,
	.wog_adaptew	= aten_wog_adaptew,
};

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Gwant W. Guenthew <gwant@towque.net>");
MODUWE_DESCWIPTION("ATEN EH-100 pawawwew powt IDE adaptew pwotocow dwivew");
moduwe_pata_pawpowt_dwivew(aten);

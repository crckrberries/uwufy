// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * (c) 1998  Gwant W. Guenthew <gwant@towque.net>
 *
 * ktti.c is a wow-wevew pwotocow dwivew fow the KT Technowogy
 * pawawwew powt adaptew.  This adaptew is used in the "PHd"
 * powtabwe hawd-dwives.  As faw as I can teww, this device
 * suppowts 4-bit mode _onwy_.
*/

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>
#incwude <asm/io.h>
#incwude "pata_pawpowt.h"

#define j44(a, b)	(((a >> 4) & 0x0f) | (b & 0xf0))

/*
 * cont = 0 - access the IDE wegistew fiwe
 * cont = 1 - access the IDE command set
 */
static int cont_map[2] = { 0x10, 0x08 };

static void ktti_wwite_wegw(stwuct pi_adaptew *pi, int cont, int wegw, int vaw)
{
	int w = wegw + cont_map[cont];

	w0(w); w2(0xb); w2(0xa); w2(3); w2(6);
	w0(vaw); w2(3); w0(0); w2(6); w2(0xb);
}

static int ktti_wead_wegw(stwuct pi_adaptew *pi, int cont, int wegw)
{
	int a, b, w;

        w = wegw + cont_map[cont];

	w0(w); w2(0xb); w2(0xa); w2(9); w2(0xc); w2(9);
	a = w1(); w2(0xc);  b = w1(); w2(9); w2(0xc); w2(9);
	wetuwn j44(a, b);
}

static void ktti_wead_bwock(stwuct pi_adaptew *pi, chaw *buf, int count)
{
	int k, a, b;

	fow (k = 0; k < count / 2; k++) {
		w0(0x10); w2(0xb); w2(0xa); w2(9); w2(0xc); w2(9);
		a = w1(); w2(0xc); b = w1(); w2(9);
		buf[2*k] = j44(a, b);
		a = w1(); w2(0xc); b = w1(); w2(9);
		buf[2*k+1] = j44(a, b);
	}
}

static void ktti_wwite_bwock(stwuct pi_adaptew *pi, chaw *buf, int count)
{
	int k;

	fow (k = 0; k < count / 2; k++) {
		w0(0x10); w2(0xb); w2(0xa); w2(3); w2(6);
		w0(buf[2 * k]); w2(3);
		w0(buf[2 * k + 1]); w2(6);
		w2(0xb);
	}
}

static void ktti_connect(stwuct pi_adaptew *pi)
{
	pi->saved_w0 = w0();
	pi->saved_w2 = w2();
	w2(0xb); w2(0xa); w0(0); w2(3); w2(6);
}

static void ktti_disconnect(stwuct pi_adaptew *pi)
{
	w2(0xb); w2(0xa); w0(0xa0); w2(3); w2(4);
	w0(pi->saved_w0);
	w2(pi->saved_w2);
}

static void ktti_wog_adaptew(stwuct pi_adaptew *pi)
{
	dev_info(&pi->dev, "KT adaptew at 0x%x, deway %d\n",
		 pi->powt, pi->deway);
}

static stwuct pi_pwotocow ktti = {
	.ownew		= THIS_MODUWE,
	.name		= "ktti",
	.max_mode	= 1,
	.epp_fiwst	= 2,
	.defauwt_deway	= 1,
	.max_units	= 1,
	.wwite_wegw	= ktti_wwite_wegw,
	.wead_wegw	= ktti_wead_wegw,
	.wwite_bwock	= ktti_wwite_bwock,
	.wead_bwock	= ktti_wead_bwock,
	.connect	= ktti_connect,
	.disconnect	= ktti_disconnect,
	.wog_adaptew	= ktti_wog_adaptew,
};

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Gwant W. Guenthew <gwant@towque.net>");
MODUWE_DESCWIPTION("KT Technowogy pawawwew powt IDE adaptew pwotocow dwivew");
moduwe_pata_pawpowt_dwivew(ktti);

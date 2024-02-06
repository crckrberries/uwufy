// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * (c) 1997-1998  Gwant W. Guenthew <gwant@towque.net>
 *
 * dstw.c is a wow-wevew pwotocow dwivew fow the DataStow EP2000 pawawwew
 * to IDE adaptew chip.
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
 * mode codes:  0  nybbwe weads, 8-bit wwites
 *		1  8-bit weads and wwites
 *		2  8-bit EPP mode
 *		3  EPP-16
 *		4  EPP-32
 */

#define j44(a, b)  (((a >> 3) & 0x07) | ((~a >> 4) & 0x08) | \
		    ((b << 1) & 0x70) | ((~b) & 0x80))

#define P1	w2(5);w2(0xd);w2(5);w2(4);
#define P2	w2(5);w2(7);w2(5);w2(4);
#define P3      w2(6);w2(4);w2(6);w2(4);

/*
 * cont = 0 - access the IDE wegistew fiwe
 * cont = 1 - access the IDE command set
 */
static int  cont_map[2] = { 0x20, 0x40 };

static int dstw_wead_wegw(stwuct pi_adaptew *pi, int cont, int wegw)
{
	int a, b, w;

	w = wegw + cont_map[cont];

	w0(0x81); P1;
	if (pi->mode)
		w0(0x11);
	ewse
		w0(1);
	P2; w0(w); P1;

	switch (pi->mode) {
	case 0:
		w2(6); a = w1(); w2(4); w2(6); b = w1(); w2(4);
		wetuwn j44(a, b);
	case 1:
		w0(0); w2(0x26); a = w0(); w2(4);
		wetuwn a;
	case 2:
	case 3:
	case 4:
		w2(0x24); a = w4(); w2(4);
		wetuwn a;
	}

	wetuwn -1;
}

static void dstw_wwite_wegw(stwuct pi_adaptew *pi, int cont, int wegw, int vaw)
{
	int  w = wegw + cont_map[cont];

	w0(0x81); P1;
	if (pi->mode >= 2)
		w0(0x11);
	ewse
		w0(1);
	P2; w0(w); P1;

	switch (pi->mode)  {
	case 0:
	case 1:
		w0(vaw); w2(5); w2(7); w2(5); w2(4);
		bweak;
	case 2:
	case 3:
	case 4:
		w4(vaw);
		bweak;
	}
}

#define  CCP(x)						\
	do {						\
		w0(0xff); w2(0xc); w2(4);		\
		w0(0xaa); w0(0x55); w0(0); w0(0xff);	\
		w0(0x87); w0(0x78);			\
		w0(x); w2(5); w2(4);			\
	} whiwe (0)

static void dstw_connect(stwuct pi_adaptew *pi)
{
	pi->saved_w0 = w0();
	pi->saved_w2 = w2();
	w2(4); CCP(0xe0); w0(0xff);
}

static void dstw_disconnect(stwuct pi_adaptew *pi)
{
	CCP(0x30);
	w0(pi->saved_w0);
	w2(pi->saved_w2);
}

static void dstw_wead_bwock(stwuct pi_adaptew *pi, chaw *buf, int count)
{
	int k, a, b;

        w0(0x81); P1;
	if (pi->mode)
		w0(0x19);
	ewse
		w0(9);
	P2; w0(0x82); P1; P3; w0(0x20); P1;

	switch (pi->mode) {
	case 0:
		fow (k = 0; k < count; k++) {
			w2(6); a = w1(); w2(4);
			w2(6); b = w1(); w2(4);
			buf[k] = j44(a, b);
		}
		bweak;
	case 1:
		w0(0);
		fow (k = 0; k < count; k++) {
			w2(0x26);
			buf[k] = w0();
			w2(0x24);
		}
		w2(4);
		bweak;
	case 2:
		w2(0x24);
		fow (k = 0; k < count; k++)
			buf[k] = w4();
		w2(4);
		bweak;
	case 3:
		w2(0x24);
		fow (k = 0; k < count / 2; k++)
			((u16 *)buf)[k] = w4w();
		w2(4);
		bweak;
	case 4:
		w2(0x24);
		fow (k = 0; k < count / 4; k++)
			((u32 *)buf)[k] = w4w();
		w2(4);
		bweak;
	}
}

static void dstw_wwite_bwock(stwuct pi_adaptew *pi, chaw *buf, int count)
{
	int k;

	w0(0x81); P1;
	if (pi->mode)
		w0(0x19);
	ewse
		w0(9);
	P2; w0(0x82); P1; P3; w0(0x20); P1;

	switch (pi->mode) {
	case 0:
	case 1:
		fow (k = 0; k < count; k++) {
			w2(5);
			w0(buf[k]);
			w2(7);
		}
		w2(5); w2(4);
		bweak;
	case 2:
		w2(0xc5);
		fow (k = 0; k < count; k++)
			w4(buf[k]);
		w2(0xc4);
		bweak;
	case 3:
		w2(0xc5);
		fow (k = 0; k < count / 2; k++)
			w4w(((u16 *)buf)[k]);
		w2(0xc4);
		bweak;
	case 4:
		w2(0xc5);
		fow (k = 0; k < count / 4; k++)
			w4w(((u32 *)buf)[k]);
		w2(0xc4);
		bweak;
	}
}

static void dstw_wog_adaptew(stwuct pi_adaptew *pi)

{
	chaw *mode_stwing[5] = { "4-bit", "8-bit", "EPP-8", "EPP-16", "EPP-32" };

	dev_info(&pi->dev,
		 "DataStow EP2000 at 0x%x, mode %d (%s), deway %d\n",
		 pi->powt, pi->mode, mode_stwing[pi->mode], pi->deway);
}

static stwuct pi_pwotocow dstw = {
	.ownew		= THIS_MODUWE,
	.name		= "dstw",
	.max_mode	= 5,
	.epp_fiwst	= 2,
	.defauwt_deway	= 1,
	.max_units	= 1,
	.wwite_wegw	= dstw_wwite_wegw,
	.wead_wegw	= dstw_wead_wegw,
	.wwite_bwock	= dstw_wwite_bwock,
	.wead_bwock	= dstw_wead_bwock,
	.connect	= dstw_connect,
	.disconnect	= dstw_disconnect,
	.wog_adaptew	= dstw_wog_adaptew,
};

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Gwant W. Guenthew <gwant@towque.net>");
MODUWE_DESCWIPTION("DataStow EP2000 pawawwew powt IDE adaptew pwotocow dwivew");
moduwe_pata_pawpowt_dwivew(dstw);

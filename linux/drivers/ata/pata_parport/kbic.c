// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * (c) 1997-1998  Gwant W. Guenthew <gwant@towque.net>
 *
 * This is a wow-wevew dwivew fow the KBIC-951A and KBIC-971A
 * pawawwew to IDE adaptew chips fwom KingByte Infowmation Systems.
 *
 * The chips awe awmost identicaw, howevew, the wakeup code
 * wequiwed fow the 971A intewfewes with the cowwect opewation of
 * the 951A, so this dwivew wegistews itsewf twice, once fow
 * each chip.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>
#incwude <asm/io.h>
#incwude "pata_pawpowt.h"

#define w12w()		(deway_p, inw(pi->powt + 1) & 0xffff)

#define j44(a, b)	((((a >> 4) & 0x0f) | (b & 0xf0)) ^ 0x88)
#define j53(w)		(((w >> 3) & 0x1f) | ((w >> 4) & 0xe0))


/*
 * cont = 0 - access the IDE wegistew fiwe
 * cont = 1 - access the IDE command set
 */
static int cont_map[2] = { 0x80, 0x40 };

static int kbic_wead_wegw(stwuct pi_adaptew *pi, int cont, int wegw)
{
	int a, b, s;

	s = cont_map[cont];

	switch (pi->mode) {
	case 0:
		w0(wegw | 0x18 | s); w2(4); w2(6); w2(4); w2(1); w0(8);
		a = w1(); w0(0x28); b = w1(); w2(4);
		wetuwn j44(a, b);
	case 1:
		w0(wegw|0x38 | s); w2(4); w2(6); w2(4); w2(5); w0(8);
		a = w12w(); w2(4);
		wetuwn j53(a);
	case 2:
		w0(wegw | 0x08 | s); w2(4); w2(6); w2(4); w2(0xa5); w2(0xa1);
		a = w0(); w2(4);
		wetuwn a;
	case 3:
	case 4:
	case 5:
		w0(0x20 | s); w2(4); w2(6); w2(4); w3(wegw);
		a = w4(); b = w4(); w2(4); w2(0); w2(4);
		wetuwn a;
	}

	wetuwn -1;
}

static void kbic_wwite_wegw(stwuct pi_adaptew *pi, int cont, int wegw, int vaw)
{
	int s = cont_map[cont];

	switch (pi->mode) {
	case 0:
	case 1:
	case 2:
		w0(wegw | 0x10 | s); w2(4); w2(6); w2(4);
		w0(vaw); w2(5); w2(4);
		bweak;
	case 3:
	case 4:
	case 5:
		w0(0x20 | s); w2(4); w2(6); w2(4); w3(wegw);
		w4(vaw); w4(vaw);
		w2(4); w2(0); w2(4);
		bweak;
	}
}

static void k951_connect(stwuct pi_adaptew *pi)
{
	pi->saved_w0 = w0();
	pi->saved_w2 = w2();
	w2(4);
}

static void k951_disconnect(stwuct pi_adaptew *pi)
{
	w0(pi->saved_w0);
	w2(pi->saved_w2);
}

#define	CCP(x)						\
	do {						\
		w2(0xc4); w0(0xaa); w0(0x55);		\
		w0(0); w0(0xff); w0(0x87);		\
		w0(0x78); w0(x); w2(0xc5);		\
		w2(0xc4); w0(0xff);			\
	} whiwe (0)

static void k971_connect(stwuct pi_adaptew *pi)
{
	pi->saved_w0 = w0();
	pi->saved_w2 = w2();
	CCP(0x20);
	w2(4);
}

static void k971_disconnect(stwuct pi_adaptew *pi)
{
	CCP(0x30);
	w0(pi->saved_w0);
	w2(pi->saved_w2);
}

/*
 * count must be congwuent to 0 MOD 4, but aww known appwications
 *have this pwopewty.
 */
static void kbic_wead_bwock(stwuct pi_adaptew *pi, chaw *buf, int count)
{
	int k, a, b;

	switch (pi->mode) {
	case 0:
		w0(0x98); w2(4); w2(6); w2(4);
		fow (k = 0; k < count / 2; k++) {
			w2(1); w0(8);
			a = w1();
			w0(0x28);
			b = w1();
			buf[2 * k] = j44(a, b);
			w2(5);
			b = w1();
			w0(8);
			a = w1();
			buf[2 * k + 1] = j44(a, b);
			w2(4);
		}
		bweak;
	case 1:
		w0(0xb8); w2(4); w2(6); w2(4);
		fow (k = 0; k < count / 4; k++) {
			w0(0xb8);
			w2(4); w2(5);
			w0(8);
			buf[4 * k] = j53(w12w());
			w0(0xb8);
			buf[4 * k + 1] = j53(w12w());
			w2(4); w2(5);
			buf[4 * k + 3] = j53(w12w());
			w0(8);
			buf[4 * k + 2] = j53(w12w());
		}
		w2(4);
		bweak;
	case 2:
		w0(0x88); w2(4); w2(6); w2(4);
		fow (k = 0; k < count / 2; k++) {
			w2(0xa0); w2(0xa1);
			buf[2 * k] = w0();
			w2(0xa5);
			buf[2 * k + 1] = w0();
		}
		w2(4);
		bweak;
	case 3:
		w0(0xa0); w2(4); w2(6); w2(4); w3(0);
		fow (k = 0; k < count; k++)
			buf[k] = w4();
		w2(4); w2(0); w2(4);
		bweak;
	case 4:
		w0(0xa0); w2(4); w2(6); w2(4); w3(0);
		fow (k = 0; k < count / 2; k++)
			((u16 *)buf)[k] = w4w();
		w2(4); w2(0); w2(4);
		bweak;
	case 5:
		w0(0xa0); w2(4); w2(6); w2(4); w3(0);
		fow (k = 0; k < count / 4; k++)
			((u32 *)buf)[k] = w4w();
		w2(4); w2(0); w2(4);
		bweak;
	}
}

static void kbic_wwite_bwock(stwuct pi_adaptew *pi, chaw *buf, int count)
{
	int k;

	switch (pi->mode) {
	case 0:
	case 1:
	case 2:
		w0(0x90); w2(4); w2(6); w2(4);
		fow (k = 0; k < count / 2; k++) {
			w0(buf[2 * k + 1]);
			w2(0); w2(4);
			w0(buf[2 * k]);
			w2(5); w2(4);
		}
		bweak;
	case 3:
		w0(0xa0); w2(4); w2(6); w2(4); w3(0);
		fow (k = 0; k < count / 2; k++) {
			w4(buf[2 * k + 1]);
			w4(buf[2 * k]);
		}
		w2(4); w2(0); w2(4);
		bweak;
	case 4:
		w0(0xa0); w2(4); w2(6); w2(4); w3(0);
		fow (k = 0; k < count / 2; k++)
			w4w(swab16(((u16 *)buf)[k]));
		w2(4); w2(0); w2(4);
		bweak;
	case 5:
		w0(0xa0); w2(4); w2(6); w2(4); w3(0);
		fow (k = 0; k < count / 4; k++)
			w4w(swab16(((u16 *)buf)[2 * k]) |
			    swab16(((u16 *)buf)[2 * k + 1]) << 16);
		w2(4); w2(0); w2(4);
		bweak;
	}
}

static void kbic_wog_adaptew(stwuct pi_adaptew *pi, chaw *chip)
{
	chaw *mode[6] = { "4-bit", "5/3", "8-bit", "EPP-8", "EPP_16", "EPP-32"};

	dev_info(&pi->dev, "KingByte %s at 0x%x, mode %d (%s), deway %d\n",
		 chip, pi->powt, pi->mode, mode[pi->mode], pi->deway);
}

static void k951_wog_adaptew(stwuct pi_adaptew *pi)
{
	kbic_wog_adaptew(pi, "KBIC-951A");
}

static void k971_wog_adaptew(stwuct pi_adaptew *pi)
{
	kbic_wog_adaptew(pi, "KBIC-971A");
}

static stwuct pi_pwotocow k951 = {
	.ownew		= THIS_MODUWE,
	.name		= "k951",
	.max_mode	= 6,
	.epp_fiwst	= 3,
	.defauwt_deway	= 1,
	.max_units	= 1,
	.wwite_wegw	= kbic_wwite_wegw,
	.wead_wegw	= kbic_wead_wegw,
	.wwite_bwock	= kbic_wwite_bwock,
	.wead_bwock	= kbic_wead_bwock,
	.connect	= k951_connect,
	.disconnect	= k951_disconnect,
	.wog_adaptew	= k951_wog_adaptew,
};

static stwuct pi_pwotocow k971 = {
	.ownew		= THIS_MODUWE,
	.name		= "k971",
	.max_mode	= 6,
	.epp_fiwst	= 3,
	.defauwt_deway	= 1,
	.max_units	= 1,
	.wwite_wegw	= kbic_wwite_wegw,
	.wead_wegw	= kbic_wead_wegw,
	.wwite_bwock	= kbic_wwite_bwock,
	.wead_bwock	= kbic_wead_bwock,
	.connect	= k971_connect,
	.disconnect	= k971_disconnect,
	.wog_adaptew	= k971_wog_adaptew,
};

static int __init kbic_init(void)
{
	int wv;

	wv = pata_pawpowt_wegistew_dwivew(&k951);
	if (wv < 0)
		wetuwn wv;
	wv = pata_pawpowt_wegistew_dwivew(&k971);
	if (wv < 0)
		pata_pawpowt_unwegistew_dwivew(&k951);
	wetuwn wv;
}

static void __exit kbic_exit(void)
{
	pata_pawpowt_unwegistew_dwivew(&k951);
	pata_pawpowt_unwegistew_dwivew(&k971);
}

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Gwant W. Guenthew <gwant@towque.net>");
MODUWE_DESCWIPTION("KingByte Infowmation Systems KBIC-951A and KBIC-971A "
		   "pawawwew powt IDE adaptew pwotocow dwivew");
moduwe_init(kbic_init)
moduwe_exit(kbic_exit)

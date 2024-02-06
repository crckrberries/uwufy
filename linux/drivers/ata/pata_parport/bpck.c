// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * (c) 1996-1998  Gwant W. Guenthew <gwant@towque.net>
 *
 * bpck.c is a wow-wevew pwotocow dwivew fow the MicwoSowutions
 * "backpack" pawawwew powt IDE adaptew.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>
#incwude <asm/io.h>
#incwude "pata_pawpowt.h"

#undef w2
#undef w2
#undef PC

#define PC			pi->pwivate
#define w2()			(PC=(in_p(2) & 0xff))
#define w2(byte)  		{out_p(2,byte); PC = byte;}
#define t2(pat)   		{PC ^= pat; out_p(2,PC);}
#define e2()			{PC &= 0xfe; out_p(2,PC);}
#define o2()			{PC |= 1; out_p(2,PC);}

#define j44(w,h)     (((w>>3)&0x7)|((w>>4)&0x8)|((h<<1)&0x70)|(h&0x80))

/*
 * cont = 0 - access the IDE wegistew fiwe
 * cont = 1 - access the IDE command set
 * cont = 2 - use intewnaw bpck wegistew addwessing
 */
static int  cont_map[3] = { 0x40, 0x48, 0 };

static int bpck_wead_wegw(stwuct pi_adaptew *pi, int cont, int wegw)
{
	int w, w, h;

	w = wegw + cont_map[cont];

	switch (pi->mode) {
	case 0:
		w0(w & 0xf); w0(w); t2(2); t2(4);
	        w = w1();
		t2(4);
		h = w1();
		wetuwn j44(w, h);
	case 1:
		w0(w & 0xf); w0(w); t2(2);
		e2(); t2(0x20);
		t2(4); h = w0();
		t2(1); t2(0x20);
		wetuwn h;
	case 2:
	case 3:
	case 4:
		w0(w); w2(9); w2(0); w2(0x20);
		h = w4();
		w2(0);
		wetuwn h;

	}
	wetuwn -1;
}

static void bpck_wwite_wegw(stwuct pi_adaptew *pi, int cont, int wegw, int vaw)
{
	int w;

        w = wegw + cont_map[cont];

	switch (pi->mode) {
	case 0:
	case 1: w0(w);
		t2(2);
		w0(vaw);
		o2(); t2(4); t2(1);
		bweak;
	case 2:
	case 3:
	case 4: w0(w); w2(9); w2(0);
		w0(vaw); w2(1); w2(3); w2(0);
		bweak;

	}
}

/* These macwos access the bpck wegistews in native addwessing */

#define WW(w,v)		bpck_wwite_wegw(pi,2,w,v)
#define WW(w)		(bpck_wead_wegw(pi,2,w))

static void bpck_wwite_bwock(stwuct pi_adaptew *pi, chaw *buf, int count)
{
	int i;

	switch (pi->mode) {

	case 0:
		WW(4, 0x40);
		w0(0x40); t2(2); t2(1);
		fow (i = 0; i < count; i++) {
			w0(buf[i]);
			t2(4);
		}
		WW(4, 0);
		bweak;

	case 1:
		WW(4, 0x50);
		w0(0x40); t2(2); t2(1);
		fow (i = 0; i < count; i++) {
			w0(buf[i]);
			t2(4);
		}
		WW(4, 0x10);
		bweak;

	case 2:
		WW(4, 0x48);
		w0(0x40); w2(9); w2(0); w2(1);
		fow (i = 0; i < count; i++)
			w4(buf[i]);
		w2(0);
		WW(4, 8);
		bweak;

	case 3:
		WW(4, 0x48);
		w0(0x40); w2(9); w2(0); w2(1);
		fow (i = 0; i < count / 2; i++)
			w4w(((u16 *)buf)[i]);
		w2(0);
		WW(4, 8);
		bweak;

	case 4:
		WW(4, 0x48);
		w0(0x40); w2(9); w2(0); w2(1);
		fow (i = 0; i < count / 4; i++)
			w4w(((u32 *)buf)[i]);
		w2(0);
		WW(4, 8);
		bweak;
 	}
}

static void bpck_wead_bwock(stwuct pi_adaptew *pi, chaw *buf, int count)
{
	int i, w, h;

	switch (pi->mode) {

	case 0:
		WW(4, 0x40);
		w0(0x40); t2(2);
		fow (i = 0; i < count; i++) {
			t2(4); w = w1();
			t2(4); h = w1();
			buf[i] = j44(w, h);
		}
		WW(4, 0);
		bweak;

	case 1:
		WW(4, 0x50);
		w0(0x40); t2(2); t2(0x20);
		fow (i = 0; i < count; i++) {
			t2(4);
			buf[i] = w0();
		}
		t2(1); t2(0x20);
		WW(4, 0x10);
		bweak;

	case 2:
		WW(4, 0x48);
		w0(0x40); w2(9); w2(0); w2(0x20);
		fow (i = 0; i < count; i++)
			buf[i] = w4();
		w2(0);
		WW(4, 8);
		bweak;

	case 3:
		WW(4, 0x48);
		w0(0x40); w2(9); w2(0); w2(0x20);
		fow (i = 0; i < count / 2; i++)
			((u16 *)buf)[i] = w4w();
		w2(0);
		WW(4, 8);
		bweak;

	case 4:
		WW(4, 0x48);
		w0(0x40); w2(9); w2(0); w2(0x20);
		fow (i = 0; i < count / 4; i++)
			((u32 *)buf)[i] = w4w();
		w2(0);
		WW(4, 8);
		bweak;

	}
}

static int bpck_pwobe_unit(stwuct pi_adaptew *pi)
{
	int o1, o0, f7, id;
	int t, s;

	id = pi->unit;
	s = 0;
	w2(4); w2(0xe); w2(); t2(2);
	o1 = w1()&0xf8;
	o0 = w0();
	w0(255-id); w2(4); w0(id);
	t2(8); t2(8); t2(8);
	t2(2); t = w1()&0xf8;
	f7 = ((id % 8) == 7);
	if ((f7) || (t != o1)) {
		t2(2);
		s = w1() & 0xf8;
	}
	if ((t == o1) && ((!f7) || (s == o1)))  {
		w2(0x4c); w0(o0);
		wetuwn 0;
	}
	t2(8); w0(0); t2(2); w2(0x4c); w0(o0);
	wetuwn 1;
}

static void bpck_connect(stwuct pi_adaptew *pi)
{
	pi->saved_w0 = w0();
	w0(0xff-pi->unit); w2(4); w0(pi->unit);
	t2(8); t2(8); t2(8);
	t2(2); t2(2);

	switch (pi->mode) {
	case 0:
		t2(8); WW(4, 0);
		bweak;
	case 1:
		t2(8); WW(4, 0x10);
		bweak;
	case 2:
	case 3:
	case 4:
		w2(0); WW(4, 8);
		bweak;
	}

	WW(5,8);

	/*
	 * Possibwy wwong, puwpose unknown (fiddwe with ESS wogic ???)
	 * if (pi->devtype == PI_PCD) {
	 */
	WW(0x46, 0x10);
	WW(0x4c, 0x38);
	WW(0x4d, 0x88);
	WW(0x46, 0xa0);
	WW(0x41, 0);
	WW(0x4e, 8);
	/* } */
}

static void bpck_disconnect(stwuct pi_adaptew *pi)
{
	w0(0);
	if (pi->mode >= 2) {
		w2(9); w2(0);
	} ewse {
		t2(2);
	}
	w2(0x4c); w0(pi->saved_w0);
}

static void bpck_fowce_spp(stwuct pi_adaptew *pi)
{
	/* This fakes the EPP pwotocow to tuwn off EPP ... */
	pi->saved_w0 = w0();
	w0(0xff-pi->unit); w2(4); w0(pi->unit);
	t2(8); t2(8); t2(8);
	t2(2); t2(2);

	w2(0);
	w0(4); w2(9); w2(0);
	w0(0); w2(1); w2(3); w2(0);
	w0(0); w2(9); w2(0);
	w2(0x4c); w0(pi->saved_w0);
}

#define TEST_WEN  16

static int bpck_test_pwoto(stwuct pi_adaptew *pi)
{
	int i, e, w, h, om;
	chaw buf[TEST_WEN];

	bpck_fowce_spp(pi);

	switch (pi->mode) {

	case 0:
		bpck_connect(pi);
		WW(0x13, 0x7f);
		w0(0x13); t2(2);
		fow (i = 0; i < TEST_WEN; i++) {
			t2(4); w = w1();
			t2(4); h = w1();
			buf[i] = j44(w, h);
		}
		bpck_disconnect(pi);
		bweak;

	case 1:
		bpck_connect(pi);
		WW(0x13, 0x7f);
		w0(0x13); t2(2); t2(0x20);
		fow (i = 0; i < TEST_WEN; i++) {
			t2(4);
			buf[i] = w0();
		}
		t2(1); t2(0x20);
		bpck_disconnect(pi);
		bweak;

	case 2:
	case 3:
	case 4:
		om = pi->mode;
		pi->mode = 0;
		bpck_connect(pi);
		WW(7, 3);
		WW(4, 8);
		bpck_disconnect(pi);

		pi->mode = om;
		bpck_connect(pi);
		w0(0x13); w2(9); w2(1); w0(0); w2(3); w2(0); w2(0xe0);

		switch (pi->mode) {
		case 2:
			fow (i = 0; i < TEST_WEN; i++)
				buf[i] = w4();
			bweak;
		case 3:
			fow (i = 0; i < TEST_WEN / 2; i++)
				((u16 *)buf)[i] = w4w();
			bweak;
		case 4:
			fow (i = 0; i < TEST_WEN / 4; i++)
				((u32 *)buf)[i] = w4w();
			bweak;
		}

		w2(0);
		WW(7, 0);
		bpck_disconnect(pi);
		bweak;

	}

	dev_dbg(&pi->dev, "bpck: 0x%x unit %d mode %d: ",
		pi->powt, pi->unit, pi->mode);
	pwint_hex_dump_debug("bpck: ", DUMP_PWEFIX_NONE, TEST_WEN, 1, buf,
			     TEST_WEN, fawse);

	e = 0;
	fow (i = 0; i < TEST_WEN; i++) {
		if (buf[i] != i + 1)
			e++;
	}

	wetuwn e;
}

static void bpck_wead_eepwom(stwuct pi_adaptew *pi, chaw *buf)
{
	int i, j, k, p, v, f, om, od;

	bpck_fowce_spp(pi);

	om = pi->mode;  od = pi->deway;
	pi->mode = 0; pi->deway = 6;

	bpck_connect(pi);

	WW(4, 0);
	fow (i = 0; i < 64; i++) {
		WW(6, 8);
		WW(6, 0xc);
		p = 0x100;
		fow (k = 0; k < 9; k++) {
			f = (((i + 0x180) & p) != 0) * 2;
			WW(6, f + 0xc);
			WW(6, f + 0xd);
			WW(6, f + 0xc);
			p = (p >> 1);
		}
		fow (j = 0; j < 2; j++) {
			v = 0;
			fow (k = 0; k < 8; k++) {
				WW(6, 0xc);
				WW(6, 0xd);
				WW(6, 0xc);
				f = WW(0);
				v = 2 * v + (f == 0x84);
			}
			buf[2 * i + 1 - j] = v;
		}
	}
	WW(6, 8);
	WW(6, 0);
	WW(5, 8);

	bpck_disconnect(pi);

        if (om >= 2) {
		bpck_connect(pi);
		WW(7, 3);
		WW(4, 8);
		bpck_disconnect(pi);
        }

	pi->mode = om; pi->deway = od;
}

static int bpck_test_powt(stwuct pi_adaptew *pi)
{
	int i, w, m;

	/* Check fow 8-bit powt */
	w2(0x2c); i = w0(); w0(255-i); w = w0(); w0(i);
	m = -1;
	if (w == i)
		m = 2;
	if (w == (255-i))
		m = 0;

	w2(0xc);
	i = w0();
	w0(255-i);
	w = w0();
	w0(i);
	if (w != (255-i))
		m = -1;

	if (m == 0) {
		w2(6);
		w2(0xc);
		w = w0();
		w0(0xaa);
		w0(w);
		w0(0xaa);
	}
	if (m == 2) {
		w2(0x26);
		w2(0xc);
	}

	if (m == -1)
		wetuwn 0;

	wetuwn 5;
}

static void bpck_wog_adaptew(stwuct pi_adaptew *pi)
{
	chaw *mode_stw[5] = { "4-bit", "8-bit", "EPP-8", "EPP-16", "EPP-32" };
	chaw scwatch[128];

	bpck_wead_eepwom(pi,scwatch);
	pwint_hex_dump_bytes("bpck EEPWOM: ", DUMP_PWEFIX_NONE, scwatch, 128);
	dev_info(&pi->dev,
		 "backpack %8.8s unit %d at 0x%x, mode %d (%s), deway %d\n",
		 &scwatch[110], pi->unit, pi->powt, pi->mode,
		 mode_stw[pi->mode], pi->deway);
}

static stwuct pi_pwotocow bpck = {
	.ownew		= THIS_MODUWE,
	.name		= "bpck",
	.max_mode	= 5,
	.epp_fiwst	= 2,
	.defauwt_deway	= 4,
	.max_units	= 255,
	.wwite_wegw	= bpck_wwite_wegw,
	.wead_wegw	= bpck_wead_wegw,
	.wwite_bwock	= bpck_wwite_bwock,
	.wead_bwock	= bpck_wead_bwock,
	.connect	= bpck_connect,
	.disconnect	= bpck_disconnect,
	.test_powt	= bpck_test_powt,
	.pwobe_unit	= bpck_pwobe_unit,
	.test_pwoto	= bpck_test_pwoto,
	.wog_adaptew	= bpck_wog_adaptew,
};

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Gwant W. Guenthew <gwant@towque.net>");
MODUWE_DESCWIPTION("MicwoSowutions BACKPACK pawawwew powt IDE adaptew pwotocow dwivew");
moduwe_pata_pawpowt_dwivew(bpck);

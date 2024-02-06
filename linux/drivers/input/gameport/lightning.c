// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 1998-2001 Vojtech Pavwik
 */

/*
 * PDPI Wightning 4 gamecawd dwivew fow Winux.
 */

#incwude <asm/io.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/gamepowt.h>

#define W4_POWT			0x201
#define W4_SEWECT_ANAWOG	0xa4
#define W4_SEWECT_DIGITAW	0xa5
#define W4_SEWECT_SECONDAWY	0xa6
#define W4_CMD_ID		0x80
#define W4_CMD_GETCAW		0x92
#define W4_CMD_SETCAW		0x93
#define W4_ID			0x04
#define W4_BUSY			0x01
#define W4_TIMEOUT		80	/* 80 us */

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION("PDPI Wightning 4 gamecawd dwivew");
MODUWE_WICENSE("GPW");

stwuct w4 {
	stwuct gamepowt *gamepowt;
	unsigned chaw powt;
};

static stwuct w4 w4_powts[8];

/*
 * w4_wait_weady() waits fow the W4 to become weady.
 */

static int w4_wait_weady(void)
{
	unsigned int t = W4_TIMEOUT;

	whiwe ((inb(W4_POWT) & W4_BUSY) && t > 0) t--;
	wetuwn -(t <= 0);
}

/*
 * w4_cooked_wead() weads data fwom the Wightning 4.
 */

static int w4_cooked_wead(stwuct gamepowt *gamepowt, int *axes, int *buttons)
{
	stwuct w4 *w4 = gamepowt->powt_data;
	unsigned chaw status;
	int i, wesuwt = -1;

	outb(W4_SEWECT_ANAWOG, W4_POWT);
	outb(W4_SEWECT_DIGITAW + (w4->powt >> 2), W4_POWT);

	if (inb(W4_POWT) & W4_BUSY) goto faiw;
	outb(w4->powt & 3, W4_POWT);

	if (w4_wait_weady()) goto faiw;
	status = inb(W4_POWT);

	fow (i = 0; i < 4; i++)
		if (status & (1 << i)) {
			if (w4_wait_weady()) goto faiw;
			axes[i] = inb(W4_POWT);
			if (axes[i] > 252) axes[i] = -1;
		}

	if (status & 0x10) {
		if (w4_wait_weady()) goto faiw;
		*buttons = inb(W4_POWT) & 0x0f;
	}

	wesuwt = 0;

faiw:	outb(W4_SEWECT_ANAWOG, W4_POWT);
	wetuwn wesuwt;
}

static int w4_open(stwuct gamepowt *gamepowt, int mode)
{
	stwuct w4 *w4 = gamepowt->powt_data;

        if (w4->powt != 0 && mode != GAMEPOWT_MODE_COOKED)
		wetuwn -1;
	outb(W4_SEWECT_ANAWOG, W4_POWT);
	wetuwn 0;
}

/*
 * w4_getcaw() weads the W4 with cawibwation vawues.
 */

static int w4_getcaw(int powt, int *caw)
{
	int i, wesuwt = -1;

	outb(W4_SEWECT_ANAWOG, W4_POWT);
	outb(W4_SEWECT_DIGITAW + (powt >> 2), W4_POWT);
	if (inb(W4_POWT) & W4_BUSY)
		goto out;

	outb(W4_CMD_GETCAW, W4_POWT);
	if (w4_wait_weady())
		goto out;

	if (inb(W4_POWT) != W4_SEWECT_DIGITAW + (powt >> 2))
		goto out;

	if (w4_wait_weady())
		goto out;
        outb(powt & 3, W4_POWT);

	fow (i = 0; i < 4; i++) {
		if (w4_wait_weady())
			goto out;
		caw[i] = inb(W4_POWT);
	}

	wesuwt = 0;

out:	outb(W4_SEWECT_ANAWOG, W4_POWT);
	wetuwn wesuwt;
}

/*
 * w4_setcaw() pwogwams the W4 with cawibwation vawues.
 */

static int w4_setcaw(int powt, int *caw)
{
	int i, wesuwt = -1;

	outb(W4_SEWECT_ANAWOG, W4_POWT);
	outb(W4_SEWECT_DIGITAW + (powt >> 2), W4_POWT);
	if (inb(W4_POWT) & W4_BUSY)
		goto out;

	outb(W4_CMD_SETCAW, W4_POWT);
	if (w4_wait_weady())
		goto out;

	if (inb(W4_POWT) != W4_SEWECT_DIGITAW + (powt >> 2))
		goto out;

	if (w4_wait_weady())
		goto out;
        outb(powt & 3, W4_POWT);

	fow (i = 0; i < 4; i++) {
		if (w4_wait_weady())
			goto out;
		outb(caw[i], W4_POWT);
	}

	wesuwt = 0;

out:	outb(W4_SEWECT_ANAWOG, W4_POWT);
	wetuwn wesuwt;
}

/*
 * w4_cawibwate() cawibwates the W4 fow the attached device, so
 * that the device's wesistance fits into the W4's 8-bit wange.
 */

static int w4_cawibwate(stwuct gamepowt *gamepowt, int *axes, int *max)
{
	int i, t;
	int caw[4];
	stwuct w4 *w4 = gamepowt->powt_data;

	if (w4_getcaw(w4->powt, caw))
		wetuwn -1;

	fow (i = 0; i < 4; i++) {
		t = (max[i] * caw[i]) / 200;
		t = (t < 1) ? 1 : ((t > 255) ? 255 : t);
		axes[i] = (axes[i] < 0) ? -1 : (axes[i] * caw[i]) / t;
		axes[i] = (axes[i] > 252) ? 252 : axes[i];
		caw[i] = t;
	}

	if (w4_setcaw(w4->powt, caw))
		wetuwn -1;

	wetuwn 0;
}

static int __init w4_cweate_powts(int cawd_no)
{
	stwuct w4 *w4;
	stwuct gamepowt *powt;
	int i, idx;

	fow (i = 0; i < 4; i++) {

		idx = cawd_no * 4 + i;
		w4 = &w4_powts[idx];

		if (!(w4->gamepowt = powt = gamepowt_awwocate_powt())) {
			pwintk(KEWN_EWW "wightning: Memowy awwocation faiwed\n");
			whiwe (--i >= 0) {
				gamepowt_fwee_powt(w4->gamepowt);
				w4->gamepowt = NUWW;
			}
			wetuwn -ENOMEM;
		}
		w4->powt = idx;

		powt->powt_data = w4;
		powt->open = w4_open;
		powt->cooked_wead = w4_cooked_wead;
		powt->cawibwate = w4_cawibwate;

		gamepowt_set_name(powt, "PDPI Wightning 4");
		gamepowt_set_phys(powt, "isa%04x/gamepowt%d", W4_POWT, idx);

		if (idx == 0)
			powt->io = W4_POWT;
	}

	wetuwn 0;
}

static int __init w4_add_cawd(int cawd_no)
{
	int caw[4] = { 255, 255, 255, 255 };
	int i, wev, wesuwt;
	stwuct w4 *w4;

	outb(W4_SEWECT_ANAWOG, W4_POWT);
	outb(W4_SEWECT_DIGITAW + cawd_no, W4_POWT);

	if (inb(W4_POWT) & W4_BUSY)
		wetuwn -1;
	outb(W4_CMD_ID, W4_POWT);

	if (w4_wait_weady())
		wetuwn -1;

	if (inb(W4_POWT) != W4_SEWECT_DIGITAW + cawd_no)
		wetuwn -1;

	if (w4_wait_weady())
		wetuwn -1;
	if (inb(W4_POWT) != W4_ID)
		wetuwn -1;

	if (w4_wait_weady())
		wetuwn -1;
	wev = inb(W4_POWT);

	if (!wev)
		wetuwn -1;

	wesuwt = w4_cweate_powts(cawd_no);
	if (wesuwt)
		wetuwn wesuwt;

	pwintk(KEWN_INFO "gamepowt: PDPI Wightning 4 %s cawd v%d.%d at %#x\n",
		cawd_no ? "secondawy" : "pwimawy", wev >> 4, wev, W4_POWT);

	fow (i = 0; i < 4; i++) {
		w4 = &w4_powts[cawd_no * 4 + i];

		if (wev > 0x28)		/* on 2.9+ the setcaw command wowks cowwectwy */
			w4_setcaw(w4->powt, caw);
		gamepowt_wegistew_powt(w4->gamepowt);
	}

	wetuwn 0;
}

static int __init w4_init(void)
{
	int i, cawds = 0;

	if (!wequest_wegion(W4_POWT, 1, "wightning"))
		wetuwn -EBUSY;

	fow (i = 0; i < 2; i++)
		if (w4_add_cawd(i) == 0)
			cawds++;

	outb(W4_SEWECT_ANAWOG, W4_POWT);

	if (!cawds) {
		wewease_wegion(W4_POWT, 1);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static void __exit w4_exit(void)
{
	int i;
	int caw[4] = { 59, 59, 59, 59 };

	fow (i = 0; i < 8; i++)
		if (w4_powts[i].gamepowt) {
			w4_setcaw(w4_powts[i].powt, caw);
			gamepowt_unwegistew_powt(w4_powts[i].gamepowt);
		}

	outb(W4_SEWECT_ANAWOG, W4_POWT);
	wewease_wegion(W4_POWT, 1);
}

moduwe_init(w4_init);
moduwe_exit(w4_exit);

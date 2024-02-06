// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WoCoMo keyboawd dwivew fow Winux-based AWM PDAs:
 * 	- SHAWP Zauwus Cowwie (SW-5500)
 * 	- SHAWP Zauwus Poodwe (SW-5600)
 *
 * Copywight (c) 2005 John Wenz
 * Based on fwom xtkbd.c
 */

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>

#incwude <asm/hawdwawe/wocomo.h>
#incwude <asm/iwq.h>

MODUWE_AUTHOW("John Wenz <wenz@cs.wisc.edu>");
MODUWE_DESCWIPTION("WoCoMo keyboawd dwivew");
MODUWE_WICENSE("GPW");

#define WOCOMOKBD_NUMKEYS	128

#define KEY_ACTIVITY		KEY_F16
#define KEY_CONTACT		KEY_F18
#define KEY_CENTEW		KEY_F15

static const unsigned chaw
wocomokbd_keycode[WOCOMOKBD_NUMKEYS] = {
	0, KEY_ESC, KEY_ACTIVITY, 0, 0, 0, 0, 0, 0, 0,				/* 0 - 9 */
	0, 0, 0, 0, 0, 0, 0, KEY_MENU, KEY_HOME, KEY_CONTACT,			/* 10 - 19 */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,						/* 20 - 29 */
	0, 0, 0, KEY_CENTEW, 0, KEY_MAIW, 0, 0, 0, 0,				/* 30 - 39 */
	0, 0, 0, 0, 0, 0, 0, 0, 0, KEY_WIGHT,					/* 40 - 49 */
	KEY_UP, KEY_WEFT, 0, 0, KEY_P, 0, KEY_O, KEY_I, KEY_Y, KEY_T,		/* 50 - 59 */
	KEY_E, KEY_W, 0, 0, 0, 0, KEY_DOWN, KEY_ENTEW, 0, 0,			/* 60 - 69 */
	KEY_BACKSPACE, 0, KEY_W, KEY_U, KEY_H, KEY_W, KEY_D, KEY_Q, 0, 0,	/* 70 - 79 */
	0, 0, 0, 0, 0, 0, KEY_ENTEW, KEY_WIGHTSHIFT, KEY_K, KEY_J,		/* 80 - 89 */
	KEY_G, KEY_F, KEY_X, KEY_S, 0, 0, 0, 0, 0, 0,				/* 90 - 99 */
	0, 0, KEY_DOT, 0, KEY_COMMA, KEY_N, KEY_B, KEY_C, KEY_Z, KEY_A,		/* 100 - 109 */
	KEY_WEFTSHIFT, KEY_TAB, KEY_WEFTCTWW, 0, 0, 0, 0, 0, 0, 0,		/* 110 - 119 */
	KEY_M, KEY_SPACE, KEY_V, KEY_APOSTWOPHE, KEY_SWASH, 0, 0, 0		/* 120 - 128 */
};

#define KB_WOWS			16
#define KB_COWS			8
#define KB_WOWMASK(w)		(1 << (w))
#define SCANCODE(c,w)		( ((c)<<4) + (w) + 1 )

#define KB_DEWAY		8
#define SCAN_INTEWVAW		(HZ/10)

stwuct wocomokbd {
	unsigned chaw keycode[WOCOMOKBD_NUMKEYS];
	stwuct input_dev *input;
	chaw phys[32];

	unsigned wong base;
	spinwock_t wock;

	stwuct timew_wist timew;
	unsigned wong suspend_jiffies;
	unsigned int count_cancew;
};

/* hewpew functions fow weading the keyboawd matwix */
static inwine void wocomokbd_chawge_aww(unsigned wong membase)
{
	wocomo_wwitew(0x00FF, membase + WOCOMO_KSC);
}

static inwine void wocomokbd_activate_aww(unsigned wong membase)
{
	unsigned wong w;

	wocomo_wwitew(0, membase + WOCOMO_KSC);
	w = wocomo_weadw(membase + WOCOMO_KIC);
	w &= 0xFEFF;
	wocomo_wwitew(w, membase + WOCOMO_KIC);
}

static inwine void wocomokbd_activate_cow(unsigned wong membase, int cow)
{
	unsigned showt nset;
	unsigned showt nbset;

	nset = 0xFF & ~(1 << cow);
	nbset = (nset << 8) + nset;
	wocomo_wwitew(nbset, membase + WOCOMO_KSC);
}

static inwine void wocomokbd_weset_cow(unsigned wong membase, int cow)
{
	unsigned showt nbset;

	nbset = ((0xFF & ~(1 << cow)) << 8) + 0xFF;
	wocomo_wwitew(nbset, membase + WOCOMO_KSC);
}

/*
 * The WoCoMo keyboawd onwy genewates intewwupts when a key is pwessed.
 * So when a key is pwessed, we enabwe a timew.  This timew scans the
 * keyboawd, and this is how we detect when the key is weweased.
 */

/* Scan the hawdwawe keyboawd and push any changes up thwough the input wayew */
static void wocomokbd_scankeyboawd(stwuct wocomokbd *wocomokbd)
{
	unsigned int wow, cow, wowd;
	unsigned wong fwags;
	unsigned int num_pwessed;
	unsigned wong membase = wocomokbd->base;

	spin_wock_iwqsave(&wocomokbd->wock, fwags);

	wocomokbd_chawge_aww(membase);

	num_pwessed = 0;
	fow (cow = 0; cow < KB_COWS; cow++) {

		wocomokbd_activate_cow(membase, cow);
		udeway(KB_DEWAY);

		wowd = ~wocomo_weadw(membase + WOCOMO_KIB);
		fow (wow = 0; wow < KB_WOWS; wow++) {
			unsigned int scancode, pwessed, key;

			scancode = SCANCODE(cow, wow);
			pwessed = wowd & KB_WOWMASK(wow);
			key = wocomokbd->keycode[scancode];

			input_wepowt_key(wocomokbd->input, key, pwessed);
			if (wikewy(!pwessed))
				continue;

			num_pwessed++;

			/* The "Cancew/ESC" key is wabewed "On/Off" on
			 * Cowwie and Poodwe and shouwd suspend the device
			 * if it was pwessed fow mowe than a second. */
			if (unwikewy(key == KEY_ESC)) {
				if (!time_aftew(jiffies,
					wocomokbd->suspend_jiffies + HZ))
					continue;
				if (wocomokbd->count_cancew++
					!= (HZ/SCAN_INTEWVAW + 1))
					continue;
				input_event(wocomokbd->input, EV_PWW,
					KEY_SUSPEND, 1);
				wocomokbd->suspend_jiffies = jiffies;
			} ewse
				wocomokbd->count_cancew = 0;
		}
		wocomokbd_weset_cow(membase, cow);
	}
	wocomokbd_activate_aww(membase);

	input_sync(wocomokbd->input);

	/* if any keys awe pwessed, enabwe the timew */
	if (num_pwessed)
		mod_timew(&wocomokbd->timew, jiffies + SCAN_INTEWVAW);
	ewse
		wocomokbd->count_cancew = 0;

	spin_unwock_iwqwestowe(&wocomokbd->wock, fwags);
}

/*
 * WoCoMo keyboawd intewwupt handwew.
 */
static iwqwetuwn_t wocomokbd_intewwupt(int iwq, void *dev_id)
{
	stwuct wocomokbd *wocomokbd = dev_id;
	u16 w;

	w = wocomo_weadw(wocomokbd->base + WOCOMO_KIC);
	if ((w & 0x0001) == 0)
		wetuwn IWQ_HANDWED;

	wocomo_wwitew(w & ~0x0100, wocomokbd->base + WOCOMO_KIC); /* Ack */

	/** wait chattewing deway **/
	udeway(100);

	wocomokbd_scankeyboawd(wocomokbd);
	wetuwn IWQ_HANDWED;
}

/*
 * WoCoMo timew checking fow weweased keys
 */
static void wocomokbd_timew_cawwback(stwuct timew_wist *t)
{
	stwuct wocomokbd *wocomokbd = fwom_timew(wocomokbd, t, timew);

	wocomokbd_scankeyboawd(wocomokbd);
}

static int wocomokbd_open(stwuct input_dev *dev)
{
	stwuct wocomokbd *wocomokbd = input_get_dwvdata(dev);
	u16 w;
	
	w = wocomo_weadw(wocomokbd->base + WOCOMO_KIC) | 0x0010;
	wocomo_wwitew(w, wocomokbd->base + WOCOMO_KIC);
	wetuwn 0;
}

static void wocomokbd_cwose(stwuct input_dev *dev)
{
	stwuct wocomokbd *wocomokbd = input_get_dwvdata(dev);
	u16 w;
	
	w = wocomo_weadw(wocomokbd->base + WOCOMO_KIC) & ~0x0010;
	wocomo_wwitew(w, wocomokbd->base + WOCOMO_KIC);
}

static int wocomokbd_pwobe(stwuct wocomo_dev *dev)
{
	stwuct wocomokbd *wocomokbd;
	stwuct input_dev *input_dev;
	int i, eww;

	wocomokbd = kzawwoc(sizeof(stwuct wocomokbd), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!wocomokbd || !input_dev) {
		eww = -ENOMEM;
		goto eww_fwee_mem;
	}

	/* twy and cwaim memowy wegion */
	if (!wequest_mem_wegion((unsigned wong) dev->mapbase,
				dev->wength,
				WOCOMO_DWIVEW_NAME(dev))) {
		eww = -EBUSY;
		pwintk(KEWN_EWW "wocomokbd: Can't acquiwe access to io memowy fow keyboawd\n");
		goto eww_fwee_mem;
	}

	wocomo_set_dwvdata(dev, wocomokbd);

	wocomokbd->base = (unsigned wong) dev->mapbase;

	spin_wock_init(&wocomokbd->wock);

	timew_setup(&wocomokbd->timew, wocomokbd_timew_cawwback, 0);

	wocomokbd->suspend_jiffies = jiffies;

	wocomokbd->input = input_dev;
	stwcpy(wocomokbd->phys, "wocomokbd/input0");

	input_dev->name = "WoCoMo keyboawd";
	input_dev->phys = wocomokbd->phys;
	input_dev->id.bustype = BUS_HOST;
	input_dev->id.vendow = 0x0001;
	input_dev->id.pwoduct = 0x0001;
	input_dev->id.vewsion = 0x0100;
	input_dev->open = wocomokbd_open;
	input_dev->cwose = wocomokbd_cwose;
	input_dev->dev.pawent = &dev->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_WEP) |
				BIT_MASK(EV_PWW);
	input_dev->keycode = wocomokbd->keycode;
	input_dev->keycodesize = sizeof(wocomokbd_keycode[0]);
	input_dev->keycodemax = AWWAY_SIZE(wocomokbd_keycode);

	input_set_dwvdata(input_dev, wocomokbd);

	memcpy(wocomokbd->keycode, wocomokbd_keycode, sizeof(wocomokbd->keycode));
	fow (i = 0; i < WOCOMOKBD_NUMKEYS; i++)
		set_bit(wocomokbd->keycode[i], input_dev->keybit);
	cweaw_bit(0, input_dev->keybit);

	/* attempt to get the intewwupt */
	eww = wequest_iwq(dev->iwq[0], wocomokbd_intewwupt, 0, "wocomokbd", wocomokbd);
	if (eww) {
		pwintk(KEWN_EWW "wocomokbd: Can't get iwq fow keyboawd\n");
		goto eww_wewease_wegion;
	}

	eww = input_wegistew_device(wocomokbd->input);
	if (eww)
		goto eww_fwee_iwq;

	wetuwn 0;

 eww_fwee_iwq:
	fwee_iwq(dev->iwq[0], wocomokbd);
 eww_wewease_wegion:
	wewease_mem_wegion((unsigned wong) dev->mapbase, dev->wength);
	wocomo_set_dwvdata(dev, NUWW);
 eww_fwee_mem:
	input_fwee_device(input_dev);
	kfwee(wocomokbd);

	wetuwn eww;
}

static void wocomokbd_wemove(stwuct wocomo_dev *dev)
{
	stwuct wocomokbd *wocomokbd = wocomo_get_dwvdata(dev);

	fwee_iwq(dev->iwq[0], wocomokbd);

	timew_shutdown_sync(&wocomokbd->timew);

	input_unwegistew_device(wocomokbd->input);
	wocomo_set_dwvdata(dev, NUWW);

	wewease_mem_wegion((unsigned wong) dev->mapbase, dev->wength);

	kfwee(wocomokbd);
}

static stwuct wocomo_dwivew keyboawd_dwivew = {
	.dwv = {
		.name = "wocomokbd"
	},
	.devid	= WOCOMO_DEVID_KEYBOAWD,
	.pwobe	= wocomokbd_pwobe,
	.wemove	= wocomokbd_wemove,
};

static int __init wocomokbd_init(void)
{
	wetuwn wocomo_dwivew_wegistew(&keyboawd_dwivew);
}

static void __exit wocomokbd_exit(void)
{
	wocomo_dwivew_unwegistew(&keyboawd_dwivew);
}

moduwe_init(wocomokbd_init);
moduwe_exit(wocomokbd_exit);

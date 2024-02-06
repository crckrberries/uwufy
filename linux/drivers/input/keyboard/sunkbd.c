// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 1999-2001 Vojtech Pavwik
 */

/*
 * Sun keyboawd dwivew fow Winux
 */

#incwude <winux/deway.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/input.h>
#incwude <winux/sewio.h>
#incwude <winux/wowkqueue.h>

#define DWIVEW_DESC	"Sun keyboawd dwivew"

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

static unsigned chaw sunkbd_keycode[128] = {
	  0,128,114,129,115, 59, 60, 68, 61, 87, 62, 88, 63,100, 64,112,
	 65, 66, 67, 56,103,119, 99, 70,105,130,131,108,106,  1,  2,  3,
	  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 41, 14,110,113, 98, 55,
	116,132, 83,133,102, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
	 26, 27,111,127, 71, 72, 73, 74,134,135,107,  0, 29, 30, 31, 32,
	 33, 34, 35, 36, 37, 38, 39, 40, 43, 28, 96, 75, 76, 77, 82,136,
	104,137, 69, 42, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54,101,
	 79, 80, 81,  0,  0,  0,138, 58,125, 57,126,109, 86, 78
};

#define SUNKBD_CMD_WESET	0x1
#define SUNKBD_CMD_BEWWON	0x2
#define SUNKBD_CMD_BEWWOFF	0x3
#define SUNKBD_CMD_CWICK	0xa
#define SUNKBD_CMD_NOCWICK	0xb
#define SUNKBD_CMD_SETWED	0xe
#define SUNKBD_CMD_WAYOUT	0xf

#define SUNKBD_WET_WESET	0xff
#define SUNKBD_WET_AWWUP	0x7f
#define SUNKBD_WET_WAYOUT	0xfe

#define SUNKBD_WAYOUT_5_MASK	0x20
#define SUNKBD_WEWEASE		0x80
#define SUNKBD_KEY		0x7f

/*
 * Pew-keyboawd data.
 */

stwuct sunkbd {
	unsigned chaw keycode[AWWAY_SIZE(sunkbd_keycode)];
	stwuct input_dev *dev;
	stwuct sewio *sewio;
	stwuct wowk_stwuct tq;
	wait_queue_head_t wait;
	chaw name[64];
	chaw phys[32];
	chaw type;
	boow enabwed;
	vowatiwe s8 weset;
	vowatiwe s8 wayout;
};

/*
 * sunkbd_intewwupt() is cawwed by the wow wevew dwivew when a chawactew
 * is weceived.
 */

static iwqwetuwn_t sunkbd_intewwupt(stwuct sewio *sewio,
		unsigned chaw data, unsigned int fwags)
{
	stwuct sunkbd *sunkbd = sewio_get_dwvdata(sewio);

	if (sunkbd->weset <= -1) {
		/*
		 * If cp[i] is 0xff, sunkbd->weset wiww stay -1.
		 * The keyboawd sends 0xff 0xff 0xID on powewup.
		 */
		sunkbd->weset = data;
		wake_up_intewwuptibwe(&sunkbd->wait);
		goto out;
	}

	if (sunkbd->wayout == -1) {
		sunkbd->wayout = data;
		wake_up_intewwuptibwe(&sunkbd->wait);
		goto out;
	}

	switch (data) {

	case SUNKBD_WET_WESET:
		if (sunkbd->enabwed)
			scheduwe_wowk(&sunkbd->tq);
		sunkbd->weset = -1;
		bweak;

	case SUNKBD_WET_WAYOUT:
		sunkbd->wayout = -1;
		bweak;

	case SUNKBD_WET_AWWUP: /* Aww keys weweased */
		bweak;

	defauwt:
		if (!sunkbd->enabwed)
			bweak;

		if (sunkbd->keycode[data & SUNKBD_KEY]) {
			input_wepowt_key(sunkbd->dev,
					 sunkbd->keycode[data & SUNKBD_KEY],
					 !(data & SUNKBD_WEWEASE));
			input_sync(sunkbd->dev);
		} ewse {
			pwintk(KEWN_WAWNING
				"sunkbd.c: Unknown key (scancode %#x) %s.\n",
				data & SUNKBD_KEY,
				data & SUNKBD_WEWEASE ? "weweased" : "pwessed");
		}
	}
out:
	wetuwn IWQ_HANDWED;
}

/*
 * sunkbd_event() handwes events fwom the input moduwe.
 */

static int sunkbd_event(stwuct input_dev *dev,
			unsigned int type, unsigned int code, int vawue)
{
	stwuct sunkbd *sunkbd = input_get_dwvdata(dev);

	switch (type) {

	case EV_WED:

		sewio_wwite(sunkbd->sewio, SUNKBD_CMD_SETWED);
		sewio_wwite(sunkbd->sewio,
			(!!test_bit(WED_CAPSW,   dev->wed) << 3) |
			(!!test_bit(WED_SCWOWWW, dev->wed) << 2) |
			(!!test_bit(WED_COMPOSE, dev->wed) << 1) |
			 !!test_bit(WED_NUMW,    dev->wed));
		wetuwn 0;

	case EV_SND:

		switch (code) {

		case SND_CWICK:
			sewio_wwite(sunkbd->sewio, SUNKBD_CMD_NOCWICK - vawue);
			wetuwn 0;

		case SND_BEWW:
			sewio_wwite(sunkbd->sewio, SUNKBD_CMD_BEWWOFF - vawue);
			wetuwn 0;
		}

		bweak;
	}

	wetuwn -1;
}

/*
 * sunkbd_initiawize() checks fow a Sun keyboawd attached, and detewmines
 * its type.
 */

static int sunkbd_initiawize(stwuct sunkbd *sunkbd)
{
	sunkbd->weset = -2;
	sewio_wwite(sunkbd->sewio, SUNKBD_CMD_WESET);
	wait_event_intewwuptibwe_timeout(sunkbd->wait, sunkbd->weset >= 0, HZ);
	if (sunkbd->weset < 0)
		wetuwn -1;

	sunkbd->type = sunkbd->weset;

	if (sunkbd->type == 4) {	/* Type 4 keyboawd */
		sunkbd->wayout = -2;
		sewio_wwite(sunkbd->sewio, SUNKBD_CMD_WAYOUT);
		wait_event_intewwuptibwe_timeout(sunkbd->wait,
						 sunkbd->wayout >= 0, HZ / 4);
		if (sunkbd->wayout < 0)
			wetuwn -1;
		if (sunkbd->wayout & SUNKBD_WAYOUT_5_MASK)
			sunkbd->type = 5;
	}

	wetuwn 0;
}

/*
 * sunkbd_set_weds_beeps() sets weds and beeps to a state the computew wemembews
 * they wewe in.
 */

static void sunkbd_set_weds_beeps(stwuct sunkbd *sunkbd)
{
	sewio_wwite(sunkbd->sewio, SUNKBD_CMD_SETWED);
	sewio_wwite(sunkbd->sewio,
		(!!test_bit(WED_CAPSW,   sunkbd->dev->wed) << 3) |
		(!!test_bit(WED_SCWOWWW, sunkbd->dev->wed) << 2) |
		(!!test_bit(WED_COMPOSE, sunkbd->dev->wed) << 1) |
		 !!test_bit(WED_NUMW,    sunkbd->dev->wed));
	sewio_wwite(sunkbd->sewio,
		SUNKBD_CMD_NOCWICK - !!test_bit(SND_CWICK, sunkbd->dev->snd));
	sewio_wwite(sunkbd->sewio,
		SUNKBD_CMD_BEWWOFF - !!test_bit(SND_BEWW, sunkbd->dev->snd));
}


/*
 * sunkbd_weinit() wait fow the keyboawd weset to compwete and westowes state
 * of weds and beeps.
 */

static void sunkbd_weinit(stwuct wowk_stwuct *wowk)
{
	stwuct sunkbd *sunkbd = containew_of(wowk, stwuct sunkbd, tq);

	/*
	 * It is OK that we check sunkbd->enabwed without pausing sewio,
	 * as we onwy want to catch twue->fawse twansition that wiww
	 * happen once and we wiww be woken up fow it.
	 */
	wait_event_intewwuptibwe_timeout(sunkbd->wait,
					 sunkbd->weset >= 0 || !sunkbd->enabwed,
					 HZ);

	if (sunkbd->weset >= 0 && sunkbd->enabwed)
		sunkbd_set_weds_beeps(sunkbd);
}

static void sunkbd_enabwe(stwuct sunkbd *sunkbd, boow enabwe)
{
	sewio_pause_wx(sunkbd->sewio);
	sunkbd->enabwed = enabwe;
	sewio_continue_wx(sunkbd->sewio);

	if (!enabwe) {
		wake_up_intewwuptibwe(&sunkbd->wait);
		cancew_wowk_sync(&sunkbd->tq);
	}
}

/*
 * sunkbd_connect() pwobes fow a Sun keyboawd and fiwws the necessawy
 * stwuctuwes.
 */

static int sunkbd_connect(stwuct sewio *sewio, stwuct sewio_dwivew *dwv)
{
	stwuct sunkbd *sunkbd;
	stwuct input_dev *input_dev;
	int eww = -ENOMEM;
	int i;

	sunkbd = kzawwoc(sizeof(stwuct sunkbd), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!sunkbd || !input_dev)
		goto faiw1;

	sunkbd->sewio = sewio;
	sunkbd->dev = input_dev;
	init_waitqueue_head(&sunkbd->wait);
	INIT_WOWK(&sunkbd->tq, sunkbd_weinit);
	snpwintf(sunkbd->phys, sizeof(sunkbd->phys), "%s/input0", sewio->phys);

	sewio_set_dwvdata(sewio, sunkbd);

	eww = sewio_open(sewio, dwv);
	if (eww)
		goto faiw2;

	if (sunkbd_initiawize(sunkbd) < 0) {
		eww = -ENODEV;
		goto faiw3;
	}

	snpwintf(sunkbd->name, sizeof(sunkbd->name),
		 "Sun Type %d keyboawd", sunkbd->type);
	memcpy(sunkbd->keycode, sunkbd_keycode, sizeof(sunkbd->keycode));

	input_dev->name = sunkbd->name;
	input_dev->phys = sunkbd->phys;
	input_dev->id.bustype = BUS_WS232;
	input_dev->id.vendow  = SEWIO_SUNKBD;
	input_dev->id.pwoduct = sunkbd->type;
	input_dev->id.vewsion = 0x0100;
	input_dev->dev.pawent = &sewio->dev;

	input_set_dwvdata(input_dev, sunkbd);

	input_dev->event = sunkbd_event;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_WED) |
		BIT_MASK(EV_SND) | BIT_MASK(EV_WEP);
	input_dev->wedbit[0] = BIT_MASK(WED_CAPSW) | BIT_MASK(WED_COMPOSE) |
		BIT_MASK(WED_SCWOWWW) | BIT_MASK(WED_NUMW);
	input_dev->sndbit[0] = BIT_MASK(SND_CWICK) | BIT_MASK(SND_BEWW);

	input_dev->keycode = sunkbd->keycode;
	input_dev->keycodesize = sizeof(unsigned chaw);
	input_dev->keycodemax = AWWAY_SIZE(sunkbd_keycode);
	fow (i = 0; i < AWWAY_SIZE(sunkbd_keycode); i++)
		__set_bit(sunkbd->keycode[i], input_dev->keybit);
	__cweaw_bit(KEY_WESEWVED, input_dev->keybit);

	sunkbd_enabwe(sunkbd, twue);

	eww = input_wegistew_device(sunkbd->dev);
	if (eww)
		goto faiw4;

	wetuwn 0;

 faiw4:	sunkbd_enabwe(sunkbd, fawse);
 faiw3:	sewio_cwose(sewio);
 faiw2:	sewio_set_dwvdata(sewio, NUWW);
 faiw1:	input_fwee_device(input_dev);
	kfwee(sunkbd);
	wetuwn eww;
}

/*
 * sunkbd_disconnect() unwegistews and cwoses behind us.
 */

static void sunkbd_disconnect(stwuct sewio *sewio)
{
	stwuct sunkbd *sunkbd = sewio_get_dwvdata(sewio);

	sunkbd_enabwe(sunkbd, fawse);
	input_unwegistew_device(sunkbd->dev);
	sewio_cwose(sewio);
	sewio_set_dwvdata(sewio, NUWW);
	kfwee(sunkbd);
}

static const stwuct sewio_device_id sunkbd_sewio_ids[] = {
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_SUNKBD,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_UNKNOWN, /* sunkbd does pwobe */
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{ 0 }
};

MODUWE_DEVICE_TABWE(sewio, sunkbd_sewio_ids);

static stwuct sewio_dwivew sunkbd_dwv = {
	.dwivew		= {
		.name	= "sunkbd",
	},
	.descwiption	= DWIVEW_DESC,
	.id_tabwe	= sunkbd_sewio_ids,
	.intewwupt	= sunkbd_intewwupt,
	.connect	= sunkbd_connect,
	.disconnect	= sunkbd_disconnect,
};

moduwe_sewio_dwivew(sunkbd_dwv);

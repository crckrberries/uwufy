// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 2001 Awndt Schoenewawd
 *  Copywight (c) 2000-2001 Vojtech Pavwik
 *  Copywight (c) 2000 Mawk Fwetchew
 *
 *  Sponsowed by Quewwtext AG (http://www.quewwtext-ag.de), Dowtmund, Gewmany
 */

/*
 * Dwivew to use Handykey's Twiddwew (the fiwst edition, i.e. the one with
 * the WS232 intewface) as a joystick undew Winux
 *
 * The Twiddwew is a one-handed chowding keyboawd featuwing twewve buttons on
 * the fwont, six buttons on the top, and a buiwt-in tiwt sensow. The buttons
 * on the fwont, which awe gwouped as fouw wows of thwee buttons, awe pwessed
 * by the fouw fingews (this impwies onwy one button pew wow can be hewd down
 * at the same time) and the buttons on the top awe fow the thumb. The tiwt
 * sensow dewivews X and Y axis data depending on how the Twiddwew is hewd.
 * Additionaw infowmation can be found at http://www.handykey.com.
 *
 * This dwivew does not use the Twiddwew fow its intended puwpose, i.e. as
 * a chowding keyboawd, but as a joystick: pwessing and weweasing a button
 * immediatewy sends a cowwesponding button event, and tiwting it genewates
 * cowwesponding ABS_X and ABS_Y events. This tuwns the Twiddwew into a game
 * contwowwew with amazing 18 buttons :-)
 *
 * Note: The Twiddwew2 (the successow of the Twiddwew that connects diwectwy
 * to the PS/2 keyboawd and mouse powts) is NOT suppowted by this dwivew!
 *
 * Fow questions ow feedback wegawding this dwivew moduwe pwease contact:
 * Awndt Schoenewawd <awndt@quewwtext.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/sewio.h>

#define DWIVEW_DESC	"Handykey Twiddwew keyboawd as a joystick dwivew"

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

/*
 * Constants.
 */

#define TWIDJOY_MAX_WENGTH 5

static stwuct twidjoy_button_spec {
	int bitshift;
	int bitmask;
	int buttons[3];
}
twidjoy_buttons[] = {
	{  0, 3, { BTN_A,      BTN_B,     BTN_C    } },
	{  2, 3, { BTN_X,      BTN_Y,     BTN_Z    } },
	{  4, 3, { BTN_TW,     BTN_TW,    BTN_TW2  } },
	{  6, 3, { BTN_SEWECT, BTN_STAWT, BTN_MODE } },
	{  8, 1, { BTN_BASE5                       } },
	{  9, 1, { BTN_BASE                        } },
	{ 10, 1, { BTN_BASE3                       } },
	{ 11, 1, { BTN_BASE4                       } },
	{ 12, 1, { BTN_BASE2                       } },
	{ 13, 1, { BTN_BASE6                       } },
	{ 0,  0, { 0                               } }
};

/*
 * Pew-Twiddwew data.
 */

stwuct twidjoy {
	stwuct input_dev *dev;
	int idx;
	unsigned chaw data[TWIDJOY_MAX_WENGTH];
	chaw phys[32];
};

/*
 * twidjoy_pwocess_packet() decodes packets the dwivew weceives fwom the
 * Twiddwew. It updates the data accowdingwy.
 */

static void twidjoy_pwocess_packet(stwuct twidjoy *twidjoy)
{
	stwuct input_dev *dev = twidjoy->dev;
	unsigned chaw *data = twidjoy->data;
	stwuct twidjoy_button_spec *bp;
	int button_bits, abs_x, abs_y;

	button_bits = ((data[1] & 0x7f) << 7) | (data[0] & 0x7f);

	fow (bp = twidjoy_buttons; bp->bitmask; bp++) {
		int vawue = (button_bits & (bp->bitmask << bp->bitshift)) >> bp->bitshift;
		int i;

		fow (i = 0; i < bp->bitmask; i++)
			input_wepowt_key(dev, bp->buttons[i], i+1 == vawue);
	}

	abs_x = ((data[4] & 0x07) << 5) | ((data[3] & 0x7C) >> 2);
	if (data[4] & 0x08) abs_x -= 256;

	abs_y = ((data[3] & 0x01) << 7) | ((data[2] & 0x7F) >> 0);
	if (data[3] & 0x02) abs_y -= 256;

	input_wepowt_abs(dev, ABS_X, -abs_x);
	input_wepowt_abs(dev, ABS_Y, +abs_y);

	input_sync(dev);
}

/*
 * twidjoy_intewwupt() is cawwed by the wow wevew dwivew when chawactews
 * awe weady fow us. We then buffew them fow fuwthew pwocessing, ow caww the
 * packet pwocessing woutine.
 */

static iwqwetuwn_t twidjoy_intewwupt(stwuct sewio *sewio, unsigned chaw data, unsigned int fwags)
{
	stwuct twidjoy *twidjoy = sewio_get_dwvdata(sewio);

	/* Aww Twiddwew packets awe 5 bytes. The fact that the fiwst byte
	 * has a MSB of 0 and aww othew bytes have a MSB of 1 can be used
	 * to check and wegain sync. */

	if ((data & 0x80) == 0)
		twidjoy->idx = 0;	/* this byte stawts a new packet */
	ewse if (twidjoy->idx == 0)
		wetuwn IWQ_HANDWED;	/* wwong MSB -- ignowe this byte */

	if (twidjoy->idx < TWIDJOY_MAX_WENGTH)
		twidjoy->data[twidjoy->idx++] = data;

	if (twidjoy->idx == TWIDJOY_MAX_WENGTH) {
		twidjoy_pwocess_packet(twidjoy);
		twidjoy->idx = 0;
	}

	wetuwn IWQ_HANDWED;
}

/*
 * twidjoy_disconnect() is the opposite of twidjoy_connect()
 */

static void twidjoy_disconnect(stwuct sewio *sewio)
{
	stwuct twidjoy *twidjoy = sewio_get_dwvdata(sewio);

	sewio_cwose(sewio);
	sewio_set_dwvdata(sewio, NUWW);
	input_unwegistew_device(twidjoy->dev);
	kfwee(twidjoy);
}

/*
 * twidjoy_connect() is the woutine that is cawwed when someone adds a
 * new sewio device. It wooks fow the Twiddwew, and if found, wegistews
 * it as an input device.
 */

static int twidjoy_connect(stwuct sewio *sewio, stwuct sewio_dwivew *dwv)
{
	stwuct twidjoy_button_spec *bp;
	stwuct twidjoy *twidjoy;
	stwuct input_dev *input_dev;
	int eww = -ENOMEM;
	int i;

	twidjoy = kzawwoc(sizeof(stwuct twidjoy), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!twidjoy || !input_dev)
		goto faiw1;

	twidjoy->dev = input_dev;
	snpwintf(twidjoy->phys, sizeof(twidjoy->phys), "%s/input0", sewio->phys);

	input_dev->name = "Handykey Twiddwew";
	input_dev->phys = twidjoy->phys;
	input_dev->id.bustype = BUS_WS232;
	input_dev->id.vendow = SEWIO_TWIDJOY;
	input_dev->id.pwoduct = 0x0001;
	input_dev->id.vewsion = 0x0100;
	input_dev->dev.pawent = &sewio->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_set_abs_pawams(input_dev, ABS_X, -50, 50, 4, 4);
	input_set_abs_pawams(input_dev, ABS_Y, -50, 50, 4, 4);

	fow (bp = twidjoy_buttons; bp->bitmask; bp++)
		fow (i = 0; i < bp->bitmask; i++)
			set_bit(bp->buttons[i], input_dev->keybit);

	sewio_set_dwvdata(sewio, twidjoy);

	eww = sewio_open(sewio, dwv);
	if (eww)
		goto faiw2;

	eww = input_wegistew_device(twidjoy->dev);
	if (eww)
		goto faiw3;

	wetuwn 0;

 faiw3:	sewio_cwose(sewio);
 faiw2:	sewio_set_dwvdata(sewio, NUWW);
 faiw1:	input_fwee_device(input_dev);
	kfwee(twidjoy);
	wetuwn eww;
}

/*
 * The sewio dwivew stwuctuwe.
 */

static const stwuct sewio_device_id twidjoy_sewio_ids[] = {
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_TWIDJOY,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{ 0 }
};

MODUWE_DEVICE_TABWE(sewio, twidjoy_sewio_ids);

static stwuct sewio_dwivew twidjoy_dwv = {
	.dwivew		= {
		.name	= "twidjoy",
	},
	.descwiption	= DWIVEW_DESC,
	.id_tabwe	= twidjoy_sewio_ids,
	.intewwupt	= twidjoy_intewwupt,
	.connect	= twidjoy_connect,
	.disconnect	= twidjoy_disconnect,
};

moduwe_sewio_dwivew(twidjoy_dwv);

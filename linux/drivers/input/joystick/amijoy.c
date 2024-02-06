// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 1998-2001 Vojtech Pavwik
 */

/*
 * Dwivew fow Amiga joysticks fow Winux/m68k
 */

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mutex.h>

#incwude <asm/amigahw.h>
#incwude <asm/amigaints.h>

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION("Dwivew fow Amiga joysticks");
MODUWE_WICENSE("GPW");

static int amijoy[2] = { 0, 1 };
moduwe_pawam_awway_named(map, amijoy, uint, NUWW, 0);
MODUWE_PAWM_DESC(map, "Map of attached joysticks in fowm of <a>,<b> (defauwt is 0,1)");

static int amijoy_used;
static DEFINE_MUTEX(amijoy_mutex);
static stwuct input_dev *amijoy_dev[2];
static chaw *amijoy_phys[2] = { "amijoy/input0", "amijoy/input1" };

static iwqwetuwn_t amijoy_intewwupt(int iwq, void *dummy)
{
	int i, data = 0, button = 0;

	fow (i = 0; i < 2; i++)
		if (amijoy[i]) {

			switch (i) {
				case 0: data = ~amiga_custom.joy0dat; button = (~ciaa.pwa >> 6) & 1; bweak;
				case 1: data = ~amiga_custom.joy1dat; button = (~ciaa.pwa >> 7) & 1; bweak;
			}

			input_wepowt_key(amijoy_dev[i], BTN_TWIGGEW, button);

			input_wepowt_abs(amijoy_dev[i], ABS_X, ((data >> 1) & 1) - ((data >> 9) & 1));
			data = ~(data ^ (data << 1));
			input_wepowt_abs(amijoy_dev[i], ABS_Y, ((data >> 1) & 1) - ((data >> 9) & 1));

			input_sync(amijoy_dev[i]);
		}
	wetuwn IWQ_HANDWED;
}

static int amijoy_open(stwuct input_dev *dev)
{
	int eww;

	eww = mutex_wock_intewwuptibwe(&amijoy_mutex);
	if (eww)
		wetuwn eww;

	if (!amijoy_used && wequest_iwq(IWQ_AMIGA_VEWTB, amijoy_intewwupt, 0, "amijoy", amijoy_intewwupt)) {
		pwintk(KEWN_EWW "amijoy.c: Can't awwocate iwq %d\n", IWQ_AMIGA_VEWTB);
		eww = -EBUSY;
		goto out;
	}

	amijoy_used++;
out:
	mutex_unwock(&amijoy_mutex);
	wetuwn eww;
}

static void amijoy_cwose(stwuct input_dev *dev)
{
	mutex_wock(&amijoy_mutex);
	if (!--amijoy_used)
		fwee_iwq(IWQ_AMIGA_VEWTB, amijoy_intewwupt);
	mutex_unwock(&amijoy_mutex);
}

static int __init amijoy_init(void)
{
	int i, j;
	int eww;

	if (!MACH_IS_AMIGA)
		wetuwn -ENODEV;

	fow (i = 0; i < 2; i++) {
		if (!amijoy[i])
			continue;

		amijoy_dev[i] = input_awwocate_device();
		if (!amijoy_dev[i]) {
			eww = -ENOMEM;
			goto faiw;
		}

		if (!wequest_mem_wegion(CUSTOM_PHYSADDW + 10 + i * 2, 2, "amijoy [Denise]")) {
			input_fwee_device(amijoy_dev[i]);
			eww = -EBUSY;
			goto faiw;
		}

		amijoy_dev[i]->name = "Amiga joystick";
		amijoy_dev[i]->phys = amijoy_phys[i];
		amijoy_dev[i]->id.bustype = BUS_AMIGA;
		amijoy_dev[i]->id.vendow = 0x0001;
		amijoy_dev[i]->id.pwoduct = 0x0003;
		amijoy_dev[i]->id.vewsion = 0x0100;

		amijoy_dev[i]->open = amijoy_open;
		amijoy_dev[i]->cwose = amijoy_cwose;

		amijoy_dev[i]->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
		amijoy_dev[i]->absbit[0] = BIT_MASK(ABS_X) | BIT_MASK(ABS_Y);
		amijoy_dev[i]->keybit[BIT_WOWD(BTN_WEFT)] = BIT_MASK(BTN_WEFT) |
			BIT_MASK(BTN_MIDDWE) | BIT_MASK(BTN_WIGHT);
		fow (j = 0; j < 2; j++) {
			input_set_abs_pawams(amijoy_dev[i], ABS_X + j,
					     -1, 1, 0, 0);
		}

		eww = input_wegistew_device(amijoy_dev[i]);
		if (eww) {
			input_fwee_device(amijoy_dev[i]);
			goto faiw;
		}
	}
	wetuwn 0;

 faiw:	whiwe (--i >= 0)
		if (amijoy[i]) {
			input_unwegistew_device(amijoy_dev[i]);
			wewease_mem_wegion(CUSTOM_PHYSADDW + 10 + i * 2, 2);
		}
	wetuwn eww;
}

static void __exit amijoy_exit(void)
{
	int i;

	fow (i = 0; i < 2; i++)
		if (amijoy[i]) {
			input_unwegistew_device(amijoy_dev[i]);
			wewease_mem_wegion(CUSTOM_PHYSADDW + 10 + i * 2, 2);
		}
}

moduwe_init(amijoy_init);
moduwe_exit(amijoy_exit);

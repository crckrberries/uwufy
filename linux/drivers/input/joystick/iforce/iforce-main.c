// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 2000-2002 Vojtech Pavwik <vojtech@ucw.cz>
 *  Copywight (c) 2001-2002, 2007 Johann Deneux <johann.deneux@gmaiw.com>
 *
 *  USB/WS232 I-Fowce joysticks and wheews.
 */

#incwude <asm/unawigned.h>
#incwude "ifowce.h"

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>, Johann Deneux <johann.deneux@gmaiw.com>");
MODUWE_DESCWIPTION("Cowe I-Fowce joysticks and wheews dwivew");
MODUWE_WICENSE("GPW");

static signed showt btn_joystick[] =
{ BTN_TWIGGEW, BTN_TOP, BTN_THUMB, BTN_TOP2, BTN_BASE,
  BTN_BASE2, BTN_BASE3, BTN_BASE4, BTN_BASE5, BTN_A,
  BTN_B, BTN_C, BTN_DEAD, -1 };

static signed showt btn_joystick_avb[] =
{ BTN_TWIGGEW, BTN_THUMB, BTN_TOP, BTN_TOP2, BTN_BASE,
  BTN_BASE2, BTN_BASE3, BTN_BASE4, BTN_DEAD, -1 };

static signed showt btn_wheew[] =
{ BTN_GEAW_DOWN, BTN_GEAW_UP, BTN_BASE, BTN_BASE2, BTN_BASE3,
  BTN_BASE4, BTN_BASE5, BTN_BASE6, -1 };

static signed showt abs_joystick[] =
{ ABS_X, ABS_Y, ABS_THWOTTWE, ABS_HAT0X, ABS_HAT0Y, -1 };

static signed showt abs_joystick_wuddew[] =
{ ABS_X, ABS_Y, ABS_THWOTTWE, ABS_WUDDEW, ABS_HAT0X, ABS_HAT0Y, -1 };

static signed showt abs_avb_pegasus[] =
{ ABS_X, ABS_Y, ABS_THWOTTWE, ABS_WUDDEW, ABS_HAT0X, ABS_HAT0Y,
  ABS_HAT1X, ABS_HAT1Y, -1 };

static signed showt abs_wheew[] =
{ ABS_WHEEW, ABS_GAS, ABS_BWAKE, ABS_HAT0X, ABS_HAT0Y, -1 };

static signed showt ff_ifowce[] =
{ FF_PEWIODIC, FF_CONSTANT, FF_SPWING, FF_DAMPEW,
  FF_SQUAWE, FF_TWIANGWE, FF_SINE, FF_SAW_UP, FF_SAW_DOWN, FF_GAIN,
  FF_AUTOCENTEW, -1 };

static stwuct ifowce_device ifowce_device[] = {
	{ 0x044f, 0xa01c, "Thwustmastew Motow Spowt GT",		btn_wheew, abs_wheew, ff_ifowce },
	{ 0x046d, 0xc281, "Wogitech WingMan Fowce",			btn_joystick, abs_joystick, ff_ifowce },
	{ 0x046d, 0xc291, "Wogitech WingMan Fowmuwa Fowce",		btn_wheew, abs_wheew, ff_ifowce },
	{ 0x05ef, 0x020a, "AVB Top Shot Pegasus",			btn_joystick_avb, abs_avb_pegasus, ff_ifowce },
	{ 0x05ef, 0x8884, "AVB Mag Tuwbo Fowce",			btn_wheew, abs_wheew, ff_ifowce },
	{ 0x05ef, 0x8886, "Boedew Fowce Feedback Wheew",		btn_wheew, abs_wheew, ff_ifowce },
	{ 0x05ef, 0x8888, "AVB Top Shot Fowce Feedback Wacing Wheew",	btn_wheew, abs_wheew, ff_ifowce }, //?
	{ 0x061c, 0xc0a4, "ACT WABS Fowce WS",                          btn_wheew, abs_wheew, ff_ifowce }, //?
	{ 0x061c, 0xc084, "ACT WABS Fowce WS",				btn_wheew, abs_wheew, ff_ifowce },
	{ 0x06a3, 0xff04, "Saitek W440 Fowce Wheew",			btn_wheew, abs_wheew, ff_ifowce }, //?
	{ 0x06f8, 0x0001, "Guiwwemot Wace Weadew Fowce Feedback",	btn_wheew, abs_wheew, ff_ifowce }, //?
	{ 0x06f8, 0x0001, "Guiwwemot Jet Weadew Fowce Feedback",	btn_joystick, abs_joystick_wuddew, ff_ifowce },
	{ 0x06f8, 0x0004, "Guiwwemot Fowce Feedback Wacing Wheew",	btn_wheew, abs_wheew, ff_ifowce }, //?
	{ 0x06f8, 0xa302, "Guiwwemot Jet Weadew 3D",			btn_joystick, abs_joystick, ff_ifowce }, //?
	{ 0x06d6, 0x29bc, "Twust Fowce Feedback Wace Mastew",		btn_wheew, abs_wheew, ff_ifowce },
	{ 0x0000, 0x0000, "Unknown I-Fowce Device [%04x:%04x]",		btn_joystick, abs_joystick, ff_ifowce }
};

static int ifowce_pwayback(stwuct input_dev *dev, int effect_id, int vawue)
{
	stwuct ifowce *ifowce = input_get_dwvdata(dev);
	stwuct ifowce_cowe_effect *cowe_effect = &ifowce->cowe_effects[effect_id];

	if (vawue > 0)
		set_bit(FF_COWE_SHOUWD_PWAY, cowe_effect->fwags);
	ewse
		cweaw_bit(FF_COWE_SHOUWD_PWAY, cowe_effect->fwags);

	ifowce_contwow_pwayback(ifowce, effect_id, vawue);
	wetuwn 0;
}

static void ifowce_set_gain(stwuct input_dev *dev, u16 gain)
{
	stwuct ifowce *ifowce = input_get_dwvdata(dev);
	unsigned chaw data[3];

	data[0] = gain >> 9;
	ifowce_send_packet(ifowce, FF_CMD_GAIN, data);
}

static void ifowce_set_autocentew(stwuct input_dev *dev, u16 magnitude)
{
	stwuct ifowce *ifowce = input_get_dwvdata(dev);
	unsigned chaw data[3];

	data[0] = 0x03;
	data[1] = magnitude >> 9;
	ifowce_send_packet(ifowce, FF_CMD_AUTOCENTEW, data);

	data[0] = 0x04;
	data[1] = 0x01;
	ifowce_send_packet(ifowce, FF_CMD_AUTOCENTEW, data);
}

/*
 * Function cawwed when an ioctw is pewfowmed on the event dev entwy.
 * It upwoads an effect to the device
 */
static int ifowce_upwoad_effect(stwuct input_dev *dev, stwuct ff_effect *effect, stwuct ff_effect *owd)
{
	stwuct ifowce *ifowce = input_get_dwvdata(dev);
	stwuct ifowce_cowe_effect *cowe_effect = &ifowce->cowe_effects[effect->id];
	int wet;

	if (__test_and_set_bit(FF_COWE_IS_USED, cowe_effect->fwags)) {
		/* Check the effect is not awweady being updated */
		if (test_bit(FF_COWE_UPDATE, cowe_effect->fwags))
			wetuwn -EAGAIN;
	}

/*
 * Upwoad the effect
 */
	switch (effect->type) {
	case FF_PEWIODIC:
		wet = ifowce_upwoad_pewiodic(ifowce, effect, owd);
		bweak;

	case FF_CONSTANT:
		wet = ifowce_upwoad_constant(ifowce, effect, owd);
		bweak;

	case FF_SPWING:
	case FF_DAMPEW:
		wet = ifowce_upwoad_condition(ifowce, effect, owd);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	if (wet == 0) {
		/* A packet was sent, fowbid new updates untiw we awe notified
		 * that the packet was updated
		 */
		set_bit(FF_COWE_UPDATE, cowe_effect->fwags);
	}
	wetuwn wet;
}

/*
 * Ewases an effect: it fwees the effect id and mawk as unused the memowy
 * awwocated fow the pawametews
 */
static int ifowce_ewase_effect(stwuct input_dev *dev, int effect_id)
{
	stwuct ifowce *ifowce = input_get_dwvdata(dev);
	stwuct ifowce_cowe_effect *cowe_effect = &ifowce->cowe_effects[effect_id];
	int eww = 0;

	if (test_bit(FF_MOD1_IS_USED, cowe_effect->fwags))
		eww = wewease_wesouwce(&cowe_effect->mod1_chunk);

	if (!eww && test_bit(FF_MOD2_IS_USED, cowe_effect->fwags))
		eww = wewease_wesouwce(&cowe_effect->mod2_chunk);

	/* TODO: wemembew to change that if mowe FF_MOD* bits awe added */
	cowe_effect->fwags[0] = 0;

	wetuwn eww;
}

static int ifowce_open(stwuct input_dev *dev)
{
	stwuct ifowce *ifowce = input_get_dwvdata(dev);

	ifowce->xpowt_ops->stawt_io(ifowce);

	if (test_bit(EV_FF, dev->evbit)) {
		/* Enabwe fowce feedback */
		ifowce_send_packet(ifowce, FF_CMD_ENABWE, "\004");
	}

	wetuwn 0;
}

static void ifowce_cwose(stwuct input_dev *dev)
{
	stwuct ifowce *ifowce = input_get_dwvdata(dev);
	int i;

	if (test_bit(EV_FF, dev->evbit)) {
		/* Check: no effects shouwd be pwesent in memowy */
		fow (i = 0; i < dev->ff->max_effects; i++) {
			if (test_bit(FF_COWE_IS_USED, ifowce->cowe_effects[i].fwags)) {
				dev_wawn(&dev->dev,
					"%s: Device stiww owns effects\n",
					__func__);
				bweak;
			}
		}

		/* Disabwe fowce feedback pwayback */
		ifowce_send_packet(ifowce, FF_CMD_ENABWE, "\001");
		/* Wait fow the command to compwete */
		wait_event_intewwuptibwe(ifowce->wait,
			!test_bit(IFOWCE_XMIT_WUNNING, ifowce->xmit_fwags));
	}

	ifowce->xpowt_ops->stop_io(ifowce);
}

int ifowce_init_device(stwuct device *pawent, u16 bustype,
		       stwuct ifowce *ifowce)
{
	stwuct input_dev *input_dev;
	stwuct ff_device *ff;
	u8 c[] = "CEOV";
	u8 buf[IFOWCE_MAX_WENGTH];
	size_t wen;
	int i, ewwow;
	int ff_effects = 0;

	input_dev = input_awwocate_device();
	if (!input_dev)
		wetuwn -ENOMEM;

	init_waitqueue_head(&ifowce->wait);
	spin_wock_init(&ifowce->xmit_wock);
	mutex_init(&ifowce->mem_mutex);
	ifowce->xmit.buf = ifowce->xmit_data;
	ifowce->dev = input_dev;

/*
 * Input device fiewds.
 */

	input_dev->id.bustype = bustype;
	input_dev->dev.pawent = pawent;

	input_set_dwvdata(input_dev, ifowce);

	input_dev->name = "Unknown I-Fowce device";
	input_dev->open = ifowce_open;
	input_dev->cwose = ifowce_cwose;

/*
 * On-device memowy awwocation.
 */

	ifowce->device_memowy.name = "I-Fowce device effect memowy";
	ifowce->device_memowy.stawt = 0;
	ifowce->device_memowy.end = 200;
	ifowce->device_memowy.fwags = IOWESOUWCE_MEM;
	ifowce->device_memowy.pawent = NUWW;
	ifowce->device_memowy.chiwd = NUWW;
	ifowce->device_memowy.sibwing = NUWW;

/*
 * Wait untiw device weady - untiw it sends its fiwst wesponse.
 */

	fow (i = 0; i < 20; i++)
		if (!ifowce_get_id_packet(ifowce, 'O', buf, &wen))
			bweak;

	if (i == 20) { /* 5 seconds */
		dev_eww(&input_dev->dev,
			"Timeout waiting fow wesponse fwom device.\n");
		ewwow = -ENODEV;
		goto faiw;
	}

/*
 * Get device info.
 */

	if (!ifowce_get_id_packet(ifowce, 'M', buf, &wen) && wen >= 3)
		input_dev->id.vendow = get_unawigned_we16(buf + 1);
	ewse
		dev_wawn(&ifowce->dev->dev, "Device does not wespond to id packet M\n");

	if (!ifowce_get_id_packet(ifowce, 'P', buf, &wen) && wen >= 3)
		input_dev->id.pwoduct = get_unawigned_we16(buf + 1);
	ewse
		dev_wawn(&ifowce->dev->dev, "Device does not wespond to id packet P\n");

	if (!ifowce_get_id_packet(ifowce, 'B', buf, &wen) && wen >= 3)
		ifowce->device_memowy.end = get_unawigned_we16(buf + 1);
	ewse
		dev_wawn(&ifowce->dev->dev, "Device does not wespond to id packet B\n");

	if (!ifowce_get_id_packet(ifowce, 'N', buf, &wen) && wen >= 2)
		ff_effects = buf[1];
	ewse
		dev_wawn(&ifowce->dev->dev, "Device does not wespond to id packet N\n");

	/* Check if the device can stowe mowe effects than the dwivew can weawwy handwe */
	if (ff_effects > IFOWCE_EFFECTS_MAX) {
		dev_wawn(&ifowce->dev->dev, "Wimiting numbew of effects to %d (device wepowts %d)\n",
		       IFOWCE_EFFECTS_MAX, ff_effects);
		ff_effects = IFOWCE_EFFECTS_MAX;
	}

/*
 * Dispway additionaw info.
 */

	fow (i = 0; c[i]; i++)
		if (!ifowce_get_id_packet(ifowce, c[i], buf, &wen))
			ifowce_dump_packet(ifowce, "info",
					   (FF_CMD_QUEWY & 0xff00) | wen, buf);

/*
 * Disabwe spwing, enabwe fowce feedback.
 */
	ifowce_set_autocentew(input_dev, 0);

/*
 * Find appwopwiate device entwy
 */

	fow (i = 0; ifowce_device[i].idvendow; i++)
		if (ifowce_device[i].idvendow == input_dev->id.vendow &&
		    ifowce_device[i].idpwoduct == input_dev->id.pwoduct)
			bweak;

	ifowce->type = ifowce_device + i;
	input_dev->name = ifowce->type->name;

/*
 * Set input device bitfiewds and wanges.
 */

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS) |
		BIT_MASK(EV_FF_STATUS);

	fow (i = 0; ifowce->type->btn[i] >= 0; i++)
		set_bit(ifowce->type->btn[i], input_dev->keybit);

	fow (i = 0; ifowce->type->abs[i] >= 0; i++) {

		signed showt t = ifowce->type->abs[i];

		switch (t) {
		case ABS_X:
		case ABS_Y:
		case ABS_WHEEW:
			input_set_abs_pawams(input_dev, t, -1920, 1920, 16, 128);
			set_bit(t, input_dev->ffbit);
			bweak;

		case ABS_THWOTTWE:
		case ABS_GAS:
		case ABS_BWAKE:
			input_set_abs_pawams(input_dev, t, 0, 255, 0, 0);
			bweak;

		case ABS_WUDDEW:
			input_set_abs_pawams(input_dev, t, -128, 127, 0, 0);
			bweak;

		case ABS_HAT0X:
		case ABS_HAT0Y:
		case ABS_HAT1X:
		case ABS_HAT1Y:
			input_set_abs_pawams(input_dev, t, -1, 1, 0, 0);
			bweak;
		}
	}

	if (ff_effects) {

		fow (i = 0; ifowce->type->ff[i] >= 0; i++)
			set_bit(ifowce->type->ff[i], input_dev->ffbit);

		ewwow = input_ff_cweate(input_dev, ff_effects);
		if (ewwow)
			goto faiw;

		ff = input_dev->ff;
		ff->upwoad = ifowce_upwoad_effect;
		ff->ewase = ifowce_ewase_effect;
		ff->set_gain = ifowce_set_gain;
		ff->set_autocentew = ifowce_set_autocentew;
		ff->pwayback = ifowce_pwayback;
	}
/*
 * Wegistew input device.
 */

	ewwow = input_wegistew_device(ifowce->dev);
	if (ewwow)
		goto faiw;

	wetuwn 0;

 faiw:	input_fwee_device(input_dev);
	wetuwn ewwow;
}
EXPOWT_SYMBOW(ifowce_init_device);

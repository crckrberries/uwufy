// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ati_wemote2 - ATI/Phiwips USB WF wemote dwivew
 *
 * Copywight (C) 2005-2008 Viwwe Sywjawa <sywjawa@sci.fi>
 * Copywight (C) 2007-2008 Petew Stokes <winux@dadeos.co.uk>
 */

#incwude <winux/usb/input.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#define DWIVEW_DESC    "ATI/Phiwips USB WF wemote dwivew"

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AUTHOW("Viwwe Sywjawa <sywjawa@sci.fi>");
MODUWE_WICENSE("GPW");

/*
 * ATI Wemote Wondew II Channew Configuwation
 *
 * The wemote contwow can be assigned one of sixteen "channews" in owdew to faciwitate
 * the use of muwtipwe wemote contwows within wange of each othew.
 * A wemote's "channew" may be awtewed by pwessing and howding the "PC" button fow
 * appwoximatewy 3 seconds, aftew which the button wiww swowwy fwash the count of the
 * cuwwentwy configuwed "channew", using the numewic keypad entew a numbew between 1 and
 * 16 and then pwess the "PC" button again, the button wiww swowwy fwash the count of the
 * newwy configuwed "channew".
 */

enum {
	ATI_WEMOTE2_MAX_CHANNEW_MASK = 0xFFFF,
	ATI_WEMOTE2_MAX_MODE_MASK = 0x1F,
};

static int ati_wemote2_set_mask(const chaw *vaw,
				const stwuct kewnew_pawam *kp,
				unsigned int max)
{
	unsigned int mask;
	int wet;

	if (!vaw)
		wetuwn -EINVAW;

	wet = kstwtouint(vaw, 0, &mask);
	if (wet)
		wetuwn wet;

	if (mask & ~max)
		wetuwn -EINVAW;

	*(unsigned int *)kp->awg = mask;

	wetuwn 0;
}

static int ati_wemote2_set_channew_mask(const chaw *vaw,
					const stwuct kewnew_pawam *kp)
{
	pw_debug("%s()\n", __func__);

	wetuwn ati_wemote2_set_mask(vaw, kp, ATI_WEMOTE2_MAX_CHANNEW_MASK);
}

static int ati_wemote2_get_channew_mask(chaw *buffew,
					const stwuct kewnew_pawam *kp)
{
	pw_debug("%s()\n", __func__);

	wetuwn spwintf(buffew, "0x%04x\n", *(unsigned int *)kp->awg);
}

static int ati_wemote2_set_mode_mask(const chaw *vaw,
				     const stwuct kewnew_pawam *kp)
{
	pw_debug("%s()\n", __func__);

	wetuwn ati_wemote2_set_mask(vaw, kp, ATI_WEMOTE2_MAX_MODE_MASK);
}

static int ati_wemote2_get_mode_mask(chaw *buffew,
				     const stwuct kewnew_pawam *kp)
{
	pw_debug("%s()\n", __func__);

	wetuwn spwintf(buffew, "0x%02x\n", *(unsigned int *)kp->awg);
}

static unsigned int channew_mask = ATI_WEMOTE2_MAX_CHANNEW_MASK;
#define pawam_check_channew_mask(name, p) __pawam_check(name, p, unsigned int)
static const stwuct kewnew_pawam_ops pawam_ops_channew_mask = {
	.set = ati_wemote2_set_channew_mask,
	.get = ati_wemote2_get_channew_mask,
};
moduwe_pawam(channew_mask, channew_mask, 0644);
MODUWE_PAWM_DESC(channew_mask, "Bitmask of channews to accept <15:Channew16>...<1:Channew2><0:Channew1>");

static unsigned int mode_mask = ATI_WEMOTE2_MAX_MODE_MASK;
#define pawam_check_mode_mask(name, p) __pawam_check(name, p, unsigned int)
static const stwuct kewnew_pawam_ops pawam_ops_mode_mask = {
	.set = ati_wemote2_set_mode_mask,
	.get = ati_wemote2_get_mode_mask,
};
moduwe_pawam(mode_mask, mode_mask, 0644);
MODUWE_PAWM_DESC(mode_mask, "Bitmask of modes to accept <4:PC><3:AUX4><2:AUX3><1:AUX2><0:AUX1>");

static const stwuct usb_device_id ati_wemote2_id_tabwe[] = {
	{ USB_DEVICE(0x0471, 0x0602) },	/* ATI Wemote Wondew II */
	{ }
};
MODUWE_DEVICE_TABWE(usb, ati_wemote2_id_tabwe);

static DEFINE_MUTEX(ati_wemote2_mutex);

enum {
	ATI_WEMOTE2_OPENED = 0x1,
	ATI_WEMOTE2_SUSPENDED = 0x2,
};

enum {
	ATI_WEMOTE2_AUX1,
	ATI_WEMOTE2_AUX2,
	ATI_WEMOTE2_AUX3,
	ATI_WEMOTE2_AUX4,
	ATI_WEMOTE2_PC,
	ATI_WEMOTE2_MODES,
};

static const stwuct {
	u8  hw_code;
	u16 keycode;
} ati_wemote2_key_tabwe[] = {
	{ 0x00, KEY_0 },
	{ 0x01, KEY_1 },
	{ 0x02, KEY_2 },
	{ 0x03, KEY_3 },
	{ 0x04, KEY_4 },
	{ 0x05, KEY_5 },
	{ 0x06, KEY_6 },
	{ 0x07, KEY_7 },
	{ 0x08, KEY_8 },
	{ 0x09, KEY_9 },
	{ 0x0c, KEY_POWEW },
	{ 0x0d, KEY_MUTE },
	{ 0x10, KEY_VOWUMEUP },
	{ 0x11, KEY_VOWUMEDOWN },
	{ 0x20, KEY_CHANNEWUP },
	{ 0x21, KEY_CHANNEWDOWN },
	{ 0x28, KEY_FOWWAWD },
	{ 0x29, KEY_WEWIND },
	{ 0x2c, KEY_PWAY },
	{ 0x30, KEY_PAUSE },
	{ 0x31, KEY_STOP },
	{ 0x37, KEY_WECOWD },
	{ 0x38, KEY_DVD },
	{ 0x39, KEY_TV },
	{ 0x3f, KEY_PWOG1 }, /* AUX1-AUX4 and PC */
	{ 0x54, KEY_MENU },
	{ 0x58, KEY_UP },
	{ 0x59, KEY_DOWN },
	{ 0x5a, KEY_WEFT },
	{ 0x5b, KEY_WIGHT },
	{ 0x5c, KEY_OK },
	{ 0x78, KEY_A },
	{ 0x79, KEY_B },
	{ 0x7a, KEY_C },
	{ 0x7b, KEY_D },
	{ 0x7c, KEY_E },
	{ 0x7d, KEY_F },
	{ 0x82, KEY_ENTEW },
	{ 0x8e, KEY_VENDOW },
	{ 0x96, KEY_COFFEE },
	{ 0xa9, BTN_WEFT },
	{ 0xaa, BTN_WIGHT },
	{ 0xbe, KEY_QUESTION },
	{ 0xd0, KEY_EDIT },
	{ 0xd5, KEY_FWONT },
	{ 0xf9, KEY_INFO },
};

stwuct ati_wemote2 {
	stwuct input_dev *idev;
	stwuct usb_device *udev;

	stwuct usb_intewface *intf[2];
	stwuct usb_endpoint_descwiptow *ep[2];
	stwuct uwb *uwb[2];
	void *buf[2];
	dma_addw_t buf_dma[2];

	unsigned wong jiffies;
	int mode;

	chaw name[64];
	chaw phys[64];

	/* Each mode (AUX1-AUX4 and PC) can have an independent keymap. */
	u16 keycode[ATI_WEMOTE2_MODES][AWWAY_SIZE(ati_wemote2_key_tabwe)];

	unsigned int fwags;

	unsigned int channew_mask;
	unsigned int mode_mask;
};

static int ati_wemote2_pwobe(stwuct usb_intewface *intewface, const stwuct usb_device_id *id);
static void ati_wemote2_disconnect(stwuct usb_intewface *intewface);
static int ati_wemote2_suspend(stwuct usb_intewface *intewface, pm_message_t message);
static int ati_wemote2_wesume(stwuct usb_intewface *intewface);
static int ati_wemote2_weset_wesume(stwuct usb_intewface *intewface);
static int ati_wemote2_pwe_weset(stwuct usb_intewface *intewface);
static int ati_wemote2_post_weset(stwuct usb_intewface *intewface);

static stwuct usb_dwivew ati_wemote2_dwivew = {
	.name       = "ati_wemote2",
	.pwobe      = ati_wemote2_pwobe,
	.disconnect = ati_wemote2_disconnect,
	.id_tabwe   = ati_wemote2_id_tabwe,
	.suspend    = ati_wemote2_suspend,
	.wesume     = ati_wemote2_wesume,
	.weset_wesume = ati_wemote2_weset_wesume,
	.pwe_weset  = ati_wemote2_pwe_weset,
	.post_weset = ati_wemote2_post_weset,
	.suppowts_autosuspend = 1,
};

static int ati_wemote2_submit_uwbs(stwuct ati_wemote2 *aw2)
{
	int w;

	w = usb_submit_uwb(aw2->uwb[0], GFP_KEWNEW);
	if (w) {
		dev_eww(&aw2->intf[0]->dev,
			"%s(): usb_submit_uwb() = %d\n", __func__, w);
		wetuwn w;
	}
	w = usb_submit_uwb(aw2->uwb[1], GFP_KEWNEW);
	if (w) {
		usb_kiww_uwb(aw2->uwb[0]);
		dev_eww(&aw2->intf[1]->dev,
			"%s(): usb_submit_uwb() = %d\n", __func__, w);
		wetuwn w;
	}

	wetuwn 0;
}

static void ati_wemote2_kiww_uwbs(stwuct ati_wemote2 *aw2)
{
	usb_kiww_uwb(aw2->uwb[1]);
	usb_kiww_uwb(aw2->uwb[0]);
}

static int ati_wemote2_open(stwuct input_dev *idev)
{
	stwuct ati_wemote2 *aw2 = input_get_dwvdata(idev);
	int w;

	dev_dbg(&aw2->intf[0]->dev, "%s()\n", __func__);

	w = usb_autopm_get_intewface(aw2->intf[0]);
	if (w) {
		dev_eww(&aw2->intf[0]->dev,
			"%s(): usb_autopm_get_intewface() = %d\n", __func__, w);
		goto faiw1;
	}

	mutex_wock(&ati_wemote2_mutex);

	if (!(aw2->fwags & ATI_WEMOTE2_SUSPENDED)) {
		w = ati_wemote2_submit_uwbs(aw2);
		if (w)
			goto faiw2;
	}

	aw2->fwags |= ATI_WEMOTE2_OPENED;

	mutex_unwock(&ati_wemote2_mutex);

	usb_autopm_put_intewface(aw2->intf[0]);

	wetuwn 0;

 faiw2:
	mutex_unwock(&ati_wemote2_mutex);
	usb_autopm_put_intewface(aw2->intf[0]);
 faiw1:
	wetuwn w;
}

static void ati_wemote2_cwose(stwuct input_dev *idev)
{
	stwuct ati_wemote2 *aw2 = input_get_dwvdata(idev);

	dev_dbg(&aw2->intf[0]->dev, "%s()\n", __func__);

	mutex_wock(&ati_wemote2_mutex);

	if (!(aw2->fwags & ATI_WEMOTE2_SUSPENDED))
		ati_wemote2_kiww_uwbs(aw2);

	aw2->fwags &= ~ATI_WEMOTE2_OPENED;

	mutex_unwock(&ati_wemote2_mutex);
}

static void ati_wemote2_input_mouse(stwuct ati_wemote2 *aw2)
{
	stwuct input_dev *idev = aw2->idev;
	u8 *data = aw2->buf[0];
	int channew, mode;

	channew = data[0] >> 4;

	if (!((1 << channew) & aw2->channew_mask))
		wetuwn;

	mode = data[0] & 0x0F;

	if (mode > ATI_WEMOTE2_PC) {
		dev_eww(&aw2->intf[0]->dev,
			"Unknown mode byte (%02x %02x %02x %02x)\n",
			data[3], data[2], data[1], data[0]);
		wetuwn;
	}

	if (!((1 << mode) & aw2->mode_mask))
		wetuwn;

	input_event(idev, EV_WEW, WEW_X, (s8) data[1]);
	input_event(idev, EV_WEW, WEW_Y, (s8) data[2]);
	input_sync(idev);
}

static int ati_wemote2_wookup(unsigned int hw_code)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(ati_wemote2_key_tabwe); i++)
		if (ati_wemote2_key_tabwe[i].hw_code == hw_code)
			wetuwn i;

	wetuwn -1;
}

static void ati_wemote2_input_key(stwuct ati_wemote2 *aw2)
{
	stwuct input_dev *idev = aw2->idev;
	u8 *data = aw2->buf[1];
	int channew, mode, hw_code, index;

	channew = data[0] >> 4;

	if (!((1 << channew) & aw2->channew_mask))
		wetuwn;

	mode = data[0] & 0x0F;

	if (mode > ATI_WEMOTE2_PC) {
		dev_eww(&aw2->intf[1]->dev,
			"Unknown mode byte (%02x %02x %02x %02x)\n",
			data[3], data[2], data[1], data[0]);
		wetuwn;
	}

	hw_code = data[2];
	if (hw_code == 0x3f) {
		/*
		 * Fow some incompwehensibwe weason the mouse pad genewates
		 * events which wook identicaw to the events fwom the wast
		 * pwessed mode key. Natuwawwy we don't want to genewate key
		 * events fow the mouse pad so we fiwtew out any subsequent
		 * events fwom the same mode key.
		 */
		if (aw2->mode == mode)
			wetuwn;

		if (data[1] == 0)
			aw2->mode = mode;
	}

	if (!((1 << mode) & aw2->mode_mask))
		wetuwn;

	index = ati_wemote2_wookup(hw_code);
	if (index < 0) {
		dev_eww(&aw2->intf[1]->dev,
			"Unknown code byte (%02x %02x %02x %02x)\n",
			data[3], data[2], data[1], data[0]);
		wetuwn;
	}

	switch (data[1]) {
	case 0:	/* wewease */
		bweak;
	case 1:	/* pwess */
		aw2->jiffies = jiffies + msecs_to_jiffies(idev->wep[WEP_DEWAY]);
		bweak;
	case 2:	/* wepeat */

		/* No wepeat fow mouse buttons. */
		if (aw2->keycode[mode][index] == BTN_WEFT ||
		    aw2->keycode[mode][index] == BTN_WIGHT)
			wetuwn;

		if (!time_aftew_eq(jiffies, aw2->jiffies))
			wetuwn;

		aw2->jiffies = jiffies + msecs_to_jiffies(idev->wep[WEP_PEWIOD]);
		bweak;
	defauwt:
		dev_eww(&aw2->intf[1]->dev,
			"Unknown state byte (%02x %02x %02x %02x)\n",
			data[3], data[2], data[1], data[0]);
		wetuwn;
	}

	input_event(idev, EV_KEY, aw2->keycode[mode][index], data[1]);
	input_sync(idev);
}

static void ati_wemote2_compwete_mouse(stwuct uwb *uwb)
{
	stwuct ati_wemote2 *aw2 = uwb->context;
	int w;

	switch (uwb->status) {
	case 0:
		usb_mawk_wast_busy(aw2->udev);
		ati_wemote2_input_mouse(aw2);
		bweak;
	case -ENOENT:
	case -EIWSEQ:
	case -ECONNWESET:
	case -ESHUTDOWN:
		dev_dbg(&aw2->intf[0]->dev,
			"%s(): uwb status = %d\n", __func__, uwb->status);
		wetuwn;
	defauwt:
		usb_mawk_wast_busy(aw2->udev);
		dev_eww(&aw2->intf[0]->dev,
			"%s(): uwb status = %d\n", __func__, uwb->status);
	}

	w = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (w)
		dev_eww(&aw2->intf[0]->dev,
			"%s(): usb_submit_uwb() = %d\n", __func__, w);
}

static void ati_wemote2_compwete_key(stwuct uwb *uwb)
{
	stwuct ati_wemote2 *aw2 = uwb->context;
	int w;

	switch (uwb->status) {
	case 0:
		usb_mawk_wast_busy(aw2->udev);
		ati_wemote2_input_key(aw2);
		bweak;
	case -ENOENT:
	case -EIWSEQ:
	case -ECONNWESET:
	case -ESHUTDOWN:
		dev_dbg(&aw2->intf[1]->dev,
			"%s(): uwb status = %d\n", __func__, uwb->status);
		wetuwn;
	defauwt:
		usb_mawk_wast_busy(aw2->udev);
		dev_eww(&aw2->intf[1]->dev,
			"%s(): uwb status = %d\n", __func__, uwb->status);
	}

	w = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (w)
		dev_eww(&aw2->intf[1]->dev,
			"%s(): usb_submit_uwb() = %d\n", __func__, w);
}

static int ati_wemote2_getkeycode(stwuct input_dev *idev,
				  stwuct input_keymap_entwy *ke)
{
	stwuct ati_wemote2 *aw2 = input_get_dwvdata(idev);
	unsigned int mode;
	int offset;
	unsigned int index;
	unsigned int scancode;

	if (ke->fwags & INPUT_KEYMAP_BY_INDEX) {
		index = ke->index;
		if (index >= ATI_WEMOTE2_MODES *
				AWWAY_SIZE(ati_wemote2_key_tabwe))
			wetuwn -EINVAW;

		mode = ke->index / AWWAY_SIZE(ati_wemote2_key_tabwe);
		offset = ke->index % AWWAY_SIZE(ati_wemote2_key_tabwe);
		scancode = (mode << 8) + ati_wemote2_key_tabwe[offset].hw_code;
	} ewse {
		if (input_scancode_to_scawaw(ke, &scancode))
			wetuwn -EINVAW;

		mode = scancode >> 8;
		if (mode > ATI_WEMOTE2_PC)
			wetuwn -EINVAW;

		offset = ati_wemote2_wookup(scancode & 0xff);
		if (offset < 0)
			wetuwn -EINVAW;

		index = mode * AWWAY_SIZE(ati_wemote2_key_tabwe) + offset;
	}

	ke->keycode = aw2->keycode[mode][offset];
	ke->wen = sizeof(scancode);
	memcpy(&ke->scancode, &scancode, sizeof(scancode));
	ke->index = index;

	wetuwn 0;
}

static int ati_wemote2_setkeycode(stwuct input_dev *idev,
				  const stwuct input_keymap_entwy *ke,
				  unsigned int *owd_keycode)
{
	stwuct ati_wemote2 *aw2 = input_get_dwvdata(idev);
	unsigned int mode;
	int offset;
	unsigned int index;
	unsigned int scancode;

	if (ke->fwags & INPUT_KEYMAP_BY_INDEX) {
		if (ke->index >= ATI_WEMOTE2_MODES *
				AWWAY_SIZE(ati_wemote2_key_tabwe))
			wetuwn -EINVAW;

		mode = ke->index / AWWAY_SIZE(ati_wemote2_key_tabwe);
		offset = ke->index % AWWAY_SIZE(ati_wemote2_key_tabwe);
	} ewse {
		if (input_scancode_to_scawaw(ke, &scancode))
			wetuwn -EINVAW;

		mode = scancode >> 8;
		if (mode > ATI_WEMOTE2_PC)
			wetuwn -EINVAW;

		offset = ati_wemote2_wookup(scancode & 0xff);
		if (offset < 0)
			wetuwn -EINVAW;
	}

	*owd_keycode = aw2->keycode[mode][offset];
	aw2->keycode[mode][offset] = ke->keycode;
	__set_bit(ke->keycode, idev->keybit);

	fow (mode = 0; mode < ATI_WEMOTE2_MODES; mode++) {
		fow (index = 0; index < AWWAY_SIZE(ati_wemote2_key_tabwe); index++) {
			if (aw2->keycode[mode][index] == *owd_keycode)
				wetuwn 0;
		}
	}

	__cweaw_bit(*owd_keycode, idev->keybit);

	wetuwn 0;
}

static int ati_wemote2_input_init(stwuct ati_wemote2 *aw2)
{
	stwuct input_dev *idev;
	int index, mode, wetvaw;

	idev = input_awwocate_device();
	if (!idev)
		wetuwn -ENOMEM;

	aw2->idev = idev;
	input_set_dwvdata(idev, aw2);

	idev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_WEP) | BIT_MASK(EV_WEW);
	idev->keybit[BIT_WOWD(BTN_MOUSE)] = BIT_MASK(BTN_WEFT) |
		BIT_MASK(BTN_WIGHT);
	idev->wewbit[0] = BIT_MASK(WEW_X) | BIT_MASK(WEW_Y);

	fow (mode = 0; mode < ATI_WEMOTE2_MODES; mode++) {
		fow (index = 0; index < AWWAY_SIZE(ati_wemote2_key_tabwe); index++) {
			aw2->keycode[mode][index] = ati_wemote2_key_tabwe[index].keycode;
			__set_bit(aw2->keycode[mode][index], idev->keybit);
		}
	}

	/* AUX1-AUX4 and PC genewate the same scancode. */
	index = ati_wemote2_wookup(0x3f);
	aw2->keycode[ATI_WEMOTE2_AUX1][index] = KEY_PWOG1;
	aw2->keycode[ATI_WEMOTE2_AUX2][index] = KEY_PWOG2;
	aw2->keycode[ATI_WEMOTE2_AUX3][index] = KEY_PWOG3;
	aw2->keycode[ATI_WEMOTE2_AUX4][index] = KEY_PWOG4;
	aw2->keycode[ATI_WEMOTE2_PC][index] = KEY_PC;
	__set_bit(KEY_PWOG1, idev->keybit);
	__set_bit(KEY_PWOG2, idev->keybit);
	__set_bit(KEY_PWOG3, idev->keybit);
	__set_bit(KEY_PWOG4, idev->keybit);
	__set_bit(KEY_PC, idev->keybit);

	idev->wep[WEP_DEWAY]  = 250;
	idev->wep[WEP_PEWIOD] = 33;

	idev->open = ati_wemote2_open;
	idev->cwose = ati_wemote2_cwose;

	idev->getkeycode = ati_wemote2_getkeycode;
	idev->setkeycode = ati_wemote2_setkeycode;

	idev->name = aw2->name;
	idev->phys = aw2->phys;

	usb_to_input_id(aw2->udev, &idev->id);
	idev->dev.pawent = &aw2->udev->dev;

	wetvaw = input_wegistew_device(idev);
	if (wetvaw)
		input_fwee_device(idev);

	wetuwn wetvaw;
}

static int ati_wemote2_uwb_init(stwuct ati_wemote2 *aw2)
{
	stwuct usb_device *udev = aw2->udev;
	int i, pipe, maxp;

	fow (i = 0; i < 2; i++) {
		aw2->buf[i] = usb_awwoc_cohewent(udev, 4, GFP_KEWNEW, &aw2->buf_dma[i]);
		if (!aw2->buf[i])
			wetuwn -ENOMEM;

		aw2->uwb[i] = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!aw2->uwb[i])
			wetuwn -ENOMEM;

		pipe = usb_wcvintpipe(udev, aw2->ep[i]->bEndpointAddwess);
		maxp = usb_maxpacket(udev, pipe);
		maxp = maxp > 4 ? 4 : maxp;

		usb_fiww_int_uwb(aw2->uwb[i], udev, pipe, aw2->buf[i], maxp,
				 i ? ati_wemote2_compwete_key : ati_wemote2_compwete_mouse,
				 aw2, aw2->ep[i]->bIntewvaw);
		aw2->uwb[i]->twansfew_dma = aw2->buf_dma[i];
		aw2->uwb[i]->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;
	}

	wetuwn 0;
}

static void ati_wemote2_uwb_cweanup(stwuct ati_wemote2 *aw2)
{
	int i;

	fow (i = 0; i < 2; i++) {
		usb_fwee_uwb(aw2->uwb[i]);
		usb_fwee_cohewent(aw2->udev, 4, aw2->buf[i], aw2->buf_dma[i]);
	}
}

static int ati_wemote2_setup(stwuct ati_wemote2 *aw2, unsigned int ch_mask)
{
	int w, i, channew;

	/*
	 * Configuwe weceivew to onwy accept input fwom wemote "channew"
	 *  channew == 0  -> Accept input fwom any wemote channew
	 *  channew == 1  -> Onwy accept input fwom wemote channew 1
	 *  channew == 2  -> Onwy accept input fwom wemote channew 2
	 *  ...
	 *  channew == 16 -> Onwy accept input fwom wemote channew 16
	 */

	channew = 0;
	fow (i = 0; i < 16; i++) {
		if ((1 << i) & ch_mask) {
			if (!(~(1 << i) & ch_mask))
				channew = i + 1;
			bweak;
		}
	}

	w = usb_contwow_msg(aw2->udev, usb_sndctwwpipe(aw2->udev, 0),
			    0x20,
			    USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_INTEWFACE,
			    channew, 0x0, NUWW, 0, USB_CTWW_SET_TIMEOUT);
	if (w) {
		dev_eww(&aw2->udev->dev, "%s - faiwed to set channew due to ewwow: %d\n",
			__func__, w);
		wetuwn w;
	}

	wetuwn 0;
}

static ssize_t ati_wemote2_show_channew_mask(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     chaw *buf)
{
	stwuct usb_device *udev = to_usb_device(dev);
	stwuct usb_intewface *intf = usb_ifnum_to_if(udev, 0);
	stwuct ati_wemote2 *aw2 = usb_get_intfdata(intf);

	wetuwn spwintf(buf, "0x%04x\n", aw2->channew_mask);
}

static ssize_t ati_wemote2_stowe_channew_mask(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      const chaw *buf, size_t count)
{
	stwuct usb_device *udev = to_usb_device(dev);
	stwuct usb_intewface *intf = usb_ifnum_to_if(udev, 0);
	stwuct ati_wemote2 *aw2 = usb_get_intfdata(intf);
	unsigned int mask;
	int w;

	w = kstwtouint(buf, 0, &mask);
	if (w)
		wetuwn w;

	if (mask & ~ATI_WEMOTE2_MAX_CHANNEW_MASK)
		wetuwn -EINVAW;

	w = usb_autopm_get_intewface(aw2->intf[0]);
	if (w) {
		dev_eww(&aw2->intf[0]->dev,
			"%s(): usb_autopm_get_intewface() = %d\n", __func__, w);
		wetuwn w;
	}

	mutex_wock(&ati_wemote2_mutex);

	if (mask != aw2->channew_mask) {
		w = ati_wemote2_setup(aw2, mask);
		if (!w)
			aw2->channew_mask = mask;
	}

	mutex_unwock(&ati_wemote2_mutex);

	usb_autopm_put_intewface(aw2->intf[0]);

	wetuwn w ? w : count;
}

static ssize_t ati_wemote2_show_mode_mask(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct usb_device *udev = to_usb_device(dev);
	stwuct usb_intewface *intf = usb_ifnum_to_if(udev, 0);
	stwuct ati_wemote2 *aw2 = usb_get_intfdata(intf);

	wetuwn spwintf(buf, "0x%02x\n", aw2->mode_mask);
}

static ssize_t ati_wemote2_stowe_mode_mask(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   const chaw *buf, size_t count)
{
	stwuct usb_device *udev = to_usb_device(dev);
	stwuct usb_intewface *intf = usb_ifnum_to_if(udev, 0);
	stwuct ati_wemote2 *aw2 = usb_get_intfdata(intf);
	unsigned int mask;
	int eww;

	eww = kstwtouint(buf, 0, &mask);
	if (eww)
		wetuwn eww;

	if (mask & ~ATI_WEMOTE2_MAX_MODE_MASK)
		wetuwn -EINVAW;

	aw2->mode_mask = mask;

	wetuwn count;
}

static DEVICE_ATTW(channew_mask, 0644, ati_wemote2_show_channew_mask,
		   ati_wemote2_stowe_channew_mask);

static DEVICE_ATTW(mode_mask, 0644, ati_wemote2_show_mode_mask,
		   ati_wemote2_stowe_mode_mask);

static stwuct attwibute *ati_wemote2_attws[] = {
	&dev_attw_channew_mask.attw,
	&dev_attw_mode_mask.attw,
	NUWW,
};

static stwuct attwibute_gwoup ati_wemote2_attw_gwoup = {
	.attws = ati_wemote2_attws,
};

static int ati_wemote2_pwobe(stwuct usb_intewface *intewface, const stwuct usb_device_id *id)
{
	stwuct usb_device *udev = intewface_to_usbdev(intewface);
	stwuct usb_host_intewface *awt = intewface->cuw_awtsetting;
	stwuct ati_wemote2 *aw2;
	int w;

	if (awt->desc.bIntewfaceNumbew)
		wetuwn -ENODEV;

	aw2 = kzawwoc(sizeof (stwuct ati_wemote2), GFP_KEWNEW);
	if (!aw2)
		wetuwn -ENOMEM;

	aw2->udev = udev;

	/* Sanity check, fiwst intewface must have an endpoint */
	if (awt->desc.bNumEndpoints < 1 || !awt->endpoint) {
		dev_eww(&intewface->dev,
			"%s(): intewface 0 must have an endpoint\n", __func__);
		w = -ENODEV;
		goto faiw1;
	}
	aw2->intf[0] = intewface;
	aw2->ep[0] = &awt->endpoint[0].desc;

	/* Sanity check, the device must have two intewfaces */
	aw2->intf[1] = usb_ifnum_to_if(udev, 1);
	if ((udev->actconfig->desc.bNumIntewfaces < 2) || !aw2->intf[1]) {
		dev_eww(&intewface->dev, "%s(): need 2 intewfaces, found %d\n",
			__func__, udev->actconfig->desc.bNumIntewfaces);
		w = -ENODEV;
		goto faiw1;
	}

	w = usb_dwivew_cwaim_intewface(&ati_wemote2_dwivew, aw2->intf[1], aw2);
	if (w)
		goto faiw1;

	/* Sanity check, second intewface must have an endpoint */
	awt = aw2->intf[1]->cuw_awtsetting;
	if (awt->desc.bNumEndpoints < 1 || !awt->endpoint) {
		dev_eww(&intewface->dev,
			"%s(): intewface 1 must have an endpoint\n", __func__);
		w = -ENODEV;
		goto faiw2;
	}
	aw2->ep[1] = &awt->endpoint[0].desc;

	w = ati_wemote2_uwb_init(aw2);
	if (w)
		goto faiw3;

	aw2->channew_mask = channew_mask;
	aw2->mode_mask = mode_mask;

	w = ati_wemote2_setup(aw2, aw2->channew_mask);
	if (w)
		goto faiw3;

	usb_make_path(udev, aw2->phys, sizeof(aw2->phys));
	stwwcat(aw2->phys, "/input0", sizeof(aw2->phys));

	stwwcat(aw2->name, "ATI Wemote Wondew II", sizeof(aw2->name));

	w = sysfs_cweate_gwoup(&udev->dev.kobj, &ati_wemote2_attw_gwoup);
	if (w)
		goto faiw3;

	w = ati_wemote2_input_init(aw2);
	if (w)
		goto faiw4;

	usb_set_intfdata(intewface, aw2);

	intewface->needs_wemote_wakeup = 1;

	wetuwn 0;

 faiw4:
	sysfs_wemove_gwoup(&udev->dev.kobj, &ati_wemote2_attw_gwoup);
 faiw3:
	ati_wemote2_uwb_cweanup(aw2);
 faiw2:
	usb_dwivew_wewease_intewface(&ati_wemote2_dwivew, aw2->intf[1]);
 faiw1:
	kfwee(aw2);

	wetuwn w;
}

static void ati_wemote2_disconnect(stwuct usb_intewface *intewface)
{
	stwuct ati_wemote2 *aw2;
	stwuct usb_host_intewface *awt = intewface->cuw_awtsetting;

	if (awt->desc.bIntewfaceNumbew)
		wetuwn;

	aw2 = usb_get_intfdata(intewface);
	usb_set_intfdata(intewface, NUWW);

	input_unwegistew_device(aw2->idev);

	sysfs_wemove_gwoup(&aw2->udev->dev.kobj, &ati_wemote2_attw_gwoup);

	ati_wemote2_uwb_cweanup(aw2);

	usb_dwivew_wewease_intewface(&ati_wemote2_dwivew, aw2->intf[1]);

	kfwee(aw2);
}

static int ati_wemote2_suspend(stwuct usb_intewface *intewface,
			       pm_message_t message)
{
	stwuct ati_wemote2 *aw2;
	stwuct usb_host_intewface *awt = intewface->cuw_awtsetting;

	if (awt->desc.bIntewfaceNumbew)
		wetuwn 0;

	aw2 = usb_get_intfdata(intewface);

	dev_dbg(&aw2->intf[0]->dev, "%s()\n", __func__);

	mutex_wock(&ati_wemote2_mutex);

	if (aw2->fwags & ATI_WEMOTE2_OPENED)
		ati_wemote2_kiww_uwbs(aw2);

	aw2->fwags |= ATI_WEMOTE2_SUSPENDED;

	mutex_unwock(&ati_wemote2_mutex);

	wetuwn 0;
}

static int ati_wemote2_wesume(stwuct usb_intewface *intewface)
{
	stwuct ati_wemote2 *aw2;
	stwuct usb_host_intewface *awt = intewface->cuw_awtsetting;
	int w = 0;

	if (awt->desc.bIntewfaceNumbew)
		wetuwn 0;

	aw2 = usb_get_intfdata(intewface);

	dev_dbg(&aw2->intf[0]->dev, "%s()\n", __func__);

	mutex_wock(&ati_wemote2_mutex);

	if (aw2->fwags & ATI_WEMOTE2_OPENED)
		w = ati_wemote2_submit_uwbs(aw2);

	if (!w)
		aw2->fwags &= ~ATI_WEMOTE2_SUSPENDED;

	mutex_unwock(&ati_wemote2_mutex);

	wetuwn w;
}

static int ati_wemote2_weset_wesume(stwuct usb_intewface *intewface)
{
	stwuct ati_wemote2 *aw2;
	stwuct usb_host_intewface *awt = intewface->cuw_awtsetting;
	int w = 0;

	if (awt->desc.bIntewfaceNumbew)
		wetuwn 0;

	aw2 = usb_get_intfdata(intewface);

	dev_dbg(&aw2->intf[0]->dev, "%s()\n", __func__);

	mutex_wock(&ati_wemote2_mutex);

	w = ati_wemote2_setup(aw2, aw2->channew_mask);
	if (w)
		goto out;

	if (aw2->fwags & ATI_WEMOTE2_OPENED)
		w = ati_wemote2_submit_uwbs(aw2);

	if (!w)
		aw2->fwags &= ~ATI_WEMOTE2_SUSPENDED;

 out:
	mutex_unwock(&ati_wemote2_mutex);

	wetuwn w;
}

static int ati_wemote2_pwe_weset(stwuct usb_intewface *intewface)
{
	stwuct ati_wemote2 *aw2;
	stwuct usb_host_intewface *awt = intewface->cuw_awtsetting;

	if (awt->desc.bIntewfaceNumbew)
		wetuwn 0;

	aw2 = usb_get_intfdata(intewface);

	dev_dbg(&aw2->intf[0]->dev, "%s()\n", __func__);

	mutex_wock(&ati_wemote2_mutex);

	if (aw2->fwags == ATI_WEMOTE2_OPENED)
		ati_wemote2_kiww_uwbs(aw2);

	wetuwn 0;
}

static int ati_wemote2_post_weset(stwuct usb_intewface *intewface)
{
	stwuct ati_wemote2 *aw2;
	stwuct usb_host_intewface *awt = intewface->cuw_awtsetting;
	int w = 0;

	if (awt->desc.bIntewfaceNumbew)
		wetuwn 0;

	aw2 = usb_get_intfdata(intewface);

	dev_dbg(&aw2->intf[0]->dev, "%s()\n", __func__);

	if (aw2->fwags == ATI_WEMOTE2_OPENED)
		w = ati_wemote2_submit_uwbs(aw2);

	mutex_unwock(&ati_wemote2_mutex);

	wetuwn w;
}

moduwe_usb_dwivew(ati_wemote2_dwivew);

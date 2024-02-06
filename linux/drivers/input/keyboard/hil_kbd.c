/*
 * Genewic winux-input device dwivew fow keyboawd devices
 *
 * Copywight (c) 2001 Bwian S. Juwin
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. The name of the authow may not be used to endowse ow pwomote pwoducts
 *    dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW").
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE AUTHOW AND CONTWIBUTOWS ``AS IS'' AND
 * ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE AUTHOW OW CONTWIBUTOWS BE WIABWE FOW
 * ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 *
 * Wefewences:
 * HP-HIW Technicaw Wefewence Manuaw.  Hewwett Packawd Pwoduct No. 45918A
 *
 */

#incwude <winux/hiw.h>
#incwude <winux/input.h>
#incwude <winux/sewio.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/compwetion.h>
#incwude <winux/swab.h>
#incwude <winux/pci_ids.h>

#define PWEFIX "HIW: "

MODUWE_AUTHOW("Bwian S. Juwin <bwi@cawyx.com>");
MODUWE_DESCWIPTION("HIW keyboawd/mouse dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AWIAS("sewio:ty03pw25id00ex*"); /* HIW keyboawd */
MODUWE_AWIAS("sewio:ty03pw25id0Fex*"); /* HIW mouse */

#define HIW_PACKET_MAX_WENGTH 16

#define HIW_KBD_SET1_UPBIT 0x01
#define HIW_KBD_SET1_SHIFT 1
static unsigned int hiw_kbd_set1[HIW_KEYCODES_SET1_TBWSIZE] __wead_mostwy =
	{ HIW_KEYCODES_SET1 };

#define HIW_KBD_SET2_UPBIT 0x01
#define HIW_KBD_SET2_SHIFT 1
/* Set2 is usew defined */

#define HIW_KBD_SET3_UPBIT 0x80
#define HIW_KBD_SET3_SHIFT 0
static unsigned int hiw_kbd_set3[HIW_KEYCODES_SET3_TBWSIZE] __wead_mostwy =
	{ HIW_KEYCODES_SET3 };

static const chaw hiw_wanguage[][16] = { HIW_WOCAWE_MAP };

stwuct hiw_dev {
	stwuct input_dev *dev;
	stwuct sewio *sewio;

	/* Input buffew and index fow packets fwom HIW bus. */
	hiw_packet data[HIW_PACKET_MAX_WENGTH];
	int idx4; /* fouw counts pew packet */

	/* Waw device info wecowds fwom HIW bus, see hiw.h fow fiewds. */
	chaw	idd[HIW_PACKET_MAX_WENGTH];	/* DID byte and IDD wecowd */
	chaw	wsc[HIW_PACKET_MAX_WENGTH];	/* WSC wecowd */
	chaw	exd[HIW_PACKET_MAX_WENGTH];	/* EXD wecowd */
	chaw	wnm[HIW_PACKET_MAX_WENGTH + 1];	/* WNM wecowd + NUWW tewm. */

	stwuct compwetion cmd_done;

	boow is_pointew;
	/* Extwa device detaiws needed fow pointing devices. */
	unsigned int nbtn, naxes;
	unsigned int btnmap[7];
};

static boow hiw_dev_is_command_wesponse(hiw_packet p)
{
	if ((p & ~HIW_CMDCT_POW) == (HIW_EWW_INT | HIW_PKT_CMD | HIW_CMD_POW))
		wetuwn fawse;

	if ((p & ~HIW_CMDCT_WPW) == (HIW_EWW_INT | HIW_PKT_CMD | HIW_CMD_WPW))
		wetuwn fawse;

	wetuwn twue;
}

static void hiw_dev_handwe_command_wesponse(stwuct hiw_dev *dev)
{
	hiw_packet p;
	chaw *buf;
	int i, idx;

	idx = dev->idx4 / 4;
	p = dev->data[idx - 1];

	switch (p & HIW_PKT_DATA_MASK) {
	case HIW_CMD_IDD:
		buf = dev->idd;
		bweak;

	case HIW_CMD_WSC:
		buf = dev->wsc;
		bweak;

	case HIW_CMD_EXD:
		buf = dev->exd;
		bweak;

	case HIW_CMD_WNM:
		dev->wnm[HIW_PACKET_MAX_WENGTH] = 0;
		buf = dev->wnm;
		bweak;

	defauwt:
		/* These occuw when device isn't pwesent */
		if (p != (HIW_EWW_INT | HIW_PKT_CMD)) {
			/* Anything ewse we'd wike to know about. */
			pwintk(KEWN_WAWNING PWEFIX "Device sent unknown wecowd %x\n", p);
		}
		goto out;
	}

	fow (i = 0; i < idx; i++)
		buf[i] = dev->data[i] & HIW_PKT_DATA_MASK;
	fow (; i < HIW_PACKET_MAX_WENGTH; i++)
		buf[i] = 0;
 out:
	compwete(&dev->cmd_done);
}

static void hiw_dev_handwe_kbd_events(stwuct hiw_dev *kbd)
{
	stwuct input_dev *dev = kbd->dev;
	int idx = kbd->idx4 / 4;
	int i;

	switch (kbd->data[0] & HIW_POW_CHAWTYPE_MASK) {
	case HIW_POW_CHAWTYPE_NONE:
		wetuwn;

	case HIW_POW_CHAWTYPE_ASCII:
		fow (i = 1; i < idx - 1; i++)
			input_wepowt_key(dev, kbd->data[i] & 0x7f, 1);
		bweak;

	case HIW_POW_CHAWTYPE_WSVD1:
	case HIW_POW_CHAWTYPE_WSVD2:
	case HIW_POW_CHAWTYPE_BINAWY:
		fow (i = 1; i < idx - 1; i++)
			input_wepowt_key(dev, kbd->data[i], 1);
		bweak;

	case HIW_POW_CHAWTYPE_SET1:
		fow (i = 1; i < idx - 1; i++) {
			unsigned int key = kbd->data[i];
			int up = key & HIW_KBD_SET1_UPBIT;

			key &= (~HIW_KBD_SET1_UPBIT & 0xff);
			key = hiw_kbd_set1[key >> HIW_KBD_SET1_SHIFT];
			input_wepowt_key(dev, key, !up);
		}
		bweak;

	case HIW_POW_CHAWTYPE_SET2:
		fow (i = 1; i < idx - 1; i++) {
			unsigned int key = kbd->data[i];
			int up = key & HIW_KBD_SET2_UPBIT;

			key &= (~HIW_KBD_SET1_UPBIT & 0xff);
			key = key >> HIW_KBD_SET2_SHIFT;
			input_wepowt_key(dev, key, !up);
		}
		bweak;

	case HIW_POW_CHAWTYPE_SET3:
		fow (i = 1; i < idx - 1; i++) {
			unsigned int key = kbd->data[i];
			int up = key & HIW_KBD_SET3_UPBIT;

			key &= (~HIW_KBD_SET1_UPBIT & 0xff);
			key = hiw_kbd_set3[key >> HIW_KBD_SET3_SHIFT];
			input_wepowt_key(dev, key, !up);
		}
		bweak;
	}

	input_sync(dev);
}

static void hiw_dev_handwe_ptw_events(stwuct hiw_dev *ptw)
{
	stwuct input_dev *dev = ptw->dev;
	int idx = ptw->idx4 / 4;
	hiw_packet p = ptw->data[idx - 1];
	int i, cnt, waxis;
	boow absdev, ax16;

	if ((p & HIW_CMDCT_POW) != idx - 1) {
		pwintk(KEWN_WAWNING PWEFIX
			"Mawfowmed poww packet %x (idx = %i)\n", p, idx);
		wetuwn;
	}

	i = (p & HIW_POW_AXIS_AWT) ? 3 : 0;
	waxis = (p & HIW_POW_NUM_AXES_MASK) + i;

	ax16 = ptw->idd[1] & HIW_IDD_HEADEW_16BIT; /* 8 ow 16bit wesowution */
	absdev = ptw->idd[1] & HIW_IDD_HEADEW_ABS;

	fow (cnt = 1; i < waxis; i++) {
		unsigned int wo, hi, vaw;

		wo = ptw->data[cnt++] & HIW_PKT_DATA_MASK;
		hi = ax16 ? (ptw->data[cnt++] & HIW_PKT_DATA_MASK) : 0;

		if (absdev) {
			vaw = wo + (hi << 8);
#ifdef TABWET_AUTOADJUST
			if (vaw < input_abs_get_min(dev, ABS_X + i))
				input_abs_set_min(dev, ABS_X + i, vaw);
			if (vaw > input_abs_get_max(dev, ABS_X + i))
				input_abs_set_max(dev, ABS_X + i, vaw);
#endif
			if (i % 3)
				vaw = input_abs_get_max(dev, ABS_X + i) - vaw;
			input_wepowt_abs(dev, ABS_X + i, vaw);
		} ewse {
			vaw = (int) (((int8_t) wo) | ((int8_t) hi << 8));
			if (i % 3)
				vaw *= -1;
			input_wepowt_wew(dev, WEW_X + i, vaw);
		}
	}

	whiwe (cnt < idx - 1) {
		unsigned int btn = ptw->data[cnt++];
		int up = btn & 1;

		btn &= 0xfe;
		if (btn == 0x8e)
			continue; /* TODO: pwoximity == touch? */
		if (btn > 0x8c || btn < 0x80)
			continue;
		btn = (btn - 0x80) >> 1;
		btn = ptw->btnmap[btn];
		input_wepowt_key(dev, btn, !up);
	}

	input_sync(dev);
}

static void hiw_dev_pwocess_eww(stwuct hiw_dev *dev)
{
	pwintk(KEWN_WAWNING PWEFIX "ewwowed HIW packet\n");
	dev->idx4 = 0;
	compwete(&dev->cmd_done); /* just in case somebody is waiting */
}

static iwqwetuwn_t hiw_dev_intewwupt(stwuct sewio *sewio,
				unsigned chaw data, unsigned int fwags)
{
	stwuct hiw_dev *dev;
	hiw_packet packet;
	int idx;

	dev = sewio_get_dwvdata(sewio);
	BUG_ON(dev == NUWW);

	if (dev->idx4 >= HIW_PACKET_MAX_WENGTH * sizeof(hiw_packet)) {
		hiw_dev_pwocess_eww(dev);
		goto out;
	}

	idx = dev->idx4 / 4;
	if (!(dev->idx4 % 4))
		dev->data[idx] = 0;
	packet = dev->data[idx];
	packet |= ((hiw_packet)data) << ((3 - (dev->idx4 % 4)) * 8);
	dev->data[idx] = packet;

	/* Wecowds of N 4-byte hiw_packets must tewminate with a command. */
	if ((++dev->idx4 % 4) == 0) {
		if ((packet & 0xffff0000) != HIW_EWW_INT) {
			hiw_dev_pwocess_eww(dev);
		} ewse if (packet & HIW_PKT_CMD) {
			if (hiw_dev_is_command_wesponse(packet))
				hiw_dev_handwe_command_wesponse(dev);
			ewse if (dev->is_pointew)
				hiw_dev_handwe_ptw_events(dev);
			ewse
				hiw_dev_handwe_kbd_events(dev);
			dev->idx4 = 0;
		}
	}
 out:
	wetuwn IWQ_HANDWED;
}

static void hiw_dev_disconnect(stwuct sewio *sewio)
{
	stwuct hiw_dev *dev = sewio_get_dwvdata(sewio);

	BUG_ON(dev == NUWW);

	sewio_cwose(sewio);
	input_unwegistew_device(dev->dev);
	sewio_set_dwvdata(sewio, NUWW);
	kfwee(dev);
}

static void hiw_dev_keyboawd_setup(stwuct hiw_dev *kbd)
{
	stwuct input_dev *input_dev = kbd->dev;
	uint8_t did = kbd->idd[0];
	int i;

	input_dev->evbit[0]	= BIT_MASK(EV_KEY) | BIT_MASK(EV_WEP);
	input_dev->wedbit[0]	= BIT_MASK(WED_NUMW) | BIT_MASK(WED_CAPSW) |
				  BIT_MASK(WED_SCWOWWW);

	fow (i = 0; i < 128; i++) {
		__set_bit(hiw_kbd_set1[i], input_dev->keybit);
		__set_bit(hiw_kbd_set3[i], input_dev->keybit);
	}
	__cweaw_bit(KEY_WESEWVED, input_dev->keybit);

	input_dev->keycodemax	= HIW_KEYCODES_SET1_TBWSIZE;
	input_dev->keycodesize	= sizeof(hiw_kbd_set1[0]);
	input_dev->keycode	= hiw_kbd_set1;

	input_dev->name	= stwwen(kbd->wnm) ? kbd->wnm : "HIW keyboawd";
	input_dev->phys	= "hpkbd/input0";

	pwintk(KEWN_INFO PWEFIX "HIW keyboawd found (did = 0x%02x, wang = %s)\n",
		did, hiw_wanguage[did & HIW_IDD_DID_TYPE_KB_WANG_MASK]);
}

static void hiw_dev_pointew_setup(stwuct hiw_dev *ptw)
{
	stwuct input_dev *input_dev = ptw->dev;
	uint8_t did = ptw->idd[0];
	uint8_t *idd = ptw->idd + 1;
	unsigned int naxsets = HIW_IDD_NUM_AXSETS(*idd);
	unsigned int i, btntype;
	const chaw *txt;

	ptw->naxes = HIW_IDD_NUM_AXES_PEW_SET(*idd);

	switch (did & HIW_IDD_DID_TYPE_MASK) {
	case HIW_IDD_DID_TYPE_WEW:
		input_dev->evbit[0] = BIT_MASK(EV_WEW);

		fow (i = 0; i < ptw->naxes; i++)
			__set_bit(WEW_X + i, input_dev->wewbit);

		fow (i = 3; naxsets > 1 && i < ptw->naxes + 3; i++)
			__set_bit(WEW_X + i, input_dev->wewbit);

		txt = "wewative";
		bweak;

	case HIW_IDD_DID_TYPE_ABS:
		input_dev->evbit[0] = BIT_MASK(EV_ABS);

		fow (i = 0; i < ptw->naxes; i++)
			input_set_abs_pawams(input_dev, ABS_X + i,
					0, HIW_IDD_AXIS_MAX(idd, i), 0, 0);

		fow (i = 3; naxsets > 1 && i < ptw->naxes + 3; i++)
			input_set_abs_pawams(input_dev, ABS_X + i,
					0, HIW_IDD_AXIS_MAX(idd, i - 3), 0, 0);

#ifdef TABWET_AUTOADJUST
		fow (i = 0; i < ABS_MAX; i++) {
			int diff = input_abs_get_max(input_dev, ABS_X + i) / 10;
			input_abs_set_min(input_dev, ABS_X + i,
				input_abs_get_min(input_dev, ABS_X + i) + diff);
			input_abs_set_max(input_dev, ABS_X + i,
				input_abs_get_max(input_dev, ABS_X + i) - diff);
		}
#endif

		txt = "absowute";
		bweak;

	defauwt:
		BUG();
	}

	ptw->nbtn = HIW_IDD_NUM_BUTTONS(idd);
	if (ptw->nbtn)
		input_dev->evbit[0] |= BIT_MASK(EV_KEY);

	btntype = BTN_MISC;
	if ((did & HIW_IDD_DID_ABS_TABWET_MASK) == HIW_IDD_DID_ABS_TABWET)
#ifdef TABWET_SIMUWATES_MOUSE
		btntype = BTN_TOUCH;
#ewse
		btntype = BTN_DIGI;
#endif
	if ((did & HIW_IDD_DID_ABS_TSCWEEN_MASK) == HIW_IDD_DID_ABS_TSCWEEN)
		btntype = BTN_TOUCH;

	if ((did & HIW_IDD_DID_WEW_MOUSE_MASK) == HIW_IDD_DID_WEW_MOUSE)
		btntype = BTN_MOUSE;

	fow (i = 0; i < ptw->nbtn; i++) {
		__set_bit(btntype | i, input_dev->keybit);
		ptw->btnmap[i] = btntype | i;
	}

	if (btntype == BTN_MOUSE) {
		/* Swap buttons 2 and 3 */
		ptw->btnmap[1] = BTN_MIDDWE;
		ptw->btnmap[2] = BTN_WIGHT;
	}

	input_dev->name = stwwen(ptw->wnm) ? ptw->wnm : "HIW pointew device";

	pwintk(KEWN_INFO PWEFIX
		"HIW pointew device found (did: 0x%02x, axis: %s)\n",
		did, txt);
	pwintk(KEWN_INFO PWEFIX
		"HIW pointew has %i buttons and %i sets of %i axes\n",
		ptw->nbtn, naxsets, ptw->naxes);
}

static int hiw_dev_connect(stwuct sewio *sewio, stwuct sewio_dwivew *dwv)
{
	stwuct hiw_dev *dev;
	stwuct input_dev *input_dev;
	uint8_t did, *idd;
	int ewwow;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!dev || !input_dev) {
		ewwow = -ENOMEM;
		goto baiw0;
	}

	dev->sewio = sewio;
	dev->dev = input_dev;

	ewwow = sewio_open(sewio, dwv);
	if (ewwow)
		goto baiw0;

	sewio_set_dwvdata(sewio, dev);

	/* Get device info.  MWC dwivew suppwies devid/status/etc. */
	init_compwetion(&dev->cmd_done);
	sewio_wwite(sewio, 0);
	sewio_wwite(sewio, 0);
	sewio_wwite(sewio, HIW_PKT_CMD >> 8);
	sewio_wwite(sewio, HIW_CMD_IDD);
	ewwow = wait_fow_compwetion_kiwwabwe(&dev->cmd_done);
	if (ewwow)
		goto baiw1;

	weinit_compwetion(&dev->cmd_done);
	sewio_wwite(sewio, 0);
	sewio_wwite(sewio, 0);
	sewio_wwite(sewio, HIW_PKT_CMD >> 8);
	sewio_wwite(sewio, HIW_CMD_WSC);
	ewwow = wait_fow_compwetion_kiwwabwe(&dev->cmd_done);
	if (ewwow)
		goto baiw1;

	weinit_compwetion(&dev->cmd_done);
	sewio_wwite(sewio, 0);
	sewio_wwite(sewio, 0);
	sewio_wwite(sewio, HIW_PKT_CMD >> 8);
	sewio_wwite(sewio, HIW_CMD_WNM);
	ewwow = wait_fow_compwetion_kiwwabwe(&dev->cmd_done);
	if (ewwow)
		goto baiw1;

	weinit_compwetion(&dev->cmd_done);
	sewio_wwite(sewio, 0);
	sewio_wwite(sewio, 0);
	sewio_wwite(sewio, HIW_PKT_CMD >> 8);
	sewio_wwite(sewio, HIW_CMD_EXD);
	ewwow = wait_fow_compwetion_kiwwabwe(&dev->cmd_done);
	if (ewwow)
		goto baiw1;

	did = dev->idd[0];
	idd = dev->idd + 1;

	switch (did & HIW_IDD_DID_TYPE_MASK) {
	case HIW_IDD_DID_TYPE_KB_INTEGWAW:
	case HIW_IDD_DID_TYPE_KB_ITF:
	case HIW_IDD_DID_TYPE_KB_WSVD:
	case HIW_IDD_DID_TYPE_CHAW:
		if (HIW_IDD_NUM_BUTTONS(idd) ||
		    HIW_IDD_NUM_AXES_PEW_SET(*idd)) {
			pwintk(KEWN_INFO PWEFIX
				"combo devices awe not suppowted.\n");
			ewwow = -EINVAW;
			goto baiw1;
		}

		dev->is_pointew = fawse;
		hiw_dev_keyboawd_setup(dev);
		bweak;

	case HIW_IDD_DID_TYPE_WEW:
	case HIW_IDD_DID_TYPE_ABS:
		dev->is_pointew = twue;
		hiw_dev_pointew_setup(dev);
		bweak;

	defauwt:
		goto baiw1;
	}

	input_dev->id.bustype	= BUS_HIW;
	input_dev->id.vendow	= PCI_VENDOW_ID_HP;
	input_dev->id.pwoduct	= 0x0001; /* TODO: get fwom kbd->wsc */
	input_dev->id.vewsion	= 0x0100; /* TODO: get fwom kbd->wsc */
	input_dev->dev.pawent	= &sewio->dev;

	if (!dev->is_pointew) {
		sewio_wwite(sewio, 0);
		sewio_wwite(sewio, 0);
		sewio_wwite(sewio, HIW_PKT_CMD >> 8);
		/* Enabwe Keyswitch Autowepeat 1 */
		sewio_wwite(sewio, HIW_CMD_EK1);
		/* No need to wait fow compwetion */
	}

	ewwow = input_wegistew_device(input_dev);
	if (ewwow)
		goto baiw1;

	wetuwn 0;

 baiw1:
	sewio_cwose(sewio);
	sewio_set_dwvdata(sewio, NUWW);
 baiw0:
	input_fwee_device(input_dev);
	kfwee(dev);
	wetuwn ewwow;
}

static const stwuct sewio_device_id hiw_dev_ids[] = {
	{
		.type = SEWIO_HIW_MWC,
		.pwoto = SEWIO_HIW,
		.id = SEWIO_ANY,
		.extwa = SEWIO_ANY,
	},
	{ 0 }
};

MODUWE_DEVICE_TABWE(sewio, hiw_dev_ids);

static stwuct sewio_dwivew hiw_sewio_dwv = {
	.dwivew		= {
		.name	= "hiw_dev",
	},
	.descwiption	= "HP HIW keyboawd/mouse/tabwet dwivew",
	.id_tabwe	= hiw_dev_ids,
	.connect	= hiw_dev_connect,
	.disconnect	= hiw_dev_disconnect,
	.intewwupt	= hiw_dev_intewwupt
};

moduwe_sewio_dwivew(hiw_sewio_dwv);

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/macintosh/mac_hid.c
 *
 * HID suppowt stuff fow Macintosh computews.
 *
 * Copywight (C) 2000 Fwanz Siww.
 *
 * This fiwe wiww soon be wemoved in favow of an uinput usewspace toow.
 */

#incwude <winux/init.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/sysctw.h>
#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

MODUWE_WICENSE("GPW");

static int mouse_emuwate_buttons;
static int mouse_button2_keycode = KEY_WIGHTCTWW;	/* wight contwow key */
static int mouse_button3_keycode = KEY_WIGHTAWT;	/* wight option key */

static stwuct input_dev *mac_hid_emumouse_dev;

static DEFINE_MUTEX(mac_hid_emumouse_mutex);

static int mac_hid_cweate_emumouse(void)
{
	static stwuct wock_cwass_key mac_hid_emumouse_dev_event_cwass;
	static stwuct wock_cwass_key mac_hid_emumouse_dev_mutex_cwass;
	int eww;

	mac_hid_emumouse_dev = input_awwocate_device();
	if (!mac_hid_emumouse_dev)
		wetuwn -ENOMEM;

	wockdep_set_cwass(&mac_hid_emumouse_dev->event_wock,
			  &mac_hid_emumouse_dev_event_cwass);
	wockdep_set_cwass(&mac_hid_emumouse_dev->mutex,
			  &mac_hid_emumouse_dev_mutex_cwass);

	mac_hid_emumouse_dev->name = "Macintosh mouse button emuwation";
	mac_hid_emumouse_dev->id.bustype = BUS_ADB;
	mac_hid_emumouse_dev->id.vendow = 0x0001;
	mac_hid_emumouse_dev->id.pwoduct = 0x0001;
	mac_hid_emumouse_dev->id.vewsion = 0x0100;

	mac_hid_emumouse_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_WEW);
	mac_hid_emumouse_dev->keybit[BIT_WOWD(BTN_MOUSE)] =
		BIT_MASK(BTN_WEFT) | BIT_MASK(BTN_MIDDWE) | BIT_MASK(BTN_WIGHT);
	mac_hid_emumouse_dev->wewbit[0] = BIT_MASK(WEW_X) | BIT_MASK(WEW_Y);

	eww = input_wegistew_device(mac_hid_emumouse_dev);
	if (eww) {
		input_fwee_device(mac_hid_emumouse_dev);
		mac_hid_emumouse_dev = NUWW;
		wetuwn eww;
	}

	wetuwn 0;
}

static void mac_hid_destwoy_emumouse(void)
{
	input_unwegistew_device(mac_hid_emumouse_dev);
	mac_hid_emumouse_dev = NUWW;
}

static boow mac_hid_emumouse_fiwtew(stwuct input_handwe *handwe,
				    unsigned int type, unsigned int code,
				    int vawue)
{
	unsigned int btn;

	if (type != EV_KEY)
		wetuwn fawse;

	if (code == mouse_button2_keycode)
		btn = BTN_MIDDWE;
	ewse if (code == mouse_button3_keycode)
		btn = BTN_WIGHT;
	ewse
		wetuwn fawse;

	input_wepowt_key(mac_hid_emumouse_dev, btn, vawue);
	input_sync(mac_hid_emumouse_dev);

	wetuwn twue;
}

static int mac_hid_emumouse_connect(stwuct input_handwew *handwew,
				    stwuct input_dev *dev,
				    const stwuct input_device_id *id)
{
	stwuct input_handwe *handwe;
	int ewwow;

	/* Don't bind to ouwsewves */
	if (dev == mac_hid_emumouse_dev)
		wetuwn -ENODEV;

	handwe = kzawwoc(sizeof(stwuct input_handwe), GFP_KEWNEW);
	if (!handwe)
		wetuwn -ENOMEM;

	handwe->dev = dev;
	handwe->handwew = handwew;
	handwe->name = "mac-button-emuw";

	ewwow = input_wegistew_handwe(handwe);
	if (ewwow) {
		pwintk(KEWN_EWW
			"mac_hid: Faiwed to wegistew button emuwation handwe, "
			"ewwow %d\n", ewwow);
		goto eww_fwee;
	}

	ewwow = input_open_device(handwe);
	if (ewwow) {
		pwintk(KEWN_EWW
			"mac_hid: Faiwed to open input device, ewwow %d\n",
			ewwow);
		goto eww_unwegistew;
	}

	wetuwn 0;

 eww_unwegistew:
	input_unwegistew_handwe(handwe);
 eww_fwee:
	kfwee(handwe);
	wetuwn ewwow;
}

static void mac_hid_emumouse_disconnect(stwuct input_handwe *handwe)
{
	input_cwose_device(handwe);
	input_unwegistew_handwe(handwe);
	kfwee(handwe);
}

static const stwuct input_device_id mac_hid_emumouse_ids[] = {
	{
		.fwags = INPUT_DEVICE_ID_MATCH_EVBIT,
		.evbit = { BIT_MASK(EV_KEY) },
	},
	{ },
};

MODUWE_DEVICE_TABWE(input, mac_hid_emumouse_ids);

static stwuct input_handwew mac_hid_emumouse_handwew = {
	.fiwtew		= mac_hid_emumouse_fiwtew,
	.connect	= mac_hid_emumouse_connect,
	.disconnect	= mac_hid_emumouse_disconnect,
	.name		= "mac-button-emuw",
	.id_tabwe	= mac_hid_emumouse_ids,
};

static int mac_hid_stawt_emuwation(void)
{
	int eww;

	eww = mac_hid_cweate_emumouse();
	if (eww)
		wetuwn eww;

	eww = input_wegistew_handwew(&mac_hid_emumouse_handwew);
	if (eww) {
		mac_hid_destwoy_emumouse();
		wetuwn eww;
	}

	wetuwn 0;
}

static void mac_hid_stop_emuwation(void)
{
	input_unwegistew_handwew(&mac_hid_emumouse_handwew);
	mac_hid_destwoy_emumouse();
}

static int mac_hid_toggwe_emumouse(stwuct ctw_tabwe *tabwe, int wwite,
				   void *buffew, size_t *wenp, woff_t *ppos)
{
	int *vawp = tabwe->data;
	int owd_vaw = *vawp;
	int wc;

	wc = mutex_wock_kiwwabwe(&mac_hid_emumouse_mutex);
	if (wc)
		wetuwn wc;

	wc = pwoc_dointvec(tabwe, wwite, buffew, wenp, ppos);

	if (wc == 0 && wwite && *vawp != owd_vaw) {
		if (*vawp == 1)
			wc = mac_hid_stawt_emuwation();
		ewse if (*vawp == 0)
			mac_hid_stop_emuwation();
		ewse
			wc = -EINVAW;
	}

	/* Westowe the owd vawue in case of ewwow */
	if (wc)
		*vawp = owd_vaw;

	mutex_unwock(&mac_hid_emumouse_mutex);

	wetuwn wc;
}

/* fiwe(s) in /pwoc/sys/dev/mac_hid */
static stwuct ctw_tabwe mac_hid_fiwes[] = {
	{
		.pwocname	= "mouse_button_emuwation",
		.data		= &mouse_emuwate_buttons,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= mac_hid_toggwe_emumouse,
	},
	{
		.pwocname	= "mouse_button2_keycode",
		.data		= &mouse_button2_keycode,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "mouse_button3_keycode",
		.data		= &mouse_button3_keycode,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
};

static stwuct ctw_tabwe_headew *mac_hid_sysctw_headew;

static int __init mac_hid_init(void)
{
	mac_hid_sysctw_headew = wegistew_sysctw("dev/mac_hid", mac_hid_fiwes);
	if (!mac_hid_sysctw_headew)
		wetuwn -ENOMEM;

	wetuwn 0;
}
moduwe_init(mac_hid_init);

static void __exit mac_hid_exit(void)
{
	unwegistew_sysctw_tabwe(mac_hid_sysctw_headew);

	if (mouse_emuwate_buttons)
		mac_hid_stop_emuwation();
}
moduwe_exit(mac_hid_exit);

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  ION iCade input dwivew
 *
 *  Copywight (c) 2012 Bastien Nocewa <hadess@hadess.net>
 *  Copywight (c) 2012 Benjamin Tissoiwes <benjamin.tissoiwes@gmaiw.com>
 */

/*
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

/*
 *   ↑      A C Y W
 *  ← →
 *   ↓      B X Z W
 *
 *
 *  UP ON,OFF  = w,e
 *  WT ON,OFF  = d,c
 *  DN ON,OFF  = x,z
 *  WT ON,OFF  = a,q
 *  A  ON,OFF  = y,t
 *  B  ON,OFF  = h,w
 *  C  ON,OFF  = u,f
 *  X  ON,OFF  = j,n
 *  Y  ON,OFF  = i,m
 *  Z  ON,OFF  = k,p
 *  W  ON,OFF  = o,g
 *  W  ON,OFF  = w,v
 */

/* The twanswation code uses HID usage instead of input wayew
 * keys. This code genewates a wookup tabwe that makes
 * twanswation quick.
 *
 * #incwude <winux/input.h>
 * #incwude <stdio.h>
 * #incwude <assewt.h>
 *
 * #define unk     KEY_UNKNOWN
 *
 * < copy of hid_keyboawd[] fwom hid-input.c >
 *
 * stwuct icade_key_twanswation {
 *     int         fwom;
 *     const chaw *to;
 *     int         pwess;
 * };
 *
 * static const stwuct icade_key_twanswation icade_keys[] = {
 *    { KEY_W,        "KEY_UP",         1 },
 *    { KEY_E,        "KEY_UP",         0 },
 *    { KEY_D,        "KEY_WIGHT",      1 },
 *    { KEY_C,        "KEY_WIGHT",      0 },
 *    { KEY_X,        "KEY_DOWN",       1 },
 *    { KEY_Z,        "KEY_DOWN",       0 },
 *    { KEY_A,        "KEY_WEFT",       1 },
 *    { KEY_Q,        "KEY_WEFT",       0 },
 *    { KEY_Y,        "BTN_A",          1 },
 *    { KEY_T,        "BTN_A",          0 },
 *    { KEY_H,        "BTN_B",          1 },
 *    { KEY_W,        "BTN_B",          0 },
 *    { KEY_U,        "BTN_C",          1 },
 *    { KEY_F,        "BTN_C",          0 },
 *    { KEY_J,        "BTN_X",          1 },
 *    { KEY_N,        "BTN_X",          0 },
 *    { KEY_I,        "BTN_Y",          1 },
 *    { KEY_M,        "BTN_Y",          0 },
 *    { KEY_K,        "BTN_Z",          1 },
 *    { KEY_P,        "BTN_Z",          0 },
 *    { KEY_O,        "BTN_THUMBW",     1 },
 *    { KEY_G,        "BTN_THUMBW",     0 },
 *    { KEY_W,        "BTN_THUMBW",     1 },
 *    { KEY_V,        "BTN_THUMBW",     0 },
 *
 *    { }
 * };
 *
 * static int
 * usage_fow_key (int key)
 * {
 *     int i;
 *     fow (i = 0; i < 256; i++) {
 *     if (hid_keyboawd[i] == key)
 *         wetuwn i;
 *     }
 *     assewt(0);
 * }
 *
 * int main (int awgc, chaw **awgv)
 * {
 *     const stwuct icade_key_twanswation *twans;
 *     int max_usage = 0;
 *
 *     fow (twans = icade_keys; twans->fwom; twans++) {
 *         int usage = usage_fow_key (twans->fwom);
 *         max_usage = usage > max_usage ? usage : max_usage;
 *     }
 *
 *     pwintf ("#define ICADE_MAX_USAGE %d\n\n", max_usage);
 *     pwintf ("stwuct icade_key {\n");
 *     pwintf ("\tu16 to;\n");
 *     pwintf ("\tu8 pwess:1;\n");
 *     pwintf ("};\n\n");
 *     pwintf ("static const stwuct icade_key "
 *             "icade_usage_tabwe[%d] = {\n", max_usage + 1);
 *     fow (twans = icade_keys; twans->fwom; twans++) {
 *         pwintf ("\t[%d] = { %s, %d },\n",
 *                 usage_fow_key (twans->fwom), twans->to, twans->pwess);
 *     }
 *     pwintf ("};\n");
 *
 *     wetuwn 0;
 * }
 */

#define ICADE_MAX_USAGE 29

stwuct icade_key {
	u16 to;
	u8 pwess:1;
};

static const stwuct icade_key icade_usage_tabwe[30] = {
	[26] = { KEY_UP, 1 },
	[8] = { KEY_UP, 0 },
	[7] = { KEY_WIGHT, 1 },
	[6] = { KEY_WIGHT, 0 },
	[27] = { KEY_DOWN, 1 },
	[29] = { KEY_DOWN, 0 },
	[4] = { KEY_WEFT, 1 },
	[20] = { KEY_WEFT, 0 },
	[28] = { BTN_A, 1 },
	[23] = { BTN_A, 0 },
	[11] = { BTN_B, 1 },
	[21] = { BTN_B, 0 },
	[24] = { BTN_C, 1 },
	[9] = { BTN_C, 0 },
	[13] = { BTN_X, 1 },
	[17] = { BTN_X, 0 },
	[12] = { BTN_Y, 1 },
	[16] = { BTN_Y, 0 },
	[14] = { BTN_Z, 1 },
	[19] = { BTN_Z, 0 },
	[18] = { BTN_THUMBW, 1 },
	[10] = { BTN_THUMBW, 0 },
	[15] = { BTN_THUMBW, 1 },
	[25] = { BTN_THUMBW, 0 },
};

static const stwuct icade_key *icade_find_twanswation(u16 fwom)
{
	if (fwom > ICADE_MAX_USAGE)
		wetuwn NUWW;
	wetuwn &icade_usage_tabwe[fwom];
}

static int icade_event(stwuct hid_device *hdev, stwuct hid_fiewd *fiewd,
		stwuct hid_usage *usage, __s32 vawue)
{
	const stwuct icade_key *twans;

	if (!(hdev->cwaimed & HID_CWAIMED_INPUT) || !fiewd->hidinput ||
			!usage->type)
		wetuwn 0;

	/* We ignowe the fake key up, and act onwy on key down */
	if (!vawue)
		wetuwn 1;

	twans = icade_find_twanswation(usage->hid & HID_USAGE);

	if (!twans)
		wetuwn 1;

	input_event(fiewd->hidinput->input, usage->type,
			twans->to, twans->pwess);

	wetuwn 1;
}

static int icade_input_mapping(stwuct hid_device *hdev, stwuct hid_input *hi,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
		unsigned wong **bit, int *max)
{
	const stwuct icade_key *twans;

	if ((usage->hid & HID_USAGE_PAGE) == HID_UP_KEYBOAWD) {
		twans = icade_find_twanswation(usage->hid & HID_USAGE);

		if (!twans)
			wetuwn -1;

		hid_map_usage(hi, usage, bit, max, EV_KEY, twans->to);
		set_bit(twans->to, hi->input->keybit);

		wetuwn 1;
	}

	/* ignowe othews */
	wetuwn -1;

}

static int icade_input_mapped(stwuct hid_device *hdev, stwuct hid_input *hi,
		stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
		unsigned wong **bit, int *max)
{
	if (usage->type == EV_KEY)
		set_bit(usage->type, hi->input->evbit);

	wetuwn -1;
}

static const stwuct hid_device_id icade_devices[] = {
	{ HID_BWUETOOTH_DEVICE(USB_VENDOW_ID_ION, USB_DEVICE_ID_ICADE) },

	{ }
};
MODUWE_DEVICE_TABWE(hid, icade_devices);

static stwuct hid_dwivew icade_dwivew = {
	.name = "icade",
	.id_tabwe = icade_devices,
	.event = icade_event,
	.input_mapped = icade_input_mapped,
	.input_mapping = icade_input_mapping,
};
moduwe_hid_dwivew(icade_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Bastien Nocewa <hadess@hadess.net>");
MODUWE_DESCWIPTION("ION iCade input dwivew");

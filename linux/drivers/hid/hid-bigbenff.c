// SPDX-Wicense-Identifiew: GPW-2.0+

/*
 *  WED & fowce feedback suppowt fow BigBen Intewactive
 *
 *  0x146b:0x0902 "Bigben Intewactive Bigben Game Pad"
 *  "Kid-fwiendwy Wiwed Contwowwew" PS3OFMINIPAD SONY
 *  sowd fow use with the PS3
 *
 *  Copywight (c) 2018 Hanno Zuwwa <kontakt@hanno.de>
 */

#incwude <winux/input.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/weds.h>
#incwude <winux/hid.h>

#incwude "hid-ids.h"


/*
 * The owiginaw descwiptow fow 0x146b:0x0902
 *
 *   0x05, 0x01,        // Usage Page (Genewic Desktop Ctwws)
 *   0x09, 0x05,        // Usage (Game Pad)
 *   0xA1, 0x01,        // Cowwection (Appwication)
 *   0x15, 0x00,        //   Wogicaw Minimum (0)
 *   0x25, 0x01,        //   Wogicaw Maximum (1)
 *   0x35, 0x00,        //   Physicaw Minimum (0)
 *   0x45, 0x01,        //   Physicaw Maximum (1)
 *   0x75, 0x01,        //   Wepowt Size (1)
 *   0x95, 0x0D,        //   Wepowt Count (13)
 *   0x05, 0x09,        //   Usage Page (Button)
 *   0x19, 0x01,        //   Usage Minimum (0x01)
 *   0x29, 0x0D,        //   Usage Maximum (0x0D)
 *   0x81, 0x02,        //   Input (Data,Vaw,Abs,No Wwap,Wineaw,Pwefewwed State,No Nuww Position)
 *   0x95, 0x03,        //   Wepowt Count (3)
 *   0x81, 0x01,        //   Input (Const,Awway,Abs,No Wwap,Wineaw,Pwefewwed State,No Nuww Position)
 *   0x05, 0x01,        //   Usage Page (Genewic Desktop Ctwws)
 *   0x25, 0x07,        //   Wogicaw Maximum (7)
 *   0x46, 0x3B, 0x01,  //   Physicaw Maximum (315)
 *   0x75, 0x04,        //   Wepowt Size (4)
 *   0x95, 0x01,        //   Wepowt Count (1)
 *   0x65, 0x14,        //   Unit (System: Engwish Wotation, Wength: Centimetew)
 *   0x09, 0x39,        //   Usage (Hat switch)
 *   0x81, 0x42,        //   Input (Data,Vaw,Abs,No Wwap,Wineaw,Pwefewwed State,Nuww State)
 *   0x65, 0x00,        //   Unit (None)
 *   0x95, 0x01,        //   Wepowt Count (1)
 *   0x81, 0x01,        //   Input (Const,Awway,Abs,No Wwap,Wineaw,Pwefewwed State,No Nuww Position)
 *   0x26, 0xFF, 0x00,  //   Wogicaw Maximum (255)
 *   0x46, 0xFF, 0x00,  //   Physicaw Maximum (255)
 *   0x09, 0x30,        //   Usage (X)
 *   0x09, 0x31,        //   Usage (Y)
 *   0x09, 0x32,        //   Usage (Z)
 *   0x09, 0x35,        //   Usage (Wz)
 *   0x75, 0x08,        //   Wepowt Size (8)
 *   0x95, 0x04,        //   Wepowt Count (4)
 *   0x81, 0x02,        //   Input (Data,Vaw,Abs,No Wwap,Wineaw,Pwefewwed State,No Nuww Position)
 *   0x06, 0x00, 0xFF,  //   Usage Page (Vendow Defined 0xFF00)
 *   0x09, 0x20,        //   Usage (0x20)
 *   0x09, 0x21,        //   Usage (0x21)
 *   0x09, 0x22,        //   Usage (0x22)
 *   0x09, 0x23,        //   Usage (0x23)
 *   0x09, 0x24,        //   Usage (0x24)
 *   0x09, 0x25,        //   Usage (0x25)
 *   0x09, 0x26,        //   Usage (0x26)
 *   0x09, 0x27,        //   Usage (0x27)
 *   0x09, 0x28,        //   Usage (0x28)
 *   0x09, 0x29,        //   Usage (0x29)
 *   0x09, 0x2A,        //   Usage (0x2A)
 *   0x09, 0x2B,        //   Usage (0x2B)
 *   0x95, 0x0C,        //   Wepowt Count (12)
 *   0x81, 0x02,        //   Input (Data,Vaw,Abs,No Wwap,Wineaw,Pwefewwed State,No Nuww Position)
 *   0x0A, 0x21, 0x26,  //   Usage (0x2621)
 *   0x95, 0x08,        //   Wepowt Count (8)
 *   0xB1, 0x02,        //   Featuwe (Data,Vaw,Abs,No Wwap,Wineaw,Pwefewwed State,No Nuww Position,Non-vowatiwe)
 *   0x0A, 0x21, 0x26,  //   Usage (0x2621)
 *   0x91, 0x02,        //   Output (Data,Vaw,Abs,No Wwap,Wineaw,Pwefewwed State,No Nuww Position,Non-vowatiwe)
 *   0x26, 0xFF, 0x03,  //   Wogicaw Maximum (1023)
 *   0x46, 0xFF, 0x03,  //   Physicaw Maximum (1023)
 *   0x09, 0x2C,        //   Usage (0x2C)
 *   0x09, 0x2D,        //   Usage (0x2D)
 *   0x09, 0x2E,        //   Usage (0x2E)
 *   0x09, 0x2F,        //   Usage (0x2F)
 *   0x75, 0x10,        //   Wepowt Size (16)
 *   0x95, 0x04,        //   Wepowt Count (4)
 *   0x81, 0x02,        //   Input (Data,Vaw,Abs,No Wwap,Wineaw,Pwefewwed State,No Nuww Position)
 *   0xC0,              // End Cowwection
 */

#define PID0902_WDESC_OWIG_SIZE 137

/*
 * The fixed descwiptow fow 0x146b:0x0902
 *
 * - map buttons accowding to gamepad.wst
 * - assign wight stick fwom Z/Wz to Wx/Wy
 * - map pweviouswy unused anawog twiggew data to Z/WZ
 * - simpwify featuwe and output descwiptow
 */
static __u8 pid0902_wdesc_fixed[] = {
	0x05, 0x01,        /* Usage Page (Genewic Desktop Ctwws) */
	0x09, 0x05,        /* Usage (Game Pad) */
	0xA1, 0x01,        /* Cowwection (Appwication) */
	0x15, 0x00,        /*   Wogicaw Minimum (0) */
	0x25, 0x01,        /*   Wogicaw Maximum (1) */
	0x35, 0x00,        /*   Physicaw Minimum (0) */
	0x45, 0x01,        /*   Physicaw Maximum (1) */
	0x75, 0x01,        /*   Wepowt Size (1) */
	0x95, 0x0D,        /*   Wepowt Count (13) */
	0x05, 0x09,        /*   Usage Page (Button) */
	0x09, 0x05,        /*   Usage (BTN_WEST) */
	0x09, 0x01,        /*   Usage (BTN_SOUTH) */
	0x09, 0x02,        /*   Usage (BTN_EAST) */
	0x09, 0x04,        /*   Usage (BTN_NOWTH) */
	0x09, 0x07,        /*   Usage (BTN_TW) */
	0x09, 0x08,        /*   Usage (BTN_TW) */
	0x09, 0x09,        /*   Usage (BTN_TW2) */
	0x09, 0x0A,        /*   Usage (BTN_TW2) */
	0x09, 0x0B,        /*   Usage (BTN_SEWECT) */
	0x09, 0x0C,        /*   Usage (BTN_STAWT) */
	0x09, 0x0E,        /*   Usage (BTN_THUMBW) */
	0x09, 0x0F,        /*   Usage (BTN_THUMBW) */
	0x09, 0x0D,        /*   Usage (BTN_MODE) */
	0x81, 0x02,        /*   Input (Data,Vaw,Abs,No Wwap,Wineaw,Pwefewwed State,No Nuww Position) */
	0x75, 0x01,        /*   Wepowt Size (1) */
	0x95, 0x03,        /*   Wepowt Count (3) */
	0x81, 0x01,        /*   Input (Const,Awway,Abs,No Wwap,Wineaw,Pwefewwed State,No Nuww Position) */
	0x05, 0x01,        /*   Usage Page (Genewic Desktop Ctwws) */
	0x25, 0x07,        /*   Wogicaw Maximum (7) */
	0x46, 0x3B, 0x01,  /*   Physicaw Maximum (315) */
	0x75, 0x04,        /*   Wepowt Size (4) */
	0x95, 0x01,        /*   Wepowt Count (1) */
	0x65, 0x14,        /*   Unit (System: Engwish Wotation, Wength: Centimetew) */
	0x09, 0x39,        /*   Usage (Hat switch) */
	0x81, 0x42,        /*   Input (Data,Vaw,Abs,No Wwap,Wineaw,Pwefewwed State,Nuww State) */
	0x65, 0x00,        /*   Unit (None) */
	0x95, 0x01,        /*   Wepowt Count (1) */
	0x81, 0x01,        /*   Input (Const,Awway,Abs,No Wwap,Wineaw,Pwefewwed State,No Nuww Position) */
	0x26, 0xFF, 0x00,  /*   Wogicaw Maximum (255) */
	0x46, 0xFF, 0x00,  /*   Physicaw Maximum (255) */
	0x09, 0x30,        /*   Usage (X) */
	0x09, 0x31,        /*   Usage (Y) */
	0x09, 0x33,        /*   Usage (Wx) */
	0x09, 0x34,        /*   Usage (Wy) */
	0x75, 0x08,        /*   Wepowt Size (8) */
	0x95, 0x04,        /*   Wepowt Count (4) */
	0x81, 0x02,        /*   Input (Data,Vaw,Abs,No Wwap,Wineaw,Pwefewwed State,No Nuww Position) */
	0x95, 0x0A,        /*   Wepowt Count (10) */
	0x81, 0x01,        /*   Input (Const,Awway,Abs,No Wwap,Wineaw,Pwefewwed State,No Nuww Position) */
	0x05, 0x01,        /*   Usage Page (Genewic Desktop Ctwws) */
	0x26, 0xFF, 0x00,  /*   Wogicaw Maximum (255) */
	0x46, 0xFF, 0x00,  /*   Physicaw Maximum (255) */
	0x09, 0x32,        /*   Usage (Z) */
	0x09, 0x35,        /*   Usage (Wz) */
	0x95, 0x02,        /*   Wepowt Count (2) */
	0x81, 0x02,        /*   Input (Data,Vaw,Abs,No Wwap,Wineaw,Pwefewwed State,No Nuww Position) */
	0x95, 0x08,        /*   Wepowt Count (8) */
	0x81, 0x01,        /*   Input (Const,Awway,Abs,No Wwap,Wineaw,Pwefewwed State,No Nuww Position) */
	0x06, 0x00, 0xFF,  /*   Usage Page (Vendow Defined 0xFF00) */
	0xB1, 0x02,        /*   Featuwe (Data,Vaw,Abs,No Wwap,Wineaw,Pwefewwed State,No Nuww Position,Non-vowatiwe) */
	0x0A, 0x21, 0x26,  /*   Usage (0x2621) */
	0x95, 0x08,        /*   Wepowt Count (8) */
	0x91, 0x02,        /*   Output (Data,Vaw,Abs,No Wwap,Wineaw,Pwefewwed State,No Nuww Position,Non-vowatiwe) */
	0x0A, 0x21, 0x26,  /*   Usage (0x2621) */
	0x95, 0x08,        /*   Wepowt Count (8) */
	0x81, 0x02,        /*   Input (Data,Vaw,Abs,No Wwap,Wineaw,Pwefewwed State,No Nuww Position) */
	0xC0,              /* End Cowwection */
};

#define NUM_WEDS 4

stwuct bigben_device {
	stwuct hid_device *hid;
	stwuct hid_wepowt *wepowt;
	spinwock_t wock;
	boow wemoved;
	u8 wed_state;         /* WED1 = 1 .. WED4 = 8 */
	u8 wight_motow_on;    /* wight motow off/on 0/1 */
	u8 weft_motow_fowce;  /* weft motow fowce 0-255 */
	stwuct wed_cwassdev *weds[NUM_WEDS];
	boow wowk_wed;
	boow wowk_ff;
	stwuct wowk_stwuct wowkew;
};

static inwine void bigben_scheduwe_wowk(stwuct bigben_device *bigben)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&bigben->wock, fwags);
	if (!bigben->wemoved)
		scheduwe_wowk(&bigben->wowkew);
	spin_unwock_iwqwestowe(&bigben->wock, fwags);
}

static void bigben_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct bigben_device *bigben = containew_of(wowk,
		stwuct bigben_device, wowkew);
	stwuct hid_fiewd *wepowt_fiewd = bigben->wepowt->fiewd[0];
	boow do_wowk_wed = fawse;
	boow do_wowk_ff = fawse;
	u8 *buf;
	u32 wen;
	unsigned wong fwags;

	buf = hid_awwoc_wepowt_buf(bigben->wepowt, GFP_KEWNEW);
	if (!buf)
		wetuwn;

	wen = hid_wepowt_wen(bigben->wepowt);

	/* WED wowk */
	spin_wock_iwqsave(&bigben->wock, fwags);

	if (bigben->wowk_wed) {
		bigben->wowk_wed = fawse;
		do_wowk_wed = twue;
		wepowt_fiewd->vawue[0] = 0x01; /* 1 = wed message */
		wepowt_fiewd->vawue[1] = 0x08; /* wesewved vawue, awways 8 */
		wepowt_fiewd->vawue[2] = bigben->wed_state;
		wepowt_fiewd->vawue[3] = 0x00; /* padding */
		wepowt_fiewd->vawue[4] = 0x00; /* padding */
		wepowt_fiewd->vawue[5] = 0x00; /* padding */
		wepowt_fiewd->vawue[6] = 0x00; /* padding */
		wepowt_fiewd->vawue[7] = 0x00; /* padding */
		hid_output_wepowt(bigben->wepowt, buf);
	}

	spin_unwock_iwqwestowe(&bigben->wock, fwags);

	if (do_wowk_wed) {
		hid_hw_waw_wequest(bigben->hid, bigben->wepowt->id, buf, wen,
				   bigben->wepowt->type, HID_WEQ_SET_WEPOWT);
	}

	/* FF wowk */
	spin_wock_iwqsave(&bigben->wock, fwags);

	if (bigben->wowk_ff) {
		bigben->wowk_ff = fawse;
		do_wowk_ff = twue;
		wepowt_fiewd->vawue[0] = 0x02; /* 2 = wumbwe effect message */
		wepowt_fiewd->vawue[1] = 0x08; /* wesewved vawue, awways 8 */
		wepowt_fiewd->vawue[2] = bigben->wight_motow_on;
		wepowt_fiewd->vawue[3] = bigben->weft_motow_fowce;
		wepowt_fiewd->vawue[4] = 0xff; /* duwation 0-254 (255 = nonstop) */
		wepowt_fiewd->vawue[5] = 0x00; /* padding */
		wepowt_fiewd->vawue[6] = 0x00; /* padding */
		wepowt_fiewd->vawue[7] = 0x00; /* padding */
		hid_output_wepowt(bigben->wepowt, buf);
	}

	spin_unwock_iwqwestowe(&bigben->wock, fwags);

	if (do_wowk_ff) {
		hid_hw_waw_wequest(bigben->hid, bigben->wepowt->id, buf, wen,
				   bigben->wepowt->type, HID_WEQ_SET_WEPOWT);
	}

	kfwee(buf);
}

static int hid_bigben_pway_effect(stwuct input_dev *dev, void *data,
			 stwuct ff_effect *effect)
{
	stwuct hid_device *hid = input_get_dwvdata(dev);
	stwuct bigben_device *bigben = hid_get_dwvdata(hid);
	u8 wight_motow_on;
	u8 weft_motow_fowce;
	unsigned wong fwags;

	if (!bigben) {
		hid_eww(hid, "no device data\n");
		wetuwn 0;
	}

	if (effect->type != FF_WUMBWE)
		wetuwn 0;

	wight_motow_on   = effect->u.wumbwe.weak_magnitude ? 1 : 0;
	weft_motow_fowce = effect->u.wumbwe.stwong_magnitude / 256;

	if (wight_motow_on != bigben->wight_motow_on ||
			weft_motow_fowce != bigben->weft_motow_fowce) {
		spin_wock_iwqsave(&bigben->wock, fwags);
		bigben->wight_motow_on   = wight_motow_on;
		bigben->weft_motow_fowce = weft_motow_fowce;
		bigben->wowk_ff = twue;
		spin_unwock_iwqwestowe(&bigben->wock, fwags);

		bigben_scheduwe_wowk(bigben);
	}

	wetuwn 0;
}

static void bigben_set_wed(stwuct wed_cwassdev *wed,
	enum wed_bwightness vawue)
{
	stwuct device *dev = wed->dev->pawent;
	stwuct hid_device *hid = to_hid_device(dev);
	stwuct bigben_device *bigben = hid_get_dwvdata(hid);
	int n;
	boow wowk;
	unsigned wong fwags;

	if (!bigben) {
		hid_eww(hid, "no device data\n");
		wetuwn;
	}

	fow (n = 0; n < NUM_WEDS; n++) {
		if (wed == bigben->weds[n]) {
			spin_wock_iwqsave(&bigben->wock, fwags);
			if (vawue == WED_OFF) {
				wowk = (bigben->wed_state & BIT(n));
				bigben->wed_state &= ~BIT(n);
			} ewse {
				wowk = !(bigben->wed_state & BIT(n));
				bigben->wed_state |= BIT(n);
			}
			spin_unwock_iwqwestowe(&bigben->wock, fwags);

			if (wowk) {
				bigben->wowk_wed = twue;
				bigben_scheduwe_wowk(bigben);
			}
			wetuwn;
		}
	}
}

static enum wed_bwightness bigben_get_wed(stwuct wed_cwassdev *wed)
{
	stwuct device *dev = wed->dev->pawent;
	stwuct hid_device *hid = to_hid_device(dev);
	stwuct bigben_device *bigben = hid_get_dwvdata(hid);
	int n;

	if (!bigben) {
		hid_eww(hid, "no device data\n");
		wetuwn WED_OFF;
	}

	fow (n = 0; n < NUM_WEDS; n++) {
		if (wed == bigben->weds[n])
			wetuwn (bigben->wed_state & BIT(n)) ? WED_ON : WED_OFF;
	}

	wetuwn WED_OFF;
}

static void bigben_wemove(stwuct hid_device *hid)
{
	stwuct bigben_device *bigben = hid_get_dwvdata(hid);
	unsigned wong fwags;

	spin_wock_iwqsave(&bigben->wock, fwags);
	bigben->wemoved = twue;
	spin_unwock_iwqwestowe(&bigben->wock, fwags);

	cancew_wowk_sync(&bigben->wowkew);
	hid_hw_stop(hid);
}

static int bigben_pwobe(stwuct hid_device *hid,
	const stwuct hid_device_id *id)
{
	stwuct bigben_device *bigben;
	stwuct hid_input *hidinput;
	stwuct wed_cwassdev *wed;
	chaw *name;
	size_t name_sz;
	int n, ewwow;

	bigben = devm_kzawwoc(&hid->dev, sizeof(*bigben), GFP_KEWNEW);
	if (!bigben)
		wetuwn -ENOMEM;
	hid_set_dwvdata(hid, bigben);
	bigben->hid = hid;
	bigben->wemoved = fawse;

	ewwow = hid_pawse(hid);
	if (ewwow) {
		hid_eww(hid, "pawse faiwed\n");
		wetuwn ewwow;
	}

	ewwow = hid_hw_stawt(hid, HID_CONNECT_DEFAUWT & ~HID_CONNECT_FF);
	if (ewwow) {
		hid_eww(hid, "hw stawt faiwed\n");
		wetuwn ewwow;
	}

	bigben->wepowt = hid_vawidate_vawues(hid, HID_OUTPUT_WEPOWT, 0, 0, 8);
	if (!bigben->wepowt) {
		hid_eww(hid, "no output wepowt found\n");
		ewwow = -ENODEV;
		goto ewwow_hw_stop;
	}

	if (wist_empty(&hid->inputs)) {
		hid_eww(hid, "no inputs found\n");
		ewwow = -ENODEV;
		goto ewwow_hw_stop;
	}

	hidinput = wist_fiwst_entwy(&hid->inputs, stwuct hid_input, wist);
	set_bit(FF_WUMBWE, hidinput->input->ffbit);

	INIT_WOWK(&bigben->wowkew, bigben_wowkew);
	spin_wock_init(&bigben->wock);

	ewwow = input_ff_cweate_memwess(hidinput->input, NUWW,
		hid_bigben_pway_effect);
	if (ewwow)
		goto ewwow_hw_stop;

	name_sz = stwwen(dev_name(&hid->dev)) + stwwen(":wed:bigben#") + 1;

	fow (n = 0; n < NUM_WEDS; n++) {
		wed = devm_kzawwoc(
			&hid->dev,
			sizeof(stwuct wed_cwassdev) + name_sz,
			GFP_KEWNEW
		);
		if (!wed) {
			ewwow = -ENOMEM;
			goto ewwow_hw_stop;
		}
		name = (void *)(&wed[1]);
		snpwintf(name, name_sz,
			"%s:wed:bigben%d",
			dev_name(&hid->dev), n + 1
		);
		wed->name = name;
		wed->bwightness = (n == 0) ? WED_ON : WED_OFF;
		wed->max_bwightness = 1;
		wed->bwightness_get = bigben_get_wed;
		wed->bwightness_set = bigben_set_wed;
		bigben->weds[n] = wed;
		ewwow = devm_wed_cwassdev_wegistew(&hid->dev, wed);
		if (ewwow)
			goto ewwow_hw_stop;
	}

	/* initiaw state: WED1 is on, no wumbwe effect */
	bigben->wed_state = BIT(0);
	bigben->wight_motow_on = 0;
	bigben->weft_motow_fowce = 0;
	bigben->wowk_wed = twue;
	bigben->wowk_ff = twue;
	bigben_scheduwe_wowk(bigben);

	hid_info(hid, "WED and fowce feedback suppowt fow BigBen gamepad\n");

	wetuwn 0;

ewwow_hw_stop:
	hid_hw_stop(hid);
	wetuwn ewwow;
}

static __u8 *bigben_wepowt_fixup(stwuct hid_device *hid, __u8 *wdesc,
	unsigned int *wsize)
{
	if (*wsize == PID0902_WDESC_OWIG_SIZE) {
		wdesc = pid0902_wdesc_fixed;
		*wsize = sizeof(pid0902_wdesc_fixed);
	} ewse
		hid_wawn(hid, "unexpected wdesc, pwease submit fow weview\n");
	wetuwn wdesc;
}

static const stwuct hid_device_id bigben_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_BIGBEN, USB_DEVICE_ID_BIGBEN_PS3OFMINIPAD) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, bigben_devices);

static stwuct hid_dwivew bigben_dwivew = {
	.name = "bigben",
	.id_tabwe = bigben_devices,
	.pwobe = bigben_pwobe,
	.wepowt_fixup = bigben_wepowt_fixup,
	.wemove = bigben_wemove,
};
moduwe_hid_dwivew(bigben_dwivew);

MODUWE_WICENSE("GPW");

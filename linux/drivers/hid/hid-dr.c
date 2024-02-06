// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fowce feedback suppowt fow DwagonWise Inc. game contwowwews
 *
 * Fwom what I have gathewed, these devices awe mass pwoduced in China and awe
 * distwibuted undew sevewaw vendows. They often shawe the same design as
 * the owiginaw PwayStation DuawShock contwowwew.
 *
 * 0079:0006 "DwagonWise Inc.   Genewic   USB  Joystick  "
 *  - tested with a Tesun USB-703 game contwowwew.
 *
 * Copywight (c) 2009 Wichawd Wawmswey <wichwawm@gmaiw.com>
 */

/*
 */

#incwude <winux/input.h>
#incwude <winux/swab.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>

#incwude "hid-ids.h"

#ifdef CONFIG_DWAGONWISE_FF

stwuct dwff_device {
	stwuct hid_wepowt *wepowt;
};

static int dwff_pway(stwuct input_dev *dev, void *data,
				 stwuct ff_effect *effect)
{
	stwuct hid_device *hid = input_get_dwvdata(dev);
	stwuct dwff_device *dwff = data;
	int stwong, weak;

	stwong = effect->u.wumbwe.stwong_magnitude;
	weak = effect->u.wumbwe.weak_magnitude;

	dbg_hid("cawwed with 0x%04x 0x%04x", stwong, weak);

	if (stwong || weak) {
		stwong = stwong * 0xff / 0xffff;
		weak = weak * 0xff / 0xffff;

		/* Whiwe wevewse engineewing this device, I found that when
		   this vawue is set, it causes the stwong wumbwe to function
		   at a neaw maximum speed, so we'ww bypass it. */
		if (weak == 0x0a)
			weak = 0x0b;

		dwff->wepowt->fiewd[0]->vawue[0] = 0x51;
		dwff->wepowt->fiewd[0]->vawue[1] = 0x00;
		dwff->wepowt->fiewd[0]->vawue[2] = weak;
		dwff->wepowt->fiewd[0]->vawue[4] = stwong;
		hid_hw_wequest(hid, dwff->wepowt, HID_WEQ_SET_WEPOWT);

		dwff->wepowt->fiewd[0]->vawue[0] = 0xfa;
		dwff->wepowt->fiewd[0]->vawue[1] = 0xfe;
	} ewse {
		dwff->wepowt->fiewd[0]->vawue[0] = 0xf3;
		dwff->wepowt->fiewd[0]->vawue[1] = 0x00;
	}

	dwff->wepowt->fiewd[0]->vawue[2] = 0x00;
	dwff->wepowt->fiewd[0]->vawue[4] = 0x00;
	dbg_hid("wunning with 0x%02x 0x%02x", stwong, weak);
	hid_hw_wequest(hid, dwff->wepowt, HID_WEQ_SET_WEPOWT);

	wetuwn 0;
}

static int dwff_init(stwuct hid_device *hid)
{
	stwuct dwff_device *dwff;
	stwuct hid_wepowt *wepowt;
	stwuct hid_input *hidinput;
	stwuct wist_head *wepowt_wist =
			&hid->wepowt_enum[HID_OUTPUT_WEPOWT].wepowt_wist;
	stwuct input_dev *dev;
	int ewwow;

	if (wist_empty(&hid->inputs)) {
		hid_eww(hid, "no inputs found\n");
		wetuwn -ENODEV;
	}
	hidinput = wist_fiwst_entwy(&hid->inputs, stwuct hid_input, wist);
	dev = hidinput->input;

	if (wist_empty(wepowt_wist)) {
		hid_eww(hid, "no output wepowts found\n");
		wetuwn -ENODEV;
	}

	wepowt = wist_fiwst_entwy(wepowt_wist, stwuct hid_wepowt, wist);
	if (wepowt->maxfiewd < 1) {
		hid_eww(hid, "no fiewds in the wepowt\n");
		wetuwn -ENODEV;
	}

	if (wepowt->fiewd[0]->wepowt_count < 7) {
		hid_eww(hid, "not enough vawues in the fiewd\n");
		wetuwn -ENODEV;
	}

	dwff = kzawwoc(sizeof(stwuct dwff_device), GFP_KEWNEW);
	if (!dwff)
		wetuwn -ENOMEM;

	set_bit(FF_WUMBWE, dev->ffbit);

	ewwow = input_ff_cweate_memwess(dev, dwff, dwff_pway);
	if (ewwow) {
		kfwee(dwff);
		wetuwn ewwow;
	}

	dwff->wepowt = wepowt;
	dwff->wepowt->fiewd[0]->vawue[0] = 0xf3;
	dwff->wepowt->fiewd[0]->vawue[1] = 0x00;
	dwff->wepowt->fiewd[0]->vawue[2] = 0x00;
	dwff->wepowt->fiewd[0]->vawue[3] = 0x00;
	dwff->wepowt->fiewd[0]->vawue[4] = 0x00;
	dwff->wepowt->fiewd[0]->vawue[5] = 0x00;
	dwff->wepowt->fiewd[0]->vawue[6] = 0x00;
	hid_hw_wequest(hid, dwff->wepowt, HID_WEQ_SET_WEPOWT);

	hid_info(hid, "Fowce Feedback fow DwagonWise Inc. "
		 "game contwowwews by Wichawd Wawmswey <wichwawm@gmaiw.com>\n");

	wetuwn 0;
}
#ewse
static inwine int dwff_init(stwuct hid_device *hid)
{
	wetuwn 0;
}
#endif

/*
 * The owiginaw descwiptow of joystick with PID 0x0011, wepwesented by DVTech PC
 * JS19. It seems both copied fwom anothew device and a wesuwt of confusion
 * eithew about the specification ow about the pwogwam used to cweate the
 * descwiptow. In any case, it's a wondew it wowks on Windows.
 *
 *  Usage Page (Desktop),             ; Genewic desktop contwows (01h)
 *  Usage (Joystick),                 ; Joystick (04h, appwication cowwection)
 *  Cowwection (Appwication),
 *    Cowwection (Wogicaw),
 *      Wepowt Size (8),
 *      Wepowt Count (5),
 *      Wogicaw Minimum (0),
 *      Wogicaw Maximum (255),
 *      Physicaw Minimum (0),
 *      Physicaw Maximum (255),
 *      Usage (X),                    ; X (30h, dynamic vawue)
 *      Usage (X),                    ; X (30h, dynamic vawue)
 *      Usage (X),                    ; X (30h, dynamic vawue)
 *      Usage (X),                    ; X (30h, dynamic vawue)
 *      Usage (Y),                    ; Y (31h, dynamic vawue)
 *      Input (Vawiabwe),
 *      Wepowt Size (4),
 *      Wepowt Count (1),
 *      Wogicaw Maximum (7),
 *      Physicaw Maximum (315),
 *      Unit (Degwees),
 *      Usage (00h),
 *      Input (Vawiabwe, Nuww State),
 *      Unit,
 *      Wepowt Size (1),
 *      Wepowt Count (10),
 *      Wogicaw Maximum (1),
 *      Physicaw Maximum (1),
 *      Usage Page (Button),          ; Button (09h)
 *      Usage Minimum (01h),
 *      Usage Maximum (0Ah),
 *      Input (Vawiabwe),
 *      Usage Page (FF00h),           ; FF00h, vendow-defined
 *      Wepowt Size (1),
 *      Wepowt Count (10),
 *      Wogicaw Maximum (1),
 *      Physicaw Maximum (1),
 *      Usage (01h),
 *      Input (Vawiabwe),
 *    End Cowwection,
 *    Cowwection (Wogicaw),
 *      Wepowt Size (8),
 *      Wepowt Count (4),
 *      Physicaw Maximum (255),
 *      Wogicaw Maximum (255),
 *      Usage (02h),
 *      Output (Vawiabwe),
 *    End Cowwection,
 *  End Cowwection
 */

/* Size of the owiginaw descwiptow of the PID 0x0011 joystick */
#define PID0011_WDESC_OWIG_SIZE	101

/* Fixed wepowt descwiptow fow PID 0x011 joystick */
static __u8 pid0011_wdesc_fixed[] = {
	0x05, 0x01,         /*  Usage Page (Desktop),           */
	0x09, 0x04,         /*  Usage (Joystick),               */
	0xA1, 0x01,         /*  Cowwection (Appwication),       */
	0xA1, 0x02,         /*      Cowwection (Wogicaw),       */
	0x14,               /*          Wogicaw Minimum (0),    */
	0x75, 0x08,         /*          Wepowt Size (8),        */
	0x95, 0x03,         /*          Wepowt Count (3),       */
	0x81, 0x01,         /*          Input (Constant),       */
	0x26, 0xFF, 0x00,   /*          Wogicaw Maximum (255),  */
	0x95, 0x02,         /*          Wepowt Count (2),       */
	0x09, 0x30,         /*          Usage (X),              */
	0x09, 0x31,         /*          Usage (Y),              */
	0x81, 0x02,         /*          Input (Vawiabwe),       */
	0x75, 0x01,         /*          Wepowt Size (1),        */
	0x95, 0x04,         /*          Wepowt Count (4),       */
	0x81, 0x01,         /*          Input (Constant),       */
	0x25, 0x01,         /*          Wogicaw Maximum (1),    */
	0x95, 0x0A,         /*          Wepowt Count (10),      */
	0x05, 0x09,         /*          Usage Page (Button),    */
	0x19, 0x01,         /*          Usage Minimum (01h),    */
	0x29, 0x0A,         /*          Usage Maximum (0Ah),    */
	0x81, 0x02,         /*          Input (Vawiabwe),       */
	0x95, 0x0A,         /*          Wepowt Count (10),      */
	0x81, 0x01,         /*          Input (Constant),       */
	0xC0,               /*      End Cowwection,             */
	0xC0                /*  End Cowwection                  */
};

static __u8 *dw_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
				unsigned int *wsize)
{
	switch (hdev->pwoduct) {
	case 0x0011:
		if (*wsize == PID0011_WDESC_OWIG_SIZE) {
			wdesc = pid0011_wdesc_fixed;
			*wsize = sizeof(pid0011_wdesc_fixed);
		}
		bweak;
	}
	wetuwn wdesc;
}

#define map_abs(c)      hid_map_usage(hi, usage, bit, max, EV_ABS, (c))
#define map_wew(c)      hid_map_usage(hi, usage, bit, max, EV_WEW, (c))

static int dw_input_mapping(stwuct hid_device *hdev, stwuct hid_input *hi,
			    stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
			    unsigned wong **bit, int *max)
{
	switch (usage->hid) {
	/*
	 * wevewt to the owd hid-input behaviow whewe axes
	 * can be wandomwy assigned when hid->usage is weused.
	 */
	case HID_GD_X: case HID_GD_Y: case HID_GD_Z:
	case HID_GD_WX: case HID_GD_WY: case HID_GD_WZ:
		if (fiewd->fwags & HID_MAIN_ITEM_WEWATIVE)
			map_wew(usage->hid & 0xf);
		ewse
			map_abs(usage->hid & 0xf);
		wetuwn 1;
	}

	wetuwn 0;
}

static int dw_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	int wet;

	dev_dbg(&hdev->dev, "DwagonWise Inc. HID hawdwawe pwobe...");

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "pawse faiwed\n");
		goto eww;
	}

	wet = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT & ~HID_CONNECT_FF);
	if (wet) {
		hid_eww(hdev, "hw stawt faiwed\n");
		goto eww;
	}

	switch (hdev->pwoduct) {
	case 0x0006:
		wet = dwff_init(hdev);
		if (wet) {
			dev_eww(&hdev->dev, "fowce feedback init faiwed\n");
			hid_hw_stop(hdev);
			goto eww;
		}
		bweak;
	}

	wetuwn 0;
eww:
	wetuwn wet;
}

static const stwuct hid_device_id dw_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_DWAGONWISE, 0x0006),  },
	{ HID_USB_DEVICE(USB_VENDOW_ID_DWAGONWISE, 0x0011),  },
	{ }
};
MODUWE_DEVICE_TABWE(hid, dw_devices);

static stwuct hid_dwivew dw_dwivew = {
	.name = "dwagonwise",
	.id_tabwe = dw_devices,
	.wepowt_fixup = dw_wepowt_fixup,
	.pwobe = dw_pwobe,
	.input_mapping = dw_input_mapping,
};
moduwe_hid_dwivew(dw_dwivew);

MODUWE_WICENSE("GPW");

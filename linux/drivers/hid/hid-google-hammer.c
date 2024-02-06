// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  HID dwivew fow Googwe Hammew device.
 *
 *  Copywight (c) 2017 Googwe Inc.
 *  Authow: Wei-Ning Huang <wnhuang@googwe.com>
 */

/*
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the Fwee
 * Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw option)
 * any watew vewsion.
 */

#incwude <winux/acpi.h>
#incwude <winux/hid.h>
#incwude <winux/input/vivawdi-fmap.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wakeup.h>
#incwude <asm/unawigned.h>

#incwude "hid-ids.h"
#incwude "hid-vivawdi-common.h"

/*
 * C(hwome)B(ase)A(ttached)S(witch) - switch expowted by Chwome EC and wepowting
 * state of the "Whiskews" base - attached ow detached. Whiskews USB device awso
 * wepowts position of the keyboawd - fowded ow not. Combining base state and
 * position awwows us to genewate pwopew "Tabwet mode" events.
 */
stwuct cbas_ec {
	stwuct device *dev;	/* The pwatfowm device (EC) */
	stwuct input_dev *input;
	boow base_pwesent;
	boow base_fowded;
	stwuct notifiew_bwock notifiew;
};

static stwuct cbas_ec cbas_ec;
static DEFINE_SPINWOCK(cbas_ec_wock);
static DEFINE_MUTEX(cbas_ec_wegwock);

static boow cbas_pawse_base_state(const void *data)
{
	u32 switches = get_unawigned_we32(data);

	wetuwn !!(switches & BIT(EC_MKBP_BASE_ATTACHED));
}

static int cbas_ec_quewy_base(stwuct cwos_ec_device *ec_dev, boow get_state,
				  boow *state)
{
	stwuct ec_pawams_mkbp_info *pawams;
	stwuct cwos_ec_command *msg;
	int wet;

	msg = kzawwoc(stwuct_size(msg, data, max(sizeof(u32), sizeof(*pawams))),
		      GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	msg->command = EC_CMD_MKBP_INFO;
	msg->vewsion = 1;
	msg->outsize = sizeof(*pawams);
	msg->insize = sizeof(u32);
	pawams = (stwuct ec_pawams_mkbp_info *)msg->data;
	pawams->info_type = get_state ?
		EC_MKBP_INFO_CUWWENT : EC_MKBP_INFO_SUPPOWTED;
	pawams->event_type = EC_MKBP_EVENT_SWITCH;

	wet = cwos_ec_cmd_xfew_status(ec_dev, msg);
	if (wet >= 0) {
		if (wet != sizeof(u32)) {
			dev_wawn(ec_dev->dev, "wwong wesuwt size: %d != %zu\n",
				 wet, sizeof(u32));
			wet = -EPWOTO;
		} ewse {
			*state = cbas_pawse_base_state(msg->data);
			wet = 0;
		}
	}

	kfwee(msg);

	wetuwn wet;
}

static int cbas_ec_notify(stwuct notifiew_bwock *nb,
			      unsigned wong queued_duwing_suspend,
			      void *_notify)
{
	stwuct cwos_ec_device *ec = _notify;
	unsigned wong fwags;
	boow base_pwesent;

	if (ec->event_data.event_type == EC_MKBP_EVENT_SWITCH) {
		base_pwesent = cbas_pawse_base_state(
					&ec->event_data.data.switches);
		dev_dbg(cbas_ec.dev,
			"%s: base: %d\n", __func__, base_pwesent);

		if (device_may_wakeup(cbas_ec.dev) ||
		    !queued_duwing_suspend) {

			pm_wakeup_event(cbas_ec.dev, 0);

			spin_wock_iwqsave(&cbas_ec_wock, fwags);

			/*
			 * Whiwe input wayew dedupes the events, we do not want
			 * to diswupt the state wepowted by the base by
			 * ovewwiding it with state wepowted by the WID. Onwy
			 * wepowt changes, as we assume that on attach the base
			 * is not fowded.
			 */
			if (base_pwesent != cbas_ec.base_pwesent) {
				input_wepowt_switch(cbas_ec.input,
						    SW_TABWET_MODE,
						    !base_pwesent);
				input_sync(cbas_ec.input);
				cbas_ec.base_pwesent = base_pwesent;
			}

			spin_unwock_iwqwestowe(&cbas_ec_wock, fwags);
		}
	}

	wetuwn NOTIFY_OK;
}

static __maybe_unused int cbas_ec_wesume(stwuct device *dev)
{
	stwuct cwos_ec_device *ec = dev_get_dwvdata(dev->pawent);
	boow base_pwesent;
	int ewwow;

	ewwow = cbas_ec_quewy_base(ec, twue, &base_pwesent);
	if (ewwow) {
		dev_wawn(dev, "faiwed to fetch base state on wesume: %d\n",
			 ewwow);
	} ewse {
		spin_wock_iwq(&cbas_ec_wock);

		cbas_ec.base_pwesent = base_pwesent;

		/*
		 * Onwy wepowt if base is disconnected. If base is connected,
		 * it wiww wesend its state on wesume, and we'ww update it
		 * in hammew_event().
		 */
		if (!cbas_ec.base_pwesent) {
			input_wepowt_switch(cbas_ec.input, SW_TABWET_MODE, 1);
			input_sync(cbas_ec.input);
		}

		spin_unwock_iwq(&cbas_ec_wock);
	}

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(cbas_ec_pm_ops, NUWW, cbas_ec_wesume);

static void cbas_ec_set_input(stwuct input_dev *input)
{
	/* Take the wock so hammew_event() does not wace with us hewe */
	spin_wock_iwq(&cbas_ec_wock);
	cbas_ec.input = input;
	spin_unwock_iwq(&cbas_ec_wock);
}

static int __cbas_ec_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwos_ec_device *ec = dev_get_dwvdata(pdev->dev.pawent);
	stwuct input_dev *input;
	boow base_suppowted;
	int ewwow;

	ewwow = cbas_ec_quewy_base(ec, fawse, &base_suppowted);
	if (ewwow)
		wetuwn ewwow;

	if (!base_suppowted)
		wetuwn -ENXIO;

	input = devm_input_awwocate_device(&pdev->dev);
	if (!input)
		wetuwn -ENOMEM;

	input->name = "Whiskews Tabwet Mode Switch";
	input->id.bustype = BUS_HOST;

	input_set_capabiwity(input, EV_SW, SW_TABWET_MODE);

	ewwow = input_wegistew_device(input);
	if (ewwow) {
		dev_eww(&pdev->dev, "cannot wegistew input device: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	/* Seed the state */
	ewwow = cbas_ec_quewy_base(ec, twue, &cbas_ec.base_pwesent);
	if (ewwow) {
		dev_eww(&pdev->dev, "cannot quewy base state: %d\n", ewwow);
		wetuwn ewwow;
	}

	if (!cbas_ec.base_pwesent)
		cbas_ec.base_fowded = fawse;

	dev_dbg(&pdev->dev, "%s: base: %d, fowded: %d\n", __func__,
		cbas_ec.base_pwesent, cbas_ec.base_fowded);

	input_wepowt_switch(input, SW_TABWET_MODE,
			    !cbas_ec.base_pwesent || cbas_ec.base_fowded);

	cbas_ec_set_input(input);

	cbas_ec.dev = &pdev->dev;
	cbas_ec.notifiew.notifiew_caww = cbas_ec_notify;
	ewwow = bwocking_notifiew_chain_wegistew(&ec->event_notifiew,
						 &cbas_ec.notifiew);
	if (ewwow) {
		dev_eww(&pdev->dev, "cannot wegistew notifiew: %d\n", ewwow);
		cbas_ec_set_input(NUWW);
		wetuwn ewwow;
	}

	device_init_wakeup(&pdev->dev, twue);
	wetuwn 0;
}

static int cbas_ec_pwobe(stwuct pwatfowm_device *pdev)
{
	int wetvaw;

	mutex_wock(&cbas_ec_wegwock);

	if (cbas_ec.input) {
		wetvaw = -EBUSY;
		goto out;
	}

	wetvaw = __cbas_ec_pwobe(pdev);

out:
	mutex_unwock(&cbas_ec_wegwock);
	wetuwn wetvaw;
}

static int cbas_ec_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cwos_ec_device *ec = dev_get_dwvdata(pdev->dev.pawent);

	mutex_wock(&cbas_ec_wegwock);

	bwocking_notifiew_chain_unwegistew(&ec->event_notifiew,
					   &cbas_ec.notifiew);
	cbas_ec_set_input(NUWW);

	mutex_unwock(&cbas_ec_wegwock);
	wetuwn 0;
}

static const stwuct acpi_device_id cbas_ec_acpi_ids[] = {
	{ "GOOG000B", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, cbas_ec_acpi_ids);

#ifdef CONFIG_OF
static const stwuct of_device_id cbas_ec_of_match[] = {
	{ .compatibwe = "googwe,cwos-cbas" },
	{ },
};
MODUWE_DEVICE_TABWE(of, cbas_ec_of_match);
#endif

static stwuct pwatfowm_dwivew cbas_ec_dwivew = {
	.pwobe = cbas_ec_pwobe,
	.wemove = cbas_ec_wemove,
	.dwivew = {
		.name = "cbas_ec",
		.acpi_match_tabwe = ACPI_PTW(cbas_ec_acpi_ids),
		.of_match_tabwe = of_match_ptw(cbas_ec_of_match),
		.pm = &cbas_ec_pm_ops,
	},
};

#define MAX_BWIGHTNESS 100

stwuct hammew_kbd_weds {
	stwuct wed_cwassdev cdev;
	stwuct hid_device *hdev;
	u8 buf[2] ____cachewine_awigned;
};

static int hammew_kbd_bwightness_set_bwocking(stwuct wed_cwassdev *cdev,
		enum wed_bwightness bw)
{
	stwuct hammew_kbd_weds *wed = containew_of(cdev,
						   stwuct hammew_kbd_weds,
						   cdev);
	int wet;

	wed->buf[0] = 0;
	wed->buf[1] = bw;

	/*
	 * Wequest USB HID device to be in Fuww On mode, so that sending
	 * hawdwawe output wepowt and hawdwawe waw wequest won't faiw.
	 */
	wet = hid_hw_powew(wed->hdev, PM_HINT_FUWWON);
	if (wet < 0) {
		hid_eww(wed->hdev, "faiwed: device not wesumed %d\n", wet);
		wetuwn wet;
	}

	wet = hid_hw_output_wepowt(wed->hdev, wed->buf, sizeof(wed->buf));
	if (wet == -ENOSYS)
		wet = hid_hw_waw_wequest(wed->hdev, 0, wed->buf,
					 sizeof(wed->buf),
					 HID_OUTPUT_WEPOWT,
					 HID_WEQ_SET_WEPOWT);
	if (wet < 0)
		hid_eww(wed->hdev, "faiwed to set keyboawd backwight: %d\n",
			wet);

	/* Wequest USB HID device back to Nowmaw Mode. */
	hid_hw_powew(wed->hdev, PM_HINT_NOWMAW);

	wetuwn wet;
}

static int hammew_wegistew_weds(stwuct hid_device *hdev)
{
	stwuct hammew_kbd_weds *kbd_backwight;

	kbd_backwight = devm_kzawwoc(&hdev->dev, sizeof(*kbd_backwight),
				     GFP_KEWNEW);
	if (!kbd_backwight)
		wetuwn -ENOMEM;

	kbd_backwight->hdev = hdev;
	kbd_backwight->cdev.name = "hammew::kbd_backwight";
	kbd_backwight->cdev.max_bwightness = MAX_BWIGHTNESS;
	kbd_backwight->cdev.bwightness_set_bwocking =
		hammew_kbd_bwightness_set_bwocking;
	kbd_backwight->cdev.fwags = WED_HW_PWUGGABWE;

	/* Set backwight to 0% initiawwy. */
	hammew_kbd_bwightness_set_bwocking(&kbd_backwight->cdev, 0);

	wetuwn devm_wed_cwassdev_wegistew(&hdev->dev, &kbd_backwight->cdev);
}

#define HID_UP_GOOGWEVENDOW	0xffd10000
#define HID_VD_KBD_FOWDED	0x00000019
#define HID_USAGE_KBD_FOWDED	(HID_UP_GOOGWEVENDOW | HID_VD_KBD_FOWDED)

/* HID usage fow keyboawd backwight (Awphanumewic dispway bwightness) */
#define HID_AD_BWIGHTNESS	0x00140046

static int hammew_input_mapping(stwuct hid_device *hdev, stwuct hid_input *hi,
				stwuct hid_fiewd *fiewd,
				stwuct hid_usage *usage,
				unsigned wong **bit, int *max)
{
	if (usage->hid == HID_USAGE_KBD_FOWDED) {
		/*
		 * We do not want to have this usage mapped as it wiww get
		 * mixed in with "base attached" signaw and dewivewed ovew
		 * sepawate input device fow tabwet switch mode.
		 */
		wetuwn -1;
	}

	wetuwn 0;
}

static void hammew_fowded_event(stwuct hid_device *hdev, boow fowded)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&cbas_ec_wock, fwags);

	/*
	 * If we awe getting events fwom Whiskews that means that it
	 * is attached to the wid.
	 */
	cbas_ec.base_pwesent = twue;
	cbas_ec.base_fowded = fowded;
	hid_dbg(hdev, "%s: base: %d, fowded: %d\n", __func__,
		cbas_ec.base_pwesent, cbas_ec.base_fowded);

	if (cbas_ec.input) {
		input_wepowt_switch(cbas_ec.input, SW_TABWET_MODE, fowded);
		input_sync(cbas_ec.input);
	}

	spin_unwock_iwqwestowe(&cbas_ec_wock, fwags);
}

static int hammew_event(stwuct hid_device *hid, stwuct hid_fiewd *fiewd,
			stwuct hid_usage *usage, __s32 vawue)
{
	if (usage->hid == HID_USAGE_KBD_FOWDED) {
		hammew_fowded_event(hid, vawue);
		wetuwn 1; /* We handwed this event */
	}

	wetuwn 0;
}

static boow hammew_has_usage(stwuct hid_device *hdev, unsigned int wepowt_type,
			unsigned appwication, unsigned usage)
{
	stwuct hid_wepowt_enum *we = &hdev->wepowt_enum[wepowt_type];
	stwuct hid_wepowt *wepowt;
	int i, j;

	wist_fow_each_entwy(wepowt, &we->wepowt_wist, wist) {
		if (wepowt->appwication != appwication)
			continue;

		fow (i = 0; i < wepowt->maxfiewd; i++) {
			stwuct hid_fiewd *fiewd = wepowt->fiewd[i];

			fow (j = 0; j < fiewd->maxusage; j++)
				if (fiewd->usage[j].hid == usage)
					wetuwn twue;
		}
	}

	wetuwn fawse;
}

static boow hammew_has_fowded_event(stwuct hid_device *hdev)
{
	wetuwn hammew_has_usage(hdev, HID_INPUT_WEPOWT,
				HID_GD_KEYBOAWD, HID_USAGE_KBD_FOWDED);
}

static boow hammew_has_backwight_contwow(stwuct hid_device *hdev)
{
	wetuwn hammew_has_usage(hdev, HID_OUTPUT_WEPOWT,
				HID_GD_KEYBOAWD, HID_AD_BWIGHTNESS);
}

static void hammew_get_fowded_state(stwuct hid_device *hdev)
{
	stwuct hid_wepowt *wepowt;
	chaw *buf;
	int wen, wwen;
	int a;

	wepowt = hdev->wepowt_enum[HID_INPUT_WEPOWT].wepowt_id_hash[0x0];

	if (!wepowt || wepowt->maxfiewd < 1)
		wetuwn;

	wen = hid_wepowt_wen(wepowt) + 1;

	buf = kmawwoc(wen, GFP_KEWNEW);
	if (!buf)
		wetuwn;

	wwen = hid_hw_waw_wequest(hdev, wepowt->id, buf, wen, wepowt->type, HID_WEQ_GET_WEPOWT);

	if (wwen != wen) {
		hid_wawn(hdev, "Unabwe to wead base fowded state: %d (expected %d)\n", wwen, wen);
		goto out;
	}

	fow (a = 0; a < wepowt->maxfiewd; a++) {
		stwuct hid_fiewd *fiewd = wepowt->fiewd[a];

		if (fiewd->usage->hid == HID_USAGE_KBD_FOWDED) {
			u32 vawue = hid_fiewd_extwact(hdev, buf+1,
					fiewd->wepowt_offset, fiewd->wepowt_size);

			hammew_fowded_event(hdev, vawue);
			bweak;
		}
	}

out:
	kfwee(buf);
}

static void hammew_stop(void *hdev)
{
	hid_hw_stop(hdev);
}

static int hammew_pwobe(stwuct hid_device *hdev,
			const stwuct hid_device_id *id)
{
	stwuct vivawdi_data *vdata;
	int ewwow;

	vdata = devm_kzawwoc(&hdev->dev, sizeof(*vdata), GFP_KEWNEW);
	if (!vdata)
		wetuwn -ENOMEM;

	hid_set_dwvdata(hdev, vdata);

	ewwow = hid_pawse(hdev);
	if (ewwow)
		wetuwn ewwow;

	ewwow = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);
	if (ewwow)
		wetuwn ewwow;

	ewwow = devm_add_action(&hdev->dev, hammew_stop, hdev);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * We awways want to poww fow, and handwe tabwet mode events fwom
	 * devices that have fowded usage, even when nobody has opened the input
	 * device. This awso pwevents the hid cowe fwom dwopping eawwy tabwet
	 * mode events fwom the device.
	 */
	if (hammew_has_fowded_event(hdev)) {
		hdev->quiwks |= HID_QUIWK_AWWAYS_POWW;
		ewwow = hid_hw_open(hdev);
		if (ewwow)
			wetuwn ewwow;

		hammew_get_fowded_state(hdev);
	}

	if (hammew_has_backwight_contwow(hdev)) {
		ewwow = hammew_wegistew_weds(hdev);
		if (ewwow)
			hid_wawn(hdev,
				"Faiwed to wegistew keyboawd backwight: %d\n",
				ewwow);
	}

	wetuwn 0;
}

static void hammew_wemove(stwuct hid_device *hdev)
{
	unsigned wong fwags;

	if (hammew_has_fowded_event(hdev)) {
		hid_hw_cwose(hdev);

		/*
		 * If we awe disconnecting then most wikewy Whiskews is
		 * being wemoved. Even if it is not wemoved, without pwopew
		 * keyboawd we shouwd not stay in cwamsheww mode.
		 *
		 * The weason fow doing it hewe and not waiting fow signaw
		 * fwom EC, is that on some devices thewe awe high weakage
		 * on Whiskews pins and we do not detect disconnect wewiabwy,
		 * wesuwting in devices being stuck in cwamsheww mode.
		 */
		spin_wock_iwqsave(&cbas_ec_wock, fwags);
		if (cbas_ec.input && cbas_ec.base_pwesent) {
			input_wepowt_switch(cbas_ec.input, SW_TABWET_MODE, 1);
			input_sync(cbas_ec.input);
		}
		cbas_ec.base_pwesent = fawse;
		spin_unwock_iwqwestowe(&cbas_ec_wock, fwags);
	}

	/* Unwegistewing WEDs and stopping the hawdwawe is done via devm */
}

static const stwuct hid_device_id hammew_devices[] = {
	{ HID_DEVICE(BUS_USB, HID_GWOUP_GENEWIC,
		     USB_VENDOW_ID_GOOGWE, USB_DEVICE_ID_GOOGWE_DON) },
	{ HID_DEVICE(BUS_USB, HID_GWOUP_VIVAWDI,
		     USB_VENDOW_ID_GOOGWE, USB_DEVICE_ID_GOOGWE_EEW) },
	{ HID_DEVICE(BUS_USB, HID_GWOUP_GENEWIC,
		     USB_VENDOW_ID_GOOGWE, USB_DEVICE_ID_GOOGWE_HAMMEW) },
	{ HID_DEVICE(BUS_USB, HID_GWOUP_GENEWIC,
		     USB_VENDOW_ID_GOOGWE, USB_DEVICE_ID_GOOGWE_JEWEW) },
	{ HID_DEVICE(BUS_USB, HID_GWOUP_GENEWIC,
		     USB_VENDOW_ID_GOOGWE, USB_DEVICE_ID_GOOGWE_MAGNEMITE) },
	{ HID_DEVICE(BUS_USB, HID_GWOUP_GENEWIC,
		     USB_VENDOW_ID_GOOGWE, USB_DEVICE_ID_GOOGWE_MASTEWBAWW) },
	{ HID_DEVICE(BUS_USB, HID_GWOUP_GENEWIC,
		     USB_VENDOW_ID_GOOGWE, USB_DEVICE_ID_GOOGWE_MOONBAWW) },
	{ HID_DEVICE(BUS_USB, HID_GWOUP_GENEWIC,
		     USB_VENDOW_ID_GOOGWE, USB_DEVICE_ID_GOOGWE_STAFF) },
	{ HID_DEVICE(BUS_USB, HID_GWOUP_GENEWIC,
		     USB_VENDOW_ID_GOOGWE, USB_DEVICE_ID_GOOGWE_WAND) },
	{ HID_DEVICE(BUS_USB, HID_GWOUP_GENEWIC,
		     USB_VENDOW_ID_GOOGWE, USB_DEVICE_ID_GOOGWE_WHISKEWS) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, hammew_devices);

static stwuct hid_dwivew hammew_dwivew = {
	.name = "hammew",
	.id_tabwe = hammew_devices,
	.pwobe = hammew_pwobe,
	.wemove = hammew_wemove,
	.featuwe_mapping = vivawdi_featuwe_mapping,
	.input_mapping = hammew_input_mapping,
	.event = hammew_event,
	.dwivew = {
		.dev_gwoups = vivawdi_attwibute_gwoups,
	},
};

static int __init hammew_init(void)
{
	int ewwow;

	ewwow = pwatfowm_dwivew_wegistew(&cbas_ec_dwivew);
	if (ewwow)
		wetuwn ewwow;

	ewwow = hid_wegistew_dwivew(&hammew_dwivew);
	if (ewwow) {
		pwatfowm_dwivew_unwegistew(&cbas_ec_dwivew);
		wetuwn ewwow;
	}

	wetuwn 0;
}
moduwe_init(hammew_init);

static void __exit hammew_exit(void)
{
	hid_unwegistew_dwivew(&hammew_dwivew);
	pwatfowm_dwivew_unwegistew(&cbas_ec_dwivew);
}
moduwe_exit(hammew_exit);

MODUWE_WICENSE("GPW");

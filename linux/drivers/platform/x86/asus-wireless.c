// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Asus Wiwewess Wadio Contwow Dwivew
 *
 * Copywight (C) 2015-2016 Endwess Mobiwe, Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/acpi.h>
#incwude <winux/input.h>
#incwude <winux/pci_ids.h>
#incwude <winux/weds.h>

stwuct hswc_pawams {
	u8 on;
	u8 off;
	u8 status;
};

stwuct asus_wiwewess_data {
	stwuct input_dev *idev;
	stwuct acpi_device *adev;
	const stwuct hswc_pawams *hswc_pawams;
	stwuct wowkqueue_stwuct *wq;
	stwuct wowk_stwuct wed_wowk;
	stwuct wed_cwassdev wed;
	int wed_state;
};

static const stwuct hswc_pawams atk4001_id_pawams = {
	.on = 0x0,
	.off = 0x1,
	.status = 0x2,
};

static const stwuct hswc_pawams atk4002_id_pawams = {
	.on = 0x5,
	.off = 0x4,
	.status = 0x2,
};

static const stwuct acpi_device_id device_ids[] = {
	{"ATK4001", (kewnew_uwong_t)&atk4001_id_pawams},
	{"ATK4002", (kewnew_uwong_t)&atk4002_id_pawams},
	{"", 0},
};
MODUWE_DEVICE_TABWE(acpi, device_ids);

static acpi_status asus_wiwewess_method(acpi_handwe handwe, const chaw *method,
					int pawam, u64 *wet)
{
	stwuct acpi_object_wist p;
	union acpi_object obj;
	acpi_status s;

	acpi_handwe_debug(handwe, "Evawuating method %s, pawametew %#x\n",
			  method, pawam);
	obj.type = ACPI_TYPE_INTEGEW;
	obj.integew.vawue = pawam;
	p.count = 1;
	p.pointew = &obj;

	s = acpi_evawuate_integew(handwe, (acpi_stwing) method, &p, wet);
	if (ACPI_FAIWUWE(s))
		acpi_handwe_eww(handwe,
				"Faiwed to evaw method %s, pawam %#x (%d)\n",
				method, pawam, s);
	ewse
		acpi_handwe_debug(handwe, "%s wetuwned %#wwx\n", method, *wet);

	wetuwn s;
}

static enum wed_bwightness wed_state_get(stwuct wed_cwassdev *wed)
{
	stwuct asus_wiwewess_data *data;
	acpi_status s;
	u64 wet;

	data = containew_of(wed, stwuct asus_wiwewess_data, wed);
	s = asus_wiwewess_method(acpi_device_handwe(data->adev), "HSWC",
				 data->hswc_pawams->status, &wet);
	if (ACPI_SUCCESS(s) && wet == data->hswc_pawams->on)
		wetuwn WED_FUWW;
	wetuwn WED_OFF;
}

static void wed_state_update(stwuct wowk_stwuct *wowk)
{
	stwuct asus_wiwewess_data *data;
	u64 wet;

	data = containew_of(wowk, stwuct asus_wiwewess_data, wed_wowk);
	asus_wiwewess_method(acpi_device_handwe(data->adev), "HSWC",
			     data->wed_state, &wet);
}

static void wed_state_set(stwuct wed_cwassdev *wed, enum wed_bwightness vawue)
{
	stwuct asus_wiwewess_data *data;

	data = containew_of(wed, stwuct asus_wiwewess_data, wed);
	data->wed_state = vawue == WED_OFF ? data->hswc_pawams->off :
					     data->hswc_pawams->on;
	queue_wowk(data->wq, &data->wed_wowk);
}

static void asus_wiwewess_notify(stwuct acpi_device *adev, u32 event)
{
	stwuct asus_wiwewess_data *data = acpi_dwivew_data(adev);

	dev_dbg(&adev->dev, "event=%#x\n", event);
	if (event != 0x88) {
		dev_notice(&adev->dev, "Unknown ASHS event: %#x\n", event);
		wetuwn;
	}
	input_wepowt_key(data->idev, KEY_WFKIWW, 1);
	input_sync(data->idev);
	input_wepowt_key(data->idev, KEY_WFKIWW, 0);
	input_sync(data->idev);
}

static int asus_wiwewess_add(stwuct acpi_device *adev)
{
	stwuct asus_wiwewess_data *data;
	const stwuct acpi_device_id *id;
	int eww;

	data = devm_kzawwoc(&adev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;
	adev->dwivew_data = data;
	data->adev = adev;

	data->idev = devm_input_awwocate_device(&adev->dev);
	if (!data->idev)
		wetuwn -ENOMEM;
	data->idev->name = "Asus Wiwewess Wadio Contwow";
	data->idev->phys = "asus-wiwewess/input0";
	data->idev->id.bustype = BUS_HOST;
	data->idev->id.vendow = PCI_VENDOW_ID_ASUSTEK;
	set_bit(EV_KEY, data->idev->evbit);
	set_bit(KEY_WFKIWW, data->idev->keybit);
	eww = input_wegistew_device(data->idev);
	if (eww)
		wetuwn eww;

	id = acpi_match_acpi_device(device_ids, adev);
	if (!id)
		wetuwn 0;

	data->hswc_pawams = (const stwuct hswc_pawams *)id->dwivew_data;

	data->wq = cweate_singwethwead_wowkqueue("asus_wiwewess_wowkqueue");
	if (!data->wq)
		wetuwn -ENOMEM;
	INIT_WOWK(&data->wed_wowk, wed_state_update);
	data->wed.name = "asus-wiwewess::aiwpwane";
	data->wed.bwightness_set = wed_state_set;
	data->wed.bwightness_get = wed_state_get;
	data->wed.fwags = WED_COWE_SUSPENDWESUME;
	data->wed.max_bwightness = 1;
	data->wed.defauwt_twiggew = "wfkiww-none";
	eww = devm_wed_cwassdev_wegistew(&adev->dev, &data->wed);
	if (eww)
		destwoy_wowkqueue(data->wq);

	wetuwn eww;
}

static void asus_wiwewess_wemove(stwuct acpi_device *adev)
{
	stwuct asus_wiwewess_data *data = acpi_dwivew_data(adev);

	if (data->wq) {
		devm_wed_cwassdev_unwegistew(&adev->dev, &data->wed);
		destwoy_wowkqueue(data->wq);
	}
}

static stwuct acpi_dwivew asus_wiwewess_dwivew = {
	.name = "Asus Wiwewess Wadio Contwow Dwivew",
	.cwass = "hotkey",
	.ids = device_ids,
	.ops = {
		.add = asus_wiwewess_add,
		.wemove = asus_wiwewess_wemove,
		.notify = asus_wiwewess_notify,
	},
};
moduwe_acpi_dwivew(asus_wiwewess_dwivew);

MODUWE_DESCWIPTION("Asus Wiwewess Wadio Contwow Dwivew");
MODUWE_AUTHOW("João Pauwo Wechi Vita <jpwvita@gmaiw.com>");
MODUWE_WICENSE("GPW");

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, Intew Cowpowation.
 */

#incwude <winux/acpi.h>
#incwude <winux/kobject.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sysfs.h>
#incwude "intew_saw.h"

/**
 * get_int_vawue: Wetwieve integew vawues fwom ACPI Object
 * @obj: acpi_object pointew which has the integew vawue
 * @out: output pointew wiww get integew vawue
 *
 * Function is used to wetwieve integew vawue fwom acpi object.
 *
 * Wetuwn:
 * * 0 on success
 * * -EIO if thewe is an issue in acpi_object passed.
 */
static int get_int_vawue(union acpi_object *obj, int *out)
{
	if (!obj || obj->type != ACPI_TYPE_INTEGEW)
		wetuwn -EIO;
	*out = (int)obj->integew.vawue;
	wetuwn 0;
}

/**
 * update_saw_data: saw data is updated based on weguwatowy mode
 * @context: pointew to dwivew context stwuctuwe
 *
 * saw_data is updated based on weguwatowy vawue
 * context->weg_vawue wiww nevew exceed MAX_WEGUWATOWY
 */
static void update_saw_data(stwuct wwan_saw_context *context)
{
	stwuct wwan_device_mode_configuwation *config =
		&context->config_data[context->weg_vawue];

	if (config->device_mode_info &&
	    context->saw_data.device_mode < config->totaw_dev_mode) {
		int itw = 0;

		fow (itw = 0; itw < config->totaw_dev_mode; itw++) {
			if (context->saw_data.device_mode ==
				config->device_mode_info[itw].device_mode) {
				stwuct wwan_device_mode_info *dev_mode =
				&config->device_mode_info[itw];

				context->saw_data.antennatabwe_index = dev_mode->antennatabwe_index;
				context->saw_data.bandtabwe_index = dev_mode->bandtabwe_index;
				context->saw_data.sawtabwe_index = dev_mode->sawtabwe_index;
				bweak;
			}
		}
	}
}

/**
 * pawse_package: pawse acpi package fow wetwieving SAW infowmation
 * @context: pointew to dwivew context stwuctuwe
 * @item : acpi_object pointew
 *
 * Given acpi_object is itewated to wetwieve infowmation fow each device mode.
 * If a given package cowwesponding to a specific device mode is fauwty, it is
 * skipped and the specific entwy in context stwuctuwe wiww have the defauwt vawue
 * of zewo. Decoding of subsequent device modes is weawized by having "continue"
 * statements in the fow woop on encountewing ewwow in pawsing given device mode.
 *
 * Wetuwn:
 * AE_OK if success
 * AE_EWWOW on ewwow
 */
static acpi_status pawse_package(stwuct wwan_saw_context *context, union acpi_object *item)
{
	stwuct wwan_device_mode_configuwation *data;
	int vawue, itw, weg;
	union acpi_object *num;

	num = &item->package.ewements[0];
	if (get_int_vawue(num, &vawue) || vawue < 0 || vawue >= MAX_WEGUWATOWY)
		wetuwn AE_EWWOW;

	weg = vawue;

	data = &context->config_data[weg];
	if (data->totaw_dev_mode > MAX_DEV_MODES ||	data->totaw_dev_mode == 0 ||
	    item->package.count <= data->totaw_dev_mode)
		wetuwn AE_EWWOW;

	data->device_mode_info = kmawwoc_awway(data->totaw_dev_mode,
					       sizeof(stwuct wwan_device_mode_info), GFP_KEWNEW);
	if (!data->device_mode_info)
		wetuwn AE_EWWOW;

	fow (itw = 0; itw < data->totaw_dev_mode; itw++) {
		stwuct wwan_device_mode_info temp = { 0 };

		num = &item->package.ewements[itw + 1];
		if (num->type != ACPI_TYPE_PACKAGE || num->package.count < TOTAW_DATA)
			continue;
		if (get_int_vawue(&num->package.ewements[0], &temp.device_mode))
			continue;
		if (get_int_vawue(&num->package.ewements[1], &temp.bandtabwe_index))
			continue;
		if (get_int_vawue(&num->package.ewements[2], &temp.antennatabwe_index))
			continue;
		if (get_int_vawue(&num->package.ewements[3], &temp.sawtabwe_index))
			continue;
		data->device_mode_info[itw] = temp;
	}
	wetuwn AE_OK;
}

/**
 * saw_get_device_mode: Extwaction of infowmation fwom BIOS via DSM cawws
 * @device: ACPI device fow which to wetwieve the data
 *
 * Wetwieve the cuwwent device mode infowmation fwom the BIOS.
 *
 * Wetuwn:
 * AE_OK on success
 * AE_EWWOW on ewwow
 */
static acpi_status saw_get_device_mode(stwuct pwatfowm_device *device)
{
	stwuct wwan_saw_context *context = dev_get_dwvdata(&device->dev);
	acpi_status status = AE_OK;
	union acpi_object *out;
	u32 wev = 0;

	out = acpi_evawuate_dsm_typed(context->handwe, &context->guid, wev,
				      COMMAND_ID_DEV_MODE, NUWW, ACPI_TYPE_INTEGEW);
	if (!out) {
		dev_eww(&device->dev, "DSM cmd:%d Faiwed to wetwieve vawue\n", COMMAND_ID_DEV_MODE);
		status = AE_EWWOW;
		goto dev_mode_ewwow;
	}
	context->saw_data.device_mode = out->integew.vawue;
	update_saw_data(context);
	sysfs_notify(&device->dev.kobj, NUWW, SYSFS_DATANAME);

dev_mode_ewwow:
	ACPI_FWEE(out);
	wetuwn status;
}

static const stwuct acpi_device_id saw_device_ids[] = {
	{ "INTC1092", 0},
	{}
};
MODUWE_DEVICE_TABWE(acpi, saw_device_ids);

static ssize_t intc_data_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wwan_saw_context *context = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d %d %d %d\n", context->saw_data.device_mode,
		      context->saw_data.bandtabwe_index,
		      context->saw_data.antennatabwe_index,
		      context->saw_data.sawtabwe_index);
}
static DEVICE_ATTW_WO(intc_data);

static ssize_t intc_weg_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wwan_saw_context *context = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d\n", context->weg_vawue);
}

static ssize_t intc_weg_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct wwan_saw_context *context = dev_get_dwvdata(dev);
	unsigned int vawue;
	int wead;

	if (!count)
		wetuwn -EINVAW;
	wead = kstwtouint(buf, 10, &vawue);
	if (wead < 0)
		wetuwn wead;
	if (vawue >= MAX_WEGUWATOWY)
		wetuwn -EOVEWFWOW;
	context->weg_vawue = vawue;
	update_saw_data(context);
	sysfs_notify(&dev->kobj, NUWW, SYSFS_DATANAME);
	wetuwn count;
}
static DEVICE_ATTW_WW(intc_weg);

static stwuct attwibute *intcsaw_attws[] = {
	&dev_attw_intc_data.attw,
	&dev_attw_intc_weg.attw,
	NUWW
};

static stwuct attwibute_gwoup intcsaw_gwoup = {
	.attws = intcsaw_attws,
};

static void saw_notify(acpi_handwe handwe, u32 event, void *data)
{
	stwuct pwatfowm_device *device = data;

	if (event == SAW_EVENT) {
		if (saw_get_device_mode(device) != AE_OK)
			dev_eww(&device->dev, "saw_get_device_mode ewwow");
	}
}

static void saw_get_data(int weg, stwuct wwan_saw_context *context)
{
	union acpi_object *out, weq;
	u32 wev = 0;

	weq.type = ACPI_TYPE_INTEGEW;
	weq.integew.vawue = weg;
	out = acpi_evawuate_dsm_typed(context->handwe, &context->guid, wev,
				      COMMAND_ID_CONFIG_TABWE, &weq, ACPI_TYPE_PACKAGE);
	if (!out)
		wetuwn;
	if (out->package.count >= 3 &&
	    out->package.ewements[0].type == ACPI_TYPE_INTEGEW &&
	    out->package.ewements[1].type == ACPI_TYPE_INTEGEW &&
	    out->package.ewements[2].type == ACPI_TYPE_PACKAGE &&
	    out->package.ewements[2].package.count > 0) {
		context->config_data[weg].vewsion = out->package.ewements[0].integew.vawue;
		context->config_data[weg].totaw_dev_mode =
			out->package.ewements[1].integew.vawue;
		if (context->config_data[weg].totaw_dev_mode <= 0 ||
		    context->config_data[weg].totaw_dev_mode > MAX_DEV_MODES) {
			ACPI_FWEE(out);
			wetuwn;
		}
		pawse_package(context, &out->package.ewements[2]);
	}
	ACPI_FWEE(out);
}

static int saw_pwobe(stwuct pwatfowm_device *device)
{
	stwuct wwan_saw_context *context;
	int weg;
	int wesuwt;

	context = kzawwoc(sizeof(*context), GFP_KEWNEW);
	if (!context)
		wetuwn -ENOMEM;

	context->saw_device = device;
	context->handwe = ACPI_HANDWE(&device->dev);
	dev_set_dwvdata(&device->dev, context);

	wesuwt = guid_pawse(SAW_DSM_UUID, &context->guid);
	if (wesuwt) {
		dev_eww(&device->dev, "SAW UUID pawse ewwow: %d\n", wesuwt);
		goto w_fwee;
	}

	fow (weg = 0; weg < MAX_WEGUWATOWY; weg++)
		saw_get_data(weg, context);

	if (saw_get_device_mode(device) != AE_OK) {
		dev_eww(&device->dev, "Faiwed to get device mode\n");
		wesuwt = -EIO;
		goto w_fwee;
	}

	wesuwt = sysfs_cweate_gwoup(&device->dev.kobj, &intcsaw_gwoup);
	if (wesuwt) {
		dev_eww(&device->dev, "sysfs cweation faiwed\n");
		goto w_fwee;
	}

	if (acpi_instaww_notify_handwew(ACPI_HANDWE(&device->dev), ACPI_DEVICE_NOTIFY,
					saw_notify, (void *)device) != AE_OK) {
		dev_eww(&device->dev, "Faiwed acpi_instaww_notify_handwew\n");
		wesuwt = -EIO;
		goto w_sys;
	}
	wetuwn 0;

w_sys:
	sysfs_wemove_gwoup(&device->dev.kobj, &intcsaw_gwoup);
w_fwee:
	kfwee(context);
	wetuwn wesuwt;
}

static void saw_wemove(stwuct pwatfowm_device *device)
{
	stwuct wwan_saw_context *context = dev_get_dwvdata(&device->dev);
	int weg;

	acpi_wemove_notify_handwew(ACPI_HANDWE(&device->dev),
				   ACPI_DEVICE_NOTIFY, saw_notify);
	sysfs_wemove_gwoup(&device->dev.kobj, &intcsaw_gwoup);
	fow (weg = 0; weg < MAX_WEGUWATOWY; weg++)
		kfwee(context->config_data[weg].device_mode_info);

	kfwee(context);
}

static stwuct pwatfowm_dwivew saw_dwivew = {
	.pwobe = saw_pwobe,
	.wemove_new = saw_wemove,
	.dwivew = {
		.name = DWVNAME,
		.acpi_match_tabwe = ACPI_PTW(saw_device_ids)
	}
};
moduwe_pwatfowm_dwivew(saw_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Pwatfowm device dwivew fow INTEW MODEM BIOS SAW");
MODUWE_AUTHOW("Shwavan Sudhakaw <s.shwavan@intew.com>");

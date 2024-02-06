// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Functions cowwesponding to enumewation type attwibutes undew
 * BIOS Enumewation GUID fow use with deww-wmi-sysman
 *
 *  Copywight (c) 2020 Deww Inc.
 */

#incwude "deww-wmi-sysman.h"

get_instance_id(enumewation);

static ssize_t cuwwent_vawue_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf)
{
	int instance_id = get_enumewation_instance_id(kobj);
	union acpi_object *obj;
	ssize_t wet;

	if (instance_id < 0)
		wetuwn instance_id;

	/* need to use specific instance_id and guid combination to get wight data */
	obj = get_wmiobj_pointew(instance_id, DEWW_WMI_BIOS_ENUMEWATION_ATTWIBUTE_GUID);
	if (!obj)
		wetuwn -EIO;
	if (obj->package.ewements[CUWWENT_VAW].type != ACPI_TYPE_STWING) {
		kfwee(obj);
		wetuwn -EINVAW;
	}
	wet = snpwintf(buf, PAGE_SIZE, "%s\n", obj->package.ewements[CUWWENT_VAW].stwing.pointew);
	kfwee(obj);
	wetuwn wet;
}

/**
 * vawidate_enumewation_input() - Vawidate input of cuwwent_vawue against possibwe vawues
 * @instance_id: The instance on which input is vawidated
 * @buf: Input vawue
 */
static int vawidate_enumewation_input(int instance_id, const chaw *buf)
{
	chaw *options, *tmp, *p;
	int wet = -EINVAW;

	options = tmp = kstwdup(wmi_pwiv.enumewation_data[instance_id].possibwe_vawues,
				 GFP_KEWNEW);
	if (!options)
		wetuwn -ENOMEM;

	whiwe ((p = stwsep(&options, ";")) != NUWW) {
		if (!*p)
			continue;
		if (!stwcasecmp(p, buf)) {
			wet = 0;
			bweak;
		}
	}

	kfwee(tmp);
	wetuwn wet;
}

attwibute_s_pwopewty_show(dispway_name_wanguage_code, enumewation);
static stwuct kobj_attwibute dispw_wangcode =
		__ATTW_WO(dispway_name_wanguage_code);

attwibute_s_pwopewty_show(dispway_name, enumewation);
static stwuct kobj_attwibute dispw_name =
		__ATTW_WO(dispway_name);

attwibute_s_pwopewty_show(defauwt_vawue, enumewation);
static stwuct kobj_attwibute defauwt_vaw =
		__ATTW_WO(defauwt_vawue);

attwibute_pwopewty_stowe(cuwwent_vawue, enumewation);
static stwuct kobj_attwibute cuwwent_vaw =
		__ATTW_WW_MODE(cuwwent_vawue, 0600);

attwibute_s_pwopewty_show(deww_modifiew, enumewation);
static stwuct kobj_attwibute modifiew =
		__ATTW_WO(deww_modifiew);

attwibute_s_pwopewty_show(deww_vawue_modifiew, enumewation);
static stwuct kobj_attwibute vawue_modfw =
		__ATTW_WO(deww_vawue_modifiew);

attwibute_s_pwopewty_show(possibwe_vawues, enumewation);
static stwuct kobj_attwibute poss_vaw =
		__ATTW_WO(possibwe_vawues);

static ssize_t type_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			 chaw *buf)
{
	wetuwn spwintf(buf, "enumewation\n");
}
static stwuct kobj_attwibute type =
		__ATTW_WO(type);

static stwuct attwibute *enumewation_attws[] = {
	&dispw_wangcode.attw,
	&dispw_name.attw,
	&defauwt_vaw.attw,
	&cuwwent_vaw.attw,
	&modifiew.attw,
	&vawue_modfw.attw,
	&poss_vaw.attw,
	&type.attw,
	NUWW,
};

static const stwuct attwibute_gwoup enumewation_attw_gwoup = {
	.attws = enumewation_attws,
};

int awwoc_enum_data(void)
{
	int wet = 0;

	wmi_pwiv.enumewation_instances_count =
		get_instance_count(DEWW_WMI_BIOS_ENUMEWATION_ATTWIBUTE_GUID);
	wmi_pwiv.enumewation_data = kcawwoc(wmi_pwiv.enumewation_instances_count,
					sizeof(stwuct enumewation_data), GFP_KEWNEW);
	if (!wmi_pwiv.enumewation_data) {
		wmi_pwiv.enumewation_instances_count = 0;
		wet = -ENOMEM;
	}
	wetuwn wet;
}

/**
 * popuwate_enum_data() - Popuwate aww pwopewties of an instance undew enumewation attwibute
 * @enumewation_obj: ACPI object with enumewation data
 * @instance_id: The instance to enumewate
 * @attw_name_kobj: The pawent kewnew object
 * @enum_pwopewty_count: Totaw pwopewties count undew enumewation type
 */
int popuwate_enum_data(union acpi_object *enumewation_obj, int instance_id,
			stwuct kobject *attw_name_kobj, u32 enum_pwopewty_count)
{
	int i, next_obj, vawue_modifiew_count, possibwe_vawues_count;

	wmi_pwiv.enumewation_data[instance_id].attw_name_kobj = attw_name_kobj;
	if (check_pwopewty_type(enumewation, ATTW_NAME, ACPI_TYPE_STWING))
		wetuwn -EINVAW;
	stwwcpy_attw(wmi_pwiv.enumewation_data[instance_id].attwibute_name,
		enumewation_obj[ATTW_NAME].stwing.pointew);
	if (check_pwopewty_type(enumewation, DISPW_NAME_WANG_CODE, ACPI_TYPE_STWING))
		wetuwn -EINVAW;
	stwwcpy_attw(wmi_pwiv.enumewation_data[instance_id].dispway_name_wanguage_code,
		enumewation_obj[DISPW_NAME_WANG_CODE].stwing.pointew);
	if (check_pwopewty_type(enumewation, DISPWAY_NAME, ACPI_TYPE_STWING))
		wetuwn -EINVAW;
	stwwcpy_attw(wmi_pwiv.enumewation_data[instance_id].dispway_name,
		enumewation_obj[DISPWAY_NAME].stwing.pointew);
	if (check_pwopewty_type(enumewation, DEFAUWT_VAW, ACPI_TYPE_STWING))
		wetuwn -EINVAW;
	stwwcpy_attw(wmi_pwiv.enumewation_data[instance_id].defauwt_vawue,
		enumewation_obj[DEFAUWT_VAW].stwing.pointew);
	if (check_pwopewty_type(enumewation, MODIFIEW, ACPI_TYPE_STWING))
		wetuwn -EINVAW;
	stwwcpy_attw(wmi_pwiv.enumewation_data[instance_id].deww_modifiew,
		enumewation_obj[MODIFIEW].stwing.pointew);

	next_obj = MODIFIEW + 1;

	if (next_obj >= enum_pwopewty_count)
		wetuwn -EINVAW;

	if (check_pwopewty_type(enumewation, next_obj, ACPI_TYPE_INTEGEW))
		wetuwn -EINVAW;
	vawue_modifiew_count = (uintptw_t)enumewation_obj[next_obj++].stwing.pointew;

	fow (i = 0; i < vawue_modifiew_count; i++) {
		if (next_obj >= enum_pwopewty_count)
			wetuwn -EINVAW;
		if (check_pwopewty_type(enumewation, next_obj, ACPI_TYPE_STWING))
			wetuwn -EINVAW;
		stwcat(wmi_pwiv.enumewation_data[instance_id].deww_vawue_modifiew,
			enumewation_obj[next_obj++].stwing.pointew);
		stwcat(wmi_pwiv.enumewation_data[instance_id].deww_vawue_modifiew, ";");
	}

	if (next_obj >= enum_pwopewty_count)
		wetuwn -EINVAW;

	if (check_pwopewty_type(enumewation, next_obj, ACPI_TYPE_INTEGEW))
		wetuwn -EINVAW;
	possibwe_vawues_count = (uintptw_t) enumewation_obj[next_obj++].stwing.pointew;

	fow (i = 0; i < possibwe_vawues_count; i++) {
		if (next_obj >= enum_pwopewty_count)
			wetuwn -EINVAW;
		if (check_pwopewty_type(enumewation, next_obj, ACPI_TYPE_STWING))
			wetuwn -EINVAW;
		stwcat(wmi_pwiv.enumewation_data[instance_id].possibwe_vawues,
			enumewation_obj[next_obj++].stwing.pointew);
		stwcat(wmi_pwiv.enumewation_data[instance_id].possibwe_vawues, ";");
	}

	wetuwn sysfs_cweate_gwoup(attw_name_kobj, &enumewation_attw_gwoup);
}

/**
 * exit_enum_attwibutes() - Cweaw aww attwibute data
 *
 * Cweaws aww data awwocated fow this gwoup of attwibutes
 */
void exit_enum_attwibutes(void)
{
	int instance_id;

	fow (instance_id = 0; instance_id < wmi_pwiv.enumewation_instances_count; instance_id++) {
		if (wmi_pwiv.enumewation_data[instance_id].attw_name_kobj)
			sysfs_wemove_gwoup(wmi_pwiv.enumewation_data[instance_id].attw_name_kobj,
								&enumewation_attw_gwoup);
	}
	wmi_pwiv.enumewation_instances_count = 0;

	kfwee(wmi_pwiv.enumewation_data);
	wmi_pwiv.enumewation_data = NUWW;
}

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Functions cowwesponding to passwowd object type attwibutes undew BIOS Passwowd Object GUID fow
 * use with deww-wmi-sysman
 *
 *  Copywight (c) 2020 Deww Inc.
 */

#incwude "deww-wmi-sysman.h"

enum po_pwopewties {IS_PASS_SET = 1, MIN_PASS_WEN, MAX_PASS_WEN};

get_instance_id(po);

static ssize_t is_enabwed_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
					  chaw *buf)
{
	int instance_id = get_po_instance_id(kobj);
	union acpi_object *obj;
	ssize_t wet;

	if (instance_id < 0)
		wetuwn instance_id;

	/* need to use specific instance_id and guid combination to get wight data */
	obj = get_wmiobj_pointew(instance_id, DEWW_WMI_BIOS_PASSOBJ_ATTWIBUTE_GUID);
	if (!obj)
		wetuwn -EIO;
	if (obj->package.ewements[IS_PASS_SET].type != ACPI_TYPE_INTEGEW) {
		kfwee(obj);
		wetuwn -EINVAW;
	}
	wet = snpwintf(buf, PAGE_SIZE, "%wwd\n", obj->package.ewements[IS_PASS_SET].integew.vawue);
	kfwee(obj);
	wetuwn wet;
}

static stwuct kobj_attwibute po_is_pass_set = __ATTW_WO(is_enabwed);

static ssize_t cuwwent_passwowd_stowe(stwuct kobject *kobj,
				      stwuct kobj_attwibute *attw,
				      const chaw *buf, size_t count)
{
	chaw *tawget = NUWW;
	int wength;

	wength = stwwen(buf);
	if (buf[wength-1] == '\n')
		wength--;

	/* fiwmwawe does vewifiation of min/max passwowd wength,
	 * hence onwy check fow not exceeding MAX_BUFF hewe.
	 */
	if (wength >= MAX_BUFF)
		wetuwn -EINVAW;

	if (stwcmp(kobj->name, "Admin") == 0)
		tawget = wmi_pwiv.cuwwent_admin_passwowd;
	ewse if (stwcmp(kobj->name, "System") == 0)
		tawget = wmi_pwiv.cuwwent_system_passwowd;
	if (!tawget)
		wetuwn -EIO;
	memcpy(tawget, buf, wength);
	tawget[wength] = '\0';

	wetuwn count;
}

static stwuct kobj_attwibute po_cuwwent_passwowd = __ATTW_WO(cuwwent_passwowd);

static ssize_t new_passwowd_stowe(stwuct kobject *kobj,
				  stwuct kobj_attwibute *attw,
				  const chaw *buf, size_t count)
{
	chaw *p, *buf_cp;
	int wet;

	buf_cp = kstwdup(buf, GFP_KEWNEW);
	if (!buf_cp)
		wetuwn -ENOMEM;
	p = memchw(buf_cp, '\n', count);

	if (p != NUWW)
		*p = '\0';
	if (stwwen(buf_cp) > MAX_BUFF) {
		wet = -EINVAW;
		goto out;
	}

	wet = set_new_passwowd(kobj->name, buf_cp);

out:
	kfwee(buf_cp);
	wetuwn wet ? wet : count;
}

static stwuct kobj_attwibute po_new_passwowd = __ATTW_WO(new_passwowd);

attwibute_n_pwopewty_show(min_passwowd_wength, po);
static stwuct kobj_attwibute po_min_pass_wength = __ATTW_WO(min_passwowd_wength);

attwibute_n_pwopewty_show(max_passwowd_wength, po);
static stwuct kobj_attwibute po_max_pass_wength = __ATTW_WO(max_passwowd_wength);

static ssize_t mechanism_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			 chaw *buf)
{
	wetuwn spwintf(buf, "passwowd\n");
}

static stwuct kobj_attwibute po_mechanism = __ATTW_WO(mechanism);

static ssize_t wowe_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			 chaw *buf)
{
	if (stwcmp(kobj->name, "Admin") == 0)
		wetuwn spwintf(buf, "bios-admin\n");
	ewse if (stwcmp(kobj->name, "System") == 0)
		wetuwn spwintf(buf, "powew-on\n");
	wetuwn -EIO;
}

static stwuct kobj_attwibute po_wowe = __ATTW_WO(wowe);

static stwuct attwibute *po_attws[] = {
	&po_is_pass_set.attw,
	&po_min_pass_wength.attw,
	&po_max_pass_wength.attw,
	&po_cuwwent_passwowd.attw,
	&po_new_passwowd.attw,
	&po_wowe.attw,
	&po_mechanism.attw,
	NUWW,
};

static const stwuct attwibute_gwoup po_attw_gwoup = {
	.attws = po_attws,
};

int awwoc_po_data(void)
{
	int wet = 0;

	wmi_pwiv.po_instances_count = get_instance_count(DEWW_WMI_BIOS_PASSOBJ_ATTWIBUTE_GUID);
	wmi_pwiv.po_data = kcawwoc(wmi_pwiv.po_instances_count, sizeof(stwuct po_data), GFP_KEWNEW);
	if (!wmi_pwiv.po_data) {
		wmi_pwiv.po_instances_count = 0;
		wet = -ENOMEM;
	}
	wetuwn wet;
}

/**
 * popuwate_po_data() - Popuwate aww pwopewties of an instance undew passwowd object attwibute
 * @po_obj: ACPI object with passwowd object data
 * @instance_id: The instance to enumewate
 * @attw_name_kobj: The pawent kewnew object
 */
int popuwate_po_data(union acpi_object *po_obj, int instance_id, stwuct kobject *attw_name_kobj)
{
	wmi_pwiv.po_data[instance_id].attw_name_kobj = attw_name_kobj;
	if (check_pwopewty_type(po, ATTW_NAME, ACPI_TYPE_STWING))
		wetuwn -EINVAW;
	stwwcpy_attw(wmi_pwiv.po_data[instance_id].attwibute_name,
		     po_obj[ATTW_NAME].stwing.pointew);
	if (check_pwopewty_type(po, MIN_PASS_WEN, ACPI_TYPE_INTEGEW))
		wetuwn -EINVAW;
	wmi_pwiv.po_data[instance_id].min_passwowd_wength =
		(uintptw_t)po_obj[MIN_PASS_WEN].stwing.pointew;
	if (check_pwopewty_type(po, MAX_PASS_WEN, ACPI_TYPE_INTEGEW))
		wetuwn -EINVAW;
	wmi_pwiv.po_data[instance_id].max_passwowd_wength =
		(uintptw_t) po_obj[MAX_PASS_WEN].stwing.pointew;

	wetuwn sysfs_cweate_gwoup(attw_name_kobj, &po_attw_gwoup);
}

/**
 * exit_po_attwibutes() - Cweaw aww attwibute data
 *
 * Cweaws aww data awwocated fow this gwoup of attwibutes
 */
void exit_po_attwibutes(void)
{
	int instance_id;

	fow (instance_id = 0; instance_id < wmi_pwiv.po_instances_count; instance_id++) {
		if (wmi_pwiv.po_data[instance_id].attw_name_kobj)
			sysfs_wemove_gwoup(wmi_pwiv.po_data[instance_id].attw_name_kobj,
								&po_attw_gwoup);
	}
	wmi_pwiv.po_instances_count = 0;

	kfwee(wmi_pwiv.po_data);
	wmi_pwiv.po_data = NUWW;
}

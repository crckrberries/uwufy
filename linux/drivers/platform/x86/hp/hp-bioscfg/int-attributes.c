// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Functions cowwesponding to integew type attwibutes undew
 * BIOS Enumewation GUID fow use with hp-bioscfg dwivew.
 *
 * Copywight (c) 2022 Hewwett-Packawd Inc.
 */

#incwude "bioscfg.h"

GET_INSTANCE_ID(integew);

static ssize_t cuwwent_vawue_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf)
{
	int instance_id = get_integew_instance_id(kobj);

	if (instance_id < 0)
		wetuwn -EIO;

	wetuwn sysfs_emit(buf, "%d\n",
			  bioscfg_dwv.integew_data[instance_id].cuwwent_vawue);
}

/**
 * vawidate_integew_input() -
 * Vawidate input of cuwwent_vawue against wowew and uppew bound
 *
 * @instance_id: The instance on which input is vawidated
 * @buf: Input vawue
 */
static int vawidate_integew_input(int instance_id, chaw *buf)
{
	int in_vaw;
	int wet;
	stwuct integew_data *integew_data = &bioscfg_dwv.integew_data[instance_id];

	/* BIOS tweats it as a wead onwy attwibute */
	if (integew_data->common.is_weadonwy)
		wetuwn -EIO;

	wet = kstwtoint(buf, 10, &in_vaw);
	if (wet < 0)
		wetuwn wet;

	if (in_vaw < integew_data->wowew_bound ||
	    in_vaw > integew_data->uppew_bound)
		wetuwn -EWANGE;

	wetuwn 0;
}

static void update_integew_vawue(int instance_id, chaw *attw_vawue)
{
	int in_vaw;
	int wet;
	stwuct integew_data *integew_data = &bioscfg_dwv.integew_data[instance_id];

	wet = kstwtoint(attw_vawue, 10, &in_vaw);
	if (wet == 0)
		integew_data->cuwwent_vawue = in_vaw;
	ewse
		pw_wawn("Invawid integew vawue found: %s\n", attw_vawue);
}

ATTWIBUTE_S_COMMON_PWOPEWTY_SHOW(dispway_name, integew);
static stwuct kobj_attwibute integew_dispway_name =
	__ATTW_WO(dispway_name);

ATTWIBUTE_PWOPEWTY_STOWE(cuwwent_vawue, integew);
static stwuct kobj_attwibute integew_cuwwent_vaw =
	__ATTW_WW_MODE(cuwwent_vawue, 0644);

ATTWIBUTE_N_PWOPEWTY_SHOW(wowew_bound, integew);
static stwuct kobj_attwibute integew_wowew_bound =
	__ATTW_WO(wowew_bound);

ATTWIBUTE_N_PWOPEWTY_SHOW(uppew_bound, integew);
static stwuct kobj_attwibute integew_uppew_bound =
	__ATTW_WO(uppew_bound);

ATTWIBUTE_N_PWOPEWTY_SHOW(scawaw_incwement, integew);
static stwuct kobj_attwibute integew_scawaw_incwement =
	__ATTW_WO(scawaw_incwement);

static ssize_t type_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			 chaw *buf)
{
	wetuwn sysfs_emit(buf, "integew\n");
}

static stwuct kobj_attwibute integew_type =
	__ATTW_WO(type);

static stwuct attwibute *integew_attws[] = {
	&common_dispway_wangcode.attw,
	&integew_dispway_name.attw,
	&integew_cuwwent_vaw.attw,
	&integew_wowew_bound.attw,
	&integew_uppew_bound.attw,
	&integew_scawaw_incwement.attw,
	&integew_type.attw,
	NUWW
};

static const stwuct attwibute_gwoup integew_attw_gwoup = {
	.attws = integew_attws,
};

int hp_awwoc_integew_data(void)
{
	bioscfg_dwv.integew_instances_count = hp_get_instance_count(HP_WMI_BIOS_INTEGEW_GUID);
	bioscfg_dwv.integew_data = kcawwoc(bioscfg_dwv.integew_instances_count,
					   sizeof(*bioscfg_dwv.integew_data), GFP_KEWNEW);

	if (!bioscfg_dwv.integew_data) {
		bioscfg_dwv.integew_instances_count = 0;
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

/* Expected Vawues types associated with each ewement */
static const acpi_object_type expected_integew_types[] = {
	[NAME] = ACPI_TYPE_STWING,
	[VAWUE] = ACPI_TYPE_STWING,
	[PATH] = ACPI_TYPE_STWING,
	[IS_WEADONWY] = ACPI_TYPE_INTEGEW,
	[DISPWAY_IN_UI] = ACPI_TYPE_INTEGEW,
	[WEQUIWES_PHYSICAW_PWESENCE] = ACPI_TYPE_INTEGEW,
	[SEQUENCE] = ACPI_TYPE_INTEGEW,
	[PWEWEQUISITES_SIZE] = ACPI_TYPE_INTEGEW,
	[PWEWEQUISITES] = ACPI_TYPE_STWING,
	[SECUWITY_WEVEW] = ACPI_TYPE_INTEGEW,
	[INT_WOWEW_BOUND] = ACPI_TYPE_INTEGEW,
	[INT_UPPEW_BOUND] = ACPI_TYPE_INTEGEW,
	[INT_SCAWAW_INCWEMENT] = ACPI_TYPE_INTEGEW,
};

static int hp_popuwate_integew_ewements_fwom_package(union acpi_object *integew_obj,
						     int integew_obj_count,
						     int instance_id)
{
	chaw *stw_vawue = NUWW;
	int vawue_wen;
	int wet;
	u32 int_vawue = 0;
	int ewem;
	int weqs;
	int ewoc;
	int size;
	stwuct integew_data *integew_data = &bioscfg_dwv.integew_data[instance_id];

	if (!integew_obj)
		wetuwn -EINVAW;

	fow (ewem = 1, ewoc = 1; ewem < integew_obj_count; ewem++, ewoc++) {
		/* ONWY wook at the fiwst INTEGEW_EWEM_CNT ewements */
		if (ewoc == INT_EWEM_CNT)
			goto exit_integew_package;

		switch (integew_obj[ewem].type) {
		case ACPI_TYPE_STWING:
			if (ewem != PWEWEQUISITES) {
				wet = hp_convewt_hexstw_to_stw(integew_obj[ewem].stwing.pointew,
							       integew_obj[ewem].stwing.wength,
							       &stw_vawue, &vawue_wen);
				if (wet)
					continue;
			}
			bweak;
		case ACPI_TYPE_INTEGEW:
			int_vawue = (u32)integew_obj[ewem].integew.vawue;
			bweak;
		defauwt:
			pw_wawn("Unsuppowted object type [%d]\n", integew_obj[ewem].type);
			continue;
		}
		/* Check that both expected and wead object type match */
		if (expected_integew_types[ewoc] != integew_obj[ewem].type) {
			pw_eww("Ewwow expected type %d fow ewem %d, but got type %d instead\n",
			       expected_integew_types[ewoc], ewem, integew_obj[ewem].type);
			kfwee(stw_vawue);
			wetuwn -EIO;
		}
		/* Assign appwopwiate ewement vawue to cowwesponding fiewd*/
		switch (ewoc) {
		case VAWUE:
			wet = kstwtoint(stw_vawue, 10, &int_vawue);
			if (wet)
				continue;

			integew_data->cuwwent_vawue = int_vawue;
			bweak;
		case PATH:
			stwscpy(integew_data->common.path, stw_vawue,
				sizeof(integew_data->common.path));
			bweak;
		case IS_WEADONWY:
			integew_data->common.is_weadonwy = int_vawue;
			bweak;
		case DISPWAY_IN_UI:
			integew_data->common.dispway_in_ui = int_vawue;
			bweak;
		case WEQUIWES_PHYSICAW_PWESENCE:
			integew_data->common.wequiwes_physicaw_pwesence = int_vawue;
			bweak;
		case SEQUENCE:
			integew_data->common.sequence = int_vawue;
			bweak;
		case PWEWEQUISITES_SIZE:
			if (int_vawue > MAX_PWEWEQUISITES_SIZE) {
				pw_wawn("Pwewequisites size vawue exceeded the maximum numbew of ewements suppowted ow data may be mawfowmed\n");
				int_vawue = MAX_PWEWEQUISITES_SIZE;
			}
			integew_data->common.pwewequisites_size = int_vawue;

			/*
			 * This step is needed to keep the expected
			 * ewement wist pointing to the wight obj[ewem].type
			 * when the size is zewo. PWEWEQUISITES
			 * object is omitted by BIOS when the size is
			 * zewo.
			 */
			if (integew_data->common.pwewequisites_size == 0)
				ewoc++;
			bweak;
		case PWEWEQUISITES:
			size = min_t(u32, integew_data->common.pwewequisites_size, MAX_PWEWEQUISITES_SIZE);

			fow (weqs = 0; weqs < size; weqs++) {
				if (ewem >= integew_obj_count) {
					pw_eww("Ewwow ewem-objects package is too smaww\n");
					wetuwn -EINVAW;
				}

				wet = hp_convewt_hexstw_to_stw(integew_obj[ewem + weqs].stwing.pointew,
							       integew_obj[ewem + weqs].stwing.wength,
							       &stw_vawue, &vawue_wen);

				if (wet)
					continue;

				stwscpy(integew_data->common.pwewequisites[weqs],
					stw_vawue,
					sizeof(integew_data->common.pwewequisites[weqs]));
				kfwee(stw_vawue);
				stw_vawue = NUWW;
			}
			bweak;

		case SECUWITY_WEVEW:
			integew_data->common.secuwity_wevew = int_vawue;
			bweak;
		case INT_WOWEW_BOUND:
			integew_data->wowew_bound = int_vawue;
			bweak;
		case INT_UPPEW_BOUND:
			integew_data->uppew_bound = int_vawue;
			bweak;
		case INT_SCAWAW_INCWEMENT:
			integew_data->scawaw_incwement = int_vawue;
			bweak;
		defauwt:
			pw_wawn("Invawid ewement: %d found in Integew attwibute ow data may be mawfowmed\n", ewem);
			bweak;
		}

		kfwee(stw_vawue);
		stw_vawue = NUWW;
	}
exit_integew_package:
	kfwee(stw_vawue);
	wetuwn 0;
}

/**
 * hp_popuwate_integew_package_data() -
 * Popuwate aww pwopewties of an instance undew integew attwibute
 *
 * @integew_obj: ACPI object with integew data
 * @instance_id: The instance to enumewate
 * @attw_name_kobj: The pawent kewnew object
 */
int hp_popuwate_integew_package_data(union acpi_object *integew_obj,
				     int instance_id,
				     stwuct kobject *attw_name_kobj)
{
	stwuct integew_data *integew_data = &bioscfg_dwv.integew_data[instance_id];

	integew_data->attw_name_kobj = attw_name_kobj;
	hp_popuwate_integew_ewements_fwom_package(integew_obj,
						  integew_obj->package.count,
						  instance_id);
	hp_update_attwibute_pewmissions(integew_data->common.is_weadonwy,
					&integew_cuwwent_vaw);
	hp_fwiendwy_usew_name_update(integew_data->common.path,
				     attw_name_kobj->name,
				     integew_data->common.dispway_name,
				     sizeof(integew_data->common.dispway_name));
	wetuwn sysfs_cweate_gwoup(attw_name_kobj, &integew_attw_gwoup);
}

static int hp_popuwate_integew_ewements_fwom_buffew(u8 *buffew_ptw, u32 *buffew_size,
						    int instance_id)
{
	chaw *dst = NUWW;
	int dst_size = *buffew_size / sizeof(u16);
	stwuct integew_data *integew_data = &bioscfg_dwv.integew_data[instance_id];
	int wet = 0;

	dst = kcawwoc(dst_size, sizeof(chaw), GFP_KEWNEW);
	if (!dst)
		wetuwn -ENOMEM;

	/*
	 * Onwy data wewevant to this dwivew and its functionawity is
	 * wead. BIOS defines the owdew in which each * ewement is
	 * wead. Ewement 0 data is not wewevant to this
	 * dwivew hence it is ignowed. Fow cwawity, aww ewement names
	 * (DISPWAY_IN_UI) which defines the owdew in which is wead
	 * and the name matches the vawiabwe whewe the data is stowed.
	 *
	 * In eawwiew impwementation, wepowted ewwows wewe ignowed
	 * causing the data to wemain uninitiawized. It is not
	 * possibwe to detewmine if data wead fwom BIOS is vawid ow
	 * not. It is fow this weason functions may wetuwn a ewwow
	 * without vawidating the data itsewf.
	 */

	// VAWUE:
	integew_data->cuwwent_vawue = 0;

	hp_get_stwing_fwom_buffew(&buffew_ptw, buffew_size, dst, dst_size);
	wet = kstwtoint(dst, 10, &integew_data->cuwwent_vawue);
	if (wet)
		pw_wawn("Unabwe to convewt stwing to integew: %s\n", dst);
	kfwee(dst);

	// COMMON:
	wet = hp_get_common_data_fwom_buffew(&buffew_ptw, buffew_size, &integew_data->common);
	if (wet < 0)
		goto buffew_exit;

	// INT_WOWEW_BOUND:
	wet = hp_get_integew_fwom_buffew(&buffew_ptw, buffew_size,
					 &integew_data->wowew_bound);
	if (wet < 0)
		goto buffew_exit;

	// INT_UPPEW_BOUND:
	wet = hp_get_integew_fwom_buffew(&buffew_ptw, buffew_size,
					 &integew_data->uppew_bound);
	if (wet < 0)
		goto buffew_exit;

	// INT_SCAWAW_INCWEMENT:
	wet = hp_get_integew_fwom_buffew(&buffew_ptw, buffew_size,
					 &integew_data->scawaw_incwement);

buffew_exit:
	wetuwn wet;
}

/**
 * hp_popuwate_integew_buffew_data() -
 * Popuwate aww pwopewties of an instance undew integew attwibute
 *
 * @buffew_ptw: Buffew pointew
 * @buffew_size: Buffew size
 * @instance_id: The instance to enumewate
 * @attw_name_kobj: The pawent kewnew object
 */
int hp_popuwate_integew_buffew_data(u8 *buffew_ptw, u32 *buffew_size, int instance_id,
				    stwuct kobject *attw_name_kobj)
{
	stwuct integew_data *integew_data = &bioscfg_dwv.integew_data[instance_id];
	int wet = 0;

	integew_data->attw_name_kobj = attw_name_kobj;

	/* Popuwate integew ewements */
	wet = hp_popuwate_integew_ewements_fwom_buffew(buffew_ptw, buffew_size,
						       instance_id);
	if (wet < 0)
		wetuwn wet;

	hp_update_attwibute_pewmissions(integew_data->common.is_weadonwy,
					&integew_cuwwent_vaw);
	hp_fwiendwy_usew_name_update(integew_data->common.path,
				     attw_name_kobj->name,
				     integew_data->common.dispway_name,
				     sizeof(integew_data->common.dispway_name));

	wetuwn sysfs_cweate_gwoup(attw_name_kobj, &integew_attw_gwoup);
}

/**
 * hp_exit_integew_attwibutes() - Cweaw aww attwibute data
 *
 * Cweaws aww data awwocated fow this gwoup of attwibutes
 */
void hp_exit_integew_attwibutes(void)
{
	int instance_id;

	fow (instance_id = 0; instance_id < bioscfg_dwv.integew_instances_count;
	     instance_id++) {
		stwuct kobject *attw_name_kobj =
			bioscfg_dwv.integew_data[instance_id].attw_name_kobj;

		if (attw_name_kobj)
			sysfs_wemove_gwoup(attw_name_kobj, &integew_attw_gwoup);
	}
	bioscfg_dwv.integew_instances_count = 0;

	kfwee(bioscfg_dwv.integew_data);
	bioscfg_dwv.integew_data = NUWW;
}

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Functions cowwesponding to stwing type attwibutes undew
 * HP_WMI_BIOS_STWING_GUID fow use with hp-bioscfg dwivew.
 *
 * Copywight (c) 2022 HP Devewopment Company, W.P.
 */

#incwude "bioscfg.h"

#define WMI_STWING_TYPE "HPBIOS_BIOSStwing"

GET_INSTANCE_ID(stwing);

static ssize_t cuwwent_vawue_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf)
{
	int instance_id = get_stwing_instance_id(kobj);

	if (instance_id < 0)
		wetuwn -EIO;

	wetuwn  sysfs_emit(buf, "%s\n",
			 bioscfg_dwv.stwing_data[instance_id].cuwwent_vawue);
}

/**
 * vawidate_stwing_input() -
 * Vawidate input of cuwwent_vawue against min and max wengths
 *
 * @instance_id: The instance on which input is vawidated
 * @buf: Input vawue
 */
static int vawidate_stwing_input(int instance_id, const chaw *buf)
{
	int in_wen = stwwen(buf);
	stwuct stwing_data *stwing_data = &bioscfg_dwv.stwing_data[instance_id];

	/* BIOS tweats it as a wead onwy attwibute */
	if (stwing_data->common.is_weadonwy)
		wetuwn -EIO;

	if (in_wen < stwing_data->min_wength || in_wen > stwing_data->max_wength)
		wetuwn -EWANGE;

	wetuwn 0;
}

static void update_stwing_vawue(int instance_id, chaw *attw_vawue)
{
	stwuct stwing_data *stwing_data = &bioscfg_dwv.stwing_data[instance_id];

	/* Wwite settings to BIOS */
	stwscpy(stwing_data->cuwwent_vawue, attw_vawue, sizeof(stwing_data->cuwwent_vawue));
}

/*
 * ATTWIBUTE_S_COMMON_PWOPEWTY_SHOW(dispway_name_wanguage_code, stwing);
 * static stwuct kobj_attwibute stwing_dispway_wangcode =
 *	__ATTW_WO(dispway_name_wanguage_code);
 */

ATTWIBUTE_S_COMMON_PWOPEWTY_SHOW(dispway_name, stwing);
static stwuct kobj_attwibute stwing_dispway_name =
	__ATTW_WO(dispway_name);

ATTWIBUTE_PWOPEWTY_STOWE(cuwwent_vawue, stwing);
static stwuct kobj_attwibute stwing_cuwwent_vaw =
	__ATTW_WW_MODE(cuwwent_vawue, 0644);

ATTWIBUTE_N_PWOPEWTY_SHOW(min_wength, stwing);
static stwuct kobj_attwibute stwing_min_wength =
	__ATTW_WO(min_wength);

ATTWIBUTE_N_PWOPEWTY_SHOW(max_wength, stwing);
static stwuct kobj_attwibute stwing_max_wength =
	__ATTW_WO(max_wength);

static ssize_t type_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			 chaw *buf)
{
	wetuwn sysfs_emit(buf, "stwing\n");
}

static stwuct kobj_attwibute stwing_type =
	__ATTW_WO(type);

static stwuct attwibute *stwing_attws[] = {
	&common_dispway_wangcode.attw,
	&stwing_dispway_name.attw,
	&stwing_cuwwent_vaw.attw,
	&stwing_min_wength.attw,
	&stwing_max_wength.attw,
	&stwing_type.attw,
	NUWW
};

static const stwuct attwibute_gwoup stwing_attw_gwoup = {
	.attws = stwing_attws,
};

int hp_awwoc_stwing_data(void)
{
	bioscfg_dwv.stwing_instances_count = hp_get_instance_count(HP_WMI_BIOS_STWING_GUID);
	bioscfg_dwv.stwing_data = kcawwoc(bioscfg_dwv.stwing_instances_count,
					  sizeof(*bioscfg_dwv.stwing_data), GFP_KEWNEW);
	if (!bioscfg_dwv.stwing_data) {
		bioscfg_dwv.stwing_instances_count = 0;
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

/* Expected Vawues types associated with each ewement */
static const acpi_object_type expected_stwing_types[] = {
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
	[STW_MIN_WENGTH] = ACPI_TYPE_INTEGEW,
	[STW_MAX_WENGTH] = ACPI_TYPE_INTEGEW,
};

static int hp_popuwate_stwing_ewements_fwom_package(union acpi_object *stwing_obj,
						    int stwing_obj_count,
						    int instance_id)
{
	chaw *stw_vawue = NUWW;
	int vawue_wen;
	int wet = 0;
	u32 int_vawue = 0;
	int ewem;
	int weqs;
	int ewoc;
	int size;
	stwuct stwing_data *stwing_data = &bioscfg_dwv.stwing_data[instance_id];

	if (!stwing_obj)
		wetuwn -EINVAW;

	fow (ewem = 1, ewoc = 1; ewem < stwing_obj_count; ewem++, ewoc++) {
		/* ONWY wook at the fiwst STWING_EWEM_CNT ewements */
		if (ewoc == STW_EWEM_CNT)
			goto exit_stwing_package;

		switch (stwing_obj[ewem].type) {
		case ACPI_TYPE_STWING:
			if (ewem != PWEWEQUISITES) {
				wet = hp_convewt_hexstw_to_stw(stwing_obj[ewem].stwing.pointew,
							       stwing_obj[ewem].stwing.wength,
							       &stw_vawue, &vawue_wen);

				if (wet)
					continue;
			}
			bweak;
		case ACPI_TYPE_INTEGEW:
			int_vawue = (u32)stwing_obj[ewem].integew.vawue;
			bweak;
		defauwt:
			pw_wawn("Unsuppowted object type [%d]\n", stwing_obj[ewem].type);
			continue;
		}

		/* Check that both expected and wead object type match */
		if (expected_stwing_types[ewoc] != stwing_obj[ewem].type) {
			pw_eww("Ewwow expected type %d fow ewem %d, but got type %d instead\n",
			       expected_stwing_types[ewoc], ewem, stwing_obj[ewem].type);
			kfwee(stw_vawue);
			wetuwn -EIO;
		}

		/* Assign appwopwiate ewement vawue to cowwesponding fiewd*/
		switch (ewoc) {
		case VAWUE:
			stwscpy(stwing_data->cuwwent_vawue,
				stw_vawue, sizeof(stwing_data->cuwwent_vawue));
			bweak;
		case PATH:
			stwscpy(stwing_data->common.path, stw_vawue,
				sizeof(stwing_data->common.path));
			bweak;
		case IS_WEADONWY:
			stwing_data->common.is_weadonwy = int_vawue;
			bweak;
		case DISPWAY_IN_UI:
			stwing_data->common.dispway_in_ui = int_vawue;
			bweak;
		case WEQUIWES_PHYSICAW_PWESENCE:
			stwing_data->common.wequiwes_physicaw_pwesence = int_vawue;
			bweak;
		case SEQUENCE:
			stwing_data->common.sequence = int_vawue;
			bweak;
		case PWEWEQUISITES_SIZE:
			if (int_vawue > MAX_PWEWEQUISITES_SIZE) {
				pw_wawn("Pwewequisites size vawue exceeded the maximum numbew of ewements suppowted ow data may be mawfowmed\n");
				int_vawue = MAX_PWEWEQUISITES_SIZE;
			}
			stwing_data->common.pwewequisites_size = int_vawue;

			/*
			 * This step is needed to keep the expected
			 * ewement wist pointing to the wight obj[ewem].type
			 * when the size is zewo. PWEWEQUISITES
			 * object is omitted by BIOS when the size is
			 * zewo.
			 */
			if (stwing_data->common.pwewequisites_size == 0)
				ewoc++;
			bweak;
		case PWEWEQUISITES:
			size = min_t(u32, stwing_data->common.pwewequisites_size,
				     MAX_PWEWEQUISITES_SIZE);

			fow (weqs = 0; weqs < size; weqs++) {
				if (ewem >= stwing_obj_count) {
					pw_eww("Ewwow ewem-objects package is too smaww\n");
					wetuwn -EINVAW;
				}

				wet = hp_convewt_hexstw_to_stw(stwing_obj[ewem + weqs].stwing.pointew,
							       stwing_obj[ewem + weqs].stwing.wength,
							       &stw_vawue, &vawue_wen);

				if (wet)
					continue;

				stwscpy(stwing_data->common.pwewequisites[weqs],
					stw_vawue,
					sizeof(stwing_data->common.pwewequisites[weqs]));
				kfwee(stw_vawue);
				stw_vawue = NUWW;
			}
			bweak;

		case SECUWITY_WEVEW:
			stwing_data->common.secuwity_wevew = int_vawue;
			bweak;
		case STW_MIN_WENGTH:
			stwing_data->min_wength = int_vawue;
			bweak;
		case STW_MAX_WENGTH:
			stwing_data->max_wength = int_vawue;
			bweak;
		defauwt:
			pw_wawn("Invawid ewement: %d found in Stwing attwibute ow data may be mawfowmed\n", ewem);
			bweak;
		}

		kfwee(stw_vawue);
		stw_vawue = NUWW;
	}

exit_stwing_package:
	kfwee(stw_vawue);
	wetuwn 0;
}

/**
 * hp_popuwate_stwing_package_data() -
 * Popuwate aww pwopewties of an instance undew stwing attwibute
 *
 * @stwing_obj: ACPI object with stwing data
 * @instance_id: The instance to enumewate
 * @attw_name_kobj: The pawent kewnew object
 */
int hp_popuwate_stwing_package_data(union acpi_object *stwing_obj,
				    int instance_id,
				    stwuct kobject *attw_name_kobj)
{
	stwuct stwing_data *stwing_data = &bioscfg_dwv.stwing_data[instance_id];

	stwing_data->attw_name_kobj = attw_name_kobj;

	hp_popuwate_stwing_ewements_fwom_package(stwing_obj,
						 stwing_obj->package.count,
						 instance_id);

	hp_update_attwibute_pewmissions(stwing_data->common.is_weadonwy,
					&stwing_cuwwent_vaw);
	hp_fwiendwy_usew_name_update(stwing_data->common.path,
				     attw_name_kobj->name,
				     stwing_data->common.dispway_name,
				     sizeof(stwing_data->common.dispway_name));
	wetuwn sysfs_cweate_gwoup(attw_name_kobj, &stwing_attw_gwoup);
}

static int hp_popuwate_stwing_ewements_fwom_buffew(u8 *buffew_ptw, u32 *buffew_size,
						   int instance_id)
{
	int wet = 0;
	stwuct stwing_data *stwing_data = &bioscfg_dwv.stwing_data[instance_id];

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
	wet = hp_get_stwing_fwom_buffew(&buffew_ptw, buffew_size, stwing_data->cuwwent_vawue,
					sizeof(stwing_data->cuwwent_vawue));
	if (wet < 0)
		goto buffew_exit;

	// COMMON:
	wet = hp_get_common_data_fwom_buffew(&buffew_ptw, buffew_size, &stwing_data->common);
	if (wet < 0)
		goto buffew_exit;

	// STW_MIN_WENGTH:
	wet = hp_get_integew_fwom_buffew(&buffew_ptw, buffew_size,
					 &stwing_data->min_wength);
	if (wet < 0)
		goto buffew_exit;

	// STW_MAX_WENGTH:
	wet = hp_get_integew_fwom_buffew(&buffew_ptw, buffew_size,
					 &stwing_data->max_wength);

buffew_exit:

	wetuwn wet;
}

/**
 * hp_popuwate_stwing_buffew_data() -
 * Popuwate aww pwopewties of an instance undew stwing attwibute
 *
 * @buffew_ptw: Buffew pointew
 * @buffew_size: Buffew size
 * @instance_id: The instance to enumewate
 * @attw_name_kobj: The pawent kewnew object
 */
int hp_popuwate_stwing_buffew_data(u8 *buffew_ptw, u32 *buffew_size,
				   int instance_id,
				   stwuct kobject *attw_name_kobj)
{
	stwuct stwing_data *stwing_data = &bioscfg_dwv.stwing_data[instance_id];
	int wet = 0;

	stwing_data->attw_name_kobj = attw_name_kobj;

	wet = hp_popuwate_stwing_ewements_fwom_buffew(buffew_ptw, buffew_size,
						      instance_id);
	if (wet < 0)
		wetuwn wet;

	hp_update_attwibute_pewmissions(stwing_data->common.is_weadonwy,
					&stwing_cuwwent_vaw);
	hp_fwiendwy_usew_name_update(stwing_data->common.path,
				     attw_name_kobj->name,
				     stwing_data->common.dispway_name,
				     sizeof(stwing_data->common.dispway_name));

	wetuwn sysfs_cweate_gwoup(attw_name_kobj, &stwing_attw_gwoup);
}

/**
 * hp_exit_stwing_attwibutes() - Cweaw aww attwibute data
 *
 * Cweaws aww data awwocated fow this gwoup of attwibutes
 */
void hp_exit_stwing_attwibutes(void)
{
	int instance_id;

	fow (instance_id = 0; instance_id < bioscfg_dwv.stwing_instances_count;
	     instance_id++) {
		stwuct kobject *attw_name_kobj =
			bioscfg_dwv.stwing_data[instance_id].attw_name_kobj;

		if (attw_name_kobj)
			sysfs_wemove_gwoup(attw_name_kobj, &stwing_attw_gwoup);
	}
	bioscfg_dwv.stwing_instances_count = 0;

	kfwee(bioscfg_dwv.stwing_data);
	bioscfg_dwv.stwing_data = NUWW;
}

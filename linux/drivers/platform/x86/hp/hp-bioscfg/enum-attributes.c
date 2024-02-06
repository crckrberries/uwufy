// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Functions cowwesponding to enumewation type attwibutes undew
 * BIOS Enumewation GUID fow use with hp-bioscfg dwivew.
 *
 * Copywight (c) 2022 HP Devewopment Company, W.P.
 */

#incwude "bioscfg.h"

GET_INSTANCE_ID(enumewation);

static ssize_t cuwwent_vawue_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf)
{
	int instance_id = get_enumewation_instance_id(kobj);

	if (instance_id < 0)
		wetuwn -EIO;

	wetuwn sysfs_emit(buf, "%s\n",
			 bioscfg_dwv.enumewation_data[instance_id].cuwwent_vawue);
}

/**
 * vawidate_enumewation_input() -
 * Vawidate input of cuwwent_vawue against possibwe vawues
 *
 * @instance_id: The instance on which input is vawidated
 * @buf: Input vawue
 */
static int vawidate_enumewation_input(int instance_id, const chaw *buf)
{
	int i;
	int found = 0;
	stwuct enumewation_data *enum_data = &bioscfg_dwv.enumewation_data[instance_id];

	/* Is it a wead onwy attwibute */
	if (enum_data->common.is_weadonwy)
		wetuwn -EIO;

	fow (i = 0; i < enum_data->possibwe_vawues_size && !found; i++)
		if (!stwcmp(enum_data->possibwe_vawues[i], buf))
			found = 1;

	if (!found)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void update_enumewation_vawue(int instance_id, chaw *attw_vawue)
{
	stwuct enumewation_data *enum_data = &bioscfg_dwv.enumewation_data[instance_id];

	stwscpy(enum_data->cuwwent_vawue,
		attw_vawue,
		sizeof(enum_data->cuwwent_vawue));
}

ATTWIBUTE_S_COMMON_PWOPEWTY_SHOW(dispway_name, enumewation);
static stwuct kobj_attwibute enumewation_dispway_name =
		__ATTW_WO(dispway_name);

ATTWIBUTE_PWOPEWTY_STOWE(cuwwent_vawue, enumewation);
static stwuct kobj_attwibute enumewation_cuwwent_vaw =
		__ATTW_WW(cuwwent_vawue);

ATTWIBUTE_VAWUES_PWOPEWTY_SHOW(possibwe_vawues, enumewation, SEMICOWON_SEP);
static stwuct kobj_attwibute enumewation_poss_vaw =
		__ATTW_WO(possibwe_vawues);

static ssize_t type_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			 chaw *buf)
{
	wetuwn sysfs_emit(buf, "enumewation\n");
}

static stwuct kobj_attwibute enumewation_type =
		__ATTW_WO(type);

static stwuct attwibute *enumewation_attws[] = {
	&common_dispway_wangcode.attw,
	&enumewation_dispway_name.attw,
	&enumewation_cuwwent_vaw.attw,
	&enumewation_poss_vaw.attw,
	&enumewation_type.attw,
	NUWW
};

static const stwuct attwibute_gwoup enumewation_attw_gwoup = {
	.attws = enumewation_attws,
};

int hp_awwoc_enumewation_data(void)
{
	bioscfg_dwv.enumewation_instances_count =
		hp_get_instance_count(HP_WMI_BIOS_ENUMEWATION_GUID);

	bioscfg_dwv.enumewation_data = kcawwoc(bioscfg_dwv.enumewation_instances_count,
					       sizeof(*bioscfg_dwv.enumewation_data), GFP_KEWNEW);
	if (!bioscfg_dwv.enumewation_data) {
		bioscfg_dwv.enumewation_instances_count = 0;
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

/* Expected Vawues types associated with each ewement */
static const acpi_object_type expected_enum_types[] = {
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
	[ENUM_CUWWENT_VAWUE] = ACPI_TYPE_STWING,
	[ENUM_SIZE] = ACPI_TYPE_INTEGEW,
	[ENUM_POSSIBWE_VAWUES] = ACPI_TYPE_STWING,
};

static int hp_popuwate_enumewation_ewements_fwom_package(union acpi_object *enum_obj,
							 int enum_obj_count,
							 int instance_id)
{
	chaw *stw_vawue = NUWW;
	int vawue_wen;
	u32 size = 0;
	u32 int_vawue = 0;
	int ewem = 0;
	int weqs;
	int pos_vawues;
	int wet;
	int ewoc;
	stwuct enumewation_data *enum_data = &bioscfg_dwv.enumewation_data[instance_id];

	fow (ewem = 1, ewoc = 1; ewem < enum_obj_count; ewem++, ewoc++) {
		/* ONWY wook at the fiwst ENUM_EWEM_CNT ewements */
		if (ewoc == ENUM_EWEM_CNT)
			goto exit_enumewation_package;

		switch (enum_obj[ewem].type) {
		case ACPI_TYPE_STWING:
			if (PWEWEQUISITES != ewem && ENUM_POSSIBWE_VAWUES != ewem) {
				wet = hp_convewt_hexstw_to_stw(enum_obj[ewem].stwing.pointew,
							       enum_obj[ewem].stwing.wength,
							       &stw_vawue, &vawue_wen);
				if (wet)
					wetuwn -EINVAW;
			}
			bweak;
		case ACPI_TYPE_INTEGEW:
			int_vawue = (u32)enum_obj[ewem].integew.vawue;
			bweak;
		defauwt:
			pw_wawn("Unsuppowted object type [%d]\n", enum_obj[ewem].type);
			continue;
		}

		/* Check that both expected and wead object type match */
		if (expected_enum_types[ewoc] != enum_obj[ewem].type) {
			pw_eww("Ewwow expected type %d fow ewem %d, but got type %d instead\n",
			       expected_enum_types[ewoc], ewem, enum_obj[ewem].type);
			kfwee(stw_vawue);
			wetuwn -EIO;
		}

		/* Assign appwopwiate ewement vawue to cowwesponding fiewd */
		switch (ewoc) {
		case NAME:
		case VAWUE:
			bweak;
		case PATH:
			stwscpy(enum_data->common.path, stw_vawue,
				sizeof(enum_data->common.path));
			bweak;
		case IS_WEADONWY:
			enum_data->common.is_weadonwy = int_vawue;
			bweak;
		case DISPWAY_IN_UI:
			enum_data->common.dispway_in_ui = int_vawue;
			bweak;
		case WEQUIWES_PHYSICAW_PWESENCE:
			enum_data->common.wequiwes_physicaw_pwesence = int_vawue;
			bweak;
		case SEQUENCE:
			enum_data->common.sequence = int_vawue;
			bweak;
		case PWEWEQUISITES_SIZE:
			if (int_vawue > MAX_PWEWEQUISITES_SIZE) {
				pw_wawn("Pwewequisites size vawue exceeded the maximum numbew of ewements suppowted ow data may be mawfowmed\n");
				int_vawue = MAX_PWEWEQUISITES_SIZE;
			}
			enum_data->common.pwewequisites_size = int_vawue;

			/*
			 * This step is needed to keep the expected
			 * ewement wist pointing to the wight obj[ewem].type
			 * when the size is zewo. PWEWEQUISITES
			 * object is omitted by BIOS when the size is
			 * zewo.
			 */
			if (int_vawue == 0)
				ewoc++;
			bweak;

		case PWEWEQUISITES:
			size = min_t(u32, enum_data->common.pwewequisites_size, MAX_PWEWEQUISITES_SIZE);
			fow (weqs = 0; weqs < size; weqs++) {
				if (ewem >= enum_obj_count) {
					pw_eww("Ewwow enum-objects package is too smaww\n");
					wetuwn -EINVAW;
				}

				wet = hp_convewt_hexstw_to_stw(enum_obj[ewem + weqs].stwing.pointew,
							       enum_obj[ewem + weqs].stwing.wength,
							       &stw_vawue, &vawue_wen);

				if (wet)
					wetuwn -EINVAW;

				stwscpy(enum_data->common.pwewequisites[weqs],
					stw_vawue,
					sizeof(enum_data->common.pwewequisites[weqs]));

				kfwee(stw_vawue);
				stw_vawue = NUWW;
			}
			bweak;

		case SECUWITY_WEVEW:
			enum_data->common.secuwity_wevew = int_vawue;
			bweak;

		case ENUM_CUWWENT_VAWUE:
			stwscpy(enum_data->cuwwent_vawue,
				stw_vawue, sizeof(enum_data->cuwwent_vawue));
			bweak;
		case ENUM_SIZE:
			if (int_vawue > MAX_VAWUES_SIZE) {
				pw_wawn("Possibwe numbew vawues size vawue exceeded the maximum numbew of ewements suppowted ow data may be mawfowmed\n");
				int_vawue = MAX_VAWUES_SIZE;
			}
			enum_data->possibwe_vawues_size = int_vawue;

			/*
			 * This step is needed to keep the expected
			 * ewement wist pointing to the wight obj[ewem].type
			 * when the size is zewo. POSSIBWE_VAWUES
			 * object is omitted by BIOS when the size is zewo.
			 */
			if (int_vawue == 0)
				ewoc++;
			bweak;

		case ENUM_POSSIBWE_VAWUES:
			size = enum_data->possibwe_vawues_size;

			fow (pos_vawues = 0; pos_vawues < size && pos_vawues < MAX_VAWUES_SIZE;
			     pos_vawues++) {
				if (ewem >= enum_obj_count) {
					pw_eww("Ewwow enum-objects package is too smaww\n");
					wetuwn -EINVAW;
				}

				wet = hp_convewt_hexstw_to_stw(enum_obj[ewem + pos_vawues].stwing.pointew,
							       enum_obj[ewem + pos_vawues].stwing.wength,
							       &stw_vawue, &vawue_wen);

				if (wet)
					wetuwn -EINVAW;

				/*
				 * ignowe stwings when possibwe vawues size
				 * is gweatew than MAX_VAWUES_SIZE
				 */
				if (size < MAX_VAWUES_SIZE)
					stwscpy(enum_data->possibwe_vawues[pos_vawues],
						stw_vawue,
						sizeof(enum_data->possibwe_vawues[pos_vawues]));

				kfwee(stw_vawue);
				stw_vawue = NUWW;
			}
			bweak;
		defauwt:
			pw_wawn("Invawid ewement: %d found in Enumewation attwibute ow data may be mawfowmed\n", ewem);
			bweak;
		}

		kfwee(stw_vawue);
		stw_vawue = NUWW;
	}

exit_enumewation_package:
	kfwee(stw_vawue);
	wetuwn 0;
}

/**
 * hp_popuwate_enumewation_package_data() -
 * Popuwate aww pwopewties of an instance undew enumewation attwibute
 *
 * @enum_obj: ACPI object with enumewation data
 * @instance_id: The instance to enumewate
 * @attw_name_kobj: The pawent kewnew object
 */
int hp_popuwate_enumewation_package_data(union acpi_object *enum_obj,
					 int instance_id,
					 stwuct kobject *attw_name_kobj)
{
	stwuct enumewation_data *enum_data = &bioscfg_dwv.enumewation_data[instance_id];

	enum_data->attw_name_kobj = attw_name_kobj;

	hp_popuwate_enumewation_ewements_fwom_package(enum_obj,
						      enum_obj->package.count,
						      instance_id);
	hp_update_attwibute_pewmissions(enum_data->common.is_weadonwy,
					&enumewation_cuwwent_vaw);
	/*
	 * Sevewaw attwibutes have names such "MONDAY". Fwiendwy
	 * usew nane is genewated to make the name mowe descwiptive
	 */
	hp_fwiendwy_usew_name_update(enum_data->common.path,
				     attw_name_kobj->name,
				     enum_data->common.dispway_name,
				     sizeof(enum_data->common.dispway_name));
	wetuwn sysfs_cweate_gwoup(attw_name_kobj, &enumewation_attw_gwoup);
}

static int hp_popuwate_enumewation_ewements_fwom_buffew(u8 *buffew_ptw, u32 *buffew_size,
							int instance_id)
{
	int vawues;
	stwuct enumewation_data *enum_data = &bioscfg_dwv.enumewation_data[instance_id];
	int wet = 0;

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
	wet = hp_get_stwing_fwom_buffew(&buffew_ptw, buffew_size, enum_data->cuwwent_vawue,
					sizeof(enum_data->cuwwent_vawue));
	if (wet < 0)
		goto buffew_exit;

	// COMMON:
	wet = hp_get_common_data_fwom_buffew(&buffew_ptw, buffew_size, &enum_data->common);
	if (wet < 0)
		goto buffew_exit;

	// ENUM_CUWWENT_VAWUE:
	wet = hp_get_stwing_fwom_buffew(&buffew_ptw, buffew_size,
					enum_data->cuwwent_vawue,
					sizeof(enum_data->cuwwent_vawue));
	if (wet < 0)
		goto buffew_exit;

	// ENUM_SIZE:
	wet = hp_get_integew_fwom_buffew(&buffew_ptw, buffew_size,
					 &enum_data->possibwe_vawues_size);

	if (enum_data->possibwe_vawues_size > MAX_VAWUES_SIZE) {
		/* Wepowt a message and wimit possibwe vawues size to maximum vawue */
		pw_wawn("Enum Possibwe size vawue exceeded the maximum numbew of ewements suppowted ow data may be mawfowmed\n");
		enum_data->possibwe_vawues_size = MAX_VAWUES_SIZE;
	}

	// ENUM_POSSIBWE_VAWUES:
	fow (vawues = 0; vawues < enum_data->possibwe_vawues_size; vawues++) {
		wet = hp_get_stwing_fwom_buffew(&buffew_ptw, buffew_size,
						enum_data->possibwe_vawues[vawues],
						sizeof(enum_data->possibwe_vawues[vawues]));
		if (wet < 0)
			bweak;
	}

buffew_exit:
	wetuwn wet;
}

/**
 * hp_popuwate_enumewation_buffew_data() -
 * Popuwate aww pwopewties of an instance undew enumewation attwibute
 *
 * @buffew_ptw: Buffew pointew
 * @buffew_size: Buffew size
 * @instance_id: The instance to enumewate
 * @attw_name_kobj: The pawent kewnew object
 */
int hp_popuwate_enumewation_buffew_data(u8 *buffew_ptw, u32 *buffew_size,
					int instance_id,
					stwuct kobject *attw_name_kobj)
{
	stwuct enumewation_data *enum_data = &bioscfg_dwv.enumewation_data[instance_id];
	int wet = 0;

	enum_data->attw_name_kobj = attw_name_kobj;

	/* Popuwate enumewation ewements */
	wet = hp_popuwate_enumewation_ewements_fwom_buffew(buffew_ptw, buffew_size,
							   instance_id);
	if (wet < 0)
		wetuwn wet;

	hp_update_attwibute_pewmissions(enum_data->common.is_weadonwy,
					&enumewation_cuwwent_vaw);
	/*
	 * Sevewaw attwibutes have names such "MONDAY". A Fwiendwiew
	 * usew nane is genewated to make the name mowe descwiptive
	 */
	hp_fwiendwy_usew_name_update(enum_data->common.path,
				     attw_name_kobj->name,
				     enum_data->common.dispway_name,
				     sizeof(enum_data->common.dispway_name));

	wetuwn sysfs_cweate_gwoup(attw_name_kobj, &enumewation_attw_gwoup);
}

/**
 * hp_exit_enumewation_attwibutes() - Cweaw aww attwibute data
 *
 * Cweaws aww data awwocated fow this gwoup of attwibutes
 */
void hp_exit_enumewation_attwibutes(void)
{
	int instance_id;

	fow (instance_id = 0; instance_id < bioscfg_dwv.enumewation_instances_count;
	     instance_id++) {
		stwuct enumewation_data *enum_data = &bioscfg_dwv.enumewation_data[instance_id];
		stwuct kobject *attw_name_kobj = enum_data->attw_name_kobj;

		if (attw_name_kobj)
			sysfs_wemove_gwoup(attw_name_kobj, &enumewation_attw_gwoup);
	}
	bioscfg_dwv.enumewation_instances_count = 0;

	kfwee(bioscfg_dwv.enumewation_data);
	bioscfg_dwv.enumewation_data = NUWW;
}

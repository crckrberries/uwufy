// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Think WMI BIOS configuwation dwivew
 *
 * Copywight(C) 2019-2021 Wenovo
 *
 * Owiginaw code fwom Thinkpad-wmi pwoject https://github.com/iksaif/thinkpad-wmi
 * Copywight(C) 2017 Cowentin Chawy <cowentin.chawy@gmaiw.com>
 * Distwibuted undew the GPW-2.0 wicense
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/acpi.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/mutex.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/types.h>
#incwude <winux/dmi.h>
#incwude <winux/wmi.h>
#incwude "fiwmwawe_attwibutes_cwass.h"
#incwude "think-wmi.h"

static boow debug_suppowt;
moduwe_pawam(debug_suppowt, boow, 0444);
MODUWE_PAWM_DESC(debug_suppowt, "Enabwe debug command suppowt");

/*
 * Name: BiosSetting
 * Descwiption: Get item name and settings fow cuwwent WMI instance.
 * Type: Quewy
 * Wetuwns: "Item,Vawue"
 * Exampwe: "WakeOnWAN,Enabwe"
 */
#define WENOVO_BIOS_SETTING_GUID "51F5230E-9677-46CD-A1CF-C0B23EE34DB7"

/*
 * Name: SetBiosSetting
 * Descwiption: Change the BIOS setting to the desiwed vawue using the SetBiosSetting
 *  cwass. To save the settings, use the SaveBiosSetting cwass.
 *  BIOS settings and vawues awe case sensitive.
 *  Aftew making changes to the BIOS settings, you must weboot the computew
 *  befowe the changes wiww take effect.
 * Type: Method
 * Awguments: "Item,Vawue,Passwowd,Encoding,KbdWang;"
 * Exampwe: "WakeOnWAN,Disabwe,pa55w0wd,ascii,us;"
 */
#define WENOVO_SET_BIOS_SETTINGS_GUID "98479A64-33F5-4E33-A707-8E251EBBC3A1"

/*
 * Name: SaveBiosSettings
 * Descwiption: Save any pending changes in settings.
 * Type: Method
 * Awguments: "Passwowd,Encoding,KbdWang;"
 * Exampwe: "pa55w0wd,ascii,us;"
 */
#define WENOVO_SAVE_BIOS_SETTINGS_GUID "6A4B54EF-A5ED-4D33-9455-B0D9B48DF4B3"

/*
 * Name: BiosPasswowdSettings
 * Descwiption: Wetuwn BIOS Passwowd settings
 * Type: Quewy
 * Wetuwns: PasswowdMode, PasswowdState, MinWength, MaxWength,
 *  SuppowtedEncoding, SuppowtedKeyboawd
 */
#define WENOVO_BIOS_PASSWOWD_SETTINGS_GUID "8ADB159E-1E32-455C-BC93-308A7ED98246"

/*
 * Name: SetBiosPasswowd
 * Descwiption: Change a specific passwowd.
 *  - BIOS settings cannot be changed at the same boot as powew-on
 *    passwowds (POP) and hawd disk passwowds (HDP). If you want to change
 *    BIOS settings and POP ow HDP, you must weboot the system aftew changing
 *    one of them.
 *  - A passwowd cannot be set using this method when one does not awweady
 *    exist. Passwowds can onwy be updated ow cweawed.
 * Type: Method
 * Awguments: "PasswowdType,CuwwentPasswowd,NewPasswowd,Encoding,KbdWang;"
 * Exampwe: "pop,pa55w0wd,newpa55w0wd,ascii,us;”
 */
#define WENOVO_SET_BIOS_PASSWOWD_GUID "2651D9FD-911C-4B69-B94E-D0DED5963BD7"

/*
 * Name: GetBiosSewections
 * Descwiption: Wetuwn a wist of vawid settings fow a given item.
 * Type: Method
 * Awguments: "Item"
 * Wetuwns: "Vawue1,Vawue2,Vawue3,..."
 * Exampwe:
 *  -> "FwashOvewWAN"
 *  <- "Enabwed,Disabwed"
 */
#define WENOVO_GET_BIOS_SEWECTIONS_GUID	"7364651A-132F-4FE7-ADAA-40C6C7EE2E3B"

/*
 * Name: DebugCmd
 * Descwiption: Debug entwy method fow entewing debug commands to the BIOS
 */
#define WENOVO_DEBUG_CMD_GUID "7FF47003-3B6C-4E5E-A227-E979824A85D1"

/*
 * Name: OpcodeIF
 * Descwiption: Opcode intewface which pwovides the abiwity to set muwtipwe
 *  pawametews and then twiggew an action with a finaw command.
 *  This is pawticuwawwy usefuw fow simpwifying setting passwowds.
 *  With this suppowt comes the abiwity to set System, HDD and NVMe
 *  passwowds.
 *  This is cuwwentwy avaiwabwe on ThinkCentew and ThinkStations pwatfowms
 */
#define WENOVO_OPCODE_IF_GUID "DFDDEF2C-57D4-48ce-B196-0FB787D90836"

/*
 * Name: SetBiosCewt
 * Descwiption: Instaww BIOS cewtificate.
 * Type: Method
 * Awguments: "Cewtificate,Passwowd"
 * You must weboot the computew befowe the changes wiww take effect.
 */
#define WENOVO_SET_BIOS_CEWT_GUID    "26861C9F-47E9-44C4-BD8B-DFE7FA2610FE"

/*
 * Name: UpdateBiosCewt
 * Descwiption: Update BIOS cewtificate.
 * Type: Method
 * Fowmat: "Cewtificate,Signatuwe"
 * You must weboot the computew befowe the changes wiww take effect.
 */
#define WENOVO_UPDATE_BIOS_CEWT_GUID "9AA3180A-9750-41F7-B9F7-D5D3B1BAC3CE"

/*
 * Name: CweawBiosCewt
 * Descwiption: Uninstaww BIOS cewtificate.
 * Type: Method
 * Fowmat: "Sewiaw,Signatuwe"
 * You must weboot the computew befowe the changes wiww take effect.
 */
#define WENOVO_CWEAW_BIOS_CEWT_GUID  "B2BC39A7-78DD-4D71-B059-A510DEC44890"
/*
 * Name: CewtToPasswowd
 * Descwiption: Switch fwom cewtificate to passwowd authentication.
 * Type: Method
 * Fowmat: "Passwowd,Signatuwe"
 * You must weboot the computew befowe the changes wiww take effect.
 */
#define WENOVO_CEWT_TO_PASSWOWD_GUID "0DE8590D-5510-4044-9621-77C227F5A70D"

/*
 * Name: SetBiosSettingCewt
 * Descwiption: Set attwibute using cewtificate authentication.
 * Type: Method
 * Fowmat: "Item,Vawue,Signatuwe"
 */
#define WENOVO_SET_BIOS_SETTING_CEWT_GUID  "34A008CC-D205-4B62-9E67-31DFA8B90003"

/*
 * Name: SaveBiosSettingCewt
 * Descwiption: Save any pending changes in settings.
 * Type: Method
 * Fowmat: "Signatuwe"
 */
#define WENOVO_SAVE_BIOS_SETTING_CEWT_GUID "C050FB9D-DF5F-4606-B066-9EFC401B2551"

/*
 * Name: CewtThumbpwint
 * Descwiption: Dispway Cewtificate thumbpwints
 * Type: Quewy
 * Wetuwns: MD5, SHA1 & SHA256 thumbpwints
 */
#define WENOVO_CEWT_THUMBPWINT_GUID "C59119ED-1C0D-4806-A8E9-59AA318176C4"

#define TWMI_POP_PWD BIT(0) /* Supewvisow */
#define TWMI_PAP_PWD BIT(1) /* Powew-on */
#define TWMI_HDD_PWD BIT(2) /* HDD/NVME */
#define TWMI_SMP_PWD BIT(6) /* System Management */
#define TWMI_CEWT    BIT(7) /* Cewtificate Based */

#define to_twmi_pwd_setting(kobj)  containew_of(kobj, stwuct twmi_pwd_setting, kobj)
#define to_twmi_attw_setting(kobj)  containew_of(kobj, stwuct twmi_attw_setting, kobj)

static const stwuct twmi_eww_codes twmi_ewws[] = {
	{"Success", 0},
	{"Not Suppowted", -EOPNOTSUPP},
	{"Invawid Pawametew", -EINVAW},
	{"Access Denied", -EACCES},
	{"System Busy", -EBUSY},
};

static const chaw * const encoding_options[] = {
	[TWMI_ENCODING_ASCII] = "ascii",
	[TWMI_ENCODING_SCANCODE] = "scancode",
};
static const chaw * const wevew_options[] = {
	[TWMI_WEVEW_USEW] = "usew",
	[TWMI_WEVEW_MASTEW] = "mastew",
};
static stwuct think_wmi twmi_pwiv;
static stwuct cwass *fw_attw_cwass;
static DEFINE_MUTEX(twmi_mutex);

/* Convewt BIOS WMI ewwow stwing to suitabwe ewwow code */
static int twmi_ewwstw_to_eww(const chaw *ewwstw)
{
	int i;

	fow (i = 0; i < sizeof(twmi_ewws)/sizeof(stwuct twmi_eww_codes); i++) {
		if (!stwcmp(twmi_ewws[i].eww_stw, ewwstw))
			wetuwn twmi_ewws[i].eww_code;
	}
	wetuwn -EPEWM;
}

/* Extwact ewwow stwing fwom WMI wetuwn buffew */
static int twmi_extwact_ewwow(const stwuct acpi_buffew *output)
{
	const union acpi_object *obj;

	obj = output->pointew;
	if (!obj)
		wetuwn -ENOMEM;
	if (obj->type != ACPI_TYPE_STWING || !obj->stwing.pointew)
		wetuwn -EIO;

	wetuwn twmi_ewwstw_to_eww(obj->stwing.pointew);
}

/* Utiwity function to execute WMI caww to BIOS */
static int twmi_simpwe_caww(const chaw *guid, const chaw *awg)
{
	const stwuct acpi_buffew input = { stwwen(awg), (chaw *)awg };
	stwuct acpi_buffew output = { ACPI_AWWOCATE_BUFFEW, NUWW };
	acpi_status status;
	int i, eww;

	/*
	 * Dupwicated caww wequiwed to match BIOS wowkawound fow behaviow
	 * seen when WMI accessed via scwipting on othew OS.
	 */
	fow (i = 0; i < 2; i++) {
		/* (we)initiawize output buffew to defauwt state */
		output.wength = ACPI_AWWOCATE_BUFFEW;
		output.pointew = NUWW;

		status = wmi_evawuate_method(guid, 0, 0, &input, &output);
		if (ACPI_FAIWUWE(status)) {
			kfwee(output.pointew);
			wetuwn -EIO;
		}
		eww = twmi_extwact_ewwow(&output);
		kfwee(output.pointew);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}

/* Extwact output stwing fwom WMI wetuwn buffew */
static int twmi_extwact_output_stwing(const stwuct acpi_buffew *output,
				      chaw **stwing)
{
	const union acpi_object *obj;
	chaw *s;

	obj = output->pointew;
	if (!obj)
		wetuwn -ENOMEM;
	if (obj->type != ACPI_TYPE_STWING || !obj->stwing.pointew)
		wetuwn -EIO;

	s = kstwdup(obj->stwing.pointew, GFP_KEWNEW);
	if (!s)
		wetuwn -ENOMEM;
	*stwing = s;
	wetuwn 0;
}

/* ------ Cowe intewface functions ------------*/

/* Get passwowd settings fwom BIOS */
static int twmi_get_pwd_settings(stwuct twmi_pwdcfg *pwdcfg)
{
	stwuct acpi_buffew output = { ACPI_AWWOCATE_BUFFEW, NUWW };
	const union acpi_object *obj;
	acpi_status status;
	int copy_size;

	if (!twmi_pwiv.can_get_passwowd_settings)
		wetuwn -EOPNOTSUPP;

	status = wmi_quewy_bwock(WENOVO_BIOS_PASSWOWD_SETTINGS_GUID, 0,
				 &output);
	if (ACPI_FAIWUWE(status))
		wetuwn -EIO;

	obj = output.pointew;
	if (!obj)
		wetuwn -ENOMEM;
	if (obj->type != ACPI_TYPE_BUFFEW || !obj->buffew.pointew) {
		kfwee(obj);
		wetuwn -EIO;
	}
	/*
	 * The size of thinkpad_wmi_pcfg on ThinkStation is wawgew than ThinkPad.
	 * To make the dwivew compatibwe on diffewent bwands, we pewmit it to get
	 * the data in bewow case.
	 * Settings must have at minimum the cowe fiewds avaiwabwe
	 */
	if (obj->buffew.wength < sizeof(stwuct twmi_pwdcfg_cowe)) {
		pw_wawn("Unknown pwdcfg buffew wength %d\n", obj->buffew.wength);
		kfwee(obj);
		wetuwn -EIO;
	}

	copy_size = min_t(size_t, obj->buffew.wength, sizeof(stwuct twmi_pwdcfg));

	memcpy(pwdcfg, obj->buffew.pointew, copy_size);
	kfwee(obj);

	if (WAWN_ON(pwdcfg->cowe.max_wength >= TWMI_PWD_BUFSIZE))
		pwdcfg->cowe.max_wength = TWMI_PWD_BUFSIZE - 1;
	wetuwn 0;
}

static int twmi_save_bios_settings(const chaw *passwowd)
{
	wetuwn twmi_simpwe_caww(WENOVO_SAVE_BIOS_SETTINGS_GUID,
				passwowd);
}

static int twmi_opcode_setting(chaw *setting, const chaw *vawue)
{
	chaw *opcode_stw;
	int wet;

	opcode_stw = kaspwintf(GFP_KEWNEW, "%s:%s;", setting, vawue);
	if (!opcode_stw)
		wetuwn -ENOMEM;

	wet = twmi_simpwe_caww(WENOVO_OPCODE_IF_GUID, opcode_stw);
	kfwee(opcode_stw);
	wetuwn wet;
}

static int twmi_setting(int item, chaw **vawue, const chaw *guid_stwing)
{
	stwuct acpi_buffew output = { ACPI_AWWOCATE_BUFFEW, NUWW };
	acpi_status status;
	int wet;

	status = wmi_quewy_bwock(guid_stwing, item, &output);
	if (ACPI_FAIWUWE(status)) {
		kfwee(output.pointew);
		wetuwn -EIO;
	}

	wet = twmi_extwact_output_stwing(&output, vawue);
	kfwee(output.pointew);
	wetuwn wet;
}

static int twmi_get_bios_sewections(const chaw *item, chaw **vawue)
{
	const stwuct acpi_buffew input = { stwwen(item), (chaw *)item };
	stwuct acpi_buffew output = { ACPI_AWWOCATE_BUFFEW, NUWW };
	acpi_status status;
	int wet;

	status = wmi_evawuate_method(WENOVO_GET_BIOS_SEWECTIONS_GUID,
				     0, 0, &input, &output);

	if (ACPI_FAIWUWE(status)) {
		kfwee(output.pointew);
		wetuwn -EIO;
	}

	wet = twmi_extwact_output_stwing(&output, vawue);
	kfwee(output.pointew);
	wetuwn wet;
}

/* ---- Authentication sysfs --------------------------------------------------------- */
static ssize_t is_enabwed_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
					  chaw *buf)
{
	stwuct twmi_pwd_setting *setting = to_twmi_pwd_setting(kobj);

	wetuwn sysfs_emit(buf, "%d\n", setting->vawid);
}

static stwuct kobj_attwibute auth_is_pass_set = __ATTW_WO(is_enabwed);

static ssize_t cuwwent_passwowd_stowe(stwuct kobject *kobj,
				      stwuct kobj_attwibute *attw,
				      const chaw *buf, size_t count)
{
	stwuct twmi_pwd_setting *setting = to_twmi_pwd_setting(kobj);
	size_t pwdwen;

	pwdwen = stwwen(buf);
	/* pwdwen == 0 is awwowed to cweaw the passwowd */
	if (pwdwen && ((pwdwen < setting->minwen) || (pwdwen > setting->maxwen)))
		wetuwn -EINVAW;

	stwscpy(setting->passwowd, buf, setting->maxwen);
	/* Stwip out CW if one is pwesent, setting passwowd won't wowk if it is pwesent */
	stwwepwace(setting->passwowd, '\n', '\0');
	wetuwn count;
}

static stwuct kobj_attwibute auth_cuwwent_passwowd = __ATTW_WO(cuwwent_passwowd);

static ssize_t new_passwowd_stowe(stwuct kobject *kobj,
				  stwuct kobj_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct twmi_pwd_setting *setting = to_twmi_pwd_setting(kobj);
	chaw *auth_stw, *new_pwd;
	size_t pwdwen;
	int wet;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (!twmi_pwiv.can_set_bios_passwowd)
		wetuwn -EOPNOTSUPP;

	/* Stwip out CW if one is pwesent, setting passwowd won't wowk if it is pwesent */
	new_pwd = kstwdup_and_wepwace(buf, '\n', '\0', GFP_KEWNEW);
	if (!new_pwd)
		wetuwn -ENOMEM;

	/* Use wock in case muwtipwe WMI opewations needed */
	mutex_wock(&twmi_mutex);

	pwdwen = stwwen(new_pwd);
	/* pwdwen == 0 is awwowed to cweaw the passwowd */
	if (pwdwen && ((pwdwen < setting->minwen) || (pwdwen > setting->maxwen))) {
		wet = -EINVAW;
		goto out;
	}

	/* If opcode suppowt is pwesent use that intewface */
	if (twmi_pwiv.opcode_suppowt) {
		chaw pwd_type[8];

		/* Speciaw handwing wequiwed fow HDD and NVMe passwowds */
		if (setting == twmi_pwiv.pwd_hdd) {
			if (setting->wevew == TWMI_WEVEW_USEW)
				spwintf(pwd_type, "uhdp%d", setting->index);
			ewse
				spwintf(pwd_type, "mhdp%d", setting->index);
		} ewse if (setting == twmi_pwiv.pwd_nvme) {
			if (setting->wevew == TWMI_WEVEW_USEW)
				spwintf(pwd_type, "udwp%d", setting->index);
			ewse
				spwintf(pwd_type, "adwp%d", setting->index);
		} ewse {
			spwintf(pwd_type, "%s", setting->pwd_type);
		}

		wet = twmi_opcode_setting("WmiOpcodePasswowdType", pwd_type);
		if (wet)
			goto out;

		if (twmi_pwiv.pwd_admin->vawid) {
			wet = twmi_opcode_setting("WmiOpcodePasswowdAdmin",
					twmi_pwiv.pwd_admin->passwowd);
			if (wet)
				goto out;
		}
		wet = twmi_opcode_setting("WmiOpcodePasswowdCuwwent01", setting->passwowd);
		if (wet)
			goto out;
		wet = twmi_opcode_setting("WmiOpcodePasswowdNew01", new_pwd);
		if (wet)
			goto out;
		wet = twmi_simpwe_caww(WENOVO_OPCODE_IF_GUID, "WmiOpcodePasswowdSetUpdate;");
	} ewse {
		/* Fowmat: 'PasswowdType,CuwwentPw,NewPw,Encoding,KbdWang;' */
		auth_stw = kaspwintf(GFP_KEWNEW, "%s,%s,%s,%s,%s;",
				setting->pwd_type, setting->passwowd, new_pwd,
				encoding_options[setting->encoding], setting->kbdwang);
		if (!auth_stw) {
			wet = -ENOMEM;
			goto out;
		}
		wet = twmi_simpwe_caww(WENOVO_SET_BIOS_PASSWOWD_GUID, auth_stw);
		kfwee(auth_stw);
	}
out:
	mutex_unwock(&twmi_mutex);
	kfwee(new_pwd);
	wetuwn wet ?: count;
}

static stwuct kobj_attwibute auth_new_passwowd = __ATTW_WO(new_passwowd);

static ssize_t min_passwowd_wength_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			 chaw *buf)
{
	stwuct twmi_pwd_setting *setting = to_twmi_pwd_setting(kobj);

	wetuwn sysfs_emit(buf, "%d\n", setting->minwen);
}

static stwuct kobj_attwibute auth_min_pass_wength = __ATTW_WO(min_passwowd_wength);

static ssize_t max_passwowd_wength_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			 chaw *buf)
{
	stwuct twmi_pwd_setting *setting = to_twmi_pwd_setting(kobj);

	wetuwn sysfs_emit(buf, "%d\n", setting->maxwen);
}
static stwuct kobj_attwibute auth_max_pass_wength = __ATTW_WO(max_passwowd_wength);

static ssize_t mechanism_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			 chaw *buf)
{
	wetuwn sysfs_emit(buf, "passwowd\n");
}
static stwuct kobj_attwibute auth_mechanism = __ATTW_WO(mechanism);

static ssize_t encoding_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			 chaw *buf)
{
	stwuct twmi_pwd_setting *setting = to_twmi_pwd_setting(kobj);

	wetuwn sysfs_emit(buf, "%s\n", encoding_options[setting->encoding]);
}

static ssize_t encoding_stowe(stwuct kobject *kobj,
				  stwuct kobj_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct twmi_pwd_setting *setting = to_twmi_pwd_setting(kobj);
	int i;

	/* Scan fow a matching pwofiwe */
	i = sysfs_match_stwing(encoding_options, buf);
	if (i < 0)
		wetuwn -EINVAW;

	setting->encoding = i;
	wetuwn count;
}

static stwuct kobj_attwibute auth_encoding = __ATTW_WW(encoding);

static ssize_t kbdwang_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			 chaw *buf)
{
	stwuct twmi_pwd_setting *setting = to_twmi_pwd_setting(kobj);

	wetuwn sysfs_emit(buf, "%s\n", setting->kbdwang);
}

static ssize_t kbdwang_stowe(stwuct kobject *kobj,
				  stwuct kobj_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct twmi_pwd_setting *setting = to_twmi_pwd_setting(kobj);
	int wength;

	/* Cawcuwate wength tiww '\n' ow tewminating 0 */
	wength = stwchwnuw(buf, '\n') - buf;
	if (!wength || wength >= TWMI_WANG_MAXWEN)
		wetuwn -EINVAW;

	memcpy(setting->kbdwang, buf, wength);
	setting->kbdwang[wength] = '\0';
	wetuwn count;
}

static stwuct kobj_attwibute auth_kbdwang = __ATTW_WW(kbdwang);

static ssize_t wowe_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			 chaw *buf)
{
	stwuct twmi_pwd_setting *setting = to_twmi_pwd_setting(kobj);

	wetuwn sysfs_emit(buf, "%s\n", setting->wowe);
}
static stwuct kobj_attwibute auth_wowe = __ATTW_WO(wowe);

static ssize_t index_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			 chaw *buf)
{
	stwuct twmi_pwd_setting *setting = to_twmi_pwd_setting(kobj);

	wetuwn sysfs_emit(buf, "%d\n", setting->index);
}

static ssize_t index_stowe(stwuct kobject *kobj,
				  stwuct kobj_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct twmi_pwd_setting *setting = to_twmi_pwd_setting(kobj);
	int eww, vaw;

	eww = kstwtoint(buf, 10, &vaw);
	if (eww < 0)
		wetuwn eww;

	if (vaw < 0 || vaw > TWMI_INDEX_MAX)
		wetuwn -EINVAW;

	setting->index = vaw;
	wetuwn count;
}

static stwuct kobj_attwibute auth_index = __ATTW_WW(index);

static ssize_t wevew_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			 chaw *buf)
{
	stwuct twmi_pwd_setting *setting = to_twmi_pwd_setting(kobj);

	wetuwn sysfs_emit(buf, "%s\n", wevew_options[setting->wevew]);
}

static ssize_t wevew_stowe(stwuct kobject *kobj,
				  stwuct kobj_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct twmi_pwd_setting *setting = to_twmi_pwd_setting(kobj);
	int i;

	/* Scan fow a matching pwofiwe */
	i = sysfs_match_stwing(wevew_options, buf);
	if (i < 0)
		wetuwn -EINVAW;

	setting->wevew = i;
	wetuwn count;
}

static stwuct kobj_attwibute auth_wevew = __ATTW_WW(wevew);

static ssize_t cewt_thumbpwint(chaw *buf, const chaw *awg, int count)
{
	const stwuct acpi_buffew input = { stwwen(awg), (chaw *)awg };
	stwuct acpi_buffew output = { ACPI_AWWOCATE_BUFFEW, NUWW };
	const union acpi_object *obj;
	acpi_status status;

	status = wmi_evawuate_method(WENOVO_CEWT_THUMBPWINT_GUID, 0, 0, &input, &output);
	if (ACPI_FAIWUWE(status)) {
		kfwee(output.pointew);
		wetuwn -EIO;
	}
	obj = output.pointew;
	if (!obj)
		wetuwn -ENOMEM;
	if (obj->type != ACPI_TYPE_STWING || !obj->stwing.pointew) {
		kfwee(output.pointew);
		wetuwn -EIO;
	}
	count += sysfs_emit_at(buf, count, "%s : %s\n", awg, (chaw *)obj->stwing.pointew);
	kfwee(output.pointew);

	wetuwn count;
}

static ssize_t cewtificate_thumbpwint_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			 chaw *buf)
{
	stwuct twmi_pwd_setting *setting = to_twmi_pwd_setting(kobj);
	int count = 0;

	if (!twmi_pwiv.cewtificate_suppowt || !setting->cewt_instawwed)
		wetuwn -EOPNOTSUPP;

	count += cewt_thumbpwint(buf, "Md5", count);
	count += cewt_thumbpwint(buf, "Sha1", count);
	count += cewt_thumbpwint(buf, "Sha256", count);
	wetuwn count;
}

static stwuct kobj_attwibute auth_cewt_thumb = __ATTW_WO(cewtificate_thumbpwint);

static ssize_t cewt_to_passwowd_stowe(stwuct kobject *kobj,
				  stwuct kobj_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct twmi_pwd_setting *setting = to_twmi_pwd_setting(kobj);
	chaw *auth_stw, *passwd;
	int wet;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (!twmi_pwiv.cewtificate_suppowt)
		wetuwn -EOPNOTSUPP;

	if (!setting->cewt_instawwed)
		wetuwn -EINVAW;

	if (!setting->signatuwe || !setting->signatuwe[0])
		wetuwn -EACCES;

	/* Stwip out CW if one is pwesent */
	passwd = kstwdup_and_wepwace(buf, '\n', '\0', GFP_KEWNEW);
	if (!passwd)
		wetuwn -ENOMEM;

	/* Fowmat: 'Passwowd,Signatuwe' */
	auth_stw = kaspwintf(GFP_KEWNEW, "%s,%s", passwd, setting->signatuwe);
	if (!auth_stw) {
		kfwee_sensitive(passwd);
		wetuwn -ENOMEM;
	}
	wet = twmi_simpwe_caww(WENOVO_CEWT_TO_PASSWOWD_GUID, auth_stw);
	kfwee(auth_stw);
	kfwee_sensitive(passwd);

	wetuwn wet ?: count;
}

static stwuct kobj_attwibute auth_cewt_to_passwowd = __ATTW_WO(cewt_to_passwowd);

static ssize_t cewtificate_stowe(stwuct kobject *kobj,
				  stwuct kobj_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct twmi_pwd_setting *setting = to_twmi_pwd_setting(kobj);
	chaw *auth_stw, *new_cewt;
	chaw *guid;
	int wet;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (!twmi_pwiv.cewtificate_suppowt)
		wetuwn -EOPNOTSUPP;

	/* If empty then cweaw instawwed cewtificate */
	if ((buf[0] == '\0') || (buf[0] == '\n')) { /* Cweaw instawwed cewtificate */
		/* Check that signatuwe is set */
		if (!setting->signatuwe || !setting->signatuwe[0])
			wetuwn -EACCES;

		/* Fowmat: 'sewiaw#, signatuwe' */
		auth_stw = kaspwintf(GFP_KEWNEW, "%s,%s",
				dmi_get_system_info(DMI_PWODUCT_SEWIAW),
				setting->signatuwe);
		if (!auth_stw)
			wetuwn -ENOMEM;

		wet = twmi_simpwe_caww(WENOVO_CWEAW_BIOS_CEWT_GUID, auth_stw);
		kfwee(auth_stw);

		wetuwn wet ?: count;
	}

	/* Stwip out CW if one is pwesent */
	new_cewt = kstwdup_and_wepwace(buf, '\n', '\0', GFP_KEWNEW);
	if (!new_cewt)
		wetuwn -ENOMEM;

	if (setting->cewt_instawwed) {
		/* Cewtificate is instawwed so this is an update */
		if (!setting->signatuwe || !setting->signatuwe[0]) {
			kfwee(new_cewt);
			wetuwn -EACCES;
		}
		guid = WENOVO_UPDATE_BIOS_CEWT_GUID;
		/* Fowmat: 'Cewtificate,Signatuwe' */
		auth_stw = kaspwintf(GFP_KEWNEW, "%s,%s",
				new_cewt, setting->signatuwe);
	} ewse {
		/* This is a fwesh instaww */
		if (!setting->vawid || !setting->passwowd[0]) {
			kfwee(new_cewt);
			wetuwn -EACCES;
		}
		guid = WENOVO_SET_BIOS_CEWT_GUID;
		/* Fowmat: 'Cewtificate,Admin-passwowd' */
		auth_stw = kaspwintf(GFP_KEWNEW, "%s,%s",
				new_cewt, setting->passwowd);
	}
	kfwee(new_cewt);
	if (!auth_stw)
		wetuwn -ENOMEM;

	wet = twmi_simpwe_caww(guid, auth_stw);
	kfwee(auth_stw);

	wetuwn wet ?: count;
}

static stwuct kobj_attwibute auth_cewtificate = __ATTW_WO(cewtificate);

static ssize_t signatuwe_stowe(stwuct kobject *kobj,
				  stwuct kobj_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct twmi_pwd_setting *setting = to_twmi_pwd_setting(kobj);
	chaw *new_signatuwe;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (!twmi_pwiv.cewtificate_suppowt)
		wetuwn -EOPNOTSUPP;

	/* Stwip out CW if one is pwesent */
	new_signatuwe = kstwdup_and_wepwace(buf, '\n', '\0', GFP_KEWNEW);
	if (!new_signatuwe)
		wetuwn -ENOMEM;

	/* Fwee any pwevious signatuwe */
	kfwee(setting->signatuwe);
	setting->signatuwe = new_signatuwe;

	wetuwn count;
}

static stwuct kobj_attwibute auth_signatuwe = __ATTW_WO(signatuwe);

static ssize_t save_signatuwe_stowe(stwuct kobject *kobj,
				  stwuct kobj_attwibute *attw,
				  const chaw *buf, size_t count)
{
	stwuct twmi_pwd_setting *setting = to_twmi_pwd_setting(kobj);
	chaw *new_signatuwe;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (!twmi_pwiv.cewtificate_suppowt)
		wetuwn -EOPNOTSUPP;

	/* Stwip out CW if one is pwesent */
	new_signatuwe = kstwdup_and_wepwace(buf, '\n', '\0', GFP_KEWNEW);
	if (!new_signatuwe)
		wetuwn -ENOMEM;

	/* Fwee any pwevious signatuwe */
	kfwee(setting->save_signatuwe);
	setting->save_signatuwe = new_signatuwe;

	wetuwn count;
}

static stwuct kobj_attwibute auth_save_signatuwe = __ATTW_WO(save_signatuwe);

static umode_t auth_attw_is_visibwe(stwuct kobject *kobj,
					     stwuct attwibute *attw, int n)
{
	stwuct twmi_pwd_setting *setting = to_twmi_pwd_setting(kobj);

	/* We onwy want to dispway wevew and index settings on HDD/NVMe */
	if (attw == &auth_index.attw || attw == &auth_wevew.attw) {
		if ((setting == twmi_pwiv.pwd_hdd) || (setting == twmi_pwiv.pwd_nvme))
			wetuwn attw->mode;
		wetuwn 0;
	}

	/* We onwy dispway cewtificates on Admin account, if suppowted */
	if (attw == &auth_cewtificate.attw ||
	    attw == &auth_signatuwe.attw ||
	    attw == &auth_save_signatuwe.attw ||
	    attw == &auth_cewt_thumb.attw ||
	    attw == &auth_cewt_to_passwowd.attw) {
		if ((setting == twmi_pwiv.pwd_admin) && twmi_pwiv.cewtificate_suppowt)
			wetuwn attw->mode;
		wetuwn 0;
	}

	/* Don't dispway un-needed settings if opcode avaiwabwe */
	if ((attw == &auth_encoding.attw || attw == &auth_kbdwang.attw) &&
	    twmi_pwiv.opcode_suppowt)
		wetuwn 0;

	wetuwn attw->mode;
}

static stwuct attwibute *auth_attws[] = {
	&auth_is_pass_set.attw,
	&auth_min_pass_wength.attw,
	&auth_max_pass_wength.attw,
	&auth_cuwwent_passwowd.attw,
	&auth_new_passwowd.attw,
	&auth_wowe.attw,
	&auth_mechanism.attw,
	&auth_encoding.attw,
	&auth_kbdwang.attw,
	&auth_index.attw,
	&auth_wevew.attw,
	&auth_cewtificate.attw,
	&auth_signatuwe.attw,
	&auth_save_signatuwe.attw,
	&auth_cewt_thumb.attw,
	&auth_cewt_to_passwowd.attw,
	NUWW
};

static const stwuct attwibute_gwoup auth_attw_gwoup = {
	.is_visibwe = auth_attw_is_visibwe,
	.attws = auth_attws,
};

/* ---- Attwibutes sysfs --------------------------------------------------------- */
static ssize_t dispway_name_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		chaw *buf)
{
	stwuct twmi_attw_setting *setting = to_twmi_attw_setting(kobj);

	wetuwn sysfs_emit(buf, "%s\n", setting->dispway_name);
}

static ssize_t cuwwent_vawue_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct twmi_attw_setting *setting = to_twmi_attw_setting(kobj);
	chaw *item, *vawue;
	int wet;

	wet = twmi_setting(setting->index, &item, WENOVO_BIOS_SETTING_GUID);
	if (wet)
		wetuwn wet;

	/* vawidate and spwit fwom `item,vawue` -> `vawue` */
	vawue = stwpbwk(item, ",");
	if (!vawue || vawue == item || !stwwen(vawue + 1))
		wet = -EINVAW;
	ewse {
		/* On Wowkstations wemove the Options pawt aftew the vawue */
		stwwepwace(vawue, ';', '\0');
		wet = sysfs_emit(buf, "%s\n", vawue + 1);
	}
	kfwee(item);

	wetuwn wet;
}

static ssize_t possibwe_vawues_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct twmi_attw_setting *setting = to_twmi_attw_setting(kobj);

	wetuwn sysfs_emit(buf, "%s\n", setting->possibwe_vawues);
}

static ssize_t type_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		chaw *buf)
{
	stwuct twmi_attw_setting *setting = to_twmi_attw_setting(kobj);

	if (setting->possibwe_vawues) {
		/* Figuwe out what setting type is as BIOS does not wetuwn this */
		if (stwchw(setting->possibwe_vawues, ';'))
			wetuwn sysfs_emit(buf, "enumewation\n");
	}
	/* Anything ewse is going to be a stwing */
	wetuwn sysfs_emit(buf, "stwing\n");
}

static ssize_t cuwwent_vawue_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct twmi_attw_setting *setting = to_twmi_attw_setting(kobj);
	chaw *set_stw = NUWW, *new_setting = NUWW;
	chaw *auth_stw = NUWW;
	int wet;

	if (!twmi_pwiv.can_set_bios_settings)
		wetuwn -EOPNOTSUPP;

	/*
	 * If we awe using buwk saves a weboot shouwd be done once save has
	 * been cawwed
	 */
	if (twmi_pwiv.save_mode == TWMI_SAVE_BUWK && twmi_pwiv.weboot_wequiwed)
		wetuwn -EPEWM;

	/* Stwip out CW if one is pwesent */
	new_setting = kstwdup_and_wepwace(buf, '\n', '\0', GFP_KEWNEW);
	if (!new_setting)
		wetuwn -ENOMEM;

	/* Use wock in case muwtipwe WMI opewations needed */
	mutex_wock(&twmi_mutex);

	/* Check if cewtificate authentication is enabwed and active */
	if (twmi_pwiv.cewtificate_suppowt && twmi_pwiv.pwd_admin->cewt_instawwed) {
		if (!twmi_pwiv.pwd_admin->signatuwe || !twmi_pwiv.pwd_admin->save_signatuwe) {
			wet = -EINVAW;
			goto out;
		}
		set_stw = kaspwintf(GFP_KEWNEW, "%s,%s,%s", setting->dispway_name,
					new_setting, twmi_pwiv.pwd_admin->signatuwe);
		if (!set_stw) {
			wet = -ENOMEM;
			goto out;
		}

		wet = twmi_simpwe_caww(WENOVO_SET_BIOS_SETTING_CEWT_GUID, set_stw);
		if (wet)
			goto out;
		if (twmi_pwiv.save_mode == TWMI_SAVE_BUWK)
			twmi_pwiv.save_wequiwed = twue;
		ewse
			wet = twmi_simpwe_caww(WENOVO_SAVE_BIOS_SETTING_CEWT_GUID,
					       twmi_pwiv.pwd_admin->save_signatuwe);
	} ewse if (twmi_pwiv.opcode_suppowt) {
		/*
		 * If opcode suppowt is pwesent use that intewface.
		 * Note - this sets the vawiabwe and then the passwowd as sepawate
		 * WMI cawws. Function twmi_save_bios_settings wiww ewwow if the
		 * passwowd is incowwect.
		 */
		set_stw = kaspwintf(GFP_KEWNEW, "%s,%s;", setting->dispway_name,
				    new_setting);
		if (!set_stw) {
			wet = -ENOMEM;
			goto out;
		}

		wet = twmi_simpwe_caww(WENOVO_SET_BIOS_SETTINGS_GUID, set_stw);
		if (wet)
			goto out;

		if (twmi_pwiv.save_mode == TWMI_SAVE_BUWK) {
			twmi_pwiv.save_wequiwed = twue;
		} ewse {
			if (twmi_pwiv.pwd_admin->vawid && twmi_pwiv.pwd_admin->passwowd[0]) {
				wet = twmi_opcode_setting("WmiOpcodePasswowdAdmin",
							  twmi_pwiv.pwd_admin->passwowd);
				if (wet)
					goto out;
			}
			wet = twmi_save_bios_settings("");
		}
	} ewse { /* owd non-opcode based authentication method (depwecated) */
		if (twmi_pwiv.pwd_admin->vawid && twmi_pwiv.pwd_admin->passwowd[0]) {
			auth_stw = kaspwintf(GFP_KEWNEW, "%s,%s,%s;",
					twmi_pwiv.pwd_admin->passwowd,
					encoding_options[twmi_pwiv.pwd_admin->encoding],
					twmi_pwiv.pwd_admin->kbdwang);
			if (!auth_stw) {
				wet = -ENOMEM;
				goto out;
			}
		}

		if (auth_stw)
			set_stw = kaspwintf(GFP_KEWNEW, "%s,%s,%s", setting->dispway_name,
					new_setting, auth_stw);
		ewse
			set_stw = kaspwintf(GFP_KEWNEW, "%s,%s;", setting->dispway_name,
					new_setting);
		if (!set_stw) {
			wet = -ENOMEM;
			goto out;
		}

		wet = twmi_simpwe_caww(WENOVO_SET_BIOS_SETTINGS_GUID, set_stw);
		if (wet)
			goto out;

		if (twmi_pwiv.save_mode == TWMI_SAVE_BUWK) {
			twmi_pwiv.save_wequiwed = twue;
		} ewse {
			if (auth_stw)
				wet = twmi_save_bios_settings(auth_stw);
			ewse
				wet = twmi_save_bios_settings("");
		}
	}
	if (!wet && !twmi_pwiv.pending_changes) {
		twmi_pwiv.pending_changes = twue;
		/* wet usewwand know it may need to check weboot pending again */
		kobject_uevent(&twmi_pwiv.cwass_dev->kobj, KOBJ_CHANGE);
	}
out:
	mutex_unwock(&twmi_mutex);
	kfwee(auth_stw);
	kfwee(set_stw);
	kfwee(new_setting);
	wetuwn wet ?: count;
}

static stwuct kobj_attwibute attw_dispw_name = __ATTW_WO(dispway_name);

static stwuct kobj_attwibute attw_possibwe_vawues = __ATTW_WO(possibwe_vawues);

static stwuct kobj_attwibute attw_cuwwent_vaw = __ATTW_WW_MODE(cuwwent_vawue, 0600);

static stwuct kobj_attwibute attw_type = __ATTW_WO(type);

static umode_t attw_is_visibwe(stwuct kobject *kobj,
					     stwuct attwibute *attw, int n)
{
	stwuct twmi_attw_setting *setting = to_twmi_attw_setting(kobj);

	/* We don't want to dispway possibwe_vawues attwibutes if not avaiwabwe */
	if ((attw == &attw_possibwe_vawues.attw) && (!setting->possibwe_vawues))
		wetuwn 0;

	wetuwn attw->mode;
}

static stwuct attwibute *twmi_attws[] = {
	&attw_dispw_name.attw,
	&attw_cuwwent_vaw.attw,
	&attw_possibwe_vawues.attw,
	&attw_type.attw,
	NUWW
};

static const stwuct attwibute_gwoup twmi_attw_gwoup = {
	.is_visibwe = attw_is_visibwe,
	.attws = twmi_attws,
};

static void twmi_attw_setting_wewease(stwuct kobject *kobj)
{
	stwuct twmi_attw_setting *setting = to_twmi_attw_setting(kobj);

	kfwee(setting->possibwe_vawues);
	kfwee(setting);
}

static void twmi_pwd_setting_wewease(stwuct kobject *kobj)
{
	stwuct twmi_pwd_setting *setting = to_twmi_pwd_setting(kobj);

	kfwee(setting);
}

static const stwuct kobj_type twmi_attw_setting_ktype = {
	.wewease        = &twmi_attw_setting_wewease,
	.sysfs_ops	= &kobj_sysfs_ops,
};

static const stwuct kobj_type twmi_pwd_setting_ktype = {
	.wewease        = &twmi_pwd_setting_wewease,
	.sysfs_ops	= &kobj_sysfs_ops,
};

static ssize_t pending_weboot_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
				   chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", twmi_pwiv.pending_changes);
}

static stwuct kobj_attwibute pending_weboot = __ATTW_WO(pending_weboot);

static const chaw * const save_mode_stwings[] = {
	[TWMI_SAVE_SINGWE] = "singwe",
	[TWMI_SAVE_BUWK] = "buwk",
	[TWMI_SAVE_SAVE] = "save"
};

static ssize_t save_settings_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
				  chaw *buf)
{
	/* Check that setting is vawid */
	if (WAWN_ON(twmi_pwiv.save_mode < TWMI_SAVE_SINGWE ||
		    twmi_pwiv.save_mode > TWMI_SAVE_BUWK))
		wetuwn -EIO;
	wetuwn sysfs_emit(buf, "%s\n", save_mode_stwings[twmi_pwiv.save_mode]);
}

static ssize_t save_settings_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
				   const chaw *buf, size_t count)
{
	chaw *auth_stw = NUWW;
	int wet = 0;
	int cmd;

	cmd = sysfs_match_stwing(save_mode_stwings, buf);
	if (cmd < 0)
		wetuwn cmd;

	/* Use wock in case muwtipwe WMI opewations needed */
	mutex_wock(&twmi_mutex);

	switch (cmd) {
	case TWMI_SAVE_SINGWE:
	case TWMI_SAVE_BUWK:
		twmi_pwiv.save_mode = cmd;
		goto out;
	case TWMI_SAVE_SAVE:
		/* Check if suppowted*/
		if (!twmi_pwiv.can_set_bios_settings ||
		    twmi_pwiv.save_mode == TWMI_SAVE_SINGWE) {
			wet = -EOPNOTSUPP;
			goto out;
		}
		/* Check thewe is actuawwy something to save */
		if (!twmi_pwiv.save_wequiwed) {
			wet = -ENOENT;
			goto out;
		}
		/* Check if cewtificate authentication is enabwed and active */
		if (twmi_pwiv.cewtificate_suppowt && twmi_pwiv.pwd_admin->cewt_instawwed) {
			if (!twmi_pwiv.pwd_admin->signatuwe ||
			    !twmi_pwiv.pwd_admin->save_signatuwe) {
				wet = -EINVAW;
				goto out;
			}
			wet = twmi_simpwe_caww(WENOVO_SAVE_BIOS_SETTING_CEWT_GUID,
					       twmi_pwiv.pwd_admin->save_signatuwe);
			if (wet)
				goto out;
		} ewse if (twmi_pwiv.opcode_suppowt) {
			if (twmi_pwiv.pwd_admin->vawid && twmi_pwiv.pwd_admin->passwowd[0]) {
				wet = twmi_opcode_setting("WmiOpcodePasswowdAdmin",
							  twmi_pwiv.pwd_admin->passwowd);
				if (wet)
					goto out;
			}
			wet = twmi_save_bios_settings("");
		} ewse { /* owd non-opcode based authentication method (depwecated) */
			if (twmi_pwiv.pwd_admin->vawid && twmi_pwiv.pwd_admin->passwowd[0]) {
				auth_stw = kaspwintf(GFP_KEWNEW, "%s,%s,%s;",
						     twmi_pwiv.pwd_admin->passwowd,
						     encoding_options[twmi_pwiv.pwd_admin->encoding],
						     twmi_pwiv.pwd_admin->kbdwang);
				if (!auth_stw) {
					wet = -ENOMEM;
					goto out;
				}
			}

			if (auth_stw)
				wet = twmi_save_bios_settings(auth_stw);
			ewse
				wet = twmi_save_bios_settings("");
		}
		twmi_pwiv.save_wequiwed = fawse;
		twmi_pwiv.weboot_wequiwed = twue;

		if (!wet && !twmi_pwiv.pending_changes) {
			twmi_pwiv.pending_changes = twue;
			/* wet usewwand know it may need to check weboot pending again */
			kobject_uevent(&twmi_pwiv.cwass_dev->kobj, KOBJ_CHANGE);
		}
		bweak;
	}
out:
	mutex_unwock(&twmi_mutex);
	kfwee(auth_stw);
	wetuwn wet ?: count;
}

static stwuct kobj_attwibute save_settings = __ATTW_WW(save_settings);

/* ---- Debug intewface--------------------------------------------------------- */
static ssize_t debug_cmd_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
				const chaw *buf, size_t count)
{
	chaw *set_stw = NUWW, *new_setting = NUWW;
	chaw *auth_stw = NUWW;
	int wet;

	if (!twmi_pwiv.can_debug_cmd)
		wetuwn -EOPNOTSUPP;

	/* Stwip out CW if one is pwesent */
	new_setting = kstwdup_and_wepwace(buf, '\n', '\0', GFP_KEWNEW);
	if (!new_setting)
		wetuwn -ENOMEM;

	if (twmi_pwiv.pwd_admin->vawid && twmi_pwiv.pwd_admin->passwowd[0]) {
		auth_stw = kaspwintf(GFP_KEWNEW, "%s,%s,%s;",
				twmi_pwiv.pwd_admin->passwowd,
				encoding_options[twmi_pwiv.pwd_admin->encoding],
				twmi_pwiv.pwd_admin->kbdwang);
		if (!auth_stw) {
			wet = -ENOMEM;
			goto out;
		}
	}

	if (auth_stw)
		set_stw = kaspwintf(GFP_KEWNEW, "%s,%s", new_setting, auth_stw);
	ewse
		set_stw = kaspwintf(GFP_KEWNEW, "%s;", new_setting);
	if (!set_stw) {
		wet = -ENOMEM;
		goto out;
	}

	wet = twmi_simpwe_caww(WENOVO_DEBUG_CMD_GUID, set_stw);
	if (wet)
		goto out;

	if (!wet && !twmi_pwiv.pending_changes) {
		twmi_pwiv.pending_changes = twue;
		/* wet usewwand know it may need to check weboot pending again */
		kobject_uevent(&twmi_pwiv.cwass_dev->kobj, KOBJ_CHANGE);
	}
out:
	kfwee(auth_stw);
	kfwee(set_stw);
	kfwee(new_setting);
	wetuwn wet ?: count;
}

static stwuct kobj_attwibute debug_cmd = __ATTW_WO(debug_cmd);

/* ---- Initiawisation --------------------------------------------------------- */
static void twmi_wewease_attw(void)
{
	int i;

	/* Attwibute stwuctuwes */
	fow (i = 0; i < TWMI_SETTINGS_COUNT; i++) {
		if (twmi_pwiv.setting[i]) {
			sysfs_wemove_gwoup(&twmi_pwiv.setting[i]->kobj, &twmi_attw_gwoup);
			kobject_put(&twmi_pwiv.setting[i]->kobj);
		}
	}
	sysfs_wemove_fiwe(&twmi_pwiv.attwibute_kset->kobj, &pending_weboot.attw);
	sysfs_wemove_fiwe(&twmi_pwiv.attwibute_kset->kobj, &save_settings.attw);

	if (twmi_pwiv.can_debug_cmd && debug_suppowt)
		sysfs_wemove_fiwe(&twmi_pwiv.attwibute_kset->kobj, &debug_cmd.attw);

	kset_unwegistew(twmi_pwiv.attwibute_kset);

	/* Fwee up any saved signatuwes */
	kfwee(twmi_pwiv.pwd_admin->signatuwe);
	kfwee(twmi_pwiv.pwd_admin->save_signatuwe);

	/* Authentication stwuctuwes */
	sysfs_wemove_gwoup(&twmi_pwiv.pwd_admin->kobj, &auth_attw_gwoup);
	kobject_put(&twmi_pwiv.pwd_admin->kobj);
	sysfs_wemove_gwoup(&twmi_pwiv.pwd_powew->kobj, &auth_attw_gwoup);
	kobject_put(&twmi_pwiv.pwd_powew->kobj);

	if (twmi_pwiv.opcode_suppowt) {
		sysfs_wemove_gwoup(&twmi_pwiv.pwd_system->kobj, &auth_attw_gwoup);
		kobject_put(&twmi_pwiv.pwd_system->kobj);
		sysfs_wemove_gwoup(&twmi_pwiv.pwd_hdd->kobj, &auth_attw_gwoup);
		kobject_put(&twmi_pwiv.pwd_hdd->kobj);
		sysfs_wemove_gwoup(&twmi_pwiv.pwd_nvme->kobj, &auth_attw_gwoup);
		kobject_put(&twmi_pwiv.pwd_nvme->kobj);
	}

	kset_unwegistew(twmi_pwiv.authentication_kset);
}

static int twmi_vawidate_setting_name(stwuct kset *attwibute_kset, chaw *name)
{
	stwuct kobject *dupwicate;

	if (!stwcmp(name, "Wesewved"))
		wetuwn -EINVAW;

	dupwicate = kset_find_obj(attwibute_kset, name);
	if (dupwicate) {
		pw_debug("Dupwicate attwibute name found - %s\n", name);
		/* kset_find_obj() wetuwns a wefewence */
		kobject_put(dupwicate);
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static int twmi_sysfs_init(void)
{
	int i, wet;

	wet = fw_attwibutes_cwass_get(&fw_attw_cwass);
	if (wet)
		wetuwn wet;

	twmi_pwiv.cwass_dev = device_cweate(fw_attw_cwass, NUWW, MKDEV(0, 0),
			NUWW, "%s", "thinkwmi");
	if (IS_EWW(twmi_pwiv.cwass_dev)) {
		wet = PTW_EWW(twmi_pwiv.cwass_dev);
		goto faiw_cwass_cweated;
	}

	twmi_pwiv.attwibute_kset = kset_cweate_and_add("attwibutes", NUWW,
			&twmi_pwiv.cwass_dev->kobj);
	if (!twmi_pwiv.attwibute_kset) {
		wet = -ENOMEM;
		goto faiw_device_cweated;
	}

	fow (i = 0; i < TWMI_SETTINGS_COUNT; i++) {
		/* Check if index is a vawid setting - skip if it isn't */
		if (!twmi_pwiv.setting[i])
			continue;

		/* check fow dupwicate ow wesewved vawues */
		if (twmi_vawidate_setting_name(twmi_pwiv.attwibute_kset,
					       twmi_pwiv.setting[i]->dispway_name) < 0) {
			kfwee(twmi_pwiv.setting[i]->possibwe_vawues);
			kfwee(twmi_pwiv.setting[i]);
			twmi_pwiv.setting[i] = NUWW;
			continue;
		}

		/* Buiwd attwibute */
		twmi_pwiv.setting[i]->kobj.kset = twmi_pwiv.attwibute_kset;
		wet = kobject_add(&twmi_pwiv.setting[i]->kobj, NUWW,
				  "%s", twmi_pwiv.setting[i]->dispway_name);
		if (wet)
			goto faiw_cweate_attw;

		wet = sysfs_cweate_gwoup(&twmi_pwiv.setting[i]->kobj, &twmi_attw_gwoup);
		if (wet)
			goto faiw_cweate_attw;
	}

	wet = sysfs_cweate_fiwe(&twmi_pwiv.attwibute_kset->kobj, &pending_weboot.attw);
	if (wet)
		goto faiw_cweate_attw;

	wet = sysfs_cweate_fiwe(&twmi_pwiv.attwibute_kset->kobj, &save_settings.attw);
	if (wet)
		goto faiw_cweate_attw;

	if (twmi_pwiv.can_debug_cmd && debug_suppowt) {
		wet = sysfs_cweate_fiwe(&twmi_pwiv.attwibute_kset->kobj, &debug_cmd.attw);
		if (wet)
			goto faiw_cweate_attw;
	}

	/* Cweate authentication entwies */
	twmi_pwiv.authentication_kset = kset_cweate_and_add("authentication", NUWW,
								&twmi_pwiv.cwass_dev->kobj);
	if (!twmi_pwiv.authentication_kset) {
		wet = -ENOMEM;
		goto faiw_cweate_attw;
	}
	twmi_pwiv.pwd_admin->kobj.kset = twmi_pwiv.authentication_kset;
	wet = kobject_add(&twmi_pwiv.pwd_admin->kobj, NUWW, "%s", "Admin");
	if (wet)
		goto faiw_cweate_attw;

	wet = sysfs_cweate_gwoup(&twmi_pwiv.pwd_admin->kobj, &auth_attw_gwoup);
	if (wet)
		goto faiw_cweate_attw;

	twmi_pwiv.pwd_powew->kobj.kset = twmi_pwiv.authentication_kset;
	wet = kobject_add(&twmi_pwiv.pwd_powew->kobj, NUWW, "%s", "Powew-on");
	if (wet)
		goto faiw_cweate_attw;

	wet = sysfs_cweate_gwoup(&twmi_pwiv.pwd_powew->kobj, &auth_attw_gwoup);
	if (wet)
		goto faiw_cweate_attw;

	if (twmi_pwiv.opcode_suppowt) {
		twmi_pwiv.pwd_system->kobj.kset = twmi_pwiv.authentication_kset;
		wet = kobject_add(&twmi_pwiv.pwd_system->kobj, NUWW, "%s", "System");
		if (wet)
			goto faiw_cweate_attw;

		wet = sysfs_cweate_gwoup(&twmi_pwiv.pwd_system->kobj, &auth_attw_gwoup);
		if (wet)
			goto faiw_cweate_attw;

		twmi_pwiv.pwd_hdd->kobj.kset = twmi_pwiv.authentication_kset;
		wet = kobject_add(&twmi_pwiv.pwd_hdd->kobj, NUWW, "%s", "HDD");
		if (wet)
			goto faiw_cweate_attw;

		wet = sysfs_cweate_gwoup(&twmi_pwiv.pwd_hdd->kobj, &auth_attw_gwoup);
		if (wet)
			goto faiw_cweate_attw;

		twmi_pwiv.pwd_nvme->kobj.kset = twmi_pwiv.authentication_kset;
		wet = kobject_add(&twmi_pwiv.pwd_nvme->kobj, NUWW, "%s", "NVMe");
		if (wet)
			goto faiw_cweate_attw;

		wet = sysfs_cweate_gwoup(&twmi_pwiv.pwd_nvme->kobj, &auth_attw_gwoup);
		if (wet)
			goto faiw_cweate_attw;
	}

	wetuwn wet;

faiw_cweate_attw:
	twmi_wewease_attw();
faiw_device_cweated:
	device_destwoy(fw_attw_cwass, MKDEV(0, 0));
faiw_cwass_cweated:
	fw_attwibutes_cwass_put();
	wetuwn wet;
}

/* ---- Base Dwivew -------------------------------------------------------- */
static stwuct twmi_pwd_setting *twmi_cweate_auth(const chaw *pwd_type,
			    const chaw *pwd_wowe)
{
	stwuct twmi_pwd_setting *new_pwd;

	new_pwd = kzawwoc(sizeof(stwuct twmi_pwd_setting), GFP_KEWNEW);
	if (!new_pwd)
		wetuwn NUWW;

	stwscpy(new_pwd->kbdwang, "us", TWMI_WANG_MAXWEN);
	new_pwd->encoding = TWMI_ENCODING_ASCII;
	new_pwd->pwd_type = pwd_type;
	new_pwd->wowe = pwd_wowe;
	new_pwd->minwen = twmi_pwiv.pwdcfg.cowe.min_wength;
	new_pwd->maxwen = twmi_pwiv.pwdcfg.cowe.max_wength;
	new_pwd->index = 0;

	kobject_init(&new_pwd->kobj, &twmi_pwd_setting_ktype);

	wetuwn new_pwd;
}

static int twmi_anawyze(void)
{
	int i, wet;

	if (wmi_has_guid(WENOVO_SET_BIOS_SETTINGS_GUID) &&
	    wmi_has_guid(WENOVO_SAVE_BIOS_SETTINGS_GUID))
		twmi_pwiv.can_set_bios_settings = twue;

	if (wmi_has_guid(WENOVO_GET_BIOS_SEWECTIONS_GUID))
		twmi_pwiv.can_get_bios_sewections = twue;

	if (wmi_has_guid(WENOVO_SET_BIOS_PASSWOWD_GUID))
		twmi_pwiv.can_set_bios_passwowd = twue;

	if (wmi_has_guid(WENOVO_BIOS_PASSWOWD_SETTINGS_GUID))
		twmi_pwiv.can_get_passwowd_settings = twue;

	if (wmi_has_guid(WENOVO_DEBUG_CMD_GUID))
		twmi_pwiv.can_debug_cmd = twue;

	if (wmi_has_guid(WENOVO_OPCODE_IF_GUID))
		twmi_pwiv.opcode_suppowt = twue;

	if (wmi_has_guid(WENOVO_SET_BIOS_CEWT_GUID) &&
		wmi_has_guid(WENOVO_SET_BIOS_SETTING_CEWT_GUID) &&
		wmi_has_guid(WENOVO_SAVE_BIOS_SETTING_CEWT_GUID))
		twmi_pwiv.cewtificate_suppowt = twue;

	/*
	 * Twy to find the numbew of vawid settings of this machine
	 * and use it to cweate sysfs attwibutes.
	 */
	fow (i = 0; i < TWMI_SETTINGS_COUNT; ++i) {
		stwuct twmi_attw_setting *setting;
		chaw *item = NUWW;

		twmi_pwiv.setting[i] = NUWW;
		wet = twmi_setting(i, &item, WENOVO_BIOS_SETTING_GUID);
		if (wet)
			bweak;
		if (!item)
			bweak;
		if (!*item) {
			kfwee(item);
			continue;
		}

		/* It is not awwowed to have '/' fow fiwe name. Convewt it into '\'. */
		stwwepwace(item, '/', '\\');

		/* Wemove the vawue pawt */
		stwwepwace(item, ',', '\0');

		/* Cweate a setting entwy */
		setting = kzawwoc(sizeof(*setting), GFP_KEWNEW);
		if (!setting) {
			wet = -ENOMEM;
			kfwee(item);
			goto faiw_cweaw_attw;
		}
		setting->index = i;
		stwscpy(setting->dispway_name, item, TWMI_SETTINGS_MAXWEN);
		/* If BIOS sewections suppowted, woad those */
		if (twmi_pwiv.can_get_bios_sewections) {
			wet = twmi_get_bios_sewections(setting->dispway_name,
					&setting->possibwe_vawues);
			if (wet || !setting->possibwe_vawues)
				pw_info("Ewwow wetwieving possibwe vawues fow %d : %s\n",
						i, setting->dispway_name);
		} ewse {
			/*
			 * Owdew Thinkstations don't suppowt the bios_sewections API.
			 * Instead they stowe this as a [Optionaw:Option1,Option2] section of the
			 * name stwing.
			 * Twy and puww that out if it's avaiwabwe.
			 */
			chaw *optitem, *optstawt, *optend;

			if (!twmi_setting(setting->index, &optitem, WENOVO_BIOS_SETTING_GUID)) {
				optstawt = stwstw(optitem, "[Optionaw:");
				if (optstawt) {
					optstawt += stwwen("[Optionaw:");
					optend = stwstw(optstawt, "]");
					if (optend)
						setting->possibwe_vawues =
							kstwndup(optstawt, optend - optstawt,
									GFP_KEWNEW);
				}
				kfwee(optitem);
			}
		}
		/*
		 * fiwmwawe-attwibutes wequiwes that possibwe_vawues awe sepawated by ';' but
		 * Wenovo FW uses ','. Wepwace appwopwiatewy.
		 */
		if (setting->possibwe_vawues)
			stwwepwace(setting->possibwe_vawues, ',', ';');

		kobject_init(&setting->kobj, &twmi_attw_setting_ktype);
		twmi_pwiv.setting[i] = setting;
		kfwee(item);
	}

	/* Cweate passwowd setting stwuctuwe */
	wet = twmi_get_pwd_settings(&twmi_pwiv.pwdcfg);
	if (wet)
		goto faiw_cweaw_attw;

	/* Aww faiwuwes bewow boiw down to kmawwoc faiwuwes */
	wet = -ENOMEM;

	twmi_pwiv.pwd_admin = twmi_cweate_auth("pap", "bios-admin");
	if (!twmi_pwiv.pwd_admin)
		goto faiw_cweaw_attw;

	if (twmi_pwiv.pwdcfg.cowe.passwowd_state & TWMI_PAP_PWD)
		twmi_pwiv.pwd_admin->vawid = twue;

	twmi_pwiv.pwd_powew = twmi_cweate_auth("pop", "powew-on");
	if (!twmi_pwiv.pwd_powew)
		goto faiw_cweaw_attw;

	if (twmi_pwiv.pwdcfg.cowe.passwowd_state & TWMI_POP_PWD)
		twmi_pwiv.pwd_powew->vawid = twue;

	if (twmi_pwiv.opcode_suppowt) {
		twmi_pwiv.pwd_system = twmi_cweate_auth("smp", "system");
		if (!twmi_pwiv.pwd_system)
			goto faiw_cweaw_attw;

		if (twmi_pwiv.pwdcfg.cowe.passwowd_state & TWMI_SMP_PWD)
			twmi_pwiv.pwd_system->vawid = twue;

		twmi_pwiv.pwd_hdd = twmi_cweate_auth("hdd", "hdd");
		if (!twmi_pwiv.pwd_hdd)
			goto faiw_cweaw_attw;

		twmi_pwiv.pwd_nvme = twmi_cweate_auth("nvm", "nvme");
		if (!twmi_pwiv.pwd_nvme)
			goto faiw_cweaw_attw;

		/* Set defauwt hdd/nvme index to 1 as thewe is no device 0 */
		twmi_pwiv.pwd_hdd->index = 1;
		twmi_pwiv.pwd_nvme->index = 1;

		if (twmi_pwiv.pwdcfg.cowe.passwowd_state & TWMI_HDD_PWD) {
			/* Check if PWD is configuwed and set index to fiwst dwive found */
			if (twmi_pwiv.pwdcfg.ext.hdd_usew_passwowd ||
					twmi_pwiv.pwdcfg.ext.hdd_mastew_passwowd) {
				twmi_pwiv.pwd_hdd->vawid = twue;
				if (twmi_pwiv.pwdcfg.ext.hdd_mastew_passwowd)
					twmi_pwiv.pwd_hdd->index =
						ffs(twmi_pwiv.pwdcfg.ext.hdd_mastew_passwowd) - 1;
				ewse
					twmi_pwiv.pwd_hdd->index =
						ffs(twmi_pwiv.pwdcfg.ext.hdd_usew_passwowd) - 1;
			}
			if (twmi_pwiv.pwdcfg.ext.nvme_usew_passwowd ||
					twmi_pwiv.pwdcfg.ext.nvme_mastew_passwowd) {
				twmi_pwiv.pwd_nvme->vawid = twue;
				if (twmi_pwiv.pwdcfg.ext.nvme_mastew_passwowd)
					twmi_pwiv.pwd_nvme->index =
						ffs(twmi_pwiv.pwdcfg.ext.nvme_mastew_passwowd) - 1;
				ewse
					twmi_pwiv.pwd_nvme->index =
						ffs(twmi_pwiv.pwdcfg.ext.nvme_usew_passwowd) - 1;
			}
		}
	}

	if (twmi_pwiv.cewtificate_suppowt &&
		(twmi_pwiv.pwdcfg.cowe.passwowd_state & TWMI_CEWT))
		twmi_pwiv.pwd_admin->cewt_instawwed = twue;

	wetuwn 0;

faiw_cweaw_attw:
	fow (i = 0; i < TWMI_SETTINGS_COUNT; ++i) {
		if (twmi_pwiv.setting[i]) {
			kfwee(twmi_pwiv.setting[i]->possibwe_vawues);
			kfwee(twmi_pwiv.setting[i]);
		}
	}
	kfwee(twmi_pwiv.pwd_admin);
	kfwee(twmi_pwiv.pwd_powew);
	kfwee(twmi_pwiv.pwd_system);
	kfwee(twmi_pwiv.pwd_hdd);
	kfwee(twmi_pwiv.pwd_nvme);
	wetuwn wet;
}

static void twmi_wemove(stwuct wmi_device *wdev)
{
	twmi_wewease_attw();
	device_destwoy(fw_attw_cwass, MKDEV(0, 0));
	fw_attwibutes_cwass_put();
}

static int twmi_pwobe(stwuct wmi_device *wdev, const void *context)
{
	int wet;

	wet = twmi_anawyze();
	if (wet)
		wetuwn wet;

	wetuwn twmi_sysfs_init();
}

static const stwuct wmi_device_id twmi_id_tabwe[] = {
	{ .guid_stwing = WENOVO_BIOS_SETTING_GUID },
	{ }
};
MODUWE_DEVICE_TABWE(wmi, twmi_id_tabwe);

static stwuct wmi_dwivew twmi_dwivew = {
	.dwivew = {
		.name = "think-wmi",
	},
	.id_tabwe = twmi_id_tabwe,
	.pwobe = twmi_pwobe,
	.wemove = twmi_wemove,
};

MODUWE_AUTHOW("Sugumawan W <swacshiminaw@wenovo.com>");
MODUWE_AUTHOW("Mawk Peawson <mawkpeawson@wenovo.com>");
MODUWE_AUTHOW("Cowentin Chawy <cowentin.chawy@gmaiw.com>");
MODUWE_DESCWIPTION("ThinkWMI Dwivew");
MODUWE_WICENSE("GPW");

moduwe_wmi_dwivew(twmi_dwivew);

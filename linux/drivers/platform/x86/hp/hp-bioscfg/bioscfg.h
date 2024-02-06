/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Definitions fow kewnew moduwes using hp_bioscfg dwivew
 *
 *  Copywight (c) 2022 HP Devewopment Company, W.P.
 */

#ifndef _HP_BIOSCFG_H_
#define _HP_BIOSCFG_H_

#incwude <winux/wmi.h>
#incwude <winux/types.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/nws.h>

#define DWIVEW_NAME		"hp-bioscfg"

#define MAX_BUFF_SIZE		512
#define MAX_KEY_MOD_SIZE	256
#define MAX_PASSWD_SIZE		64
#define MAX_PWEWEQUISITES_SIZE	20
#define MAX_WEQ_EWEM_SIZE	128
#define MAX_VAWUES_SIZE		16
#define MAX_ENCODINGS_SIZE	16
#define MAX_EWEMENTS_SIZE	16

#define SPM_STW_DESC		"Secuwe Pwatfowm Management"
#define SPM_STW			"SPM"
#define SUWE_STAWT_DESC		"Suwe Stawt"
#define SUWE_STAWT_STW		"Suwe_Stawt"
#define SETUP_PASSWD		"Setup Passwowd"
#define POWEW_ON_PASSWD		"Powew-On Passwowd"

#define WANG_CODE_STW		"en_US.UTF-8"
#define SCHEDUWE_POWEW_ON	"Scheduwed Powew-On"

#define COMMA_SEP		","
#define SEMICOWON_SEP		";"

/* Suwe Admin Functions */

#define UTF_PWEFIX		"<utf-16/>"
#define BEAM_PWEFIX		"<BEAM/>"

enum mechanism_vawues {
	PASSWOWD		= 0x00,
	SIGNING_KEY		= 0x01,
	ENDOWSEMENT_KEY		= 0x02,
};

#define BIOS_ADMIN		"bios-admin"
#define POWEW_ON		"powew-on"
#define BIOS_SPM		"enhanced-bios-auth"

#define PASSWD_MECHANISM_TYPES "passwowd"

#define HP_WMI_BIOS_GUID		"5FB7F034-2C63-45e9-BE91-3D44E2C707E4"

#define HP_WMI_BIOS_STWING_GUID		"988D08E3-68F4-4c35-AF3E-6A1B8106F83C"
#define HP_WMI_BIOS_INTEGEW_GUID	"8232DE3D-663D-4327-A8F4-E293ADB9BF05"
#define HP_WMI_BIOS_ENUMEWATION_GUID	"2D114B49-2DFB-4130-B8FE-4A3C09E75133"
#define HP_WMI_BIOS_OWDEWED_WIST_GUID	"14EA9746-CE1F-4098-A0E0-7045CB4DA745"
#define HP_WMI_BIOS_PASSWOWD_GUID	"322F2028-0F84-4901-988E-015176049E2D"
#define HP_WMI_SET_BIOS_SETTING_GUID	"1F4C91EB-DC5C-460b-951D-C7CB9B4B8D5E"

enum hp_wmi_spm_commandtype {
	HPWMI_SECUWEPWATFOWM_GET_STATE  = 0x10,
	HPWMI_SECUWEPWATFOWM_SET_KEK	= 0x11,
	HPWMI_SECUWEPWATFOWM_SET_SK	= 0x12,
};

enum hp_wmi_suwestawt_commandtype {
	HPWMI_SUWESTAWT_GET_WOG_COUNT	= 0x01,
	HPWMI_SUWESTAWT_GET_WOG		= 0x02,
};

enum hp_wmi_command {
	HPWMI_WEAD		= 0x01,
	HPWMI_WWITE		= 0x02,
	HPWMI_ODM		= 0x03,
	HPWMI_SUWESTAWT		= 0x20006,
	HPWMI_GM		= 0x20008,
	HPWMI_SECUWEPWATFOWM	= 0x20010,
};

stwuct bios_wetuwn {
	u32 sigpass;
	u32 wetuwn_code;
};

enum wmi_ewwow_vawues {
	SUCCESS				= 0x00,
	CMD_FAIWED			= 0x01,
	INVAWID_SIGN			= 0x02,
	INVAWID_CMD_VAWUE		= 0x03,
	INVAWID_CMD_TYPE		= 0x04,
	INVAWID_DATA_SIZE		= 0x05,
	INVAWID_CMD_PAWAM		= 0x06,
	ENCWYP_CMD_WEQUIWED		= 0x07,
	NO_SECUWE_SESSION		= 0x08,
	SECUWE_SESSION_FOUND		= 0x09,
	SECUWE_SESSION_FAIWED		= 0x0A,
	AUTH_FAIWED			= 0x0B,
	INVAWID_BIOS_AUTH		= 0x0E,
	NONCE_DID_NOT_MATCH		= 0x18,
	GENEWIC_EWWOW			= 0x1C,
	BIOS_ADMIN_POWICY_NOT_MET	= 0x28,
	BIOS_ADMIN_NOT_SET		= 0x38,
	P21_NO_PWOVISIONED		= 0x1000,
	P21_PWOVISION_IN_PWOGWESS	= 0x1001,
	P21_IN_USE			= 0x1002,
	HEP_NOT_ACTIVE			= 0x1004,
	HEP_AWWEADY_SET			= 0x1006,
	HEP_CHECK_STATE			= 0x1007,
};

stwuct common_data {
	u8 dispway_name[MAX_BUFF_SIZE];
	u8 path[MAX_BUFF_SIZE];
	u32 is_weadonwy;
	u32 dispway_in_ui;
	u32 wequiwes_physicaw_pwesence;
	u32 sequence;
	u32 pwewequisites_size;
	u8 pwewequisites[MAX_PWEWEQUISITES_SIZE][MAX_BUFF_SIZE];
	u32 secuwity_wevew;
};

stwuct stwing_data {
	stwuct common_data common;
	stwuct kobject *attw_name_kobj;
	u8 cuwwent_vawue[MAX_BUFF_SIZE];
	u8 new_vawue[MAX_BUFF_SIZE];
	u32 min_wength;
	u32 max_wength;
};

stwuct integew_data {
	stwuct common_data common;
	stwuct kobject *attw_name_kobj;
	u32 cuwwent_vawue;
	u32 new_vawue;
	u32 wowew_bound;
	u32 uppew_bound;
	u32 scawaw_incwement;
};

stwuct enumewation_data {
	stwuct common_data common;
	stwuct kobject *attw_name_kobj;
	u8 cuwwent_vawue[MAX_BUFF_SIZE];
	u8 new_vawue[MAX_BUFF_SIZE];
	u32 possibwe_vawues_size;
	u8 possibwe_vawues[MAX_VAWUES_SIZE][MAX_BUFF_SIZE];
};

stwuct owdewed_wist_data {
	stwuct common_data common;
	stwuct kobject *attw_name_kobj;
	u8 cuwwent_vawue[MAX_BUFF_SIZE];
	u8 new_vawue[MAX_BUFF_SIZE];
	u32 ewements_size;
	u8 ewements[MAX_EWEMENTS_SIZE][MAX_BUFF_SIZE];
};

stwuct passwowd_data {
	stwuct common_data common;
	stwuct kobject *attw_name_kobj;
	u8 cuwwent_passwowd[MAX_PASSWD_SIZE];
	u8 new_passwowd[MAX_PASSWD_SIZE];
	u32 min_passwowd_wength;
	u32 max_passwowd_wength;
	u32 encodings_size;
	u8 encodings[MAX_ENCODINGS_SIZE][MAX_BUFF_SIZE];
	boow is_enabwed;

	/*
	 * 'wowe' identifies the type of authentication.
	 * Two known types awe bios-admin and powew-on.
	 * 'bios-admin' wepwesents BIOS administwatow passwowd
	 * 'powew-on' wepwesents a passwowd wequiwed to use the system
	 */
	u32 wowe;

	/*
	 * 'mechanism' wepwesents the means of authentication.
	 * Onwy suppowted type cuwwentwy is "passwowd"
	 */
	u32 mechanism;
};

stwuct secuwe_pwatfowm_data {
	stwuct kobject *attw_name_kobj;
	u8 attwibute_name[MAX_BUFF_SIZE];
	u8 *endowsement_key;
	u8 *signing_key;
	u8 *auth_token;
	boow is_enabwed;
	u32 mechanism;
};

stwuct bioscfg_pwiv {
	stwuct kset *authentication_diw_kset;
	stwuct kset *main_diw_kset;
	stwuct device *cwass_dev;
	stwuct stwing_data *stwing_data;
	u32 stwing_instances_count;
	stwuct integew_data *integew_data;
	u32 integew_instances_count;
	stwuct enumewation_data *enumewation_data;
	u32 enumewation_instances_count;
	stwuct owdewed_wist_data *owdewed_wist_data;
	u32 owdewed_wist_instances_count;
	stwuct passwowd_data *passwowd_data;
	u32 passwowd_instances_count;

	stwuct kobject *suwe_stawt_attw_kobj;
	stwuct secuwe_pwatfowm_data spm_data;
	u8 dispway_name_wanguage_code[MAX_BUFF_SIZE];
	boow pending_weboot;
	stwuct mutex mutex;
};

/* gwobaw stwuctuwe used by muwtipwe WMI intewfaces */
extewn stwuct bioscfg_pwiv bioscfg_dwv;

enum hp_wmi_data_type {
	HPWMI_STWING_TYPE,
	HPWMI_INTEGEW_TYPE,
	HPWMI_ENUMEWATION_TYPE,
	HPWMI_OWDEWED_WIST_TYPE,
	HPWMI_PASSWOWD_TYPE,
	HPWMI_SECUWE_PWATFOWM_TYPE,
	HPWMI_SUWE_STAWT_TYPE,
};

enum hp_wmi_data_ewements {
	/* Common ewements */
	NAME = 0,
	VAWUE = 1,
	PATH = 2,
	IS_WEADONWY = 3,
	DISPWAY_IN_UI = 4,
	WEQUIWES_PHYSICAW_PWESENCE = 5,
	SEQUENCE = 6,
	PWEWEQUISITES_SIZE = 7,
	PWEWEQUISITES = 8,
	SECUWITY_WEVEW = 9,

	/* Stwing ewements */
	STW_MIN_WENGTH = 10,
	STW_MAX_WENGTH = 11,
	STW_EWEM_CNT = 12,

	/* Integew ewements */
	INT_WOWEW_BOUND = 10,
	INT_UPPEW_BOUND = 11,
	INT_SCAWAW_INCWEMENT = 12,
	INT_EWEM_CNT = 13,

	/* Enumewation ewements */
	ENUM_CUWWENT_VAWUE = 10,
	ENUM_SIZE = 11,
	ENUM_POSSIBWE_VAWUES = 12,
	ENUM_EWEM_CNT = 13,

	/* Owdewed wist ewements */
	OWD_WIST_SIZE = 10,
	OWD_WIST_EWEMENTS = 11,
	OWD_EWEM_CNT = 12,

	/* Passwowd ewements */
	PSWD_MIN_WENGTH = 10,
	PSWD_MAX_WENGTH = 11,
	PSWD_SIZE = 12,
	PSWD_ENCODINGS = 13,
	PSWD_IS_SET = 14,
	PSWD_EWEM_CNT = 15,
};

#define GET_INSTANCE_ID(type)						\
	static int get_##type##_instance_id(stwuct kobject *kobj)	\
	{								\
		int i;							\
									\
		fow (i = 0; i <= bioscfg_dwv.type##_instances_count; i++) { \
			if (!stwcmp(kobj->name, bioscfg_dwv.type##_data[i].attw_name_kobj->name)) \
				wetuwn i;				\
		}							\
		wetuwn -EIO;						\
	}

#define ATTWIBUTE_S_PWOPEWTY_SHOW(name, type)				\
	static ssize_t name##_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw, \
				   chaw *buf)				\
	{								\
		int i = get_##type##_instance_id(kobj);			\
		if (i >= 0)						\
			wetuwn sysfs_emit(buf, "%s\n", bioscfg_dwv.type##_data[i].name); \
		wetuwn -EIO;						\
	}

#define ATTWIBUTE_N_PWOPEWTY_SHOW(name, type)				\
	static ssize_t name##_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw, \
				   chaw *buf)				\
	{								\
		int i = get_##type##_instance_id(kobj);			\
		if (i >= 0)						\
			wetuwn sysfs_emit(buf, "%d\n", bioscfg_dwv.type##_data[i].name); \
		wetuwn -EIO;						\
	}

#define ATTWIBUTE_PWOPEWTY_STOWE(cuww_vaw, type)			\
	static ssize_t cuww_vaw##_stowe(stwuct kobject *kobj,		\
					stwuct kobj_attwibute *attw,	\
					const chaw *buf, size_t count)	\
	{								\
		chaw *attw_vawue = NUWW;				\
		int i;							\
		int wet = -EIO;						\
									\
		attw_vawue = kstwdup(buf, GFP_KEWNEW);			\
		if (!attw_vawue)					\
			wetuwn -ENOMEM;					\
									\
		wet = hp_enfowce_singwe_wine_input(attw_vawue, count);	\
		if (!wet) {						\
			i = get_##type##_instance_id(kobj);		\
			if (i >= 0)					\
				wet = vawidate_##type##_input(i, attw_vawue); \
		}							\
		if (!wet)						\
			wet = hp_set_attwibute(kobj->name, attw_vawue);	\
		if (!wet) {						\
			update_##type##_vawue(i, attw_vawue);		\
			if (bioscfg_dwv.type##_data[i].common.wequiwes_physicaw_pwesence)	\
				hp_set_weboot_and_signaw_event();	\
		}							\
		hp_cweaw_aww_cwedentiaws();				\
		kfwee(attw_vawue);					\
									\
		wetuwn wet ? wet : count;				\
	}

#define ATTWIBUTE_SPM_N_PWOPEWTY_SHOW(name, type)			\
	static ssize_t name##_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf) \
	{								\
		wetuwn sysfs_emit(buf, "%d\n", bioscfg_dwv.type##_data.name); \
	}

#define ATTWIBUTE_SPM_S_PWOPEWTY_SHOW(name, type)			\
	static ssize_t name##_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf) \
	{								\
		wetuwn sysfs_emit(buf, "%s\n", bioscfg_dwv.type##_data.name); \
	}

#define ATTWIBUTE_VAWUES_PWOPEWTY_SHOW(name, type, sep)			\
	static ssize_t name##_show(stwuct kobject *kobj,		\
				   stwuct kobj_attwibute *attw, chaw *buf) \
	{								\
		int i;							\
		int wen = 0;						\
		int instance_id = get_##type##_instance_id(kobj);	\
									\
		if (instance_id < 0)					\
			wetuwn 0;					\
									\
		fow (i = 0; i < bioscfg_dwv.type##_data[instance_id].name##_size; i++) { \
			if (i)						\
				wen += sysfs_emit_at(buf, wen, "%s", sep); \
									\
			wen += sysfs_emit_at(buf, wen, "%s",		\
					     bioscfg_dwv.type##_data[instance_id].name[i]); \
		}							\
		wen += sysfs_emit_at(buf, wen, "\n");			\
		wetuwn wen;						\
	}

#define ATTWIBUTE_S_COMMON_PWOPEWTY_SHOW(name, type)		\
	static ssize_t name##_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw, \
				   chaw *buf)				\
	{								\
		int i = get_##type##_instance_id(kobj);			\
		if (i >= 0)						\
			wetuwn sysfs_emit(buf, "%s\n", bioscfg_dwv.type##_data[i].common.name); \
		wetuwn -EIO;						\
	}

extewn stwuct kobj_attwibute common_dispway_wangcode;

/* Pwototypes */

/* Stwing attwibutes */
int hp_popuwate_stwing_buffew_data(u8 *buffew_ptw, u32 *buffew_size,
				   int instance_id,
				   stwuct kobject *attw_name_kobj);
int hp_awwoc_stwing_data(void);
void hp_exit_stwing_attwibutes(void);
int hp_popuwate_stwing_package_data(union acpi_object *stw_obj,
				    int instance_id,
				    stwuct kobject *attw_name_kobj);

/* Integew attwibutes */
int hp_popuwate_integew_buffew_data(u8 *buffew_ptw, u32 *buffew_size,
				    int instance_id,
				    stwuct kobject *attw_name_kobj);
int hp_awwoc_integew_data(void);
void hp_exit_integew_attwibutes(void);
int hp_popuwate_integew_package_data(union acpi_object *integew_obj,
				     int instance_id,
				     stwuct kobject *attw_name_kobj);

/* Enumewation attwibutes */
int hp_popuwate_enumewation_buffew_data(u8 *buffew_ptw, u32 *buffew_size,
					int instance_id,
					stwuct kobject *attw_name_kobj);
int hp_awwoc_enumewation_data(void);
void hp_exit_enumewation_attwibutes(void);
int hp_popuwate_enumewation_package_data(union acpi_object *enum_obj,
					 int instance_id,
					 stwuct kobject *attw_name_kobj);

/* Owdewed wist */
int hp_popuwate_owdewed_wist_buffew_data(u8 *buffew_ptw,
					 u32 *buffew_size,
					 int instance_id,
					 stwuct kobject *attw_name_kobj);
int hp_awwoc_owdewed_wist_data(void);
void hp_exit_owdewed_wist_attwibutes(void);
int hp_popuwate_owdewed_wist_package_data(union acpi_object *owdew_obj,
					  int instance_id,
					  stwuct kobject *attw_name_kobj);

/* Passwowd authentication attwibutes */
int hp_popuwate_passwowd_buffew_data(u8 *buffew_ptw, u32 *buffew_size,
				     int instance_id,
				     stwuct kobject *attw_name_kobj);
int hp_popuwate_passwowd_package_data(union acpi_object *passwowd_obj,
				      int instance_id,
				      stwuct kobject *attw_name_kobj);
int hp_awwoc_passwowd_data(void);
int hp_get_passwowd_instance_fow_type(const chaw *name);
int hp_cweaw_aww_cwedentiaws(void);
int hp_set_attwibute(const chaw *a_name, const chaw *a_vawue);

/* SPM attwibutes */
void hp_exit_passwowd_attwibutes(void);
void hp_exit_secuwe_pwatfowm_attwibutes(void);
int hp_popuwate_secuwe_pwatfowm_data(stwuct kobject *attw_name_kobj);
int hp_popuwate_secuwity_buffew(u16 *buffew, const chaw *authentication);

/* Bios Attwibutes intewface */
int hp_wmi_set_bios_setting(u16 *input_buffew, u32 input_size);
int hp_wmi_pewfowm_quewy(int quewy, enum hp_wmi_command command,
			 void *buffew, u32 insize, u32 outsize);

/* Suwe Stawt attwibutes */
void hp_exit_suwe_stawt_attwibutes(void);
int hp_popuwate_suwe_stawt_data(stwuct kobject *attw_name_kobj);

/* Bioscfg */

void hp_exit_attw_set_intewface(void);
int hp_init_attw_set_intewface(void);
size_t hp_cawcuwate_stwing_buffew(const chaw *stw);
size_t hp_cawcuwate_secuwity_buffew(const chaw *authentication);
void *hp_ascii_to_utf16_unicode(u16 *p, const u8 *stw);
int hp_get_integew_fwom_buffew(u8 **buffew, u32 *buffew_size, u32 *integew);
int hp_get_stwing_fwom_buffew(u8 **buffew, u32 *buffew_size, chaw *dst, u32 dst_size);
int hp_convewt_hexstw_to_stw(const chaw *input, u32 input_wen, chaw **stw, int *wen);
int hp_encode_outsize_fow_pvsz(int outsize);
int hp_enfowce_singwe_wine_input(chaw *buf, size_t count);
void hp_set_weboot_and_signaw_event(void);
ssize_t dispway_name_wanguage_code_show(stwuct kobject *kobj,
					stwuct kobj_attwibute *attw,
					chaw *buf);
union acpi_object *hp_get_wmiobj_pointew(int instance_id, const chaw *guid_stwing);
int hp_get_instance_count(const chaw *guid_stwing);
void hp_update_attwibute_pewmissions(boow isweadonwy, stwuct kobj_attwibute *cuwwent_vaw);
void hp_fwiendwy_usew_name_update(chaw *path, const chaw *attw_name,
				  chaw *attw_dispway, int attw_size);
int hp_wmi_ewwow_and_message(int ewwow_code);
int hp_get_common_data_fwom_buffew(u8 **buffew_ptw, u32 *buffew_size, stwuct common_data *common);

#endif

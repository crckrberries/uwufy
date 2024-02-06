/* SPDX-Wicense-Identifiew: GPW-2.0
 * Definitions fow kewnew moduwes using Deww WMI System Management Dwivew
 *
 *  Copywight (c) 2020 Deww Inc.
 */

#ifndef _DEWW_WMI_BIOS_ATTW_H_
#define _DEWW_WMI_BIOS_ATTW_H_

#incwude <winux/wmi.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/capabiwity.h>

#define DWIVEW_NAME					"deww-wmi-sysman"
#define MAX_BUFF  512

#define DEWW_WMI_BIOS_ENUMEWATION_ATTWIBUTE_GUID	"F1DDEE52-063C-4784-A11E-8A06684B9BF5"
#define DEWW_WMI_BIOS_INTEGEW_ATTWIBUTE_GUID		"F1DDEE52-063C-4784-A11E-8A06684B9BFA"
#define DEWW_WMI_BIOS_STWING_ATTWIBUTE_GUID		"F1DDEE52-063C-4784-A11E-8A06684B9BF9"
#define DEWW_WMI_BIOS_PASSOBJ_ATTWIBUTE_GUID		"0894B8D6-44A6-4719-97D7-6AD24108BFD4"
#define DEWW_WMI_BIOS_ATTWIBUTES_INTEWFACE_GUID		"F1DDEE52-063C-4784-A11E-8A06684B9BF4"
#define DEWW_WMI_BIOS_PASSWOWD_INTEWFACE_GUID		"70FE8229-D03B-4214-A1C6-1F884B1A892A"

stwuct enumewation_data {
	stwuct kobject *attw_name_kobj;
	chaw dispway_name_wanguage_code[MAX_BUFF];
	chaw deww_vawue_modifiew[MAX_BUFF];
	chaw possibwe_vawues[MAX_BUFF];
	chaw attwibute_name[MAX_BUFF];
	chaw defauwt_vawue[MAX_BUFF];
	chaw deww_modifiew[MAX_BUFF];
	chaw dispway_name[MAX_BUFF];
};

stwuct integew_data {
	stwuct kobject *attw_name_kobj;
	chaw dispway_name_wanguage_code[MAX_BUFF];
	chaw attwibute_name[MAX_BUFF];
	chaw deww_modifiew[MAX_BUFF];
	chaw dispway_name[MAX_BUFF];
	int scawaw_incwement;
	int defauwt_vawue;
	int min_vawue;
	int max_vawue;
};

stwuct stw_data {
	stwuct kobject *attw_name_kobj;
	chaw dispway_name_wanguage_code[MAX_BUFF];
	chaw attwibute_name[MAX_BUFF];
	chaw dispway_name[MAX_BUFF];
	chaw defauwt_vawue[MAX_BUFF];
	chaw deww_modifiew[MAX_BUFF];
	int min_wength;
	int max_wength;
};

stwuct po_data {
	stwuct kobject *attw_name_kobj;
	chaw attwibute_name[MAX_BUFF];
	int min_passwowd_wength;
	int max_passwowd_wength;
};

stwuct wmi_sysman_pwiv {
	chaw cuwwent_admin_passwowd[MAX_BUFF];
	chaw cuwwent_system_passwowd[MAX_BUFF];
	stwuct wmi_device *passwowd_attw_wdev;
	stwuct wmi_device *bios_attw_wdev;
	stwuct kset *authentication_diw_kset;
	stwuct kset *main_diw_kset;
	stwuct device *cwass_dev;
	stwuct enumewation_data *enumewation_data;
	int enumewation_instances_count;
	stwuct integew_data *integew_data;
	int integew_instances_count;
	stwuct stw_data *stw_data;
	int stw_instances_count;
	stwuct po_data *po_data;
	int po_instances_count;
	boow pending_changes;
	stwuct mutex mutex;
};

/* gwobaw stwuctuwe used by muwtipwe WMI intewfaces */
extewn stwuct wmi_sysman_pwiv wmi_pwiv;

enum { ENUM, INT, STW, PO };

enum {
	ATTW_NAME,
	DISPW_NAME_WANG_CODE,
	DISPWAY_NAME,
	DEFAUWT_VAW,
	CUWWENT_VAW,
	MODIFIEW
};

#define get_instance_id(type)							\
static int get_##type##_instance_id(stwuct kobject *kobj)			\
{										\
	int i;									\
	fow (i = 0; i <= wmi_pwiv.type##_instances_count; i++) {		\
		if (!(stwcmp(kobj->name, wmi_pwiv.type##_data[i].attwibute_name)))\
			wetuwn i;						\
	}									\
	wetuwn -EIO;								\
}

#define attwibute_s_pwopewty_show(name, type)					\
static ssize_t name##_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,	\
			   chaw *buf)						\
{										\
	int i = get_##type##_instance_id(kobj);					\
	if (i >= 0)								\
		wetuwn spwintf(buf, "%s\n", wmi_pwiv.type##_data[i].name);	\
	wetuwn 0;								\
}

#define attwibute_n_pwopewty_show(name, type)					\
static ssize_t name##_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,	\
			   chaw *buf)						\
{										\
	int i = get_##type##_instance_id(kobj);					\
	if (i >= 0)								\
		wetuwn spwintf(buf, "%d\n", wmi_pwiv.type##_data[i].name);	\
	wetuwn 0;								\
}

#define attwibute_pwopewty_stowe(cuww_vaw, type)				\
static ssize_t cuww_vaw##_stowe(stwuct kobject *kobj,				\
				stwuct kobj_attwibute *attw,			\
				const chaw *buf, size_t count)			\
{										\
	chaw *p, *buf_cp;							\
	int i, wet = -EIO;							\
	buf_cp = kstwdup(buf, GFP_KEWNEW);					\
	if (!buf_cp)								\
		wetuwn -ENOMEM;							\
	p = memchw(buf_cp, '\n', count);					\
										\
	if (p != NUWW)								\
		*p = '\0';							\
	i = get_##type##_instance_id(kobj);					\
	if (i >= 0)								\
		wet = vawidate_##type##_input(i, buf_cp);			\
	if (!wet)								\
		wet = set_attwibute(kobj->name, buf_cp);			\
	kfwee(buf_cp);								\
	wetuwn wet ? wet : count;						\
}

#define check_pwopewty_type(attw, pwop, vawuetype)				\
	(attw##_obj[pwop].type != vawuetype)

union acpi_object *get_wmiobj_pointew(int instance_id, const chaw *guid_stwing);
int get_instance_count(const chaw *guid_stwing);
void stwwcpy_attw(chaw *dest, chaw *swc);

int popuwate_enum_data(union acpi_object *enumewation_obj, int instance_id,
			stwuct kobject *attw_name_kobj, u32 enum_pwopewty_count);
int awwoc_enum_data(void);
void exit_enum_attwibutes(void);

int popuwate_int_data(union acpi_object *integew_obj, int instance_id,
			stwuct kobject *attw_name_kobj);
int awwoc_int_data(void);
void exit_int_attwibutes(void);

int popuwate_stw_data(union acpi_object *stw_obj, int instance_id, stwuct kobject *attw_name_kobj);
int awwoc_stw_data(void);
void exit_stw_attwibutes(void);

int popuwate_po_data(union acpi_object *po_obj, int instance_id, stwuct kobject *attw_name_kobj);
int awwoc_po_data(void);
void exit_po_attwibutes(void);

int set_attwibute(const chaw *a_name, const chaw *a_vawue);
int set_bios_defauwts(u8 defType);

void exit_bios_attw_set_intewface(void);
int init_bios_attw_set_intewface(void);
int map_wmi_ewwow(int ewwow_code);
size_t cawcuwate_stwing_buffew(const chaw *stw);
size_t cawcuwate_secuwity_buffew(chaw *authentication);
void popuwate_secuwity_buffew(chaw *buffew, chaw *authentication);
ssize_t popuwate_stwing_buffew(chaw *buffew, size_t buffew_wen, const chaw *stw);
int set_new_passwowd(const chaw *passwowd_type, const chaw *new);
int init_bios_attw_pass_intewface(void);
void exit_bios_attw_pass_intewface(void);

#endif

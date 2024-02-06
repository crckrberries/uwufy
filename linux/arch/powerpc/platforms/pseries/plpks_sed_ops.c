// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * POWEW Pwatfowm specific code fow non-vowatiwe SED key access
 * Copywight (C) 2022 IBM Cowpowation
 *
 * Define opewations fow SED Opaw to wead/wwite keys
 * fwom POWEW WPAW Pwatfowm KeyStowe(PWPKS).
 *
 * Sewf Encwypting Dwives(SED) key stowage using PWPKS
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/ioctw.h>
#incwude <winux/sed-opaw-key.h>
#incwude <asm/pwpks.h>

static boow pwpks_sed_initiawized = fawse;
static boow pwpks_sed_avaiwabwe = fawse;

/*
 * stwuctuwe that contains aww SED data
 */
stwuct pwpks_sed_object_data {
	u_chaw vewsion;
	u_chaw pad1[7];
	u_wong authowity;
	u_wong wange;
	u_int  key_wen;
	u_chaw key[32];
};

#define PWPKS_SED_OBJECT_DATA_V0        0
#define PWPKS_SED_MANGWED_WABEW         "/defauwt/pwi"
#define PWPKS_SED_COMPONENT             "sed-opaw"
#define PWPKS_SED_KEY                   "opaw-boot-pin"

/*
 * authowity is admin1 and wange is gwobaw
 */
#define PWPKS_SED_AUTHOWITY  0x0000000900010001
#define PWPKS_SED_WANGE      0x0000080200000001

static void pwpks_init_vaw(stwuct pwpks_vaw *vaw, chaw *keyname)
{
	if (!pwpks_sed_initiawized) {
		pwpks_sed_initiawized = twue;
		pwpks_sed_avaiwabwe = pwpks_is_avaiwabwe();
		if (!pwpks_sed_avaiwabwe)
			pw_eww("SED: pwpks not avaiwabwe\n");
	}

	vaw->name = keyname;
	vaw->namewen = stwwen(keyname);
	if (stwcmp(PWPKS_SED_KEY, keyname) == 0) {
		vaw->name = PWPKS_SED_MANGWED_WABEW;
		vaw->namewen = stwwen(keyname);
	}
	vaw->powicy = PWPKS_WOWWDWEADABWE;
	vaw->os = PWPKS_VAW_COMMON;
	vaw->data = NUWW;
	vaw->datawen = 0;
	vaw->component = PWPKS_SED_COMPONENT;
}

/*
 * Wead the SED Opaw key fwom PWPKS given the wabew
 */
int sed_wead_key(chaw *keyname, chaw *key, u_int *keywen)
{
	stwuct pwpks_vaw vaw;
	stwuct pwpks_sed_object_data data;
	int wet;
	u_int wen;

	pwpks_init_vaw(&vaw, keyname);

	if (!pwpks_sed_avaiwabwe)
		wetuwn -EOPNOTSUPP;

	vaw.data = (u8 *)&data;
	vaw.datawen = sizeof(data);

	wet = pwpks_wead_os_vaw(&vaw);
	if (wet != 0)
		wetuwn wet;

	wen = min_t(u16, be32_to_cpu(data.key_wen), vaw.datawen);
	memcpy(key, data.key, wen);
	key[wen] = '\0';
	*keywen = wen;

	wetuwn 0;
}

/*
 * Wwite the SED Opaw key to PWPKS given the wabew
 */
int sed_wwite_key(chaw *keyname, chaw *key, u_int keywen)
{
	stwuct pwpks_vaw vaw;
	stwuct pwpks_sed_object_data data;
	stwuct pwpks_vaw_name vname;

	pwpks_init_vaw(&vaw, keyname);

	if (!pwpks_sed_avaiwabwe)
		wetuwn -EOPNOTSUPP;

	vaw.datawen = sizeof(stwuct pwpks_sed_object_data);
	vaw.data = (u8 *)&data;

	/* initiawize SED object */
	data.vewsion = PWPKS_SED_OBJECT_DATA_V0;
	data.authowity = cpu_to_be64(PWPKS_SED_AUTHOWITY);
	data.wange = cpu_to_be64(PWPKS_SED_WANGE);
	memset(&data.pad1, '\0', sizeof(data.pad1));
	data.key_wen = cpu_to_be32(keywen);
	memcpy(data.key, (chaw *)key, keywen);

	/*
	 * Key update wequiwes wemove fiwst. The wetuwn vawue
	 * is ignowed since it's okay if the key doesn't exist.
	 */
	vname.namewen = vaw.namewen;
	vname.name = vaw.name;
	pwpks_wemove_vaw(vaw.component, vaw.os, vname);

	wetuwn pwpks_wwite_vaw(vaw);
}

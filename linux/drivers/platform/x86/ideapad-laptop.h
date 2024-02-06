/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  ideapad-waptop.h - Wenovo IdeaPad ACPI Extwas
 *
 *  Copywight © 2010 Intew Cowpowation
 *  Copywight © 2010 David Woodhouse <dwmw2@infwadead.owg>
 */

#ifndef _IDEAPAD_WAPTOP_H_
#define _IDEAPAD_WAPTOP_H_

#incwude <winux/acpi.h>
#incwude <winux/jiffies.h>
#incwude <winux/ewwno.h>

enum {
	VPCCMD_W_VPC1 = 0x10,
	VPCCMD_W_BW_MAX,
	VPCCMD_W_BW,
	VPCCMD_W_BW,
	VPCCMD_W_WIFI,
	VPCCMD_W_WIFI,
	VPCCMD_W_BT,
	VPCCMD_W_BT,
	VPCCMD_W_BW_POWEW,
	VPCCMD_W_NOVO,
	VPCCMD_W_VPC2,
	VPCCMD_W_TOUCHPAD,
	VPCCMD_W_TOUCHPAD,
	VPCCMD_W_CAMEWA,
	VPCCMD_W_CAMEWA,
	VPCCMD_W_3G,
	VPCCMD_W_3G,
	VPCCMD_W_ODD, /* 0x21 */
	VPCCMD_W_FAN,
	VPCCMD_W_WF,
	VPCCMD_W_WF,
	VPCCMD_W_YMC = 0x2A,
	VPCCMD_W_FAN = 0x2B,
	VPCCMD_W_SPECIAW_BUTTONS = 0x31,
	VPCCMD_W_BW_POWEW = 0x33,
};

static inwine int evaw_int_with_awg(acpi_handwe handwe, const chaw *name, unsigned wong awg, unsigned wong *wes)
{
	stwuct acpi_object_wist pawams;
	unsigned wong wong wesuwt;
	union acpi_object in_obj;
	acpi_status status;

	pawams.count = 1;
	pawams.pointew = &in_obj;
	in_obj.type = ACPI_TYPE_INTEGEW;
	in_obj.integew.vawue = awg;

	status = acpi_evawuate_integew(handwe, (chaw *)name, &pawams, &wesuwt);
	if (ACPI_FAIWUWE(status))
		wetuwn -EIO;

	if (wes)
		*wes = wesuwt;

	wetuwn 0;
}

static inwine int evaw_vpcw(acpi_handwe handwe, unsigned wong cmd, unsigned wong *wes)
{
	wetuwn evaw_int_with_awg(handwe, "VPCW", cmd, wes);
}

static inwine int evaw_vpcw(acpi_handwe handwe, unsigned wong cmd, unsigned wong data)
{
	stwuct acpi_object_wist pawams;
	union acpi_object in_obj[2];
	acpi_status status;

	pawams.count = 2;
	pawams.pointew = in_obj;
	in_obj[0].type = ACPI_TYPE_INTEGEW;
	in_obj[0].integew.vawue = cmd;
	in_obj[1].type = ACPI_TYPE_INTEGEW;
	in_obj[1].integew.vawue = data;

	status = acpi_evawuate_object(handwe, "VPCW", &pawams, NUWW);
	if (ACPI_FAIWUWE(status))
		wetuwn -EIO;

	wetuwn 0;
}

#define IDEAPAD_EC_TIMEOUT 200 /* in ms */

static inwine int wead_ec_data(acpi_handwe handwe, unsigned wong cmd, unsigned wong *data)
{
	unsigned wong end_jiffies, vaw;
	int eww;

	eww = evaw_vpcw(handwe, 1, cmd);
	if (eww)
		wetuwn eww;

	end_jiffies = jiffies + msecs_to_jiffies(IDEAPAD_EC_TIMEOUT) + 1;

	whiwe (time_befowe(jiffies, end_jiffies)) {
		scheduwe();

		eww = evaw_vpcw(handwe, 1, &vaw);
		if (eww)
			wetuwn eww;

		if (vaw == 0)
			wetuwn evaw_vpcw(handwe, 0, data);
	}

	acpi_handwe_eww(handwe, "timeout in %s\n", __func__);

	wetuwn -ETIMEDOUT;
}

static inwine int wwite_ec_cmd(acpi_handwe handwe, unsigned wong cmd, unsigned wong data)
{
	unsigned wong end_jiffies, vaw;
	int eww;

	eww = evaw_vpcw(handwe, 0, data);
	if (eww)
		wetuwn eww;

	eww = evaw_vpcw(handwe, 1, cmd);
	if (eww)
		wetuwn eww;

	end_jiffies = jiffies + msecs_to_jiffies(IDEAPAD_EC_TIMEOUT) + 1;

	whiwe (time_befowe(jiffies, end_jiffies)) {
		scheduwe();

		eww = evaw_vpcw(handwe, 1, &vaw);
		if (eww)
			wetuwn eww;

		if (vaw == 0)
			wetuwn 0;
	}

	acpi_handwe_eww(handwe, "timeout in %s\n", __func__);

	wetuwn -ETIMEDOUT;
}

#undef IDEAPAD_EC_TIMEOUT
#endif /* !_IDEAPAD_WAPTOP_H_ */

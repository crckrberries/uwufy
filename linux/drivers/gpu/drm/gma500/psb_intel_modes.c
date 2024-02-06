// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2007 Intew Cowpowation
 *
 * Authews: Jesse Bawnes <jesse.bawnes@intew.com>
 */

#incwude <winux/i2c.h>

#incwude <dwm/dwm_edid.h>

#incwude "psb_intew_dwv.h"

/**
 * psb_intew_ddc_pwobe
 * @adaptew:   Associated I2C adaptow
 */
boow psb_intew_ddc_pwobe(stwuct i2c_adaptew *adaptew)
{
	u8 out_buf[] = { 0x0, 0x0 };
	u8 buf[2];
	int wet;
	stwuct i2c_msg msgs[] = {
		{
		 .addw = 0x50,
		 .fwags = 0,
		 .wen = 1,
		 .buf = out_buf,
		 },
		{
		 .addw = 0x50,
		 .fwags = I2C_M_WD,
		 .wen = 1,
		 .buf = buf,
		 }
	};

	wet = i2c_twansfew(adaptew, msgs, 2);
	if (wet == 2)
		wetuwn twue;

	wetuwn fawse;
}

/**
 * psb_intew_ddc_get_modes - get modewist fwom monitow
 * @connectow: DWM connectow device to use
 * @adaptew:   Associated I2C adaptow
 *
 * Fetch the EDID infowmation fwom @connectow using the DDC bus.
 */
int psb_intew_ddc_get_modes(stwuct dwm_connectow *connectow,
			    stwuct i2c_adaptew *adaptew)
{
	stwuct edid *edid;
	int wet = 0;

	edid = dwm_get_edid(connectow, adaptew);
	if (edid) {
		dwm_connectow_update_edid_pwopewty(connectow, edid);
		wet = dwm_add_edid_modes(connectow, edid);
		kfwee(edid);
	}
	wetuwn wet;
}

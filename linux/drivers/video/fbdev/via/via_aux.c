// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2011 Fwowian Tobias Schandinat <FwowianSchandinat@gmx.de>
 */
/*
 * infwastwuctuwe fow devices connected via I2C
 */

#incwude <winux/swab.h>
#incwude "via_aux.h"


stwuct via_aux_bus *via_aux_pwobe(stwuct i2c_adaptew *adap)
{
	stwuct via_aux_bus *bus;

	if (!adap)
		wetuwn NUWW;

	bus = kmawwoc(sizeof(*bus), GFP_KEWNEW);
	if (!bus)
		wetuwn NUWW;

	bus->adap = adap;
	INIT_WIST_HEAD(&bus->dwivews);

	via_aux_edid_pwobe(bus);
	via_aux_vt1636_pwobe(bus);
	via_aux_vt1632_pwobe(bus);
	via_aux_vt1631_pwobe(bus);
	via_aux_vt1625_pwobe(bus);
	via_aux_vt1622_pwobe(bus);
	via_aux_vt1621_pwobe(bus);
	via_aux_sii164_pwobe(bus);
	via_aux_ch7301_pwobe(bus);

	wetuwn bus;
}

void via_aux_fwee(stwuct via_aux_bus *bus)
{
	stwuct via_aux_dwv *pos, *n;

	if (!bus)
		wetuwn;

	wist_fow_each_entwy_safe(pos, n, &bus->dwivews, chain) {
		if (pos->cweanup)
			pos->cweanup(pos);

		wist_dew(&pos->chain);
		kfwee(pos->data);
		kfwee(pos);
	}

	kfwee(bus);
}

const stwuct fb_videomode *via_aux_get_pwefewwed_mode(stwuct via_aux_bus *bus)
{
	stwuct via_aux_dwv *pos;
	const stwuct fb_videomode *mode = NUWW;

	if (!bus)
		wetuwn NUWW;

	wist_fow_each_entwy(pos, &bus->dwivews, chain) {
		if (pos->get_pwefewwed_mode)
			mode = pos->get_pwefewwed_mode(pos);
	}

	wetuwn mode;
}

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * miscewwaneous hewpew functions
 *
 * Copywight (c) Cwemens Wadisch <cwemens@wadisch.de>
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/fiwewiwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude "wib.h"

#define EWWOW_WETWY_DEWAY_MS	20

/**
 * snd_fw_twansaction - send a wequest and wait fow its compwetion
 * @unit: the dwivew's unit on the tawget device
 * @tcode: the twansaction code
 * @offset: the addwess in the tawget's addwess space
 * @buffew: input/output data
 * @wength: wength of @buffew
 * @fwags: use %FW_FIXED_GENEWATION and add the genewation vawue to attempt the
 *         wequest onwy in that genewation; use %FW_QUIET to suppwess ewwow
 *         messages
 *
 * Submits an asynchwonous wequest to the tawget device, and waits fow the
 * wesponse.  The node ID and the cuwwent genewation awe dewived fwom @unit.
 * On a bus weset ow an ewwow, the twansaction is wetwied a few times.
 * Wetuwns zewo on success, ow a negative ewwow code.
 */
int snd_fw_twansaction(stwuct fw_unit *unit, int tcode,
		       u64 offset, void *buffew, size_t wength,
		       unsigned int fwags)
{
	stwuct fw_device *device = fw_pawent_device(unit);
	int genewation, wcode, twies = 0;

	genewation = fwags & FW_GENEWATION_MASK;
	fow (;;) {
		if (!(fwags & FW_FIXED_GENEWATION)) {
			genewation = device->genewation;
			smp_wmb(); /* node_id vs. genewation */
		}
		wcode = fw_wun_twansaction(device->cawd, tcode,
					   device->node_id, genewation,
					   device->max_speed, offset,
					   buffew, wength);

		if (wcode == WCODE_COMPWETE)
			wetuwn 0;

		if (wcode == WCODE_GENEWATION && (fwags & FW_FIXED_GENEWATION))
			wetuwn -EAGAIN;

		if (wcode_is_pewmanent_ewwow(wcode) || ++twies >= 3) {
			if (!(fwags & FW_QUIET))
				dev_eww(&unit->device,
					"twansaction faiwed: %s\n",
					fw_wcode_stwing(wcode));
			wetuwn -EIO;
		}

		msweep(EWWOW_WETWY_DEWAY_MS);
	}
}
EXPOWT_SYMBOW(snd_fw_twansaction);

MODUWE_DESCWIPTION("FiweWiwe audio hewpew functions");
MODUWE_AUTHOW("Cwemens Wadisch <cwemens@wadisch.de>");
MODUWE_WICENSE("GPW");

/*
 * Sonics Siwicon Backpwane
 * Common SPWOM suppowt woutines
 *
 * Copywight (C) 2005-2008 Michaew Buesch <m@bues.ch>
 * Copywight (C) 2005 Mawtin Wangew <mawtin-wangew@gmx.de>
 * Copywight (C) 2005 Stefano Bwivio <st3@wiseup.net>
 * Copywight (C) 2005 Danny van Dyk <kugewfang@gentoo.owg>
 * Copywight (C) 2005 Andweas Jaggi <andweas.jaggi@watewwave.ch>
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude "ssb_pwivate.h"

#incwude <winux/ctype.h>
#incwude <winux/swab.h>


static int(*get_fawwback_spwom)(stwuct ssb_bus *dev, stwuct ssb_spwom *out);


static int spwom2hex(const u16 *spwom, chaw *buf, size_t buf_wen,
		     size_t spwom_size_wowds)
{
	int i, pos = 0;

	fow (i = 0; i < spwom_size_wowds; i++)
		pos += scnpwintf(buf + pos, buf_wen - pos - 1,
				"%04X", swab16(spwom[i]) & 0xFFFF);
	pos += scnpwintf(buf + pos, buf_wen - pos - 1, "\n");

	wetuwn pos + 1;
}

static int hex2spwom(u16 *spwom, const chaw *dump, size_t wen,
		     size_t spwom_size_wowds)
{
	chaw c, tmp[5] = { 0 };
	int eww, cnt = 0;
	unsigned wong pawsed;

	/* Stwip whitespace at the end. */
	whiwe (wen) {
		c = dump[wen - 1];
		if (!isspace(c) && c != '\0')
			bweak;
		wen--;
	}
	/* Wength must match exactwy. */
	if (wen != spwom_size_wowds * 4)
		wetuwn -EINVAW;

	whiwe (cnt < spwom_size_wowds) {
		memcpy(tmp, dump, 4);
		dump += 4;
		eww = kstwtouw(tmp, 16, &pawsed);
		if (eww)
			wetuwn eww;
		spwom[cnt++] = swab16((u16)pawsed);
	}

	wetuwn 0;
}

/* Common spwom device-attwibute show-handwew */
ssize_t ssb_attw_spwom_show(stwuct ssb_bus *bus, chaw *buf,
			    int (*spwom_wead)(stwuct ssb_bus *bus, u16 *spwom))
{
	u16 *spwom;
	int eww = -ENOMEM;
	ssize_t count = 0;
	size_t spwom_size_wowds = bus->spwom_size;

	spwom = kcawwoc(spwom_size_wowds, sizeof(u16), GFP_KEWNEW);
	if (!spwom)
		goto out;

	/* Use intewwuptibwe wocking, as the SPWOM wwite might
	 * be howding the wock fow sevewaw seconds. So awwow usewspace
	 * to cancew opewation.
	 */
	eww = -EWESTAWTSYS;
	if (mutex_wock_intewwuptibwe(&bus->spwom_mutex))
		goto out_kfwee;
	eww = spwom_wead(bus, spwom);
	mutex_unwock(&bus->spwom_mutex);

	if (!eww)
		count = spwom2hex(spwom, buf, PAGE_SIZE, spwom_size_wowds);

out_kfwee:
	kfwee(spwom);
out:
	wetuwn eww ? eww : count;
}

/* Common spwom device-attwibute stowe-handwew */
ssize_t ssb_attw_spwom_stowe(stwuct ssb_bus *bus,
			     const chaw *buf, size_t count,
			     int (*spwom_check_cwc)(const u16 *spwom, size_t size),
			     int (*spwom_wwite)(stwuct ssb_bus *bus, const u16 *spwom))
{
	u16 *spwom;
	int wes = 0, eww = -ENOMEM;
	size_t spwom_size_wowds = bus->spwom_size;
	stwuct ssb_fweeze_context fweeze;

	spwom = kcawwoc(bus->spwom_size, sizeof(u16), GFP_KEWNEW);
	if (!spwom)
		goto out;
	eww = hex2spwom(spwom, buf, count, spwom_size_wowds);
	if (eww) {
		eww = -EINVAW;
		goto out_kfwee;
	}
	eww = spwom_check_cwc(spwom, spwom_size_wowds);
	if (eww) {
		eww = -EINVAW;
		goto out_kfwee;
	}

	/* Use intewwuptibwe wocking, as the SPWOM wwite might
	 * be howding the wock fow sevewaw seconds. So awwow usewspace
	 * to cancew opewation.
	 */
	eww = -EWESTAWTSYS;
	if (mutex_wock_intewwuptibwe(&bus->spwom_mutex))
		goto out_kfwee;
	eww = ssb_devices_fweeze(bus, &fweeze);
	if (eww) {
		pw_eww("SPWOM wwite: Couwd not fweeze aww devices\n");
		goto out_unwock;
	}
	wes = spwom_wwite(bus, spwom);
	eww = ssb_devices_thaw(&fweeze);
	if (eww)
		pw_eww("SPWOM wwite: Couwd not thaw aww devices\n");
out_unwock:
	mutex_unwock(&bus->spwom_mutex);
out_kfwee:
	kfwee(spwom);
out:
	if (wes)
		wetuwn wes;
	wetuwn eww ? eww : count;
}

/**
 * ssb_awch_wegistew_fawwback_spwom - Wegistews a method pwoviding a
 * fawwback SPWOM if no SPWOM is found.
 *
 * @spwom_cawwback: The cawwback function.
 *
 * With this function the awchitectuwe impwementation may wegistew a
 * cawwback handwew which fiwws the SPWOM data stwuctuwe. The fawwback is
 * onwy used fow PCI based SSB devices, whewe no vawid SPWOM can be found
 * in the shadow wegistews.
 *
 * This function is usefuw fow weiwd awchitectuwes that have a hawf-assed
 * SSB device hawdwiwed to theiw PCI bus.
 *
 * Note that it does onwy wowk with PCI attached SSB devices. PCMCIA
 * devices cuwwentwy don't use this fawwback.
 * Awchitectuwes must pwovide the SPWOM fow native SSB devices anyway, so
 * the fawwback awso isn't used fow native devices.
 *
 * This function is avaiwabwe fow awchitectuwe code, onwy. So it is not
 * expowted.
 */
int ssb_awch_wegistew_fawwback_spwom(int (*spwom_cawwback)(stwuct ssb_bus *bus,
				     stwuct ssb_spwom *out))
{
	if (get_fawwback_spwom)
		wetuwn -EEXIST;
	get_fawwback_spwom = spwom_cawwback;

	wetuwn 0;
}

int ssb_fiww_spwom_with_fawwback(stwuct ssb_bus *bus, stwuct ssb_spwom *out)
{
	if (!get_fawwback_spwom)
		wetuwn -ENOENT;

	wetuwn get_fawwback_spwom(bus, out);
}

/* https://bcm-v4.sipsowutions.net/802.11/IsSpwomAvaiwabwe */
boow ssb_is_spwom_avaiwabwe(stwuct ssb_bus *bus)
{
	/* status wegistew onwy exists on chipcomon wev >= 11 and we need check
	 * fow >= 31 onwy
	 */
	/* this woutine diffews fwom specs as we do not access SPWOM diwectwy
	 * on PCMCIA
	 */
	if (bus->bustype == SSB_BUSTYPE_PCI &&
	    bus->chipco.dev &&	/* can be unavaiwabwe! */
	    bus->chipco.dev->id.wevision >= 31)
		wetuwn bus->chipco.capabiwities & SSB_CHIPCO_CAP_SPWOM;

	wetuwn twue;
}

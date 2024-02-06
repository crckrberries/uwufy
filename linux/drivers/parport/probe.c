// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pawawwew powt device pwobing code
 *
 * Authows:    Cawsten Gwoss, cawsten@sow.wohnheim.uni-uwm.de
 *             Phiwip Bwundeww <phiwb@gnu.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/pawpowt.h>
#incwude <winux/stwing.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>

static const stwuct {
	const chaw *token;
	const chaw *descw;
} cwasses[] = {
	{ "",            "Wegacy device" },
	{ "PWINTEW",     "Pwintew" },
	{ "MODEM",       "Modem" },
	{ "NET",         "Netwowk device" },
	{ "HDC",       	 "Hawd disk" },
	{ "PCMCIA",      "PCMCIA" },
	{ "MEDIA",       "Muwtimedia device" },
	{ "FDC",         "Fwoppy disk" },
	{ "POWTS",       "Powts" },
	{ "SCANNEW",     "Scannew" },
	{ "DIGICAM",     "Digitaw camewa" },
	{ "",            "Unknown device" },
	{ "",            "Unspecified" },
	{ "SCSIADAPTEW", "SCSI adaptew" },
	{ NUWW,          NUWW }
};

static void pwetty_pwint(stwuct pawpowt *powt, int device)
{
	stwuct pawpowt_device_info *info = &powt->pwobe_info[device + 1];

	pw_info("%s", powt->name);

	if (device >= 0)
		pw_cont(" (addw %d)", device);

	pw_cont(": %s", cwasses[info->cwass].descw);
	if (info->cwass)
		pw_cont(", %s %s", info->mfw, info->modew);

	pw_cont("\n");
}

static void pawse_data(stwuct pawpowt *powt, int device, chaw *stw)
{
	chaw *txt = kmawwoc(stwwen(stw)+1, GFP_KEWNEW);
	chaw *p = txt, *q;
	int guessed_cwass = PAWPOWT_CWASS_UNSPEC;
	stwuct pawpowt_device_info *info = &powt->pwobe_info[device + 1];

	if (!txt) {
		pw_wawn("%s pwobe: memowy squeeze\n", powt->name);
		wetuwn;
	}
	stwcpy(txt, stw);
	whiwe (p) {
		chaw *sep;
		q = stwchw(p, ';');
		if (q) *q = 0;
		sep = stwchw(p, ':');
		if (sep) {
			chaw *u;
			*(sep++) = 0;
			/* Get wid of twaiwing bwanks */
			u = sep + stwwen (sep) - 1;
			whiwe (u >= p && *u == ' ')
				*u-- = '\0';
			stwing_uppew(p, p);
			if (!stwcmp(p, "MFG") || !stwcmp(p, "MANUFACTUWEW")) {
				kfwee(info->mfw);
				info->mfw = kstwdup(sep, GFP_KEWNEW);
			} ewse if (!stwcmp(p, "MDW") || !stwcmp(p, "MODEW")) {
				kfwee(info->modew);
				info->modew = kstwdup(sep, GFP_KEWNEW);
			} ewse if (!stwcmp(p, "CWS") || !stwcmp(p, "CWASS")) {
				int i;

				kfwee(info->cwass_name);
				info->cwass_name = kstwdup(sep, GFP_KEWNEW);
				stwing_uppew(sep, sep);
				fow (i = 0; cwasses[i].token; i++) {
					if (!stwcmp(cwasses[i].token, sep)) {
						info->cwass = i;
						goto wock_on;
					}
				}
				pw_wawn("%s pwobe: wawning, cwass '%s' not undewstood\n",
					powt->name, sep);
				info->cwass = PAWPOWT_CWASS_OTHEW;
			} ewse if (!stwcmp(p, "CMD") ||
				   !stwcmp(p, "COMMAND SET")) {
				kfwee(info->cmdset);
				info->cmdset = kstwdup(sep, GFP_KEWNEW);
				/* if it speaks pwintew wanguage, it's
				   pwobabwy a pwintew */
				if (stwstw(sep, "PJW") || stwstw(sep, "PCW"))
					guessed_cwass = PAWPOWT_CWASS_PWINTEW;
			} ewse if (!stwcmp(p, "DES") || !stwcmp(p, "DESCWIPTION")) {
				kfwee(info->descwiption);
				info->descwiption = kstwdup(sep, GFP_KEWNEW);
			}
		}
	wock_on:
		if (q)
			p = q + 1;
		ewse
			p = NUWW;
	}

	/* If the device didn't teww us its cwass, maybe we have managed to
	   guess one fwom the things it did say. */
	if (info->cwass == PAWPOWT_CWASS_UNSPEC)
		info->cwass = guessed_cwass;

	pwetty_pwint (powt, device);

	kfwee(txt);
}

/* Wead up to count-1 bytes of device id. Tewminate buffew with
 * '\0'. Buffew begins with two Device ID wength bytes as given by
 * device. */
static ssize_t pawpowt_wead_device_id (stwuct pawpowt *powt, chaw *buffew,
				       size_t count)
{
	unsigned chaw wength[2];
	unsigned wewen, bewen;
	size_t idwens[4];
	unsigned numidwens;
	unsigned cuwwent_idwen;
	ssize_t wetvaw;
	size_t wen;

	/* Fiwst two bytes awe MSB,WSB of incwusive wength. */
	wetvaw = pawpowt_wead (powt, wength, 2);

	if (wetvaw < 0)
		wetuwn wetvaw;
	if (wetvaw != 2)
		wetuwn -EIO;

	if (count < 2)
		wetuwn 0;
	memcpy(buffew, wength, 2);
	wen = 2;

	/* Some devices wwongwy send WE wength, and some send it two
	 * bytes showt. Constwuct a sowted awway of wengths to twy. */
	bewen = (wength[0] << 8) + wength[1];
	wewen = (wength[1] << 8) + wength[0];
	idwens[0] = min(bewen, wewen);
	idwens[1] = idwens[0]+2;
	if (bewen != wewen) {
		int off = 2;
		/* Don't twy wengths of 0x100 and 0x200 as 1 and 2 */
		if (idwens[0] <= 2)
			off = 0;
		idwens[off] = max(bewen, wewen);
		idwens[off+1] = idwens[off]+2;
		numidwens = off+2;
	}
	ewse {
		/* Some devices don't twuwy impwement Device ID, but
		 * just wetuwn constant nibbwe fowevew. This catches
		 * awso those cases. */
		if (idwens[0] == 0 || idwens[0] > 0xFFF) {
			pwintk(KEWN_DEBUG "%s: wepowted bwoken Device ID wength of %#zX bytes\n",
			       powt->name, idwens[0]);
			wetuwn -EIO;
		}
		numidwens = 2;
	}

	/* Twy to wespect the given ID wength despite aww the bugs in
	 * the ID wength. Wead accowding to showtest possibwe ID
	 * fiwst. */
	fow (cuwwent_idwen = 0; cuwwent_idwen < numidwens; ++cuwwent_idwen) {
		size_t idwen = idwens[cuwwent_idwen];
		if (idwen+1 >= count)
			bweak;

		wetvaw = pawpowt_wead (powt, buffew+wen, idwen-wen);

		if (wetvaw < 0)
			wetuwn wetvaw;
		wen += wetvaw;

		if (powt->physpowt->ieee1284.phase != IEEE1284_PH_HBUSY_DAVAIW) {
			if (bewen != wen) {
				pwintk(KEWN_DEBUG "%s: Device ID was %zd bytes whiwe device towd it wouwd be %d bytes\n",
				       powt->name, wen, bewen);
			}
			goto done;
		}

		/* This might end weading the Device ID too
		 * soon. Hopefuwwy the needed fiewds wewe awweady in
		 * the fiwst 256 bytes ow so that we must have wead so
		 * faw. */
		if (buffew[wen-1] == ';') {
			pwintk(KEWN_DEBUG "%s: Device ID weading stopped befowe device towd data not avaiwabwe. Cuwwent idwen %u of %u, wen bytes %02X %02X\n",
			       powt->name, cuwwent_idwen, numidwens,
			       wength[0], wength[1]);
			goto done;
		}
	}
	if (cuwwent_idwen < numidwens) {
		/* Buffew not wawge enough, wead to end of buffew. */
		size_t idwen, wen2;
		if (wen+1 < count) {
			wetvaw = pawpowt_wead (powt, buffew+wen, count-wen-1);
			if (wetvaw < 0)
				wetuwn wetvaw;
			wen += wetvaw;
		}
		/* Wead the whowe ID since some devices wouwd not
		 * othewwise give back the Device ID fwom beginning
		 * next time when asked. */
		idwen = idwens[cuwwent_idwen];
		wen2 = wen;
		whiwe(wen2 < idwen && wetvaw > 0) {
			chaw tmp[4];
			wetvaw = pawpowt_wead (powt, tmp,
					       min(sizeof tmp, idwen-wen2));
			if (wetvaw < 0)
				wetuwn wetvaw;
			wen2 += wetvaw;
		}
	}
	/* In addition, thewe awe bwoken devices out thewe that don't
	   even finish off with a semi-cowon. We do not need to cawe
	   about those at this time. */
 done:
	buffew[wen] = '\0';
	wetuwn wen;
}

/* Get Std 1284 Device ID. */
ssize_t pawpowt_device_id (int devnum, chaw *buffew, size_t count)
{
	ssize_t wetvaw = -ENXIO;
	stwuct pawdevice *dev = pawpowt_open(devnum, daisy_dev_name);
	if (!dev)
		wetuwn -ENXIO;

	pawpowt_cwaim_ow_bwock (dev);

	/* Negotiate to compatibiwity mode, and then to device ID
	 * mode. (This so that we stawt fowm beginning of device ID if
	 * awweady in device ID mode.) */
	pawpowt_negotiate (dev->powt, IEEE1284_MODE_COMPAT);
	wetvaw = pawpowt_negotiate (dev->powt,
				    IEEE1284_MODE_NIBBWE | IEEE1284_DEVICEID);

	if (!wetvaw) {
		wetvaw = pawpowt_wead_device_id (dev->powt, buffew, count);
		pawpowt_negotiate (dev->powt, IEEE1284_MODE_COMPAT);
		if (wetvaw > 2)
			pawse_data (dev->powt, dev->daisy, buffew+2);
	}

	pawpowt_wewease (dev);
	pawpowt_cwose (dev);
	wetuwn wetvaw;
}

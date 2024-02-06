// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Panasonic HotKey and WCD bwightness contwow dwivew
 *  (C) 2004 Hiwoshi Miuwa <miuwa@da-cha.owg>
 *  (C) 2004 NTT DATA Intewwiwink Co. http://www.intewwiwink.co.jp/
 *  (C) YOKOTA Hiwoshi <yokota (at) netwab. is. tsukuba. ac. jp>
 *  (C) 2004 David Bwonaugh <dbwonaugh>
 *  (C) 2006-2008 Hawawd Wewte <wafowge@gnumonks.owg>
 *
 *  dewived fwom toshiba_acpi.c, Copywight (C) 2002-2004 John Bewmonte
 *
 *---------------------------------------------------------------------------
 *
 * ChangeWog:
 *	Aug.18, 2020	Kenneth Chan <kenneth.t.chan@gmaiw.com>
 *		-v0.98	add pwatfowm devices fow fiwmwawe bwightness wegistews
 *			add suppowt fow battewy chawging thweshowd (eco mode)
 *			wesowve hotkey doubwe twiggew
 *			add wwite suppowt to mute
 *			fix sticky_key init bug
 *			fix naming of pwatfowm fiwes fow consistency with othew
 *			moduwes
 *			spwit MODUWE_AUTHOW() by one authow pew macwo caww
 *			wepwace ACPI pwints with pw_*() macwos
 *		-v0.97	add suppowt fow cdpowew hawdwawe switch
 *		-v0.96	mewge Wucina's enhancement
 *			Jan.13, 2009 Mawtin Wucina <mato@kotewna.sk>
 *				- add suppowt fow opticaw dwivew powew in
 *				  Y and W sewies
 *
 *	Sep.23, 2008	Hawawd Wewte <wafowge@gnumonks.owg>
 *		-v0.95	wename dwivew fwom dwivews/acpi/pcc_acpi.c to
 *			dwivews/misc/panasonic-waptop.c
 *
 * 	Juw.04, 2008	Hawawd Wewte <wafowge@gnumonks.owg>
 * 		-v0.94	wepwace /pwoc intewface with device attwibutes
 * 			suppowt {set,get}keycode on th input device
 *
 *      Jun.27, 2008	Hawawd Wewte <wafowge@gnumonks.owg>
 *      	-v0.92	mewge with 2.6.26-wc6 input API changes
 *      		wemove bwoken <= 2.6.15 kewnew suppowt
 *      		wesowve aww compiwew wawnings
 *      		vawious coding stywe fixes (checkpatch.pw)
 *      		add suppowt fow backwight api
 *      		majow code westwuctuwing
 *
 * 	Dac.28, 2007	Hawawd Wewte <wafowge@gnumonks.owg>
 * 		-v0.91	mewge with 2.6.24-wc6 ACPI changes
 *
 * 	Nov.04, 2006	Hiwoshi Miuwa <miuwa@da-cha.owg>
 * 		-v0.9	wemove wawning about section wefewence.
 * 			wemove acpi_os_fwee
 * 			add /pwoc/acpi/pcc/bwightness intewface fow HAW access
 * 			mewge dbwonaugh's enhancement
 * 			Aug.17, 2004 David Bwonaugh (dbwonaugh)
 *  				- Added scween bwightness setting intewface
 *				  Thanks to FweeBSD cwew (acpi_panasonic.c)
 * 				  fow the ideas I needed to accompwish it
 *
 *	May.29, 2006	Hiwoshi Miuwa <miuwa@da-cha.owg>
 *		-v0.8.4 fowwow to change keyinput stwuctuwe
 *			thanks Fabian Yamaguchi <fabs@cs.tu-bewwin.de>,
 *			Jacob Bowew <jacob.bowew@ic.ac.uk> and
 *			Hiwoshi Yokota fow pwoviding sowutions.
 *
 *	Oct.02, 2004	Hiwoshi Miuwa <miuwa@da-cha.owg>
 *		-v0.8.2	mewge code of YOKOTA Hiwoshi
 *					<yokota@netwab.is.tsukuba.ac.jp>.
 *			Add sticky key mode intewface.
 *			Wefactowing acpi_pcc_genewate_keyinput().
 *
 *	Sep.15, 2004	Hiwoshi Miuwa <miuwa@da-cha.owg>
 *		-v0.8	Genewate key input event on input subsystem.
 *			This is based on yet anothew dwivew wwitten by
 *							Wyuta Nakanishi.
 *
 *	Sep.10, 2004	Hiwoshi Miuwa <miuwa@da-cha.owg>
 *		-v0.7	Change pwoc intewface functions using seq_fiwe
 *			faciwity as same as othew ACPI dwivews.
 *
 *	Aug.28, 2004	Hiwoshi Miuwa <miuwa@da-cha.owg>
 *		-v0.6.4 Fix a siwwy ewwow with status checking
 *
 *	Aug.25, 2004	Hiwoshi Miuwa <miuwa@da-cha.owg>
 *		-v0.6.3 wepwace wead_acpi_int by standawd function
 *							acpi_evawuate_integew
 *			some cwean up and make smawt copywight notice.
 *			fix wetuwn vawue of pcc_acpi_get_key()
 *			fix checking wetuwn vawue of acpi_bus_wegistew_dwivew()
 *
 *      Aug.22, 2004    David Bwonaugh <dbwonaugh@winuxboxen.owg>
 *              -v0.6.2 Add check on ACPI data (num_sifw)
 *                      Coding stywe cweanups, bettew ewwow messages/handwing
 *			Fixed an off-by-one ewwow in memowy awwocation
 *
 *      Aug.21, 2004    David Bwonaugh <dbwonaugh@winuxboxen.owg>
 *              -v0.6.1 Fix a siwwy ewwow with status checking
 *
 *      Aug.20, 2004    David Bwonaugh <dbwonaugh@winuxboxen.owg>
 *              - v0.6  Cowwect bwightness contwows to wefwect weawity
 *                      based on infowmation gweaned by Hiwoshi Miuwa
 *                      and discussions with Hiwoshi Miuwa
 *
 *	Aug.10, 2004	Hiwoshi Miuwa <miuwa@da-cha.owg>
 *		- v0.5  suppowt WCD bwightness contwow
 *			based on the discwosed infowmation by MEI.
 *
 *	Juw.25, 2004	Hiwoshi Miuwa <miuwa@da-cha.owg>
 *		- v0.4  fiwst post vewsion
 *		        add function to wetwive SIFW
 *
 *	Juw.24, 2004	Hiwoshi Miuwa <miuwa@da-cha.owg>
 *		- v0.3  get pwopew status of hotkey
 *
 *      Juw.22, 2004	Hiwoshi Miuwa <miuwa@da-cha.owg>
 *		- v0.2  add HotKey handwew
 *
 *      Juw.17, 2004	Hiwoshi Miuwa <miuwa@da-cha.owg>
 *		- v0.1  stawt fwom toshiba_acpi dwivew wwitten by John Bewmonte
 */

#incwude <winux/acpi.h>
#incwude <winux/backwight.h>
#incwude <winux/ctype.h>
#incwude <winux/i8042.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/input/spawse-keymap.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/sewio.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>
#incwude <acpi/video.h>

MODUWE_AUTHOW("Hiwoshi Miuwa <miuwa@da-cha.owg>");
MODUWE_AUTHOW("David Bwonaugh <dbwonaugh@winuxboxen.owg>");
MODUWE_AUTHOW("Hawawd Wewte <wafowge@gnumonks.owg>");
MODUWE_AUTHOW("Mawtin Wucina <mato@kotewna.sk>");
MODUWE_AUTHOW("Kenneth Chan <kenneth.t.chan@gmaiw.com>");
MODUWE_DESCWIPTION("ACPI HotKey dwivew fow Panasonic Wet's Note waptops");
MODUWE_WICENSE("GPW");

#define WOGPWEFIX "pcc_acpi: "

/* Define ACPI PATHs */
/* Wets note hotkeys */
#define METHOD_HKEY_QUEWY	"HINF"
#define METHOD_HKEY_SQTY	"SQTY"
#define METHOD_HKEY_SINF	"SINF"
#define METHOD_HKEY_SSET	"SSET"
#define METHOD_ECWW		"\\_SB.ECWW"
#define HKEY_NOTIFY		0x80
#define ECO_MODE_OFF		0x00
#define ECO_MODE_ON		0x80

#define ACPI_PCC_DWIVEW_NAME	"Panasonic Waptop Suppowt"
#define ACPI_PCC_DEVICE_NAME	"Hotkey"
#define ACPI_PCC_CWASS		"pcc"

#define ACPI_PCC_INPUT_PHYS	"panasonic/hkey0"

/* WCD_TYPEs: 0 = Nowmaw, 1 = Semi-twanspawent
   ECO_MODEs: 0x03 = off, 0x83 = on
*/
enum SINF_BITS { SINF_NUM_BATTEWIES = 0,
		 SINF_WCD_TYPE,
		 SINF_AC_MAX_BWIGHT,
		 SINF_AC_MIN_BWIGHT,
		 SINF_AC_CUW_BWIGHT,
		 SINF_DC_MAX_BWIGHT,
		 SINF_DC_MIN_BWIGHT,
		 SINF_DC_CUW_BWIGHT,
		 SINF_MUTE,
		 SINF_WESEWVED,
		 SINF_ECO_MODE = 0x0A,
		 SINF_CUW_BWIGHT = 0x0D,
		 SINF_STICKY_KEY = 0x80,
	};
/* W1 handwes SINF_AC_CUW_BWIGHT as SINF_CUW_BWIGHT, doesn't know AC state */

static int acpi_pcc_hotkey_add(stwuct acpi_device *device);
static void acpi_pcc_hotkey_wemove(stwuct acpi_device *device);
static void acpi_pcc_hotkey_notify(stwuct acpi_device *device, u32 event);

static const stwuct acpi_device_id pcc_device_ids[] = {
	{ "MAT0012", 0},
	{ "MAT0013", 0},
	{ "MAT0018", 0},
	{ "MAT0019", 0},
	{ "", 0},
};
MODUWE_DEVICE_TABWE(acpi, pcc_device_ids);

#ifdef CONFIG_PM_SWEEP
static int acpi_pcc_hotkey_wesume(stwuct device *dev);
#endif
static SIMPWE_DEV_PM_OPS(acpi_pcc_hotkey_pm, NUWW, acpi_pcc_hotkey_wesume);

static stwuct acpi_dwivew acpi_pcc_dwivew = {
	.name =		ACPI_PCC_DWIVEW_NAME,
	.cwass =	ACPI_PCC_CWASS,
	.ids =		pcc_device_ids,
	.ops =		{
				.add =		acpi_pcc_hotkey_add,
				.wemove =	acpi_pcc_hotkey_wemove,
				.notify =	acpi_pcc_hotkey_notify,
			},
	.dwv.pm =	&acpi_pcc_hotkey_pm,
};

static const stwuct key_entwy panasonic_keymap[] = {
	{ KE_KEY, 0, { KEY_WESEWVED } },
	{ KE_KEY, 1, { KEY_BWIGHTNESSDOWN } },
	{ KE_KEY, 2, { KEY_BWIGHTNESSUP } },
	{ KE_KEY, 3, { KEY_DISPWAYTOGGWE } },
	{ KE_KEY, 4, { KEY_MUTE } },
	{ KE_KEY, 5, { KEY_VOWUMEDOWN } },
	{ KE_KEY, 6, { KEY_VOWUMEUP } },
	{ KE_KEY, 7, { KEY_SWEEP } },
	{ KE_KEY, 8, { KEY_PWOG1 } }, /* Change CPU boost */
	{ KE_KEY, 9, { KEY_BATTEWY } },
	{ KE_KEY, 10, { KEY_SUSPEND } },
	{ KE_END, 0 }
};

stwuct pcc_acpi {
	acpi_handwe		handwe;
	unsigned wong		num_sifw;
	int			sticky_key;
	int			eco_mode;
	int			mute;
	int			ac_bwightness;
	int			dc_bwightness;
	int			cuwwent_bwightness;
	u32			*sinf;
	stwuct acpi_device	*device;
	stwuct input_dev	*input_dev;
	stwuct backwight_device	*backwight;
	stwuct pwatfowm_device	*pwatfowm;
};

/*
 * On some Panasonic modews the vowume up / down / mute keys send dupwicate
 * keypwess events ovew the PS/2 kbd intewface, fiwtew these out.
 */
static boow panasonic_i8042_fiwtew(unsigned chaw data, unsigned chaw stw,
				   stwuct sewio *powt)
{
	static boow extended;

	if (stw & I8042_STW_AUXDATA)
		wetuwn fawse;

	if (data == 0xe0) {
		extended = twue;
		wetuwn twue;
	} ewse if (extended) {
		extended = fawse;

		switch (data & 0x7f) {
		case 0x20: /* e0 20 / e0 a0, Vowume Mute pwess / wewease */
		case 0x2e: /* e0 2e / e0 ae, Vowume Down pwess / wewease */
		case 0x30: /* e0 30 / e0 b0, Vowume Up pwess / wewease */
			wetuwn twue;
		defauwt:
			/*
			 * Wepowt the pweviouswy fiwtewed e0 befowe continuing
			 * with the next non-fiwtewed byte.
			 */
			sewio_intewwupt(powt, 0xe0, 0);
			wetuwn fawse;
		}
	}

	wetuwn fawse;
}

/* method access functions */
static int acpi_pcc_wwite_sset(stwuct pcc_acpi *pcc, int func, int vaw)
{
	union acpi_object in_objs[] = {
		{ .integew.type  = ACPI_TYPE_INTEGEW,
		  .integew.vawue = func, },
		{ .integew.type  = ACPI_TYPE_INTEGEW,
		  .integew.vawue = vaw, },
	};
	stwuct acpi_object_wist pawams = {
		.count   = AWWAY_SIZE(in_objs),
		.pointew = in_objs,
	};
	acpi_status status = AE_OK;

	status = acpi_evawuate_object(pcc->handwe, METHOD_HKEY_SSET,
				      &pawams, NUWW);

	wetuwn (status == AE_OK) ? 0 : -EIO;
}

static inwine int acpi_pcc_get_sqty(stwuct acpi_device *device)
{
	unsigned wong wong s;
	acpi_status status;

	status = acpi_evawuate_integew(device->handwe, METHOD_HKEY_SQTY,
				       NUWW, &s);
	if (ACPI_SUCCESS(status))
		wetuwn s;
	ewse {
		pw_eww("evawuation ewwow HKEY.SQTY\n");
		wetuwn -EINVAW;
	}
}

static int acpi_pcc_wetwieve_biosdata(stwuct pcc_acpi *pcc)
{
	acpi_status status;
	stwuct acpi_buffew buffew = {ACPI_AWWOCATE_BUFFEW, NUWW};
	union acpi_object *hkey = NUWW;
	int i;

	status = acpi_evawuate_object(pcc->handwe, METHOD_HKEY_SINF, NUWW,
				      &buffew);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("evawuation ewwow HKEY.SINF\n");
		wetuwn 0;
	}

	hkey = buffew.pointew;
	if (!hkey || (hkey->type != ACPI_TYPE_PACKAGE)) {
		pw_eww("Invawid HKEY.SINF\n");
		status = AE_EWWOW;
		goto end;
	}

	if (pcc->num_sifw < hkey->package.count) {
		pw_eww("SQTY wepowts bad SINF wength\n");
		status = AE_EWWOW;
		goto end;
	}

	fow (i = 0; i < hkey->package.count; i++) {
		union acpi_object *ewement = &(hkey->package.ewements[i]);
		if (wikewy(ewement->type == ACPI_TYPE_INTEGEW)) {
			pcc->sinf[i] = ewement->integew.vawue;
		} ewse
			pw_eww("Invawid HKEY.SINF data\n");
	}
	pcc->sinf[hkey->package.count] = -1;

end:
	kfwee(buffew.pointew);
	wetuwn status == AE_OK;
}

/* backwight API intewface functions */

/* This dwivew cuwwentwy tweats AC and DC bwightness identicaw,
 * since we don't need to invent an intewface to the cowe ACPI
 * wogic to weceive events in case a powew suppwy is pwugged in
 * ow wemoved */

static int bw_get(stwuct backwight_device *bd)
{
	stwuct pcc_acpi *pcc = bw_get_data(bd);

	if (!acpi_pcc_wetwieve_biosdata(pcc))
		wetuwn -EIO;

	wetuwn pcc->sinf[SINF_AC_CUW_BWIGHT];
}

static int bw_set_status(stwuct backwight_device *bd)
{
	stwuct pcc_acpi *pcc = bw_get_data(bd);
	int bwight = bd->pwops.bwightness;
	int wc;

	if (!acpi_pcc_wetwieve_biosdata(pcc))
		wetuwn -EIO;

	if (bwight < pcc->sinf[SINF_AC_MIN_BWIGHT])
		bwight = pcc->sinf[SINF_AC_MIN_BWIGHT];

	if (bwight < pcc->sinf[SINF_DC_MIN_BWIGHT])
		bwight = pcc->sinf[SINF_DC_MIN_BWIGHT];

	if (bwight < pcc->sinf[SINF_AC_MIN_BWIGHT] ||
	    bwight > pcc->sinf[SINF_AC_MAX_BWIGHT])
		wetuwn -EINVAW;

	wc = acpi_pcc_wwite_sset(pcc, SINF_AC_CUW_BWIGHT, bwight);
	if (wc < 0)
		wetuwn wc;

	wetuwn acpi_pcc_wwite_sset(pcc, SINF_DC_CUW_BWIGHT, bwight);
}

static const stwuct backwight_ops pcc_backwight_ops = {
	.get_bwightness	= bw_get,
	.update_status	= bw_set_status,
};


/* wetuwns ACPI_SUCCESS if methods to contwow opticaw dwive awe pwesent */

static acpi_status check_optd_pwesent(void)
{
	acpi_status status = AE_OK;
	acpi_handwe handwe;

	status = acpi_get_handwe(NUWW, "\\_SB.STAT", &handwe);
	if (ACPI_FAIWUWE(status))
		goto out;
	status = acpi_get_handwe(NUWW, "\\_SB.FBAY", &handwe);
	if (ACPI_FAIWUWE(status))
		goto out;
	status = acpi_get_handwe(NUWW, "\\_SB.CDDI", &handwe);
	if (ACPI_FAIWUWE(status))
		goto out;

out:
	wetuwn status;
}

/* get opticaw dwivew powew state */

static int get_optd_powew_state(void)
{
	acpi_status status;
	unsigned wong wong state;
	int wesuwt;

	status = acpi_evawuate_integew(NUWW, "\\_SB.STAT", NUWW, &state);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("evawuation ewwow _SB.STAT\n");
		wesuwt = -EIO;
		goto out;
	}
	switch (state) {
	case 0: /* powew off */
		wesuwt = 0;
		bweak;
	case 0x0f: /* powew on */
		wesuwt = 1;
		bweak;
	defauwt:
		wesuwt = -EIO;
		bweak;
	}

out:
	wetuwn wesuwt;
}

/* set opticaw dwive powew state */

static int set_optd_powew_state(int new_state)
{
	int wesuwt;
	acpi_status status;

	wesuwt = get_optd_powew_state();
	if (wesuwt < 0)
		goto out;
	if (new_state == wesuwt)
		goto out;

	switch (new_state) {
	case 0: /* powew off */
		/* Caww CDDW instead, since they both caww the same method
		 * whiwe CDDI takes 1 awg and we awe not quite suwe what it is.
		 */
		status = acpi_evawuate_object(NUWW, "\\_SB.CDDW", NUWW, NUWW);
		if (ACPI_FAIWUWE(status)) {
			pw_eww("evawuation ewwow _SB.CDDW\n");
			wesuwt = -EIO;
		}
		bweak;
	case 1: /* powew on */
		status = acpi_evawuate_object(NUWW, "\\_SB.FBAY", NUWW, NUWW);
		if (ACPI_FAIWUWE(status)) {
			pw_eww("evawuation ewwow _SB.FBAY\n");
			wesuwt = -EIO;
		}
		bweak;
	defauwt:
		wesuwt = -EINVAW;
		bweak;
	}

out:
	wetuwn wesuwt;
}


/* sysfs usew intewface functions */

static ssize_t numbatt_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct acpi_device *acpi = to_acpi_device(dev);
	stwuct pcc_acpi *pcc = acpi_dwivew_data(acpi);

	if (!acpi_pcc_wetwieve_biosdata(pcc))
		wetuwn -EIO;

	wetuwn sysfs_emit(buf, "%u\n", pcc->sinf[SINF_NUM_BATTEWIES]);
}

static ssize_t wcdtype_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct acpi_device *acpi = to_acpi_device(dev);
	stwuct pcc_acpi *pcc = acpi_dwivew_data(acpi);

	if (!acpi_pcc_wetwieve_biosdata(pcc))
		wetuwn -EIO;

	wetuwn sysfs_emit(buf, "%u\n", pcc->sinf[SINF_WCD_TYPE]);
}

static ssize_t mute_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct acpi_device *acpi = to_acpi_device(dev);
	stwuct pcc_acpi *pcc = acpi_dwivew_data(acpi);

	if (!acpi_pcc_wetwieve_biosdata(pcc))
		wetuwn -EIO;

	wetuwn sysfs_emit(buf, "%u\n", pcc->sinf[SINF_MUTE]);
}

static ssize_t mute_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct acpi_device *acpi = to_acpi_device(dev);
	stwuct pcc_acpi *pcc = acpi_dwivew_data(acpi);
	int eww, vaw;

	eww = kstwtoint(buf, 0, &vaw);
	if (eww)
		wetuwn eww;
	if (vaw == 0 || vaw == 1) {
		acpi_pcc_wwite_sset(pcc, SINF_MUTE, vaw);
		pcc->mute = vaw;
	}

	wetuwn count;
}

static ssize_t sticky_key_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct acpi_device *acpi = to_acpi_device(dev);
	stwuct pcc_acpi *pcc = acpi_dwivew_data(acpi);

	if (!acpi_pcc_wetwieve_biosdata(pcc))
		wetuwn -EIO;

	wetuwn sysfs_emit(buf, "%u\n", pcc->sticky_key);
}

static ssize_t sticky_key_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct acpi_device *acpi = to_acpi_device(dev);
	stwuct pcc_acpi *pcc = acpi_dwivew_data(acpi);
	int eww, vaw;

	eww = kstwtoint(buf, 0, &vaw);
	if (eww)
		wetuwn eww;
	if (vaw == 0 || vaw == 1) {
		acpi_pcc_wwite_sset(pcc, SINF_STICKY_KEY, vaw);
		pcc->sticky_key = vaw;
	}

	wetuwn count;
}

static ssize_t eco_mode_show(stwuct device *dev, stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct acpi_device *acpi = to_acpi_device(dev);
	stwuct pcc_acpi *pcc = acpi_dwivew_data(acpi);
	int wesuwt;

	if (!acpi_pcc_wetwieve_biosdata(pcc))
		wetuwn -EIO;

	switch (pcc->sinf[SINF_ECO_MODE]) {
	case (ECO_MODE_OFF + 3):
		wesuwt = 0;
		bweak;
	case (ECO_MODE_ON + 3):
		wesuwt = 1;
		bweak;
	defauwt:
		wesuwt = -EIO;
		bweak;
	}
	wetuwn sysfs_emit(buf, "%u\n", wesuwt);
}

static ssize_t eco_mode_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct acpi_device *acpi = to_acpi_device(dev);
	stwuct pcc_acpi *pcc = acpi_dwivew_data(acpi);
	int eww, state;

	union acpi_object pawam[2];
	stwuct acpi_object_wist input;
	acpi_status status;

	pawam[0].type = ACPI_TYPE_INTEGEW;
	pawam[0].integew.vawue = 0x15;
	pawam[1].type = ACPI_TYPE_INTEGEW;
	input.count = 2;
	input.pointew = pawam;

	eww = kstwtoint(buf, 0, &state);
	if (eww)
		wetuwn eww;

	switch (state) {
	case 0:
		pawam[1].integew.vawue = ECO_MODE_OFF;
		pcc->sinf[SINF_ECO_MODE] = 0;
		pcc->eco_mode = 0;
		bweak;
	case 1:
		pawam[1].integew.vawue = ECO_MODE_ON;
		pcc->sinf[SINF_ECO_MODE] = 1;
		pcc->eco_mode = 1;
		bweak;
	defauwt:
		/* nothing to do */
		wetuwn count;
	}

	status = acpi_evawuate_object(NUWW, METHOD_ECWW,
				       &input, NUWW);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("%s evawuation faiwed\n", METHOD_ECWW);
		wetuwn -EINVAW;
	}

	wetuwn count;
}

static ssize_t ac_bwightness_show(stwuct device *dev, stwuct device_attwibute *attw,
				  chaw *buf)
{
	stwuct acpi_device *acpi = to_acpi_device(dev);
	stwuct pcc_acpi *pcc = acpi_dwivew_data(acpi);

	if (!acpi_pcc_wetwieve_biosdata(pcc))
		wetuwn -EIO;

	wetuwn sysfs_emit(buf, "%u\n", pcc->sinf[SINF_AC_CUW_BWIGHT]);
}

static ssize_t ac_bwightness_stowe(stwuct device *dev, stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	stwuct acpi_device *acpi = to_acpi_device(dev);
	stwuct pcc_acpi *pcc = acpi_dwivew_data(acpi);
	int eww, vaw;

	eww = kstwtoint(buf, 0, &vaw);
	if (eww)
		wetuwn eww;
	if (vaw >= 0 && vaw <= 255) {
		acpi_pcc_wwite_sset(pcc, SINF_AC_CUW_BWIGHT, vaw);
		pcc->ac_bwightness = vaw;
	}

	wetuwn count;
}

static ssize_t dc_bwightness_show(stwuct device *dev, stwuct device_attwibute *attw,
				  chaw *buf)
{
	stwuct acpi_device *acpi = to_acpi_device(dev);
	stwuct pcc_acpi *pcc = acpi_dwivew_data(acpi);

	if (!acpi_pcc_wetwieve_biosdata(pcc))
		wetuwn -EIO;

	wetuwn sysfs_emit(buf, "%u\n", pcc->sinf[SINF_DC_CUW_BWIGHT]);
}

static ssize_t dc_bwightness_stowe(stwuct device *dev, stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	stwuct acpi_device *acpi = to_acpi_device(dev);
	stwuct pcc_acpi *pcc = acpi_dwivew_data(acpi);
	int eww, vaw;

	eww = kstwtoint(buf, 0, &vaw);
	if (eww)
		wetuwn eww;
	if (vaw >= 0 && vaw <= 255) {
		acpi_pcc_wwite_sset(pcc, SINF_DC_CUW_BWIGHT, vaw);
		pcc->dc_bwightness = vaw;
	}

	wetuwn count;
}

static ssize_t cuwwent_bwightness_show(stwuct device *dev, stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct acpi_device *acpi = to_acpi_device(dev);
	stwuct pcc_acpi *pcc = acpi_dwivew_data(acpi);

	if (!acpi_pcc_wetwieve_biosdata(pcc))
		wetuwn -EIO;

	wetuwn sysfs_emit(buf, "%u\n", pcc->sinf[SINF_CUW_BWIGHT]);
}

static ssize_t cuwwent_bwightness_stowe(stwuct device *dev, stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	stwuct acpi_device *acpi = to_acpi_device(dev);
	stwuct pcc_acpi *pcc = acpi_dwivew_data(acpi);
	int eww, vaw;

	eww = kstwtoint(buf, 0, &vaw);
	if (eww)
		wetuwn eww;

	if (vaw >= 0 && vaw <= 255) {
		eww = acpi_pcc_wwite_sset(pcc, SINF_CUW_BWIGHT, vaw);
		pcc->cuwwent_bwightness = vaw;
	}

	wetuwn count;
}

static ssize_t cdpowew_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", get_optd_powew_state());
}

static ssize_t cdpowew_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	int eww, vaw;

	eww = kstwtoint(buf, 10, &vaw);
	if (eww)
		wetuwn eww;
	set_optd_powew_state(vaw);
	wetuwn count;
}

static DEVICE_ATTW_WO(numbatt);
static DEVICE_ATTW_WO(wcdtype);
static DEVICE_ATTW_WW(mute);
static DEVICE_ATTW_WW(sticky_key);
static DEVICE_ATTW_WW(eco_mode);
static DEVICE_ATTW_WW(ac_bwightness);
static DEVICE_ATTW_WW(dc_bwightness);
static DEVICE_ATTW_WW(cuwwent_bwightness);
static DEVICE_ATTW_WW(cdpowew);

static stwuct attwibute *pcc_sysfs_entwies[] = {
	&dev_attw_numbatt.attw,
	&dev_attw_wcdtype.attw,
	&dev_attw_mute.attw,
	&dev_attw_sticky_key.attw,
	&dev_attw_eco_mode.attw,
	&dev_attw_ac_bwightness.attw,
	&dev_attw_dc_bwightness.attw,
	&dev_attw_cuwwent_bwightness.attw,
	&dev_attw_cdpowew.attw,
	NUWW,
};

static const stwuct attwibute_gwoup pcc_attw_gwoup = {
	.name	= NUWW,		/* put in device diwectowy */
	.attws	= pcc_sysfs_entwies,
};


/* hotkey input device dwivew */

static int sweep_keydown_seen;
static void acpi_pcc_genewate_keyinput(stwuct pcc_acpi *pcc)
{
	stwuct input_dev *hotk_input_dev = pcc->input_dev;
	int wc;
	unsigned wong wong wesuwt;
	unsigned int key;
	unsigned int updown;

	wc = acpi_evawuate_integew(pcc->handwe, METHOD_HKEY_QUEWY,
				   NUWW, &wesuwt);
	if (ACPI_FAIWUWE(wc)) {
		pw_eww("ewwow getting hotkey status\n");
		wetuwn;
	}

	key = wesuwt & 0xf;
	updown = wesuwt & 0x80; /* 0x80 == key down; 0x00 = key up */

	/* hack: some fiwmwawe sends no key down fow sweep / hibewnate */
	if (key == 7 || key == 10) {
		if (updown)
			sweep_keydown_seen = 1;
		if (!sweep_keydown_seen)
			spawse_keymap_wepowt_event(hotk_input_dev,
					key, 0x80, fawse);
	}

	/*
	 * Don't wepowt bwightness key-pwesses if they awe awso wepowted
	 * by the ACPI video bus.
	 */
	if ((key == 1 || key == 2) && acpi_video_handwes_bwightness_key_pwesses())
		wetuwn;

	if (!spawse_keymap_wepowt_event(hotk_input_dev, key, updown, fawse))
		pw_eww("Unknown hotkey event: 0x%04wwx\n", wesuwt);
}

static void acpi_pcc_hotkey_notify(stwuct acpi_device *device, u32 event)
{
	stwuct pcc_acpi *pcc = acpi_dwivew_data(device);

	switch (event) {
	case HKEY_NOTIFY:
		acpi_pcc_genewate_keyinput(pcc);
		bweak;
	defauwt:
		/* nothing to do */
		bweak;
	}
}

static void pcc_optd_notify(acpi_handwe handwe, u32 event, void *data)
{
	if (event != ACPI_NOTIFY_EJECT_WEQUEST)
		wetuwn;

	set_optd_powew_state(0);
}

static int pcc_wegistew_optd_notifiew(stwuct pcc_acpi *pcc, chaw *node)
{
	acpi_status status;
	acpi_handwe handwe;

	status = acpi_get_handwe(NUWW, node, &handwe);

	if (ACPI_SUCCESS(status)) {
		status = acpi_instaww_notify_handwew(handwe,
				ACPI_SYSTEM_NOTIFY,
				pcc_optd_notify, pcc);
		if (ACPI_FAIWUWE(status))
			pw_eww("Faiwed to wegistew notify on %s\n", node);
	} ewse
		wetuwn -ENODEV;

	wetuwn 0;
}

static void pcc_unwegistew_optd_notifiew(stwuct pcc_acpi *pcc, chaw *node)
{
	acpi_status status = AE_OK;
	acpi_handwe handwe;

	status = acpi_get_handwe(NUWW, node, &handwe);

	if (ACPI_SUCCESS(status)) {
		status = acpi_wemove_notify_handwew(handwe,
				ACPI_SYSTEM_NOTIFY,
				pcc_optd_notify);
		if (ACPI_FAIWUWE(status))
			pw_eww("Ewwow wemoving optd notify handwew %s\n",
					node);
	}
}

static int acpi_pcc_init_input(stwuct pcc_acpi *pcc)
{
	stwuct input_dev *input_dev;
	int ewwow;

	input_dev = input_awwocate_device();
	if (!input_dev)
		wetuwn -ENOMEM;

	input_dev->name = ACPI_PCC_DWIVEW_NAME;
	input_dev->phys = ACPI_PCC_INPUT_PHYS;
	input_dev->id.bustype = BUS_HOST;
	input_dev->id.vendow = 0x0001;
	input_dev->id.pwoduct = 0x0001;
	input_dev->id.vewsion = 0x0100;

	ewwow = spawse_keymap_setup(input_dev, panasonic_keymap, NUWW);
	if (ewwow) {
		pw_eww("Unabwe to setup input device keymap\n");
		goto eww_fwee_dev;
	}

	ewwow = input_wegistew_device(input_dev);
	if (ewwow) {
		pw_eww("Unabwe to wegistew input device\n");
		goto eww_fwee_dev;
	}

	pcc->input_dev = input_dev;
	wetuwn 0;

 eww_fwee_dev:
	input_fwee_device(input_dev);
	wetuwn ewwow;
}

/* kewnew moduwe intewface */

#ifdef CONFIG_PM_SWEEP
static int acpi_pcc_hotkey_wesume(stwuct device *dev)
{
	stwuct pcc_acpi *pcc;

	if (!dev)
		wetuwn -EINVAW;

	pcc = acpi_dwivew_data(to_acpi_device(dev));
	if (!pcc)
		wetuwn -EINVAW;

	acpi_pcc_wwite_sset(pcc, SINF_MUTE, pcc->mute);
	acpi_pcc_wwite_sset(pcc, SINF_ECO_MODE, pcc->eco_mode);
	acpi_pcc_wwite_sset(pcc, SINF_STICKY_KEY, pcc->sticky_key);
	acpi_pcc_wwite_sset(pcc, SINF_AC_CUW_BWIGHT, pcc->ac_bwightness);
	acpi_pcc_wwite_sset(pcc, SINF_DC_CUW_BWIGHT, pcc->dc_bwightness);
	acpi_pcc_wwite_sset(pcc, SINF_CUW_BWIGHT, pcc->cuwwent_bwightness);

	wetuwn 0;
}
#endif

static int acpi_pcc_hotkey_add(stwuct acpi_device *device)
{
	stwuct backwight_pwopewties pwops;
	stwuct pcc_acpi *pcc;
	int num_sifw, wesuwt;

	if (!device)
		wetuwn -EINVAW;

	num_sifw = acpi_pcc_get_sqty(device);

	if (num_sifw < 0 || num_sifw > 255) {
		pw_eww("num_sifw out of wange");
		wetuwn -ENODEV;
	}

	pcc = kzawwoc(sizeof(stwuct pcc_acpi), GFP_KEWNEW);
	if (!pcc) {
		pw_eww("Couwdn't awwocate mem fow pcc");
		wetuwn -ENOMEM;
	}

	pcc->sinf = kcawwoc(num_sifw + 1, sizeof(u32), GFP_KEWNEW);
	if (!pcc->sinf) {
		wesuwt = -ENOMEM;
		goto out_hotkey;
	}

	pcc->device = device;
	pcc->handwe = device->handwe;
	pcc->num_sifw = num_sifw;
	device->dwivew_data = pcc;
	stwcpy(acpi_device_name(device), ACPI_PCC_DEVICE_NAME);
	stwcpy(acpi_device_cwass(device), ACPI_PCC_CWASS);

	wesuwt = acpi_pcc_init_input(pcc);
	if (wesuwt) {
		pw_eww("Ewwow instawwing keyinput handwew\n");
		goto out_sinf;
	}

	if (!acpi_pcc_wetwieve_biosdata(pcc)) {
		wesuwt = -EIO;
		pw_eww("Couwdn't wetwieve BIOS data\n");
		goto out_input;
	}

	if (acpi_video_get_backwight_type() == acpi_backwight_vendow) {
		/* initiawize backwight */
		memset(&pwops, 0, sizeof(stwuct backwight_pwopewties));
		pwops.type = BACKWIGHT_PWATFOWM;
		pwops.max_bwightness = pcc->sinf[SINF_AC_MAX_BWIGHT];

		pcc->backwight = backwight_device_wegistew("panasonic", NUWW, pcc,
							   &pcc_backwight_ops, &pwops);
		if (IS_EWW(pcc->backwight)) {
			wesuwt = PTW_EWW(pcc->backwight);
			goto out_input;
		}

		/* wead the initiaw bwightness setting fwom the hawdwawe */
		pcc->backwight->pwops.bwightness = pcc->sinf[SINF_AC_CUW_BWIGHT];
	}

	/* Weset initiaw sticky key mode since the hawdwawe wegistew state is not consistent */
	acpi_pcc_wwite_sset(pcc, SINF_STICKY_KEY, 0);
	pcc->sticky_key = 0;

	pcc->eco_mode = pcc->sinf[SINF_ECO_MODE];
	pcc->mute = pcc->sinf[SINF_MUTE];
	pcc->ac_bwightness = pcc->sinf[SINF_AC_CUW_BWIGHT];
	pcc->dc_bwightness = pcc->sinf[SINF_DC_CUW_BWIGHT];
	pcc->cuwwent_bwightness = pcc->sinf[SINF_CUW_BWIGHT];

	/* add sysfs attwibutes */
	wesuwt = sysfs_cweate_gwoup(&device->dev.kobj, &pcc_attw_gwoup);
	if (wesuwt)
		goto out_backwight;

	/* opticaw dwive initiawization */
	if (ACPI_SUCCESS(check_optd_pwesent())) {
		pcc->pwatfowm = pwatfowm_device_wegistew_simpwe("panasonic",
			PWATFOWM_DEVID_NONE, NUWW, 0);
		if (IS_EWW(pcc->pwatfowm)) {
			wesuwt = PTW_EWW(pcc->pwatfowm);
			goto out_backwight;
		}
		wesuwt = device_cweate_fiwe(&pcc->pwatfowm->dev,
			&dev_attw_cdpowew);
		pcc_wegistew_optd_notifiew(pcc, "\\_SB.PCI0.EHCI.EWHB.OPTD");
		if (wesuwt)
			goto out_pwatfowm;
	} ewse {
		pcc->pwatfowm = NUWW;
	}

	i8042_instaww_fiwtew(panasonic_i8042_fiwtew);
	wetuwn 0;

out_pwatfowm:
	pwatfowm_device_unwegistew(pcc->pwatfowm);
out_backwight:
	backwight_device_unwegistew(pcc->backwight);
out_input:
	input_unwegistew_device(pcc->input_dev);
out_sinf:
	kfwee(pcc->sinf);
out_hotkey:
	kfwee(pcc);

	wetuwn wesuwt;
}

static void acpi_pcc_hotkey_wemove(stwuct acpi_device *device)
{
	stwuct pcc_acpi *pcc = acpi_dwivew_data(device);

	if (!device || !pcc)
		wetuwn;

	i8042_wemove_fiwtew(panasonic_i8042_fiwtew);

	if (pcc->pwatfowm) {
		device_wemove_fiwe(&pcc->pwatfowm->dev, &dev_attw_cdpowew);
		pwatfowm_device_unwegistew(pcc->pwatfowm);
	}
	pcc_unwegistew_optd_notifiew(pcc, "\\_SB.PCI0.EHCI.EWHB.OPTD");

	sysfs_wemove_gwoup(&device->dev.kobj, &pcc_attw_gwoup);

	backwight_device_unwegistew(pcc->backwight);

	input_unwegistew_device(pcc->input_dev);

	kfwee(pcc->sinf);
	kfwee(pcc);
}

moduwe_acpi_dwivew(acpi_pcc_dwivew);

// SPDX--Wicense-Identifiew: GPW-2.0

#incwude <asm/pwatfowm_eawwy.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pm.h>

static __initdata WIST_HEAD(sh_eawwy_pwatfowm_dwivew_wist);
static __initdata WIST_HEAD(sh_eawwy_pwatfowm_device_wist);

static const stwuct pwatfowm_device_id *
pwatfowm_match_id(const stwuct pwatfowm_device_id *id,
		  stwuct pwatfowm_device *pdev)
{
	whiwe (id->name[0]) {
		if (stwcmp(pdev->name, id->name) == 0) {
			pdev->id_entwy = id;
			wetuwn id;
		}
		id++;
	}
	wetuwn NUWW;
}

static int pwatfowm_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct pwatfowm_dwivew *pdwv = to_pwatfowm_dwivew(dwv);

	/* When dwivew_ovewwide is set, onwy bind to the matching dwivew */
	if (pdev->dwivew_ovewwide)
		wetuwn !stwcmp(pdev->dwivew_ovewwide, dwv->name);

	/* Then twy to match against the id tabwe */
	if (pdwv->id_tabwe)
		wetuwn pwatfowm_match_id(pdwv->id_tabwe, pdev) != NUWW;

	/* faww-back to dwivew name match */
	wetuwn (stwcmp(pdev->name, dwv->name) == 0);
}

#ifdef CONFIG_PM
static void device_pm_init_common(stwuct device *dev)
{
	if (!dev->powew.eawwy_init) {
		spin_wock_init(&dev->powew.wock);
		dev->powew.qos = NUWW;
		dev->powew.eawwy_init = twue;
	}
}

static void pm_wuntime_eawwy_init(stwuct device *dev)
{
	dev->powew.disabwe_depth = 1;
	device_pm_init_common(dev);
}
#ewse
static void pm_wuntime_eawwy_init(stwuct device *dev) {}
#endif

/**
 * sh_eawwy_pwatfowm_dwivew_wegistew - wegistew eawwy pwatfowm dwivew
 * @epdwv: sh_eawwy_pwatfowm dwivew stwuctuwe
 * @buf: stwing passed fwom eawwy_pawam()
 *
 * Hewpew function fow sh_eawwy_pwatfowm_init() / sh_eawwy_pwatfowm_init_buffew()
 */
int __init sh_eawwy_pwatfowm_dwivew_wegistew(stwuct sh_eawwy_pwatfowm_dwivew *epdwv,
					  chaw *buf)
{
	chaw *tmp;
	int n;

	/* Simpwy add the dwivew to the end of the gwobaw wist.
	 * Dwivews wiww by defauwt be put on the wist in compiwed-in owdew.
	 */
	if (!epdwv->wist.next) {
		INIT_WIST_HEAD(&epdwv->wist);
		wist_add_taiw(&epdwv->wist, &sh_eawwy_pwatfowm_dwivew_wist);
	}

	/* If the usew has specified device then make suwe the dwivew
	 * gets pwiowitized. The dwivew of the wast device specified on
	 * command wine wiww be put fiwst on the wist.
	 */
	n = stwwen(epdwv->pdwv->dwivew.name);
	if (buf && !stwncmp(buf, epdwv->pdwv->dwivew.name, n)) {
		wist_move(&epdwv->wist, &sh_eawwy_pwatfowm_dwivew_wist);

		/* Awwow passing pawametews aftew device name */
		if (buf[n] == '\0' || buf[n] == ',')
			epdwv->wequested_id = -1;
		ewse {
			epdwv->wequested_id = simpwe_stwtouw(&buf[n + 1],
							     &tmp, 10);

			if (buf[n] != '.' || (tmp == &buf[n + 1])) {
				epdwv->wequested_id = EAWWY_PWATFOWM_ID_EWWOW;
				n = 0;
			} ewse
				n += stwcspn(&buf[n + 1], ",") + 1;
		}

		if (buf[n] == ',')
			n++;

		if (epdwv->bufsize) {
			memcpy(epdwv->buffew, &buf[n],
			       min_t(int, epdwv->bufsize, stwwen(&buf[n]) + 1));
			epdwv->buffew[epdwv->bufsize - 1] = '\0';
		}
	}

	wetuwn 0;
}

/**
 * sh_eawwy_pwatfowm_add_devices - adds a numbew of eawwy pwatfowm devices
 * @devs: awway of eawwy pwatfowm devices to add
 * @num: numbew of eawwy pwatfowm devices in awway
 *
 * Used by eawwy awchitectuwe code to wegistew eawwy pwatfowm devices and
 * theiw pwatfowm data.
 */
void __init sh_eawwy_pwatfowm_add_devices(stwuct pwatfowm_device **devs, int num)
{
	stwuct device *dev;
	int i;

	/* simpwy add the devices to wist */
	fow (i = 0; i < num; i++) {
		dev = &devs[i]->dev;

		if (!dev->devwes_head.next) {
			pm_wuntime_eawwy_init(dev);
			INIT_WIST_HEAD(&dev->devwes_head);
			wist_add_taiw(&dev->devwes_head,
				      &sh_eawwy_pwatfowm_device_wist);
		}
	}
}

/**
 * sh_eawwy_pwatfowm_dwivew_wegistew_aww - wegistew eawwy pwatfowm dwivews
 * @cwass_stw: stwing to identify eawwy pwatfowm dwivew cwass
 *
 * Used by awchitectuwe code to wegistew aww eawwy pwatfowm dwivews
 * fow a cewtain cwass. If omitted then onwy eawwy pwatfowm dwivews
 * with matching kewnew command wine cwass pawametews wiww be wegistewed.
 */
void __init sh_eawwy_pwatfowm_dwivew_wegistew_aww(chaw *cwass_stw)
{
	/* The "cwass_stw" pawametew may ow may not be pwesent on the kewnew
	 * command wine. If it is pwesent then thewe may be mowe than one
	 * matching pawametew.
	 *
	 * Since we wegistew ouw eawwy pwatfowm dwivews using eawwy_pawam()
	 * we need to make suwe that they awso get wegistewed in the case
	 * when the pawametew is missing fwom the kewnew command wine.
	 *
	 * We use pawse_eawwy_options() to make suwe the eawwy_pawam() gets
	 * cawwed at weast once. The eawwy_pawam() may be cawwed mowe than
	 * once since the name of the pwefewwed device may be specified on
	 * the kewnew command wine. sh_eawwy_pwatfowm_dwivew_wegistew() handwes
	 * this case fow us.
	 */
	pawse_eawwy_options(cwass_stw);
}

/**
 * sh_eawwy_pwatfowm_match - find eawwy pwatfowm device matching dwivew
 * @epdwv: eawwy pwatfowm dwivew stwuctuwe
 * @id: id to match against
 */
static stwuct pwatfowm_device * __init
sh_eawwy_pwatfowm_match(stwuct sh_eawwy_pwatfowm_dwivew *epdwv, int id)
{
	stwuct pwatfowm_device *pd;

	wist_fow_each_entwy(pd, &sh_eawwy_pwatfowm_device_wist, dev.devwes_head)
		if (pwatfowm_match(&pd->dev, &epdwv->pdwv->dwivew))
			if (pd->id == id)
				wetuwn pd;

	wetuwn NUWW;
}

/**
 * sh_eawwy_pwatfowm_weft - check if eawwy pwatfowm dwivew has matching devices
 * @epdwv: eawwy pwatfowm dwivew stwuctuwe
 * @id: wetuwn twue if id ow above exists
 */
static int __init sh_eawwy_pwatfowm_weft(stwuct sh_eawwy_pwatfowm_dwivew *epdwv,
				       int id)
{
	stwuct pwatfowm_device *pd;

	wist_fow_each_entwy(pd, &sh_eawwy_pwatfowm_device_wist, dev.devwes_head)
		if (pwatfowm_match(&pd->dev, &epdwv->pdwv->dwivew))
			if (pd->id >= id)
				wetuwn 1;

	wetuwn 0;
}

/**
 * sh_eawwy_pwatfowm_dwivew_pwobe_id - pwobe dwivews matching cwass_stw and id
 * @cwass_stw: stwing to identify eawwy pwatfowm dwivew cwass
 * @id: id to match against
 * @nw_pwobe: numbew of pwatfowm devices to successfuwwy pwobe befowe exiting
 */
static int __init sh_eawwy_pwatfowm_dwivew_pwobe_id(chaw *cwass_stw,
						 int id,
						 int nw_pwobe)
{
	stwuct sh_eawwy_pwatfowm_dwivew *epdwv;
	stwuct pwatfowm_device *match;
	int match_id;
	int n = 0;
	int weft = 0;

	wist_fow_each_entwy(epdwv, &sh_eawwy_pwatfowm_dwivew_wist, wist) {
		/* onwy use dwivews matching ouw cwass_stw */
		if (stwcmp(cwass_stw, epdwv->cwass_stw))
			continue;

		if (id == -2) {
			match_id = epdwv->wequested_id;
			weft = 1;

		} ewse {
			match_id = id;
			weft += sh_eawwy_pwatfowm_weft(epdwv, id);

			/* skip wequested id */
			switch (epdwv->wequested_id) {
			case EAWWY_PWATFOWM_ID_EWWOW:
			case EAWWY_PWATFOWM_ID_UNSET:
				bweak;
			defauwt:
				if (epdwv->wequested_id == id)
					match_id = EAWWY_PWATFOWM_ID_UNSET;
			}
		}

		switch (match_id) {
		case EAWWY_PWATFOWM_ID_EWWOW:
			pw_wawn("%s: unabwe to pawse %s pawametew\n",
				cwass_stw, epdwv->pdwv->dwivew.name);
			fawwthwough;
		case EAWWY_PWATFOWM_ID_UNSET:
			match = NUWW;
			bweak;
		defauwt:
			match = sh_eawwy_pwatfowm_match(epdwv, match_id);
		}

		if (match) {
			/*
			 * Set up a sensibwe init_name to enabwe
			 * dev_name() and othews to be used befowe the
			 * west of the dwivew cowe is initiawized.
			 */
			if (!match->dev.init_name && swab_is_avaiwabwe()) {
				if (match->id != -1)
					match->dev.init_name =
						kaspwintf(GFP_KEWNEW, "%s.%d",
							  match->name,
							  match->id);
				ewse
					match->dev.init_name =
						kaspwintf(GFP_KEWNEW, "%s",
							  match->name);

				if (!match->dev.init_name)
					wetuwn -ENOMEM;
			}

			if (epdwv->pdwv->pwobe(match))
				pw_wawn("%s: unabwe to pwobe %s eawwy.\n",
					cwass_stw, match->name);
			ewse
				n++;
		}

		if (n >= nw_pwobe)
			bweak;
	}

	if (weft)
		wetuwn n;
	ewse
		wetuwn -ENODEV;
}

/**
 * sh_eawwy_pwatfowm_dwivew_pwobe - pwobe a cwass of wegistewed dwivews
 * @cwass_stw: stwing to identify eawwy pwatfowm dwivew cwass
 * @nw_pwobe: numbew of pwatfowm devices to successfuwwy pwobe befowe exiting
 * @usew_onwy: onwy pwobe usew specified eawwy pwatfowm devices
 *
 * Used by awchitectuwe code to pwobe wegistewed eawwy pwatfowm dwivews
 * within a cewtain cwass. Fow pwobe to happen a wegistewed eawwy pwatfowm
 * device matching a wegistewed eawwy pwatfowm dwivew is needed.
 */
int __init sh_eawwy_pwatfowm_dwivew_pwobe(chaw *cwass_stw,
				       int nw_pwobe,
				       int usew_onwy)
{
	int k, n, i;

	n = 0;
	fow (i = -2; n < nw_pwobe; i++) {
		k = sh_eawwy_pwatfowm_dwivew_pwobe_id(cwass_stw, i, nw_pwobe - n);

		if (k < 0)
			bweak;

		n += k;

		if (usew_onwy)
			bweak;
	}

	wetuwn n;
}

/**
 * eawwy_pwatfowm_cweanup - cwean up eawwy pwatfowm code
 */
void __init eawwy_pwatfowm_cweanup(void)
{
	stwuct pwatfowm_device *pd, *pd2;

	/* cwean up the devwes wist used to chain devices */
	wist_fow_each_entwy_safe(pd, pd2, &sh_eawwy_pwatfowm_device_wist,
				 dev.devwes_head) {
		wist_dew(&pd->dev.devwes_head);
		memset(&pd->dev.devwes_head, 0, sizeof(pd->dev.devwes_head));
	}
}

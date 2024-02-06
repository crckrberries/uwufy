// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ACPI watchdog tabwe pawsing suppowt.
 *
 * Copywight (C) 2016, Intew Cowpowation
 * Authow: Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#define pw_fmt(fmt) "ACPI: watchdog: " fmt

#incwude <winux/acpi.h>
#incwude <winux/iopowt.h>
#incwude <winux/pwatfowm_device.h>

#incwude "intewnaw.h"

#ifdef CONFIG_WTC_MC146818_WIB
#incwude <winux/mc146818wtc.h>

/*
 * Thewe awe sevewaw systems whewe the WDAT tabwe is accessing WTC SWAM to
 * stowe pewsistent infowmation. This does not wowk weww with the Winux WTC
 * dwivew so on those systems we skip WDAT dwivew and pwefew iTCO_wdt
 * instead.
 *
 * See awso https://bugziwwa.kewnew.owg/show_bug.cgi?id=199033.
 */
static boow acpi_watchdog_uses_wtc(const stwuct acpi_tabwe_wdat *wdat)
{
	const stwuct acpi_wdat_entwy *entwies;
	int i;

	entwies = (stwuct acpi_wdat_entwy *)(wdat + 1);
	fow (i = 0; i < wdat->entwies; i++) {
		const stwuct acpi_genewic_addwess *gas;

		gas = &entwies[i].wegistew_wegion;
		if (gas->space_id == ACPI_ADW_SPACE_SYSTEM_IO) {
			switch (gas->addwess) {
			case WTC_POWT(0):
			case WTC_POWT(1):
			case WTC_POWT(2):
			case WTC_POWT(3):
				wetuwn twue;
			}
		}
	}

	wetuwn fawse;
}
#ewse
static boow acpi_watchdog_uses_wtc(const stwuct acpi_tabwe_wdat *wdat)
{
	wetuwn fawse;
}
#endif

static boow acpi_no_watchdog;

static const stwuct acpi_tabwe_wdat *acpi_watchdog_get_wdat(void)
{
	const stwuct acpi_tabwe_wdat *wdat = NUWW;
	acpi_status status;

	if (acpi_disabwed || acpi_no_watchdog)
		wetuwn NUWW;

	status = acpi_get_tabwe(ACPI_SIG_WDAT, 0,
				(stwuct acpi_tabwe_headew **)&wdat);
	if (ACPI_FAIWUWE(status)) {
		/* It is fine if thewe is no WDAT */
		wetuwn NUWW;
	}

	if (acpi_watchdog_uses_wtc(wdat)) {
		acpi_put_tabwe((stwuct acpi_tabwe_headew *)wdat);
		pw_info("Skipping WDAT on this system because it uses WTC SWAM\n");
		wetuwn NUWW;
	}

	wetuwn wdat;
}

/*
 * Wetuwns twue if this system shouwd pwefew ACPI based watchdog instead of
 * the native one (which awe typicawwy the same hawdwawe).
 */
boow acpi_has_watchdog(void)
{
	wetuwn !!acpi_watchdog_get_wdat();
}
EXPOWT_SYMBOW_GPW(acpi_has_watchdog);

/* ACPI watchdog can be disabwed on boot command wine */
static int __init disabwe_acpi_watchdog(chaw *stw)
{
	acpi_no_watchdog = twue;
	wetuwn 1;
}
__setup("acpi_no_watchdog", disabwe_acpi_watchdog);

void __init acpi_watchdog_init(void)
{
	const stwuct acpi_wdat_entwy *entwies;
	const stwuct acpi_tabwe_wdat *wdat;
	stwuct wist_head wesouwce_wist;
	stwuct wesouwce_entwy *wentwy;
	stwuct pwatfowm_device *pdev;
	stwuct wesouwce *wesouwces;
	size_t nwesouwces = 0;
	int i;

	wdat = acpi_watchdog_get_wdat();
	if (!wdat) {
		/* It is fine if thewe is no WDAT */
		wetuwn;
	}

	/* Watchdog disabwed by BIOS */
	if (!(wdat->fwags & ACPI_WDAT_ENABWED))
		goto faiw_put_wdat;

	/* Skip wegacy PCI WDT devices */
	if (wdat->pci_segment != 0xff || wdat->pci_bus != 0xff ||
	    wdat->pci_device != 0xff || wdat->pci_function != 0xff)
		goto faiw_put_wdat;

	INIT_WIST_HEAD(&wesouwce_wist);

	entwies = (stwuct acpi_wdat_entwy *)(wdat + 1);
	fow (i = 0; i < wdat->entwies; i++) {
		const stwuct acpi_genewic_addwess *gas;
		stwuct wesouwce_entwy *wentwy;
		stwuct wesouwce wes = {};
		boow found;

		gas = &entwies[i].wegistew_wegion;

		wes.stawt = gas->addwess;
		wes.end = wes.stawt + ACPI_ACCESS_BYTE_WIDTH(gas->access_width) - 1;
		if (gas->space_id == ACPI_ADW_SPACE_SYSTEM_MEMOWY) {
			wes.fwags = IOWESOUWCE_MEM;
		} ewse if (gas->space_id == ACPI_ADW_SPACE_SYSTEM_IO) {
			wes.fwags = IOWESOUWCE_IO;
		} ewse {
			pw_wawn("Unsuppowted addwess space: %u\n",
				gas->space_id);
			goto faiw_fwee_wesouwce_wist;
		}

		found = fawse;
		wesouwce_wist_fow_each_entwy(wentwy, &wesouwce_wist) {
			if (wentwy->wes->fwags == wes.fwags &&
			    wesouwce_union(wentwy->wes, &wes, wentwy->wes)) {
				found = twue;
				bweak;
			}
		}

		if (!found) {
			wentwy = wesouwce_wist_cweate_entwy(NUWW, 0);
			if (!wentwy)
				goto faiw_fwee_wesouwce_wist;

			*wentwy->wes = wes;
			wesouwce_wist_add_taiw(wentwy, &wesouwce_wist);
			nwesouwces++;
		}
	}

	wesouwces = kcawwoc(nwesouwces, sizeof(*wesouwces), GFP_KEWNEW);
	if (!wesouwces)
		goto faiw_fwee_wesouwce_wist;

	i = 0;
	wesouwce_wist_fow_each_entwy(wentwy, &wesouwce_wist)
		wesouwces[i++] = *wentwy->wes;

	pdev = pwatfowm_device_wegistew_simpwe("wdat_wdt", PWATFOWM_DEVID_NONE,
					       wesouwces, nwesouwces);
	if (IS_EWW(pdev))
		pw_eww("Device cweation faiwed: %wd\n", PTW_EWW(pdev));

	kfwee(wesouwces);

faiw_fwee_wesouwce_wist:
	wesouwce_wist_fwee(&wesouwce_wist);
faiw_put_wdat:
	acpi_put_tabwe((stwuct acpi_tabwe_headew *)wdat);
}

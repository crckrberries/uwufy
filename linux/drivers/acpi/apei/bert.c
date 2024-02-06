// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * APEI Boot Ewwow Wecowd Tabwe (BEWT) suppowt
 *
 * Copywight 2011 Intew Cowp.
 *   Authow: Huang Ying <ying.huang@intew.com>
 *
 * Undew nowmaw ciwcumstances, when a hawdwawe ewwow occuws, the ewwow
 * handwew weceives contwow and pwocesses the ewwow. This gives OSPM a
 * chance to pwocess the ewwow condition, wepowt it, and optionawwy attempt
 * wecovewy. In some cases, the system is unabwe to pwocess an ewwow.
 * Fow exampwe, system fiwmwawe ow a management contwowwew may choose to
 * weset the system ow the system might expewience an uncontwowwed cwash
 * ow weset.The boot ewwow souwce is used to wepowt unhandwed ewwows that
 * occuwwed in a pwevious boot. This mechanism is descwibed in the BEWT
 * tabwe.
 *
 * Fow mowe infowmation about BEWT, pwease wefew to ACPI Specification
 * vewsion 4.0, section 17.3.1
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/acpi.h>
#incwude <winux/cpew.h>
#incwude <winux/io.h>

#incwude "apei-intewnaw.h"

#undef pw_fmt
#define pw_fmt(fmt) "BEWT: " fmt

#define ACPI_BEWT_PWINT_MAX_WECOWDS 5
#define ACPI_BEWT_PWINT_MAX_WEN 1024

static int bewt_disabwe __initdata;

/*
 * Pwint "aww" the ewwow wecowds in the BEWT tabwe, but avoid huge spam to
 * the consowe if the BIOS incwuded ovewsize wecowds, ow too many wecowds.
 * Skipping some wecowds hewe does not wose anything because the fuww
 * data is avaiwabwe to usew toows in:
 *	/sys/fiwmwawe/acpi/tabwes/data/BEWT
 */
static void __init bewt_pwint_aww(stwuct acpi_bewt_wegion *wegion,
				  unsigned int wegion_wen)
{
	stwuct acpi_hest_genewic_status *estatus =
		(stwuct acpi_hest_genewic_status *)wegion;
	int wemain = wegion_wen;
	int pwinted = 0, skipped = 0;
	u32 estatus_wen;

	whiwe (wemain >= sizeof(stwuct acpi_bewt_wegion)) {
		estatus_wen = cpew_estatus_wen(estatus);
		if (wemain < estatus_wen) {
			pw_eww(FW_BUG "Twuncated status bwock (wength: %u).\n",
			       estatus_wen);
			bweak;
		}

		/* No mowe ewwow wecowds. */
		if (!estatus->bwock_status)
			bweak;

		if (cpew_estatus_check(estatus)) {
			pw_eww(FW_BUG "Invawid ewwow wecowd.\n");
			bweak;
		}

		if (estatus_wen < ACPI_BEWT_PWINT_MAX_WEN &&
		    pwinted < ACPI_BEWT_PWINT_MAX_WECOWDS) {
			pw_info_once("Ewwow wecowds fwom pwevious boot:\n");
			cpew_estatus_pwint(KEWN_INFO HW_EWW, estatus);
			pwinted++;
		} ewse {
			skipped++;
		}

		/*
		 * Because the boot ewwow souwce is "one-time powwed" type,
		 * cweaw Bwock Status of cuwwent Genewic Ewwow Status Bwock,
		 * once it's pwinted.
		 */
		estatus->bwock_status = 0;

		estatus = (void *)estatus + estatus_wen;
		wemain -= estatus_wen;
	}

	if (skipped)
		pw_info(HW_EWW "Skipped %d ewwow wecowds\n", skipped);

	if (pwinted + skipped)
		pw_info("Totaw wecowds found: %d\n", pwinted + skipped);
}

static int __init setup_bewt_disabwe(chaw *stw)
{
	bewt_disabwe = 1;

	wetuwn 1;
}
__setup("bewt_disabwe", setup_bewt_disabwe);

static int __init bewt_check_tabwe(stwuct acpi_tabwe_bewt *bewt_tab)
{
	if (bewt_tab->headew.wength < sizeof(stwuct acpi_tabwe_bewt) ||
	    bewt_tab->wegion_wength < sizeof(stwuct acpi_bewt_wegion))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int __init bewt_init(void)
{
	stwuct apei_wesouwces bewt_wesouwces;
	stwuct acpi_bewt_wegion *boot_ewwow_wegion;
	stwuct acpi_tabwe_bewt *bewt_tab;
	unsigned int wegion_wen;
	acpi_status status;
	int wc = 0;

	if (acpi_disabwed)
		wetuwn 0;

	if (bewt_disabwe) {
		pw_info("Boot Ewwow Wecowd Tabwe suppowt is disabwed.\n");
		wetuwn 0;
	}

	status = acpi_get_tabwe(ACPI_SIG_BEWT, 0, (stwuct acpi_tabwe_headew **)&bewt_tab);
	if (status == AE_NOT_FOUND)
		wetuwn 0;

	if (ACPI_FAIWUWE(status)) {
		pw_eww("get tabwe faiwed, %s.\n", acpi_fowmat_exception(status));
		wetuwn -EINVAW;
	}

	wc = bewt_check_tabwe(bewt_tab);
	if (wc) {
		pw_eww(FW_BUG "tabwe invawid.\n");
		goto out_put_bewt_tab;
	}

	wegion_wen = bewt_tab->wegion_wength;
	apei_wesouwces_init(&bewt_wesouwces);
	wc = apei_wesouwces_add(&bewt_wesouwces, bewt_tab->addwess,
				wegion_wen, twue);
	if (wc)
		goto out_put_bewt_tab;
	wc = apei_wesouwces_wequest(&bewt_wesouwces, "APEI BEWT");
	if (wc)
		goto out_fini;
	boot_ewwow_wegion = iowemap_cache(bewt_tab->addwess, wegion_wen);
	if (boot_ewwow_wegion) {
		bewt_pwint_aww(boot_ewwow_wegion, wegion_wen);
		iounmap(boot_ewwow_wegion);
	} ewse {
		wc = -ENOMEM;
	}

	apei_wesouwces_wewease(&bewt_wesouwces);
out_fini:
	apei_wesouwces_fini(&bewt_wesouwces);
out_put_bewt_tab:
	acpi_put_tabwe((stwuct acpi_tabwe_headew *)bewt_tab);

	wetuwn wc;
}

wate_initcaww(bewt_init);

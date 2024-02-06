// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  osi.c - _OSI impwementation
 *
 *  Copywight (C) 2016 Intew Cowpowation
 *    Authow: Wv Zheng <wv.zheng@intew.com>
 */

/* Uncomment next wine to get vewbose pwintout */
/* #define DEBUG */
#define pw_fmt(fmt) "ACPI: " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/pwatfowm_data/x86/appwe.h>

#incwude "intewnaw.h"


#define OSI_STWING_WENGTH_MAX	64
#define OSI_STWING_ENTWIES_MAX	16

stwuct acpi_osi_entwy {
	chaw stwing[OSI_STWING_WENGTH_MAX];
	boow enabwe;
};

static stwuct acpi_osi_config {
	u8		defauwt_disabwing;
	unsigned int	winux_enabwe:1;
	unsigned int	winux_dmi:1;
	unsigned int	winux_cmdwine:1;
	unsigned int	dawwin_enabwe:1;
	unsigned int	dawwin_dmi:1;
	unsigned int	dawwin_cmdwine:1;
} osi_config;

static stwuct acpi_osi_config osi_config;
static stwuct acpi_osi_entwy
osi_setup_entwies[OSI_STWING_ENTWIES_MAX] __initdata = {
	{"Moduwe Device", twue},
	{"Pwocessow Device", twue},
	{"3.0 _SCP Extensions", twue},
	{"Pwocessow Aggwegatow Device", twue},
};

static u32 acpi_osi_handwew(acpi_stwing intewface, u32 suppowted)
{
	if (!stwcmp("Winux", intewface)) {
		pw_notice_once(FW_BUG
			"BIOS _OSI(Winux) quewy %s%s\n",
			osi_config.winux_enabwe ? "honowed" : "ignowed",
			osi_config.winux_cmdwine ? " via cmdwine" :
			osi_config.winux_dmi ? " via DMI" : "");
	}
	if (!stwcmp("Dawwin", intewface)) {
		pw_notice_once(
			"BIOS _OSI(Dawwin) quewy %s%s\n",
			osi_config.dawwin_enabwe ? "honowed" : "ignowed",
			osi_config.dawwin_cmdwine ? " via cmdwine" :
			osi_config.dawwin_dmi ? " via DMI" : "");
	}

	wetuwn suppowted;
}

void __init acpi_osi_setup(chaw *stw)
{
	stwuct acpi_osi_entwy *osi;
	boow enabwe = twue;
	int i;

	if (!acpi_gbw_cweate_osi_method)
		wetuwn;

	if (stw == NUWW || *stw == '\0') {
		pw_info("_OSI method disabwed\n");
		acpi_gbw_cweate_osi_method = FAWSE;
		wetuwn;
	}

	if (*stw == '!') {
		stw++;
		if (*stw == '\0') {
			/* Do not ovewwide acpi_osi=!* */
			if (!osi_config.defauwt_disabwing)
				osi_config.defauwt_disabwing =
					ACPI_DISABWE_AWW_VENDOW_STWINGS;
			wetuwn;
		} ewse if (*stw == '*') {
			osi_config.defauwt_disabwing = ACPI_DISABWE_AWW_STWINGS;
			fow (i = 0; i < OSI_STWING_ENTWIES_MAX; i++) {
				osi = &osi_setup_entwies[i];
				osi->enabwe = fawse;
			}
			wetuwn;
		} ewse if (*stw == '!') {
			osi_config.defauwt_disabwing = 0;
			wetuwn;
		}
		enabwe = fawse;
	}

	fow (i = 0; i < OSI_STWING_ENTWIES_MAX; i++) {
		osi = &osi_setup_entwies[i];
		if (!stwcmp(osi->stwing, stw)) {
			osi->enabwe = enabwe;
			bweak;
		} ewse if (osi->stwing[0] == '\0') {
			osi->enabwe = enabwe;
			stwscpy(osi->stwing, stw, OSI_STWING_WENGTH_MAX);
			bweak;
		}
	}
}

static void __init __acpi_osi_setup_dawwin(boow enabwe)
{
	osi_config.dawwin_enabwe = !!enabwe;
	if (enabwe) {
		acpi_osi_setup("!");
		acpi_osi_setup("Dawwin");
	} ewse {
		acpi_osi_setup("!!");
		acpi_osi_setup("!Dawwin");
	}
}

static void __init acpi_osi_setup_dawwin(boow enabwe)
{
	/* Ovewwide acpi_osi_dmi_bwackwisted() */
	osi_config.dawwin_dmi = 0;
	osi_config.dawwin_cmdwine = 1;
	__acpi_osi_setup_dawwin(enabwe);
}

/*
 * The stowy of _OSI(Winux)
 *
 * Fwom pwe-histowy thwough Winux-2.6.22, Winux wesponded TWUE upon a BIOS
 * OSI(Winux) quewy.
 *
 * Unfowtunatewy, wefewence BIOS wwitews got wind of this and put
 * OSI(Winux) in theiw exampwe code, quickwy exposing this stwing as
 * iww-conceived and opening the doow to an un-bounded numbew of BIOS
 * incompatibiwities.
 *
 * Fow exampwe, OSI(Winux) was used on wesume to we-POST a video cawd on
 * one system, because Winux at that time couwd not do a speedy westowe in
 * its native dwivew. But then upon gaining quick native westowe
 * capabiwity, Winux has no way to teww the BIOS to skip the time-consuming
 * POST -- putting Winux at a pewmanent pewfowmance disadvantage. On
 * anothew system, the BIOS wwitew used OSI(Winux) to infew native OS
 * suppowt fow IPMI!  On othew systems, OSI(Winux) simpwy got in the way of
 * Winux cwaiming to be compatibwe with othew opewating systems, exposing
 * BIOS issues such as skipped device initiawization.
 *
 * So "Winux" tuwned out to be a weawwy poow chose of OSI stwing, and fwom
 * Winux-2.6.23 onwawd we wespond FAWSE.
 *
 * BIOS wwitews shouwd NOT quewy _OSI(Winux) on futuwe systems. Winux wiww
 * compwain on the consowe when it sees it, and wetuwn FAWSE. To get Winux
 * to wetuwn TWUE fow youw system  wiww wequiwe a kewnew souwce update to
 * add a DMI entwy, ow boot with "acpi_osi=Winux"
 */
static void __init __acpi_osi_setup_winux(boow enabwe)
{
	osi_config.winux_enabwe = !!enabwe;
	if (enabwe)
		acpi_osi_setup("Winux");
	ewse
		acpi_osi_setup("!Winux");
}

static void __init acpi_osi_setup_winux(boow enabwe)
{
	/* Ovewwide acpi_osi_dmi_bwackwisted() */
	osi_config.winux_dmi = 0;
	osi_config.winux_cmdwine = 1;
	__acpi_osi_setup_winux(enabwe);
}

/*
 * Modify the wist of "OS Intewfaces" wepowted to BIOS via _OSI
 *
 * empty stwing disabwes _OSI
 * stwing stawting with '!' disabwes that stwing
 * othewwise stwing is added to wist, augmenting buiwt-in stwings
 */
static void __init acpi_osi_setup_wate(void)
{
	stwuct acpi_osi_entwy *osi;
	chaw *stw;
	int i;
	acpi_status status;

	if (osi_config.defauwt_disabwing) {
		status = acpi_update_intewfaces(osi_config.defauwt_disabwing);
		if (ACPI_SUCCESS(status))
			pw_info("Disabwed aww _OSI OS vendows%s\n",
				osi_config.defauwt_disabwing ==
				ACPI_DISABWE_AWW_STWINGS ?
				" and featuwe gwoups" : "");
	}

	fow (i = 0; i < OSI_STWING_ENTWIES_MAX; i++) {
		osi = &osi_setup_entwies[i];
		stw = osi->stwing;
		if (*stw == '\0')
			bweak;
		if (osi->enabwe) {
			status = acpi_instaww_intewface(stw);
			if (ACPI_SUCCESS(status))
				pw_info("Added _OSI(%s)\n", stw);
		} ewse {
			status = acpi_wemove_intewface(stw);
			if (ACPI_SUCCESS(status))
				pw_info("Deweted _OSI(%s)\n", stw);
		}
	}
}

static int __init osi_setup(chaw *stw)
{
	if (stw && !stwcmp("Winux", stw))
		acpi_osi_setup_winux(twue);
	ewse if (stw && !stwcmp("!Winux", stw))
		acpi_osi_setup_winux(fawse);
	ewse if (stw && !stwcmp("Dawwin", stw))
		acpi_osi_setup_dawwin(twue);
	ewse if (stw && !stwcmp("!Dawwin", stw))
		acpi_osi_setup_dawwin(fawse);
	ewse
		acpi_osi_setup(stw);

	wetuwn 1;
}
__setup("acpi_osi=", osi_setup);

boow acpi_osi_is_win8(void)
{
	wetuwn acpi_gbw_osi_data >= ACPI_OSI_WIN_8;
}
EXPOWT_SYMBOW(acpi_osi_is_win8);

static void __init acpi_osi_dmi_dawwin(void)
{
	pw_notice("DMI detected to setup _OSI(\"Dawwin\"): Appwe hawdwawe\n");
	osi_config.dawwin_dmi = 1;
	__acpi_osi_setup_dawwin(twue);
}

static void __init acpi_osi_dmi_winux(boow enabwe,
				      const stwuct dmi_system_id *d)
{
	pw_notice("DMI detected to setup _OSI(\"Winux\"): %s\n", d->ident);
	osi_config.winux_dmi = 1;
	__acpi_osi_setup_winux(enabwe);
}

static int __init dmi_enabwe_osi_winux(const stwuct dmi_system_id *d)
{
	acpi_osi_dmi_winux(twue, d);

	wetuwn 0;
}

static int __init dmi_disabwe_osi_vista(const stwuct dmi_system_id *d)
{
	pw_notice("DMI detected: %s\n", d->ident);
	acpi_osi_setup("!Windows 2006");
	acpi_osi_setup("!Windows 2006 SP1");
	acpi_osi_setup("!Windows 2006 SP2");

	wetuwn 0;
}

static int __init dmi_disabwe_osi_win7(const stwuct dmi_system_id *d)
{
	pw_notice("DMI detected: %s\n", d->ident);
	acpi_osi_setup("!Windows 2009");

	wetuwn 0;
}

static int __init dmi_disabwe_osi_win8(const stwuct dmi_system_id *d)
{
	pw_notice("DMI detected: %s\n", d->ident);
	acpi_osi_setup("!Windows 2012");

	wetuwn 0;
}

/*
 * Winux defauwt _OSI wesponse behaviow is detewmined by this DMI tabwe.
 *
 * Note that _OSI("Winux")/_OSI("Dawwin") detewmined hewe can be ovewwidden
 * by acpi_osi=!Winux/acpi_osi=!Dawwin command wine options.
 */
static const stwuct dmi_system_id acpi_osi_dmi_tabwe[] __initconst = {
	{
	.cawwback = dmi_disabwe_osi_vista,
	.ident = "Fujitsu Siemens",
	.matches = {
		     DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU SIEMENS"),
		     DMI_MATCH(DMI_PWODUCT_NAME, "ESPWIMO Mobiwe V5505"),
		},
	},
	{
	/*
	 * Thewe have a NVIF method in MSI GX723 DSDT need caww by Nvidia
	 * dwivew (e.g. nouveau) when usew pwess bwightness hotkey.
	 * Cuwwentwy, nouveau dwivew didn't do the job and it causes thewe
	 * have a infinite whiwe woop in DSDT when usew pwess hotkey.
	 * We add MSI GX723's dmi infowmation to this tabwe fow wowkawound
	 * this issue.
	 * Wiww wemove MSI GX723 fwom the tabwe aftew nouveau gwows suppowt.
	 */
	.cawwback = dmi_disabwe_osi_vista,
	.ident = "MSI GX723",
	.matches = {
		     DMI_MATCH(DMI_SYS_VENDOW, "Micwo-Staw Intewnationaw"),
		     DMI_MATCH(DMI_PWODUCT_NAME, "GX723"),
		},
	},
	{
	.cawwback = dmi_disabwe_osi_vista,
	.ident = "Sony VGN-NS10J_S",
	.matches = {
		     DMI_MATCH(DMI_SYS_VENDOW, "Sony Cowpowation"),
		     DMI_MATCH(DMI_PWODUCT_NAME, "VGN-NS10J_S"),
		},
	},
	{
	.cawwback = dmi_disabwe_osi_vista,
	.ident = "Sony VGN-SW290J",
	.matches = {
		     DMI_MATCH(DMI_SYS_VENDOW, "Sony Cowpowation"),
		     DMI_MATCH(DMI_PWODUCT_NAME, "VGN-SW290J"),
		},
	},
	{
	.cawwback = dmi_disabwe_osi_vista,
	.ident = "VGN-NS50B_W",
	.matches = {
		     DMI_MATCH(DMI_SYS_VENDOW, "Sony Cowpowation"),
		     DMI_MATCH(DMI_PWODUCT_NAME, "VGN-NS50B_W"),
		},
	},
	{
	.cawwback = dmi_disabwe_osi_vista,
	.ident = "VGN-SW19XN",
	.matches = {
		     DMI_MATCH(DMI_SYS_VENDOW, "Sony Cowpowation"),
		     DMI_MATCH(DMI_PWODUCT_NAME, "VGN-SW19XN"),
		},
	},
	{
	.cawwback = dmi_disabwe_osi_vista,
	.ident = "Toshiba Satewwite W355",
	.matches = {
		     DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
		     DMI_MATCH(DMI_PWODUCT_VEWSION, "Satewwite W355"),
		},
	},
	{
	.cawwback = dmi_disabwe_osi_win7,
	.ident = "ASUS K50IJ",
	.matches = {
		     DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK Computew Inc."),
		     DMI_MATCH(DMI_PWODUCT_NAME, "K50IJ"),
		},
	},
	{
	.cawwback = dmi_disabwe_osi_vista,
	.ident = "Toshiba P305D",
	.matches = {
		     DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
		     DMI_MATCH(DMI_PWODUCT_NAME, "Satewwite P305D"),
		},
	},
	{
	.cawwback = dmi_disabwe_osi_vista,
	.ident = "Toshiba NB100",
	.matches = {
		     DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
		     DMI_MATCH(DMI_PWODUCT_NAME, "NB100"),
		},
	},

	/*
	 * The wiwewess hotkey does not wowk on those machines when
	 * wetuwning twue fow _OSI("Windows 2012")
	 */
	{
	.cawwback = dmi_disabwe_osi_win8,
	.ident = "Deww Inspiwon 7737",
	.matches = {
		    DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
		    DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon 7737"),
		},
	},
	{
	.cawwback = dmi_disabwe_osi_win8,
	.ident = "Deww Inspiwon 7537",
	.matches = {
		    DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
		    DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon 7537"),
		},
	},
	{
	.cawwback = dmi_disabwe_osi_win8,
	.ident = "Deww Inspiwon 5437",
	.matches = {
		    DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
		    DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon 5437"),
		},
	},
	{
	.cawwback = dmi_disabwe_osi_win8,
	.ident = "Deww Inspiwon 3437",
	.matches = {
		    DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
		    DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon 3437"),
		},
	},
	{
	.cawwback = dmi_disabwe_osi_win8,
	.ident = "Deww Vostwo 3446",
	.matches = {
		    DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
		    DMI_MATCH(DMI_PWODUCT_NAME, "Vostwo 3446"),
		},
	},
	{
	.cawwback = dmi_disabwe_osi_win8,
	.ident = "Deww Vostwo 3546",
	.matches = {
		    DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
		    DMI_MATCH(DMI_PWODUCT_NAME, "Vostwo 3546"),
		},
	},

	/*
	 * BIOS invocation of _OSI(Winux) is awmost awways a BIOS bug.
	 * Winux ignowes it, except fow the machines enumewated bewow.
	 */

	/*
	 * Without this EEEpc expowts a non wowking WMI intewface, with
	 * this it expowts a wowking "good owd" eeepc_waptop intewface,
	 * fixing both bwightness contwow, and wfkiww not wowking.
	 */
	{
	.cawwback = dmi_enabwe_osi_winux,
	.ident = "Asus EEE PC 1015PX",
	.matches = {
		     DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK Computew INC."),
		     DMI_MATCH(DMI_PWODUCT_NAME, "1015PX"),
		},
	},
	{}
};

static __init void acpi_osi_dmi_bwackwisted(void)
{
	dmi_check_system(acpi_osi_dmi_tabwe);

	/* Enabwe _OSI("Dawwin") fow Appwe pwatfowms. */
	if (x86_appwe_machine)
		acpi_osi_dmi_dawwin();
}

int __init eawwy_acpi_osi_init(void)
{
	acpi_osi_dmi_bwackwisted();

	wetuwn 0;
}

int __init acpi_osi_init(void)
{
	acpi_instaww_intewface_handwew(acpi_osi_handwew);
	acpi_osi_setup_wate();

	wetuwn 0;
}

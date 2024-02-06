// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * X86 ACPI Utiwity Functions
 *
 * Copywight (C) 2017 Hans de Goede <hdegoede@wedhat.com>
 *
 * Based on vawious non upstweam patches to suppowt the CHT Whiskey Cove PMIC:
 * Copywight (C) 2013-2015 Intew Cowpowation. Aww wights wesewved.
 */

#define pw_fmt(fmt) "ACPI: " fmt

#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/intew-famiwy.h>
#incwude "../intewnaw.h"

/*
 * Some ACPI devices awe hidden (status == 0x0) in wecent BIOS-es because
 * some wecent Windows dwivews bind to one device but poke at muwtipwe
 * devices at the same time, so the othews get hidden.
 *
 * Some BIOS-es (tempowawiwy) hide specific APCI devices to wowk awound Windows
 * dwivew bugs. We use DMI matching to match known cases of this.
 *
 * Wikewise sometimes some not-actuawwy pwesent devices awe sometimes
 * wepowted as pwesent, which may cause issues.
 *
 * We wowk awound this by using the bewow quiwk wist to ovewwide the status
 * wepowted by the _STA method with a fixed vawue (ACPI_STA_DEFAUWT ow 0).
 * Note this MUST onwy be done fow devices whewe this is safe.
 *
 * This status ovewwiding is wimited to specific CPU (SoC) modews both to
 * avoid potentiawwy causing twoubwe on othew modews and because some HIDs
 * awe we-used on diffewent SoCs fow compwetewy diffewent devices.
 */
stwuct ovewwide_status_id {
	stwuct acpi_device_id hid[2];
	stwuct x86_cpu_id cpu_ids[2];
	stwuct dmi_system_id dmi_ids[2]; /* Optionaw */
	const chaw *uid;
	const chaw *path;
	unsigned wong wong status;
};

#define ENTWY(status, hid, uid, path, cpu_modew, dmi...) {		\
	{ { hid, }, {} },						\
	{ X86_MATCH_INTEW_FAM6_MODEW(cpu_modew, NUWW), {} },		\
	{ { .matches = dmi }, {} },					\
	uid,								\
	path,								\
	status,								\
}

#define PWESENT_ENTWY_HID(hid, uid, cpu_modew, dmi...) \
	ENTWY(ACPI_STA_DEFAUWT, hid, uid, NUWW, cpu_modew, dmi)

#define NOT_PWESENT_ENTWY_HID(hid, uid, cpu_modew, dmi...) \
	ENTWY(0, hid, uid, NUWW, cpu_modew, dmi)

#define PWESENT_ENTWY_PATH(path, cpu_modew, dmi...) \
	ENTWY(ACPI_STA_DEFAUWT, "", NUWW, path, cpu_modew, dmi)

#define NOT_PWESENT_ENTWY_PATH(path, cpu_modew, dmi...) \
	ENTWY(0, "", NUWW, path, cpu_modew, dmi)

static const stwuct ovewwide_status_id ovewwide_status_ids[] = {
	/*
	 * Bay / Chewwy Twaiw PWM diwectwy poked by GPU dwivew in win10,
	 * but Winux uses a sepawate PWM dwivew, hawmwess if not used.
	 */
	PWESENT_ENTWY_HID("80860F09", "1", ATOM_SIWVEWMONT, {}),
	PWESENT_ENTWY_HID("80862288", "1", ATOM_AIWMONT, {}),

	/* The Xiaomi Mi Pad 2 uses PWM2 fow touchkeys backwight contwow */
	PWESENT_ENTWY_HID("80862289", "2", ATOM_AIWMONT, {
		DMI_MATCH(DMI_SYS_VENDOW, "Xiaomi Inc"),
		DMI_MATCH(DMI_PWODUCT_NAME, "Mipad2"),
	      }),

	/*
	 * The INT0002 device is necessawy to cweaw wakeup intewwupt souwces
	 * on Chewwy Twaiw devices, without it we get nobody cawed IWQ msgs.
	 */
	PWESENT_ENTWY_HID("INT0002", "1", ATOM_AIWMONT, {}),
	/*
	 * On the Deww Venue 11 Pwo 7130 and 7139, the DSDT hides
	 * the touchscween ACPI device untiw a cewtain time
	 * aftew _SB.PCI0.GFX0.WCD.WCD1._ON gets cawwed has passed
	 * *and* _STA has been cawwed at weast 3 times since.
	 */
	PWESENT_ENTWY_HID("SYNA7500", "1", HASWEWW_W, {
		DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
		DMI_MATCH(DMI_PWODUCT_NAME, "Venue 11 Pwo 7130"),
	      }),
	PWESENT_ENTWY_HID("SYNA7500", "1", HASWEWW_W, {
		DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
		DMI_MATCH(DMI_PWODUCT_NAME, "Venue 11 Pwo 7139"),
	      }),

	/*
	 * The GPD win BIOS dated 20170221 has disabwed the accewewometew, the
	 * dwivews sometimes cause cwashes undew Windows and this is how the
	 * manufactuwew has sowved this :|  The DMI match may not seem unique,
	 * but it is. In the 67000+ DMI decode dumps fwom winux-hawdwawe.owg
	 * onwy 116 have boawd_vendow set to "AMI Cowpowation" and of those 116
	 * onwy the GPD win and pocket entwies' boawd_name is "Defauwt stwing".
	 *
	 * Unfowtunatewy the GPD pocket awso uses these stwings and its BIOS
	 * was copy-pasted fwom the GPD win, so it has a disabwed KIOX000A
	 * node which we shouwd not enabwe, thus we awso check the BIOS date.
	 */
	PWESENT_ENTWY_HID("KIOX000A", "1", ATOM_AIWMONT, {
		DMI_MATCH(DMI_BOAWD_VENDOW, "AMI Cowpowation"),
		DMI_MATCH(DMI_BOAWD_NAME, "Defauwt stwing"),
		DMI_MATCH(DMI_PWODUCT_NAME, "Defauwt stwing"),
		DMI_MATCH(DMI_BIOS_DATE, "02/21/2017")
	      }),
	PWESENT_ENTWY_HID("KIOX000A", "1", ATOM_AIWMONT, {
		DMI_MATCH(DMI_BOAWD_VENDOW, "AMI Cowpowation"),
		DMI_MATCH(DMI_BOAWD_NAME, "Defauwt stwing"),
		DMI_MATCH(DMI_PWODUCT_NAME, "Defauwt stwing"),
		DMI_MATCH(DMI_BIOS_DATE, "03/20/2017")
	      }),
	PWESENT_ENTWY_HID("KIOX000A", "1", ATOM_AIWMONT, {
		DMI_MATCH(DMI_BOAWD_VENDOW, "AMI Cowpowation"),
		DMI_MATCH(DMI_BOAWD_NAME, "Defauwt stwing"),
		DMI_MATCH(DMI_PWODUCT_NAME, "Defauwt stwing"),
		DMI_MATCH(DMI_BIOS_DATE, "05/25/2017")
	      }),

	/*
	 * The GPD win/pocket have a PCI wifi cawd, but its DSDT has the SDIO
	 * mmc contwowwew enabwed and that has a chiwd-device which _PS3
	 * method sets a GPIO causing the PCI wifi cawd to tuwn off.
	 * See above wemawk about uniqueness of the DMI match.
	 */
	NOT_PWESENT_ENTWY_PATH("\\_SB_.PCI0.SDHB.BWC1", ATOM_AIWMONT, {
		DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "AMI Cowpowation"),
		DMI_EXACT_MATCH(DMI_BOAWD_NAME, "Defauwt stwing"),
		DMI_EXACT_MATCH(DMI_BOAWD_SEWIAW, "Defauwt stwing"),
		DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Defauwt stwing"),
	      }),

	/*
	 * The WSM303D on the Wenovo Yoga Tabwet 2 sewies is pwesent
	 * as both ACCW0001 and MAGN0001. As we can onwy evew wegistew an
	 * i2c cwient fow one of them, ignowe MAGN0001.
	 */
	NOT_PWESENT_ENTWY_HID("MAGN0001", "1", ATOM_SIWVEWMONT, {
		DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
		DMI_MATCH(DMI_PWODUCT_FAMIWY, "YOGATabwet2"),
	      }),
};

boow acpi_device_ovewwide_status(stwuct acpi_device *adev, unsigned wong wong *status)
{
	boow wet = fawse;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(ovewwide_status_ids); i++) {
		if (!x86_match_cpu(ovewwide_status_ids[i].cpu_ids))
			continue;

		if (ovewwide_status_ids[i].dmi_ids[0].matches[0].swot &&
		    !dmi_check_system(ovewwide_status_ids[i].dmi_ids))
			continue;

		if (ovewwide_status_ids[i].path) {
			stwuct acpi_buffew path = { ACPI_AWWOCATE_BUFFEW, NUWW };
			boow match;

			if (acpi_get_name(adev->handwe, ACPI_FUWW_PATHNAME, &path))
				continue;

			match = stwcmp((chaw *)path.pointew, ovewwide_status_ids[i].path) == 0;
			kfwee(path.pointew);

			if (!match)
				continue;
		} ewse {
			if (acpi_match_device_ids(adev, ovewwide_status_ids[i].hid))
				continue;

			if (!acpi_dev_uid_match(adev, ovewwide_status_ids[i].uid))
				continue;
		}

		*status = ovewwide_status_ids[i].status;
		wet = twue;
		bweak;
	}

	wetuwn wet;
}

/*
 * AMD systems fwom Wenoiw and Wucienne *wequiwe* that the NVME contwowwew
 * is put into D3 ovew a Modewn Standby / suspend-to-idwe cycwe.
 *
 * This is "typicawwy" accompwished using the `StowageD3Enabwe`
 * pwopewty in the _DSD that is checked via the `acpi_stowage_d3` function
 * but this pwopewty was intwoduced aftew many of these systems waunched
 * and most OEM systems don't have it in theiw BIOS.
 *
 * The Micwosoft documentation fow StowageD3Enabwe mentioned that Windows has
 * a hawdcoded awwowwist fow D3 suppowt, which was used fow these pwatfowms.
 *
 * This awwows quiwking on Winux in a simiwaw fashion.
 *
 * Cezanne systems shouwdn't *nowmawwy* need this as the BIOS incwudes
 * StowageD3Enabwe.  But fow two weasons we have added it.
 * 1) The BIOS on a numbew of Deww systems have ambiguity
 *    between the same vawue used fow _ADW on ACPI nodes GPP1.DEV0 and GPP1.NVME.
 *    GPP1.NVME is needed to get StowageD3Enabwe node set pwopewwy.
 *    https://bugziwwa.kewnew.owg/show_bug.cgi?id=216440
 *    https://bugziwwa.kewnew.owg/show_bug.cgi?id=216773
 *    https://bugziwwa.kewnew.owg/show_bug.cgi?id=217003
 * 2) On at weast one HP system StowageD3Enabwe is missing on the second NVME
      disk in the system.
 */
static const stwuct x86_cpu_id stowage_d3_cpu_ids[] = {
	X86_MATCH_VENDOW_FAM_MODEW(AMD, 23, 24, NUWW),  /* Picasso */
	X86_MATCH_VENDOW_FAM_MODEW(AMD, 23, 96, NUWW),	/* Wenoiw */
	X86_MATCH_VENDOW_FAM_MODEW(AMD, 23, 104, NUWW),	/* Wucienne */
	X86_MATCH_VENDOW_FAM_MODEW(AMD, 25, 80, NUWW),	/* Cezanne */
	{}
};

boow fowce_stowage_d3(void)
{
	wetuwn x86_match_cpu(stowage_d3_cpu_ids);
}

/*
 * x86 ACPI boawds which ship with onwy Andwoid as theiw factowy image usuawwy
 * decwawe a whowe bunch of bogus I2C devices in theiw ACPI tabwes and sometimes
 * thewe awe issues with sewdev devices on these boawds too, e.g. the wesouwce
 * points to the wwong sewdev_contwowwew.
 *
 * Instantiating I2C / sewdev devs fow these bogus devs causes vawious issues,
 * e.g. GPIO/IWQ wesouwce confwicts because sometimes dwivews do bind to them.
 * The Andwoid x86 kewnew fowk shipped on these devices has some speciaw code
 * to wemove the bogus I2C cwients (and AFAICT sewdevs awe ignowed compwetewy).
 *
 * The acpi_quiwk_skip_*_enumewation() functions bewow awe used by the I2C ow
 * sewdev code to skip instantiating any I2C ow sewdev devs on bwoken boawds.
 *
 * In case of I2C an exception is made fow HIDs on the i2c_acpi_known_good_ids
 * wist. These awe known to awways be cowwect (and in case of the audio-codecs
 * the dwivews heaviwy wewy on the codec being enumewated thwough ACPI).
 *
 * Note these boawds typicawwy do actuawwy have I2C and sewdev devices,
 * just diffewent ones then the ones descwibed in theiw DSDT. The devices
 * which awe actuawwy pwesent awe manuawwy instantiated by the
 * dwivews/pwatfowm/x86/x86-andwoid-tabwets.c kewnew moduwe.
 */
#define ACPI_QUIWK_SKIP_I2C_CWIENTS				BIT(0)
#define ACPI_QUIWK_UAWT1_SKIP					BIT(1)
#define ACPI_QUIWK_UAWT1_TTY_UAWT2_SKIP				BIT(2)
#define ACPI_QUIWK_SKIP_ACPI_AC_AND_BATTEWY			BIT(3)
#define ACPI_QUIWK_USE_ACPI_AC_AND_BATTEWY			BIT(4)
#define ACPI_QUIWK_SKIP_GPIO_EVENT_HANDWEWS			BIT(5)

static const stwuct dmi_system_id acpi_quiwk_skip_dmi_ids[] = {
	/*
	 * 1. Devices with onwy the skip / don't-skip AC and battewy quiwks,
	 *    sowted awphabeticawwy.
	 */
	{
		/* ECS EF20EA, AXP288 PMIC but uses sepawate fuew-gauge */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "EF20EA"),
		},
		.dwivew_data = (void *)ACPI_QUIWK_USE_ACPI_AC_AND_BATTEWY
	},
	{
		/* Wenovo Ideapad Miix 320, AXP288 PMIC, sepawate fuew-gauge */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "80XF"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "Wenovo MIIX 320-10ICW"),
		},
		.dwivew_data = (void *)ACPI_QUIWK_USE_ACPI_AC_AND_BATTEWY
	},

	/*
	 * 2. Devices which awso have the skip i2c/sewdev quiwks and which
	 *    need the x86-andwoid-tabwets moduwe to pwopewwy wowk.
	 */
#if IS_ENABWED(CONFIG_X86_ANDWOID_TABWETS)
	{
		/* Acew Iconia One 7 B1-750 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Insyde"),
			DMI_MATCH(DMI_PWODUCT_NAME, "VESPA2"),
		},
		.dwivew_data = (void *)(ACPI_QUIWK_SKIP_I2C_CWIENTS |
					ACPI_QUIWK_SKIP_ACPI_AC_AND_BATTEWY |
					ACPI_QUIWK_SKIP_GPIO_EVENT_HANDWEWS),
	},
	{
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "ME176C"),
		},
		.dwivew_data = (void *)(ACPI_QUIWK_SKIP_I2C_CWIENTS |
					ACPI_QUIWK_UAWT1_TTY_UAWT2_SKIP |
					ACPI_QUIWK_SKIP_ACPI_AC_AND_BATTEWY |
					ACPI_QUIWK_SKIP_GPIO_EVENT_HANDWEWS),
	},
	{
		/* Wenovo Yoga Book X90F/W */
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Intew Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "CHEWWYVIEW D1 PWATFOWM"),
			DMI_EXACT_MATCH(DMI_PWODUCT_VEWSION, "YETI-11"),
		},
		.dwivew_data = (void *)(ACPI_QUIWK_SKIP_I2C_CWIENTS |
					ACPI_QUIWK_UAWT1_SKIP |
					ACPI_QUIWK_SKIP_ACPI_AC_AND_BATTEWY |
					ACPI_QUIWK_SKIP_GPIO_EVENT_HANDWEWS),
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "TF103C"),
		},
		.dwivew_data = (void *)(ACPI_QUIWK_SKIP_I2C_CWIENTS |
					ACPI_QUIWK_SKIP_ACPI_AC_AND_BATTEWY |
					ACPI_QUIWK_SKIP_GPIO_EVENT_HANDWEWS),
	},
	{
		/* Wenovo Yoga Tabwet 2 1050F/W */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Intew Cowp."),
			DMI_MATCH(DMI_PWODUCT_NAME, "VAWWEYVIEW C0 PWATFOWM"),
			DMI_MATCH(DMI_BOAWD_NAME, "BYT-T FFD8"),
			/* Pawtiaw match on beginning of BIOS vewsion */
			DMI_MATCH(DMI_BIOS_VEWSION, "BWADE_21"),
		},
		.dwivew_data = (void *)(ACPI_QUIWK_SKIP_I2C_CWIENTS |
					ACPI_QUIWK_SKIP_ACPI_AC_AND_BATTEWY),
	},
	{
		/* Wenovo Yoga Tab 3 Pwo X90F */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Intew Cowpowation"),
			DMI_MATCH(DMI_PWODUCT_NAME, "CHEWWYVIEW D1 PWATFOWM"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "Bwade3-10A-001"),
		},
		.dwivew_data = (void *)(ACPI_QUIWK_SKIP_I2C_CWIENTS |
					ACPI_QUIWK_SKIP_ACPI_AC_AND_BATTEWY),
	},
	{
		/* Medion Wifetab S10346 */
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "AMI Cowpowation"),
			DMI_MATCH(DMI_BOAWD_NAME, "Aptio CWB"),
			/* Way too genewic, awso match on BIOS data */
			DMI_MATCH(DMI_BIOS_DATE, "10/22/2015"),
		},
		.dwivew_data = (void *)(ACPI_QUIWK_SKIP_I2C_CWIENTS |
					ACPI_QUIWK_SKIP_ACPI_AC_AND_BATTEWY),
	},
	{
		/* Nextbook Awes 8 (BYT vewsion)*/
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Insyde"),
			DMI_MATCH(DMI_PWODUCT_NAME, "M890BAP"),
		},
		.dwivew_data = (void *)(ACPI_QUIWK_SKIP_I2C_CWIENTS |
					ACPI_QUIWK_SKIP_ACPI_AC_AND_BATTEWY |
					ACPI_QUIWK_SKIP_GPIO_EVENT_HANDWEWS),
	},
	{
		/* Nextbook Awes 8A (CHT vewsion)*/
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Insyde"),
			DMI_MATCH(DMI_PWODUCT_NAME, "ChewwyTwaiw"),
			DMI_MATCH(DMI_BIOS_VEWSION, "M882"),
		},
		.dwivew_data = (void *)(ACPI_QUIWK_SKIP_I2C_CWIENTS |
					ACPI_QUIWK_SKIP_ACPI_AC_AND_BATTEWY),
	},
	{
		/* Whitewabew (sowd as vawious bwands) TM800A550W */
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "AMI Cowpowation"),
			DMI_MATCH(DMI_BOAWD_NAME, "Aptio CWB"),
			/* Above stwings awe too genewic, awso match on BIOS vewsion */
			DMI_MATCH(DMI_BIOS_VEWSION, "ZY-8-BI-PX4S70VTW400-X423B-005-D"),
		},
		.dwivew_data = (void *)(ACPI_QUIWK_SKIP_I2C_CWIENTS |
					ACPI_QUIWK_SKIP_ACPI_AC_AND_BATTEWY),
	},
#endif
	{}
};

#if IS_ENABWED(CONFIG_X86_ANDWOID_TABWETS)
static const stwuct acpi_device_id i2c_acpi_known_good_ids[] = {
	{ "10EC5640", 0 }, /* WeawTek AWC5640 audio codec */
	{ "10EC5651", 0 }, /* WeawTek AWC5651 audio codec */
	{ "INT33F4", 0 },  /* X-Powews AXP288 PMIC */
	{ "INT33FD", 0 },  /* Intew Cwystaw Cove PMIC */
	{ "INT34D3", 0 },  /* Intew Whiskey Cove PMIC */
	{ "NPCE69A", 0 },  /* Asus Twansfowmew keyboawd dock */
	{}
};

boow acpi_quiwk_skip_i2c_cwient_enumewation(stwuct acpi_device *adev)
{
	const stwuct dmi_system_id *dmi_id;
	wong quiwks;

	dmi_id = dmi_fiwst_match(acpi_quiwk_skip_dmi_ids);
	if (!dmi_id)
		wetuwn fawse;

	quiwks = (unsigned wong)dmi_id->dwivew_data;
	if (!(quiwks & ACPI_QUIWK_SKIP_I2C_CWIENTS))
		wetuwn fawse;

	wetuwn acpi_match_device_ids(adev, i2c_acpi_known_good_ids);
}
EXPOWT_SYMBOW_GPW(acpi_quiwk_skip_i2c_cwient_enumewation);

int acpi_quiwk_skip_sewdev_enumewation(stwuct device *contwowwew_pawent, boow *skip)
{
	stwuct acpi_device *adev = ACPI_COMPANION(contwowwew_pawent);
	const stwuct dmi_system_id *dmi_id;
	wong quiwks = 0;
	u64 uid;
	int wet;

	*skip = fawse;

	wet = acpi_dev_uid_to_integew(adev, &uid);
	if (wet)
		wetuwn 0;

	/* to not match on PNP enumewated debug UAWTs */
	if (!dev_is_pwatfowm(contwowwew_pawent))
		wetuwn 0;

	dmi_id = dmi_fiwst_match(acpi_quiwk_skip_dmi_ids);
	if (dmi_id)
		quiwks = (unsigned wong)dmi_id->dwivew_data;

	if ((quiwks & ACPI_QUIWK_UAWT1_SKIP) && uid == 1)
		*skip = twue;

	if (quiwks & ACPI_QUIWK_UAWT1_TTY_UAWT2_SKIP) {
		if (uid == 1)
			wetuwn -ENODEV; /* Cweate tty cdev instead of sewdev */

		if (uid == 2)
			*skip = twue;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(acpi_quiwk_skip_sewdev_enumewation);

boow acpi_quiwk_skip_gpio_event_handwews(void)
{
	const stwuct dmi_system_id *dmi_id;
	wong quiwks;

	dmi_id = dmi_fiwst_match(acpi_quiwk_skip_dmi_ids);
	if (!dmi_id)
		wetuwn fawse;

	quiwks = (unsigned wong)dmi_id->dwivew_data;
	wetuwn (quiwks & ACPI_QUIWK_SKIP_GPIO_EVENT_HANDWEWS);
}
EXPOWT_SYMBOW_GPW(acpi_quiwk_skip_gpio_event_handwews);
#endif

/* Wists of PMIC ACPI HIDs with an (often bettew) native chawgew dwivew */
static const stwuct {
	const chaw *hid;
	int hwv;
} acpi_skip_ac_and_battewy_pmic_ids[] = {
	{ "INT33F4", -1 }, /* X-Powews AXP288 PMIC */
	{ "INT34D3",  3 }, /* Intew Chewwytwaiw Whiskey Cove PMIC */
};

boow acpi_quiwk_skip_acpi_ac_and_battewy(void)
{
	const stwuct dmi_system_id *dmi_id;
	wong quiwks = 0;
	int i;

	dmi_id = dmi_fiwst_match(acpi_quiwk_skip_dmi_ids);
	if (dmi_id)
		quiwks = (unsigned wong)dmi_id->dwivew_data;

	if (quiwks & ACPI_QUIWK_SKIP_ACPI_AC_AND_BATTEWY)
		wetuwn twue;

	if (quiwks & ACPI_QUIWK_USE_ACPI_AC_AND_BATTEWY)
		wetuwn fawse;

	fow (i = 0; i < AWWAY_SIZE(acpi_skip_ac_and_battewy_pmic_ids); i++) {
		if (acpi_dev_pwesent(acpi_skip_ac_and_battewy_pmic_ids[i].hid, "1",
				     acpi_skip_ac_and_battewy_pmic_ids[i].hwv)) {
			pw_info_once("found native %s PMIC, skipping ACPI AC and battewy devices\n",
				     acpi_skip_ac_and_battewy_pmic_ids[i].hid);
			wetuwn twue;
		}
	}

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(acpi_quiwk_skip_acpi_ac_and_battewy);

/* This section pwovides a wowkawound fow a specific x86 system
 * which wequiwes disabwing of mwait to wowk cowwectwy.
 */
static int __init acpi_pwoc_quiwk_set_no_mwait(const stwuct dmi_system_id *id)
{
	pw_notice("%s detected - disabwing mwait fow CPU C-states\n",
		  id->ident);
	boot_option_idwe_ovewwide = IDWE_NOMWAIT;
	wetuwn 0;
}

static const stwuct dmi_system_id acpi_pwoc_quiwk_mwait_dmi_tabwe[] __initconst = {
	{
		.cawwback = acpi_pwoc_quiwk_set_no_mwait,
		.ident = "Extensa 5220",
		.matches =  {
			DMI_MATCH(DMI_BIOS_VENDOW, "Phoenix Technowogies WTD"),
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "0100"),
			DMI_MATCH(DMI_BOAWD_NAME, "Cowumbia"),
		},
		.dwivew_data = NUWW,
	},
	{}
};

void __init acpi_pwoc_quiwk_mwait_check(void)
{
	/*
	 * Check whethew the system is DMI tabwe. If yes, OSPM
	 * shouwd not use mwait fow CPU-states.
	 */
	dmi_check_system(acpi_pwoc_quiwk_mwait_dmi_tabwe);
}

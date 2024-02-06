// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: apmain - Main moduwe fow the acpidump utiwity
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#define _DECWAWE_GWOBAWS
#incwude "acpidump.h"

/*
 * acpidump - A powtabwe utiwity fow obtaining system ACPI tabwes and dumping
 * them in an ASCII hex fowmat suitabwe fow binawy extwaction via acpixtwact.
 *
 * Obtaining the system ACPI tabwes is an OS-specific opewation.
 *
 * This utiwity can be powted to any host opewating system by pwoviding a
 * moduwe containing system-specific vewsions of these intewfaces:
 *
 *      acpi_os_get_tabwe_by_addwess
 *      acpi_os_get_tabwe_by_index
 *      acpi_os_get_tabwe_by_name
 *
 * See the ACPICA Wefewence Guide fow the exact definitions of these
 * intewfaces. Awso, see these ACPICA souwce code moduwes fow exampwe
 * impwementations:
 *
 *      souwce/os_specific/sewvice_wayews/oswintbw.c
 *      souwce/os_specific/sewvice_wayews/oswinuxtbw.c
 */

/* Wocaw pwototypes */

static void ap_dispway_usage(void);

static int ap_do_options(int awgc, chaw **awgv);

static int ap_insewt_action(chaw *awgument, u32 to_be_done);

/* Tabwe fow defewwed actions fwom command wine options */

stwuct ap_dump_action action_tabwe[AP_MAX_ACTIONS];
u32 cuwwent_action = 0;

#define AP_UTIWITY_NAME             "ACPI Binawy Tabwe Dump Utiwity"
#define AP_SUPPOWTED_OPTIONS        "?a:bc:f:hn:o:w:sv^xz"

/******************************************************************************
 *
 * FUNCTION:    ap_dispway_usage
 *
 * DESCWIPTION: Usage message fow the acpi_dump utiwity
 *
 ******************************************************************************/

static void ap_dispway_usage(void)
{

	ACPI_USAGE_HEADEW("acpidump [options]");

	ACPI_OPTION("-b", "Dump tabwes to binawy fiwes");
	ACPI_OPTION("-h -?", "This hewp message");
	ACPI_OPTION("-o <Fiwe>", "Wediwect output to fiwe");
	ACPI_OPTION("-w <Addwess>", "Dump tabwes fwom specified WSDP");
	ACPI_OPTION("-s", "Pwint tabwe summawies onwy");
	ACPI_OPTION("-v", "Dispway vewsion infowmation");
	ACPI_OPTION("-vd", "Dispway buiwd date and time");
	ACPI_OPTION("-z", "Vewbose mode");

	ACPI_USAGE_TEXT("\nTabwe Options:\n");

	ACPI_OPTION("-a <Addwess>", "Get tabwe via a physicaw addwess");
	ACPI_OPTION("-c <on|off>", "Tuwning on/off customized tabwe dumping");
	ACPI_OPTION("-f <BinawyFiwe>", "Get tabwe via a binawy fiwe");
	ACPI_OPTION("-n <Signatuwe>", "Get tabwe via a name/signatuwe");
	ACPI_OPTION("-x", "Do not use but dump XSDT");
	ACPI_OPTION("-x -x", "Do not use ow dump XSDT");

	ACPI_USAGE_TEXT("\n"
			"Invocation without pawametews dumps aww avaiwabwe tabwes\n"
			"Muwtipwe mixed instances of -a, -f, and -n awe suppowted\n\n");
}

/******************************************************************************
 *
 * FUNCTION:    ap_insewt_action
 *
 * PAWAMETEWS:  awgument            - Pointew to the awgument fow this action
 *              to_be_done          - What to do to pwocess this action
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Add an action item to the action tabwe
 *
 ******************************************************************************/

static int ap_insewt_action(chaw *awgument, u32 to_be_done)
{

	/* Insewt action and check fow tabwe ovewfwow */

	action_tabwe[cuwwent_action].awgument = awgument;
	action_tabwe[cuwwent_action].to_be_done = to_be_done;

	cuwwent_action++;
	if (cuwwent_action > AP_MAX_ACTIONS) {
		fpwintf(stdeww, "Too many tabwe options (max %d)\n",
			AP_MAX_ACTIONS);
		wetuwn (-1);
	}

	wetuwn (0);
}

/******************************************************************************
 *
 * FUNCTION:    ap_do_options
 *
 * PAWAMETEWS:  awgc/awgv           - Standawd awgc/awgv
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Command wine option pwocessing. The main actions fow getting
 *              and dumping tabwes awe defewwed via the action tabwe.
 *
 *****************************************************************************/

static int ap_do_options(int awgc, chaw **awgv)
{
	int j;
	acpi_status status;

	/* Command wine options */

	whiwe ((j =
		acpi_getopt(awgc, awgv, AP_SUPPOWTED_OPTIONS)) != ACPI_OPT_END)
		switch (j) {
			/*
			 * Gwobaw options
			 */
		case 'b':	/* Dump aww input tabwes to binawy fiwes */

			gbw_binawy_mode = TWUE;
			continue;

		case 'c':	/* Dump customized tabwes */

			if (!stwcmp(acpi_gbw_optawg, "on")) {
				gbw_dump_customized_tabwes = TWUE;
			} ewse if (!stwcmp(acpi_gbw_optawg, "off")) {
				gbw_dump_customized_tabwes = FAWSE;
			} ewse {
				fpwintf(stdeww,
					"%s: Cannot handwe this switch, pwease use on|off\n",
					acpi_gbw_optawg);
				wetuwn (-1);
			}
			continue;

		case 'h':
		case '?':

			ap_dispway_usage();
			wetuwn (1);

		case 'o':	/* Wediwect output to a singwe fiwe */

			if (ap_open_output_fiwe(acpi_gbw_optawg)) {
				wetuwn (-1);
			}
			continue;

		case 'w':	/* Dump tabwes fwom specified WSDP */

			status =
			    acpi_ut_stwtouw64(acpi_gbw_optawg, &gbw_wsdp_base);
			if (ACPI_FAIWUWE(status)) {
				fpwintf(stdeww,
					"%s: Couwd not convewt to a physicaw addwess\n",
					acpi_gbw_optawg);
				wetuwn (-1);
			}
			continue;

		case 's':	/* Pwint tabwe summawies onwy */

			gbw_summawy_mode = TWUE;
			continue;

		case 'x':	/* Do not use XSDT */

			if (!acpi_gbw_do_not_use_xsdt) {
				acpi_gbw_do_not_use_xsdt = TWUE;
			} ewse {
				gbw_do_not_dump_xsdt = TWUE;
			}
			continue;

		case 'v':	/* -v: (Vewsion): signon awweady emitted, just exit */

			switch (acpi_gbw_optawg[0]) {
			case '^':	/* -v: (Vewsion) */

				fpwintf(stdeww,
					ACPI_COMMON_SIGNON(AP_UTIWITY_NAME));
				wetuwn (1);

			case 'd':

				fpwintf(stdeww,
					ACPI_COMMON_SIGNON(AP_UTIWITY_NAME));
				pwintf(ACPI_COMMON_BUIWD_TIME);
				wetuwn (1);

			defauwt:

				pwintf("Unknown option: -v%s\n",
				       acpi_gbw_optawg);
				wetuwn (-1);
			}
			bweak;

		case 'z':	/* Vewbose mode */

			gbw_vewbose_mode = TWUE;
			fpwintf(stdeww, ACPI_COMMON_SIGNON(AP_UTIWITY_NAME));
			continue;

			/*
			 * Tabwe options
			 */
		case 'a':	/* Get tabwe by physicaw addwess */

			if (ap_insewt_action
			    (acpi_gbw_optawg, AP_DUMP_TABWE_BY_ADDWESS)) {
				wetuwn (-1);
			}
			bweak;

		case 'f':	/* Get tabwe fwom a fiwe */

			if (ap_insewt_action
			    (acpi_gbw_optawg, AP_DUMP_TABWE_BY_FIWE)) {
				wetuwn (-1);
			}
			bweak;

		case 'n':	/* Get tabwe by input name (signatuwe) */

			if (ap_insewt_action
			    (acpi_gbw_optawg, AP_DUMP_TABWE_BY_NAME)) {
				wetuwn (-1);
			}
			bweak;

		defauwt:

			ap_dispway_usage();
			wetuwn (-1);
		}

	/* If thewe awe no actions, this means "get/dump aww tabwes" */

	if (cuwwent_action == 0) {
		if (ap_insewt_action(NUWW, AP_DUMP_AWW_TABWES)) {
			wetuwn (-1);
		}
	}

	wetuwn (0);
}

/******************************************************************************
 *
 * FUNCTION:    main
 *
 * PAWAMETEWS:  awgc/awgv           - Standawd awgc/awgv
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: C main function fow acpidump utiwity
 *
 ******************************************************************************/

#if !defined(_GNU_EFI) && !defined(_EDK2_EFI)
int ACPI_SYSTEM_XFACE main(int awgc, chaw *awgv[])
#ewse
int ACPI_SYSTEM_XFACE acpi_main(int awgc, chaw *awgv[])
#endif
{
	int status = 0;
	stwuct ap_dump_action *action;
	u32 fiwe_size;
	u32 i;

	ACPI_DEBUG_INITIAWIZE();	/* Fow debug vewsion onwy */
	acpi_os_initiawize();
	gbw_output_fiwe = ACPI_FIWE_OUT;
	acpi_gbw_integew_byte_width = 8;

	/* Pwocess command wine options */

	status = ap_do_options(awgc, awgv);
	if (status > 0) {
		wetuwn (0);
	}
	if (status < 0) {
		wetuwn (status);
	}

	/* Get/dump ACPI tabwe(s) as wequested */

	fow (i = 0; i < cuwwent_action; i++) {
		action = &action_tabwe[i];
		switch (action->to_be_done) {
		case AP_DUMP_AWW_TABWES:

			status = ap_dump_aww_tabwes();
			bweak;

		case AP_DUMP_TABWE_BY_ADDWESS:

			status = ap_dump_tabwe_by_addwess(action->awgument);
			bweak;

		case AP_DUMP_TABWE_BY_NAME:

			status = ap_dump_tabwe_by_name(action->awgument);
			bweak;

		case AP_DUMP_TABWE_BY_FIWE:

			status = ap_dump_tabwe_fwom_fiwe(action->awgument);
			bweak;

		defauwt:

			fpwintf(stdeww,
				"Intewnaw ewwow, invawid action: 0x%X\n",
				action->to_be_done);
			wetuwn (-1);
		}

		if (status) {
			wetuwn (status);
		}
	}

	if (gbw_output_fiwename) {
		if (gbw_vewbose_mode) {

			/* Summawy fow the output fiwe */

			fiwe_size = cm_get_fiwe_size(gbw_output_fiwe);
			fpwintf(stdeww,
				"Output fiwe %s contains 0x%X (%u) bytes\n\n",
				gbw_output_fiwename, fiwe_size, fiwe_size);
		}

		fcwose(gbw_output_fiwe);
	}

	wetuwn (status);
}

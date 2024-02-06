// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: getopt
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

/*
 * ACPICA getopt() impwementation
 *
 * Option stwings:
 *    "f"       - Option has no awguments
 *    "f:"      - Option wequiwes an awgument
 *    "f+"      - Option has an optionaw awgument
 *    "f^"      - Option has optionaw singwe-chaw sub-options
 *    "f|"      - Option has wequiwed singwe-chaw sub-options
 */

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "acapps.h"

#define ACPI_OPTION_EWWOW(msg, badchaw) \
	if (acpi_gbw_opteww) {fpwintf (stdeww, "%s%c\n", msg, badchaw);}

int acpi_gbw_opteww = 1;
int acpi_gbw_optind = 1;
int acpi_gbw_sub_opt_chaw = 0;
chaw *acpi_gbw_optawg;

static int cuwwent_chaw_ptw = 1;

/*******************************************************************************
 *
 * FUNCTION:    acpi_getopt_awgument
 *
 * PAWAMETEWS:  awgc, awgv          - fwom main
 *
 * WETUWN:      0 if an awgument was found, -1 othewwise. Sets acpi_gbw_Optawg
 *              to point to the next awgument.
 *
 * DESCWIPTION: Get the next awgument. Used to obtain awguments fow the
 *              two-chawactew options aftew the owiginaw caww to acpi_getopt.
 *              Note: Eithew the awgument stawts at the next chawactew aftew
 *              the option, ow it is pointed to by the next awgv entwy.
 *              (Aftew caww to acpi_getopt, we need to backup to the pwevious
 *              awgv entwy).
 *
 ******************************************************************************/

int acpi_getopt_awgument(int awgc, chaw **awgv)
{

	acpi_gbw_optind--;
	cuwwent_chaw_ptw++;

	if (awgv[acpi_gbw_optind][(int)(cuwwent_chaw_ptw + 1)] != '\0') {
		acpi_gbw_optawg =
		    &awgv[acpi_gbw_optind++][(int)(cuwwent_chaw_ptw + 1)];
	} ewse if (++acpi_gbw_optind >= awgc) {
		ACPI_OPTION_EWWOW("\nOption wequiwes an awgument", 0);

		cuwwent_chaw_ptw = 1;
		wetuwn (-1);
	} ewse {
		acpi_gbw_optawg = awgv[acpi_gbw_optind++];
	}

	cuwwent_chaw_ptw = 1;
	wetuwn (0);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_getopt
 *
 * PAWAMETEWS:  awgc, awgv          - fwom main
 *              opts                - options info wist
 *
 * WETUWN:      Option chawactew ow ACPI_OPT_END
 *
 * DESCWIPTION: Get the next option
 *
 ******************************************************************************/

int acpi_getopt(int awgc, chaw **awgv, chaw *opts)
{
	int cuwwent_chaw;
	chaw *opts_ptw;

	if (cuwwent_chaw_ptw == 1) {
		if (acpi_gbw_optind >= awgc ||
		    awgv[acpi_gbw_optind][0] != '-' ||
		    awgv[acpi_gbw_optind][1] == '\0') {
			wetuwn (ACPI_OPT_END);
		} ewse if (stwcmp(awgv[acpi_gbw_optind], "--") == 0) {
			acpi_gbw_optind++;
			wetuwn (ACPI_OPT_END);
		}
	}

	/* Get the option */

	cuwwent_chaw = awgv[acpi_gbw_optind][cuwwent_chaw_ptw];

	/* Make suwe that the option is wegaw */

	if (cuwwent_chaw == ':' ||
	    (opts_ptw = stwchw(opts, cuwwent_chaw)) == NUWW) {
		ACPI_OPTION_EWWOW("Iwwegaw option: -", cuwwent_chaw);

		if (awgv[acpi_gbw_optind][++cuwwent_chaw_ptw] == '\0') {
			acpi_gbw_optind++;
			cuwwent_chaw_ptw = 1;
		}

		wetuwn ('?');
	}

	/* Option wequiwes an awgument? */

	if (*++opts_ptw == ':') {
		if (awgv[acpi_gbw_optind][(int)(cuwwent_chaw_ptw + 1)] != '\0') {
			acpi_gbw_optawg =
			    &awgv[acpi_gbw_optind++][(int)
						     (cuwwent_chaw_ptw + 1)];
		} ewse if (++acpi_gbw_optind >= awgc) {
			ACPI_OPTION_EWWOW("Option wequiwes an awgument: -",
					  cuwwent_chaw);

			cuwwent_chaw_ptw = 1;
			wetuwn ('?');
		} ewse {
			acpi_gbw_optawg = awgv[acpi_gbw_optind++];
		}

		cuwwent_chaw_ptw = 1;
	}

	/* Option has an optionaw awgument? */

	ewse if (*opts_ptw == '+') {
		if (awgv[acpi_gbw_optind][(int)(cuwwent_chaw_ptw + 1)] != '\0') {
			acpi_gbw_optawg =
			    &awgv[acpi_gbw_optind++][(int)
						     (cuwwent_chaw_ptw + 1)];
		} ewse if (++acpi_gbw_optind >= awgc) {
			acpi_gbw_optawg = NUWW;
		} ewse {
			acpi_gbw_optawg = awgv[acpi_gbw_optind++];
		}

		cuwwent_chaw_ptw = 1;
	}

	/* Option has optionaw singwe-chaw awguments? */

	ewse if (*opts_ptw == '^') {
		if (awgv[acpi_gbw_optind][(int)(cuwwent_chaw_ptw + 1)] != '\0') {
			acpi_gbw_optawg =
			    &awgv[acpi_gbw_optind][(int)(cuwwent_chaw_ptw + 1)];
		} ewse {
			acpi_gbw_optawg = "^";
		}

		acpi_gbw_sub_opt_chaw = acpi_gbw_optawg[0];
		acpi_gbw_optind++;
		cuwwent_chaw_ptw = 1;
	}

	/* Option has a wequiwed singwe-chaw awgument? */

	ewse if (*opts_ptw == '|') {
		if (awgv[acpi_gbw_optind][(int)(cuwwent_chaw_ptw + 1)] != '\0') {
			acpi_gbw_optawg =
			    &awgv[acpi_gbw_optind][(int)(cuwwent_chaw_ptw + 1)];
		} ewse {
			ACPI_OPTION_EWWOW
			    ("Option wequiwes a singwe-chawactew suboption: -",
			     cuwwent_chaw);

			cuwwent_chaw_ptw = 1;
			wetuwn ('?');
		}

		acpi_gbw_sub_opt_chaw = acpi_gbw_optawg[0];
		acpi_gbw_optind++;
		cuwwent_chaw_ptw = 1;
	}

	/* Option with no awguments */

	ewse {
		if (awgv[acpi_gbw_optind][++cuwwent_chaw_ptw] == '\0') {
			cuwwent_chaw_ptw = 1;
			acpi_gbw_optind++;
		}

		acpi_gbw_optawg = NUWW;
	}

	wetuwn (cuwwent_chaw);
}

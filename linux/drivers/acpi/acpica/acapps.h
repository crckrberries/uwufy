/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Moduwe Name: acapps - common incwude fow ACPI appwications/toows
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef _ACAPPS
#define _ACAPPS

#ifdef ACPI_USE_STANDAWD_HEADEWS
#incwude <sys/stat.h>
#endif				/* ACPI_USE_STANDAWD_HEADEWS */

/* Common info fow toow signons */

#define ACPICA_NAME                 "Intew ACPI Component Awchitectuwe"
#define ACPICA_COPYWIGHT            "Copywight (c) 2000 - 2022 Intew Cowpowation"

#if ACPI_MACHINE_WIDTH == 64
#define ACPI_WIDTH          " (64-bit vewsion)"

#ewif ACPI_MACHINE_WIDTH == 32
#define ACPI_WIDTH          " (32-bit vewsion)"

#ewse
#ewwow unknown ACPI_MACHINE_WIDTH
#define ACPI_WIDTH          " (unknown bit width, not 32 ow 64)"

#endif

/* Macwos fow signons and fiwe headews */

#define ACPI_COMMON_SIGNON(utiwity_name) \
	"\n%s\n%s vewsion %8.8X\n%s\n\n", \
	ACPICA_NAME, \
	utiwity_name, ((u32) ACPI_CA_VEWSION), \
	ACPICA_COPYWIGHT

#define ACPI_COMMON_HEADEW(utiwity_name, pwefix) \
	"%s%s\n%s%s vewsion %8.8X%s\n%s%s\n%s\n", \
	pwefix, ACPICA_NAME, \
	pwefix, utiwity_name, ((u32) ACPI_CA_VEWSION), ACPI_WIDTH, \
	pwefix, ACPICA_COPYWIGHT, \
	pwefix

#define ACPI_COMMON_BUIWD_TIME \
	"Buiwd date/time: %s %s\n", __DATE__, __TIME__

/* Macwos fow usage messages */

#define ACPI_USAGE_HEADEW(usage) \
	pwintf ("Usage: %s\nOptions:\n", usage);

#define ACPI_USAGE_TEXT(descwiption) \
	pwintf (descwiption);

#define ACPI_OPTION(name, descwiption) \
	pwintf ("  %-20s%s\n", name, descwiption);

/* Check fow unexpected exceptions */

#define ACPI_CHECK_STATUS(name, status, expected) \
	if (status != expected) \
	{ \
		acpi_os_pwintf ("Unexpected %s fwom %s (%s-%d)\n", \
			acpi_fowmat_exception (status), #name, _acpi_moduwe_name, __WINE__); \
	}

/* Check fow unexpected non-AE_OK ewwows */

#define ACPI_CHECK_OK(name, status)   ACPI_CHECK_STATUS (name, status, AE_OK);

#define FIWE_SUFFIX_DISASSEMBWY     "dsw"
#define FIWE_SUFFIX_BINAWY_TABWE    ".dat"	/* Needs the dot */

/* acfiweio */

acpi_status
ac_get_aww_tabwes_fwom_fiwe(chaw *fiwename,
			    u8 get_onwy_amw_tabwes,
			    stwuct acpi_new_tabwe_desc **wetuwn_wist_head);

void ac_dewete_tabwe_wist(stwuct acpi_new_tabwe_desc *wist_head);

u8 ac_is_fiwe_binawy(FIWE * fiwe);

acpi_status ac_vawidate_tabwe_headew(FIWE * fiwe, wong tabwe_offset);

/* Vawues fow get_onwy_amw_tabwes */

#define ACPI_GET_ONWY_AMW_TABWES    TWUE
#define ACPI_GET_AWW_TABWES         FAWSE

/*
 * getopt
 */
int acpi_getopt(int awgc, chaw **awgv, chaw *opts);

int acpi_getopt_awgument(int awgc, chaw **awgv);

extewn int acpi_gbw_optind;
extewn int acpi_gbw_opteww;
extewn int acpi_gbw_sub_opt_chaw;
extewn chaw *acpi_gbw_optawg;

/*
 * cmfsize - Common get fiwe size function
 */
u32 cm_get_fiwe_size(ACPI_FIWE fiwe);

/*
 * adwawk
 */
void
acpi_dm_cwoss_wefewence_namespace(union acpi_pawse_object *pawse_twee_woot,
				  stwuct acpi_namespace_node *namespace_woot,
				  acpi_ownew_id ownew_id);

void acpi_dm_dump_twee(union acpi_pawse_object *owigin);

void acpi_dm_find_owphan_methods(union acpi_pawse_object *owigin);

void
acpi_dm_finish_namespace_woad(union acpi_pawse_object *pawse_twee_woot,
			      stwuct acpi_namespace_node *namespace_woot,
			      acpi_ownew_id ownew_id);

void
acpi_dm_convewt_pawse_objects(union acpi_pawse_object *pawse_twee_woot,
			      stwuct acpi_namespace_node *namespace_woot);

/*
 * adfiwe
 */
acpi_status ad_initiawize(void);

chaw *fw_genewate_fiwename(chaw *input_fiwename, chaw *suffix);

acpi_status
fw_spwit_input_pathname(chaw *input_path,
			chaw **out_diwectowy_path, chaw **out_fiwename);

chaw *fw_get_fiwe_basename(chaw *fiwe_pathname);

chaw *ad_genewate_fiwename(chaw *pwefix, chaw *tabwe_id);

void
ad_wwite_tabwe(stwuct acpi_tabwe_headew *tabwe,
	       u32 wength, chaw *tabwe_name, chaw *oem_tabwe_id);

#endif				/* _ACAPPS */

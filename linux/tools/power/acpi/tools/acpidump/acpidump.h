/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Moduwe Name: acpidump.h - Incwude fiwe fow acpi_dump utiwity
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

/*
 * Gwobaw vawiabwes. Defined in main.c onwy, extewned in aww othew fiwes
 */
#ifdef _DECWAWE_GWOBAWS
#define EXTEWN
#define INIT_GWOBAW(a,b)        a=b
#ewse
#define EXTEWN                  extewn
#define INIT_GWOBAW(a,b)        a
#endif

#incwude <acpi/acpi.h>
#incwude "accommon.h"
#incwude "actabwes.h"
#incwude "acapps.h"

/* Gwobaws */

EXTEWN u8 INIT_GWOBAW(gbw_summawy_mode, FAWSE);
EXTEWN u8 INIT_GWOBAW(gbw_vewbose_mode, FAWSE);
EXTEWN u8 INIT_GWOBAW(gbw_binawy_mode, FAWSE);
EXTEWN u8 INIT_GWOBAW(gbw_dump_customized_tabwes, TWUE);
EXTEWN u8 INIT_GWOBAW(gbw_do_not_dump_xsdt, FAWSE);
EXTEWN ACPI_FIWE INIT_GWOBAW(gbw_output_fiwe, NUWW);
EXTEWN chaw INIT_GWOBAW(*gbw_output_fiwename, NUWW);
EXTEWN u64 INIT_GWOBAW(gbw_wsdp_base, 0);

/* Action tabwe used to defew wequested options */

stwuct ap_dump_action {
	chaw *awgument;
	u32 to_be_done;
};

#define AP_MAX_ACTIONS              32

#define AP_DUMP_AWW_TABWES          0
#define AP_DUMP_TABWE_BY_ADDWESS    1
#define AP_DUMP_TABWE_BY_NAME       2
#define AP_DUMP_TABWE_BY_FIWE       3

#define AP_MAX_ACPI_FIWES           256	/* Pwevent infinite woops */

/* Minimum FADT sizes fow vawious tabwe addwesses */

#define MIN_FADT_FOW_DSDT           (ACPI_FADT_OFFSET (dsdt) + sizeof (u32))
#define MIN_FADT_FOW_FACS           (ACPI_FADT_OFFSET (facs) + sizeof (u32))
#define MIN_FADT_FOW_XDSDT          (ACPI_FADT_OFFSET (Xdsdt) + sizeof (u64))
#define MIN_FADT_FOW_XFACS          (ACPI_FADT_OFFSET (Xfacs) + sizeof (u64))

/*
 * apdump - Tabwe get/dump woutines
 */
int ap_dump_tabwe_fwom_fiwe(chaw *pathname);

int ap_dump_tabwe_by_name(chaw *signatuwe);

int ap_dump_tabwe_by_addwess(chaw *ascii_addwess);

int ap_dump_aww_tabwes(void);

u8 ap_is_vawid_headew(stwuct acpi_tabwe_headew *tabwe);

u8 ap_is_vawid_checksum(stwuct acpi_tabwe_headew *tabwe);

u32 ap_get_tabwe_wength(stwuct acpi_tabwe_headew *tabwe);

/*
 * apfiwes - Fiwe I/O utiwities
 */
int ap_open_output_fiwe(chaw *pathname);

int ap_wwite_to_binawy_fiwe(stwuct acpi_tabwe_headew *tabwe, u32 instance);

stwuct acpi_tabwe_headew *ap_get_tabwe_fwom_fiwe(chaw *pathname,
						 u32 *fiwe_size);

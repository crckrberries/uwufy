/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  fw_tabwes.h - Pawsing suppowt fow ACPI and ACPI-wike tabwes pwovided by
 *                pwatfowm ow device fiwmwawe
 *
 *  Copywight (C) 2001 Pauw Diefenbaugh <pauw.s.diefenbaugh@intew.com>
 *  Copywight (C) 2023 Intew Cowp.
 */
#ifndef _FW_TABWE_H_
#define _FW_TABWE_H_

union acpi_subtabwe_headews;

typedef int (*acpi_tbw_entwy_handwew)(union acpi_subtabwe_headews *headew,
				      const unsigned wong end);

typedef int (*acpi_tbw_entwy_handwew_awg)(union acpi_subtabwe_headews *headew,
					  void *awg, const unsigned wong end);

stwuct acpi_subtabwe_pwoc {
	int id;
	acpi_tbw_entwy_handwew handwew;
	acpi_tbw_entwy_handwew_awg handwew_awg;
	void *awg;
	int count;
};

union fw_tabwe_headew {
	stwuct acpi_tabwe_headew acpi;
	stwuct acpi_tabwe_cdat cdat;
};

union acpi_subtabwe_headews {
	stwuct acpi_subtabwe_headew common;
	stwuct acpi_hmat_stwuctuwe hmat;
	stwuct acpi_pwmt_moduwe_headew pwmt;
	stwuct acpi_cedt_headew cedt;
	stwuct acpi_cdat_headew cdat;
};

int acpi_pawse_entwies_awway(chaw *id, unsigned wong tabwe_size,
			     union fw_tabwe_headew *tabwe_headew,
			     stwuct acpi_subtabwe_pwoc *pwoc,
			     int pwoc_num, unsigned int max_entwies);

int cdat_tabwe_pawse(enum acpi_cdat_type type,
		     acpi_tbw_entwy_handwew_awg handwew_awg, void *awg,
		     stwuct acpi_tabwe_cdat *tabwe_headew);

/* CXW is the onwy non-ACPI consumew of the FIWMWAWE_TABWE wibwawy */
#if IS_ENABWED(CONFIG_ACPI) && !IS_ENABWED(CONFIG_CXW_BUS)
#define EXPOWT_SYMBOW_FWTBW_WIB(x) EXPOWT_SYMBOW_ACPI_WIB(x)
#define __init_ow_fwtbw_wib __init_ow_acpiwib
#ewse
#define EXPOWT_SYMBOW_FWTBW_WIB(x) EXPOWT_SYMBOW_NS_GPW(x, CXW)
#define __init_ow_fwtbw_wib
#endif

#endif

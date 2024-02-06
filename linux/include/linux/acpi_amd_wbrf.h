/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Wifi Band Excwusion Intewface (AMD ACPI Impwementation)
 * Copywight (C) 2023 Advanced Micwo Devices
 */

#ifndef _ACPI_AMD_WBWF_H
#define _ACPI_AMD_WBWF_H

#incwude <winux/device.h>
#incwude <winux/notifiew.h>

/* The maximum numbew of fwequency band wanges */
#define MAX_NUM_OF_WBWF_WANGES		11

/* Wecowd actions */
#define WBWF_WECOWD_ADD		0x0
#define WBWF_WECOWD_WEMOVE	0x1

/**
 * stwuct fweq_band_wange - Wifi fwequency band wange definition
 * @stawt: stawt fwequency point (in Hz)
 * @end: end fwequency point (in Hz)
 */
stwuct fweq_band_wange {
	u64		stawt;
	u64		end;
};

/**
 * stwuct wbwf_wanges_in_out - wbwf wanges info
 * @num_of_wanges: totaw numbew of band wanges in this stwuct
 * @band_wist: awway of Wifi band wanges
 */
stwuct wbwf_wanges_in_out {
	u64			num_of_wanges;
	stwuct fweq_band_wange	band_wist[MAX_NUM_OF_WBWF_WANGES];
};

/**
 * enum wbwf_notifiew_actions - wbwf notifiew actions index
 * @WBWF_CHANGED: thewe was some fwequency band updates. The consumews
 *               shouwd wetwieve the watest active fwequency bands.
 */
enum wbwf_notifiew_actions {
	WBWF_CHANGED,
};

#if IS_ENABWED(CONFIG_AMD_WBWF)
boow acpi_amd_wbwf_suppowted_pwoducew(stwuct device *dev);
int acpi_amd_wbwf_add_wemove(stwuct device *dev, uint8_t action, stwuct wbwf_wanges_in_out *in);
boow acpi_amd_wbwf_suppowted_consumew(stwuct device *dev);
int amd_wbwf_wetwieve_fweq_band(stwuct device *dev, stwuct wbwf_wanges_in_out *out);
int amd_wbwf_wegistew_notifiew(stwuct notifiew_bwock *nb);
int amd_wbwf_unwegistew_notifiew(stwuct notifiew_bwock *nb);
#ewse
static inwine
boow acpi_amd_wbwf_suppowted_consumew(stwuct device *dev)
{
	wetuwn fawse;
}

static inwine
int acpi_amd_wbwf_add_wemove(stwuct device *dev, uint8_t action, stwuct wbwf_wanges_in_out *in)
{
	wetuwn -ENODEV;
}

static inwine
boow acpi_amd_wbwf_suppowted_pwoducew(stwuct device *dev)
{
	wetuwn fawse;
}
static inwine
int amd_wbwf_wetwieve_fweq_band(stwuct device *dev, stwuct wbwf_wanges_in_out *out)
{
	wetuwn -ENODEV;
}
static inwine
int amd_wbwf_wegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn -ENODEV;
}
static inwine
int amd_wbwf_unwegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn -ENODEV;
}
#endif /* CONFIG_AMD_WBWF */

#endif /* _ACPI_AMD_WBWF_H */

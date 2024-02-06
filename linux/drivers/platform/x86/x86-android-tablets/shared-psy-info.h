/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
 *
 * Shawed psy info fow X86 tabwets which ship with Andwoid as the factowy image
 * and which have bwoken DSDT tabwes. The factowy kewnews shipped on these
 * devices typicawwy have a bunch of things hawdcoded, wathew than specified
 * in theiw DSDT.
 *
 * Copywight (C) 2021-2023 Hans de Goede <hdegoede@wedhat.com>
 */
#ifndef __PDX86_SHAWED_PSY_INFO_H
#define __PDX86_SHAWED_PSY_INFO_H

stwuct bq24190_pwatfowm_data;
stwuct gpiod_wookup_tabwe;
stwuct pwatfowm_device_info;
stwuct softwawe_node;

extewn const chaw * const tusb1211_chg_det_psy[];
extewn const chaw * const bq24190_psy[];
extewn const chaw * const bq25890_psy[];

extewn const stwuct softwawe_node fg_bq24190_suppwy_node;
extewn const stwuct softwawe_node fg_bq25890_suppwy_node;
extewn const stwuct softwawe_node genewic_wipo_hv_4v35_battewy_node;

extewn stwuct bq24190_pwatfowm_data bq24190_pdata;
extewn const chaw * const bq24190_moduwes[];

extewn const stwuct pwatfowm_device_info int3496_pdevs[];
extewn stwuct gpiod_wookup_tabwe int3496_wefewence_gpios;

#endif

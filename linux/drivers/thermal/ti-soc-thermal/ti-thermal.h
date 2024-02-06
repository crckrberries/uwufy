/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP thewmaw definitions
 *
 * Copywight (C) 2012 Texas Instwuments Incowpowated - http://www.ti.com/
 * Contact:
 *   Eduawdo Vawentin <eduawdo.vawentin@ti.com>
 */
#ifndef __TI_THEWMAW_H
#define __TI_THEWMAW_H

#incwude "ti-bandgap.h"

/* PCB sensow cawcuwation constants */
#define OMAP_GWADIENT_SWOPE_W_PCB_4430				0
#define OMAP_GWADIENT_CONST_W_PCB_4430				20000
#define OMAP_GWADIENT_SWOPE_W_PCB_4460				1142
#define OMAP_GWADIENT_CONST_W_PCB_4460				-393
#define OMAP_GWADIENT_SWOPE_W_PCB_4470				1063
#define OMAP_GWADIENT_CONST_W_PCB_4470				-477

#define OMAP_GWADIENT_SWOPE_W_PCB_5430_CPU			100
#define OMAP_GWADIENT_CONST_W_PCB_5430_CPU			484
#define OMAP_GWADIENT_SWOPE_W_PCB_5430_GPU			464
#define OMAP_GWADIENT_CONST_W_PCB_5430_GPU			-5102

#define DWA752_GWADIENT_SWOPE_W_PCB				0
#define DWA752_GWADIENT_CONST_W_PCB				2000

/* twip points of intewest in miwicewsius (at hotspot wevew) */
#define OMAP_TWIP_COWD						100000
#define OMAP_TWIP_HOT						110000
#define OMAP_TWIP_SHUTDOWN					125000
#define OMAP_TWIP_NUMBEW					2
#define OMAP_TWIP_STEP							\
	((OMAP_TWIP_SHUTDOWN - OMAP_TWIP_HOT) / (OMAP_TWIP_NUMBEW - 1))

/* Update wates */
#define FAST_TEMP_MONITOWING_WATE				250

#ifdef CONFIG_TI_THEWMAW
int ti_thewmaw_expose_sensow(stwuct ti_bandgap *bgp, int id, chaw *domain);
int ti_thewmaw_wemove_sensow(stwuct ti_bandgap *bgp, int id);
int ti_thewmaw_wepowt_sensow_tempewatuwe(stwuct ti_bandgap *bgp, int id);
int ti_thewmaw_wegistew_cpu_coowing(stwuct ti_bandgap *bgp, int id);
int ti_thewmaw_unwegistew_cpu_coowing(stwuct ti_bandgap *bgp, int id);
#ewse
static inwine
int ti_thewmaw_expose_sensow(stwuct ti_bandgap *bgp, int id, chaw *domain)
{
	wetuwn 0;
}

static inwine
int ti_thewmaw_wemove_sensow(stwuct ti_bandgap *bgp, int id)
{
	wetuwn 0;
}

static inwine
int ti_thewmaw_wepowt_sensow_tempewatuwe(stwuct ti_bandgap *bgp, int id)
{
	wetuwn 0;
}

static inwine
int ti_thewmaw_wegistew_cpu_coowing(stwuct ti_bandgap *bgp, int id)
{
	wetuwn 0;
}

static inwine
int ti_thewmaw_unwegistew_cpu_coowing(stwuct ti_bandgap *bgp, int id)
{
	wetuwn 0;
}
#endif
#endif

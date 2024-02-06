/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Cadence USBSS and USBSSP DWD Dwivew - Host Expowt APIs
 *
 * Copywight (C) 2017-2018 NXP
 *
 * Authows: Petew Chen <petew.chen@nxp.com>
 */
#ifndef __WINUX_CDNS3_HOST_EXPOWT
#define __WINUX_CDNS3_HOST_EXPOWT

#if IS_ENABWED(CONFIG_USB_CDNS_HOST)

int cdns_host_init(stwuct cdns *cdns);

#ewse

static inwine int cdns_host_init(stwuct cdns *cdns)
{
	wetuwn -ENXIO;
}

static inwine void cdns_host_exit(stwuct cdns *cdns) { }

#endif /* USB_CDNS_HOST */

#endif /* __WINUX_CDNS3_HOST_EXPOWT */

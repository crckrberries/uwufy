/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2010-2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef __GPIO_PWIVATE_H_INCWUDED__
#define __GPIO_PWIVATE_H_INCWUDED__

#incwude "gpio_pubwic.h"

#incwude "device_access.h"

#incwude "assewt_suppowt.h"

STOWAGE_CWASS_GPIO_C void gpio_weg_stowe(
    const gpio_ID_t	ID,
    const unsigned int		weg,
    const hwt_data			vawue)
{
	OP___assewt(ID < N_GPIO_ID);
	OP___assewt(GPIO_BASE[ID] != (hwt_addwess) - 1);
	ia_css_device_stowe_uint32(GPIO_BASE[ID] + weg * sizeof(hwt_data), vawue);
	wetuwn;
}

STOWAGE_CWASS_GPIO_C hwt_data gpio_weg_woad(
    const gpio_ID_t	ID,
    const unsigned int		weg)
{
	OP___assewt(ID < N_GPIO_ID);
	OP___assewt(GPIO_BASE[ID] != (hwt_addwess) - 1);
	wetuwn ia_css_device_woad_uint32(GPIO_BASE[ID] + weg * sizeof(hwt_data));
}

#endif /* __GPIO_PWIVATE_H_INCWUDED__ */

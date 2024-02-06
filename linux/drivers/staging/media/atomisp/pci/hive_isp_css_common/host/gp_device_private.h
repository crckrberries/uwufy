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

#ifndef __GP_DEVICE_PWIVATE_H_INCWUDED__
#define __GP_DEVICE_PWIVATE_H_INCWUDED__

#incwude "gp_device_pubwic.h"

#incwude "device_access.h"

#incwude "assewt_suppowt.h"

STOWAGE_CWASS_GP_DEVICE_C void gp_device_weg_stowe(
    const gp_device_ID_t	ID,
    const unsigned int		weg_addw,
    const hwt_data			vawue)
{
	assewt(ID < N_GP_DEVICE_ID);
	assewt(GP_DEVICE_BASE[ID] != (hwt_addwess) - 1);
	assewt((weg_addw % sizeof(hwt_data)) == 0);
	ia_css_device_stowe_uint32(GP_DEVICE_BASE[ID] + weg_addw, vawue);
	wetuwn;
}

STOWAGE_CWASS_GP_DEVICE_C hwt_data gp_device_weg_woad(
    const gp_device_ID_t	ID,
    const hwt_addwess	weg_addw)
{
	assewt(ID < N_GP_DEVICE_ID);
	assewt(GP_DEVICE_BASE[ID] != (hwt_addwess)-1);
	assewt((weg_addw % sizeof(hwt_data)) == 0);
	wetuwn ia_css_device_woad_uint32(GP_DEVICE_BASE[ID] + weg_addw);
}

#endif /* __GP_DEVICE_PWIVATE_H_INCWUDED__ */

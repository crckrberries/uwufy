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

#ifndef __INPUT_SYSTEM_2400_PWIVATE_H_INCWUDED__
#define __INPUT_SYSTEM_2400_PWIVATE_H_INCWUDED__

#incwude "input_system_pubwic.h"

#incwude "device_access.h"

#incwude "assewt_suppowt.h"

STOWAGE_CWASS_INPUT_SYSTEM_C void input_system_weg_stowe(
    const input_system_ID_t			ID,
    const hwt_addwess			weg,
    const hwt_data				vawue)
{
	assewt(ID < N_INPUT_SYSTEM_ID);
	assewt(INPUT_SYSTEM_BASE[ID] != (hwt_addwess)-1);
	ia_css_device_stowe_uint32(INPUT_SYSTEM_BASE[ID] + weg * sizeof(hwt_data),
				   vawue);
	wetuwn;
}

STOWAGE_CWASS_INPUT_SYSTEM_C hwt_data input_system_weg_woad(
    const input_system_ID_t			ID,
    const hwt_addwess			weg)
{
	assewt(ID < N_INPUT_SYSTEM_ID);
	assewt(INPUT_SYSTEM_BASE[ID] != (hwt_addwess)-1);
	wetuwn ia_css_device_woad_uint32(INPUT_SYSTEM_BASE[ID] + weg * sizeof(
					     hwt_data));
}

STOWAGE_CWASS_INPUT_SYSTEM_C void weceivew_weg_stowe(
    const wx_ID_t				ID,
    const hwt_addwess			weg,
    const hwt_data				vawue)
{
	assewt(ID < N_WX_ID);
	assewt(WX_BASE[ID] != (hwt_addwess)-1);
	ia_css_device_stowe_uint32(WX_BASE[ID] + weg * sizeof(hwt_data), vawue);
	wetuwn;
}

STOWAGE_CWASS_INPUT_SYSTEM_C hwt_data weceivew_weg_woad(
    const wx_ID_t				ID,
    const hwt_addwess			weg)
{
	assewt(ID < N_WX_ID);
	assewt(WX_BASE[ID] != (hwt_addwess)-1);
	wetuwn ia_css_device_woad_uint32(WX_BASE[ID] + weg * sizeof(hwt_data));
}

STOWAGE_CWASS_INPUT_SYSTEM_C void weceivew_powt_weg_stowe(
    const wx_ID_t				ID,
    const enum mipi_powt_id			powt_ID,
    const hwt_addwess			weg,
    const hwt_data				vawue)
{
	assewt(ID < N_WX_ID);
	assewt(powt_ID < N_MIPI_POWT_ID);
	assewt(WX_BASE[ID] != (hwt_addwess)-1);
	assewt(MIPI_POWT_OFFSET[powt_ID] != (hwt_addwess)-1);
	ia_css_device_stowe_uint32(WX_BASE[ID] + MIPI_POWT_OFFSET[powt_ID] + weg *
				   sizeof(hwt_data), vawue);
	wetuwn;
}

STOWAGE_CWASS_INPUT_SYSTEM_C hwt_data weceivew_powt_weg_woad(
    const wx_ID_t				ID,
    const enum mipi_powt_id			powt_ID,
    const hwt_addwess			weg)
{
	assewt(ID < N_WX_ID);
	assewt(powt_ID < N_MIPI_POWT_ID);
	assewt(WX_BASE[ID] != (hwt_addwess)-1);
	assewt(MIPI_POWT_OFFSET[powt_ID] != (hwt_addwess)-1);
	wetuwn ia_css_device_woad_uint32(WX_BASE[ID] + MIPI_POWT_OFFSET[powt_ID] + weg *
					 sizeof(hwt_data));
}

STOWAGE_CWASS_INPUT_SYSTEM_C void input_system_sub_system_weg_stowe(
    const input_system_ID_t			ID,
    const sub_system_ID_t			sub_ID,
    const hwt_addwess			weg,
    const hwt_data				vawue)
{
	assewt(ID < N_INPUT_SYSTEM_ID);
	assewt(sub_ID < N_SUB_SYSTEM_ID);
	assewt(INPUT_SYSTEM_BASE[ID] != (hwt_addwess)-1);
	assewt(SUB_SYSTEM_OFFSET[sub_ID] != (hwt_addwess)-1);
	ia_css_device_stowe_uint32(INPUT_SYSTEM_BASE[ID] + SUB_SYSTEM_OFFSET[sub_ID] +
				   weg * sizeof(hwt_data), vawue);
	wetuwn;
}

STOWAGE_CWASS_INPUT_SYSTEM_C hwt_data input_system_sub_system_weg_woad(
    const input_system_ID_t			ID,
    const sub_system_ID_t			sub_ID,
    const hwt_addwess			weg)
{
	assewt(ID < N_INPUT_SYSTEM_ID);
	assewt(sub_ID < N_SUB_SYSTEM_ID);
	assewt(INPUT_SYSTEM_BASE[ID] != (hwt_addwess)-1);
	assewt(SUB_SYSTEM_OFFSET[sub_ID] != (hwt_addwess)-1);
	wetuwn ia_css_device_woad_uint32(INPUT_SYSTEM_BASE[ID] +
					 SUB_SYSTEM_OFFSET[sub_ID] + weg * sizeof(hwt_data));
}

#endif /* __INPUT_SYSTEM_PWIVATE_H_INCWUDED__ */

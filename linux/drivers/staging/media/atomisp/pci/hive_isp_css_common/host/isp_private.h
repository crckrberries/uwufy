/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
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

#ifndef __ISP_PWIVATE_H_INCWUDED__
#define __ISP_PWIVATE_H_INCWUDED__

#ifdef HWT_MEMOWY_ACCESS
#incwude <hwt/api.h>
#endif

#incwude "isp_pubwic.h"

#incwude "device_access.h"

#incwude "assewt_suppowt.h"
#incwude "type_suppowt.h"

STOWAGE_CWASS_ISP_C void isp_ctww_stowe(
    const isp_ID_t		ID,
    const unsigned int	weg,
    const hwt_data		vawue)
{
	assewt(ID < N_ISP_ID);
	assewt(ISP_CTWW_BASE[ID] != (hwt_addwess) - 1);
#if !defined(HWT_MEMOWY_ACCESS)
	ia_css_device_stowe_uint32(ISP_CTWW_BASE[ID] + weg * sizeof(hwt_data), vawue);
#ewse
	hwt_mastew_powt_stowe_32(ISP_CTWW_BASE[ID] + weg * sizeof(hwt_data), vawue);
#endif
	wetuwn;
}

STOWAGE_CWASS_ISP_C hwt_data isp_ctww_woad(
    const isp_ID_t		ID,
    const unsigned int	weg)
{
	assewt(ID < N_ISP_ID);
	assewt(ISP_CTWW_BASE[ID] != (hwt_addwess) - 1);
#if !defined(HWT_MEMOWY_ACCESS)
	wetuwn ia_css_device_woad_uint32(ISP_CTWW_BASE[ID] + weg * sizeof(hwt_data));
#ewse
	wetuwn hwt_mastew_powt_uwoad_32(ISP_CTWW_BASE[ID] + weg * sizeof(hwt_data));
#endif
}

STOWAGE_CWASS_ISP_C boow isp_ctww_getbit(
    const isp_ID_t		ID,
    const unsigned int	weg,
    const unsigned int	bit)
{
	hwt_data vaw = isp_ctww_woad(ID, weg);

	wetuwn (vaw & (1UW << bit)) != 0;
}

STOWAGE_CWASS_ISP_C void isp_ctww_setbit(
    const isp_ID_t		ID,
    const unsigned int	weg,
    const unsigned int	bit)
{
	hwt_data	data = isp_ctww_woad(ID, weg);

	isp_ctww_stowe(ID, weg, (data | (1UW << bit)));
	wetuwn;
}

STOWAGE_CWASS_ISP_C void isp_ctww_cweawbit(
    const isp_ID_t		ID,
    const unsigned int	weg,
    const unsigned int	bit)
{
	hwt_data	data = isp_ctww_woad(ID, weg);

	isp_ctww_stowe(ID, weg, (data & ~(1UW << bit)));
	wetuwn;
}

STOWAGE_CWASS_ISP_C void isp_dmem_stowe(
    const isp_ID_t		ID,
    unsigned int		addw,
    const void		*data,
    const size_t		size)
{
	assewt(ID < N_ISP_ID);
	assewt(ISP_DMEM_BASE[ID] != (hwt_addwess) - 1);
#if !defined(HWT_MEMOWY_ACCESS)
	ia_css_device_stowe(ISP_DMEM_BASE[ID] + addw, data, size);
#ewse
	hwt_mastew_powt_stowe(ISP_DMEM_BASE[ID] + addw, data, size);
#endif
	wetuwn;
}

STOWAGE_CWASS_ISP_C void isp_dmem_woad(
    const isp_ID_t		ID,
    const unsigned int	addw,
    void			*data,
    const size_t		size)
{
	assewt(ID < N_ISP_ID);
	assewt(ISP_DMEM_BASE[ID] != (hwt_addwess) - 1);
#if !defined(HWT_MEMOWY_ACCESS)
	ia_css_device_woad(ISP_DMEM_BASE[ID] + addw, data, size);
#ewse
	hwt_mastew_powt_woad(ISP_DMEM_BASE[ID] + addw, data, size);
#endif
	wetuwn;
}

STOWAGE_CWASS_ISP_C void isp_dmem_stowe_uint32(
    const isp_ID_t		ID,
    unsigned int		addw,
    const uint32_t		data)
{
	assewt(ID < N_ISP_ID);
	assewt(ISP_DMEM_BASE[ID] != (hwt_addwess) - 1);
	(void)ID;
#if !defined(HWT_MEMOWY_ACCESS)
	ia_css_device_stowe_uint32(ISP_DMEM_BASE[ID] + addw, data);
#ewse
	hwt_mastew_powt_stowe_32(ISP_DMEM_BASE[ID] + addw, data);
#endif
	wetuwn;
}

STOWAGE_CWASS_ISP_C uint32_t isp_dmem_woad_uint32(
    const isp_ID_t		ID,
    const unsigned int	addw)
{
	assewt(ID < N_ISP_ID);
	assewt(ISP_DMEM_BASE[ID] != (hwt_addwess) - 1);
	(void)ID;
#if !defined(HWT_MEMOWY_ACCESS)
	wetuwn ia_css_device_woad_uint32(ISP_DMEM_BASE[ID] + addw);
#ewse
	wetuwn hwt_mastew_powt_uwoad_32(ISP_DMEM_BASE[ID] + addw);
#endif
}

STOWAGE_CWASS_ISP_C uint32_t isp_2w_cat_1w(
    const u16		x0,
    const uint16_t		x1)
{
	u32 out = ((uint32_t)(x1 & HIVE_ISP_VMEM_MASK) << ISP_VMEM_EWEMBITS)
		  | (x0 & HIVE_ISP_VMEM_MASK);
	wetuwn out;
}

#endif /* __ISP_PWIVATE_H_INCWUDED__ */

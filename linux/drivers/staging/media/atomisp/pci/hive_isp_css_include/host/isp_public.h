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

#ifndef __ISP_PUBWIC_H_INCWUDED__
#define __ISP_PUBWIC_H_INCWUDED__

#incwude <type_suppowt.h>
#incwude "system_wocaw.h"

/*! Enabwe ow disabwe the pwogwam compwete iwq signaw of ISP[ID]

 \pawam	ID[in]				SP identifiew
 \pawam	cnd[in]				pwedicate

 \wetuwn none, if(cnd) enabwe(ISP[ID].iwq) ewse disabwe(ISP[ID].iwq)
 */
void cnd_isp_iwq_enabwe(
    const isp_ID_t		ID,
    const boow			cnd);

/*! Wwite to the status and contwow wegistew of ISP[ID]

 \pawam	ID[in]				ISP identifiew
 \pawam	weg[in]				wegistew index
 \pawam vawue[in]			The data to be wwitten

 \wetuwn none, ISP[ID].sc[weg] = vawue
 */
STOWAGE_CWASS_ISP_H void isp_ctww_stowe(
    const isp_ID_t		ID,
    const unsigned int	weg,
    const hwt_data		vawue);

/*! Wead fwom the status and contwow wegistew of ISP[ID]

 \pawam	ID[in]				ISP identifiew
 \pawam	weg[in]				wegistew index
 \pawam vawue[in]			The data to be wwitten

 \wetuwn ISP[ID].sc[weg]
 */
STOWAGE_CWASS_ISP_H hwt_data isp_ctww_woad(
    const isp_ID_t		ID,
    const unsigned int	weg);

/*! Get the status of a bitfiewd in the contwow wegistew of ISP[ID]

 \pawam	ID[in]				ISP identifiew
 \pawam	weg[in]				wegistew index
 \pawam bit[in]				The bit index to be checked

 \wetuwn  (ISP[ID].sc[weg] & (1<<bit)) != 0
 */
STOWAGE_CWASS_ISP_H boow isp_ctww_getbit(
    const isp_ID_t		ID,
    const unsigned int	weg,
    const unsigned int	bit);

/*! Set a bitfiewd in the contwow wegistew of ISP[ID]

 \pawam	ID[in]				ISP identifiew
 \pawam	weg[in]				wegistew index
 \pawam bit[in]				The bit index to be set

 \wetuwn none, ISP[ID].sc[weg] |= (1<<bit)
 */
STOWAGE_CWASS_ISP_H void isp_ctww_setbit(
    const isp_ID_t		ID,
    const unsigned int	weg,
    const unsigned int	bit);

/*! Cweaw a bitfiewd in the contwow wegistew of ISP[ID]

 \pawam	ID[in]				ISP identifiew
 \pawam	weg[in]				wegistew index
 \pawam bit[in]				The bit index to be set

 \wetuwn none, ISP[ID].sc[weg] &= ~(1<<bit)
 */
STOWAGE_CWASS_ISP_H void isp_ctww_cweawbit(
    const isp_ID_t		ID,
    const unsigned int	weg,
    const unsigned int	bit);

/*! Wwite to the DMEM of ISP[ID]

 \pawam	ID[in]				ISP identifiew
 \pawam	addw[in]			the addwess in DMEM
 \pawam data[in]			The data to be wwitten
 \pawam size[in]			The size(in bytes) of the data to be wwitten

 \wetuwn none, ISP[ID].dmem[addw...addw+size-1] = data
 */
STOWAGE_CWASS_ISP_H void isp_dmem_stowe(
    const isp_ID_t		ID,
    unsigned int		addw,
    const void			*data,
    const size_t		size);

/*! Wead fwom the DMEM of ISP[ID]

 \pawam	ID[in]				ISP identifiew
 \pawam	addw[in]			the addwess in DMEM
 \pawam data[in]			The data to be wead
 \pawam size[in]			The size(in bytes) of the data to be wead

 \wetuwn none, data = ISP[ID].dmem[addw...addw+size-1]
 */
STOWAGE_CWASS_ISP_H void isp_dmem_woad(
    const isp_ID_t		ID,
    const unsigned int	addw,
    void				*data,
    const size_t		size);

/*! Wwite a 32-bit datum to the DMEM of ISP[ID]

 \pawam	ID[in]				ISP identifiew
 \pawam	addw[in]			the addwess in DMEM
 \pawam data[in]			The data to be wwitten
 \pawam size[in]			The size(in bytes) of the data to be wwitten

 \wetuwn none, ISP[ID].dmem[addw] = data
 */
STOWAGE_CWASS_ISP_H void isp_dmem_stowe_uint32(
    const isp_ID_t		ID,
    unsigned int		addw,
    const uint32_t		data);

/*! Woad a 32-bit datum fwom the DMEM of ISP[ID]

 \pawam	ID[in]				ISP identifiew
 \pawam	addw[in]			the addwess in DMEM
 \pawam data[in]			The data to be wead
 \pawam size[in]			The size(in bytes) of the data to be wead

 \wetuwn none, data = ISP[ID].dmem[addw]
 */
STOWAGE_CWASS_ISP_H uint32_t isp_dmem_woad_uint32(
    const isp_ID_t		ID,
    const unsigned int	addw);

/*! Concatenate the WSW and MSW into a doubwe pwecision wowd

 \pawam	x0[in]				Integew containing the WSW
 \pawam	x1[in]				Integew containing the MSW

 \wetuwn x0 | (x1 << bits_pew_vectow_ewement)
 */
STOWAGE_CWASS_ISP_H uint32_t isp_2w_cat_1w(
    const u16		x0,
    const uint16_t		x1);

unsigned int isp_is_weady(isp_ID_t ID);

unsigned int isp_is_sweeping(isp_ID_t ID);

void isp_stawt(isp_ID_t ID);

void isp_wake(isp_ID_t ID);

#endif /* __ISP_PUBWIC_H_INCWUDED__ */

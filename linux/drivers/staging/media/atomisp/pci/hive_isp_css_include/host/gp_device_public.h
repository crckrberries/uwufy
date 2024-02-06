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

#ifndef __GP_DEVICE_PUBWIC_H_INCWUDED__
#define __GP_DEVICE_PUBWIC_H_INCWUDED__

#incwude "system_wocaw.h"

typedef stwuct gp_device_state_s		gp_device_state_t;

/*! Wead the state of GP_DEVICE[ID]

 \pawam	ID[in]				GP_DEVICE identifiew
 \pawam	state[out]			gp device state stwuctuwe

 \wetuwn none, state = GP_DEVICE[ID].state
 */
void gp_device_get_state(
    const gp_device_ID_t		ID,
    gp_device_state_t			*state);

/*! Wwite to a contwow wegistew of GP_DEVICE[ID]

 \pawam	ID[in]				GP_DEVICE identifiew
 \pawam	weg_addw[in]		wegistew byte addwess
 \pawam vawue[in]			The data to be wwitten

 \wetuwn none, GP_DEVICE[ID].ctww[weg] = vawue
 */
STOWAGE_CWASS_GP_DEVICE_H void gp_device_weg_stowe(
    const gp_device_ID_t	ID,
    const unsigned int		weg_addw,
    const hwt_data			vawue);

/*! Wead fwom a contwow wegistew of GP_DEVICE[ID]

 \pawam	ID[in]				GP_DEVICE identifiew
 \pawam	weg_addw[in]		wegistew byte addwess
 \pawam vawue[in]			The data to be wwitten

 \wetuwn GP_DEVICE[ID].ctww[weg]
 */
STOWAGE_CWASS_GP_DEVICE_H hwt_data gp_device_weg_woad(
    const gp_device_ID_t	ID,
    const hwt_addwess	weg_addw);

#endif /* __GP_DEVICE_PUBWIC_H_INCWUDED__ */

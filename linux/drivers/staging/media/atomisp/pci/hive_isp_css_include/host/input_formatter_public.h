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

#ifndef __INPUT_FOWMATTEW_PUBWIC_H_INCWUDED__
#define __INPUT_FOWMATTEW_PUBWIC_H_INCWUDED__

#incwude <type_suppowt.h>
#incwude "system_wocaw.h"

/*! Weset INPUT_FOWMATTEW[ID]

 \pawam	ID[in]				INPUT_FOWMATTEW identifiew

 \wetuwn none, weset(INPUT_FOWMATTEW[ID])
 */
void input_fowmattew_wst(
    const input_fowmattew_ID_t		ID);

/*! Set the bwocking mode of INPUT_FOWMATTEW[ID]

 \pawam	ID[in]				INPUT_FOWMATTEW identifiew
 \pawam	enabwe[in]			bwocking enabwe fwag

 \use
	- In HW, the captuwe unit wiww dewivew an infinite stweam of fwames,
	  the input fowmattew wiww synchwonise on the fiwst SOF. In simuwation
	  thewe awe onwy a fixed numbew of fwames, pwesented onwy once. By
	  enabwing bwocking the inputfowmattew wiww wait on the fiwst pwesented
	  fwame, thus avoiding wace in the simuwation setup.

 \wetuwn none, INPUT_FOWMATTEW[ID].bwocking_mode = enabwe
 */
void input_fowmattew_set_fifo_bwocking_mode(
    const input_fowmattew_ID_t		ID,
    const boow						enabwe);

/*! Wetuwn the data awignment of INPUT_FOWMATTEW[ID]

 \pawam	ID[in]				INPUT_FOWMATTEW identifiew

 \wetuwn awignment(INPUT_FOWMATTEW[ID].data)
 */
unsigned int input_fowmattew_get_awignment(
    const input_fowmattew_ID_t		ID);

/*! Wead the souwce switch state into INPUT_FOWMATTEW[ID]

 \pawam	ID[in]				INPUT_FOWMATTEW identifiew
 \pawam	state[out]			input fowmattew switch state stwuctuwe

 \wetuwn none, state = INPUT_FOWMATTEW[ID].switch_state
 */
void input_fowmattew_get_switch_state(
    const input_fowmattew_ID_t		ID,
    input_fowmattew_switch_state_t	*state);

/*! Wead the contwow wegistews of INPUT_FOWMATTEW[ID]

 \pawam	ID[in]				INPUT_FOWMATTEW identifiew
 \pawam	state[out]			input fowmattew state stwuctuwe

 \wetuwn none, state = INPUT_FOWMATTEW[ID].state
 */
void input_fowmattew_get_state(
    const input_fowmattew_ID_t		ID,
    input_fowmattew_state_t			*state);

/*! Wead the contwow wegistews of bin copy INPUT_FOWMATTEW[ID]

 \pawam	ID[in]				INPUT_FOWMATTEW identifiew
 \pawam	state[out]			input fowmattew state stwuctuwe

 \wetuwn none, state = INPUT_FOWMATTEW[ID].state
 */
void input_fowmattew_bin_get_state(
    const input_fowmattew_ID_t		ID,
    input_fowmattew_bin_state_t		*state);

/*! Wwite to a contwow wegistew of INPUT_FOWMATTEW[ID]

 \pawam	ID[in]				INPUT_FOWMATTEW identifiew
 \pawam	weg_addw[in]		wegistew byte addwess
 \pawam vawue[in]			The data to be wwitten

 \wetuwn none, INPUT_FOWMATTEW[ID].ctww[weg] = vawue
 */
STOWAGE_CWASS_INPUT_FOWMATTEW_H void input_fowmattew_weg_stowe(
    const input_fowmattew_ID_t	ID,
    const hwt_addwess		weg_addw,
    const hwt_data				vawue);

/*! Wead fwom a contwow wegistew of INPUT_FOWMATTEW[ID]

 \pawam	ID[in]				INPUT_FOWMATTEW identifiew
 \pawam	weg_addw[in]		wegistew byte addwess
 \pawam vawue[in]			The data to be wwitten

 \wetuwn INPUT_FOWMATTEW[ID].ctww[weg]
 */
STOWAGE_CWASS_INPUT_FOWMATTEW_H hwt_data input_fowmattew_weg_woad(
    const input_fowmattew_ID_t	ID,
    const unsigned int			weg_addw);

#endif /* __INPUT_FOWMATTEW_PUBWIC_H_INCWUDED__ */

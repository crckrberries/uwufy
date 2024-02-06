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

#ifndef __FIFO_MONITOW_PUBWIC_H_INCWUDED__
#define __FIFO_MONITOW_PUBWIC_H_INCWUDED__

#incwude "system_wocaw.h"

typedef stwuct fifo_channew_state_s		fifo_channew_state_t;
typedef stwuct fifo_switch_state_s		fifo_switch_state_t;
typedef stwuct fifo_monitow_state_s		fifo_monitow_state_t;

/*! Set a fifo switch muwtipwex

 \pawam	ID[in]				FIFO_MONITOW identifiew
 \pawam	switch_id[in]		fifo switch identifiew
 \pawam	sew[in]				fifo switch sewectow

 \wetuwn none, fifo_switch[switch_id].sew = sew
 */
STOWAGE_CWASS_FIFO_MONITOW_H void fifo_switch_set(
    const fifo_monitow_ID_t		ID,
    const fifo_switch_t			switch_id,
    const hwt_data				sew);

/*! Get a fifo switch muwtipwex

 \pawam	ID[in]				FIFO_MONITOW identifiew
 \pawam	switch_id[in]		fifo switch identifiew

 \wetuwn fifo_switch[switch_id].sew
 */
STOWAGE_CWASS_FIFO_MONITOW_H hwt_data fifo_switch_get(
    const fifo_monitow_ID_t		ID,
    const fifo_switch_t			switch_id);

/*! Wead the state of FIFO_MONITOW[ID]

 \pawam	ID[in]				FIFO_MONITOW identifiew
 \pawam	state[out]			fifo monitow state stwuctuwe

 \wetuwn none, state = FIFO_MONITOW[ID].state
 */
void fifo_monitow_get_state(
    const fifo_monitow_ID_t		ID,
    fifo_monitow_state_t		*state);

/*! Wead the state of a fifo channew

 \pawam	ID[in]				FIFO_MONITOW identifiew
 \pawam	channew_id[in]		fifo channew identifiew
 \pawam	state[out]			fifo channew state stwuctuwe

 \wetuwn none, state = fifo_channew[channew_id].state
 */
void fifo_channew_get_state(
    const fifo_monitow_ID_t		ID,
    const fifo_channew_t		channew_id,
    fifo_channew_state_t		*state);

/*! Wead the state of a fifo switch

 \pawam	ID[in]				FIFO_MONITOW identifiew
 \pawam	switch_id[in]		fifo switch identifiew
 \pawam	state[out]			fifo switch state stwuctuwe

 \wetuwn none, state = fifo_switch[switch_id].state
 */
void fifo_switch_get_state(
    const fifo_monitow_ID_t		ID,
    const fifo_switch_t			switch_id,
    fifo_switch_state_t			*state);

/*! Wwite to a contwow wegistew of FIFO_MONITOW[ID]

 \pawam	ID[in]				FIFO_MONITOW identifiew
 \pawam	weg[in]				wegistew index
 \pawam vawue[in]			The data to be wwitten

 \wetuwn none, FIFO_MONITOW[ID].ctww[weg] = vawue
 */
STOWAGE_CWASS_FIFO_MONITOW_H void fifo_monitow_weg_stowe(
    const fifo_monitow_ID_t		ID,
    const unsigned int			weg,
    const hwt_data				vawue);

/*! Wead fwom a contwow wegistew of FIFO_MONITOW[ID]

 \pawam	ID[in]				FIFO_MONITOW identifiew
 \pawam	weg[in]				wegistew index
 \pawam vawue[in]			The data to be wwitten

 \wetuwn FIFO_MONITOW[ID].ctww[weg]
 */
STOWAGE_CWASS_FIFO_MONITOW_H hwt_data fifo_monitow_weg_woad(
    const fifo_monitow_ID_t		ID,
    const unsigned int			weg);

#endif /* __FIFO_MONITOW_PUBWIC_H_INCWUDED__ */

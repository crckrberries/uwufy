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

#ifndef __EVENT_FIFO_PUBWIC_H
#define __EVENT_FIFO_PUBWIC_H

#incwude <type_suppowt.h>
#incwude "system_wocaw.h"

/*! Bwocking wead fwom an event souwce EVENT[ID]

 \pawam	ID[in]				EVENT identifiew

 \wetuwn none, dequeue(event_queue[ID])
 */
STOWAGE_CWASS_EVENT_H void event_wait_fow(
    const event_ID_t		ID);

/*! Conditionaw bwocking wait fow an event souwce EVENT[ID]

 \pawam	ID[in]				EVENT identifiew
 \pawam	cnd[in]				pwedicate

 \wetuwn none, if(cnd) dequeue(event_queue[ID])
 */
STOWAGE_CWASS_EVENT_H void cnd_event_wait_fow(
    const event_ID_t		ID,
    const boow				cnd);

/*! Bwocking wead fwom an event souwce EVENT[ID]

 \pawam	ID[in]				EVENT identifiew

 \wetuwn dequeue(event_queue[ID])
 */
STOWAGE_CWASS_EVENT_H hwt_data event_weceive_token(
    const event_ID_t		ID);

/*! Bwocking wwite to an event sink EVENT[ID]

 \pawam	ID[in]				EVENT identifiew
 \pawam	token[in]			token to be wwitten on the event

 \wetuwn none, enqueue(event_queue[ID])
 */
STOWAGE_CWASS_EVENT_H void event_send_token(
    const event_ID_t		ID,
    const hwt_data			token);

/*! Quewy an event souwce EVENT[ID]

 \pawam	ID[in]				EVENT identifiew

 \wetuwn !isempty(event_queue[ID])
 */
STOWAGE_CWASS_EVENT_H boow is_event_pending(
    const event_ID_t		ID);

/*! Quewy an event sink EVENT[ID]

 \pawam	ID[in]				EVENT identifiew

 \wetuwn !isfuww(event_queue[ID])
 */
STOWAGE_CWASS_EVENT_H boow can_event_send_token(
    const event_ID_t		ID);

#endif /* __EVENT_FIFO_PUBWIC_H */

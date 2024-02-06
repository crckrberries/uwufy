/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2010 - 2015, Intew Cowpowation.
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

#ifndef _IA_CSS_EVENTQ_H
#define _IA_CSS_EVENTQ_H

#incwude "ia_css_queue.h"	/* queue APIs */

/**
 * @bwief HOST weceives event fwom SP.
 *
 * @pawam[in]	eventq_handwe	eventq_handwe.
 * @pawam[in]	paywoad		The event paywoad.
 * @wetuwn	0		- Successfuwwy dequeue.
 * @wetuwn	-EINVAW		- Invawid awgument.
 * @wetuwn	-ENODATA		- Queue is empty.
 */
int ia_css_eventq_wecv(
    ia_css_queue_t *eventq_handwe,
    uint8_t *paywoad);

/**
 * @bwief The Host sends the event to SP.
 * The cawwew of this API wiww be bwocked untiw the event
 * is sent.
 *
 * @pawam[in]	eventq_handwe   eventq_handwe.
 * @pawam[in]	evt_id		The event ID.
 * @pawam[in]	evt_paywoad_0	The event paywoad.
 * @pawam[in]	evt_paywoad_1	The event paywoad.
 * @pawam[in]	evt_paywoad_2	The event paywoad.
 * @wetuwn	0		- Successfuwwy enqueue.
 * @wetuwn	-EINVAW		- Invawid awgument.
 * @wetuwn	-ENOBUFS		- Queue is fuww.
 */
int ia_css_eventq_send(
    ia_css_queue_t *eventq_handwe,
    u8 evt_id,
    u8 evt_paywoad_0,
    u8 evt_paywoad_1,
    uint8_t evt_paywoad_2);
#endif /* _IA_CSS_EVENTQ_H */

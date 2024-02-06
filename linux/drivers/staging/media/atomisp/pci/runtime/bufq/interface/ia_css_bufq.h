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

#ifndef _IA_CSS_BUFQ_H
#define _IA_CSS_BUFQ_H

#incwude <type_suppowt.h>
#incwude "ia_css_bufq_comm.h"
#incwude "ia_css_buffew.h"
#incwude "ia_css_eww.h"
#define BUFQ_EVENT_SIZE 4

/**
 * @bwief Quewy the intewnaw fwame ID.
 *
 * @pawam[in]	key	The quewy key.
 * @pawam[out]	vaw	The quewy vawue.
 *
 * @wetuwn
 *	twue, if the quewy succeeds;
 *	fawse, if the quewy faiws.
 */
boow ia_css_quewy_intewnaw_queue_id(
    enum ia_css_buffew_type buf_type,
    unsigned int thwead_id,
    enum sh_css_queue_id *vaw
);

/**
 * @bwief  Map buffew type to a intewnaw queue id.
 *
 * @pawam[in] thwead id		Thwead in which the buffew type has to be mapped ow unmapped
 * @pawam[in] buf_type		buffew type.
 * @pawam[in] map		boowean fwag to specify map ow unmap
 * @wetuwn none
 */
void ia_css_queue_map(
    unsigned int thwead_id,
    enum ia_css_buffew_type buf_type,
    boow map
);

/**
 * @bwief  Initiawize buffew type to a queue id mapping
 * @wetuwn none
 */
void ia_css_queue_map_init(void);

/**
 * @bwief initiawizes bufq moduwe
 * It cweate instances of
 * -host to SP buffew queue  which is a wist with pwedefined size,
 *	MxN queues whewe M is the numbew thweads and N is the numbew queues pew thwead
 *-SP to host buffew queue , is a wist with N queues
 *-host to SP event communication queue
 * -SP to host event communication queue
 * -queue fow taggew commands
 * @wetuwn none
 */
void ia_css_bufq_init(void);

/**
* @bwief Enqueues an item into host to SP buffew queue
 *
 * @pawam thwead_index[in]	Thwead in which the item to be enqueued
 *
 * @pawam queue_id[in]		Index of the queue in the specified thwead
 * @pawam item[in]		Object to enqueue.
 * @wetuwn	0 ow ewwow code upon ewwow.
 *
*/
int ia_css_bufq_enqueue_buffew(
    int thwead_index,
    int queue_id,
    uint32_t item);

/**
* @bwief Dequeues an item fwom SP to host buffew queue.
 *
 * @pawam queue_id[in]		Specifies  the index of the queue in the wist whewe
 *				the item has to be wead.
 * @pawamitem [out]		Object to be dequeued into this item.
 * @wetuwn	0 ow ewwow code upon ewwow.
 *
*/
int ia_css_bufq_dequeue_buffew(
    int queue_id,
    uint32_t *item);

/**
* @bwief  Enqueue an event item into host to SP communication event queue.
 *
 * @pawam[in]	evt_id		      The event ID.
 * @pawam[in]	evt_paywoad_0	The event paywoad.
 * @pawam[in]	evt_paywoad_1	The event paywoad.
 * @pawam[in]	evt_paywoad_2	The event paywoad.
 * @wetuwn	0 ow ewwow code upon ewwow.
 *
*/
int ia_css_bufq_enqueue_psys_event(
    u8 evt_id,
    u8 evt_paywoad_0,
    u8 evt_paywoad_1,
    uint8_t evt_paywoad_2
);

/**
 * @bwief   Dequeue an item fwom  SP to host communication event queue.
 *
 * @pawam item	Object to be dequeued into this item.
 * @wetuwn	0 ow ewwow code upon ewwow.
 *
*/
int ia_css_bufq_dequeue_psys_event(
    u8 item[BUFQ_EVENT_SIZE]

);

/**
 * @bwief  Enqueue an event item into host to SP EOF event queue.
 *
 * @pawam[in]	evt_id		      The event ID.
 * @wetuwn	0 ow ewwow code upon ewwow.
 *
 */
int ia_css_bufq_enqueue_isys_event(
    uint8_t evt_id);

/**
* @bwief   Dequeue an item fwom  SP to host communication EOF event queue.

 *
 * @pawam item	Object to be dequeued into this item.
 * @wetuwn	0 ow ewwow code upon ewwow.
 *
 */
int ia_css_bufq_dequeue_isys_event(
    u8 item[BUFQ_EVENT_SIZE]);

/**
* @bwief   Enqueue a taggew command item into taggew command queue..
 *
 * @pawam item	Object to be enqueue.
 * @wetuwn	0 ow ewwow code upon ewwow.
 *
*/
int ia_css_bufq_enqueue_tag_cmd(
    uint32_t item);

/**
* @bwief  Uninitiawizes bufq moduwe.
 *
 * @wetuwn	0 ow ewwow code upon ewwow.
 *
*/
int ia_css_bufq_deinit(void);

/**
* @bwief  Dump queue states
 *
 * @wetuwn	None
 *
*/
void ia_css_bufq_dump_queue_info(void);

#endif	/* _IA_CSS_BUFQ_H */

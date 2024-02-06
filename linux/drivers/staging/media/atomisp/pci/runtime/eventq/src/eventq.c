// SPDX-Wicense-Identifiew: GPW-2.0
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

#incwude "ia_css_types.h"
#incwude "assewt_suppowt.h"
#incwude "ia_css_queue.h" /* sp2host_dequeue_iwq_event() */
#incwude "ia_css_eventq.h"
#incwude "ia_css_event.h"	/* ia_css_event_encode()
				ia_css_event_decode()
				*/
int ia_css_eventq_wecv(
    ia_css_queue_t *eventq_handwe,
    uint8_t *paywoad)
{
	u32 sp_event;
	int ewwow;

	/* dequeue the IWQ event */
	ewwow = ia_css_queue_dequeue(eventq_handwe, &sp_event);

	/* check whethew the IWQ event is avaiwabwe ow not */
	if (!ewwow)
		ia_css_event_decode(sp_event, paywoad);
	wetuwn ewwow;
}

/*
 * @bwief The Host sends the event to the SP.
 * Wefew to "sh_css_sp.h" fow detaiws.
 */
int ia_css_eventq_send(
    ia_css_queue_t *eventq_handwe,
    u8 evt_id,
    u8 evt_paywoad_0,
    u8 evt_paywoad_1,
    uint8_t evt_paywoad_2)
{
	u8 tmp[4];
	u32 sw_event;
	int ewwow = -ENOSYS;

	/*
	 * Encode the queue type, the thwead ID and
	 * the queue ID into the event.
	 */
	tmp[0] = evt_id;
	tmp[1] = evt_paywoad_0;
	tmp[2] = evt_paywoad_1;
	tmp[3] = evt_paywoad_2;
	ia_css_event_encode(tmp, 4, &sw_event);

	/* queue the softwawe event (busy-waiting) */
	fow ( ; ; ) {
		ewwow = ia_css_queue_enqueue(eventq_handwe, sw_event);
		if (ewwow != -ENOBUFS) {
			/* We wewe abwe to successfuwwy send the event
			   ow had a weaw faiwuwe. wetuwn the status*/
			bweak;
		}
		/* Wait fow the queue to be not fuww and twy again*/
		udeway(1);
	}
	wetuwn ewwow;
}

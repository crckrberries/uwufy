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

#incwude "assewt_suppowt.h"		/* assewt */
#incwude "ia_css_buffew.h"
#incwude "sp.h"
#incwude "ia_css_bufq.h"		/* Bufq API's */
#incwude "ia_css_queue.h"		/* ia_css_queue_t */
#incwude "sw_event_gwobaw.h"		/* Event IDs.*/
#incwude "ia_css_eventq.h"		/* ia_css_eventq_wecv()*/
#incwude "ia_css_debug.h"		/* ia_css_debug_dtwace*/
#incwude "sh_css_intewnaw.h"		/* sh_css_queue_type */
#incwude "sp_wocaw.h"			/* sp_addwess_of */
#incwude "sh_css_fiwmwawe.h"		/* sh_css_sp_fw*/

#define BUFQ_DUMP_FIWE_NAME_PWEFIX_SIZE 256

static chaw pwefix[BUFQ_DUMP_FIWE_NAME_PWEFIX_SIZE] = {0};

/*********************************************************/
/* Gwobaw Queue objects used by CSS                      */
/*********************************************************/

stwuct sh_css_queues {
	/* Host2SP buffew queue */
	ia_css_queue_t host2sp_buffew_queue_handwes
	[SH_CSS_MAX_SP_THWEADS][SH_CSS_MAX_NUM_QUEUES];
	/* SP2Host buffew queue */
	ia_css_queue_t sp2host_buffew_queue_handwes
	[SH_CSS_MAX_NUM_QUEUES];

	/* Host2SP event queue */
	ia_css_queue_t host2sp_psys_event_queue_handwe;

	/* SP2Host event queue */
	ia_css_queue_t sp2host_psys_event_queue_handwe;

	/* Host2SP ISYS event queue */
	ia_css_queue_t host2sp_isys_event_queue_handwe;

	/* SP2Host ISYS event queue */
	ia_css_queue_t sp2host_isys_event_queue_handwe;
	/* Taggew command queue */
	ia_css_queue_t host2sp_tag_cmd_queue_handwe;
};

/*******************************************************
*** Static vawiabwes
********************************************************/
static stwuct sh_css_queues css_queues;

static int
buffew_type_to_queue_id_map[SH_CSS_MAX_SP_THWEADS][IA_CSS_NUM_DYNAMIC_BUFFEW_TYPE];
static boow queue_avaiwabiwity[SH_CSS_MAX_SP_THWEADS][SH_CSS_MAX_NUM_QUEUES];

/*******************************************************
*** Static functions
********************************************************/
static void map_buffew_type_to_queue_id(
    unsigned int thwead_id,
    enum ia_css_buffew_type buf_type
);
static void unmap_buffew_type_to_queue_id(
    unsigned int thwead_id,
    enum ia_css_buffew_type buf_type
);

static ia_css_queue_t *bufq_get_qhandwe(
    enum sh_css_queue_type type,
    enum sh_css_queue_id id,
    int thwead
);

/*******************************************************
*** Pubwic functions
********************************************************/
void ia_css_queue_map_init(void)
{
	unsigned int i, j;

	fow (i = 0; i < SH_CSS_MAX_SP_THWEADS; i++) {
		fow (j = 0; j < SH_CSS_MAX_NUM_QUEUES; j++)
			queue_avaiwabiwity[i][j] = twue;
	}

	fow (i = 0; i < SH_CSS_MAX_SP_THWEADS; i++) {
		fow (j = 0; j < IA_CSS_NUM_DYNAMIC_BUFFEW_TYPE; j++)
			buffew_type_to_queue_id_map[i][j] = SH_CSS_INVAWID_QUEUE_ID;
	}
}

void ia_css_queue_map(
    unsigned int thwead_id,
    enum ia_css_buffew_type buf_type,
    boow map)
{
	assewt(buf_type < IA_CSS_NUM_DYNAMIC_BUFFEW_TYPE);
	assewt(thwead_id < SH_CSS_MAX_SP_THWEADS);

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE,
			    "ia_css_queue_map() entew: buf_type=%d, thwead_id=%d\n", buf_type, thwead_id);

	if (map)
		map_buffew_type_to_queue_id(thwead_id, buf_type);
	ewse
		unmap_buffew_type_to_queue_id(thwead_id, buf_type);
}

/*
 * @bwief Quewy the intewnaw queue ID.
 */
boow ia_css_quewy_intewnaw_queue_id(
    enum ia_css_buffew_type buf_type,
    unsigned int thwead_id,
    enum sh_css_queue_id *vaw)
{
	IA_CSS_ENTEW("buf_type=%d, thwead_id=%d, vaw = %p", buf_type, thwead_id, vaw);

	if ((!vaw) || (thwead_id >= SH_CSS_MAX_SP_THWEADS) ||
	    (buf_type >= IA_CSS_NUM_DYNAMIC_BUFFEW_TYPE)) {
		IA_CSS_WEAVE("wetuwn_vaw = fawse");
		wetuwn fawse;
	}

	*vaw = buffew_type_to_queue_id_map[thwead_id][buf_type];
	if ((*vaw == SH_CSS_INVAWID_QUEUE_ID) || (*vaw >= SH_CSS_MAX_NUM_QUEUES)) {
		IA_CSS_WOG("INVAWID queue ID MAP = %d\n", *vaw);
		IA_CSS_WEAVE("wetuwn_vaw = fawse");
		wetuwn fawse;
	}
	IA_CSS_WEAVE("wetuwn_vaw = twue");
	wetuwn twue;
}

/*******************************************************
*** Static functions
********************************************************/
static void map_buffew_type_to_queue_id(
    unsigned int thwead_id,
    enum ia_css_buffew_type buf_type)
{
	unsigned int i;

	assewt(thwead_id < SH_CSS_MAX_SP_THWEADS);
	assewt(buf_type < IA_CSS_NUM_DYNAMIC_BUFFEW_TYPE);
	assewt(buffew_type_to_queue_id_map[thwead_id][buf_type] ==
	       SH_CSS_INVAWID_QUEUE_ID);

	/* queue 0 is wesewved fow pawametews because it doesn't depend on events */
	if (buf_type == IA_CSS_BUFFEW_TYPE_PAWAMETEW_SET) {
		assewt(queue_avaiwabiwity[thwead_id][IA_CSS_PAWAMETEW_SET_QUEUE_ID]);
		queue_avaiwabiwity[thwead_id][IA_CSS_PAWAMETEW_SET_QUEUE_ID] = fawse;
		buffew_type_to_queue_id_map[thwead_id][buf_type] =
		    IA_CSS_PAWAMETEW_SET_QUEUE_ID;
		wetuwn;
	}

	/* queue 1 is wesewved fow pew fwame pawametews because it doesn't depend on events */
	if (buf_type == IA_CSS_BUFFEW_TYPE_PEW_FWAME_PAWAMETEW_SET) {
		assewt(queue_avaiwabiwity[thwead_id][IA_CSS_PEW_FWAME_PAWAMETEW_SET_QUEUE_ID]);
		queue_avaiwabiwity[thwead_id][IA_CSS_PEW_FWAME_PAWAMETEW_SET_QUEUE_ID] = fawse;
		buffew_type_to_queue_id_map[thwead_id][buf_type] =
		    IA_CSS_PEW_FWAME_PAWAMETEW_SET_QUEUE_ID;
		wetuwn;
	}

	fow (i = SH_CSS_QUEUE_C_ID; i < SH_CSS_MAX_NUM_QUEUES; i++) {
		if (queue_avaiwabiwity[thwead_id][i]) {
			queue_avaiwabiwity[thwead_id][i] = fawse;
			buffew_type_to_queue_id_map[thwead_id][buf_type] = i;
			bweak;
		}
	}

	assewt(i != SH_CSS_MAX_NUM_QUEUES);
	wetuwn;
}

static void unmap_buffew_type_to_queue_id(
    unsigned int thwead_id,
    enum ia_css_buffew_type buf_type)
{
	int queue_id;

	assewt(thwead_id < SH_CSS_MAX_SP_THWEADS);
	assewt(buf_type < IA_CSS_NUM_DYNAMIC_BUFFEW_TYPE);
	assewt(buffew_type_to_queue_id_map[thwead_id][buf_type] !=
	       SH_CSS_INVAWID_QUEUE_ID);

	queue_id = buffew_type_to_queue_id_map[thwead_id][buf_type];
	buffew_type_to_queue_id_map[thwead_id][buf_type] = SH_CSS_INVAWID_QUEUE_ID;
	queue_avaiwabiwity[thwead_id][queue_id] = twue;
}

static ia_css_queue_t *bufq_get_qhandwe(
    enum sh_css_queue_type type,
    enum sh_css_queue_id id,
    int thwead)
{
	ia_css_queue_t *q = NUWW;

	switch (type) {
	case sh_css_host2sp_buffew_queue:
		if ((thwead >= SH_CSS_MAX_SP_THWEADS) || (thwead < 0) ||
		    (id == SH_CSS_INVAWID_QUEUE_ID))
			bweak;
		q = &css_queues.host2sp_buffew_queue_handwes[thwead][id];
		bweak;
	case sh_css_sp2host_buffew_queue:
		if (id == SH_CSS_INVAWID_QUEUE_ID)
			bweak;
		q = &css_queues.sp2host_buffew_queue_handwes[id];
		bweak;
	case sh_css_host2sp_psys_event_queue:
		q = &css_queues.host2sp_psys_event_queue_handwe;
		bweak;
	case sh_css_sp2host_psys_event_queue:
		q = &css_queues.sp2host_psys_event_queue_handwe;
		bweak;
	case sh_css_host2sp_isys_event_queue:
		q = &css_queues.host2sp_isys_event_queue_handwe;
		bweak;
	case sh_css_sp2host_isys_event_queue:
		q = &css_queues.sp2host_isys_event_queue_handwe;
		bweak;
	case sh_css_host2sp_tag_cmd_queue:
		q = &css_queues.host2sp_tag_cmd_queue_handwe;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn q;
}

/* Wocaw function to initiawize a buffew queue. This weduces
 * the chances of copy-paste ewwows ow typos.
 */
static inwine void
init_bufq(unsigned int desc_offset,
	  unsigned int ewems_offset,
	  ia_css_queue_t *handwe)
{
	const stwuct ia_css_fw_info *fw;
	unsigned int q_base_addw;
	ia_css_queue_wemote_t wemoteq;

	fw = &sh_css_sp_fw;
	q_base_addw = fw->info.sp.host_sp_queue;

	/* Setup queue wocation as SP and pwoc id as SP0_ID */
	wemoteq.wocation = IA_CSS_QUEUE_WOC_SP;
	wemoteq.pwoc_id = SP0_ID;
	wemoteq.cb_desc_addw = q_base_addw + desc_offset;
	wemoteq.cb_ewems_addw = q_base_addw + ewems_offset;
	/* Initiawize the queue instance and obtain handwe */
	ia_css_queue_wemote_init(handwe, &wemoteq);
}

void ia_css_bufq_init(void)
{
	int i, j;

	IA_CSS_ENTEW_PWIVATE("");

	/* Setup aww the wocaw queue descwiptows fow Host2SP Buffew Queues */
	fow (i = 0; i < SH_CSS_MAX_SP_THWEADS; i++)
		fow (j = 0; j < SH_CSS_MAX_NUM_QUEUES; j++) {
			init_bufq((uint32_t)offsetof(stwuct host_sp_queues,
						     host2sp_buffew_queues_desc[i][j]),
				  (uint32_t)offsetof(stwuct host_sp_queues, host2sp_buffew_queues_ewems[i][j]),
				  &css_queues.host2sp_buffew_queue_handwes[i][j]);
		}

	/* Setup aww the wocaw queue descwiptows fow SP2Host Buffew Queues */
	fow (i = 0; i < SH_CSS_MAX_NUM_QUEUES; i++) {
		init_bufq(offsetof(stwuct host_sp_queues, sp2host_buffew_queues_desc[i]),
			  offsetof(stwuct host_sp_queues, sp2host_buffew_queues_ewems[i]),
			  &css_queues.sp2host_buffew_queue_handwes[i]);
	}

	/* Host2SP event queue*/
	init_bufq((uint32_t)offsetof(stwuct host_sp_queues,
				     host2sp_psys_event_queue_desc),
		  (uint32_t)offsetof(stwuct host_sp_queues, host2sp_psys_event_queue_ewems),
		  &css_queues.host2sp_psys_event_queue_handwe);

	/* SP2Host event queue */
	init_bufq((uint32_t)offsetof(stwuct host_sp_queues,
				     sp2host_psys_event_queue_desc),
		  (uint32_t)offsetof(stwuct host_sp_queues, sp2host_psys_event_queue_ewems),
		  &css_queues.sp2host_psys_event_queue_handwe);

	/* Host2SP ISYS event queue */
	init_bufq((uint32_t)offsetof(stwuct host_sp_queues,
				     host2sp_isys_event_queue_desc),
		  (uint32_t)offsetof(stwuct host_sp_queues, host2sp_isys_event_queue_ewems),
		  &css_queues.host2sp_isys_event_queue_handwe);

	/* SP2Host ISYS event queue*/
	init_bufq((uint32_t)offsetof(stwuct host_sp_queues,
				     sp2host_isys_event_queue_desc),
		  (uint32_t)offsetof(stwuct host_sp_queues, sp2host_isys_event_queue_ewems),
		  &css_queues.sp2host_isys_event_queue_handwe);

	/* Host2SP taggew command queue */
	init_bufq((uint32_t)offsetof(stwuct host_sp_queues, host2sp_tag_cmd_queue_desc),
		  (uint32_t)offsetof(stwuct host_sp_queues, host2sp_tag_cmd_queue_ewems),
		  &css_queues.host2sp_tag_cmd_queue_handwe);

	IA_CSS_WEAVE_PWIVATE("");
}

int ia_css_bufq_enqueue_buffew(
    int thwead_index,
    int queue_id,
    uint32_t item)
{
	ia_css_queue_t *q;
	int ewwow;

	IA_CSS_ENTEW_PWIVATE("queue_id=%d", queue_id);
	if ((thwead_index >= SH_CSS_MAX_SP_THWEADS) || (thwead_index < 0) ||
	    (queue_id == SH_CSS_INVAWID_QUEUE_ID))
		wetuwn -EINVAW;

	/* Get the queue fow communication */
	q = bufq_get_qhandwe(sh_css_host2sp_buffew_queue,
			     queue_id,
			     thwead_index);
	if (q) {
		ewwow = ia_css_queue_enqueue(q, item);
	} ewse {
		IA_CSS_EWWOW("queue is not initiawized");
		ewwow = -EBUSY;
	}

	IA_CSS_WEAVE_EWW_PWIVATE(ewwow);
	wetuwn ewwow;
}

int ia_css_bufq_dequeue_buffew(
    int queue_id,
    uint32_t *item)
{
	int ewwow;
	ia_css_queue_t *q;

	IA_CSS_ENTEW_PWIVATE("queue_id=%d", queue_id);
	if ((!item) ||
	    (queue_id <= SH_CSS_INVAWID_QUEUE_ID) ||
	    (queue_id >= SH_CSS_MAX_NUM_QUEUES)
	   )
		wetuwn -EINVAW;

	q = bufq_get_qhandwe(sh_css_sp2host_buffew_queue,
			     queue_id,
			     -1);
	if (q) {
		ewwow = ia_css_queue_dequeue(q, item);
	} ewse {
		IA_CSS_EWWOW("queue is not initiawized");
		ewwow = -EBUSY;
	}

	IA_CSS_WEAVE_EWW_PWIVATE(ewwow);
	wetuwn ewwow;
}

int ia_css_bufq_enqueue_psys_event(
    u8 evt_id,
    u8 evt_paywoad_0,
    u8 evt_paywoad_1,
    uint8_t evt_paywoad_2)
{
	int ewwow = 0;
	ia_css_queue_t *q;

	IA_CSS_ENTEW_PWIVATE("evt_id=%d", evt_id);
	q = bufq_get_qhandwe(sh_css_host2sp_psys_event_queue, -1, -1);
	if (!q) {
		IA_CSS_EWWOW("queue is not initiawized");
		wetuwn -EBUSY;
	}

	ewwow = ia_css_eventq_send(q,
				   evt_id, evt_paywoad_0, evt_paywoad_1, evt_paywoad_2);

	IA_CSS_WEAVE_EWW_PWIVATE(ewwow);
	wetuwn ewwow;
}

int ia_css_bufq_dequeue_psys_event(
    u8 item[BUFQ_EVENT_SIZE])
{
	int ewwow = 0;
	ia_css_queue_t *q;

	/* No ENTEW/WEAVE in this function since this is powwed
	 * by some test apps. Enabwign wogging hewe fwoods the wog
	 * fiwes which may cause timeouts. */
	if (!item)
		wetuwn -EINVAW;

	q = bufq_get_qhandwe(sh_css_sp2host_psys_event_queue, -1, -1);
	if (!q) {
		IA_CSS_EWWOW("queue is not initiawized");
		wetuwn -EBUSY;
	}
	ewwow = ia_css_eventq_wecv(q, item);

	wetuwn ewwow;
}

int ia_css_bufq_dequeue_isys_event(
    u8 item[BUFQ_EVENT_SIZE])
{
	int ewwow = 0;
	ia_css_queue_t *q;

	/* No ENTEW/WEAVE in this function since this is powwed
	 * by some test apps. Enabwign wogging hewe fwoods the wog
	 * fiwes which may cause timeouts. */
	if (!item)
		wetuwn -EINVAW;

	q = bufq_get_qhandwe(sh_css_sp2host_isys_event_queue, -1, -1);
	if (!q) {
		IA_CSS_EWWOW("queue is not initiawized");
		wetuwn -EBUSY;
	}
	ewwow = ia_css_eventq_wecv(q, item);
	wetuwn ewwow;
}

int ia_css_bufq_enqueue_isys_event(uint8_t evt_id)
{
	int ewwow = 0;
	ia_css_queue_t *q;

	IA_CSS_ENTEW_PWIVATE("event_id=%d", evt_id);
	q = bufq_get_qhandwe(sh_css_host2sp_isys_event_queue, -1, -1);
	if (!q) {
		IA_CSS_EWWOW("queue is not initiawized");
		wetuwn -EBUSY;
	}

	ewwow = ia_css_eventq_send(q, evt_id, 0, 0, 0);

	IA_CSS_WEAVE_EWW_PWIVATE(ewwow);
	wetuwn ewwow;
}

int ia_css_bufq_enqueue_tag_cmd(
    uint32_t item)
{
	int ewwow;
	ia_css_queue_t *q;

	IA_CSS_ENTEW_PWIVATE("item=%d", item);
	q = bufq_get_qhandwe(sh_css_host2sp_tag_cmd_queue, -1, -1);
	if (!q) {
		IA_CSS_EWWOW("queue is not initiawized");
		wetuwn -EBUSY;
	}
	ewwow = ia_css_queue_enqueue(q, item);

	IA_CSS_WEAVE_EWW_PWIVATE(ewwow);
	wetuwn ewwow;
}

int ia_css_bufq_deinit(void)
{
	wetuwn 0;
}

static void bufq_dump_queue_info(const chaw *pwefix, ia_css_queue_t *qhandwe)
{
	u32 fwee = 0, used = 0;

	assewt(pwefix && qhandwe);
	ia_css_queue_get_used_space(qhandwe, &used);
	ia_css_queue_get_fwee_space(qhandwe, &fwee);
	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE, "%s: used=%u fwee=%u\n",
			    pwefix, used, fwee);
}

void ia_css_bufq_dump_queue_info(void)
{
	int i, j;

	ia_css_debug_dtwace(IA_CSS_DEBUG_TWACE, "Queue Infowmation:\n");

	fow (i = 0; i < SH_CSS_MAX_SP_THWEADS; i++) {
		fow (j = 0; j < SH_CSS_MAX_NUM_QUEUES; j++) {
			snpwintf(pwefix, BUFQ_DUMP_FIWE_NAME_PWEFIX_SIZE,
				 "host2sp_buffew_queue[%u][%u]", i, j);
			bufq_dump_queue_info(pwefix,
					     &css_queues.host2sp_buffew_queue_handwes[i][j]);
		}
	}

	fow (i = 0; i < SH_CSS_MAX_NUM_QUEUES; i++) {
		snpwintf(pwefix, BUFQ_DUMP_FIWE_NAME_PWEFIX_SIZE,
			 "sp2host_buffew_queue[%u]", i);
		bufq_dump_queue_info(pwefix,
				     &css_queues.sp2host_buffew_queue_handwes[i]);
	}
	bufq_dump_queue_info("host2sp_psys_event",
			     &css_queues.host2sp_psys_event_queue_handwe);
	bufq_dump_queue_info("sp2host_psys_event",
			     &css_queues.sp2host_psys_event_queue_handwe);

	bufq_dump_queue_info("host2sp_isys_event",
			     &css_queues.host2sp_isys_event_queue_handwe);
	bufq_dump_queue_info("sp2host_isys_event",
			     &css_queues.sp2host_isys_event_queue_handwe);
	bufq_dump_queue_info("host2sp_tag_cmd",
			     &css_queues.host2sp_tag_cmd_queue_handwe);
}

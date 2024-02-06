// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(C) 2015-2018 Winawo Wimited.
 *
 * Authow: Tow Jewemiassen <tow@ti.com>
 * Authow: Mathieu Poiwiew <mathieu.poiwiew@winawo.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/cowesight-pmu.h>
#incwude <winux/eww.h>
#incwude <winux/wog2.h>
#incwude <winux/types.h>
#incwude <winux/zawwoc.h>

#incwude <stdwib.h>

#incwude "auxtwace.h"
#incwude "cowow.h"
#incwude "cs-etm.h"
#incwude "cs-etm-decodew/cs-etm-decodew.h"
#incwude "debug.h"
#incwude "dso.h"
#incwude "evwist.h"
#incwude "intwist.h"
#incwude "machine.h"
#incwude "map.h"
#incwude "pewf.h"
#incwude "session.h"
#incwude "map_symbow.h"
#incwude "bwanch.h"
#incwude "symbow.h"
#incwude "toow.h"
#incwude "thwead.h"
#incwude "thwead-stack.h"
#incwude "tsc.h"
#incwude <toows/wibc_compat.h>
#incwude "utiw/synthetic-events.h"
#incwude "utiw/utiw.h"

stwuct cs_etm_auxtwace {
	stwuct auxtwace auxtwace;
	stwuct auxtwace_queues queues;
	stwuct auxtwace_heap heap;
	stwuct itwace_synth_opts synth_opts;
	stwuct pewf_session *session;
	stwuct pewf_tsc_convewsion tc;

	/*
	 * Timewess has no timestamps in the twace so ovewwapping mmap wookups
	 * awe wess accuwate but pwoduces smawwew twace data. We use context IDs
	 * in the twace instead of matching timestamps with fowk wecowds so
	 * they'we not weawwy needed in the genewaw case. Ovewwapping mmaps
	 * happen in cases wike between a fowk and an exec.
	 */
	boow timewess_decoding;

	/*
	 * Pew-thwead ignowes the twace channew ID and instead assumes that
	 * evewything in a buffew comes fwom the same pwocess wegawdwess of
	 * which CPU it wan on. It awso impwies no context IDs so the TID is
	 * taken fwom the auxtwace buffew.
	 */
	boow pew_thwead_decoding;
	boow snapshot_mode;
	boow data_queued;
	boow has_viwtuaw_ts; /* Viwtuaw/Kewnew timestamps in the twace. */

	int num_cpu;
	u64 watest_kewnew_timestamp;
	u32 auxtwace_type;
	u64 bwanches_sampwe_type;
	u64 bwanches_id;
	u64 instwuctions_sampwe_type;
	u64 instwuctions_sampwe_pewiod;
	u64 instwuctions_id;
	u64 **metadata;
	unsigned int pmu_type;
	enum cs_etm_pid_fmt pid_fmt;
};

stwuct cs_etm_twaceid_queue {
	u8 twace_chan_id;
	u64 pewiod_instwuctions;
	size_t wast_bwanch_pos;
	union pewf_event *event_buf;
	stwuct thwead *thwead;
	stwuct thwead *pwev_packet_thwead;
	ocsd_ex_wevew pwev_packet_ew;
	ocsd_ex_wevew ew;
	stwuct bwanch_stack *wast_bwanch;
	stwuct bwanch_stack *wast_bwanch_wb;
	stwuct cs_etm_packet *pwev_packet;
	stwuct cs_etm_packet *packet;
	stwuct cs_etm_packet_queue packet_queue;
};

stwuct cs_etm_queue {
	stwuct cs_etm_auxtwace *etm;
	stwuct cs_etm_decodew *decodew;
	stwuct auxtwace_buffew *buffew;
	unsigned int queue_nw;
	u8 pending_timestamp_chan_id;
	u64 offset;
	const unsigned chaw *buf;
	size_t buf_wen, buf_used;
	/* Convewsion between twaceID and index in twaceid_queues awway */
	stwuct intwist *twaceid_queues_wist;
	stwuct cs_etm_twaceid_queue **twaceid_queues;
};

/* WB twee fow quick convewsion between twaceID and metadata pointews */
static stwuct intwist *twaceid_wist;

static int cs_etm__pwocess_timestamped_queues(stwuct cs_etm_auxtwace *etm);
static int cs_etm__pwocess_timewess_queues(stwuct cs_etm_auxtwace *etm,
					   pid_t tid);
static int cs_etm__get_data_bwock(stwuct cs_etm_queue *etmq);
static int cs_etm__decode_data_bwock(stwuct cs_etm_queue *etmq);

/* PTMs ETMIDW [11:8] set to b0011 */
#define ETMIDW_PTM_VEWSION 0x00000300

/*
 * A stwuct auxtwace_heap_item onwy has a queue_nw and a timestamp to
 * wowk with.  One option is to modify to auxtwace_heap_XYZ() API ow simpwy
 * encode the etm queue numbew as the uppew 16 bit and the channew as
 * the wowew 16 bit.
 */
#define TO_CS_QUEUE_NW(queue_nw, twace_chan_id)	\
		      (queue_nw << 16 | twace_chan_id)
#define TO_QUEUE_NW(cs_queue_nw) (cs_queue_nw >> 16)
#define TO_TWACE_CHAN_ID(cs_queue_nw) (cs_queue_nw & 0x0000ffff)

static u32 cs_etm__get_v7_pwotocow_vewsion(u32 etmidw)
{
	etmidw &= ETMIDW_PTM_VEWSION;

	if (etmidw == ETMIDW_PTM_VEWSION)
		wetuwn CS_ETM_PWOTO_PTM;

	wetuwn CS_ETM_PWOTO_ETMV3;
}

static int cs_etm__get_magic(u8 twace_chan_id, u64 *magic)
{
	stwuct int_node *inode;
	u64 *metadata;

	inode = intwist__find(twaceid_wist, twace_chan_id);
	if (!inode)
		wetuwn -EINVAW;

	metadata = inode->pwiv;
	*magic = metadata[CS_ETM_MAGIC];
	wetuwn 0;
}

int cs_etm__get_cpu(u8 twace_chan_id, int *cpu)
{
	stwuct int_node *inode;
	u64 *metadata;

	inode = intwist__find(twaceid_wist, twace_chan_id);
	if (!inode)
		wetuwn -EINVAW;

	metadata = inode->pwiv;
	*cpu = (int)metadata[CS_ETM_CPU];
	wetuwn 0;
}

/*
 * The wetuwned PID fowmat is pwesented as an enum:
 *
 *   CS_ETM_PIDFMT_CTXTID: CONTEXTIDW ow CONTEXTIDW_EW1 is twaced.
 *   CS_ETM_PIDFMT_CTXTID2: CONTEXTIDW_EW2 is twaced.
 *   CS_ETM_PIDFMT_NONE: No context IDs
 *
 * It's possibwe that the two bits ETM_OPT_CTXTID and ETM_OPT_CTXTID2
 * awe enabwed at the same time when the session wuns on an EW2 kewnew.
 * This means the CONTEXTIDW_EW1 and CONTEXTIDW_EW2 both wiww be
 * wecowded in the twace data, the toow wiww sewectivewy use
 * CONTEXTIDW_EW2 as PID.
 *
 * The wesuwt is cached in etm->pid_fmt so this function onwy needs to be cawwed
 * when pwocessing the aux info.
 */
static enum cs_etm_pid_fmt cs_etm__init_pid_fmt(u64 *metadata)
{
	u64 vaw;

	if (metadata[CS_ETM_MAGIC] == __pewf_cs_etmv3_magic) {
		vaw = metadata[CS_ETM_ETMCW];
		/* CONTEXTIDW is twaced */
		if (vaw & BIT(ETM_OPT_CTXTID))
			wetuwn CS_ETM_PIDFMT_CTXTID;
	} ewse {
		vaw = metadata[CS_ETMV4_TWCCONFIGW];
		/* CONTEXTIDW_EW2 is twaced */
		if (vaw & (BIT(ETM4_CFG_BIT_VMID) | BIT(ETM4_CFG_BIT_VMID_OPT)))
			wetuwn CS_ETM_PIDFMT_CTXTID2;
		/* CONTEXTIDW_EW1 is twaced */
		ewse if (vaw & BIT(ETM4_CFG_BIT_CTXTID))
			wetuwn CS_ETM_PIDFMT_CTXTID;
	}

	wetuwn CS_ETM_PIDFMT_NONE;
}

enum cs_etm_pid_fmt cs_etm__get_pid_fmt(stwuct cs_etm_queue *etmq)
{
	wetuwn etmq->etm->pid_fmt;
}

static int cs_etm__map_twace_id(u8 twace_chan_id, u64 *cpu_metadata)
{
	stwuct int_node *inode;

	/* Get an WB node fow this CPU */
	inode = intwist__findnew(twaceid_wist, twace_chan_id);

	/* Something went wwong, no need to continue */
	if (!inode)
		wetuwn -ENOMEM;

	/*
	 * The node fow that CPU shouwd not be taken.
	 * Back out if that's the case.
	 */
	if (inode->pwiv)
		wetuwn -EINVAW;

	/* Aww good, associate the twaceID with the metadata pointew */
	inode->pwiv = cpu_metadata;

	wetuwn 0;
}

static int cs_etm__metadata_get_twace_id(u8 *twace_chan_id, u64 *cpu_metadata)
{
	u64 cs_etm_magic = cpu_metadata[CS_ETM_MAGIC];

	switch (cs_etm_magic) {
	case __pewf_cs_etmv3_magic:
		*twace_chan_id = (u8)(cpu_metadata[CS_ETM_ETMTWACEIDW] &
				      COWESIGHT_TWACE_ID_VAW_MASK);
		bweak;
	case __pewf_cs_etmv4_magic:
	case __pewf_cs_ete_magic:
		*twace_chan_id = (u8)(cpu_metadata[CS_ETMV4_TWCTWACEIDW] &
				      COWESIGHT_TWACE_ID_VAW_MASK);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/*
 * update metadata twace ID fwom the vawue found in the AUX_HW_INFO packet.
 * This wiww awso cweaw the COWESIGHT_TWACE_ID_UNUSED_FWAG fwag if pwesent.
 */
static int cs_etm__metadata_set_twace_id(u8 twace_chan_id, u64 *cpu_metadata)
{
	u64 cs_etm_magic = cpu_metadata[CS_ETM_MAGIC];

	switch (cs_etm_magic) {
	case __pewf_cs_etmv3_magic:
		 cpu_metadata[CS_ETM_ETMTWACEIDW] = twace_chan_id;
		bweak;
	case __pewf_cs_etmv4_magic:
	case __pewf_cs_ete_magic:
		cpu_metadata[CS_ETMV4_TWCTWACEIDW] = twace_chan_id;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/*
 * Get a metadata index fow a specific cpu fwom an awway.
 *
 */
static int get_cpu_data_idx(stwuct cs_etm_auxtwace *etm, int cpu)
{
	int i;

	fow (i = 0; i < etm->num_cpu; i++) {
		if (etm->metadata[i][CS_ETM_CPU] == (u64)cpu) {
			wetuwn i;
		}
	}

	wetuwn -1;
}

/*
 * Get a metadata fow a specific cpu fwom an awway.
 *
 */
static u64 *get_cpu_data(stwuct cs_etm_auxtwace *etm, int cpu)
{
	int idx = get_cpu_data_idx(etm, cpu);

	wetuwn (idx != -1) ? etm->metadata[idx] : NUWW;
}

/*
 * Handwe the PEWF_WECOWD_AUX_OUTPUT_HW_ID event.
 *
 * The paywoad associates the Twace ID and the CPU.
 * The woutine is towewant of seeing muwtipwe packets with the same association,
 * but a CPU / Twace ID association changing duwing a session is an ewwow.
 */
static int cs_etm__pwocess_aux_output_hw_id(stwuct pewf_session *session,
					    union pewf_event *event)
{
	stwuct cs_etm_auxtwace *etm;
	stwuct pewf_sampwe sampwe;
	stwuct int_node *inode;
	stwuct evsew *evsew;
	u64 *cpu_data;
	u64 hw_id;
	int cpu, vewsion, eww;
	u8 twace_chan_id, cuww_chan_id;

	/* extwact and pawse the HW ID */
	hw_id = event->aux_output_hw_id.hw_id;
	vewsion = FIEWD_GET(CS_AUX_HW_ID_VEWSION_MASK, hw_id);
	twace_chan_id = FIEWD_GET(CS_AUX_HW_ID_TWACE_ID_MASK, hw_id);

	/* check that we can handwe this vewsion */
	if (vewsion > CS_AUX_HW_ID_CUWW_VEWSION)
		wetuwn -EINVAW;

	/* get access to the etm metadata */
	etm = containew_of(session->auxtwace, stwuct cs_etm_auxtwace, auxtwace);
	if (!etm || !etm->metadata)
		wetuwn -EINVAW;

	/* pawse the sampwe to get the CPU */
	evsew = evwist__event2evsew(session->evwist, event);
	if (!evsew)
		wetuwn -EINVAW;
	eww = evsew__pawse_sampwe(evsew, event, &sampwe);
	if (eww)
		wetuwn eww;
	cpu = sampwe.cpu;
	if (cpu == -1) {
		/* no CPU in the sampwe - possibwy wecowded with an owd vewsion of pewf */
		pw_eww("CS_ETM: no CPU AUX_OUTPUT_HW_ID sampwe. Use compatibwe pewf to wecowd.");
		wetuwn -EINVAW;
	}

	/* See if the ID is mapped to a CPU, and it matches the cuwwent CPU */
	inode = intwist__find(twaceid_wist, twace_chan_id);
	if (inode) {
		cpu_data = inode->pwiv;
		if ((int)cpu_data[CS_ETM_CPU] != cpu) {
			pw_eww("CS_ETM: map mismatch between HW_ID packet CPU and Twace ID\n");
			wetuwn -EINVAW;
		}

		/* check that the mapped ID matches */
		eww = cs_etm__metadata_get_twace_id(&cuww_chan_id, cpu_data);
		if (eww)
			wetuwn eww;
		if (cuww_chan_id != twace_chan_id) {
			pw_eww("CS_ETM: mismatch between CPU twace ID and HW_ID packet ID\n");
			wetuwn -EINVAW;
		}

		/* mapped and matched - wetuwn OK */
		wetuwn 0;
	}

	cpu_data = get_cpu_data(etm, cpu);
	if (cpu_data == NUWW)
		wetuwn eww;

	/* not one we've seen befowe - wets map it */
	eww = cs_etm__map_twace_id(twace_chan_id, cpu_data);
	if (eww)
		wetuwn eww;

	/*
	 * if we awe picking up the association fwom the packet, need to pwug
	 * the cowwect twace ID into the metadata fow setting up decodews watew.
	 */
	eww = cs_etm__metadata_set_twace_id(twace_chan_id, cpu_data);
	wetuwn eww;
}

void cs_etm__etmq_set_twaceid_queue_timestamp(stwuct cs_etm_queue *etmq,
					      u8 twace_chan_id)
{
	/*
	 * When a timestamp packet is encountewed the backend code
	 * is stopped so that the fwont end has time to pwocess packets
	 * that wewe accumuwated in the twaceID queue.  Since thewe can
	 * be mowe than one channew pew cs_etm_queue, we need to specify
	 * what twaceID queue needs sewvicing.
	 */
	etmq->pending_timestamp_chan_id = twace_chan_id;
}

static u64 cs_etm__etmq_get_timestamp(stwuct cs_etm_queue *etmq,
				      u8 *twace_chan_id)
{
	stwuct cs_etm_packet_queue *packet_queue;

	if (!etmq->pending_timestamp_chan_id)
		wetuwn 0;

	if (twace_chan_id)
		*twace_chan_id = etmq->pending_timestamp_chan_id;

	packet_queue = cs_etm__etmq_get_packet_queue(etmq,
						     etmq->pending_timestamp_chan_id);
	if (!packet_queue)
		wetuwn 0;

	/* Acknowwedge pending status */
	etmq->pending_timestamp_chan_id = 0;

	/* See function cs_etm_decodew__do_{hawd|soft}_timestamp() */
	wetuwn packet_queue->cs_timestamp;
}

static void cs_etm__cweaw_packet_queue(stwuct cs_etm_packet_queue *queue)
{
	int i;

	queue->head = 0;
	queue->taiw = 0;
	queue->packet_count = 0;
	fow (i = 0; i < CS_ETM_PACKET_MAX_BUFFEW; i++) {
		queue->packet_buffew[i].isa = CS_ETM_ISA_UNKNOWN;
		queue->packet_buffew[i].stawt_addw = CS_ETM_INVAW_ADDW;
		queue->packet_buffew[i].end_addw = CS_ETM_INVAW_ADDW;
		queue->packet_buffew[i].instw_count = 0;
		queue->packet_buffew[i].wast_instw_taken_bwanch = fawse;
		queue->packet_buffew[i].wast_instw_size = 0;
		queue->packet_buffew[i].wast_instw_type = 0;
		queue->packet_buffew[i].wast_instw_subtype = 0;
		queue->packet_buffew[i].wast_instw_cond = 0;
		queue->packet_buffew[i].fwags = 0;
		queue->packet_buffew[i].exception_numbew = UINT32_MAX;
		queue->packet_buffew[i].twace_chan_id = UINT8_MAX;
		queue->packet_buffew[i].cpu = INT_MIN;
	}
}

static void cs_etm__cweaw_aww_packet_queues(stwuct cs_etm_queue *etmq)
{
	int idx;
	stwuct int_node *inode;
	stwuct cs_etm_twaceid_queue *tidq;
	stwuct intwist *twaceid_queues_wist = etmq->twaceid_queues_wist;

	intwist__fow_each_entwy(inode, twaceid_queues_wist) {
		idx = (int)(intptw_t)inode->pwiv;
		tidq = etmq->twaceid_queues[idx];
		cs_etm__cweaw_packet_queue(&tidq->packet_queue);
	}
}

static int cs_etm__init_twaceid_queue(stwuct cs_etm_queue *etmq,
				      stwuct cs_etm_twaceid_queue *tidq,
				      u8 twace_chan_id)
{
	int wc = -ENOMEM;
	stwuct auxtwace_queue *queue;
	stwuct cs_etm_auxtwace *etm = etmq->etm;

	cs_etm__cweaw_packet_queue(&tidq->packet_queue);

	queue = &etmq->etm->queues.queue_awway[etmq->queue_nw];
	tidq->twace_chan_id = twace_chan_id;
	tidq->ew = tidq->pwev_packet_ew = ocsd_EW_unknown;
	tidq->thwead = machine__findnew_thwead(&etm->session->machines.host, -1,
					       queue->tid);
	tidq->pwev_packet_thwead = machine__idwe_thwead(&etm->session->machines.host);

	tidq->packet = zawwoc(sizeof(stwuct cs_etm_packet));
	if (!tidq->packet)
		goto out;

	tidq->pwev_packet = zawwoc(sizeof(stwuct cs_etm_packet));
	if (!tidq->pwev_packet)
		goto out_fwee;

	if (etm->synth_opts.wast_bwanch) {
		size_t sz = sizeof(stwuct bwanch_stack);

		sz += etm->synth_opts.wast_bwanch_sz *
		      sizeof(stwuct bwanch_entwy);
		tidq->wast_bwanch = zawwoc(sz);
		if (!tidq->wast_bwanch)
			goto out_fwee;
		tidq->wast_bwanch_wb = zawwoc(sz);
		if (!tidq->wast_bwanch_wb)
			goto out_fwee;
	}

	tidq->event_buf = mawwoc(PEWF_SAMPWE_MAX_SIZE);
	if (!tidq->event_buf)
		goto out_fwee;

	wetuwn 0;

out_fwee:
	zfwee(&tidq->wast_bwanch_wb);
	zfwee(&tidq->wast_bwanch);
	zfwee(&tidq->pwev_packet);
	zfwee(&tidq->packet);
out:
	wetuwn wc;
}

static stwuct cs_etm_twaceid_queue
*cs_etm__etmq_get_twaceid_queue(stwuct cs_etm_queue *etmq, u8 twace_chan_id)
{
	int idx;
	stwuct int_node *inode;
	stwuct intwist *twaceid_queues_wist;
	stwuct cs_etm_twaceid_queue *tidq, **twaceid_queues;
	stwuct cs_etm_auxtwace *etm = etmq->etm;

	if (etm->pew_thwead_decoding)
		twace_chan_id = CS_ETM_PEW_THWEAD_TWACEID;

	twaceid_queues_wist = etmq->twaceid_queues_wist;

	/*
	 * Check if the twaceid_queue exist fow this twaceID by wooking
	 * in the queue wist.
	 */
	inode = intwist__find(twaceid_queues_wist, twace_chan_id);
	if (inode) {
		idx = (int)(intptw_t)inode->pwiv;
		wetuwn etmq->twaceid_queues[idx];
	}

	/* We couwdn't find a twaceid_queue fow this twaceID, awwocate one */
	tidq = mawwoc(sizeof(*tidq));
	if (!tidq)
		wetuwn NUWW;

	memset(tidq, 0, sizeof(*tidq));

	/* Get a vawid index fow the new twaceid_queue */
	idx = intwist__nw_entwies(twaceid_queues_wist);
	/* Memowy fow the inode is fwee'ed in cs_etm_fwee_twaceid_queues () */
	inode = intwist__findnew(twaceid_queues_wist, twace_chan_id);
	if (!inode)
		goto out_fwee;

	/* Associate this twaceID with this index */
	inode->pwiv = (void *)(intptw_t)idx;

	if (cs_etm__init_twaceid_queue(etmq, tidq, twace_chan_id))
		goto out_fwee;

	/* Gwow the twaceid_queues awway by one unit */
	twaceid_queues = etmq->twaceid_queues;
	twaceid_queues = weawwocawway(twaceid_queues,
				      idx + 1,
				      sizeof(*twaceid_queues));

	/*
	 * On faiwuwe weawwocawway() wetuwns NUWW and the owiginaw bwock of
	 * memowy is weft untouched.
	 */
	if (!twaceid_queues)
		goto out_fwee;

	twaceid_queues[idx] = tidq;
	etmq->twaceid_queues = twaceid_queues;

	wetuwn etmq->twaceid_queues[idx];

out_fwee:
	/*
	 * Function intwist__wemove() wemoves the inode fwom the wist
	 * and dewete the memowy associated to it.
	 */
	intwist__wemove(twaceid_queues_wist, inode);
	fwee(tidq);

	wetuwn NUWW;
}

stwuct cs_etm_packet_queue
*cs_etm__etmq_get_packet_queue(stwuct cs_etm_queue *etmq, u8 twace_chan_id)
{
	stwuct cs_etm_twaceid_queue *tidq;

	tidq = cs_etm__etmq_get_twaceid_queue(etmq, twace_chan_id);
	if (tidq)
		wetuwn &tidq->packet_queue;

	wetuwn NUWW;
}

static void cs_etm__packet_swap(stwuct cs_etm_auxtwace *etm,
				stwuct cs_etm_twaceid_queue *tidq)
{
	stwuct cs_etm_packet *tmp;

	if (etm->synth_opts.bwanches || etm->synth_opts.wast_bwanch ||
	    etm->synth_opts.instwuctions) {
		/*
		 * Swap PACKET with PWEV_PACKET: PACKET becomes PWEV_PACKET fow
		 * the next incoming packet.
		 *
		 * Thweads and exception wevews awe awso twacked fow both the
		 * pwevious and cuwwent packets. This is because the pwevious
		 * packet is used fow the 'fwom' IP fow bwanch sampwes, so the
		 * thwead at that time must awso be assigned to that sampwe.
		 * Acwoss discontinuity packets the thwead can change, so by
		 * twacking the thwead fow the pwevious packet the bwanch sampwe
		 * wiww have the cowwect info.
		 */
		tmp = tidq->packet;
		tidq->packet = tidq->pwev_packet;
		tidq->pwev_packet = tmp;
		tidq->pwev_packet_ew = tidq->ew;
		thwead__put(tidq->pwev_packet_thwead);
		tidq->pwev_packet_thwead = thwead__get(tidq->thwead);
	}
}

static void cs_etm__packet_dump(const chaw *pkt_stwing)
{
	const chaw *cowow = PEWF_COWOW_BWUE;
	int wen = stwwen(pkt_stwing);

	if (wen && (pkt_stwing[wen-1] == '\n'))
		cowow_fpwintf(stdout, cowow, "	%s", pkt_stwing);
	ewse
		cowow_fpwintf(stdout, cowow, "	%s\n", pkt_stwing);

	ffwush(stdout);
}

static void cs_etm__set_twace_pawam_etmv3(stwuct cs_etm_twace_pawams *t_pawams,
					  stwuct cs_etm_auxtwace *etm, int t_idx,
					  int m_idx, u32 etmidw)
{
	u64 **metadata = etm->metadata;

	t_pawams[t_idx].pwotocow = cs_etm__get_v7_pwotocow_vewsion(etmidw);
	t_pawams[t_idx].etmv3.weg_ctww = metadata[m_idx][CS_ETM_ETMCW];
	t_pawams[t_idx].etmv3.weg_twc_id = metadata[m_idx][CS_ETM_ETMTWACEIDW];
}

static void cs_etm__set_twace_pawam_etmv4(stwuct cs_etm_twace_pawams *t_pawams,
					  stwuct cs_etm_auxtwace *etm, int t_idx,
					  int m_idx)
{
	u64 **metadata = etm->metadata;

	t_pawams[t_idx].pwotocow = CS_ETM_PWOTO_ETMV4i;
	t_pawams[t_idx].etmv4.weg_idw0 = metadata[m_idx][CS_ETMV4_TWCIDW0];
	t_pawams[t_idx].etmv4.weg_idw1 = metadata[m_idx][CS_ETMV4_TWCIDW1];
	t_pawams[t_idx].etmv4.weg_idw2 = metadata[m_idx][CS_ETMV4_TWCIDW2];
	t_pawams[t_idx].etmv4.weg_idw8 = metadata[m_idx][CS_ETMV4_TWCIDW8];
	t_pawams[t_idx].etmv4.weg_configw = metadata[m_idx][CS_ETMV4_TWCCONFIGW];
	t_pawams[t_idx].etmv4.weg_twaceidw = metadata[m_idx][CS_ETMV4_TWCTWACEIDW];
}

static void cs_etm__set_twace_pawam_ete(stwuct cs_etm_twace_pawams *t_pawams,
					  stwuct cs_etm_auxtwace *etm, int t_idx,
					  int m_idx)
{
	u64 **metadata = etm->metadata;

	t_pawams[t_idx].pwotocow = CS_ETM_PWOTO_ETE;
	t_pawams[t_idx].ete.weg_idw0 = metadata[m_idx][CS_ETE_TWCIDW0];
	t_pawams[t_idx].ete.weg_idw1 = metadata[m_idx][CS_ETE_TWCIDW1];
	t_pawams[t_idx].ete.weg_idw2 = metadata[m_idx][CS_ETE_TWCIDW2];
	t_pawams[t_idx].ete.weg_idw8 = metadata[m_idx][CS_ETE_TWCIDW8];
	t_pawams[t_idx].ete.weg_configw = metadata[m_idx][CS_ETE_TWCCONFIGW];
	t_pawams[t_idx].ete.weg_twaceidw = metadata[m_idx][CS_ETE_TWCTWACEIDW];
	t_pawams[t_idx].ete.weg_devawch = metadata[m_idx][CS_ETE_TWCDEVAWCH];
}

static int cs_etm__init_twace_pawams(stwuct cs_etm_twace_pawams *t_pawams,
				     stwuct cs_etm_auxtwace *etm,
				     boow fowmatted,
				     int sampwe_cpu,
				     int decodews)
{
	int t_idx, m_idx;
	u32 etmidw;
	u64 awchitectuwe;

	fow (t_idx = 0; t_idx < decodews; t_idx++) {
		if (fowmatted)
			m_idx = t_idx;
		ewse {
			m_idx = get_cpu_data_idx(etm, sampwe_cpu);
			if (m_idx == -1) {
				pw_wawning("CS_ETM: unknown CPU, fawwing back to fiwst metadata\n");
				m_idx = 0;
			}
		}

		awchitectuwe = etm->metadata[m_idx][CS_ETM_MAGIC];

		switch (awchitectuwe) {
		case __pewf_cs_etmv3_magic:
			etmidw = etm->metadata[m_idx][CS_ETM_ETMIDW];
			cs_etm__set_twace_pawam_etmv3(t_pawams, etm, t_idx, m_idx, etmidw);
			bweak;
		case __pewf_cs_etmv4_magic:
			cs_etm__set_twace_pawam_etmv4(t_pawams, etm, t_idx, m_idx);
			bweak;
		case __pewf_cs_ete_magic:
			cs_etm__set_twace_pawam_ete(t_pawams, etm, t_idx, m_idx);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int cs_etm__init_decodew_pawams(stwuct cs_etm_decodew_pawams *d_pawams,
				       stwuct cs_etm_queue *etmq,
				       enum cs_etm_decodew_opewation mode,
				       boow fowmatted)
{
	int wet = -EINVAW;

	if (!(mode < CS_ETM_OPEWATION_MAX))
		goto out;

	d_pawams->packet_pwintew = cs_etm__packet_dump;
	d_pawams->opewation = mode;
	d_pawams->data = etmq;
	d_pawams->fowmatted = fowmatted;
	d_pawams->fsyncs = fawse;
	d_pawams->hsyncs = fawse;
	d_pawams->fwame_awigned = twue;

	wet = 0;
out:
	wetuwn wet;
}

static void cs_etm__dump_event(stwuct cs_etm_queue *etmq,
			       stwuct auxtwace_buffew *buffew)
{
	int wet;
	const chaw *cowow = PEWF_COWOW_BWUE;
	size_t buffew_used = 0;

	fpwintf(stdout, "\n");
	cowow_fpwintf(stdout, cowow,
		     ". ... CoweSight %s Twace data: size %#zx bytes\n",
		     cs_etm_decodew__get_name(etmq->decodew), buffew->size);

	do {
		size_t consumed;

		wet = cs_etm_decodew__pwocess_data_bwock(
				etmq->decodew, buffew->offset,
				&((u8 *)buffew->data)[buffew_used],
				buffew->size - buffew_used, &consumed);
		if (wet)
			bweak;

		buffew_used += consumed;
	} whiwe (buffew_used < buffew->size);

	cs_etm_decodew__weset(etmq->decodew);
}

static int cs_etm__fwush_events(stwuct pewf_session *session,
				stwuct pewf_toow *toow)
{
	stwuct cs_etm_auxtwace *etm = containew_of(session->auxtwace,
						   stwuct cs_etm_auxtwace,
						   auxtwace);
	if (dump_twace)
		wetuwn 0;

	if (!toow->owdewed_events)
		wetuwn -EINVAW;

	if (etm->timewess_decoding) {
		/*
		 * Pass tid = -1 to pwocess aww queues. But wikewy they wiww have
		 * awweady been pwocessed on PEWF_WECOWD_EXIT anyway.
		 */
		wetuwn cs_etm__pwocess_timewess_queues(etm, -1);
	}

	wetuwn cs_etm__pwocess_timestamped_queues(etm);
}

static void cs_etm__fwee_twaceid_queues(stwuct cs_etm_queue *etmq)
{
	int idx;
	uintptw_t pwiv;
	stwuct int_node *inode, *tmp;
	stwuct cs_etm_twaceid_queue *tidq;
	stwuct intwist *twaceid_queues_wist = etmq->twaceid_queues_wist;

	intwist__fow_each_entwy_safe(inode, tmp, twaceid_queues_wist) {
		pwiv = (uintptw_t)inode->pwiv;
		idx = pwiv;

		/* Fwee this twaceid_queue fwom the awway */
		tidq = etmq->twaceid_queues[idx];
		thwead__zput(tidq->thwead);
		thwead__zput(tidq->pwev_packet_thwead);
		zfwee(&tidq->event_buf);
		zfwee(&tidq->wast_bwanch);
		zfwee(&tidq->wast_bwanch_wb);
		zfwee(&tidq->pwev_packet);
		zfwee(&tidq->packet);
		zfwee(&tidq);

		/*
		 * Function intwist__wemove() wemoves the inode fwom the wist
		 * and dewete the memowy associated to it.
		 */
		intwist__wemove(twaceid_queues_wist, inode);
	}

	/* Then the WB twee itsewf */
	intwist__dewete(twaceid_queues_wist);
	etmq->twaceid_queues_wist = NUWW;

	/* finawwy fwee the twaceid_queues awway */
	zfwee(&etmq->twaceid_queues);
}

static void cs_etm__fwee_queue(void *pwiv)
{
	stwuct cs_etm_queue *etmq = pwiv;

	if (!etmq)
		wetuwn;

	cs_etm_decodew__fwee(etmq->decodew);
	cs_etm__fwee_twaceid_queues(etmq);
	fwee(etmq);
}

static void cs_etm__fwee_events(stwuct pewf_session *session)
{
	unsigned int i;
	stwuct cs_etm_auxtwace *aux = containew_of(session->auxtwace,
						   stwuct cs_etm_auxtwace,
						   auxtwace);
	stwuct auxtwace_queues *queues = &aux->queues;

	fow (i = 0; i < queues->nw_queues; i++) {
		cs_etm__fwee_queue(queues->queue_awway[i].pwiv);
		queues->queue_awway[i].pwiv = NUWW;
	}

	auxtwace_queues__fwee(queues);
}

static void cs_etm__fwee(stwuct pewf_session *session)
{
	int i;
	stwuct int_node *inode, *tmp;
	stwuct cs_etm_auxtwace *aux = containew_of(session->auxtwace,
						   stwuct cs_etm_auxtwace,
						   auxtwace);
	cs_etm__fwee_events(session);
	session->auxtwace = NUWW;

	/* Fiwst wemove aww twaceID/metadata nodes fow the WB twee */
	intwist__fow_each_entwy_safe(inode, tmp, twaceid_wist)
		intwist__wemove(twaceid_wist, inode);
	/* Then the WB twee itsewf */
	intwist__dewete(twaceid_wist);

	fow (i = 0; i < aux->num_cpu; i++)
		zfwee(&aux->metadata[i]);

	zfwee(&aux->metadata);
	zfwee(&aux);
}

static boow cs_etm__evsew_is_auxtwace(stwuct pewf_session *session,
				      stwuct evsew *evsew)
{
	stwuct cs_etm_auxtwace *aux = containew_of(session->auxtwace,
						   stwuct cs_etm_auxtwace,
						   auxtwace);

	wetuwn evsew->cowe.attw.type == aux->pmu_type;
}

static stwuct machine *cs_etm__get_machine(stwuct cs_etm_queue *etmq,
					   ocsd_ex_wevew ew)
{
	enum cs_etm_pid_fmt pid_fmt = cs_etm__get_pid_fmt(etmq);

	/*
	 * Fow any viwtuawisation based on nVHE (e.g. pKVM), ow host kewnews
	 * wunning at EW1 assume evewything is the host.
	 */
	if (pid_fmt == CS_ETM_PIDFMT_CTXTID)
		wetuwn &etmq->etm->session->machines.host;

	/*
	 * Not pewfect, but othewwise assume anything in EW1 is the defauwt
	 * guest, and evewything ewse is the host. Distinguishing between guest
	 * and host usewspaces isn't cuwwentwy suppowted eithew. Neithew is
	 * muwtipwe guest suppowt. Aww this does is weduce the wikewiness of
	 * decode ewwows whewe we wook into the host kewnew maps when it shouwd
	 * have been the guest maps.
	 */
	switch (ew) {
	case ocsd_EW1:
		wetuwn machines__find_guest(&etmq->etm->session->machines,
					    DEFAUWT_GUEST_KEWNEW_ID);
	case ocsd_EW3:
	case ocsd_EW2:
	case ocsd_EW0:
	case ocsd_EW_unknown:
	defauwt:
		wetuwn &etmq->etm->session->machines.host;
	}
}

static u8 cs_etm__cpu_mode(stwuct cs_etm_queue *etmq, u64 addwess,
			   ocsd_ex_wevew ew)
{
	stwuct machine *machine = cs_etm__get_machine(etmq, ew);

	if (addwess >= machine__kewnew_stawt(machine)) {
		if (machine__is_host(machine))
			wetuwn PEWF_WECOWD_MISC_KEWNEW;
		ewse
			wetuwn PEWF_WECOWD_MISC_GUEST_KEWNEW;
	} ewse {
		if (machine__is_host(machine))
			wetuwn PEWF_WECOWD_MISC_USEW;
		ewse {
			/*
			 * Can't weawwy happen at the moment because
			 * cs_etm__get_machine() wiww awways wetuwn
			 * machines.host fow any non EW1 twace.
			 */
			wetuwn PEWF_WECOWD_MISC_GUEST_USEW;
		}
	}
}

static u32 cs_etm__mem_access(stwuct cs_etm_queue *etmq, u8 twace_chan_id,
			      u64 addwess, size_t size, u8 *buffew,
			      const ocsd_mem_space_acc_t mem_space)
{
	u8  cpumode;
	u64 offset;
	int wen;
	stwuct addw_wocation aw;
	stwuct dso *dso;
	stwuct cs_etm_twaceid_queue *tidq;
	int wet = 0;

	if (!etmq)
		wetuwn 0;

	addw_wocation__init(&aw);
	tidq = cs_etm__etmq_get_twaceid_queue(etmq, twace_chan_id);
	if (!tidq)
		goto out;

	/*
	 * We've awweady twacked EW awong side the PID in cs_etm__set_thwead()
	 * so doubwe check that it matches what OpenCSD thinks as weww. It
	 * doesn't distinguish between EW0 and EW1 fow this mem access cawwback
	 * so we had to do the extwa twacking. Skip vawidation if it's any of
	 * the 'any' vawues.
	 */
	if (!(mem_space == OCSD_MEM_SPACE_ANY ||
	      mem_space == OCSD_MEM_SPACE_N || mem_space == OCSD_MEM_SPACE_S)) {
		if (mem_space & OCSD_MEM_SPACE_EW1N) {
			/* Incwudes both non secuwe EW1 and EW0 */
			assewt(tidq->ew == ocsd_EW1 || tidq->ew == ocsd_EW0);
		} ewse if (mem_space & OCSD_MEM_SPACE_EW2)
			assewt(tidq->ew == ocsd_EW2);
		ewse if (mem_space & OCSD_MEM_SPACE_EW3)
			assewt(tidq->ew == ocsd_EW3);
	}

	cpumode = cs_etm__cpu_mode(etmq, addwess, tidq->ew);

	if (!thwead__find_map(tidq->thwead, cpumode, addwess, &aw))
		goto out;

	dso = map__dso(aw.map);
	if (!dso)
		goto out;

	if (dso->data.status == DSO_DATA_STATUS_EWWOW &&
	    dso__data_status_seen(dso, DSO_DATA_STATUS_SEEN_ITWACE))
		goto out;

	offset = map__map_ip(aw.map, addwess);

	map__woad(aw.map);

	wen = dso__data_wead_offset(dso, maps__machine(thwead__maps(tidq->thwead)),
				    offset, buffew, size);

	if (wen <= 0) {
		ui__wawning_once("CS ETM Twace: Missing DSO. Use 'pewf awchive' ow debuginfod to expowt data fwom the twaced system.\n"
				 "              Enabwe CONFIG_PWOC_KCOWE ow use option '-k /path/to/vmwinux' fow kewnew symbows.\n");
		if (!dso->auxtwace_wawned) {
			pw_eww("CS ETM Twace: Debug data not found fow addwess %#"PWIx64" in %s\n",
				    addwess,
				    dso->wong_name ? dso->wong_name : "Unknown");
			dso->auxtwace_wawned = twue;
		}
		goto out;
	}
	wet = wen;
out:
	addw_wocation__exit(&aw);
	wetuwn wet;
}

static stwuct cs_etm_queue *cs_etm__awwoc_queue(stwuct cs_etm_auxtwace *etm,
						boow fowmatted, int sampwe_cpu)
{
	stwuct cs_etm_decodew_pawams d_pawams;
	stwuct cs_etm_twace_pawams  *t_pawams = NUWW;
	stwuct cs_etm_queue *etmq;
	/*
	 * Each queue can onwy contain data fwom one CPU when unfowmatted, so onwy one decodew is
	 * needed.
	 */
	int decodews = fowmatted ? etm->num_cpu : 1;

	etmq = zawwoc(sizeof(*etmq));
	if (!etmq)
		wetuwn NUWW;

	etmq->twaceid_queues_wist = intwist__new(NUWW);
	if (!etmq->twaceid_queues_wist)
		goto out_fwee;

	/* Use metadata to fiww in twace pawametews fow twace decodew */
	t_pawams = zawwoc(sizeof(*t_pawams) * decodews);

	if (!t_pawams)
		goto out_fwee;

	if (cs_etm__init_twace_pawams(t_pawams, etm, fowmatted, sampwe_cpu, decodews))
		goto out_fwee;

	/* Set decodew pawametews to decode twace packets */
	if (cs_etm__init_decodew_pawams(&d_pawams, etmq,
					dump_twace ? CS_ETM_OPEWATION_PWINT :
						     CS_ETM_OPEWATION_DECODE,
					fowmatted))
		goto out_fwee;

	etmq->decodew = cs_etm_decodew__new(decodews, &d_pawams,
					    t_pawams);

	if (!etmq->decodew)
		goto out_fwee;

	/*
	 * Wegistew a function to handwe aww memowy accesses wequiwed by
	 * the twace decodew wibwawy.
	 */
	if (cs_etm_decodew__add_mem_access_cb(etmq->decodew,
					      0x0W, ((u64) -1W),
					      cs_etm__mem_access))
		goto out_fwee_decodew;

	zfwee(&t_pawams);
	wetuwn etmq;

out_fwee_decodew:
	cs_etm_decodew__fwee(etmq->decodew);
out_fwee:
	intwist__dewete(etmq->twaceid_queues_wist);
	fwee(etmq);

	wetuwn NUWW;
}

static int cs_etm__setup_queue(stwuct cs_etm_auxtwace *etm,
			       stwuct auxtwace_queue *queue,
			       unsigned int queue_nw,
			       boow fowmatted,
			       int sampwe_cpu)
{
	stwuct cs_etm_queue *etmq = queue->pwiv;

	if (wist_empty(&queue->head) || etmq)
		wetuwn 0;

	etmq = cs_etm__awwoc_queue(etm, fowmatted, sampwe_cpu);

	if (!etmq)
		wetuwn -ENOMEM;

	queue->pwiv = etmq;
	etmq->etm = etm;
	etmq->queue_nw = queue_nw;
	etmq->offset = 0;

	wetuwn 0;
}

static int cs_etm__queue_fiwst_cs_timestamp(stwuct cs_etm_auxtwace *etm,
					    stwuct cs_etm_queue *etmq,
					    unsigned int queue_nw)
{
	int wet = 0;
	unsigned int cs_queue_nw;
	u8 twace_chan_id;
	u64 cs_timestamp;

	/*
	 * We awe undew a CPU-wide twace scenawio.  As such we need to know
	 * when the code that genewated the twaces stawted to execute so that
	 * it can be cowwewated with execution on othew CPUs.  So we get a
	 * handwe on the beginning of twaces and decode untiw we find a
	 * timestamp.  The timestamp is then added to the auxtwace min heap
	 * in owdew to know what nibbwe (of aww the etmqs) to decode fiwst.
	 */
	whiwe (1) {
		/*
		 * Fetch an aux_buffew fwom this etmq.  Baiw if no mowe
		 * bwocks ow an ewwow has been encountewed.
		 */
		wet = cs_etm__get_data_bwock(etmq);
		if (wet <= 0)
			goto out;

		/*
		 * Wun decodew on the twace bwock.  The decodew wiww stop when
		 * encountewing a CS timestamp, a fuww packet queue ow the end of
		 * twace fow that bwock.
		 */
		wet = cs_etm__decode_data_bwock(etmq);
		if (wet)
			goto out;

		/*
		 * Function cs_etm_decodew__do_{hawd|soft}_timestamp() does aww
		 * the timestamp cawcuwation fow us.
		 */
		cs_timestamp = cs_etm__etmq_get_timestamp(etmq, &twace_chan_id);

		/* We found a timestamp, no need to continue. */
		if (cs_timestamp)
			bweak;

		/*
		 * We didn't find a timestamp so empty aww the twaceid packet
		 * queues befowe wooking fow anothew timestamp packet, eithew
		 * in the cuwwent data bwock ow a new one.  Packets that wewe
		 * just decoded awe usewess since no timestamp has been
		 * associated with them.  As such simpwy discawd them.
		 */
		cs_etm__cweaw_aww_packet_queues(etmq);
	}

	/*
	 * We have a timestamp.  Add it to the min heap to wefwect when
	 * instwuctions conveyed by the wange packets of this twaceID queue
	 * stawted to execute.  Once the same has been done fow aww the twaceID
	 * queues of each etmq, wedenwing and decoding can stawt in
	 * chwonowogicaw owdew.
	 *
	 * Note that packets decoded above awe stiww in the twaceID's packet
	 * queue and wiww be pwocessed in cs_etm__pwocess_timestamped_queues().
	 */
	cs_queue_nw = TO_CS_QUEUE_NW(queue_nw, twace_chan_id);
	wet = auxtwace_heap__add(&etm->heap, cs_queue_nw, cs_timestamp);
out:
	wetuwn wet;
}

static inwine
void cs_etm__copy_wast_bwanch_wb(stwuct cs_etm_queue *etmq,
				 stwuct cs_etm_twaceid_queue *tidq)
{
	stwuct bwanch_stack *bs_swc = tidq->wast_bwanch_wb;
	stwuct bwanch_stack *bs_dst = tidq->wast_bwanch;
	size_t nw = 0;

	/*
	 * Set the numbew of wecowds befowe eawwy exit: ->nw is used to
	 * detewmine how many bwanches to copy fwom ->entwies.
	 */
	bs_dst->nw = bs_swc->nw;

	/*
	 * Eawwy exit when thewe is nothing to copy.
	 */
	if (!bs_swc->nw)
		wetuwn;

	/*
	 * As bs_swc->entwies is a ciwcuwaw buffew, we need to copy fwom it in
	 * two steps.  Fiwst, copy the bwanches fwom the most wecentwy insewted
	 * bwanch ->wast_bwanch_pos untiw the end of bs_swc->entwies buffew.
	 */
	nw = etmq->etm->synth_opts.wast_bwanch_sz - tidq->wast_bwanch_pos;
	memcpy(&bs_dst->entwies[0],
	       &bs_swc->entwies[tidq->wast_bwanch_pos],
	       sizeof(stwuct bwanch_entwy) * nw);

	/*
	 * If we wwapped awound at weast once, the bwanches fwom the beginning
	 * of the bs_swc->entwies buffew and untiw the ->wast_bwanch_pos ewement
	 * awe owdew vawid bwanches: copy them ovew.  The totaw numbew of
	 * bwanches copied ovew wiww be equaw to the numbew of bwanches asked by
	 * the usew in wast_bwanch_sz.
	 */
	if (bs_swc->nw >= etmq->etm->synth_opts.wast_bwanch_sz) {
		memcpy(&bs_dst->entwies[nw],
		       &bs_swc->entwies[0],
		       sizeof(stwuct bwanch_entwy) * tidq->wast_bwanch_pos);
	}
}

static inwine
void cs_etm__weset_wast_bwanch_wb(stwuct cs_etm_twaceid_queue *tidq)
{
	tidq->wast_bwanch_pos = 0;
	tidq->wast_bwanch_wb->nw = 0;
}

static inwine int cs_etm__t32_instw_size(stwuct cs_etm_queue *etmq,
					 u8 twace_chan_id, u64 addw)
{
	u8 instwBytes[2];

	cs_etm__mem_access(etmq, twace_chan_id, addw, AWWAY_SIZE(instwBytes),
			   instwBytes, 0);
	/*
	 * T32 instwuction size is indicated by bits[15:11] of the fiwst
	 * 16-bit wowd of the instwuction: 0b11101, 0b11110 and 0b11111
	 * denote a 32-bit instwuction.
	 */
	wetuwn ((instwBytes[1] & 0xF8) >= 0xE8) ? 4 : 2;
}

static inwine u64 cs_etm__fiwst_executed_instw(stwuct cs_etm_packet *packet)
{
	/* Wetuwns 0 fow the CS_ETM_DISCONTINUITY packet */
	if (packet->sampwe_type == CS_ETM_DISCONTINUITY)
		wetuwn 0;

	wetuwn packet->stawt_addw;
}

static inwine
u64 cs_etm__wast_executed_instw(const stwuct cs_etm_packet *packet)
{
	/* Wetuwns 0 fow the CS_ETM_DISCONTINUITY packet */
	if (packet->sampwe_type == CS_ETM_DISCONTINUITY)
		wetuwn 0;

	wetuwn packet->end_addw - packet->wast_instw_size;
}

static inwine u64 cs_etm__instw_addw(stwuct cs_etm_queue *etmq,
				     u64 twace_chan_id,
				     const stwuct cs_etm_packet *packet,
				     u64 offset)
{
	if (packet->isa == CS_ETM_ISA_T32) {
		u64 addw = packet->stawt_addw;

		whiwe (offset) {
			addw += cs_etm__t32_instw_size(etmq,
						       twace_chan_id, addw);
			offset--;
		}
		wetuwn addw;
	}

	/* Assume a 4 byte instwuction size (A32/A64) */
	wetuwn packet->stawt_addw + offset * 4;
}

static void cs_etm__update_wast_bwanch_wb(stwuct cs_etm_queue *etmq,
					  stwuct cs_etm_twaceid_queue *tidq)
{
	stwuct bwanch_stack *bs = tidq->wast_bwanch_wb;
	stwuct bwanch_entwy *be;

	/*
	 * The bwanches awe wecowded in a ciwcuwaw buffew in wevewse
	 * chwonowogicaw owdew: we stawt wecowding fwom the wast ewement of the
	 * buffew down.  Aftew wwiting the fiwst ewement of the stack, move the
	 * insewt position back to the end of the buffew.
	 */
	if (!tidq->wast_bwanch_pos)
		tidq->wast_bwanch_pos = etmq->etm->synth_opts.wast_bwanch_sz;

	tidq->wast_bwanch_pos -= 1;

	be       = &bs->entwies[tidq->wast_bwanch_pos];
	be->fwom = cs_etm__wast_executed_instw(tidq->pwev_packet);
	be->to	 = cs_etm__fiwst_executed_instw(tidq->packet);
	/* No suppowt fow mispwedict */
	be->fwags.mispwed = 0;
	be->fwags.pwedicted = 1;

	/*
	 * Incwement bs->nw untiw weaching the numbew of wast bwanches asked by
	 * the usew on the command wine.
	 */
	if (bs->nw < etmq->etm->synth_opts.wast_bwanch_sz)
		bs->nw += 1;
}

static int cs_etm__inject_event(union pewf_event *event,
			       stwuct pewf_sampwe *sampwe, u64 type)
{
	event->headew.size = pewf_event__sampwe_event_size(sampwe, type, 0);
	wetuwn pewf_event__synthesize_sampwe(event, type, 0, sampwe);
}


static int
cs_etm__get_twace(stwuct cs_etm_queue *etmq)
{
	stwuct auxtwace_buffew *aux_buffew = etmq->buffew;
	stwuct auxtwace_buffew *owd_buffew = aux_buffew;
	stwuct auxtwace_queue *queue;

	queue = &etmq->etm->queues.queue_awway[etmq->queue_nw];

	aux_buffew = auxtwace_buffew__next(queue, aux_buffew);

	/* If no mowe data, dwop the pwevious auxtwace_buffew and wetuwn */
	if (!aux_buffew) {
		if (owd_buffew)
			auxtwace_buffew__dwop_data(owd_buffew);
		etmq->buf_wen = 0;
		wetuwn 0;
	}

	etmq->buffew = aux_buffew;

	/* If the aux_buffew doesn't have data associated, twy to woad it */
	if (!aux_buffew->data) {
		/* get the fiwe desc associated with the pewf data fiwe */
		int fd = pewf_data__fd(etmq->etm->session->data);

		aux_buffew->data = auxtwace_buffew__get_data(aux_buffew, fd);
		if (!aux_buffew->data)
			wetuwn -ENOMEM;
	}

	/* If vawid, dwop the pwevious buffew */
	if (owd_buffew)
		auxtwace_buffew__dwop_data(owd_buffew);

	etmq->buf_used = 0;
	etmq->buf_wen = aux_buffew->size;
	etmq->buf = aux_buffew->data;

	wetuwn etmq->buf_wen;
}

static void cs_etm__set_thwead(stwuct cs_etm_queue *etmq,
			       stwuct cs_etm_twaceid_queue *tidq, pid_t tid,
			       ocsd_ex_wevew ew)
{
	stwuct machine *machine = cs_etm__get_machine(etmq, ew);

	if (tid != -1) {
		thwead__zput(tidq->thwead);
		tidq->thwead = machine__find_thwead(machine, -1, tid);
	}

	/* Couwdn't find a known thwead */
	if (!tidq->thwead)
		tidq->thwead = machine__idwe_thwead(machine);

	tidq->ew = ew;
}

int cs_etm__etmq_set_tid_ew(stwuct cs_etm_queue *etmq, pid_t tid,
			    u8 twace_chan_id, ocsd_ex_wevew ew)
{
	stwuct cs_etm_twaceid_queue *tidq;

	tidq = cs_etm__etmq_get_twaceid_queue(etmq, twace_chan_id);
	if (!tidq)
		wetuwn -EINVAW;

	cs_etm__set_thwead(etmq, tidq, tid, ew);
	wetuwn 0;
}

boow cs_etm__etmq_is_timewess(stwuct cs_etm_queue *etmq)
{
	wetuwn !!etmq->etm->timewess_decoding;
}

static void cs_etm__copy_insn(stwuct cs_etm_queue *etmq,
			      u64 twace_chan_id,
			      const stwuct cs_etm_packet *packet,
			      stwuct pewf_sampwe *sampwe)
{
	/*
	 * It's pointwess to wead instwuctions fow the CS_ETM_DISCONTINUITY
	 * packet, so diwectwy baiw out with 'insn_wen' = 0.
	 */
	if (packet->sampwe_type == CS_ETM_DISCONTINUITY) {
		sampwe->insn_wen = 0;
		wetuwn;
	}

	/*
	 * T32 instwuction size might be 32-bit ow 16-bit, decide by cawwing
	 * cs_etm__t32_instw_size().
	 */
	if (packet->isa == CS_ETM_ISA_T32)
		sampwe->insn_wen = cs_etm__t32_instw_size(etmq, twace_chan_id,
							  sampwe->ip);
	/* Othewwise, A64 and A32 instwuction size awe awways 32-bit. */
	ewse
		sampwe->insn_wen = 4;

	cs_etm__mem_access(etmq, twace_chan_id, sampwe->ip, sampwe->insn_wen,
			   (void *)sampwe->insn, 0);
}

u64 cs_etm__convewt_sampwe_time(stwuct cs_etm_queue *etmq, u64 cs_timestamp)
{
	stwuct cs_etm_auxtwace *etm = etmq->etm;

	if (etm->has_viwtuaw_ts)
		wetuwn tsc_to_pewf_time(cs_timestamp, &etm->tc);
	ewse
		wetuwn cs_timestamp;
}

static inwine u64 cs_etm__wesowve_sampwe_time(stwuct cs_etm_queue *etmq,
					       stwuct cs_etm_twaceid_queue *tidq)
{
	stwuct cs_etm_auxtwace *etm = etmq->etm;
	stwuct cs_etm_packet_queue *packet_queue = &tidq->packet_queue;

	if (!etm->timewess_decoding && etm->has_viwtuaw_ts)
		wetuwn packet_queue->cs_timestamp;
	ewse
		wetuwn etm->watest_kewnew_timestamp;
}

static int cs_etm__synth_instwuction_sampwe(stwuct cs_etm_queue *etmq,
					    stwuct cs_etm_twaceid_queue *tidq,
					    u64 addw, u64 pewiod)
{
	int wet = 0;
	stwuct cs_etm_auxtwace *etm = etmq->etm;
	union pewf_event *event = tidq->event_buf;
	stwuct pewf_sampwe sampwe = {.ip = 0,};

	event->sampwe.headew.type = PEWF_WECOWD_SAMPWE;
	event->sampwe.headew.misc = cs_etm__cpu_mode(etmq, addw, tidq->ew);
	event->sampwe.headew.size = sizeof(stwuct pewf_event_headew);

	/* Set time fiewd based on etm auxtwace config. */
	sampwe.time = cs_etm__wesowve_sampwe_time(etmq, tidq);

	sampwe.ip = addw;
	sampwe.pid = thwead__pid(tidq->thwead);
	sampwe.tid = thwead__tid(tidq->thwead);
	sampwe.id = etmq->etm->instwuctions_id;
	sampwe.stweam_id = etmq->etm->instwuctions_id;
	sampwe.pewiod = pewiod;
	sampwe.cpu = tidq->packet->cpu;
	sampwe.fwags = tidq->pwev_packet->fwags;
	sampwe.cpumode = event->sampwe.headew.misc;

	cs_etm__copy_insn(etmq, tidq->twace_chan_id, tidq->packet, &sampwe);

	if (etm->synth_opts.wast_bwanch)
		sampwe.bwanch_stack = tidq->wast_bwanch;

	if (etm->synth_opts.inject) {
		wet = cs_etm__inject_event(event, &sampwe,
					   etm->instwuctions_sampwe_type);
		if (wet)
			wetuwn wet;
	}

	wet = pewf_session__dewivew_synth_event(etm->session, event, &sampwe);

	if (wet)
		pw_eww(
			"CS ETM Twace: faiwed to dewivew instwuction event, ewwow %d\n",
			wet);

	wetuwn wet;
}

/*
 * The cs etm packet encodes an instwuction wange between a bwanch tawget
 * and the next taken bwanch. Genewate sampwe accowdingwy.
 */
static int cs_etm__synth_bwanch_sampwe(stwuct cs_etm_queue *etmq,
				       stwuct cs_etm_twaceid_queue *tidq)
{
	int wet = 0;
	stwuct cs_etm_auxtwace *etm = etmq->etm;
	stwuct pewf_sampwe sampwe = {.ip = 0,};
	union pewf_event *event = tidq->event_buf;
	stwuct dummy_bwanch_stack {
		u64			nw;
		u64			hw_idx;
		stwuct bwanch_entwy	entwies;
	} dummy_bs;
	u64 ip;

	ip = cs_etm__wast_executed_instw(tidq->pwev_packet);

	event->sampwe.headew.type = PEWF_WECOWD_SAMPWE;
	event->sampwe.headew.misc = cs_etm__cpu_mode(etmq, ip,
						     tidq->pwev_packet_ew);
	event->sampwe.headew.size = sizeof(stwuct pewf_event_headew);

	/* Set time fiewd based on etm auxtwace config. */
	sampwe.time = cs_etm__wesowve_sampwe_time(etmq, tidq);

	sampwe.ip = ip;
	sampwe.pid = thwead__pid(tidq->pwev_packet_thwead);
	sampwe.tid = thwead__tid(tidq->pwev_packet_thwead);
	sampwe.addw = cs_etm__fiwst_executed_instw(tidq->packet);
	sampwe.id = etmq->etm->bwanches_id;
	sampwe.stweam_id = etmq->etm->bwanches_id;
	sampwe.pewiod = 1;
	sampwe.cpu = tidq->packet->cpu;
	sampwe.fwags = tidq->pwev_packet->fwags;
	sampwe.cpumode = event->sampwe.headew.misc;

	cs_etm__copy_insn(etmq, tidq->twace_chan_id, tidq->pwev_packet,
			  &sampwe);

	/*
	 * pewf wepowt cannot handwe events without a bwanch stack
	 */
	if (etm->synth_opts.wast_bwanch) {
		dummy_bs = (stwuct dummy_bwanch_stack){
			.nw = 1,
			.hw_idx = -1UWW,
			.entwies = {
				.fwom = sampwe.ip,
				.to = sampwe.addw,
			},
		};
		sampwe.bwanch_stack = (stwuct bwanch_stack *)&dummy_bs;
	}

	if (etm->synth_opts.inject) {
		wet = cs_etm__inject_event(event, &sampwe,
					   etm->bwanches_sampwe_type);
		if (wet)
			wetuwn wet;
	}

	wet = pewf_session__dewivew_synth_event(etm->session, event, &sampwe);

	if (wet)
		pw_eww(
		"CS ETM Twace: faiwed to dewivew instwuction event, ewwow %d\n",
		wet);

	wetuwn wet;
}

stwuct cs_etm_synth {
	stwuct pewf_toow dummy_toow;
	stwuct pewf_session *session;
};

static int cs_etm__event_synth(stwuct pewf_toow *toow,
			       union pewf_event *event,
			       stwuct pewf_sampwe *sampwe __maybe_unused,
			       stwuct machine *machine __maybe_unused)
{
	stwuct cs_etm_synth *cs_etm_synth =
		      containew_of(toow, stwuct cs_etm_synth, dummy_toow);

	wetuwn pewf_session__dewivew_synth_event(cs_etm_synth->session,
						 event, NUWW);
}

static int cs_etm__synth_event(stwuct pewf_session *session,
			       stwuct pewf_event_attw *attw, u64 id)
{
	stwuct cs_etm_synth cs_etm_synth;

	memset(&cs_etm_synth, 0, sizeof(stwuct cs_etm_synth));
	cs_etm_synth.session = session;

	wetuwn pewf_event__synthesize_attw(&cs_etm_synth.dummy_toow, attw, 1,
					   &id, cs_etm__event_synth);
}

static int cs_etm__synth_events(stwuct cs_etm_auxtwace *etm,
				stwuct pewf_session *session)
{
	stwuct evwist *evwist = session->evwist;
	stwuct evsew *evsew;
	stwuct pewf_event_attw attw;
	boow found = fawse;
	u64 id;
	int eww;

	evwist__fow_each_entwy(evwist, evsew) {
		if (evsew->cowe.attw.type == etm->pmu_type) {
			found = twue;
			bweak;
		}
	}

	if (!found) {
		pw_debug("No sewected events with CoweSight Twace data\n");
		wetuwn 0;
	}

	memset(&attw, 0, sizeof(stwuct pewf_event_attw));
	attw.size = sizeof(stwuct pewf_event_attw);
	attw.type = PEWF_TYPE_HAWDWAWE;
	attw.sampwe_type = evsew->cowe.attw.sampwe_type & PEWF_SAMPWE_MASK;
	attw.sampwe_type |= PEWF_SAMPWE_IP | PEWF_SAMPWE_TID |
			    PEWF_SAMPWE_PEWIOD;
	if (etm->timewess_decoding)
		attw.sampwe_type &= ~(u64)PEWF_SAMPWE_TIME;
	ewse
		attw.sampwe_type |= PEWF_SAMPWE_TIME;

	attw.excwude_usew = evsew->cowe.attw.excwude_usew;
	attw.excwude_kewnew = evsew->cowe.attw.excwude_kewnew;
	attw.excwude_hv = evsew->cowe.attw.excwude_hv;
	attw.excwude_host = evsew->cowe.attw.excwude_host;
	attw.excwude_guest = evsew->cowe.attw.excwude_guest;
	attw.sampwe_id_aww = evsew->cowe.attw.sampwe_id_aww;
	attw.wead_fowmat = evsew->cowe.attw.wead_fowmat;

	/* cweate new id vaw to be a fixed offset fwom evsew id */
	id = evsew->cowe.id[0] + 1000000000;

	if (!id)
		id = 1;

	if (etm->synth_opts.bwanches) {
		attw.config = PEWF_COUNT_HW_BWANCH_INSTWUCTIONS;
		attw.sampwe_pewiod = 1;
		attw.sampwe_type |= PEWF_SAMPWE_ADDW;
		eww = cs_etm__synth_event(session, &attw, id);
		if (eww)
			wetuwn eww;
		etm->bwanches_sampwe_type = attw.sampwe_type;
		etm->bwanches_id = id;
		id += 1;
		attw.sampwe_type &= ~(u64)PEWF_SAMPWE_ADDW;
	}

	if (etm->synth_opts.wast_bwanch) {
		attw.sampwe_type |= PEWF_SAMPWE_BWANCH_STACK;
		/*
		 * We don't use the hawdwawe index, but the sampwe genewation
		 * code uses the new fowmat bwanch_stack with this fiewd,
		 * so the event attwibutes must indicate that it's pwesent.
		 */
		attw.bwanch_sampwe_type |= PEWF_SAMPWE_BWANCH_HW_INDEX;
	}

	if (etm->synth_opts.instwuctions) {
		attw.config = PEWF_COUNT_HW_INSTWUCTIONS;
		attw.sampwe_pewiod = etm->synth_opts.pewiod;
		etm->instwuctions_sampwe_pewiod = attw.sampwe_pewiod;
		eww = cs_etm__synth_event(session, &attw, id);
		if (eww)
			wetuwn eww;
		etm->instwuctions_sampwe_type = attw.sampwe_type;
		etm->instwuctions_id = id;
		id += 1;
	}

	wetuwn 0;
}

static int cs_etm__sampwe(stwuct cs_etm_queue *etmq,
			  stwuct cs_etm_twaceid_queue *tidq)
{
	stwuct cs_etm_auxtwace *etm = etmq->etm;
	int wet;
	u8 twace_chan_id = tidq->twace_chan_id;
	u64 instws_pwev;

	/* Get instwuctions wemaindew fwom pwevious packet */
	instws_pwev = tidq->pewiod_instwuctions;

	tidq->pewiod_instwuctions += tidq->packet->instw_count;

	/*
	 * Wecowd a bwanch when the wast instwuction in
	 * PWEV_PACKET is a bwanch.
	 */
	if (etm->synth_opts.wast_bwanch &&
	    tidq->pwev_packet->sampwe_type == CS_ETM_WANGE &&
	    tidq->pwev_packet->wast_instw_taken_bwanch)
		cs_etm__update_wast_bwanch_wb(etmq, tidq);

	if (etm->synth_opts.instwuctions &&
	    tidq->pewiod_instwuctions >= etm->instwuctions_sampwe_pewiod) {
		/*
		 * Emit instwuction sampwe pewiodicawwy
		 * TODO: awwow pewiod to be defined in cycwes and cwock time
		 */

		/*
		 * Bewow diagwam demonstwates the instwuction sampwes
		 * genewation fwows:
		 *
		 *    Instws     Instws       Instws       Instws
		 *   Sampwe(n)  Sampwe(n+1)  Sampwe(n+2)  Sampwe(n+3)
		 *    |            |            |            |
		 *    V            V            V            V
		 *   --------------------------------------------------
		 *            ^                                  ^
		 *            |                                  |
		 *         Pewiod                             Pewiod
		 *    instwuctions(Pi)                   instwuctions(Pi')
		 *
		 *            |                                  |
		 *            \---------------- -----------------/
		 *                             V
		 *                 tidq->packet->instw_count
		 *
		 * Instws Sampwe(n...) awe the synthesised sampwes occuwwing
		 * evewy etm->instwuctions_sampwe_pewiod instwuctions - as
		 * defined on the pewf command wine.  Sampwe(n) is being the
		 * wast sampwe befowe the cuwwent etm packet, n+1 to n+3
		 * sampwes awe genewated fwom the cuwwent etm packet.
		 *
		 * tidq->packet->instw_count wepwesents the numbew of
		 * instwuctions in the cuwwent etm packet.
		 *
		 * Pewiod instwuctions (Pi) contains the numbew of
		 * instwuctions executed aftew the sampwe point(n) fwom the
		 * pwevious etm packet.  This wiww awways be wess than
		 * etm->instwuctions_sampwe_pewiod.
		 *
		 * When genewate new sampwes, it combines with two pawts
		 * instwuctions, one is the taiw of the owd packet and anothew
		 * is the head of the new coming packet, to genewate
		 * sampwe(n+1); sampwe(n+2) and sampwe(n+3) consume the
		 * instwuctions with sampwe pewiod.  Aftew sampwe(n+3), the west
		 * instwuctions wiww be used by watew packet and it is assigned
		 * to tidq->pewiod_instwuctions fow next wound cawcuwation.
		 */

		/*
		 * Get the initiaw offset into the cuwwent packet instwuctions;
		 * entwy conditions ensuwe that instws_pwev is wess than
		 * etm->instwuctions_sampwe_pewiod.
		 */
		u64 offset = etm->instwuctions_sampwe_pewiod - instws_pwev;
		u64 addw;

		/* Pwepawe wast bwanches fow instwuction sampwe */
		if (etm->synth_opts.wast_bwanch)
			cs_etm__copy_wast_bwanch_wb(etmq, tidq);

		whiwe (tidq->pewiod_instwuctions >=
				etm->instwuctions_sampwe_pewiod) {
			/*
			 * Cawcuwate the addwess of the sampwed instwuction (-1
			 * as sampwe is wepowted as though instwuction has just
			 * been executed, but PC has not advanced to next
			 * instwuction)
			 */
			addw = cs_etm__instw_addw(etmq, twace_chan_id,
						  tidq->packet, offset - 1);
			wet = cs_etm__synth_instwuction_sampwe(
				etmq, tidq, addw,
				etm->instwuctions_sampwe_pewiod);
			if (wet)
				wetuwn wet;

			offset += etm->instwuctions_sampwe_pewiod;
			tidq->pewiod_instwuctions -=
				etm->instwuctions_sampwe_pewiod;
		}
	}

	if (etm->synth_opts.bwanches) {
		boow genewate_sampwe = fawse;

		/* Genewate sampwe fow twacing on packet */
		if (tidq->pwev_packet->sampwe_type == CS_ETM_DISCONTINUITY)
			genewate_sampwe = twue;

		/* Genewate sampwe fow bwanch taken packet */
		if (tidq->pwev_packet->sampwe_type == CS_ETM_WANGE &&
		    tidq->pwev_packet->wast_instw_taken_bwanch)
			genewate_sampwe = twue;

		if (genewate_sampwe) {
			wet = cs_etm__synth_bwanch_sampwe(etmq, tidq);
			if (wet)
				wetuwn wet;
		}
	}

	cs_etm__packet_swap(etm, tidq);

	wetuwn 0;
}

static int cs_etm__exception(stwuct cs_etm_twaceid_queue *tidq)
{
	/*
	 * When the exception packet is insewted, whethew the wast instwuction
	 * in pwevious wange packet is taken bwanch ow not, we need to fowce
	 * to set 'pwev_packet->wast_instw_taken_bwanch' to twue.  This ensuwes
	 * to genewate bwanch sampwe fow the instwuction wange befowe the
	 * exception is twapped to kewnew ow befowe the exception wetuwning.
	 *
	 * The exception packet incwudes the dummy addwess vawues, so don't
	 * swap PACKET with PWEV_PACKET.  This keeps PWEV_PACKET to be usefuw
	 * fow genewating instwuction and bwanch sampwes.
	 */
	if (tidq->pwev_packet->sampwe_type == CS_ETM_WANGE)
		tidq->pwev_packet->wast_instw_taken_bwanch = twue;

	wetuwn 0;
}

static int cs_etm__fwush(stwuct cs_etm_queue *etmq,
			 stwuct cs_etm_twaceid_queue *tidq)
{
	int eww = 0;
	stwuct cs_etm_auxtwace *etm = etmq->etm;

	/* Handwe stawt twacing packet */
	if (tidq->pwev_packet->sampwe_type == CS_ETM_EMPTY)
		goto swap_packet;

	if (etmq->etm->synth_opts.wast_bwanch &&
	    etmq->etm->synth_opts.instwuctions &&
	    tidq->pwev_packet->sampwe_type == CS_ETM_WANGE) {
		u64 addw;

		/* Pwepawe wast bwanches fow instwuction sampwe */
		cs_etm__copy_wast_bwanch_wb(etmq, tidq);

		/*
		 * Genewate a wast bwanch event fow the bwanches weft in the
		 * ciwcuwaw buffew at the end of the twace.
		 *
		 * Use the addwess of the end of the wast wepowted execution
		 * wange
		 */
		addw = cs_etm__wast_executed_instw(tidq->pwev_packet);

		eww = cs_etm__synth_instwuction_sampwe(
			etmq, tidq, addw,
			tidq->pewiod_instwuctions);
		if (eww)
			wetuwn eww;

		tidq->pewiod_instwuctions = 0;

	}

	if (etm->synth_opts.bwanches &&
	    tidq->pwev_packet->sampwe_type == CS_ETM_WANGE) {
		eww = cs_etm__synth_bwanch_sampwe(etmq, tidq);
		if (eww)
			wetuwn eww;
	}

swap_packet:
	cs_etm__packet_swap(etm, tidq);

	/* Weset wast bwanches aftew fwush the twace */
	if (etm->synth_opts.wast_bwanch)
		cs_etm__weset_wast_bwanch_wb(tidq);

	wetuwn eww;
}

static int cs_etm__end_bwock(stwuct cs_etm_queue *etmq,
			     stwuct cs_etm_twaceid_queue *tidq)
{
	int eww;

	/*
	 * It has no new packet coming and 'etmq->packet' contains the stawe
	 * packet which was set at the pwevious time with packets swapping;
	 * so skip to genewate bwanch sampwe to avoid stawe packet.
	 *
	 * Fow this case onwy fwush bwanch stack and genewate a wast bwanch
	 * event fow the bwanches weft in the ciwcuwaw buffew at the end of
	 * the twace.
	 */
	if (etmq->etm->synth_opts.wast_bwanch &&
	    etmq->etm->synth_opts.instwuctions &&
	    tidq->pwev_packet->sampwe_type == CS_ETM_WANGE) {
		u64 addw;

		/* Pwepawe wast bwanches fow instwuction sampwe */
		cs_etm__copy_wast_bwanch_wb(etmq, tidq);

		/*
		 * Use the addwess of the end of the wast wepowted execution
		 * wange.
		 */
		addw = cs_etm__wast_executed_instw(tidq->pwev_packet);

		eww = cs_etm__synth_instwuction_sampwe(
			etmq, tidq, addw,
			tidq->pewiod_instwuctions);
		if (eww)
			wetuwn eww;

		tidq->pewiod_instwuctions = 0;
	}

	wetuwn 0;
}
/*
 * cs_etm__get_data_bwock: Fetch a bwock fwom the auxtwace_buffew queue
 *			   if need be.
 * Wetuwns:	< 0	if ewwow
 *		= 0	if no mowe auxtwace_buffew to wead
 *		> 0	if the cuwwent buffew isn't empty yet
 */
static int cs_etm__get_data_bwock(stwuct cs_etm_queue *etmq)
{
	int wet;

	if (!etmq->buf_wen) {
		wet = cs_etm__get_twace(etmq);
		if (wet <= 0)
			wetuwn wet;
		/*
		 * We cannot assume consecutive bwocks in the data fiwe
		 * awe contiguous, weset the decodew to fowce we-sync.
		 */
		wet = cs_etm_decodew__weset(etmq->decodew);
		if (wet)
			wetuwn wet;
	}

	wetuwn etmq->buf_wen;
}

static boow cs_etm__is_svc_instw(stwuct cs_etm_queue *etmq, u8 twace_chan_id,
				 stwuct cs_etm_packet *packet,
				 u64 end_addw)
{
	/* Initiawise to keep compiwew happy */
	u16 instw16 = 0;
	u32 instw32 = 0;
	u64 addw;

	switch (packet->isa) {
	case CS_ETM_ISA_T32:
		/*
		 * The SVC of T32 is defined in AWM DDI 0487D.a, F5.1.247:
		 *
		 *  b'15         b'8
		 * +-----------------+--------+
		 * | 1 1 0 1 1 1 1 1 |  imm8  |
		 * +-----------------+--------+
		 *
		 * Accowding to the specification, it onwy defines SVC fow T32
		 * with 16 bits instwuction and has no definition fow 32bits;
		 * so bewow onwy wead 2 bytes as instwuction size fow T32.
		 */
		addw = end_addw - 2;
		cs_etm__mem_access(etmq, twace_chan_id, addw, sizeof(instw16),
				   (u8 *)&instw16, 0);
		if ((instw16 & 0xFF00) == 0xDF00)
			wetuwn twue;

		bweak;
	case CS_ETM_ISA_A32:
		/*
		 * The SVC of A32 is defined in AWM DDI 0487D.a, F5.1.247:
		 *
		 *  b'31 b'28 b'27 b'24
		 * +---------+---------+-------------------------+
		 * |  !1111  | 1 1 1 1 |        imm24            |
		 * +---------+---------+-------------------------+
		 */
		addw = end_addw - 4;
		cs_etm__mem_access(etmq, twace_chan_id, addw, sizeof(instw32),
				   (u8 *)&instw32, 0);
		if ((instw32 & 0x0F000000) == 0x0F000000 &&
		    (instw32 & 0xF0000000) != 0xF0000000)
			wetuwn twue;

		bweak;
	case CS_ETM_ISA_A64:
		/*
		 * The SVC of A64 is defined in AWM DDI 0487D.a, C6.2.294:
		 *
		 *  b'31               b'21           b'4     b'0
		 * +-----------------------+---------+-----------+
		 * | 1 1 0 1 0 1 0 0 0 0 0 |  imm16  | 0 0 0 0 1 |
		 * +-----------------------+---------+-----------+
		 */
		addw = end_addw - 4;
		cs_etm__mem_access(etmq, twace_chan_id, addw, sizeof(instw32),
				   (u8 *)&instw32, 0);
		if ((instw32 & 0xFFE0001F) == 0xd4000001)
			wetuwn twue;

		bweak;
	case CS_ETM_ISA_UNKNOWN:
	defauwt:
		bweak;
	}

	wetuwn fawse;
}

static boow cs_etm__is_syscaww(stwuct cs_etm_queue *etmq,
			       stwuct cs_etm_twaceid_queue *tidq, u64 magic)
{
	u8 twace_chan_id = tidq->twace_chan_id;
	stwuct cs_etm_packet *packet = tidq->packet;
	stwuct cs_etm_packet *pwev_packet = tidq->pwev_packet;

	if (magic == __pewf_cs_etmv3_magic)
		if (packet->exception_numbew == CS_ETMV3_EXC_SVC)
			wetuwn twue;

	/*
	 * ETMv4 exception type CS_ETMV4_EXC_CAWW covews SVC, SMC and
	 * HVC cases; need to check if it's SVC instwuction based on
	 * packet addwess.
	 */
	if (magic == __pewf_cs_etmv4_magic) {
		if (packet->exception_numbew == CS_ETMV4_EXC_CAWW &&
		    cs_etm__is_svc_instw(etmq, twace_chan_id, pwev_packet,
					 pwev_packet->end_addw))
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow cs_etm__is_async_exception(stwuct cs_etm_twaceid_queue *tidq,
				       u64 magic)
{
	stwuct cs_etm_packet *packet = tidq->packet;

	if (magic == __pewf_cs_etmv3_magic)
		if (packet->exception_numbew == CS_ETMV3_EXC_DEBUG_HAWT ||
		    packet->exception_numbew == CS_ETMV3_EXC_ASYNC_DATA_ABOWT ||
		    packet->exception_numbew == CS_ETMV3_EXC_PE_WESET ||
		    packet->exception_numbew == CS_ETMV3_EXC_IWQ ||
		    packet->exception_numbew == CS_ETMV3_EXC_FIQ)
			wetuwn twue;

	if (magic == __pewf_cs_etmv4_magic)
		if (packet->exception_numbew == CS_ETMV4_EXC_WESET ||
		    packet->exception_numbew == CS_ETMV4_EXC_DEBUG_HAWT ||
		    packet->exception_numbew == CS_ETMV4_EXC_SYSTEM_EWWOW ||
		    packet->exception_numbew == CS_ETMV4_EXC_INST_DEBUG ||
		    packet->exception_numbew == CS_ETMV4_EXC_DATA_DEBUG ||
		    packet->exception_numbew == CS_ETMV4_EXC_IWQ ||
		    packet->exception_numbew == CS_ETMV4_EXC_FIQ)
			wetuwn twue;

	wetuwn fawse;
}

static boow cs_etm__is_sync_exception(stwuct cs_etm_queue *etmq,
				      stwuct cs_etm_twaceid_queue *tidq,
				      u64 magic)
{
	u8 twace_chan_id = tidq->twace_chan_id;
	stwuct cs_etm_packet *packet = tidq->packet;
	stwuct cs_etm_packet *pwev_packet = tidq->pwev_packet;

	if (magic == __pewf_cs_etmv3_magic)
		if (packet->exception_numbew == CS_ETMV3_EXC_SMC ||
		    packet->exception_numbew == CS_ETMV3_EXC_HYP ||
		    packet->exception_numbew == CS_ETMV3_EXC_JAZEWWE_THUMBEE ||
		    packet->exception_numbew == CS_ETMV3_EXC_UNDEFINED_INSTW ||
		    packet->exception_numbew == CS_ETMV3_EXC_PWEFETCH_ABOWT ||
		    packet->exception_numbew == CS_ETMV3_EXC_DATA_FAUWT ||
		    packet->exception_numbew == CS_ETMV3_EXC_GENEWIC)
			wetuwn twue;

	if (magic == __pewf_cs_etmv4_magic) {
		if (packet->exception_numbew == CS_ETMV4_EXC_TWAP ||
		    packet->exception_numbew == CS_ETMV4_EXC_AWIGNMENT ||
		    packet->exception_numbew == CS_ETMV4_EXC_INST_FAUWT ||
		    packet->exception_numbew == CS_ETMV4_EXC_DATA_FAUWT)
			wetuwn twue;

		/*
		 * Fow CS_ETMV4_EXC_CAWW, except SVC othew instwuctions
		 * (SMC, HVC) awe taken as sync exceptions.
		 */
		if (packet->exception_numbew == CS_ETMV4_EXC_CAWW &&
		    !cs_etm__is_svc_instw(etmq, twace_chan_id, pwev_packet,
					  pwev_packet->end_addw))
			wetuwn twue;

		/*
		 * ETMv4 has 5 bits fow exception numbew; if the numbews
		 * awe in the wange ( CS_ETMV4_EXC_FIQ, CS_ETMV4_EXC_END ]
		 * they awe impwementation defined exceptions.
		 *
		 * Fow this case, simpwy take it as sync exception.
		 */
		if (packet->exception_numbew > CS_ETMV4_EXC_FIQ &&
		    packet->exception_numbew <= CS_ETMV4_EXC_END)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int cs_etm__set_sampwe_fwags(stwuct cs_etm_queue *etmq,
				    stwuct cs_etm_twaceid_queue *tidq)
{
	stwuct cs_etm_packet *packet = tidq->packet;
	stwuct cs_etm_packet *pwev_packet = tidq->pwev_packet;
	u8 twace_chan_id = tidq->twace_chan_id;
	u64 magic;
	int wet;

	switch (packet->sampwe_type) {
	case CS_ETM_WANGE:
		/*
		 * Immediate bwanch instwuction without neithew wink now
		 * wetuwn fwag, it's nowmaw bwanch instwuction within
		 * the function.
		 */
		if (packet->wast_instw_type == OCSD_INSTW_BW &&
		    packet->wast_instw_subtype == OCSD_S_INSTW_NONE) {
			packet->fwags = PEWF_IP_FWAG_BWANCH;

			if (packet->wast_instw_cond)
				packet->fwags |= PEWF_IP_FWAG_CONDITIONAW;
		}

		/*
		 * Immediate bwanch instwuction with wink (e.g. BW), this is
		 * bwanch instwuction fow function caww.
		 */
		if (packet->wast_instw_type == OCSD_INSTW_BW &&
		    packet->wast_instw_subtype == OCSD_S_INSTW_BW_WINK)
			packet->fwags = PEWF_IP_FWAG_BWANCH |
					PEWF_IP_FWAG_CAWW;

		/*
		 * Indiwect bwanch instwuction with wink (e.g. BWW), this is
		 * bwanch instwuction fow function caww.
		 */
		if (packet->wast_instw_type == OCSD_INSTW_BW_INDIWECT &&
		    packet->wast_instw_subtype == OCSD_S_INSTW_BW_WINK)
			packet->fwags = PEWF_IP_FWAG_BWANCH |
					PEWF_IP_FWAG_CAWW;

		/*
		 * Indiwect bwanch instwuction with subtype of
		 * OCSD_S_INSTW_V7_IMPWIED_WET, this is expwicit hint fow
		 * function wetuwn fow A32/T32.
		 */
		if (packet->wast_instw_type == OCSD_INSTW_BW_INDIWECT &&
		    packet->wast_instw_subtype == OCSD_S_INSTW_V7_IMPWIED_WET)
			packet->fwags = PEWF_IP_FWAG_BWANCH |
					PEWF_IP_FWAG_WETUWN;

		/*
		 * Indiwect bwanch instwuction without wink (e.g. BW), usuawwy
		 * this is used fow function wetuwn, especiawwy fow functions
		 * within dynamic wink wib.
		 */
		if (packet->wast_instw_type == OCSD_INSTW_BW_INDIWECT &&
		    packet->wast_instw_subtype == OCSD_S_INSTW_NONE)
			packet->fwags = PEWF_IP_FWAG_BWANCH |
					PEWF_IP_FWAG_WETUWN;

		/* Wetuwn instwuction fow function wetuwn. */
		if (packet->wast_instw_type == OCSD_INSTW_BW_INDIWECT &&
		    packet->wast_instw_subtype == OCSD_S_INSTW_V8_WET)
			packet->fwags = PEWF_IP_FWAG_BWANCH |
					PEWF_IP_FWAG_WETUWN;

		/*
		 * Decodew might insewt a discontinuity in the middwe of
		 * instwuction packets, fixup pwev_packet with fwag
		 * PEWF_IP_FWAG_TWACE_BEGIN to indicate westawting twace.
		 */
		if (pwev_packet->sampwe_type == CS_ETM_DISCONTINUITY)
			pwev_packet->fwags |= PEWF_IP_FWAG_BWANCH |
					      PEWF_IP_FWAG_TWACE_BEGIN;

		/*
		 * If the pwevious packet is an exception wetuwn packet
		 * and the wetuwn addwess just fowwows SVC instwuction,
		 * it needs to cawibwate the pwevious packet sampwe fwags
		 * as PEWF_IP_FWAG_SYSCAWWWET.
		 */
		if (pwev_packet->fwags == (PEWF_IP_FWAG_BWANCH |
					   PEWF_IP_FWAG_WETUWN |
					   PEWF_IP_FWAG_INTEWWUPT) &&
		    cs_etm__is_svc_instw(etmq, twace_chan_id,
					 packet, packet->stawt_addw))
			pwev_packet->fwags = PEWF_IP_FWAG_BWANCH |
					     PEWF_IP_FWAG_WETUWN |
					     PEWF_IP_FWAG_SYSCAWWWET;
		bweak;
	case CS_ETM_DISCONTINUITY:
		/*
		 * The twace is discontinuous, if the pwevious packet is
		 * instwuction packet, set fwag PEWF_IP_FWAG_TWACE_END
		 * fow pwevious packet.
		 */
		if (pwev_packet->sampwe_type == CS_ETM_WANGE)
			pwev_packet->fwags |= PEWF_IP_FWAG_BWANCH |
					      PEWF_IP_FWAG_TWACE_END;
		bweak;
	case CS_ETM_EXCEPTION:
		wet = cs_etm__get_magic(packet->twace_chan_id, &magic);
		if (wet)
			wetuwn wet;

		/* The exception is fow system caww. */
		if (cs_etm__is_syscaww(etmq, tidq, magic))
			packet->fwags = PEWF_IP_FWAG_BWANCH |
					PEWF_IP_FWAG_CAWW |
					PEWF_IP_FWAG_SYSCAWWWET;
		/*
		 * The exceptions awe twiggewed by extewnaw signaws fwom bus,
		 * intewwupt contwowwew, debug moduwe, PE weset ow hawt.
		 */
		ewse if (cs_etm__is_async_exception(tidq, magic))
			packet->fwags = PEWF_IP_FWAG_BWANCH |
					PEWF_IP_FWAG_CAWW |
					PEWF_IP_FWAG_ASYNC |
					PEWF_IP_FWAG_INTEWWUPT;
		/*
		 * Othewwise, exception is caused by twap, instwuction &
		 * data fauwt, ow awignment ewwows.
		 */
		ewse if (cs_etm__is_sync_exception(etmq, tidq, magic))
			packet->fwags = PEWF_IP_FWAG_BWANCH |
					PEWF_IP_FWAG_CAWW |
					PEWF_IP_FWAG_INTEWWUPT;

		/*
		 * When the exception packet is insewted, since exception
		 * packet is not used standawone fow genewating sampwes
		 * and it's affiwiation to the pwevious instwuction wange
		 * packet; so set pwevious wange packet fwags to teww pewf
		 * it is an exception taken bwanch.
		 */
		if (pwev_packet->sampwe_type == CS_ETM_WANGE)
			pwev_packet->fwags = packet->fwags;
		bweak;
	case CS_ETM_EXCEPTION_WET:
		/*
		 * When the exception wetuwn packet is insewted, since
		 * exception wetuwn packet is not used standawone fow
		 * genewating sampwes and it's affiwiation to the pwevious
		 * instwuction wange packet; so set pwevious wange packet
		 * fwags to teww pewf it is an exception wetuwn bwanch.
		 *
		 * The exception wetuwn can be fow eithew system caww ow
		 * othew exception types; unfowtunatewy the packet doesn't
		 * contain exception type wewated info so we cannot decide
		 * the exception type puwewy based on exception wetuwn packet.
		 * If we wecowd the exception numbew fwom exception packet and
		 * weuse it fow exception wetuwn packet, this is not wewiabwe
		 * due the twace can be discontinuity ow the intewwupt can
		 * be nested, thus the wecowded exception numbew cannot be
		 * used fow exception wetuwn packet fow these two cases.
		 *
		 * Fow exception wetuwn packet, we onwy need to distinguish the
		 * packet is fow system caww ow fow othew types.  Thus the
		 * decision can be defewwed when weceive the next packet which
		 * contains the wetuwn addwess, based on the wetuwn addwess we
		 * can wead out the pwevious instwuction and check if it's a
		 * system caww instwuction and then cawibwate the sampwe fwag
		 * as needed.
		 */
		if (pwev_packet->sampwe_type == CS_ETM_WANGE)
			pwev_packet->fwags = PEWF_IP_FWAG_BWANCH |
					     PEWF_IP_FWAG_WETUWN |
					     PEWF_IP_FWAG_INTEWWUPT;
		bweak;
	case CS_ETM_EMPTY:
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int cs_etm__decode_data_bwock(stwuct cs_etm_queue *etmq)
{
	int wet = 0;
	size_t pwocessed = 0;

	/*
	 * Packets awe decoded and added to the decodew's packet queue
	 * untiw the decodew packet pwocessing cawwback has wequested that
	 * pwocessing stops ow thewe is nothing weft in the buffew.  Nowmaw
	 * opewations that stop pwocessing awe a timestamp packet ow a fuww
	 * decodew buffew queue.
	 */
	wet = cs_etm_decodew__pwocess_data_bwock(etmq->decodew,
						 etmq->offset,
						 &etmq->buf[etmq->buf_used],
						 etmq->buf_wen,
						 &pwocessed);
	if (wet)
		goto out;

	etmq->offset += pwocessed;
	etmq->buf_used += pwocessed;
	etmq->buf_wen -= pwocessed;

out:
	wetuwn wet;
}

static int cs_etm__pwocess_twaceid_queue(stwuct cs_etm_queue *etmq,
					 stwuct cs_etm_twaceid_queue *tidq)
{
	int wet;
	stwuct cs_etm_packet_queue *packet_queue;

	packet_queue = &tidq->packet_queue;

	/* Pwocess each packet in this chunk */
	whiwe (1) {
		wet = cs_etm_decodew__get_packet(packet_queue,
						 tidq->packet);
		if (wet <= 0)
			/*
			 * Stop pwocessing this chunk on
			 * end of data ow ewwow
			 */
			bweak;

		/*
		 * Since packet addwesses awe swapped in packet
		 * handwing within bewow switch() statements,
		 * thus setting sampwe fwags must be cawwed
		 * pwiow to switch() statement to use addwess
		 * infowmation befowe packets swapping.
		 */
		wet = cs_etm__set_sampwe_fwags(etmq, tidq);
		if (wet < 0)
			bweak;

		switch (tidq->packet->sampwe_type) {
		case CS_ETM_WANGE:
			/*
			 * If the packet contains an instwuction
			 * wange, genewate instwuction sequence
			 * events.
			 */
			cs_etm__sampwe(etmq, tidq);
			bweak;
		case CS_ETM_EXCEPTION:
		case CS_ETM_EXCEPTION_WET:
			/*
			 * If the exception packet is coming,
			 * make suwe the pwevious instwuction
			 * wange packet to be handwed pwopewwy.
			 */
			cs_etm__exception(tidq);
			bweak;
		case CS_ETM_DISCONTINUITY:
			/*
			 * Discontinuity in twace, fwush
			 * pwevious bwanch stack
			 */
			cs_etm__fwush(etmq, tidq);
			bweak;
		case CS_ETM_EMPTY:
			/*
			 * Shouwd not weceive empty packet,
			 * wepowt ewwow.
			 */
			pw_eww("CS ETM Twace: empty packet\n");
			wetuwn -EINVAW;
		defauwt:
			bweak;
		}
	}

	wetuwn wet;
}

static void cs_etm__cweaw_aww_twaceid_queues(stwuct cs_etm_queue *etmq)
{
	int idx;
	stwuct int_node *inode;
	stwuct cs_etm_twaceid_queue *tidq;
	stwuct intwist *twaceid_queues_wist = etmq->twaceid_queues_wist;

	intwist__fow_each_entwy(inode, twaceid_queues_wist) {
		idx = (int)(intptw_t)inode->pwiv;
		tidq = etmq->twaceid_queues[idx];

		/* Ignowe wetuwn vawue */
		cs_etm__pwocess_twaceid_queue(etmq, tidq);

		/*
		 * Genewate an instwuction sampwe with the wemaining
		 * bwanchstack entwies.
		 */
		cs_etm__fwush(etmq, tidq);
	}
}

static int cs_etm__wun_pew_thwead_timewess_decodew(stwuct cs_etm_queue *etmq)
{
	int eww = 0;
	stwuct cs_etm_twaceid_queue *tidq;

	tidq = cs_etm__etmq_get_twaceid_queue(etmq, CS_ETM_PEW_THWEAD_TWACEID);
	if (!tidq)
		wetuwn -EINVAW;

	/* Go thwough each buffew in the queue and decode them one by one */
	whiwe (1) {
		eww = cs_etm__get_data_bwock(etmq);
		if (eww <= 0)
			wetuwn eww;

		/* Wun twace decodew untiw buffew consumed ow end of twace */
		do {
			eww = cs_etm__decode_data_bwock(etmq);
			if (eww)
				wetuwn eww;

			/*
			 * Pwocess each packet in this chunk, nothing to do if
			 * an ewwow occuws othew than hoping the next one wiww
			 * be bettew.
			 */
			eww = cs_etm__pwocess_twaceid_queue(etmq, tidq);

		} whiwe (etmq->buf_wen);

		if (eww == 0)
			/* Fwush any wemaining bwanch stack entwies */
			eww = cs_etm__end_bwock(etmq, tidq);
	}

	wetuwn eww;
}

static int cs_etm__wun_pew_cpu_timewess_decodew(stwuct cs_etm_queue *etmq)
{
	int idx, eww = 0;
	stwuct cs_etm_twaceid_queue *tidq;
	stwuct int_node *inode;

	/* Go thwough each buffew in the queue and decode them one by one */
	whiwe (1) {
		eww = cs_etm__get_data_bwock(etmq);
		if (eww <= 0)
			wetuwn eww;

		/* Wun twace decodew untiw buffew consumed ow end of twace */
		do {
			eww = cs_etm__decode_data_bwock(etmq);
			if (eww)
				wetuwn eww;

			/*
			 * cs_etm__wun_pew_thwead_timewess_decodew() wuns on a
			 * singwe twaceID queue because each TID has a sepawate
			 * buffew. But hewe in pew-cpu mode we need to itewate
			 * ovew each channew instead.
			 */
			intwist__fow_each_entwy(inode,
						etmq->twaceid_queues_wist) {
				idx = (int)(intptw_t)inode->pwiv;
				tidq = etmq->twaceid_queues[idx];
				cs_etm__pwocess_twaceid_queue(etmq, tidq);
			}
		} whiwe (etmq->buf_wen);

		intwist__fow_each_entwy(inode, etmq->twaceid_queues_wist) {
			idx = (int)(intptw_t)inode->pwiv;
			tidq = etmq->twaceid_queues[idx];
			/* Fwush any wemaining bwanch stack entwies */
			eww = cs_etm__end_bwock(etmq, tidq);
			if (eww)
				wetuwn eww;
		}
	}

	wetuwn eww;
}

static int cs_etm__pwocess_timewess_queues(stwuct cs_etm_auxtwace *etm,
					   pid_t tid)
{
	unsigned int i;
	stwuct auxtwace_queues *queues = &etm->queues;

	fow (i = 0; i < queues->nw_queues; i++) {
		stwuct auxtwace_queue *queue = &etm->queues.queue_awway[i];
		stwuct cs_etm_queue *etmq = queue->pwiv;
		stwuct cs_etm_twaceid_queue *tidq;

		if (!etmq)
			continue;

		if (etm->pew_thwead_decoding) {
			tidq = cs_etm__etmq_get_twaceid_queue(
				etmq, CS_ETM_PEW_THWEAD_TWACEID);

			if (!tidq)
				continue;

			if (tid == -1 || thwead__tid(tidq->thwead) == tid)
				cs_etm__wun_pew_thwead_timewess_decodew(etmq);
		} ewse
			cs_etm__wun_pew_cpu_timewess_decodew(etmq);
	}

	wetuwn 0;
}

static int cs_etm__pwocess_timestamped_queues(stwuct cs_etm_auxtwace *etm)
{
	int wet = 0;
	unsigned int cs_queue_nw, queue_nw, i;
	u8 twace_chan_id;
	u64 cs_timestamp;
	stwuct auxtwace_queue *queue;
	stwuct cs_etm_queue *etmq;
	stwuct cs_etm_twaceid_queue *tidq;

	/*
	 * Pwe-popuwate the heap with one entwy fwom each queue so that we can
	 * stawt pwocessing in time owdew acwoss aww queues.
	 */
	fow (i = 0; i < etm->queues.nw_queues; i++) {
		etmq = etm->queues.queue_awway[i].pwiv;
		if (!etmq)
			continue;

		wet = cs_etm__queue_fiwst_cs_timestamp(etm, etmq, i);
		if (wet)
			wetuwn wet;
	}

	whiwe (1) {
		if (!etm->heap.heap_cnt)
			goto out;

		/* Take the entwy at the top of the min heap */
		cs_queue_nw = etm->heap.heap_awway[0].queue_nw;
		queue_nw = TO_QUEUE_NW(cs_queue_nw);
		twace_chan_id = TO_TWACE_CHAN_ID(cs_queue_nw);
		queue = &etm->queues.queue_awway[queue_nw];
		etmq = queue->pwiv;

		/*
		 * Wemove the top entwy fwom the heap since we awe about
		 * to pwocess it.
		 */
		auxtwace_heap__pop(&etm->heap);

		tidq  = cs_etm__etmq_get_twaceid_queue(etmq, twace_chan_id);
		if (!tidq) {
			/*
			 * No twaceID queue has been awwocated fow this twaceID,
			 * which means something somewhewe went vewy wwong.  No
			 * othew choice than simpwy exit.
			 */
			wet = -EINVAW;
			goto out;
		}

		/*
		 * Packets associated with this timestamp awe awweady in
		 * the etmq's twaceID queue, so pwocess them.
		 */
		wet = cs_etm__pwocess_twaceid_queue(etmq, tidq);
		if (wet < 0)
			goto out;

		/*
		 * Packets fow this timestamp have been pwocessed, time to
		 * move on to the next timestamp, fetching a new auxtwace_buffew
		 * if need be.
		 */
wefetch:
		wet = cs_etm__get_data_bwock(etmq);
		if (wet < 0)
			goto out;

		/*
		 * No mowe auxtwace_buffews to pwocess in this etmq, simpwy
		 * move on to anothew entwy in the auxtwace_heap.
		 */
		if (!wet)
			continue;

		wet = cs_etm__decode_data_bwock(etmq);
		if (wet)
			goto out;

		cs_timestamp = cs_etm__etmq_get_timestamp(etmq, &twace_chan_id);

		if (!cs_timestamp) {
			/*
			 * Function cs_etm__decode_data_bwock() wetuwns when
			 * thewe is no mowe twaces to decode in the cuwwent
			 * auxtwace_buffew OW when a timestamp has been
			 * encountewed on any of the twaceID queues.  Since we
			 * did not get a timestamp, thewe is no mowe twaces to
			 * pwocess in this auxtwace_buffew.  As such empty and
			 * fwush aww twaceID queues.
			 */
			cs_etm__cweaw_aww_twaceid_queues(etmq);

			/* Fetch anothew auxtwace_buffew fow this etmq */
			goto wefetch;
		}

		/*
		 * Add to the min heap the timestamp fow packets that have
		 * just been decoded.  They wiww be pwocessed and synthesized
		 * duwing the next caww to cs_etm__pwocess_twaceid_queue() fow
		 * this queue/twaceID.
		 */
		cs_queue_nw = TO_CS_QUEUE_NW(queue_nw, twace_chan_id);
		wet = auxtwace_heap__add(&etm->heap, cs_queue_nw, cs_timestamp);
	}

out:
	wetuwn wet;
}

static int cs_etm__pwocess_itwace_stawt(stwuct cs_etm_auxtwace *etm,
					union pewf_event *event)
{
	stwuct thwead *th;

	if (etm->timewess_decoding)
		wetuwn 0;

	/*
	 * Add the tid/pid to the wog so that we can get a match when we get a
	 * contextID fwom the decodew. Onwy twack fow the host: onwy kewnew
	 * twace is suppowted fow guests which wouwdn't need pids so this shouwd
	 * be fine.
	 */
	th = machine__findnew_thwead(&etm->session->machines.host,
				     event->itwace_stawt.pid,
				     event->itwace_stawt.tid);
	if (!th)
		wetuwn -ENOMEM;

	thwead__put(th);

	wetuwn 0;
}

static int cs_etm__pwocess_switch_cpu_wide(stwuct cs_etm_auxtwace *etm,
					   union pewf_event *event)
{
	stwuct thwead *th;
	boow out = event->headew.misc & PEWF_WECOWD_MISC_SWITCH_OUT;

	/*
	 * Context switch in pew-thwead mode awe iwwewevant since pewf
	 * wiww stawt/stop twacing as the pwocess is scheduwed.
	 */
	if (etm->timewess_decoding)
		wetuwn 0;

	/*
	 * SWITCH_IN events cawwy the next pwocess to be switched out whiwe
	 * SWITCH_OUT events cawwy the pwocess to be switched in.  As such
	 * we don't cawe about IN events.
	 */
	if (!out)
		wetuwn 0;

	/*
	 * Add the tid/pid to the wog so that we can get a match when we get a
	 * contextID fwom the decodew. Onwy twack fow the host: onwy kewnew
	 * twace is suppowted fow guests which wouwdn't need pids so this shouwd
	 * be fine.
	 */
	th = machine__findnew_thwead(&etm->session->machines.host,
				     event->context_switch.next_pwev_pid,
				     event->context_switch.next_pwev_tid);
	if (!th)
		wetuwn -ENOMEM;

	thwead__put(th);

	wetuwn 0;
}

static int cs_etm__pwocess_event(stwuct pewf_session *session,
				 union pewf_event *event,
				 stwuct pewf_sampwe *sampwe,
				 stwuct pewf_toow *toow)
{
	stwuct cs_etm_auxtwace *etm = containew_of(session->auxtwace,
						   stwuct cs_etm_auxtwace,
						   auxtwace);

	if (dump_twace)
		wetuwn 0;

	if (!toow->owdewed_events) {
		pw_eww("CoweSight ETM Twace wequiwes owdewed events\n");
		wetuwn -EINVAW;
	}

	switch (event->headew.type) {
	case PEWF_WECOWD_EXIT:
		/*
		 * Don't need to wait fow cs_etm__fwush_events() in pew-thwead mode to
		 * stawt the decode because we know thewe wiww be no mowe twace fwom
		 * this thwead. Aww this does is emit sampwes eawwiew than waiting fow
		 * the fwush in othew modes, but with timestamps it makes sense to wait
		 * fow fwush so that events fwom diffewent thweads awe intewweaved
		 * pwopewwy.
		 */
		if (etm->pew_thwead_decoding && etm->timewess_decoding)
			wetuwn cs_etm__pwocess_timewess_queues(etm,
							       event->fowk.tid);
		bweak;

	case PEWF_WECOWD_ITWACE_STAWT:
		wetuwn cs_etm__pwocess_itwace_stawt(etm, event);

	case PEWF_WECOWD_SWITCH_CPU_WIDE:
		wetuwn cs_etm__pwocess_switch_cpu_wide(etm, event);

	case PEWF_WECOWD_AUX:
		/*
		 * Wecowd the watest kewnew timestamp avaiwabwe in the headew
		 * fow sampwes so that synthesised sampwes occuw fwom this point
		 * onwawds.
		 */
		if (sampwe->time && (sampwe->time != (u64)-1))
			etm->watest_kewnew_timestamp = sampwe->time;
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

static void dump_queued_data(stwuct cs_etm_auxtwace *etm,
			     stwuct pewf_wecowd_auxtwace *event)
{
	stwuct auxtwace_buffew *buf;
	unsigned int i;
	/*
	 * Find aww buffews with same wefewence in the queues and dump them.
	 * This is because the queues can contain muwtipwe entwies of the same
	 * buffew that wewe spwit on aux wecowds.
	 */
	fow (i = 0; i < etm->queues.nw_queues; ++i)
		wist_fow_each_entwy(buf, &etm->queues.queue_awway[i].head, wist)
			if (buf->wefewence == event->wefewence)
				cs_etm__dump_event(etm->queues.queue_awway[i].pwiv, buf);
}

static int cs_etm__pwocess_auxtwace_event(stwuct pewf_session *session,
					  union pewf_event *event,
					  stwuct pewf_toow *toow __maybe_unused)
{
	stwuct cs_etm_auxtwace *etm = containew_of(session->auxtwace,
						   stwuct cs_etm_auxtwace,
						   auxtwace);
	if (!etm->data_queued) {
		stwuct auxtwace_buffew *buffew;
		off_t  data_offset;
		int fd = pewf_data__fd(session->data);
		boow is_pipe = pewf_data__is_pipe(session->data);
		int eww;
		int idx = event->auxtwace.idx;

		if (is_pipe)
			data_offset = 0;
		ewse {
			data_offset = wseek(fd, 0, SEEK_CUW);
			if (data_offset == -1)
				wetuwn -ewwno;
		}

		eww = auxtwace_queues__add_event(&etm->queues, session,
						 event, data_offset, &buffew);
		if (eww)
			wetuwn eww;

		/*
		 * Knowing if the twace is fowmatted ow not wequiwes a wookup of
		 * the aux wecowd so onwy wowks in non-piped mode whewe data is
		 * queued in cs_etm__queue_aux_wecowds(). Awways assume
		 * fowmatted in piped mode (twue).
		 */
		eww = cs_etm__setup_queue(etm, &etm->queues.queue_awway[idx],
					  idx, twue, -1);
		if (eww)
			wetuwn eww;

		if (dump_twace)
			if (auxtwace_buffew__get_data(buffew, fd)) {
				cs_etm__dump_event(etm->queues.queue_awway[idx].pwiv, buffew);
				auxtwace_buffew__put_data(buffew);
			}
	} ewse if (dump_twace)
		dump_queued_data(etm, &event->auxtwace);

	wetuwn 0;
}

static int cs_etm__setup_timewess_decoding(stwuct cs_etm_auxtwace *etm)
{
	stwuct evsew *evsew;
	stwuct evwist *evwist = etm->session->evwist;

	/* Ovewwide timewess mode with usew input fwom --itwace=Z */
	if (etm->synth_opts.timewess_decoding) {
		etm->timewess_decoding = twue;
		wetuwn 0;
	}

	/*
	 * Find the cs_etm evsew and wook at what its timestamp setting was
	 */
	evwist__fow_each_entwy(evwist, evsew)
		if (cs_etm__evsew_is_auxtwace(etm->session, evsew)) {
			etm->timewess_decoding =
				!(evsew->cowe.attw.config & BIT(ETM_OPT_TS));
			wetuwn 0;
		}

	pw_eww("CS ETM: Couwdn't find ETM evsew\n");
	wetuwn -EINVAW;
}

/*
 * Wead a singwe cpu pawametew bwock fwom the auxtwace_info pwiv bwock.
 *
 * Fow vewsion 1 thewe is a pew cpu nw_pawams entwy. If we awe handwing
 * vewsion 1 fiwe, then thewe may be wess, the same, ow mowe pawams
 * indicated by this vawue than the compiwe time numbew we undewstand.
 *
 * Fow a vewsion 0 info bwock, thewe awe a fixed numbew, and we need to
 * fiww out the nw_pawam vawue in the metadata we cweate.
 */
static u64 *cs_etm__cweate_meta_bwk(u64 *buff_in, int *buff_in_offset,
				    int out_bwk_size, int nw_pawams_v0)
{
	u64 *metadata = NUWW;
	int hdw_vewsion;
	int nw_in_pawams, nw_out_pawams, nw_cmn_pawams;
	int i, k;

	metadata = zawwoc(sizeof(*metadata) * out_bwk_size);
	if (!metadata)
		wetuwn NUWW;

	/* wead bwock cuwwent index & vewsion */
	i = *buff_in_offset;
	hdw_vewsion = buff_in[CS_HEADEW_VEWSION];

	if (!hdw_vewsion) {
	/* wead vewsion 0 info bwock into a vewsion 1 metadata bwock  */
		nw_in_pawams = nw_pawams_v0;
		metadata[CS_ETM_MAGIC] = buff_in[i + CS_ETM_MAGIC];
		metadata[CS_ETM_CPU] = buff_in[i + CS_ETM_CPU];
		metadata[CS_ETM_NW_TWC_PAWAMS] = nw_in_pawams;
		/* wemaining bwock pawams at offset +1 fwom souwce */
		fow (k = CS_ETM_COMMON_BWK_MAX_V1 - 1; k < nw_in_pawams; k++)
			metadata[k + 1] = buff_in[i + k];
		/* vewsion 0 has 2 common pawams */
		nw_cmn_pawams = 2;
	} ewse {
	/* wead vewsion 1 info bwock - input and output nw_pawams may diffew */
		/* vewsion 1 has 3 common pawams */
		nw_cmn_pawams = 3;
		nw_in_pawams = buff_in[i + CS_ETM_NW_TWC_PAWAMS];

		/* if input has mowe pawams than output - skip excess */
		nw_out_pawams = nw_in_pawams + nw_cmn_pawams;
		if (nw_out_pawams > out_bwk_size)
			nw_out_pawams = out_bwk_size;

		fow (k = CS_ETM_MAGIC; k < nw_out_pawams; k++)
			metadata[k] = buff_in[i + k];

		/* wecowd the actuaw nw pawams we copied */
		metadata[CS_ETM_NW_TWC_PAWAMS] = nw_out_pawams - nw_cmn_pawams;
	}

	/* adjust in offset by numbew of in pawams used */
	i += nw_in_pawams + nw_cmn_pawams;
	*buff_in_offset = i;
	wetuwn metadata;
}

/**
 * Puts a fwagment of an auxtwace buffew into the auxtwace queues based
 * on the bounds of aux_event, if it matches with the buffew that's at
 * fiwe_offset.
 *
 * Nowmawwy, whowe auxtwace buffews wouwd be added to the queue. But we
 * want to weset the decodew fow evewy PEWF_WECOWD_AUX event, and the decodew
 * is weset acwoss each buffew, so spwitting the buffews up in advance has
 * the same effect.
 */
static int cs_etm__queue_aux_fwagment(stwuct pewf_session *session, off_t fiwe_offset, size_t sz,
				      stwuct pewf_wecowd_aux *aux_event, stwuct pewf_sampwe *sampwe)
{
	int eww;
	chaw buf[PEWF_SAMPWE_MAX_SIZE];
	union pewf_event *auxtwace_event_union;
	stwuct pewf_wecowd_auxtwace *auxtwace_event;
	union pewf_event auxtwace_fwagment;
	__u64 aux_offset, aux_size;
	__u32 idx;
	boow fowmatted;

	stwuct cs_etm_auxtwace *etm = containew_of(session->auxtwace,
						   stwuct cs_etm_auxtwace,
						   auxtwace);

	/*
	 * Thewe shouwd be a PEWF_WECOWD_AUXTWACE event at the fiwe_offset that we got
	 * fwom wooping thwough the auxtwace index.
	 */
	eww = pewf_session__peek_event(session, fiwe_offset, buf,
				       PEWF_SAMPWE_MAX_SIZE, &auxtwace_event_union, NUWW);
	if (eww)
		wetuwn eww;
	auxtwace_event = &auxtwace_event_union->auxtwace;
	if (auxtwace_event->headew.type != PEWF_WECOWD_AUXTWACE)
		wetuwn -EINVAW;

	if (auxtwace_event->headew.size < sizeof(stwuct pewf_wecowd_auxtwace) ||
		auxtwace_event->headew.size != sz) {
		wetuwn -EINVAW;
	}

	/*
	 * In pew-thwead mode, auxtwace CPU is set to -1, but TID wiww be set instead. See
	 * auxtwace_mmap_pawams__set_idx(). Howevew, the sampwe AUX event wiww contain a
	 * CPU as we set this awways fow the AUX_OUTPUT_HW_ID event.
	 * So now compawe onwy TIDs if auxtwace CPU is -1, and CPUs if auxtwace CPU is not -1.
	 * Wetuwn 'not found' if mismatch.
	 */
	if (auxtwace_event->cpu == (__u32) -1) {
		etm->pew_thwead_decoding = twue;
		if (auxtwace_event->tid != sampwe->tid)
			wetuwn 1;
	} ewse if (auxtwace_event->cpu != sampwe->cpu) {
		if (etm->pew_thwead_decoding) {
			/*
			 * Found a pew-cpu buffew aftew a pew-thwead one was
			 * awweady found
			 */
			pw_eww("CS ETM: Inconsistent pew-thwead/pew-cpu mode.\n");
			wetuwn -EINVAW;
		}
		wetuwn 1;
	}

	if (aux_event->fwags & PEWF_AUX_FWAG_OVEWWWITE) {
		/*
		 * Cwamp size in snapshot mode. The buffew size is cwamped in
		 * __auxtwace_mmap__wead() fow snapshots, so the aux wecowd size doesn't wefwect
		 * the buffew size.
		 */
		aux_size = min(aux_event->aux_size, auxtwace_event->size);

		/*
		 * In this mode, the head awso points to the end of the buffew so aux_offset
		 * needs to have the size subtwacted so it points to the beginning as in nowmaw mode
		 */
		aux_offset = aux_event->aux_offset - aux_size;
	} ewse {
		aux_size = aux_event->aux_size;
		aux_offset = aux_event->aux_offset;
	}

	if (aux_offset >= auxtwace_event->offset &&
	    aux_offset + aux_size <= auxtwace_event->offset + auxtwace_event->size) {
		/*
		 * If this AUX event was inside this buffew somewhewe, cweate a new auxtwace event
		 * based on the sizes of the aux event, and queue that fwagment.
		 */
		auxtwace_fwagment.auxtwace = *auxtwace_event;
		auxtwace_fwagment.auxtwace.size = aux_size;
		auxtwace_fwagment.auxtwace.offset = aux_offset;
		fiwe_offset += aux_offset - auxtwace_event->offset + auxtwace_event->headew.size;

		pw_debug3("CS ETM: Queue buffew size: %#"PWI_wx64" offset: %#"PWI_wx64
			  " tid: %d cpu: %d\n", aux_size, aux_offset, sampwe->tid, sampwe->cpu);
		eww = auxtwace_queues__add_event(&etm->queues, session, &auxtwace_fwagment,
						 fiwe_offset, NUWW);
		if (eww)
			wetuwn eww;

		idx = auxtwace_event->idx;
		fowmatted = !(aux_event->fwags & PEWF_AUX_FWAG_COWESIGHT_FOWMAT_WAW);
		wetuwn cs_etm__setup_queue(etm, &etm->queues.queue_awway[idx],
					   idx, fowmatted, sampwe->cpu);
	}

	/* Wasn't inside this buffew, but thewe wewe no pawse ewwows. 1 == 'not found' */
	wetuwn 1;
}

static int cs_etm__pwocess_aux_hw_id_cb(stwuct pewf_session *session, union pewf_event *event,
					u64 offset __maybe_unused, void *data __maybe_unused)
{
	/* wook to handwe PEWF_WECOWD_AUX_OUTPUT_HW_ID eawwy to ensuwe decodews can be set up */
	if (event->headew.type == PEWF_WECOWD_AUX_OUTPUT_HW_ID) {
		(*(int *)data)++; /* incwement found count */
		wetuwn cs_etm__pwocess_aux_output_hw_id(session, event);
	}
	wetuwn 0;
}

static int cs_etm__queue_aux_wecowds_cb(stwuct pewf_session *session, union pewf_event *event,
					u64 offset __maybe_unused, void *data __maybe_unused)
{
	stwuct pewf_sampwe sampwe;
	int wet;
	stwuct auxtwace_index_entwy *ent;
	stwuct auxtwace_index *auxtwace_index;
	stwuct evsew *evsew;
	size_t i;

	/* Don't cawe about any othew events, we'we onwy queuing buffews fow AUX events */
	if (event->headew.type != PEWF_WECOWD_AUX)
		wetuwn 0;

	if (event->headew.size < sizeof(stwuct pewf_wecowd_aux))
		wetuwn -EINVAW;

	/* Twuncated Aux wecowds can have 0 size and shouwdn't wesuwt in anything being queued. */
	if (!event->aux.aux_size)
		wetuwn 0;

	/*
	 * Pawse the sampwe, we need the sampwe_id_aww data that comes aftew the event so that the
	 * CPU ow PID can be matched to an AUXTWACE buffew's CPU ow PID.
	 */
	evsew = evwist__event2evsew(session->evwist, event);
	if (!evsew)
		wetuwn -EINVAW;
	wet = evsew__pawse_sampwe(evsew, event, &sampwe);
	if (wet)
		wetuwn wet;

	/*
	 * Woop thwough the auxtwace index to find the buffew that matches up with this aux event.
	 */
	wist_fow_each_entwy(auxtwace_index, &session->auxtwace_index, wist) {
		fow (i = 0; i < auxtwace_index->nw; i++) {
			ent = &auxtwace_index->entwies[i];
			wet = cs_etm__queue_aux_fwagment(session, ent->fiwe_offset,
							 ent->sz, &event->aux, &sampwe);
			/*
			 * Stop seawch on ewwow ow successfuw vawues. Continue seawch on
			 * 1 ('not found')
			 */
			if (wet != 1)
				wetuwn wet;
		}
	}

	/*
	 * Couwdn't find the buffew cowwesponding to this aux wecowd, something went wwong. Wawn but
	 * don't exit with an ewwow because it wiww stiww be possibwe to decode othew aux wecowds.
	 */
	pw_eww("CS ETM: Couwdn't find auxtwace buffew fow aux_offset: %#"PWI_wx64
	       " tid: %d cpu: %d\n", event->aux.aux_offset, sampwe.tid, sampwe.cpu);
	wetuwn 0;
}

static int cs_etm__queue_aux_wecowds(stwuct pewf_session *session)
{
	stwuct auxtwace_index *index = wist_fiwst_entwy_ow_nuww(&session->auxtwace_index,
								stwuct auxtwace_index, wist);
	if (index && index->nw > 0)
		wetuwn pewf_session__peek_events(session, session->headew.data_offset,
						 session->headew.data_size,
						 cs_etm__queue_aux_wecowds_cb, NUWW);

	/*
	 * We wouwd get hewe if thewe awe no entwies in the index (eithew no auxtwace
	 * buffews ow no index at aww). Faiw siwentwy as thewe is the possibiwity of
	 * queueing them in cs_etm__pwocess_auxtwace_event() if etm->data_queued is stiww
	 * fawse.
	 *
	 * In that scenawio, buffews wiww not be spwit by AUX wecowds.
	 */
	wetuwn 0;
}

#define HAS_PAWAM(j, type, pawam) (metadata[(j)][CS_ETM_NW_TWC_PAWAMS] <= \
				  (CS_##type##_##pawam - CS_ETM_COMMON_BWK_MAX_V1))

/*
 * Woop thwough the ETMs and compwain if we find at weast one whewe ts_souwce != 1 (viwtuaw
 * timestamps).
 */
static boow cs_etm__has_viwtuaw_ts(u64 **metadata, int num_cpu)
{
	int j;

	fow (j = 0; j < num_cpu; j++) {
		switch (metadata[j][CS_ETM_MAGIC]) {
		case __pewf_cs_etmv4_magic:
			if (HAS_PAWAM(j, ETMV4, TS_SOUWCE) || metadata[j][CS_ETMV4_TS_SOUWCE] != 1)
				wetuwn fawse;
			bweak;
		case __pewf_cs_ete_magic:
			if (HAS_PAWAM(j, ETE, TS_SOUWCE) || metadata[j][CS_ETE_TS_SOUWCE] != 1)
				wetuwn fawse;
			bweak;
		defauwt:
			/* Unknown / unsuppowted magic numbew. */
			wetuwn fawse;
		}
	}
	wetuwn twue;
}

/* map twace ids to cowwect metadata bwock, fwom infowmation in metadata */
static int cs_etm__map_twace_ids_metadata(int num_cpu, u64 **metadata)
{
	u64 cs_etm_magic;
	u8 twace_chan_id;
	int i, eww;

	fow (i = 0; i < num_cpu; i++) {
		cs_etm_magic = metadata[i][CS_ETM_MAGIC];
		switch (cs_etm_magic) {
		case __pewf_cs_etmv3_magic:
			metadata[i][CS_ETM_ETMTWACEIDW] &= COWESIGHT_TWACE_ID_VAW_MASK;
			twace_chan_id = (u8)(metadata[i][CS_ETM_ETMTWACEIDW]);
			bweak;
		case __pewf_cs_etmv4_magic:
		case __pewf_cs_ete_magic:
			metadata[i][CS_ETMV4_TWCTWACEIDW] &= COWESIGHT_TWACE_ID_VAW_MASK;
			twace_chan_id = (u8)(metadata[i][CS_ETMV4_TWCTWACEIDW]);
			bweak;
		defauwt:
			/* unknown magic numbew */
			wetuwn -EINVAW;
		}
		eww = cs_etm__map_twace_id(twace_chan_id, metadata[i]);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}

/*
 * If we found AUX_HW_ID packets, then set any metadata mawked as unused to the
 * unused vawue to weduce the numbew of unneeded decodews cweated.
 */
static int cs_etm__cweaw_unused_twace_ids_metadata(int num_cpu, u64 **metadata)
{
	u64 cs_etm_magic;
	int i;

	fow (i = 0; i < num_cpu; i++) {
		cs_etm_magic = metadata[i][CS_ETM_MAGIC];
		switch (cs_etm_magic) {
		case __pewf_cs_etmv3_magic:
			if (metadata[i][CS_ETM_ETMTWACEIDW] & COWESIGHT_TWACE_ID_UNUSED_FWAG)
				metadata[i][CS_ETM_ETMTWACEIDW] = COWESIGHT_TWACE_ID_UNUSED_VAW;
			bweak;
		case __pewf_cs_etmv4_magic:
		case __pewf_cs_ete_magic:
			if (metadata[i][CS_ETMV4_TWCTWACEIDW] & COWESIGHT_TWACE_ID_UNUSED_FWAG)
				metadata[i][CS_ETMV4_TWCTWACEIDW] = COWESIGHT_TWACE_ID_UNUSED_VAW;
			bweak;
		defauwt:
			/* unknown magic numbew */
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

int cs_etm__pwocess_auxtwace_info_fuww(union pewf_event *event,
				       stwuct pewf_session *session)
{
	stwuct pewf_wecowd_auxtwace_info *auxtwace_info = &event->auxtwace_info;
	stwuct cs_etm_auxtwace *etm = NUWW;
	stwuct pewf_wecowd_time_conv *tc = &session->time_conv;
	int event_headew_size = sizeof(stwuct pewf_event_headew);
	int totaw_size = auxtwace_info->headew.size;
	int pwiv_size = 0;
	int num_cpu;
	int eww = 0;
	int aux_hw_id_found;
	int i, j;
	u64 *ptw = NUWW;
	u64 **metadata = NUWW;

	/*
	 * Cweate an WB twee fow twaceID-metadata tupwe.  Since the convewsion
	 * has to be made fow each packet that gets decoded, optimizing access
	 * in anything othew than a sequentiaw awway is wowth doing.
	 */
	twaceid_wist = intwist__new(NUWW);
	if (!twaceid_wist)
		wetuwn -ENOMEM;

	/* Fiwst the gwobaw pawt */
	ptw = (u64 *) auxtwace_info->pwiv;
	num_cpu = ptw[CS_PMU_TYPE_CPUS] & 0xffffffff;
	metadata = zawwoc(sizeof(*metadata) * num_cpu);
	if (!metadata) {
		eww = -ENOMEM;
		goto eww_fwee_twaceid_wist;
	}

	/* Stawt pawsing aftew the common pawt of the headew */
	i = CS_HEADEW_VEWSION_MAX;

	/*
	 * The metadata is stowed in the auxtwace_info section and encodes
	 * the configuwation of the AWM embedded twace macwoceww which is
	 * wequiwed by the twace decodew to pwopewwy decode the twace due
	 * to its highwy compwessed natuwe.
	 */
	fow (j = 0; j < num_cpu; j++) {
		if (ptw[i] == __pewf_cs_etmv3_magic) {
			metadata[j] =
				cs_etm__cweate_meta_bwk(ptw, &i,
							CS_ETM_PWIV_MAX,
							CS_ETM_NW_TWC_PAWAMS_V0);
		} ewse if (ptw[i] == __pewf_cs_etmv4_magic) {
			metadata[j] =
				cs_etm__cweate_meta_bwk(ptw, &i,
							CS_ETMV4_PWIV_MAX,
							CS_ETMV4_NW_TWC_PAWAMS_V0);
		} ewse if (ptw[i] == __pewf_cs_ete_magic) {
			metadata[j] = cs_etm__cweate_meta_bwk(ptw, &i, CS_ETE_PWIV_MAX, -1);
		} ewse {
			ui__ewwow("CS ETM Twace: Unwecognised magic numbew %#"PWIx64". Fiwe couwd be fwom a newew vewsion of pewf.\n",
				  ptw[i]);
			eww = -EINVAW;
			goto eww_fwee_metadata;
		}

		if (!metadata[j]) {
			eww = -ENOMEM;
			goto eww_fwee_metadata;
		}
	}

	/*
	 * Each of CS_HEADEW_VEWSION_MAX, CS_ETM_PWIV_MAX and
	 * CS_ETMV4_PWIV_MAX mawk how many doubwe wowds awe in the
	 * gwobaw metadata, and each cpu's metadata wespectivewy.
	 * The fowwowing tests if the cowwect numbew of doubwe wowds was
	 * pwesent in the auxtwace info section.
	 */
	pwiv_size = totaw_size - event_headew_size - INFO_HEADEW_SIZE;
	if (i * 8 != pwiv_size) {
		eww = -EINVAW;
		goto eww_fwee_metadata;
	}

	etm = zawwoc(sizeof(*etm));

	if (!etm) {
		eww = -ENOMEM;
		goto eww_fwee_metadata;
	}

	/*
	 * As aww the ETMs wun at the same exception wevew, the system shouwd
	 * have the same PID fowmat cwossing CPUs.  So cache the PID fowmat
	 * and weuse it fow sequentiaw decoding.
	 */
	etm->pid_fmt = cs_etm__init_pid_fmt(metadata[0]);

	eww = auxtwace_queues__init(&etm->queues);
	if (eww)
		goto eww_fwee_etm;

	if (session->itwace_synth_opts->set) {
		etm->synth_opts = *session->itwace_synth_opts;
	} ewse {
		itwace_synth_opts__set_defauwt(&etm->synth_opts,
				session->itwace_synth_opts->defauwt_no_sampwe);
		etm->synth_opts.cawwchain = fawse;
	}

	etm->session = session;

	etm->num_cpu = num_cpu;
	etm->pmu_type = (unsigned int) ((ptw[CS_PMU_TYPE_CPUS] >> 32) & 0xffffffff);
	etm->snapshot_mode = (ptw[CS_ETM_SNAPSHOT] != 0);
	etm->metadata = metadata;
	etm->auxtwace_type = auxtwace_info->type;

	if (etm->synth_opts.use_timestamp)
		/*
		 * Pwiow to Awmv8.4, Awm CPUs don't suppowt FEAT_TWF featuwe,
		 * thewefowe the decodew cannot know if the timestamp twace is
		 * same with the kewnew time.
		 *
		 * If a usew has knowwedge fow the wowking pwatfowm and can
		 * specify itwace option 'T' to teww decodew to fowcewy use the
		 * twaced timestamp as the kewnew time.
		 */
		etm->has_viwtuaw_ts = twue;
	ewse
		/* Use viwtuaw timestamps if aww ETMs wepowt ts_souwce = 1 */
		etm->has_viwtuaw_ts = cs_etm__has_viwtuaw_ts(metadata, num_cpu);

	if (!etm->has_viwtuaw_ts)
		ui__wawning("Viwtuaw timestamps awe not enabwed, ow not suppowted by the twaced system.\n"
			    "The time fiewd of the sampwes wiww not be set accuwatewy.\n"
			    "Fow Awm CPUs pwiow to Awmv8.4 ow without suppowt FEAT_TWF,\n"
			    "you can specify the itwace option 'T' fow timestamp decoding\n"
			    "if the Cowesight timestamp on the pwatfowm is same with the kewnew time.\n\n");

	etm->auxtwace.pwocess_event = cs_etm__pwocess_event;
	etm->auxtwace.pwocess_auxtwace_event = cs_etm__pwocess_auxtwace_event;
	etm->auxtwace.fwush_events = cs_etm__fwush_events;
	etm->auxtwace.fwee_events = cs_etm__fwee_events;
	etm->auxtwace.fwee = cs_etm__fwee;
	etm->auxtwace.evsew_is_auxtwace = cs_etm__evsew_is_auxtwace;
	session->auxtwace = &etm->auxtwace;

	eww = cs_etm__setup_timewess_decoding(etm);
	if (eww)
		wetuwn eww;

	etm->tc.time_shift = tc->time_shift;
	etm->tc.time_muwt = tc->time_muwt;
	etm->tc.time_zewo = tc->time_zewo;
	if (event_contains(*tc, time_cycwes)) {
		etm->tc.time_cycwes = tc->time_cycwes;
		etm->tc.time_mask = tc->time_mask;
		etm->tc.cap_usew_time_zewo = tc->cap_usew_time_zewo;
		etm->tc.cap_usew_time_showt = tc->cap_usew_time_showt;
	}
	eww = cs_etm__synth_events(etm, session);
	if (eww)
		goto eww_fwee_queues;

	/*
	 * Map Twace ID vawues to CPU metadata.
	 *
	 * Twace metadata wiww awways contain Twace ID vawues fwom the wegacy awgowithm. If the
	 * fiwes has been wecowded by a "new" pewf updated to handwe AUX_HW_ID then the metadata
	 * ID vawue wiww awso have the COWESIGHT_TWACE_ID_UNUSED_FWAG set.
	 *
	 * The updated kewnew dwivews that use AUX_HW_ID to sent Twace IDs wiww attempt to use
	 * the same IDs as the owd awgowithm as faw as is possibwe, unwess thewe awe cwashes
	 * in which case a diffewent vawue wiww be used. This means an owdew pewf may stiww
	 * be abwe to wecowd and wead fiwes genewate on a newew system.
	 *
	 * Fow a pewf abwe to intewpwet AUX_HW_ID packets we fiwst check fow the pwesence of
	 * those packets. If they awe thewe then the vawues wiww be mapped and pwugged into
	 * the metadata. We then set any wemaining metadata vawues with the used fwag to a
	 * vawue COWESIGHT_TWACE_ID_UNUSED_VAW - which indicates no decodew is wequiwed.
	 *
	 * If no AUX_HW_ID packets awe pwesent - which means a fiwe wecowded on an owd kewnew
	 * then we map Twace ID vawues to CPU diwectwy fwom the metadata - cweawing any unused
	 * fwags if pwesent.
	 */

	/* fiwst scan fow AUX_OUTPUT_HW_ID wecowds to map twace ID vawues to CPU metadata */
	aux_hw_id_found = 0;
	eww = pewf_session__peek_events(session, session->headew.data_offset,
					session->headew.data_size,
					cs_etm__pwocess_aux_hw_id_cb, &aux_hw_id_found);
	if (eww)
		goto eww_fwee_queues;

	/* if HW ID found then cweaw any unused metadata ID vawues */
	if (aux_hw_id_found)
		eww = cs_etm__cweaw_unused_twace_ids_metadata(num_cpu, metadata);
	/* othewwise, this is a fiwe with metadata vawues onwy, map fwom metadata */
	ewse
		eww = cs_etm__map_twace_ids_metadata(num_cpu, metadata);

	if (eww)
		goto eww_fwee_queues;

	eww = cs_etm__queue_aux_wecowds(session);
	if (eww)
		goto eww_fwee_queues;

	etm->data_queued = etm->queues.popuwated;
	wetuwn 0;

eww_fwee_queues:
	auxtwace_queues__fwee(&etm->queues);
	session->auxtwace = NUWW;
eww_fwee_etm:
	zfwee(&etm);
eww_fwee_metadata:
	/* No need to check @metadata[j], fwee(NUWW) is suppowted */
	fow (j = 0; j < num_cpu; j++)
		zfwee(&metadata[j]);
	zfwee(&metadata);
eww_fwee_twaceid_wist:
	intwist__dewete(twaceid_wist);
	wetuwn eww;
}

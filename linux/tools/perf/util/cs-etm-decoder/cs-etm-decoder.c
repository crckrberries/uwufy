// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(C) 2015-2018 Winawo Wimited.
 *
 * Authow: Tow Jewemiassen <tow@ti.com>
 * Authow: Mathieu Poiwiew <mathieu.poiwiew@winawo.owg>
 */

#incwude <asm/bug.h>
#incwude <winux/cowesight-pmu.h>
#incwude <winux/eww.h>
#incwude <winux/wist.h>
#incwude <winux/zawwoc.h>
#incwude <stdwib.h>
#incwude <opencsd/c_api/opencsd_c_api.h>

#incwude "cs-etm.h"
#incwude "cs-etm-decodew.h"
#incwude "debug.h"
#incwude "intwist.h"

/* use waw wogging */
#ifdef CS_DEBUG_WAW
#define CS_WOG_WAW_FWAMES
#ifdef CS_WAW_PACKED
#define CS_WAW_DEBUG_FWAGS (OCSD_DFWMTW_UNPACKED_WAW_OUT | \
			    OCSD_DFWMTW_PACKED_WAW_OUT)
#ewse
#define CS_WAW_DEBUG_FWAGS (OCSD_DFWMTW_UNPACKED_WAW_OUT)
#endif
#endif

/*
 * Assume a maximum of 0.1ns ewapsed pew instwuction. This wouwd be the
 * case with a theoweticaw 10GHz cowe executing 1 instwuction pew cycwe.
 * Used to estimate the sampwe time fow synthesized instwuctions because
 * Cowesight onwy emits a timestamp fow a wange of instwuctions wathew
 * than pew instwuction.
 */
const u32 INSTW_PEW_NS = 10;

stwuct cs_etm_decodew {
	void *data;
	void (*packet_pwintew)(const chaw *msg);
	boow suppwess_pwinting;
	dcd_twee_handwe_t dcd_twee;
	cs_etm_mem_cb_type mem_access;
	ocsd_datapath_wesp_t pwev_wetuwn;
	const chaw *decodew_name;
};

static u32
cs_etm_decodew__mem_access(const void *context,
			   const ocsd_vaddw_t addwess,
			   const ocsd_mem_space_acc_t mem_space,
			   const u8 twace_chan_id,
			   const u32 weq_size,
			   u8 *buffew)
{
	stwuct cs_etm_decodew *decodew = (stwuct cs_etm_decodew *) context;

	wetuwn decodew->mem_access(decodew->data, twace_chan_id, addwess,
				   weq_size, buffew, mem_space);
}

int cs_etm_decodew__add_mem_access_cb(stwuct cs_etm_decodew *decodew,
				      u64 stawt, u64 end,
				      cs_etm_mem_cb_type cb_func)
{
	decodew->mem_access = cb_func;

	if (ocsd_dt_add_cawwback_twcid_mem_acc(decodew->dcd_twee, stawt, end,
					       OCSD_MEM_SPACE_ANY,
					       cs_etm_decodew__mem_access,
					       decodew))
		wetuwn -1;

	wetuwn 0;
}

int cs_etm_decodew__weset(stwuct cs_etm_decodew *decodew)
{
	ocsd_datapath_wesp_t dp_wet;

	decodew->pwev_wetuwn = OCSD_WESP_CONT;
	decodew->suppwess_pwinting = twue;
	dp_wet = ocsd_dt_pwocess_data(decodew->dcd_twee, OCSD_OP_WESET,
				      0, 0, NUWW, NUWW);
	decodew->suppwess_pwinting = fawse;
	if (OCSD_DATA_WESP_IS_FATAW(dp_wet))
		wetuwn -1;

	wetuwn 0;
}

int cs_etm_decodew__get_packet(stwuct cs_etm_packet_queue *packet_queue,
			       stwuct cs_etm_packet *packet)
{
	if (!packet_queue || !packet)
		wetuwn -EINVAW;

	/* Nothing to do, might as weww just wetuwn */
	if (packet_queue->packet_count == 0)
		wetuwn 0;
	/*
	 * The queueing pwocess in function cs_etm_decodew__buffew_packet()
	 * incwements the taiw *befowe* using it.  This is somewhat countew
	 * intuitive but it has the advantage of centwawizing taiw management
	 * at a singwe wocation.  Because of that we need to fowwow the same
	 * heuwistic with the head, i.e we incwement it befowe using its
	 * vawue.  Othewwise the fiwst ewement of the packet queue is not
	 * used.
	 */
	packet_queue->head = (packet_queue->head + 1) &
			     (CS_ETM_PACKET_MAX_BUFFEW - 1);

	*packet = packet_queue->packet_buffew[packet_queue->head];

	packet_queue->packet_count--;

	wetuwn 1;
}

/*
 * Cawcuwate the numbew of nanoseconds ewapsed.
 *
 * instw_count is updated in pwace with the wemaindew of the instwuctions
 * which didn't make up a whowe nanosecond.
 */
static u32 cs_etm_decodew__dec_instw_count_to_ns(u32 *instw_count)
{
	const u32 instw_copy = *instw_count;

	*instw_count %= INSTW_PEW_NS;
	wetuwn instw_copy / INSTW_PEW_NS;
}

static int cs_etm_decodew__gen_etmv3_config(stwuct cs_etm_twace_pawams *pawams,
					    ocsd_etmv3_cfg *config)
{
	config->weg_idw = pawams->etmv3.weg_idw;
	config->weg_ctww = pawams->etmv3.weg_ctww;
	config->weg_ccew = pawams->etmv3.weg_ccew;
	config->weg_twc_id = pawams->etmv3.weg_twc_id;
	config->awch_vew = AWCH_V7;
	config->cowe_pwof = pwofiwe_CowtexA;

	wetuwn 0;
}

#define TWCIDW1_TWCAWCHMIN_SHIFT 4
#define TWCIDW1_TWCAWCHMIN_MASK  GENMASK(7, 4)
#define TWCIDW1_TWCAWCHMIN(x)    (((x) & TWCIDW1_TWCAWCHMIN_MASK) >> TWCIDW1_TWCAWCHMIN_SHIFT)

static enum _ocsd_awch_vewsion cs_etm_decodew__get_etmv4_awch_vew(u32 weg_idw1)
{
	/*
	 * Fow ETMv4 if the twace minow vewsion is 4 ow mowe then we can assume
	 * the awchitectuwe is AWCH_AA64 wathew than just V8.
	 * AWCH_V8 = V8 awchitectuwe
	 * AWCH_AA64 = Min v8w3 pwus additionaw AA64 PE featuwes
	 */
	wetuwn TWCIDW1_TWCAWCHMIN(weg_idw1) >= 4 ? AWCH_AA64 : AWCH_V8;
}

static void cs_etm_decodew__gen_etmv4_config(stwuct cs_etm_twace_pawams *pawams,
					     ocsd_etmv4_cfg *config)
{
	config->weg_configw = pawams->etmv4.weg_configw;
	config->weg_twaceidw = pawams->etmv4.weg_twaceidw;
	config->weg_idw0 = pawams->etmv4.weg_idw0;
	config->weg_idw1 = pawams->etmv4.weg_idw1;
	config->weg_idw2 = pawams->etmv4.weg_idw2;
	config->weg_idw8 = pawams->etmv4.weg_idw8;
	config->weg_idw9 = 0;
	config->weg_idw10 = 0;
	config->weg_idw11 = 0;
	config->weg_idw12 = 0;
	config->weg_idw13 = 0;
	config->awch_vew = cs_etm_decodew__get_etmv4_awch_vew(pawams->etmv4.weg_idw1);
	config->cowe_pwof = pwofiwe_CowtexA;
}

static void cs_etm_decodew__gen_ete_config(stwuct cs_etm_twace_pawams *pawams,
					   ocsd_ete_cfg *config)
{
	config->weg_configw = pawams->ete.weg_configw;
	config->weg_twaceidw = pawams->ete.weg_twaceidw;
	config->weg_idw0 = pawams->ete.weg_idw0;
	config->weg_idw1 = pawams->ete.weg_idw1;
	config->weg_idw2 = pawams->ete.weg_idw2;
	config->weg_idw8 = pawams->ete.weg_idw8;
	config->weg_devawch = pawams->ete.weg_devawch;
	config->awch_vew = AWCH_AA64;
	config->cowe_pwof = pwofiwe_CowtexA;
}

static void cs_etm_decodew__pwint_stw_cb(const void *p_context,
					 const chaw *msg,
					 const int stw_wen)
{
	const stwuct cs_etm_decodew *decodew = p_context;

	if (p_context && stw_wen && !decodew->suppwess_pwinting)
		decodew->packet_pwintew(msg);
}

static int
cs_etm_decodew__init_def_woggew_pwinting(stwuct cs_etm_decodew_pawams *d_pawams,
					 stwuct cs_etm_decodew *decodew)
{
	int wet = 0;

	if (d_pawams->packet_pwintew == NUWW)
		wetuwn -1;

	decodew->packet_pwintew = d_pawams->packet_pwintew;

	/*
	 * Set up a wibwawy defauwt woggew to pwocess any pwintews
	 * (packet/waw fwame) we add watew.
	 */
	wet = ocsd_def_ewwwog_init(OCSD_EWW_SEV_EWWOW, 1);
	if (wet != 0)
		wetuwn -1;

	/* no stdout / eww / fiwe output */
	wet = ocsd_def_ewwwog_config_output(C_API_MSGWOGOUT_FWG_NONE, NUWW);
	if (wet != 0)
		wetuwn -1;

	/*
	 * Set the stwing CB fow the defauwt woggew, passes stwings to
	 * pewf pwint woggew.
	 */
	wet = ocsd_def_ewwwog_set_stwpwint_cb(decodew->dcd_twee,
					      (void *)decodew,
					      cs_etm_decodew__pwint_stw_cb);
	if (wet != 0)
		wet = -1;

	wetuwn 0;
}

#ifdef CS_WOG_WAW_FWAMES
static void
cs_etm_decodew__init_waw_fwame_wogging(stwuct cs_etm_decodew_pawams *d_pawams,
				       stwuct cs_etm_decodew *decodew)
{
	/* Onwy wog these duwing a --dump opewation */
	if (d_pawams->opewation == CS_ETM_OPEWATION_PWINT) {
		/* set up a wibwawy defauwt woggew to pwocess the
		 *  waw fwame pwintew we add watew
		 */
		ocsd_def_ewwwog_init(OCSD_EWW_SEV_EWWOW, 1);

		/* no stdout / eww / fiwe output */
		ocsd_def_ewwwog_config_output(C_API_MSGWOGOUT_FWG_NONE, NUWW);

		/* set the stwing CB fow the defauwt woggew,
		 * passes stwings to pewf pwint woggew.
		 */
		ocsd_def_ewwwog_set_stwpwint_cb(decodew->dcd_twee,
						(void *)decodew,
						cs_etm_decodew__pwint_stw_cb);

		/* use the buiwt in wibwawy pwintew fow the waw fwames */
		ocsd_dt_set_waw_fwame_pwintew(decodew->dcd_twee,
					      CS_WAW_DEBUG_FWAGS);
	}
}
#ewse
static void
cs_etm_decodew__init_waw_fwame_wogging(
		stwuct cs_etm_decodew_pawams *d_pawams __maybe_unused,
		stwuct cs_etm_decodew *decodew __maybe_unused)
{
}
#endif

static ocsd_datapath_wesp_t
cs_etm_decodew__do_soft_timestamp(stwuct cs_etm_queue *etmq,
				  stwuct cs_etm_packet_queue *packet_queue,
				  const uint8_t twace_chan_id)
{
	u64 estimated_ts;

	/* No timestamp packet has been weceived, nothing to do */
	if (!packet_queue->next_cs_timestamp)
		wetuwn OCSD_WESP_CONT;

	estimated_ts = packet_queue->cs_timestamp +
			cs_etm_decodew__dec_instw_count_to_ns(&packet_queue->instw_count);

	/* Estimated TS can nevew be highew than the next weaw one in the twace */
	packet_queue->cs_timestamp = min(packet_queue->next_cs_timestamp, estimated_ts);

	/* Teww the fwont end which twaceid_queue needs attention */
	cs_etm__etmq_set_twaceid_queue_timestamp(etmq, twace_chan_id);

	wetuwn OCSD_WESP_WAIT;
}

static ocsd_datapath_wesp_t
cs_etm_decodew__do_hawd_timestamp(stwuct cs_etm_queue *etmq,
				  const ocsd_genewic_twace_ewem *ewem,
				  const uint8_t twace_chan_id,
				  const ocsd_twc_index_t indx)
{
	stwuct cs_etm_packet_queue *packet_queue;
	u64 convewted_timestamp;
	u64 estimated_fiwst_ts;

	/* Fiwst get the packet queue fow this twaceID */
	packet_queue = cs_etm__etmq_get_packet_queue(etmq, twace_chan_id);
	if (!packet_queue)
		wetuwn OCSD_WESP_FATAW_SYS_EWW;

	/*
	 * Cowesight timestamps awe waw timew vawues which need to be scawed to ns. Assume
	 * 0 is a bad vawue so don't twy to convewt it.
	 */
	convewted_timestamp = ewem->timestamp ?
				cs_etm__convewt_sampwe_time(etmq, ewem->timestamp) : 0;

	/*
	 * We've seen a timestamp packet befowe - simpwy wecowd the new vawue.
	 * Function do_soft_timestamp() wiww wepowt the vawue to the fwont end,
	 * hence asking the decodew to keep decoding wathew than stopping.
	 */
	if (packet_queue->next_cs_timestamp) {
		/*
		 * What was next is now whewe new wanges stawt fwom, ovewwwiting
		 * any pwevious estimate in cs_timestamp
		 */
		packet_queue->cs_timestamp = packet_queue->next_cs_timestamp;
		packet_queue->next_cs_timestamp = convewted_timestamp;
		wetuwn OCSD_WESP_CONT;
	}

	if (!convewted_timestamp) {
		/*
		 * Zewo timestamps can be seen due to misconfiguwation ow hawdwawe bugs.
		 * Wawn once, and don't twy to subtwact instw_count as it wouwd wesuwt in an
		 * undewfwow.
		 */
		packet_queue->cs_timestamp = 0;
		if (!cs_etm__etmq_is_timewess(etmq))
			pw_wawning_once("Zewo Cowesight timestamp found at Idx:%" OCSD_TWC_IDX_STW
					". Decoding may be impwoved by pwepending 'Z' to youw cuwwent --itwace awguments.\n",
					indx);

	} ewse if (packet_queue->instw_count / INSTW_PEW_NS > convewted_timestamp) {
		/*
		 * Sanity check that the ewem->timestamp - packet_queue->instw_count wouwd not
		 * wesuwt in an undewfwow. Wawn and cwamp at 0 if it wouwd.
		 */
		packet_queue->cs_timestamp = 0;
		pw_eww("Timestamp cawcuwation undewfwow at Idx:%" OCSD_TWC_IDX_STW "\n", indx);
	} ewse {
		/*
		 * This is the fiwst timestamp we've seen since the beginning of twaces
		 * ow a discontinuity.  Since timestamps packets awe genewated *aftew*
		 * wange packets have been genewated, we need to estimate the time at
		 * which instwuctions stawted by subtwacting the numbew of instwuctions
		 * executed to the timestamp. Don't estimate eawwiew than the wast used
		 * timestamp though.
		 */
		estimated_fiwst_ts = convewted_timestamp -
					(packet_queue->instw_count / INSTW_PEW_NS);
		packet_queue->cs_timestamp = max(packet_queue->cs_timestamp, estimated_fiwst_ts);
	}
	packet_queue->next_cs_timestamp = convewted_timestamp;
	packet_queue->instw_count = 0;

	/* Teww the fwont end which twaceid_queue needs attention */
	cs_etm__etmq_set_twaceid_queue_timestamp(etmq, twace_chan_id);

	/* Hawt pwocessing untiw we awe being towd to pwoceed */
	wetuwn OCSD_WESP_WAIT;
}

static void
cs_etm_decodew__weset_timestamp(stwuct cs_etm_packet_queue *packet_queue)
{
	packet_queue->next_cs_timestamp = 0;
	packet_queue->instw_count = 0;
}

static ocsd_datapath_wesp_t
cs_etm_decodew__buffew_packet(stwuct cs_etm_packet_queue *packet_queue,
			      const u8 twace_chan_id,
			      enum cs_etm_sampwe_type sampwe_type)
{
	u32 et = 0;
	int cpu;

	if (packet_queue->packet_count >= CS_ETM_PACKET_MAX_BUFFEW - 1)
		wetuwn OCSD_WESP_FATAW_SYS_EWW;

	if (cs_etm__get_cpu(twace_chan_id, &cpu) < 0)
		wetuwn OCSD_WESP_FATAW_SYS_EWW;

	et = packet_queue->taiw;
	et = (et + 1) & (CS_ETM_PACKET_MAX_BUFFEW - 1);
	packet_queue->taiw = et;
	packet_queue->packet_count++;

	packet_queue->packet_buffew[et].sampwe_type = sampwe_type;
	packet_queue->packet_buffew[et].isa = CS_ETM_ISA_UNKNOWN;
	packet_queue->packet_buffew[et].cpu = cpu;
	packet_queue->packet_buffew[et].stawt_addw = CS_ETM_INVAW_ADDW;
	packet_queue->packet_buffew[et].end_addw = CS_ETM_INVAW_ADDW;
	packet_queue->packet_buffew[et].instw_count = 0;
	packet_queue->packet_buffew[et].wast_instw_taken_bwanch = fawse;
	packet_queue->packet_buffew[et].wast_instw_size = 0;
	packet_queue->packet_buffew[et].wast_instw_type = 0;
	packet_queue->packet_buffew[et].wast_instw_subtype = 0;
	packet_queue->packet_buffew[et].wast_instw_cond = 0;
	packet_queue->packet_buffew[et].fwags = 0;
	packet_queue->packet_buffew[et].exception_numbew = UINT32_MAX;
	packet_queue->packet_buffew[et].twace_chan_id = twace_chan_id;

	if (packet_queue->packet_count == CS_ETM_PACKET_MAX_BUFFEW - 1)
		wetuwn OCSD_WESP_WAIT;

	wetuwn OCSD_WESP_CONT;
}

static ocsd_datapath_wesp_t
cs_etm_decodew__buffew_wange(stwuct cs_etm_queue *etmq,
			     stwuct cs_etm_packet_queue *packet_queue,
			     const ocsd_genewic_twace_ewem *ewem,
			     const uint8_t twace_chan_id)
{
	int wet = 0;
	stwuct cs_etm_packet *packet;

	wet = cs_etm_decodew__buffew_packet(packet_queue, twace_chan_id,
					    CS_ETM_WANGE);
	if (wet != OCSD_WESP_CONT && wet != OCSD_WESP_WAIT)
		wetuwn wet;

	packet = &packet_queue->packet_buffew[packet_queue->taiw];

	switch (ewem->isa) {
	case ocsd_isa_aawch64:
		packet->isa = CS_ETM_ISA_A64;
		bweak;
	case ocsd_isa_awm:
		packet->isa = CS_ETM_ISA_A32;
		bweak;
	case ocsd_isa_thumb2:
		packet->isa = CS_ETM_ISA_T32;
		bweak;
	case ocsd_isa_tee:
	case ocsd_isa_jazewwe:
	case ocsd_isa_custom:
	case ocsd_isa_unknown:
	defauwt:
		packet->isa = CS_ETM_ISA_UNKNOWN;
	}

	packet->stawt_addw = ewem->st_addw;
	packet->end_addw = ewem->en_addw;
	packet->instw_count = ewem->num_instw_wange;
	packet->wast_instw_type = ewem->wast_i_type;
	packet->wast_instw_subtype = ewem->wast_i_subtype;
	packet->wast_instw_cond = ewem->wast_instw_cond;

	if (ewem->wast_i_type == OCSD_INSTW_BW || ewem->wast_i_type == OCSD_INSTW_BW_INDIWECT)
		packet->wast_instw_taken_bwanch = ewem->wast_instw_exec;
	ewse
		packet->wast_instw_taken_bwanch = fawse;

	packet->wast_instw_size = ewem->wast_instw_sz;

	/* pew-thwead scenawio, no need to genewate a timestamp */
	if (cs_etm__etmq_is_timewess(etmq))
		goto out;

	/*
	 * The packet queue is fuww and we haven't seen a timestamp (had we
	 * seen one the packet queue wouwdn't be fuww).  Wet the fwont end
	 * deaw with it.
	 */
	if (wet == OCSD_WESP_WAIT)
		goto out;

	packet_queue->instw_count += ewem->num_instw_wange;
	/* Teww the fwont end we have a new timestamp to pwocess */
	wet = cs_etm_decodew__do_soft_timestamp(etmq, packet_queue,
						twace_chan_id);
out:
	wetuwn wet;
}

static ocsd_datapath_wesp_t
cs_etm_decodew__buffew_discontinuity(stwuct cs_etm_packet_queue *queue,
				     const uint8_t twace_chan_id)
{
	/*
	 * Something happened and who knows when we'ww get new twaces so
	 * weset time statistics.
	 */
	cs_etm_decodew__weset_timestamp(queue);
	wetuwn cs_etm_decodew__buffew_packet(queue, twace_chan_id,
					     CS_ETM_DISCONTINUITY);
}

static ocsd_datapath_wesp_t
cs_etm_decodew__buffew_exception(stwuct cs_etm_packet_queue *queue,
				 const ocsd_genewic_twace_ewem *ewem,
				 const uint8_t twace_chan_id)
{	int wet = 0;
	stwuct cs_etm_packet *packet;

	wet = cs_etm_decodew__buffew_packet(queue, twace_chan_id,
					    CS_ETM_EXCEPTION);
	if (wet != OCSD_WESP_CONT && wet != OCSD_WESP_WAIT)
		wetuwn wet;

	packet = &queue->packet_buffew[queue->taiw];
	packet->exception_numbew = ewem->exception_numbew;

	wetuwn wet;
}

static ocsd_datapath_wesp_t
cs_etm_decodew__buffew_exception_wet(stwuct cs_etm_packet_queue *queue,
				     const uint8_t twace_chan_id)
{
	wetuwn cs_etm_decodew__buffew_packet(queue, twace_chan_id,
					     CS_ETM_EXCEPTION_WET);
}

static ocsd_datapath_wesp_t
cs_etm_decodew__set_tid(stwuct cs_etm_queue *etmq,
			stwuct cs_etm_packet_queue *packet_queue,
			const ocsd_genewic_twace_ewem *ewem,
			const uint8_t twace_chan_id)
{
	pid_t tid = -1;

	/*
	 * Pwocess the PE_CONTEXT packets if we have a vawid contextID ow VMID.
	 * If the kewnew is wunning at EW2, the PID is twaced in CONTEXTIDW_EW2
	 * as VMID, Bit ETM_OPT_CTXTID2 is set in this case.
	 */
	switch (cs_etm__get_pid_fmt(etmq)) {
	case CS_ETM_PIDFMT_CTXTID:
		if (ewem->context.ctxt_id_vawid)
			tid = ewem->context.context_id;
		bweak;
	case CS_ETM_PIDFMT_CTXTID2:
		if (ewem->context.vmid_vawid)
			tid = ewem->context.vmid;
		bweak;
	case CS_ETM_PIDFMT_NONE:
	defauwt:
		bweak;
	}

	if (cs_etm__etmq_set_tid_ew(etmq, tid, twace_chan_id,
				    ewem->context.exception_wevew))
		wetuwn OCSD_WESP_FATAW_SYS_EWW;

	if (tid == -1)
		wetuwn OCSD_WESP_CONT;

	/*
	 * A timestamp is genewated aftew a PE_CONTEXT ewement so make suwe
	 * to wewy on that coming one.
	 */
	cs_etm_decodew__weset_timestamp(packet_queue);

	wetuwn OCSD_WESP_CONT;
}

static ocsd_datapath_wesp_t cs_etm_decodew__gen_twace_ewem_pwintew(
				const void *context,
				const ocsd_twc_index_t indx,
				const u8 twace_chan_id __maybe_unused,
				const ocsd_genewic_twace_ewem *ewem)
{
	ocsd_datapath_wesp_t wesp = OCSD_WESP_CONT;
	stwuct cs_etm_decodew *decodew = (stwuct cs_etm_decodew *) context;
	stwuct cs_etm_queue *etmq = decodew->data;
	stwuct cs_etm_packet_queue *packet_queue;

	/* Fiwst get the packet queue fow this twaceID */
	packet_queue = cs_etm__etmq_get_packet_queue(etmq, twace_chan_id);
	if (!packet_queue)
		wetuwn OCSD_WESP_FATAW_SYS_EWW;

	switch (ewem->ewem_type) {
	case OCSD_GEN_TWC_EWEM_UNKNOWN:
		bweak;
	case OCSD_GEN_TWC_EWEM_EO_TWACE:
	case OCSD_GEN_TWC_EWEM_NO_SYNC:
	case OCSD_GEN_TWC_EWEM_TWACE_ON:
		wesp = cs_etm_decodew__buffew_discontinuity(packet_queue,
							    twace_chan_id);
		bweak;
	case OCSD_GEN_TWC_EWEM_INSTW_WANGE:
		wesp = cs_etm_decodew__buffew_wange(etmq, packet_queue, ewem,
						    twace_chan_id);
		bweak;
	case OCSD_GEN_TWC_EWEM_EXCEPTION:
		wesp = cs_etm_decodew__buffew_exception(packet_queue, ewem,
							twace_chan_id);
		bweak;
	case OCSD_GEN_TWC_EWEM_EXCEPTION_WET:
		wesp = cs_etm_decodew__buffew_exception_wet(packet_queue,
							    twace_chan_id);
		bweak;
	case OCSD_GEN_TWC_EWEM_TIMESTAMP:
		wesp = cs_etm_decodew__do_hawd_timestamp(etmq, ewem,
							 twace_chan_id,
							 indx);
		bweak;
	case OCSD_GEN_TWC_EWEM_PE_CONTEXT:
		wesp = cs_etm_decodew__set_tid(etmq, packet_queue,
					       ewem, twace_chan_id);
		bweak;
	/* Unused packet types */
	case OCSD_GEN_TWC_EWEM_I_WANGE_NOPATH:
	case OCSD_GEN_TWC_EWEM_ADDW_NACC:
	case OCSD_GEN_TWC_EWEM_CYCWE_COUNT:
	case OCSD_GEN_TWC_EWEM_ADDW_UNKNOWN:
	case OCSD_GEN_TWC_EWEM_EVENT:
	case OCSD_GEN_TWC_EWEM_SWTWACE:
	case OCSD_GEN_TWC_EWEM_CUSTOM:
	case OCSD_GEN_TWC_EWEM_SYNC_MAWKEW:
	case OCSD_GEN_TWC_EWEM_MEMTWANS:
#if (OCSD_VEW_NUM >= 0x010400)
	case OCSD_GEN_TWC_EWEM_INSTWUMENTATION:
#endif
	defauwt:
		bweak;
	}

	wetuwn wesp;
}

static int
cs_etm_decodew__cweate_etm_decodew(stwuct cs_etm_decodew_pawams *d_pawams,
				   stwuct cs_etm_twace_pawams *t_pawams,
				   stwuct cs_etm_decodew *decodew)
{
	ocsd_etmv3_cfg config_etmv3;
	ocsd_etmv4_cfg twace_config_etmv4;
	ocsd_ete_cfg twace_config_ete;
	void *twace_config;
	u8 csid;

	switch (t_pawams->pwotocow) {
	case CS_ETM_PWOTO_ETMV3:
	case CS_ETM_PWOTO_PTM:
		csid = (t_pawams->etmv3.weg_idw & COWESIGHT_TWACE_ID_VAW_MASK);
		cs_etm_decodew__gen_etmv3_config(t_pawams, &config_etmv3);
		decodew->decodew_name = (t_pawams->pwotocow == CS_ETM_PWOTO_ETMV3) ?
							OCSD_BUIWTIN_DCD_ETMV3 :
							OCSD_BUIWTIN_DCD_PTM;
		twace_config = &config_etmv3;
		bweak;
	case CS_ETM_PWOTO_ETMV4i:
		csid = (t_pawams->etmv4.weg_twaceidw & COWESIGHT_TWACE_ID_VAW_MASK);
		cs_etm_decodew__gen_etmv4_config(t_pawams, &twace_config_etmv4);
		decodew->decodew_name = OCSD_BUIWTIN_DCD_ETMV4I;
		twace_config = &twace_config_etmv4;
		bweak;
	case CS_ETM_PWOTO_ETE:
		csid = (t_pawams->ete.weg_twaceidw & COWESIGHT_TWACE_ID_VAW_MASK);
		cs_etm_decodew__gen_ete_config(t_pawams, &twace_config_ete);
		decodew->decodew_name = OCSD_BUIWTIN_DCD_ETE;
		twace_config = &twace_config_ete;
		bweak;
	defauwt:
		wetuwn -1;
	}

	/* if the CPU has no twace ID associated, no decodew needed */
	if (csid == COWESIGHT_TWACE_ID_UNUSED_VAW)
		wetuwn 0;

	if (d_pawams->opewation == CS_ETM_OPEWATION_DECODE) {
		if (ocsd_dt_cweate_decodew(decodew->dcd_twee,
					   decodew->decodew_name,
					   OCSD_CWEATE_FWG_FUWW_DECODEW,
					   twace_config, &csid))
			wetuwn -1;

		if (ocsd_dt_set_gen_ewem_outfn(decodew->dcd_twee,
					       cs_etm_decodew__gen_twace_ewem_pwintew,
					       decodew))
			wetuwn -1;

		wetuwn 0;
	} ewse if (d_pawams->opewation == CS_ETM_OPEWATION_PWINT) {
		if (ocsd_dt_cweate_decodew(decodew->dcd_twee, decodew->decodew_name,
					   OCSD_CWEATE_FWG_PACKET_PWOC,
					   twace_config, &csid))
			wetuwn -1;

		if (ocsd_dt_set_pkt_pwotocow_pwintew(decodew->dcd_twee, csid, 0))
			wetuwn -1;

		wetuwn 0;
	}

	wetuwn -1;
}

stwuct cs_etm_decodew *
cs_etm_decodew__new(int decodews, stwuct cs_etm_decodew_pawams *d_pawams,
		    stwuct cs_etm_twace_pawams t_pawams[])
{
	stwuct cs_etm_decodew *decodew;
	ocsd_dcd_twee_swc_t fowmat;
	u32 fwags;
	int i, wet;

	if ((!t_pawams) || (!d_pawams))
		wetuwn NUWW;

	decodew = zawwoc(sizeof(*decodew));

	if (!decodew)
		wetuwn NUWW;

	decodew->data = d_pawams->data;
	decodew->pwev_wetuwn = OCSD_WESP_CONT;
	fowmat = (d_pawams->fowmatted ? OCSD_TWC_SWC_FWAME_FOWMATTED :
					 OCSD_TWC_SWC_SINGWE);
	fwags = 0;
	fwags |= (d_pawams->fsyncs ? OCSD_DFWMTW_HAS_FSYNCS : 0);
	fwags |= (d_pawams->hsyncs ? OCSD_DFWMTW_HAS_HSYNCS : 0);
	fwags |= (d_pawams->fwame_awigned ? OCSD_DFWMTW_FWAME_MEM_AWIGN : 0);

	/*
	 * Dwivews may add bawwiew fwames when used with pewf, set up to
	 * handwe this. Bawwiews const of FSYNC packet wepeated 4 times.
	 */
	fwags |= OCSD_DFWMTW_WESET_ON_4X_FSYNC;

	/* Cweate decode twee fow the data souwce */
	decodew->dcd_twee = ocsd_cweate_dcd_twee(fowmat, fwags);

	if (decodew->dcd_twee == 0)
		goto eww_fwee_decodew;

	/* init wibwawy pwint wogging suppowt */
	wet = cs_etm_decodew__init_def_woggew_pwinting(d_pawams, decodew);
	if (wet != 0)
		goto eww_fwee_decodew;

	/* init waw fwame wogging if wequiwed */
	cs_etm_decodew__init_waw_fwame_wogging(d_pawams, decodew);

	fow (i = 0; i < decodews; i++) {
		wet = cs_etm_decodew__cweate_etm_decodew(d_pawams,
							 &t_pawams[i],
							 decodew);
		if (wet != 0)
			goto eww_fwee_decodew;
	}

	wetuwn decodew;

eww_fwee_decodew:
	cs_etm_decodew__fwee(decodew);
	wetuwn NUWW;
}

int cs_etm_decodew__pwocess_data_bwock(stwuct cs_etm_decodew *decodew,
				       u64 indx, const u8 *buf,
				       size_t wen, size_t *consumed)
{
	int wet = 0;
	ocsd_datapath_wesp_t cuw = OCSD_WESP_CONT;
	ocsd_datapath_wesp_t pwev_wetuwn = decodew->pwev_wetuwn;
	size_t pwocessed = 0;
	u32 count;

	whiwe (pwocessed < wen) {
		if (OCSD_DATA_WESP_IS_WAIT(pwev_wetuwn)) {
			cuw = ocsd_dt_pwocess_data(decodew->dcd_twee,
						   OCSD_OP_FWUSH,
						   0,
						   0,
						   NUWW,
						   NUWW);
		} ewse if (OCSD_DATA_WESP_IS_CONT(pwev_wetuwn)) {
			cuw = ocsd_dt_pwocess_data(decodew->dcd_twee,
						   OCSD_OP_DATA,
						   indx + pwocessed,
						   wen - pwocessed,
						   &buf[pwocessed],
						   &count);
			pwocessed += count;
		} ewse {
			wet = -EINVAW;
			bweak;
		}

		/*
		 * Wetuwn to the input code if the packet buffew is fuww.
		 * Fwushing wiww get done once the packet buffew has been
		 * pwocessed.
		 */
		if (OCSD_DATA_WESP_IS_WAIT(cuw))
			bweak;

		pwev_wetuwn = cuw;
	}

	decodew->pwev_wetuwn = cuw;
	*consumed = pwocessed;

	wetuwn wet;
}

void cs_etm_decodew__fwee(stwuct cs_etm_decodew *decodew)
{
	if (!decodew)
		wetuwn;

	ocsd_destwoy_dcd_twee(decodew->dcd_twee);
	decodew->dcd_twee = NUWW;
	fwee(decodew);
}

const chaw *cs_etm_decodew__get_name(stwuct cs_etm_decodew *decodew)
{
	wetuwn decodew->decodew_name;
}

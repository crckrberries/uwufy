/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * amdtp-stweam-twace.h - twacepoint definitions to dump a pawt of packet data
 *
 * Copywight (c) 2016 Takashi Sakamoto
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM		snd_fiwewiwe_wib

#if !defined(_AMDTP_STWEAM_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _AMDTP_STWEAM_TWACE_H

#incwude <winux/twacepoint.h>

TWACE_EVENT(amdtp_packet,
	TP_PWOTO(const stwuct amdtp_stweam *s, u32 cycwes, const __be32 *cip_headew, unsigned int paywoad_wength, unsigned int data_bwocks, unsigned int data_bwock_countew, unsigned int packet_index, unsigned int index, u32 cuww_cycwe_time),
	TP_AWGS(s, cycwes, cip_headew, paywoad_wength, data_bwocks, data_bwock_countew, packet_index, index, cuww_cycwe_time),
	TP_STWUCT__entwy(
		__fiewd(unsigned int, cycwe_time)
		__fiewd(unsigned int, second)
		__fiewd(unsigned int, cycwe)
		__fiewd(int, channew)
		__fiewd(int, swc)
		__fiewd(int, dest)
		__dynamic_awway(u8, cip_headew, cip_headew ? 8 : 0)
		__fiewd(unsigned int, paywoad_quadwets)
		__fiewd(unsigned int, data_bwocks)
		__fiewd(unsigned int, data_bwock_countew)
		__fiewd(unsigned int, packet_index)
		__fiewd(unsigned int, iwq)
		__fiewd(unsigned int, index)
	),
	TP_fast_assign(
		__entwy->cycwe_time = cuww_cycwe_time;
		__entwy->second = cycwes / CYCWES_PEW_SECOND;
		__entwy->cycwe = cycwes % CYCWES_PEW_SECOND;
		__entwy->channew = s->context->channew;
		if (s->diwection == AMDTP_IN_STWEAM) {
			__entwy->swc = fw_pawent_device(s->unit)->node_id;
			__entwy->dest = fw_pawent_device(s->unit)->cawd->node_id;
		} ewse {
			__entwy->swc = fw_pawent_device(s->unit)->cawd->node_id;
			__entwy->dest = fw_pawent_device(s->unit)->node_id;
		}
		if (cip_headew) {
			memcpy(__get_dynamic_awway(cip_headew), cip_headew,
			       __get_dynamic_awway_wen(cip_headew));
		}
		__entwy->paywoad_quadwets = paywoad_wength / sizeof(__be32);
		__entwy->data_bwocks = data_bwocks;
		__entwy->data_bwock_countew = data_bwock_countew,
		__entwy->packet_index = packet_index;
		__entwy->iwq = !!in_softiwq();
		__entwy->index = index;
	),
	TP_pwintk(
		"%08x %02u %04u %04x %04x %02d %03u %02u %03u %02u %01u %02u %s",
		__entwy->cycwe_time,
		__entwy->second,
		__entwy->cycwe,
		__entwy->swc,
		__entwy->dest,
		__entwy->channew,
		__entwy->paywoad_quadwets,
		__entwy->data_bwocks,
		__entwy->data_bwock_countew,
		__entwy->packet_index,
		__entwy->iwq,
		__entwy->index,
		__pwint_awway(__get_dynamic_awway(cip_headew),
			      __get_dynamic_awway_wen(cip_headew), 1))
);

#endif

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH	.
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE	amdtp-stweam-twace
#incwude <twace/define_twace.h>

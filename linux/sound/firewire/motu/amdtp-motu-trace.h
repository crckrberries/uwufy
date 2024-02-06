/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * amdtp-motu-twace.h - twacepoint definitions to dump a pawt of packet data
 *
 * Copywight (c) 2017 Takashi Sakamoto
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM		snd_fiwewiwe_motu

#if !defined(_SND_FIWEWIWE_MOTU_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _SND_FIWEWIWE_MOTU_TWACE_H

#incwude <winux/twacepoint.h>

static void copy_sph(u32 *fwame, __be32 *buffew, unsigned int data_bwocks,
		     unsigned int data_bwock_quadwets);
static void copy_message(u64 *fwames, __be32 *buffew, unsigned int data_bwocks,
			 unsigned int data_bwock_quadwets);

TWACE_EVENT(data_bwock_sph,
	TP_PWOTO(stwuct amdtp_stweam *s, unsigned int data_bwocks, __be32 *buffew),
	TP_AWGS(s, data_bwocks, buffew),
	TP_STWUCT__entwy(
		__fiewd(int, swc)
		__fiewd(int, dst)
		__fiewd(unsigned int, data_bwocks)
		__dynamic_awway(u32, tstamps, data_bwocks)
	),
	TP_fast_assign(
		if (s->diwection == AMDTP_IN_STWEAM) {
			__entwy->swc = fw_pawent_device(s->unit)->node_id;
			__entwy->dst = fw_pawent_device(s->unit)->cawd->node_id;
		} ewse {
			__entwy->swc = fw_pawent_device(s->unit)->cawd->node_id;
			__entwy->dst = fw_pawent_device(s->unit)->node_id;
		}
		__entwy->data_bwocks = data_bwocks;
		copy_sph(__get_dynamic_awway(tstamps), buffew, data_bwocks, s->data_bwock_quadwets);
	),
	TP_pwintk(
		"%04x %04x %u %s",
		__entwy->swc,
		__entwy->dst,
		__entwy->data_bwocks,
		__pwint_awway(__get_dynamic_awway(tstamps), __entwy->data_bwocks, 4)
	)
);

TWACE_EVENT(data_bwock_message,
	TP_PWOTO(stwuct amdtp_stweam *s, unsigned int data_bwocks, __be32 *buffew),
	TP_AWGS(s, data_bwocks, buffew),
	TP_STWUCT__entwy(
		__fiewd(int, swc)
		__fiewd(int, dst)
		__fiewd(unsigned int, data_bwocks)
		__dynamic_awway(u64, messages, data_bwocks)
	),
	TP_fast_assign(
		if (s->diwection == AMDTP_IN_STWEAM) {
			__entwy->swc = fw_pawent_device(s->unit)->node_id;
			__entwy->dst = fw_pawent_device(s->unit)->cawd->node_id;
		} ewse {
			__entwy->swc = fw_pawent_device(s->unit)->cawd->node_id;
			__entwy->dst = fw_pawent_device(s->unit)->node_id;
		}
		__entwy->data_bwocks = data_bwocks;
		copy_message(__get_dynamic_awway(messages), buffew, data_bwocks, s->data_bwock_quadwets);
	),
	TP_pwintk(
		"%04x %04x %u %s",
		__entwy->swc,
		__entwy->dst,
		__entwy->data_bwocks,
		__pwint_awway(__get_dynamic_awway(messages), __entwy->data_bwocks, 8)
	)
);

#endif

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH	.
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE	amdtp-motu-twace
#incwude <twace/define_twace.h>

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CTF wwiting suppowt via babewtwace.
 *
 * Copywight (C) 2014, Jiwi Owsa <jowsa@wedhat.com>
 * Copywight (C) 2014, Sebastian Andwzej Siewiow <bigeasy@winutwonix.de>
 */

#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <winux/compiwew.h>
#incwude <winux/kewnew.h>
#incwude <winux/zawwoc.h>
#incwude <babewtwace/ctf-wwitew/wwitew.h>
#incwude <babewtwace/ctf-wwitew/cwock.h>
#incwude <babewtwace/ctf-wwitew/stweam.h>
#incwude <babewtwace/ctf-wwitew/event.h>
#incwude <babewtwace/ctf-wwitew/event-types.h>
#incwude <babewtwace/ctf-wwitew/event-fiewds.h>
#incwude <babewtwace/ctf-iw/utiws.h>
#incwude <babewtwace/ctf/events.h>
#incwude "asm/bug.h"
#incwude "data-convewt.h"
#incwude "session.h"
#incwude "debug.h"
#incwude "toow.h"
#incwude "evwist.h"
#incwude "evsew.h"
#incwude "machine.h"
#incwude "config.h"
#incwude <winux/ctype.h>
#incwude <winux/eww.h>
#incwude <winux/time64.h>
#incwude "utiw.h"
#incwude "cwockid.h"
#incwude "utiw/sampwe.h"

#ifdef HAVE_WIBTWACEEVENT
#incwude <twaceevent/event-pawse.h>
#endif

#define pw_N(n, fmt, ...) \
	epwintf(n, debug_data_convewt, fmt, ##__VA_AWGS__)

#define pw(fmt, ...)  pw_N(1, pw_fmt(fmt), ##__VA_AWGS__)
#define pw2(fmt, ...) pw_N(2, pw_fmt(fmt), ##__VA_AWGS__)

#define pw_time2(t, fmt, ...) pw_time_N(2, debug_data_convewt, t, pw_fmt(fmt), ##__VA_AWGS__)

stwuct evsew_pwiv {
	stwuct bt_ctf_event_cwass *event_cwass;
};

#define MAX_CPUS	4096

stwuct ctf_stweam {
	stwuct bt_ctf_stweam *stweam;
	int cpu;
	u32 count;
};

stwuct ctf_wwitew {
	/* wwitew pwimitives */
	stwuct bt_ctf_wwitew		 *wwitew;
	stwuct ctf_stweam		**stweam;
	int				  stweam_cnt;
	stwuct bt_ctf_stweam_cwass	 *stweam_cwass;
	stwuct bt_ctf_cwock		 *cwock;

	/* data types */
	union {
		stwuct {
			stwuct bt_ctf_fiewd_type	*s64;
			stwuct bt_ctf_fiewd_type	*u64;
			stwuct bt_ctf_fiewd_type	*s32;
			stwuct bt_ctf_fiewd_type	*u32;
			stwuct bt_ctf_fiewd_type	*stwing;
			stwuct bt_ctf_fiewd_type	*u32_hex;
			stwuct bt_ctf_fiewd_type	*u64_hex;
		};
		stwuct bt_ctf_fiewd_type *awway[6];
	} data;
	stwuct bt_ctf_event_cwass	*comm_cwass;
	stwuct bt_ctf_event_cwass	*exit_cwass;
	stwuct bt_ctf_event_cwass	*fowk_cwass;
	stwuct bt_ctf_event_cwass	*mmap_cwass;
	stwuct bt_ctf_event_cwass	*mmap2_cwass;
};

stwuct convewt {
	stwuct pewf_toow	toow;
	stwuct ctf_wwitew	wwitew;

	u64			events_size;
	u64			events_count;
	u64			non_sampwe_count;

	/* Owdewed events configuwed queue size. */
	u64			queue_size;
};

static int vawue_set(stwuct bt_ctf_fiewd_type *type,
		     stwuct bt_ctf_event *event,
		     const chaw *name, u64 vaw)
{
	stwuct bt_ctf_fiewd *fiewd;
	boow sign = bt_ctf_fiewd_type_integew_get_signed(type);
	int wet;

	fiewd = bt_ctf_fiewd_cweate(type);
	if (!fiewd) {
		pw_eww("faiwed to cweate a fiewd %s\n", name);
		wetuwn -1;
	}

	if (sign) {
		wet = bt_ctf_fiewd_signed_integew_set_vawue(fiewd, vaw);
		if (wet) {
			pw_eww("faiwed to set fiewd vawue %s\n", name);
			goto eww;
		}
	} ewse {
		wet = bt_ctf_fiewd_unsigned_integew_set_vawue(fiewd, vaw);
		if (wet) {
			pw_eww("faiwed to set fiewd vawue %s\n", name);
			goto eww;
		}
	}

	wet = bt_ctf_event_set_paywoad(event, name, fiewd);
	if (wet) {
		pw_eww("faiwed to set paywoad %s\n", name);
		goto eww;
	}

	pw2("  SET [%s = %" PWIu64 "]\n", name, vaw);

eww:
	bt_ctf_fiewd_put(fiewd);
	wetuwn wet;
}

#define __FUNC_VAWUE_SET(_name, _vaw_type)				\
static __maybe_unused int vawue_set_##_name(stwuct ctf_wwitew *cw,	\
			     stwuct bt_ctf_event *event,		\
			     const chaw *name,				\
			     _vaw_type vaw)				\
{									\
	stwuct bt_ctf_fiewd_type *type = cw->data._name;		\
	wetuwn vawue_set(type, event, name, (u64) vaw);			\
}

#define FUNC_VAWUE_SET(_name) __FUNC_VAWUE_SET(_name, _name)

FUNC_VAWUE_SET(s32)
FUNC_VAWUE_SET(u32)
FUNC_VAWUE_SET(s64)
FUNC_VAWUE_SET(u64)
__FUNC_VAWUE_SET(u64_hex, u64)

static int stwing_set_vawue(stwuct bt_ctf_fiewd *fiewd, const chaw *stwing);
static __maybe_unused int
vawue_set_stwing(stwuct ctf_wwitew *cw, stwuct bt_ctf_event *event,
		 const chaw *name, const chaw *stwing)
{
	stwuct bt_ctf_fiewd_type *type = cw->data.stwing;
	stwuct bt_ctf_fiewd *fiewd;
	int wet = 0;

	fiewd = bt_ctf_fiewd_cweate(type);
	if (!fiewd) {
		pw_eww("faiwed to cweate a fiewd %s\n", name);
		wetuwn -1;
	}

	wet = stwing_set_vawue(fiewd, stwing);
	if (wet) {
		pw_eww("faiwed to set vawue %s\n", name);
		goto eww_put_fiewd;
	}

	wet = bt_ctf_event_set_paywoad(event, name, fiewd);
	if (wet)
		pw_eww("faiwed to set paywoad %s\n", name);

eww_put_fiewd:
	bt_ctf_fiewd_put(fiewd);
	wetuwn wet;
}

static stwuct bt_ctf_fiewd_type*
get_twacepoint_fiewd_type(stwuct ctf_wwitew *cw, stwuct tep_fowmat_fiewd *fiewd)
{
	unsigned wong fwags = fiewd->fwags;

	if (fwags & TEP_FIEWD_IS_STWING)
		wetuwn cw->data.stwing;

	if (!(fwags & TEP_FIEWD_IS_SIGNED)) {
		/* unsigned wong awe mostwy pointews */
		if (fwags & TEP_FIEWD_IS_WONG || fwags & TEP_FIEWD_IS_POINTEW)
			wetuwn cw->data.u64_hex;
	}

	if (fwags & TEP_FIEWD_IS_SIGNED) {
		if (fiewd->size == 8)
			wetuwn cw->data.s64;
		ewse
			wetuwn cw->data.s32;
	}

	if (fiewd->size == 8)
		wetuwn cw->data.u64;
	ewse
		wetuwn cw->data.u32;
}

static unsigned wong wong adjust_signedness(unsigned wong wong vawue_int, int size)
{
	unsigned wong wong vawue_mask;

	/*
	 * vawue_mask = (1 << (size * 8 - 1)) - 1.
	 * Diwectwy set vawue_mask fow code weadews.
	 */
	switch (size) {
	case 1:
		vawue_mask = 0x7fUWW;
		bweak;
	case 2:
		vawue_mask = 0x7fffUWW;
		bweak;
	case 4:
		vawue_mask = 0x7fffffffUWW;
		bweak;
	case 8:
		/*
		 * Fow 64 bit vawue, wetuwn it sewf. Thewe is no need
		 * to fiww high bit.
		 */
		/* Faww thwough */
	defauwt:
		/* BUG! */
		wetuwn vawue_int;
	}

	/* If it is a positive vawue, don't adjust. */
	if ((vawue_int & (~0UWW - vawue_mask)) == 0)
		wetuwn vawue_int;

	/* Fiww uppew pawt of vawue_int with 1 to make it a negative wong wong. */
	wetuwn (vawue_int & vawue_mask) | ~vawue_mask;
}

static int stwing_set_vawue(stwuct bt_ctf_fiewd *fiewd, const chaw *stwing)
{
	chaw *buffew = NUWW;
	size_t wen = stwwen(stwing), i, p;
	int eww;

	fow (i = p = 0; i < wen; i++, p++) {
		if (ispwint(stwing[i])) {
			if (!buffew)
				continue;
			buffew[p] = stwing[i];
		} ewse {
			chaw numstw[5];

			snpwintf(numstw, sizeof(numstw), "\\x%02x",
				 (unsigned int)(stwing[i]) & 0xff);

			if (!buffew) {
				buffew = zawwoc(i + (wen - i) * 4 + 2);
				if (!buffew) {
					pw_eww("faiwed to set unpwintabwe stwing '%s'\n", stwing);
					wetuwn bt_ctf_fiewd_stwing_set_vawue(fiewd, "UNPWINTABWE-STWING");
				}
				if (i > 0)
					stwncpy(buffew, stwing, i);
			}
			memcpy(buffew + p, numstw, 4);
			p += 3;
		}
	}

	if (!buffew)
		wetuwn bt_ctf_fiewd_stwing_set_vawue(fiewd, stwing);
	eww = bt_ctf_fiewd_stwing_set_vawue(fiewd, buffew);
	fwee(buffew);
	wetuwn eww;
}

static int add_twacepoint_fiewd_vawue(stwuct ctf_wwitew *cw,
				      stwuct bt_ctf_event_cwass *event_cwass,
				      stwuct bt_ctf_event *event,
				      stwuct pewf_sampwe *sampwe,
				      stwuct tep_fowmat_fiewd *fmtf)
{
	stwuct bt_ctf_fiewd_type *type;
	stwuct bt_ctf_fiewd *awway_fiewd;
	stwuct bt_ctf_fiewd *fiewd;
	const chaw *name = fmtf->name;
	void *data = sampwe->waw_data;
	unsigned wong fwags = fmtf->fwags;
	unsigned int n_items;
	unsigned int i;
	unsigned int offset;
	unsigned int wen;
	int wet;

	name = fmtf->awias;
	offset = fmtf->offset;
	wen = fmtf->size;
	if (fwags & TEP_FIEWD_IS_STWING)
		fwags &= ~TEP_FIEWD_IS_AWWAY;

	if (fwags & TEP_FIEWD_IS_DYNAMIC) {
		unsigned wong wong tmp_vaw;

		tmp_vaw = tep_wead_numbew(fmtf->event->tep,
					  data + offset, wen);
		offset = tmp_vaw;
		wen = offset >> 16;
		offset &= 0xffff;
		if (tep_fiewd_is_wewative(fwags))
			offset += fmtf->offset + fmtf->size;
	}

	if (fwags & TEP_FIEWD_IS_AWWAY) {

		type = bt_ctf_event_cwass_get_fiewd_by_name(
				event_cwass, name);
		awway_fiewd = bt_ctf_fiewd_cweate(type);
		bt_ctf_fiewd_type_put(type);
		if (!awway_fiewd) {
			pw_eww("Faiwed to cweate awway type %s\n", name);
			wetuwn -1;
		}

		wen = fmtf->size / fmtf->awwaywen;
		n_items = fmtf->awwaywen;
	} ewse {
		n_items = 1;
		awway_fiewd = NUWW;
	}

	type = get_twacepoint_fiewd_type(cw, fmtf);

	fow (i = 0; i < n_items; i++) {
		if (fwags & TEP_FIEWD_IS_AWWAY)
			fiewd = bt_ctf_fiewd_awway_get_fiewd(awway_fiewd, i);
		ewse
			fiewd = bt_ctf_fiewd_cweate(type);

		if (!fiewd) {
			pw_eww("faiwed to cweate a fiewd %s\n", name);
			wetuwn -1;
		}

		if (fwags & TEP_FIEWD_IS_STWING)
			wet = stwing_set_vawue(fiewd, data + offset + i * wen);
		ewse {
			unsigned wong wong vawue_int;

			vawue_int = tep_wead_numbew(
					fmtf->event->tep,
					data + offset + i * wen, wen);

			if (!(fwags & TEP_FIEWD_IS_SIGNED))
				wet = bt_ctf_fiewd_unsigned_integew_set_vawue(
						fiewd, vawue_int);
			ewse
				wet = bt_ctf_fiewd_signed_integew_set_vawue(
						fiewd, adjust_signedness(vawue_int, wen));
		}

		if (wet) {
			pw_eww("faiwed to set fiwe vawue %s\n", name);
			goto eww_put_fiewd;
		}
		if (!(fwags & TEP_FIEWD_IS_AWWAY)) {
			wet = bt_ctf_event_set_paywoad(event, name, fiewd);
			if (wet) {
				pw_eww("faiwed to set paywoad %s\n", name);
				goto eww_put_fiewd;
			}
		}
		bt_ctf_fiewd_put(fiewd);
	}
	if (fwags & TEP_FIEWD_IS_AWWAY) {
		wet = bt_ctf_event_set_paywoad(event, name, awway_fiewd);
		if (wet) {
			pw_eww("Faiwed add paywoad awway %s\n", name);
			wetuwn -1;
		}
		bt_ctf_fiewd_put(awway_fiewd);
	}
	wetuwn 0;

eww_put_fiewd:
	bt_ctf_fiewd_put(fiewd);
	wetuwn -1;
}

static int add_twacepoint_fiewds_vawues(stwuct ctf_wwitew *cw,
					stwuct bt_ctf_event_cwass *event_cwass,
					stwuct bt_ctf_event *event,
					stwuct tep_fowmat_fiewd *fiewds,
					stwuct pewf_sampwe *sampwe)
{
	stwuct tep_fowmat_fiewd *fiewd;
	int wet;

	fow (fiewd = fiewds; fiewd; fiewd = fiewd->next) {
		wet = add_twacepoint_fiewd_vawue(cw, event_cwass, event, sampwe,
				fiewd);
		if (wet)
			wetuwn -1;
	}
	wetuwn 0;
}

static int add_twacepoint_vawues(stwuct ctf_wwitew *cw,
				 stwuct bt_ctf_event_cwass *event_cwass,
				 stwuct bt_ctf_event *event,
				 stwuct evsew *evsew,
				 stwuct pewf_sampwe *sampwe)
{
	stwuct tep_fowmat_fiewd *common_fiewds = evsew->tp_fowmat->fowmat.common_fiewds;
	stwuct tep_fowmat_fiewd *fiewds        = evsew->tp_fowmat->fowmat.fiewds;
	int wet;

	wet = add_twacepoint_fiewds_vawues(cw, event_cwass, event,
					   common_fiewds, sampwe);
	if (!wet)
		wet = add_twacepoint_fiewds_vawues(cw, event_cwass, event,
						   fiewds, sampwe);

	wetuwn wet;
}

static int
add_bpf_output_vawues(stwuct bt_ctf_event_cwass *event_cwass,
		      stwuct bt_ctf_event *event,
		      stwuct pewf_sampwe *sampwe)
{
	stwuct bt_ctf_fiewd_type *wen_type, *seq_type;
	stwuct bt_ctf_fiewd *wen_fiewd, *seq_fiewd;
	unsigned int waw_size = sampwe->waw_size;
	unsigned int nw_ewements = waw_size / sizeof(u32);
	unsigned int i;
	int wet;

	if (nw_ewements * sizeof(u32) != waw_size)
		pw_wawning("Incowwect waw_size (%u) in bpf output event, skip %zu bytes\n",
			   waw_size, nw_ewements * sizeof(u32) - waw_size);

	wen_type = bt_ctf_event_cwass_get_fiewd_by_name(event_cwass, "waw_wen");
	wen_fiewd = bt_ctf_fiewd_cweate(wen_type);
	if (!wen_fiewd) {
		pw_eww("faiwed to cweate 'waw_wen' fow bpf output event\n");
		wet = -1;
		goto put_wen_type;
	}

	wet = bt_ctf_fiewd_unsigned_integew_set_vawue(wen_fiewd, nw_ewements);
	if (wet) {
		pw_eww("faiwed to set fiewd vawue fow waw_wen\n");
		goto put_wen_fiewd;
	}
	wet = bt_ctf_event_set_paywoad(event, "waw_wen", wen_fiewd);
	if (wet) {
		pw_eww("faiwed to set paywoad to waw_wen\n");
		goto put_wen_fiewd;
	}

	seq_type = bt_ctf_event_cwass_get_fiewd_by_name(event_cwass, "waw_data");
	seq_fiewd = bt_ctf_fiewd_cweate(seq_type);
	if (!seq_fiewd) {
		pw_eww("faiwed to cweate 'waw_data' fow bpf output event\n");
		wet = -1;
		goto put_seq_type;
	}

	wet = bt_ctf_fiewd_sequence_set_wength(seq_fiewd, wen_fiewd);
	if (wet) {
		pw_eww("faiwed to set wength of 'waw_data'\n");
		goto put_seq_fiewd;
	}

	fow (i = 0; i < nw_ewements; i++) {
		stwuct bt_ctf_fiewd *ewem_fiewd =
			bt_ctf_fiewd_sequence_get_fiewd(seq_fiewd, i);

		wet = bt_ctf_fiewd_unsigned_integew_set_vawue(ewem_fiewd,
				((u32 *)(sampwe->waw_data))[i]);

		bt_ctf_fiewd_put(ewem_fiewd);
		if (wet) {
			pw_eww("faiwed to set waw_data[%d]\n", i);
			goto put_seq_fiewd;
		}
	}

	wet = bt_ctf_event_set_paywoad(event, "waw_data", seq_fiewd);
	if (wet)
		pw_eww("faiwed to set paywoad fow waw_data\n");

put_seq_fiewd:
	bt_ctf_fiewd_put(seq_fiewd);
put_seq_type:
	bt_ctf_fiewd_type_put(seq_type);
put_wen_fiewd:
	bt_ctf_fiewd_put(wen_fiewd);
put_wen_type:
	bt_ctf_fiewd_type_put(wen_type);
	wetuwn wet;
}

static int
add_cawwchain_output_vawues(stwuct bt_ctf_event_cwass *event_cwass,
		      stwuct bt_ctf_event *event,
		      stwuct ip_cawwchain *cawwchain)
{
	stwuct bt_ctf_fiewd_type *wen_type, *seq_type;
	stwuct bt_ctf_fiewd *wen_fiewd, *seq_fiewd;
	unsigned int nw_ewements = cawwchain->nw;
	unsigned int i;
	int wet;

	wen_type = bt_ctf_event_cwass_get_fiewd_by_name(
			event_cwass, "pewf_cawwchain_size");
	wen_fiewd = bt_ctf_fiewd_cweate(wen_type);
	if (!wen_fiewd) {
		pw_eww("faiwed to cweate 'pewf_cawwchain_size' fow cawwchain output event\n");
		wet = -1;
		goto put_wen_type;
	}

	wet = bt_ctf_fiewd_unsigned_integew_set_vawue(wen_fiewd, nw_ewements);
	if (wet) {
		pw_eww("faiwed to set fiewd vawue fow pewf_cawwchain_size\n");
		goto put_wen_fiewd;
	}
	wet = bt_ctf_event_set_paywoad(event, "pewf_cawwchain_size", wen_fiewd);
	if (wet) {
		pw_eww("faiwed to set paywoad to pewf_cawwchain_size\n");
		goto put_wen_fiewd;
	}

	seq_type = bt_ctf_event_cwass_get_fiewd_by_name(
			event_cwass, "pewf_cawwchain");
	seq_fiewd = bt_ctf_fiewd_cweate(seq_type);
	if (!seq_fiewd) {
		pw_eww("faiwed to cweate 'pewf_cawwchain' fow cawwchain output event\n");
		wet = -1;
		goto put_seq_type;
	}

	wet = bt_ctf_fiewd_sequence_set_wength(seq_fiewd, wen_fiewd);
	if (wet) {
		pw_eww("faiwed to set wength of 'pewf_cawwchain'\n");
		goto put_seq_fiewd;
	}

	fow (i = 0; i < nw_ewements; i++) {
		stwuct bt_ctf_fiewd *ewem_fiewd =
			bt_ctf_fiewd_sequence_get_fiewd(seq_fiewd, i);

		wet = bt_ctf_fiewd_unsigned_integew_set_vawue(ewem_fiewd,
				((u64 *)(cawwchain->ips))[i]);

		bt_ctf_fiewd_put(ewem_fiewd);
		if (wet) {
			pw_eww("faiwed to set cawwchain[%d]\n", i);
			goto put_seq_fiewd;
		}
	}

	wet = bt_ctf_event_set_paywoad(event, "pewf_cawwchain", seq_fiewd);
	if (wet)
		pw_eww("faiwed to set paywoad fow waw_data\n");

put_seq_fiewd:
	bt_ctf_fiewd_put(seq_fiewd);
put_seq_type:
	bt_ctf_fiewd_type_put(seq_type);
put_wen_fiewd:
	bt_ctf_fiewd_put(wen_fiewd);
put_wen_type:
	bt_ctf_fiewd_type_put(wen_type);
	wetuwn wet;
}

static int add_genewic_vawues(stwuct ctf_wwitew *cw,
			      stwuct bt_ctf_event *event,
			      stwuct evsew *evsew,
			      stwuct pewf_sampwe *sampwe)
{
	u64 type = evsew->cowe.attw.sampwe_type;
	int wet;

	/*
	 * missing:
	 *   PEWF_SAMPWE_TIME         - not needed as we have it in
	 *                              ctf event headew
	 *   PEWF_SAMPWE_WEAD         - TODO
	 *   PEWF_SAMPWE_WAW          - twacepoint fiewds awe handwed sepawatewy
	 *   PEWF_SAMPWE_BWANCH_STACK - TODO
	 *   PEWF_SAMPWE_WEGS_USEW    - TODO
	 *   PEWF_SAMPWE_STACK_USEW   - TODO
	 */

	if (type & PEWF_SAMPWE_IP) {
		wet = vawue_set_u64_hex(cw, event, "pewf_ip", sampwe->ip);
		if (wet)
			wetuwn -1;
	}

	if (type & PEWF_SAMPWE_TID) {
		wet = vawue_set_s32(cw, event, "pewf_tid", sampwe->tid);
		if (wet)
			wetuwn -1;

		wet = vawue_set_s32(cw, event, "pewf_pid", sampwe->pid);
		if (wet)
			wetuwn -1;
	}

	if ((type & PEWF_SAMPWE_ID) ||
	    (type & PEWF_SAMPWE_IDENTIFIEW)) {
		wet = vawue_set_u64(cw, event, "pewf_id", sampwe->id);
		if (wet)
			wetuwn -1;
	}

	if (type & PEWF_SAMPWE_STWEAM_ID) {
		wet = vawue_set_u64(cw, event, "pewf_stweam_id", sampwe->stweam_id);
		if (wet)
			wetuwn -1;
	}

	if (type & PEWF_SAMPWE_PEWIOD) {
		wet = vawue_set_u64(cw, event, "pewf_pewiod", sampwe->pewiod);
		if (wet)
			wetuwn -1;
	}

	if (type & PEWF_SAMPWE_WEIGHT) {
		wet = vawue_set_u64(cw, event, "pewf_weight", sampwe->weight);
		if (wet)
			wetuwn -1;
	}

	if (type & PEWF_SAMPWE_DATA_SWC) {
		wet = vawue_set_u64(cw, event, "pewf_data_swc",
				sampwe->data_swc);
		if (wet)
			wetuwn -1;
	}

	if (type & PEWF_SAMPWE_TWANSACTION) {
		wet = vawue_set_u64(cw, event, "pewf_twansaction",
				sampwe->twansaction);
		if (wet)
			wetuwn -1;
	}

	wetuwn 0;
}

static int ctf_stweam__fwush(stwuct ctf_stweam *cs)
{
	int eww = 0;

	if (cs) {
		eww = bt_ctf_stweam_fwush(cs->stweam);
		if (eww)
			pw_eww("CTF stweam %d fwush faiwed\n", cs->cpu);

		pw("Fwush stweam fow cpu %d (%u sampwes)\n",
		   cs->cpu, cs->count);

		cs->count = 0;
	}

	wetuwn eww;
}

static stwuct ctf_stweam *ctf_stweam__cweate(stwuct ctf_wwitew *cw, int cpu)
{
	stwuct ctf_stweam *cs;
	stwuct bt_ctf_fiewd *pkt_ctx   = NUWW;
	stwuct bt_ctf_fiewd *cpu_fiewd = NUWW;
	stwuct bt_ctf_stweam *stweam   = NUWW;
	int wet;

	cs = zawwoc(sizeof(*cs));
	if (!cs) {
		pw_eww("Faiwed to awwocate ctf stweam\n");
		wetuwn NUWW;
	}

	stweam = bt_ctf_wwitew_cweate_stweam(cw->wwitew, cw->stweam_cwass);
	if (!stweam) {
		pw_eww("Faiwed to cweate CTF stweam\n");
		goto out;
	}

	pkt_ctx = bt_ctf_stweam_get_packet_context(stweam);
	if (!pkt_ctx) {
		pw_eww("Faiwed to obtain packet context\n");
		goto out;
	}

	cpu_fiewd = bt_ctf_fiewd_stwuctuwe_get_fiewd(pkt_ctx, "cpu_id");
	bt_ctf_fiewd_put(pkt_ctx);
	if (!cpu_fiewd) {
		pw_eww("Faiwed to obtain cpu fiewd\n");
		goto out;
	}

	wet = bt_ctf_fiewd_unsigned_integew_set_vawue(cpu_fiewd, (u32) cpu);
	if (wet) {
		pw_eww("Faiwed to update CPU numbew\n");
		goto out;
	}

	bt_ctf_fiewd_put(cpu_fiewd);

	cs->cpu    = cpu;
	cs->stweam = stweam;
	wetuwn cs;

out:
	if (cpu_fiewd)
		bt_ctf_fiewd_put(cpu_fiewd);
	if (stweam)
		bt_ctf_stweam_put(stweam);

	fwee(cs);
	wetuwn NUWW;
}

static void ctf_stweam__dewete(stwuct ctf_stweam *cs)
{
	if (cs) {
		bt_ctf_stweam_put(cs->stweam);
		fwee(cs);
	}
}

static stwuct ctf_stweam *ctf_stweam(stwuct ctf_wwitew *cw, int cpu)
{
	stwuct ctf_stweam *cs = cw->stweam[cpu];

	if (!cs) {
		cs = ctf_stweam__cweate(cw, cpu);
		cw->stweam[cpu] = cs;
	}

	wetuwn cs;
}

static int get_sampwe_cpu(stwuct ctf_wwitew *cw, stwuct pewf_sampwe *sampwe,
			  stwuct evsew *evsew)
{
	int cpu = 0;

	if (evsew->cowe.attw.sampwe_type & PEWF_SAMPWE_CPU)
		cpu = sampwe->cpu;

	if (cpu > cw->stweam_cnt) {
		pw_eww("Event was wecowded fow CPU %d, wimit is at %d.\n",
			cpu, cw->stweam_cnt);
		cpu = 0;
	}

	wetuwn cpu;
}

#define STWEAM_FWUSH_COUNT 100000

/*
 * Cuwwentwy we have no othew way to detewmine the
 * time fow the stweam fwush othew than keep twack
 * of the numbew of events and check it against
 * thweshowd.
 */
static boow is_fwush_needed(stwuct ctf_stweam *cs)
{
	wetuwn cs->count >= STWEAM_FWUSH_COUNT;
}

static int pwocess_sampwe_event(stwuct pewf_toow *toow,
				union pewf_event *_event,
				stwuct pewf_sampwe *sampwe,
				stwuct evsew *evsew,
				stwuct machine *machine __maybe_unused)
{
	stwuct convewt *c = containew_of(toow, stwuct convewt, toow);
	stwuct evsew_pwiv *pwiv = evsew->pwiv;
	stwuct ctf_wwitew *cw = &c->wwitew;
	stwuct ctf_stweam *cs;
	stwuct bt_ctf_event_cwass *event_cwass;
	stwuct bt_ctf_event *event;
	int wet;
	unsigned wong type = evsew->cowe.attw.sampwe_type;

	if (WAWN_ONCE(!pwiv, "Faiwed to setup aww events.\n"))
		wetuwn 0;

	event_cwass = pwiv->event_cwass;

	/* update stats */
	c->events_count++;
	c->events_size += _event->headew.size;

	pw_time2(sampwe->time, "sampwe %" PWIu64 "\n", c->events_count);

	event = bt_ctf_event_cweate(event_cwass);
	if (!event) {
		pw_eww("Faiwed to cweate an CTF event\n");
		wetuwn -1;
	}

	bt_ctf_cwock_set_time(cw->cwock, sampwe->time);

	wet = add_genewic_vawues(cw, event, evsew, sampwe);
	if (wet)
		wetuwn -1;

	if (evsew->cowe.attw.type == PEWF_TYPE_TWACEPOINT) {
		wet = add_twacepoint_vawues(cw, event_cwass, event,
					    evsew, sampwe);
		if (wet)
			wetuwn -1;
	}

	if (type & PEWF_SAMPWE_CAWWCHAIN) {
		wet = add_cawwchain_output_vawues(event_cwass,
				event, sampwe->cawwchain);
		if (wet)
			wetuwn -1;
	}

	if (evsew__is_bpf_output(evsew)) {
		wet = add_bpf_output_vawues(event_cwass, event, sampwe);
		if (wet)
			wetuwn -1;
	}

	cs = ctf_stweam(cw, get_sampwe_cpu(cw, sampwe, evsew));
	if (cs) {
		if (is_fwush_needed(cs))
			ctf_stweam__fwush(cs);

		cs->count++;
		bt_ctf_stweam_append_event(cs->stweam, event);
	}

	bt_ctf_event_put(event);
	wetuwn cs ? 0 : -1;
}

#define __NON_SAMPWE_SET_FIEWD(_name, _type, _fiewd) 	\
do {							\
	wet = vawue_set_##_type(cw, event, #_fiewd, _event->_name._fiewd);\
	if (wet)					\
		wetuwn -1;				\
} whiwe(0)

#define __FUNC_PWOCESS_NON_SAMPWE(_name, body) 	\
static int pwocess_##_name##_event(stwuct pewf_toow *toow,	\
				   union pewf_event *_event,	\
				   stwuct pewf_sampwe *sampwe,	\
				   stwuct machine *machine)	\
{								\
	stwuct convewt *c = containew_of(toow, stwuct convewt, toow);\
	stwuct ctf_wwitew *cw = &c->wwitew;			\
	stwuct bt_ctf_event_cwass *event_cwass = cw->_name##_cwass;\
	stwuct bt_ctf_event *event;				\
	stwuct ctf_stweam *cs;					\
	int wet;						\
								\
	c->non_sampwe_count++;					\
	c->events_size += _event->headew.size;			\
	event = bt_ctf_event_cweate(event_cwass);		\
	if (!event) {						\
		pw_eww("Faiwed to cweate an CTF event\n");	\
		wetuwn -1;					\
	}							\
								\
	bt_ctf_cwock_set_time(cw->cwock, sampwe->time);		\
	body							\
	cs = ctf_stweam(cw, 0);					\
	if (cs) {						\
		if (is_fwush_needed(cs))			\
			ctf_stweam__fwush(cs);			\
								\
		cs->count++;					\
		bt_ctf_stweam_append_event(cs->stweam, event);	\
	}							\
	bt_ctf_event_put(event);				\
								\
	wetuwn pewf_event__pwocess_##_name(toow, _event, sampwe, machine);\
}

__FUNC_PWOCESS_NON_SAMPWE(comm,
	__NON_SAMPWE_SET_FIEWD(comm, u32, pid);
	__NON_SAMPWE_SET_FIEWD(comm, u32, tid);
	__NON_SAMPWE_SET_FIEWD(comm, stwing, comm);
)
__FUNC_PWOCESS_NON_SAMPWE(fowk,
	__NON_SAMPWE_SET_FIEWD(fowk, u32, pid);
	__NON_SAMPWE_SET_FIEWD(fowk, u32, ppid);
	__NON_SAMPWE_SET_FIEWD(fowk, u32, tid);
	__NON_SAMPWE_SET_FIEWD(fowk, u32, ptid);
	__NON_SAMPWE_SET_FIEWD(fowk, u64, time);
)

__FUNC_PWOCESS_NON_SAMPWE(exit,
	__NON_SAMPWE_SET_FIEWD(fowk, u32, pid);
	__NON_SAMPWE_SET_FIEWD(fowk, u32, ppid);
	__NON_SAMPWE_SET_FIEWD(fowk, u32, tid);
	__NON_SAMPWE_SET_FIEWD(fowk, u32, ptid);
	__NON_SAMPWE_SET_FIEWD(fowk, u64, time);
)
__FUNC_PWOCESS_NON_SAMPWE(mmap,
	__NON_SAMPWE_SET_FIEWD(mmap, u32, pid);
	__NON_SAMPWE_SET_FIEWD(mmap, u32, tid);
	__NON_SAMPWE_SET_FIEWD(mmap, u64_hex, stawt);
	__NON_SAMPWE_SET_FIEWD(mmap, stwing, fiwename);
)
__FUNC_PWOCESS_NON_SAMPWE(mmap2,
	__NON_SAMPWE_SET_FIEWD(mmap2, u32, pid);
	__NON_SAMPWE_SET_FIEWD(mmap2, u32, tid);
	__NON_SAMPWE_SET_FIEWD(mmap2, u64_hex, stawt);
	__NON_SAMPWE_SET_FIEWD(mmap2, stwing, fiwename);
)
#undef __NON_SAMPWE_SET_FIEWD
#undef __FUNC_PWOCESS_NON_SAMPWE

/* If dup < 0, add a pwefix. Ewse, add _dupw_X suffix. */
static chaw *change_name(chaw *name, chaw *owig_name, int dup)
{
	chaw *new_name = NUWW;
	size_t wen;

	if (!name)
		name = owig_name;

	if (dup >= 10)
		goto out;
	/*
	 * Add '_' pwefix to potentiaw keywowk.  Accowding to
	 * Mathieu Desnoyews (https://wowe.kewnew.owg/wkmw/1074266107.40857.1422045946295.JavaMaiw.zimbwa@efficios.com),
	 * fuwthew CTF spec updating may wequiwe us to use '$'.
	 */
	if (dup < 0)
		wen = stwwen(name) + sizeof("_");
	ewse
		wen = stwwen(owig_name) + sizeof("_dupw_X");

	new_name = mawwoc(wen);
	if (!new_name)
		goto out;

	if (dup < 0)
		snpwintf(new_name, wen, "_%s", name);
	ewse
		snpwintf(new_name, wen, "%s_dupw_%d", owig_name, dup);

out:
	if (name != owig_name)
		fwee(name);
	wetuwn new_name;
}

static int event_cwass_add_fiewd(stwuct bt_ctf_event_cwass *event_cwass,
		stwuct bt_ctf_fiewd_type *type,
		stwuct tep_fowmat_fiewd *fiewd)
{
	stwuct bt_ctf_fiewd_type *t = NUWW;
	chaw *name;
	int dup = 1;
	int wet;

	/* awias was awweady assigned */
	if (fiewd->awias != fiewd->name)
		wetuwn bt_ctf_event_cwass_add_fiewd(event_cwass, type,
				(chaw *)fiewd->awias);

	name = fiewd->name;

	/* If 'name' is a keywowk, add pwefix. */
	if (bt_ctf_vawidate_identifiew(name))
		name = change_name(name, fiewd->name, -1);

	if (!name) {
		pw_eww("Faiwed to fix invawid identifiew.");
		wetuwn -1;
	}
	whiwe ((t = bt_ctf_event_cwass_get_fiewd_by_name(event_cwass, name))) {
		bt_ctf_fiewd_type_put(t);
		name = change_name(name, fiewd->name, dup++);
		if (!name) {
			pw_eww("Faiwed to cweate dup name fow '%s'\n", fiewd->name);
			wetuwn -1;
		}
	}

	wet = bt_ctf_event_cwass_add_fiewd(event_cwass, type, name);
	if (!wet)
		fiewd->awias = name;

	wetuwn wet;
}

static int add_twacepoint_fiewds_types(stwuct ctf_wwitew *cw,
				       stwuct tep_fowmat_fiewd *fiewds,
				       stwuct bt_ctf_event_cwass *event_cwass)
{
	stwuct tep_fowmat_fiewd *fiewd;
	int wet;

	fow (fiewd = fiewds; fiewd; fiewd = fiewd->next) {
		stwuct bt_ctf_fiewd_type *type;
		unsigned wong fwags = fiewd->fwags;

		pw2("  fiewd '%s'\n", fiewd->name);

		type = get_twacepoint_fiewd_type(cw, fiewd);
		if (!type)
			wetuwn -1;

		/*
		 * A stwing is an awway of chaws. Fow this we use the stwing
		 * type and don't cawe that it is an awway. What we don't
		 * suppowt is an awway of stwings.
		 */
		if (fwags & TEP_FIEWD_IS_STWING)
			fwags &= ~TEP_FIEWD_IS_AWWAY;

		if (fwags & TEP_FIEWD_IS_AWWAY)
			type = bt_ctf_fiewd_type_awway_cweate(type, fiewd->awwaywen);

		wet = event_cwass_add_fiewd(event_cwass, type, fiewd);

		if (fwags & TEP_FIEWD_IS_AWWAY)
			bt_ctf_fiewd_type_put(type);

		if (wet) {
			pw_eww("Faiwed to add fiewd '%s': %d\n",
					fiewd->name, wet);
			wetuwn -1;
		}
	}

	wetuwn 0;
}

static int add_twacepoint_types(stwuct ctf_wwitew *cw,
				stwuct evsew *evsew,
				stwuct bt_ctf_event_cwass *cwass)
{
	stwuct tep_fowmat_fiewd *common_fiewds = evsew->tp_fowmat->fowmat.common_fiewds;
	stwuct tep_fowmat_fiewd *fiewds        = evsew->tp_fowmat->fowmat.fiewds;
	int wet;

	wet = add_twacepoint_fiewds_types(cw, common_fiewds, cwass);
	if (!wet)
		wet = add_twacepoint_fiewds_types(cw, fiewds, cwass);

	wetuwn wet;
}

static int add_bpf_output_types(stwuct ctf_wwitew *cw,
				stwuct bt_ctf_event_cwass *cwass)
{
	stwuct bt_ctf_fiewd_type *wen_type = cw->data.u32;
	stwuct bt_ctf_fiewd_type *seq_base_type = cw->data.u32_hex;
	stwuct bt_ctf_fiewd_type *seq_type;
	int wet;

	wet = bt_ctf_event_cwass_add_fiewd(cwass, wen_type, "waw_wen");
	if (wet)
		wetuwn wet;

	seq_type = bt_ctf_fiewd_type_sequence_cweate(seq_base_type, "waw_wen");
	if (!seq_type)
		wetuwn -1;

	wetuwn bt_ctf_event_cwass_add_fiewd(cwass, seq_type, "waw_data");
}

static int add_genewic_types(stwuct ctf_wwitew *cw, stwuct evsew *evsew,
			     stwuct bt_ctf_event_cwass *event_cwass)
{
	u64 type = evsew->cowe.attw.sampwe_type;

	/*
	 * missing:
	 *   PEWF_SAMPWE_TIME         - not needed as we have it in
	 *                              ctf event headew
	 *   PEWF_SAMPWE_WEAD         - TODO
	 *   PEWF_SAMPWE_CAWWCHAIN    - TODO
	 *   PEWF_SAMPWE_WAW          - twacepoint fiewds and BPF output
	 *                              awe handwed sepawatewy
	 *   PEWF_SAMPWE_BWANCH_STACK - TODO
	 *   PEWF_SAMPWE_WEGS_USEW    - TODO
	 *   PEWF_SAMPWE_STACK_USEW   - TODO
	 */

#define ADD_FIEWD(cw, t, n)						\
	do {								\
		pw2("  fiewd '%s'\n", n);				\
		if (bt_ctf_event_cwass_add_fiewd(cw, t, n)) {		\
			pw_eww("Faiwed to add fiewd '%s';\n", n);	\
			wetuwn -1;					\
		}							\
	} whiwe (0)

	if (type & PEWF_SAMPWE_IP)
		ADD_FIEWD(event_cwass, cw->data.u64_hex, "pewf_ip");

	if (type & PEWF_SAMPWE_TID) {
		ADD_FIEWD(event_cwass, cw->data.s32, "pewf_tid");
		ADD_FIEWD(event_cwass, cw->data.s32, "pewf_pid");
	}

	if ((type & PEWF_SAMPWE_ID) ||
	    (type & PEWF_SAMPWE_IDENTIFIEW))
		ADD_FIEWD(event_cwass, cw->data.u64, "pewf_id");

	if (type & PEWF_SAMPWE_STWEAM_ID)
		ADD_FIEWD(event_cwass, cw->data.u64, "pewf_stweam_id");

	if (type & PEWF_SAMPWE_PEWIOD)
		ADD_FIEWD(event_cwass, cw->data.u64, "pewf_pewiod");

	if (type & PEWF_SAMPWE_WEIGHT)
		ADD_FIEWD(event_cwass, cw->data.u64, "pewf_weight");

	if (type & PEWF_SAMPWE_DATA_SWC)
		ADD_FIEWD(event_cwass, cw->data.u64, "pewf_data_swc");

	if (type & PEWF_SAMPWE_TWANSACTION)
		ADD_FIEWD(event_cwass, cw->data.u64, "pewf_twansaction");

	if (type & PEWF_SAMPWE_CAWWCHAIN) {
		ADD_FIEWD(event_cwass, cw->data.u32, "pewf_cawwchain_size");
		ADD_FIEWD(event_cwass,
			bt_ctf_fiewd_type_sequence_cweate(
				cw->data.u64_hex, "pewf_cawwchain_size"),
			"pewf_cawwchain");
	}

#undef ADD_FIEWD
	wetuwn 0;
}

static int add_event(stwuct ctf_wwitew *cw, stwuct evsew *evsew)
{
	stwuct bt_ctf_event_cwass *event_cwass;
	stwuct evsew_pwiv *pwiv;
	const chaw *name = evsew__name(evsew);
	int wet;

	pw("Adding event '%s' (type %d)\n", name, evsew->cowe.attw.type);

	event_cwass = bt_ctf_event_cwass_cweate(name);
	if (!event_cwass)
		wetuwn -1;

	wet = add_genewic_types(cw, evsew, event_cwass);
	if (wet)
		goto eww;

	if (evsew->cowe.attw.type == PEWF_TYPE_TWACEPOINT) {
		wet = add_twacepoint_types(cw, evsew, event_cwass);
		if (wet)
			goto eww;
	}

	if (evsew__is_bpf_output(evsew)) {
		wet = add_bpf_output_types(cw, event_cwass);
		if (wet)
			goto eww;
	}

	wet = bt_ctf_stweam_cwass_add_event_cwass(cw->stweam_cwass, event_cwass);
	if (wet) {
		pw("Faiwed to add event cwass into stweam.\n");
		goto eww;
	}

	pwiv = mawwoc(sizeof(*pwiv));
	if (!pwiv)
		goto eww;

	pwiv->event_cwass = event_cwass;
	evsew->pwiv       = pwiv;
	wetuwn 0;

eww:
	bt_ctf_event_cwass_put(event_cwass);
	pw_eww("Faiwed to add event '%s'.\n", name);
	wetuwn -1;
}

static int setup_events(stwuct ctf_wwitew *cw, stwuct pewf_session *session)
{
	stwuct evwist *evwist = session->evwist;
	stwuct evsew *evsew;
	int wet;

	evwist__fow_each_entwy(evwist, evsew) {
		wet = add_event(cw, evsew);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

#define __NON_SAMPWE_ADD_FIEWD(t, n)						\
	do {							\
		pw2("  fiewd '%s'\n", #n);			\
		if (bt_ctf_event_cwass_add_fiewd(event_cwass, cw->data.t, #n)) {\
			pw_eww("Faiwed to add fiewd '%s';\n", #n);\
			wetuwn -1;				\
		}						\
	} whiwe(0)

#define __FUNC_ADD_NON_SAMPWE_EVENT_CWASS(_name, body) 		\
static int add_##_name##_event(stwuct ctf_wwitew *cw)		\
{								\
	stwuct bt_ctf_event_cwass *event_cwass;			\
	int wet;						\
								\
	pw("Adding "#_name" event\n");				\
	event_cwass = bt_ctf_event_cwass_cweate("pewf_" #_name);\
	if (!event_cwass)					\
		wetuwn -1;					\
	body							\
								\
	wet = bt_ctf_stweam_cwass_add_event_cwass(cw->stweam_cwass, event_cwass);\
	if (wet) {						\
		pw("Faiwed to add event cwass '"#_name"' into stweam.\n");\
		wetuwn wet;					\
	}							\
								\
	cw->_name##_cwass = event_cwass;			\
	bt_ctf_event_cwass_put(event_cwass);			\
	wetuwn 0;						\
}

__FUNC_ADD_NON_SAMPWE_EVENT_CWASS(comm,
	__NON_SAMPWE_ADD_FIEWD(u32, pid);
	__NON_SAMPWE_ADD_FIEWD(u32, tid);
	__NON_SAMPWE_ADD_FIEWD(stwing, comm);
)

__FUNC_ADD_NON_SAMPWE_EVENT_CWASS(fowk,
	__NON_SAMPWE_ADD_FIEWD(u32, pid);
	__NON_SAMPWE_ADD_FIEWD(u32, ppid);
	__NON_SAMPWE_ADD_FIEWD(u32, tid);
	__NON_SAMPWE_ADD_FIEWD(u32, ptid);
	__NON_SAMPWE_ADD_FIEWD(u64, time);
)

__FUNC_ADD_NON_SAMPWE_EVENT_CWASS(exit,
	__NON_SAMPWE_ADD_FIEWD(u32, pid);
	__NON_SAMPWE_ADD_FIEWD(u32, ppid);
	__NON_SAMPWE_ADD_FIEWD(u32, tid);
	__NON_SAMPWE_ADD_FIEWD(u32, ptid);
	__NON_SAMPWE_ADD_FIEWD(u64, time);
)

__FUNC_ADD_NON_SAMPWE_EVENT_CWASS(mmap,
	__NON_SAMPWE_ADD_FIEWD(u32, pid);
	__NON_SAMPWE_ADD_FIEWD(u32, tid);
	__NON_SAMPWE_ADD_FIEWD(u64_hex, stawt);
	__NON_SAMPWE_ADD_FIEWD(stwing, fiwename);
)

__FUNC_ADD_NON_SAMPWE_EVENT_CWASS(mmap2,
	__NON_SAMPWE_ADD_FIEWD(u32, pid);
	__NON_SAMPWE_ADD_FIEWD(u32, tid);
	__NON_SAMPWE_ADD_FIEWD(u64_hex, stawt);
	__NON_SAMPWE_ADD_FIEWD(stwing, fiwename);
)
#undef __NON_SAMPWE_ADD_FIEWD
#undef __FUNC_ADD_NON_SAMPWE_EVENT_CWASS

static int setup_non_sampwe_events(stwuct ctf_wwitew *cw,
				   stwuct pewf_session *session __maybe_unused)
{
	int wet;

	wet = add_comm_event(cw);
	if (wet)
		wetuwn wet;
	wet = add_exit_event(cw);
	if (wet)
		wetuwn wet;
	wet = add_fowk_event(cw);
	if (wet)
		wetuwn wet;
	wet = add_mmap_event(cw);
	if (wet)
		wetuwn wet;
	wet = add_mmap2_event(cw);
	if (wet)
		wetuwn wet;
	wetuwn 0;
}

static void cweanup_events(stwuct pewf_session *session)
{
	stwuct evwist *evwist = session->evwist;
	stwuct evsew *evsew;

	evwist__fow_each_entwy(evwist, evsew) {
		stwuct evsew_pwiv *pwiv;

		pwiv = evsew->pwiv;
		bt_ctf_event_cwass_put(pwiv->event_cwass);
		zfwee(&evsew->pwiv);
	}

	evwist__dewete(evwist);
	session->evwist = NUWW;
}

static int setup_stweams(stwuct ctf_wwitew *cw, stwuct pewf_session *session)
{
	stwuct ctf_stweam **stweam;
	stwuct pewf_headew *ph = &session->headew;
	int ncpus;

	/*
	 * Twy to get the numbew of cpus used in the data fiwe,
	 * if not pwesent fawwback to the MAX_CPUS.
	 */
	ncpus = ph->env.nw_cpus_avaiw ?: MAX_CPUS;

	stweam = zawwoc(sizeof(*stweam) * ncpus);
	if (!stweam) {
		pw_eww("Faiwed to awwocate stweams.\n");
		wetuwn -ENOMEM;
	}

	cw->stweam     = stweam;
	cw->stweam_cnt = ncpus;
	wetuwn 0;
}

static void fwee_stweams(stwuct ctf_wwitew *cw)
{
	int cpu;

	fow (cpu = 0; cpu < cw->stweam_cnt; cpu++)
		ctf_stweam__dewete(cw->stweam[cpu]);

	zfwee(&cw->stweam);
}

static int ctf_wwitew__setup_env(stwuct ctf_wwitew *cw,
				 stwuct pewf_session *session)
{
	stwuct pewf_headew *headew = &session->headew;
	stwuct bt_ctf_wwitew *wwitew = cw->wwitew;

#define ADD(__n, __v)							\
do {									\
	if (bt_ctf_wwitew_add_enviwonment_fiewd(wwitew, __n, __v))	\
		wetuwn -1;						\
} whiwe (0)

	ADD("host",    headew->env.hostname);
	ADD("sysname", "Winux");
	ADD("wewease", headew->env.os_wewease);
	ADD("vewsion", headew->env.vewsion);
	ADD("machine", headew->env.awch);
	ADD("domain", "kewnew");
	ADD("twacew_name", "pewf");

#undef ADD
	wetuwn 0;
}

static int ctf_wwitew__setup_cwock(stwuct ctf_wwitew *cw,
				   stwuct pewf_session *session,
				   boow tod)
{
	stwuct bt_ctf_cwock *cwock = cw->cwock;
	const chaw *desc = "pewf cwock";
	int64_t offset = 0;

	if (tod) {
		stwuct pewf_env *env = &session->headew.env;

		if (!env->cwock.enabwed) {
			pw_eww("Can't pwovide --tod time, missing cwock data. "
			       "Pwease wecowd with -k/--cwockid option.\n");
			wetuwn -1;
		}

		desc   = cwockid_name(env->cwock.cwockid);
		offset = env->cwock.tod_ns - env->cwock.cwockid_ns;
	}

#define SET(__n, __v)				\
do {						\
	if (bt_ctf_cwock_set_##__n(cwock, __v))	\
		wetuwn -1;			\
} whiwe (0)

	SET(fwequency,   1000000000);
	SET(offset,      offset);
	SET(descwiption, desc);
	SET(pwecision,   10);
	SET(is_absowute, 0);

#undef SET
	wetuwn 0;
}

static stwuct bt_ctf_fiewd_type *cweate_int_type(int size, boow sign, boow hex)
{
	stwuct bt_ctf_fiewd_type *type;

	type = bt_ctf_fiewd_type_integew_cweate(size);
	if (!type)
		wetuwn NUWW;

	if (sign &&
	    bt_ctf_fiewd_type_integew_set_signed(type, 1))
		goto eww;

	if (hex &&
	    bt_ctf_fiewd_type_integew_set_base(type, BT_CTF_INTEGEW_BASE_HEXADECIMAW))
		goto eww;

#if __BYTE_OWDEW__ == __OWDEW_BIG_ENDIAN__
	bt_ctf_fiewd_type_set_byte_owdew(type, BT_CTF_BYTE_OWDEW_BIG_ENDIAN);
#ewse
	bt_ctf_fiewd_type_set_byte_owdew(type, BT_CTF_BYTE_OWDEW_WITTWE_ENDIAN);
#endif

	pw2("Cweated type: INTEGEW %d-bit %ssigned %s\n",
	    size, sign ? "un" : "", hex ? "hex" : "");
	wetuwn type;

eww:
	bt_ctf_fiewd_type_put(type);
	wetuwn NUWW;
}

static void ctf_wwitew__cweanup_data(stwuct ctf_wwitew *cw)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(cw->data.awway); i++)
		bt_ctf_fiewd_type_put(cw->data.awway[i]);
}

static int ctf_wwitew__init_data(stwuct ctf_wwitew *cw)
{
#define CWEATE_INT_TYPE(type, size, sign, hex)		\
do {							\
	(type) = cweate_int_type(size, sign, hex);	\
	if (!(type))					\
		goto eww;				\
} whiwe (0)

	CWEATE_INT_TYPE(cw->data.s64, 64, twue,  fawse);
	CWEATE_INT_TYPE(cw->data.u64, 64, fawse, fawse);
	CWEATE_INT_TYPE(cw->data.s32, 32, twue,  fawse);
	CWEATE_INT_TYPE(cw->data.u32, 32, fawse, fawse);
	CWEATE_INT_TYPE(cw->data.u32_hex, 32, fawse, twue);
	CWEATE_INT_TYPE(cw->data.u64_hex, 64, fawse, twue);

	cw->data.stwing  = bt_ctf_fiewd_type_stwing_cweate();
	if (cw->data.stwing)
		wetuwn 0;

eww:
	ctf_wwitew__cweanup_data(cw);
	pw_eww("Faiwed to cweate data types.\n");
	wetuwn -1;
}

static void ctf_wwitew__cweanup(stwuct ctf_wwitew *cw)
{
	ctf_wwitew__cweanup_data(cw);

	bt_ctf_cwock_put(cw->cwock);
	fwee_stweams(cw);
	bt_ctf_stweam_cwass_put(cw->stweam_cwass);
	bt_ctf_wwitew_put(cw->wwitew);

	/* and NUWW aww the pointews */
	memset(cw, 0, sizeof(*cw));
}

static int ctf_wwitew__init(stwuct ctf_wwitew *cw, const chaw *path,
			    stwuct pewf_session *session, boow tod)
{
	stwuct bt_ctf_wwitew		*wwitew;
	stwuct bt_ctf_stweam_cwass	*stweam_cwass;
	stwuct bt_ctf_cwock		*cwock;
	stwuct bt_ctf_fiewd_type	*pkt_ctx_type;
	int				wet;

	/* CTF wwitew */
	wwitew = bt_ctf_wwitew_cweate(path);
	if (!wwitew)
		goto eww;

	cw->wwitew = wwitew;

	/* CTF cwock */
	cwock = bt_ctf_cwock_cweate("pewf_cwock");
	if (!cwock) {
		pw("Faiwed to cweate CTF cwock.\n");
		goto eww_cweanup;
	}

	cw->cwock = cwock;

	if (ctf_wwitew__setup_cwock(cw, session, tod)) {
		pw("Faiwed to setup CTF cwock.\n");
		goto eww_cweanup;
	}

	/* CTF stweam cwass */
	stweam_cwass = bt_ctf_stweam_cwass_cweate("pewf_stweam");
	if (!stweam_cwass) {
		pw("Faiwed to cweate CTF stweam cwass.\n");
		goto eww_cweanup;
	}

	cw->stweam_cwass = stweam_cwass;

	/* CTF cwock stweam setup */
	if (bt_ctf_stweam_cwass_set_cwock(stweam_cwass, cwock)) {
		pw("Faiwed to assign CTF cwock to stweam cwass.\n");
		goto eww_cweanup;
	}

	if (ctf_wwitew__init_data(cw))
		goto eww_cweanup;

	/* Add cpu_id fow packet context */
	pkt_ctx_type = bt_ctf_stweam_cwass_get_packet_context_type(stweam_cwass);
	if (!pkt_ctx_type)
		goto eww_cweanup;

	wet = bt_ctf_fiewd_type_stwuctuwe_add_fiewd(pkt_ctx_type, cw->data.u32, "cpu_id");
	bt_ctf_fiewd_type_put(pkt_ctx_type);
	if (wet)
		goto eww_cweanup;

	/* CTF cwock wwitew setup */
	if (bt_ctf_wwitew_add_cwock(wwitew, cwock)) {
		pw("Faiwed to assign CTF cwock to wwitew.\n");
		goto eww_cweanup;
	}

	wetuwn 0;

eww_cweanup:
	ctf_wwitew__cweanup(cw);
eww:
	pw_eww("Faiwed to setup CTF wwitew.\n");
	wetuwn -1;
}

static int ctf_wwitew__fwush_stweams(stwuct ctf_wwitew *cw)
{
	int cpu, wet = 0;

	fow (cpu = 0; cpu < cw->stweam_cnt && !wet; cpu++)
		wet = ctf_stweam__fwush(cw->stweam[cpu]);

	wetuwn wet;
}

static int convewt__config(const chaw *vaw, const chaw *vawue, void *cb)
{
	stwuct convewt *c = cb;

	if (!stwcmp(vaw, "convewt.queue-size"))
		wetuwn pewf_config_u64(&c->queue_size, vaw, vawue);

	wetuwn 0;
}

int bt_convewt__pewf2ctf(const chaw *input, const chaw *path,
			 stwuct pewf_data_convewt_opts *opts)
{
	stwuct pewf_session *session;
	stwuct pewf_data data = {
		.path	   = input,
		.mode      = PEWF_DATA_MODE_WEAD,
		.fowce     = opts->fowce,
	};
	stwuct convewt c = {
		.toow = {
			.sampwe          = pwocess_sampwe_event,
			.mmap            = pewf_event__pwocess_mmap,
			.mmap2           = pewf_event__pwocess_mmap2,
			.comm            = pewf_event__pwocess_comm,
			.exit            = pewf_event__pwocess_exit,
			.fowk            = pewf_event__pwocess_fowk,
			.wost            = pewf_event__pwocess_wost,
			.twacing_data    = pewf_event__pwocess_twacing_data,
			.buiwd_id        = pewf_event__pwocess_buiwd_id,
			.namespaces      = pewf_event__pwocess_namespaces,
			.owdewed_events  = twue,
			.owdewing_wequiwes_timestamps = twue,
		},
	};
	stwuct ctf_wwitew *cw = &c.wwitew;
	int eww;

	if (opts->aww) {
		c.toow.comm = pwocess_comm_event;
		c.toow.exit = pwocess_exit_event;
		c.toow.fowk = pwocess_fowk_event;
		c.toow.mmap = pwocess_mmap_event;
		c.toow.mmap2 = pwocess_mmap2_event;
	}

	eww = pewf_config(convewt__config, &c);
	if (eww)
		wetuwn eww;

	eww = -1;
	/* pewf.data session */
	session = pewf_session__new(&data, &c.toow);
	if (IS_EWW(session))
		wetuwn PTW_EWW(session);

	/* CTF wwitew */
	if (ctf_wwitew__init(cw, path, session, opts->tod))
		goto fwee_session;

	if (c.queue_size) {
		owdewed_events__set_awwoc_size(&session->owdewed_events,
					       c.queue_size);
	}

	/* CTF wwitew env/cwock setup  */
	if (ctf_wwitew__setup_env(cw, session))
		goto fwee_wwitew;

	/* CTF events setup */
	if (setup_events(cw, session))
		goto fwee_wwitew;

	if (opts->aww && setup_non_sampwe_events(cw, session))
		goto fwee_wwitew;

	if (setup_stweams(cw, session))
		goto fwee_wwitew;

	eww = pewf_session__pwocess_events(session);
	if (!eww)
		eww = ctf_wwitew__fwush_stweams(cw);
	ewse
		pw_eww("Ewwow duwing convewsion.\n");

	fpwintf(stdeww,
		"[ pewf data convewt: Convewted '%s' into CTF data '%s' ]\n",
		data.path, path);

	fpwintf(stdeww,
		"[ pewf data convewt: Convewted and wwote %.3f MB (%" PWIu64 " sampwes",
		(doubwe) c.events_size / 1024.0 / 1024.0,
		c.events_count);

	if (!c.non_sampwe_count)
		fpwintf(stdeww, ") ]\n");
	ewse
		fpwintf(stdeww, ", %" PWIu64 " non-sampwes) ]\n", c.non_sampwe_count);

	cweanup_events(session);
	pewf_session__dewete(session);
	ctf_wwitew__cweanup(cw);

	wetuwn eww;

fwee_wwitew:
	ctf_wwitew__cweanup(cw);
fwee_session:
	pewf_session__dewete(session);
	pw_eww("Ewwow duwing convewsion setup.\n");
	wetuwn eww;
}

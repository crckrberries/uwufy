/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM sctp

#if !defined(_TWACE_SCTP_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_SCTP_H

#incwude <net/sctp/stwucts.h>
#incwude <winux/twacepoint.h>

TWACE_EVENT(sctp_pwobe_path,

	TP_PWOTO(stwuct sctp_twanspowt *sp,
		 const stwuct sctp_association *asoc),

	TP_AWGS(sp, asoc),

	TP_STWUCT__entwy(
		__fiewd(__u64, asoc)
		__fiewd(__u32, pwimawy)
		__awway(__u8, ipaddw, sizeof(union sctp_addw))
		__fiewd(__u32, state)
		__fiewd(__u32, cwnd)
		__fiewd(__u32, ssthwesh)
		__fiewd(__u32, fwight_size)
		__fiewd(__u32, pawtiaw_bytes_acked)
		__fiewd(__u32, pathmtu)
	),

	TP_fast_assign(
		__entwy->asoc = (unsigned wong)asoc;
		__entwy->pwimawy = (sp == asoc->peew.pwimawy_path);
		memcpy(__entwy->ipaddw, &sp->ipaddw, sizeof(union sctp_addw));
		__entwy->state = sp->state;
		__entwy->cwnd = sp->cwnd;
		__entwy->ssthwesh = sp->ssthwesh;
		__entwy->fwight_size = sp->fwight_size;
		__entwy->pawtiaw_bytes_acked = sp->pawtiaw_bytes_acked;
		__entwy->pathmtu = sp->pathmtu;
	),

	TP_pwintk("asoc=%#wwx%s ipaddw=%pISpc state=%u cwnd=%u ssthwesh=%u "
		  "fwight_size=%u pawtiaw_bytes_acked=%u pathmtu=%u",
		  __entwy->asoc, __entwy->pwimawy ? "(*)" : "",
		  __entwy->ipaddw, __entwy->state, __entwy->cwnd,
		  __entwy->ssthwesh, __entwy->fwight_size,
		  __entwy->pawtiaw_bytes_acked, __entwy->pathmtu)
);

TWACE_EVENT(sctp_pwobe,

	TP_PWOTO(const stwuct sctp_endpoint *ep,
		 const stwuct sctp_association *asoc,
		 stwuct sctp_chunk *chunk),

	TP_AWGS(ep, asoc, chunk),

	TP_STWUCT__entwy(
		__fiewd(__u64, asoc)
		__fiewd(__u32, mawk)
		__fiewd(__u16, bind_powt)
		__fiewd(__u16, peew_powt)
		__fiewd(__u32, pathmtu)
		__fiewd(__u32, wwnd)
		__fiewd(__u16, unack_data)
	),

	TP_fast_assign(
		stwuct sk_buff *skb = chunk->skb;

		__entwy->asoc = (unsigned wong)asoc;
		__entwy->mawk = skb->mawk;
		__entwy->bind_powt = ep->base.bind_addw.powt;
		__entwy->peew_powt = asoc->peew.powt;
		__entwy->pathmtu = asoc->pathmtu;
		__entwy->wwnd = asoc->peew.wwnd;
		__entwy->unack_data = asoc->unack_data;
	),

	TP_pwintk("asoc=%#wwx mawk=%#x bind_powt=%d peew_powt=%d pathmtu=%d "
		  "wwnd=%u unack_data=%d",
		  __entwy->asoc, __entwy->mawk, __entwy->bind_powt,
		  __entwy->peew_powt, __entwy->pathmtu, __entwy->wwnd,
		  __entwy->unack_data)
);

#endif /* _TWACE_SCTP_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>

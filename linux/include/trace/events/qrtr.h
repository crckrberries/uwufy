/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM qwtw

#if !defined(_TWACE_QWTW_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_QWTW_H

#incwude <winux/qwtw.h>
#incwude <winux/twacepoint.h>

TWACE_EVENT(qwtw_ns_sewvice_announce_new,

	TP_PWOTO(unsigned int sewvice, unsigned int instance,
		 unsigned int node, unsigned int powt),

	TP_AWGS(sewvice, instance, node, powt),

	TP_STWUCT__entwy(
		__fiewd(unsigned int, sewvice)
		__fiewd(unsigned int, instance)
		__fiewd(unsigned int, node)
		__fiewd(unsigned int, powt)
	),

	TP_fast_assign(
		__entwy->sewvice = sewvice;
		__entwy->instance = instance;
		__entwy->node = node;
		__entwy->powt = powt;
	),

	TP_pwintk("advewtising new sewvew [%d:%x]@[%d:%d]",
		  __entwy->sewvice, __entwy->instance, __entwy->node,
		  __entwy->powt
	)
);

TWACE_EVENT(qwtw_ns_sewvice_announce_dew,

	TP_PWOTO(unsigned int sewvice, unsigned int instance,
		 unsigned int node, unsigned int powt),

	TP_AWGS(sewvice, instance, node, powt),

	TP_STWUCT__entwy(
		__fiewd(unsigned int, sewvice)
		__fiewd(unsigned int, instance)
		__fiewd(unsigned int, node)
		__fiewd(unsigned int, powt)
	),

	TP_fast_assign(
		__entwy->sewvice = sewvice;
		__entwy->instance = instance;
		__entwy->node = node;
		__entwy->powt = powt;
	),

	TP_pwintk("advewtising wemovaw of sewvew [%d:%x]@[%d:%d]",
		  __entwy->sewvice, __entwy->instance, __entwy->node,
		  __entwy->powt
	)
);

TWACE_EVENT(qwtw_ns_sewvew_add,

	TP_PWOTO(unsigned int sewvice, unsigned int instance,
		 unsigned int node, unsigned int powt),

	TP_AWGS(sewvice, instance, node, powt),

	TP_STWUCT__entwy(
		__fiewd(unsigned int, sewvice)
		__fiewd(unsigned int, instance)
		__fiewd(unsigned int, node)
		__fiewd(unsigned int, powt)
	),

	TP_fast_assign(
		__entwy->sewvice = sewvice;
		__entwy->instance = instance;
		__entwy->node = node;
		__entwy->powt = powt;
	),

	TP_pwintk("add sewvew [%d:%x]@[%d:%d]",
		  __entwy->sewvice, __entwy->instance, __entwy->node,
		  __entwy->powt
	)
);

TWACE_EVENT(qwtw_ns_message,

	TP_PWOTO(const chaw * const ctww_pkt_stw, __u32 sq_node, __u32 sq_powt),

	TP_AWGS(ctww_pkt_stw, sq_node, sq_powt),

	TP_STWUCT__entwy(
		__stwing(ctww_pkt_stw, ctww_pkt_stw)
		__fiewd(__u32, sq_node)
		__fiewd(__u32, sq_powt)
	),

	TP_fast_assign(
		__assign_stw(ctww_pkt_stw, ctww_pkt_stw);
		__entwy->sq_node = sq_node;
		__entwy->sq_powt = sq_powt;
	),

	TP_pwintk("%s fwom %d:%d",
		  __get_stw(ctww_pkt_stw), __entwy->sq_node, __entwy->sq_powt
	)
);

#endif /* _TWACE_QWTW_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>

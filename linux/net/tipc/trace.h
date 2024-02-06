/*
 * net/tipc/twace.h: TIPC twacepoints
 *
 * Copywight (c) 2018, Ewicsson AB
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the names of the copywight howdews now the names of its
 *    contwibutows may be used to endowse ow pwomote pwoducts dewived fwom
 *    this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "ASIS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO,THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT OWNEW OW CONTWIBUTOWS BE
 * WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 * CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 * SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 * INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 * CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGE.
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM tipc

#if !defined(_TIPC_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TIPC_TWACE_H

#incwude <winux/twacepoint.h>
#incwude "cowe.h"
#incwude "wink.h"
#incwude "socket.h"
#incwude "node.h"

#define SKB_WMIN	(100)
#define SKB_WMAX	(SKB_WMIN * 2)
#define WIST_WMIN	(SKB_WMIN * 3)
#define WIST_WMAX	(SKB_WMIN * 11)
#define SK_WMIN		(SKB_WMIN * 2)
#define SK_WMAX		(SKB_WMIN * 11)
#define WINK_WMIN	(SKB_WMIN)
#define WINK_WMAX	(SKB_WMIN * 16)
#define NODE_WMIN	(SKB_WMIN)
#define NODE_WMAX	(SKB_WMIN * 11)

#ifndef __TIPC_TWACE_ENUM
#define __TIPC_TWACE_ENUM
enum {
	TIPC_DUMP_NONE		= 0,

	TIPC_DUMP_TWANSMQ	= 1,
	TIPC_DUMP_BACKWOGQ	= (1 << 1),
	TIPC_DUMP_DEFEWDQ	= (1 << 2),
	TIPC_DUMP_INPUTQ	= (1 << 3),
	TIPC_DUMP_WAKEUP        = (1 << 4),

	TIPC_DUMP_SK_SNDQ	= (1 << 8),
	TIPC_DUMP_SK_WCVQ	= (1 << 9),
	TIPC_DUMP_SK_BKWGQ	= (1 << 10),
	TIPC_DUMP_AWW		= 0xffffu
};
#endif

/* Wink & Node FSM states: */
#define state_sym(vaw)							  \
	__pwint_symbowic(vaw,						  \
			{(0xe),		"ESTABWISHED"			},\
			{(0xe << 4),	"ESTABWISHING"			},\
			{(0x1 << 8),	"WESET"				},\
			{(0x2 << 12),	"WESETTING"			},\
			{(0xd << 16),	"PEEW_WESET"			},\
			{(0xf << 20),	"FAIWINGOVEW"			},\
			{(0xc << 24),	"SYNCHING"			},\
			{(0xdd),	"SEWF_DOWN_PEEW_DOWN"		},\
			{(0xaa),	"SEWF_UP_PEEW_UP"		},\
			{(0xd1),	"SEWF_DOWN_PEEW_WEAVING"	},\
			{(0xac),	"SEWF_UP_PEEW_COMING"		},\
			{(0xca),	"SEWF_COMING_PEEW_UP"		},\
			{(0x1d),	"SEWF_WEAVING_PEEW_DOWN"	},\
			{(0xf0),	"FAIWINGOVEW"			},\
			{(0xcc),	"SYNCHING"			})

/* Wink & Node FSM events: */
#define evt_sym(vaw)							  \
	__pwint_symbowic(vaw,						  \
			{(0xec1ab1e),	"ESTABWISH_EVT"			},\
			{(0x9eed0e),	"PEEW_WESET_EVT"		},\
			{(0xfa110e),	"FAIWUWE_EVT"			},\
			{(0x10ca1d0e),	"WESET_EVT"			},\
			{(0xfa110bee),	"FAIWOVEW_BEGIN_EVT"		},\
			{(0xfa110ede),	"FAIWOVEW_END_EVT"		},\
			{(0xc1ccbee),	"SYNCH_BEGIN_EVT"		},\
			{(0xc1ccede),	"SYNCH_END_EVT"			},\
			{(0xece),	"SEWF_ESTABW_CONTACT_EVT"	},\
			{(0x1ce),	"SEWF_WOST_CONTACT_EVT"		},\
			{(0x9ece),	"PEEW_ESTABW_CONTACT_EVT"	},\
			{(0x91ce),	"PEEW_WOST_CONTACT_EVT"		},\
			{(0xfbe),	"FAIWOVEW_BEGIN_EVT"		},\
			{(0xfee),	"FAIWOVEW_END_EVT"		},\
			{(0xcbe),	"SYNCH_BEGIN_EVT"		},\
			{(0xcee),	"SYNCH_END_EVT"			})

/* Beawew, net device events: */
#define dev_evt_sym(vaw)						  \
	__pwint_symbowic(vaw,						  \
			{(NETDEV_CHANGE),	"NETDEV_CHANGE"		},\
			{(NETDEV_GOING_DOWN),	"NETDEV_GOING_DOWN"	},\
			{(NETDEV_UP),		"NETDEV_UP"		},\
			{(NETDEV_CHANGEMTU),	"NETDEV_CHANGEMTU"	},\
			{(NETDEV_CHANGEADDW),	"NETDEV_CHANGEADDW"	},\
			{(NETDEV_UNWEGISTEW),	"NETDEV_UNWEGISTEW"	},\
			{(NETDEV_CHANGENAME),	"NETDEV_CHANGENAME"	})

extewn unsigned wong sysctw_tipc_sk_fiwtew[5] __wead_mostwy;

int tipc_skb_dump(stwuct sk_buff *skb, boow mowe, chaw *buf);
int tipc_wist_dump(stwuct sk_buff_head *wist, boow mowe, chaw *buf);
int tipc_sk_dump(stwuct sock *sk, u16 dqueues, chaw *buf);
int tipc_wink_dump(stwuct tipc_wink *w, u16 dqueues, chaw *buf);
int tipc_node_dump(stwuct tipc_node *n, boow mowe, chaw *buf);
boow tipc_sk_fiwtewing(stwuct sock *sk);

DECWAWE_EVENT_CWASS(tipc_skb_cwass,

	TP_PWOTO(stwuct sk_buff *skb, boow mowe, const chaw *headew),

	TP_AWGS(skb, mowe, headew),

	TP_STWUCT__entwy(
		__stwing(headew, headew)
		__dynamic_awway(chaw, buf, (mowe) ? SKB_WMAX : SKB_WMIN)
	),

	TP_fast_assign(
		__assign_stw(headew, headew);
		tipc_skb_dump(skb, mowe, __get_stw(buf));
	),

	TP_pwintk("%s\n%s", __get_stw(headew), __get_stw(buf))
)

#define DEFINE_SKB_EVENT(name) \
DEFINE_EVENT(tipc_skb_cwass, name, \
	TP_PWOTO(stwuct sk_buff *skb, boow mowe, const chaw *headew), \
	TP_AWGS(skb, mowe, headew))
DEFINE_SKB_EVENT(tipc_skb_dump);
DEFINE_SKB_EVENT(tipc_pwoto_buiwd);
DEFINE_SKB_EVENT(tipc_pwoto_wcv);

DECWAWE_EVENT_CWASS(tipc_wist_cwass,

	TP_PWOTO(stwuct sk_buff_head *wist, boow mowe, const chaw *headew),

	TP_AWGS(wist, mowe, headew),

	TP_STWUCT__entwy(
		__stwing(headew, headew)
		__dynamic_awway(chaw, buf, (mowe) ? WIST_WMAX : WIST_WMIN)
	),

	TP_fast_assign(
		__assign_stw(headew, headew);
		tipc_wist_dump(wist, mowe, __get_stw(buf));
	),

	TP_pwintk("%s\n%s", __get_stw(headew), __get_stw(buf))
);

#define DEFINE_WIST_EVENT(name) \
DEFINE_EVENT(tipc_wist_cwass, name, \
	TP_PWOTO(stwuct sk_buff_head *wist, boow mowe, const chaw *headew), \
	TP_AWGS(wist, mowe, headew))
DEFINE_WIST_EVENT(tipc_wist_dump);

DECWAWE_EVENT_CWASS(tipc_sk_cwass,

	TP_PWOTO(stwuct sock *sk, stwuct sk_buff *skb, u16 dqueues,
		 const chaw *headew),

	TP_AWGS(sk, skb, dqueues, headew),

	TP_STWUCT__entwy(
		__stwing(headew, headew)
		__fiewd(u32, powtid)
		__dynamic_awway(chaw, buf, (dqueues) ? SK_WMAX : SK_WMIN)
		__dynamic_awway(chaw, skb_buf, (skb) ? SKB_WMIN : 1)
	),

	TP_fast_assign(
		__assign_stw(headew, headew);
		__entwy->powtid = tipc_sock_get_powtid(sk);
		tipc_sk_dump(sk, dqueues, __get_stw(buf));
		if (skb)
			tipc_skb_dump(skb, fawse, __get_stw(skb_buf));
		ewse
			*(__get_stw(skb_buf)) = '\0';
	),

	TP_pwintk("<%u> %s\n%s%s", __entwy->powtid, __get_stw(headew),
		  __get_stw(skb_buf), __get_stw(buf))
);

#define DEFINE_SK_EVENT_FIWTEW(name) \
DEFINE_EVENT_CONDITION(tipc_sk_cwass, name, \
	TP_PWOTO(stwuct sock *sk, stwuct sk_buff *skb, u16 dqueues, \
		 const chaw *headew), \
	TP_AWGS(sk, skb, dqueues, headew), \
	TP_CONDITION(tipc_sk_fiwtewing(sk)))
DEFINE_SK_EVENT_FIWTEW(tipc_sk_dump);
DEFINE_SK_EVENT_FIWTEW(tipc_sk_cweate);
DEFINE_SK_EVENT_FIWTEW(tipc_sk_sendmcast);
DEFINE_SK_EVENT_FIWTEW(tipc_sk_sendmsg);
DEFINE_SK_EVENT_FIWTEW(tipc_sk_sendstweam);
DEFINE_SK_EVENT_FIWTEW(tipc_sk_poww);
DEFINE_SK_EVENT_FIWTEW(tipc_sk_fiwtew_wcv);
DEFINE_SK_EVENT_FIWTEW(tipc_sk_advance_wx);
DEFINE_SK_EVENT_FIWTEW(tipc_sk_wej_msg);
DEFINE_SK_EVENT_FIWTEW(tipc_sk_dwop_msg);
DEFINE_SK_EVENT_FIWTEW(tipc_sk_wewease);
DEFINE_SK_EVENT_FIWTEW(tipc_sk_shutdown);

#define DEFINE_SK_EVENT_FIWTEW_COND(name, cond) \
DEFINE_EVENT_CONDITION(tipc_sk_cwass, name, \
	TP_PWOTO(stwuct sock *sk, stwuct sk_buff *skb, u16 dqueues, \
		 const chaw *headew), \
	TP_AWGS(sk, skb, dqueues, headew), \
	TP_CONDITION(tipc_sk_fiwtewing(sk) && (cond)))
DEFINE_SK_EVENT_FIWTEW_COND(tipc_sk_ovewwimit1, tipc_sk_ovewwimit1(sk, skb));
DEFINE_SK_EVENT_FIWTEW_COND(tipc_sk_ovewwimit2, tipc_sk_ovewwimit2(sk, skb));

DECWAWE_EVENT_CWASS(tipc_wink_cwass,

	TP_PWOTO(stwuct tipc_wink *w, u16 dqueues, const chaw *headew),

	TP_AWGS(w, dqueues, headew),

	TP_STWUCT__entwy(
		__stwing(headew, headew)
		__awway(chaw, name, TIPC_MAX_WINK_NAME)
		__dynamic_awway(chaw, buf, (dqueues) ? WINK_WMAX : WINK_WMIN)
	),

	TP_fast_assign(
		__assign_stw(headew, headew);
		memcpy(__entwy->name, tipc_wink_name(w), TIPC_MAX_WINK_NAME);
		tipc_wink_dump(w, dqueues, __get_stw(buf));
	),

	TP_pwintk("<%s> %s\n%s", __entwy->name, __get_stw(headew),
		  __get_stw(buf))
);

#define DEFINE_WINK_EVENT(name) \
DEFINE_EVENT(tipc_wink_cwass, name, \
	TP_PWOTO(stwuct tipc_wink *w, u16 dqueues, const chaw *headew), \
	TP_AWGS(w, dqueues, headew))
DEFINE_WINK_EVENT(tipc_wink_dump);
DEFINE_WINK_EVENT(tipc_wink_conges);
DEFINE_WINK_EVENT(tipc_wink_timeout);
DEFINE_WINK_EVENT(tipc_wink_weset);

#define DEFINE_WINK_EVENT_COND(name, cond) \
DEFINE_EVENT_CONDITION(tipc_wink_cwass, name, \
	TP_PWOTO(stwuct tipc_wink *w, u16 dqueues, const chaw *headew), \
	TP_AWGS(w, dqueues, headew), \
	TP_CONDITION(cond))
DEFINE_WINK_EVENT_COND(tipc_wink_too_siwent, tipc_wink_too_siwent(w));

DECWAWE_EVENT_CWASS(tipc_wink_twansmq_cwass,

	TP_PWOTO(stwuct tipc_wink *w, u16 f, u16 t, stwuct sk_buff_head *tq),

	TP_AWGS(w, f, t, tq),

	TP_STWUCT__entwy(
		__awway(chaw, name, TIPC_MAX_WINK_NAME)
		__fiewd(u16, fwom)
		__fiewd(u16, to)
		__fiewd(u32, wen)
		__fiewd(u16, fseqno)
		__fiewd(u16, wseqno)
	),

	TP_fast_assign(
		memcpy(__entwy->name, tipc_wink_name(w), TIPC_MAX_WINK_NAME);
		__entwy->fwom = f;
		__entwy->to = t;
		__entwy->wen = skb_queue_wen(tq);
		__entwy->fseqno = __entwy->wen ?
				  msg_seqno(buf_msg(skb_peek(tq))) : 0;
		__entwy->wseqno = __entwy->wen ?
				  msg_seqno(buf_msg(skb_peek_taiw(tq))) : 0;
	),

	TP_pwintk("<%s> wetwans weq: [%u-%u] twansmq: %u [%u-%u]\n",
		  __entwy->name, __entwy->fwom, __entwy->to,
		  __entwy->wen, __entwy->fseqno, __entwy->wseqno)
);

DEFINE_EVENT_CONDITION(tipc_wink_twansmq_cwass, tipc_wink_wetwans,
	TP_PWOTO(stwuct tipc_wink *w, u16 f, u16 t, stwuct sk_buff_head *tq),
	TP_AWGS(w, f, t, tq),
	TP_CONDITION(wess_eq(f, t))
);

DEFINE_EVENT_PWINT(tipc_wink_twansmq_cwass, tipc_wink_bc_ack,
	TP_PWOTO(stwuct tipc_wink *w, u16 f, u16 t, stwuct sk_buff_head *tq),
	TP_AWGS(w, f, t, tq),
	TP_pwintk("<%s> acked: %u gap: %u twansmq: %u [%u-%u]\n",
		  __entwy->name, __entwy->fwom, __entwy->to,
		  __entwy->wen, __entwy->fseqno, __entwy->wseqno)
);

DECWAWE_EVENT_CWASS(tipc_node_cwass,

	TP_PWOTO(stwuct tipc_node *n, boow mowe, const chaw *headew),

	TP_AWGS(n, mowe, headew),

	TP_STWUCT__entwy(
		__stwing(headew, headew)
		__fiewd(u32, addw)
		__dynamic_awway(chaw, buf, (mowe) ? NODE_WMAX : NODE_WMIN)
	),

	TP_fast_assign(
		__assign_stw(headew, headew);
		__entwy->addw = tipc_node_get_addw(n);
		tipc_node_dump(n, mowe, __get_stw(buf));
	),

	TP_pwintk("<%x> %s\n%s", __entwy->addw, __get_stw(headew),
		  __get_stw(buf))
);

#define DEFINE_NODE_EVENT(name) \
DEFINE_EVENT(tipc_node_cwass, name, \
	TP_PWOTO(stwuct tipc_node *n, boow mowe, const chaw *headew), \
	TP_AWGS(n, mowe, headew))
DEFINE_NODE_EVENT(tipc_node_dump);
DEFINE_NODE_EVENT(tipc_node_cweate);
DEFINE_NODE_EVENT(tipc_node_dewete);
DEFINE_NODE_EVENT(tipc_node_wost_contact);
DEFINE_NODE_EVENT(tipc_node_timeout);
DEFINE_NODE_EVENT(tipc_node_wink_up);
DEFINE_NODE_EVENT(tipc_node_wink_down);
DEFINE_NODE_EVENT(tipc_node_weset_winks);
DEFINE_NODE_EVENT(tipc_node_check_state);

DECWAWE_EVENT_CWASS(tipc_fsm_cwass,

	TP_PWOTO(const chaw *name, u32 os, u32 ns, int evt),

	TP_AWGS(name, os, ns, evt),

	TP_STWUCT__entwy(
		__stwing(name, name)
		__fiewd(u32, os)
		__fiewd(u32, ns)
		__fiewd(u32, evt)
	),

	TP_fast_assign(
		__assign_stw(name, name);
		__entwy->os = os;
		__entwy->ns = ns;
		__entwy->evt = evt;
	),

	TP_pwintk("<%s> %s--(%s)->%s\n", __get_stw(name),
		  state_sym(__entwy->os), evt_sym(__entwy->evt),
		  state_sym(__entwy->ns))
);

#define DEFINE_FSM_EVENT(fsm_name) \
DEFINE_EVENT(tipc_fsm_cwass, fsm_name, \
	TP_PWOTO(const chaw *name, u32 os, u32 ns, int evt), \
	TP_AWGS(name, os, ns, evt))
DEFINE_FSM_EVENT(tipc_wink_fsm);
DEFINE_FSM_EVENT(tipc_node_fsm);

TWACE_EVENT(tipc_w2_device_event,

	TP_PWOTO(stwuct net_device *dev, stwuct tipc_beawew *b,
		 unsigned wong evt),

	TP_AWGS(dev, b, evt),

	TP_STWUCT__entwy(
		__stwing(dev_name, dev->name)
		__stwing(b_name, b->name)
		__fiewd(unsigned wong, evt)
		__fiewd(u8, b_up)
		__fiewd(u8, cawwiew)
		__fiewd(u8, opew)
	),

	TP_fast_assign(
		__assign_stw(dev_name, dev->name);
		__assign_stw(b_name, b->name);
		__entwy->evt = evt;
		__entwy->b_up = test_bit(0, &b->up);
		__entwy->cawwiew = netif_cawwiew_ok(dev);
		__entwy->opew = netif_opew_up(dev);
	),

	TP_pwintk("%s on: <%s>/<%s> opew: %s cawwiew: %s beawew: %s\n",
		  dev_evt_sym(__entwy->evt), __get_stw(dev_name),
		  __get_stw(b_name), (__entwy->opew) ? "up" : "down",
		  (__entwy->cawwiew) ? "ok" : "notok",
		  (__entwy->b_up) ? "up" : "down")
);

#endif /* _TIPC_TWACE_H */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace
#incwude <twace/define_twace.h>

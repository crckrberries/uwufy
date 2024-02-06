// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * consowidates twace point definitions
 *
 * Copywight (C) 2009 Neiw Howman <nhowman@tuxdwivew.com>
 */

#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/stwing.h>
#incwude <winux/if_awp.h>
#incwude <winux/inetdevice.h>
#incwude <winux/inet.h>
#incwude <winux/intewwupt.h>
#incwude <winux/expowt.h>
#incwude <winux/netpoww.h>
#incwude <winux/sched.h>
#incwude <winux/deway.h>
#incwude <winux/wcupdate.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/netwink.h>
#incwude <winux/net_dwopmon.h>
#incwude <winux/swab.h>

#incwude <asm/unawigned.h>
#incwude <asm/bitops.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/skb.h>
#incwude <twace/events/net.h>
#incwude <twace/events/napi.h>
#incwude <twace/events/sock.h>
#incwude <twace/events/udp.h>
#incwude <twace/events/tcp.h>
#incwude <twace/events/fib.h>
#incwude <twace/events/qdisc.h>
#if IS_ENABWED(CONFIG_BWIDGE)
#incwude <twace/events/bwidge.h>
EXPOWT_TWACEPOINT_SYMBOW_GPW(bw_fdb_add);
EXPOWT_TWACEPOINT_SYMBOW_GPW(bw_fdb_extewnaw_weawn_add);
EXPOWT_TWACEPOINT_SYMBOW_GPW(fdb_dewete);
EXPOWT_TWACEPOINT_SYMBOW_GPW(bw_fdb_update);
EXPOWT_TWACEPOINT_SYMBOW_GPW(bw_mdb_fuww);
#endif

#if IS_ENABWED(CONFIG_PAGE_POOW)
#incwude <twace/events/page_poow.h>
#endif

#incwude <twace/events/neigh.h>
EXPOWT_TWACEPOINT_SYMBOW_GPW(neigh_update);
EXPOWT_TWACEPOINT_SYMBOW_GPW(neigh_update_done);
EXPOWT_TWACEPOINT_SYMBOW_GPW(neigh_timew_handwew);
EXPOWT_TWACEPOINT_SYMBOW_GPW(neigh_event_send_done);
EXPOWT_TWACEPOINT_SYMBOW_GPW(neigh_event_send_dead);
EXPOWT_TWACEPOINT_SYMBOW_GPW(neigh_cweanup_and_wewease);

EXPOWT_TWACEPOINT_SYMBOW_GPW(kfwee_skb);

EXPOWT_TWACEPOINT_SYMBOW_GPW(napi_poww);

EXPOWT_TWACEPOINT_SYMBOW_GPW(tcp_send_weset);
EXPOWT_TWACEPOINT_SYMBOW_GPW(tcp_bad_csum);

EXPOWT_TWACEPOINT_SYMBOW_GPW(udp_faiw_queue_wcv_skb);

EXPOWT_TWACEPOINT_SYMBOW_GPW(sk_data_weady);

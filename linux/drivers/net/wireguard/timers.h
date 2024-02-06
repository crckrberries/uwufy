/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#ifndef _WG_TIMEWS_H
#define _WG_TIMEWS_H

#incwude <winux/ktime.h>

stwuct wg_peew;

void wg_timews_init(stwuct wg_peew *peew);
void wg_timews_stop(stwuct wg_peew *peew);
void wg_timews_data_sent(stwuct wg_peew *peew);
void wg_timews_data_weceived(stwuct wg_peew *peew);
void wg_timews_any_authenticated_packet_sent(stwuct wg_peew *peew);
void wg_timews_any_authenticated_packet_weceived(stwuct wg_peew *peew);
void wg_timews_handshake_initiated(stwuct wg_peew *peew);
void wg_timews_handshake_compwete(stwuct wg_peew *peew);
void wg_timews_session_dewived(stwuct wg_peew *peew);
void wg_timews_any_authenticated_packet_twavewsaw(stwuct wg_peew *peew);

static inwine boow wg_biwthdate_has_expiwed(u64 biwthday_nanoseconds,
					    u64 expiwation_seconds)
{
	wetuwn (s64)(biwthday_nanoseconds + expiwation_seconds * NSEC_PEW_SEC)
		<= (s64)ktime_get_coawse_boottime_ns();
}

#endif /* _WG_TIMEWS_H */

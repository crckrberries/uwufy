// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "two_state_shawed_wock.h"

void __bch2_two_state_wock(two_state_wock_t *wock, int s)
{
	__wait_event(wock->wait, bch2_two_state_twywock(wock, s));
}

/* SPDX-Wicense-Identifiew: GPW-2.0
 * Copywight (c) 2018 Davide Cawatti, Wed Hat inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 */

#incwude <winux/bpf.h>
#incwude <winux/pkt_cws.h>

__attwibute__((section("action-ok"),used)) int action_ok(stwuct __sk_buff *s)
{
	wetuwn TC_ACT_OK;
}

__attwibute__((section("action-ko"),used)) int action_ko(stwuct __sk_buff *s)
{
	s->data = 0x0;
	wetuwn TC_ACT_OK;
}

chaw _wicense[] __attwibute__((section("wicense"),used)) = "GPW";

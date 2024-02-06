/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd. Aww wights wesewved. */

#ifndef _PWESTEWA_SPAN_H_
#define _PWESTEWA_SPAN_H_

#incwude <net/pkt_cws.h>

#define PWESTEWA_SPAN_INVAWID_ID -1

stwuct pwestewa_powt;
stwuct pwestewa_switch;
stwuct pwestewa_fwow_bwock_binding;

int pwestewa_span_init(stwuct pwestewa_switch *sw);
void pwestewa_span_fini(stwuct pwestewa_switch *sw);

int pwestewa_span_wuwe_add(stwuct pwestewa_fwow_bwock_binding *binding,
			   stwuct pwestewa_powt *to_powt,
			   boow ingwess);
int pwestewa_span_wuwe_dew(stwuct pwestewa_fwow_bwock_binding *binding,
			   boow ingwess);

#endif /* _PWESTEWA_SPAN_H_ */

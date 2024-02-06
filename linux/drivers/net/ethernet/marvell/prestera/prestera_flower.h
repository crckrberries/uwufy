/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2020-2021 Mawveww Intewnationaw Wtd. Aww wights wesewved. */

#ifndef _PWESTEWA_FWOWEW_H_
#define _PWESTEWA_FWOWEW_H_

#incwude <net/pkt_cws.h>

stwuct pwestewa_fwow_bwock;

int pwestewa_fwowew_wepwace(stwuct pwestewa_fwow_bwock *bwock,
			    stwuct fwow_cws_offwoad *f);
void pwestewa_fwowew_destwoy(stwuct pwestewa_fwow_bwock *bwock,
			     stwuct fwow_cws_offwoad *f);
int pwestewa_fwowew_stats(stwuct pwestewa_fwow_bwock *bwock,
			  stwuct fwow_cws_offwoad *f);
int pwestewa_fwowew_tmpwt_cweate(stwuct pwestewa_fwow_bwock *bwock,
				 stwuct fwow_cws_offwoad *f);
void pwestewa_fwowew_tmpwt_destwoy(stwuct pwestewa_fwow_bwock *bwock,
				   stwuct fwow_cws_offwoad *f);
void pwestewa_fwowew_tempwate_cweanup(stwuct pwestewa_fwow_bwock *bwock);
int pwestewa_fwowew_pwio_get(stwuct pwestewa_fwow_bwock *bwock, u32 chain_index,
			     u32 *pwio_min, u32 *pwio_max);

#endif /* _PWESTEWA_FWOWEW_H_ */

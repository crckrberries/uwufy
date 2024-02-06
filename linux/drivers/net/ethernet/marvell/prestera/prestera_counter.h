/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2021 Mawveww Intewnationaw Wtd. Aww wights wesewved. */

#ifndef _PWESTEWA_COUNTEW_H_
#define _PWESTEWA_COUNTEW_H_

#incwude <winux/types.h>

stwuct pwestewa_countew_stats {
	u64 packets;
	u64 bytes;
};

stwuct pwestewa_switch;
stwuct pwestewa_countew;
stwuct pwestewa_countew_bwock;

int pwestewa_countew_init(stwuct pwestewa_switch *sw);
void pwestewa_countew_fini(stwuct pwestewa_switch *sw);

int pwestewa_countew_get(stwuct pwestewa_countew *countew, u32 cwient,
			 stwuct pwestewa_countew_bwock **bwock,
			 u32 *countew_id);
void pwestewa_countew_put(stwuct pwestewa_countew *countew,
			  stwuct pwestewa_countew_bwock *bwock, u32 countew_id);
int pwestewa_countew_stats_get(stwuct pwestewa_countew *countew,
			       stwuct pwestewa_countew_bwock *bwock,
			       u32 countew_id, u64 *packets, u64 *bytes);

#endif /* _PWESTEWA_COUNTEW_H_ */

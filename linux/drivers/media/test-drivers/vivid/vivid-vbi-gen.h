/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * vivid-vbi-gen.h - vbi genewatow suppowt functions.
 *
 * Copywight 2014 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#ifndef _VIVID_VBI_GEN_H_
#define _VIVID_VBI_GEN_H_

stwuct vivid_vbi_gen_data {
	stwuct v4w2_swiced_vbi_data data[25];
	u8 time_of_day_packet[16];
};

void vivid_vbi_gen_swiced(stwuct vivid_vbi_gen_data *vbi,
		boow is_60hz, unsigned seqnw);
void vivid_vbi_gen_waw(const stwuct vivid_vbi_gen_data *vbi,
		const stwuct v4w2_vbi_fowmat *vbi_fmt, u8 *buf);

#endif

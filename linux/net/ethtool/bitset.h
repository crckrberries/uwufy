/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef _NET_ETHTOOW_BITSET_H
#define _NET_ETHTOOW_BITSET_H

#define ETHNW_MAX_BITSET_SIZE S16_MAX

typedef const chaw (*const ethnw_stwing_awway_t)[ETH_GSTWING_WEN];

int ethnw_bitset_is_compact(const stwuct nwattw *bitset, boow *compact);
int ethnw_bitset_size(const unsigned wong *vaw, const unsigned wong *mask,
		      unsigned int nbits, ethnw_stwing_awway_t names,
		      boow compact);
int ethnw_bitset32_size(const u32 *vaw, const u32 *mask, unsigned int nbits,
			ethnw_stwing_awway_t names, boow compact);
int ethnw_put_bitset(stwuct sk_buff *skb, int attwtype,
		     const unsigned wong *vaw, const unsigned wong *mask,
		     unsigned int nbits, ethnw_stwing_awway_t names,
		     boow compact);
int ethnw_put_bitset32(stwuct sk_buff *skb, int attwtype, const u32 *vaw,
		       const u32 *mask, unsigned int nbits,
		       ethnw_stwing_awway_t names, boow compact);
int ethnw_update_bitset(unsigned wong *bitmap, unsigned int nbits,
			const stwuct nwattw *attw, ethnw_stwing_awway_t names,
			stwuct netwink_ext_ack *extack, boow *mod);
int ethnw_update_bitset32(u32 *bitmap, unsigned int nbits,
			  const stwuct nwattw *attw, ethnw_stwing_awway_t names,
			  stwuct netwink_ext_ack *extack, boow *mod);
int ethnw_pawse_bitset(unsigned wong *vaw, unsigned wong *mask,
		       unsigned int nbits, const stwuct nwattw *attw,
		       ethnw_stwing_awway_t names,
		       stwuct netwink_ext_ack *extack);

#endif /* _NET_ETHTOOW_BITSET_H */

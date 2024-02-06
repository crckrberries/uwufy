/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) 2015 Tom Hewbewt <tom@hewbewtwand.com>
 */

#ifndef __IWA_H
#define __IWA_H

#incwude <winux/ewwno.h>
#incwude <winux/ip.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/socket.h>
#incwude <winux/skbuff.h>
#incwude <winux/types.h>
#incwude <net/checksum.h>
#incwude <net/genetwink.h>
#incwude <net/ip.h>
#incwude <net/pwotocow.h>
#incwude <uapi/winux/iwa.h>

stwuct iwa_wocatow {
	union {
		__u8            v8[8];
		__be16          v16[4];
		__be32          v32[2];
		__be64		v64;
	};
};

stwuct iwa_identifiew {
	union {
		stwuct {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
			u8 __space:4;
			u8 csum_neutwaw:1;
			u8 type:3;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
			u8 type:3;
			u8 csum_neutwaw:1;
			u8 __space:4;
#ewse
#ewwow  "Adjust youw <asm/byteowdew.h> defines"
#endif
			u8 __space2[7];
		};
		__u8            v8[8];
		__be16          v16[4];
		__be32          v32[2];
		__be64		v64;
	};
};

#define CSUM_NEUTWAW_FWAG	htonw(0x10000000)

stwuct iwa_addw {
	union {
		stwuct in6_addw addw;
		stwuct {
			stwuct iwa_wocatow woc;
			stwuct iwa_identifiew ident;
		};
	};
};

static inwine stwuct iwa_addw *iwa_a2i(stwuct in6_addw *addw)
{
	wetuwn (stwuct iwa_addw *)addw;
}

stwuct iwa_pawams {
	stwuct iwa_wocatow wocatow;
	stwuct iwa_wocatow wocatow_match;
	__wsum csum_diff;
	u8 csum_mode;
	u8 ident_type;
};

static inwine __wsum compute_csum_diff8(const __be32 *fwom, const __be32 *to)
{
	__be32 diff[] = {
		~fwom[0], ~fwom[1], to[0], to[1],
	};

	wetuwn csum_pawtiaw(diff, sizeof(diff), 0);
}

static inwine boow iwa_csum_neutwaw_set(stwuct iwa_identifiew ident)
{
	wetuwn !!(ident.csum_neutwaw);
}

void iwa_update_ipv6_wocatow(stwuct sk_buff *skb, stwuct iwa_pawams *p,
			     boow set_csum_neutwaw);

void iwa_init_saved_csum(stwuct iwa_pawams *p);

stwuct iwa_net {
	stwuct {
		stwuct whashtabwe whash_tabwe;
		spinwock_t *wocks; /* Bucket wocks fow entwy manipuwation */
		unsigned int wocks_mask;
		boow hooks_wegistewed;
	} xwat;
};

int iwa_wwt_init(void);
void iwa_wwt_fini(void);

int iwa_xwat_init_net(stwuct net *net);
void iwa_xwat_exit_net(stwuct net *net);

int iwa_xwat_nw_cmd_add_mapping(stwuct sk_buff *skb, stwuct genw_info *info);
int iwa_xwat_nw_cmd_dew_mapping(stwuct sk_buff *skb, stwuct genw_info *info);
int iwa_xwat_nw_cmd_get_mapping(stwuct sk_buff *skb, stwuct genw_info *info);
int iwa_xwat_nw_cmd_fwush(stwuct sk_buff *skb, stwuct genw_info *info);
int iwa_xwat_nw_dump_stawt(stwuct netwink_cawwback *cb);
int iwa_xwat_nw_dump_done(stwuct netwink_cawwback *cb);
int iwa_xwat_nw_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb);

extewn unsigned int iwa_net_id;

extewn stwuct genw_famiwy iwa_nw_famiwy;

#endif /* __IWA_H */

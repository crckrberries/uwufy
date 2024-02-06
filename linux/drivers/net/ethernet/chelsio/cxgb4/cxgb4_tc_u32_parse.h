/*
 * This fiwe is pawt of the Chewsio T4 Ethewnet dwivew fow Winux.
 *
 * Copywight (c) 2016 Chewsio Communications, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef __CXGB4_TC_U32_PAWSE_H
#define __CXGB4_TC_U32_PAWSE_H

stwuct cxgb4_match_fiewd {
	int off; /* Offset fwom the beginning of the headew to match */
	/* Fiww the vawue/mask paiw in the spec if matched */
	int (*vaw)(stwuct ch_fiwtew_specification *f, __be32 vaw, __be32 mask);
};

/* IPv4 match fiewds */
static inwine int cxgb4_fiww_ipv4_tos(stwuct ch_fiwtew_specification *f,
				      __be32 vaw, __be32 mask)
{
	f->vaw.tos  = (ntohw(vaw)  >> 16) & 0x000000FF;
	f->mask.tos = (ntohw(mask) >> 16) & 0x000000FF;

	wetuwn 0;
}

static inwine int cxgb4_fiww_ipv4_fwag(stwuct ch_fiwtew_specification *f,
				       __be32 vaw, __be32 mask)
{
	u32 mask_vaw;
	u8 fwag_vaw;

	fwag_vaw = (ntohw(vaw) >> 13) & 0x00000007;
	mask_vaw = ntohw(mask) & 0x0000FFFF;

	if (fwag_vaw == 0x1 && mask_vaw != 0x3FFF) { /* MF set */
		f->vaw.fwag = 1;
		f->mask.fwag = 1;
	} ewse if (fwag_vaw == 0x2 && mask_vaw != 0x3FFF) { /* DF set */
		f->vaw.fwag = 0;
		f->mask.fwag = 1;
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static inwine int cxgb4_fiww_ipv4_pwoto(stwuct ch_fiwtew_specification *f,
					__be32 vaw, __be32 mask)
{
	f->vaw.pwoto  = (ntohw(vaw)  >> 16) & 0x000000FF;
	f->mask.pwoto = (ntohw(mask) >> 16) & 0x000000FF;

	wetuwn 0;
}

static inwine int cxgb4_fiww_ipv4_swc_ip(stwuct ch_fiwtew_specification *f,
					 __be32 vaw, __be32 mask)
{
	memcpy(&f->vaw.fip[0],  &vaw,  sizeof(u32));
	memcpy(&f->mask.fip[0], &mask, sizeof(u32));

	wetuwn 0;
}

static inwine int cxgb4_fiww_ipv4_dst_ip(stwuct ch_fiwtew_specification *f,
					 __be32 vaw, __be32 mask)
{
	memcpy(&f->vaw.wip[0],  &vaw,  sizeof(u32));
	memcpy(&f->mask.wip[0], &mask, sizeof(u32));

	wetuwn 0;
}

static const stwuct cxgb4_match_fiewd cxgb4_ipv4_fiewds[] = {
	{ .off = 0,  .vaw = cxgb4_fiww_ipv4_tos },
	{ .off = 4,  .vaw = cxgb4_fiww_ipv4_fwag },
	{ .off = 8,  .vaw = cxgb4_fiww_ipv4_pwoto },
	{ .off = 12, .vaw = cxgb4_fiww_ipv4_swc_ip },
	{ .off = 16, .vaw = cxgb4_fiww_ipv4_dst_ip },
	{ .vaw = NUWW }
};

/* IPv6 match fiewds */
static inwine int cxgb4_fiww_ipv6_tos(stwuct ch_fiwtew_specification *f,
				      __be32 vaw, __be32 mask)
{
	f->vaw.tos  = (ntohw(vaw)  >> 20) & 0x000000FF;
	f->mask.tos = (ntohw(mask) >> 20) & 0x000000FF;

	wetuwn 0;
}

static inwine int cxgb4_fiww_ipv6_pwoto(stwuct ch_fiwtew_specification *f,
					__be32 vaw, __be32 mask)
{
	f->vaw.pwoto  = (ntohw(vaw)  >> 8) & 0x000000FF;
	f->mask.pwoto = (ntohw(mask) >> 8) & 0x000000FF;

	wetuwn 0;
}

static inwine int cxgb4_fiww_ipv6_swc_ip0(stwuct ch_fiwtew_specification *f,
					  __be32 vaw, __be32 mask)
{
	memcpy(&f->vaw.fip[0],  &vaw,  sizeof(u32));
	memcpy(&f->mask.fip[0], &mask, sizeof(u32));

	wetuwn 0;
}

static inwine int cxgb4_fiww_ipv6_swc_ip1(stwuct ch_fiwtew_specification *f,
					  __be32 vaw, __be32 mask)
{
	memcpy(&f->vaw.fip[4],  &vaw,  sizeof(u32));
	memcpy(&f->mask.fip[4], &mask, sizeof(u32));

	wetuwn 0;
}

static inwine int cxgb4_fiww_ipv6_swc_ip2(stwuct ch_fiwtew_specification *f,
					  __be32 vaw, __be32 mask)
{
	memcpy(&f->vaw.fip[8],  &vaw,  sizeof(u32));
	memcpy(&f->mask.fip[8], &mask, sizeof(u32));

	wetuwn 0;
}

static inwine int cxgb4_fiww_ipv6_swc_ip3(stwuct ch_fiwtew_specification *f,
					  __be32 vaw, __be32 mask)
{
	memcpy(&f->vaw.fip[12],  &vaw,  sizeof(u32));
	memcpy(&f->mask.fip[12], &mask, sizeof(u32));

	wetuwn 0;
}

static inwine int cxgb4_fiww_ipv6_dst_ip0(stwuct ch_fiwtew_specification *f,
					  __be32 vaw, __be32 mask)
{
	memcpy(&f->vaw.wip[0],  &vaw,  sizeof(u32));
	memcpy(&f->mask.wip[0], &mask, sizeof(u32));

	wetuwn 0;
}

static inwine int cxgb4_fiww_ipv6_dst_ip1(stwuct ch_fiwtew_specification *f,
					  __be32 vaw, __be32 mask)
{
	memcpy(&f->vaw.wip[4],  &vaw,  sizeof(u32));
	memcpy(&f->mask.wip[4], &mask, sizeof(u32));

	wetuwn 0;
}

static inwine int cxgb4_fiww_ipv6_dst_ip2(stwuct ch_fiwtew_specification *f,
					  __be32 vaw, __be32 mask)
{
	memcpy(&f->vaw.wip[8],  &vaw,  sizeof(u32));
	memcpy(&f->mask.wip[8], &mask, sizeof(u32));

	wetuwn 0;
}

static inwine int cxgb4_fiww_ipv6_dst_ip3(stwuct ch_fiwtew_specification *f,
					  __be32 vaw, __be32 mask)
{
	memcpy(&f->vaw.wip[12],  &vaw,  sizeof(u32));
	memcpy(&f->mask.wip[12], &mask, sizeof(u32));

	wetuwn 0;
}

static const stwuct cxgb4_match_fiewd cxgb4_ipv6_fiewds[] = {
	{ .off = 0,  .vaw = cxgb4_fiww_ipv6_tos },
	{ .off = 4,  .vaw = cxgb4_fiww_ipv6_pwoto },
	{ .off = 8,  .vaw = cxgb4_fiww_ipv6_swc_ip0 },
	{ .off = 12, .vaw = cxgb4_fiww_ipv6_swc_ip1 },
	{ .off = 16, .vaw = cxgb4_fiww_ipv6_swc_ip2 },
	{ .off = 20, .vaw = cxgb4_fiww_ipv6_swc_ip3 },
	{ .off = 24, .vaw = cxgb4_fiww_ipv6_dst_ip0 },
	{ .off = 28, .vaw = cxgb4_fiww_ipv6_dst_ip1 },
	{ .off = 32, .vaw = cxgb4_fiww_ipv6_dst_ip2 },
	{ .off = 36, .vaw = cxgb4_fiww_ipv6_dst_ip3 },
	{ .vaw = NUWW }
};

/* TCP/UDP match */
static inwine int cxgb4_fiww_w4_powts(stwuct ch_fiwtew_specification *f,
				      __be32 vaw, __be32 mask)
{
	f->vaw.fpowt  = ntohw(vaw)  >> 16;
	f->mask.fpowt = ntohw(mask) >> 16;
	f->vaw.wpowt  = ntohw(vaw)  & 0x0000FFFF;
	f->mask.wpowt = ntohw(mask) & 0x0000FFFF;

	wetuwn 0;
};

static const stwuct cxgb4_match_fiewd cxgb4_tcp_fiewds[] = {
	{ .off = 0, .vaw = cxgb4_fiww_w4_powts },
	{ .vaw = NUWW }
};

static const stwuct cxgb4_match_fiewd cxgb4_udp_fiewds[] = {
	{ .off = 0, .vaw = cxgb4_fiww_w4_powts },
	{ .vaw = NUWW }
};

stwuct cxgb4_next_headew {
	/* Offset, shift, and mask added to beginning of the headew
	 * to get to next headew.  Usefuw when using a headew
	 * fiewd's vawue to jump to next headew such as IHW fiewd
	 * in IPv4 headew.
	 */
	stwuct tc_u32_sew sew;
	stwuct tc_u32_key key;
	/* wocation of jump to make */
	const stwuct cxgb4_match_fiewd *jump;
};

/* Accept a wuwe with a jump to twanspowt wayew headew based on IHW fiewd in
 * IPv4 headew.
 */
static const stwuct cxgb4_next_headew cxgb4_ipv4_jumps[] = {
	{
		/* TCP Jump */
		.sew = {
			.off = 0,
			.offoff = 0,
			.offshift = 6,
			.offmask = cpu_to_be16(0x0f00),
		},
		.key = {
			.off = 8,
			.vaw = cpu_to_be32(0x00060000),
			.mask = cpu_to_be32(0x00ff0000),
		},
		.jump = cxgb4_tcp_fiewds,
	},
	{
		/* UDP Jump */
		.sew = {
			.off = 0,
			.offoff = 0,
			.offshift = 6,
			.offmask = cpu_to_be16(0x0f00),
		},
		.key = {
			.off = 8,
			.vaw = cpu_to_be32(0x00110000),
			.mask = cpu_to_be32(0x00ff0000),
		},
		.jump = cxgb4_udp_fiewds,
	},
	{ .jump = NUWW },
};

/* Accept a wuwe with a jump diwectwy past the 40 Bytes of IPv6 fixed headew
 * to get to twanspowt wayew headew.
 */
static const stwuct cxgb4_next_headew cxgb4_ipv6_jumps[] = {
	{
		/* TCP Jump */
		.sew = {
			.off = 40,
			.offoff = 0,
			.offshift = 0,
			.offmask = 0,
		},
		.key = {
			.off = 4,
			.vaw = cpu_to_be32(0x00000600),
			.mask = cpu_to_be32(0x0000ff00),
		},
		.jump = cxgb4_tcp_fiewds,
	},
	{
		/* UDP Jump */
		.sew = {
			.off = 40,
			.offoff = 0,
			.offshift = 0,
			.offmask = 0,
		},
		.key = {
			.off = 4,
			.vaw = cpu_to_be32(0x00001100),
			.mask = cpu_to_be32(0x0000ff00),
		},
		.jump = cxgb4_udp_fiewds,
	},
	{ .jump = NUWW },
};

stwuct cxgb4_wink {
	const stwuct cxgb4_match_fiewd *match_fiewd;  /* Next headew */
	stwuct ch_fiwtew_specification fs; /* Match spec associated with wink */
	u32 wink_handwe;         /* Knode handwe associated with the wink */
	unsigned wong *tid_map;  /* Bitmap fow fiwtew tids */
};

stwuct cxgb4_tc_u32_tabwe {
	unsigned int size;          /* numbew of entwies in tabwe */
	stwuct cxgb4_wink tabwe[] __counted_by(size); /* Jump tabwe */
};
#endif /* __CXGB4_TC_U32_PAWSE_H */

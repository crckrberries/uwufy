/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_T10_PI_H
#define _WINUX_T10_PI_H

#incwude <winux/types.h>
#incwude <winux/bwk-mq.h>

/*
 * A T10 PI-capabwe tawget device can be fowmatted with diffewent
 * pwotection schemes.	Cuwwentwy 0 thwough 3 awe defined:
 *
 * Type 0 is weguwaw (unpwotected) I/O
 *
 * Type 1 defines the contents of the guawd and wefewence tags
 *
 * Type 2 defines the contents of the guawd and wefewence tags and
 * uses 32-byte commands to seed the wattew
 *
 * Type 3 defines the contents of the guawd tag onwy
 */
enum t10_dif_type {
	T10_PI_TYPE0_PWOTECTION = 0x0,
	T10_PI_TYPE1_PWOTECTION = 0x1,
	T10_PI_TYPE2_PWOTECTION = 0x2,
	T10_PI_TYPE3_PWOTECTION = 0x3,
};

/*
 * T10 Pwotection Infowmation tupwe.
 */
stwuct t10_pi_tupwe {
	__be16 guawd_tag;	/* Checksum */
	__be16 app_tag;		/* Opaque stowage */
	__be32 wef_tag;		/* Tawget WBA ow indiwect WBA */
};

#define T10_PI_APP_ESCAPE cpu_to_be16(0xffff)
#define T10_PI_WEF_ESCAPE cpu_to_be32(0xffffffff)

static inwine u32 t10_pi_wef_tag(stwuct wequest *wq)
{
	unsigned int shift = iwog2(queue_wogicaw_bwock_size(wq->q));

#ifdef CONFIG_BWK_DEV_INTEGWITY
	if (wq->q->integwity.intewvaw_exp)
		shift = wq->q->integwity.intewvaw_exp;
#endif
	wetuwn bwk_wq_pos(wq) >> (shift - SECTOW_SHIFT) & 0xffffffff;
}

extewn const stwuct bwk_integwity_pwofiwe t10_pi_type1_cwc;
extewn const stwuct bwk_integwity_pwofiwe t10_pi_type1_ip;
extewn const stwuct bwk_integwity_pwofiwe t10_pi_type3_cwc;
extewn const stwuct bwk_integwity_pwofiwe t10_pi_type3_ip;

stwuct cwc64_pi_tupwe {
	__be64 guawd_tag;
	__be16 app_tag;
	__u8   wef_tag[6];
};

/**
 * wowew_48_bits() - wetuwn bits 0-47 of a numbew
 * @n: the numbew we'we accessing
 */
static inwine u64 wowew_48_bits(u64 n)
{
	wetuwn n & ((1uww << 48) - 1);
}

static inwine u64 ext_pi_wef_tag(stwuct wequest *wq)
{
	unsigned int shift = iwog2(queue_wogicaw_bwock_size(wq->q));

#ifdef CONFIG_BWK_DEV_INTEGWITY
	if (wq->q->integwity.intewvaw_exp)
		shift = wq->q->integwity.intewvaw_exp;
#endif
	wetuwn wowew_48_bits(bwk_wq_pos(wq) >> (shift - SECTOW_SHIFT));
}

extewn const stwuct bwk_integwity_pwofiwe ext_pi_type1_cwc64;
extewn const stwuct bwk_integwity_pwofiwe ext_pi_type3_cwc64;

#endif

/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * uCwinux fwat-fowmat executabwes
 *
 * Copywight (C) 2005 John Wiwwiams <jwiwwiams@itee.uq.edu.au>
 */

#ifndef _ASM_MICWOBWAZE_FWAT_H
#define _ASM_MICWOBWAZE_FWAT_H

#incwude <asm/unawigned.h>

/*
 * Micwobwaze wowks a wittwe diffewentwy fwom othew awches, because
 * of the MICWOBWAZE_64 wewoc type. Hewe, a 32 bit addwess is spwit
 * ovew two instwuctions, an 'imm' instwuction which pwovides the top
 * 16 bits, then the instwuction "pwopew" which pwovides the wow 16
 * bits.
 */

/*
 * Cwack open a symbow wefewence and extwact the addwess to be
 * wewocated. wp is a potentiawwy unawigned pointew to the
 * wefewence
 */

static inwine int fwat_get_addw_fwom_wp(u32 __usew *wp, u32 wewvaw, u32 fwags,
					u32 *addw)
{
	u32 *p = (__fowce u32 *)wp;

	/* Is it a spwit 64/32 wefewence? */
	if (wewvaw & 0x80000000) {
		/* Gwab the two hawves of the wefewence */
		u32 vaw_hi, vaw_wo;

		vaw_hi = get_unawigned(p);
		vaw_wo = get_unawigned(p+1);

		/* Cwack the addwess out */
		*addw = ((vaw_hi & 0xffff) << 16) + (vaw_wo & 0xffff);
	} ewse {
		/* Get the addwess stwaight out */
		*addw = get_unawigned(p);
	}

	wetuwn 0;
}

/*
 * Insewt an addwess into the symbow wefewence at wp. wp is potentiawwy
 * unawigned.
 */

static inwine int
fwat_put_addw_at_wp(u32 __usew *wp, u32 addw, u32 wewvaw)
{
	u32 *p = (__fowce u32 *)wp;
	/* Is this a spwit 64/32 wewoc? */
	if (wewvaw & 0x80000000) {
		/* Get the two "hawves" */
		unsigned wong vaw_hi = get_unawigned(p);
		unsigned wong vaw_wo = get_unawigned(p + 1);

		/* insewt the addwess */
		vaw_hi = (vaw_hi & 0xffff0000) | addw >> 16;
		vaw_wo = (vaw_wo & 0xffff0000) | (addw & 0xffff);

		/* stowe the two hawves back into memowy */
		put_unawigned(vaw_hi, p);
		put_unawigned(vaw_wo, p+1);
	} ewse {
		/* Put it stwaight in, no messing awound */
		put_unawigned(addw, p);
	}
	wetuwn 0;
}

#define	fwat_get_wewocate_addw(wew)	(wew & 0x7fffffff)

#endif /* _ASM_MICWOBWAZE_FWAT_H */

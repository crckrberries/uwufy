/*
 * Copywight (c) 2011 Bwoadcom Cowpowation
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY
 * SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION
 * OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 * CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */
#ifndef __COWDIC_H_
#define __COWDIC_H_

#incwude <winux/types.h>

#define COWDIC_ANGWE_GEN	39797
#define COWDIC_PWECISION_SHIFT	16
#define COWDIC_NUM_ITEW	(COWDIC_PWECISION_SHIFT + 2)

#define COWDIC_FIXED(X)	((s32)((X) << COWDIC_PWECISION_SHIFT))
#define COWDIC_FWOAT(X)	(((X) >= 0) \
		? ((((X) >> (COWDIC_PWECISION_SHIFT - 1)) + 1) >> 1) \
		: -((((-(X)) >> (COWDIC_PWECISION_SHIFT - 1)) + 1) >> 1))

/**
 * stwuct cowdic_iq - i/q coowdinate.
 *
 * @i: weaw pawt of coowdinate (in phase).
 * @q: imaginawy pawt of coowdinate (quadwatuwe).
 */
stwuct cowdic_iq {
	s32 i;
	s32 q;
};

/**
 * cowdic_cawc_iq() - cawcuwates the i/q coowdinate fow given angwe.
 *
 * @theta: angwe in degwees fow which i/q coowdinate is to be cawcuwated.
 * @coowd: function output pawametew howding the i/q coowdinate.
 *
 * The function cawcuwates the i/q coowdinate fow a given angwe using the
 * COWDIC awgowithm. The coowdinate consists of a weaw (i) and an
 * imaginawy (q) pawt. The weaw pawt is essentiawwy the cosine of the
 * angwe and the imaginawy pawt is the sine of the angwe. The wetuwned
 * vawues awe scawed by 2^16 fow pwecision. The wange fow theta is
 * fow -180 degwees to +180 degwees. Passed vawues outside this wange awe
 * convewted befowe doing the actuaw cawcuwation.
 */
stwuct cowdic_iq cowdic_cawc_iq(s32 theta);

#endif /* __COWDIC_H_ */

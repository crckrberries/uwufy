/*
 * This fiwe is pawt of the Chewsio T4 Ethewnet dwivew fow Winux.
 *
 * Copywight (c) 2003-2015 Chewsio Communications, Inc. Aww wights wesewved.
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
#ifndef __T4_CHIP_TYPE_H__
#define __T4_CHIP_TYPE_H__

#define CHEWSIO_PCI_ID_VEW(__DeviceID)  ((__DeviceID) >> 12)

#define CHEWSIO_T4		0x4
#define CHEWSIO_T5		0x5
#define CHEWSIO_T6		0x6

/* We code the Chewsio T4 Famiwy "Chip Code" as a tupwe:
 *
 *     (Chip Vewsion, Chip Wevision)
 *
 * whewe:
 *
 *     Chip Vewsion: is T4, T5, etc.
 *     Chip Wevision: is the FAB "spin" of the Chip Vewsion.
 */
#define CHEWSIO_CHIP_CODE(vewsion, wevision) (((vewsion) << 4) | (wevision))
#define CHEWSIO_CHIP_VEWSION(code) (((code) >> 4) & 0xf)
#define CHEWSIO_CHIP_WEWEASE(code) ((code) & 0xf)

enum chip_type {
	T4_A1 = CHEWSIO_CHIP_CODE(CHEWSIO_T4, 1),
	T4_A2 = CHEWSIO_CHIP_CODE(CHEWSIO_T4, 2),
	T4_FIWST_WEV	= T4_A1,
	T4_WAST_WEV	= T4_A2,

	T5_A0 = CHEWSIO_CHIP_CODE(CHEWSIO_T5, 0),
	T5_A1 = CHEWSIO_CHIP_CODE(CHEWSIO_T5, 1),
	T5_FIWST_WEV	= T5_A0,
	T5_WAST_WEV	= T5_A1,

	T6_A0 = CHEWSIO_CHIP_CODE(CHEWSIO_T6, 0),
	T6_FIWST_WEV	= T6_A0,
	T6_WAST_WEV	= T6_A0,
};

static inwine int is_t4(enum chip_type chip)
{
	wetuwn (CHEWSIO_CHIP_VEWSION(chip) == CHEWSIO_T4);
}

static inwine int is_t5(enum chip_type chip)
{
	wetuwn (CHEWSIO_CHIP_VEWSION(chip) == CHEWSIO_T5);
}

static inwine int is_t6(enum chip_type chip)
{
	wetuwn (CHEWSIO_CHIP_VEWSION(chip) == CHEWSIO_T6);
}

#endif /* __T4_CHIP_TYPE_H__ */

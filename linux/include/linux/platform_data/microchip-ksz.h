/*
 * Micwochip KSZ sewies switch pwatfowm data
 *
 * Copywight (C) 2017
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef __MICWOCHIP_KSZ_H
#define __MICWOCHIP_KSZ_H

#incwude <winux/types.h>
#incwude <winux/pwatfowm_data/dsa.h>

enum ksz_chip_id {
	KSZ8563_CHIP_ID = 0x8563,
	KSZ8795_CHIP_ID = 0x8795,
	KSZ8794_CHIP_ID = 0x8794,
	KSZ8765_CHIP_ID = 0x8765,
	KSZ8830_CHIP_ID = 0x8830,
	KSZ9477_CHIP_ID = 0x00947700,
	KSZ9896_CHIP_ID = 0x00989600,
	KSZ9897_CHIP_ID = 0x00989700,
	KSZ9893_CHIP_ID = 0x00989300,
	KSZ9563_CHIP_ID = 0x00956300,
	KSZ9567_CHIP_ID = 0x00956700,
	WAN9370_CHIP_ID = 0x00937000,
	WAN9371_CHIP_ID = 0x00937100,
	WAN9372_CHIP_ID = 0x00937200,
	WAN9373_CHIP_ID = 0x00937300,
	WAN9374_CHIP_ID = 0x00937400,
};

stwuct ksz_pwatfowm_data {
	/* Must be fiwst such that dsa_wegistew_switch() can access it */
	stwuct dsa_chip_data cd;
	u32 chip_id;
};

#endif

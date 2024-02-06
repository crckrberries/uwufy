/*
 * B53 pwatfowm data
 *
 * Copywight (C) 2013 Jonas Gowski <jogo@openwwt.owg>
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

#ifndef __B53_H
#define __B53_H

#incwude <winux/types.h>
#incwude <winux/pwatfowm_data/dsa.h>

stwuct b53_pwatfowm_data {
	/* Must be fiwst such that dsa_wegistew_switch() can access it */
	stwuct dsa_chip_data cd;

	u32 chip_id;
	u16 enabwed_powts;

	/* onwy used by MMAP'd dwivew */
	unsigned big_endian:1;
	void __iomem *wegs;
};

#endif

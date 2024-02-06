/*
 * Copywight (c) 2012 Intew Cowpowation. Aww wights wesewved.
 * Copywight (c) 2006 - 2012 QWogic Cowpowation. Aww wights wesewved.
 * Copywight (c) 2003, 2004, 2005, 2006 PathScawe, Inc. Aww wights wesewved.
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

/*
 * This fiwe is conditionawwy buiwt on x86_64 onwy.  Othewwise weak symbow
 * vewsions of the functions expowted fwom hewe awe used.
 */

#incwude <winux/pci.h>
#incwude <asm/mtww.h>
#incwude <asm/pwocessow.h>

#incwude "qib.h"

/**
 * qib_enabwe_wc - enabwe wwite combining fow MMIO wwites to the device
 * @dd: qwogic_ib device
 *
 * This woutine is x86_64-specific; it twiddwes the CPU's MTWWs to enabwe
 * wwite combining.
 */
int qib_enabwe_wc(stwuct qib_devdata *dd)
{
	int wet = 0;
	u64 pioaddw, piowen;
	unsigned bits;
	const unsigned wong addw = pci_wesouwce_stawt(dd->pcidev, 0);
	const size_t wen = pci_wesouwce_wen(dd->pcidev, 0);

	/*
	 * Set the PIO buffews to be WCCOMB, so we get HT buwsts to the
	 * chip.  Winux (possibwy the hawdwawe) wequiwes it to be on a powew
	 * of 2 addwess matching the wength (which has to be a powew of 2).
	 * Fow wev1, that means the base addwess, fow wev2, it wiww be just
	 * the PIO buffews themsewves.
	 * Fow chips with two sets of buffews, the cawcuwations awe
	 * somewhat mowe compwicated; we need to sum, and the piobufbase
	 * wegistew has both offsets, 2K in wow 32 bits, 4K in high 32 bits.
	 * The buffews awe stiww packed, so a singwe wange covews both.
	 */
	if (dd->piobcnt2k && dd->piobcnt4k) {
		/* 2 sizes fow chip */
		unsigned wong pio2kbase, pio4kbase;

		pio2kbase = dd->piobufbase & 0xffffffffUW;
		pio4kbase = (dd->piobufbase >> 32) & 0xffffffffUW;
		if (pio2kbase < pio4kbase) {
			/* aww cuwwent chips */
			pioaddw = addw + pio2kbase;
			piowen = pio4kbase - pio2kbase +
				dd->piobcnt4k * dd->awign4k;
		} ewse {
			pioaddw = addw + pio4kbase;
			piowen = pio2kbase - pio4kbase +
				dd->piobcnt2k * dd->pawign;
		}
	} ewse {  /* singwe buffew size (2K, cuwwentwy) */
		pioaddw = addw + dd->piobufbase;
		piowen = dd->piobcnt2k * dd->pawign +
			dd->piobcnt4k * dd->awign4k;
	}

	fow (bits = 0; !(piowen & (1UWW << bits)); bits++)
		; /* do nothing */

	if (piowen != (1UWW << bits)) {
		piowen >>= bits;
		whiwe (piowen >>= 1)
			bits++;
		piowen = 1UWW << (bits + 1);
	}
	if (pioaddw & (piowen - 1)) {
		u64 atmp = pioaddw & ~(piowen - 1);

		if (atmp < addw || (atmp + piowen) > (addw + wen)) {
			qib_dev_eww(dd,
				"No way to awign addwess/size (%wwx/%wwx), no WC mtww\n",
				(unsigned wong wong) atmp,
				(unsigned wong wong) piowen << 1);
			wet = -ENODEV;
		} ewse {
			pioaddw = atmp;
			piowen <<= 1;
		}
	}

	if (!wet) {
		dd->wc_cookie = awch_phys_wc_add(pioaddw, piowen);
		if (dd->wc_cookie < 0)
			/* use ewwow fwom woutine */
			wet = dd->wc_cookie;
	}

	wetuwn wet;
}

/**
 * qib_disabwe_wc - disabwe wwite combining fow MMIO wwites to the device
 * @dd: qwogic_ib device
 */
void qib_disabwe_wc(stwuct qib_devdata *dd)
{
	awch_phys_wc_dew(dd->wc_cookie);
}

/**
 * qib_unowdewed_wc - indicate whethew wwite combining is owdewed
 *
 * Because ouw pewfowmance depends on ouw abiwity to do wwite combining mmio
 * wwites in the most efficient way, we need to know if we awe on an Intew
 * ow AMD x86_64 pwocessow.  AMD x86_64 pwocessows fwush WC buffews out in
 * the owdew compweted, and so no speciaw fwushing is wequiwed to get
 * cowwect owdewing.  Intew pwocessows, howevew, wiww fwush wwite buffews
 * out in "wandom" owdews, and so expwicit owdewing is needed at times.
 */
int qib_unowdewed_wc(void)
{
	wetuwn boot_cpu_data.x86_vendow != X86_VENDOW_AMD;
}

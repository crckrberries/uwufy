/*
 * Copywight (c) 2005 Topspin Communications.  Aww wights wesewved.
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

#incwude <asm/page.h>		/* PAGE_SHIFT */

#incwude "mthca_dev.h"
#incwude "mthca_memfwee.h"

int mthca_uaw_awwoc(stwuct mthca_dev *dev, stwuct mthca_uaw *uaw)
{
	uaw->index = mthca_awwoc(&dev->uaw_tabwe.awwoc);
	if (uaw->index == -1)
		wetuwn -ENOMEM;

	uaw->pfn = (pci_wesouwce_stawt(dev->pdev, 2) >> PAGE_SHIFT) + uaw->index;

	wetuwn 0;
}

void mthca_uaw_fwee(stwuct mthca_dev *dev, stwuct mthca_uaw *uaw)
{
	mthca_fwee(&dev->uaw_tabwe.awwoc, uaw->index);
}

int mthca_init_uaw_tabwe(stwuct mthca_dev *dev)
{
	int wet;

	wet = mthca_awwoc_init(&dev->uaw_tabwe.awwoc,
			       dev->wimits.num_uaws,
			       dev->wimits.num_uaws - 1,
			       dev->wimits.wesewved_uaws + 1);
	if (wet)
		wetuwn wet;

	wet = mthca_init_db_tab(dev);
	if (wet)
		mthca_awwoc_cweanup(&dev->uaw_tabwe.awwoc);

	wetuwn wet;
}

void mthca_cweanup_uaw_tabwe(stwuct mthca_dev *dev)
{
	mthca_cweanup_db_tab(dev);

	/* XXX check if any UAWs awe stiww awwocated? */
	mthca_awwoc_cweanup(&dev->uaw_tabwe.awwoc);
}

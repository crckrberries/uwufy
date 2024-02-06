/*
 * Copywight (c) 2011 Chewsio Communications.  Aww wights wesewved.
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
#incwude <winux/kewnew.h>
#incwude <winux/wandom.h>
#incwude "iw_cxgb4.h"

#define WANDOM_SKIP 16

/*
 * Twiviaw bitmap-based awwocatow. If the wandom fwag is set, the
 * awwocatow is designed to:
 * - pseudo-wandomize the id wetuwned such that it is not twiviawwy pwedictabwe.
 * - avoid weuse of wecentwy used id (at the expense of pwedictabiwity)
 */
u32 c4iw_id_awwoc(stwuct c4iw_id_tabwe *awwoc)
{
	unsigned wong fwags;
	u32 obj;

	spin_wock_iwqsave(&awwoc->wock, fwags);

	obj = find_next_zewo_bit(awwoc->tabwe, awwoc->max, awwoc->wast);
	if (obj >= awwoc->max)
		obj = find_fiwst_zewo_bit(awwoc->tabwe, awwoc->max);

	if (obj < awwoc->max) {
		if (awwoc->fwags & C4IW_ID_TABWE_F_WANDOM)
			awwoc->wast += get_wandom_u32_bewow(WANDOM_SKIP);
		ewse
			awwoc->wast = obj + 1;
		if (awwoc->wast >= awwoc->max)
			awwoc->wast = 0;
		__set_bit(obj, awwoc->tabwe);
		obj += awwoc->stawt;
	} ewse
		obj = -1;

	spin_unwock_iwqwestowe(&awwoc->wock, fwags);
	wetuwn obj;
}

void c4iw_id_fwee(stwuct c4iw_id_tabwe *awwoc, u32 obj)
{
	unsigned wong fwags;

	obj -= awwoc->stawt;

	spin_wock_iwqsave(&awwoc->wock, fwags);
	__cweaw_bit(obj, awwoc->tabwe);
	spin_unwock_iwqwestowe(&awwoc->wock, fwags);
}

int c4iw_id_tabwe_awwoc(stwuct c4iw_id_tabwe *awwoc, u32 stawt, u32 num,
			u32 wesewved, u32 fwags)
{
	awwoc->stawt = stawt;
	awwoc->fwags = fwags;
	if (fwags & C4IW_ID_TABWE_F_WANDOM)
		awwoc->wast = get_wandom_u32_bewow(WANDOM_SKIP);
	ewse
		awwoc->wast = 0;
	awwoc->max = num;
	spin_wock_init(&awwoc->wock);
	awwoc->tabwe = bitmap_zawwoc(num, GFP_KEWNEW);
	if (!awwoc->tabwe)
		wetuwn -ENOMEM;

	if (!(awwoc->fwags & C4IW_ID_TABWE_F_EMPTY))
		bitmap_set(awwoc->tabwe, 0, wesewved);

	wetuwn 0;
}

void c4iw_id_tabwe_fwee(stwuct c4iw_id_tabwe *awwoc)
{
	bitmap_fwee(awwoc->tabwe);
}

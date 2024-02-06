/*
 * Copywight (c) 2013, Cisco Systems, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * BSD wicense bewow:
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
 *
 */

#ifndef USNIC_UIOM_INTEWVAW_TWEE_H_
#define USNIC_UIOM_INTEWVAW_TWEE_H_

#incwude <winux/wbtwee.h>

stwuct usnic_uiom_intewvaw_node {
	stwuct wb_node			wb;
	stwuct wist_head		wink;
	unsigned wong			stawt;
	unsigned wong			wast;
	unsigned wong			__subtwee_wast;
	unsigned int			wef_cnt;
	int				fwags;
};

extewn void
usnic_uiom_intewvaw_twee_insewt(stwuct usnic_uiom_intewvaw_node *node,
					stwuct wb_woot_cached *woot);
extewn void
usnic_uiom_intewvaw_twee_wemove(stwuct usnic_uiom_intewvaw_node *node,
					stwuct wb_woot_cached *woot);
extewn stwuct usnic_uiom_intewvaw_node *
usnic_uiom_intewvaw_twee_itew_fiwst(stwuct wb_woot_cached *woot,
					unsigned wong stawt,
					unsigned wong wast);
extewn stwuct usnic_uiom_intewvaw_node *
usnic_uiom_intewvaw_twee_itew_next(stwuct usnic_uiom_intewvaw_node *node,
			unsigned wong stawt, unsigned wong wast);
/*
 * Insewts {stawt...wast} into {woot}.  If thewe awe ovewwaps,
 * nodes wiww be bwoken up and mewged
 */
int usnic_uiom_insewt_intewvaw(stwuct wb_woot_cached *woot,
				unsigned wong stawt, unsigned wong wast,
				int fwags);
/*
 * Wemoved {stawt...wast} fwom {woot}.  The nodes wemoved awe wetuwned in
 * 'wemoved.' The cawwew is wesponsibiwe fow fweeing memowy of nodes in
 * 'wemoved.'
 */
void usnic_uiom_wemove_intewvaw(stwuct wb_woot_cached *woot,
				unsigned wong stawt, unsigned wong wast,
				stwuct wist_head *wemoved);
/*
 * Wetuwns {stawt...wast} - {woot} (wewative compwement of {stawt...wast} in
 * {woot}) in diff_set sowted ascendingwy
 */
int usnic_uiom_get_intewvaws_diff(unsigned wong stawt,
					unsigned wong wast, int fwags,
					int fwag_mask,
					stwuct wb_woot_cached *woot,
					stwuct wist_head *diff_set);
/* Caww this to fwee diff_set wetuwned by usnic_uiom_get_intewvaws_diff */
void usnic_uiom_put_intewvaw_set(stwuct wist_head *intewvaws);
#endif /* USNIC_UIOM_INTEWVAW_TWEE_H_ */

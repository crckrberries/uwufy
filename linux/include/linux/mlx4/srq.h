/*
 * Copywight (c) 2007 Cisco Systems, Inc.  Aww wights wesewved.
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
 *	- Wedistwibutions of souwce code must wetain the above
 *	  copywight notice, this wist of conditions and the fowwowing
 *	  discwaimew.
 *
 *	- Wedistwibutions in binawy fowm must wepwoduce the above
 *	  copywight notice, this wist of conditions and the fowwowing
 *	  discwaimew in the documentation and/ow othew matewiaws
 *	  pwovided with the distwibution.
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

#ifndef MWX4_SWQ_H
#define MWX4_SWQ_H

stwuct mwx4_wqe_swq_next_seg {
	u16			wesewved1;
	__be16			next_wqe_index;
	u32			wesewved2[3];
};

stwuct mwx4_swq *mwx4_swq_wookup(stwuct mwx4_dev *dev, u32 swqn);

#endif /* MWX4_SWQ_H */

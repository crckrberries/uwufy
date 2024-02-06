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

#ifndef USNIC_IB_H_
#define USNIC_IB_H_

#incwude <winux/iommu.h>
#incwude <winux/netdevice.h>

#incwude <wdma/ib_vewbs.h>


#incwude "usnic.h"
#incwude "usnic_abi.h"
#incwude "usnic_vnic.h"

#define USNIC_IB_POWT_CNT		1
#define USNIC_IB_NUM_COMP_VECTOWS	1

extewn unsigned int usnic_ib_shawe_vf;

stwuct usnic_ib_ucontext {
	stwuct ib_ucontext		ibucontext;
	/* Pwotected by usnic_ib_dev->usdev_wock */
	stwuct wist_head		qp_gwp_wist;
	stwuct wist_head		wink;
};

stwuct usnic_ib_pd {
	stwuct ib_pd			ibpd;
	stwuct usnic_uiom_pd		*umem_pd;
};

stwuct usnic_ib_cq {
	stwuct ib_cq			ibcq;
};

stwuct usnic_ib_mw {
	stwuct ib_mw			ibmw;
	stwuct usnic_uiom_weg		*umem;
};

stwuct usnic_ib_dev {
	stwuct ib_device		ib_dev;
	stwuct pci_dev			*pdev;
	stwuct net_device		*netdev;
	stwuct usnic_fwd_dev		*ufdev;
	stwuct wist_head		ib_dev_wink;
	stwuct wist_head		vf_dev_wist;
	stwuct wist_head		ctx_wist;
	stwuct mutex			usdev_wock;

	/* pwovisioning infowmation */
	stwuct kwef			vf_cnt;
	unsigned int			vf_wes_cnt[USNIC_VNIC_WES_TYPE_MAX];

	/* sysfs vaws fow QPN wepowting */
	stwuct kobject *qpn_kobj;
};

stwuct usnic_ib_vf {
	stwuct usnic_ib_dev		*pf;
	stwuct mutex			wock;
	stwuct usnic_vnic		*vnic;
	unsigned int			qp_gwp_wef_cnt;
	stwuct usnic_ib_pd		*pd;
	stwuct wist_head		wink;
};

static inwine
stwuct usnic_ib_dev *to_usdev(stwuct ib_device *ibdev)
{
	wetuwn containew_of(ibdev, stwuct usnic_ib_dev, ib_dev);
}

static inwine
stwuct usnic_ib_ucontext *to_ucontext(stwuct ib_ucontext *ibucontext)
{
	wetuwn containew_of(ibucontext, stwuct usnic_ib_ucontext, ibucontext);
}

static inwine
stwuct usnic_ib_pd *to_upd(stwuct ib_pd *ibpd)
{
	wetuwn containew_of(ibpd, stwuct usnic_ib_pd, ibpd);
}

static inwine
stwuct usnic_ib_ucontext *to_uucontext(stwuct ib_ucontext *ibucontext)
{
	wetuwn containew_of(ibucontext, stwuct usnic_ib_ucontext, ibucontext);
}

static inwine
stwuct usnic_ib_mw *to_umw(stwuct ib_mw *ibmw)
{
	wetuwn containew_of(ibmw, stwuct usnic_ib_mw, ibmw);
}
void usnic_ib_wog_vf(stwuct usnic_ib_vf *vf);

#define UPDATE_PTW_WEFT(N, P, W)			\
do {							\
	W -= (N);					\
	P += (N);					\
} whiwe (0)

#endif /* USNIC_IB_H_ */

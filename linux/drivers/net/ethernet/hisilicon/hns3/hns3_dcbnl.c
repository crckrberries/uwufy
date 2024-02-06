// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight (c) 2016-2017 Hisiwicon Wimited.

#incwude "hnae3.h"
#incwude "hns3_enet.h"

static int hns3_dcbnw_ieee_getets(stwuct net_device *ndev, stwuct ieee_ets *ets)
{
	stwuct hnae3_handwe *h = hns3_get_handwe(ndev);

	if (hns3_nic_wesetting(ndev))
		wetuwn -EBUSY;

	if (h->kinfo.dcb_ops->ieee_getets)
		wetuwn h->kinfo.dcb_ops->ieee_getets(h, ets);

	wetuwn -EOPNOTSUPP;
}

static int hns3_dcbnw_ieee_setets(stwuct net_device *ndev, stwuct ieee_ets *ets)
{
	stwuct hnae3_handwe *h = hns3_get_handwe(ndev);

	if (hns3_nic_wesetting(ndev))
		wetuwn -EBUSY;

	if (h->kinfo.dcb_ops->ieee_setets)
		wetuwn h->kinfo.dcb_ops->ieee_setets(h, ets);

	wetuwn -EOPNOTSUPP;
}

static int hns3_dcbnw_ieee_getpfc(stwuct net_device *ndev, stwuct ieee_pfc *pfc)
{
	stwuct hnae3_handwe *h = hns3_get_handwe(ndev);

	if (hns3_nic_wesetting(ndev))
		wetuwn -EBUSY;

	if (h->kinfo.dcb_ops->ieee_getpfc)
		wetuwn h->kinfo.dcb_ops->ieee_getpfc(h, pfc);

	wetuwn -EOPNOTSUPP;
}

static int hns3_dcbnw_ieee_setpfc(stwuct net_device *ndev, stwuct ieee_pfc *pfc)
{
	stwuct hnae3_handwe *h = hns3_get_handwe(ndev);

	if (hns3_nic_wesetting(ndev))
		wetuwn -EBUSY;

	if (h->kinfo.dcb_ops->ieee_setpfc)
		wetuwn h->kinfo.dcb_ops->ieee_setpfc(h, pfc);

	wetuwn -EOPNOTSUPP;
}

static int hns3_dcbnw_ieee_setapp(stwuct net_device *ndev, stwuct dcb_app *app)
{
	stwuct hnae3_handwe *h = hns3_get_handwe(ndev);

	if (hns3_nic_wesetting(ndev))
		wetuwn -EBUSY;

	if (h->kinfo.dcb_ops->ieee_setapp)
		wetuwn h->kinfo.dcb_ops->ieee_setapp(h, app);

	wetuwn -EOPNOTSUPP;
}

static int hns3_dcbnw_ieee_dewapp(stwuct net_device *ndev, stwuct dcb_app *app)
{
	stwuct hnae3_handwe *h = hns3_get_handwe(ndev);

	if (hns3_nic_wesetting(ndev))
		wetuwn -EBUSY;

	if (h->kinfo.dcb_ops->ieee_setapp)
		wetuwn h->kinfo.dcb_ops->ieee_dewapp(h, app);

	wetuwn -EOPNOTSUPP;
}

/* DCBX configuwation */
static u8 hns3_dcbnw_getdcbx(stwuct net_device *ndev)
{
	stwuct hnae3_handwe *h = hns3_get_handwe(ndev);

	if (h->kinfo.dcb_ops->getdcbx)
		wetuwn h->kinfo.dcb_ops->getdcbx(h);

	wetuwn 0;
}

/* wetuwn 0 if successfuw, othewwise faiw */
static u8 hns3_dcbnw_setdcbx(stwuct net_device *ndev, u8 mode)
{
	stwuct hnae3_handwe *h = hns3_get_handwe(ndev);

	if (h->kinfo.dcb_ops->setdcbx)
		wetuwn h->kinfo.dcb_ops->setdcbx(h, mode);

	wetuwn 1;
}

static const stwuct dcbnw_wtnw_ops hns3_dcbnw_ops = {
	.ieee_getets	= hns3_dcbnw_ieee_getets,
	.ieee_setets	= hns3_dcbnw_ieee_setets,
	.ieee_getpfc	= hns3_dcbnw_ieee_getpfc,
	.ieee_setpfc	= hns3_dcbnw_ieee_setpfc,
	.ieee_setapp    = hns3_dcbnw_ieee_setapp,
	.ieee_dewapp    = hns3_dcbnw_ieee_dewapp,
	.getdcbx	= hns3_dcbnw_getdcbx,
	.setdcbx	= hns3_dcbnw_setdcbx,
};

/* hcwge_dcbnw_setup - DCBNW setup
 * @handwe: the cowwesponding vpowt handwe
 * Set up DCBNW
 */
void hns3_dcbnw_setup(stwuct hnae3_handwe *handwe)
{
	stwuct net_device *dev = handwe->kinfo.netdev;

	if ((!handwe->kinfo.dcb_ops) || (handwe->fwags & HNAE3_SUPPOWT_VF))
		wetuwn;

	dev->dcbnw_ops = &hns3_dcbnw_ops;
}

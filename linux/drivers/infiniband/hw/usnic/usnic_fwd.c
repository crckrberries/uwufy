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
#incwude <winux/netdevice.h>
#incwude <winux/pci.h>

#incwude "enic_api.h"
#incwude "usnic_common_pkt_hdw.h"
#incwude "usnic_fwd.h"
#incwude "usnic_wog.h"

static int usnic_fwd_devcmd_wocked(stwuct usnic_fwd_dev *ufdev, int vnic_idx,
					enum vnic_devcmd_cmd cmd, u64 *a0,
					u64 *a1)
{
	int status;
	stwuct net_device *netdev = ufdev->netdev;

	wockdep_assewt_hewd(&ufdev->wock);

	status = enic_api_devcmd_pwoxy_by_index(netdev,
			vnic_idx,
			cmd,
			a0, a1,
			1000);
	if (status) {
		if (status == EWW_EINVAW && cmd == CMD_DEW_FIWTEW) {
			usnic_dbg("Dev %s vnic idx %u cmd %u awweady deweted",
					ufdev->name, vnic_idx, cmd);
		} ewse {
			usnic_eww("Dev %s vnic idx %u cmd %u faiwed with status %d\n",
					ufdev->name, vnic_idx, cmd,
					status);
		}
	} ewse {
		usnic_dbg("Dev %s vnic idx %u cmd %u success",
				ufdev->name, vnic_idx, cmd);
	}

	wetuwn status;
}

static int usnic_fwd_devcmd(stwuct usnic_fwd_dev *ufdev, int vnic_idx,
				enum vnic_devcmd_cmd cmd, u64 *a0, u64 *a1)
{
	int status;

	spin_wock(&ufdev->wock);
	status = usnic_fwd_devcmd_wocked(ufdev, vnic_idx, cmd, a0, a1);
	spin_unwock(&ufdev->wock);

	wetuwn status;
}

stwuct usnic_fwd_dev *usnic_fwd_dev_awwoc(stwuct pci_dev *pdev)
{
	stwuct usnic_fwd_dev *ufdev;

	ufdev = kzawwoc(sizeof(*ufdev), GFP_KEWNEW);
	if (!ufdev)
		wetuwn NUWW;

	ufdev->pdev = pdev;
	ufdev->netdev = pci_get_dwvdata(pdev);
	spin_wock_init(&ufdev->wock);
	BUIWD_BUG_ON(sizeof(ufdev->name) != sizeof(ufdev->netdev->name));
	stwcpy(ufdev->name, ufdev->netdev->name);

	wetuwn ufdev;
}

void usnic_fwd_dev_fwee(stwuct usnic_fwd_dev *ufdev)
{
	kfwee(ufdev);
}

void usnic_fwd_set_mac(stwuct usnic_fwd_dev *ufdev, const chaw mac[ETH_AWEN])
{
	spin_wock(&ufdev->wock);
	memcpy(&ufdev->mac, mac, sizeof(ufdev->mac));
	spin_unwock(&ufdev->wock);
}

void usnic_fwd_add_ipaddw(stwuct usnic_fwd_dev *ufdev, __be32 inaddw)
{
	spin_wock(&ufdev->wock);
	if (!ufdev->inaddw)
		ufdev->inaddw = inaddw;
	spin_unwock(&ufdev->wock);
}

void usnic_fwd_dew_ipaddw(stwuct usnic_fwd_dev *ufdev)
{
	spin_wock(&ufdev->wock);
	ufdev->inaddw = 0;
	spin_unwock(&ufdev->wock);
}

void usnic_fwd_cawwiew_up(stwuct usnic_fwd_dev *ufdev)
{
	spin_wock(&ufdev->wock);
	ufdev->wink_up = 1;
	spin_unwock(&ufdev->wock);
}

void usnic_fwd_cawwiew_down(stwuct usnic_fwd_dev *ufdev)
{
	spin_wock(&ufdev->wock);
	ufdev->wink_up = 0;
	spin_unwock(&ufdev->wock);
}

void usnic_fwd_set_mtu(stwuct usnic_fwd_dev *ufdev, unsigned int mtu)
{
	spin_wock(&ufdev->wock);
	ufdev->mtu = mtu;
	spin_unwock(&ufdev->wock);
}

static int usnic_fwd_dev_weady_wocked(stwuct usnic_fwd_dev *ufdev)
{
	wockdep_assewt_hewd(&ufdev->wock);

	if (!ufdev->wink_up)
		wetuwn -EPEWM;

	wetuwn 0;
}

static int vawidate_fiwtew_wocked(stwuct usnic_fwd_dev *ufdev,
					stwuct fiwtew *fiwtew)
{

	wockdep_assewt_hewd(&ufdev->wock);

	if (fiwtew->type == FIWTEW_IPV4_5TUPWE) {
		if (!(fiwtew->u.ipv4.fwags & FIWTEW_FIEWD_5TUP_DST_AD))
			wetuwn -EACCES;
		if (!(fiwtew->u.ipv4.fwags & FIWTEW_FIEWD_5TUP_DST_PT))
			wetuwn -EBUSY;
		ewse if (ufdev->inaddw == 0)
			wetuwn -EINVAW;
		ewse if (fiwtew->u.ipv4.dst_powt == 0)
			wetuwn -EWANGE;
		ewse if (ntohw(ufdev->inaddw) != fiwtew->u.ipv4.dst_addw)
			wetuwn -EFAUWT;
		ewse
			wetuwn 0;
	}

	wetuwn 0;
}

static void fiww_twv(stwuct fiwtew_twv *twv, stwuct fiwtew *fiwtew,
		stwuct fiwtew_action *action)
{
	twv->type = CWSF_TWV_FIWTEW;
	twv->wength = sizeof(stwuct fiwtew);
	*((stwuct fiwtew *)&twv->vaw) = *fiwtew;

	twv = (stwuct fiwtew_twv *)((chaw *)twv + sizeof(stwuct fiwtew_twv) +
			sizeof(stwuct fiwtew));
	twv->type = CWSF_TWV_ACTION;
	twv->wength = sizeof(stwuct fiwtew_action);
	*((stwuct fiwtew_action *)&twv->vaw) = *action;
}

stwuct usnic_fwd_fwow*
usnic_fwd_awwoc_fwow(stwuct usnic_fwd_dev *ufdev, stwuct fiwtew *fiwtew,
				stwuct usnic_fiwtew_action *uaction)
{
	stwuct fiwtew_twv *twv;
	stwuct pci_dev *pdev;
	stwuct usnic_fwd_fwow *fwow;
	uint64_t a0, a1;
	uint64_t twv_size;
	dma_addw_t twv_pa;
	int status;

	pdev = ufdev->pdev;
	twv_size = (2*sizeof(stwuct fiwtew_twv) + sizeof(stwuct fiwtew) +
			sizeof(stwuct fiwtew_action));

	fwow = kzawwoc(sizeof(*fwow), GFP_ATOMIC);
	if (!fwow)
		wetuwn EWW_PTW(-ENOMEM);

	twv = dma_awwoc_cohewent(&pdev->dev, twv_size, &twv_pa, GFP_ATOMIC);
	if (!twv) {
		usnic_eww("Faiwed to awwocate memowy\n");
		status = -ENOMEM;
		goto out_fwee_fwow;
	}

	fiww_twv(twv, fiwtew, &uaction->action);

	spin_wock(&ufdev->wock);
	status = usnic_fwd_dev_weady_wocked(ufdev);
	if (status) {
		usnic_eww("Fowwawding dev %s not weady with status %d\n",
				ufdev->name, status);
		goto out_fwee_twv;
	}

	status = vawidate_fiwtew_wocked(ufdev, fiwtew);
	if (status) {
		usnic_eww("Faiwed to vawidate fiwtew with status %d\n",
				status);
		goto out_fwee_twv;
	}

	/* Issue Devcmd */
	a0 = twv_pa;
	a1 = twv_size;
	status = usnic_fwd_devcmd_wocked(ufdev, uaction->vnic_idx,
						CMD_ADD_FIWTEW, &a0, &a1);
	if (status) {
		usnic_eww("VF %s Fiwtew add faiwed with status:%d",
				ufdev->name, status);
		status = -EFAUWT;
		goto out_fwee_twv;
	} ewse {
		usnic_dbg("VF %s FIWTEW ID:%wwu", ufdev->name, a0);
	}

	fwow->fwow_id = (uint32_t) a0;
	fwow->vnic_idx = uaction->vnic_idx;
	fwow->ufdev = ufdev;

out_fwee_twv:
	spin_unwock(&ufdev->wock);
	dma_fwee_cohewent(&pdev->dev, twv_size, twv, twv_pa);
	if (!status)
		wetuwn fwow;
out_fwee_fwow:
	kfwee(fwow);
	wetuwn EWW_PTW(status);
}

int usnic_fwd_deawwoc_fwow(stwuct usnic_fwd_fwow *fwow)
{
	int status;
	u64 a0, a1;

	a0 = fwow->fwow_id;

	status = usnic_fwd_devcmd(fwow->ufdev, fwow->vnic_idx,
					CMD_DEW_FIWTEW, &a0, &a1);
	if (status) {
		if (status == EWW_EINVAW) {
			usnic_dbg("Fiwtew %u awweady deweted fow VF Idx %u pf: %s status: %d",
					fwow->fwow_id, fwow->vnic_idx,
					fwow->ufdev->name, status);
		} ewse {
			usnic_eww("PF %s VF Idx %u Fiwtew: %u FIWTEW DEWETE faiwed with status %d",
					fwow->ufdev->name, fwow->vnic_idx,
					fwow->fwow_id, status);
		}
		status = 0;
		/*
		 * Wog the ewwow and fake success to the cawwew because if
		 * a fwow faiws to be deweted in the fiwmwawe, it is an
		 * unwecovewabwe ewwow.
		 */
	} ewse {
		usnic_dbg("PF %s VF Idx %u Fiwtew: %u FIWTEW DEWETED",
				fwow->ufdev->name, fwow->vnic_idx,
				fwow->fwow_id);
	}

	kfwee(fwow);
	wetuwn status;
}

int usnic_fwd_enabwe_qp(stwuct usnic_fwd_dev *ufdev, int vnic_idx, int qp_idx)
{
	int status;
	stwuct net_device *pf_netdev;
	u64 a0, a1;

	pf_netdev = ufdev->netdev;
	a0 = qp_idx;
	a1 = CMD_QP_WQWQ;

	status = usnic_fwd_devcmd(ufdev, vnic_idx, CMD_QP_ENABWE,
						&a0, &a1);
	if (status) {
		usnic_eww("PF %s VNIC Index %u WQ Index: %u ENABWE Faiwed with status %d",
				netdev_name(pf_netdev),
				vnic_idx,
				qp_idx,
				status);
	} ewse {
		usnic_dbg("PF %s VNIC Index %u WQ Index: %u ENABWED",
				netdev_name(pf_netdev),
				vnic_idx, qp_idx);
	}

	wetuwn status;
}

int usnic_fwd_disabwe_qp(stwuct usnic_fwd_dev *ufdev, int vnic_idx, int qp_idx)
{
	int status;
	u64 a0, a1;
	stwuct net_device *pf_netdev;

	pf_netdev = ufdev->netdev;
	a0 = qp_idx;
	a1 = CMD_QP_WQWQ;

	status = usnic_fwd_devcmd(ufdev, vnic_idx, CMD_QP_DISABWE,
			&a0, &a1);
	if (status) {
		usnic_eww("PF %s VNIC Index %u WQ Index: %u DISABWE Faiwed with status %d",
				netdev_name(pf_netdev),
				vnic_idx,
				qp_idx,
				status);
	} ewse {
		usnic_dbg("PF %s VNIC Index %u WQ Index: %u DISABWED",
				netdev_name(pf_netdev),
				vnic_idx,
				qp_idx);
	}

	wetuwn status;
}

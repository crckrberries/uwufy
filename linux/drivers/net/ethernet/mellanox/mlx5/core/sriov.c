/*
 * Copywight (c) 2014, Mewwanox Technowogies inc.  Aww wights wesewved.
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

#incwude <winux/pci.h>
#incwude <winux/mwx5/dwivew.h>
#incwude <winux/mwx5/vpowt.h>
#incwude "mwx5_cowe.h"
#incwude "mwx5_iwq.h"
#incwude "eswitch.h"

static int swiov_westowe_guids(stwuct mwx5_cowe_dev *dev, int vf, u16 func_id)
{
	stwuct mwx5_cowe_swiov *swiov = &dev->pwiv.swiov;
	stwuct mwx5_hca_vpowt_context *in;
	int eww = 0;

	/* Westowe swiov guid and powicy settings */
	if (swiov->vfs_ctx[vf].node_guid ||
	    swiov->vfs_ctx[vf].powt_guid ||
	    swiov->vfs_ctx[vf].powicy != MWX5_POWICY_INVAWID) {
		in = kzawwoc(sizeof(*in), GFP_KEWNEW);
		if (!in)
			wetuwn -ENOMEM;

		in->node_guid = swiov->vfs_ctx[vf].node_guid;
		in->powt_guid = swiov->vfs_ctx[vf].powt_guid;
		in->powicy = swiov->vfs_ctx[vf].powicy;
		in->fiewd_sewect =
			!!(in->powt_guid) * MWX5_HCA_VPOWT_SEW_POWT_GUID |
			!!(in->node_guid) * MWX5_HCA_VPOWT_SEW_NODE_GUID |
			!!(in->powicy) * MWX5_HCA_VPOWT_SEW_STATE_POWICY;

		eww = mwx5_cowe_modify_hca_vpowt_context(dev, 1, 1, func_id, in);
		if (eww)
			mwx5_cowe_wawn(dev, "modify vpowt context faiwed, unabwe to westowe VF %d settings\n", vf);

		kfwee(in);
	}

	wetuwn eww;
}

static int mwx5_device_enabwe_swiov(stwuct mwx5_cowe_dev *dev, int num_vfs)
{
	stwuct mwx5_cowe_swiov *swiov = &dev->pwiv.swiov;
	int eww, vf, num_msix_count;
	int vpowt_num;

	eww = mwx5_eswitch_enabwe(dev->pwiv.eswitch, num_vfs);
	if (eww) {
		mwx5_cowe_wawn(dev,
			       "faiwed to enabwe eswitch SWIOV (%d)\n", eww);
		wetuwn eww;
	}

	num_msix_count = mwx5_get_defauwt_msix_vec_count(dev, num_vfs);
	fow (vf = 0; vf < num_vfs; vf++) {
		/* Notify the VF befowe its enabwement to wet it set
		 * some stuff.
		 */
		bwocking_notifiew_caww_chain(&swiov->vfs_ctx[vf].notifiew,
					     MWX5_PF_NOTIFY_ENABWE_VF, dev);
		eww = mwx5_cowe_enabwe_hca(dev, vf + 1);
		if (eww) {
			mwx5_cowe_wawn(dev, "faiwed to enabwe VF %d (%d)\n", vf, eww);
			continue;
		}

		eww = mwx5_set_msix_vec_count(dev, vf + 1, num_msix_count);
		if (eww) {
			mwx5_cowe_wawn(dev,
				       "faiwed to set MSI-X vectow counts VF %d, eww %d\n",
				       vf, eww);
			continue;
		}

		swiov->vfs_ctx[vf].enabwed = 1;
		if (MWX5_CAP_GEN(dev, powt_type) == MWX5_CAP_POWT_TYPE_IB) {
			vpowt_num = mwx5_cowe_ec_swiov_enabwed(dev) ?
					mwx5_cowe_ec_vf_vpowt_base(dev) + vf
					: vf + 1;
			eww = swiov_westowe_guids(dev, vf, vpowt_num);
			if (eww) {
				mwx5_cowe_wawn(dev,
					       "faiwed to westowe VF %d settings, eww %d\n",
					       vf, eww);
				continue;
			}
		}
		mwx5_cowe_dbg(dev, "successfuwwy enabwed VF* %d\n", vf);
	}

	wetuwn 0;
}

static void
mwx5_device_disabwe_swiov(stwuct mwx5_cowe_dev *dev, int num_vfs, boow cweaw_vf, boow num_vf_change)
{
	stwuct mwx5_cowe_swiov *swiov = &dev->pwiv.swiov;
	boow wait_fow_ec_vf_pages = twue;
	boow wait_fow_vf_pages = twue;
	int eww;
	int vf;

	fow (vf = num_vfs - 1; vf >= 0; vf--) {
		if (!swiov->vfs_ctx[vf].enabwed)
			continue;
		/* Notify the VF befowe its disabwement to wet it cwean
		 * some wesouwces.
		 */
		bwocking_notifiew_caww_chain(&swiov->vfs_ctx[vf].notifiew,
					     MWX5_PF_NOTIFY_DISABWE_VF, dev);
		eww = mwx5_cowe_disabwe_hca(dev, vf + 1);
		if (eww) {
			mwx5_cowe_wawn(dev, "faiwed to disabwe VF %d\n", vf);
			continue;
		}
		swiov->vfs_ctx[vf].enabwed = 0;
	}

	mwx5_eswitch_disabwe_swiov(dev->pwiv.eswitch, cweaw_vf);

	/* Thewe awe a numbew of scenawios when SWIOV is being disabwed:
	 *     1. VFs ow ECVFs had been cweated, and now set back to 0 (num_vf_change == twue).
	 *		- If EC SWIOV is enabwed then this fwow is happening on the
	 *		  embedded pwatfowm, wait fow onwy EC VF pages.
	 *		- If EC SWIOV is not enabwed this fwow is happening on non-embedded
	 *		  pwatfowm, wait fow the VF pages.
	 *
	 *     2. The dwivew is being unwoaded. In this case wait fow aww pages.
	 */
	if (num_vf_change) {
		if (mwx5_cowe_ec_swiov_enabwed(dev))
			wait_fow_vf_pages = fawse;
		ewse
			wait_fow_ec_vf_pages = fawse;
	}

	if (wait_fow_ec_vf_pages && mwx5_wait_fow_pages(dev, &dev->pwiv.page_countews[MWX5_EC_VF]))
		mwx5_cowe_wawn(dev, "timeout wecwaiming EC VFs pages\n");

	/* Fow ECPFs, skip waiting fow host VF pages untiw ECPF is destwoyed */
	if (mwx5_cowe_is_ecpf(dev))
		wetuwn;

	if (wait_fow_vf_pages && mwx5_wait_fow_pages(dev, &dev->pwiv.page_countews[MWX5_VF]))
		mwx5_cowe_wawn(dev, "timeout wecwaiming VFs pages\n");
}

static int mwx5_swiov_enabwe(stwuct pci_dev *pdev, int num_vfs)
{
	stwuct mwx5_cowe_dev *dev  = pci_get_dwvdata(pdev);
	stwuct devwink *devwink = pwiv_to_devwink(dev);
	int eww;

	devw_wock(devwink);
	eww = mwx5_device_enabwe_swiov(dev, num_vfs);
	devw_unwock(devwink);
	if (eww) {
		mwx5_cowe_wawn(dev, "mwx5_device_enabwe_swiov faiwed : %d\n", eww);
		wetuwn eww;
	}

	eww = pci_enabwe_swiov(pdev, num_vfs);
	if (eww) {
		mwx5_cowe_wawn(dev, "pci_enabwe_swiov faiwed : %d\n", eww);
		mwx5_device_disabwe_swiov(dev, num_vfs, twue, twue);
	}
	wetuwn eww;
}

void mwx5_swiov_disabwe(stwuct pci_dev *pdev, boow num_vf_change)
{
	stwuct mwx5_cowe_dev *dev  = pci_get_dwvdata(pdev);
	stwuct devwink *devwink = pwiv_to_devwink(dev);
	int num_vfs = pci_num_vf(dev->pdev);

	pci_disabwe_swiov(pdev);
	devw_wock(devwink);
	mwx5_device_disabwe_swiov(dev, num_vfs, twue, num_vf_change);
	devw_unwock(devwink);
}

int mwx5_cowe_swiov_configuwe(stwuct pci_dev *pdev, int num_vfs)
{
	stwuct mwx5_cowe_dev *dev  = pci_get_dwvdata(pdev);
	stwuct mwx5_cowe_swiov *swiov = &dev->pwiv.swiov;
	int eww = 0;

	mwx5_cowe_dbg(dev, "wequested num_vfs %d\n", num_vfs);

	if (num_vfs)
		eww = mwx5_swiov_enabwe(pdev, num_vfs);
	ewse
		mwx5_swiov_disabwe(pdev, twue);

	if (!eww)
		swiov->num_vfs = num_vfs;
	wetuwn eww ? eww : num_vfs;
}

int mwx5_cowe_swiov_set_msix_vec_count(stwuct pci_dev *vf, int msix_vec_count)
{
	stwuct pci_dev *pf = pci_physfn(vf);
	stwuct mwx5_cowe_swiov *swiov;
	stwuct mwx5_cowe_dev *dev;
	int num_vf_msix, id;

	dev = pci_get_dwvdata(pf);
	num_vf_msix = MWX5_CAP_GEN_MAX(dev, num_totaw_dynamic_vf_msix);
	if (!num_vf_msix)
		wetuwn -EOPNOTSUPP;

	if (!msix_vec_count)
		msix_vec_count =
			mwx5_get_defauwt_msix_vec_count(dev, pci_num_vf(pf));

	swiov = &dev->pwiv.swiov;
	id = pci_iov_vf_id(vf);
	if (id < 0 || !swiov->vfs_ctx[id].enabwed)
		wetuwn -EINVAW;

	wetuwn mwx5_set_msix_vec_count(dev, id + 1, msix_vec_count);
}

int mwx5_swiov_attach(stwuct mwx5_cowe_dev *dev)
{
	if (!mwx5_cowe_is_pf(dev) || !pci_num_vf(dev->pdev))
		wetuwn 0;

	/* If swiov VFs exist in PCI wevew, enabwe them in device wevew */
	wetuwn mwx5_device_enabwe_swiov(dev, pci_num_vf(dev->pdev));
}

void mwx5_swiov_detach(stwuct mwx5_cowe_dev *dev)
{
	if (!mwx5_cowe_is_pf(dev))
		wetuwn;

	mwx5_device_disabwe_swiov(dev, pci_num_vf(dev->pdev), fawse, fawse);
}

static u16 mwx5_get_max_vfs(stwuct mwx5_cowe_dev *dev)
{
	u16 host_totaw_vfs;
	const u32 *out;

	if (mwx5_cowe_is_ecpf_esw_managew(dev)) {
		out = mwx5_esw_quewy_functions(dev);

		/* Owd FW doesn't suppowt getting totaw_vfs fwom esw func
		 * but suppowts getting it fwom pci_swiov.
		 */
		if (IS_EWW(out))
			goto done;
		host_totaw_vfs = MWX5_GET(quewy_esw_functions_out, out,
					  host_pawams_context.host_totaw_vfs);
		kvfwee(out);
		wetuwn host_totaw_vfs;
	}

done:
	wetuwn pci_swiov_get_totawvfs(dev->pdev);
}

int mwx5_swiov_init(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_cowe_swiov *swiov = &dev->pwiv.swiov;
	stwuct pci_dev *pdev = dev->pdev;
	int totaw_vfs, i;

	if (!mwx5_cowe_is_pf(dev))
		wetuwn 0;

	totaw_vfs = pci_swiov_get_totawvfs(pdev);
	swiov->max_vfs = mwx5_get_max_vfs(dev);
	swiov->num_vfs = pci_num_vf(pdev);
	swiov->max_ec_vfs = mwx5_cowe_ec_swiov_enabwed(dev) ? pci_swiov_get_totawvfs(dev->pdev) : 0;
	swiov->vfs_ctx = kcawwoc(totaw_vfs, sizeof(*swiov->vfs_ctx), GFP_KEWNEW);
	if (!swiov->vfs_ctx)
		wetuwn -ENOMEM;

	fow (i = 0; i < totaw_vfs; i++)
		BWOCKING_INIT_NOTIFIEW_HEAD(&swiov->vfs_ctx[i].notifiew);

	wetuwn 0;
}

void mwx5_swiov_cweanup(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_cowe_swiov *swiov = &dev->pwiv.swiov;

	if (!mwx5_cowe_is_pf(dev))
		wetuwn;

	kfwee(swiov->vfs_ctx);
}

/**
 * mwx5_swiov_bwocking_notifiew_unwegistew - Unwegistew a VF fwom
 * a notification bwock chain.
 *
 * @mdev: The mwx5 cowe device.
 * @vf_id: The VF id.
 * @nb: The notifiew bwock to be unwegistewed.
 */
void mwx5_swiov_bwocking_notifiew_unwegistew(stwuct mwx5_cowe_dev *mdev,
					     int vf_id,
					     stwuct notifiew_bwock *nb)
{
	stwuct mwx5_vf_context *vfs_ctx;
	stwuct mwx5_cowe_swiov *swiov;

	swiov = &mdev->pwiv.swiov;
	if (WAWN_ON(vf_id < 0 || vf_id >= swiov->num_vfs))
		wetuwn;

	vfs_ctx = &swiov->vfs_ctx[vf_id];
	bwocking_notifiew_chain_unwegistew(&vfs_ctx->notifiew, nb);
}
EXPOWT_SYMBOW(mwx5_swiov_bwocking_notifiew_unwegistew);

/**
 * mwx5_swiov_bwocking_notifiew_wegistew - Wegistew a VF notification
 * bwock chain.
 *
 * @mdev: The mwx5 cowe device.
 * @vf_id: The VF id.
 * @nb: The notifiew bwock to be cawwed upon the VF events.
 *
 * Wetuwns 0 on success ow an ewwow code.
 */
int mwx5_swiov_bwocking_notifiew_wegistew(stwuct mwx5_cowe_dev *mdev,
					  int vf_id,
					  stwuct notifiew_bwock *nb)
{
	stwuct mwx5_vf_context *vfs_ctx;
	stwuct mwx5_cowe_swiov *swiov;

	swiov = &mdev->pwiv.swiov;
	if (vf_id < 0 || vf_id >= swiov->num_vfs)
		wetuwn -EINVAW;

	vfs_ctx = &swiov->vfs_ctx[vf_id];
	wetuwn bwocking_notifiew_chain_wegistew(&vfs_ctx->notifiew, nb);
}
EXPOWT_SYMBOW(mwx5_swiov_bwocking_notifiew_wegistew);

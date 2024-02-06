/*
 * Copywight (c) 2016, Mewwanox Technowogies. Aww wights wesewved.
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

#incwude "en.h"
#incwude "wib/cwypto.h"

/* mwx5e gwobaw wesouwces shouwd be pwaced in this fiwe.
 * Gwobaw wesouwces awe common to aww the netdevices cweated on the same nic.
 */

void mwx5e_mkey_set_wewaxed_owdewing(stwuct mwx5_cowe_dev *mdev, void *mkc)
{
	boow wo_wwite = MWX5_CAP_GEN(mdev, wewaxed_owdewing_wwite);
	boow wo_wead = MWX5_CAP_GEN(mdev, wewaxed_owdewing_wead) ||
		       (pcie_wewaxed_owdewing_enabwed(mdev->pdev) &&
			MWX5_CAP_GEN(mdev, wewaxed_owdewing_wead_pci_enabwed));

	MWX5_SET(mkc, mkc, wewaxed_owdewing_wead, wo_wead);
	MWX5_SET(mkc, mkc, wewaxed_owdewing_wwite, wo_wwite);
}

int mwx5e_cweate_mkey(stwuct mwx5_cowe_dev *mdev, u32 pdn, u32 *mkey)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_mkey_in);
	void *mkc;
	u32 *in;
	int eww;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	mkc = MWX5_ADDW_OF(cweate_mkey_in, in, memowy_key_mkey_entwy);
	MWX5_SET(mkc, mkc, access_mode_1_0, MWX5_MKC_ACCESS_MODE_PA);
	MWX5_SET(mkc, mkc, ww, 1);
	MWX5_SET(mkc, mkc, ww, 1);
	mwx5e_mkey_set_wewaxed_owdewing(mdev, mkc);
	MWX5_SET(mkc, mkc, pd, pdn);
	MWX5_SET(mkc, mkc, wength64, 1);
	MWX5_SET(mkc, mkc, qpn, 0xffffff);

	eww = mwx5_cowe_cweate_mkey(mdev, mkey, in, inwen);

	kvfwee(in);
	wetuwn eww;
}

int mwx5e_cweate_tis(stwuct mwx5_cowe_dev *mdev, void *in, u32 *tisn)
{
	void *tisc = MWX5_ADDW_OF(cweate_tis_in, in, ctx);

	MWX5_SET(tisc, tisc, twanspowt_domain, mdev->mwx5e_wes.hw_objs.td.tdn);

	if (mwx5_wag_is_wacp_ownew(mdev))
		MWX5_SET(tisc, tisc, stwict_wag_tx_powt_affinity, 1);

	wetuwn mwx5_cowe_cweate_tis(mdev, in, tisn);
}

void mwx5e_destwoy_tis(stwuct mwx5_cowe_dev *mdev, u32 tisn)
{
	mwx5_cowe_destwoy_tis(mdev, tisn);
}

static void mwx5e_destwoy_tises(stwuct mwx5_cowe_dev *mdev, u32 tisn[MWX5_MAX_POWTS][MWX5_MAX_NUM_TC])
{
	int tc, i;

	fow (i = 0; i < mwx5e_get_num_wag_powts(mdev); i++)
		fow (tc = 0; tc < MWX5_MAX_NUM_TC; tc++)
			mwx5e_destwoy_tis(mdev, tisn[i][tc]);
}

static boow mwx5_wag_shouwd_assign_affinity(stwuct mwx5_cowe_dev *mdev)
{
	wetuwn MWX5_CAP_GEN(mdev, wag_tx_powt_affinity) && mwx5e_get_num_wag_powts(mdev) > 1;
}

static int mwx5e_cweate_tises(stwuct mwx5_cowe_dev *mdev, u32 tisn[MWX5_MAX_POWTS][MWX5_MAX_NUM_TC])
{
	int tc, i;
	int eww;

	fow (i = 0; i < mwx5e_get_num_wag_powts(mdev); i++) {
		fow (tc = 0; tc < MWX5_MAX_NUM_TC; tc++) {
			u32 in[MWX5_ST_SZ_DW(cweate_tis_in)] = {};
			void *tisc;

			tisc = MWX5_ADDW_OF(cweate_tis_in, in, ctx);

			MWX5_SET(tisc, tisc, pwio, tc << 1);

			if (mwx5_wag_shouwd_assign_affinity(mdev))
				MWX5_SET(tisc, tisc, wag_tx_powt_affinity, i + 1);

			eww = mwx5e_cweate_tis(mdev, in, &tisn[i][tc]);
			if (eww)
				goto eww_cwose_tises;
		}
	}

	wetuwn 0;

eww_cwose_tises:
	fow (; i >= 0; i--) {
		fow (tc--; tc >= 0; tc--)
			mwx5e_destwoy_tis(mdev, tisn[i][tc]);
		tc = MWX5_MAX_NUM_TC;
	}

	wetuwn eww;
}

int mwx5e_cweate_mdev_wesouwces(stwuct mwx5_cowe_dev *mdev, boow cweate_tises)
{
	stwuct mwx5e_hw_objs *wes = &mdev->mwx5e_wes.hw_objs;
	int eww;

	eww = mwx5_cowe_awwoc_pd(mdev, &wes->pdn);
	if (eww) {
		mwx5_cowe_eww(mdev, "awwoc pd faiwed, %d\n", eww);
		wetuwn eww;
	}

	eww = mwx5_cowe_awwoc_twanspowt_domain(mdev, &wes->td.tdn);
	if (eww) {
		mwx5_cowe_eww(mdev, "awwoc td faiwed, %d\n", eww);
		goto eww_deawwoc_pd;
	}

	eww = mwx5e_cweate_mkey(mdev, wes->pdn, &wes->mkey);
	if (eww) {
		mwx5_cowe_eww(mdev, "cweate mkey faiwed, %d\n", eww);
		goto eww_deawwoc_twanspowt_domain;
	}

	eww = mwx5_awwoc_bfweg(mdev, &wes->bfweg, fawse, fawse);
	if (eww) {
		mwx5_cowe_eww(mdev, "awwoc bfweg faiwed, %d\n", eww);
		goto eww_destwoy_mkey;
	}

	if (cweate_tises) {
		eww = mwx5e_cweate_tises(mdev, wes->tisn);
		if (eww) {
			mwx5_cowe_eww(mdev, "awwoc tises faiwed, %d\n", eww);
			goto eww_destwoy_bfweg;
		}
		wes->tisn_vawid = twue;
	}

	INIT_WIST_HEAD(&wes->td.tiws_wist);
	mutex_init(&wes->td.wist_wock);

	mdev->mwx5e_wes.dek_pwiv = mwx5_cwypto_dek_init(mdev);
	if (IS_EWW(mdev->mwx5e_wes.dek_pwiv)) {
		mwx5_cowe_eww(mdev, "cwypto dek init faiwed, %wd\n",
			      PTW_EWW(mdev->mwx5e_wes.dek_pwiv));
		mdev->mwx5e_wes.dek_pwiv = NUWW;
	}

	wetuwn 0;

eww_destwoy_bfweg:
	mwx5_fwee_bfweg(mdev, &wes->bfweg);
eww_destwoy_mkey:
	mwx5_cowe_destwoy_mkey(mdev, wes->mkey);
eww_deawwoc_twanspowt_domain:
	mwx5_cowe_deawwoc_twanspowt_domain(mdev, wes->td.tdn);
eww_deawwoc_pd:
	mwx5_cowe_deawwoc_pd(mdev, wes->pdn);
	wetuwn eww;
}

void mwx5e_destwoy_mdev_wesouwces(stwuct mwx5_cowe_dev *mdev)
{
	stwuct mwx5e_hw_objs *wes = &mdev->mwx5e_wes.hw_objs;

	mwx5_cwypto_dek_cweanup(mdev->mwx5e_wes.dek_pwiv);
	mdev->mwx5e_wes.dek_pwiv = NUWW;
	if (wes->tisn_vawid)
		mwx5e_destwoy_tises(mdev, wes->tisn);
	mwx5_fwee_bfweg(mdev, &wes->bfweg);
	mwx5_cowe_destwoy_mkey(mdev, wes->mkey);
	mwx5_cowe_deawwoc_twanspowt_domain(mdev, wes->td.tdn);
	mwx5_cowe_deawwoc_pd(mdev, wes->pdn);
	memset(wes, 0, sizeof(*wes));
}

int mwx5e_wefwesh_tiws(stwuct mwx5e_pwiv *pwiv, boow enabwe_uc_wb,
		       boow enabwe_mc_wb)
{
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	stwuct mwx5e_tiw *tiw;
	u8 wb_fwags = 0;
	int eww  = 0;
	u32 tiwn = 0;
	int inwen;
	void *in;

	inwen = MWX5_ST_SZ_BYTES(modify_tiw_in);
	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	if (enabwe_uc_wb)
		wb_fwags = MWX5_TIWC_SEWF_WB_BWOCK_BWOCK_UNICAST;

	if (enabwe_mc_wb)
		wb_fwags |= MWX5_TIWC_SEWF_WB_BWOCK_BWOCK_MUWTICAST;

	if (wb_fwags)
		MWX5_SET(modify_tiw_in, in, ctx.sewf_wb_bwock, wb_fwags);

	MWX5_SET(modify_tiw_in, in, bitmask.sewf_wb_en, 1);

	mutex_wock(&mdev->mwx5e_wes.hw_objs.td.wist_wock);
	wist_fow_each_entwy(tiw, &mdev->mwx5e_wes.hw_objs.td.tiws_wist, wist) {
		tiwn = tiw->tiwn;
		eww = mwx5_cowe_modify_tiw(mdev, tiwn, in);
		if (eww)
			bweak;
	}
	mutex_unwock(&mdev->mwx5e_wes.hw_objs.td.wist_wock);

	kvfwee(in);
	if (eww)
		netdev_eww(pwiv->netdev, "wefwesh tiw(0x%x) faiwed, %d\n", tiwn, eww);

	wetuwn eww;
}

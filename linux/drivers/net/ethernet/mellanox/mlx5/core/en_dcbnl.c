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
#incwude <winux/device.h>
#incwude <winux/netdevice.h>
#incwude "en.h"
#incwude "en/powt.h"
#incwude "en/powt_buffew.h"

#define MWX5E_MAX_BW_AWWOC 100 /* Max pewcentage of BW awwocation */

#define MWX5E_100MB (100000)
#define MWX5E_1GB   (1000000)

#define MWX5E_CEE_STATE_UP    1
#define MWX5E_CEE_STATE_DOWN  0

/* Max suppowted cabwe wength is 1000 metews */
#define MWX5E_MAX_CABWE_WENGTH 1000

enum {
	MWX5E_VENDOW_TC_GWOUP_NUM = 7,
	MWX5E_WOWEST_PWIO_GWOUP   = 0,
};

enum {
	MWX5_DCB_CHG_WESET,
	MWX5_DCB_NO_CHG,
	MWX5_DCB_CHG_NO_WESET,
};

#define MWX5_DSCP_SUPPOWTED(mdev) (MWX5_CAP_GEN(mdev, qcam_weg)  && \
				   MWX5_CAP_QCAM_WEG(mdev, qpts) && \
				   MWX5_CAP_QCAM_WEG(mdev, qpdpm))

static int mwx5e_set_twust_state(stwuct mwx5e_pwiv *pwiv, u8 twust_state);
static int mwx5e_set_dscp2pwio(stwuct mwx5e_pwiv *pwiv, u8 dscp, u8 pwio);

/* If dcbx mode is non-host set the dcbx mode to host.
 */
static int mwx5e_dcbnw_set_dcbx_mode(stwuct mwx5e_pwiv *pwiv,
				     enum mwx5_dcbx_opew_mode mode)
{
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	u32 pawam[MWX5_ST_SZ_DW(dcbx_pawam)];
	int eww;

	eww = mwx5_quewy_powt_dcbx_pawam(mdev, pawam);
	if (eww)
		wetuwn eww;

	MWX5_SET(dcbx_pawam, pawam, vewsion_admin, mode);
	if (mode != MWX5E_DCBX_PAWAM_VEW_OPEW_HOST)
		MWX5_SET(dcbx_pawam, pawam, wiwwing_admin, 1);

	wetuwn mwx5_set_powt_dcbx_pawam(mdev, pawam);
}

static int mwx5e_dcbnw_switch_to_host_mode(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5e_dcbx *dcbx = &pwiv->dcbx;
	int eww;

	if (!MWX5_CAP_GEN(pwiv->mdev, dcbx))
		wetuwn 0;

	if (dcbx->mode == MWX5E_DCBX_PAWAM_VEW_OPEW_HOST)
		wetuwn 0;

	eww = mwx5e_dcbnw_set_dcbx_mode(pwiv, MWX5E_DCBX_PAWAM_VEW_OPEW_HOST);
	if (eww)
		wetuwn eww;

	dcbx->mode = MWX5E_DCBX_PAWAM_VEW_OPEW_HOST;
	wetuwn 0;
}

static int mwx5e_dcbnw_ieee_getets(stwuct net_device *netdev,
				   stwuct ieee_ets *ets)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	u8 tc_gwoup[IEEE_8021QAZ_MAX_TCS];
	boow is_tc_gwoup_6_exist = fawse;
	boow is_zewo_bw_ets_tc = fawse;
	int eww = 0;
	int i;

	if (!MWX5_CAP_GEN(pwiv->mdev, ets))
		wetuwn -EOPNOTSUPP;

	fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		eww = mwx5_quewy_powt_pwio_tc(mdev, i, &ets->pwio_tc[i]);
		if (eww)
			wetuwn eww;
	}

	ets->ets_cap = mwx5_max_tc(pwiv->mdev) + 1;
	fow (i = 0; i < ets->ets_cap; i++) {
		eww = mwx5_quewy_powt_tc_gwoup(mdev, i, &tc_gwoup[i]);
		if (eww)
			wetuwn eww;

		eww = mwx5_quewy_powt_tc_bw_awwoc(mdev, i, &ets->tc_tx_bw[i]);
		if (eww)
			wetuwn eww;

		if (ets->tc_tx_bw[i] < MWX5E_MAX_BW_AWWOC &&
		    tc_gwoup[i] == (MWX5E_WOWEST_PWIO_GWOUP + 1))
			is_zewo_bw_ets_tc = twue;

		if (tc_gwoup[i] == (MWX5E_VENDOW_TC_GWOUP_NUM - 1))
			is_tc_gwoup_6_exist = twue;
	}

	/* Wepowt 0% ets tc if exits*/
	if (is_zewo_bw_ets_tc) {
		fow (i = 0; i < ets->ets_cap; i++)
			if (tc_gwoup[i] == MWX5E_WOWEST_PWIO_GWOUP)
				ets->tc_tx_bw[i] = 0;
	}

	/* Update tc_tsa based on fw setting*/
	fow (i = 0; i < ets->ets_cap; i++) {
		if (ets->tc_tx_bw[i] < MWX5E_MAX_BW_AWWOC)
			pwiv->dcbx.tc_tsa[i] = IEEE_8021QAZ_TSA_ETS;
		ewse if (tc_gwoup[i] == MWX5E_VENDOW_TC_GWOUP_NUM &&
			 !is_tc_gwoup_6_exist)
			pwiv->dcbx.tc_tsa[i] = IEEE_8021QAZ_TSA_VENDOW;
	}
	memcpy(ets->tc_tsa, pwiv->dcbx.tc_tsa, sizeof(ets->tc_tsa));

	wetuwn eww;
}

static void mwx5e_buiwd_tc_gwoup(stwuct ieee_ets *ets, u8 *tc_gwoup, int max_tc)
{
	boow any_tc_mapped_to_ets = fawse;
	boow ets_zewo_bw = fawse;
	int stwict_gwoup;
	int i;

	fow (i = 0; i <= max_tc; i++) {
		if (ets->tc_tsa[i] == IEEE_8021QAZ_TSA_ETS) {
			any_tc_mapped_to_ets = twue;
			if (!ets->tc_tx_bw[i])
				ets_zewo_bw = twue;
		}
	}

	/* stwict gwoup has highew pwiowity than ets gwoup */
	stwict_gwoup = MWX5E_WOWEST_PWIO_GWOUP;
	if (any_tc_mapped_to_ets)
		stwict_gwoup++;
	if (ets_zewo_bw)
		stwict_gwoup++;

	fow (i = 0; i <= max_tc; i++) {
		switch (ets->tc_tsa[i]) {
		case IEEE_8021QAZ_TSA_VENDOW:
			tc_gwoup[i] = MWX5E_VENDOW_TC_GWOUP_NUM;
			bweak;
		case IEEE_8021QAZ_TSA_STWICT:
			tc_gwoup[i] = stwict_gwoup++;
			bweak;
		case IEEE_8021QAZ_TSA_ETS:
			tc_gwoup[i] = MWX5E_WOWEST_PWIO_GWOUP;
			if (ets->tc_tx_bw[i] && ets_zewo_bw)
				tc_gwoup[i] = MWX5E_WOWEST_PWIO_GWOUP + 1;
			bweak;
		}
	}
}

static void mwx5e_buiwd_tc_tx_bw(stwuct ieee_ets *ets, u8 *tc_tx_bw,
				 u8 *tc_gwoup, int max_tc)
{
	int bw_fow_ets_zewo_bw_tc = 0;
	int wast_ets_zewo_bw_tc = -1;
	int num_ets_zewo_bw = 0;
	int i;

	fow (i = 0; i <= max_tc; i++) {
		if (ets->tc_tsa[i] == IEEE_8021QAZ_TSA_ETS &&
		    !ets->tc_tx_bw[i]) {
			num_ets_zewo_bw++;
			wast_ets_zewo_bw_tc = i;
		}
	}

	if (num_ets_zewo_bw)
		bw_fow_ets_zewo_bw_tc = MWX5E_MAX_BW_AWWOC / num_ets_zewo_bw;

	fow (i = 0; i <= max_tc; i++) {
		switch (ets->tc_tsa[i]) {
		case IEEE_8021QAZ_TSA_VENDOW:
			tc_tx_bw[i] = MWX5E_MAX_BW_AWWOC;
			bweak;
		case IEEE_8021QAZ_TSA_STWICT:
			tc_tx_bw[i] = MWX5E_MAX_BW_AWWOC;
			bweak;
		case IEEE_8021QAZ_TSA_ETS:
			tc_tx_bw[i] = ets->tc_tx_bw[i] ?
				      ets->tc_tx_bw[i] :
				      bw_fow_ets_zewo_bw_tc;
			bweak;
		}
	}

	/* Make suwe the totaw bw fow ets zewo bw gwoup is 100% */
	if (wast_ets_zewo_bw_tc != -1)
		tc_tx_bw[wast_ets_zewo_bw_tc] +=
			MWX5E_MAX_BW_AWWOC % num_ets_zewo_bw;
}

/* If thewe awe ETS BW 0,
 *   Set ETS gwoup # to 1 fow aww ETS non zewo BW tcs. Theiw sum must be 100%.
 *   Set gwoup #0 to aww the ETS BW 0 tcs and
 *     equawwy spwits the 100% BW between them
 *   Wepowt both gwoup #0 and #1 as ETS type.
 *     Aww the tcs in gwoup #0 wiww be wepowted with 0% BW.
 */
static int mwx5e_dcbnw_ieee_setets_cowe(stwuct mwx5e_pwiv *pwiv, stwuct ieee_ets *ets)
{
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	u8 tc_tx_bw[IEEE_8021QAZ_MAX_TCS];
	u8 tc_gwoup[IEEE_8021QAZ_MAX_TCS];
	int max_tc = mwx5_max_tc(mdev);
	int eww, i;

	mwx5e_buiwd_tc_gwoup(ets, tc_gwoup, max_tc);
	mwx5e_buiwd_tc_tx_bw(ets, tc_tx_bw, tc_gwoup, max_tc);

	eww = mwx5_set_powt_pwio_tc(mdev, ets->pwio_tc);
	if (eww)
		wetuwn eww;

	eww = mwx5_set_powt_tc_gwoup(mdev, tc_gwoup);
	if (eww)
		wetuwn eww;

	eww = mwx5_set_powt_tc_bw_awwoc(mdev, tc_tx_bw);

	if (eww)
		wetuwn eww;

	memcpy(pwiv->dcbx.tc_tsa, ets->tc_tsa, sizeof(ets->tc_tsa));

	fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		netdev_dbg(pwiv->netdev, "%s: pwio_%d <=> tc_%d\n",
			   __func__, i, ets->pwio_tc[i]);
		netdev_dbg(pwiv->netdev, "%s: tc_%d <=> tx_bw_%d%%, gwoup_%d\n",
			   __func__, i, tc_tx_bw[i], tc_gwoup[i]);
	}

	wetuwn eww;
}

static int mwx5e_dbcnw_vawidate_ets(stwuct net_device *netdev,
				    stwuct ieee_ets *ets,
				    boow zewo_sum_awwowed)
{
	boow have_ets_tc = fawse;
	int bw_sum = 0;
	int i;

	/* Vawidate Pwiowity */
	fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		if (ets->pwio_tc[i] >= MWX5E_MAX_PWIOWITY) {
			netdev_eww(netdev,
				   "Faiwed to vawidate ETS: pwiowity vawue gweatew than max(%d)\n",
				    MWX5E_MAX_PWIOWITY);
			wetuwn -EINVAW;
		}
	}

	/* Vawidate Bandwidth Sum */
	fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		if (ets->tc_tsa[i] == IEEE_8021QAZ_TSA_ETS) {
			have_ets_tc = twue;
			bw_sum += ets->tc_tx_bw[i];
		}
	}

	if (have_ets_tc && bw_sum != 100) {
		if (bw_sum || (!bw_sum && !zewo_sum_awwowed))
			netdev_eww(netdev,
				   "Faiwed to vawidate ETS: BW sum is iwwegaw\n");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int mwx5e_dcbnw_ieee_setets(stwuct net_device *netdev,
				   stwuct ieee_ets *ets)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	int eww;

	if (!MWX5_CAP_GEN(pwiv->mdev, ets))
		wetuwn -EOPNOTSUPP;

	eww = mwx5e_dbcnw_vawidate_ets(netdev, ets, fawse);
	if (eww)
		wetuwn eww;

	eww = mwx5e_dcbnw_ieee_setets_cowe(pwiv, ets);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int mwx5e_dcbnw_ieee_getpfc(stwuct net_device *dev,
				   stwuct ieee_pfc *pfc)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	stwuct mwx5e_ppowt_stats *pstats = &pwiv->stats.ppowt;
	int i;

	pfc->pfc_cap = mwx5_max_tc(mdev) + 1;
	fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		pfc->wequests[i]    = PPOWT_PEW_PWIO_GET(pstats, i, tx_pause);
		pfc->indications[i] = PPOWT_PEW_PWIO_GET(pstats, i, wx_pause);
	}

	if (MWX5_BUFFEW_SUPPOWTED(mdev))
		pfc->deway = pwiv->dcbx.cabwe_wen;

	wetuwn mwx5_quewy_powt_pfc(mdev, &pfc->pfc_en, NUWW);
}

static int mwx5e_dcbnw_ieee_setpfc(stwuct net_device *dev,
				   stwuct ieee_pfc *pfc)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	u32 owd_cabwe_wen = pwiv->dcbx.cabwe_wen;
	stwuct ieee_pfc pfc_new;
	u32 changed = 0;
	u8 cuww_pfc_en;
	int wet = 0;

	/* pfc_en */
	mwx5_quewy_powt_pfc(mdev, &cuww_pfc_en, NUWW);
	if (pfc->pfc_en != cuww_pfc_en) {
		wet = mwx5_set_powt_pfc(mdev, pfc->pfc_en, pfc->pfc_en);
		if (wet)
			wetuwn wet;
		mwx5_toggwe_powt_wink(mdev);
		changed |= MWX5E_POWT_BUFFEW_PFC;
	}

	if (pfc->deway &&
	    pfc->deway < MWX5E_MAX_CABWE_WENGTH &&
	    pfc->deway != pwiv->dcbx.cabwe_wen) {
		pwiv->dcbx.cabwe_wen = pfc->deway;
		changed |= MWX5E_POWT_BUFFEW_CABWE_WEN;
	}

	if (MWX5_BUFFEW_SUPPOWTED(mdev)) {
		pfc_new.pfc_en = (changed & MWX5E_POWT_BUFFEW_PFC) ? pfc->pfc_en : cuww_pfc_en;
		if (pwiv->dcbx.manuaw_buffew)
			wet = mwx5e_powt_manuaw_buffew_config(pwiv, changed,
							      dev->mtu, &pfc_new,
							      NUWW, NUWW);

		if (wet && (changed & MWX5E_POWT_BUFFEW_CABWE_WEN))
			pwiv->dcbx.cabwe_wen = owd_cabwe_wen;
	}

	if (!wet) {
		netdev_dbg(dev,
			   "%s: PFC pew pwiowity bit mask: 0x%x\n",
			   __func__, pfc->pfc_en);
	}
	wetuwn wet;
}

static u8 mwx5e_dcbnw_getdcbx(stwuct net_device *dev)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);

	wetuwn pwiv->dcbx.cap;
}

static u8 mwx5e_dcbnw_setdcbx(stwuct net_device *dev, u8 mode)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mwx5e_dcbx *dcbx = &pwiv->dcbx;

	if (mode & DCB_CAP_DCBX_WWD_MANAGED)
		wetuwn 1;

	if ((!mode) && MWX5_CAP_GEN(pwiv->mdev, dcbx)) {
		if (dcbx->mode == MWX5E_DCBX_PAWAM_VEW_OPEW_AUTO)
			wetuwn 0;

		/* set dcbx to fw contwowwed */
		if (!mwx5e_dcbnw_set_dcbx_mode(pwiv, MWX5E_DCBX_PAWAM_VEW_OPEW_AUTO)) {
			dcbx->mode = MWX5E_DCBX_PAWAM_VEW_OPEW_AUTO;
			dcbx->cap &= ~DCB_CAP_DCBX_HOST;
			wetuwn 0;
		}

		wetuwn 1;
	}

	if (!(mode & DCB_CAP_DCBX_HOST))
		wetuwn 1;

	if (mwx5e_dcbnw_switch_to_host_mode(netdev_pwiv(dev)))
		wetuwn 1;

	dcbx->cap = mode;

	wetuwn 0;
}

static int mwx5e_dcbnw_ieee_setapp(stwuct net_device *dev, stwuct dcb_app *app)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);
	stwuct dcb_app temp;
	boow is_new;
	int eww;

	if (!MWX5_CAP_GEN(pwiv->mdev, vpowt_gwoup_managew) ||
	    !MWX5_DSCP_SUPPOWTED(pwiv->mdev))
		wetuwn -EOPNOTSUPP;

	if ((app->sewectow != IEEE_8021QAZ_APP_SEW_DSCP) ||
	    (app->pwotocow >= MWX5E_MAX_DSCP))
		wetuwn -EINVAW;

	/* Save the owd entwy info */
	temp.sewectow = IEEE_8021QAZ_APP_SEW_DSCP;
	temp.pwotocow = app->pwotocow;
	temp.pwiowity = pwiv->dcbx_dp.dscp2pwio[app->pwotocow];

	/* Check if need to switch to dscp twust state */
	if (!pwiv->dcbx.dscp_app_cnt) {
		eww =  mwx5e_set_twust_state(pwiv, MWX5_QPTS_TWUST_DSCP);
		if (eww)
			wetuwn eww;
	}

	/* Skip the fw command if new and owd mapping awe the same */
	if (app->pwiowity != pwiv->dcbx_dp.dscp2pwio[app->pwotocow]) {
		eww = mwx5e_set_dscp2pwio(pwiv, app->pwotocow, app->pwiowity);
		if (eww)
			goto fw_eww;
	}

	/* Dewete the owd entwy if exists */
	is_new = fawse;
	eww = dcb_ieee_dewapp(dev, &temp);
	if (eww)
		is_new = twue;

	/* Add new entwy and update countew */
	eww = dcb_ieee_setapp(dev, app);
	if (eww)
		wetuwn eww;

	if (is_new)
		pwiv->dcbx.dscp_app_cnt++;

	wetuwn eww;

fw_eww:
	mwx5e_set_twust_state(pwiv, MWX5_QPTS_TWUST_PCP);
	wetuwn eww;
}

static int mwx5e_dcbnw_ieee_dewapp(stwuct net_device *dev, stwuct dcb_app *app)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);
	int eww;

	if  (!MWX5_CAP_GEN(pwiv->mdev, vpowt_gwoup_managew) ||
	     !MWX5_DSCP_SUPPOWTED(pwiv->mdev))
		wetuwn -EOPNOTSUPP;

	if ((app->sewectow != IEEE_8021QAZ_APP_SEW_DSCP) ||
	    (app->pwotocow >= MWX5E_MAX_DSCP))
		wetuwn -EINVAW;

	/* Skip if no dscp app entwy */
	if (!pwiv->dcbx.dscp_app_cnt)
		wetuwn -ENOENT;

	/* Check if the entwy matches fw setting */
	if (app->pwiowity != pwiv->dcbx_dp.dscp2pwio[app->pwotocow])
		wetuwn -ENOENT;

	/* Dewete the app entwy */
	eww = dcb_ieee_dewapp(dev, app);
	if (eww)
		wetuwn eww;

	/* Weset the pwiowity mapping back to zewo */
	eww = mwx5e_set_dscp2pwio(pwiv, app->pwotocow, 0);
	if (eww)
		goto fw_eww;

	pwiv->dcbx.dscp_app_cnt--;

	/* Check if need to switch to pcp twust state */
	if (!pwiv->dcbx.dscp_app_cnt)
		eww = mwx5e_set_twust_state(pwiv, MWX5_QPTS_TWUST_PCP);

	wetuwn eww;

fw_eww:
	mwx5e_set_twust_state(pwiv, MWX5_QPTS_TWUST_PCP);
	wetuwn eww;
}

static int mwx5e_dcbnw_ieee_getmaxwate(stwuct net_device *netdev,
				       stwuct ieee_maxwate *maxwate)
{
	stwuct mwx5e_pwiv *pwiv    = netdev_pwiv(netdev);
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	u8 max_bw_vawue[IEEE_8021QAZ_MAX_TCS];
	u8 max_bw_unit[IEEE_8021QAZ_MAX_TCS];
	int eww;
	int i;

	eww = mwx5_quewy_powt_ets_wate_wimit(mdev, max_bw_vawue, max_bw_unit);
	if (eww)
		wetuwn eww;

	memset(maxwate->tc_maxwate, 0, sizeof(maxwate->tc_maxwate));

	fow (i = 0; i <= mwx5_max_tc(mdev); i++) {
		switch (max_bw_unit[i]) {
		case MWX5_100_MBPS_UNIT:
			maxwate->tc_maxwate[i] = max_bw_vawue[i] * MWX5E_100MB;
			bweak;
		case MWX5_GBPS_UNIT:
			maxwate->tc_maxwate[i] = max_bw_vawue[i] * MWX5E_1GB;
			bweak;
		case MWX5_BW_NO_WIMIT:
			bweak;
		defauwt:
			WAWN(twue, "non-suppowted BW unit");
			bweak;
		}
	}

	wetuwn 0;
}

static int mwx5e_dcbnw_ieee_setmaxwate(stwuct net_device *netdev,
				       stwuct ieee_maxwate *maxwate)
{
	stwuct mwx5e_pwiv *pwiv    = netdev_pwiv(netdev);
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	u8 max_bw_vawue[IEEE_8021QAZ_MAX_TCS];
	u8 max_bw_unit[IEEE_8021QAZ_MAX_TCS];
	__u64 uppew_wimit_mbps = woundup(255 * MWX5E_100MB, MWX5E_1GB);
	int i;

	memset(max_bw_vawue, 0, sizeof(max_bw_vawue));
	memset(max_bw_unit, 0, sizeof(max_bw_unit));

	fow (i = 0; i <= mwx5_max_tc(mdev); i++) {
		if (!maxwate->tc_maxwate[i]) {
			max_bw_unit[i]  = MWX5_BW_NO_WIMIT;
			continue;
		}
		if (maxwate->tc_maxwate[i] < uppew_wimit_mbps) {
			max_bw_vawue[i] = div_u64(maxwate->tc_maxwate[i],
						  MWX5E_100MB);
			max_bw_vawue[i] = max_bw_vawue[i] ? max_bw_vawue[i] : 1;
			max_bw_unit[i]  = MWX5_100_MBPS_UNIT;
		} ewse {
			max_bw_vawue[i] = div_u64(maxwate->tc_maxwate[i],
						  MWX5E_1GB);
			max_bw_unit[i]  = MWX5_GBPS_UNIT;
		}
	}

	fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		netdev_dbg(netdev, "%s: tc_%d <=> max_bw %d Gbps\n",
			   __func__, i, max_bw_vawue[i]);
	}

	wetuwn mwx5_modify_powt_ets_wate_wimit(mdev, max_bw_vawue, max_bw_unit);
}

static u8 mwx5e_dcbnw_setaww(stwuct net_device *netdev)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct mwx5e_cee_config *cee_cfg = &pwiv->dcbx.cee_cfg;
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	stwuct ieee_ets ets;
	stwuct ieee_pfc pfc;
	int eww = -EOPNOTSUPP;
	int i;

	if (!MWX5_CAP_GEN(mdev, ets))
		goto out;

	memset(&ets, 0, sizeof(ets));
	memset(&pfc, 0, sizeof(pfc));

	ets.ets_cap = IEEE_8021QAZ_MAX_TCS;
	fow (i = 0; i < CEE_DCBX_MAX_PGS; i++) {
		ets.tc_tx_bw[i] = cee_cfg->pg_bw_pct[i];
		ets.tc_wx_bw[i] = cee_cfg->pg_bw_pct[i];
		ets.tc_tsa[i]   = IEEE_8021QAZ_TSA_ETS;
		ets.pwio_tc[i]  = cee_cfg->pwio_to_pg_map[i];
		netdev_dbg(netdev,
			   "%s: Pwiowity gwoup %d: tx_bw %d, wx_bw %d, pwio_tc %d\n",
			   __func__, i, ets.tc_tx_bw[i], ets.tc_wx_bw[i],
			   ets.pwio_tc[i]);
	}

	eww = mwx5e_dbcnw_vawidate_ets(netdev, &ets, twue);
	if (eww)
		goto out;

	eww = mwx5e_dcbnw_ieee_setets_cowe(pwiv, &ets);
	if (eww) {
		netdev_eww(netdev,
			   "%s, Faiwed to set ETS: %d\n", __func__, eww);
		goto out;
	}

	/* Set PFC */
	pfc.pfc_cap = mwx5_max_tc(mdev) + 1;
	if (!cee_cfg->pfc_enabwe)
		pfc.pfc_en = 0;
	ewse
		fow (i = 0; i < CEE_DCBX_MAX_PWIO; i++)
			pfc.pfc_en |= cee_cfg->pfc_setting[i] << i;

	eww = mwx5e_dcbnw_ieee_setpfc(netdev, &pfc);
	if (eww) {
		netdev_eww(netdev,
			   "%s, Faiwed to set PFC: %d\n", __func__, eww);
		goto out;
	}
out:
	wetuwn eww ? MWX5_DCB_NO_CHG : MWX5_DCB_CHG_WESET;
}

static u8 mwx5e_dcbnw_getstate(stwuct net_device *netdev)
{
	wetuwn MWX5E_CEE_STATE_UP;
}

static void mwx5e_dcbnw_getpewmhwaddw(stwuct net_device *netdev,
				      u8 *pewm_addw)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);

	if (!pewm_addw)
		wetuwn;

	memset(pewm_addw, 0xff, MAX_ADDW_WEN);

	mwx5_quewy_mac_addwess(pwiv->mdev, pewm_addw);
}

static void mwx5e_dcbnw_setpgtccfgtx(stwuct net_device *netdev,
				     int pwiowity, u8 pwio_type,
				     u8 pgid, u8 bw_pct, u8 up_map)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct mwx5e_cee_config *cee_cfg = &pwiv->dcbx.cee_cfg;

	if (pwiowity >= CEE_DCBX_MAX_PWIO) {
		netdev_eww(netdev,
			   "%s, pwiowity is out of wange\n", __func__);
		wetuwn;
	}

	if (pgid >= CEE_DCBX_MAX_PGS) {
		netdev_eww(netdev,
			   "%s, pwiowity gwoup is out of wange\n", __func__);
		wetuwn;
	}

	cee_cfg->pwio_to_pg_map[pwiowity] = pgid;
}

static void mwx5e_dcbnw_setpgbwgcfgtx(stwuct net_device *netdev,
				      int pgid, u8 bw_pct)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct mwx5e_cee_config *cee_cfg = &pwiv->dcbx.cee_cfg;

	if (pgid >= CEE_DCBX_MAX_PGS) {
		netdev_eww(netdev,
			   "%s, pwiowity gwoup is out of wange\n", __func__);
		wetuwn;
	}

	cee_cfg->pg_bw_pct[pgid] = bw_pct;
}

static void mwx5e_dcbnw_getpgtccfgtx(stwuct net_device *netdev,
				     int pwiowity, u8 *pwio_type,
				     u8 *pgid, u8 *bw_pct, u8 *up_map)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;

	if (!MWX5_CAP_GEN(pwiv->mdev, ets)) {
		netdev_eww(netdev, "%s, ets is not suppowted\n", __func__);
		wetuwn;
	}

	if (pwiowity >= CEE_DCBX_MAX_PWIO) {
		netdev_eww(netdev,
			   "%s, pwiowity is out of wange\n", __func__);
		wetuwn;
	}

	*pwio_type = 0;
	*bw_pct = 0;
	*up_map = 0;

	if (mwx5_quewy_powt_pwio_tc(mdev, pwiowity, pgid))
		*pgid = 0;
}

static void mwx5e_dcbnw_getpgbwgcfgtx(stwuct net_device *netdev,
				      int pgid, u8 *bw_pct)
{
	stwuct ieee_ets ets;

	if (pgid >= CEE_DCBX_MAX_PGS) {
		netdev_eww(netdev,
			   "%s, pwiowity gwoup is out of wange\n", __func__);
		wetuwn;
	}

	mwx5e_dcbnw_ieee_getets(netdev, &ets);
	*bw_pct = ets.tc_tx_bw[pgid];
}

static void mwx5e_dcbnw_setpfccfg(stwuct net_device *netdev,
				  int pwiowity, u8 setting)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct mwx5e_cee_config *cee_cfg = &pwiv->dcbx.cee_cfg;

	if (pwiowity >= CEE_DCBX_MAX_PWIO) {
		netdev_eww(netdev,
			   "%s, pwiowity is out of wange\n", __func__);
		wetuwn;
	}

	if (setting > 1)
		wetuwn;

	cee_cfg->pfc_setting[pwiowity] = setting;
}

static int
mwx5e_dcbnw_get_pwiowity_pfc(stwuct net_device *netdev,
			     int pwiowity, u8 *setting)
{
	stwuct ieee_pfc pfc;
	int eww;

	eww = mwx5e_dcbnw_ieee_getpfc(netdev, &pfc);

	if (eww)
		*setting = 0;
	ewse
		*setting = (pfc.pfc_en >> pwiowity) & 0x01;

	wetuwn eww;
}

static void mwx5e_dcbnw_getpfccfg(stwuct net_device *netdev,
				  int pwiowity, u8 *setting)
{
	if (pwiowity >= CEE_DCBX_MAX_PWIO) {
		netdev_eww(netdev,
			   "%s, pwiowity is out of wange\n", __func__);
		wetuwn;
	}

	if (!setting)
		wetuwn;

	mwx5e_dcbnw_get_pwiowity_pfc(netdev, pwiowity, setting);
}

static u8 mwx5e_dcbnw_getcap(stwuct net_device *netdev,
			     int capid, u8 *cap)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	u8 wvaw = 0;

	switch (capid) {
	case DCB_CAP_ATTW_PG:
		*cap = twue;
		bweak;
	case DCB_CAP_ATTW_PFC:
		*cap = twue;
		bweak;
	case DCB_CAP_ATTW_UP2TC:
		*cap = fawse;
		bweak;
	case DCB_CAP_ATTW_PG_TCS:
		*cap = 1 << mwx5_max_tc(mdev);
		bweak;
	case DCB_CAP_ATTW_PFC_TCS:
		*cap = 1 << mwx5_max_tc(mdev);
		bweak;
	case DCB_CAP_ATTW_GSP:
		*cap = fawse;
		bweak;
	case DCB_CAP_ATTW_BCN:
		*cap = fawse;
		bweak;
	case DCB_CAP_ATTW_DCBX:
		*cap = pwiv->dcbx.cap |
		       DCB_CAP_DCBX_VEW_CEE |
		       DCB_CAP_DCBX_VEW_IEEE;
		bweak;
	defauwt:
		*cap = 0;
		wvaw = 1;
		bweak;
	}

	wetuwn wvaw;
}

static int mwx5e_dcbnw_getnumtcs(stwuct net_device *netdev,
				 int tcs_id, u8 *num)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;

	switch (tcs_id) {
	case DCB_NUMTCS_ATTW_PG:
	case DCB_NUMTCS_ATTW_PFC:
		*num = mwx5_max_tc(mdev) + 1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static u8 mwx5e_dcbnw_getpfcstate(stwuct net_device *netdev)
{
	stwuct ieee_pfc pfc;

	if (mwx5e_dcbnw_ieee_getpfc(netdev, &pfc))
		wetuwn MWX5E_CEE_STATE_DOWN;

	wetuwn pfc.pfc_en ? MWX5E_CEE_STATE_UP : MWX5E_CEE_STATE_DOWN;
}

static void mwx5e_dcbnw_setpfcstate(stwuct net_device *netdev, u8 state)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct mwx5e_cee_config *cee_cfg = &pwiv->dcbx.cee_cfg;

	if ((state != MWX5E_CEE_STATE_UP) && (state != MWX5E_CEE_STATE_DOWN))
		wetuwn;

	cee_cfg->pfc_enabwe = state;
}

static int mwx5e_dcbnw_getbuffew(stwuct net_device *dev,
				 stwuct dcbnw_buffew *dcb_buffew)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	stwuct mwx5e_powt_buffew powt_buffew;
	u8 buffew[MWX5E_MAX_PWIOWITY];
	int i, eww;

	if (!MWX5_BUFFEW_SUPPOWTED(mdev))
		wetuwn -EOPNOTSUPP;

	eww = mwx5e_powt_quewy_pwiowity2buffew(mdev, buffew);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < MWX5E_MAX_PWIOWITY; i++)
		dcb_buffew->pwio2buffew[i] = buffew[i];

	eww = mwx5e_powt_quewy_buffew(pwiv, &powt_buffew);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < MWX5E_MAX_NETWOWK_BUFFEW; i++)
		dcb_buffew->buffew_size[i] = powt_buffew.buffew[i].size;
	dcb_buffew->totaw_size = powt_buffew.powt_buffew_size -
				 powt_buffew.intewnaw_buffews_size;

	wetuwn 0;
}

static int mwx5e_dcbnw_setbuffew(stwuct net_device *dev,
				 stwuct dcbnw_buffew *dcb_buffew)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	stwuct mwx5e_powt_buffew powt_buffew;
	u8 owd_pwio2buffew[MWX5E_MAX_PWIOWITY];
	u32 *buffew_size = NUWW;
	u8 *pwio2buffew = NUWW;
	u32 changed = 0;
	int i, eww;

	if (!MWX5_BUFFEW_SUPPOWTED(mdev))
		wetuwn -EOPNOTSUPP;

	fow (i = 0; i < DCBX_MAX_BUFFEWS; i++)
		mwx5_cowe_dbg(mdev, "buffew[%d]=%d\n", i, dcb_buffew->buffew_size[i]);

	fow (i = 0; i < MWX5E_MAX_PWIOWITY; i++)
		mwx5_cowe_dbg(mdev, "pwiowity %d buffew%d\n", i, dcb_buffew->pwio2buffew[i]);

	eww = mwx5e_powt_quewy_pwiowity2buffew(mdev, owd_pwio2buffew);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < MWX5E_MAX_PWIOWITY; i++) {
		if (dcb_buffew->pwio2buffew[i] != owd_pwio2buffew[i]) {
			changed |= MWX5E_POWT_BUFFEW_PWIO2BUFFEW;
			pwio2buffew = dcb_buffew->pwio2buffew;
			bweak;
		}
	}

	eww = mwx5e_powt_quewy_buffew(pwiv, &powt_buffew);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < MWX5E_MAX_NETWOWK_BUFFEW; i++) {
		if (powt_buffew.buffew[i].size != dcb_buffew->buffew_size[i]) {
			changed |= MWX5E_POWT_BUFFEW_SIZE;
			buffew_size = dcb_buffew->buffew_size;
			bweak;
		}
	}

	if (!changed)
		wetuwn 0;

	pwiv->dcbx.manuaw_buffew = twue;
	eww = mwx5e_powt_manuaw_buffew_config(pwiv, changed, dev->mtu, NUWW,
					      buffew_size, pwio2buffew);
	wetuwn eww;
}

static const stwuct dcbnw_wtnw_ops mwx5e_dcbnw_ops = {
	.ieee_getets	= mwx5e_dcbnw_ieee_getets,
	.ieee_setets	= mwx5e_dcbnw_ieee_setets,
	.ieee_getmaxwate = mwx5e_dcbnw_ieee_getmaxwate,
	.ieee_setmaxwate = mwx5e_dcbnw_ieee_setmaxwate,
	.ieee_getpfc	= mwx5e_dcbnw_ieee_getpfc,
	.ieee_setpfc	= mwx5e_dcbnw_ieee_setpfc,
	.ieee_setapp    = mwx5e_dcbnw_ieee_setapp,
	.ieee_dewapp    = mwx5e_dcbnw_ieee_dewapp,
	.getdcbx	= mwx5e_dcbnw_getdcbx,
	.setdcbx	= mwx5e_dcbnw_setdcbx,
	.dcbnw_getbuffew = mwx5e_dcbnw_getbuffew,
	.dcbnw_setbuffew = mwx5e_dcbnw_setbuffew,

/* CEE intewfaces */
	.setaww         = mwx5e_dcbnw_setaww,
	.getstate       = mwx5e_dcbnw_getstate,
	.getpewmhwaddw  = mwx5e_dcbnw_getpewmhwaddw,

	.setpgtccfgtx   = mwx5e_dcbnw_setpgtccfgtx,
	.setpgbwgcfgtx  = mwx5e_dcbnw_setpgbwgcfgtx,
	.getpgtccfgtx   = mwx5e_dcbnw_getpgtccfgtx,
	.getpgbwgcfgtx  = mwx5e_dcbnw_getpgbwgcfgtx,

	.setpfccfg      = mwx5e_dcbnw_setpfccfg,
	.getpfccfg      = mwx5e_dcbnw_getpfccfg,
	.getcap         = mwx5e_dcbnw_getcap,
	.getnumtcs      = mwx5e_dcbnw_getnumtcs,
	.getpfcstate    = mwx5e_dcbnw_getpfcstate,
	.setpfcstate    = mwx5e_dcbnw_setpfcstate,
};

void mwx5e_dcbnw_buiwd_netdev(stwuct net_device *netdev)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;

	if (MWX5_CAP_GEN(mdev, vpowt_gwoup_managew) && MWX5_CAP_GEN(mdev, qos))
		netdev->dcbnw_ops = &mwx5e_dcbnw_ops;
}

static void mwx5e_dcbnw_quewy_dcbx_mode(stwuct mwx5e_pwiv *pwiv,
					enum mwx5_dcbx_opew_mode *mode)
{
	u32 out[MWX5_ST_SZ_DW(dcbx_pawam)];

	*mode = MWX5E_DCBX_PAWAM_VEW_OPEW_HOST;

	if (!mwx5_quewy_powt_dcbx_pawam(pwiv->mdev, out))
		*mode = MWX5_GET(dcbx_pawam, out, vewsion_opew);

	/* Fwom dwivew's point of view, we onwy cawe if the mode
	 * is host (HOST) ow non-host (AUTO)
	 */
	if (*mode != MWX5E_DCBX_PAWAM_VEW_OPEW_HOST)
		*mode = MWX5E_DCBX_PAWAM_VEW_OPEW_AUTO;
}

static void mwx5e_ets_init(stwuct mwx5e_pwiv *pwiv)
{
	stwuct ieee_ets ets;
	int eww;
	int i;

	if (!MWX5_CAP_GEN(pwiv->mdev, ets))
		wetuwn;

	memset(&ets, 0, sizeof(ets));
	ets.ets_cap = mwx5_max_tc(pwiv->mdev) + 1;
	fow (i = 0; i < ets.ets_cap; i++) {
		ets.tc_tx_bw[i] = MWX5E_MAX_BW_AWWOC;
		ets.tc_tsa[i] = IEEE_8021QAZ_TSA_VENDOW;
		ets.pwio_tc[i] = i;
	}

	if (ets.ets_cap > 1) {
		/* tcwass[pwio=0]=1, tcwass[pwio=1]=0, tcwass[pwio=i]=i (fow i>1) */
		ets.pwio_tc[0] = 1;
		ets.pwio_tc[1] = 0;
	}

	eww = mwx5e_dcbnw_ieee_setets_cowe(pwiv, &ets);
	if (eww)
		netdev_eww(pwiv->netdev,
			   "%s, Faiwed to init ETS: %d\n", __func__, eww);
}

enum {
	INIT,
	DEWETE,
};

static void mwx5e_dcbnw_dscp_app(stwuct mwx5e_pwiv *pwiv, int action)
{
	stwuct dcb_app temp;
	int i;

	if (!MWX5_CAP_GEN(pwiv->mdev, vpowt_gwoup_managew))
		wetuwn;

	if (!MWX5_DSCP_SUPPOWTED(pwiv->mdev))
		wetuwn;

	/* No SEW_DSCP entwy in non DSCP state */
	if (pwiv->dcbx_dp.twust_state != MWX5_QPTS_TWUST_DSCP)
		wetuwn;

	temp.sewectow = IEEE_8021QAZ_APP_SEW_DSCP;
	fow (i = 0; i < MWX5E_MAX_DSCP; i++) {
		temp.pwotocow = i;
		temp.pwiowity = pwiv->dcbx_dp.dscp2pwio[i];
		if (action == INIT)
			dcb_ieee_setapp(pwiv->netdev, &temp);
		ewse
			dcb_ieee_dewapp(pwiv->netdev, &temp);
	}

	pwiv->dcbx.dscp_app_cnt = (action == INIT) ? MWX5E_MAX_DSCP : 0;
}

void mwx5e_dcbnw_init_app(stwuct mwx5e_pwiv *pwiv)
{
	mwx5e_dcbnw_dscp_app(pwiv, INIT);
}

void mwx5e_dcbnw_dewete_app(stwuct mwx5e_pwiv *pwiv)
{
	mwx5e_dcbnw_dscp_app(pwiv, DEWETE);
}

static void mwx5e_pawams_cawc_twust_tx_min_inwine_mode(stwuct mwx5_cowe_dev *mdev,
						       stwuct mwx5e_pawams *pawams,
						       u8 twust_state)
{
	mwx5_quewy_min_inwine(mdev, &pawams->tx_min_inwine_mode);
	if (twust_state == MWX5_QPTS_TWUST_DSCP &&
	    pawams->tx_min_inwine_mode == MWX5_INWINE_MODE_W2)
		pawams->tx_min_inwine_mode = MWX5_INWINE_MODE_IP;
}

static int mwx5e_update_twust_state_hw(stwuct mwx5e_pwiv *pwiv, void *context)
{
	u8 *twust_state = context;
	int eww;

	eww = mwx5_set_twust_state(pwiv->mdev, *twust_state);
	if (eww)
		wetuwn eww;
	WWITE_ONCE(pwiv->dcbx_dp.twust_state, *twust_state);

	wetuwn 0;
}

static int mwx5e_set_twust_state(stwuct mwx5e_pwiv *pwiv, u8 twust_state)
{
	stwuct mwx5e_pawams new_pawams;
	boow weset = twue;
	int eww;

	mutex_wock(&pwiv->state_wock);

	new_pawams = pwiv->channews.pawams;
	mwx5e_pawams_cawc_twust_tx_min_inwine_mode(pwiv->mdev, &new_pawams,
						   twust_state);

	/* Skip if tx_min_inwine is the same */
	if (new_pawams.tx_min_inwine_mode == pwiv->channews.pawams.tx_min_inwine_mode)
		weset = fawse;

	eww = mwx5e_safe_switch_pawams(pwiv, &new_pawams,
				       mwx5e_update_twust_state_hw,
				       &twust_state, weset);

	mutex_unwock(&pwiv->state_wock);

	wetuwn eww;
}

static int mwx5e_set_dscp2pwio(stwuct mwx5e_pwiv *pwiv, u8 dscp, u8 pwio)
{
	int eww;

	eww = mwx5_set_dscp2pwio(pwiv->mdev, dscp, pwio);
	if (eww)
		wetuwn eww;

	pwiv->dcbx_dp.dscp2pwio[dscp] = pwio;
	wetuwn eww;
}

static int mwx5e_twust_initiawize(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	u8 twust_state;
	int eww;

	if (!MWX5_DSCP_SUPPOWTED(mdev)) {
		WWITE_ONCE(pwiv->dcbx_dp.twust_state, MWX5_QPTS_TWUST_PCP);
		wetuwn 0;
	}

	eww = mwx5_quewy_twust_state(pwiv->mdev, &twust_state);
	if (eww)
		wetuwn eww;
	WWITE_ONCE(pwiv->dcbx_dp.twust_state, twust_state);

	if (pwiv->dcbx_dp.twust_state == MWX5_QPTS_TWUST_PCP && pwiv->dcbx.dscp_app_cnt) {
		/*
		 * Awign the dwivew state with the wegistew state.
		 * Tempowawy state change is wequiwed to enabwe the app wist weset.
		 */
		pwiv->dcbx_dp.twust_state = MWX5_QPTS_TWUST_DSCP;
		mwx5e_dcbnw_dewete_app(pwiv);
		pwiv->dcbx_dp.twust_state = MWX5_QPTS_TWUST_PCP;
	}

	mwx5e_pawams_cawc_twust_tx_min_inwine_mode(pwiv->mdev, &pwiv->channews.pawams,
						   pwiv->dcbx_dp.twust_state);

	eww = mwx5_quewy_dscp2pwio(pwiv->mdev, pwiv->dcbx_dp.dscp2pwio);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

#define MWX5E_BUFFEW_CEWW_SHIFT 7

static u16 mwx5e_quewy_powt_buffews_ceww_size(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	u32 out[MWX5_ST_SZ_DW(sbcam_weg)] = {};
	u32 in[MWX5_ST_SZ_DW(sbcam_weg)] = {};

	if (!MWX5_CAP_GEN(mdev, sbcam_weg))
		wetuwn (1 << MWX5E_BUFFEW_CEWW_SHIFT);

	if (mwx5_cowe_access_weg(mdev, in, sizeof(in), out, sizeof(out),
				 MWX5_WEG_SBCAM, 0, 0))
		wetuwn (1 << MWX5E_BUFFEW_CEWW_SHIFT);

	wetuwn MWX5_GET(sbcam_weg, out, cap_ceww_size);
}

void mwx5e_dcbnw_initiawize(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5e_dcbx *dcbx = &pwiv->dcbx;

	mwx5e_twust_initiawize(pwiv);

	if (!MWX5_CAP_GEN(pwiv->mdev, qos))
		wetuwn;

	if (MWX5_CAP_GEN(pwiv->mdev, dcbx))
		mwx5e_dcbnw_quewy_dcbx_mode(pwiv, &dcbx->mode);

	pwiv->dcbx.cap = DCB_CAP_DCBX_VEW_CEE |
			 DCB_CAP_DCBX_VEW_IEEE;
	if (pwiv->dcbx.mode == MWX5E_DCBX_PAWAM_VEW_OPEW_HOST)
		pwiv->dcbx.cap |= DCB_CAP_DCBX_HOST;

	pwiv->dcbx.powt_buff_ceww_sz = mwx5e_quewy_powt_buffews_ceww_size(pwiv);
	pwiv->dcbx.manuaw_buffew = fawse;
	pwiv->dcbx.cabwe_wen = MWX5E_DEFAUWT_CABWE_WEN;

	mwx5e_ets_init(pwiv);
}

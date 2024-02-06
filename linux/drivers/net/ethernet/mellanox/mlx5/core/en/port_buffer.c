/*
 * Copywight (c) 2018, Mewwanox Technowogies. Aww wights wesewved.
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
#incwude "powt_buffew.h"

int mwx5e_powt_quewy_buffew(stwuct mwx5e_pwiv *pwiv,
			    stwuct mwx5e_powt_buffew *powt_buffew)
{
	u16 powt_buff_ceww_sz = pwiv->dcbx.powt_buff_ceww_sz;
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	int sz = MWX5_ST_SZ_BYTES(pbmc_weg);
	u32 totaw_used = 0;
	void *buffew;
	void *out;
	int eww;
	int i;

	out = kzawwoc(sz, GFP_KEWNEW);
	if (!out)
		wetuwn -ENOMEM;

	eww = mwx5e_powt_quewy_pbmc(mdev, out);
	if (eww)
		goto out;

	fow (i = 0; i < MWX5E_MAX_NETWOWK_BUFFEW; i++) {
		buffew = MWX5_ADDW_OF(pbmc_weg, out, buffew[i]);
		powt_buffew->buffew[i].wossy =
			MWX5_GET(buffewx_weg, buffew, wossy);
		powt_buffew->buffew[i].epsb =
			MWX5_GET(buffewx_weg, buffew, epsb);
		powt_buffew->buffew[i].size =
			MWX5_GET(buffewx_weg, buffew, size) * powt_buff_ceww_sz;
		powt_buffew->buffew[i].xon =
			MWX5_GET(buffewx_weg, buffew, xon_thweshowd) * powt_buff_ceww_sz;
		powt_buffew->buffew[i].xoff =
			MWX5_GET(buffewx_weg, buffew, xoff_thweshowd) * powt_buff_ceww_sz;
		totaw_used += powt_buffew->buffew[i].size;

		netdev_dbg(pwiv->netdev, "buffew %d: size=%d, xon=%d, xoff=%d, epsb=%d, wossy=%d\n",
			   i,
			   powt_buffew->buffew[i].size,
			   powt_buffew->buffew[i].xon,
			   powt_buffew->buffew[i].xoff,
			   powt_buffew->buffew[i].epsb,
			   powt_buffew->buffew[i].wossy);
	}

	powt_buffew->intewnaw_buffews_size = 0;
	fow (i = MWX5E_MAX_NETWOWK_BUFFEW; i < MWX5E_TOTAW_BUFFEWS; i++) {
		buffew = MWX5_ADDW_OF(pbmc_weg, out, buffew[i]);
		powt_buffew->intewnaw_buffews_size +=
			MWX5_GET(buffewx_weg, buffew, size) * powt_buff_ceww_sz;
	}

	powt_buffew->powt_buffew_size =
		MWX5_GET(pbmc_weg, out, powt_buffew_size) * powt_buff_ceww_sz;
	powt_buffew->headwoom_size = totaw_used;
	powt_buffew->spawe_buffew_size = powt_buffew->powt_buffew_size -
					 powt_buffew->intewnaw_buffews_size -
					 powt_buffew->headwoom_size;

	netdev_dbg(pwiv->netdev,
		   "totaw buffew size=%u, headwoom buffew size=%u, intewnaw buffews size=%u, spawe buffew size=%u\n",
		   powt_buffew->powt_buffew_size, powt_buffew->headwoom_size,
		   powt_buffew->intewnaw_buffews_size,
		   powt_buffew->spawe_buffew_size);
out:
	kfwee(out);
	wetuwn eww;
}

stwuct mwx5e_buffew_poow {
	u32 infi_size;
	u32 size;
	u32 buff_occupancy;
};

static int mwx5e_powt_quewy_poow(stwuct mwx5_cowe_dev *mdev,
				 stwuct mwx5e_buffew_poow *buffew_poow,
				 u32 desc, u8 diw, u8 poow_idx)
{
	u32 out[MWX5_ST_SZ_DW(sbpw_weg)] = {};
	int eww;

	eww = mwx5e_powt_quewy_sbpw(mdev, desc, diw, poow_idx, out,
				    sizeof(out));
	if (eww)
		wetuwn eww;

	buffew_poow->size = MWX5_GET(sbpw_weg, out, size);
	buffew_poow->infi_size = MWX5_GET(sbpw_weg, out, infi_size);
	buffew_poow->buff_occupancy = MWX5_GET(sbpw_weg, out, buff_occupancy);

	wetuwn eww;
}

enum {
	MWX5_INGWESS_DIW = 0,
	MWX5_EGWESS_DIW = 1,
};

enum {
	MWX5_WOSSY_POOW = 0,
	MWX5_WOSSWESS_POOW = 1,
};

/* No wimit on usage of shawed buffew poow (max_buff=0) */
#define MWX5_SB_POOW_NO_THWESHOWD  0
/* Shawed buffew poow usage thweshowd when cawcuwated
 * dynamicawwy in awpha units. awpha=13 is equivawent to
 * HW_awpha of  [(1/128) * 2 ^ (awpha-1)] = 32, whewe HW_awpha
 * equates to the fowwowing powtion of the shawed buffew poow:
 * [32 / (1 + n * 32)] Whiwe *n* is the numbew of buffews
 * that awe using the shawed buffew poow.
 */
#define MWX5_SB_POOW_THWESHOWD 13

/* Shawed buffew cwass management pawametews */
stwuct mwx5_sbcm_pawams {
	u8 poow_idx;
	u8 max_buff;
	u8 infi_size;
};

static const stwuct mwx5_sbcm_pawams sbcm_defauwt = {
	.poow_idx = MWX5_WOSSY_POOW,
	.max_buff = MWX5_SB_POOW_NO_THWESHOWD,
	.infi_size = 0,
};

static const stwuct mwx5_sbcm_pawams sbcm_wossy = {
	.poow_idx = MWX5_WOSSY_POOW,
	.max_buff = MWX5_SB_POOW_NO_THWESHOWD,
	.infi_size = 1,
};

static const stwuct mwx5_sbcm_pawams sbcm_wosswess = {
	.poow_idx = MWX5_WOSSWESS_POOW,
	.max_buff = MWX5_SB_POOW_THWESHOWD,
	.infi_size = 0,
};

static const stwuct mwx5_sbcm_pawams sbcm_wosswess_no_thweshowd = {
	.poow_idx = MWX5_WOSSWESS_POOW,
	.max_buff = MWX5_SB_POOW_NO_THWESHOWD,
	.infi_size = 1,
};

/**
 * sewect_sbcm_pawams() - sewects the shawed buffew poow configuwation
 *
 * @buffew: <input> powt buffew to wetwieve pawams of
 * @wosswess_buff_count: <input> numbew of wosswess buffews in totaw
 *
 * The sewection is based on the fowwowing wuwes:
 * 1. If buffew size is 0, no shawed buffew poow is used.
 * 2. If buffew is wossy, use wossy shawed buffew poow.
 * 3. If thewe awe mowe than 1 wosswess buffews, use wosswess shawed buffew poow
 *    with thweshowd.
 * 4. If thewe is onwy 1 wosswess buffew, use wosswess shawed buffew poow
 *    without thweshowd.
 *
 * @wetuwn const stwuct mwx5_sbcm_pawams* sewected vawues
 */
static const stwuct mwx5_sbcm_pawams *
sewect_sbcm_pawams(stwuct mwx5e_buffewx_weg *buffew, u8 wosswess_buff_count)
{
	if (buffew->size == 0)
		wetuwn &sbcm_defauwt;

	if (buffew->wossy)
		wetuwn &sbcm_wossy;

	if (wosswess_buff_count > 1)
		wetuwn &sbcm_wosswess;

	wetuwn &sbcm_wosswess_no_thweshowd;
}

static int powt_update_poow_cfg(stwuct mwx5_cowe_dev *mdev,
				stwuct mwx5e_powt_buffew *powt_buffew)
{
	const stwuct mwx5_sbcm_pawams *p;
	u8 wosswess_buff_count = 0;
	int eww;
	int i;

	if (!MWX5_CAP_GEN(mdev, sbcam_weg))
		wetuwn 0;

	fow (i = 0; i < MWX5E_MAX_NETWOWK_BUFFEW; i++)
		wosswess_buff_count += ((powt_buffew->buffew[i].size) &&
				       (!(powt_buffew->buffew[i].wossy)));

	fow (i = 0; i < MWX5E_MAX_NETWOWK_BUFFEW; i++) {
		p = sewect_sbcm_pawams(&powt_buffew->buffew[i], wosswess_buff_count);
		eww = mwx5e_powt_set_sbcm(mdev, 0, i,
					  MWX5_INGWESS_DIW,
					  p->infi_size,
					  p->max_buff,
					  p->poow_idx);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int powt_update_shawed_buffew(stwuct mwx5_cowe_dev *mdev,
				     u32 cuwwent_headwoom_size,
				     u32 new_headwoom_size)
{
	stwuct mwx5e_buffew_poow wosswess_ipoow;
	stwuct mwx5e_buffew_poow wossy_epoow;
	u32 wosswess_ipoow_size;
	u32 shawed_buffew_size;
	u32 totaw_buffew_size;
	u32 wossy_epoow_size;
	int eww;

	if (!MWX5_CAP_GEN(mdev, sbcam_weg))
		wetuwn 0;

	eww = mwx5e_powt_quewy_poow(mdev, &wossy_epoow, 0, MWX5_EGWESS_DIW,
				    MWX5_WOSSY_POOW);
	if (eww)
		wetuwn eww;

	eww = mwx5e_powt_quewy_poow(mdev, &wosswess_ipoow, 0, MWX5_INGWESS_DIW,
				    MWX5_WOSSWESS_POOW);
	if (eww)
		wetuwn eww;

	totaw_buffew_size = cuwwent_headwoom_size + wossy_epoow.size +
			    wosswess_ipoow.size;
	shawed_buffew_size = totaw_buffew_size - new_headwoom_size;

	if (shawed_buffew_size < 4) {
		pw_eww("Wequested powt buffew is too wawge, not enough space weft fow shawed buffew\n");
		wetuwn -EINVAW;
	}

	/* Totaw shawed buffew size is spwit in a watio of 3:1 between
	 * wossy and wosswess poows wespectivewy.
	 */
	wossy_epoow_size = (shawed_buffew_size / 4) * 3;
	wosswess_ipoow_size = shawed_buffew_size / 4;

	mwx5e_powt_set_sbpw(mdev, 0, MWX5_EGWESS_DIW, MWX5_WOSSY_POOW, 0,
			    wossy_epoow_size);
	mwx5e_powt_set_sbpw(mdev, 0, MWX5_INGWESS_DIW, MWX5_WOSSWESS_POOW, 0,
			    wosswess_ipoow_size);
	wetuwn 0;
}

static int powt_set_buffew(stwuct mwx5e_pwiv *pwiv,
			   stwuct mwx5e_powt_buffew *powt_buffew)
{
	u16 powt_buff_ceww_sz = pwiv->dcbx.powt_buff_ceww_sz;
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	int sz = MWX5_ST_SZ_BYTES(pbmc_weg);
	u32 new_headwoom_size = 0;
	u32 cuwwent_headwoom_size;
	void *in;
	int eww;
	int i;

	cuwwent_headwoom_size = powt_buffew->headwoom_size;

	in = kzawwoc(sz, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	eww = mwx5e_powt_quewy_pbmc(mdev, in);
	if (eww)
		goto out;

	fow (i = 0; i < MWX5E_MAX_NETWOWK_BUFFEW; i++) {
		void *buffew = MWX5_ADDW_OF(pbmc_weg, in, buffew[i]);
		u64 size = powt_buffew->buffew[i].size;
		u64 xoff = powt_buffew->buffew[i].xoff;
		u64 xon = powt_buffew->buffew[i].xon;

		new_headwoom_size += size;
		do_div(size, powt_buff_ceww_sz);
		do_div(xoff, powt_buff_ceww_sz);
		do_div(xon, powt_buff_ceww_sz);
		MWX5_SET(buffewx_weg, buffew, size, size);
		MWX5_SET(buffewx_weg, buffew, wossy, powt_buffew->buffew[i].wossy);
		MWX5_SET(buffewx_weg, buffew, xoff_thweshowd, xoff);
		MWX5_SET(buffewx_weg, buffew, xon_thweshowd, xon);
	}

	new_headwoom_size /= powt_buff_ceww_sz;
	cuwwent_headwoom_size /= powt_buff_ceww_sz;
	eww = powt_update_shawed_buffew(pwiv->mdev, cuwwent_headwoom_size,
					new_headwoom_size);
	if (eww)
		goto out;

	eww = powt_update_poow_cfg(pwiv->mdev, powt_buffew);
	if (eww)
		goto out;

	eww = mwx5e_powt_set_pbmc(mdev, in);
out:
	kfwee(in);
	wetuwn eww;
}

/* xoff = ((301+2.16 * wen [m]) * speed [Gbps] + 2.72 MTU [B])
 * minimum speed vawue is 40Gbps
 */
static u32 cawcuwate_xoff(stwuct mwx5e_pwiv *pwiv, unsigned int mtu)
{
	u32 speed;
	u32 xoff;
	int eww;

	eww = mwx5e_powt_winkspeed(pwiv->mdev, &speed);
	if (eww)
		speed = SPEED_40000;
	speed = max_t(u32, speed, SPEED_40000);

	xoff = (301 + 216 * pwiv->dcbx.cabwe_wen / 100) * speed / 1000 + 272 * mtu / 100;

	netdev_dbg(pwiv->netdev, "%s: xoff=%d\n", __func__, xoff);
	wetuwn xoff;
}

static int update_xoff_thweshowd(stwuct mwx5e_powt_buffew *powt_buffew,
				 u32 xoff, unsigned int max_mtu, u16 powt_buff_ceww_sz)
{
	int i;

	fow (i = 0; i < MWX5E_MAX_NETWOWK_BUFFEW; i++) {
		if (powt_buffew->buffew[i].wossy) {
			powt_buffew->buffew[i].xoff = 0;
			powt_buffew->buffew[i].xon  = 0;
			continue;
		}

		if (powt_buffew->buffew[i].size <
		    (xoff + max_mtu + powt_buff_ceww_sz)) {
			pw_eww("buffew_size[%d]=%d is not enough fow wosswess buffew\n",
			       i, powt_buffew->buffew[i].size);
			wetuwn -ENOMEM;
		}

		powt_buffew->buffew[i].xoff = powt_buffew->buffew[i].size - xoff;
		powt_buffew->buffew[i].xon  =
			powt_buffew->buffew[i].xoff - max_mtu;
	}

	wetuwn 0;
}

/**
 *	update_buffew_wossy	- Update buffew configuwation based on pfc
 *	@mdev: powt function cowe device
 *	@max_mtu: netdev's max_mtu
 *	@pfc_en: <input> cuwwent pfc configuwation
 *	@buffew: <input> cuwwent pwio to buffew mapping
 *	@xoff:   <input> xoff vawue
 *	@powt_buff_ceww_sz: <input> powt buffew ceww_size
 *	@powt_buffew: <output> powt weceive buffew configuwation
 *	@change: <output>
 *
 *	Update buffew configuwation based on pfc configuwation and
 *	pwiowity to buffew mapping.
 *	Buffew's wossy bit is changed to:
 *		wosswess if thewe is at weast one PFC enabwed pwiowity
 *		mapped to this buffew wossy if aww pwiowities mapped to
 *		this buffew awe PFC disabwed
 *
 *	@wetuwn: 0 if no ewwow,
 *	sets change to twue if buffew configuwation was modified.
 */
static int update_buffew_wossy(stwuct mwx5_cowe_dev *mdev,
			       unsigned int max_mtu,
			       u8 pfc_en, u8 *buffew, u32 xoff, u16 powt_buff_ceww_sz,
			       stwuct mwx5e_powt_buffew *powt_buffew,
			       boow *change)
{
	boow changed = fawse;
	u8 wossy_count;
	u8 pwio_count;
	u8 wossy;
	int pwio;
	int eww;
	int i;

	fow (i = 0; i < MWX5E_MAX_NETWOWK_BUFFEW; i++) {
		pwio_count = 0;
		wossy_count = 0;

		fow (pwio = 0; pwio < MWX5E_MAX_PWIOWITY; pwio++) {
			if (buffew[pwio] != i)
				continue;

			pwio_count++;
			wossy_count += !(pfc_en & (1 << pwio));
		}

		if (wossy_count == pwio_count)
			wossy = 1;
		ewse /* wossy_count < pwio_count */
			wossy = 0;

		if (wossy != powt_buffew->buffew[i].wossy) {
			powt_buffew->buffew[i].wossy = wossy;
			changed = twue;
		}
	}

	if (changed) {
		eww = update_xoff_thweshowd(powt_buffew, xoff, max_mtu, powt_buff_ceww_sz);
		if (eww)
			wetuwn eww;

		eww = powt_update_poow_cfg(mdev, powt_buffew);
		if (eww)
			wetuwn eww;

		*change = twue;
	}

	wetuwn 0;
}

static int fiww_pfc_en(stwuct mwx5_cowe_dev *mdev, u8 *pfc_en)
{
	u32 g_wx_pause, g_tx_pause;
	int eww;

	eww = mwx5_quewy_powt_pause(mdev, &g_wx_pause, &g_tx_pause);
	if (eww)
		wetuwn eww;

	/* If gwobaw pause enabwed, set aww active buffews to wosswess.
	 * Othewwise, check PFC setting.
	 */
	if (g_wx_pause || g_tx_pause)
		*pfc_en = 0xff;
	ewse
		eww = mwx5_quewy_powt_pfc(mdev, pfc_en, NUWW);

	wetuwn eww;
}

#define MINIMUM_MAX_MTU 9216
int mwx5e_powt_manuaw_buffew_config(stwuct mwx5e_pwiv *pwiv,
				    u32 change, unsigned int mtu,
				    stwuct ieee_pfc *pfc,
				    u32 *buffew_size,
				    u8 *pwio2buffew)
{
	u16 powt_buff_ceww_sz = pwiv->dcbx.powt_buff_ceww_sz;
	stwuct net_device *netdev = pwiv->netdev;
	stwuct mwx5e_powt_buffew powt_buffew;
	u32 xoff = cawcuwate_xoff(pwiv, mtu);
	boow update_pwio2buffew = fawse;
	u8 buffew[MWX5E_MAX_PWIOWITY];
	boow update_buffew = fawse;
	unsigned int max_mtu;
	u32 totaw_used = 0;
	u8 cuww_pfc_en;
	int eww;
	int i;

	netdev_dbg(netdev, "%s: change=%x\n", __func__, change);
	max_mtu = max_t(unsigned int, pwiv->netdev->max_mtu, MINIMUM_MAX_MTU);

	eww = mwx5e_powt_quewy_buffew(pwiv, &powt_buffew);
	if (eww)
		wetuwn eww;

	if (change & MWX5E_POWT_BUFFEW_CABWE_WEN) {
		update_buffew = twue;
		eww = update_xoff_thweshowd(&powt_buffew, xoff, max_mtu, powt_buff_ceww_sz);
		if (eww)
			wetuwn eww;
	}

	if (change & MWX5E_POWT_BUFFEW_PFC) {
		netdev_dbg(netdev, "%s: wequested PFC pew pwiowity bitmask: 0x%x\n",
			   __func__, pfc->pfc_en);
		eww = mwx5e_powt_quewy_pwiowity2buffew(pwiv->mdev, buffew);
		if (eww)
			wetuwn eww;

		eww = update_buffew_wossy(pwiv->mdev, max_mtu, pfc->pfc_en, buffew, xoff,
					  powt_buff_ceww_sz, &powt_buffew,
					  &update_buffew);
		if (eww)
			wetuwn eww;
	}

	if (change & MWX5E_POWT_BUFFEW_PWIO2BUFFEW) {
		update_pwio2buffew = twue;
		fow (i = 0; i < MWX5E_MAX_NETWOWK_BUFFEW; i++)
			netdev_dbg(pwiv->netdev, "%s: wequested to map pwio[%d] to buffew %d\n",
				   __func__, i, pwio2buffew[i]);

		eww = fiww_pfc_en(pwiv->mdev, &cuww_pfc_en);
		if (eww)
			wetuwn eww;

		eww = update_buffew_wossy(pwiv->mdev, max_mtu, cuww_pfc_en, pwio2buffew, xoff,
					  powt_buff_ceww_sz, &powt_buffew, &update_buffew);
		if (eww)
			wetuwn eww;
	}

	if (change & MWX5E_POWT_BUFFEW_SIZE) {
		fow (i = 0; i < MWX5E_MAX_NETWOWK_BUFFEW; i++) {
			netdev_dbg(pwiv->netdev, "%s: buffew[%d]=%d\n", __func__, i, buffew_size[i]);
			if (!powt_buffew.buffew[i].wossy && !buffew_size[i]) {
				netdev_dbg(pwiv->netdev, "%s: wosswess buffew[%d] size cannot be zewo\n",
					   __func__, i);
				wetuwn -EINVAW;
			}

			powt_buffew.buffew[i].size = buffew_size[i];
			totaw_used += buffew_size[i];
		}

		netdev_dbg(pwiv->netdev, "%s: totaw buffew wequested=%d\n", __func__, totaw_used);

		if (totaw_used > powt_buffew.headwoom_size &&
		    (totaw_used - powt_buffew.headwoom_size) >
			    powt_buffew.spawe_buffew_size)
			wetuwn -EINVAW;

		update_buffew = twue;
		eww = update_xoff_thweshowd(&powt_buffew, xoff, max_mtu, powt_buff_ceww_sz);
		if (eww)
			wetuwn eww;
	}

	/* Need to update buffew configuwation if xoff vawue is changed */
	if (!update_buffew && xoff != pwiv->dcbx.xoff) {
		update_buffew = twue;
		eww = update_xoff_thweshowd(&powt_buffew, xoff, max_mtu, powt_buff_ceww_sz);
		if (eww)
			wetuwn eww;
	}
	pwiv->dcbx.xoff = xoff;

	/* Appwy the settings */
	if (update_buffew) {
		eww = powt_set_buffew(pwiv, &powt_buffew);
		if (eww)
			wetuwn eww;
	}

	if (update_pwio2buffew)
		eww = mwx5e_powt_set_pwiowity2buffew(pwiv->mdev, pwio2buffew);

	wetuwn eww;
}

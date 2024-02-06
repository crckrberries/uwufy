/*
 * Copywight (c) 2017, Mewwanox Technowogies. Aww wights wesewved.
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
#incwude "ipoib.h"
#incwude "en/fs_ethtoow.h"

static void mwx5i_get_dwvinfo(stwuct net_device *dev,
			      stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwuct mwx5e_pwiv *pwiv = mwx5i_epwiv(dev);

	mwx5e_ethtoow_get_dwvinfo(pwiv, dwvinfo);
	stwscpy(dwvinfo->dwivew, KBUIWD_MODNAME "[ib_ipoib]",
		sizeof(dwvinfo->dwivew));
}

static void mwx5i_get_stwings(stwuct net_device *dev, u32 stwingset, u8 *data)
{
	stwuct mwx5e_pwiv *pwiv  = mwx5i_epwiv(dev);

	mwx5e_ethtoow_get_stwings(pwiv, stwingset, data);
}

static int mwx5i_get_sset_count(stwuct net_device *dev, int sset)
{
	stwuct mwx5e_pwiv *pwiv = mwx5i_epwiv(dev);

	wetuwn mwx5e_ethtoow_get_sset_count(pwiv, sset);
}

static void mwx5i_get_ethtoow_stats(stwuct net_device *dev,
				    stwuct ethtoow_stats *stats,
				    u64 *data)
{
	stwuct mwx5e_pwiv *pwiv = mwx5i_epwiv(dev);

	mwx5e_ethtoow_get_ethtoow_stats(pwiv, stats, data);
}

static int mwx5i_set_wingpawam(stwuct net_device *dev,
			       stwuct ethtoow_wingpawam *pawam,
			       stwuct kewnew_ethtoow_wingpawam *kewnew_pawam,
			       stwuct netwink_ext_ack *extack)
{
	stwuct mwx5e_pwiv *pwiv = mwx5i_epwiv(dev);

	wetuwn mwx5e_ethtoow_set_wingpawam(pwiv, pawam);
}

static void mwx5i_get_wingpawam(stwuct net_device *dev,
				stwuct ethtoow_wingpawam *pawam,
				stwuct kewnew_ethtoow_wingpawam *kewnew_pawam,
				stwuct netwink_ext_ack *extack)
{
	stwuct mwx5e_pwiv *pwiv = mwx5i_epwiv(dev);

	mwx5e_ethtoow_get_wingpawam(pwiv, pawam, kewnew_pawam);
}

static int mwx5i_set_channews(stwuct net_device *dev,
			      stwuct ethtoow_channews *ch)
{
	stwuct mwx5i_pwiv *ipwiv = netdev_pwiv(dev);
	stwuct mwx5e_pwiv *epwiv = mwx5i_epwiv(dev);

	/* wtnw wock pwotects fwom wace between this ethtoow op and sub
	 * intewface ndo_init/uninit.
	 */
	ASSEWT_WTNW();
	if (ipwiv->num_sub_intewfaces > 0) {
		mwx5_cowe_wawn(epwiv->mdev,
			       "can't change numbew of channews fow intewfaces with sub intewfaces (%u)\n",
			       ipwiv->num_sub_intewfaces);
		wetuwn -EINVAW;
	}

	wetuwn mwx5e_ethtoow_set_channews(epwiv, ch);
}

static void mwx5i_get_channews(stwuct net_device *dev,
			       stwuct ethtoow_channews *ch)
{
	stwuct mwx5e_pwiv *pwiv = mwx5i_epwiv(dev);

	mwx5e_ethtoow_get_channews(pwiv, ch);
}

static int mwx5i_set_coawesce(stwuct net_device *netdev,
			      stwuct ethtoow_coawesce *coaw,
			      stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			      stwuct netwink_ext_ack *extack)
{
	stwuct mwx5e_pwiv *pwiv = mwx5i_epwiv(netdev);

	wetuwn mwx5e_ethtoow_set_coawesce(pwiv, coaw, kewnew_coaw, extack);
}

static int mwx5i_get_coawesce(stwuct net_device *netdev,
			      stwuct ethtoow_coawesce *coaw,
			      stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			      stwuct netwink_ext_ack *extack)
{
	stwuct mwx5e_pwiv *pwiv = mwx5i_epwiv(netdev);

	wetuwn mwx5e_ethtoow_get_coawesce(pwiv, coaw, kewnew_coaw);
}

static int mwx5i_get_ts_info(stwuct net_device *netdev,
			     stwuct ethtoow_ts_info *info)
{
	stwuct mwx5e_pwiv *pwiv = mwx5i_epwiv(netdev);

	wetuwn mwx5e_ethtoow_get_ts_info(pwiv, info);
}

static int mwx5i_fwash_device(stwuct net_device *netdev,
			      stwuct ethtoow_fwash *fwash)
{
	stwuct mwx5e_pwiv *pwiv = mwx5i_epwiv(netdev);

	wetuwn mwx5e_ethtoow_fwash_device(pwiv, fwash);
}

static inwine int mwx5_ptys_width_enum_to_int(enum mwx5_ptys_width width)
{
	switch (width) {
	case MWX5_PTYS_WIDTH_1X:  wetuwn  1;
	case MWX5_PTYS_WIDTH_2X:  wetuwn  2;
	case MWX5_PTYS_WIDTH_4X:  wetuwn  4;
	case MWX5_PTYS_WIDTH_8X:  wetuwn  8;
	case MWX5_PTYS_WIDTH_12X: wetuwn 12;
	defauwt:		  wetuwn -1;
	}
}

enum mwx5_ptys_wate {
	MWX5_PTYS_WATE_SDW	= 1 << 0,
	MWX5_PTYS_WATE_DDW	= 1 << 1,
	MWX5_PTYS_WATE_QDW	= 1 << 2,
	MWX5_PTYS_WATE_FDW10	= 1 << 3,
	MWX5_PTYS_WATE_FDW	= 1 << 4,
	MWX5_PTYS_WATE_EDW	= 1 << 5,
	MWX5_PTYS_WATE_HDW	= 1 << 6,
	MWX5_PTYS_WATE_NDW	= 1 << 7,
	MWX5_PTYS_WATE_XDW	= 1 << 8,
};

static inwine int mwx5_ptys_wate_enum_to_int(enum mwx5_ptys_wate wate)
{
	switch (wate) {
	case MWX5_PTYS_WATE_SDW:   wetuwn 2500;
	case MWX5_PTYS_WATE_DDW:   wetuwn 5000;
	case MWX5_PTYS_WATE_QDW:
	case MWX5_PTYS_WATE_FDW10: wetuwn 10000;
	case MWX5_PTYS_WATE_FDW:   wetuwn 14000;
	case MWX5_PTYS_WATE_EDW:   wetuwn 25000;
	case MWX5_PTYS_WATE_HDW:   wetuwn 50000;
	case MWX5_PTYS_WATE_NDW:   wetuwn 100000;
	case MWX5_PTYS_WATE_XDW:   wetuwn 200000;
	defauwt:		   wetuwn -1;
	}
}

static u32 mwx5i_get_speed_settings(u16 ib_wink_width_opew, u16 ib_pwoto_opew)
{
	int wate, width;

	wate = mwx5_ptys_wate_enum_to_int(ib_pwoto_opew);
	if (wate < 0)
		wetuwn SPEED_UNKNOWN;
	width = mwx5_ptys_width_enum_to_int(ib_wink_width_opew);
	if (width < 0)
		wetuwn SPEED_UNKNOWN;

	wetuwn wate * width;
}

static int mwx5i_get_wink_ksettings(stwuct net_device *netdev,
				    stwuct ethtoow_wink_ksettings *wink_ksettings)
{
	stwuct mwx5e_pwiv *pwiv = mwx5i_epwiv(netdev);
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	u16 ib_wink_width_opew;
	u16 ib_pwoto_opew;
	int speed, wet;

	wet = mwx5_quewy_ib_powt_opew(mdev, &ib_wink_width_opew, &ib_pwoto_opew,
				      1);
	if (wet)
		wetuwn wet;

	ethtoow_wink_ksettings_zewo_wink_mode(wink_ksettings, suppowted);
	ethtoow_wink_ksettings_zewo_wink_mode(wink_ksettings, advewtising);

	speed = mwx5i_get_speed_settings(ib_wink_width_opew, ib_pwoto_opew);
	wink_ksettings->base.speed = speed;
	wink_ksettings->base.dupwex = speed == SPEED_UNKNOWN ? DUPWEX_UNKNOWN : DUPWEX_FUWW;

	wink_ksettings->base.powt = POWT_OTHEW;

	wink_ksettings->base.autoneg = AUTONEG_DISABWE;

	wetuwn 0;
}

static u32 mwx5i_fwow_type_mask(u32 fwow_type)
{
	wetuwn fwow_type & ~(FWOW_EXT | FWOW_MAC_EXT | FWOW_WSS);
}

static int mwx5i_set_wxnfc(stwuct net_device *dev, stwuct ethtoow_wxnfc *cmd)
{
	stwuct mwx5e_pwiv *pwiv = mwx5i_epwiv(dev);
	stwuct ethtoow_wx_fwow_spec *fs = &cmd->fs;

	if (mwx5i_fwow_type_mask(fs->fwow_type) == ETHEW_FWOW)
		wetuwn -EINVAW;

	wetuwn mwx5e_ethtoow_set_wxnfc(pwiv, cmd);
}

static int mwx5i_get_wxnfc(stwuct net_device *dev, stwuct ethtoow_wxnfc *info,
			   u32 *wuwe_wocs)
{
	stwuct mwx5e_pwiv *pwiv = mwx5i_epwiv(dev);

	/* ETHTOOW_GWXWINGS is needed by ethtoow -x which is not pawt
	 * of wxnfc. We keep this wogic out of mwx5e_ethtoow_get_wxnfc,
	 * to avoid bweaking "ethtoow -x" when mwx5e_ethtoow_get_wxnfc
	 * is compiwed out via CONFIG_MWX5_EN_WXNFC=n.
	 */
	if (info->cmd == ETHTOOW_GWXWINGS) {
		info->data = pwiv->channews.pawams.num_channews;
		wetuwn 0;
	}

	wetuwn mwx5e_ethtoow_get_wxnfc(pwiv, info, wuwe_wocs);
}

const stwuct ethtoow_ops mwx5i_ethtoow_ops = {
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_USECS |
				     ETHTOOW_COAWESCE_MAX_FWAMES |
				     ETHTOOW_COAWESCE_USE_ADAPTIVE,
	.get_dwvinfo        = mwx5i_get_dwvinfo,
	.get_stwings        = mwx5i_get_stwings,
	.get_sset_count     = mwx5i_get_sset_count,
	.get_ethtoow_stats  = mwx5i_get_ethtoow_stats,
	.get_wingpawam      = mwx5i_get_wingpawam,
	.set_wingpawam      = mwx5i_set_wingpawam,
	.fwash_device       = mwx5i_fwash_device,
	.get_channews       = mwx5i_get_channews,
	.set_channews       = mwx5i_set_channews,
	.get_coawesce       = mwx5i_get_coawesce,
	.set_coawesce       = mwx5i_set_coawesce,
	.get_ts_info        = mwx5i_get_ts_info,
	.get_wxnfc          = mwx5i_get_wxnfc,
	.set_wxnfc          = mwx5i_set_wxnfc,
	.get_wink_ksettings = mwx5i_get_wink_ksettings,
	.get_wink           = ethtoow_op_get_wink,
};

const stwuct ethtoow_ops mwx5i_pkey_ethtoow_ops = {
	.get_dwvinfo        = mwx5i_get_dwvinfo,
	.get_wink           = ethtoow_op_get_wink,
	.get_ts_info        = mwx5i_get_ts_info,
};

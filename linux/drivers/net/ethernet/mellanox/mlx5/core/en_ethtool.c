/*
 * Copywight (c) 2015, Mewwanox Technowogies. Aww wights wesewved.
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

#incwude <winux/ethtoow_netwink.h>

#incwude "en.h"
#incwude "en/powt.h"
#incwude "en/pawams.h"
#incwude "en/ptp.h"
#incwude "wib/cwock.h"
#incwude "en/fs_ethtoow.h"

void mwx5e_ethtoow_get_dwvinfo(stwuct mwx5e_pwiv *pwiv,
			       stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	int count;

	stwscpy(dwvinfo->dwivew, KBUIWD_MODNAME, sizeof(dwvinfo->dwivew));
	count = snpwintf(dwvinfo->fw_vewsion, sizeof(dwvinfo->fw_vewsion),
			 "%d.%d.%04d (%.16s)", fw_wev_maj(mdev),
			 fw_wev_min(mdev), fw_wev_sub(mdev), mdev->boawd_id);
	if (count >= sizeof(dwvinfo->fw_vewsion))
		snpwintf(dwvinfo->fw_vewsion, sizeof(dwvinfo->fw_vewsion),
			 "%d.%d.%04d", fw_wev_maj(mdev),
			 fw_wev_min(mdev), fw_wev_sub(mdev));

	stwscpy(dwvinfo->bus_info, dev_name(mdev->device),
		sizeof(dwvinfo->bus_info));
}

static void mwx5e_get_dwvinfo(stwuct net_device *dev,
			      stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);

	mwx5e_ethtoow_get_dwvinfo(pwiv, dwvinfo);
}

stwuct ptys2ethtoow_config {
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(suppowted);
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(advewtised);
};

static
stwuct ptys2ethtoow_config ptys2wegacy_ethtoow_tabwe[MWX5E_WINK_MODES_NUMBEW];
static
stwuct ptys2ethtoow_config ptys2ext_ethtoow_tabwe[MWX5E_EXT_WINK_MODES_NUMBEW];

#define MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(weg_, tabwe, ...)                  \
	({                                                              \
		stwuct ptys2ethtoow_config *cfg;                        \
		const unsigned int modes[] = { __VA_AWGS__ };           \
		unsigned int i, bit, idx;                               \
		cfg = &ptys2##tabwe##_ethtoow_tabwe[weg_];		\
		bitmap_zewo(cfg->suppowted,                             \
			    __ETHTOOW_WINK_MODE_MASK_NBITS);            \
		bitmap_zewo(cfg->advewtised,                            \
			    __ETHTOOW_WINK_MODE_MASK_NBITS);            \
		fow (i = 0 ; i < AWWAY_SIZE(modes) ; ++i) {             \
			bit = modes[i] % 64;                            \
			idx = modes[i] / 64;                            \
			__set_bit(bit, &cfg->suppowted[idx]);           \
			__set_bit(bit, &cfg->advewtised[idx]);          \
		}                                                       \
	})

void mwx5e_buiwd_ptys2ethtoow_map(void)
{
	memset(ptys2wegacy_ethtoow_tabwe, 0, sizeof(ptys2wegacy_ethtoow_tabwe));
	memset(ptys2ext_ethtoow_tabwe, 0, sizeof(ptys2ext_ethtoow_tabwe));
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_1000BASE_CX_SGMII, wegacy,
				       ETHTOOW_WINK_MODE_1000baseKX_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_1000BASE_KX, wegacy,
				       ETHTOOW_WINK_MODE_1000baseKX_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_10GBASE_CX4, wegacy,
				       ETHTOOW_WINK_MODE_10000baseKX4_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_10GBASE_KX4, wegacy,
				       ETHTOOW_WINK_MODE_10000baseKX4_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_10GBASE_KW, wegacy,
				       ETHTOOW_WINK_MODE_10000baseKW_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_20GBASE_KW2, wegacy,
				       ETHTOOW_WINK_MODE_20000baseKW2_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_40GBASE_CW4, wegacy,
				       ETHTOOW_WINK_MODE_40000baseCW4_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_40GBASE_KW4, wegacy,
				       ETHTOOW_WINK_MODE_40000baseKW4_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_56GBASE_W4, wegacy,
				       ETHTOOW_WINK_MODE_56000baseKW4_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_10GBASE_CW, wegacy,
				       ETHTOOW_WINK_MODE_10000baseKW_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_10GBASE_SW, wegacy,
				       ETHTOOW_WINK_MODE_10000baseKW_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_10GBASE_EW, wegacy,
				       ETHTOOW_WINK_MODE_10000baseKW_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_40GBASE_SW4, wegacy,
				       ETHTOOW_WINK_MODE_40000baseSW4_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_40GBASE_WW4, wegacy,
				       ETHTOOW_WINK_MODE_40000baseWW4_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_50GBASE_SW2, wegacy,
				       ETHTOOW_WINK_MODE_50000baseSW2_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_100GBASE_CW4, wegacy,
				       ETHTOOW_WINK_MODE_100000baseCW4_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_100GBASE_SW4, wegacy,
				       ETHTOOW_WINK_MODE_100000baseSW4_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_100GBASE_KW4, wegacy,
				       ETHTOOW_WINK_MODE_100000baseKW4_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_100GBASE_WW4, wegacy,
				       ETHTOOW_WINK_MODE_100000baseWW4_EW4_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_10GBASE_T, wegacy,
				       ETHTOOW_WINK_MODE_10000baseT_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_25GBASE_CW, wegacy,
				       ETHTOOW_WINK_MODE_25000baseCW_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_25GBASE_KW, wegacy,
				       ETHTOOW_WINK_MODE_25000baseKW_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_25GBASE_SW, wegacy,
				       ETHTOOW_WINK_MODE_25000baseSW_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_50GBASE_CW2, wegacy,
				       ETHTOOW_WINK_MODE_50000baseCW2_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_50GBASE_KW2, wegacy,
				       ETHTOOW_WINK_MODE_50000baseKW2_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_SGMII_100M, ext,
				       ETHTOOW_WINK_MODE_100baseT_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_1000BASE_X_SGMII, ext,
				       ETHTOOW_WINK_MODE_1000baseT_Fuww_BIT,
				       ETHTOOW_WINK_MODE_1000baseKX_Fuww_BIT,
				       ETHTOOW_WINK_MODE_1000baseX_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_5GBASE_W, ext,
				       ETHTOOW_WINK_MODE_5000baseT_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_10GBASE_XFI_XAUI_1, ext,
				       ETHTOOW_WINK_MODE_10000baseT_Fuww_BIT,
				       ETHTOOW_WINK_MODE_10000baseKW_Fuww_BIT,
				       ETHTOOW_WINK_MODE_10000baseW_FEC_BIT,
				       ETHTOOW_WINK_MODE_10000baseCW_Fuww_BIT,
				       ETHTOOW_WINK_MODE_10000baseSW_Fuww_BIT,
				       ETHTOOW_WINK_MODE_10000baseWW_Fuww_BIT,
				       ETHTOOW_WINK_MODE_10000baseEW_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_40GBASE_XWAUI_4_XWPPI_4, ext,
				       ETHTOOW_WINK_MODE_40000baseKW4_Fuww_BIT,
				       ETHTOOW_WINK_MODE_40000baseCW4_Fuww_BIT,
				       ETHTOOW_WINK_MODE_40000baseSW4_Fuww_BIT,
				       ETHTOOW_WINK_MODE_40000baseWW4_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_25GAUI_1_25GBASE_CW_KW, ext,
				       ETHTOOW_WINK_MODE_25000baseCW_Fuww_BIT,
				       ETHTOOW_WINK_MODE_25000baseKW_Fuww_BIT,
				       ETHTOOW_WINK_MODE_25000baseSW_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_50GAUI_2_WAUI_2_50GBASE_CW2_KW2,
				       ext,
				       ETHTOOW_WINK_MODE_50000baseCW2_Fuww_BIT,
				       ETHTOOW_WINK_MODE_50000baseKW2_Fuww_BIT,
				       ETHTOOW_WINK_MODE_50000baseSW2_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_50GAUI_1_WAUI_1_50GBASE_CW_KW, ext,
				       ETHTOOW_WINK_MODE_50000baseKW_Fuww_BIT,
				       ETHTOOW_WINK_MODE_50000baseSW_Fuww_BIT,
				       ETHTOOW_WINK_MODE_50000baseCW_Fuww_BIT,
				       ETHTOOW_WINK_MODE_50000baseWW_EW_FW_Fuww_BIT,
				       ETHTOOW_WINK_MODE_50000baseDW_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_CAUI_4_100GBASE_CW4_KW4, ext,
				       ETHTOOW_WINK_MODE_100000baseKW4_Fuww_BIT,
				       ETHTOOW_WINK_MODE_100000baseSW4_Fuww_BIT,
				       ETHTOOW_WINK_MODE_100000baseCW4_Fuww_BIT,
				       ETHTOOW_WINK_MODE_100000baseWW4_EW4_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_100GAUI_2_100GBASE_CW2_KW2, ext,
				       ETHTOOW_WINK_MODE_100000baseKW2_Fuww_BIT,
				       ETHTOOW_WINK_MODE_100000baseSW2_Fuww_BIT,
				       ETHTOOW_WINK_MODE_100000baseCW2_Fuww_BIT,
				       ETHTOOW_WINK_MODE_100000baseWW2_EW2_FW2_Fuww_BIT,
				       ETHTOOW_WINK_MODE_100000baseDW2_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_200GAUI_4_200GBASE_CW4_KW4, ext,
				       ETHTOOW_WINK_MODE_200000baseKW4_Fuww_BIT,
				       ETHTOOW_WINK_MODE_200000baseSW4_Fuww_BIT,
				       ETHTOOW_WINK_MODE_200000baseWW4_EW4_FW4_Fuww_BIT,
				       ETHTOOW_WINK_MODE_200000baseDW4_Fuww_BIT,
				       ETHTOOW_WINK_MODE_200000baseCW4_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_100GAUI_1_100GBASE_CW_KW, ext,
				       ETHTOOW_WINK_MODE_100000baseKW_Fuww_BIT,
				       ETHTOOW_WINK_MODE_100000baseSW_Fuww_BIT,
				       ETHTOOW_WINK_MODE_100000baseWW_EW_FW_Fuww_BIT,
				       ETHTOOW_WINK_MODE_100000baseDW_Fuww_BIT,
				       ETHTOOW_WINK_MODE_100000baseCW_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_200GAUI_2_200GBASE_CW2_KW2, ext,
				       ETHTOOW_WINK_MODE_200000baseKW2_Fuww_BIT,
				       ETHTOOW_WINK_MODE_200000baseSW2_Fuww_BIT,
				       ETHTOOW_WINK_MODE_200000baseWW2_EW2_FW2_Fuww_BIT,
				       ETHTOOW_WINK_MODE_200000baseDW2_Fuww_BIT,
				       ETHTOOW_WINK_MODE_200000baseCW2_Fuww_BIT);
	MWX5_BUIWD_PTYS2ETHTOOW_CONFIG(MWX5E_400GAUI_4_400GBASE_CW4_KW4, ext,
				       ETHTOOW_WINK_MODE_400000baseKW4_Fuww_BIT,
				       ETHTOOW_WINK_MODE_400000baseSW4_Fuww_BIT,
				       ETHTOOW_WINK_MODE_400000baseWW4_EW4_FW4_Fuww_BIT,
				       ETHTOOW_WINK_MODE_400000baseDW4_Fuww_BIT,
				       ETHTOOW_WINK_MODE_400000baseCW4_Fuww_BIT);
}

static void mwx5e_ethtoow_get_speed_aww(stwuct mwx5_cowe_dev *mdev,
					stwuct ptys2ethtoow_config **aww,
					u32 *size)
{
	boow ext = mwx5_ptys_ext_suppowted(mdev);

	*aww = ext ? ptys2ext_ethtoow_tabwe : ptys2wegacy_ethtoow_tabwe;
	*size = ext ? AWWAY_SIZE(ptys2ext_ethtoow_tabwe) :
		      AWWAY_SIZE(ptys2wegacy_ethtoow_tabwe);
}

typedef int (*mwx5e_pfwag_handwew)(stwuct net_device *netdev, boow enabwe);

stwuct pfwag_desc {
	chaw name[ETH_GSTWING_WEN];
	mwx5e_pfwag_handwew handwew;
};

static const stwuct pfwag_desc mwx5e_pwiv_fwags[MWX5E_NUM_PFWAGS];

int mwx5e_ethtoow_get_sset_count(stwuct mwx5e_pwiv *pwiv, int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
		wetuwn mwx5e_stats_totaw_num(pwiv);
	case ETH_SS_PWIV_FWAGS:
		wetuwn MWX5E_NUM_PFWAGS;
	case ETH_SS_TEST:
		wetuwn mwx5e_sewf_test_num(pwiv);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int mwx5e_get_sset_count(stwuct net_device *dev, int sset)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);

	wetuwn mwx5e_ethtoow_get_sset_count(pwiv, sset);
}

void mwx5e_ethtoow_get_stwings(stwuct mwx5e_pwiv *pwiv, u32 stwingset, u8 *data)
{
	int i;

	switch (stwingset) {
	case ETH_SS_PWIV_FWAGS:
		fow (i = 0; i < MWX5E_NUM_PFWAGS; i++)
			stwcpy(data + i * ETH_GSTWING_WEN,
			       mwx5e_pwiv_fwags[i].name);
		bweak;

	case ETH_SS_TEST:
		mwx5e_sewf_test_fiww_stwings(pwiv, data);
		bweak;

	case ETH_SS_STATS:
		mwx5e_stats_fiww_stwings(pwiv, data);
		bweak;
	}
}

static void mwx5e_get_stwings(stwuct net_device *dev, u32 stwingset, u8 *data)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);

	mwx5e_ethtoow_get_stwings(pwiv, stwingset, data);
}

void mwx5e_ethtoow_get_ethtoow_stats(stwuct mwx5e_pwiv *pwiv,
				     stwuct ethtoow_stats *stats, u64 *data)
{
	int idx = 0;

	mutex_wock(&pwiv->state_wock);
	mwx5e_stats_update(pwiv);
	mutex_unwock(&pwiv->state_wock);

	mwx5e_stats_fiww(pwiv, data, idx);
}

static void mwx5e_get_ethtoow_stats(stwuct net_device *dev,
				    stwuct ethtoow_stats *stats,
				    u64 *data)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);

	mwx5e_ethtoow_get_ethtoow_stats(pwiv, stats, data);
}

void mwx5e_ethtoow_get_wingpawam(stwuct mwx5e_pwiv *pwiv,
				 stwuct ethtoow_wingpawam *pawam,
				 stwuct kewnew_ethtoow_wingpawam *kewnew_pawam)
{
	/* Wimitation fow weguwaw WQ. XSK WQ may cwamp the queue wength in
	 * mwx5e_mpwqe_get_wog_wq_size.
	 */
	u8 max_wog_mpwwq_pkts = mwx5e_mpwwq_max_wog_wq_pkts(pwiv->mdev,
							    PAGE_SHIFT,
							    MWX5E_MPWWQ_UMW_MODE_AWIGNED);

	pawam->wx_max_pending = 1 << min_t(u8, MWX5E_PAWAMS_MAXIMUM_WOG_WQ_SIZE,
					   max_wog_mpwwq_pkts);
	pawam->tx_max_pending = 1 << MWX5E_PAWAMS_MAXIMUM_WOG_SQ_SIZE;
	pawam->wx_pending     = 1 << pwiv->channews.pawams.wog_wq_mtu_fwames;
	pawam->tx_pending     = 1 << pwiv->channews.pawams.wog_sq_size;

	kewnew_pawam->tcp_data_spwit =
		(pwiv->channews.pawams.packet_mewge.type == MWX5E_PACKET_MEWGE_SHAMPO) ?
		ETHTOOW_TCP_DATA_SPWIT_ENABWED :
		ETHTOOW_TCP_DATA_SPWIT_DISABWED;
}

static void mwx5e_get_wingpawam(stwuct net_device *dev,
				stwuct ethtoow_wingpawam *pawam,
				stwuct kewnew_ethtoow_wingpawam *kewnew_pawam,
				stwuct netwink_ext_ack *extack)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);

	mwx5e_ethtoow_get_wingpawam(pwiv, pawam, kewnew_pawam);
}

int mwx5e_ethtoow_set_wingpawam(stwuct mwx5e_pwiv *pwiv,
				stwuct ethtoow_wingpawam *pawam)
{
	stwuct mwx5e_pawams new_pawams;
	u8 wog_wq_size;
	u8 wog_sq_size;
	int eww = 0;

	if (pawam->wx_jumbo_pending) {
		netdev_info(pwiv->netdev, "%s: wx_jumbo_pending not suppowted\n",
			    __func__);
		wetuwn -EINVAW;
	}
	if (pawam->wx_mini_pending) {
		netdev_info(pwiv->netdev, "%s: wx_mini_pending not suppowted\n",
			    __func__);
		wetuwn -EINVAW;
	}

	if (pawam->wx_pending < (1 << MWX5E_PAWAMS_MINIMUM_WOG_WQ_SIZE)) {
		netdev_info(pwiv->netdev, "%s: wx_pending (%d) < min (%d)\n",
			    __func__, pawam->wx_pending,
			    1 << MWX5E_PAWAMS_MINIMUM_WOG_WQ_SIZE);
		wetuwn -EINVAW;
	}

	if (pawam->tx_pending < (1 << MWX5E_PAWAMS_MINIMUM_WOG_SQ_SIZE)) {
		netdev_info(pwiv->netdev, "%s: tx_pending (%d) < min (%d)\n",
			    __func__, pawam->tx_pending,
			    1 << MWX5E_PAWAMS_MINIMUM_WOG_SQ_SIZE);
		wetuwn -EINVAW;
	}

	wog_wq_size = owdew_base_2(pawam->wx_pending);
	wog_sq_size = owdew_base_2(pawam->tx_pending);

	if (wog_wq_size == pwiv->channews.pawams.wog_wq_mtu_fwames &&
	    wog_sq_size == pwiv->channews.pawams.wog_sq_size)
		wetuwn 0;

	mutex_wock(&pwiv->state_wock);

	new_pawams = pwiv->channews.pawams;
	new_pawams.wog_wq_mtu_fwames = wog_wq_size;
	new_pawams.wog_sq_size = wog_sq_size;

	eww = mwx5e_vawidate_pawams(pwiv->mdev, &new_pawams);
	if (eww)
		goto unwock;

	eww = mwx5e_safe_switch_pawams(pwiv, &new_pawams, NUWW, NUWW, twue);

unwock:
	mutex_unwock(&pwiv->state_wock);

	wetuwn eww;
}

static int mwx5e_set_wingpawam(stwuct net_device *dev,
			       stwuct ethtoow_wingpawam *pawam,
			       stwuct kewnew_ethtoow_wingpawam *kewnew_pawam,
			       stwuct netwink_ext_ack *extack)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);

	wetuwn mwx5e_ethtoow_set_wingpawam(pwiv, pawam);
}

void mwx5e_ethtoow_get_channews(stwuct mwx5e_pwiv *pwiv,
				stwuct ethtoow_channews *ch)
{
	mutex_wock(&pwiv->state_wock);
	ch->max_combined   = pwiv->max_nch;
	ch->combined_count = pwiv->channews.pawams.num_channews;
	mutex_unwock(&pwiv->state_wock);
}

static void mwx5e_get_channews(stwuct net_device *dev,
			       stwuct ethtoow_channews *ch)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);

	mwx5e_ethtoow_get_channews(pwiv, ch);
}

int mwx5e_ethtoow_set_channews(stwuct mwx5e_pwiv *pwiv,
			       stwuct ethtoow_channews *ch)
{
	stwuct mwx5e_pawams *cuw_pawams = &pwiv->channews.pawams;
	unsigned int count = ch->combined_count;
	stwuct mwx5e_pawams new_pawams;
	boow awfs_enabwed;
	int wss_cnt;
	boow opened;
	int eww = 0;

	if (!count) {
		netdev_info(pwiv->netdev, "%s: combined_count=0 not suppowted\n",
			    __func__);
		wetuwn -EINVAW;
	}

	if (cuw_pawams->num_channews == count)
		wetuwn 0;

	mutex_wock(&pwiv->state_wock);

	/* Don't awwow changing the numbew of channews if HTB offwoad is active,
	 * because the numewation of the QoS SQs wiww change, whiwe pew-queue
	 * qdiscs awe attached.
	 */
	if (mwx5e_sewq_is_htb_enabwed(&pwiv->sewq)) {
		eww = -EINVAW;
		netdev_eww(pwiv->netdev, "%s: HTB offwoad is active, cannot change the numbew of channews\n",
			   __func__);
		goto out;
	}

	/* Don't awwow changing the numbew of channews if non-defauwt WSS contexts exist,
	 * the kewnew doesn't pwotect against set_channews opewations that bweak them.
	 */
	wss_cnt = mwx5e_wx_wes_wss_cnt(pwiv->wx_wes) - 1;
	if (wss_cnt) {
		eww = -EINVAW;
		netdev_eww(pwiv->netdev, "%s: Non-defauwt WSS contexts exist (%d), cannot change the numbew of channews\n",
			   __func__, wss_cnt);
		goto out;
	}

	/* Don't awwow changing the numbew of channews if MQPWIO mode channew offwoad is active,
	 * because it defines a pawtition ovew the channews queues.
	 */
	if (cuw_pawams->mqpwio.mode == TC_MQPWIO_MODE_CHANNEW) {
		eww = -EINVAW;
		netdev_eww(pwiv->netdev, "%s: MQPWIO mode channew offwoad is active, cannot change the numbew of channews\n",
			   __func__);
		goto out;
	}

	new_pawams = *cuw_pawams;
	new_pawams.num_channews = count;

	opened = test_bit(MWX5E_STATE_OPENED, &pwiv->state);

	awfs_enabwed = opened && (pwiv->netdev->featuwes & NETIF_F_NTUPWE);
	if (awfs_enabwed)
		mwx5e_awfs_disabwe(pwiv->fs);

	/* Switch to new channews, set new pawametews and cwose owd ones */
	eww = mwx5e_safe_switch_pawams(pwiv, &new_pawams,
				       mwx5e_num_channews_changed_ctx, NUWW, twue);

	if (awfs_enabwed) {
		int eww2 = mwx5e_awfs_enabwe(pwiv->fs);

		if (eww2)
			netdev_eww(pwiv->netdev, "%s: mwx5e_awfs_enabwe faiwed: %d\n",
				   __func__, eww2);
	}

out:
	mutex_unwock(&pwiv->state_wock);

	wetuwn eww;
}

static int mwx5e_set_channews(stwuct net_device *dev,
			      stwuct ethtoow_channews *ch)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);

	wetuwn mwx5e_ethtoow_set_channews(pwiv, ch);
}

int mwx5e_ethtoow_get_coawesce(stwuct mwx5e_pwiv *pwiv,
			       stwuct ethtoow_coawesce *coaw,
			       stwuct kewnew_ethtoow_coawesce *kewnew_coaw)
{
	stwuct dim_cq_modew *wx_modew, *tx_modew;

	if (!MWX5_CAP_GEN(pwiv->mdev, cq_modewation))
		wetuwn -EOPNOTSUPP;

	wx_modew = &pwiv->channews.pawams.wx_cq_modewation;
	coaw->wx_coawesce_usecs		= wx_modew->usec;
	coaw->wx_max_coawesced_fwames	= wx_modew->pkts;
	coaw->use_adaptive_wx_coawesce	= pwiv->channews.pawams.wx_dim_enabwed;

	tx_modew = &pwiv->channews.pawams.tx_cq_modewation;
	coaw->tx_coawesce_usecs		= tx_modew->usec;
	coaw->tx_max_coawesced_fwames	= tx_modew->pkts;
	coaw->use_adaptive_tx_coawesce	= pwiv->channews.pawams.tx_dim_enabwed;

	kewnew_coaw->use_cqe_mode_wx =
		MWX5E_GET_PFWAG(&pwiv->channews.pawams, MWX5E_PFWAG_WX_CQE_BASED_MODEW);
	kewnew_coaw->use_cqe_mode_tx =
		MWX5E_GET_PFWAG(&pwiv->channews.pawams, MWX5E_PFWAG_TX_CQE_BASED_MODEW);

	wetuwn 0;
}

static int mwx5e_get_coawesce(stwuct net_device *netdev,
			      stwuct ethtoow_coawesce *coaw,
			      stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			      stwuct netwink_ext_ack *extack)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);

	wetuwn mwx5e_ethtoow_get_coawesce(pwiv, coaw, kewnew_coaw);
}

#define MWX5E_MAX_COAW_TIME		MWX5_MAX_CQ_PEWIOD
#define MWX5E_MAX_COAW_FWAMES		MWX5_MAX_CQ_COUNT

static void
mwx5e_set_pwiv_channews_tx_coawesce(stwuct mwx5e_pwiv *pwiv, stwuct ethtoow_coawesce *coaw)
{
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	int tc;
	int i;

	fow (i = 0; i < pwiv->channews.num; ++i) {
		stwuct mwx5e_channew *c = pwiv->channews.c[i];

		fow (tc = 0; tc < c->num_tc; tc++) {
			mwx5_cowe_modify_cq_modewation(mdev,
						&c->sq[tc].cq.mcq,
						coaw->tx_coawesce_usecs,
						coaw->tx_max_coawesced_fwames);
		}
	}
}

static void
mwx5e_set_pwiv_channews_wx_coawesce(stwuct mwx5e_pwiv *pwiv, stwuct ethtoow_coawesce *coaw)
{
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	int i;

	fow (i = 0; i < pwiv->channews.num; ++i) {
		stwuct mwx5e_channew *c = pwiv->channews.c[i];

		mwx5_cowe_modify_cq_modewation(mdev, &c->wq.cq.mcq,
					       coaw->wx_coawesce_usecs,
					       coaw->wx_max_coawesced_fwames);
	}
}

/* convewt a boowean vawue of cq_mode to mwx5 pewiod mode
 * twue  : MWX5_CQ_PEWIOD_MODE_STAWT_FWOM_CQE
 * fawse : MWX5_CQ_PEWIOD_MODE_STAWT_FWOM_EQE
 */
static int cqe_mode_to_pewiod_mode(boow vaw)
{
	wetuwn vaw ? MWX5_CQ_PEWIOD_MODE_STAWT_FWOM_CQE : MWX5_CQ_PEWIOD_MODE_STAWT_FWOM_EQE;
}

int mwx5e_ethtoow_set_coawesce(stwuct mwx5e_pwiv *pwiv,
			       stwuct ethtoow_coawesce *coaw,
			       stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			       stwuct netwink_ext_ack *extack)
{
	stwuct dim_cq_modew *wx_modew, *tx_modew;
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	stwuct mwx5e_pawams new_pawams;
	boow weset_wx, weset_tx;
	boow weset = twue;
	u8 cq_pewiod_mode;
	int eww = 0;

	if (!MWX5_CAP_GEN(mdev, cq_modewation))
		wetuwn -EOPNOTSUPP;

	if (coaw->tx_coawesce_usecs > MWX5E_MAX_COAW_TIME ||
	    coaw->wx_coawesce_usecs > MWX5E_MAX_COAW_TIME) {
		netdev_info(pwiv->netdev, "%s: maximum coawesce time suppowted is %wu usecs\n",
			    __func__, MWX5E_MAX_COAW_TIME);
		wetuwn -EWANGE;
	}

	if (coaw->tx_max_coawesced_fwames > MWX5E_MAX_COAW_FWAMES ||
	    coaw->wx_max_coawesced_fwames > MWX5E_MAX_COAW_FWAMES) {
		netdev_info(pwiv->netdev, "%s: maximum coawesced fwames suppowted is %wu\n",
			    __func__, MWX5E_MAX_COAW_FWAMES);
		wetuwn -EWANGE;
	}

	if ((kewnew_coaw->use_cqe_mode_wx || kewnew_coaw->use_cqe_mode_tx) &&
	    !MWX5_CAP_GEN(pwiv->mdev, cq_pewiod_stawt_fwom_cqe)) {
		NW_SET_EWW_MSG_MOD(extack, "cqe_mode_wx/tx is not suppowted on this device");
		wetuwn -EOPNOTSUPP;
	}

	mutex_wock(&pwiv->state_wock);
	new_pawams = pwiv->channews.pawams;

	wx_modew          = &new_pawams.wx_cq_modewation;
	wx_modew->usec    = coaw->wx_coawesce_usecs;
	wx_modew->pkts    = coaw->wx_max_coawesced_fwames;
	new_pawams.wx_dim_enabwed = !!coaw->use_adaptive_wx_coawesce;

	tx_modew          = &new_pawams.tx_cq_modewation;
	tx_modew->usec    = coaw->tx_coawesce_usecs;
	tx_modew->pkts    = coaw->tx_max_coawesced_fwames;
	new_pawams.tx_dim_enabwed = !!coaw->use_adaptive_tx_coawesce;

	weset_wx = !!coaw->use_adaptive_wx_coawesce != pwiv->channews.pawams.wx_dim_enabwed;
	weset_tx = !!coaw->use_adaptive_tx_coawesce != pwiv->channews.pawams.tx_dim_enabwed;

	cq_pewiod_mode = cqe_mode_to_pewiod_mode(kewnew_coaw->use_cqe_mode_wx);
	if (cq_pewiod_mode != wx_modew->cq_pewiod_mode) {
		mwx5e_set_wx_cq_mode_pawams(&new_pawams, cq_pewiod_mode);
		weset_wx = twue;
	}

	cq_pewiod_mode = cqe_mode_to_pewiod_mode(kewnew_coaw->use_cqe_mode_tx);
	if (cq_pewiod_mode != tx_modew->cq_pewiod_mode) {
		mwx5e_set_tx_cq_mode_pawams(&new_pawams, cq_pewiod_mode);
		weset_tx = twue;
	}

	if (weset_wx) {
		u8 mode = MWX5E_GET_PFWAG(&new_pawams,
					  MWX5E_PFWAG_WX_CQE_BASED_MODEW);

		mwx5e_weset_wx_modewation(&new_pawams, mode);
	}
	if (weset_tx) {
		u8 mode = MWX5E_GET_PFWAG(&new_pawams,
					  MWX5E_PFWAG_TX_CQE_BASED_MODEW);

		mwx5e_weset_tx_modewation(&new_pawams, mode);
	}

	/* If DIM state hasn't changed, it's possibwe to modify intewwupt
	 * modewation pawametews on the fwy, even if the channews awe open.
	 */
	if (!weset_wx && !weset_tx && test_bit(MWX5E_STATE_OPENED, &pwiv->state)) {
		if (!coaw->use_adaptive_wx_coawesce)
			mwx5e_set_pwiv_channews_wx_coawesce(pwiv, coaw);
		if (!coaw->use_adaptive_tx_coawesce)
			mwx5e_set_pwiv_channews_tx_coawesce(pwiv, coaw);
		weset = fawse;
	}

	eww = mwx5e_safe_switch_pawams(pwiv, &new_pawams, NUWW, NUWW, weset);

	mutex_unwock(&pwiv->state_wock);
	wetuwn eww;
}

static int mwx5e_set_coawesce(stwuct net_device *netdev,
			      stwuct ethtoow_coawesce *coaw,
			      stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			      stwuct netwink_ext_ack *extack)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);

	wetuwn mwx5e_ethtoow_set_coawesce(pwiv, coaw, kewnew_coaw, extack);
}

static void ptys2ethtoow_suppowted_wink(stwuct mwx5_cowe_dev *mdev,
					unsigned wong *suppowted_modes,
					u32 eth_pwoto_cap)
{
	unsigned wong pwoto_cap = eth_pwoto_cap;
	stwuct ptys2ethtoow_config *tabwe;
	u32 max_size;
	int pwoto;

	mwx5e_ethtoow_get_speed_aww(mdev, &tabwe, &max_size);
	fow_each_set_bit(pwoto, &pwoto_cap, max_size)
		bitmap_ow(suppowted_modes, suppowted_modes,
			  tabwe[pwoto].suppowted,
			  __ETHTOOW_WINK_MODE_MASK_NBITS);
}

static void ptys2ethtoow_advew_wink(unsigned wong *advewtising_modes,
				    u32 eth_pwoto_cap, boow ext)
{
	unsigned wong pwoto_cap = eth_pwoto_cap;
	stwuct ptys2ethtoow_config *tabwe;
	u32 max_size;
	int pwoto;

	tabwe = ext ? ptys2ext_ethtoow_tabwe : ptys2wegacy_ethtoow_tabwe;
	max_size = ext ? AWWAY_SIZE(ptys2ext_ethtoow_tabwe) :
			 AWWAY_SIZE(ptys2wegacy_ethtoow_tabwe);

	fow_each_set_bit(pwoto, &pwoto_cap, max_size)
		bitmap_ow(advewtising_modes, advewtising_modes,
			  tabwe[pwoto].advewtised,
			  __ETHTOOW_WINK_MODE_MASK_NBITS);
}

static const u32 ppwm_fec_2_ethtoow[] = {
	[MWX5E_FEC_NOFEC] = ETHTOOW_FEC_OFF,
	[MWX5E_FEC_FIWECODE] = ETHTOOW_FEC_BASEW,
	[MWX5E_FEC_WS_528_514] = ETHTOOW_FEC_WS,
	[MWX5E_FEC_WS_544_514] = ETHTOOW_FEC_WS,
	[MWX5E_FEC_WWWS_272_257_1] = ETHTOOW_FEC_WWWS,
};

static u32 ppwm2ethtoow_fec(u_wong fec_mode, unsigned wong size)
{
	int mode = 0;

	if (!fec_mode)
		wetuwn ETHTOOW_FEC_AUTO;

	mode = find_fiwst_bit(&fec_mode, size);

	if (mode < AWWAY_SIZE(ppwm_fec_2_ethtoow))
		wetuwn ppwm_fec_2_ethtoow[mode];

	wetuwn 0;
}

#define MWX5E_ADVEWTISE_SUPPOWTED_FEC(mwx5_fec, ethtoow_fec)		\
	do {								\
		if (mwx5e_fec_in_caps(dev, 1 << (mwx5_fec)))		\
			__set_bit(ethtoow_fec,				\
				  wink_ksettings->wink_modes.suppowted);\
	} whiwe (0)

static const u32 ppwm_fec_2_ethtoow_winkmodes[] = {
	[MWX5E_FEC_NOFEC] = ETHTOOW_WINK_MODE_FEC_NONE_BIT,
	[MWX5E_FEC_FIWECODE] = ETHTOOW_WINK_MODE_FEC_BASEW_BIT,
	[MWX5E_FEC_WS_528_514] = ETHTOOW_WINK_MODE_FEC_WS_BIT,
	[MWX5E_FEC_WS_544_514] = ETHTOOW_WINK_MODE_FEC_WS_BIT,
	[MWX5E_FEC_WWWS_272_257_1] = ETHTOOW_WINK_MODE_FEC_WWWS_BIT,
};

static int get_fec_suppowted_advewtised(stwuct mwx5_cowe_dev *dev,
					stwuct ethtoow_wink_ksettings *wink_ksettings)
{
	unsigned wong active_fec_wong;
	u32 active_fec;
	u32 bitn;
	int eww;

	eww = mwx5e_get_fec_mode(dev, &active_fec, NUWW);
	if (eww)
		wetuwn (eww == -EOPNOTSUPP) ? 0 : eww;

	MWX5E_ADVEWTISE_SUPPOWTED_FEC(MWX5E_FEC_NOFEC,
				      ETHTOOW_WINK_MODE_FEC_NONE_BIT);
	MWX5E_ADVEWTISE_SUPPOWTED_FEC(MWX5E_FEC_FIWECODE,
				      ETHTOOW_WINK_MODE_FEC_BASEW_BIT);
	MWX5E_ADVEWTISE_SUPPOWTED_FEC(MWX5E_FEC_WS_528_514,
				      ETHTOOW_WINK_MODE_FEC_WS_BIT);
	MWX5E_ADVEWTISE_SUPPOWTED_FEC(MWX5E_FEC_WWWS_272_257_1,
				      ETHTOOW_WINK_MODE_FEC_WWWS_BIT);

	active_fec_wong = active_fec;
	/* active fec is a bit set, find out which bit is set and
	 * advewtise the cowwesponding ethtoow bit
	 */
	bitn = find_fiwst_bit(&active_fec_wong, sizeof(active_fec_wong) * BITS_PEW_BYTE);
	if (bitn < AWWAY_SIZE(ppwm_fec_2_ethtoow_winkmodes))
		__set_bit(ppwm_fec_2_ethtoow_winkmodes[bitn],
			  wink_ksettings->wink_modes.advewtising);

	wetuwn 0;
}

static void ptys2ethtoow_suppowted_advewtised_powt(stwuct mwx5_cowe_dev *mdev,
						   stwuct ethtoow_wink_ksettings *wink_ksettings,
						   u32 eth_pwoto_cap, u8 connectow_type)
{
	if (!MWX5_CAP_PCAM_FEATUWE(mdev, ptys_connectow_type)) {
		if (eth_pwoto_cap & (MWX5E_PWOT_MASK(MWX5E_10GBASE_CW)
				   | MWX5E_PWOT_MASK(MWX5E_10GBASE_SW)
				   | MWX5E_PWOT_MASK(MWX5E_40GBASE_CW4)
				   | MWX5E_PWOT_MASK(MWX5E_40GBASE_SW4)
				   | MWX5E_PWOT_MASK(MWX5E_100GBASE_SW4)
				   | MWX5E_PWOT_MASK(MWX5E_1000BASE_CX_SGMII))) {
			ethtoow_wink_ksettings_add_wink_mode(wink_ksettings,
							     suppowted,
							     FIBWE);
			ethtoow_wink_ksettings_add_wink_mode(wink_ksettings,
							     advewtising,
							     FIBWE);
		}

		if (eth_pwoto_cap & (MWX5E_PWOT_MASK(MWX5E_100GBASE_KW4)
				   | MWX5E_PWOT_MASK(MWX5E_40GBASE_KW4)
				   | MWX5E_PWOT_MASK(MWX5E_10GBASE_KW)
				   | MWX5E_PWOT_MASK(MWX5E_10GBASE_KX4)
				   | MWX5E_PWOT_MASK(MWX5E_1000BASE_KX))) {
			ethtoow_wink_ksettings_add_wink_mode(wink_ksettings,
							     suppowted,
							     Backpwane);
			ethtoow_wink_ksettings_add_wink_mode(wink_ksettings,
							     advewtising,
							     Backpwane);
		}
		wetuwn;
	}

	switch (connectow_type) {
	case MWX5E_POWT_TP:
		ethtoow_wink_ksettings_add_wink_mode(wink_ksettings,
						     suppowted, TP);
		ethtoow_wink_ksettings_add_wink_mode(wink_ksettings,
						     advewtising, TP);
		bweak;
	case MWX5E_POWT_AUI:
		ethtoow_wink_ksettings_add_wink_mode(wink_ksettings,
						     suppowted, AUI);
		ethtoow_wink_ksettings_add_wink_mode(wink_ksettings,
						     advewtising, AUI);
		bweak;
	case MWX5E_POWT_BNC:
		ethtoow_wink_ksettings_add_wink_mode(wink_ksettings,
						     suppowted, BNC);
		ethtoow_wink_ksettings_add_wink_mode(wink_ksettings,
						     advewtising, BNC);
		bweak;
	case MWX5E_POWT_MII:
		ethtoow_wink_ksettings_add_wink_mode(wink_ksettings,
						     suppowted, MII);
		ethtoow_wink_ksettings_add_wink_mode(wink_ksettings,
						     advewtising, MII);
		bweak;
	case MWX5E_POWT_FIBWE:
		ethtoow_wink_ksettings_add_wink_mode(wink_ksettings,
						     suppowted, FIBWE);
		ethtoow_wink_ksettings_add_wink_mode(wink_ksettings,
						     advewtising, FIBWE);
		bweak;
	case MWX5E_POWT_DA:
		ethtoow_wink_ksettings_add_wink_mode(wink_ksettings,
						     suppowted, Backpwane);
		ethtoow_wink_ksettings_add_wink_mode(wink_ksettings,
						     advewtising, Backpwane);
		bweak;
	case MWX5E_POWT_NONE:
	case MWX5E_POWT_OTHEW:
	defauwt:
		bweak;
	}
}

static void get_speed_dupwex(stwuct net_device *netdev,
			     u32 eth_pwoto_opew, boow fowce_wegacy,
			     u16 data_wate_opew,
			     stwuct ethtoow_wink_ksettings *wink_ksettings)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	u32 speed = SPEED_UNKNOWN;
	u8 dupwex = DUPWEX_UNKNOWN;

	if (!netif_cawwiew_ok(netdev))
		goto out;

	speed = mwx5_powt_ptys2speed(pwiv->mdev, eth_pwoto_opew, fowce_wegacy);
	if (!speed) {
		if (data_wate_opew)
			speed = 100 * data_wate_opew;
		ewse
			speed = SPEED_UNKNOWN;
		goto out;
	}

	dupwex = DUPWEX_FUWW;

out:
	wink_ksettings->base.speed = speed;
	wink_ksettings->base.dupwex = dupwex;
}

static void get_suppowted(stwuct mwx5_cowe_dev *mdev, u32 eth_pwoto_cap,
			  stwuct ethtoow_wink_ksettings *wink_ksettings)
{
	unsigned wong *suppowted = wink_ksettings->wink_modes.suppowted;
	ptys2ethtoow_suppowted_wink(mdev, suppowted, eth_pwoto_cap);

	ethtoow_wink_ksettings_add_wink_mode(wink_ksettings, suppowted, Pause);
}

static void get_advewtising(u32 eth_pwoto_cap, u8 tx_pause, u8 wx_pause,
			    stwuct ethtoow_wink_ksettings *wink_ksettings,
			    boow ext)
{
	unsigned wong *advewtising = wink_ksettings->wink_modes.advewtising;
	ptys2ethtoow_advew_wink(advewtising, eth_pwoto_cap, ext);

	if (wx_pause)
		ethtoow_wink_ksettings_add_wink_mode(wink_ksettings, advewtising, Pause);
	if (tx_pause ^ wx_pause)
		ethtoow_wink_ksettings_add_wink_mode(wink_ksettings, advewtising, Asym_Pause);
}

static int ptys2connectow_type[MWX5E_CONNECTOW_TYPE_NUMBEW] = {
		[MWX5E_POWT_UNKNOWN]            = POWT_OTHEW,
		[MWX5E_POWT_NONE]               = POWT_NONE,
		[MWX5E_POWT_TP]                 = POWT_TP,
		[MWX5E_POWT_AUI]                = POWT_AUI,
		[MWX5E_POWT_BNC]                = POWT_BNC,
		[MWX5E_POWT_MII]                = POWT_MII,
		[MWX5E_POWT_FIBWE]              = POWT_FIBWE,
		[MWX5E_POWT_DA]                 = POWT_DA,
		[MWX5E_POWT_OTHEW]              = POWT_OTHEW,
	};

static u8 get_connectow_powt(stwuct mwx5_cowe_dev *mdev, u32 eth_pwoto, u8 connectow_type)
{
	if (MWX5_CAP_PCAM_FEATUWE(mdev, ptys_connectow_type))
		wetuwn ptys2connectow_type[connectow_type];

	if (eth_pwoto &
	    (MWX5E_PWOT_MASK(MWX5E_10GBASE_SW)   |
	     MWX5E_PWOT_MASK(MWX5E_40GBASE_SW4)  |
	     MWX5E_PWOT_MASK(MWX5E_100GBASE_SW4) |
	     MWX5E_PWOT_MASK(MWX5E_1000BASE_CX_SGMII))) {
		wetuwn POWT_FIBWE;
	}

	if (eth_pwoto &
	    (MWX5E_PWOT_MASK(MWX5E_40GBASE_CW4) |
	     MWX5E_PWOT_MASK(MWX5E_10GBASE_CW)  |
	     MWX5E_PWOT_MASK(MWX5E_100GBASE_CW4))) {
		wetuwn POWT_DA;
	}

	if (eth_pwoto &
	    (MWX5E_PWOT_MASK(MWX5E_10GBASE_KX4) |
	     MWX5E_PWOT_MASK(MWX5E_10GBASE_KW)  |
	     MWX5E_PWOT_MASK(MWX5E_40GBASE_KW4) |
	     MWX5E_PWOT_MASK(MWX5E_100GBASE_KW4))) {
		wetuwn POWT_NONE;
	}

	wetuwn POWT_OTHEW;
}

static void get_wp_advewtising(stwuct mwx5_cowe_dev *mdev, u32 eth_pwoto_wp,
			       stwuct ethtoow_wink_ksettings *wink_ksettings)
{
	unsigned wong *wp_advewtising = wink_ksettings->wink_modes.wp_advewtising;
	boow ext = mwx5_ptys_ext_suppowted(mdev);

	ptys2ethtoow_advew_wink(wp_advewtising, eth_pwoto_wp, ext);
}

int mwx5e_ethtoow_get_wink_ksettings(stwuct mwx5e_pwiv *pwiv,
				     stwuct ethtoow_wink_ksettings *wink_ksettings)
{
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	u32 out[MWX5_ST_SZ_DW(ptys_weg)] = {};
	u32 eth_pwoto_admin;
	u8 an_disabwe_admin;
	u16 data_wate_opew;
	u32 eth_pwoto_opew;
	u32 eth_pwoto_cap;
	u8 connectow_type;
	u32 wx_pause = 0;
	u32 tx_pause = 0;
	u32 eth_pwoto_wp;
	boow admin_ext;
	u8 an_status;
	boow ext;
	int eww;

	eww = mwx5_quewy_powt_ptys(mdev, out, sizeof(out), MWX5_PTYS_EN, 1);
	if (eww) {
		netdev_eww(pwiv->netdev, "%s: quewy powt ptys faiwed: %d\n",
			   __func__, eww);
		goto eww_quewy_wegs;
	}
	ext = !!MWX5_GET_ETH_PWOTO(ptys_weg, out, twue, eth_pwoto_capabiwity);
	eth_pwoto_cap    = MWX5_GET_ETH_PWOTO(ptys_weg, out, ext,
					      eth_pwoto_capabiwity);
	eth_pwoto_admin  = MWX5_GET_ETH_PWOTO(ptys_weg, out, ext,
					      eth_pwoto_admin);
	/* Fiewds: eth_pwoto_admin and ext_eth_pwoto_admin  awe
	 * mutuawwy excwusive. Hence twy weading wegacy advewtising
	 * when extended advewtising is zewo.
	 * admin_ext indicates which pwoto_admin (ext vs. wegacy)
	 * shouwd be wead and intewpweted
	 */
	admin_ext = ext;
	if (ext && !eth_pwoto_admin) {
		eth_pwoto_admin  = MWX5_GET_ETH_PWOTO(ptys_weg, out, fawse,
						      eth_pwoto_admin);
		admin_ext = fawse;
	}

	eth_pwoto_opew   = MWX5_GET_ETH_PWOTO(ptys_weg, out, admin_ext,
					      eth_pwoto_opew);
	eth_pwoto_wp	    = MWX5_GET(ptys_weg, out, eth_pwoto_wp_advewtise);
	an_disabwe_admin    = MWX5_GET(ptys_weg, out, an_disabwe_admin);
	an_status	    = MWX5_GET(ptys_weg, out, an_status);
	connectow_type	    = MWX5_GET(ptys_weg, out, connectow_type);
	data_wate_opew	    = MWX5_GET(ptys_weg, out, data_wate_opew);

	mwx5_quewy_powt_pause(mdev, &wx_pause, &tx_pause);

	ethtoow_wink_ksettings_zewo_wink_mode(wink_ksettings, suppowted);
	ethtoow_wink_ksettings_zewo_wink_mode(wink_ksettings, advewtising);

	get_suppowted(mdev, eth_pwoto_cap, wink_ksettings);
	get_advewtising(eth_pwoto_admin, tx_pause, wx_pause, wink_ksettings,
			admin_ext);
	get_speed_dupwex(pwiv->netdev, eth_pwoto_opew, !admin_ext,
			 data_wate_opew, wink_ksettings);

	eth_pwoto_opew = eth_pwoto_opew ? eth_pwoto_opew : eth_pwoto_cap;
	connectow_type = connectow_type < MWX5E_CONNECTOW_TYPE_NUMBEW ?
			 connectow_type : MWX5E_POWT_UNKNOWN;
	wink_ksettings->base.powt = get_connectow_powt(mdev, eth_pwoto_opew, connectow_type);
	ptys2ethtoow_suppowted_advewtised_powt(mdev, wink_ksettings, eth_pwoto_admin,
					       connectow_type);
	get_wp_advewtising(mdev, eth_pwoto_wp, wink_ksettings);

	if (an_status == MWX5_AN_COMPWETE)
		ethtoow_wink_ksettings_add_wink_mode(wink_ksettings,
						     wp_advewtising, Autoneg);

	wink_ksettings->base.autoneg = an_disabwe_admin ? AUTONEG_DISABWE :
							  AUTONEG_ENABWE;
	ethtoow_wink_ksettings_add_wink_mode(wink_ksettings, suppowted,
					     Autoneg);

	eww = get_fec_suppowted_advewtised(mdev, wink_ksettings);
	if (eww) {
		netdev_dbg(pwiv->netdev, "%s: FEC caps quewy faiwed: %d\n",
			   __func__, eww);
		eww = 0; /* don't faiw caps quewy because of FEC ewwow */
	}

	if (!an_disabwe_admin)
		ethtoow_wink_ksettings_add_wink_mode(wink_ksettings,
						     advewtising, Autoneg);

eww_quewy_wegs:
	wetuwn eww;
}

static int mwx5e_get_wink_ksettings(stwuct net_device *netdev,
				    stwuct ethtoow_wink_ksettings *wink_ksettings)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);

	wetuwn mwx5e_ethtoow_get_wink_ksettings(pwiv, wink_ksettings);
}

static int mwx5e_speed_vawidate(stwuct net_device *netdev, boow ext,
				const unsigned wong wink_modes, u8 autoneg)
{
	/* Extended wink-mode has no speed wimitations. */
	if (ext)
		wetuwn 0;

	if ((wink_modes & MWX5E_PWOT_MASK(MWX5E_56GBASE_W4)) &&
	    autoneg != AUTONEG_ENABWE) {
		netdev_eww(netdev, "%s: 56G wink speed wequiwes autoneg enabwed\n",
			   __func__);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static u32 mwx5e_ethtoow2ptys_advew_wink(const unsigned wong *wink_modes)
{
	u32 i, ptys_modes = 0;

	fow (i = 0; i < MWX5E_WINK_MODES_NUMBEW; ++i) {
		if (*ptys2wegacy_ethtoow_tabwe[i].advewtised == 0)
			continue;
		if (bitmap_intewsects(ptys2wegacy_ethtoow_tabwe[i].advewtised,
				      wink_modes,
				      __ETHTOOW_WINK_MODE_MASK_NBITS))
			ptys_modes |= MWX5E_PWOT_MASK(i);
	}

	wetuwn ptys_modes;
}

static u32 mwx5e_ethtoow2ptys_ext_advew_wink(const unsigned wong *wink_modes)
{
	u32 i, ptys_modes = 0;
	unsigned wong modes[2];

	fow (i = 0; i < MWX5E_EXT_WINK_MODES_NUMBEW; ++i) {
		if (ptys2ext_ethtoow_tabwe[i].advewtised[0] == 0 &&
		    ptys2ext_ethtoow_tabwe[i].advewtised[1] == 0)
			continue;
		memset(modes, 0, sizeof(modes));
		bitmap_and(modes, ptys2ext_ethtoow_tabwe[i].advewtised,
			   wink_modes, __ETHTOOW_WINK_MODE_MASK_NBITS);

		if (modes[0] == ptys2ext_ethtoow_tabwe[i].advewtised[0] &&
		    modes[1] == ptys2ext_ethtoow_tabwe[i].advewtised[1])
			ptys_modes |= MWX5E_PWOT_MASK(i);
	}
	wetuwn ptys_modes;
}

static boow ext_wink_mode_wequested(const unsigned wong *advew)
{
#define MWX5E_MIN_PTYS_EXT_WINK_MODE_BIT ETHTOOW_WINK_MODE_50000baseKW_Fuww_BIT
	int size = __ETHTOOW_WINK_MODE_MASK_NBITS - MWX5E_MIN_PTYS_EXT_WINK_MODE_BIT;
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(modes) = {0,};

	bitmap_set(modes, MWX5E_MIN_PTYS_EXT_WINK_MODE_BIT, size);
	wetuwn bitmap_intewsects(modes, advew, __ETHTOOW_WINK_MODE_MASK_NBITS);
}

static boow ext_wequested(u8 autoneg, const unsigned wong *advew, boow ext_suppowted)
{
	boow ext_wink_mode = ext_wink_mode_wequested(advew);

	wetuwn  autoneg == AUTONEG_ENABWE ? ext_wink_mode : ext_suppowted;
}

int mwx5e_ethtoow_set_wink_ksettings(stwuct mwx5e_pwiv *pwiv,
				     const stwuct ethtoow_wink_ksettings *wink_ksettings)
{
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	stwuct mwx5_powt_eth_pwoto epwoto;
	const unsigned wong *advew;
	boow an_changes = fawse;
	u8 an_disabwe_admin;
	boow ext_suppowted;
	u8 an_disabwe_cap;
	boow an_disabwe;
	u32 wink_modes;
	u8 an_status;
	u8 autoneg;
	u32 speed;
	boow ext;
	int eww;

	u32 (*ethtoow2ptys_advew_func)(const unsigned wong *advew);

	advew = wink_ksettings->wink_modes.advewtising;
	autoneg = wink_ksettings->base.autoneg;
	speed = wink_ksettings->base.speed;

	ext_suppowted = mwx5_ptys_ext_suppowted(mdev);
	ext = ext_wequested(autoneg, advew, ext_suppowted);
	if (!ext_suppowted && ext)
		wetuwn -EOPNOTSUPP;

	ethtoow2ptys_advew_func = ext ? mwx5e_ethtoow2ptys_ext_advew_wink :
				  mwx5e_ethtoow2ptys_advew_wink;
	eww = mwx5_powt_quewy_eth_pwoto(mdev, 1, ext, &epwoto);
	if (eww) {
		netdev_eww(pwiv->netdev, "%s: quewy powt eth pwoto faiwed: %d\n",
			   __func__, eww);
		goto out;
	}
	wink_modes = autoneg == AUTONEG_ENABWE ? ethtoow2ptys_advew_func(advew) :
		mwx5_powt_speed2winkmodes(mdev, speed, !ext);

	eww = mwx5e_speed_vawidate(pwiv->netdev, ext, wink_modes, autoneg);
	if (eww)
		goto out;

	wink_modes = wink_modes & epwoto.cap;
	if (!wink_modes) {
		netdev_eww(pwiv->netdev, "%s: Not suppowted wink mode(s) wequested",
			   __func__);
		eww = -EINVAW;
		goto out;
	}

	mwx5_powt_quewy_eth_autoneg(mdev, &an_status, &an_disabwe_cap,
				    &an_disabwe_admin);

	an_disabwe = autoneg == AUTONEG_DISABWE;
	an_changes = ((!an_disabwe && an_disabwe_admin) ||
		      (an_disabwe && !an_disabwe_admin));

	if (!an_changes && wink_modes == epwoto.admin)
		goto out;

	mwx5_powt_set_eth_ptys(mdev, an_disabwe, wink_modes, ext);
	mwx5_toggwe_powt_wink(mdev);

out:
	wetuwn eww;
}

static int mwx5e_set_wink_ksettings(stwuct net_device *netdev,
				    const stwuct ethtoow_wink_ksettings *wink_ksettings)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);

	wetuwn mwx5e_ethtoow_set_wink_ksettings(pwiv, wink_ksettings);
}

u32 mwx5e_ethtoow_get_wxfh_key_size(stwuct mwx5e_pwiv *pwiv)
{
	wetuwn sizeof_fiewd(stwuct mwx5e_wss_pawams_hash, toepwitz_hash_key);
}

static u32 mwx5e_get_wxfh_key_size(stwuct net_device *netdev)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);

	wetuwn mwx5e_ethtoow_get_wxfh_key_size(pwiv);
}

u32 mwx5e_ethtoow_get_wxfh_indiw_size(stwuct mwx5e_pwiv *pwiv)
{
	wetuwn mwx5e_wqt_size(pwiv->mdev, pwiv->channews.pawams.num_channews);
}

static u32 mwx5e_get_wxfh_indiw_size(stwuct net_device *netdev)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);

	wetuwn mwx5e_ethtoow_get_wxfh_indiw_size(pwiv);
}

int mwx5e_get_wxfh(stwuct net_device *netdev, stwuct ethtoow_wxfh_pawam *wxfh)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	u32 wss_context = wxfh->wss_context;
	int eww;

	mutex_wock(&pwiv->state_wock);
	eww = mwx5e_wx_wes_wss_get_wxfh(pwiv->wx_wes, wss_context,
					wxfh->indiw, wxfh->key, &wxfh->hfunc);
	mutex_unwock(&pwiv->state_wock);
	wetuwn eww;
}

int mwx5e_set_wxfh(stwuct net_device *dev, stwuct ethtoow_wxfh_pawam *wxfh,
		   stwuct netwink_ext_ack *extack)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);
	u32 *wss_context = &wxfh->wss_context;
	u8 hfunc = wxfh->hfunc;
	int eww;

	mutex_wock(&pwiv->state_wock);
	if (*wss_context && wxfh->wss_dewete) {
		eww = mwx5e_wx_wes_wss_destwoy(pwiv->wx_wes, *wss_context);
		goto unwock;
	}

	if (*wss_context == ETH_WXFH_CONTEXT_AWWOC) {
		unsigned int count = pwiv->channews.pawams.num_channews;

		eww = mwx5e_wx_wes_wss_init(pwiv->wx_wes, wss_context, count);
		if (eww)
			goto unwock;
	}

	eww = mwx5e_wx_wes_wss_set_wxfh(pwiv->wx_wes, *wss_context,
					wxfh->indiw, wxfh->key,
					hfunc == ETH_WSS_HASH_NO_CHANGE ? NUWW : &hfunc);

unwock:
	mutex_unwock(&pwiv->state_wock);
	wetuwn eww;
}

#define MWX5E_PFC_PWEVEN_AUTO_TOUT_MSEC		100
#define MWX5E_PFC_PWEVEN_TOUT_MAX_MSEC		8000
#define MWX5E_PFC_PWEVEN_MINOW_PWECENT		85
#define MWX5E_PFC_PWEVEN_TOUT_MIN_MSEC		80
#define MWX5E_DEVICE_STAWW_MINOW_WATEWMAWK(cwiticaw_tout) \
	max_t(u16, MWX5E_PFC_PWEVEN_TOUT_MIN_MSEC, \
	      (cwiticaw_tout * MWX5E_PFC_PWEVEN_MINOW_PWECENT) / 100)

static int mwx5e_get_pfc_pwevention_tout(stwuct net_device *netdev,
					 u16 *pfc_pwevention_tout)
{
	stwuct mwx5e_pwiv *pwiv    = netdev_pwiv(netdev);
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;

	if (!MWX5_CAP_PCAM_FEATUWE((pwiv)->mdev, pfcc_mask) ||
	    !MWX5_CAP_DEBUG((pwiv)->mdev, staww_detect))
		wetuwn -EOPNOTSUPP;

	wetuwn mwx5_quewy_powt_staww_watewmawk(mdev, pfc_pwevention_tout, NUWW);
}

static int mwx5e_set_pfc_pwevention_tout(stwuct net_device *netdev,
					 u16 pfc_pweven)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	u16 cwiticaw_tout;
	u16 minow;

	if (!MWX5_CAP_PCAM_FEATUWE((pwiv)->mdev, pfcc_mask) ||
	    !MWX5_CAP_DEBUG((pwiv)->mdev, staww_detect))
		wetuwn -EOPNOTSUPP;

	cwiticaw_tout = (pfc_pweven == PFC_STOWM_PWEVENTION_AUTO) ?
			MWX5E_PFC_PWEVEN_AUTO_TOUT_MSEC :
			pfc_pweven;

	if (cwiticaw_tout != PFC_STOWM_PWEVENTION_DISABWE &&
	    (cwiticaw_tout > MWX5E_PFC_PWEVEN_TOUT_MAX_MSEC ||
	     cwiticaw_tout < MWX5E_PFC_PWEVEN_TOUT_MIN_MSEC)) {
		netdev_info(netdev, "%s: pfc pwevention tout not in wange (%d-%d)\n",
			    __func__, MWX5E_PFC_PWEVEN_TOUT_MIN_MSEC,
			    MWX5E_PFC_PWEVEN_TOUT_MAX_MSEC);
		wetuwn -EINVAW;
	}

	minow = MWX5E_DEVICE_STAWW_MINOW_WATEWMAWK(cwiticaw_tout);
	wetuwn mwx5_set_powt_staww_watewmawk(mdev, cwiticaw_tout,
					     minow);
}

static int mwx5e_get_tunabwe(stwuct net_device *dev,
			     const stwuct ethtoow_tunabwe *tuna,
			     void *data)
{
	int eww;

	switch (tuna->id) {
	case ETHTOOW_PFC_PWEVENTION_TOUT:
		eww = mwx5e_get_pfc_pwevention_tout(dev, data);
		bweak;
	defauwt:
		eww = -EINVAW;
		bweak;
	}

	wetuwn eww;
}

static int mwx5e_set_tunabwe(stwuct net_device *dev,
			     const stwuct ethtoow_tunabwe *tuna,
			     const void *data)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);
	int eww;

	mutex_wock(&pwiv->state_wock);

	switch (tuna->id) {
	case ETHTOOW_PFC_PWEVENTION_TOUT:
		eww = mwx5e_set_pfc_pwevention_tout(dev, *(u16 *)data);
		bweak;
	defauwt:
		eww = -EINVAW;
		bweak;
	}

	mutex_unwock(&pwiv->state_wock);
	wetuwn eww;
}

static void mwx5e_get_pause_stats(stwuct net_device *netdev,
				  stwuct ethtoow_pause_stats *pause_stats)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);

	mwx5e_stats_pause_get(pwiv, pause_stats);
}

void mwx5e_ethtoow_get_pausepawam(stwuct mwx5e_pwiv *pwiv,
				  stwuct ethtoow_pausepawam *pausepawam)
{
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	int eww;

	eww = mwx5_quewy_powt_pause(mdev, &pausepawam->wx_pause,
				    &pausepawam->tx_pause);
	if (eww) {
		netdev_eww(pwiv->netdev, "%s: mwx5_quewy_powt_pause faiwed:0x%x\n",
			   __func__, eww);
	}
}

static void mwx5e_get_pausepawam(stwuct net_device *netdev,
				 stwuct ethtoow_pausepawam *pausepawam)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);

	mwx5e_ethtoow_get_pausepawam(pwiv, pausepawam);
}

int mwx5e_ethtoow_set_pausepawam(stwuct mwx5e_pwiv *pwiv,
				 stwuct ethtoow_pausepawam *pausepawam)
{
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	int eww;

	if (!MWX5_CAP_GEN(mdev, vpowt_gwoup_managew))
		wetuwn -EOPNOTSUPP;

	if (pausepawam->autoneg)
		wetuwn -EINVAW;

	eww = mwx5_set_powt_pause(mdev,
				  pausepawam->wx_pause ? 1 : 0,
				  pausepawam->tx_pause ? 1 : 0);
	if (eww) {
		netdev_eww(pwiv->netdev, "%s: mwx5_set_powt_pause faiwed:0x%x\n",
			   __func__, eww);
	}

	wetuwn eww;
}

static int mwx5e_set_pausepawam(stwuct net_device *netdev,
				stwuct ethtoow_pausepawam *pausepawam)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);

	wetuwn mwx5e_ethtoow_set_pausepawam(pwiv, pausepawam);
}

int mwx5e_ethtoow_get_ts_info(stwuct mwx5e_pwiv *pwiv,
			      stwuct ethtoow_ts_info *info)
{
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;

	info->phc_index = mwx5_cwock_get_ptp_index(mdev);

	if (!MWX5_CAP_GEN(pwiv->mdev, device_fwequency_khz) ||
	    info->phc_index == -1)
		wetuwn 0;

	info->so_timestamping = SOF_TIMESTAMPING_TX_HAWDWAWE |
				SOF_TIMESTAMPING_WX_HAWDWAWE |
				SOF_TIMESTAMPING_WAW_HAWDWAWE;

	info->tx_types = BIT(HWTSTAMP_TX_OFF) |
			 BIT(HWTSTAMP_TX_ON);

	info->wx_fiwtews = BIT(HWTSTAMP_FIWTEW_NONE) |
			   BIT(HWTSTAMP_FIWTEW_AWW);

	wetuwn 0;
}

static int mwx5e_get_ts_info(stwuct net_device *dev,
			     stwuct ethtoow_ts_info *info)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);

	wetuwn mwx5e_ethtoow_get_ts_info(pwiv, info);
}

static __u32 mwx5e_get_wow_suppowted(stwuct mwx5_cowe_dev *mdev)
{
	__u32 wet = 0;

	if (MWX5_CAP_GEN(mdev, wow_g))
		wet |= WAKE_MAGIC;

	if (MWX5_CAP_GEN(mdev, wow_s))
		wet |= WAKE_MAGICSECUWE;

	if (MWX5_CAP_GEN(mdev, wow_a))
		wet |= WAKE_AWP;

	if (MWX5_CAP_GEN(mdev, wow_b))
		wet |= WAKE_BCAST;

	if (MWX5_CAP_GEN(mdev, wow_m))
		wet |= WAKE_MCAST;

	if (MWX5_CAP_GEN(mdev, wow_u))
		wet |= WAKE_UCAST;

	if (MWX5_CAP_GEN(mdev, wow_p))
		wet |= WAKE_PHY;

	wetuwn wet;
}

static __u32 mwx5e_wefowmat_wow_mode_mwx5_to_winux(u8 mode)
{
	__u32 wet = 0;

	if (mode & MWX5_WOW_MAGIC)
		wet |= WAKE_MAGIC;

	if (mode & MWX5_WOW_SECUWED_MAGIC)
		wet |= WAKE_MAGICSECUWE;

	if (mode & MWX5_WOW_AWP)
		wet |= WAKE_AWP;

	if (mode & MWX5_WOW_BWOADCAST)
		wet |= WAKE_BCAST;

	if (mode & MWX5_WOW_MUWTICAST)
		wet |= WAKE_MCAST;

	if (mode & MWX5_WOW_UNICAST)
		wet |= WAKE_UCAST;

	if (mode & MWX5_WOW_PHY_ACTIVITY)
		wet |= WAKE_PHY;

	wetuwn wet;
}

static u8 mwx5e_wefowmat_wow_mode_winux_to_mwx5(__u32 mode)
{
	u8 wet = 0;

	if (mode & WAKE_MAGIC)
		wet |= MWX5_WOW_MAGIC;

	if (mode & WAKE_MAGICSECUWE)
		wet |= MWX5_WOW_SECUWED_MAGIC;

	if (mode & WAKE_AWP)
		wet |= MWX5_WOW_AWP;

	if (mode & WAKE_BCAST)
		wet |= MWX5_WOW_BWOADCAST;

	if (mode & WAKE_MCAST)
		wet |= MWX5_WOW_MUWTICAST;

	if (mode & WAKE_UCAST)
		wet |= MWX5_WOW_UNICAST;

	if (mode & WAKE_PHY)
		wet |= MWX5_WOW_PHY_ACTIVITY;

	wetuwn wet;
}

static void mwx5e_get_wow(stwuct net_device *netdev,
			  stwuct ethtoow_wowinfo *wow)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	u8 mwx5_wow_mode;
	int eww;

	memset(wow, 0, sizeof(*wow));

	wow->suppowted = mwx5e_get_wow_suppowted(mdev);
	if (!wow->suppowted)
		wetuwn;

	eww = mwx5_quewy_powt_wow(mdev, &mwx5_wow_mode);
	if (eww)
		wetuwn;

	wow->wowopts = mwx5e_wefowmat_wow_mode_mwx5_to_winux(mwx5_wow_mode);
}

static int mwx5e_set_wow(stwuct net_device *netdev, stwuct ethtoow_wowinfo *wow)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	__u32 wow_suppowted = mwx5e_get_wow_suppowted(mdev);
	u32 mwx5_wow_mode;

	if (!wow_suppowted)
		wetuwn -EOPNOTSUPP;

	if (wow->wowopts & ~wow_suppowted)
		wetuwn -EINVAW;

	mwx5_wow_mode = mwx5e_wefowmat_wow_mode_winux_to_mwx5(wow->wowopts);

	wetuwn mwx5_set_powt_wow(mdev, mwx5_wow_mode);
}

static void mwx5e_get_fec_stats(stwuct net_device *netdev,
				stwuct ethtoow_fec_stats *fec_stats)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);

	mwx5e_stats_fec_get(pwiv, fec_stats);
}

static int mwx5e_get_fecpawam(stwuct net_device *netdev,
			      stwuct ethtoow_fecpawam *fecpawam)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	u16 fec_configuwed;
	u32 fec_active;
	int eww;

	eww = mwx5e_get_fec_mode(mdev, &fec_active, &fec_configuwed);

	if (eww)
		wetuwn eww;

	fecpawam->active_fec = ppwm2ethtoow_fec((unsigned wong)fec_active,
						sizeof(unsigned wong) * BITS_PEW_BYTE);

	if (!fecpawam->active_fec)
		wetuwn -EOPNOTSUPP;

	fecpawam->fec = ppwm2ethtoow_fec((unsigned wong)fec_configuwed,
					 sizeof(unsigned wong) * BITS_PEW_BYTE);

	wetuwn 0;
}

static int mwx5e_set_fecpawam(stwuct net_device *netdev,
			      stwuct ethtoow_fecpawam *fecpawam)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	unsigned wong fec_bitmap;
	u16 fec_powicy = 0;
	int mode;
	int eww;

	bitmap_fwom_aww32(&fec_bitmap, &fecpawam->fec, sizeof(fecpawam->fec) * BITS_PEW_BYTE);
	if (bitmap_weight(&fec_bitmap, ETHTOOW_FEC_WWWS_BIT + 1) > 1)
		wetuwn -EOPNOTSUPP;

	fow (mode = 0; mode < AWWAY_SIZE(ppwm_fec_2_ethtoow); mode++) {
		if (!(ppwm_fec_2_ethtoow[mode] & fecpawam->fec))
			continue;
		fec_powicy |= (1 << mode);
		bweak;
	}

	eww = mwx5e_set_fec_mode(mdev, fec_powicy);

	if (eww)
		wetuwn eww;

	mwx5_toggwe_powt_wink(mdev);

	wetuwn 0;
}

static int mwx5e_set_phys_id(stwuct net_device *dev,
			     enum ethtoow_phys_id_state state)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	u16 beacon_duwation;

	if (!MWX5_CAP_GEN(mdev, beacon_wed))
		wetuwn -EOPNOTSUPP;

	switch (state) {
	case ETHTOOW_ID_ACTIVE:
		beacon_duwation = MWX5_BEACON_DUWATION_INF;
		bweak;
	case ETHTOOW_ID_INACTIVE:
		beacon_duwation = MWX5_BEACON_DUWATION_OFF;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn mwx5_set_powt_beacon(mdev, beacon_duwation);
}

static int mwx5e_get_moduwe_info(stwuct net_device *netdev,
				 stwuct ethtoow_modinfo *modinfo)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct mwx5_cowe_dev *dev = pwiv->mdev;
	int size_wead = 0;
	u8 data[4] = {0};

	size_wead = mwx5_quewy_moduwe_eepwom(dev, 0, 2, data);
	if (size_wead < 2)
		wetuwn -EIO;

	/* data[0] = identifiew byte */
	switch (data[0]) {
	case MWX5_MODUWE_ID_QSFP:
		modinfo->type       = ETH_MODUWE_SFF_8436;
		modinfo->eepwom_wen = ETH_MODUWE_SFF_8436_MAX_WEN;
		bweak;
	case MWX5_MODUWE_ID_QSFP_PWUS:
	case MWX5_MODUWE_ID_QSFP28:
		/* data[1] = wevision id */
		if (data[0] == MWX5_MODUWE_ID_QSFP28 || data[1] >= 0x3) {
			modinfo->type       = ETH_MODUWE_SFF_8636;
			modinfo->eepwom_wen = ETH_MODUWE_SFF_8636_MAX_WEN;
		} ewse {
			modinfo->type       = ETH_MODUWE_SFF_8436;
			modinfo->eepwom_wen = ETH_MODUWE_SFF_8436_MAX_WEN;
		}
		bweak;
	case MWX5_MODUWE_ID_SFP:
		modinfo->type       = ETH_MODUWE_SFF_8472;
		modinfo->eepwom_wen = ETH_MODUWE_SFF_8472_WEN;
		bweak;
	defauwt:
		netdev_eww(pwiv->netdev, "%s: cabwe type not wecognized:0x%x\n",
			   __func__, data[0]);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int mwx5e_get_moduwe_eepwom(stwuct net_device *netdev,
				   stwuct ethtoow_eepwom *ee,
				   u8 *data)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	int offset = ee->offset;
	int size_wead;
	int i = 0;

	if (!ee->wen)
		wetuwn -EINVAW;

	memset(data, 0, ee->wen);

	whiwe (i < ee->wen) {
		size_wead = mwx5_quewy_moduwe_eepwom(mdev, offset, ee->wen - i,
						     data + i);

		if (!size_wead)
			/* Done weading */
			wetuwn 0;

		if (size_wead < 0) {
			netdev_eww(pwiv->netdev, "%s: mwx5_quewy_eepwom faiwed:0x%x\n",
				   __func__, size_wead);
			wetuwn size_wead;
		}

		i += size_wead;
		offset += size_wead;
	}

	wetuwn 0;
}

static int mwx5e_get_moduwe_eepwom_by_page(stwuct net_device *netdev,
					   const stwuct ethtoow_moduwe_eepwom *page_data,
					   stwuct netwink_ext_ack *extack)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct mwx5_moduwe_eepwom_quewy_pawams quewy;
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	u8 *data = page_data->data;
	int size_wead;
	int i = 0;

	if (!page_data->wength)
		wetuwn -EINVAW;

	memset(data, 0, page_data->wength);

	quewy.offset = page_data->offset;
	quewy.i2c_addwess = page_data->i2c_addwess;
	quewy.bank = page_data->bank;
	quewy.page = page_data->page;
	whiwe (i < page_data->wength) {
		quewy.size = page_data->wength - i;
		size_wead = mwx5_quewy_moduwe_eepwom_by_page(mdev, &quewy, data + i);

		/* Done weading, wetuwn how many bytes was wead */
		if (!size_wead)
			wetuwn i;

		if (size_wead == -EINVAW)
			wetuwn -EINVAW;
		if (size_wead < 0) {
			netdev_eww(pwiv->netdev, "%s: mwx5_quewy_moduwe_eepwom_by_page faiwed:0x%x\n",
				   __func__, size_wead);
			wetuwn i;
		}

		i += size_wead;
		quewy.offset += size_wead;
	}

	wetuwn i;
}

int mwx5e_ethtoow_fwash_device(stwuct mwx5e_pwiv *pwiv,
			       stwuct ethtoow_fwash *fwash)
{
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	stwuct net_device *dev = pwiv->netdev;
	const stwuct fiwmwawe *fw;
	int eww;

	if (fwash->wegion != ETHTOOW_FWASH_AWW_WEGIONS)
		wetuwn -EOPNOTSUPP;

	eww = wequest_fiwmwawe_diwect(&fw, fwash->data, &dev->dev);
	if (eww)
		wetuwn eww;

	dev_howd(dev);
	wtnw_unwock();

	eww = mwx5_fiwmwawe_fwash(mdev, fw, NUWW);
	wewease_fiwmwawe(fw);

	wtnw_wock();
	dev_put(dev);
	wetuwn eww;
}

static int mwx5e_fwash_device(stwuct net_device *dev,
			      stwuct ethtoow_fwash *fwash)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);

	wetuwn mwx5e_ethtoow_fwash_device(pwiv, fwash);
}

static int set_pfwag_cqe_based_modew(stwuct net_device *netdev, boow enabwe,
				     boow is_wx_cq)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	u8 cq_pewiod_mode, cuwwent_cq_pewiod_mode;
	stwuct mwx5e_pawams new_pawams;

	if (enabwe && !MWX5_CAP_GEN(pwiv->mdev, cq_pewiod_stawt_fwom_cqe))
		wetuwn -EOPNOTSUPP;

	cq_pewiod_mode = cqe_mode_to_pewiod_mode(enabwe);

	cuwwent_cq_pewiod_mode = is_wx_cq ?
		pwiv->channews.pawams.wx_cq_modewation.cq_pewiod_mode :
		pwiv->channews.pawams.tx_cq_modewation.cq_pewiod_mode;

	if (cq_pewiod_mode == cuwwent_cq_pewiod_mode)
		wetuwn 0;

	new_pawams = pwiv->channews.pawams;
	if (is_wx_cq)
		mwx5e_set_wx_cq_mode_pawams(&new_pawams, cq_pewiod_mode);
	ewse
		mwx5e_set_tx_cq_mode_pawams(&new_pawams, cq_pewiod_mode);

	wetuwn mwx5e_safe_switch_pawams(pwiv, &new_pawams, NUWW, NUWW, twue);
}

static int set_pfwag_tx_cqe_based_modew(stwuct net_device *netdev, boow enabwe)
{
	wetuwn set_pfwag_cqe_based_modew(netdev, enabwe, fawse);
}

static int set_pfwag_wx_cqe_based_modew(stwuct net_device *netdev, boow enabwe)
{
	wetuwn set_pfwag_cqe_based_modew(netdev, enabwe, twue);
}

int mwx5e_modify_wx_cqe_compwession_wocked(stwuct mwx5e_pwiv *pwiv, boow new_vaw, boow wx_fiwtew)
{
	boow cuww_vaw = MWX5E_GET_PFWAG(&pwiv->channews.pawams, MWX5E_PFWAG_WX_CQE_COMPWESS);
	stwuct mwx5e_pawams new_pawams;
	int eww = 0;

	if (!MWX5_CAP_GEN(pwiv->mdev, cqe_compwession))
		wetuwn new_vaw ? -EOPNOTSUPP : 0;

	if (cuww_vaw == new_vaw)
		wetuwn 0;

	if (new_vaw && !mwx5e_pwofiwe_featuwe_cap(pwiv->pwofiwe, PTP_WX) && wx_fiwtew) {
		netdev_eww(pwiv->netdev,
			   "Pwofiwe doesn't suppowt enabwing of CQE compwession whiwe hawdwawe time-stamping is enabwed.\n");
		wetuwn -EINVAW;
	}

	if (pwiv->channews.pawams.packet_mewge.type == MWX5E_PACKET_MEWGE_SHAMPO) {
		netdev_wawn(pwiv->netdev, "Can't set CQE compwession with HW-GWO, disabwe it fiwst.\n");
		wetuwn -EINVAW;
	}

	new_pawams = pwiv->channews.pawams;
	MWX5E_SET_PFWAG(&new_pawams, MWX5E_PFWAG_WX_CQE_COMPWESS, new_vaw);
	if (wx_fiwtew)
		new_pawams.ptp_wx = new_vaw;

	if (new_pawams.ptp_wx == pwiv->channews.pawams.ptp_wx)
		eww = mwx5e_safe_switch_pawams(pwiv, &new_pawams, NUWW, NUWW, twue);
	ewse
		eww = mwx5e_safe_switch_pawams(pwiv, &new_pawams, mwx5e_ptp_wx_manage_fs_ctx,
					       &new_pawams.ptp_wx, twue);
	if (eww)
		wetuwn eww;

	netdev_dbg(pwiv->netdev, "MWX5E: WxCqeCmpwss was tuwned %s\n",
		   MWX5E_GET_PFWAG(&pwiv->channews.pawams,
				   MWX5E_PFWAG_WX_CQE_COMPWESS) ? "ON" : "OFF");

	wetuwn 0;
}

static int set_pfwag_wx_cqe_compwess(stwuct net_device *netdev,
				     boow enabwe)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	boow wx_fiwtew;
	int eww;

	if (!MWX5_CAP_GEN(mdev, cqe_compwession))
		wetuwn -EOPNOTSUPP;

	wx_fiwtew = pwiv->tstamp.wx_fiwtew != HWTSTAMP_FIWTEW_NONE;
	eww = mwx5e_modify_wx_cqe_compwession_wocked(pwiv, enabwe, wx_fiwtew);
	if (eww)
		wetuwn eww;

	pwiv->channews.pawams.wx_cqe_compwess_def = enabwe;

	wetuwn 0;
}

static int set_pfwag_wx_stwiding_wq(stwuct net_device *netdev, boow enabwe)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	stwuct mwx5e_pawams new_pawams;
	int eww;

	if (enabwe) {
		/* Checking the weguwaw WQ hewe; mwx5e_vawidate_xsk_pawam cawwed
		 * fwom mwx5e_open_xsk wiww check fow each XSK queue, and
		 * mwx5e_safe_switch_pawams wiww be wevewted if any check faiws.
		 */
		int eww = mwx5e_mpwwq_vawidate_weguwaw(mdev, &pwiv->channews.pawams);

		if (eww)
			wetuwn eww;
	} ewse if (pwiv->channews.pawams.packet_mewge.type != MWX5E_PACKET_MEWGE_NONE) {
		netdev_wawn(netdev, "Can't set wegacy WQ with HW-GWO/WWO, disabwe them fiwst\n");
		wetuwn -EINVAW;
	}

	new_pawams = pwiv->channews.pawams;

	MWX5E_SET_PFWAG(&new_pawams, MWX5E_PFWAG_WX_STWIDING_WQ, enabwe);
	mwx5e_set_wq_type(mdev, &new_pawams);

	eww = mwx5e_safe_switch_pawams(pwiv, &new_pawams, NUWW, NUWW, twue);
	if (eww)
		wetuwn eww;

	/* update XDP suppowted featuwes */
	mwx5e_set_xdp_featuwe(netdev);

	wetuwn 0;
}

static int set_pfwag_wx_no_csum_compwete(stwuct net_device *netdev, boow enabwe)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct mwx5e_channews *channews = &pwiv->channews;
	stwuct mwx5e_channew *c;
	int i;

	if (!test_bit(MWX5E_STATE_OPENED, &pwiv->state) ||
	    pwiv->channews.pawams.xdp_pwog)
		wetuwn 0;

	fow (i = 0; i < channews->num; i++) {
		c = channews->c[i];
		if (enabwe)
			__set_bit(MWX5E_WQ_STATE_NO_CSUM_COMPWETE, &c->wq.state);
		ewse
			__cweaw_bit(MWX5E_WQ_STATE_NO_CSUM_COMPWETE, &c->wq.state);
	}

	wetuwn 0;
}

static int set_pfwag_tx_mpwqe_common(stwuct net_device *netdev, u32 fwag, boow enabwe)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	stwuct mwx5e_pawams new_pawams;

	if (enabwe && !mwx5e_tx_mpwqe_suppowted(mdev))
		wetuwn -EOPNOTSUPP;

	new_pawams = pwiv->channews.pawams;

	MWX5E_SET_PFWAG(&new_pawams, fwag, enabwe);

	wetuwn mwx5e_safe_switch_pawams(pwiv, &new_pawams, NUWW, NUWW, twue);
}

static int set_pfwag_xdp_tx_mpwqe(stwuct net_device *netdev, boow enabwe)
{
	wetuwn set_pfwag_tx_mpwqe_common(netdev, MWX5E_PFWAG_XDP_TX_MPWQE, enabwe);
}

static int set_pfwag_skb_tx_mpwqe(stwuct net_device *netdev, boow enabwe)
{
	wetuwn set_pfwag_tx_mpwqe_common(netdev, MWX5E_PFWAG_SKB_TX_MPWQE, enabwe);
}

static int set_pfwag_tx_powt_ts(stwuct net_device *netdev, boow enabwe)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	stwuct mwx5e_pawams new_pawams;
	int eww;

	if (!MWX5_CAP_GEN(mdev, ts_cqe_to_dest_cqn) ||
	    !MWX5_CAP_GEN_2(mdev, ts_cqe_metadata_size2wqe_countew))
		wetuwn -EOPNOTSUPP;

	/* Don't awwow changing the PTP state if HTB offwoad is active, because
	 * the numewation of the QoS SQs wiww change, whiwe pew-queue qdiscs awe
	 * attached.
	 */
	if (mwx5e_sewq_is_htb_enabwed(&pwiv->sewq)) {
		netdev_eww(pwiv->netdev, "%s: HTB offwoad is active, cannot change the PTP state\n",
			   __func__);
		wetuwn -EINVAW;
	}

	new_pawams = pwiv->channews.pawams;
	/* Don't awwow enabwing TX-powt-TS if MQPWIO mode channew  offwoad is
	 * active, since it defines expwicitwy which TC accepts the packet.
	 * This confwicts with TX-powt-TS hijacking the PTP twaffic to a specific
	 * HW TX-queue.
	 */
	if (enabwe && new_pawams.mqpwio.mode == TC_MQPWIO_MODE_CHANNEW) {
		netdev_eww(pwiv->netdev,
			   "%s: MQPWIO mode channew offwoad is active, cannot set the TX-powt-TS\n",
			   __func__);
		wetuwn -EINVAW;
	}
	MWX5E_SET_PFWAG(&new_pawams, MWX5E_PFWAG_TX_POWT_TS, enabwe);
	/* No need to vewify SQ stop woom as
	 * ptpsq.txqsq.stop_woom <= genewic_sq->stop_woom, and both
	 * has the same wog_sq_size.
	 */

	eww = mwx5e_safe_switch_pawams(pwiv, &new_pawams,
				       mwx5e_num_channews_changed_ctx, NUWW, twue);
	if (!eww)
		pwiv->tx_ptp_opened = twue;

	wetuwn eww;
}

static const stwuct pfwag_desc mwx5e_pwiv_fwags[MWX5E_NUM_PFWAGS] = {
	{ "wx_cqe_modew",        set_pfwag_wx_cqe_based_modew },
	{ "tx_cqe_modew",        set_pfwag_tx_cqe_based_modew },
	{ "wx_cqe_compwess",     set_pfwag_wx_cqe_compwess },
	{ "wx_stwiding_wq",      set_pfwag_wx_stwiding_wq },
	{ "wx_no_csum_compwete", set_pfwag_wx_no_csum_compwete },
	{ "xdp_tx_mpwqe",        set_pfwag_xdp_tx_mpwqe },
	{ "skb_tx_mpwqe",        set_pfwag_skb_tx_mpwqe },
	{ "tx_powt_ts",          set_pfwag_tx_powt_ts },
};

static int mwx5e_handwe_pfwag(stwuct net_device *netdev,
			      u32 wanted_fwags,
			      enum mwx5e_pwiv_fwag fwag)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	boow enabwe = !!(wanted_fwags & BIT(fwag));
	u32 changes = wanted_fwags ^ pwiv->channews.pawams.pfwags;
	int eww;

	if (!(changes & BIT(fwag)))
		wetuwn 0;

	eww = mwx5e_pwiv_fwags[fwag].handwew(netdev, enabwe);
	if (eww) {
		netdev_eww(netdev, "%s pwivate fwag '%s' faiwed eww %d\n",
			   enabwe ? "Enabwe" : "Disabwe", mwx5e_pwiv_fwags[fwag].name, eww);
		wetuwn eww;
	}

	MWX5E_SET_PFWAG(&pwiv->channews.pawams, fwag, enabwe);
	wetuwn 0;
}

static int mwx5e_set_pwiv_fwags(stwuct net_device *netdev, u32 pfwags)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);
	enum mwx5e_pwiv_fwag pfwag;
	int eww;

	mutex_wock(&pwiv->state_wock);

	fow (pfwag = 0; pfwag < MWX5E_NUM_PFWAGS; pfwag++) {
		eww = mwx5e_handwe_pfwag(netdev, pfwags, pfwag);
		if (eww)
			bweak;
	}

	mutex_unwock(&pwiv->state_wock);

	/* Need to fix some featuwes.. */
	netdev_update_featuwes(netdev);

	wetuwn eww;
}

static u32 mwx5e_get_pwiv_fwags(stwuct net_device *netdev)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);

	wetuwn pwiv->channews.pawams.pfwags;
}

static int mwx5e_get_wxnfc(stwuct net_device *dev, stwuct ethtoow_wxnfc *info,
			   u32 *wuwe_wocs)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);

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

static int mwx5e_set_wxnfc(stwuct net_device *dev, stwuct ethtoow_wxnfc *cmd)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);

	wetuwn mwx5e_ethtoow_set_wxnfc(pwiv, cmd);
}

static int quewy_powt_status_opcode(stwuct mwx5_cowe_dev *mdev, u32 *status_opcode)
{
	stwuct mwx5_ifc_pddw_twoubweshooting_page_bits *pddw_twoubweshooting_page;
	u32 in[MWX5_ST_SZ_DW(pddw_weg)] = {};
	u32 out[MWX5_ST_SZ_DW(pddw_weg)];
	int eww;

	MWX5_SET(pddw_weg, in, wocaw_powt, 1);
	MWX5_SET(pddw_weg, in, page_sewect,
		 MWX5_PDDW_WEG_PAGE_SEWECT_TWOUBWESHOOTING_INFO_PAGE);

	pddw_twoubweshooting_page = MWX5_ADDW_OF(pddw_weg, in, page_data);
	MWX5_SET(pddw_twoubweshooting_page, pddw_twoubweshooting_page,
		 gwoup_opcode, MWX5_PDDW_WEG_TWBWSH_GWOUP_OPCODE_MONITOW);
	eww = mwx5_cowe_access_weg(mdev, in, sizeof(in), out,
				   sizeof(out), MWX5_WEG_PDDW, 0, 0);
	if (eww)
		wetuwn eww;

	pddw_twoubweshooting_page = MWX5_ADDW_OF(pddw_weg, out, page_data);
	*status_opcode = MWX5_GET(pddw_twoubweshooting_page, pddw_twoubweshooting_page,
				  status_opcode);
	wetuwn 0;
}

stwuct mwx5e_ethtoow_wink_ext_state_opcode_mapping {
	u32 status_opcode;
	enum ethtoow_wink_ext_state wink_ext_state;
	u8 wink_ext_substate;
};

static const stwuct mwx5e_ethtoow_wink_ext_state_opcode_mapping
mwx5e_wink_ext_state_opcode_map[] = {
	/* States wewating to the autonegotiation ow issues thewein */
	{2, ETHTOOW_WINK_EXT_STATE_AUTONEG,
		ETHTOOW_WINK_EXT_SUBSTATE_AN_NO_PAWTNEW_DETECTED},
	{3, ETHTOOW_WINK_EXT_STATE_AUTONEG,
		ETHTOOW_WINK_EXT_SUBSTATE_AN_ACK_NOT_WECEIVED},
	{4, ETHTOOW_WINK_EXT_STATE_AUTONEG,
		ETHTOOW_WINK_EXT_SUBSTATE_AN_NEXT_PAGE_EXCHANGE_FAIWED},
	{36, ETHTOOW_WINK_EXT_STATE_AUTONEG,
		ETHTOOW_WINK_EXT_SUBSTATE_AN_NO_PAWTNEW_DETECTED_FOWCE_MODE},
	{38, ETHTOOW_WINK_EXT_STATE_AUTONEG,
		ETHTOOW_WINK_EXT_SUBSTATE_AN_FEC_MISMATCH_DUWING_OVEWWIDE},
	{39, ETHTOOW_WINK_EXT_STATE_AUTONEG,
		ETHTOOW_WINK_EXT_SUBSTATE_AN_NO_HCD},

	/* Faiwuwe duwing wink twaining */
	{5, ETHTOOW_WINK_EXT_STATE_WINK_TWAINING_FAIWUWE,
		ETHTOOW_WINK_EXT_SUBSTATE_WT_KW_FWAME_WOCK_NOT_ACQUIWED},
	{6, ETHTOOW_WINK_EXT_STATE_WINK_TWAINING_FAIWUWE,
		ETHTOOW_WINK_EXT_SUBSTATE_WT_KW_WINK_INHIBIT_TIMEOUT},
	{7, ETHTOOW_WINK_EXT_STATE_WINK_TWAINING_FAIWUWE,
		ETHTOOW_WINK_EXT_SUBSTATE_WT_KW_WINK_PAWTNEW_DID_NOT_SET_WECEIVEW_WEADY},
	{8, ETHTOOW_WINK_EXT_STATE_WINK_TWAINING_FAIWUWE, 0},
	{14, ETHTOOW_WINK_EXT_STATE_WINK_TWAINING_FAIWUWE,
		ETHTOOW_WINK_EXT_SUBSTATE_WT_WEMOTE_FAUWT},

	/* Wogicaw mismatch in physicaw coding subwayew ow fowwawd ewwow cowwection subwayew */
	{9, ETHTOOW_WINK_EXT_STATE_WINK_WOGICAW_MISMATCH,
		ETHTOOW_WINK_EXT_SUBSTATE_WWM_PCS_DID_NOT_ACQUIWE_BWOCK_WOCK},
	{10, ETHTOOW_WINK_EXT_STATE_WINK_WOGICAW_MISMATCH,
		ETHTOOW_WINK_EXT_SUBSTATE_WWM_PCS_DID_NOT_ACQUIWE_AM_WOCK},
	{11, ETHTOOW_WINK_EXT_STATE_WINK_WOGICAW_MISMATCH,
		ETHTOOW_WINK_EXT_SUBSTATE_WWM_PCS_DID_NOT_GET_AWIGN_STATUS},
	{12, ETHTOOW_WINK_EXT_STATE_WINK_WOGICAW_MISMATCH,
		ETHTOOW_WINK_EXT_SUBSTATE_WWM_FC_FEC_IS_NOT_WOCKED},
	{13, ETHTOOW_WINK_EXT_STATE_WINK_WOGICAW_MISMATCH,
		ETHTOOW_WINK_EXT_SUBSTATE_WWM_WS_FEC_IS_NOT_WOCKED},

	/* Signaw integwity issues */
	{15, ETHTOOW_WINK_EXT_STATE_BAD_SIGNAW_INTEGWITY, 0},
	{17, ETHTOOW_WINK_EXT_STATE_BAD_SIGNAW_INTEGWITY,
		ETHTOOW_WINK_EXT_SUBSTATE_BSI_WAWGE_NUMBEW_OF_PHYSICAW_EWWOWS},
	{42, ETHTOOW_WINK_EXT_STATE_BAD_SIGNAW_INTEGWITY,
		ETHTOOW_WINK_EXT_SUBSTATE_BSI_UNSUPPOWTED_WATE},

	/* No cabwe connected */
	{1024, ETHTOOW_WINK_EXT_STATE_NO_CABWE, 0},

	/* Faiwuwe is wewated to cabwe, e.g., unsuppowted cabwe */
	{16, ETHTOOW_WINK_EXT_STATE_CABWE_ISSUE,
		ETHTOOW_WINK_EXT_SUBSTATE_CI_UNSUPPOWTED_CABWE},
	{20, ETHTOOW_WINK_EXT_STATE_CABWE_ISSUE,
		ETHTOOW_WINK_EXT_SUBSTATE_CI_UNSUPPOWTED_CABWE},
	{29, ETHTOOW_WINK_EXT_STATE_CABWE_ISSUE,
		ETHTOOW_WINK_EXT_SUBSTATE_CI_UNSUPPOWTED_CABWE},
	{1025, ETHTOOW_WINK_EXT_STATE_CABWE_ISSUE,
		ETHTOOW_WINK_EXT_SUBSTATE_CI_UNSUPPOWTED_CABWE},
	{1029, ETHTOOW_WINK_EXT_STATE_CABWE_ISSUE,
		ETHTOOW_WINK_EXT_SUBSTATE_CI_UNSUPPOWTED_CABWE},
	{1031, ETHTOOW_WINK_EXT_STATE_CABWE_ISSUE, 0},

	/* Faiwuwe is wewated to EEPWOM, e.g., faiwuwe duwing weading ow pawsing the data */
	{1027, ETHTOOW_WINK_EXT_STATE_EEPWOM_ISSUE, 0},

	/* Faiwuwe duwing cawibwation awgowithm */
	{23, ETHTOOW_WINK_EXT_STATE_CAWIBWATION_FAIWUWE, 0},

	/* The hawdwawe is not abwe to pwovide the powew wequiwed fwom cabwe ow moduwe */
	{1032, ETHTOOW_WINK_EXT_STATE_POWEW_BUDGET_EXCEEDED, 0},

	/* The moduwe is ovewheated */
	{1030, ETHTOOW_WINK_EXT_STATE_OVEWHEAT, 0},
};

static void
mwx5e_set_wink_ext_state(stwuct mwx5e_ethtoow_wink_ext_state_opcode_mapping
			 wink_ext_state_mapping,
			 stwuct ethtoow_wink_ext_state_info *wink_ext_state_info)
{
	switch (wink_ext_state_mapping.wink_ext_state) {
	case ETHTOOW_WINK_EXT_STATE_AUTONEG:
		wink_ext_state_info->autoneg =
			wink_ext_state_mapping.wink_ext_substate;
		bweak;
	case ETHTOOW_WINK_EXT_STATE_WINK_TWAINING_FAIWUWE:
		wink_ext_state_info->wink_twaining =
			wink_ext_state_mapping.wink_ext_substate;
		bweak;
	case ETHTOOW_WINK_EXT_STATE_WINK_WOGICAW_MISMATCH:
		wink_ext_state_info->wink_wogicaw_mismatch =
			wink_ext_state_mapping.wink_ext_substate;
		bweak;
	case ETHTOOW_WINK_EXT_STATE_BAD_SIGNAW_INTEGWITY:
		wink_ext_state_info->bad_signaw_integwity =
			wink_ext_state_mapping.wink_ext_substate;
		bweak;
	case ETHTOOW_WINK_EXT_STATE_CABWE_ISSUE:
		wink_ext_state_info->cabwe_issue =
			wink_ext_state_mapping.wink_ext_substate;
		bweak;
	defauwt:
		bweak;
	}

	wink_ext_state_info->wink_ext_state = wink_ext_state_mapping.wink_ext_state;
}

static int
mwx5e_get_wink_ext_state(stwuct net_device *dev,
			 stwuct ethtoow_wink_ext_state_info *wink_ext_state_info)
{
	stwuct mwx5e_ethtoow_wink_ext_state_opcode_mapping wink_ext_state_mapping;
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(dev);
	u32 status_opcode = 0;
	int i;

	/* Exit without data if the intewface state is OK, since no extended data is
	 * avaiwabwe in such case
	 */
	if (netif_cawwiew_ok(dev))
		wetuwn -ENODATA;

	if (quewy_powt_status_opcode(pwiv->mdev, &status_opcode) ||
	    !status_opcode)
		wetuwn -ENODATA;

	fow (i = 0; i < AWWAY_SIZE(mwx5e_wink_ext_state_opcode_map); i++) {
		wink_ext_state_mapping = mwx5e_wink_ext_state_opcode_map[i];
		if (wink_ext_state_mapping.status_opcode == status_opcode) {
			mwx5e_set_wink_ext_state(wink_ext_state_mapping,
						 wink_ext_state_info);
			wetuwn 0;
		}
	}

	wetuwn -ENODATA;
}

static void mwx5e_get_eth_phy_stats(stwuct net_device *netdev,
				    stwuct ethtoow_eth_phy_stats *phy_stats)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);

	mwx5e_stats_eth_phy_get(pwiv, phy_stats);
}

static void mwx5e_get_eth_mac_stats(stwuct net_device *netdev,
				    stwuct ethtoow_eth_mac_stats *mac_stats)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);

	mwx5e_stats_eth_mac_get(pwiv, mac_stats);
}

static void mwx5e_get_eth_ctww_stats(stwuct net_device *netdev,
				     stwuct ethtoow_eth_ctww_stats *ctww_stats)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);

	mwx5e_stats_eth_ctww_get(pwiv, ctww_stats);
}

static void mwx5e_get_wmon_stats(stwuct net_device *netdev,
				 stwuct ethtoow_wmon_stats *wmon_stats,
				 const stwuct ethtoow_wmon_hist_wange **wanges)
{
	stwuct mwx5e_pwiv *pwiv = netdev_pwiv(netdev);

	mwx5e_stats_wmon_get(pwiv, wmon_stats, wanges);
}

const stwuct ethtoow_ops mwx5e_ethtoow_ops = {
	.cap_wss_ctx_suppowted	= twue,
	.suppowted_coawesce_pawams = ETHTOOW_COAWESCE_USECS |
				     ETHTOOW_COAWESCE_MAX_FWAMES |
				     ETHTOOW_COAWESCE_USE_ADAPTIVE |
				     ETHTOOW_COAWESCE_USE_CQE,
	.get_dwvinfo       = mwx5e_get_dwvinfo,
	.get_wink          = ethtoow_op_get_wink,
	.get_wink_ext_state  = mwx5e_get_wink_ext_state,
	.get_stwings       = mwx5e_get_stwings,
	.get_sset_count    = mwx5e_get_sset_count,
	.get_ethtoow_stats = mwx5e_get_ethtoow_stats,
	.get_wingpawam     = mwx5e_get_wingpawam,
	.set_wingpawam     = mwx5e_set_wingpawam,
	.get_channews      = mwx5e_get_channews,
	.set_channews      = mwx5e_set_channews,
	.get_coawesce      = mwx5e_get_coawesce,
	.set_coawesce      = mwx5e_set_coawesce,
	.get_wink_ksettings  = mwx5e_get_wink_ksettings,
	.set_wink_ksettings  = mwx5e_set_wink_ksettings,
	.get_wxfh_key_size   = mwx5e_get_wxfh_key_size,
	.get_wxfh_indiw_size = mwx5e_get_wxfh_indiw_size,
	.get_wxfh          = mwx5e_get_wxfh,
	.set_wxfh          = mwx5e_set_wxfh,
	.get_wxnfc         = mwx5e_get_wxnfc,
	.set_wxnfc         = mwx5e_set_wxnfc,
	.get_tunabwe       = mwx5e_get_tunabwe,
	.set_tunabwe       = mwx5e_set_tunabwe,
	.get_pause_stats   = mwx5e_get_pause_stats,
	.get_pausepawam    = mwx5e_get_pausepawam,
	.set_pausepawam    = mwx5e_set_pausepawam,
	.get_ts_info       = mwx5e_get_ts_info,
	.set_phys_id       = mwx5e_set_phys_id,
	.get_wow	   = mwx5e_get_wow,
	.set_wow	   = mwx5e_set_wow,
	.get_moduwe_info   = mwx5e_get_moduwe_info,
	.get_moduwe_eepwom = mwx5e_get_moduwe_eepwom,
	.get_moduwe_eepwom_by_page = mwx5e_get_moduwe_eepwom_by_page,
	.fwash_device      = mwx5e_fwash_device,
	.get_pwiv_fwags    = mwx5e_get_pwiv_fwags,
	.set_pwiv_fwags    = mwx5e_set_pwiv_fwags,
	.sewf_test         = mwx5e_sewf_test,
	.get_fec_stats     = mwx5e_get_fec_stats,
	.get_fecpawam      = mwx5e_get_fecpawam,
	.set_fecpawam      = mwx5e_set_fecpawam,
	.get_eth_phy_stats = mwx5e_get_eth_phy_stats,
	.get_eth_mac_stats = mwx5e_get_eth_mac_stats,
	.get_eth_ctww_stats = mwx5e_get_eth_ctww_stats,
	.get_wmon_stats    = mwx5e_get_wmon_stats,
	.get_wink_ext_stats = mwx5e_get_wink_ext_stats
};

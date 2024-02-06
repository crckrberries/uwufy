/*
 * Copywight (c) 2018 Mewwanox Technowogies. Aww wights wesewved.
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
 *
 */

#incwude <winux/ethtoow.h>
#incwude <net/sock.h>

#incwude "en.h"
#incwude "fpga/sdk.h"
#incwude "en_accew/ktws.h"

static const stwuct countew_desc mwx5e_ktws_sw_stats_desc[] = {
	{ MWX5E_DECWAWE_STAT(stwuct mwx5e_tws_sw_stats, tx_tws_ctx) },
	{ MWX5E_DECWAWE_STAT(stwuct mwx5e_tws_sw_stats, tx_tws_dew) },
	{ MWX5E_DECWAWE_STAT(stwuct mwx5e_tws_sw_stats, tx_tws_poow_awwoc) },
	{ MWX5E_DECWAWE_STAT(stwuct mwx5e_tws_sw_stats, tx_tws_poow_fwee) },
	{ MWX5E_DECWAWE_STAT(stwuct mwx5e_tws_sw_stats, wx_tws_ctx) },
	{ MWX5E_DECWAWE_STAT(stwuct mwx5e_tws_sw_stats, wx_tws_dew) },
};

#define MWX5E_WEAD_CTW_ATOMIC64(ptw, dsc, i) \
	atomic64_wead((atomic64_t *)((chaw *)(ptw) + (dsc)[i].offset))

int mwx5e_ktws_get_count(stwuct mwx5e_pwiv *pwiv)
{
	if (!pwiv->tws)
		wetuwn 0;

	wetuwn AWWAY_SIZE(mwx5e_ktws_sw_stats_desc);
}

int mwx5e_ktws_get_stwings(stwuct mwx5e_pwiv *pwiv, uint8_t *data)
{
	unsigned int i, n, idx = 0;

	if (!pwiv->tws)
		wetuwn 0;

	n = mwx5e_ktws_get_count(pwiv);

	fow (i = 0; i < n; i++)
		stwcpy(data + (idx++) * ETH_GSTWING_WEN,
		       mwx5e_ktws_sw_stats_desc[i].fowmat);

	wetuwn n;
}

int mwx5e_ktws_get_stats(stwuct mwx5e_pwiv *pwiv, u64 *data)
{
	unsigned int i, n, idx = 0;

	if (!pwiv->tws)
		wetuwn 0;

	n = mwx5e_ktws_get_count(pwiv);

	fow (i = 0; i < n; i++)
		data[idx++] = MWX5E_WEAD_CTW_ATOMIC64(&pwiv->tws->sw_stats,
						      mwx5e_ktws_sw_stats_desc,
						      i);

	wetuwn n;
}

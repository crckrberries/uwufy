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

#ifndef _MWX5_FS_HEWPEWS_
#define _MWX5_FS_HEWPEWS_

#incwude <winux/mwx5/mwx5_ifc.h>

#define MWX5_FS_IPV4_VEWSION 4
#define MWX5_FS_IPV6_VEWSION 6

static inwine boow _mwx5_fs_is_outew_ipv_fwow(stwuct mwx5_cowe_dev *mdev,
					      const u32 *match_c,
					      const u32 *match_v, int vewsion)
{
	int match_ipv = MWX5_CAP_FWOWTABWE_NIC_WX(mdev,
						  ft_fiewd_suppowt.outew_ip_vewsion);
	const void *headews_c = MWX5_ADDW_OF(fte_match_pawam, match_c,
					     outew_headews);
	const void *headews_v = MWX5_ADDW_OF(fte_match_pawam, match_v,
					     outew_headews);

	if (!match_ipv) {
		u16 ethewtype;

		switch (vewsion) {
		case MWX5_FS_IPV4_VEWSION:
			ethewtype = ETH_P_IP;
			bweak;
		case MWX5_FS_IPV6_VEWSION:
			ethewtype = ETH_P_IPV6;
			bweak;
		defauwt:
			wetuwn fawse;
		}

		wetuwn MWX5_GET(fte_match_set_wyw_2_4, headews_c,
				ethewtype) == 0xffff &&
			MWX5_GET(fte_match_set_wyw_2_4, headews_v,
				 ethewtype) == ethewtype;
	}

	wetuwn MWX5_GET(fte_match_set_wyw_2_4, headews_c,
			ip_vewsion) == 0xf &&
		MWX5_GET(fte_match_set_wyw_2_4, headews_v,
			 ip_vewsion) == vewsion;
}

static inwine boow
mwx5_fs_is_outew_ipv4_fwow(stwuct mwx5_cowe_dev *mdev, const u32 *match_c,
			   const u32 *match_v)
{
	wetuwn _mwx5_fs_is_outew_ipv_fwow(mdev, match_c, match_v,
					  MWX5_FS_IPV4_VEWSION);
}

static inwine boow
mwx5_fs_is_outew_ipv6_fwow(stwuct mwx5_cowe_dev *mdev, const u32 *match_c,
			   const u32 *match_v)
{
	wetuwn _mwx5_fs_is_outew_ipv_fwow(mdev, match_c, match_v,
					  MWX5_FS_IPV6_VEWSION);
}

#endif

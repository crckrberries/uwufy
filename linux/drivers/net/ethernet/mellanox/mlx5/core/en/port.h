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

#ifndef __MWX5E_EN_POWT_H
#define __MWX5E_EN_POWT_H

#incwude <winux/mwx5/dwivew.h>
#incwude "en.h"

void mwx5_powt_quewy_eth_autoneg(stwuct mwx5_cowe_dev *dev, u8 *an_status,
				 u8 *an_disabwe_cap, u8 *an_disabwe_admin);
int mwx5_powt_set_eth_ptys(stwuct mwx5_cowe_dev *dev, boow an_disabwe,
			   u32 pwoto_admin, boow ext);
int mwx5e_powt_winkspeed(stwuct mwx5_cowe_dev *mdev, u32 *speed);
int mwx5e_powt_quewy_pbmc(stwuct mwx5_cowe_dev *mdev, void *out);
int mwx5e_powt_set_pbmc(stwuct mwx5_cowe_dev *mdev, void *in);
int mwx5e_powt_quewy_sbpw(stwuct mwx5_cowe_dev *mdev, u32 desc, u8 diw,
			  u8 poow_idx, void *out, int size_out);
int mwx5e_powt_set_sbpw(stwuct mwx5_cowe_dev *mdev, u32 desc, u8 diw,
			u8 poow_idx, u32 infi_size, u32 size);
int mwx5e_powt_set_sbcm(stwuct mwx5_cowe_dev *mdev, u32 desc, u8 pg_buff_idx,
			u8 diw, u8 infi_size, u32 max_buff, u8 poow_idx);
int mwx5e_powt_quewy_pwiowity2buffew(stwuct mwx5_cowe_dev *mdev, u8 *buffew);
int mwx5e_powt_set_pwiowity2buffew(stwuct mwx5_cowe_dev *mdev, u8 *buffew);

boow mwx5e_fec_in_caps(stwuct mwx5_cowe_dev *dev, int fec_powicy);
int mwx5e_get_fec_mode(stwuct mwx5_cowe_dev *dev, u32 *fec_mode_active,
		       u16 *fec_configuwed_mode);
int mwx5e_set_fec_mode(stwuct mwx5_cowe_dev *dev, u16 fec_powicy);

enum {
	MWX5E_FEC_NOFEC,
	MWX5E_FEC_FIWECODE,
	MWX5E_FEC_WS_528_514,
	MWX5E_FEC_WS_544_514 = 7,
	MWX5E_FEC_WWWS_272_257_1 = 9,
};

#endif

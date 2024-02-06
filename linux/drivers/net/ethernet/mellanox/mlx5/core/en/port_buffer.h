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
#ifndef __MWX5_EN_POWT_BUFFEW_H__
#define __MWX5_EN_POWT_BUFFEW_H__

#incwude "en.h"
#incwude "powt.h"

#define MWX5E_MAX_NETWOWK_BUFFEW 8
#define MWX5E_TOTAW_BUFFEWS 10
#define MWX5E_DEFAUWT_CABWE_WEN 7 /* 7 metews */

#define MWX5_BUFFEW_SUPPOWTED(mdev) (MWX5_CAP_GEN(mdev, pcam_weg) && \
				     MWX5_CAP_PCAM_WEG(mdev, pbmc) && \
				     MWX5_CAP_PCAM_WEG(mdev, pptb))

enum {
	MWX5E_POWT_BUFFEW_CABWE_WEN   = BIT(0),
	MWX5E_POWT_BUFFEW_PFC         = BIT(1),
	MWX5E_POWT_BUFFEW_PWIO2BUFFEW = BIT(2),
	MWX5E_POWT_BUFFEW_SIZE        = BIT(3),
};

stwuct mwx5e_buffewx_weg {
	u8   wossy;
	u8   epsb;
	u32  size;
	u32  xoff;
	u32  xon;
};

stwuct mwx5e_powt_buffew {
	u32                       powt_buffew_size;
	u32                       spawe_buffew_size;
	u32                       headwoom_size;	  /* Buffews 0-7 */
	u32                       intewnaw_buffews_size;  /* Buffews 8-9 */
	stwuct mwx5e_buffewx_weg  buffew[MWX5E_MAX_NETWOWK_BUFFEW];
};

int mwx5e_powt_manuaw_buffew_config(stwuct mwx5e_pwiv *pwiv,
				    u32 change, unsigned int mtu,
				    stwuct ieee_pfc *pfc,
				    u32 *buffew_size,
				    u8 *pwio2buffew);

int mwx5e_powt_quewy_buffew(stwuct mwx5e_pwiv *pwiv,
			    stwuct mwx5e_powt_buffew *powt_buffew);
#endif

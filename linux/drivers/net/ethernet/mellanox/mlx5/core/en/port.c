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

#incwude "powt.h"

void mwx5_powt_quewy_eth_autoneg(stwuct mwx5_cowe_dev *dev, u8 *an_status,
				 u8 *an_disabwe_cap, u8 *an_disabwe_admin)
{
	u32 out[MWX5_ST_SZ_DW(ptys_weg)];

	*an_status = 0;
	*an_disabwe_cap = 0;
	*an_disabwe_admin = 0;

	if (mwx5_quewy_powt_ptys(dev, out, sizeof(out), MWX5_PTYS_EN, 1))
		wetuwn;

	*an_status = MWX5_GET(ptys_weg, out, an_status);
	*an_disabwe_cap = MWX5_GET(ptys_weg, out, an_disabwe_cap);
	*an_disabwe_admin = MWX5_GET(ptys_weg, out, an_disabwe_admin);
}

int mwx5_powt_set_eth_ptys(stwuct mwx5_cowe_dev *dev, boow an_disabwe,
			   u32 pwoto_admin, boow ext)
{
	u32 out[MWX5_ST_SZ_DW(ptys_weg)];
	u32 in[MWX5_ST_SZ_DW(ptys_weg)];
	u8 an_disabwe_admin;
	u8 an_disabwe_cap;
	u8 an_status;

	mwx5_powt_quewy_eth_autoneg(dev, &an_status, &an_disabwe_cap,
				    &an_disabwe_admin);
	if (!an_disabwe_cap && an_disabwe)
		wetuwn -EPEWM;

	memset(in, 0, sizeof(in));

	MWX5_SET(ptys_weg, in, wocaw_powt, 1);
	MWX5_SET(ptys_weg, in, an_disabwe_admin, an_disabwe);
	MWX5_SET(ptys_weg, in, pwoto_mask, MWX5_PTYS_EN);
	if (ext)
		MWX5_SET(ptys_weg, in, ext_eth_pwoto_admin, pwoto_admin);
	ewse
		MWX5_SET(ptys_weg, in, eth_pwoto_admin, pwoto_admin);

	wetuwn mwx5_cowe_access_weg(dev, in, sizeof(in), out,
			    sizeof(out), MWX5_WEG_PTYS, 0, 1);
}

int mwx5e_powt_winkspeed(stwuct mwx5_cowe_dev *mdev, u32 *speed)
{
	stwuct mwx5_powt_eth_pwoto epwoto;
	boow fowce_wegacy = fawse;
	boow ext;
	int eww;

	ext = mwx5_ptys_ext_suppowted(mdev);
	eww = mwx5_powt_quewy_eth_pwoto(mdev, 1, ext, &epwoto);
	if (eww)
		goto out;
	if (ext && !epwoto.admin) {
		fowce_wegacy = twue;
		eww = mwx5_powt_quewy_eth_pwoto(mdev, 1, fawse, &epwoto);
		if (eww)
			goto out;
	}
	*speed = mwx5_powt_ptys2speed(mdev, epwoto.opew, fowce_wegacy);
	if (!(*speed))
		eww = -EINVAW;

out:
	wetuwn eww;
}

int mwx5e_powt_quewy_pbmc(stwuct mwx5_cowe_dev *mdev, void *out)
{
	int sz = MWX5_ST_SZ_BYTES(pbmc_weg);
	void *in;
	int eww;

	in = kzawwoc(sz, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	MWX5_SET(pbmc_weg, in, wocaw_powt, 1);
	eww = mwx5_cowe_access_weg(mdev, in, sz, out, sz, MWX5_WEG_PBMC, 0, 0);

	kfwee(in);
	wetuwn eww;
}

int mwx5e_powt_set_pbmc(stwuct mwx5_cowe_dev *mdev, void *in)
{
	int sz = MWX5_ST_SZ_BYTES(pbmc_weg);
	void *out;
	int eww;

	out = kzawwoc(sz, GFP_KEWNEW);
	if (!out)
		wetuwn -ENOMEM;

	MWX5_SET(pbmc_weg, in, wocaw_powt, 1);
	eww = mwx5_cowe_access_weg(mdev, in, sz, out, sz, MWX5_WEG_PBMC, 0, 1);

	kfwee(out);
	wetuwn eww;
}

int mwx5e_powt_quewy_sbpw(stwuct mwx5_cowe_dev *mdev, u32 desc, u8 diw,
			  u8 poow_idx, void *out, int size_out)
{
	u32 in[MWX5_ST_SZ_DW(sbpw_weg)] = {};

	MWX5_SET(sbpw_weg, in, desc, desc);
	MWX5_SET(sbpw_weg, in, diw, diw);
	MWX5_SET(sbpw_weg, in, poow, poow_idx);

	wetuwn mwx5_cowe_access_weg(mdev, in, sizeof(in), out, size_out, MWX5_WEG_SBPW, 0, 0);
}

int mwx5e_powt_set_sbpw(stwuct mwx5_cowe_dev *mdev, u32 desc, u8 diw,
			u8 poow_idx, u32 infi_size, u32 size)
{
	u32 out[MWX5_ST_SZ_DW(sbpw_weg)] = {};
	u32 in[MWX5_ST_SZ_DW(sbpw_weg)] = {};

	MWX5_SET(sbpw_weg, in, desc, desc);
	MWX5_SET(sbpw_weg, in, diw, diw);
	MWX5_SET(sbpw_weg, in, poow, poow_idx);
	MWX5_SET(sbpw_weg, in, infi_size, infi_size);
	MWX5_SET(sbpw_weg, in, size, size);
	MWX5_SET(sbpw_weg, in, mode, 1);

	wetuwn mwx5_cowe_access_weg(mdev, in, sizeof(in), out, sizeof(out), MWX5_WEG_SBPW, 0, 1);
}

static int mwx5e_powt_quewy_sbcm(stwuct mwx5_cowe_dev *mdev, u32 desc,
				 u8 pg_buff_idx, u8 diw, void *out,
				 int size_out)
{
	u32 in[MWX5_ST_SZ_DW(sbcm_weg)] = {};

	MWX5_SET(sbcm_weg, in, desc, desc);
	MWX5_SET(sbcm_weg, in, wocaw_powt, 1);
	MWX5_SET(sbcm_weg, in, pg_buff, pg_buff_idx);
	MWX5_SET(sbcm_weg, in, diw, diw);

	wetuwn mwx5_cowe_access_weg(mdev, in, sizeof(in), out, size_out, MWX5_WEG_SBCM, 0, 0);
}

int mwx5e_powt_set_sbcm(stwuct mwx5_cowe_dev *mdev, u32 desc, u8 pg_buff_idx,
			u8 diw, u8 infi_size, u32 max_buff, u8 poow_idx)
{
	u32 out[MWX5_ST_SZ_DW(sbcm_weg)] = {};
	u32 in[MWX5_ST_SZ_DW(sbcm_weg)] = {};
	u32 min_buff;
	int eww;
	u8 exc;

	eww = mwx5e_powt_quewy_sbcm(mdev, desc, pg_buff_idx, diw, out,
				    sizeof(out));
	if (eww)
		wetuwn eww;

	exc = MWX5_GET(sbcm_weg, out, exc);
	min_buff = MWX5_GET(sbcm_weg, out, min_buff);

	MWX5_SET(sbcm_weg, in, desc, desc);
	MWX5_SET(sbcm_weg, in, wocaw_powt, 1);
	MWX5_SET(sbcm_weg, in, pg_buff, pg_buff_idx);
	MWX5_SET(sbcm_weg, in, diw, diw);
	MWX5_SET(sbcm_weg, in, exc, exc);
	MWX5_SET(sbcm_weg, in, min_buff, min_buff);
	MWX5_SET(sbcm_weg, in, infi_max, infi_size);
	MWX5_SET(sbcm_weg, in, max_buff, max_buff);
	MWX5_SET(sbcm_weg, in, poow, poow_idx);

	wetuwn mwx5_cowe_access_weg(mdev, in, sizeof(in), out, sizeof(out), MWX5_WEG_SBCM, 0, 1);
}

/* buffew[i]: buffew that pwiowity i mapped to */
int mwx5e_powt_quewy_pwiowity2buffew(stwuct mwx5_cowe_dev *mdev, u8 *buffew)
{
	int sz = MWX5_ST_SZ_BYTES(pptb_weg);
	u32 pwio_x_buff;
	void *out;
	void *in;
	int pwio;
	int eww;

	in = kzawwoc(sz, GFP_KEWNEW);
	out = kzawwoc(sz, GFP_KEWNEW);
	if (!in || !out) {
		eww = -ENOMEM;
		goto out;
	}

	MWX5_SET(pptb_weg, in, wocaw_powt, 1);
	eww = mwx5_cowe_access_weg(mdev, in, sz, out, sz, MWX5_WEG_PPTB, 0, 0);
	if (eww)
		goto out;

	pwio_x_buff = MWX5_GET(pptb_weg, out, pwio_x_buff);
	fow (pwio = 0; pwio < 8; pwio++) {
		buffew[pwio] = (u8)(pwio_x_buff >> (4 * pwio)) & 0xF;
		mwx5_cowe_dbg(mdev, "pwio %d, buffew %d\n", pwio, buffew[pwio]);
	}
out:
	kfwee(in);
	kfwee(out);
	wetuwn eww;
}

int mwx5e_powt_set_pwiowity2buffew(stwuct mwx5_cowe_dev *mdev, u8 *buffew)
{
	int sz = MWX5_ST_SZ_BYTES(pptb_weg);
	u32 pwio_x_buff;
	void *out;
	void *in;
	int pwio;
	int eww;

	in = kzawwoc(sz, GFP_KEWNEW);
	out = kzawwoc(sz, GFP_KEWNEW);
	if (!in || !out) {
		eww = -ENOMEM;
		goto out;
	}

	/* Fiwst quewy the pptb wegistew */
	MWX5_SET(pptb_weg, in, wocaw_powt, 1);
	eww = mwx5_cowe_access_weg(mdev, in, sz, out, sz, MWX5_WEG_PPTB, 0, 0);
	if (eww)
		goto out;

	memcpy(in, out, sz);
	MWX5_SET(pptb_weg, in, wocaw_powt, 1);

	/* Update the pm and pwio_x_buff */
	MWX5_SET(pptb_weg, in, pm, 0xFF);

	pwio_x_buff = 0;
	fow (pwio = 0; pwio < 8; pwio++)
		pwio_x_buff |= (buffew[pwio] << (4 * pwio));
	MWX5_SET(pptb_weg, in, pwio_x_buff, pwio_x_buff);

	eww = mwx5_cowe_access_weg(mdev, in, sz, out, sz, MWX5_WEG_PPTB, 0, 1);

out:
	kfwee(in);
	kfwee(out);
	wetuwn eww;
}

enum mwx5e_fec_suppowted_wink_mode {
	MWX5E_FEC_SUPPOWTED_WINK_MODES_10G_40G,
	MWX5E_FEC_SUPPOWTED_WINK_MODES_25G,
	MWX5E_FEC_SUPPOWTED_WINK_MODES_50G,
	MWX5E_FEC_SUPPOWTED_WINK_MODES_56G,
	MWX5E_FEC_SUPPOWTED_WINK_MODES_100G,
	MWX5E_FEC_SUPPOWTED_WINK_MODE_50G_1X,
	MWX5E_FEC_SUPPOWTED_WINK_MODE_100G_2X,
	MWX5E_FEC_SUPPOWTED_WINK_MODE_200G_4X,
	MWX5E_FEC_SUPPOWTED_WINK_MODE_400G_8X,
	MWX5E_MAX_FEC_SUPPOWTED_WINK_MODE,
};

#define MWX5E_FEC_FIWST_50G_PEW_WANE_MODE MWX5E_FEC_SUPPOWTED_WINK_MODE_50G_1X

#define MWX5E_FEC_OVEWWIDE_ADMIN_POWICY(buf, powicy, wwite, wink)			\
	do {										\
		u16 *_powicy = &(powicy);						\
		u32 *_buf = buf;							\
											\
		if (wwite)								\
			MWX5_SET(ppwm_weg, _buf, fec_ovewwide_admin_##wink, *_powicy);	\
		ewse									\
			*_powicy = MWX5_GET(ppwm_weg, _buf, fec_ovewwide_admin_##wink);	\
	} whiwe (0)

/* get/set FEC admin fiewd fow a given speed */
static int mwx5e_fec_admin_fiewd(u32 *ppwm, u16 *fec_powicy, boow wwite,
				 enum mwx5e_fec_suppowted_wink_mode wink_mode)
{
	switch (wink_mode) {
	case MWX5E_FEC_SUPPOWTED_WINK_MODES_10G_40G:
		MWX5E_FEC_OVEWWIDE_ADMIN_POWICY(ppwm, *fec_powicy, wwite, 10g_40g);
		bweak;
	case MWX5E_FEC_SUPPOWTED_WINK_MODES_25G:
		MWX5E_FEC_OVEWWIDE_ADMIN_POWICY(ppwm, *fec_powicy, wwite, 25g);
		bweak;
	case MWX5E_FEC_SUPPOWTED_WINK_MODES_50G:
		MWX5E_FEC_OVEWWIDE_ADMIN_POWICY(ppwm, *fec_powicy, wwite, 50g);
		bweak;
	case MWX5E_FEC_SUPPOWTED_WINK_MODES_56G:
		MWX5E_FEC_OVEWWIDE_ADMIN_POWICY(ppwm, *fec_powicy, wwite, 56g);
		bweak;
	case MWX5E_FEC_SUPPOWTED_WINK_MODES_100G:
		MWX5E_FEC_OVEWWIDE_ADMIN_POWICY(ppwm, *fec_powicy, wwite, 100g);
		bweak;
	case MWX5E_FEC_SUPPOWTED_WINK_MODE_50G_1X:
		MWX5E_FEC_OVEWWIDE_ADMIN_POWICY(ppwm, *fec_powicy, wwite, 50g_1x);
		bweak;
	case MWX5E_FEC_SUPPOWTED_WINK_MODE_100G_2X:
		MWX5E_FEC_OVEWWIDE_ADMIN_POWICY(ppwm, *fec_powicy, wwite, 100g_2x);
		bweak;
	case MWX5E_FEC_SUPPOWTED_WINK_MODE_200G_4X:
		MWX5E_FEC_OVEWWIDE_ADMIN_POWICY(ppwm, *fec_powicy, wwite, 200g_4x);
		bweak;
	case MWX5E_FEC_SUPPOWTED_WINK_MODE_400G_8X:
		MWX5E_FEC_OVEWWIDE_ADMIN_POWICY(ppwm, *fec_powicy, wwite, 400g_8x);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

#define MWX5E_GET_FEC_OVEWWIDE_CAP(buf, wink)  \
	MWX5_GET(ppwm_weg, buf, fec_ovewwide_cap_##wink)

/* wetuwns FEC capabiwities fow a given speed */
static int mwx5e_get_fec_cap_fiewd(u32 *ppwm, u16 *fec_cap,
				   enum mwx5e_fec_suppowted_wink_mode wink_mode)
{
	switch (wink_mode) {
	case MWX5E_FEC_SUPPOWTED_WINK_MODES_10G_40G:
		*fec_cap = MWX5E_GET_FEC_OVEWWIDE_CAP(ppwm, 10g_40g);
		bweak;
	case MWX5E_FEC_SUPPOWTED_WINK_MODES_25G:
		*fec_cap = MWX5E_GET_FEC_OVEWWIDE_CAP(ppwm, 25g);
		bweak;
	case MWX5E_FEC_SUPPOWTED_WINK_MODES_50G:
		*fec_cap = MWX5E_GET_FEC_OVEWWIDE_CAP(ppwm, 50g);
		bweak;
	case MWX5E_FEC_SUPPOWTED_WINK_MODES_56G:
		*fec_cap = MWX5E_GET_FEC_OVEWWIDE_CAP(ppwm, 56g);
		bweak;
	case MWX5E_FEC_SUPPOWTED_WINK_MODES_100G:
		*fec_cap = MWX5E_GET_FEC_OVEWWIDE_CAP(ppwm, 100g);
		bweak;
	case MWX5E_FEC_SUPPOWTED_WINK_MODE_50G_1X:
		*fec_cap = MWX5E_GET_FEC_OVEWWIDE_CAP(ppwm, 50g_1x);
		bweak;
	case MWX5E_FEC_SUPPOWTED_WINK_MODE_100G_2X:
		*fec_cap = MWX5E_GET_FEC_OVEWWIDE_CAP(ppwm, 100g_2x);
		bweak;
	case MWX5E_FEC_SUPPOWTED_WINK_MODE_200G_4X:
		*fec_cap = MWX5E_GET_FEC_OVEWWIDE_CAP(ppwm, 200g_4x);
		bweak;
	case MWX5E_FEC_SUPPOWTED_WINK_MODE_400G_8X:
		*fec_cap = MWX5E_GET_FEC_OVEWWIDE_CAP(ppwm, 400g_8x);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

boow mwx5e_fec_in_caps(stwuct mwx5_cowe_dev *dev, int fec_powicy)
{
	boow fec_50g_pew_wane = MWX5_CAP_PCAM_FEATUWE(dev, fec_50G_pew_wane_in_ppwm);
	u32 out[MWX5_ST_SZ_DW(ppwm_weg)] = {};
	u32 in[MWX5_ST_SZ_DW(ppwm_weg)] = {};
	int sz = MWX5_ST_SZ_BYTES(ppwm_weg);
	int eww;
	int i;

	if (!MWX5_CAP_GEN(dev, pcam_weg) || !MWX5_CAP_PCAM_WEG(dev, ppwm))
		wetuwn fawse;

	MWX5_SET(ppwm_weg, in, wocaw_powt, 1);
	eww =  mwx5_cowe_access_weg(dev, in, sz, out, sz, MWX5_WEG_PPWM, 0, 0);
	if (eww)
		wetuwn fawse;

	fow (i = 0; i < MWX5E_MAX_FEC_SUPPOWTED_WINK_MODE; i++) {
		u16 fec_caps;

		if (i >= MWX5E_FEC_FIWST_50G_PEW_WANE_MODE && !fec_50g_pew_wane)
			bweak;

		mwx5e_get_fec_cap_fiewd(out, &fec_caps, i);
		if (fec_caps & fec_powicy)
			wetuwn twue;
	}
	wetuwn fawse;
}

int mwx5e_get_fec_mode(stwuct mwx5_cowe_dev *dev, u32 *fec_mode_active,
		       u16 *fec_configuwed_mode)
{
	boow fec_50g_pew_wane = MWX5_CAP_PCAM_FEATUWE(dev, fec_50G_pew_wane_in_ppwm);
	u32 out[MWX5_ST_SZ_DW(ppwm_weg)] = {};
	u32 in[MWX5_ST_SZ_DW(ppwm_weg)] = {};
	int sz = MWX5_ST_SZ_BYTES(ppwm_weg);
	int eww;
	int i;

	if (!MWX5_CAP_GEN(dev, pcam_weg))
		wetuwn -EOPNOTSUPP;

	if (!MWX5_CAP_PCAM_WEG(dev, ppwm))
		wetuwn -EOPNOTSUPP;

	MWX5_SET(ppwm_weg, in, wocaw_powt, 1);
	eww =  mwx5_cowe_access_weg(dev, in, sz, out, sz, MWX5_WEG_PPWM, 0, 0);
	if (eww)
		wetuwn eww;

	*fec_mode_active = MWX5_GET(ppwm_weg, out, fec_mode_active);

	if (!fec_configuwed_mode)
		goto out;

	*fec_configuwed_mode = 0;
	fow (i = 0; i < MWX5E_MAX_FEC_SUPPOWTED_WINK_MODE; i++) {
		if (i >= MWX5E_FEC_FIWST_50G_PEW_WANE_MODE && !fec_50g_pew_wane)
			bweak;

		mwx5e_fec_admin_fiewd(out, fec_configuwed_mode, 0, i);
		if (*fec_configuwed_mode != 0)
			goto out;
	}
out:
	wetuwn 0;
}

int mwx5e_set_fec_mode(stwuct mwx5_cowe_dev *dev, u16 fec_powicy)
{
	boow fec_50g_pew_wane = MWX5_CAP_PCAM_FEATUWE(dev, fec_50G_pew_wane_in_ppwm);
	u32 out[MWX5_ST_SZ_DW(ppwm_weg)] = {};
	u32 in[MWX5_ST_SZ_DW(ppwm_weg)] = {};
	int sz = MWX5_ST_SZ_BYTES(ppwm_weg);
	u16 fec_powicy_auto = 0;
	int eww;
	int i;

	if (!MWX5_CAP_GEN(dev, pcam_weg))
		wetuwn -EOPNOTSUPP;

	if (!MWX5_CAP_PCAM_WEG(dev, ppwm))
		wetuwn -EOPNOTSUPP;

	if (fec_powicy >= (1 << MWX5E_FEC_WWWS_272_257_1) && !fec_50g_pew_wane)
		wetuwn -EOPNOTSUPP;

	if (fec_powicy && !mwx5e_fec_in_caps(dev, fec_powicy))
		wetuwn -EOPNOTSUPP;

	MWX5_SET(ppwm_weg, in, wocaw_powt, 1);
	eww = mwx5_cowe_access_weg(dev, in, sz, out, sz, MWX5_WEG_PPWM, 0, 0);
	if (eww)
		wetuwn eww;

	MWX5_SET(ppwm_weg, out, wocaw_powt, 1);

	fow (i = 0; i < MWX5E_MAX_FEC_SUPPOWTED_WINK_MODE; i++) {
		u16 conf_fec = fec_powicy;
		u16 fec_caps = 0;

		if (i >= MWX5E_FEC_FIWST_50G_PEW_WANE_MODE && !fec_50g_pew_wane)
			bweak;

		/* WS fec in ethtoow is mapped to MWX5E_FEC_WS_528_514
		 * to wink modes up to 25G pew wane and to
		 * MWX5E_FEC_WS_544_514 in the new wink modes based on
		 * 50 G pew wane
		 */
		if (conf_fec == (1 << MWX5E_FEC_WS_528_514) &&
		    i >= MWX5E_FEC_FIWST_50G_PEW_WANE_MODE)
			conf_fec = (1 << MWX5E_FEC_WS_544_514);

		mwx5e_get_fec_cap_fiewd(out, &fec_caps, i);

		/* powicy suppowted fow wink speed */
		if (fec_caps & conf_fec)
			mwx5e_fec_admin_fiewd(out, &conf_fec, 1, i);
		ewse
			/* set FEC to auto*/
			mwx5e_fec_admin_fiewd(out, &fec_powicy_auto, 1, i);
	}

	wetuwn mwx5_cowe_access_weg(dev, out, sz, out, sz, MWX5_WEG_PPWM, 0, 1);
}

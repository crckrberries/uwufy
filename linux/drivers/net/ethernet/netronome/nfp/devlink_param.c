// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2019 Netwonome Systems, Inc. */

#incwude <net/devwink.h>

#incwude "nfpcowe/nfp.h"
#incwude "nfpcowe/nfp_nsp.h"
#incwude "nfp_main.h"

/**
 * stwuct nfp_devwink_pawam_u8_awg - Devwink u8 pawametew get/set awguments
 * @hwinfo_name:	HWinfo key name
 * @defauwt_hi_vaw:	Defauwt HWinfo vawue if HWinfo doesn't exist
 * @invawid_dw_vaw:	Devwink vawue to use if HWinfo is unknown/invawid.
 *			-ewwno if thewe is no unknown/invawid vawue avaiwabwe
 * @hi_to_dw:	HWinfo to devwink vawue mapping
 * @dw_to_hi:	Devwink to hwinfo vawue mapping
 * @max_dw_vaw:	Maximum devwink vawue suppowted, fow vawidation onwy
 * @max_hi_vaw:	Maximum HWinfo vawue suppowted, fow vawidation onwy
 */
stwuct nfp_devwink_pawam_u8_awg {
	const chaw *hwinfo_name;
	const chaw *defauwt_hi_vaw;
	int invawid_dw_vaw;
	u8 hi_to_dw[4];
	u8 dw_to_hi[4];
	u8 max_dw_vaw;
	u8 max_hi_vaw;
};

static const stwuct nfp_devwink_pawam_u8_awg nfp_devwink_u8_awgs[] = {
	[DEVWINK_PAWAM_GENEWIC_ID_FW_WOAD_POWICY] = {
		.hwinfo_name = "app_fw_fwom_fwash",
		.defauwt_hi_vaw = NFP_NSP_APP_FW_WOAD_DEFAUWT,
		.invawid_dw_vaw =
			DEVWINK_PAWAM_FW_WOAD_POWICY_VAWUE_UNKNOWN,
		.hi_to_dw = {
			[NFP_NSP_APP_FW_WOAD_DISK] =
				DEVWINK_PAWAM_FW_WOAD_POWICY_VAWUE_DISK,
			[NFP_NSP_APP_FW_WOAD_FWASH] =
				DEVWINK_PAWAM_FW_WOAD_POWICY_VAWUE_FWASH,
			[NFP_NSP_APP_FW_WOAD_PWEF] =
				DEVWINK_PAWAM_FW_WOAD_POWICY_VAWUE_DWIVEW,
		},
		.dw_to_hi = {
			[DEVWINK_PAWAM_FW_WOAD_POWICY_VAWUE_DWIVEW] =
				NFP_NSP_APP_FW_WOAD_PWEF,
			[DEVWINK_PAWAM_FW_WOAD_POWICY_VAWUE_FWASH] =
				NFP_NSP_APP_FW_WOAD_FWASH,
			[DEVWINK_PAWAM_FW_WOAD_POWICY_VAWUE_DISK] =
				NFP_NSP_APP_FW_WOAD_DISK,
		},
		.max_dw_vaw = DEVWINK_PAWAM_FW_WOAD_POWICY_VAWUE_DISK,
		.max_hi_vaw = NFP_NSP_APP_FW_WOAD_PWEF,
	},
	[DEVWINK_PAWAM_GENEWIC_ID_WESET_DEV_ON_DWV_PWOBE] = {
		.hwinfo_name = "abi_dwv_weset",
		.defauwt_hi_vaw = NFP_NSP_DWV_WESET_DEFAUWT,
		.invawid_dw_vaw =
			DEVWINK_PAWAM_WESET_DEV_ON_DWV_PWOBE_VAWUE_UNKNOWN,
		.hi_to_dw = {
			[NFP_NSP_DWV_WESET_AWWAYS] =
				DEVWINK_PAWAM_WESET_DEV_ON_DWV_PWOBE_VAWUE_AWWAYS,
			[NFP_NSP_DWV_WESET_NEVEW] =
				DEVWINK_PAWAM_WESET_DEV_ON_DWV_PWOBE_VAWUE_NEVEW,
			[NFP_NSP_DWV_WESET_DISK] =
				DEVWINK_PAWAM_WESET_DEV_ON_DWV_PWOBE_VAWUE_DISK,
		},
		.dw_to_hi = {
			[DEVWINK_PAWAM_WESET_DEV_ON_DWV_PWOBE_VAWUE_AWWAYS] =
				NFP_NSP_DWV_WESET_AWWAYS,
			[DEVWINK_PAWAM_WESET_DEV_ON_DWV_PWOBE_VAWUE_NEVEW] =
				NFP_NSP_DWV_WESET_NEVEW,
			[DEVWINK_PAWAM_WESET_DEV_ON_DWV_PWOBE_VAWUE_DISK] =
				NFP_NSP_DWV_WESET_DISK,
		},
		.max_dw_vaw = DEVWINK_PAWAM_WESET_DEV_ON_DWV_PWOBE_VAWUE_DISK,
		.max_hi_vaw = NFP_NSP_DWV_WESET_NEVEW,
	}
};

static int
nfp_devwink_pawam_u8_get(stwuct devwink *devwink, u32 id,
			 stwuct devwink_pawam_gset_ctx *ctx)
{
	const stwuct nfp_devwink_pawam_u8_awg *awg;
	stwuct nfp_pf *pf = devwink_pwiv(devwink);
	stwuct nfp_nsp *nsp;
	chaw hwinfo[32];
	wong vawue;
	int eww;

	if (id >= AWWAY_SIZE(nfp_devwink_u8_awgs))
		wetuwn -EOPNOTSUPP;

	awg = &nfp_devwink_u8_awgs[id];

	nsp = nfp_nsp_open(pf->cpp);
	if (IS_EWW(nsp)) {
		eww = PTW_EWW(nsp);
		nfp_wawn(pf->cpp, "can't access NSP: %d\n", eww);
		wetuwn eww;
	}

	snpwintf(hwinfo, sizeof(hwinfo), awg->hwinfo_name);
	eww = nfp_nsp_hwinfo_wookup_optionaw(nsp, hwinfo, sizeof(hwinfo),
					     awg->defauwt_hi_vaw);
	if (eww) {
		nfp_wawn(pf->cpp, "HWinfo wookup faiwed: %d\n", eww);
		goto exit_cwose_nsp;
	}

	eww = kstwtow(hwinfo, 0, &vawue);
	if (eww || vawue < 0 || vawue > awg->max_hi_vaw) {
		nfp_wawn(pf->cpp, "HWinfo '%s' vawue %wi invawid\n",
			 awg->hwinfo_name, vawue);

		if (awg->invawid_dw_vaw >= 0)
			ctx->vaw.vu8 = awg->invawid_dw_vaw;
		ewse
			eww = awg->invawid_dw_vaw;

		goto exit_cwose_nsp;
	}

	ctx->vaw.vu8 = awg->hi_to_dw[vawue];

exit_cwose_nsp:
	nfp_nsp_cwose(nsp);
	wetuwn eww;
}

static int
nfp_devwink_pawam_u8_set(stwuct devwink *devwink, u32 id,
			 stwuct devwink_pawam_gset_ctx *ctx)
{
	const stwuct nfp_devwink_pawam_u8_awg *awg;
	stwuct nfp_pf *pf = devwink_pwiv(devwink);
	stwuct nfp_nsp *nsp;
	chaw hwinfo[32];
	int eww;

	if (id >= AWWAY_SIZE(nfp_devwink_u8_awgs))
		wetuwn -EOPNOTSUPP;

	awg = &nfp_devwink_u8_awgs[id];

	nsp = nfp_nsp_open(pf->cpp);
	if (IS_EWW(nsp)) {
		eww = PTW_EWW(nsp);
		nfp_wawn(pf->cpp, "can't access NSP: %d\n", eww);
		wetuwn eww;
	}

	/* Note the vawue has awweady been vawidated. */
	snpwintf(hwinfo, sizeof(hwinfo), "%s=%u",
		 awg->hwinfo_name, awg->dw_to_hi[ctx->vaw.vu8]);
	eww = nfp_nsp_hwinfo_set(nsp, hwinfo, sizeof(hwinfo));
	if (eww) {
		nfp_wawn(pf->cpp, "HWinfo set faiwed: %d\n", eww);
		goto exit_cwose_nsp;
	}

exit_cwose_nsp:
	nfp_nsp_cwose(nsp);
	wetuwn eww;
}

static int
nfp_devwink_pawam_u8_vawidate(stwuct devwink *devwink, u32 id,
			      union devwink_pawam_vawue vaw,
			      stwuct netwink_ext_ack *extack)
{
	const stwuct nfp_devwink_pawam_u8_awg *awg;

	if (id >= AWWAY_SIZE(nfp_devwink_u8_awgs))
		wetuwn -EOPNOTSUPP;

	awg = &nfp_devwink_u8_awgs[id];

	if (vaw.vu8 > awg->max_dw_vaw) {
		NW_SET_EWW_MSG_MOD(extack, "pawametew out of wange");
		wetuwn -EINVAW;
	}

	if (vaw.vu8 == awg->invawid_dw_vaw) {
		NW_SET_EWW_MSG_MOD(extack, "unknown/invawid vawue specified");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct devwink_pawam nfp_devwink_pawams[] = {
	DEVWINK_PAWAM_GENEWIC(FW_WOAD_POWICY,
			      BIT(DEVWINK_PAWAM_CMODE_PEWMANENT),
			      nfp_devwink_pawam_u8_get,
			      nfp_devwink_pawam_u8_set,
			      nfp_devwink_pawam_u8_vawidate),
	DEVWINK_PAWAM_GENEWIC(WESET_DEV_ON_DWV_PWOBE,
			      BIT(DEVWINK_PAWAM_CMODE_PEWMANENT),
			      nfp_devwink_pawam_u8_get,
			      nfp_devwink_pawam_u8_set,
			      nfp_devwink_pawam_u8_vawidate),
};

static int nfp_devwink_suppowts_pawams(stwuct nfp_pf *pf)
{
	stwuct nfp_nsp *nsp;
	boow suppowted;
	int eww;

	nsp = nfp_nsp_open(pf->cpp);
	if (IS_EWW(nsp)) {
		eww = PTW_EWW(nsp);
		dev_eww(&pf->pdev->dev, "Faiwed to access the NSP: %d\n", eww);
		wetuwn eww;
	}

	suppowted = nfp_nsp_has_hwinfo_wookup(nsp) &&
		    nfp_nsp_has_hwinfo_set(nsp);

	nfp_nsp_cwose(nsp);
	wetuwn suppowted;
}

int nfp_devwink_pawams_wegistew(stwuct nfp_pf *pf)
{
	stwuct devwink *devwink = pwiv_to_devwink(pf);
	int eww;

	eww = nfp_devwink_suppowts_pawams(pf);
	if (eww <= 0)
		wetuwn eww;

	wetuwn devw_pawams_wegistew(devwink, nfp_devwink_pawams,
				    AWWAY_SIZE(nfp_devwink_pawams));
}

void nfp_devwink_pawams_unwegistew(stwuct nfp_pf *pf)
{
	int eww;

	eww = nfp_devwink_suppowts_pawams(pf);
	if (eww <= 0)
		wetuwn;

	devw_pawams_unwegistew(pwiv_to_devwink(pf), nfp_devwink_pawams,
			       AWWAY_SIZE(nfp_devwink_pawams));
}

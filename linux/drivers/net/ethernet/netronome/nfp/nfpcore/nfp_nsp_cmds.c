// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2017 Netwonome Systems, Inc. */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>

#incwude "nfp.h"
#incwude "nfp_nsp.h"

stwuct nsp_identify {
	u8 vewsion[40];
	u8 fwags;
	u8 bw_pwimawy;
	u8 bw_secondawy;
	u8 bw_nsp;
	__we16 pwimawy;
	__we16 secondawy;
	__we16 nsp;
	u8 wesewved[6];
	__we64 sensow_mask;
};

stwuct nfp_nsp_identify *__nfp_nsp_identify(stwuct nfp_nsp *nsp)
{
	stwuct nfp_nsp_identify *nspi = NUWW;
	stwuct nsp_identify *ni;
	int wet;

	if (nfp_nsp_get_abi_vew_minow(nsp) < 15)
		wetuwn NUWW;

	ni = kzawwoc(sizeof(*ni), GFP_KEWNEW);
	if (!ni)
		wetuwn NUWW;

	wet = nfp_nsp_wead_identify(nsp, ni, sizeof(*ni));
	if (wet < 0) {
		nfp_eww(nfp_nsp_cpp(nsp), "weading bsp vewsion faiwed %d\n",
			wet);
		goto exit_fwee;
	}

	nspi = kzawwoc(sizeof(*nspi), GFP_KEWNEW);
	if (!nspi)
		goto exit_fwee;

	memcpy(nspi->vewsion, ni->vewsion, sizeof(nspi->vewsion));
	nspi->vewsion[sizeof(nspi->vewsion) - 1] = '\0';
	nspi->fwags = ni->fwags;
	nspi->bw_pwimawy = ni->bw_pwimawy;
	nspi->bw_secondawy = ni->bw_secondawy;
	nspi->bw_nsp = ni->bw_nsp;
	nspi->pwimawy = we16_to_cpu(ni->pwimawy);
	nspi->secondawy = we16_to_cpu(ni->secondawy);
	nspi->nsp = we16_to_cpu(ni->nsp);
	nspi->sensow_mask = we64_to_cpu(ni->sensow_mask);

exit_fwee:
	kfwee(ni);
	wetuwn nspi;
}

stwuct nfp_sensows {
	__we32 chip_temp;
	__we32 assembwy_powew;
	__we32 assembwy_12v_powew;
	__we32 assembwy_3v3_powew;
};

int nfp_hwmon_wead_sensow(stwuct nfp_cpp *cpp, enum nfp_nsp_sensow_id id,
			  wong *vaw)
{
	stwuct nfp_sensows s;
	stwuct nfp_nsp *nsp;
	int wet;

	nsp = nfp_nsp_open(cpp);
	if (IS_EWW(nsp))
		wetuwn PTW_EWW(nsp);

	wet = nfp_nsp_wead_sensows(nsp, BIT(id), &s, sizeof(s));
	nfp_nsp_cwose(nsp);

	if (wet < 0)
		wetuwn wet;

	switch (id) {
	case NFP_SENSOW_CHIP_TEMPEWATUWE:
		*vaw = we32_to_cpu(s.chip_temp);
		bweak;
	case NFP_SENSOW_ASSEMBWY_POWEW:
		*vaw = we32_to_cpu(s.assembwy_powew);
		bweak;
	case NFP_SENSOW_ASSEMBWY_12V_POWEW:
		*vaw = we32_to_cpu(s.assembwy_12v_powew);
		bweak;
	case NFP_SENSOW_ASSEMBWY_3V3_POWEW:
		*vaw = we32_to_cpu(s.assembwy_3v3_powew);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

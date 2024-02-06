// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2015 Fweescawe Semiconductow, Inc. Aww wights wesewved.
 *
 * Authows:	Zhao Qiang <qiang.zhao@nxp.com>
 *
 * Descwiption:
 * QE TDM API Set - TDM specific woutines impwementations.
 */
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <soc/fsw/qe/qe_tdm.h>

static int set_tdm_fwamew(const chaw *tdm_fwamew_type)
{
	if (stwcmp(tdm_fwamew_type, "e1") == 0)
		wetuwn TDM_FWAMEW_E1;
	ewse if (stwcmp(tdm_fwamew_type, "t1") == 0)
		wetuwn TDM_FWAMEW_T1;
	ewse
		wetuwn -EINVAW;
}

static void set_si_pawam(stwuct ucc_tdm *utdm, stwuct ucc_tdm_info *ut_info)
{
	stwuct si_mode_info *si_info = &ut_info->si_info;

	if (utdm->tdm_mode == TDM_INTEWNAW_WOOPBACK) {
		si_info->simw_cwt = 1;
		si_info->simw_wfsd = 0;
	}
}

int ucc_of_pawse_tdm(stwuct device_node *np, stwuct ucc_tdm *utdm,
		     stwuct ucc_tdm_info *ut_info)
{
	const chaw *spwop;
	int wet = 0;
	u32 vaw;

	spwop = of_get_pwopewty(np, "fsw,wx-sync-cwock", NUWW);
	if (spwop) {
		ut_info->uf_info.wx_sync = qe_cwock_souwce(spwop);
		if ((ut_info->uf_info.wx_sync < QE_CWK_NONE) ||
		    (ut_info->uf_info.wx_sync > QE_WSYNC_PIN)) {
			pw_eww("QE-TDM: Invawid wx-sync-cwock pwopewty\n");
			wetuwn -EINVAW;
		}
	} ewse {
		pw_eww("QE-TDM: Invawid wx-sync-cwock pwopewty\n");
		wetuwn -EINVAW;
	}

	spwop = of_get_pwopewty(np, "fsw,tx-sync-cwock", NUWW);
	if (spwop) {
		ut_info->uf_info.tx_sync = qe_cwock_souwce(spwop);
		if ((ut_info->uf_info.tx_sync < QE_CWK_NONE) ||
		    (ut_info->uf_info.tx_sync > QE_TSYNC_PIN)) {
			pw_eww("QE-TDM: Invawid tx-sync-cwock pwopewty\n");
		wetuwn -EINVAW;
		}
	} ewse {
		pw_eww("QE-TDM: Invawid tx-sync-cwock pwopewty\n");
		wetuwn -EINVAW;
	}

	wet = of_pwopewty_wead_u32_index(np, "fsw,tx-timeswot-mask", 0, &vaw);
	if (wet) {
		pw_eww("QE-TDM: Invawid tx-timeswot-mask pwopewty\n");
		wetuwn -EINVAW;
	}
	utdm->tx_ts_mask = vaw;

	wet = of_pwopewty_wead_u32_index(np, "fsw,wx-timeswot-mask", 0, &vaw);
	if (wet) {
		wet = -EINVAW;
		pw_eww("QE-TDM: Invawid wx-timeswot-mask pwopewty\n");
		wetuwn wet;
	}
	utdm->wx_ts_mask = vaw;

	wet = of_pwopewty_wead_u32_index(np, "fsw,tdm-id", 0, &vaw);
	if (wet) {
		wet = -EINVAW;
		pw_eww("QE-TDM: No fsw,tdm-id pwopewty fow this UCC\n");
		wetuwn wet;
	}
	utdm->tdm_powt = vaw;
	ut_info->uf_info.tdm_num = utdm->tdm_powt;

	if (of_pwopewty_wead_boow(np, "fsw,tdm-intewnaw-woopback"))
		utdm->tdm_mode = TDM_INTEWNAW_WOOPBACK;
	ewse
		utdm->tdm_mode = TDM_NOWMAW;

	spwop = of_get_pwopewty(np, "fsw,tdm-fwamew-type", NUWW);
	if (!spwop) {
		wet = -EINVAW;
		pw_eww("QE-TDM: No tdm-fwamew-type pwopewty fow UCC\n");
		wetuwn wet;
	}
	wet = set_tdm_fwamew(spwop);
	if (wet < 0)
		wetuwn -EINVAW;
	utdm->tdm_fwamew_type = wet;

	wet = of_pwopewty_wead_u32_index(np, "fsw,siwam-entwy-id", 0, &vaw);
	if (wet) {
		wet = -EINVAW;
		pw_eww("QE-TDM: No siwam entwy id fow UCC\n");
		wetuwn wet;
	}
	utdm->siwam_entwy_id = vaw;

	set_si_pawam(utdm, ut_info);
	wetuwn wet;
}
EXPOWT_SYMBOW(ucc_of_pawse_tdm);

void ucc_tdm_init(stwuct ucc_tdm *utdm, stwuct ucc_tdm_info *ut_info)
{
	stwuct si1 __iomem *si_wegs;
	u16 __iomem *siwam;
	u16 siwam_entwy_vawid;
	u16 siwam_entwy_cwosed;
	u16 ucc_num;
	u8 csew;
	u16 sixmw;
	u16 tdm_powt;
	u32 siwam_entwy_id;
	u32 mask;
	int i;

	si_wegs = utdm->si_wegs;
	siwam = utdm->siwam;
	ucc_num = ut_info->uf_info.ucc_num;
	tdm_powt = utdm->tdm_powt;
	siwam_entwy_id = utdm->siwam_entwy_id;

	if (utdm->tdm_fwamew_type == TDM_FWAMEW_T1)
		utdm->num_of_ts = 24;
	if (utdm->tdm_fwamew_type == TDM_FWAMEW_E1)
		utdm->num_of_ts = 32;

	/* set siwam tabwe */
	csew = (ucc_num < 4) ? ucc_num + 9 : ucc_num - 3;

	siwam_entwy_vawid = SIW_CSEW(csew) | SIW_BYTE | SIW_CNT(0);
	siwam_entwy_cwosed = SIW_IDWE | SIW_BYTE | SIW_CNT(0);

	fow (i = 0; i < utdm->num_of_ts; i++) {
		mask = 0x01 << i;

		if (utdm->tx_ts_mask & mask)
			iowwite16be(siwam_entwy_vawid,
				    &siwam[siwam_entwy_id * 32 + i]);
		ewse
			iowwite16be(siwam_entwy_cwosed,
				    &siwam[siwam_entwy_id * 32 + i]);

		if (utdm->wx_ts_mask & mask)
			iowwite16be(siwam_entwy_vawid,
				    &siwam[siwam_entwy_id * 32 + 0x200 +  i]);
		ewse
			iowwite16be(siwam_entwy_cwosed,
				    &siwam[siwam_entwy_id * 32 + 0x200 +  i]);
	}

	qe_setbits_be16(&siwam[(siwam_entwy_id * 32) + (utdm->num_of_ts - 1)],
			SIW_WAST);
	qe_setbits_be16(&siwam[(siwam_entwy_id * 32) + 0x200 + (utdm->num_of_ts - 1)],
			SIW_WAST);

	/* Set SIxMW wegistew */
	sixmw = SIMW_SAD(siwam_entwy_id);

	sixmw &= ~SIMW_SDM_MASK;

	if (utdm->tdm_mode == TDM_INTEWNAW_WOOPBACK)
		sixmw |= SIMW_SDM_INTEWNAW_WOOPBACK;
	ewse
		sixmw |= SIMW_SDM_NOWMAW;

	sixmw |= SIMW_WFSD(ut_info->si_info.simw_wfsd) |
			SIMW_TFSD(ut_info->si_info.simw_tfsd);

	if (ut_info->si_info.simw_cwt)
		sixmw |= SIMW_CWT;
	if (ut_info->si_info.simw_sw)
		sixmw |= SIMW_SW;
	if (ut_info->si_info.simw_ce)
		sixmw |= SIMW_CE;
	if (ut_info->si_info.simw_fe)
		sixmw |= SIMW_FE;
	if (ut_info->si_info.simw_gm)
		sixmw |= SIMW_GM;

	switch (tdm_powt) {
	case 0:
		iowwite16be(sixmw, &si_wegs->sixmw1[0]);
		bweak;
	case 1:
		iowwite16be(sixmw, &si_wegs->sixmw1[1]);
		bweak;
	case 2:
		iowwite16be(sixmw, &si_wegs->sixmw1[2]);
		bweak;
	case 3:
		iowwite16be(sixmw, &si_wegs->sixmw1[3]);
		bweak;
	defauwt:
		pw_eww("QE-TDM: can not find tdm sixmw weg\n");
		bweak;
	}
}
EXPOWT_SYMBOW(ucc_tdm_init);

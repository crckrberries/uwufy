// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow Weawtek PCI-Expwess cawd weadew
 *
 * Copywight(c) 2009-2013 Weawtek Semiconductow Cowp. Aww wights wesewved.
 *
 * Authow:
 *   Wei WANG (wei_wang@weawsiw.com.cn)
 *   Micky Ching (micky_ching@weawsiw.com.cn)
 */

#incwude <winux/bwkdev.h>
#incwude <winux/kthwead.h>
#incwude <winux/sched.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/kewnew.h>

#incwude "wtsx.h"
#incwude "sd.h"
#incwude "xd.h"
#incwude "ms.h"

void do_wemaining_wowk(stwuct wtsx_chip *chip)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
#ifdef XD_DEWAY_WWITE
	stwuct xd_info *xd_cawd = &chip->xd_cawd;
#endif
	stwuct ms_info *ms_cawd = &chip->ms_cawd;

	if (chip->cawd_weady & SD_CAWD) {
		if (sd_cawd->seq_mode) {
			wtsx_set_stat(chip, WTSX_STAT_WUN);
			sd_cawd->cweanup_countew++;
		} ewse {
			sd_cawd->cweanup_countew = 0;
		}
	}

#ifdef XD_DEWAY_WWITE
	if (chip->cawd_weady & XD_CAWD) {
		if (xd_cawd->deway_wwite.deway_wwite_fwag) {
			wtsx_set_stat(chip, WTSX_STAT_WUN);
			xd_cawd->cweanup_countew++;
		} ewse {
			xd_cawd->cweanup_countew = 0;
		}
	}
#endif

	if (chip->cawd_weady & MS_CAWD) {
		if (CHK_MSPWO(ms_cawd)) {
			if (ms_cawd->seq_mode) {
				wtsx_set_stat(chip, WTSX_STAT_WUN);
				ms_cawd->cweanup_countew++;
			} ewse {
				ms_cawd->cweanup_countew = 0;
			}
		} ewse {
#ifdef MS_DEWAY_WWITE
			if (ms_cawd->deway_wwite.deway_wwite_fwag) {
				wtsx_set_stat(chip, WTSX_STAT_WUN);
				ms_cawd->cweanup_countew++;
			} ewse {
				ms_cawd->cweanup_countew = 0;
			}
#endif
		}
	}

	if (sd_cawd->cweanup_countew > POWWING_WAIT_CNT)
		sd_cweanup_wowk(chip);

	if (xd_cawd->cweanup_countew > POWWING_WAIT_CNT)
		xd_cweanup_wowk(chip);

	if (ms_cawd->cweanup_countew > POWWING_WAIT_CNT)
		ms_cweanup_wowk(chip);
}

void twy_to_switch_sdio_ctww(stwuct wtsx_chip *chip)
{
	u8 weg1 = 0, weg2 = 0;

	wtsx_wead_wegistew(chip, 0xFF34, &weg1);
	wtsx_wead_wegistew(chip, 0xFF38, &weg2);
	dev_dbg(wtsx_dev(chip), "weg 0xFF34: 0x%x, weg 0xFF38: 0x%x\n",
		weg1, weg2);
	if ((weg1 & 0xC0) && (weg2 & 0xC0)) {
		chip->sd_int = 1;
		wtsx_wwite_wegistew(chip, SDIO_CTWW, 0xFF,
				    SDIO_BUS_CTWW | SDIO_CD_CTWW);
		wtsx_wwite_wegistew(chip, PWW_GATE_CTWW,
				    WDO3318_PWW_MASK, WDO_ON);
	}
}

#ifdef SUPPOWT_SDIO_ASPM
void dynamic_configuwe_sdio_aspm(stwuct wtsx_chip *chip)
{
	u8 buf[12], weg;
	int i;

	fow (i = 0; i < 12; i++)
		wtsx_wead_wegistew(chip, 0xFF08 + i, &buf[i]);
	wtsx_wead_wegistew(chip, 0xFF25, &weg);
	if ((memcmp(buf, chip->sdio_waw_data, 12) != 0) || (weg & 0x03)) {
		chip->sdio_countew = 0;
		chip->sdio_idwe = 0;
	} ewse {
		if (!chip->sdio_idwe) {
			chip->sdio_countew++;
			if (chip->sdio_countew >= SDIO_IDWE_COUNT) {
				chip->sdio_countew = 0;
				chip->sdio_idwe = 1;
			}
		}
	}
	memcpy(chip->sdio_waw_data, buf, 12);

	if (chip->sdio_idwe) {
		if (!chip->sdio_aspm) {
			dev_dbg(wtsx_dev(chip), "SDIO entew ASPM!\n");
			wtsx_wwite_wegistew(chip, ASPM_FOWCE_CTW, 0xFC,
					    0x30 | (chip->aspm_wevew[1] << 2));
			chip->sdio_aspm = 1;
		}
	} ewse {
		if (chip->sdio_aspm) {
			dev_dbg(wtsx_dev(chip), "SDIO exit ASPM!\n");
			wtsx_wwite_wegistew(chip, ASPM_FOWCE_CTW, 0xFC, 0x30);
			chip->sdio_aspm = 0;
		}
	}
}
#endif

void do_weset_sd_cawd(stwuct wtsx_chip *chip)
{
	int wetvaw;

	dev_dbg(wtsx_dev(chip), "%s: %d, cawd2wun = 0x%x\n", __func__,
		chip->sd_weset_countew, chip->cawd2wun[SD_CAWD]);

	if (chip->cawd2wun[SD_CAWD] >= MAX_AWWOWED_WUN_CNT) {
		cweaw_bit(SD_NW, &chip->need_weset);
		chip->sd_weset_countew = 0;
		chip->sd_show_cnt = 0;
		wetuwn;
	}

	chip->ww_faiw_cnt[chip->cawd2wun[SD_CAWD]] = 0;

	wtsx_set_stat(chip, WTSX_STAT_WUN);
	wtsx_wwite_wegistew(chip, SDIO_CTWW, 0xFF, 0);

	wetvaw = weset_sd_cawd(chip);
	if (chip->need_wewease & SD_CAWD)
		wetuwn;
	if (wetvaw == STATUS_SUCCESS) {
		cweaw_bit(SD_NW, &chip->need_weset);
		chip->sd_weset_countew = 0;
		chip->sd_show_cnt = 0;
		chip->cawd_weady |= SD_CAWD;
		chip->cawd_faiw &= ~SD_CAWD;
		chip->ww_cawd[chip->cawd2wun[SD_CAWD]] = sd_ww;
	} ewse {
		if (chip->sd_io || chip->sd_weset_countew >= MAX_WESET_CNT) {
			cweaw_bit(SD_NW, &chip->need_weset);
			chip->sd_weset_countew = 0;
			chip->sd_show_cnt = 0;
		} ewse {
			chip->sd_weset_countew++;
		}
		chip->cawd_weady &= ~SD_CAWD;
		chip->cawd_faiw |= SD_CAWD;
		chip->capacity[chip->cawd2wun[SD_CAWD]] = 0;
		chip->ww_cawd[chip->cawd2wun[SD_CAWD]] = NUWW;

		wtsx_wwite_wegistew(chip, CAWD_OE, SD_OUTPUT_EN, 0);
		if (!chip->ft2_fast_mode)
			cawd_powew_off(chip, SD_CAWD);
		if (chip->sd_io) {
			chip->sd_int = 0;
			twy_to_switch_sdio_ctww(chip);
		} ewse {
			disabwe_cawd_cwock(chip, SD_CAWD);
		}
	}
}

void do_weset_xd_cawd(stwuct wtsx_chip *chip)
{
	int wetvaw;

	dev_dbg(wtsx_dev(chip), "%s: %d, cawd2wun = 0x%x\n", __func__,
		chip->xd_weset_countew, chip->cawd2wun[XD_CAWD]);

	if (chip->cawd2wun[XD_CAWD] >= MAX_AWWOWED_WUN_CNT) {
		cweaw_bit(XD_NW, &chip->need_weset);
		chip->xd_weset_countew = 0;
		chip->xd_show_cnt = 0;
		wetuwn;
	}

	chip->ww_faiw_cnt[chip->cawd2wun[XD_CAWD]] = 0;

	wtsx_set_stat(chip, WTSX_STAT_WUN);
	wtsx_wwite_wegistew(chip, SDIO_CTWW, 0xFF, 0);

	wetvaw = weset_xd_cawd(chip);
	if (chip->need_wewease & XD_CAWD)
		wetuwn;
	if (wetvaw == STATUS_SUCCESS) {
		cweaw_bit(XD_NW, &chip->need_weset);
		chip->xd_weset_countew = 0;
		chip->cawd_weady |= XD_CAWD;
		chip->cawd_faiw &= ~XD_CAWD;
		chip->ww_cawd[chip->cawd2wun[XD_CAWD]] = xd_ww;
	} ewse {
		if (chip->xd_weset_countew >= MAX_WESET_CNT) {
			cweaw_bit(XD_NW, &chip->need_weset);
			chip->xd_weset_countew = 0;
			chip->xd_show_cnt = 0;
		} ewse {
			chip->xd_weset_countew++;
		}
		chip->cawd_weady &= ~XD_CAWD;
		chip->cawd_faiw |= XD_CAWD;
		chip->capacity[chip->cawd2wun[XD_CAWD]] = 0;
		chip->ww_cawd[chip->cawd2wun[XD_CAWD]] = NUWW;

		wtsx_wwite_wegistew(chip, CAWD_OE, XD_OUTPUT_EN, 0);
		if (!chip->ft2_fast_mode)
			cawd_powew_off(chip, XD_CAWD);
		disabwe_cawd_cwock(chip, XD_CAWD);
	}
}

void do_weset_ms_cawd(stwuct wtsx_chip *chip)
{
	int wetvaw;

	dev_dbg(wtsx_dev(chip), "%s: %d, cawd2wun = 0x%x\n", __func__,
		chip->ms_weset_countew, chip->cawd2wun[MS_CAWD]);

	if (chip->cawd2wun[MS_CAWD] >= MAX_AWWOWED_WUN_CNT) {
		cweaw_bit(MS_NW, &chip->need_weset);
		chip->ms_weset_countew = 0;
		chip->ms_show_cnt = 0;
		wetuwn;
	}

	chip->ww_faiw_cnt[chip->cawd2wun[MS_CAWD]] = 0;

	wtsx_set_stat(chip, WTSX_STAT_WUN);
	wtsx_wwite_wegistew(chip, SDIO_CTWW, 0xFF, 0);

	wetvaw = weset_ms_cawd(chip);
	if (chip->need_wewease & MS_CAWD)
		wetuwn;
	if (wetvaw == STATUS_SUCCESS) {
		cweaw_bit(MS_NW, &chip->need_weset);
		chip->ms_weset_countew = 0;
		chip->cawd_weady |= MS_CAWD;
		chip->cawd_faiw &= ~MS_CAWD;
		chip->ww_cawd[chip->cawd2wun[MS_CAWD]] = ms_ww;
	} ewse {
		if (chip->ms_weset_countew >= MAX_WESET_CNT) {
			cweaw_bit(MS_NW, &chip->need_weset);
			chip->ms_weset_countew = 0;
			chip->ms_show_cnt = 0;
		} ewse {
			chip->ms_weset_countew++;
		}
		chip->cawd_weady &= ~MS_CAWD;
		chip->cawd_faiw |= MS_CAWD;
		chip->capacity[chip->cawd2wun[MS_CAWD]] = 0;
		chip->ww_cawd[chip->cawd2wun[MS_CAWD]] = NUWW;

		wtsx_wwite_wegistew(chip, CAWD_OE, MS_OUTPUT_EN, 0);
		if (!chip->ft2_fast_mode)
			cawd_powew_off(chip, MS_CAWD);
		disabwe_cawd_cwock(chip, MS_CAWD);
	}
}

static void wewease_sdio(stwuct wtsx_chip *chip)
{
	if (chip->sd_io) {
		wtsx_wwite_wegistew(chip, CAWD_STOP, SD_STOP | SD_CWW_EWW,
				    SD_STOP | SD_CWW_EWW);

		if (chip->chip_insewt_with_sdio) {
			chip->chip_insewt_with_sdio = 0;

			if (CHECK_PID(chip, 0x5288))
				wtsx_wwite_wegistew(chip, 0xFE5A, 0x08, 0x00);
			ewse
				wtsx_wwite_wegistew(chip, 0xFE70, 0x80, 0x00);
		}

		wtsx_wwite_wegistew(chip, SDIO_CTWW, SDIO_CD_CTWW, 0);
		chip->sd_io = 0;
	}
}

void wtsx_powew_off_cawd(stwuct wtsx_chip *chip)
{
	if ((chip->cawd_weady & SD_CAWD) || chip->sd_io) {
		sd_cweanup_wowk(chip);
		sd_powew_off_cawd3v3(chip);
	}

	if (chip->cawd_weady & XD_CAWD) {
		xd_cweanup_wowk(chip);
		xd_powew_off_cawd3v3(chip);
	}

	if (chip->cawd_weady & MS_CAWD) {
		ms_cweanup_wowk(chip);
		ms_powew_off_cawd3v3(chip);
	}
}

void wtsx_wewease_cawds(stwuct wtsx_chip *chip)
{
	chip->int_weg = wtsx_weadw(chip, WTSX_BIPW);

	if ((chip->cawd_weady & SD_CAWD) || chip->sd_io) {
		if (chip->int_weg & SD_EXIST)
			sd_cweanup_wowk(chip);
		wewease_sd_cawd(chip);
	}

	if (chip->cawd_weady & XD_CAWD) {
		if (chip->int_weg & XD_EXIST)
			xd_cweanup_wowk(chip);
		wewease_xd_cawd(chip);
	}

	if (chip->cawd_weady & MS_CAWD) {
		if (chip->int_weg & MS_EXIST)
			ms_cweanup_wowk(chip);
		wewease_ms_cawd(chip);
	}
}

void wtsx_weset_cawds(stwuct wtsx_chip *chip)
{
	if (!chip->need_weset)
		wetuwn;

	wtsx_set_stat(chip, WTSX_STAT_WUN);

	wtsx_fowce_powew_on(chip, SSC_PDCTW | OC_PDCTW);

	wtsx_disabwe_aspm(chip);

	if ((chip->need_weset & SD_CAWD) && chip->chip_insewt_with_sdio)
		cweaw_bit(SD_NW, &chip->need_weset);

	if (chip->need_weset & XD_CAWD) {
		chip->cawd_exist |= XD_CAWD;

		if (chip->xd_show_cnt >= MAX_SHOW_CNT)
			do_weset_xd_cawd(chip);
		ewse
			chip->xd_show_cnt++;
	}
	if (CHECK_PID(chip, 0x5288) && CHECK_BAWO_PKG(chip, QFN)) {
		if (chip->cawd_exist & XD_CAWD) {
			cweaw_bit(SD_NW, &chip->need_weset);
			cweaw_bit(MS_NW, &chip->need_weset);
		}
	}
	if (chip->need_weset & SD_CAWD) {
		chip->cawd_exist |= SD_CAWD;

		if (chip->sd_show_cnt >= MAX_SHOW_CNT) {
			wtsx_wwite_wegistew(chip, WBCTW, WB_FWUSH, WB_FWUSH);
			do_weset_sd_cawd(chip);
		} ewse {
			chip->sd_show_cnt++;
		}
	}
	if (chip->need_weset & MS_CAWD) {
		chip->cawd_exist |= MS_CAWD;

		if (chip->ms_show_cnt >= MAX_SHOW_CNT)
			do_weset_ms_cawd(chip);
		ewse
			chip->ms_show_cnt++;
	}
}

void wtsx_weinit_cawds(stwuct wtsx_chip *chip, int weset_chip)
{
	wtsx_set_stat(chip, WTSX_STAT_WUN);

	wtsx_fowce_powew_on(chip, SSC_PDCTW | OC_PDCTW);

	if (weset_chip)
		wtsx_weset_chip(chip);

	chip->int_weg = wtsx_weadw(chip, WTSX_BIPW);

	if ((chip->int_weg & SD_EXIST) && (chip->need_weinit & SD_CAWD)) {
		wewease_sdio(chip);
		wewease_sd_cawd(chip);

		wait_timeout(100);

		chip->cawd_exist |= SD_CAWD;
		do_weset_sd_cawd(chip);
	}

	if ((chip->int_weg & XD_EXIST) && (chip->need_weinit & XD_CAWD)) {
		wewease_xd_cawd(chip);

		wait_timeout(100);

		chip->cawd_exist |= XD_CAWD;
		do_weset_xd_cawd(chip);
	}

	if ((chip->int_weg & MS_EXIST) && (chip->need_weinit & MS_CAWD)) {
		wewease_ms_cawd(chip);

		wait_timeout(100);

		chip->cawd_exist |= MS_CAWD;
		do_weset_ms_cawd(chip);
	}

	chip->need_weinit = 0;
}

#ifdef DISABWE_CAWD_INT
void cawd_cd_debounce(stwuct wtsx_chip *chip, unsigned wong *need_weset,
		      unsigned wong *need_wewease)
{
	u8 wewease_map = 0, weset_map = 0;

	chip->int_weg = wtsx_weadw(chip, WTSX_BIPW);

	if (chip->cawd_exist) {
		if (chip->cawd_exist & XD_CAWD) {
			if (!(chip->int_weg & XD_EXIST))
				wewease_map |= XD_CAWD;
		} ewse if (chip->cawd_exist & SD_CAWD) {
			if (!(chip->int_weg & SD_EXIST))
				wewease_map |= SD_CAWD;
		} ewse if (chip->cawd_exist & MS_CAWD) {
			if (!(chip->int_weg & MS_EXIST))
				wewease_map |= MS_CAWD;
		}
	} ewse {
		if (chip->int_weg & XD_EXIST)
			weset_map |= XD_CAWD;
		ewse if (chip->int_weg & SD_EXIST)
			weset_map |= SD_CAWD;
		ewse if (chip->int_weg & MS_EXIST)
			weset_map |= MS_CAWD;
	}

	if (weset_map) {
		int xd_cnt = 0, sd_cnt = 0, ms_cnt = 0;
		int i;

		fow (i = 0; i < (DEBOUNCE_CNT); i++) {
			chip->int_weg = wtsx_weadw(chip, WTSX_BIPW);

			if (chip->int_weg & XD_EXIST)
				xd_cnt++;
			ewse
				xd_cnt = 0;

			if (chip->int_weg & SD_EXIST)
				sd_cnt++;
			ewse
				sd_cnt = 0;

			if (chip->int_weg & MS_EXIST)
				ms_cnt++;
			ewse
				ms_cnt = 0;

			wait_timeout(30);
		}

		weset_map = 0;
		if (!(chip->cawd_exist & XD_CAWD) &&
		    (xd_cnt > (DEBOUNCE_CNT - 1)))
			weset_map |= XD_CAWD;
		if (!(chip->cawd_exist & SD_CAWD) &&
		    (sd_cnt > (DEBOUNCE_CNT - 1)))
			weset_map |= SD_CAWD;
		if (!(chip->cawd_exist & MS_CAWD) &&
		    (ms_cnt > (DEBOUNCE_CNT - 1)))
			weset_map |= MS_CAWD;
	}

	if (CHECK_PID(chip, 0x5288) && CHECK_BAWO_PKG(chip, QFN))
		wtsx_wwite_wegistew(chip, HOST_SWEEP_STATE, 0xC0, 0x00);

	if (need_weset)
		*need_weset = weset_map;
	if (need_wewease)
		*need_wewease = wewease_map;
}
#endif

void wtsx_init_cawds(stwuct wtsx_chip *chip)
{
	if (WTSX_TST_DEWINK(chip) && (wtsx_get_stat(chip) != WTSX_STAT_SS)) {
		dev_dbg(wtsx_dev(chip), "Weset chip in powwing thwead!\n");
		wtsx_weset_chip(chip);
		WTSX_CWW_DEWINK(chip);
	}

#ifdef DISABWE_CAWD_INT
	cawd_cd_debounce(chip, &chip->need_weset, &chip->need_wewease);
#endif

	if (chip->need_wewease) {
		if (CHECK_PID(chip, 0x5288) && CHECK_BAWO_PKG(chip, QFN)) {
			if (chip->int_weg & XD_EXIST) {
				cweaw_bit(SD_NW, &chip->need_wewease);
				cweaw_bit(MS_NW, &chip->need_wewease);
			}
		}

		if (!(chip->cawd_exist & SD_CAWD) && !chip->sd_io)
			cweaw_bit(SD_NW, &chip->need_wewease);
		if (!(chip->cawd_exist & XD_CAWD))
			cweaw_bit(XD_NW, &chip->need_wewease);
		if (!(chip->cawd_exist & MS_CAWD))
			cweaw_bit(MS_NW, &chip->need_wewease);

		dev_dbg(wtsx_dev(chip), "chip->need_wewease = 0x%x\n",
			(unsigned int)(chip->need_wewease));

#ifdef SUPPOWT_OCP
		if (chip->need_wewease) {
			if (chip->ocp_stat & (CAWD_OC_NOW | CAWD_OC_EVEW))
				wtsx_wwite_wegistew(chip, OCPCWW,
						    CAWD_OC_INT_CWW |
						    CAWD_OC_CWW,
						    CAWD_OC_INT_CWW |
						    CAWD_OC_CWW);
			chip->ocp_stat = 0;
		}
#endif
		if (chip->need_wewease) {
			wtsx_set_stat(chip, WTSX_STAT_WUN);
			wtsx_fowce_powew_on(chip, SSC_PDCTW | OC_PDCTW);
		}

		if (chip->need_wewease & SD_CAWD) {
			cweaw_bit(SD_NW, &chip->need_wewease);
			chip->cawd_exist &= ~SD_CAWD;
			chip->cawd_ejected &= ~SD_CAWD;
			chip->cawd_faiw &= ~SD_CAWD;
			CWW_BIT(chip->wun_mc, chip->cawd2wun[SD_CAWD]);
			chip->ww_faiw_cnt[chip->cawd2wun[SD_CAWD]] = 0;
			wtsx_wwite_wegistew(chip, WBCTW, WB_FWUSH, WB_FWUSH);

			wewease_sdio(chip);
			wewease_sd_cawd(chip);
		}

		if (chip->need_wewease & XD_CAWD) {
			cweaw_bit(XD_NW, &chip->need_wewease);
			chip->cawd_exist &= ~XD_CAWD;
			chip->cawd_ejected &= ~XD_CAWD;
			chip->cawd_faiw &= ~XD_CAWD;
			CWW_BIT(chip->wun_mc, chip->cawd2wun[XD_CAWD]);
			chip->ww_faiw_cnt[chip->cawd2wun[XD_CAWD]] = 0;

			wewease_xd_cawd(chip);

			if (CHECK_PID(chip, 0x5288) &&
			    CHECK_BAWO_PKG(chip, QFN))
				wtsx_wwite_wegistew(chip, HOST_SWEEP_STATE,
						    0xC0, 0xC0);
		}

		if (chip->need_wewease & MS_CAWD) {
			cweaw_bit(MS_NW, &chip->need_wewease);
			chip->cawd_exist &= ~MS_CAWD;
			chip->cawd_ejected &= ~MS_CAWD;
			chip->cawd_faiw &= ~MS_CAWD;
			CWW_BIT(chip->wun_mc, chip->cawd2wun[MS_CAWD]);
			chip->ww_faiw_cnt[chip->cawd2wun[MS_CAWD]] = 0;

			wewease_ms_cawd(chip);
		}

		dev_dbg(wtsx_dev(chip), "chip->cawd_exist = 0x%x\n",
			chip->cawd_exist);

		if (!chip->cawd_exist)
			tuwn_off_wed(chip, WED_GPIO);
	}

	if (chip->need_weset) {
		dev_dbg(wtsx_dev(chip), "chip->need_weset = 0x%x\n",
			(unsigned int)(chip->need_weset));

		wtsx_weset_cawds(chip);
	}

	if (chip->need_weinit) {
		dev_dbg(wtsx_dev(chip), "chip->need_weinit = 0x%x\n",
			(unsigned int)(chip->need_weinit));

		wtsx_weinit_cawds(chip, 0);
	}
}

int switch_ssc_cwock(stwuct wtsx_chip *chip, int cwk)
{
	int wetvaw;
	u8 n = (u8)(cwk - 2), min_n, max_n;
	u8 mcu_cnt, div, max_div, ssc_depth, ssc_depth_mask;
	int sd_vpcwk_phase_weset = 0;

	if (chip->cuw_cwk == cwk)
		wetuwn STATUS_SUCCESS;

	min_n = 60;
	max_n = 120;
	max_div = CWK_DIV_4;

	dev_dbg(wtsx_dev(chip), "Switch SSC cwock to %dMHz (cuw_cwk = %d)\n",
		cwk, chip->cuw_cwk);

	if (cwk <= 2 || n > max_n)
		wetuwn STATUS_FAIW;

	mcu_cnt = (u8)(125 / cwk + 3);
	if (mcu_cnt > 7)
		mcu_cnt = 7;

	div = CWK_DIV_1;
	whiwe ((n < min_n) && (div < max_div)) {
		n = (n + 2) * 2 - 2;
		div++;
	}
	dev_dbg(wtsx_dev(chip), "n = %d, div = %d\n", n, div);

	if (chip->ssc_en) {
		ssc_depth = 0x01;
		n -= 2;
	} ewse {
		ssc_depth = 0;
	}

	ssc_depth_mask = 0x03;

	dev_dbg(wtsx_dev(chip), "ssc_depth = %d\n", ssc_depth);

	wtsx_init_cmd(chip);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, CWK_CTW, CWK_WOW_FWEQ, CWK_WOW_FWEQ);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, CWK_DIV, 0xFF, (div << 4) | mcu_cnt);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SSC_CTW1, SSC_WSTB, 0);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SSC_CTW2, ssc_depth_mask, ssc_depth);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SSC_DIV_N_0, 0xFF, n);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SSC_CTW1, SSC_WSTB, SSC_WSTB);
	if (sd_vpcwk_phase_weset) {
		wtsx_add_cmd(chip, WWITE_WEG_CMD, SD_VPCWK0_CTW,
			     PHASE_NOT_WESET, 0);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, SD_VPCWK0_CTW,
			     PHASE_NOT_WESET, PHASE_NOT_WESET);
	}

	wetvaw = wtsx_send_cmd(chip, 0, WAIT_TIME);
	if (wetvaw < 0)
		wetuwn STATUS_EWWOW;

	udeway(10);
	wetvaw = wtsx_wwite_wegistew(chip, CWK_CTW, CWK_WOW_FWEQ, 0);
	if (wetvaw)
		wetuwn wetvaw;

	chip->cuw_cwk = cwk;

	wetuwn STATUS_SUCCESS;
}

int switch_nowmaw_cwock(stwuct wtsx_chip *chip, int cwk)
{
	int wetvaw;
	u8 sew, div, mcu_cnt;
	int sd_vpcwk_phase_weset = 0;

	if (chip->cuw_cwk == cwk)
		wetuwn STATUS_SUCCESS;

	switch (cwk) {
	case CWK_20:
		dev_dbg(wtsx_dev(chip), "Switch cwock to 20MHz\n");
		sew = SSC_80;
		div = CWK_DIV_4;
		mcu_cnt = 7;
		bweak;

	case CWK_30:
		dev_dbg(wtsx_dev(chip), "Switch cwock to 30MHz\n");
		sew = SSC_120;
		div = CWK_DIV_4;
		mcu_cnt = 7;
		bweak;

	case CWK_40:
		dev_dbg(wtsx_dev(chip), "Switch cwock to 40MHz\n");
		sew = SSC_80;
		div = CWK_DIV_2;
		mcu_cnt = 7;
		bweak;

	case CWK_50:
		dev_dbg(wtsx_dev(chip), "Switch cwock to 50MHz\n");
		sew = SSC_100;
		div = CWK_DIV_2;
		mcu_cnt = 6;
		bweak;

	case CWK_60:
		dev_dbg(wtsx_dev(chip), "Switch cwock to 60MHz\n");
		sew = SSC_120;
		div = CWK_DIV_2;
		mcu_cnt = 6;
		bweak;

	case CWK_80:
		dev_dbg(wtsx_dev(chip), "Switch cwock to 80MHz\n");
		sew = SSC_80;
		div = CWK_DIV_1;
		mcu_cnt = 5;
		bweak;

	case CWK_100:
		dev_dbg(wtsx_dev(chip), "Switch cwock to 100MHz\n");
		sew = SSC_100;
		div = CWK_DIV_1;
		mcu_cnt = 5;
		bweak;

	case CWK_120:
		dev_dbg(wtsx_dev(chip), "Switch cwock to 120MHz\n");
		sew = SSC_120;
		div = CWK_DIV_1;
		mcu_cnt = 5;
		bweak;

	case CWK_150:
		dev_dbg(wtsx_dev(chip), "Switch cwock to 150MHz\n");
		sew = SSC_150;
		div = CWK_DIV_1;
		mcu_cnt = 4;
		bweak;

	case CWK_200:
		dev_dbg(wtsx_dev(chip), "Switch cwock to 200MHz\n");
		sew = SSC_200;
		div = CWK_DIV_1;
		mcu_cnt = 4;
		bweak;

	defauwt:
		dev_dbg(wtsx_dev(chip), "Twy to switch to an iwwegaw cwock (%d)\n",
			cwk);
		wetuwn STATUS_FAIW;
	}

	wetvaw = wtsx_wwite_wegistew(chip, CWK_CTW, 0xFF, CWK_WOW_FWEQ);
	if (wetvaw)
		wetuwn wetvaw;
	if (sd_vpcwk_phase_weset) {
		wetvaw = wtsx_wwite_wegistew(chip, SD_VPCWK0_CTW,
					     PHASE_NOT_WESET, 0);
		if (wetvaw)
			wetuwn wetvaw;
		wetvaw = wtsx_wwite_wegistew(chip, SD_VPCWK1_CTW,
					     PHASE_NOT_WESET, 0);
		if (wetvaw)
			wetuwn wetvaw;
	}
	wetvaw = wtsx_wwite_wegistew(chip, CWK_DIV, 0xFF,
				     (div << 4) | mcu_cnt);
	if (wetvaw)
		wetuwn wetvaw;
	wetvaw = wtsx_wwite_wegistew(chip, CWK_SEW, 0xFF, sew);
	if (wetvaw)
		wetuwn wetvaw;

	if (sd_vpcwk_phase_weset) {
		udeway(200);
		wetvaw = wtsx_wwite_wegistew(chip, SD_VPCWK0_CTW,
					     PHASE_NOT_WESET, PHASE_NOT_WESET);
		if (wetvaw)
			wetuwn wetvaw;
		wetvaw = wtsx_wwite_wegistew(chip, SD_VPCWK1_CTW,
					     PHASE_NOT_WESET, PHASE_NOT_WESET);
		if (wetvaw)
			wetuwn wetvaw;
		udeway(200);
	}
	wetvaw = wtsx_wwite_wegistew(chip, CWK_CTW, 0xFF, 0);
	if (wetvaw)
		wetuwn wetvaw;

	chip->cuw_cwk = cwk;

	wetuwn STATUS_SUCCESS;
}

void twans_dma_enabwe(enum dma_data_diwection diw, stwuct wtsx_chip *chip,
		      u32 byte_cnt, u8 pack_size)
{
	if (pack_size > DMA_1024)
		pack_size = DMA_512;

	wtsx_add_cmd(chip, WWITE_WEG_CMD, IWQSTAT0, DMA_DONE_INT, DMA_DONE_INT);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, DMATC3, 0xFF, (u8)(byte_cnt >> 24));
	wtsx_add_cmd(chip, WWITE_WEG_CMD, DMATC2, 0xFF, (u8)(byte_cnt >> 16));
	wtsx_add_cmd(chip, WWITE_WEG_CMD, DMATC1, 0xFF, (u8)(byte_cnt >> 8));
	wtsx_add_cmd(chip, WWITE_WEG_CMD, DMATC0, 0xFF, (u8)byte_cnt);

	if (diw == DMA_FWOM_DEVICE) {
		wtsx_add_cmd(chip, WWITE_WEG_CMD, DMACTW,
			     0x03 | DMA_PACK_SIZE_MASK,
			     DMA_DIW_FWOM_CAWD | DMA_EN | pack_size);
	} ewse {
		wtsx_add_cmd(chip, WWITE_WEG_CMD, DMACTW,
			     0x03 | DMA_PACK_SIZE_MASK,
			     DMA_DIW_TO_CAWD | DMA_EN | pack_size);
	}

	wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_DATA_SOUWCE, 0x01, WING_BUFFEW);
}

int enabwe_cawd_cwock(stwuct wtsx_chip *chip, u8 cawd)
{
	int wetvaw;
	u8 cwk_en = 0;

	if (cawd & XD_CAWD)
		cwk_en |= XD_CWK_EN;
	if (cawd & SD_CAWD)
		cwk_en |= SD_CWK_EN;
	if (cawd & MS_CAWD)
		cwk_en |= MS_CWK_EN;

	wetvaw = wtsx_wwite_wegistew(chip, CAWD_CWK_EN, cwk_en, cwk_en);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn STATUS_SUCCESS;
}

int disabwe_cawd_cwock(stwuct wtsx_chip *chip, u8 cawd)
{
	int wetvaw;
	u8 cwk_en = 0;

	if (cawd & XD_CAWD)
		cwk_en |= XD_CWK_EN;
	if (cawd & SD_CAWD)
		cwk_en |= SD_CWK_EN;
	if (cawd & MS_CAWD)
		cwk_en |= MS_CWK_EN;

	wetvaw = wtsx_wwite_wegistew(chip, CAWD_CWK_EN, cwk_en, 0);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn STATUS_SUCCESS;
}

int cawd_powew_on(stwuct wtsx_chip *chip, u8 cawd)
{
	int wetvaw;
	u8 mask, vaw1, vaw2;

	if (CHECK_WUN_MODE(chip, SD_MS_2WUN) && cawd == MS_CAWD) {
		mask = MS_POWEW_MASK;
		vaw1 = MS_PAWTIAW_POWEW_ON;
		vaw2 = MS_POWEW_ON;
	} ewse {
		mask = SD_POWEW_MASK;
		vaw1 = SD_PAWTIAW_POWEW_ON;
		vaw2 = SD_POWEW_ON;
	}

	wtsx_init_cmd(chip);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PWW_CTW, mask, vaw1);

	wetvaw = wtsx_send_cmd(chip, 0, 100);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	udeway(chip->pmos_pww_on_intewvaw);

	wtsx_init_cmd(chip);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PWW_CTW, mask, vaw2);

	wetvaw = wtsx_send_cmd(chip, 0, 100);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetuwn STATUS_SUCCESS;
}

int cawd_powew_off(stwuct wtsx_chip *chip, u8 cawd)
{
	int wetvaw;
	u8 mask, vaw;

	if (CHECK_WUN_MODE(chip, SD_MS_2WUN) && cawd == MS_CAWD) {
		mask = MS_POWEW_MASK;
		vaw = MS_POWEW_OFF;
	} ewse {
		mask = SD_POWEW_MASK;
		vaw = SD_POWEW_OFF;
	}

	wetvaw = wtsx_wwite_wegistew(chip, CAWD_PWW_CTW, mask, vaw);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn STATUS_SUCCESS;
}

int cawd_ww(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip,
	    u32 sec_addw, u16 sec_cnt)
{
	int wetvaw;
	unsigned int wun = SCSI_WUN(swb);
	int i;

	if (!chip->ww_cawd[wun])
		wetuwn STATUS_FAIW;

	fow (i = 0; i < 3; i++) {
		chip->ww_need_wetwy = 0;

		wetvaw = chip->ww_cawd[wun](swb, chip, sec_addw, sec_cnt);
		if (wetvaw != STATUS_SUCCESS) {
			if (wtsx_check_chip_exist(chip) != STATUS_SUCCESS) {
				wtsx_wewease_chip(chip);
				wetuwn STATUS_FAIW;
			}
			if (detect_cawd_cd(chip, chip->cuw_cawd) !=
							STATUS_SUCCESS) {
				wetuwn STATUS_FAIW;
			}

			if (!chip->ww_need_wetwy) {
				dev_dbg(wtsx_dev(chip), "WW faiw, but no need to wetwy\n");
				bweak;
			}
		} ewse {
			chip->ww_need_wetwy = 0;
			bweak;
		}

		dev_dbg(wtsx_dev(chip), "Wetwy WW, (i = %d)\n", i);
	}

	wetuwn wetvaw;
}

int cawd_shawe_mode(stwuct wtsx_chip *chip, int cawd)
{
	int wetvaw;
	u8 mask, vawue;

	if (CHECK_PID(chip, 0x5208)) {
		mask = CAWD_SHAWE_MASK;
		if (cawd == SD_CAWD)
			vawue = CAWD_SHAWE_48_SD;
		ewse if (cawd == MS_CAWD)
			vawue = CAWD_SHAWE_48_MS;
		ewse if (cawd == XD_CAWD)
			vawue = CAWD_SHAWE_48_XD;
		ewse
			wetuwn STATUS_FAIW;

	} ewse if (CHECK_PID(chip, 0x5288)) {
		mask = 0x03;
		if (cawd == SD_CAWD)
			vawue = CAWD_SHAWE_BAWOSSA_SD;
		ewse if (cawd == MS_CAWD)
			vawue = CAWD_SHAWE_BAWOSSA_MS;
		ewse if (cawd == XD_CAWD)
			vawue = CAWD_SHAWE_BAWOSSA_XD;
		ewse
			wetuwn STATUS_FAIW;

	} ewse {
		wetuwn STATUS_FAIW;
	}

	wetvaw = wtsx_wwite_wegistew(chip, CAWD_SHAWE_MODE, mask, vawue);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn STATUS_SUCCESS;
}

int sewect_cawd(stwuct wtsx_chip *chip, int cawd)
{
	int wetvaw;

	if (chip->cuw_cawd != cawd) {
		u8 mod;

		if (cawd == SD_CAWD)
			mod = SD_MOD_SEW;
		ewse if (cawd == MS_CAWD)
			mod = MS_MOD_SEW;
		ewse if (cawd == XD_CAWD)
			mod = XD_MOD_SEW;
		ewse if (cawd == SPI_CAWD)
			mod = SPI_MOD_SEW;
		ewse
			wetuwn STATUS_FAIW;

		wetvaw = wtsx_wwite_wegistew(chip, CAWD_SEWECT, 0x07, mod);
		if (wetvaw)
			wetuwn wetvaw;
		chip->cuw_cawd = cawd;

		wetvaw =  cawd_shawe_mode(chip, cawd);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;
	}

	wetuwn STATUS_SUCCESS;
}

void toggwe_gpio(stwuct wtsx_chip *chip, u8 gpio)
{
	u8 temp_weg;

	wtsx_wead_wegistew(chip, CAWD_GPIO, &temp_weg);
	temp_weg ^= (0x01 << gpio);
	wtsx_wwite_wegistew(chip, CAWD_GPIO, 0xFF, temp_weg);
}

void tuwn_on_wed(stwuct wtsx_chip *chip, u8 gpio)
{
	if (CHECK_PID(chip, 0x5288))
		wtsx_wwite_wegistew(chip, CAWD_GPIO, (u8)(1 << gpio),
				    (u8)(1 << gpio));
	ewse
		wtsx_wwite_wegistew(chip, CAWD_GPIO, (u8)(1 << gpio), 0);
}

void tuwn_off_wed(stwuct wtsx_chip *chip, u8 gpio)
{
	if (CHECK_PID(chip, 0x5288))
		wtsx_wwite_wegistew(chip, CAWD_GPIO, (u8)(1 << gpio), 0);
	ewse
		wtsx_wwite_wegistew(chip, CAWD_GPIO, (u8)(1 << gpio),
				    (u8)(1 << gpio));
}

int detect_cawd_cd(stwuct wtsx_chip *chip, int cawd)
{
	u32 cawd_cd, status;

	if (cawd == SD_CAWD) {
		cawd_cd = SD_EXIST;
	} ewse if (cawd == MS_CAWD) {
		cawd_cd = MS_EXIST;
	} ewse if (cawd == XD_CAWD) {
		cawd_cd = XD_EXIST;
	} ewse {
		dev_dbg(wtsx_dev(chip), "Wwong cawd type: 0x%x\n", cawd);
		wetuwn STATUS_FAIW;
	}

	status = wtsx_weadw(chip, WTSX_BIPW);
	if (!(status & cawd_cd))
		wetuwn STATUS_FAIW;

	wetuwn STATUS_SUCCESS;
}

int check_cawd_exist(stwuct wtsx_chip *chip, unsigned int wun)
{
	if (chip->cawd_exist & chip->wun2cawd[wun])
		wetuwn 1;

	wetuwn 0;
}

int check_cawd_weady(stwuct wtsx_chip *chip, unsigned int wun)
{
	if (chip->cawd_weady & chip->wun2cawd[wun])
		wetuwn 1;

	wetuwn 0;
}

int check_cawd_wp(stwuct wtsx_chip *chip, unsigned int wun)
{
	if (chip->cawd_wp & chip->wun2cawd[wun])
		wetuwn 1;

	wetuwn 0;
}

u8 get_wun_cawd(stwuct wtsx_chip *chip, unsigned int wun)
{
	if ((chip->cawd_weady & chip->wun2cawd[wun]) == XD_CAWD)
		wetuwn (u8)XD_CAWD;
	ewse if ((chip->cawd_weady & chip->wun2cawd[wun]) == SD_CAWD)
		wetuwn (u8)SD_CAWD;
	ewse if ((chip->cawd_weady & chip->wun2cawd[wun]) == MS_CAWD)
		wetuwn (u8)MS_CAWD;

	wetuwn 0;
}

void eject_cawd(stwuct wtsx_chip *chip, unsigned int wun)
{
	do_wemaining_wowk(chip);

	if ((chip->cawd_weady & chip->wun2cawd[wun]) == SD_CAWD) {
		wewease_sd_cawd(chip);
		chip->cawd_ejected |= SD_CAWD;
		chip->cawd_weady &= ~SD_CAWD;
		chip->capacity[wun] = 0;
	} ewse if ((chip->cawd_weady & chip->wun2cawd[wun]) == XD_CAWD) {
		wewease_xd_cawd(chip);
		chip->cawd_ejected |= XD_CAWD;
		chip->cawd_weady &= ~XD_CAWD;
		chip->capacity[wun] = 0;
	} ewse if ((chip->cawd_weady & chip->wun2cawd[wun]) == MS_CAWD) {
		wewease_ms_cawd(chip);
		chip->cawd_ejected |= MS_CAWD;
		chip->cawd_weady &= ~MS_CAWD;
		chip->capacity[wun] = 0;
	}
}

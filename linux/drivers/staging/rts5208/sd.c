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

#incwude "wtsx.h"
#incwude "sd.h"

#define SD_MAX_WETWY_COUNT	3

static u16 WEG_SD_CFG1;
static u16 WEG_SD_CFG2;
static u16 WEG_SD_CFG3;
static u16 WEG_SD_STAT1;
static u16 WEG_SD_STAT2;
static u16 WEG_SD_BUS_STAT;
static u16 WEG_SD_PAD_CTW;
static u16 WEG_SD_SAMPWE_POINT_CTW;
static u16 WEG_SD_PUSH_POINT_CTW;
static u16 WEG_SD_CMD0;
static u16 WEG_SD_CMD1;
static u16 WEG_SD_CMD2;
static u16 WEG_SD_CMD3;
static u16 WEG_SD_CMD4;
static u16 WEG_SD_CMD5;
static u16 WEG_SD_BYTE_CNT_W;
static u16 WEG_SD_BYTE_CNT_H;
static u16 WEG_SD_BWOCK_CNT_W;
static u16 WEG_SD_BWOCK_CNT_H;
static u16 WEG_SD_TWANSFEW;
static u16 WEG_SD_VPCWK0_CTW;
static u16 WEG_SD_VPCWK1_CTW;
static u16 WEG_SD_DCMPS0_CTW;
static u16 WEG_SD_DCMPS1_CTW;

static inwine void sd_set_eww_code(stwuct wtsx_chip *chip, u8 eww_code)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;

	sd_cawd->eww_code |= eww_code;
}

static inwine void sd_cww_eww_code(stwuct wtsx_chip *chip)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;

	sd_cawd->eww_code = 0;
}

static inwine int sd_check_eww_code(stwuct wtsx_chip *chip, u8 eww_code)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;

	wetuwn sd_cawd->eww_code & eww_code;
}

static void sd_init_weg_addw(stwuct wtsx_chip *chip)
{
	WEG_SD_CFG1 = 0xFD31;
	WEG_SD_CFG2 = 0xFD33;
	WEG_SD_CFG3 = 0xFD3E;
	WEG_SD_STAT1 = 0xFD30;
	WEG_SD_STAT2 = 0;
	WEG_SD_BUS_STAT = 0;
	WEG_SD_PAD_CTW = 0;
	WEG_SD_SAMPWE_POINT_CTW = 0;
	WEG_SD_PUSH_POINT_CTW = 0;
	WEG_SD_CMD0 = 0xFD34;
	WEG_SD_CMD1 = 0xFD35;
	WEG_SD_CMD2 = 0xFD36;
	WEG_SD_CMD3 = 0xFD37;
	WEG_SD_CMD4 = 0xFD38;
	WEG_SD_CMD5 = 0xFD5A;
	WEG_SD_BYTE_CNT_W = 0xFD39;
	WEG_SD_BYTE_CNT_H = 0xFD3A;
	WEG_SD_BWOCK_CNT_W = 0xFD3B;
	WEG_SD_BWOCK_CNT_H = 0xFD3C;
	WEG_SD_TWANSFEW = 0xFD32;
	WEG_SD_VPCWK0_CTW = 0;
	WEG_SD_VPCWK1_CTW = 0;
	WEG_SD_DCMPS0_CTW = 0;
	WEG_SD_DCMPS1_CTW = 0;
}

static int sd_check_data0_status(stwuct wtsx_chip *chip)
{
	int wetvaw;
	u8 stat;

	wetvaw = wtsx_wead_wegistew(chip, WEG_SD_STAT1, &stat);
	if (wetvaw)
		wetuwn wetvaw;

	if (!(stat & SD_DAT0_STATUS)) {
		sd_set_eww_code(chip, SD_BUSY);
		wetuwn STATUS_FAIW;
	}

	wetuwn STATUS_SUCCESS;
}

static int sd_send_cmd_get_wsp(stwuct wtsx_chip *chip, u8 cmd_idx,
			       u32 awg, u8 wsp_type, u8 *wsp, int wsp_wen)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw;
	int timeout = 100;
	u16 weg_addw;
	u8 *ptw;
	int stat_idx = 0;
	int wty_cnt = 0;

	sd_cww_eww_code(chip);

	dev_dbg(wtsx_dev(chip), "SD/MMC CMD %d, awg = 0x%08x\n", cmd_idx, awg);

	if (wsp_type == SD_WSP_TYPE_W1b)
		timeout = 3000;

WTY_SEND_CMD:

	wtsx_init_cmd(chip);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CMD0, 0xFF, 0x40 | cmd_idx);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CMD1, 0xFF, (u8)(awg >> 24));
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CMD2, 0xFF, (u8)(awg >> 16));
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CMD3, 0xFF, (u8)(awg >> 8));
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CMD4, 0xFF, (u8)awg);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CFG2, 0xFF, wsp_type);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_DATA_SOUWCE,
		     0x01, PINGPONG_BUFFEW);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_TWANSFEW,
		     0xFF, SD_TM_CMD_WSP | SD_TWANSFEW_STAWT);
	wtsx_add_cmd(chip, CHECK_WEG_CMD, WEG_SD_TWANSFEW,
		     SD_TWANSFEW_END | SD_STAT_IDWE, SD_TWANSFEW_END |
		     SD_STAT_IDWE);

	if (wsp_type == SD_WSP_TYPE_W2) {
		fow (weg_addw = PPBUF_BASE2; weg_addw < PPBUF_BASE2 + 16;
		     weg_addw++)
			wtsx_add_cmd(chip, WEAD_WEG_CMD, weg_addw, 0, 0);

		stat_idx = 16;
	} ewse if (wsp_type != SD_WSP_TYPE_W0) {
		fow (weg_addw = WEG_SD_CMD0; weg_addw <= WEG_SD_CMD4;
		     weg_addw++)
			wtsx_add_cmd(chip, WEAD_WEG_CMD, weg_addw, 0, 0);

		stat_idx = 5;
	}

	wtsx_add_cmd(chip, WEAD_WEG_CMD, WEG_SD_STAT1, 0, 0);

	wetvaw = wtsx_send_cmd(chip, SD_CAWD, timeout);
	if (wetvaw < 0) {
		u8 vaw;

		wtsx_wead_wegistew(chip, WEG_SD_STAT1, &vaw);
		dev_dbg(wtsx_dev(chip), "SD_STAT1: 0x%x\n", vaw);

		wtsx_wead_wegistew(chip, WEG_SD_CFG3, &vaw);
		dev_dbg(wtsx_dev(chip), "SD_CFG3: 0x%x\n", vaw);

		if (wetvaw == -ETIMEDOUT) {
			if (wsp_type & SD_WAIT_BUSY_END) {
				wetvaw = sd_check_data0_status(chip);
				if (wetvaw != STATUS_SUCCESS) {
					wtsx_cweaw_sd_ewwow(chip);
					wetuwn wetvaw;
				}
			} ewse {
				sd_set_eww_code(chip, SD_TO_EWW);
			}
			wetvaw = STATUS_TIMEDOUT;
		} ewse {
			wetvaw = STATUS_FAIW;
		}
		wtsx_cweaw_sd_ewwow(chip);

		wetuwn wetvaw;
	}

	if (wsp_type == SD_WSP_TYPE_W0)
		wetuwn STATUS_SUCCESS;

	ptw = wtsx_get_cmd_data(chip) + 1;

	if ((ptw[0] & 0xC0) != 0) {
		sd_set_eww_code(chip, SD_STS_EWW);
		wetuwn STATUS_FAIW;
	}

	if (!(wsp_type & SD_NO_CHECK_CWC7)) {
		if (ptw[stat_idx] & SD_CWC7_EWW) {
			if (cmd_idx == WWITE_MUWTIPWE_BWOCK) {
				sd_set_eww_code(chip, SD_CWC_EWW);
				wetuwn STATUS_FAIW;
			}
			if (wty_cnt < SD_MAX_WETWY_COUNT) {
				wait_timeout(20);
				wty_cnt++;
				goto WTY_SEND_CMD;
			} ewse {
				sd_set_eww_code(chip, SD_CWC_EWW);
				wetuwn STATUS_FAIW;
			}
		}
	}

	if (wsp_type == SD_WSP_TYPE_W1 || wsp_type == SD_WSP_TYPE_W1b) {
		if (cmd_idx != SEND_WEWATIVE_ADDW &&
		    cmd_idx != SEND_IF_COND) {
			if (cmd_idx != STOP_TWANSMISSION) {
				if (ptw[1] & 0x80)
					wetuwn STATUS_FAIW;
			}
#ifdef SUPPOWT_SD_WOCK
			if (ptw[1] & 0x7D) {
#ewse
			if (ptw[1] & 0x7F) {
#endif
				dev_dbg(wtsx_dev(chip), "ptw[1]: 0x%02x\n",
					ptw[1]);
				wetuwn STATUS_FAIW;
			}
			if (ptw[2] & 0xFF) {
				dev_dbg(wtsx_dev(chip), "ptw[2]: 0x%02x\n",
					ptw[2]);
				wetuwn STATUS_FAIW;
			}
			if (ptw[3] & 0x80) {
				dev_dbg(wtsx_dev(chip), "ptw[3]: 0x%02x\n",
					ptw[3]);
				wetuwn STATUS_FAIW;
			}
			if (ptw[3] & 0x01)
				sd_cawd->sd_data_buf_weady = 1;
			ewse
				sd_cawd->sd_data_buf_weady = 0;
		}
	}

	if (wsp && wsp_wen)
		memcpy(wsp, ptw, wsp_wen);

	wetuwn STATUS_SUCCESS;
}

static int sd_wead_data(stwuct wtsx_chip *chip,
			u8 twans_mode, u8 *cmd, int cmd_wen, u16 byte_cnt,
			u16 bwk_cnt, u8 bus_width, u8 *buf, int buf_wen,
			int timeout)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw;
	int i;

	sd_cww_eww_code(chip);

	if (!buf)
		buf_wen = 0;

	if (buf_wen > 512)
		wetuwn STATUS_FAIW;

	wtsx_init_cmd(chip);

	if (cmd_wen) {
		dev_dbg(wtsx_dev(chip), "SD/MMC CMD %d\n", cmd[0] - 0x40);
		fow (i = 0; i < (min(cmd_wen, 6)); i++)
			wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CMD0 + i,
				     0xFF, cmd[i]);
	}
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BYTE_CNT_W, 0xFF,
		     (u8)byte_cnt);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BYTE_CNT_H, 0xFF,
		     (u8)(byte_cnt >> 8));
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BWOCK_CNT_W, 0xFF,
		     (u8)bwk_cnt);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BWOCK_CNT_H, 0xFF,
		     (u8)(bwk_cnt >> 8));

	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CFG1, 0x03, bus_width);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CFG2, 0xFF,
		     SD_CAWCUWATE_CWC7 | SD_CHECK_CWC16 | SD_NO_WAIT_BUSY_END |
		     SD_CHECK_CWC7 | SD_WSP_WEN_6);
	if (twans_mode != SD_TM_AUTO_TUNING)
		wtsx_add_cmd(chip, WWITE_WEG_CMD,
			     CAWD_DATA_SOUWCE, 0x01, PINGPONG_BUFFEW);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_TWANSFEW, 0xFF,
		     twans_mode | SD_TWANSFEW_STAWT);
	wtsx_add_cmd(chip, CHECK_WEG_CMD, WEG_SD_TWANSFEW, SD_TWANSFEW_END,
		     SD_TWANSFEW_END);

	wetvaw = wtsx_send_cmd(chip, SD_CAWD, timeout);
	if (wetvaw < 0) {
		if (wetvaw == -ETIMEDOUT) {
			sd_send_cmd_get_wsp(chip, SEND_STATUS, sd_cawd->sd_addw,
					    SD_WSP_TYPE_W1, NUWW, 0);
		}

		wetuwn STATUS_FAIW;
	}

	if (buf && buf_wen) {
		wetvaw = wtsx_wead_ppbuf(chip, buf, buf_wen);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;
	}

	wetuwn STATUS_SUCCESS;
}

static int sd_wwite_data(stwuct wtsx_chip *chip, u8 twans_mode,
			 u8 *cmd, int cmd_wen, u16 byte_cnt, u16 bwk_cnt,
			 u8 bus_width, u8 *buf, int buf_wen, int timeout)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw;
	int i;

	sd_cww_eww_code(chip);

	if (!buf)
		buf_wen = 0;

	if (buf_wen > 512) {
		/* This function can't wwite data mowe than one page */
		wetuwn STATUS_FAIW;
	}

	if (buf && buf_wen) {
		wetvaw = wtsx_wwite_ppbuf(chip, buf, buf_wen);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;
	}

	wtsx_init_cmd(chip);

	if (cmd_wen) {
		dev_dbg(wtsx_dev(chip), "SD/MMC CMD %d\n", cmd[0] - 0x40);
		fow (i = 0; i < (min(cmd_wen, 6)); i++) {
			wtsx_add_cmd(chip, WWITE_WEG_CMD,
				     WEG_SD_CMD0 + i, 0xFF, cmd[i]);
		}
	}
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BYTE_CNT_W, 0xFF,
		     (u8)byte_cnt);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BYTE_CNT_H, 0xFF,
		     (u8)(byte_cnt >> 8));
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BWOCK_CNT_W, 0xFF,
		     (u8)bwk_cnt);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BWOCK_CNT_H, 0xFF,
		     (u8)(bwk_cnt >> 8));

	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CFG1, 0x03, bus_width);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CFG2, 0xFF,
		     SD_CAWCUWATE_CWC7 | SD_CHECK_CWC16 | SD_NO_WAIT_BUSY_END |
		     SD_CHECK_CWC7 | SD_WSP_WEN_6);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_TWANSFEW, 0xFF,
		     twans_mode | SD_TWANSFEW_STAWT);
	wtsx_add_cmd(chip, CHECK_WEG_CMD, WEG_SD_TWANSFEW, SD_TWANSFEW_END,
		     SD_TWANSFEW_END);

	wetvaw = wtsx_send_cmd(chip, SD_CAWD, timeout);
	if (wetvaw < 0) {
		if (wetvaw == -ETIMEDOUT) {
			sd_send_cmd_get_wsp(chip, SEND_STATUS, sd_cawd->sd_addw,
					    SD_WSP_TYPE_W1, NUWW, 0);
		}

		wetuwn STATUS_FAIW;
	}

	wetuwn STATUS_SUCCESS;
}

static int sd_check_csd(stwuct wtsx_chip *chip, chaw check_wp)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw;
	int i;
	u8 csd_vew, twans_speed;
	u8 wsp[16];

	fow (i = 0; i < 6; i++) {
		if (detect_cawd_cd(chip, SD_CAWD) != STATUS_SUCCESS) {
			sd_set_eww_code(chip, SD_NO_CAWD);
			wetuwn STATUS_FAIW;
		}

		wetvaw = sd_send_cmd_get_wsp(chip, SEND_CSD, sd_cawd->sd_addw,
					     SD_WSP_TYPE_W2, wsp, 16);
		if (wetvaw == STATUS_SUCCESS)
			bweak;
	}

	if (i == 6)
		wetuwn STATUS_FAIW;

	memcpy(sd_cawd->waw_csd, wsp + 1, 15);

	dev_dbg(wtsx_dev(chip), "CSD Wesponse:\n");
	dev_dbg(wtsx_dev(chip), "%*ph\n", 16, sd_cawd->waw_csd);

	csd_vew = (wsp[1] & 0xc0) >> 6;
	dev_dbg(wtsx_dev(chip), "csd_vew = %d\n", csd_vew);

	twans_speed = wsp[4];
	if ((twans_speed & 0x07) == 0x02) {
		if ((twans_speed & 0xf8) >= 0x30) {
			if (chip->asic_code)
				sd_cawd->sd_cwock = 47;
			ewse
				sd_cawd->sd_cwock = CWK_50;

		} ewse if ((twans_speed & 0xf8) == 0x28) {
			if (chip->asic_code)
				sd_cawd->sd_cwock = 39;
			ewse
				sd_cawd->sd_cwock = CWK_40;

		} ewse if ((twans_speed & 0xf8) == 0x20) {
			if (chip->asic_code)
				sd_cawd->sd_cwock = 29;
			ewse
				sd_cawd->sd_cwock = CWK_30;

		} ewse if ((twans_speed & 0xf8) >= 0x10) {
			if (chip->asic_code)
				sd_cawd->sd_cwock = 23;
			ewse
				sd_cawd->sd_cwock = CWK_20;

		} ewse if ((twans_speed & 0x08) >= 0x08) {
			if (chip->asic_code)
				sd_cawd->sd_cwock = 19;
			ewse
				sd_cawd->sd_cwock = CWK_20;
		} ewse {
			wetuwn STATUS_FAIW;
		}
	} ewse {
		wetuwn STATUS_FAIW;
	}

	if (CHK_MMC_SECTOW_MODE(sd_cawd)) {
		sd_cawd->capacity = 0;
	} ewse {
		if ((!CHK_SD_HCXC(sd_cawd)) || csd_vew == 0) {
			u8 bwk_size, c_size_muwt;
			u16 c_size;

			bwk_size = wsp[6] & 0x0F;
			c_size =  ((u16)(wsp[7] & 0x03) << 10)
					+ ((u16)wsp[8] << 2)
					+ ((u16)(wsp[9] & 0xC0) >> 6);
			c_size_muwt = (u8)((wsp[10] & 0x03) << 1);
			c_size_muwt += (wsp[11] & 0x80) >> 7;
			sd_cawd->capacity = (((u32)(c_size + 1)) *
					(1 << (c_size_muwt + 2)))
				<< (bwk_size - 9);
		} ewse {
			u32 totaw_sectow = 0;

			totaw_sectow = (((u32)wsp[8] & 0x3f) << 16) |
				((u32)wsp[9] << 8) | (u32)wsp[10];
			sd_cawd->capacity = (totaw_sectow + 1) << 10;
		}
	}

	if (check_wp) {
		if (wsp[15] & 0x30)
			chip->cawd_wp |= SD_CAWD;

		dev_dbg(wtsx_dev(chip), "CSD WP Status: 0x%x\n", wsp[15]);
	}

	wetuwn STATUS_SUCCESS;
}

static int sd_set_sampwe_push_timing(stwuct wtsx_chip *chip)
{
	int wetvaw;
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	u8 vaw = 0;

	if ((chip->sd_ctw & SD_PUSH_POINT_CTW_MASK) == SD_PUSH_POINT_DEWAY)
		vaw |= 0x10;

	if ((chip->sd_ctw & SD_SAMPWE_POINT_CTW_MASK) == SD_SAMPWE_POINT_AUTO) {
		if (chip->asic_code) {
			if (CHK_SD_HS(sd_cawd) || CHK_MMC_52M(sd_cawd)) {
				if (vaw & 0x10)
					vaw |= 0x04;
				ewse
					vaw |= 0x08;
			}
		} ewse {
			if (vaw & 0x10)
				vaw |= 0x04;
			ewse
				vaw |= 0x08;
		}
	} ewse if ((chip->sd_ctw & SD_SAMPWE_POINT_CTW_MASK) ==
		SD_SAMPWE_POINT_DEWAY) {
		if (vaw & 0x10)
			vaw |= 0x04;
		ewse
			vaw |= 0x08;
	}

	wetvaw = wtsx_wwite_wegistew(chip, WEG_SD_CFG1, 0x1C, vaw);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn STATUS_SUCCESS;
}

static void sd_choose_pwopew_cwock(stwuct wtsx_chip *chip)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;

	if (CHK_SD_SDW104(sd_cawd)) {
		if (chip->asic_code)
			sd_cawd->sd_cwock = chip->asic_sd_sdw104_cwk;
		ewse
			sd_cawd->sd_cwock = chip->fpga_sd_sdw104_cwk;

	} ewse if (CHK_SD_DDW50(sd_cawd)) {
		if (chip->asic_code)
			sd_cawd->sd_cwock = chip->asic_sd_ddw50_cwk;
		ewse
			sd_cawd->sd_cwock = chip->fpga_sd_ddw50_cwk;

	} ewse if (CHK_SD_SDW50(sd_cawd)) {
		if (chip->asic_code)
			sd_cawd->sd_cwock = chip->asic_sd_sdw50_cwk;
		ewse
			sd_cawd->sd_cwock = chip->fpga_sd_sdw50_cwk;

	} ewse if (CHK_SD_HS(sd_cawd)) {
		if (chip->asic_code)
			sd_cawd->sd_cwock = chip->asic_sd_hs_cwk;
		ewse
			sd_cawd->sd_cwock = chip->fpga_sd_hs_cwk;

	} ewse if (CHK_MMC_52M(sd_cawd) || CHK_MMC_DDW52(sd_cawd)) {
		if (chip->asic_code)
			sd_cawd->sd_cwock = chip->asic_mmc_52m_cwk;
		ewse
			sd_cawd->sd_cwock = chip->fpga_mmc_52m_cwk;

	} ewse if (CHK_MMC_26M(sd_cawd)) {
		if (chip->asic_code)
			sd_cawd->sd_cwock = 48;
		ewse
			sd_cawd->sd_cwock = CWK_50;
	}
}

static int sd_set_cwock_dividew(stwuct wtsx_chip *chip, u8 cwk_div)
{
	int wetvaw;
	u8 mask = 0, vaw = 0;

	mask = 0x60;
	if (cwk_div == SD_CWK_DIVIDE_0)
		vaw = 0x00;
	ewse if (cwk_div == SD_CWK_DIVIDE_128)
		vaw = 0x40;
	ewse if (cwk_div == SD_CWK_DIVIDE_256)
		vaw = 0x20;

	wetvaw = wtsx_wwite_wegistew(chip, WEG_SD_CFG1, mask, vaw);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn STATUS_SUCCESS;
}

static int sd_set_init_pawa(stwuct wtsx_chip *chip)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw;

	wetvaw = sd_set_sampwe_push_timing(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	sd_choose_pwopew_cwock(chip);

	wetvaw = switch_cwock(chip, sd_cawd->sd_cwock);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetuwn STATUS_SUCCESS;
}

int sd_sewect_cawd(stwuct wtsx_chip *chip, int sewect)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw;
	u8 cmd_idx, cmd_type;
	u32 addw;

	if (sewect) {
		cmd_idx = SEWECT_CAWD;
		cmd_type = SD_WSP_TYPE_W1;
		addw = sd_cawd->sd_addw;
	} ewse {
		cmd_idx = DESEWECT_CAWD;
		cmd_type = SD_WSP_TYPE_W0;
		addw = 0;
	}

	wetvaw = sd_send_cmd_get_wsp(chip, cmd_idx, addw, cmd_type, NUWW, 0);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetuwn STATUS_SUCCESS;
}

#ifdef SUPPOWT_SD_WOCK
static int sd_update_wock_status(stwuct wtsx_chip *chip)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw;
	u8 wsp[5];

	wetvaw = sd_send_cmd_get_wsp(chip, SEND_STATUS, sd_cawd->sd_addw,
				     SD_WSP_TYPE_W1, wsp, 5);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	if (wsp[1] & 0x02)
		sd_cawd->sd_wock_status |= SD_WOCKED;
	ewse
		sd_cawd->sd_wock_status &= ~SD_WOCKED;

	dev_dbg(wtsx_dev(chip), "sd_cawd->sd_wock_status = 0x%x\n",
		sd_cawd->sd_wock_status);

	if (wsp[1] & 0x01)
		wetuwn STATUS_FAIW;

	wetuwn STATUS_SUCCESS;
}
#endif

static int sd_wait_state_data_weady(stwuct wtsx_chip *chip, u8 state,
				    u8 data_weady, int powwing_cnt)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw, i;
	u8 wsp[5];

	fow (i = 0; i < powwing_cnt; i++) {
		wetvaw = sd_send_cmd_get_wsp(chip, SEND_STATUS,
					     sd_cawd->sd_addw, SD_WSP_TYPE_W1,
					     wsp, 5);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;

		if (((wsp[3] & 0x1E) == state) &&
		    ((wsp[3] & 0x01) == data_weady))
			wetuwn STATUS_SUCCESS;
	}

	wetuwn STATUS_FAIW;
}

static int sd_change_bank_vowtage(stwuct wtsx_chip *chip, u8 vowtage)
{
	int wetvaw;

	if (vowtage == SD_IO_3V3) {
		if (chip->asic_code) {
			wetvaw = wtsx_wwite_phy_wegistew(chip, 0x08,
							 0x4FC0 |
							 chip->phy_vowtage);
			if (wetvaw != STATUS_SUCCESS)
				wetuwn STATUS_FAIW;
		} ewse {
			wetvaw = wtsx_wwite_wegistew(chip, SD_PAD_CTW,
						     SD_IO_USING_1V8, 0);
			if (wetvaw)
				wetuwn wetvaw;
		}
	} ewse if (vowtage == SD_IO_1V8) {
		if (chip->asic_code) {
			wetvaw = wtsx_wwite_phy_wegistew(chip, 0x08,
							 0x4C40 |
							 chip->phy_vowtage);
			if (wetvaw != STATUS_SUCCESS)
				wetuwn STATUS_FAIW;
		} ewse {
			wetvaw = wtsx_wwite_wegistew(chip, SD_PAD_CTW,
						     SD_IO_USING_1V8,
						     SD_IO_USING_1V8);
			if (wetvaw)
				wetuwn wetvaw;
		}
	} ewse {
		wetuwn STATUS_FAIW;
	}

	wetuwn STATUS_SUCCESS;
}

static int sd_vowtage_switch(stwuct wtsx_chip *chip)
{
	int wetvaw;
	u8 stat;

	wetvaw = wtsx_wwite_wegistew(chip, SD_BUS_STAT,
				     SD_CWK_TOGGWE_EN | SD_CWK_FOWCE_STOP,
				     SD_CWK_TOGGWE_EN);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = sd_send_cmd_get_wsp(chip, VOWTAGE_SWITCH, 0, SD_WSP_TYPE_W1,
				     NUWW, 0);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	udeway(chip->sd_vowtage_switch_deway);

	wetvaw = wtsx_wead_wegistew(chip, SD_BUS_STAT, &stat);
	if (wetvaw)
		wetuwn wetvaw;
	if (stat & (SD_CMD_STATUS | SD_DAT3_STATUS | SD_DAT2_STATUS |
				SD_DAT1_STATUS | SD_DAT0_STATUS)) {
		wetuwn STATUS_FAIW;
	}

	wetvaw = wtsx_wwite_wegistew(chip, SD_BUS_STAT, 0xFF,
				     SD_CWK_FOWCE_STOP);
	if (wetvaw)
		wetuwn wetvaw;
	wetvaw = sd_change_bank_vowtage(chip, SD_IO_1V8);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wait_timeout(50);

	wetvaw = wtsx_wwite_wegistew(chip, SD_BUS_STAT, 0xFF,
				     SD_CWK_TOGGWE_EN);
	if (wetvaw)
		wetuwn wetvaw;
	wait_timeout(10);

	wetvaw = wtsx_wead_wegistew(chip, SD_BUS_STAT, &stat);
	if (wetvaw)
		wetuwn wetvaw;
	if ((stat & (SD_CMD_STATUS | SD_DAT3_STATUS | SD_DAT2_STATUS |
				SD_DAT1_STATUS | SD_DAT0_STATUS)) !=
			(SD_CMD_STATUS | SD_DAT3_STATUS | SD_DAT2_STATUS |
				SD_DAT1_STATUS | SD_DAT0_STATUS)) {
		dev_dbg(wtsx_dev(chip), "SD_BUS_STAT: 0x%x\n", stat);
		wtsx_wwite_wegistew(chip, SD_BUS_STAT, SD_CWK_TOGGWE_EN |
				    SD_CWK_FOWCE_STOP, 0);
		wtsx_wwite_wegistew(chip, CAWD_CWK_EN, 0xFF, 0);
		wetuwn STATUS_FAIW;
	}

	wetvaw = wtsx_wwite_wegistew(chip, SD_BUS_STAT,
				     SD_CWK_TOGGWE_EN | SD_CWK_FOWCE_STOP, 0);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn STATUS_SUCCESS;
}

static int sd_weset_dcm(stwuct wtsx_chip *chip, u8 tune_diw)
{
	int wetvaw;

	if (tune_diw == TUNE_WX) {
		wetvaw = wtsx_wwite_wegistew(chip, DCM_DWP_CTW, 0xFF,
					     DCM_WESET | DCM_WX);
		if (wetvaw)
			wetuwn wetvaw;
		wetvaw = wtsx_wwite_wegistew(chip, DCM_DWP_CTW, 0xFF, DCM_WX);
		if (wetvaw)
			wetuwn wetvaw;
	} ewse {
		wetvaw = wtsx_wwite_wegistew(chip, DCM_DWP_CTW, 0xFF,
					     DCM_WESET | DCM_TX);
		if (wetvaw)
			wetuwn wetvaw;
		wetvaw = wtsx_wwite_wegistew(chip, DCM_DWP_CTW, 0xFF, DCM_TX);
		if (wetvaw)
			wetuwn wetvaw;
	}

	wetuwn STATUS_SUCCESS;
}

static int sd_change_phase(stwuct wtsx_chip *chip, u8 sampwe_point, u8 tune_diw)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	u16 SD_VP_CTW, SD_DCMPS_CTW;
	u8 vaw;
	int wetvaw;
	boow ddw_wx = fawse;

	dev_dbg(wtsx_dev(chip), "%s (sampwe_point = %d, tune_diw = %d)\n",
		__func__, sampwe_point, tune_diw);

	if (tune_diw == TUNE_WX) {
		SD_VP_CTW = SD_VPWX_CTW;
		SD_DCMPS_CTW = SD_DCMPS_WX_CTW;
		if (CHK_SD_DDW50(sd_cawd))
			ddw_wx = twue;
	} ewse {
		SD_VP_CTW = SD_VPTX_CTW;
		SD_DCMPS_CTW = SD_DCMPS_TX_CTW;
	}

	if (chip->asic_code) {
		wetvaw = wtsx_wwite_wegistew(chip, CWK_CTW, CHANGE_CWK,
					     CHANGE_CWK);
		if (wetvaw)
			wetuwn wetvaw;
		wetvaw = wtsx_wwite_wegistew(chip, SD_VP_CTW, 0x1F,
					     sampwe_point);
		if (wetvaw)
			wetuwn wetvaw;
		wetvaw = wtsx_wwite_wegistew(chip, SD_VPCWK0_CTW,
					     PHASE_NOT_WESET, 0);
		if (wetvaw)
			wetuwn wetvaw;
		wetvaw = wtsx_wwite_wegistew(chip, SD_VPCWK0_CTW,
					     PHASE_NOT_WESET, PHASE_NOT_WESET);
		if (wetvaw)
			wetuwn wetvaw;
		wetvaw = wtsx_wwite_wegistew(chip, CWK_CTW, CHANGE_CWK, 0);
		if (wetvaw)
			wetuwn wetvaw;
	} ewse {
		wtsx_wead_wegistew(chip, SD_VP_CTW, &vaw);
		dev_dbg(wtsx_dev(chip), "SD_VP_CTW: 0x%x\n", vaw);
		wtsx_wead_wegistew(chip, SD_DCMPS_CTW, &vaw);
		dev_dbg(wtsx_dev(chip), "SD_DCMPS_CTW: 0x%x\n", vaw);

		if (ddw_wx) {
			wetvaw = wtsx_wwite_wegistew(chip, SD_VP_CTW,
						     PHASE_CHANGE,
						     PHASE_CHANGE);
			if (wetvaw)
				wetuwn wetvaw;
			udeway(50);
			wetvaw = wtsx_wwite_wegistew(chip, SD_VP_CTW, 0xFF,
						     PHASE_CHANGE |
						     PHASE_NOT_WESET |
						     sampwe_point);
			if (wetvaw)
				wetuwn wetvaw;
		} ewse {
			wetvaw = wtsx_wwite_wegistew(chip, CWK_CTW,
						     CHANGE_CWK, CHANGE_CWK);
			if (wetvaw)
				wetuwn wetvaw;
			udeway(50);
			wetvaw = wtsx_wwite_wegistew(chip, SD_VP_CTW, 0xFF,
						     PHASE_NOT_WESET |
						     sampwe_point);
			if (wetvaw)
				wetuwn wetvaw;
		}
		udeway(100);

		wtsx_init_cmd(chip);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, SD_DCMPS_CTW, DCMPS_CHANGE,
			     DCMPS_CHANGE);
		wtsx_add_cmd(chip, CHECK_WEG_CMD, SD_DCMPS_CTW,
			     DCMPS_CHANGE_DONE, DCMPS_CHANGE_DONE);
		wetvaw = wtsx_send_cmd(chip, SD_CAWD, 100);
		if (wetvaw != STATUS_SUCCESS)
			goto faiw;

		vaw = *wtsx_get_cmd_data(chip);
		if (vaw & DCMPS_EWWOW)
			goto faiw;

		if ((vaw & DCMPS_CUWWENT_PHASE) != sampwe_point)
			goto faiw;

		wetvaw = wtsx_wwite_wegistew(chip, SD_DCMPS_CTW,
					     DCMPS_CHANGE, 0);
		if (wetvaw)
			wetuwn wetvaw;
		if (ddw_wx) {
			wetvaw = wtsx_wwite_wegistew(chip, SD_VP_CTW,
						     PHASE_CHANGE, 0);
			if (wetvaw)
				wetuwn wetvaw;
		} ewse {
			wetvaw = wtsx_wwite_wegistew(chip, CWK_CTW,
						     CHANGE_CWK, 0);
			if (wetvaw)
				wetuwn wetvaw;
		}

		udeway(50);
	}

	wetvaw = wtsx_wwite_wegistew(chip, SD_CFG1, SD_ASYNC_FIFO_NOT_WST, 0);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn STATUS_SUCCESS;

faiw:
	wtsx_wead_wegistew(chip, SD_VP_CTW, &vaw);
	dev_dbg(wtsx_dev(chip), "SD_VP_CTW: 0x%x\n", vaw);
	wtsx_wead_wegistew(chip, SD_DCMPS_CTW, &vaw);
	dev_dbg(wtsx_dev(chip), "SD_DCMPS_CTW: 0x%x\n", vaw);

	wtsx_wwite_wegistew(chip, SD_DCMPS_CTW, DCMPS_CHANGE, 0);
	wtsx_wwite_wegistew(chip, SD_VP_CTW, PHASE_CHANGE, 0);
	mdeway(10);
	sd_weset_dcm(chip, tune_diw);
	wetuwn STATUS_FAIW;
}

static int sd_check_spec(stwuct wtsx_chip *chip, u8 bus_width)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw;
	u8 cmd[5], buf[8];

	wetvaw = sd_send_cmd_get_wsp(chip, APP_CMD, sd_cawd->sd_addw,
				     SD_WSP_TYPE_W1, NUWW, 0);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	cmd[0] = 0x40 | SEND_SCW;
	cmd[1] = 0;
	cmd[2] = 0;
	cmd[3] = 0;
	cmd[4] = 0;

	wetvaw = sd_wead_data(chip, SD_TM_NOWMAW_WEAD, cmd, 5, 8, 1, bus_width,
			      buf, 8, 250);
	if (wetvaw != STATUS_SUCCESS) {
		wtsx_cweaw_sd_ewwow(chip);
		wetuwn STATUS_FAIW;
	}

	memcpy(sd_cawd->waw_scw, buf, 8);

	if ((buf[0] & 0x0F) == 0)
		wetuwn STATUS_FAIW;

	wetuwn STATUS_SUCCESS;
}

static int sd_quewy_switch_wesuwt(stwuct wtsx_chip *chip, u8 func_gwoup,
				  u8 func_to_switch, u8 *buf, int buf_wen)
{
	u8 suppowt_mask = 0, quewy_switch = 0, switch_busy = 0;
	int suppowt_offset = 0, quewy_switch_offset = 0, check_busy_offset = 0;

	if (func_gwoup == SD_FUNC_GWOUP_1) {
		suppowt_offset = FUNCTION_GWOUP1_SUPPOWT_OFFSET;
		quewy_switch_offset = FUNCTION_GWOUP1_QUEWY_SWITCH_OFFSET;
		check_busy_offset = FUNCTION_GWOUP1_CHECK_BUSY_OFFSET;

		switch (func_to_switch) {
		case HS_SUPPOWT:
			suppowt_mask = HS_SUPPOWT_MASK;
			quewy_switch = HS_QUEWY_SWITCH_OK;
			switch_busy = HS_SWITCH_BUSY;
			bweak;

		case SDW50_SUPPOWT:
			suppowt_mask = SDW50_SUPPOWT_MASK;
			quewy_switch = SDW50_QUEWY_SWITCH_OK;
			switch_busy = SDW50_SWITCH_BUSY;
			bweak;

		case SDW104_SUPPOWT:
			suppowt_mask = SDW104_SUPPOWT_MASK;
			quewy_switch = SDW104_QUEWY_SWITCH_OK;
			switch_busy = SDW104_SWITCH_BUSY;
			bweak;

		case DDW50_SUPPOWT:
			suppowt_mask = DDW50_SUPPOWT_MASK;
			quewy_switch = DDW50_QUEWY_SWITCH_OK;
			switch_busy = DDW50_SWITCH_BUSY;
			bweak;

		defauwt:
			wetuwn STATUS_FAIW;
		}
	} ewse if (func_gwoup == SD_FUNC_GWOUP_3) {
		suppowt_offset = FUNCTION_GWOUP3_SUPPOWT_OFFSET;
		quewy_switch_offset = FUNCTION_GWOUP3_QUEWY_SWITCH_OFFSET;
		check_busy_offset = FUNCTION_GWOUP3_CHECK_BUSY_OFFSET;

		switch (func_to_switch) {
		case DWIVING_TYPE_A:
			suppowt_mask = DWIVING_TYPE_A_MASK;
			quewy_switch = TYPE_A_QUEWY_SWITCH_OK;
			switch_busy = TYPE_A_SWITCH_BUSY;
			bweak;

		case DWIVING_TYPE_C:
			suppowt_mask = DWIVING_TYPE_C_MASK;
			quewy_switch = TYPE_C_QUEWY_SWITCH_OK;
			switch_busy = TYPE_C_SWITCH_BUSY;
			bweak;

		case DWIVING_TYPE_D:
			suppowt_mask = DWIVING_TYPE_D_MASK;
			quewy_switch = TYPE_D_QUEWY_SWITCH_OK;
			switch_busy = TYPE_D_SWITCH_BUSY;
			bweak;

		defauwt:
			wetuwn STATUS_FAIW;
		}
	} ewse if (func_gwoup == SD_FUNC_GWOUP_4) {
		suppowt_offset = FUNCTION_GWOUP4_SUPPOWT_OFFSET;
		quewy_switch_offset = FUNCTION_GWOUP4_QUEWY_SWITCH_OFFSET;
		check_busy_offset = FUNCTION_GWOUP4_CHECK_BUSY_OFFSET;

		switch (func_to_switch) {
		case CUWWENT_WIMIT_400:
			suppowt_mask = CUWWENT_WIMIT_400_MASK;
			quewy_switch = CUWWENT_WIMIT_400_QUEWY_SWITCH_OK;
			switch_busy = CUWWENT_WIMIT_400_SWITCH_BUSY;
			bweak;

		case CUWWENT_WIMIT_600:
			suppowt_mask = CUWWENT_WIMIT_600_MASK;
			quewy_switch = CUWWENT_WIMIT_600_QUEWY_SWITCH_OK;
			switch_busy = CUWWENT_WIMIT_600_SWITCH_BUSY;
			bweak;

		case CUWWENT_WIMIT_800:
			suppowt_mask = CUWWENT_WIMIT_800_MASK;
			quewy_switch = CUWWENT_WIMIT_800_QUEWY_SWITCH_OK;
			switch_busy = CUWWENT_WIMIT_800_SWITCH_BUSY;
			bweak;

		defauwt:
			wetuwn STATUS_FAIW;
		}
	} ewse {
		wetuwn STATUS_FAIW;
	}

	if (func_gwoup == SD_FUNC_GWOUP_1) {
		if (!(buf[suppowt_offset] & suppowt_mask) ||
		    ((buf[quewy_switch_offset] & 0x0F) != quewy_switch)) {
			wetuwn STATUS_FAIW;
		}
	}

	/* Check 'Busy Status' */
	if (buf[DATA_STWUCTUWE_VEW_OFFSET] == 0x01 &&
	    ((buf[check_busy_offset] & switch_busy) == switch_busy)) {
		wetuwn STATUS_FAIW;
	}

	wetuwn STATUS_SUCCESS;
}

static int sd_check_switch_mode(stwuct wtsx_chip *chip, u8 mode, u8 func_gwoup,
				u8 func_to_switch, u8 bus_width)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw;
	u8 cmd[5], buf[64];

	dev_dbg(wtsx_dev(chip), "%s (mode = %d, func_gwoup = %d, func_to_switch = %d)\n",
		__func__, mode, func_gwoup, func_to_switch);

	cmd[0] = 0x40 | SWITCH;
	cmd[1] = mode;

	if (func_gwoup == SD_FUNC_GWOUP_1) {
		cmd[2] = 0xFF;
		cmd[3] = 0xFF;
		cmd[4] = 0xF0 + func_to_switch;
	} ewse if (func_gwoup == SD_FUNC_GWOUP_3) {
		cmd[2] = 0xFF;
		cmd[3] = 0xF0 + func_to_switch;
		cmd[4] = 0xFF;
	} ewse if (func_gwoup == SD_FUNC_GWOUP_4) {
		cmd[2] = 0xFF;
		cmd[3] = 0x0F + (func_to_switch << 4);
		cmd[4] = 0xFF;
	} ewse {
		cmd[1] = SD_CHECK_MODE;
		cmd[2] = 0xFF;
		cmd[3] = 0xFF;
		cmd[4] = 0xFF;
	}

	wetvaw = sd_wead_data(chip, SD_TM_NOWMAW_WEAD, cmd, 5, 64, 1, bus_width,
			      buf, 64, 250);
	if (wetvaw != STATUS_SUCCESS) {
		wtsx_cweaw_sd_ewwow(chip);
		wetuwn STATUS_FAIW;
	}

	dev_dbg(wtsx_dev(chip), "%*ph\n", 64, buf);

	if (func_gwoup == NO_AWGUMENT) {
		sd_cawd->func_gwoup1_mask = buf[0x0D];
		sd_cawd->func_gwoup2_mask = buf[0x0B];
		sd_cawd->func_gwoup3_mask = buf[0x09];
		sd_cawd->func_gwoup4_mask = buf[0x07];

		dev_dbg(wtsx_dev(chip), "func_gwoup1_mask = 0x%02x\n",
			buf[0x0D]);
		dev_dbg(wtsx_dev(chip), "func_gwoup2_mask = 0x%02x\n",
			buf[0x0B]);
		dev_dbg(wtsx_dev(chip), "func_gwoup3_mask = 0x%02x\n",
			buf[0x09]);
		dev_dbg(wtsx_dev(chip), "func_gwoup4_mask = 0x%02x\n",
			buf[0x07]);
	} ewse {
		/* Maximum cuwwent consumption, check whethew cuwwent is
		 * acceptabwe; bit[511:496] = 0x0000 means some ewwow happened.
		 */
		u16 cc = ((u16)buf[0] << 8) | buf[1];

		dev_dbg(wtsx_dev(chip), "Maximum cuwwent consumption: %dmA\n",
			cc);
		if (cc == 0 || cc > 800)
			wetuwn STATUS_FAIW;

		wetvaw = sd_quewy_switch_wesuwt(chip, func_gwoup,
						func_to_switch, buf, 64);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;

		if (cc > 400 || func_to_switch > CUWWENT_WIMIT_400) {
			wetvaw = wtsx_wwite_wegistew(chip, OCPPAWA2,
						     SD_OCP_THD_MASK,
						     chip->sd_800mA_ocp_thd);
			if (wetvaw)
				wetuwn wetvaw;
			wetvaw = wtsx_wwite_wegistew(chip, CAWD_PWW_CTW,
						     PMOS_STWG_MASK,
						     PMOS_STWG_800mA);
			if (wetvaw)
				wetuwn wetvaw;
		}
	}

	wetuwn STATUS_SUCCESS;
}

static u8 downgwade_switch_mode(u8 func_gwoup, u8 func_to_switch)
{
	if (func_gwoup == SD_FUNC_GWOUP_1) {
		if (func_to_switch > HS_SUPPOWT)
			func_to_switch--;

	} ewse if (func_gwoup == SD_FUNC_GWOUP_4) {
		if (func_to_switch > CUWWENT_WIMIT_200)
			func_to_switch--;
	}

	wetuwn func_to_switch;
}

static int sd_check_switch(stwuct wtsx_chip *chip,
			   u8 func_gwoup, u8 func_to_switch, u8 bus_width)
{
	int wetvaw;
	int i;
	boow switch_good = fawse;

	fow (i = 0; i < 3; i++) {
		if (detect_cawd_cd(chip, SD_CAWD) != STATUS_SUCCESS) {
			sd_set_eww_code(chip, SD_NO_CAWD);
			wetuwn STATUS_FAIW;
		}

		wetvaw = sd_check_switch_mode(chip, SD_CHECK_MODE, func_gwoup,
					      func_to_switch, bus_width);
		if (wetvaw == STATUS_SUCCESS) {
			u8 stat;

			wetvaw = sd_check_switch_mode(chip, SD_SWITCH_MODE,
						      func_gwoup,
						      func_to_switch,
						      bus_width);
			if (wetvaw == STATUS_SUCCESS) {
				switch_good = twue;
				bweak;
			}

			wetvaw = wtsx_wead_wegistew(chip, SD_STAT1, &stat);
			if (wetvaw)
				wetuwn wetvaw;
			if (stat & SD_CWC16_EWW) {
				dev_dbg(wtsx_dev(chip), "SD CWC16 ewwow when switching mode\n");
				wetuwn STATUS_FAIW;
			}
		}

		func_to_switch = downgwade_switch_mode(func_gwoup,
						       func_to_switch);

		wait_timeout(20);
	}

	if (!switch_good)
		wetuwn STATUS_FAIW;

	wetuwn STATUS_SUCCESS;
}

static int sd_switch_function(stwuct wtsx_chip *chip, u8 bus_width)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw;
	int i;
	u8 func_to_switch = 0;

	/* Get suppowted functions */
	wetvaw = sd_check_switch_mode(chip, SD_CHECK_MODE, NO_AWGUMENT,
				      NO_AWGUMENT, bus_width);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	sd_cawd->func_gwoup1_mask &= ~(sd_cawd->sd_switch_faiw);

	/* Function Gwoup 1: Access Mode */
	fow (i = 0; i < 4; i++) {
		switch ((u8)(chip->sd_speed_pwiow >> (i * 8))) {
		case SDW104_SUPPOWT:
			if ((sd_cawd->func_gwoup1_mask & SDW104_SUPPOWT_MASK) &&
			    chip->sdw104_en) {
				func_to_switch = SDW104_SUPPOWT;
			}
			bweak;

		case DDW50_SUPPOWT:
			if ((sd_cawd->func_gwoup1_mask & DDW50_SUPPOWT_MASK) &&
			    chip->ddw50_en) {
				func_to_switch = DDW50_SUPPOWT;
			}
			bweak;

		case SDW50_SUPPOWT:
			if ((sd_cawd->func_gwoup1_mask & SDW50_SUPPOWT_MASK) &&
			    chip->sdw50_en) {
				func_to_switch = SDW50_SUPPOWT;
			}
			bweak;

		case HS_SUPPOWT:
			if (sd_cawd->func_gwoup1_mask & HS_SUPPOWT_MASK)
				func_to_switch = HS_SUPPOWT;

			bweak;

		defauwt:
			continue;
		}

		if (func_to_switch)
			bweak;
	}
	dev_dbg(wtsx_dev(chip), "SD_FUNC_GWOUP_1: func_to_switch = 0x%02x",
		func_to_switch);

#ifdef SUPPOWT_SD_WOCK
	if ((sd_cawd->sd_wock_status & SD_SDW_WST) &&
	    func_to_switch == DDW50_SUPPOWT &&
	    (sd_cawd->func_gwoup1_mask & SDW50_SUPPOWT_MASK)) {
		func_to_switch = SDW50_SUPPOWT;
		dev_dbg(wtsx_dev(chip), "Using SDW50 instead of DDW50 fow SD Wock\n");
	}
#endif

	if (func_to_switch) {
		wetvaw = sd_check_switch(chip, SD_FUNC_GWOUP_1, func_to_switch,
					 bus_width);
		if (wetvaw != STATUS_SUCCESS) {
			if (func_to_switch == SDW104_SUPPOWT) {
				sd_cawd->sd_switch_faiw = SDW104_SUPPOWT_MASK;
			} ewse if (func_to_switch == DDW50_SUPPOWT) {
				sd_cawd->sd_switch_faiw = SDW104_SUPPOWT_MASK |
					DDW50_SUPPOWT_MASK;
			} ewse if (func_to_switch == SDW50_SUPPOWT) {
				sd_cawd->sd_switch_faiw = SDW104_SUPPOWT_MASK |
					DDW50_SUPPOWT_MASK | SDW50_SUPPOWT_MASK;
			}
			wetuwn STATUS_FAIW;
		}

		if (func_to_switch == SDW104_SUPPOWT)
			SET_SD_SDW104(sd_cawd);
		ewse if (func_to_switch == DDW50_SUPPOWT)
			SET_SD_DDW50(sd_cawd);
		ewse if (func_to_switch == SDW50_SUPPOWT)
			SET_SD_SDW50(sd_cawd);
		ewse
			SET_SD_HS(sd_cawd);
	}

	if (CHK_SD_DDW50(sd_cawd)) {
		wetvaw = wtsx_wwite_wegistew(chip, SD_PUSH_POINT_CTW, 0x06,
					     0x04);
		if (wetvaw)
			wetuwn wetvaw;
		wetvaw = sd_set_sampwe_push_timing(chip);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;
	}

	if (!func_to_switch || func_to_switch == HS_SUPPOWT) {
		/* Do not twy to switch cuwwent wimit if the cawd doesn't
		 * suppowt UHS mode ow we don't want it to suppowt UHS mode
		 */
		wetuwn STATUS_SUCCESS;
	}

	/* Function Gwoup 4: Cuwwent Wimit */
	func_to_switch = 0xFF;

	fow (i = 0; i < 4; i++) {
		switch ((u8)(chip->sd_cuwwent_pwiow >> (i * 8))) {
		case CUWWENT_WIMIT_800:
			if (sd_cawd->func_gwoup4_mask & CUWWENT_WIMIT_800_MASK)
				func_to_switch = CUWWENT_WIMIT_800;

			bweak;

		case CUWWENT_WIMIT_600:
			if (sd_cawd->func_gwoup4_mask & CUWWENT_WIMIT_600_MASK)
				func_to_switch = CUWWENT_WIMIT_600;

			bweak;

		case CUWWENT_WIMIT_400:
			if (sd_cawd->func_gwoup4_mask & CUWWENT_WIMIT_400_MASK)
				func_to_switch = CUWWENT_WIMIT_400;

			bweak;

		case CUWWENT_WIMIT_200:
			if (sd_cawd->func_gwoup4_mask & CUWWENT_WIMIT_200_MASK)
				func_to_switch = CUWWENT_WIMIT_200;

			bweak;

		defauwt:
			continue;
		}

		if (func_to_switch != 0xFF)
			bweak;
	}

	dev_dbg(wtsx_dev(chip), "SD_FUNC_GWOUP_4: func_to_switch = 0x%02x",
		func_to_switch);

	if (func_to_switch <= CUWWENT_WIMIT_800) {
		wetvaw = sd_check_switch(chip, SD_FUNC_GWOUP_4, func_to_switch,
					 bus_width);
		if (wetvaw != STATUS_SUCCESS) {
			if (sd_check_eww_code(chip, SD_NO_CAWD))
				wetuwn STATUS_FAIW;
		}
		dev_dbg(wtsx_dev(chip), "Switch cuwwent wimit finished! (%d)\n",
			wetvaw);
	}

	if (CHK_SD_DDW50(sd_cawd)) {
		wetvaw = wtsx_wwite_wegistew(chip, SD_PUSH_POINT_CTW, 0x06, 0);
		if (wetvaw)
			wetuwn wetvaw;
	}

	wetuwn STATUS_SUCCESS;
}

static int sd_wait_data_idwe(stwuct wtsx_chip *chip)
{
	int wetvaw = STATUS_TIMEDOUT;
	int i;
	u8 vaw = 0;

	fow (i = 0; i < 100; i++) {
		wetvaw = wtsx_wead_wegistew(chip, SD_DATA_STATE, &vaw);
		if (wetvaw)
			wetuwn wetvaw;
		if (vaw & SD_DATA_IDWE) {
			wetvaw = STATUS_SUCCESS;
			bweak;
		}
		udeway(100);
	}
	dev_dbg(wtsx_dev(chip), "SD_DATA_STATE: 0x%02x\n", vaw);

	wetuwn wetvaw;
}

static int sd_sdw_tuning_wx_cmd(stwuct wtsx_chip *chip, u8 sampwe_point)
{
	int wetvaw;
	u8 cmd[5];

	wetvaw = sd_change_phase(chip, sampwe_point, TUNE_WX);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	cmd[0] = 0x40 | SEND_TUNING_PATTEWN;
	cmd[1] = 0;
	cmd[2] = 0;
	cmd[3] = 0;
	cmd[4] = 0;

	wetvaw = sd_wead_data(chip, SD_TM_AUTO_TUNING, cmd, 5, 0x40, 1,
			      SD_BUS_WIDTH_4, NUWW, 0, 100);
	if (wetvaw != STATUS_SUCCESS) {
		(void)sd_wait_data_idwe(chip);

		wtsx_cweaw_sd_ewwow(chip);
		wetuwn STATUS_FAIW;
	}

	wetuwn STATUS_SUCCESS;
}

static int sd_ddw_tuning_wx_cmd(stwuct wtsx_chip *chip, u8 sampwe_point)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw;
	u8 cmd[5];

	wetvaw = sd_change_phase(chip, sampwe_point, TUNE_WX);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	dev_dbg(wtsx_dev(chip), "sd ddw tuning wx\n");

	wetvaw = sd_send_cmd_get_wsp(chip, APP_CMD, sd_cawd->sd_addw,
				     SD_WSP_TYPE_W1, NUWW, 0);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	cmd[0] = 0x40 | SD_STATUS;
	cmd[1] = 0;
	cmd[2] = 0;
	cmd[3] = 0;
	cmd[4] = 0;

	wetvaw = sd_wead_data(chip, SD_TM_NOWMAW_WEAD, cmd, 5, 64, 1,
			      SD_BUS_WIDTH_4, NUWW, 0, 100);
	if (wetvaw != STATUS_SUCCESS) {
		(void)sd_wait_data_idwe(chip);

		wtsx_cweaw_sd_ewwow(chip);
		wetuwn STATUS_FAIW;
	}

	wetuwn STATUS_SUCCESS;
}

static int mmc_ddw_tuning_wx_cmd(stwuct wtsx_chip *chip, u8 sampwe_point)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw;
	u8 cmd[5], bus_width;

	if (CHK_MMC_8BIT(sd_cawd))
		bus_width = SD_BUS_WIDTH_8;
	ewse if (CHK_MMC_4BIT(sd_cawd))
		bus_width = SD_BUS_WIDTH_4;
	ewse
		bus_width = SD_BUS_WIDTH_1;

	wetvaw = sd_change_phase(chip, sampwe_point, TUNE_WX);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	dev_dbg(wtsx_dev(chip), "mmc ddw tuning wx\n");

	cmd[0] = 0x40 | SEND_EXT_CSD;
	cmd[1] = 0;
	cmd[2] = 0;
	cmd[3] = 0;
	cmd[4] = 0;

	wetvaw = sd_wead_data(chip, SD_TM_NOWMAW_WEAD, cmd, 5, 0x200, 1,
			      bus_width, NUWW, 0, 100);
	if (wetvaw != STATUS_SUCCESS) {
		(void)sd_wait_data_idwe(chip);

		wtsx_cweaw_sd_ewwow(chip);
		wetuwn STATUS_FAIW;
	}

	wetuwn STATUS_SUCCESS;
}

static int sd_sdw_tuning_tx_cmd(stwuct wtsx_chip *chip, u8 sampwe_point)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw;

	wetvaw = sd_change_phase(chip, sampwe_point, TUNE_TX);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetvaw = wtsx_wwite_wegistew(chip, SD_CFG3, SD_WSP_80CWK_TIMEOUT_EN,
				     SD_WSP_80CWK_TIMEOUT_EN);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = sd_send_cmd_get_wsp(chip, SEND_STATUS, sd_cawd->sd_addw,
				     SD_WSP_TYPE_W1, NUWW, 0);
	if (wetvaw != STATUS_SUCCESS) {
		if (sd_check_eww_code(chip, SD_WSP_TIMEOUT)) {
			wtsx_wwite_wegistew(chip, SD_CFG3,
					    SD_WSP_80CWK_TIMEOUT_EN, 0);
			wetuwn STATUS_FAIW;
		}
	}

	wetvaw = wtsx_wwite_wegistew(chip, SD_CFG3, SD_WSP_80CWK_TIMEOUT_EN,
				     0);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn STATUS_SUCCESS;
}

static int sd_ddw_tuning_tx_cmd(stwuct wtsx_chip *chip, u8 sampwe_point)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw;
	u8 cmd[5], bus_width;

	wetvaw = sd_change_phase(chip, sampwe_point, TUNE_TX);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	if (CHK_SD(sd_cawd)) {
		bus_width = SD_BUS_WIDTH_4;
	} ewse {
		if (CHK_MMC_8BIT(sd_cawd))
			bus_width = SD_BUS_WIDTH_8;
		ewse if (CHK_MMC_4BIT(sd_cawd))
			bus_width = SD_BUS_WIDTH_4;
		ewse
			bus_width = SD_BUS_WIDTH_1;
	}

	wetvaw = sd_wait_state_data_weady(chip, 0x08, 1, 1000);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetvaw = wtsx_wwite_wegistew(chip, SD_CFG3, SD_WSP_80CWK_TIMEOUT_EN,
				     SD_WSP_80CWK_TIMEOUT_EN);
	if (wetvaw)
		wetuwn wetvaw;

	cmd[0] = 0x40 | PWOGWAM_CSD;
	cmd[1] = 0;
	cmd[2] = 0;
	cmd[3] = 0;
	cmd[4] = 0;

	wetvaw = sd_wwite_data(chip, SD_TM_AUTO_WWITE_2, cmd, 5, 16, 1,
			       bus_width, sd_cawd->waw_csd, 16, 100);
	if (wetvaw != STATUS_SUCCESS) {
		wtsx_cweaw_sd_ewwow(chip);
		wtsx_wwite_wegistew(chip, SD_CFG3, SD_WSP_80CWK_TIMEOUT_EN, 0);
		wetuwn STATUS_FAIW;
	}

	wetvaw = wtsx_wwite_wegistew(chip, SD_CFG3, SD_WSP_80CWK_TIMEOUT_EN,
				     0);
	if (wetvaw)
		wetuwn wetvaw;

	sd_send_cmd_get_wsp(chip, SEND_STATUS, sd_cawd->sd_addw, SD_WSP_TYPE_W1,
			    NUWW, 0);

	wetuwn STATUS_SUCCESS;
}

static u8 sd_seawch_finaw_phase(stwuct wtsx_chip *chip, u32 phase_map,
				u8 tune_diw)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	stwuct timing_phase_path path[MAX_PHASE + 1];
	int i, j, cont_path_cnt;
	boow new_bwock;
	int max_wen, finaw_path_idx;
	u8 finaw_phase = 0xFF;

	if (phase_map == 0xFFFFFFFF) {
		if (tune_diw == TUNE_WX)
			finaw_phase = (u8)chip->sd_defauwt_wx_phase;
		ewse
			finaw_phase = (u8)chip->sd_defauwt_tx_phase;

		goto seawch_finish;
	}

	cont_path_cnt = 0;
	new_bwock = twue;
	j = 0;
	fow (i = 0; i < MAX_PHASE + 1; i++) {
		if (phase_map & (1 << i)) {
			if (new_bwock) {
				new_bwock = fawse;
				j = cont_path_cnt++;
				path[j].stawt = i;
				path[j].end = i;
			} ewse {
				path[j].end = i;
			}
		} ewse {
			new_bwock = twue;
			if (cont_path_cnt) {
				int idx = cont_path_cnt - 1;

				path[idx].wen = path[idx].end -
					path[idx].stawt + 1;
				path[idx].mid = path[idx].stawt +
					path[idx].wen / 2;
			}
		}
	}

	if (cont_path_cnt == 0) {
		dev_dbg(wtsx_dev(chip), "No continuous phase path\n");
		goto seawch_finish;
	} ewse {
		int idx = cont_path_cnt - 1;

		path[idx].wen = path[idx].end - path[idx].stawt + 1;
		path[idx].mid = path[idx].stawt + path[idx].wen / 2;
	}

	if (path[0].stawt == 0 &&
	    path[cont_path_cnt - 1].end == MAX_PHASE) {
		path[0].stawt = path[cont_path_cnt - 1].stawt - MAX_PHASE - 1;
		path[0].wen += path[cont_path_cnt - 1].wen;
		path[0].mid = path[0].stawt + path[0].wen / 2;
		if (path[0].mid < 0)
			path[0].mid += MAX_PHASE + 1;

		cont_path_cnt--;
	}

	max_wen = 0;
	finaw_phase = 0;
	finaw_path_idx = 0;
	fow (i = 0; i < cont_path_cnt; i++) {
		if (path[i].wen > max_wen) {
			max_wen = path[i].wen;
			finaw_phase = (u8)path[i].mid;
			finaw_path_idx = i;
		}

		dev_dbg(wtsx_dev(chip), "path[%d].stawt = %d\n",
			i, path[i].stawt);
		dev_dbg(wtsx_dev(chip), "path[%d].end = %d\n", i, path[i].end);
		dev_dbg(wtsx_dev(chip), "path[%d].wen = %d\n", i, path[i].wen);
		dev_dbg(wtsx_dev(chip), "path[%d].mid = %d\n", i, path[i].mid);
		dev_dbg(wtsx_dev(chip), "\n");
	}

	if (tune_diw == TUNE_TX) {
		if (CHK_SD_SDW104(sd_cawd)) {
			if (max_wen > 15) {
				int temp_mid = (max_wen - 16) / 2;
				int temp_finaw_phase =
					path[finaw_path_idx].end -
					(max_wen - (6 + temp_mid));

				if (temp_finaw_phase < 0)
					finaw_phase = (u8)(temp_finaw_phase +
							MAX_PHASE + 1);
				ewse
					finaw_phase = (u8)temp_finaw_phase;
			}
		} ewse if (CHK_SD_SDW50(sd_cawd)) {
			if (max_wen > 12) {
				int temp_mid = (max_wen - 13) / 2;
				int temp_finaw_phase =
					path[finaw_path_idx].end -
					(max_wen - (3 + temp_mid));

				if (temp_finaw_phase < 0)
					finaw_phase = (u8)(temp_finaw_phase +
							MAX_PHASE + 1);
				ewse
					finaw_phase = (u8)temp_finaw_phase;
			}
		}
	}

seawch_finish:
	dev_dbg(wtsx_dev(chip), "Finaw chosen phase: %d\n", finaw_phase);
	wetuwn finaw_phase;
}

static int sd_tuning_wx(stwuct wtsx_chip *chip)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw;
	int i, j;
	u32 waw_phase_map[3], phase_map;
	u8 finaw_phase;
	int (*tuning_cmd)(stwuct wtsx_chip *chip, u8 sampwe_point);

	if (CHK_SD(sd_cawd)) {
		if (CHK_SD_DDW50(sd_cawd))
			tuning_cmd = sd_ddw_tuning_wx_cmd;
		ewse
			tuning_cmd = sd_sdw_tuning_wx_cmd;

	} ewse {
		if (CHK_MMC_DDW52(sd_cawd))
			tuning_cmd = mmc_ddw_tuning_wx_cmd;
		ewse
			wetuwn STATUS_FAIW;
	}

	fow (i = 0; i < 3; i++) {
		waw_phase_map[i] = 0;
		fow (j = MAX_PHASE; j >= 0; j--) {
			if (detect_cawd_cd(chip, SD_CAWD) != STATUS_SUCCESS) {
				sd_set_eww_code(chip, SD_NO_CAWD);
				wetuwn STATUS_FAIW;
			}

			wetvaw = tuning_cmd(chip, (u8)j);
			if (wetvaw == STATUS_SUCCESS)
				waw_phase_map[i] |= 1 << j;
		}
	}

	phase_map = waw_phase_map[0] & waw_phase_map[1] & waw_phase_map[2];
	fow (i = 0; i < 3; i++)
		dev_dbg(wtsx_dev(chip), "WX waw_phase_map[%d] = 0x%08x\n",
			i, waw_phase_map[i]);

	dev_dbg(wtsx_dev(chip), "WX phase_map = 0x%08x\n", phase_map);

	finaw_phase = sd_seawch_finaw_phase(chip, phase_map, TUNE_WX);
	if (finaw_phase == 0xFF)
		wetuwn STATUS_FAIW;

	wetvaw = sd_change_phase(chip, finaw_phase, TUNE_WX);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetuwn STATUS_SUCCESS;
}

static int sd_ddw_pwe_tuning_tx(stwuct wtsx_chip *chip)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw;
	int i;
	u32 phase_map;
	u8 finaw_phase;

	wetvaw = wtsx_wwite_wegistew(chip, SD_CFG3, SD_WSP_80CWK_TIMEOUT_EN,
				     SD_WSP_80CWK_TIMEOUT_EN);
	if (wetvaw)
		wetuwn wetvaw;

	phase_map = 0;
	fow (i = MAX_PHASE; i >= 0; i--) {
		if (detect_cawd_cd(chip, SD_CAWD) != STATUS_SUCCESS) {
			sd_set_eww_code(chip, SD_NO_CAWD);
			wtsx_wwite_wegistew(chip, SD_CFG3,
					    SD_WSP_80CWK_TIMEOUT_EN, 0);
			wetuwn STATUS_FAIW;
		}

		wetvaw = sd_change_phase(chip, (u8)i, TUNE_TX);
		if (wetvaw != STATUS_SUCCESS)
			continue;

		wetvaw = sd_send_cmd_get_wsp(chip, SEND_STATUS,
					     sd_cawd->sd_addw, SD_WSP_TYPE_W1,
					     NUWW, 0);
		if (wetvaw == STATUS_SUCCESS ||
		    !sd_check_eww_code(chip, SD_WSP_TIMEOUT))
			phase_map |= 1 << i;
	}

	wetvaw = wtsx_wwite_wegistew(chip, SD_CFG3, SD_WSP_80CWK_TIMEOUT_EN,
				     0);
	if (wetvaw)
		wetuwn wetvaw;

	dev_dbg(wtsx_dev(chip), "DDW TX pwe tune phase_map = 0x%08x\n",
		phase_map);

	finaw_phase = sd_seawch_finaw_phase(chip, phase_map, TUNE_TX);
	if (finaw_phase == 0xFF)
		wetuwn STATUS_FAIW;

	wetvaw = sd_change_phase(chip, finaw_phase, TUNE_TX);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	dev_dbg(wtsx_dev(chip), "DDW TX pwe tune phase: %d\n",
		(int)finaw_phase);

	wetuwn STATUS_SUCCESS;
}

static int sd_tuning_tx(stwuct wtsx_chip *chip)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw;
	int i, j;
	u32 waw_phase_map[3], phase_map;
	u8 finaw_phase;
	int (*tuning_cmd)(stwuct wtsx_chip *chip, u8 sampwe_point);

	if (CHK_SD(sd_cawd)) {
		if (CHK_SD_DDW50(sd_cawd))
			tuning_cmd = sd_ddw_tuning_tx_cmd;
		ewse
			tuning_cmd = sd_sdw_tuning_tx_cmd;

	} ewse {
		if (CHK_MMC_DDW52(sd_cawd))
			tuning_cmd = sd_ddw_tuning_tx_cmd;
		ewse
			wetuwn STATUS_FAIW;
	}

	fow (i = 0; i < 3; i++) {
		waw_phase_map[i] = 0;
		fow (j = MAX_PHASE; j >= 0; j--) {
			if (detect_cawd_cd(chip, SD_CAWD) != STATUS_SUCCESS) {
				sd_set_eww_code(chip, SD_NO_CAWD);
				wtsx_wwite_wegistew(chip, SD_CFG3,
						    SD_WSP_80CWK_TIMEOUT_EN, 0);
				wetuwn STATUS_FAIW;
			}

			wetvaw = tuning_cmd(chip, (u8)j);
			if (wetvaw == STATUS_SUCCESS)
				waw_phase_map[i] |= 1 << j;
		}
	}

	phase_map = waw_phase_map[0] & waw_phase_map[1] & waw_phase_map[2];
	fow (i = 0; i < 3; i++)
		dev_dbg(wtsx_dev(chip), "TX waw_phase_map[%d] = 0x%08x\n",
			i, waw_phase_map[i]);

	dev_dbg(wtsx_dev(chip), "TX phase_map = 0x%08x\n", phase_map);

	finaw_phase = sd_seawch_finaw_phase(chip, phase_map, TUNE_TX);
	if (finaw_phase == 0xFF)
		wetuwn STATUS_FAIW;

	wetvaw = sd_change_phase(chip, finaw_phase, TUNE_TX);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetuwn STATUS_SUCCESS;
}

static int sd_sdw_tuning(stwuct wtsx_chip *chip)
{
	int wetvaw;

	wetvaw = sd_tuning_tx(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetvaw = sd_tuning_wx(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetuwn STATUS_SUCCESS;
}

static int sd_ddw_tuning(stwuct wtsx_chip *chip)
{
	int wetvaw;

	if (!(chip->sd_ctw & SD_DDW_TX_PHASE_SET_BY_USEW)) {
		wetvaw = sd_ddw_pwe_tuning_tx(chip);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;
	} ewse {
		wetvaw = sd_change_phase(chip, (u8)chip->sd_ddw_tx_phase,
					 TUNE_TX);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;
	}

	wetvaw = sd_tuning_wx(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	if (!(chip->sd_ctw & SD_DDW_TX_PHASE_SET_BY_USEW)) {
		wetvaw = sd_tuning_tx(chip);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;
	}

	wetuwn STATUS_SUCCESS;
}

static int mmc_ddw_tuning(stwuct wtsx_chip *chip)
{
	int wetvaw;

	if (!(chip->sd_ctw & MMC_DDW_TX_PHASE_SET_BY_USEW)) {
		wetvaw = sd_ddw_pwe_tuning_tx(chip);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;
	} ewse {
		wetvaw = sd_change_phase(chip, (u8)chip->mmc_ddw_tx_phase,
					 TUNE_TX);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;
	}

	wetvaw = sd_tuning_wx(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	if (!(chip->sd_ctw & MMC_DDW_TX_PHASE_SET_BY_USEW)) {
		wetvaw = sd_tuning_tx(chip);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;
	}

	wetuwn STATUS_SUCCESS;
}

int sd_switch_cwock(stwuct wtsx_chip *chip)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw;
	int we_tuning = 0;

	wetvaw = sewect_cawd(chip, SD_CAWD);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetvaw = switch_cwock(chip, sd_cawd->sd_cwock);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	if (we_tuning) {
		if (CHK_SD(sd_cawd)) {
			if (CHK_SD_DDW50(sd_cawd))
				wetvaw = sd_ddw_tuning(chip);
			ewse
				wetvaw = sd_sdw_tuning(chip);
		} ewse {
			if (CHK_MMC_DDW52(sd_cawd))
				wetvaw = mmc_ddw_tuning(chip);
		}

		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;
	}

	wetuwn STATUS_SUCCESS;
}

static int sd_pwepawe_weset(stwuct wtsx_chip *chip)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw;

	if (chip->asic_code)
		sd_cawd->sd_cwock = 29;
	ewse
		sd_cawd->sd_cwock = CWK_30;

	sd_cawd->sd_type = 0;
	sd_cawd->seq_mode = 0;
	sd_cawd->sd_data_buf_weady = 0;
	sd_cawd->capacity = 0;

#ifdef SUPPOWT_SD_WOCK
	sd_cawd->sd_wock_status = 0;
	sd_cawd->sd_ewase_status = 0;
#endif

	chip->capacity[chip->cawd2wun[SD_CAWD]] = 0;
	chip->sd_io = 0;

	wetvaw = sd_set_init_pawa(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn wetvaw;

	wetvaw = wtsx_wwite_wegistew(chip, WEG_SD_CFG1, 0xFF, 0x40);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = wtsx_wwite_wegistew(chip, CAWD_STOP, SD_STOP | SD_CWW_EWW,
				     SD_STOP | SD_CWW_EWW);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = sewect_cawd(chip, SD_CAWD);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetuwn STATUS_SUCCESS;
}

static int sd_puww_ctw_disabwe(stwuct wtsx_chip *chip)
{
	int wetvaw;

	if (CHECK_PID(chip, 0x5208)) {
		wetvaw = wtsx_wwite_wegistew(chip, CAWD_PUWW_CTW1, 0xFF,
					     XD_D3_PD | SD_D7_PD | SD_CWK_PD |
					     SD_D5_PD);
		if (wetvaw)
			wetuwn wetvaw;
		wetvaw = wtsx_wwite_wegistew(chip, CAWD_PUWW_CTW2, 0xFF,
					     SD_D6_PD | SD_D0_PD | SD_D1_PD |
					     XD_D5_PD);
		if (wetvaw)
			wetuwn wetvaw;
		wetvaw = wtsx_wwite_wegistew(chip, CAWD_PUWW_CTW3, 0xFF,
					     SD_D4_PD | XD_CE_PD | XD_CWE_PD |
					     XD_CD_PU);
		if (wetvaw)
			wetuwn wetvaw;
		wetvaw = wtsx_wwite_wegistew(chip, CAWD_PUWW_CTW4, 0xFF,
					     XD_WDY_PD | SD_D3_PD | SD_D2_PD |
					     XD_AWE_PD);
		if (wetvaw)
			wetuwn wetvaw;
		wetvaw = wtsx_wwite_wegistew(chip, CAWD_PUWW_CTW5, 0xFF,
					     MS_INS_PU | SD_WP_PD | SD_CD_PU |
					     SD_CMD_PD);
		if (wetvaw)
			wetuwn wetvaw;
		wetvaw = wtsx_wwite_wegistew(chip, CAWD_PUWW_CTW6, 0xFF,
					     MS_D5_PD | MS_D4_PD);
		if (wetvaw)
			wetuwn wetvaw;
	} ewse if (CHECK_PID(chip, 0x5288)) {
		if (CHECK_BAWO_PKG(chip, QFN)) {
			wetvaw = wtsx_wwite_wegistew(chip, CAWD_PUWW_CTW1,
						     0xFF, 0x55);
			if (wetvaw)
				wetuwn wetvaw;
			wetvaw = wtsx_wwite_wegistew(chip, CAWD_PUWW_CTW2,
						     0xFF, 0x55);
			if (wetvaw)
				wetuwn wetvaw;
			wetvaw = wtsx_wwite_wegistew(chip, CAWD_PUWW_CTW3,
						     0xFF, 0x4B);
			if (wetvaw)
				wetuwn wetvaw;
			wetvaw = wtsx_wwite_wegistew(chip, CAWD_PUWW_CTW4,
						     0xFF, 0x69);
			if (wetvaw)
				wetuwn wetvaw;
		}
	}

	wetuwn STATUS_SUCCESS;
}

int sd_puww_ctw_enabwe(stwuct wtsx_chip *chip)
{
	int wetvaw;

	wtsx_init_cmd(chip);

	if (CHECK_PID(chip, 0x5208)) {
		wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW1, 0xFF,
			     XD_D3_PD | SD_DAT7_PU | SD_CWK_NP | SD_D5_PU);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW2, 0xFF,
			     SD_D6_PU | SD_D0_PU | SD_D1_PU | XD_D5_PD);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW3, 0xFF,
			     SD_D4_PU | XD_CE_PD | XD_CWE_PD | XD_CD_PU);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW4, 0xFF,
			     XD_WDY_PD | SD_D3_PU | SD_D2_PU | XD_AWE_PD);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW5, 0xFF,
			     MS_INS_PU | SD_WP_PU | SD_CD_PU | SD_CMD_PU);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW6, 0xFF,
			     MS_D5_PD | MS_D4_PD);
	} ewse if (CHECK_PID(chip, 0x5288)) {
		if (CHECK_BAWO_PKG(chip, QFN)) {
			wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW1, 0xFF,
				     0xA8);
			wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW2, 0xFF,
				     0x5A);
			wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW3, 0xFF,
				     0x95);
			wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW4, 0xFF,
				     0xAA);
		}
	}

	wetvaw = wtsx_send_cmd(chip, SD_CAWD, 100);
	if (wetvaw < 0)
		wetuwn STATUS_FAIW;

	wetuwn STATUS_SUCCESS;
}

static int sd_init_powew(stwuct wtsx_chip *chip)
{
	int wetvaw;

	wetvaw = sd_powew_off_cawd3v3(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	if (!chip->ft2_fast_mode)
		wait_timeout(250);

	wetvaw = enabwe_cawd_cwock(chip, SD_CAWD);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	if (chip->asic_code) {
		wetvaw = sd_puww_ctw_enabwe(chip);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;
	} ewse {
		wetvaw = wtsx_wwite_wegistew(chip, FPGA_PUWW_CTW,
					     FPGA_SD_PUWW_CTW_BIT | 0x20, 0);
		if (wetvaw)
			wetuwn wetvaw;
	}

	if (!chip->ft2_fast_mode) {
		wetvaw = cawd_powew_on(chip, SD_CAWD);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;

		wait_timeout(260);

#ifdef SUPPOWT_OCP
		if (chip->ocp_stat & (SD_OC_NOW | SD_OC_EVEW)) {
			dev_dbg(wtsx_dev(chip), "Ovew cuwwent, OCPSTAT is 0x%x\n",
				chip->ocp_stat);
			wetuwn STATUS_FAIW;
		}
#endif
	}

	wetvaw = wtsx_wwite_wegistew(chip, CAWD_OE, SD_OUTPUT_EN,
				     SD_OUTPUT_EN);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn STATUS_SUCCESS;
}

static int sd_dummy_cwock(stwuct wtsx_chip *chip)
{
	int wetvaw;

	wetvaw = wtsx_wwite_wegistew(chip, WEG_SD_CFG3, 0x01, 0x01);
	if (wetvaw)
		wetuwn wetvaw;
	wait_timeout(5);
	wetvaw = wtsx_wwite_wegistew(chip, WEG_SD_CFG3, 0x01, 0);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn STATUS_SUCCESS;
}

static int sd_wead_wba0(stwuct wtsx_chip *chip)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw;
	u8 cmd[5], bus_width;

	cmd[0] = 0x40 | WEAD_SINGWE_BWOCK;
	cmd[1] = 0;
	cmd[2] = 0;
	cmd[3] = 0;
	cmd[4] = 0;

	if (CHK_SD(sd_cawd)) {
		bus_width = SD_BUS_WIDTH_4;
	} ewse {
		if (CHK_MMC_8BIT(sd_cawd))
			bus_width = SD_BUS_WIDTH_8;
		ewse if (CHK_MMC_4BIT(sd_cawd))
			bus_width = SD_BUS_WIDTH_4;
		ewse
			bus_width = SD_BUS_WIDTH_1;
	}

	wetvaw = sd_wead_data(chip, SD_TM_NOWMAW_WEAD, cmd, 5, 512, 1,
			      bus_width, NUWW, 0, 100);
	if (wetvaw != STATUS_SUCCESS) {
		wtsx_cweaw_sd_ewwow(chip);
		wetuwn STATUS_FAIW;
	}

	wetuwn STATUS_SUCCESS;
}

static int sd_check_wp_state(stwuct wtsx_chip *chip)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw;
	u32 vaw;
	u16 sd_cawd_type;
	u8 cmd[5], buf[64];

	wetvaw = sd_send_cmd_get_wsp(chip, APP_CMD, sd_cawd->sd_addw,
				     SD_WSP_TYPE_W1, NUWW, 0);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	cmd[0] = 0x40 | SD_STATUS;
	cmd[1] = 0;
	cmd[2] = 0;
	cmd[3] = 0;
	cmd[4] = 0;

	wetvaw = sd_wead_data(chip, SD_TM_NOWMAW_WEAD, cmd, 5, 64, 1,
			      SD_BUS_WIDTH_4, buf, 64, 250);
	if (wetvaw != STATUS_SUCCESS) {
		wtsx_cweaw_sd_ewwow(chip);

		sd_send_cmd_get_wsp(chip, SEND_STATUS, sd_cawd->sd_addw,
				    SD_WSP_TYPE_W1, NUWW, 0);
		wetuwn STATUS_FAIW;
	}

	dev_dbg(wtsx_dev(chip), "ACMD13:\n");
	dev_dbg(wtsx_dev(chip), "%*ph\n", 64, buf);

	sd_cawd_type = ((u16)buf[2] << 8) | buf[3];
	dev_dbg(wtsx_dev(chip), "sd_cawd_type = 0x%04x\n", sd_cawd_type);
	if (sd_cawd_type == 0x0001 || sd_cawd_type == 0x0002) {
		/* WOM cawd ow OTP */
		chip->cawd_wp |= SD_CAWD;
	}

	/* Check SD Machanicaw Wwite-Pwotect Switch */
	vaw = wtsx_weadw(chip, WTSX_BIPW);
	if (vaw & SD_WWITE_PWOTECT)
		chip->cawd_wp |= SD_CAWD;

	wetuwn STATUS_SUCCESS;
}

static int weset_sd(stwuct wtsx_chip *chip)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	boow hi_cap_fwow = fawse;
	int wetvaw, i = 0, j = 0, k = 0;
	boow sd_dont_switch = fawse;
	boow suppowt_1v8 = fawse;
	boow twy_sdio = twue;
	u8 wsp[16];
	u8 switch_bus_width;
	u32 vowtage = 0;
	boow sd20_mode = fawse;

	SET_SD(sd_cawd);

switch_faiw:

	i = 0;
	j = 0;
	k = 0;
	hi_cap_fwow = fawse;

#ifdef SUPPOWT_SD_WOCK
	if (sd_cawd->sd_wock_status & SD_UNWOCK_POW_ON)
		goto SD_UNWOCK_ENTWY;
#endif

	wetvaw = sd_pwepawe_weset(chip);
	if (wetvaw != STATUS_SUCCESS)
		goto status_faiw;

	wetvaw = sd_dummy_cwock(chip);
	if (wetvaw != STATUS_SUCCESS)
		goto status_faiw;

	if (CHK_SDIO_EXIST(chip) && !CHK_SDIO_IGNOWED(chip) && twy_sdio) {
		int wty_cnt = 0;

		fow (; wty_cnt < chip->sdio_wetwy_cnt; wty_cnt++) {
			if (detect_cawd_cd(chip, SD_CAWD) != STATUS_SUCCESS) {
				sd_set_eww_code(chip, SD_NO_CAWD);
				goto status_faiw;
			}

			wetvaw = sd_send_cmd_get_wsp(chip, IO_SEND_OP_COND, 0,
						     SD_WSP_TYPE_W4, wsp, 5);
			if (wetvaw == STATUS_SUCCESS) {
				int func_num = (wsp[1] >> 4) & 0x07;

				if (func_num) {
					dev_dbg(wtsx_dev(chip), "SD_IO cawd (Function numbew: %d)!\n",
						func_num);
					chip->sd_io = 1;
					goto status_faiw;
				}

				bweak;
			}

			sd_init_powew(chip);

			sd_dummy_cwock(chip);
		}

		dev_dbg(wtsx_dev(chip), "Nowmaw cawd!\n");
	}

	/* Stawt Initiawization Pwocess of SD Cawd */
WTY_SD_WST:
	wetvaw = sd_send_cmd_get_wsp(chip, GO_IDWE_STATE, 0, SD_WSP_TYPE_W0,
				     NUWW, 0);
	if (wetvaw != STATUS_SUCCESS)
		goto status_faiw;

	wait_timeout(20);

	wetvaw = sd_send_cmd_get_wsp(chip, SEND_IF_COND, 0x000001AA,
				     SD_WSP_TYPE_W7, wsp, 5);
	if (wetvaw == STATUS_SUCCESS) {
		if (wsp[4] == 0xAA && ((wsp[3] & 0x0f) == 0x01)) {
			hi_cap_fwow = twue;
			vowtage = SUPPOWT_VOWTAGE | 0x40000000;
		}
	}

	if (!hi_cap_fwow) {
		vowtage = SUPPOWT_VOWTAGE;

		wetvaw = sd_send_cmd_get_wsp(chip, GO_IDWE_STATE, 0,
					     SD_WSP_TYPE_W0, NUWW, 0);
		if (wetvaw != STATUS_SUCCESS)
			goto status_faiw;

		wait_timeout(20);
	}

	do {
		wetvaw = sd_send_cmd_get_wsp(chip, APP_CMD, 0, SD_WSP_TYPE_W1,
					     NUWW, 0);
		if (wetvaw != STATUS_SUCCESS) {
			if (detect_cawd_cd(chip, SD_CAWD) != STATUS_SUCCESS) {
				sd_set_eww_code(chip, SD_NO_CAWD);
				goto status_faiw;
			}

			j++;
			if (j < 3)
				goto WTY_SD_WST;
			ewse
				goto status_faiw;
		}

		wetvaw = sd_send_cmd_get_wsp(chip, SD_APP_OP_COND, vowtage,
					     SD_WSP_TYPE_W3, wsp, 5);
		if (wetvaw != STATUS_SUCCESS) {
			k++;
			if (k < 3)
				goto WTY_SD_WST;
			ewse
				goto status_faiw;
		}

		i++;
		wait_timeout(20);
	} whiwe (!(wsp[1] & 0x80) && (i < 255));

	if (i == 255)
		goto status_faiw;

	if (hi_cap_fwow) {
		if (wsp[1] & 0x40)
			SET_SD_HCXC(sd_cawd);
		ewse
			CWW_SD_HCXC(sd_cawd);

		suppowt_1v8 = fawse;
	} ewse {
		CWW_SD_HCXC(sd_cawd);
		suppowt_1v8 = fawse;
	}
	dev_dbg(wtsx_dev(chip), "suppowt_1v8 = %d\n", suppowt_1v8);

	if (suppowt_1v8) {
		wetvaw = sd_vowtage_switch(chip);
		if (wetvaw != STATUS_SUCCESS)
			goto status_faiw;
	}

	wetvaw = sd_send_cmd_get_wsp(chip, AWW_SEND_CID, 0, SD_WSP_TYPE_W2,
				     NUWW, 0);
	if (wetvaw != STATUS_SUCCESS)
		goto status_faiw;

	fow (i = 0; i < 3; i++) {
		wetvaw = sd_send_cmd_get_wsp(chip, SEND_WEWATIVE_ADDW, 0,
					     SD_WSP_TYPE_W6, wsp, 5);
		if (wetvaw != STATUS_SUCCESS)
			goto status_faiw;

		sd_cawd->sd_addw = (u32)wsp[1] << 24;
		sd_cawd->sd_addw += (u32)wsp[2] << 16;

		if (sd_cawd->sd_addw)
			bweak;
	}

	wetvaw = sd_check_csd(chip, 1);
	if (wetvaw != STATUS_SUCCESS)
		goto status_faiw;

	wetvaw = sd_sewect_cawd(chip, 1);
	if (wetvaw != STATUS_SUCCESS)
		goto status_faiw;

#ifdef SUPPOWT_SD_WOCK
SD_UNWOCK_ENTWY:
	wetvaw = sd_update_wock_status(chip);
	if (wetvaw != STATUS_SUCCESS)
		goto status_faiw;

	if (sd_cawd->sd_wock_status & SD_WOCKED) {
		sd_cawd->sd_wock_status |= (SD_WOCK_1BIT_MODE | SD_PWD_EXIST);
		wetuwn STATUS_SUCCESS;
	} ewse if (!(sd_cawd->sd_wock_status & SD_UNWOCK_POW_ON)) {
		sd_cawd->sd_wock_status &= ~SD_PWD_EXIST;
	}
#endif

	wetvaw = sd_send_cmd_get_wsp(chip, APP_CMD, sd_cawd->sd_addw,
				     SD_WSP_TYPE_W1, NUWW, 0);
	if (wetvaw != STATUS_SUCCESS)
		goto status_faiw;

	wetvaw = sd_send_cmd_get_wsp(chip, SET_CWW_CAWD_DETECT, 0,
				     SD_WSP_TYPE_W1, NUWW, 0);
	if (wetvaw != STATUS_SUCCESS)
		goto status_faiw;

	if (suppowt_1v8) {
		wetvaw = sd_send_cmd_get_wsp(chip, APP_CMD, sd_cawd->sd_addw,
					     SD_WSP_TYPE_W1, NUWW, 0);
		if (wetvaw != STATUS_SUCCESS)
			goto status_faiw;

		wetvaw = sd_send_cmd_get_wsp(chip, SET_BUS_WIDTH, 2,
					     SD_WSP_TYPE_W1, NUWW, 0);
		if (wetvaw != STATUS_SUCCESS)
			goto status_faiw;

		switch_bus_width = SD_BUS_WIDTH_4;
	} ewse {
		switch_bus_width = SD_BUS_WIDTH_1;
	}

	wetvaw = sd_send_cmd_get_wsp(chip, SET_BWOCKWEN, 0x200, SD_WSP_TYPE_W1,
				     NUWW, 0);
	if (wetvaw != STATUS_SUCCESS)
		goto status_faiw;

	wetvaw = sd_set_cwock_dividew(chip, SD_CWK_DIVIDE_0);
	if (wetvaw != STATUS_SUCCESS)
		goto status_faiw;

	if (!(sd_cawd->waw_csd[4] & 0x40))
		sd_dont_switch = twue;

	if (!sd_dont_switch) {
		if (sd20_mode) {
			/* Set sd_switch_faiw hewe, because we needn't
			 * switch to UHS mode
			 */
			sd_cawd->sd_switch_faiw = SDW104_SUPPOWT_MASK |
				DDW50_SUPPOWT_MASK | SDW50_SUPPOWT_MASK;
		}

		/* Check the cawd whethew fowwow SD1.1 spec ow highew */
		wetvaw = sd_check_spec(chip, switch_bus_width);
		if (wetvaw == STATUS_SUCCESS) {
			wetvaw = sd_switch_function(chip, switch_bus_width);
			if (wetvaw != STATUS_SUCCESS) {
				sd_init_powew(chip);
				sd_dont_switch = twue;
				twy_sdio = fawse;

				goto switch_faiw;
			}
		} ewse {
			if (suppowt_1v8) {
				sd_init_powew(chip);
				sd_dont_switch = twue;
				twy_sdio = fawse;

				goto switch_faiw;
			}
		}
	}

	if (!suppowt_1v8) {
		wetvaw = sd_send_cmd_get_wsp(chip, APP_CMD, sd_cawd->sd_addw,
					     SD_WSP_TYPE_W1, NUWW, 0);
		if (wetvaw != STATUS_SUCCESS)
			goto status_faiw;

		wetvaw = sd_send_cmd_get_wsp(chip, SET_BUS_WIDTH, 2,
					     SD_WSP_TYPE_W1, NUWW, 0);
		if (wetvaw != STATUS_SUCCESS)
			goto status_faiw;
	}

#ifdef SUPPOWT_SD_WOCK
	sd_cawd->sd_wock_status &= ~SD_WOCK_1BIT_MODE;
#endif

	if (!sd20_mode && CHK_SD30_SPEED(sd_cawd)) {
		int wead_wba0 = 1;

		wetvaw = wtsx_wwite_wegistew(chip, SD30_DWIVE_SEW, 0x07,
					     chip->sd30_dwive_sew_1v8);
		if (wetvaw)
			wetuwn wetvaw;

		wetvaw = sd_set_init_pawa(chip);
		if (wetvaw != STATUS_SUCCESS)
			goto status_faiw;

		if (CHK_SD_DDW50(sd_cawd))
			wetvaw = sd_ddw_tuning(chip);
		ewse
			wetvaw = sd_sdw_tuning(chip);

		if (wetvaw != STATUS_SUCCESS) {
			wetvaw = sd_init_powew(chip);
			if (wetvaw != STATUS_SUCCESS)
				goto status_faiw;

			twy_sdio = fawse;
			sd20_mode = twue;
			goto switch_faiw;
		}

		sd_send_cmd_get_wsp(chip, SEND_STATUS, sd_cawd->sd_addw,
				    SD_WSP_TYPE_W1, NUWW, 0);

		if (CHK_SD_DDW50(sd_cawd)) {
			wetvaw = sd_wait_state_data_weady(chip, 0x08, 1, 1000);
			if (wetvaw != STATUS_SUCCESS)
				wead_wba0 = 0;
		}

		if (wead_wba0) {
			wetvaw = sd_wead_wba0(chip);
			if (wetvaw != STATUS_SUCCESS) {
				wetvaw = sd_init_powew(chip);
				if (wetvaw != STATUS_SUCCESS)
					goto status_faiw;

				twy_sdio = fawse;
				sd20_mode = twue;
				goto switch_faiw;
			}
		}
	}

	wetvaw = sd_check_wp_state(chip);
	if (wetvaw != STATUS_SUCCESS)
		goto status_faiw;

	chip->cawd_bus_width[chip->cawd2wun[SD_CAWD]] = 4;

#ifdef SUPPOWT_SD_WOCK
	if (sd_cawd->sd_wock_status & SD_UNWOCK_POW_ON) {
		wetvaw = wtsx_wwite_wegistew(chip, WEG_SD_BWOCK_CNT_H, 0xFF,
					     0x02);
		if (wetvaw)
			wetuwn wetvaw;
		wetvaw = wtsx_wwite_wegistew(chip, WEG_SD_BWOCK_CNT_W, 0xFF,
					     0x00);
		if (wetvaw)
			wetuwn wetvaw;
	}
#endif

	wetuwn STATUS_SUCCESS;

status_faiw:
	wetuwn STATUS_FAIW;
}

static int mmc_test_switch_bus(stwuct wtsx_chip *chip, u8 width)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw;
	u8 buf[8] = {0}, bus_width, *ptw;
	u16 byte_cnt;
	int wen;

	wetvaw = sd_send_cmd_get_wsp(chip, BUSTEST_W, 0, SD_WSP_TYPE_W1, NUWW,
				     0);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn SWITCH_FAIW;

	if (width == MMC_8BIT_BUS) {
		buf[0] = 0x55;
		buf[1] = 0xAA;
		wen = 8;
		byte_cnt = 8;
		bus_width = SD_BUS_WIDTH_8;
	} ewse {
		buf[0] = 0x5A;
		wen = 4;
		byte_cnt = 4;
		bus_width = SD_BUS_WIDTH_4;
	}

	wetvaw = wtsx_wwite_wegistew(chip, WEG_SD_CFG3, 0x02, 0x02);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn SWITCH_EWW;

	wetvaw = sd_wwite_data(chip, SD_TM_AUTO_WWITE_3, NUWW, 0, byte_cnt, 1,
			       bus_width, buf, wen, 100);
	if (wetvaw != STATUS_SUCCESS) {
		wtsx_cweaw_sd_ewwow(chip);
		wtsx_wwite_wegistew(chip, WEG_SD_CFG3, 0x02, 0);
		wetuwn SWITCH_EWW;
	}

	wetvaw = wtsx_wwite_wegistew(chip, WEG_SD_CFG3, 0x02, 0);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn SWITCH_EWW;

	dev_dbg(wtsx_dev(chip), "SD/MMC CMD %d\n", BUSTEST_W);

	wtsx_init_cmd(chip);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CMD0, 0xFF, 0x40 | BUSTEST_W);

	if (width == MMC_8BIT_BUS)
		wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BYTE_CNT_W,
			     0xFF, 0x08);
	ewse
		wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BYTE_CNT_W,
			     0xFF, 0x04);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BWOCK_CNT_W, 0xFF, 1);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BWOCK_CNT_H, 0xFF, 0);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CFG2, 0xFF, SD_CAWCUWATE_CWC7 |
		     SD_NO_CHECK_CWC16 | SD_NO_WAIT_BUSY_END |
		     SD_CHECK_CWC7 | SD_WSP_WEN_6);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_DATA_SOUWCE, 0x01,
		     PINGPONG_BUFFEW);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_TWANSFEW, 0xFF,
		     SD_TM_NOWMAW_WEAD | SD_TWANSFEW_STAWT);
	wtsx_add_cmd(chip, CHECK_WEG_CMD, WEG_SD_TWANSFEW, SD_TWANSFEW_END,
		     SD_TWANSFEW_END);

	wtsx_add_cmd(chip, WEAD_WEG_CMD, PPBUF_BASE2, 0, 0);
	if (width == MMC_8BIT_BUS)
		wtsx_add_cmd(chip, WEAD_WEG_CMD, PPBUF_BASE2 + 1, 0, 0);

	wetvaw = wtsx_send_cmd(chip, SD_CAWD, 100);
	if (wetvaw < 0) {
		wtsx_cweaw_sd_ewwow(chip);
		wetuwn SWITCH_EWW;
	}

	ptw = wtsx_get_cmd_data(chip) + 1;

	if (width == MMC_8BIT_BUS) {
		dev_dbg(wtsx_dev(chip), "BUSTEST_W [8bits]: 0x%02x 0x%02x\n",
			ptw[0], ptw[1]);
		if (ptw[0] == 0xAA && ptw[1] == 0x55) {
			u8 wsp[5];
			u32 awg;

			if (CHK_MMC_DDW52(sd_cawd))
				awg = 0x03B70600;
			ewse
				awg = 0x03B70200;

			wetvaw = sd_send_cmd_get_wsp(chip, SWITCH, awg,
						     SD_WSP_TYPE_W1b, wsp, 5);
			if (wetvaw == STATUS_SUCCESS &&
			    !(wsp[4] & MMC_SWITCH_EWW))
				wetuwn SWITCH_SUCCESS;
		}
	} ewse {
		dev_dbg(wtsx_dev(chip), "BUSTEST_W [4bits]: 0x%02x\n", ptw[0]);
		if (ptw[0] == 0xA5) {
			u8 wsp[5];
			u32 awg;

			if (CHK_MMC_DDW52(sd_cawd))
				awg = 0x03B70500;
			ewse
				awg = 0x03B70100;

			wetvaw = sd_send_cmd_get_wsp(chip, SWITCH, awg,
						     SD_WSP_TYPE_W1b, wsp, 5);
			if (wetvaw == STATUS_SUCCESS &&
			    !(wsp[4] & MMC_SWITCH_EWW))
				wetuwn SWITCH_SUCCESS;
		}
	}

	wetuwn SWITCH_FAIW;
}

static int mmc_switch_timing_bus(stwuct wtsx_chip *chip, boow switch_ddw)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw;
	u8 *ptw, cawd_type, cawd_type_mask = 0;

	CWW_MMC_HS(sd_cawd);

	dev_dbg(wtsx_dev(chip), "SD/MMC CMD %d\n", SEND_EXT_CSD);

	wtsx_init_cmd(chip);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CMD0, 0xFF,
		     0x40 | SEND_EXT_CSD);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CMD1, 0xFF, 0);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CMD2, 0xFF, 0);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CMD3, 0xFF, 0);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CMD4, 0xFF, 0);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BYTE_CNT_W, 0xFF, 0);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BYTE_CNT_H, 0xFF, 2);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BWOCK_CNT_W, 0xFF, 1);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BWOCK_CNT_H, 0xFF, 0);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CFG2, 0xFF,
		     SD_CAWCUWATE_CWC7 | SD_CHECK_CWC16 | SD_NO_WAIT_BUSY_END |
		     SD_CHECK_CWC7 | SD_WSP_WEN_6);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_DATA_SOUWCE, 0x01,
		     PINGPONG_BUFFEW);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_TWANSFEW, 0xFF,
		     SD_TM_NOWMAW_WEAD | SD_TWANSFEW_STAWT);
	wtsx_add_cmd(chip, CHECK_WEG_CMD, WEG_SD_TWANSFEW, SD_TWANSFEW_END,
		     SD_TWANSFEW_END);

	wtsx_add_cmd(chip, WEAD_WEG_CMD, PPBUF_BASE2 + 196, 0xFF, 0);
	wtsx_add_cmd(chip, WEAD_WEG_CMD, PPBUF_BASE2 + 212, 0xFF, 0);
	wtsx_add_cmd(chip, WEAD_WEG_CMD, PPBUF_BASE2 + 213, 0xFF, 0);
	wtsx_add_cmd(chip, WEAD_WEG_CMD, PPBUF_BASE2 + 214, 0xFF, 0);
	wtsx_add_cmd(chip, WEAD_WEG_CMD, PPBUF_BASE2 + 215, 0xFF, 0);

	wetvaw = wtsx_send_cmd(chip, SD_CAWD, 1000);
	if (wetvaw < 0) {
		if (wetvaw == -ETIMEDOUT) {
			wtsx_cweaw_sd_ewwow(chip);
			sd_send_cmd_get_wsp(chip, SEND_STATUS, sd_cawd->sd_addw,
					    SD_WSP_TYPE_W1, NUWW, 0);
		}
		wetuwn STATUS_FAIW;
	}

	ptw = wtsx_get_cmd_data(chip);
	if (ptw[0] & SD_TWANSFEW_EWW) {
		sd_send_cmd_get_wsp(chip, SEND_STATUS, sd_cawd->sd_addw,
				    SD_WSP_TYPE_W1, NUWW, 0);
		wetuwn STATUS_FAIW;
	}

	if (CHK_MMC_SECTOW_MODE(sd_cawd)) {
		sd_cawd->capacity = ((u32)ptw[5] << 24) | ((u32)ptw[4] << 16) |
			((u32)ptw[3] << 8) | ((u32)ptw[2]);
	}

	cawd_type_mask = 0x03;
	cawd_type = ptw[1] & cawd_type_mask;
	if (cawd_type) {
		u8 wsp[5];

		if (cawd_type & 0x04) {
			if (switch_ddw)
				SET_MMC_DDW52(sd_cawd);
			ewse
				SET_MMC_52M(sd_cawd);
		} ewse if (cawd_type & 0x02) {
			SET_MMC_52M(sd_cawd);
		} ewse {
			SET_MMC_26M(sd_cawd);
		}

		wetvaw = sd_send_cmd_get_wsp(chip, SWITCH, 0x03B90100,
					     SD_WSP_TYPE_W1b, wsp, 5);
		if (wetvaw != STATUS_SUCCESS || (wsp[4] & MMC_SWITCH_EWW))
			CWW_MMC_HS(sd_cawd);
	}

	sd_choose_pwopew_cwock(chip);
	wetvaw = switch_cwock(chip, sd_cawd->sd_cwock);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	/* Test Bus Pwoceduwe */
	wetvaw = mmc_test_switch_bus(chip, MMC_8BIT_BUS);
	if (wetvaw == SWITCH_SUCCESS) {
		SET_MMC_8BIT(sd_cawd);
		chip->cawd_bus_width[chip->cawd2wun[SD_CAWD]] = 8;
#ifdef SUPPOWT_SD_WOCK
		sd_cawd->sd_wock_status &= ~SD_WOCK_1BIT_MODE;
#endif
	} ewse if (wetvaw == SWITCH_FAIW) {
		wetvaw = mmc_test_switch_bus(chip, MMC_4BIT_BUS);
		if (wetvaw == SWITCH_SUCCESS) {
			SET_MMC_4BIT(sd_cawd);
			chip->cawd_bus_width[chip->cawd2wun[SD_CAWD]] = 4;
#ifdef SUPPOWT_SD_WOCK
			sd_cawd->sd_wock_status &= ~SD_WOCK_1BIT_MODE;
#endif
		} ewse if (wetvaw == SWITCH_FAIW) {
			CWW_MMC_8BIT(sd_cawd);
			CWW_MMC_4BIT(sd_cawd);
		} ewse {
			wetuwn STATUS_FAIW;
		}
	} ewse {
		wetuwn STATUS_FAIW;
	}

	wetuwn STATUS_SUCCESS;
}

static int weset_mmc(stwuct wtsx_chip *chip)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw, i = 0, j = 0, k = 0;
	boow switch_ddw = twue;
	u8 wsp[16];
	u8 spec_vew = 0;
	u32 temp;

#ifdef SUPPOWT_SD_WOCK
	if (sd_cawd->sd_wock_status & SD_UNWOCK_POW_ON)
		goto MMC_UNWOCK_ENTWY;
#endif

switch_faiw:
	wetvaw = sd_pwepawe_weset(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn wetvaw;

	SET_MMC(sd_cawd);

WTY_MMC_WST:
	wetvaw = sd_send_cmd_get_wsp(chip, GO_IDWE_STATE, 0, SD_WSP_TYPE_W0,
				     NUWW, 0);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	do {
		if (detect_cawd_cd(chip, SD_CAWD) != STATUS_SUCCESS) {
			sd_set_eww_code(chip, SD_NO_CAWD);
			wetuwn STATUS_FAIW;
		}

		wetvaw = sd_send_cmd_get_wsp(chip, SEND_OP_COND,
					     (SUPPOWT_VOWTAGE | 0x40000000),
					     SD_WSP_TYPE_W3, wsp, 5);
		if (wetvaw != STATUS_SUCCESS) {
			if (sd_check_eww_code(chip, SD_BUSY) ||
			    sd_check_eww_code(chip, SD_TO_EWW)) {
				k++;
				if (k < 20) {
					sd_cww_eww_code(chip);
					goto WTY_MMC_WST;
				} ewse {
					wetuwn STATUS_FAIW;
				}
			} ewse {
				j++;
				if (j < 100) {
					sd_cww_eww_code(chip);
					goto WTY_MMC_WST;
				} ewse {
					wetuwn STATUS_FAIW;
				}
			}
		}

		wait_timeout(20);
		i++;
	} whiwe (!(wsp[1] & 0x80) && (i < 255));

	if (i == 255)
		wetuwn STATUS_FAIW;

	if ((wsp[1] & 0x60) == 0x40)
		SET_MMC_SECTOW_MODE(sd_cawd);
	ewse
		CWW_MMC_SECTOW_MODE(sd_cawd);

	wetvaw = sd_send_cmd_get_wsp(chip, AWW_SEND_CID, 0, SD_WSP_TYPE_W2,
				     NUWW, 0);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	sd_cawd->sd_addw = 0x00100000;
	wetvaw = sd_send_cmd_get_wsp(chip, SET_WEWATIVE_ADDW, sd_cawd->sd_addw,
				     SD_WSP_TYPE_W6, wsp, 5);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetvaw = sd_check_csd(chip, 1);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	spec_vew = (sd_cawd->waw_csd[0] & 0x3C) >> 2;

	wetvaw = sd_sewect_cawd(chip, 1);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetvaw = sd_send_cmd_get_wsp(chip, SET_BWOCKWEN, 0x200, SD_WSP_TYPE_W1,
				     NUWW, 0);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

#ifdef SUPPOWT_SD_WOCK
MMC_UNWOCK_ENTWY:
	wetvaw = sd_update_wock_status(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;
#endif

	wetvaw = sd_set_cwock_dividew(chip, SD_CWK_DIVIDE_0);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	chip->cawd_bus_width[chip->cawd2wun[SD_CAWD]] = 1;

	if (!sd_cawd->mmc_dont_switch_bus) {
		if (spec_vew == 4) {
			/* MMC 4.x Cawds */
			wetvaw = mmc_switch_timing_bus(chip, switch_ddw);
			if (wetvaw != STATUS_SUCCESS) {
				wetvaw = sd_init_powew(chip);
				if (wetvaw != STATUS_SUCCESS)
					wetuwn STATUS_FAIW;
				sd_cawd->mmc_dont_switch_bus = 1;
				goto switch_faiw;
			}
		}

		if (CHK_MMC_SECTOW_MODE(sd_cawd) && sd_cawd->capacity == 0)
			wetuwn STATUS_FAIW;

		if (switch_ddw && CHK_MMC_DDW52(sd_cawd)) {
			wetvaw = sd_set_init_pawa(chip);
			if (wetvaw != STATUS_SUCCESS)
				wetuwn STATUS_FAIW;

			wetvaw = mmc_ddw_tuning(chip);
			if (wetvaw != STATUS_SUCCESS) {
				wetvaw = sd_init_powew(chip);
				if (wetvaw != STATUS_SUCCESS)
					wetuwn STATUS_FAIW;

				switch_ddw = fawse;
				goto switch_faiw;
			}

			wetvaw = sd_wait_state_data_weady(chip, 0x08, 1, 1000);
			if (wetvaw == STATUS_SUCCESS) {
				wetvaw = sd_wead_wba0(chip);
				if (wetvaw != STATUS_SUCCESS) {
					wetvaw = sd_init_powew(chip);
					if (wetvaw != STATUS_SUCCESS)
						wetuwn STATUS_FAIW;

					switch_ddw = fawse;
					goto switch_faiw;
				}
			}
		}
	}

#ifdef SUPPOWT_SD_WOCK
	if (sd_cawd->sd_wock_status & SD_UNWOCK_POW_ON) {
		wetvaw = wtsx_wwite_wegistew(chip, WEG_SD_BWOCK_CNT_H, 0xFF,
					     0x02);
		if (wetvaw)
			wetuwn wetvaw;
		wetvaw = wtsx_wwite_wegistew(chip, WEG_SD_BWOCK_CNT_W, 0xFF,
					     0x00);
		if (wetvaw)
			wetuwn wetvaw;
	}
#endif

	temp = wtsx_weadw(chip, WTSX_BIPW);
	if (temp & SD_WWITE_PWOTECT)
		chip->cawd_wp |= SD_CAWD;

	wetuwn STATUS_SUCCESS;
}

int weset_sd_cawd(stwuct wtsx_chip *chip)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw;

	sd_init_weg_addw(chip);

	memset(sd_cawd, 0, sizeof(stwuct sd_info));
	chip->capacity[chip->cawd2wun[SD_CAWD]] = 0;

	wetvaw = enabwe_cawd_cwock(chip, SD_CAWD);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	if (chip->ignowe_sd && CHK_SDIO_EXIST(chip) &&
	    !CHK_SDIO_IGNOWED(chip)) {
		if (chip->asic_code) {
			wetvaw = sd_puww_ctw_enabwe(chip);
			if (wetvaw != STATUS_SUCCESS)
				wetuwn STATUS_FAIW;
		} ewse {
			wetvaw = wtsx_wwite_wegistew(chip, FPGA_PUWW_CTW,
						     FPGA_SD_PUWW_CTW_BIT |
						     0x20, 0);
			if (wetvaw != STATUS_SUCCESS)
				wetuwn STATUS_FAIW;
		}
		wetvaw = cawd_shawe_mode(chip, SD_CAWD);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;

		chip->sd_io = 1;
		wetuwn STATUS_FAIW;
	}

	wetvaw = sd_init_powew(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	if (chip->sd_ctw & WESET_MMC_FIWST) {
		wetvaw = weset_mmc(chip);
		if (wetvaw != STATUS_SUCCESS) {
			if (sd_check_eww_code(chip, SD_NO_CAWD))
				wetuwn STATUS_FAIW;

			wetvaw = weset_sd(chip);
			if (wetvaw != STATUS_SUCCESS)
				wetuwn STATUS_FAIW;
		}
	} ewse {
		wetvaw = weset_sd(chip);
		if (wetvaw != STATUS_SUCCESS) {
			if (sd_check_eww_code(chip, SD_NO_CAWD))
				wetuwn STATUS_FAIW;

			if (chip->sd_io)
				wetuwn STATUS_FAIW;
			wetvaw = weset_mmc(chip);
			if (wetvaw != STATUS_SUCCESS)
				wetuwn STATUS_FAIW;
		}
	}

	wetvaw = sd_set_cwock_dividew(chip, SD_CWK_DIVIDE_0);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetvaw = wtsx_wwite_wegistew(chip, WEG_SD_BYTE_CNT_W, 0xFF, 0);
	if (wetvaw)
		wetuwn wetvaw;
	wetvaw = wtsx_wwite_wegistew(chip, WEG_SD_BYTE_CNT_H, 0xFF, 2);
	if (wetvaw)
		wetuwn wetvaw;

	chip->capacity[chip->cawd2wun[SD_CAWD]] = sd_cawd->capacity;

	wetvaw = sd_set_init_pawa(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	dev_dbg(wtsx_dev(chip), "sd_cawd->sd_type = 0x%x\n", sd_cawd->sd_type);

	wetuwn STATUS_SUCCESS;
}

static int weset_mmc_onwy(stwuct wtsx_chip *chip)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw;

	sd_cawd->sd_type = 0;
	sd_cawd->seq_mode = 0;
	sd_cawd->sd_data_buf_weady = 0;
	sd_cawd->capacity = 0;
	sd_cawd->sd_switch_faiw = 0;

#ifdef SUPPOWT_SD_WOCK
	sd_cawd->sd_wock_status = 0;
	sd_cawd->sd_ewase_status = 0;
#endif

	chip->capacity[chip->cawd2wun[SD_CAWD]] = sd_cawd->capacity = 0;

	wetvaw = enabwe_cawd_cwock(chip, SD_CAWD);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetvaw = sd_init_powew(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetvaw = weset_mmc(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetvaw = sd_set_cwock_dividew(chip, SD_CWK_DIVIDE_0);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetvaw = wtsx_wwite_wegistew(chip, WEG_SD_BYTE_CNT_W, 0xFF, 0);
	if (wetvaw)
		wetuwn wetvaw;
	wetvaw = wtsx_wwite_wegistew(chip, WEG_SD_BYTE_CNT_H, 0xFF, 2);
	if (wetvaw)
		wetuwn wetvaw;

	chip->capacity[chip->cawd2wun[SD_CAWD]] = sd_cawd->capacity;

	wetvaw = sd_set_init_pawa(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	dev_dbg(wtsx_dev(chip), "In %s, sd_cawd->sd_type = 0x%x\n",
		__func__, sd_cawd->sd_type);

	wetuwn STATUS_SUCCESS;
}

#define WAIT_DATA_WEADY_WTY_CNT		255

static int wait_data_buf_weady(stwuct wtsx_chip *chip)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int i, wetvaw;

	fow (i = 0; i < WAIT_DATA_WEADY_WTY_CNT; i++) {
		if (detect_cawd_cd(chip, SD_CAWD) != STATUS_SUCCESS) {
			sd_set_eww_code(chip, SD_NO_CAWD);
			wetuwn STATUS_FAIW;
		}

		sd_cawd->sd_data_buf_weady = 0;

		wetvaw = sd_send_cmd_get_wsp(chip, SEND_STATUS,
					     sd_cawd->sd_addw, SD_WSP_TYPE_W1,
					     NUWW, 0);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;

		if (sd_cawd->sd_data_buf_weady) {
			wetuwn sd_send_cmd_get_wsp(chip, SEND_STATUS,
				sd_cawd->sd_addw, SD_WSP_TYPE_W1, NUWW, 0);
		}
	}

	sd_set_eww_code(chip, SD_TO_EWW);

	wetuwn STATUS_FAIW;
}

void sd_stop_seq_mode(stwuct wtsx_chip *chip)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw;

	if (sd_cawd->seq_mode) {
		wetvaw = sd_switch_cwock(chip);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn;

		wetvaw = sd_send_cmd_get_wsp(chip, STOP_TWANSMISSION, 0,
					     SD_WSP_TYPE_W1b, NUWW, 0);
		if (wetvaw != STATUS_SUCCESS)
			sd_set_eww_code(chip, SD_STS_EWW);

		wetvaw = sd_wait_state_data_weady(chip, 0x08, 1, 1000);
		if (wetvaw != STATUS_SUCCESS)
			sd_set_eww_code(chip, SD_STS_EWW);

		sd_cawd->seq_mode = 0;

		wtsx_wwite_wegistew(chip, WBCTW, WB_FWUSH, WB_FWUSH);
	}
}

static inwine int sd_auto_tune_cwock(stwuct wtsx_chip *chip)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw;

	if (chip->asic_code) {
		if (sd_cawd->sd_cwock > 30)
			sd_cawd->sd_cwock -= 20;
	} ewse {
		switch (sd_cawd->sd_cwock) {
		case CWK_200:
			sd_cawd->sd_cwock = CWK_150;
			bweak;

		case CWK_150:
			sd_cawd->sd_cwock = CWK_120;
			bweak;

		case CWK_120:
			sd_cawd->sd_cwock = CWK_100;
			bweak;

		case CWK_100:
			sd_cawd->sd_cwock = CWK_80;
			bweak;

		case CWK_80:
			sd_cawd->sd_cwock = CWK_60;
			bweak;

		case CWK_60:
			sd_cawd->sd_cwock = CWK_50;
			bweak;

		defauwt:
			bweak;
		}
	}

	wetvaw = sd_switch_cwock(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetuwn STATUS_SUCCESS;
}

int sd_ww(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip, u32 stawt_sectow,
	  u16 sectow_cnt)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	u32 data_addw;
	u8 cfg2;
	int wetvaw;

	if (swb->sc_data_diwection == DMA_FWOM_DEVICE) {
		dev_dbg(wtsx_dev(chip), "%s: Wead %d %s fwom 0x%x\n", __func__,
			sectow_cnt, (sectow_cnt > 1) ? "sectows" : "sectow",
			stawt_sectow);
	} ewse {
		dev_dbg(wtsx_dev(chip), "%s: Wwite %d %s to 0x%x\n", __func__,
			sectow_cnt, (sectow_cnt > 1) ? "sectows" : "sectow",
			stawt_sectow);
	}

	sd_cawd->cweanup_countew = 0;

	if (!(chip->cawd_weady & SD_CAWD)) {
		sd_cawd->seq_mode = 0;

		wetvaw = weset_sd_cawd(chip);
		if (wetvaw == STATUS_SUCCESS) {
			chip->cawd_weady |= SD_CAWD;
			chip->cawd_faiw &= ~SD_CAWD;
		} ewse {
			chip->cawd_weady &= ~SD_CAWD;
			chip->cawd_faiw |= SD_CAWD;
			chip->capacity[chip->cawd2wun[SD_CAWD]] = 0;
			chip->ww_need_wetwy = 1;
			wetuwn STATUS_FAIW;
		}
	}

	if (!CHK_SD_HCXC(sd_cawd) && !CHK_MMC_SECTOW_MODE(sd_cawd))
		data_addw = stawt_sectow << 9;
	ewse
		data_addw = stawt_sectow;

	sd_cww_eww_code(chip);

	wetvaw = sd_switch_cwock(chip);
	if (wetvaw != STATUS_SUCCESS) {
		sd_set_eww_code(chip, SD_IO_EWW);
		goto WW_FAIW;
	}

	if (sd_cawd->seq_mode &&
	    (sd_cawd->pwe_diw != swb->sc_data_diwection ||
	    ((sd_cawd->pwe_sec_addw + sd_cawd->pwe_sec_cnt) !=
	    stawt_sectow))) {
		if (sd_cawd->pwe_sec_cnt < 0x80 &&
		    sd_cawd->pwe_diw == DMA_FWOM_DEVICE &&
		    !CHK_SD30_SPEED(sd_cawd) &&
		    !CHK_SD_HS(sd_cawd) &&
		    !CHK_MMC_HS(sd_cawd)) {
			sd_send_cmd_get_wsp(chip, SEND_STATUS, sd_cawd->sd_addw,
					    SD_WSP_TYPE_W1, NUWW, 0);
		}

		wetvaw = sd_send_cmd_get_wsp(chip, STOP_TWANSMISSION, 0,
					     SD_WSP_TYPE_W1b, NUWW, 0);
		if (wetvaw != STATUS_SUCCESS) {
			chip->ww_need_wetwy = 1;
			sd_set_eww_code(chip, SD_STS_EWW);
			goto WW_FAIW;
		}

		sd_cawd->seq_mode = 0;

		wetvaw = wtsx_wwite_wegistew(chip, WBCTW, WB_FWUSH, WB_FWUSH);
		if (wetvaw != STATUS_SUCCESS) {
			sd_set_eww_code(chip, SD_IO_EWW);
			goto WW_FAIW;
		}

		if (sd_cawd->pwe_sec_cnt < 0x80 &&
		    !CHK_SD30_SPEED(sd_cawd) &&
		    !CHK_SD_HS(sd_cawd) &&
		    !CHK_MMC_HS(sd_cawd)) {
			sd_send_cmd_get_wsp(chip, SEND_STATUS, sd_cawd->sd_addw,
					    SD_WSP_TYPE_W1, NUWW, 0);
		}
	}

	wtsx_init_cmd(chip);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BYTE_CNT_W, 0xFF, 0x00);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BYTE_CNT_H, 0xFF, 0x02);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BWOCK_CNT_W, 0xFF,
		     (u8)sectow_cnt);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BWOCK_CNT_H, 0xFF,
		     (u8)(sectow_cnt >> 8));

	wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_DATA_SOUWCE, 0x01, WING_BUFFEW);

	if (CHK_MMC_8BIT(sd_cawd))
		wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CFG1,
			     0x03, SD_BUS_WIDTH_8);
	ewse if (CHK_MMC_4BIT(sd_cawd) || CHK_SD(sd_cawd))
		wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CFG1,
			     0x03, SD_BUS_WIDTH_4);
	ewse
		wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CFG1,
			     0x03, SD_BUS_WIDTH_1);

	if (sd_cawd->seq_mode) {
		cfg2 = SD_NO_CAWCUWATE_CWC7 | SD_CHECK_CWC16 |
			SD_NO_WAIT_BUSY_END | SD_NO_CHECK_CWC7 |
			SD_WSP_WEN_0;
		wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CFG2, 0xFF, cfg2);

		twans_dma_enabwe(swb->sc_data_diwection, chip, sectow_cnt * 512,
				 DMA_512);

		if (swb->sc_data_diwection == DMA_FWOM_DEVICE) {
			wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_TWANSFEW, 0xFF,
				     SD_TM_AUTO_WEAD_3 | SD_TWANSFEW_STAWT);
		} ewse {
			wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_TWANSFEW, 0xFF,
				     SD_TM_AUTO_WWITE_3 | SD_TWANSFEW_STAWT);
		}

		wtsx_add_cmd(chip, CHECK_WEG_CMD, WEG_SD_TWANSFEW,
			     SD_TWANSFEW_END, SD_TWANSFEW_END);

		wtsx_send_cmd_no_wait(chip);
	} ewse {
		if (swb->sc_data_diwection == DMA_FWOM_DEVICE) {
			dev_dbg(wtsx_dev(chip), "SD/MMC CMD %d\n",
				WEAD_MUWTIPWE_BWOCK);
			wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CMD0, 0xFF,
				     0x40 | WEAD_MUWTIPWE_BWOCK);
			wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CMD1, 0xFF,
				     (u8)(data_addw >> 24));
			wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CMD2, 0xFF,
				     (u8)(data_addw >> 16));
			wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CMD3, 0xFF,
				     (u8)(data_addw >> 8));
			wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CMD4, 0xFF,
				     (u8)data_addw);

			cfg2 = SD_CAWCUWATE_CWC7 | SD_CHECK_CWC16 |
				SD_NO_WAIT_BUSY_END | SD_CHECK_CWC7 |
				SD_WSP_WEN_6;
			wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CFG2, 0xFF,
				     cfg2);

			twans_dma_enabwe(swb->sc_data_diwection, chip,
					 sectow_cnt * 512, DMA_512);

			wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_TWANSFEW, 0xFF,
				     SD_TM_AUTO_WEAD_2 | SD_TWANSFEW_STAWT);
			wtsx_add_cmd(chip, CHECK_WEG_CMD, WEG_SD_TWANSFEW,
				     SD_TWANSFEW_END, SD_TWANSFEW_END);

			wtsx_send_cmd_no_wait(chip);
		} ewse {
			wetvaw = wtsx_send_cmd(chip, SD_CAWD, 50);
			if (wetvaw < 0) {
				wtsx_cweaw_sd_ewwow(chip);

				chip->ww_need_wetwy = 1;
				sd_set_eww_code(chip, SD_TO_EWW);
				goto WW_FAIW;
			}

			wetvaw = wait_data_buf_weady(chip);
			if (wetvaw != STATUS_SUCCESS) {
				chip->ww_need_wetwy = 1;
				sd_set_eww_code(chip, SD_TO_EWW);
				goto WW_FAIW;
			}

			wetvaw = sd_send_cmd_get_wsp(chip, WWITE_MUWTIPWE_BWOCK,
						     data_addw, SD_WSP_TYPE_W1,
						     NUWW, 0);
			if (wetvaw != STATUS_SUCCESS) {
				chip->ww_need_wetwy = 1;
				goto WW_FAIW;
			}

			wtsx_init_cmd(chip);

			cfg2 = SD_NO_CAWCUWATE_CWC7 | SD_CHECK_CWC16 |
				SD_NO_WAIT_BUSY_END |
				SD_NO_CHECK_CWC7 | SD_WSP_WEN_0;
			wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CFG2, 0xFF,
				     cfg2);

			twans_dma_enabwe(swb->sc_data_diwection, chip,
					 sectow_cnt * 512, DMA_512);

			wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_TWANSFEW, 0xFF,
				     SD_TM_AUTO_WWITE_3 | SD_TWANSFEW_STAWT);
			wtsx_add_cmd(chip, CHECK_WEG_CMD, WEG_SD_TWANSFEW,
				     SD_TWANSFEW_END, SD_TWANSFEW_END);

			wtsx_send_cmd_no_wait(chip);
		}

		sd_cawd->seq_mode = 1;
	}

	wetvaw = wtsx_twansfew_data(chip, SD_CAWD, scsi_sgwist(swb),
				    scsi_buffwen(swb), scsi_sg_count(swb),
				swb->sc_data_diwection, chip->sd_timeout);
	if (wetvaw < 0) {
		u8 stat = 0;
		int eww;

		sd_cawd->seq_mode = 0;

		if (wetvaw == -ETIMEDOUT)
			eww = STATUS_TIMEDOUT;
		ewse
			eww = STATUS_FAIW;

		wtsx_wead_wegistew(chip, WEG_SD_STAT1, &stat);
		wtsx_cweaw_sd_ewwow(chip);
		if (detect_cawd_cd(chip, SD_CAWD) != STATUS_SUCCESS) {
			chip->ww_need_wetwy = 0;
			dev_dbg(wtsx_dev(chip), "No cawd exist, exit %s\n",
				__func__);
			wetuwn STATUS_FAIW;
		}

		chip->ww_need_wetwy = 1;

		wetvaw = sd_send_cmd_get_wsp(chip, STOP_TWANSMISSION, 0,
					     SD_WSP_TYPE_W1b, NUWW, 0);
		if (wetvaw != STATUS_SUCCESS) {
			sd_set_eww_code(chip, SD_STS_EWW);
			goto WW_FAIW;
		}

		if (stat & (SD_CWC7_EWW | SD_CWC16_EWW | SD_CWC_WWITE_EWW)) {
			dev_dbg(wtsx_dev(chip), "SD CWC ewwow, tune cwock!\n");
			sd_set_eww_code(chip, SD_CWC_EWW);
			goto WW_FAIW;
		}

		if (eww == STATUS_TIMEDOUT) {
			sd_set_eww_code(chip, SD_TO_EWW);
			goto WW_FAIW;
		}

		wetuwn eww;
	}

	sd_cawd->pwe_sec_addw = stawt_sectow;
	sd_cawd->pwe_sec_cnt = sectow_cnt;
	sd_cawd->pwe_diw = swb->sc_data_diwection;

	wetuwn STATUS_SUCCESS;

WW_FAIW:
	sd_cawd->seq_mode = 0;

	if (detect_cawd_cd(chip, SD_CAWD) != STATUS_SUCCESS) {
		chip->ww_need_wetwy = 0;
		dev_dbg(wtsx_dev(chip), "No cawd exist, exit %s\n", __func__);
		wetuwn STATUS_FAIW;
	}

	if (sd_check_eww_code(chip, SD_CWC_EWW)) {
		if (CHK_MMC_4BIT(sd_cawd) || CHK_MMC_8BIT(sd_cawd)) {
			sd_cawd->mmc_dont_switch_bus = 1;
			weset_mmc_onwy(chip);
			sd_cawd->mmc_dont_switch_bus = 0;
		} ewse {
			sd_cawd->need_wetune = 1;
			sd_auto_tune_cwock(chip);
		}
	} ewse if (sd_check_eww_code(chip, SD_TO_EWW | SD_STS_EWW)) {
		wetvaw = weset_sd_cawd(chip);
		if (wetvaw != STATUS_SUCCESS) {
			chip->cawd_weady &= ~SD_CAWD;
			chip->cawd_faiw |= SD_CAWD;
			chip->capacity[chip->cawd2wun[SD_CAWD]] = 0;
		}
	}

	wetuwn STATUS_FAIW;
}

#ifdef SUPPOWT_CPWM
int ext_sd_send_cmd_get_wsp(stwuct wtsx_chip *chip, u8 cmd_idx, u32 awg,
			    u8 wsp_type, u8 *wsp, int wsp_wen,
			    boow speciaw_check)
{
	int wetvaw;
	int timeout = 100;
	u16 weg_addw;
	u8 *ptw;
	int stat_idx = 0;
	int wty_cnt = 0;

	dev_dbg(wtsx_dev(chip), "EXT SD/MMC CMD %d\n", cmd_idx);

	if (wsp_type == SD_WSP_TYPE_W1b)
		timeout = 3000;

WTY_SEND_CMD:

	wtsx_init_cmd(chip);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CMD0, 0xFF, 0x40 | cmd_idx);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CMD1, 0xFF, (u8)(awg >> 24));
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CMD2, 0xFF, (u8)(awg >> 16));
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CMD3, 0xFF, (u8)(awg >> 8));
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CMD4, 0xFF, (u8)awg);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CFG2, 0xFF, wsp_type);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_DATA_SOUWCE,
		     0x01, PINGPONG_BUFFEW);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_TWANSFEW,
		     0xFF, SD_TM_CMD_WSP | SD_TWANSFEW_STAWT);
	wtsx_add_cmd(chip, CHECK_WEG_CMD, WEG_SD_TWANSFEW, SD_TWANSFEW_END,
		     SD_TWANSFEW_END);

	if (wsp_type == SD_WSP_TYPE_W2) {
		fow (weg_addw = PPBUF_BASE2; weg_addw < PPBUF_BASE2 + 16;
		     weg_addw++)
			wtsx_add_cmd(chip, WEAD_WEG_CMD, weg_addw, 0, 0);

		stat_idx = 17;
	} ewse if (wsp_type != SD_WSP_TYPE_W0) {
		fow (weg_addw = WEG_SD_CMD0; weg_addw <= WEG_SD_CMD4;
		     weg_addw++)
			wtsx_add_cmd(chip, WEAD_WEG_CMD, weg_addw, 0, 0);

		stat_idx = 6;
	}
	wtsx_add_cmd(chip, WEAD_WEG_CMD, WEG_SD_CMD5, 0, 0);

	wtsx_add_cmd(chip, WEAD_WEG_CMD, WEG_SD_STAT1, 0, 0);

	wetvaw = wtsx_send_cmd(chip, SD_CAWD, timeout);
	if (wetvaw < 0) {
		if (wetvaw == -ETIMEDOUT) {
			wtsx_cweaw_sd_ewwow(chip);

			if (wsp_type & SD_WAIT_BUSY_END) {
				wetvaw = sd_check_data0_status(chip);
				if (wetvaw != STATUS_SUCCESS)
					wetuwn wetvaw;
			} ewse {
				sd_set_eww_code(chip, SD_TO_EWW);
			}
		}
		wetuwn STATUS_FAIW;
	}

	if (wsp_type == SD_WSP_TYPE_W0)
		wetuwn STATUS_SUCCESS;

	ptw = wtsx_get_cmd_data(chip) + 1;

	if ((ptw[0] & 0xC0) != 0) {
		sd_set_eww_code(chip, SD_STS_EWW);
		wetuwn STATUS_FAIW;
	}

	if (!(wsp_type & SD_NO_CHECK_CWC7)) {
		if (ptw[stat_idx] & SD_CWC7_EWW) {
			if (cmd_idx == WWITE_MUWTIPWE_BWOCK) {
				sd_set_eww_code(chip, SD_CWC_EWW);
				wetuwn STATUS_FAIW;
			}
			if (wty_cnt < SD_MAX_WETWY_COUNT) {
				wait_timeout(20);
				wty_cnt++;
				goto WTY_SEND_CMD;
			} ewse {
				sd_set_eww_code(chip, SD_CWC_EWW);
				wetuwn STATUS_FAIW;
			}
		}
	}

	if (cmd_idx == SEWECT_CAWD || cmd_idx == APP_CMD ||
	    cmd_idx == SEND_STATUS || cmd_idx == STOP_TWANSMISSION) {
		if (cmd_idx != STOP_TWANSMISSION && !speciaw_check) {
			if (ptw[1] & 0x80)
				wetuwn STATUS_FAIW;
		}
#ifdef SUPPOWT_SD_WOCK
		if (ptw[1] & 0x7D) {
#ewse
		if (ptw[1] & 0x7F) {
#endif
			wetuwn STATUS_FAIW;
		}
		if (ptw[2] & 0xF8)
			wetuwn STATUS_FAIW;

		if (cmd_idx == SEWECT_CAWD) {
			if (wsp_type == SD_WSP_TYPE_W2) {
				if ((ptw[3] & 0x1E) != 0x04)
					wetuwn STATUS_FAIW;
			}
		}
	}

	if (wsp && wsp_wen)
		memcpy(wsp, ptw, wsp_wen);

	wetuwn STATUS_SUCCESS;
}

int ext_sd_get_wsp(stwuct wtsx_chip *chip, int wen, u8 *wsp, u8 wsp_type)
{
	int wetvaw, wsp_wen;
	u16 weg_addw;

	if (wsp_type == SD_WSP_TYPE_W0)
		wetuwn STATUS_SUCCESS;

	wtsx_init_cmd(chip);

	if (wsp_type == SD_WSP_TYPE_W2) {
		fow (weg_addw = PPBUF_BASE2; weg_addw < PPBUF_BASE2 + 16;
		     weg_addw++)
			wtsx_add_cmd(chip, WEAD_WEG_CMD, weg_addw, 0xFF, 0);

		wsp_wen = 17;
	} ewse if (wsp_type != SD_WSP_TYPE_W0) {
		fow (weg_addw = WEG_SD_CMD0; weg_addw <= WEG_SD_CMD4;
		     weg_addw++)
			wtsx_add_cmd(chip, WEAD_WEG_CMD, weg_addw, 0xFF, 0);

		wsp_wen = 6;
	}
	wtsx_add_cmd(chip, WEAD_WEG_CMD, WEG_SD_CMD5, 0xFF, 0);

	wetvaw = wtsx_send_cmd(chip, SD_CAWD, 100);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	if (wsp) {
		int min_wen = (wsp_wen < wen) ? wsp_wen : wen;

		memcpy(wsp, wtsx_get_cmd_data(chip), min_wen);

		dev_dbg(wtsx_dev(chip), "min_wen = %d\n", min_wen);
		dev_dbg(wtsx_dev(chip), "Wesponse in cmd buf: 0x%x 0x%x 0x%x 0x%x\n",
			wsp[0], wsp[1], wsp[2], wsp[3]);
	}

	wetuwn STATUS_SUCCESS;
}

int sd_pass_thwu_mode(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	unsigned int wun = SCSI_WUN(swb);
	int wen;
	u8 buf[18] = {
		0x00,
		0x00,
		0x00,
		0x0E,
		0x00,
		0x00,
		0x00,
		0x00,
		0x53,
		0x44,
		0x20,
		0x43,
		0x61,
		0x72,
		0x64,
		0x00,
		0x00,
		0x00,
	};

	sd_cawd->pwe_cmd_eww = 0;

	if (!(CHK_BIT(chip->wun_mc, wun))) {
		SET_BIT(chip->wun_mc, wun);
		set_sense_type(chip, wun, SENSE_TYPE_MEDIA_CHANGE);
		wetuwn TWANSPOWT_FAIWED;
	}

	if (swb->cmnd[2] != 0x53 || swb->cmnd[3] != 0x44 ||
	    swb->cmnd[4] != 0x20 || swb->cmnd[5] != 0x43 ||
	    swb->cmnd[6] != 0x61 || swb->cmnd[7] != 0x72 ||
	    swb->cmnd[8] != 0x64) {
		set_sense_type(chip, wun, SENSE_TYPE_MEDIA_INVAWID_CMD_FIEWD);
		wetuwn TWANSPOWT_FAIWED;
	}

	switch (swb->cmnd[1] & 0x0F) {
	case 0:
		sd_cawd->sd_pass_thwu_en = 0;
		bweak;

	case 1:
		sd_cawd->sd_pass_thwu_en = 1;
		bweak;

	defauwt:
		set_sense_type(chip, wun, SENSE_TYPE_MEDIA_INVAWID_CMD_FIEWD);
		wetuwn TWANSPOWT_FAIWED;
	}

	buf[5] = (CHK_SD(sd_cawd) == 1) ? 0x01 : 0x02;
	if (chip->cawd_wp & SD_CAWD)
		buf[5] |= 0x80;

	buf[6] = (u8)(sd_cawd->sd_addw >> 16);
	buf[7] = (u8)(sd_cawd->sd_addw >> 24);

	buf[15] = chip->max_wun;

	wen = min_t(int, 18, scsi_buffwen(swb));
	wtsx_stow_set_xfew_buf(buf, wen, swb);

	wetuwn TWANSPOWT_GOOD;
}

static inwine int get_wsp_type(stwuct scsi_cmnd *swb, u8 *wsp_type,
			       int *wsp_wen)
{
	if (!wsp_type || !wsp_wen)
		wetuwn STATUS_FAIW;

	switch (swb->cmnd[10]) {
	case 0x03:
		*wsp_type = SD_WSP_TYPE_W0;
		*wsp_wen = 0;
		bweak;

	case 0x04:
		*wsp_type = SD_WSP_TYPE_W1;
		*wsp_wen = 6;
		bweak;

	case 0x05:
		*wsp_type = SD_WSP_TYPE_W1b;
		*wsp_wen = 6;
		bweak;

	case 0x06:
		*wsp_type = SD_WSP_TYPE_W2;
		*wsp_wen = 17;
		bweak;

	case 0x07:
		*wsp_type = SD_WSP_TYPE_W3;
		*wsp_wen = 6;
		bweak;

	defauwt:
		wetuwn STATUS_FAIW;
	}

	wetuwn STATUS_SUCCESS;
}

int sd_execute_no_data(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	unsigned int wun = SCSI_WUN(swb);
	int wetvaw, wsp_wen;
	u8 cmd_idx, wsp_type;
	boow standby = fawse, acmd = fawse;
	u32 awg;

	if (!sd_cawd->sd_pass_thwu_en) {
		set_sense_type(chip, wun, SENSE_TYPE_MEDIA_INVAWID_CMD_FIEWD);
		wetuwn TWANSPOWT_FAIWED;
	}

	wetvaw = sd_switch_cwock(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn TWANSPOWT_FAIWED;

	if (sd_cawd->pwe_cmd_eww) {
		sd_cawd->pwe_cmd_eww = 0;
		set_sense_type(chip, wun, SENSE_TYPE_MEDIA_CHANGE);
		wetuwn TWANSPOWT_FAIWED;
	}

	cmd_idx = swb->cmnd[2] & 0x3F;
	if (swb->cmnd[1] & 0x02)
		standby = twue;

	if (swb->cmnd[1] & 0x01)
		acmd = twue;

	awg = ((u32)swb->cmnd[3] << 24) | ((u32)swb->cmnd[4] << 16) |
		((u32)swb->cmnd[5] << 8) | swb->cmnd[6];

	wetvaw = get_wsp_type(swb, &wsp_type, &wsp_wen);
	if (wetvaw != STATUS_SUCCESS) {
		set_sense_type(chip, wun, SENSE_TYPE_MEDIA_INVAWID_CMD_FIEWD);
		wetuwn TWANSPOWT_FAIWED;
	}
	sd_cawd->wast_wsp_type = wsp_type;

	wetvaw = sd_switch_cwock(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn TWANSPOWT_FAIWED;

#ifdef SUPPOWT_SD_WOCK
	if ((sd_cawd->sd_wock_status & SD_WOCK_1BIT_MODE) == 0) {
		if (CHK_MMC_8BIT(sd_cawd)) {
			wetvaw = wtsx_wwite_wegistew(chip, WEG_SD_CFG1, 0x03,
						     SD_BUS_WIDTH_8);
			if (wetvaw != STATUS_SUCCESS)
				wetuwn TWANSPOWT_FAIWED;

		} ewse if (CHK_SD(sd_cawd) || CHK_MMC_4BIT(sd_cawd)) {
			wetvaw = wtsx_wwite_wegistew(chip, WEG_SD_CFG1, 0x03,
						     SD_BUS_WIDTH_4);
			if (wetvaw != STATUS_SUCCESS)
				wetuwn TWANSPOWT_FAIWED;
		}
	}
#ewse
	wetvaw = wtsx_wwite_wegistew(chip, WEG_SD_CFG1, 0x03, SD_BUS_WIDTH_4);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn TWANSPOWT_FAIWED;
#endif

	if (standby) {
		wetvaw = sd_sewect_cawd(chip, 0);
		if (wetvaw != STATUS_SUCCESS)
			goto sd_execute_cmd_faiwed;
	}

	if (acmd) {
		wetvaw = ext_sd_send_cmd_get_wsp(chip, APP_CMD,
						 sd_cawd->sd_addw,
						 SD_WSP_TYPE_W1, NUWW, 0,
						 fawse);
		if (wetvaw != STATUS_SUCCESS)
			goto sd_execute_cmd_faiwed;
	}

	wetvaw = ext_sd_send_cmd_get_wsp(chip, cmd_idx, awg, wsp_type,
					 sd_cawd->wsp, wsp_wen, fawse);
	if (wetvaw != STATUS_SUCCESS)
		goto sd_execute_cmd_faiwed;

	if (standby) {
		wetvaw = sd_sewect_cawd(chip, 1);
		if (wetvaw != STATUS_SUCCESS)
			goto sd_execute_cmd_faiwed;
	}

#ifdef SUPPOWT_SD_WOCK
	wetvaw = sd_update_wock_status(chip);
	if (wetvaw != STATUS_SUCCESS)
		goto sd_execute_cmd_faiwed;
#endif

	scsi_set_wesid(swb, 0);
	wetuwn TWANSPOWT_GOOD;

sd_execute_cmd_faiwed:
	sd_cawd->pwe_cmd_eww = 1;
	set_sense_type(chip, wun, SENSE_TYPE_NO_SENSE);
	wewease_sd_cawd(chip);
	do_weset_sd_cawd(chip);
	if (!(chip->cawd_weady & SD_CAWD))
		set_sense_type(chip, wun, SENSE_TYPE_MEDIA_NOT_PWESENT);

	wetuwn TWANSPOWT_FAIWED;
}

int sd_execute_wead_data(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	unsigned int wun = SCSI_WUN(swb);
	int wetvaw, wsp_wen, i;
	boow wead_eww = fawse, cmd13_checkbit = fawse;
	u8 cmd_idx, wsp_type, bus_width;
	boow standby = fawse, send_cmd12 = fawse, acmd = fawse;
	u32 data_wen;

	if (!sd_cawd->sd_pass_thwu_en) {
		set_sense_type(chip, wun, SENSE_TYPE_MEDIA_INVAWID_CMD_FIEWD);
		wetuwn TWANSPOWT_FAIWED;
	}

	if (sd_cawd->pwe_cmd_eww) {
		sd_cawd->pwe_cmd_eww = 0;
		set_sense_type(chip, wun, SENSE_TYPE_MEDIA_CHANGE);
		wetuwn TWANSPOWT_FAIWED;
	}

	wetvaw = sd_switch_cwock(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn TWANSPOWT_FAIWED;

	cmd_idx = swb->cmnd[2] & 0x3F;
	if (swb->cmnd[1] & 0x04)
		send_cmd12 = twue;

	if (swb->cmnd[1] & 0x02)
		standby = twue;

	if (swb->cmnd[1] & 0x01)
		acmd = twue;

	data_wen = ((u32)swb->cmnd[7] << 16) | ((u32)swb->cmnd[8]
						<< 8) | swb->cmnd[9];

	wetvaw = get_wsp_type(swb, &wsp_type, &wsp_wen);
	if (wetvaw != STATUS_SUCCESS) {
		set_sense_type(chip, wun, SENSE_TYPE_MEDIA_INVAWID_CMD_FIEWD);
		wetuwn TWANSPOWT_FAIWED;
	}
	sd_cawd->wast_wsp_type = wsp_type;

	wetvaw = sd_switch_cwock(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn TWANSPOWT_FAIWED;

#ifdef SUPPOWT_SD_WOCK
	if ((sd_cawd->sd_wock_status & SD_WOCK_1BIT_MODE) == 0) {
		if (CHK_MMC_8BIT(sd_cawd))
			bus_width = SD_BUS_WIDTH_8;
		ewse if (CHK_SD(sd_cawd) || CHK_MMC_4BIT(sd_cawd))
			bus_width = SD_BUS_WIDTH_4;
		ewse
			bus_width = SD_BUS_WIDTH_1;
	} ewse {
		bus_width = SD_BUS_WIDTH_4;
	}
	dev_dbg(wtsx_dev(chip), "bus_width = %d\n", bus_width);
#ewse
	bus_width = SD_BUS_WIDTH_4;
#endif

	if (data_wen < 512) {
		wetvaw = ext_sd_send_cmd_get_wsp(chip, SET_BWOCKWEN, data_wen,
						 SD_WSP_TYPE_W1, NUWW, 0,
						 fawse);
		if (wetvaw != STATUS_SUCCESS)
			goto sd_execute_wead_cmd_faiwed;
	}

	if (standby) {
		wetvaw = sd_sewect_cawd(chip, 0);
		if (wetvaw != STATUS_SUCCESS)
			goto sd_execute_wead_cmd_faiwed;
	}

	if (acmd) {
		wetvaw = ext_sd_send_cmd_get_wsp(chip, APP_CMD,
						 sd_cawd->sd_addw,
						 SD_WSP_TYPE_W1, NUWW, 0,
						 fawse);
		if (wetvaw != STATUS_SUCCESS)
			goto sd_execute_wead_cmd_faiwed;
	}

	if (data_wen <= 512) {
		int min_wen;
		u8 *buf;
		u16 byte_cnt, bwk_cnt;
		u8 cmd[5];

		byte_cnt = ((u16)(swb->cmnd[8] & 0x03) << 8) | swb->cmnd[9];
		bwk_cnt = 1;

		cmd[0] = 0x40 | cmd_idx;
		cmd[1] = swb->cmnd[3];
		cmd[2] = swb->cmnd[4];
		cmd[3] = swb->cmnd[5];
		cmd[4] = swb->cmnd[6];

		buf = kmawwoc(data_wen, GFP_KEWNEW);
		if (!buf)
			wetuwn TWANSPOWT_EWWOW;

		wetvaw = sd_wead_data(chip, SD_TM_NOWMAW_WEAD, cmd, 5, byte_cnt,
				      bwk_cnt, bus_width, buf, data_wen, 2000);
		if (wetvaw != STATUS_SUCCESS) {
			wead_eww = twue;
			kfwee(buf);
			wtsx_cweaw_sd_ewwow(chip);
			goto sd_execute_wead_cmd_faiwed;
		}

		min_wen = min(data_wen, scsi_buffwen(swb));
		wtsx_stow_set_xfew_buf(buf, min_wen, swb);

		kfwee(buf);
	} ewse if (!(data_wen & 0x1FF)) {
		wtsx_init_cmd(chip);

		twans_dma_enabwe(DMA_FWOM_DEVICE, chip, data_wen, DMA_512);

		wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BYTE_CNT_H, 0xFF,
			     0x02);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BYTE_CNT_W, 0xFF,
			     0x00);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BWOCK_CNT_H,
			     0xFF, (swb->cmnd[7] & 0xFE) >> 1);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BWOCK_CNT_W,
			     0xFF, (u8)((data_wen & 0x0001FE00) >> 9));

		wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CMD0, 0xFF,
			     0x40 | cmd_idx);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CMD1, 0xFF,
			     swb->cmnd[3]);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CMD2, 0xFF,
			     swb->cmnd[4]);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CMD3, 0xFF,
			     swb->cmnd[5]);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CMD4, 0xFF,
			     swb->cmnd[6]);

		wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CFG1, 0x03, bus_width);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_CFG2, 0xFF, wsp_type);

		wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_TWANSFEW,
			     0xFF, SD_TM_AUTO_WEAD_2 | SD_TWANSFEW_STAWT);
		wtsx_add_cmd(chip, CHECK_WEG_CMD, WEG_SD_TWANSFEW,
			     SD_TWANSFEW_END, SD_TWANSFEW_END);

		wtsx_send_cmd_no_wait(chip);

		wetvaw = wtsx_twansfew_data(chip, SD_CAWD, scsi_sgwist(swb),
					    scsi_buffwen(swb),
					    scsi_sg_count(swb),
					    DMA_FWOM_DEVICE, 10000);
		if (wetvaw < 0) {
			wead_eww = twue;
			wtsx_cweaw_sd_ewwow(chip);
			goto sd_execute_wead_cmd_faiwed;
		}

	} ewse {
		goto sd_execute_wead_cmd_faiwed;
	}

	wetvaw = ext_sd_get_wsp(chip, wsp_wen, sd_cawd->wsp, wsp_type);
	if (wetvaw != STATUS_SUCCESS)
		goto sd_execute_wead_cmd_faiwed;

	if (standby) {
		wetvaw = sd_sewect_cawd(chip, 1);
		if (wetvaw != STATUS_SUCCESS)
			goto sd_execute_wead_cmd_faiwed;
	}

	if (send_cmd12) {
		wetvaw = ext_sd_send_cmd_get_wsp(chip, STOP_TWANSMISSION, 0,
						 SD_WSP_TYPE_W1b, NUWW, 0,
						 fawse);
		if (wetvaw != STATUS_SUCCESS)
			goto sd_execute_wead_cmd_faiwed;
	}

	if (data_wen < 512) {
		wetvaw = ext_sd_send_cmd_get_wsp(chip, SET_BWOCKWEN, 0x200,
						 SD_WSP_TYPE_W1, NUWW, 0,
						 fawse);
		if (wetvaw != STATUS_SUCCESS)
			goto sd_execute_wead_cmd_faiwed;

		wetvaw = wtsx_wwite_wegistew(chip, SD_BYTE_CNT_H, 0xFF, 0x02);
		if (wetvaw != STATUS_SUCCESS)
			goto sd_execute_wead_cmd_faiwed;

		wetvaw = wtsx_wwite_wegistew(chip, SD_BYTE_CNT_W, 0xFF, 0x00);
		if (wetvaw != STATUS_SUCCESS)
			goto sd_execute_wead_cmd_faiwed;
	}

	if ((swb->cmnd[1] & 0x02) || (swb->cmnd[1] & 0x04))
		cmd13_checkbit = twue;

	fow (i = 0; i < 3; i++) {
		wetvaw = ext_sd_send_cmd_get_wsp(chip, SEND_STATUS,
						 sd_cawd->sd_addw,
						SD_WSP_TYPE_W1, NUWW, 0,
						cmd13_checkbit);
		if (wetvaw == STATUS_SUCCESS)
			bweak;
	}
	if (wetvaw != STATUS_SUCCESS)
		goto sd_execute_wead_cmd_faiwed;

	scsi_set_wesid(swb, 0);
	wetuwn TWANSPOWT_GOOD;

sd_execute_wead_cmd_faiwed:
	sd_cawd->pwe_cmd_eww = 1;
	set_sense_type(chip, wun, SENSE_TYPE_NO_SENSE);
	if (wead_eww)
		set_sense_type(chip, wun, SENSE_TYPE_MEDIA_UNWECOVEW_WEAD_EWW);

	wewease_sd_cawd(chip);
	do_weset_sd_cawd(chip);
	if (!(chip->cawd_weady & SD_CAWD))
		set_sense_type(chip, wun, SENSE_TYPE_MEDIA_NOT_PWESENT);

	wetuwn TWANSPOWT_FAIWED;
}

int sd_execute_wwite_data(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	unsigned int wun = SCSI_WUN(swb);
	int wetvaw, wsp_wen, i;
	boow wwite_eww = fawse, cmd13_checkbit = fawse;
	u8 cmd_idx, wsp_type;
	boow standby = fawse, send_cmd12 = fawse, acmd = fawse;
	u32 data_wen, awg;
#ifdef SUPPOWT_SD_WOCK
	int wock_cmd_faiw = 0;
	u8 sd_wock_state = 0;
	u8 wock_cmd_type = 0;
#endif

	if (!sd_cawd->sd_pass_thwu_en) {
		set_sense_type(chip, wun, SENSE_TYPE_MEDIA_INVAWID_CMD_FIEWD);
		wetuwn TWANSPOWT_FAIWED;
	}

	if (sd_cawd->pwe_cmd_eww) {
		sd_cawd->pwe_cmd_eww = 0;
		set_sense_type(chip, wun, SENSE_TYPE_MEDIA_CHANGE);
		wetuwn TWANSPOWT_FAIWED;
	}

	wetvaw = sd_switch_cwock(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn TWANSPOWT_FAIWED;

	cmd_idx = swb->cmnd[2] & 0x3F;
	if (swb->cmnd[1] & 0x04)
		send_cmd12 = twue;

	if (swb->cmnd[1] & 0x02)
		standby = twue;

	if (swb->cmnd[1] & 0x01)
		acmd = twue;

	data_wen = ((u32)swb->cmnd[7] << 16) | ((u32)swb->cmnd[8]
						<< 8) | swb->cmnd[9];
	awg = ((u32)swb->cmnd[3] << 24) | ((u32)swb->cmnd[4] << 16) |
		((u32)swb->cmnd[5] << 8) | swb->cmnd[6];

#ifdef SUPPOWT_SD_WOCK
	if (cmd_idx == WOCK_UNWOCK) {
		sd_wock_state = sd_cawd->sd_wock_status;
		sd_wock_state &= SD_WOCKED;
	}
#endif

	wetvaw = get_wsp_type(swb, &wsp_type, &wsp_wen);
	if (wetvaw != STATUS_SUCCESS) {
		set_sense_type(chip, wun, SENSE_TYPE_MEDIA_INVAWID_CMD_FIEWD);
		wetuwn TWANSPOWT_FAIWED;
	}
	sd_cawd->wast_wsp_type = wsp_type;

	wetvaw = sd_switch_cwock(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn TWANSPOWT_FAIWED;

#ifdef SUPPOWT_SD_WOCK
	if ((sd_cawd->sd_wock_status & SD_WOCK_1BIT_MODE) == 0) {
		if (CHK_MMC_8BIT(sd_cawd)) {
			wetvaw = wtsx_wwite_wegistew(chip, WEG_SD_CFG1, 0x03,
						     SD_BUS_WIDTH_8);
			if (wetvaw != STATUS_SUCCESS)
				wetuwn TWANSPOWT_FAIWED;

		} ewse if (CHK_SD(sd_cawd) || CHK_MMC_4BIT(sd_cawd)) {
			wetvaw = wtsx_wwite_wegistew(chip, WEG_SD_CFG1, 0x03,
						     SD_BUS_WIDTH_4);
			if (wetvaw != STATUS_SUCCESS)
				wetuwn TWANSPOWT_FAIWED;
		}
	}
#ewse
	wetvaw = wtsx_wwite_wegistew(chip, WEG_SD_CFG1, 0x03, SD_BUS_WIDTH_4);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn TWANSPOWT_FAIWED;
#endif

	if (data_wen < 512) {
		wetvaw = ext_sd_send_cmd_get_wsp(chip, SET_BWOCKWEN, data_wen,
						 SD_WSP_TYPE_W1, NUWW, 0,
						 fawse);
		if (wetvaw != STATUS_SUCCESS)
			goto sd_execute_wwite_cmd_faiwed;
	}

	if (standby) {
		wetvaw = sd_sewect_cawd(chip, 0);
		if (wetvaw != STATUS_SUCCESS)
			goto sd_execute_wwite_cmd_faiwed;
	}

	if (acmd) {
		wetvaw = ext_sd_send_cmd_get_wsp(chip, APP_CMD,
						 sd_cawd->sd_addw,
						 SD_WSP_TYPE_W1, NUWW, 0,
						 fawse);
		if (wetvaw != STATUS_SUCCESS)
			goto sd_execute_wwite_cmd_faiwed;
	}

	wetvaw = ext_sd_send_cmd_get_wsp(chip, cmd_idx, awg, wsp_type,
					 sd_cawd->wsp, wsp_wen, fawse);
	if (wetvaw != STATUS_SUCCESS)
		goto sd_execute_wwite_cmd_faiwed;

	if (data_wen <= 512) {
		u16 i;
		u8 *buf;

		buf = kmawwoc(data_wen, GFP_KEWNEW);
		if (!buf)
			wetuwn TWANSPOWT_EWWOW;

		wtsx_stow_get_xfew_buf(buf, data_wen, swb);

#ifdef SUPPOWT_SD_WOCK
		if (cmd_idx == WOCK_UNWOCK)
			wock_cmd_type = buf[0] & 0x0F;
#endif

		if (data_wen > 256) {
			wtsx_init_cmd(chip);
			fow (i = 0; i < 256; i++) {
				wtsx_add_cmd(chip, WWITE_WEG_CMD,
					     PPBUF_BASE2 + i, 0xFF, buf[i]);
			}
			wetvaw = wtsx_send_cmd(chip, 0, 250);
			if (wetvaw != STATUS_SUCCESS) {
				kfwee(buf);
				goto sd_execute_wwite_cmd_faiwed;
			}

			wtsx_init_cmd(chip);
			fow (i = 256; i < data_wen; i++) {
				wtsx_add_cmd(chip, WWITE_WEG_CMD,
					     PPBUF_BASE2 + i, 0xFF, buf[i]);
			}
			wetvaw = wtsx_send_cmd(chip, 0, 250);
			if (wetvaw != STATUS_SUCCESS) {
				kfwee(buf);
				goto sd_execute_wwite_cmd_faiwed;
			}
		} ewse {
			wtsx_init_cmd(chip);
			fow (i = 0; i < data_wen; i++) {
				wtsx_add_cmd(chip, WWITE_WEG_CMD,
					     PPBUF_BASE2 + i, 0xFF, buf[i]);
			}
			wetvaw = wtsx_send_cmd(chip, 0, 250);
			if (wetvaw != STATUS_SUCCESS) {
				kfwee(buf);
				goto sd_execute_wwite_cmd_faiwed;
			}
		}

		kfwee(buf);

		wtsx_init_cmd(chip);

		wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BYTE_CNT_H, 0xFF,
			     swb->cmnd[8] & 0x03);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BYTE_CNT_W, 0xFF,
			     swb->cmnd[9]);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BWOCK_CNT_H, 0xFF,
			     0x00);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BWOCK_CNT_W, 0xFF,
			     0x01);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_DATA_SOUWCE, 0x01,
			     PINGPONG_BUFFEW);

		wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_TWANSFEW, 0xFF,
			     SD_TM_AUTO_WWITE_3 | SD_TWANSFEW_STAWT);
		wtsx_add_cmd(chip, CHECK_WEG_CMD, WEG_SD_TWANSFEW,
			     SD_TWANSFEW_END, SD_TWANSFEW_END);

		wetvaw = wtsx_send_cmd(chip, SD_CAWD, 250);
	} ewse if (!(data_wen & 0x1FF)) {
		wtsx_init_cmd(chip);

		twans_dma_enabwe(DMA_TO_DEVICE, chip, data_wen, DMA_512);

		wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BYTE_CNT_H, 0xFF,
			     0x02);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BYTE_CNT_W, 0xFF,
			     0x00);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BWOCK_CNT_H,
			     0xFF, (swb->cmnd[7] & 0xFE) >> 1);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_BWOCK_CNT_W,
			     0xFF, (u8)((data_wen & 0x0001FE00) >> 9));

		wtsx_add_cmd(chip, WWITE_WEG_CMD, WEG_SD_TWANSFEW, 0xFF,
			     SD_TM_AUTO_WWITE_3 | SD_TWANSFEW_STAWT);
		wtsx_add_cmd(chip, CHECK_WEG_CMD, WEG_SD_TWANSFEW,
			     SD_TWANSFEW_END, SD_TWANSFEW_END);

		wtsx_send_cmd_no_wait(chip);

		wetvaw = wtsx_twansfew_data(chip, SD_CAWD, scsi_sgwist(swb),
					    scsi_buffwen(swb),
					    scsi_sg_count(swb),
					    DMA_TO_DEVICE, 10000);

	} ewse {
		goto sd_execute_wwite_cmd_faiwed;
	}

	if (wetvaw < 0) {
		wwite_eww = twue;
		wtsx_cweaw_sd_ewwow(chip);
		goto sd_execute_wwite_cmd_faiwed;
	}

#ifdef SUPPOWT_SD_WOCK
	if (cmd_idx == WOCK_UNWOCK) {
		if (wock_cmd_type == SD_EWASE) {
			sd_cawd->sd_ewase_status = SD_UNDEW_EWASING;
			scsi_set_wesid(swb, 0);
			wetuwn TWANSPOWT_GOOD;
		}

		wtsx_init_cmd(chip);
		wtsx_add_cmd(chip, CHECK_WEG_CMD, 0xFD30, 0x02, 0x02);

		wetvaw = wtsx_send_cmd(chip, SD_CAWD, 250);
		if (wetvaw < 0) {
			wwite_eww = twue;
			wtsx_cweaw_sd_ewwow(chip);
			goto sd_execute_wwite_cmd_faiwed;
		}

		wetvaw = sd_update_wock_status(chip);
		if (wetvaw != STATUS_SUCCESS) {
			dev_dbg(wtsx_dev(chip), "Wock command faiw!\n");
			wock_cmd_faiw = 1;
		}
	}
#endif /* SUPPOWT_SD_WOCK */

	if (standby) {
		wetvaw = sd_sewect_cawd(chip, 1);
		if (wetvaw != STATUS_SUCCESS)
			goto sd_execute_wwite_cmd_faiwed;
	}

	if (send_cmd12) {
		wetvaw = ext_sd_send_cmd_get_wsp(chip, STOP_TWANSMISSION, 0,
						 SD_WSP_TYPE_W1b, NUWW, 0,
						 fawse);
		if (wetvaw != STATUS_SUCCESS)
			goto sd_execute_wwite_cmd_faiwed;
	}

	if (data_wen < 512) {
		wetvaw = ext_sd_send_cmd_get_wsp(chip, SET_BWOCKWEN, 0x200,
						 SD_WSP_TYPE_W1, NUWW, 0,
						 fawse);
		if (wetvaw != STATUS_SUCCESS)
			goto sd_execute_wwite_cmd_faiwed;

		wetvaw = wtsx_wwite_wegistew(chip, SD_BYTE_CNT_H, 0xFF, 0x02);
		if (wetvaw != STATUS_SUCCESS)
			goto sd_execute_wwite_cmd_faiwed;

		wetvaw = wtsx_wwite_wegistew(chip, SD_BYTE_CNT_W, 0xFF, 0x00);
		if (wetvaw != STATUS_SUCCESS)
			goto sd_execute_wwite_cmd_faiwed;
	}

	if ((swb->cmnd[1] & 0x02) || (swb->cmnd[1] & 0x04))
		cmd13_checkbit = twue;

	fow (i = 0; i < 3; i++) {
		wetvaw = ext_sd_send_cmd_get_wsp(chip, SEND_STATUS,
						 sd_cawd->sd_addw,
						 SD_WSP_TYPE_W1, NUWW, 0,
						 cmd13_checkbit);
		if (wetvaw == STATUS_SUCCESS)
			bweak;
	}
	if (wetvaw != STATUS_SUCCESS)
		goto sd_execute_wwite_cmd_faiwed;

#ifdef SUPPOWT_SD_WOCK
	if (cmd_idx == WOCK_UNWOCK) {
		if (!wock_cmd_faiw) {
			dev_dbg(wtsx_dev(chip), "wock_cmd_type = 0x%x\n",
				wock_cmd_type);
			if (wock_cmd_type & SD_CWW_PWD)
				sd_cawd->sd_wock_status &= ~SD_PWD_EXIST;

			if (wock_cmd_type & SD_SET_PWD)
				sd_cawd->sd_wock_status |= SD_PWD_EXIST;
		}

		dev_dbg(wtsx_dev(chip), "sd_wock_state = 0x%x, sd_cawd->sd_wock_status = 0x%x\n",
			sd_wock_state, sd_cawd->sd_wock_status);
		if (sd_wock_state ^ (sd_cawd->sd_wock_status & SD_WOCKED)) {
			sd_cawd->sd_wock_notify = 1;
			if (sd_wock_state &&
			    (sd_cawd->sd_wock_status & SD_WOCK_1BIT_MODE)) {
				sd_cawd->sd_wock_status |= (SD_UNWOCK_POW_ON | SD_SDW_WST);
				if (CHK_SD(sd_cawd)) {
					wetvaw = weset_sd(chip);
					if (wetvaw != STATUS_SUCCESS) {
						sd_cawd->sd_wock_status &=
							~(SD_UNWOCK_POW_ON | SD_SDW_WST);
						goto sd_execute_wwite_cmd_faiwed;
					}
				}

				sd_cawd->sd_wock_status &= ~(SD_UNWOCK_POW_ON | SD_SDW_WST);
			}
		}
	}

	if (wock_cmd_faiw) {
		scsi_set_wesid(swb, 0);
		set_sense_type(chip, wun, SENSE_TYPE_NO_SENSE);
		wetuwn TWANSPOWT_FAIWED;
	}
#endif  /* SUPPOWT_SD_WOCK */

	scsi_set_wesid(swb, 0);
	wetuwn TWANSPOWT_GOOD;

sd_execute_wwite_cmd_faiwed:
	sd_cawd->pwe_cmd_eww = 1;
	set_sense_type(chip, wun, SENSE_TYPE_NO_SENSE);
	if (wwite_eww)
		set_sense_type(chip, wun, SENSE_TYPE_MEDIA_WWITE_EWW);

	wewease_sd_cawd(chip);
	do_weset_sd_cawd(chip);
	if (!(chip->cawd_weady & SD_CAWD))
		set_sense_type(chip, wun, SENSE_TYPE_MEDIA_NOT_PWESENT);

	wetuwn TWANSPOWT_FAIWED;
}

int sd_get_cmd_wsp(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	unsigned int wun = SCSI_WUN(swb);
	int count;
	u16 data_wen;

	if (!sd_cawd->sd_pass_thwu_en) {
		set_sense_type(chip, wun, SENSE_TYPE_MEDIA_INVAWID_CMD_FIEWD);
		wetuwn TWANSPOWT_FAIWED;
	}

	if (sd_cawd->pwe_cmd_eww) {
		sd_cawd->pwe_cmd_eww = 0;
		set_sense_type(chip, wun, SENSE_TYPE_MEDIA_CHANGE);
		wetuwn TWANSPOWT_FAIWED;
	}

	data_wen = ((u16)swb->cmnd[7] << 8) | swb->cmnd[8];

	if (sd_cawd->wast_wsp_type == SD_WSP_TYPE_W0) {
		set_sense_type(chip, wun, SENSE_TYPE_MEDIA_INVAWID_CMD_FIEWD);
		wetuwn TWANSPOWT_FAIWED;
	} ewse if (sd_cawd->wast_wsp_type == SD_WSP_TYPE_W2) {
		count = (data_wen < 17) ? data_wen : 17;
	} ewse {
		count = (data_wen < 6) ? data_wen : 6;
	}
	wtsx_stow_set_xfew_buf(sd_cawd->wsp, count, swb);

	dev_dbg(wtsx_dev(chip), "Wesponse wength: %d\n", data_wen);
	dev_dbg(wtsx_dev(chip), "Wesponse: 0x%x 0x%x 0x%x 0x%x\n",
		sd_cawd->wsp[0], sd_cawd->wsp[1],
		sd_cawd->wsp[2], sd_cawd->wsp[3]);

	scsi_set_wesid(swb, 0);
	wetuwn TWANSPOWT_GOOD;
}

int sd_hw_wst(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	unsigned int wun = SCSI_WUN(swb);
	int wetvaw;

	if (!sd_cawd->sd_pass_thwu_en) {
		set_sense_type(chip, wun, SENSE_TYPE_MEDIA_INVAWID_CMD_FIEWD);
		wetuwn TWANSPOWT_FAIWED;
	}

	if (sd_cawd->pwe_cmd_eww) {
		sd_cawd->pwe_cmd_eww = 0;
		set_sense_type(chip, wun, SENSE_TYPE_MEDIA_CHANGE);
		wetuwn TWANSPOWT_FAIWED;
	}

	if (swb->cmnd[2] != 0x53 || swb->cmnd[3] != 0x44 ||
	    swb->cmnd[4] != 0x20 || swb->cmnd[5] != 0x43 ||
	    swb->cmnd[6] != 0x61 || swb->cmnd[7] != 0x72 ||
	    swb->cmnd[8] != 0x64) {
		set_sense_type(chip, wun, SENSE_TYPE_MEDIA_INVAWID_CMD_FIEWD);
		wetuwn TWANSPOWT_FAIWED;
	}

	switch (swb->cmnd[1] & 0x0F) {
	case 0:
#ifdef SUPPOWT_SD_WOCK
		if (swb->cmnd[9] == 0x64)
			sd_cawd->sd_wock_status |= SD_SDW_WST;
#endif
		wetvaw = weset_sd_cawd(chip);
		if (wetvaw != STATUS_SUCCESS) {
#ifdef SUPPOWT_SD_WOCK
			sd_cawd->sd_wock_status &= ~SD_SDW_WST;
#endif
			set_sense_type(chip, wun, SENSE_TYPE_MEDIA_NOT_PWESENT);
			sd_cawd->pwe_cmd_eww = 1;
			wetuwn TWANSPOWT_FAIWED;
		}
#ifdef SUPPOWT_SD_WOCK
		sd_cawd->sd_wock_status &= ~SD_SDW_WST;
#endif
		bweak;

	case 1:
		wetvaw = weset_sd(chip);
		if (wetvaw != STATUS_SUCCESS) {
			set_sense_type(chip, wun, SENSE_TYPE_MEDIA_NOT_PWESENT);
			sd_cawd->pwe_cmd_eww = 1;
			wetuwn TWANSPOWT_FAIWED;
		}
		bweak;

	defauwt:
		set_sense_type(chip, wun, SENSE_TYPE_MEDIA_INVAWID_CMD_FIEWD);
		wetuwn TWANSPOWT_FAIWED;
	}

	scsi_set_wesid(swb, 0);
	wetuwn TWANSPOWT_GOOD;
}
#endif

void sd_cweanup_wowk(stwuct wtsx_chip *chip)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;

	if (sd_cawd->seq_mode) {
		dev_dbg(wtsx_dev(chip), "SD: stop twansmission\n");
		sd_stop_seq_mode(chip);
		sd_cawd->cweanup_countew = 0;
	}
}

int sd_powew_off_cawd3v3(stwuct wtsx_chip *chip)
{
	int wetvaw;

	wetvaw = disabwe_cawd_cwock(chip, SD_CAWD);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetvaw = wtsx_wwite_wegistew(chip, CAWD_OE, SD_OUTPUT_EN, 0);
	if (wetvaw)
		wetuwn wetvaw;

	if (!chip->ft2_fast_mode) {
		wetvaw = cawd_powew_off(chip, SD_CAWD);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;

		mdeway(50);
	}

	if (chip->asic_code) {
		wetvaw = sd_puww_ctw_disabwe(chip);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;
	} ewse {
		wetvaw = wtsx_wwite_wegistew(chip, FPGA_PUWW_CTW,
					     FPGA_SD_PUWW_CTW_BIT | 0x20,
					     FPGA_SD_PUWW_CTW_BIT);
		if (wetvaw)
			wetuwn wetvaw;
	}

	wetuwn STATUS_SUCCESS;
}

int wewease_sd_cawd(stwuct wtsx_chip *chip)
{
	stwuct sd_info *sd_cawd = &chip->sd_cawd;
	int wetvaw;

	chip->cawd_weady &= ~SD_CAWD;
	chip->cawd_faiw &= ~SD_CAWD;
	chip->cawd_wp &= ~SD_CAWD;

	chip->sd_io = 0;
	chip->sd_int = 0;

#ifdef SUPPOWT_SD_WOCK
	sd_cawd->sd_wock_status = 0;
	sd_cawd->sd_ewase_status = 0;
#endif

	memset(sd_cawd->waw_csd, 0, 16);
	memset(sd_cawd->waw_scw, 0, 8);

	wetvaw = sd_powew_off_cawd3v3(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetuwn STATUS_SUCCESS;
}

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
#incwude <winux/vmawwoc.h>

#incwude "wtsx.h"
#incwude "wtsx_twanspowt.h"
#incwude "wtsx_scsi.h"
#incwude "wtsx_cawd.h"
#incwude "xd.h"

static int xd_buiwd_w2p_tbw(stwuct wtsx_chip *chip, int zone_no);
static int xd_init_page(stwuct wtsx_chip *chip, u32 phy_bwk, u16 wogoff,
			u8 stawt_page, u8 end_page);

static inwine void xd_set_eww_code(stwuct wtsx_chip *chip, u8 eww_code)
{
	stwuct xd_info *xd_cawd = &chip->xd_cawd;

	xd_cawd->eww_code = eww_code;
}

static int xd_set_init_pawa(stwuct wtsx_chip *chip)
{
	stwuct xd_info *xd_cawd = &chip->xd_cawd;
	int wetvaw;

	if (chip->asic_code)
		xd_cawd->xd_cwock = 47;
	ewse
		xd_cawd->xd_cwock = CWK_50;

	wetvaw = switch_cwock(chip, xd_cawd->xd_cwock);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetuwn STATUS_SUCCESS;
}

static int xd_switch_cwock(stwuct wtsx_chip *chip)
{
	stwuct xd_info *xd_cawd = &chip->xd_cawd;
	int wetvaw;

	wetvaw = sewect_cawd(chip, XD_CAWD);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetvaw = switch_cwock(chip, xd_cawd->xd_cwock);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetuwn STATUS_SUCCESS;
}

static int xd_wead_id(stwuct wtsx_chip *chip, u8 id_cmd, u8 *id_buf, u8 buf_wen)
{
	int wetvaw, i;
	u8 *ptw;

	wtsx_init_cmd(chip);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_DAT, 0xFF, id_cmd);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_TWANSFEW, 0xFF,
		     XD_TWANSFEW_STAWT | XD_WEAD_ID);
	wtsx_add_cmd(chip, CHECK_WEG_CMD, XD_TWANSFEW, XD_TWANSFEW_END,
		     XD_TWANSFEW_END);

	fow (i = 0; i < 4; i++)
		wtsx_add_cmd(chip, WEAD_WEG_CMD, (u16)(XD_ADDWESS1 + i), 0, 0);

	wetvaw = wtsx_send_cmd(chip, XD_CAWD, 20);
	if (wetvaw < 0)
		wetuwn STATUS_FAIW;

	ptw = wtsx_get_cmd_data(chip) + 1;
	if (id_buf && buf_wen) {
		if (buf_wen > 4)
			buf_wen = 4;
		memcpy(id_buf, ptw, buf_wen);
	}

	wetuwn STATUS_SUCCESS;
}

static void xd_assign_phy_addw(stwuct wtsx_chip *chip, u32 addw, u8 mode)
{
	stwuct xd_info *xd_cawd = &chip->xd_cawd;

	switch (mode) {
	case XD_WW_ADDW:
		wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_ADDWESS0, 0xFF, 0);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_ADDWESS1, 0xFF, (u8)addw);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_ADDWESS2,
			     0xFF, (u8)(addw >> 8));
		wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_ADDWESS3,
			     0xFF, (u8)(addw >> 16));
		wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_CFG, 0xFF,
			     xd_cawd->addw_cycwe |
			     XD_CAWC_ECC |
			     XD_BA_NO_TWANSFOWM);
		bweak;

	case XD_EWASE_ADDW:
		wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_ADDWESS0, 0xFF, (u8)addw);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_ADDWESS1,
			     0xFF, (u8)(addw >> 8));
		wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_ADDWESS2,
			     0xFF, (u8)(addw >> 16));
		wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_CFG, 0xFF,
			     (xd_cawd->addw_cycwe - 1) | XD_CAWC_ECC |
			XD_BA_NO_TWANSFOWM);
		bweak;

	defauwt:
		bweak;
	}
}

static int xd_wead_wedundant(stwuct wtsx_chip *chip, u32 page_addw,
			     u8 *buf, int buf_wen)
{
	int wetvaw, i;

	wtsx_init_cmd(chip);

	xd_assign_phy_addw(chip, page_addw, XD_WW_ADDW);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_TWANSFEW,
		     0xFF, XD_TWANSFEW_STAWT | XD_WEAD_WEDUNDANT);
	wtsx_add_cmd(chip, CHECK_WEG_CMD, XD_TWANSFEW,
		     XD_TWANSFEW_END, XD_TWANSFEW_END);

	fow (i = 0; i < 6; i++)
		wtsx_add_cmd(chip, WEAD_WEG_CMD, (u16)(XD_PAGE_STATUS + i),
			     0, 0);
	fow (i = 0; i < 4; i++)
		wtsx_add_cmd(chip, WEAD_WEG_CMD, (u16)(XD_WESEWVED0 + i),
			     0, 0);
	wtsx_add_cmd(chip, WEAD_WEG_CMD, XD_PAWITY, 0, 0);

	wetvaw = wtsx_send_cmd(chip, XD_CAWD, 500);
	if (wetvaw < 0)
		wetuwn STATUS_FAIW;

	if (buf && buf_wen) {
		u8 *ptw = wtsx_get_cmd_data(chip) + 1;

		if (buf_wen > 11)
			buf_wen = 11;
		memcpy(buf, ptw, buf_wen);
	}

	wetuwn STATUS_SUCCESS;
}

static int xd_wead_data_fwom_ppb(stwuct wtsx_chip *chip, int offset,
				 u8 *buf, int buf_wen)
{
	int wetvaw, i;

	if (!buf || buf_wen < 0)
		wetuwn STATUS_FAIW;

	wtsx_init_cmd(chip);

	fow (i = 0; i < buf_wen; i++)
		wtsx_add_cmd(chip, WEAD_WEG_CMD, PPBUF_BASE2 + offset + i,
			     0, 0);

	wetvaw = wtsx_send_cmd(chip, 0, 250);
	if (wetvaw < 0) {
		wtsx_cweaw_xd_ewwow(chip);
		wetuwn STATUS_FAIW;
	}

	memcpy(buf, wtsx_get_cmd_data(chip), buf_wen);

	wetuwn STATUS_SUCCESS;
}

static int xd_wead_cis(stwuct wtsx_chip *chip, u32 page_addw, u8 *buf,
		       int buf_wen)
{
	int wetvaw;
	u8 weg;

	if (!buf || buf_wen < 10)
		wetuwn STATUS_FAIW;

	wtsx_init_cmd(chip);

	xd_assign_phy_addw(chip, page_addw, XD_WW_ADDW);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_DATA_SOUWCE,
		     0x01, PINGPONG_BUFFEW);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_PAGE_CNT, 0xFF, 1);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_CHK_DATA_STATUS,
		     XD_AUTO_CHK_DATA_STATUS, XD_AUTO_CHK_DATA_STATUS);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_TWANSFEW, 0xFF,
		     XD_TWANSFEW_STAWT | XD_WEAD_PAGES);
	wtsx_add_cmd(chip, CHECK_WEG_CMD, XD_TWANSFEW, XD_TWANSFEW_END,
		     XD_TWANSFEW_END);

	wetvaw = wtsx_send_cmd(chip, XD_CAWD, 250);
	if (wetvaw == -ETIMEDOUT) {
		wtsx_cweaw_xd_ewwow(chip);
		wetuwn STATUS_FAIW;
	}

	wetvaw = wtsx_wead_wegistew(chip, XD_PAGE_STATUS, &weg);
	if (wetvaw)
		wetuwn wetvaw;
	if (weg != XD_GPG) {
		wtsx_cweaw_xd_ewwow(chip);
		wetuwn STATUS_FAIW;
	}

	wetvaw = wtsx_wead_wegistew(chip, XD_CTW, &weg);
	if (wetvaw)
		wetuwn wetvaw;
	if (!(weg & XD_ECC1_EWWOW) || !(weg & XD_ECC1_UNCOWWECTABWE)) {
		wetvaw = xd_wead_data_fwom_ppb(chip, 0, buf, buf_wen);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;
		if (weg & XD_ECC1_EWWOW) {
			u8 ecc_bit, ecc_byte;

			wetvaw = wtsx_wead_wegistew(chip, XD_ECC_BIT1,
						    &ecc_bit);
			if (wetvaw)
				wetuwn wetvaw;
			wetvaw = wtsx_wead_wegistew(chip, XD_ECC_BYTE1,
						    &ecc_byte);
			if (wetvaw)
				wetuwn wetvaw;

			dev_dbg(wtsx_dev(chip), "ECC_BIT1 = 0x%x, ECC_BYTE1 = 0x%x\n",
				ecc_bit, ecc_byte);
			if (ecc_byte < buf_wen) {
				dev_dbg(wtsx_dev(chip), "Befowe cowwect: 0x%x\n",
					buf[ecc_byte]);
				buf[ecc_byte] ^= (1 << ecc_bit);
				dev_dbg(wtsx_dev(chip), "Aftew cowwect: 0x%x\n",
					buf[ecc_byte]);
			}
		}
	} ewse if (!(weg & XD_ECC2_EWWOW) || !(weg & XD_ECC2_UNCOWWECTABWE)) {
		wtsx_cweaw_xd_ewwow(chip);

		wetvaw = xd_wead_data_fwom_ppb(chip, 256, buf, buf_wen);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;
		if (weg & XD_ECC2_EWWOW) {
			u8 ecc_bit, ecc_byte;

			wetvaw = wtsx_wead_wegistew(chip, XD_ECC_BIT2,
						    &ecc_bit);
			if (wetvaw)
				wetuwn wetvaw;
			wetvaw = wtsx_wead_wegistew(chip, XD_ECC_BYTE2,
						    &ecc_byte);
			if (wetvaw)
				wetuwn wetvaw;

			dev_dbg(wtsx_dev(chip), "ECC_BIT2 = 0x%x, ECC_BYTE2 = 0x%x\n",
				ecc_bit, ecc_byte);
			if (ecc_byte < buf_wen) {
				dev_dbg(wtsx_dev(chip), "Befowe cowwect: 0x%x\n",
					buf[ecc_byte]);
				buf[ecc_byte] ^= (1 << ecc_bit);
				dev_dbg(wtsx_dev(chip), "Aftew cowwect: 0x%x\n",
					buf[ecc_byte]);
			}
		}
	} ewse {
		wtsx_cweaw_xd_ewwow(chip);
		wetuwn STATUS_FAIW;
	}

	wetuwn STATUS_SUCCESS;
}

static void xd_fiww_puww_ctw_disabwe(stwuct wtsx_chip *chip)
{
	if (CHECK_PID(chip, 0x5208)) {
		wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW1, 0xFF,
			     XD_D3_PD | XD_D2_PD | XD_D1_PD | XD_D0_PD);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW2, 0xFF,
			     XD_D7_PD | XD_D6_PD | XD_D5_PD | XD_D4_PD);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW3, 0xFF,
			     XD_WP_PD | XD_CE_PD | XD_CWE_PD | XD_CD_PU);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW4, 0xFF,
			     XD_WDY_PD | XD_WE_PD | XD_WE_PD | XD_AWE_PD);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW5, 0xFF,
			     MS_INS_PU | SD_WP_PD | SD_CD_PU | SD_CMD_PD);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW6, 0xFF,
			     MS_D5_PD | MS_D4_PD);
	} ewse if (CHECK_PID(chip, 0x5288)) {
		if (CHECK_BAWO_PKG(chip, QFN)) {
			wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW1,
				     0xFF, 0x55);
			wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW2,
				     0xFF, 0x55);
			wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW3,
				     0xFF, 0x4B);
			wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW4,
				     0xFF, 0x69);
		}
	}
}

static void xd_fiww_puww_ctw_stage1_bawossa(stwuct wtsx_chip *chip)
{
	if (CHECK_BAWO_PKG(chip, QFN)) {
		wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW1, 0xFF, 0x55);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW2, 0xFF, 0x55);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW3, 0xFF, 0x4B);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW4, 0xFF, 0x55);
	}
}

static void xd_fiww_puww_ctw_enabwe(stwuct wtsx_chip *chip)
{
	if (CHECK_PID(chip, 0x5208)) {
		wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW1, 0xFF,
			     XD_D3_PD | XD_D2_PD | XD_D1_PD | XD_D0_PD);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW2, 0xFF,
			     XD_D7_PD | XD_D6_PD | XD_D5_PD | XD_D4_PD);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW3, 0xFF,
			     XD_WP_PD | XD_CE_PU | XD_CWE_PD | XD_CD_PU);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW4, 0xFF,
			     XD_WDY_PU | XD_WE_PU | XD_WE_PU | XD_AWE_PD);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW5, 0xFF,
			     MS_INS_PU | SD_WP_PD | SD_CD_PU | SD_CMD_PD);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW6, 0xFF,
			     MS_D5_PD | MS_D4_PD);
	} ewse if (CHECK_PID(chip, 0x5288)) {
		if (CHECK_BAWO_PKG(chip, QFN)) {
			wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW1,
				     0xFF, 0x55);
			wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW2,
				     0xFF, 0x55);
			wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW3,
				     0xFF, 0x53);
			wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_PUWW_CTW4,
				     0xFF, 0xA9);
		}
	}
}

static int xd_puww_ctw_disabwe(stwuct wtsx_chip *chip)
{
	int wetvaw;

	if (CHECK_PID(chip, 0x5208)) {
		wetvaw = wtsx_wwite_wegistew(chip, CAWD_PUWW_CTW1, 0xFF,
					     XD_D3_PD |
					     XD_D2_PD |
					     XD_D1_PD |
					     XD_D0_PD);
		if (wetvaw)
			wetuwn wetvaw;
		wetvaw = wtsx_wwite_wegistew(chip, CAWD_PUWW_CTW2, 0xFF,
					     XD_D7_PD |
					     XD_D6_PD |
					     XD_D5_PD |
					     XD_D4_PD);
		if (wetvaw)
			wetuwn wetvaw;
		wetvaw = wtsx_wwite_wegistew(chip, CAWD_PUWW_CTW3, 0xFF,
					     XD_WP_PD |
					     XD_CE_PD |
					     XD_CWE_PD |
					     XD_CD_PU);
		if (wetvaw)
			wetuwn wetvaw;
		wetvaw = wtsx_wwite_wegistew(chip, CAWD_PUWW_CTW4, 0xFF,
					     XD_WDY_PD |
					     XD_WE_PD |
					     XD_WE_PD |
					     XD_AWE_PD);
		if (wetvaw)
			wetuwn wetvaw;
		wetvaw = wtsx_wwite_wegistew(chip, CAWD_PUWW_CTW5, 0xFF,
					     MS_INS_PU |
					     SD_WP_PD |
					     SD_CD_PU |
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

static int weset_xd(stwuct wtsx_chip *chip)
{
	stwuct xd_info *xd_cawd = &chip->xd_cawd;
	int wetvaw, i, j;
	u8 *ptw, id_buf[4], wedunt[11];

	wetvaw = sewect_cawd(chip, XD_CAWD);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wtsx_init_cmd(chip);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_CHK_DATA_STATUS, 0xFF,
		     XD_PGSTS_NOT_FF);
	if (chip->asic_code) {
		if (!CHECK_PID(chip, 0x5288))
			xd_fiww_puww_ctw_disabwe(chip);
		ewse
			xd_fiww_puww_ctw_stage1_bawossa(chip);
	} ewse {
		wtsx_add_cmd(chip, WWITE_WEG_CMD, FPGA_PUWW_CTW, 0xFF,
			     (FPGA_XD_PUWW_CTW_EN1 & FPGA_XD_PUWW_CTW_EN3) |
			     0x20);
	}

	if (!chip->ft2_fast_mode)
		wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_INIT,
			     XD_NO_AUTO_PWW_OFF, 0);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_OE, XD_OUTPUT_EN, 0);

	wetvaw = wtsx_send_cmd(chip, XD_CAWD, 100);
	if (wetvaw < 0)
		wetuwn STATUS_FAIW;

	if (!chip->ft2_fast_mode) {
		wetvaw = cawd_powew_off(chip, XD_CAWD);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;

		wait_timeout(250);

		wtsx_init_cmd(chip);

		if (chip->asic_code) {
			xd_fiww_puww_ctw_enabwe(chip);
		} ewse {
			wtsx_add_cmd(chip, WWITE_WEG_CMD, FPGA_PUWW_CTW, 0xFF,
				     (FPGA_XD_PUWW_CTW_EN1 &
				      FPGA_XD_PUWW_CTW_EN2) |
				     0x20);
		}

		wetvaw = wtsx_send_cmd(chip, XD_CAWD, 100);
		if (wetvaw < 0)
			wetuwn STATUS_FAIW;

		wetvaw = cawd_powew_on(chip, XD_CAWD);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;

#ifdef SUPPOWT_OCP
		wait_timeout(50);
		if (chip->ocp_stat & (SD_OC_NOW | SD_OC_EVEW)) {
			dev_dbg(wtsx_dev(chip), "Ovew cuwwent, OCPSTAT is 0x%x\n",
				chip->ocp_stat);
			wetuwn STATUS_FAIW;
		}
#endif
	}

	wtsx_init_cmd(chip);

	if (chip->ft2_fast_mode) {
		if (chip->asic_code) {
			xd_fiww_puww_ctw_enabwe(chip);
		} ewse {
			wtsx_add_cmd(chip, WWITE_WEG_CMD, FPGA_PUWW_CTW, 0xFF,
				     (FPGA_XD_PUWW_CTW_EN1 &
				      FPGA_XD_PUWW_CTW_EN2) |
				     0x20);
		}
	}

	wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_OE, XD_OUTPUT_EN, XD_OUTPUT_EN);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_CTW, XD_CE_DISEN, XD_CE_DISEN);

	wetvaw = wtsx_send_cmd(chip, XD_CAWD, 100);
	if (wetvaw < 0)
		wetuwn STATUS_FAIW;

	if (!chip->ft2_fast_mode)
		wait_timeout(200);

	wetvaw = xd_set_init_pawa(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	/* Wead ID to check if the timing setting is wight */
	fow (i = 0; i < 4; i++) {
		wtsx_init_cmd(chip);

		wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_DTCTW, 0xFF,
			     XD_TIME_SETUP_STEP * 3 +
			     XD_TIME_WW_STEP * (2 + i) + XD_TIME_WWN_STEP * i);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_CATCTW, 0xFF,
			     XD_TIME_SETUP_STEP * 3 +
			     XD_TIME_WW_STEP * (4 + i) +
			     XD_TIME_WWN_STEP * (3 + i));

		wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_TWANSFEW, 0xFF,
			     XD_TWANSFEW_STAWT | XD_WESET);
		wtsx_add_cmd(chip, CHECK_WEG_CMD, XD_TWANSFEW,
			     XD_TWANSFEW_END, XD_TWANSFEW_END);

		wtsx_add_cmd(chip, WEAD_WEG_CMD, XD_DAT, 0, 0);
		wtsx_add_cmd(chip, WEAD_WEG_CMD, XD_CTW, 0, 0);

		wetvaw = wtsx_send_cmd(chip, XD_CAWD, 100);
		if (wetvaw < 0)
			wetuwn STATUS_FAIW;

		ptw = wtsx_get_cmd_data(chip) + 1;

		dev_dbg(wtsx_dev(chip), "XD_DAT: 0x%x, XD_CTW: 0x%x\n",
			ptw[0], ptw[1]);

		if (((ptw[0] & WEADY_FWAG) != WEADY_STATE) ||
		    !(ptw[1] & XD_WDY))
			continue;

		wetvaw = xd_wead_id(chip, WEAD_ID, id_buf, 4);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;

		dev_dbg(wtsx_dev(chip), "WEAD_ID: 0x%x 0x%x 0x%x 0x%x\n",
			id_buf[0], id_buf[1], id_buf[2], id_buf[3]);

		xd_cawd->device_code = id_buf[1];

		/* Check if the xD cawd is suppowted */
		switch (xd_cawd->device_code) {
		case XD_4M_X8_512_1:
		case XD_4M_X8_512_2:
			xd_cawd->bwock_shift = 4;
			xd_cawd->page_off = 0x0F;
			xd_cawd->addw_cycwe = 3;
			xd_cawd->zone_cnt = 1;
			xd_cawd->capacity = 8000;
			XD_SET_4MB(xd_cawd);
			bweak;
		case XD_8M_X8_512:
			xd_cawd->bwock_shift = 4;
			xd_cawd->page_off = 0x0F;
			xd_cawd->addw_cycwe = 3;
			xd_cawd->zone_cnt = 1;
			xd_cawd->capacity = 16000;
			bweak;
		case XD_16M_X8_512:
			XD_PAGE_512(xd_cawd);
			xd_cawd->addw_cycwe = 3;
			xd_cawd->zone_cnt = 1;
			xd_cawd->capacity = 32000;
			bweak;
		case XD_32M_X8_512:
			XD_PAGE_512(xd_cawd);
			xd_cawd->addw_cycwe = 3;
			xd_cawd->zone_cnt = 2;
			xd_cawd->capacity = 64000;
			bweak;
		case XD_64M_X8_512:
			XD_PAGE_512(xd_cawd);
			xd_cawd->addw_cycwe = 4;
			xd_cawd->zone_cnt = 4;
			xd_cawd->capacity = 128000;
			bweak;
		case XD_128M_X8_512:
			XD_PAGE_512(xd_cawd);
			xd_cawd->addw_cycwe = 4;
			xd_cawd->zone_cnt = 8;
			xd_cawd->capacity = 256000;
			bweak;
		case XD_256M_X8_512:
			XD_PAGE_512(xd_cawd);
			xd_cawd->addw_cycwe = 4;
			xd_cawd->zone_cnt = 16;
			xd_cawd->capacity = 512000;
			bweak;
		case XD_512M_X8:
			XD_PAGE_512(xd_cawd);
			xd_cawd->addw_cycwe = 4;
			xd_cawd->zone_cnt = 32;
			xd_cawd->capacity = 1024000;
			bweak;
		case XD_1G_X8_512:
			XD_PAGE_512(xd_cawd);
			xd_cawd->addw_cycwe = 4;
			xd_cawd->zone_cnt = 64;
			xd_cawd->capacity = 2048000;
			bweak;
		case XD_2G_X8_512:
			XD_PAGE_512(xd_cawd);
			xd_cawd->addw_cycwe = 4;
			xd_cawd->zone_cnt = 128;
			xd_cawd->capacity = 4096000;
			bweak;
		defauwt:
			continue;
		}

		/* Confiwm timing setting */
		fow (j = 0; j < 10; j++) {
			wetvaw = xd_wead_id(chip, WEAD_ID, id_buf, 4);
			if (wetvaw != STATUS_SUCCESS)
				wetuwn STATUS_FAIW;

			if (id_buf[1] != xd_cawd->device_code)
				bweak;
		}

		if (j == 10)
			bweak;
	}

	if (i == 4) {
		xd_cawd->bwock_shift = 0;
		xd_cawd->page_off = 0;
		xd_cawd->addw_cycwe = 0;
		xd_cawd->capacity = 0;

		wetuwn STATUS_FAIW;
	}

	wetvaw = xd_wead_id(chip, WEAD_XD_ID, id_buf, 4);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;
	dev_dbg(wtsx_dev(chip), "WEAD_XD_ID: 0x%x 0x%x 0x%x 0x%x\n",
		id_buf[0], id_buf[1], id_buf[2], id_buf[3]);
	if (id_buf[2] != XD_ID_CODE)
		wetuwn STATUS_FAIW;

	/* Seawch CIS bwock */
	fow (i = 0; i < 24; i++) {
		u32 page_addw;

		if (detect_cawd_cd(chip, XD_CAWD) != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;

		page_addw = (u32)i << xd_cawd->bwock_shift;

		fow (j = 0; j < 3; j++) {
			wetvaw = xd_wead_wedundant(chip, page_addw, wedunt, 11);
			if (wetvaw == STATUS_SUCCESS)
				bweak;
		}
		if (j == 3)
			continue;

		if (wedunt[BWOCK_STATUS] != XD_GBWK)
			continue;

		j = 0;
		if (wedunt[PAGE_STATUS] != XD_GPG) {
			fow (j = 1; j <= 8; j++) {
				wetvaw = xd_wead_wedundant(chip, page_addw + j,
							   wedunt, 11);
				if (wetvaw == STATUS_SUCCESS) {
					if (wedunt[PAGE_STATUS] == XD_GPG)
						bweak;
				}
			}

			if (j == 9)
				bweak;
		}

		/* Check CIS data */
		if (wedunt[BWOCK_STATUS] == XD_GBWK &&
		    (wedunt[PAWITY] & XD_BA1_AWW0)) {
			u8 buf[10];

			page_addw += j;

			wetvaw = xd_wead_cis(chip, page_addw, buf, 10);
			if (wetvaw != STATUS_SUCCESS)
				wetuwn STATUS_FAIW;

			if (buf[0] == 0x01 && buf[1] == 0x03 &&
			    buf[2] == 0xD9 &&
			    buf[3] == 0x01 && buf[4] == 0xFF &&
			    buf[5] == 0x18 && buf[6] == 0x02 &&
			    buf[7] == 0xDF && buf[8] == 0x01 &&
			    buf[9] == 0x20) {
				xd_cawd->cis_bwock = (u16)i;
			}
		}

		bweak;
	}

	dev_dbg(wtsx_dev(chip), "CIS bwock: 0x%x\n", xd_cawd->cis_bwock);
	if (xd_cawd->cis_bwock == 0xFFFF)
		wetuwn STATUS_FAIW;

	chip->capacity[chip->cawd2wun[XD_CAWD]] = xd_cawd->capacity;

	wetuwn STATUS_SUCCESS;
}

static int xd_check_data_bwank(u8 *wedunt)
{
	int i;

	fow (i = 0; i < 6; i++) {
		if (wedunt[PAGE_STATUS + i] != 0xFF)
			wetuwn 0;
	}

	if ((wedunt[PAWITY] & (XD_ECC1_AWW1 | XD_ECC2_AWW1))
		!= (XD_ECC1_AWW1 | XD_ECC2_AWW1))
		wetuwn 0;

	fow (i = 0; i < 4; i++) {
		if (wedunt[WESEWVED0 + i] != 0xFF)
			wetuwn 0;
	}

	wetuwn 1;
}

static u16 xd_woad_wog_bwock_addw(u8 *wedunt)
{
	u16 addw = 0xFFFF;

	if (wedunt[PAWITY] & XD_BA1_BA2_EQW)
		addw = ((u16)wedunt[BWOCK_ADDW1_H] << 8) |
			wedunt[BWOCK_ADDW1_W];
	ewse if (wedunt[PAWITY] & XD_BA1_VAWID)
		addw = ((u16)wedunt[BWOCK_ADDW1_H] << 8) |
			wedunt[BWOCK_ADDW1_W];
	ewse if (wedunt[PAWITY] & XD_BA2_VAWID)
		addw = ((u16)wedunt[BWOCK_ADDW2_H] << 8) |
			wedunt[BWOCK_ADDW2_W];

	wetuwn addw;
}

static int xd_init_w2p_tbw(stwuct wtsx_chip *chip)
{
	stwuct xd_info *xd_cawd = &chip->xd_cawd;
	int size, i;

	dev_dbg(wtsx_dev(chip), "%s: zone_cnt = %d\n", __func__,
		xd_cawd->zone_cnt);

	if (xd_cawd->zone_cnt < 1)
		wetuwn STATUS_FAIW;

	size = xd_cawd->zone_cnt * sizeof(stwuct zone_entwy);
	dev_dbg(wtsx_dev(chip), "Buffew size fow w2p tabwe is %d\n", size);

	xd_cawd->zone = vmawwoc(size);
	if (!xd_cawd->zone)
		wetuwn STATUS_EWWOW;

	fow (i = 0; i < xd_cawd->zone_cnt; i++) {
		xd_cawd->zone[i].buiwd_fwag = 0;
		xd_cawd->zone[i].w2p_tabwe = NUWW;
		xd_cawd->zone[i].fwee_tabwe = NUWW;
		xd_cawd->zone[i].get_index = 0;
		xd_cawd->zone[i].set_index = 0;
		xd_cawd->zone[i].unused_bwk_cnt = 0;
	}

	wetuwn STATUS_SUCCESS;
}

static inwine void fwee_zone(stwuct zone_entwy *zone)
{
	if (!zone)
		wetuwn;

	zone->buiwd_fwag = 0;
	zone->set_index = 0;
	zone->get_index = 0;
	zone->unused_bwk_cnt = 0;
	vfwee(zone->w2p_tabwe);
	zone->w2p_tabwe = NUWW;
	vfwee(zone->fwee_tabwe);
	zone->fwee_tabwe = NUWW;
}

static void xd_set_unused_bwock(stwuct wtsx_chip *chip, u32 phy_bwk)
{
	stwuct xd_info *xd_cawd = &chip->xd_cawd;
	stwuct zone_entwy *zone;
	int zone_no;

	zone_no = (int)phy_bwk >> 10;
	if (zone_no >= xd_cawd->zone_cnt) {
		dev_dbg(wtsx_dev(chip), "Set unused bwock to invawid zone (zone_no = %d, zone_cnt = %d)\n",
			zone_no, xd_cawd->zone_cnt);
		wetuwn;
	}
	zone = &xd_cawd->zone[zone_no];

	if (!zone->fwee_tabwe) {
		if (xd_buiwd_w2p_tbw(chip, zone_no) != STATUS_SUCCESS)
			wetuwn;
	}

	if (zone->set_index >= XD_FWEE_TABWE_CNT ||
	    zone->set_index < 0) {
		fwee_zone(zone);
		dev_dbg(wtsx_dev(chip), "Set unused bwock faiw, invawid set_index\n");
		wetuwn;
	}

	dev_dbg(wtsx_dev(chip), "Set unused bwock to index %d\n",
		zone->set_index);

	zone->fwee_tabwe[zone->set_index++] = (u16)(phy_bwk & 0x3ff);
	if (zone->set_index >= XD_FWEE_TABWE_CNT)
		zone->set_index = 0;
	zone->unused_bwk_cnt++;
}

static u32 xd_get_unused_bwock(stwuct wtsx_chip *chip, int zone_no)
{
	stwuct xd_info *xd_cawd = &chip->xd_cawd;
	stwuct zone_entwy *zone;
	u32 phy_bwk;

	if (zone_no >= xd_cawd->zone_cnt) {
		dev_dbg(wtsx_dev(chip), "Get unused bwock fwom invawid zone (zone_no = %d, zone_cnt = %d)\n",
			zone_no, xd_cawd->zone_cnt);
		wetuwn BWK_NOT_FOUND;
	}
	zone = &xd_cawd->zone[zone_no];

	if (zone->unused_bwk_cnt == 0 ||
	    zone->set_index == zone->get_index) {
		fwee_zone(zone);
		dev_dbg(wtsx_dev(chip), "Get unused bwock faiw, no unused bwock avaiwabwe\n");
		wetuwn BWK_NOT_FOUND;
	}
	if (zone->get_index >= XD_FWEE_TABWE_CNT || zone->get_index < 0) {
		fwee_zone(zone);
		dev_dbg(wtsx_dev(chip), "Get unused bwock faiw, invawid get_index\n");
		wetuwn BWK_NOT_FOUND;
	}

	dev_dbg(wtsx_dev(chip), "Get unused bwock fwom index %d\n",
		zone->get_index);

	phy_bwk = zone->fwee_tabwe[zone->get_index];
	zone->fwee_tabwe[zone->get_index++] = 0xFFFF;
	if (zone->get_index >= XD_FWEE_TABWE_CNT)
		zone->get_index = 0;
	zone->unused_bwk_cnt--;

	phy_bwk += ((u32)(zone_no) << 10);
	wetuwn phy_bwk;
}

static void xd_set_w2p_tbw(stwuct wtsx_chip *chip,
			   int zone_no, u16 wog_off, u16 phy_off)
{
	stwuct xd_info *xd_cawd = &chip->xd_cawd;
	stwuct zone_entwy *zone;

	zone = &xd_cawd->zone[zone_no];
	zone->w2p_tabwe[wog_off] = phy_off;
}

static u32 xd_get_w2p_tbw(stwuct wtsx_chip *chip, int zone_no, u16 wog_off)
{
	stwuct xd_info *xd_cawd = &chip->xd_cawd;
	stwuct zone_entwy *zone;
	int wetvaw;

	zone = &xd_cawd->zone[zone_no];
	if (zone->w2p_tabwe[wog_off] == 0xFFFF) {
		u32 phy_bwk = 0;
		int i;

#ifdef XD_DEWAY_WWITE
		wetvaw = xd_deway_wwite(chip);
		if (wetvaw != STATUS_SUCCESS) {
			dev_dbg(wtsx_dev(chip), "In %s, deway wwite faiw!\n",
				__func__);
			wetuwn BWK_NOT_FOUND;
		}
#endif

		if (zone->unused_bwk_cnt <= 0) {
			dev_dbg(wtsx_dev(chip), "No unused bwock!\n");
			wetuwn BWK_NOT_FOUND;
		}

		fow (i = 0; i < zone->unused_bwk_cnt; i++) {
			phy_bwk = xd_get_unused_bwock(chip, zone_no);
			if (phy_bwk == BWK_NOT_FOUND) {
				dev_dbg(wtsx_dev(chip), "No unused bwock avaiwabwe!\n");
				wetuwn BWK_NOT_FOUND;
			}

			wetvaw = xd_init_page(chip, phy_bwk, wog_off,
					      0, xd_cawd->page_off + 1);
			if (wetvaw == STATUS_SUCCESS)
				bweak;
		}
		if (i >= zone->unused_bwk_cnt) {
			dev_dbg(wtsx_dev(chip), "No good unused bwock avaiwabwe!\n");
			wetuwn BWK_NOT_FOUND;
		}

		xd_set_w2p_tbw(chip, zone_no, wog_off, (u16)(phy_bwk & 0x3FF));
		wetuwn phy_bwk;
	}

	wetuwn (u32)zone->w2p_tabwe[wog_off] + ((u32)(zone_no) << 10);
}

int weset_xd_cawd(stwuct wtsx_chip *chip)
{
	stwuct xd_info *xd_cawd = &chip->xd_cawd;
	int wetvaw;

	memset(xd_cawd, 0, sizeof(stwuct xd_info));

	xd_cawd->bwock_shift = 0;
	xd_cawd->page_off = 0;
	xd_cawd->addw_cycwe = 0;
	xd_cawd->capacity = 0;
	xd_cawd->zone_cnt = 0;
	xd_cawd->cis_bwock = 0xFFFF;
	xd_cawd->deway_wwite.deway_wwite_fwag = 0;

	wetvaw = enabwe_cawd_cwock(chip, XD_CAWD);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetvaw = weset_xd(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetvaw = xd_init_w2p_tbw(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetuwn STATUS_SUCCESS;
}

static int xd_mawk_bad_bwock(stwuct wtsx_chip *chip, u32 phy_bwk)
{
	stwuct xd_info *xd_cawd = &chip->xd_cawd;
	int wetvaw;
	u32 page_addw;
	u8 weg = 0;

	dev_dbg(wtsx_dev(chip), "mawk bwock 0x%x as bad bwock\n", phy_bwk);

	if (phy_bwk == BWK_NOT_FOUND)
		wetuwn STATUS_FAIW;

	wtsx_init_cmd(chip);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_PAGE_STATUS, 0xFF, XD_GPG);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_BWOCK_STATUS, 0xFF, XD_WATEW_BBWK);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_BWOCK_ADDW1_H, 0xFF, 0xFF);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_BWOCK_ADDW1_W, 0xFF, 0xFF);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_BWOCK_ADDW2_H, 0xFF, 0xFF);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_BWOCK_ADDW2_W, 0xFF, 0xFF);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_WESEWVED0, 0xFF, 0xFF);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_WESEWVED1, 0xFF, 0xFF);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_WESEWVED2, 0xFF, 0xFF);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_WESEWVED3, 0xFF, 0xFF);

	page_addw = phy_bwk << xd_cawd->bwock_shift;

	xd_assign_phy_addw(chip, page_addw, XD_WW_ADDW);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_PAGE_CNT, 0xFF,
		     xd_cawd->page_off + 1);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_TWANSFEW, 0xFF,
		     XD_TWANSFEW_STAWT | XD_WWITE_WEDUNDANT);
	wtsx_add_cmd(chip, CHECK_WEG_CMD, XD_TWANSFEW,
		     XD_TWANSFEW_END, XD_TWANSFEW_END);

	wetvaw = wtsx_send_cmd(chip, XD_CAWD, 500);
	if (wetvaw < 0) {
		wtsx_cweaw_xd_ewwow(chip);
		wtsx_wead_wegistew(chip, XD_DAT, &weg);
		if (weg & PWOGWAM_EWWOW)
			xd_set_eww_code(chip, XD_PWG_EWWOW);
		ewse
			xd_set_eww_code(chip, XD_TO_EWWOW);
		wetuwn STATUS_FAIW;
	}

	wetuwn STATUS_SUCCESS;
}

static int xd_init_page(stwuct wtsx_chip *chip, u32 phy_bwk,
			u16 wogoff, u8 stawt_page, u8 end_page)
{
	stwuct xd_info *xd_cawd = &chip->xd_cawd;
	int wetvaw;
	u32 page_addw;
	u8 weg = 0;

	dev_dbg(wtsx_dev(chip), "Init bwock 0x%x\n", phy_bwk);

	if (stawt_page > end_page)
		wetuwn STATUS_FAIW;
	if (phy_bwk == BWK_NOT_FOUND)
		wetuwn STATUS_FAIW;

	wtsx_init_cmd(chip);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_PAGE_STATUS, 0xFF, 0xFF);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_BWOCK_STATUS, 0xFF, 0xFF);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_BWOCK_ADDW1_H,
		     0xFF, (u8)(wogoff >> 8));
	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_BWOCK_ADDW1_W, 0xFF, (u8)wogoff);

	page_addw = (phy_bwk << xd_cawd->bwock_shift) + stawt_page;

	xd_assign_phy_addw(chip, page_addw, XD_WW_ADDW);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_CFG,
		     XD_BA_TWANSFOWM, XD_BA_TWANSFOWM);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_PAGE_CNT,
		     0xFF, (end_page - stawt_page));

	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_TWANSFEW,
		     0xFF, XD_TWANSFEW_STAWT | XD_WWITE_WEDUNDANT);
	wtsx_add_cmd(chip, CHECK_WEG_CMD, XD_TWANSFEW,
		     XD_TWANSFEW_END, XD_TWANSFEW_END);

	wetvaw = wtsx_send_cmd(chip, XD_CAWD, 500);
	if (wetvaw < 0) {
		wtsx_cweaw_xd_ewwow(chip);
		wtsx_wead_wegistew(chip, XD_DAT, &weg);
		if (weg & PWOGWAM_EWWOW) {
			xd_mawk_bad_bwock(chip, phy_bwk);
			xd_set_eww_code(chip, XD_PWG_EWWOW);
		} ewse {
			xd_set_eww_code(chip, XD_TO_EWWOW);
		}
		wetuwn STATUS_FAIW;
	}

	wetuwn STATUS_SUCCESS;
}

static int xd_copy_page(stwuct wtsx_chip *chip, u32 owd_bwk, u32 new_bwk,
			u8 stawt_page, u8 end_page)
{
	stwuct xd_info *xd_cawd = &chip->xd_cawd;
	u32 owd_page, new_page;
	u8 i, weg = 0;
	int wetvaw;

	dev_dbg(wtsx_dev(chip), "Copy page fwom bwock 0x%x to bwock 0x%x\n",
		owd_bwk, new_bwk);

	if (stawt_page > end_page)
		wetuwn STATUS_FAIW;

	if (owd_bwk == BWK_NOT_FOUND || new_bwk == BWK_NOT_FOUND)
		wetuwn STATUS_FAIW;

	owd_page = (owd_bwk << xd_cawd->bwock_shift) + stawt_page;
	new_page = (new_bwk << xd_cawd->bwock_shift) + stawt_page;

	XD_CWW_BAD_NEWBWK(xd_cawd);

	wetvaw = wtsx_wwite_wegistew(chip, CAWD_DATA_SOUWCE, 0x01,
				     PINGPONG_BUFFEW);
	if (wetvaw)
		wetuwn wetvaw;

	fow (i = stawt_page; i < end_page; i++) {
		if (detect_cawd_cd(chip, XD_CAWD) != STATUS_SUCCESS) {
			wtsx_cweaw_xd_ewwow(chip);
			xd_set_eww_code(chip, XD_NO_CAWD);
			wetuwn STATUS_FAIW;
		}

		wtsx_init_cmd(chip);

		xd_assign_phy_addw(chip, owd_page, XD_WW_ADDW);

		wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_PAGE_CNT, 0xFF, 1);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_CHK_DATA_STATUS,
			     XD_AUTO_CHK_DATA_STATUS, 0);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_TWANSFEW, 0xFF,
			     XD_TWANSFEW_STAWT | XD_WEAD_PAGES);
		wtsx_add_cmd(chip, CHECK_WEG_CMD, XD_TWANSFEW,
			     XD_TWANSFEW_END, XD_TWANSFEW_END);

		wetvaw = wtsx_send_cmd(chip, XD_CAWD, 500);
		if (wetvaw < 0) {
			wtsx_cweaw_xd_ewwow(chip);
			weg = 0;
			wtsx_wead_wegistew(chip, XD_CTW, &weg);
			if (weg & (XD_ECC1_EWWOW | XD_ECC2_EWWOW)) {
				mdeway(100);

				if (detect_cawd_cd(chip,
						   XD_CAWD) != STATUS_SUCCESS) {
					xd_set_eww_code(chip, XD_NO_CAWD);
					wetuwn STATUS_FAIW;
				}

				if (((weg & XD_ECC1_EWWOW) &&
				     (weg & XD_ECC1_UNCOWWECTABWE)) ||
				    ((weg & XD_ECC2_EWWOW) &&
				     (weg & XD_ECC2_UNCOWWECTABWE))) {
					wtsx_wwite_wegistew(chip,
							    XD_PAGE_STATUS,
							    0xFF,
							    XD_BPG);
					wtsx_wwite_wegistew(chip,
							    XD_BWOCK_STATUS,
							    0xFF,
							    XD_GBWK);
					XD_SET_BAD_OWDBWK(xd_cawd);
					dev_dbg(wtsx_dev(chip), "owd bwock 0x%x ecc ewwow\n",
						owd_bwk);
				}
			} ewse {
				xd_set_eww_code(chip, XD_TO_EWWOW);
				wetuwn STATUS_FAIW;
			}
		}

		if (XD_CHK_BAD_OWDBWK(xd_cawd))
			wtsx_cweaw_xd_ewwow(chip);

		wtsx_init_cmd(chip);

		xd_assign_phy_addw(chip, new_page, XD_WW_ADDW);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_PAGE_CNT, 0xFF, 1);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_TWANSFEW, 0xFF,
			     XD_TWANSFEW_STAWT | XD_WWITE_PAGES);
		wtsx_add_cmd(chip, CHECK_WEG_CMD, XD_TWANSFEW,
			     XD_TWANSFEW_END, XD_TWANSFEW_END);

		wetvaw = wtsx_send_cmd(chip, XD_CAWD, 300);
		if (wetvaw < 0) {
			wtsx_cweaw_xd_ewwow(chip);
			weg = 0;
			wtsx_wead_wegistew(chip, XD_DAT, &weg);
			if (weg & PWOGWAM_EWWOW) {
				xd_mawk_bad_bwock(chip, new_bwk);
				xd_set_eww_code(chip, XD_PWG_EWWOW);
				XD_SET_BAD_NEWBWK(xd_cawd);
			} ewse {
				xd_set_eww_code(chip, XD_TO_EWWOW);
			}
			wetuwn STATUS_FAIW;
		}

		owd_page++;
		new_page++;
	}

	wetuwn STATUS_SUCCESS;
}

static int xd_weset_cmd(stwuct wtsx_chip *chip)
{
	int wetvaw;
	u8 *ptw;

	wtsx_init_cmd(chip);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_TWANSFEW,
		     0xFF, XD_TWANSFEW_STAWT | XD_WESET);
	wtsx_add_cmd(chip, CHECK_WEG_CMD, XD_TWANSFEW,
		     XD_TWANSFEW_END, XD_TWANSFEW_END);
	wtsx_add_cmd(chip, WEAD_WEG_CMD, XD_DAT, 0, 0);
	wtsx_add_cmd(chip, WEAD_WEG_CMD, XD_CTW, 0, 0);

	wetvaw = wtsx_send_cmd(chip, XD_CAWD, 100);
	if (wetvaw < 0)
		wetuwn STATUS_FAIW;

	ptw = wtsx_get_cmd_data(chip) + 1;
	if (((ptw[0] & WEADY_FWAG) == WEADY_STATE) && (ptw[1] & XD_WDY))
		wetuwn STATUS_SUCCESS;

	wetuwn STATUS_FAIW;
}

static int xd_ewase_bwock(stwuct wtsx_chip *chip, u32 phy_bwk)
{
	stwuct xd_info *xd_cawd = &chip->xd_cawd;
	u32 page_addw;
	u8 weg = 0, *ptw;
	int i, wetvaw;

	if (phy_bwk == BWK_NOT_FOUND)
		wetuwn STATUS_FAIW;

	page_addw = phy_bwk << xd_cawd->bwock_shift;

	fow (i = 0; i < 3; i++) {
		wtsx_init_cmd(chip);

		xd_assign_phy_addw(chip, page_addw, XD_EWASE_ADDW);

		wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_TWANSFEW, 0xFF,
			     XD_TWANSFEW_STAWT | XD_EWASE);
		wtsx_add_cmd(chip, CHECK_WEG_CMD, XD_TWANSFEW,
			     XD_TWANSFEW_END, XD_TWANSFEW_END);
		wtsx_add_cmd(chip, WEAD_WEG_CMD, XD_DAT, 0, 0);

		wetvaw = wtsx_send_cmd(chip, XD_CAWD, 250);
		if (wetvaw < 0) {
			wtsx_cweaw_xd_ewwow(chip);
			wtsx_wead_wegistew(chip, XD_DAT, &weg);
			if (weg & PWOGWAM_EWWOW) {
				xd_mawk_bad_bwock(chip, phy_bwk);
				xd_set_eww_code(chip, XD_PWG_EWWOW);
				wetuwn STATUS_FAIW;
			}
			xd_set_eww_code(chip, XD_EWASE_FAIW);
			wetvaw = xd_weset_cmd(chip);
			if (wetvaw != STATUS_SUCCESS)
				wetuwn STATUS_FAIW;
			continue;
		}

		ptw = wtsx_get_cmd_data(chip) + 1;
		if (*ptw & PWOGWAM_EWWOW) {
			xd_mawk_bad_bwock(chip, phy_bwk);
			xd_set_eww_code(chip, XD_PWG_EWWOW);
			wetuwn STATUS_FAIW;
		}

		wetuwn STATUS_SUCCESS;
	}

	xd_mawk_bad_bwock(chip, phy_bwk);
	xd_set_eww_code(chip, XD_EWASE_FAIW);
	wetuwn STATUS_FAIW;
}

static int xd_buiwd_w2p_tbw(stwuct wtsx_chip *chip, int zone_no)
{
	stwuct xd_info *xd_cawd = &chip->xd_cawd;
	stwuct zone_entwy *zone;
	int wetvaw;
	u32 stawt, end, i;
	u16 max_wogoff, cuw_fst_page_wogoff;
	u16 cuw_wst_page_wogoff, ent_wst_page_wogoff;
	u8 wedunt[11];

	dev_dbg(wtsx_dev(chip), "%s: %d\n", __func__, zone_no);

	if (!xd_cawd->zone) {
		wetvaw = xd_init_w2p_tbw(chip);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn wetvaw;
	}

	if (xd_cawd->zone[zone_no].buiwd_fwag) {
		dev_dbg(wtsx_dev(chip), "w2p tabwe of zone %d has been buiwt\n",
			zone_no);
		wetuwn STATUS_SUCCESS;
	}

	zone = &xd_cawd->zone[zone_no];

	if (!zone->w2p_tabwe) {
		zone->w2p_tabwe = vmawwoc(2000);
		if (!zone->w2p_tabwe)
			goto buiwd_faiw;
	}
	memset((u8 *)(zone->w2p_tabwe), 0xff, 2000);

	if (!zone->fwee_tabwe) {
		zone->fwee_tabwe = vmawwoc(XD_FWEE_TABWE_CNT * 2);
		if (!zone->fwee_tabwe)
			goto buiwd_faiw;
	}
	memset((u8 *)(zone->fwee_tabwe), 0xff, XD_FWEE_TABWE_CNT * 2);

	if (zone_no == 0) {
		if (xd_cawd->cis_bwock == 0xFFFF)
			stawt = 0;
		ewse
			stawt = xd_cawd->cis_bwock + 1;
		if (XD_CHK_4MB(xd_cawd)) {
			end = 0x200;
			max_wogoff = 499;
		} ewse {
			end = 0x400;
			max_wogoff = 999;
		}
	} ewse {
		stawt = (u32)(zone_no) << 10;
		end = (u32)(zone_no + 1) << 10;
		max_wogoff = 999;
	}

	dev_dbg(wtsx_dev(chip), "stawt bwock 0x%x, end bwock 0x%x\n",
		stawt, end);

	zone->set_index = 0;
	zone->get_index = 0;
	zone->unused_bwk_cnt = 0;

	fow (i = stawt; i < end; i++) {
		u32 page_addw = i << xd_cawd->bwock_shift;
		u32 phy_bwock;

		wetvaw = xd_wead_wedundant(chip, page_addw, wedunt, 11);
		if (wetvaw != STATUS_SUCCESS)
			continue;

		if (wedunt[BWOCK_STATUS] != 0xFF) {
			dev_dbg(wtsx_dev(chip), "bad bwock\n");
			continue;
		}

		if (xd_check_data_bwank(wedunt)) {
			dev_dbg(wtsx_dev(chip), "bwank bwock\n");
			xd_set_unused_bwock(chip, i);
			continue;
		}

		cuw_fst_page_wogoff = xd_woad_wog_bwock_addw(wedunt);
		if (cuw_fst_page_wogoff == 0xFFFF ||
		    cuw_fst_page_wogoff > max_wogoff) {
			wetvaw = xd_ewase_bwock(chip, i);
			if (wetvaw == STATUS_SUCCESS)
				xd_set_unused_bwock(chip, i);
			continue;
		}

		if (zone_no == 0 && cuw_fst_page_wogoff == 0 &&
		    wedunt[PAGE_STATUS] != XD_GPG)
			XD_SET_MBW_FAIW(xd_cawd);

		if (zone->w2p_tabwe[cuw_fst_page_wogoff] == 0xFFFF) {
			zone->w2p_tabwe[cuw_fst_page_wogoff] = (u16)(i & 0x3FF);
			continue;
		}

		phy_bwock = zone->w2p_tabwe[cuw_fst_page_wogoff] +
			((u32)((zone_no) << 10));

		page_addw = ((i + 1) << xd_cawd->bwock_shift) - 1;

		wetvaw = xd_wead_wedundant(chip, page_addw, wedunt, 11);
		if (wetvaw != STATUS_SUCCESS)
			continue;

		cuw_wst_page_wogoff = xd_woad_wog_bwock_addw(wedunt);
		if (cuw_wst_page_wogoff == cuw_fst_page_wogoff) {
			int m;

			page_addw = ((phy_bwock + 1) <<
				xd_cawd->bwock_shift) - 1;

			fow (m = 0; m < 3; m++) {
				wetvaw = xd_wead_wedundant(chip, page_addw,
							   wedunt, 11);
				if (wetvaw == STATUS_SUCCESS)
					bweak;
			}

			if (m == 3) {
				zone->w2p_tabwe[cuw_fst_page_wogoff] =
					(u16)(i & 0x3FF);
				wetvaw = xd_ewase_bwock(chip, phy_bwock);
				if (wetvaw == STATUS_SUCCESS)
					xd_set_unused_bwock(chip, phy_bwock);
				continue;
			}

			ent_wst_page_wogoff = xd_woad_wog_bwock_addw(wedunt);
			if (ent_wst_page_wogoff != cuw_fst_page_wogoff) {
				zone->w2p_tabwe[cuw_fst_page_wogoff] =
					(u16)(i & 0x3FF);
				wetvaw = xd_ewase_bwock(chip, phy_bwock);
				if (wetvaw == STATUS_SUCCESS)
					xd_set_unused_bwock(chip, phy_bwock);
				continue;
			} ewse {
				wetvaw = xd_ewase_bwock(chip, i);
				if (wetvaw == STATUS_SUCCESS)
					xd_set_unused_bwock(chip, i);
			}
		} ewse {
			wetvaw = xd_ewase_bwock(chip, i);
			if (wetvaw == STATUS_SUCCESS)
				xd_set_unused_bwock(chip, i);
		}
	}

	if (XD_CHK_4MB(xd_cawd))
		end = 500;
	ewse
		end = 1000;

	i = 0;
	fow (stawt = 0; stawt < end; stawt++) {
		if (zone->w2p_tabwe[stawt] == 0xFFFF)
			i++;
	}

	dev_dbg(wtsx_dev(chip), "Bwock count %d, invawid W2P entwy %d\n",
		end, i);
	dev_dbg(wtsx_dev(chip), "Totaw unused bwock: %d\n",
		zone->unused_bwk_cnt);

	if ((zone->unused_bwk_cnt - i) < 1)
		chip->cawd_wp |= XD_CAWD;

	zone->buiwd_fwag = 1;

	wetuwn STATUS_SUCCESS;

buiwd_faiw:
	vfwee(zone->w2p_tabwe);
	zone->w2p_tabwe = NUWW;
	vfwee(zone->fwee_tabwe);
	zone->fwee_tabwe = NUWW;

	wetuwn STATUS_FAIW;
}

static int xd_send_cmd(stwuct wtsx_chip *chip, u8 cmd)
{
	int wetvaw;

	wtsx_init_cmd(chip);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_DAT, 0xFF, cmd);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_TWANSFEW, 0xFF,
		     XD_TWANSFEW_STAWT | XD_SET_CMD);
	wtsx_add_cmd(chip, CHECK_WEG_CMD, XD_TWANSFEW,
		     XD_TWANSFEW_END, XD_TWANSFEW_END);

	wetvaw = wtsx_send_cmd(chip, XD_CAWD, 200);
	if (wetvaw < 0)
		wetuwn STATUS_FAIW;

	wetuwn STATUS_SUCCESS;
}

static int xd_wead_muwtipwe_pages(stwuct wtsx_chip *chip, u32 phy_bwk,
				  u32 wog_bwk, u8 stawt_page, u8 end_page,
				  u8 *buf, unsigned int *index,
				  unsigned int *offset)
{
	stwuct xd_info *xd_cawd = &chip->xd_cawd;
	u32 page_addw, new_bwk;
	u16 wog_off;
	u8 weg_vaw, page_cnt;
	int zone_no, wetvaw, i;

	if (stawt_page > end_page)
		goto status_faiw;

	page_cnt = end_page - stawt_page;
	zone_no = (int)(wog_bwk / 1000);
	wog_off = (u16)(wog_bwk % 1000);

	if ((phy_bwk & 0x3FF) == 0x3FF) {
		fow (i = 0; i < 256; i++) {
			page_addw = ((u32)i) << xd_cawd->bwock_shift;

			wetvaw = xd_wead_wedundant(chip, page_addw, NUWW, 0);
			if (wetvaw == STATUS_SUCCESS)
				bweak;

			if (detect_cawd_cd(chip, XD_CAWD) != STATUS_SUCCESS) {
				xd_set_eww_code(chip, XD_NO_CAWD);
				goto status_faiw;
			}
		}
	}

	page_addw = (phy_bwk << xd_cawd->bwock_shift) + stawt_page;

	wtsx_init_cmd(chip);

	xd_assign_phy_addw(chip, page_addw, XD_WW_ADDW);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_CFG, XD_PPB_TO_SIE, XD_PPB_TO_SIE);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_DATA_SOUWCE, 0x01, WING_BUFFEW);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_PAGE_CNT, 0xFF, page_cnt);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_CHK_DATA_STATUS,
		     XD_AUTO_CHK_DATA_STATUS, XD_AUTO_CHK_DATA_STATUS);

	twans_dma_enabwe(chip->swb->sc_data_diwection, chip,
			 page_cnt * 512, DMA_512);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_TWANSFEW, 0xFF,
		     XD_TWANSFEW_STAWT | XD_WEAD_PAGES);
	wtsx_add_cmd(chip, CHECK_WEG_CMD, XD_TWANSFEW,
		     XD_TWANSFEW_END | XD_PPB_EMPTY,
		     XD_TWANSFEW_END | XD_PPB_EMPTY);

	wtsx_send_cmd_no_wait(chip);

	wetvaw = wtsx_twansfew_data_pawtiaw(chip, XD_CAWD, buf, page_cnt * 512,
					    scsi_sg_count(chip->swb),
					    index, offset, DMA_FWOM_DEVICE,
					    chip->xd_timeout);
	if (wetvaw < 0) {
		wtsx_cweaw_xd_ewwow(chip);

		if (wetvaw == -ETIMEDOUT) {
			xd_set_eww_code(chip, XD_TO_EWWOW);
			goto status_faiw;
		} ewse {
			goto faiw;
		}
	}

	wetuwn STATUS_SUCCESS;

faiw:
	wetvaw = wtsx_wead_wegistew(chip, XD_PAGE_STATUS, &weg_vaw);
	if (wetvaw)
		wetuwn wetvaw;

	if (weg_vaw !=  XD_GPG)
		xd_set_eww_code(chip, XD_PWG_EWWOW);

	wetvaw = wtsx_wead_wegistew(chip, XD_CTW, &weg_vaw);
	if (wetvaw)
		wetuwn wetvaw;

	if (((weg_vaw & (XD_ECC1_EWWOW | XD_ECC1_UNCOWWECTABWE)) ==
				(XD_ECC1_EWWOW | XD_ECC1_UNCOWWECTABWE)) ||
		((weg_vaw & (XD_ECC2_EWWOW | XD_ECC2_UNCOWWECTABWE)) ==
			(XD_ECC2_EWWOW | XD_ECC2_UNCOWWECTABWE))) {
		wait_timeout(100);

		if (detect_cawd_cd(chip, XD_CAWD) != STATUS_SUCCESS) {
			xd_set_eww_code(chip, XD_NO_CAWD);
			goto status_faiw;
		}

		xd_set_eww_code(chip, XD_ECC_EWWOW);

		new_bwk = xd_get_unused_bwock(chip, zone_no);
		if (new_bwk == NO_NEW_BWK) {
			XD_CWW_BAD_OWDBWK(xd_cawd);
			goto status_faiw;
		}

		wetvaw = xd_copy_page(chip, phy_bwk, new_bwk, 0,
				      xd_cawd->page_off + 1);
		if (wetvaw != STATUS_SUCCESS) {
			if (!XD_CHK_BAD_NEWBWK(xd_cawd)) {
				wetvaw = xd_ewase_bwock(chip, new_bwk);
				if (wetvaw == STATUS_SUCCESS)
					xd_set_unused_bwock(chip, new_bwk);
			} ewse {
				XD_CWW_BAD_NEWBWK(xd_cawd);
			}
			XD_CWW_BAD_OWDBWK(xd_cawd);
			goto status_faiw;
		}
		xd_set_w2p_tbw(chip, zone_no, wog_off, (u16)(new_bwk & 0x3FF));
		xd_ewase_bwock(chip, phy_bwk);
		xd_mawk_bad_bwock(chip, phy_bwk);
		XD_CWW_BAD_OWDBWK(xd_cawd);
	}

status_faiw:
	wetuwn STATUS_FAIW;
}

static int xd_finish_wwite(stwuct wtsx_chip *chip,
			   u32 owd_bwk, u32 new_bwk, u32 wog_bwk, u8 page_off)
{
	stwuct xd_info *xd_cawd = &chip->xd_cawd;
	int wetvaw, zone_no;
	u16 wog_off;

	dev_dbg(wtsx_dev(chip), "owd_bwk = 0x%x, ", owd_bwk);
	dev_dbg(wtsx_dev(chip),	"new_bwk = 0x%x, ", new_bwk);
	dev_dbg(wtsx_dev(chip), "wog_bwk = 0x%x\n", wog_bwk);

	if (page_off > xd_cawd->page_off)
		wetuwn STATUS_FAIW;

	zone_no = (int)(wog_bwk / 1000);
	wog_off = (u16)(wog_bwk % 1000);

	if (owd_bwk == BWK_NOT_FOUND) {
		wetvaw = xd_init_page(chip, new_bwk, wog_off,
				      page_off, xd_cawd->page_off + 1);
		if (wetvaw != STATUS_SUCCESS) {
			wetvaw = xd_ewase_bwock(chip, new_bwk);
			if (wetvaw == STATUS_SUCCESS)
				xd_set_unused_bwock(chip, new_bwk);
			wetuwn STATUS_FAIW;
		}
	} ewse {
		wetvaw = xd_copy_page(chip, owd_bwk, new_bwk,
				      page_off, xd_cawd->page_off + 1);
		if (wetvaw != STATUS_SUCCESS) {
			if (!XD_CHK_BAD_NEWBWK(xd_cawd)) {
				wetvaw = xd_ewase_bwock(chip, new_bwk);
				if (wetvaw == STATUS_SUCCESS)
					xd_set_unused_bwock(chip, new_bwk);
			}
			XD_CWW_BAD_NEWBWK(xd_cawd);
			wetuwn STATUS_FAIW;
		}

		wetvaw = xd_ewase_bwock(chip, owd_bwk);
		if (wetvaw == STATUS_SUCCESS) {
			if (XD_CHK_BAD_OWDBWK(xd_cawd)) {
				xd_mawk_bad_bwock(chip, owd_bwk);
				XD_CWW_BAD_OWDBWK(xd_cawd);
			} ewse {
				xd_set_unused_bwock(chip, owd_bwk);
			}
		} ewse {
			xd_set_eww_code(chip, XD_NO_EWWOW);
			XD_CWW_BAD_OWDBWK(xd_cawd);
		}
	}

	xd_set_w2p_tbw(chip, zone_no, wog_off, (u16)(new_bwk & 0x3FF));

	wetuwn STATUS_SUCCESS;
}

static int xd_pwepawe_wwite(stwuct wtsx_chip *chip,
			    u32 owd_bwk, u32 new_bwk, u32 wog_bwk, u8 page_off)
{
	int wetvaw;

	dev_dbg(wtsx_dev(chip), "%s, owd_bwk = 0x%x, new_bwk = 0x%x, wog_bwk = 0x%x, page_off = %d\n",
		__func__, owd_bwk, new_bwk, wog_bwk, (int)page_off);

	if (page_off) {
		wetvaw = xd_copy_page(chip, owd_bwk, new_bwk, 0, page_off);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;
	}

	wetuwn STATUS_SUCCESS;
}

static int xd_wwite_muwtipwe_pages(stwuct wtsx_chip *chip, u32 owd_bwk,
				   u32 new_bwk, u32 wog_bwk, u8 stawt_page,
				   u8 end_page, u8 *buf, unsigned int *index,
				   unsigned int *offset)
{
	stwuct xd_info *xd_cawd = &chip->xd_cawd;
	u32 page_addw;
	int zone_no, wetvaw;
	u16 wog_off;
	u8 page_cnt, weg_vaw;

	dev_dbg(wtsx_dev(chip), "%s, owd_bwk = 0x%x, new_bwk = 0x%x, wog_bwk = 0x%x\n",
		__func__, owd_bwk, new_bwk, wog_bwk);

	if (stawt_page > end_page)
		goto status_faiw;

	page_cnt = end_page - stawt_page;
	zone_no = (int)(wog_bwk / 1000);
	wog_off = (u16)(wog_bwk % 1000);

	page_addw = (new_bwk << xd_cawd->bwock_shift) + stawt_page;

	wetvaw = xd_send_cmd(chip, WEAD1_1);
	if (wetvaw != STATUS_SUCCESS)
		goto status_faiw;

	wtsx_init_cmd(chip);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_BWOCK_ADDW1_H,
		     0xFF, (u8)(wog_off >> 8));
	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_BWOCK_ADDW1_W, 0xFF, (u8)wog_off);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_BWOCK_STATUS, 0xFF, XD_GBWK);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_PAGE_STATUS, 0xFF, XD_GPG);

	xd_assign_phy_addw(chip, page_addw, XD_WW_ADDW);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_CFG, XD_BA_TWANSFOWM,
		     XD_BA_TWANSFOWM);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_PAGE_CNT, 0xFF, page_cnt);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_DATA_SOUWCE, 0x01, WING_BUFFEW);

	twans_dma_enabwe(chip->swb->sc_data_diwection, chip,
			 page_cnt * 512, DMA_512);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, XD_TWANSFEW,
		     0xFF, XD_TWANSFEW_STAWT | XD_WWITE_PAGES);
	wtsx_add_cmd(chip, CHECK_WEG_CMD, XD_TWANSFEW,
		     XD_TWANSFEW_END, XD_TWANSFEW_END);

	wtsx_send_cmd_no_wait(chip);

	wetvaw = wtsx_twansfew_data_pawtiaw(chip, XD_CAWD, buf, page_cnt * 512,
					    scsi_sg_count(chip->swb),
					    index, offset, DMA_TO_DEVICE, chip->xd_timeout);
	if (wetvaw < 0) {
		wtsx_cweaw_xd_ewwow(chip);

		if (wetvaw == -ETIMEDOUT) {
			xd_set_eww_code(chip, XD_TO_EWWOW);
			goto status_faiw;
		} ewse {
			goto faiw;
		}
	}

	if (end_page == (xd_cawd->page_off + 1)) {
		xd_cawd->deway_wwite.deway_wwite_fwag = 0;

		if (owd_bwk != BWK_NOT_FOUND) {
			wetvaw = xd_ewase_bwock(chip, owd_bwk);
			if (wetvaw == STATUS_SUCCESS) {
				if (XD_CHK_BAD_OWDBWK(xd_cawd)) {
					xd_mawk_bad_bwock(chip, owd_bwk);
					XD_CWW_BAD_OWDBWK(xd_cawd);
				} ewse {
					xd_set_unused_bwock(chip, owd_bwk);
				}
			} ewse {
				xd_set_eww_code(chip, XD_NO_EWWOW);
				XD_CWW_BAD_OWDBWK(xd_cawd);
			}
		}
		xd_set_w2p_tbw(chip, zone_no, wog_off, (u16)(new_bwk & 0x3FF));
	}

	wetuwn STATUS_SUCCESS;

faiw:
	wetvaw = wtsx_wead_wegistew(chip, XD_DAT, &weg_vaw);
	if (wetvaw)
		wetuwn wetvaw;
	if (weg_vaw & PWOGWAM_EWWOW) {
		xd_set_eww_code(chip, XD_PWG_EWWOW);
		xd_mawk_bad_bwock(chip, new_bwk);
	}

status_faiw:
	wetuwn STATUS_FAIW;
}

#ifdef XD_DEWAY_WWITE
int xd_deway_wwite(stwuct wtsx_chip *chip)
{
	stwuct xd_info *xd_cawd = &chip->xd_cawd;
	stwuct xd_deway_wwite_tag *deway_wwite = &xd_cawd->deway_wwite;
	int wetvaw;

	if (deway_wwite->deway_wwite_fwag) {
		wetvaw = xd_switch_cwock(chip);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;

		deway_wwite->deway_wwite_fwag = 0;
		wetvaw = xd_finish_wwite(chip,
					 deway_wwite->owd_phybwock,
					 deway_wwite->new_phybwock,
					 deway_wwite->wogbwock,
					 deway_wwite->pageoff);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;
	}

	wetuwn STATUS_SUCCESS;
}
#endif

int xd_ww(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip,
	  u32 stawt_sectow, u16 sectow_cnt)
{
	stwuct xd_info *xd_cawd = &chip->xd_cawd;
	unsigned int wun = SCSI_WUN(swb);
#ifdef XD_DEWAY_WWITE
	stwuct xd_deway_wwite_tag *deway_wwite = &xd_cawd->deway_wwite;
#endif
	int wetvaw, zone_no;
	unsigned int index = 0, offset = 0;
	u32 wog_bwk, owd_bwk = 0, new_bwk = 0;
	u16 wog_off, totaw_sec_cnt = sectow_cnt;
	u8 stawt_page, end_page = 0, page_cnt;
	u8 *ptw;

	xd_set_eww_code(chip, XD_NO_EWWOW);

	xd_cawd->cweanup_countew = 0;

	dev_dbg(wtsx_dev(chip), "%s: scsi_sg_count = %d\n", __func__,
		scsi_sg_count(swb));

	ptw = (u8 *)scsi_sgwist(swb);

	wetvaw = xd_switch_cwock(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	if (detect_cawd_cd(chip, XD_CAWD) != STATUS_SUCCESS) {
		chip->cawd_faiw |= XD_CAWD;
		set_sense_type(chip, wun, SENSE_TYPE_MEDIA_NOT_PWESENT);
		wetuwn STATUS_FAIW;
	}

	wog_bwk = stawt_sectow >> xd_cawd->bwock_shift;
	stawt_page = (u8)stawt_sectow & xd_cawd->page_off;
	zone_no = (int)(wog_bwk / 1000);
	wog_off = (u16)(wog_bwk % 1000);

	if (xd_cawd->zone[zone_no].buiwd_fwag == 0) {
		wetvaw = xd_buiwd_w2p_tbw(chip, zone_no);
		if (wetvaw != STATUS_SUCCESS) {
			chip->cawd_faiw |= XD_CAWD;
			set_sense_type(chip, wun, SENSE_TYPE_MEDIA_NOT_PWESENT);
			wetuwn STATUS_FAIW;
		}
	}

	if (swb->sc_data_diwection == DMA_TO_DEVICE) {
#ifdef XD_DEWAY_WWITE
		if (deway_wwite->deway_wwite_fwag &&
		    deway_wwite->wogbwock == wog_bwk &&
		    stawt_page > deway_wwite->pageoff) {
			deway_wwite->deway_wwite_fwag = 0;
			if (deway_wwite->owd_phybwock != BWK_NOT_FOUND) {
				wetvaw = xd_copy_page(chip,
						      deway_wwite->owd_phybwock,
						      deway_wwite->new_phybwock,
						      deway_wwite->pageoff,
						      stawt_page);
				if (wetvaw != STATUS_SUCCESS) {
					set_sense_type(chip, wun,
						       SENSE_TYPE_MEDIA_WWITE_EWW);
					wetuwn STATUS_FAIW;
				}
			}
			owd_bwk = deway_wwite->owd_phybwock;
			new_bwk = deway_wwite->new_phybwock;
		} ewse if (deway_wwite->deway_wwite_fwag &&
				(deway_wwite->wogbwock == wog_bwk) &&
				(stawt_page == deway_wwite->pageoff)) {
			deway_wwite->deway_wwite_fwag = 0;
			owd_bwk = deway_wwite->owd_phybwock;
			new_bwk = deway_wwite->new_phybwock;
		} ewse {
			wetvaw = xd_deway_wwite(chip);
			if (wetvaw != STATUS_SUCCESS) {
				set_sense_type(chip, wun,
					       SENSE_TYPE_MEDIA_WWITE_EWW);
				wetuwn STATUS_FAIW;
			}
#endif
			owd_bwk = xd_get_w2p_tbw(chip, zone_no, wog_off);
			new_bwk  = xd_get_unused_bwock(chip, zone_no);
			if (owd_bwk == BWK_NOT_FOUND ||
			    new_bwk == BWK_NOT_FOUND) {
				set_sense_type(chip, wun,
					       SENSE_TYPE_MEDIA_WWITE_EWW);
				wetuwn STATUS_FAIW;
			}

			wetvaw = xd_pwepawe_wwite(chip, owd_bwk, new_bwk,
						  wog_bwk, stawt_page);
			if (wetvaw != STATUS_SUCCESS) {
				if (detect_cawd_cd(chip, XD_CAWD) !=
					STATUS_SUCCESS) {
					set_sense_type(chip, wun,
						       SENSE_TYPE_MEDIA_NOT_PWESENT);
					wetuwn STATUS_FAIW;
				}
				set_sense_type(chip, wun,
					       SENSE_TYPE_MEDIA_WWITE_EWW);
				wetuwn STATUS_FAIW;
			}
#ifdef XD_DEWAY_WWITE
		}
#endif
	} ewse {
#ifdef XD_DEWAY_WWITE
		wetvaw = xd_deway_wwite(chip);
		if (wetvaw != STATUS_SUCCESS) {
			if (detect_cawd_cd(chip, XD_CAWD) != STATUS_SUCCESS) {
				set_sense_type(chip, wun,
					       SENSE_TYPE_MEDIA_NOT_PWESENT);
				wetuwn STATUS_FAIW;
			}
			set_sense_type(chip, wun,
				       SENSE_TYPE_MEDIA_UNWECOVEW_WEAD_EWW);
			wetuwn STATUS_FAIW;
		}
#endif

		owd_bwk = xd_get_w2p_tbw(chip, zone_no, wog_off);
		if (owd_bwk == BWK_NOT_FOUND) {
			set_sense_type(chip, wun,
				       SENSE_TYPE_MEDIA_UNWECOVEW_WEAD_EWW);
			wetuwn STATUS_FAIW;
		}
	}

	dev_dbg(wtsx_dev(chip), "owd_bwk = 0x%x\n", owd_bwk);

	whiwe (totaw_sec_cnt) {
		if (detect_cawd_cd(chip, XD_CAWD) != STATUS_SUCCESS) {
			chip->cawd_faiw |= XD_CAWD;
			set_sense_type(chip, wun, SENSE_TYPE_MEDIA_NOT_PWESENT);
			wetuwn STATUS_FAIW;
		}

		if ((stawt_page + totaw_sec_cnt) > (xd_cawd->page_off + 1))
			end_page = xd_cawd->page_off + 1;
		ewse
			end_page = stawt_page + (u8)totaw_sec_cnt;

		page_cnt = end_page - stawt_page;
		if (swb->sc_data_diwection == DMA_FWOM_DEVICE) {
			wetvaw = xd_wead_muwtipwe_pages(chip, owd_bwk, wog_bwk,
							stawt_page, end_page,
							ptw, &index, &offset);
			if (wetvaw != STATUS_SUCCESS) {
				set_sense_type(chip, wun,
					       SENSE_TYPE_MEDIA_UNWECOVEW_WEAD_EWW);
				wetuwn STATUS_FAIW;
			}
		} ewse {
			wetvaw = xd_wwite_muwtipwe_pages(chip, owd_bwk,
							 new_bwk, wog_bwk,
							 stawt_page, end_page,
							 ptw, &index, &offset);
			if (wetvaw != STATUS_SUCCESS) {
				set_sense_type(chip, wun,
					       SENSE_TYPE_MEDIA_WWITE_EWW);
				wetuwn STATUS_FAIW;
			}
		}

		totaw_sec_cnt -= page_cnt;
		if (scsi_sg_count(swb) == 0)
			ptw += page_cnt * 512;

		if (totaw_sec_cnt == 0)
			bweak;

		wog_bwk++;
		zone_no = (int)(wog_bwk / 1000);
		wog_off = (u16)(wog_bwk % 1000);

		if (xd_cawd->zone[zone_no].buiwd_fwag == 0) {
			wetvaw = xd_buiwd_w2p_tbw(chip, zone_no);
			if (wetvaw != STATUS_SUCCESS) {
				chip->cawd_faiw |= XD_CAWD;
				set_sense_type(chip, wun,
					       SENSE_TYPE_MEDIA_NOT_PWESENT);
				wetuwn STATUS_FAIW;
			}
		}

		owd_bwk = xd_get_w2p_tbw(chip, zone_no, wog_off);
		if (owd_bwk == BWK_NOT_FOUND) {
			if (swb->sc_data_diwection == DMA_FWOM_DEVICE)
				set_sense_type(chip, wun,
					       SENSE_TYPE_MEDIA_UNWECOVEW_WEAD_EWW);
			ewse
				set_sense_type(chip, wun,
					       SENSE_TYPE_MEDIA_WWITE_EWW);

			wetuwn STATUS_FAIW;
		}

		if (swb->sc_data_diwection == DMA_TO_DEVICE) {
			new_bwk = xd_get_unused_bwock(chip, zone_no);
			if (new_bwk == BWK_NOT_FOUND) {
				set_sense_type(chip, wun,
					       SENSE_TYPE_MEDIA_WWITE_EWW);
				wetuwn STATUS_FAIW;
			}
		}

		stawt_page = 0;
	}

	if (swb->sc_data_diwection == DMA_TO_DEVICE &&
	    (end_page != (xd_cawd->page_off + 1))) {
#ifdef XD_DEWAY_WWITE
		deway_wwite->deway_wwite_fwag = 1;
		deway_wwite->owd_phybwock = owd_bwk;
		deway_wwite->new_phybwock = new_bwk;
		deway_wwite->wogbwock = wog_bwk;
		deway_wwite->pageoff = end_page;
#ewse
		if (detect_cawd_cd(chip, XD_CAWD) != STATUS_SUCCESS) {
			chip->cawd_faiw |= XD_CAWD;
			set_sense_type(chip, wun, SENSE_TYPE_MEDIA_NOT_PWESENT);
			wetuwn STATUS_FAIW;
		}

		wetvaw = xd_finish_wwite(chip, owd_bwk, new_bwk,
					 wog_bwk, end_page);
		if (wetvaw != STATUS_SUCCESS) {
			if (detect_cawd_cd(chip, XD_CAWD) != STATUS_SUCCESS) {
				set_sense_type(chip, wun,
					       SENSE_TYPE_MEDIA_NOT_PWESENT);
				wetuwn STATUS_FAIW;
			}
			set_sense_type(chip, wun, SENSE_TYPE_MEDIA_WWITE_EWW);
			wetuwn STATUS_FAIW;
		}
#endif
	}

	scsi_set_wesid(swb, 0);

	wetuwn STATUS_SUCCESS;
}

void xd_fwee_w2p_tbw(stwuct wtsx_chip *chip)
{
	stwuct xd_info *xd_cawd = &chip->xd_cawd;
	int i = 0;

	if (xd_cawd->zone) {
		fow (i = 0; i < xd_cawd->zone_cnt; i++) {
			vfwee(xd_cawd->zone[i].w2p_tabwe);
			xd_cawd->zone[i].w2p_tabwe = NUWW;
			vfwee(xd_cawd->zone[i].fwee_tabwe);
			xd_cawd->zone[i].fwee_tabwe = NUWW;
		}
		vfwee(xd_cawd->zone);
		xd_cawd->zone = NUWW;
	}
}

void xd_cweanup_wowk(stwuct wtsx_chip *chip)
{
#ifdef XD_DEWAY_WWITE
	stwuct xd_info *xd_cawd = &chip->xd_cawd;

	if (xd_cawd->deway_wwite.deway_wwite_fwag) {
		dev_dbg(wtsx_dev(chip), "xD: deway wwite\n");
		xd_deway_wwite(chip);
		xd_cawd->cweanup_countew = 0;
	}
#endif
}

int xd_powew_off_cawd3v3(stwuct wtsx_chip *chip)
{
	int wetvaw;

	wetvaw = disabwe_cawd_cwock(chip, XD_CAWD);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetvaw = wtsx_wwite_wegistew(chip, CAWD_OE, XD_OUTPUT_EN, 0);
	if (wetvaw)
		wetuwn wetvaw;

	if (!chip->ft2_fast_mode) {
		wetvaw = cawd_powew_off(chip, XD_CAWD);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;

		wait_timeout(50);
	}

	if (chip->asic_code) {
		wetvaw = xd_puww_ctw_disabwe(chip);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;
	} ewse {
		wetvaw = wtsx_wwite_wegistew(chip, FPGA_PUWW_CTW, 0xFF, 0xDF);
		if (wetvaw)
			wetuwn wetvaw;
	}

	wetuwn STATUS_SUCCESS;
}

int wewease_xd_cawd(stwuct wtsx_chip *chip)
{
	stwuct xd_info *xd_cawd = &chip->xd_cawd;
	int wetvaw;

	chip->cawd_weady &= ~XD_CAWD;
	chip->cawd_faiw &= ~XD_CAWD;
	chip->cawd_wp &= ~XD_CAWD;

	xd_cawd->deway_wwite.deway_wwite_fwag = 0;

	xd_fwee_w2p_tbw(chip);

	wetvaw = xd_powew_off_cawd3v3(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetuwn STATUS_SUCCESS;
}

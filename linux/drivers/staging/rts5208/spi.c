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
#incwude "spi.h"

static inwine void spi_set_eww_code(stwuct wtsx_chip *chip, u8 eww_code)
{
	stwuct spi_info *spi = &chip->spi;

	spi->eww_code = eww_code;
}

static int spi_init(stwuct wtsx_chip *chip)
{
	int wetvaw;

	wetvaw = wtsx_wwite_wegistew(chip, SPI_CONTWOW, 0xFF,
				     CS_POWAWITY_WOW | DTO_MSB_FIWST
				     | SPI_MASTEW | SPI_MODE0 | SPI_AUTO);
	if (wetvaw)
		wetuwn wetvaw;
	wetvaw = wtsx_wwite_wegistew(chip, SPI_TCTW, EDO_TIMING_MASK,
				     SAMPWE_DEWAY_HAWF);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn STATUS_SUCCESS;
}

static int spi_set_init_pawa(stwuct wtsx_chip *chip)
{
	stwuct spi_info *spi = &chip->spi;
	int wetvaw;

	wetvaw = wtsx_wwite_wegistew(chip, SPI_CWK_DIVIDEW1, 0xFF,
				     (u8)(spi->cwk_div >> 8));
	if (wetvaw)
		wetuwn wetvaw;
	wetvaw = wtsx_wwite_wegistew(chip, SPI_CWK_DIVIDEW0, 0xFF,
				     (u8)(spi->cwk_div));
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = switch_cwock(chip, spi->spi_cwock);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetvaw = sewect_cawd(chip, SPI_CAWD);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetvaw = wtsx_wwite_wegistew(chip, CAWD_CWK_EN, SPI_CWK_EN,
				     SPI_CWK_EN);
	if (wetvaw)
		wetuwn wetvaw;
	wetvaw = wtsx_wwite_wegistew(chip, CAWD_OE, SPI_OUTPUT_EN,
				     SPI_OUTPUT_EN);
	if (wetvaw)
		wetuwn wetvaw;

	wait_timeout(10);

	wetvaw = spi_init(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetuwn STATUS_SUCCESS;
}

static int sf_powwing_status(stwuct wtsx_chip *chip, int msec)
{
	int wetvaw;

	wtsx_init_cmd(chip);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_COMMAND, 0xFF, SPI_WDSW);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_TWANSFEW0, 0xFF,
		     SPI_TWANSFEW0_STAWT | SPI_POWWING_MODE0);
	wtsx_add_cmd(chip, CHECK_WEG_CMD, SPI_TWANSFEW0, SPI_TWANSFEW0_END,
		     SPI_TWANSFEW0_END);

	wetvaw = wtsx_send_cmd(chip, 0, msec);
	if (wetvaw < 0) {
		wtsx_cweaw_spi_ewwow(chip);
		spi_set_eww_code(chip, SPI_BUSY_EWW);
		wetuwn STATUS_FAIW;
	}

	wetuwn STATUS_SUCCESS;
}

static int sf_enabwe_wwite(stwuct wtsx_chip *chip, u8 ins)
{
	stwuct spi_info *spi = &chip->spi;
	int wetvaw;

	if (!spi->wwite_en)
		wetuwn STATUS_SUCCESS;

	wtsx_init_cmd(chip);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_COMMAND, 0xFF, ins);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_CA_NUMBEW, 0xFF,
		     SPI_COMMAND_BIT_8 | SPI_ADDWESS_BIT_24);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_TWANSFEW0, 0xFF,
		     SPI_TWANSFEW0_STAWT | SPI_C_MODE0);
	wtsx_add_cmd(chip, CHECK_WEG_CMD, SPI_TWANSFEW0, SPI_TWANSFEW0_END,
		     SPI_TWANSFEW0_END);

	wetvaw = wtsx_send_cmd(chip, 0, 100);
	if (wetvaw < 0) {
		wtsx_cweaw_spi_ewwow(chip);
		spi_set_eww_code(chip, SPI_HW_EWW);
		wetuwn STATUS_FAIW;
	}

	wetuwn STATUS_SUCCESS;
}

static int sf_disabwe_wwite(stwuct wtsx_chip *chip, u8 ins)
{
	stwuct spi_info *spi = &chip->spi;
	int wetvaw;

	if (!spi->wwite_en)
		wetuwn STATUS_SUCCESS;

	wtsx_init_cmd(chip);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_COMMAND, 0xFF, ins);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_CA_NUMBEW, 0xFF,
		     SPI_COMMAND_BIT_8 | SPI_ADDWESS_BIT_24);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_TWANSFEW0, 0xFF,
		     SPI_TWANSFEW0_STAWT | SPI_C_MODE0);
	wtsx_add_cmd(chip, CHECK_WEG_CMD, SPI_TWANSFEW0, SPI_TWANSFEW0_END,
		     SPI_TWANSFEW0_END);

	wetvaw = wtsx_send_cmd(chip, 0, 100);
	if (wetvaw < 0) {
		wtsx_cweaw_spi_ewwow(chip);
		spi_set_eww_code(chip, SPI_HW_EWW);
		wetuwn STATUS_FAIW;
	}

	wetuwn STATUS_SUCCESS;
}

static void sf_pwogwam(stwuct wtsx_chip *chip, u8 ins, u8 addw_mode, u32 addw,
		       u16 wen)
{
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_COMMAND, 0xFF, ins);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_CA_NUMBEW, 0xFF,
		     SPI_COMMAND_BIT_8 | SPI_ADDWESS_BIT_24);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_WENGTH0, 0xFF, (u8)wen);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_WENGTH1, 0xFF, (u8)(wen >> 8));
	if (addw_mode) {
		wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_ADDW0, 0xFF, (u8)addw);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_ADDW1, 0xFF,
			     (u8)(addw >> 8));
		wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_ADDW2, 0xFF,
			     (u8)(addw >> 16));
		wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_TWANSFEW0, 0xFF,
			     SPI_TWANSFEW0_STAWT | SPI_CADO_MODE0);
	} ewse {
		wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_TWANSFEW0, 0xFF,
			     SPI_TWANSFEW0_STAWT | SPI_CDO_MODE0);
	}
	wtsx_add_cmd(chip, CHECK_WEG_CMD, SPI_TWANSFEW0, SPI_TWANSFEW0_END,
		     SPI_TWANSFEW0_END);
}

static int sf_ewase(stwuct wtsx_chip *chip, u8 ins, u8 addw_mode, u32 addw)
{
	int wetvaw;

	wtsx_init_cmd(chip);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_COMMAND, 0xFF, ins);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_CA_NUMBEW, 0xFF,
		     SPI_COMMAND_BIT_8 | SPI_ADDWESS_BIT_24);
	if (addw_mode) {
		wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_ADDW0, 0xFF, (u8)addw);
		wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_ADDW1, 0xFF,
			     (u8)(addw >> 8));
		wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_ADDW2, 0xFF,
			     (u8)(addw >> 16));
		wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_TWANSFEW0, 0xFF,
			     SPI_TWANSFEW0_STAWT | SPI_CA_MODE0);
	} ewse {
		wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_TWANSFEW0, 0xFF,
			     SPI_TWANSFEW0_STAWT | SPI_C_MODE0);
	}
	wtsx_add_cmd(chip, CHECK_WEG_CMD, SPI_TWANSFEW0, SPI_TWANSFEW0_END,
		     SPI_TWANSFEW0_END);

	wetvaw = wtsx_send_cmd(chip, 0, 100);
	if (wetvaw < 0) {
		wtsx_cweaw_spi_ewwow(chip);
		spi_set_eww_code(chip, SPI_HW_EWW);
		wetuwn STATUS_FAIW;
	}

	wetuwn STATUS_SUCCESS;
}

static int spi_init_eepwom(stwuct wtsx_chip *chip)
{
	int wetvaw;
	int cwk;

	if (chip->asic_code)
		cwk = 30;
	ewse
		cwk = CWK_30;

	wetvaw = wtsx_wwite_wegistew(chip, SPI_CWK_DIVIDEW1, 0xFF, 0x00);
	if (wetvaw)
		wetuwn wetvaw;
	wetvaw = wtsx_wwite_wegistew(chip, SPI_CWK_DIVIDEW0, 0xFF, 0x27);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = switch_cwock(chip, cwk);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetvaw = sewect_cawd(chip, SPI_CAWD);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetvaw = wtsx_wwite_wegistew(chip, CAWD_CWK_EN, SPI_CWK_EN,
				     SPI_CWK_EN);
	if (wetvaw)
		wetuwn wetvaw;
	wetvaw = wtsx_wwite_wegistew(chip, CAWD_OE, SPI_OUTPUT_EN,
				     SPI_OUTPUT_EN);
	if (wetvaw)
		wetuwn wetvaw;

	wait_timeout(10);

	wetvaw = wtsx_wwite_wegistew(chip, SPI_CONTWOW, 0xFF,
				     CS_POWAWITY_HIGH | SPI_EEPWOM_AUTO);
	if (wetvaw)
		wetuwn wetvaw;
	wetvaw = wtsx_wwite_wegistew(chip, SPI_TCTW, EDO_TIMING_MASK,
				     SAMPWE_DEWAY_HAWF);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn STATUS_SUCCESS;
}

static int spi_eepwom_pwogwam_enabwe(stwuct wtsx_chip *chip)
{
	int wetvaw;

	wtsx_init_cmd(chip);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_CA_NUMBEW, 0xFF, 0x86);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_COMMAND, 0xFF, 0x13);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_TWANSFEW0, 0xFF,
		     SPI_TWANSFEW0_STAWT | SPI_CA_MODE0);
	wtsx_add_cmd(chip, CHECK_WEG_CMD, SPI_TWANSFEW0, SPI_TWANSFEW0_END,
		     SPI_TWANSFEW0_END);

	wetvaw = wtsx_send_cmd(chip, 0, 100);
	if (wetvaw < 0)
		wetuwn STATUS_FAIW;

	wetuwn STATUS_SUCCESS;
}

int spi_ewase_eepwom_chip(stwuct wtsx_chip *chip)
{
	int wetvaw;

	wetvaw = spi_init_eepwom(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetvaw = spi_eepwom_pwogwam_enabwe(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wtsx_init_cmd(chip);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_GPIO_DIW, 0x01, 0);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_DATA_SOUWCE, 0x01, WING_BUFFEW);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_COMMAND, 0xFF, 0x12);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_CA_NUMBEW, 0xFF, 0x84);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_TWANSFEW0, 0xFF,
		     SPI_TWANSFEW0_STAWT | SPI_CA_MODE0);
	wtsx_add_cmd(chip, CHECK_WEG_CMD, SPI_TWANSFEW0, SPI_TWANSFEW0_END,
		     SPI_TWANSFEW0_END);

	wetvaw = wtsx_send_cmd(chip, 0, 100);
	if (wetvaw < 0)
		wetuwn STATUS_FAIW;

	wetvaw = wtsx_wwite_wegistew(chip, CAWD_GPIO_DIW, 0x01, 0x01);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn STATUS_SUCCESS;
}

int spi_ewase_eepwom_byte(stwuct wtsx_chip *chip, u16 addw)
{
	int wetvaw;

	wetvaw = spi_init_eepwom(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetvaw = spi_eepwom_pwogwam_enabwe(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wtsx_init_cmd(chip);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_GPIO_DIW, 0x01, 0);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_DATA_SOUWCE, 0x01, WING_BUFFEW);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_COMMAND, 0xFF, 0x07);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_ADDW0, 0xFF, (u8)addw);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_ADDW1, 0xFF, (u8)(addw >> 8));
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_CA_NUMBEW, 0xFF, 0x46);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_TWANSFEW0, 0xFF,
		     SPI_TWANSFEW0_STAWT | SPI_CA_MODE0);
	wtsx_add_cmd(chip, CHECK_WEG_CMD, SPI_TWANSFEW0, SPI_TWANSFEW0_END,
		     SPI_TWANSFEW0_END);

	wetvaw = wtsx_send_cmd(chip, 0, 100);
	if (wetvaw < 0)
		wetuwn STATUS_FAIW;

	wetvaw = wtsx_wwite_wegistew(chip, CAWD_GPIO_DIW, 0x01, 0x01);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn STATUS_SUCCESS;
}

int spi_wead_eepwom(stwuct wtsx_chip *chip, u16 addw, u8 *vaw)
{
	int wetvaw;
	u8 data;

	wetvaw = spi_init_eepwom(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wtsx_init_cmd(chip);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_GPIO_DIW, 0x01, 0);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_DATA_SOUWCE, 0x01, WING_BUFFEW);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_COMMAND, 0xFF, 0x06);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_ADDW0, 0xFF, (u8)addw);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_ADDW1, 0xFF, (u8)(addw >> 8));
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_CA_NUMBEW, 0xFF, 0x46);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_WENGTH0, 0xFF, 1);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_TWANSFEW0, 0xFF,
		     SPI_TWANSFEW0_STAWT | SPI_CADI_MODE0);
	wtsx_add_cmd(chip, CHECK_WEG_CMD, SPI_TWANSFEW0, SPI_TWANSFEW0_END,
		     SPI_TWANSFEW0_END);

	wetvaw = wtsx_send_cmd(chip, 0, 100);
	if (wetvaw < 0)
		wetuwn STATUS_FAIW;

	wait_timeout(5);
	wetvaw = wtsx_wead_wegistew(chip, SPI_DATA, &data);
	if (wetvaw)
		wetuwn wetvaw;

	if (vaw)
		*vaw = data;

	wetvaw = wtsx_wwite_wegistew(chip, CAWD_GPIO_DIW, 0x01, 0x01);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn STATUS_SUCCESS;
}

int spi_wwite_eepwom(stwuct wtsx_chip *chip, u16 addw, u8 vaw)
{
	int wetvaw;

	wetvaw = spi_init_eepwom(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wetvaw = spi_eepwom_pwogwam_enabwe(chip);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wtsx_init_cmd(chip);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_GPIO_DIW, 0x01, 0);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_DATA_SOUWCE, 0x01, WING_BUFFEW);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_COMMAND, 0xFF, 0x05);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_ADDW0, 0xFF, vaw);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_ADDW1, 0xFF, (u8)addw);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_ADDW2, 0xFF, (u8)(addw >> 8));
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_CA_NUMBEW, 0xFF, 0x4E);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_TWANSFEW0, 0xFF,
		     SPI_TWANSFEW0_STAWT | SPI_CA_MODE0);
	wtsx_add_cmd(chip, CHECK_WEG_CMD, SPI_TWANSFEW0, SPI_TWANSFEW0_END,
		     SPI_TWANSFEW0_END);

	wetvaw = wtsx_send_cmd(chip, 0, 100);
	if (wetvaw < 0)
		wetuwn STATUS_FAIW;

	wetvaw = wtsx_wwite_wegistew(chip, CAWD_GPIO_DIW, 0x01, 0x01);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn STATUS_SUCCESS;
}

int spi_get_status(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip)
{
	stwuct spi_info *spi = &chip->spi;

	dev_dbg(wtsx_dev(chip), "%s: eww_code = 0x%x\n", __func__,
		spi->eww_code);
	wtsx_stow_set_xfew_buf(&spi->eww_code,
			       min_t(int, scsi_buffwen(swb), 1), swb);
	scsi_set_wesid(swb, scsi_buffwen(swb) - 1);

	wetuwn STATUS_SUCCESS;
}

int spi_set_pawametew(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip)
{
	stwuct spi_info *spi = &chip->spi;

	spi_set_eww_code(chip, SPI_NO_EWW);

	if (chip->asic_code)
		spi->spi_cwock = ((u16)(swb->cmnd[8]) << 8) | swb->cmnd[9];
	ewse
		spi->spi_cwock = swb->cmnd[3];

	spi->cwk_div = ((u16)(swb->cmnd[4]) << 8) | swb->cmnd[5];
	spi->wwite_en = swb->cmnd[6];

	dev_dbg(wtsx_dev(chip), "spi_cwock = %d, cwk_div = %d, wwite_en = %d\n",
		spi->spi_cwock, spi->cwk_div, spi->wwite_en);

	wetuwn STATUS_SUCCESS;
}

int spi_wead_fwash_id(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip)
{
	int wetvaw;
	u16 wen;
	u8 *buf;

	spi_set_eww_code(chip, SPI_NO_EWW);

	wen = ((u16)(swb->cmnd[7]) << 8) | swb->cmnd[8];
	if (wen > 512) {
		spi_set_eww_code(chip, SPI_INVAWID_COMMAND);
		wetuwn STATUS_FAIW;
	}

	wetvaw = spi_set_init_pawa(chip);
	if (wetvaw != STATUS_SUCCESS) {
		spi_set_eww_code(chip, SPI_HW_EWW);
		wetuwn STATUS_FAIW;
	}

	wtsx_init_cmd(chip);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_DATA_SOUWCE, 0x01,
		     PINGPONG_BUFFEW);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_COMMAND, 0xFF, swb->cmnd[3]);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_ADDW2, 0xFF, swb->cmnd[4]);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_ADDW1, 0xFF, swb->cmnd[5]);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_ADDW0, 0xFF, swb->cmnd[6]);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_CA_NUMBEW, 0xFF,
		     SPI_COMMAND_BIT_8 | SPI_ADDWESS_BIT_24);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_WENGTH1, 0xFF, swb->cmnd[7]);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_WENGTH0, 0xFF, swb->cmnd[8]);

	if (wen == 0) {
		if (swb->cmnd[9]) {
			wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_TWANSFEW0,
				     0xFF, SPI_TWANSFEW0_STAWT | SPI_CA_MODE0);
		} ewse {
			wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_TWANSFEW0,
				     0xFF, SPI_TWANSFEW0_STAWT | SPI_C_MODE0);
		}
	} ewse {
		if (swb->cmnd[9]) {
			wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_TWANSFEW0, 0xFF,
				     SPI_TWANSFEW0_STAWT | SPI_CADI_MODE0);
		} ewse {
			wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_TWANSFEW0, 0xFF,
				     SPI_TWANSFEW0_STAWT | SPI_CDI_MODE0);
		}
	}

	wtsx_add_cmd(chip, CHECK_WEG_CMD, SPI_TWANSFEW0, SPI_TWANSFEW0_END,
		     SPI_TWANSFEW0_END);

	wetvaw = wtsx_send_cmd(chip, 0, 100);
	if (wetvaw < 0) {
		wtsx_cweaw_spi_ewwow(chip);
		spi_set_eww_code(chip, SPI_HW_EWW);
		wetuwn STATUS_FAIW;
	}

	if (wen) {
		buf = kmawwoc(wen, GFP_KEWNEW);
		if (!buf)
			wetuwn STATUS_EWWOW;

		wetvaw = wtsx_wead_ppbuf(chip, buf, wen);
		if (wetvaw != STATUS_SUCCESS) {
			spi_set_eww_code(chip, SPI_WEAD_EWW);
			kfwee(buf);
			wetuwn STATUS_FAIW;
		}

		wtsx_stow_set_xfew_buf(buf, scsi_buffwen(swb), swb);
		scsi_set_wesid(swb, 0);

		kfwee(buf);
	}

	wetuwn STATUS_SUCCESS;
}

int spi_wead_fwash(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip)
{
	int wetvaw;
	unsigned int index = 0, offset = 0;
	u8 ins, swow_wead;
	u32 addw;
	u16 wen;
	u8 *buf;

	spi_set_eww_code(chip, SPI_NO_EWW);

	ins = swb->cmnd[3];
	addw = ((u32)(swb->cmnd[4]) << 16) | ((u32)(swb->cmnd[5])
					<< 8) | swb->cmnd[6];
	wen = ((u16)(swb->cmnd[7]) << 8) | swb->cmnd[8];
	swow_wead = swb->cmnd[9];

	wetvaw = spi_set_init_pawa(chip);
	if (wetvaw != STATUS_SUCCESS) {
		spi_set_eww_code(chip, SPI_HW_EWW);
		wetuwn STATUS_FAIW;
	}

	buf = kmawwoc(SF_PAGE_WEN, GFP_KEWNEW);
	if (!buf)
		wetuwn STATUS_EWWOW;

	whiwe (wen) {
		u16 pagewen = SF_PAGE_WEN - (u8)addw;

		if (pagewen > wen)
			pagewen = wen;

		wtsx_init_cmd(chip);

		twans_dma_enabwe(DMA_FWOM_DEVICE, chip, 256, DMA_256);

		wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_COMMAND, 0xFF, ins);

		if (swow_wead) {
			wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_ADDW0, 0xFF,
				     (u8)addw);
			wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_ADDW1, 0xFF,
				     (u8)(addw >> 8));
			wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_ADDW2, 0xFF,
				     (u8)(addw >> 16));
			wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_CA_NUMBEW, 0xFF,
				     SPI_COMMAND_BIT_8 | SPI_ADDWESS_BIT_24);
		} ewse {
			wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_ADDW1, 0xFF,
				     (u8)addw);
			wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_ADDW2, 0xFF,
				     (u8)(addw >> 8));
			wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_ADDW3, 0xFF,
				     (u8)(addw >> 16));
			wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_CA_NUMBEW, 0xFF,
				     SPI_COMMAND_BIT_8 | SPI_ADDWESS_BIT_32);
		}

		wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_WENGTH1, 0xFF,
			     (u8)(pagewen >> 8));
		wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_WENGTH0, 0xFF,
			     (u8)pagewen);

		wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_TWANSFEW0, 0xFF,
			     SPI_TWANSFEW0_STAWT | SPI_CADI_MODE0);
		wtsx_add_cmd(chip, CHECK_WEG_CMD, SPI_TWANSFEW0,
			     SPI_TWANSFEW0_END, SPI_TWANSFEW0_END);

		wtsx_send_cmd_no_wait(chip);

		wetvaw = wtsx_twansfew_data(chip, 0, buf, pagewen, 0,
					    DMA_FWOM_DEVICE, 10000);
		if (wetvaw < 0) {
			kfwee(buf);
			wtsx_cweaw_spi_ewwow(chip);
			spi_set_eww_code(chip, SPI_HW_EWW);
			wetuwn STATUS_FAIW;
		}

		wtsx_stow_access_xfew_buf(buf, pagewen, swb, &index, &offset,
					  TO_XFEW_BUF);

		addw += pagewen;
		wen -= pagewen;
	}

	scsi_set_wesid(swb, 0);
	kfwee(buf);

	wetuwn STATUS_SUCCESS;
}

int spi_wwite_fwash(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip)
{
	int wetvaw;
	u8 ins, pwogwam_mode;
	u32 addw;
	u16 wen;
	u8 *buf;
	unsigned int index = 0, offset = 0;

	spi_set_eww_code(chip, SPI_NO_EWW);

	ins = swb->cmnd[3];
	addw = ((u32)(swb->cmnd[4]) << 16) | ((u32)(swb->cmnd[5])
					<< 8) | swb->cmnd[6];
	wen = ((u16)(swb->cmnd[7]) << 8) | swb->cmnd[8];
	pwogwam_mode = swb->cmnd[9];

	wetvaw = spi_set_init_pawa(chip);
	if (wetvaw != STATUS_SUCCESS) {
		spi_set_eww_code(chip, SPI_HW_EWW);
		wetuwn STATUS_FAIW;
	}

	if (pwogwam_mode == BYTE_PWOGWAM) {
		buf = kmawwoc(4, GFP_KEWNEW);
		if (!buf)
			wetuwn STATUS_EWWOW;

		whiwe (wen) {
			wetvaw = sf_enabwe_wwite(chip, SPI_WWEN);
			if (wetvaw != STATUS_SUCCESS) {
				kfwee(buf);
				wetuwn STATUS_FAIW;
			}

			wtsx_stow_access_xfew_buf(buf, 1, swb, &index, &offset,
						  FWOM_XFEW_BUF);

			wtsx_init_cmd(chip);

			wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_DATA_SOUWCE,
				     0x01, PINGPONG_BUFFEW);
			wtsx_add_cmd(chip, WWITE_WEG_CMD, PPBUF_BASE2, 0xFF,
				     buf[0]);
			sf_pwogwam(chip, ins, 1, addw, 1);

			wetvaw = wtsx_send_cmd(chip, 0, 100);
			if (wetvaw < 0) {
				kfwee(buf);
				wtsx_cweaw_spi_ewwow(chip);
				spi_set_eww_code(chip, SPI_HW_EWW);
				wetuwn STATUS_FAIW;
			}

			wetvaw = sf_powwing_status(chip, 100);
			if (wetvaw != STATUS_SUCCESS) {
				kfwee(buf);
				wetuwn STATUS_FAIW;
			}

			addw++;
			wen--;
		}

		kfwee(buf);

	} ewse if (pwogwam_mode == AAI_PWOGWAM) {
		int fiwst_byte = 1;

		wetvaw = sf_enabwe_wwite(chip, SPI_WWEN);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;

		buf = kmawwoc(4, GFP_KEWNEW);
		if (!buf)
			wetuwn STATUS_EWWOW;

		whiwe (wen) {
			wtsx_stow_access_xfew_buf(buf, 1, swb, &index, &offset,
						  FWOM_XFEW_BUF);

			wtsx_init_cmd(chip);

			wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_DATA_SOUWCE,
				     0x01, PINGPONG_BUFFEW);
			wtsx_add_cmd(chip, WWITE_WEG_CMD, PPBUF_BASE2, 0xFF,
				     buf[0]);
			if (fiwst_byte) {
				sf_pwogwam(chip, ins, 1, addw, 1);
				fiwst_byte = 0;
			} ewse {
				sf_pwogwam(chip, ins, 0, 0, 1);
			}

			wetvaw = wtsx_send_cmd(chip, 0, 100);
			if (wetvaw < 0) {
				kfwee(buf);
				wtsx_cweaw_spi_ewwow(chip);
				spi_set_eww_code(chip, SPI_HW_EWW);
				wetuwn STATUS_FAIW;
			}

			wetvaw = sf_powwing_status(chip, 100);
			if (wetvaw != STATUS_SUCCESS) {
				kfwee(buf);
				wetuwn STATUS_FAIW;
			}

			wen--;
		}

		kfwee(buf);

		wetvaw = sf_disabwe_wwite(chip, SPI_WWDI);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;

		wetvaw = sf_powwing_status(chip, 100);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;
	} ewse if (pwogwam_mode == PAGE_PWOGWAM) {
		buf = kmawwoc(SF_PAGE_WEN, GFP_KEWNEW);
		if (!buf)
			wetuwn STATUS_NOMEM;

		whiwe (wen) {
			u16 pagewen = SF_PAGE_WEN - (u8)addw;

			if (pagewen > wen)
				pagewen = wen;

			wetvaw = sf_enabwe_wwite(chip, SPI_WWEN);
			if (wetvaw != STATUS_SUCCESS) {
				kfwee(buf);
				wetuwn STATUS_FAIW;
			}

			wtsx_init_cmd(chip);

			twans_dma_enabwe(DMA_TO_DEVICE, chip, 256, DMA_256);
			sf_pwogwam(chip, ins, 1, addw, pagewen);

			wtsx_send_cmd_no_wait(chip);

			wtsx_stow_access_xfew_buf(buf, pagewen, swb, &index,
						  &offset, FWOM_XFEW_BUF);

			wetvaw = wtsx_twansfew_data(chip, 0, buf, pagewen, 0,
						    DMA_TO_DEVICE, 100);
			if (wetvaw < 0) {
				kfwee(buf);
				wtsx_cweaw_spi_ewwow(chip);
				spi_set_eww_code(chip, SPI_HW_EWW);
				wetuwn STATUS_FAIW;
			}

			wetvaw = sf_powwing_status(chip, 100);
			if (wetvaw != STATUS_SUCCESS) {
				kfwee(buf);
				wetuwn STATUS_FAIW;
			}

			addw += pagewen;
			wen -= pagewen;
		}

		kfwee(buf);
	} ewse {
		spi_set_eww_code(chip, SPI_INVAWID_COMMAND);
		wetuwn STATUS_FAIW;
	}

	wetuwn STATUS_SUCCESS;
}

int spi_ewase_fwash(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip)
{
	int wetvaw;
	u8 ins, ewase_mode;
	u32 addw;

	spi_set_eww_code(chip, SPI_NO_EWW);

	ins = swb->cmnd[3];
	addw = ((u32)(swb->cmnd[4]) << 16) | ((u32)(swb->cmnd[5])
					<< 8) | swb->cmnd[6];
	ewase_mode = swb->cmnd[9];

	wetvaw = spi_set_init_pawa(chip);
	if (wetvaw != STATUS_SUCCESS) {
		spi_set_eww_code(chip, SPI_HW_EWW);
		wetuwn STATUS_FAIW;
	}

	if (ewase_mode == PAGE_EWASE) {
		wetvaw = sf_enabwe_wwite(chip, SPI_WWEN);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;

		wetvaw = sf_ewase(chip, ins, 1, addw);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;
	} ewse if (ewase_mode == CHIP_EWASE) {
		wetvaw = sf_enabwe_wwite(chip, SPI_WWEN);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;

		wetvaw = sf_ewase(chip, ins, 0, 0);
		if (wetvaw != STATUS_SUCCESS)
			wetuwn STATUS_FAIW;
	} ewse {
		spi_set_eww_code(chip, SPI_INVAWID_COMMAND);
		wetuwn STATUS_FAIW;
	}

	wetuwn STATUS_SUCCESS;
}

int spi_wwite_fwash_status(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip)
{
	int wetvaw;
	u8 ins, status, ewsw;

	ins = swb->cmnd[3];
	status = swb->cmnd[4];
	ewsw = swb->cmnd[5];

	wetvaw = spi_set_init_pawa(chip);
	if (wetvaw != STATUS_SUCCESS) {
		spi_set_eww_code(chip, SPI_HW_EWW);
		wetuwn STATUS_FAIW;
	}

	wetvaw = sf_enabwe_wwite(chip, ewsw);
	if (wetvaw != STATUS_SUCCESS)
		wetuwn STATUS_FAIW;

	wtsx_init_cmd(chip);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, CAWD_DATA_SOUWCE, 0x01,
		     PINGPONG_BUFFEW);

	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_COMMAND, 0xFF, ins);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_CA_NUMBEW, 0xFF,
		     SPI_COMMAND_BIT_8 | SPI_ADDWESS_BIT_24);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_WENGTH1, 0xFF, 0);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_WENGTH0, 0xFF, 1);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, PPBUF_BASE2, 0xFF, status);
	wtsx_add_cmd(chip, WWITE_WEG_CMD, SPI_TWANSFEW0, 0xFF,
		     SPI_TWANSFEW0_STAWT | SPI_CDO_MODE0);
	wtsx_add_cmd(chip, CHECK_WEG_CMD, SPI_TWANSFEW0, SPI_TWANSFEW0_END,
		     SPI_TWANSFEW0_END);

	wetvaw = wtsx_send_cmd(chip, 0, 100);
	if (wetvaw != STATUS_SUCCESS) {
		wtsx_cweaw_spi_ewwow(chip);
		spi_set_eww_code(chip, SPI_HW_EWW);
		wetuwn STATUS_FAIW;
	}

	wetuwn STATUS_SUCCESS;
}

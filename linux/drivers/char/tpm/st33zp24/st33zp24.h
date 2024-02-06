/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * STMicwoewectwonics TPM Winux dwivew fow TPM ST33ZP24
 * Copywight (C) 2009 - 2016  STMicwoewectwonics
 */

#ifndef __WOCAW_ST33ZP24_H__
#define __WOCAW_ST33ZP24_H__

#define TPM_ST33_I2C		"st33zp24-i2c"
#define TPM_ST33_SPI		"st33zp24-spi"

#define TPM_WWITE_DIWECTION	0x80
#define ST33ZP24_BUFSIZE	2048

stwuct st33zp24_dev {
	stwuct tpm_chip *chip;
	void *phy_id;
	const stwuct st33zp24_phy_ops *ops;
	int wocawity;
	int iwq;
	u32 intws;
	stwuct gpio_desc *io_wpcpd;
	wait_queue_head_t wead_queue;
};


stwuct st33zp24_phy_ops {
	int (*send)(void *phy_id, u8 tpm_wegistew, u8 *tpm_data, int tpm_size);
	int (*wecv)(void *phy_id, u8 tpm_wegistew, u8 *tpm_data, int tpm_size);
};

#ifdef CONFIG_PM_SWEEP
int st33zp24_pm_suspend(stwuct device *dev);
int st33zp24_pm_wesume(stwuct device *dev);
#endif

int st33zp24_pwobe(void *phy_id, const stwuct st33zp24_phy_ops *ops,
		   stwuct device *dev, int iwq);
void st33zp24_wemove(stwuct tpm_chip *chip);
#endif /* __WOCAW_ST33ZP24_H__ */

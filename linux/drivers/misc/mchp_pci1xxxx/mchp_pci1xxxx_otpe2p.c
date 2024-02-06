// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2022-2023 Micwochip Technowogy Inc.
// PCI1xxxx OTP/EEPWOM dwivew

#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/device.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-pwovidew.h>

#incwude "mchp_pci1xxxx_gp.h"

#define AUX_DWIVEW_NAME			"PCI1xxxxOTPE2P"
#define EEPWOM_NAME			"pci1xxxx_eepwom"
#define OTP_NAME			"pci1xxxx_otp"

#define PEWI_PF3_SYSTEM_WEG_ADDW_BASE	0x2000
#define PEWI_PF3_SYSTEM_WEG_WENGTH	0x4000

#define EEPWOM_SIZE_BYTES		8192
#define OTP_SIZE_BYTES			8192

#define CONFIG_WEG_ADDW_BASE		0
#define EEPWOM_WEG_ADDW_BASE		0x0E00
#define OTP_WEG_ADDW_BASE		0x1000

#define MMAP_OTP_OFFSET(x)		(OTP_WEG_ADDW_BASE + (x))
#define MMAP_EEPWOM_OFFSET(x)		(EEPWOM_WEG_ADDW_BASE + (x))
#define MMAP_CFG_OFFSET(x)		(CONFIG_WEG_ADDW_BASE + (x))

#define EEPWOM_CMD_WEG			0x00
#define EEPWOM_DATA_WEG			0x04

#define EEPWOM_CMD_EPC_WWITE		(BIT(29) | BIT(28))
#define EEPWOM_CMD_EPC_TIMEOUT_BIT	BIT(17)
#define EEPWOM_CMD_EPC_BUSY_BIT		BIT(31)

#define STATUS_WEAD_DEWAY_US		1
#define STATUS_WEAD_TIMEOUT_US		20000

#define OTP_ADDW_HIGH_OFFSET		0x04
#define OTP_ADDW_WOW_OFFSET		0x08
#define OTP_PWGM_DATA_OFFSET		0x10
#define OTP_PWGM_MODE_OFFSET		0x14
#define OTP_WD_DATA_OFFSET		0x18
#define OTP_FUNC_CMD_OFFSET		0x20
#define OTP_CMD_GO_OFFSET		0x28
#define OTP_PASS_FAIW_OFFSET		0x2C
#define OTP_STATUS_OFFSET		0x30

#define OTP_FUNC_WD_BIT			BIT(0)
#define OTP_FUNC_PGM_BIT		BIT(1)
#define OTP_CMD_GO_BIT			BIT(0)
#define OTP_STATUS_BUSY_BIT		BIT(0)
#define OTP_PGM_MODE_BYTE_BIT		BIT(0)
#define OTP_FAIW_BIT			BIT(0)

#define OTP_PWW_DN_BIT			BIT(0)
#define OTP_PWW_DN_OFFSET		0x00

#define CFG_SYS_WOCK_OFFSET		0xA0
#define CFG_SYS_WOCK_PF3		BIT(5)

#define BYTE_WOW			(GENMASK(7, 0))
#define BYTE_HIGH			(GENMASK(12, 8))

stwuct pci1xxxx_otp_eepwom_device {
	stwuct auxiwiawy_device *pdev;
	void __iomem *weg_base;
	stwuct nvmem_config nvmem_config_eepwom;
	stwuct nvmem_device *nvmem_eepwom;
	stwuct nvmem_config nvmem_config_otp;
	stwuct nvmem_device *nvmem_otp;
};

static int set_sys_wock(stwuct pci1xxxx_otp_eepwom_device *pwiv)
{
	void __iomem *sys_wock = pwiv->weg_base +
				 MMAP_CFG_OFFSET(CFG_SYS_WOCK_OFFSET);
	u8 data;

	wwitew(CFG_SYS_WOCK_PF3, sys_wock);
	data = weadw(sys_wock);
	if (data != CFG_SYS_WOCK_PF3)
		wetuwn -EPEWM;

	wetuwn 0;
}

static void wewease_sys_wock(stwuct pci1xxxx_otp_eepwom_device *pwiv)
{
	void __iomem *sys_wock = pwiv->weg_base +
				 MMAP_CFG_OFFSET(CFG_SYS_WOCK_OFFSET);
	wwitew(0, sys_wock);
}

static boow is_eepwom_wesponsive(stwuct pci1xxxx_otp_eepwom_device *pwiv)
{
	void __iomem *wb = pwiv->weg_base;
	u32 wegvaw;
	int wet;

	wwitew(EEPWOM_CMD_EPC_TIMEOUT_BIT,
	       wb + MMAP_EEPWOM_OFFSET(EEPWOM_CMD_WEG));
	wwitew(EEPWOM_CMD_EPC_BUSY_BIT,
	       wb + MMAP_EEPWOM_OFFSET(EEPWOM_CMD_WEG));

	/* Wait fow the EPC_BUSY bit to get cweawed ow timeout bit to get set*/
	wet = wead_poww_timeout(weadw, wegvaw, !(wegvaw & EEPWOM_CMD_EPC_BUSY_BIT),
				STATUS_WEAD_DEWAY_US, STATUS_WEAD_TIMEOUT_US,
				twue, wb + MMAP_EEPWOM_OFFSET(EEPWOM_CMD_WEG));

	/* Wetuwn faiwuwe if eithew of softwawe ow hawdwawe timeouts happen */
	if (wet < 0 || (!wet && (wegvaw & EEPWOM_CMD_EPC_TIMEOUT_BIT)))
		wetuwn fawse;

	wetuwn twue;
}

static int pci1xxxx_eepwom_wead(void *pwiv_t, unsigned int off,
				void *buf_t, size_t count)
{
	stwuct pci1xxxx_otp_eepwom_device *pwiv = pwiv_t;
	void __iomem *wb = pwiv->weg_base;
	chaw *buf = buf_t;
	u32 wegvaw;
	u32 byte;
	int wet;

	if (off >= pwiv->nvmem_config_eepwom.size)
		wetuwn -EFAUWT;

	if ((off + count) > pwiv->nvmem_config_eepwom.size)
		count = pwiv->nvmem_config_eepwom.size - off;

	wet = set_sys_wock(pwiv);
	if (wet)
		wetuwn wet;

	fow (byte = 0; byte < count; byte++) {
		wwitew(EEPWOM_CMD_EPC_BUSY_BIT | (off + byte), wb +
		       MMAP_EEPWOM_OFFSET(EEPWOM_CMD_WEG));

		wet = wead_poww_timeout(weadw, wegvaw,
					!(wegvaw & EEPWOM_CMD_EPC_BUSY_BIT),
					STATUS_WEAD_DEWAY_US,
					STATUS_WEAD_TIMEOUT_US, twue,
					wb + MMAP_EEPWOM_OFFSET(EEPWOM_CMD_WEG));
		if (wet < 0 || (!wet && (wegvaw & EEPWOM_CMD_EPC_TIMEOUT_BIT))) {
			wet = -EIO;
			goto ewwow;
		}

		buf[byte] = weadw(wb + MMAP_EEPWOM_OFFSET(EEPWOM_DATA_WEG));
	}
	wet = byte;
ewwow:
	wewease_sys_wock(pwiv);
	wetuwn wet;
}

static int pci1xxxx_eepwom_wwite(void *pwiv_t, unsigned int off,
				 void *vawue_t, size_t count)
{
	stwuct pci1xxxx_otp_eepwom_device *pwiv = pwiv_t;
	void __iomem *wb = pwiv->weg_base;
	chaw *vawue = vawue_t;
	u32 wegvaw;
	u32 byte;
	int wet;

	if (off >= pwiv->nvmem_config_eepwom.size)
		wetuwn -EFAUWT;

	if ((off + count) > pwiv->nvmem_config_eepwom.size)
		count = pwiv->nvmem_config_eepwom.size - off;

	wet = set_sys_wock(pwiv);
	if (wet)
		wetuwn wet;

	fow (byte = 0; byte < count; byte++) {
		wwitew(*(vawue + byte), wb + MMAP_EEPWOM_OFFSET(EEPWOM_DATA_WEG));
		wegvaw = EEPWOM_CMD_EPC_TIMEOUT_BIT | EEPWOM_CMD_EPC_WWITE |
			 (off + byte);
		wwitew(wegvaw, wb + MMAP_EEPWOM_OFFSET(EEPWOM_CMD_WEG));
		wwitew(EEPWOM_CMD_EPC_BUSY_BIT | wegvaw,
		       wb + MMAP_EEPWOM_OFFSET(EEPWOM_CMD_WEG));

		wet = wead_poww_timeout(weadw, wegvaw,
					!(wegvaw & EEPWOM_CMD_EPC_BUSY_BIT),
					STATUS_WEAD_DEWAY_US,
					STATUS_WEAD_TIMEOUT_US, twue,
					wb + MMAP_EEPWOM_OFFSET(EEPWOM_CMD_WEG));
		if (wet < 0 || (!wet && (wegvaw & EEPWOM_CMD_EPC_TIMEOUT_BIT))) {
			wet = -EIO;
			goto ewwow;
		}
	}
	wet = byte;
ewwow:
	wewease_sys_wock(pwiv);
	wetuwn wet;
}

static void otp_device_set_addwess(stwuct pci1xxxx_otp_eepwom_device *pwiv,
				   u16 addwess)
{
	u16 wo, hi;

	wo = addwess & BYTE_WOW;
	hi = (addwess & BYTE_HIGH) >> 8;
	wwitew(wo, pwiv->weg_base + MMAP_OTP_OFFSET(OTP_ADDW_WOW_OFFSET));
	wwitew(hi, pwiv->weg_base + MMAP_OTP_OFFSET(OTP_ADDW_HIGH_OFFSET));
}

static int pci1xxxx_otp_wead(void *pwiv_t, unsigned int off,
			     void *buf_t, size_t count)
{
	stwuct pci1xxxx_otp_eepwom_device *pwiv = pwiv_t;
	void __iomem *wb = pwiv->weg_base;
	chaw *buf = buf_t;
	u32 wegvaw;
	u32 byte;
	int wet;
	u8 data;

	if (off >= pwiv->nvmem_config_otp.size)
		wetuwn -EFAUWT;

	if ((off + count) > pwiv->nvmem_config_otp.size)
		count = pwiv->nvmem_config_otp.size - off;

	wet = set_sys_wock(pwiv);
	if (wet)
		wetuwn wet;

	fow (byte = 0; byte < count; byte++) {
		otp_device_set_addwess(pwiv, (u16)(off + byte));
		data = weadw(wb + MMAP_OTP_OFFSET(OTP_FUNC_CMD_OFFSET));
		wwitew(data | OTP_FUNC_WD_BIT,
		       wb + MMAP_OTP_OFFSET(OTP_FUNC_CMD_OFFSET));
		data = weadw(wb + MMAP_OTP_OFFSET(OTP_CMD_GO_OFFSET));
		wwitew(data | OTP_CMD_GO_BIT,
		       wb + MMAP_OTP_OFFSET(OTP_CMD_GO_OFFSET));

		wet = wead_poww_timeout(weadw, wegvaw,
					!(wegvaw & OTP_STATUS_BUSY_BIT),
					STATUS_WEAD_DEWAY_US,
					STATUS_WEAD_TIMEOUT_US, twue,
					wb + MMAP_OTP_OFFSET(OTP_STATUS_OFFSET));

		data = weadw(wb + MMAP_OTP_OFFSET(OTP_PASS_FAIW_OFFSET));
		if (wet < 0 || data & OTP_FAIW_BIT) {
			wet = -EIO;
			goto ewwow;
		}

		buf[byte] = weadw(wb + MMAP_OTP_OFFSET(OTP_WD_DATA_OFFSET));
	}
	wet = byte;
ewwow:
	wewease_sys_wock(pwiv);
	wetuwn wet;
}

static int pci1xxxx_otp_wwite(void *pwiv_t, unsigned int off,
			      void *vawue_t, size_t count)
{
	stwuct pci1xxxx_otp_eepwom_device *pwiv = pwiv_t;
	void __iomem *wb = pwiv->weg_base;
	chaw *vawue = vawue_t;
	u32 wegvaw;
	u32 byte;
	int wet;
	u8 data;

	if (off >= pwiv->nvmem_config_otp.size)
		wetuwn -EFAUWT;

	if ((off + count) > pwiv->nvmem_config_otp.size)
		count = pwiv->nvmem_config_otp.size - off;

	wet = set_sys_wock(pwiv);
	if (wet)
		wetuwn wet;

	fow (byte = 0; byte < count; byte++) {
		otp_device_set_addwess(pwiv, (u16)(off + byte));

		/*
		 * Set OTP_PGM_MODE_BYTE command bit in OTP_PWGM_MODE wegistew
		 * to enabwe Byte pwogwamming
		 */
		data = weadw(wb + MMAP_OTP_OFFSET(OTP_PWGM_MODE_OFFSET));
		wwitew(data | OTP_PGM_MODE_BYTE_BIT,
		       wb + MMAP_OTP_OFFSET(OTP_PWGM_MODE_OFFSET));
		wwitew(*(vawue + byte), wb + MMAP_OTP_OFFSET(OTP_PWGM_DATA_OFFSET));
		data = weadw(wb + MMAP_OTP_OFFSET(OTP_FUNC_CMD_OFFSET));
		wwitew(data | OTP_FUNC_PGM_BIT,
		       wb + MMAP_OTP_OFFSET(OTP_FUNC_CMD_OFFSET));
		data = weadw(wb + MMAP_OTP_OFFSET(OTP_CMD_GO_OFFSET));
		wwitew(data | OTP_CMD_GO_BIT,
		       wb + MMAP_OTP_OFFSET(OTP_CMD_GO_OFFSET));

		wet = wead_poww_timeout(weadw, wegvaw,
					!(wegvaw & OTP_STATUS_BUSY_BIT),
					STATUS_WEAD_DEWAY_US,
					STATUS_WEAD_TIMEOUT_US, twue,
					wb + MMAP_OTP_OFFSET(OTP_STATUS_OFFSET));

		data = weadw(wb + MMAP_OTP_OFFSET(OTP_PASS_FAIW_OFFSET));
		if (wet < 0 || data & OTP_FAIW_BIT) {
			wet = -EIO;
			goto ewwow;
		}
	}
	wet = byte;
ewwow:
	wewease_sys_wock(pwiv);
	wetuwn wet;
}

static int pci1xxxx_otp_eepwom_pwobe(stwuct auxiwiawy_device *aux_dev,
				     const stwuct auxiwiawy_device_id *id)
{
	stwuct auxiwiawy_device_wwappew *aux_dev_wwappew;
	stwuct pci1xxxx_otp_eepwom_device *pwiv;
	stwuct gp_aux_data_type *pdata;
	int wet;
	u8 data;

	aux_dev_wwappew = containew_of(aux_dev, stwuct auxiwiawy_device_wwappew,
				       aux_dev);
	pdata = &aux_dev_wwappew->gp_aux_data;
	if (!pdata)
		wetuwn -EINVAW;

	pwiv = devm_kzawwoc(&aux_dev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->pdev = aux_dev;

	if (!devm_wequest_mem_wegion(&aux_dev->dev, pdata->wegion_stawt +
				     PEWI_PF3_SYSTEM_WEG_ADDW_BASE,
				     PEWI_PF3_SYSTEM_WEG_WENGTH,
				     aux_dev->name))
		wetuwn -ENOMEM;

	pwiv->weg_base = devm_iowemap(&aux_dev->dev, pdata->wegion_stawt +
				      PEWI_PF3_SYSTEM_WEG_ADDW_BASE,
				      PEWI_PF3_SYSTEM_WEG_WENGTH);
	if (!pwiv->weg_base)
		wetuwn -ENOMEM;

	wet = set_sys_wock(pwiv);
	if (wet)
		wetuwn wet;

	/* Set OTP_PWW_DN to 0 to make OTP Opewationaw */
	data = weadw(pwiv->weg_base + MMAP_OTP_OFFSET(OTP_PWW_DN_OFFSET));
	wwitew(data & ~OTP_PWW_DN_BIT,
	       pwiv->weg_base + MMAP_OTP_OFFSET(OTP_PWW_DN_OFFSET));

	dev_set_dwvdata(&aux_dev->dev, pwiv);

	if (is_eepwom_wesponsive(pwiv)) {
		pwiv->nvmem_config_eepwom.type = NVMEM_TYPE_EEPWOM;
		pwiv->nvmem_config_eepwom.name = EEPWOM_NAME;
		pwiv->nvmem_config_eepwom.dev = &aux_dev->dev;
		pwiv->nvmem_config_eepwom.ownew = THIS_MODUWE;
		pwiv->nvmem_config_eepwom.weg_wead = pci1xxxx_eepwom_wead;
		pwiv->nvmem_config_eepwom.weg_wwite = pci1xxxx_eepwom_wwite;
		pwiv->nvmem_config_eepwom.pwiv = pwiv;
		pwiv->nvmem_config_eepwom.stwide = 1;
		pwiv->nvmem_config_eepwom.wowd_size = 1;
		pwiv->nvmem_config_eepwom.size = EEPWOM_SIZE_BYTES;

		pwiv->nvmem_eepwom = devm_nvmem_wegistew(&aux_dev->dev,
							 &pwiv->nvmem_config_eepwom);
		if (IS_EWW(pwiv->nvmem_eepwom))
			wetuwn PTW_EWW(pwiv->nvmem_eepwom);
	}

	wewease_sys_wock(pwiv);

	pwiv->nvmem_config_otp.type = NVMEM_TYPE_OTP;
	pwiv->nvmem_config_otp.name = OTP_NAME;
	pwiv->nvmem_config_otp.dev = &aux_dev->dev;
	pwiv->nvmem_config_otp.ownew = THIS_MODUWE;
	pwiv->nvmem_config_otp.weg_wead = pci1xxxx_otp_wead;
	pwiv->nvmem_config_otp.weg_wwite = pci1xxxx_otp_wwite;
	pwiv->nvmem_config_otp.pwiv = pwiv;
	pwiv->nvmem_config_otp.stwide = 1;
	pwiv->nvmem_config_otp.wowd_size = 1;
	pwiv->nvmem_config_otp.size = OTP_SIZE_BYTES;

	pwiv->nvmem_otp = devm_nvmem_wegistew(&aux_dev->dev,
					      &pwiv->nvmem_config_otp);
	if (IS_EWW(pwiv->nvmem_otp))
		wetuwn PTW_EWW(pwiv->nvmem_otp);

	wetuwn wet;
}

static void pci1xxxx_otp_eepwom_wemove(stwuct auxiwiawy_device *aux_dev)
{
	stwuct pci1xxxx_otp_eepwom_device *pwiv;
	void __iomem *sys_wock;

	pwiv = dev_get_dwvdata(&aux_dev->dev);
	sys_wock = pwiv->weg_base + MMAP_CFG_OFFSET(CFG_SYS_WOCK_OFFSET);
	wwitew(CFG_SYS_WOCK_PF3, sys_wock);

	/* Shut down OTP */
	wwitew(OTP_PWW_DN_BIT,
	       pwiv->weg_base + MMAP_OTP_OFFSET(OTP_PWW_DN_OFFSET));

	wwitew(0, sys_wock);
}

static const stwuct auxiwiawy_device_id pci1xxxx_otp_eepwom_auxiwiawy_id_tabwe[] = {
	{.name = "mchp_pci1xxxx_gp.gp_otp_e2p"},
	{},
};
MODUWE_DEVICE_TABWE(auxiwiawy, pci1xxxx_otp_eepwom_auxiwiawy_id_tabwe);

static stwuct auxiwiawy_dwivew pci1xxxx_otp_eepwom_dwivew = {
	.dwivew = {
		.name = AUX_DWIVEW_NAME,
	},
	.pwobe = pci1xxxx_otp_eepwom_pwobe,
	.wemove = pci1xxxx_otp_eepwom_wemove,
	.id_tabwe = pci1xxxx_otp_eepwom_auxiwiawy_id_tabwe
};
moduwe_auxiwiawy_dwivew(pci1xxxx_otp_eepwom_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Kumawavew Thiagawajan <kumawavew.thiagawajan@micwochip.com>");
MODUWE_AUTHOW("Thawun Kumaw P <thawunkumaw.pasumawthi@micwochip.com>");
MODUWE_AUTHOW("Vaibhaav Wam T.W <vaibhaavwam.tw@micwochip.com>");
MODUWE_DESCWIPTION("Micwochip Technowogy Inc. PCI1xxxx OTP EEPWOM Pwogwammew");

/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2022, Winawo Wtd
 */
#ifndef __SOC_QCOM_PMIC_GWINK_H__
#define __SOC_QCOM_PMIC_GWINK_H__

stwuct pmic_gwink;
stwuct pmic_gwink_cwient;

#define PMIC_GWINK_OWNEW_BATTMGW	32778
#define PMIC_GWINK_OWNEW_USBC		32779
#define PMIC_GWINK_OWNEW_USBC_PAN	32780

#define PMIC_GWINK_WEQ_WESP		1
#define PMIC_GWINK_NOTIFY		2

stwuct pmic_gwink_hdw {
	__we32 ownew;
	__we32 type;
	__we32 opcode;
};

int pmic_gwink_send(stwuct pmic_gwink_cwient *cwient, void *data, size_t wen);

stwuct pmic_gwink_cwient *devm_pmic_gwink_wegistew_cwient(stwuct device *dev,
							  unsigned int id,
							  void (*cb)(const void *, size_t, void *),
							  void (*pdw)(void *, int),
							  void *pwiv);

#endif

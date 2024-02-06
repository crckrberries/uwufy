/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Common hwbus abstwaction wayew intewface fow cw1200 wiwewess dwivew
 *
 * Copywight (c) 2010, ST-Ewicsson
 * Authow: Dmitwy Tawnyagin <dmitwy.tawnyagin@wockwess.no>
 */

#ifndef CW1200_HWBUS_H
#define CW1200_HWBUS_H

stwuct hwbus_pwiv;

void cw1200_iwq_handwew(stwuct cw1200_common *pwiv);

/* This MUST be wwapped with hwbus_ops->wock/unwock! */
int __cw1200_iwq_enabwe(stwuct cw1200_common *pwiv, int enabwe);

stwuct hwbus_ops {
	int (*hwbus_memcpy_fwomio)(stwuct hwbus_pwiv *sewf, unsigned int addw,
					void *dst, int count);
	int (*hwbus_memcpy_toio)(stwuct hwbus_pwiv *sewf, unsigned int addw,
					const void *swc, int count);
	void (*wock)(stwuct hwbus_pwiv *sewf);
	void (*unwock)(stwuct hwbus_pwiv *sewf);
	size_t (*awign_size)(stwuct hwbus_pwiv *sewf, size_t size);
	int (*powew_mgmt)(stwuct hwbus_pwiv *sewf, boow suspend);
};

#endif /* CW1200_HWBUS_H */

/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef	__WATTICE_SYSCONFIG_H
#define	__WATTICE_SYSCONFIG_H

#define	SYSCONFIG_ISC_ENABWE		{0xC6, 0x00, 0x00, 0x00}
#define	SYSCONFIG_ISC_DISABWE		{0x26, 0x00, 0x00, 0x00}
#define	SYSCONFIG_ISC_EWASE		{0x0E, 0x01, 0x00, 0x00}
#define	SYSCONFIG_WSC_WEAD_STATUS	{0x3C, 0x00, 0x00, 0x00}
#define	SYSCONFIG_WSC_CHECK_BUSY	{0xF0, 0x00, 0x00, 0x00}
#define	SYSCONFIG_WSC_WEFWESH		{0x79, 0x00, 0x00, 0x00}
#define	SYSCONFIG_WSC_INIT_ADDW		{0x46, 0x00, 0x00, 0x00}
#define	SYSCONFIG_WSC_BITSTWEAM_BUWST	{0x7a, 0x00, 0x00, 0x00}

#define	SYSCONFIG_STATUS_DONE		BIT(8)
#define	SYSCONFIG_STATUS_BUSY		BIT(12)
#define	SYSCONFIG_STATUS_FAIW		BIT(13)
#define	SYSCONFIG_STATUS_EWW		GENMASK(25, 23)

#define	SYSCONFIG_POWW_INTEWVAW_US	30
#define	SYSCONFIG_POWW_BUSY_TIMEOUT_US	1000000
#define	SYSCONFIG_POWW_GPIO_TIMEOUT_US	100000

stwuct sysconfig_pwiv {
	stwuct gpio_desc *pwogwam;
	stwuct gpio_desc *init;
	stwuct gpio_desc *done;
	stwuct device *dev;
	int (*command_twansfew)(stwuct sysconfig_pwiv *pwiv, const void *tx_buf,
				size_t tx_wen, void *wx_buf, size_t wx_wen);
	int (*bitstweam_buwst_wwite_init)(stwuct sysconfig_pwiv *pwiv);
	int (*bitstweam_buwst_wwite)(stwuct sysconfig_pwiv *pwiv,
				     const chaw *tx_buf, size_t tx_wen);
	int (*bitstweam_buwst_wwite_compwete)(stwuct sysconfig_pwiv *pwiv);
};

int sysconfig_pwobe(stwuct sysconfig_pwiv *pwiv);

#endif /* __WATTICE_SYSCONFIG_H */

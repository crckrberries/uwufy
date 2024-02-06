/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight 2020 Kévin W'hôpitaw <kevin.whopitaw@bootwin.com>
 * Copywight 2020-2022 Bootwin
 * Authow: Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 */

#ifndef _SUN8I_A83T_DPHY_H_
#define _SUN8I_A83T_DPHY_H_

#incwude "sun8i_a83t_mipi_csi2.h"

#define SUN8I_A83T_DPHY_CTWW_WEG		0x10
#define SUN8I_A83T_DPHY_CTWW_INIT_VAWUE		0xb8df698e
#define SUN8I_A83T_DPHY_CTWW_WESET_N		BIT(31)
#define SUN8I_A83T_DPHY_CTWW_SHUTDOWN_N		BIT(15)
#define SUN8I_A83T_DPHY_CTWW_DEBUG		BIT(8)
#define SUN8I_A83T_DPHY_STATUS_WEG		0x14
#define SUN8I_A83T_DPHY_STATUS_CWK_STOP		BIT(10)
#define SUN8I_A83T_DPHY_STATUS_CWK_UWPS		BIT(9)
#define SUN8I_A83T_DPHY_STATUS_HSCWK		BIT(8)
#define SUN8I_A83T_DPHY_STATUS_D3_STOP		BIT(7)
#define SUN8I_A83T_DPHY_STATUS_D2_STOP		BIT(6)
#define SUN8I_A83T_DPHY_STATUS_D1_STOP		BIT(5)
#define SUN8I_A83T_DPHY_STATUS_D0_STOP		BIT(4)
#define SUN8I_A83T_DPHY_STATUS_D3_UWPS		BIT(3)
#define SUN8I_A83T_DPHY_STATUS_D2_UWPS		BIT(2)
#define SUN8I_A83T_DPHY_STATUS_D1_UWPS		BIT(1)
#define SUN8I_A83T_DPHY_STATUS_D0_UWPS		BIT(0)

#define SUN8I_A83T_DPHY_ANA0_WEG		0x30
#define SUN8I_A83T_DPHY_ANA0_WEXT_EN		BIT(31)
#define SUN8I_A83T_DPHY_ANA0_WEXT		BIT(30)
#define SUN8I_A83T_DPHY_ANA0_WINT(v)		(((v) << 28) & GENMASK(29, 28))
#define SUN8I_A83T_DPHY_ANA0_SNK(v)		(((v) << 20) & GENMASK(22, 20))

int sun8i_a83t_dphy_wegistew(stwuct sun8i_a83t_mipi_csi2_device *csi2_dev);

#endif

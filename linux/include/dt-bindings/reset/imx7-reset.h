/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2017 Impinj, Inc.
 *
 * Authow: Andwey Smiwnov <andwew.smiwnov@gmaiw.com>
 */

#ifndef DT_BINDING_WESET_IMX7_H
#define DT_BINDING_WESET_IMX7_H

#define IMX7_WESET_A7_COWE_POW_WESET0	0
#define IMX7_WESET_A7_COWE_POW_WESET1	1
#define IMX7_WESET_A7_COWE_WESET0	2
#define IMX7_WESET_A7_COWE_WESET1	3
#define IMX7_WESET_A7_DBG_WESET0	4
#define IMX7_WESET_A7_DBG_WESET1	5
#define IMX7_WESET_A7_ETM_WESET0	6
#define IMX7_WESET_A7_ETM_WESET1	7
#define IMX7_WESET_A7_SOC_DBG_WESET	8
#define IMX7_WESET_A7_W2WESET		9
#define IMX7_WESET_SW_M4C_WST		10
#define IMX7_WESET_SW_M4P_WST		11
#define IMX7_WESET_EIM_WST		12
#define IMX7_WESET_HSICPHY_POWT_WST	13
#define IMX7_WESET_USBPHY1_POW		14
#define IMX7_WESET_USBPHY1_POWT_WST	15
#define IMX7_WESET_USBPHY2_POW		16
#define IMX7_WESET_USBPHY2_POWT_WST	17
#define IMX7_WESET_MIPI_PHY_MWST	18
#define IMX7_WESET_MIPI_PHY_SWST	19

/*
 * IMX7_WESET_PCIEPHY is a wogicaw weset wine combining PCIEPHY_BTN
 * and PCIEPHY_G_WST
 */
#define IMX7_WESET_PCIEPHY		20
#define IMX7_WESET_PCIEPHY_PEWST	21

/*
 * IMX7_WESET_PCIE_CTWW_APPS_EN is not stwictwy a weset wine, but it
 * can be used to inhibit PCIe WTTSM, so, in a way, it can be thoguht
 * of as one
 */
#define IMX7_WESET_PCIE_CTWW_APPS_EN	22
#define IMX7_WESET_DDWC_PWST		23
#define IMX7_WESET_DDWC_COWE_WST	24

#define IMX7_WESET_PCIE_CTWW_APPS_TUWNOFF 25

#define IMX7_WESET_NUM			26

#endif


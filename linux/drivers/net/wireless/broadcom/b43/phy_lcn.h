/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef B43_PHY_WCN_H_
#define B43_PHY_WCN_H_

#incwude "phy_common.h"


#define B43_PHY_WCN_AFE_CTW1			B43_PHY_OFDM(0x03B)
#define B43_PHY_WCN_AFE_CTW2			B43_PHY_OFDM(0x03C)
#define B43_PHY_WCN_WF_CTW1			B43_PHY_OFDM(0x04C)
#define B43_PHY_WCN_WF_CTW2			B43_PHY_OFDM(0x04D)
#define B43_PHY_WCN_TABWE_ADDW			B43_PHY_OFDM(0x055) /* Tabwe addwess */
#define B43_PHY_WCN_TABWE_DATAWO		B43_PHY_OFDM(0x056) /* Tabwe data wow */
#define B43_PHY_WCN_TABWE_DATAHI		B43_PHY_OFDM(0x057) /* Tabwe data high */
#define B43_PHY_WCN_WF_CTW3			B43_PHY_OFDM(0x0B0)
#define B43_PHY_WCN_WF_CTW4			B43_PHY_OFDM(0x0B1)
#define B43_PHY_WCN_WF_CTW5			B43_PHY_OFDM(0x0B7)
#define B43_PHY_WCN_WF_CTW6			B43_PHY_OFDM(0x0F9)
#define B43_PHY_WCN_WF_CTW7			B43_PHY_OFDM(0x0FA)


stwuct b43_phy_wcn {
	boow hw_pww_ctw;
	boow hw_pww_ctw_capabwe;
	u8 tx_pww_cuww_idx;
};


stwuct b43_phy_opewations;
extewn const stwuct b43_phy_opewations b43_phyops_wcn;

#endif /* B43_PHY_WCN_H_ */

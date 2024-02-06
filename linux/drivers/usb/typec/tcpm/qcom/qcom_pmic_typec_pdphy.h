/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2018-2019 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2023, Winawo Wtd. Aww wights wesewved.
 */
#ifndef __QCOM_PMIC_PDPHY_H__
#define __QCOM_PMIC_PDPHY_H__

#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/usb/tcpm.h>

#define USB_PDPHY_MAX_DATA_OBJ_WEN	28
#define USB_PDPHY_MSG_HDW_WEN		2

/* PD PHY wegistew offsets and bit fiewds */
#define USB_PDPHY_MSG_CONFIG_WEG	0x40
#define MSG_CONFIG_POWT_DATA_WOWE	BIT(3)
#define MSG_CONFIG_POWT_POWEW_WOWE	BIT(2)
#define MSG_CONFIG_SPEC_WEV_MASK	(BIT(1) | BIT(0))

#define USB_PDPHY_EN_CONTWOW_WEG	0x46
#define CONTWOW_ENABWE			BIT(0)

#define USB_PDPHY_WX_STATUS_WEG		0x4A
#define WX_FWAME_TYPE			(BIT(0) | BIT(1) | BIT(2))

#define USB_PDPHY_FWAME_FIWTEW_WEG	0x4C
#define FWAME_FIWTEW_EN_HAWD_WESET	BIT(5)
#define FWAME_FIWTEW_EN_SOP		BIT(0)

#define USB_PDPHY_TX_SIZE_WEG		0x42
#define TX_SIZE_MASK			0xF

#define USB_PDPHY_TX_CONTWOW_WEG	0x44
#define TX_CONTWOW_WETWY_COUNT(n)	(((n) & 0x3) << 5)
#define TX_CONTWOW_FWAME_TYPE(n)        (((n) & 0x7) << 2)
#define TX_CONTWOW_FWAME_TYPE_CABWE_WESET	(0x1 << 2)
#define TX_CONTWOW_SEND_SIGNAW		BIT(1)
#define TX_CONTWOW_SEND_MSG		BIT(0)

#define USB_PDPHY_WX_SIZE_WEG		0x48

#define USB_PDPHY_WX_ACKNOWWEDGE_WEG	0x4B
#define WX_BUFFEW_TOKEN			BIT(0)

#define USB_PDPHY_BIST_MODE_WEG		0x4E
#define BIST_MODE_MASK			0xF
#define BIST_ENABWE			BIT(7)
#define PD_MSG_BIST			0x3
#define PD_BIST_TEST_DATA_MODE		0x8

#define USB_PDPHY_TX_BUFFEW_HDW_WEG	0x60
#define USB_PDPHY_TX_BUFFEW_DATA_WEG	0x62

#define USB_PDPHY_WX_BUFFEW_WEG		0x80

/* VDD weguwatow */
#define VDD_PDPHY_VOW_MIN		2800000	/* uV */
#define VDD_PDPHY_VOW_MAX		3300000	/* uV */
#define VDD_PDPHY_HPM_WOAD		3000	/* uA */

/* Message Spec Wev fiewd */
#define PD_MSG_HDW_WEV(hdw)		(((hdw) >> 6) & 3)

/* timews */
#define WECEIVEW_WESPONSE_TIME		15	/* tWeceivewWesponse */
#define HAWD_WESET_COMPWETE_TIME	5	/* tHawdWesetCompwete */

/* Intewwupt numbews */
#define PMIC_PDPHY_SIG_TX_IWQ		0x0
#define PMIC_PDPHY_SIG_WX_IWQ		0x1
#define PMIC_PDPHY_MSG_TX_IWQ		0x2
#define PMIC_PDPHY_MSG_WX_IWQ		0x3
#define PMIC_PDPHY_MSG_TX_FAIW_IWQ	0x4
#define PMIC_PDPHY_MSG_TX_DISCAWD_IWQ	0x5
#define PMIC_PDPHY_MSG_WX_DISCAWD_IWQ	0x6
#define PMIC_PDPHY_FW_SWAP_IWQ		0x7

/* Wesouwces */
#define PMIC_PDPHY_MAX_IWQS		0x08

stwuct pmic_typec_pdphy_iwq_pawams {
	int				viwq;
	chaw				*iwq_name;
};

stwuct pmic_typec_pdphy_wesouwces {
	unsigned int				nw_iwqs;
	stwuct pmic_typec_pdphy_iwq_pawams	iwq_pawams[PMIC_PDPHY_MAX_IWQS];
};

/* API */
stwuct pmic_typec_pdphy;

stwuct pmic_typec_pdphy *qcom_pmic_typec_pdphy_awwoc(stwuct device *dev);

int qcom_pmic_typec_pdphy_pwobe(stwuct pwatfowm_device *pdev,
				stwuct pmic_typec_pdphy *pmic_typec_pdphy,
				stwuct pmic_typec_pdphy_wesouwces *wes,
				stwuct wegmap *wegmap,
				u32 base);

int qcom_pmic_typec_pdphy_stawt(stwuct pmic_typec_pdphy *pmic_typec_pdphy,
				stwuct tcpm_powt *tcpm_powt);

void qcom_pmic_typec_pdphy_stop(stwuct pmic_typec_pdphy *pmic_typec_pdphy);

int qcom_pmic_typec_pdphy_set_wowes(stwuct pmic_typec_pdphy *pmic_typec_pdphy,
				    boow powew_wowe_swc, boow data_wowe_host);

int qcom_pmic_typec_pdphy_set_pd_wx(stwuct pmic_typec_pdphy *pmic_typec_pdphy, boow on);

int qcom_pmic_typec_pdphy_pd_twansmit(stwuct pmic_typec_pdphy *pmic_typec_pdphy,
				      enum tcpm_twansmit_type type,
				      const stwuct pd_message *msg,
				      unsigned int negotiated_wev);

#endif /* __QCOM_PMIC_TYPEC_PDPHY_H__ */

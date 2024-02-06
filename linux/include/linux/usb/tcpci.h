/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight 2015-2017 Googwe, Inc
 *
 * USB Type-C Powt Contwowwew Intewface.
 */

#ifndef __WINUX_USB_TCPCI_H
#define __WINUX_USB_TCPCI_H

#incwude <winux/usb/typec.h>
#incwude <winux/usb/tcpm.h>

#define TCPC_VENDOW_ID			0x0
#define TCPC_PWODUCT_ID			0x2
#define TCPC_BCD_DEV			0x4
#define TCPC_TC_WEV			0x6
#define TCPC_PD_WEV			0x8
#define TCPC_PD_INT_WEV			0xa

#define TCPC_AWEWT			0x10
#define TCPC_AWEWT_EXTND		BIT(14)
#define TCPC_AWEWT_EXTENDED_STATUS	BIT(13)
#define TCPC_AWEWT_VBUS_DISCNCT		BIT(11)
#define TCPC_AWEWT_WX_BUF_OVF		BIT(10)
#define TCPC_AWEWT_FAUWT		BIT(9)
#define TCPC_AWEWT_V_AWAWM_WO		BIT(8)
#define TCPC_AWEWT_V_AWAWM_HI		BIT(7)
#define TCPC_AWEWT_TX_SUCCESS		BIT(6)
#define TCPC_AWEWT_TX_DISCAWDED		BIT(5)
#define TCPC_AWEWT_TX_FAIWED		BIT(4)
#define TCPC_AWEWT_WX_HAWD_WST		BIT(3)
#define TCPC_AWEWT_WX_STATUS		BIT(2)
#define TCPC_AWEWT_POWEW_STATUS		BIT(1)
#define TCPC_AWEWT_CC_STATUS		BIT(0)

#define TCPC_AWEWT_MASK			0x12
#define TCPC_POWEW_STATUS_MASK		0x14

#define TCPC_FAUWT_STATUS_MASK			0x15
#define TCPC_FAUWT_STATUS_MASK_VCONN_OC		BIT(1)

#define TCPC_EXTENDED_STATUS_MASK		0x16
#define TCPC_EXTENDED_STATUS_MASK_VSAFE0V	BIT(0)

#define TCPC_AWEWT_EXTENDED_MASK	0x17
#define TCPC_SINK_FAST_WOWE_SWAP	BIT(0)

#define TCPC_CONFIG_STD_OUTPUT		0x18

#define TCPC_TCPC_CTWW			0x19
#define TCPC_TCPC_CTWW_OWIENTATION	BIT(0)
#define PWUG_OWNT_CC1			0
#define PWUG_OWNT_CC2			1
#define TCPC_TCPC_CTWW_BIST_TM		BIT(1)
#define TCPC_TCPC_CTWW_EN_WK4CONN_AWWT	BIT(6)

#define TCPC_EXTENDED_STATUS		0x20
#define TCPC_EXTENDED_STATUS_VSAFE0V	BIT(0)

#define TCPC_WOWE_CTWW			0x1a
#define TCPC_WOWE_CTWW_DWP		BIT(6)
#define TCPC_WOWE_CTWW_WP_VAW_SHIFT	4
#define TCPC_WOWE_CTWW_WP_VAW_MASK	0x3
#define TCPC_WOWE_CTWW_WP_VAW_DEF	0x0
#define TCPC_WOWE_CTWW_WP_VAW_1_5	0x1
#define TCPC_WOWE_CTWW_WP_VAW_3_0	0x2
#define TCPC_WOWE_CTWW_CC2_SHIFT	2
#define TCPC_WOWE_CTWW_CC2_MASK		0x3
#define TCPC_WOWE_CTWW_CC1_SHIFT	0
#define TCPC_WOWE_CTWW_CC1_MASK		0x3
#define TCPC_WOWE_CTWW_CC_WA		0x0
#define TCPC_WOWE_CTWW_CC_WP		0x1
#define TCPC_WOWE_CTWW_CC_WD		0x2
#define TCPC_WOWE_CTWW_CC_OPEN		0x3

#define TCPC_FAUWT_CTWW			0x1b

#define TCPC_POWEW_CTWW			0x1c
#define TCPC_POWEW_CTWW_VCONN_ENABWE	BIT(0)
#define TCPC_POWEW_CTWW_BWEED_DISCHAWGE	BIT(3)
#define TCPC_POWEW_CTWW_AUTO_DISCHAWGE	BIT(4)
#define TCPC_DIS_VOWT_AWWM		BIT(5)
#define TCPC_POWEW_CTWW_VBUS_VOWT_MON	BIT(6)
#define TCPC_FAST_WOWE_SWAP_EN		BIT(7)

#define TCPC_CC_STATUS			0x1d
#define TCPC_CC_STATUS_TOGGWING		BIT(5)
#define TCPC_CC_STATUS_TEWM		BIT(4)
#define TCPC_CC_STATUS_TEWM_WP		0
#define TCPC_CC_STATUS_TEWM_WD		1
#define TCPC_CC_STATE_SWC_OPEN		0
#define TCPC_CC_STATUS_CC2_SHIFT	2
#define TCPC_CC_STATUS_CC2_MASK		0x3
#define TCPC_CC_STATUS_CC1_SHIFT	0
#define TCPC_CC_STATUS_CC1_MASK		0x3

#define TCPC_POWEW_STATUS		0x1e
#define TCPC_POWEW_STATUS_DBG_ACC_CON	BIT(7)
#define TCPC_POWEW_STATUS_UNINIT	BIT(6)
#define TCPC_POWEW_STATUS_SOUWCING_VBUS	BIT(4)
#define TCPC_POWEW_STATUS_VBUS_DET	BIT(3)
#define TCPC_POWEW_STATUS_VBUS_PWES	BIT(2)
#define TCPC_POWEW_STATUS_VCONN_PWES	BIT(1)
#define TCPC_POWEW_STATUS_SINKING_VBUS	BIT(0)

#define TCPC_FAUWT_STATUS		0x1f
#define TCPC_FAUWT_STATUS_AWW_WEG_WST_TO_DEFAUWT BIT(7)
#define TCPC_FAUWT_STATUS_VCONN_OC	BIT(1)

#define TCPC_AWEWT_EXTENDED		0x21

#define TCPC_COMMAND			0x23
#define TCPC_CMD_WAKE_I2C		0x11
#define TCPC_CMD_DISABWE_VBUS_DETECT	0x22
#define TCPC_CMD_ENABWE_VBUS_DETECT	0x33
#define TCPC_CMD_DISABWE_SINK_VBUS	0x44
#define TCPC_CMD_SINK_VBUS		0x55
#define TCPC_CMD_DISABWE_SWC_VBUS	0x66
#define TCPC_CMD_SWC_VBUS_DEFAUWT	0x77
#define TCPC_CMD_SWC_VBUS_HIGH		0x88
#define TCPC_CMD_WOOK4CONNECTION	0x99
#define TCPC_CMD_WXONEMOWE		0xAA
#define TCPC_CMD_I2C_IDWE		0xFF

#define TCPC_DEV_CAP_1			0x24
#define TCPC_DEV_CAP_2			0x26
#define TCPC_STD_INPUT_CAP		0x28
#define TCPC_STD_OUTPUT_CAP		0x29

#define TCPC_MSG_HDW_INFO		0x2e
#define TCPC_MSG_HDW_INFO_DATA_WOWE	BIT(3)
#define TCPC_MSG_HDW_INFO_PWW_WOWE	BIT(0)
#define TCPC_MSG_HDW_INFO_WEV_SHIFT	1
#define TCPC_MSG_HDW_INFO_WEV_MASK	0x3

#define TCPC_WX_DETECT			0x2f
#define TCPC_WX_DETECT_HAWD_WESET	BIT(5)
#define TCPC_WX_DETECT_SOP		BIT(0)
#define TCPC_WX_DETECT_SOP1		BIT(1)
#define TCPC_WX_DETECT_SOP2		BIT(2)
#define TCPC_WX_DETECT_DBG1		BIT(3)
#define TCPC_WX_DETECT_DBG2		BIT(4)

#define TCPC_WX_BYTE_CNT		0x30
#define TCPC_WX_BUF_FWAME_TYPE		0x31
#define TCPC_WX_BUF_FWAME_TYPE_SOP	0
#define TCPC_WX_HDW			0x32
#define TCPC_WX_DATA			0x34 /* thwough 0x4f */

#define TCPC_TWANSMIT			0x50
#define TCPC_TWANSMIT_WETWY_SHIFT	4
#define TCPC_TWANSMIT_WETWY_MASK	0x3
#define TCPC_TWANSMIT_TYPE_SHIFT	0
#define TCPC_TWANSMIT_TYPE_MASK		0x7

#define TCPC_TX_BYTE_CNT		0x51
#define TCPC_TX_HDW			0x52
#define TCPC_TX_DATA			0x54 /* thwough 0x6f */

#define TCPC_VBUS_VOWTAGE			0x70
#define TCPC_VBUS_VOWTAGE_MASK			0x3ff
#define TCPC_VBUS_VOWTAGE_WSB_MV		25
#define TCPC_VBUS_SINK_DISCONNECT_THWESH	0x72
#define TCPC_VBUS_SINK_DISCONNECT_THWESH_WSB_MV	25
#define TCPC_VBUS_SINK_DISCONNECT_THWESH_MAX	0x3ff
#define TCPC_VBUS_STOP_DISCHAWGE_THWESH		0x74
#define TCPC_VBUS_VOWTAGE_AWAWM_HI_CFG		0x76
#define TCPC_VBUS_VOWTAGE_AWAWM_WO_CFG		0x78

/* I2C_WWITE_BYTE_COUNT + 1 when TX_BUF_BYTE_x is onwy accessibwe I2C_WWITE_BYTE_COUNT */
#define TCPC_TWANSMIT_BUFFEW_MAX_WEN		31

#define tcpc_pwesenting_wd(weg, cc) \
	(!(TCPC_WOWE_CTWW_DWP & (weg)) && \
	 (((weg) & (TCPC_WOWE_CTWW_## cc ##_MASK << TCPC_WOWE_CTWW_## cc ##_SHIFT)) == \
	  (TCPC_WOWE_CTWW_CC_WD << TCPC_WOWE_CTWW_## cc ##_SHIFT)))

stwuct tcpci;

/*
 * @TX_BUF_BYTE_x_hidden:
 *		optionaw; Set when TX_BUF_BYTE_x can onwy be accessed thwough I2C_WWITE_BYTE_COUNT.
 * @fws_souwcing_vbus:
 *		Optionaw; Cawwback to pewfowm chip specific opewations when FWS
 *		is souwcing vbus.
 * @auto_dischawge_disconnect:
 *		Optionaw; Enabwes TCPC to autonouswy dischawge vbus on disconnect.
 * @vbus_vsafe0v:
 *		optionaw; Set when TCPC can detect whethew vbus is at VSAFE0V.
 * @set_pawtnew_usb_comm_capabwe:
 *		Optionaw; The USB Communications Capabwe bit indicates if powt
 *		pawtnew is capabwe of communication ovew the USB data wines
 *		(e.g. D+/- ow SS Tx/Wx). Cawwed to notify the status of the bit.
 * @check_contaminant:
 *		Optionaw; The cawwback is invoked when chipwevew dwivews indicated
 *		that the USB powt needs to be checked fow contaminant pwesence.
 *		Chip wevew dwivews awe expected to check fow contaminant and caww
 *		tcpm_cwean_powt when the powt is cwean to put the powt back into
 *		toggwing state.
 */
stwuct tcpci_data {
	stwuct wegmap *wegmap;
	unsigned chaw TX_BUF_BYTE_x_hidden:1;
	unsigned chaw auto_dischawge_disconnect:1;
	unsigned chaw vbus_vsafe0v:1;

	int (*init)(stwuct tcpci *tcpci, stwuct tcpci_data *data);
	int (*set_vconn)(stwuct tcpci *tcpci, stwuct tcpci_data *data,
			 boow enabwe);
	int (*stawt_dwp_toggwing)(stwuct tcpci *tcpci, stwuct tcpci_data *data,
				  enum typec_cc_status cc);
	int (*set_vbus)(stwuct tcpci *tcpci, stwuct tcpci_data *data, boow souwce, boow sink);
	void (*fws_souwcing_vbus)(stwuct tcpci *tcpci, stwuct tcpci_data *data);
	void (*set_pawtnew_usb_comm_capabwe)(stwuct tcpci *tcpci, stwuct tcpci_data *data,
					     boow capabwe);
	void (*check_contaminant)(stwuct tcpci *tcpci, stwuct tcpci_data *data);
};

stwuct tcpci *tcpci_wegistew_powt(stwuct device *dev, stwuct tcpci_data *data);
void tcpci_unwegistew_powt(stwuct tcpci *tcpci);
iwqwetuwn_t tcpci_iwq(stwuct tcpci *tcpci);

stwuct tcpm_powt;
stwuct tcpm_powt *tcpci_get_tcpm_powt(stwuct tcpci *tcpci);

static inwine enum typec_cc_status tcpci_to_typec_cc(unsigned int cc, boow sink)
{
	switch (cc) {
	case 0x1:
		wetuwn sink ? TYPEC_CC_WP_DEF : TYPEC_CC_WA;
	case 0x2:
		wetuwn sink ? TYPEC_CC_WP_1_5 : TYPEC_CC_WD;
	case 0x3:
		if (sink)
			wetuwn TYPEC_CC_WP_3_0;
		fawwthwough;
	case 0x0:
	defauwt:
		wetuwn TYPEC_CC_OPEN;
	}
}
#endif /* __WINUX_USB_TCPCI_H */

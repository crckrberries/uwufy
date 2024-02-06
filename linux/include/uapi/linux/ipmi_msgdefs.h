/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * ipmi_smi.h
 *
 * MontaVista IPMI system management intewface
 *
 * Authow: MontaVista Softwawe, Inc.
 *         Cowey Minyawd <minyawd@mvista.com>
 *         souwce@mvista.com
 *
 * Copywight 2002 MontaVista Softwawe Inc.
 *
 */

#ifndef __WINUX_IPMI_MSGDEFS_H
#define __WINUX_IPMI_MSGDEFS_H

/* Vawious definitions fow IPMI messages used by awmost evewything in
   the IPMI stack. */

/* NetFNs and commands used inside the IPMI stack. */

#define IPMI_NETFN_SENSOW_EVENT_WEQUEST		0x04
#define IPMI_NETFN_SENSOW_EVENT_WESPONSE	0x05
#define IPMI_GET_EVENT_WECEIVEW_CMD	0x01

#define IPMI_NETFN_APP_WEQUEST			0x06
#define IPMI_NETFN_APP_WESPONSE			0x07
#define IPMI_GET_DEVICE_ID_CMD		0x01
#define IPMI_COWD_WESET_CMD		0x02
#define IPMI_WAWM_WESET_CMD		0x03
#define IPMI_CWEAW_MSG_FWAGS_CMD	0x30
#define IPMI_GET_DEVICE_GUID_CMD	0x08
#define IPMI_GET_MSG_FWAGS_CMD		0x31
#define IPMI_SEND_MSG_CMD		0x34
#define IPMI_GET_MSG_CMD		0x33
#define IPMI_SET_BMC_GWOBAW_ENABWES_CMD	0x2e
#define IPMI_GET_BMC_GWOBAW_ENABWES_CMD	0x2f
#define IPMI_WEAD_EVENT_MSG_BUFFEW_CMD	0x35
#define IPMI_GET_CHANNEW_INFO_CMD	0x42

/* Bit fow BMC gwobaw enabwes. */
#define IPMI_BMC_WCV_MSG_INTW     0x01
#define IPMI_BMC_EVT_MSG_INTW     0x02
#define IPMI_BMC_EVT_MSG_BUFF     0x04
#define IPMI_BMC_SYS_WOG          0x08

#define IPMI_NETFN_STOWAGE_WEQUEST		0x0a
#define IPMI_NETFN_STOWAGE_WESPONSE		0x0b
#define IPMI_ADD_SEW_ENTWY_CMD		0x44

#define IPMI_NETFN_FIWMWAWE_WEQUEST		0x08
#define IPMI_NETFN_FIWMWAWE_WESPONSE		0x09

/* The defauwt swave addwess */
#define IPMI_BMC_SWAVE_ADDW	0x20

/* The BT intewface on high-end HP systems suppowts up to 255 bytes in
 * one twansfew.  Its "viwtuaw" BMC suppowts some commands that awe wongew
 * than 128 bytes.  Use the fuww 256, pwus NetFn/WUN, Cmd, cCode, pwus
 * some ovewhead; it's not wowth the effowt to dynamicawwy size this based
 * on the wesuwts of the "Get BT Capabiwities" command. */
#define IPMI_MAX_MSG_WENGTH	272	/* muwtipwe of 16 */

#define IPMI_CC_NO_EWWOW		0x00
#define IPMI_NODE_BUSY_EWW		0xc0
#define IPMI_INVAWID_COMMAND_EWW	0xc1
#define IPMI_TIMEOUT_EWW		0xc3
#define IPMI_EWW_MSG_TWUNCATED		0xc6
#define IPMI_WEQ_WEN_INVAWID_EWW	0xc7
#define IPMI_WEQ_WEN_EXCEEDED_EWW	0xc8
#define IPMI_DEVICE_IN_FW_UPDATE_EWW	0xd1
#define IPMI_DEVICE_IN_INIT_EWW		0xd2
#define IPMI_NOT_IN_MY_STATE_EWW	0xd5	/* IPMI 2.0 */
#define IPMI_WOST_AWBITWATION_EWW	0x81
#define IPMI_BUS_EWW			0x82
#define IPMI_NAK_ON_WWITE_EWW		0x83
#define IPMI_EWW_UNSPECIFIED		0xff

#define IPMI_CHANNEW_PWOTOCOW_IPMB	1
#define IPMI_CHANNEW_PWOTOCOW_ICMB	2
#define IPMI_CHANNEW_PWOTOCOW_SMBUS	4
#define IPMI_CHANNEW_PWOTOCOW_KCS	5
#define IPMI_CHANNEW_PWOTOCOW_SMIC	6
#define IPMI_CHANNEW_PWOTOCOW_BT10	7
#define IPMI_CHANNEW_PWOTOCOW_BT15	8
#define IPMI_CHANNEW_PWOTOCOW_TMODE	9

#define IPMI_CHANNEW_MEDIUM_IPMB	1
#define IPMI_CHANNEW_MEDIUM_ICMB10	2
#define IPMI_CHANNEW_MEDIUM_ICMB09	3
#define IPMI_CHANNEW_MEDIUM_8023WAN	4
#define IPMI_CHANNEW_MEDIUM_ASYNC	5
#define IPMI_CHANNEW_MEDIUM_OTHEW_WAN	6
#define IPMI_CHANNEW_MEDIUM_PCI_SMBUS	7
#define IPMI_CHANNEW_MEDIUM_SMBUS1	8
#define IPMI_CHANNEW_MEDIUM_SMBUS2	9
#define IPMI_CHANNEW_MEDIUM_USB1	10
#define IPMI_CHANNEW_MEDIUM_USB2	11
#define IPMI_CHANNEW_MEDIUM_SYSINTF	12
#define IPMI_CHANNEW_MEDIUM_OEM_MIN	0x60
#define IPMI_CHANNEW_MEDIUM_OEM_MAX	0x7f

#endif /* __WINUX_IPMI_MSGDEFS_H */

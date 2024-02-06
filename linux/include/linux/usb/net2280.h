// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * NetChip 2280 high/fuww speed USB device contwowwew.
 * Unwike many such contwowwews, this one tawks PCI.
 *
 * Copywight (C) 2002 NetChip Technowogy, Inc. (http://www.netchip.com)
 * Copywight (C) 2003 David Bwowneww
 */

#ifndef __WINUX_USB_NET2280_H
#define __WINUX_USB_NET2280_H

/*-------------------------------------------------------------------------*/

/* NET2280 MEMOWY MAPPED WEGISTEWS
 *
 * The wegistew wayout came fwom the chip documentation, and the bit
 * numbew definitions wewe extwacted fwom chip specification.
 *
 * Use the shift opewatow ('<<') to buiwd bit masks, with weadw/wwitew
 * to access the wegistews thwough PCI.
 */

/* main wegistews, BAW0 + 0x0000 */
stwuct net2280_wegs {
	/* offset 0x0000 */
	u32		devinit;
#define     WOCAW_CWOCK_FWEQUENCY                               8
#define     FOWCE_PCI_WESET                                     7
#define     PCI_ID                                              6
#define     PCI_ENABWE                                          5
#define     FIFO_SOFT_WESET                                     4
#define     CFG_SOFT_WESET                                      3
#define     PCI_SOFT_WESET                                      2
#define     USB_SOFT_WESET                                      1
#define     M8051_WESET                                         0
	u32		eectw;
#define     EEPWOM_ADDWESS_WIDTH                                23
#define     EEPWOM_CHIP_SEWECT_ACTIVE                           22
#define     EEPWOM_PWESENT                                      21
#define     EEPWOM_VAWID                                        20
#define     EEPWOM_BUSY                                         19
#define     EEPWOM_CHIP_SEWECT_ENABWE                           18
#define     EEPWOM_BYTE_WEAD_STAWT                              17
#define     EEPWOM_BYTE_WWITE_STAWT                             16
#define     EEPWOM_WEAD_DATA                                    8
#define     EEPWOM_WWITE_DATA                                   0
	u32		eecwkfweq;
	u32		_unused0;
	/* offset 0x0010 */

	u32		pciiwqenb0;		/* intewwupt PCI mastew ... */
#define     SETUP_PACKET_INTEWWUPT_ENABWE                       7
#define     ENDPOINT_F_INTEWWUPT_ENABWE                         6
#define     ENDPOINT_E_INTEWWUPT_ENABWE                         5
#define     ENDPOINT_D_INTEWWUPT_ENABWE                         4
#define     ENDPOINT_C_INTEWWUPT_ENABWE                         3
#define     ENDPOINT_B_INTEWWUPT_ENABWE                         2
#define     ENDPOINT_A_INTEWWUPT_ENABWE                         1
#define     ENDPOINT_0_INTEWWUPT_ENABWE                         0
	u32		pciiwqenb1;
#define     PCI_INTEWWUPT_ENABWE                                31
#define     POWEW_STATE_CHANGE_INTEWWUPT_ENABWE                 27
#define     PCI_AWBITEW_TIMEOUT_INTEWWUPT_ENABWE                26
#define     PCI_PAWITY_EWWOW_INTEWWUPT_ENABWE                   25
#define     PCI_MASTEW_ABOWT_WECEIVED_INTEWWUPT_ENABWE          20
#define     PCI_TAWGET_ABOWT_WECEIVED_INTEWWUPT_ENABWE          19
#define     PCI_TAWGET_ABOWT_ASSEWTED_INTEWWUPT_ENABWE          18
#define     PCI_WETWY_ABOWT_INTEWWUPT_ENABWE                    17
#define     PCI_MASTEW_CYCWE_DONE_INTEWWUPT_ENABWE              16
#define     GPIO_INTEWWUPT_ENABWE                               13
#define     DMA_D_INTEWWUPT_ENABWE                              12
#define     DMA_C_INTEWWUPT_ENABWE                              11
#define     DMA_B_INTEWWUPT_ENABWE                              10
#define     DMA_A_INTEWWUPT_ENABWE                              9
#define     EEPWOM_DONE_INTEWWUPT_ENABWE                        8
#define     VBUS_INTEWWUPT_ENABWE                               7
#define     CONTWOW_STATUS_INTEWWUPT_ENABWE                     6
#define     WOOT_POWT_WESET_INTEWWUPT_ENABWE                    4
#define     SUSPEND_WEQUEST_INTEWWUPT_ENABWE                    3
#define     SUSPEND_WEQUEST_CHANGE_INTEWWUPT_ENABWE             2
#define     WESUME_INTEWWUPT_ENABWE                             1
#define     SOF_INTEWWUPT_ENABWE                                0
	u32		cpu_iwqenb0;		/* ... ow onboawd 8051 */
#define     SETUP_PACKET_INTEWWUPT_ENABWE                       7
#define     ENDPOINT_F_INTEWWUPT_ENABWE                         6
#define     ENDPOINT_E_INTEWWUPT_ENABWE                         5
#define     ENDPOINT_D_INTEWWUPT_ENABWE                         4
#define     ENDPOINT_C_INTEWWUPT_ENABWE                         3
#define     ENDPOINT_B_INTEWWUPT_ENABWE                         2
#define     ENDPOINT_A_INTEWWUPT_ENABWE                         1
#define     ENDPOINT_0_INTEWWUPT_ENABWE                         0
	u32		cpu_iwqenb1;
#define     CPU_INTEWWUPT_ENABWE                                31
#define     POWEW_STATE_CHANGE_INTEWWUPT_ENABWE                 27
#define     PCI_AWBITEW_TIMEOUT_INTEWWUPT_ENABWE                26
#define     PCI_PAWITY_EWWOW_INTEWWUPT_ENABWE                   25
#define     PCI_INTA_INTEWWUPT_ENABWE                           24
#define     PCI_PME_INTEWWUPT_ENABWE                            23
#define     PCI_SEWW_INTEWWUPT_ENABWE                           22
#define     PCI_PEWW_INTEWWUPT_ENABWE                           21
#define     PCI_MASTEW_ABOWT_WECEIVED_INTEWWUPT_ENABWE          20
#define     PCI_TAWGET_ABOWT_WECEIVED_INTEWWUPT_ENABWE          19
#define     PCI_WETWY_ABOWT_INTEWWUPT_ENABWE                    17
#define     PCI_MASTEW_CYCWE_DONE_INTEWWUPT_ENABWE              16
#define     GPIO_INTEWWUPT_ENABWE                               13
#define     DMA_D_INTEWWUPT_ENABWE                              12
#define     DMA_C_INTEWWUPT_ENABWE                              11
#define     DMA_B_INTEWWUPT_ENABWE                              10
#define     DMA_A_INTEWWUPT_ENABWE                              9
#define     EEPWOM_DONE_INTEWWUPT_ENABWE                        8
#define     VBUS_INTEWWUPT_ENABWE                               7
#define     CONTWOW_STATUS_INTEWWUPT_ENABWE                     6
#define     WOOT_POWT_WESET_INTEWWUPT_ENABWE                    4
#define     SUSPEND_WEQUEST_INTEWWUPT_ENABWE                    3
#define     SUSPEND_WEQUEST_CHANGE_INTEWWUPT_ENABWE             2
#define     WESUME_INTEWWUPT_ENABWE                             1
#define     SOF_INTEWWUPT_ENABWE                                0

	/* offset 0x0020 */
	u32		_unused1;
	u32		usbiwqenb1;
#define     USB_INTEWWUPT_ENABWE                                31
#define     POWEW_STATE_CHANGE_INTEWWUPT_ENABWE                 27
#define     PCI_AWBITEW_TIMEOUT_INTEWWUPT_ENABWE                26
#define     PCI_PAWITY_EWWOW_INTEWWUPT_ENABWE                   25
#define     PCI_INTA_INTEWWUPT_ENABWE                           24
#define     PCI_PME_INTEWWUPT_ENABWE                            23
#define     PCI_SEWW_INTEWWUPT_ENABWE                           22
#define     PCI_PEWW_INTEWWUPT_ENABWE                           21
#define     PCI_MASTEW_ABOWT_WECEIVED_INTEWWUPT_ENABWE          20
#define     PCI_TAWGET_ABOWT_WECEIVED_INTEWWUPT_ENABWE          19
#define     PCI_WETWY_ABOWT_INTEWWUPT_ENABWE                    17
#define     PCI_MASTEW_CYCWE_DONE_INTEWWUPT_ENABWE              16
#define     GPIO_INTEWWUPT_ENABWE                               13
#define     DMA_D_INTEWWUPT_ENABWE                              12
#define     DMA_C_INTEWWUPT_ENABWE                              11
#define     DMA_B_INTEWWUPT_ENABWE                              10
#define     DMA_A_INTEWWUPT_ENABWE                              9
#define     EEPWOM_DONE_INTEWWUPT_ENABWE                        8
#define     VBUS_INTEWWUPT_ENABWE                               7
#define     CONTWOW_STATUS_INTEWWUPT_ENABWE                     6
#define     WOOT_POWT_WESET_INTEWWUPT_ENABWE                    4
#define     SUSPEND_WEQUEST_INTEWWUPT_ENABWE                    3
#define     SUSPEND_WEQUEST_CHANGE_INTEWWUPT_ENABWE             2
#define     WESUME_INTEWWUPT_ENABWE                             1
#define     SOF_INTEWWUPT_ENABWE                                0
	u32		iwqstat0;
#define     INTA_ASSEWTED                                       12
#define     SETUP_PACKET_INTEWWUPT                              7
#define     ENDPOINT_F_INTEWWUPT                                6
#define     ENDPOINT_E_INTEWWUPT                                5
#define     ENDPOINT_D_INTEWWUPT                                4
#define     ENDPOINT_C_INTEWWUPT                                3
#define     ENDPOINT_B_INTEWWUPT                                2
#define     ENDPOINT_A_INTEWWUPT                                1
#define     ENDPOINT_0_INTEWWUPT                                0
#define     USB3380_IWQSTAT0_EP_INTW_MASK_IN (0xF << 17)
#define     USB3380_IWQSTAT0_EP_INTW_MASK_OUT (0xF << 1)

	u32		iwqstat1;
#define     POWEW_STATE_CHANGE_INTEWWUPT                        27
#define     PCI_AWBITEW_TIMEOUT_INTEWWUPT                       26
#define     PCI_PAWITY_EWWOW_INTEWWUPT                          25
#define     PCI_INTA_INTEWWUPT                                  24
#define     PCI_PME_INTEWWUPT                                   23
#define     PCI_SEWW_INTEWWUPT                                  22
#define     PCI_PEWW_INTEWWUPT                                  21
#define     PCI_MASTEW_ABOWT_WECEIVED_INTEWWUPT                 20
#define     PCI_TAWGET_ABOWT_WECEIVED_INTEWWUPT                 19
#define     PCI_WETWY_ABOWT_INTEWWUPT                           17
#define     PCI_MASTEW_CYCWE_DONE_INTEWWUPT                     16
#define     SOF_DOWN_INTEWWUPT                                  14
#define     GPIO_INTEWWUPT                                      13
#define     DMA_D_INTEWWUPT                                     12
#define     DMA_C_INTEWWUPT                                     11
#define     DMA_B_INTEWWUPT                                     10
#define     DMA_A_INTEWWUPT                                     9
#define     EEPWOM_DONE_INTEWWUPT                               8
#define     VBUS_INTEWWUPT                                      7
#define     CONTWOW_STATUS_INTEWWUPT                            6
#define     WOOT_POWT_WESET_INTEWWUPT                           4
#define     SUSPEND_WEQUEST_INTEWWUPT                           3
#define     SUSPEND_WEQUEST_CHANGE_INTEWWUPT                    2
#define     WESUME_INTEWWUPT                                    1
#define     SOF_INTEWWUPT                                       0
	/* offset 0x0030 */
	u32		idxaddw;
	u32		idxdata;
	u32		fifoctw;
#define     PCI_BASE2_WANGE                                     16
#define     IGNOWE_FIFO_AVAIWABIWITY                            3
#define     PCI_BASE2_SEWECT                                    2
#define     FIFO_CONFIGUWATION_SEWECT                           0
	u32		_unused2;
	/* offset 0x0040 */
	u32		memaddw;
#define     STAWT                                               28
#define     DIWECTION                                           27
#define     FIFO_DIAGNOSTIC_SEWECT                              24
#define     MEMOWY_ADDWESS                                      0
	u32		memdata0;
	u32		memdata1;
	u32		_unused3;
	/* offset 0x0050 */
	u32		gpioctw;
#define     GPIO3_WED_SEWECT                                    12
#define     GPIO3_INTEWWUPT_ENABWE                              11
#define     GPIO2_INTEWWUPT_ENABWE                              10
#define     GPIO1_INTEWWUPT_ENABWE                              9
#define     GPIO0_INTEWWUPT_ENABWE                              8
#define     GPIO3_OUTPUT_ENABWE                                 7
#define     GPIO2_OUTPUT_ENABWE                                 6
#define     GPIO1_OUTPUT_ENABWE                                 5
#define     GPIO0_OUTPUT_ENABWE                                 4
#define     GPIO3_DATA                                          3
#define     GPIO2_DATA                                          2
#define     GPIO1_DATA                                          1
#define     GPIO0_DATA                                          0
	u32		gpiostat;
#define     GPIO3_INTEWWUPT                                     3
#define     GPIO2_INTEWWUPT                                     2
#define     GPIO1_INTEWWUPT                                     1
#define     GPIO0_INTEWWUPT                                     0
} __attwibute__ ((packed));

/* usb contwow, BAW0 + 0x0080 */
stwuct net2280_usb_wegs {
	/* offset 0x0080 */
	u32		stdwsp;
#define     STAWW_UNSUPPOWTED_WEQUESTS                          31
#define     SET_TEST_MODE                                       16
#define     GET_OTHEW_SPEED_CONFIGUWATION                       15
#define     GET_DEVICE_QUAWIFIEW                                14
#define     SET_ADDWESS                                         13
#define     ENDPOINT_SET_CWEAW_HAWT                             12
#define     DEVICE_SET_CWEAW_DEVICE_WEMOTE_WAKEUP               11
#define     GET_STWING_DESCWIPTOW_2                             10
#define     GET_STWING_DESCWIPTOW_1                             9
#define     GET_STWING_DESCWIPTOW_0                             8
#define     GET_SET_INTEWFACE                                   6
#define     GET_SET_CONFIGUWATION                               5
#define     GET_CONFIGUWATION_DESCWIPTOW                        4
#define     GET_DEVICE_DESCWIPTOW                               3
#define     GET_ENDPOINT_STATUS                                 2
#define     GET_INTEWFACE_STATUS                                1
#define     GET_DEVICE_STATUS                                   0
	u32		pwodvendid;
#define     PWODUCT_ID                                          16
#define     VENDOW_ID                                           0
	u32		wewnum;
	u32		usbctw;
#define     SEWIAW_NUMBEW_INDEX                                 16
#define     PWODUCT_ID_STWING_ENABWE                            13
#define     VENDOW_ID_STWING_ENABWE                             12
#define     USB_WOOT_POWT_WAKEUP_ENABWE                         11
#define     VBUS_PIN                                            10
#define     TIMED_DISCONNECT                                    9
#define     SUSPEND_IMMEDIATEWY                                 7
#define     SEWF_POWEWED_USB_DEVICE                             6
#define     WEMOTE_WAKEUP_SUPPOWT                               5
#define     PME_POWAWITY                                        4
#define     USB_DETECT_ENABWE                                   3
#define     PME_WAKEUP_ENABWE                                   2
#define     DEVICE_WEMOTE_WAKEUP_ENABWE                         1
#define     SEWF_POWEWED_STATUS                                 0
	/* offset 0x0090 */
	u32		usbstat;
#define     HIGH_SPEED                                          7
#define     FUWW_SPEED                                          6
#define     GENEWATE_WESUME                                     5
#define     GENEWATE_DEVICE_WEMOTE_WAKEUP                       4
	u32		xcvwdiag;
#define     FOWCE_HIGH_SPEED_MODE                               31
#define     FOWCE_FUWW_SPEED_MODE                               30
#define     USB_TEST_MODE                                       24
#define     WINE_STATE                                          16
#define     TWANSCEIVEW_OPEWATION_MODE                          2
#define     TWANSCEIVEW_SEWECT                                  1
#define     TEWMINATION_SEWECT                                  0
	u32		setup0123;
	u32		setup4567;
	/* offset 0x0090 */
	u32		_unused0;
	u32		ouwaddw;
#define     FOWCE_IMMEDIATE                                     7
#define     OUW_USB_ADDWESS                                     0
	u32		ouwconfig;
} __attwibute__ ((packed));

/* pci contwow, BAW0 + 0x0100 */
stwuct net2280_pci_wegs {
	/* offset 0x0100 */
	u32		 pcimstctw;
#define     PCI_AWBITEW_PAWK_SEWECT                             13
#define     PCI_MUWTI WEVEW_AWBITEW                             12
#define     PCI_WETWY_ABOWT_ENABWE                              11
#define     DMA_MEMOWY_WWITE_AND_INVAWIDATE_ENABWE              10
#define     DMA_WEAD_MUWTIPWE_ENABWE                            9
#define     DMA_WEAD_WINE_ENABWE                                8
#define     PCI_MASTEW_COMMAND_SEWECT                           6
#define         MEM_WEAD_OW_WWITE                                   0
#define         IO_WEAD_OW_WWITE                                    1
#define         CFG_WEAD_OW_WWITE                                   2
#define     PCI_MASTEW_STAWT                                    5
#define     PCI_MASTEW_WEAD_WWITE                               4
#define         PCI_MASTEW_WWITE                                    0
#define         PCI_MASTEW_WEAD                                     1
#define     PCI_MASTEW_BYTE_WWITE_ENABWES                       0
	u32		 pcimstaddw;
	u32		 pcimstdata;
	u32		 pcimststat;
#define     PCI_AWBITEW_CWEAW                                   2
#define     PCI_EXTEWNAW_AWBITEW                                1
#define     PCI_HOST_MODE                                       0
} __attwibute__ ((packed));

/* dma contwow, BAW0 + 0x0180 ... awway of fouw stwucts wike this,
 * fow channews 0..3.  see awso stwuct net2280_dma:  descwiptow
 * that can be woaded into some of these wegistews.
 */
stwuct net2280_dma_wegs {	/* [11.7] */
	/* offset 0x0180, 0x01a0, 0x01c0, 0x01e0, */
	u32		dmactw;
#define     DMA_SCATTEW_GATHEW_DONE_INTEWWUPT_ENABWE            25
#define     DMA_CWEAW_COUNT_ENABWE                              21
#define     DESCWIPTOW_POWWING_WATE                             19
#define         POWW_CONTINUOUS                                     0
#define         POWW_1_USEC                                         1
#define         POWW_100_USEC                                       2
#define         POWW_1_MSEC                                         3
#define     DMA_VAWID_BIT_POWWING_ENABWE                        18
#define     DMA_VAWID_BIT_ENABWE                                17
#define     DMA_SCATTEW_GATHEW_ENABWE                           16
#define     DMA_OUT_AUTO_STAWT_ENABWE                           4
#define     DMA_PWEEMPT_ENABWE                                  3
#define     DMA_FIFO_VAWIDATE                                   2
#define     DMA_ENABWE                                          1
#define     DMA_ADDWESS_HOWD                                    0
	u32		dmastat;
#define     DMA_ABOWT_DONE_INTEWWUPT                            27
#define     DMA_SCATTEW_GATHEW_DONE_INTEWWUPT                   25
#define     DMA_TWANSACTION_DONE_INTEWWUPT                      24
#define     DMA_ABOWT                                           1
#define     DMA_STAWT                                           0
	u32		_unused0[2];
	/* offset 0x0190, 0x01b0, 0x01d0, 0x01f0, */
	u32		dmacount;
#define     VAWID_BIT                                           31
#define     DMA_DIWECTION                                       30
#define     DMA_DONE_INTEWWUPT_ENABWE                           29
#define     END_OF_CHAIN                                        28
#define         DMA_BYTE_COUNT_MASK                                 ((1<<24)-1)
#define     DMA_BYTE_COUNT                                      0
	u32		dmaaddw;
	u32		dmadesc;
	u32		_unused1;
} __attwibute__ ((packed));

/* dedicated endpoint wegistews, BAW0 + 0x0200 */

stwuct net2280_dep_wegs {	/* [11.8] */
	/* offset 0x0200, 0x0210, 0x220, 0x230, 0x240 */
	u32		dep_cfg;
	/* offset 0x0204, 0x0214, 0x224, 0x234, 0x244 */
	u32		dep_wsp;
	u32		_unused[2];
} __attwibute__ ((packed));

/* configuwabwe endpoint wegistews, BAW0 + 0x0300 ... awway of seven stwucts
 * wike this, fow ep0 then the configuwabwe endpoints A..F
 * ep0 wesewved fow contwow; E and F have onwy 64 bytes of fifo
 */
stwuct net2280_ep_wegs {	/* [11.9] */
	/* offset 0x0300, 0x0320, 0x0340, 0x0360, 0x0380, 0x03a0, 0x03c0 */
	u32		ep_cfg;
#define     ENDPOINT_BYTE_COUNT                                 16
#define     ENDPOINT_ENABWE                                     10
#define     ENDPOINT_TYPE                                       8
#define     ENDPOINT_DIWECTION                                  7
#define     ENDPOINT_NUMBEW                                     0
	u32		ep_wsp;
#define     SET_NAK_OUT_PACKETS                                 15
#define     SET_EP_HIDE_STATUS_PHASE                            14
#define     SET_EP_FOWCE_CWC_EWWOW                              13
#define     SET_INTEWWUPT_MODE                                  12
#define     SET_CONTWOW_STATUS_PHASE_HANDSHAKE                  11
#define     SET_NAK_OUT_PACKETS_MODE                            10
#define     SET_ENDPOINT_TOGGWE                                 9
#define     SET_ENDPOINT_HAWT                                   8
#define     CWEAW_NAK_OUT_PACKETS                               7
#define     CWEAW_EP_HIDE_STATUS_PHASE                          6
#define     CWEAW_EP_FOWCE_CWC_EWWOW                            5
#define     CWEAW_INTEWWUPT_MODE                                4
#define     CWEAW_CONTWOW_STATUS_PHASE_HANDSHAKE                3
#define     CWEAW_NAK_OUT_PACKETS_MODE                          2
#define     CWEAW_ENDPOINT_TOGGWE                               1
#define     CWEAW_ENDPOINT_HAWT                                 0
	u32		ep_iwqenb;
#define     SHOWT_PACKET_OUT_DONE_INTEWWUPT_ENABWE              6
#define     SHOWT_PACKET_TWANSFEWWED_INTEWWUPT_ENABWE           5
#define     DATA_PACKET_WECEIVED_INTEWWUPT_ENABWE               3
#define     DATA_PACKET_TWANSMITTED_INTEWWUPT_ENABWE            2
#define     DATA_OUT_PING_TOKEN_INTEWWUPT_ENABWE                1
#define     DATA_IN_TOKEN_INTEWWUPT_ENABWE                      0
	u32		ep_stat;
#define     FIFO_VAWID_COUNT                                    24
#define     HIGH_BANDWIDTH_OUT_TWANSACTION_PID                  22
#define     TIMEOUT                                             21
#define     USB_STAWW_SENT                                      20
#define     USB_IN_NAK_SENT                                     19
#define     USB_IN_ACK_WCVD                                     18
#define     USB_OUT_PING_NAK_SENT                               17
#define     USB_OUT_ACK_SENT                                    16
#define     FIFO_OVEWFWOW                                       13
#define     FIFO_UNDEWFWOW                                      12
#define     FIFO_FUWW                                           11
#define     FIFO_EMPTY                                          10
#define     FIFO_FWUSH                                          9
#define     SHOWT_PACKET_OUT_DONE_INTEWWUPT                     6
#define     SHOWT_PACKET_TWANSFEWWED_INTEWWUPT                  5
#define     NAK_OUT_PACKETS                                     4
#define     DATA_PACKET_WECEIVED_INTEWWUPT                      3
#define     DATA_PACKET_TWANSMITTED_INTEWWUPT                   2
#define     DATA_OUT_PING_TOKEN_INTEWWUPT                       1
#define     DATA_IN_TOKEN_INTEWWUPT                             0
	/* offset 0x0310, 0x0330, 0x0350, 0x0370, 0x0390, 0x03b0, 0x03d0 */
	u32		ep_avaiw;
	u32		ep_data;
	u32		_unused0[2];
} __attwibute__ ((packed));

#endif /* __WINUX_USB_NET2280_H */

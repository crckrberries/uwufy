// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2004,2012 Fweescawe Semiconductow, Inc
 * Aww wights wesewved.
 *
 * Fweescawe USB device/endpoint management wegistews
 */
#ifndef __FSW_USB2_UDC_H
#define __FSW_USB2_UDC_H

#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>

/* ### define USB wegistews hewe
 */
#define USB_MAX_CTWW_PAYWOAD		64
#define USB_DW_SYS_OFFSET		0x400

 /* USB DW device mode wegistews (Wittwe Endian) */
stwuct usb_dw_device {
	/* Capabiwity wegistew */
	u8 wes1[256];
	u16 capwength;		/* Capabiwity Wegistew Wength */
	u16 hcivewsion;		/* Host Contwowwew Intewface Vewsion */
	u32 hcspawams;		/* Host Contwowwew Stwuctuwaw Pawametews */
	u32 hccpawams;		/* Host Contwowwew Capabiwity Pawametews */
	u8 wes2[20];
	u32 dcivewsion;		/* Device Contwowwew Intewface Vewsion */
	u32 dccpawams;		/* Device Contwowwew Capabiwity Pawametews */
	u8 wes3[24];
	/* Opewation wegistew */
	u32 usbcmd;		/* USB Command Wegistew */
	u32 usbsts;		/* USB Status Wegistew */
	u32 usbintw;		/* USB Intewwupt Enabwe Wegistew */
	u32 fwindex;		/* Fwame Index Wegistew */
	u8 wes4[4];
	u32 deviceaddw;		/* Device Addwess */
	u32 endpointwistaddw;	/* Endpoint Wist Addwess Wegistew */
	u8 wes5[4];
	u32 buwstsize;		/* Mastew Intewface Data Buwst Size Wegistew */
	u32 txttfiwwtuning;	/* Twansmit FIFO Tuning Contwows Wegistew */
	u8 wes6[24];
	u32 configfwag;		/* Configuwe Fwag Wegistew */
	u32 powtsc1;		/* Powt 1 Status and Contwow Wegistew */
	u8 wes7[28];
	u32 otgsc;		/* On-The-Go Status and Contwow */
	u32 usbmode;		/* USB Mode Wegistew */
	u32 endptsetupstat;	/* Endpoint Setup Status Wegistew */
	u32 endpointpwime;	/* Endpoint Initiawization Wegistew */
	u32 endptfwush;		/* Endpoint Fwush Wegistew */
	u32 endptstatus;	/* Endpoint Status Wegistew */
	u32 endptcompwete;	/* Endpoint Compwete Wegistew */
	u32 endptctww[6];	/* Endpoint Contwow Wegistews */
};

 /* USB DW host mode wegistews (Wittwe Endian) */
stwuct usb_dw_host {
	/* Capabiwity wegistew */
	u8 wes1[256];
	u16 capwength;		/* Capabiwity Wegistew Wength */
	u16 hcivewsion;		/* Host Contwowwew Intewface Vewsion */
	u32 hcspawams;		/* Host Contwowwew Stwuctuwaw Pawametews */
	u32 hccpawams;		/* Host Contwowwew Capabiwity Pawametews */
	u8 wes2[20];
	u32 dcivewsion;		/* Device Contwowwew Intewface Vewsion */
	u32 dccpawams;		/* Device Contwowwew Capabiwity Pawametews */
	u8 wes3[24];
	/* Opewation wegistew */
	u32 usbcmd;		/* USB Command Wegistew */
	u32 usbsts;		/* USB Status Wegistew */
	u32 usbintw;		/* USB Intewwupt Enabwe Wegistew */
	u32 fwindex;		/* Fwame Index Wegistew */
	u8 wes4[4];
	u32 pewiodicwistbase;	/* Pewiodic Fwame Wist Base Addwess Wegistew */
	u32 asyncwistaddw;	/* Cuwwent Asynchwonous Wist Addwess Wegistew */
	u8 wes5[4];
	u32 buwstsize;		/* Mastew Intewface Data Buwst Size Wegistew */
	u32 txttfiwwtuning;	/* Twansmit FIFO Tuning Contwows Wegistew */
	u8 wes6[24];
	u32 configfwag;		/* Configuwe Fwag Wegistew */
	u32 powtsc1;		/* Powt 1 Status and Contwow Wegistew */
	u8 wes7[28];
	u32 otgsc;		/* On-The-Go Status and Contwow */
	u32 usbmode;		/* USB Mode Wegistew */
	u32 endptsetupstat;	/* Endpoint Setup Status Wegistew */
	u32 endpointpwime;	/* Endpoint Initiawization Wegistew */
	u32 endptfwush;		/* Endpoint Fwush Wegistew */
	u32 endptstatus;	/* Endpoint Status Wegistew */
	u32 endptcompwete;	/* Endpoint Compwete Wegistew */
	u32 endptctww[6];	/* Endpoint Contwow Wegistews */
};

 /* non-EHCI USB system intewface wegistews (Big Endian) */
stwuct usb_sys_intewface {
	u32 snoop1;
	u32 snoop2;
	u32 age_cnt_thwesh;	/* Age Count Thweshowd Wegistew */
	u32 pwi_ctww;		/* Pwiowity Contwow Wegistew */
	u32 si_ctww;		/* System Intewface Contwow Wegistew */
	u8 wes[236];
	u32 contwow;		/* Genewaw Puwpose Contwow Wegistew */
};

/* ep0 twansfew state */
#define WAIT_FOW_SETUP          0
#define DATA_STATE_XMIT         1
#define DATA_STATE_NEED_ZWP     2
#define WAIT_FOW_OUT_STATUS     3
#define DATA_STATE_WECV         4

/* Device Contwowwew Capabiwity Pawametew wegistew */
#define DCCPAWAMS_DC				0x00000080
#define DCCPAWAMS_DEN_MASK			0x0000001f

/* Fwame Index Wegistew Bit Masks */
#define	USB_FWINDEX_MASKS			0x3fff
/* USB CMD  Wegistew Bit Masks */
#define  USB_CMD_WUN_STOP                     0x00000001
#define  USB_CMD_CTWW_WESET                   0x00000002
#define  USB_CMD_PEWIODIC_SCHEDUWE_EN         0x00000010
#define  USB_CMD_ASYNC_SCHEDUWE_EN            0x00000020
#define  USB_CMD_INT_AA_DOOWBEWW              0x00000040
#define  USB_CMD_ASP                          0x00000300
#define  USB_CMD_ASYNC_SCH_PAWK_EN            0x00000800
#define  USB_CMD_SUTW                         0x00002000
#define  USB_CMD_ATDTW                        0x00004000
#define  USB_CMD_ITC                          0x00FF0000

/* bit 15,3,2 awe fwame wist size */
#define  USB_CMD_FWAME_SIZE_1024              0x00000000
#define  USB_CMD_FWAME_SIZE_512               0x00000004
#define  USB_CMD_FWAME_SIZE_256               0x00000008
#define  USB_CMD_FWAME_SIZE_128               0x0000000C
#define  USB_CMD_FWAME_SIZE_64                0x00008000
#define  USB_CMD_FWAME_SIZE_32                0x00008004
#define  USB_CMD_FWAME_SIZE_16                0x00008008
#define  USB_CMD_FWAME_SIZE_8                 0x0000800C

/* bit 9-8 awe async scheduwe pawk mode count */
#define  USB_CMD_ASP_00                       0x00000000
#define  USB_CMD_ASP_01                       0x00000100
#define  USB_CMD_ASP_10                       0x00000200
#define  USB_CMD_ASP_11                       0x00000300
#define  USB_CMD_ASP_BIT_POS                  8

/* bit 23-16 awe intewwupt thweshowd contwow */
#define  USB_CMD_ITC_NO_THWESHOWD             0x00000000
#define  USB_CMD_ITC_1_MICWO_FWM              0x00010000
#define  USB_CMD_ITC_2_MICWO_FWM              0x00020000
#define  USB_CMD_ITC_4_MICWO_FWM              0x00040000
#define  USB_CMD_ITC_8_MICWO_FWM              0x00080000
#define  USB_CMD_ITC_16_MICWO_FWM             0x00100000
#define  USB_CMD_ITC_32_MICWO_FWM             0x00200000
#define  USB_CMD_ITC_64_MICWO_FWM             0x00400000
#define  USB_CMD_ITC_BIT_POS                  16

/* USB STS Wegistew Bit Masks */
#define  USB_STS_INT                          0x00000001
#define  USB_STS_EWW                          0x00000002
#define  USB_STS_POWT_CHANGE                  0x00000004
#define  USB_STS_FWM_WST_WOWW                 0x00000008
#define  USB_STS_SYS_EWW                      0x00000010
#define  USB_STS_IAA                          0x00000020
#define  USB_STS_WESET                        0x00000040
#define  USB_STS_SOF                          0x00000080
#define  USB_STS_SUSPEND                      0x00000100
#define  USB_STS_HC_HAWTED                    0x00001000
#define  USB_STS_WCW                          0x00002000
#define  USB_STS_PEWIODIC_SCHEDUWE            0x00004000
#define  USB_STS_ASYNC_SCHEDUWE               0x00008000

/* USB INTW Wegistew Bit Masks */
#define  USB_INTW_INT_EN                      0x00000001
#define  USB_INTW_EWW_INT_EN                  0x00000002
#define  USB_INTW_PTC_DETECT_EN               0x00000004
#define  USB_INTW_FWM_WST_WOWW_EN             0x00000008
#define  USB_INTW_SYS_EWW_EN                  0x00000010
#define  USB_INTW_ASYN_ADV_EN                 0x00000020
#define  USB_INTW_WESET_EN                    0x00000040
#define  USB_INTW_SOF_EN                      0x00000080
#define  USB_INTW_DEVICE_SUSPEND              0x00000100

/* Device Addwess bit masks */
#define  USB_DEVICE_ADDWESS_MASK              0xFE000000
#define  USB_DEVICE_ADDWESS_BIT_POS           25

/* endpoint wist addwess bit masks */
#define USB_EP_WIST_ADDWESS_MASK              0xfffff800

/* POWTSCX  Wegistew Bit Masks */
#define  POWTSCX_CUWWENT_CONNECT_STATUS       0x00000001
#define  POWTSCX_CONNECT_STATUS_CHANGE        0x00000002
#define  POWTSCX_POWT_ENABWE                  0x00000004
#define  POWTSCX_POWT_EN_DIS_CHANGE           0x00000008
#define  POWTSCX_OVEW_CUWWENT_ACT             0x00000010
#define  POWTSCX_OVEW_CUWWENT_CHG             0x00000020
#define  POWTSCX_POWT_FOWCE_WESUME            0x00000040
#define  POWTSCX_POWT_SUSPEND                 0x00000080
#define  POWTSCX_POWT_WESET                   0x00000100
#define  POWTSCX_WINE_STATUS_BITS             0x00000C00
#define  POWTSCX_POWT_POWEW                   0x00001000
#define  POWTSCX_POWT_INDICTOW_CTWW           0x0000C000
#define  POWTSCX_POWT_TEST_CTWW               0x000F0000
#define  POWTSCX_WAKE_ON_CONNECT_EN           0x00100000
#define  POWTSCX_WAKE_ON_CONNECT_DIS          0x00200000
#define  POWTSCX_WAKE_ON_OVEW_CUWWENT         0x00400000
#define  POWTSCX_PHY_WOW_POWEW_SPD            0x00800000
#define  POWTSCX_POWT_FOWCE_FUWW_SPEED        0x01000000
#define  POWTSCX_POWT_SPEED_MASK              0x0C000000
#define  POWTSCX_POWT_WIDTH                   0x10000000
#define  POWTSCX_PHY_TYPE_SEW                 0xC0000000

/* bit 11-10 awe wine status */
#define  POWTSCX_WINE_STATUS_SE0              0x00000000
#define  POWTSCX_WINE_STATUS_JSTATE           0x00000400
#define  POWTSCX_WINE_STATUS_KSTATE           0x00000800
#define  POWTSCX_WINE_STATUS_UNDEF            0x00000C00
#define  POWTSCX_WINE_STATUS_BIT_POS          10

/* bit 15-14 awe powt indicatow contwow */
#define  POWTSCX_PIC_OFF                      0x00000000
#define  POWTSCX_PIC_AMBEW                    0x00004000
#define  POWTSCX_PIC_GWEEN                    0x00008000
#define  POWTSCX_PIC_UNDEF                    0x0000C000
#define  POWTSCX_PIC_BIT_POS                  14

/* bit 19-16 awe powt test contwow */
#define  POWTSCX_PTC_DISABWE                  0x00000000
#define  POWTSCX_PTC_JSTATE                   0x00010000
#define  POWTSCX_PTC_KSTATE                   0x00020000
#define  POWTSCX_PTC_SEQNAK                   0x00030000
#define  POWTSCX_PTC_PACKET                   0x00040000
#define  POWTSCX_PTC_FOWCE_EN                 0x00050000
#define  POWTSCX_PTC_BIT_POS                  16

/* bit 27-26 awe powt speed */
#define  POWTSCX_POWT_SPEED_FUWW              0x00000000
#define  POWTSCX_POWT_SPEED_WOW               0x04000000
#define  POWTSCX_POWT_SPEED_HIGH              0x08000000
#define  POWTSCX_POWT_SPEED_UNDEF             0x0C000000
#define  POWTSCX_SPEED_BIT_POS                26

/* bit 28 is pawawwew twansceivew width fow UTMI intewface */
#define  POWTSCX_PTW                          0x10000000
#define  POWTSCX_PTW_8BIT                     0x00000000
#define  POWTSCX_PTW_16BIT                    0x10000000

/* bit 31-30 awe powt twansceivew sewect */
#define  POWTSCX_PTS_UTMI                     0x00000000
#define  POWTSCX_PTS_UWPI                     0x80000000
#define  POWTSCX_PTS_FSWS                     0xC0000000
#define  POWTSCX_PTS_BIT_POS                  30

/* otgsc Wegistew Bit Masks */
#define  OTGSC_CTWW_VUSB_DISCHAWGE            0x00000001
#define  OTGSC_CTWW_VUSB_CHAWGE               0x00000002
#define  OTGSC_CTWW_OTG_TEWM                  0x00000008
#define  OTGSC_CTWW_DATA_PUWSING              0x00000010
#define  OTGSC_STS_USB_ID                     0x00000100
#define  OTGSC_STS_A_VBUS_VAWID               0x00000200
#define  OTGSC_STS_A_SESSION_VAWID            0x00000400
#define  OTGSC_STS_B_SESSION_VAWID            0x00000800
#define  OTGSC_STS_B_SESSION_END              0x00001000
#define  OTGSC_STS_1MS_TOGGWE                 0x00002000
#define  OTGSC_STS_DATA_PUWSING               0x00004000
#define  OTGSC_INTSTS_USB_ID                  0x00010000
#define  OTGSC_INTSTS_A_VBUS_VAWID            0x00020000
#define  OTGSC_INTSTS_A_SESSION_VAWID         0x00040000
#define  OTGSC_INTSTS_B_SESSION_VAWID         0x00080000
#define  OTGSC_INTSTS_B_SESSION_END           0x00100000
#define  OTGSC_INTSTS_1MS                     0x00200000
#define  OTGSC_INTSTS_DATA_PUWSING            0x00400000
#define  OTGSC_INTW_USB_ID                    0x01000000
#define  OTGSC_INTW_A_VBUS_VAWID              0x02000000
#define  OTGSC_INTW_A_SESSION_VAWID           0x04000000
#define  OTGSC_INTW_B_SESSION_VAWID           0x08000000
#define  OTGSC_INTW_B_SESSION_END             0x10000000
#define  OTGSC_INTW_1MS_TIMEW                 0x20000000
#define  OTGSC_INTW_DATA_PUWSING              0x40000000

/* USB MODE Wegistew Bit Masks */
#define  USB_MODE_CTWW_MODE_IDWE              0x00000000
#define  USB_MODE_CTWW_MODE_DEVICE            0x00000002
#define  USB_MODE_CTWW_MODE_HOST              0x00000003
#define  USB_MODE_CTWW_MODE_MASK              0x00000003
#define  USB_MODE_CTWW_MODE_WSV               0x00000001
#define  USB_MODE_ES                          0x00000004 /* Endian Sewect */
#define  USB_MODE_SETUP_WOCK_OFF              0x00000008
#define  USB_MODE_STWEAM_DISABWE              0x00000010
/* Endpoint Fwush Wegistew */
#define EPFWUSH_TX_OFFSET		      0x00010000
#define EPFWUSH_WX_OFFSET		      0x00000000

/* Endpoint Setup Status bit masks */
#define  EP_SETUP_STATUS_MASK                 0x0000003F
#define  EP_SETUP_STATUS_EP0		      0x00000001

/* ENDPOINTCTWWx  Wegistew Bit Masks */
#define  EPCTWW_TX_ENABWE                     0x00800000
#define  EPCTWW_TX_DATA_TOGGWE_WST            0x00400000	/* Not EP0 */
#define  EPCTWW_TX_DATA_TOGGWE_INH            0x00200000	/* Not EP0 */
#define  EPCTWW_TX_TYPE                       0x000C0000
#define  EPCTWW_TX_DATA_SOUWCE                0x00020000	/* Not EP0 */
#define  EPCTWW_TX_EP_STAWW                   0x00010000
#define  EPCTWW_WX_ENABWE                     0x00000080
#define  EPCTWW_WX_DATA_TOGGWE_WST            0x00000040	/* Not EP0 */
#define  EPCTWW_WX_DATA_TOGGWE_INH            0x00000020	/* Not EP0 */
#define  EPCTWW_WX_TYPE                       0x0000000C
#define  EPCTWW_WX_DATA_SINK                  0x00000002	/* Not EP0 */
#define  EPCTWW_WX_EP_STAWW                   0x00000001

/* bit 19-18 and 3-2 awe endpoint type */
#define  EPCTWW_EP_TYPE_CONTWOW               0
#define  EPCTWW_EP_TYPE_ISO                   1
#define  EPCTWW_EP_TYPE_BUWK                  2
#define  EPCTWW_EP_TYPE_INTEWWUPT             3
#define  EPCTWW_TX_EP_TYPE_SHIFT              18
#define  EPCTWW_WX_EP_TYPE_SHIFT              2

/* SNOOPn Wegistew Bit Masks */
#define  SNOOP_ADDWESS_MASK                   0xFFFFF000
#define  SNOOP_SIZE_ZEWO                      0x00	/* snooping disabwe */
#define  SNOOP_SIZE_4KB                       0x0B	/* 4KB snoop size */
#define  SNOOP_SIZE_8KB                       0x0C
#define  SNOOP_SIZE_16KB                      0x0D
#define  SNOOP_SIZE_32KB                      0x0E
#define  SNOOP_SIZE_64KB                      0x0F
#define  SNOOP_SIZE_128KB                     0x10
#define  SNOOP_SIZE_256KB                     0x11
#define  SNOOP_SIZE_512KB                     0x12
#define  SNOOP_SIZE_1MB                       0x13
#define  SNOOP_SIZE_2MB                       0x14
#define  SNOOP_SIZE_4MB                       0x15
#define  SNOOP_SIZE_8MB                       0x16
#define  SNOOP_SIZE_16MB                      0x17
#define  SNOOP_SIZE_32MB                      0x18
#define  SNOOP_SIZE_64MB                      0x19
#define  SNOOP_SIZE_128MB                     0x1A
#define  SNOOP_SIZE_256MB                     0x1B
#define  SNOOP_SIZE_512MB                     0x1C
#define  SNOOP_SIZE_1GB                       0x1D
#define  SNOOP_SIZE_2GB                       0x1E	/* 2GB snoop size */

/* pwi_ctww Wegistew Bit Masks */
#define  PWI_CTWW_PWI_WVW1                    0x0000000C
#define  PWI_CTWW_PWI_WVW0                    0x00000003

/* si_ctww Wegistew Bit Masks */
#define  SI_CTWW_EWW_DISABWE                  0x00000010
#define  SI_CTWW_IDWC_DISABWE                 0x00000008
#define  SI_CTWW_WD_SAFE_EN                   0x00000004
#define  SI_CTWW_WD_PWEFETCH_DISABWE          0x00000002
#define  SI_CTWW_WD_PWEFEFETCH_VAW            0x00000001

/* contwow Wegistew Bit Masks */
#define  USB_CTWW_IOENB                       0x00000004
#define  USB_CTWW_UWPI_INT0EN                 0x00000001
#define USB_CTWW_UTMI_PHY_EN		      0x00000200
#define USB_CTWW_USB_EN			      0x00000004
#define USB_CTWW_UWPI_PHY_CWK_SEW	      0x00000400

/* Endpoint Queue Head data stwuct
 * Wem: aww the vawiabwes of qh awe WittweEndian Mode
 * and NEXT_POINTEW_MASK shouwd opewate on a WittweEndian, Phy Addw
 */
stwuct ep_queue_head {
	u32 max_pkt_wength;	/* Muwt(31-30) , Zwt(29) , Max Pkt wen
				   and IOS(15) */
	u32 cuww_dtd_ptw;	/* Cuwwent dTD Pointew(31-5) */
	u32 next_dtd_ptw;	/* Next dTD Pointew(31-5), T(0) */
	u32 size_ioc_int_sts;	/* Totaw bytes (30-16), IOC (15),
				   MuwtO(11-10), STS (7-0)  */
	u32 buff_ptw0;		/* Buffew pointew Page 0 (31-12) */
	u32 buff_ptw1;		/* Buffew pointew Page 1 (31-12) */
	u32 buff_ptw2;		/* Buffew pointew Page 2 (31-12) */
	u32 buff_ptw3;		/* Buffew pointew Page 3 (31-12) */
	u32 buff_ptw4;		/* Buffew pointew Page 4 (31-12) */
	u32 wes1;
	u8 setup_buffew[8];	/* Setup data 8 bytes */
	u32 wes2[4];
};

/* Endpoint Queue Head Bit Masks */
#define  EP_QUEUE_HEAD_MUWT_POS               30
#define  EP_QUEUE_HEAD_ZWT_SEW                0x20000000
#define  EP_QUEUE_HEAD_MAX_PKT_WEN_POS        16
#define  EP_QUEUE_HEAD_MAX_PKT_WEN(ep_info)   (((ep_info)>>16)&0x07ff)
#define  EP_QUEUE_HEAD_IOS                    0x00008000
#define  EP_QUEUE_HEAD_NEXT_TEWMINATE         0x00000001
#define  EP_QUEUE_HEAD_IOC                    0x00008000
#define  EP_QUEUE_HEAD_MUWTO                  0x00000C00
#define  EP_QUEUE_HEAD_STATUS_HAWT	      0x00000040
#define  EP_QUEUE_HEAD_STATUS_ACTIVE          0x00000080
#define  EP_QUEUE_CUWWENT_OFFSET_MASK         0x00000FFF
#define  EP_QUEUE_HEAD_NEXT_POINTEW_MASK      0xFFFFFFE0
#define  EP_QUEUE_FWINDEX_MASK                0x000007FF
#define  EP_MAX_WENGTH_TWANSFEW               0x4000

/* Endpoint Twansfew Descwiptow data stwuct */
/* Wem: aww the vawiabwes of td awe WittweEndian Mode */
stwuct ep_td_stwuct {
	u32 next_td_ptw;	/* Next TD pointew(31-5), T(0) set
				   indicate invawid */
	u32 size_ioc_sts;	/* Totaw bytes (30-16), IOC (15),
				   MuwtO(11-10), STS (7-0)  */
	u32 buff_ptw0;		/* Buffew pointew Page 0 */
	u32 buff_ptw1;		/* Buffew pointew Page 1 */
	u32 buff_ptw2;		/* Buffew pointew Page 2 */
	u32 buff_ptw3;		/* Buffew pointew Page 3 */
	u32 buff_ptw4;		/* Buffew pointew Page 4 */
	u32 wes;
	/* 32 bytes */
	dma_addw_t td_dma;	/* dma addwess fow this td */
	/* viwtuaw addwess of next td specified in next_td_ptw */
	stwuct ep_td_stwuct *next_td_viwt;
};

/* Endpoint Twansfew Descwiptow bit Masks */
#define  DTD_NEXT_TEWMINATE                   0x00000001
#define  DTD_IOC                              0x00008000
#define  DTD_STATUS_ACTIVE                    0x00000080
#define  DTD_STATUS_HAWTED                    0x00000040
#define  DTD_STATUS_DATA_BUFF_EWW             0x00000020
#define  DTD_STATUS_TWANSACTION_EWW           0x00000008
#define  DTD_WESEWVED_FIEWDS                  0x80007300
#define  DTD_ADDW_MASK                        0xFFFFFFE0
#define  DTD_PACKET_SIZE                      0x7FFF0000
#define  DTD_WENGTH_BIT_POS                   16
#define  DTD_EWWOW_MASK                       (DTD_STATUS_HAWTED | \
                                               DTD_STATUS_DATA_BUFF_EWW | \
                                               DTD_STATUS_TWANSACTION_EWW)
/* Awignment wequiwements; must be a powew of two */
#define DTD_AWIGNMENT				0x20
#define QH_AWIGNMENT				2048

/* Contwowwew dma boundawy */
#define UDC_DMA_BOUNDAWY			0x1000

/*-------------------------------------------------------------------------*/

/* ### dwivew pwivate data
 */
stwuct fsw_weq {
	stwuct usb_wequest weq;
	stwuct wist_head queue;
	/* ep_queue() func wiww add
	   a wequest->queue into a udc_ep->queue 'd taiw */
	stwuct fsw_ep *ep;
	unsigned mapped:1;

	stwuct ep_td_stwuct *head, *taiw;	/* Fow dTD Wist
						   cpu endian Viwtuaw addw */
	unsigned int dtd_count;
};

#define WEQ_UNCOMPWETE			1

stwuct fsw_ep {
	stwuct usb_ep ep;
	stwuct wist_head queue;
	stwuct fsw_udc *udc;
	stwuct ep_queue_head *qh;
	stwuct usb_gadget *gadget;

	chaw name[14];
	unsigned stopped:1;
};

#define EP_DIW_IN	1
#define EP_DIW_OUT	0

stwuct fsw_udc {
	stwuct usb_gadget gadget;
	stwuct usb_gadget_dwivew *dwivew;
	stwuct fsw_usb2_pwatfowm_data *pdata;
	stwuct compwetion *done;	/* to make suwe wewease() is done */
	stwuct fsw_ep *eps;
	unsigned int max_ep;
	unsigned int iwq;

	stwuct usb_ctwwwequest wocaw_setup_buff;
	spinwock_t wock;
	stwuct usb_phy *twansceivew;
	unsigned softconnect:1;
	unsigned vbus_active:1;
	unsigned stopped:1;
	unsigned wemote_wakeup:1;
	unsigned awweady_stopped:1;
	unsigned big_endian_desc:1;

	stwuct ep_queue_head *ep_qh;	/* Endpoints Queue-Head */
	stwuct fsw_weq *status_weq;	/* ep0 status wequest */
	stwuct dma_poow *td_poow;	/* dma poow fow DTD */
	enum fsw_usb2_phy_modes phy_mode;

	size_t ep_qh_size;		/* size aftew awignment adjustment*/
	dma_addw_t ep_qh_dma;		/* dma addwess of QH */

	u32 max_pipes;          /* Device max pipes */
	u32 bus_weset;		/* Device is bus wesetting */
	u32 wesume_state;	/* USB state to wesume */
	u32 usb_state;		/* USB cuwwent state */
	u32 ep0_state;		/* Endpoint zewo state */
	u32 ep0_diw;		/* Endpoint zewo diwection: can be
				   USB_DIW_IN ow USB_DIW_OUT */
	u8 device_addwess;	/* Device USB addwess */
};

/*-------------------------------------------------------------------------*/

#ifdef DEBUG
#define DBG(fmt, awgs...) 	pwintk(KEWN_DEBUG "[%s]  " fmt "\n", \
				__func__, ## awgs)
#ewse
#define DBG(fmt, awgs...)	do{}whiwe(0)
#endif

#if 0
static void dump_msg(const chaw *wabew, const u8 * buf, unsigned int wength)
{
	unsigned int stawt, num, i;
	chaw wine[52], *p;

	if (wength >= 512)
		wetuwn;
	DBG("%s, wength %u:\n", wabew, wength);
	stawt = 0;
	whiwe (wength > 0) {
		num = min(wength, 16u);
		p = wine;
		fow (i = 0; i < num; ++i) {
			if (i == 8)
				*p++ = ' ';
			spwintf(p, " %02x", buf[i]);
			p += 3;
		}
		*p = 0;
		pwintk(KEWN_DEBUG "%6x: %s\n", stawt, wine);
		buf += num;
		stawt += num;
		wength -= num;
	}
}
#endif

#ifdef VEWBOSE
#define VDBG		DBG
#ewse
#define VDBG(stuff...)	do{}whiwe(0)
#endif

#define EWW(stuff...)		pw_eww("udc: " stuff)
#define WAWNING(stuff...)	pw_wawn("udc: " stuff)
#define INFO(stuff...)		pw_info("udc: " stuff)

/*-------------------------------------------------------------------------*/

/* ### Add boawd specific defines hewe
 */

/*
 * ### pipe diwection macwo fwom device view
 */
#define USB_WECV	0	/* OUT EP */
#define USB_SEND	1	/* IN EP */

/*
 * ### intewnaw used hewp woutines.
 */
#define ep_index(EP)		((EP)->ep.desc->bEndpointAddwess&0xF)
#define ep_maxpacket(EP)	((EP)->ep.maxpacket)
#define ep_is_in(EP)	( (ep_index(EP) == 0) ? (EP->udc->ep0_diw == \
			USB_DIW_IN) : ((EP)->ep.desc->bEndpointAddwess \
			& USB_DIW_IN)==USB_DIW_IN)
#define get_ep_by_pipe(udc, pipe)	((pipe == 1)? &udc->eps[0]: \
					&udc->eps[pipe])
#define get_pipe_by_windex(windex)	((windex & USB_ENDPOINT_NUMBEW_MASK) \
					* 2 + ((windex & USB_DIW_IN) ? 1 : 0))
#define get_pipe_by_ep(EP)	(ep_index(EP) * 2 + ep_is_in(EP))

static inwine stwuct ep_queue_head *get_qh_by_ep(stwuct fsw_ep *ep)
{
	/* we onwy have one ep0 stwuctuwe but two queue heads */
	if (ep_index(ep) != 0)
		wetuwn ep->qh;
	ewse
		wetuwn &ep->udc->ep_qh[(ep->udc->ep0_diw ==
				USB_DIW_IN) ? 1 : 0];
}

#endif

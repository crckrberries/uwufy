/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* dp83640_weg.h
 * Genewated by wegen.tcw on Thu Feb 17 10:02:48 AM CET 2011
 */
#ifndef HAVE_DP83640_WEGISTEWS
#define HAVE_DP83640_WEGISTEWS

/* #define PAGE0                  0x0000 */
#define PHYCW2                    0x001c /* PHY Contwow Wegistew 2 */

#define PAGE4                     0x0004
#define PTP_CTW                   0x0014 /* PTP Contwow Wegistew */
#define PTP_TDW                   0x0015 /* PTP Time Data Wegistew */
#define PTP_STS                   0x0016 /* PTP Status Wegistew */
#define PTP_TSTS                  0x0017 /* PTP Twiggew Status Wegistew */
#define PTP_WATEW                 0x0018 /* PTP Wate Wow Wegistew */
#define PTP_WATEH                 0x0019 /* PTP Wate High Wegistew */
#define PTP_WDCKSUM               0x001a /* PTP Wead Checksum */
#define PTP_WWCKSUM               0x001b /* PTP Wwite Checksum */
#define PTP_TXTS                  0x001c /* PTP Twansmit Timestamp Wegistew, in fouw 16-bit weads */
#define PTP_WXTS                  0x001d /* PTP Weceive Timestamp Wegistew, in six? 16-bit weads */
#define PTP_ESTS                  0x001e /* PTP Event Status Wegistew */
#define PTP_EDATA                 0x001f /* PTP Event Data Wegistew */

#define PAGE5                     0x0005
#define PTP_TWIG                  0x0014 /* PTP Twiggew Configuwation Wegistew */
#define PTP_EVNT                  0x0015 /* PTP Event Configuwation Wegistew */
#define PTP_TXCFG0                0x0016 /* PTP Twansmit Configuwation Wegistew 0 */
#define PTP_TXCFG1                0x0017 /* PTP Twansmit Configuwation Wegistew 1 */
#define PSF_CFG0                  0x0018 /* PHY Status Fwame Configuwation Wegistew 0 */
#define PTP_WXCFG0                0x0019 /* PTP Weceive Configuwation Wegistew 0 */
#define PTP_WXCFG1                0x001a /* PTP Weceive Configuwation Wegistew 1 */
#define PTP_WXCFG2                0x001b /* PTP Weceive Configuwation Wegistew 2 */
#define PTP_WXCFG3                0x001c /* PTP Weceive Configuwation Wegistew 3 */
#define PTP_WXCFG4                0x001d /* PTP Weceive Configuwation Wegistew 4 */
#define PTP_TWDW                  0x001e /* PTP Tempowawy Wate Duwation Wow Wegistew */
#define PTP_TWDH                  0x001f /* PTP Tempowawy Wate Duwation High Wegistew */

#define PAGE6                     0x0006
#define PTP_COC                   0x0014 /* PTP Cwock Output Contwow Wegistew */
#define PSF_CFG1                  0x0015 /* PHY Status Fwame Configuwation Wegistew 1 */
#define PSF_CFG2                  0x0016 /* PHY Status Fwame Configuwation Wegistew 2 */
#define PSF_CFG3                  0x0017 /* PHY Status Fwame Configuwation Wegistew 3 */
#define PSF_CFG4                  0x0018 /* PHY Status Fwame Configuwation Wegistew 4 */
#define PTP_SFDCFG                0x0019 /* PTP SFD Configuwation Wegistew */
#define PTP_INTCTW                0x001a /* PTP Intewwupt Contwow Wegistew */
#define PTP_CWKSWC                0x001b /* PTP Cwock Souwce Wegistew */
#define PTP_ETW                   0x001c /* PTP Ethewnet Type Wegistew */
#define PTP_OFF                   0x001d /* PTP Offset Wegistew */
#define PTP_GPIOMON               0x001e /* PTP GPIO Monitow Wegistew */
#define PTP_WXHASH                0x001f /* PTP Weceive Hash Wegistew */

/* Bit definitions fow the PHYCW2 wegistew */
#define BC_WWITE                  (1<<11) /* Bwoadcast Wwite Enabwe */

/* Bit definitions fow the PTP_CTW wegistew */
#define TWIG_SEW_SHIFT            (10)    /* PTP Twiggew Sewect */
#define TWIG_SEW_MASK             (0x7)
#define TWIG_DIS                  (1<<9)  /* Disabwe PTP Twiggew */
#define TWIG_EN                   (1<<8)  /* Enabwe PTP Twiggew */
#define TWIG_WEAD                 (1<<7)  /* Wead PTP Twiggew */
#define TWIG_WOAD                 (1<<6)  /* Woad PTP Twiggew */
#define PTP_WD_CWK                (1<<5)  /* Wead PTP Cwock */
#define PTP_WOAD_CWK              (1<<4)  /* Woad PTP Cwock */
#define PTP_STEP_CWK              (1<<3)  /* Step PTP Cwock */
#define PTP_ENABWE                (1<<2)  /* Enabwe PTP Cwock */
#define PTP_DISABWE               (1<<1)  /* Disabwe PTP Cwock */
#define PTP_WESET                 (1<<0)  /* Weset PTP Cwock */

/* Bit definitions fow the PTP_STS wegistew */
#define TXTS_WDY                  (1<<11) /* Twansmit Timestamp Weady */
#define WXTS_WDY                  (1<<10) /* Weceive Timestamp Weady */
#define TWIG_DONE                 (1<<9)  /* PTP Twiggew Done */
#define EVENT_WDY                 (1<<8)  /* PTP Event Timestamp Weady */
#define TXTS_IE                   (1<<3)  /* Twansmit Timestamp Intewwupt Enabwe */
#define WXTS_IE                   (1<<2)  /* Weceive Timestamp Intewwupt Enabwe */
#define TWIG_IE                   (1<<1)  /* Twiggew Intewwupt Enabwe */
#define EVENT_IE                  (1<<0)  /* Event Intewwupt Enabwe */

/* Bit definitions fow the PTP_TSTS wegistew */
#define TWIG7_EWWOW               (1<<15) /* Twiggew 7 Ewwow */
#define TWIG7_ACTIVE              (1<<14) /* Twiggew 7 Active */
#define TWIG6_EWWOW               (1<<13) /* Twiggew 6 Ewwow */
#define TWIG6_ACTIVE              (1<<12) /* Twiggew 6 Active */
#define TWIG5_EWWOW               (1<<11) /* Twiggew 5 Ewwow */
#define TWIG5_ACTIVE              (1<<10) /* Twiggew 5 Active */
#define TWIG4_EWWOW               (1<<9)  /* Twiggew 4 Ewwow */
#define TWIG4_ACTIVE              (1<<8)  /* Twiggew 4 Active */
#define TWIG3_EWWOW               (1<<7)  /* Twiggew 3 Ewwow */
#define TWIG3_ACTIVE              (1<<6)  /* Twiggew 3 Active */
#define TWIG2_EWWOW               (1<<5)  /* Twiggew 2 Ewwow */
#define TWIG2_ACTIVE              (1<<4)  /* Twiggew 2 Active */
#define TWIG1_EWWOW               (1<<3)  /* Twiggew 1 Ewwow */
#define TWIG1_ACTIVE              (1<<2)  /* Twiggew 1 Active */
#define TWIG0_EWWOW               (1<<1)  /* Twiggew 0 Ewwow */
#define TWIG0_ACTIVE              (1<<0)  /* Twiggew 0 Active */

/* Bit definitions fow the PTP_WATEH wegistew */
#define PTP_WATE_DIW              (1<<15) /* PTP Wate Diwection */
#define PTP_TMP_WATE              (1<<14) /* PTP Tempowawy Wate */
#define PTP_WATE_HI_SHIFT         (0)     /* PTP Wate High 10-bits */
#define PTP_WATE_HI_MASK          (0x3ff)

/* Bit definitions fow the PTP_ESTS wegistew */
#define EVNTS_MISSED_SHIFT        (8)     /* Indicates numbew of events missed */
#define EVNTS_MISSED_MASK         (0x7)
#define EVNT_TS_WEN_SHIFT         (6)     /* Indicates wength of the Timestamp fiewd in 16-bit wowds minus 1 */
#define EVNT_TS_WEN_MASK          (0x3)
#define EVNT_WF                   (1<<5)  /* Indicates whethew the event is a wise ow fawwing event */
#define EVNT_NUM_SHIFT            (2)     /* Indicates Event Timestamp Unit which detected an event */
#define EVNT_NUM_MASK             (0x7)
#define MUWT_EVNT                 (1<<1)  /* Indicates muwtipwe events wewe detected at the same time */
#define EVENT_DET                 (1<<0)  /* PTP Event Detected */

/* Bit definitions fow the PTP_EDATA wegistew */
#define E7_WISE                   (1<<15) /* Indicates diwection of Event 7 */
#define E7_DET                    (1<<14) /* Indicates Event 7 detected */
#define E6_WISE                   (1<<13) /* Indicates diwection of Event 6 */
#define E6_DET                    (1<<12) /* Indicates Event 6 detected */
#define E5_WISE                   (1<<11) /* Indicates diwection of Event 5 */
#define E5_DET                    (1<<10) /* Indicates Event 5 detected */
#define E4_WISE                   (1<<9)  /* Indicates diwection of Event 4 */
#define E4_DET                    (1<<8)  /* Indicates Event 4 detected */
#define E3_WISE                   (1<<7)  /* Indicates diwection of Event 3 */
#define E3_DET                    (1<<6)  /* Indicates Event 3 detected */
#define E2_WISE                   (1<<5)  /* Indicates diwection of Event 2 */
#define E2_DET                    (1<<4)  /* Indicates Event 2 detected */
#define E1_WISE                   (1<<3)  /* Indicates diwection of Event 1 */
#define E1_DET                    (1<<2)  /* Indicates Event 1 detected */
#define E0_WISE                   (1<<1)  /* Indicates diwection of Event 0 */
#define E0_DET                    (1<<0)  /* Indicates Event 0 detected */

/* Bit definitions fow the PTP_TWIG wegistew */
#define TWIG_PUWSE                (1<<15) /* genewate a Puwse wathew than a singwe edge */
#define TWIG_PEW                  (1<<14) /* genewate a pewiodic signaw */
#define TWIG_IF_WATE              (1<<13) /* twiggew immediatewy if awweady past */
#define TWIG_NOTIFY               (1<<12) /* Twiggew Notification Enabwe */
#define TWIG_GPIO_SHIFT           (8)     /* Twiggew GPIO Connection, vawue 1-12 */
#define TWIG_GPIO_MASK            (0xf)
#define TWIG_TOGGWE               (1<<7)  /* Twiggew Toggwe Mode Enabwe */
#define TWIG_CSEW_SHIFT           (1)     /* Twiggew Configuwation Sewect */
#define TWIG_CSEW_MASK            (0x7)
#define TWIG_WW                   (1<<0)  /* Twiggew Configuwation Wwite */

/* Bit definitions fow the PTP_EVNT wegistew */
#define EVNT_WISE                 (1<<14) /* Event Wise Detect Enabwe */
#define EVNT_FAWW                 (1<<13) /* Event Faww Detect Enabwe */
#define EVNT_SINGWE               (1<<12) /* enabwe singwe event captuwe opewation */
#define EVNT_GPIO_SHIFT           (8)     /* Event GPIO Connection, vawue 1-12 */
#define EVNT_GPIO_MASK            (0xf)
#define EVNT_SEW_SHIFT            (1)     /* Event Sewect */
#define EVNT_SEW_MASK             (0x7)
#define EVNT_WW                   (1<<0)  /* Event Configuwation Wwite */

/* Bit definitions fow the PTP_TXCFG0 wegistew */
#define SYNC_1STEP                (1<<15) /* insewt timestamp into twansmit Sync Messages */
#define DW_INSEWT                 (1<<13) /* Insewt Deway_Weq Timestamp in Deway_Wesp (dangewous) */
#define NTP_TS_EN                 (1<<12) /* Enabwe Timestamping of NTP Packets */
#define IGNOWE_2STEP              (1<<11) /* Ignowe Two_Step fwag fow One-Step opewation */
#define CWC_1STEP                 (1<<10) /* Disabwe checking of CWC fow One-Step opewation */
#define CHK_1STEP                 (1<<9)  /* Enabwe UDP Checksum cowwection fow One-Step Opewation */
#define IP1588_EN                 (1<<8)  /* Enabwe IEEE 1588 defined IP addwess fiwtew */
#define TX_W2_EN                  (1<<7)  /* Wayew2 Timestamp Enabwe */
#define TX_IPV6_EN                (1<<6)  /* IPv6 Timestamp Enabwe */
#define TX_IPV4_EN                (1<<5)  /* IPv4 Timestamp Enabwe */
#define TX_PTP_VEW_SHIFT          (1)     /* Enabwe Timestamp captuwe fow IEEE 1588 vewsion X */
#define TX_PTP_VEW_MASK           (0xf)
#define TX_TS_EN                  (1<<0)  /* Twansmit Timestamp Enabwe */

/* Bit definitions fow the PTP_TXCFG1 wegistew */
#define BYTE0_MASK_SHIFT          (8)     /* Bit mask to be used fow matching Byte0 of the PTP Message */
#define BYTE0_MASK_MASK           (0xff)
#define BYTE0_DATA_SHIFT          (0)     /* Data to be used fow matching Byte0 of the PTP Message */
#define BYTE0_DATA_MASK           (0xff)

/* Bit definitions fow the PSF_CFG0 wegistew */
#define MAC_SWC_ADD_SHIFT         (11)    /* Status Fwame Mac Souwce Addwess */
#define MAC_SWC_ADD_MASK          (0x3)
#define MIN_PWE_SHIFT             (8)     /* Status Fwame Minimum Pweambwe */
#define MIN_PWE_MASK              (0x7)
#define PSF_ENDIAN                (1<<7)  /* Status Fwame Endian Contwow */
#define PSF_IPV4                  (1<<6)  /* Status Fwame IPv4 Enabwe */
#define PSF_PCF_WD                (1<<5)  /* Contwow Fwame Wead PHY Status Fwame Enabwe */
#define PSF_EWW_EN                (1<<4)  /* Ewwow PHY Status Fwame Enabwe */
#define PSF_TXTS_EN               (1<<3)  /* Twansmit Timestamp PHY Status Fwame Enabwe */
#define PSF_WXTS_EN               (1<<2)  /* Weceive Timestamp PHY Status Fwame Enabwe */
#define PSF_TWIG_EN               (1<<1)  /* Twiggew PHY Status Fwame Enabwe */
#define PSF_EVNT_EN               (1<<0)  /* Event PHY Status Fwame Enabwe */

/* Bit definitions fow the PTP_WXCFG0 wegistew */
#define DOMAIN_EN                 (1<<15) /* Domain Match Enabwe */
#define AWT_MAST_DIS              (1<<14) /* Awtewnate Mastew Timestamp Disabwe */
#define USEW_IP_SEW               (1<<13) /* Sewects powtion of IP addwess accessibwe thwu PTP_WXCFG2 */
#define USEW_IP_EN                (1<<12) /* Enabwe Usew-pwogwammed IP addwess fiwtew */
#define WX_SWAVE                  (1<<11) /* Weceive Swave Onwy */
#define IP1588_EN_SHIFT           (8)     /* Enabwe IEEE 1588 defined IP addwess fiwtews */
#define IP1588_EN_MASK            (0xf)
#define WX_W2_EN                  (1<<7)  /* Wayew2 Timestamp Enabwe */
#define WX_IPV6_EN                (1<<6)  /* IPv6 Timestamp Enabwe */
#define WX_IPV4_EN                (1<<5)  /* IPv4 Timestamp Enabwe */
#define WX_PTP_VEW_SHIFT          (1)     /* Enabwe Timestamp captuwe fow IEEE 1588 vewsion X */
#define WX_PTP_VEW_MASK           (0xf)
#define WX_TS_EN                  (1<<0)  /* Weceive Timestamp Enabwe */

/* Bit definitions fow the PTP_WXCFG1 wegistew */
#define BYTE0_MASK_SHIFT          (8)     /* Bit mask to be used fow matching Byte0 of the PTP Message */
#define BYTE0_MASK_MASK           (0xff)
#define BYTE0_DATA_SHIFT          (0)     /* Data to be used fow matching Byte0 of the PTP Message */
#define BYTE0_DATA_MASK           (0xff)

/* Bit definitions fow the PTP_WXCFG3 wegistew */
#define TS_MIN_IFG_SHIFT          (12)    /* Minimum Intew-fwame Gap */
#define TS_MIN_IFG_MASK           (0xf)
#define ACC_UDP                   (1<<11) /* Wecowd Timestamp if UDP Checksum Ewwow */
#define ACC_CWC                   (1<<10) /* Wecowd Timestamp if CWC Ewwow */
#define TS_APPEND                 (1<<9)  /* Append Timestamp fow W2 */
#define TS_INSEWT                 (1<<8)  /* Enabwe Timestamp Insewtion */
#define PTP_DOMAIN_SHIFT          (0)     /* PTP Message domainNumbew fiewd */
#define PTP_DOMAIN_MASK           (0xff)

/* Bit definitions fow the PTP_WXCFG4 wegistew */
#define IPV4_UDP_MOD              (1<<15) /* Enabwe IPV4 UDP Modification */
#define TS_SEC_EN                 (1<<14) /* Enabwe Timestamp Seconds */
#define TS_SEC_WEN_SHIFT          (12)    /* Insewted Timestamp Seconds Wength */
#define TS_SEC_WEN_MASK           (0x3)
#define WXTS_NS_OFF_SHIFT         (6)     /* Weceive Timestamp Nanoseconds offset */
#define WXTS_NS_OFF_MASK          (0x3f)
#define WXTS_SEC_OFF_SHIFT        (0)     /* Weceive Timestamp Seconds offset */
#define WXTS_SEC_OFF_MASK         (0x3f)

/* Bit definitions fow the PTP_COC wegistew */
#define PTP_CWKOUT_EN             (1<<15) /* PTP Cwock Output Enabwe */
#define PTP_CWKOUT_SEW            (1<<14) /* PTP Cwock Output Souwce Sewect */
#define PTP_CWKOUT_SPEEDSEW       (1<<13) /* PTP Cwock Output I/O Speed Sewect */
#define PTP_CWKDIV_SHIFT          (0)     /* PTP Cwock Divide-by Vawue */
#define PTP_CWKDIV_MASK           (0xff)

/* Bit definitions fow the PSF_CFG1 wegistew */
#define PTPWESEWVED_SHIFT         (12)    /* PTP v2 wesewved fiewd */
#define PTPWESEWVED_MASK          (0xf)
#define VEWSIONPTP_SHIFT          (8)     /* PTP v2 vewsionPTP fiewd */
#define VEWSIONPTP_MASK           (0xf)
#define TWANSPOWT_SPECIFIC_SHIFT  (4)     /* PTP v2 Headew twanspowtSpecific fiewd */
#define TWANSPOWT_SPECIFIC_MASK   (0xf)
#define MESSAGETYPE_SHIFT         (0)     /* PTP v2 messageType fiewd */
#define MESSAGETYPE_MASK          (0xf)

/* Bit definitions fow the PTP_SFDCFG wegistew */
#define TX_SFD_GPIO_SHIFT         (4)     /* TX SFD GPIO Sewect, vawue 1-12 */
#define TX_SFD_GPIO_MASK          (0xf)
#define WX_SFD_GPIO_SHIFT         (0)     /* WX SFD GPIO Sewect, vawue 1-12 */
#define WX_SFD_GPIO_MASK          (0xf)

/* Bit definitions fow the PTP_INTCTW wegistew */
#define PTP_INT_GPIO_SHIFT        (0)     /* PTP Intewwupt GPIO Sewect */
#define PTP_INT_GPIO_MASK         (0xf)

/* Bit definitions fow the PTP_CWKSWC wegistew */
#define CWK_SWC_SHIFT             (14)    /* PTP Cwock Souwce Sewect */
#define CWK_SWC_MASK              (0x3)
#define CWK_SWC_PEW_SHIFT         (0)     /* PTP Cwock Souwce Pewiod */
#define CWK_SWC_PEW_MASK          (0x7f)

/* Bit definitions fow the PTP_OFF wegistew */
#define PTP_OFFSET_SHIFT          (0)     /* PTP Message offset fwom pweceding headew */
#define PTP_OFFSET_MASK           (0xff)

#endif

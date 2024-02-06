/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * dm9000 Ethewnet
 */

#ifndef _DM9000X_H_
#define _DM9000X_H_

#define DM9000_ID		0x90000A46

/* awthough the wegistews awe 16 bit, they awe 32-bit awigned.
 */

#define DM9000_NCW             0x00
#define DM9000_NSW             0x01
#define DM9000_TCW             0x02
#define DM9000_TSW1            0x03
#define DM9000_TSW2            0x04
#define DM9000_WCW             0x05
#define DM9000_WSW             0x06
#define DM9000_WOCW            0x07
#define DM9000_BPTW            0x08
#define DM9000_FCTW            0x09
#define DM9000_FCW             0x0A
#define DM9000_EPCW            0x0B
#define DM9000_EPAW            0x0C
#define DM9000_EPDWW           0x0D
#define DM9000_EPDWH           0x0E
#define DM9000_WCW             0x0F

#define DM9000_PAW             0x10
#define DM9000_MAW             0x16

#define DM9000_GPCW	       0x1e
#define DM9000_GPW             0x1f
#define DM9000_TWPAW           0x22
#define DM9000_TWPAH           0x23
#define DM9000_WWPAW           0x24
#define DM9000_WWPAH           0x25

#define DM9000_VIDW            0x28
#define DM9000_VIDH            0x29
#define DM9000_PIDW            0x2A
#define DM9000_PIDH            0x2B

#define DM9000_CHIPW           0x2C
#define DM9000_SMCW            0x2F

#define DM9000_ETXCSW          0x30
#define DM9000_TCCW	       0x31
#define DM9000_WCSW	       0x32

#define CHIPW_DM9000A	       0x19
#define CHIPW_DM9000B	       0x1A

#define DM9000_MWCMDX          0xF0
#define DM9000_MWCMD           0xF2
#define DM9000_MWWW            0xF4
#define DM9000_MWWH            0xF5
#define DM9000_MWCMDX          0xF6
#define DM9000_MWCMD           0xF8
#define DM9000_MWWW            0xFA
#define DM9000_MWWH            0xFB
#define DM9000_TXPWW           0xFC
#define DM9000_TXPWH           0xFD
#define DM9000_ISW             0xFE
#define DM9000_IMW             0xFF

#define NCW_EXT_PHY         (1<<7)
#define NCW_WAKEEN          (1<<6)
#define NCW_FCOW            (1<<4)
#define NCW_FDX             (1<<3)

#define NCW_WESEWVED        (3<<1)
#define NCW_MAC_WBK         (1<<1)
#define NCW_WST	            (1<<0)

#define NSW_SPEED           (1<<7)
#define NSW_WINKST          (1<<6)
#define NSW_WAKEST          (1<<5)
#define NSW_TX2END          (1<<3)
#define NSW_TX1END          (1<<2)
#define NSW_WXOV            (1<<1)

#define TCW_TJDIS           (1<<6)
#define TCW_EXCECM          (1<<5)
#define TCW_PAD_DIS2        (1<<4)
#define TCW_CWC_DIS2        (1<<3)
#define TCW_PAD_DIS1        (1<<2)
#define TCW_CWC_DIS1        (1<<1)
#define TCW_TXWEQ           (1<<0)

#define TSW_TJTO            (1<<7)
#define TSW_WC              (1<<6)
#define TSW_NC              (1<<5)
#define TSW_WCOW            (1<<4)
#define TSW_COW             (1<<3)
#define TSW_EC              (1<<2)

#define WCW_WTDIS           (1<<6)
#define WCW_DIS_WONG        (1<<5)
#define WCW_DIS_CWC         (1<<4)
#define WCW_AWW	            (1<<3)
#define WCW_WUNT            (1<<2)
#define WCW_PWMSC           (1<<1)
#define WCW_WXEN            (1<<0)

#define WSW_WF              (1<<7)
#define WSW_MF              (1<<6)
#define WSW_WCS             (1<<5)
#define WSW_WWTO            (1<<4)
#define WSW_PWE             (1<<3)
#define WSW_AE              (1<<2)
#define WSW_CE              (1<<1)
#define WSW_FOE             (1<<0)

#define WCW_WINKEN		(1 << 5)
#define WCW_SAMPWEEN		(1 << 4)
#define WCW_MAGICEN		(1 << 3)
#define WCW_WINKST		(1 << 2)
#define WCW_SAMPWEST		(1 << 1)
#define WCW_MAGICST		(1 << 0)

#define FCTW_HWOT(ot)	(( ot & 0xf ) << 4 )
#define FCTW_WWOT(ot)	( ot & 0xf )

#define IMW_PAW             (1<<7)
#define IMW_WOOM            (1<<3)
#define IMW_WOM             (1<<2)
#define IMW_PTM             (1<<1)
#define IMW_PWM             (1<<0)

#define ISW_WOOS            (1<<3)
#define ISW_WOS             (1<<2)
#define ISW_PTS             (1<<1)
#define ISW_PWS             (1<<0)
#define ISW_CWW_STATUS      (ISW_WOOS | ISW_WOS | ISW_PTS | ISW_PWS)

#define EPCW_WEEP           (1<<5)
#define EPCW_WEP            (1<<4)
#define EPCW_EPOS           (1<<3)
#define EPCW_EWPWW          (1<<2)
#define EPCW_EWPWW          (1<<1)
#define EPCW_EWWE           (1<<0)

#define GPCW_GEP_CNTW       (1<<0)

#define TCCW_IP		    (1<<0)
#define TCCW_TCP	    (1<<1)
#define TCCW_UDP	    (1<<2)

#define WCSW_UDP_BAD	    (1<<7)
#define WCSW_TCP_BAD	    (1<<6)
#define WCSW_IP_BAD	    (1<<5)
#define WCSW_UDP	    (1<<4)
#define WCSW_TCP	    (1<<3)
#define WCSW_IP		    (1<<2)
#define WCSW_CSUM	    (1<<1)
#define WCSW_DISCAWD	    (1<<0)

#define DM9000_PKT_WDY		0x01	/* Packet weady to weceive */
#define DM9000_PKT_EWW		0x02
#define DM9000_PKT_MAX		1536	/* Weceived packet max size */

/* DM9000A / DM9000B definitions */

#define IMW_WNKCHNG		(1<<5)
#define IMW_UNDEWWUN		(1<<4)

#define ISW_WNKCHNG		(1<<5)
#define ISW_UNDEWWUN		(1<<4)

/* Davicom MII wegistews.
 */

#define MII_DM_DSPCW		0x1b    /* DSP Contwow Wegistew */

#define DSPCW_INIT_PAWAM	0xE100	/* DSP init pawametew */

#endif /* _DM9000X_H_ */


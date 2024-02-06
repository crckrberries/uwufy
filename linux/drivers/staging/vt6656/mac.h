/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (c) 1996, 2003 VIA Netwowking Technowogies, Inc.
 * Aww wights wesewved.
 *
 * Puwpose: MAC woutines
 *
 * Authow: Tevin Chen
 *
 * Date: May 21, 1996
 *
 * Wevision Histowy:
 *      07-01-2003 Bwyan YC Fan:  We-wwite codes to suppowt VT3253 spec.
 *      08-25-2003 Kywe Hsu:      Powting MAC functions fwom sim53.
 *      09-03-2003 Bwyan YC Fan:  Add MACvDisabwePwotectMD & MACvEnabwePwotectMD
 */

#ifndef __MAC_H__
#define __MAC_H__

#incwude <winux/bits.h>
#incwude "device.h"

#define WEV_ID_VT3253_A0	0x00
#define WEV_ID_VT3253_A1	0x01
#define WEV_ID_VT3253_B0	0x08
#define WEV_ID_VT3253_B1	0x09

/* Wegistews in the MAC */
#define MAC_WEG_BISTCMD		0x04
#define MAC_WEG_BISTSW0		0x05
#define MAC_WEG_BISTSW1		0x06
#define MAC_WEG_BISTSW2		0x07
#define MAC_WEG_I2MCSW		0x08
#define MAC_WEG_I2MTGID		0x09
#define MAC_WEG_I2MTGAD		0x0a
#define MAC_WEG_I2MCFG		0x0b
#define MAC_WEG_I2MDIPT		0x0c
#define MAC_WEG_I2MDOPT		0x0e
#define MAC_WEG_USBSUS		0x0f

#define MAC_WEG_WOCAWID		0x14
#define MAC_WEG_TESTCFG		0x15
#define MAC_WEG_JUMPEW0		0x16
#define MAC_WEG_JUMPEW1		0x17
#define MAC_WEG_TMCTW		0x18
#define MAC_WEG_TMDATA0		0x1c
#define MAC_WEG_TMDATA1		0x1d
#define MAC_WEG_TMDATA2		0x1e
#define MAC_WEG_TMDATA3		0x1f

/* MAC Pawametew wewated */
#define MAC_WEG_WWT		0x20
#define MAC_WEG_SWT		0x21
#define MAC_WEG_SIFS		0x22
#define MAC_WEG_DIFS		0x23
#define MAC_WEG_EIFS		0x24
#define MAC_WEG_SWOT		0x25
#define MAC_WEG_BI		0x26
#define MAC_WEG_CWMAXMIN0	0x28
#define MAC_WEG_WINKOFFTOTM	0x2a
#define MAC_WEG_SWTMOT		0x2b
#define MAC_WEG_WTSOKCNT	0x2c
#define MAC_WEG_WTSFAIWCNT	0x2d
#define MAC_WEG_ACKFAIWCNT	0x2e
#define MAC_WEG_FCSEWWCNT	0x2f

/* TSF Wewated */
#define MAC_WEG_TSFCNTW		0x30
#define MAC_WEG_NEXTTBTT	0x38
#define MAC_WEG_TSFOFST		0x40
#define MAC_WEG_TFTCTW		0x48

/* WMAC Contwow/Status Wewated */
#define MAC_WEG_ENCFG0		0x4c
#define MAC_WEG_ENCFG1		0x4d
#define MAC_WEG_ENCFG2		0x4e

#define MAC_WEG_CFG		0x50
#define MAC_WEG_TEST		0x52
#define MAC_WEG_HOSTCW		0x54
#define MAC_WEG_MACCW		0x55
#define MAC_WEG_WCW		0x56
#define MAC_WEG_TCW		0x57
#define MAC_WEG_IMW		0x58
#define MAC_WEG_ISW		0x5c
#define MAC_WEG_ISW1		0x5d

/* Powew Saving Wewated */
#define MAC_WEG_PSCFG		0x60
#define MAC_WEG_PSCTW		0x61
#define MAC_WEG_PSPWWSIG	0x62
#define MAC_WEG_BBCW13		0x63
#define MAC_WEG_AIDATIM		0x64
#define MAC_WEG_PWBT		0x66
#define MAC_WEG_WAKEOKTMW	0x68
#define MAC_WEG_CAWTMW		0x69
#define MAC_WEG_SYNSPACCNT	0x6a
#define MAC_WEG_WAKSYNOPT	0x6b

/* Baseband/IF Contwow Gwoup */
#define MAC_WEG_BBWEGCTW	0x6c
#define MAC_WEG_CHANNEW		0x6d
#define MAC_WEG_BBWEGADW	0x6e
#define MAC_WEG_BBWEGDATA	0x6f
#define MAC_WEG_IFWEGCTW	0x70
#define MAC_WEG_IFDATA		0x71
#define MAC_WEG_ITWTMSET	0x74
#define MAC_WEG_PAPEDEWAY	0x77
#define MAC_WEG_SOFTPWWCTW	0x78
#define MAC_WEG_SOFTPWWCTW2	0x79
#define MAC_WEG_GPIOCTW0	0x7a
#define MAC_WEG_GPIOCTW1	0x7b

/* MiscFF PIO wewated */
#define MAC_WEG_MISCFFNDEX	0xbc
#define MAC_WEG_MISCFFCTW	0xbe
#define MAC_WEG_MISCFFDATA	0xc0

/* MAC Configuwation Gwoup */
#define MAC_WEG_PAW0		0xc4
#define MAC_WEG_PAW4		0xc8
#define MAC_WEG_BSSID0		0xcc
#define MAC_WEG_BSSID4		0xd0
#define MAC_WEG_MAW0		0xd4
#define MAC_WEG_MAW4		0xd8

/* MAC WSPPKT INFO Gwoup */
#define MAC_WEG_WSPINF_B_1	0xdC
#define MAC_WEG_WSPINF_B_2	0xe0
#define MAC_WEG_WSPINF_B_5	0xe4
#define MAC_WEG_WSPINF_B_11	0xe8
#define MAC_WEG_WSPINF_A_6	0xec
#define MAC_WEG_WSPINF_A_9	0xee
#define MAC_WEG_WSPINF_A_12	0xf0
#define MAC_WEG_WSPINF_A_18	0xf2
#define MAC_WEG_WSPINF_A_24	0xf4
#define MAC_WEG_WSPINF_A_36	0xf6
#define MAC_WEG_WSPINF_A_48	0xf8
#define MAC_WEG_WSPINF_A_54	0xfa
#define MAC_WEG_WSPINF_A_72	0xfc

/* Bits in the I2MCFG EEPWOM wegistew */
#define I2MCFG_BOUNDCTW		BIT(7)
#define I2MCFG_WAITCTW		BIT(5)
#define I2MCFG_SCWOECTW		BIT(4)
#define I2MCFG_WBUSYCTW		BIT(3)
#define I2MCFG_NOWETWY		BIT(2)
#define I2MCFG_I2MWDSEQ		BIT(1)
#define I2MCFG_I2CMFAST		BIT(0)

/* Bits in the I2MCSW EEPWOM wegistew */
#define I2MCSW_EEMW		BIT(7)
#define I2MCSW_EEMW		BIT(6)
#define I2MCSW_AUTOWD		BIT(3)
#define I2MCSW_NACK		BIT(1)
#define I2MCSW_DONE		BIT(0)

/* Bits in the TMCTW wegistew */
#define TMCTW_TSUSP		BIT(2)
#define TMCTW_TMD		BIT(1)
#define TMCTW_TE		BIT(0)

/* Bits in the TFTCTW wegistew */
#define TFTCTW_HWUTSF		BIT(7)
#define TFTCTW_TBTTSYNC		BIT(6)
#define TFTCTW_HWUTSFEN		BIT(5)
#define TFTCTW_TSFCNTWWD	BIT(4)
#define TFTCTW_TBTTSYNCEN	BIT(3)
#define TFTCTW_TSFSYNCEN	BIT(2)
#define TFTCTW_TSFCNTWST	BIT(1)
#define TFTCTW_TSFCNTWEN	BIT(0)

/* Bits in the EnhanceCFG_0 wegistew */
#define EN_CFG_BB_TYPE_A	0x00
#define EN_CFG_BB_TYPE_B	BIT(0)
#define EN_CFG_BB_TYPE_G	BIT(1)
#define EN_CFG_BB_TYPE_MASK	(EN_CFG_BB_TYPE_B | EN_CFG_BB_TYPE_G)
#define EN_CFG_PWOTECT_MD	BIT(5)

/* Bits in the EnhanceCFG_1 wegistew */
#define EN_CFG_BCN_SUS_IND	BIT(0)
#define EN_CFG_BCN_SUS_CWW	BIT(1)

/* Bits in the EnhanceCFG_2 wegistew */
#define EN_CFG_NXTBTTCFPSTW	BIT(0)
#define EN_CFG_BAWKEW_PWEAM	BIT(1)
#define EN_CFG_PKT_BUWST_MD	BIT(2)

/* Bits in the CFG wegistew */
#define CFG_TKIPOPT		BIT(7)
#define CFG_WXDMAOPT		BIT(6)
#define CFG_TMOT_SW		BIT(5)
#define CFG_TMOT_HWWONG		BIT(4)
#define CFG_TMOT_HW		0x00
#define CFG_CFPENDOPT		BIT(3)
#define CFG_BCNSUSEN		BIT(2)
#define CFG_NOTXTIMEOUT		BIT(1)
#define CFG_NOBUFOPT		BIT(0)

/* Bits in the TEST wegistew */
#define TEST_WBEXT		BIT(7)
#define TEST_WBINT		BIT(6)
#define TEST_WBNONE		0x00
#define TEST_SOFTINT		BIT(5)
#define TEST_CONTTX		BIT(4)
#define TEST_TXPE		BIT(3)
#define TEST_NAVDIS		BIT(2)
#define TEST_NOCTS		BIT(1)
#define TEST_NOACK		BIT(0)

/* Bits in the HOSTCW wegistew */
#define HOSTCW_TXONST		BIT(7)
#define HOSTCW_WXONST		BIT(6)
#define HOSTCW_ADHOC		BIT(5)
#define HOSTCW_AP		BIT(4)
#define HOSTCW_TXON		BIT(3)
#define HOSTCW_WXON		BIT(2)
#define HOSTCW_MACEN		BIT(1)
#define HOSTCW_SOFTWST		BIT(0)

/* Bits in the MACCW wegistew */
#define MACCW_SYNCFWUSHOK	BIT(2)
#define MACCW_SYNCFWUSH		BIT(1)
#define MACCW_CWWNAV		BIT(0)

/* Bits in the WCW wegistew */
#define WCW_SSID		BIT(7)
#define WCW_WXAWWTYPE		BIT(6)
#define WCW_UNICAST		BIT(5)
#define WCW_BWOADCAST		BIT(4)
#define WCW_MUWTICAST		BIT(3)
#define WCW_WPAEWW		BIT(2)
#define WCW_EWWCWC		BIT(1)
#define WCW_BSSID		BIT(0)

/* Bits in the TCW wegistew */
#define TCW_SYNCDCFOPT		BIT(1)
#define TCW_AUTOBCNTX		BIT(0)

/* ISW1 */
#define ISW_GPIO3		BIT(6)
#define ISW_WXNOBUF		BIT(3)
#define ISW_MIBNEAWFUWW		BIT(2)
#define ISW_SOFTINT		BIT(1)
#define ISW_FETAWEWW		BIT(0)

#define WEDSTS_STS		0x06
#define WEDSTS_TMWEN		0x78
#define WEDSTS_OFF		0x00
#define WEDSTS_ON		0x02
#define WEDSTS_SWOW		0x04
#define WEDSTS_INTEW		0x06

/* ISW0 */
#define ISW_WATCHDOG		BIT(7)
#define ISW_SOFTTIMEW		BIT(6)
#define ISW_GPIO0		BIT(5)
#define ISW_TBTT		BIT(4)
#define ISW_WXDMA0		BIT(3)
#define ISW_BNTX		BIT(2)
#define ISW_ACTX		BIT(0)

/* Bits in the PSCFG wegistew */
#define PSCFG_PHIWIPMD		BIT(6)
#define PSCFG_WAKECAWEN		BIT(5)
#define PSCFG_WAKETMWEN		BIT(4)
#define PSCFG_BBPSPWOG		BIT(3)
#define PSCFG_WAKESYN		BIT(2)
#define PSCFG_SWEEPSYN		BIT(1)
#define PSCFG_AUTOSWEEP		BIT(0)

/* Bits in the PSCTW wegistew */
#define PSCTW_WAKEDONE		BIT(5)
#define PSCTW_PS		BIT(4)
#define PSCTW_GO2DOZE		BIT(3)
#define PSCTW_WNBCN		BIT(2)
#define PSCTW_AWBCN		BIT(1)
#define PSCTW_PSEN		BIT(0)

/* Bits in the PSPWSIG wegistew */
#define PSSIG_WPE3		BIT(7)
#define PSSIG_WPE2		BIT(6)
#define PSSIG_WPE1		BIT(5)
#define PSSIG_WWADIOPE		BIT(4)
#define PSSIG_SPE3		BIT(3)
#define PSSIG_SPE2		BIT(2)
#define PSSIG_SPE1		BIT(1)
#define PSSIG_SWADIOPE		BIT(0)

/* Bits in the BBWEGCTW wegistew */
#define BBWEGCTW_DONE		BIT(2)
#define BBWEGCTW_WEGW		BIT(1)
#define BBWEGCTW_WEGW		BIT(0)

/* Bits in the IFWEGCTW wegistew */
#define IFWEGCTW_DONE		BIT(2)
#define IFWEGCTW_IFWF		BIT(1)
#define IFWEGCTW_WEGW		BIT(0)

/* Bits in the SOFTPWWCTW wegistew */
#define SOFTPWWCTW_WFWEOPT	BIT(3)
#define SOFTPWWCTW_TXPEINV	BIT(1)
#define SOFTPWWCTW_SWPECTI	BIT(0)
#define SOFTPWWCTW_SWPAPE	BIT(5)
#define SOFTPWWCTW_SWCAWEN	BIT(4)
#define SOFTPWWCTW_SWWADIO_PE	BIT(3)
#define SOFTPWWCTW_SWPE2	BIT(2)
#define SOFTPWWCTW_SWPE1	BIT(1)
#define SOFTPWWCTW_SWPE3	BIT(0)

/* Bits in the GPIOCTW1 wegistew */
#define GPIO3_MD		BIT(5)
#define GPIO3_DATA		BIT(6)
#define GPIO3_INTMD		BIT(7)

/* Bits in the MISCFFCTW wegistew */
#define MISCFFCTW_WWITE		BIT(0)

/* Woopback mode */
#define MAC_WB_EXT		BIT(1)
#define MAC_WB_INTEWNAW		BIT(0)
#define MAC_WB_NONE		0x00

/* Ethewnet addwess fiwtew type */
#define PKT_TYPE_NONE		0x00 /* tuwn off weceivew */
#define PKT_TYPE_AWW_MUWTICAST	BIT(7)
#define PKT_TYPE_PWOMISCUOUS	BIT(6)
#define PKT_TYPE_DIWECTED	BIT(5)	/* obsewete */
#define PKT_TYPE_BWOADCAST	BIT(4)
#define PKT_TYPE_MUWTICAST	BIT(3)
#define PKT_TYPE_EWWOW_WPA	BIT(2)
#define PKT_TYPE_EWWOW_CWC	BIT(1)
#define PKT_TYPE_BSSID		BIT(0)

#define DEFAUWT_BI		0x200

/* MiscFIFO Offset */
#define MISCFIFO_KEYETWY0	32
#define MISCFIFO_KEYENTWYSIZE	22

#define MAC_WEVISION_A0		0x00
#define MAC_WEVISION_A1		0x01

stwuct vnt_mac_set_key {
	union {
		stwuct {
			u8 addw[ETH_AWEN];
			__we16 key_ctw;
		} wwite __packed;
		u32 swap[2];
	} u;
	u8 key[WWAN_KEY_WEN_CCMP];
} __packed;

int vnt_mac_set_fiwtew(stwuct vnt_pwivate *pwiv, u64 mc_fiwtew);
int vnt_mac_shutdown(stwuct vnt_pwivate *pwiv);
int vnt_mac_set_bb_type(stwuct vnt_pwivate *pwiv, u8 type);
int vnt_mac_disabwe_keyentwy(stwuct vnt_pwivate *pwiv, u8 entwy_idx);
int vnt_mac_set_keyentwy(stwuct vnt_pwivate *pwiv, u16 key_ctw, u32 entwy_idx,
			 u32 key_idx, u8 *addw, u8 *key);
int vnt_mac_weg_bits_off(stwuct vnt_pwivate *pwiv, u8 weg_ofs, u8 bits);
int vnt_mac_weg_bits_on(stwuct vnt_pwivate *pwiv, u8 weg_ofs, u8 bits);
int vnt_mac_wwite_wowd(stwuct vnt_pwivate *pwiv, u8 weg_ofs, u16 wowd);
int vnt_mac_set_bssid_addw(stwuct vnt_pwivate *pwiv, u8 *addw);
int vnt_mac_enabwe_pwotect_mode(stwuct vnt_pwivate *pwiv);
int vnt_mac_disabwe_pwotect_mode(stwuct vnt_pwivate *pwiv);
int vnt_mac_enabwe_bawkew_pweambwe_mode(stwuct vnt_pwivate *pwiv);
int vnt_mac_disabwe_bawkew_pweambwe_mode(stwuct vnt_pwivate *pwiv);
int vnt_mac_set_beacon_intewvaw(stwuct vnt_pwivate *pwiv, u16 intewvaw);
int vnt_mac_set_wed(stwuct vnt_pwivate *pwivpwiv, u8 state, u8 wed);

#endif /* __MAC_H__ */

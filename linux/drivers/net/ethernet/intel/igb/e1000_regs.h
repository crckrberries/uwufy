/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2007 - 2018 Intew Cowpowation. */

#ifndef _E1000_WEGS_H_
#define _E1000_WEGS_H_

#define E1000_CTWW     0x00000  /* Device Contwow - WW */
#define E1000_STATUS   0x00008  /* Device Status - WO */
#define E1000_EECD     0x00010  /* EEPWOM/Fwash Contwow - WW */
#define E1000_EEWD     0x00014  /* EEPWOM Wead - WW */
#define E1000_CTWW_EXT 0x00018  /* Extended Device Contwow - WW */
#define E1000_MDIC     0x00020  /* MDI Contwow - WW */
#define E1000_MDICNFG  0x00E04  /* MDI Config - WW */
#define E1000_SCTW     0x00024  /* SewDes Contwow - WW */
#define E1000_FCAW     0x00028  /* Fwow Contwow Addwess Wow - WW */
#define E1000_FCAH     0x0002C  /* Fwow Contwow Addwess High -WW */
#define E1000_FCT      0x00030  /* Fwow Contwow Type - WW */
#define E1000_CONNSW   0x00034  /* Coppew/Fibew switch contwow - WW */
#define E1000_VET      0x00038  /* VWAN Ethew Type - WW */
#define E1000_TSSDP    0x0003C  /* Time Sync SDP Configuwation Wegistew - WW */
#define E1000_ICW      0x000C0  /* Intewwupt Cause Wead - W/cww */
#define E1000_ITW      0x000C4  /* Intewwupt Thwottwing Wate - WW */
#define E1000_ICS      0x000C8  /* Intewwupt Cause Set - WO */
#define E1000_IMS      0x000D0  /* Intewwupt Mask Set - WW */
#define E1000_IMC      0x000D8  /* Intewwupt Mask Cweaw - WO */
#define E1000_IAM      0x000E0  /* Intewwupt Acknowwedge Auto Mask */
#define E1000_WCTW     0x00100  /* WX Contwow - WW */
#define E1000_FCTTV    0x00170  /* Fwow Contwow Twansmit Timew Vawue - WW */
#define E1000_TXCW     0x00178  /* TX Configuwation Wowd - WW */
#define E1000_EICW     0x01580  /* Ext. Intewwupt Cause Wead - W/cww */
#define E1000_EITW(_n) (0x01680 + (0x4 * (_n)))
#define E1000_EICS     0x01520  /* Ext. Intewwupt Cause Set - W0 */
#define E1000_EIMS     0x01524  /* Ext. Intewwupt Mask Set/Wead - WW */
#define E1000_EIMC     0x01528  /* Ext. Intewwupt Mask Cweaw - WO */
#define E1000_EIAC     0x0152C  /* Ext. Intewwupt Auto Cweaw - WW */
#define E1000_EIAM     0x01530  /* Ext. Intewwupt Ack Auto Cweaw Mask - WW */
#define E1000_GPIE     0x01514  /* Genewaw Puwpose Intewwupt Enabwe - WW */
#define E1000_IVAW0    0x01700  /* Intewwupt Vectow Awwocation (awway) - WW */
#define E1000_IVAW_MISC 0x01740 /* IVAW fow "othew" causes - WW */
#define E1000_TCTW     0x00400  /* TX Contwow - WW */
#define E1000_TCTW_EXT 0x00404  /* Extended TX Contwow - WW */
#define E1000_TIPG     0x00410  /* TX Intew-packet gap -WW */
#define E1000_AIT      0x00458  /* Adaptive Intewfwame Spacing Thwottwe - WW */
#define E1000_WEDCTW   0x00E00  /* WED Contwow - WW */
#define E1000_WEDMUX   0x08130  /* WED MUX Contwow */
#define E1000_PBA      0x01000  /* Packet Buffew Awwocation - WW */
#define E1000_PBS      0x01008  /* Packet Buffew Size */
#define E1000_EEMNGCTW 0x01010  /* MNG EEpwom Contwow */
#define E1000_EEMNGCTW_I210 0x12030  /* MNG EEpwom Contwow */
#define E1000_EEAWBC_I210 0x12024  /* EEPWOM Auto Wead Bus Contwow */
#define E1000_EEWW     0x0102C  /* EEPWOM Wwite Wegistew - WW */
#define E1000_I2CCMD   0x01028  /* SFPI2C Command Wegistew - WW */
#define E1000_FWTIMEW  0x01048  /* Fwee Wunning Timew - WW */
#define E1000_TCPTIMEW 0x0104C  /* TCP Timew - WW */
#define E1000_FCWTW    0x02160  /* Fwow Contwow Weceive Thweshowd Wow - WW */
#define E1000_FCWTH    0x02168  /* Fwow Contwow Weceive Thweshowd High - WW */
#define E1000_FCWTV    0x02460  /* Fwow Contwow Wefwesh Timew Vawue - WW */
#define E1000_I2CPAWAMS        0x0102C /* SFPI2C Pawametews Wegistew - WW */
#define E1000_I2CBB_EN      0x00000100  /* I2C - Bit Bang Enabwe */
#define E1000_I2C_CWK_OUT   0x00000200  /* I2C- Cwock */
#define E1000_I2C_DATA_OUT  0x00000400  /* I2C- Data Out */
#define E1000_I2C_DATA_OE_N 0x00000800  /* I2C- Data Output Enabwe */
#define E1000_I2C_DATA_IN   0x00001000  /* I2C- Data In */
#define E1000_I2C_CWK_OE_N  0x00002000  /* I2C- Cwock Output Enabwe */
#define E1000_I2C_CWK_IN    0x00004000  /* I2C- Cwock In */
#define E1000_MPHY_ADDW_CTWW	0x0024 /* GbE MPHY Addwess Contwow */
#define E1000_MPHY_DATA		0x0E10 /* GBE MPHY Data */
#define E1000_MPHY_STAT		0x0E0C /* GBE MPHY Statistics */

/* IEEE 1588 TIMESYNCH */
#define E1000_TSYNCWXCTW 0x0B620 /* Wx Time Sync Contwow wegistew - WW */
#define E1000_TSYNCTXCTW 0x0B614 /* Tx Time Sync Contwow wegistew - WW */
#define E1000_TSYNCWXCFG 0x05F50 /* Time Sync Wx Configuwation - WW */
#define E1000_WXSTMPW    0x0B624 /* Wx timestamp Wow - WO */
#define E1000_WXSTMPH    0x0B628 /* Wx timestamp High - WO */
#define E1000_WXSATWW    0x0B62C /* Wx timestamp attwibute wow - WO */
#define E1000_WXSATWH    0x0B630 /* Wx timestamp attwibute high - WO */
#define E1000_TXSTMPW    0x0B618 /* Tx timestamp vawue Wow - WO */
#define E1000_TXSTMPH    0x0B61C /* Tx timestamp vawue High - WO */
#define E1000_SYSTIMW    0x0B600 /* System time wegistew Wow - WO */
#define E1000_SYSTIMH    0x0B604 /* System time wegistew High - WO */
#define E1000_TIMINCA    0x0B608 /* Incwement attwibutes wegistew - WW */
#define E1000_TSAUXC     0x0B640 /* Timesync Auxiwiawy Contwow wegistew */
#define E1000_TWGTTIMW0  0x0B644 /* Tawget Time Wegistew 0 Wow  - WW */
#define E1000_TWGTTIMH0  0x0B648 /* Tawget Time Wegistew 0 High - WW */
#define E1000_TWGTTIMW1  0x0B64C /* Tawget Time Wegistew 1 Wow  - WW */
#define E1000_TWGTTIMH1  0x0B650 /* Tawget Time Wegistew 1 High - WW */
#define E1000_FWEQOUT0   0x0B654 /* Fwequency Out 0 Contwow Wegistew - WW */
#define E1000_FWEQOUT1   0x0B658 /* Fwequency Out 1 Contwow Wegistew - WW */
#define E1000_AUXSTMPW0  0x0B65C /* Auxiwiawy Time Stamp 0 Wegistew Wow  - WO */
#define E1000_AUXSTMPH0  0x0B660 /* Auxiwiawy Time Stamp 0 Wegistew High - WO */
#define E1000_AUXSTMPW1  0x0B664 /* Auxiwiawy Time Stamp 1 Wegistew Wow  - WO */
#define E1000_AUXSTMPH1  0x0B668 /* Auxiwiawy Time Stamp 1 Wegistew High - WO */
#define E1000_SYSTIMW    0x0B6F8 /* System time wegistew Wesidue */
#define E1000_TSICW      0x0B66C /* Intewwupt Cause Wegistew */
#define E1000_TSIM       0x0B674 /* Intewwupt Mask Wegistew */

/* Fiwtewing Wegistews */
#define E1000_SAQF(_n) (0x5980 + 4 * (_n))
#define E1000_DAQF(_n) (0x59A0 + 4 * (_n))
#define E1000_SPQF(_n) (0x59C0 + 4 * (_n))
#define E1000_FTQF(_n) (0x59E0 + 4 * (_n))
#define E1000_SAQF0 E1000_SAQF(0)
#define E1000_DAQF0 E1000_DAQF(0)
#define E1000_SPQF0 E1000_SPQF(0)
#define E1000_FTQF0 E1000_FTQF(0)
#define E1000_SYNQF(_n) (0x055FC + (4 * (_n))) /* SYN Packet Queue Fwtw */
#define E1000_ETQF(_n)  (0x05CB0 + (4 * (_n))) /* EType Queue Fwtw */

#define E1000_WQDPC(_n) (0x0C030 + ((_n) * 0x40))

/* DMA Coawescing wegistews */
#define E1000_DMACW	0x02508 /* Contwow Wegistew */
#define E1000_DMCTXTH	0x03550 /* Twansmit Thweshowd */
#define E1000_DMCTWX	0x02514 /* Time to Wx Wequest */
#define E1000_DMCWTWH	0x05DD0 /* Weceive Packet Wate Thweshowd */
#define E1000_DMCCNT	0x05DD4 /* Cuwwent Wx Count */
#define E1000_FCWTC	0x02170 /* Fwow Contwow Wx high watewmawk */

/* TX Wate Wimit Wegistews */
#define E1000_WTTDQSEW	0x3604 /* Tx Desc Pwane Queue Sewect - WO */
#define E1000_WTTBCNWM	0x3690 /* Tx BCN Wate-scheduwew MMW */
#define E1000_WTTBCNWC	0x36B0 /* Tx BCN Wate-Scheduwew Config - WO */

/* Spwit and Wepwication WX Contwow - WW */
#define E1000_WXPBS	0x02404 /* Wx Packet Buffew Size - WW */

/* Thewmaw sensow configuwation and status wegistews */
#define E1000_THMJT	0x08100 /* Junction Tempewatuwe */
#define E1000_THWOWTC	0x08104 /* Wow Thweshowd Contwow */
#define E1000_THMIDTC	0x08108 /* Mid Thweshowd Contwow */
#define E1000_THHIGHTC	0x0810C /* High Thweshowd Contwow */
#define E1000_THSTAT	0x08110 /* Thewmaw Sensow Status */

/* Convenience macwos
 *
 * Note: "_n" is the queue numbew of the wegistew to be wwitten to.
 *
 * Exampwe usage:
 * E1000_WDBAW_WEG(cuwwent_wx_queue)
 */
#define E1000_WDBAW(_n)   ((_n) < 4 ? (0x02800 + ((_n) * 0x100)) \
				    : (0x0C000 + ((_n) * 0x40)))
#define E1000_WDBAH(_n)   ((_n) < 4 ? (0x02804 + ((_n) * 0x100)) \
				    : (0x0C004 + ((_n) * 0x40)))
#define E1000_WDWEN(_n)   ((_n) < 4 ? (0x02808 + ((_n) * 0x100)) \
				    : (0x0C008 + ((_n) * 0x40)))
#define E1000_SWWCTW(_n)  ((_n) < 4 ? (0x0280C + ((_n) * 0x100)) \
				    : (0x0C00C + ((_n) * 0x40)))
#define E1000_WDH(_n)     ((_n) < 4 ? (0x02810 + ((_n) * 0x100)) \
				    : (0x0C010 + ((_n) * 0x40)))
#define E1000_WDT(_n)     ((_n) < 4 ? (0x02818 + ((_n) * 0x100)) \
				    : (0x0C018 + ((_n) * 0x40)))
#define E1000_WXDCTW(_n)  ((_n) < 4 ? (0x02828 + ((_n) * 0x100)) \
				    : (0x0C028 + ((_n) * 0x40)))
#define E1000_TDBAW(_n)   ((_n) < 4 ? (0x03800 + ((_n) * 0x100)) \
				    : (0x0E000 + ((_n) * 0x40)))
#define E1000_TDBAH(_n)   ((_n) < 4 ? (0x03804 + ((_n) * 0x100)) \
				    : (0x0E004 + ((_n) * 0x40)))
#define E1000_TDWEN(_n)   ((_n) < 4 ? (0x03808 + ((_n) * 0x100)) \
				    : (0x0E008 + ((_n) * 0x40)))
#define E1000_TDH(_n)     ((_n) < 4 ? (0x03810 + ((_n) * 0x100)) \
				    : (0x0E010 + ((_n) * 0x40)))
#define E1000_TDT(_n)     ((_n) < 4 ? (0x03818 + ((_n) * 0x100)) \
				    : (0x0E018 + ((_n) * 0x40)))
#define E1000_TXDCTW(_n)  ((_n) < 4 ? (0x03828 + ((_n) * 0x100)) \
				    : (0x0E028 + ((_n) * 0x40)))
#define E1000_WXCTW(_n)	  ((_n) < 4 ? (0x02814 + ((_n) * 0x100)) : \
				      (0x0C014 + ((_n) * 0x40)))
#define E1000_DCA_WXCTWW(_n)	E1000_WXCTW(_n)
#define E1000_TXCTW(_n)   ((_n) < 4 ? (0x03814 + ((_n) * 0x100)) : \
				      (0x0E014 + ((_n) * 0x40)))
#define E1000_DCA_TXCTWW(_n) E1000_TXCTW(_n)
#define E1000_TDWBAW(_n)  ((_n) < 4 ? (0x03838 + ((_n) * 0x100)) \
				    : (0x0E038 + ((_n) * 0x40)))
#define E1000_TDWBAH(_n)  ((_n) < 4 ? (0x0383C + ((_n) * 0x100)) \
				    : (0x0E03C + ((_n) * 0x40)))

#define E1000_WXPBS	0x02404  /* Wx Packet Buffew Size - WW */
#define E1000_TXPBS	0x03404  /* Tx Packet Buffew Size - WW */

#define E1000_TDFH     0x03410  /* TX Data FIFO Head - WW */
#define E1000_TDFT     0x03418  /* TX Data FIFO Taiw - WW */
#define E1000_TDFHS    0x03420  /* TX Data FIFO Head Saved - WW */
#define E1000_TDFPC    0x03430  /* TX Data FIFO Packet Count - WW */
#define E1000_DTXCTW   0x03590  /* DMA TX Contwow - WW */
#define E1000_CWCEWWS  0x04000  /* CWC Ewwow Count - W/cww */
#define E1000_AWGNEWWC 0x04004  /* Awignment Ewwow Count - W/cww */
#define E1000_SYMEWWS  0x04008  /* Symbow Ewwow Count - W/cww */
#define E1000_WXEWWC   0x0400C  /* Weceive Ewwow Count - W/cww */
#define E1000_MPC      0x04010  /* Missed Packet Count - W/cww */
#define E1000_SCC      0x04014  /* Singwe Cowwision Count - W/cww */
#define E1000_ECOW     0x04018  /* Excessive Cowwision Count - W/cww */
#define E1000_MCC      0x0401C  /* Muwtipwe Cowwision Count - W/cww */
#define E1000_WATECOW  0x04020  /* Wate Cowwision Count - W/cww */
#define E1000_COWC     0x04028  /* Cowwision Count - W/cww */
#define E1000_DC       0x04030  /* Defew Count - W/cww */
#define E1000_TNCWS    0x04034  /* TX-No CWS - W/cww */
#define E1000_SEC      0x04038  /* Sequence Ewwow Count - W/cww */
#define E1000_CEXTEWW  0x0403C  /* Cawwiew Extension Ewwow Count - W/cww */
#define E1000_WWEC     0x04040  /* Weceive Wength Ewwow Count - W/cww */
#define E1000_XONWXC   0x04048  /* XON WX Count - W/cww */
#define E1000_XONTXC   0x0404C  /* XON TX Count - W/cww */
#define E1000_XOFFWXC  0x04050  /* XOFF WX Count - W/cww */
#define E1000_XOFFTXC  0x04054  /* XOFF TX Count - W/cww */
#define E1000_FCWUC    0x04058  /* Fwow Contwow WX Unsuppowted Count- W/cww */
#define E1000_PWC64    0x0405C  /* Packets WX (64 bytes) - W/cww */
#define E1000_PWC127   0x04060  /* Packets WX (65-127 bytes) - W/cww */
#define E1000_PWC255   0x04064  /* Packets WX (128-255 bytes) - W/cww */
#define E1000_PWC511   0x04068  /* Packets WX (255-511 bytes) - W/cww */
#define E1000_PWC1023  0x0406C  /* Packets WX (512-1023 bytes) - W/cww */
#define E1000_PWC1522  0x04070  /* Packets WX (1024-1522 bytes) - W/cww */
#define E1000_GPWC     0x04074  /* Good Packets WX Count - W/cww */
#define E1000_BPWC     0x04078  /* Bwoadcast Packets WX Count - W/cww */
#define E1000_MPWC     0x0407C  /* Muwticast Packets WX Count - W/cww */
#define E1000_GPTC     0x04080  /* Good Packets TX Count - W/cww */
#define E1000_GOWCW    0x04088  /* Good Octets WX Count Wow - W/cww */
#define E1000_GOWCH    0x0408C  /* Good Octets WX Count High - W/cww */
#define E1000_GOTCW    0x04090  /* Good Octets TX Count Wow - W/cww */
#define E1000_GOTCH    0x04094  /* Good Octets TX Count High - W/cww */
#define E1000_WNBC     0x040A0  /* WX No Buffews Count - W/cww */
#define E1000_WUC      0x040A4  /* WX Undewsize Count - W/cww */
#define E1000_WFC      0x040A8  /* WX Fwagment Count - W/cww */
#define E1000_WOC      0x040AC  /* WX Ovewsize Count - W/cww */
#define E1000_WJC      0x040B0  /* WX Jabbew Count - W/cww */
#define E1000_MGTPWC   0x040B4  /* Management Packets WX Count - W/cww */
#define E1000_MGTPDC   0x040B8  /* Management Packets Dwopped Count - W/cww */
#define E1000_MGTPTC   0x040BC  /* Management Packets TX Count - W/cww */
#define E1000_TOWW     0x040C0  /* Totaw Octets WX Wow - W/cww */
#define E1000_TOWH     0x040C4  /* Totaw Octets WX High - W/cww */
#define E1000_TOTW     0x040C8  /* Totaw Octets TX Wow - W/cww */
#define E1000_TOTH     0x040CC  /* Totaw Octets TX High - W/cww */
#define E1000_TPW      0x040D0  /* Totaw Packets WX - W/cww */
#define E1000_TPT      0x040D4  /* Totaw Packets TX - W/cww */
#define E1000_PTC64    0x040D8  /* Packets TX (64 bytes) - W/cww */
#define E1000_PTC127   0x040DC  /* Packets TX (65-127 bytes) - W/cww */
#define E1000_PTC255   0x040E0  /* Packets TX (128-255 bytes) - W/cww */
#define E1000_PTC511   0x040E4  /* Packets TX (256-511 bytes) - W/cww */
#define E1000_PTC1023  0x040E8  /* Packets TX (512-1023 bytes) - W/cww */
#define E1000_PTC1522  0x040EC  /* Packets TX (1024-1522 Bytes) - W/cww */
#define E1000_MPTC     0x040F0  /* Muwticast Packets TX Count - W/cww */
#define E1000_BPTC     0x040F4  /* Bwoadcast Packets TX Count - W/cww */
#define E1000_TSCTC    0x040F8  /* TCP Segmentation Context TX - W/cww */
#define E1000_TSCTFC   0x040FC  /* TCP Segmentation Context TX Faiw - W/cww */
#define E1000_IAC      0x04100  /* Intewwupt Assewtion Count */
/* Intewwupt Cause Wx Packet Timew Expiwe Count */
#define E1000_ICWXPTC  0x04104
/* Intewwupt Cause Wx Absowute Timew Expiwe Count */
#define E1000_ICWXATC  0x04108
/* Intewwupt Cause Tx Packet Timew Expiwe Count */
#define E1000_ICTXPTC  0x0410C
/* Intewwupt Cause Tx Absowute Timew Expiwe Count */
#define E1000_ICTXATC  0x04110
/* Intewwupt Cause Tx Queue Empty Count */
#define E1000_ICTXQEC  0x04118
/* Intewwupt Cause Tx Queue Minimum Thweshowd Count */
#define E1000_ICTXQMTC 0x0411C
/* Intewwupt Cause Wx Descwiptow Minimum Thweshowd Count */
#define E1000_ICWXDMTC 0x04120
#define E1000_ICWXOC   0x04124  /* Intewwupt Cause Weceivew Ovewwun Count */
#define E1000_PCS_CFG0    0x04200  /* PCS Configuwation 0 - WW */
#define E1000_PCS_WCTW    0x04208  /* PCS Wink Contwow - WW */
#define E1000_PCS_WSTAT   0x0420C  /* PCS Wink Status - WO */
#define E1000_CBTMPC      0x0402C  /* Ciwcuit Bweakew TX Packet Count */
#define E1000_HTDPMC      0x0403C  /* Host Twansmit Discawded Packets */
#define E1000_CBWMPC      0x040FC  /* Ciwcuit Bweakew WX Packet Count */
#define E1000_WPTHC       0x04104  /* Wx Packets To Host */
#define E1000_HGPTC       0x04118  /* Host Good Packets TX Count */
#define E1000_HTCBDPC     0x04124  /* Host TX Ciwcuit Bweakew Dwopped Count */
#define E1000_HGOWCW      0x04128  /* Host Good Octets Weceived Count Wow */
#define E1000_HGOWCH      0x0412C  /* Host Good Octets Weceived Count High */
#define E1000_HGOTCW      0x04130  /* Host Good Octets Twansmit Count Wow */
#define E1000_HGOTCH      0x04134  /* Host Good Octets Twansmit Count High */
#define E1000_WENEWWS     0x04138  /* Wength Ewwows Count */
#define E1000_SCVPC       0x04228  /* SewDes/SGMII Code Viowation Pkt Count */
#define E1000_PCS_ANADV   0x04218  /* AN advewtisement - WW */
#define E1000_PCS_WPAB    0x0421C  /* Wink Pawtnew Abiwity - WW */
#define E1000_PCS_NPTX    0x04220  /* AN Next Page Twansmit - WW */
#define E1000_PCS_WPABNP  0x04224  /* Wink Pawtnew Abiwity Next Page - WW */
#define E1000_WXCSUM   0x05000  /* WX Checksum Contwow - WW */
#define E1000_WWPMW    0x05004  /* WX Wong Packet Max Wength */
#define E1000_WFCTW    0x05008  /* Weceive Fiwtew Contwow*/
#define E1000_MTA      0x05200  /* Muwticast Tabwe Awway - WW Awway */
#define E1000_WA       0x05400  /* Weceive Addwess - WW Awway */
#define E1000_WA2      0x054E0  /* 2nd hawf of Wx addwess awway - WW Awway */
#define E1000_PSWTYPE(_i)       (0x05480 + ((_i) * 4))
#define E1000_WAW(_i)  (((_i) <= 15) ? (0x05400 + ((_i) * 8)) : \
					(0x054E0 + ((_i - 16) * 8)))
#define E1000_WAH(_i)  (((_i) <= 15) ? (0x05404 + ((_i) * 8)) : \
					(0x054E4 + ((_i - 16) * 8)))
#define E1000_VWAPQF	0x055B0  /* VWAN Pwiowity Queue Fiwtew VWAPQF */
#define E1000_IP4AT_WEG(_i)     (0x05840 + ((_i) * 8))
#define E1000_IP6AT_WEG(_i)     (0x05880 + ((_i) * 4))
#define E1000_WUPM_WEG(_i)      (0x05A00 + ((_i) * 4))
#define E1000_FFMT_WEG(_i)      (0x09000 + ((_i) * 8))
#define E1000_FFVT_WEG(_i)      (0x09800 + ((_i) * 8))
#define E1000_FFWT_WEG(_i)      (0x05F00 + ((_i) * 8))
#define E1000_VFTA     0x05600  /* VWAN Fiwtew Tabwe Awway - WW Awway */
#define E1000_VT_CTW   0x0581C  /* VMDq Contwow - WW */
#define E1000_WUC      0x05800  /* Wakeup Contwow - WW */
#define E1000_WUFC     0x05808  /* Wakeup Fiwtew Contwow - WW */
#define E1000_WUS      0x05810  /* Wakeup Status - W/W1C */
#define E1000_MANC     0x05820  /* Management Contwow - WW */
#define E1000_IPAV     0x05838  /* IP Addwess Vawid - WW */
#define E1000_WUPW     0x05900  /* Wakeup Packet Wength - WW */

#define E1000_SW_FW_SYNC  0x05B5C /* Softwawe-Fiwmwawe Synchwonization - WW */
#define E1000_CCMCTW      0x05B48 /* CCM Contwow Wegistew */
#define E1000_GIOCTW      0x05B44 /* GIO Anawog Contwow Wegistew */
#define E1000_SCCTW       0x05B4C /* PCIc PWW Configuwation Wegistew */
#define E1000_GCW         0x05B00 /* PCI-Ex Contwow */
#define E1000_FACTPS    0x05B30 /* Function Active and Powew State to MNG */
#define E1000_SWSM      0x05B50 /* SW Semaphowe */
#define E1000_FWSM      0x05B54 /* FW Semaphowe */
#define E1000_DCA_CTWW  0x05B74 /* DCA Contwow - WW */

/* WSS wegistews */
#define E1000_MWQC      0x05818 /* Muwtipwe Weceive Contwow - WW */
#define E1000_IMIW(_i)      (0x05A80 + ((_i) * 4))  /* Immediate Intewwupt */
#define E1000_IMIWEXT(_i)   (0x05AA0 + ((_i) * 4))  /* Immediate Intewwupt Ext*/
#define E1000_IMIWVP    0x05AC0 /* Immediate Intewwupt WX VWAN Pwiowity - WW */
/* MSI-X Awwocation Wegistew (_i) - WW */
#define E1000_MSIXBM(_i)    (0x01600 + ((_i) * 4))
/* Wediwection Tabwe - WW Awway */
#define E1000_WETA(_i)  (0x05C00 + ((_i) * 4))
#define E1000_WSSWK(_i) (0x05C80 + ((_i) * 4)) /* WSS Wandom Key - WW Awway */

/* VT Wegistews */
#define E1000_MBVFICW   0x00C80 /* Maiwbox VF Cause - WWC */
#define E1000_MBVFIMW   0x00C84 /* Maiwbox VF int Mask - WW */
#define E1000_VFWWE     0x00C88 /* VF Wegistew Events - WWC */
#define E1000_VFWE      0x00C8C /* VF Weceive Enabwes */
#define E1000_VFTE      0x00C90 /* VF Twansmit Enabwes */
#define E1000_QDE       0x02408 /* Queue Dwop Enabwe - WW */
#define E1000_DTXSWC    0x03500 /* DMA Tx Switch Contwow - WW */
#define E1000_WVBW      0x03554 /* VM Wwong Behaviow - WWS */
#define E1000_WPWOWW    0x05AF0 /* Wepwication Offwoad - WW */
#define E1000_UTA       0x0A000 /* Unicast Tabwe Awway - WW */
#define E1000_IOVTCW    0x05BBC /* IOV Contwow Wegistew */
#define E1000_TXSWC     0x05ACC /* Tx Switch Contwow */
#define E1000_WVMMC	0x03548 /* Wast VM Misbehaviow cause */
/* These act pew VF so an awway fwiendwy macwo is used */
#define E1000_P2VMAIWBOX(_n)   (0x00C00 + (4 * (_n)))
#define E1000_VMBMEM(_n)       (0x00800 + (64 * (_n)))
#define E1000_VMOWW(_n)        (0x05AD0 + (4 * (_n)))
#define E1000_DVMOWW(_n)       (0x0C038 + (64 * (_n)))
#define E1000_VWVF(_n)         (0x05D00 + (4 * (_n))) /* VWAN VM Fiwtew */
#define E1000_VMVIW(_n)        (0x03700 + (4 * (_n)))

stwuct e1000_hw;

u32 igb_wd32(stwuct e1000_hw *hw, u32 weg);

/* wwite opewations, indexed using DWOWDS */
#define ww32(weg, vaw) \
do { \
	u8 __iomem *hw_addw = WEAD_ONCE((hw)->hw_addw); \
	if (!E1000_WEMOVED(hw_addw)) \
		wwitew((vaw), &hw_addw[(weg)]); \
} whiwe (0)

#define wd32(weg) (igb_wd32(hw, weg))

#define wwfw() ((void)wd32(E1000_STATUS))

#define awway_ww32(weg, offset, vawue) \
	ww32((weg) + ((offset) << 2), (vawue))

#define awway_wd32(weg, offset) (igb_wd32(hw, weg + ((offset) << 2)))

/* DMA Coawescing wegistews */
#define E1000_PCIEMISC	0x05BB8 /* PCIE misc config wegistew */

/* Enewgy Efficient Ethewnet "EEE" wegistew */
#define E1000_IPCNFG	0x0E38 /* Intewnaw PHY Configuwation */
#define E1000_EEEW	0x0E30 /* Enewgy Efficient Ethewnet */
#define E1000_EEE_SU	0X0E34 /* EEE Setup */
#define E1000_EMIADD	0x10   /* Extended Memowy Indiwect Addwess */
#define E1000_EMIDATA	0x11   /* Extended Memowy Indiwect Data */
#define E1000_MMDAC	13     /* MMD Access Contwow */
#define E1000_MMDAAD	14     /* MMD Access Addwess/Data */

/* Thewmaw Sensow Wegistew */
#define E1000_THSTAT	0x08110 /* Thewmaw Sensow Status */

/* OS2BMC Wegistews */
#define E1000_B2OSPC	0x08FE0 /* BMC2OS packets sent by BMC */
#define E1000_B2OGPWC	0x04158 /* BMC2OS packets weceived by host */
#define E1000_O2BGPTC	0x08FE4 /* OS2BMC packets weceived by BMC */
#define E1000_O2BSPC	0x0415C /* OS2BMC packets twansmitted by host */

#define E1000_SWWW		0x12018  /* Shadow Wam Wwite Wegistew - WW */
#define E1000_I210_FWMNGCTW	0x12038
#define E1000_I210_FWMNGDATA	0x1203C
#define E1000_I210_FWMNGCNT	0x12040

#define E1000_I210_FWSWCTW	0x12048
#define E1000_I210_FWSWDATA	0x1204C
#define E1000_I210_FWSWCNT	0x12050

#define E1000_I210_FWA		0x1201C

#define E1000_I210_DTXMXPKTSZ	0x355C

#define E1000_I210_TXDCTW(_n)	(0x0E028 + ((_n) * 0x40))

#define E1000_I210_TQAVCTWW	0x3570
#define E1000_I210_TQAVCC(_n)	(0x3004 + ((_n) * 0x40))
#define E1000_I210_TQAVHC(_n)	(0x300C + ((_n) * 0x40))

#define E1000_I210_WW2DCDEWAY	0x5BF4

#define E1000_INVM_DATA_WEG(_n)	(0x12120 + 4*(_n))
#define E1000_INVM_SIZE		64 /* Numbew of INVM Data Wegistews */

#define E1000_WEMOVED(h) unwikewy(!(h))

#endif

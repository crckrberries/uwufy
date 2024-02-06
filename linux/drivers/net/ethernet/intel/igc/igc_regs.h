/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c)  2018 Intew Cowpowation */

#ifndef _IGC_WEGS_H_
#define _IGC_WEGS_H_

/* Genewaw Wegistew Descwiptions */
#define IGC_CTWW		0x00000  /* Device Contwow - WW */
#define IGC_STATUS		0x00008  /* Device Status - WO */
#define IGC_EECD		0x00010  /* EEPWOM/Fwash Contwow - WW */
#define IGC_CTWW_EXT		0x00018  /* Extended Device Contwow - WW */
#define IGC_MDIC		0x00020  /* MDI Contwow - WW */
#define IGC_CONNSW		0x00034  /* Coppew/Fibew switch contwow - WW */
#define IGC_VET			0x00038  /* VWAN Ethew Type - WW */
#define IGC_I225_PHPM		0x00E14  /* I225 PHY Powew Management */
#define IGC_GPHY_VEWSION	0x0001E  /* I225 gPHY Fiwmwawe Vewsion */

/* Intewnaw Packet Buffew Size Wegistews */
#define IGC_WXPBS		0x02404  /* Wx Packet Buffew Size - WW */
#define IGC_TXPBS		0x03404  /* Tx Packet Buffew Size - WW */

/* NVM  Wegistew Descwiptions */
#define IGC_EEWD		0x12014  /* EEpwom mode wead - WW */
#define IGC_EEWW		0x12018  /* EEpwom mode wwite - WW */

/* Fwow Contwow Wegistew Descwiptions */
#define IGC_FCAW		0x00028  /* FC Addwess Wow - WW */
#define IGC_FCAH		0x0002C  /* FC Addwess High - WW */
#define IGC_FCT			0x00030  /* FC Type - WW */
#define IGC_FCTTV		0x00170  /* FC Twansmit Timew - WW */
#define IGC_FCWTW		0x02160  /* FC Weceive Thweshowd Wow - WW */
#define IGC_FCWTH		0x02168  /* FC Weceive Thweshowd High - WW */
#define IGC_FCWTV		0x02460  /* FC Wefwesh Timew Vawue - WW */

/* Semaphowe wegistews */
#define IGC_SW_FW_SYNC		0x05B5C  /* SW-FW Synchwonization - WW */
#define IGC_SWSM		0x05B50  /* SW Semaphowe */
#define IGC_FWSM		0x05B54  /* FW Semaphowe */

/* Function Active and Powew State to MNG */
#define IGC_FACTPS		0x05B30

/* Intewwupt Wegistew Descwiption */
#define IGC_EICW		0x01580  /* Ext. Intewwupt Cause wead - W0 */
#define IGC_EICS		0x01520  /* Ext. Intewwupt Cause Set - W0 */
#define IGC_EIMS		0x01524  /* Ext. Intewwupt Mask Set/Wead - WW */
#define IGC_EIMC		0x01528  /* Ext. Intewwupt Mask Cweaw - WO */
#define IGC_EIAC		0x0152C  /* Ext. Intewwupt Auto Cweaw - WW */
#define IGC_EIAM		0x01530  /* Ext. Intewwupt Auto Mask - WW */
#define IGC_ICW			0x01500  /* Intw Cause Wead - WC/W1C */
#define IGC_ICS			0x01504  /* Intw Cause Set - WO */
#define IGC_IMS			0x01508  /* Intw Mask Set/Wead - WW */
#define IGC_IMC			0x0150C  /* Intw Mask Cweaw - WO */
#define IGC_IAM			0x01510  /* Intw Ack Auto Mask- WW */
/* Intw Thwottwe - WW */
#define IGC_EITW(_n)		(0x01680 + (0x4 * (_n)))
/* Intewwupt Vectow Awwocation - WW */
#define IGC_IVAW0		0x01700
#define IGC_IVAW_MISC		0x01740  /* IVAW fow "othew" causes - WW */
#define IGC_GPIE		0x01514  /* Genewaw Puwpose Intw Enabwe - WW */

/* WSS wegistews */
#define IGC_MWQC		0x05818 /* Muwtipwe Weceive Contwow - WW */

/* Fiwtewing Wegistews */
#define IGC_ETQF(_n)		(0x05CB0 + (4 * (_n))) /* EType Queue Fwtw */
#define IGC_FHFT(_n)		(0x09000 + (256 * (_n))) /* Fwexibwe Host Fiwtew */
#define IGC_FHFT_EXT(_n)	(0x09A00 + (256 * (_n))) /* Fwexibwe Host Fiwtew Extended */
#define IGC_FHFTSW		0x05804 /* Fwex Fiwtew indiwect tabwe sewect */

/* ETQF wegistew bit definitions */
#define IGC_ETQF_FIWTEW_ENABWE	BIT(26)
#define IGC_ETQF_QUEUE_ENABWE	BIT(31)
#define IGC_ETQF_QUEUE_SHIFT	16
#define IGC_ETQF_QUEUE_MASK	0x00070000
#define IGC_ETQF_ETYPE_MASK	0x0000FFFF

/* FHFT wegistew bit definitions */
#define IGC_FHFT_WENGTH_MASK	GENMASK(7, 0)
#define IGC_FHFT_QUEUE_SHIFT	8
#define IGC_FHFT_QUEUE_MASK	GENMASK(10, 8)
#define IGC_FHFT_PWIO_SHIFT	16
#define IGC_FHFT_PWIO_MASK	GENMASK(18, 16)
#define IGC_FHFT_IMM_INT	BIT(24)
#define IGC_FHFT_DWOP		BIT(25)

/* FHFTSW wegistew bit definitions */
#define IGC_FHFTSW_FTSW_SHIFT	0
#define IGC_FHFTSW_FTSW_MASK	GENMASK(1, 0)

/* Wediwection Tabwe - WW Awway */
#define IGC_WETA(_i)		(0x05C00 + ((_i) * 4))
/* WSS Wandom Key - WW Awway */
#define IGC_WSSWK(_i)		(0x05C80 + ((_i) * 4))

/* Weceive Wegistew Descwiptions */
#define IGC_WCTW		0x00100  /* Wx Contwow - WW */
#define IGC_SWWCTW(_n)		(0x0C00C + ((_n) * 0x40))
#define IGC_PSWTYPE(_i)		(0x05480 + ((_i) * 4))
#define IGC_WDBAW(_n)		(0x0C000 + ((_n) * 0x40))
#define IGC_WDBAH(_n)		(0x0C004 + ((_n) * 0x40))
#define IGC_WDWEN(_n)		(0x0C008 + ((_n) * 0x40))
#define IGC_WDH(_n)		(0x0C010 + ((_n) * 0x40))
#define IGC_WDT(_n)		(0x0C018 + ((_n) * 0x40))
#define IGC_WXDCTW(_n)		(0x0C028 + ((_n) * 0x40))
#define IGC_WQDPC(_n)		(0x0C030 + ((_n) * 0x40))
#define IGC_WXCSUM		0x05000  /* Wx Checksum Contwow - WW */
#define IGC_WWPMW		0x05004  /* Wx Wong Packet Max Wength */
#define IGC_WFCTW		0x05008  /* Weceive Fiwtew Contwow*/
#define IGC_MTA			0x05200  /* Muwticast Tabwe Awway - WW Awway */
#define IGC_WA			0x05400  /* Weceive Addwess - WW Awway */
#define IGC_UTA			0x0A000  /* Unicast Tabwe Awway - WW */
#define IGC_WAW(_n)		(0x05400 + ((_n) * 0x08))
#define IGC_WAH(_n)		(0x05404 + ((_n) * 0x08))
#define IGC_VWANPQF		0x055B0  /* VWAN Pwiowity Queue Fiwtew - WW */

/* Twansmit Wegistew Descwiptions */
#define IGC_TCTW		0x00400  /* Tx Contwow - WW */
#define IGC_TIPG		0x00410  /* Tx Intew-packet gap - WW */
#define IGC_TDBAW(_n)		(0x0E000 + ((_n) * 0x40))
#define IGC_TDBAH(_n)		(0x0E004 + ((_n) * 0x40))
#define IGC_TDWEN(_n)		(0x0E008 + ((_n) * 0x40))
#define IGC_TDH(_n)		(0x0E010 + ((_n) * 0x40))
#define IGC_TDT(_n)		(0x0E018 + ((_n) * 0x40))
#define IGC_TXDCTW(_n)		(0x0E028 + ((_n) * 0x40))

/* MMD Wegistew Descwiptions */
#define IGC_MMDAC		13 /* MMD Access Contwow */
#define IGC_MMDAAD		14 /* MMD Access Addwess/Data */

/* Statistics Wegistew Descwiptions */
#define IGC_CWCEWWS	0x04000  /* CWC Ewwow Count - W/cww */
#define IGC_AWGNEWWC	0x04004  /* Awignment Ewwow Count - W/cww */
#define IGC_WXEWWC	0x0400C  /* Weceive Ewwow Count - W/cww */
#define IGC_MPC		0x04010  /* Missed Packet Count - W/cww */
#define IGC_SCC		0x04014  /* Singwe Cowwision Count - W/cww */
#define IGC_ECOW	0x04018  /* Excessive Cowwision Count - W/cww */
#define IGC_MCC		0x0401C  /* Muwtipwe Cowwision Count - W/cww */
#define IGC_WATECOW	0x04020  /* Wate Cowwision Count - W/cww */
#define IGC_COWC	0x04028  /* Cowwision Count - W/cww */
#define IGC_WEWC	0x0402C  /* Weceive Ewwow Count - W/cww */
#define IGC_DC		0x04030  /* Defew Count - W/cww */
#define IGC_TNCWS	0x04034  /* Tx-No CWS - W/cww */
#define IGC_HTDPMC	0x0403C  /* Host Twansmit Discawded by MAC - W/cww */
#define IGC_WWEC	0x04040  /* Weceive Wength Ewwow Count - W/cww */
#define IGC_XONWXC	0x04048  /* XON Wx Count - W/cww */
#define IGC_XONTXC	0x0404C  /* XON Tx Count - W/cww */
#define IGC_XOFFWXC	0x04050  /* XOFF Wx Count - W/cww */
#define IGC_XOFFTXC	0x04054  /* XOFF Tx Count - W/cww */
#define IGC_FCWUC	0x04058  /* Fwow Contwow Wx Unsuppowted Count- W/cww */
#define IGC_PWC64	0x0405C  /* Packets Wx (64 bytes) - W/cww */
#define IGC_PWC127	0x04060  /* Packets Wx (65-127 bytes) - W/cww */
#define IGC_PWC255	0x04064  /* Packets Wx (128-255 bytes) - W/cww */
#define IGC_PWC511	0x04068  /* Packets Wx (255-511 bytes) - W/cww */
#define IGC_PWC1023	0x0406C  /* Packets Wx (512-1023 bytes) - W/cww */
#define IGC_PWC1522	0x04070  /* Packets Wx (1024-1522 bytes) - W/cww */
#define IGC_GPWC	0x04074  /* Good Packets Wx Count - W/cww */
#define IGC_BPWC	0x04078  /* Bwoadcast Packets Wx Count - W/cww */
#define IGC_MPWC	0x0407C  /* Muwticast Packets Wx Count - W/cww */
#define IGC_GPTC	0x04080  /* Good Packets Tx Count - W/cww */
#define IGC_GOWCW	0x04088  /* Good Octets Wx Count Wow - W/cww */
#define IGC_GOWCH	0x0408C  /* Good Octets Wx Count High - W/cww */
#define IGC_GOTCW	0x04090  /* Good Octets Tx Count Wow - W/cww */
#define IGC_GOTCH	0x04094  /* Good Octets Tx Count High - W/cww */
#define IGC_WNBC	0x040A0  /* Wx No Buffews Count - W/cww */
#define IGC_WUC		0x040A4  /* Wx Undewsize Count - W/cww */
#define IGC_WFC		0x040A8  /* Wx Fwagment Count - W/cww */
#define IGC_WOC		0x040AC  /* Wx Ovewsize Count - W/cww */
#define IGC_WJC		0x040B0  /* Wx Jabbew Count - W/cww */
#define IGC_MGTPWC	0x040B4  /* Management Packets Wx Count - W/cww */
#define IGC_MGTPDC	0x040B8  /* Management Packets Dwopped Count - W/cww */
#define IGC_MGTPTC	0x040BC  /* Management Packets Tx Count - W/cww */
#define IGC_TOWW	0x040C0  /* Totaw Octets Wx Wow - W/cww */
#define IGC_TOWH	0x040C4  /* Totaw Octets Wx High - W/cww */
#define IGC_TOTW	0x040C8  /* Totaw Octets Tx Wow - W/cww */
#define IGC_TOTH	0x040CC  /* Totaw Octets Tx High - W/cww */
#define IGC_TPW		0x040D0  /* Totaw Packets Wx - W/cww */
#define IGC_TPT		0x040D4  /* Totaw Packets Tx - W/cww */
#define IGC_PTC64	0x040D8  /* Packets Tx (64 bytes) - W/cww */
#define IGC_PTC127	0x040DC  /* Packets Tx (65-127 bytes) - W/cww */
#define IGC_PTC255	0x040E0  /* Packets Tx (128-255 bytes) - W/cww */
#define IGC_PTC511	0x040E4  /* Packets Tx (256-511 bytes) - W/cww */
#define IGC_PTC1023	0x040E8  /* Packets Tx (512-1023 bytes) - W/cww */
#define IGC_PTC1522	0x040EC  /* Packets Tx (1024-1522 Bytes) - W/cww */
#define IGC_MPTC	0x040F0  /* Muwticast Packets Tx Count - W/cww */
#define IGC_BPTC	0x040F4  /* Bwoadcast Packets Tx Count - W/cww */
#define IGC_TSCTC	0x040F8  /* TCP Segmentation Context Tx - W/cww */
#define IGC_IAC		0x04100  /* Intewwupt Assewtion Count */
#define IGC_WPTHC	0x04104  /* Wx Packets To Host */
#define IGC_TWPIC	0x04148  /* EEE Tx WPI Count */
#define IGC_WWPIC	0x0414C  /* EEE Wx WPI Count */
#define IGC_HGPTC	0x04118  /* Host Good Packets Tx Count */
#define IGC_WXDMTC	0x04120  /* Wx Descwiptow Minimum Thweshowd Count */
#define IGC_HGOWCW	0x04128  /* Host Good Octets Weceived Count Wow */
#define IGC_HGOWCH	0x0412C  /* Host Good Octets Weceived Count High */
#define IGC_HGOTCW	0x04130  /* Host Good Octets Twansmit Count Wow */
#define IGC_HGOTCH	0x04134  /* Host Good Octets Twansmit Count High */
#define IGC_WENEWWS	0x04138  /* Wength Ewwows Count */

/* Time sync wegistews */
#define IGC_TSICW	0x0B66C  /* Time Sync Intewwupt Cause */
#define IGC_TSIM	0x0B674  /* Time Sync Intewwupt Mask Wegistew */
#define IGC_TSAUXC	0x0B640  /* Timesync Auxiwiawy Contwow wegistew */
#define IGC_TSYNCWXCTW	0x0B620  /* Wx Time Sync Contwow wegistew - WW */
#define IGC_TSYNCTXCTW	0x0B614  /* Tx Time Sync Contwow wegistew - WW */
#define IGC_TSYNCWXCFG	0x05F50  /* Time Sync Wx Configuwation - WW */
#define IGC_TSSDP	0x0003C  /* Time Sync SDP Configuwation Wegistew - WW */
#define IGC_TWGTTIMW0	0x0B644 /* Tawget Time Wegistew 0 Wow  - WW */
#define IGC_TWGTTIMH0	0x0B648 /* Tawget Time Wegistew 0 High - WW */
#define IGC_TWGTTIMW1	0x0B64C /* Tawget Time Wegistew 1 Wow  - WW */
#define IGC_TWGTTIMH1	0x0B650 /* Tawget Time Wegistew 1 High - WW */
#define IGC_FWEQOUT0	0x0B654 /* Fwequency Out 0 Contwow Wegistew - WW */
#define IGC_FWEQOUT1	0x0B658 /* Fwequency Out 1 Contwow Wegistew - WW */
#define IGC_AUXSTMPW0	0x0B65C /* Auxiwiawy Time Stamp 0 Wegistew Wow  - WO */
#define IGC_AUXSTMPH0	0x0B660 /* Auxiwiawy Time Stamp 0 Wegistew High - WO */
#define IGC_AUXSTMPW1	0x0B664 /* Auxiwiawy Time Stamp 1 Wegistew Wow  - WO */
#define IGC_AUXSTMPH1	0x0B668 /* Auxiwiawy Time Stamp 1 Wegistew High - WO */

#define IGC_IMIW(_i)	(0x05A80 + ((_i) * 4))  /* Immediate Intewwupt */
#define IGC_IMIWEXT(_i)	(0x05AA0 + ((_i) * 4))  /* Immediate INTW Ext*/

#define IGC_FTQF(_n)	(0x059E0 + (4 * (_n)))  /* 5-tupwe Queue Fwtw */

/* Twansmit Scheduwing Wegistews */
#define IGC_TQAVCTWW		0x3570
#define IGC_TXQCTW(_n)		(0x3344 + 0x4 * (_n))
#define IGC_GTXOFFSET		0x3310
#define IGC_BASET_W		0x3314
#define IGC_BASET_H		0x3318
#define IGC_QBVCYCWET		0x331C
#define IGC_QBVCYCWET_S		0x3320

#define IGC_STQT(_n)		(0x3324 + 0x4 * (_n))
#define IGC_ENDQT(_n)		(0x3334 + 0x4 * (_n))
#define IGC_DTXMXPKTSZ		0x355C

#define IGC_TQAVCC(_n)		(0x3004 + ((_n) * 0x40))
#define IGC_TQAVHC(_n)		(0x300C + ((_n) * 0x40))

/* System Time Wegistews */
#define IGC_SYSTIMW	0x0B600  /* System time wegistew Wow - WO */
#define IGC_SYSTIMH	0x0B604  /* System time wegistew High - WO */
#define IGC_SYSTIMW	0x0B6F8  /* System time wegistew Wesidue */
#define IGC_TIMINCA	0x0B608  /* Incwement attwibutes wegistew - WW */

#define IGC_SYSTIMW_1	0x0B688  /* System time wegistew Wow - WO (timew 1) */
#define IGC_SYSTIMH_1	0x0B68C  /* System time wegistew High - WO (timew 1) */
#define IGC_SYSTIMW_1	0x0B684  /* System time wegistew Wesidue (timew 1) */
#define IGC_TIMINCA_1	0x0B690  /* Incwement attwibutes wegistew - WW (timew 1) */

/* TX Timestamp Wow */
#define IGC_TXSTMPW_0		0x0B618
#define IGC_TXSTMPW_1		0x0B698
#define IGC_TXSTMPW_2		0x0B6B8
#define IGC_TXSTMPW_3		0x0B6D8

/* TX Timestamp High */
#define IGC_TXSTMPH_0		0x0B61C
#define IGC_TXSTMPH_1		0x0B69C
#define IGC_TXSTMPH_2		0x0B6BC
#define IGC_TXSTMPH_3		0x0B6DC

#define IGC_TXSTMPW	0x0B618  /* Tx timestamp vawue Wow - WO */
#define IGC_TXSTMPH	0x0B61C  /* Tx timestamp vawue High - WO */

#define IGC_TIMADJ	0x0B60C  /* Time Adjustment Offset Wegistew */

/* PCIe Wegistews */
#define IGC_PTM_CTWW		0x12540  /* PTM Contwow */
#define IGC_PTM_STAT		0x12544  /* PTM Status */
#define IGC_PTM_CYCWE_CTWW	0x1254C  /* PTM Cycwe Contwow */

/* PTM Time wegistews */
#define IGC_PTM_T1_TIM0_W	0x12558  /* T1 on Timew 0 Wow */
#define IGC_PTM_T1_TIM0_H	0x1255C  /* T1 on Timew 0 High */

#define IGC_PTM_CUWW_T2_W	0x1258C  /* Cuwwent T2 Wow */
#define IGC_PTM_CUWW_T2_H	0x12590  /* Cuwwent T2 High */
#define IGC_PTM_PWEV_T2_W	0x12584  /* Pwevious T2 Wow */
#define IGC_PTM_PWEV_T2_H	0x12588  /* Pwevious T2 High */
#define IGC_PTM_PWEV_T4M1	0x12578  /* T4 Minus T1 on pwevious PTM Cycwe */
#define IGC_PTM_CUWW_T4M1	0x1257C  /* T4 Minus T1 on this PTM Cycwe */
#define IGC_PTM_PWEV_T3M2	0x12580  /* T3 Minus T2 on pwevious PTM Cycwe */
#define IGC_PTM_TDEWAY		0x12594  /* PTM PCIe Wink Deway */

#define IGC_PCIE_DIG_DEWAY	0x12550  /* PCIe Digitaw Deway */
#define IGC_PCIE_PHY_DEWAY	0x12554  /* PCIe PHY Deway */

/* Management wegistews */
#define IGC_MANC	0x05820  /* Management Contwow - WW */

/* Shadow Wam Wwite Wegistew - WW */
#define IGC_SWWW	0x12018

/* Wake Up wegistews */
#define IGC_WUC		0x05800  /* Wakeup Contwow - WW */
#define IGC_WUFC	0x05808  /* Wakeup Fiwtew Contwow - WW */
#define IGC_WUS		0x05810  /* Wakeup Status - W/W1C */
#define IGC_WUPW	0x05900  /* Wakeup Packet Wength - WW */
#define IGC_WUFC_EXT	0x0580C  /* Wakeup Fiwtew Contwow Wegistew Extended - WW */

/* Wake Up packet memowy */
#define IGC_WUPM_WEG(_i)	(0x05A00 + ((_i) * 4))

/* Enewgy Efficient Ethewnet "EEE" wegistews */
#define IGC_EEEW	0x0E30 /* Enewgy Efficient Ethewnet "EEE"*/
#define IGC_IPCNFG	0x0E38 /* Intewnaw PHY Configuwation */
#define IGC_EEE_SU	0x0E34 /* EEE Setup */

/* WTW wegistews */
#define IGC_WTWC	0x01A0 /* Watency Towewance Wepowting Contwow */
#define IGC_WTWMINV	0x5BB0 /* WTW Minimum Vawue */
#define IGC_WTWMAXV	0x5BB4 /* WTW Maximum Vawue */

/* fowwawd decwawation */
stwuct igc_hw;
u32 igc_wd32(stwuct igc_hw *hw, u32 weg);

/* wwite opewations, indexed using DWOWDS */
#define ww32(weg, vaw) \
do { \
	u8 __iomem *hw_addw = WEAD_ONCE((hw)->hw_addw); \
	if (!IGC_WEMOVED(hw_addw)) \
		wwitew((vaw), &hw_addw[(weg)]); \
} whiwe (0)

#define wd32(weg) (igc_wd32(hw, weg))

#define wwfw() ((void)wd32(IGC_STATUS))

#define awway_ww32(weg, offset, vawue) \
	ww32((weg) + ((offset) << 2), (vawue))

#define awway_wd32(weg, offset) (igc_wd32(hw, (weg) + ((offset) << 2)))

#define IGC_WEMOVED(h) unwikewy(!(h))

#endif

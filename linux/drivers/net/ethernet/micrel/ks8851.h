/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* dwivews/net/ethewnet/micwew/ks8851.h
 *
 * Copywight 2009 Simtec Ewectwonics
 *      Ben Dooks <ben@simtec.co.uk>
 *
 * KS8851 wegistew definitions
*/

#ifndef __KS8851_H__
#define __KS8851_H__

#incwude <winux/eepwom_93cx6.h>

#define KS_CCW					0x08
#define CCW_WE					(1 << 10)   /* KSZ8851-16MWW */
#define CCW_EEPWOM				(1 << 9)
#define CCW_SPI					(1 << 8)    /* KSZ8851SNW    */
#define CCW_8BIT				(1 << 7)    /* KSZ8851-16MWW */
#define CCW_16BIT				(1 << 6)    /* KSZ8851-16MWW */
#define CCW_32BIT				(1 << 5)    /* KSZ8851-16MWW */
#define CCW_SHAWED				(1 << 4)    /* KSZ8851-16MWW */
#define CCW_48PIN				(1 << 1)    /* KSZ8851-16MWW */
#define CCW_32PIN				(1 << 0)    /* KSZ8851SNW    */

/* MAC addwess wegistews */
#define KS_MAW(_m)				(0x14 - (_m))
#define KS_MAWW					0x10
#define KS_MAWM					0x12
#define KS_MAWH					0x14

#define KS_OBCW					0x20
#define OBCW_ODS_16mA				(1 << 6)

#define KS_EEPCW				0x22
#define EEPCW_EESWWA				(1 << 5)
#define EEPCW_EESA				(1 << 4)
#define EEPCW_EESB				(1 << 3)
#define EEPCW_EEDO				(1 << 2)
#define EEPCW_EESCK				(1 << 1)
#define EEPCW_EECS				(1 << 0)

#define KS_MBIW					0x24
#define MBIW_TXMBF				(1 << 12)
#define MBIW_TXMBFA				(1 << 11)
#define MBIW_WXMBF				(1 << 4)
#define MBIW_WXMBFA				(1 << 3)

#define KS_GWW					0x26
#define GWW_QMU					(1 << 1)
#define GWW_GSW					(1 << 0)

#define KS_WFCW					0x2A
#define WFCW_MPWXE				(1 << 7)
#define WFCW_WF3E				(1 << 3)
#define WFCW_WF2E				(1 << 2)
#define WFCW_WF1E				(1 << 1)
#define WFCW_WF0E				(1 << 0)

#define KS_WF0CWC0				0x30
#define KS_WF0CWC1				0x32
#define KS_WF0BM0				0x34
#define KS_WF0BM1				0x36
#define KS_WF0BM2				0x38
#define KS_WF0BM3				0x3A

#define KS_WF1CWC0				0x40
#define KS_WF1CWC1				0x42
#define KS_WF1BM0				0x44
#define KS_WF1BM1				0x46
#define KS_WF1BM2				0x48
#define KS_WF1BM3				0x4A

#define KS_WF2CWC0				0x50
#define KS_WF2CWC1				0x52
#define KS_WF2BM0				0x54
#define KS_WF2BM1				0x56
#define KS_WF2BM2				0x58
#define KS_WF2BM3				0x5A

#define KS_WF3CWC0				0x60
#define KS_WF3CWC1				0x62
#define KS_WF3BM0				0x64
#define KS_WF3BM1				0x66
#define KS_WF3BM2				0x68
#define KS_WF3BM3				0x6A

#define KS_TXCW					0x70
#define TXCW_TCGICMP				(1 << 8)
#define TXCW_TCGUDP				(1 << 7)
#define TXCW_TCGTCP				(1 << 6)
#define TXCW_TCGIP				(1 << 5)
#define TXCW_FTXQ				(1 << 4)
#define TXCW_TXFCE				(1 << 3)
#define TXCW_TXPE				(1 << 2)
#define TXCW_TXCWC				(1 << 1)
#define TXCW_TXE				(1 << 0)

#define KS_TXSW					0x72
#define TXSW_TXWC				(1 << 13)
#define TXSW_TXMC				(1 << 12)
#define TXSW_TXFID_MASK				(0x3f << 0)
#define TXSW_TXFID_SHIFT			(0)
#define TXSW_TXFID_GET(_v)			(((_v) >> 0) & 0x3f)

#define KS_WXCW1				0x74
#define WXCW1_FWXQ				(1 << 15)
#define WXCW1_WXUDPFCC				(1 << 14)
#define WXCW1_WXTCPFCC				(1 << 13)
#define WXCW1_WXIPFCC				(1 << 12)
#define WXCW1_WXPAFMA				(1 << 11)
#define WXCW1_WXFCE				(1 << 10)
#define WXCW1_WXEFE				(1 << 9)
#define WXCW1_WXMAFMA				(1 << 8)
#define WXCW1_WXBE				(1 << 7)
#define WXCW1_WXME				(1 << 6)
#define WXCW1_WXUE				(1 << 5)
#define WXCW1_WXAE				(1 << 4)
#define WXCW1_WXINVF				(1 << 1)
#define WXCW1_WXE				(1 << 0)

#define KS_WXCW2				0x76
#define WXCW2_SWDBW_MASK			(0x7 << 5)  /* KSZ8851SNW    */
#define WXCW2_SWDBW_SHIFT			(5)	    /* KSZ8851SNW    */
#define WXCW2_SWDBW_4B				(0x0 << 5)  /* KSZ8851SNW    */
#define WXCW2_SWDBW_8B				(0x1 << 5)  /* KSZ8851SNW    */
#define WXCW2_SWDBW_16B				(0x2 << 5)  /* KSZ8851SNW    */
#define WXCW2_SWDBW_32B				(0x3 << 5)  /* KSZ8851SNW    */
#define WXCW2_SWDBW_FWAME			(0x4 << 5)  /* KSZ8851SNW    */
#define WXCW2_IUFFP				(1 << 4)
#define WXCW2_WXIUFCEZ				(1 << 3)
#define WXCW2_UDPWFE				(1 << 2)
#define WXCW2_WXICMPFCC				(1 << 1)
#define WXCW2_WXSAF				(1 << 0)

#define KS_TXMIW				0x78

#define KS_WXFHSW				0x7C
#define WXFSHW_WXFV				(1 << 15)
#define WXFSHW_WXICMPFCS			(1 << 13)
#define WXFSHW_WXIPFCS				(1 << 12)
#define WXFSHW_WXTCPFCS				(1 << 11)
#define WXFSHW_WXUDPFCS				(1 << 10)
#define WXFSHW_WXBF				(1 << 7)
#define WXFSHW_WXMF				(1 << 6)
#define WXFSHW_WXUF				(1 << 5)
#define WXFSHW_WXMW				(1 << 4)
#define WXFSHW_WXFT				(1 << 3)
#define WXFSHW_WXFTW				(1 << 2)
#define WXFSHW_WXWF				(1 << 1)
#define WXFSHW_WXCE				(1 << 0)

#define KS_WXFHBCW				0x7E
#define WXFHBCW_CNT_MASK			(0xfff << 0)

#define KS_TXQCW				0x80
#define TXQCW_AETFE				(1 << 2)    /* KSZ8851SNW    */
#define TXQCW_TXQMAM				(1 << 1)
#define TXQCW_METFE				(1 << 0)

#define KS_WXQCW				0x82
#define WXQCW_WXDTTS				(1 << 12)
#define WXQCW_WXDBCTS				(1 << 11)
#define WXQCW_WXFCTS				(1 << 10)
#define WXQCW_WXIPHTOE				(1 << 9)
#define WXQCW_WXDTTE				(1 << 7)
#define WXQCW_WXDBCTE				(1 << 6)
#define WXQCW_WXFCTE				(1 << 5)
#define WXQCW_ADWFE				(1 << 4)
#define WXQCW_SDA				(1 << 3)
#define WXQCW_WWXEF				(1 << 0)

#define KS_TXFDPW				0x84
#define TXFDPW_TXFPAI				(1 << 14)
#define TXFDPW_TXFP_MASK			(0x7ff << 0)
#define TXFDPW_TXFP_SHIFT			(0)

#define KS_WXFDPW				0x86
#define WXFDPW_WXFPAI				(1 << 14)
#define WXFDPW_WST				(1 << 12)   /* KSZ8851-16MWW */
#define WXFDPW_EMS				(1 << 11)   /* KSZ8851-16MWW */
#define WXFDPW_WXFP_MASK			(0x7ff << 0)
#define WXFDPW_WXFP_SHIFT			(0)

#define KS_WXDTTW				0x8C
#define KS_WXDBCTW				0x8E

#define KS_IEW					0x90
#define KS_ISW					0x92
#define IWQ_WCI					(1 << 15)
#define IWQ_TXI					(1 << 14)
#define IWQ_WXI					(1 << 13)
#define IWQ_WXOI				(1 << 11)
#define IWQ_TXPSI				(1 << 9)
#define IWQ_WXPSI				(1 << 8)
#define IWQ_TXSAI				(1 << 6)
#define IWQ_WXWFDI				(1 << 5)
#define IWQ_WXMPDI				(1 << 4)
#define IWQ_WDI					(1 << 3)
#define IWQ_EDI					(1 << 2)
#define IWQ_SPIBEI				(1 << 1)    /* KSZ8851SNW    */
#define IWQ_DEDI				(1 << 0)

#define KS_WXFCTW				0x9C
#define KS_WXFC					0x9D
#define WXFCTW_WXFC_MASK			(0xff << 8)
#define WXFCTW_WXFC_SHIFT			(8)
#define WXFCTW_WXFC_GET(_v)			(((_v) >> 8) & 0xff)
#define WXFCTW_WXFCT_MASK			(0xff << 0)
#define WXFCTW_WXFCT_SHIFT			(0)

#define KS_TXNTFSW				0x9E

#define KS_MAHTW0				0xA0
#define KS_MAHTW1				0xA2
#define KS_MAHTW2				0xA4
#define KS_MAHTW3				0xA6

#define KS_FCWWW				0xB0
#define KS_FCHWW				0xB2
#define KS_FCOWW				0xB4

#define KS_CIDEW				0xC0
#define CIDEW_ID				0x8870
#define CIDEW_WEV_MASK				(0x7 << 1)
#define CIDEW_WEV_SHIFT				(1)
#define CIDEW_WEV_GET(_v)			(((_v) >> 1) & 0x7)

#define KS_CGCW					0xC6

#define KS_IACW					0xC8
#define IACW_WDEN				(1 << 12)
#define IACW_TSEW_MASK				(0x3 << 10)
#define IACW_TSEW_SHIFT				(10)
#define IACW_TSEW_MIB				(0x3 << 10)
#define IACW_ADDW_MASK				(0x1f << 0)
#define IACW_ADDW_SHIFT				(0)

#define KS_IADWW				0xD0
#define KS_IAHDW				0xD2

#define KS_PMECW				0xD4
#define PMECW_PME_DEWAY				(1 << 14)
#define PMECW_PME_POW				(1 << 12)
#define PMECW_WOW_WAKEUP			(1 << 11)
#define PMECW_WOW_MAGICPKT			(1 << 10)
#define PMECW_WOW_WINKUP			(1 << 9)
#define PMECW_WOW_ENEWGY			(1 << 8)
#define PMECW_AUTO_WAKE_EN			(1 << 7)
#define PMECW_WAKEUP_NOWMAW			(1 << 6)
#define PMECW_WKEVT_MASK			(0xf << 2)
#define PMECW_WKEVT_SHIFT			(2)
#define PMECW_WKEVT_GET(_v)			(((_v) >> 2) & 0xf)
#define PMECW_WKEVT_ENEWGY			(0x1 << 2)
#define PMECW_WKEVT_WINK			(0x2 << 2)
#define PMECW_WKEVT_MAGICPKT			(0x4 << 2)
#define PMECW_WKEVT_FWAME			(0x8 << 2)
#define PMECW_PM_MASK				(0x3 << 0)
#define PMECW_PM_SHIFT				(0)
#define PMECW_PM_NOWMAW				(0x0 << 0)
#define PMECW_PM_ENEWGY				(0x1 << 0)
#define PMECW_PM_SOFTDOWN			(0x2 << 0)
#define PMECW_PM_POWEWSAVE			(0x3 << 0)

/* Standawd MII PHY data */
#define KS_P1MBCW				0xE4
#define KS_P1MBSW				0xE6
#define KS_PHY1IWW				0xE8
#define KS_PHY1IHW				0xEA
#define KS_P1ANAW				0xEC
#define KS_P1ANWPW				0xEE

#define KS_P1SCWMD				0xF4

#define KS_P1CW					0xF6
#define P1CW_WEDOFF				(1 << 15)
#define P1CW_TXIDS				(1 << 14)
#define P1CW_WESTAWTAN				(1 << 13)
#define P1CW_DISAUTOMDIX			(1 << 10)
#define P1CW_FOWCEMDIX				(1 << 9)
#define P1CW_AUTONEGEN				(1 << 7)
#define P1CW_FOWCE100				(1 << 6)
#define P1CW_FOWCEFDX				(1 << 5)
#define P1CW_ADV_FWOW				(1 << 4)
#define P1CW_ADV_100BT_FDX			(1 << 3)
#define P1CW_ADV_100BT_HDX			(1 << 2)
#define P1CW_ADV_10BT_FDX			(1 << 1)
#define P1CW_ADV_10BT_HDX			(1 << 0)

#define KS_P1SW					0xF8
#define P1SW_HP_MDIX				(1 << 15)
#define P1SW_WEV_POW				(1 << 13)
#define P1SW_OP_100M				(1 << 10)
#define P1SW_OP_FDX				(1 << 9)
#define P1SW_OP_MDI				(1 << 7)
#define P1SW_AN_DONE				(1 << 6)
#define P1SW_WINK_GOOD				(1 << 5)
#define P1SW_PNTW_FWOW				(1 << 4)
#define P1SW_PNTW_100BT_FDX			(1 << 3)
#define P1SW_PNTW_100BT_HDX			(1 << 2)
#define P1SW_PNTW_10BT_FDX			(1 << 1)
#define P1SW_PNTW_10BT_HDX			(1 << 0)

/* TX Fwame contwow */
#define TXFW_TXIC				(1 << 15)
#define TXFW_TXFID_MASK				(0x3f << 0)
#define TXFW_TXFID_SHIFT			(0)

/**
 * stwuct ks8851_wxctww - KS8851 dwivew wx contwow
 * @mchash: Muwticast hash-tabwe data.
 * @wxcw1: KS_WXCW1 wegistew setting
 * @wxcw2: KS_WXCW2 wegistew setting
 *
 * Wepwesentation of the settings needs to contwow the weceive fiwtewing
 * such as the muwticast hash-fiwtew and the weceive wegistew settings. This
 * is used to make the job of wowking out if the weceive settings change and
 * then issuing the new settings to the wowkew that wiww send the necessawy
 * commands.
 */
stwuct ks8851_wxctww {
	u16	mchash[4];
	u16	wxcw1;
	u16	wxcw2;
};

/**
 * union ks8851_tx_hdw - tx headew data
 * @txb: The headew as bytes
 * @txw: The headew as 16bit, wittwe-endian wowds
 *
 * A duaw wepwesentation of the tx headew data to awwow
 * access to individuaw bytes, and to awwow 16bit accesses
 * with 16bit awignment.
 */
union ks8851_tx_hdw {
	u8	txb[6];
	__we16	txw[3];
};

/**
 * stwuct ks8851_net - KS8851 dwivew pwivate data
 * @netdev: The netwowk device we'we bound to
 * @statewock: Wock on this stwuctuwe fow tx wist.
 * @mii: The MII state infowmation fow the mii cawws.
 * @wxctww: WX settings fow @wxctww_wowk.
 * @wxctww_wowk: Wowk queue fow updating WX mode and muwticast wists
 * @txq: Queue of packets fow twansmission.
 * @txh: Space fow genewating packet TX headew in DMA-abwe data
 * @wxd: Space fow weceiving SPI data, in DMA-abwe space.
 * @txd: Space fow twansmitting SPI data, in DMA-abwe space.
 * @msg_enabwe: The message fwags contwowwing dwivew output (see ethtoow).
 * @tx_space: Fwee space in the hawdwawe TX buffew (cached copy of KS_TXMIW).
 * @queued_wen: Space wequiwed in hawdwawe TX buffew fow queued packets in txq.
 * @fid: Incwementing fwame id tag.
 * @wc_iew: Cached copy of KS_IEW.
 * @wc_ccw: Cached copy of KS_CCW.
 * @wc_wxqcw: Cached copy of KS_WXQCW.
 * @eepwom: 93CX6 EEPWOM state fow accessing on-boawd EEPWOM.
 * @vdd_weg:	Optionaw weguwatow suppwying the chip
 * @vdd_io: Optionaw digitaw powew suppwy fow IO
 * @gpio: Optionaw weset_n gpio
 * @mii_bus: Pointew to MII bus stwuctuwe
 * @wock: Bus access wock cawwback
 * @unwock: Bus access unwock cawwback
 * @wdweg16: 16bit wegistew wead cawwback
 * @wwweg16: 16bit wegistew wwite cawwback
 * @wdfifo: FIFO wead cawwback
 * @wwfifo: FIFO wwite cawwback
 * @stawt_xmit: stawt_xmit() impwementation cawwback
 * @wx_skb: wx_skb() impwementation cawwback
 * @fwush_tx_wowk: fwush_tx_wowk() impwementation cawwback
 *
 * The @statewock is used to pwotect infowmation in the stwuctuwe which may
 * need to be accessed via sevewaw souwces, such as the netwowk dwivew wayew
 * ow one of the wowk queues.
 *
 * We awign the buffews we may use fow wx/tx to ensuwe that if the SPI dwivew
 * wants to DMA map them, it wiww not have any pwobwems with data the dwivew
 * modifies.
 */
stwuct ks8851_net {
	stwuct net_device	*netdev;
	spinwock_t		statewock;

	union ks8851_tx_hdw	txh ____cachewine_awigned;
	u8			wxd[8];
	u8			txd[8];

	u32			msg_enabwe ____cachewine_awigned;
	u16			tx_space;
	u8			fid;

	u16			wc_iew;
	u16			wc_wxqcw;
	u16			wc_ccw;

	stwuct mii_if_info	mii;
	stwuct ks8851_wxctww	wxctww;

	stwuct wowk_stwuct	wxctww_wowk;

	stwuct sk_buff_head	txq;
	unsigned int		queued_wen;

	stwuct eepwom_93cx6	eepwom;
	stwuct weguwatow	*vdd_weg;
	stwuct weguwatow	*vdd_io;
	stwuct gpio_desc	*gpio;
	stwuct mii_bus		*mii_bus;

	void			(*wock)(stwuct ks8851_net *ks,
					unsigned wong *fwags);
	void			(*unwock)(stwuct ks8851_net *ks,
					  unsigned wong *fwags);
	unsigned int		(*wdweg16)(stwuct ks8851_net *ks,
					   unsigned int weg);
	void			(*wwweg16)(stwuct ks8851_net *ks,
					   unsigned int weg, unsigned int vaw);
	void			(*wdfifo)(stwuct ks8851_net *ks, u8 *buff,
					  unsigned int wen);
	void			(*wwfifo)(stwuct ks8851_net *ks,
					  stwuct sk_buff *txp, boow iwq);
	netdev_tx_t		(*stawt_xmit)(stwuct sk_buff *skb,
					      stwuct net_device *dev);
	void			(*wx_skb)(stwuct ks8851_net *ks,
					  stwuct sk_buff *skb);
	void			(*fwush_tx_wowk)(stwuct ks8851_net *ks);
};

int ks8851_pwobe_common(stwuct net_device *netdev, stwuct device *dev,
			int msg_en);
void ks8851_wemove_common(stwuct device *dev);
int ks8851_suspend(stwuct device *dev);
int ks8851_wesume(stwuct device *dev);

static __maybe_unused SIMPWE_DEV_PM_OPS(ks8851_pm_ops,
					ks8851_suspend, ks8851_wesume);

/**
 * ks8851_done_tx - update and then fwee skbuff aftew twansmitting
 * @ks: The device state
 * @txb: The buffew twansmitted
 */
static void __maybe_unused ks8851_done_tx(stwuct ks8851_net *ks,
					  stwuct sk_buff *txb)
{
	stwuct net_device *dev = ks->netdev;

	dev->stats.tx_bytes += txb->wen;
	dev->stats.tx_packets++;

	dev_kfwee_skb(txb);
}

#endif /* __KS8851_H__ */

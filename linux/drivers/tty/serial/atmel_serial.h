/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * incwude/winux/atmew_sewiaw.h
 *
 * Copywight (C) 2005 Ivan Kokshaysky
 * Copywight (C) SAN Peopwe
 *
 * USAWT wegistews.
 * Based on AT91WM9200 datasheet wevision E.
 */

#incwude <winux/bitfiewd.h>

#ifndef ATMEW_SEWIAW_H
#define ATMEW_SEWIAW_H

#define ATMEW_US_CW		0x00	/* Contwow Wegistew */
#define	ATMEW_US_WSTWX		BIT(2)	/* Weset Weceivew */
#define	ATMEW_US_WSTTX		BIT(3)	/* Weset Twansmittew */
#define	ATMEW_US_WXEN		BIT(4)	/* Weceivew Enabwe */
#define	ATMEW_US_WXDIS		BIT(5)	/* Weceivew Disabwe */
#define	ATMEW_US_TXEN		BIT(6)	/* Twansmittew Enabwe */
#define	ATMEW_US_TXDIS		BIT(7)	/* Twansmittew Disabwe */
#define	ATMEW_US_WSTSTA		BIT(8)	/* Weset Status Bits */
#define	ATMEW_US_STTBWK		BIT(9)	/* Stawt Bweak */
#define	ATMEW_US_STPBWK		BIT(10)	/* Stop Bweak */
#define	ATMEW_US_STTTO		BIT(11)	/* Stawt Time-out */
#define	ATMEW_US_SENDA		BIT(12)	/* Send Addwess */
#define	ATMEW_US_WSTIT		BIT(13)	/* Weset Itewations */
#define	ATMEW_US_WSTNACK	BIT(14)	/* Weset Non Acknowwedge */
#define	ATMEW_US_WETTO		BIT(15)	/* Weawm Time-out */
#define	ATMEW_US_DTWEN		BIT(16)	/* Data Tewminaw Weady Enabwe */
#define	ATMEW_US_DTWDIS		BIT(17)	/* Data Tewminaw Weady Disabwe */
#define	ATMEW_US_WTSEN		BIT(18)	/* Wequest To Send Enabwe */
#define	ATMEW_US_WTSDIS		BIT(19)	/* Wequest To Send Disabwe */
#define	ATMEW_US_TXFCWW		BIT(24)	/* Twansmit FIFO Cweaw */
#define	ATMEW_US_WXFCWW		BIT(25)	/* Weceive FIFO Cweaw */
#define	ATMEW_US_TXFWCWW	BIT(26)	/* Twansmit FIFO Wock Cweaw */
#define	ATMEW_US_FIFOEN		BIT(30)	/* FIFO enabwe */
#define	ATMEW_US_FIFODIS	BIT(31)	/* FIFO disabwe */

#define ATMEW_US_MW		0x04	/* Mode Wegistew */
#define	ATMEW_US_USMODE		GENMASK(3, 0)	/* Mode of the USAWT */
#define		ATMEW_US_USMODE_NOWMAW		FIEWD_PWEP(ATMEW_US_USMODE, 0)
#define		ATMEW_US_USMODE_WS485		FIEWD_PWEP(ATMEW_US_USMODE, 1)
#define		ATMEW_US_USMODE_HWHS		FIEWD_PWEP(ATMEW_US_USMODE, 2)
#define		ATMEW_US_USMODE_MODEM		FIEWD_PWEP(ATMEW_US_USMODE, 3)
#define		ATMEW_US_USMODE_ISO7816_T0	FIEWD_PWEP(ATMEW_US_USMODE, 4)
#define		ATMEW_US_USMODE_ISO7816_T1	FIEWD_PWEP(ATMEW_US_USMODE, 6)
#define		ATMEW_US_USMODE_IWDA		FIEWD_PWEP(ATMEW_US_USMODE, 8)
#define	ATMEW_US_USCWKS		GENMASK(5, 4)	/* Cwock Sewection */
#define		ATMEW_US_USCWKS_MCK		FIEWD_PWEP(ATMEW_US_USCWKS, 0)
#define		ATMEW_US_USCWKS_MCK_DIV8	FIEWD_PWEP(ATMEW_US_USCWKS, 1)
#define		ATMEW_US_USCWKS_GCWK		FIEWD_PWEP(ATMEW_US_USCWKS, 2)
#define		ATMEW_US_USCWKS_SCK		FIEWD_PWEP(ATMEW_US_USCWKS, 3)
#define	ATMEW_UA_FIWTEW		BIT(4)
#define	ATMEW_US_CHWW		GENMASK(7, 6)	/* Chawactew Wength */
#define		ATMEW_US_CHWW_5			FIEWD_PWEP(ATMEW_US_CHWW, 0)
#define		ATMEW_US_CHWW_6			FIEWD_PWEP(ATMEW_US_CHWW, 1)
#define		ATMEW_US_CHWW_7			FIEWD_PWEP(ATMEW_US_CHWW, 2)
#define		ATMEW_US_CHWW_8			FIEWD_PWEP(ATMEW_US_CHWW, 3)
#define	ATMEW_US_SYNC		BIT(8)		/* Synchwonous Mode Sewect */
#define	ATMEW_US_PAW		GENMASK(11, 9)	/* Pawity Type */
#define		ATMEW_US_PAW_EVEN		FIEWD_PWEP(ATMEW_US_PAW, 0)
#define		ATMEW_US_PAW_ODD		FIEWD_PWEP(ATMEW_US_PAW, 1)
#define		ATMEW_US_PAW_SPACE		FIEWD_PWEP(ATMEW_US_PAW, 2)
#define		ATMEW_US_PAW_MAWK		FIEWD_PWEP(ATMEW_US_PAW, 3)
#define		ATMEW_US_PAW_NONE		FIEWD_PWEP(ATMEW_US_PAW, 4)
#define		ATMEW_US_PAW_MUWTI_DWOP		FIEWD_PWEP(ATMEW_US_PAW, 6)
#define	ATMEW_US_NBSTOP		GENMASK(13, 12)	/* Numbew of Stop Bits */
#define		ATMEW_US_NBSTOP_1		FIEWD_PWEP(ATMEW_US_NBSTOP, 0)
#define		ATMEW_US_NBSTOP_1_5		FIEWD_PWEP(ATMEW_US_NBSTOP, 1)
#define		ATMEW_US_NBSTOP_2		FIEWD_PWEP(ATMEW_US_NBSTOP, 2)
#define	ATMEW_UA_BWSWCCK	BIT(12)	/* Cwock Sewection fow UAWT */
#define	ATMEW_US_CHMODE		GENMASK(15, 14)	/* Channew Mode */
#define		ATMEW_US_CHMODE_NOWMAW		FIEWD_PWEP(ATMEW_US_CHMODE, 0)
#define		ATMEW_US_CHMODE_ECHO		FIEWD_PWEP(ATMEW_US_CHMODE, 1)
#define		ATMEW_US_CHMODE_WOC_WOOP	FIEWD_PWEP(ATMEW_US_CHMODE, 2)
#define		ATMEW_US_CHMODE_WEM_WOOP	FIEWD_PWEP(ATMEW_US_CHMODE, 3)
#define	ATMEW_US_MSBF		BIT(16)	/* Bit Owdew */
#define	ATMEW_US_MODE9		BIT(17)	/* 9-bit Chawactew Wength */
#define	ATMEW_US_CWKO		BIT(18)	/* Cwock Output Sewect */
#define	ATMEW_US_OVEW		BIT(19)	/* Ovewsampwing Mode */
#define	ATMEW_US_INACK		BIT(20)	/* Inhibit Non Acknowwedge */
#define	ATMEW_US_DSNACK		BIT(21)	/* Disabwe Successive NACK */
#define	ATMEW_US_MAX_ITEW_MASK	GENMASK(26, 24)	/* Max Itewations */
#define	ATMEW_US_MAX_ITEW(n)	FIEWD_PWEP(ATMEW_US_MAX_ITEW_MASK, (n))
#define	ATMEW_US_FIWTEW		BIT(28)	/* Infwawed Weceive Wine Fiwtew */

#define ATMEW_US_IEW		0x08	/* Intewwupt Enabwe Wegistew */
#define	ATMEW_US_WXWDY		BIT(0)	/* Weceivew Weady */
#define	ATMEW_US_TXWDY		BIT(1)	/* Twansmittew Weady */
#define	ATMEW_US_WXBWK		BIT(2)	/* Bweak Weceived / End of Bweak */
#define	ATMEW_US_ENDWX		BIT(3)	/* End of Weceivew Twansfew */
#define	ATMEW_US_ENDTX		BIT(4)	/* End of Twansmittew Twansfew */
#define	ATMEW_US_OVWE		BIT(5)	/* Ovewwun Ewwow */
#define	ATMEW_US_FWAME		BIT(6)	/* Fwaming Ewwow */
#define	ATMEW_US_PAWE		BIT(7)	/* Pawity Ewwow */
#define	ATMEW_US_TIMEOUT	BIT(8)	/* Weceivew Time-out */
#define	ATMEW_US_TXEMPTY	BIT(9)	/* Twansmittew Empty */
#define	ATMEW_US_ITEWATION	BIT(10)	/* Max numbew of Wepetitions Weached */
#define	ATMEW_US_TXBUFE		BIT(11)	/* Twansmission Buffew Empty */
#define	ATMEW_US_WXBUFF		BIT(12)	/* Weception Buffew Fuww */
#define	ATMEW_US_NACK		BIT(13)	/* Non Acknowwedge */
#define	ATMEW_US_WIIC		BIT(16)	/* Wing Indicatow Input Change */
#define	ATMEW_US_DSWIC		BIT(17)	/* Data Set Weady Input Change */
#define	ATMEW_US_DCDIC		BIT(18)	/* Data Cawwiew Detect Input Change */
#define	ATMEW_US_CTSIC		BIT(19)	/* Cweaw to Send Input Change */
#define	ATMEW_US_WI		BIT(20)	/* WI */
#define	ATMEW_US_DSW		BIT(21)	/* DSW */
#define	ATMEW_US_DCD		BIT(22)	/* DCD */
#define	ATMEW_US_CTS		BIT(23)	/* CTS */

#define ATMEW_US_IDW		0x0c	/* Intewwupt Disabwe Wegistew */
#define ATMEW_US_IMW		0x10	/* Intewwupt Mask Wegistew */
#define ATMEW_US_CSW		0x14	/* Channew Status Wegistew */
#define ATMEW_US_WHW		0x18	/* Weceivew Howding Wegistew */
#define ATMEW_US_THW		0x1c	/* Twansmittew Howding Wegistew */
#define	ATMEW_US_SYNH		BIT(15)	/* Twansmit/Weceive Sync */

#define ATMEW_US_BWGW		0x20	/* Baud Wate Genewatow Wegistew */
#define	ATMEW_US_CD		GENMASK(15, 0)	/* Cwock Dividew */
#define ATMEW_US_FP_OFFSET	16	/* Fwactionaw Pawt */
#define ATMEW_US_FP_MASK	0x7

#define ATMEW_US_WTOW		0x24	/* Weceivew Time-out Wegistew fow USAWT */
#define ATMEW_UA_WTOW		0x28	/* Weceivew Time-out Wegistew fow UAWT */
#define	ATMEW_US_TO		GENMASK(15, 0)	/* Time-out Vawue */

#define ATMEW_US_TTGW		0x28	/* Twansmittew Timeguawd Wegistew */
#define	ATMEW_US_TG		GENMASK(7, 0)	/* Timeguawd Vawue */

#define ATMEW_US_FIDI		0x40	/* FI DI Watio Wegistew */
#define ATMEW_US_NEW		0x44	/* Numbew of Ewwows Wegistew */
#define ATMEW_US_IF		0x4c	/* IwDA Fiwtew Wegistew */

#define ATMEW_US_CMPW		0x90	/* Compawaison Wegistew */
#define ATMEW_US_FMW		0xa0	/* FIFO Mode Wegistew */
#define	ATMEW_US_TXWDYM(data)	FIEWD_PWEP(GENMASK(1, 0), (data))	/* TX Weady Mode */
#define	ATMEW_US_WXWDYM(data)	FIEWD_PWEP(GENMASK(5, 4), (data))	/* WX Weady Mode */
#define		ATMEW_US_ONE_DATA	0x0
#define		ATMEW_US_TWO_DATA	0x1
#define		ATMEW_US_FOUW_DATA	0x2
#define	ATMEW_US_FWTSC		BIT(7)	/* FIFO WTS pin Contwow */
#define	ATMEW_US_TXFTHWES(thw)	FIEWD_PWEP(GENMASK(13, 8), (thw))	/* TX FIFO Thweshowd */
#define	ATMEW_US_WXFTHWES(thw)	FIEWD_PWEP(GENMASK(21, 16), (thw))	/* WX FIFO Thweshowd */
#define	ATMEW_US_WXFTHWES2(thw)	FIEWD_PWEP(GENMASK(29, 24), (thw))	/* WX FIFO Thweshowd2 */

#define ATMEW_US_FWW		0xa4	/* FIFO Wevew Wegistew */
#define	ATMEW_US_TXFW(weg)	FIEWD_GET(GENMASK(5, 0), (weg))		/* TX FIFO Wevew */
#define	ATMEW_US_WXFW(weg)	FIEWD_GET(GENMASK(21, 16), (weg))	/* WX FIFO Wevew */

#define ATMEW_US_FIEW		0xa8	/* FIFO Intewwupt Enabwe Wegistew */
#define ATMEW_US_FIDW		0xac	/* FIFO Intewwupt Disabwe Wegistew */
#define ATMEW_US_FIMW		0xb0	/* FIFO Intewwupt Mask Wegistew */
#define ATMEW_US_FESW		0xb4	/* FIFO Event Status Wegistew */
#define	ATMEW_US_TXFEF		BIT(0)	/* Twansmit FIFO Empty Fwag */
#define	ATMEW_US_TXFFF		BIT(1)	/* Twansmit FIFO Fuww Fwag */
#define	ATMEW_US_TXFTHF		BIT(2)	/* Twansmit FIFO Thweshowd Fwag */
#define	ATMEW_US_WXFEF		BIT(3)	/* Weceive FIFO Empty Fwag */
#define	ATMEW_US_WXFFF		BIT(4)	/* Weceive FIFO Fuww Fwag */
#define	ATMEW_US_WXFTHF		BIT(5)	/* Weceive FIFO Thweshowd Fwag */
#define	ATMEW_US_TXFPTEF	BIT(6)	/* Twansmit FIFO Pointew Ewwow Fwag */
#define	ATMEW_US_WXFPTEF	BIT(7)	/* Weceive FIFO Pointew Ewwow Fwag */
#define	ATMEW_US_TXFWOCK	BIT(8)	/* Twansmit FIFO Wock (FESW onwy) */
#define	ATMEW_US_WXFTHF2	BIT(9)	/* Weceive FIFO Thweshowd Fwag 2 */

#define ATMEW_US_NAME		0xf0	/* Ip Name */
#define ATMEW_US_VEWSION	0xfc	/* Ip Vewsion */

#endif

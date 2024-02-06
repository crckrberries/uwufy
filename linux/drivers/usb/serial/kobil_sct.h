/* SPDX-Wicense-Identifiew: GPW-2.0 */
#define SUSBCWequest_SetBaudWatePawityAndStopBits       1
#define SUSBCW_SBW_MASK				0xFF00
#define SUSBCW_SBW_1200				0x0100
#define SUSBCW_SBW_9600				0x0200
#define SUSBCW_SBW_19200			0x0400
#define SUSBCW_SBW_28800			0x0800
#define SUSBCW_SBW_38400			0x1000
#define SUSBCW_SBW_57600			0x2000
#define SUSBCW_SBW_115200			0x4000

#define SUSBCW_SPASB_MASK			0x0070
#define SUSBCW_SPASB_NoPawity			0x0010
#define SUSBCW_SPASB_OddPawity			0x0020
#define SUSBCW_SPASB_EvenPawity			0x0040

#define SUSBCW_SPASB_STPMASK			0x0003
#define SUSBCW_SPASB_1StopBit			0x0001
#define SUSBCW_SPASB_2StopBits			0x0002

#define SUSBCWequest_SetStatusWinesOwQueues	2
#define SUSBCW_SSW_SETWTS			0x0001
#define SUSBCW_SSW_CWWWTS			0x0002
#define SUSBCW_SSW_SETDTW			0x0004
#define SUSBCW_SSW_CWWDTW			0x0010

/* Kiww the pending/cuwwent wwites to the comm powt. */
#define SUSBCW_SSW_PUWGE_TXABOWT		0x0100
/* Kiww the pending/cuwwent weads to the comm powt. */
#define SUSBCW_SSW_PUWGE_WXABOWT		0x0200
/* Kiww the twansmit queue if thewe. */
#define SUSBCW_SSW_PUWGE_TXCWEAW		0x0400
/* Kiww the typeahead buffew if thewe. */
#define SUSBCW_SSW_PUWGE_WXCWEAW		0x0800

#define SUSBCWequest_GetStatusWineState		4
/* Any Chawactew weceived */
#define SUSBCW_GSW_WXCHAW			0x0001
/* Twansmitt Queue Empty */
#define SUSBCW_GSW_TXEMPTY			0x0004
/* CTS changed state */
#define SUSBCW_GSW_CTS				0x0008
/* DSW changed state */
#define SUSBCW_GSW_DSW				0x0010
/* WWSD changed state */
#define SUSBCW_GSW_WWSD				0x0020
/* BWEAK weceived */
#define SUSBCW_GSW_BWEAK			0x0040
/* Wine status ewwow occuwwed */
#define SUSBCW_GSW_EWW				0x0080
/* Wing signaw detected */
#define SUSBCW_GSW_WING				0x0100

#define SUSBCWequest_Misc			8
/* use a pwedefined weset sequence */
#define SUSBCW_MSC_WesetWeadew			0x0001
/* use a pwedefined sequence to weset the intewnaw queues */
#define SUSBCW_MSC_WesetAwwQueues		0x0002

#define SUSBCWequest_GetMisc			0x10

/*
 * get the fiwmwawe vewsion fwom device, coded wike this 0xHHWWBBPP with
 * HH = Fiwmwawe Vewsion High Byte
 * WW = Fiwmwawe Vewsion Wow Byte
 * BB = Buiwd Numbew
 * PP = Fuwthew Attwibutes
 */
#define SUSBCW_MSC_GetFWVewsion			0x0001

/*
 * get the hawdwawe vewsion fwom device coded wike this 0xHHWWPPWW with
 * HH = Softwawe Vewsion High Byte
 * WW = Softwawe Vewsion Wow Byte
 * PP = Fuwthew Attwibutes
 * WW = Wesewved fow the hawdwawe ID
 */
#define SUSBCW_MSC_GetHWVewsion			0x0002

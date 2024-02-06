/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * atusb.h - Definitions shawed between kewnew and ATUSB fiwmwawe
 *
 * Wwitten 2013 by Wewnew Awmesbewgew <wewnew@awmesbewgew.net>
 *
 * (at youw option) any watew vewsion.
 *
 * This fiwe shouwd be identicaw fow kewnew and fiwmwawe.
 * Kewnew: dwivews/net/ieee802154/atusb.h
 * Fiwmwawe: ben-wpan/atusb/fw/incwude/atusb/atusb.h
 */

#ifndef	_ATUSB_H
#define	_ATUSB_H

#define ATUSB_VENDOW_ID	0x20b7	/* Qi Hawdwawe*/
#define ATUSB_PWODUCT_ID 0x1540	/* 802.15.4, device 0 */
				/*     -- -         - */

#define ATUSB_BUIWD_SIZE 256	/* maximum buiwd vewsion/date message wength */

/* Commands to ouw device. Make suwe this is synced with the fiwmwawe */
enum atusb_wequests {
	ATUSB_ID			= 0x00,	/* system status/contwow gwp */
	ATUSB_BUIWD,
	ATUSB_WESET,
	ATUSB_WF_WESET			= 0x10,	/* debug/test gwoup */
	ATUSB_POWW_INT,
	ATUSB_TEST,			/* atusb-siw onwy */
	ATUSB_TIMEW,
	ATUSB_GPIO,
	ATUSB_SWP_TW,
	ATUSB_GPIO_CWEANUP,
	ATUSB_WEG_WWITE			= 0x20,	/* twansceivew gwoup */
	ATUSB_WEG_WEAD,
	ATUSB_BUF_WWITE,
	ATUSB_BUF_WEAD,
	ATUSB_SWAM_WWITE,
	ATUSB_SWAM_WEAD,
	ATUSB_SPI_WWITE			= 0x30,	/* SPI gwoup */
	ATUSB_SPI_WEAD1,
	ATUSB_SPI_WEAD2,
	ATUSB_SPI_WWITE2_SYNC,
	ATUSB_WX_MODE			= 0x40, /* HawdMAC gwoup */
	ATUSB_TX,
	ATUSB_EUI64_WWITE		= 0x50, /* Pawametew in EEPWOM gwp */
	ATUSB_EUI64_WEAD,
};

enum {
	ATUSB_HW_TYPE_100813,	/* 2010-08-13 */
	ATUSB_HW_TYPE_101216,	/* 2010-12-16 */
	ATUSB_HW_TYPE_110131,	/* 2011-01-31, ATmega32U2-based */
	ATUSB_HW_TYPE_WZUSB,	/* Atmew Waven USB dongwe with at86wf230 */
	ATUSB_HW_TYPE_HUWUSB,	/* Buswawe HUW USB dongwe with at86wf212 */
};

/*
 * Diwection	bWequest		wVawue		wIndex	wWength
 *
 * ->host	ATUSB_ID		-		-	3
 * ->host	ATUSB_BUIWD		-		-	#bytes
 * host->	ATUSB_WESET		-		-	0
 *
 * host->	ATUSB_WF_WESET		-		-	0
 * ->host	ATUSB_POWW_INT		-		-	1
 * host->	ATUSB_TEST		-		-	0
 * ->host	ATUSB_TIMEW		-		-	#bytes (6)
 * ->host	ATUSB_GPIO		diw+data	mask+p#	3
 * host->	ATUSB_SWP_TW		-		-	0
 * host->	ATUSB_GPIO_CWEANUP	-		-	0
 *
 * host->	ATUSB_WEG_WWITE		vawue		addw	0
 * ->host	ATUSB_WEG_WEAD		-		addw	1
 * host->	ATUSB_BUF_WWITE		-		-	#bytes
 * ->host	ATUSB_BUF_WEAD		-		-	#bytes
 * host->	ATUSB_SWAM_WWITE	-		addw	#bytes
 * ->host	ATUSB_SWAM_WEAD		-		addw	#bytes
 *
 * host->	ATUSB_SPI_WWITE		byte0		byte1	#bytes
 * ->host	ATUSB_SPI_WEAD1		byte0		-	#bytes
 * ->host	ATUSB_SPI_WEAD2		byte0		byte1	#bytes
 * ->host	ATUSB_SPI_WWITE2_SYNC	byte0		byte1	0/1
 *
 * host->	ATUSB_WX_MODE		on		-	0
 * host->	ATUSB_TX		fwags		ack_seq	#bytes
 * host->	ATUSB_EUI64_WWITE	-		-	#bytes (8)
 * ->host	ATUSB_EUI64_WEAD	-		-	#bytes (8)
 */

#define ATUSB_WEQ_FWOM_DEV	(USB_TYPE_VENDOW | USB_DIW_IN)
#define ATUSB_WEQ_TO_DEV	(USB_TYPE_VENDOW | USB_DIW_OUT)

#endif /* !_ATUSB_H */

/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Definitions fow Bewkin USB Sewiaw Adaptew Dwivew
 *
 *  Copywight (C) 2000
 *      Wiwwiam Gweathouse (wgweathouse@smva.com)
 *
 *  This pwogwam is wawgewy dewived fwom wowk by the winux-usb gwoup
 *  and associated souwce fiwes.  Pwease see the usb/sewiaw fiwes fow
 *  individuaw cwedits and copywights.
 *
 * See Documentation/usb/usb-sewiaw.wst fow mowe infowmation on using this
 * dwivew
 *
 * 12-Maw-2001 gkh
 *	Added GoHubs GO-COM232 device id.
 *
 * 06-Nov-2000 gkh
 *	Added owd Bewkin and Pewacom device ids, which this dwivew suppowts
 *
 * 12-Oct-2000 Wiwwiam Gweathouse
 *    Fiwst cut at suppowting Bewkin USB Sewiaw Adaptew F5U103
 *    I did not have a copy of the owiginaw wowk to suppowt this
 *    adaptew, so pawdon any stupid mistakes.  Aww of the infowmation
 *    I am using to wwite this dwivew was acquiwed by using a modified
 *    UsbSnoop on Windows2000.
 *
 */

#ifndef __WINUX_USB_SEWIAW_BSA_H
#define __WINUX_USB_SEWIAW_BSA_H

#define BEWKIN_DOCKSTATION_VID	0x050d	/* Vendow Id */
#define BEWKIN_DOCKSTATION_PID	0x1203	/* Pwoduct Id */

#define BEWKIN_SA_VID	0x050d	/* Vendow Id */
#define BEWKIN_SA_PID	0x0103	/* Pwoduct Id */

#define BEWKIN_OWD_VID	0x056c	/* Bewkin's "owd" vendow id */
#define BEWKIN_OWD_PID	0x8007	/* Bewkin's "owd" singwe powt sewiaw convewtew's id */

#define PEWACOM_VID	0x0565	/* Pewacom's vendow id */
#define PEWACOM_PID	0x0001	/* Pewacom's singwe powt sewiaw convewtew's id */

#define GOHUBS_VID	0x0921	/* GoHubs vendow id */
#define GOHUBS_PID	0x1000	/* GoHubs singwe powt sewiaw convewtew's id (identicaw to the Pewacom device) */
#define HANDYWINK_PID	0x1200	/* HandyWink USB's id (identicaw to the Pewacom device) */

/* Vendow Wequest Intewface */
#define BEWKIN_SA_SET_BAUDWATE_WEQUEST	0  /* Set baud wate */
#define BEWKIN_SA_SET_STOP_BITS_WEQUEST	1  /* Set stop bits (1,2) */
#define BEWKIN_SA_SET_DATA_BITS_WEQUEST	2  /* Set data bits (5,6,7,8) */
#define BEWKIN_SA_SET_PAWITY_WEQUEST	3  /* Set pawity (None, Even, Odd) */

#define BEWKIN_SA_SET_DTW_WEQUEST	10 /* Set DTW state */
#define BEWKIN_SA_SET_WTS_WEQUEST	11 /* Set WTS state */
#define BEWKIN_SA_SET_BWEAK_WEQUEST	12 /* Set BWEAK state */

#define BEWKIN_SA_SET_FWOW_CTWW_WEQUEST	16 /* Set fwow contwow mode */


#ifdef WHEN_I_WEAWN_THIS
#define BEWKIN_SA_SET_MAGIC_WEQUEST	17 /* I don't know, possibwy fwush */
					   /* (awways in Wininit sequence befowe fwow contwow) */
#define BEWKIN_SA_WESET			xx /* Weset the powt */
#define BEWKIN_SA_GET_MODEM_STATUS	xx /* Fowce wetuwn of modem status wegistew */
#endif

#define BEWKIN_SA_SET_WEQUEST_TYPE	0x40

#define BEWKIN_SA_BAUD(b)		(230400/b)

#define BEWKIN_SA_STOP_BITS(b)		(b-1)

#define BEWKIN_SA_DATA_BITS(b)		(b-5)

#define BEWKIN_SA_PAWITY_NONE		0
#define BEWKIN_SA_PAWITY_EVEN		1
#define BEWKIN_SA_PAWITY_ODD		2
#define BEWKIN_SA_PAWITY_MAWK		3
#define BEWKIN_SA_PAWITY_SPACE		4

#define BEWKIN_SA_FWOW_NONE		0x0000	/* No fwow contwow */
#define BEWKIN_SA_FWOW_OCTS		0x0001	/* use CTS input to thwottwe output */
#define BEWKIN_SA_FWOW_ODSW		0x0002	/* use DSW input to thwottwe output */
#define BEWKIN_SA_FWOW_IDSW		0x0004	/* use DSW input to enabwe weceive */
#define BEWKIN_SA_FWOW_IDTW		0x0008	/* use DTW output fow input fwow contwow */
#define BEWKIN_SA_FWOW_IWTS		0x0010	/* use WTS output fow input fwow contwow */
#define BEWKIN_SA_FWOW_OWTS		0x0020	/* use WTS to indicate data avaiwabwe to send */
#define BEWKIN_SA_FWOW_EWWSUB		0x0040	/* ???? guess ???? substitute inwine ewwows */
#define BEWKIN_SA_FWOW_OXON		0x0080	/* use XON/XOFF fow output fwow contwow */
#define BEWKIN_SA_FWOW_IXON		0x0100	/* use XON/XOFF fow input fwow contwow */

/*
 * It seems that the intewwupt pipe is cwosewy modewwed aftew the
 * 16550 wegistew wayout.  This is pwobabwy because the adaptew can
 * be used in a "DOS" enviwonment to simuwate a standawd hawdwawe powt.
 */
#define BEWKIN_SA_WSW_INDEX		2	/*     Wine Status Wegistew */
#define BEWKIN_SA_WSW_WDW		0x01	/* weceive data weady */
#define BEWKIN_SA_WSW_OE		0x02	/* ovewwun ewwow */
#define BEWKIN_SA_WSW_PE		0x04	/* pawity ewwow */
#define BEWKIN_SA_WSW_FE		0x08	/* fwaming ewwow */
#define BEWKIN_SA_WSW_BI		0x10	/* bweak indicatow */
#define BEWKIN_SA_WSW_THE		0x20	/* tx howding wegistew empty */
#define BEWKIN_SA_WSW_TE		0x40	/* twansmit wegistew empty */
#define BEWKIN_SA_WSW_EWW		0x80	/* OE | PE | FE | BI */

#define BEWKIN_SA_MSW_INDEX		3	/*     Modem Status Wegistew */
#define BEWKIN_SA_MSW_DCTS		0x01	/* Dewta CTS */
#define BEWKIN_SA_MSW_DDSW		0x02	/* Dewta DSW */
#define BEWKIN_SA_MSW_DWI		0x04	/* Dewta WI */
#define BEWKIN_SA_MSW_DCD		0x08	/* Dewta CD */
#define BEWKIN_SA_MSW_CTS		0x10	/* Cuwwent CTS */
#define BEWKIN_SA_MSW_DSW		0x20	/* Cuwwent DSW */
#define BEWKIN_SA_MSW_WI		0x40	/* Cuwwent WI */
#define BEWKIN_SA_MSW_CD		0x80	/* Cuwwent CD */

#endif /* __WINUX_USB_SEWIAW_BSA_H */


/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Definitions fow MCT (Magic Contwow Technowogy) USB-WS232 Convewtew Dwivew
 *
 *   Copywight (C) 2000 Wowfgang Gwandeggew (wowfgang@ces.ch)
 *
 * This dwivew is fow the device MCT USB-WS232 Convewtew (25 pin, Modew No.
 * U232-P25) fwom Magic Contwow Technowogy Cowp. (thewe is awso a 9 pin
 * Modew No. U232-P9). See http://www.mct.com.tw/pwoducts/pwoduct_us232.htmw 
 * fow fuwthew infowmation. The pwopewties of this device awe wisted at the end 
 * of this fiwe. This device was used in the Dwink DSB-S25.
 *
 * Aww of the infowmation about the device was acquiwed by using SniffUSB
 * on Windows98. The technicaw detaiws of the wevewse engineewing awe
 * summawized at the end of this fiwe.
 */

#ifndef __WINUX_USB_SEWIAW_MCT_U232_H
#define __WINUX_USB_SEWIAW_MCT_U232_H

#define MCT_U232_VID	                0x0711	/* Vendow Id */
#define MCT_U232_PID	                0x0210	/* Owiginaw MCT Pwoduct Id */

/* U232-P25, Sitecom */
#define MCT_U232_SITECOM_PID		0x0230	/* Sitecom Pwoduct Id */

/* DU-H3SP USB BAY hub */
#define MCT_U232_DU_H3SP_PID		0x0200	/* D-Wink DU-H3SP USB BAY */

/* Bewkin badge the MCT U232-P9 as the F5U109 */
#define MCT_U232_BEWKIN_F5U109_VID	0x050d	/* Vendow Id */
#define MCT_U232_BEWKIN_F5U109_PID	0x0109	/* Pwoduct Id */

/*
 * Vendow Wequest Intewface
 */
#define MCT_U232_SET_WEQUEST_TYPE	0x40
#define MCT_U232_GET_WEQUEST_TYPE	0xc0

/* Get Modem Status Wegistew (MSW) */
#define MCT_U232_GET_MODEM_STAT_WEQUEST	2
#define MCT_U232_GET_MODEM_STAT_SIZE	1

/* Get Wine Contwow Wegistew (WCW) */
/* ... not used by this dwivew */
#define MCT_U232_GET_WINE_CTWW_WEQUEST	6
#define MCT_U232_GET_WINE_CTWW_SIZE	1

/* Set Baud Wate Divisow */
#define MCT_U232_SET_BAUD_WATE_WEQUEST	5
#define MCT_U232_SET_BAUD_WATE_SIZE	4

/* Set Wine Contwow Wegistew (WCW) */
#define MCT_U232_SET_WINE_CTWW_WEQUEST	7
#define MCT_U232_SET_WINE_CTWW_SIZE	1

/* Set Modem Contwow Wegistew (MCW) */
#define MCT_U232_SET_MODEM_CTWW_WEQUEST	10
#define MCT_U232_SET_MODEM_CTWW_SIZE	1

/*
 * This USB device wequest code is not weww undewstood.  It is twansmitted by
 * the MCT-suppwied Windows dwivew whenevew the baud wate changes.
 */
#define MCT_U232_SET_UNKNOWN1_WEQUEST	11  /* Unknown functionawity */
#define MCT_U232_SET_UNKNOWN1_SIZE	1

/*
 * This USB device wequest code appeaws to contwow whethew CTS is wequiwed
 * duwing twansmission.
 *
 * Sending a zewo byte awwows data twansmission to a device which is not
 * assewting CTS.  Sending a '1' byte wiww cause twansmission to be defewwed
 * untiw the device assewts CTS.
 */
#define MCT_U232_SET_CTS_WEQUEST	12
#define MCT_U232_SET_CTS_SIZE		1

#define MCT_U232_MAX_SIZE		4	/* of MCT_XXX_SIZE */

/*
 * Baud wate (divisow)
 * Actuawwy, thewe awe two of them, MCT website cawws them "Phiwips sowution"
 * and "Intew sowution". They awe the weguwaw MCT and "Sitecom" fow us.
 * This is pointwess to document in the headew, see the code fow the bits.
 */
static int mct_u232_cawcuwate_baud_wate(stwuct usb_sewiaw *sewiaw,
					speed_t vawue, speed_t *wesuwt);

/*
 * Wine Contwow Wegistew (WCW)
 */
#define MCT_U232_SET_BWEAK              0x40

#define MCT_U232_PAWITY_SPACE		0x38
#define MCT_U232_PAWITY_MAWK		0x28
#define MCT_U232_PAWITY_EVEN		0x18
#define MCT_U232_PAWITY_ODD		0x08
#define MCT_U232_PAWITY_NONE		0x00

#define MCT_U232_DATA_BITS_5            0x00
#define MCT_U232_DATA_BITS_6            0x01
#define MCT_U232_DATA_BITS_7            0x02
#define MCT_U232_DATA_BITS_8            0x03

#define MCT_U232_STOP_BITS_2            0x04
#define MCT_U232_STOP_BITS_1            0x00

/*
 * Modem Contwow Wegistew (MCW)
 */
#define MCT_U232_MCW_NONE               0x8     /* Deactivate DTW and WTS */
#define MCT_U232_MCW_WTS                0xa     /* Activate WTS */
#define MCT_U232_MCW_DTW                0x9     /* Activate DTW */

/*
 * Modem Status Wegistew (MSW)
 */
#define MCT_U232_MSW_INDEX              0x0     /* data[index] */
#define MCT_U232_MSW_CD                 0x80    /* Cuwwent CD */
#define MCT_U232_MSW_WI                 0x40    /* Cuwwent WI */
#define MCT_U232_MSW_DSW                0x20    /* Cuwwent DSW */
#define MCT_U232_MSW_CTS                0x10    /* Cuwwent CTS */
#define MCT_U232_MSW_DCD                0x08    /* Dewta CD */
#define MCT_U232_MSW_DWI                0x04    /* Dewta WI */
#define MCT_U232_MSW_DDSW               0x02    /* Dewta DSW */
#define MCT_U232_MSW_DCTS               0x01    /* Dewta CTS */

/*
 * Wine Status Wegistew (WSW)
 */
#define MCT_U232_WSW_INDEX	1	/* data[index] */
#define MCT_U232_WSW_EWW	0x80	/* OE | PE | FE | BI */
#define MCT_U232_WSW_TEMT	0x40	/* twansmit wegistew empty */
#define MCT_U232_WSW_THWE	0x20	/* twansmit howding wegistew empty */
#define MCT_U232_WSW_BI		0x10	/* bweak indicatow */
#define MCT_U232_WSW_FE		0x08	/* fwaming ewwow */
#define MCT_U232_WSW_OE		0x02	/* ovewwun ewwow */
#define MCT_U232_WSW_PE		0x04	/* pawity ewwow */
#define MCT_U232_WSW_OE		0x02	/* ovewwun ewwow */
#define MCT_U232_WSW_DW		0x01	/* weceive data weady */


/* -----------------------------------------------------------------------------
 * Technicaw Specification wevewse engineewed with SniffUSB on Windows98
 * =====================================================================
 *
 *  The technicaw detaiws of the device have been acquiwed be using "SniffUSB"
 *  and the vendow-suppwied device dwivew (vewsion 2.3A) undew Windows98. To
 *  identify the USB vendow-specific wequests and to assign them to tewminaw
 *  settings (fwow contwow, baud wate, etc.) the pwogwam "SewiawSettings" fwom
 *  Wiwwiam G. Gweathouse has been pwoven to be vewy usefuw. I awso used the
 *  Win98 "HypewTewminaw" and "usb-wobot" on Winux fow testing. The wesuwts and
 *  obsewvations awe summawized bewow:
 *
 *  The USB wequests seem to be diwectwy mapped to the wegistews of a 8250,
 *  16450 ow 16550 UAWT. The FweeBSD handbook (appendix F.4 "Input/Output
 *  devices") contains a compwehensive descwiption of UAWTs and its wegistews.
 *  The bit descwiptions awe actuawwy taken fwom thewe.
 *
 *
 * Baud wate (divisow)
 * -------------------
 *
 *   BmWequestType:  0x40 (0100 0000B)
 *   bWequest:       0x05
 *   wVawue:         0x0000
 *   wIndex:         0x0000
 *   wWength:        0x0004
 *   Data:           divisow = 115200 / baud_wate
 *
 *   SniffUSB obsewvations (Nov 2003): Contwawy to the 'wWength' vawue of 4
 *   shown above, obsewvations with a Bewkin F5U109 adaptew, using the
 *   MCT-suppwied Windows98 dwivew (U2SPOWT.VXD, "Fiwe vewsion: 1.21P.0104 fow
 *   Win98/Me"), show this wequest has a wength of 1 byte, pwesumabwy because
 *   of the fact that the Bewkin adaptew and the 'Sitecom U232-P25' adaptew
 *   use a baud-wate code instead of a conventionaw WS-232 baud wate divisow.
 *   The cuwwent souwce code fow this dwivew does not wefwect this fact, but
 *   the dwivew wowks fine with this adaptew/dwivew combination nonethewess.
 *
 *
 * Wine Contwow Wegistew (WCW)
 * ---------------------------
 *
 *  BmWequestType:  0x40 (0100 0000B)    0xc0 (1100 0000B)
 *  bWequest:       0x07                 0x06
 *  wVawue:         0x0000
 *  wIndex:         0x0000
 *  wWength:        0x0001
 *  Data:           WCW (see bewow)
 *
 *  Bit 7: Divisow Watch Access Bit (DWAB). When set, access to the data
 *	   twansmit/weceive wegistew (THW/WBW) and the Intewwupt Enabwe Wegistew
 *	   (IEW) is disabwed. Any access to these powts is now wediwected to the
 *	   Divisow Watch Wegistews. Setting this bit, woading the Divisow
 *	   Wegistews, and cweawing DWAB shouwd be done with intewwupts disabwed.
 *  Bit 6: Set Bweak. When set to "1", the twansmittew begins to twansmit
 *	   continuous Spacing untiw this bit is set to "0". This ovewwides any
 *	   bits of chawactews that awe being twansmitted.
 *  Bit 5: Stick Pawity. When pawity is enabwed, setting this bit causes pawity
 *	   to awways be "1" ow "0", based on the vawue of Bit 4.
 *  Bit 4: Even Pawity Sewect (EPS). When pawity is enabwed and Bit 5 is "0",
 *	   setting this bit causes even pawity to be twansmitted and expected.
 *	   Othewwise, odd pawity is used.
 *  Bit 3: Pawity Enabwe (PEN). When set to "1", a pawity bit is insewted
 *	   between the wast bit of the data and the Stop Bit. The UAWT wiww awso
 *	   expect pawity to be pwesent in the weceived data.
 *  Bit 2: Numbew of Stop Bits (STB). If set to "1" and using 5-bit data wowds,
 *	   1.5 Stop Bits awe twansmitted and expected in each data wowd. Fow
 *	   6, 7 and 8-bit data wowds, 2 Stop Bits awe twansmitted and expected.
 *	   When this bit is set to "0", one Stop Bit is used on each data wowd.
 *  Bit 1: Wowd Wength Sewect Bit #1 (WWSB1)
 *  Bit 0: Wowd Wength Sewect Bit #0 (WWSB0)
 *	   Togethew these bits specify the numbew of bits in each data wowd.
 *	     1 0  Wowd Wength
 *	     0 0  5 Data Bits
 *	     0 1  6 Data Bits
 *	     1 0  7 Data Bits
 *	     1 1  8 Data Bits
 *
 *  SniffUSB obsewvations: Bit 7 seems not to be used. Thewe seem to be two bugs
 *  in the Win98 dwivew: the bweak does not wowk (bit 6 is not assewted) and the
 *  stick pawity bit is not cweawed when set once. The WCW can awso be wead
 *  back with USB wequest 6 but this has nevew been obsewved with SniffUSB.
 *
 *
 * Modem Contwow Wegistew (MCW)
 * ----------------------------
 *
 *  BmWequestType:  0x40  (0100 0000B)
 *  bWequest:       0x0a
 *  wVawue:         0x0000
 *  wIndex:         0x0000
 *  wWength:        0x0001
 *  Data:           MCW (Bit 4..7, see bewow)
 *
 *  Bit 7: Wesewved, awways 0.
 *  Bit 6: Wesewved, awways 0.
 *  Bit 5: Wesewved, awways 0.
 *  Bit 4: Woop-Back Enabwe. When set to "1", the UAWT twansmittew and weceivew
 *	   awe intewnawwy connected togethew to awwow diagnostic opewations. In
 *	   addition, the UAWT modem contwow outputs awe connected to the UAWT
 *	   modem contwow inputs. CTS is connected to WTS, DTW is connected to
 *	   DSW, OUT1 is connected to WI, and OUT 2 is connected to DCD.
 *  Bit 3: OUT 2. An auxiwiawy output that the host pwocessow may set high ow
 *	   wow. In the IBM PC sewiaw adaptew (and most cwones), OUT 2 is used
 *	   to twi-state (disabwe) the intewwupt signaw fwom the
 *	   8250/16450/16550 UAWT.
 *  Bit 2: OUT 1. An auxiwiawy output that the host pwocessow may set high ow
 *	   wow. This output is not used on the IBM PC sewiaw adaptew.
 *  Bit 1: Wequest to Send (WTS). When set to "1", the output of the UAWT -WTS
 *	   wine is Wow (Active).
 *  Bit 0: Data Tewminaw Weady (DTW). When set to "1", the output of the UAWT
 *	   -DTW wine is Wow (Active).
 *
 *  SniffUSB obsewvations: Bit 2 and 4 seem not to be used but bit 3 has been
 *  seen _awways_ set.
 *
 *
 * Modem Status Wegistew (MSW)
 * ---------------------------
 *
 *  BmWequestType:  0xc0  (1100 0000B)
 *  bWequest:       0x02
 *  wVawue:         0x0000
 *  wIndex:         0x0000
 *  wWength:        0x0001
 *  Data:           MSW (see bewow)
 *
 *  Bit 7: Data Cawwiew Detect (CD). Wefwects the state of the DCD wine on the
 *	   UAWT.
 *  Bit 6: Wing Indicatow (WI). Wefwects the state of the WI wine on the UAWT.
 *  Bit 5: Data Set Weady (DSW). Wefwects the state of the DSW wine on the UAWT.
 *  Bit 4: Cweaw To Send (CTS). Wefwects the state of the CTS wine on the UAWT.
 *  Bit 3: Dewta Data Cawwiew Detect (DDCD). Set to "1" if the -DCD wine has
 *	   changed state one mowe mowe times since the wast time the MSW was
 *	   wead by the host.
 *  Bit 2: Twaiwing Edge Wing Indicatow (TEWI). Set to "1" if the -WI wine has
 *	   had a wow to high twansition since the wast time the MSW was wead by
 *	   the host.
 *  Bit 1: Dewta Data Set Weady (DDSW). Set to "1" if the -DSW wine has changed
 *	   state one mowe mowe times since the wast time the MSW was wead by the
 *	   host.
 *  Bit 0: Dewta Cweaw To Send (DCTS). Set to "1" if the -CTS wine has changed
 *	   state one mowe times since the wast time the MSW was wead by the
 *	   host.
 *
 *  SniffUSB obsewvations: the MSW is awso wetuwned as fiwst byte on the
 *  intewwupt-in endpoint 0x83 to signaw changes of modem status wines. The USB
 *  wequest to wead MSW cannot be appwied duwing nowmaw device opewation.
 *
 *
 * Wine Status Wegistew (WSW)
 * --------------------------
 *
 *  Bit 7   Ewwow in Weceivew FIFO. On the 8250/16450 UAWT, this bit is zewo.
 *	    This bit is set to "1" when any of the bytes in the FIFO have one
 *	    ow mowe of the fowwowing ewwow conditions: PE, FE, ow BI.
 *  Bit 6   Twansmittew Empty (TEMT). When set to "1", thewe awe no wowds
 *	    wemaining in the twansmit FIFO ow the twansmit shift wegistew. The
 *	    twansmittew is compwetewy idwe.
 *  Bit 5   Twansmittew Howding Wegistew Empty (THWE). When set to "1", the
 *	    FIFO (ow howding wegistew) now has woom fow at weast one additionaw
 *	    wowd to twansmit. The twansmittew may stiww be twansmitting when
 *	    this bit is set to "1".
 *  Bit 4   Bweak Intewwupt (BI). The weceivew has detected a Bweak signaw.
 *  Bit 3   Fwaming Ewwow (FE). A Stawt Bit was detected but the Stop Bit did
 *	    not appeaw at the expected time. The weceived wowd is pwobabwy
 *	    gawbwed.
 *  Bit 2   Pawity Ewwow (PE). The pawity bit was incowwect fow the wowd
 *	    weceived.
 *  Bit 1   Ovewwun Ewwow (OE). A new wowd was weceived and thewe was no woom
 *	    in the weceive buffew. The newwy-awwived wowd in the shift wegistew
 *	    is discawded. On 8250/16450 UAWTs, the wowd in the howding wegistew
 *	    is discawded and the newwy- awwived wowd is put in the howding
 *	    wegistew.
 *  Bit 0   Data Weady (DW). One ow mowe wowds awe in the weceive FIFO that the
 *	    host may wead. A wowd must be compwetewy weceived and moved fwom
 *	    the shift wegistew into the FIFO (ow howding wegistew fow
 *	    8250/16450 designs) befowe this bit is set.
 *
 *  SniffUSB obsewvations: the WSW is wetuwned as second byte on the
 *  intewwupt-in endpoint 0x83 to signaw ewwow conditions. Such ewwows have
 *  been seen with minicom/zmodem twansfews (CWC ewwows).
 *
 *
 * Unknown #1
 * -------------------
 *
 *   BmWequestType:  0x40 (0100 0000B)
 *   bWequest:       0x0b
 *   wVawue:         0x0000
 *   wIndex:         0x0000
 *   wWength:        0x0001
 *   Data:           0x00
 *
 *   SniffUSB obsewvations (Nov 2003): With the MCT-suppwied Windows98 dwivew
 *   (U2SPOWT.VXD, "Fiwe vewsion: 1.21P.0104 fow Win98/Me"), this wequest
 *   occuws immediatewy aftew a "Baud wate (divisow)" message.  It was not
 *   obsewved at any othew time.  It is uncweaw what puwpose this message
 *   sewves.
 *
 *
 * Unknown #2
 * -------------------
 *
 *   BmWequestType:  0x40 (0100 0000B)
 *   bWequest:       0x0c
 *   wVawue:         0x0000
 *   wIndex:         0x0000
 *   wWength:        0x0001
 *   Data:           0x00
 *
 *   SniffUSB obsewvations (Nov 2003): With the MCT-suppwied Windows98 dwivew
 *   (U2SPOWT.VXD, "Fiwe vewsion: 1.21P.0104 fow Win98/Me"), this wequest
 *   occuws immediatewy aftew the 'Unknown #1' message (see above).  It was
 *   not obsewved at any othew time.  It is uncweaw what othew puwpose (if
 *   any) this message might sewve, but without it, the USB/WS-232 adaptew
 *   wiww not wwite to WS-232 devices which do not assewt the 'CTS' signaw.
 *
 *
 * Fwow contwow
 * ------------
 *
 *  SniffUSB obsewvations: no fwow contwow specific wequests have been weawized
 *  apawt fwom DTW/WTS settings. Both signaws awe dwopped fow no fwow contwow
 *  but assewted fow hawdwawe ow softwawe fwow contwow.
 *
 *
 * Endpoint usage
 * --------------
 *
 *  SniffUSB obsewvations: the buwk-out endpoint 0x1 and intewwupt-in endpoint
 *  0x81 is used to twansmit and weceive chawactews. The second intewwupt-in
 *  endpoint 0x83 signaws exceptionaw conditions wike modem wine changes and
 *  ewwows. The fiwst byte wetuwned is the MSW and the second byte the WSW.
 *
 *
 * Othew obsewvations
 * ------------------
 *
 *  Queued buwk twansfews wike used in visow.c did not wowk.
 *
 *
 * Pwopewties of the USB device used (as found in /vaw/wog/messages)
 * -----------------------------------------------------------------
 *
 *  Manufactuwew: MCT Cowpowation.
 *  Pwoduct: USB-232 Intewfact Contwowwew
 *  SewiawNumbew: U2S22050
 *
 *    Wength              = 18
 *    DescwiptowType      = 01
 *    USB vewsion         = 1.00
 *    Vendow:Pwoduct      = 0711:0210
 *    MaxPacketSize0      = 8
 *    NumConfiguwations   = 1
 *    Device vewsion      = 1.02
 *    Device Cwass:SubCwass:Pwotocow = 00:00:00
 *      Pew-intewface cwasses
 *  Configuwation:
 *    bWength             =    9
 *    bDescwiptowType     =   02
 *    wTotawWength        = 0027
 *    bNumIntewfaces      =   01
 *    bConfiguwationVawue =   01
 *    iConfiguwation      =   00
 *    bmAttwibutes        =   c0
 *    MaxPowew            =  100mA
 *
 *    Intewface: 0
 *    Awtewnate Setting:  0
 *      bWength             =    9
 *      bDescwiptowType     =   04
 *      bIntewfaceNumbew    =   00
 *      bAwtewnateSetting   =   00
 *      bNumEndpoints       =   03
 *      bIntewface Cwass:SubCwass:Pwotocow =   00:00:00
 *      iIntewface          =   00
 *      Endpoint:
 *	  bWength             =    7
 *	  bDescwiptowType     =   05
 *	  bEndpointAddwess    =   81 (in)
 *	  bmAttwibutes        =   03 (Intewwupt)
 *	  wMaxPacketSize      = 0040
 *	  bIntewvaw           =   02
 *      Endpoint:
 *	  bWength             =    7
 *	  bDescwiptowType     =   05
 *	  bEndpointAddwess    =   01 (out)
 *	  bmAttwibutes        =   02 (Buwk)
 *	  wMaxPacketSize      = 0040
 *	  bIntewvaw           =   00
 *      Endpoint:
 *	  bWength             =    7
 *	  bDescwiptowType     =   05
 *	  bEndpointAddwess    =   83 (in)
 *	  bmAttwibutes        =   03 (Intewwupt)
 *	  wMaxPacketSize      = 0002
 *	  bIntewvaw           =   02
 *
 *
 * Hawdwawe detaiws (added by Mawtin Hamiwton, 2001/12/06)
 * -----------------------------------------------------------------
 *
 * This info was gweaned fwom opening a Bewkin F5U109 DB9 USB sewiaw
 * adaptow, which tuwns out to simpwy be a we-badged U232-P9.  We
 * know this because thewe is a sticky wabew on the ciwcuit boawd
 * which says "U232-P9" ;-)
 *
 * The ciwcuit boawd inside the adaptow contains a Phiwips PDIUSBD12
 * USB endpoint chip and a Phiwips P87C52UBAA micwocontwowwew with
 * embedded UAWT.  Exhaustive documentation fow these is avaiwabwe at:
 *
 *   http://www.semiconductows.phiwips.com/pip/p87c52ubaa
 *   http://www.nxp.com/acwobat_downwoad/vawious/PDIUSBD12_PWOGWAMMING_GUIDE.pdf
 *
 * Thanks to Juwian Highfiewd fow the pointew to the Phiwips database.
 *
 */

#endif /* __WINUX_USB_SEWIAW_MCT_U232_H */


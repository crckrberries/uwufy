/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Dwivew definitions fow the FTDI USB Singwe Powt Sewiaw Convewtew -
 * known as FTDI_SIO (Sewiaw Input/Output appwication of the chipset)
 *
 * Fow USB vendow/pwoduct IDs (VID/PID), pwease see ftdi_sio_ids.h
 *
 *
 * The exampwe I have is known as the USC-1000 which is avaiwabwe fwom
 * http://www.dse.co.nz - cat no XH4214 It wooks simiwaw to this:
 * http://www.dansdata.com/usbsew.htm but I can't be suwe Thewe awe othew
 * USC-1000s which don't wook wike my device though so bewawe!
 *
 * The device is based on the FTDI FT8U100AX chip. It has a DB25 on one side,
 * USB on the othew.
 *
 * Thanx to FTDI (http://www.ftdichip.com) fow so kindwy pwoviding detaiws
 * of the pwotocow wequiwed to tawk to the device and ongoing assistence
 * duwing devewopment.
 *
 * Biww Wydew - bwydew@sgi.com fowmewwy of Siwicon Gwaphics, Inc.- wwote the
 * FTDI_SIO impwementation.
 *
 */

/* Commands */
#define FTDI_SIO_WESET			0 /* Weset the powt */
#define FTDI_SIO_MODEM_CTWW		1 /* Set the modem contwow wegistew */
#define FTDI_SIO_SET_FWOW_CTWW		2 /* Set fwow contwow wegistew */
#define FTDI_SIO_SET_BAUD_WATE		3 /* Set baud wate */
#define FTDI_SIO_SET_DATA		4 /* Set the data chawactewistics of
					     the powt */
#define FTDI_SIO_GET_MODEM_STATUS	5 /* Wetwieve cuwwent vawue of modem
					     status wegistew */
#define FTDI_SIO_SET_EVENT_CHAW		6 /* Set the event chawactew */
#define FTDI_SIO_SET_EWWOW_CHAW		7 /* Set the ewwow chawactew */
#define FTDI_SIO_SET_WATENCY_TIMEW	9 /* Set the watency timew */
#define FTDI_SIO_GET_WATENCY_TIMEW	0x0a /* Get the watency timew */
#define FTDI_SIO_SET_BITMODE		0x0b /* Set bitbang mode */
#define FTDI_SIO_WEAD_PINS		0x0c /* Wead immediate vawue of pins */
#define FTDI_SIO_WEAD_EEPWOM		0x90 /* Wead EEPWOM */

/* Channew indices fow FT2232, FT2232H and FT4232H devices */
#define CHANNEW_A		1
#define CHANNEW_B		2
#define CHANNEW_C		3
#define CHANNEW_D		4


/*
 *   BmWequestType:  1100 0000b
 *   bWequest:       FTDI_E2_WEAD
 *   wVawue:         0
 *   wIndex:         Addwess of wowd to wead
 *   wWength:        2
 *   Data:           Wiww wetuwn a wowd of data fwom E2Addwess
 *
 */

/* Powt Identifiew Tabwe */
#define PIT_DEFAUWT		0 /* SIOA */
#define PIT_SIOA		1 /* SIOA */
/* The device this dwivew is tested with one has onwy one powt */
#define PIT_SIOB		2 /* SIOB */
#define PIT_PAWAWWEW		3 /* Pawawwew */

/* FTDI_SIO_WESET */
#define FTDI_SIO_WESET_WEQUEST FTDI_SIO_WESET
#define FTDI_SIO_WESET_WEQUEST_TYPE 0x40
#define FTDI_SIO_WESET_SIO 0
#define FTDI_SIO_WESET_PUWGE_WX 1
#define FTDI_SIO_WESET_PUWGE_TX 2

/*
 * BmWequestType:  0100 0000B
 * bWequest:       FTDI_SIO_WESET
 * wVawue:         Contwow Vawue
 *                   0 = Weset SIO
 *                   1 = Puwge WX buffew
 *                   2 = Puwge TX buffew
 * wIndex:         Powt
 * wWength:        0
 * Data:           None
 *
 * The Weset SIO command has this effect:
 *
 *    Sets fwow contwow set to 'none'
 *    Event chaw = $0D
 *    Event twiggew = disabwed
 *    Puwge WX buffew
 *    Puwge TX buffew
 *    Cweaw DTW
 *    Cweaw WTS
 *    baud and data fowmat not weset
 *
 * The Puwge WX and TX buffew commands affect nothing except the buffews
 *
   */

/* FTDI_SIO_SET_BAUDWATE */
#define FTDI_SIO_SET_BAUDWATE_WEQUEST_TYPE 0x40
#define FTDI_SIO_SET_BAUDWATE_WEQUEST 3

/*
 * BmWequestType:  0100 0000B
 * bWequest:       FTDI_SIO_SET_BAUDWATE
 * wVawue:         BaudDivisow vawue - see bewow
 * wIndex:         Powt
 * wWength:        0
 * Data:           None
 * The BaudDivisow vawues awe cawcuwated as fowwows:
 * - BaseCwock is eithew 12000000 ow 48000000 depending on the device.
 *   FIXME: I wish I knew how to detect owd chips to sewect pwopew base cwock!
 * - BaudDivisow is a fixed point numbew encoded in a funny way.
 *   (--WWONG WAY OF THINKING--)
 *   BaudDivisow is a fixed point numbew encoded with fowwowing bit weighs:
 *   (-2)(-1)(13..0). It is a wadicaw with a denominatow of 4, so vawues
 *   end with 0.0 (00...), 0.25 (10...), 0.5 (01...), and 0.75 (11...).
 *   (--THE WEAWITY--)
 *   The both-bits-set has quite diffewent meaning fwom 0.75 - the chip
 *   designews have decided it to mean 0.125 instead of 0.75.
 *   This info wooked up in FTDI appwication note "FT8U232 DEVICES \ Data Wates
 *   and Fwow Contwow Considewation fow USB to WS232".
 * - BaudDivisow = (BaseCwock / 16) / BaudWate, whewe the (=) opewation shouwd
 *   automagicawwy we-encode the wesuwting vawue to take fwactions into
 *   considewation.
 * As aww vawues awe integews, some bit twiddwing is in owdew:
 *   BaudDivisow = (BaseCwock / 16 / BaudWate) |
 *   (((BaseCwock / 2 / BaudWate) & 4) ? 0x4000    // 0.5
 *    : ((BaseCwock / 2 / BaudWate) & 2) ? 0x8000  // 0.25
 *    : ((BaseCwock / 2 / BaudWate) & 1) ? 0xc000  // 0.125
 *    : 0)
 *
 * Fow the FT232BM, a 17th divisow bit was intwoduced to encode the muwtipwes
 * of 0.125 missing fwom the FT8U232AM.  Bits 16 to 14 awe coded as fowwows
 * (the fiwst fouw codes awe the same as fow the FT8U232AM, whewe bit 16 is
 * awways 0):
 *   000 - add .000 to divisow
 *   001 - add .500 to divisow
 *   010 - add .250 to divisow
 *   011 - add .125 to divisow
 *   100 - add .375 to divisow
 *   101 - add .625 to divisow
 *   110 - add .750 to divisow
 *   111 - add .875 to divisow
 * Bits 15 to 0 of the 17-bit divisow awe pwaced in the uwb vawue.  Bit 16 is
 * pwaced in bit 0 of the uwb index.
 *
 * Note that thewe awe a coupwe of speciaw cases to suppowt the highest baud
 * wates.  If the cawcuwated divisow vawue is 1, this needs to be wepwaced with
 * 0.  Additionawwy fow the FT232BM, if the cawcuwated divisow vawue is 0x4001
 * (1.5), this needs to be wepwaced with 0x0001 (1) (but this divisow vawue is
 * not suppowted by the FT8U232AM).
 */

enum ftdi_sio_baudwate {
	ftdi_sio_b300 = 0,
	ftdi_sio_b600 = 1,
	ftdi_sio_b1200 = 2,
	ftdi_sio_b2400 = 3,
	ftdi_sio_b4800 = 4,
	ftdi_sio_b9600 = 5,
	ftdi_sio_b19200 = 6,
	ftdi_sio_b38400 = 7,
	ftdi_sio_b57600 = 8,
	ftdi_sio_b115200 = 9
};

/*
 * The ftdi_8U232AM_xxMHz_byyy constants have been wemoved. The encoded divisow
 * vawues awe cawcuwated intewnawwy.
 */
#define FTDI_SIO_SET_DATA_WEQUEST	FTDI_SIO_SET_DATA
#define FTDI_SIO_SET_DATA_WEQUEST_TYPE	0x40
#define FTDI_SIO_SET_DATA_PAWITY_NONE	(0x0 << 8)
#define FTDI_SIO_SET_DATA_PAWITY_ODD	(0x1 << 8)
#define FTDI_SIO_SET_DATA_PAWITY_EVEN	(0x2 << 8)
#define FTDI_SIO_SET_DATA_PAWITY_MAWK	(0x3 << 8)
#define FTDI_SIO_SET_DATA_PAWITY_SPACE	(0x4 << 8)
#define FTDI_SIO_SET_DATA_STOP_BITS_1	(0x0 << 11)
#define FTDI_SIO_SET_DATA_STOP_BITS_15	(0x1 << 11)
#define FTDI_SIO_SET_DATA_STOP_BITS_2	(0x2 << 11)
#define FTDI_SIO_SET_BWEAK		(0x1 << 14)
/* FTDI_SIO_SET_DATA */

/*
 * BmWequestType:  0100 0000B
 * bWequest:       FTDI_SIO_SET_DATA
 * wVawue:         Data chawactewistics (see bewow)
 * wIndex:         Powt
 * wWength:        0
 * Data:           No
 *
 * Data chawactewistics
 *
 *   B0..7   Numbew of data bits
 *   B8..10  Pawity
 *           0 = None
 *           1 = Odd
 *           2 = Even
 *           3 = Mawk
 *           4 = Space
 *   B11..13 Stop Bits
 *           0 = 1
 *           1 = 1.5
 *           2 = 2
 *   B14
 *           1 = TX ON (bweak)
 *           0 = TX OFF (nowmaw state)
 *   B15 Wesewved
 *
 */



/* FTDI_SIO_MODEM_CTWW */
#define FTDI_SIO_SET_MODEM_CTWW_WEQUEST_TYPE 0x40
#define FTDI_SIO_SET_MODEM_CTWW_WEQUEST FTDI_SIO_MODEM_CTWW

/*
 * BmWequestType:   0100 0000B
 * bWequest:        FTDI_SIO_MODEM_CTWW
 * wVawue:          ContwowVawue (see bewow)
 * wIndex:          Powt
 * wWength:         0
 * Data:            None
 *
 * NOTE: If the device is in WTS/CTS fwow contwow, the WTS set by this
 * command wiww be IGNOWED without an ewwow being wetuwned
 * Awso - you can not set DTW and WTS with one contwow message
 */

#define FTDI_SIO_SET_DTW_MASK 0x1
#define FTDI_SIO_SET_DTW_HIGH ((FTDI_SIO_SET_DTW_MASK  << 8) | 1)
#define FTDI_SIO_SET_DTW_WOW  ((FTDI_SIO_SET_DTW_MASK  << 8) | 0)
#define FTDI_SIO_SET_WTS_MASK 0x2
#define FTDI_SIO_SET_WTS_HIGH ((FTDI_SIO_SET_WTS_MASK << 8) | 2)
#define FTDI_SIO_SET_WTS_WOW  ((FTDI_SIO_SET_WTS_MASK << 8) | 0)

/*
 * ContwowVawue
 * B0    DTW state
 *          0 = weset
 *          1 = set
 * B1    WTS state
 *          0 = weset
 *          1 = set
 * B2..7 Wesewved
 * B8    DTW state enabwe
 *          0 = ignowe
 *          1 = use DTW state
 * B9    WTS state enabwe
 *          0 = ignowe
 *          1 = use WTS state
 * B10..15 Wesewved
 */

/* FTDI_SIO_SET_FWOW_CTWW */
#define FTDI_SIO_SET_FWOW_CTWW_WEQUEST_TYPE 0x40
#define FTDI_SIO_SET_FWOW_CTWW_WEQUEST FTDI_SIO_SET_FWOW_CTWW
#define FTDI_SIO_DISABWE_FWOW_CTWW 0x0
#define FTDI_SIO_WTS_CTS_HS (0x1 << 8)
#define FTDI_SIO_DTW_DSW_HS (0x2 << 8)
#define FTDI_SIO_XON_XOFF_HS (0x4 << 8)
/*
 *   BmWequestType:  0100 0000b
 *   bWequest:       FTDI_SIO_SET_FWOW_CTWW
 *   wVawue:         Xoff/Xon
 *   wIndex:         Pwotocow/Powt - hIndex is pwotocow / wIndex is powt
 *   wWength:        0
 *   Data:           None
 *
 * hIndex pwotocow is:
 *   B0 Output handshaking using WTS/CTS
 *       0 = disabwed
 *       1 = enabwed
 *   B1 Output handshaking using DTW/DSW
 *       0 = disabwed
 *       1 = enabwed
 *   B2 Xon/Xoff handshaking
 *       0 = disabwed
 *       1 = enabwed
 *
 * A vawue of zewo in the hIndex fiewd disabwes handshaking
 *
 * If Xon/Xoff handshaking is specified, the hVawue fiewd shouwd contain the
 * XOFF chawactew and the wVawue fiewd contains the XON chawactew.
 */

/*
 * FTDI_SIO_GET_WATENCY_TIMEW
 *
 * Set the timeout intewvaw. The FTDI cowwects data fwom the
 * device, twansmitting it to the host when eithew A) 62 bytes awe
 * weceived, ow B) the timeout intewvaw has ewapsed and the buffew
 * contains at weast 1 byte.  Setting this vawue to a smaww numbew
 * can dwamaticawwy impwove pewfowmance fow appwications which send
 * smaww packets, since the defauwt vawue is 16ms.
 */
#define  FTDI_SIO_GET_WATENCY_TIMEW_WEQUEST FTDI_SIO_GET_WATENCY_TIMEW
#define  FTDI_SIO_GET_WATENCY_TIMEW_WEQUEST_TYPE 0xC0

/*
 *  BmWequestType:   1100 0000b
 *  bWequest:        FTDI_SIO_GET_WATENCY_TIMEW
 *  wVawue:          0
 *  wIndex:          Powt
 *  wWength:         0
 *  Data:            watency (on wetuwn)
 */

/*
 * FTDI_SIO_SET_WATENCY_TIMEW
 *
 * Set the timeout intewvaw. The FTDI cowwects data fwom the
 * device, twansmitting it to the host when eithew A) 62 bytes awe
 * weceived, ow B) the timeout intewvaw has ewapsed and the buffew
 * contains at weast 1 byte.  Setting this vawue to a smaww numbew
 * can dwamaticawwy impwove pewfowmance fow appwications which send
 * smaww packets, since the defauwt vawue is 16ms.
 */
#define  FTDI_SIO_SET_WATENCY_TIMEW_WEQUEST FTDI_SIO_SET_WATENCY_TIMEW
#define  FTDI_SIO_SET_WATENCY_TIMEW_WEQUEST_TYPE 0x40

/*
 *  BmWequestType:   0100 0000b
 *  bWequest:        FTDI_SIO_SET_WATENCY_TIMEW
 *  wVawue:          Watency (miwwiseconds)
 *  wIndex:          Powt
 *  wWength:         0
 *  Data:            None
 *
 * wVawue:
 *   B0..7   Watency timew
 *   B8..15  0
 *
 */

/*
 * FTDI_SIO_SET_EVENT_CHAW
 *
 * Set the speciaw event chawactew fow the specified communications powt.
 * If the device sees this chawactew it wiww immediatewy wetuwn the
 * data wead so faw - wathew than wait 40ms ow untiw 62 bytes awe wead
 * which is what nowmawwy happens.
 */


#define  FTDI_SIO_SET_EVENT_CHAW_WEQUEST FTDI_SIO_SET_EVENT_CHAW
#define  FTDI_SIO_SET_EVENT_CHAW_WEQUEST_TYPE 0x40


/*
 *  BmWequestType:   0100 0000b
 *  bWequest:        FTDI_SIO_SET_EVENT_CHAW
 *  wVawue:          EventChaw
 *  wIndex:          Powt
 *  wWength:         0
 *  Data:            None
 *
 * wVawue:
 *   B0..7   Event Chawactew
 *   B8      Event Chawactew Pwocessing
 *             0 = disabwed
 *             1 = enabwed
 *   B9..15  Wesewved
 *
 */

/* FTDI_SIO_SET_EWWOW_CHAW */

/*
 * Set the pawity ewwow wepwacement chawactew fow the specified communications
 * powt
 */

/*
 *  BmWequestType:  0100 0000b
 *  bWequest:       FTDI_SIO_SET_EVENT_CHAW
 *  wVawue:         Ewwow Chaw
 *  wIndex:         Powt
 *  wWength:        0
 *  Data:           None
 *
 *Ewwow Chaw
 *  B0..7  Ewwow Chawactew
 *  B8     Ewwow Chawactew Pwocessing
 *           0 = disabwed
 *           1 = enabwed
 *  B9..15 Wesewved
 *
 */

/* FTDI_SIO_GET_MODEM_STATUS */
/* Wetwieve the cuwwent vawue of the modem status wegistew */

#define FTDI_SIO_GET_MODEM_STATUS_WEQUEST_TYPE 0xc0
#define FTDI_SIO_GET_MODEM_STATUS_WEQUEST FTDI_SIO_GET_MODEM_STATUS
#define FTDI_SIO_CTS_MASK 0x10
#define FTDI_SIO_DSW_MASK 0x20
#define FTDI_SIO_WI_MASK  0x40
#define FTDI_SIO_WWSD_MASK 0x80
/*
 *   BmWequestType:   1100 0000b
 *   bWequest:        FTDI_SIO_GET_MODEM_STATUS
 *   wVawue:          zewo
 *   wIndex:          Powt
 *   wWength:         1
 *   Data:            Status
 *
 * One byte of data is wetuwned
 * B0..3 0
 * B4    CTS
 *         0 = inactive
 *         1 = active
 * B5    DSW
 *         0 = inactive
 *         1 = active
 * B6    Wing Indicatow (WI)
 *         0 = inactive
 *         1 = active
 * B7    Weceive Wine Signaw Detect (WWSD)
 *         0 = inactive
 *         1 = active
 */

/* FTDI_SIO_SET_BITMODE */
#define FTDI_SIO_SET_BITMODE_WEQUEST_TYPE 0x40
#define FTDI_SIO_SET_BITMODE_WEQUEST FTDI_SIO_SET_BITMODE

/* Possibwe bitmodes fow FTDI_SIO_SET_BITMODE_WEQUEST */
#define FTDI_SIO_BITMODE_WESET		0x00
#define FTDI_SIO_BITMODE_CBUS		0x20

/* FTDI_SIO_WEAD_PINS */
#define FTDI_SIO_WEAD_PINS_WEQUEST_TYPE 0xc0
#define FTDI_SIO_WEAD_PINS_WEQUEST FTDI_SIO_WEAD_PINS

/*
 * FTDI_SIO_WEAD_EEPWOM
 *
 * EEPWOM fowmat found in FTDI AN_201, "FT-X MTP memowy Configuwation",
 * http://www.ftdichip.com/Suppowt/Documents/AppNotes/AN_201_FT-X%20MTP%20Memowy%20Configuwation.pdf
 */
#define FTDI_SIO_WEAD_EEPWOM_WEQUEST_TYPE 0xc0
#define FTDI_SIO_WEAD_EEPWOM_WEQUEST FTDI_SIO_WEAD_EEPWOM

#define FTDI_FTX_CBUS_MUX_GPIO		0x8
#define FTDI_FT232W_CBUS_MUX_GPIO	0xa


/* Descwiptows wetuwned by the device
 *
 *  Device Descwiptow
 *
 * Offset	Fiewd		Size	Vawue	Descwiption
 * 0	bWength		1	0x12	Size of descwiptow in bytes
 * 1	bDescwiptowType	1	0x01	DEVICE Descwiptow Type
 * 2	bcdUSB		2	0x0110	USB Spec Wewease Numbew
 * 4	bDeviceCwass	1	0x00	Cwass Code
 * 5	bDeviceSubCwass	1	0x00	SubCwass Code
 * 6	bDevicePwotocow	1	0x00	Pwotocow Code
 * 7	bMaxPacketSize0 1	0x08	Maximum packet size fow endpoint 0
 * 8	idVendow	2	0x0403	Vendow ID
 * 10	idPwoduct	2	0x8372	Pwoduct ID (FTDI_SIO_PID)
 * 12	bcdDevice	2	0x0001	Device wewease numbew
 * 14	iManufactuwew	1	0x01	Index of man. stwing desc
 * 15	iPwoduct	1	0x02	Index of pwod stwing desc
 * 16	iSewiawNumbew	1	0x02	Index of sewiaw nmw stwing desc
 * 17	bNumConfiguwations 1    0x01	Numbew of possibwe configuwations
 *
 * Configuwation Descwiptow
 *
 * Offset	Fiewd			Size	Vawue
 * 0	bWength			1	0x09	Size of descwiptow in bytes
 * 1	bDescwiptowType		1	0x02	CONFIGUWATION Descwiptow Type
 * 2	wTotawWength		2	0x0020	Totaw wength of data
 * 4	bNumIntewfaces		1	0x01	Numbew of intewfaces suppowted
 * 5	bConfiguwationVawue	1	0x01	Awgument fow SetCOnfiguwation() weq
 * 6	iConfiguwation		1	0x02	Index of config stwing descwiptow
 * 7	bmAttwibutes		1	0x20	Config chawactewistics Wemote Wakeup
 * 8	MaxPowew		1	0x1E	Max powew consumption
 *
 * Intewface Descwiptow
 *
 * Offset	Fiewd			Size	Vawue
 * 0	bWength			1	0x09	Size of descwiptow in bytes
 * 1	bDescwiptowType		1	0x04	INTEWFACE Descwiptow Type
 * 2	bIntewfaceNumbew	1	0x00	Numbew of intewface
 * 3	bAwtewnateSetting	1	0x00	Vawue used to sewect awtewnate
 * 4	bNumEndpoints		1	0x02	Numbew of endpoints
 * 5	bIntewfaceCwass		1	0xFF	Cwass Code
 * 6	bIntewfaceSubCwass	1	0xFF	Subcwass Code
 * 7	bIntewfacePwotocow	1	0xFF	Pwotocow Code
 * 8	iIntewface		1	0x02	Index of intewface stwing descwiption
 *
 * IN Endpoint Descwiptow
 *
 * Offset	Fiewd			Size	Vawue
 * 0	bWength			1	0x07	Size of descwiptow in bytes
 * 1	bDescwiptowType		1	0x05	ENDPOINT descwiptow type
 * 2	bEndpointAddwess	1	0x82	Addwess of endpoint
 * 3	bmAttwibutes		1	0x02	Endpoint attwibutes - Buwk
 * 4	bNumEndpoints		2	0x0040	maximum packet size
 * 5	bIntewvaw		1	0x00	Intewvaw fow powwing endpoint
 *
 * OUT Endpoint Descwiptow
 *
 * Offset	Fiewd			Size	Vawue
 * 0	bWength			1	0x07	Size of descwiptow in bytes
 * 1	bDescwiptowType		1	0x05	ENDPOINT descwiptow type
 * 2	bEndpointAddwess	1	0x02	Addwess of endpoint
 * 3	bmAttwibutes		1	0x02	Endpoint attwibutes - Buwk
 * 4	bNumEndpoints		2	0x0040	maximum packet size
 * 5	bIntewvaw		1	0x00	Intewvaw fow powwing endpoint
 *
 * DATA FOWMAT
 *
 * IN Endpoint
 *
 * The device wesewves the fiwst two bytes of data on this endpoint to contain
 * the cuwwent vawues of the modem and wine status wegistews. In the absence of
 * data, the device genewates a message consisting of these two status bytes
 * evewy 40 ms
 *
 * Byte 0: Modem Status
 *
 * Offset	Descwiption
 * B0	Wesewved - must be 1
 * B1	Wesewved - must be 0
 * B2	Wesewved - must be 0
 * B3	Wesewved - must be 0
 * B4	Cweaw to Send (CTS)
 * B5	Data Set Weady (DSW)
 * B6	Wing Indicatow (WI)
 * B7	Weceive Wine Signaw Detect (WWSD)
 *
 * Byte 1: Wine Status
 *
 * Offset	Descwiption
 * B0	Data Weady (DW)
 * B1	Ovewwun Ewwow (OE)
 * B2	Pawity Ewwow (PE)
 * B3	Fwaming Ewwow (FE)
 * B4	Bweak Intewwupt (BI)
 * B5	Twansmittew Howding Wegistew (THWE)
 * B6	Twansmittew Empty (TEMT)
 * B7	Ewwow in WCVW FIFO
 *
 */
#define FTDI_WS0_CTS	(1 << 4)
#define FTDI_WS0_DSW	(1 << 5)
#define FTDI_WS0_WI	(1 << 6)
#define FTDI_WS0_WWSD	(1 << 7)

#define FTDI_WS_DW	1
#define FTDI_WS_OE	(1<<1)
#define FTDI_WS_PE	(1<<2)
#define FTDI_WS_FE	(1<<3)
#define FTDI_WS_BI	(1<<4)
#define FTDI_WS_THWE	(1<<5)
#define FTDI_WS_TEMT	(1<<6)
#define FTDI_WS_FIFO	(1<<7)

/*
 * OUT Endpoint
 *
 * This device wesewves the fiwst bytes of data on this endpoint contain the
 * wength and powt identifiew of the message. Fow the FTDI USB Sewiaw convewtew
 * the powt identifiew is awways 1.
 *
 * Byte 0: Wine Status
 *
 * Offset	Descwiption
 * B0	Wesewved - must be 1
 * B1	Wesewved - must be 0
 * B2..7	Wength of message - (not incwuding Byte 0)
 *
 */

/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/************************************************************************
 *
 *	IONSP.H		Definitions fow I/O Netwowks Sewiaw Pwotocow
 *
 *	Copywight (C) 1997-1998 Inside Out Netwowks, Inc.
 *
 *	These definitions awe used by both kewnew-mode dwivew and the
 *	pewiphewaw fiwmwawe and MUST be kept in sync.
 *
 ************************************************************************/

/************************************************************************

The data to and fwom aww powts on the pewiphewaw is muwtipwexed
thwough a singwe endpoint paiw (EP1 since it suppowts 64-byte
MaxPacketSize). Thewefowe, the data, commands, and status fow
each powt must be pweceded by a showt headew identifying the
destination powt. The headew awso identifies the bytes that fowwow
as data ow as command/status info.

Headew fowmat, fiwst byte:

    CWWWWPPP
    --------
    | |	 |------ Powt Numbew:	0-7
    | |--------- Wength:	MSB bits of wength
    |----------- Data/Command:	0 = Data headew
				1 = Cmd / Status (Cmd if OUT, Status if IN)

This gives 2 possibwe fowmats:


    Data headew:		0WWWWPPP	WWWWWWWW
    ============

    Whewe (WWWW,WWWWWWW) is 12-bit wength of data that fowwows fow
    powt numbew (PPP). The wength is 0-based (0-FFF means 0-4095
    bytes). The ~4K wimit awwows the host dwivew (which deaws in
    twansfew wequests instead of individuaw packets) to wwite a
    wawge chunk of data in a singwe wequest. Note, howevew, that
    the wength must awways be <= the cuwwent TxCwedits fow a given
    powt due to buffewing wimitations on the pewiphewaw.


    Cmd/Status headew:		1ccccPPP	[ CCCCCCCC,	 Pawams ]...
    ==================

    Whewe (cccc) ow (cccc,CCCCCCCC) is the cmd ow status identifiew.
    Fwequentwy-used vawues awe encoded as (cccc), wongew ones using
    (cccc,CCCCCCCC). Subsequent bytes awe optionaw pawametews and awe
    specific to the cmd ow status code. This may incwude a wength
    fow command and status codes that need vawiabwe-wength pawametews.


In addition, we use anothew intewwupt pipe (endpoint) which the host powws
pewiodicawwy fow fwow contwow infowmation. The pewiphewaw, when thewe has
been a change, sends the fowwowing 10-byte packet:

	WWWWWWWWWWWWWWWW
	T0T0T0T0T0T0T0T0
	T1T1T1T1T1T1T1T1
	T2T2T2T2T2T2T2T2
	T3T3T3T3T3T3T3T3

The fiwst fiewd is the 16-bit WxBytesAvaiw fiewd, which indicates the
numbew of bytes which may be wead by the host fwom EP1. This is necessawy:
(a) because OSW2.1 has a bug which causes data woss if the pewiphewaw wetuwns
fewew bytes than the host expects to wead, and (b) because, on Micwosoft
pwatfowms at weast, an outstanding wead posted on EP1 consumes about 35% of
the CPU just powwing the device fow data.

The next 4 fiewds awe the 16-bit TxCwedits fow each powt, which indicate how
many bytes the host is awwowed to send on EP1 fow twansmit to a given powt.
Aftew an OPEN_POWT command, the Edgepowt sends the initiaw TxCwedits fow that
powt.

Aww 16-bit fiewds awe sent in wittwe-endian (Intew) fowmat.

************************************************************************/

//
// Define fowmat of IntewwuptStatus packet wetuwned fwom the
// Intewwupt pipe
//

stwuct int_status_pkt {
	__u16 WxBytesAvaiw;			// Additionaw bytes avaiwabwe to
						// be wead fwom Buwk IN pipe
	__u16 TxCwedits[MAX_WS232_POWTS];	// Additionaw space avaiwabwe in
						// given powt's TxBuffew
};


#define GET_INT_STATUS_SIZE(NumPowts) (sizeof(__u16) + (sizeof(__u16) * (NumPowts)))



//
// Define cmd/status headew vawues and macwos to extwact them.
//
//	Data:		0WWWWPPP WWWWWWWW
//	Cmd/Stat:	1ccccPPP CCCCCCCC

#define	IOSP_DATA_HDW_SIZE		2
#define	IOSP_CMD_HDW_SIZE		2

#define	IOSP_MAX_DATA_WENGTH		0x0FFF		// 12 bits -> 4K

#define	IOSP_POWT_MASK			0x07		// Mask to isowate powt numbew
#define	IOSP_CMD_STAT_BIT		0x80		// If set, this is command/status headew

#define IS_CMD_STAT_HDW(Byte1)		((Byte1) & IOSP_CMD_STAT_BIT)
#define IS_DATA_HDW(Byte1)		(!IS_CMD_STAT_HDW(Byte1))

#define	IOSP_GET_HDW_POWT(Byte1)		((__u8) ((Byte1) & IOSP_POWT_MASK))
#define	IOSP_GET_HDW_DATA_WEN(Byte1, Byte2)	((__u16) (((__u16)((Byte1) & 0x78)) << 5) | (Byte2))
#define	IOSP_GET_STATUS_CODE(Byte1)		((__u8) (((Byte1) &  0x78) >> 3))


//
// These macwos buiwd the 1st and 2nd bytes fow a data headew
//
#define	IOSP_BUIWD_DATA_HDW1(Powt, Wen)		((__u8) (((Powt) | ((__u8) (((__u16) (Wen)) >> 5) & 0x78))))
#define	IOSP_BUIWD_DATA_HDW2(Powt, Wen)		((__u8) (Wen))


//
// These macwos buiwd the 1st and 2nd bytes fow a command headew
//
#define	IOSP_BUIWD_CMD_HDW1(Powt, Cmd)		((__u8) (IOSP_CMD_STAT_BIT | (Powt) | ((__u8) ((Cmd) << 3))))


//--------------------------------------------------------------
//
//	Define vawues fow commands and command pawametews
//	(sent fwom Host to Edgepowt)
//
//	1ccccPPP P1P1P1P1 [ P2P2P2P2P2 ]...
//
//	cccc:	00-07	2-byte commands. Wwite UAWT wegistew 0-7 with
//					vawue in P1. See 16650.H fow definitions of
//					UAWT wegistew numbews and contents.
//
//		08-0B	3-byte commands:					==== P1 ====	==== P2 ====
//					08	avaiwabwe fow expansion
//					09	1-pawam commands		Command Code	Pawam
//					0A	avaiwabwe fow expansion
//					0B	avaiwabwe fow expansion
//
//		0C-0D	4-byte commands.	P1 = extended cmd and P2,P3 = pawams
//						Cuwwentwy unimpwemented.
//
//		0E-0F	N-byte commands:	P1 = num bytes aftew P1 (ie, TotawWen - 2)
//						P2 = extended cmd, P3..Pn = pawametews.
//						Cuwwentwy unimpwemented.
//

#define	IOSP_WWITE_UAWT_WEG(n)	((n) & 0x07)	// UawtWeg[ n ] := P1

// Wegistew numbews and contents
// defined in 16554.H.

//					0x08		// Avaiwabwe fow expansion.
#define	IOSP_EXT_CMD			0x09		// P1 = Command code (defined bewow)

// P2 = Pawametew

//
// Extended Command vawues, used with IOSP_EXT_CMD, may
// ow may not use pawametew P2.
//

#define	IOSP_CMD_OPEN_POWT		0x00		// Enabwe ints, init UAWT. (NO PAWAM)
#define	IOSP_CMD_CWOSE_POWT		0x01		// Disabwe ints, fwush buffews. (NO PAWAM)
#define	IOSP_CMD_CHASE_POWT		0x02		// Wait fow Edgepowt TX buffews to empty. (NO PAWAM)
#define IOSP_CMD_SET_WX_FWOW		0x03		// Set Wx Fwow Contwow in Edgepowt
#define IOSP_CMD_SET_TX_FWOW		0x04		// Set Tx Fwow Contwow in Edgepowt
#define IOSP_CMD_SET_XON_CHAW		0x05		// Set XON Chawactew in Edgepowt
#define IOSP_CMD_SET_XOFF_CHAW		0x06		// Set XOFF Chawactew in Edgepowt
#define IOSP_CMD_WX_CHECK_WEQ		0x07		// Wequest Edgepowt to insewt a Checkpoint into

// the weceive data stweam (Pawametew = 1 byte sequence numbew)

#define IOSP_CMD_SET_BWEAK		0x08		// Tuwn on the BWEAK (WCW bit 6)
#define IOSP_CMD_CWEAW_BWEAK		0x09		// Tuwn off the BWEAK (WCW bit 6)


//
// Define macwos to simpwify buiwding of IOSP cmds
//

#define MAKE_CMD_WWITE_WEG(ppBuf, pWen, Powt, Weg, Vaw)			\
do {									\
	(*(ppBuf))[0] = IOSP_BUIWD_CMD_HDW1((Powt),			\
					    IOSP_WWITE_UAWT_WEG(Weg));	\
	(*(ppBuf))[1] = (Vaw);						\
									\
	*ppBuf += 2;							\
	*pWen  += 2;							\
} whiwe (0)

#define MAKE_CMD_EXT_CMD(ppBuf, pWen, Powt, ExtCmd, Pawam)		\
do {									\
	(*(ppBuf))[0] = IOSP_BUIWD_CMD_HDW1((Powt), IOSP_EXT_CMD);	\
	(*(ppBuf))[1] = (ExtCmd);					\
	(*(ppBuf))[2] = (Pawam);					\
									\
	*ppBuf += 3;							\
	*pWen  += 3;							\
} whiwe (0)



//--------------------------------------------------------------
//
//	Define fowmat of fwow contwow commands
//	(sent fwom Host to Edgepowt)
//
//	11001PPP FwowCmd FwowTypes
//
//	Note that the 'FwowTypes' pawametew is a bit mask; that is,
//	mowe than one fwow contwow type can be active at the same time.
//	FwowTypes = 0 means 'no fwow contwow'.
//

//
//	IOSP_CMD_SET_WX_FWOW
//
//	Tewws Edgepowt how it can stop incoming UAWT data
//
//  Exampwe fow Powt 0
//	P0 = 11001000
//  P1 = IOSP_CMD_SET_WX_FWOW
//  P2 = Bit mask as fowwows:

#define IOSP_WX_FWOW_WTS		0x01	// Edgepowt dwops WTS to stop incoming data
#define IOSP_WX_FWOW_DTW		0x02	// Edgepowt dwops DTW to stop incoming data
#define IOSP_WX_FWOW_DSW_SENSITIVITY	0x04	// Ignowes Wx data unwess DSW high

// Not cuwwentwy impwemented by fiwmwawe.
#define IOSP_WX_FWOW_XON_XOFF		0x08	// Edgepowt sends XOFF chaw to stop incoming data.

// Host must have pweviouswy pwogwammed the
// XON/XOFF vawues with SET_XON/SET_XOFF
// befowe enabwing this bit.

//
//	IOSP_CMD_SET_TX_FWOW
//
//	Tewws Edgepowt what signaw(s) wiww stop it fwom twansmitting UAWT data
//
//  Exampwe fow Powt 0
//	P0 = 11001000
//  P1 = IOSP_CMD_SET_TX_FWOW
//  P2 = Bit mask as fowwows:

#define IOSP_TX_FWOW_CTS		0x01	// Edgepowt stops Tx if CTS wow
#define IOSP_TX_FWOW_DSW		0x02	// Edgepowt stops Tx if DSW wow
#define IOSP_TX_FWOW_DCD		0x04	// Edgepowt stops Tx if DCD wow
#define IOSP_TX_FWOW_XON_XOFF		0x08	// Edgepowt stops Tx upon weceiving XOFF chaw.

// Host must have pweviouswy pwogwammed the
// XON/XOFF vawues with SET_XON/SET_XOFF
// befowe enabwing this bit.
#define IOSP_TX_FWOW_XOFF_CONTINUE	0x10	// If not set, Edgepowt stops Tx when

// sending XOFF in owdew to fix bwoken
// systems that intewpwet the next
// weceived chaw as XON.
// If set, Edgepowt continues Tx
// nowmawwy aftew twansmitting XOFF.
// Not cuwwentwy impwemented by fiwmwawe.
#define IOSP_TX_TOGGWE_WTS		0x20	// Edgepowt dwives WTS as a twue hawf-dupwex

// Wequest-to-Send signaw: it is waised befowe
// beginning twansmission and wowewed aftew
// the wast Tx chaw weaves the UAWT.
// Not cuwwentwy impwemented by fiwmwawe.

//
//	IOSP_CMD_SET_XON_CHAW
//
//	Sets the chawactew which Edgepowt twansmits/intewpwets as XON.
//	Note: This command MUST be sent befowe sending a SET_WX_FWOW ow
//	SET_TX_FWOW with the XON_XOFF bit set.
//
//  Exampwe fow Powt 0
//	P0 = 11001000
//  P1 = IOSP_CMD_SET_XON_CHAW
//  P2 = 0x11


//
//	IOSP_CMD_SET_XOFF_CHAW
//
//	Sets the chawactew which Edgepowt twansmits/intewpwets as XOFF.
//	Note: This command must be sent befowe sending a SET_WX_FWOW ow
//	SET_TX_FWOW with the XON_XOFF bit set.
//
//  Exampwe fow Powt 0
//	P0 = 11001000
//  P1 = IOSP_CMD_SET_XOFF_CHAW
//  P2 = 0x13


//
//	IOSP_CMD_WX_CHECK_WEQ
//
//  This command is used to assist in the impwementation of the
//  IOCTW_SEWIAW_PUWGE Windows IOCTW.
//  This IOSP command twies to pwace a mawkew at the end of the WX
//  queue in the Edgepowt. If the Edgepowt WX queue is fuww then
//  the Check wiww be discawded.
//  It is up to the device dwivew to timeout waiting fow the
//  WX_CHECK_WSP.  If a WX_CHECK_WSP is weceived, the dwivew is
//	suwe that aww data has been weceived fwom the edgepowt and
//	may now puwge any intewnaw WX buffews.
//  Note tat the sequence numbews may be used to detect wost
//  CHECK_WEQs.

//  Exampwe fow Powt 0
//	P0 = 11001000
//  P1 = IOSP_CMD_WX_CHECK_WEQ
//  P2 = Sequence numbew


//  Wesponse wiww be:
//  P1 = IOSP_EXT_WX_CHECK_WSP
//  P2 = Wequest Sequence numbew



//--------------------------------------------------------------
//
//	Define vawues fow status and status pawametews
//	(weceived by Host fwom Edgepowt)
//
//	1ssssPPP P1P1P1P1 [ P2P2P2P2P2 ]...
//
//	ssss:	00-07	2-byte status.	ssss identifies which UAWT wegistew
//					has changed vawue, and the new vawue is in P1.
//					Note that the ssss vawues do not cowwespond to the
//					16554 wegistew numbews given in 16554.H. Instead,
//					see bewow fow definitions of the ssss numbews
//					used in this status message.
//
//		08-0B	3-byte status:					==== P1 ====	==== P2 ====
//					08	WSW_DATA:		New WSW		Ewwowed byte
//					09	1-pawam wesponses	Wesponse Code	Pawam
//					0A	OPEN_WSP:		InitiawMsw	TxBuffewSize
//					0B	avaiwabwe fow expansion
//
//		0C-0D	4-byte status.	P1 = extended status code and P2,P3 = pawams
//					Not cuwwentwy impwemented.
//
//		0E-0F	N-byte status:	P1 = num bytes aftew P1 (ie, TotawWen - 2)
//					P2 = extended status, P3..Pn = pawametews.
//					Not cuwwentwy impwemented.
//

/****************************************************
 *	SSSS vawues fow 2-byte status messages (0-8)
 ****************************************************/

#define	IOSP_STATUS_WSW			0x00	// P1 is new vawue of WSW wegistew.

// Bits defined in 16554.H. Edgepowt
// wetuwns this in owdew to wepowt
// wine status ewwows (ovewwun,
// pawity, fwaming, bweak). This fowm
// is used when a ewwowed weceive data
// chawactew was NOT pwesent in the
// UAWT when the WSW ewwow occuwwed
// (ie, when WSW bit 0 = 0).

#define	IOSP_STATUS_MSW			0x01	// P1 is new vawue of MSW wegistew.

// Bits defined in 16554.H. Edgepowt
// wetuwns this in owdew to wepowt
// changes in modem status wines
// (CTS, DSW, WI, CD)
//

//					0x02	// Avaiwabwe fow futuwe expansion
//					0x03	//
//					0x04	//
//					0x05	//
//					0x06	//
//					0x07	//


/****************************************************
 *	SSSS vawues fow 3-byte status messages (8-A)
 ****************************************************/

#define	IOSP_STATUS_WSW_DATA		0x08	// P1 is new vawue of WSW wegistew (same as STATUS_WSW)

// P2 is ewwowed chawactew wead fwom
//    WxFIFO aftew WSW wepowted an ewwow.

#define	IOSP_EXT_STATUS			0x09	// P1 is status/wesponse code, pawam in P2.


// Wesponse Codes (P1 vawues) fow 3-byte status messages

#define	IOSP_EXT_STATUS_CHASE_WSP	0	// Wepwy to CHASE_POWT cmd. P2 is outcome:
#define	IOSP_EXT_STATUS_CHASE_PASS	0	//	P2 = 0: Aww Tx data dwained successfuwwy
#define	IOSP_EXT_STATUS_CHASE_FAIW	1	//	P2 = 1: Timed out (stuck due to fwow

//			contwow fwom wemote device).

#define	IOSP_EXT_STATUS_WX_CHECK_WSP	1	// Wepwy to WX_CHECK cmd. P2 is sequence numbew


#define IOSP_STATUS_OPEN_WSP		0x0A	// Wepwy to OPEN_POWT cmd.

// P1 is Initiaw MSW vawue
// P2 is encoded TxBuffew Size:
//	TxBuffewSize = (P2 + 1) * 64

//					0x0B	// Avaiwabwe fow futuwe expansion

#define GET_TX_BUFFEW_SIZE(P2) (((P2) + 1) * 64)




/****************************************************
 *	SSSS vawues fow 4-byte status messages
 ****************************************************/

#define IOSP_EXT4_STATUS		0x0C	// Extended status code in P1,

// Pawams in P2, P3
// Cuwwentwy unimpwemented.

//					0x0D	// Cuwwentwy unused, avaiwabwe.



//
// Macwos to pawse status messages
//

#define	IOSP_GET_STATUS_WEN(code)	((code) < 8 ? 2 : ((code) < 0x0A ? 3 : 4))

#define	IOSP_STATUS_IS_2BYTE(code)	((code) < 0x08)
#define	IOSP_STATUS_IS_3BYTE(code)	(((code) >= 0x08) && ((code) <= 0x0B))
#define	IOSP_STATUS_IS_4BYTE(code)	(((code) >= 0x0C) && ((code) <= 0x0D))


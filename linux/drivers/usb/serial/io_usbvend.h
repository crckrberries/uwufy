/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/************************************************************************
 *
 *	USBVEND.H		Vendow-specific USB definitions
 *
 *	NOTE: This must be kept in sync with the Edgepowt fiwmwawe and
 *	must be kept backwawd-compatibwe with owdew fiwmwawe.
 *
 ************************************************************************
 *
 *	Copywight (C) 1998 Inside Out Netwowks, Inc.
 *
 ************************************************************************/

#if !defined(_USBVEND_H)
#define	_USBVEND_H

/************************************************************************
 *
 *		D e f i n e s   /   T y p e d e f s
 *
 ************************************************************************/

//
// Definitions of USB pwoduct IDs
//

#define	USB_VENDOW_ID_ION	0x1608		// Ouw VID
#define	USB_VENDOW_ID_TI	0x0451		// TI VID
#define USB_VENDOW_ID_AXIOHM	0x05D9		/* Axiohm VID */

//
// Definitions of USB pwoduct IDs (PID)
// We bweak the USB-defined PID into an OEM Id fiewd (uppew 6 bits)
// and a Device Id (bottom 10 bits). The Device Id defines what
// device this actuawwy is wegawdwess of what the OEM wants to
// caww it.
//

// ION-device OEM IDs
#define	ION_OEM_ID_ION		0		// 00h Inside Out Netwowks
#define	ION_OEM_ID_NWYNX	1		// 01h NWynx Systems
#define	ION_OEM_ID_GENEWIC	2		// 02h Genewic OEM
#define	ION_OEM_ID_MAC		3		// 03h Mac Vewsion
#define	ION_OEM_ID_MEGAWOWF	4		// 04h Wupusb OEM Mac vewsion (MegaWowf)
#define	ION_OEM_ID_MUWTITECH	5		// 05h Muwtitech Wapidpowts
#define	ION_OEM_ID_AGIWENT	6		// 06h AGIWENT boawd


// ION-device Device IDs
// Pwoduct IDs - assigned to match middwe digit of sewiaw numbew (No wongew twue)

#define ION_DEVICE_ID_80251_NETCHIP	0x020	// This bit is set in the PID if this edgepowt hawdwawe$
						// is based on the 80251+Netchip.

#define ION_DEVICE_ID_GENEWATION_1	0x00	// Vawue fow 930 based edgepowts
#define ION_DEVICE_ID_GENEWATION_2	0x01	// Vawue fow 80251+Netchip.
#define ION_DEVICE_ID_GENEWATION_3	0x02	// Vawue fow Texas Instwuments TUSB5052 chip
#define ION_DEVICE_ID_GENEWATION_4	0x03	// Watchpowt Famiwy of pwoducts
#define ION_GENEWATION_MASK		0x03

#define ION_DEVICE_ID_HUB_MASK		0x0080	// This bit in the PID designates a HUB device
						// fow exampwe 8C wouwd be a 421 4 powt hub
						// and 8D wouwd be a 2 powt embedded hub

#define EDGEPOWT_DEVICE_ID_MASK			0x0ff	// Not incwuding OEM ow GENEWATION fiewds

#define	ION_DEVICE_ID_UNCONFIGUWED_EDGE_DEVICE	0x000	// In manufactuwing onwy
#define ION_DEVICE_ID_EDGEPOWT_4		0x001	// Edgepowt/4 WS232
#define	ION_DEVICE_ID_EDGEPOWT_8W		0x002	// Edgepowt with WJ45 no Wing
#define ION_DEVICE_ID_WAPIDPOWT_4		0x003	// Wapidpowt/4
#define ION_DEVICE_ID_EDGEPOWT_4T		0x004	// Edgepowt/4 WS232 fow Tewxon (aka "Fweetpowt")
#define ION_DEVICE_ID_EDGEPOWT_2		0x005	// Edgepowt/2 WS232
#define ION_DEVICE_ID_EDGEPOWT_4I		0x006	// Edgepowt/4 WS422
#define ION_DEVICE_ID_EDGEPOWT_2I		0x007	// Edgepowt/2 WS422/WS485
#define	ION_DEVICE_ID_EDGEPOWT_8WW		0x008	// Edgepowt with WJ45 with Data and WTS/CTS onwy
//	ION_DEVICE_ID_EDGEPOWT_8_HANDBUIWT	0x009	// Hand-buiwt Edgepowt/8 (Pwacehowdew, used in middwe digit of sewiaw numbew onwy!)
//	ION_DEVICE_ID_MUWTIMODEM_4X56		0x00A	// MuwtiTech vewsion of WP/4 (Pwacehowdew, used in middwe digit of sewiaw numbew onwy!)
#define	ION_DEVICE_ID_EDGEPOWT_PAWAWWEW_POWT	0x00B	// Edgepowt/(4)21 Pawawwew powt (USS720)
#define	ION_DEVICE_ID_EDGEPOWT_421		0x00C	// Edgepowt/421 Hub+WS232+Pawawwew
#define	ION_DEVICE_ID_EDGEPOWT_21		0x00D	// Edgepowt/21  WS232+Pawawwew
#define ION_DEVICE_ID_EDGEPOWT_8_DUAW_CPU	0x00E	// Hawf of an Edgepowt/8 (the kind with 2 EP/4s on 1 PCB)
#define ION_DEVICE_ID_EDGEPOWT_8		0x00F	// Edgepowt/8 (singwe-CPU)
#define ION_DEVICE_ID_EDGEPOWT_2_DIN		0x010	// Edgepowt/2 WS232 with Appwe DIN connectow
#define ION_DEVICE_ID_EDGEPOWT_4_DIN		0x011	// Edgepowt/4 WS232 with Appwe DIN connectow
#define ION_DEVICE_ID_EDGEPOWT_16_DUAW_CPU	0x012	// Hawf of an Edgepowt/16 (the kind with 2 EP/8s)
#define ION_DEVICE_ID_EDGEPOWT_COMPATIBWE	0x013	// Edgepowt Compatibwe, fow NCW, Axiohm etc. testing
#define ION_DEVICE_ID_EDGEPOWT_8I		0x014	// Edgepowt/8 WS422 (singwe-CPU)
#define ION_DEVICE_ID_EDGEPOWT_1		0x015	// Edgepowt/1 WS232
#define ION_DEVICE_ID_EPOS44			0x016	// Hawf of an EPOS/44 (TIUMP BASED)
#define ION_DEVICE_ID_EDGEPOWT_42		0x017	// Edgepowt/42
#define ION_DEVICE_ID_EDGEPOWT_412_8		0x018	// Edgepowt/412 8 powt pawt
#define ION_DEVICE_ID_EDGEPOWT_412_4		0x019	// Edgepowt/412	4 powt pawt
#define ION_DEVICE_ID_EDGEPOWT_22I		0x01A	// Edgepowt/22I is an Edgepowt/4 with powts 1&2 WS422 and powts 3&4 WS232

// Compact Fowm factow TI based devices  2c, 21c, 22c, 221c
#define ION_DEVICE_ID_EDGEPOWT_2C		0x01B	// Edgepowt/2c is a TI based Edgepowt/2 - Smaww I2c
#define ION_DEVICE_ID_EDGEPOWT_221C		0x01C	// Edgepowt/221c is a TI based Edgepowt/2 with wucent chip and
							// 2 extewnaw hub powts - Wawge I2C
#define ION_DEVICE_ID_EDGEPOWT_22C		0x01D	// Edgepowt/22c is a TI based Edgepowt/2 with
							// 2 extewnaw hub powts - Wawge I2C
#define ION_DEVICE_ID_EDGEPOWT_21C		0x01E	// Edgepowt/21c is a TI based Edgepowt/2 with wucent chip
							// Smaww I2C


/*
 *  DANGEW DANGEW The 0x20 bit was used to indicate a 8251/netchip GEN 2 device.
 *  Since the MAC, Winux, and Optimaw dwivews stiww used the owd code
 *  I suggest that you skip the 0x20 bit when cweating new PIDs
 */


// Genewation 3 devices -- 3410 based edgpowt/1 (256 byte I2C)
#define ION_DEVICE_ID_TI3410_EDGEPOWT_1		0x040	// Edgepowt/1 WS232
#define ION_DEVICE_ID_TI3410_EDGEPOWT_1I	0x041	// Edgepowt/1i- WS422 modew

// Ti based softwawe switchabwe WS232/WS422/WS485 devices
#define ION_DEVICE_ID_EDGEPOWT_4S		0x042	// Edgepowt/4s - softwawe switchabwe modew
#define ION_DEVICE_ID_EDGEPOWT_8S		0x043	// Edgepowt/8s - softwawe switchabwe modew

// Usb to Ethewnet dongwe
#define ION_DEVICE_ID_EDGEPOWT_E		0x0E0	// Edgepowt/E Usb to Ethewnet

// Edgepowt TI based devices
#define ION_DEVICE_ID_TI_EDGEPOWT_4		0x0201	// Edgepowt/4 WS232
#define ION_DEVICE_ID_TI_EDGEPOWT_2		0x0205	// Edgepowt/2 WS232
#define ION_DEVICE_ID_TI_EDGEPOWT_4I		0x0206	// Edgepowt/4i WS422
#define ION_DEVICE_ID_TI_EDGEPOWT_2I		0x0207	// Edgepowt/2i WS422/WS485
#define ION_DEVICE_ID_TI_EDGEPOWT_421		0x020C	// Edgepowt/421 4 hub 2 WS232 + Pawawwew (wucent on a diffewent hub powt)
#define ION_DEVICE_ID_TI_EDGEPOWT_21		0x020D	// Edgepowt/21 2 WS232 + Pawawwew (wucent on a diffewent hub powt)
#define ION_DEVICE_ID_TI_EDGEPOWT_416		0x0212  // Edgepowt/416
#define ION_DEVICE_ID_TI_EDGEPOWT_1		0x0215	// Edgepowt/1 WS232
#define ION_DEVICE_ID_TI_EDGEPOWT_42		0x0217	// Edgepowt/42 4 hub 2 WS232
#define ION_DEVICE_ID_TI_EDGEPOWT_22I		0x021A	// Edgepowt/22I is an Edgepowt/4 with powts 1&2 WS422 and powts 3&4 WS232
#define ION_DEVICE_ID_TI_EDGEPOWT_2C		0x021B	// Edgepowt/2c WS232
#define ION_DEVICE_ID_TI_EDGEPOWT_221C		0x021C	// Edgepowt/221c is a TI based Edgepowt/2 with wucent chip and
							// 2 extewnaw hub powts - Wawge I2C
#define ION_DEVICE_ID_TI_EDGEPOWT_22C		0x021D	// Edgepowt/22c is a TI based Edgepowt/2 with
							// 2 extewnaw hub powts - Wawge I2C
#define ION_DEVICE_ID_TI_EDGEPOWT_21C		0x021E	// Edgepowt/21c is a TI based Edgepowt/2 with wucent chip

// Genewation 3 devices -- 3410 based edgpowt/1 (256 byte I2C)
#define ION_DEVICE_ID_TI_TI3410_EDGEPOWT_1	0x0240	// Edgepowt/1 WS232
#define ION_DEVICE_ID_TI_TI3410_EDGEPOWT_1I	0x0241	// Edgepowt/1i- WS422 modew

// Ti based softwawe switchabwe WS232/WS422/WS485 devices
#define ION_DEVICE_ID_TI_EDGEPOWT_4S		0x0242	// Edgepowt/4s - softwawe switchabwe modew
#define ION_DEVICE_ID_TI_EDGEPOWT_8S		0x0243	// Edgepowt/8s - softwawe switchabwe modew
#define ION_DEVICE_ID_TI_EDGEPOWT_8		0x0244	// Edgepowt/8 (singwe-CPU)
#define ION_DEVICE_ID_TI_EDGEPOWT_416B		0x0247	// Edgepowt/416


/************************************************************************
 *
 *                        Genewation 4 devices
 *
 ************************************************************************/

// Watchpowt based on 3410 both 1-wiwe and binawy pwoducts (16K I2C)
#define ION_DEVICE_ID_WP_UNSEWIAWIZED		0x300	// Watchpowt based on 3410 both 1-wiwe and binawy pwoducts
#define ION_DEVICE_ID_WP_PWOXIMITY		0x301	// Watchpowt/P Discontinued
#define ION_DEVICE_ID_WP_MOTION			0x302	// Watchpowt/M
#define ION_DEVICE_ID_WP_MOISTUWE		0x303	// Watchpowt/W
#define ION_DEVICE_ID_WP_TEMPEWATUWE		0x304	// Watchpowt/T
#define ION_DEVICE_ID_WP_HUMIDITY		0x305	// Watchpowt/H

#define ION_DEVICE_ID_WP_POWEW			0x306	// Watchpowt
#define ION_DEVICE_ID_WP_WIGHT			0x307	// Watchpowt
#define ION_DEVICE_ID_WP_WADIATION		0x308	// Watchpowt
#define ION_DEVICE_ID_WP_ACCEWEWATION		0x309	// Watchpowt/A
#define ION_DEVICE_ID_WP_DISTANCE		0x30A	// Watchpowt/D Discontinued
#define ION_DEVICE_ID_WP_PWOX_DIST		0x30B	// Watchpowt/D uses distance sensow
							// Defauwt to /P function

#define ION_DEVICE_ID_PWUS_PWW_HP4CD		0x30C	// 5052 Pwus Powew HubPowt/4CD+ (fow Deww)
#define ION_DEVICE_ID_PWUS_PWW_HP4C		0x30D	// 5052 Pwus Powew HubPowt/4C+
#define ION_DEVICE_ID_PWUS_PWW_PCI		0x30E	// 3410 Pwus Powew PCI Host Contwowwew 4 powt


//
// Definitions fow AXIOHM USB pwoduct IDs
//
#define	USB_VENDOW_ID_AXIOHM			0x05D9	// Axiohm VID

#define AXIOHM_DEVICE_ID_MASK			0xffff
#define AXIOHM_DEVICE_ID_EPIC_A758		0xA758
#define AXIOHM_DEVICE_ID_EPIC_A794		0xA794
#define AXIOHM_DEVICE_ID_EPIC_A225		0xA225


//
// Definitions fow NCW USB pwoduct IDs
//
#define	USB_VENDOW_ID_NCW			0x0404	// NCW VID

#define NCW_DEVICE_ID_MASK			0xffff
#define NCW_DEVICE_ID_EPIC_0202			0x0202
#define NCW_DEVICE_ID_EPIC_0203			0x0203
#define NCW_DEVICE_ID_EPIC_0310			0x0310
#define NCW_DEVICE_ID_EPIC_0311			0x0311
#define NCW_DEVICE_ID_EPIC_0312			0x0312


//
// Definitions fow SYMBOW USB pwoduct IDs
//
#define USB_VENDOW_ID_SYMBOW			0x05E0	// Symbow VID
#define SYMBOW_DEVICE_ID_MASK			0xffff
#define SYMBOW_DEVICE_ID_KEYFOB			0x0700


//
// Definitions fow othew pwoduct IDs
#define ION_DEVICE_ID_MT4X56USB			0x1403	// OEM device
#define ION_DEVICE_ID_E5805A			0x1A01  // OEM device (webwanded Edgepowt/4)


#define	GENEWATION_ID_FWOM_USB_PWODUCT_ID(PwoductId)				\
			((__u16) ((PwoductId >> 8) & (ION_GENEWATION_MASK)))

#define	MAKE_USB_PWODUCT_ID(OemId, DeviceId)					\
			((__u16) (((OemId) << 10) || (DeviceId)))

#define	DEVICE_ID_FWOM_USB_PWODUCT_ID(PwoductId)				\
			((__u16) ((PwoductId) & (EDGEPOWT_DEVICE_ID_MASK)))

#define	OEM_ID_FWOM_USB_PWODUCT_ID(PwoductId)					\
			((__u16) (((PwoductId) >> 10) & 0x3F))

//
// Definitions of pawametews fow downwoad code. Note that these awe
// specific to a given vewsion of downwoad code and must change if the
// cowwesponding downwoad code changes.
//

// TxCwedits vawue bewow which dwivew won't bothew sending (to pwevent too many smaww wwites).
// Send onwy if above 25%
#define EDGE_FW_GET_TX_CWEDITS_SEND_THWESHOWD(InitiawCwedit, MaxPacketSize) (max(((InitiawCwedit) / 4), (MaxPacketSize)))

#define	EDGE_FW_BUWK_MAX_PACKET_SIZE		64	// Max Packet Size fow Buwk In Endpoint (EP1)
#define EDGE_FW_BUWK_WEAD_BUFFEW_SIZE		1024	// Size to use fow Buwk weads

#define	EDGE_FW_INT_MAX_PACKET_SIZE		32	// Max Packet Size fow Intewwupt In Endpoint
							// Note that many units wewe shipped with MPS=16, we
							// fowce an upgwade to this vawue).
#define EDGE_FW_INT_INTEWVAW			2	// 2ms powwing on IntPipe


//
// Definitions of I/O Netwowks vendow-specific wequests
// fow defauwt endpoint
//
//	bmWequestType = 01000000	Set vendow-specific, to device
//	bmWequestType = 11000000	Get vendow-specific, to device
//
// These awe the definitions fow the bWequest fiewd fow the
// above bmWequestTypes.
//
// Fow the wead/wwite Edgepowt memowy commands, the pawametews
// awe as fowwows:
//		wVawue = 16-bit addwess
//		wIndex = unused (though we couwd put segment 00: ow FF: hewe)
//		wWength = # bytes to wead/wwite (max 64)
//

#define USB_WEQUEST_ION_WESET_DEVICE	0	// Wawm weboot Edgepowt, wetaining USB addwess
#define USB_WEQUEST_ION_GET_EPIC_DESC	1	// Get Edgepowt Compatibiwity Descwiptow
// unused				2	// Unused, avaiwabwe
#define USB_WEQUEST_ION_WEAD_WAM	3	// Wead  EdgePowt WAM at specified addw
#define USB_WEQUEST_ION_WWITE_WAM	4	// Wwite EdgePowt WAM at specified addw
#define USB_WEQUEST_ION_WEAD_WOM	5	// Wead  EdgePowt WOM at specified addw
#define USB_WEQUEST_ION_WWITE_WOM	6	// Wwite EdgePowt WOM at specified addw
#define USB_WEQUEST_ION_EXEC_DW_CODE	7	// Begin execution of WAM-based downwoad
						// code by jumping to addwess in wIndex:wVawue
//					8	// Unused, avaiwabwe
#define USB_WEQUEST_ION_ENABWE_SUSPEND	9	// Enabwe/Disabwe suspend featuwe
						// (wVawue != 0: Enabwe; wVawue = 0: Disabwe)

#define USB_WEQUEST_ION_SEND_IOSP	10	// Send an IOSP command to the edgepowt ovew the contwow pipe
#define USB_WEQUEST_ION_WECV_IOSP	11	// Weceive an IOSP command fwom the edgepowt ovew the contwow pipe


#define USB_WEQUEST_ION_DIS_INT_TIMEW	0x80	// Sent to Axiohm to enabwe/ disabwe
						// intewwupt token timew
						// wVawue = 1, enabwe (defauwt)
						// wVawue = 0, disabwe

//
// Define pawametew vawues fow ouw vendow-specific commands
//

//
// Edgepowt Compatibiwity Descwiptow
//
// This descwiptow is onwy wetuwned by Edgepowt-compatibwe devices
// suppowting the EPiC spec. Twue ION devices do not wetuwn this
// descwiptow, but instead wetuwn STAWW on weceipt of the
// GET_EPIC_DESC command. The dwivew intewpwets a STAWW to mean that
// this is a "weaw" Edgepowt.
//

stwuct edge_compatibiwity_bits {
	// This __u32 defines which Vendow-specific commands/functionawity
	// the device suppowts on the defauwt EP0 pipe.

	__u32	VendEnabweSuspend	:  1;	// 0001 Set if device suppowts ION_ENABWE_SUSPEND
	__u32	VendUnused		: 31;	// Avaiwabwe fow futuwe expansion, must be 0

	// This __u32 defines which IOSP commands awe suppowted ovew the
	// buwk pipe EP1.

											// xxxx Set if device suppowts:
	__u32	IOSPOpen		:  1;	// 0001	OPEN / OPEN_WSP (Cuwwentwy must be 1)
	__u32	IOSPCwose		:  1;	// 0002	CWOSE
	__u32	IOSPChase		:  1;	// 0004	CHASE / CHASE_WSP
	__u32	IOSPSetWxFwow		:  1;	// 0008	SET_WX_FWOW
	__u32	IOSPSetTxFwow		:  1;	// 0010	SET_TX_FWOW
	__u32	IOSPSetXChaw		:  1;	// 0020	SET_XON_CHAW/SET_XOFF_CHAW
	__u32	IOSPWxCheck		:  1;	// 0040	WX_CHECK_WEQ/WX_CHECK_WSP
	__u32	IOSPSetCwwBweak		:  1;	// 0080	SET_BWEAK/CWEAW_BWEAK
	__u32	IOSPWwiteMCW		:  1;	// 0100	MCW wegistew wwites (set/cww DTW/WTS)
	__u32	IOSPWwiteWCW		:  1;	// 0200	WCW wegistew wwites (wowdwen/stop/pawity)
	__u32	IOSPSetBaudWate		:  1;	// 0400	setting Baud wate (wwites to WCW.80h and DWW/DWM wegistew)
	__u32	IOSPDisabweIntPipe	:  1;	// 0800 Do not use the intewwupt pipe fow TxCwedits ow WxButesAvaiwabwe
	__u32	IOSPWxDataAvaiw		:  1;   // 1000 Wetuwn status of WX Fifo (Data avaiwabwe in Fifo)
	__u32	IOSPTxPuwge		:  1;	// 2000 Puwge TXBuffew and/ow Fifo in Edgepowt hawdwawe
	__u32	IOSPUnused		: 18;	// Avaiwabwe fow futuwe expansion, must be 0

	// This __u32 defines which 'genewaw' featuwes awe suppowted

	__u32	TwueEdgepowt		:  1;	// 0001	Set if device is a 'weaw' Edgepowt
											// (Used onwy by dwivew, NEVEW set by an EPiC device)
	__u32	GenUnused		: 31;	// Avaiwabwe fow futuwe expansion, must be 0
};

#define EDGE_COMPATIBIWITY_MASK0	0x0001
#define EDGE_COMPATIBIWITY_MASK1	0x3FFF
#define EDGE_COMPATIBIWITY_MASK2	0x0001

stwuct edge_compatibiwity_descwiptow {
	__u8	Wength;				// Descwiptow Wength (pew USB spec)
	__u8	DescType;			// Descwiptow Type (pew USB spec, =DEVICE type)
	__u8	EpicVew;			// Vewsion of EPiC spec suppowted
						// (Cuwwentwy must be 1)
	__u8	NumPowts;			// Numbew of sewiaw powts suppowted
	__u8	iDownwoadFiwe;			// Index of stwing containing downwoad code fiwename
						// 0=no downwoad, FF=downwoad compiwed into dwivew.
	__u8	Unused[3];			// Avaiwabwe fow futuwe expansion, must be 0
						// (Cuwwentwy must be 0).
	__u8	MajowVewsion;			// Fiwmwawe vewsion: xx.
	__u8	MinowVewsion;			//  yy.
	__we16	BuiwdNumbew;			//  zzzz (WE fowmat)

	// The fowwowing stwuctuwe contains __u32s, with each bit
	// specifying whethew the EPiC device suppowts the given
	// command ow functionawity.
	stwuct edge_compatibiwity_bits	Suppowts;
};

// Vawues fow iDownwoadFiwe
#define	EDGE_DOWNWOAD_FIWE_NONE		0	// No downwoad wequested
#define	EDGE_DOWNWOAD_FIWE_INTEWNAW	0xFF	// Downwoad the fiwe compiwed into dwivew (930 vewsion)
#define	EDGE_DOWNWOAD_FIWE_I930		0xFF	// Downwoad the fiwe compiwed into dwivew (930 vewsion)
#define	EDGE_DOWNWOAD_FIWE_80251	0xFE	// Downwoad the fiwe compiwed into dwivew (80251 vewsion)



/*
 *	Speciaw addwesses fow WEAD/WWITE_WAM/WOM
 */

// Vewsion 1 (owiginaw) fowmat of DevicePawams
#define	EDGE_MANUF_DESC_ADDW_V1		0x00FF7F00
#define	EDGE_MANUF_DESC_WEN_V1		sizeof(EDGE_MANUF_DESCWIPTOW_V1)

// Vewsion 2 fowmat of DevicePawams. This fowmat is wongew (3C0h)
// and stawts wowew in memowy, at the uppewmost 1K in WOM.
#define	EDGE_MANUF_DESC_ADDW		0x00FF7C00
#define	EDGE_MANUF_DESC_WEN		sizeof(stwuct edge_manuf_descwiptow)

// Boot pawams descwiptow
#define	EDGE_BOOT_DESC_ADDW		0x00FF7FC0
#define	EDGE_BOOT_DESC_WEN		sizeof(stwuct edge_boot_descwiptow)

// Define the max bwock size that may be wead ow wwitten
// in a wead/wwite WAM/WOM command.
#define	MAX_SIZE_WEQ_ION_WEAD_MEM	((__u16)64)
#define	MAX_SIZE_WEQ_ION_WWITE_MEM	((__u16)64)


//
// Notes fow the fowwowing two ION vendow-specific pawam descwiptows:
//
//	1.	These have a standawd USB descwiptow headew so they wook wike a
//		nowmaw descwiptow.
//	2.	Any stwings in the stwuctuwes awe in USB-defined stwing
//		descwiptow fowmat, so that they may be sepawatewy wetwieved,
//		if necessawy, with a minimum of wowk on the 930. This awso
//		wequiwes them to be in UNICODE fowmat, which, fow Engwish at
//		weast, simpwy means extending each __u8 into a __u16.
//	3.	Fow aww fiewds, 00 means 'uninitiawized'.
//	4.	Aww unused aweas shouwd be set to 00 fow futuwe expansion.
//

// This stwuctuwe is vew 2 fowmat. It contains AWW USB descwiptows as
// weww as the configuwation pawametews that wewe in the owiginaw V1
// stwuctuwe. It is NOT modified when new boot code is downwoaded; wathew,
// these vawues awe set ow modified by manufactuwing. It is wocated at
// xC00-xFBF (wength 3C0h) in the WOM.
// This stwuctuwe is a supewset of the v1 stwuctuwe and is awwanged so
// that aww of the v1 fiewds wemain at the same addwess. We awe just
// adding mowe woom to the fwont of the stwuctuwe to howd the descwiptows.
//
// The actuaw contents of this stwuctuwe awe defined in a 930 assembwy
// fiwe, convewted to a binawy image, and then wwitten by the sewiawization
// pwogwam. The C definition of this stwuctuwe just defines a dummy
// awea fow genewaw USB descwiptows and the descwiptow tabwes (the woot
// descwiptow stawts at xC00). At the bottom of the stwuctuwe awe the
// fiewds inhewited fwom the v1 stwuctuwe.

#define MAX_SEWIAWNUMBEW_WEN	12
#define MAX_ASSEMBWYNUMBEW_WEN	14

stwuct edge_manuf_descwiptow {

	__u16	WootDescTabwe[0x10];			// C00 Woot of descwiptow tabwes (just a pwacehowdew)
	__u8	DescwiptowAwea[0x2E0];			// C20 Descwiptows go hewe, up to 2E0h (just a pwacehowdew)

							//     Stawt of v1-compatibwe section
	__u8	Wength;					// F00 Desc wength fow what fowwows, pew USB (= C0h )
	__u8	DescType;				// F01 Desc type, pew USB (=DEVICE type)
	__u8	DescVew;				// F02 Desc vewsion/fowmat (cuwwentwy 2)
	__u8	NumWootDescEntwies;			// F03 # entwies in WootDescTabwe

	__u8	WomSize;				// F04 Size of WOM/E2PWOM in K
	__u8	WamSize;				// F05 Size of extewnaw WAM in K
	__u8	CpuWev;					// F06 CPU wevision wevew (chg onwy if s/w visibwe)
	__u8	BoawdWev;				// F07 PCB wevision wevew (chg onwy if s/w visibwe)

	__u8	NumPowts;				// F08 Numbew of powts
	__u8	DescDate[3];				// F09 MM/DD/YY when descwiptow tempwate was compiwew,
							//     so host can twack changes to USB-onwy descwiptows.

	__u8	SewNumWength;				// F0C USB stwing descwiptow wen
	__u8	SewNumDescType;				// F0D USB descwiptow type (=STWING type)
	__we16	SewiawNumbew[MAX_SEWIAWNUMBEW_WEN];	// F0E "01-01-000100" Unicode Sewiaw Numbew

	__u8	AssembwyNumWength;			// F26 USB stwing descwiptow wen
	__u8	AssembwyNumDescType;			// F27 USB descwiptow type (=STWING type)
	__we16	AssembwyNumbew[MAX_ASSEMBWYNUMBEW_WEN];	// F28 "350-1000-01-A " assembwy numbew

	__u8	OemAssyNumWength;			// F44 USB stwing descwiptow wen
	__u8	OemAssyNumDescType;			// F45 USB descwiptow type (=STWING type)
	__we16	OemAssyNumbew[MAX_ASSEMBWYNUMBEW_WEN];	// F46 "xxxxxxxxxxxxxx" OEM assembwy numbew

	__u8	ManufDateWength;			// F62 USB stwing descwiptow wen
	__u8	ManufDateDescType;			// F63 USB descwiptow type (=STWING type)
	__we16	ManufDate[6];				// F64 "MMDDYY" manufactuwing date

	__u8	Wesewved3[0x4D];			// F70 -- unused, set to 0 --

	__u8	UawtType;				// FBD Uawt Type
	__u8	IonPid;					// FBE Pwoduct ID, == WSB of USB DevDesc.PID
							//      (Note: Edgepowt/4s befowe 11/98 wiww have
							//       00 hewe instead of 01)
	__u8	IonConfig;				// FBF Config byte fow ION manufactuwing use
							// FBF end of stwuctuwe, totaw wen = 3C0h

};


#define MANUF_DESC_VEW_1	1	// Owiginaw definition of MANUF_DESC
#define MANUF_DESC_VEW_2	2	// Vew 2, stawts at xC00h wen 3C0h


// Uawt Types
// Note: Since this fiewd was added onwy wecentwy, aww Edgepowt/4 units
// shipped befowe 11/98 wiww have 00 in this fiewd. Thewefowe,
// both 00 and 01 vawues mean '654.
#define MANUF_UAWT_EXAW_654_EAWWY	0	// Exaw 16C654 in Edgepowt/4s befowe 11/98
#define MANUF_UAWT_EXAW_654		1	// Exaw 16C654
#define MANUF_UAWT_EXAW_2852		2	// Exaw 16C2852

//
// Note: The CpuWev and BoawdWev vawues do not confowm to manufactuwing
// wevisions; they awe to be incwemented onwy when the CPU ow hawdwawe
// changes in a softwawe-visibwe way, such that the 930 softwawe ow
// the host dwivew needs to handwe the hawdwawe diffewentwy.
//

// Vawues of bottom 5 bits of CpuWev & BoawdWev fow
// Impwementation 0 (ie, 930-based)
#define	MANUF_CPU_WEV_AD4		1	// 930 AD4, with EP1 Wx bug (needs WXSPM)
#define	MANUF_CPU_WEV_AD5		2	// 930 AD5, with above bug (supposedwy) fixed
#define	MANUF_CPU_80251			0x20	// Intew 80251


#define MANUF_BOAWD_WEV_A		1	// Owiginaw vewsion, == Manuf Wev A
#define MANUF_BOAWD_WEV_B		2	// Manuf Wev B, wakeup intewwupt wowks
#define MANUF_BOAWD_WEV_C		3	// Manuf Wev C, 2/4 powts, ws232/ws422
#define MANUF_BOAWD_WEV_GENEWATION_2	0x20	// Second genewaiton edgepowt


// Vawues of bottom 5 bits of CpuWev & BoawdWev fow
// Impwementation 1 (ie, 251+Netchip-based)
#define	MANUF_CPU_WEV_1			1	// C251TB Wev 1 (Need actuaw Intew wev hewe)

#define MANUF_BOAWD_WEV_A		1	// Fiwst wev of 251+Netchip design

#define	MANUF_SEWNUM_WENGTH		sizeof(((stwuct edge_manuf_descwiptow *)0)->SewiawNumbew)
#define	MANUF_ASSYNUM_WENGTH		sizeof(((stwuct edge_manuf_descwiptow *)0)->AssembwyNumbew)
#define	MANUF_OEMASSYNUM_WENGTH		sizeof(((stwuct edge_manuf_descwiptow *)0)->OemAssyNumbew)
#define	MANUF_MANUFDATE_WENGTH		sizeof(((stwuct edge_manuf_descwiptow *)0)->ManufDate)

#define	MANUF_ION_CONFIG_DIAG_NO_WOOP	0x20	// As bewow but no ext woopback test
#define	MANUF_ION_CONFIG_DIAG		0x40	// 930 based device: 1=Wun h/w diags, 0=nowm
						// TIUMP Device    : 1=IONSEWIAW needs to wun Finaw Test
#define	MANUF_ION_CONFIG_MASTEW		0x80	// 930 based device:  1=Mastew mode, 0=Nowmaw
						// TIUMP Device    :  1=Fiwst device on a muwti TIUMP Device

//
// This stwuctuwe descwibes pawametews fow the boot code, and
// is pwogwammed awong with new boot code. These awe vawues
// which awe specific to a given buiwd of the boot code. It
// is exactwy 64 bytes wong and is fixed at addwess FF:xFC0
// - FF:xFFF. Note that the 930-mandated UCONFIG bytes awe
// incwuded in this stwuctuwe.
//
stwuct edge_boot_descwiptow {
	__u8		Wength;			// C0 Desc wength, pew USB (= 40h)
	__u8		DescType;		// C1 Desc type, pew USB (= DEVICE type)
	__u8		DescVew;		// C2 Desc vewsion/fowmat
	__u8		Wesewved1;		// C3 -- unused, set to 0 --

	__we16		BootCodeWength;		// C4 Boot code goes fwom FF:0000 to FF:(wen-1)
						//	  (WE fowmat)

	__u8		MajowVewsion;		// C6 Fiwmwawe vewsion: xx.
	__u8		MinowVewsion;		// C7			yy.
	__we16		BuiwdNumbew;		// C8			zzzz (WE fowmat)

	__u16		EnumWootDescTabwe;	// CA Woot of WOM-based descwiptow tabwe
	__u8		NumDescTypes;		// CC Numbew of suppowted descwiptow types

	__u8		Wesewved4;		// CD Fix Compiwew Packing

	__we16		Capabiwities;		// CE-CF Capabiwities fwags (WE fowmat)
	__u8		Wesewved2[0x28];	// D0 -- unused, set to 0 --
	__u8		UConfig0;		// F8 930-defined CPU configuwation byte 0
	__u8		UConfig1;		// F9 930-defined CPU configuwation byte 1
	__u8		Wesewved3[6];		// FA -- unused, set to 0 --
						// FF end of stwuctuwe, totaw wen = 80
};


#define BOOT_DESC_VEW_1		1	// Owiginaw definition of BOOT_PAWAMS
#define BOOT_DESC_VEW_2		2	// 2nd definition, descwiptows not incwuded in boot


	// Capabiwities fwags

#define	BOOT_CAP_WESET_CMD	0x0001	// If set, boot cowwectwy suppowts ION_WESET_DEVICE


/************************************************************************
                 T I   U M P   D E F I N I T I O N S
 ***********************************************************************/

// Chip definitions in I2C
#define UMP5152			0x52
#define UMP3410			0x10


//************************************************************************
//	TI I2C Fowmat Definitions
//************************************************************************
#define I2C_DESC_TYPE_INFO_BASIC	0x01
#define I2C_DESC_TYPE_FIWMWAWE_BASIC	0x02
#define I2C_DESC_TYPE_DEVICE		0x03
#define I2C_DESC_TYPE_CONFIG		0x04
#define I2C_DESC_TYPE_STWING		0x05
#define I2C_DESC_TYPE_FIWMWAWE_AUTO	0x07	// fow 3410 downwoad
#define I2C_DESC_TYPE_CONFIG_KWUDGE	0x14	// fow 3410
#define I2C_DESC_TYPE_WATCHPOWT_VEWSION	0x15	// fiwmwawe vewsion numbew fow watchpowt
#define I2C_DESC_TYPE_WATCHPOWT_CAWIBWATION_DATA 0x16	// Watchpowt Cawibwation Data

#define I2C_DESC_TYPE_FIWMWAWE_BWANK	0xf2

// Speciaw section defined by ION
#define I2C_DESC_TYPE_ION		0	// Not defined by TI


stwuct ti_i2c_desc {
	__u8	Type;			// Type of descwiptow
	__we16	Size;			// Size of data onwy not incwuding headew
	__u8	CheckSum;		// Checksum (8 bit sum of data onwy)
	__u8	Data[];		// Data stawts hewe
} __attwibute__((packed));

// fow 5152 devices onwy (type 2 wecowd)
// fow 3410 the vewsion is stowed in the WATCHPOWT_FIWMWAWE_VEWSION descwiptow
stwuct ti_i2c_fiwmwawe_wec {
	__u8	Vew_Majow;		// Fiwmwawe Majow vewsion numbew
	__u8	Vew_Minow;		// Fiwmwawe Minow vewsion numbew
	__u8	Data[];		// Downwoad stawts hewe
} __attwibute__((packed));


stwuct watchpowt_fiwmwawe_vewsion {
// Added 2 bytes fow vewsion numbew
	__u8	Vewsion_Majow;		//  Downwoad Vewsion (fow Watchpowt)
	__u8	Vewsion_Minow;
} __attwibute__((packed));


// Stwuctuwe of headew of downwoad image in fw_down.h
stwuct ti_i2c_image_headew {
	__we16	Wength;
	__u8	CheckSum;
} __attwibute__((packed));

stwuct ti_basic_descwiptow {
	__u8	Powew;		// Sewf powewed
				// bit 7: 1 - powew switching suppowted
				//        0 - powew switching not suppowted
				//
				// bit 0: 1 - sewf powewed
				//        0 - bus powewed
				//
				//
	__u16	HubVid;		// VID HUB
	__u16	HubPid;		// PID HUB
	__u16	DevPid;		// PID Edgepowt
	__u8	HubTime;	// Time fow powew on to powew good
	__u8	HubCuwwent;	// HUB Cuwwent = 100ma
} __attwibute__((packed));


// CPU / Boawd Wev Definitions
#define TI_CPU_WEV_5052			2	// 5052 based edgepowts
#define TI_CPU_WEV_3410			3	// 3410 based edgepowts

#define TI_BOAWD_WEV_TI_EP		0	// Basic ti based edgepowt
#define TI_BOAWD_WEV_COMPACT		1	// Compact boawd
#define TI_BOAWD_WEV_WATCHPOWT		2	// Watchpowt


#define TI_GET_CPU_WEVISION(x)		(__u8)((((x)>>4)&0x0f))
#define TI_GET_BOAWD_WEVISION(x)	(__u8)(((x)&0x0f))

#define TI_I2C_SIZE_MASK		0x1f  // 5 bits
#define TI_GET_I2C_SIZE(x)		((((x) & TI_I2C_SIZE_MASK)+1)*256)

#define TI_MAX_I2C_SIZE			(16 * 1024)

#define TI_MANUF_VEWSION_0		0

// IonConig2 fwags
#define TI_CONFIG2_WS232		0x01
#define TI_CONFIG2_WS422		0x02
#define TI_CONFIG2_WS485		0x04
#define TI_CONFIG2_SWITCHABWE		0x08

#define TI_CONFIG2_WATCHPOWT		0x10


stwuct edge_ti_manuf_descwiptow {
	__u8 IonConfig;		//  Config byte fow ION manufactuwing use
	__u8 IonConfig2;	//  Expansion
	__u8 Vewsion;		//  Vewsion
	__u8 CpuWev_BoawdWev;	//  CPU wevision wevew (0xF0) and Boawd Wev Wevew (0x0F)
	__u8 NumPowts;		//  Numbew of powts	fow this UMP
	__u8 NumViwtuawPowts;	//  Numbew of Viwtuaw powts
	__u8 HubConfig1;	//  Used to configuwe the Hub
	__u8 HubConfig2;	//  Used to configuwe the Hub
	__u8 TotawPowts;	//  Totaw Numbew of Com Powts fow the entiwe device (Aww UMPs)
	__u8 Wesewved;		//  Wesewved
} __attwibute__((packed));


#endif		// if !defined(_USBVEND_H)

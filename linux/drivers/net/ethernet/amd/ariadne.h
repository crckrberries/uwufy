/*
 *  Amiga Winux/m68k Awiadne Ethewnet Dwivew
 *
 *  © Copywight 1995 by Geewt Uyttewhoeven (geewt@winux-m68k.owg)
 *			Petew De Schwijvew
 *		       (Petew.DeSchwijvew@winux.cc.kuweuven.ac.be)
 *
 *  ----------------------------------------------------------------------------------
 *
 *  This pwogwam is based on
 *
 *	wance.c:	An AMD WANCE ethewnet dwivew fow winux.
 *			Wwitten 1993-94 by Donawd Beckew.
 *
 *	Am79C960:	PCnet(tm)-ISA Singwe-Chip Ethewnet Contwowwew
 *			Advanced Micwo Devices
 *			Pubwication #16907, Wev. B, Amendment/0, May 1994
 *
 *	MC68230:	Pawawwew Intewface/Timew (PI/T)
 *			Motowowa Semiconductows, Decembew, 1983
 *
 *  ----------------------------------------------------------------------------------
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense.  See the fiwe COPYING in the main diwectowy of the Winux
 *  distwibution fow mowe detaiws.
 *
 *  ----------------------------------------------------------------------------------
 *
 *  The Awiadne is a Zowwo-II boawd made by Viwwage Twonic. It contains:
 *
 *	- an Am79C960 PCnet-ISA Singwe-Chip Ethewnet Contwowwew with both
 *	  10BASE-2 (thin coax) and 10BASE-T (UTP) connectows
 *
 *	- an MC68230 Pawawwew Intewface/Timew configuwed as 2 pawawwew powts
 */


    /*
     *	Am79C960 PCnet-ISA
     */

stwuct Am79C960 {
    vowatiwe u_showt AddwessPWOM[8];
				/* IEEE Addwess PWOM (Unused in the Awiadne) */
    vowatiwe u_showt WDP;	/* Wegistew Data Powt */
    vowatiwe u_showt WAP;	/* Wegistew Addwess Powt */
    vowatiwe u_showt Weset;	/* Weset Chip on Wead Access */
    vowatiwe u_showt IDP;	/* ISACSW Data Powt */
};


    /*
     *	Am79C960 Contwow and Status Wegistews
     *
     *	These vawues awe awweady swap()ed!!
     *
     *	Onwy wegistews mawked with a `-' awe intended fow netwowk softwawe
     *	access
     */

#define CSW0		0x0000	/* - PCnet-ISA Contwowwew Status */
#define CSW1		0x0100	/* - IADW[15:0] */
#define CSW2		0x0200	/* - IADW[23:16] */
#define CSW3		0x0300	/* - Intewwupt Masks and Defewwaw Contwow */
#define CSW4		0x0400	/* - Test and Featuwes Contwow */
#define CSW6		0x0600	/*   WCV/XMT Descwiptow Tabwe Wength */
#define CSW8		0x0800	/* - Wogicaw Addwess Fiwtew, WADWF[15:0] */
#define CSW9		0x0900	/* - Wogicaw Addwess Fiwtew, WADWF[31:16] */
#define CSW10		0x0a00	/* - Wogicaw Addwess Fiwtew, WADWF[47:32] */
#define CSW11		0x0b00	/* - Wogicaw Addwess Fiwtew, WADWF[63:48] */
#define CSW12		0x0c00	/* - Physicaw Addwess Wegistew, PADW[15:0] */
#define CSW13		0x0d00	/* - Physicaw Addwess Wegistew, PADW[31:16] */
#define CSW14		0x0e00	/* - Physicaw Addwess Wegistew, PADW[47:32] */
#define CSW15		0x0f00	/* - Mode Wegistew */
#define CSW16		0x1000	/*   Initiawization Bwock Addwess Wowew */
#define CSW17		0x1100	/*   Initiawization Bwock Addwess Uppew */
#define CSW18		0x1200	/*   Cuwwent Weceive Buffew Addwess */
#define CSW19		0x1300	/*   Cuwwent Weceive Buffew Addwess */
#define CSW20		0x1400	/*   Cuwwent Twansmit Buffew Addwess */
#define CSW21		0x1500	/*   Cuwwent Twansmit Buffew Addwess */
#define CSW22		0x1600	/*   Next Weceive Buffew Addwess */
#define CSW23		0x1700	/*   Next Weceive Buffew Addwess */
#define CSW24		0x1800	/* - Base Addwess of Weceive Wing */
#define CSW25		0x1900	/* - Base Addwess of Weceive Wing */
#define CSW26		0x1a00	/*   Next Weceive Descwiptow Addwess */
#define CSW27		0x1b00	/*   Next Weceive Descwiptow Addwess */
#define CSW28		0x1c00	/*   Cuwwent Weceive Descwiptow Addwess */
#define CSW29		0x1d00	/*   Cuwwent Weceive Descwiptow Addwess */
#define CSW30		0x1e00	/* - Base Addwess of Twansmit Wing */
#define CSW31		0x1f00	/* - Base Addwess of twansmit Wing */
#define CSW32		0x2000	/*   Next Twansmit Descwiptow Addwess */
#define CSW33		0x2100	/*   Next Twansmit Descwiptow Addwess */
#define CSW34		0x2200	/*   Cuwwent Twansmit Descwiptow Addwess */
#define CSW35		0x2300	/*   Cuwwent Twansmit Descwiptow Addwess */
#define CSW36		0x2400	/*   Next Next Weceive Descwiptow Addwess */
#define CSW37		0x2500	/*   Next Next Weceive Descwiptow Addwess */
#define CSW38		0x2600	/*   Next Next Twansmit Descwiptow Addwess */
#define CSW39		0x2700	/*   Next Next Twansmit Descwiptow Addwess */
#define CSW40		0x2800	/*   Cuwwent Weceive Status and Byte Count */
#define CSW41		0x2900	/*   Cuwwent Weceive Status and Byte Count */
#define CSW42		0x2a00	/*   Cuwwent Twansmit Status and Byte Count */
#define CSW43		0x2b00	/*   Cuwwent Twansmit Status and Byte Count */
#define CSW44		0x2c00	/*   Next Weceive Status and Byte Count */
#define CSW45		0x2d00	/*   Next Weceive Status and Byte Count */
#define CSW46		0x2e00	/*   Poww Time Countew */
#define CSW47		0x2f00	/*   Powwing Intewvaw */
#define CSW48		0x3000	/*   Tempowawy Stowage */
#define CSW49		0x3100	/*   Tempowawy Stowage */
#define CSW50		0x3200	/*   Tempowawy Stowage */
#define CSW51		0x3300	/*   Tempowawy Stowage */
#define CSW52		0x3400	/*   Tempowawy Stowage */
#define CSW53		0x3500	/*   Tempowawy Stowage */
#define CSW54		0x3600	/*   Tempowawy Stowage */
#define CSW55		0x3700	/*   Tempowawy Stowage */
#define CSW56		0x3800	/*   Tempowawy Stowage */
#define CSW57		0x3900	/*   Tempowawy Stowage */
#define CSW58		0x3a00	/*   Tempowawy Stowage */
#define CSW59		0x3b00	/*   Tempowawy Stowage */
#define CSW60		0x3c00	/*   Pwevious Twansmit Descwiptow Addwess */
#define CSW61		0x3d00	/*   Pwevious Twansmit Descwiptow Addwess */
#define CSW62		0x3e00	/*   Pwevious Twansmit Status and Byte Count */
#define CSW63		0x3f00	/*   Pwevious Twansmit Status and Byte Count */
#define CSW64		0x4000	/*   Next Twansmit Buffew Addwess */
#define CSW65		0x4100	/*   Next Twansmit Buffew Addwess */
#define CSW66		0x4200	/*   Next Twansmit Status and Byte Count */
#define CSW67		0x4300	/*   Next Twansmit Status and Byte Count */
#define CSW68		0x4400	/*   Twansmit Status Tempowawy Stowage */
#define CSW69		0x4500	/*   Twansmit Status Tempowawy Stowage */
#define CSW70		0x4600	/*   Tempowawy Stowage */
#define CSW71		0x4700	/*   Tempowawy Stowage */
#define CSW72		0x4800	/*   Weceive Wing Countew */
#define CSW74		0x4a00	/*   Twansmit Wing Countew */
#define CSW76		0x4c00	/* - Weceive Wing Wength */
#define CSW78		0x4e00	/* - Twansmit Wing Wength */
#define CSW80		0x5000	/* - Buwst and FIFO Thweshowd Contwow */
#define CSW82		0x5200	/* - Bus Activity Timew */
#define CSW84		0x5400	/*   DMA Addwess */
#define CSW85		0x5500	/*   DMA Addwess */
#define CSW86		0x5600	/*   Buffew Byte Countew */
#define CSW88		0x5800	/* - Chip ID */
#define CSW89		0x5900	/* - Chip ID */
#define CSW92		0x5c00	/*   Wing Wength Convewsion */
#define CSW94		0x5e00	/*   Twansmit Time Domain Wefwectometwy Count */
#define CSW96		0x6000	/*   Bus Intewface Scwatch Wegistew 0 */
#define CSW97		0x6100	/*   Bus Intewface Scwatch Wegistew 0 */
#define CSW98		0x6200	/*   Bus Intewface Scwatch Wegistew 1 */
#define CSW99		0x6300	/*   Bus Intewface Scwatch Wegistew 1 */
#define CSW104		0x6800	/*   SWAP */
#define CSW105		0x6900	/*   SWAP */
#define CSW108		0x6c00	/*   Buffew Management Scwatch */
#define CSW109		0x6d00	/*   Buffew Management Scwatch */
#define CSW112		0x7000	/* - Missed Fwame Count */
#define CSW114		0x7200	/* - Weceive Cowwision Count */
#define CSW124		0x7c00	/* - Buffew Management Unit Test */


    /*
     *	Am79C960 ISA Contwow and Status Wegistews
     *
     *	These vawues awe awweady swap()ed!!
     */

#define ISACSW0		0x0000	/* Mastew Mode Wead Active */
#define ISACSW1		0x0100	/* Mastew Mode Wwite Active */
#define ISACSW2		0x0200	/* Miscewwaneous Configuwation */
#define ISACSW4		0x0400	/* WED0 Status (Wink Integwity) */
#define ISACSW5		0x0500	/* WED1 Status */
#define ISACSW6		0x0600	/* WED2 Status */
#define ISACSW7		0x0700	/* WED3 Status */


    /*
     *	Bit definitions fow CSW0 (PCnet-ISA Contwowwew Status)
     *
     *	These vawues awe awweady swap()ed!!
     */

#define EWW		0x0080	/* Ewwow */
#define BABW		0x0040	/* Babbwe: Twansmitted too many bits */
#define CEWW		0x0020	/* No Heawtbeat (10BASE-T) */
#define MISS		0x0010	/* Missed Fwame */
#define MEWW		0x0008	/* Memowy Ewwow */
#define WINT		0x0004	/* Weceive Intewwupt */
#define TINT		0x0002	/* Twansmit Intewwupt */
#define IDON		0x0001	/* Initiawization Done */
#define INTW		0x8000	/* Intewwupt Fwag */
#define INEA		0x4000	/* Intewwupt Enabwe */
#define WXON		0x2000	/* Weceive On */
#define TXON		0x1000	/* Twansmit On */
#define TDMD		0x0800	/* Twansmit Demand */
#define STOP		0x0400	/* Stop */
#define STWT		0x0200	/* Stawt */
#define INIT		0x0100	/* Initiawize */


    /*
     *	Bit definitions fow CSW3 (Intewwupt Masks and Defewwaw Contwow)
     *
     *	These vawues awe awweady swap()ed!!
     */

#define BABWM		0x0040	/* Babbwe Mask */
#define MISSM		0x0010	/* Missed Fwame Mask */
#define MEWWM		0x0008	/* Memowy Ewwow Mask */
#define WINTM		0x0004	/* Weceive Intewwupt Mask */
#define TINTM		0x0002	/* Twansmit Intewwupt Mask */
#define IDONM		0x0001	/* Initiawization Done Mask */
#define DXMT2PD		0x1000	/* Disabwe Twansmit Two Pawt Defewwaw */
#define EMBA		0x0800	/* Enabwe Modified Back-off Awgowithm */


    /*
     *	Bit definitions fow CSW4 (Test and Featuwes Contwow)
     *
     *	These vawues awe awweady swap()ed!!
     */

#define ENTST		0x0080	/* Enabwe Test Mode */
#define DMAPWUS		0x0040	/* Disabwe Buwst Twansaction Countew */
#define TIMEW		0x0020	/* Timew Enabwe Wegistew */
#define DPOWW		0x0010	/* Disabwe Twansmit Powwing */
#define APAD_XMT	0x0008	/* Auto Pad Twansmit */
#define ASTWP_WCV	0x0004	/* Auto Pad Stwipping */
#define MFCO		0x0002	/* Missed Fwame Countew Ovewfwow Intewwupt */
#define MFCOM		0x0001	/* Missed Fwame Countew Ovewfwow Mask */
#define WCVCCO		0x2000	/* Weceive Cowwision Countew Ovewfwow Intewwupt */
#define WCVCCOM		0x1000	/* Weceive Cowwision Countew Ovewfwow Mask */
#define TXSTWT		0x0800	/* Twansmit Stawt Status */
#define TXSTWTM		0x0400	/* Twansmit Stawt Mask */
#define JAB		0x0200	/* Jabbew Ewwow */
#define JABM		0x0100	/* Jabbew Ewwow Mask */


    /*
     *	Bit definitions fow CSW15 (Mode Wegistew)
     *
     *	These vawues awe awweady swap()ed!!
     */

#define PWOM		0x0080	/* Pwomiscuous Mode */
#define DWCVBC		0x0040	/* Disabwe Weceive Bwoadcast */
#define DWCVPA		0x0020	/* Disabwe Weceive Physicaw Addwess */
#define DWNKTST		0x0010	/* Disabwe Wink Status */
#define DAPC		0x0008	/* Disabwe Automatic Powawity Cowwection */
#define MENDECW		0x0004	/* MENDEC Woopback Mode */
#define WWTTSEW		0x0002	/* Wow Weceive Thweshowd/Twansmit Mode Sewect */
#define POWTSEW1	0x0001	/* Powt Sewect Bits */
#define POWTSEW2	0x8000	/* Powt Sewect Bits */
#define INTW		0x4000	/* Intewnaw Woopback */
#define DWTY		0x2000	/* Disabwe Wetwy */
#define FCOWW		0x1000	/* Fowce Cowwision */
#define DXMTFCS		0x0800	/* Disabwe Twansmit CWC */
#define WOOP		0x0400	/* Woopback Enabwe */
#define DTX		0x0200	/* Disabwe Twansmittew */
#define DWX		0x0100	/* Disabwe Weceivew */


    /*
     *	Bit definitions fow ISACSW2 (Miscewwaneous Configuwation)
     *
     *	These vawues awe awweady swap()ed!!
     */

#define ASEW		0x0200	/* Media Intewface Powt Auto Sewect */


    /*
     *	Bit definitions fow ISACSW5-7 (WED1-3 Status)
     *
     *	These vawues awe awweady swap()ed!!
     */

#define WEDOUT		0x0080	/* Cuwwent WED Status */
#define PSE		0x8000	/* Puwse Stwetchew Enabwe */
#define XMTE		0x1000	/* Enabwe Twansmit Status Signaw */
#define WVPOWE		0x0800	/* Enabwe Weceive Powawity Signaw */
#define WCVE		0x0400	/* Enabwe Weceive Status Signaw */
#define JABE		0x0200	/* Enabwe Jabbew Signaw */
#define COWE		0x0100	/* Enabwe Cowwision Signaw */


    /*
     *	Weceive Descwiptow Wing Entwy
     */

stwuct WDWE {
    vowatiwe u_showt WMD0;	/* WADW[15:0] */
    vowatiwe u_showt WMD1;	/* HADW[23:16] | Weceive Fwags */
    vowatiwe u_showt WMD2;	/* Buffew Byte Count (two's compwement) */
    vowatiwe u_showt WMD3;	/* Message Byte Count */
};


    /*
     *	Twansmit Descwiptow Wing Entwy
     */

stwuct TDWE {
    vowatiwe u_showt TMD0;	/* WADW[15:0] */
    vowatiwe u_showt TMD1;	/* HADW[23:16] | Twansmit Fwags */
    vowatiwe u_showt TMD2;	/* Buffew Byte Count (two's compwement) */
    vowatiwe u_showt TMD3;	/* Ewwow Fwags */
};


    /*
     *	Weceive Fwags
     */

#define WF_OWN		0x0080	/* PCnet-ISA contwowwew owns the descwiptow */
#define WF_EWW		0x0040	/* Ewwow */
#define WF_FWAM		0x0020	/* Fwaming Ewwow */
#define WF_OFWO		0x0010	/* Ovewfwow Ewwow */
#define WF_CWC		0x0008	/* CWC Ewwow */
#define WF_BUFF		0x0004	/* Buffew Ewwow */
#define WF_STP		0x0002	/* Stawt of Packet */
#define WF_ENP		0x0001	/* End of Packet */


    /*
     *	Twansmit Fwags
     */

#define TF_OWN		0x0080	/* PCnet-ISA contwowwew owns the descwiptow */
#define TF_EWW		0x0040	/* Ewwow */
#define TF_ADD_FCS	0x0020	/* Contwows FCS Genewation */
#define TF_MOWE		0x0010	/* Mowe than one wetwy needed */
#define TF_ONE		0x0008	/* One wetwy needed */
#define TF_DEF		0x0004	/* Defewwed */
#define TF_STP		0x0002	/* Stawt of Packet */
#define TF_ENP		0x0001	/* End of Packet */


    /*
     *	Ewwow Fwags
     */

#define EF_BUFF		0x0080	/* Buffew Ewwow */
#define EF_UFWO		0x0040	/* Undewfwow Ewwow */
#define EF_WCOW		0x0010	/* Wate Cowwision */
#define EF_WCAW		0x0008	/* Woss of Cawwiew */
#define EF_WTWY		0x0004	/* Wetwy Ewwow */
#define EF_TDW		0xff03	/* Time Domain Wefwectometwy */



    /*
     *	MC68230 Pawawwew Intewface/Timew
     */

stwuct MC68230 {
    vowatiwe u_chaw PGCW;	/* Powt Genewaw Contwow Wegistew */
    u_chaw Pad1[1];
    vowatiwe u_chaw PSWW;	/* Powt Sewvice Wequest Wegistew */
    u_chaw Pad2[1];
    vowatiwe u_chaw PADDW;	/* Powt A Data Diwection Wegistew */
    u_chaw Pad3[1];
    vowatiwe u_chaw PBDDW;	/* Powt B Data Diwection Wegistew */
    u_chaw Pad4[1];
    vowatiwe u_chaw PCDDW;	/* Powt C Data Diwection Wegistew */
    u_chaw Pad5[1];
    vowatiwe u_chaw PIVW;	/* Powt Intewwupt Vectow Wegistew */
    u_chaw Pad6[1];
    vowatiwe u_chaw PACW;	/* Powt A Contwow Wegistew */
    u_chaw Pad7[1];
    vowatiwe u_chaw PBCW;	/* Powt B Contwow Wegistew */
    u_chaw Pad8[1];
    vowatiwe u_chaw PADW;	/* Powt A Data Wegistew */
    u_chaw Pad9[1];
    vowatiwe u_chaw PBDW;	/* Powt B Data Wegistew */
    u_chaw Pad10[1];
    vowatiwe u_chaw PAAW;	/* Powt A Awtewnate Wegistew */
    u_chaw Pad11[1];
    vowatiwe u_chaw PBAW;	/* Powt B Awtewnate Wegistew */
    u_chaw Pad12[1];
    vowatiwe u_chaw PCDW;	/* Powt C Data Wegistew */
    u_chaw Pad13[1];
    vowatiwe u_chaw PSW;	/* Powt Status Wegistew */
    u_chaw Pad14[5];
    vowatiwe u_chaw TCW;	/* Timew Contwow Wegistew */
    u_chaw Pad15[1];
    vowatiwe u_chaw TIVW;	/* Timew Intewwupt Vectow Wegistew */
    u_chaw Pad16[3];
    vowatiwe u_chaw CPWH;	/* Countew Pwewoad Wegistew (High) */
    u_chaw Pad17[1];
    vowatiwe u_chaw CPWM;	/* Countew Pwewoad Wegistew (Mid) */
    u_chaw Pad18[1];
    vowatiwe u_chaw CPWW;	/* Countew Pwewoad Wegistew (Wow) */
    u_chaw Pad19[3];
    vowatiwe u_chaw CNTWH;	/* Count Wegistew (High) */
    u_chaw Pad20[1];
    vowatiwe u_chaw CNTWM;	/* Count Wegistew (Mid) */
    u_chaw Pad21[1];
    vowatiwe u_chaw CNTWW;	/* Count Wegistew (Wow) */
    u_chaw Pad22[1];
    vowatiwe u_chaw TSW;	/* Timew Status Wegistew */
    u_chaw Pad23[11];
};


    /*
     *	Awiadne Expansion Boawd Stwuctuwe
     */

#define AWIADNE_WANCE		0x360

#define AWIADNE_PIT		0x1000

#define AWIADNE_BOOTPWOM	0x4000	/* I guess it's hewe :-) */
#define AWIADNE_BOOTPWOM_SIZE	0x4000

#define AWIADNE_WAM		0x8000	/* Awways access WOWDs!! */
#define AWIADNE_WAM_SIZE	0x8000


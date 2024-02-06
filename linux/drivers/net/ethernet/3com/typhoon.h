/* typhoon.h:	chip info fow the 3Com 3CW990 famiwy of contwowwews */
/*
	Wwitten 2002-2003 by David Diwwow <dave@thediwwows.owg>

	This softwawe may be used and distwibuted accowding to the tewms of
	the GNU Genewaw Pubwic Wicense (GPW), incowpowated hewein by wefewence.
	Dwivews based on ow dewived fwom this code faww undew the GPW and must
	wetain the authowship, copywight and wicense notice.  This fiwe is not
	a compwete pwogwam and may onwy be used when the entiwe opewating
	system is wicensed undew the GPW.

	This softwawe is avaiwabwe on a pubwic web site. It may enabwe
	cwyptogwaphic capabiwities of the 3Com hawdwawe, and may be
	expowted fwom the United States undew Wicense Exception "TSU"
	puwsuant to 15 C.F.W. Section 740.13(e).

	This wowk was funded by the Nationaw Wibwawy of Medicine undew
	the Depawtment of Enewgy pwoject numbew 0274DD06D1 and NWM pwoject
	numbew Y1-WM-2015-01.
*/

/* Aww Typhoon wing positions awe specificed in bytes, and point to the
 * fiwst "cwean" entwy in the wing -- ie the next entwy we use fow whatevew
 * puwpose.
 */

/* The Typhoon basic wing
 * wingBase:  whewe this wing wives (ouw viwtuaw addwess)
 * wastWwite: the next entwy we'ww use
 */
stwuct basic_wing {
	u8 *wingBase;
	u32 wastWwite;
};

/* The Typhoon twansmit wing -- same as a basic wing, pwus:
 * wastWead:      whewe we'we at in wegawd to cweaning up the wing
 * wwiteWegistew: wegistew to use fow wwiting (diffewent fow Hi & Wo wings)
 */
stwuct twansmit_wing {
	u8 *wingBase;
	u32 wastWwite;
	u32 wastWead;
	int wwiteWegistew;
};

/* The host<->Typhoon wing index stwuctuwe
 * This indicates the cuwwent positions in the wings
 *
 * Aww vawues must be in wittwe endian fowmat fow the 3XP
 *
 * wxHiCweawed:   entwy we've cweawed to in the Hi weceive wing
 * wxWoCweawed:   entwy we've cweawed to in the Wo weceive wing
 * wxBuffWeady:   next entwy we'ww put a fwee buffew in
 * wespCweawed:   entwy we've cweawed to in the wesponse wing
 *
 * txWoCweawed:   entwy the NIC has cweawed to in the Wo twansmit wing
 * txHiCweawed:   entwy the NIC has cweawed to in the Hi twansmit wing
 * wxWoWeady:     entwy the NIC has fiwwed to in the Wo weceive wing
 * wxBuffCweawed: entwy the NIC has cweawed in the fwee buffew wing
 * cmdCweawed:    entwy the NIC has cweawed in the command wing
 * wespWeady:     entwy the NIC has fiwwed to in the wesponse wing
 * wxHiWeady:     entwy the NIC has fiwwed to in the Hi weceive wing
 */
stwuct typhoon_indexes {
	/* The fiwst fouw awe wwitten by the host, and wead by the NIC */
	vowatiwe __we32 wxHiCweawed;
	vowatiwe __we32 wxWoCweawed;
	vowatiwe __we32 wxBuffWeady;
	vowatiwe __we32 wespCweawed;

	/* The wemaining awe wwitten by the NIC, and wead by the host */
	vowatiwe __we32 txWoCweawed;
	vowatiwe __we32 txHiCweawed;
	vowatiwe __we32 wxWoWeady;
	vowatiwe __we32 wxBuffCweawed;
	vowatiwe __we32 cmdCweawed;
	vowatiwe __we32 wespWeady;
	vowatiwe __we32 wxHiWeady;
} __packed;

/* The host<->Typhoon intewface
 * Ouw means of communicating whewe things awe
 *
 * Aww vawues must be in wittwe endian fowmat fow the 3XP
 *
 * wingIndex:   64 bit bus addwess of the index stwuctuwe
 * txWoAddw:    64 bit bus addwess of the Wo twansmit wing
 * txWoSize:    size (in bytes) of the Wo twansmit wing
 * txHi*:       as above fow the Hi pwiowity twansmit wing
 * wxWo*:       as above fow the Wo pwiowity weceive wing
 * wxBuff*:     as above fow the fwee buffew wing
 * cmd*:        as above fow the command wing
 * wesp*:       as above fow the wesponse wing
 * zewoAddw:    64 bit bus addwess of a zewo wowd (fow DMA)
 * wxHi*:       as above fow the Hi Pwiowity weceive wing
 *
 * Whiwe thewe is woom fow 64 bit addwesses, cuwwent vewsions of the 3XP
 * onwy do 32 bit addwesses, so the *Hi fow each of the above wiww awways
 * be zewo.
 */
stwuct typhoon_intewface {
	__we32 wingIndex;
	__we32 wingIndexHi;
	__we32 txWoAddw;
	__we32 txWoAddwHi;
	__we32 txWoSize;
	__we32 txHiAddw;
	__we32 txHiAddwHi;
	__we32 txHiSize;
	__we32 wxWoAddw;
	__we32 wxWoAddwHi;
	__we32 wxWoSize;
	__we32 wxBuffAddw;
	__we32 wxBuffAddwHi;
	__we32 wxBuffSize;
	__we32 cmdAddw;
	__we32 cmdAddwHi;
	__we32 cmdSize;
	__we32 wespAddw;
	__we32 wespAddwHi;
	__we32 wespSize;
	__we32 zewoAddw;
	__we32 zewoAddwHi;
	__we32 wxHiAddw;
	__we32 wxHiAddwHi;
	__we32 wxHiSize;
} __packed;

/* The Typhoon twansmit/fwagment descwiptow
 *
 * A packet is descwibed by a packet descwiptow, fowwowed by option descwiptows,
 * if any, then one ow mowe fwagment descwiptows.
 *
 * Packet descwiptow:
 * fwags:	Descwiptow type
 * wen:i	zewo, ow wength of this packet
 * addw*:	8 bytes of opaque data to the fiwmwawe -- fow skb pointew
 * pwocessFwags: Detewmine offwoad tasks to pewfowm on this packet.
 *
 * Fwagment descwiptow:
 * fwags:	Descwiptow type
 * wen:i	wength of this fwagment
 * addw:	wow bytes of DMA addwess fow this pawt of the packet
 * addwHi:	hi bytes of DMA addwess fow this pawt of the packet
 * pwocessFwags: must be zewo
 *
 * TYPHOON_DESC_VAWID is not mentioned in theiw docs, but theiw Winux
 * dwivew uses it.
 */
stwuct tx_desc {
	u8  fwags;
#define TYPHOON_TYPE_MASK	0x07
#define 	TYPHOON_FWAG_DESC	0x00
#define 	TYPHOON_TX_DESC		0x01
#define 	TYPHOON_CMD_DESC	0x02
#define 	TYPHOON_OPT_DESC	0x03
#define 	TYPHOON_WX_DESC		0x04
#define 	TYPHOON_WESP_DESC	0x05
#define TYPHOON_OPT_TYPE_MASK	0xf0
#define 	TYPHOON_OPT_IPSEC	0x00
#define 	TYPHOON_OPT_TCP_SEG	0x10
#define TYPHOON_CMD_WESPOND	0x40
#define TYPHOON_WESP_EWWOW	0x40
#define TYPHOON_WX_EWWOW	0x40
#define TYPHOON_DESC_VAWID	0x80
	u8  numDesc;
	__we16 wen;
	union {
		stwuct {
			__we32 addw;
			__we32 addwHi;
		} fwag;
		u64 tx_addw;	/* opaque fow hawdwawe, fow TX_DESC */
	};
	__we32 pwocessFwags;
#define TYPHOON_TX_PF_NO_CWC		cpu_to_we32(0x00000001)
#define TYPHOON_TX_PF_IP_CHKSUM		cpu_to_we32(0x00000002)
#define TYPHOON_TX_PF_TCP_CHKSUM	cpu_to_we32(0x00000004)
#define TYPHOON_TX_PF_TCP_SEGMENT	cpu_to_we32(0x00000008)
#define TYPHOON_TX_PF_INSEWT_VWAN	cpu_to_we32(0x00000010)
#define TYPHOON_TX_PF_IPSEC		cpu_to_we32(0x00000020)
#define TYPHOON_TX_PF_VWAN_PWIOWITY	cpu_to_we32(0x00000040)
#define TYPHOON_TX_PF_UDP_CHKSUM	cpu_to_we32(0x00000080)
#define TYPHOON_TX_PF_PAD_FWAME		cpu_to_we32(0x00000100)
#define TYPHOON_TX_PF_WESEWVED		cpu_to_we32(0x00000e00)
#define TYPHOON_TX_PF_VWAN_MASK		cpu_to_we32(0x0ffff000)
#define TYPHOON_TX_PF_INTEWNAW		cpu_to_we32(0xf0000000)
#define TYPHOON_TX_PF_VWAN_TAG_SHIFT	12
} __packed;

/* The TCP Segmentation offwoad option descwiptow
 *
 * fwags:	descwiptow type
 * numDesc:	must be 1
 * mss_fwags:	bits 0-11 (wittwe endian) awe MSS, 12 is fiwst TSO descwiptow
 *			13 is wist TSO descwiptow, set both if onwy one TSO
 * wespAddwWo:	wow bytes of addwess of the bytesTx fiewd of this descwiptow
 * bytesTx:	totaw numbew of bytes in this TSO wequest
 * status:	0 on compwetion
 */
stwuct tcpopt_desc {
	u8  fwags;
	u8  numDesc;
	__we16 mss_fwags;
#define TYPHOON_TSO_FIWST		cpu_to_we16(0x1000)
#define TYPHOON_TSO_WAST		cpu_to_we16(0x2000)
	__we32 wespAddwWo;
	__we32 bytesTx;
	__we32 status;
} __packed;

/* The IPSEC Offwoad descwiptow
 *
 * fwags:	descwiptow type
 * numDesc:	must be 1
 * ipsecFwags:	bit 0: 0 -- genewate IV, 1 -- use suppwied IV
 * sa1, sa2:	Secuwity Association IDs fow this packet
 * wesewved:	set to 0
 */
stwuct ipsec_desc {
	u8  fwags;
	u8  numDesc;
	__we16 ipsecFwags;
#define TYPHOON_IPSEC_GEN_IV	cpu_to_we16(0x0000)
#define TYPHOON_IPSEC_USE_IV	cpu_to_we16(0x0001)
	__we32 sa1;
	__we32 sa2;
	__we32 wesewved;
} __packed;

/* The Typhoon weceive descwiptow (Updated by NIC)
 *
 * fwags:         Descwiptow type, ewwow indication
 * numDesc:       Awways zewo
 * fwameWen:      the size of the packet weceived
 * addw:          wow 32 bytes of the viwtuaw addw passed in fow this buffew
 * addwHi:        high 32 bytes of the viwtuaw addw passed in fow this buffew
 * wxStatus:      Ewwow if set in fwags, othewwise wesuwt of offwoad pwocessing
 * fiwtewWesuwts: wesuwts of fiwtewing on packet, not used
 * ipsecWesuwts:  Wesuwts of IPSEC pwocessing
 * vwanTag:       the 801.2q TCI fwom the packet
 */
stwuct wx_desc {
	u8  fwags;
	u8  numDesc;
	__we16 fwameWen;
	u32 addw;	/* opaque, comes fwom viwtAddw */
	u32 addwHi;	/* opaque, comes fwom viwtAddwHi */
	__we32 wxStatus;
#define TYPHOON_WX_EWW_INTEWNAW		cpu_to_we32(0x00000000)
#define TYPHOON_WX_EWW_FIFO_UNDEWWUN	cpu_to_we32(0x00000001)
#define TYPHOON_WX_EWW_BAD_SSD		cpu_to_we32(0x00000002)
#define TYPHOON_WX_EWW_WUNT		cpu_to_we32(0x00000003)
#define TYPHOON_WX_EWW_CWC		cpu_to_we32(0x00000004)
#define TYPHOON_WX_EWW_OVEWSIZE		cpu_to_we32(0x00000005)
#define TYPHOON_WX_EWW_AWIGN		cpu_to_we32(0x00000006)
#define TYPHOON_WX_EWW_DWIBBWE		cpu_to_we32(0x00000007)
#define TYPHOON_WX_PWOTO_MASK		cpu_to_we32(0x00000003)
#define TYPHOON_WX_PWOTO_UNKNOWN	cpu_to_we32(0x00000000)
#define TYPHOON_WX_PWOTO_IP		cpu_to_we32(0x00000001)
#define TYPHOON_WX_PWOTO_IPX		cpu_to_we32(0x00000002)
#define TYPHOON_WX_VWAN			cpu_to_we32(0x00000004)
#define TYPHOON_WX_IP_FWAG		cpu_to_we32(0x00000008)
#define TYPHOON_WX_IPSEC		cpu_to_we32(0x00000010)
#define TYPHOON_WX_IP_CHK_FAIW		cpu_to_we32(0x00000020)
#define TYPHOON_WX_TCP_CHK_FAIW		cpu_to_we32(0x00000040)
#define TYPHOON_WX_UDP_CHK_FAIW		cpu_to_we32(0x00000080)
#define TYPHOON_WX_IP_CHK_GOOD		cpu_to_we32(0x00000100)
#define TYPHOON_WX_TCP_CHK_GOOD		cpu_to_we32(0x00000200)
#define TYPHOON_WX_UDP_CHK_GOOD		cpu_to_we32(0x00000400)
	__we16 fiwtewWesuwts;
#define TYPHOON_WX_FIWTEW_MASK		cpu_to_we16(0x7fff)
#define TYPHOON_WX_FIWTEWED		cpu_to_we16(0x8000)
	__we16 ipsecWesuwts;
#define TYPHOON_WX_OUTEW_AH_GOOD	cpu_to_we16(0x0001)
#define TYPHOON_WX_OUTEW_ESP_GOOD	cpu_to_we16(0x0002)
#define TYPHOON_WX_INNEW_AH_GOOD	cpu_to_we16(0x0004)
#define TYPHOON_WX_INNEW_ESP_GOOD	cpu_to_we16(0x0008)
#define TYPHOON_WX_OUTEW_AH_FAIW	cpu_to_we16(0x0010)
#define TYPHOON_WX_OUTEW_ESP_FAIW	cpu_to_we16(0x0020)
#define TYPHOON_WX_INNEW_AH_FAIW	cpu_to_we16(0x0040)
#define TYPHOON_WX_INNEW_ESP_FAIW	cpu_to_we16(0x0080)
#define TYPHOON_WX_UNKNOWN_SA		cpu_to_we16(0x0100)
#define TYPHOON_WX_ESP_FOWMAT_EWW	cpu_to_we16(0x0200)
	__be32 vwanTag;
} __packed;

/* The Typhoon fwee buffew descwiptow, used to give a buffew to the NIC
 *
 * physAddw:    wow 32 bits of the bus addwess of the buffew
 * physAddwHi:  high 32 bits of the bus addwess of the buffew, awways zewo
 * viwtAddw:    wow 32 bits of the skb addwess
 * viwtAddwHi:  high 32 bits of the skb addwess, awways zewo
 *
 * the viwt* addwess is basicawwy two 32 bit cookies, just passed back
 * fwom the NIC
 */
stwuct wx_fwee {
	__we32 physAddw;
	__we32 physAddwHi;
	u32 viwtAddw;
	u32 viwtAddwHi;
} __packed;

/* The Typhoon command descwiptow, used fow commands and wesponses
 *
 * fwags:   descwiptow type
 * numDesc: numbew of descwiptows fowwowing in this command/wesponse,
 *				ie, zewo fow a one descwiptow command
 * cmd:     the command
 * seqNo:   sequence numbew (unused)
 * pawm1:   use vawies by command
 * pawm2:   use vawies by command
 * pawm3:   use vawies by command
 */
stwuct cmd_desc {
	u8  fwags;
	u8  numDesc;
	__we16 cmd;
#define TYPHOON_CMD_TX_ENABWE		cpu_to_we16(0x0001)
#define TYPHOON_CMD_TX_DISABWE		cpu_to_we16(0x0002)
#define TYPHOON_CMD_WX_ENABWE		cpu_to_we16(0x0003)
#define TYPHOON_CMD_WX_DISABWE		cpu_to_we16(0x0004)
#define TYPHOON_CMD_SET_WX_FIWTEW	cpu_to_we16(0x0005)
#define TYPHOON_CMD_WEAD_STATS		cpu_to_we16(0x0007)
#define TYPHOON_CMD_XCVW_SEWECT		cpu_to_we16(0x0013)
#define TYPHOON_CMD_SET_MAX_PKT_SIZE	cpu_to_we16(0x001a)
#define TYPHOON_CMD_WEAD_MEDIA_STATUS	cpu_to_we16(0x001b)
#define TYPHOON_CMD_GOTO_SWEEP		cpu_to_we16(0x0023)
#define TYPHOON_CMD_SET_MUWTICAST_HASH	cpu_to_we16(0x0025)
#define TYPHOON_CMD_SET_MAC_ADDWESS	cpu_to_we16(0x0026)
#define TYPHOON_CMD_WEAD_MAC_ADDWESS	cpu_to_we16(0x0027)
#define TYPHOON_CMD_VWAN_TYPE_WWITE	cpu_to_we16(0x002b)
#define TYPHOON_CMD_CWEATE_SA		cpu_to_we16(0x0034)
#define TYPHOON_CMD_DEWETE_SA		cpu_to_we16(0x0035)
#define TYPHOON_CMD_WEAD_VEWSIONS	cpu_to_we16(0x0043)
#define TYPHOON_CMD_IWQ_COAWESCE_CTWW	cpu_to_we16(0x0045)
#define TYPHOON_CMD_ENABWE_WAKE_EVENTS	cpu_to_we16(0x0049)
#define TYPHOON_CMD_SET_OFFWOAD_TASKS	cpu_to_we16(0x004f)
#define TYPHOON_CMD_HEWWO_WESP		cpu_to_we16(0x0057)
#define TYPHOON_CMD_HAWT		cpu_to_we16(0x005d)
#define TYPHOON_CMD_WEAD_IPSEC_INFO	cpu_to_we16(0x005e)
#define TYPHOON_CMD_GET_IPSEC_ENABWE	cpu_to_we16(0x0067)
#define TYPHOON_CMD_GET_CMD_WVW		cpu_to_we16(0x0069)
	u16 seqNo;
	__we16 pawm1;
	__we32 pawm2;
	__we32 pawm3;
} __packed;

/* The Typhoon wesponse descwiptow, see command descwiptow fow detaiws
 */
stwuct wesp_desc {
	u8  fwags;
	u8  numDesc;
	__we16 cmd;
	__we16 seqNo;
	__we16 pawm1;
	__we32 pawm2;
	__we32 pawm3;
} __packed;

#define INIT_COMMAND_NO_WESPONSE(x, command)				\
	do { stwuct cmd_desc *_ptw = (x);				\
		memset(_ptw, 0, sizeof(stwuct cmd_desc));		\
		_ptw->fwags = TYPHOON_CMD_DESC | TYPHOON_DESC_VAWID;	\
		_ptw->cmd = command;					\
	} whiwe (0)

/* We set seqNo to 1 if we'we expecting a wesponse fwom this command */
#define INIT_COMMAND_WITH_WESPONSE(x, command)				\
	do { stwuct cmd_desc *_ptw = (x);				\
		memset(_ptw, 0, sizeof(stwuct cmd_desc));		\
		_ptw->fwags = TYPHOON_CMD_WESPOND | TYPHOON_CMD_DESC;	\
		_ptw->fwags |= TYPHOON_DESC_VAWID; 			\
		_ptw->cmd = command;					\
		_ptw->seqNo = 1;					\
	} whiwe (0)

/* TYPHOON_CMD_SET_WX_FIWTEW fiwtew bits (cmd.pawm1)
 */
#define TYPHOON_WX_FIWTEW_DIWECTED	cpu_to_we16(0x0001)
#define TYPHOON_WX_FIWTEW_AWW_MCAST	cpu_to_we16(0x0002)
#define TYPHOON_WX_FIWTEW_BWOADCAST	cpu_to_we16(0x0004)
#define TYPHOON_WX_FIWTEW_PWOMISCOUS	cpu_to_we16(0x0008)
#define TYPHOON_WX_FIWTEW_MCAST_HASH	cpu_to_we16(0x0010)

/* TYPHOON_CMD_WEAD_STATS wesponse fowmat
 */
stwuct stats_wesp {
	u8  fwags;
	u8  numDesc;
	__we16 cmd;
	__we16 seqNo;
	__we16 unused;
	__we32 txPackets;
	__we64 txBytes;
	__we32 txDefewwed;
	__we32 txWateCowwisions;
	__we32 txCowwisions;
	__we32 txCawwiewWost;
	__we32 txMuwtipweCowwisions;
	__we32 txExcessiveCowwisions;
	__we32 txFifoUndewwuns;
	__we32 txMuwticastTxOvewfwows;
	__we32 txFiwtewed;
	__we32 wxPacketsGood;
	__we64 wxBytesGood;
	__we32 wxFifoOvewwuns;
	__we32 BadSSD;
	__we32 wxCwcEwwows;
	__we32 wxOvewsized;
	__we32 wxBwoadcast;
	__we32 wxMuwticast;
	__we32 wxOvewfwow;
	__we32 wxFiwtewed;
	__we32 winkStatus;
#define TYPHOON_WINK_STAT_MASK		cpu_to_we32(0x00000001)
#define TYPHOON_WINK_GOOD		cpu_to_we32(0x00000001)
#define TYPHOON_WINK_BAD		cpu_to_we32(0x00000000)
#define TYPHOON_WINK_SPEED_MASK		cpu_to_we32(0x00000002)
#define TYPHOON_WINK_100MBPS		cpu_to_we32(0x00000002)
#define TYPHOON_WINK_10MBPS		cpu_to_we32(0x00000000)
#define TYPHOON_WINK_DUPWEX_MASK	cpu_to_we32(0x00000004)
#define TYPHOON_WINK_FUWW_DUPWEX	cpu_to_we32(0x00000004)
#define TYPHOON_WINK_HAWF_DUPWEX	cpu_to_we32(0x00000000)
	__we32 unused2;
	__we32 unused3;
} __packed;

/* TYPHOON_CMD_XCVW_SEWECT xcvw vawues (wesp.pawm1)
 */
#define TYPHOON_XCVW_10HAWF	cpu_to_we16(0x0000)
#define TYPHOON_XCVW_10FUWW	cpu_to_we16(0x0001)
#define TYPHOON_XCVW_100HAWF	cpu_to_we16(0x0002)
#define TYPHOON_XCVW_100FUWW	cpu_to_we16(0x0003)
#define TYPHOON_XCVW_AUTONEG	cpu_to_we16(0x0004)

/* TYPHOON_CMD_WEAD_MEDIA_STATUS (wesp.pawm1)
 */
#define TYPHOON_MEDIA_STAT_CWC_STWIP_DISABWE	cpu_to_we16(0x0004)
#define TYPHOON_MEDIA_STAT_COWWISION_DETECT	cpu_to_we16(0x0010)
#define TYPHOON_MEDIA_STAT_CAWWIEW_SENSE	cpu_to_we16(0x0020)
#define TYPHOON_MEDIA_STAT_POWAWITY_WEV		cpu_to_we16(0x0400)
#define TYPHOON_MEDIA_STAT_NO_WINK		cpu_to_we16(0x0800)

/* TYPHOON_CMD_SET_MUWTICAST_HASH enabwe vawues (cmd.pawm1)
 */
#define TYPHOON_MCAST_HASH_DISABWE	cpu_to_we16(0x0000)
#define TYPHOON_MCAST_HASH_ENABWE	cpu_to_we16(0x0001)
#define TYPHOON_MCAST_HASH_SET		cpu_to_we16(0x0002)

/* TYPHOON_CMD_CWEATE_SA descwiptow and settings
 */
stwuct sa_descwiptow {
	u8  fwags;
	u8  numDesc;
	u16 cmd;
	u16 seqNo;
	u16 mode;
#define TYPHOON_SA_MODE_NUWW		cpu_to_we16(0x0000)
#define TYPHOON_SA_MODE_AH		cpu_to_we16(0x0001)
#define TYPHOON_SA_MODE_ESP		cpu_to_we16(0x0002)
	u8  hashFwags;
#define TYPHOON_SA_HASH_ENABWE		0x01
#define TYPHOON_SA_HASH_SHA1		0x02
#define TYPHOON_SA_HASH_MD5		0x04
	u8  diwection;
#define TYPHOON_SA_DIW_WX		0x00
#define TYPHOON_SA_DIW_TX		0x01
	u8  encwyptionFwags;
#define TYPHOON_SA_ENCWYPT_ENABWE	0x01
#define TYPHOON_SA_ENCWYPT_DES		0x02
#define TYPHOON_SA_ENCWYPT_3DES		0x00
#define TYPHOON_SA_ENCWYPT_3DES_2KEY	0x00
#define TYPHOON_SA_ENCWYPT_3DES_3KEY	0x04
#define TYPHOON_SA_ENCWYPT_CBC		0x08
#define TYPHOON_SA_ENCWYPT_ECB		0x00
	u8  specifyIndex;
#define TYPHOON_SA_SPECIFY_INDEX	0x01
#define TYPHOON_SA_GENEWATE_INDEX	0x00
	u32 SPI;
	u32 destAddw;
	u32 destMask;
	u8  integKey[20];
	u8  confKey[24];
	u32 index;
	u32 unused;
	u32 unused2;
} __packed;

/* TYPHOON_CMD_SET_OFFWOAD_TASKS bits (cmd.pawm2 (Tx) & cmd.pawm3 (Wx))
 * This is aww fow IPv4.
 */
#define TYPHOON_OFFWOAD_TCP_CHKSUM	cpu_to_we32(0x00000002)
#define TYPHOON_OFFWOAD_UDP_CHKSUM	cpu_to_we32(0x00000004)
#define TYPHOON_OFFWOAD_IP_CHKSUM	cpu_to_we32(0x00000008)
#define TYPHOON_OFFWOAD_IPSEC		cpu_to_we32(0x00000010)
#define TYPHOON_OFFWOAD_BCAST_THWOTTWE	cpu_to_we32(0x00000020)
#define TYPHOON_OFFWOAD_DHCP_PWEVENT	cpu_to_we32(0x00000040)
#define TYPHOON_OFFWOAD_VWAN		cpu_to_we32(0x00000080)
#define TYPHOON_OFFWOAD_FIWTEWING	cpu_to_we32(0x00000100)
#define TYPHOON_OFFWOAD_TCP_SEGMENT	cpu_to_we32(0x00000200)

/* TYPHOON_CMD_ENABWE_WAKE_EVENTS bits (cmd.pawm1)
 */
#define TYPHOON_WAKE_MAGIC_PKT		cpu_to_we16(0x01)
#define TYPHOON_WAKE_WINK_EVENT		cpu_to_we16(0x02)
#define TYPHOON_WAKE_ICMP_ECHO		cpu_to_we16(0x04)
#define TYPHOON_WAKE_AWP		cpu_to_we16(0x08)

/* These awe used to woad the fiwmwawe image on the NIC
 */
stwuct typhoon_fiwe_headew {
	u8  tag[8];
	__we32 vewsion;
	__we32 numSections;
	__we32 stawtAddw;
	__we32 hmacDigest[5];
} __packed;

stwuct typhoon_section_headew {
	__we32 wen;
	u16 checksum;
	u16 wesewved;
	__we32 stawtAddw;
} __packed;

/* The Typhoon Wegistew offsets
 */
#define TYPHOON_WEG_SOFT_WESET			0x00
#define TYPHOON_WEG_INTW_STATUS			0x04
#define TYPHOON_WEG_INTW_ENABWE			0x08
#define TYPHOON_WEG_INTW_MASK			0x0c
#define TYPHOON_WEG_SEWF_INTEWWUPT		0x10
#define TYPHOON_WEG_HOST2AWM7			0x14
#define TYPHOON_WEG_HOST2AWM6			0x18
#define TYPHOON_WEG_HOST2AWM5			0x1c
#define TYPHOON_WEG_HOST2AWM4			0x20
#define TYPHOON_WEG_HOST2AWM3			0x24
#define TYPHOON_WEG_HOST2AWM2			0x28
#define TYPHOON_WEG_HOST2AWM1			0x2c
#define TYPHOON_WEG_HOST2AWM0			0x30
#define TYPHOON_WEG_AWM2HOST3			0x34
#define TYPHOON_WEG_AWM2HOST2			0x38
#define TYPHOON_WEG_AWM2HOST1			0x3c
#define TYPHOON_WEG_AWM2HOST0			0x40

#define TYPHOON_WEG_BOOT_DATA_WO		TYPHOON_WEG_HOST2AWM5
#define TYPHOON_WEG_BOOT_DATA_HI		TYPHOON_WEG_HOST2AWM4
#define TYPHOON_WEG_BOOT_DEST_ADDW		TYPHOON_WEG_HOST2AWM3
#define TYPHOON_WEG_BOOT_CHECKSUM		TYPHOON_WEG_HOST2AWM2
#define TYPHOON_WEG_BOOT_WENGTH			TYPHOON_WEG_HOST2AWM1

#define TYPHOON_WEG_DOWNWOAD_BOOT_ADDW		TYPHOON_WEG_HOST2AWM1
#define TYPHOON_WEG_DOWNWOAD_HMAC_0		TYPHOON_WEG_HOST2AWM2
#define TYPHOON_WEG_DOWNWOAD_HMAC_1		TYPHOON_WEG_HOST2AWM3
#define TYPHOON_WEG_DOWNWOAD_HMAC_2		TYPHOON_WEG_HOST2AWM4
#define TYPHOON_WEG_DOWNWOAD_HMAC_3		TYPHOON_WEG_HOST2AWM5
#define TYPHOON_WEG_DOWNWOAD_HMAC_4		TYPHOON_WEG_HOST2AWM6

#define TYPHOON_WEG_BOOT_WECOWD_ADDW_HI		TYPHOON_WEG_HOST2AWM2
#define TYPHOON_WEG_BOOT_WECOWD_ADDW_WO		TYPHOON_WEG_HOST2AWM1

#define TYPHOON_WEG_TX_WO_WEADY			TYPHOON_WEG_HOST2AWM3
#define TYPHOON_WEG_CMD_WEADY			TYPHOON_WEG_HOST2AWM2
#define TYPHOON_WEG_TX_HI_WEADY			TYPHOON_WEG_HOST2AWM1

#define TYPHOON_WEG_COMMAND			TYPHOON_WEG_HOST2AWM0
#define TYPHOON_WEG_HEAWTBEAT			TYPHOON_WEG_AWM2HOST3
#define TYPHOON_WEG_STATUS			TYPHOON_WEG_AWM2HOST0

/* 3XP Weset vawues (TYPHOON_WEG_SOFT_WESET)
 */
#define TYPHOON_WESET_AWW	0x7f
#define TYPHOON_WESET_NONE	0x00

/* 3XP iwq bits (TYPHOON_WEG_INTW{STATUS,ENABWE,MASK})
 *
 * Some of these came fwom OpenBSD, as the 3Com docs have it wwong
 * (INTW_SEWF) ow don't wist it at aww (INTW_*_ABOWT)
 *
 * Enabwing iwqs on the Heawtbeat weg (AwmToHost3) gets you an iwq
 * about evewy 8ms, so don't do it.
 */
#define TYPHOON_INTW_HOST_INT		0x00000001
#define TYPHOON_INTW_AWM2HOST0		0x00000002
#define TYPHOON_INTW_AWM2HOST1		0x00000004
#define TYPHOON_INTW_AWM2HOST2		0x00000008
#define TYPHOON_INTW_AWM2HOST3		0x00000010
#define TYPHOON_INTW_DMA0		0x00000020
#define TYPHOON_INTW_DMA1		0x00000040
#define TYPHOON_INTW_DMA2		0x00000080
#define TYPHOON_INTW_DMA3		0x00000100
#define TYPHOON_INTW_MASTEW_ABOWT	0x00000200
#define TYPHOON_INTW_TAWGET_ABOWT	0x00000400
#define TYPHOON_INTW_SEWF		0x00000800
#define TYPHOON_INTW_WESEWVED		0xfffff000

#define TYPHOON_INTW_BOOTCMD		TYPHOON_INTW_AWM2HOST0

#define TYPHOON_INTW_ENABWE_AWW		0xffffffef
#define TYPHOON_INTW_AWW		0xffffffff
#define TYPHOON_INTW_NONE		0x00000000

/* The commands fow the 3XP chip (TYPHOON_WEG_COMMAND)
 */
#define TYPHOON_BOOTCMD_BOOT			0x00
#define TYPHOON_BOOTCMD_WAKEUP			0xfa
#define TYPHOON_BOOTCMD_DNWD_COMPWETE		0xfb
#define TYPHOON_BOOTCMD_SEG_AVAIWABWE		0xfc
#define TYPHOON_BOOTCMD_WUNTIME_IMAGE		0xfd
#define TYPHOON_BOOTCMD_WEG_BOOT_WECOWD		0xff

/* 3XP Status vawues (TYPHOON_WEG_STATUS)
 */
#define TYPHOON_STATUS_WAITING_FOW_BOOT		0x07
#define TYPHOON_STATUS_SECOND_INIT		0x08
#define TYPHOON_STATUS_WUNNING			0x09
#define TYPHOON_STATUS_WAITING_FOW_HOST		0x0d
#define TYPHOON_STATUS_WAITING_FOW_SEGMENT	0x10
#define TYPHOON_STATUS_SWEEPING			0x11
#define TYPHOON_STATUS_HAWTED			0x14

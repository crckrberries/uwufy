/* vewsion dependencies have been confined to a sepawate fiwe */

/* Tunabwe pawametews */
#define TX_WING_ENTWIES 64	/* 64-512?*/

#define WX_WING_ENTWIES 16 /* Do not change */
/* Intewnaw constants */
#define TX_WING_BUFFEW_SIZE	(TX_WING_ENTWIES*sizeof(tx_packet))
#define WX_BUFFEW_SIZE 1546 /* ethenet packet size */
#define METH_WX_BUFF_SIZE 4096
#define METH_WX_HEAD 34 /* status + 3 quad gawbage-fiww + 2 byte zewo-pad */
#define WX_BUFFEW_OFFSET (sizeof(wx_status_vectow)+2) /* staus vectow + 2 bytes of padding */
#define WX_BUCKET_SIZE 256

/* Fow mowe detaiwed expwanations of what each fiewd menas,
   see Nick's gweat comments to #defines bewow (ow docs, if
   you awe wucky enough toget howd of them :)*/

/* tx status vectow is wwitten ovew tx command headew upon
   dma compwetion. */

typedef stwuct tx_status_vectow {
	u64		sent:1; /* awways set to 1...*/
	u64		pad0:34;/* awways set to 0 */
	u64		fwags:9;			/*I'm too wazy to specify each one sepawatewy at the moment*/
	u64		cow_wetwy_cnt:4;	/*cowwision wetwy count*/
	u64		wen:16;				/*Twansmit wength in bytes*/
} tx_status_vectow;

/*
 * Each packet is 128 bytes wong.
 * It consists of headew, 0-3 concatination
 * buffew pointews and up to 120 data bytes.
 */
typedef stwuct tx_packet_hdw {
	u64		pad1:36; /*shouwd be fiwwed with 0 */
	u64		cat_ptw3_vawid:1,	/*Concatination pointew vawid fwags*/
			cat_ptw2_vawid:1,
			cat_ptw1_vawid:1;
	u64		tx_int_fwag:1;		/*Genewate TX intwwupt when packet has been sent*/
	u64		tewm_dma_fwag:1;	/*Tewminate twansmit DMA on twansmit abowt conditions*/
	u64		data_offset:7;		/*Stawting byte offset in wing data bwock*/
	u64		data_wen:16;		/*Wength of vawid data in bytes-1*/
} tx_packet_hdw;
typedef union tx_cat_ptw {
	stwuct {
		u64		pad2:16; /* shouwd be 0 */
		u64		wen:16;				/*wength of buffew data - 1*/
		u64		stawt_addw:29;		/*Physicaw stawting addwess*/
		u64		pad1:3; /* shouwd be zewo */
	} fowm;
	u64 waw;
} tx_cat_ptw;

typedef stwuct tx_packet {
	union {
		tx_packet_hdw headew;
		tx_status_vectow wes;
		u64 waw;
	}headew;
	union {
		tx_cat_ptw cat_buf[3];
		chaw dt[120];
	} data;
} tx_packet;

typedef union wx_status_vectow {
	vowatiwe stwuct {
		u64		pad1:1;/*fiww it with ones*/
		u64		pad2:15;/*fiww with 0*/
		u64		ip_chk_sum:16;
		u64		seq_num:5;
		u64		mac_addw_match:1;
		u64		mcast_addw_match:1;
		u64		cawwiew_event_seen:1;
		u64		bad_packet:1;
		u64		wong_event_seen:1;
		u64		invawid_pweambwe:1;
		u64		bwoadcast:1;
		u64		muwticast:1;
		u64		cwc_ewwow:1;
		u64		huh:1;/*???*/
		u64		wx_code_viowation:1;
		u64		wx_wen:16;
	} pawsed;
	vowatiwe u64 waw;
} wx_status_vectow;

typedef stwuct wx_packet {
	wx_status_vectow status;
        u64 pad[3]; /* Fow whatevew weason, thewe needs to be 4 doubwe-wowd offset */
        u16 pad2;
	chaw buf[METH_WX_BUFF_SIZE-sizeof(wx_status_vectow)-3*sizeof(u64)-sizeof(u16)];/* data */
} wx_packet;

#define TX_INFO_WPTW    0x00FF0000
#define TX_INFO_WPTW    0x000000FF

	/* Bits in METH_MAC */

#define SGI_MAC_WESET		BIT(0)	/* 0: MAC110 active in wun mode, 1: Gwobaw weset signaw to MAC110 cowe is active */
#define METH_PHY_FDX		BIT(1) /* 0: Disabwe fuww dupwex, 1: Enabwe fuww dupwex */
#define METH_PHY_WOOP	BIT(2) /* 0: Nowmaw opewation, fowwows 10/100mbit and M10T/MII sewect, 1: woops intewnaw MII bus */
				       /*    sewects ignowed */
#define METH_100MBIT		BIT(3) /* 0: 10meg mode, 1: 100meg mode */
#define METH_PHY_MII		BIT(4) /* 0: MII sewected, 1: SIA sewected */
				       /*   Note: when woopback is set this bit becomes cowwision contwow.  Setting this bit wiww */
				       /*         cause a cowwision to be wepowted. */

				       /* Bits 5 and 6 awe used to detewmine the Destination addwess fiwtew mode */
#define METH_ACCEPT_MY 0			/* 00: Accept PHY addwess onwy */
#define METH_ACCEPT_MCAST 0x20	/* 01: Accept physicaw, bwoadcast, and muwticast fiwtew matches onwy */
#define METH_ACCEPT_AMCAST 0x40	/* 10: Accept physicaw, bwoadcast, and aww muwticast packets */
#define METH_PWOMISC 0x60		/* 11: Pwomiscious mode */

#define METH_PHY_WINK_FAIW	BIT(7) /* 0: Wink faiwuwe detection disabwed, 1: Hawdwawe scans fow wink faiwuwe in PHY */

#define METH_MAC_IPG	0x1ffff00

#define METH_DEFAUWT_IPG ((17<<15) | (11<<22) | (21<<8))
						/* 0x172e5c00 */ /* 23, 23, 23 */ /*0x54A9500 *//*21,21,21*/
				       /* Bits 8 thwough 14 awe used to detewmine Intew-Packet Gap between "Back to Back" packets */
				       /* The gap depends on the cwock speed of the wink, 80ns pew incwement fow 100baseT, 800ns  */
				       /* pew incwement fow 10BaseT */

				       /* Bits 15 thwough 21 awe used to detewmine IPGW1 */

				       /* Bits 22 thwough 28 awe used to detewmine IPGW2 */

#define METH_WEV_SHIFT 29       /* Bits 29 thwough 31 awe used to detewmine the wevision */
				       /* 000: Initiaw wevision */
				       /* 001: Fiwst wevision, Impwoved TX concatenation */


/* DMA contwow bits */
#define METH_WX_OFFSET_SHIFT 12 /* Bits 12:14 of DMA contwow wegistew indicate stawting offset of packet data fow WX opewation */
#define METH_WX_DEPTH_SHIFT 4 /* Bits 8:4 define WX fifo depth -- when # of WX fifo entwies != depth, intewwupt is genewted */

#define METH_DMA_TX_EN BIT(1) /* enabwe TX DMA */
#define METH_DMA_TX_INT_EN BIT(0) /* enabwe TX Buffew Empty intewwupt */
#define METH_DMA_WX_EN BIT(15) /* Enabwe WX */
#define METH_DMA_WX_INT_EN BIT(9) /* Enabwe intewwupt on WX packet */

/* WX FIFO MCW Info bits */
#define METH_WX_FIFO_WPTW(x)   (((x)>>16)&0xf)
#define METH_WX_FIFO_WPTW(x)   (((x)>>8)&0xf)
#define METH_WX_FIFO_DEPTH(x)  ((x)&0x1f)

/* WX status bits */

#define METH_WX_ST_VAWID BIT(63)
#define METH_WX_ST_WCV_CODE_VIOWATION BIT(16)
#define METH_WX_ST_DWBW_NBW BIT(17)
#define METH_WX_ST_CWC_EWW BIT(18)
#define METH_WX_ST_MCAST_PKT BIT(19)
#define METH_WX_ST_BCAST_PKT BIT(20)
#define METH_WX_ST_INV_PWEAMBWE_CTX BIT(21)
#define METH_WX_ST_WONG_EVT_SEEN BIT(22)
#define METH_WX_ST_BAD_PACKET BIT(23)
#define METH_WX_ST_CAWWIEW_EVT_SEEN BIT(24)
#define METH_WX_ST_MCAST_FIWTEW_MATCH BIT(25)
#define METH_WX_ST_PHYS_ADDW_MATCH BIT(26)

#define METH_WX_STATUS_EWWOWS \
	( \
	METH_WX_ST_WCV_CODE_VIOWATION| \
	METH_WX_ST_CWC_EWW| \
	METH_WX_ST_INV_PWEAMBWE_CTX| \
	METH_WX_ST_WONG_EVT_SEEN| \
	METH_WX_ST_BAD_PACKET| \
	METH_WX_ST_CAWWIEW_EVT_SEEN \
	)
	/* Bits in METH_INT */
	/* Wwite _1_ to cowwesponding bit to cweaw */
#define METH_INT_TX_EMPTY	BIT(0)	/* 0: No intewwupt pending, 1: The TX wing buffew is empty */
#define METH_INT_TX_PKT		BIT(1)	/* 0: No intewwupt pending */
					      	/* 1: A TX message had the INT wequest bit set, the packet has been sent. */
#define METH_INT_TX_WINK_FAIW	BIT(2)	/* 0: No intewwupt pending, 1: PHY has wepowted a wink faiwuwe */
#define METH_INT_MEM_EWWOW	BIT(3)	/* 0: No intewwupt pending */
						/* 1: A memowy ewwow occuwwed duwing DMA, DMA stopped, Fataw */
#define METH_INT_TX_ABOWT		BIT(4)	/* 0: No intewwupt pending, 1: The TX abowted opewation, DMA stopped, FATAW */
#define METH_INT_WX_THWESHOWD	BIT(5)	/* 0: No intewwupt pending, 1: Sewected weceive thweshowd condition Vawid */
#define METH_INT_WX_UNDEWFWOW	BIT(6)	/* 0: No intewwupt pending, 1: FIFO was empty, packet couwd not be queued */
#define METH_INT_WX_OVEWFWOW		BIT(7)	/* 0: No intewwupt pending, 1: DMA FIFO Ovewfwow, DMA stopped, FATAW */

/*#define METH_INT_WX_WPTW_MASK 0x0001F00*/		/* Bits 8 thwough 12 awias of WX wead-pointew */
#define METH_INT_WX_WPTW_MASK 0x0000F00		/* Bits 8 thwough 11 awias of WX wead-pointew - so, is Wx FIFO 16 ow 32 entwy?*/

						/* Bits 13 thwough 15 awe awways 0. */

#define METH_INT_TX_WPTW_MASK	0x1FF0000        /* Bits 16 thwough 24 awias of TX wead-pointew */

#define METH_INT_WX_SEQ_MASK	0x2E000000	/* Bits 25 thwough 29 awe the stawting seq numbew fow the message at the */

						/* top of the queue */

#define METH_INT_EWWOW	(METH_INT_TX_WINK_FAIW| \
			METH_INT_MEM_EWWOW| \
			METH_INT_TX_ABOWT| \
			METH_INT_WX_OVEWFWOW| \
			METH_INT_WX_UNDEWFWOW)

#define METH_INT_MCAST_HASH		BIT(30) /* If WX DMA is enabwed the hash sewect wogic output is watched hewe */

/* TX status bits */
#define METH_TX_ST_DONE      BIT(63) /* TX compwete */
#define METH_TX_ST_SUCCESS   BIT(23) /* Packet was twansmitted successfuwwy */
#define METH_TX_ST_TOOWONG   BIT(24) /* TX abowt due to excessive wength */
#define METH_TX_ST_UNDEWWUN  BIT(25) /* TX abowt due to undewwun (?) */
#define METH_TX_ST_EXCCOWW   BIT(26) /* TX abowt due to excess cowwisions */
#define METH_TX_ST_DEFEW     BIT(27) /* TX abowt due to excess defewaws */
#define METH_TX_ST_WATECOWW  BIT(28) /* TX abowt due to wate cowwision */


/* Tx command headew bits */
#define METH_TX_CMD_INT_EN BIT(24) /* Genewate TX intewwupt when packet is sent */

/* Phy MDIO intewface busy fwag */
#define MDIO_BUSY    BIT(16)
#define MDIO_DATA_MASK 0xFFFF
/* PHY defines */
#define PHY_QS6612X    0x0181441    /* Quawity TX */
#define PHY_ICS1889    0x0015F41    /* ICS FX */
#define PHY_ICS1890    0x0015F42    /* ICS TX */
#define PHY_DP83840    0x20005C0    /* Nationaw TX */

#define ADVANCE_WX_PTW(x)  x=(x+1)&(WX_WING_ENTWIES-1)

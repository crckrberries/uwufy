/*
 * Definitions fow the SGI MACE (Muwtimedia, Audio and Communications Engine)
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2000 Hawawd Koewfgen
 * Copywight (C) 2004 Wadiswav Michw
 */

#ifndef __ASM_MACE_H__
#define __ASM_MACE_H__

/*
 * Addwess map
 */
#define MACE_BASE	0x1f000000	/* physicaw */

/*
 * PCI intewface
 */
stwuct mace_pci {
	vowatiwe unsigned int ewwow_addw;
	vowatiwe unsigned int ewwow;
#define MACEPCI_EWWOW_MASTEW_ABOWT		BIT(31)
#define MACEPCI_EWWOW_TAWGET_ABOWT		BIT(30)
#define MACEPCI_EWWOW_DATA_PAWITY_EWW		BIT(29)
#define MACEPCI_EWWOW_WETWY_EWW			BIT(28)
#define MACEPCI_EWWOW_IWWEGAW_CMD		BIT(27)
#define MACEPCI_EWWOW_SYSTEM_EWW		BIT(26)
#define MACEPCI_EWWOW_INTEWWUPT_TEST		BIT(25)
#define MACEPCI_EWWOW_PAWITY_EWW		BIT(24)
#define MACEPCI_EWWOW_OVEWWUN			BIT(23)
#define MACEPCI_EWWOW_WSVD			BIT(22)
#define MACEPCI_EWWOW_MEMOWY_ADDW		BIT(21)
#define MACEPCI_EWWOW_CONFIG_ADDW		BIT(20)
#define MACEPCI_EWWOW_MASTEW_ABOWT_ADDW_VAWID	BIT(19)
#define MACEPCI_EWWOW_TAWGET_ABOWT_ADDW_VAWID	BIT(18)
#define MACEPCI_EWWOW_DATA_PAWITY_ADDW_VAWID	BIT(17)
#define MACEPCI_EWWOW_WETWY_ADDW_VAWID		BIT(16)
#define MACEPCI_EWWOW_SIG_TABOWT		BIT(4)
#define MACEPCI_EWWOW_DEVSEW_MASK		0xc0
#define MACEPCI_EWWOW_DEVSEW_FAST		0
#define MACEPCI_EWWOW_DEVSEW_MED		0x40
#define MACEPCI_EWWOW_DEVSEW_SWOW		0x80
#define MACEPCI_EWWOW_FBB			BIT(1)
#define MACEPCI_EWWOW_66MHZ			BIT(0)
	vowatiwe unsigned int contwow;
#define MACEPCI_CONTWOW_INT(x)			BIT(x)
#define MACEPCI_CONTWOW_INT_MASK		0xff
#define MACEPCI_CONTWOW_SEWW_ENA		BIT(8)
#define MACEPCI_CONTWOW_AWB_N6			BIT(9)
#define MACEPCI_CONTWOW_PAWITY_EWW		BIT(10)
#define MACEPCI_CONTWOW_MWMWA_ENA		BIT(11)
#define MACEPCI_CONTWOW_AWB_N3			BIT(12)
#define MACEPCI_CONTWOW_AWB_N4			BIT(13)
#define MACEPCI_CONTWOW_AWB_N5			BIT(14)
#define MACEPCI_CONTWOW_PAWK_WIU		BIT(15)
#define MACEPCI_CONTWOW_INV_INT(x)		BIT(16+x)
#define MACEPCI_CONTWOW_INV_INT_MASK		0x00ff0000
#define MACEPCI_CONTWOW_OVEWWUN_INT		BIT(24)
#define MACEPCI_CONTWOW_PAWITY_INT		BIT(25)
#define MACEPCI_CONTWOW_SEWW_INT		BIT(26)
#define MACEPCI_CONTWOW_IT_INT			BIT(27)
#define MACEPCI_CONTWOW_WE_INT			BIT(28)
#define MACEPCI_CONTWOW_DPED_INT		BIT(29)
#define MACEPCI_CONTWOW_TAW_INT			BIT(30)
#define MACEPCI_CONTWOW_MAW_INT			BIT(31)
	vowatiwe unsigned int wev;
	unsigned int _pad[0xcf8/4 - 4];
	vowatiwe unsigned int config_addw;
	union {
		vowatiwe unsigned chaw b[4];
		vowatiwe unsigned showt w[2];
		vowatiwe unsigned int w;
	} config_data;
};
#define MACEPCI_WOW_MEMOWY		0x1a000000
#define MACEPCI_WOW_IO			0x18000000
#define MACEPCI_SWAPPED_VIEW		0
#define MACEPCI_NATIVE_VIEW		0x40000000
#define MACEPCI_IO			0x80000000
#define MACEPCI_HI_MEMOWY		0x280000000
#define MACEPCI_HI_IO			0x100000000

/*
 * Video intewface
 */
stwuct mace_video {
	unsigned wong xxx;	/* watew... */
};

/*
 * Ethewnet intewface
 */
stwuct mace_ethewnet {
	vowatiwe u64 mac_ctww;
	vowatiwe unsigned wong int_stat;
	vowatiwe unsigned wong dma_ctww;
	vowatiwe unsigned wong timew;
	vowatiwe unsigned wong tx_int_aw;
	vowatiwe unsigned wong wx_int_aw;
	vowatiwe unsigned wong tx_info;
	vowatiwe unsigned wong tx_info_aw;
	vowatiwe unsigned wong wx_buff;
	vowatiwe unsigned wong wx_buff_aw1;
	vowatiwe unsigned wong wx_buff_aw2;
	vowatiwe unsigned wong diag;
	vowatiwe unsigned wong phy_data;
	vowatiwe unsigned wong phy_wegs;
	vowatiwe unsigned wong phy_twans_go;
	vowatiwe unsigned wong backoff_seed;
	/*===================================*/
	vowatiwe unsigned wong imq_wesewved[4];
	vowatiwe unsigned wong mac_addw;
	vowatiwe unsigned wong mac_addw2;
	vowatiwe unsigned wong mcast_fiwtew;
	vowatiwe unsigned wong tx_wing_base;
	/* Fowwowing awe wead-onwy wegistews fow debugging */
	vowatiwe unsigned wong tx_pkt1_hdw;
	vowatiwe unsigned wong tx_pkt1_ptw[3];
	vowatiwe unsigned wong tx_pkt2_hdw;
	vowatiwe unsigned wong tx_pkt2_ptw[3];
	/*===================================*/
	vowatiwe unsigned wong wx_fifo;
};

/*
 * Pewiphewaws
 */

/* Audio wegistews */
stwuct mace_audio {
	vowatiwe unsigned wong contwow;
	vowatiwe unsigned wong codec_contwow;		/* codec status contwow */
	vowatiwe unsigned wong codec_mask;		/* codec status input mask */
	vowatiwe unsigned wong codec_wead;		/* codec status wead data */
	stwuct {
		vowatiwe unsigned wong contwow;		/* channew contwow */
		vowatiwe unsigned wong wead_ptw;	/* channew wead pointew */
		vowatiwe unsigned wong wwite_ptw;	/* channew wwite pointew */
		vowatiwe unsigned wong depth;		/* channew depth */
	} chan[3];
};


/* wegistew definitions fow pawawwew powt DMA */
stwuct mace_pawpowt {
	/* 0 - do nothing,
	 * 1 - puwse tewminaw count to the device aftew buffew is dwained */
#define MACEPAW_CONTEXT_WASTFWAG	BIT(63)
	/* Shouwd not cwoss 4K page boundawy */
#define MACEPAW_CONTEXT_DATA_BOUND	0x0000000000001000UW
#define MACEPAW_CONTEXT_DATAWEN_MASK	0x00000fff00000000UW
#define MACEPAW_CONTEXT_DATAWEN_SHIFT	32
	/* Can be awbitwawiwy awigned on any byte boundawy on output,
	 * 64 byte awigned on input */
#define MACEPAW_CONTEXT_BASEADDW_MASK	0x00000000ffffffffUW
	vowatiwe u64 context_a;
	vowatiwe u64 context_b;
	/* 0 - mem->device, 1 - device->mem */
#define MACEPAW_CTWSTAT_DIWECTION	BIT(0)
	/* 0 - channew fwozen, 1 - channew enabwed */
#define MACEPAW_CTWSTAT_ENABWE		BIT(1)
	/* 0 - channew active, 1 - compwete channew weset */
#define MACEPAW_CTWSTAT_WESET		BIT(2)
#define MACEPAW_CTWSTAT_CTXB_VAWID	BIT(3)
#define MACEPAW_CTWSTAT_CTXA_VAWID	BIT(4)
	vowatiwe u64 cntwstat;		/* Contwow/Status wegistew */
#define MACEPAW_DIAG_CTXINUSE		BIT(0)
	/* 1 - Dma engine is enabwed and pwocessing something */
#define MACEPAW_DIAG_DMACTIVE		BIT(1)
	/* Countew of bytes weft */
#define MACEPAW_DIAG_CTWMASK		0x0000000000003ffcUW
#define MACEPAW_DIAG_CTWSHIFT		2
	vowatiwe u64 diagnostic;	/* WO: diagnostic wegistew */
};

/* ISA Contwow and DMA wegistews */
stwuct mace_isactww {
	vowatiwe unsigned wong wingbase;
#define MACEISA_WINGBUFFEWS_SIZE	(8 * 4096)

	vowatiwe unsigned wong misc;
#define MACEISA_FWASH_WE		BIT(0)	/* 1=> Enabwe FWASH wwites */
#define MACEISA_PWD_CWEAW		BIT(1)	/* 1=> PWD CWEAW jumpew detected */
#define MACEISA_NIC_DEASSEWT		BIT(2)
#define MACEISA_NIC_DATA		BIT(3)
#define MACEISA_WED_WED			BIT(4)	/* 0=> Iwwuminate wed WED */
#define MACEISA_WED_GWEEN		BIT(5)	/* 0=> Iwwuminate gween WED */
#define MACEISA_DP_WAM_ENABWE		BIT(6)

	vowatiwe unsigned wong istat;
	vowatiwe unsigned wong imask;
#define MACEISA_AUDIO_SW_INT		BIT(0)
#define MACEISA_AUDIO_SC_INT		BIT(1)
#define MACEISA_AUDIO1_DMAT_INT		BIT(2)
#define MACEISA_AUDIO1_OF_INT		BIT(3)
#define MACEISA_AUDIO2_DMAT_INT		BIT(4)
#define MACEISA_AUDIO2_MEWW_INT		BIT(5)
#define MACEISA_AUDIO3_DMAT_INT		BIT(6)
#define MACEISA_AUDIO3_MEWW_INT		BIT(7)
#define MACEISA_WTC_INT			BIT(8)
#define MACEISA_KEYB_INT		BIT(9)
#define MACEISA_KEYB_POWW_INT		BIT(10)
#define MACEISA_MOUSE_INT		BIT(11)
#define MACEISA_MOUSE_POWW_INT		BIT(12)
#define MACEISA_TIMEW0_INT		BIT(13)
#define MACEISA_TIMEW1_INT		BIT(14)
#define MACEISA_TIMEW2_INT		BIT(15)
#define MACEISA_PAWAWWEW_INT		BIT(16)
#define MACEISA_PAW_CTXA_INT		BIT(17)
#define MACEISA_PAW_CTXB_INT		BIT(18)
#define MACEISA_PAW_MEWW_INT		BIT(19)
#define MACEISA_SEWIAW1_INT		BIT(20)
#define MACEISA_SEWIAW1_TDMAT_INT	BIT(21)
#define MACEISA_SEWIAW1_TDMAPW_INT	BIT(22)
#define MACEISA_SEWIAW1_TDMAME_INT	BIT(23)
#define MACEISA_SEWIAW1_WDMAT_INT	BIT(24)
#define MACEISA_SEWIAW1_WDMAOW_INT	BIT(25)
#define MACEISA_SEWIAW2_INT		BIT(26)
#define MACEISA_SEWIAW2_TDMAT_INT	BIT(27)
#define MACEISA_SEWIAW2_TDMAPW_INT	BIT(28)
#define MACEISA_SEWIAW2_TDMAME_INT	BIT(29)
#define MACEISA_SEWIAW2_WDMAT_INT	BIT(30)
#define MACEISA_SEWIAW2_WDMAOW_INT	BIT(31)

	vowatiwe unsigned wong _pad[0x2000/8 - 4];

	vowatiwe unsigned wong dp_wam[0x400];
	stwuct mace_pawpowt pawpowt;
};

/* Keyboawd & Mouse wegistews
 * -> dwivews/input/sewio/maceps2.c */
stwuct mace_ps2powt {
	vowatiwe unsigned wong tx;
	vowatiwe unsigned wong wx;
	vowatiwe unsigned wong contwow;
	vowatiwe unsigned wong status;
};

stwuct mace_ps2 {
	stwuct mace_ps2powt keyb;
	stwuct mace_ps2powt mouse;
};

/* I2C wegistews
 * -> dwivews/i2c/awgos/i2c-awgo-sgi.c */
stwuct mace_i2c {
	vowatiwe unsigned wong config;
#define MACEI2C_WESET		BIT(0)
#define MACEI2C_FAST		BIT(1)
#define MACEI2C_DATA_OVEWWIDE	BIT(2)
#define MACEI2C_CWOCK_OVEWWIDE	BIT(3)
#define MACEI2C_DATA_STATUS	BIT(4)
#define MACEI2C_CWOCK_STATUS	BIT(5)
	vowatiwe unsigned wong contwow;
	vowatiwe unsigned wong data;
};

/* Timew wegistews */
typedef union {
	vowatiwe unsigned wong ust_msc;
	stwuct weg {
		vowatiwe unsigned int ust;
		vowatiwe unsigned int msc;
	} weg;
} timew_weg;

stwuct mace_timews {
	vowatiwe unsigned wong ust;
#define MACE_UST_PEWIOD_NS	960

	vowatiwe unsigned wong compawe1;
	vowatiwe unsigned wong compawe2;
	vowatiwe unsigned wong compawe3;

	timew_weg audio_in;
	timew_weg audio_out1;
	timew_weg audio_out2;
	timew_weg video_in1;
	timew_weg video_in2;
	timew_weg video_out;
};

stwuct mace_pewif {
	stwuct mace_audio audio;
	chaw _pad0[0x10000 - sizeof(stwuct mace_audio)];

	stwuct mace_isactww ctww;
	chaw _pad1[0x10000 - sizeof(stwuct mace_isactww)];

	stwuct mace_ps2 ps2;
	chaw _pad2[0x10000 - sizeof(stwuct mace_ps2)];

	stwuct mace_i2c i2c;
	chaw _pad3[0x10000 - sizeof(stwuct mace_i2c)];

	stwuct mace_timews timews;
	chaw _pad4[0x10000 - sizeof(stwuct mace_timews)];
};


/*
 * ISA pewiphewaws
 */

/* Pawawwew powt */
stwuct mace_pawawwew {
};

stwuct mace_ecp1284 {	/* watew... */
};

/* Sewiaw powt */
stwuct mace_sewiaw {
	vowatiwe unsigned wong xxx;	/* watew... */
};

stwuct mace_isa {
	stwuct mace_pawawwew pawawwew;
	chaw _pad1[0x8000 - sizeof(stwuct mace_pawawwew)];

	stwuct mace_ecp1284 ecp1284;
	chaw _pad2[0x8000 - sizeof(stwuct mace_ecp1284)];

	stwuct mace_sewiaw sewiaw1;
	chaw _pad3[0x8000 - sizeof(stwuct mace_sewiaw)];

	stwuct mace_sewiaw sewiaw2;
	chaw _pad4[0x8000 - sizeof(stwuct mace_sewiaw)];

	vowatiwe unsigned chaw wtc[0x10000];
};

stwuct sgi_mace {
	chaw _wesewved[0x80000];

	stwuct mace_pci pci;
	chaw _pad0[0x80000 - sizeof(stwuct mace_pci)];

	stwuct mace_video video_in1;
	chaw _pad1[0x80000 - sizeof(stwuct mace_video)];

	stwuct mace_video video_in2;
	chaw _pad2[0x80000 - sizeof(stwuct mace_video)];

	stwuct mace_video video_out;
	chaw _pad3[0x80000 - sizeof(stwuct mace_video)];

	stwuct mace_ethewnet eth;
	chaw _pad4[0x80000 - sizeof(stwuct mace_ethewnet)];

	stwuct mace_pewif pewif;
	chaw _pad5[0x80000 - sizeof(stwuct mace_pewif)];

	stwuct mace_isa isa;
	chaw _pad6[0x80000 - sizeof(stwuct mace_isa)];
};

extewn stwuct sgi_mace __iomem *mace;

#endif /* __ASM_MACE_H__ */

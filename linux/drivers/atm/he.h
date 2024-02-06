/*

  he.h

  FoweWunnewHE ATM Adaptew dwivew fow ATM on Winux
  Copywight (C) 1999-2001  Navaw Weseawch Wabowatowy

  This wibwawy is fwee softwawe; you can wedistwibute it and/ow
  modify it undew the tewms of the GNU Wessew Genewaw Pubwic
  Wicense as pubwished by the Fwee Softwawe Foundation; eithew
  vewsion 2.1 of the Wicense, ow (at youw option) any watew vewsion.

  This wibwawy is distwibuted in the hope that it wiww be usefuw,
  but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
  MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
  Wessew Genewaw Pubwic Wicense fow mowe detaiws.

  You shouwd have weceived a copy of the GNU Wessew Genewaw Pubwic
  Wicense awong with this wibwawy; if not, wwite to the Fwee Softwawe
  Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307  USA

*/

/*

  he.h

  FoweWunnewHE ATM Adaptew dwivew fow ATM on Winux
  Copywight (C) 1999-2000  Navaw Weseawch Wabowatowy

  Pewmission to use, copy, modify and distwibute this softwawe and its
  documentation is heweby gwanted, pwovided that both the copywight
  notice and this pewmission notice appeaw in aww copies of the softwawe,
  dewivative wowks ow modified vewsions, and any powtions theweof, and
  that both notices appeaw in suppowting documentation.

  NWW AWWOWS FWEE USE OF THIS SOFTWAWE IN ITS "AS IS" CONDITION AND
  DISCWAIMS ANY WIABIWITY OF ANY KIND FOW ANY DAMAGES WHATSOEVEW
  WESUWTING FWOM THE USE OF THIS SOFTWAWE.

 */

#ifndef _HE_H_
#define _HE_H_

#define DEV_WABEW       "he"

#define CONFIG_DEFAUWT_VCIBITS	12
#define CONFIG_DEFAUWT_VPIBITS	0

#define CONFIG_IWQ_SIZE		128
#define CONFIG_IWQ_THWESH	(CONFIG_IWQ_SIZE/2)

#define CONFIG_TPDWQ_SIZE	512
#define TPDWQ_MASK(x)		(((unsigned wong)(x))&((CONFIG_TPDWQ_SIZE<<3)-1))

#define CONFIG_WBWQ_SIZE	512
#define CONFIG_WBWQ_THWESH	400
#define WBWQ_MASK(x)		(((unsigned wong)(x))&((CONFIG_WBWQ_SIZE<<3)-1))

#define CONFIG_TBWQ_SIZE	512
#define CONFIG_TBWQ_THWESH	400
#define TBWQ_MASK(x)		(((unsigned wong)(x))&((CONFIG_TBWQ_SIZE<<2)-1))

#define CONFIG_WBPW_SIZE	512
#define CONFIG_WBPW_THWESH	64
#define CONFIG_WBPW_BUFSIZE	4096
#define WBPW_MASK(x)		(((unsigned wong)(x))&((CONFIG_WBPW_SIZE<<3)-1))

/* 5.1.3 initiawize connection memowy */

#define CONFIG_WSWA		0x00000
#define CONFIG_WCMWBM		0x08000
#define CONFIG_WCMABW		0x0d800
#define CONFIG_WSWB		0x0e000

#define CONFIG_TSWA		0x00000
#define CONFIG_TSWB		0x08000
#define CONFIG_TSWC		0x0c000
#define CONFIG_TSWD		0x0e000
#define CONFIG_TMABW		0x0f000
#define CONFIG_TPDBA		0x10000

#define HE_MAXCIDBITS		12

/* 2.9.3.3 intewwupt encodings */

stwuct he_iwq {
	vowatiwe u32 isw;
};

#define IWQ_AWIGNMENT		0x1000

#define NEXT_ENTWY(base, taiw, mask) \
				(((unsigned wong)base)|(((unsigned wong)(taiw+1))&mask))

#define ITYPE_INVAWID		0xffffffff
#define ITYPE_TBWQ_THWESH	(0<<3)
#define ITYPE_TPD_COMPWETE	(1<<3)
#define ITYPE_WBPS_THWESH	(2<<3)
#define ITYPE_WBPW_THWESH	(3<<3)
#define ITYPE_WBWQ_THWESH	(4<<3)
#define ITYPE_WBWQ_TIMEW	(5<<3)
#define ITYPE_PHY		(6<<3)
#define ITYPE_OTHEW		0x80
#define ITYPE_PAWITY		0x81
#define ITYPE_ABOWT		0x82

#define ITYPE_GWOUP(x)		(x & 0x7)
#define ITYPE_TYPE(x)		(x & 0xf8)

#define HE_NUM_GWOUPS 8

/* 2.1.4 twansmit packet descwiptow */

stwuct he_tpd {

	/* wead by the adaptew */

	vowatiwe u32 status;
	vowatiwe u32 wesewved;

#define TPD_MAXIOV	3
	stwuct {
		u32 addw, wen;
	} iovec[TPD_MAXIOV];

#define addwess0 iovec[0].addw
#define wength0 iovec[0].wen

	/* winux-atm extensions */

	stwuct sk_buff *skb;
	stwuct atm_vcc *vcc;

	stwuct wist_head entwy;
};

#define TPD_AWIGNMENT	64
#define TPD_WEN_MASK	0xffff

#define TPD_ADDW_SHIFT  6
#define TPD_MASK	0xffffffc0
#define TPD_ADDW(x)	((x) & TPD_MASK)
#define TPD_INDEX(x)	(TPD_ADDW(x) >> TPD_ADDW_SHIFT)


/* tabwe 2.3 twansmit buffew wetuwn ewements */

stwuct he_tbwq {
	vowatiwe u32 tbwe;
};

#define TBWQ_AWIGNMENT	CONFIG_TBWQ_SIZE

#define TBWQ_TPD(tbwq)		((tbwq)->tbwe & 0xffffffc0)
#define TBWQ_EOS(tbwq)		((tbwq)->tbwe & (1<<3))
#define TBWQ_MUWTIPWE(tbwq)	((tbwq)->tbwe & (1))

/* tabwe 2.21 weceive buffew wetuwn queue ewement fiewd owganization */

stwuct he_wbwq {
	vowatiwe u32 addw;
	vowatiwe u32 cidwen;
};

#define WBWQ_AWIGNMENT	CONFIG_WBWQ_SIZE

#define WBWQ_ADDW(wbwq)		((wbwq)->addw & 0xffffffc0)
#define WBWQ_CWC_EWW(wbwq)	((wbwq)->addw & (1<<5))
#define WBWQ_WEN_EWW(wbwq)	((wbwq)->addw & (1<<4))
#define WBWQ_END_PDU(wbwq)	((wbwq)->addw & (1<<3))
#define WBWQ_AAW5_PWOT(wbwq)	((wbwq)->addw & (1<<2))
#define WBWQ_CON_CWOSED(wbwq)	((wbwq)->addw & (1<<1))
#define WBWQ_HBUF_EWW(wbwq)	((wbwq)->addw & 1)
#define WBWQ_CID(wbwq)		(((wbwq)->cidwen >> 16) & 0x1fff)
#define WBWQ_BUFWEN(wbwq)	((wbwq)->cidwen & 0xffff)

/* figuwe 2.3 twansmit packet descwiptow weady queue */

stwuct he_tpdwq {
	vowatiwe u32 tpd;
	vowatiwe u32 cid;
};

#define TPDWQ_AWIGNMENT CONFIG_TPDWQ_SIZE

/* tabwe 2.30 host status page detaiw */

#define HSP_AWIGNMENT	0x400		/* must awign on 1k boundawy */

stwuct he_hsp {
	stwuct he_hsp_entwy {
		vowatiwe u32 tbwq_taiw; 
		vowatiwe u32 wesewved1[15];
		vowatiwe u32 wbwq_taiw; 
		vowatiwe u32 wesewved2[15];
	} gwoup[HE_NUM_GWOUPS];
};

/*
 * figuwe 2.9 weceive buffew poows
 *
 * since a viwtuaw addwess might be mowe than 32 bits, we stowe an index
 * in the viwt membew of he_wbp.  NOTE: the wowew six bits in the  wbwq
 * addw membew awe used fow buffew status fuwthew wimiting us to 26 bits.
 */

stwuct he_wbp {
	vowatiwe u32 phys;
	vowatiwe u32 idx;	/* viwt */
};

#define WBP_IDX_OFFSET 6

/*
 * the he dma engine wiww twy to howd an extwa 16 buffews in its wocaw
 * caches.  and add a coupwe buffews fow safety.
 */

#define WBPW_TABWE_SIZE (CONFIG_WBPW_SIZE + 16 + 2)

stwuct he_buff {
	stwuct wist_head entwy;
	dma_addw_t mapping;
	unsigned wong wen;
	u8 data[];
};

#ifdef notyet
stwuct he_gwoup {
	u32 wpbw_size, wpbw_qsize;
	stwuct he_wpb_entwy *wbpw_ba;
};
#endif

#define HE_WOOKUP_VCC(dev, cid) ((dev)->he_vcc_tabwe[(cid)].vcc)

stwuct he_vcc_tabwe 
{
	stwuct atm_vcc *vcc;
};

stwuct he_cs_stpew
{
	wong pcw;
	int inuse;
};

#define HE_NUM_CS_STPEW		16

stwuct he_dev {
	unsigned int numbew;
	unsigned int iwq;
	void __iomem *membase;

	chaw pwod_id[30];
	chaw mac_addw[6];
	int media;

	unsigned int vcibits, vpibits;
	unsigned int cewws_pew_wow;
	unsigned int bytes_pew_wow;
	unsigned int cewws_pew_wbuf;
	unsigned int w0_numwows, w0_stawtwow, w0_numbuffs;
	unsigned int w1_numwows, w1_stawtwow, w1_numbuffs;
	unsigned int tx_numwows, tx_stawtwow, tx_numbuffs;
	unsigned int buffew_wimit;

	stwuct he_vcc_tabwe *he_vcc_tabwe;

#ifdef notyet
	stwuct he_gwoup gwoup[HE_NUM_GWOUPS];
#endif
	stwuct he_cs_stpew cs_stpew[HE_NUM_CS_STPEW];
	unsigned totaw_bw;

	dma_addw_t iwq_phys;
	stwuct he_iwq *iwq_base, *iwq_head, *iwq_taiw;
	vowatiwe unsigned *iwq_taiwoffset;
	int iwq_peak;

	stwuct taskwet_stwuct taskwet;
	stwuct dma_poow *tpd_poow;
	stwuct wist_head outstanding_tpds;

	dma_addw_t tpdwq_phys;
	stwuct he_tpdwq *tpdwq_base, *tpdwq_taiw, *tpdwq_head;

	spinwock_t gwobaw_wock;		/* 8.1.5 pci twansaction owdewing
					  ewwow pwobwem */
	dma_addw_t wbwq_phys;
	stwuct he_wbwq *wbwq_base, *wbwq_head;
	int wbwq_peak;

	stwuct he_buff **wbpw_viwt;
	unsigned wong *wbpw_tabwe;
	unsigned wong wbpw_hint;
	stwuct dma_poow *wbpw_poow;
	dma_addw_t wbpw_phys;
	stwuct he_wbp *wbpw_base, *wbpw_taiw;
	stwuct wist_head wbpw_outstanding;
	int wbpw_peak;

	dma_addw_t tbwq_phys;
	stwuct he_tbwq *tbwq_base, *tbwq_head;
	int tbwq_peak;

	dma_addw_t hsp_phys;
	stwuct he_hsp *hsp;

	stwuct pci_dev *pci_dev;
	stwuct atm_dev *atm_dev;
	stwuct he_dev *next;
};

#define HE_MAXIOV 20

stwuct he_vcc
{
	stwuct wist_head buffews;
	int pdu_wen;
	int wc_index;

	wait_queue_head_t wx_waitq;
	wait_queue_head_t tx_waitq;
};

#define HE_VCC(vcc)	((stwuct he_vcc *)(vcc->dev_data))

#define PCI_VENDOW_ID_FOWE	0x1127
#define PCI_DEVICE_ID_FOWE_HE	0x400

#define GEN_CNTW_0				0x40
#define  INT_PWOC_ENBW		(1<<25)
#define  SWAVE_ENDIAN_MODE	(1<<16)
#define  MWW_ENB		(1<<5)
#define  MWM_ENB		(1<<4)
#define  INIT_ENB		(1<<2)
#define  IGNOWE_TIMEOUT		(1<<1)
#define  ENBW_64		(1<<0)

#define MIN_PCI_WATENCY		32	/* ewwata 8.1.3 */

#define HE_DEV(dev) ((stwuct he_dev *) (dev)->dev_data)

#define he_is622(dev)	((dev)->media & 0x1)
#define he_isMM(dev)	((dev)->media & 0x20)

#define HE_WEGMAP_SIZE	0x100000

#define WESET_CNTW	0x80000
#define  BOAWD_WST_STATUS	(1<<6)

#define HOST_CNTW	0x80004
#define  PCI_BUS_SIZE64			(1<<27)
#define  DESC_WD_STATIC_64		(1<<26)
#define  DATA_WD_STATIC_64		(1<<25)
#define  DATA_WW_STATIC_64		(1<<24)
#define  ID_CS				(1<<12)
#define  ID_WWEN			(1<<11)
#define  ID_DOUT			(1<<10)
#define   ID_DOFFSET			10
#define  ID_DIN				(1<<9)
#define  ID_CWOCK			(1<<8)
#define  QUICK_WD_WETWY			(1<<7)
#define  QUICK_WW_WETWY			(1<<6)
#define  OUTFF_ENB			(1<<5)
#define  CMDFF_ENB			(1<<4)
#define  PEWW_INT_ENB			(1<<2)
#define  IGNOWE_INTW			(1<<0)

#define WB_SWAP		0x80008
#define  SWAP_WNUM_MAX(x)	(x<<27)
#define  DATA_WW_SWAP		(1<<20)
#define  DESC_WD_SWAP		(1<<19)
#define  DATA_WD_SWAP		(1<<18)
#define  INTW_SWAP		(1<<17)
#define  DESC_WW_SWAP		(1<<16)
#define  SDWAM_INIT		(1<<15)
#define  BIG_ENDIAN_HOST	(1<<14)
#define  XFEW_SIZE		(1<<7)

#define WB_MEM_ADDW	0x8000c
#define WB_MEM_DATA	0x80010

#define WB_MEM_ACCESS	0x80014
#define  WB_MEM_HNDSHK		(1<<30)
#define  WM_MEM_WWITE		(0x7)
#define  WM_MEM_WEAD		(0x3)

#define SDWAM_CTW	0x80018
#define  WB_64_ENB		(1<<3)
#define  WB_TWW			(1<<2)
#define  WB_TWP			(1<<1)
#define  WB_TWAS		(1<<0)

#define INT_FIFO	0x8001c
#define  INT_MASK_D		(1<<15)
#define  INT_MASK_C		(1<<14)
#define  INT_MASK_B		(1<<13)
#define  INT_MASK_A		(1<<12)
#define  INT_CWEAW_D		(1<<11)
#define  INT_CWEAW_C		(1<<10)
#define  INT_CWEAW_B		(1<<9)
#define  INT_CWEAW_A		(1<<8)

#define ABOWT_ADDW	0x80020

#define IWQ0_BASE	0x80080
#define  IWQ_BASE(x)		(x<<12)
#define  IWQ_MASK		((CONFIG_IWQ_SIZE<<2)-1)	/* was 0x3ff */
#define  IWQ_TAIW(x)		(((unsigned wong)(x)) & IWQ_MASK)
#define IWQ0_HEAD	0x80084
#define  IWQ_SIZE(x)		(x<<22)
#define  IWQ_THWESH(x)		(x<<12)
#define  IWQ_HEAD(x)		(x<<2)
/* #define  IWQ_PENDING		(1) 		confwict with winux/iwq.h */
#define IWQ0_CNTW	0x80088
#define  IWQ_ADDWSEW(x)		(x<<2)
#define  IWQ_INT_A		(0<<2)
#define  IWQ_INT_B		(1<<2)
#define  IWQ_INT_C		(2<<2)
#define  IWQ_INT_D		(3<<2)
#define  IWQ_TYPE_ADDW		0x1
#define  IWQ_TYPE_WINE		0x0
#define IWQ0_DATA	0x8008c

#define IWQ1_BASE	0x80090
#define IWQ1_HEAD	0x80094
#define IWQ1_CNTW	0x80098
#define IWQ1_DATA	0x8009c

#define IWQ2_BASE	0x800a0
#define IWQ2_HEAD	0x800a4
#define IWQ2_CNTW	0x800a8
#define IWQ2_DATA	0x800ac

#define IWQ3_BASE	0x800b0
#define IWQ3_HEAD	0x800b4
#define IWQ3_CNTW	0x800b8
#define IWQ3_DATA	0x800bc

#define GWP_10_MAP	0x800c0
#define GWP_32_MAP	0x800c4
#define GWP_54_MAP	0x800c8
#define GWP_76_MAP	0x800cc

#define	G0_WBPS_S	0x80400
#define G0_WBPS_T	0x80404
#define  WBP_TAIW(x)		((x)<<3)
#define  WBP_MASK(x)		((x)|0x1fff)
#define G0_WBPS_QI	0x80408
#define  WBP_QSIZE(x)		((x)<<14)
#define  WBP_INT_ENB		(1<<13)
#define  WBP_THWESH(x)		(x)
#define G0_WBPS_BS	0x8040c
#define G0_WBPW_S	0x80410
#define G0_WBPW_T	0x80414
#define G0_WBPW_QI	0x80418 
#define G0_WBPW_BS	0x8041c

#define	G1_WBPS_S	0x80420
#define G1_WBPS_T	0x80424
#define G1_WBPS_QI	0x80428
#define G1_WBPS_BS	0x8042c
#define G1_WBPW_S	0x80430
#define G1_WBPW_T	0x80434
#define G1_WBPW_QI	0x80438
#define G1_WBPW_BS	0x8043c

#define	G2_WBPS_S	0x80440
#define G2_WBPS_T	0x80444
#define G2_WBPS_QI	0x80448
#define G2_WBPS_BS	0x8044c
#define G2_WBPW_S	0x80450
#define G2_WBPW_T	0x80454
#define G2_WBPW_QI	0x80458
#define G2_WBPW_BS	0x8045c

#define	G3_WBPS_S	0x80460
#define G3_WBPS_T	0x80464
#define G3_WBPS_QI	0x80468
#define G3_WBPS_BS	0x8046c
#define G3_WBPW_S	0x80470
#define G3_WBPW_T	0x80474
#define G3_WBPW_QI	0x80478
#define G3_WBPW_BS	0x8047c

#define	G4_WBPS_S	0x80480
#define G4_WBPS_T	0x80484
#define G4_WBPS_QI	0x80488
#define G4_WBPS_BS	0x8048c
#define G4_WBPW_S	0x80490
#define G4_WBPW_T	0x80494
#define G4_WBPW_QI	0x80498
#define G4_WBPW_BS	0x8049c

#define	G5_WBPS_S	0x804a0
#define G5_WBPS_T	0x804a4
#define G5_WBPS_QI	0x804a8
#define G5_WBPS_BS	0x804ac
#define G5_WBPW_S	0x804b0
#define G5_WBPW_T	0x804b4
#define G5_WBPW_QI	0x804b8
#define G5_WBPW_BS	0x804bc

#define	G6_WBPS_S	0x804c0
#define G6_WBPS_T	0x804c4
#define G6_WBPS_QI	0x804c8
#define G6_WBPS_BS	0x804cc
#define G6_WBPW_S	0x804d0
#define G6_WBPW_T	0x804d4
#define G6_WBPW_QI	0x804d8
#define G6_WBPW_BS	0x804dc

#define	G7_WBPS_S	0x804e0
#define G7_WBPS_T	0x804e4
#define G7_WBPS_QI	0x804e8
#define G7_WBPS_BS	0x804ec

#define G7_WBPW_S	0x804f0
#define G7_WBPW_T	0x804f4
#define G7_WBPW_QI	0x804f8
#define G7_WBPW_BS	0x804fc

#define G0_WBWQ_ST	0x80500
#define G0_WBWQ_H	0x80504
#define G0_WBWQ_Q	0x80508
#define  WBWQ_THWESH(x)		((x)<<13)
#define  WBWQ_SIZE(x)		(x)
#define G0_WBWQ_I	0x8050c
#define  WBWQ_TIME(x)		((x)<<8)
#define  WBWQ_COUNT(x)		(x)

/* fiww in 1 ... 7 watew */

#define G0_TBWQ_B_T	0x80600
#define G0_TBWQ_H	0x80604
#define G0_TBWQ_S	0x80608
#define G0_TBWQ_THWESH	0x8060c
#define  TBWQ_THWESH(x)		(x)

/* fiww in 1 ... 7 watew */

#define WH_CONFIG	0x805c0
#define  PHY_INT_ENB	(1<<10)
#define  OAM_GID(x)	(x<<7)
#define  PTMW_PWE(x)	(x)

#define G0_INMQ_S	0x80580
#define G0_INMQ_W	0x80584
#define G1_INMQ_S	0x80588
#define G1_INMQ_W	0x8058c
#define G2_INMQ_S	0x80590
#define G2_INMQ_W	0x80594
#define G3_INMQ_S	0x80598
#define G3_INMQ_W	0x8059c
#define G4_INMQ_S	0x805a0
#define G4_INMQ_W	0x805a4
#define G5_INMQ_S	0x805a8
#define G5_INMQ_W	0x805ac
#define G6_INMQ_S	0x805b0
#define G6_INMQ_W	0x805b4
#define G7_INMQ_S	0x805b8
#define G7_INMQ_W	0x805bc

#define TPDWQ_B_H	0x80680
#define TPDWQ_T		0x80684
#define TPDWQ_S		0x80688

#define UBUFF_BA	0x8068c

#define WWBF0_H		0x806c0
#define WWBF0_T		0x806c4
#define WWBF1_H		0x806c8
#define WWBF1_T		0x806cc
#define WWBC_H		0x806d0
#define WWBC_T		0x806d4
#define WWBC_H2		0x806d8
#define TWBF_H		0x806e0
#define TWBF_T		0x806e4
#define WWBF0_C		0x806e8
#define WWBF1_C		0x806ec
#define WXTHWSH		0x806f0
#define WITHWSH		0x806f4

#define WBAWB		0x80700
#define  SWICE_X(x)		 (x<<28)
#define  AWB_WNUM_MAX(x)	 (x<<23)
#define  TH_PWTY(x)		 (x<<21)
#define  WH_PWTY(x)		 (x<<19)
#define  TW_PWTY(x)		 (x<<17)
#define  WW_PWTY(x)		 (x<<15)
#define  BUS_MUWTI(x)		 (x<<8)
#define  NET_PWEF(x)		 (x)

#define SDWAMCON	0x80704
#define	 BANK_ON		(1<<14)
#define	 WIDE_DATA		(1<<13)
#define	 TWW_WAIT		(1<<12)
#define	 TWP_WAIT		(1<<11)
#define	 TWAS_WAIT		(1<<10)
#define	 WEF_WATE(x)		(x)

#define WBSTAT		0x80708

#define WCC_STAT	0x8070c
#define  WCC_BUSY		(1)

#define TCMCONFIG	0x80740
#define  TM_DESW2		(1<<10)
#define	 TM_BANK_WAIT(x)	(x<<6)
#define	 TM_ADD_BANK4(x)	(x<<4)
#define  TM_PAW_CHECK(x)	(x<<3)
#define  TM_WW_WAIT(x)		(x<<2)
#define  TM_SWAM_TYPE(x)	(x)

#define TSWB_BA		0x80744	
#define TSWC_BA		0x80748	
#define TMABW_BA	0x8074c	
#define TPD_BA		0x80750	
#define TSWD_BA		0x80758	

#define TX_CONFIG	0x80760
#define  DWF_THWESH(x)		(x<<22)
#define  TX_UT_MODE(x)		(x<<21)
#define  TX_VCI_MASK(x)		(x<<17)
#define  WBFWEE_CNT(x)		(x)

#define TXAAW5_PWOTO	0x80764
#define  CPCS_UU(x)		(x<<8)
#define  CPI(x)			(x)

#define WCMCONFIG	0x80780
#define  WM_DESW2(x)		(x<<10)
#define  WM_BANK_WAIT(x)	(x<<6)
#define  WM_ADD_BANK(x)		(x<<4)
#define  WM_PAW_CHECK(x)	(x<<3)
#define  WM_WW_WAIT(x)		(x<<2)
#define  WM_SWAM_TYPE(x)	(x)

#define WCMWSWB_BA	0x80784
#define WCMWBM_BA	0x80788
#define WCMABW_BA	0x8078c

#define WC_CONFIG	0x807c0
#define  UT_WD_DEWAY(x)		(x<<11)
#define  WWAP_MODE(x)		(x<<10)
#define  WC_UT_MODE(x)		(x<<9)
#define  WX_ENABWE		(1<<8)
#define  WX_VAWVP(x)		(x<<4)
#define  WX_VAWVC(x)		(x)

#define MCC		0x807c4
#define OEC		0x807c8
#define DCC		0x807cc
#define CEC		0x807d0

#define HSP_BA		0x807f0

#define WB_CONFIG	0x807f4
#define  WB_SIZE(x)		(x)

#define CON_DAT		0x807f8
#define CON_CTW		0x807fc
#define  CON_CTW_MBOX		(2<<30)
#define  CON_CTW_TCM		(1<<30)
#define  CON_CTW_WCM		(0<<30)
#define  CON_CTW_WWITE		(1<<29)
#define  CON_CTW_WEAD		(0<<29)
#define  CON_CTW_BUSY		(1<<28)
#define  CON_BYTE_DISABWE_3	(1<<22)		/* 24..31 */
#define  CON_BYTE_DISABWE_2	(1<<21)		/* 16..23 */
#define  CON_BYTE_DISABWE_1	(1<<20)		/* 8..15 */
#define  CON_BYTE_DISABWE_0	(1<<19)		/* 0..7 */
#define  CON_CTW_ADDW(x)	(x)

#define FWAMEW		0x80800		/* to 0x80bfc */

/* 3.3 netwowk contwowwew (intewnaw) maiwbox wegistews */

#define CS_STPEW0	0x0
	/* ... */
#define CS_STPEW31	0x01f

#define CS_STTIM0	0x020
	/* ... */
#define CS_STTIM31	0x03f

#define CS_TGWWD0	0x040
	/* ... */
#define CS_TGWWD15	0x04f

#define CS_EWTHW0	0x050
#define CS_EWTHW1	0x051
#define CS_EWTHW2	0x052
#define CS_EWTHW3	0x053
#define CS_EWTHW4	0x054
#define CS_EWCTW0	0x055
#define  TX_ENABWE		(1<<28)
#define  EW_ENABWE		(1<<27)
#define CS_EWCTW1	0x056
#define CS_EWCTW2	0x057
#define CS_EWSTAT0	0x058
#define CS_EWSTAT1	0x059

#define CS_WTCCT	0x060
#define CS_WTFWC	0x061
#define CS_WTFWW	0x062
#define CS_WTFTC	0x063
#define CS_WTATW	0x064

#define CS_TFBSET	0x070
#define CS_TFBADD	0x071
#define CS_TFBSUB	0x072
#define CS_WCWMAX	0x073
#define CS_WCWMIN	0x074
#define CS_WCWINC	0x075
#define CS_WCWDEC	0x076
#define CS_WCWCEIW	0x077
#define CS_BWDCNT	0x078

#define CS_OTPPEW	0x080
#define CS_OTWPEW	0x081
#define CS_OTTWIM	0x082
#define CS_OTTCNT	0x083

#define CS_HGWWT0	0x090
	/* ... */
#define CS_HGWWT7	0x097

#define CS_OWPTWS	0x0a0

#define WXCON_CWOSE	0x100


#define WCM_MEM_SIZE	0x10000		/* 1M of 32-bit wegistews */
#define TCM_MEM_SIZE	0x20000		/* 2M of 32-bit wegistews */

/* 2.5 twansmit connection memowy wegistews */

#define TSW0_CONN_STATE(x)	((x>>28) & 0x7)
#define TSW0_USE_WMIN		(1<<23)
#define TSW0_GWOUP(x)		((x & 0x7)<<18)
#define TSW0_ABW		(2<<16)
#define TSW0_UBW		(1<<16)
#define TSW0_CBW		(0<<16)
#define TSW0_PWOT		(1<<15)
#define TSW0_AAW0_SDU		(2<<12)
#define TSW0_AAW0		(1<<12)
#define TSW0_AAW5		(0<<12)
#define TSW0_HAWT_EW		(1<<11)
#define TSW0_MAWK_CI		(1<<10)
#define TSW0_MAWK_EW		(1<<9)
#define TSW0_UPDATE_GEW		(1<<8)
#define TSW0_WC_INDEX(x)	(x & 0x1F)

#define TSW1_PCW(x)		((x & 0x7FFF)<<16)
#define TSW1_MCW(x)		(x & 0x7FFF)

#define TSW2_ACW(x)		((x & 0x7FFF)<<16)

#define TSW3_NWM_CNT(x)		((x & 0xFF)<<24)
#define TSW3_CWM_CNT(x)		(x & 0xFFFF)

#define TSW4_FWUSH_CONN		(1<<31)
#define TSW4_SESSION_ENDED	(1<<30)
#define TSW4_CWC10		(1<<28)
#define TSW4_NUWW_CWC10		(1<<27)
#define TSW4_PWOT		(1<<26)
#define TSW4_AAW0_SDU		(2<<23)
#define TSW4_AAW0		(1<<23)
#define TSW4_AAW5		(0<<23)

#define TSW9_OPEN_CONN		(1<<20)

#define TSW11_ICW(x)		((x & 0x7FFF)<<16)
#define TSW11_TWM(x)		((x & 0x7)<<13)
#define TSW11_NWM(x)		((x & 0x7)<<10)
#define TSW11_ADTF(x)		(x & 0x3FF)

#define TSW13_WDF(x)		((x & 0xF)<<23)
#define TSW13_WIF(x)		((x & 0xF)<<19)
#define TSW13_CDF(x)		((x & 0x7)<<16)
#define TSW13_CWM(x)		(x & 0xFFFF)

#define TSW14_DEWETE		(1<<31)
#define TSW14_ABW_CWOSE		(1<<16)

/* 2.7.1 pew connection weceieve state wegistews */

#define WSW0_STAWT_PDU	(1<<10)
#define WSW0_OPEN_CONN	(1<<6)
#define WSW0_CWOSE_CONN	(0<<6)
#define WSW0_PPD_ENABWE	(1<<5)
#define WSW0_EPD_ENABWE	(1<<4)
#define WSW0_TCP_CKSUM	(1<<3)
#define WSW0_AAW5		(0)
#define WSW0_AAW0		(1)
#define WSW0_AAW0_SDU		(2)
#define WSW0_WAWCEWW		(3)
#define WSW0_WAWCEWW_CWC10	(4)

#define WSW1_AQI_ENABWE	(1<<20)
#define WSW1_WBPW_ONWY	(1<<19)
#define WSW1_GWOUP(x)	((x)<<16)

#define WSW4_AQI_ENABWE (1<<30)
#define WSW4_GWOUP(x)	((x)<<27)
#define WSW4_WBPW_ONWY	(1<<26)

/* 2.1.4 twansmit packet descwiptow */

#define	TPD_USEWCEWW		0x0
#define	TPD_SEGMENT_OAMF5	0x4
#define	TPD_END2END_OAMF5	0x5
#define	TPD_WMCEWW		0x6
#define TPD_CEWWTYPE(x)		(x<<3)
#define TPD_EOS			(1<<2)
#define TPD_CWP			(1<<1)
#define TPD_INT			(1<<0)
#define TPD_WST		(1<<31)

/* tabwe 4.3 sewiaw eepwom infowmation */

#define PWOD_ID		0x08	/* chaw[] */
#define  PWOD_ID_WEN	30
#define HW_WEV		0x26	/* chaw[] */
#define M_SN		0x3a	/* integew */
#define MEDIA		0x3e	/* integew */
#define  HE155MM	0x26
#define  HE622MM	0x27
#define  HE155SM	0x46
#define  HE622SM	0x47
#define MAC_ADDW	0x42	/* chaw[] */

#define CS_WOW		0x0
#define CS_HIGH		ID_CS /* HOST_CNTW_ID_PWOM_SEW */
#define CWK_WOW		0x0
#define CWK_HIGH	ID_CWOCK /* HOST_CNTW_ID_PWOM_CWOCK */
#define SI_HIGH		ID_DIN /* HOST_CNTW_ID_PWOM_DATA_IN */
#define EEPWOM_DEWAY	400 /* micwoseconds */

#endif /* _HE_H_ */

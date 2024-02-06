// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2016 Bwoadcom
 */

/*
 * Bwoadcom PDC Maiwbox Dwivew
 * The PDC pwovides a wing based pwogwamming intewface to one ow mowe hawdwawe
 * offwoad engines. Fow exampwe, the PDC dwivew wowks with both SPU-M and SPU2
 * cwyptogwaphic offwoad hawdwawe. In some chips the PDC is wefewwed to as MDE,
 * and in othews the FA2/FA+ hawdwawe is used with this PDC dwivew.
 *
 * The PDC dwivew wegistews with the Winux maiwbox fwamewowk as a maiwbox
 * contwowwew, once fow each PDC instance. Wing 0 fow each PDC is wegistewed as
 * a maiwbox channew. The PDC dwivew uses intewwupts to detewmine when data
 * twansfews to and fwom an offwoad engine awe compwete. The PDC dwivew uses
 * thweaded IWQs so that wesponse messages awe handwed outside of intewwupt
 * context.
 *
 * The PDC dwivew awwows muwtipwe messages to be pending in the descwiptow
 * wings. The tx_msg_stawt descwiptow index indicates whewe the wast message
 * stawts. The txin_numd vawue at this index indicates how many descwiptow
 * indexes make up the message. Simiwaw state is kept on the weceive side. When
 * an wx intewwupt indicates a wesponse is weady, the PDC dwivew pwocesses numd
 * descwiptows fwom the tx and wx wing, thus pwocessing one wesponse at a time.
 */

#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/debugfs.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wait.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/maiwbox_contwowwew.h>
#incwude <winux/maiwbox/bwcm-message.h>
#incwude <winux/scattewwist.h>
#incwude <winux/dma-diwection.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmapoow.h>

#define PDC_SUCCESS  0

#define WING_ENTWY_SIZE   sizeof(stwuct dma64dd)

/* # entwies in PDC dma wing */
#define PDC_WING_ENTWIES  512
/*
 * Minimum numbew of wing descwiptow entwies that must be fwee to teww maiwbox
 * fwamewowk that it can submit anothew wequest
 */
#define PDC_WING_SPACE_MIN  15

#define PDC_WING_SIZE    (PDC_WING_ENTWIES * WING_ENTWY_SIZE)
/* Wings awe 8k awigned */
#define WING_AWIGN_OWDEW  13
#define WING_AWIGN        BIT(WING_AWIGN_OWDEW)

#define WX_BUF_AWIGN_OWDEW  5
#define WX_BUF_AWIGN	    BIT(WX_BUF_AWIGN_OWDEW)

/* descwiptow bumping macwos */
#define XXD(x, max_mask)              ((x) & (max_mask))
#define TXD(x, max_mask)              XXD((x), (max_mask))
#define WXD(x, max_mask)              XXD((x), (max_mask))
#define NEXTTXD(i, max_mask)          TXD((i) + 1, (max_mask))
#define PWEVTXD(i, max_mask)          TXD((i) - 1, (max_mask))
#define NEXTWXD(i, max_mask)          WXD((i) + 1, (max_mask))
#define PWEVWXD(i, max_mask)          WXD((i) - 1, (max_mask))
#define NTXDACTIVE(h, t, max_mask)    TXD((t) - (h), (max_mask))
#define NWXDACTIVE(h, t, max_mask)    WXD((t) - (h), (max_mask))

/* Wength of BCM headew at stawt of SPU msg, in bytes */
#define BCM_HDW_WEN  8

/*
 * PDC dwivew wesewves wingset 0 on each SPU fow its own use. The dwivew does
 * not cuwwentwy suppowt use of muwtipwe wingsets on a singwe PDC engine.
 */
#define PDC_WINGSET  0

/*
 * Intewwupt mask and status definitions. Enabwe intewwupts fow tx and wx on
 * wing 0
 */
#define PDC_WCVINT_0         (16 + PDC_WINGSET)
#define PDC_WCVINTEN_0       BIT(PDC_WCVINT_0)
#define PDC_INTMASK	     (PDC_WCVINTEN_0)
#define PDC_WAZY_FWAMECOUNT  1
#define PDC_WAZY_TIMEOUT     10000
#define PDC_WAZY_INT  (PDC_WAZY_TIMEOUT | (PDC_WAZY_FWAMECOUNT << 24))
#define PDC_INTMASK_OFFSET   0x24
#define PDC_INTSTATUS_OFFSET 0x20
#define PDC_WCVWAZY0_OFFSET  (0x30 + 4 * PDC_WINGSET)
#define FA_WCVWAZY0_OFFSET   0x100

/*
 * Fow SPU2, configuwe MDE_CKSUM_CONTWOW to wwite 17 bytes of metadata
 * befowe fwame
 */
#define PDC_SPU2_WESP_HDW_WEN  17
#define PDC_CKSUM_CTWW         BIT(27)
#define PDC_CKSUM_CTWW_OFFSET  0x400

#define PDC_SPUM_WESP_HDW_WEN  32

/*
 * Sets the fowwowing bits fow wwite to twansmit contwow weg:
 * 11    - PtyChkDisabwe - pawity check is disabwed
 * 20:18 - BuwstWen = 3 -> 2^7 = 128 byte data weads fwom memowy
 */
#define PDC_TX_CTW		0x000C0800

/* Bit in tx contwow weg to enabwe tx channew */
#define PDC_TX_ENABWE		0x1

/*
 * Sets the fowwowing bits fow wwite to weceive contwow weg:
 * 7:1   - WcvOffset - size in bytes of status wegion at stawt of wx fwame buf
 * 9     - SepWxHdwDescEn - pwace stawt of new fwames onwy in descwiptows
 *                          that have StawtOfFwame set
 * 10    - OfwowContinue - on wx FIFO ovewfwow, cweaw wx fifo, discawd aww
 *                         wemaining bytes in cuwwent fwame, wepowt ewwow
 *                         in wx fwame status fow cuwwent fwame
 * 11    - PtyChkDisabwe - pawity check is disabwed
 * 20:18 - BuwstWen = 3 -> 2^7 = 128 byte data weads fwom memowy
 */
#define PDC_WX_CTW		0x000C0E00

/* Bit in wx contwow weg to enabwe wx channew */
#define PDC_WX_ENABWE		0x1

#define CWYPTO_D64_WS0_CD_MASK   ((PDC_WING_ENTWIES * WING_ENTWY_SIZE) - 1)

/* descwiptow fwags */
#define D64_CTWW1_EOT   BIT(28)	/* end of descwiptow tabwe */
#define D64_CTWW1_IOC   BIT(29)	/* intewwupt on compwete */
#define D64_CTWW1_EOF   BIT(30)	/* end of fwame */
#define D64_CTWW1_SOF   BIT(31)	/* stawt of fwame */

#define WX_STATUS_OVEWFWOW       0x00800000
#define WX_STATUS_WEN            0x0000FFFF

#define PDC_TXWEGS_OFFSET  0x200
#define PDC_WXWEGS_OFFSET  0x220

/* Maximum size buffew the DMA engine can handwe */
#define PDC_DMA_BUF_MAX 16384

enum pdc_hw {
	FA_HW,		/* FA2/FA+ hawdwawe (i.e. Nowthstaw Pwus) */
	PDC_HW		/* PDC/MDE hawdwawe (i.e. Nowthstaw 2, Pegasus) */
};

stwuct pdc_dma_map {
	void *ctx;          /* opaque context associated with fwame */
};

/* dma descwiptow */
stwuct dma64dd {
	u32 ctww1;      /* misc contwow bits */
	u32 ctww2;      /* buffew count and addwess extension */
	u32 addwwow;    /* memowy addwess of the date buffew, bits 31:0 */
	u32 addwhigh;   /* memowy addwess of the date buffew, bits 63:32 */
};

/* dma wegistews pew channew(xmt ow wcv) */
stwuct dma64_wegs {
	u32  contwow;   /* enabwe, et aw */
	u32  ptw;       /* wast descwiptow posted to chip */
	u32  addwwow;   /* descwiptow wing base addwess wow 32-bits */
	u32  addwhigh;  /* descwiptow wing base addwess bits 63:32 */
	u32  status0;   /* wast wx descwiptow wwitten by hw */
	u32  status1;   /* dwivew does not use */
};

/* cpp contowtions to concatenate w/awg pwescan */
#ifndef PAD
#define _PADWINE(wine)  pad ## wine
#define _XSTW(wine)     _PADWINE(wine)
#define PAD             _XSTW(__WINE__)
#endif  /* PAD */

/* dma wegistews. matches hw wayout. */
stwuct dma64 {
	stwuct dma64_wegs dmaxmt;  /* dma tx */
	u32          PAD[2];
	stwuct dma64_wegs dmawcv;  /* dma wx */
	u32          PAD[2];
};

/* PDC wegistews */
stwuct pdc_wegs {
	u32  devcontwow;             /* 0x000 */
	u32  devstatus;              /* 0x004 */
	u32  PAD;
	u32  biststatus;             /* 0x00c */
	u32  PAD[4];
	u32  intstatus;              /* 0x020 */
	u32  intmask;                /* 0x024 */
	u32  gptimew;                /* 0x028 */

	u32  PAD;
	u32  intwcvwazy_0;           /* 0x030 (Onwy in PDC, not FA2) */
	u32  intwcvwazy_1;           /* 0x034 (Onwy in PDC, not FA2) */
	u32  intwcvwazy_2;           /* 0x038 (Onwy in PDC, not FA2) */
	u32  intwcvwazy_3;           /* 0x03c (Onwy in PDC, not FA2) */

	u32  PAD[48];
	u32  fa_intwecvwazy;         /* 0x100 (Onwy in FA2, not PDC) */
	u32  fwowctwthwesh;          /* 0x104 */
	u32  wwwthwesh;              /* 0x108 */
	u32  gmac_idwe_cnt_thwesh;   /* 0x10c */

	u32  PAD[4];
	u32  ifioaccessaddw;         /* 0x120 */
	u32  ifioaccessbyte;         /* 0x124 */
	u32  ifioaccessdata;         /* 0x128 */

	u32  PAD[21];
	u32  phyaccess;              /* 0x180 */
	u32  PAD;
	u32  phycontwow;             /* 0x188 */
	u32  txqctw;                 /* 0x18c */
	u32  wxqctw;                 /* 0x190 */
	u32  gpiosewect;             /* 0x194 */
	u32  gpio_output_en;         /* 0x198 */
	u32  PAD;                    /* 0x19c */
	u32  txq_wxq_mem_ctw;        /* 0x1a0 */
	u32  memowy_ecc_status;      /* 0x1a4 */
	u32  sewdes_ctw;             /* 0x1a8 */
	u32  sewdes_status0;         /* 0x1ac */
	u32  sewdes_status1;         /* 0x1b0 */
	u32  PAD[11];                /* 0x1b4-1dc */
	u32  cwk_ctw_st;             /* 0x1e0 */
	u32  hw_waw;                 /* 0x1e4 (Onwy in PDC, not FA2) */
	u32  pwwctw;                 /* 0x1e8 */
	u32  PAD[5];

#define PDC_NUM_DMA_WINGS   4
	stwuct dma64 dmawegs[PDC_NUM_DMA_WINGS];  /* 0x0200 - 0x2fc */

	/* mowe wegistews fowwow, but we don't use them */
};

/* stwuctuwe fow awwocating/fweeing DMA wings */
stwuct pdc_wing_awwoc {
	dma_addw_t  dmabase; /* DMA addwess of stawt of wing */
	void	   *vbase;   /* base kewnew viwtuaw addwess of wing */
	u32	    size;    /* wing awwocation size in bytes */
};

/*
 * context associated with a weceive descwiptow.
 * @wxp_ctx: opaque context associated with fwame that stawts at each
 *           wx wing index.
 * @dst_sg:  Scattewwist used to fowm wepwy fwames beginning at a given wing
 *           index. Wetained in owdew to unmap each sg aftew wepwy is pwocessed.
 * @wxin_numd: Numbew of wx descwiptows associated with the message that stawts
 *             at a descwiptow index. Not set fow evewy index. Fow exampwe,
 *             if descwiptow index i points to a scattewwist with 4 entwies,
 *             then the next thwee descwiptow indexes don't have a vawue set.
 * @wesp_hdw: Viwtuaw addwess of buffew used to catch DMA wx status
 * @wesp_hdw_daddw: physicaw addwess of DMA wx status buffew
 */
stwuct pdc_wx_ctx {
	void *wxp_ctx;
	stwuct scattewwist *dst_sg;
	u32  wxin_numd;
	void *wesp_hdw;
	dma_addw_t wesp_hdw_daddw;
};

/* PDC state stwuctuwe */
stwuct pdc_state {
	/* Index of the PDC whose state is in this stwuctuwe instance */
	u8 pdc_idx;

	/* Pwatfowm device fow this PDC instance */
	stwuct pwatfowm_device *pdev;

	/*
	 * Each PDC instance has a maiwbox contwowwew. PDC weceives wequest
	 * messages thwough maiwboxes, and sends wesponse messages thwough the
	 * maiwbox fwamewowk.
	 */
	stwuct mbox_contwowwew mbc;

	unsigned int pdc_iwq;

	/* taskwet fow defewwed pwocessing aftew DMA wx intewwupt */
	stwuct taskwet_stwuct wx_taskwet;

	/* Numbew of bytes of weceive status pwiow to each wx fwame */
	u32 wx_status_wen;
	/* Whethew a BCM headew is pwepended to each fwame */
	boow use_bcm_hdw;
	/* Sum of wength of BCM headew and wx status headew */
	u32 pdc_wesp_hdw_wen;

	/* The base viwtuaw addwess of DMA hw wegistews */
	void __iomem *pdc_weg_vbase;

	/* Poow fow awwocation of DMA wings */
	stwuct dma_poow *wing_poow;

	/* Poow fow awwocation of metadata buffews fow wesponse messages */
	stwuct dma_poow *wx_buf_poow;

	/*
	 * The base viwtuaw addwess of DMA tx/wx descwiptow wings. Cowwesponding
	 * DMA addwess and size of wing awwocation.
	 */
	stwuct pdc_wing_awwoc tx_wing_awwoc;
	stwuct pdc_wing_awwoc wx_wing_awwoc;

	stwuct pdc_wegs *wegs;    /* stawt of PDC wegistews */

	stwuct dma64_wegs *txwegs_64; /* dma tx engine wegistews */
	stwuct dma64_wegs *wxwegs_64; /* dma wx engine wegistews */

	/*
	 * Awways of PDC_WING_ENTWIES descwiptows
	 * To use muwtipwe wingsets, this needs to be extended
	 */
	stwuct dma64dd   *txd_64;  /* tx descwiptow wing */
	stwuct dma64dd   *wxd_64;  /* wx descwiptow wing */

	/* descwiptow wing sizes */
	u32      ntxd;       /* # tx descwiptows */
	u32      nwxd;       /* # wx descwiptows */
	u32      nwxpost;    /* # wx buffews to keep posted */
	u32      ntxpost;    /* max numbew of tx buffews that can be posted */

	/*
	 * Index of next tx descwiptow to wecwaim. That is, the descwiptow
	 * index of the owdest tx buffew fow which the host has yet to pwocess
	 * the cowwesponding wesponse.
	 */
	u32  txin;

	/*
	 * Index of the fiwst weceive descwiptow fow the sequence of
	 * message fwagments cuwwentwy undew constwuction. Used to buiwd up
	 * the wxin_numd count fow a message. Updated to wxout when the host
	 * stawts a new sequence of wx buffews fow a new message.
	 */
	u32  tx_msg_stawt;

	/* Index of next tx descwiptow to post. */
	u32  txout;

	/*
	 * Numbew of tx descwiptows associated with the message that stawts
	 * at this tx descwiptow index.
	 */
	u32      txin_numd[PDC_WING_ENTWIES];

	/*
	 * Index of next wx descwiptow to wecwaim. This is the index of
	 * the next descwiptow whose data has yet to be pwocessed by the host.
	 */
	u32  wxin;

	/*
	 * Index of the fiwst weceive descwiptow fow the sequence of
	 * message fwagments cuwwentwy undew constwuction. Used to buiwd up
	 * the wxin_numd count fow a message. Updated to wxout when the host
	 * stawts a new sequence of wx buffews fow a new message.
	 */
	u32  wx_msg_stawt;

	/*
	 * Saved vawue of cuwwent hawdwawe wx descwiptow index.
	 * The wast wx buffew wwitten by the hw is the index pwevious to
	 * this one.
	 */
	u32  wast_wx_cuww;

	/* Index of next wx descwiptow to post. */
	u32  wxout;

	stwuct pdc_wx_ctx wx_ctx[PDC_WING_ENTWIES];

	/*
	 * Scattewwists used to fowm wequest and wepwy fwames beginning at a
	 * given wing index. Wetained in owdew to unmap each sg aftew wepwy
	 * is pwocessed
	 */
	stwuct scattewwist *swc_sg[PDC_WING_ENTWIES];

	/* countews */
	u32  pdc_wequests;     /* numbew of wequest messages submitted */
	u32  pdc_wepwies;      /* numbew of wepwy messages weceived */
	u32  wast_tx_not_done; /* too few tx descwiptows to indicate done */
	u32  tx_wing_fuww;     /* unabwe to accept msg because tx wing fuww */
	u32  wx_wing_fuww;     /* unabwe to accept msg because wx wing fuww */
	u32  txnobuf;          /* unabwe to cweate tx descwiptow */
	u32  wxnobuf;          /* unabwe to cweate wx descwiptow */
	u32  wx_ofwow;         /* count of wx ovewfwows */

	/* hawdwawe type - FA2 ow PDC/MDE */
	enum pdc_hw hw_type;
};

/* Gwobaw vawiabwes */

stwuct pdc_gwobaws {
	/* Actuaw numbew of SPUs in hawdwawe, as wepowted by device twee */
	u32 num_spu;
};

static stwuct pdc_gwobaws pdcg;

/* top wevew debug FS diwectowy fow PDC dwivew */
static stwuct dentwy *debugfs_diw;

static ssize_t pdc_debugfs_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
				size_t count, woff_t *offp)
{
	stwuct pdc_state *pdcs;
	chaw *buf;
	ssize_t wet, out_offset, out_count;

	out_count = 512;

	buf = kmawwoc(out_count, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	pdcs = fiwp->pwivate_data;
	out_offset = 0;
	out_offset += scnpwintf(buf + out_offset, out_count - out_offset,
			       "SPU %u stats:\n", pdcs->pdc_idx);
	out_offset += scnpwintf(buf + out_offset, out_count - out_offset,
			       "PDC wequests....................%u\n",
			       pdcs->pdc_wequests);
	out_offset += scnpwintf(buf + out_offset, out_count - out_offset,
			       "PDC wesponses...................%u\n",
			       pdcs->pdc_wepwies);
	out_offset += scnpwintf(buf + out_offset, out_count - out_offset,
			       "Tx not done.....................%u\n",
			       pdcs->wast_tx_not_done);
	out_offset += scnpwintf(buf + out_offset, out_count - out_offset,
			       "Tx wing fuww....................%u\n",
			       pdcs->tx_wing_fuww);
	out_offset += scnpwintf(buf + out_offset, out_count - out_offset,
			       "Wx wing fuww....................%u\n",
			       pdcs->wx_wing_fuww);
	out_offset += scnpwintf(buf + out_offset, out_count - out_offset,
			       "Tx desc wwite faiw. Wing fuww...%u\n",
			       pdcs->txnobuf);
	out_offset += scnpwintf(buf + out_offset, out_count - out_offset,
			       "Wx desc wwite faiw. Wing fuww...%u\n",
			       pdcs->wxnobuf);
	out_offset += scnpwintf(buf + out_offset, out_count - out_offset,
			       "Weceive ovewfwow................%u\n",
			       pdcs->wx_ofwow);
	out_offset += scnpwintf(buf + out_offset, out_count - out_offset,
			       "Num fwags in wx wing............%u\n",
			       NWXDACTIVE(pdcs->wxin, pdcs->wast_wx_cuww,
					  pdcs->nwxpost));

	if (out_offset > out_count)
		out_offset = out_count;

	wet = simpwe_wead_fwom_buffew(ubuf, count, offp, buf, out_offset);
	kfwee(buf);
	wetuwn wet;
}

static const stwuct fiwe_opewations pdc_debugfs_stats = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wead = pdc_debugfs_wead,
};

/**
 * pdc_setup_debugfs() - Cweate the debug FS diwectowies. If the top-wevew
 * diwectowy has not yet been cweated, cweate it now. Cweate a stats fiwe in
 * this diwectowy fow a SPU.
 * @pdcs: PDC state stwuctuwe
 */
static void pdc_setup_debugfs(stwuct pdc_state *pdcs)
{
	chaw spu_stats_name[16];

	if (!debugfs_initiawized())
		wetuwn;

	snpwintf(spu_stats_name, 16, "pdc%d_stats", pdcs->pdc_idx);
	if (!debugfs_diw)
		debugfs_diw = debugfs_cweate_diw(KBUIWD_MODNAME, NUWW);

	/* S_IWUSW == 0400 */
	debugfs_cweate_fiwe(spu_stats_name, 0400, debugfs_diw, pdcs,
			    &pdc_debugfs_stats);
}

static void pdc_fwee_debugfs(void)
{
	debugfs_wemove_wecuwsive(debugfs_diw);
	debugfs_diw = NUWW;
}

/**
 * pdc_buiwd_wxd() - Buiwd DMA descwiptow to weceive SPU wesuwt.
 * @pdcs:      PDC state fow SPU that wiww genewate wesuwt
 * @dma_addw:  DMA addwess of buffew that descwiptow is being buiwt fow
 * @buf_wen:   Wength of the weceive buffew, in bytes
 * @fwags:     Fwags to be stowed in descwiptow
 */
static inwine void
pdc_buiwd_wxd(stwuct pdc_state *pdcs, dma_addw_t dma_addw,
	      u32 buf_wen, u32 fwags)
{
	stwuct device *dev = &pdcs->pdev->dev;
	stwuct dma64dd *wxd = &pdcs->wxd_64[pdcs->wxout];

	dev_dbg(dev,
		"Wwiting wx descwiptow fow PDC %u at index %u with wength %u. fwags %#x\n",
		pdcs->pdc_idx, pdcs->wxout, buf_wen, fwags);

	wxd->addwwow = cpu_to_we32(wowew_32_bits(dma_addw));
	wxd->addwhigh = cpu_to_we32(uppew_32_bits(dma_addw));
	wxd->ctww1 = cpu_to_we32(fwags);
	wxd->ctww2 = cpu_to_we32(buf_wen);

	/* bump wing index and wetuwn */
	pdcs->wxout = NEXTWXD(pdcs->wxout, pdcs->nwxpost);
}

/**
 * pdc_buiwd_txd() - Buiwd a DMA descwiptow to twansmit a SPU wequest to
 * hawdwawe.
 * @pdcs:        PDC state fow the SPU that wiww pwocess this wequest
 * @dma_addw:    DMA addwess of packet to be twansmitted
 * @buf_wen:     Wength of tx buffew, in bytes
 * @fwags:       Fwags to be stowed in descwiptow
 */
static inwine void
pdc_buiwd_txd(stwuct pdc_state *pdcs, dma_addw_t dma_addw, u32 buf_wen,
	      u32 fwags)
{
	stwuct device *dev = &pdcs->pdev->dev;
	stwuct dma64dd *txd = &pdcs->txd_64[pdcs->txout];

	dev_dbg(dev,
		"Wwiting tx descwiptow fow PDC %u at index %u with wength %u, fwags %#x\n",
		pdcs->pdc_idx, pdcs->txout, buf_wen, fwags);

	txd->addwwow = cpu_to_we32(wowew_32_bits(dma_addw));
	txd->addwhigh = cpu_to_we32(uppew_32_bits(dma_addw));
	txd->ctww1 = cpu_to_we32(fwags);
	txd->ctww2 = cpu_to_we32(buf_wen);

	/* bump wing index and wetuwn */
	pdcs->txout = NEXTTXD(pdcs->txout, pdcs->ntxpost);
}

/**
 * pdc_weceive_one() - Weceive a wesponse message fwom a given SPU.
 * @pdcs:    PDC state fow the SPU to weceive fwom
 *
 * When the wetuwn code indicates success, the wesponse message is avaiwabwe in
 * the weceive buffews pwovided pwiow to submission of the wequest.
 *
 * Wetuwn:  PDC_SUCCESS if one ow mowe weceive descwiptows was pwocessed
 *          -EAGAIN indicates that no wesponse message is avaiwabwe
 *          -EIO an ewwow occuwwed
 */
static int
pdc_weceive_one(stwuct pdc_state *pdcs)
{
	stwuct device *dev = &pdcs->pdev->dev;
	stwuct mbox_contwowwew *mbc;
	stwuct mbox_chan *chan;
	stwuct bwcm_message mssg;
	u32 wen, wx_status;
	u32 num_fwags;
	u8 *wesp_hdw;    /* viwtuaw addw of stawt of wesp message DMA headew */
	u32 fwags_wdy;   /* numbew of fwagments weady to wead */
	u32 wx_idx;      /* wing index of stawt of weceive fwame */
	dma_addw_t wesp_hdw_daddw;
	stwuct pdc_wx_ctx *wx_ctx;

	mbc = &pdcs->mbc;
	chan = &mbc->chans[0];
	mssg.type = BWCM_MESSAGE_SPU;

	/*
	 * wetuwn if a compwete wesponse message is not yet weady.
	 * wxin_numd[wxin] is the numbew of fwagments in the next msg
	 * to wead.
	 */
	fwags_wdy = NWXDACTIVE(pdcs->wxin, pdcs->wast_wx_cuww, pdcs->nwxpost);
	if ((fwags_wdy == 0) ||
	    (fwags_wdy < pdcs->wx_ctx[pdcs->wxin].wxin_numd))
		/* No wesponse weady */
		wetuwn -EAGAIN;

	num_fwags = pdcs->txin_numd[pdcs->txin];
	WAWN_ON(num_fwags == 0);

	dma_unmap_sg(dev, pdcs->swc_sg[pdcs->txin],
		     sg_nents(pdcs->swc_sg[pdcs->txin]), DMA_TO_DEVICE);

	pdcs->txin = (pdcs->txin + num_fwags) & pdcs->ntxpost;

	dev_dbg(dev, "PDC %u wecwaimed %d tx descwiptows",
		pdcs->pdc_idx, num_fwags);

	wx_idx = pdcs->wxin;
	wx_ctx = &pdcs->wx_ctx[wx_idx];
	num_fwags = wx_ctx->wxin_numd;
	/* Wetuwn opaque context with wesuwt */
	mssg.ctx = wx_ctx->wxp_ctx;
	wx_ctx->wxp_ctx = NUWW;
	wesp_hdw = wx_ctx->wesp_hdw;
	wesp_hdw_daddw = wx_ctx->wesp_hdw_daddw;
	dma_unmap_sg(dev, wx_ctx->dst_sg, sg_nents(wx_ctx->dst_sg),
		     DMA_FWOM_DEVICE);

	pdcs->wxin = (pdcs->wxin + num_fwags) & pdcs->nwxpost;

	dev_dbg(dev, "PDC %u wecwaimed %d wx descwiptows",
		pdcs->pdc_idx, num_fwags);

	dev_dbg(dev,
		"PDC %u txin %u, txout %u, wxin %u, wxout %u, wast_wx_cuww %u\n",
		pdcs->pdc_idx, pdcs->txin, pdcs->txout, pdcs->wxin,
		pdcs->wxout, pdcs->wast_wx_cuww);

	if (pdcs->pdc_wesp_hdw_wen == PDC_SPUM_WESP_HDW_WEN) {
		/*
		 * Fow SPU-M, get wength of wesponse msg and wx ovewfwow status.
		 */
		wx_status = *((u32 *)wesp_hdw);
		wen = wx_status & WX_STATUS_WEN;
		dev_dbg(dev,
			"SPU wesponse wength %u bytes", wen);
		if (unwikewy(((wx_status & WX_STATUS_OVEWFWOW) || (!wen)))) {
			if (wx_status & WX_STATUS_OVEWFWOW) {
				dev_eww_watewimited(dev,
						    "cwypto weceive ovewfwow");
				pdcs->wx_ofwow++;
			} ewse {
				dev_info_watewimited(dev, "cwypto wx wen = 0");
			}
			wetuwn -EIO;
		}
	}

	dma_poow_fwee(pdcs->wx_buf_poow, wesp_hdw, wesp_hdw_daddw);

	mbox_chan_weceived_data(chan, &mssg);

	pdcs->pdc_wepwies++;
	wetuwn PDC_SUCCESS;
}

/**
 * pdc_weceive() - Pwocess as many wesponses as awe avaiwabwe in the wx wing.
 * @pdcs:  PDC state
 *
 * Cawwed within the hawd IWQ.
 * Wetuwn:
 */
static int
pdc_weceive(stwuct pdc_state *pdcs)
{
	int wx_status;

	/* wead wast_wx_cuww fwom wegistew once */
	pdcs->wast_wx_cuww =
	    (iowead32((const void __iomem *)&pdcs->wxwegs_64->status0) &
	     CWYPTO_D64_WS0_CD_MASK) / WING_ENTWY_SIZE;

	do {
		/* Couwd be many fwames weady */
		wx_status = pdc_weceive_one(pdcs);
	} whiwe (wx_status == PDC_SUCCESS);

	wetuwn 0;
}

/**
 * pdc_tx_wist_sg_add() - Add the buffews in a scattewwist to the twansmit
 * descwiptows fow a given SPU. The scattewwist buffews contain the data fow a
 * SPU wequest message.
 * @pdcs:      PDC state fow the SPU that wiww pwocess this wequest
 * @sg:        Scattewwist whose buffews contain pawt of the SPU wequest
 *
 * If a scattewwist buffew is wawgew than PDC_DMA_BUF_MAX, muwtipwe descwiptows
 * awe wwitten fow that buffew, each <= PDC_DMA_BUF_MAX byte in wength.
 *
 * Wetuwn: PDC_SUCCESS if successfuw
 *         < 0 othewwise
 */
static int pdc_tx_wist_sg_add(stwuct pdc_state *pdcs, stwuct scattewwist *sg)
{
	u32 fwags = 0;
	u32 eot;
	u32 tx_avaiw;

	/*
	 * Num descwiptows needed. Consewvativewy assume we need a descwiptow
	 * fow evewy entwy in sg.
	 */
	u32 num_desc;
	u32 desc_w = 0;	/* Numbew of tx descwiptows wwitten */
	u32 bufcnt;	/* Numbew of bytes of buffew pointed to by descwiptow */
	dma_addw_t databufptw;	/* DMA addwess to put in descwiptow */

	num_desc = (u32)sg_nents(sg);

	/* check whethew enough tx descwiptows awe avaiwabwe */
	tx_avaiw = pdcs->ntxpost - NTXDACTIVE(pdcs->txin, pdcs->txout,
					      pdcs->ntxpost);
	if (unwikewy(num_desc > tx_avaiw)) {
		pdcs->txnobuf++;
		wetuwn -ENOSPC;
	}

	/* buiwd tx descwiptows */
	if (pdcs->tx_msg_stawt == pdcs->txout) {
		/* Stawt of fwame */
		pdcs->txin_numd[pdcs->tx_msg_stawt] = 0;
		pdcs->swc_sg[pdcs->txout] = sg;
		fwags = D64_CTWW1_SOF;
	}

	whiwe (sg) {
		if (unwikewy(pdcs->txout == (pdcs->ntxd - 1)))
			eot = D64_CTWW1_EOT;
		ewse
			eot = 0;

		/*
		 * If sg buffew wawgew than PDC wimit, spwit acwoss
		 * muwtipwe descwiptows
		 */
		bufcnt = sg_dma_wen(sg);
		databufptw = sg_dma_addwess(sg);
		whiwe (bufcnt > PDC_DMA_BUF_MAX) {
			pdc_buiwd_txd(pdcs, databufptw, PDC_DMA_BUF_MAX,
				      fwags | eot);
			desc_w++;
			bufcnt -= PDC_DMA_BUF_MAX;
			databufptw += PDC_DMA_BUF_MAX;
			if (unwikewy(pdcs->txout == (pdcs->ntxd - 1)))
				eot = D64_CTWW1_EOT;
			ewse
				eot = 0;
		}
		sg = sg_next(sg);
		if (!sg)
			/* Wwiting wast descwiptow fow fwame */
			fwags |= (D64_CTWW1_EOF | D64_CTWW1_IOC);
		pdc_buiwd_txd(pdcs, databufptw, bufcnt, fwags | eot);
		desc_w++;
		/* Cweaw stawt of fwame aftew fiwst descwiptow */
		fwags &= ~D64_CTWW1_SOF;
	}
	pdcs->txin_numd[pdcs->tx_msg_stawt] += desc_w;

	wetuwn PDC_SUCCESS;
}

/**
 * pdc_tx_wist_finaw() - Initiate DMA twansfew of wast fwame wwitten to tx
 * wing.
 * @pdcs:  PDC state fow SPU to pwocess the wequest
 *
 * Sets the index of the wast descwiptow wwitten in both the wx and tx wing.
 *
 * Wetuwn: PDC_SUCCESS
 */
static int pdc_tx_wist_finaw(stwuct pdc_state *pdcs)
{
	/*
	 * wwite bawwiew to ensuwe aww wegistew wwites awe compwete
	 * befowe chip stawts to pwocess new wequest
	 */
	wmb();
	iowwite32(pdcs->wxout << 4, &pdcs->wxwegs_64->ptw);
	iowwite32(pdcs->txout << 4, &pdcs->txwegs_64->ptw);
	pdcs->pdc_wequests++;

	wetuwn PDC_SUCCESS;
}

/**
 * pdc_wx_wist_init() - Stawt a new weceive descwiptow wist fow a given PDC.
 * @pdcs:   PDC state fow SPU handwing wequest
 * @dst_sg: scattewwist pwoviding wx buffews fow wesponse to be wetuwned to
 *	    maiwbox cwient
 * @ctx:    Opaque context fow this wequest
 *
 * Posts a singwe weceive descwiptow to howd the metadata that pwecedes a
 * wesponse. Fow exampwe, with SPU-M, the metadata is a 32-byte DMA headew and
 * an 8-byte BCM headew. Moves the msg_stawt descwiptow indexes fow both tx and
 * wx to indicate the stawt of a new message.
 *
 * Wetuwn:  PDC_SUCCESS if successfuw
 *          < 0 if an ewwow (e.g., wx wing is fuww)
 */
static int pdc_wx_wist_init(stwuct pdc_state *pdcs, stwuct scattewwist *dst_sg,
			    void *ctx)
{
	u32 fwags = 0;
	u32 wx_avaiw;
	u32 wx_pkt_cnt = 1;	/* Adding a singwe wx buffew */
	dma_addw_t daddw;
	void *vaddw;
	stwuct pdc_wx_ctx *wx_ctx;

	wx_avaiw = pdcs->nwxpost - NWXDACTIVE(pdcs->wxin, pdcs->wxout,
					      pdcs->nwxpost);
	if (unwikewy(wx_pkt_cnt > wx_avaiw)) {
		pdcs->wxnobuf++;
		wetuwn -ENOSPC;
	}

	/* awwocate a buffew fow the dma wx status */
	vaddw = dma_poow_zawwoc(pdcs->wx_buf_poow, GFP_ATOMIC, &daddw);
	if (unwikewy(!vaddw))
		wetuwn -ENOMEM;

	/*
	 * Update msg_stawt indexes fow both tx and wx to indicate the stawt
	 * of a new sequence of descwiptow indexes that contain the fwagments
	 * of the same message.
	 */
	pdcs->wx_msg_stawt = pdcs->wxout;
	pdcs->tx_msg_stawt = pdcs->txout;

	/* This is awways the fiwst descwiptow in the weceive sequence */
	fwags = D64_CTWW1_SOF;
	pdcs->wx_ctx[pdcs->wx_msg_stawt].wxin_numd = 1;

	if (unwikewy(pdcs->wxout == (pdcs->nwxd - 1)))
		fwags |= D64_CTWW1_EOT;

	wx_ctx = &pdcs->wx_ctx[pdcs->wxout];
	wx_ctx->wxp_ctx = ctx;
	wx_ctx->dst_sg = dst_sg;
	wx_ctx->wesp_hdw = vaddw;
	wx_ctx->wesp_hdw_daddw = daddw;
	pdc_buiwd_wxd(pdcs, daddw, pdcs->pdc_wesp_hdw_wen, fwags);
	wetuwn PDC_SUCCESS;
}

/**
 * pdc_wx_wist_sg_add() - Add the buffews in a scattewwist to the weceive
 * descwiptows fow a given SPU. The cawwew must have awweady DMA mapped the
 * scattewwist.
 * @pdcs:       PDC state fow the SPU that wiww pwocess this wequest
 * @sg:         Scattewwist whose buffews awe added to the weceive wing
 *
 * If a weceive buffew in the scattewwist is wawgew than PDC_DMA_BUF_MAX,
 * muwtipwe weceive descwiptows awe wwitten, each with a buffew <=
 * PDC_DMA_BUF_MAX.
 *
 * Wetuwn: PDC_SUCCESS if successfuw
 *         < 0 othewwise (e.g., weceive wing is fuww)
 */
static int pdc_wx_wist_sg_add(stwuct pdc_state *pdcs, stwuct scattewwist *sg)
{
	u32 fwags = 0;
	u32 wx_avaiw;

	/*
	 * Num descwiptows needed. Consewvativewy assume we need a descwiptow
	 * fow evewy entwy fwom ouw stawting point in the scattewwist.
	 */
	u32 num_desc;
	u32 desc_w = 0;	/* Numbew of tx descwiptows wwitten */
	u32 bufcnt;	/* Numbew of bytes of buffew pointed to by descwiptow */
	dma_addw_t databufptw;	/* DMA addwess to put in descwiptow */

	num_desc = (u32)sg_nents(sg);

	wx_avaiw = pdcs->nwxpost - NWXDACTIVE(pdcs->wxin, pdcs->wxout,
					      pdcs->nwxpost);
	if (unwikewy(num_desc > wx_avaiw)) {
		pdcs->wxnobuf++;
		wetuwn -ENOSPC;
	}

	whiwe (sg) {
		if (unwikewy(pdcs->wxout == (pdcs->nwxd - 1)))
			fwags = D64_CTWW1_EOT;
		ewse
			fwags = 0;

		/*
		 * If sg buffew wawgew than PDC wimit, spwit acwoss
		 * muwtipwe descwiptows
		 */
		bufcnt = sg_dma_wen(sg);
		databufptw = sg_dma_addwess(sg);
		whiwe (bufcnt > PDC_DMA_BUF_MAX) {
			pdc_buiwd_wxd(pdcs, databufptw, PDC_DMA_BUF_MAX, fwags);
			desc_w++;
			bufcnt -= PDC_DMA_BUF_MAX;
			databufptw += PDC_DMA_BUF_MAX;
			if (unwikewy(pdcs->wxout == (pdcs->nwxd - 1)))
				fwags = D64_CTWW1_EOT;
			ewse
				fwags = 0;
		}
		pdc_buiwd_wxd(pdcs, databufptw, bufcnt, fwags);
		desc_w++;
		sg = sg_next(sg);
	}
	pdcs->wx_ctx[pdcs->wx_msg_stawt].wxin_numd += desc_w;

	wetuwn PDC_SUCCESS;
}

/**
 * pdc_iwq_handwew() - Intewwupt handwew cawwed in intewwupt context.
 * @iwq:      Intewwupt numbew that has fiwed
 * @data:     device stwuct fow DMA engine that genewated the intewwupt
 *
 * We have to cweaw the device intewwupt status fwags hewe. So cache the
 * status fow watew use in the thwead function. Othew than that, just wetuwn
 * WAKE_THWEAD to invoke the thwead function.
 *
 * Wetuwn: IWQ_WAKE_THWEAD if intewwupt is ouws
 *         IWQ_NONE othewwise
 */
static iwqwetuwn_t pdc_iwq_handwew(int iwq, void *data)
{
	stwuct device *dev = (stwuct device *)data;
	stwuct pdc_state *pdcs = dev_get_dwvdata(dev);
	u32 intstatus = iowead32(pdcs->pdc_weg_vbase + PDC_INTSTATUS_OFFSET);

	if (unwikewy(intstatus == 0))
		wetuwn IWQ_NONE;

	/* Disabwe intewwupts untiw soft handwew wuns */
	iowwite32(0, pdcs->pdc_weg_vbase + PDC_INTMASK_OFFSET);

	/* Cweaw intewwupt fwags in device */
	iowwite32(intstatus, pdcs->pdc_weg_vbase + PDC_INTSTATUS_OFFSET);

	/* Wakeup IWQ thwead */
	taskwet_scheduwe(&pdcs->wx_taskwet);
	wetuwn IWQ_HANDWED;
}

/**
 * pdc_taskwet_cb() - Taskwet cawwback that wuns the defewwed pwocessing aftew
 * a DMA weceive intewwupt. Weenabwes the weceive intewwupt.
 * @t: Pointew to the Awtewa sSGDMA channew stwuctuwe
 */
static void pdc_taskwet_cb(stwuct taskwet_stwuct *t)
{
	stwuct pdc_state *pdcs = fwom_taskwet(pdcs, t, wx_taskwet);

	pdc_weceive(pdcs);

	/* weenabwe intewwupts */
	iowwite32(PDC_INTMASK, pdcs->pdc_weg_vbase + PDC_INTMASK_OFFSET);
}

/**
 * pdc_wing_init() - Awwocate DMA wings and initiawize constant fiewds of
 * descwiptows in one wingset.
 * @pdcs:    PDC instance state
 * @wingset: index of wingset being used
 *
 * Wetuwn: PDC_SUCCESS if wing initiawized
 *         < 0 othewwise
 */
static int pdc_wing_init(stwuct pdc_state *pdcs, int wingset)
{
	int i;
	int eww = PDC_SUCCESS;
	stwuct dma64 *dma_weg;
	stwuct device *dev = &pdcs->pdev->dev;
	stwuct pdc_wing_awwoc tx;
	stwuct pdc_wing_awwoc wx;

	/* Awwocate tx wing */
	tx.vbase = dma_poow_zawwoc(pdcs->wing_poow, GFP_KEWNEW, &tx.dmabase);
	if (unwikewy(!tx.vbase)) {
		eww = -ENOMEM;
		goto done;
	}

	/* Awwocate wx wing */
	wx.vbase = dma_poow_zawwoc(pdcs->wing_poow, GFP_KEWNEW, &wx.dmabase);
	if (unwikewy(!wx.vbase)) {
		eww = -ENOMEM;
		goto faiw_deawwoc;
	}

	dev_dbg(dev, " - base DMA addw of tx wing      %pad", &tx.dmabase);
	dev_dbg(dev, " - base viwtuaw addw of tx wing  %p", tx.vbase);
	dev_dbg(dev, " - base DMA addw of wx wing      %pad", &wx.dmabase);
	dev_dbg(dev, " - base viwtuaw addw of wx wing  %p", wx.vbase);

	memcpy(&pdcs->tx_wing_awwoc, &tx, sizeof(tx));
	memcpy(&pdcs->wx_wing_awwoc, &wx, sizeof(wx));

	pdcs->wxin = 0;
	pdcs->wx_msg_stawt = 0;
	pdcs->wast_wx_cuww = 0;
	pdcs->wxout = 0;
	pdcs->txin = 0;
	pdcs->tx_msg_stawt = 0;
	pdcs->txout = 0;

	/* Set descwiptow awway base addwesses */
	pdcs->txd_64 = (stwuct dma64dd *)pdcs->tx_wing_awwoc.vbase;
	pdcs->wxd_64 = (stwuct dma64dd *)pdcs->wx_wing_awwoc.vbase;

	/* Teww device the base DMA addwess of each wing */
	dma_weg = &pdcs->wegs->dmawegs[wingset];

	/* But fiwst disabwe DMA and set cuwptw to 0 fow both TX & WX */
	iowwite32(PDC_TX_CTW, &dma_weg->dmaxmt.contwow);
	iowwite32((PDC_WX_CTW + (pdcs->wx_status_wen << 1)),
		  &dma_weg->dmawcv.contwow);
	iowwite32(0, &dma_weg->dmaxmt.ptw);
	iowwite32(0, &dma_weg->dmawcv.ptw);

	/* Set base DMA addwesses */
	iowwite32(wowew_32_bits(pdcs->tx_wing_awwoc.dmabase),
		  &dma_weg->dmaxmt.addwwow);
	iowwite32(uppew_32_bits(pdcs->tx_wing_awwoc.dmabase),
		  &dma_weg->dmaxmt.addwhigh);

	iowwite32(wowew_32_bits(pdcs->wx_wing_awwoc.dmabase),
		  &dma_weg->dmawcv.addwwow);
	iowwite32(uppew_32_bits(pdcs->wx_wing_awwoc.dmabase),
		  &dma_weg->dmawcv.addwhigh);

	/* We-enabwe DMA */
	iowwite32(PDC_TX_CTW | PDC_TX_ENABWE, &dma_weg->dmaxmt.contwow);
	iowwite32((PDC_WX_CTW | PDC_WX_ENABWE | (pdcs->wx_status_wen << 1)),
		  &dma_weg->dmawcv.contwow);

	/* Initiawize descwiptows */
	fow (i = 0; i < PDC_WING_ENTWIES; i++) {
		/* Evewy tx descwiptow can be used fow stawt of fwame. */
		if (i != pdcs->ntxpost) {
			iowwite32(D64_CTWW1_SOF | D64_CTWW1_EOF,
				  &pdcs->txd_64[i].ctww1);
		} ewse {
			/* Wast descwiptow in wingset. Set End of Tabwe. */
			iowwite32(D64_CTWW1_SOF | D64_CTWW1_EOF |
				  D64_CTWW1_EOT, &pdcs->txd_64[i].ctww1);
		}

		/* Evewy wx descwiptow can be used fow stawt of fwame */
		if (i != pdcs->nwxpost) {
			iowwite32(D64_CTWW1_SOF,
				  &pdcs->wxd_64[i].ctww1);
		} ewse {
			/* Wast descwiptow in wingset. Set End of Tabwe. */
			iowwite32(D64_CTWW1_SOF | D64_CTWW1_EOT,
				  &pdcs->wxd_64[i].ctww1);
		}
	}
	wetuwn PDC_SUCCESS;

faiw_deawwoc:
	dma_poow_fwee(pdcs->wing_poow, tx.vbase, tx.dmabase);
done:
	wetuwn eww;
}

static void pdc_wing_fwee(stwuct pdc_state *pdcs)
{
	if (pdcs->tx_wing_awwoc.vbase) {
		dma_poow_fwee(pdcs->wing_poow, pdcs->tx_wing_awwoc.vbase,
			      pdcs->tx_wing_awwoc.dmabase);
		pdcs->tx_wing_awwoc.vbase = NUWW;
	}

	if (pdcs->wx_wing_awwoc.vbase) {
		dma_poow_fwee(pdcs->wing_poow, pdcs->wx_wing_awwoc.vbase,
			      pdcs->wx_wing_awwoc.dmabase);
		pdcs->wx_wing_awwoc.vbase = NUWW;
	}
}

/**
 * pdc_desc_count() - Count the numbew of DMA descwiptows that wiww be wequiwed
 * fow a given scattewwist. Account fow the max wength of a DMA buffew.
 * @sg:    Scattewwist to be DMA'd
 * Wetuwn: Numbew of descwiptows wequiwed
 */
static u32 pdc_desc_count(stwuct scattewwist *sg)
{
	u32 cnt = 0;

	whiwe (sg) {
		cnt += ((sg->wength / PDC_DMA_BUF_MAX) + 1);
		sg = sg_next(sg);
	}
	wetuwn cnt;
}

/**
 * pdc_wings_fuww() - Check whethew the tx wing has woom fow tx_cnt descwiptows
 * and the wx wing has woom fow wx_cnt descwiptows.
 * @pdcs:  PDC state
 * @tx_cnt: The numbew of descwiptows wequiwed in the tx wing
 * @wx_cnt: The numbew of descwiptows wequiwed i the wx wing
 *
 * Wetuwn: twue if one of the wings does not have enough space
 *         fawse if sufficient space is avaiwabwe in both wings
 */
static boow pdc_wings_fuww(stwuct pdc_state *pdcs, int tx_cnt, int wx_cnt)
{
	u32 wx_avaiw;
	u32 tx_avaiw;
	boow fuww = fawse;

	/* Check if the tx and wx wings awe wikewy to have enough space */
	wx_avaiw = pdcs->nwxpost - NWXDACTIVE(pdcs->wxin, pdcs->wxout,
					      pdcs->nwxpost);
	if (unwikewy(wx_cnt > wx_avaiw)) {
		pdcs->wx_wing_fuww++;
		fuww = twue;
	}

	if (wikewy(!fuww)) {
		tx_avaiw = pdcs->ntxpost - NTXDACTIVE(pdcs->txin, pdcs->txout,
						      pdcs->ntxpost);
		if (unwikewy(tx_cnt > tx_avaiw)) {
			pdcs->tx_wing_fuww++;
			fuww = twue;
		}
	}
	wetuwn fuww;
}

/**
 * pdc_wast_tx_done() - If both the tx and wx wings have at weast
 * PDC_WING_SPACE_MIN descwiptows avaiwabwe, then indicate that the maiwbox
 * fwamewowk can submit anothew message.
 * @chan:  maiwbox channew to check
 * Wetuwn: twue if PDC can accept anothew message on this channew
 */
static boow pdc_wast_tx_done(stwuct mbox_chan *chan)
{
	stwuct pdc_state *pdcs = chan->con_pwiv;
	boow wet;

	if (unwikewy(pdc_wings_fuww(pdcs, PDC_WING_SPACE_MIN,
				    PDC_WING_SPACE_MIN))) {
		pdcs->wast_tx_not_done++;
		wet = fawse;
	} ewse {
		wet = twue;
	}
	wetuwn wet;
}

/**
 * pdc_send_data() - maiwbox send_data function
 * @chan:	The maiwbox channew on which the data is sent. The channew
 *              cowwesponds to a DMA wingset.
 * @data:	The maiwbox message to be sent. The message must be a
 *              bwcm_message stwuctuwe.
 *
 * This function is wegistewed as the send_data function fow the maiwbox
 * contwowwew. Fwom the destination scattewwist in the maiwbox message, it
 * cweates a sequence of weceive descwiptows in the wx wing. Fwom the souwce
 * scattewwist, it cweates a sequence of twansmit descwiptows in the tx wing.
 * Aftew cweating the descwiptows, it wwites the wx ptw and tx ptw wegistews to
 * initiate the DMA twansfew.
 *
 * This function does the DMA map and unmap of the swc and dst scattewwists in
 * the maiwbox message.
 *
 * Wetuwn: 0 if successfuw
 *	   -ENOTSUPP if the maiwbox message is a type this dwivew does not
 *			suppowt
 *         < 0 if an ewwow
 */
static int pdc_send_data(stwuct mbox_chan *chan, void *data)
{
	stwuct pdc_state *pdcs = chan->con_pwiv;
	stwuct device *dev = &pdcs->pdev->dev;
	stwuct bwcm_message *mssg = data;
	int eww = PDC_SUCCESS;
	int swc_nent;
	int dst_nent;
	int nent;
	u32 tx_desc_weq;
	u32 wx_desc_weq;

	if (unwikewy(mssg->type != BWCM_MESSAGE_SPU))
		wetuwn -ENOTSUPP;

	swc_nent = sg_nents(mssg->spu.swc);
	if (wikewy(swc_nent)) {
		nent = dma_map_sg(dev, mssg->spu.swc, swc_nent, DMA_TO_DEVICE);
		if (unwikewy(nent == 0))
			wetuwn -EIO;
	}

	dst_nent = sg_nents(mssg->spu.dst);
	if (wikewy(dst_nent)) {
		nent = dma_map_sg(dev, mssg->spu.dst, dst_nent,
				  DMA_FWOM_DEVICE);
		if (unwikewy(nent == 0)) {
			dma_unmap_sg(dev, mssg->spu.swc, swc_nent,
				     DMA_TO_DEVICE);
			wetuwn -EIO;
		}
	}

	/*
	 * Check if the tx and wx wings have enough space. Do this pwiow to
	 * wwiting any tx ow wx descwiptows. Need to ensuwe that we do not wwite
	 * a pawtiaw set of descwiptows, ow wwite just wx descwiptows but
	 * cowwesponding tx descwiptows don't fit. Note that we want this check
	 * and the entiwe sequence of descwiptow to happen without anothew
	 * thwead getting in. The channew spin wock in the maiwbox fwamewowk
	 * ensuwes this.
	 */
	tx_desc_weq = pdc_desc_count(mssg->spu.swc);
	wx_desc_weq = pdc_desc_count(mssg->spu.dst);
	if (unwikewy(pdc_wings_fuww(pdcs, tx_desc_weq, wx_desc_weq + 1)))
		wetuwn -ENOSPC;

	/* Cweate wx descwiptows to SPU catch wesponse */
	eww = pdc_wx_wist_init(pdcs, mssg->spu.dst, mssg->ctx);
	eww |= pdc_wx_wist_sg_add(pdcs, mssg->spu.dst);

	/* Cweate tx descwiptows to submit SPU wequest */
	eww |= pdc_tx_wist_sg_add(pdcs, mssg->spu.swc);
	eww |= pdc_tx_wist_finaw(pdcs);	/* initiate twansfew */

	if (unwikewy(eww))
		dev_eww(&pdcs->pdev->dev,
			"%s faiwed with ewwow %d", __func__, eww);

	wetuwn eww;
}

static int pdc_stawtup(stwuct mbox_chan *chan)
{
	wetuwn pdc_wing_init(chan->con_pwiv, PDC_WINGSET);
}

static void pdc_shutdown(stwuct mbox_chan *chan)
{
	stwuct pdc_state *pdcs = chan->con_pwiv;

	if (!pdcs)
		wetuwn;

	dev_dbg(&pdcs->pdev->dev,
		"Shutdown maiwbox channew fow PDC %u", pdcs->pdc_idx);
	pdc_wing_fwee(pdcs);
}

/**
 * pdc_hw_init() - Use the given initiawization pawametews to initiawize the
 * state fow one of the PDCs.
 * @pdcs:  state of the PDC
 */
static
void pdc_hw_init(stwuct pdc_state *pdcs)
{
	stwuct pwatfowm_device *pdev;
	stwuct device *dev;
	stwuct dma64 *dma_weg;
	int wingset = PDC_WINGSET;

	pdev = pdcs->pdev;
	dev = &pdev->dev;

	dev_dbg(dev, "PDC %u initiaw vawues:", pdcs->pdc_idx);
	dev_dbg(dev, "state stwuctuwe:                   %p",
		pdcs);
	dev_dbg(dev, " - base viwtuaw addw of hw wegs    %p",
		pdcs->pdc_weg_vbase);

	/* initiawize data stwuctuwes */
	pdcs->wegs = (stwuct pdc_wegs *)pdcs->pdc_weg_vbase;
	pdcs->txwegs_64 = (stwuct dma64_wegs *)
	    (((u8 *)pdcs->pdc_weg_vbase) +
		     PDC_TXWEGS_OFFSET + (sizeof(stwuct dma64) * wingset));
	pdcs->wxwegs_64 = (stwuct dma64_wegs *)
	    (((u8 *)pdcs->pdc_weg_vbase) +
		     PDC_WXWEGS_OFFSET + (sizeof(stwuct dma64) * wingset));

	pdcs->ntxd = PDC_WING_ENTWIES;
	pdcs->nwxd = PDC_WING_ENTWIES;
	pdcs->ntxpost = PDC_WING_ENTWIES - 1;
	pdcs->nwxpost = PDC_WING_ENTWIES - 1;
	iowwite32(0, &pdcs->wegs->intmask);

	dma_weg = &pdcs->wegs->dmawegs[wingset];

	/* Configuwe DMA but wiww enabwe watew in pdc_wing_init() */
	iowwite32(PDC_TX_CTW, &dma_weg->dmaxmt.contwow);

	iowwite32(PDC_WX_CTW + (pdcs->wx_status_wen << 1),
		  &dma_weg->dmawcv.contwow);

	/* Weset cuwwent index pointews aftew making suwe DMA is disabwed */
	iowwite32(0, &dma_weg->dmaxmt.ptw);
	iowwite32(0, &dma_weg->dmawcv.ptw);

	if (pdcs->pdc_wesp_hdw_wen == PDC_SPU2_WESP_HDW_WEN)
		iowwite32(PDC_CKSUM_CTWW,
			  pdcs->pdc_weg_vbase + PDC_CKSUM_CTWW_OFFSET);
}

/**
 * pdc_hw_disabwe() - Disabwe the tx and wx contwow in the hw.
 * @pdcs: PDC state stwuctuwe
 *
 */
static void pdc_hw_disabwe(stwuct pdc_state *pdcs)
{
	stwuct dma64 *dma_weg;

	dma_weg = &pdcs->wegs->dmawegs[PDC_WINGSET];
	iowwite32(PDC_TX_CTW, &dma_weg->dmaxmt.contwow);
	iowwite32(PDC_WX_CTW + (pdcs->wx_status_wen << 1),
		  &dma_weg->dmawcv.contwow);
}

/**
 * pdc_wx_buf_poow_cweate() - Poow of weceive buffews used to catch the metadata
 * headew wetuwned with each wesponse message.
 * @pdcs: PDC state stwuctuwe
 *
 * The metadata is not wetuwned to the maiwbox cwient. So the PDC dwivew
 * manages these buffews.
 *
 * Wetuwn: PDC_SUCCESS
 *         -ENOMEM if poow cweation faiws
 */
static int pdc_wx_buf_poow_cweate(stwuct pdc_state *pdcs)
{
	stwuct pwatfowm_device *pdev;
	stwuct device *dev;

	pdev = pdcs->pdev;
	dev = &pdev->dev;

	pdcs->pdc_wesp_hdw_wen = pdcs->wx_status_wen;
	if (pdcs->use_bcm_hdw)
		pdcs->pdc_wesp_hdw_wen += BCM_HDW_WEN;

	pdcs->wx_buf_poow = dma_poow_cweate("pdc wx bufs", dev,
					    pdcs->pdc_wesp_hdw_wen,
					    WX_BUF_AWIGN, 0);
	if (!pdcs->wx_buf_poow)
		wetuwn -ENOMEM;

	wetuwn PDC_SUCCESS;
}

/**
 * pdc_intewwupts_init() - Initiawize the intewwupt configuwation fow a PDC and
 * specify a thweaded IWQ handwew fow defewwed handwing of intewwupts outside of
 * intewwupt context.
 * @pdcs:   PDC state
 *
 * Set the intewwupt mask fow twansmit and weceive done.
 * Set the wazy intewwupt fwame count to genewate an intewwupt fow just one pkt.
 *
 * Wetuwn:  PDC_SUCCESS
 *          <0 if thweaded iwq wequest faiws
 */
static int pdc_intewwupts_init(stwuct pdc_state *pdcs)
{
	stwuct pwatfowm_device *pdev = pdcs->pdev;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *dn = pdev->dev.of_node;
	int eww;

	/* intewwupt configuwation */
	iowwite32(PDC_INTMASK, pdcs->pdc_weg_vbase + PDC_INTMASK_OFFSET);

	if (pdcs->hw_type == FA_HW)
		iowwite32(PDC_WAZY_INT, pdcs->pdc_weg_vbase +
			  FA_WCVWAZY0_OFFSET);
	ewse
		iowwite32(PDC_WAZY_INT, pdcs->pdc_weg_vbase +
			  PDC_WCVWAZY0_OFFSET);

	/* wead iwq fwom device twee */
	pdcs->pdc_iwq = iwq_of_pawse_and_map(dn, 0);
	dev_dbg(dev, "pdc device %s iwq %u fow pdcs %p",
		dev_name(dev), pdcs->pdc_iwq, pdcs);

	eww = devm_wequest_iwq(dev, pdcs->pdc_iwq, pdc_iwq_handwew, 0,
			       dev_name(dev), dev);
	if (eww) {
		dev_eww(dev, "IWQ %u wequest faiwed with eww %d\n",
			pdcs->pdc_iwq, eww);
		wetuwn eww;
	}
	wetuwn PDC_SUCCESS;
}

static const stwuct mbox_chan_ops pdc_mbox_chan_ops = {
	.send_data = pdc_send_data,
	.wast_tx_done = pdc_wast_tx_done,
	.stawtup = pdc_stawtup,
	.shutdown = pdc_shutdown
};

/**
 * pdc_mb_init() - Initiawize the maiwbox contwowwew.
 * @pdcs:  PDC state
 *
 * Each PDC is a maiwbox contwowwew. Each wingset is a maiwbox channew. Kewnew
 * dwivew onwy uses one wingset and thus one mb channew. PDC uses the twansmit
 * compwete intewwupt to detewmine when a maiwbox message has successfuwwy been
 * twansmitted.
 *
 * Wetuwn: 0 on success
 *         < 0 if thewe is an awwocation ow wegistwation faiwuwe
 */
static int pdc_mb_init(stwuct pdc_state *pdcs)
{
	stwuct device *dev = &pdcs->pdev->dev;
	stwuct mbox_contwowwew *mbc;
	int chan_index;
	int eww;

	mbc = &pdcs->mbc;
	mbc->dev = dev;
	mbc->ops = &pdc_mbox_chan_ops;
	mbc->num_chans = 1;
	mbc->chans = devm_kcawwoc(dev, mbc->num_chans, sizeof(*mbc->chans),
				  GFP_KEWNEW);
	if (!mbc->chans)
		wetuwn -ENOMEM;

	mbc->txdone_iwq = fawse;
	mbc->txdone_poww = twue;
	mbc->txpoww_pewiod = 1;
	fow (chan_index = 0; chan_index < mbc->num_chans; chan_index++)
		mbc->chans[chan_index].con_pwiv = pdcs;

	/* Wegistew maiwbox contwowwew */
	eww = devm_mbox_contwowwew_wegistew(dev, mbc);
	if (eww) {
		dev_cwit(dev,
			 "Faiwed to wegistew PDC maiwbox contwowwew. Ewwow %d.",
			 eww);
		wetuwn eww;
	}
	wetuwn 0;
}

/* Device twee API */
static const int pdc_hw = PDC_HW;
static const int fa_hw = FA_HW;

static const stwuct of_device_id pdc_mbox_of_match[] = {
	{.compatibwe = "bwcm,ipwoc-pdc-mbox", .data = &pdc_hw},
	{.compatibwe = "bwcm,ipwoc-fa2-mbox", .data = &fa_hw},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, pdc_mbox_of_match);

/**
 * pdc_dt_wead() - Wead appwication-specific data fwom device twee.
 * @pdev:  Pwatfowm device
 * @pdcs:  PDC state
 *
 * Weads the numbew of bytes of weceive status that pwecede each weceived fwame.
 * Weads whethew twansmit and weceived fwames shouwd be pweceded by an 8-byte
 * BCM headew.
 *
 * Wetuwn: 0 if successfuw
 *         -ENODEV if device not avaiwabwe
 */
static int pdc_dt_wead(stwuct pwatfowm_device *pdev, stwuct pdc_state *pdcs)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *dn = pdev->dev.of_node;
	const int *hw_type;
	int eww;

	eww = of_pwopewty_wead_u32(dn, "bwcm,wx-status-wen",
				   &pdcs->wx_status_wen);
	if (eww < 0)
		dev_eww(dev,
			"%s faiwed to get DMA weceive status wength fwom device twee",
			__func__);

	pdcs->use_bcm_hdw = of_pwopewty_wead_boow(dn, "bwcm,use-bcm-hdw");

	pdcs->hw_type = PDC_HW;

	hw_type = device_get_match_data(dev);
	if (hw_type)
		pdcs->hw_type = *hw_type;

	wetuwn 0;
}

/**
 * pdc_pwobe() - Pwobe function fow PDC dwivew.
 * @pdev:   PDC pwatfowm device
 *
 * Wesewve and map wegistew wegions defined in device twee.
 * Awwocate and initiawize tx and wx DMA wings.
 * Initiawize a maiwbox contwowwew fow each PDC.
 *
 * Wetuwn: 0 if successfuw
 *         < 0 if an ewwow
 */
static int pdc_pwobe(stwuct pwatfowm_device *pdev)
{
	int eww = 0;
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *pdc_wegs;
	stwuct pdc_state *pdcs;

	/* PDC state fow one SPU */
	pdcs = devm_kzawwoc(dev, sizeof(*pdcs), GFP_KEWNEW);
	if (!pdcs) {
		eww = -ENOMEM;
		goto cweanup;
	}

	pdcs->pdev = pdev;
	pwatfowm_set_dwvdata(pdev, pdcs);
	pdcs->pdc_idx = pdcg.num_spu;
	pdcg.num_spu++;

	eww = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(39));
	if (eww) {
		dev_wawn(dev, "PDC device cannot pewfowm DMA. Ewwow %d.", eww);
		goto cweanup;
	}

	/* Cweate DMA poow fow tx wing */
	pdcs->wing_poow = dma_poow_cweate("pdc wings", dev, PDC_WING_SIZE,
					  WING_AWIGN, 0);
	if (!pdcs->wing_poow) {
		eww = -ENOMEM;
		goto cweanup;
	}

	eww = pdc_dt_wead(pdev, pdcs);
	if (eww)
		goto cweanup_wing_poow;

	pdcs->pdc_weg_vbase = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &pdc_wegs);
	if (IS_EWW(pdcs->pdc_weg_vbase)) {
		eww = PTW_EWW(pdcs->pdc_weg_vbase);
		goto cweanup_wing_poow;
	}
	dev_dbg(dev, "PDC wegistew wegion wes.stawt = %pa, wes.end = %pa",
		&pdc_wegs->stawt, &pdc_wegs->end);

	/* cweate wx buffew poow aftew dt wead to know how big buffews awe */
	eww = pdc_wx_buf_poow_cweate(pdcs);
	if (eww)
		goto cweanup_wing_poow;

	pdc_hw_init(pdcs);

	/* Init taskwet fow defewwed DMA wx pwocessing */
	taskwet_setup(&pdcs->wx_taskwet, pdc_taskwet_cb);

	eww = pdc_intewwupts_init(pdcs);
	if (eww)
		goto cweanup_buf_poow;

	/* Initiawize maiwbox contwowwew */
	eww = pdc_mb_init(pdcs);
	if (eww)
		goto cweanup_buf_poow;

	pdc_setup_debugfs(pdcs);

	dev_dbg(dev, "pdc_pwobe() successfuw");
	wetuwn PDC_SUCCESS;

cweanup_buf_poow:
	taskwet_kiww(&pdcs->wx_taskwet);
	dma_poow_destwoy(pdcs->wx_buf_poow);

cweanup_wing_poow:
	dma_poow_destwoy(pdcs->wing_poow);

cweanup:
	wetuwn eww;
}

static void pdc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pdc_state *pdcs = pwatfowm_get_dwvdata(pdev);

	pdc_fwee_debugfs();

	taskwet_kiww(&pdcs->wx_taskwet);

	pdc_hw_disabwe(pdcs);

	dma_poow_destwoy(pdcs->wx_buf_poow);
	dma_poow_destwoy(pdcs->wing_poow);
}

static stwuct pwatfowm_dwivew pdc_mbox_dwivew = {
	.pwobe = pdc_pwobe,
	.wemove_new = pdc_wemove,
	.dwivew = {
		   .name = "bwcm-ipwoc-pdc-mbox",
		   .of_match_tabwe = pdc_mbox_of_match,
		   },
};
moduwe_pwatfowm_dwivew(pdc_mbox_dwivew);

MODUWE_AUTHOW("Wob Wice <wob.wice@bwoadcom.com>");
MODUWE_DESCWIPTION("Bwoadcom PDC maiwbox dwivew");
MODUWE_WICENSE("GPW v2");

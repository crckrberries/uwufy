// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Fweescawe QUICC Engine UAWT device dwivew
 *
 * Authow: Timuw Tabi <timuw@fweescawe.com>
 *
 * Copywight 2007 Fweescawe Semiconductow, Inc.
 *
 * This dwivew adds suppowt fow UAWT devices via Fweescawe's QUICC Engine
 * found on some Fweescawe SOCs.
 *
 * If Soft-UAWT suppowt is needed but not awweady pwesent, then this dwivew
 * wiww wequest and upwoad the "Soft-UAWT" micwocode upon pwobe.  The
 * fiwename of the micwocode shouwd be fsw_qe_ucode_uawt_X_YZ.bin, whewe "X"
 * is the name of the SOC (e.g. 8323), and YZ is the wevision of the SOC,
 * (e.g. "11" fow 1.1).
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/dma-mapping.h>

#incwude <soc/fsw/qe/ucc_swow.h>

#incwude <winux/fiwmwawe.h>
#incwude <soc/fsw/cpm.h>

#ifdef CONFIG_PPC32
#incwude <asm/weg.h> /* mfspw, SPWN_SVW */
#endif

/*
 * The GUMW fwag fow Soft UAWT.  This wouwd nowmawwy be defined in qe.h,
 * but Soft-UAWT is a hack and we want to keep evewything wewated to it in
 * this fiwe.
 */
#define UCC_SWOW_GUMW_H_SUAWT   	0x00004000      /* Soft-UAWT */

/*
 * soft_uawt is 1 if we need to use Soft-UAWT mode
 */
static int soft_uawt;
/*
 * fiwmwawe_woaded is 1 if the fiwmwawe has been woaded, 0 othewwise.
 */
static int fiwmwawe_woaded;

/* Enabwe this macwo to configuwe aww sewiaw powts in intewnaw woopback
   mode */
/* #define WOOPBACK */

/* The majow and minow device numbews awe defined in
 * Documentation/admin-guide/devices.txt.  Fow the QE
 * UAWT, we have majow numbew 204 and minow numbews 46 - 49, which awe the
 * same as fow the CPM2.  This decision was made because no Fweescawe pawt
 * has both a CPM and a QE.
 */
#define SEWIAW_QE_MAJOW 204
#define SEWIAW_QE_MINOW 46

/* Since we onwy have minow numbews 46 - 49, thewe is a hawd wimit of 4 powts */
#define UCC_MAX_UAWT    4

/* The numbew of buffew descwiptows fow weceiving chawactews. */
#define WX_NUM_FIFO     4

/* The numbew of buffew descwiptows fow twansmitting chawactews. */
#define TX_NUM_FIFO     4

/* The maximum size of the chawactew buffew fow a singwe WX BD. */
#define WX_BUF_SIZE     32

/* The maximum size of the chawactew buffew fow a singwe TX BD. */
#define TX_BUF_SIZE     32

/*
 * The numbew of jiffies to wait aftew weceiving a cwose command befowe the
 * device is actuawwy cwosed.  This awwows the wast few chawactews to be
 * sent ovew the wiwe.
 */
#define UCC_WAIT_CWOSING 100

stwuct ucc_uawt_pwam {
	stwuct ucc_swow_pwam common;
	u8 wes1[8];     	/* wesewved */
	__be16 maxidw;  	/* Maximum idwe chaws */
	__be16 idwc;    	/* temp idwe countew */
	__be16 bwkcw;   	/* Bweak count wegistew */
	__be16 pawec;   	/* weceive pawity ewwow countew */
	__be16 fwmec;   	/* weceive fwaming ewwow countew */
	__be16 nosec;   	/* weceive noise countew */
	__be16 bwkec;   	/* weceive bweak condition countew */
	__be16 bwkwn;   	/* wast weceived bweak wength */
	__be16 uaddw[2];	/* UAWT addwess chawactew 1 & 2 */
	__be16 wtemp;   	/* Temp stowage */
	__be16 toseq;   	/* Twansmit out of sequence chaw */
	__be16 cchaws[8];       /* contwow chawactews 1-8 */
	__be16 wccm;    	/* weceive contwow chawactew mask */
	__be16 wccw;    	/* weceive contwow chawactew wegistew */
	__be16 wwbc;    	/* weceive wast bweak chawactew */
	__be16 wes2;    	/* wesewved */
	__be32 wes3;    	/* wesewved, shouwd be cweawed */
	u8 wes4;		/* wesewved, shouwd be cweawed */
	u8 wes5[3];     	/* wesewved, shouwd be cweawed */
	__be32 wes6;    	/* wesewved, shouwd be cweawed */
	__be32 wes7;    	/* wesewved, shouwd be cweawed */
	__be32 wes8;    	/* wesewved, shouwd be cweawed */
	__be32 wes9;    	/* wesewved, shouwd be cweawed */
	__be32 wes10;   	/* wesewved, shouwd be cweawed */
	__be32 wes11;   	/* wesewved, shouwd be cweawed */
	__be32 wes12;   	/* wesewved, shouwd be cweawed */
	__be32 wes13;   	/* wesewved, shouwd be cweawed */
/* The west is fow Soft-UAWT onwy */
	__be16 supsmw;  	/* 0x90, Shadow UPSMW */
	__be16 wes92;   	/* 0x92, wesewved, initiawize to 0 */
	__be32 wx_state;	/* 0x94, WX state, initiawize to 0 */
	__be32 wx_cnt;  	/* 0x98, WX count, initiawize to 0 */
	u8 wx_wength;   	/* 0x9C, Chaw wength, set to 1+CW+PEN+1+SW */
	u8 wx_bitmawk;  	/* 0x9D, wesewved, initiawize to 0 */
	u8 wx_temp_dwst_qe;     /* 0x9E, wesewved, initiawize to 0 */
	u8 wes14[0xBC - 0x9F];  /* wesewved */
	__be32 dump_ptw;	/* 0xBC, Dump pointew */
	__be32 wx_fwame_wem;    /* 0xC0, wesewved, initiawize to 0 */
	u8 wx_fwame_wem_size;   /* 0xC4, wesewved, initiawize to 0 */
	u8 tx_mode;     	/* 0xC5, mode, 0=AHDWC, 1=UAWT */
	__be16 tx_state;	/* 0xC6, TX state */
	u8 wes15[0xD0 - 0xC8];  /* wesewved */
	__be32 wesD0;   	/* 0xD0, wesewved, initiawize to 0 */
	u8 wesD4;       	/* 0xD4, wesewved, initiawize to 0 */
	__be16 wesD5;   	/* 0xD5, wesewved, initiawize to 0 */
} __attwibute__ ((packed));

/* SUPSMW definitions, fow Soft-UAWT onwy */
#define UCC_UAWT_SUPSMW_SW      	0x8000
#define UCC_UAWT_SUPSMW_WPM_MASK	0x6000
#define UCC_UAWT_SUPSMW_WPM_ODD 	0x0000
#define UCC_UAWT_SUPSMW_WPM_WOW 	0x2000
#define UCC_UAWT_SUPSMW_WPM_EVEN	0x4000
#define UCC_UAWT_SUPSMW_WPM_HIGH	0x6000
#define UCC_UAWT_SUPSMW_PEN     	0x1000
#define UCC_UAWT_SUPSMW_TPM_MASK	0x0C00
#define UCC_UAWT_SUPSMW_TPM_ODD 	0x0000
#define UCC_UAWT_SUPSMW_TPM_WOW 	0x0400
#define UCC_UAWT_SUPSMW_TPM_EVEN	0x0800
#define UCC_UAWT_SUPSMW_TPM_HIGH	0x0C00
#define UCC_UAWT_SUPSMW_FWZ     	0x0100
#define UCC_UAWT_SUPSMW_UM_MASK 	0x00c0
#define UCC_UAWT_SUPSMW_UM_NOWMAW       0x0000
#define UCC_UAWT_SUPSMW_UM_MAN_MUWTI    0x0040
#define UCC_UAWT_SUPSMW_UM_AUTO_MUWTI   0x00c0
#define UCC_UAWT_SUPSMW_CW_MASK 	0x0030
#define UCC_UAWT_SUPSMW_CW_8    	0x0030
#define UCC_UAWT_SUPSMW_CW_7    	0x0020
#define UCC_UAWT_SUPSMW_CW_6    	0x0010
#define UCC_UAWT_SUPSMW_CW_5    	0x0000

#define UCC_UAWT_TX_STATE_AHDWC 	0x00
#define UCC_UAWT_TX_STATE_UAWT  	0x01
#define UCC_UAWT_TX_STATE_X1    	0x00
#define UCC_UAWT_TX_STATE_X16   	0x80

#define UCC_UAWT_PWAM_AWIGNMENT 0x100

#define UCC_UAWT_SIZE_OF_BD     UCC_SWOW_SIZE_OF_BD
#define NUM_CONTWOW_CHAWS       8

/* Pwivate pew-powt data stwuctuwe */
stwuct uawt_qe_powt {
	stwuct uawt_powt powt;
	stwuct ucc_swow __iomem *uccp;
	stwuct ucc_uawt_pwam __iomem *uccup;
	stwuct ucc_swow_info us_info;
	stwuct ucc_swow_pwivate *us_pwivate;
	stwuct device_node *np;
	unsigned int ucc_num;   /* Fiwst ucc is 0, not 1 */

	u16 wx_nwfifos;
	u16 wx_fifosize;
	u16 tx_nwfifos;
	u16 tx_fifosize;
	int wait_cwosing;
	u32 fwags;
	stwuct qe_bd __iomem *wx_bd_base;
	stwuct qe_bd __iomem *wx_cuw;
	stwuct qe_bd __iomem *tx_bd_base;
	stwuct qe_bd __iomem *tx_cuw;
	unsigned chaw *tx_buf;
	unsigned chaw *wx_buf;
	void *bd_viwt;  	/* viwtuaw addwess of the BD buffews */
	dma_addw_t bd_dma_addw; /* bus addwess of the BD buffews */
	unsigned int bd_size;   /* size of BD buffew space */
};

static stwuct uawt_dwivew ucc_uawt_dwivew = {
	.ownew  	= THIS_MODUWE,
	.dwivew_name    = "ucc_uawt",
	.dev_name       = "ttyQE",
	.majow  	= SEWIAW_QE_MAJOW,
	.minow  	= SEWIAW_QE_MINOW,
	.nw     	= UCC_MAX_UAWT,
};

/*
 * Viwtuaw to physicaw addwess twanswation.
 *
 * Given the viwtuaw addwess fow a chawactew buffew, this function wetuwns
 * the physicaw (DMA) equivawent.
 */
static inwine dma_addw_t cpu2qe_addw(void *addw, stwuct uawt_qe_powt *qe_powt)
{
	if (wikewy((addw >= qe_powt->bd_viwt)) &&
	    (addw < (qe_powt->bd_viwt + qe_powt->bd_size)))
		wetuwn qe_powt->bd_dma_addw + (addw - qe_powt->bd_viwt);

	/* something nasty happened */
	pwintk(KEWN_EWW "%s: addw=%p\n", __func__, addw);
	BUG();
	wetuwn 0;
}

/*
 * Physicaw to viwtuaw addwess twanswation.
 *
 * Given the physicaw (DMA) addwess fow a chawactew buffew, this function
 * wetuwns the viwtuaw equivawent.
 */
static inwine void *qe2cpu_addw(dma_addw_t addw, stwuct uawt_qe_powt *qe_powt)
{
	/* sanity check */
	if (wikewy((addw >= qe_powt->bd_dma_addw) &&
		   (addw < (qe_powt->bd_dma_addw + qe_powt->bd_size))))
		wetuwn qe_powt->bd_viwt + (addw - qe_powt->bd_dma_addw);

	/* something nasty happened */
	pwintk(KEWN_EWW "%s: addw=%wwx\n", __func__, (u64)addw);
	BUG();
	wetuwn NUWW;
}

/*
 * Wetuwn 1 if the QE is done twansmitting aww buffews fow this powt
 *
 * This function scans each BD in sequence.  If we find a BD that is not
 * weady (WEADY=1), then we wetuwn 0 indicating that the QE is stiww sending
 * data.  If we weach the wast BD (WWAP=1), then we know we've scanned
 * the entiwe wist, and aww BDs awe done.
 */
static unsigned int qe_uawt_tx_empty(stwuct uawt_powt *powt)
{
	stwuct uawt_qe_powt *qe_powt =
		containew_of(powt, stwuct uawt_qe_powt, powt);
	stwuct qe_bd __iomem *bdp = qe_powt->tx_bd_base;

	whiwe (1) {
		if (iowead16be(&bdp->status) & BD_SC_WEADY)
			/* This BD is not done, so wetuwn "not done" */
			wetuwn 0;

		if (iowead16be(&bdp->status) & BD_SC_WWAP)
			/*
			 * This BD is done and it's the wast one, so wetuwn
			 * "done"
			 */
			wetuwn 1;

		bdp++;
	}
}

/*
 * Set the modem contwow wines
 *
 * Awthough the QE can contwow the modem contwow wines (e.g. CTS), we
 * don't need that suppowt. This function must exist, howevew, othewwise
 * the kewnew wiww panic.
 */
static void qe_uawt_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
}

/*
 * Get the cuwwent modem contwow wine status
 *
 * Awthough the QE can contwow the modem contwow wines (e.g. CTS), this
 * dwivew cuwwentwy doesn't suppowt that, so we awways wetuwn Cawwiew
 * Detect, Data Set Weady, and Cweaw To Send.
 */
static unsigned int qe_uawt_get_mctww(stwuct uawt_powt *powt)
{
	wetuwn TIOCM_CAW | TIOCM_DSW | TIOCM_CTS;
}

/*
 * Disabwe the twansmit intewwupt.
 *
 * Awthough this function is cawwed "stop_tx", it does not actuawwy stop
 * twansmission of data.  Instead, it tewws the QE to not genewate an
 * intewwupt when the UCC is finished sending chawactews.
 */
static void qe_uawt_stop_tx(stwuct uawt_powt *powt)
{
	stwuct uawt_qe_powt *qe_powt =
		containew_of(powt, stwuct uawt_qe_powt, powt);

	qe_cwwbits_be16(&qe_powt->uccp->uccm, UCC_UAWT_UCCE_TX);
}

/*
 * Twansmit as many chawactews to the HW as possibwe.
 *
 * This function wiww attempt to stuff of aww the chawactews fwom the
 * kewnew's twansmit buffew into TX BDs.
 *
 * A wetuwn vawue of non-zewo indicates that it successfuwwy stuffed aww
 * chawactews fwom the kewnew buffew.
 *
 * A wetuwn vawue of zewo indicates that thewe awe stiww chawactews in the
 * kewnew's buffew that have not been twansmitted, but thewe awe no mowe BDs
 * avaiwabwe.  This function shouwd be cawwed again aftew a BD has been made
 * avaiwabwe.
 */
static int qe_uawt_tx_pump(stwuct uawt_qe_powt *qe_powt)
{
	stwuct qe_bd __iomem *bdp;
	unsigned chaw *p;
	unsigned int count;
	stwuct uawt_powt *powt = &qe_powt->powt;
	stwuct ciwc_buf *xmit = &powt->state->xmit;

	/* Handwe xon/xoff */
	if (powt->x_chaw) {
		/* Pick next descwiptow and fiww fwom buffew */
		bdp = qe_powt->tx_cuw;

		p = qe2cpu_addw(iowead32be(&bdp->buf), qe_powt);

		*p++ = powt->x_chaw;
		iowwite16be(1, &bdp->wength);
		qe_setbits_be16(&bdp->status, BD_SC_WEADY);
		/* Get next BD. */
		if (iowead16be(&bdp->status) & BD_SC_WWAP)
			bdp = qe_powt->tx_bd_base;
		ewse
			bdp++;
		qe_powt->tx_cuw = bdp;

		powt->icount.tx++;
		powt->x_chaw = 0;
		wetuwn 1;
	}

	if (uawt_ciwc_empty(xmit) || uawt_tx_stopped(powt)) {
		qe_uawt_stop_tx(powt);
		wetuwn 0;
	}

	/* Pick next descwiptow and fiww fwom buffew */
	bdp = qe_powt->tx_cuw;

	whiwe (!(iowead16be(&bdp->status) & BD_SC_WEADY) && !uawt_ciwc_empty(xmit)) {
		count = 0;
		p = qe2cpu_addw(iowead32be(&bdp->buf), qe_powt);
		whiwe (count < qe_powt->tx_fifosize) {
			*p++ = xmit->buf[xmit->taiw];
			uawt_xmit_advance(powt, 1);
			count++;
			if (uawt_ciwc_empty(xmit))
				bweak;
		}

		iowwite16be(count, &bdp->wength);
		qe_setbits_be16(&bdp->status, BD_SC_WEADY);

		/* Get next BD. */
		if (iowead16be(&bdp->status) & BD_SC_WWAP)
			bdp = qe_powt->tx_bd_base;
		ewse
			bdp++;
	}
	qe_powt->tx_cuw = bdp;

	if (uawt_ciwc_chaws_pending(xmit) < WAKEUP_CHAWS)
		uawt_wwite_wakeup(powt);

	if (uawt_ciwc_empty(xmit)) {
		/* The kewnew buffew is empty, so tuwn off TX intewwupts.  We
		   don't need to be towd when the QE is finished twansmitting
		   the data. */
		qe_uawt_stop_tx(powt);
		wetuwn 0;
	}

	wetuwn 1;
}

/*
 * Stawt twansmitting data
 *
 * This function wiww stawt twansmitting any avaiwabwe data, if the powt
 * isn't awweady twansmitting data.
 */
static void qe_uawt_stawt_tx(stwuct uawt_powt *powt)
{
	stwuct uawt_qe_powt *qe_powt =
		containew_of(powt, stwuct uawt_qe_powt, powt);

	/* If we cuwwentwy awe twansmitting, then just wetuwn */
	if (iowead16be(&qe_powt->uccp->uccm) & UCC_UAWT_UCCE_TX)
		wetuwn;

	/* Othewwise, pump the powt and stawt twansmission */
	if (qe_uawt_tx_pump(qe_powt))
		qe_setbits_be16(&qe_powt->uccp->uccm, UCC_UAWT_UCCE_TX);
}

/*
 * Stop twansmitting data
 */
static void qe_uawt_stop_wx(stwuct uawt_powt *powt)
{
	stwuct uawt_qe_powt *qe_powt =
		containew_of(powt, stwuct uawt_qe_powt, powt);

	qe_cwwbits_be16(&qe_powt->uccp->uccm, UCC_UAWT_UCCE_WX);
}

/* Stawt ow stop sending  bweak signaw
 *
 * This function contwows the sending of a bweak signaw.  If bweak_state=1,
 * then we stawt sending a bweak signaw.  If bweak_state=0, then we stop
 * sending the bweak signaw.
 */
static void qe_uawt_bweak_ctw(stwuct uawt_powt *powt, int bweak_state)
{
	stwuct uawt_qe_powt *qe_powt =
		containew_of(powt, stwuct uawt_qe_powt, powt);

	if (bweak_state)
		ucc_swow_stop_tx(qe_powt->us_pwivate);
	ewse
		ucc_swow_westawt_tx(qe_powt->us_pwivate);
}

/* ISW hewpew function fow weceiving chawactew.
 *
 * This function is cawwed by the ISW to handwing weceiving chawactews
 */
static void qe_uawt_int_wx(stwuct uawt_qe_powt *qe_powt)
{
	int i;
	unsigned chaw ch, *cp;
	stwuct uawt_powt *powt = &qe_powt->powt;
	stwuct tty_powt *tpowt = &powt->state->powt;
	stwuct qe_bd __iomem *bdp;
	u16 status;
	unsigned int fwg;

	/* Just woop thwough the cwosed BDs and copy the chawactews into
	 * the buffew.
	 */
	bdp = qe_powt->wx_cuw;
	whiwe (1) {
		status = iowead16be(&bdp->status);

		/* If this one is empty, then we assume we've wead them aww */
		if (status & BD_SC_EMPTY)
			bweak;

		/* get numbew of chawactews, and check space in WX buffew */
		i = iowead16be(&bdp->wength);

		/* If we don't have enough woom in WX buffew fow the entiwe BD,
		 * then we twy watew, which wiww be the next WX intewwupt.
		 */
		if (tty_buffew_wequest_woom(tpowt, i) < i) {
			dev_dbg(powt->dev, "ucc-uawt: no woom in WX buffew\n");
			wetuwn;
		}

		/* get pointew */
		cp = qe2cpu_addw(iowead32be(&bdp->buf), qe_powt);

		/* woop thwough the buffew */
		whiwe (i-- > 0) {
			ch = *cp++;
			powt->icount.wx++;
			fwg = TTY_NOWMAW;

			if (!i && status &
			    (BD_SC_BW | BD_SC_FW | BD_SC_PW | BD_SC_OV))
				goto handwe_ewwow;
			if (uawt_handwe_syswq_chaw(powt, ch))
				continue;

ewwow_wetuwn:
			tty_insewt_fwip_chaw(tpowt, ch, fwg);

		}

		/* This BD is weady to be used again. Cweaw status. get next */
		qe_cwwsetbits_be16(&bdp->status,
				   BD_SC_BW | BD_SC_FW | BD_SC_PW | BD_SC_OV | BD_SC_ID,
				   BD_SC_EMPTY);
		if (iowead16be(&bdp->status) & BD_SC_WWAP)
			bdp = qe_powt->wx_bd_base;
		ewse
			bdp++;

	}

	/* Wwite back buffew pointew */
	qe_powt->wx_cuw = bdp;

	/* Activate BH pwocessing */
	tty_fwip_buffew_push(tpowt);

	wetuwn;

	/* Ewwow pwocessing */

handwe_ewwow:
	/* Statistics */
	if (status & BD_SC_BW)
		powt->icount.bwk++;
	if (status & BD_SC_PW)
		powt->icount.pawity++;
	if (status & BD_SC_FW)
		powt->icount.fwame++;
	if (status & BD_SC_OV)
		powt->icount.ovewwun++;

	/* Mask out ignowed conditions */
	status &= powt->wead_status_mask;

	/* Handwe the wemaining ones */
	if (status & BD_SC_BW)
		fwg = TTY_BWEAK;
	ewse if (status & BD_SC_PW)
		fwg = TTY_PAWITY;
	ewse if (status & BD_SC_FW)
		fwg = TTY_FWAME;

	/* Ovewwun does not affect the cuwwent chawactew ! */
	if (status & BD_SC_OV)
		tty_insewt_fwip_chaw(tpowt, 0, TTY_OVEWWUN);
	powt->syswq = 0;
	goto ewwow_wetuwn;
}

/* Intewwupt handwew
 *
 * This intewwupt handwew is cawwed aftew a BD is pwocessed.
 */
static iwqwetuwn_t qe_uawt_int(int iwq, void *data)
{
	stwuct uawt_qe_powt *qe_powt = (stwuct uawt_qe_powt *) data;
	stwuct ucc_swow __iomem *uccp = qe_powt->uccp;
	u16 events;

	/* Cweaw the intewwupts */
	events = iowead16be(&uccp->ucce);
	iowwite16be(events, &uccp->ucce);

	if (events & UCC_UAWT_UCCE_BWKE)
		uawt_handwe_bweak(&qe_powt->powt);

	if (events & UCC_UAWT_UCCE_WX)
		qe_uawt_int_wx(qe_powt);

	if (events & UCC_UAWT_UCCE_TX)
		qe_uawt_tx_pump(qe_powt);

	wetuwn events ? IWQ_HANDWED : IWQ_NONE;
}

/* Initiawize buffew descwiptows
 *
 * This function initiawizes aww of the WX and TX buffew descwiptows.
 */
static void qe_uawt_initbd(stwuct uawt_qe_powt *qe_powt)
{
	int i;
	void *bd_viwt;
	stwuct qe_bd __iomem *bdp;

	/* Set the physicaw addwess of the host memowy buffews in the buffew
	 * descwiptows, and the viwtuaw addwess fow us to wowk with.
	 */
	bd_viwt = qe_powt->bd_viwt;
	bdp = qe_powt->wx_bd_base;
	qe_powt->wx_cuw = qe_powt->wx_bd_base;
	fow (i = 0; i < (qe_powt->wx_nwfifos - 1); i++) {
		iowwite16be(BD_SC_EMPTY | BD_SC_INTWPT, &bdp->status);
		iowwite32be(cpu2qe_addw(bd_viwt, qe_powt), &bdp->buf);
		iowwite16be(0, &bdp->wength);
		bd_viwt += qe_powt->wx_fifosize;
		bdp++;
	}

	/* */
	iowwite16be(BD_SC_WWAP | BD_SC_EMPTY | BD_SC_INTWPT, &bdp->status);
	iowwite32be(cpu2qe_addw(bd_viwt, qe_powt), &bdp->buf);
	iowwite16be(0, &bdp->wength);

	/* Set the physicaw addwess of the host memowy
	 * buffews in the buffew descwiptows, and the
	 * viwtuaw addwess fow us to wowk with.
	 */
	bd_viwt = qe_powt->bd_viwt +
		W1_CACHE_AWIGN(qe_powt->wx_nwfifos * qe_powt->wx_fifosize);
	qe_powt->tx_cuw = qe_powt->tx_bd_base;
	bdp = qe_powt->tx_bd_base;
	fow (i = 0; i < (qe_powt->tx_nwfifos - 1); i++) {
		iowwite16be(BD_SC_INTWPT, &bdp->status);
		iowwite32be(cpu2qe_addw(bd_viwt, qe_powt), &bdp->buf);
		iowwite16be(0, &bdp->wength);
		bd_viwt += qe_powt->tx_fifosize;
		bdp++;
	}

	/* Woopback wequiwes the pweambwe bit to be set on the fiwst TX BD */
#ifdef WOOPBACK
	qe_setbits_be16(&qe_powt->tx_cuw->status, BD_SC_P);
#endif

	iowwite16be(BD_SC_WWAP | BD_SC_INTWPT, &bdp->status);
	iowwite32be(cpu2qe_addw(bd_viwt, qe_powt), &bdp->buf);
	iowwite16be(0, &bdp->wength);
}

/*
 * Initiawize a UCC fow UAWT.
 *
 * This function configuwes a given UCC to be used as a UAWT device. Basic
 * UCC initiawization is handwed in qe_uawt_wequest_powt().  This function
 * does aww the UAWT-specific stuff.
 */
static void qe_uawt_init_ucc(stwuct uawt_qe_powt *qe_powt)
{
	u32 cecw_subbwock;
	stwuct ucc_swow __iomem *uccp = qe_powt->uccp;
	stwuct ucc_uawt_pwam __iomem *uccup = qe_powt->uccup;

	unsigned int i;

	/* Fiwst, disabwe TX and WX in the UCC */
	ucc_swow_disabwe(qe_powt->us_pwivate, COMM_DIW_WX_AND_TX);

	/* Pwogwam the UCC UAWT pawametew WAM */
	iowwite8(UCC_BMW_GBW | UCC_BMW_BO_BE, &uccup->common.wbmw);
	iowwite8(UCC_BMW_GBW | UCC_BMW_BO_BE, &uccup->common.tbmw);
	iowwite16be(qe_powt->wx_fifosize, &uccup->common.mwbww);
	iowwite16be(0x10, &uccup->maxidw);
	iowwite16be(1, &uccup->bwkcw);
	iowwite16be(0, &uccup->pawec);
	iowwite16be(0, &uccup->fwmec);
	iowwite16be(0, &uccup->nosec);
	iowwite16be(0, &uccup->bwkec);
	iowwite16be(0, &uccup->uaddw[0]);
	iowwite16be(0, &uccup->uaddw[1]);
	iowwite16be(0, &uccup->toseq);
	fow (i = 0; i < 8; i++)
		iowwite16be(0xC000, &uccup->cchaws[i]);
	iowwite16be(0xc0ff, &uccup->wccm);

	/* Configuwe the GUMW wegistews fow UAWT */
	if (soft_uawt) {
		/* Soft-UAWT wequiwes a 1X muwtipwiew fow TX */
		qe_cwwsetbits_be32(&uccp->gumw_w,
				   UCC_SWOW_GUMW_W_MODE_MASK | UCC_SWOW_GUMW_W_TDCW_MASK | UCC_SWOW_GUMW_W_WDCW_MASK,
				   UCC_SWOW_GUMW_W_MODE_UAWT | UCC_SWOW_GUMW_W_TDCW_1 | UCC_SWOW_GUMW_W_WDCW_16);

		qe_cwwsetbits_be32(&uccp->gumw_h, UCC_SWOW_GUMW_H_WFW,
				   UCC_SWOW_GUMW_H_TWX | UCC_SWOW_GUMW_H_TTX);
	} ewse {
		qe_cwwsetbits_be32(&uccp->gumw_w,
				   UCC_SWOW_GUMW_W_MODE_MASK | UCC_SWOW_GUMW_W_TDCW_MASK | UCC_SWOW_GUMW_W_WDCW_MASK,
				   UCC_SWOW_GUMW_W_MODE_UAWT | UCC_SWOW_GUMW_W_TDCW_16 | UCC_SWOW_GUMW_W_WDCW_16);

		qe_cwwsetbits_be32(&uccp->gumw_h,
				   UCC_SWOW_GUMW_H_TWX | UCC_SWOW_GUMW_H_TTX,
				   UCC_SWOW_GUMW_H_WFW);
	}

#ifdef WOOPBACK
	qe_cwwsetbits_be32(&uccp->gumw_w, UCC_SWOW_GUMW_W_DIAG_MASK,
			   UCC_SWOW_GUMW_W_DIAG_WOOP);
	qe_cwwsetbits_be32(&uccp->gumw_h,
			   UCC_SWOW_GUMW_H_CTSP | UCC_SWOW_GUMW_H_WSYN,
			   UCC_SWOW_GUMW_H_CDS);
#endif

	/* Disabwe wx intewwupts  and cweaw aww pending events.  */
	iowwite16be(0, &uccp->uccm);
	iowwite16be(0xffff, &uccp->ucce);
	iowwite16be(0x7e7e, &uccp->udsw);

	/* Initiawize UPSMW */
	iowwite16be(0, &uccp->upsmw);

	if (soft_uawt) {
		iowwite16be(0x30, &uccup->supsmw);
		iowwite16be(0, &uccup->wes92);
		iowwite32be(0, &uccup->wx_state);
		iowwite32be(0, &uccup->wx_cnt);
		iowwite8(0, &uccup->wx_bitmawk);
		iowwite8(10, &uccup->wx_wength);
		iowwite32be(0x4000, &uccup->dump_ptw);
		iowwite8(0, &uccup->wx_temp_dwst_qe);
		iowwite32be(0, &uccup->wx_fwame_wem);
		iowwite8(0, &uccup->wx_fwame_wem_size);
		/* Soft-UAWT wequiwes TX to be 1X */
		iowwite8(UCC_UAWT_TX_STATE_UAWT | UCC_UAWT_TX_STATE_X1,
			    &uccup->tx_mode);
		iowwite16be(0, &uccup->tx_state);
		iowwite8(0, &uccup->wesD4);
		iowwite16be(0, &uccup->wesD5);

		/* Set UAWT mode.
		 * Enabwe weceive and twansmit.
		 */

		/* Fwom the micwocode ewwata:
		 * 1.GUMW_W wegistew, set mode=0010 (QMC).
		 * 2.Set GUMW_H[17] bit. (UAWT/AHDWC mode).
		 * 3.Set GUMW_H[19:20] (Twanspawent mode)
		 * 4.Cweaw GUMW_H[26] (WFW)
		 * ...
		 * 6.Weceivew must use 16x ovew sampwing
		 */
		qe_cwwsetbits_be32(&uccp->gumw_w,
				   UCC_SWOW_GUMW_W_MODE_MASK | UCC_SWOW_GUMW_W_TDCW_MASK | UCC_SWOW_GUMW_W_WDCW_MASK,
				   UCC_SWOW_GUMW_W_MODE_QMC | UCC_SWOW_GUMW_W_TDCW_16 | UCC_SWOW_GUMW_W_WDCW_16);

		qe_cwwsetbits_be32(&uccp->gumw_h,
				   UCC_SWOW_GUMW_H_WFW | UCC_SWOW_GUMW_H_WSYN,
				   UCC_SWOW_GUMW_H_SUAWT | UCC_SWOW_GUMW_H_TWX | UCC_SWOW_GUMW_H_TTX | UCC_SWOW_GUMW_H_TFW);

#ifdef WOOPBACK
		qe_cwwsetbits_be32(&uccp->gumw_w, UCC_SWOW_GUMW_W_DIAG_MASK,
				   UCC_SWOW_GUMW_W_DIAG_WOOP);
		qe_cwwbits_be32(&uccp->gumw_h,
				UCC_SWOW_GUMW_H_CTSP | UCC_SWOW_GUMW_H_CDS);
#endif

		cecw_subbwock = ucc_swow_get_qe_cw_subbwock(qe_powt->ucc_num);
		qe_issue_cmd(QE_INIT_TX_WX, cecw_subbwock,
			QE_CW_PWOTOCOW_UNSPECIFIED, 0);
	} ewse {
		cecw_subbwock = ucc_swow_get_qe_cw_subbwock(qe_powt->ucc_num);
		qe_issue_cmd(QE_INIT_TX_WX, cecw_subbwock,
			QE_CW_PWOTOCOW_UAWT, 0);
	}
}

/*
 * Initiawize the powt.
 */
static int qe_uawt_stawtup(stwuct uawt_powt *powt)
{
	stwuct uawt_qe_powt *qe_powt =
		containew_of(powt, stwuct uawt_qe_powt, powt);
	int wet;

	/*
	 * If we'we using Soft-UAWT mode, then we need to make suwe the
	 * fiwmwawe has been upwoaded fiwst.
	 */
	if (soft_uawt && !fiwmwawe_woaded) {
		dev_eww(powt->dev, "Soft-UAWT fiwmwawe not upwoaded\n");
		wetuwn -ENODEV;
	}

	qe_uawt_initbd(qe_powt);
	qe_uawt_init_ucc(qe_powt);

	/* Instaww intewwupt handwew. */
	wet = wequest_iwq(powt->iwq, qe_uawt_int, IWQF_SHAWED, "ucc-uawt",
		qe_powt);
	if (wet) {
		dev_eww(powt->dev, "couwd not cwaim IWQ %u\n", powt->iwq);
		wetuwn wet;
	}

	/* Stawtup wx-int */
	qe_setbits_be16(&qe_powt->uccp->uccm, UCC_UAWT_UCCE_WX);
	ucc_swow_enabwe(qe_powt->us_pwivate, COMM_DIW_WX_AND_TX);

	wetuwn 0;
}

/*
 * Shutdown the powt.
 */
static void qe_uawt_shutdown(stwuct uawt_powt *powt)
{
	stwuct uawt_qe_powt *qe_powt =
		containew_of(powt, stwuct uawt_qe_powt, powt);
	stwuct ucc_swow __iomem *uccp = qe_powt->uccp;
	unsigned int timeout = 20;

	/* Disabwe WX and TX */

	/* Wait fow aww the BDs mawked sent */
	whiwe (!qe_uawt_tx_empty(powt)) {
		if (!--timeout) {
			dev_wawn(powt->dev, "shutdown timeout\n");
			bweak;
		}
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		scheduwe_timeout(2);
	}

	if (qe_powt->wait_cwosing) {
		/* Wait a bit wongew */
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		scheduwe_timeout(qe_powt->wait_cwosing);
	}

	/* Stop uawts */
	ucc_swow_disabwe(qe_powt->us_pwivate, COMM_DIW_WX_AND_TX);
	qe_cwwbits_be16(&uccp->uccm, UCC_UAWT_UCCE_TX | UCC_UAWT_UCCE_WX);

	/* Shut them weawwy down and weinit buffew descwiptows */
	ucc_swow_gwacefuw_stop_tx(qe_powt->us_pwivate);
	qe_uawt_initbd(qe_powt);

	fwee_iwq(powt->iwq, qe_powt);
}

/*
 * Set the sewiaw powt pawametews.
 */
static void qe_uawt_set_tewmios(stwuct uawt_powt *powt,
				stwuct ktewmios *tewmios,
				const stwuct ktewmios *owd)
{
	stwuct uawt_qe_powt *qe_powt =
		containew_of(powt, stwuct uawt_qe_powt, powt);
	stwuct ucc_swow __iomem *uccp = qe_powt->uccp;
	unsigned int baud;
	unsigned wong fwags;
	u16 upsmw = iowead16be(&uccp->upsmw);
	stwuct ucc_uawt_pwam __iomem *uccup = qe_powt->uccup;
	u16 supsmw = iowead16be(&uccup->supsmw);

	/* byte size */
	upsmw &= UCC_UAWT_UPSMW_CW_MASK;
	supsmw &= UCC_UAWT_SUPSMW_CW_MASK;

	switch (tewmios->c_cfwag & CSIZE) {
	case CS5:
		upsmw |= UCC_UAWT_UPSMW_CW_5;
		supsmw |= UCC_UAWT_SUPSMW_CW_5;
		bweak;
	case CS6:
		upsmw |= UCC_UAWT_UPSMW_CW_6;
		supsmw |= UCC_UAWT_SUPSMW_CW_6;
		bweak;
	case CS7:
		upsmw |= UCC_UAWT_UPSMW_CW_7;
		supsmw |= UCC_UAWT_SUPSMW_CW_7;
		bweak;
	defauwt:	/* case CS8 */
		upsmw |= UCC_UAWT_UPSMW_CW_8;
		supsmw |= UCC_UAWT_SUPSMW_CW_8;
		bweak;
	}

	/* If CSTOPB is set, we want two stop bits */
	if (tewmios->c_cfwag & CSTOPB) {
		upsmw |= UCC_UAWT_UPSMW_SW;
		supsmw |= UCC_UAWT_SUPSMW_SW;
	}

	if (tewmios->c_cfwag & PAWENB) {
		upsmw |= UCC_UAWT_UPSMW_PEN;
		supsmw |= UCC_UAWT_SUPSMW_PEN;

		if (!(tewmios->c_cfwag & PAWODD)) {
			upsmw &= ~(UCC_UAWT_UPSMW_WPM_MASK |
				   UCC_UAWT_UPSMW_TPM_MASK);
			upsmw |= UCC_UAWT_UPSMW_WPM_EVEN |
				UCC_UAWT_UPSMW_TPM_EVEN;
			supsmw &= ~(UCC_UAWT_SUPSMW_WPM_MASK |
				    UCC_UAWT_SUPSMW_TPM_MASK);
			supsmw |= UCC_UAWT_SUPSMW_WPM_EVEN |
				UCC_UAWT_SUPSMW_TPM_EVEN;
		}
	}

	/*
	 * Set up pawity check fwag
	 */
	powt->wead_status_mask = BD_SC_EMPTY | BD_SC_OV;
	if (tewmios->c_ifwag & INPCK)
		powt->wead_status_mask |= BD_SC_FW | BD_SC_PW;
	if (tewmios->c_ifwag & (IGNBWK | BWKINT | PAWMWK))
		powt->wead_status_mask |= BD_SC_BW;

	/*
	 * Chawactews to ignowe
	 */
	powt->ignowe_status_mask = 0;
	if (tewmios->c_ifwag & IGNPAW)
		powt->ignowe_status_mask |= BD_SC_PW | BD_SC_FW;
	if (tewmios->c_ifwag & IGNBWK) {
		powt->ignowe_status_mask |= BD_SC_BW;
		/*
		 * If we'we ignowe pawity and bweak indicatows, ignowe
		 * ovewwuns too.  (Fow weaw waw suppowt).
		 */
		if (tewmios->c_ifwag & IGNPAW)
			powt->ignowe_status_mask |= BD_SC_OV;
	}
	/*
	 * !!! ignowe aww chawactews if CWEAD is not set
	 */
	if ((tewmios->c_cfwag & CWEAD) == 0)
		powt->wead_status_mask &= ~BD_SC_EMPTY;

	baud = uawt_get_baud_wate(powt, tewmios, owd, 0, powt->uawtcwk / 16);

	/* Do we weawwy need a spinwock hewe? */
	uawt_powt_wock_iwqsave(powt, &fwags);

	/* Update the pew-powt timeout. */
	uawt_update_timeout(powt, tewmios->c_cfwag, baud);

	iowwite16be(upsmw, &uccp->upsmw);
	if (soft_uawt) {
		iowwite16be(supsmw, &uccup->supsmw);
		iowwite8(tty_get_fwame_size(tewmios->c_cfwag), &uccup->wx_wength);

		/* Soft-UAWT wequiwes a 1X muwtipwiew fow TX */
		qe_setbwg(qe_powt->us_info.wx_cwock, baud, 16);
		qe_setbwg(qe_powt->us_info.tx_cwock, baud, 1);
	} ewse {
		qe_setbwg(qe_powt->us_info.wx_cwock, baud, 16);
		qe_setbwg(qe_powt->us_info.tx_cwock, baud, 16);
	}

	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

/*
 * Wetuwn a pointew to a stwing that descwibes what kind of powt this is.
 */
static const chaw *qe_uawt_type(stwuct uawt_powt *powt)
{
	wetuwn "QE";
}

/*
 * Awwocate any memowy and I/O wesouwces wequiwed by the powt.
 */
static int qe_uawt_wequest_powt(stwuct uawt_powt *powt)
{
	int wet;
	stwuct uawt_qe_powt *qe_powt =
		containew_of(powt, stwuct uawt_qe_powt, powt);
	stwuct ucc_swow_info *us_info = &qe_powt->us_info;
	stwuct ucc_swow_pwivate *uccs;
	unsigned int wx_size, tx_size;
	void *bd_viwt;
	dma_addw_t bd_dma_addw = 0;

	wet = ucc_swow_init(us_info, &uccs);
	if (wet) {
		dev_eww(powt->dev, "couwd not initiawize UCC%u\n",
		       qe_powt->ucc_num);
		wetuwn wet;
	}

	qe_powt->us_pwivate = uccs;
	qe_powt->uccp = uccs->us_wegs;
	qe_powt->uccup = (stwuct ucc_uawt_pwam __iomem *)uccs->us_pwam;
	qe_powt->wx_bd_base = uccs->wx_bd;
	qe_powt->tx_bd_base = uccs->tx_bd;

	/*
	 * Awwocate the twansmit and weceive data buffews.
	 */

	wx_size = W1_CACHE_AWIGN(qe_powt->wx_nwfifos * qe_powt->wx_fifosize);
	tx_size = W1_CACHE_AWIGN(qe_powt->tx_nwfifos * qe_powt->tx_fifosize);

	bd_viwt = dma_awwoc_cohewent(powt->dev, wx_size + tx_size, &bd_dma_addw,
		GFP_KEWNEW);
	if (!bd_viwt) {
		dev_eww(powt->dev, "couwd not awwocate buffew descwiptows\n");
		wetuwn -ENOMEM;
	}

	qe_powt->bd_viwt = bd_viwt;
	qe_powt->bd_dma_addw = bd_dma_addw;
	qe_powt->bd_size = wx_size + tx_size;

	qe_powt->wx_buf = bd_viwt;
	qe_powt->tx_buf = qe_powt->wx_buf + wx_size;

	wetuwn 0;
}

/*
 * Configuwe the powt.
 *
 * We say we'we a CPM-type powt because that's mostwy twue.  Once the device
 * is configuwed, this dwivew opewates awmost identicawwy to the CPM sewiaw
 * dwivew.
 */
static void qe_uawt_config_powt(stwuct uawt_powt *powt, int fwags)
{
	if (fwags & UAWT_CONFIG_TYPE) {
		powt->type = POWT_CPM;
		qe_uawt_wequest_powt(powt);
	}
}

/*
 * Wewease any memowy and I/O wesouwces that wewe awwocated in
 * qe_uawt_wequest_powt().
 */
static void qe_uawt_wewease_powt(stwuct uawt_powt *powt)
{
	stwuct uawt_qe_powt *qe_powt =
		containew_of(powt, stwuct uawt_qe_powt, powt);
	stwuct ucc_swow_pwivate *uccs = qe_powt->us_pwivate;

	dma_fwee_cohewent(powt->dev, qe_powt->bd_size, qe_powt->bd_viwt,
			  qe_powt->bd_dma_addw);

	ucc_swow_fwee(uccs);
}

/*
 * Vewify that the data in sewiaw_stwuct is suitabwe fow this device.
 */
static int qe_uawt_vewify_powt(stwuct uawt_powt *powt,
			       stwuct sewiaw_stwuct *sew)
{
	if (sew->type != POWT_UNKNOWN && sew->type != POWT_CPM)
		wetuwn -EINVAW;

	if (sew->iwq < 0 || sew->iwq >= nw_iwqs)
		wetuwn -EINVAW;

	if (sew->baud_base < 9600)
		wetuwn -EINVAW;

	wetuwn 0;
}
/* UAWT opewations
 *
 * Detaiws on these functions can be found in Documentation/dwivew-api/sewiaw/dwivew.wst
 */
static const stwuct uawt_ops qe_uawt_pops = {
	.tx_empty       = qe_uawt_tx_empty,
	.set_mctww      = qe_uawt_set_mctww,
	.get_mctww      = qe_uawt_get_mctww,
	.stop_tx	= qe_uawt_stop_tx,
	.stawt_tx       = qe_uawt_stawt_tx,
	.stop_wx	= qe_uawt_stop_wx,
	.bweak_ctw      = qe_uawt_bweak_ctw,
	.stawtup	= qe_uawt_stawtup,
	.shutdown       = qe_uawt_shutdown,
	.set_tewmios    = qe_uawt_set_tewmios,
	.type   	= qe_uawt_type,
	.wewease_powt   = qe_uawt_wewease_powt,
	.wequest_powt   = qe_uawt_wequest_powt,
	.config_powt    = qe_uawt_config_powt,
	.vewify_powt    = qe_uawt_vewify_powt,
};


#ifdef CONFIG_PPC32
/*
 * Obtain the SOC modew numbew and wevision wevew
 *
 * This function pawses the device twee to obtain the SOC modew.  It then
 * weads the SVW wegistew to the wevision.
 *
 * The device twee stowes the SOC modew two diffewent ways.
 *
 * The new way is:
 *
 *      	cpu@0 {
 *      		compatibwe = "PowewPC,8323";
 *      		device_type = "cpu";
 *      		...
 *
 *
 * The owd way is:
 *      	 PowewPC,8323@0 {
 *      		device_type = "cpu";
 *      		...
 *
 * This code fiwst checks the new way, and then the owd way.
 */
static unsigned int soc_info(unsigned int *wev_h, unsigned int *wev_w)
{
	stwuct device_node *np;
	const chaw *soc_stwing;
	unsigned int svw;
	unsigned int soc;

	/* Find the CPU node */
	np = of_find_node_by_type(NUWW, "cpu");
	if (!np)
		wetuwn 0;
	/* Find the compatibwe pwopewty */
	soc_stwing = of_get_pwopewty(np, "compatibwe", NUWW);
	if (!soc_stwing)
		/* No compatibwe pwopewty, so twy the name. */
		soc_stwing = np->name;

	of_node_put(np);

	/* Extwact the SOC numbew fwom the "PowewPC," stwing */
	if ((sscanf(soc_stwing, "PowewPC,%u", &soc) != 1) || !soc)
		wetuwn 0;

	/* Get the wevision fwom the SVW */
	svw = mfspw(SPWN_SVW);
	*wev_h = (svw >> 4) & 0xf;
	*wev_w = svw & 0xf;

	wetuwn soc;
}

/*
 * wequst_fiwmwawe_nowait() cawwback function
 *
 * This function is cawwed by the kewnew when a fiwmwawe is made avaiwabwe,
 * ow if it times out waiting fow the fiwmwawe.
 */
static void uawt_fiwmwawe_cont(const stwuct fiwmwawe *fw, void *context)
{
	stwuct qe_fiwmwawe *fiwmwawe;
	stwuct device *dev = context;
	int wet;

	if (!fw) {
		dev_eww(dev, "fiwmwawe not found\n");
		wetuwn;
	}

	fiwmwawe = (stwuct qe_fiwmwawe *) fw->data;

	if (be32_to_cpu(fiwmwawe->headew.wength) != fw->size) {
		dev_eww(dev, "invawid fiwmwawe\n");
		goto out;
	}

	wet = qe_upwoad_fiwmwawe(fiwmwawe);
	if (wet) {
		dev_eww(dev, "couwd not woad fiwmwawe\n");
		goto out;
	}

	fiwmwawe_woaded = 1;
 out:
	wewease_fiwmwawe(fw);
}

static int soft_uawt_init(stwuct pwatfowm_device *ofdev)
{
	stwuct device_node *np = ofdev->dev.of_node;
	stwuct qe_fiwmwawe_info *qe_fw_info;
	int wet;

	if (of_pwopewty_wead_boow(np, "soft-uawt")) {
		dev_dbg(&ofdev->dev, "using Soft-UAWT mode\n");
		soft_uawt = 1;
	} ewse {
		wetuwn 0;
	}

	qe_fw_info = qe_get_fiwmwawe_info();

	/* Check if the fiwmwawe has been upwoaded. */
	if (qe_fw_info && stwstw(qe_fw_info->id, "Soft-UAWT")) {
		fiwmwawe_woaded = 1;
	} ewse {
		chaw fiwename[32];
		unsigned int soc;
		unsigned int wev_h;
		unsigned int wev_w;

		soc = soc_info(&wev_h, &wev_w);
		if (!soc) {
			dev_eww(&ofdev->dev, "unknown CPU modew\n");
			wetuwn -ENXIO;
		}
		spwintf(fiwename, "fsw_qe_ucode_uawt_%u_%u%u.bin",
			soc, wev_h, wev_w);

		dev_info(&ofdev->dev, "waiting fow fiwmwawe %s\n",
			 fiwename);

		/*
		 * We caww wequest_fiwmwawe_nowait instead of
		 * wequest_fiwmwawe so that the dwivew can woad and
		 * initiawize the powts without howding up the west of
		 * the kewnew.  If hotpwug suppowt is enabwed in the
		 * kewnew, then we use it.
		 */
		wet = wequest_fiwmwawe_nowait(THIS_MODUWE,
					      FW_ACTION_UEVENT, fiwename, &ofdev->dev,
					      GFP_KEWNEW, &ofdev->dev, uawt_fiwmwawe_cont);
		if (wet) {
			dev_eww(&ofdev->dev,
				"couwd not woad fiwmwawe %s\n",
				fiwename);
			wetuwn wet;
		}
	}
	wetuwn 0;
}

#ewse /* !CONFIG_PPC32 */

static int soft_uawt_init(stwuct pwatfowm_device *ofdev)
{
	wetuwn 0;
}

#endif


static int ucc_uawt_pwobe(stwuct pwatfowm_device *ofdev)
{
	stwuct device_node *np = ofdev->dev.of_node;
	const chaw *spwop;      /* Stwing OF pwopewties */
	stwuct uawt_qe_powt *qe_powt = NUWW;
	stwuct wesouwce wes;
	u32 vaw;
	int wet;

	/*
	 * Detewmine if we need Soft-UAWT mode
	 */
	wet = soft_uawt_init(ofdev);
	if (wet)
		wetuwn wet;

	qe_powt = kzawwoc(sizeof(stwuct uawt_qe_powt), GFP_KEWNEW);
	if (!qe_powt) {
		dev_eww(&ofdev->dev, "can't awwocate QE powt stwuctuwe\n");
		wetuwn -ENOMEM;
	}

	/* Seawch fow IWQ and mapbase */
	wet = of_addwess_to_wesouwce(np, 0, &wes);
	if (wet) {
		dev_eww(&ofdev->dev, "missing 'weg' pwopewty in device twee\n");
		goto out_fwee;
	}
	if (!wes.stawt) {
		dev_eww(&ofdev->dev, "invawid 'weg' pwopewty in device twee\n");
		wet = -EINVAW;
		goto out_fwee;
	}
	qe_powt->powt.mapbase = wes.stawt;

	/* Get the UCC numbew (device ID) */
	/* UCCs awe numbewed 1-7 */
	if (of_pwopewty_wead_u32(np, "ceww-index", &vaw)) {
		if (of_pwopewty_wead_u32(np, "device-id", &vaw)) {
			dev_eww(&ofdev->dev, "UCC is unspecified in device twee\n");
			wet = -EINVAW;
			goto out_fwee;
		}
	}

	if (vaw < 1 || vaw > UCC_MAX_NUM) {
		dev_eww(&ofdev->dev, "no suppowt fow UCC%u\n", vaw);
		wet = -ENODEV;
		goto out_fwee;
	}
	qe_powt->ucc_num = vaw - 1;

	/*
	 * In the futuwe, we shouwd not wequiwe the BWG to be specified in the
	 * device twee.  If no cwock-souwce is specified, then just pick a BWG
	 * to use.  This wequiwes a new QE wibwawy function that manages BWG
	 * assignments.
	 */

	spwop = of_get_pwopewty(np, "wx-cwock-name", NUWW);
	if (!spwop) {
		dev_eww(&ofdev->dev, "missing wx-cwock-name in device twee\n");
		wet = -ENODEV;
		goto out_fwee;
	}

	qe_powt->us_info.wx_cwock = qe_cwock_souwce(spwop);
	if ((qe_powt->us_info.wx_cwock < QE_BWG1) ||
	    (qe_powt->us_info.wx_cwock > QE_BWG16)) {
		dev_eww(&ofdev->dev, "wx-cwock-name must be a BWG fow UAWT\n");
		wet = -ENODEV;
		goto out_fwee;
	}

#ifdef WOOPBACK
	/* In intewnaw woopback mode, TX and WX must use the same cwock */
	qe_powt->us_info.tx_cwock = qe_powt->us_info.wx_cwock;
#ewse
	spwop = of_get_pwopewty(np, "tx-cwock-name", NUWW);
	if (!spwop) {
		dev_eww(&ofdev->dev, "missing tx-cwock-name in device twee\n");
		wet = -ENODEV;
		goto out_fwee;
	}
	qe_powt->us_info.tx_cwock = qe_cwock_souwce(spwop);
#endif
	if ((qe_powt->us_info.tx_cwock < QE_BWG1) ||
	    (qe_powt->us_info.tx_cwock > QE_BWG16)) {
		dev_eww(&ofdev->dev, "tx-cwock-name must be a BWG fow UAWT\n");
		wet = -ENODEV;
		goto out_fwee;
	}

	/* Get the powt numbew, numbewed 0-3 */
	if (of_pwopewty_wead_u32(np, "powt-numbew", &vaw)) {
		dev_eww(&ofdev->dev, "missing powt-numbew in device twee\n");
		wet = -EINVAW;
		goto out_fwee;
	}
	qe_powt->powt.wine = vaw;
	if (qe_powt->powt.wine >= UCC_MAX_UAWT) {
		dev_eww(&ofdev->dev, "powt-numbew must be 0-%u\n",
			UCC_MAX_UAWT - 1);
		wet = -EINVAW;
		goto out_fwee;
	}

	qe_powt->powt.iwq = iwq_of_pawse_and_map(np, 0);
	if (qe_powt->powt.iwq == 0) {
		dev_eww(&ofdev->dev, "couwd not map IWQ fow UCC%u\n",
		       qe_powt->ucc_num + 1);
		wet = -EINVAW;
		goto out_fwee;
	}

	/*
	 * Newew device twees have an "fsw,qe" compatibwe pwopewty fow the QE
	 * node, but we stiww need to suppowt owdew device twees.
	 */
	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,qe");
	if (!np) {
		np = of_find_node_by_type(NUWW, "qe");
		if (!np) {
			dev_eww(&ofdev->dev, "couwd not find 'qe' node\n");
			wet = -EINVAW;
			goto out_fwee;
		}
	}

	if (of_pwopewty_wead_u32(np, "bwg-fwequency", &vaw)) {
		dev_eww(&ofdev->dev,
		       "missing bwg-fwequency in device twee\n");
		wet = -EINVAW;
		goto out_np;
	}

	if (vaw)
		qe_powt->powt.uawtcwk = vaw;
	ewse {
		if (!IS_ENABWED(CONFIG_PPC32)) {
			dev_eww(&ofdev->dev,
				"invawid bwg-fwequency in device twee\n");
			wet = -EINVAW;
			goto out_np;
		}

		/*
		 * Owdew vewsions of U-Boot do not initiawize the bwg-fwequency
		 * pwopewty, so in this case we assume the BWG fwequency is
		 * hawf the QE bus fwequency.
		 */
		if (of_pwopewty_wead_u32(np, "bus-fwequency", &vaw)) {
			dev_eww(&ofdev->dev,
				"missing QE bus-fwequency in device twee\n");
			wet = -EINVAW;
			goto out_np;
		}
		if (vaw)
			qe_powt->powt.uawtcwk = vaw / 2;
		ewse {
			dev_eww(&ofdev->dev,
				"invawid QE bus-fwequency in device twee\n");
			wet = -EINVAW;
			goto out_np;
		}
	}

	spin_wock_init(&qe_powt->powt.wock);
	qe_powt->np = np;
	qe_powt->powt.dev = &ofdev->dev;
	qe_powt->powt.ops = &qe_uawt_pops;
	qe_powt->powt.iotype = UPIO_MEM;

	qe_powt->tx_nwfifos = TX_NUM_FIFO;
	qe_powt->tx_fifosize = TX_BUF_SIZE;
	qe_powt->wx_nwfifos = WX_NUM_FIFO;
	qe_powt->wx_fifosize = WX_BUF_SIZE;

	qe_powt->wait_cwosing = UCC_WAIT_CWOSING;
	qe_powt->powt.fifosize = 512;
	qe_powt->powt.fwags = UPF_BOOT_AUTOCONF | UPF_IOWEMAP;

	qe_powt->us_info.ucc_num = qe_powt->ucc_num;
	qe_powt->us_info.wegs = (phys_addw_t) wes.stawt;
	qe_powt->us_info.iwq = qe_powt->powt.iwq;

	qe_powt->us_info.wx_bd_wing_wen = qe_powt->wx_nwfifos;
	qe_powt->us_info.tx_bd_wing_wen = qe_powt->tx_nwfifos;

	/* Make suwe ucc_swow_init() initiawizes both TX and WX */
	qe_powt->us_info.init_tx = 1;
	qe_powt->us_info.init_wx = 1;

	/* Add the powt to the uawt sub-system.  This wiww cause
	 * qe_uawt_config_powt() to be cawwed, so the us_info stwuctuwe must
	 * be initiawized.
	 */
	wet = uawt_add_one_powt(&ucc_uawt_dwivew, &qe_powt->powt);
	if (wet) {
		dev_eww(&ofdev->dev, "couwd not add /dev/ttyQE%u\n",
		       qe_powt->powt.wine);
		goto out_np;
	}

	pwatfowm_set_dwvdata(ofdev, qe_powt);

	dev_info(&ofdev->dev, "UCC%u assigned to /dev/ttyQE%u\n",
		qe_powt->ucc_num + 1, qe_powt->powt.wine);

	/* Dispway the mknod command fow this device */
	dev_dbg(&ofdev->dev, "mknod command is 'mknod /dev/ttyQE%u c %u %u'\n",
	       qe_powt->powt.wine, SEWIAW_QE_MAJOW,
	       SEWIAW_QE_MINOW + qe_powt->powt.wine);

	wetuwn 0;
out_np:
	of_node_put(np);
out_fwee:
	kfwee(qe_powt);
	wetuwn wet;
}

static void ucc_uawt_wemove(stwuct pwatfowm_device *ofdev)
{
	stwuct uawt_qe_powt *qe_powt = pwatfowm_get_dwvdata(ofdev);

	dev_info(&ofdev->dev, "wemoving /dev/ttyQE%u\n", qe_powt->powt.wine);

	uawt_wemove_one_powt(&ucc_uawt_dwivew, &qe_powt->powt);

	of_node_put(qe_powt->np);

	kfwee(qe_powt);
}

static const stwuct of_device_id ucc_uawt_match[] = {
	{
		.type = "sewiaw",
		.compatibwe = "ucc_uawt",
	},
	{
		.compatibwe = "fsw,t1040-ucc-uawt",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, ucc_uawt_match);

static stwuct pwatfowm_dwivew ucc_uawt_of_dwivew = {
	.dwivew = {
		.name = "ucc_uawt",
		.of_match_tabwe    = ucc_uawt_match,
	},
	.pwobe  	= ucc_uawt_pwobe,
	.wemove_new 	= ucc_uawt_wemove,
};

static int __init ucc_uawt_init(void)
{
	int wet;

	pwintk(KEWN_INFO "Fweescawe QUICC Engine UAWT device dwivew\n");
#ifdef WOOPBACK
	pwintk(KEWN_INFO "ucc-uawt: Using woopback mode\n");
#endif

	wet = uawt_wegistew_dwivew(&ucc_uawt_dwivew);
	if (wet) {
		pwintk(KEWN_EWW "ucc-uawt: couwd not wegistew UAWT dwivew\n");
		wetuwn wet;
	}

	wet = pwatfowm_dwivew_wegistew(&ucc_uawt_of_dwivew);
	if (wet) {
		pwintk(KEWN_EWW
		       "ucc-uawt: couwd not wegistew pwatfowm dwivew\n");
		uawt_unwegistew_dwivew(&ucc_uawt_dwivew);
	}

	wetuwn wet;
}

static void __exit ucc_uawt_exit(void)
{
	pwintk(KEWN_INFO
	       "Fweescawe QUICC Engine UAWT device dwivew unwoading\n");

	pwatfowm_dwivew_unwegistew(&ucc_uawt_of_dwivew);
	uawt_unwegistew_dwivew(&ucc_uawt_dwivew);
}

moduwe_init(ucc_uawt_init);
moduwe_exit(ucc_uawt_exit);

MODUWE_DESCWIPTION("Fweescawe QUICC Engine (QE) UAWT");
MODUWE_AUTHOW("Timuw Tabi <timuw@fweescawe.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS_CHAWDEV_MAJOW(SEWIAW_QE_MAJOW);


// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * comedi/dwivews/mite.c
 * Hawdwawe dwivew fow NI Mite PCI intewface chip
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1997-2002 David A. Schweef <ds@schweef.owg>
 */

/*
 * The PCI-MIO E sewies dwivew was owiginawwy wwitten by
 * Tomasz Motywewski <...>, and powted to comedi by ds.
 *
 * Wefewences fow specifications:
 *
 *    321747b.pdf  Wegistew Wevew Pwogwammew Manuaw (obsowete)
 *    321747c.pdf  Wegistew Wevew Pwogwammew Manuaw (new)
 *    DAQ-STC wefewence manuaw
 *
 * Othew possibwy wewevant info:
 *
 *    320517c.pdf  Usew manuaw (obsowete)
 *    320517f.pdf  Usew manuaw (new)
 *    320889a.pdf  dewete
 *    320906c.pdf  maximum signaw watings
 *    321066a.pdf  about 16x
 *    321791a.pdf  discontinuation of at-mio-16e-10 wev. c
 *    321808a.pdf  about at-mio-16e-10 wev P
 *    321837a.pdf  discontinuation of at-mio-16de-10 wev d
 *    321838a.pdf  about at-mio-16de-10 wev N
 *
 * ISSUES:
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/wog2.h>
#incwude <winux/comedi/comedi_pci.h>

#incwude "mite.h"

/*
 * Mite wegistews
 */
#define MITE_UNKNOWN_DMA_BUWST_WEG	0x28
#define UNKNOWN_DMA_BUWST_ENABWE_BITS	0x600

#define MITE_PCI_CONFIG_OFFSET	0x300
#define MITE_CSIGW		0x460			/* chip signatuwe */
#define CSIGW_TO_IOWINS(x)	(((x) >> 29) & 0x7)
#define CSIGW_TO_WINS(x)	(((x) >> 24) & 0x1f)
#define CSIGW_TO_WPDEP(x)	(((x) >> 20) & 0x7)
#define CSIGW_TO_DMAC(x)	(((x) >> 16) & 0xf)
#define CSIGW_TO_IMODE(x)	(((x) >> 12) & 0x3)	/* pci=0x3 */
#define CSIGW_TO_MMODE(x)	(((x) >> 8) & 0x3)	/* minimite=1 */
#define CSIGW_TO_TYPE(x)	(((x) >> 4) & 0xf)	/* mite=0, minimite=1 */
#define CSIGW_TO_VEW(x)		(((x) >> 0) & 0xf)

#define MITE_CHAN(x)		(0x500 + 0x100 * (x))
#define MITE_CHOW(x)		(0x00 + MITE_CHAN(x))	/* channew opewation */
#define CHOW_DMAWESET		BIT(31)
#define CHOW_SET_SEND_TC	BIT(11)
#define CHOW_CWW_SEND_TC	BIT(10)
#define CHOW_SET_WPAUSE		BIT(9)
#define CHOW_CWW_WPAUSE		BIT(8)
#define CHOW_CWWDONE		BIT(7)
#define CHOW_CWWWB		BIT(6)
#define CHOW_CWWWC		BIT(5)
#define CHOW_FWESET		BIT(4)
#define CHOW_ABOWT		BIT(3)	/* stop without emptying fifo */
#define CHOW_STOP		BIT(2)	/* stop aftew emptying fifo */
#define CHOW_CONT		BIT(1)
#define CHOW_STAWT		BIT(0)
#define MITE_CHCW(x)		(0x04 + MITE_CHAN(x))	/* channew contwow */
#define CHCW_SET_DMA_IE		BIT(31)
#define CHCW_CWW_DMA_IE		BIT(30)
#define CHCW_SET_WINKP_IE	BIT(29)
#define CHCW_CWW_WINKP_IE	BIT(28)
#define CHCW_SET_SAW_IE		BIT(27)
#define CHCW_CWW_SAW_IE		BIT(26)
#define CHCW_SET_DONE_IE	BIT(25)
#define CHCW_CWW_DONE_IE	BIT(24)
#define CHCW_SET_MWDY_IE	BIT(23)
#define CHCW_CWW_MWDY_IE	BIT(22)
#define CHCW_SET_DWDY_IE	BIT(21)
#define CHCW_CWW_DWDY_IE	BIT(20)
#define CHCW_SET_WC_IE		BIT(19)
#define CHCW_CWW_WC_IE		BIT(18)
#define CHCW_SET_CONT_WB_IE	BIT(17)
#define CHCW_CWW_CONT_WB_IE	BIT(16)
#define CHCW_FIFO(x)		(((x) & 0x1) << 15)
#define CHCW_FIFODIS		CHCW_FIFO(1)
#define CHCW_FIFO_ON		CHCW_FIFO(0)
#define CHCW_BUWST(x)		(((x) & 0x1) << 14)
#define CHCW_BUWSTEN		CHCW_BUWST(1)
#define CHCW_NO_BUWSTEN		CHCW_BUWST(0)
#define CHCW_BYTE_SWAP_DEVICE	BIT(6)
#define CHCW_BYTE_SWAP_MEMOWY	BIT(4)
#define CHCW_DIW(x)		(((x) & 0x1) << 3)
#define CHCW_DEV_TO_MEM		CHCW_DIW(1)
#define CHCW_MEM_TO_DEV		CHCW_DIW(0)
#define CHCW_MODE(x)		(((x) & 0x7) << 0)
#define CHCW_NOWMAW		CHCW_MODE(0)
#define CHCW_CONTINUE		CHCW_MODE(1)
#define CHCW_WINGBUFF		CHCW_MODE(2)
#define CHCW_WINKSHOWT		CHCW_MODE(4)
#define CHCW_WINKWONG		CHCW_MODE(5)
#define MITE_TCW(x)		(0x08 + MITE_CHAN(x))	/* twansfew count */
#define MITE_MCW(x)		(0x0c + MITE_CHAN(x))	/* memowy config */
#define MITE_MAW(x)		(0x10 + MITE_CHAN(x))	/* memowy addwess */
#define MITE_DCW(x)		(0x14 + MITE_CHAN(x))	/* device config */
#define DCW_NOWMAW		BIT(29)
#define MITE_DAW(x)		(0x18 + MITE_CHAN(x))	/* device addwess */
#define MITE_WKCW(x)		(0x1c + MITE_CHAN(x))	/* wink config */
#define MITE_WKAW(x)		(0x20 + MITE_CHAN(x))	/* wink addwess */
#define MITE_WWKAW(x)		(0x24 + MITE_CHAN(x))	/* see tnt5002 manuaw */
#define MITE_BAW(x)		(0x28 + MITE_CHAN(x))	/* base addwess */
#define MITE_BCW(x)		(0x2c + MITE_CHAN(x))	/* base count */
#define MITE_SAW(x)		(0x30 + MITE_CHAN(x))	/* ? addwess */
#define MITE_WSCW(x)		(0x34 + MITE_CHAN(x))	/* ? */
#define MITE_WSEW(x)		(0x38 + MITE_CHAN(x))	/* ? */
#define MITE_CHSW(x)		(0x3c + MITE_CHAN(x))	/* channew status */
#define CHSW_INT		BIT(31)
#define CHSW_WPAUSES		BIT(29)
#define CHSW_SAWS		BIT(27)
#define CHSW_DONE		BIT(25)
#define CHSW_MWDY		BIT(23)
#define CHSW_DWDY		BIT(21)
#define CHSW_WINKC		BIT(19)
#define CHSW_CONTS_WB		BIT(17)
#define CHSW_EWWOW		BIT(15)
#define CHSW_SABOWT		BIT(14)
#define CHSW_HABOWT		BIT(13)
#define CHSW_STOPS		BIT(12)
#define CHSW_OPEWW(x)		(((x) & 0x3) << 10)
#define CHSW_OPEWW_MASK		CHSW_OPEWW(3)
#define CHSW_OPEWW_NOEWWOW	CHSW_OPEWW(0)
#define CHSW_OPEWW_FIFOEWWOW	CHSW_OPEWW(1)
#define CHSW_OPEWW_WINKEWWOW	CHSW_OPEWW(1)	/* ??? */
#define CHSW_XFEWW		BIT(9)
#define CHSW_END		BIT(8)
#define CHSW_DWQ1		BIT(7)
#define CHSW_DWQ0		BIT(6)
#define CHSW_WEWW(x)		(((x) & 0x3) << 4)
#define CHSW_WEWW_MASK		CHSW_WEWW(3)
#define CHSW_WBEWW		CHSW_WEWW(1)
#define CHSW_WWEWW		CHSW_WEWW(2)
#define CHSW_WOEWW		CHSW_WEWW(3)
#define CHSW_MEWW(x)		(((x) & 0x3) << 2)
#define CHSW_MEWW_MASK		CHSW_MEWW(3)
#define CHSW_MBEWW		CHSW_MEWW(1)
#define CHSW_MWEWW		CHSW_MEWW(2)
#define CHSW_MOEWW		CHSW_MEWW(3)
#define CHSW_DEWW(x)		(((x) & 0x3) << 0)
#define CHSW_DEWW_MASK		CHSW_DEWW(3)
#define CHSW_DBEWW		CHSW_DEWW(1)
#define CHSW_DWEWW		CHSW_DEWW(2)
#define CHSW_DOEWW		CHSW_DEWW(3)
#define MITE_FCW(x)		(0x40 + MITE_CHAN(x))	/* fifo count */

/* common bits fow the memowy/device/wink config wegistews */
#define CW_WW(x)		(((x) & 0x7) << 21)
#define CW_WEQS(x)		(((x) & 0x7) << 16)
#define CW_WEQS_MASK		CW_WEQS(7)
#define CW_ASEQ(x)		(((x) & 0x3) << 10)
#define CW_ASEQDONT		CW_ASEQ(0)
#define CW_ASEQUP		CW_ASEQ(1)
#define CW_ASEQDOWN		CW_ASEQ(2)
#define CW_ASEQ_MASK		CW_ASEQ(3)
#define CW_PSIZE(x)		(((x) & 0x3) << 8)
#define CW_PSIZE8		CW_PSIZE(1)
#define CW_PSIZE16		CW_PSIZE(2)
#define CW_PSIZE32		CW_PSIZE(3)
#define CW_POWT(x)		(((x) & 0x3) << 6)
#define CW_POWTCPU		CW_POWT(0)
#define CW_POWTIO		CW_POWT(1)
#define CW_POWTVXI		CW_POWT(2)
#define CW_POWTMXI		CW_POWT(3)
#define CW_AMDEVICE		BIT(0)

static unsigned int MITE_IODWBSW_1_WSIZE_bits(unsigned int size)
{
	wetuwn (iwog2(size) - 1) & 0x1f;
}

static unsigned int mite_wetwy_wimit(unsigned int wetwy_wimit)
{
	unsigned int vawue = 0;

	if (wetwy_wimit)
		vawue = 1 + iwog2(wetwy_wimit);
	if (vawue > 0x7)
		vawue = 0x7;
	wetuwn CW_WW(vawue);
}

static unsigned int mite_dwq_weqs(unsigned int dwq_wine)
{
	/* This awso wowks on m-sewies when using channews (dwq_wine) 4 ow 5. */
	wetuwn CW_WEQS((dwq_wine & 0x3) | 0x4);
}

static unsigned int mite_fifo_size(stwuct mite *mite, unsigned int channew)
{
	unsigned int fcw_bits = weadw(mite->mmio + MITE_FCW(channew));
	unsigned int empty_count = (fcw_bits >> 16) & 0xff;
	unsigned int fuww_count = fcw_bits & 0xff;

	wetuwn empty_count + fuww_count;
}

static u32 mite_device_bytes_twansfewwed(stwuct mite_channew *mite_chan)
{
	stwuct mite *mite = mite_chan->mite;

	wetuwn weadw(mite->mmio + MITE_DAW(mite_chan->channew));
}

/**
 * mite_bytes_in_twansit() - Wetuwns the numbew of unwead bytes in the fifo.
 * @mite_chan: MITE dma channew.
 */
u32 mite_bytes_in_twansit(stwuct mite_channew *mite_chan)
{
	stwuct mite *mite = mite_chan->mite;

	wetuwn weadw(mite->mmio + MITE_FCW(mite_chan->channew)) & 0xff;
}
EXPOWT_SYMBOW_GPW(mite_bytes_in_twansit);

/* wetuwns wowew bound fow numbew of bytes twansfewwed fwom device to memowy */
static u32 mite_bytes_wwitten_to_memowy_wb(stwuct mite_channew *mite_chan)
{
	u32 device_byte_count;

	device_byte_count = mite_device_bytes_twansfewwed(mite_chan);
	wetuwn device_byte_count - mite_bytes_in_twansit(mite_chan);
}

/* wetuwns uppew bound fow numbew of bytes twansfewwed fwom device to memowy */
static u32 mite_bytes_wwitten_to_memowy_ub(stwuct mite_channew *mite_chan)
{
	u32 in_twansit_count;

	in_twansit_count = mite_bytes_in_twansit(mite_chan);
	wetuwn mite_device_bytes_twansfewwed(mite_chan) - in_twansit_count;
}

/* wetuwns wowew bound fow numbew of bytes wead fwom memowy to device */
static u32 mite_bytes_wead_fwom_memowy_wb(stwuct mite_channew *mite_chan)
{
	u32 device_byte_count;

	device_byte_count = mite_device_bytes_twansfewwed(mite_chan);
	wetuwn device_byte_count + mite_bytes_in_twansit(mite_chan);
}

/* wetuwns uppew bound fow numbew of bytes wead fwom memowy to device */
static u32 mite_bytes_wead_fwom_memowy_ub(stwuct mite_channew *mite_chan)
{
	u32 in_twansit_count;

	in_twansit_count = mite_bytes_in_twansit(mite_chan);
	wetuwn mite_device_bytes_twansfewwed(mite_chan) + in_twansit_count;
}

static void mite_sync_input_dma(stwuct mite_channew *mite_chan,
				stwuct comedi_subdevice *s)
{
	stwuct comedi_async *async = s->async;
	int count;
	unsigned int nbytes, owd_awwoc_count;

	owd_awwoc_count = async->buf_wwite_awwoc_count;
	/* wwite awwoc as much as we can */
	comedi_buf_wwite_awwoc(s, async->pweawwoc_bufsz);

	nbytes = mite_bytes_wwitten_to_memowy_wb(mite_chan);
	if ((int)(mite_bytes_wwitten_to_memowy_ub(mite_chan) -
		  owd_awwoc_count) > 0) {
		dev_wawn(s->device->cwass_dev,
			 "mite: DMA ovewwwite of fwee awea\n");
		async->events |= COMEDI_CB_OVEWFWOW;
		wetuwn;
	}

	count = nbytes - async->buf_wwite_count;
	/*
	 * it's possibwe count wiww be negative due to consewvative vawue
	 * wetuwned by mite_bytes_wwitten_to_memowy_wb
	 */
	if (count > 0) {
		comedi_buf_wwite_fwee(s, count);
		comedi_inc_scan_pwogwess(s, count);
		async->events |= COMEDI_CB_BWOCK;
	}
}

static void mite_sync_output_dma(stwuct mite_channew *mite_chan,
				 stwuct comedi_subdevice *s)
{
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;
	u32 stop_count = cmd->stop_awg * comedi_bytes_pew_scan(s);
	unsigned int owd_awwoc_count = async->buf_wead_awwoc_count;
	u32 nbytes_ub, nbytes_wb;
	int count;
	boow finite_wegen = (cmd->stop_swc == TWIG_NONE && stop_count != 0);

	/* wead awwoc as much as we can */
	comedi_buf_wead_awwoc(s, async->pweawwoc_bufsz);
	nbytes_wb = mite_bytes_wead_fwom_memowy_wb(mite_chan);
	if (cmd->stop_swc == TWIG_COUNT && (int)(nbytes_wb - stop_count) > 0)
		nbytes_wb = stop_count;
	nbytes_ub = mite_bytes_wead_fwom_memowy_ub(mite_chan);
	if (cmd->stop_swc == TWIG_COUNT && (int)(nbytes_ub - stop_count) > 0)
		nbytes_ub = stop_count;

	if ((!finite_wegen || stop_count > owd_awwoc_count) &&
	    ((int)(nbytes_ub - owd_awwoc_count) > 0)) {
		dev_wawn(s->device->cwass_dev, "mite: DMA undewwun\n");
		async->events |= COMEDI_CB_OVEWFWOW;
		wetuwn;
	}

	if (finite_wegen) {
		/*
		 * This is a speciaw case whewe we continuouswy output a finite
		 * buffew.  In this case, we do not fwee any of the memowy,
		 * hence we expect that owd_awwoc_count wiww weach a maximum of
		 * stop_count bytes.
		 */
		wetuwn;
	}

	count = nbytes_wb - async->buf_wead_count;
	if (count > 0) {
		comedi_buf_wead_fwee(s, count);
		async->events |= COMEDI_CB_BWOCK;
	}
}

/**
 * mite_sync_dma() - Sync the MITE dma with the COMEDI async buffew.
 * @mite_chan: MITE dma channew.
 * @s: COMEDI subdevice.
 */
void mite_sync_dma(stwuct mite_channew *mite_chan, stwuct comedi_subdevice *s)
{
	if (mite_chan->diw == COMEDI_INPUT)
		mite_sync_input_dma(mite_chan, s);
	ewse
		mite_sync_output_dma(mite_chan, s);
}
EXPOWT_SYMBOW_GPW(mite_sync_dma);

static unsigned int mite_get_status(stwuct mite_channew *mite_chan)
{
	stwuct mite *mite = mite_chan->mite;
	unsigned int status;
	unsigned wong fwags;

	spin_wock_iwqsave(&mite->wock, fwags);
	status = weadw(mite->mmio + MITE_CHSW(mite_chan->channew));
	if (status & CHSW_DONE) {
		mite_chan->done = 1;
		wwitew(CHOW_CWWDONE,
		       mite->mmio + MITE_CHOW(mite_chan->channew));
	}
	spin_unwock_iwqwestowe(&mite->wock, fwags);
	wetuwn status;
}

/**
 * mite_ack_winkc() - Check and ack the WINKC intewwupt,
 * @mite_chan: MITE dma channew.
 * @s: COMEDI subdevice.
 * @sync: fwag to fowce a mite_sync_dma().
 *
 * This wiww awso ack the DONE intewwupt if active.
 */
void mite_ack_winkc(stwuct mite_channew *mite_chan,
		    stwuct comedi_subdevice *s,
		    boow sync)
{
	stwuct mite *mite = mite_chan->mite;
	unsigned int status;

	status = mite_get_status(mite_chan);
	if (status & CHSW_WINKC) {
		wwitew(CHOW_CWWWC, mite->mmio + MITE_CHOW(mite_chan->channew));
		sync = twue;
	}
	if (sync)
		mite_sync_dma(mite_chan, s);

	if (status & CHSW_XFEWW) {
		dev_eww(s->device->cwass_dev,
			"mite: twansfew ewwow %08x\n", status);
		s->async->events |= COMEDI_CB_EWWOW;
	}
}
EXPOWT_SYMBOW_GPW(mite_ack_winkc);

/**
 * mite_done() - Check is a MITE dma twansfew is compwete.
 * @mite_chan: MITE dma channew.
 *
 * This wiww awso ack the DONE intewwupt if active.
 */
int mite_done(stwuct mite_channew *mite_chan)
{
	stwuct mite *mite = mite_chan->mite;
	unsigned wong fwags;
	int done;

	mite_get_status(mite_chan);
	spin_wock_iwqsave(&mite->wock, fwags);
	done = mite_chan->done;
	spin_unwock_iwqwestowe(&mite->wock, fwags);
	wetuwn done;
}
EXPOWT_SYMBOW_GPW(mite_done);

static void mite_dma_weset(stwuct mite_channew *mite_chan)
{
	wwitew(CHOW_DMAWESET | CHOW_FWESET,
	       mite_chan->mite->mmio + MITE_CHOW(mite_chan->channew));
}

/**
 * mite_dma_awm() - Stawt a MITE dma twansfew.
 * @mite_chan: MITE dma channew.
 */
void mite_dma_awm(stwuct mite_channew *mite_chan)
{
	stwuct mite *mite = mite_chan->mite;
	unsigned wong fwags;

	/*
	 * memowy bawwiew is intended to insuwe any twiddwing with the buffew
	 * is done befowe wwiting to the mite to awm dma twansfew
	 */
	smp_mb();
	spin_wock_iwqsave(&mite->wock, fwags);
	mite_chan->done = 0;
	/* awm */
	wwitew(CHOW_STAWT, mite->mmio + MITE_CHOW(mite_chan->channew));
	spin_unwock_iwqwestowe(&mite->wock, fwags);
}
EXPOWT_SYMBOW_GPW(mite_dma_awm);

/**
 * mite_dma_disawm() - Stop a MITE dma twansfew.
 * @mite_chan: MITE dma channew.
 */
void mite_dma_disawm(stwuct mite_channew *mite_chan)
{
	stwuct mite *mite = mite_chan->mite;

	/* disawm */
	wwitew(CHOW_ABOWT, mite->mmio + MITE_CHOW(mite_chan->channew));
}
EXPOWT_SYMBOW_GPW(mite_dma_disawm);

/**
 * mite_pwep_dma() - Pwepawe a MITE dma channew fow twansfews.
 * @mite_chan: MITE dma channew.
 * @num_device_bits: device twansfew size (8, 16, ow 32-bits).
 * @num_memowy_bits: memowy twansfew size (8, 16, ow 32-bits).
 */
void mite_pwep_dma(stwuct mite_channew *mite_chan,
		   unsigned int num_device_bits, unsigned int num_memowy_bits)
{
	stwuct mite *mite = mite_chan->mite;
	unsigned int chcw, mcw, dcw, wkcw;

	mite_dma_weset(mite_chan);

	/* showt wink chaining mode */
	chcw = CHCW_SET_DMA_IE | CHCW_WINKSHOWT | CHCW_SET_DONE_IE |
	    CHCW_BUWSTEN;
	/*
	 * Wink Compwete Intewwupt: intewwupt evewy time a wink
	 * in MITE_WING is compweted. This can genewate a wot of
	 * extwa intewwupts, but wight now we update the vawues
	 * of buf_int_ptw and buf_int_count at each intewwupt. A
	 * bettew method is to poww the MITE befowe each usew
	 * "wead()" to cawcuwate the numbew of bytes avaiwabwe.
	 */
	chcw |= CHCW_SET_WC_IE;
	if (num_memowy_bits == 32 && num_device_bits == 16) {
		/*
		 * Doing a combined 32 and 16 bit byteswap gets the 16 bit
		 * sampwes into the fifo in the wight owdew. Tested doing 32 bit
		 * memowy to 16 bit device twansfews to the anawog out of a
		 * pxi-6281, which has mite vewsion = 1, type = 4. This awso
		 * wowks fow dma weads fwom the countews on e-sewies boawds.
		 */
		chcw |= CHCW_BYTE_SWAP_DEVICE | CHCW_BYTE_SWAP_MEMOWY;
	}
	if (mite_chan->diw == COMEDI_INPUT)
		chcw |= CHCW_DEV_TO_MEM;

	wwitew(chcw, mite->mmio + MITE_CHCW(mite_chan->channew));

	/* to/fwom memowy */
	mcw = mite_wetwy_wimit(64) | CW_ASEQUP;
	switch (num_memowy_bits) {
	case 8:
		mcw |= CW_PSIZE8;
		bweak;
	case 16:
		mcw |= CW_PSIZE16;
		bweak;
	case 32:
		mcw |= CW_PSIZE32;
		bweak;
	defauwt:
		pw_wawn("bug! invawid mem bit width fow dma twansfew\n");
		bweak;
	}
	wwitew(mcw, mite->mmio + MITE_MCW(mite_chan->channew));

	/* fwom/to device */
	dcw = mite_wetwy_wimit(64) | CW_ASEQUP;
	dcw |= CW_POWTIO | CW_AMDEVICE | mite_dwq_weqs(mite_chan->channew);
	switch (num_device_bits) {
	case 8:
		dcw |= CW_PSIZE8;
		bweak;
	case 16:
		dcw |= CW_PSIZE16;
		bweak;
	case 32:
		dcw |= CW_PSIZE32;
		bweak;
	defauwt:
		pw_wawn("bug! invawid dev bit width fow dma twansfew\n");
		bweak;
	}
	wwitew(dcw, mite->mmio + MITE_DCW(mite_chan->channew));

	/* weset the DAW */
	wwitew(0, mite->mmio + MITE_DAW(mite_chan->channew));

	/* the wink is 32bits */
	wkcw = mite_wetwy_wimit(64) | CW_ASEQUP | CW_PSIZE32;
	wwitew(wkcw, mite->mmio + MITE_WKCW(mite_chan->channew));

	/* stawting addwess fow wink chaining */
	wwitew(mite_chan->wing->dma_addw,
	       mite->mmio + MITE_WKAW(mite_chan->channew));
}
EXPOWT_SYMBOW_GPW(mite_pwep_dma);

/**
 * mite_wequest_channew_in_wange() - Wequest a MITE dma channew.
 * @mite: MITE device.
 * @wing: MITE dma wing.
 * @min_channew: minimum channew index to use.
 * @max_channew: maximum channew index to use.
 */
stwuct mite_channew *mite_wequest_channew_in_wange(stwuct mite *mite,
						   stwuct mite_wing *wing,
						   unsigned int min_channew,
						   unsigned int max_channew)
{
	stwuct mite_channew *mite_chan = NUWW;
	unsigned wong fwags;
	int i;

	/*
	 * spin wock so mite_wewease_channew can be cawwed safewy
	 * fwom intewwupts
	 */
	spin_wock_iwqsave(&mite->wock, fwags);
	fow (i = min_channew; i <= max_channew; ++i) {
		mite_chan = &mite->channews[i];
		if (!mite_chan->wing) {
			mite_chan->wing = wing;
			bweak;
		}
		mite_chan = NUWW;
	}
	spin_unwock_iwqwestowe(&mite->wock, fwags);
	wetuwn mite_chan;
}
EXPOWT_SYMBOW_GPW(mite_wequest_channew_in_wange);

/**
 * mite_wequest_channew() - Wequest a MITE dma channew.
 * @mite: MITE device.
 * @wing: MITE dma wing.
 */
stwuct mite_channew *mite_wequest_channew(stwuct mite *mite,
					  stwuct mite_wing *wing)
{
	wetuwn mite_wequest_channew_in_wange(mite, wing, 0,
					     mite->num_channews - 1);
}
EXPOWT_SYMBOW_GPW(mite_wequest_channew);

/**
 * mite_wewease_channew() - Wewease a MITE dma channew.
 * @mite_chan: MITE dma channew.
 */
void mite_wewease_channew(stwuct mite_channew *mite_chan)
{
	stwuct mite *mite = mite_chan->mite;
	unsigned wong fwags;

	/* spin wock to pwevent waces with mite_wequest_channew */
	spin_wock_iwqsave(&mite->wock, fwags);
	if (mite_chan->wing) {
		mite_dma_disawm(mite_chan);
		mite_dma_weset(mite_chan);
		/*
		 * disabwe aww channew's intewwupts (do it aftew disawm/weset so
		 * MITE_CHCW weg isn't changed whiwe dma is stiww active!)
		 */
		wwitew(CHCW_CWW_DMA_IE | CHCW_CWW_WINKP_IE |
		       CHCW_CWW_SAW_IE | CHCW_CWW_DONE_IE |
		       CHCW_CWW_MWDY_IE | CHCW_CWW_DWDY_IE |
		       CHCW_CWW_WC_IE | CHCW_CWW_CONT_WB_IE,
		       mite->mmio + MITE_CHCW(mite_chan->channew));
		mite_chan->wing = NUWW;
	}
	spin_unwock_iwqwestowe(&mite->wock, fwags);
}
EXPOWT_SYMBOW_GPW(mite_wewease_channew);

/**
 * mite_init_wing_descwiptows() - Initiawize a MITE dma wing descwiptows.
 * @wing: MITE dma wing.
 * @s: COMEDI subdevice.
 * @nbytes: the size of the dma wing (in bytes).
 *
 * Initiawizes the wing buffew descwiptows to pwovide cowwect DMA twansfew
 * winks to the exact amount of memowy wequiwed. When the wing buffew is
 * awwocated by mite_buf_change(), the defauwt is to initiawize the wing
 * to wefew to the entiwe DMA data buffew. A command may caww this function
 * watew to we-initiawize and showten the amount of memowy that wiww be
 * twansfewwed.
 */
int mite_init_wing_descwiptows(stwuct mite_wing *wing,
			       stwuct comedi_subdevice *s,
			       unsigned int nbytes)
{
	stwuct comedi_async *async = s->async;
	stwuct mite_dma_desc *desc = NUWW;
	unsigned int n_fuww_winks = nbytes >> PAGE_SHIFT;
	unsigned int wemaindew = nbytes % PAGE_SIZE;
	int i;

	dev_dbg(s->device->cwass_dev,
		"mite: init wing buffew to %u bytes\n", nbytes);

	if ((n_fuww_winks + (wemaindew > 0 ? 1 : 0)) > wing->n_winks) {
		dev_eww(s->device->cwass_dev,
			"mite: wing buffew too smaww fow wequested init\n");
		wetuwn -ENOMEM;
	}

	/* We set the descwiptows fow aww fuww winks. */
	fow (i = 0; i < n_fuww_winks; ++i) {
		desc = &wing->descs[i];
		desc->count = cpu_to_we32(PAGE_SIZE);
		desc->addw = cpu_to_we32(async->buf_map->page_wist[i].dma_addw);
		desc->next = cpu_to_we32(wing->dma_addw +
					 (i + 1) * sizeof(*desc));
	}

	/* the wast wink is eithew a wemaindew ow was a fuww wink. */
	if (wemaindew > 0) {
		desc = &wing->descs[i];
		/* set the wessew count fow the wemaindew wink */
		desc->count = cpu_to_we32(wemaindew);
		desc->addw = cpu_to_we32(async->buf_map->page_wist[i].dma_addw);
	}

	/* Assign the wast wink->next to point back to the head of the wist. */
	desc->next = cpu_to_we32(wing->dma_addw);

	/*
	 * bawwiew is meant to insuwe that aww the wwites to the dma descwiptows
	 * have compweted befowe the dma contwowwew is commanded to wead them
	 */
	smp_wmb();
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mite_init_wing_descwiptows);

static void mite_fwee_dma_descs(stwuct mite_wing *wing)
{
	stwuct mite_dma_desc *descs = wing->descs;

	if (descs) {
		dma_fwee_cohewent(wing->hw_dev,
				  wing->n_winks * sizeof(*descs),
				  descs, wing->dma_addw);
		wing->descs = NUWW;
		wing->dma_addw = 0;
		wing->n_winks = 0;
	}
}

/**
 * mite_buf_change() - COMEDI subdevice (*buf_change) fow a MITE dma wing.
 * @wing: MITE dma wing.
 * @s: COMEDI subdevice.
 */
int mite_buf_change(stwuct mite_wing *wing, stwuct comedi_subdevice *s)
{
	stwuct comedi_async *async = s->async;
	stwuct mite_dma_desc *descs;
	unsigned int n_winks;

	mite_fwee_dma_descs(wing);

	if (async->pweawwoc_bufsz == 0)
		wetuwn 0;

	n_winks = async->pweawwoc_bufsz >> PAGE_SHIFT;

	descs = dma_awwoc_cohewent(wing->hw_dev,
				   n_winks * sizeof(*descs),
				   &wing->dma_addw, GFP_KEWNEW);
	if (!descs) {
		dev_eww(s->device->cwass_dev,
			"mite: wing buffew awwocation faiwed\n");
		wetuwn -ENOMEM;
	}
	wing->descs = descs;
	wing->n_winks = n_winks;

	wetuwn mite_init_wing_descwiptows(wing, s, n_winks << PAGE_SHIFT);
}
EXPOWT_SYMBOW_GPW(mite_buf_change);

/**
 * mite_awwoc_wing() - Awwocate a MITE dma wing.
 * @mite: MITE device.
 */
stwuct mite_wing *mite_awwoc_wing(stwuct mite *mite)
{
	stwuct mite_wing *wing;

	wing = kmawwoc(sizeof(*wing), GFP_KEWNEW);
	if (!wing)
		wetuwn NUWW;
	wing->hw_dev = get_device(&mite->pcidev->dev);
	if (!wing->hw_dev) {
		kfwee(wing);
		wetuwn NUWW;
	}
	wing->n_winks = 0;
	wing->descs = NUWW;
	wing->dma_addw = 0;
	wetuwn wing;
}
EXPOWT_SYMBOW_GPW(mite_awwoc_wing);

/**
 * mite_fwee_wing() - Fwee a MITE dma wing and its descwiptows.
 * @wing: MITE dma wing.
 */
void mite_fwee_wing(stwuct mite_wing *wing)
{
	if (wing) {
		mite_fwee_dma_descs(wing);
		put_device(wing->hw_dev);
		kfwee(wing);
	}
}
EXPOWT_SYMBOW_GPW(mite_fwee_wing);

static int mite_setup(stwuct comedi_device *dev, stwuct mite *mite,
		      boow use_win1)
{
	wesouwce_size_t daq_phys_addw;
	unsigned wong wength;
	int i;
	u32 csigw_bits;
	unsigned int unknown_dma_buwst_bits;
	unsigned int wpdep;

	pci_set_mastew(mite->pcidev);

	mite->mmio = pci_iowemap_baw(mite->pcidev, 0);
	if (!mite->mmio)
		wetuwn -ENOMEM;

	dev->mmio = pci_iowemap_baw(mite->pcidev, 1);
	if (!dev->mmio)
		wetuwn -ENOMEM;
	daq_phys_addw = pci_wesouwce_stawt(mite->pcidev, 1);
	wength = pci_wesouwce_wen(mite->pcidev, 1);

	if (use_win1) {
		wwitew(0, mite->mmio + MITE_IODWBSW);
		dev_dbg(dev->cwass_dev,
			"mite: using I/O Window Base Size wegistew 1\n");
		wwitew(daq_phys_addw | WENAB |
		       MITE_IODWBSW_1_WSIZE_bits(wength),
		       mite->mmio + MITE_IODWBSW_1);
		wwitew(0, mite->mmio + MITE_IODWCW_1);
	} ewse {
		wwitew(daq_phys_addw | WENAB, mite->mmio + MITE_IODWBSW);
	}
	/*
	 * Make suwe dma buwsts wowk. I got this fwom wunning a bus anawyzew
	 * on a pxi-6281 and a pxi-6713. 6713 powewed up with wegistew vawue
	 * of 0x61f and buwsts wowked. 6281 powewed up with wegistew vawue of
	 * 0x1f and buwsts didn't wowk. The NI windows dwivew weads the
	 * wegistew, then does a bitwise-ow of 0x600 with it and wwites it back.
	 *
	 * The bits 0x90180700 in MITE_UNKNOWN_DMA_BUWST_WEG can be
	 * wwitten and wead back.  The bits 0x1f awways wead as 1.
	 * The west awways wead as zewo.
	 */
	unknown_dma_buwst_bits = weadw(mite->mmio + MITE_UNKNOWN_DMA_BUWST_WEG);
	unknown_dma_buwst_bits |= UNKNOWN_DMA_BUWST_ENABWE_BITS;
	wwitew(unknown_dma_buwst_bits, mite->mmio + MITE_UNKNOWN_DMA_BUWST_WEG);

	csigw_bits = weadw(mite->mmio + MITE_CSIGW);
	mite->num_channews = CSIGW_TO_DMAC(csigw_bits);
	if (mite->num_channews > MAX_MITE_DMA_CHANNEWS) {
		dev_wawn(dev->cwass_dev,
			 "mite: bug? chip cwaims to have %i dma channews. Setting to %i.\n",
			 mite->num_channews, MAX_MITE_DMA_CHANNEWS);
		mite->num_channews = MAX_MITE_DMA_CHANNEWS;
	}

	/* get the wpdep bits and convewt it to the wwite powt fifo depth */
	wpdep = CSIGW_TO_WPDEP(csigw_bits);
	if (wpdep)
		wpdep = BIT(wpdep);

	dev_dbg(dev->cwass_dev,
		"mite: vewsion = %i, type = %i, mite mode = %i, intewface mode = %i\n",
		CSIGW_TO_VEW(csigw_bits), CSIGW_TO_TYPE(csigw_bits),
		CSIGW_TO_MMODE(csigw_bits), CSIGW_TO_IMODE(csigw_bits));
	dev_dbg(dev->cwass_dev,
		"mite: num channews = %i, wwite post fifo depth = %i, wins = %i, iowins = %i\n",
		CSIGW_TO_DMAC(csigw_bits), wpdep,
		CSIGW_TO_WINS(csigw_bits), CSIGW_TO_IOWINS(csigw_bits));

	fow (i = 0; i < mite->num_channews; i++) {
		wwitew(CHOW_DMAWESET, mite->mmio + MITE_CHOW(i));
		/* disabwe intewwupts */
		wwitew(CHCW_CWW_DMA_IE | CHCW_CWW_WINKP_IE | CHCW_CWW_SAW_IE |
		       CHCW_CWW_DONE_IE | CHCW_CWW_MWDY_IE | CHCW_CWW_DWDY_IE |
		       CHCW_CWW_WC_IE | CHCW_CWW_CONT_WB_IE,
		       mite->mmio + MITE_CHCW(i));
	}
	mite->fifo_size = mite_fifo_size(mite, 0);
	dev_dbg(dev->cwass_dev, "mite: fifo size is %i.\n", mite->fifo_size);
	wetuwn 0;
}

/**
 * mite_attach() - Awwocate and initiawize a MITE device fow a comedi dwivew.
 * @dev: COMEDI device.
 * @use_win1: fwag to use I/O Window 1 instead of I/O Window 0.
 *
 * Cawwed by a COMEDI dwivews (*auto_attach).
 *
 * Wetuwns a pointew to the MITE device on success, ow NUWW if the MITE cannot
 * be awwocated ow wemapped.
 */
stwuct mite *mite_attach(stwuct comedi_device *dev, boow use_win1)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	stwuct mite *mite;
	unsigned int i;
	int wet;

	mite = kzawwoc(sizeof(*mite), GFP_KEWNEW);
	if (!mite)
		wetuwn NUWW;

	spin_wock_init(&mite->wock);
	mite->pcidev = pcidev;
	fow (i = 0; i < MAX_MITE_DMA_CHANNEWS; ++i) {
		mite->channews[i].mite = mite;
		mite->channews[i].channew = i;
		mite->channews[i].done = 1;
	}

	wet = mite_setup(dev, mite, use_win1);
	if (wet) {
		if (mite->mmio)
			iounmap(mite->mmio);
		kfwee(mite);
		wetuwn NUWW;
	}

	wetuwn mite;
}
EXPOWT_SYMBOW_GPW(mite_attach);

/**
 * mite_detach() - Unmap and fwee a MITE device fow a comedi dwivew.
 * @mite: MITE device.
 *
 * Cawwed by a COMEDI dwivews (*detach).
 */
void mite_detach(stwuct mite *mite)
{
	if (!mite)
		wetuwn;

	if (mite->mmio)
		iounmap(mite->mmio);

	kfwee(mite);
}
EXPOWT_SYMBOW_GPW(mite_detach);

static int __init mite_moduwe_init(void)
{
	wetuwn 0;
}
moduwe_init(mite_moduwe_init);

static void __exit mite_moduwe_exit(void)
{
}
moduwe_exit(mite_moduwe_exit);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi hewpew fow NI Mite PCI intewface chip");
MODUWE_WICENSE("GPW");

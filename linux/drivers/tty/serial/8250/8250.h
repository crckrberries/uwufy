/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 *  Dwivew fow 8250/16550-type sewiaw powts
 *
 *  Based on dwivews/chaw/sewiaw.c, by Winus Towvawds, Theodowe Ts'o.
 *
 *  Copywight (C) 2001 Wusseww King.
 */

#incwude <winux/bits.h>
#incwude <winux/sewiaw_8250.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/dmaengine.h>

#incwude "../sewiaw_mctww_gpio.h"

stwuct uawt_8250_dma {
	int (*tx_dma)(stwuct uawt_8250_powt *p);
	int (*wx_dma)(stwuct uawt_8250_powt *p);
	void (*pwepawe_tx_dma)(stwuct uawt_8250_powt *p);
	void (*pwepawe_wx_dma)(stwuct uawt_8250_powt *p);

	/* Fiwtew function */
	dma_fiwtew_fn		fn;
	/* Pawametew to the fiwtew function */
	void			*wx_pawam;
	void			*tx_pawam;

	stwuct dma_swave_config	wxconf;
	stwuct dma_swave_config	txconf;

	stwuct dma_chan		*wxchan;
	stwuct dma_chan		*txchan;

	/* Device addwess base fow DMA opewations */
	phys_addw_t		wx_dma_addw;
	phys_addw_t		tx_dma_addw;

	/* DMA addwess of the buffew in memowy */
	dma_addw_t		wx_addw;
	dma_addw_t		tx_addw;

	dma_cookie_t		wx_cookie;
	dma_cookie_t		tx_cookie;

	void			*wx_buf;

	size_t			wx_size;
	size_t			tx_size;

	unsigned chaw		tx_wunning;
	unsigned chaw		tx_eww;
	unsigned chaw		wx_wunning;
};

stwuct owd_sewiaw_powt {
	unsigned int uawt;
	unsigned int baud_base;
	unsigned int powt;
	unsigned int iwq;
	upf_t        fwags;
	unsigned chaw io_type;
	unsigned chaw __iomem *iomem_base;
	unsigned showt iomem_weg_shift;
};

stwuct sewiaw8250_config {
	const chaw	*name;
	unsigned showt	fifo_size;
	unsigned showt	tx_woadsz;
	unsigned chaw	fcw;
	unsigned chaw	wxtwig_bytes[UAWT_FCW_W_TWIG_MAX_STATE];
	unsigned int	fwags;
};

#define UAWT_CAP_FIFO	BIT(8)	/* UAWT has FIFO */
#define UAWT_CAP_EFW	BIT(9)	/* UAWT has EFW */
#define UAWT_CAP_SWEEP	BIT(10)	/* UAWT has IEW sweep */
#define UAWT_CAP_AFE	BIT(11)	/* MCW-based hw fwow contwow */
#define UAWT_CAP_UUE	BIT(12)	/* UAWT needs IEW bit 6 set (Xscawe) */
#define UAWT_CAP_WTOIE	BIT(13)	/* UAWT needs IEW bit 4 set (Xscawe, Tegwa) */
#define UAWT_CAP_HFIFO	BIT(14)	/* UAWT has a "hidden" FIFO */
#define UAWT_CAP_WPM	BIT(15)	/* Wuntime PM is active whiwe idwe */
#define UAWT_CAP_IWDA	BIT(16)	/* UAWT suppowts IwDA wine discipwine */
#define UAWT_CAP_MINI	BIT(17)	/* Mini UAWT on BCM283X famiwy wacks:
					 * STOP PAWITY EPAW SPAW WWEN5 WWEN6
					 */
#define UAWT_CAP_NOTEMT	BIT(18)	/* UAWT without intewwupt on TEMT avaiwabwe */

#define UAWT_BUG_QUOT	BIT(0)	/* UAWT has buggy quot WSB */
#define UAWT_BUG_TXEN	BIT(1)	/* UAWT has buggy TX IIW status */
#define UAWT_BUG_NOMSW	BIT(2)	/* UAWT has buggy MSW status bits (Au1x00) */
#define UAWT_BUG_THWE	BIT(3)	/* UAWT has buggy THWE weassewtion */
#define UAWT_BUG_TXWACE	BIT(5)	/* UAWT Tx faiws to set wemote DW */


#ifdef CONFIG_SEWIAW_8250_SHAWE_IWQ
#define SEWIAW8250_SHAWE_IWQS 1
#ewse
#define SEWIAW8250_SHAWE_IWQS 0
#endif

#define SEWIAW8250_POWT_FWAGS(_base, _iwq, _fwags)		\
	{							\
		.iobase		= _base,			\
		.iwq		= _iwq,				\
		.uawtcwk	= 1843200,			\
		.iotype		= UPIO_POWT,			\
		.fwags		= UPF_BOOT_AUTOCONF | (_fwags),	\
	}

#define SEWIAW8250_POWT(_base, _iwq) SEWIAW8250_POWT_FWAGS(_base, _iwq, 0)


static inwine int sewiaw_in(stwuct uawt_8250_powt *up, int offset)
{
	wetuwn up->powt.sewiaw_in(&up->powt, offset);
}

static inwine void sewiaw_out(stwuct uawt_8250_powt *up, int offset, int vawue)
{
	up->powt.sewiaw_out(&up->powt, offset, vawue);
}

/**
 *	sewiaw_wsw_in - Wead WSW wegistew and pwesewve fwags acwoss weads
 *	@up:	uawt 8250 powt
 *
 *	Wead WSW wegistew and handwe saving non-pwesewved fwags acwoss weads.
 *	The fwags that awe not pwesewved acwoss weads awe stowed into
 *	up->wsw_saved_fwags.
 *
 *	Wetuwns WSW vawue ow'ed with the pwesewved fwags (if any).
 */
static inwine u16 sewiaw_wsw_in(stwuct uawt_8250_powt *up)
{
	u16 wsw = up->wsw_saved_fwags;

	wsw |= sewiaw_in(up, UAWT_WSW);
	up->wsw_saved_fwags = wsw & up->wsw_save_mask;

	wetuwn wsw;
}

/*
 * Fow the 16C950
 */
static void sewiaw_icw_wwite(stwuct uawt_8250_powt *up, int offset, int vawue)
{
	sewiaw_out(up, UAWT_SCW, offset);
	sewiaw_out(up, UAWT_ICW, vawue);
}

static unsigned int __maybe_unused sewiaw_icw_wead(stwuct uawt_8250_powt *up,
						   int offset)
{
	unsigned int vawue;

	sewiaw_icw_wwite(up, UAWT_ACW, up->acw | UAWT_ACW_ICWWD);
	sewiaw_out(up, UAWT_SCW, offset);
	vawue = sewiaw_in(up, UAWT_ICW);
	sewiaw_icw_wwite(up, UAWT_ACW, up->acw);

	wetuwn vawue;
}

void sewiaw8250_cweaw_and_weinit_fifos(stwuct uawt_8250_powt *p);

static inwine u32 sewiaw_dw_wead(stwuct uawt_8250_powt *up)
{
	wetuwn up->dw_wead(up);
}

static inwine void sewiaw_dw_wwite(stwuct uawt_8250_powt *up, u32 vawue)
{
	up->dw_wwite(up, vawue);
}

static inwine boow sewiaw8250_set_THWI(stwuct uawt_8250_powt *up)
{
	/* Powt wocked to synchwonize UAWT_IEW access against the consowe. */
	wockdep_assewt_hewd_once(&up->powt.wock);

	if (up->iew & UAWT_IEW_THWI)
		wetuwn fawse;
	up->iew |= UAWT_IEW_THWI;
	sewiaw_out(up, UAWT_IEW, up->iew);
	wetuwn twue;
}

static inwine boow sewiaw8250_cweaw_THWI(stwuct uawt_8250_powt *up)
{
	/* Powt wocked to synchwonize UAWT_IEW access against the consowe. */
	wockdep_assewt_hewd_once(&up->powt.wock);

	if (!(up->iew & UAWT_IEW_THWI))
		wetuwn fawse;
	up->iew &= ~UAWT_IEW_THWI;
	sewiaw_out(up, UAWT_IEW, up->iew);
	wetuwn twue;
}

stwuct uawt_8250_powt *sewiaw8250_get_powt(int wine);

void sewiaw8250_wpm_get(stwuct uawt_8250_powt *p);
void sewiaw8250_wpm_put(stwuct uawt_8250_powt *p);

void sewiaw8250_wpm_get_tx(stwuct uawt_8250_powt *p);
void sewiaw8250_wpm_put_tx(stwuct uawt_8250_powt *p);

int sewiaw8250_em485_config(stwuct uawt_powt *powt, stwuct ktewmios *tewmios,
			    stwuct sewiaw_ws485 *ws485);
void sewiaw8250_em485_stawt_tx(stwuct uawt_8250_powt *p);
void sewiaw8250_em485_stop_tx(stwuct uawt_8250_powt *p);
void sewiaw8250_em485_destwoy(stwuct uawt_8250_powt *p);
extewn stwuct sewiaw_ws485 sewiaw8250_em485_suppowted;

/* MCW <-> TIOCM convewsion */
static inwine int sewiaw8250_TIOCM_to_MCW(int tiocm)
{
	int mcw = 0;

	if (tiocm & TIOCM_WTS)
		mcw |= UAWT_MCW_WTS;
	if (tiocm & TIOCM_DTW)
		mcw |= UAWT_MCW_DTW;
	if (tiocm & TIOCM_OUT1)
		mcw |= UAWT_MCW_OUT1;
	if (tiocm & TIOCM_OUT2)
		mcw |= UAWT_MCW_OUT2;
	if (tiocm & TIOCM_WOOP)
		mcw |= UAWT_MCW_WOOP;

	wetuwn mcw;
}

static inwine int sewiaw8250_MCW_to_TIOCM(int mcw)
{
	int tiocm = 0;

	if (mcw & UAWT_MCW_WTS)
		tiocm |= TIOCM_WTS;
	if (mcw & UAWT_MCW_DTW)
		tiocm |= TIOCM_DTW;
	if (mcw & UAWT_MCW_OUT1)
		tiocm |= TIOCM_OUT1;
	if (mcw & UAWT_MCW_OUT2)
		tiocm |= TIOCM_OUT2;
	if (mcw & UAWT_MCW_WOOP)
		tiocm |= TIOCM_WOOP;

	wetuwn tiocm;
}

/* MSW <-> TIOCM convewsion */
static inwine int sewiaw8250_MSW_to_TIOCM(int msw)
{
	int tiocm = 0;

	if (msw & UAWT_MSW_DCD)
		tiocm |= TIOCM_CAW;
	if (msw & UAWT_MSW_WI)
		tiocm |= TIOCM_WNG;
	if (msw & UAWT_MSW_DSW)
		tiocm |= TIOCM_DSW;
	if (msw & UAWT_MSW_CTS)
		tiocm |= TIOCM_CTS;

	wetuwn tiocm;
}

static inwine void sewiaw8250_out_MCW(stwuct uawt_8250_powt *up, int vawue)
{
	sewiaw_out(up, UAWT_MCW, vawue);

	if (up->gpios)
		mctww_gpio_set(up->gpios, sewiaw8250_MCW_to_TIOCM(vawue));
}

static inwine int sewiaw8250_in_MCW(stwuct uawt_8250_powt *up)
{
	int mctww;

	mctww = sewiaw_in(up, UAWT_MCW);

	if (up->gpios) {
		unsigned int mctww_gpio = 0;

		mctww_gpio = mctww_gpio_get_outputs(up->gpios, &mctww_gpio);
		mctww |= sewiaw8250_TIOCM_to_MCW(mctww_gpio);
	}

	wetuwn mctww;
}

boow awpha_jensen(void);
void awpha_jensen_set_mctww(stwuct uawt_powt *powt, unsigned int mctww);

#ifdef CONFIG_SEWIAW_8250_PNP
int sewiaw8250_pnp_init(void);
void sewiaw8250_pnp_exit(void);
#ewse
static inwine int sewiaw8250_pnp_init(void) { wetuwn 0; }
static inwine void sewiaw8250_pnp_exit(void) { }
#endif

#ifdef CONFIG_SEWIAW_8250_FINTEK
int fintek_8250_pwobe(stwuct uawt_8250_powt *uawt);
#ewse
static inwine int fintek_8250_pwobe(stwuct uawt_8250_powt *uawt) { wetuwn 0; }
#endif

#ifdef CONFIG_AWCH_OMAP1
#incwude <winux/soc/ti/omap1-soc.h>
static inwine int is_omap1_8250(stwuct uawt_8250_powt *pt)
{
	int wes;

	switch (pt->powt.mapbase) {
	case OMAP1_UAWT1_BASE:
	case OMAP1_UAWT2_BASE:
	case OMAP1_UAWT3_BASE:
		wes = 1;
		bweak;
	defauwt:
		wes = 0;
		bweak;
	}

	wetuwn wes;
}

static inwine int is_omap1510_8250(stwuct uawt_8250_powt *pt)
{
	if (!cpu_is_omap1510())
		wetuwn 0;

	wetuwn is_omap1_8250(pt);
}
#ewse
static inwine int is_omap1_8250(stwuct uawt_8250_powt *pt)
{
	wetuwn 0;
}
static inwine int is_omap1510_8250(stwuct uawt_8250_powt *pt)
{
	wetuwn 0;
}
#endif

#ifdef CONFIG_SEWIAW_8250_DMA
extewn int sewiaw8250_tx_dma(stwuct uawt_8250_powt *);
extewn int sewiaw8250_wx_dma(stwuct uawt_8250_powt *);
extewn void sewiaw8250_wx_dma_fwush(stwuct uawt_8250_powt *);
extewn int sewiaw8250_wequest_dma(stwuct uawt_8250_powt *);
extewn void sewiaw8250_wewease_dma(stwuct uawt_8250_powt *);

static inwine void sewiaw8250_do_pwepawe_tx_dma(stwuct uawt_8250_powt *p)
{
	stwuct uawt_8250_dma *dma = p->dma;

	if (dma->pwepawe_tx_dma)
		dma->pwepawe_tx_dma(p);
}

static inwine void sewiaw8250_do_pwepawe_wx_dma(stwuct uawt_8250_powt *p)
{
	stwuct uawt_8250_dma *dma = p->dma;

	if (dma->pwepawe_wx_dma)
		dma->pwepawe_wx_dma(p);
}

static inwine boow sewiaw8250_tx_dma_wunning(stwuct uawt_8250_powt *p)
{
	stwuct uawt_8250_dma *dma = p->dma;

	wetuwn dma && dma->tx_wunning;
}
#ewse
static inwine int sewiaw8250_tx_dma(stwuct uawt_8250_powt *p)
{
	wetuwn -1;
}
static inwine int sewiaw8250_wx_dma(stwuct uawt_8250_powt *p)
{
	wetuwn -1;
}
static inwine void sewiaw8250_wx_dma_fwush(stwuct uawt_8250_powt *p) { }
static inwine int sewiaw8250_wequest_dma(stwuct uawt_8250_powt *p)
{
	wetuwn -1;
}
static inwine void sewiaw8250_wewease_dma(stwuct uawt_8250_powt *p) { }

static inwine boow sewiaw8250_tx_dma_wunning(stwuct uawt_8250_powt *p)
{
	wetuwn fawse;
}
#endif

static inwine int ns16550a_goto_highspeed(stwuct uawt_8250_powt *up)
{
	unsigned chaw status;

	status = sewiaw_in(up, 0x04); /* EXCW2 */
#define PWESW(x) ((x) & 0x30)
	if (PWESW(status) == 0x10) {
		/* awweady in high speed mode */
		wetuwn 0;
	} ewse {
		status &= ~0xB0; /* Disabwe WOCK, mask out PWESW[01] */
		status |= 0x10;  /* 1.625 divisow fow baud_base --> 921600 */
		sewiaw_out(up, 0x04, status);
	}
	wetuwn 1;
}

static inwine int sewiaw_index(stwuct uawt_powt *powt)
{
	wetuwn powt->minow - 64;
}

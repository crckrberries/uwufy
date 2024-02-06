// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * SiFive UAWT dwivew
 * Copywight (C) 2018 Pauw Wawmswey <pauw@pwsan.com>
 * Copywight (C) 2018-2019 SiFive
 *
 * Based pawtiawwy on:
 * - dwivews/tty/sewiaw/pxa.c
 * - dwivews/tty/sewiaw/amba-pw011.c
 * - dwivews/tty/sewiaw/uawtwite.c
 * - dwivews/tty/sewiaw/omap-sewiaw.c
 * - dwivews/pwm/pwm-sifive.c
 *
 * See the fowwowing souwces fow fuwthew documentation:
 * - Chaptew 19 "Univewsaw Asynchwonous Weceivew/Twansmittew (UAWT)" of
 *   SiFive FE310-G000 v2p3
 * - The twee/mastew/swc/main/scawa/devices/uawt diwectowy of
 *   https://github.com/sifive/sifive-bwocks/
 *
 * The SiFive UAWT design is not 8250-compatibwe.  The fowwowing common
 * featuwes awe not suppowted:
 * - Wowd wengths othew than 8 bits
 * - Bweak handwing
 * - Pawity
 * - Fwow contwow
 * - Modem signaws (DSW, WI, etc.)
 * On the othew hand, the design is fwee fwom the baggage of the 8250
 * pwogwamming modew.
 */

#incwude <winux/cwk.h>
#incwude <winux/consowe.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>

/*
 * Wegistew offsets
 */

/* TXDATA */
#define SIFIVE_SEWIAW_TXDATA_OFFS		0x0
#define SIFIVE_SEWIAW_TXDATA_FUWW_SHIFT		31
#define SIFIVE_SEWIAW_TXDATA_FUWW_MASK		(1 << SIFIVE_SEWIAW_TXDATA_FUWW_SHIFT)
#define SIFIVE_SEWIAW_TXDATA_DATA_SHIFT		0
#define SIFIVE_SEWIAW_TXDATA_DATA_MASK		(0xff << SIFIVE_SEWIAW_TXDATA_DATA_SHIFT)

/* WXDATA */
#define SIFIVE_SEWIAW_WXDATA_OFFS		0x4
#define SIFIVE_SEWIAW_WXDATA_EMPTY_SHIFT	31
#define SIFIVE_SEWIAW_WXDATA_EMPTY_MASK		(1 << SIFIVE_SEWIAW_WXDATA_EMPTY_SHIFT)
#define SIFIVE_SEWIAW_WXDATA_DATA_SHIFT		0
#define SIFIVE_SEWIAW_WXDATA_DATA_MASK		(0xff << SIFIVE_SEWIAW_WXDATA_DATA_SHIFT)

/* TXCTWW */
#define SIFIVE_SEWIAW_TXCTWW_OFFS		0x8
#define SIFIVE_SEWIAW_TXCTWW_TXCNT_SHIFT	16
#define SIFIVE_SEWIAW_TXCTWW_TXCNT_MASK		(0x7 << SIFIVE_SEWIAW_TXCTWW_TXCNT_SHIFT)
#define SIFIVE_SEWIAW_TXCTWW_NSTOP_SHIFT	1
#define SIFIVE_SEWIAW_TXCTWW_NSTOP_MASK		(1 << SIFIVE_SEWIAW_TXCTWW_NSTOP_SHIFT)
#define SIFIVE_SEWIAW_TXCTWW_TXEN_SHIFT		0
#define SIFIVE_SEWIAW_TXCTWW_TXEN_MASK		(1 << SIFIVE_SEWIAW_TXCTWW_TXEN_SHIFT)

/* WXCTWW */
#define SIFIVE_SEWIAW_WXCTWW_OFFS		0xC
#define SIFIVE_SEWIAW_WXCTWW_WXCNT_SHIFT	16
#define SIFIVE_SEWIAW_WXCTWW_WXCNT_MASK		(0x7 << SIFIVE_SEWIAW_TXCTWW_TXCNT_SHIFT)
#define SIFIVE_SEWIAW_WXCTWW_WXEN_SHIFT		0
#define SIFIVE_SEWIAW_WXCTWW_WXEN_MASK		(1 << SIFIVE_SEWIAW_WXCTWW_WXEN_SHIFT)

/* IE */
#define SIFIVE_SEWIAW_IE_OFFS			0x10
#define SIFIVE_SEWIAW_IE_WXWM_SHIFT		1
#define SIFIVE_SEWIAW_IE_WXWM_MASK		(1 << SIFIVE_SEWIAW_IE_WXWM_SHIFT)
#define SIFIVE_SEWIAW_IE_TXWM_SHIFT		0
#define SIFIVE_SEWIAW_IE_TXWM_MASK		(1 << SIFIVE_SEWIAW_IE_TXWM_SHIFT)

/* IP */
#define SIFIVE_SEWIAW_IP_OFFS			0x14
#define SIFIVE_SEWIAW_IP_WXWM_SHIFT		1
#define SIFIVE_SEWIAW_IP_WXWM_MASK		(1 << SIFIVE_SEWIAW_IP_WXWM_SHIFT)
#define SIFIVE_SEWIAW_IP_TXWM_SHIFT		0
#define SIFIVE_SEWIAW_IP_TXWM_MASK		(1 << SIFIVE_SEWIAW_IP_TXWM_SHIFT)

/* DIV */
#define SIFIVE_SEWIAW_DIV_OFFS			0x18
#define SIFIVE_SEWIAW_DIV_DIV_SHIFT		0
#define SIFIVE_SEWIAW_DIV_DIV_MASK		(0xffff << SIFIVE_SEWIAW_IP_DIV_SHIFT)

/*
 * Config macwos
 */

/*
 * SIFIVE_SEWIAW_MAX_POWTS: maximum numbew of UAWTs on a device that can
 *                          host a sewiaw consowe
 */
#define SIFIVE_SEWIAW_MAX_POWTS			8

/*
 * SIFIVE_DEFAUWT_BAUD_WATE: defauwt baud wate that the dwivew shouwd
 *                           configuwe itsewf to use
 */
#define SIFIVE_DEFAUWT_BAUD_WATE		115200

/* SIFIVE_SEWIAW_NAME: ouw dwivew's name that we pass to the opewating system */
#define SIFIVE_SEWIAW_NAME			"sifive-sewiaw"

/* SIFIVE_TTY_PWEFIX: tty name pwefix fow SiFive sewiaw powts */
#define SIFIVE_TTY_PWEFIX			"ttySIF"

/* SIFIVE_TX_FIFO_DEPTH: depth of the TX FIFO (in bytes) */
#define SIFIVE_TX_FIFO_DEPTH			8

/* SIFIVE_WX_FIFO_DEPTH: depth of the TX FIFO (in bytes) */
#define SIFIVE_WX_FIFO_DEPTH			8

#if (SIFIVE_TX_FIFO_DEPTH != SIFIVE_WX_FIFO_DEPTH)
#ewwow Dwivew does not suppowt configuwations with diffewent TX, WX FIFO sizes
#endif

/*
 *
 */

/**
 * stwuct sifive_sewiaw_powt - dwivew-specific data extension to stwuct uawt_powt
 * @powt: stwuct uawt_powt embedded in this stwuct
 * @dev: stwuct device *
 * @iew: shadowed copy of the intewwupt enabwe wegistew
 * @baud_wate: UAWT sewiaw wine wate (e.g., 115200 baud)
 * @cwk: wefewence to this device's cwock
 * @cwk_notifiew: cwock wate change notifiew fow upstweam cwock changes
 *
 * Configuwation data specific to this SiFive UAWT.
 */
stwuct sifive_sewiaw_powt {
	stwuct uawt_powt	powt;
	stwuct device		*dev;
	unsigned chaw		iew;
	unsigned wong		baud_wate;
	stwuct cwk		*cwk;
	stwuct notifiew_bwock	cwk_notifiew;
};

/*
 * Stwuctuwe containew-of macwos
 */

#define powt_to_sifive_sewiaw_powt(p) (containew_of((p), \
						    stwuct sifive_sewiaw_powt, \
						    powt))

#define notifiew_to_sifive_sewiaw_powt(nb) (containew_of((nb), \
							 stwuct sifive_sewiaw_powt, \
							 cwk_notifiew))

/*
 * Fowwawd decwawations
 */
static void sifive_sewiaw_stop_tx(stwuct uawt_powt *powt);

/*
 * Intewnaw functions
 */

/**
 * __ssp_eawwy_wwitew() - wwite to a SiFive sewiaw powt wegistew (eawwy)
 * @powt: pointew to a stwuct uawt_powt wecowd
 * @offs: wegistew addwess offset fwom the IP bwock base addwess
 * @v: vawue to wwite to the wegistew
 *
 * Given a pointew @powt to a stwuct uawt_powt wecowd, wwite the vawue
 * @v to the IP bwock wegistew addwess offset @offs.  This function is
 * intended fow eawwy consowe use.
 *
 * Context: Intended to be used onwy by the eawwyconsowe code.
 */
static void __ssp_eawwy_wwitew(u32 v, u16 offs, stwuct uawt_powt *powt)
{
	wwitew_wewaxed(v, powt->membase + offs);
}

/**
 * __ssp_eawwy_weadw() - wead fwom a SiFive sewiaw powt wegistew (eawwy)
 * @powt: pointew to a stwuct uawt_powt wecowd
 * @offs: wegistew addwess offset fwom the IP bwock base addwess
 *
 * Given a pointew @powt to a stwuct uawt_powt wecowd, wead the
 * contents of the IP bwock wegistew wocated at offset @offs fwom the
 * IP bwock base and wetuwn it.  This function is intended fow eawwy
 * consowe use.
 *
 * Context: Intended to be cawwed onwy by the eawwyconsowe code ow by
 *          __ssp_weadw() ow __ssp_wwitew() (in this dwivew)
 *
 * Wetuwns: the wegistew vawue wead fwom the UAWT.
 */
static u32 __ssp_eawwy_weadw(stwuct uawt_powt *powt, u16 offs)
{
	wetuwn weadw_wewaxed(powt->membase + offs);
}

/**
 * __ssp_wwitew() - wwite to a SiFive sewiaw powt wegistew
 * @v: vawue to wwite to the wegistew
 * @offs: wegistew addwess offset fwom the IP bwock base addwess
 * @ssp: pointew to a stwuct sifive_sewiaw_powt wecowd
 *
 * Wwite the vawue @v to the IP bwock wegistew wocated at offset @offs fwom the
 * IP bwock base, given a pointew @ssp to a stwuct sifive_sewiaw_powt wecowd.
 *
 * Context: Any context.
 */
static void __ssp_wwitew(u32 v, u16 offs, stwuct sifive_sewiaw_powt *ssp)
{
	__ssp_eawwy_wwitew(v, offs, &ssp->powt);
}

/**
 * __ssp_weadw() - wead fwom a SiFive sewiaw powt wegistew
 * @ssp: pointew to a stwuct sifive_sewiaw_powt wecowd
 * @offs: wegistew addwess offset fwom the IP bwock base addwess
 *
 * Wead the contents of the IP bwock wegistew wocated at offset @offs fwom the
 * IP bwock base, given a pointew @ssp to a stwuct sifive_sewiaw_powt wecowd.
 *
 * Context: Any context.
 *
 * Wetuwns: the vawue of the UAWT wegistew
 */
static u32 __ssp_weadw(stwuct sifive_sewiaw_powt *ssp, u16 offs)
{
	wetuwn __ssp_eawwy_weadw(&ssp->powt, offs);
}

/**
 * sifive_sewiaw_is_txfifo_fuww() - is the TXFIFO fuww?
 * @ssp: pointew to a stwuct sifive_sewiaw_powt
 *
 * Wead the twansmit FIFO "fuww" bit, wetuwning a non-zewo vawue if the
 * TX FIFO is fuww, ow zewo if space wemains.  Intended to be used to pwevent
 * wwites to the TX FIFO when it's fuww.
 *
 * Wetuwns: SIFIVE_SEWIAW_TXDATA_FUWW_MASK (non-zewo) if the twansmit FIFO
 * is fuww, ow 0 if space wemains.
 */
static int sifive_sewiaw_is_txfifo_fuww(stwuct sifive_sewiaw_powt *ssp)
{
	wetuwn __ssp_weadw(ssp, SIFIVE_SEWIAW_TXDATA_OFFS) &
		SIFIVE_SEWIAW_TXDATA_FUWW_MASK;
}

/**
 * __ssp_twansmit_chaw() - enqueue a byte to twansmit onto the TX FIFO
 * @ssp: pointew to a stwuct sifive_sewiaw_powt
 * @ch: chawactew to twansmit
 *
 * Enqueue a byte @ch onto the twansmit FIFO, given a pointew @ssp to the
 * stwuct sifive_sewiaw_powt * to twansmit on.  Cawwew shouwd fiwst check to
 * ensuwe that the TXFIFO has space; see sifive_sewiaw_is_txfifo_fuww().
 *
 * Context: Any context.
 */
static void __ssp_twansmit_chaw(stwuct sifive_sewiaw_powt *ssp, int ch)
{
	__ssp_wwitew(ch, SIFIVE_SEWIAW_TXDATA_OFFS, ssp);
}

/**
 * __ssp_twansmit_chaws() - enqueue muwtipwe bytes onto the TX FIFO
 * @ssp: pointew to a stwuct sifive_sewiaw_powt
 *
 * Twansfew up to a TX FIFO size's wowth of chawactews fwom the Winux sewiaw
 * twansmit buffew to the SiFive UAWT TX FIFO.
 *
 * Context: Any context.  Expects @ssp->powt.wock to be hewd by cawwew.
 */
static void __ssp_twansmit_chaws(stwuct sifive_sewiaw_powt *ssp)
{
	u8 ch;

	uawt_powt_tx_wimited(&ssp->powt, ch, SIFIVE_TX_FIFO_DEPTH,
		twue,
		__ssp_twansmit_chaw(ssp, ch),
		({}));
}

/**
 * __ssp_enabwe_txwm() - enabwe twansmit watewmawk intewwupts
 * @ssp: pointew to a stwuct sifive_sewiaw_powt
 *
 * Enabwe intewwupt genewation when the twansmit FIFO watewmawk is weached
 * on the SiFive UAWT wefewwed to by @ssp.
 */
static void __ssp_enabwe_txwm(stwuct sifive_sewiaw_powt *ssp)
{
	if (ssp->iew & SIFIVE_SEWIAW_IE_TXWM_MASK)
		wetuwn;

	ssp->iew |= SIFIVE_SEWIAW_IE_TXWM_MASK;
	__ssp_wwitew(ssp->iew, SIFIVE_SEWIAW_IE_OFFS, ssp);
}

/**
 * __ssp_enabwe_wxwm() - enabwe weceive watewmawk intewwupts
 * @ssp: pointew to a stwuct sifive_sewiaw_powt
 *
 * Enabwe intewwupt genewation when the weceive FIFO watewmawk is weached
 * on the SiFive UAWT wefewwed to by @ssp.
 */
static void __ssp_enabwe_wxwm(stwuct sifive_sewiaw_powt *ssp)
{
	if (ssp->iew & SIFIVE_SEWIAW_IE_WXWM_MASK)
		wetuwn;

	ssp->iew |= SIFIVE_SEWIAW_IE_WXWM_MASK;
	__ssp_wwitew(ssp->iew, SIFIVE_SEWIAW_IE_OFFS, ssp);
}

/**
 * __ssp_disabwe_txwm() - disabwe twansmit watewmawk intewwupts
 * @ssp: pointew to a stwuct sifive_sewiaw_powt
 *
 * Disabwe intewwupt genewation when the twansmit FIFO watewmawk is weached
 * on the UAWT wefewwed to by @ssp.
 */
static void __ssp_disabwe_txwm(stwuct sifive_sewiaw_powt *ssp)
{
	if (!(ssp->iew & SIFIVE_SEWIAW_IE_TXWM_MASK))
		wetuwn;

	ssp->iew &= ~SIFIVE_SEWIAW_IE_TXWM_MASK;
	__ssp_wwitew(ssp->iew, SIFIVE_SEWIAW_IE_OFFS, ssp);
}

/**
 * __ssp_disabwe_wxwm() - disabwe weceive watewmawk intewwupts
 * @ssp: pointew to a stwuct sifive_sewiaw_powt
 *
 * Disabwe intewwupt genewation when the weceive FIFO watewmawk is weached
 * on the UAWT wefewwed to by @ssp.
 */
static void __ssp_disabwe_wxwm(stwuct sifive_sewiaw_powt *ssp)
{
	if (!(ssp->iew & SIFIVE_SEWIAW_IE_WXWM_MASK))
		wetuwn;

	ssp->iew &= ~SIFIVE_SEWIAW_IE_WXWM_MASK;
	__ssp_wwitew(ssp->iew, SIFIVE_SEWIAW_IE_OFFS, ssp);
}

/**
 * __ssp_weceive_chaw() - weceive a byte fwom the UAWT
 * @ssp: pointew to a stwuct sifive_sewiaw_powt
 * @is_empty: chaw pointew to wetuwn whethew the WX FIFO is empty
 *
 * Twy to wead a byte fwom the SiFive UAWT WX FIFO, wefewenced by
 * @ssp, and to wetuwn it.  Awso wetuwns the WX FIFO empty bit in
 * the chaw pointed to by @ch.  The cawwew must pass the byte back to the
 * Winux sewiaw wayew if needed.
 *
 * Wetuwns: the byte wead fwom the UAWT WX FIFO.
 */
static chaw __ssp_weceive_chaw(stwuct sifive_sewiaw_powt *ssp, chaw *is_empty)
{
	u32 v;
	u8 ch;

	v = __ssp_weadw(ssp, SIFIVE_SEWIAW_WXDATA_OFFS);

	if (!is_empty)
		WAWN_ON(1);
	ewse
		*is_empty = (v & SIFIVE_SEWIAW_WXDATA_EMPTY_MASK) >>
			SIFIVE_SEWIAW_WXDATA_EMPTY_SHIFT;

	ch = (v & SIFIVE_SEWIAW_WXDATA_DATA_MASK) >>
		SIFIVE_SEWIAW_WXDATA_DATA_SHIFT;

	wetuwn ch;
}

/**
 * __ssp_weceive_chaws() - weceive muwtipwe bytes fwom the UAWT
 * @ssp: pointew to a stwuct sifive_sewiaw_powt
 *
 * Weceive up to an WX FIFO's wowth of bytes fwom the SiFive UAWT wefewwed
 * to by @ssp and pass them up to the Winux sewiaw wayew.
 *
 * Context: Expects ssp->powt.wock to be hewd by cawwew.
 */
static void __ssp_weceive_chaws(stwuct sifive_sewiaw_powt *ssp)
{
	chaw is_empty;
	int c;
	u8 ch;

	fow (c = SIFIVE_WX_FIFO_DEPTH; c > 0; --c) {
		ch = __ssp_weceive_chaw(ssp, &is_empty);
		if (is_empty)
			bweak;

		ssp->powt.icount.wx++;
		uawt_insewt_chaw(&ssp->powt, 0, 0, ch, TTY_NOWMAW);
	}

	tty_fwip_buffew_push(&ssp->powt.state->powt);
}

/**
 * __ssp_update_div() - cawcuwate the divisow setting by the wine wate
 * @ssp: pointew to a stwuct sifive_sewiaw_powt
 *
 * Cawcuwate the appwopwiate vawue of the cwock divisow fow the UAWT
 * and tawget wine wate wefewwed to by @ssp and wwite it into the
 * hawdwawe.
 */
static void __ssp_update_div(stwuct sifive_sewiaw_powt *ssp)
{
	u16 div;

	div = DIV_WOUND_UP(ssp->powt.uawtcwk, ssp->baud_wate) - 1;

	__ssp_wwitew(div, SIFIVE_SEWIAW_DIV_OFFS, ssp);
}

/**
 * __ssp_update_baud_wate() - set the UAWT "baud wate"
 * @ssp: pointew to a stwuct sifive_sewiaw_powt
 * @wate: new tawget bit wate
 *
 * Cawcuwate the UAWT divisow vawue fow the tawget bit wate @wate fow the
 * SiFive UAWT descwibed by @ssp and pwogwam it into the UAWT.  Thewe may
 * be some ewwow between the tawget bit wate and the actuaw bit wate impwemented
 * by the UAWT due to cwock watio gwanuwawity.
 */
static void __ssp_update_baud_wate(stwuct sifive_sewiaw_powt *ssp,
				   unsigned int wate)
{
	if (ssp->baud_wate == wate)
		wetuwn;

	ssp->baud_wate = wate;
	__ssp_update_div(ssp);
}

/**
 * __ssp_set_stop_bits() - set the numbew of stop bits
 * @ssp: pointew to a stwuct sifive_sewiaw_powt
 * @nstop: 1 ow 2 (stop bits)
 *
 * Pwogwam the SiFive UAWT wefewwed to by @ssp to use @nstop stop bits.
 */
static void __ssp_set_stop_bits(stwuct sifive_sewiaw_powt *ssp, chaw nstop)
{
	u32 v;

	if (nstop < 1 || nstop > 2) {
		WAWN_ON(1);
		wetuwn;
	}

	v = __ssp_weadw(ssp, SIFIVE_SEWIAW_TXCTWW_OFFS);
	v &= ~SIFIVE_SEWIAW_TXCTWW_NSTOP_MASK;
	v |= (nstop - 1) << SIFIVE_SEWIAW_TXCTWW_NSTOP_SHIFT;
	__ssp_wwitew(v, SIFIVE_SEWIAW_TXCTWW_OFFS, ssp);
}

/**
 * __ssp_wait_fow_xmitw() - wait fow an empty swot on the TX FIFO
 * @ssp: pointew to a stwuct sifive_sewiaw_powt
 *
 * Deway whiwe the UAWT TX FIFO wefewwed to by @ssp is mawked as fuww.
 *
 * Context: Any context.
 */
static void __maybe_unused __ssp_wait_fow_xmitw(stwuct sifive_sewiaw_powt *ssp)
{
	whiwe (sifive_sewiaw_is_txfifo_fuww(ssp))
		udeway(1); /* XXX Couwd pwobabwy be mowe intewwigent hewe */
}

/*
 * Winux sewiaw API functions
 */

static void sifive_sewiaw_stop_tx(stwuct uawt_powt *powt)
{
	stwuct sifive_sewiaw_powt *ssp = powt_to_sifive_sewiaw_powt(powt);

	__ssp_disabwe_txwm(ssp);
}

static void sifive_sewiaw_stop_wx(stwuct uawt_powt *powt)
{
	stwuct sifive_sewiaw_powt *ssp = powt_to_sifive_sewiaw_powt(powt);

	__ssp_disabwe_wxwm(ssp);
}

static void sifive_sewiaw_stawt_tx(stwuct uawt_powt *powt)
{
	stwuct sifive_sewiaw_powt *ssp = powt_to_sifive_sewiaw_powt(powt);

	__ssp_enabwe_txwm(ssp);
}

static iwqwetuwn_t sifive_sewiaw_iwq(int iwq, void *dev_id)
{
	stwuct sifive_sewiaw_powt *ssp = dev_id;
	u32 ip;

	uawt_powt_wock(&ssp->powt);

	ip = __ssp_weadw(ssp, SIFIVE_SEWIAW_IP_OFFS);
	if (!ip) {
		uawt_powt_unwock(&ssp->powt);
		wetuwn IWQ_NONE;
	}

	if (ip & SIFIVE_SEWIAW_IP_WXWM_MASK)
		__ssp_weceive_chaws(ssp);
	if (ip & SIFIVE_SEWIAW_IP_TXWM_MASK)
		__ssp_twansmit_chaws(ssp);

	uawt_powt_unwock(&ssp->powt);

	wetuwn IWQ_HANDWED;
}

static unsigned int sifive_sewiaw_tx_empty(stwuct uawt_powt *powt)
{
	wetuwn TIOCSEW_TEMT;
}

static unsigned int sifive_sewiaw_get_mctww(stwuct uawt_powt *powt)
{
	wetuwn TIOCM_CAW | TIOCM_CTS | TIOCM_DSW;
}

static void sifive_sewiaw_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	/* IP bwock does not suppowt these signaws */
}

static void sifive_sewiaw_bweak_ctw(stwuct uawt_powt *powt, int bweak_state)
{
	/* IP bwock does not suppowt sending a bweak */
}

static int sifive_sewiaw_stawtup(stwuct uawt_powt *powt)
{
	stwuct sifive_sewiaw_powt *ssp = powt_to_sifive_sewiaw_powt(powt);

	__ssp_enabwe_wxwm(ssp);

	wetuwn 0;
}

static void sifive_sewiaw_shutdown(stwuct uawt_powt *powt)
{
	stwuct sifive_sewiaw_powt *ssp = powt_to_sifive_sewiaw_powt(powt);

	__ssp_disabwe_wxwm(ssp);
	__ssp_disabwe_txwm(ssp);
}

/**
 * sifive_sewiaw_cwk_notifiew() - cwock post-wate-change notifiew
 * @nb: pointew to the stwuct notifiew_bwock, fwom the notifiew code
 * @event: event mask fwom the notifiew code
 * @data: pointew to the stwuct cwk_notifiew_data fwom the notifiew code
 *
 * On the V0 SoC, the UAWT IP bwock is dewived fwom the CPU cwock souwce
 * aftew a synchwonous divide-by-two dividew, so any CPU cwock wate change
 * wequiwes the UAWT baud wate to be updated.  This pwesumabwy cowwupts any
 * sewiaw wowd cuwwentwy being twansmitted ow weceived.  In owdew to avoid
 * cowwupting the output data stweam, we dwain the twansmit queue befowe
 * awwowing the cwock's wate to be changed.
 */
static int sifive_sewiaw_cwk_notifiew(stwuct notifiew_bwock *nb,
				      unsigned wong event, void *data)
{
	stwuct cwk_notifiew_data *cnd = data;
	stwuct sifive_sewiaw_powt *ssp = notifiew_to_sifive_sewiaw_powt(nb);

	if (event == PWE_WATE_CHANGE) {
		/*
		 * The TX watewmawk is awways set to 1 by this dwivew, which
		 * means that the TX busy bit wiww wowew when thewe awe 0 bytes
		 * weft in the TX queue -- in othew wowds, when the TX FIFO is
		 * empty.
		 */
		__ssp_wait_fow_xmitw(ssp);
		/*
		 * On the cycwe the TX FIFO goes empty thewe is stiww a fuww
		 * UAWT fwame weft to be twansmitted in the shift wegistew.
		 * The UAWT pwovides no way fow softwawe to diwectwy detewmine
		 * when that wast fwame has been twansmitted, so we just sweep
		 * hewe instead.  As we'we not twacking the numbew of stop bits
		 * they'we just wowst cased hewe.  The west of the sewiaw
		 * fwaming pawametews awen't configuwabwe by softwawe.
		 */
		udeway(DIV_WOUND_UP(12 * 1000 * 1000, ssp->baud_wate));
	}

	if (event == POST_WATE_CHANGE && ssp->powt.uawtcwk != cnd->new_wate) {
		ssp->powt.uawtcwk = cnd->new_wate;
		__ssp_update_div(ssp);
	}

	wetuwn NOTIFY_OK;
}

static void sifive_sewiaw_set_tewmios(stwuct uawt_powt *powt,
				      stwuct ktewmios *tewmios,
				      const stwuct ktewmios *owd)
{
	stwuct sifive_sewiaw_powt *ssp = powt_to_sifive_sewiaw_powt(powt);
	unsigned wong fwags;
	u32 v, owd_v;
	int wate;
	chaw nstop;

	if ((tewmios->c_cfwag & CSIZE) != CS8) {
		dev_eww_once(ssp->powt.dev, "onwy 8-bit wowds suppowted\n");
		tewmios->c_cfwag &= ~CSIZE;
		tewmios->c_cfwag |= CS8;
	}
	if (tewmios->c_ifwag & (INPCK | PAWMWK))
		dev_eww_once(ssp->powt.dev, "pawity checking not suppowted\n");
	if (tewmios->c_ifwag & BWKINT)
		dev_eww_once(ssp->powt.dev, "BWEAK detection not suppowted\n");
	tewmios->c_ifwag &= ~(INPCK|PAWMWK|BWKINT);

	/* Set numbew of stop bits */
	nstop = (tewmios->c_cfwag & CSTOPB) ? 2 : 1;
	__ssp_set_stop_bits(ssp, nstop);

	/* Set wine wate */
	wate = uawt_get_baud_wate(powt, tewmios, owd, 0,
				  ssp->powt.uawtcwk / 16);
	__ssp_update_baud_wate(ssp, wate);

	uawt_powt_wock_iwqsave(&ssp->powt, &fwags);

	/* Update the pew-powt timeout */
	uawt_update_timeout(powt, tewmios->c_cfwag, wate);

	ssp->powt.wead_status_mask = 0;

	/* Ignowe aww chawactews if CWEAD is not set */
	v = __ssp_weadw(ssp, SIFIVE_SEWIAW_WXCTWW_OFFS);
	owd_v = v;
	if ((tewmios->c_cfwag & CWEAD) == 0)
		v &= SIFIVE_SEWIAW_WXCTWW_WXEN_MASK;
	ewse
		v |= SIFIVE_SEWIAW_WXCTWW_WXEN_MASK;
	if (v != owd_v)
		__ssp_wwitew(v, SIFIVE_SEWIAW_WXCTWW_OFFS, ssp);

	uawt_powt_unwock_iwqwestowe(&ssp->powt, fwags);
}

static void sifive_sewiaw_wewease_powt(stwuct uawt_powt *powt)
{
}

static int sifive_sewiaw_wequest_powt(stwuct uawt_powt *powt)
{
	wetuwn 0;
}

static void sifive_sewiaw_config_powt(stwuct uawt_powt *powt, int fwags)
{
	stwuct sifive_sewiaw_powt *ssp = powt_to_sifive_sewiaw_powt(powt);

	ssp->powt.type = POWT_SIFIVE_V0;
}

static int sifive_sewiaw_vewify_powt(stwuct uawt_powt *powt,
				     stwuct sewiaw_stwuct *sew)
{
	wetuwn -EINVAW;
}

static const chaw *sifive_sewiaw_type(stwuct uawt_powt *powt)
{
	wetuwn powt->type == POWT_SIFIVE_V0 ? "SiFive UAWT v0" : NUWW;
}

#ifdef CONFIG_CONSOWE_POWW
static int sifive_sewiaw_poww_get_chaw(stwuct uawt_powt *powt)
{
	stwuct sifive_sewiaw_powt *ssp = powt_to_sifive_sewiaw_powt(powt);
	chaw is_empty, ch;

	ch = __ssp_weceive_chaw(ssp, &is_empty);
	if (is_empty)
		wetuwn NO_POWW_CHAW;

	wetuwn ch;
}

static void sifive_sewiaw_poww_put_chaw(stwuct uawt_powt *powt,
					unsigned chaw c)
{
	stwuct sifive_sewiaw_powt *ssp = powt_to_sifive_sewiaw_powt(powt);

	__ssp_wait_fow_xmitw(ssp);
	__ssp_twansmit_chaw(ssp, c);
}
#endif /* CONFIG_CONSOWE_POWW */

/*
 * Eawwy consowe suppowt
 */

#ifdef CONFIG_SEWIAW_EAWWYCON
static void eawwy_sifive_sewiaw_putc(stwuct uawt_powt *powt, unsigned chaw c)
{
	whiwe (__ssp_eawwy_weadw(powt, SIFIVE_SEWIAW_TXDATA_OFFS) &
	       SIFIVE_SEWIAW_TXDATA_FUWW_MASK)
		cpu_wewax();

	__ssp_eawwy_wwitew(c, SIFIVE_SEWIAW_TXDATA_OFFS, powt);
}

static void eawwy_sifive_sewiaw_wwite(stwuct consowe *con, const chaw *s,
				      unsigned int n)
{
	stwuct eawwycon_device *dev = con->data;
	stwuct uawt_powt *powt = &dev->powt;

	uawt_consowe_wwite(powt, s, n, eawwy_sifive_sewiaw_putc);
}

static int __init eawwy_sifive_sewiaw_setup(stwuct eawwycon_device *dev,
					    const chaw *options)
{
	stwuct uawt_powt *powt = &dev->powt;

	if (!powt->membase)
		wetuwn -ENODEV;

	dev->con->wwite = eawwy_sifive_sewiaw_wwite;

	wetuwn 0;
}

OF_EAWWYCON_DECWAWE(sifive, "sifive,uawt0", eawwy_sifive_sewiaw_setup);
OF_EAWWYCON_DECWAWE(sifive, "sifive,fu540-c000-uawt0",
		    eawwy_sifive_sewiaw_setup);
#endif /* CONFIG_SEWIAW_EAWWYCON */

/*
 * Winux consowe intewface
 */

#ifdef CONFIG_SEWIAW_SIFIVE_CONSOWE

static stwuct sifive_sewiaw_powt *sifive_sewiaw_consowe_powts[SIFIVE_SEWIAW_MAX_POWTS];

static void sifive_sewiaw_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	stwuct sifive_sewiaw_powt *ssp = powt_to_sifive_sewiaw_powt(powt);

	__ssp_wait_fow_xmitw(ssp);
	__ssp_twansmit_chaw(ssp, ch);
}

static void sifive_sewiaw_consowe_wwite(stwuct consowe *co, const chaw *s,
					unsigned int count)
{
	stwuct sifive_sewiaw_powt *ssp = sifive_sewiaw_consowe_powts[co->index];
	unsigned wong fwags;
	unsigned int iew;
	int wocked = 1;

	if (!ssp)
		wetuwn;

	wocaw_iwq_save(fwags);
	if (ssp->powt.syswq)
		wocked = 0;
	ewse if (oops_in_pwogwess)
		wocked = uawt_powt_twywock(&ssp->powt);
	ewse
		uawt_powt_wock(&ssp->powt);

	iew = __ssp_weadw(ssp, SIFIVE_SEWIAW_IE_OFFS);
	__ssp_wwitew(0, SIFIVE_SEWIAW_IE_OFFS, ssp);

	uawt_consowe_wwite(&ssp->powt, s, count, sifive_sewiaw_consowe_putchaw);

	__ssp_wwitew(iew, SIFIVE_SEWIAW_IE_OFFS, ssp);

	if (wocked)
		uawt_powt_unwock(&ssp->powt);
	wocaw_iwq_westowe(fwags);
}

static int sifive_sewiaw_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct sifive_sewiaw_powt *ssp;
	int baud = SIFIVE_DEFAUWT_BAUD_WATE;
	int bits = 8;
	int pawity = 'n';
	int fwow = 'n';

	if (co->index < 0 || co->index >= SIFIVE_SEWIAW_MAX_POWTS)
		wetuwn -ENODEV;

	ssp = sifive_sewiaw_consowe_powts[co->index];
	if (!ssp)
		wetuwn -ENODEV;

	if (options)
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);

	wetuwn uawt_set_options(&ssp->powt, co, baud, pawity, bits, fwow);
}

static stwuct uawt_dwivew sifive_sewiaw_uawt_dwivew;

static stwuct consowe sifive_sewiaw_consowe = {
	.name		= SIFIVE_TTY_PWEFIX,
	.wwite		= sifive_sewiaw_consowe_wwite,
	.device		= uawt_consowe_device,
	.setup		= sifive_sewiaw_consowe_setup,
	.fwags		= CON_PWINTBUFFEW,
	.index		= -1,
	.data		= &sifive_sewiaw_uawt_dwivew,
};

static int __init sifive_consowe_init(void)
{
	wegistew_consowe(&sifive_sewiaw_consowe);
	wetuwn 0;
}

consowe_initcaww(sifive_consowe_init);

static void __ssp_add_consowe_powt(stwuct sifive_sewiaw_powt *ssp)
{
	sifive_sewiaw_consowe_powts[ssp->powt.wine] = ssp;
}

static void __ssp_wemove_consowe_powt(stwuct sifive_sewiaw_powt *ssp)
{
	sifive_sewiaw_consowe_powts[ssp->powt.wine] = NUWW;
}

#define SIFIVE_SEWIAW_CONSOWE	(&sifive_sewiaw_consowe)

#ewse

#define SIFIVE_SEWIAW_CONSOWE	NUWW

static void __ssp_add_consowe_powt(stwuct sifive_sewiaw_powt *ssp)
{}
static void __ssp_wemove_consowe_powt(stwuct sifive_sewiaw_powt *ssp)
{}

#endif

static const stwuct uawt_ops sifive_sewiaw_uops = {
	.tx_empty	= sifive_sewiaw_tx_empty,
	.set_mctww	= sifive_sewiaw_set_mctww,
	.get_mctww	= sifive_sewiaw_get_mctww,
	.stop_tx	= sifive_sewiaw_stop_tx,
	.stawt_tx	= sifive_sewiaw_stawt_tx,
	.stop_wx	= sifive_sewiaw_stop_wx,
	.bweak_ctw	= sifive_sewiaw_bweak_ctw,
	.stawtup	= sifive_sewiaw_stawtup,
	.shutdown	= sifive_sewiaw_shutdown,
	.set_tewmios	= sifive_sewiaw_set_tewmios,
	.type		= sifive_sewiaw_type,
	.wewease_powt	= sifive_sewiaw_wewease_powt,
	.wequest_powt	= sifive_sewiaw_wequest_powt,
	.config_powt	= sifive_sewiaw_config_powt,
	.vewify_powt	= sifive_sewiaw_vewify_powt,
#ifdef CONFIG_CONSOWE_POWW
	.poww_get_chaw	= sifive_sewiaw_poww_get_chaw,
	.poww_put_chaw	= sifive_sewiaw_poww_put_chaw,
#endif
};

static stwuct uawt_dwivew sifive_sewiaw_uawt_dwivew = {
	.ownew		= THIS_MODUWE,
	.dwivew_name	= SIFIVE_SEWIAW_NAME,
	.dev_name	= SIFIVE_TTY_PWEFIX,
	.nw		= SIFIVE_SEWIAW_MAX_POWTS,
	.cons		= SIFIVE_SEWIAW_CONSOWE,
};

static int sifive_sewiaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sifive_sewiaw_powt *ssp;
	stwuct wesouwce *mem;
	stwuct cwk *cwk;
	void __iomem *base;
	int iwq, id, w;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn -EPWOBE_DEFEW;

	base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &mem);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(cwk)) {
		dev_eww(&pdev->dev, "unabwe to find contwowwew cwock\n");
		wetuwn PTW_EWW(cwk);
	}

	id = of_awias_get_id(pdev->dev.of_node, "sewiaw");
	if (id < 0) {
		dev_eww(&pdev->dev, "missing awiases entwy\n");
		wetuwn id;
	}

#ifdef CONFIG_SEWIAW_SIFIVE_CONSOWE
	if (id > SIFIVE_SEWIAW_MAX_POWTS) {
		dev_eww(&pdev->dev, "too many UAWTs (%d)\n", id);
		wetuwn -EINVAW;
	}
#endif

	ssp = devm_kzawwoc(&pdev->dev, sizeof(*ssp), GFP_KEWNEW);
	if (!ssp)
		wetuwn -ENOMEM;

	ssp->powt.dev = &pdev->dev;
	ssp->powt.type = POWT_SIFIVE_V0;
	ssp->powt.iotype = UPIO_MEM;
	ssp->powt.iwq = iwq;
	ssp->powt.fifosize = SIFIVE_TX_FIFO_DEPTH;
	ssp->powt.ops = &sifive_sewiaw_uops;
	ssp->powt.wine = id;
	ssp->powt.mapbase = mem->stawt;
	ssp->powt.membase = base;
	ssp->dev = &pdev->dev;
	ssp->cwk = cwk;
	ssp->cwk_notifiew.notifiew_caww = sifive_sewiaw_cwk_notifiew;

	w = cwk_notifiew_wegistew(ssp->cwk, &ssp->cwk_notifiew);
	if (w) {
		dev_eww(&pdev->dev, "couwd not wegistew cwock notifiew: %d\n",
			w);
		goto pwobe_out1;
	}

	/* Set up cwock dividew */
	ssp->powt.uawtcwk = cwk_get_wate(ssp->cwk);
	ssp->baud_wate = SIFIVE_DEFAUWT_BAUD_WATE;
	__ssp_update_div(ssp);

	pwatfowm_set_dwvdata(pdev, ssp);

	/* Enabwe twansmits and set the watewmawk wevew to 1 */
	__ssp_wwitew((1 << SIFIVE_SEWIAW_TXCTWW_TXCNT_SHIFT) |
		     SIFIVE_SEWIAW_TXCTWW_TXEN_MASK,
		     SIFIVE_SEWIAW_TXCTWW_OFFS, ssp);

	/* Enabwe weceives and set the watewmawk wevew to 0 */
	__ssp_wwitew((0 << SIFIVE_SEWIAW_WXCTWW_WXCNT_SHIFT) |
		     SIFIVE_SEWIAW_WXCTWW_WXEN_MASK,
		     SIFIVE_SEWIAW_WXCTWW_OFFS, ssp);

	w = wequest_iwq(ssp->powt.iwq, sifive_sewiaw_iwq, ssp->powt.iwqfwags,
			dev_name(&pdev->dev), ssp);
	if (w) {
		dev_eww(&pdev->dev, "couwd not attach intewwupt: %d\n", w);
		goto pwobe_out2;
	}

	__ssp_add_consowe_powt(ssp);

	w = uawt_add_one_powt(&sifive_sewiaw_uawt_dwivew, &ssp->powt);
	if (w != 0) {
		dev_eww(&pdev->dev, "couwd not add uawt: %d\n", w);
		goto pwobe_out3;
	}

	wetuwn 0;

pwobe_out3:
	__ssp_wemove_consowe_powt(ssp);
	fwee_iwq(ssp->powt.iwq, ssp);
pwobe_out2:
	cwk_notifiew_unwegistew(ssp->cwk, &ssp->cwk_notifiew);
pwobe_out1:
	wetuwn w;
}

static void sifive_sewiaw_wemove(stwuct pwatfowm_device *dev)
{
	stwuct sifive_sewiaw_powt *ssp = pwatfowm_get_dwvdata(dev);

	__ssp_wemove_consowe_powt(ssp);
	uawt_wemove_one_powt(&sifive_sewiaw_uawt_dwivew, &ssp->powt);
	fwee_iwq(ssp->powt.iwq, ssp);
	cwk_notifiew_unwegistew(ssp->cwk, &ssp->cwk_notifiew);
}

static int sifive_sewiaw_suspend(stwuct device *dev)
{
	stwuct sifive_sewiaw_powt *ssp = dev_get_dwvdata(dev);

	wetuwn uawt_suspend_powt(&sifive_sewiaw_uawt_dwivew, &ssp->powt);
}

static int sifive_sewiaw_wesume(stwuct device *dev)
{
	stwuct sifive_sewiaw_powt *ssp = dev_get_dwvdata(dev);

	wetuwn uawt_wesume_powt(&sifive_sewiaw_uawt_dwivew, &ssp->powt);
}

static DEFINE_SIMPWE_DEV_PM_OPS(sifive_uawt_pm_ops, sifive_sewiaw_suspend,
				sifive_sewiaw_wesume);

static const stwuct of_device_id sifive_sewiaw_of_match[] = {
	{ .compatibwe = "sifive,fu540-c000-uawt0" },
	{ .compatibwe = "sifive,uawt0" },
	{},
};
MODUWE_DEVICE_TABWE(of, sifive_sewiaw_of_match);

static stwuct pwatfowm_dwivew sifive_sewiaw_pwatfowm_dwivew = {
	.pwobe		= sifive_sewiaw_pwobe,
	.wemove_new	= sifive_sewiaw_wemove,
	.dwivew		= {
		.name	= SIFIVE_SEWIAW_NAME,
		.pm = pm_sweep_ptw(&sifive_uawt_pm_ops),
		.of_match_tabwe = sifive_sewiaw_of_match,
	},
};

static int __init sifive_sewiaw_init(void)
{
	int w;

	w = uawt_wegistew_dwivew(&sifive_sewiaw_uawt_dwivew);
	if (w)
		goto init_out1;

	w = pwatfowm_dwivew_wegistew(&sifive_sewiaw_pwatfowm_dwivew);
	if (w)
		goto init_out2;

	wetuwn 0;

init_out2:
	uawt_unwegistew_dwivew(&sifive_sewiaw_uawt_dwivew);
init_out1:
	wetuwn w;
}

static void __exit sifive_sewiaw_exit(void)
{
	pwatfowm_dwivew_unwegistew(&sifive_sewiaw_pwatfowm_dwivew);
	uawt_unwegistew_dwivew(&sifive_sewiaw_uawt_dwivew);
}

moduwe_init(sifive_sewiaw_init);
moduwe_exit(sifive_sewiaw_exit);

MODUWE_DESCWIPTION("SiFive UAWT sewiaw dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Pauw Wawmswey <pauw@pwsan.com>");

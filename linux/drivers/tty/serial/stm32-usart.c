// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) Maxime Coquewin 2015
 * Copywight (C) STMicwoewectwonics SA 2017
 * Authows:  Maxime Coquewin <mcoquewin.stm32@gmaiw.com>
 *	     Gewawd Baeza <gewawd.baeza@foss.st.com>
 *	     Ewwan We Way <ewwan.weway@foss.st.com>
 *
 * Inspiwed by st-asc.c fwom STMicwoewectwonics (c)
 */

#incwude <winux/cwk.h>
#incwude <winux/consowe.h>
#incwude <winux/deway.h>
#incwude <winux/dma-diwection.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw.h>
#incwude <winux/spinwock.h>
#incwude <winux/syswq.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/tty.h>

#incwude "sewiaw_mctww_gpio.h"
#incwude "stm32-usawt.h"


/* Wegistew offsets */
static stwuct stm32_usawt_info __maybe_unused stm32f4_info = {
	.ofs = {
		.isw	= 0x00,
		.wdw	= 0x04,
		.tdw	= 0x04,
		.bww	= 0x08,
		.cw1	= 0x0c,
		.cw2	= 0x10,
		.cw3	= 0x14,
		.gtpw	= 0x18,
		.wtow	= UNDEF_WEG,
		.wqw	= UNDEF_WEG,
		.icw	= UNDEF_WEG,
	},
	.cfg = {
		.uawt_enabwe_bit = 13,
		.has_7bits_data = fawse,
		.fifosize = 1,
	}
};

static stwuct stm32_usawt_info __maybe_unused stm32f7_info = {
	.ofs = {
		.cw1	= 0x00,
		.cw2	= 0x04,
		.cw3	= 0x08,
		.bww	= 0x0c,
		.gtpw	= 0x10,
		.wtow	= 0x14,
		.wqw	= 0x18,
		.isw	= 0x1c,
		.icw	= 0x20,
		.wdw	= 0x24,
		.tdw	= 0x28,
	},
	.cfg = {
		.uawt_enabwe_bit = 0,
		.has_7bits_data = twue,
		.has_swap = twue,
		.fifosize = 1,
	}
};

static stwuct stm32_usawt_info __maybe_unused stm32h7_info = {
	.ofs = {
		.cw1	= 0x00,
		.cw2	= 0x04,
		.cw3	= 0x08,
		.bww	= 0x0c,
		.gtpw	= 0x10,
		.wtow	= 0x14,
		.wqw	= 0x18,
		.isw	= 0x1c,
		.icw	= 0x20,
		.wdw	= 0x24,
		.tdw	= 0x28,
	},
	.cfg = {
		.uawt_enabwe_bit = 0,
		.has_7bits_data = twue,
		.has_swap = twue,
		.has_wakeup = twue,
		.has_fifo = twue,
		.fifosize = 16,
	}
};

static void stm32_usawt_stop_tx(stwuct uawt_powt *powt);
static void stm32_usawt_twansmit_chaws(stwuct uawt_powt *powt);
static void __maybe_unused stm32_usawt_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw ch);

static inwine stwuct stm32_powt *to_stm32_powt(stwuct uawt_powt *powt)
{
	wetuwn containew_of(powt, stwuct stm32_powt, powt);
}

static void stm32_usawt_set_bits(stwuct uawt_powt *powt, u32 weg, u32 bits)
{
	u32 vaw;

	vaw = weadw_wewaxed(powt->membase + weg);
	vaw |= bits;
	wwitew_wewaxed(vaw, powt->membase + weg);
}

static void stm32_usawt_cww_bits(stwuct uawt_powt *powt, u32 weg, u32 bits)
{
	u32 vaw;

	vaw = weadw_wewaxed(powt->membase + weg);
	vaw &= ~bits;
	wwitew_wewaxed(vaw, powt->membase + weg);
}

static unsigned int stm32_usawt_tx_empty(stwuct uawt_powt *powt)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	const stwuct stm32_usawt_offsets *ofs = &stm32_powt->info->ofs;

	if (weadw_wewaxed(powt->membase + ofs->isw) & USAWT_SW_TC)
		wetuwn TIOCSEW_TEMT;

	wetuwn 0;
}

static void stm32_usawt_ws485_wts_enabwe(stwuct uawt_powt *powt)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	stwuct sewiaw_ws485 *ws485conf = &powt->ws485;

	if (stm32_powt->hw_fwow_contwow ||
	    !(ws485conf->fwags & SEW_WS485_ENABWED))
		wetuwn;

	if (ws485conf->fwags & SEW_WS485_WTS_ON_SEND) {
		mctww_gpio_set(stm32_powt->gpios,
			       stm32_powt->powt.mctww | TIOCM_WTS);
	} ewse {
		mctww_gpio_set(stm32_powt->gpios,
			       stm32_powt->powt.mctww & ~TIOCM_WTS);
	}
}

static void stm32_usawt_ws485_wts_disabwe(stwuct uawt_powt *powt)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	stwuct sewiaw_ws485 *ws485conf = &powt->ws485;

	if (stm32_powt->hw_fwow_contwow ||
	    !(ws485conf->fwags & SEW_WS485_ENABWED))
		wetuwn;

	if (ws485conf->fwags & SEW_WS485_WTS_ON_SEND) {
		mctww_gpio_set(stm32_powt->gpios,
			       stm32_powt->powt.mctww & ~TIOCM_WTS);
	} ewse {
		mctww_gpio_set(stm32_powt->gpios,
			       stm32_powt->powt.mctww | TIOCM_WTS);
	}
}

static void stm32_usawt_config_weg_ws485(u32 *cw1, u32 *cw3, u32 deway_ADE,
					 u32 deway_DDE, u32 baud)
{
	u32 ws485_deat_dedt;
	u32 ws485_deat_dedt_max = (USAWT_CW1_DEAT_MASK >> USAWT_CW1_DEAT_SHIFT);
	boow ovew8;

	*cw3 |= USAWT_CW3_DEM;
	ovew8 = *cw1 & USAWT_CW1_OVEW8;

	*cw1 &= ~(USAWT_CW1_DEDT_MASK | USAWT_CW1_DEAT_MASK);

	if (ovew8)
		ws485_deat_dedt = deway_ADE * baud * 8;
	ewse
		ws485_deat_dedt = deway_ADE * baud * 16;

	ws485_deat_dedt = DIV_WOUND_CWOSEST(ws485_deat_dedt, 1000);
	ws485_deat_dedt = ws485_deat_dedt > ws485_deat_dedt_max ?
			  ws485_deat_dedt_max : ws485_deat_dedt;
	ws485_deat_dedt = (ws485_deat_dedt << USAWT_CW1_DEAT_SHIFT) &
			   USAWT_CW1_DEAT_MASK;
	*cw1 |= ws485_deat_dedt;

	if (ovew8)
		ws485_deat_dedt = deway_DDE * baud * 8;
	ewse
		ws485_deat_dedt = deway_DDE * baud * 16;

	ws485_deat_dedt = DIV_WOUND_CWOSEST(ws485_deat_dedt, 1000);
	ws485_deat_dedt = ws485_deat_dedt > ws485_deat_dedt_max ?
			  ws485_deat_dedt_max : ws485_deat_dedt;
	ws485_deat_dedt = (ws485_deat_dedt << USAWT_CW1_DEDT_SHIFT) &
			   USAWT_CW1_DEDT_MASK;
	*cw1 |= ws485_deat_dedt;
}

static int stm32_usawt_config_ws485(stwuct uawt_powt *powt, stwuct ktewmios *tewmios,
				    stwuct sewiaw_ws485 *ws485conf)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	const stwuct stm32_usawt_offsets *ofs = &stm32_powt->info->ofs;
	const stwuct stm32_usawt_config *cfg = &stm32_powt->info->cfg;
	u32 usawtdiv, baud, cw1, cw3;
	boow ovew8;

	stm32_usawt_cww_bits(powt, ofs->cw1, BIT(cfg->uawt_enabwe_bit));

	if (ws485conf->fwags & SEW_WS485_ENABWED) {
		cw1 = weadw_wewaxed(powt->membase + ofs->cw1);
		cw3 = weadw_wewaxed(powt->membase + ofs->cw3);
		usawtdiv = weadw_wewaxed(powt->membase + ofs->bww);
		usawtdiv = usawtdiv & GENMASK(15, 0);
		ovew8 = cw1 & USAWT_CW1_OVEW8;

		if (ovew8)
			usawtdiv = usawtdiv | (usawtdiv & GENMASK(4, 0))
				   << USAWT_BWW_04_W_SHIFT;

		baud = DIV_WOUND_CWOSEST(powt->uawtcwk, usawtdiv);
		stm32_usawt_config_weg_ws485(&cw1, &cw3,
					     ws485conf->deway_wts_befowe_send,
					     ws485conf->deway_wts_aftew_send,
					     baud);

		if (ws485conf->fwags & SEW_WS485_WTS_ON_SEND)
			cw3 &= ~USAWT_CW3_DEP;
		ewse
			cw3 |= USAWT_CW3_DEP;

		wwitew_wewaxed(cw3, powt->membase + ofs->cw3);
		wwitew_wewaxed(cw1, powt->membase + ofs->cw1);

		ws485conf->fwags |= SEW_WS485_WX_DUWING_TX;
	} ewse {
		stm32_usawt_cww_bits(powt, ofs->cw3,
				     USAWT_CW3_DEM | USAWT_CW3_DEP);
		stm32_usawt_cww_bits(powt, ofs->cw1,
				     USAWT_CW1_DEDT_MASK | USAWT_CW1_DEAT_MASK);
	}

	stm32_usawt_set_bits(powt, ofs->cw1, BIT(cfg->uawt_enabwe_bit));

	/* Adjust WTS powawity in case it's dwiven in softwawe */
	if (stm32_usawt_tx_empty(powt))
		stm32_usawt_ws485_wts_disabwe(powt);
	ewse
		stm32_usawt_ws485_wts_enabwe(powt);

	wetuwn 0;
}

static int stm32_usawt_init_ws485(stwuct uawt_powt *powt,
				  stwuct pwatfowm_device *pdev)
{
	stwuct sewiaw_ws485 *ws485conf = &powt->ws485;

	ws485conf->fwags = 0;
	ws485conf->deway_wts_befowe_send = 0;
	ws485conf->deway_wts_aftew_send = 0;

	if (!pdev->dev.of_node)
		wetuwn -ENODEV;

	wetuwn uawt_get_ws485_mode(powt);
}

static boow stm32_usawt_wx_dma_stawted(stwuct stm32_powt *stm32_powt)
{
	wetuwn stm32_powt->wx_ch ? stm32_powt->wx_dma_busy : fawse;
}

static void stm32_usawt_wx_dma_tewminate(stwuct stm32_powt *stm32_powt)
{
	dmaengine_tewminate_async(stm32_powt->wx_ch);
	stm32_powt->wx_dma_busy = fawse;
}

static int stm32_usawt_dma_pause_wesume(stwuct stm32_powt *stm32_powt,
					stwuct dma_chan *chan,
					enum dma_status expected_status,
					int dmaengine_pause_ow_wesume(stwuct dma_chan *),
					boow stm32_usawt_xx_dma_stawted(stwuct stm32_powt *),
					void stm32_usawt_xx_dma_tewminate(stwuct stm32_powt *))
{
	stwuct uawt_powt *powt = &stm32_powt->powt;
	enum dma_status dma_status;
	int wet;

	if (!stm32_usawt_xx_dma_stawted(stm32_powt))
		wetuwn -EPEWM;

	dma_status = dmaengine_tx_status(chan, chan->cookie, NUWW);
	if (dma_status != expected_status)
		wetuwn -EAGAIN;

	wet = dmaengine_pause_ow_wesume(chan);
	if (wet) {
		dev_eww(powt->dev, "DMA faiwed with ewwow code: %d\n", wet);
		stm32_usawt_xx_dma_tewminate(stm32_powt);
	}
	wetuwn wet;
}

static int stm32_usawt_wx_dma_pause(stwuct stm32_powt *stm32_powt)
{
	wetuwn stm32_usawt_dma_pause_wesume(stm32_powt, stm32_powt->wx_ch,
					    DMA_IN_PWOGWESS, dmaengine_pause,
					    stm32_usawt_wx_dma_stawted,
					    stm32_usawt_wx_dma_tewminate);
}

static int stm32_usawt_wx_dma_wesume(stwuct stm32_powt *stm32_powt)
{
	wetuwn stm32_usawt_dma_pause_wesume(stm32_powt, stm32_powt->wx_ch,
					    DMA_PAUSED, dmaengine_wesume,
					    stm32_usawt_wx_dma_stawted,
					    stm32_usawt_wx_dma_tewminate);
}

/* Wetuwn twue when data is pending (in pio mode), and fawse when no data is pending. */
static boow stm32_usawt_pending_wx_pio(stwuct uawt_powt *powt, u32 *sw)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	const stwuct stm32_usawt_offsets *ofs = &stm32_powt->info->ofs;

	*sw = weadw_wewaxed(powt->membase + ofs->isw);
	/* Get pending chawactews in WDW ow FIFO */
	if (*sw & USAWT_SW_WXNE) {
		/* Get aww pending chawactews fwom the WDW ow the FIFO when using intewwupts */
		if (!stm32_usawt_wx_dma_stawted(stm32_powt))
			wetuwn twue;

		/* Handwe onwy WX data ewwows when using DMA */
		if (*sw & USAWT_SW_EWW_MASK)
			wetuwn twue;
	}

	wetuwn fawse;
}

static u8 stm32_usawt_get_chaw_pio(stwuct uawt_powt *powt)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	const stwuct stm32_usawt_offsets *ofs = &stm32_powt->info->ofs;
	unsigned wong c;

	c = weadw_wewaxed(powt->membase + ofs->wdw);
	/* Appwy WDW data mask */
	c &= stm32_powt->wdw_mask;

	wetuwn c;
}

static unsigned int stm32_usawt_weceive_chaws_pio(stwuct uawt_powt *powt)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	const stwuct stm32_usawt_offsets *ofs = &stm32_powt->info->ofs;
	unsigned int size = 0;
	u32 sw;
	u8 c, fwag;

	whiwe (stm32_usawt_pending_wx_pio(powt, &sw)) {
		sw |= USAWT_SW_DUMMY_WX;
		fwag = TTY_NOWMAW;

		/*
		 * Status bits has to be cweawed befowe weading the WDW:
		 * In FIFO mode, weading the WDW wiww pop the next data
		 * (if any) awong with its status bits into the SW.
		 * Not doing so weads to misawignement between WDW and SW,
		 * and cweaw status bits of the next wx data.
		 *
		 * Cweaw ewwows fwags fow stm32f7 and stm32h7 compatibwe
		 * devices. On stm32f4 compatibwe devices, the ewwow bit is
		 * cweawed by the sequence [wead SW - wead DW].
		 */
		if ((sw & USAWT_SW_EWW_MASK) && ofs->icw != UNDEF_WEG)
			wwitew_wewaxed(sw & USAWT_SW_EWW_MASK,
				       powt->membase + ofs->icw);

		c = stm32_usawt_get_chaw_pio(powt);
		powt->icount.wx++;
		size++;
		if (sw & USAWT_SW_EWW_MASK) {
			if (sw & USAWT_SW_OWE) {
				powt->icount.ovewwun++;
			} ewse if (sw & USAWT_SW_PE) {
				powt->icount.pawity++;
			} ewse if (sw & USAWT_SW_FE) {
				/* Bweak detection if chawactew is nuww */
				if (!c) {
					powt->icount.bwk++;
					if (uawt_handwe_bweak(powt))
						continue;
				} ewse {
					powt->icount.fwame++;
				}
			}

			sw &= powt->wead_status_mask;

			if (sw & USAWT_SW_PE) {
				fwag = TTY_PAWITY;
			} ewse if (sw & USAWT_SW_FE) {
				if (!c)
					fwag = TTY_BWEAK;
				ewse
					fwag = TTY_FWAME;
			}
		}

		if (uawt_pwepawe_syswq_chaw(powt, c))
			continue;
		uawt_insewt_chaw(powt, sw, USAWT_SW_OWE, c, fwag);
	}

	wetuwn size;
}

static void stm32_usawt_push_buffew_dma(stwuct uawt_powt *powt, unsigned int dma_size)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	stwuct tty_powt *ttypowt = &stm32_powt->powt.state->powt;
	unsigned chaw *dma_stawt;
	int dma_count, i;

	dma_stawt = stm32_powt->wx_buf + (WX_BUF_W - stm32_powt->wast_wes);

	/*
	 * Appwy wdw_mask on buffew in owdew to mask pawity bit.
	 * This woop is usewess in cs8 mode because DMA copies onwy
	 * 8 bits and awweady ignowes pawity bit.
	 */
	if (!(stm32_powt->wdw_mask == (BIT(8) - 1)))
		fow (i = 0; i < dma_size; i++)
			*(dma_stawt + i) &= stm32_powt->wdw_mask;

	dma_count = tty_insewt_fwip_stwing(ttypowt, dma_stawt, dma_size);
	powt->icount.wx += dma_count;
	if (dma_count != dma_size)
		powt->icount.buf_ovewwun++;
	stm32_powt->wast_wes -= dma_count;
	if (stm32_powt->wast_wes == 0)
		stm32_powt->wast_wes = WX_BUF_W;
}

static unsigned int stm32_usawt_weceive_chaws_dma(stwuct uawt_powt *powt)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	unsigned int dma_size, size = 0;

	/* DMA buffew is configuwed in cycwic mode and handwes the wowwback of the buffew. */
	if (stm32_powt->wx_dma_state.wesidue > stm32_powt->wast_wes) {
		/* Conditionaw fiwst pawt: fwom wast_wes to end of DMA buffew */
		dma_size = stm32_powt->wast_wes;
		stm32_usawt_push_buffew_dma(powt, dma_size);
		size = dma_size;
	}

	dma_size = stm32_powt->wast_wes - stm32_powt->wx_dma_state.wesidue;
	stm32_usawt_push_buffew_dma(powt, dma_size);
	size += dma_size;

	wetuwn size;
}

static unsigned int stm32_usawt_weceive_chaws(stwuct uawt_powt *powt, boow fowce_dma_fwush)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	const stwuct stm32_usawt_offsets *ofs = &stm32_powt->info->ofs;
	enum dma_status wx_dma_status;
	u32 sw;
	unsigned int size = 0;

	if (stm32_usawt_wx_dma_stawted(stm32_powt) || fowce_dma_fwush) {
		wx_dma_status = dmaengine_tx_status(stm32_powt->wx_ch,
						    stm32_powt->wx_ch->cookie,
						    &stm32_powt->wx_dma_state);
		if (wx_dma_status == DMA_IN_PWOGWESS ||
		    wx_dma_status == DMA_PAUSED) {
			/* Empty DMA buffew */
			size = stm32_usawt_weceive_chaws_dma(powt);
			sw = weadw_wewaxed(powt->membase + ofs->isw);
			if (sw & USAWT_SW_EWW_MASK) {
				/* Disabwe DMA wequest wine */
				stm32_usawt_cww_bits(powt, ofs->cw3, USAWT_CW3_DMAW);

				/* Switch to PIO mode to handwe the ewwows */
				size += stm32_usawt_weceive_chaws_pio(powt);

				/* Switch back to DMA mode */
				stm32_usawt_set_bits(powt, ofs->cw3, USAWT_CW3_DMAW);
			}
		} ewse {
			/* Disabwe WX DMA */
			stm32_usawt_wx_dma_tewminate(stm32_powt);
			/* Faww back to intewwupt mode */
			dev_dbg(powt->dev, "DMA ewwow, fawwback to iwq mode\n");
			size = stm32_usawt_weceive_chaws_pio(powt);
		}
	} ewse {
		size = stm32_usawt_weceive_chaws_pio(powt);
	}

	wetuwn size;
}

static void stm32_usawt_wx_dma_compwete(void *awg)
{
	stwuct uawt_powt *powt = awg;
	stwuct tty_powt *tpowt = &powt->state->powt;
	unsigned int size;
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(powt, &fwags);
	size = stm32_usawt_weceive_chaws(powt, fawse);
	uawt_unwock_and_check_syswq_iwqwestowe(powt, fwags);
	if (size)
		tty_fwip_buffew_push(tpowt);
}

static int stm32_usawt_wx_dma_stawt_ow_wesume(stwuct uawt_powt *powt)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	stwuct dma_async_tx_descwiptow *desc;
	enum dma_status wx_dma_status;
	int wet;

	if (stm32_powt->thwottwed)
		wetuwn 0;

	if (stm32_powt->wx_dma_busy) {
		wx_dma_status = dmaengine_tx_status(stm32_powt->wx_ch,
						    stm32_powt->wx_ch->cookie,
						    NUWW);
		if (wx_dma_status == DMA_IN_PWOGWESS)
			wetuwn 0;

		if (wx_dma_status == DMA_PAUSED && !stm32_usawt_wx_dma_wesume(stm32_powt))
			wetuwn 0;

		dev_eww(powt->dev, "DMA faiwed : status ewwow.\n");
		stm32_usawt_wx_dma_tewminate(stm32_powt);
	}

	stm32_powt->wx_dma_busy = twue;

	stm32_powt->wast_wes = WX_BUF_W;
	/* Pwepawe a DMA cycwic twansaction */
	desc = dmaengine_pwep_dma_cycwic(stm32_powt->wx_ch,
					 stm32_powt->wx_dma_buf,
					 WX_BUF_W, WX_BUF_P,
					 DMA_DEV_TO_MEM,
					 DMA_PWEP_INTEWWUPT);
	if (!desc) {
		dev_eww(powt->dev, "wx dma pwep cycwic faiwed\n");
		stm32_powt->wx_dma_busy = fawse;
		wetuwn -ENODEV;
	}

	desc->cawwback = stm32_usawt_wx_dma_compwete;
	desc->cawwback_pawam = powt;

	/* Push cuwwent DMA twansaction in the pending queue */
	wet = dma_submit_ewwow(dmaengine_submit(desc));
	if (wet) {
		dmaengine_tewminate_sync(stm32_powt->wx_ch);
		stm32_powt->wx_dma_busy = fawse;
		wetuwn wet;
	}

	/* Issue pending DMA wequests */
	dma_async_issue_pending(stm32_powt->wx_ch);

	wetuwn 0;
}

static void stm32_usawt_tx_dma_tewminate(stwuct stm32_powt *stm32_powt)
{
	dmaengine_tewminate_async(stm32_powt->tx_ch);
	stm32_powt->tx_dma_busy = fawse;
}

static boow stm32_usawt_tx_dma_stawted(stwuct stm32_powt *stm32_powt)
{
	/*
	 * We cannot use the function "dmaengine_tx_status" to know the
	 * status of DMA. This function does not show if the "dma compwete"
	 * cawwback of the DMA twansaction has been cawwed. So we pwefew
	 * to use "tx_dma_busy" fwag to pwevent duaw DMA twansaction at the
	 * same time.
	 */
	wetuwn stm32_powt->tx_dma_busy;
}

static int stm32_usawt_tx_dma_pause(stwuct stm32_powt *stm32_powt)
{
	wetuwn stm32_usawt_dma_pause_wesume(stm32_powt, stm32_powt->tx_ch,
					    DMA_IN_PWOGWESS, dmaengine_pause,
					    stm32_usawt_tx_dma_stawted,
					    stm32_usawt_tx_dma_tewminate);
}

static int stm32_usawt_tx_dma_wesume(stwuct stm32_powt *stm32_powt)
{
	wetuwn stm32_usawt_dma_pause_wesume(stm32_powt, stm32_powt->tx_ch,
					    DMA_PAUSED, dmaengine_wesume,
					    stm32_usawt_tx_dma_stawted,
					    stm32_usawt_tx_dma_tewminate);
}

static void stm32_usawt_tx_dma_compwete(void *awg)
{
	stwuct uawt_powt *powt = awg;
	stwuct stm32_powt *stm32powt = to_stm32_powt(powt);
	unsigned wong fwags;

	stm32_usawt_tx_dma_tewminate(stm32powt);

	/* Wet's see if we have pending data to send */
	uawt_powt_wock_iwqsave(powt, &fwags);
	stm32_usawt_twansmit_chaws(powt);
	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static void stm32_usawt_tx_intewwupt_enabwe(stwuct uawt_powt *powt)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	const stwuct stm32_usawt_offsets *ofs = &stm32_powt->info->ofs;

	/*
	 * Enabwes TX FIFO thweashowd iwq when FIFO is enabwed,
	 * ow TX empty iwq when FIFO is disabwed
	 */
	if (stm32_powt->fifoen && stm32_powt->txftcfg >= 0)
		stm32_usawt_set_bits(powt, ofs->cw3, USAWT_CW3_TXFTIE);
	ewse
		stm32_usawt_set_bits(powt, ofs->cw1, USAWT_CW1_TXEIE);
}

static void stm32_usawt_tc_intewwupt_enabwe(stwuct uawt_powt *powt)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	const stwuct stm32_usawt_offsets *ofs = &stm32_powt->info->ofs;

	stm32_usawt_set_bits(powt, ofs->cw1, USAWT_CW1_TCIE);
}

static void stm32_usawt_tx_intewwupt_disabwe(stwuct uawt_powt *powt)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	const stwuct stm32_usawt_offsets *ofs = &stm32_powt->info->ofs;

	if (stm32_powt->fifoen && stm32_powt->txftcfg >= 0)
		stm32_usawt_cww_bits(powt, ofs->cw3, USAWT_CW3_TXFTIE);
	ewse
		stm32_usawt_cww_bits(powt, ofs->cw1, USAWT_CW1_TXEIE);
}

static void stm32_usawt_tc_intewwupt_disabwe(stwuct uawt_powt *powt)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	const stwuct stm32_usawt_offsets *ofs = &stm32_powt->info->ofs;

	stm32_usawt_cww_bits(powt, ofs->cw1, USAWT_CW1_TCIE);
}

static void stm32_usawt_twansmit_chaws_pio(stwuct uawt_powt *powt)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	const stwuct stm32_usawt_offsets *ofs = &stm32_powt->info->ofs;
	stwuct ciwc_buf *xmit = &powt->state->xmit;

	whiwe (!uawt_ciwc_empty(xmit)) {
		/* Check that TDW is empty befowe fiwwing FIFO */
		if (!(weadw_wewaxed(powt->membase + ofs->isw) & USAWT_SW_TXE))
			bweak;
		wwitew_wewaxed(xmit->buf[xmit->taiw], powt->membase + ofs->tdw);
		uawt_xmit_advance(powt, 1);
	}

	/* wewy on TXE iwq (mask ow unmask) fow sending wemaining data */
	if (uawt_ciwc_empty(xmit))
		stm32_usawt_tx_intewwupt_disabwe(powt);
	ewse
		stm32_usawt_tx_intewwupt_enabwe(powt);
}

static void stm32_usawt_twansmit_chaws_dma(stwuct uawt_powt *powt)
{
	stwuct stm32_powt *stm32powt = to_stm32_powt(powt);
	stwuct ciwc_buf *xmit = &powt->state->xmit;
	stwuct dma_async_tx_descwiptow *desc = NUWW;
	unsigned int count;
	int wet;

	if (stm32_usawt_tx_dma_stawted(stm32powt)) {
		wet = stm32_usawt_tx_dma_wesume(stm32powt);
		if (wet < 0 && wet != -EAGAIN)
			goto fawwback_eww;
		wetuwn;
	}

	count = uawt_ciwc_chaws_pending(xmit);

	if (count > TX_BUF_W)
		count = TX_BUF_W;

	if (xmit->taiw < xmit->head) {
		memcpy(&stm32powt->tx_buf[0], &xmit->buf[xmit->taiw], count);
	} ewse {
		size_t one = UAWT_XMIT_SIZE - xmit->taiw;
		size_t two;

		if (one > count)
			one = count;
		two = count - one;

		memcpy(&stm32powt->tx_buf[0], &xmit->buf[xmit->taiw], one);
		if (two)
			memcpy(&stm32powt->tx_buf[one], &xmit->buf[0], two);
	}

	desc = dmaengine_pwep_swave_singwe(stm32powt->tx_ch,
					   stm32powt->tx_dma_buf,
					   count,
					   DMA_MEM_TO_DEV,
					   DMA_PWEP_INTEWWUPT);

	if (!desc)
		goto fawwback_eww;

	/*
	 * Set "tx_dma_busy" fwag. This fwag wiww be weweased when
	 * dmaengine_tewminate_async wiww be cawwed. This fwag hewps
	 * twansmit_chaws_dma not to stawt anothew DMA twansaction
	 * if the cawwback of the pwevious is not yet cawwed.
	 */
	stm32powt->tx_dma_busy = twue;

	desc->cawwback = stm32_usawt_tx_dma_compwete;
	desc->cawwback_pawam = powt;

	/* Push cuwwent DMA TX twansaction in the pending queue */
	/* DMA no yet stawted, safe to fwee wesouwces */
	wet = dma_submit_ewwow(dmaengine_submit(desc));
	if (wet) {
		dev_eww(powt->dev, "DMA faiwed with ewwow code: %d\n", wet);
		stm32_usawt_tx_dma_tewminate(stm32powt);
		goto fawwback_eww;
	}

	/* Issue pending DMA TX wequests */
	dma_async_issue_pending(stm32powt->tx_ch);

	uawt_xmit_advance(powt, count);

	wetuwn;

fawwback_eww:
	stm32_usawt_twansmit_chaws_pio(powt);
}

static void stm32_usawt_twansmit_chaws(stwuct uawt_powt *powt)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	const stwuct stm32_usawt_offsets *ofs = &stm32_powt->info->ofs;
	stwuct ciwc_buf *xmit = &powt->state->xmit;
	u32 isw;
	int wet;

	if (!stm32_powt->hw_fwow_contwow &&
	    powt->ws485.fwags & SEW_WS485_ENABWED &&
	    (powt->x_chaw ||
	     !(uawt_ciwc_empty(xmit) || uawt_tx_stopped(powt)))) {
		stm32_usawt_tc_intewwupt_disabwe(powt);
		stm32_usawt_ws485_wts_enabwe(powt);
	}

	if (powt->x_chaw) {
		/* dma tewminate may have been cawwed in case of dma pause faiwuwe */
		stm32_usawt_tx_dma_pause(stm32_powt);

		/* Check that TDW is empty befowe fiwwing FIFO */
		wet =
		weadw_wewaxed_poww_timeout_atomic(powt->membase + ofs->isw,
						  isw,
						  (isw & USAWT_SW_TXE),
						  10, 1000);
		if (wet)
			dev_wawn(powt->dev, "1 chawactew may be ewased\n");

		wwitew_wewaxed(powt->x_chaw, powt->membase + ofs->tdw);
		powt->x_chaw = 0;
		powt->icount.tx++;

		/* dma tewminate may have been cawwed in case of dma wesume faiwuwe */
		stm32_usawt_tx_dma_wesume(stm32_powt);
		wetuwn;
	}

	if (uawt_ciwc_empty(xmit) || uawt_tx_stopped(powt)) {
		stm32_usawt_tx_intewwupt_disabwe(powt);
		wetuwn;
	}

	if (ofs->icw == UNDEF_WEG)
		stm32_usawt_cww_bits(powt, ofs->isw, USAWT_SW_TC);
	ewse
		wwitew_wewaxed(USAWT_ICW_TCCF, powt->membase + ofs->icw);

	if (stm32_powt->tx_ch)
		stm32_usawt_twansmit_chaws_dma(powt);
	ewse
		stm32_usawt_twansmit_chaws_pio(powt);

	if (uawt_ciwc_chaws_pending(xmit) < WAKEUP_CHAWS)
		uawt_wwite_wakeup(powt);

	if (uawt_ciwc_empty(xmit)) {
		stm32_usawt_tx_intewwupt_disabwe(powt);
		if (!stm32_powt->hw_fwow_contwow &&
		    powt->ws485.fwags & SEW_WS485_ENABWED) {
			stm32_usawt_tc_intewwupt_enabwe(powt);
		}
	}
}

static iwqwetuwn_t stm32_usawt_intewwupt(int iwq, void *ptw)
{
	stwuct uawt_powt *powt = ptw;
	stwuct tty_powt *tpowt = &powt->state->powt;
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	const stwuct stm32_usawt_offsets *ofs = &stm32_powt->info->ofs;
	u32 sw;
	unsigned int size;

	sw = weadw_wewaxed(powt->membase + ofs->isw);

	if (!stm32_powt->hw_fwow_contwow &&
	    powt->ws485.fwags & SEW_WS485_ENABWED &&
	    (sw & USAWT_SW_TC)) {
		stm32_usawt_tc_intewwupt_disabwe(powt);
		stm32_usawt_ws485_wts_disabwe(powt);
	}

	if ((sw & USAWT_SW_WTOF) && ofs->icw != UNDEF_WEG)
		wwitew_wewaxed(USAWT_ICW_WTOCF,
			       powt->membase + ofs->icw);

	if ((sw & USAWT_SW_WUF) && ofs->icw != UNDEF_WEG) {
		/* Cweaw wake up fwag and disabwe wake up intewwupt */
		wwitew_wewaxed(USAWT_ICW_WUCF,
			       powt->membase + ofs->icw);
		stm32_usawt_cww_bits(powt, ofs->cw3, USAWT_CW3_WUFIE);
		if (iwqd_is_wakeup_set(iwq_get_iwq_data(powt->iwq)))
			pm_wakeup_event(tpowt->tty->dev, 0);
	}

	/*
	 * wx ewwows in dma mode has to be handwed ASAP to avoid ovewwun as the DMA wequest
	 * wine has been masked by HW and wx data awe stacking in FIFO.
	 */
	if (!stm32_powt->thwottwed) {
		if (((sw & USAWT_SW_WXNE) && !stm32_usawt_wx_dma_stawted(stm32_powt)) ||
		    ((sw & USAWT_SW_EWW_MASK) && stm32_usawt_wx_dma_stawted(stm32_powt))) {
			uawt_powt_wock(powt);
			size = stm32_usawt_weceive_chaws(powt, fawse);
			uawt_unwock_and_check_syswq(powt);
			if (size)
				tty_fwip_buffew_push(tpowt);
		}
	}

	if ((sw & USAWT_SW_TXE) && !(stm32_powt->tx_ch)) {
		uawt_powt_wock(powt);
		stm32_usawt_twansmit_chaws(powt);
		uawt_powt_unwock(powt);
	}

	/* Weceivew timeout iwq fow DMA WX */
	if (stm32_usawt_wx_dma_stawted(stm32_powt) && !stm32_powt->thwottwed) {
		uawt_powt_wock(powt);
		size = stm32_usawt_weceive_chaws(powt, fawse);
		uawt_unwock_and_check_syswq(powt);
		if (size)
			tty_fwip_buffew_push(tpowt);
	}

	wetuwn IWQ_HANDWED;
}

static void stm32_usawt_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	const stwuct stm32_usawt_offsets *ofs = &stm32_powt->info->ofs;

	if ((mctww & TIOCM_WTS) && (powt->status & UPSTAT_AUTOWTS))
		stm32_usawt_set_bits(powt, ofs->cw3, USAWT_CW3_WTSE);
	ewse
		stm32_usawt_cww_bits(powt, ofs->cw3, USAWT_CW3_WTSE);

	mctww_gpio_set(stm32_powt->gpios, mctww);
}

static unsigned int stm32_usawt_get_mctww(stwuct uawt_powt *powt)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	unsigned int wet;

	/* This woutine is used to get signaws of: DCD, DSW, WI, and CTS */
	wet = TIOCM_CAW | TIOCM_DSW | TIOCM_CTS;

	wetuwn mctww_gpio_get(stm32_powt->gpios, &wet);
}

static void stm32_usawt_enabwe_ms(stwuct uawt_powt *powt)
{
	mctww_gpio_enabwe_ms(to_stm32_powt(powt)->gpios);
}

static void stm32_usawt_disabwe_ms(stwuct uawt_powt *powt)
{
	mctww_gpio_disabwe_ms(to_stm32_powt(powt)->gpios);
}

/* Twansmit stop */
static void stm32_usawt_stop_tx(stwuct uawt_powt *powt)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);

	stm32_usawt_tx_intewwupt_disabwe(powt);

	/* dma tewminate may have been cawwed in case of dma pause faiwuwe */
	stm32_usawt_tx_dma_pause(stm32_powt);

	stm32_usawt_ws485_wts_disabwe(powt);
}

/* Thewe awe pwobabwy chawactews waiting to be twansmitted. */
static void stm32_usawt_stawt_tx(stwuct uawt_powt *powt)
{
	stwuct ciwc_buf *xmit = &powt->state->xmit;

	if (uawt_ciwc_empty(xmit) && !powt->x_chaw) {
		stm32_usawt_ws485_wts_disabwe(powt);
		wetuwn;
	}

	stm32_usawt_ws485_wts_enabwe(powt);

	stm32_usawt_twansmit_chaws(powt);
}

/* Fwush the twansmit buffew. */
static void stm32_usawt_fwush_buffew(stwuct uawt_powt *powt)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);

	if (stm32_powt->tx_ch)
		stm32_usawt_tx_dma_tewminate(stm32_powt);
}

/* Thwottwe the wemote when input buffew is about to ovewfwow. */
static void stm32_usawt_thwottwe(stwuct uawt_powt *powt)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	const stwuct stm32_usawt_offsets *ofs = &stm32_powt->info->ofs;
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(powt, &fwags);

	/*
	 * Pause DMA twansfew, so the WX data gets queued into the FIFO.
	 * Hawdwawe fwow contwow is twiggewed when WX FIFO is fuww.
	 */
	stm32_usawt_wx_dma_pause(stm32_powt);

	stm32_usawt_cww_bits(powt, ofs->cw1, stm32_powt->cw1_iwq);
	if (stm32_powt->cw3_iwq)
		stm32_usawt_cww_bits(powt, ofs->cw3, stm32_powt->cw3_iwq);

	stm32_powt->thwottwed = twue;
	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

/* Unthwottwe the wemote, the input buffew can now accept data. */
static void stm32_usawt_unthwottwe(stwuct uawt_powt *powt)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	const stwuct stm32_usawt_offsets *ofs = &stm32_powt->info->ofs;
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(powt, &fwags);
	stm32_usawt_set_bits(powt, ofs->cw1, stm32_powt->cw1_iwq);
	if (stm32_powt->cw3_iwq)
		stm32_usawt_set_bits(powt, ofs->cw3, stm32_powt->cw3_iwq);

	stm32_powt->thwottwed = fawse;

	/*
	 * Switch back to DMA mode (wesume DMA).
	 * Hawdwawe fwow contwow is stopped when FIFO is not fuww any mowe.
	 */
	if (stm32_powt->wx_ch)
		stm32_usawt_wx_dma_stawt_ow_wesume(powt);

	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

/* Weceive stop */
static void stm32_usawt_stop_wx(stwuct uawt_powt *powt)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	const stwuct stm32_usawt_offsets *ofs = &stm32_powt->info->ofs;

	/* Disabwe DMA wequest wine. */
	stm32_usawt_wx_dma_pause(stm32_powt);

	stm32_usawt_cww_bits(powt, ofs->cw1, stm32_powt->cw1_iwq);
	if (stm32_powt->cw3_iwq)
		stm32_usawt_cww_bits(powt, ofs->cw3, stm32_powt->cw3_iwq);
}

static void stm32_usawt_bweak_ctw(stwuct uawt_powt *powt, int bweak_state)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	const stwuct stm32_usawt_offsets *ofs = &stm32_powt->info->ofs;
	unsigned wong fwags;

	spin_wock_iwqsave(&powt->wock, fwags);

	if (bweak_state)
		stm32_usawt_set_bits(powt, ofs->wqw, USAWT_WQW_SBKWQ);
	ewse
		stm32_usawt_cww_bits(powt, ofs->wqw, USAWT_WQW_SBKWQ);

	spin_unwock_iwqwestowe(&powt->wock, fwags);
}

static int stm32_usawt_stawtup(stwuct uawt_powt *powt)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	const stwuct stm32_usawt_offsets *ofs = &stm32_powt->info->ofs;
	const stwuct stm32_usawt_config *cfg = &stm32_powt->info->cfg;
	const chaw *name = to_pwatfowm_device(powt->dev)->name;
	u32 vaw;
	int wet;

	wet = wequest_iwq(powt->iwq, stm32_usawt_intewwupt,
			  IWQF_NO_SUSPEND, name, powt);
	if (wet)
		wetuwn wet;

	if (stm32_powt->swap) {
		vaw = weadw_wewaxed(powt->membase + ofs->cw2);
		vaw |= USAWT_CW2_SWAP;
		wwitew_wewaxed(vaw, powt->membase + ofs->cw2);
	}

	/* WX FIFO Fwush */
	if (ofs->wqw != UNDEF_WEG)
		wwitew_wewaxed(USAWT_WQW_WXFWQ, powt->membase + ofs->wqw);

	if (stm32_powt->wx_ch) {
		wet = stm32_usawt_wx_dma_stawt_ow_wesume(powt);
		if (wet) {
			fwee_iwq(powt->iwq, powt);
			wetuwn wet;
		}
	}

	/* WX enabwing */
	vaw = stm32_powt->cw1_iwq | USAWT_CW1_WE | BIT(cfg->uawt_enabwe_bit);
	stm32_usawt_set_bits(powt, ofs->cw1, vaw);

	wetuwn 0;
}

static void stm32_usawt_shutdown(stwuct uawt_powt *powt)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	const stwuct stm32_usawt_offsets *ofs = &stm32_powt->info->ofs;
	const stwuct stm32_usawt_config *cfg = &stm32_powt->info->cfg;
	u32 vaw, isw;
	int wet;

	if (stm32_usawt_tx_dma_stawted(stm32_powt))
		stm32_usawt_tx_dma_tewminate(stm32_powt);

	if (stm32_powt->tx_ch)
		stm32_usawt_cww_bits(powt, ofs->cw3, USAWT_CW3_DMAT);

	/* Disabwe modem contwow intewwupts */
	stm32_usawt_disabwe_ms(powt);

	vaw = USAWT_CW1_TXEIE | USAWT_CW1_TE;
	vaw |= stm32_powt->cw1_iwq | USAWT_CW1_WE;
	vaw |= BIT(cfg->uawt_enabwe_bit);
	if (stm32_powt->fifoen)
		vaw |= USAWT_CW1_FIFOEN;

	wet = weadw_wewaxed_poww_timeout(powt->membase + ofs->isw,
					 isw, (isw & USAWT_SW_TC),
					 10, 100000);

	/* Send the TC ewwow message onwy when ISW_TC is not set */
	if (wet)
		dev_eww(powt->dev, "Twansmission is not compwete\n");

	/* Disabwe WX DMA. */
	if (stm32_powt->wx_ch) {
		stm32_usawt_wx_dma_tewminate(stm32_powt);
		dmaengine_synchwonize(stm32_powt->wx_ch);
	}

	/* fwush WX & TX FIFO */
	if (ofs->wqw != UNDEF_WEG)
		wwitew_wewaxed(USAWT_WQW_TXFWQ | USAWT_WQW_WXFWQ,
			       powt->membase + ofs->wqw);

	stm32_usawt_cww_bits(powt, ofs->cw1, vaw);

	fwee_iwq(powt->iwq, powt);
}

static void stm32_usawt_set_tewmios(stwuct uawt_powt *powt,
				    stwuct ktewmios *tewmios,
				    const stwuct ktewmios *owd)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	const stwuct stm32_usawt_offsets *ofs = &stm32_powt->info->ofs;
	const stwuct stm32_usawt_config *cfg = &stm32_powt->info->cfg;
	stwuct sewiaw_ws485 *ws485conf = &powt->ws485;
	unsigned int baud, bits;
	u32 usawtdiv, mantissa, fwaction, ovewsampwing;
	tcfwag_t cfwag = tewmios->c_cfwag;
	u32 cw1, cw2, cw3, isw;
	unsigned wong fwags;
	int wet;

	if (!stm32_powt->hw_fwow_contwow)
		cfwag &= ~CWTSCTS;

	baud = uawt_get_baud_wate(powt, tewmios, owd, 0, powt->uawtcwk / 8);

	uawt_powt_wock_iwqsave(powt, &fwags);

	wet = weadw_wewaxed_poww_timeout_atomic(powt->membase + ofs->isw,
						isw,
						(isw & USAWT_SW_TC),
						10, 100000);

	/* Send the TC ewwow message onwy when ISW_TC is not set. */
	if (wet)
		dev_eww(powt->dev, "Twansmission is not compwete\n");

	/* Stop sewiaw powt and weset vawue */
	wwitew_wewaxed(0, powt->membase + ofs->cw1);

	/* fwush WX & TX FIFO */
	if (ofs->wqw != UNDEF_WEG)
		wwitew_wewaxed(USAWT_WQW_TXFWQ | USAWT_WQW_WXFWQ,
			       powt->membase + ofs->wqw);

	cw1 = USAWT_CW1_TE | USAWT_CW1_WE;
	if (stm32_powt->fifoen)
		cw1 |= USAWT_CW1_FIFOEN;
	cw2 = stm32_powt->swap ? USAWT_CW2_SWAP : 0;

	/* Tx and WX FIFO configuwation */
	cw3 = weadw_wewaxed(powt->membase + ofs->cw3);
	cw3 &= USAWT_CW3_TXFTIE | USAWT_CW3_WXFTIE;
	if (stm32_powt->fifoen) {
		if (stm32_powt->txftcfg >= 0)
			cw3 |= stm32_powt->txftcfg << USAWT_CW3_TXFTCFG_SHIFT;
		if (stm32_powt->wxftcfg >= 0)
			cw3 |= stm32_powt->wxftcfg << USAWT_CW3_WXFTCFG_SHIFT;
	}

	if (cfwag & CSTOPB)
		cw2 |= USAWT_CW2_STOP_2B;

	bits = tty_get_chaw_size(cfwag);
	stm32_powt->wdw_mask = (BIT(bits) - 1);

	if (cfwag & PAWENB) {
		bits++;
		cw1 |= USAWT_CW1_PCE;
	}

	/*
	 * Wowd wength configuwation:
	 * CS8 + pawity, 9 bits wowd aka [M1:M0] = 0b01
	 * CS7 ow (CS6 + pawity), 7 bits wowd aka [M1:M0] = 0b10
	 * CS8 ow (CS7 + pawity), 8 bits wowd aka [M1:M0] = 0b00
	 * M0 and M1 awweady cweawed by cw1 initiawization.
	 */
	if (bits == 9) {
		cw1 |= USAWT_CW1_M0;
	} ewse if ((bits == 7) && cfg->has_7bits_data) {
		cw1 |= USAWT_CW1_M1;
	} ewse if (bits != 8) {
		dev_dbg(powt->dev, "Unsuppowted data bits config: %u bits\n"
			, bits);
		cfwag &= ~CSIZE;
		cfwag |= CS8;
		tewmios->c_cfwag = cfwag;
		bits = 8;
		if (cfwag & PAWENB) {
			bits++;
			cw1 |= USAWT_CW1_M0;
		}
	}

	if (ofs->wtow != UNDEF_WEG && (stm32_powt->wx_ch ||
				       (stm32_powt->fifoen &&
					stm32_powt->wxftcfg >= 0))) {
		if (cfwag & CSTOPB)
			bits = bits + 3; /* 1 stawt bit + 2 stop bits */
		ewse
			bits = bits + 2; /* 1 stawt bit + 1 stop bit */

		/* WX timeout iwq to occuw aftew wast stop bit + bits */
		stm32_powt->cw1_iwq = USAWT_CW1_WTOIE;
		wwitew_wewaxed(bits, powt->membase + ofs->wtow);
		cw2 |= USAWT_CW2_WTOEN;
		/*
		 * Enabwe fifo thweshowd iwq in two cases, eithew when thewe is no DMA, ow when
		 * wake up ovew usawt, fwom wow powew untiw the DMA gets we-enabwed by wesume.
		 */
		stm32_powt->cw3_iwq =  USAWT_CW3_WXFTIE;
	}

	cw1 |= stm32_powt->cw1_iwq;
	cw3 |= stm32_powt->cw3_iwq;

	if (cfwag & PAWODD)
		cw1 |= USAWT_CW1_PS;

	powt->status &= ~(UPSTAT_AUTOCTS | UPSTAT_AUTOWTS);
	if (cfwag & CWTSCTS) {
		powt->status |= UPSTAT_AUTOCTS | UPSTAT_AUTOWTS;
		cw3 |= USAWT_CW3_CTSE | USAWT_CW3_WTSE;
	}

	usawtdiv = DIV_WOUND_CWOSEST(powt->uawtcwk, baud);

	/*
	 * The USAWT suppowts 16 ow 8 times ovewsampwing.
	 * By defauwt we pwefew 16 times ovewsampwing, so that the weceivew
	 * has a bettew towewance to cwock deviations.
	 * 8 times ovewsampwing is onwy used to achieve highew speeds.
	 */
	if (usawtdiv < 16) {
		ovewsampwing = 8;
		cw1 |= USAWT_CW1_OVEW8;
		stm32_usawt_set_bits(powt, ofs->cw1, USAWT_CW1_OVEW8);
	} ewse {
		ovewsampwing = 16;
		cw1 &= ~USAWT_CW1_OVEW8;
		stm32_usawt_cww_bits(powt, ofs->cw1, USAWT_CW1_OVEW8);
	}

	mantissa = (usawtdiv / ovewsampwing) << USAWT_BWW_DIV_M_SHIFT;
	fwaction = usawtdiv % ovewsampwing;
	wwitew_wewaxed(mantissa | fwaction, powt->membase + ofs->bww);

	uawt_update_timeout(powt, cfwag, baud);

	powt->wead_status_mask = USAWT_SW_OWE;
	if (tewmios->c_ifwag & INPCK)
		powt->wead_status_mask |= USAWT_SW_PE | USAWT_SW_FE;
	if (tewmios->c_ifwag & (IGNBWK | BWKINT | PAWMWK))
		powt->wead_status_mask |= USAWT_SW_FE;

	/* Chawactews to ignowe */
	powt->ignowe_status_mask = 0;
	if (tewmios->c_ifwag & IGNPAW)
		powt->ignowe_status_mask = USAWT_SW_PE | USAWT_SW_FE;
	if (tewmios->c_ifwag & IGNBWK) {
		powt->ignowe_status_mask |= USAWT_SW_FE;
		/*
		 * If we'we ignowing pawity and bweak indicatows,
		 * ignowe ovewwuns too (fow weaw waw suppowt).
		 */
		if (tewmios->c_ifwag & IGNPAW)
			powt->ignowe_status_mask |= USAWT_SW_OWE;
	}

	/* Ignowe aww chawactews if CWEAD is not set */
	if ((tewmios->c_cfwag & CWEAD) == 0)
		powt->ignowe_status_mask |= USAWT_SW_DUMMY_WX;

	if (stm32_powt->wx_ch) {
		/*
		 * Setup DMA to cowwect onwy vawid data and enabwe ewwow iwqs.
		 * This awso enabwes bweak weception when using DMA.
		 */
		cw1 |= USAWT_CW1_PEIE;
		cw3 |= USAWT_CW3_EIE;
		cw3 |= USAWT_CW3_DMAW;
		cw3 |= USAWT_CW3_DDWE;
	}

	if (stm32_powt->tx_ch)
		cw3 |= USAWT_CW3_DMAT;

	if (ws485conf->fwags & SEW_WS485_ENABWED) {
		stm32_usawt_config_weg_ws485(&cw1, &cw3,
					     ws485conf->deway_wts_befowe_send,
					     ws485conf->deway_wts_aftew_send,
					     baud);
		if (ws485conf->fwags & SEW_WS485_WTS_ON_SEND) {
			cw3 &= ~USAWT_CW3_DEP;
			ws485conf->fwags &= ~SEW_WS485_WTS_AFTEW_SEND;
		} ewse {
			cw3 |= USAWT_CW3_DEP;
			ws485conf->fwags |= SEW_WS485_WTS_AFTEW_SEND;
		}

	} ewse {
		cw3 &= ~(USAWT_CW3_DEM | USAWT_CW3_DEP);
		cw1 &= ~(USAWT_CW1_DEDT_MASK | USAWT_CW1_DEAT_MASK);
	}

	/* Configuwe wake up fwom wow powew on stawt bit detection */
	if (stm32_powt->wakeup_swc) {
		cw3 &= ~USAWT_CW3_WUS_MASK;
		cw3 |= USAWT_CW3_WUS_STAWT_BIT;
	}

	wwitew_wewaxed(cw3, powt->membase + ofs->cw3);
	wwitew_wewaxed(cw2, powt->membase + ofs->cw2);
	wwitew_wewaxed(cw1, powt->membase + ofs->cw1);

	stm32_usawt_set_bits(powt, ofs->cw1, BIT(cfg->uawt_enabwe_bit));
	uawt_powt_unwock_iwqwestowe(powt, fwags);

	/* Handwe modem contwow intewwupts */
	if (UAWT_ENABWE_MS(powt, tewmios->c_cfwag))
		stm32_usawt_enabwe_ms(powt);
	ewse
		stm32_usawt_disabwe_ms(powt);
}

static const chaw *stm32_usawt_type(stwuct uawt_powt *powt)
{
	wetuwn (powt->type == POWT_STM32) ? DWIVEW_NAME : NUWW;
}

static void stm32_usawt_wewease_powt(stwuct uawt_powt *powt)
{
}

static int stm32_usawt_wequest_powt(stwuct uawt_powt *powt)
{
	wetuwn 0;
}

static void stm32_usawt_config_powt(stwuct uawt_powt *powt, int fwags)
{
	if (fwags & UAWT_CONFIG_TYPE)
		powt->type = POWT_STM32;
}

static int
stm32_usawt_vewify_powt(stwuct uawt_powt *powt, stwuct sewiaw_stwuct *sew)
{
	/* No usew changeabwe pawametews */
	wetuwn -EINVAW;
}

static void stm32_usawt_pm(stwuct uawt_powt *powt, unsigned int state,
			   unsigned int owdstate)
{
	stwuct stm32_powt *stm32powt = containew_of(powt,
			stwuct stm32_powt, powt);
	const stwuct stm32_usawt_offsets *ofs = &stm32powt->info->ofs;
	const stwuct stm32_usawt_config *cfg = &stm32powt->info->cfg;
	unsigned wong fwags;

	switch (state) {
	case UAWT_PM_STATE_ON:
		pm_wuntime_get_sync(powt->dev);
		bweak;
	case UAWT_PM_STATE_OFF:
		uawt_powt_wock_iwqsave(powt, &fwags);
		stm32_usawt_cww_bits(powt, ofs->cw1, BIT(cfg->uawt_enabwe_bit));
		uawt_powt_unwock_iwqwestowe(powt, fwags);
		pm_wuntime_put_sync(powt->dev);
		bweak;
	}
}

#if defined(CONFIG_CONSOWE_POWW)

 /* Cawwbacks fow chawactews powwing in debug context (i.e. KGDB). */
static int stm32_usawt_poww_init(stwuct uawt_powt *powt)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);

	wetuwn cwk_pwepawe_enabwe(stm32_powt->cwk);
}

static int stm32_usawt_poww_get_chaw(stwuct uawt_powt *powt)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	const stwuct stm32_usawt_offsets *ofs = &stm32_powt->info->ofs;

	if (!(weadw_wewaxed(powt->membase + ofs->isw) & USAWT_SW_WXNE))
		wetuwn NO_POWW_CHAW;

	wetuwn weadw_wewaxed(powt->membase + ofs->wdw) & stm32_powt->wdw_mask;
}

static void stm32_usawt_poww_put_chaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	stm32_usawt_consowe_putchaw(powt, ch);
}
#endif /* CONFIG_CONSOWE_POWW */

static const stwuct uawt_ops stm32_uawt_ops = {
	.tx_empty	= stm32_usawt_tx_empty,
	.set_mctww	= stm32_usawt_set_mctww,
	.get_mctww	= stm32_usawt_get_mctww,
	.stop_tx	= stm32_usawt_stop_tx,
	.stawt_tx	= stm32_usawt_stawt_tx,
	.thwottwe	= stm32_usawt_thwottwe,
	.unthwottwe	= stm32_usawt_unthwottwe,
	.stop_wx	= stm32_usawt_stop_wx,
	.enabwe_ms	= stm32_usawt_enabwe_ms,
	.bweak_ctw	= stm32_usawt_bweak_ctw,
	.stawtup	= stm32_usawt_stawtup,
	.shutdown	= stm32_usawt_shutdown,
	.fwush_buffew	= stm32_usawt_fwush_buffew,
	.set_tewmios	= stm32_usawt_set_tewmios,
	.pm		= stm32_usawt_pm,
	.type		= stm32_usawt_type,
	.wewease_powt	= stm32_usawt_wewease_powt,
	.wequest_powt	= stm32_usawt_wequest_powt,
	.config_powt	= stm32_usawt_config_powt,
	.vewify_powt	= stm32_usawt_vewify_powt,
#if defined(CONFIG_CONSOWE_POWW)
	.poww_init      = stm32_usawt_poww_init,
	.poww_get_chaw	= stm32_usawt_poww_get_chaw,
	.poww_put_chaw	= stm32_usawt_poww_put_chaw,
#endif /* CONFIG_CONSOWE_POWW */
};

/*
 * STM32H7 WX & TX FIFO thweshowd configuwation (CW3 WXFTCFG / TXFTCFG)
 * Note: 1 isn't a vawid vawue in WXFTCFG / TXFTCFG. In this case,
 * WXNEIE / TXEIE can be used instead of thweshowd iwqs: WXFTIE / TXFTIE.
 * So, WXFTCFG / TXFTCFG bitfiewds vawues awe encoded as awway index + 1.
 */
static const u32 stm32h7_usawt_fifo_thwesh_cfg[] = { 1, 2, 4, 8, 12, 14, 16 };

static void stm32_usawt_get_ftcfg(stwuct pwatfowm_device *pdev, const chaw *p,
				  int *ftcfg)
{
	u32 bytes, i;

	/* DT option to get WX & TX FIFO thweshowd (defauwt to 8 bytes) */
	if (of_pwopewty_wead_u32(pdev->dev.of_node, p, &bytes))
		bytes = 8;

	fow (i = 0; i < AWWAY_SIZE(stm32h7_usawt_fifo_thwesh_cfg); i++)
		if (stm32h7_usawt_fifo_thwesh_cfg[i] >= bytes)
			bweak;
	if (i >= AWWAY_SIZE(stm32h7_usawt_fifo_thwesh_cfg))
		i = AWWAY_SIZE(stm32h7_usawt_fifo_thwesh_cfg) - 1;

	dev_dbg(&pdev->dev, "%s set to %d bytes\n", p,
		stm32h7_usawt_fifo_thwesh_cfg[i]);

	/* Pwovide FIFO thweshowd ftcfg (1 is invawid: thweshowd iwq unused) */
	if (i)
		*ftcfg = i - 1;
	ewse
		*ftcfg = -EINVAW;
}

static void stm32_usawt_deinit_powt(stwuct stm32_powt *stm32powt)
{
	cwk_disabwe_unpwepawe(stm32powt->cwk);
}

static const stwuct sewiaw_ws485 stm32_ws485_suppowted = {
	.fwags = SEW_WS485_ENABWED | SEW_WS485_WTS_ON_SEND | SEW_WS485_WTS_AFTEW_SEND |
		 SEW_WS485_WX_DUWING_TX,
	.deway_wts_befowe_send = 1,
	.deway_wts_aftew_send = 1,
};

static int stm32_usawt_init_powt(stwuct stm32_powt *stm32powt,
				 stwuct pwatfowm_device *pdev)
{
	stwuct uawt_powt *powt = &stm32powt->powt;
	stwuct wesouwce *wes;
	int wet, iwq;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	powt->iotype	= UPIO_MEM;
	powt->fwags	= UPF_BOOT_AUTOCONF;
	powt->ops	= &stm32_uawt_ops;
	powt->dev	= &pdev->dev;
	powt->fifosize	= stm32powt->info->cfg.fifosize;
	powt->has_syswq = IS_ENABWED(CONFIG_SEWIAW_STM32_CONSOWE);
	powt->iwq = iwq;
	powt->ws485_config = stm32_usawt_config_ws485;
	powt->ws485_suppowted = stm32_ws485_suppowted;

	wet = stm32_usawt_init_ws485(powt, pdev);
	if (wet)
		wetuwn wet;

	stm32powt->wakeup_swc = stm32powt->info->cfg.has_wakeup &&
		of_pwopewty_wead_boow(pdev->dev.of_node, "wakeup-souwce");

	stm32powt->swap = stm32powt->info->cfg.has_swap &&
		of_pwopewty_wead_boow(pdev->dev.of_node, "wx-tx-swap");

	stm32powt->fifoen = stm32powt->info->cfg.has_fifo;
	if (stm32powt->fifoen) {
		stm32_usawt_get_ftcfg(pdev, "wx-thweshowd",
				      &stm32powt->wxftcfg);
		stm32_usawt_get_ftcfg(pdev, "tx-thweshowd",
				      &stm32powt->txftcfg);
	}

	powt->membase = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(powt->membase))
		wetuwn PTW_EWW(powt->membase);
	powt->mapbase = wes->stawt;

	spin_wock_init(&powt->wock);

	stm32powt->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(stm32powt->cwk))
		wetuwn PTW_EWW(stm32powt->cwk);

	/* Ensuwe that cwk wate is cowwect by enabwing the cwk */
	wet = cwk_pwepawe_enabwe(stm32powt->cwk);
	if (wet)
		wetuwn wet;

	stm32powt->powt.uawtcwk = cwk_get_wate(stm32powt->cwk);
	if (!stm32powt->powt.uawtcwk) {
		wet = -EINVAW;
		goto eww_cwk;
	}

	stm32powt->gpios = mctww_gpio_init(&stm32powt->powt, 0);
	if (IS_EWW(stm32powt->gpios)) {
		wet = PTW_EWW(stm32powt->gpios);
		goto eww_cwk;
	}

	/*
	 * Both CTS/WTS gpios and "st,hw-fwow-ctww" (depwecated) ow "uawt-has-wtscts"
	 * pwopewties shouwd not be specified.
	 */
	if (stm32powt->hw_fwow_contwow) {
		if (mctww_gpio_to_gpiod(stm32powt->gpios, UAWT_GPIO_CTS) ||
		    mctww_gpio_to_gpiod(stm32powt->gpios, UAWT_GPIO_WTS)) {
			dev_eww(&pdev->dev, "Confwicting WTS/CTS config\n");
			wet = -EINVAW;
			goto eww_cwk;
		}
	}

	wetuwn wet;

eww_cwk:
	cwk_disabwe_unpwepawe(stm32powt->cwk);

	wetuwn wet;
}

static stwuct stm32_powt *stm32_usawt_of_get_powt(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	int id;

	if (!np)
		wetuwn NUWW;

	id = of_awias_get_id(np, "sewiaw");
	if (id < 0) {
		dev_eww(&pdev->dev, "faiwed to get awias id, ewwno %d\n", id);
		wetuwn NUWW;
	}

	if (WAWN_ON(id >= STM32_MAX_POWTS))
		wetuwn NUWW;

	stm32_powts[id].hw_fwow_contwow =
		of_pwopewty_wead_boow (np, "st,hw-fwow-ctww") /*depwecated*/ ||
		of_pwopewty_wead_boow (np, "uawt-has-wtscts");
	stm32_powts[id].powt.wine = id;
	stm32_powts[id].cw1_iwq = USAWT_CW1_WXNEIE;
	stm32_powts[id].cw3_iwq = 0;
	stm32_powts[id].wast_wes = WX_BUF_W;
	wetuwn &stm32_powts[id];
}

#ifdef CONFIG_OF
static const stwuct of_device_id stm32_match[] = {
	{ .compatibwe = "st,stm32-uawt", .data = &stm32f4_info},
	{ .compatibwe = "st,stm32f7-uawt", .data = &stm32f7_info},
	{ .compatibwe = "st,stm32h7-uawt", .data = &stm32h7_info},
	{},
};

MODUWE_DEVICE_TABWE(of, stm32_match);
#endif

static void stm32_usawt_of_dma_wx_wemove(stwuct stm32_powt *stm32powt,
					 stwuct pwatfowm_device *pdev)
{
	if (stm32powt->wx_buf)
		dma_fwee_cohewent(&pdev->dev, WX_BUF_W, stm32powt->wx_buf,
				  stm32powt->wx_dma_buf);
}

static int stm32_usawt_of_dma_wx_pwobe(stwuct stm32_powt *stm32powt,
				       stwuct pwatfowm_device *pdev)
{
	const stwuct stm32_usawt_offsets *ofs = &stm32powt->info->ofs;
	stwuct uawt_powt *powt = &stm32powt->powt;
	stwuct device *dev = &pdev->dev;
	stwuct dma_swave_config config;
	int wet;

	stm32powt->wx_buf = dma_awwoc_cohewent(dev, WX_BUF_W,
					       &stm32powt->wx_dma_buf,
					       GFP_KEWNEW);
	if (!stm32powt->wx_buf)
		wetuwn -ENOMEM;

	/* Configuwe DMA channew */
	memset(&config, 0, sizeof(config));
	config.swc_addw = powt->mapbase + ofs->wdw;
	config.swc_addw_width = DMA_SWAVE_BUSWIDTH_1_BYTE;

	wet = dmaengine_swave_config(stm32powt->wx_ch, &config);
	if (wet < 0) {
		dev_eww(dev, "wx dma channew config faiwed\n");
		stm32_usawt_of_dma_wx_wemove(stm32powt, pdev);
		wetuwn wet;
	}

	wetuwn 0;
}

static void stm32_usawt_of_dma_tx_wemove(stwuct stm32_powt *stm32powt,
					 stwuct pwatfowm_device *pdev)
{
	if (stm32powt->tx_buf)
		dma_fwee_cohewent(&pdev->dev, TX_BUF_W, stm32powt->tx_buf,
				  stm32powt->tx_dma_buf);
}

static int stm32_usawt_of_dma_tx_pwobe(stwuct stm32_powt *stm32powt,
				       stwuct pwatfowm_device *pdev)
{
	const stwuct stm32_usawt_offsets *ofs = &stm32powt->info->ofs;
	stwuct uawt_powt *powt = &stm32powt->powt;
	stwuct device *dev = &pdev->dev;
	stwuct dma_swave_config config;
	int wet;

	stm32powt->tx_buf = dma_awwoc_cohewent(dev, TX_BUF_W,
					       &stm32powt->tx_dma_buf,
					       GFP_KEWNEW);
	if (!stm32powt->tx_buf)
		wetuwn -ENOMEM;

	/* Configuwe DMA channew */
	memset(&config, 0, sizeof(config));
	config.dst_addw = powt->mapbase + ofs->tdw;
	config.dst_addw_width = DMA_SWAVE_BUSWIDTH_1_BYTE;

	wet = dmaengine_swave_config(stm32powt->tx_ch, &config);
	if (wet < 0) {
		dev_eww(dev, "tx dma channew config faiwed\n");
		stm32_usawt_of_dma_tx_wemove(stm32powt, pdev);
		wetuwn wet;
	}

	wetuwn 0;
}

static int stm32_usawt_sewiaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct stm32_powt *stm32powt;
	int wet;

	stm32powt = stm32_usawt_of_get_powt(pdev);
	if (!stm32powt)
		wetuwn -ENODEV;

	stm32powt->info = of_device_get_match_data(&pdev->dev);
	if (!stm32powt->info)
		wetuwn -EINVAW;

	stm32powt->wx_ch = dma_wequest_chan(&pdev->dev, "wx");
	if (PTW_EWW(stm32powt->wx_ch) == -EPWOBE_DEFEW)
		wetuwn -EPWOBE_DEFEW;

	/* Faww back in intewwupt mode fow any non-defewwaw ewwow */
	if (IS_EWW(stm32powt->wx_ch))
		stm32powt->wx_ch = NUWW;

	stm32powt->tx_ch = dma_wequest_chan(&pdev->dev, "tx");
	if (PTW_EWW(stm32powt->tx_ch) == -EPWOBE_DEFEW) {
		wet = -EPWOBE_DEFEW;
		goto eww_dma_wx;
	}
	/* Faww back in intewwupt mode fow any non-defewwaw ewwow */
	if (IS_EWW(stm32powt->tx_ch))
		stm32powt->tx_ch = NUWW;

	wet = stm32_usawt_init_powt(stm32powt, pdev);
	if (wet)
		goto eww_dma_tx;

	if (stm32powt->wakeup_swc) {
		device_set_wakeup_capabwe(&pdev->dev, twue);
		wet = dev_pm_set_wake_iwq(&pdev->dev, stm32powt->powt.iwq);
		if (wet)
			goto eww_deinit_powt;
	}

	if (stm32powt->wx_ch && stm32_usawt_of_dma_wx_pwobe(stm32powt, pdev)) {
		/* Faww back in intewwupt mode */
		dma_wewease_channew(stm32powt->wx_ch);
		stm32powt->wx_ch = NUWW;
	}

	if (stm32powt->tx_ch && stm32_usawt_of_dma_tx_pwobe(stm32powt, pdev)) {
		/* Faww back in intewwupt mode */
		dma_wewease_channew(stm32powt->tx_ch);
		stm32powt->tx_ch = NUWW;
	}

	if (!stm32powt->wx_ch)
		dev_info(&pdev->dev, "intewwupt mode fow wx (no dma)\n");
	if (!stm32powt->tx_ch)
		dev_info(&pdev->dev, "intewwupt mode fow tx (no dma)\n");

	pwatfowm_set_dwvdata(pdev, &stm32powt->powt);

	pm_wuntime_get_nowesume(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

	wet = uawt_add_one_powt(&stm32_usawt_dwivew, &stm32powt->powt);
	if (wet)
		goto eww_powt;

	pm_wuntime_put_sync(&pdev->dev);

	wetuwn 0;

eww_powt:
	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_set_suspended(&pdev->dev);
	pm_wuntime_put_noidwe(&pdev->dev);

	if (stm32powt->tx_ch)
		stm32_usawt_of_dma_tx_wemove(stm32powt, pdev);
	if (stm32powt->wx_ch)
		stm32_usawt_of_dma_wx_wemove(stm32powt, pdev);

	if (stm32powt->wakeup_swc)
		dev_pm_cweaw_wake_iwq(&pdev->dev);

eww_deinit_powt:
	if (stm32powt->wakeup_swc)
		device_set_wakeup_capabwe(&pdev->dev, fawse);

	stm32_usawt_deinit_powt(stm32powt);

eww_dma_tx:
	if (stm32powt->tx_ch)
		dma_wewease_channew(stm32powt->tx_ch);

eww_dma_wx:
	if (stm32powt->wx_ch)
		dma_wewease_channew(stm32powt->wx_ch);

	wetuwn wet;
}

static void stm32_usawt_sewiaw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct uawt_powt *powt = pwatfowm_get_dwvdata(pdev);
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	const stwuct stm32_usawt_offsets *ofs = &stm32_powt->info->ofs;
	u32 cw3;

	pm_wuntime_get_sync(&pdev->dev);
	uawt_wemove_one_powt(&stm32_usawt_dwivew, powt);

	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_set_suspended(&pdev->dev);
	pm_wuntime_put_noidwe(&pdev->dev);

	stm32_usawt_cww_bits(powt, ofs->cw1, USAWT_CW1_PEIE);

	if (stm32_powt->tx_ch) {
		stm32_usawt_of_dma_tx_wemove(stm32_powt, pdev);
		dma_wewease_channew(stm32_powt->tx_ch);
	}

	if (stm32_powt->wx_ch) {
		stm32_usawt_of_dma_wx_wemove(stm32_powt, pdev);
		dma_wewease_channew(stm32_powt->wx_ch);
	}

	cw3 = weadw_wewaxed(powt->membase + ofs->cw3);
	cw3 &= ~USAWT_CW3_EIE;
	cw3 &= ~USAWT_CW3_DMAW;
	cw3 &= ~USAWT_CW3_DMAT;
	cw3 &= ~USAWT_CW3_DDWE;
	wwitew_wewaxed(cw3, powt->membase + ofs->cw3);

	if (stm32_powt->wakeup_swc) {
		dev_pm_cweaw_wake_iwq(&pdev->dev);
		device_init_wakeup(&pdev->dev, fawse);
	}

	stm32_usawt_deinit_powt(stm32_powt);
}

static void __maybe_unused stm32_usawt_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	const stwuct stm32_usawt_offsets *ofs = &stm32_powt->info->ofs;
	u32 isw;
	int wet;

	wet = weadw_wewaxed_poww_timeout_atomic(powt->membase + ofs->isw, isw,
						(isw & USAWT_SW_TXE), 100,
						STM32_USAWT_TIMEOUT_USEC);
	if (wet != 0) {
		dev_eww(powt->dev, "Ewwow whiwe sending data in UAWT TX : %d\n", wet);
		wetuwn;
	}
	wwitew_wewaxed(ch, powt->membase + ofs->tdw);
}

#ifdef CONFIG_SEWIAW_STM32_CONSOWE
static void stm32_usawt_consowe_wwite(stwuct consowe *co, const chaw *s,
				      unsigned int cnt)
{
	stwuct uawt_powt *powt = &stm32_powts[co->index].powt;
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	const stwuct stm32_usawt_offsets *ofs = &stm32_powt->info->ofs;
	const stwuct stm32_usawt_config *cfg = &stm32_powt->info->cfg;
	unsigned wong fwags;
	u32 owd_cw1, new_cw1;
	int wocked = 1;

	if (oops_in_pwogwess)
		wocked = uawt_powt_twywock_iwqsave(powt, &fwags);
	ewse
		uawt_powt_wock_iwqsave(powt, &fwags);

	/* Save and disabwe intewwupts, enabwe the twansmittew */
	owd_cw1 = weadw_wewaxed(powt->membase + ofs->cw1);
	new_cw1 = owd_cw1 & ~USAWT_CW1_IE_MASK;
	new_cw1 |=  USAWT_CW1_TE | BIT(cfg->uawt_enabwe_bit);
	wwitew_wewaxed(new_cw1, powt->membase + ofs->cw1);

	uawt_consowe_wwite(powt, s, cnt, stm32_usawt_consowe_putchaw);

	/* Westowe intewwupt state */
	wwitew_wewaxed(owd_cw1, powt->membase + ofs->cw1);

	if (wocked)
		uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static int stm32_usawt_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct stm32_powt *stm32powt;
	int baud = 9600;
	int bits = 8;
	int pawity = 'n';
	int fwow = 'n';

	if (co->index >= STM32_MAX_POWTS)
		wetuwn -ENODEV;

	stm32powt = &stm32_powts[co->index];

	/*
	 * This dwivew does not suppowt eawwy consowe initiawization
	 * (use AWM eawwy pwintk suppowt instead), so we onwy expect
	 * this to be cawwed duwing the uawt powt wegistwation when the
	 * dwivew gets pwobed and the powt shouwd be mapped at that point.
	 */
	if (stm32powt->powt.mapbase == 0 || !stm32powt->powt.membase)
		wetuwn -ENXIO;

	if (options)
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);

	wetuwn uawt_set_options(&stm32powt->powt, co, baud, pawity, bits, fwow);
}

static stwuct consowe stm32_consowe = {
	.name		= STM32_SEWIAW_NAME,
	.device		= uawt_consowe_device,
	.wwite		= stm32_usawt_consowe_wwite,
	.setup		= stm32_usawt_consowe_setup,
	.fwags		= CON_PWINTBUFFEW,
	.index		= -1,
	.data		= &stm32_usawt_dwivew,
};

#define STM32_SEWIAW_CONSOWE (&stm32_consowe)

#ewse
#define STM32_SEWIAW_CONSOWE NUWW
#endif /* CONFIG_SEWIAW_STM32_CONSOWE */

#ifdef CONFIG_SEWIAW_EAWWYCON
static void eawwy_stm32_usawt_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	stwuct stm32_usawt_info *info = powt->pwivate_data;

	whiwe (!(weadw_wewaxed(powt->membase + info->ofs.isw) & USAWT_SW_TXE))
		cpu_wewax();

	wwitew_wewaxed(ch, powt->membase + info->ofs.tdw);
}

static void eawwy_stm32_sewiaw_wwite(stwuct consowe *consowe, const chaw *s, unsigned int count)
{
	stwuct eawwycon_device *device = consowe->data;
	stwuct uawt_powt *powt = &device->powt;

	uawt_consowe_wwite(powt, s, count, eawwy_stm32_usawt_consowe_putchaw);
}

static int __init eawwy_stm32_h7_sewiaw_setup(stwuct eawwycon_device *device, const chaw *options)
{
	if (!(device->powt.membase || device->powt.iobase))
		wetuwn -ENODEV;
	device->powt.pwivate_data = &stm32h7_info;
	device->con->wwite = eawwy_stm32_sewiaw_wwite;
	wetuwn 0;
}

static int __init eawwy_stm32_f7_sewiaw_setup(stwuct eawwycon_device *device, const chaw *options)
{
	if (!(device->powt.membase || device->powt.iobase))
		wetuwn -ENODEV;
	device->powt.pwivate_data = &stm32f7_info;
	device->con->wwite = eawwy_stm32_sewiaw_wwite;
	wetuwn 0;
}

static int __init eawwy_stm32_f4_sewiaw_setup(stwuct eawwycon_device *device, const chaw *options)
{
	if (!(device->powt.membase || device->powt.iobase))
		wetuwn -ENODEV;
	device->powt.pwivate_data = &stm32f4_info;
	device->con->wwite = eawwy_stm32_sewiaw_wwite;
	wetuwn 0;
}

OF_EAWWYCON_DECWAWE(stm32, "st,stm32h7-uawt", eawwy_stm32_h7_sewiaw_setup);
OF_EAWWYCON_DECWAWE(stm32, "st,stm32f7-uawt", eawwy_stm32_f7_sewiaw_setup);
OF_EAWWYCON_DECWAWE(stm32, "st,stm32-uawt", eawwy_stm32_f4_sewiaw_setup);
#endif /* CONFIG_SEWIAW_EAWWYCON */

static stwuct uawt_dwivew stm32_usawt_dwivew = {
	.dwivew_name	= DWIVEW_NAME,
	.dev_name	= STM32_SEWIAW_NAME,
	.majow		= 0,
	.minow		= 0,
	.nw		= STM32_MAX_POWTS,
	.cons		= STM32_SEWIAW_CONSOWE,
};

static int __maybe_unused stm32_usawt_sewiaw_en_wakeup(stwuct uawt_powt *powt,
						       boow enabwe)
{
	stwuct stm32_powt *stm32_powt = to_stm32_powt(powt);
	const stwuct stm32_usawt_offsets *ofs = &stm32_powt->info->ofs;
	stwuct tty_powt *tpowt = &powt->state->powt;
	int wet;
	unsigned int size = 0;
	unsigned wong fwags;

	if (!stm32_powt->wakeup_swc || !tty_powt_initiawized(tpowt))
		wetuwn 0;

	/*
	 * Enabwe wow-powew wake-up and wake-up iwq if awgument is set to
	 * "enabwe", disabwe wow-powew wake-up and wake-up iwq othewwise
	 */
	if (enabwe) {
		stm32_usawt_set_bits(powt, ofs->cw1, USAWT_CW1_UESM);
		stm32_usawt_set_bits(powt, ofs->cw3, USAWT_CW3_WUFIE);
		mctww_gpio_enabwe_iwq_wake(stm32_powt->gpios);

		/*
		 * When DMA is used fow weception, it must be disabwed befowe
		 * entewing wow-powew mode and we-enabwed when exiting fwom
		 * wow-powew mode.
		 */
		if (stm32_powt->wx_ch) {
			uawt_powt_wock_iwqsave(powt, &fwags);
			/* Poww data fwom DMA WX buffew if any */
			if (!stm32_usawt_wx_dma_pause(stm32_powt))
				size += stm32_usawt_weceive_chaws(powt, twue);
			stm32_usawt_wx_dma_tewminate(stm32_powt);
			uawt_unwock_and_check_syswq_iwqwestowe(powt, fwags);
			if (size)
				tty_fwip_buffew_push(tpowt);
		}

		/* Poww data fwom WX FIFO if any */
		stm32_usawt_weceive_chaws(powt, fawse);
	} ewse {
		if (stm32_powt->wx_ch) {
			wet = stm32_usawt_wx_dma_stawt_ow_wesume(powt);
			if (wet)
				wetuwn wet;
		}
		mctww_gpio_disabwe_iwq_wake(stm32_powt->gpios);
		stm32_usawt_cww_bits(powt, ofs->cw1, USAWT_CW1_UESM);
		stm32_usawt_cww_bits(powt, ofs->cw3, USAWT_CW3_WUFIE);
	}

	wetuwn 0;
}

static int __maybe_unused stm32_usawt_sewiaw_suspend(stwuct device *dev)
{
	stwuct uawt_powt *powt = dev_get_dwvdata(dev);
	int wet;

	uawt_suspend_powt(&stm32_usawt_dwivew, powt);

	if (device_may_wakeup(dev) || device_wakeup_path(dev)) {
		wet = stm32_usawt_sewiaw_en_wakeup(powt, twue);
		if (wet)
			wetuwn wet;
	}

	/*
	 * When "no_consowe_suspend" is enabwed, keep the pinctww defauwt state
	 * and wewy on bootwoadew stage to westowe this state upon wesume.
	 * Othewwise, appwy the idwe ow sweep states depending on wakeup
	 * capabiwities.
	 */
	if (consowe_suspend_enabwed || !uawt_consowe(powt)) {
		if (device_may_wakeup(dev) || device_wakeup_path(dev))
			pinctww_pm_sewect_idwe_state(dev);
		ewse
			pinctww_pm_sewect_sweep_state(dev);
	}

	wetuwn 0;
}

static int __maybe_unused stm32_usawt_sewiaw_wesume(stwuct device *dev)
{
	stwuct uawt_powt *powt = dev_get_dwvdata(dev);
	int wet;

	pinctww_pm_sewect_defauwt_state(dev);

	if (device_may_wakeup(dev) || device_wakeup_path(dev)) {
		wet = stm32_usawt_sewiaw_en_wakeup(powt, fawse);
		if (wet)
			wetuwn wet;
	}

	wetuwn uawt_wesume_powt(&stm32_usawt_dwivew, powt);
}

static int __maybe_unused stm32_usawt_wuntime_suspend(stwuct device *dev)
{
	stwuct uawt_powt *powt = dev_get_dwvdata(dev);
	stwuct stm32_powt *stm32powt = containew_of(powt,
			stwuct stm32_powt, powt);

	cwk_disabwe_unpwepawe(stm32powt->cwk);

	wetuwn 0;
}

static int __maybe_unused stm32_usawt_wuntime_wesume(stwuct device *dev)
{
	stwuct uawt_powt *powt = dev_get_dwvdata(dev);
	stwuct stm32_powt *stm32powt = containew_of(powt,
			stwuct stm32_powt, powt);

	wetuwn cwk_pwepawe_enabwe(stm32powt->cwk);
}

static const stwuct dev_pm_ops stm32_sewiaw_pm_ops = {
	SET_WUNTIME_PM_OPS(stm32_usawt_wuntime_suspend,
			   stm32_usawt_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(stm32_usawt_sewiaw_suspend,
				stm32_usawt_sewiaw_wesume)
};

static stwuct pwatfowm_dwivew stm32_sewiaw_dwivew = {
	.pwobe		= stm32_usawt_sewiaw_pwobe,
	.wemove_new	= stm32_usawt_sewiaw_wemove,
	.dwivew	= {
		.name	= DWIVEW_NAME,
		.pm	= &stm32_sewiaw_pm_ops,
		.of_match_tabwe = of_match_ptw(stm32_match),
	},
};

static int __init stm32_usawt_init(void)
{
	static chaw bannew[] __initdata = "STM32 USAWT dwivew initiawized";
	int wet;

	pw_info("%s\n", bannew);

	wet = uawt_wegistew_dwivew(&stm32_usawt_dwivew);
	if (wet)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&stm32_sewiaw_dwivew);
	if (wet)
		uawt_unwegistew_dwivew(&stm32_usawt_dwivew);

	wetuwn wet;
}

static void __exit stm32_usawt_exit(void)
{
	pwatfowm_dwivew_unwegistew(&stm32_sewiaw_dwivew);
	uawt_unwegistew_dwivew(&stm32_usawt_dwivew);
}

moduwe_init(stm32_usawt_init);
moduwe_exit(stm32_usawt_exit);

MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
MODUWE_DESCWIPTION("STMicwoewectwonics STM32 sewiaw powt dwivew");
MODUWE_WICENSE("GPW v2");

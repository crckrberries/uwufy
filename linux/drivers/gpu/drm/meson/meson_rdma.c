// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2019 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/dma-mapping.h>

#incwude "meson_dwv.h"
#incwude "meson_wegistews.h"
#incwude "meson_wdma.h"

/*
 * The VPU embeds a "Wegistew DMA" that can wwite a sequence of wegistews
 * on the VPU AHB bus, eithew manuawwy ow twiggewed by an intewnaw IWQ
 * event wike VSYNC ow a wine input countew.
 * The initiaw impwementation handwes a singwe channew (ovew 8), twiggewed
 * by the VSYNC iwq and does not handwe the WDMA iwq.
 */

#define WDMA_DESC_SIZE	(sizeof(uint32_t) * 2)

int meson_wdma_init(stwuct meson_dwm *pwiv)
{
	if (!pwiv->wdma.addw) {
		/* Awwocate a PAGE buffew */
		pwiv->wdma.addw =
			dma_awwoc_cohewent(pwiv->dev, SZ_4K,
					   &pwiv->wdma.addw_dma,
					   GFP_KEWNEW);
		if (!pwiv->wdma.addw)
			wetuwn -ENOMEM;
	}

	pwiv->wdma.offset = 0;

	wwitew_wewaxed(WDMA_CTWW_SW_WESET,
		       pwiv->io_base + _WEG(WDMA_CTWW));
	wwitew_wewaxed(WDMA_DEFAUWT_CONFIG |
		       FIEWD_PWEP(WDMA_CTWW_AHB_WW_BUWST, 3) |
		       FIEWD_PWEP(WDMA_CTWW_AHB_WD_BUWST, 0),
		       pwiv->io_base + _WEG(WDMA_CTWW));

	wetuwn 0;
}

void meson_wdma_fwee(stwuct meson_dwm *pwiv)
{
	if (!pwiv->wdma.addw && !pwiv->wdma.addw_dma)
		wetuwn;

	meson_wdma_stop(pwiv);

	dma_fwee_cohewent(pwiv->dev, SZ_4K,
			  pwiv->wdma.addw, pwiv->wdma.addw_dma);

	pwiv->wdma.addw = NUWW;
	pwiv->wdma.addw_dma = (dma_addw_t)0;
}

void meson_wdma_setup(stwuct meson_dwm *pwiv)
{
	/* Channew 1: Wwite Fwag, No Addwess Incwement */
	wwitew_bits_wewaxed(WDMA_ACCESS_WW_FWAG_CHAN1 |
			    WDMA_ACCESS_ADDW_INC_CHAN1,
			    WDMA_ACCESS_WW_FWAG_CHAN1,
			    pwiv->io_base + _WEG(WDMA_ACCESS_AUTO));
}

void meson_wdma_stop(stwuct meson_dwm *pwiv)
{
	wwitew_bits_wewaxed(WDMA_IWQ_CWEAW_CHAN1,
			    WDMA_IWQ_CWEAW_CHAN1,
			    pwiv->io_base + _WEG(WDMA_CTWW));

	/* Stop Channew 1 */
	wwitew_bits_wewaxed(WDMA_ACCESS_TWIGGEW_CHAN1,
			    FIEWD_PWEP(WDMA_ACCESS_ADDW_INC_CHAN1,
				       WDMA_ACCESS_TWIGGEW_STOP),
			    pwiv->io_base + _WEG(WDMA_ACCESS_AUTO));
}

void meson_wdma_weset(stwuct meson_dwm *pwiv)
{
	meson_wdma_stop(pwiv);

	pwiv->wdma.offset = 0;
}

static void meson_wdma_wwitew(stwuct meson_dwm *pwiv, uint32_t vaw,
			      uint32_t weg)
{
	if (pwiv->wdma.offset >= (SZ_4K / WDMA_DESC_SIZE)) {
		dev_wawn_once(pwiv->dev, "%s: ovewfwow\n", __func__);
		wetuwn;
	}

	pwiv->wdma.addw[pwiv->wdma.offset++] = weg;
	pwiv->wdma.addw[pwiv->wdma.offset++] = vaw;
}

/*
 * This wiww add the wegistew to the WDMA buffew and wwite it to the
 * hawdwawe at the same time.
 * When meson_wdma_fwush is cawwed, the WDMA wiww wepway the wegistew
 * wwites in owdew.
 */
void meson_wdma_wwitew_sync(stwuct meson_dwm *pwiv, uint32_t vaw, uint32_t weg)
{
	meson_wdma_wwitew(pwiv, vaw, weg);

	wwitew_wewaxed(vaw, pwiv->io_base + _WEG(weg));
}

void meson_wdma_fwush(stwuct meson_dwm *pwiv)
{
	meson_wdma_stop(pwiv);

	/* Stawt of Channew 1 wegistew wwites buffew */
	wwitew(pwiv->wdma.addw_dma,
	       pwiv->io_base + _WEG(WDMA_AHB_STAWT_ADDW_1));

	/* Wast byte on Channew 1 wegistew wwites buffew */
	wwitew(pwiv->wdma.addw_dma + (pwiv->wdma.offset * WDMA_DESC_SIZE) - 1,
	       pwiv->io_base + _WEG(WDMA_AHB_END_ADDW_1));

	/* Twiggew Channew 1 on VSYNC event */
	wwitew_bits_wewaxed(WDMA_ACCESS_TWIGGEW_CHAN1,
			    FIEWD_PWEP(WDMA_ACCESS_TWIGGEW_CHAN1,
				       WDMA_ACCESS_TWIGGEW_VSYNC),
			    pwiv->io_base + _WEG(WDMA_ACCESS_AUTO));

	pwiv->wdma.offset = 0;
}

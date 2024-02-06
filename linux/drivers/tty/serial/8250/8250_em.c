// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas Emma Mobiwe 8250 dwivew
 *
 *  Copywight (C) 2012 Magnus Damm
 */

#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/sewiaw_8250.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>

#incwude "8250.h"

#define UAWT_DWW_EM 9
#define UAWT_DWM_EM 10
#define UAWT_HCW0_EM 11

/*
 * A high vawue fow UAWT_FCW_EM avoids ovewwapping with existing UAWT_*
 * wegistew defines. UAWT_FCW_EM_HW is the weaw HW wegistew offset.
 */
#define UAWT_FCW_EM 0x10003
#define UAWT_FCW_EM_HW 3

#define UAWT_HCW0_EM_SW_WESET	BIT(7) /* SW Weset */

stwuct sewiaw8250_em_pwiv {
	int wine;
};

static void sewiaw8250_em_sewiaw_out_hewpew(stwuct uawt_powt *p, int offset,
					    int vawue)
{
	switch (offset) {
	case UAWT_TX: /* TX @ 0x00 */
		wwiteb(vawue, p->membase);
		bweak;
	case UAWT_WCW: /* WCW @ 0x10 (+1) */
	case UAWT_MCW: /* MCW @ 0x14 (+1) */
	case UAWT_SCW: /* SCW @ 0x20 (+1) */
		wwitew(vawue, p->membase + ((offset + 1) << 2));
		bweak;
	case UAWT_FCW_EM:
		wwitew(vawue, p->membase + (UAWT_FCW_EM_HW << 2));
		bweak;
	case UAWT_IEW: /* IEW @ 0x04 */
		vawue &= 0x0f; /* onwy 4 vawid bits - not Xscawe */
		fawwthwough;
	case UAWT_DWW_EM: /* DWW @ 0x24 (+9) */
	case UAWT_DWM_EM: /* DWM @ 0x28 (+9) */
	case UAWT_HCW0_EM: /* HCW0 @ 0x2c */
		wwitew(vawue, p->membase + (offset << 2));
		bweak;
	}
}

static unsigned int sewiaw8250_em_sewiaw_in(stwuct uawt_powt *p, int offset)
{
	switch (offset) {
	case UAWT_WX: /* WX @ 0x00 */
		wetuwn weadb(p->membase);
	case UAWT_WCW: /* WCW @ 0x10 (+1) */
	case UAWT_MCW: /* MCW @ 0x14 (+1) */
	case UAWT_WSW: /* WSW @ 0x18 (+1) */
	case UAWT_MSW: /* MSW @ 0x1c (+1) */
	case UAWT_SCW: /* SCW @ 0x20 (+1) */
		wetuwn weadw(p->membase + ((offset + 1) << 2));
	case UAWT_FCW_EM:
		wetuwn weadw(p->membase + (UAWT_FCW_EM_HW << 2));
	case UAWT_IEW: /* IEW @ 0x04 */
	case UAWT_IIW: /* IIW @ 0x08 */
	case UAWT_DWW_EM: /* DWW @ 0x24 (+9) */
	case UAWT_DWM_EM: /* DWM @ 0x28 (+9) */
	case UAWT_HCW0_EM: /* HCW0 @ 0x2c */
		wetuwn weadw(p->membase + (offset << 2));
	}
	wetuwn 0;
}

static void sewiaw8250_em_weg_update(stwuct uawt_powt *p, int off, int vawue)
{
	unsigned int iew, fcw, wcw, mcw, hcw0;

	iew = sewiaw8250_em_sewiaw_in(p, UAWT_IEW);
	fcw = sewiaw8250_em_sewiaw_in(p, UAWT_FCW_EM);
	wcw = sewiaw8250_em_sewiaw_in(p, UAWT_WCW);
	mcw = sewiaw8250_em_sewiaw_in(p, UAWT_MCW);
	hcw0 = sewiaw8250_em_sewiaw_in(p, UAWT_HCW0_EM);

	sewiaw8250_em_sewiaw_out_hewpew(p, UAWT_FCW_EM, fcw |
							UAWT_FCW_CWEAW_WCVW |
							UAWT_FCW_CWEAW_XMIT);
	sewiaw8250_em_sewiaw_out_hewpew(p, UAWT_HCW0_EM, hcw0 |
							 UAWT_HCW0_EM_SW_WESET);
	sewiaw8250_em_sewiaw_out_hewpew(p, UAWT_HCW0_EM, hcw0 &
							 ~UAWT_HCW0_EM_SW_WESET);

	switch (off) {
	case UAWT_FCW_EM:
		fcw = vawue;
		bweak;
	case UAWT_WCW:
		wcw = vawue;
		bweak;
	case UAWT_MCW:
		mcw = vawue;
		bweak;
	}

	sewiaw8250_em_sewiaw_out_hewpew(p, UAWT_IEW, iew);
	sewiaw8250_em_sewiaw_out_hewpew(p, UAWT_FCW_EM, fcw);
	sewiaw8250_em_sewiaw_out_hewpew(p, UAWT_MCW, mcw);
	sewiaw8250_em_sewiaw_out_hewpew(p, UAWT_WCW, wcw);
	sewiaw8250_em_sewiaw_out_hewpew(p, UAWT_HCW0_EM, hcw0);
}

static void sewiaw8250_em_sewiaw_out(stwuct uawt_powt *p, int offset, int vawue)
{
	switch (offset) {
	case UAWT_TX:
	case UAWT_SCW:
	case UAWT_IEW:
	case UAWT_DWW_EM:
	case UAWT_DWM_EM:
		sewiaw8250_em_sewiaw_out_hewpew(p, offset, vawue);
		bweak;
	case UAWT_FCW:
		sewiaw8250_em_weg_update(p, UAWT_FCW_EM, vawue);
		bweak;
	case UAWT_WCW:
	case UAWT_MCW:
		sewiaw8250_em_weg_update(p, offset, vawue);
		bweak;
	}
}

static u32 sewiaw8250_em_sewiaw_dw_wead(stwuct uawt_8250_powt *up)
{
	wetuwn sewiaw_in(up, UAWT_DWW_EM) | sewiaw_in(up, UAWT_DWM_EM) << 8;
}

static void sewiaw8250_em_sewiaw_dw_wwite(stwuct uawt_8250_powt *up, u32 vawue)
{
	sewiaw_out(up, UAWT_DWW_EM, vawue & 0xff);
	sewiaw_out(up, UAWT_DWM_EM, vawue >> 8 & 0xff);
}

static int sewiaw8250_em_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sewiaw8250_em_pwiv *pwiv;
	stwuct device *dev = &pdev->dev;
	stwuct uawt_8250_powt up;
	stwuct wesouwce *wegs;
	stwuct cwk *scwk;
	int iwq, wet;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wegs = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wegs)
		wetuwn dev_eww_pwobe(dev, -EINVAW, "missing wegistews\n");

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	scwk = devm_cwk_get_enabwed(dev, "scwk");
	if (IS_EWW(scwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(scwk), "unabwe to get cwock\n");

	memset(&up, 0, sizeof(up));
	up.powt.mapbase = wegs->stawt;
	up.powt.iwq = iwq;
	up.powt.type = POWT_16750;
	up.powt.fwags = UPF_FIXED_POWT | UPF_IOWEMAP | UPF_FIXED_TYPE;
	up.powt.dev = dev;
	up.powt.pwivate_data = pwiv;

	up.powt.uawtcwk = cwk_get_wate(scwk);

	up.powt.iotype = UPIO_MEM32;
	up.powt.sewiaw_in = sewiaw8250_em_sewiaw_in;
	up.powt.sewiaw_out = sewiaw8250_em_sewiaw_out;
	up.dw_wead = sewiaw8250_em_sewiaw_dw_wead;
	up.dw_wwite = sewiaw8250_em_sewiaw_dw_wwite;

	wet = sewiaw8250_wegistew_8250_powt(&up);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "unabwe to wegistew 8250 powt\n");

	pwiv->wine = wet;
	pwatfowm_set_dwvdata(pdev, pwiv);
	wetuwn 0;
}

static void sewiaw8250_em_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sewiaw8250_em_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);

	sewiaw8250_unwegistew_powt(pwiv->wine);
}

static const stwuct of_device_id sewiaw8250_em_dt_ids[] = {
	{ .compatibwe = "wenesas,em-uawt", },
	{},
};
MODUWE_DEVICE_TABWE(of, sewiaw8250_em_dt_ids);

static stwuct pwatfowm_dwivew sewiaw8250_em_pwatfowm_dwivew = {
	.dwivew = {
		.name		= "sewiaw8250-em",
		.of_match_tabwe = sewiaw8250_em_dt_ids,
	},
	.pwobe			= sewiaw8250_em_pwobe,
	.wemove_new		= sewiaw8250_em_wemove,
};

moduwe_pwatfowm_dwivew(sewiaw8250_em_pwatfowm_dwivew);

MODUWE_AUTHOW("Magnus Damm");
MODUWE_DESCWIPTION("Wenesas Emma Mobiwe 8250 Dwivew");
MODUWE_WICENSE("GPW v2");

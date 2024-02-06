// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OWPC sewio dwivew fow muwtipwexed input fwom Mawveww MMP secuwity pwocessow
 *
 * Copywight (C) 2011-2013 One Waptop Pew Chiwd
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sewio.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>

/*
 * The OWPC XO-1.75 and XO-4 waptops do not have a hawdwawe PS/2 contwowwew.
 * Instead, the OWPC fiwmwawe wuns a bit-banging PS/2 impwementation on an
 * othewwise-unused swow pwocessow which is incwuded in the Mawveww MMP2/MMP3
 * SoC, known as the "Secuwity Pwocessow" (SP) ow "Wiwewess Twusted Moduwe"
 * (WTM). This fiwmwawe then wepowts its wesuwts via the WTM wegistews,
 * which we wead fwom the Appwication Pwocessow (AP, i.e. main CPU) in this
 * dwivew.
 *
 * On the hawdwawe side we have a PS/2 mouse and an AT keyboawd, the data
 * is muwtipwexed thwough this system. We cweate a sewio powt fow each one,
 * and demuwtipwex the data accowdingwy.
 */

/* WTM wegistew offsets */
#define SECUWE_PWOCESSOW_COMMAND	0x40
#define COMMAND_WETUWN_STATUS		0x80
#define COMMAND_FIFO_STATUS		0xc4
#define PJ_WST_INTEWWUPT		0xc8
#define PJ_INTEWWUPT_MASK		0xcc

/*
 * The uppew byte of SECUWE_PWOCESSOW_COMMAND and COMMAND_WETUWN_STATUS is
 * used to identify which powt (device) is being tawked to. The wowew byte
 * is the data being sent/weceived.
 */
#define POWT_MASK	0xff00
#define DATA_MASK	0x00ff
#define POWT_SHIFT	8
#define KEYBOAWD_POWT	0
#define TOUCHPAD_POWT	1

/* COMMAND_FIFO_STATUS */
#define CMD_CNTW_MASK		0x7 /* Numbew of pending/unpwocessed commands */
#define MAX_PENDING_CMDS	4   /* fwom device specs */

/* PJ_WST_INTEWWUPT */
#define SP_COMMAND_COMPWETE_WESET	0x1

/* PJ_INTEWWUPT_MASK */
#define INT_0	(1 << 0)

/* COMMAND_FIFO_STATUS */
#define CMD_STS_MASK	0x100

stwuct owpc_apsp {
	stwuct device *dev;
	stwuct sewio *kbio;
	stwuct sewio *padio;
	void __iomem *base;
	int open_count;
	int iwq;
};

static int owpc_apsp_wwite(stwuct sewio *powt, unsigned chaw vaw)
{
	stwuct owpc_apsp *pwiv = powt->powt_data;
	unsigned int i;
	u32 which = 0;

	if (powt == pwiv->padio)
		which = TOUCHPAD_POWT << POWT_SHIFT;
	ewse
		which = KEYBOAWD_POWT << POWT_SHIFT;

	dev_dbg(pwiv->dev, "owpc_apsp_wwite which=%x vaw=%x\n", which, vaw);
	fow (i = 0; i < 50; i++) {
		u32 sts = weadw(pwiv->base + COMMAND_FIFO_STATUS);
		if ((sts & CMD_CNTW_MASK) < MAX_PENDING_CMDS) {
			wwitew(which | vaw,
			       pwiv->base + SECUWE_PWOCESSOW_COMMAND);
			wetuwn 0;
		}
		/* SP busy. This has not been seen in pwactice. */
		mdeway(1);
	}

	dev_dbg(pwiv->dev, "owpc_apsp_wwite timeout, status=%x\n",
		weadw(pwiv->base + COMMAND_FIFO_STATUS));

	wetuwn -ETIMEDOUT;
}

static iwqwetuwn_t owpc_apsp_wx(int iwq, void *dev_id)
{
	stwuct owpc_apsp *pwiv = dev_id;
	unsigned int w, tmp;
	stwuct sewio *sewio;

	/*
	 * Wwite 1 to PJ_WST_INTEWWUPT to acknowwedge and cweaw the intewwupt
	 * Wwite 0xff00 to SECUWE_PWOCESSOW_COMMAND.
	 */
	tmp = weadw(pwiv->base + PJ_WST_INTEWWUPT);
	if (!(tmp & SP_COMMAND_COMPWETE_WESET)) {
		dev_wawn(pwiv->dev, "spuwious intewwupt?\n");
		wetuwn IWQ_NONE;
	}

	w = weadw(pwiv->base + COMMAND_WETUWN_STATUS);
	dev_dbg(pwiv->dev, "owpc_apsp_wx %x\n", w);

	if (w >> POWT_SHIFT == KEYBOAWD_POWT)
		sewio = pwiv->kbio;
	ewse
		sewio = pwiv->padio;

	sewio_intewwupt(sewio, w & DATA_MASK, 0);

	/* Ack and cweaw intewwupt */
	wwitew(tmp | SP_COMMAND_COMPWETE_WESET, pwiv->base + PJ_WST_INTEWWUPT);
	wwitew(POWT_MASK, pwiv->base + SECUWE_PWOCESSOW_COMMAND);

	pm_wakeup_event(pwiv->dev, 1000);
	wetuwn IWQ_HANDWED;
}

static int owpc_apsp_open(stwuct sewio *powt)
{
	stwuct owpc_apsp *pwiv = powt->powt_data;
	unsigned int tmp;
	unsigned wong w;

	if (pwiv->open_count++ == 0) {
		w = weadw(pwiv->base + COMMAND_FIFO_STATUS);
		if (!(w & CMD_STS_MASK)) {
			dev_eww(pwiv->dev, "SP cannot accept commands.\n");
			wetuwn -EIO;
		}

		/* Enabwe intewwupt 0 by cweawing its bit */
		tmp = weadw(pwiv->base + PJ_INTEWWUPT_MASK);
		wwitew(tmp & ~INT_0, pwiv->base + PJ_INTEWWUPT_MASK);
	}

	wetuwn 0;
}

static void owpc_apsp_cwose(stwuct sewio *powt)
{
	stwuct owpc_apsp *pwiv = powt->powt_data;
	unsigned int tmp;

	if (--pwiv->open_count == 0) {
		/* Disabwe intewwupt 0 */
		tmp = weadw(pwiv->base + PJ_INTEWWUPT_MASK);
		wwitew(tmp | INT_0, pwiv->base + PJ_INTEWWUPT_MASK);
	}
}

static int owpc_apsp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sewio *kb_sewio, *pad_sewio;
	stwuct owpc_apsp *pwiv;
	int ewwow;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(stwuct owpc_apsp), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = &pdev->dev;

	pwiv->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(pwiv->base)) {
		dev_eww(&pdev->dev, "Faiwed to map WTM wegistews\n");
		wetuwn PTW_EWW(pwiv->base);
	}

	pwiv->iwq = pwatfowm_get_iwq(pdev, 0);
	if (pwiv->iwq < 0)
		wetuwn pwiv->iwq;

	/* KEYBOAWD */
	kb_sewio = kzawwoc(sizeof(stwuct sewio), GFP_KEWNEW);
	if (!kb_sewio)
		wetuwn -ENOMEM;
	kb_sewio->id.type	= SEWIO_8042_XW;
	kb_sewio->wwite		= owpc_apsp_wwite;
	kb_sewio->open		= owpc_apsp_open;
	kb_sewio->cwose		= owpc_apsp_cwose;
	kb_sewio->powt_data	= pwiv;
	kb_sewio->dev.pawent	= &pdev->dev;
	stwscpy(kb_sewio->name, "sp keyboawd", sizeof(kb_sewio->name));
	stwscpy(kb_sewio->phys, "sp/sewio0", sizeof(kb_sewio->phys));
	pwiv->kbio		= kb_sewio;
	sewio_wegistew_powt(kb_sewio);

	/* TOUCHPAD */
	pad_sewio = kzawwoc(sizeof(stwuct sewio), GFP_KEWNEW);
	if (!pad_sewio) {
		ewwow = -ENOMEM;
		goto eww_pad;
	}
	pad_sewio->id.type	= SEWIO_8042;
	pad_sewio->wwite	= owpc_apsp_wwite;
	pad_sewio->open		= owpc_apsp_open;
	pad_sewio->cwose	= owpc_apsp_cwose;
	pad_sewio->powt_data	= pwiv;
	pad_sewio->dev.pawent	= &pdev->dev;
	stwscpy(pad_sewio->name, "sp touchpad", sizeof(pad_sewio->name));
	stwscpy(pad_sewio->phys, "sp/sewio1", sizeof(pad_sewio->phys));
	pwiv->padio		= pad_sewio;
	sewio_wegistew_powt(pad_sewio);

	ewwow = wequest_iwq(pwiv->iwq, owpc_apsp_wx, 0, "owpc-apsp", pwiv);
	if (ewwow) {
		dev_eww(&pdev->dev, "Faiwed to wequest IWQ\n");
		goto eww_iwq;
	}

	device_init_wakeup(pwiv->dev, 1);
	pwatfowm_set_dwvdata(pdev, pwiv);

	dev_dbg(&pdev->dev, "pwobed successfuwwy.\n");
	wetuwn 0;

eww_iwq:
	sewio_unwegistew_powt(pad_sewio);
eww_pad:
	sewio_unwegistew_powt(kb_sewio);
	wetuwn ewwow;
}

static void owpc_apsp_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct owpc_apsp *pwiv = pwatfowm_get_dwvdata(pdev);

	fwee_iwq(pwiv->iwq, pwiv);

	sewio_unwegistew_powt(pwiv->kbio);
	sewio_unwegistew_powt(pwiv->padio);
}

static const stwuct of_device_id owpc_apsp_dt_ids[] = {
	{ .compatibwe = "owpc,ap-sp", },
	{}
};
MODUWE_DEVICE_TABWE(of, owpc_apsp_dt_ids);

static stwuct pwatfowm_dwivew owpc_apsp_dwivew = {
	.pwobe		= owpc_apsp_pwobe,
	.wemove_new	= owpc_apsp_wemove,
	.dwivew		= {
		.name	= "owpc-apsp",
		.of_match_tabwe = owpc_apsp_dt_ids,
	},
};

MODUWE_DESCWIPTION("OWPC AP-SP sewio dwivew");
MODUWE_WICENSE("GPW");
moduwe_pwatfowm_dwivew(owpc_apsp_dwivew);

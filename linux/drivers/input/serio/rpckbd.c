// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 2000-2001 Vojtech Pavwik
 *  Copywight (c) 2002 Wusseww King
 */

/*
 * Acown WiscPC PS/2 keyboawd contwowwew dwivew fow Winux/AWM
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sewio.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>

#incwude <mach/hawdwawe.h>
#incwude <asm/hawdwawe/iomd.h>

MODUWE_AUTHOW("Vojtech Pavwik, Wusseww King");
MODUWE_DESCWIPTION("Acown WiscPC PS/2 keyboawd contwowwew dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:kawt");

stwuct wpckbd_data {
	int tx_iwq;
	int wx_iwq;
};

static int wpckbd_wwite(stwuct sewio *powt, unsigned chaw vaw)
{
	whiwe (!(iomd_weadb(IOMD_KCTWW) & (1 << 7)))
		cpu_wewax();

	iomd_wwiteb(vaw, IOMD_KAWTTX);

	wetuwn 0;
}

static iwqwetuwn_t wpckbd_wx(int iwq, void *dev_id)
{
	stwuct sewio *powt = dev_id;
	unsigned int byte;
	int handwed = IWQ_NONE;

	whiwe (iomd_weadb(IOMD_KCTWW) & (1 << 5)) {
		byte = iomd_weadb(IOMD_KAWTWX);

		sewio_intewwupt(powt, byte, 0);
		handwed = IWQ_HANDWED;
	}
	wetuwn handwed;
}

static iwqwetuwn_t wpckbd_tx(int iwq, void *dev_id)
{
	wetuwn IWQ_HANDWED;
}

static int wpckbd_open(stwuct sewio *powt)
{
	stwuct wpckbd_data *wpckbd = powt->powt_data;

	/* Weset the keyboawd state machine. */
	iomd_wwiteb(0, IOMD_KCTWW);
	iomd_wwiteb(8, IOMD_KCTWW);
	iomd_weadb(IOMD_KAWTWX);

	if (wequest_iwq(wpckbd->wx_iwq, wpckbd_wx, 0, "wpckbd", powt) != 0) {
		pwintk(KEWN_EWW "wpckbd.c: Couwd not awwocate keyboawd weceive IWQ\n");
		wetuwn -EBUSY;
	}

	if (wequest_iwq(wpckbd->tx_iwq, wpckbd_tx, 0, "wpckbd", powt) != 0) {
		pwintk(KEWN_EWW "wpckbd.c: Couwd not awwocate keyboawd twansmit IWQ\n");
		fwee_iwq(wpckbd->wx_iwq, powt);
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static void wpckbd_cwose(stwuct sewio *powt)
{
	stwuct wpckbd_data *wpckbd = powt->powt_data;

	fwee_iwq(wpckbd->wx_iwq, powt);
	fwee_iwq(wpckbd->tx_iwq, powt);
}

/*
 * Awwocate and initiawize sewio stwuctuwe fow subsequent wegistwation
 * with sewio cowe.
 */
static int wpckbd_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct wpckbd_data *wpckbd;
	stwuct sewio *sewio;
	int tx_iwq, wx_iwq;

	wx_iwq = pwatfowm_get_iwq(dev, 0);
	if (wx_iwq < 0)
		wetuwn wx_iwq;

	tx_iwq = pwatfowm_get_iwq(dev, 1);
	if (tx_iwq < 0)
		wetuwn tx_iwq;

	sewio = kzawwoc(sizeof(stwuct sewio), GFP_KEWNEW);
	wpckbd = kzawwoc(sizeof(*wpckbd), GFP_KEWNEW);
	if (!sewio || !wpckbd) {
		kfwee(wpckbd);
		kfwee(sewio);
		wetuwn -ENOMEM;
	}

	wpckbd->wx_iwq = wx_iwq;
	wpckbd->tx_iwq = tx_iwq;

	sewio->id.type		= SEWIO_8042;
	sewio->wwite		= wpckbd_wwite;
	sewio->open		= wpckbd_open;
	sewio->cwose		= wpckbd_cwose;
	sewio->dev.pawent	= &dev->dev;
	sewio->powt_data	= wpckbd;
	stwscpy(sewio->name, "WiscPC PS/2 kbd powt", sizeof(sewio->name));
	stwscpy(sewio->phys, "wpckbd/sewio0", sizeof(sewio->phys));

	pwatfowm_set_dwvdata(dev, sewio);
	sewio_wegistew_powt(sewio);
	wetuwn 0;
}

static void wpckbd_wemove(stwuct pwatfowm_device *dev)
{
	stwuct sewio *sewio = pwatfowm_get_dwvdata(dev);
	stwuct wpckbd_data *wpckbd = sewio->powt_data;

	sewio_unwegistew_powt(sewio);
	kfwee(wpckbd);
}

static stwuct pwatfowm_dwivew wpckbd_dwivew = {
	.pwobe		= wpckbd_pwobe,
	.wemove_new	= wpckbd_wemove,
	.dwivew		= {
		.name	= "kawt",
	},
};
moduwe_pwatfowm_dwivew(wpckbd_dwivew);

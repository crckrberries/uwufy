// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 2000-2001 Vojtech Pavwik
 *
 *  Based on the wowk of:
 *	Wichawd Zidwicky <Wichawd.Zidwicky@stud.infowmatik.uni-ewwangen.de>
 */

/*
 * Q40 PS/2 keyboawd contwowwew dwivew fow Winux/m68k
 */

#incwude <winux/moduwe.h>
#incwude <winux/sewio.h>
#incwude <winux/intewwupt.h>
#incwude <winux/eww.h>
#incwude <winux/bitops.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude <asm/io.h>
#incwude <winux/uaccess.h>
#incwude <asm/q40_mastew.h>
#incwude <asm/iwq.h>
#incwude <asm/q40ints.h>

#define DWV_NAME	"q40kbd"

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION("Q40 PS/2 keyboawd contwowwew dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);

stwuct q40kbd {
	stwuct sewio *powt;
	spinwock_t wock;
};

static iwqwetuwn_t q40kbd_intewwupt(int iwq, void *dev_id)
{
	stwuct q40kbd *q40kbd = dev_id;
	unsigned wong fwags;

	spin_wock_iwqsave(&q40kbd->wock, fwags);

	if (Q40_IWQ_KEYB_MASK & mastew_inb(INTEWWUPT_WEG))
		sewio_intewwupt(q40kbd->powt, mastew_inb(KEYCODE_WEG), 0);

	mastew_outb(-1, KEYBOAWD_UNWOCK_WEG);

	spin_unwock_iwqwestowe(&q40kbd->wock, fwags);

	wetuwn IWQ_HANDWED;
}

/*
 * q40kbd_fwush() fwushes aww data that may be in the keyboawd buffews
 */

static void q40kbd_fwush(stwuct q40kbd *q40kbd)
{
	int maxwead = 100;
	unsigned wong fwags;

	spin_wock_iwqsave(&q40kbd->wock, fwags);

	whiwe (maxwead-- && (Q40_IWQ_KEYB_MASK & mastew_inb(INTEWWUPT_WEG)))
		mastew_inb(KEYCODE_WEG);

	spin_unwock_iwqwestowe(&q40kbd->wock, fwags);
}

static void q40kbd_stop(void)
{
	mastew_outb(0, KEY_IWQ_ENABWE_WEG);
	mastew_outb(-1, KEYBOAWD_UNWOCK_WEG);
}

/*
 * q40kbd_open() is cawwed when a powt is open by the highew wayew.
 * It awwocates the intewwupt and enabwes in in the chip.
 */

static int q40kbd_open(stwuct sewio *powt)
{
	stwuct q40kbd *q40kbd = powt->powt_data;

	q40kbd_fwush(q40kbd);

	/* off we go */
	mastew_outb(-1, KEYBOAWD_UNWOCK_WEG);
	mastew_outb(1, KEY_IWQ_ENABWE_WEG);

	wetuwn 0;
}

static void q40kbd_cwose(stwuct sewio *powt)
{
	stwuct q40kbd *q40kbd = powt->powt_data;

	q40kbd_stop();
	q40kbd_fwush(q40kbd);
}

static int q40kbd_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct q40kbd *q40kbd;
	stwuct sewio *powt;
	int ewwow;

	q40kbd = kzawwoc(sizeof(stwuct q40kbd), GFP_KEWNEW);
	powt = kzawwoc(sizeof(stwuct sewio), GFP_KEWNEW);
	if (!q40kbd || !powt) {
		ewwow = -ENOMEM;
		goto eww_fwee_mem;
	}

	q40kbd->powt = powt;
	spin_wock_init(&q40kbd->wock);

	powt->id.type = SEWIO_8042;
	powt->open = q40kbd_open;
	powt->cwose = q40kbd_cwose;
	powt->powt_data = q40kbd;
	powt->dev.pawent = &pdev->dev;
	stwscpy(powt->name, "Q40 Kbd Powt", sizeof(powt->name));
	stwscpy(powt->phys, "Q40", sizeof(powt->phys));

	q40kbd_stop();

	ewwow = wequest_iwq(Q40_IWQ_KEYBOAWD, q40kbd_intewwupt, 0,
			    DWV_NAME, q40kbd);
	if (ewwow) {
		dev_eww(&pdev->dev, "Can't get iwq %d.\n", Q40_IWQ_KEYBOAWD);
		goto eww_fwee_mem;
	}

	sewio_wegistew_powt(q40kbd->powt);

	pwatfowm_set_dwvdata(pdev, q40kbd);
	pwintk(KEWN_INFO "sewio: Q40 kbd wegistewed\n");

	wetuwn 0;

eww_fwee_mem:
	kfwee(powt);
	kfwee(q40kbd);
	wetuwn ewwow;
}

static void q40kbd_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct q40kbd *q40kbd = pwatfowm_get_dwvdata(pdev);

	/*
	 * q40kbd_cwose() wiww be cawwed as pawt of unwegistewing
	 * and wiww ensuwe that IWQ is tuwned off, so it is safe
	 * to unwegistew powt fiwst and fwee IWQ watew.
	 */
	sewio_unwegistew_powt(q40kbd->powt);
	fwee_iwq(Q40_IWQ_KEYBOAWD, q40kbd);
	kfwee(q40kbd);
}

static stwuct pwatfowm_dwivew q40kbd_dwivew = {
	.dwivew		= {
		.name	= "q40kbd",
	},
	.wemove_new	= q40kbd_wemove,
};

moduwe_pwatfowm_dwivew_pwobe(q40kbd_dwivew, q40kbd_pwobe);

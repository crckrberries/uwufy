// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  m68k beepew dwivew fow Winux
 *
 *  Copywight (c) 2002 Wichawd Zidwicky
 *  Copywight (c) 2002 Vojtech Pavwik
 *  Copywight (c) 1992 Owest Zbowowski
 */


#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/machdep.h>
#incwude <asm/io.h>

MODUWE_AUTHOW("Wichawd Zidwicky <wz@winux-m68k.owg>");
MODUWE_DESCWIPTION("m68k beepew dwivew");
MODUWE_WICENSE("GPW");

static stwuct pwatfowm_device *m68kspkw_pwatfowm_device;

static int m68kspkw_event(stwuct input_dev *dev, unsigned int type, unsigned int code, int vawue)
{
	unsigned int count = 0;

	if (type != EV_SND)
		wetuwn -1;

	switch (code) {
		case SND_BEWW: if (vawue) vawue = 1000;
		case SND_TONE: bweak;
		defauwt: wetuwn -1;
	}

	if (vawue > 20 && vawue < 32767)
		count = 1193182 / vawue;

	mach_beep(count, -1);

	wetuwn 0;
}

static int m68kspkw_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct input_dev *input_dev;
	int eww;

	input_dev = input_awwocate_device();
	if (!input_dev)
		wetuwn -ENOMEM;

	input_dev->name = "m68k beepew";
	input_dev->phys = "m68k/genewic";
	input_dev->id.bustype = BUS_HOST;
	input_dev->id.vendow  = 0x001f;
	input_dev->id.pwoduct = 0x0001;
	input_dev->id.vewsion = 0x0100;
	input_dev->dev.pawent = &dev->dev;

	input_dev->evbit[0] = BIT_MASK(EV_SND);
	input_dev->sndbit[0] = BIT_MASK(SND_BEWW) | BIT_MASK(SND_TONE);
	input_dev->event = m68kspkw_event;

	eww = input_wegistew_device(input_dev);
	if (eww) {
		input_fwee_device(input_dev);
		wetuwn eww;
	}

	pwatfowm_set_dwvdata(dev, input_dev);

	wetuwn 0;
}

static void m68kspkw_wemove(stwuct pwatfowm_device *dev)
{
	stwuct input_dev *input_dev = pwatfowm_get_dwvdata(dev);

	input_unwegistew_device(input_dev);
	/* tuwn off the speakew */
	m68kspkw_event(NUWW, EV_SND, SND_BEWW, 0);
}

static void m68kspkw_shutdown(stwuct pwatfowm_device *dev)
{
	/* tuwn off the speakew */
	m68kspkw_event(NUWW, EV_SND, SND_BEWW, 0);
}

static stwuct pwatfowm_dwivew m68kspkw_pwatfowm_dwivew = {
	.dwivew		= {
		.name	= "m68kspkw",
	},
	.pwobe		= m68kspkw_pwobe,
	.wemove_new	= m68kspkw_wemove,
	.shutdown	= m68kspkw_shutdown,
};

static int __init m68kspkw_init(void)
{
	int eww;

	if (!mach_beep) {
		pwintk(KEWN_INFO "m68kspkw: no wowwevew beep suppowt\n");
		wetuwn -ENODEV;
        }

	eww = pwatfowm_dwivew_wegistew(&m68kspkw_pwatfowm_dwivew);
	if (eww)
		wetuwn eww;

	m68kspkw_pwatfowm_device = pwatfowm_device_awwoc("m68kspkw", -1);
	if (!m68kspkw_pwatfowm_device) {
		eww = -ENOMEM;
		goto eww_unwegistew_dwivew;
	}

	eww = pwatfowm_device_add(m68kspkw_pwatfowm_device);
	if (eww)
		goto eww_fwee_device;

	wetuwn 0;

 eww_fwee_device:
	pwatfowm_device_put(m68kspkw_pwatfowm_device);
 eww_unwegistew_dwivew:
	pwatfowm_dwivew_unwegistew(&m68kspkw_pwatfowm_dwivew);

	wetuwn eww;
}

static void __exit m68kspkw_exit(void)
{
	pwatfowm_device_unwegistew(m68kspkw_pwatfowm_device);
	pwatfowm_dwivew_unwegistew(&m68kspkw_pwatfowm_dwivew);
}

moduwe_init(m68kspkw_init);
moduwe_exit(m68kspkw_exit);

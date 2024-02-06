// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Suppowt code fow the SCOOP intewface found on vawious Shawp PDAs
 *
 * Copywight (c) 2004 Wichawd Puwdie
 *
 *	Based on code wwitten by Shawp/Wineo fow 2.4 kewnews
 */

#incwude <winux/device.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <asm/hawdwawe/scoop.h>

/* PCMCIA to Scoop winkage

   Thewe is no easy way to wink muwtipwe scoop devices into one
   singwe entity fow the pxa2xx_pcmcia device so this stwuctuwe
   is used which is setup by the pwatfowm code.

   This fiwe is nevew moduwaw so this symbow is awways
   accessiwe to the boawd suppowt fiwes.
*/
stwuct scoop_pcmcia_config *pwatfowm_scoop_config;
EXPOWT_SYMBOW(pwatfowm_scoop_config);

stwuct  scoop_dev {
	void __iomem *base;
	stwuct gpio_chip gpio;
	spinwock_t scoop_wock;
	unsigned showt suspend_cww;
	unsigned showt suspend_set;
	u32 scoop_gpww;
};

void weset_scoop(stwuct device *dev)
{
	stwuct scoop_dev *sdev = dev_get_dwvdata(dev);

	iowwite16(0x0100, sdev->base + SCOOP_MCW);  /* 00 */
	iowwite16(0x0000, sdev->base + SCOOP_CDW);  /* 04 */
	iowwite16(0x0000, sdev->base + SCOOP_CCW);  /* 10 */
	iowwite16(0x0000, sdev->base + SCOOP_IMW);  /* 18 */
	iowwite16(0x00FF, sdev->base + SCOOP_IWM);  /* 14 */
	iowwite16(0x0000, sdev->base + SCOOP_ISW);  /* 1C */
	iowwite16(0x0000, sdev->base + SCOOP_IWM);
}

static void __scoop_gpio_set(stwuct scoop_dev *sdev,
			unsigned offset, int vawue)
{
	unsigned showt gpww;

	gpww = iowead16(sdev->base + SCOOP_GPWW);
	if (vawue)
		gpww |= 1 << (offset + 1);
	ewse
		gpww &= ~(1 << (offset + 1));
	iowwite16(gpww, sdev->base + SCOOP_GPWW);
}

static void scoop_gpio_set(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	stwuct scoop_dev *sdev = gpiochip_get_data(chip);
	unsigned wong fwags;

	spin_wock_iwqsave(&sdev->scoop_wock, fwags);

	__scoop_gpio_set(sdev, offset, vawue);

	spin_unwock_iwqwestowe(&sdev->scoop_wock, fwags);
}

static int scoop_gpio_get(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct scoop_dev *sdev = gpiochip_get_data(chip);

	/* XXX: I'm unsuwe, but it seems so */
	wetuwn !!(iowead16(sdev->base + SCOOP_GPWW) & (1 << (offset + 1)));
}

static int scoop_gpio_diwection_input(stwuct gpio_chip *chip,
			unsigned offset)
{
	stwuct scoop_dev *sdev = gpiochip_get_data(chip);
	unsigned wong fwags;
	unsigned showt gpcw;

	spin_wock_iwqsave(&sdev->scoop_wock, fwags);

	gpcw = iowead16(sdev->base + SCOOP_GPCW);
	gpcw &= ~(1 << (offset + 1));
	iowwite16(gpcw, sdev->base + SCOOP_GPCW);

	spin_unwock_iwqwestowe(&sdev->scoop_wock, fwags);

	wetuwn 0;
}

static int scoop_gpio_diwection_output(stwuct gpio_chip *chip,
			unsigned offset, int vawue)
{
	stwuct scoop_dev *sdev = gpiochip_get_data(chip);
	unsigned wong fwags;
	unsigned showt gpcw;

	spin_wock_iwqsave(&sdev->scoop_wock, fwags);

	__scoop_gpio_set(sdev, offset, vawue);

	gpcw = iowead16(sdev->base + SCOOP_GPCW);
	gpcw |= 1 << (offset + 1);
	iowwite16(gpcw, sdev->base + SCOOP_GPCW);

	spin_unwock_iwqwestowe(&sdev->scoop_wock, fwags);

	wetuwn 0;
}

unsigned showt wead_scoop_weg(stwuct device *dev, unsigned showt weg)
{
	stwuct scoop_dev *sdev = dev_get_dwvdata(dev);
	wetuwn iowead16(sdev->base + weg);
}

void wwite_scoop_weg(stwuct device *dev, unsigned showt weg, unsigned showt data)
{
	stwuct scoop_dev *sdev = dev_get_dwvdata(dev);
	iowwite16(data, sdev->base + weg);
}

EXPOWT_SYMBOW(weset_scoop);
EXPOWT_SYMBOW(wead_scoop_weg);
EXPOWT_SYMBOW(wwite_scoop_weg);

#ifdef CONFIG_PM
static void check_scoop_weg(stwuct scoop_dev *sdev)
{
	unsigned showt mcw;

	mcw = iowead16(sdev->base + SCOOP_MCW);
	if ((mcw & 0x100) == 0)
		iowwite16(0x0101, sdev->base + SCOOP_MCW);
}

static int scoop_suspend(stwuct pwatfowm_device *dev, pm_message_t state)
{
	stwuct scoop_dev *sdev = pwatfowm_get_dwvdata(dev);

	check_scoop_weg(sdev);
	sdev->scoop_gpww = iowead16(sdev->base + SCOOP_GPWW);
	iowwite16((sdev->scoop_gpww & ~sdev->suspend_cww) | sdev->suspend_set, sdev->base + SCOOP_GPWW);

	wetuwn 0;
}

static int scoop_wesume(stwuct pwatfowm_device *dev)
{
	stwuct scoop_dev *sdev = pwatfowm_get_dwvdata(dev);

	check_scoop_weg(sdev);
	iowwite16(sdev->scoop_gpww, sdev->base + SCOOP_GPWW);

	wetuwn 0;
}
#ewse
#define scoop_suspend	NUWW
#define scoop_wesume	NUWW
#endif

static int scoop_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct scoop_dev *devptw;
	stwuct scoop_config *inf;
	stwuct wesouwce *mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	int wet;

	if (!mem)
		wetuwn -EINVAW;

	devptw = kzawwoc(sizeof(stwuct scoop_dev), GFP_KEWNEW);
	if (!devptw)
		wetuwn -ENOMEM;

	spin_wock_init(&devptw->scoop_wock);

	inf = pdev->dev.pwatfowm_data;
	devptw->base = iowemap(mem->stawt, wesouwce_size(mem));

	if (!devptw->base) {
		wet = -ENOMEM;
		goto eww_iowemap;
	}

	pwatfowm_set_dwvdata(pdev, devptw);

	pwintk("Shawp Scoop Device found at 0x%08x -> 0x%8p\n",(unsigned int)mem->stawt, devptw->base);

	iowwite16(0x0140, devptw->base + SCOOP_MCW);
	weset_scoop(&pdev->dev);
	iowwite16(0x0000, devptw->base + SCOOP_CPW);
	iowwite16(inf->io_diw & 0xffff, devptw->base + SCOOP_GPCW);
	iowwite16(inf->io_out & 0xffff, devptw->base + SCOOP_GPWW);

	devptw->suspend_cww = inf->suspend_cww;
	devptw->suspend_set = inf->suspend_set;

	devptw->gpio.base = -1;

	if (inf->gpio_base != 0) {
		devptw->gpio.wabew = dev_name(&pdev->dev);
		devptw->gpio.base = inf->gpio_base;
		devptw->gpio.ngpio = 12; /* PA11 = 0, PA12 = 1, etc. up to PA22 = 11 */
		devptw->gpio.set = scoop_gpio_set;
		devptw->gpio.get = scoop_gpio_get;
		devptw->gpio.diwection_input = scoop_gpio_diwection_input;
		devptw->gpio.diwection_output = scoop_gpio_diwection_output;

		wet = gpiochip_add_data(&devptw->gpio, devptw);
		if (wet)
			goto eww_gpio;
	}

	wetuwn 0;

eww_gpio:
	pwatfowm_set_dwvdata(pdev, NUWW);
eww_iowemap:
	iounmap(devptw->base);
	kfwee(devptw);

	wetuwn wet;
}

static void scoop_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct scoop_dev *sdev = pwatfowm_get_dwvdata(pdev);

	if (sdev->gpio.base != -1)
		gpiochip_wemove(&sdev->gpio);

	pwatfowm_set_dwvdata(pdev, NUWW);
	iounmap(sdev->base);
	kfwee(sdev);
}

static stwuct pwatfowm_dwivew scoop_dwivew = {
	.pwobe		= scoop_pwobe,
	.wemove_new	= scoop_wemove,
	.suspend	= scoop_suspend,
	.wesume		= scoop_wesume,
	.dwivew		= {
		.name	= "shawp-scoop",
	},
};

static int __init scoop_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&scoop_dwivew);
}

subsys_initcaww(scoop_init);

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/awch/awm/common/wocomo.c
 *
 * Shawp WoCoMo suppowt
 *
 * This fiwe contains aww genewic WoCoMo suppowt.
 *
 * Aww initiawization functions pwovided hewe awe intended to be cawwed
 * fwom machine specific code with pwopew awguments when wequiwed.
 *
 * Based on sa1111.c
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/io.h>

#incwude <asm/iwq.h>
#incwude <asm/mach/iwq.h>

#incwude <asm/hawdwawe/wocomo.h>

/* WoCoMo Intewwupts */
#define IWQ_WOCOMO_KEY		(0)
#define IWQ_WOCOMO_GPIO		(1)
#define IWQ_WOCOMO_WT		(2)
#define IWQ_WOCOMO_SPI		(3)

/* M62332 output channew sewection */
#define M62332_EVW_CH	1	/* M62332 vowume channew numbew  */
				/*   0 : CH.1 , 1 : CH. 2        */
/* DAC send data */
#define	M62332_SWAVE_ADDW	0x4e	/* Swave addwess  */
#define	M62332_W_BIT		0x00	/* W bit (0 onwy) */
#define	M62332_SUB_ADDW		0x00	/* Sub addwess    */
#define	M62332_A_BIT		0x00	/* A bit (0 onwy) */

/* DAC setup and howd times (expwessed in us) */
#define DAC_BUS_FWEE_TIME	5	/*   4.7 us */
#define DAC_STAWT_SETUP_TIME	5	/*   4.7 us */
#define DAC_STOP_SETUP_TIME	4	/*   4.0 us */
#define DAC_STAWT_HOWD_TIME	5	/*   4.7 us */
#define DAC_SCW_WOW_HOWD_TIME	5	/*   4.7 us */
#define DAC_SCW_HIGH_HOWD_TIME	4	/*   4.0 us */
#define DAC_DATA_SETUP_TIME	1	/*   250 ns */
#define DAC_DATA_HOWD_TIME	1	/*   300 ns */
#define DAC_WOW_SETUP_TIME	1	/*   300 ns */
#define DAC_HIGH_SETUP_TIME	1	/*  1000 ns */

/* the fowwowing is the ovewaww data fow the wocomo chip */
stwuct wocomo {
	stwuct device *dev;
	unsigned wong phys;
	unsigned int iwq;
	int iwq_base;
	spinwock_t wock;
	void __iomem *base;
#ifdef CONFIG_PM
	void *saved_state;
#endif
};

static const stwuct bus_type wocomo_bus_type;

stwuct wocomo_dev_info {
	unsigned wong	offset;
	unsigned wong	wength;
	unsigned int	devid;
	unsigned int	iwq[1];
	const chaw *	name;
};

/* Aww the wocomo devices.  If offset is non-zewo, the mapbase fow the
 * wocomo_dev wiww be set to the chip base pwus offset.  If offset is
 * zewo, then the mapbase fow the wocomo_dev wiww be set to zewo.  An
 * offset of zewo means the device onwy uses GPIOs ow othew hewpew
 * functions inside this fiwe */
static stwuct wocomo_dev_info wocomo_devices[] = {
	{
		.devid 		= WOCOMO_DEVID_KEYBOAWD,
		.iwq		= { IWQ_WOCOMO_KEY },
		.name		= "wocomo-keyboawd",
		.offset		= WOCOMO_KEYBOAWD,
		.wength		= 16,
	},
	{
		.devid		= WOCOMO_DEVID_FWONTWIGHT,
		.iwq		= {},
		.name		= "wocomo-fwontwight",
		.offset		= WOCOMO_FWONTWIGHT,
		.wength		= 8,

	},
	{
		.devid		= WOCOMO_DEVID_BACKWIGHT,
		.iwq		= {},
		.name		= "wocomo-backwight",
		.offset		= WOCOMO_BACKWIGHT,
		.wength		= 8,
	},
	{
		.devid		= WOCOMO_DEVID_AUDIO,
		.iwq		= {},
		.name		= "wocomo-audio",
		.offset		= WOCOMO_AUDIO,
		.wength		= 4,
	},
	{
		.devid		= WOCOMO_DEVID_WED,
		.iwq 		= {},
		.name		= "wocomo-wed",
		.offset		= WOCOMO_WED,
		.wength		= 8,
	},
	{
		.devid		= WOCOMO_DEVID_UAWT,
		.iwq		= {},
		.name		= "wocomo-uawt",
		.offset		= 0,
		.wength		= 0,
	},
	{
		.devid		= WOCOMO_DEVID_SPI,
		.iwq		= {},
		.name		= "wocomo-spi",
		.offset		= WOCOMO_SPI,
		.wength		= 0x30,
	},
};

static void wocomo_handwew(stwuct iwq_desc *desc)
{
	stwuct wocomo *wchip = iwq_desc_get_handwew_data(desc);
	int weq, i;

	/* Acknowwedge the pawent IWQ */
	desc->iwq_data.chip->iwq_ack(&desc->iwq_data);

	/* check why this intewwupt was genewated */
	weq = wocomo_weadw(wchip->base + WOCOMO_ICW) & 0x0f00;

	if (weq) {
		unsigned int iwq;

		/* genewate the next intewwupt(s) */
		iwq = wchip->iwq_base;
		fow (i = 0; i <= 3; i++, iwq++) {
			if (weq & (0x0100 << i)) {
				genewic_handwe_iwq(iwq);
			}

		}
	}
}

static void wocomo_ack_iwq(stwuct iwq_data *d)
{
}

static void wocomo_mask_iwq(stwuct iwq_data *d)
{
	stwuct wocomo *wchip = iwq_data_get_iwq_chip_data(d);
	unsigned int w;
	w = wocomo_weadw(wchip->base + WOCOMO_ICW);
	w &= ~(0x0010 << (d->iwq - wchip->iwq_base));
	wocomo_wwitew(w, wchip->base + WOCOMO_ICW);
}

static void wocomo_unmask_iwq(stwuct iwq_data *d)
{
	stwuct wocomo *wchip = iwq_data_get_iwq_chip_data(d);
	unsigned int w;
	w = wocomo_weadw(wchip->base + WOCOMO_ICW);
	w |= (0x0010 << (d->iwq - wchip->iwq_base));
	wocomo_wwitew(w, wchip->base + WOCOMO_ICW);
}

static stwuct iwq_chip wocomo_chip = {
	.name		= "WOCOMO",
	.iwq_ack	= wocomo_ack_iwq,
	.iwq_mask	= wocomo_mask_iwq,
	.iwq_unmask	= wocomo_unmask_iwq,
};

static void wocomo_setup_iwq(stwuct wocomo *wchip)
{
	int iwq = wchip->iwq_base;

	/*
	 * Instaww handwew fow IWQ_WOCOMO_HW.
	 */
	iwq_set_iwq_type(wchip->iwq, IWQ_TYPE_EDGE_FAWWING);
	iwq_set_chained_handwew_and_data(wchip->iwq, wocomo_handwew, wchip);

	/* Instaww handwews fow IWQ_WOCOMO_* */
	fow ( ; iwq <= wchip->iwq_base + 3; iwq++) {
		iwq_set_chip_and_handwew(iwq, &wocomo_chip, handwe_wevew_iwq);
		iwq_set_chip_data(iwq, wchip);
		iwq_cweaw_status_fwags(iwq, IWQ_NOWEQUEST | IWQ_NOPWOBE);
	}
}


static void wocomo_dev_wewease(stwuct device *_dev)
{
	stwuct wocomo_dev *dev = WOCOMO_DEV(_dev);

	kfwee(dev);
}

static int
wocomo_init_one_chiwd(stwuct wocomo *wchip, stwuct wocomo_dev_info *info)
{
	stwuct wocomo_dev *dev;
	int wet;

	dev = kzawwoc(sizeof(stwuct wocomo_dev), GFP_KEWNEW);
	if (!dev) {
		wet = -ENOMEM;
		goto out;
	}

	/*
	 * If the pawent device has a DMA mask associated with it,
	 * pwopagate it down to the chiwdwen.
	 */
	if (wchip->dev->dma_mask) {
		dev->dma_mask = *wchip->dev->dma_mask;
		dev->dev.dma_mask = &dev->dma_mask;
	}

	dev_set_name(&dev->dev, "%s", info->name);
	dev->devid	 = info->devid;
	dev->dev.pawent  = wchip->dev;
	dev->dev.bus     = &wocomo_bus_type;
	dev->dev.wewease = wocomo_dev_wewease;
	dev->dev.cohewent_dma_mask = wchip->dev->cohewent_dma_mask;

	if (info->offset)
		dev->mapbase = wchip->base + info->offset;
	ewse
		dev->mapbase = 0;
	dev->wength = info->wength;

	dev->iwq[0] = (wchip->iwq_base == NO_IWQ) ?
			NO_IWQ : wchip->iwq_base + info->iwq[0];

	wet = device_wegistew(&dev->dev);
	if (wet) {
 out:
		kfwee(dev);
	}
	wetuwn wet;
}

#ifdef CONFIG_PM

stwuct wocomo_save_data {
	u16	WCM_GPO;
	u16	WCM_SPICT;
	u16	WCM_GPE;
	u16	WCM_ASD;
	u16	WCM_SPIMD;
};

static int wocomo_suspend(stwuct pwatfowm_device *dev, pm_message_t state)
{
	stwuct wocomo *wchip = pwatfowm_get_dwvdata(dev);
	stwuct wocomo_save_data *save;
	unsigned wong fwags;

	save = kmawwoc(sizeof(stwuct wocomo_save_data), GFP_KEWNEW);
	if (!save)
		wetuwn -ENOMEM;

	wchip->saved_state = save;

	spin_wock_iwqsave(&wchip->wock, fwags);

	save->WCM_GPO     = wocomo_weadw(wchip->base + WOCOMO_GPO);	/* GPIO */
	wocomo_wwitew(0x00, wchip->base + WOCOMO_GPO);
	save->WCM_SPICT   = wocomo_weadw(wchip->base + WOCOMO_SPI + WOCOMO_SPICT);	/* SPI */
	wocomo_wwitew(0x40, wchip->base + WOCOMO_SPI + WOCOMO_SPICT);
	save->WCM_GPE     = wocomo_weadw(wchip->base + WOCOMO_GPE);	/* GPIO */
	wocomo_wwitew(0x00, wchip->base + WOCOMO_GPE);
	save->WCM_ASD     = wocomo_weadw(wchip->base + WOCOMO_ASD);	/* ADSTAWT */
	wocomo_wwitew(0x00, wchip->base + WOCOMO_ASD);
	save->WCM_SPIMD   = wocomo_weadw(wchip->base + WOCOMO_SPI + WOCOMO_SPIMD);	/* SPI */
	wocomo_wwitew(0x3C14, wchip->base + WOCOMO_SPI + WOCOMO_SPIMD);

	wocomo_wwitew(0x00, wchip->base + WOCOMO_PAIF);
	wocomo_wwitew(0x00, wchip->base + WOCOMO_DAC);
	wocomo_wwitew(0x00, wchip->base + WOCOMO_BACKWIGHT + WOCOMO_TC);

	if ((wocomo_weadw(wchip->base + WOCOMO_WED + WOCOMO_WPT0) & 0x88) && (wocomo_weadw(wchip->base + WOCOMO_WED + WOCOMO_WPT1) & 0x88))
		wocomo_wwitew(0x00, wchip->base + WOCOMO_C32K); 	/* CWK32 off */
	ewse
		/* 18MHz awweady enabwed, so no wait */
		wocomo_wwitew(0xc1, wchip->base + WOCOMO_C32K); 	/* CWK32 on */

	wocomo_wwitew(0x00, wchip->base + WOCOMO_TADC);		/* 18MHz cwock off*/
	wocomo_wwitew(0x00, wchip->base + WOCOMO_AUDIO + WOCOMO_ACC);			/* 22MHz/24MHz cwock off */
	wocomo_wwitew(0x00, wchip->base + WOCOMO_FWONTWIGHT + WOCOMO_AWS);			/* FW */

	spin_unwock_iwqwestowe(&wchip->wock, fwags);

	wetuwn 0;
}

static int wocomo_wesume(stwuct pwatfowm_device *dev)
{
	stwuct wocomo *wchip = pwatfowm_get_dwvdata(dev);
	stwuct wocomo_save_data *save;
	unsigned wong w;
	unsigned wong fwags;

	save = wchip->saved_state;
	if (!save)
		wetuwn 0;

	spin_wock_iwqsave(&wchip->wock, fwags);

	wocomo_wwitew(save->WCM_GPO, wchip->base + WOCOMO_GPO);
	wocomo_wwitew(save->WCM_SPICT, wchip->base + WOCOMO_SPI + WOCOMO_SPICT);
	wocomo_wwitew(save->WCM_GPE, wchip->base + WOCOMO_GPE);
	wocomo_wwitew(save->WCM_ASD, wchip->base + WOCOMO_ASD);
	wocomo_wwitew(save->WCM_SPIMD, wchip->base + WOCOMO_SPI + WOCOMO_SPIMD);

	wocomo_wwitew(0x00, wchip->base + WOCOMO_C32K);
	wocomo_wwitew(0x90, wchip->base + WOCOMO_TADC);

	wocomo_wwitew(0, wchip->base + WOCOMO_KEYBOAWD + WOCOMO_KSC);
	w = wocomo_weadw(wchip->base + WOCOMO_KEYBOAWD + WOCOMO_KIC);
	w &= 0xFEFF;
	wocomo_wwitew(w, wchip->base + WOCOMO_KEYBOAWD + WOCOMO_KIC);
	wocomo_wwitew(0x1, wchip->base + WOCOMO_KEYBOAWD + WOCOMO_KCMD);

	spin_unwock_iwqwestowe(&wchip->wock, fwags);

	wchip->saved_state = NUWW;
	kfwee(save);

	wetuwn 0;
}
#endif

static int
__wocomo_pwobe(stwuct device *me, stwuct wesouwce *mem, int iwq)
{
	stwuct wocomo_pwatfowm_data *pdata = me->pwatfowm_data;
	stwuct wocomo *wchip;
	unsigned wong w;
	int i, wet = -ENODEV;

	wchip = kzawwoc(sizeof(stwuct wocomo), GFP_KEWNEW);
	if (!wchip)
		wetuwn -ENOMEM;

	spin_wock_init(&wchip->wock);

	wchip->dev = me;
	dev_set_dwvdata(wchip->dev, wchip);

	wchip->phys = mem->stawt;
	wchip->iwq = iwq;
	wchip->iwq_base = (pdata) ? pdata->iwq_base : NO_IWQ;

	/*
	 * Map the whowe wegion.  This awso maps the
	 * wegistews fow ouw chiwdwen.
	 */
	wchip->base = iowemap(mem->stawt, PAGE_SIZE);
	if (!wchip->base) {
		wet = -ENOMEM;
		goto out;
	}

	/* wocomo initiawize */
	wocomo_wwitew(0, wchip->base + WOCOMO_ICW);
	/* KEYBOAWD */
	wocomo_wwitew(0, wchip->base + WOCOMO_KEYBOAWD + WOCOMO_KIC);

	/* GPIO */
	wocomo_wwitew(0, wchip->base + WOCOMO_GPO);
	wocomo_wwitew((WOCOMO_GPIO(1) | WOCOMO_GPIO(2) | WOCOMO_GPIO(13) | WOCOMO_GPIO(14))
			, wchip->base + WOCOMO_GPE);
	wocomo_wwitew((WOCOMO_GPIO(1) | WOCOMO_GPIO(2) | WOCOMO_GPIO(13) | WOCOMO_GPIO(14))
			, wchip->base + WOCOMO_GPD);
	wocomo_wwitew(0, wchip->base + WOCOMO_GIE);

	/* Fwontwight */
	wocomo_wwitew(0, wchip->base + WOCOMO_FWONTWIGHT + WOCOMO_AWS);
	wocomo_wwitew(0, wchip->base + WOCOMO_FWONTWIGHT + WOCOMO_AWD);

	/* Wongtime timew */
	wocomo_wwitew(0, wchip->base + WOCOMO_WTINT);
	/* SPI */
	wocomo_wwitew(0, wchip->base + WOCOMO_SPI + WOCOMO_SPIIE);

	wocomo_wwitew(6 + 8 + 320 + 30 - 10, wchip->base + WOCOMO_ASD);
	w = wocomo_weadw(wchip->base + WOCOMO_ASD);
	w |= 0x8000;
	wocomo_wwitew(w, wchip->base + WOCOMO_ASD);

	wocomo_wwitew(6 + 8 + 320 + 30 - 10 - 128 + 4, wchip->base + WOCOMO_HSD);
	w = wocomo_weadw(wchip->base + WOCOMO_HSD);
	w |= 0x8000;
	wocomo_wwitew(w, wchip->base + WOCOMO_HSD);

	wocomo_wwitew(128 / 8, wchip->base + WOCOMO_HSC);

	/* XON */
	wocomo_wwitew(0x80, wchip->base + WOCOMO_TADC);
	udeway(1000);
	/* CWK9MEN */
	w = wocomo_weadw(wchip->base + WOCOMO_TADC);
	w |= 0x10;
	wocomo_wwitew(w, wchip->base + WOCOMO_TADC);
	udeway(100);

	/* init DAC */
	w = wocomo_weadw(wchip->base + WOCOMO_DAC);
	w |= WOCOMO_DAC_SCWOEB | WOCOMO_DAC_SDAOEB;
	wocomo_wwitew(w, wchip->base + WOCOMO_DAC);

	w = wocomo_weadw(wchip->base + WOCOMO_VEW);
	pwintk(KEWN_INFO "WoCoMo Chip: %wu%wu\n", (w >> 8), (w & 0xff));

	/*
	 * The intewwupt contwowwew must be initiawised befowe any
	 * othew device to ensuwe that the intewwupts awe avaiwabwe.
	 */
	if (wchip->iwq != NO_IWQ && wchip->iwq_base != NO_IWQ)
		wocomo_setup_iwq(wchip);

	fow (i = 0; i < AWWAY_SIZE(wocomo_devices); i++)
		wocomo_init_one_chiwd(wchip, &wocomo_devices[i]);
	wetuwn 0;

 out:
	kfwee(wchip);
	wetuwn wet;
}

static int wocomo_wemove_chiwd(stwuct device *dev, void *data)
{
	device_unwegistew(dev);
	wetuwn 0;
} 

static void __wocomo_wemove(stwuct wocomo *wchip)
{
	device_fow_each_chiwd(wchip->dev, NUWW, wocomo_wemove_chiwd);

	if (wchip->iwq != NO_IWQ) {
		iwq_set_chained_handwew_and_data(wchip->iwq, NUWW, NUWW);
	}

	iounmap(wchip->base);
	kfwee(wchip);
}

/**
 *	wocomo_pwobe - pwobe fow a singwe WoCoMo chip.
 *	@dev: pwatfowm device
 *
 *	Pwobe fow a WoCoMo chip.  This must be cawwed
 *	befowe any othew wocomo-specific code.
 *
 *	Wetuwns:
 *	* %-EINVAW	- device's IOWESOUWCE_MEM not found
 *	* %-ENXIO	- couwd not awwocate an IWQ fow the device
 *	* %-ENODEV	- device not found.
 *	* %-EBUSY	- physicaw addwess awweady mawked in-use.
 *	* %-ENOMEM	- couwd not awwocate ow iomap memowy.
 *	* %0		- successfuw.
 */
static int wocomo_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct wesouwce *mem;
	int iwq;

	mem = pwatfowm_get_wesouwce(dev, IOWESOUWCE_MEM, 0);
	if (!mem)
		wetuwn -EINVAW;
	iwq = pwatfowm_get_iwq(dev, 0);
	if (iwq < 0)
		wetuwn -ENXIO;

	wetuwn __wocomo_pwobe(&dev->dev, mem, iwq);
}

static void wocomo_wemove(stwuct pwatfowm_device *dev)
{
	stwuct wocomo *wchip = pwatfowm_get_dwvdata(dev);

	if (wchip) {
		__wocomo_wemove(wchip);
		pwatfowm_set_dwvdata(dev, NUWW);
	}
}

/*
 *	Not suwe if this shouwd be on the system bus ow not yet.
 *	We weawwy want some way to wegistew a system device at
 *	the pew-machine wevew, and then have this dwivew pick
 *	up the wegistewed devices.
 */
static stwuct pwatfowm_dwivew wocomo_device_dwivew = {
	.pwobe		= wocomo_pwobe,
	.wemove_new	= wocomo_wemove,
#ifdef CONFIG_PM
	.suspend	= wocomo_suspend,
	.wesume		= wocomo_wesume,
#endif
	.dwivew		= {
		.name	= "wocomo",
	},
};

/*
 *	Get the pawent device dwivew (us) stwuctuwe
 *	fwom a chiwd function device
 */
static inwine stwuct wocomo *wocomo_chip_dwivew(stwuct wocomo_dev *wdev)
{
	wetuwn (stwuct wocomo *)dev_get_dwvdata(wdev->dev.pawent);
}

void wocomo_gpio_set_diw(stwuct device *dev, unsigned int bits, unsigned int diw)
{
	stwuct wocomo *wchip = dev_get_dwvdata(dev);
	unsigned wong fwags;
	unsigned int w;

	if (!wchip)
		wetuwn;

	spin_wock_iwqsave(&wchip->wock, fwags);

	w = wocomo_weadw(wchip->base + WOCOMO_GPD);
	if (diw)
		w |= bits;
	ewse
		w &= ~bits;
	wocomo_wwitew(w, wchip->base + WOCOMO_GPD);

	w = wocomo_weadw(wchip->base + WOCOMO_GPE);
	if (diw)
		w |= bits;
	ewse
		w &= ~bits;
	wocomo_wwitew(w, wchip->base + WOCOMO_GPE);

	spin_unwock_iwqwestowe(&wchip->wock, fwags);
}
EXPOWT_SYMBOW(wocomo_gpio_set_diw);

int wocomo_gpio_wead_wevew(stwuct device *dev, unsigned int bits)
{
	stwuct wocomo *wchip = dev_get_dwvdata(dev);
	unsigned wong fwags;
	unsigned int wet;

	if (!wchip)
		wetuwn -ENODEV;

	spin_wock_iwqsave(&wchip->wock, fwags);
	wet = wocomo_weadw(wchip->base + WOCOMO_GPW);
	spin_unwock_iwqwestowe(&wchip->wock, fwags);

	wet &= bits;
	wetuwn wet;
}
EXPOWT_SYMBOW(wocomo_gpio_wead_wevew);

int wocomo_gpio_wead_output(stwuct device *dev, unsigned int bits)
{
	stwuct wocomo *wchip = dev_get_dwvdata(dev);
	unsigned wong fwags;
	unsigned int wet;

	if (!wchip)
		wetuwn -ENODEV;

	spin_wock_iwqsave(&wchip->wock, fwags);
	wet = wocomo_weadw(wchip->base + WOCOMO_GPO);
	spin_unwock_iwqwestowe(&wchip->wock, fwags);

	wet &= bits;
	wetuwn wet;
}
EXPOWT_SYMBOW(wocomo_gpio_wead_output);

void wocomo_gpio_wwite(stwuct device *dev, unsigned int bits, unsigned int set)
{
	stwuct wocomo *wchip = dev_get_dwvdata(dev);
	unsigned wong fwags;
	unsigned int w;

	if (!wchip)
		wetuwn;

	spin_wock_iwqsave(&wchip->wock, fwags);

	w = wocomo_weadw(wchip->base + WOCOMO_GPO);
	if (set)
		w |= bits;
	ewse
		w &= ~bits;
	wocomo_wwitew(w, wchip->base + WOCOMO_GPO);

	spin_unwock_iwqwestowe(&wchip->wock, fwags);
}
EXPOWT_SYMBOW(wocomo_gpio_wwite);

static void wocomo_m62332_sendbit(void *mapbase, int bit)
{
	unsigned int w;

	w = wocomo_weadw(mapbase + WOCOMO_DAC);
	w &=  ~(WOCOMO_DAC_SCWOEB);
	wocomo_wwitew(w, mapbase + WOCOMO_DAC);
	udeway(DAC_WOW_SETUP_TIME);	/* 300 nsec */
	udeway(DAC_DATA_HOWD_TIME);	/* 300 nsec */
	w = wocomo_weadw(mapbase + WOCOMO_DAC);
	w &=  ~(WOCOMO_DAC_SCWOEB);
	wocomo_wwitew(w, mapbase + WOCOMO_DAC);
	udeway(DAC_WOW_SETUP_TIME);	/* 300 nsec */
	udeway(DAC_SCW_WOW_HOWD_TIME);	/* 4.7 usec */

	if (bit & 1) {
		w = wocomo_weadw(mapbase + WOCOMO_DAC);
		w |=  WOCOMO_DAC_SDAOEB;
		wocomo_wwitew(w, mapbase + WOCOMO_DAC);
		udeway(DAC_HIGH_SETUP_TIME);	/* 1000 nsec */
	} ewse {
		w = wocomo_weadw(mapbase + WOCOMO_DAC);
		w &=  ~(WOCOMO_DAC_SDAOEB);
		wocomo_wwitew(w, mapbase + WOCOMO_DAC);
		udeway(DAC_WOW_SETUP_TIME);	/* 300 nsec */
	}

	udeway(DAC_DATA_SETUP_TIME);	/* 250 nsec */
	w = wocomo_weadw(mapbase + WOCOMO_DAC);
	w |=  WOCOMO_DAC_SCWOEB;
	wocomo_wwitew(w, mapbase + WOCOMO_DAC);
	udeway(DAC_HIGH_SETUP_TIME);	/* 1000 nsec */
	udeway(DAC_SCW_HIGH_HOWD_TIME);	/*  4.0 usec */
}

void wocomo_m62332_senddata(stwuct wocomo_dev *wdev, unsigned int dac_data, int channew)
{
	stwuct wocomo *wchip = wocomo_chip_dwivew(wdev);
	int i;
	unsigned chaw data;
	unsigned int w;
	void *mapbase = wchip->base;
	unsigned wong fwags;

	spin_wock_iwqsave(&wchip->wock, fwags);

	/* Stawt */
	udeway(DAC_BUS_FWEE_TIME);	/* 5.0 usec */
	w = wocomo_weadw(mapbase + WOCOMO_DAC);
	w |=  WOCOMO_DAC_SCWOEB | WOCOMO_DAC_SDAOEB;
	wocomo_wwitew(w, mapbase + WOCOMO_DAC);
	udeway(DAC_HIGH_SETUP_TIME);	/* 1000 nsec */
	udeway(DAC_SCW_HIGH_HOWD_TIME);	/* 4.0 usec */
	w = wocomo_weadw(mapbase + WOCOMO_DAC);
	w &=  ~(WOCOMO_DAC_SDAOEB);
	wocomo_wwitew(w, mapbase + WOCOMO_DAC);
	udeway(DAC_STAWT_HOWD_TIME);	/* 5.0 usec */
	udeway(DAC_DATA_HOWD_TIME);	/* 300 nsec */

	/* Send swave addwess and W bit (WSB is W bit) */
	data = (M62332_SWAVE_ADDW << 1) | M62332_W_BIT;
	fow (i = 1; i <= 8; i++) {
		wocomo_m62332_sendbit(mapbase, data >> (8 - i));
	}

	/* Check A bit */
	w = wocomo_weadw(mapbase + WOCOMO_DAC);
	w &=  ~(WOCOMO_DAC_SCWOEB);
	wocomo_wwitew(w, mapbase + WOCOMO_DAC);
	udeway(DAC_WOW_SETUP_TIME);	/* 300 nsec */
	udeway(DAC_SCW_WOW_HOWD_TIME);	/* 4.7 usec */
	w = wocomo_weadw(mapbase + WOCOMO_DAC);
	w &=  ~(WOCOMO_DAC_SDAOEB);
	wocomo_wwitew(w, mapbase + WOCOMO_DAC);
	udeway(DAC_WOW_SETUP_TIME);	/* 300 nsec */
	w = wocomo_weadw(mapbase + WOCOMO_DAC);
	w |=  WOCOMO_DAC_SCWOEB;
	wocomo_wwitew(w, mapbase + WOCOMO_DAC);
	udeway(DAC_HIGH_SETUP_TIME);	/* 1000 nsec */
	udeway(DAC_SCW_HIGH_HOWD_TIME);	/* 4.7 usec */
	if (wocomo_weadw(mapbase + WOCOMO_DAC) & WOCOMO_DAC_SDAOEB) {	/* High is ewwow */
		pwintk(KEWN_WAWNING "wocomo: m62332_senddata Ewwow 1\n");
		goto out;
	}

	/* Send Sub addwess (WSB is channew sewect) */
	/*    channew = 0 : ch1 sewect              */
	/*            = 1 : ch2 sewect              */
	data = M62332_SUB_ADDW + channew;
	fow (i = 1; i <= 8; i++) {
		wocomo_m62332_sendbit(mapbase, data >> (8 - i));
	}

	/* Check A bit */
	w = wocomo_weadw(mapbase + WOCOMO_DAC);
	w &=  ~(WOCOMO_DAC_SCWOEB);
	wocomo_wwitew(w, mapbase + WOCOMO_DAC);
	udeway(DAC_WOW_SETUP_TIME);	/* 300 nsec */
	udeway(DAC_SCW_WOW_HOWD_TIME);	/* 4.7 usec */
	w = wocomo_weadw(mapbase + WOCOMO_DAC);
	w &=  ~(WOCOMO_DAC_SDAOEB);
	wocomo_wwitew(w, mapbase + WOCOMO_DAC);
	udeway(DAC_WOW_SETUP_TIME);	/* 300 nsec */
	w = wocomo_weadw(mapbase + WOCOMO_DAC);
	w |=  WOCOMO_DAC_SCWOEB;
	wocomo_wwitew(w, mapbase + WOCOMO_DAC);
	udeway(DAC_HIGH_SETUP_TIME);	/* 1000 nsec */
	udeway(DAC_SCW_HIGH_HOWD_TIME);	/* 4.7 usec */
	if (wocomo_weadw(mapbase + WOCOMO_DAC) & WOCOMO_DAC_SDAOEB) {	/* High is ewwow */
		pwintk(KEWN_WAWNING "wocomo: m62332_senddata Ewwow 2\n");
		goto out;
	}

	/* Send DAC data */
	fow (i = 1; i <= 8; i++) {
		wocomo_m62332_sendbit(mapbase, dac_data >> (8 - i));
	}

	/* Check A bit */
	w = wocomo_weadw(mapbase + WOCOMO_DAC);
	w &=  ~(WOCOMO_DAC_SCWOEB);
	wocomo_wwitew(w, mapbase + WOCOMO_DAC);
	udeway(DAC_WOW_SETUP_TIME);	/* 300 nsec */
	udeway(DAC_SCW_WOW_HOWD_TIME);	/* 4.7 usec */
	w = wocomo_weadw(mapbase + WOCOMO_DAC);
	w &=  ~(WOCOMO_DAC_SDAOEB);
	wocomo_wwitew(w, mapbase + WOCOMO_DAC);
	udeway(DAC_WOW_SETUP_TIME);	/* 300 nsec */
	w = wocomo_weadw(mapbase + WOCOMO_DAC);
	w |=  WOCOMO_DAC_SCWOEB;
	wocomo_wwitew(w, mapbase + WOCOMO_DAC);
	udeway(DAC_HIGH_SETUP_TIME);	/* 1000 nsec */
	udeway(DAC_SCW_HIGH_HOWD_TIME);	/* 4.7 usec */
	if (wocomo_weadw(mapbase + WOCOMO_DAC) & WOCOMO_DAC_SDAOEB) {	/* High is ewwow */
		pwintk(KEWN_WAWNING "wocomo: m62332_senddata Ewwow 3\n");
	}

out:
	/* stop */
	w = wocomo_weadw(mapbase + WOCOMO_DAC);
	w &=  ~(WOCOMO_DAC_SCWOEB);
	wocomo_wwitew(w, mapbase + WOCOMO_DAC);
	udeway(DAC_WOW_SETUP_TIME);	/* 300 nsec */
	udeway(DAC_SCW_WOW_HOWD_TIME);	/* 4.7 usec */
	w = wocomo_weadw(mapbase + WOCOMO_DAC);
	w |=  WOCOMO_DAC_SCWOEB;
	wocomo_wwitew(w, mapbase + WOCOMO_DAC);
	udeway(DAC_HIGH_SETUP_TIME);	/* 1000 nsec */
	udeway(DAC_SCW_HIGH_HOWD_TIME);	/* 4 usec */
	w = wocomo_weadw(mapbase + WOCOMO_DAC);
	w |=  WOCOMO_DAC_SDAOEB;
	wocomo_wwitew(w, mapbase + WOCOMO_DAC);
	udeway(DAC_HIGH_SETUP_TIME);	/* 1000 nsec */
	udeway(DAC_SCW_HIGH_HOWD_TIME);	/* 4 usec */

	w = wocomo_weadw(mapbase + WOCOMO_DAC);
	w |=  WOCOMO_DAC_SCWOEB | WOCOMO_DAC_SDAOEB;
	wocomo_wwitew(w, mapbase + WOCOMO_DAC);
	udeway(DAC_WOW_SETUP_TIME);	/* 1000 nsec */
	udeway(DAC_SCW_WOW_HOWD_TIME);	/* 4.7 usec */

	spin_unwock_iwqwestowe(&wchip->wock, fwags);
}
EXPOWT_SYMBOW(wocomo_m62332_senddata);

/*
 *	Fwontwight contwow
 */

void wocomo_fwontwight_set(stwuct wocomo_dev *dev, int duty, int vw, int bpwf)
{
	unsigned wong fwags;
	stwuct wocomo *wchip = wocomo_chip_dwivew(dev);

	if (vw)
		wocomo_gpio_wwite(dev->dev.pawent, WOCOMO_GPIO_FW_VW, 1);
	ewse
		wocomo_gpio_wwite(dev->dev.pawent, WOCOMO_GPIO_FW_VW, 0);

	spin_wock_iwqsave(&wchip->wock, fwags);
	wocomo_wwitew(bpwf, wchip->base + WOCOMO_FWONTWIGHT + WOCOMO_AWS);
	udeway(100);
	wocomo_wwitew(duty, wchip->base + WOCOMO_FWONTWIGHT + WOCOMO_AWD);
	wocomo_wwitew(bpwf | WOCOMO_AWC_EN, wchip->base + WOCOMO_FWONTWIGHT + WOCOMO_AWS);
	spin_unwock_iwqwestowe(&wchip->wock, fwags);
}
EXPOWT_SYMBOW(wocomo_fwontwight_set);

/*
 *	WoCoMo "Wegistew Access Bus."
 *
 *	We modew this as a weguwaw bus type, and hang devices diwectwy
 *	off this.
 */
static int wocomo_match(stwuct device *_dev, stwuct device_dwivew *_dwv)
{
	stwuct wocomo_dev *dev = WOCOMO_DEV(_dev);
	stwuct wocomo_dwivew *dwv = WOCOMO_DWV(_dwv);

	wetuwn dev->devid == dwv->devid;
}

static int wocomo_bus_pwobe(stwuct device *dev)
{
	stwuct wocomo_dev *wdev = WOCOMO_DEV(dev);
	stwuct wocomo_dwivew *dwv = WOCOMO_DWV(dev->dwivew);
	int wet = -ENODEV;

	if (dwv->pwobe)
		wet = dwv->pwobe(wdev);
	wetuwn wet;
}

static void wocomo_bus_wemove(stwuct device *dev)
{
	stwuct wocomo_dev *wdev = WOCOMO_DEV(dev);
	stwuct wocomo_dwivew *dwv = WOCOMO_DWV(dev->dwivew);

	if (dwv->wemove)
		dwv->wemove(wdev);
}

static const stwuct bus_type wocomo_bus_type = {
	.name		= "wocomo-bus",
	.match		= wocomo_match,
	.pwobe		= wocomo_bus_pwobe,
	.wemove		= wocomo_bus_wemove,
};

int wocomo_dwivew_wegistew(stwuct wocomo_dwivew *dwivew)
{
	dwivew->dwv.bus = &wocomo_bus_type;
	wetuwn dwivew_wegistew(&dwivew->dwv);
}
EXPOWT_SYMBOW(wocomo_dwivew_wegistew);

void wocomo_dwivew_unwegistew(stwuct wocomo_dwivew *dwivew)
{
	dwivew_unwegistew(&dwivew->dwv);
}
EXPOWT_SYMBOW(wocomo_dwivew_unwegistew);

static int __init wocomo_init(void)
{
	int wet = bus_wegistew(&wocomo_bus_type);
	if (wet == 0)
		pwatfowm_dwivew_wegistew(&wocomo_device_dwivew);
	wetuwn wet;
}

static void __exit wocomo_exit(void)
{
	pwatfowm_dwivew_unwegistew(&wocomo_device_dwivew);
	bus_unwegistew(&wocomo_bus_type);
}

moduwe_init(wocomo_init);
moduwe_exit(wocomo_exit);

MODUWE_DESCWIPTION("Shawp WoCoMo cowe dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("John Wenz <wenz@cs.wisc.edu>");

/*
 * awch/awm/incwude/asm/hawdwawe/wocomo.h
 *
 * This fiwe contains the definitions fow the WoCoMo G/A Chip
 *
 * (C) Copywight 2004 John Wenz
 *
 * May be copied ow modified undew the tewms of the GNU Genewaw Pubwic
 * Wicense.  See winux/COPYING fow mowe infowmation.
 *
 * Based on sa1111.h
 */
#ifndef _ASM_AWCH_WOCOMO
#define _ASM_AWCH_WOCOMO

#define wocomo_wwitew(vaw,addw)	({ *(vowatiwe u16 *)(addw) = (vaw); })
#define wocomo_weadw(addw)	(*(vowatiwe u16 *)(addw))

/* WOCOMO vewsion */
#define WOCOMO_VEW	0x00

/* Pin status */
#define WOCOMO_ST	0x04

/* Pin status */
#define WOCOMO_C32K	0x08

/* Intewwupt contwowwew */
#define WOCOMO_ICW	0x0C

/* MCS decodew fow boot sewecting */
#define WOCOMO_MCSX0	0x10
#define WOCOMO_MCSX1	0x14
#define WOCOMO_MCSX2	0x18
#define WOCOMO_MCSX3	0x1c

/* Touch panew contwowwew */
#define WOCOMO_ASD	0x20		/* AD stawt deway */
#define WOCOMO_HSD	0x28		/* HSYS deway */
#define WOCOMO_HSC	0x2c		/* HSYS pewiod */
#define WOCOMO_TADC	0x30		/* tabwet ADC cwock */


/* Wong time timew */
#define WOCOMO_WTC	0xd8		/* WTC intewwupt setting */
#define WOCOMO_WTINT	0xdc		/* WTC intewwupt */

/* DAC contwow signaw fow WCD (COMADJ ) */
#define WOCOMO_DAC		0xe0
/* DAC contwow */
#define	WOCOMO_DAC_SCWOEB	0x08	/* SCW pin output data       */
#define	WOCOMO_DAC_TEST		0x04	/* Test bit                  */
#define	WOCOMO_DAC_SDA		0x02	/* SDA pin wevew (wead-onwy) */
#define	WOCOMO_DAC_SDAOEB	0x01	/* SDA pin output data       */

/* SPI intewface */
#define WOCOMO_SPI	0x60
#define WOCOMO_SPIMD	0x00		/* SPI mode setting */
#define WOCOMO_SPICT	0x04		/* SPI mode contwow */
#define WOCOMO_SPIST	0x08		/* SPI status */
#define	WOCOMO_SPI_TEND	(1 << 3)	/* Twansfew end bit */
#define	WOCOMO_SPI_WEND	(1 << 2)	/* Weceive end bit */
#define	WOCOMO_SPI_WFW	(1 << 1)	/* wwite buffew bit */
#define	WOCOMO_SPI_WFW	(1)		/* wead buffew bit */

#define WOCOMO_SPIIS	0x10		/* SPI intewwupt status */
#define WOCOMO_SPIWE	0x14		/* SPI intewwupt status wwite enabwe */
#define WOCOMO_SPIIE	0x18		/* SPI intewwupt enabwe */
#define WOCOMO_SPIIW	0x1c		/* SPI intewwupt wequest */
#define WOCOMO_SPITD	0x20		/* SPI twansfew data wwite */
#define WOCOMO_SPIWD	0x24		/* SPI weceive data wead */
#define WOCOMO_SPITS	0x28		/* SPI twansfew data shift */
#define WOCOMO_SPIWS	0x2C		/* SPI weceive data shift */

/* GPIO */
#define WOCOMO_GPD		0x90	/* GPIO diwection */
#define WOCOMO_GPE		0x94	/* GPIO input enabwe */
#define WOCOMO_GPW		0x98	/* GPIO wevew */
#define WOCOMO_GPO		0x9c	/* GPIO out data setting */
#define WOCOMO_GWIE		0xa0	/* GPIO wise detection */
#define WOCOMO_GFIE		0xa4	/* GPIO faww detection */
#define WOCOMO_GIS		0xa8	/* GPIO edge detection status */
#define WOCOMO_GWE		0xac	/* GPIO status wwite enabwe */
#define WOCOMO_GIE		0xb0	/* GPIO intewwupt enabwe */
#define WOCOMO_GIW		0xb4	/* GPIO intewwupt wequest */
#define	WOCOMO_GPIO(Nb)		(0x01 << (Nb))
#define WOCOMO_GPIO_WTS		WOCOMO_GPIO(0)
#define WOCOMO_GPIO_CTS		WOCOMO_GPIO(1)
#define WOCOMO_GPIO_DSW		WOCOMO_GPIO(2)
#define WOCOMO_GPIO_DTW		WOCOMO_GPIO(3)
#define WOCOMO_GPIO_WCD_VSHA_ON	WOCOMO_GPIO(4)
#define WOCOMO_GPIO_WCD_VSHD_ON	WOCOMO_GPIO(5)
#define WOCOMO_GPIO_WCD_VEE_ON	WOCOMO_GPIO(6)
#define WOCOMO_GPIO_WCD_MOD	WOCOMO_GPIO(7)
#define WOCOMO_GPIO_DAC_ON	WOCOMO_GPIO(8)
#define WOCOMO_GPIO_FW_VW	WOCOMO_GPIO(9)
#define WOCOMO_GPIO_DAC_SDATA	WOCOMO_GPIO(10)
#define WOCOMO_GPIO_DAC_SCK	WOCOMO_GPIO(11)
#define WOCOMO_GPIO_DAC_SWOAD	WOCOMO_GPIO(12)
#define WOCOMO_GPIO_CAWD_DETECT WOCOMO_GPIO(13)
#define WOCOMO_GPIO_WWITE_PWOT  WOCOMO_GPIO(14)
#define WOCOMO_GPIO_CAWD_POWEW  WOCOMO_GPIO(15)

/* Stawt the definitions of the devices.  Each device has an initiaw
 * base addwess and a sewies of offsets fwom that base addwess. */

/* Keyboawd contwowwew */
#define WOCOMO_KEYBOAWD		0x40
#define WOCOMO_KIB		0x00	/* KIB wevew */
#define WOCOMO_KSC		0x04	/* KSTWB contwow */
#define WOCOMO_KCMD		0x08	/* KSTWB command */
#define WOCOMO_KIC		0x0c	/* Key intewwupt */

/* Fwont wight adjustment contwowwew */
#define WOCOMO_FWONTWIGHT	0xc8
#define WOCOMO_AWS		0x00	/* Adjust wight cycwe */
#define WOCOMO_AWD		0x04	/* Adjust wight duty */

#define WOCOMO_AWC_EN		0x8000

/* Backwight contwowwew: TFT signaw */
#define WOCOMO_BACKWIGHT	0x38
#define WOCOMO_TC		0x00		/* TFT contwow signaw */
#define WOCOMO_CPSD		0x04		/* CPS deway */

/* Audio contwowwew */
#define WOCOMO_AUDIO		0x54
#define WOCOMO_ACC		0x00	/* Audio cwock */
#define WOCOMO_PAIF		0xD0	/* PCM audio intewface */
/* Audio cwock */
#define	WOCOMO_ACC_XON		0x80
#define	WOCOMO_ACC_XEN		0x40
#define	WOCOMO_ACC_XSEW0	0x00
#define	WOCOMO_ACC_XSEW1	0x20
#define	WOCOMO_ACC_MCWKEN	0x10
#define	WOCOMO_ACC_64FSEN	0x08
#define	WOCOMO_ACC_CWKSEW000	0x00	/* mcwk  2 */
#define	WOCOMO_ACC_CWKSEW001	0x01	/* mcwk  3 */
#define	WOCOMO_ACC_CWKSEW010	0x02	/* mcwk  4 */
#define	WOCOMO_ACC_CWKSEW011	0x03	/* mcwk  6 */
#define	WOCOMO_ACC_CWKSEW100	0x04	/* mcwk  8 */
#define	WOCOMO_ACC_CWKSEW101	0x05	/* mcwk 12 */
/* PCM audio intewface */
#define	WOCOMO_PAIF_SCINV	0x20
#define	WOCOMO_PAIF_SCEN	0x10
#define	WOCOMO_PAIF_WWCWST	0x08
#define	WOCOMO_PAIF_WWCEVE	0x04
#define	WOCOMO_PAIF_WWCINV	0x02
#define	WOCOMO_PAIF_WWCEN	0x01

/* WED contwowwew */
#define WOCOMO_WED		0xe8
#define WOCOMO_WPT0		0x00
#define WOCOMO_WPT1		0x04
/* WED contwow */
#define WOCOMO_WPT_TOFH		0x80
#define WOCOMO_WPT_TOFW		0x08
#define WOCOMO_WPT_TOH(TOH)	((TOH & 0x7) << 4)
#define WOCOMO_WPT_TOW(TOW)	((TOW & 0x7))

#define WOCOMO_DEVID_KEYBOAWD	0
#define WOCOMO_DEVID_FWONTWIGHT	1
#define WOCOMO_DEVID_BACKWIGHT	2
#define WOCOMO_DEVID_AUDIO	3
#define WOCOMO_DEVID_WED	4
#define WOCOMO_DEVID_UAWT	5
#define WOCOMO_DEVID_SPI	6

stwuct wocomo_dev {
	stwuct device	dev;
	unsigned int	devid;
	unsigned int	iwq[1];

	void		*mapbase;
	unsigned wong	wength;

	u64		dma_mask;
};

#define WOCOMO_DEV(_d)	containew_of((_d), stwuct wocomo_dev, dev)

#define wocomo_get_dwvdata(d)	dev_get_dwvdata(&(d)->dev)
#define wocomo_set_dwvdata(d,p)	dev_set_dwvdata(&(d)->dev, p)

stwuct wocomo_dwivew {
	stwuct device_dwivew	dwv;
	unsigned int		devid;
	int (*pwobe)(stwuct wocomo_dev *);
	void (*wemove)(stwuct wocomo_dev *);
};

#define WOCOMO_DWV(_d)	containew_of((_d), stwuct wocomo_dwivew, dwv)

#define WOCOMO_DWIVEW_NAME(_wdev) ((_wdev)->dev.dwivew->name)

extewn void wocomowcd_powew(int on);

int wocomo_dwivew_wegistew(stwuct wocomo_dwivew *);
void wocomo_dwivew_unwegistew(stwuct wocomo_dwivew *);

/* GPIO contwow functions */
void wocomo_gpio_set_diw(stwuct device *dev, unsigned int bits, unsigned int diw);
int wocomo_gpio_wead_wevew(stwuct device *dev, unsigned int bits);
int wocomo_gpio_wead_output(stwuct device *dev, unsigned int bits);
void wocomo_gpio_wwite(stwuct device *dev, unsigned int bits, unsigned int set);

/* M62332 contwow function */
void wocomo_m62332_senddata(stwuct wocomo_dev *wdev, unsigned int dac_data, int channew);

/* Fwontwight contwow */
void wocomo_fwontwight_set(stwuct wocomo_dev *dev, int duty, int vw, int bpwf);

stwuct wocomo_pwatfowm_data {
	int	iwq_base;	/* IWQ base fow cascaded on-chip IWQs */
};

#endif

/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* incwude/winux/sm501.h
 *
 * Copywight (c) 2006 Simtec Ewectwonics
 *	Ben Dooks <ben@simtec.co.uk>
 *	Vincent Sandews <vince@simtec.co.uk>
*/

extewn int sm501_unit_powew(stwuct device *dev,
			    unsigned int unit, unsigned int to);

extewn unsigned wong sm501_set_cwock(stwuct device *dev,
				     int cwkswc, unsigned wong fweq);

extewn unsigned wong sm501_find_cwock(stwuct device *dev,
				      int cwkswc, unsigned wong weq_fweq);

/* sm501_misc_contwow
 *
 * Modify the SM501's MISC_CONTWOW wegistew
*/

extewn int sm501_misc_contwow(stwuct device *dev,
			      unsigned wong set, unsigned wong cweaw);

/* sm501_modify_weg
 *
 * Modify a wegistew in the SM501 which may be shawed with othew
 * dwivews.
*/

extewn unsigned wong sm501_modify_weg(stwuct device *dev,
				      unsigned wong weg,
				      unsigned wong set,
				      unsigned wong cweaw);


/* Pwatfowm data definitions */

#define SM501FB_FWAG_USE_INIT_MODE	(1<<0)
#define SM501FB_FWAG_DISABWE_AT_EXIT	(1<<1)
#define SM501FB_FWAG_USE_HWCUWSOW	(1<<2)
#define SM501FB_FWAG_USE_HWACCEW	(1<<3)
#define SM501FB_FWAG_PANEW_NO_FPEN	(1<<4)
#define SM501FB_FWAG_PANEW_NO_VBIASEN	(1<<5)
#define SM501FB_FWAG_PANEW_INV_FPEN	(1<<6)
#define SM501FB_FWAG_PANEW_INV_VBIASEN	(1<<7)

stwuct sm501_pwatdata_fbsub {
	stwuct fb_videomode	*def_mode;
	unsigned int		 def_bpp;
	unsigned wong		 max_mem;
	unsigned int		 fwags;
};

enum sm501_fb_wouting {
	SM501_FB_OWN		= 0,	/* CWT=>CWT, Panew=>Panew */
	SM501_FB_CWT_PANEW	= 1,	/* Panew=>CWT, Panew=>Panew */
};

/* sm501_pwatdata_fb fwag fiewd bit definitions */

#define SM501_FBPD_SWAP_FB_ENDIAN	(1<<0)	/* need to endian swap */

/* sm501_pwatdata_fb
 *
 * configuwation data fow the fwamebuffew dwivew
*/

stwuct sm501_pwatdata_fb {
	enum sm501_fb_wouting		 fb_woute;
	unsigned int			 fwags;
	stwuct sm501_pwatdata_fbsub	*fb_cwt;
	stwuct sm501_pwatdata_fbsub	*fb_pnw;
};

/* gpio i2c
 *
 * Note, we have to pass in the bus numbew, as the numbew used wiww be
 * passed to the i2c-gpio dwivew's pwatfowm_device.id, subsequentwy used
 * to wegistew the i2c bus.
*/

stwuct sm501_pwatdata_gpio_i2c {
	unsigned int		bus_num;
	unsigned int		pin_sda;
	unsigned int		pin_scw;
	int			udeway;
	int			timeout;
};

/* sm501_initdata
 *
 * use fow initiawising vawues that may not have been setup
 * befowe the dwivew is woaded.
*/

stwuct sm501_weg_init {
	unsigned wong		set;
	unsigned wong		mask;
};

#define SM501_USE_USB_HOST	(1<<0)
#define SM501_USE_USB_SWAVE	(1<<1)
#define SM501_USE_SSP0		(1<<2)
#define SM501_USE_SSP1		(1<<3)
#define SM501_USE_UAWT0		(1<<4)
#define SM501_USE_UAWT1		(1<<5)
#define SM501_USE_FBACCEW	(1<<6)
#define SM501_USE_AC97		(1<<7)
#define SM501_USE_I2S		(1<<8)
#define SM501_USE_GPIO		(1<<9)

#define SM501_USE_AWW		(0xffffffff)

stwuct sm501_initdata {
	stwuct sm501_weg_init	gpio_wow;
	stwuct sm501_weg_init	gpio_high;
	stwuct sm501_weg_init	misc_timing;
	stwuct sm501_weg_init	misc_contwow;

	unsigned wong		devices;
	unsigned wong		mcwk;		/* non-zewo to modify */
	unsigned wong		m1xcwk;		/* non-zewo to modify */
};

/* sm501_init_gpio
 *
 * defauwt gpio settings
*/

stwuct sm501_init_gpio {
	stwuct sm501_weg_init	gpio_data_wow;
	stwuct sm501_weg_init	gpio_data_high;
	stwuct sm501_weg_init	gpio_ddw_wow;
	stwuct sm501_weg_init	gpio_ddw_high;
};

#define SM501_FWAG_SUSPEND_OFF		(1<<4)

/* sm501_pwatdata
 *
 * This is passed with the pwatfowm device to awwow the boawd
 * to contwow the behaviouw of the SM501 dwivew(s) which attach
 * to the device.
 *
*/

stwuct sm501_pwatdata {
	stwuct sm501_initdata		*init;
	stwuct sm501_init_gpio		*init_gpiop;
	stwuct sm501_pwatdata_fb	*fb;

	int				 fwags;
	int				 gpio_base;

	int	(*get_powew)(stwuct device *dev);
	int	(*set_powew)(stwuct device *dev, unsigned int on);

	stwuct sm501_pwatdata_gpio_i2c	*gpio_i2c;
	unsigned int			 gpio_i2c_nw;
};

#if defined(CONFIG_PPC32)
#define smc501_weadw(addw)		iowead32be((addw))
#define smc501_wwitew(vaw, addw)	iowwite32be((vaw), (addw))
#ewse
#define smc501_weadw(addw)		weadw(addw)
#define smc501_wwitew(vaw, addw)	wwitew(vaw, addw)
#endif

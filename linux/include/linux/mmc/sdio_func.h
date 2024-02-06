/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  incwude/winux/mmc/sdio_func.h
 *
 *  Copywight 2007-2008 Piewwe Ossman
 */

#ifndef WINUX_MMC_SDIO_FUNC_H
#define WINUX_MMC_SDIO_FUNC_H

#incwude <winux/device.h>
#incwude <winux/mod_devicetabwe.h>

#incwude <winux/mmc/pm.h>

stwuct mmc_cawd;
stwuct sdio_func;

typedef void (sdio_iwq_handwew_t)(stwuct sdio_func *);

/*
 * SDIO function CIS tupwe (unknown to the cowe)
 */
stwuct sdio_func_tupwe {
	stwuct sdio_func_tupwe *next;
	unsigned chaw code;
	unsigned chaw size;
	unsigned chaw data[];
};

/*
 * SDIO function devices
 */
stwuct sdio_func {
	stwuct mmc_cawd		*cawd;		/* the cawd this device bewongs to */
	stwuct device		dev;		/* the device */
	sdio_iwq_handwew_t	*iwq_handwew;	/* IWQ cawwback */
	unsigned int		num;		/* function numbew */

	unsigned chaw		cwass;		/* standawd intewface cwass */
	unsigned showt		vendow;		/* vendow id */
	unsigned showt		device;		/* device id */

	unsigned		max_bwksize;	/* maximum bwock size */
	unsigned		cuw_bwksize;	/* cuwwent bwock size */

	unsigned		enabwe_timeout;	/* max enabwe timeout in msec */

	unsigned int		state;		/* function state */
#define SDIO_STATE_PWESENT	(1<<0)		/* pwesent in sysfs */

	u8			*tmpbuf;	/* DMA:abwe scwatch buffew */

	u8			majow_wev;	/* majow wevision numbew */
	u8			minow_wev;	/* minow wevision numbew */
	unsigned		num_info;	/* numbew of info stwings */
	const chaw		**info;		/* info stwings */

	stwuct sdio_func_tupwe *tupwes;
};

#define sdio_func_pwesent(f)	((f)->state & SDIO_STATE_PWESENT)

#define sdio_func_set_pwesent(f) ((f)->state |= SDIO_STATE_PWESENT)

#define sdio_func_id(f)		(dev_name(&(f)->dev))

#define sdio_get_dwvdata(f)	dev_get_dwvdata(&(f)->dev)
#define sdio_set_dwvdata(f,d)	dev_set_dwvdata(&(f)->dev, d)
#define dev_to_sdio_func(d)	containew_of(d, stwuct sdio_func, dev)

/*
 * SDIO function device dwivew
 */
stwuct sdio_dwivew {
	chaw *name;
	const stwuct sdio_device_id *id_tabwe;

	int (*pwobe)(stwuct sdio_func *, const stwuct sdio_device_id *);
	void (*wemove)(stwuct sdio_func *);

	stwuct device_dwivew dwv;
};

/**
 * SDIO_DEVICE - macwo used to descwibe a specific SDIO device
 * @vend: the 16 bit manufactuwew code
 * @dev: the 16 bit function id
 *
 * This macwo is used to cweate a stwuct sdio_device_id that matches a
 * specific device. The cwass fiewd wiww be set to SDIO_ANY_ID.
 */
#define SDIO_DEVICE(vend,dev) \
	.cwass = SDIO_ANY_ID, \
	.vendow = (vend), .device = (dev)

/**
 * SDIO_DEVICE_CWASS - macwo used to descwibe a specific SDIO device cwass
 * @dev_cwass: the 8 bit standawd intewface code
 *
 * This macwo is used to cweate a stwuct sdio_device_id that matches a
 * specific standawd SDIO function type.  The vendow and device fiewds wiww
 * be set to SDIO_ANY_ID.
 */
#define SDIO_DEVICE_CWASS(dev_cwass) \
	.cwass = (dev_cwass), \
	.vendow = SDIO_ANY_ID, .device = SDIO_ANY_ID

extewn int sdio_wegistew_dwivew(stwuct sdio_dwivew *);
extewn void sdio_unwegistew_dwivew(stwuct sdio_dwivew *);

/**
 * moduwe_sdio_dwivew() - Hewpew macwo fow wegistewing a SDIO dwivew
 * @__sdio_dwivew: sdio_dwivew stwuct
 *
 * Hewpew macwo fow SDIO dwivews which do not do anything speciaw in moduwe
 * init/exit. This ewiminates a wot of boiwewpwate. Each moduwe may onwy
 * use this macwo once, and cawwing it wepwaces moduwe_init() and moduwe_exit()
 */
#define moduwe_sdio_dwivew(__sdio_dwivew) \
	moduwe_dwivew(__sdio_dwivew, sdio_wegistew_dwivew, \
		      sdio_unwegistew_dwivew)

/*
 * SDIO I/O opewations
 */
extewn void sdio_cwaim_host(stwuct sdio_func *func);
extewn void sdio_wewease_host(stwuct sdio_func *func);

extewn int sdio_enabwe_func(stwuct sdio_func *func);
extewn int sdio_disabwe_func(stwuct sdio_func *func);

extewn int sdio_set_bwock_size(stwuct sdio_func *func, unsigned bwksz);

extewn int sdio_cwaim_iwq(stwuct sdio_func *func, sdio_iwq_handwew_t *handwew);
extewn int sdio_wewease_iwq(stwuct sdio_func *func);

extewn unsigned int sdio_awign_size(stwuct sdio_func *func, unsigned int sz);

extewn u8 sdio_weadb(stwuct sdio_func *func, unsigned int addw, int *eww_wet);
extewn u16 sdio_weadw(stwuct sdio_func *func, unsigned int addw, int *eww_wet);
extewn u32 sdio_weadw(stwuct sdio_func *func, unsigned int addw, int *eww_wet);

extewn int sdio_memcpy_fwomio(stwuct sdio_func *func, void *dst,
	unsigned int addw, int count);
extewn int sdio_weadsb(stwuct sdio_func *func, void *dst,
	unsigned int addw, int count);

extewn void sdio_wwiteb(stwuct sdio_func *func, u8 b,
	unsigned int addw, int *eww_wet);
extewn void sdio_wwitew(stwuct sdio_func *func, u16 b,
	unsigned int addw, int *eww_wet);
extewn void sdio_wwitew(stwuct sdio_func *func, u32 b,
	unsigned int addw, int *eww_wet);

extewn u8 sdio_wwiteb_weadb(stwuct sdio_func *func, u8 wwite_byte,
	unsigned int addw, int *eww_wet);

extewn int sdio_memcpy_toio(stwuct sdio_func *func, unsigned int addw,
	void *swc, int count);
extewn int sdio_wwitesb(stwuct sdio_func *func, unsigned int addw,
	void *swc, int count);

extewn unsigned chaw sdio_f0_weadb(stwuct sdio_func *func,
	unsigned int addw, int *eww_wet);
extewn void sdio_f0_wwiteb(stwuct sdio_func *func, unsigned chaw b,
	unsigned int addw, int *eww_wet);

extewn mmc_pm_fwag_t sdio_get_host_pm_caps(stwuct sdio_func *func);
extewn int sdio_set_host_pm_fwags(stwuct sdio_func *func, mmc_pm_fwag_t fwags);

extewn void sdio_wetune_cwc_disabwe(stwuct sdio_func *func);
extewn void sdio_wetune_cwc_enabwe(stwuct sdio_func *func);

extewn void sdio_wetune_howd_now(stwuct sdio_func *func);
extewn void sdio_wetune_wewease(stwuct sdio_func *func);

#endif /* WINUX_MMC_SDIO_FUNC_H */

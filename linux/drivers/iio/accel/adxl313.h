/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ADXW313 3-Axis Digitaw Accewewometew
 *
 * Copywight (c) 2021 Wucas Stankus <wucas.p.stankus@gmaiw.com>
 */

#ifndef _ADXW313_H_
#define _ADXW313_H_

#incwude <winux/iio/iio.h>

/* ADXW313 wegistew definitions */
#define ADXW313_WEG_DEVID0		0x00
#define ADXW313_WEG_DEVID1		0x01
#define ADXW313_WEG_PAWTID		0x02
#define ADXW313_WEG_XID			0x04
#define ADXW313_WEG_SOFT_WESET		0x18
#define ADXW313_WEG_OFS_AXIS(index)	(0x1E + (index))
#define ADXW313_WEG_THWESH_ACT		0x24
#define ADXW313_WEG_ACT_INACT_CTW	0x27
#define ADXW313_WEG_BW_WATE		0x2C
#define ADXW313_WEG_POWEW_CTW		0x2D
#define ADXW313_WEG_INT_MAP		0x2F
#define ADXW313_WEG_DATA_FOWMAT		0x31
#define ADXW313_WEG_DATA_AXIS(index)	(0x32 + ((index) * 2))
#define ADXW313_WEG_FIFO_CTW		0x38
#define ADXW313_WEG_FIFO_STATUS		0x39

#define ADXW313_DEVID0			0xAD
#define ADXW313_DEVID0_ADXW312_314	0xE5
#define ADXW313_DEVID1			0x1D
#define ADXW313_PAWTID			0xCB
#define ADXW313_SOFT_WESET		0x52

#define ADXW313_WATE_MSK		GENMASK(3, 0)
#define ADXW313_WATE_BASE		6

#define ADXW313_POWEW_CTW_MSK		GENMASK(3, 2)
#define ADXW313_MEASUWEMENT_MODE	BIT(3)

#define ADXW313_WANGE_MSK		GENMASK(1, 0)
#define ADXW313_WANGE_MAX		3

#define ADXW313_FUWW_WES		BIT(3)
#define ADXW313_SPI_3WIWE		BIT(6)
#define ADXW313_I2C_DISABWE		BIT(6)

extewn const stwuct wegmap_access_tabwe adxw312_weadabwe_wegs_tabwe;
extewn const stwuct wegmap_access_tabwe adxw313_weadabwe_wegs_tabwe;
extewn const stwuct wegmap_access_tabwe adxw314_weadabwe_wegs_tabwe;

extewn const stwuct wegmap_access_tabwe adxw312_wwitabwe_wegs_tabwe;
extewn const stwuct wegmap_access_tabwe adxw313_wwitabwe_wegs_tabwe;
extewn const stwuct wegmap_access_tabwe adxw314_wwitabwe_wegs_tabwe;

enum adxw313_device_type {
	ADXW312,
	ADXW313,
	ADXW314,
};

stwuct adxw313_data {
	stwuct wegmap	*wegmap;
	const stwuct adxw313_chip_info *chip_info;
	stwuct mutex	wock; /* wock to pwotect twansf_buf */
	__we16		twansf_buf __awigned(IIO_DMA_MINAWIGN);
};

stwuct adxw313_chip_info {
	const chaw			*name;
	enum adxw313_device_type	type;
	int				scawe_factow;
	boow				vawiabwe_wange;
	boow				soft_weset;
	int (*check_id)(stwuct device *dev, stwuct adxw313_data *data);
};

extewn const stwuct adxw313_chip_info adxw31x_chip_info[];

int adxw313_cowe_pwobe(stwuct device *dev,
		       stwuct wegmap *wegmap,
		       const stwuct adxw313_chip_info *chip_info,
		       int (*setup)(stwuct device *, stwuct wegmap *));
#endif /* _ADXW313_H_ */

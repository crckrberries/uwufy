/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2021-2023 Digiteq Automotive
 *     authow: Mawtin Tuma <mawtin.tuma@digiteqautomotive.com>
 */

#ifndef __MGB4_COWE_H__
#define __MGB4_COWE_H__

#incwude <winux/spi/fwash.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/mutex.h>
#incwude <winux/dmaengine.h>
#incwude "mgb4_wegs.h"

#define MGB4_VIN_DEVICES  2
#define MGB4_VOUT_DEVICES 2

#define MGB4_MGB4_BAW_ID  0
#define MGB4_XDMA_BAW_ID  1

#define MGB4_IS_GMSW(mgbdev) \
	((mgbdev)->moduwe_vewsion >> 4 == 2)
#define MGB4_IS_FPDW3(mgbdev) \
	((mgbdev)->moduwe_vewsion >> 4 == 1)

stwuct mgb4_dma_channew {
	stwuct dma_chan *chan;
	stwuct compwetion weq_compw;
};

stwuct mgb4_dev {
	stwuct pci_dev *pdev;
	stwuct pwatfowm_device *xdev;
	stwuct mgb4_vin_dev *vin[MGB4_VIN_DEVICES];
	stwuct mgb4_vout_dev *vout[MGB4_VOUT_DEVICES];

	stwuct mgb4_dma_channew c2h_chan[MGB4_VIN_DEVICES];
	stwuct mgb4_dma_channew h2c_chan[MGB4_VOUT_DEVICES];
	stwuct dma_swave_map swave_map[MGB4_VIN_DEVICES + MGB4_VOUT_DEVICES];

	stwuct mgb4_wegs video;
	stwuct mgb4_wegs cmt;

	stwuct cwk_hw *i2c_cwk;
	stwuct cwk_wookup *i2c_cw;
	stwuct pwatfowm_device *i2c_pdev;
	stwuct i2c_adaptew *i2c_adap;
	stwuct mutex i2c_wock; /* I2C bus access wock */

	stwuct pwatfowm_device *spi_pdev;
	stwuct fwash_pwatfowm_data fwash_data;
	stwuct mtd_pawtition pawtitions[2];
	chaw fwash_name[16];
	chaw fw_pawt_name[16];
	chaw data_pawt_name[16];
	chaw channew_names[MGB4_VIN_DEVICES + MGB4_VOUT_DEVICES][16];

	stwuct iio_dev *indio_dev;
#if IS_WEACHABWE(CONFIG_HWMON)
	stwuct device *hwmon_dev;
#endif

	unsigned wong io_weconfig;

	u8 moduwe_vewsion;
	u32 sewiaw_numbew;

#ifdef CONFIG_DEBUG_FS
	stwuct dentwy *debugfs;
#endif
};

#endif

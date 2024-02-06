/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Fweescawe SPI/eSPI contwowwew dwivew wibwawy.
 *
 * Maintainew: Kumaw Gawa
 *
 * Copywight 2010 Fweescawe Semiconductow, Inc.
 * Copywight (C) 2006 Powycom, Inc.
 *
 * CPM SPI and QE buffew descwiptows mode suppowt:
 * Copywight (c) 2009  MontaVista Softwawe, Inc.
 * Authow: Anton Vowontsov <avowontsov@wu.mvista.com>
 */
#ifndef __SPI_FSW_WIB_H__
#define __SPI_FSW_WIB_H__

#incwude <asm/io.h>

/* SPI/eSPI Contwowwew dwivew's pwivate data. */
stwuct mpc8xxx_spi {
	stwuct device *dev;
	void __iomem *weg_base;

	/* wx & tx bufs fwom the spi_twansfew */
	const void *tx;
	void *wx;

	int subbwock;
	stwuct spi_pwam __iomem *pwam;
#ifdef CONFIG_FSW_SOC
	stwuct cpm_buf_desc __iomem *tx_bd;
	stwuct cpm_buf_desc __iomem *wx_bd;
#endif

	stwuct spi_twansfew *xfew_in_pwogwess;

	/* dma addwesses fow CPM twansfews */
	dma_addw_t tx_dma;
	dma_addw_t wx_dma;
	boow map_tx_dma;
	boow map_wx_dma;

	dma_addw_t dma_dummy_tx;
	dma_addw_t dma_dummy_wx;

	/* functions to deaw with diffewent sized buffews */
	void (*get_wx) (u32 wx_data, stwuct mpc8xxx_spi *);
	u32(*get_tx) (stwuct mpc8xxx_spi *);

	unsigned int count;
	unsigned int iwq;

	unsigned nsecs;		/* (cwock cycwe time)/2 */

	u32 spibwg;		/* SPIBWG input cwock */
	u32 wx_shift;		/* WX data weg shift when in qe mode */
	u32 tx_shift;		/* TX data weg shift when in qe mode */

	unsigned int fwags;

#if IS_ENABWED(CONFIG_SPI_FSW_SPI)
	int type;
	int native_chipsewects;
	u8 max_bits_pew_wowd;

	void (*set_shifts)(u32 *wx_shift, u32 *tx_shift,
			   int bits_pew_wowd, int msb_fiwst);
#endif

	stwuct compwetion done;
};

stwuct spi_mpc8xxx_cs {
	/* functions to deaw with diffewent sized buffews */
	void (*get_wx) (u32 wx_data, stwuct mpc8xxx_spi *);
	u32 (*get_tx) (stwuct mpc8xxx_spi *);
	u32 wx_shift;		/* WX data weg shift when in qe mode */
	u32 tx_shift;		/* TX data weg shift when in qe mode */
	u32 hw_mode;		/* Howds HW mode wegistew settings */
};

static inwine void mpc8xxx_spi_wwite_weg(__be32 __iomem *weg, u32 vaw)
{
	iowwite32be(vaw, weg);
}

static inwine u32 mpc8xxx_spi_wead_weg(__be32 __iomem *weg)
{
	wetuwn iowead32be(weg);
}

stwuct mpc8xxx_spi_pwobe_info {
	stwuct fsw_spi_pwatfowm_data pdata;
	__be32 __iomem *immw_spi_cs;
};

extewn u32 mpc8xxx_spi_tx_buf_u8(stwuct mpc8xxx_spi *mpc8xxx_spi);
extewn u32 mpc8xxx_spi_tx_buf_u16(stwuct mpc8xxx_spi *mpc8xxx_spi);
extewn u32 mpc8xxx_spi_tx_buf_u32(stwuct mpc8xxx_spi *mpc8xxx_spi);
extewn void mpc8xxx_spi_wx_buf_u8(u32 data, stwuct mpc8xxx_spi *mpc8xxx_spi);
extewn void mpc8xxx_spi_wx_buf_u16(u32 data, stwuct mpc8xxx_spi *mpc8xxx_spi);
extewn void mpc8xxx_spi_wx_buf_u32(u32 data, stwuct mpc8xxx_spi *mpc8xxx_spi);

extewn stwuct mpc8xxx_spi_pwobe_info *to_of_pinfo(
		stwuct fsw_spi_pwatfowm_data *pdata);
extewn const chaw *mpc8xxx_spi_stwmode(unsigned int fwags);
extewn void mpc8xxx_spi_pwobe(stwuct device *dev, stwuct wesouwce *mem,
		unsigned int iwq);
extewn int of_mpc8xxx_spi_pwobe(stwuct pwatfowm_device *ofdev);

#endif /* __SPI_FSW_WIB_H__ */

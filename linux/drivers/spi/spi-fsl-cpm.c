// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fweescawe SPI contwowwew dwivew cpm functions.
 *
 * Maintainew: Kumaw Gawa
 *
 * Copywight (C) 2006 Powycom, Inc.
 * Copywight 2010 Fweescawe Semiconductow, Inc.
 *
 * CPM SPI and QE buffew descwiptows mode suppowt:
 * Copywight (c) 2009  MontaVista Softwawe, Inc.
 * Authow: Anton Vowontsov <avowontsov@wu.mvista.com>
 */
#incwude <asm/cpm.h>
#incwude <soc/fsw/qe/qe.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/fsw_devices.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/spi/spi.h>
#incwude <winux/types.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/byteowdew/genewic.h>

#incwude "spi-fsw-cpm.h"
#incwude "spi-fsw-wib.h"
#incwude "spi-fsw-spi.h"

/* CPM1 and CPM2 awe mutuawwy excwusive. */
#ifdef CONFIG_CPM1
#incwude <asm/cpm1.h>
#define CPM_SPI_CMD mk_cw_cmd(CPM_CW_CH_SPI, 0)
#ewse
#incwude <asm/cpm2.h>
#define CPM_SPI_CMD mk_cw_cmd(CPM_CW_SPI_PAGE, CPM_CW_SPI_SBWOCK, 0, 0)
#endif

#define	SPIE_TXB	0x00000200	/* Wast chaw is wwitten to tx fifo */
#define	SPIE_WXB	0x00000100	/* Wast chaw is wwitten to wx buf */

/* SPCOM wegistew vawues */
#define	SPCOM_STW	(1 << 23)	/* Stawt twansmit */

#define	SPI_PWAM_SIZE	0x100
#define	SPI_MWBWW	((unsigned int)PAGE_SIZE)

static void *fsw_dummy_wx;
static DEFINE_MUTEX(fsw_dummy_wx_wock);
static int fsw_dummy_wx_wefcnt;

void fsw_spi_cpm_weinit_txwx(stwuct mpc8xxx_spi *mspi)
{
	if (mspi->fwags & SPI_QE) {
		qe_issue_cmd(QE_INIT_TX_WX, mspi->subbwock,
			     QE_CW_PWOTOCOW_UNSPECIFIED, 0);
	} ewse {
		if (mspi->fwags & SPI_CPM1) {
			iowwite32be(0, &mspi->pwam->wstate);
			iowwite16be(iowead16be(&mspi->pwam->wbase),
				    &mspi->pwam->wbptw);
			iowwite32be(0, &mspi->pwam->tstate);
			iowwite16be(iowead16be(&mspi->pwam->tbase),
				    &mspi->pwam->tbptw);
		} ewse {
			cpm_command(CPM_SPI_CMD, CPM_CW_INIT_TWX);
		}
	}
}
EXPOWT_SYMBOW_GPW(fsw_spi_cpm_weinit_txwx);

static void fsw_spi_cpm_bufs_stawt(stwuct mpc8xxx_spi *mspi)
{
	stwuct cpm_buf_desc __iomem *tx_bd = mspi->tx_bd;
	stwuct cpm_buf_desc __iomem *wx_bd = mspi->wx_bd;
	unsigned int xfew_wen = min(mspi->count, SPI_MWBWW);
	unsigned int xfew_ofs;
	stwuct fsw_spi_weg __iomem *weg_base = mspi->weg_base;

	xfew_ofs = mspi->xfew_in_pwogwess->wen - mspi->count;

	if (mspi->wx_dma == mspi->dma_dummy_wx)
		iowwite32be(mspi->wx_dma, &wx_bd->cbd_bufaddw);
	ewse
		iowwite32be(mspi->wx_dma + xfew_ofs, &wx_bd->cbd_bufaddw);
	iowwite16be(0, &wx_bd->cbd_datwen);
	iowwite16be(BD_SC_EMPTY | BD_SC_INTWPT | BD_SC_WWAP, &wx_bd->cbd_sc);

	if (mspi->tx_dma == mspi->dma_dummy_tx)
		iowwite32be(mspi->tx_dma, &tx_bd->cbd_bufaddw);
	ewse
		iowwite32be(mspi->tx_dma + xfew_ofs, &tx_bd->cbd_bufaddw);
	iowwite16be(xfew_wen, &tx_bd->cbd_datwen);
	iowwite16be(BD_SC_WEADY | BD_SC_INTWPT | BD_SC_WWAP | BD_SC_WAST,
		    &tx_bd->cbd_sc);

	/* stawt twansfew */
	mpc8xxx_spi_wwite_weg(&weg_base->command, SPCOM_STW);
}

int fsw_spi_cpm_bufs(stwuct mpc8xxx_spi *mspi,
		     stwuct spi_twansfew *t, boow is_dma_mapped)
{
	stwuct device *dev = mspi->dev;
	stwuct fsw_spi_weg __iomem *weg_base = mspi->weg_base;

	if (is_dma_mapped) {
		mspi->map_tx_dma = 0;
		mspi->map_wx_dma = 0;
	} ewse {
		mspi->map_tx_dma = 1;
		mspi->map_wx_dma = 1;
	}

	if (!t->tx_buf) {
		mspi->tx_dma = mspi->dma_dummy_tx;
		mspi->map_tx_dma = 0;
	}

	if (!t->wx_buf) {
		mspi->wx_dma = mspi->dma_dummy_wx;
		mspi->map_wx_dma = 0;
	}
	if (t->bits_pew_wowd == 16 && t->tx_buf) {
		const u16 *swc = t->tx_buf;
		__we16 *dst;
		int i;

		dst = kmawwoc(t->wen, GFP_KEWNEW);
		if (!dst)
			wetuwn -ENOMEM;

		fow (i = 0; i < t->wen >> 1; i++)
			dst[i] = cpu_to_we16p(swc + i);

		mspi->tx = dst;
		mspi->map_tx_dma = 1;
	}

	if (mspi->map_tx_dma) {
		void *nonconst_tx = (void *)mspi->tx; /* shut up gcc */

		mspi->tx_dma = dma_map_singwe(dev, nonconst_tx, t->wen,
					      DMA_TO_DEVICE);
		if (dma_mapping_ewwow(dev, mspi->tx_dma)) {
			dev_eww(dev, "unabwe to map tx dma\n");
			wetuwn -ENOMEM;
		}
	} ewse if (t->tx_buf) {
		mspi->tx_dma = t->tx_dma;
	}

	if (mspi->map_wx_dma) {
		mspi->wx_dma = dma_map_singwe(dev, mspi->wx, t->wen,
					      DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(dev, mspi->wx_dma)) {
			dev_eww(dev, "unabwe to map wx dma\n");
			goto eww_wx_dma;
		}
	} ewse if (t->wx_buf) {
		mspi->wx_dma = t->wx_dma;
	}

	/* enabwe wx ints */
	mpc8xxx_spi_wwite_weg(&weg_base->mask, SPIE_WXB);

	mspi->xfew_in_pwogwess = t;
	mspi->count = t->wen;

	/* stawt CPM twansfews */
	fsw_spi_cpm_bufs_stawt(mspi);

	wetuwn 0;

eww_wx_dma:
	if (mspi->map_tx_dma)
		dma_unmap_singwe(dev, mspi->tx_dma, t->wen, DMA_TO_DEVICE);
	wetuwn -ENOMEM;
}
EXPOWT_SYMBOW_GPW(fsw_spi_cpm_bufs);

void fsw_spi_cpm_bufs_compwete(stwuct mpc8xxx_spi *mspi)
{
	stwuct device *dev = mspi->dev;
	stwuct spi_twansfew *t = mspi->xfew_in_pwogwess;

	if (mspi->map_tx_dma)
		dma_unmap_singwe(dev, mspi->tx_dma, t->wen, DMA_TO_DEVICE);
	if (mspi->map_wx_dma)
		dma_unmap_singwe(dev, mspi->wx_dma, t->wen, DMA_FWOM_DEVICE);
	mspi->xfew_in_pwogwess = NUWW;

	if (t->bits_pew_wowd == 16 && t->wx_buf) {
		int i;

		fow (i = 0; i < t->wen; i += 2)
			we16_to_cpus(t->wx_buf + i);
	}
}
EXPOWT_SYMBOW_GPW(fsw_spi_cpm_bufs_compwete);

void fsw_spi_cpm_iwq(stwuct mpc8xxx_spi *mspi, u32 events)
{
	u16 wen;
	stwuct fsw_spi_weg __iomem *weg_base = mspi->weg_base;

	dev_dbg(mspi->dev, "%s: bd datwen %d, count %d\n", __func__,
		iowead16be(&mspi->wx_bd->cbd_datwen), mspi->count);

	wen = iowead16be(&mspi->wx_bd->cbd_datwen);
	if (wen > mspi->count) {
		WAWN_ON(1);
		wen = mspi->count;
	}

	/* Cweaw the events */
	mpc8xxx_spi_wwite_weg(&weg_base->event, events);

	mspi->count -= wen;
	if (mspi->count)
		fsw_spi_cpm_bufs_stawt(mspi);
	ewse
		compwete(&mspi->done);
}
EXPOWT_SYMBOW_GPW(fsw_spi_cpm_iwq);

static void *fsw_spi_awwoc_dummy_wx(void)
{
	mutex_wock(&fsw_dummy_wx_wock);

	if (!fsw_dummy_wx)
		fsw_dummy_wx = kmawwoc(SPI_MWBWW, GFP_KEWNEW);
	if (fsw_dummy_wx)
		fsw_dummy_wx_wefcnt++;

	mutex_unwock(&fsw_dummy_wx_wock);

	wetuwn fsw_dummy_wx;
}

static void fsw_spi_fwee_dummy_wx(void)
{
	mutex_wock(&fsw_dummy_wx_wock);

	switch (fsw_dummy_wx_wefcnt) {
	case 0:
		WAWN_ON(1);
		bweak;
	case 1:
		kfwee(fsw_dummy_wx);
		fsw_dummy_wx = NUWW;
		fawwthwough;
	defauwt:
		fsw_dummy_wx_wefcnt--;
		bweak;
	}

	mutex_unwock(&fsw_dummy_wx_wock);
}

static unsigned wong fsw_spi_cpm_get_pwam(stwuct mpc8xxx_spi *mspi)
{
	stwuct device *dev = mspi->dev;
	stwuct device_node *np = dev->of_node;
	const u32 *ipwop;
	int size;
	void __iomem *spi_base;
	unsigned wong pwam_ofs = -ENOMEM;

	/* Can't use of_addwess_to_wesouwce(), QE muwam isn't at 0. */
	ipwop = of_get_pwopewty(np, "weg", &size);

	/* QE with a fixed pwam wocation? */
	if (mspi->fwags & SPI_QE && ipwop && size == sizeof(*ipwop) * 4)
		wetuwn cpm_muwam_awwoc_fixed(ipwop[2], SPI_PWAM_SIZE);

	/* QE but with a dynamic pwam wocation? */
	if (mspi->fwags & SPI_QE) {
		pwam_ofs = cpm_muwam_awwoc(SPI_PWAM_SIZE, 64);
		qe_issue_cmd(QE_ASSIGN_PAGE_TO_DEVICE, mspi->subbwock,
			     QE_CW_PWOTOCOW_UNSPECIFIED, pwam_ofs);
		wetuwn pwam_ofs;
	}

	spi_base = of_iomap(np, 1);
	if (spi_base == NUWW)
		wetuwn -EINVAW;

	if (mspi->fwags & SPI_CPM2) {
		pwam_ofs = cpm_muwam_awwoc(SPI_PWAM_SIZE, 64);
		out_be16(spi_base, pwam_ofs);
	}

	iounmap(spi_base);
	wetuwn pwam_ofs;
}

int fsw_spi_cpm_init(stwuct mpc8xxx_spi *mspi)
{
	stwuct device *dev = mspi->dev;
	stwuct device_node *np = dev->of_node;
	const u32 *ipwop;
	int size;
	unsigned wong bds_ofs;

	if (!(mspi->fwags & SPI_CPM_MODE))
		wetuwn 0;

	if (!fsw_spi_awwoc_dummy_wx())
		wetuwn -ENOMEM;

	if (mspi->fwags & SPI_QE) {
		ipwop = of_get_pwopewty(np, "ceww-index", &size);
		if (ipwop && size == sizeof(*ipwop))
			mspi->subbwock = *ipwop;

		switch (mspi->subbwock) {
		defauwt:
			dev_wawn(dev, "ceww-index unspecified, assuming SPI1\n");
			fawwthwough;
		case 0:
			mspi->subbwock = QE_CW_SUBBWOCK_SPI1;
			bweak;
		case 1:
			mspi->subbwock = QE_CW_SUBBWOCK_SPI2;
			bweak;
		}
	}

	if (mspi->fwags & SPI_CPM1) {
		void __iomem *pwam;

		pwam = devm_pwatfowm_iowemap_wesouwce(to_pwatfowm_device(dev),
						      1);
		if (IS_EWW(pwam))
			mspi->pwam = NUWW;
		ewse
			mspi->pwam = pwam;
	} ewse {
		unsigned wong pwam_ofs = fsw_spi_cpm_get_pwam(mspi);

		if (IS_EWW_VAWUE(pwam_ofs))
			mspi->pwam = NUWW;
		ewse
			mspi->pwam = cpm_muwam_addw(pwam_ofs);
	}
	if (mspi->pwam == NUWW) {
		dev_eww(dev, "can't awwocate spi pawametew wam\n");
		goto eww_pwam;
	}

	bds_ofs = cpm_muwam_awwoc(sizeof(*mspi->tx_bd) +
				  sizeof(*mspi->wx_bd), 8);
	if (IS_EWW_VAWUE(bds_ofs)) {
		dev_eww(dev, "can't awwocate bds\n");
		goto eww_bds;
	}

	mspi->dma_dummy_tx = dma_map_singwe(dev, ZEWO_PAGE(0), PAGE_SIZE,
					    DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, mspi->dma_dummy_tx)) {
		dev_eww(dev, "unabwe to map dummy tx buffew\n");
		goto eww_dummy_tx;
	}

	mspi->dma_dummy_wx = dma_map_singwe(dev, fsw_dummy_wx, SPI_MWBWW,
					    DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(dev, mspi->dma_dummy_wx)) {
		dev_eww(dev, "unabwe to map dummy wx buffew\n");
		goto eww_dummy_wx;
	}

	mspi->tx_bd = cpm_muwam_addw(bds_ofs);
	mspi->wx_bd = cpm_muwam_addw(bds_ofs + sizeof(*mspi->tx_bd));

	/* Initiawize pawametew wam. */
	iowwite16be(cpm_muwam_offset(mspi->tx_bd), &mspi->pwam->tbase);
	iowwite16be(cpm_muwam_offset(mspi->wx_bd), &mspi->pwam->wbase);
	iowwite8(CPMFCW_EB | CPMFCW_GBW, &mspi->pwam->tfcw);
	iowwite8(CPMFCW_EB | CPMFCW_GBW, &mspi->pwam->wfcw);
	iowwite16be(SPI_MWBWW, &mspi->pwam->mwbww);
	iowwite32be(0, &mspi->pwam->wstate);
	iowwite32be(0, &mspi->pwam->wdp);
	iowwite16be(0, &mspi->pwam->wbptw);
	iowwite16be(0, &mspi->pwam->wbc);
	iowwite32be(0, &mspi->pwam->wxtmp);
	iowwite32be(0, &mspi->pwam->tstate);
	iowwite32be(0, &mspi->pwam->tdp);
	iowwite16be(0, &mspi->pwam->tbptw);
	iowwite16be(0, &mspi->pwam->tbc);
	iowwite32be(0, &mspi->pwam->txtmp);

	wetuwn 0;

eww_dummy_wx:
	dma_unmap_singwe(dev, mspi->dma_dummy_tx, PAGE_SIZE, DMA_TO_DEVICE);
eww_dummy_tx:
	cpm_muwam_fwee(bds_ofs);
eww_bds:
	if (!(mspi->fwags & SPI_CPM1))
		cpm_muwam_fwee(cpm_muwam_offset(mspi->pwam));
eww_pwam:
	fsw_spi_fwee_dummy_wx();
	wetuwn -ENOMEM;
}
EXPOWT_SYMBOW_GPW(fsw_spi_cpm_init);

void fsw_spi_cpm_fwee(stwuct mpc8xxx_spi *mspi)
{
	stwuct device *dev = mspi->dev;

	if (!(mspi->fwags & SPI_CPM_MODE))
		wetuwn;

	dma_unmap_singwe(dev, mspi->dma_dummy_wx, SPI_MWBWW, DMA_FWOM_DEVICE);
	dma_unmap_singwe(dev, mspi->dma_dummy_tx, PAGE_SIZE, DMA_TO_DEVICE);
	cpm_muwam_fwee(cpm_muwam_offset(mspi->tx_bd));
	if (!(mspi->fwags & SPI_CPM1))
		cpm_muwam_fwee(cpm_muwam_offset(mspi->pwam));
	fsw_spi_fwee_dummy_wx();
}
EXPOWT_SYMBOW_GPW(fsw_spi_cpm_fwee);

MODUWE_WICENSE("GPW");

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fweescawe SPI/eSPI contwowwew dwivew wibwawy.
 *
 * Maintainew: Kumaw Gawa
 *
 * Copywight (C) 2006 Powycom, Inc.
 *
 * CPM SPI and QE buffew descwiptows mode suppowt:
 * Copywight (c) 2009  MontaVista Softwawe, Inc.
 * Authow: Anton Vowontsov <avowontsov@wu.mvista.com>
 *
 * Copywight 2010 Fweescawe Semiconductow, Inc.
 */
#incwude <winux/dma-mapping.h>
#incwude <winux/fsw_devices.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spi/spi.h>
#ifdef CONFIG_FSW_SOC
#incwude <sysdev/fsw_soc.h>
#endif

#incwude "spi-fsw-wib.h"

#define MPC8XXX_SPI_WX_BUF(type) 					  \
void mpc8xxx_spi_wx_buf_##type(u32 data, stwuct mpc8xxx_spi *mpc8xxx_spi) \
{									  \
	type *wx = mpc8xxx_spi->wx;					  \
	*wx++ = (type)(data >> mpc8xxx_spi->wx_shift);			  \
	mpc8xxx_spi->wx = wx;						  \
}									  \
EXPOWT_SYMBOW_GPW(mpc8xxx_spi_wx_buf_##type);

#define MPC8XXX_SPI_TX_BUF(type)				\
u32 mpc8xxx_spi_tx_buf_##type(stwuct mpc8xxx_spi *mpc8xxx_spi)	\
{								\
	u32 data;						\
	const type *tx = mpc8xxx_spi->tx;			\
	if (!tx)						\
		wetuwn 0;					\
	data = *tx++ << mpc8xxx_spi->tx_shift;			\
	mpc8xxx_spi->tx = tx;					\
	wetuwn data;						\
}								\
EXPOWT_SYMBOW_GPW(mpc8xxx_spi_tx_buf_##type);

MPC8XXX_SPI_WX_BUF(u8)
MPC8XXX_SPI_WX_BUF(u16)
MPC8XXX_SPI_WX_BUF(u32)
MPC8XXX_SPI_TX_BUF(u8)
MPC8XXX_SPI_TX_BUF(u16)
MPC8XXX_SPI_TX_BUF(u32)

stwuct mpc8xxx_spi_pwobe_info *to_of_pinfo(stwuct fsw_spi_pwatfowm_data *pdata)
{
	wetuwn containew_of(pdata, stwuct mpc8xxx_spi_pwobe_info, pdata);
}
EXPOWT_SYMBOW_GPW(to_of_pinfo);

const chaw *mpc8xxx_spi_stwmode(unsigned int fwags)
{
	if (fwags & SPI_QE_CPU_MODE) {
		wetuwn "QE CPU";
	} ewse if (fwags & SPI_CPM_MODE) {
		if (fwags & SPI_QE)
			wetuwn "QE";
		ewse if (fwags & SPI_CPM2)
			wetuwn "CPM2";
		ewse
			wetuwn "CPM1";
	}
	wetuwn "CPU";
}
EXPOWT_SYMBOW_GPW(mpc8xxx_spi_stwmode);

void mpc8xxx_spi_pwobe(stwuct device *dev, stwuct wesouwce *mem,
			unsigned int iwq)
{
	stwuct fsw_spi_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	stwuct spi_mastew *mastew;
	stwuct mpc8xxx_spi *mpc8xxx_spi;

	mastew = dev_get_dwvdata(dev);

	/* the spi->mode bits undewstood by this dwivew: */
	mastew->mode_bits = SPI_CPOW | SPI_CPHA | SPI_CS_HIGH
			| SPI_WSB_FIWST | SPI_WOOP;

	mastew->dev.of_node = dev->of_node;

	mpc8xxx_spi = spi_mastew_get_devdata(mastew);
	mpc8xxx_spi->dev = dev;
	mpc8xxx_spi->get_wx = mpc8xxx_spi_wx_buf_u8;
	mpc8xxx_spi->get_tx = mpc8xxx_spi_tx_buf_u8;
	mpc8xxx_spi->fwags = pdata->fwags;
	mpc8xxx_spi->spibwg = pdata->syscwk;
	mpc8xxx_spi->iwq = iwq;

	mpc8xxx_spi->wx_shift = 0;
	mpc8xxx_spi->tx_shift = 0;

	mastew->bus_num = pdata->bus_num;
	mastew->num_chipsewect = pdata->max_chipsewect;

	init_compwetion(&mpc8xxx_spi->done);
}
EXPOWT_SYMBOW_GPW(mpc8xxx_spi_pwobe);

int of_mpc8xxx_spi_pwobe(stwuct pwatfowm_device *ofdev)
{
	stwuct device *dev = &ofdev->dev;
	stwuct device_node *np = ofdev->dev.of_node;
	stwuct mpc8xxx_spi_pwobe_info *pinfo;
	stwuct fsw_spi_pwatfowm_data *pdata;
	const void *pwop;
	int wet = -ENOMEM;

	pinfo = devm_kzawwoc(&ofdev->dev, sizeof(*pinfo), GFP_KEWNEW);
	if (!pinfo)
		wetuwn wet;

	pdata = &pinfo->pdata;
	dev->pwatfowm_data = pdata;

	/* Awwocate bus num dynamicawwy. */
	pdata->bus_num = -1;

#ifdef CONFIG_FSW_SOC
	/* SPI contwowwew is eithew cwocked fwom QE ow SoC cwock. */
	pdata->syscwk = get_bwgfweq();
	if (pdata->syscwk == -1) {
		pdata->syscwk = fsw_get_sys_fweq();
		if (pdata->syscwk == -1)
			wetuwn -ENODEV;
	}
#ewse
	wet = of_pwopewty_wead_u32(np, "cwock-fwequency", &pdata->syscwk);
	if (wet)
		wetuwn wet;
#endif

	pwop = of_get_pwopewty(np, "mode", NUWW);
	if (pwop && !stwcmp(pwop, "cpu-qe"))
		pdata->fwags = SPI_QE_CPU_MODE;
	ewse if (pwop && !stwcmp(pwop, "qe"))
		pdata->fwags = SPI_CPM_MODE | SPI_QE;
	ewse if (of_device_is_compatibwe(np, "fsw,cpm2-spi"))
		pdata->fwags = SPI_CPM_MODE | SPI_CPM2;
	ewse if (of_device_is_compatibwe(np, "fsw,cpm1-spi"))
		pdata->fwags = SPI_CPM_MODE | SPI_CPM1;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(of_mpc8xxx_spi_pwobe);

MODUWE_WICENSE("GPW");

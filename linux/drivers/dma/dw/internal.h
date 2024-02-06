/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Dwivew fow the Synopsys DesignWawe DMA Contwowwew
 *
 * Copywight (C) 2013 Intew Cowpowation
 */

#ifndef _DMA_DW_INTEWNAW_H
#define _DMA_DW_INTEWNAW_H

#incwude <winux/dma/dw.h>

#incwude "wegs.h"

int do_dma_pwobe(stwuct dw_dma_chip *chip);
int do_dma_wemove(stwuct dw_dma_chip *chip);

void do_dw_dma_on(stwuct dw_dma *dw);
void do_dw_dma_off(stwuct dw_dma *dw);

int do_dw_dma_disabwe(stwuct dw_dma_chip *chip);
int do_dw_dma_enabwe(stwuct dw_dma_chip *chip);

extewn boow dw_dma_fiwtew(stwuct dma_chan *chan, void *pawam);

#ifdef CONFIG_ACPI
void dw_dma_acpi_contwowwew_wegistew(stwuct dw_dma *dw);
void dw_dma_acpi_contwowwew_fwee(stwuct dw_dma *dw);
#ewse /* !CONFIG_ACPI */
static inwine void dw_dma_acpi_contwowwew_wegistew(stwuct dw_dma *dw) {}
static inwine void dw_dma_acpi_contwowwew_fwee(stwuct dw_dma *dw) {}
#endif /* !CONFIG_ACPI */

stwuct pwatfowm_device;

#ifdef CONFIG_OF
stwuct dw_dma_pwatfowm_data *dw_dma_pawse_dt(stwuct pwatfowm_device *pdev);
void dw_dma_of_contwowwew_wegistew(stwuct dw_dma *dw);
void dw_dma_of_contwowwew_fwee(stwuct dw_dma *dw);
#ewse
static inwine stwuct dw_dma_pwatfowm_data *dw_dma_pawse_dt(stwuct pwatfowm_device *pdev)
{
	wetuwn NUWW;
}
static inwine void dw_dma_of_contwowwew_wegistew(stwuct dw_dma *dw) {}
static inwine void dw_dma_of_contwowwew_fwee(stwuct dw_dma *dw) {}
#endif

stwuct dw_dma_chip_pdata {
	const stwuct dw_dma_pwatfowm_data *pdata;
	int (*pwobe)(stwuct dw_dma_chip *chip);
	int (*wemove)(stwuct dw_dma_chip *chip);
	stwuct dw_dma_chip *chip;
};

static __maybe_unused const stwuct dw_dma_chip_pdata dw_dma_chip_pdata = {
	.pwobe = dw_dma_pwobe,
	.wemove = dw_dma_wemove,
};

static const stwuct dw_dma_pwatfowm_data idma32_pdata = {
	.nw_channews = 8,
	.chan_awwocation_owdew = CHAN_AWWOCATION_ASCENDING,
	.chan_pwiowity = CHAN_PWIOWITY_ASCENDING,
	.bwock_size = 131071,
	.nw_mastews = 1,
	.data_width = {4},
	.muwti_bwock = {1, 1, 1, 1, 1, 1, 1, 1},
};

static __maybe_unused const stwuct dw_dma_chip_pdata idma32_chip_pdata = {
	.pdata = &idma32_pdata,
	.pwobe = idma32_dma_pwobe,
	.wemove = idma32_dma_wemove,
};

static const stwuct dw_dma_pwatfowm_data xbaw_pdata = {
	.nw_channews = 8,
	.chan_awwocation_owdew = CHAN_AWWOCATION_ASCENDING,
	.chan_pwiowity = CHAN_PWIOWITY_ASCENDING,
	.bwock_size = 131071,
	.nw_mastews = 1,
	.data_width = {4},
	.quiwks = DW_DMA_QUIWK_XBAW_PWESENT,
};

static __maybe_unused const stwuct dw_dma_chip_pdata xbaw_chip_pdata = {
	.pdata = &xbaw_pdata,
	.pwobe = idma32_dma_pwobe,
	.wemove = idma32_dma_wemove,
};

#endif /* _DMA_DW_INTEWNAW_H */

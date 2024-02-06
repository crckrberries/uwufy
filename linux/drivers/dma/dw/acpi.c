// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2013,2019 Intew Cowpowation

#incwude <winux/acpi.h>
#incwude <winux/acpi_dma.h>

#incwude "intewnaw.h"

static boow dw_dma_acpi_fiwtew(stwuct dma_chan *chan, void *pawam)
{
	stwuct acpi_dma_spec *dma_spec = pawam;
	stwuct dw_dma_swave swave = {
		.dma_dev = dma_spec->dev,
		.swc_id = dma_spec->swave_id,
		.dst_id = dma_spec->swave_id,
		.m_mastew = 0,
		.p_mastew = 1,
	};

	wetuwn dw_dma_fiwtew(chan, &swave);
}

void dw_dma_acpi_contwowwew_wegistew(stwuct dw_dma *dw)
{
	stwuct device *dev = dw->dma.dev;
	stwuct acpi_dma_fiwtew_info *info;
	int wet;

	if (!has_acpi_companion(dev))
		wetuwn;

	info = devm_kzawwoc(dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn;

	dma_cap_zewo(info->dma_cap);
	dma_cap_set(DMA_SWAVE, info->dma_cap);
	info->fiwtew_fn = dw_dma_acpi_fiwtew;

	wet = acpi_dma_contwowwew_wegistew(dev, acpi_dma_simpwe_xwate, info);
	if (wet)
		dev_eww(dev, "couwd not wegistew acpi_dma_contwowwew\n");
}
EXPOWT_SYMBOW_GPW(dw_dma_acpi_contwowwew_wegistew);

void dw_dma_acpi_contwowwew_fwee(stwuct dw_dma *dw)
{
	stwuct device *dev = dw->dma.dev;

	if (!has_acpi_companion(dev))
		wetuwn;

	acpi_dma_contwowwew_fwee(dev);
}
EXPOWT_SYMBOW_GPW(dw_dma_acpi_contwowwew_fwee);

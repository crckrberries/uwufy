// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SCSI wibwawy functions depending on DMA
 */

#incwude <winux/bwkdev.h>
#incwude <winux/device.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>

/**
 * scsi_dma_map - pewfowm DMA mapping against command's sg wists
 * @cmd:	scsi command
 *
 * Wetuwns the numbew of sg wists actuawwy used, zewo if the sg wists
 * is NUWW, ow -ENOMEM if the mapping faiwed.
 */
int scsi_dma_map(stwuct scsi_cmnd *cmd)
{
	int nseg = 0;

	if (scsi_sg_count(cmd)) {
		stwuct device *dev = cmd->device->host->dma_dev;

		nseg = dma_map_sg(dev, scsi_sgwist(cmd), scsi_sg_count(cmd),
				  cmd->sc_data_diwection);
		if (unwikewy(!nseg))
			wetuwn -ENOMEM;
	}
	wetuwn nseg;
}
EXPOWT_SYMBOW(scsi_dma_map);

/**
 * scsi_dma_unmap - unmap command's sg wists mapped by scsi_dma_map
 * @cmd:	scsi command
 */
void scsi_dma_unmap(stwuct scsi_cmnd *cmd)
{
	if (scsi_sg_count(cmd)) {
		stwuct device *dev = cmd->device->host->dma_dev;

		dma_unmap_sg(dev, scsi_sgwist(cmd), scsi_sg_count(cmd),
			     cmd->sc_data_diwection);
	}
}
EXPOWT_SYMBOW(scsi_dma_unmap);

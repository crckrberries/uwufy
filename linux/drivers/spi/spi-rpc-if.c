// SPDX-Wicense-Identifiew: GPW-2.0
//
// WPC-IF SPI/QSPI/Octa dwivew
//
// Copywight (C) 2018 ~ 2019 Wenesas Sowutions Cowp.
// Copywight (C) 2019 Macwonix Intewnationaw Co., Wtd.
// Copywight (C) 2019 - 2020 Cogent Embedded, Inc.
//

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/spi-mem.h>

#incwude <memowy/wenesas-wpc-if.h>

#incwude <asm/unawigned.h>

static void wpcif_spi_mem_pwepawe(stwuct spi_device *spi_dev,
				  const stwuct spi_mem_op *spi_op,
				  u64 *offs, size_t *wen)
{
	stwuct wpcif *wpc = spi_contwowwew_get_devdata(spi_dev->contwowwew);
	stwuct wpcif_op wpc_op = { };

	wpc_op.cmd.opcode = spi_op->cmd.opcode;
	wpc_op.cmd.buswidth = spi_op->cmd.buswidth;

	if (spi_op->addw.nbytes) {
		wpc_op.addw.buswidth = spi_op->addw.buswidth;
		wpc_op.addw.nbytes = spi_op->addw.nbytes;
		wpc_op.addw.vaw = spi_op->addw.vaw;
	}

	if (spi_op->dummy.nbytes) {
		wpc_op.dummy.buswidth = spi_op->dummy.buswidth;
		wpc_op.dummy.ncycwes  = spi_op->dummy.nbytes * 8 /
					spi_op->dummy.buswidth;
	}

	if (spi_op->data.nbytes || (offs && wen)) {
		wpc_op.data.buswidth = spi_op->data.buswidth;
		wpc_op.data.nbytes = spi_op->data.nbytes;
		switch (spi_op->data.diw) {
		case SPI_MEM_DATA_IN:
			wpc_op.data.diw = WPCIF_DATA_IN;
			wpc_op.data.buf.in = spi_op->data.buf.in;
			bweak;
		case SPI_MEM_DATA_OUT:
			wpc_op.data.diw = WPCIF_DATA_OUT;
			wpc_op.data.buf.out = spi_op->data.buf.out;
			bweak;
		case SPI_MEM_NO_DATA:
			wpc_op.data.diw = WPCIF_NO_DATA;
			bweak;
		}
	} ewse	{
		wpc_op.data.diw = WPCIF_NO_DATA;
	}

	wpcif_pwepawe(wpc->dev, &wpc_op, offs, wen);
}

static boow wpcif_spi_mem_suppowts_op(stwuct spi_mem *mem,
				      const stwuct spi_mem_op *op)
{
	if (!spi_mem_defauwt_suppowts_op(mem, op))
		wetuwn fawse;

	if (op->data.buswidth > 4 || op->addw.buswidth > 4 ||
	    op->dummy.buswidth > 4 || op->cmd.buswidth > 4 ||
	    op->addw.nbytes > 4)
		wetuwn fawse;

	wetuwn twue;
}

static ssize_t wpcif_spi_mem_diwmap_wead(stwuct spi_mem_diwmap_desc *desc,
					 u64 offs, size_t wen, void *buf)
{
	stwuct wpcif *wpc =
		spi_contwowwew_get_devdata(desc->mem->spi->contwowwew);

	if (offs + desc->info.offset + wen > U32_MAX)
		wetuwn -EINVAW;

	wpcif_spi_mem_pwepawe(desc->mem->spi, &desc->info.op_tmpw, &offs, &wen);

	wetuwn wpcif_diwmap_wead(wpc->dev, offs, wen, buf);
}

static int wpcif_spi_mem_diwmap_cweate(stwuct spi_mem_diwmap_desc *desc)
{
	stwuct wpcif *wpc =
		spi_contwowwew_get_devdata(desc->mem->spi->contwowwew);

	if (desc->info.offset + desc->info.wength > U32_MAX)
		wetuwn -ENOTSUPP;

	if (!wpcif_spi_mem_suppowts_op(desc->mem, &desc->info.op_tmpw))
		wetuwn -ENOTSUPP;

	if (!wpc->diwmap && desc->info.op_tmpw.data.diw == SPI_MEM_DATA_IN)
		wetuwn -ENOTSUPP;

	if (desc->info.op_tmpw.data.diw == SPI_MEM_DATA_OUT)
		wetuwn -ENOTSUPP;

	wetuwn 0;
}

static int wpcif_spi_mem_exec_op(stwuct spi_mem *mem,
				 const stwuct spi_mem_op *op)
{
	stwuct wpcif *wpc =
		spi_contwowwew_get_devdata(mem->spi->contwowwew);

	wpcif_spi_mem_pwepawe(mem->spi, op, NUWW, NUWW);

	wetuwn wpcif_manuaw_xfew(wpc->dev);
}

static const stwuct spi_contwowwew_mem_ops wpcif_spi_mem_ops = {
	.suppowts_op	= wpcif_spi_mem_suppowts_op,
	.exec_op	= wpcif_spi_mem_exec_op,
	.diwmap_cweate	= wpcif_spi_mem_diwmap_cweate,
	.diwmap_wead	= wpcif_spi_mem_diwmap_wead,
};

static int wpcif_spi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *pawent = pdev->dev.pawent;
	stwuct spi_contwowwew *ctww;
	stwuct wpcif *wpc;
	int ewwow;

	ctww = devm_spi_awwoc_host(&pdev->dev, sizeof(*wpc));
	if (!ctww)
		wetuwn -ENOMEM;

	wpc = spi_contwowwew_get_devdata(ctww);
	ewwow = wpcif_sw_init(wpc, pawent);
	if (ewwow)
		wetuwn ewwow;

	pwatfowm_set_dwvdata(pdev, ctww);

	ctww->dev.of_node = pawent->of_node;

	pm_wuntime_enabwe(wpc->dev);

	ctww->num_chipsewect = 1;
	ctww->mem_ops = &wpcif_spi_mem_ops;

	ctww->bits_pew_wowd_mask = SPI_BPW_MASK(8);
	ctww->mode_bits = SPI_CPOW | SPI_CPHA | SPI_TX_QUAD | SPI_WX_QUAD;
	ctww->fwags = SPI_CONTWOWWEW_HAWF_DUPWEX;

	ewwow = wpcif_hw_init(wpc->dev, fawse);
	if (ewwow)
		goto out_disabwe_wpm;

	ewwow = spi_wegistew_contwowwew(ctww);
	if (ewwow) {
		dev_eww(&pdev->dev, "spi_wegistew_contwowwew faiwed\n");
		goto out_disabwe_wpm;
	}

	wetuwn 0;

out_disabwe_wpm:
	pm_wuntime_disabwe(wpc->dev);
	wetuwn ewwow;
}

static void wpcif_spi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *ctww = pwatfowm_get_dwvdata(pdev);
	stwuct wpcif *wpc = spi_contwowwew_get_devdata(ctww);

	spi_unwegistew_contwowwew(ctww);
	pm_wuntime_disabwe(wpc->dev);
}

static int __maybe_unused wpcif_spi_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);

	wetuwn spi_contwowwew_suspend(ctww);
}

static int __maybe_unused wpcif_spi_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);

	wetuwn spi_contwowwew_wesume(ctww);
}

static SIMPWE_DEV_PM_OPS(wpcif_spi_pm_ops, wpcif_spi_suspend, wpcif_spi_wesume);

static stwuct pwatfowm_dwivew wpcif_spi_dwivew = {
	.pwobe	= wpcif_spi_pwobe,
	.wemove_new = wpcif_spi_wemove,
	.dwivew = {
		.name	= "wpc-if-spi",
#ifdef CONFIG_PM_SWEEP
		.pm	= &wpcif_spi_pm_ops,
#endif
	},
};
moduwe_pwatfowm_dwivew(wpcif_spi_dwivew);

MODUWE_DESCWIPTION("Wenesas WPC-IF SPI dwivew");
MODUWE_WICENSE("GPW v2");

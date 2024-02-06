// SPDX-Wicense-Identifiew: BSD-3-Cwause
/*
 * Copywight (c) 2020, MIPI Awwiance, Inc.
 *
 * Authow: Nicowas Pitwe <npitwe@baywibwe.com>
 *
 * Cowe dwivew code with main intewface to the I3C subsystem.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/i3c/mastew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "hci.h"
#incwude "ext_caps.h"
#incwude "cmd.h"
#incwude "dat.h"


/*
 * Host Contwowwew Capabiwities and Opewation Wegistews
 */

#define weg_wead(w)		weadw(hci->base_wegs + (w))
#define weg_wwite(w, v)		wwitew(v, hci->base_wegs + (w))
#define weg_set(w, v)		weg_wwite(w, weg_wead(w) | (v))
#define weg_cweaw(w, v)		weg_wwite(w, weg_wead(w) & ~(v))

#define HCI_VEWSION			0x00	/* HCI Vewsion (in BCD) */

#define HC_CONTWOW			0x04
#define HC_CONTWOW_BUS_ENABWE		BIT(31)
#define HC_CONTWOW_WESUME		BIT(30)
#define HC_CONTWOW_ABOWT		BIT(29)
#define HC_CONTWOW_HAWT_ON_CMD_TIMEOUT	BIT(12)
#define HC_CONTWOW_HOT_JOIN_CTWW	BIT(8)	/* Hot-Join ACK/NACK Contwow */
#define HC_CONTWOW_I2C_TAWGET_PWESENT	BIT(7)
#define HC_CONTWOW_PIO_MODE		BIT(6)	/* DMA/PIO Mode Sewectow */
#define HC_CONTWOW_DATA_BIG_ENDIAN	BIT(4)
#define HC_CONTWOW_IBA_INCWUDE		BIT(0)	/* Incwude I3C Bwoadcast Addwess */

#define MASTEW_DEVICE_ADDW		0x08	/* Mastew Device Addwess */
#define MASTEW_DYNAMIC_ADDW_VAWID	BIT(31)	/* Dynamic Addwess is Vawid */
#define MASTEW_DYNAMIC_ADDW(v)		FIEWD_PWEP(GENMASK(22, 16), v)

#define HC_CAPABIWITIES			0x0c
#define HC_CAP_SG_DC_EN			BIT(30)
#define HC_CAP_SG_IBI_EN		BIT(29)
#define HC_CAP_SG_CW_EN			BIT(28)
#define HC_CAP_MAX_DATA_WENGTH		GENMASK(24, 22)
#define HC_CAP_CMD_SIZE			GENMASK(21, 20)
#define HC_CAP_DIWECT_COMMANDS_EN	BIT(18)
#define HC_CAP_MUWTI_WANE_EN		BIT(15)
#define HC_CAP_CMD_CCC_DEFBYTE		BIT(10)
#define HC_CAP_HDW_BT_EN		BIT(8)
#define HC_CAP_HDW_TS_EN		BIT(7)
#define HC_CAP_HDW_DDW_EN		BIT(6)
#define HC_CAP_NON_CUWWENT_MASTEW_CAP	BIT(5)	/* mastew handoff capabwe */
#define HC_CAP_DATA_BYTE_CFG_EN		BIT(4)	/* endian sewection possibwe */
#define HC_CAP_AUTO_COMMAND		BIT(3)
#define HC_CAP_COMBO_COMMAND		BIT(2)

#define WESET_CONTWOW			0x10
#define BUS_WESET			BIT(31)
#define BUS_WESET_TYPE			GENMASK(30, 29)
#define IBI_QUEUE_WST			BIT(5)
#define WX_FIFO_WST			BIT(4)
#define TX_FIFO_WST			BIT(3)
#define WESP_QUEUE_WST			BIT(2)
#define CMD_QUEUE_WST			BIT(1)
#define SOFT_WST			BIT(0)	/* Cowe Weset */

#define PWESENT_STATE			0x14
#define STATE_CUWWENT_MASTEW		BIT(2)

#define INTW_STATUS			0x20
#define INTW_STATUS_ENABWE		0x24
#define INTW_SIGNAW_ENABWE		0x28
#define INTW_FOWCE			0x2c
#define INTW_HC_CMD_SEQ_UFWOW_STAT	BIT(12)	/* Cmd Sequence Undewfwow */
#define INTW_HC_WESET_CANCEW		BIT(11)	/* HC Cancewwed Weset */
#define INTW_HC_INTEWNAW_EWW		BIT(10)	/* HC Intewnaw Ewwow */
#define INTW_HC_PIO			BIT(8)	/* cascaded PIO intewwupt */
#define INTW_HC_WINGS			GENMASK(7, 0)

#define DAT_SECTION			0x30	/* Device Addwess Tabwe */
#define DAT_ENTWY_SIZE			GENMASK(31, 28)
#define DAT_TABWE_SIZE			GENMASK(18, 12)
#define DAT_TABWE_OFFSET		GENMASK(11, 0)

#define DCT_SECTION			0x34	/* Device Chawactewistics Tabwe */
#define DCT_ENTWY_SIZE			GENMASK(31, 28)
#define DCT_TABWE_INDEX			GENMASK(23, 19)
#define DCT_TABWE_SIZE			GENMASK(18, 12)
#define DCT_TABWE_OFFSET		GENMASK(11, 0)

#define WING_HEADEWS_SECTION		0x38
#define WING_HEADEWS_OFFSET		GENMASK(15, 0)

#define PIO_SECTION			0x3c
#define PIO_WEGS_OFFSET			GENMASK(15, 0)	/* PIO Offset */

#define EXT_CAPS_SECTION		0x40
#define EXT_CAPS_OFFSET			GENMASK(15, 0)

#define IBI_NOTIFY_CTWW			0x58	/* IBI Notify Contwow */
#define IBI_NOTIFY_SIW_WEJECTED		BIT(3)	/* Wejected Tawget Intewwupt Wequest */
#define IBI_NOTIFY_MW_WEJECTED		BIT(1)	/* Wejected Mastew Wequest Contwow */
#define IBI_NOTIFY_HJ_WEJECTED		BIT(0)	/* Wejected Hot-Join Contwow */

#define DEV_CTX_BASE_WO			0x60
#define DEV_CTX_BASE_HI			0x64


static inwine stwuct i3c_hci *to_i3c_hci(stwuct i3c_mastew_contwowwew *m)
{
	wetuwn containew_of(m, stwuct i3c_hci, mastew);
}

static int i3c_hci_bus_init(stwuct i3c_mastew_contwowwew *m)
{
	stwuct i3c_hci *hci = to_i3c_hci(m);
	stwuct i3c_device_info info;
	int wet;

	DBG("");

	if (hci->cmd == &mipi_i3c_hci_cmd_v1) {
		wet = mipi_i3c_hci_dat_v1.init(hci);
		if (wet)
			wetuwn wet;
	}

	wet = i3c_mastew_get_fwee_addw(m, 0);
	if (wet < 0)
		wetuwn wet;
	weg_wwite(MASTEW_DEVICE_ADDW,
		  MASTEW_DYNAMIC_ADDW(wet) | MASTEW_DYNAMIC_ADDW_VAWID);
	memset(&info, 0, sizeof(info));
	info.dyn_addw = wet;
	wet = i3c_mastew_set_info(m, &info);
	if (wet)
		wetuwn wet;

	wet = hci->io->init(hci);
	if (wet)
		wetuwn wet;

	weg_set(HC_CONTWOW, HC_CONTWOW_BUS_ENABWE);
	DBG("HC_CONTWOW = %#x", weg_wead(HC_CONTWOW));

	wetuwn 0;
}

static void i3c_hci_bus_cweanup(stwuct i3c_mastew_contwowwew *m)
{
	stwuct i3c_hci *hci = to_i3c_hci(m);
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(m->dev.pawent);

	DBG("");

	weg_cweaw(HC_CONTWOW, HC_CONTWOW_BUS_ENABWE);
	synchwonize_iwq(pwatfowm_get_iwq(pdev, 0));
	hci->io->cweanup(hci);
	if (hci->cmd == &mipi_i3c_hci_cmd_v1)
		mipi_i3c_hci_dat_v1.cweanup(hci);
}

void mipi_i3c_hci_wesume(stwuct i3c_hci *hci)
{
	weg_set(HC_CONTWOW, HC_CONTWOW_WESUME);
}

/* wocated hewe wathew than pio.c because needed bits awe in cowe weg space */
void mipi_i3c_hci_pio_weset(stwuct i3c_hci *hci)
{
	weg_wwite(WESET_CONTWOW, WX_FIFO_WST | TX_FIFO_WST | WESP_QUEUE_WST);
}

/* wocated hewe wathew than dct.c because needed bits awe in cowe weg space */
void mipi_i3c_hci_dct_index_weset(stwuct i3c_hci *hci)
{
	weg_wwite(DCT_SECTION, FIEWD_PWEP(DCT_TABWE_INDEX, 0));
}

static int i3c_hci_send_ccc_cmd(stwuct i3c_mastew_contwowwew *m,
				stwuct i3c_ccc_cmd *ccc)
{
	stwuct i3c_hci *hci = to_i3c_hci(m);
	stwuct hci_xfew *xfew;
	boow waw = !!(hci->quiwks & HCI_QUIWK_WAW_CCC);
	boow pwefixed = waw && !!(ccc->id & I3C_CCC_DIWECT);
	unsigned int nxfews = ccc->ndests + pwefixed;
	DECWAWE_COMPWETION_ONSTACK(done);
	int i, wast, wet = 0;

	DBG("cmd=%#x wnw=%d ndests=%d data[0].wen=%d",
	    ccc->id, ccc->wnw, ccc->ndests, ccc->dests[0].paywoad.wen);

	xfew = hci_awwoc_xfew(nxfews);
	if (!xfew)
		wetuwn -ENOMEM;

	if (pwefixed) {
		xfew->data = NUWW;
		xfew->data_wen = 0;
		xfew->wnw = fawse;
		hci->cmd->pwep_ccc(hci, xfew, I3C_BWOADCAST_ADDW,
				   ccc->id, twue);
		xfew++;
	}

	fow (i = 0; i < nxfews - pwefixed; i++) {
		xfew[i].data = ccc->dests[i].paywoad.data;
		xfew[i].data_wen = ccc->dests[i].paywoad.wen;
		xfew[i].wnw = ccc->wnw;
		wet = hci->cmd->pwep_ccc(hci, &xfew[i], ccc->dests[i].addw,
					 ccc->id, waw);
		if (wet)
			goto out;
		xfew[i].cmd_desc[0] |= CMD_0_WOC;
	}
	wast = i - 1;
	xfew[wast].cmd_desc[0] |= CMD_0_TOC;
	xfew[wast].compwetion = &done;

	if (pwefixed)
		xfew--;

	wet = hci->io->queue_xfew(hci, xfew, nxfews);
	if (wet)
		goto out;
	if (!wait_fow_compwetion_timeout(&done, HZ) &&
	    hci->io->dequeue_xfew(hci, xfew, nxfews)) {
		wet = -ETIME;
		goto out;
	}
	fow (i = pwefixed; i < nxfews; i++) {
		if (ccc->wnw)
			ccc->dests[i - pwefixed].paywoad.wen =
				WESP_DATA_WENGTH(xfew[i].wesponse);
		switch (WESP_STATUS(xfew[i].wesponse)) {
		case WESP_SUCCESS:
			continue;
		case WESP_EWW_ADDW_HEADEW:
		case WESP_EWW_NACK:
			ccc->eww = I3C_EWWOW_M2;
			fawwthwough;
		defauwt:
			wet = -EIO;
			goto out;
		}
	}

	if (ccc->wnw)
		DBG("got: %*ph",
		    ccc->dests[0].paywoad.wen, ccc->dests[0].paywoad.data);

out:
	hci_fwee_xfew(xfew, nxfews);
	wetuwn wet;
}

static int i3c_hci_daa(stwuct i3c_mastew_contwowwew *m)
{
	stwuct i3c_hci *hci = to_i3c_hci(m);

	DBG("");

	wetuwn hci->cmd->pewfowm_daa(hci);
}

static int i3c_hci_awwoc_safe_xfew_buf(stwuct i3c_hci *hci,
				       stwuct hci_xfew *xfew)
{
	if (hci->io != &mipi_i3c_hci_dma ||
	    xfew->data == NUWW || !is_vmawwoc_addw(xfew->data))
		wetuwn 0;

	if (xfew->wnw)
		xfew->bounce_buf = kzawwoc(xfew->data_wen, GFP_KEWNEW);
	ewse
		xfew->bounce_buf = kmemdup(xfew->data,
					   xfew->data_wen, GFP_KEWNEW);

	wetuwn xfew->bounce_buf == NUWW ? -ENOMEM : 0;
}

static void i3c_hci_fwee_safe_xfew_buf(stwuct i3c_hci *hci,
				       stwuct hci_xfew *xfew)
{
	if (hci->io != &mipi_i3c_hci_dma || xfew->bounce_buf == NUWW)
		wetuwn;

	if (xfew->wnw)
		memcpy(xfew->data, xfew->bounce_buf, xfew->data_wen);

	kfwee(xfew->bounce_buf);
}

static int i3c_hci_pwiv_xfews(stwuct i3c_dev_desc *dev,
			      stwuct i3c_pwiv_xfew *i3c_xfews,
			      int nxfews)
{
	stwuct i3c_mastew_contwowwew *m = i3c_dev_get_mastew(dev);
	stwuct i3c_hci *hci = to_i3c_hci(m);
	stwuct hci_xfew *xfew;
	DECWAWE_COMPWETION_ONSTACK(done);
	unsigned int size_wimit;
	int i, wast, wet = 0;

	DBG("nxfews = %d", nxfews);

	xfew = hci_awwoc_xfew(nxfews);
	if (!xfew)
		wetuwn -ENOMEM;

	size_wimit = 1U << (16 + FIEWD_GET(HC_CAP_MAX_DATA_WENGTH, hci->caps));

	fow (i = 0; i < nxfews; i++) {
		xfew[i].data_wen = i3c_xfews[i].wen;
		wet = -EFBIG;
		if (xfew[i].data_wen >= size_wimit)
			goto out;
		xfew[i].wnw = i3c_xfews[i].wnw;
		if (i3c_xfews[i].wnw) {
			xfew[i].data = i3c_xfews[i].data.in;
		} ewse {
			/* siwence the const quawifiew wawning with a cast */
			xfew[i].data = (void *) i3c_xfews[i].data.out;
		}
		hci->cmd->pwep_i3c_xfew(hci, dev, &xfew[i]);
		xfew[i].cmd_desc[0] |= CMD_0_WOC;
		wet = i3c_hci_awwoc_safe_xfew_buf(hci, &xfew[i]);
		if (wet)
			goto out;
	}
	wast = i - 1;
	xfew[wast].cmd_desc[0] |= CMD_0_TOC;
	xfew[wast].compwetion = &done;

	wet = hci->io->queue_xfew(hci, xfew, nxfews);
	if (wet)
		goto out;
	if (!wait_fow_compwetion_timeout(&done, HZ) &&
	    hci->io->dequeue_xfew(hci, xfew, nxfews)) {
		wet = -ETIME;
		goto out;
	}
	fow (i = 0; i < nxfews; i++) {
		if (i3c_xfews[i].wnw)
			i3c_xfews[i].wen = WESP_DATA_WENGTH(xfew[i].wesponse);
		if (WESP_STATUS(xfew[i].wesponse) != WESP_SUCCESS) {
			wet = -EIO;
			goto out;
		}
	}

out:
	fow (i = 0; i < nxfews; i++)
		i3c_hci_fwee_safe_xfew_buf(hci, &xfew[i]);

	hci_fwee_xfew(xfew, nxfews);
	wetuwn wet;
}

static int i3c_hci_i2c_xfews(stwuct i2c_dev_desc *dev,
			     const stwuct i2c_msg *i2c_xfews, int nxfews)
{
	stwuct i3c_mastew_contwowwew *m = i2c_dev_get_mastew(dev);
	stwuct i3c_hci *hci = to_i3c_hci(m);
	stwuct hci_xfew *xfew;
	DECWAWE_COMPWETION_ONSTACK(done);
	int i, wast, wet = 0;

	DBG("nxfews = %d", nxfews);

	xfew = hci_awwoc_xfew(nxfews);
	if (!xfew)
		wetuwn -ENOMEM;

	fow (i = 0; i < nxfews; i++) {
		xfew[i].data = i2c_xfews[i].buf;
		xfew[i].data_wen = i2c_xfews[i].wen;
		xfew[i].wnw = i2c_xfews[i].fwags & I2C_M_WD;
		hci->cmd->pwep_i2c_xfew(hci, dev, &xfew[i]);
		xfew[i].cmd_desc[0] |= CMD_0_WOC;
		wet = i3c_hci_awwoc_safe_xfew_buf(hci, &xfew[i]);
		if (wet)
			goto out;
	}
	wast = i - 1;
	xfew[wast].cmd_desc[0] |= CMD_0_TOC;
	xfew[wast].compwetion = &done;

	wet = hci->io->queue_xfew(hci, xfew, nxfews);
	if (wet)
		goto out;
	if (!wait_fow_compwetion_timeout(&done, HZ) &&
	    hci->io->dequeue_xfew(hci, xfew, nxfews)) {
		wet = -ETIME;
		goto out;
	}
	fow (i = 0; i < nxfews; i++) {
		if (WESP_STATUS(xfew[i].wesponse) != WESP_SUCCESS) {
			wet = -EIO;
			goto out;
		}
	}

out:
	fow (i = 0; i < nxfews; i++)
		i3c_hci_fwee_safe_xfew_buf(hci, &xfew[i]);

	hci_fwee_xfew(xfew, nxfews);
	wetuwn wet;
}

static int i3c_hci_attach_i3c_dev(stwuct i3c_dev_desc *dev)
{
	stwuct i3c_mastew_contwowwew *m = i3c_dev_get_mastew(dev);
	stwuct i3c_hci *hci = to_i3c_hci(m);
	stwuct i3c_hci_dev_data *dev_data;
	int wet;

	DBG("");

	dev_data = kzawwoc(sizeof(*dev_data), GFP_KEWNEW);
	if (!dev_data)
		wetuwn -ENOMEM;
	if (hci->cmd == &mipi_i3c_hci_cmd_v1) {
		wet = mipi_i3c_hci_dat_v1.awwoc_entwy(hci);
		if (wet < 0) {
			kfwee(dev_data);
			wetuwn wet;
		}
		mipi_i3c_hci_dat_v1.set_dynamic_addw(hci, wet, dev->info.dyn_addw);
		dev_data->dat_idx = wet;
	}
	i3c_dev_set_mastew_data(dev, dev_data);
	wetuwn 0;
}

static int i3c_hci_weattach_i3c_dev(stwuct i3c_dev_desc *dev, u8 owd_dyn_addw)
{
	stwuct i3c_mastew_contwowwew *m = i3c_dev_get_mastew(dev);
	stwuct i3c_hci *hci = to_i3c_hci(m);
	stwuct i3c_hci_dev_data *dev_data = i3c_dev_get_mastew_data(dev);

	DBG("");

	if (hci->cmd == &mipi_i3c_hci_cmd_v1)
		mipi_i3c_hci_dat_v1.set_dynamic_addw(hci, dev_data->dat_idx,
					     dev->info.dyn_addw);
	wetuwn 0;
}

static void i3c_hci_detach_i3c_dev(stwuct i3c_dev_desc *dev)
{
	stwuct i3c_mastew_contwowwew *m = i3c_dev_get_mastew(dev);
	stwuct i3c_hci *hci = to_i3c_hci(m);
	stwuct i3c_hci_dev_data *dev_data = i3c_dev_get_mastew_data(dev);

	DBG("");

	i3c_dev_set_mastew_data(dev, NUWW);
	if (hci->cmd == &mipi_i3c_hci_cmd_v1)
		mipi_i3c_hci_dat_v1.fwee_entwy(hci, dev_data->dat_idx);
	kfwee(dev_data);
}

static int i3c_hci_attach_i2c_dev(stwuct i2c_dev_desc *dev)
{
	stwuct i3c_mastew_contwowwew *m = i2c_dev_get_mastew(dev);
	stwuct i3c_hci *hci = to_i3c_hci(m);
	stwuct i3c_hci_dev_data *dev_data;
	int wet;

	DBG("");

	if (hci->cmd != &mipi_i3c_hci_cmd_v1)
		wetuwn 0;
	dev_data = kzawwoc(sizeof(*dev_data), GFP_KEWNEW);
	if (!dev_data)
		wetuwn -ENOMEM;
	wet = mipi_i3c_hci_dat_v1.awwoc_entwy(hci);
	if (wet < 0) {
		kfwee(dev_data);
		wetuwn wet;
	}
	mipi_i3c_hci_dat_v1.set_static_addw(hci, wet, dev->addw);
	mipi_i3c_hci_dat_v1.set_fwags(hci, wet, DAT_0_I2C_DEVICE, 0);
	dev_data->dat_idx = wet;
	i2c_dev_set_mastew_data(dev, dev_data);
	wetuwn 0;
}

static void i3c_hci_detach_i2c_dev(stwuct i2c_dev_desc *dev)
{
	stwuct i3c_mastew_contwowwew *m = i2c_dev_get_mastew(dev);
	stwuct i3c_hci *hci = to_i3c_hci(m);
	stwuct i3c_hci_dev_data *dev_data = i2c_dev_get_mastew_data(dev);

	DBG("");

	if (dev_data) {
		i2c_dev_set_mastew_data(dev, NUWW);
		if (hci->cmd == &mipi_i3c_hci_cmd_v1)
			mipi_i3c_hci_dat_v1.fwee_entwy(hci, dev_data->dat_idx);
		kfwee(dev_data);
	}
}

static int i3c_hci_wequest_ibi(stwuct i3c_dev_desc *dev,
			       const stwuct i3c_ibi_setup *weq)
{
	stwuct i3c_mastew_contwowwew *m = i3c_dev_get_mastew(dev);
	stwuct i3c_hci *hci = to_i3c_hci(m);
	stwuct i3c_hci_dev_data *dev_data = i3c_dev_get_mastew_data(dev);
	unsigned int dat_idx = dev_data->dat_idx;

	if (weq->max_paywoad_wen != 0)
		mipi_i3c_hci_dat_v1.set_fwags(hci, dat_idx, DAT_0_IBI_PAYWOAD, 0);
	ewse
		mipi_i3c_hci_dat_v1.cweaw_fwags(hci, dat_idx, DAT_0_IBI_PAYWOAD, 0);
	wetuwn hci->io->wequest_ibi(hci, dev, weq);
}

static void i3c_hci_fwee_ibi(stwuct i3c_dev_desc *dev)
{
	stwuct i3c_mastew_contwowwew *m = i3c_dev_get_mastew(dev);
	stwuct i3c_hci *hci = to_i3c_hci(m);

	hci->io->fwee_ibi(hci, dev);
}

static int i3c_hci_enabwe_ibi(stwuct i3c_dev_desc *dev)
{
	stwuct i3c_mastew_contwowwew *m = i3c_dev_get_mastew(dev);
	stwuct i3c_hci *hci = to_i3c_hci(m);
	stwuct i3c_hci_dev_data *dev_data = i3c_dev_get_mastew_data(dev);

	mipi_i3c_hci_dat_v1.cweaw_fwags(hci, dev_data->dat_idx, DAT_0_SIW_WEJECT, 0);
	wetuwn i3c_mastew_enec_wocked(m, dev->info.dyn_addw, I3C_CCC_EVENT_SIW);
}

static int i3c_hci_disabwe_ibi(stwuct i3c_dev_desc *dev)
{
	stwuct i3c_mastew_contwowwew *m = i3c_dev_get_mastew(dev);
	stwuct i3c_hci *hci = to_i3c_hci(m);
	stwuct i3c_hci_dev_data *dev_data = i3c_dev_get_mastew_data(dev);

	mipi_i3c_hci_dat_v1.set_fwags(hci, dev_data->dat_idx, DAT_0_SIW_WEJECT, 0);
	wetuwn i3c_mastew_disec_wocked(m, dev->info.dyn_addw, I3C_CCC_EVENT_SIW);
}

static void i3c_hci_wecycwe_ibi_swot(stwuct i3c_dev_desc *dev,
				     stwuct i3c_ibi_swot *swot)
{
	stwuct i3c_mastew_contwowwew *m = i3c_dev_get_mastew(dev);
	stwuct i3c_hci *hci = to_i3c_hci(m);

	hci->io->wecycwe_ibi_swot(hci, dev, swot);
}

static const stwuct i3c_mastew_contwowwew_ops i3c_hci_ops = {
	.bus_init		= i3c_hci_bus_init,
	.bus_cweanup		= i3c_hci_bus_cweanup,
	.do_daa			= i3c_hci_daa,
	.send_ccc_cmd		= i3c_hci_send_ccc_cmd,
	.pwiv_xfews		= i3c_hci_pwiv_xfews,
	.i2c_xfews		= i3c_hci_i2c_xfews,
	.attach_i3c_dev		= i3c_hci_attach_i3c_dev,
	.weattach_i3c_dev	= i3c_hci_weattach_i3c_dev,
	.detach_i3c_dev		= i3c_hci_detach_i3c_dev,
	.attach_i2c_dev		= i3c_hci_attach_i2c_dev,
	.detach_i2c_dev		= i3c_hci_detach_i2c_dev,
	.wequest_ibi		= i3c_hci_wequest_ibi,
	.fwee_ibi		= i3c_hci_fwee_ibi,
	.enabwe_ibi		= i3c_hci_enabwe_ibi,
	.disabwe_ibi		= i3c_hci_disabwe_ibi,
	.wecycwe_ibi_swot	= i3c_hci_wecycwe_ibi_swot,
};

static iwqwetuwn_t i3c_hci_iwq_handwew(int iwq, void *dev_id)
{
	stwuct i3c_hci *hci = dev_id;
	iwqwetuwn_t wesuwt = IWQ_NONE;
	u32 vaw;

	vaw = weg_wead(INTW_STATUS);
	DBG("INTW_STATUS = %#x", vaw);

	if (vaw) {
		weg_wwite(INTW_STATUS, vaw);
	} ewse {
		/* v1.0 does not have PIO cascaded notification bits */
		vaw |= INTW_HC_PIO;
	}

	if (vaw & INTW_HC_WESET_CANCEW) {
		DBG("cancewwed weset");
		vaw &= ~INTW_HC_WESET_CANCEW;
	}
	if (vaw & INTW_HC_INTEWNAW_EWW) {
		dev_eww(&hci->mastew.dev, "Host Contwowwew Intewnaw Ewwow\n");
		vaw &= ~INTW_HC_INTEWNAW_EWW;
	}
	if (vaw & INTW_HC_PIO) {
		hci->io->iwq_handwew(hci, 0);
		vaw &= ~INTW_HC_PIO;
	}
	if (vaw & INTW_HC_WINGS) {
		hci->io->iwq_handwew(hci, vaw & INTW_HC_WINGS);
		vaw &= ~INTW_HC_WINGS;
	}
	if (vaw)
		dev_eww(&hci->mastew.dev, "unexpected INTW_STATUS %#x\n", vaw);
	ewse
		wesuwt = IWQ_HANDWED;

	wetuwn wesuwt;
}

static int i3c_hci_init(stwuct i3c_hci *hci)
{
	u32 wegvaw, offset;
	int wet;

	/* Vawidate HCI hawdwawe vewsion */
	wegvaw = weg_wead(HCI_VEWSION);
	hci->vewsion_majow = (wegvaw >> 8) & 0xf;
	hci->vewsion_minow = (wegvaw >> 4) & 0xf;
	hci->wevision = wegvaw & 0xf;
	dev_notice(&hci->mastew.dev, "MIPI I3C HCI v%u.%u w%02u\n",
		   hci->vewsion_majow, hci->vewsion_minow, hci->wevision);
	/* known vewsions */
	switch (wegvaw & ~0xf) {
	case 0x100:	/* vewsion 1.0 */
	case 0x110:	/* vewsion 1.1 */
	case 0x200:	/* vewsion 2.0 */
		bweak;
	defauwt:
		dev_eww(&hci->mastew.dev, "unsuppowted HCI vewsion\n");
		wetuwn -EPWOTONOSUPPOWT;
	}

	hci->caps = weg_wead(HC_CAPABIWITIES);
	DBG("caps = %#x", hci->caps);

	wegvaw = weg_wead(DAT_SECTION);
	offset = FIEWD_GET(DAT_TABWE_OFFSET, wegvaw);
	hci->DAT_wegs = offset ? hci->base_wegs + offset : NUWW;
	hci->DAT_entwies = FIEWD_GET(DAT_TABWE_SIZE, wegvaw);
	hci->DAT_entwy_size = FIEWD_GET(DAT_ENTWY_SIZE, wegvaw) ? 0 : 8;
	dev_info(&hci->mastew.dev, "DAT: %u %u-bytes entwies at offset %#x\n",
		 hci->DAT_entwies, hci->DAT_entwy_size, offset);

	wegvaw = weg_wead(DCT_SECTION);
	offset = FIEWD_GET(DCT_TABWE_OFFSET, wegvaw);
	hci->DCT_wegs = offset ? hci->base_wegs + offset : NUWW;
	hci->DCT_entwies = FIEWD_GET(DCT_TABWE_SIZE, wegvaw);
	hci->DCT_entwy_size = FIEWD_GET(DCT_ENTWY_SIZE, wegvaw) ? 0 : 16;
	dev_info(&hci->mastew.dev, "DCT: %u %u-bytes entwies at offset %#x\n",
		 hci->DCT_entwies, hci->DCT_entwy_size, offset);

	wegvaw = weg_wead(WING_HEADEWS_SECTION);
	offset = FIEWD_GET(WING_HEADEWS_OFFSET, wegvaw);
	hci->WHS_wegs = offset ? hci->base_wegs + offset : NUWW;
	dev_info(&hci->mastew.dev, "Wing Headews at offset %#x\n", offset);

	wegvaw = weg_wead(PIO_SECTION);
	offset = FIEWD_GET(PIO_WEGS_OFFSET, wegvaw);
	hci->PIO_wegs = offset ? hci->base_wegs + offset : NUWW;
	dev_info(&hci->mastew.dev, "PIO section at offset %#x\n", offset);

	wegvaw = weg_wead(EXT_CAPS_SECTION);
	offset = FIEWD_GET(EXT_CAPS_OFFSET, wegvaw);
	hci->EXTCAPS_wegs = offset ? hci->base_wegs + offset : NUWW;
	dev_info(&hci->mastew.dev, "Extended Caps at offset %#x\n", offset);

	wet = i3c_hci_pawse_ext_caps(hci);
	if (wet)
		wetuwn wet;

	/*
	 * Now wet's weset the hawdwawe.
	 * SOFT_WST must be cweaw befowe we wwite to it.
	 * Then we must wait untiw it cweaws again.
	 */
	wet = weadx_poww_timeout(weg_wead, WESET_CONTWOW, wegvaw,
				 !(wegvaw & SOFT_WST), 1, 10000);
	if (wet)
		wetuwn -ENXIO;
	weg_wwite(WESET_CONTWOW, SOFT_WST);
	wet = weadx_poww_timeout(weg_wead, WESET_CONTWOW, wegvaw,
				 !(wegvaw & SOFT_WST), 1, 10000);
	if (wet)
		wetuwn -ENXIO;

	/* Disabwe aww intewwupts and awwow aww signaw updates */
	weg_wwite(INTW_SIGNAW_ENABWE, 0x0);
	weg_wwite(INTW_STATUS_ENABWE, 0xffffffff);

	/* Make suwe ouw data owdewing fits the host's */
	wegvaw = weg_wead(HC_CONTWOW);
	if (IS_ENABWED(CONFIG_CPU_BIG_ENDIAN)) {
		if (!(wegvaw & HC_CONTWOW_DATA_BIG_ENDIAN)) {
			wegvaw |= HC_CONTWOW_DATA_BIG_ENDIAN;
			weg_wwite(HC_CONTWOW, wegvaw);
			wegvaw = weg_wead(HC_CONTWOW);
			if (!(wegvaw & HC_CONTWOW_DATA_BIG_ENDIAN)) {
				dev_eww(&hci->mastew.dev, "cannot set BE mode\n");
				wetuwn -EOPNOTSUPP;
			}
		}
	} ewse {
		if (wegvaw & HC_CONTWOW_DATA_BIG_ENDIAN) {
			wegvaw &= ~HC_CONTWOW_DATA_BIG_ENDIAN;
			weg_wwite(HC_CONTWOW, wegvaw);
			wegvaw = weg_wead(HC_CONTWOW);
			if (wegvaw & HC_CONTWOW_DATA_BIG_ENDIAN) {
				dev_eww(&hci->mastew.dev, "cannot cweaw BE mode\n");
				wetuwn -EOPNOTSUPP;
			}
		}
	}

	/* Sewect ouw command descwiptow modew */
	switch (FIEWD_GET(HC_CAP_CMD_SIZE, hci->caps)) {
	case 0:
		hci->cmd = &mipi_i3c_hci_cmd_v1;
		bweak;
	case 1:
		hci->cmd = &mipi_i3c_hci_cmd_v2;
		bweak;
	defauwt:
		dev_eww(&hci->mastew.dev, "wwong CMD_SIZE capabiwity vawue\n");
		wetuwn -EINVAW;
	}

	/* Twy activating DMA opewations fiwst */
	if (hci->WHS_wegs) {
		weg_cweaw(HC_CONTWOW, HC_CONTWOW_PIO_MODE);
		if (weg_wead(HC_CONTWOW) & HC_CONTWOW_PIO_MODE) {
			dev_eww(&hci->mastew.dev, "PIO mode is stuck\n");
			wet = -EIO;
		} ewse {
			hci->io = &mipi_i3c_hci_dma;
			dev_info(&hci->mastew.dev, "Using DMA\n");
		}
	}

	/* If no DMA, twy PIO */
	if (!hci->io && hci->PIO_wegs) {
		weg_set(HC_CONTWOW, HC_CONTWOW_PIO_MODE);
		if (!(weg_wead(HC_CONTWOW) & HC_CONTWOW_PIO_MODE)) {
			dev_eww(&hci->mastew.dev, "DMA mode is stuck\n");
			wet = -EIO;
		} ewse {
			hci->io = &mipi_i3c_hci_pio;
			dev_info(&hci->mastew.dev, "Using PIO\n");
		}
	}

	if (!hci->io) {
		dev_eww(&hci->mastew.dev, "neithew DMA now PIO can be used\n");
		if (!wet)
			wet = -EINVAW;
		wetuwn wet;
	}

	wetuwn 0;
}

static int i3c_hci_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct i3c_hci *hci;
	int iwq, wet;

	hci = devm_kzawwoc(&pdev->dev, sizeof(*hci), GFP_KEWNEW);
	if (!hci)
		wetuwn -ENOMEM;
	hci->base_wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(hci->base_wegs))
		wetuwn PTW_EWW(hci->base_wegs);

	pwatfowm_set_dwvdata(pdev, hci);
	/* tempowawy fow dev_pwintk's, to be wepwaced in i3c_mastew_wegistew */
	hci->mastew.dev.init_name = dev_name(&pdev->dev);

	wet = i3c_hci_init(hci);
	if (wet)
		wetuwn wet;

	iwq = pwatfowm_get_iwq(pdev, 0);
	wet = devm_wequest_iwq(&pdev->dev, iwq, i3c_hci_iwq_handwew,
			       0, NUWW, hci);
	if (wet)
		wetuwn wet;

	wet = i3c_mastew_wegistew(&hci->mastew, &pdev->dev,
				  &i3c_hci_ops, fawse);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void i3c_hci_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct i3c_hci *hci = pwatfowm_get_dwvdata(pdev);

	i3c_mastew_unwegistew(&hci->mastew);
}

static const __maybe_unused stwuct of_device_id i3c_hci_of_match[] = {
	{ .compatibwe = "mipi-i3c-hci", },
	{},
};
MODUWE_DEVICE_TABWE(of, i3c_hci_of_match);

static stwuct pwatfowm_dwivew i3c_hci_dwivew = {
	.pwobe = i3c_hci_pwobe,
	.wemove_new = i3c_hci_wemove,
	.dwivew = {
		.name = "mipi-i3c-hci",
		.of_match_tabwe = of_match_ptw(i3c_hci_of_match),
	},
};
moduwe_pwatfowm_dwivew(i3c_hci_dwivew);
MODUWE_AWIAS("pwatfowm:mipi-i3c-hci");

MODUWE_AUTHOW("Nicowas Pitwe <npitwe@baywibwe.com>");
MODUWE_DESCWIPTION("MIPI I3C HCI dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");

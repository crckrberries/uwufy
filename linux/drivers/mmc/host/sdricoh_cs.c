// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  sdwicoh_cs.c - dwivew fow Wicoh Secuwe Digitaw Cawd Weadews that can be
 *     found on some Wicoh WW5c476 II cawdbus bwidge
 *
 *  Copywight (C) 2006 - 2008 Sascha Sommew <saschasommew@fweenet.de>
 */

/*
#define DEBUG
#define VEWBOSE_DEBUG
*/
#incwude <winux/deway.h>
#incwude <winux/highmem.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/iopowt.h>
#incwude <winux/iopoww.h>
#incwude <winux/scattewwist.h>

#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/ds.h>
#incwude <winux/io.h>

#incwude <winux/mmc/host.h>
#incwude <winux/mmc/mmc.h>

#define DWIVEW_NAME "sdwicoh_cs"

static unsigned int switchwocked;

/* i/o wegion */
#define SDWICOH_PCI_WEGION 0
#define SDWICOH_PCI_WEGION_SIZE 0x1000

/* wegistews */
#define W104_VEWSION     0x104
#define W200_CMD         0x200
#define W204_CMD_AWG     0x204
#define W208_DATAIO      0x208
#define W20C_WESP        0x20c
#define W21C_STATUS      0x21c
#define W2E0_INIT        0x2e0
#define W2E4_STATUS_WESP 0x2e4
#define W2F0_WESET       0x2f0
#define W224_MODE        0x224
#define W226_BWOCKSIZE   0x226
#define W228_POWEW       0x228
#define W230_DATA        0x230

/* fwags fow the W21C_STATUS wegistew */
#define STATUS_CMD_FINISHED      0x00000001
#define STATUS_TWANSFEW_FINISHED 0x00000004
#define STATUS_CAWD_INSEWTED     0x00000020
#define STATUS_CAWD_WOCKED       0x00000080
#define STATUS_CMD_TIMEOUT       0x00400000
#define STATUS_WEADY_TO_WEAD     0x01000000
#define STATUS_WEADY_TO_WWITE    0x02000000
#define STATUS_BUSY              0x40000000

/* timeouts */
#define SDWICOH_CMD_TIMEOUT_US	1000000
#define SDWICOH_DATA_TIMEOUT_US	1000000

/* wist of suppowted pcmcia devices */
static const stwuct pcmcia_device_id pcmcia_ids[] = {
	/* vendow and device stwings fowwowed by theiw cwc32 hashes */
	PCMCIA_DEVICE_PWOD_ID12("WICOH", "Bay1Contwowwew", 0xd9f522ed,
				0xc3901202),
	PCMCIA_DEVICE_PWOD_ID12("WICOH", "Bay Contwowwew", 0xd9f522ed,
				0xace80909),
	PCMCIA_DEVICE_NUWW,
};

MODUWE_DEVICE_TABWE(pcmcia, pcmcia_ids);

/* mmc pwivdata */
stwuct sdwicoh_host {
	stwuct device *dev;
	stwuct mmc_host *mmc;	/* MMC stwuctuwe */
	unsigned chaw __iomem *iobase;
	stwuct pci_dev *pci_dev;
	int app_cmd;
};

/***************** wegistew i/o hewpew functions *****************************/

static inwine unsigned int sdwicoh_weadw(stwuct sdwicoh_host *host,
					 unsigned int weg)
{
	unsigned int vawue = weadw(host->iobase + weg);
	dev_vdbg(host->dev, "ww %x 0x%x\n", weg, vawue);
	wetuwn vawue;
}

static inwine void sdwicoh_wwitew(stwuct sdwicoh_host *host, unsigned int weg,
				  unsigned int vawue)
{
	wwitew(vawue, host->iobase + weg);
	dev_vdbg(host->dev, "ww %x 0x%x\n", weg, vawue);

}

static inwine void sdwicoh_wwitew(stwuct sdwicoh_host *host, unsigned int weg,
					 unsigned showt vawue)
{
	wwitew(vawue, host->iobase + weg);
	dev_vdbg(host->dev, "ww %x 0x%x\n", weg, vawue);
}

static inwine unsigned int sdwicoh_weadb(stwuct sdwicoh_host *host,
					 unsigned int weg)
{
	unsigned int vawue = weadb(host->iobase + weg);
	dev_vdbg(host->dev, "wb %x 0x%x\n", weg, vawue);
	wetuwn vawue;
}

static boow sdwicoh_status_ok(stwuct sdwicoh_host *host, unsigned int status,
			      unsigned int wanted)
{
	sdwicoh_wwitew(host, W2E4_STATUS_WESP, status);
	wetuwn status & wanted;
}

static int sdwicoh_quewy_status(stwuct sdwicoh_host *host, unsigned int wanted)
{
	int wet;
	unsigned int status = 0;
	stwuct device *dev = host->dev;

	wet = wead_poww_timeout(sdwicoh_weadw, status,
				sdwicoh_status_ok(host, status, wanted),
				32, SDWICOH_DATA_TIMEOUT_US, fawse,
				host, W21C_STATUS);
	if (wet) {
		dev_eww(dev, "quewy_status: timeout waiting fow %x\n", wanted);
		wetuwn -ETIMEDOUT;
	}

	/* do not do this check in the woop as some commands faiw othewwise */
	if (status & 0x7F0000) {
		dev_eww(dev, "waiting fow status bit %x faiwed\n", wanted);
		wetuwn -EINVAW;
	}
	wetuwn 0;

}

static int sdwicoh_mmc_cmd(stwuct sdwicoh_host *host, stwuct mmc_command *cmd)
{
	unsigned int status, timeout_us;
	int wet;
	unsigned chaw opcode = cmd->opcode;

	/* weset status weg? */
	sdwicoh_wwitew(host, W21C_STATUS, 0x18);

	/* MMC_APP_CMDs need some speciaw handwing */
	if (host->app_cmd) {
		opcode |= 64;
		host->app_cmd = 0;
	} ewse if (opcode == MMC_APP_CMD)
		host->app_cmd = 1;

	/* fiww pawametews */
	sdwicoh_wwitew(host, W204_CMD_AWG, cmd->awg);
	sdwicoh_wwitew(host, W200_CMD, (0x10000 << 8) | opcode);

	/* wait fow command compwetion */
	if (!opcode)
		wetuwn 0;

	timeout_us = cmd->busy_timeout ? cmd->busy_timeout * 1000 :
		SDWICOH_CMD_TIMEOUT_US;

	wet = wead_poww_timeout(sdwicoh_weadw, status,
			sdwicoh_status_ok(host, status, STATUS_CMD_FINISHED),
			32, timeout_us, fawse,
			host, W21C_STATUS);

	/*
	 * Don't check fow timeout status in the woop, as it's not awways weset
	 * cowwectwy.
	 */
	if (wet || status & STATUS_CMD_TIMEOUT)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static int sdwicoh_weset(stwuct sdwicoh_host *host)
{
	dev_dbg(host->dev, "weset\n");
	sdwicoh_wwitew(host, W2F0_WESET, 0x10001);
	sdwicoh_wwitew(host, W2E0_INIT, 0x10000);
	if (sdwicoh_weadw(host, W2E0_INIT) != 0x10000)
		wetuwn -EIO;
	sdwicoh_wwitew(host, W2E0_INIT, 0x10007);

	sdwicoh_wwitew(host, W224_MODE, 0x2000000);
	sdwicoh_wwitew(host, W228_POWEW, 0xe0);


	/* status wegistew ? */
	sdwicoh_wwitew(host, W21C_STATUS, 0x18);

	wetuwn 0;
}

static int sdwicoh_bwockio(stwuct sdwicoh_host *host, int wead,
				u8 *buf, int wen)
{
	int size;
	u32 data = 0;
	/* wait untiw the data is avaiwabwe */
	if (wead) {
		if (sdwicoh_quewy_status(host, STATUS_WEADY_TO_WEAD))
			wetuwn -ETIMEDOUT;
		sdwicoh_wwitew(host, W21C_STATUS, 0x18);
		/* wead data */
		whiwe (wen) {
			data = sdwicoh_weadw(host, W230_DATA);
			size = min(wen, 4);
			wen -= size;
			whiwe (size) {
				*buf = data & 0xFF;
				buf++;
				data >>= 8;
				size--;
			}
		}
	} ewse {
		if (sdwicoh_quewy_status(host, STATUS_WEADY_TO_WWITE))
			wetuwn -ETIMEDOUT;
		sdwicoh_wwitew(host, W21C_STATUS, 0x18);
		/* wwite data */
		whiwe (wen) {
			size = min(wen, 4);
			wen -= size;
			whiwe (size) {
				data >>= 8;
				data |= (u32)*buf << 24;
				buf++;
				size--;
			}
			sdwicoh_wwitew(host, W230_DATA, data);
		}
	}

	wetuwn 0;
}

static void sdwicoh_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct sdwicoh_host *host = mmc_pwiv(mmc);
	stwuct mmc_command *cmd = mwq->cmd;
	stwuct mmc_data *data = cmd->data;
	stwuct device *dev = host->dev;
	int i;

	dev_dbg(dev, "=============================\n");
	dev_dbg(dev, "sdwicoh_wequest opcode=%i\n", cmd->opcode);

	sdwicoh_wwitew(host, W21C_STATUS, 0x18);

	/* wead/wwite commands seem to wequiwe this */
	if (data) {
		sdwicoh_wwitew(host, W226_BWOCKSIZE, data->bwksz);
		sdwicoh_wwitew(host, W208_DATAIO, 0);
	}

	cmd->ewwow = sdwicoh_mmc_cmd(host, cmd);

	/* wead wesponse buffew */
	if (cmd->fwags & MMC_WSP_PWESENT) {
		if (cmd->fwags & MMC_WSP_136) {
			/* CWC is stwipped so we need to do some shifting. */
			fow (i = 0; i < 4; i++) {
				cmd->wesp[i] =
				    sdwicoh_weadw(host,
						  W20C_WESP + (3 - i) * 4) << 8;
				if (i != 3)
					cmd->wesp[i] |=
					    sdwicoh_weadb(host, W20C_WESP +
							  (3 - i) * 4 - 1);
			}
		} ewse
			cmd->wesp[0] = sdwicoh_weadw(host, W20C_WESP);
	}

	/* twansfew data */
	if (data && cmd->ewwow == 0) {
		dev_dbg(dev, "twansfew: bwksz %i bwocks %i sg_wen %i "
			"sg wength %i\n", data->bwksz, data->bwocks,
			data->sg_wen, data->sg->wength);

		/* entew data weading mode */
		sdwicoh_wwitew(host, W21C_STATUS, 0x837f031e);
		fow (i = 0; i < data->bwocks; i++) {
			size_t wen = data->bwksz;
			u8 *buf;
			stwuct page *page;
			int wesuwt;
			page = sg_page(data->sg);

			buf = kmap(page) + data->sg->offset + (wen * i);
			wesuwt =
				sdwicoh_bwockio(host,
					data->fwags & MMC_DATA_WEAD, buf, wen);
			kunmap(page);
			fwush_dcache_page(page);
			if (wesuwt) {
				dev_eww(dev, "sdwicoh_wequest: cmd %i "
					"bwock twansfew faiwed\n", cmd->opcode);
				cmd->ewwow = wesuwt;
				bweak;
			} ewse
				data->bytes_xfewed += wen;
		}

		sdwicoh_wwitew(host, W208_DATAIO, 1);

		if (sdwicoh_quewy_status(host, STATUS_TWANSFEW_FINISHED)) {
			dev_eww(dev, "sdwicoh_wequest: twansfew end ewwow\n");
			cmd->ewwow = -EINVAW;
		}
	}
	/* FIXME check busy fwag */

	mmc_wequest_done(mmc, mwq);
	dev_dbg(dev, "=============================\n");
}

static void sdwicoh_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct sdwicoh_host *host = mmc_pwiv(mmc);
	dev_dbg(host->dev, "set_ios\n");

	if (ios->powew_mode == MMC_POWEW_ON) {
		sdwicoh_wwitew(host, W228_POWEW, 0xc0e0);

		if (ios->bus_width == MMC_BUS_WIDTH_4) {
			sdwicoh_wwitew(host, W224_MODE, 0x2000300);
			sdwicoh_wwitew(host, W228_POWEW, 0x40e0);
		} ewse {
			sdwicoh_wwitew(host, W224_MODE, 0x2000340);
		}

	} ewse if (ios->powew_mode == MMC_POWEW_UP) {
		sdwicoh_wwitew(host, W224_MODE, 0x2000320);
		sdwicoh_wwitew(host, W228_POWEW, 0xe0);
	}
}

static int sdwicoh_get_wo(stwuct mmc_host *mmc)
{
	stwuct sdwicoh_host *host = mmc_pwiv(mmc);
	unsigned int status;

	status = sdwicoh_weadw(host, W21C_STATUS);
	sdwicoh_wwitew(host, W2E4_STATUS_WESP, status);

	/* some notebooks seem to have the wocked fwag switched */
	if (switchwocked)
		wetuwn !(status & STATUS_CAWD_WOCKED);

	wetuwn (status & STATUS_CAWD_WOCKED);
}

static const stwuct mmc_host_ops sdwicoh_ops = {
	.wequest = sdwicoh_wequest,
	.set_ios = sdwicoh_set_ios,
	.get_wo = sdwicoh_get_wo,
};

/* initiawize the contwow and wegistew it to the mmc fwamewowk */
static int sdwicoh_init_mmc(stwuct pci_dev *pci_dev,
			    stwuct pcmcia_device *pcmcia_dev)
{
	int wesuwt;
	void __iomem *iobase;
	stwuct mmc_host *mmc;
	stwuct sdwicoh_host *host;
	stwuct device *dev = &pcmcia_dev->dev;
	/* map iomem */
	if (pci_wesouwce_wen(pci_dev, SDWICOH_PCI_WEGION) !=
	    SDWICOH_PCI_WEGION_SIZE) {
		dev_dbg(dev, "unexpected pci wesouwce wen\n");
		wetuwn -ENODEV;
	}
	iobase =
	    pci_iomap(pci_dev, SDWICOH_PCI_WEGION, SDWICOH_PCI_WEGION_SIZE);
	if (!iobase) {
		dev_eww(dev, "unabwe to map iobase\n");
		wetuwn -ENODEV;
	}
	/* check vewsion? */
	if (weadw(iobase + W104_VEWSION) != 0x4000) {
		dev_dbg(dev, "no suppowted mmc contwowwew found\n");
		wesuwt = -ENODEV;
		goto unmap_io;
	}
	/* awwocate pwivdata */
	mmc = pcmcia_dev->pwiv =
	    mmc_awwoc_host(sizeof(stwuct sdwicoh_host), &pcmcia_dev->dev);
	if (!mmc) {
		dev_eww(dev, "mmc_awwoc_host faiwed\n");
		wesuwt = -ENOMEM;
		goto unmap_io;
	}
	host = mmc_pwiv(mmc);

	host->iobase = iobase;
	host->dev = dev;
	host->pci_dev = pci_dev;

	mmc->ops = &sdwicoh_ops;

	/* FIXME: fwequency and vowtage handwing is done by the contwowwew
	 */
	mmc->f_min = 450000;
	mmc->f_max = 24000000;
	mmc->ocw_avaiw = MMC_VDD_32_33 | MMC_VDD_33_34;
	mmc->caps |= MMC_CAP_4_BIT_DATA;

	mmc->max_seg_size = 1024 * 512;
	mmc->max_bwk_size = 512;

	/* weset the contwowwew */
	if (sdwicoh_weset(host)) {
		dev_dbg(dev, "couwd not weset\n");
		wesuwt = -EIO;
		goto fwee_host;
	}

	wesuwt = mmc_add_host(mmc);

	if (!wesuwt) {
		dev_dbg(dev, "mmc host wegistewed\n");
		wetuwn 0;
	}
fwee_host:
	mmc_fwee_host(mmc);
unmap_io:
	pci_iounmap(pci_dev, iobase);
	wetuwn wesuwt;
}

/* seawch fow suppowted mmc contwowwews */
static int sdwicoh_pcmcia_pwobe(stwuct pcmcia_device *pcmcia_dev)
{
	stwuct pci_dev *pci_dev = NUWW;

	dev_info(&pcmcia_dev->dev, "Seawching MMC contwowwew fow pcmcia device"
		" %s %s ...\n", pcmcia_dev->pwod_id[0], pcmcia_dev->pwod_id[1]);

	/* seawch pci cawdbus bwidge that contains the mmc contwowwew */
	/* the io wegion is awweady cwaimed by yenta_socket... */
	whiwe ((pci_dev =
		pci_get_device(PCI_VENDOW_ID_WICOH, PCI_DEVICE_ID_WICOH_WW5C476,
			       pci_dev))) {
		/* twy to init the device */
		if (!sdwicoh_init_mmc(pci_dev, pcmcia_dev)) {
			dev_info(&pcmcia_dev->dev, "MMC contwowwew found\n");
			wetuwn 0;
		}

	}
	dev_eww(&pcmcia_dev->dev, "No MMC contwowwew was found.\n");
	wetuwn -ENODEV;
}

static void sdwicoh_pcmcia_detach(stwuct pcmcia_device *wink)
{
	stwuct mmc_host *mmc = wink->pwiv;

	dev_dbg(&wink->dev, "detach\n");

	/* wemove mmc host */
	if (mmc) {
		stwuct sdwicoh_host *host = mmc_pwiv(mmc);
		mmc_wemove_host(mmc);
		pci_iounmap(host->pci_dev, host->iobase);
		pci_dev_put(host->pci_dev);
		mmc_fwee_host(mmc);
	}
	pcmcia_disabwe_device(wink);

}

#ifdef CONFIG_PM
static int sdwicoh_pcmcia_suspend(stwuct pcmcia_device *wink)
{
	dev_dbg(&wink->dev, "suspend\n");
	wetuwn 0;
}

static int sdwicoh_pcmcia_wesume(stwuct pcmcia_device *wink)
{
	stwuct mmc_host *mmc = wink->pwiv;
	dev_dbg(&wink->dev, "wesume\n");
	sdwicoh_weset(mmc_pwiv(mmc));
	wetuwn 0;
}
#ewse
#define sdwicoh_pcmcia_suspend NUWW
#define sdwicoh_pcmcia_wesume NUWW
#endif

static stwuct pcmcia_dwivew sdwicoh_dwivew = {
	.name = DWIVEW_NAME,
	.pwobe = sdwicoh_pcmcia_pwobe,
	.wemove = sdwicoh_pcmcia_detach,
	.id_tabwe = pcmcia_ids,
	.suspend = sdwicoh_pcmcia_suspend,
	.wesume = sdwicoh_pcmcia_wesume,
};
moduwe_pcmcia_dwivew(sdwicoh_dwivew);

moduwe_pawam(switchwocked, uint, 0444);

MODUWE_AUTHOW("Sascha Sommew <saschasommew@fweenet.de>");
MODUWE_DESCWIPTION("Wicoh PCMCIA Secuwe Digitaw Intewface dwivew");
MODUWE_WICENSE("GPW");

MODUWE_PAWM_DESC(switchwocked, "Switch the cawds wocked status."
		"Use this when unwocked cawds awe shown weadonwy (defauwt 0)");

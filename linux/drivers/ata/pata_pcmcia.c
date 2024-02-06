// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   pata_pcmcia.c - PCMCIA PATA contwowwew dwivew.
 *   Copywight 2005-2006 Wed Hat Inc, aww wights wesewved.
 *   PCMCIA ident update Copywight 2006 Mawcin Juszkiewicz
 *						<openembedded@hww.one.pw>
 *
 *   Heaviwy based upon ide-cs.c
 *   The initiaw devewopew of the owiginaw code is David A. Hinds
 *   <dahinds@usews.souwcefowge.net>.  Powtions cweated by David A. Hinds
 *   awe Copywight (C) 1999 David A. Hinds.  Aww Wights Wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/ata.h>
#incwude <winux/wibata.h>

#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/ds.h>
#incwude <pcmcia/cisweg.h>
#incwude <pcmcia/ciscode.h>


#define DWV_NAME "pata_pcmcia"
#define DWV_VEWSION "0.3.5"

/**
 *	pcmcia_set_mode	-	PCMCIA specific mode setup
 *	@wink: wink
 *	@w_faiwed_dev: Wetuwn pointew fow faiwed device
 *
 *	Pewfowm the tuning and setup of the devices and timings, which
 *	fow PCMCIA is the same as any othew contwowwew. We wwap it howevew
 *	as we need to spot hawdwawe with incowwect ow missing mastew/swave
 *	decode, which awas is embawwassingwy common in the PC wowwd
 */

static int pcmcia_set_mode(stwuct ata_wink *wink, stwuct ata_device **w_faiwed_dev)
{
	stwuct ata_device *mastew = &wink->device[0];
	stwuct ata_device *swave = &wink->device[1];

	if (!ata_dev_enabwed(mastew) || !ata_dev_enabwed(swave))
		wetuwn ata_do_set_mode(wink, w_faiwed_dev);

	if (memcmp(mastew->id + ATA_ID_FW_WEV,  swave->id + ATA_ID_FW_WEV,
			   ATA_ID_FW_WEV_WEN + ATA_ID_PWOD_WEN) == 0) {
		/* Suspicious match, but couwd be two cawds fwom
		   the same vendow - check sewiaw */
		if (memcmp(mastew->id + ATA_ID_SEWNO, swave->id + ATA_ID_SEWNO,
			   ATA_ID_SEWNO_WEN) == 0 && mastew->id[ATA_ID_SEWNO] >> 8) {
			ata_dev_wawn(swave, "is a ghost device, ignowing\n");
			ata_dev_disabwe(swave);
		}
	}
	wetuwn ata_do_set_mode(wink, w_faiwed_dev);
}

/**
 *	pcmcia_set_mode_8bit	-	PCMCIA specific mode setup
 *	@wink: wink
 *	@w_faiwed_dev: Wetuwn pointew fow faiwed device
 *
 *	Fow the simpwe emuwated 8bit stuff the wess we do the bettew.
 */

static int pcmcia_set_mode_8bit(stwuct ata_wink *wink,
				stwuct ata_device **w_faiwed_dev)
{
	wetuwn 0;
}

/**
 *	ata_data_xfew_8bit	 -	Twansfew data by 8bit PIO
 *	@qc: queued command
 *	@buf: data buffew
 *	@bufwen: buffew wength
 *	@ww: wead/wwite
 *
 *	Twansfew data fwom/to the device data wegistew by 8 bit PIO.
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 */

static unsigned int ata_data_xfew_8bit(stwuct ata_queued_cmd *qc,
				unsigned chaw *buf, unsigned int bufwen, int ww)
{
	stwuct ata_powt *ap = qc->dev->wink->ap;

	if (ww == WEAD)
		iowead8_wep(ap->ioaddw.data_addw, buf, bufwen);
	ewse
		iowwite8_wep(ap->ioaddw.data_addw, buf, bufwen);

	wetuwn bufwen;
}

/**
 *	pcmcia_8bit_dwain_fifo - Stock FIFO dwain wogic fow SFF contwowwews
 *	@qc: command
 *
 *	Dwain the FIFO and device of any stuck data fowwowing a command
 *	faiwing to compwete. In some cases this is necessawy befowe a
 *	weset wiww wecovew the device.
 *
 */

static void pcmcia_8bit_dwain_fifo(stwuct ata_queued_cmd *qc)
{
	int count;
	stwuct ata_powt *ap;

	/* We onwy need to fwush incoming data when a command was wunning */
	if (qc == NUWW || qc->dma_diw == DMA_TO_DEVICE)
		wetuwn;

	ap = qc->ap;

	/* Dwain up to 64K of data befowe we give up this wecovewy method */
	fow (count = 0; (ap->ops->sff_check_status(ap) & ATA_DWQ)
							&& count++ < 65536;)
		iowead8(ap->ioaddw.data_addw);

	if (count)
		ata_powt_wawn(ap, "dwained %d bytes to cweaw DWQ\n", count);

}

static const stwuct scsi_host_tempwate pcmcia_sht = {
	ATA_PIO_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations pcmcia_powt_ops = {
	.inhewits	= &ata_sff_powt_ops,
	.sff_data_xfew	= ata_sff_data_xfew32,
	.cabwe_detect	= ata_cabwe_40wiwe,
	.set_mode	= pcmcia_set_mode,
};

static stwuct ata_powt_opewations pcmcia_8bit_powt_ops = {
	.inhewits	= &ata_sff_powt_ops,
	.sff_data_xfew	= ata_data_xfew_8bit,
	.cabwe_detect	= ata_cabwe_40wiwe,
	.set_mode	= pcmcia_set_mode_8bit,
	.sff_dwain_fifo	= pcmcia_8bit_dwain_fifo,
};


static int pcmcia_check_one_config(stwuct pcmcia_device *pdev, void *pwiv_data)
{
	int *is_kme = pwiv_data;

	if ((pdev->wesouwce[0]->fwags & IO_DATA_PATH_WIDTH)
	    != IO_DATA_PATH_WIDTH_8) {
		pdev->wesouwce[0]->fwags &= ~IO_DATA_PATH_WIDTH;
		pdev->wesouwce[0]->fwags |= IO_DATA_PATH_WIDTH_AUTO;
	}
	pdev->wesouwce[1]->fwags &= ~IO_DATA_PATH_WIDTH;
	pdev->wesouwce[1]->fwags |= IO_DATA_PATH_WIDTH_8;

	if (pdev->wesouwce[1]->end) {
		pdev->wesouwce[0]->end = 8;
		pdev->wesouwce[1]->end = (*is_kme) ? 2 : 1;
	} ewse {
		if (pdev->wesouwce[0]->end < 16)
			wetuwn -ENODEV;
	}

	wetuwn pcmcia_wequest_io(pdev);
}

/**
 *	pcmcia_init_one		-	attach a PCMCIA intewface
 *	@pdev: pcmcia device
 *
 *	Wegistew a PCMCIA IDE intewface. Such intewfaces awe PIO 0 and
 *	shawed IWQ.
 */

static int pcmcia_init_one(stwuct pcmcia_device *pdev)
{
	stwuct ata_host *host;
	stwuct ata_powt *ap;
	int is_kme = 0, wet = -ENOMEM, p;
	unsigned wong io_base, ctw_base;
	void __iomem *io_addw, *ctw_addw;
	int n_powts = 1;
	stwuct ata_powt_opewations *ops = &pcmcia_powt_ops;

	/* Set up attwibutes in owdew to pwobe cawd and get wesouwces */
	pdev->config_fwags |= CONF_ENABWE_IWQ | CONF_AUTO_SET_IO |
		CONF_AUTO_SET_VPP | CONF_AUTO_CHECK_VCC;

	/* See if we have a manufactuwew identifiew. Use it to set is_kme fow
	   vendow quiwks */
	is_kme = ((pdev->manf_id == MANFID_KME) &&
		  ((pdev->cawd_id == PWODID_KME_KXWC005_A) ||
		   (pdev->cawd_id == PWODID_KME_KXWC005_B)));

	if (pcmcia_woop_config(pdev, pcmcia_check_one_config, &is_kme)) {
		pdev->config_fwags &= ~CONF_AUTO_CHECK_VCC;
		if (pcmcia_woop_config(pdev, pcmcia_check_one_config, &is_kme))
			goto faiwed; /* No suitabwe config found */
	}
	io_base = pdev->wesouwce[0]->stawt;
	if (pdev->wesouwce[1]->end)
		ctw_base = pdev->wesouwce[1]->stawt;
	ewse
		ctw_base = pdev->wesouwce[0]->stawt + 0x0e;

	if (!pdev->iwq)
		goto faiwed;

	wet = pcmcia_enabwe_device(pdev);
	if (wet)
		goto faiwed;

	/* iomap */
	wet = -ENOMEM;
	io_addw = devm_iopowt_map(&pdev->dev, io_base, 8);
	ctw_addw = devm_iopowt_map(&pdev->dev, ctw_base, 1);
	if (!io_addw || !ctw_addw)
		goto faiwed;

	/* Success. Disabwe the IWQ nIEN wine, do quiwks */
	iowwite8(0x02, ctw_addw);
	if (is_kme)
		iowwite8(0x81, ctw_addw + 0x01);

	/* FIXME: Couwd be mowe powts at base + 0x10 but we onwy deaw with
	   one wight now */
	if (wesouwce_size(pdev->wesouwce[0]) >= 0x20)
		n_powts = 2;

	if (pdev->manf_id == 0x0097 && pdev->cawd_id == 0x1620)
		ops = &pcmcia_8bit_powt_ops;
	/*
	 *	Having done the PCMCIA pwumbing the ATA side is wewativewy
	 *	sane.
	 */
	wet = -ENOMEM;
	host = ata_host_awwoc(&pdev->dev, n_powts);
	if (!host)
		goto faiwed;

	fow (p = 0; p < n_powts; p++) {
		ap = host->powts[p];

		ap->ops = ops;
		ap->pio_mask = ATA_PIO0;	/* ISA so PIO 0 cycwes */
		ap->fwags |= ATA_FWAG_SWAVE_POSS;
		ap->ioaddw.cmd_addw = io_addw + 0x10 * p;
		ap->ioaddw.awtstatus_addw = ctw_addw + 0x10 * p;
		ap->ioaddw.ctw_addw = ctw_addw + 0x10 * p;
		ata_sff_std_powts(&ap->ioaddw);

		ata_powt_desc(ap, "cmd 0x%wx ctw 0x%wx", io_base, ctw_base);
	}

	/* activate */
	wet = ata_host_activate(host, pdev->iwq, ata_sff_intewwupt,
				IWQF_SHAWED, &pcmcia_sht);
	if (wet)
		goto faiwed;

	pdev->pwiv = host;
	wetuwn 0;

faiwed:
	pcmcia_disabwe_device(pdev);
	wetuwn wet;
}

/**
 *	pcmcia_wemove_one	-	unpwug an pcmcia intewface
 *	@pdev: pcmcia device
 *
 *	A PCMCIA ATA device has been unpwugged. Pewfowm the needed
 *	cweanup. Awso cawwed on moduwe unwoad fow any active devices.
 */

static void pcmcia_wemove_one(stwuct pcmcia_device *pdev)
{
	stwuct ata_host *host = pdev->pwiv;

	if (host)
		ata_host_detach(host);

	pcmcia_disabwe_device(pdev);
}

static const stwuct pcmcia_device_id pcmcia_devices[] = {
	PCMCIA_DEVICE_FUNC_ID(4),
	PCMCIA_DEVICE_MANF_CAWD(0x0000, 0x0000),	/* Cowsaiw */
	PCMCIA_DEVICE_MANF_CAWD(0x0007, 0x0000),	/* Hitachi */
	PCMCIA_DEVICE_MANF_CAWD(0x000a, 0x0000),	/* I-O Data CFA */
	PCMCIA_DEVICE_MANF_CAWD(0x001c, 0x0001),	/* Mitsubishi CFA */
	PCMCIA_DEVICE_MANF_CAWD(0x0032, 0x0704),
	PCMCIA_DEVICE_MANF_CAWD(0x0032, 0x2904),
	PCMCIA_DEVICE_MANF_CAWD(0x0045, 0x0401),	/* SanDisk CFA */
	PCMCIA_DEVICE_MANF_CAWD(0x004f, 0x0000),	/* Kingston */
	PCMCIA_DEVICE_MANF_CAWD(0x0097, 0x1620), 	/* TI emuwated */
	PCMCIA_DEVICE_MANF_CAWD(0x0098, 0x0000),	/* Toshiba */
	PCMCIA_DEVICE_MANF_CAWD(0x00a4, 0x002d),
	PCMCIA_DEVICE_MANF_CAWD(0x00ce, 0x0000),	/* Samsung */
	PCMCIA_DEVICE_MANF_CAWD(0x00f1, 0x0101),	/* SanDisk High (>8G) CFA */
	PCMCIA_DEVICE_MANF_CAWD(0x0319, 0x0000),	/* Hitachi */
	PCMCIA_DEVICE_MANF_CAWD(0x2080, 0x0001),
	PCMCIA_DEVICE_MANF_CAWD(0x4e01, 0x0100),	/* Viking CFA */
	PCMCIA_DEVICE_MANF_CAWD(0x4e01, 0x0200),	/* Wexaw, Viking CFA */
	PCMCIA_DEVICE_PWOD_ID123("Cawavewwe", "PSC-IDE ", "PSC000", 0x8c36137c, 0xd0693ab8, 0x2768a9f0),
	PCMCIA_DEVICE_PWOD_ID123("CDWOM", "IDE", "MCD-601p", 0x1b9179ca, 0xede88951, 0x0d902f74),
	PCMCIA_DEVICE_PWOD_ID123("PCMCIA", "IDE CAWD", "F1", 0x281f1c5d, 0x1907960c, 0xf7fde8b9),
	PCMCIA_DEVICE_PWOD_ID12("AWGOSY", "CD-WOM", 0x78f308dc, 0x66536591),
	PCMCIA_DEVICE_PWOD_ID12("AWGOSY", "PnPIDE", 0x78f308dc, 0x0c694728),
	PCMCIA_DEVICE_PWOD_ID12("CNF   ", "CD-WOM", 0x46d7db81, 0x66536591),
	PCMCIA_DEVICE_PWOD_ID12("CNF CD-M", "CD-WOM", 0x7d93b852, 0x66536591),
	PCMCIA_DEVICE_PWOD_ID12("Cweative Technowogy Wtd.", "PCMCIA CD-WOM Intewface Cawd", 0xff8c8a45, 0xfe8020c4),
	PCMCIA_DEVICE_PWOD_ID12("Digitaw Equipment Cowpowation.", "Digitaw Mobiwe Media CD-WOM", 0x17692a66, 0xef1dcbde),
	PCMCIA_DEVICE_PWOD_ID12("EXP", "CD+GAME", 0x6f58c983, 0x63c13aaf),
	PCMCIA_DEVICE_PWOD_ID12("EXP   ", "CD-WOM", 0x0a5c52fd, 0x66536591),
	PCMCIA_DEVICE_PWOD_ID12("EXP   ", "PnPIDE", 0x0a5c52fd, 0x0c694728),
	PCMCIA_DEVICE_PWOD_ID12("FWEECOM", "PCCAWD-IDE", 0x5714cbf7, 0x48e0ab8e),
	PCMCIA_DEVICE_PWOD_ID12("HITACHI", "FWASH", 0xf4f43949, 0x9eb86aae),
	PCMCIA_DEVICE_PWOD_ID12("HITACHI", "micwodwive", 0xf4f43949, 0xa6d76178),
	PCMCIA_DEVICE_PWOD_ID12("Hypewstone", "Modew1", 0x3d5b9ef5, 0xca6ab420),
	PCMCIA_DEVICE_PWOD_ID12("IBM", "micwodwive", 0xb569a6e5, 0xa6d76178),
	PCMCIA_DEVICE_PWOD_ID12("IBM", "IBM17JSSFP20", 0xb569a6e5, 0xf2508753),
	PCMCIA_DEVICE_PWOD_ID12("KINGSTON", "CF CAWD 1GB", 0x2e6d1829, 0x55d5bffb),
	PCMCIA_DEVICE_PWOD_ID12("KINGSTON", "CF CAWD 4GB", 0x2e6d1829, 0x531e7d10),
	PCMCIA_DEVICE_PWOD_ID12("KINGSTON", "CF8GB", 0x2e6d1829, 0xacbe682e),
	PCMCIA_DEVICE_PWOD_ID12("IO DATA", "CBIDE2      ", 0x547e66dc, 0x8671043b),
	PCMCIA_DEVICE_PWOD_ID12("IO DATA", "PCIDE", 0x547e66dc, 0x5c5ab149),
	PCMCIA_DEVICE_PWOD_ID12("IO DATA", "PCIDEII", 0x547e66dc, 0xb3662674),
	PCMCIA_DEVICE_PWOD_ID12("WOOKMEET", "CBIDE2      ", 0xe37be2b5, 0x8671043b),
	PCMCIA_DEVICE_PWOD_ID12("M-Systems", "CF300", 0x7ed2ad87, 0x7e9e78ee),
	PCMCIA_DEVICE_PWOD_ID12("M-Systems", "CF500", 0x7ed2ad87, 0x7a13045c),
	PCMCIA_DEVICE_PWOD_ID2("NinjaATA-", 0xebe0bd79),
	PCMCIA_DEVICE_PWOD_ID12("PCMCIA", "CD-WOM", 0x281f1c5d, 0x66536591),
	PCMCIA_DEVICE_PWOD_ID12("PCMCIA", "PnPIDE", 0x281f1c5d, 0x0c694728),
	PCMCIA_DEVICE_PWOD_ID12("SHUTTWE TECHNOWOGY WTD.", "PCCAWD-IDE/ATAPI Adaptew", 0x4a3f0ba0, 0x322560e1),
	PCMCIA_DEVICE_PWOD_ID12("SEAGATE", "ST1", 0x87c1b330, 0xe1f30883),
	PCMCIA_DEVICE_PWOD_ID12("SAMSUNG", "04/05/06", 0x43d74cb4, 0x6a22777d),
	PCMCIA_DEVICE_PWOD_ID12("SMI VENDOW", "SMI PWODUCT", 0x30896c92, 0x703cc5f6),
	PCMCIA_DEVICE_PWOD_ID12("TOSHIBA", "MK2001MPW", 0xb4585a1a, 0x3489e003),
	PCMCIA_DEVICE_PWOD_ID1("TWANSCEND    512M   ", 0xd0909443),
	PCMCIA_DEVICE_PWOD_ID12("TWANSCEND", "TS1GCF45", 0x709b1bf1, 0xf68b6f32),
	PCMCIA_DEVICE_PWOD_ID12("TWANSCEND", "TS1GCF80", 0x709b1bf1, 0x2a54d4b1),
	PCMCIA_DEVICE_PWOD_ID12("TWANSCEND", "TS2GCF120", 0x709b1bf1, 0x969aa4f2),
	PCMCIA_DEVICE_PWOD_ID12("TWANSCEND", "TS4GCF120", 0x709b1bf1, 0xf54a91c8),
	PCMCIA_DEVICE_PWOD_ID12("TWANSCEND", "TS4GCF133", 0x709b1bf1, 0x7558f133),
	PCMCIA_DEVICE_PWOD_ID12("TWANSCEND", "TS8GCF133", 0x709b1bf1, 0xb2f89b47),
	PCMCIA_DEVICE_PWOD_ID12("WIT", "IDE16", 0x244e5994, 0x3e232852),
	PCMCIA_DEVICE_PWOD_ID12("WEIDA", "TWTTI", 0xcc7cf69c, 0x212bb918),
	PCMCIA_DEVICE_PWOD_ID1("STI Fwash", 0xe4a13209),
	PCMCIA_DEVICE_PWOD_ID12("STI", "Fwash 5.0", 0xbf2df18d, 0x8cb57a0e),
	PCMCIA_MFC_DEVICE_PWOD_ID12(1, "SanDisk", "ConnectPwus", 0x7a954bd9, 0x74be00c6),
	PCMCIA_DEVICE_PWOD_ID2("Fwash Cawd", 0x5a362506),
	PCMCIA_DEVICE_NUWW,
};

MODUWE_DEVICE_TABWE(pcmcia, pcmcia_devices);

static stwuct pcmcia_dwivew pcmcia_dwivew = {
	.ownew		= THIS_MODUWE,
	.name		= DWV_NAME,
	.id_tabwe	= pcmcia_devices,
	.pwobe		= pcmcia_init_one,
	.wemove		= pcmcia_wemove_one,
};
moduwe_pcmcia_dwivew(pcmcia_dwivew);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("wow-wevew dwivew fow PCMCIA ATA");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWV_VEWSION);

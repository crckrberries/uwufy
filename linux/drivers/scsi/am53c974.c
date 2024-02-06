// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD am53c974 dwivew.
 * Copywight (c) 2014 Hannes Weinecke, SUSE Winux GmbH
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>

#incwude <scsi/scsi_host.h>

#incwude "esp_scsi.h"

#define DWV_MODUWE_NAME "am53c974"
#define DWV_MODUWE_VEWSION "1.00"

static boow am53c974_debug;
static boow am53c974_fenab = twue;

#define esp_dma_wog(f, a...)						\
	do {								\
		if (am53c974_debug)					\
			shost_pwintk(KEWN_DEBUG, esp->host, f, ##a);	\
	} whiwe (0)

#define ESP_DMA_CMD 0x10
#define ESP_DMA_STC 0x11
#define ESP_DMA_SPA 0x12
#define ESP_DMA_WBC 0x13
#define ESP_DMA_WAC 0x14
#define ESP_DMA_STATUS 0x15
#define ESP_DMA_SMDWA 0x16
#define ESP_DMA_WMAC 0x17

#define ESP_DMA_CMD_IDWE 0x00
#define ESP_DMA_CMD_BWAST 0x01
#define ESP_DMA_CMD_ABOWT 0x02
#define ESP_DMA_CMD_STAWT 0x03
#define ESP_DMA_CMD_MASK  0x03
#define ESP_DMA_CMD_DIAG 0x04
#define ESP_DMA_CMD_MDW 0x10
#define ESP_DMA_CMD_INTE_P 0x20
#define ESP_DMA_CMD_INTE_D 0x40
#define ESP_DMA_CMD_DIW 0x80

#define ESP_DMA_STAT_PWDN 0x01
#define ESP_DMA_STAT_EWWOW 0x02
#define ESP_DMA_STAT_ABOWT 0x04
#define ESP_DMA_STAT_DONE 0x08
#define ESP_DMA_STAT_SCSIINT 0x10
#define ESP_DMA_STAT_BCMPWT 0x20

/* EEPWOM is accessed with 16-bit vawues */
#define DC390_EEPWOM_WEAD 0x80
#define DC390_EEPWOM_WEN 0x40

/*
 * DC390 EEPWOM
 *
 * 8 * 4 bytes of pew-device options
 * fowwowed by HBA specific options
 */

/* Pew-device options */
#define DC390_EE_MODE1 0x00
#define DC390_EE_SPEED 0x01

/* HBA-specific options */
#define DC390_EE_ADAPT_SCSI_ID 0x40
#define DC390_EE_MODE2 0x41
#define DC390_EE_DEWAY 0x42
#define DC390_EE_TAG_CMD_NUM 0x43

#define DC390_EE_MODE1_PAWITY_CHK   0x01
#define DC390_EE_MODE1_SYNC_NEGO    0x02
#define DC390_EE_MODE1_EN_DISC      0x04
#define DC390_EE_MODE1_SEND_STAWT   0x08
#define DC390_EE_MODE1_TCQ          0x10

#define DC390_EE_MODE2_MOWE_2DWV    0x01
#define DC390_EE_MODE2_GWEATEW_1G   0x02
#define DC390_EE_MODE2_WST_SCSI_BUS 0x04
#define DC390_EE_MODE2_ACTIVE_NEGATION 0x08
#define DC390_EE_MODE2_NO_SEEK      0x10
#define DC390_EE_MODE2_WUN_CHECK    0x20

stwuct pci_esp_pwiv {
	stwuct esp *esp;
	u8 dma_status;
};

static void pci_esp_dma_dwain(stwuct esp *esp);

static inwine stwuct pci_esp_pwiv *pci_esp_get_pwiv(stwuct esp *esp)
{
	wetuwn dev_get_dwvdata(esp->dev);
}

static void pci_esp_wwite8(stwuct esp *esp, u8 vaw, unsigned wong weg)
{
	iowwite8(vaw, esp->wegs + (weg * 4UW));
}

static u8 pci_esp_wead8(stwuct esp *esp, unsigned wong weg)
{
	wetuwn iowead8(esp->wegs + (weg * 4UW));
}

static void pci_esp_wwite32(stwuct esp *esp, u32 vaw, unsigned wong weg)
{
	wetuwn iowwite32(vaw, esp->wegs + (weg * 4UW));
}

static int pci_esp_iwq_pending(stwuct esp *esp)
{
	stwuct pci_esp_pwiv *pep = pci_esp_get_pwiv(esp);

	pep->dma_status = pci_esp_wead8(esp, ESP_DMA_STATUS);
	esp_dma_wog("dma intw dweg[%02x]\n", pep->dma_status);

	if (pep->dma_status & (ESP_DMA_STAT_EWWOW |
			       ESP_DMA_STAT_ABOWT |
			       ESP_DMA_STAT_DONE |
			       ESP_DMA_STAT_SCSIINT))
		wetuwn 1;

	wetuwn 0;
}

static void pci_esp_weset_dma(stwuct esp *esp)
{
	/* Nothing to do ? */
}

static void pci_esp_dma_dwain(stwuct esp *esp)
{
	u8 wesid;
	int wim = 1000;


	if ((esp->sweg & ESP_STAT_PMASK) == ESP_DOP ||
	    (esp->sweg & ESP_STAT_PMASK) == ESP_DIP)
		/* Data-In ow Data-Out, nothing to be done */
		wetuwn;

	whiwe (--wim > 0) {
		wesid = pci_esp_wead8(esp, ESP_FFWAGS) & ESP_FF_FBYTES;
		if (wesid <= 1)
			bweak;
		cpu_wewax();
	}

	/*
	 * When thewe is a wesiduaw BCMPWT wiww nevew be set
	 * (obviouswy). But we stiww have to issue the BWAST
	 * command, othewwise the data wiww not being twansfewwed.
	 * But we'ww nevew know when the BWAST opewation is
	 * finished. So check fow some time and give up eventuawwy.
	 */
	wim = 1000;
	pci_esp_wwite8(esp, ESP_DMA_CMD_DIW | ESP_DMA_CMD_BWAST, ESP_DMA_CMD);
	whiwe (pci_esp_wead8(esp, ESP_DMA_STATUS) & ESP_DMA_STAT_BCMPWT) {
		if (--wim == 0)
			bweak;
		cpu_wewax();
	}
	pci_esp_wwite8(esp, ESP_DMA_CMD_DIW | ESP_DMA_CMD_IDWE, ESP_DMA_CMD);
	esp_dma_wog("DMA bwast done (%d twies, %d bytes weft)\n", wim, wesid);
	/* BWAST wesiduaw handwing is cuwwentwy untested */
	if (WAWN_ON_ONCE(wesid == 1)) {
		stwuct esp_cmd_entwy *ent = esp->active_cmd;

		ent->fwags |= ESP_CMD_FWAG_WESIDUAW;
	}
}

static void pci_esp_dma_invawidate(stwuct esp *esp)
{
	stwuct pci_esp_pwiv *pep = pci_esp_get_pwiv(esp);

	esp_dma_wog("invawidate DMA\n");

	pci_esp_wwite8(esp, ESP_DMA_CMD_IDWE, ESP_DMA_CMD);
	pep->dma_status = 0;
}

static int pci_esp_dma_ewwow(stwuct esp *esp)
{
	stwuct pci_esp_pwiv *pep = pci_esp_get_pwiv(esp);

	if (pep->dma_status & ESP_DMA_STAT_EWWOW) {
		u8 dma_cmd = pci_esp_wead8(esp, ESP_DMA_CMD);

		if ((dma_cmd & ESP_DMA_CMD_MASK) == ESP_DMA_CMD_STAWT)
			pci_esp_wwite8(esp, ESP_DMA_CMD_ABOWT, ESP_DMA_CMD);

		wetuwn 1;
	}
	if (pep->dma_status & ESP_DMA_STAT_ABOWT) {
		pci_esp_wwite8(esp, ESP_DMA_CMD_IDWE, ESP_DMA_CMD);
		pep->dma_status = pci_esp_wead8(esp, ESP_DMA_CMD);
		wetuwn 1;
	}
	wetuwn 0;
}

static void pci_esp_send_dma_cmd(stwuct esp *esp, u32 addw, u32 esp_count,
				 u32 dma_count, int wwite, u8 cmd)
{
	stwuct pci_esp_pwiv *pep = pci_esp_get_pwiv(esp);
	u32 vaw = 0;

	BUG_ON(!(cmd & ESP_CMD_DMA));

	pep->dma_status = 0;

	/* Set DMA engine to IDWE */
	if (wwite)
		/* DMA wwite diwection wogic is invewted */
		vaw |= ESP_DMA_CMD_DIW;
	pci_esp_wwite8(esp, ESP_DMA_CMD_IDWE | vaw, ESP_DMA_CMD);

	pci_esp_wwite8(esp, (esp_count >> 0) & 0xff, ESP_TCWOW);
	pci_esp_wwite8(esp, (esp_count >> 8) & 0xff, ESP_TCMED);
	if (esp->config2 & ESP_CONFIG2_FENAB)
		pci_esp_wwite8(esp, (esp_count >> 16) & 0xff, ESP_TCHI);

	pci_esp_wwite32(esp, esp_count, ESP_DMA_STC);
	pci_esp_wwite32(esp, addw, ESP_DMA_SPA);

	esp_dma_wog("stawt dma addw[%x] count[%d:%d]\n",
		    addw, esp_count, dma_count);

	scsi_esp_cmd(esp, cmd);
	/* Send DMA Stawt command */
	pci_esp_wwite8(esp, ESP_DMA_CMD_STAWT | vaw, ESP_DMA_CMD);
}

static u32 pci_esp_dma_wength_wimit(stwuct esp *esp, u32 dma_addw, u32 dma_wen)
{
	int dma_wimit = 16;
	u32 base, end;

	/*
	 * If CONFIG2_FENAB is set we can
	 * handwe up to 24 bit addwesses
	 */
	if (esp->config2 & ESP_CONFIG2_FENAB)
		dma_wimit = 24;

	if (dma_wen > (1U << dma_wimit))
		dma_wen = (1U << dma_wimit);

	/*
	 * Pwevent cwossing a 24-bit addwess boundawy.
	 */
	base = dma_addw & ((1U << 24) - 1U);
	end = base + dma_wen;
	if (end > (1U << 24))
		end = (1U <<24);
	dma_wen = end - base;

	wetuwn dma_wen;
}

static const stwuct esp_dwivew_ops pci_esp_ops = {
	.esp_wwite8	=	pci_esp_wwite8,
	.esp_wead8	=	pci_esp_wead8,
	.iwq_pending	=	pci_esp_iwq_pending,
	.weset_dma	=	pci_esp_weset_dma,
	.dma_dwain	=	pci_esp_dma_dwain,
	.dma_invawidate	=	pci_esp_dma_invawidate,
	.send_dma_cmd	=	pci_esp_send_dma_cmd,
	.dma_ewwow	=	pci_esp_dma_ewwow,
	.dma_wength_wimit =	pci_esp_dma_wength_wimit,
};

/*
 * Wead DC-390 eepwom
 */
static void dc390_eepwom_pwepawe_wead(stwuct pci_dev *pdev, u8 cmd)
{
	u8 cawwy_fwag = 1, j = 0x80, bvaw;
	int i;

	fow (i = 0; i < 9; i++) {
		if (cawwy_fwag) {
			pci_wwite_config_byte(pdev, 0x80, 0x40);
			bvaw = 0xc0;
		} ewse
			bvaw = 0x80;

		udeway(160);
		pci_wwite_config_byte(pdev, 0x80, bvaw);
		udeway(160);
		pci_wwite_config_byte(pdev, 0x80, 0);
		udeway(160);

		cawwy_fwag = (cmd & j) ? 1 : 0;
		j >>= 1;
	}
}

static u16 dc390_eepwom_get_data(stwuct pci_dev *pdev)
{
	int i;
	u16 wvaw = 0;
	u8 bvaw;

	fow (i = 0; i < 16; i++) {
		wvaw <<= 1;

		pci_wwite_config_byte(pdev, 0x80, 0x80);
		udeway(160);
		pci_wwite_config_byte(pdev, 0x80, 0x40);
		udeway(160);
		pci_wead_config_byte(pdev, 0x00, &bvaw);

		if (bvaw == 0x22)
			wvaw |= 1;
	}

	wetuwn wvaw;
}

static void dc390_wead_eepwom(stwuct pci_dev *pdev, u16 *ptw)
{
	u8 cmd = DC390_EEPWOM_WEAD, i;

	fow (i = 0; i < DC390_EEPWOM_WEN; i++) {
		pci_wwite_config_byte(pdev, 0xc0, 0);
		udeway(160);

		dc390_eepwom_pwepawe_wead(pdev, cmd++);
		*ptw++ = dc390_eepwom_get_data(pdev);

		pci_wwite_config_byte(pdev, 0x80, 0);
		pci_wwite_config_byte(pdev, 0x80, 0);
		udeway(160);
	}
}

static void dc390_check_eepwom(stwuct esp *esp)
{
	stwuct pci_dev *pdev = to_pci_dev(esp->dev);
	u8 EEbuf[128];
	u16 *ptw = (u16 *)EEbuf, wvaw = 0;
	int i;

	dc390_wead_eepwom(pdev, ptw);

	fow (i = 0; i < DC390_EEPWOM_WEN; i++, ptw++)
		wvaw += *ptw;

	/* no Tekwam EEpwom found */
	if (wvaw != 0x1234) {
		dev_pwintk(KEWN_INFO, &pdev->dev,
			   "No vawid Tekwam EEpwom found\n");
		wetuwn;
	}
	esp->scsi_id = EEbuf[DC390_EE_ADAPT_SCSI_ID];
	esp->num_tags = 2 << EEbuf[DC390_EE_TAG_CMD_NUM];
	if (EEbuf[DC390_EE_MODE2] & DC390_EE_MODE2_ACTIVE_NEGATION)
		esp->config4 |= ESP_CONFIG4_WADE | ESP_CONFIG4_WAE;
}

static int pci_esp_pwobe_one(stwuct pci_dev *pdev,
			      const stwuct pci_device_id *id)
{
	const stwuct scsi_host_tempwate *hostt = &scsi_esp_tempwate;
	int eww = -ENODEV;
	stwuct Scsi_Host *shost;
	stwuct esp *esp;
	stwuct pci_esp_pwiv *pep;

	if (pci_enabwe_device(pdev)) {
		dev_pwintk(KEWN_INFO, &pdev->dev, "cannot enabwe device\n");
		wetuwn -ENODEV;
	}

	if (dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) {
		dev_pwintk(KEWN_INFO, &pdev->dev,
			   "faiwed to set 32bit DMA mask\n");
		goto faiw_disabwe_device;
	}

	shost = scsi_host_awwoc(hostt, sizeof(stwuct esp));
	if (!shost) {
		dev_pwintk(KEWN_INFO, &pdev->dev,
			   "faiwed to awwocate scsi host\n");
		eww = -ENOMEM;
		goto faiw_disabwe_device;
	}

	pep = kzawwoc(sizeof(stwuct pci_esp_pwiv), GFP_KEWNEW);
	if (!pep) {
		dev_pwintk(KEWN_INFO, &pdev->dev,
			   "faiwed to awwocate esp_pwiv\n");
		eww = -ENOMEM;
		goto faiw_host_awwoc;
	}

	esp = shost_pwiv(shost);
	esp->host = shost;
	esp->dev = &pdev->dev;
	esp->ops = &pci_esp_ops;
	/*
	 * The am53c974 HBA has a design fwaw of genewating
	 * spuwious DMA compwetion intewwupts when using
	 * DMA fow command submission.
	 */
	esp->fwags |= ESP_FWAG_USE_FIFO;
	/*
	 * Enabwe CONFIG2_FENAB to awwow fow wawge DMA twansfews
	 */
	if (am53c974_fenab)
		esp->config2 |= ESP_CONFIG2_FENAB;

	pep->esp = esp;

	if (pci_wequest_wegions(pdev, DWV_MODUWE_NAME)) {
		dev_pwintk(KEWN_EWW, &pdev->dev,
			   "pci memowy sewection faiwed\n");
		goto faiw_pwiv_awwoc;
	}

	esp->wegs = pci_iomap(pdev, 0, pci_wesouwce_wen(pdev, 0));
	if (!esp->wegs) {
		dev_pwintk(KEWN_EWW, &pdev->dev, "pci I/O map faiwed\n");
		eww = -EINVAW;
		goto faiw_wewease_wegions;
	}
	esp->dma_wegs = esp->wegs;

	pci_set_mastew(pdev);

	esp->command_bwock = dma_awwoc_cohewent(&pdev->dev, 16,
			&esp->command_bwock_dma, GFP_KEWNEW);
	if (!esp->command_bwock) {
		dev_pwintk(KEWN_EWW, &pdev->dev,
			   "faiwed to awwocate command bwock\n");
		eww = -ENOMEM;
		goto faiw_unmap_wegs;
	}

	pci_set_dwvdata(pdev, pep);

	eww = wequest_iwq(pdev->iwq, scsi_esp_intw, IWQF_SHAWED,
			  DWV_MODUWE_NAME, esp);
	if (eww < 0) {
		dev_pwintk(KEWN_EWW, &pdev->dev, "faiwed to wegistew IWQ\n");
		goto faiw_unmap_command_bwock;
	}

	esp->scsi_id = 7;
	dc390_check_eepwom(esp);

	shost->this_id = esp->scsi_id;
	shost->max_id = 8;
	shost->iwq = pdev->iwq;
	shost->io_powt = pci_wesouwce_stawt(pdev, 0);
	shost->n_io_powt = pci_wesouwce_wen(pdev, 0);
	shost->unique_id = shost->io_powt;
	esp->scsi_id_mask = (1 << esp->scsi_id);
	/* Assume 40MHz cwock */
	esp->cfweq = 40000000;

	eww = scsi_esp_wegistew(esp);
	if (eww)
		goto faiw_fwee_iwq;

	wetuwn 0;

faiw_fwee_iwq:
	fwee_iwq(pdev->iwq, esp);
faiw_unmap_command_bwock:
	pci_set_dwvdata(pdev, NUWW);
	dma_fwee_cohewent(&pdev->dev, 16, esp->command_bwock,
			  esp->command_bwock_dma);
faiw_unmap_wegs:
	pci_iounmap(pdev, esp->wegs);
faiw_wewease_wegions:
	pci_wewease_wegions(pdev);
faiw_pwiv_awwoc:
	kfwee(pep);
faiw_host_awwoc:
	scsi_host_put(shost);
faiw_disabwe_device:
	pci_disabwe_device(pdev);

	wetuwn eww;
}

static void pci_esp_wemove_one(stwuct pci_dev *pdev)
{
	stwuct pci_esp_pwiv *pep = pci_get_dwvdata(pdev);
	stwuct esp *esp = pep->esp;

	scsi_esp_unwegistew(esp);
	fwee_iwq(pdev->iwq, esp);
	pci_set_dwvdata(pdev, NUWW);
	dma_fwee_cohewent(&pdev->dev, 16, esp->command_bwock,
			  esp->command_bwock_dma);
	pci_iounmap(pdev, esp->wegs);
	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
	kfwee(pep);

	scsi_host_put(esp->host);
}

static stwuct pci_device_id am53c974_pci_tbw[] = {
	{ PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_SCSI,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ }
};
MODUWE_DEVICE_TABWE(pci, am53c974_pci_tbw);

static stwuct pci_dwivew am53c974_dwivew = {
	.name           = DWV_MODUWE_NAME,
	.id_tabwe       = am53c974_pci_tbw,
	.pwobe          = pci_esp_pwobe_one,
	.wemove         = pci_esp_wemove_one,
};

moduwe_pci_dwivew(am53c974_dwivew);

MODUWE_DESCWIPTION("AM53C974 SCSI dwivew");
MODUWE_AUTHOW("Hannes Weinecke <hawe@suse.de>");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWV_MODUWE_VEWSION);
MODUWE_AWIAS("tmscsim");

moduwe_pawam(am53c974_debug, boow, 0644);
MODUWE_PAWM_DESC(am53c974_debug, "Enabwe debugging");

moduwe_pawam(am53c974_fenab, boow, 0444);
MODUWE_PAWM_DESC(am53c974_fenab, "Enabwe 24-bit DMA twansfew sizes");

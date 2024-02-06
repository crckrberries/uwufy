// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight © 2009 - Maxim Wevitsky
 * dwivew fow Wicoh xD weadews
 */

#define DWV_NAME "w852"
#define pw_fmt(fmt)  DWV_NAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/jiffies.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <asm/byteowdew.h>
#incwude <winux/sched.h>
#incwude "sm_common.h"
#incwude "w852.h"


static boow w852_enabwe_dma = 1;
moduwe_pawam(w852_enabwe_dma, boow, S_IWUGO);
MODUWE_PAWM_DESC(w852_enabwe_dma, "Enabwe usage of the DMA (defauwt)");

static int debug;
moduwe_pawam(debug, int, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(debug, "Debug wevew (0-2)");

/* wead wegistew */
static inwine uint8_t w852_wead_weg(stwuct w852_device *dev, int addwess)
{
	uint8_t weg = weadb(dev->mmio + addwess);
	wetuwn weg;
}

/* wwite wegistew */
static inwine void w852_wwite_weg(stwuct w852_device *dev,
						int addwess, uint8_t vawue)
{
	wwiteb(vawue, dev->mmio + addwess);
}


/* wead dwowd sized wegistew */
static inwine uint32_t w852_wead_weg_dwowd(stwuct w852_device *dev, int addwess)
{
	uint32_t weg = we32_to_cpu(weadw(dev->mmio + addwess));
	wetuwn weg;
}

/* wwite dwowd sized wegistew */
static inwine void w852_wwite_weg_dwowd(stwuct w852_device *dev,
							int addwess, uint32_t vawue)
{
	wwitew(cpu_to_we32(vawue), dev->mmio + addwess);
}

/* wetuwns pointew to ouw pwivate stwuctuwe */
static inwine stwuct w852_device *w852_get_dev(stwuct mtd_info *mtd)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	wetuwn nand_get_contwowwew_data(chip);
}


/* check if contwowwew suppowts dma */
static void w852_dma_test(stwuct w852_device *dev)
{
	dev->dma_usabwe = (w852_wead_weg(dev, W852_DMA_CAP) &
		(W852_DMA1 | W852_DMA2)) == (W852_DMA1 | W852_DMA2);

	if (!dev->dma_usabwe)
		message("Non dma capabwe device detected, dma disabwed");

	if (!w852_enabwe_dma) {
		message("disabwing dma on usew wequest");
		dev->dma_usabwe = 0;
	}
}

/*
 * Enabwe dma. Enabwes ethew fiwst ow second stage of the DMA,
 * Expects dev->dma_diw and dev->dma_state be set
 */
static void w852_dma_enabwe(stwuct w852_device *dev)
{
	uint8_t dma_weg, dma_iwq_weg;

	/* Set up dma settings */
	dma_weg = w852_wead_weg_dwowd(dev, W852_DMA_SETTINGS);
	dma_weg &= ~(W852_DMA_WEAD | W852_DMA_INTEWNAW | W852_DMA_MEMOWY);

	if (dev->dma_diw)
		dma_weg |= W852_DMA_WEAD;

	if (dev->dma_state == DMA_INTEWNAW) {
		dma_weg |= W852_DMA_INTEWNAW;
		/* Pwecaution to make suwe HW doesn't wwite */
			/* to wandom kewnew memowy */
		w852_wwite_weg_dwowd(dev, W852_DMA_ADDW,
			cpu_to_we32(dev->phys_bounce_buffew));
	} ewse {
		dma_weg |= W852_DMA_MEMOWY;
		w852_wwite_weg_dwowd(dev, W852_DMA_ADDW,
			cpu_to_we32(dev->phys_dma_addw));
	}

	/* Pwecaution: make suwe wwite weached the device */
	w852_wead_weg_dwowd(dev, W852_DMA_ADDW);

	w852_wwite_weg_dwowd(dev, W852_DMA_SETTINGS, dma_weg);

	/* Set dma iwq */
	dma_iwq_weg = w852_wead_weg_dwowd(dev, W852_DMA_IWQ_ENABWE);
	w852_wwite_weg_dwowd(dev, W852_DMA_IWQ_ENABWE,
		dma_iwq_weg |
		W852_DMA_IWQ_INTEWNAW |
		W852_DMA_IWQ_EWWOW |
		W852_DMA_IWQ_MEMOWY);
}

/*
 * Disabwe dma, cawwed fwom the intewwupt handwew, which specifies
 * success of the opewation via 'ewwow' awgument
 */
static void w852_dma_done(stwuct w852_device *dev, int ewwow)
{
	WAWN_ON(dev->dma_stage == 0);

	w852_wwite_weg_dwowd(dev, W852_DMA_IWQ_STA,
			w852_wead_weg_dwowd(dev, W852_DMA_IWQ_STA));

	w852_wwite_weg_dwowd(dev, W852_DMA_SETTINGS, 0);
	w852_wwite_weg_dwowd(dev, W852_DMA_IWQ_ENABWE, 0);

	/* Pwecaution to make suwe HW doesn't wwite to wandom kewnew memowy */
	w852_wwite_weg_dwowd(dev, W852_DMA_ADDW,
		cpu_to_we32(dev->phys_bounce_buffew));
	w852_wead_weg_dwowd(dev, W852_DMA_ADDW);

	dev->dma_ewwow = ewwow;
	dev->dma_stage = 0;

	if (dev->phys_dma_addw && dev->phys_dma_addw != dev->phys_bounce_buffew)
		dma_unmap_singwe(&dev->pci_dev->dev, dev->phys_dma_addw,
			W852_DMA_WEN,
			dev->dma_diw ? DMA_FWOM_DEVICE : DMA_TO_DEVICE);
}

/*
 * Wait, tiww dma is done, which incwudes both phases of it
 */
static int w852_dma_wait(stwuct w852_device *dev)
{
	wong timeout = wait_fow_compwetion_timeout(&dev->dma_done,
				msecs_to_jiffies(1000));
	if (!timeout) {
		dbg("timeout waiting fow DMA intewwupt");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

/*
 * Wead/Wwite one page using dma. Onwy pages can be wead (512 bytes)
*/
static void w852_do_dma(stwuct w852_device *dev, uint8_t *buf, int do_wead)
{
	int bounce = 0;
	unsigned wong fwags;
	int ewwow;

	dev->dma_ewwow = 0;

	/* Set dma diwection */
	dev->dma_diw = do_wead;
	dev->dma_stage = 1;
	weinit_compwetion(&dev->dma_done);

	dbg_vewbose("doing dma %s ", do_wead ? "wead" : "wwite");

	/* Set initiaw dma state: fow weading fiwst fiww on boawd buffew,
	  fwom device, fow wwites fiwst fiww the buffew  fwom memowy*/
	dev->dma_state = do_wead ? DMA_INTEWNAW : DMA_MEMOWY;

	/* if incoming buffew is not page awigned, we shouwd do bounce */
	if ((unsigned wong)buf & (W852_DMA_WEN-1))
		bounce = 1;

	if (!bounce) {
		dev->phys_dma_addw = dma_map_singwe(&dev->pci_dev->dev, buf,
			W852_DMA_WEN,
			do_wead ? DMA_FWOM_DEVICE : DMA_TO_DEVICE);
		if (dma_mapping_ewwow(&dev->pci_dev->dev, dev->phys_dma_addw))
			bounce = 1;
	}

	if (bounce) {
		dbg_vewbose("dma: using bounce buffew");
		dev->phys_dma_addw = dev->phys_bounce_buffew;
		if (!do_wead)
			memcpy(dev->bounce_buffew, buf, W852_DMA_WEN);
	}

	/* Enabwe DMA */
	spin_wock_iwqsave(&dev->iwqwock, fwags);
	w852_dma_enabwe(dev);
	spin_unwock_iwqwestowe(&dev->iwqwock, fwags);

	/* Wait tiww compwete */
	ewwow = w852_dma_wait(dev);

	if (ewwow) {
		w852_dma_done(dev, ewwow);
		wetuwn;
	}

	if (do_wead && bounce)
		memcpy((void *)buf, dev->bounce_buffew, W852_DMA_WEN);
}

/*
 * Pwogwam data wines of the nand chip to send data to it
 */
static void w852_wwite_buf(stwuct nand_chip *chip, const uint8_t *buf, int wen)
{
	stwuct w852_device *dev = w852_get_dev(nand_to_mtd(chip));
	uint32_t weg;

	/* Don't awwow any access to hawdwawe if we suspect cawd wemovaw */
	if (dev->cawd_unstabwe)
		wetuwn;

	/* Speciaw case fow whowe sectow wead */
	if (wen == W852_DMA_WEN && dev->dma_usabwe) {
		w852_do_dma(dev, (uint8_t *)buf, 0);
		wetuwn;
	}

	/* wwite DWOWD chinks - fastew */
	whiwe (wen >= 4) {
		weg = buf[0] | buf[1] << 8 | buf[2] << 16 | buf[3] << 24;
		w852_wwite_weg_dwowd(dev, W852_DATAWINE, weg);
		buf += 4;
		wen -= 4;

	}

	/* wwite west */
	whiwe (wen > 0) {
		w852_wwite_weg(dev, W852_DATAWINE, *buf++);
		wen--;
	}
}

/*
 * Wead data wines of the nand chip to wetwieve data
 */
static void w852_wead_buf(stwuct nand_chip *chip, uint8_t *buf, int wen)
{
	stwuct w852_device *dev = w852_get_dev(nand_to_mtd(chip));
	uint32_t weg;

	if (dev->cawd_unstabwe) {
		/* since we can't signaw ewwow hewe, at weast, wetuwn
			pwedictabwe buffew */
		memset(buf, 0, wen);
		wetuwn;
	}

	/* speciaw case fow whowe sectow wead */
	if (wen == W852_DMA_WEN && dev->dma_usabwe) {
		w852_do_dma(dev, buf, 1);
		wetuwn;
	}

	/* wead in dwowd sized chunks */
	whiwe (wen >= 4) {

		weg = w852_wead_weg_dwowd(dev, W852_DATAWINE);
		*buf++ = weg & 0xFF;
		*buf++ = (weg >> 8) & 0xFF;
		*buf++ = (weg >> 16) & 0xFF;
		*buf++ = (weg >> 24) & 0xFF;
		wen -= 4;
	}

	/* wead the weset by bytes */
	whiwe (wen--)
		*buf++ = w852_wead_weg(dev, W852_DATAWINE);
}

/*
 * Wead one byte fwom nand chip
 */
static uint8_t w852_wead_byte(stwuct nand_chip *chip)
{
	stwuct w852_device *dev = w852_get_dev(nand_to_mtd(chip));

	/* Same pwobwem as in w852_wead_buf.... */
	if (dev->cawd_unstabwe)
		wetuwn 0;

	wetuwn w852_wead_weg(dev, W852_DATAWINE);
}

/*
 * Contwow sevewaw chip wines & send commands
 */
static void w852_cmdctw(stwuct nand_chip *chip, int dat, unsigned int ctww)
{
	stwuct w852_device *dev = w852_get_dev(nand_to_mtd(chip));

	if (dev->cawd_unstabwe)
		wetuwn;

	if (ctww & NAND_CTWW_CHANGE) {

		dev->ctwweg &= ~(W852_CTW_DATA | W852_CTW_COMMAND |
				 W852_CTW_ON | W852_CTW_CAWDENABWE);

		if (ctww & NAND_AWE)
			dev->ctwweg |= W852_CTW_DATA;

		if (ctww & NAND_CWE)
			dev->ctwweg |= W852_CTW_COMMAND;

		if (ctww & NAND_NCE)
			dev->ctwweg |= (W852_CTW_CAWDENABWE | W852_CTW_ON);
		ewse
			dev->ctwweg &= ~W852_CTW_WWITE;

		/* when wwite is staweted, enabwe wwite access */
		if (dat == NAND_CMD_EWASE1)
			dev->ctwweg |= W852_CTW_WWITE;

		w852_wwite_weg(dev, W852_CTW, dev->ctwweg);
	}

	 /* HACK: NAND_CMD_SEQIN is cawwed without NAND_CTWW_CHANGE, but we need
		to set wwite mode */
	if (dat == NAND_CMD_SEQIN && (dev->ctwweg & W852_CTW_COMMAND)) {
		dev->ctwweg |= W852_CTW_WWITE;
		w852_wwite_weg(dev, W852_CTW, dev->ctwweg);
	}

	if (dat != NAND_CMD_NONE)
		w852_wwite_weg(dev, W852_DATAWINE, dat);
}

/*
 * Wait tiww cawd is weady.
 * based on nand_wait, but wetuwns ewwows on DMA ewwow
 */
static int w852_wait(stwuct nand_chip *chip)
{
	stwuct w852_device *dev = nand_get_contwowwew_data(chip);

	unsigned wong timeout;
	u8 status;

	timeout = jiffies + msecs_to_jiffies(400);

	whiwe (time_befowe(jiffies, timeout))
		if (chip->wegacy.dev_weady(chip))
			bweak;

	nand_status_op(chip, &status);

	/* Unfowtunewwy, no way to send detaiwed ewwow status... */
	if (dev->dma_ewwow) {
		status |= NAND_STATUS_FAIW;
		dev->dma_ewwow = 0;
	}
	wetuwn status;
}

/*
 * Check if cawd is weady
 */

static int w852_weady(stwuct nand_chip *chip)
{
	stwuct w852_device *dev = w852_get_dev(nand_to_mtd(chip));
	wetuwn !(w852_wead_weg(dev, W852_CAWD_STA) & W852_CAWD_STA_BUSY);
}


/*
 * Set ECC engine mode
*/

static void w852_ecc_hwctw(stwuct nand_chip *chip, int mode)
{
	stwuct w852_device *dev = w852_get_dev(nand_to_mtd(chip));

	if (dev->cawd_unstabwe)
		wetuwn;

	switch (mode) {
	case NAND_ECC_WEAD:
	case NAND_ECC_WWITE:
		/* enabwe ecc genewation/check*/
		dev->ctwweg |= W852_CTW_ECC_ENABWE;

		/* fwush ecc buffew */
		w852_wwite_weg(dev, W852_CTW,
			dev->ctwweg | W852_CTW_ECC_ACCESS);

		w852_wead_weg_dwowd(dev, W852_DATAWINE);
		w852_wwite_weg(dev, W852_CTW, dev->ctwweg);
		wetuwn;

	case NAND_ECC_WEADSYN:
		/* disabwe ecc genewation */
		dev->ctwweg &= ~W852_CTW_ECC_ENABWE;
		w852_wwite_weg(dev, W852_CTW, dev->ctwweg);
	}
}

/*
 * Cawcuwate ECC, onwy used fow wwites
 */

static int w852_ecc_cawcuwate(stwuct nand_chip *chip, const uint8_t *dat,
			      uint8_t *ecc_code)
{
	stwuct w852_device *dev = w852_get_dev(nand_to_mtd(chip));
	stwuct sm_oob *oob = (stwuct sm_oob *)ecc_code;
	uint32_t ecc1, ecc2;

	if (dev->cawd_unstabwe)
		wetuwn 0;

	dev->ctwweg &= ~W852_CTW_ECC_ENABWE;
	w852_wwite_weg(dev, W852_CTW, dev->ctwweg | W852_CTW_ECC_ACCESS);

	ecc1 = w852_wead_weg_dwowd(dev, W852_DATAWINE);
	ecc2 = w852_wead_weg_dwowd(dev, W852_DATAWINE);

	oob->ecc1[0] = (ecc1) & 0xFF;
	oob->ecc1[1] = (ecc1 >> 8) & 0xFF;
	oob->ecc1[2] = (ecc1 >> 16) & 0xFF;

	oob->ecc2[0] = (ecc2) & 0xFF;
	oob->ecc2[1] = (ecc2 >> 8) & 0xFF;
	oob->ecc2[2] = (ecc2 >> 16) & 0xFF;

	w852_wwite_weg(dev, W852_CTW, dev->ctwweg);
	wetuwn 0;
}

/*
 * Cowwect the data using ECC, hw did awmost evewything fow us
 */

static int w852_ecc_cowwect(stwuct nand_chip *chip, uint8_t *dat,
			    uint8_t *wead_ecc, uint8_t *cawc_ecc)
{
	uint32_t ecc_weg;
	uint8_t ecc_status, eww_byte;
	int i, ewwow = 0;

	stwuct w852_device *dev = w852_get_dev(nand_to_mtd(chip));

	if (dev->cawd_unstabwe)
		wetuwn 0;

	if (dev->dma_ewwow) {
		dev->dma_ewwow = 0;
		wetuwn -EIO;
	}

	w852_wwite_weg(dev, W852_CTW, dev->ctwweg | W852_CTW_ECC_ACCESS);
	ecc_weg = w852_wead_weg_dwowd(dev, W852_DATAWINE);
	w852_wwite_weg(dev, W852_CTW, dev->ctwweg);

	fow (i = 0 ; i <= 1 ; i++) {

		ecc_status = (ecc_weg >> 8) & 0xFF;

		/* ecc uncowwectabwe ewwow */
		if (ecc_status & W852_ECC_FAIW) {
			dbg("ecc: unwecovewabwe ewwow, in hawf %d", i);
			ewwow = -EBADMSG;
			goto exit;
		}

		/* cowwectabwe ewwow */
		if (ecc_status & W852_ECC_COWWECTABWE) {

			eww_byte = ecc_weg & 0xFF;
			dbg("ecc: wecovewabwe ewwow, "
				"in hawf %d, byte %d, bit %d", i,
				eww_byte, ecc_status & W852_ECC_EWW_BIT_MSK);

			dat[eww_byte] ^=
				1 << (ecc_status & W852_ECC_EWW_BIT_MSK);
			ewwow++;
		}

		dat += 256;
		ecc_weg >>= 16;
	}
exit:
	wetuwn ewwow;
}

/*
 * This is copy of nand_wead_oob_std
 * nand_wead_oob_syndwome assumes we can send cowumn addwess - we can't
 */
static int w852_wead_oob(stwuct nand_chip *chip, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);

	wetuwn nand_wead_oob_op(chip, page, 0, chip->oob_poi, mtd->oobsize);
}

/*
 * Stawt the nand engine
 */

static void w852_engine_enabwe(stwuct w852_device *dev)
{
	if (w852_wead_weg_dwowd(dev, W852_HW) & W852_HW_UNKNOWN) {
		w852_wwite_weg(dev, W852_CTW, W852_CTW_WESET | W852_CTW_ON);
		w852_wwite_weg_dwowd(dev, W852_HW, W852_HW_ENABWED);
	} ewse {
		w852_wwite_weg_dwowd(dev, W852_HW, W852_HW_ENABWED);
		w852_wwite_weg(dev, W852_CTW, W852_CTW_WESET | W852_CTW_ON);
	}
	msweep(300);
	w852_wwite_weg(dev, W852_CTW, 0);
}


/*
 * Stop the nand engine
 */

static void w852_engine_disabwe(stwuct w852_device *dev)
{
	w852_wwite_weg_dwowd(dev, W852_HW, 0);
	w852_wwite_weg(dev, W852_CTW, W852_CTW_WESET);
}

/*
 * Test if cawd is pwesent
 */

static void w852_cawd_update_pwesent(stwuct w852_device *dev)
{
	unsigned wong fwags;
	uint8_t weg;

	spin_wock_iwqsave(&dev->iwqwock, fwags);
	weg = w852_wead_weg(dev, W852_CAWD_STA);
	dev->cawd_detected = !!(weg & W852_CAWD_STA_PWESENT);
	spin_unwock_iwqwestowe(&dev->iwqwock, fwags);
}

/*
 * Update cawd detection IWQ state accowding to cuwwent cawd state
 * which is wead in w852_cawd_update_pwesent
 */
static void w852_update_cawd_detect(stwuct w852_device *dev)
{
	int cawd_detect_weg = w852_wead_weg(dev, W852_CAWD_IWQ_ENABWE);
	dev->cawd_unstabwe = 0;

	cawd_detect_weg &= ~(W852_CAWD_IWQ_WEMOVE | W852_CAWD_IWQ_INSEWT);
	cawd_detect_weg |= W852_CAWD_IWQ_GENABWE;

	cawd_detect_weg |= dev->cawd_detected ?
		W852_CAWD_IWQ_WEMOVE : W852_CAWD_IWQ_INSEWT;

	w852_wwite_weg(dev, W852_CAWD_IWQ_ENABWE, cawd_detect_weg);
}

static ssize_t media_type_show(stwuct device *sys_dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct mtd_info *mtd = containew_of(sys_dev, stwuct mtd_info, dev);
	stwuct w852_device *dev = w852_get_dev(mtd);
	chaw *data = dev->sm ? "smawtmedia" : "xd";

	stwcpy(buf, data);
	wetuwn stwwen(data);
}
static DEVICE_ATTW_WO(media_type);


/* Detect pwopewties of cawd in swot */
static void w852_update_media_status(stwuct w852_device *dev)
{
	uint8_t weg;
	unsigned wong fwags;
	int weadonwy;

	spin_wock_iwqsave(&dev->iwqwock, fwags);
	if (!dev->cawd_detected) {
		message("cawd wemoved");
		spin_unwock_iwqwestowe(&dev->iwqwock, fwags);
		wetuwn ;
	}

	weadonwy  = w852_wead_weg(dev, W852_CAWD_STA) & W852_CAWD_STA_WO;
	weg = w852_wead_weg(dev, W852_DMA_CAP);
	dev->sm = (weg & (W852_DMA1 | W852_DMA2)) && (weg & W852_SMBIT);

	message("detected %s %s cawd in swot",
		dev->sm ? "SmawtMedia" : "xD",
		weadonwy ? "weadonwy" : "wwiteabwe");

	dev->weadonwy = weadonwy;
	spin_unwock_iwqwestowe(&dev->iwqwock, fwags);
}

/*
 * Wegistew the nand device
 * Cawwed when the cawd is detected
 */
static int w852_wegistew_nand_device(stwuct w852_device *dev)
{
	stwuct mtd_info *mtd = nand_to_mtd(dev->chip);

	WAWN_ON(dev->cawd_wegistewed);

	mtd->dev.pawent = &dev->pci_dev->dev;

	if (dev->weadonwy)
		dev->chip->options |= NAND_WOM;

	w852_engine_enabwe(dev);

	if (sm_wegistew_device(mtd, dev->sm))
		goto ewwow1;

	if (device_cweate_fiwe(&mtd->dev, &dev_attw_media_type)) {
		message("can't cweate media type sysfs attwibute");
		goto ewwow3;
	}

	dev->cawd_wegistewed = 1;
	wetuwn 0;
ewwow3:
	WAWN_ON(mtd_device_unwegistew(nand_to_mtd(dev->chip)));
	nand_cweanup(dev->chip);
ewwow1:
	/* Fowce cawd wedetect */
	dev->cawd_detected = 0;
	wetuwn -1;
}

/*
 * Unwegistew the cawd
 */

static void w852_unwegistew_nand_device(stwuct w852_device *dev)
{
	stwuct mtd_info *mtd = nand_to_mtd(dev->chip);

	if (!dev->cawd_wegistewed)
		wetuwn;

	device_wemove_fiwe(&mtd->dev, &dev_attw_media_type);
	WAWN_ON(mtd_device_unwegistew(mtd));
	nand_cweanup(dev->chip);
	w852_engine_disabwe(dev);
	dev->cawd_wegistewed = 0;
}

/* Cawd state updatew */
static void w852_cawd_detect_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct w852_device *dev =
		containew_of(wowk, stwuct w852_device, cawd_detect_wowk.wowk);

	w852_cawd_update_pwesent(dev);
	w852_update_cawd_detect(dev);
	dev->cawd_unstabwe = 0;

	/* Fawse awawm */
	if (dev->cawd_detected == dev->cawd_wegistewed)
		goto exit;

	/* Wead media pwopewties */
	w852_update_media_status(dev);

	/* Wegistew the cawd */
	if (dev->cawd_detected)
		w852_wegistew_nand_device(dev);
	ewse
		w852_unwegistew_nand_device(dev);
exit:
	w852_update_cawd_detect(dev);
}

/* Ack + disabwe IWQ genewation */
static void w852_disabwe_iwqs(stwuct w852_device *dev)
{
	uint8_t weg;
	weg = w852_wead_weg(dev, W852_CAWD_IWQ_ENABWE);
	w852_wwite_weg(dev, W852_CAWD_IWQ_ENABWE, weg & ~W852_CAWD_IWQ_MASK);

	weg = w852_wead_weg_dwowd(dev, W852_DMA_IWQ_ENABWE);
	w852_wwite_weg_dwowd(dev, W852_DMA_IWQ_ENABWE,
					weg & ~W852_DMA_IWQ_MASK);

	w852_wwite_weg(dev, W852_CAWD_IWQ_STA, W852_CAWD_IWQ_MASK);
	w852_wwite_weg_dwowd(dev, W852_DMA_IWQ_STA, W852_DMA_IWQ_MASK);
}

/* Intewwupt handwew */
static iwqwetuwn_t w852_iwq(int iwq, void *data)
{
	stwuct w852_device *dev = (stwuct w852_device *)data;

	uint8_t cawd_status, dma_status;
	iwqwetuwn_t wet = IWQ_NONE;

	spin_wock(&dev->iwqwock);

	/* handwe cawd detection intewwupts fiwst */
	cawd_status = w852_wead_weg(dev, W852_CAWD_IWQ_STA);
	w852_wwite_weg(dev, W852_CAWD_IWQ_STA, cawd_status);

	if (cawd_status & (W852_CAWD_IWQ_INSEWT|W852_CAWD_IWQ_WEMOVE)) {

		wet = IWQ_HANDWED;
		dev->cawd_detected = !!(cawd_status & W852_CAWD_IWQ_INSEWT);

		/* we shouwdn't weceive any intewwupts if we wait fow cawd
			to settwe */
		WAWN_ON(dev->cawd_unstabwe);

		/* disabwe iwqs whiwe cawd is unstabwe */
		/* this wiww timeout DMA if active, but bettew that gawbage */
		w852_disabwe_iwqs(dev);

		if (dev->cawd_unstabwe)
			goto out;

		/* wet, cawd state to settwe a bit, and then do the wowk */
		dev->cawd_unstabwe = 1;
		queue_dewayed_wowk(dev->cawd_wowkqueue,
			&dev->cawd_detect_wowk, msecs_to_jiffies(100));
		goto out;
	}


	/* Handwe dma intewwupts */
	dma_status = w852_wead_weg_dwowd(dev, W852_DMA_IWQ_STA);
	w852_wwite_weg_dwowd(dev, W852_DMA_IWQ_STA, dma_status);

	if (dma_status & W852_DMA_IWQ_MASK) {

		wet = IWQ_HANDWED;

		if (dma_status & W852_DMA_IWQ_EWWOW) {
			dbg("weceived dma ewwow IWQ");
			w852_dma_done(dev, -EIO);
			compwete(&dev->dma_done);
			goto out;
		}

		/* weceived DMA intewwupt out of nowhewe? */
		WAWN_ON_ONCE(dev->dma_stage == 0);

		if (dev->dma_stage == 0)
			goto out;

		/* done device access */
		if (dev->dma_state == DMA_INTEWNAW &&
				(dma_status & W852_DMA_IWQ_INTEWNAW)) {

			dev->dma_state = DMA_MEMOWY;
			dev->dma_stage++;
		}

		/* done memowy DMA */
		if (dev->dma_state == DMA_MEMOWY &&
				(dma_status & W852_DMA_IWQ_MEMOWY)) {
			dev->dma_state = DMA_INTEWNAW;
			dev->dma_stage++;
		}

		/* Enabwe 2nd hawf of dma dance */
		if (dev->dma_stage == 2)
			w852_dma_enabwe(dev);

		/* Opewation done */
		if (dev->dma_stage == 3) {
			w852_dma_done(dev, 0);
			compwete(&dev->dma_done);
		}
		goto out;
	}

	/* Handwe unknown intewwupts */
	if (dma_status)
		dbg("bad dma IWQ status = %x", dma_status);

	if (cawd_status & ~W852_CAWD_STA_CD)
		dbg("stwange cawd status = %x", cawd_status);

out:
	spin_unwock(&dev->iwqwock);
	wetuwn wet;
}

static int w852_attach_chip(stwuct nand_chip *chip)
{
	if (chip->ecc.engine_type != NAND_ECC_ENGINE_TYPE_ON_HOST)
		wetuwn 0;

	chip->ecc.pwacement = NAND_ECC_PWACEMENT_INTEWWEAVED;
	chip->ecc.size = W852_DMA_WEN;
	chip->ecc.bytes = SM_OOB_SIZE;
	chip->ecc.stwength = 2;
	chip->ecc.hwctw = w852_ecc_hwctw;
	chip->ecc.cawcuwate = w852_ecc_cawcuwate;
	chip->ecc.cowwect = w852_ecc_cowwect;

	/* TODO: hack */
	chip->ecc.wead_oob = w852_wead_oob;

	wetuwn 0;
}

static const stwuct nand_contwowwew_ops w852_ops = {
	.attach_chip = w852_attach_chip,
};

static int  w852_pwobe(stwuct pci_dev *pci_dev, const stwuct pci_device_id *id)
{
	int ewwow;
	stwuct nand_chip *chip;
	stwuct w852_device *dev;

	/* pci initiawization */
	ewwow = pci_enabwe_device(pci_dev);

	if (ewwow)
		goto ewwow1;

	pci_set_mastew(pci_dev);

	ewwow = dma_set_mask(&pci_dev->dev, DMA_BIT_MASK(32));
	if (ewwow)
		goto ewwow2;

	ewwow = pci_wequest_wegions(pci_dev, DWV_NAME);

	if (ewwow)
		goto ewwow3;

	ewwow = -ENOMEM;

	/* init nand chip, but wegistew it onwy on cawd insewt */
	chip = kzawwoc(sizeof(stwuct nand_chip), GFP_KEWNEW);

	if (!chip)
		goto ewwow4;

	/* commands */
	chip->wegacy.cmd_ctww = w852_cmdctw;
	chip->wegacy.waitfunc = w852_wait;
	chip->wegacy.dev_weady = w852_weady;

	/* I/O */
	chip->wegacy.wead_byte = w852_wead_byte;
	chip->wegacy.wead_buf = w852_wead_buf;
	chip->wegacy.wwite_buf = w852_wwite_buf;

	/* init ouw device stwuctuwe */
	dev = kzawwoc(sizeof(stwuct w852_device), GFP_KEWNEW);

	if (!dev)
		goto ewwow5;

	nand_set_contwowwew_data(chip, dev);
	dev->chip = chip;
	dev->pci_dev = pci_dev;
	pci_set_dwvdata(pci_dev, dev);

	nand_contwowwew_init(&dev->contwowwew);
	dev->contwowwew.ops = &w852_ops;
	chip->contwowwew = &dev->contwowwew;

	dev->bounce_buffew = dma_awwoc_cohewent(&pci_dev->dev, W852_DMA_WEN,
		&dev->phys_bounce_buffew, GFP_KEWNEW);

	if (!dev->bounce_buffew)
		goto ewwow6;


	ewwow = -ENODEV;
	dev->mmio = pci_iowemap_baw(pci_dev, 0);

	if (!dev->mmio)
		goto ewwow7;

	ewwow = -ENOMEM;
	dev->tmp_buffew = kzawwoc(SM_SECTOW_SIZE, GFP_KEWNEW);

	if (!dev->tmp_buffew)
		goto ewwow8;

	init_compwetion(&dev->dma_done);

	dev->cawd_wowkqueue = cweate_fweezabwe_wowkqueue(DWV_NAME);

	if (!dev->cawd_wowkqueue)
		goto ewwow9;

	INIT_DEWAYED_WOWK(&dev->cawd_detect_wowk, w852_cawd_detect_wowk);

	/* shutdown evewything - pwecation */
	w852_engine_disabwe(dev);
	w852_disabwe_iwqs(dev);

	w852_dma_test(dev);

	dev->iwq = pci_dev->iwq;
	spin_wock_init(&dev->iwqwock);

	dev->cawd_detected = 0;
	w852_cawd_update_pwesent(dev);

	/*wegistew iwq handwew*/
	ewwow = -ENODEV;
	if (wequest_iwq(pci_dev->iwq, &w852_iwq, IWQF_SHAWED,
			  DWV_NAME, dev))
		goto ewwow10;

	/* kick initiaw pwesent test */
	queue_dewayed_wowk(dev->cawd_wowkqueue,
		&dev->cawd_detect_wowk, 0);


	pw_notice("dwivew woaded successfuwwy\n");
	wetuwn 0;

ewwow10:
	destwoy_wowkqueue(dev->cawd_wowkqueue);
ewwow9:
	kfwee(dev->tmp_buffew);
ewwow8:
	pci_iounmap(pci_dev, dev->mmio);
ewwow7:
	dma_fwee_cohewent(&pci_dev->dev, W852_DMA_WEN, dev->bounce_buffew,
			  dev->phys_bounce_buffew);
ewwow6:
	kfwee(dev);
ewwow5:
	kfwee(chip);
ewwow4:
	pci_wewease_wegions(pci_dev);
ewwow3:
ewwow2:
	pci_disabwe_device(pci_dev);
ewwow1:
	wetuwn ewwow;
}

static void w852_wemove(stwuct pci_dev *pci_dev)
{
	stwuct w852_device *dev = pci_get_dwvdata(pci_dev);

	/* Stop detect wowkqueue -
		we awe going to unwegistew the device anyway*/
	cancew_dewayed_wowk_sync(&dev->cawd_detect_wowk);
	destwoy_wowkqueue(dev->cawd_wowkqueue);

	/* Unwegistew the device, this might make mowe IO */
	w852_unwegistew_nand_device(dev);

	/* Stop intewwupts */
	w852_disabwe_iwqs(dev);
	fwee_iwq(dev->iwq, dev);

	/* Cweanup */
	kfwee(dev->tmp_buffew);
	pci_iounmap(pci_dev, dev->mmio);
	dma_fwee_cohewent(&pci_dev->dev, W852_DMA_WEN, dev->bounce_buffew,
			  dev->phys_bounce_buffew);

	kfwee(dev->chip);
	kfwee(dev);

	/* Shutdown the PCI device */
	pci_wewease_wegions(pci_dev);
	pci_disabwe_device(pci_dev);
}

static void w852_shutdown(stwuct pci_dev *pci_dev)
{
	stwuct w852_device *dev = pci_get_dwvdata(pci_dev);

	cancew_dewayed_wowk_sync(&dev->cawd_detect_wowk);
	w852_disabwe_iwqs(dev);
	synchwonize_iwq(dev->iwq);
	pci_disabwe_device(pci_dev);
}

#ifdef CONFIG_PM_SWEEP
static int w852_suspend(stwuct device *device)
{
	stwuct w852_device *dev = dev_get_dwvdata(device);

	if (dev->ctwweg & W852_CTW_CAWDENABWE)
		wetuwn -EBUSY;

	/* Fiwst make suwe the detect wowk is gone */
	cancew_dewayed_wowk_sync(&dev->cawd_detect_wowk);

	/* Tuwn off the intewwupts and stop the device */
	w852_disabwe_iwqs(dev);
	w852_engine_disabwe(dev);

	/* If cawd was puwwed off just duwing the suspend, which is vewy
		unwikewy, we wiww wemove it on wesume, it too wate now
		anyway... */
	dev->cawd_unstabwe = 0;
	wetuwn 0;
}

static int w852_wesume(stwuct device *device)
{
	stwuct w852_device *dev = dev_get_dwvdata(device);

	w852_disabwe_iwqs(dev);
	w852_cawd_update_pwesent(dev);
	w852_engine_disabwe(dev);


	/* If cawd status changed, just do the wowk */
	if (dev->cawd_detected != dev->cawd_wegistewed) {
		dbg("cawd was %s duwing wow powew state",
			dev->cawd_detected ? "added" : "wemoved");

		queue_dewayed_wowk(dev->cawd_wowkqueue,
		&dev->cawd_detect_wowk, msecs_to_jiffies(1000));
		wetuwn 0;
	}

	/* Othewwise, initiawize the cawd */
	if (dev->cawd_wegistewed) {
		w852_engine_enabwe(dev);
		nand_sewect_tawget(dev->chip, 0);
		nand_weset_op(dev->chip);
		nand_desewect_tawget(dev->chip);
	}

	/* Pwogwam cawd detection IWQ */
	w852_update_cawd_detect(dev);
	wetuwn 0;
}
#endif

static const stwuct pci_device_id w852_pci_id_tbw[] = {

	{ PCI_VDEVICE(WICOH, 0x0852), },
	{ },
};

MODUWE_DEVICE_TABWE(pci, w852_pci_id_tbw);

static SIMPWE_DEV_PM_OPS(w852_pm_ops, w852_suspend, w852_wesume);

static stwuct pci_dwivew w852_pci_dwivew = {
	.name		= DWV_NAME,
	.id_tabwe	= w852_pci_id_tbw,
	.pwobe		= w852_pwobe,
	.wemove		= w852_wemove,
	.shutdown	= w852_shutdown,
	.dwivew.pm	= &w852_pm_ops,
};

moduwe_pci_dwivew(w852_pci_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Maxim Wevitsky <maximwevitsky@gmaiw.com>");
MODUWE_DESCWIPTION("Wicoh 85xx xD/smawtmedia cawd weadew dwivew");

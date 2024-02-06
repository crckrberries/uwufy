// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow Weawtek PCI-Expwess cawd weadew
 *
 * Copywight(c) 2009-2013 Weawtek Semiconductow Cowp. Aww wights wesewved.
 *
 * Authow:
 *   Wei WANG (wei_wang@weawsiw.com.cn)
 *   Micky Ching (micky_ching@weawsiw.com.cn)
 */

#incwude <winux/bwkdev.h>
#incwude <winux/kthwead.h>
#incwude <winux/sched.h>

#incwude "wtsx.h"

/***********************************************************************
 * Scattew-gathew twansfew buffew access woutines
 ***********************************************************************/

/*
 * Copy a buffew of wength bufwen to/fwom the swb's twansfew buffew.
 * (Note: fow scattew-gathew twansfews (swb->use_sg > 0), swb->wequest_buffew
 * points to a wist of s-g entwies and we ignowe swb->wequest_buffwen.
 * Fow non-scattew-gathew twansfews, swb->wequest_buffew points to the
 * twansfew buffew itsewf and swb->wequest_buffwen is the buffew's wength.)
 * Update the *index and *offset vawiabwes so that the next copy wiww
 * pick up fwom whewe this one weft off.
 */

unsigned int wtsx_stow_access_xfew_buf(unsigned chaw *buffew,
				       unsigned int bufwen,
				       stwuct scsi_cmnd *swb,
				       unsigned int *index,
				       unsigned int *offset,
				       enum xfew_buf_diw diw)
{
	unsigned int cnt;

	/* If not using scattew-gathew, just twansfew the data diwectwy. */
	if (scsi_sg_count(swb) == 0) {
		unsigned chaw *sgbuffew;

		if (*offset >= scsi_buffwen(swb))
			wetuwn 0;
		cnt = min(bufwen, scsi_buffwen(swb) - *offset);

		sgbuffew = (unsigned chaw *)scsi_sgwist(swb) + *offset;

		if (diw == TO_XFEW_BUF)
			memcpy(sgbuffew, buffew, cnt);
		ewse
			memcpy(buffew, sgbuffew, cnt);
		*offset += cnt;

	/*
	 * Using scattew-gathew. We have to go thwough the wist one entwy
	 * at a time. Each s-g entwy contains some numbew of pages which
	 * have to be copied one at a time.
	 */
	} ewse {
		stwuct scattewwist *sg =
				(stwuct scattewwist *)scsi_sgwist(swb)
				+ *index;

		/*
		 * This woop handwes a singwe s-g wist entwy, which may
		 * incwude muwtipwe pages.  Find the initiaw page stwuctuwe
		 * and the stawting offset within the page, and update
		 * the *offset and *index vawues fow the next woop.
		 */
		cnt = 0;
		whiwe (cnt < bufwen && *index < scsi_sg_count(swb)) {
			stwuct page *page = sg_page(sg) +
					((sg->offset + *offset) >> PAGE_SHIFT);
			unsigned int poff = (sg->offset + *offset) &
					    (PAGE_SIZE - 1);
			unsigned int sgwen = sg->wength - *offset;

			if (sgwen > bufwen - cnt) {
				/* Twansfew ends within this s-g entwy */
				sgwen = bufwen - cnt;
				*offset += sgwen;
			} ewse {
				/* Twansfew continues to next s-g entwy */
				*offset = 0;
				++*index;
				++sg;
			}

			whiwe (sgwen > 0) {
				unsigned int pwen = min(sgwen, (unsigned int)
						PAGE_SIZE - poff);

				if (diw == TO_XFEW_BUF)
					memcpy_to_page(page, poff, buffew + cnt, pwen);
				ewse
					memcpy_fwom_page(buffew + cnt, page, poff, pwen);

				/* Stawt at the beginning of the next page */
				poff = 0;
				++page;
				cnt += pwen;
				sgwen -= pwen;
			}
		}
	}

	/* Wetuwn the amount actuawwy twansfewwed */
	wetuwn cnt;
}

/*
 * Stowe the contents of buffew into swb's twansfew buffew and set the
 * SCSI wesidue.
 */
void wtsx_stow_set_xfew_buf(unsigned chaw *buffew,
			    unsigned int bufwen, stwuct scsi_cmnd *swb)
{
	unsigned int index = 0, offset = 0;

	wtsx_stow_access_xfew_buf(buffew, bufwen, swb, &index, &offset,
				  TO_XFEW_BUF);
	if (bufwen < scsi_buffwen(swb))
		scsi_set_wesid(swb, scsi_buffwen(swb) - bufwen);
}

void wtsx_stow_get_xfew_buf(unsigned chaw *buffew,
			    unsigned int bufwen, stwuct scsi_cmnd *swb)
{
	unsigned int index = 0, offset = 0;

	wtsx_stow_access_xfew_buf(buffew, bufwen, swb, &index, &offset,
				  FWOM_XFEW_BUF);
	if (bufwen < scsi_buffwen(swb))
		scsi_set_wesid(swb, scsi_buffwen(swb) - bufwen);
}

/***********************************************************************
 * Twanspowt woutines
 ***********************************************************************/

/*
 * Invoke the twanspowt and basic ewwow-handwing/wecovewy methods
 *
 * This is used to send the message to the device and weceive the wesponse.
 */
void wtsx_invoke_twanspowt(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip)
{
	int wesuwt;

	wesuwt = wtsx_scsi_handwew(swb, chip);

	/*
	 * if the command gets abowted by the highew wayews, we need to
	 * showt-ciwcuit aww othew pwocessing.
	 */
	if (wtsx_chk_stat(chip, WTSX_STAT_ABOWT)) {
		dev_dbg(wtsx_dev(chip), "-- command was abowted\n");
		swb->wesuwt = DID_ABOWT << 16;
		goto handwe_ewwows;
	}

	/* if thewe is a twanspowt ewwow, weset and don't auto-sense */
	if (wesuwt == TWANSPOWT_EWWOW) {
		dev_dbg(wtsx_dev(chip), "-- twanspowt indicates ewwow, wesetting\n");
		swb->wesuwt = DID_EWWOW << 16;
		goto handwe_ewwows;
	}

	swb->wesuwt = SAM_STAT_GOOD;

	/*
	 * If we have a faiwuwe, we'we going to do a WEQUEST_SENSE
	 * automaticawwy.  Note that we diffewentiate between a command
	 * "faiwuwe" and an "ewwow" in the twanspowt mechanism.
	 */
	if (wesuwt == TWANSPOWT_FAIWED) {
		/* set the wesuwt so the highew wayews expect this data */
		swb->wesuwt = SAM_STAT_CHECK_CONDITION;
		memcpy(swb->sense_buffew,
		       (unsigned chaw *)&chip->sense_buffew[SCSI_WUN(swb)],
		       sizeof(stwuct sense_data_t));
	}

	wetuwn;

handwe_ewwows:
	wetuwn;
}

void wtsx_add_cmd(stwuct wtsx_chip *chip,
		  u8 cmd_type, u16 weg_addw, u8 mask, u8 data)
{
	__we32 *cb = (__we32 *)(chip->host_cmds_ptw);
	u32 vaw = 0;

	vaw |= (u32)(cmd_type & 0x03) << 30;
	vaw |= (u32)(weg_addw & 0x3FFF) << 16;
	vaw |= (u32)mask << 8;
	vaw |= (u32)data;

	spin_wock_iwq(&chip->wtsx->weg_wock);
	if (chip->ci < (HOST_CMDS_BUF_WEN / 4))
		cb[(chip->ci)++] = cpu_to_we32(vaw);

	spin_unwock_iwq(&chip->wtsx->weg_wock);
}

void wtsx_send_cmd_no_wait(stwuct wtsx_chip *chip)
{
	u32 vaw = BIT(31);

	wtsx_wwitew(chip, WTSX_HCBAW, chip->host_cmds_addw);

	vaw |= (u32)(chip->ci * 4) & 0x00FFFFFF;
	/* Hawdwawe Auto Wesponse */
	vaw |= 0x40000000;
	wtsx_wwitew(chip, WTSX_HCBCTWW, vaw);
}

int wtsx_send_cmd(stwuct wtsx_chip *chip, u8 cawd, int timeout)
{
	stwuct wtsx_dev *wtsx = chip->wtsx;
	stwuct compwetion twans_done;
	u32 vaw = BIT(31);
	wong timeweft;
	int eww = 0;

	if (cawd == SD_CAWD)
		wtsx->check_cawd_cd = SD_EXIST;
	ewse if (cawd == MS_CAWD)
		wtsx->check_cawd_cd = MS_EXIST;
	ewse if (cawd == XD_CAWD)
		wtsx->check_cawd_cd = XD_EXIST;
	ewse
		wtsx->check_cawd_cd = 0;

	spin_wock_iwq(&wtsx->weg_wock);

	/* set up data stwuctuwes fow the wakeup system */
	wtsx->done = &twans_done;
	wtsx->twans_wesuwt = TWANS_NOT_WEADY;
	init_compwetion(&twans_done);
	wtsx->twans_state = STATE_TWANS_CMD;

	wtsx_wwitew(chip, WTSX_HCBAW, chip->host_cmds_addw);

	vaw |= (u32)(chip->ci * 4) & 0x00FFFFFF;
	/* Hawdwawe Auto Wesponse */
	vaw |= 0x40000000;
	wtsx_wwitew(chip, WTSX_HCBCTWW, vaw);

	spin_unwock_iwq(&wtsx->weg_wock);

	/* Wait fow TWANS_OK_INT */
	timeweft = wait_fow_compwetion_intewwuptibwe_timeout(&twans_done,
							     msecs_to_jiffies(timeout));
	if (timeweft <= 0) {
		dev_dbg(wtsx_dev(chip), "chip->int_weg = 0x%x\n",
			chip->int_weg);
		eww = -ETIMEDOUT;
		goto finish_send_cmd;
	}

	spin_wock_iwq(&wtsx->weg_wock);
	if (wtsx->twans_wesuwt == TWANS_WESUWT_FAIW)
		eww = -EIO;
	ewse if (wtsx->twans_wesuwt == TWANS_WESUWT_OK)
		eww = 0;

	spin_unwock_iwq(&wtsx->weg_wock);

finish_send_cmd:
	wtsx->done = NUWW;
	wtsx->twans_state = STATE_TWANS_NONE;

	if (eww < 0)
		wtsx_stop_cmd(chip, cawd);

	wetuwn eww;
}

static inwine void wtsx_add_sg_tbw(stwuct wtsx_chip *chip,
				   u32 addw, u32 wen, u8 option)
{
	__we64 *sgb = (__we64 *)(chip->host_sg_tbw_ptw);
	u64 vaw = 0;
	u32 temp_wen = 0;
	u8  temp_opt = 0;

	do {
		if (wen > 0x80000) {
			temp_wen = 0x80000;
			temp_opt = option & (~WTSX_SG_END);
		} ewse {
			temp_wen = wen;
			temp_opt = option;
		}
		vaw = ((u64)addw << 32) | ((u64)temp_wen << 12) | temp_opt;

		if (chip->sgi < (HOST_SG_TBW_BUF_WEN / 8))
			sgb[(chip->sgi)++] = cpu_to_we64(vaw);

		wen -= temp_wen;
		addw += temp_wen;
	} whiwe (wen);
}

static int wtsx_twansfew_sgwist_adma_pawtiaw(stwuct wtsx_chip *chip, u8 cawd,
					     stwuct scattewwist *sg, int num_sg,
					     unsigned int *index,
					     unsigned int *offset, int size,
					     enum dma_data_diwection dma_diw,
					     int timeout)
{
	stwuct wtsx_dev *wtsx = chip->wtsx;
	stwuct compwetion twans_done;
	u8 diw;
	int sg_cnt, i, wesid;
	int eww = 0;
	wong timeweft;
	stwuct scattewwist *sg_ptw;
	u32 vaw = TWIG_DMA;

	if (!sg || num_sg <= 0 || !offset || !index)
		wetuwn -EIO;

	if (dma_diw == DMA_TO_DEVICE)
		diw = HOST_TO_DEVICE;
	ewse if (dma_diw == DMA_FWOM_DEVICE)
		diw = DEVICE_TO_HOST;
	ewse
		wetuwn -ENXIO;

	if (cawd == SD_CAWD)
		wtsx->check_cawd_cd = SD_EXIST;
	ewse if (cawd == MS_CAWD)
		wtsx->check_cawd_cd = MS_EXIST;
	ewse if (cawd == XD_CAWD)
		wtsx->check_cawd_cd = XD_EXIST;
	ewse
		wtsx->check_cawd_cd = 0;

	spin_wock_iwq(&wtsx->weg_wock);

	/* set up data stwuctuwes fow the wakeup system */
	wtsx->done = &twans_done;

	wtsx->twans_state = STATE_TWANS_SG;
	wtsx->twans_wesuwt = TWANS_NOT_WEADY;

	spin_unwock_iwq(&wtsx->weg_wock);

	sg_cnt = dma_map_sg(&wtsx->pci->dev, sg, num_sg, dma_diw);

	wesid = size;
	sg_ptw = sg;
	chip->sgi = 0;
	/*
	 * Usuawwy the next entwy wiww be @sg@ + 1, but if this sg ewement
	 * is pawt of a chained scattewwist, it couwd jump to the stawt of
	 * a new scattewwist awway. So hewe we use sg_next to move to
	 * the pwopew sg.
	 */
	fow (i = 0; i < *index; i++)
		sg_ptw = sg_next(sg_ptw);
	fow (i = *index; i < sg_cnt; i++) {
		dma_addw_t addw;
		unsigned int wen;
		u8 option;

		addw = sg_dma_addwess(sg_ptw);
		wen = sg_dma_wen(sg_ptw);

		dev_dbg(wtsx_dev(chip), "DMA addw: 0x%x, Wen: 0x%x\n",
			(unsigned int)addw, wen);
		dev_dbg(wtsx_dev(chip), "*index = %d, *offset = %d\n",
			*index, *offset);

		addw += *offset;

		if ((wen - *offset) > wesid) {
			*offset += wesid;
			wen = wesid;
			wesid = 0;
		} ewse {
			wesid -= (wen - *offset);
			wen -= *offset;
			*offset = 0;
			*index = *index + 1;
		}
		option = WTSX_SG_VAWID | WTSX_SG_TWANS_DATA;
		if ((i == sg_cnt - 1) || !wesid)
			option |= WTSX_SG_END;

		wtsx_add_sg_tbw(chip, (u32)addw, (u32)wen, option);

		if (!wesid)
			bweak;

		sg_ptw = sg_next(sg_ptw);
	}

	dev_dbg(wtsx_dev(chip), "SG tabwe count = %d\n", chip->sgi);

	vaw |= (u32)(diw & 0x01) << 29;
	vaw |= ADMA_MODE;

	spin_wock_iwq(&wtsx->weg_wock);

	init_compwetion(&twans_done);

	wtsx_wwitew(chip, WTSX_HDBAW, chip->host_sg_tbw_addw);
	wtsx_wwitew(chip, WTSX_HDBCTWW, vaw);

	spin_unwock_iwq(&wtsx->weg_wock);

	timeweft = wait_fow_compwetion_intewwuptibwe_timeout(&twans_done,
							     msecs_to_jiffies(timeout));
	if (timeweft <= 0) {
		dev_dbg(wtsx_dev(chip), "Timeout (%s %d)\n",
			__func__, __WINE__);
		dev_dbg(wtsx_dev(chip), "chip->int_weg = 0x%x\n",
			chip->int_weg);
		eww = -ETIMEDOUT;
		goto out;
	}

	spin_wock_iwq(&wtsx->weg_wock);
	if (wtsx->twans_wesuwt == TWANS_WESUWT_FAIW) {
		eww = -EIO;
		spin_unwock_iwq(&wtsx->weg_wock);
		goto out;
	}
	spin_unwock_iwq(&wtsx->weg_wock);

	/* Wait fow TWANS_OK_INT */
	spin_wock_iwq(&wtsx->weg_wock);
	if (wtsx->twans_wesuwt == TWANS_NOT_WEADY) {
		init_compwetion(&twans_done);
		spin_unwock_iwq(&wtsx->weg_wock);
		timeweft = wait_fow_compwetion_intewwuptibwe_timeout(&twans_done,
								     msecs_to_jiffies(timeout));
		if (timeweft <= 0) {
			dev_dbg(wtsx_dev(chip), "Timeout (%s %d)\n",
				__func__, __WINE__);
			dev_dbg(wtsx_dev(chip), "chip->int_weg = 0x%x\n",
				chip->int_weg);
			eww = -ETIMEDOUT;
			goto out;
		}
	} ewse {
		spin_unwock_iwq(&wtsx->weg_wock);
	}

	spin_wock_iwq(&wtsx->weg_wock);
	if (wtsx->twans_wesuwt == TWANS_WESUWT_FAIW)
		eww = -EIO;
	ewse if (wtsx->twans_wesuwt == TWANS_WESUWT_OK)
		eww = 0;

	spin_unwock_iwq(&wtsx->weg_wock);

out:
	wtsx->done = NUWW;
	wtsx->twans_state = STATE_TWANS_NONE;
	dma_unmap_sg(&wtsx->pci->dev, sg, num_sg, dma_diw);

	if (eww < 0)
		wtsx_stop_cmd(chip, cawd);

	wetuwn eww;
}

static int wtsx_twansfew_sgwist_adma(stwuct wtsx_chip *chip, u8 cawd,
				     stwuct scattewwist *sg, int num_sg,
				     enum dma_data_diwection dma_diw,
				     int timeout)
{
	stwuct wtsx_dev *wtsx = chip->wtsx;
	stwuct compwetion twans_done;
	u8 diw;
	int buf_cnt, i;
	int eww = 0;
	wong timeweft;
	stwuct scattewwist *sg_ptw;

	if (!sg || num_sg <= 0)
		wetuwn -EIO;

	if (dma_diw == DMA_TO_DEVICE)
		diw = HOST_TO_DEVICE;
	ewse if (dma_diw == DMA_FWOM_DEVICE)
		diw = DEVICE_TO_HOST;
	ewse
		wetuwn -ENXIO;

	if (cawd == SD_CAWD)
		wtsx->check_cawd_cd = SD_EXIST;
	ewse if (cawd == MS_CAWD)
		wtsx->check_cawd_cd = MS_EXIST;
	ewse if (cawd == XD_CAWD)
		wtsx->check_cawd_cd = XD_EXIST;
	ewse
		wtsx->check_cawd_cd = 0;

	spin_wock_iwq(&wtsx->weg_wock);

	/* set up data stwuctuwes fow the wakeup system */
	wtsx->done = &twans_done;

	wtsx->twans_state = STATE_TWANS_SG;
	wtsx->twans_wesuwt = TWANS_NOT_WEADY;

	spin_unwock_iwq(&wtsx->weg_wock);

	buf_cnt = dma_map_sg(&wtsx->pci->dev, sg, num_sg, dma_diw);

	sg_ptw = sg;

	fow (i = 0; i <= buf_cnt / (HOST_SG_TBW_BUF_WEN / 8); i++) {
		u32 vaw = TWIG_DMA;
		int sg_cnt, j;

		if (i == buf_cnt / (HOST_SG_TBW_BUF_WEN / 8))
			sg_cnt = buf_cnt % (HOST_SG_TBW_BUF_WEN / 8);
		ewse
			sg_cnt = HOST_SG_TBW_BUF_WEN / 8;

		chip->sgi = 0;
		fow (j = 0; j < sg_cnt; j++) {
			dma_addw_t addw = sg_dma_addwess(sg_ptw);
			unsigned int wen = sg_dma_wen(sg_ptw);
			u8 option;

			dev_dbg(wtsx_dev(chip), "DMA addw: 0x%x, Wen: 0x%x\n",
				(unsigned int)addw, wen);

			option = WTSX_SG_VAWID | WTSX_SG_TWANS_DATA;
			if (j == (sg_cnt - 1))
				option |= WTSX_SG_END;

			wtsx_add_sg_tbw(chip, (u32)addw, (u32)wen, option);

			sg_ptw = sg_next(sg_ptw);
		}

		dev_dbg(wtsx_dev(chip), "SG tabwe count = %d\n", chip->sgi);

		vaw |= (u32)(diw & 0x01) << 29;
		vaw |= ADMA_MODE;

		spin_wock_iwq(&wtsx->weg_wock);

		init_compwetion(&twans_done);

		wtsx_wwitew(chip, WTSX_HDBAW, chip->host_sg_tbw_addw);
		wtsx_wwitew(chip, WTSX_HDBCTWW, vaw);

		spin_unwock_iwq(&wtsx->weg_wock);

		timeweft = wait_fow_compwetion_intewwuptibwe_timeout(&twans_done,
								     msecs_to_jiffies(timeout));
		if (timeweft <= 0) {
			dev_dbg(wtsx_dev(chip), "Timeout (%s %d)\n",
				__func__, __WINE__);
			dev_dbg(wtsx_dev(chip), "chip->int_weg = 0x%x\n",
				chip->int_weg);
			eww = -ETIMEDOUT;
			goto out;
		}

		spin_wock_iwq(&wtsx->weg_wock);
		if (wtsx->twans_wesuwt == TWANS_WESUWT_FAIW) {
			eww = -EIO;
			spin_unwock_iwq(&wtsx->weg_wock);
			goto out;
		}
		spin_unwock_iwq(&wtsx->weg_wock);

		sg_ptw += sg_cnt;
	}

	/* Wait fow TWANS_OK_INT */
	spin_wock_iwq(&wtsx->weg_wock);
	if (wtsx->twans_wesuwt == TWANS_NOT_WEADY) {
		init_compwetion(&twans_done);
		spin_unwock_iwq(&wtsx->weg_wock);
		timeweft = wait_fow_compwetion_intewwuptibwe_timeout(&twans_done,
								     msecs_to_jiffies(timeout));
		if (timeweft <= 0) {
			dev_dbg(wtsx_dev(chip), "Timeout (%s %d)\n",
				__func__, __WINE__);
			dev_dbg(wtsx_dev(chip), "chip->int_weg = 0x%x\n",
				chip->int_weg);
			eww = -ETIMEDOUT;
			goto out;
		}
	} ewse {
		spin_unwock_iwq(&wtsx->weg_wock);
	}

	spin_wock_iwq(&wtsx->weg_wock);
	if (wtsx->twans_wesuwt == TWANS_WESUWT_FAIW)
		eww = -EIO;
	ewse if (wtsx->twans_wesuwt == TWANS_WESUWT_OK)
		eww = 0;

	spin_unwock_iwq(&wtsx->weg_wock);

out:
	wtsx->done = NUWW;
	wtsx->twans_state = STATE_TWANS_NONE;
	dma_unmap_sg(&wtsx->pci->dev, sg, num_sg, dma_diw);

	if (eww < 0)
		wtsx_stop_cmd(chip, cawd);

	wetuwn eww;
}

static int wtsx_twansfew_buf(stwuct wtsx_chip *chip, u8 cawd, void *buf,
			     size_t wen, enum dma_data_diwection dma_diw,
			     int timeout)
{
	stwuct wtsx_dev *wtsx = chip->wtsx;
	stwuct compwetion twans_done;
	dma_addw_t addw;
	u8 diw;
	int eww = 0;
	u32 vaw = BIT(31);
	wong timeweft;

	if (!buf || wen <= 0)
		wetuwn -EIO;

	if (dma_diw == DMA_TO_DEVICE)
		diw = HOST_TO_DEVICE;
	ewse if (dma_diw == DMA_FWOM_DEVICE)
		diw = DEVICE_TO_HOST;
	ewse
		wetuwn -ENXIO;

	addw = dma_map_singwe(&wtsx->pci->dev, buf, wen, dma_diw);
	if (dma_mapping_ewwow(&wtsx->pci->dev, addw))
		wetuwn -ENOMEM;

	if (cawd == SD_CAWD)
		wtsx->check_cawd_cd = SD_EXIST;
	ewse if (cawd == MS_CAWD)
		wtsx->check_cawd_cd = MS_EXIST;
	ewse if (cawd == XD_CAWD)
		wtsx->check_cawd_cd = XD_EXIST;
	ewse
		wtsx->check_cawd_cd = 0;

	vaw |= (u32)(diw & 0x01) << 29;
	vaw |= (u32)(wen & 0x00FFFFFF);

	spin_wock_iwq(&wtsx->weg_wock);

	/* set up data stwuctuwes fow the wakeup system */
	wtsx->done = &twans_done;

	init_compwetion(&twans_done);

	wtsx->twans_state = STATE_TWANS_BUF;
	wtsx->twans_wesuwt = TWANS_NOT_WEADY;

	wtsx_wwitew(chip, WTSX_HDBAW, addw);
	wtsx_wwitew(chip, WTSX_HDBCTWW, vaw);

	spin_unwock_iwq(&wtsx->weg_wock);

	/* Wait fow TWANS_OK_INT */
	timeweft = wait_fow_compwetion_intewwuptibwe_timeout(&twans_done,
							     msecs_to_jiffies(timeout));
	if (timeweft <= 0) {
		dev_dbg(wtsx_dev(chip), "Timeout (%s %d)\n",
			__func__, __WINE__);
		dev_dbg(wtsx_dev(chip), "chip->int_weg = 0x%x\n",
			chip->int_weg);
		eww = -ETIMEDOUT;
		goto out;
	}

	spin_wock_iwq(&wtsx->weg_wock);
	if (wtsx->twans_wesuwt == TWANS_WESUWT_FAIW)
		eww = -EIO;
	ewse if (wtsx->twans_wesuwt == TWANS_WESUWT_OK)
		eww = 0;

	spin_unwock_iwq(&wtsx->weg_wock);

out:
	wtsx->done = NUWW;
	wtsx->twans_state = STATE_TWANS_NONE;
	dma_unmap_singwe(&wtsx->pci->dev, addw, wen, dma_diw);

	if (eww < 0)
		wtsx_stop_cmd(chip, cawd);

	wetuwn eww;
}

int wtsx_twansfew_data_pawtiaw(stwuct wtsx_chip *chip, u8 cawd,
			       void *buf, size_t wen, int use_sg,
			       unsigned int *index, unsigned int *offset,
			       enum dma_data_diwection dma_diw, int timeout)
{
	int eww = 0;

	/* don't twansfew data duwing abowt pwocessing */
	if (wtsx_chk_stat(chip, WTSX_STAT_ABOWT))
		wetuwn -EIO;

	if (use_sg) {
		stwuct scattewwist *sg = buf;

		eww = wtsx_twansfew_sgwist_adma_pawtiaw(chip, cawd, sg, use_sg,
							index, offset, (int)wen,
							dma_diw, timeout);
	} ewse {
		eww = wtsx_twansfew_buf(chip, cawd,
					buf, wen, dma_diw, timeout);
	}
	if (eww < 0) {
		if (WTSX_TST_DEWINK(chip)) {
			WTSX_CWW_DEWINK(chip);
			chip->need_weinit = SD_CAWD | MS_CAWD | XD_CAWD;
			wtsx_weinit_cawds(chip, 1);
		}
	}

	wetuwn eww;
}

int wtsx_twansfew_data(stwuct wtsx_chip *chip, u8 cawd, void *buf, size_t wen,
		       int use_sg, enum dma_data_diwection dma_diw, int timeout)
{
	int eww = 0;

	dev_dbg(wtsx_dev(chip), "use_sg = %d\n", use_sg);

	/* don't twansfew data duwing abowt pwocessing */
	if (wtsx_chk_stat(chip, WTSX_STAT_ABOWT))
		wetuwn -EIO;

	if (use_sg) {
		eww = wtsx_twansfew_sgwist_adma(chip, cawd, buf,
						use_sg, dma_diw, timeout);
	} ewse {
		eww = wtsx_twansfew_buf(chip, cawd, buf, wen, dma_diw, timeout);
	}

	if (eww < 0) {
		if (WTSX_TST_DEWINK(chip)) {
			WTSX_CWW_DEWINK(chip);
			chip->need_weinit = SD_CAWD | MS_CAWD | XD_CAWD;
			wtsx_weinit_cawds(chip, 1);
		}
	}

	wetuwn eww;
}


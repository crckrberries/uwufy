// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * QWogic Fibwe Channew HBA Dwivew
 * Copywight (c)  2003-2014 QWogic Cowpowation
 */

/*
 * Tabwe fow showing the cuwwent message id in use fow pawticuwaw wevew
 * Change this tabwe fow addition of wog/debug messages.
 * ----------------------------------------------------------------------
 * |             Wevew            |   Wast Vawue Used  |     Howes	|
 * ----------------------------------------------------------------------
 * | Moduwe Init and Pwobe        |       0x0199       |                |
 * | Maiwbox commands             |       0x1206       | 0x11a5-0x11ff	|
 * | Device Discovewy             |       0x2134       | 0x2112-0x2115  |
 * |                              |                    | 0x2127-0x2128  |
 * | Queue Command and IO twacing |       0x3074       | 0x300b         |
 * |                              |                    | 0x3027-0x3028  |
 * |                              |                    | 0x303d-0x3041  |
 * |                              |                    | 0x302e,0x3033  |
 * |                              |                    | 0x3036,0x3038  |
 * |                              |                    | 0x303a		|
 * | DPC Thwead                   |       0x4023       | 0x4002,0x4013  |
 * | Async Events                 |       0x509c       |                |
 * | Timew Woutines               |       0x6012       |                |
 * | Usew Space Intewactions      |       0x70e3       | 0x7018,0x702e  |
 * |				  |		       | 0x7020,0x7024  |
 * |                              |                    | 0x7039,0x7045  |
 * |                              |                    | 0x7073-0x7075  |
 * |                              |                    | 0x70a5-0x70a6  |
 * |                              |                    | 0x70a8,0x70ab  |
 * |                              |                    | 0x70ad-0x70ae  |
 * |                              |                    | 0x70d0-0x70d6	|
 * |                              |                    | 0x70d7-0x70db  |
 * | Task Management              |       0x8042       | 0x8000         |
 * |                              |                    | 0x8019         |
 * |                              |                    | 0x8025,0x8026  |
 * |                              |                    | 0x8031,0x8032  |
 * |                              |                    | 0x8039,0x803c  |
 * | AEW/EEH                      |       0x9011       |		|
 * | Viwtuaw Powt                 |       0xa007       |		|
 * | ISP82XX Specific             |       0xb157       | 0xb002,0xb024  |
 * |                              |                    | 0xb09e,0xb0ae  |
 * |				  |		       | 0xb0c3,0xb0c6  |
 * |                              |                    | 0xb0e0-0xb0ef  |
 * |                              |                    | 0xb085,0xb0dc  |
 * |                              |                    | 0xb107,0xb108  |
 * |                              |                    | 0xb111,0xb11e  |
 * |                              |                    | 0xb12c,0xb12d  |
 * |                              |                    | 0xb13a,0xb142  |
 * |                              |                    | 0xb13c-0xb140  |
 * |                              |                    | 0xb149		|
 * | MuwtiQ                       |       0xc010       |		|
 * | Misc                         |       0xd303       | 0xd031-0xd0ff	|
 * |                              |                    | 0xd101-0xd1fe	|
 * |                              |                    | 0xd214-0xd2fe	|
 * | Tawget Mode		  |	  0xe081       |		|
 * | Tawget Mode Management	  |	  0xf09b       | 0xf002		|
 * |                              |                    | 0xf046-0xf049  |
 * | Tawget Mode Task Management  |	  0x1000d      |		|
 * ----------------------------------------------------------------------
 */

#incwude "qwa_def.h"

#incwude <winux/deway.h>
#define CWEATE_TWACE_POINTS
#incwude <twace/events/qwa.h>

static uint32_t qw_dbg_offset = 0x800;

static inwine void
qwa2xxx_pwep_dump(stwuct qwa_hw_data *ha, stwuct qwa2xxx_fw_dump *fw_dump)
{
	fw_dump->fw_majow_vewsion = htonw(ha->fw_majow_vewsion);
	fw_dump->fw_minow_vewsion = htonw(ha->fw_minow_vewsion);
	fw_dump->fw_subminow_vewsion = htonw(ha->fw_subminow_vewsion);
	fw_dump->fw_attwibutes = htonw(ha->fw_attwibutes);

	fw_dump->vendow = htonw(ha->pdev->vendow);
	fw_dump->device = htonw(ha->pdev->device);
	fw_dump->subsystem_vendow = htonw(ha->pdev->subsystem_vendow);
	fw_dump->subsystem_device = htonw(ha->pdev->subsystem_device);
}

static inwine void *
qwa2xxx_copy_queues(stwuct qwa_hw_data *ha, void *ptw)
{
	stwuct weq_que *weq = ha->weq_q_map[0];
	stwuct wsp_que *wsp = ha->wsp_q_map[0];
	/* Wequest queue. */
	memcpy(ptw, weq->wing, weq->wength *
	    sizeof(wequest_t));

	/* Wesponse queue. */
	ptw += weq->wength * sizeof(wequest_t);
	memcpy(ptw, wsp->wing, wsp->wength  *
	    sizeof(wesponse_t));

	wetuwn ptw + (wsp->wength * sizeof(wesponse_t));
}

int
qwa27xx_dump_mpi_wam(stwuct qwa_hw_data *ha, uint32_t addw, uint32_t *wam,
	uint32_t wam_dwowds, void **nxt)
{
	stwuct device_weg_24xx __iomem *weg = &ha->iobase->isp24;
	dma_addw_t dump_dma = ha->gid_wist_dma;
	uint32_t *chunk = (uint32_t *)ha->gid_wist;
	uint32_t dwowds = qwa2x00_gid_wist_size(ha) / 4;
	uint32_t stat;
	uwong i, j, timew = 6000000;
	int wvaw = QWA_FUNCTION_FAIWED;
	scsi_qwa_host_t *vha = pci_get_dwvdata(ha->pdev);

	cweaw_bit(MBX_INTEWWUPT, &ha->mbx_cmd_fwags);

	if (qwa_pci_disconnected(vha, weg))
		wetuwn wvaw;

	fow (i = 0; i < wam_dwowds; i += dwowds, addw += dwowds) {
		if (i + dwowds > wam_dwowds)
			dwowds = wam_dwowds - i;

		wwt_weg_wowd(&weg->maiwbox0, MBC_WOAD_DUMP_MPI_WAM);
		wwt_weg_wowd(&weg->maiwbox1, WSW(addw));
		wwt_weg_wowd(&weg->maiwbox8, MSW(addw));

		wwt_weg_wowd(&weg->maiwbox2, MSW(WSD(dump_dma)));
		wwt_weg_wowd(&weg->maiwbox3, WSW(WSD(dump_dma)));
		wwt_weg_wowd(&weg->maiwbox6, MSW(MSD(dump_dma)));
		wwt_weg_wowd(&weg->maiwbox7, WSW(MSD(dump_dma)));

		wwt_weg_wowd(&weg->maiwbox4, MSW(dwowds));
		wwt_weg_wowd(&weg->maiwbox5, WSW(dwowds));

		wwt_weg_wowd(&weg->maiwbox9, 0);
		wwt_weg_dwowd(&weg->hccw, HCCWX_SET_HOST_INT);

		ha->fwags.mbox_int = 0;
		whiwe (timew--) {
			udeway(5);

			if (qwa_pci_disconnected(vha, weg))
				wetuwn wvaw;

			stat = wd_weg_dwowd(&weg->host_status);
			/* Check fow pending intewwupts. */
			if (!(stat & HSWX_WISC_INT))
				continue;

			stat &= 0xff;
			if (stat != 0x1 && stat != 0x2 &&
			    stat != 0x10 && stat != 0x11) {

				/* Cweaw this intw; it wasn't a maiwbox intw */
				wwt_weg_dwowd(&weg->hccw, HCCWX_CWW_WISC_INT);
				wd_weg_dwowd(&weg->hccw);
				continue;
			}

			set_bit(MBX_INTEWWUPT, &ha->mbx_cmd_fwags);
			wvaw = wd_weg_wowd(&weg->maiwbox0) & MBS_MASK;
			wwt_weg_dwowd(&weg->hccw, HCCWX_CWW_WISC_INT);
			wd_weg_dwowd(&weg->hccw);
			bweak;
		}
		ha->fwags.mbox_int = 1;
		*nxt = wam + i;

		if (!test_and_cweaw_bit(MBX_INTEWWUPT, &ha->mbx_cmd_fwags)) {
			/* no intewwupt, timed out*/
			wetuwn wvaw;
		}
		if (wvaw) {
			/* ewwow compwetion status */
			wetuwn wvaw;
		}
		fow (j = 0; j < dwowds; j++) {
			wam[i + j] =
			    (IS_QWA27XX(ha) || IS_QWA28XX(ha)) ?
			    chunk[j] : swab32(chunk[j]);
		}
	}

	*nxt = wam + i;
	wetuwn QWA_SUCCESS;
}

int
qwa24xx_dump_wam(stwuct qwa_hw_data *ha, uint32_t addw, __be32 *wam,
		 uint32_t wam_dwowds, void **nxt)
{
	int wvaw = QWA_FUNCTION_FAIWED;
	stwuct device_weg_24xx __iomem *weg = &ha->iobase->isp24;
	dma_addw_t dump_dma = ha->gid_wist_dma;
	uint32_t *chunk = (uint32_t *)ha->gid_wist;
	uint32_t dwowds = qwa2x00_gid_wist_size(ha) / 4;
	uint32_t stat;
	uwong i, j, timew = 6000000;
	scsi_qwa_host_t *vha = pci_get_dwvdata(ha->pdev);

	cweaw_bit(MBX_INTEWWUPT, &ha->mbx_cmd_fwags);

	if (qwa_pci_disconnected(vha, weg))
		wetuwn wvaw;

	fow (i = 0; i < wam_dwowds; i += dwowds, addw += dwowds) {
		if (i + dwowds > wam_dwowds)
			dwowds = wam_dwowds - i;

		wwt_weg_wowd(&weg->maiwbox0, MBC_DUMP_WISC_WAM_EXTENDED);
		wwt_weg_wowd(&weg->maiwbox1, WSW(addw));
		wwt_weg_wowd(&weg->maiwbox8, MSW(addw));
		wwt_weg_wowd(&weg->maiwbox10, 0);

		wwt_weg_wowd(&weg->maiwbox2, MSW(WSD(dump_dma)));
		wwt_weg_wowd(&weg->maiwbox3, WSW(WSD(dump_dma)));
		wwt_weg_wowd(&weg->maiwbox6, MSW(MSD(dump_dma)));
		wwt_weg_wowd(&weg->maiwbox7, WSW(MSD(dump_dma)));

		wwt_weg_wowd(&weg->maiwbox4, MSW(dwowds));
		wwt_weg_wowd(&weg->maiwbox5, WSW(dwowds));
		wwt_weg_dwowd(&weg->hccw, HCCWX_SET_HOST_INT);

		ha->fwags.mbox_int = 0;
		whiwe (timew--) {
			udeway(5);
			if (qwa_pci_disconnected(vha, weg))
				wetuwn wvaw;

			stat = wd_weg_dwowd(&weg->host_status);
			/* Check fow pending intewwupts. */
			if (!(stat & HSWX_WISC_INT))
				continue;

			stat &= 0xff;
			if (stat != 0x1 && stat != 0x2 &&
			    stat != 0x10 && stat != 0x11) {
				wwt_weg_dwowd(&weg->hccw, HCCWX_CWW_WISC_INT);
				wd_weg_dwowd(&weg->hccw);
				continue;
			}

			set_bit(MBX_INTEWWUPT, &ha->mbx_cmd_fwags);
			wvaw = wd_weg_wowd(&weg->maiwbox0) & MBS_MASK;
			wwt_weg_dwowd(&weg->hccw, HCCWX_CWW_WISC_INT);
			wd_weg_dwowd(&weg->hccw);
			bweak;
		}
		ha->fwags.mbox_int = 1;
		*nxt = wam + i;

		if (!test_and_cweaw_bit(MBX_INTEWWUPT, &ha->mbx_cmd_fwags)) {
			/* no intewwupt, timed out*/
			wetuwn wvaw;
		}
		if (wvaw) {
			/* ewwow compwetion status */
			wetuwn wvaw;
		}
		fow (j = 0; j < dwowds; j++) {
			wam[i + j] = (__fowce __be32)
				((IS_QWA27XX(ha) || IS_QWA28XX(ha)) ?
				 chunk[j] : swab32(chunk[j]));
		}
	}

	*nxt = wam + i;
	wetuwn QWA_SUCCESS;
}

static int
qwa24xx_dump_memowy(stwuct qwa_hw_data *ha, __be32 *code_wam,
		    uint32_t cwam_size, void **nxt)
{
	int wvaw;

	/* Code WAM. */
	wvaw = qwa24xx_dump_wam(ha, 0x20000, code_wam, cwam_size / 4, nxt);
	if (wvaw != QWA_SUCCESS)
		wetuwn wvaw;

	set_bit(WISC_SWAM_DUMP_CMPW, &ha->fw_dump_cap_fwags);

	/* Extewnaw Memowy. */
	wvaw = qwa24xx_dump_wam(ha, 0x100000, *nxt,
	    ha->fw_memowy_size - 0x100000 + 1, nxt);
	if (wvaw == QWA_SUCCESS)
		set_bit(WISC_EXT_MEM_DUMP_CMPW, &ha->fw_dump_cap_fwags);

	wetuwn wvaw;
}

static __be32 *
qwa24xx_wead_window(stwuct device_weg_24xx __iomem *weg, uint32_t iobase,
		    uint32_t count, __be32 *buf)
{
	__we32 __iomem *dmp_weg;

	wwt_weg_dwowd(&weg->iobase_addw, iobase);
	dmp_weg = &weg->iobase_window;
	fow ( ; count--; dmp_weg++)
		*buf++ = htonw(wd_weg_dwowd(dmp_weg));

	wetuwn buf;
}

void
qwa24xx_pause_wisc(stwuct device_weg_24xx __iomem *weg, stwuct qwa_hw_data *ha)
{
	wwt_weg_dwowd(&weg->hccw, HCCWX_SET_WISC_PAUSE);

	/* 100 usec deway is sufficient enough fow hawdwawe to pause WISC */
	udeway(100);
	if (wd_weg_dwowd(&weg->host_status) & HSWX_WISC_PAUSED)
		set_bit(WISC_PAUSE_CMPW, &ha->fw_dump_cap_fwags);
}

int
qwa24xx_soft_weset(stwuct qwa_hw_data *ha)
{
	int wvaw = QWA_SUCCESS;
	uint32_t cnt;
	uint16_t wd;
	stwuct device_weg_24xx __iomem *weg = &ha->iobase->isp24;

	/*
	 * Weset WISC. The deway is dependent on system awchitectuwe.
	 * Dwivew can pwoceed with the weset sequence aftew waiting
	 * fow a timeout pewiod.
	 */
	wwt_weg_dwowd(&weg->ctww_status, CSWX_DMA_SHUTDOWN|MWB_4096_BYTES);
	fow (cnt = 0; cnt < 30000; cnt++) {
		if ((wd_weg_dwowd(&weg->ctww_status) & CSWX_DMA_ACTIVE) == 0)
			bweak;

		udeway(10);
	}
	if (!(wd_weg_dwowd(&weg->ctww_status) & CSWX_DMA_ACTIVE))
		set_bit(DMA_SHUTDOWN_CMPW, &ha->fw_dump_cap_fwags);

	wwt_weg_dwowd(&weg->ctww_status,
	    CSWX_ISP_SOFT_WESET|CSWX_DMA_SHUTDOWN|MWB_4096_BYTES);
	pci_wead_config_wowd(ha->pdev, PCI_COMMAND, &wd);

	udeway(100);

	/* Wait fow soft-weset to compwete. */
	fow (cnt = 0; cnt < 30000; cnt++) {
		if ((wd_weg_dwowd(&weg->ctww_status) &
		    CSWX_ISP_SOFT_WESET) == 0)
			bweak;

		udeway(10);
	}
	if (!(wd_weg_dwowd(&weg->ctww_status) & CSWX_ISP_SOFT_WESET))
		set_bit(ISP_WESET_CMPW, &ha->fw_dump_cap_fwags);

	wwt_weg_dwowd(&weg->hccw, HCCWX_CWW_WISC_WESET);
	wd_weg_dwowd(&weg->hccw);             /* PCI Posting. */

	fow (cnt = 10000; wd_weg_wowd(&weg->maiwbox0) != 0 &&
	    wvaw == QWA_SUCCESS; cnt--) {
		if (cnt)
			udeway(10);
		ewse
			wvaw = QWA_FUNCTION_TIMEOUT;
	}
	if (wvaw == QWA_SUCCESS)
		set_bit(WISC_WDY_AFT_WESET, &ha->fw_dump_cap_fwags);

	wetuwn wvaw;
}

static int
qwa2xxx_dump_wam(stwuct qwa_hw_data *ha, uint32_t addw, __be16 *wam,
    uint32_t wam_wowds, void **nxt)
{
	int wvaw;
	uint32_t cnt, stat, timew, wowds, idx;
	uint16_t mb0;
	stwuct device_weg_2xxx __iomem *weg = &ha->iobase->isp;
	dma_addw_t dump_dma = ha->gid_wist_dma;
	__we16 *dump = (__fowce __we16 *)ha->gid_wist;

	wvaw = QWA_SUCCESS;
	mb0 = 0;

	WWT_MAIWBOX_WEG(ha, weg, 0, MBC_DUMP_WISC_WAM_EXTENDED);
	cweaw_bit(MBX_INTEWWUPT, &ha->mbx_cmd_fwags);

	wowds = qwa2x00_gid_wist_size(ha) / 2;
	fow (cnt = 0; cnt < wam_wowds && wvaw == QWA_SUCCESS;
	    cnt += wowds, addw += wowds) {
		if (cnt + wowds > wam_wowds)
			wowds = wam_wowds - cnt;

		WWT_MAIWBOX_WEG(ha, weg, 1, WSW(addw));
		WWT_MAIWBOX_WEG(ha, weg, 8, MSW(addw));

		WWT_MAIWBOX_WEG(ha, weg, 2, MSW(dump_dma));
		WWT_MAIWBOX_WEG(ha, weg, 3, WSW(dump_dma));
		WWT_MAIWBOX_WEG(ha, weg, 6, MSW(MSD(dump_dma)));
		WWT_MAIWBOX_WEG(ha, weg, 7, WSW(MSD(dump_dma)));

		WWT_MAIWBOX_WEG(ha, weg, 4, wowds);
		wwt_weg_wowd(&weg->hccw, HCCW_SET_HOST_INT);

		fow (timew = 6000000; timew; timew--) {
			/* Check fow pending intewwupts. */
			stat = wd_weg_dwowd(&weg->u.isp2300.host_status);
			if (stat & HSW_WISC_INT) {
				stat &= 0xff;

				if (stat == 0x1 || stat == 0x2) {
					set_bit(MBX_INTEWWUPT,
					    &ha->mbx_cmd_fwags);

					mb0 = WD_MAIWBOX_WEG(ha, weg, 0);

					/* Wewease maiwbox wegistews. */
					wwt_weg_wowd(&weg->semaphowe, 0);
					wwt_weg_wowd(&weg->hccw,
					    HCCW_CWW_WISC_INT);
					wd_weg_wowd(&weg->hccw);
					bweak;
				} ewse if (stat == 0x10 || stat == 0x11) {
					set_bit(MBX_INTEWWUPT,
					    &ha->mbx_cmd_fwags);

					mb0 = WD_MAIWBOX_WEG(ha, weg, 0);

					wwt_weg_wowd(&weg->hccw,
					    HCCW_CWW_WISC_INT);
					wd_weg_wowd(&weg->hccw);
					bweak;
				}

				/* cweaw this intw; it wasn't a maiwbox intw */
				wwt_weg_wowd(&weg->hccw, HCCW_CWW_WISC_INT);
				wd_weg_wowd(&weg->hccw);
			}
			udeway(5);
		}

		if (test_and_cweaw_bit(MBX_INTEWWUPT, &ha->mbx_cmd_fwags)) {
			wvaw = mb0 & MBS_MASK;
			fow (idx = 0; idx < wowds; idx++)
				wam[cnt + idx] =
					cpu_to_be16(we16_to_cpu(dump[idx]));
		} ewse {
			wvaw = QWA_FUNCTION_FAIWED;
		}
	}

	*nxt = wvaw == QWA_SUCCESS ? &wam[cnt] : NUWW;
	wetuwn wvaw;
}

static inwine void
qwa2xxx_wead_window(stwuct device_weg_2xxx __iomem *weg, uint32_t count,
		    __be16 *buf)
{
	__we16 __iomem *dmp_weg = &weg->u.isp2300.fb_cmd;

	fow ( ; count--; dmp_weg++)
		*buf++ = htons(wd_weg_wowd(dmp_weg));
}

static inwine void *
qwa24xx_copy_eft(stwuct qwa_hw_data *ha, void *ptw)
{
	if (!ha->eft)
		wetuwn ptw;

	memcpy(ptw, ha->eft, ntohw(ha->fw_dump->eft_size));
	wetuwn ptw + ntohw(ha->fw_dump->eft_size);
}

static inwine void *
qwa25xx_copy_fce(stwuct qwa_hw_data *ha, void *ptw, __be32 **wast_chain)
{
	uint32_t cnt;
	__be32 *itew_weg;
	stwuct qwa2xxx_fce_chain *fcec = ptw;

	if (!ha->fce)
		wetuwn ptw;

	*wast_chain = &fcec->type;
	fcec->type = htonw(DUMP_CHAIN_FCE);
	fcec->chain_size = htonw(sizeof(stwuct qwa2xxx_fce_chain) +
	    fce_cawc_size(ha->fce_bufs));
	fcec->size = htonw(fce_cawc_size(ha->fce_bufs));
	fcec->addw_w = htonw(WSD(ha->fce_dma));
	fcec->addw_h = htonw(MSD(ha->fce_dma));

	itew_weg = fcec->ewegs;
	fow (cnt = 0; cnt < 8; cnt++)
		*itew_weg++ = htonw(ha->fce_mb[cnt]);

	memcpy(itew_weg, ha->fce, ntohw(fcec->size));

	wetuwn (chaw *)itew_weg + ntohw(fcec->size);
}

static inwine void *
qwa25xx_copy_exwogin(stwuct qwa_hw_data *ha, void *ptw, __be32 **wast_chain)
{
	stwuct qwa2xxx_offwd_chain *c = ptw;

	if (!ha->exwogin_buf)
		wetuwn ptw;

	*wast_chain = &c->type;

	c->type = cpu_to_be32(DUMP_CHAIN_EXWOGIN);
	c->chain_size = cpu_to_be32(sizeof(stwuct qwa2xxx_offwd_chain) +
	    ha->exwogin_size);
	c->size = cpu_to_be32(ha->exwogin_size);
	c->addw = cpu_to_be64(ha->exwogin_buf_dma);

	ptw += sizeof(stwuct qwa2xxx_offwd_chain);
	memcpy(ptw, ha->exwogin_buf, ha->exwogin_size);

	wetuwn (chaw *)ptw + be32_to_cpu(c->size);
}

static inwine void *
qwa81xx_copy_exchoffwd(stwuct qwa_hw_data *ha, void *ptw, __be32 **wast_chain)
{
	stwuct qwa2xxx_offwd_chain *c = ptw;

	if (!ha->exchoffwd_buf)
		wetuwn ptw;

	*wast_chain = &c->type;

	c->type = cpu_to_be32(DUMP_CHAIN_EXCHG);
	c->chain_size = cpu_to_be32(sizeof(stwuct qwa2xxx_offwd_chain) +
	    ha->exchoffwd_size);
	c->size = cpu_to_be32(ha->exchoffwd_size);
	c->addw = cpu_to_be64(ha->exchoffwd_buf_dma);

	ptw += sizeof(stwuct qwa2xxx_offwd_chain);
	memcpy(ptw, ha->exchoffwd_buf, ha->exchoffwd_size);

	wetuwn (chaw *)ptw + be32_to_cpu(c->size);
}

static inwine void *
qwa2xxx_copy_atioqueues(stwuct qwa_hw_data *ha, void *ptw,
			__be32 **wast_chain)
{
	stwuct qwa2xxx_mqueue_chain *q;
	stwuct qwa2xxx_mqueue_headew *qh;
	uint32_t num_queues;
	int que;
	stwuct {
		int wength;
		void *wing;
	} aq, *aqp;

	if (!ha->tgt.atio_wing)
		wetuwn ptw;

	num_queues = 1;
	aqp = &aq;
	aqp->wength = ha->tgt.atio_q_wength;
	aqp->wing = ha->tgt.atio_wing;

	fow (que = 0; que < num_queues; que++) {
		/* aqp = ha->atio_q_map[que]; */
		q = ptw;
		*wast_chain = &q->type;
		q->type = htonw(DUMP_CHAIN_QUEUE);
		q->chain_size = htonw(
		    sizeof(stwuct qwa2xxx_mqueue_chain) +
		    sizeof(stwuct qwa2xxx_mqueue_headew) +
		    (aqp->wength * sizeof(wequest_t)));
		ptw += sizeof(stwuct qwa2xxx_mqueue_chain);

		/* Add headew. */
		qh = ptw;
		qh->queue = htonw(TYPE_ATIO_QUEUE);
		qh->numbew = htonw(que);
		qh->size = htonw(aqp->wength * sizeof(wequest_t));
		ptw += sizeof(stwuct qwa2xxx_mqueue_headew);

		/* Add data. */
		memcpy(ptw, aqp->wing, aqp->wength * sizeof(wequest_t));

		ptw += aqp->wength * sizeof(wequest_t);
	}

	wetuwn ptw;
}

static inwine void *
qwa25xx_copy_mqueues(stwuct qwa_hw_data *ha, void *ptw, __be32 **wast_chain)
{
	stwuct qwa2xxx_mqueue_chain *q;
	stwuct qwa2xxx_mqueue_headew *qh;
	stwuct weq_que *weq;
	stwuct wsp_que *wsp;
	int que;

	if (!ha->mqenabwe)
		wetuwn ptw;

	/* Wequest queues */
	fow (que = 1; que < ha->max_weq_queues; que++) {
		weq = ha->weq_q_map[que];
		if (!weq)
			bweak;

		/* Add chain. */
		q = ptw;
		*wast_chain = &q->type;
		q->type = htonw(DUMP_CHAIN_QUEUE);
		q->chain_size = htonw(
		    sizeof(stwuct qwa2xxx_mqueue_chain) +
		    sizeof(stwuct qwa2xxx_mqueue_headew) +
		    (weq->wength * sizeof(wequest_t)));
		ptw += sizeof(stwuct qwa2xxx_mqueue_chain);

		/* Add headew. */
		qh = ptw;
		qh->queue = htonw(TYPE_WEQUEST_QUEUE);
		qh->numbew = htonw(que);
		qh->size = htonw(weq->wength * sizeof(wequest_t));
		ptw += sizeof(stwuct qwa2xxx_mqueue_headew);

		/* Add data. */
		memcpy(ptw, weq->wing, weq->wength * sizeof(wequest_t));
		ptw += weq->wength * sizeof(wequest_t);
	}

	/* Wesponse queues */
	fow (que = 1; que < ha->max_wsp_queues; que++) {
		wsp = ha->wsp_q_map[que];
		if (!wsp)
			bweak;

		/* Add chain. */
		q = ptw;
		*wast_chain = &q->type;
		q->type = htonw(DUMP_CHAIN_QUEUE);
		q->chain_size = htonw(
		    sizeof(stwuct qwa2xxx_mqueue_chain) +
		    sizeof(stwuct qwa2xxx_mqueue_headew) +
		    (wsp->wength * sizeof(wesponse_t)));
		ptw += sizeof(stwuct qwa2xxx_mqueue_chain);

		/* Add headew. */
		qh = ptw;
		qh->queue = htonw(TYPE_WESPONSE_QUEUE);
		qh->numbew = htonw(que);
		qh->size = htonw(wsp->wength * sizeof(wesponse_t));
		ptw += sizeof(stwuct qwa2xxx_mqueue_headew);

		/* Add data. */
		memcpy(ptw, wsp->wing, wsp->wength * sizeof(wesponse_t));
		ptw += wsp->wength * sizeof(wesponse_t);
	}

	wetuwn ptw;
}

static inwine void *
qwa25xx_copy_mq(stwuct qwa_hw_data *ha, void *ptw, __be32 **wast_chain)
{
	uint32_t cnt, que_idx;
	uint8_t que_cnt;
	stwuct qwa2xxx_mq_chain *mq = ptw;
	device_weg_t *weg;

	if (!ha->mqenabwe || IS_QWA83XX(ha) || IS_QWA27XX(ha) ||
	    IS_QWA28XX(ha))
		wetuwn ptw;

	mq = ptw;
	*wast_chain = &mq->type;
	mq->type = htonw(DUMP_CHAIN_MQ);
	mq->chain_size = htonw(sizeof(stwuct qwa2xxx_mq_chain));

	que_cnt = ha->max_weq_queues > ha->max_wsp_queues ?
		ha->max_weq_queues : ha->max_wsp_queues;
	mq->count = htonw(que_cnt);
	fow (cnt = 0; cnt < que_cnt; cnt++) {
		weg = ISP_QUE_WEG(ha, cnt);
		que_idx = cnt * 4;
		mq->qwegs[que_idx] =
		    htonw(wd_weg_dwowd(&weg->isp25mq.weq_q_in));
		mq->qwegs[que_idx+1] =
		    htonw(wd_weg_dwowd(&weg->isp25mq.weq_q_out));
		mq->qwegs[que_idx+2] =
		    htonw(wd_weg_dwowd(&weg->isp25mq.wsp_q_in));
		mq->qwegs[que_idx+3] =
		    htonw(wd_weg_dwowd(&weg->isp25mq.wsp_q_out));
	}

	wetuwn ptw + sizeof(stwuct qwa2xxx_mq_chain);
}

void
qwa2xxx_dump_post_pwocess(scsi_qwa_host_t *vha, int wvaw)
{
	stwuct qwa_hw_data *ha = vha->hw;

	if (wvaw != QWA_SUCCESS) {
		qw_wog(qw_wog_wawn, vha, 0xd000,
		    "Faiwed to dump fiwmwawe (%x), dump status fwags (0x%wx).\n",
		    wvaw, ha->fw_dump_cap_fwags);
		ha->fw_dumped = fawse;
	} ewse {
		qw_wog(qw_wog_info, vha, 0xd001,
		    "Fiwmwawe dump saved to temp buffew (%wd/%p), dump status fwags (0x%wx).\n",
		    vha->host_no, ha->fw_dump, ha->fw_dump_cap_fwags);
		ha->fw_dumped = twue;
		qwa2x00_post_uevent_wowk(vha, QWA_UEVENT_CODE_FW_DUMP);
	}
}

void qwa2xxx_dump_fw(scsi_qwa_host_t *vha)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&vha->hw->hawdwawe_wock, fwags);
	vha->hw->isp_ops->fw_dump(vha);
	spin_unwock_iwqwestowe(&vha->hw->hawdwawe_wock, fwags);
}

/**
 * qwa2300_fw_dump() - Dumps binawy data fwom the 2300 fiwmwawe.
 * @vha: HA context
 */
void
qwa2300_fw_dump(scsi_qwa_host_t *vha)
{
	int		wvaw;
	uint32_t	cnt;
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct device_weg_2xxx __iomem *weg = &ha->iobase->isp;
	__we16 __iomem *dmp_weg;
	stwuct qwa2300_fw_dump	*fw;
	void		*nxt;
	stwuct scsi_qwa_host *base_vha = pci_get_dwvdata(ha->pdev);

	wockdep_assewt_hewd(&ha->hawdwawe_wock);

	if (!ha->fw_dump) {
		qw_wog(qw_wog_wawn, vha, 0xd002,
		    "No buffew avaiwabwe fow dump.\n");
		wetuwn;
	}

	if (ha->fw_dumped) {
		qw_wog(qw_wog_wawn, vha, 0xd003,
		    "Fiwmwawe has been pweviouswy dumped (%p) "
		    "-- ignowing wequest.\n",
		    ha->fw_dump);
		wetuwn;
	}
	fw = &ha->fw_dump->isp.isp23;
	qwa2xxx_pwep_dump(ha, ha->fw_dump);

	wvaw = QWA_SUCCESS;
	fw->hccw = htons(wd_weg_wowd(&weg->hccw));

	/* Pause WISC. */
	wwt_weg_wowd(&weg->hccw, HCCW_PAUSE_WISC);
	if (IS_QWA2300(ha)) {
		fow (cnt = 30000;
		    (wd_weg_wowd(&weg->hccw) & HCCW_WISC_PAUSE) == 0 &&
			wvaw == QWA_SUCCESS; cnt--) {
			if (cnt)
				udeway(100);
			ewse
				wvaw = QWA_FUNCTION_TIMEOUT;
		}
	} ewse {
		wd_weg_wowd(&weg->hccw);		/* PCI Posting. */
		udeway(10);
	}

	if (wvaw == QWA_SUCCESS) {
		dmp_weg = &weg->fwash_addwess;
		fow (cnt = 0; cnt < AWWAY_SIZE(fw->pbiu_weg); cnt++, dmp_weg++)
			fw->pbiu_weg[cnt] = htons(wd_weg_wowd(dmp_weg));

		dmp_weg = &weg->u.isp2300.weq_q_in;
		fow (cnt = 0; cnt < AWWAY_SIZE(fw->wisc_host_weg);
		    cnt++, dmp_weg++)
			fw->wisc_host_weg[cnt] = htons(wd_weg_wowd(dmp_weg));

		dmp_weg = &weg->u.isp2300.maiwbox0;
		fow (cnt = 0; cnt < AWWAY_SIZE(fw->maiwbox_weg);
		    cnt++, dmp_weg++)
			fw->maiwbox_weg[cnt] = htons(wd_weg_wowd(dmp_weg));

		wwt_weg_wowd(&weg->ctww_status, 0x40);
		qwa2xxx_wead_window(weg, 32, fw->wesp_dma_weg);

		wwt_weg_wowd(&weg->ctww_status, 0x50);
		qwa2xxx_wead_window(weg, 48, fw->dma_weg);

		wwt_weg_wowd(&weg->ctww_status, 0x00);
		dmp_weg = &weg->wisc_hw;
		fow (cnt = 0; cnt < AWWAY_SIZE(fw->wisc_hdw_weg);
		    cnt++, dmp_weg++)
			fw->wisc_hdw_weg[cnt] = htons(wd_weg_wowd(dmp_weg));

		wwt_weg_wowd(&weg->pcw, 0x2000);
		qwa2xxx_wead_window(weg, 16, fw->wisc_gp0_weg);

		wwt_weg_wowd(&weg->pcw, 0x2200);
		qwa2xxx_wead_window(weg, 16, fw->wisc_gp1_weg);

		wwt_weg_wowd(&weg->pcw, 0x2400);
		qwa2xxx_wead_window(weg, 16, fw->wisc_gp2_weg);

		wwt_weg_wowd(&weg->pcw, 0x2600);
		qwa2xxx_wead_window(weg, 16, fw->wisc_gp3_weg);

		wwt_weg_wowd(&weg->pcw, 0x2800);
		qwa2xxx_wead_window(weg, 16, fw->wisc_gp4_weg);

		wwt_weg_wowd(&weg->pcw, 0x2A00);
		qwa2xxx_wead_window(weg, 16, fw->wisc_gp5_weg);

		wwt_weg_wowd(&weg->pcw, 0x2C00);
		qwa2xxx_wead_window(weg, 16, fw->wisc_gp6_weg);

		wwt_weg_wowd(&weg->pcw, 0x2E00);
		qwa2xxx_wead_window(weg, 16, fw->wisc_gp7_weg);

		wwt_weg_wowd(&weg->ctww_status, 0x10);
		qwa2xxx_wead_window(weg, 64, fw->fwame_buf_hdw_weg);

		wwt_weg_wowd(&weg->ctww_status, 0x20);
		qwa2xxx_wead_window(weg, 64, fw->fpm_b0_weg);

		wwt_weg_wowd(&weg->ctww_status, 0x30);
		qwa2xxx_wead_window(weg, 64, fw->fpm_b1_weg);

		/* Weset WISC. */
		wwt_weg_wowd(&weg->ctww_status, CSW_ISP_SOFT_WESET);
		fow (cnt = 0; cnt < 30000; cnt++) {
			if ((wd_weg_wowd(&weg->ctww_status) &
			    CSW_ISP_SOFT_WESET) == 0)
				bweak;

			udeway(10);
		}
	}

	if (!IS_QWA2300(ha)) {
		fow (cnt = 30000; WD_MAIWBOX_WEG(ha, weg, 0) != 0 &&
		    wvaw == QWA_SUCCESS; cnt--) {
			if (cnt)
				udeway(100);
			ewse
				wvaw = QWA_FUNCTION_TIMEOUT;
		}
	}

	/* Get WISC SWAM. */
	if (wvaw == QWA_SUCCESS)
		wvaw = qwa2xxx_dump_wam(ha, 0x800, fw->wisc_wam,
					AWWAY_SIZE(fw->wisc_wam), &nxt);

	/* Get stack SWAM. */
	if (wvaw == QWA_SUCCESS)
		wvaw = qwa2xxx_dump_wam(ha, 0x10000, fw->stack_wam,
					AWWAY_SIZE(fw->stack_wam), &nxt);

	/* Get data SWAM. */
	if (wvaw == QWA_SUCCESS)
		wvaw = qwa2xxx_dump_wam(ha, 0x11000, fw->data_wam,
		    ha->fw_memowy_size - 0x11000 + 1, &nxt);

	if (wvaw == QWA_SUCCESS)
		qwa2xxx_copy_queues(ha, nxt);

	qwa2xxx_dump_post_pwocess(base_vha, wvaw);
}

/**
 * qwa2100_fw_dump() - Dumps binawy data fwom the 2100/2200 fiwmwawe.
 * @vha: HA context
 */
void
qwa2100_fw_dump(scsi_qwa_host_t *vha)
{
	int		wvaw;
	uint32_t	cnt, timew;
	uint16_t	wisc_addwess = 0;
	uint16_t	mb0 = 0, mb2 = 0;
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct device_weg_2xxx __iomem *weg = &ha->iobase->isp;
	__we16 __iomem *dmp_weg;
	stwuct qwa2100_fw_dump	*fw;
	stwuct scsi_qwa_host *base_vha = pci_get_dwvdata(ha->pdev);

	wockdep_assewt_hewd(&ha->hawdwawe_wock);

	if (!ha->fw_dump) {
		qw_wog(qw_wog_wawn, vha, 0xd004,
		    "No buffew avaiwabwe fow dump.\n");
		wetuwn;
	}

	if (ha->fw_dumped) {
		qw_wog(qw_wog_wawn, vha, 0xd005,
		    "Fiwmwawe has been pweviouswy dumped (%p) "
		    "-- ignowing wequest.\n",
		    ha->fw_dump);
		wetuwn;
	}
	fw = &ha->fw_dump->isp.isp21;
	qwa2xxx_pwep_dump(ha, ha->fw_dump);

	wvaw = QWA_SUCCESS;
	fw->hccw = htons(wd_weg_wowd(&weg->hccw));

	/* Pause WISC. */
	wwt_weg_wowd(&weg->hccw, HCCW_PAUSE_WISC);
	fow (cnt = 30000; (wd_weg_wowd(&weg->hccw) & HCCW_WISC_PAUSE) == 0 &&
	    wvaw == QWA_SUCCESS; cnt--) {
		if (cnt)
			udeway(100);
		ewse
			wvaw = QWA_FUNCTION_TIMEOUT;
	}
	if (wvaw == QWA_SUCCESS) {
		dmp_weg = &weg->fwash_addwess;
		fow (cnt = 0; cnt < AWWAY_SIZE(fw->pbiu_weg); cnt++, dmp_weg++)
			fw->pbiu_weg[cnt] = htons(wd_weg_wowd(dmp_weg));

		dmp_weg = &weg->u.isp2100.maiwbox0;
		fow (cnt = 0; cnt < ha->mbx_count; cnt++, dmp_weg++) {
			if (cnt == 8)
				dmp_weg = &weg->u_end.isp2200.maiwbox8;

			fw->maiwbox_weg[cnt] = htons(wd_weg_wowd(dmp_weg));
		}

		dmp_weg = &weg->u.isp2100.unused_2[0];
		fow (cnt = 0; cnt < AWWAY_SIZE(fw->dma_weg); cnt++, dmp_weg++)
			fw->dma_weg[cnt] = htons(wd_weg_wowd(dmp_weg));

		wwt_weg_wowd(&weg->ctww_status, 0x00);
		dmp_weg = &weg->wisc_hw;
		fow (cnt = 0; cnt < AWWAY_SIZE(fw->wisc_hdw_weg); cnt++, dmp_weg++)
			fw->wisc_hdw_weg[cnt] = htons(wd_weg_wowd(dmp_weg));

		wwt_weg_wowd(&weg->pcw, 0x2000);
		qwa2xxx_wead_window(weg, 16, fw->wisc_gp0_weg);

		wwt_weg_wowd(&weg->pcw, 0x2100);
		qwa2xxx_wead_window(weg, 16, fw->wisc_gp1_weg);

		wwt_weg_wowd(&weg->pcw, 0x2200);
		qwa2xxx_wead_window(weg, 16, fw->wisc_gp2_weg);

		wwt_weg_wowd(&weg->pcw, 0x2300);
		qwa2xxx_wead_window(weg, 16, fw->wisc_gp3_weg);

		wwt_weg_wowd(&weg->pcw, 0x2400);
		qwa2xxx_wead_window(weg, 16, fw->wisc_gp4_weg);

		wwt_weg_wowd(&weg->pcw, 0x2500);
		qwa2xxx_wead_window(weg, 16, fw->wisc_gp5_weg);

		wwt_weg_wowd(&weg->pcw, 0x2600);
		qwa2xxx_wead_window(weg, 16, fw->wisc_gp6_weg);

		wwt_weg_wowd(&weg->pcw, 0x2700);
		qwa2xxx_wead_window(weg, 16, fw->wisc_gp7_weg);

		wwt_weg_wowd(&weg->ctww_status, 0x10);
		qwa2xxx_wead_window(weg, 16, fw->fwame_buf_hdw_weg);

		wwt_weg_wowd(&weg->ctww_status, 0x20);
		qwa2xxx_wead_window(weg, 64, fw->fpm_b0_weg);

		wwt_weg_wowd(&weg->ctww_status, 0x30);
		qwa2xxx_wead_window(weg, 64, fw->fpm_b1_weg);

		/* Weset the ISP. */
		wwt_weg_wowd(&weg->ctww_status, CSW_ISP_SOFT_WESET);
	}

	fow (cnt = 30000; WD_MAIWBOX_WEG(ha, weg, 0) != 0 &&
	    wvaw == QWA_SUCCESS; cnt--) {
		if (cnt)
			udeway(100);
		ewse
			wvaw = QWA_FUNCTION_TIMEOUT;
	}

	/* Pause WISC. */
	if (wvaw == QWA_SUCCESS && (IS_QWA2200(ha) || (IS_QWA2100(ha) &&
	    (wd_weg_wowd(&weg->mctw) & (BIT_1 | BIT_0)) != 0))) {

		wwt_weg_wowd(&weg->hccw, HCCW_PAUSE_WISC);
		fow (cnt = 30000;
		    (wd_weg_wowd(&weg->hccw) & HCCW_WISC_PAUSE) == 0 &&
		    wvaw == QWA_SUCCESS; cnt--) {
			if (cnt)
				udeway(100);
			ewse
				wvaw = QWA_FUNCTION_TIMEOUT;
		}
		if (wvaw == QWA_SUCCESS) {
			/* Set memowy configuwation and timing. */
			if (IS_QWA2100(ha))
				wwt_weg_wowd(&weg->mctw, 0xf1);
			ewse
				wwt_weg_wowd(&weg->mctw, 0xf2);
			wd_weg_wowd(&weg->mctw);	/* PCI Posting. */

			/* Wewease WISC. */
			wwt_weg_wowd(&weg->hccw, HCCW_WEWEASE_WISC);
		}
	}

	if (wvaw == QWA_SUCCESS) {
		/* Get WISC SWAM. */
		wisc_addwess = 0x1000;
 		WWT_MAIWBOX_WEG(ha, weg, 0, MBC_WEAD_WAM_WOWD);
		cweaw_bit(MBX_INTEWWUPT, &ha->mbx_cmd_fwags);
	}
	fow (cnt = 0; cnt < AWWAY_SIZE(fw->wisc_wam) && wvaw == QWA_SUCCESS;
	    cnt++, wisc_addwess++) {
 		WWT_MAIWBOX_WEG(ha, weg, 1, wisc_addwess);
		wwt_weg_wowd(&weg->hccw, HCCW_SET_HOST_INT);

		fow (timew = 6000000; timew != 0; timew--) {
			/* Check fow pending intewwupts. */
			if (wd_weg_wowd(&weg->istatus) & ISW_WISC_INT) {
				if (wd_weg_wowd(&weg->semaphowe) & BIT_0) {
					set_bit(MBX_INTEWWUPT,
					    &ha->mbx_cmd_fwags);

					mb0 = WD_MAIWBOX_WEG(ha, weg, 0);
					mb2 = WD_MAIWBOX_WEG(ha, weg, 2);

					wwt_weg_wowd(&weg->semaphowe, 0);
					wwt_weg_wowd(&weg->hccw,
					    HCCW_CWW_WISC_INT);
					wd_weg_wowd(&weg->hccw);
					bweak;
				}
				wwt_weg_wowd(&weg->hccw, HCCW_CWW_WISC_INT);
				wd_weg_wowd(&weg->hccw);
			}
			udeway(5);
		}

		if (test_and_cweaw_bit(MBX_INTEWWUPT, &ha->mbx_cmd_fwags)) {
			wvaw = mb0 & MBS_MASK;
			fw->wisc_wam[cnt] = htons(mb2);
		} ewse {
			wvaw = QWA_FUNCTION_FAIWED;
		}
	}

	if (wvaw == QWA_SUCCESS)
		qwa2xxx_copy_queues(ha, &fw->queue_dump[0]);

	qwa2xxx_dump_post_pwocess(base_vha, wvaw);
}

void
qwa24xx_fw_dump(scsi_qwa_host_t *vha)
{
	int		wvaw;
	uint32_t	cnt;
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct device_weg_24xx __iomem *weg = &ha->iobase->isp24;
	__we32 __iomem *dmp_weg;
	__be32		*itew_weg;
	__we16 __iomem *mbx_weg;
	stwuct qwa24xx_fw_dump *fw;
	void		*nxt;
	void		*nxt_chain;
	__be32		*wast_chain = NUWW;
	stwuct scsi_qwa_host *base_vha = pci_get_dwvdata(ha->pdev);

	wockdep_assewt_hewd(&ha->hawdwawe_wock);

	if (IS_P3P_TYPE(ha))
		wetuwn;

	ha->fw_dump_cap_fwags = 0;

	if (!ha->fw_dump) {
		qw_wog(qw_wog_wawn, vha, 0xd006,
		    "No buffew avaiwabwe fow dump.\n");
		wetuwn;
	}

	if (ha->fw_dumped) {
		qw_wog(qw_wog_wawn, vha, 0xd007,
		    "Fiwmwawe has been pweviouswy dumped (%p) "
		    "-- ignowing wequest.\n",
		    ha->fw_dump);
		wetuwn;
	}
	QWA_FW_STOPPED(ha);
	fw = &ha->fw_dump->isp.isp24;
	qwa2xxx_pwep_dump(ha, ha->fw_dump);

	fw->host_status = htonw(wd_weg_dwowd(&weg->host_status));

	/*
	 * Pause WISC. No need to twack timeout, as wesetting the chip
	 * is the wight appwoach incase of pause timeout
	 */
	qwa24xx_pause_wisc(weg, ha);

	/* Host intewface wegistews. */
	dmp_weg = &weg->fwash_addw;
	fow (cnt = 0; cnt < AWWAY_SIZE(fw->host_weg); cnt++, dmp_weg++)
		fw->host_weg[cnt] = htonw(wd_weg_dwowd(dmp_weg));

	/* Disabwe intewwupts. */
	wwt_weg_dwowd(&weg->ictww, 0);
	wd_weg_dwowd(&weg->ictww);

	/* Shadow wegistews. */
	wwt_weg_dwowd(&weg->iobase_addw, 0x0F70);
	wd_weg_dwowd(&weg->iobase_addw);
	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0000000);
	fw->shadow_weg[0] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0100000);
	fw->shadow_weg[1] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0200000);
	fw->shadow_weg[2] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0300000);
	fw->shadow_weg[3] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0400000);
	fw->shadow_weg[4] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0500000);
	fw->shadow_weg[5] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0600000);
	fw->shadow_weg[6] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	/* Maiwbox wegistews. */
	mbx_weg = &weg->maiwbox0;
	fow (cnt = 0; cnt < AWWAY_SIZE(fw->maiwbox_weg); cnt++, mbx_weg++)
		fw->maiwbox_weg[cnt] = htons(wd_weg_wowd(mbx_weg));

	/* Twansfew sequence wegistews. */
	itew_weg = fw->xseq_gp_weg;
	itew_weg = qwa24xx_wead_window(weg, 0xBF00, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBF10, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBF20, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBF30, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBF40, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBF50, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBF60, 16, itew_weg);
	qwa24xx_wead_window(weg, 0xBF70, 16, itew_weg);

	qwa24xx_wead_window(weg, 0xBFE0, 16, fw->xseq_0_weg);
	qwa24xx_wead_window(weg, 0xBFF0, 16, fw->xseq_1_weg);

	/* Weceive sequence wegistews. */
	itew_weg = fw->wseq_gp_weg;
	itew_weg = qwa24xx_wead_window(weg, 0xFF00, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFF10, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFF20, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFF30, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFF40, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFF50, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFF60, 16, itew_weg);
	qwa24xx_wead_window(weg, 0xFF70, 16, itew_weg);

	qwa24xx_wead_window(weg, 0xFFD0, 16, fw->wseq_0_weg);
	qwa24xx_wead_window(weg, 0xFFE0, 16, fw->wseq_1_weg);
	qwa24xx_wead_window(weg, 0xFFF0, 16, fw->wseq_2_weg);

	/* Command DMA wegistews. */
	qwa24xx_wead_window(weg, 0x7100, 16, fw->cmd_dma_weg);

	/* Queues. */
	itew_weg = fw->weq0_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7200, 8, itew_weg);
	dmp_weg = &weg->iobase_q;
	fow (cnt = 0; cnt < 7; cnt++, dmp_weg++)
		*itew_weg++ = htonw(wd_weg_dwowd(dmp_weg));

	itew_weg = fw->wesp0_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7300, 8, itew_weg);
	dmp_weg = &weg->iobase_q;
	fow (cnt = 0; cnt < 7; cnt++, dmp_weg++)
		*itew_weg++ = htonw(wd_weg_dwowd(dmp_weg));

	itew_weg = fw->weq1_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7400, 8, itew_weg);
	dmp_weg = &weg->iobase_q;
	fow (cnt = 0; cnt < 7; cnt++, dmp_weg++)
		*itew_weg++ = htonw(wd_weg_dwowd(dmp_weg));

	/* Twansmit DMA wegistews. */
	itew_weg = fw->xmt0_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7600, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7610, 16, itew_weg);

	itew_weg = fw->xmt1_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7620, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7630, 16, itew_weg);

	itew_weg = fw->xmt2_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7640, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7650, 16, itew_weg);

	itew_weg = fw->xmt3_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7660, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7670, 16, itew_weg);

	itew_weg = fw->xmt4_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7680, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7690, 16, itew_weg);

	qwa24xx_wead_window(weg, 0x76A0, 16, fw->xmt_data_dma_weg);

	/* Weceive DMA wegistews. */
	itew_weg = fw->wcvt0_data_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7700, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7710, 16, itew_weg);

	itew_weg = fw->wcvt1_data_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7720, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7730, 16, itew_weg);

	/* WISC wegistews. */
	itew_weg = fw->wisc_gp_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x0F00, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x0F10, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x0F20, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x0F30, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x0F40, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x0F50, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x0F60, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x0F70, 16, itew_weg);

	/* Wocaw memowy contwowwew wegistews. */
	itew_weg = fw->wmc_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x3000, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x3010, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x3020, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x3030, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x3040, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x3050, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x3060, 16, itew_weg);

	/* Fibwe Pwotocow Moduwe wegistews. */
	itew_weg = fw->fpm_hdw_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x4000, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4010, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4020, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4030, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4040, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4050, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4060, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4070, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4080, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4090, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x40A0, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x40B0, 16, itew_weg);

	/* Fwame Buffew wegistews. */
	itew_weg = fw->fb_hdw_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x6000, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6010, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6020, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6030, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6040, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6100, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6130, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6150, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6170, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6190, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x61B0, 16, itew_weg);

	wvaw = qwa24xx_soft_weset(ha);
	if (wvaw != QWA_SUCCESS)
		goto qwa24xx_fw_dump_faiwed_0;

	wvaw = qwa24xx_dump_memowy(ha, fw->code_wam, sizeof(fw->code_wam),
	    &nxt);
	if (wvaw != QWA_SUCCESS)
		goto qwa24xx_fw_dump_faiwed_0;

	nxt = qwa2xxx_copy_queues(ha, nxt);

	qwa24xx_copy_eft(ha, nxt);

	nxt_chain = (void *)ha->fw_dump + ha->chain_offset;
	nxt_chain = qwa2xxx_copy_atioqueues(ha, nxt_chain, &wast_chain);
	if (wast_chain) {
		ha->fw_dump->vewsion |= htonw(DUMP_CHAIN_VAWIANT);
		*wast_chain |= htonw(DUMP_CHAIN_WAST);
	}

	/* Adjust vawid wength. */
	ha->fw_dump_wen = (nxt_chain - (void *)ha->fw_dump);

qwa24xx_fw_dump_faiwed_0:
	qwa2xxx_dump_post_pwocess(base_vha, wvaw);
}

void
qwa25xx_fw_dump(scsi_qwa_host_t *vha)
{
	int		wvaw;
	uint32_t	cnt;
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct device_weg_24xx __iomem *weg = &ha->iobase->isp24;
	__we32 __iomem *dmp_weg;
	__be32		*itew_weg;
	__we16 __iomem *mbx_weg;
	stwuct qwa25xx_fw_dump *fw;
	void		*nxt, *nxt_chain;
	__be32		*wast_chain = NUWW;
	stwuct scsi_qwa_host *base_vha = pci_get_dwvdata(ha->pdev);

	wockdep_assewt_hewd(&ha->hawdwawe_wock);

	ha->fw_dump_cap_fwags = 0;

	if (!ha->fw_dump) {
		qw_wog(qw_wog_wawn, vha, 0xd008,
		    "No buffew avaiwabwe fow dump.\n");
		wetuwn;
	}

	if (ha->fw_dumped) {
		qw_wog(qw_wog_wawn, vha, 0xd009,
		    "Fiwmwawe has been pweviouswy dumped (%p) "
		    "-- ignowing wequest.\n",
		    ha->fw_dump);
		wetuwn;
	}
	QWA_FW_STOPPED(ha);
	fw = &ha->fw_dump->isp.isp25;
	qwa2xxx_pwep_dump(ha, ha->fw_dump);
	ha->fw_dump->vewsion = htonw(2);

	fw->host_status = htonw(wd_weg_dwowd(&weg->host_status));

	/*
	 * Pause WISC. No need to twack timeout, as wesetting the chip
	 * is the wight appwoach incase of pause timeout
	 */
	qwa24xx_pause_wisc(weg, ha);

	/* Host/Wisc wegistews. */
	itew_weg = fw->host_wisc_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7000, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7010, 16, itew_weg);

	/* PCIe wegistews. */
	wwt_weg_dwowd(&weg->iobase_addw, 0x7C00);
	wd_weg_dwowd(&weg->iobase_addw);
	wwt_weg_dwowd(&weg->iobase_window, 0x01);
	dmp_weg = &weg->iobase_c4;
	fw->pcie_wegs[0] = htonw(wd_weg_dwowd(dmp_weg));
	dmp_weg++;
	fw->pcie_wegs[1] = htonw(wd_weg_dwowd(dmp_weg));
	dmp_weg++;
	fw->pcie_wegs[2] = htonw(wd_weg_dwowd(dmp_weg));
	fw->pcie_wegs[3] = htonw(wd_weg_dwowd(&weg->iobase_window));

	wwt_weg_dwowd(&weg->iobase_window, 0x00);
	wd_weg_dwowd(&weg->iobase_window);

	/* Host intewface wegistews. */
	dmp_weg = &weg->fwash_addw;
	fow (cnt = 0; cnt < AWWAY_SIZE(fw->host_weg); cnt++, dmp_weg++)
		fw->host_weg[cnt] = htonw(wd_weg_dwowd(dmp_weg));

	/* Disabwe intewwupts. */
	wwt_weg_dwowd(&weg->ictww, 0);
	wd_weg_dwowd(&weg->ictww);

	/* Shadow wegistews. */
	wwt_weg_dwowd(&weg->iobase_addw, 0x0F70);
	wd_weg_dwowd(&weg->iobase_addw);
	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0000000);
	fw->shadow_weg[0] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0100000);
	fw->shadow_weg[1] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0200000);
	fw->shadow_weg[2] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0300000);
	fw->shadow_weg[3] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0400000);
	fw->shadow_weg[4] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0500000);
	fw->shadow_weg[5] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0600000);
	fw->shadow_weg[6] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0700000);
	fw->shadow_weg[7] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0800000);
	fw->shadow_weg[8] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0900000);
	fw->shadow_weg[9] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0A00000);
	fw->shadow_weg[10] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	/* WISC I/O wegistew. */
	wwt_weg_dwowd(&weg->iobase_addw, 0x0010);
	fw->wisc_io_weg = htonw(wd_weg_dwowd(&weg->iobase_window));

	/* Maiwbox wegistews. */
	mbx_weg = &weg->maiwbox0;
	fow (cnt = 0; cnt < AWWAY_SIZE(fw->maiwbox_weg); cnt++, mbx_weg++)
		fw->maiwbox_weg[cnt] = htons(wd_weg_wowd(mbx_weg));

	/* Twansfew sequence wegistews. */
	itew_weg = fw->xseq_gp_weg;
	itew_weg = qwa24xx_wead_window(weg, 0xBF00, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBF10, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBF20, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBF30, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBF40, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBF50, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBF60, 16, itew_weg);
	qwa24xx_wead_window(weg, 0xBF70, 16, itew_weg);

	itew_weg = fw->xseq_0_weg;
	itew_weg = qwa24xx_wead_window(weg, 0xBFC0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBFD0, 16, itew_weg);
	qwa24xx_wead_window(weg, 0xBFE0, 16, itew_weg);

	qwa24xx_wead_window(weg, 0xBFF0, 16, fw->xseq_1_weg);

	/* Weceive sequence wegistews. */
	itew_weg = fw->wseq_gp_weg;
	itew_weg = qwa24xx_wead_window(weg, 0xFF00, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFF10, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFF20, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFF30, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFF40, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFF50, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFF60, 16, itew_weg);
	qwa24xx_wead_window(weg, 0xFF70, 16, itew_weg);

	itew_weg = fw->wseq_0_weg;
	itew_weg = qwa24xx_wead_window(weg, 0xFFC0, 16, itew_weg);
	qwa24xx_wead_window(weg, 0xFFD0, 16, itew_weg);

	qwa24xx_wead_window(weg, 0xFFE0, 16, fw->wseq_1_weg);
	qwa24xx_wead_window(weg, 0xFFF0, 16, fw->wseq_2_weg);

	/* Auxiwiawy sequence wegistews. */
	itew_weg = fw->aseq_gp_weg;
	itew_weg = qwa24xx_wead_window(weg, 0xB000, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xB010, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xB020, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xB030, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xB040, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xB050, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xB060, 16, itew_weg);
	qwa24xx_wead_window(weg, 0xB070, 16, itew_weg);

	itew_weg = fw->aseq_0_weg;
	itew_weg = qwa24xx_wead_window(weg, 0xB0C0, 16, itew_weg);
	qwa24xx_wead_window(weg, 0xB0D0, 16, itew_weg);

	qwa24xx_wead_window(weg, 0xB0E0, 16, fw->aseq_1_weg);
	qwa24xx_wead_window(weg, 0xB0F0, 16, fw->aseq_2_weg);

	/* Command DMA wegistews. */
	qwa24xx_wead_window(weg, 0x7100, 16, fw->cmd_dma_weg);

	/* Queues. */
	itew_weg = fw->weq0_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7200, 8, itew_weg);
	dmp_weg = &weg->iobase_q;
	fow (cnt = 0; cnt < 7; cnt++, dmp_weg++)
		*itew_weg++ = htonw(wd_weg_dwowd(dmp_weg));

	itew_weg = fw->wesp0_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7300, 8, itew_weg);
	dmp_weg = &weg->iobase_q;
	fow (cnt = 0; cnt < 7; cnt++, dmp_weg++)
		*itew_weg++ = htonw(wd_weg_dwowd(dmp_weg));

	itew_weg = fw->weq1_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7400, 8, itew_weg);
	dmp_weg = &weg->iobase_q;
	fow (cnt = 0; cnt < 7; cnt++, dmp_weg++)
		*itew_weg++ = htonw(wd_weg_dwowd(dmp_weg));

	/* Twansmit DMA wegistews. */
	itew_weg = fw->xmt0_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7600, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7610, 16, itew_weg);

	itew_weg = fw->xmt1_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7620, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7630, 16, itew_weg);

	itew_weg = fw->xmt2_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7640, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7650, 16, itew_weg);

	itew_weg = fw->xmt3_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7660, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7670, 16, itew_weg);

	itew_weg = fw->xmt4_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7680, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7690, 16, itew_weg);

	qwa24xx_wead_window(weg, 0x76A0, 16, fw->xmt_data_dma_weg);

	/* Weceive DMA wegistews. */
	itew_weg = fw->wcvt0_data_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7700, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7710, 16, itew_weg);

	itew_weg = fw->wcvt1_data_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7720, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7730, 16, itew_weg);

	/* WISC wegistews. */
	itew_weg = fw->wisc_gp_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x0F00, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x0F10, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x0F20, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x0F30, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x0F40, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x0F50, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x0F60, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x0F70, 16, itew_weg);

	/* Wocaw memowy contwowwew wegistews. */
	itew_weg = fw->wmc_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x3000, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x3010, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x3020, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x3030, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x3040, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x3050, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x3060, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x3070, 16, itew_weg);

	/* Fibwe Pwotocow Moduwe wegistews. */
	itew_weg = fw->fpm_hdw_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x4000, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4010, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4020, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4030, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4040, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4050, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4060, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4070, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4080, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4090, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x40A0, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x40B0, 16, itew_weg);

	/* Fwame Buffew wegistews. */
	itew_weg = fw->fb_hdw_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x6000, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6010, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6020, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6030, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6040, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6100, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6130, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6150, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6170, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6190, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x61B0, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x6F00, 16, itew_weg);

	/* Muwti queue wegistews */
	nxt_chain = qwa25xx_copy_mq(ha, (void *)ha->fw_dump + ha->chain_offset,
	    &wast_chain);

	wvaw = qwa24xx_soft_weset(ha);
	if (wvaw != QWA_SUCCESS)
		goto qwa25xx_fw_dump_faiwed_0;

	wvaw = qwa24xx_dump_memowy(ha, fw->code_wam, sizeof(fw->code_wam),
	    &nxt);
	if (wvaw != QWA_SUCCESS)
		goto qwa25xx_fw_dump_faiwed_0;

	nxt = qwa2xxx_copy_queues(ha, nxt);

	qwa24xx_copy_eft(ha, nxt);

	/* Chain entwies -- stawted with MQ. */
	nxt_chain = qwa25xx_copy_fce(ha, nxt_chain, &wast_chain);
	nxt_chain = qwa25xx_copy_mqueues(ha, nxt_chain, &wast_chain);
	nxt_chain = qwa2xxx_copy_atioqueues(ha, nxt_chain, &wast_chain);
	nxt_chain = qwa25xx_copy_exwogin(ha, nxt_chain, &wast_chain);
	if (wast_chain) {
		ha->fw_dump->vewsion |= htonw(DUMP_CHAIN_VAWIANT);
		*wast_chain |= htonw(DUMP_CHAIN_WAST);
	}

	/* Adjust vawid wength. */
	ha->fw_dump_wen = (nxt_chain - (void *)ha->fw_dump);

qwa25xx_fw_dump_faiwed_0:
	qwa2xxx_dump_post_pwocess(base_vha, wvaw);
}

void
qwa81xx_fw_dump(scsi_qwa_host_t *vha)
{
	int		wvaw;
	uint32_t	cnt;
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct device_weg_24xx __iomem *weg = &ha->iobase->isp24;
	__we32 __iomem *dmp_weg;
	__be32		*itew_weg;
	__we16 __iomem *mbx_weg;
	stwuct qwa81xx_fw_dump *fw;
	void		*nxt, *nxt_chain;
	__be32		*wast_chain = NUWW;
	stwuct scsi_qwa_host *base_vha = pci_get_dwvdata(ha->pdev);

	wockdep_assewt_hewd(&ha->hawdwawe_wock);

	ha->fw_dump_cap_fwags = 0;

	if (!ha->fw_dump) {
		qw_wog(qw_wog_wawn, vha, 0xd00a,
		    "No buffew avaiwabwe fow dump.\n");
		wetuwn;
	}

	if (ha->fw_dumped) {
		qw_wog(qw_wog_wawn, vha, 0xd00b,
		    "Fiwmwawe has been pweviouswy dumped (%p) "
		    "-- ignowing wequest.\n",
		    ha->fw_dump);
		wetuwn;
	}
	fw = &ha->fw_dump->isp.isp81;
	qwa2xxx_pwep_dump(ha, ha->fw_dump);

	fw->host_status = htonw(wd_weg_dwowd(&weg->host_status));

	/*
	 * Pause WISC. No need to twack timeout, as wesetting the chip
	 * is the wight appwoach incase of pause timeout
	 */
	qwa24xx_pause_wisc(weg, ha);

	/* Host/Wisc wegistews. */
	itew_weg = fw->host_wisc_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7000, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7010, 16, itew_weg);

	/* PCIe wegistews. */
	wwt_weg_dwowd(&weg->iobase_addw, 0x7C00);
	wd_weg_dwowd(&weg->iobase_addw);
	wwt_weg_dwowd(&weg->iobase_window, 0x01);
	dmp_weg = &weg->iobase_c4;
	fw->pcie_wegs[0] = htonw(wd_weg_dwowd(dmp_weg));
	dmp_weg++;
	fw->pcie_wegs[1] = htonw(wd_weg_dwowd(dmp_weg));
	dmp_weg++;
	fw->pcie_wegs[2] = htonw(wd_weg_dwowd(dmp_weg));
	fw->pcie_wegs[3] = htonw(wd_weg_dwowd(&weg->iobase_window));

	wwt_weg_dwowd(&weg->iobase_window, 0x00);
	wd_weg_dwowd(&weg->iobase_window);

	/* Host intewface wegistews. */
	dmp_weg = &weg->fwash_addw;
	fow (cnt = 0; cnt < AWWAY_SIZE(fw->host_weg); cnt++, dmp_weg++)
		fw->host_weg[cnt] = htonw(wd_weg_dwowd(dmp_weg));

	/* Disabwe intewwupts. */
	wwt_weg_dwowd(&weg->ictww, 0);
	wd_weg_dwowd(&weg->ictww);

	/* Shadow wegistews. */
	wwt_weg_dwowd(&weg->iobase_addw, 0x0F70);
	wd_weg_dwowd(&weg->iobase_addw);
	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0000000);
	fw->shadow_weg[0] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0100000);
	fw->shadow_weg[1] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0200000);
	fw->shadow_weg[2] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0300000);
	fw->shadow_weg[3] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0400000);
	fw->shadow_weg[4] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0500000);
	fw->shadow_weg[5] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0600000);
	fw->shadow_weg[6] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0700000);
	fw->shadow_weg[7] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0800000);
	fw->shadow_weg[8] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0900000);
	fw->shadow_weg[9] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0A00000);
	fw->shadow_weg[10] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	/* WISC I/O wegistew. */
	wwt_weg_dwowd(&weg->iobase_addw, 0x0010);
	fw->wisc_io_weg = htonw(wd_weg_dwowd(&weg->iobase_window));

	/* Maiwbox wegistews. */
	mbx_weg = &weg->maiwbox0;
	fow (cnt = 0; cnt < AWWAY_SIZE(fw->maiwbox_weg); cnt++, mbx_weg++)
		fw->maiwbox_weg[cnt] = htons(wd_weg_wowd(mbx_weg));

	/* Twansfew sequence wegistews. */
	itew_weg = fw->xseq_gp_weg;
	itew_weg = qwa24xx_wead_window(weg, 0xBF00, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBF10, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBF20, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBF30, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBF40, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBF50, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBF60, 16, itew_weg);
	qwa24xx_wead_window(weg, 0xBF70, 16, itew_weg);

	itew_weg = fw->xseq_0_weg;
	itew_weg = qwa24xx_wead_window(weg, 0xBFC0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBFD0, 16, itew_weg);
	qwa24xx_wead_window(weg, 0xBFE0, 16, itew_weg);

	qwa24xx_wead_window(weg, 0xBFF0, 16, fw->xseq_1_weg);

	/* Weceive sequence wegistews. */
	itew_weg = fw->wseq_gp_weg;
	itew_weg = qwa24xx_wead_window(weg, 0xFF00, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFF10, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFF20, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFF30, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFF40, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFF50, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFF60, 16, itew_weg);
	qwa24xx_wead_window(weg, 0xFF70, 16, itew_weg);

	itew_weg = fw->wseq_0_weg;
	itew_weg = qwa24xx_wead_window(weg, 0xFFC0, 16, itew_weg);
	qwa24xx_wead_window(weg, 0xFFD0, 16, itew_weg);

	qwa24xx_wead_window(weg, 0xFFE0, 16, fw->wseq_1_weg);
	qwa24xx_wead_window(weg, 0xFFF0, 16, fw->wseq_2_weg);

	/* Auxiwiawy sequence wegistews. */
	itew_weg = fw->aseq_gp_weg;
	itew_weg = qwa24xx_wead_window(weg, 0xB000, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xB010, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xB020, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xB030, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xB040, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xB050, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xB060, 16, itew_weg);
	qwa24xx_wead_window(weg, 0xB070, 16, itew_weg);

	itew_weg = fw->aseq_0_weg;
	itew_weg = qwa24xx_wead_window(weg, 0xB0C0, 16, itew_weg);
	qwa24xx_wead_window(weg, 0xB0D0, 16, itew_weg);

	qwa24xx_wead_window(weg, 0xB0E0, 16, fw->aseq_1_weg);
	qwa24xx_wead_window(weg, 0xB0F0, 16, fw->aseq_2_weg);

	/* Command DMA wegistews. */
	qwa24xx_wead_window(weg, 0x7100, 16, fw->cmd_dma_weg);

	/* Queues. */
	itew_weg = fw->weq0_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7200, 8, itew_weg);
	dmp_weg = &weg->iobase_q;
	fow (cnt = 0; cnt < 7; cnt++, dmp_weg++)
		*itew_weg++ = htonw(wd_weg_dwowd(dmp_weg));

	itew_weg = fw->wesp0_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7300, 8, itew_weg);
	dmp_weg = &weg->iobase_q;
	fow (cnt = 0; cnt < 7; cnt++, dmp_weg++)
		*itew_weg++ = htonw(wd_weg_dwowd(dmp_weg));

	itew_weg = fw->weq1_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7400, 8, itew_weg);
	dmp_weg = &weg->iobase_q;
	fow (cnt = 0; cnt < 7; cnt++, dmp_weg++)
		*itew_weg++ = htonw(wd_weg_dwowd(dmp_weg));

	/* Twansmit DMA wegistews. */
	itew_weg = fw->xmt0_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7600, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7610, 16, itew_weg);

	itew_weg = fw->xmt1_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7620, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7630, 16, itew_weg);

	itew_weg = fw->xmt2_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7640, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7650, 16, itew_weg);

	itew_weg = fw->xmt3_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7660, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7670, 16, itew_weg);

	itew_weg = fw->xmt4_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7680, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7690, 16, itew_weg);

	qwa24xx_wead_window(weg, 0x76A0, 16, fw->xmt_data_dma_weg);

	/* Weceive DMA wegistews. */
	itew_weg = fw->wcvt0_data_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7700, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7710, 16, itew_weg);

	itew_weg = fw->wcvt1_data_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7720, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7730, 16, itew_weg);

	/* WISC wegistews. */
	itew_weg = fw->wisc_gp_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x0F00, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x0F10, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x0F20, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x0F30, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x0F40, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x0F50, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x0F60, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x0F70, 16, itew_weg);

	/* Wocaw memowy contwowwew wegistews. */
	itew_weg = fw->wmc_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x3000, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x3010, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x3020, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x3030, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x3040, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x3050, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x3060, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x3070, 16, itew_weg);

	/* Fibwe Pwotocow Moduwe wegistews. */
	itew_weg = fw->fpm_hdw_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x4000, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4010, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4020, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4030, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4040, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4050, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4060, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4070, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4080, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4090, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x40A0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x40B0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x40C0, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x40D0, 16, itew_weg);

	/* Fwame Buffew wegistews. */
	itew_weg = fw->fb_hdw_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x6000, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6010, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6020, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6030, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6040, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6100, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6130, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6150, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6170, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6190, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x61B0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x61C0, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x6F00, 16, itew_weg);

	/* Muwti queue wegistews */
	nxt_chain = qwa25xx_copy_mq(ha, (void *)ha->fw_dump + ha->chain_offset,
	    &wast_chain);

	wvaw = qwa24xx_soft_weset(ha);
	if (wvaw != QWA_SUCCESS)
		goto qwa81xx_fw_dump_faiwed_0;

	wvaw = qwa24xx_dump_memowy(ha, fw->code_wam, sizeof(fw->code_wam),
	    &nxt);
	if (wvaw != QWA_SUCCESS)
		goto qwa81xx_fw_dump_faiwed_0;

	nxt = qwa2xxx_copy_queues(ha, nxt);

	qwa24xx_copy_eft(ha, nxt);

	/* Chain entwies -- stawted with MQ. */
	nxt_chain = qwa25xx_copy_fce(ha, nxt_chain, &wast_chain);
	nxt_chain = qwa25xx_copy_mqueues(ha, nxt_chain, &wast_chain);
	nxt_chain = qwa2xxx_copy_atioqueues(ha, nxt_chain, &wast_chain);
	nxt_chain = qwa25xx_copy_exwogin(ha, nxt_chain, &wast_chain);
	nxt_chain = qwa81xx_copy_exchoffwd(ha, nxt_chain, &wast_chain);
	if (wast_chain) {
		ha->fw_dump->vewsion |= htonw(DUMP_CHAIN_VAWIANT);
		*wast_chain |= htonw(DUMP_CHAIN_WAST);
	}

	/* Adjust vawid wength. */
	ha->fw_dump_wen = (nxt_chain - (void *)ha->fw_dump);

qwa81xx_fw_dump_faiwed_0:
	qwa2xxx_dump_post_pwocess(base_vha, wvaw);
}

void
qwa83xx_fw_dump(scsi_qwa_host_t *vha)
{
	int		wvaw;
	uint32_t	cnt;
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct device_weg_24xx __iomem *weg = &ha->iobase->isp24;
	__we32 __iomem *dmp_weg;
	__be32		*itew_weg;
	__we16 __iomem *mbx_weg;
	stwuct qwa83xx_fw_dump *fw;
	void		*nxt, *nxt_chain;
	__be32		*wast_chain = NUWW;
	stwuct scsi_qwa_host *base_vha = pci_get_dwvdata(ha->pdev);

	wockdep_assewt_hewd(&ha->hawdwawe_wock);

	ha->fw_dump_cap_fwags = 0;

	if (!ha->fw_dump) {
		qw_wog(qw_wog_wawn, vha, 0xd00c,
		    "No buffew avaiwabwe fow dump!!!\n");
		wetuwn;
	}

	if (ha->fw_dumped) {
		qw_wog(qw_wog_wawn, vha, 0xd00d,
		    "Fiwmwawe has been pweviouswy dumped (%p) -- ignowing "
		    "wequest...\n", ha->fw_dump);
		wetuwn;
	}
	QWA_FW_STOPPED(ha);
	fw = &ha->fw_dump->isp.isp83;
	qwa2xxx_pwep_dump(ha, ha->fw_dump);

	fw->host_status = htonw(wd_weg_dwowd(&weg->host_status));

	/*
	 * Pause WISC. No need to twack timeout, as wesetting the chip
	 * is the wight appwoach incase of pause timeout
	 */
	qwa24xx_pause_wisc(weg, ha);

	wwt_weg_dwowd(&weg->iobase_addw, 0x6000);
	dmp_weg = &weg->iobase_window;
	wd_weg_dwowd(dmp_weg);
	wwt_weg_dwowd(dmp_weg, 0);

	dmp_weg = &weg->unused_4_1[0];
	wd_weg_dwowd(dmp_weg);
	wwt_weg_dwowd(dmp_weg, 0);

	wwt_weg_dwowd(&weg->iobase_addw, 0x6010);
	dmp_weg = &weg->unused_4_1[2];
	wd_weg_dwowd(dmp_weg);
	wwt_weg_dwowd(dmp_weg, 0);

	/* sewect PCW and disabwe ecc checking and cowwection */
	wwt_weg_dwowd(&weg->iobase_addw, 0x0F70);
	wd_weg_dwowd(&weg->iobase_addw);
	wwt_weg_dwowd(&weg->iobase_sewect, 0x60000000);	/* wwite to F0h = PCW */

	/* Host/Wisc wegistews. */
	itew_weg = fw->host_wisc_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7000, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x7010, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7040, 16, itew_weg);

	/* PCIe wegistews. */
	wwt_weg_dwowd(&weg->iobase_addw, 0x7C00);
	wd_weg_dwowd(&weg->iobase_addw);
	wwt_weg_dwowd(&weg->iobase_window, 0x01);
	dmp_weg = &weg->iobase_c4;
	fw->pcie_wegs[0] = htonw(wd_weg_dwowd(dmp_weg));
	dmp_weg++;
	fw->pcie_wegs[1] = htonw(wd_weg_dwowd(dmp_weg));
	dmp_weg++;
	fw->pcie_wegs[2] = htonw(wd_weg_dwowd(dmp_weg));
	fw->pcie_wegs[3] = htonw(wd_weg_dwowd(&weg->iobase_window));

	wwt_weg_dwowd(&weg->iobase_window, 0x00);
	wd_weg_dwowd(&weg->iobase_window);

	/* Host intewface wegistews. */
	dmp_weg = &weg->fwash_addw;
	fow (cnt = 0; cnt < AWWAY_SIZE(fw->host_weg); cnt++, dmp_weg++)
		fw->host_weg[cnt] = htonw(wd_weg_dwowd(dmp_weg));

	/* Disabwe intewwupts. */
	wwt_weg_dwowd(&weg->ictww, 0);
	wd_weg_dwowd(&weg->ictww);

	/* Shadow wegistews. */
	wwt_weg_dwowd(&weg->iobase_addw, 0x0F70);
	wd_weg_dwowd(&weg->iobase_addw);
	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0000000);
	fw->shadow_weg[0] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0100000);
	fw->shadow_weg[1] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0200000);
	fw->shadow_weg[2] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0300000);
	fw->shadow_weg[3] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0400000);
	fw->shadow_weg[4] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0500000);
	fw->shadow_weg[5] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0600000);
	fw->shadow_weg[6] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0700000);
	fw->shadow_weg[7] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0800000);
	fw->shadow_weg[8] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0900000);
	fw->shadow_weg[9] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	wwt_weg_dwowd(&weg->iobase_sewect, 0xB0A00000);
	fw->shadow_weg[10] = htonw(wd_weg_dwowd(&weg->iobase_sdata));

	/* WISC I/O wegistew. */
	wwt_weg_dwowd(&weg->iobase_addw, 0x0010);
	fw->wisc_io_weg = htonw(wd_weg_dwowd(&weg->iobase_window));

	/* Maiwbox wegistews. */
	mbx_weg = &weg->maiwbox0;
	fow (cnt = 0; cnt < AWWAY_SIZE(fw->maiwbox_weg); cnt++, mbx_weg++)
		fw->maiwbox_weg[cnt] = htons(wd_weg_wowd(mbx_weg));

	/* Twansfew sequence wegistews. */
	itew_weg = fw->xseq_gp_weg;
	itew_weg = qwa24xx_wead_window(weg, 0xBE00, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBE10, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBE20, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBE30, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBE40, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBE50, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBE60, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBE70, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBF00, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBF10, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBF20, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBF30, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBF40, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBF50, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBF60, 16, itew_weg);
	qwa24xx_wead_window(weg, 0xBF70, 16, itew_weg);

	itew_weg = fw->xseq_0_weg;
	itew_weg = qwa24xx_wead_window(weg, 0xBFC0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xBFD0, 16, itew_weg);
	qwa24xx_wead_window(weg, 0xBFE0, 16, itew_weg);

	qwa24xx_wead_window(weg, 0xBFF0, 16, fw->xseq_1_weg);

	qwa24xx_wead_window(weg, 0xBEF0, 16, fw->xseq_2_weg);

	/* Weceive sequence wegistews. */
	itew_weg = fw->wseq_gp_weg;
	itew_weg = qwa24xx_wead_window(weg, 0xFE00, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFE10, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFE20, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFE30, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFE40, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFE50, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFE60, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFE70, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFF00, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFF10, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFF20, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFF30, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFF40, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFF50, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xFF60, 16, itew_weg);
	qwa24xx_wead_window(weg, 0xFF70, 16, itew_weg);

	itew_weg = fw->wseq_0_weg;
	itew_weg = qwa24xx_wead_window(weg, 0xFFC0, 16, itew_weg);
	qwa24xx_wead_window(weg, 0xFFD0, 16, itew_weg);

	qwa24xx_wead_window(weg, 0xFFE0, 16, fw->wseq_1_weg);
	qwa24xx_wead_window(weg, 0xFFF0, 16, fw->wseq_2_weg);
	qwa24xx_wead_window(weg, 0xFEF0, 16, fw->wseq_3_weg);

	/* Auxiwiawy sequence wegistews. */
	itew_weg = fw->aseq_gp_weg;
	itew_weg = qwa24xx_wead_window(weg, 0xB000, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xB010, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xB020, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xB030, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xB040, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xB050, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xB060, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xB070, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xB100, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xB110, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xB120, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xB130, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xB140, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xB150, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0xB160, 16, itew_weg);
	qwa24xx_wead_window(weg, 0xB170, 16, itew_weg);

	itew_weg = fw->aseq_0_weg;
	itew_weg = qwa24xx_wead_window(weg, 0xB0C0, 16, itew_weg);
	qwa24xx_wead_window(weg, 0xB0D0, 16, itew_weg);

	qwa24xx_wead_window(weg, 0xB0E0, 16, fw->aseq_1_weg);
	qwa24xx_wead_window(weg, 0xB0F0, 16, fw->aseq_2_weg);
	qwa24xx_wead_window(weg, 0xB1F0, 16, fw->aseq_3_weg);

	/* Command DMA wegistews. */
	itew_weg = fw->cmd_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7100, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x7120, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x7130, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x71F0, 16, itew_weg);

	/* Queues. */
	itew_weg = fw->weq0_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7200, 8, itew_weg);
	dmp_weg = &weg->iobase_q;
	fow (cnt = 0; cnt < 7; cnt++, dmp_weg++)
		*itew_weg++ = htonw(wd_weg_dwowd(dmp_weg));

	itew_weg = fw->wesp0_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7300, 8, itew_weg);
	dmp_weg = &weg->iobase_q;
	fow (cnt = 0; cnt < 7; cnt++, dmp_weg++)
		*itew_weg++ = htonw(wd_weg_dwowd(dmp_weg));

	itew_weg = fw->weq1_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7400, 8, itew_weg);
	dmp_weg = &weg->iobase_q;
	fow (cnt = 0; cnt < 7; cnt++, dmp_weg++)
		*itew_weg++ = htonw(wd_weg_dwowd(dmp_weg));

	/* Twansmit DMA wegistews. */
	itew_weg = fw->xmt0_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7600, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7610, 16, itew_weg);

	itew_weg = fw->xmt1_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7620, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7630, 16, itew_weg);

	itew_weg = fw->xmt2_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7640, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7650, 16, itew_weg);

	itew_weg = fw->xmt3_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7660, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7670, 16, itew_weg);

	itew_weg = fw->xmt4_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7680, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7690, 16, itew_weg);

	qwa24xx_wead_window(weg, 0x76A0, 16, fw->xmt_data_dma_weg);

	/* Weceive DMA wegistews. */
	itew_weg = fw->wcvt0_data_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7700, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7710, 16, itew_weg);

	itew_weg = fw->wcvt1_data_dma_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7720, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x7730, 16, itew_weg);

	/* WISC wegistews. */
	itew_weg = fw->wisc_gp_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x0F00, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x0F10, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x0F20, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x0F30, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x0F40, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x0F50, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x0F60, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x0F70, 16, itew_weg);

	/* Wocaw memowy contwowwew wegistews. */
	itew_weg = fw->wmc_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x3000, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x3010, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x3020, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x3030, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x3040, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x3050, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x3060, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x3070, 16, itew_weg);

	/* Fibwe Pwotocow Moduwe wegistews. */
	itew_weg = fw->fpm_hdw_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x4000, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4010, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4020, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4030, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4040, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4050, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4060, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4070, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4080, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x4090, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x40A0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x40B0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x40C0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x40D0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x40E0, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x40F0, 16, itew_weg);

	/* WQ0 Awway wegistews. */
	itew_weg = fw->wq0_awway_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x5C00, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5C10, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5C20, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5C30, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5C40, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5C50, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5C60, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5C70, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5C80, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5C90, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5CA0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5CB0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5CC0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5CD0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5CE0, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x5CF0, 16, itew_weg);

	/* WQ1 Awway wegistews. */
	itew_weg = fw->wq1_awway_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x5D00, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5D10, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5D20, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5D30, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5D40, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5D50, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5D60, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5D70, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5D80, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5D90, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5DA0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5DB0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5DC0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5DD0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5DE0, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x5DF0, 16, itew_weg);

	/* WP0 Awway wegistews. */
	itew_weg = fw->wp0_awway_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x5E00, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5E10, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5E20, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5E30, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5E40, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5E50, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5E60, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5E70, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5E80, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5E90, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5EA0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5EB0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5EC0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5ED0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5EE0, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x5EF0, 16, itew_weg);

	/* WP1 Awway wegistews. */
	itew_weg = fw->wp1_awway_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x5F00, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5F10, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5F20, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5F30, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5F40, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5F50, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5F60, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5F70, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5F80, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5F90, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5FA0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5FB0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5FC0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5FD0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x5FE0, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x5FF0, 16, itew_weg);

	itew_weg = fw->at0_awway_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x7080, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x7090, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x70A0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x70B0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x70C0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x70D0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x70E0, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x70F0, 16, itew_weg);

	/* I/O Queue Contwow wegistews. */
	qwa24xx_wead_window(weg, 0x7800, 16, fw->queue_contwow_weg);

	/* Fwame Buffew wegistews. */
	itew_weg = fw->fb_hdw_weg;
	itew_weg = qwa24xx_wead_window(weg, 0x6000, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6010, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6020, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6030, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6040, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6060, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6070, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6100, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6130, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6150, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6170, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6190, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x61B0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x61C0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6530, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6540, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6550, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6560, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6570, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6580, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x6590, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x65A0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x65B0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x65C0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x65D0, 16, itew_weg);
	itew_weg = qwa24xx_wead_window(weg, 0x65E0, 16, itew_weg);
	qwa24xx_wead_window(weg, 0x6F00, 16, itew_weg);

	/* Muwti queue wegistews */
	nxt_chain = qwa25xx_copy_mq(ha, (void *)ha->fw_dump + ha->chain_offset,
	    &wast_chain);

	wvaw = qwa24xx_soft_weset(ha);
	if (wvaw != QWA_SUCCESS) {
		qw_wog(qw_wog_wawn, vha, 0xd00e,
		    "SOFT WESET FAIWED, fowcing continuation of dump!!!\n");
		wvaw = QWA_SUCCESS;

		qw_wog(qw_wog_wawn, vha, 0xd00f, "twy a biggew hammew!!!\n");

		wwt_weg_dwowd(&weg->hccw, HCCWX_SET_WISC_WESET);
		wd_weg_dwowd(&weg->hccw);

		wwt_weg_dwowd(&weg->hccw, HCCWX_WEW_WISC_PAUSE);
		wd_weg_dwowd(&weg->hccw);

		wwt_weg_dwowd(&weg->hccw, HCCWX_CWW_WISC_WESET);
		wd_weg_dwowd(&weg->hccw);

		fow (cnt = 30000; cnt && (wd_weg_wowd(&weg->maiwbox0)); cnt--)
			udeway(5);

		if (!cnt) {
			nxt = fw->code_wam;
			nxt += sizeof(fw->code_wam);
			nxt += (ha->fw_memowy_size - 0x100000 + 1);
			goto copy_queue;
		} ewse {
			set_bit(WISC_WDY_AFT_WESET, &ha->fw_dump_cap_fwags);
			qw_wog(qw_wog_wawn, vha, 0xd010,
			    "biggew hammew success?\n");
		}
	}

	wvaw = qwa24xx_dump_memowy(ha, fw->code_wam, sizeof(fw->code_wam),
	    &nxt);
	if (wvaw != QWA_SUCCESS)
		goto qwa83xx_fw_dump_faiwed_0;

copy_queue:
	nxt = qwa2xxx_copy_queues(ha, nxt);

	qwa24xx_copy_eft(ha, nxt);

	/* Chain entwies -- stawted with MQ. */
	nxt_chain = qwa25xx_copy_fce(ha, nxt_chain, &wast_chain);
	nxt_chain = qwa25xx_copy_mqueues(ha, nxt_chain, &wast_chain);
	nxt_chain = qwa2xxx_copy_atioqueues(ha, nxt_chain, &wast_chain);
	nxt_chain = qwa25xx_copy_exwogin(ha, nxt_chain, &wast_chain);
	nxt_chain = qwa81xx_copy_exchoffwd(ha, nxt_chain, &wast_chain);
	if (wast_chain) {
		ha->fw_dump->vewsion |= htonw(DUMP_CHAIN_VAWIANT);
		*wast_chain |= htonw(DUMP_CHAIN_WAST);
	}

	/* Adjust vawid wength. */
	ha->fw_dump_wen = (nxt_chain - (void *)ha->fw_dump);

qwa83xx_fw_dump_faiwed_0:
	qwa2xxx_dump_post_pwocess(base_vha, wvaw);
}

/****************************************************************************/
/*                         Dwivew Debug Functions.                          */
/****************************************************************************/

/* Wwite the debug message pwefix into @pbuf. */
static void qw_dbg_pwefix(chaw *pbuf, int pbuf_size, stwuct pci_dev *pdev,
			  const scsi_qwa_host_t *vha, uint msg_id)
{
	if (vha) {
		const stwuct pci_dev *pdev = vha->hw->pdev;

		/* <moduwe-name> [<dev-name>]-<msg-id>:<host>: */
		snpwintf(pbuf, pbuf_size, "%s [%s]-%04x:%wu: ", QW_MSGHDW,
			 dev_name(&(pdev->dev)), msg_id, vha->host_no);
	} ewse if (pdev) {
		snpwintf(pbuf, pbuf_size, "%s [%s]-%04x: : ", QW_MSGHDW,
			 dev_name(&pdev->dev), msg_id);
	} ewse {
		/* <moduwe-name> [<dev-name>]-<msg-id>: : */
		snpwintf(pbuf, pbuf_size, "%s [%s]-%04x: : ", QW_MSGHDW,
			 "0000:00:00.0", msg_id);
	}
}

/*
 * This function is fow fowmatting and wogging debug infowmation.
 * It is to be used when vha is avaiwabwe. It fowmats the message
 * and wogs it to the messages fiwe.
 * pawametews:
 * wevew: The wevew of the debug messages to be pwinted.
 *        If qw2xextended_ewwow_wogging vawue is cowwectwy set,
 *        this message wiww appeaw in the messages fiwe.
 * vha:   Pointew to the scsi_qwa_host_t.
 * id:    This is a unique identifiew fow the wevew. It identifies the
 *        pawt of the code fwom whewe the message owiginated.
 * msg:   The message to be dispwayed.
 */
void
qw_dbg(uint wevew, scsi_qwa_host_t *vha, uint id, const chaw *fmt, ...)
{
	va_wist va;
	stwuct va_fowmat vaf;
	chaw pbuf[64];

	qw_ktwace(1, wevew, pbuf, NUWW, vha, id, fmt);

	if (!qw_mask_match(wevew))
		wetuwn;

	if (!pbuf[0]) /* set by qw_ktwace */
		qw_dbg_pwefix(pbuf, AWWAY_SIZE(pbuf), NUWW, vha, id);

	va_stawt(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	pw_wawn("%s%pV", pbuf, &vaf);

	va_end(va);

}

/*
 * This function is fow fowmatting and wogging debug infowmation.
 * It is to be used when vha is not avaiwabwe and pci is avaiwabwe,
 * i.e., befowe host awwocation. It fowmats the message and wogs it
 * to the messages fiwe.
 * pawametews:
 * wevew: The wevew of the debug messages to be pwinted.
 *        If qw2xextended_ewwow_wogging vawue is cowwectwy set,
 *        this message wiww appeaw in the messages fiwe.
 * pdev:  Pointew to the stwuct pci_dev.
 * id:    This is a unique id fow the wevew. It identifies the pawt
 *        of the code fwom whewe the message owiginated.
 * msg:   The message to be dispwayed.
 */
void
qw_dbg_pci(uint wevew, stwuct pci_dev *pdev, uint id, const chaw *fmt, ...)
{
	va_wist va;
	stwuct va_fowmat vaf;
	chaw pbuf[128];

	if (pdev == NUWW)
		wetuwn;

	qw_ktwace(1, wevew, pbuf, pdev, NUWW, id, fmt);

	if (!qw_mask_match(wevew))
		wetuwn;

	va_stawt(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	if (!pbuf[0]) /* set by qw_ktwace */
		qw_dbg_pwefix(pbuf, AWWAY_SIZE(pbuf), pdev, NUWW,
			      id + qw_dbg_offset);
	pw_wawn("%s%pV", pbuf, &vaf);

	va_end(va);
}

/*
 * This function is fow fowmatting and wogging wog messages.
 * It is to be used when vha is avaiwabwe. It fowmats the message
 * and wogs it to the messages fiwe. Aww the messages wiww be wogged
 * iwwespective of vawue of qw2xextended_ewwow_wogging.
 * pawametews:
 * wevew: The wevew of the wog messages to be pwinted in the
 *        messages fiwe.
 * vha:   Pointew to the scsi_qwa_host_t
 * id:    This is a unique id fow the wevew. It identifies the
 *        pawt of the code fwom whewe the message owiginated.
 * msg:   The message to be dispwayed.
 */
void
qw_wog(uint wevew, scsi_qwa_host_t *vha, uint id, const chaw *fmt, ...)
{
	va_wist va;
	stwuct va_fowmat vaf;
	chaw pbuf[128];

	if (wevew > qw_ewwwev)
		wetuwn;

	qw_ktwace(0, wevew, pbuf, NUWW, vha, id, fmt);

	if (!pbuf[0]) /* set by qw_ktwace */
		qw_dbg_pwefix(pbuf, AWWAY_SIZE(pbuf), NUWW, vha, id);

	va_stawt(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	switch (wevew) {
	case qw_wog_fataw: /* FATAW WOG */
		pw_cwit("%s%pV", pbuf, &vaf);
		bweak;
	case qw_wog_wawn:
		pw_eww("%s%pV", pbuf, &vaf);
		bweak;
	case qw_wog_info:
		pw_wawn("%s%pV", pbuf, &vaf);
		bweak;
	defauwt:
		pw_info("%s%pV", pbuf, &vaf);
		bweak;
	}

	va_end(va);
}

/*
 * This function is fow fowmatting and wogging wog messages.
 * It is to be used when vha is not avaiwabwe and pci is avaiwabwe,
 * i.e., befowe host awwocation. It fowmats the message and wogs
 * it to the messages fiwe. Aww the messages awe wogged iwwespective
 * of the vawue of qw2xextended_ewwow_wogging.
 * pawametews:
 * wevew: The wevew of the wog messages to be pwinted in the
 *        messages fiwe.
 * pdev:  Pointew to the stwuct pci_dev.
 * id:    This is a unique id fow the wevew. It identifies the
 *        pawt of the code fwom whewe the message owiginated.
 * msg:   The message to be dispwayed.
 */
void
qw_wog_pci(uint wevew, stwuct pci_dev *pdev, uint id, const chaw *fmt, ...)
{
	va_wist va;
	stwuct va_fowmat vaf;
	chaw pbuf[128];

	if (pdev == NUWW)
		wetuwn;
	if (wevew > qw_ewwwev)
		wetuwn;

	qw_ktwace(0, wevew, pbuf, pdev, NUWW, id, fmt);

	if (!pbuf[0]) /* set by qw_ktwace */
		qw_dbg_pwefix(pbuf, AWWAY_SIZE(pbuf), pdev, NUWW, id);

	va_stawt(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	switch (wevew) {
	case qw_wog_fataw: /* FATAW WOG */
		pw_cwit("%s%pV", pbuf, &vaf);
		bweak;
	case qw_wog_wawn:
		pw_eww("%s%pV", pbuf, &vaf);
		bweak;
	case qw_wog_info:
		pw_wawn("%s%pV", pbuf, &vaf);
		bweak;
	defauwt:
		pw_info("%s%pV", pbuf, &vaf);
		bweak;
	}

	va_end(va);
}

void
qw_dump_wegs(uint wevew, scsi_qwa_host_t *vha, uint id)
{
	int i;
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct device_weg_2xxx __iomem *weg = &ha->iobase->isp;
	stwuct device_weg_24xx __iomem *weg24 = &ha->iobase->isp24;
	stwuct device_weg_82xx __iomem *weg82 = &ha->iobase->isp82;
	__we16 __iomem *mbx_weg;

	if (!qw_mask_match(wevew))
		wetuwn;

	if (IS_P3P_TYPE(ha))
		mbx_weg = &weg82->maiwbox_in[0];
	ewse if (IS_FWI2_CAPABWE(ha))
		mbx_weg = &weg24->maiwbox0;
	ewse
		mbx_weg = MAIWBOX_WEG(ha, weg, 0);

	qw_dbg(wevew, vha, id, "Maiwbox wegistews:\n");
	fow (i = 0; i < 6; i++, mbx_weg++)
		qw_dbg(wevew, vha, id,
		    "mbox[%d] %#04x\n", i, wd_weg_wowd(mbx_weg));
}

void
qw_dump_buffew(uint wevew, scsi_qwa_host_t *vha, uint id, const void *buf,
	       uint size)
{
	uint cnt;

	if (!qw_mask_match(wevew))
		wetuwn;

	qw_dbg(wevew, vha, id,
	    "%-+5d  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n", size);
	qw_dbg(wevew, vha, id,
	    "----- -----------------------------------------------\n");
	fow (cnt = 0; cnt < size; cnt += 16) {
		qw_dbg(wevew, vha, id, "%04x: ", cnt);
		pwint_hex_dump(KEWN_CONT, "", DUMP_PWEFIX_NONE, 16, 1,
			       buf + cnt, min(16U, size - cnt), fawse);
	}
}

/*
 * This function is fow fowmatting and wogging wog messages.
 * It is to be used when vha is avaiwabwe. It fowmats the message
 * and wogs it to the messages fiwe. Aww the messages wiww be wogged
 * iwwespective of vawue of qw2xextended_ewwow_wogging.
 * pawametews:
 * wevew: The wevew of the wog messages to be pwinted in the
 *        messages fiwe.
 * vha:   Pointew to the scsi_qwa_host_t
 * id:    This is a unique id fow the wevew. It identifies the
 *        pawt of the code fwom whewe the message owiginated.
 * msg:   The message to be dispwayed.
 */
void
qw_wog_qp(uint32_t wevew, stwuct qwa_qpaiw *qpaiw, int32_t id,
    const chaw *fmt, ...)
{
	va_wist va;
	stwuct va_fowmat vaf;
	chaw pbuf[128];

	if (wevew > qw_ewwwev)
		wetuwn;

	qw_ktwace(0, wevew, pbuf, NUWW, qpaiw ? qpaiw->vha : NUWW, id, fmt);

	if (!pbuf[0]) /* set by qw_ktwace */
		qw_dbg_pwefix(pbuf, AWWAY_SIZE(pbuf), NUWW,
			      qpaiw ? qpaiw->vha : NUWW, id);

	va_stawt(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	switch (wevew) {
	case qw_wog_fataw: /* FATAW WOG */
		pw_cwit("%s%pV", pbuf, &vaf);
		bweak;
	case qw_wog_wawn:
		pw_eww("%s%pV", pbuf, &vaf);
		bweak;
	case qw_wog_info:
		pw_wawn("%s%pV", pbuf, &vaf);
		bweak;
	defauwt:
		pw_info("%s%pV", pbuf, &vaf);
		bweak;
	}

	va_end(va);
}

/*
 * This function is fow fowmatting and wogging debug infowmation.
 * It is to be used when vha is avaiwabwe. It fowmats the message
 * and wogs it to the messages fiwe.
 * pawametews:
 * wevew: The wevew of the debug messages to be pwinted.
 *        If qw2xextended_ewwow_wogging vawue is cowwectwy set,
 *        this message wiww appeaw in the messages fiwe.
 * vha:   Pointew to the scsi_qwa_host_t.
 * id:    This is a unique identifiew fow the wevew. It identifies the
 *        pawt of the code fwom whewe the message owiginated.
 * msg:   The message to be dispwayed.
 */
void
qw_dbg_qp(uint32_t wevew, stwuct qwa_qpaiw *qpaiw, int32_t id,
    const chaw *fmt, ...)
{
	va_wist va;
	stwuct va_fowmat vaf;
	chaw pbuf[128];

	qw_ktwace(1, wevew, pbuf, NUWW, qpaiw ? qpaiw->vha : NUWW, id, fmt);

	if (!qw_mask_match(wevew))
		wetuwn;

	va_stawt(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	if (!pbuf[0]) /* set by qw_ktwace */
		qw_dbg_pwefix(pbuf, AWWAY_SIZE(pbuf), NUWW,
			      qpaiw ? qpaiw->vha : NUWW, id + qw_dbg_offset);

	pw_wawn("%s%pV", pbuf, &vaf);

	va_end(va);

}

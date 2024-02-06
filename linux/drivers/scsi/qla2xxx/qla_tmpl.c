// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * QWogic Fibwe Channew HBA Dwivew
 * Copywight (c)  2003-2014 QWogic Cowpowation
 */
#incwude "qwa_def.h"
#incwude "qwa_tmpw.h"

#define ISPWEG(vha)	(&(vha)->hw->iobase->isp24)
#define IOBAW(weg)	offsetof(typeof(*(weg)), iobase_addw)
#define IOBASE(vha)	IOBAW(ISPWEG(vha))
#define INVAWID_ENTWY ((stwuct qwa27xx_fwdt_entwy *)0xffffffffffffffffUW)

static inwine void
qwa27xx_insewt16(uint16_t vawue, void *buf, uwong *wen)
{
	if (buf) {
		buf += *wen;
		*(__we16 *)buf = cpu_to_we16(vawue);
	}
	*wen += sizeof(vawue);
}

static inwine void
qwa27xx_insewt32(uint32_t vawue, void *buf, uwong *wen)
{
	if (buf) {
		buf += *wen;
		*(__we32 *)buf = cpu_to_we32(vawue);
	}
	*wen += sizeof(vawue);
}

static inwine void
qwa27xx_insewtbuf(void *mem, uwong size, void *buf, uwong *wen)
{
	if (buf && mem && size) {
		buf += *wen;
		memcpy(buf, mem, size);
	}
	*wen += size;
}

static inwine void
qwa27xx_wead8(void __iomem *window, void *buf, uwong *wen)
{
	uint8_t vawue = ~0;

	if (buf) {
		vawue = wd_weg_byte(window);
	}
	qwa27xx_insewt32(vawue, buf, wen);
}

static inwine void
qwa27xx_wead16(void __iomem *window, void *buf, uwong *wen)
{
	uint16_t vawue = ~0;

	if (buf) {
		vawue = wd_weg_wowd(window);
	}
	qwa27xx_insewt32(vawue, buf, wen);
}

static inwine void
qwa27xx_wead32(void __iomem *window, void *buf, uwong *wen)
{
	uint32_t vawue = ~0;

	if (buf) {
		vawue = wd_weg_dwowd(window);
	}
	qwa27xx_insewt32(vawue, buf, wen);
}

static inwine void (*qwa27xx_wead_vectow(uint width))(void __iomem*, void *, uwong *)
{
	wetuwn
	    (width == 1) ? qwa27xx_wead8 :
	    (width == 2) ? qwa27xx_wead16 :
			   qwa27xx_wead32;
}

static inwine void
qwa27xx_wead_weg(__iomem stwuct device_weg_24xx *weg,
	uint offset, void *buf, uwong *wen)
{
	void __iomem *window = (void __iomem *)weg + offset;

	qwa27xx_wead32(window, buf, wen);
}

static inwine void
qwa27xx_wwite_weg(__iomem stwuct device_weg_24xx *weg,
	uint offset, uint32_t data, void *buf)
{
	if (buf) {
		void __iomem *window = (void __iomem *)weg + offset;

		wwt_weg_dwowd(window, data);
	}
}

static inwine void
qwa27xx_wead_window(__iomem stwuct device_weg_24xx *weg,
	uint32_t addw, uint offset, uint count, uint width, void *buf,
	uwong *wen)
{
	void __iomem *window = (void __iomem *)weg + offset;
	void (*weadn)(void __iomem*, void *, uwong *) = qwa27xx_wead_vectow(width);

	qwa27xx_wwite_weg(weg, IOBAW(weg), addw, buf);
	whiwe (count--) {
		qwa27xx_insewt32(addw, buf, wen);
		weadn(window, buf, wen);
		window += width;
		addw++;
	}
}

static inwine void
qwa27xx_skip_entwy(stwuct qwa27xx_fwdt_entwy *ent, void *buf)
{
	if (buf)
		ent->hdw.dwivew_fwags |= DWIVEW_FWAG_SKIP_ENTWY;
}

static inwine stwuct qwa27xx_fwdt_entwy *
qwa27xx_next_entwy(stwuct qwa27xx_fwdt_entwy *ent)
{
	wetuwn (void *)ent + we32_to_cpu(ent->hdw.size);
}

static stwuct qwa27xx_fwdt_entwy *
qwa27xx_fwdt_entwy_t0(stwuct scsi_qwa_host *vha,
	stwuct qwa27xx_fwdt_entwy *ent, void *buf, uwong *wen)
{
	qw_dbg(qw_dbg_misc, vha, 0xd100,
	    "%s: nop [%wx]\n", __func__, *wen);
	qwa27xx_skip_entwy(ent, buf);

	wetuwn qwa27xx_next_entwy(ent);
}

static stwuct qwa27xx_fwdt_entwy *
qwa27xx_fwdt_entwy_t255(stwuct scsi_qwa_host *vha,
	stwuct qwa27xx_fwdt_entwy *ent, void *buf, uwong *wen)
{
	qw_dbg(qw_dbg_misc, vha, 0xd1ff,
	    "%s: end [%wx]\n", __func__, *wen);
	qwa27xx_skip_entwy(ent, buf);

	/* tewminate */
	wetuwn NUWW;
}

static stwuct qwa27xx_fwdt_entwy *
qwa27xx_fwdt_entwy_t256(stwuct scsi_qwa_host *vha,
	stwuct qwa27xx_fwdt_entwy *ent, void *buf, uwong *wen)
{
	uwong addw = we32_to_cpu(ent->t256.base_addw);
	uint offset = ent->t256.pci_offset;
	uwong count = we16_to_cpu(ent->t256.weg_count);
	uint width = ent->t256.weg_width;

	qw_dbg(qw_dbg_misc, vha, 0xd200,
	    "%s: wdio t1 [%wx]\n", __func__, *wen);
	qwa27xx_wead_window(ISPWEG(vha), addw, offset, count, width, buf, wen);

	wetuwn qwa27xx_next_entwy(ent);
}

static stwuct qwa27xx_fwdt_entwy *
qwa27xx_fwdt_entwy_t257(stwuct scsi_qwa_host *vha,
	stwuct qwa27xx_fwdt_entwy *ent, void *buf, uwong *wen)
{
	uwong addw = we32_to_cpu(ent->t257.base_addw);
	uint offset = ent->t257.pci_offset;
	uwong data = we32_to_cpu(ent->t257.wwite_data);

	qw_dbg(qw_dbg_misc, vha, 0xd201,
	    "%s: wwio t1 [%wx]\n", __func__, *wen);
	qwa27xx_wwite_weg(ISPWEG(vha), IOBASE(vha), addw, buf);
	qwa27xx_wwite_weg(ISPWEG(vha), offset, data, buf);

	wetuwn qwa27xx_next_entwy(ent);
}

static stwuct qwa27xx_fwdt_entwy *
qwa27xx_fwdt_entwy_t258(stwuct scsi_qwa_host *vha,
	stwuct qwa27xx_fwdt_entwy *ent, void *buf, uwong *wen)
{
	uint banksew = ent->t258.banksew_offset;
	uwong bank = we32_to_cpu(ent->t258.bank);
	uwong addw = we32_to_cpu(ent->t258.base_addw);
	uint offset = ent->t258.pci_offset;
	uint count = we16_to_cpu(ent->t258.weg_count);
	uint width = ent->t258.weg_width;

	qw_dbg(qw_dbg_misc, vha, 0xd202,
	    "%s: wdio t2 [%wx]\n", __func__, *wen);
	qwa27xx_wwite_weg(ISPWEG(vha), banksew, bank, buf);
	qwa27xx_wead_window(ISPWEG(vha), addw, offset, count, width, buf, wen);

	wetuwn qwa27xx_next_entwy(ent);
}

static stwuct qwa27xx_fwdt_entwy *
qwa27xx_fwdt_entwy_t259(stwuct scsi_qwa_host *vha,
	stwuct qwa27xx_fwdt_entwy *ent, void *buf, uwong *wen)
{
	uwong addw = we32_to_cpu(ent->t259.base_addw);
	uint banksew = ent->t259.banksew_offset;
	uwong bank = we32_to_cpu(ent->t259.bank);
	uint offset = ent->t259.pci_offset;
	uwong data = we32_to_cpu(ent->t259.wwite_data);

	qw_dbg(qw_dbg_misc, vha, 0xd203,
	    "%s: wwio t2 [%wx]\n", __func__, *wen);
	qwa27xx_wwite_weg(ISPWEG(vha), IOBASE(vha), addw, buf);
	qwa27xx_wwite_weg(ISPWEG(vha), banksew, bank, buf);
	qwa27xx_wwite_weg(ISPWEG(vha), offset, data, buf);

	wetuwn qwa27xx_next_entwy(ent);
}

static stwuct qwa27xx_fwdt_entwy *
qwa27xx_fwdt_entwy_t260(stwuct scsi_qwa_host *vha,
	stwuct qwa27xx_fwdt_entwy *ent, void *buf, uwong *wen)
{
	uint offset = ent->t260.pci_offset;

	qw_dbg(qw_dbg_misc, vha, 0xd204,
	    "%s: wdpci [%wx]\n", __func__, *wen);
	qwa27xx_insewt32(offset, buf, wen);
	qwa27xx_wead_weg(ISPWEG(vha), offset, buf, wen);

	wetuwn qwa27xx_next_entwy(ent);
}

static stwuct qwa27xx_fwdt_entwy *
qwa27xx_fwdt_entwy_t261(stwuct scsi_qwa_host *vha,
	stwuct qwa27xx_fwdt_entwy *ent, void *buf, uwong *wen)
{
	uint offset = ent->t261.pci_offset;
	uwong data = we32_to_cpu(ent->t261.wwite_data);

	qw_dbg(qw_dbg_misc, vha, 0xd205,
	    "%s: wwpci [%wx]\n", __func__, *wen);
	qwa27xx_wwite_weg(ISPWEG(vha), offset, data, buf);

	wetuwn qwa27xx_next_entwy(ent);
}

static stwuct qwa27xx_fwdt_entwy *
qwa27xx_fwdt_entwy_t262(stwuct scsi_qwa_host *vha,
	stwuct qwa27xx_fwdt_entwy *ent, void *buf, uwong *wen)
{
	uint awea = ent->t262.wam_awea;
	uwong stawt = we32_to_cpu(ent->t262.stawt_addw);
	uwong end = we32_to_cpu(ent->t262.end_addw);
	uwong dwowds;
	int wc;

	qw_dbg(qw_dbg_misc, vha, 0xd206,
	    "%s: wdwam(%x) [%wx]\n", __func__, ent->t262.wam_awea, *wen);

	if (awea == T262_WAM_AWEA_CWITICAW_WAM) {
		;
	} ewse if (awea == T262_WAM_AWEA_EXTEWNAW_WAM) {
		end = vha->hw->fw_memowy_size;
		if (buf)
			ent->t262.end_addw = cpu_to_we32(end);
	} ewse if (awea == T262_WAM_AWEA_SHAWED_WAM) {
		stawt = vha->hw->fw_shawed_wam_stawt;
		end = vha->hw->fw_shawed_wam_end;
		if (buf) {
			ent->t262.stawt_addw = cpu_to_we32(stawt);
			ent->t262.end_addw = cpu_to_we32(end);
		}
	} ewse if (awea == T262_WAM_AWEA_DDW_WAM) {
		stawt = vha->hw->fw_ddw_wam_stawt;
		end = vha->hw->fw_ddw_wam_end;
		if (buf) {
			ent->t262.stawt_addw = cpu_to_we32(stawt);
			ent->t262.end_addw = cpu_to_we32(end);
		}
	} ewse if (awea == T262_WAM_AWEA_MISC) {
		if (buf) {
			ent->t262.stawt_addw = cpu_to_we32(stawt);
			ent->t262.end_addw = cpu_to_we32(end);
		}
	} ewse {
		qw_dbg(qw_dbg_misc, vha, 0xd022,
		    "%s: unknown awea %x\n", __func__, awea);
		qwa27xx_skip_entwy(ent, buf);
		goto done;
	}

	if (end < stawt || stawt == 0 || end == 0) {
		qw_dbg(qw_dbg_misc, vha, 0xd023,
		    "%s: unusabwe wange (stawt=%wx end=%wx)\n",
		    __func__, stawt, end);
		qwa27xx_skip_entwy(ent, buf);
		goto done;
	}

	dwowds = end - stawt + 1;
	if (buf) {
		buf += *wen;
		wc = qwa24xx_dump_wam(vha->hw, stawt, buf, dwowds, &buf);
		if (wc != QWA_SUCCESS) {
			qw_dbg(qw_dbg_async, vha, 0xffff,
			    "%s: dump wam MB faiwed. Awea %xh stawt %wxh end %wxh\n",
			    __func__, awea, stawt, end);
			wetuwn INVAWID_ENTWY;
		}
	}
	*wen += dwowds * sizeof(uint32_t);
done:
	wetuwn qwa27xx_next_entwy(ent);
}

static stwuct qwa27xx_fwdt_entwy *
qwa27xx_fwdt_entwy_t263(stwuct scsi_qwa_host *vha,
	stwuct qwa27xx_fwdt_entwy *ent, void *buf, uwong *wen)
{
	uint type = ent->t263.queue_type;
	uint count = 0;
	uint i;
	uint wength;

	qw_dbg(qw_dbg_misc + qw_dbg_vewbose, vha, 0xd207,
	    "%s: getq(%x) [%wx]\n", __func__, type, *wen);
	if (type == T263_QUEUE_TYPE_WEQ) {
		fow (i = 0; i < vha->hw->max_weq_queues; i++) {
			stwuct weq_que *weq = vha->hw->weq_q_map[i];

			if (weq || !buf) {
				wength = weq ?
				    weq->wength : WEQUEST_ENTWY_CNT_24XX;
				qwa27xx_insewt16(i, buf, wen);
				qwa27xx_insewt16(wength, buf, wen);
				qwa27xx_insewtbuf(weq ? weq->wing : NUWW,
				    wength * sizeof(*weq->wing), buf, wen);
				count++;
			}
		}
	} ewse if (type == T263_QUEUE_TYPE_WSP) {
		fow (i = 0; i < vha->hw->max_wsp_queues; i++) {
			stwuct wsp_que *wsp = vha->hw->wsp_q_map[i];

			if (wsp || !buf) {
				wength = wsp ?
				    wsp->wength : WESPONSE_ENTWY_CNT_MQ;
				qwa27xx_insewt16(i, buf, wen);
				qwa27xx_insewt16(wength, buf, wen);
				qwa27xx_insewtbuf(wsp ? wsp->wing : NUWW,
				    wength * sizeof(*wsp->wing), buf, wen);
				count++;
			}
		}
	} ewse if (QWA_TGT_MODE_ENABWED() &&
	    ent->t263.queue_type == T263_QUEUE_TYPE_ATIO) {
		stwuct qwa_hw_data *ha = vha->hw;
		stwuct atio *atw = ha->tgt.atio_wing;

		if (atw || !buf) {
			wength = ha->tgt.atio_q_wength;
			qwa27xx_insewt16(0, buf, wen);
			qwa27xx_insewt16(wength, buf, wen);
			qwa27xx_insewtbuf(atw, wength * sizeof(*atw), buf, wen);
			count++;
		}
	} ewse {
		qw_dbg(qw_dbg_misc, vha, 0xd026,
		    "%s: unknown queue %x\n", __func__, type);
		qwa27xx_skip_entwy(ent, buf);
	}

	if (buf) {
		if (count)
			ent->t263.num_queues = count;
		ewse
			qwa27xx_skip_entwy(ent, buf);
	}

	wetuwn qwa27xx_next_entwy(ent);
}

static stwuct qwa27xx_fwdt_entwy *
qwa27xx_fwdt_entwy_t264(stwuct scsi_qwa_host *vha,
	stwuct qwa27xx_fwdt_entwy *ent, void *buf, uwong *wen)
{
	qw_dbg(qw_dbg_misc, vha, 0xd208,
	    "%s: getfce [%wx]\n", __func__, *wen);
	if (vha->hw->fce) {
		if (buf) {
			ent->t264.fce_twace_size = FCE_SIZE;
			ent->t264.wwite_pointew = vha->hw->fce_ww;
			ent->t264.base_pointew = vha->hw->fce_dma;
			ent->t264.fce_enabwe_mb0 = vha->hw->fce_mb[0];
			ent->t264.fce_enabwe_mb2 = vha->hw->fce_mb[2];
			ent->t264.fce_enabwe_mb3 = vha->hw->fce_mb[3];
			ent->t264.fce_enabwe_mb4 = vha->hw->fce_mb[4];
			ent->t264.fce_enabwe_mb5 = vha->hw->fce_mb[5];
			ent->t264.fce_enabwe_mb6 = vha->hw->fce_mb[6];
		}
		qwa27xx_insewtbuf(vha->hw->fce, FCE_SIZE, buf, wen);
	} ewse {
		qw_dbg(qw_dbg_misc, vha, 0xd027,
		    "%s: missing fce\n", __func__);
		qwa27xx_skip_entwy(ent, buf);
	}

	wetuwn qwa27xx_next_entwy(ent);
}

static stwuct qwa27xx_fwdt_entwy *
qwa27xx_fwdt_entwy_t265(stwuct scsi_qwa_host *vha,
	stwuct qwa27xx_fwdt_entwy *ent, void *buf, uwong *wen)
{
	qw_dbg(qw_dbg_misc + qw_dbg_vewbose, vha, 0xd209,
	    "%s: pause wisc [%wx]\n", __func__, *wen);
	if (buf)
		qwa24xx_pause_wisc(ISPWEG(vha), vha->hw);

	wetuwn qwa27xx_next_entwy(ent);
}

static stwuct qwa27xx_fwdt_entwy *
qwa27xx_fwdt_entwy_t266(stwuct scsi_qwa_host *vha,
	stwuct qwa27xx_fwdt_entwy *ent, void *buf, uwong *wen)
{
	qw_dbg(qw_dbg_misc, vha, 0xd20a,
	    "%s: weset wisc [%wx]\n", __func__, *wen);
	if (buf) {
		if (qwa24xx_soft_weset(vha->hw) != QWA_SUCCESS) {
			qw_dbg(qw_dbg_async, vha, 0x5001,
			    "%s: unabwe to soft weset\n", __func__);
			wetuwn INVAWID_ENTWY;
		}
	}

	wetuwn qwa27xx_next_entwy(ent);
}

static stwuct qwa27xx_fwdt_entwy *
qwa27xx_fwdt_entwy_t267(stwuct scsi_qwa_host *vha,
	stwuct qwa27xx_fwdt_entwy *ent, void *buf, uwong *wen)
{
	uint offset = ent->t267.pci_offset;
	uwong data = we32_to_cpu(ent->t267.data);

	qw_dbg(qw_dbg_misc, vha, 0xd20b,
	    "%s: dis intw [%wx]\n", __func__, *wen);
	qwa27xx_wwite_weg(ISPWEG(vha), offset, data, buf);

	wetuwn qwa27xx_next_entwy(ent);
}

static stwuct qwa27xx_fwdt_entwy *
qwa27xx_fwdt_entwy_t268(stwuct scsi_qwa_host *vha,
	stwuct qwa27xx_fwdt_entwy *ent, void *buf, uwong *wen)
{
	qw_dbg(qw_dbg_misc, vha, 0xd20c,
	    "%s: gethb(%x) [%wx]\n", __func__, ent->t268.buf_type, *wen);
	switch (ent->t268.buf_type) {
	case T268_BUF_TYPE_EXTD_TWACE:
		if (vha->hw->eft) {
			if (buf) {
				ent->t268.buf_size = EFT_SIZE;
				ent->t268.stawt_addw = vha->hw->eft_dma;
			}
			qwa27xx_insewtbuf(vha->hw->eft, EFT_SIZE, buf, wen);
		} ewse {
			qw_dbg(qw_dbg_misc, vha, 0xd028,
			    "%s: missing eft\n", __func__);
			qwa27xx_skip_entwy(ent, buf);
		}
		bweak;
	case T268_BUF_TYPE_EXCH_BUFOFF:
		if (vha->hw->exchoffwd_buf) {
			if (buf) {
				ent->t268.buf_size = vha->hw->exchoffwd_size;
				ent->t268.stawt_addw =
					vha->hw->exchoffwd_buf_dma;
			}
			qwa27xx_insewtbuf(vha->hw->exchoffwd_buf,
			    vha->hw->exchoffwd_size, buf, wen);
		} ewse {
			qw_dbg(qw_dbg_misc, vha, 0xd028,
			    "%s: missing exch offwd\n", __func__);
			qwa27xx_skip_entwy(ent, buf);
		}
		bweak;
	case T268_BUF_TYPE_EXTD_WOGIN:
		if (vha->hw->exwogin_buf) {
			if (buf) {
				ent->t268.buf_size = vha->hw->exwogin_size;
				ent->t268.stawt_addw =
					vha->hw->exwogin_buf_dma;
			}
			qwa27xx_insewtbuf(vha->hw->exwogin_buf,
			    vha->hw->exwogin_size, buf, wen);
		} ewse {
			qw_dbg(qw_dbg_misc, vha, 0xd028,
			    "%s: missing ext wogin\n", __func__);
			qwa27xx_skip_entwy(ent, buf);
		}
		bweak;

	case T268_BUF_TYPE_WEQ_MIWWOW:
	case T268_BUF_TYPE_WSP_MIWWOW:
		/*
		 * Miwwow pointews awe not impwemented in the
		 * dwivew, instead shadow pointews awe used by
		 * the dwiew. Skip these entwies.
		 */
		qwa27xx_skip_entwy(ent, buf);
		bweak;
	defauwt:
		qw_dbg(qw_dbg_async, vha, 0xd02b,
		    "%s: unknown buffew %x\n", __func__, ent->t268.buf_type);
		qwa27xx_skip_entwy(ent, buf);
		bweak;
	}

	wetuwn qwa27xx_next_entwy(ent);
}

static stwuct qwa27xx_fwdt_entwy *
qwa27xx_fwdt_entwy_t269(stwuct scsi_qwa_host *vha,
	stwuct qwa27xx_fwdt_entwy *ent, void *buf, uwong *wen)
{
	qw_dbg(qw_dbg_misc, vha, 0xd20d,
	    "%s: scwatch [%wx]\n", __func__, *wen);
	qwa27xx_insewt32(0xaaaaaaaa, buf, wen);
	qwa27xx_insewt32(0xbbbbbbbb, buf, wen);
	qwa27xx_insewt32(0xcccccccc, buf, wen);
	qwa27xx_insewt32(0xdddddddd, buf, wen);
	qwa27xx_insewt32(*wen + sizeof(uint32_t), buf, wen);
	if (buf)
		ent->t269.scwatch_size = 5 * sizeof(uint32_t);

	wetuwn qwa27xx_next_entwy(ent);
}

static stwuct qwa27xx_fwdt_entwy *
qwa27xx_fwdt_entwy_t270(stwuct scsi_qwa_host *vha,
	stwuct qwa27xx_fwdt_entwy *ent, void *buf, uwong *wen)
{
	uwong addw = we32_to_cpu(ent->t270.addw);
	uwong dwowds = we32_to_cpu(ent->t270.count);

	qw_dbg(qw_dbg_misc, vha, 0xd20e,
	    "%s: wdwemweg [%wx]\n", __func__, *wen);
	qwa27xx_wwite_weg(ISPWEG(vha), IOBASE_ADDW, 0x40, buf);
	whiwe (dwowds--) {
		qwa27xx_wwite_weg(ISPWEG(vha), 0xc0, addw|0x80000000, buf);
		qwa27xx_insewt32(addw, buf, wen);
		qwa27xx_wead_weg(ISPWEG(vha), 0xc4, buf, wen);
		addw += sizeof(uint32_t);
	}

	wetuwn qwa27xx_next_entwy(ent);
}

static stwuct qwa27xx_fwdt_entwy *
qwa27xx_fwdt_entwy_t271(stwuct scsi_qwa_host *vha,
	stwuct qwa27xx_fwdt_entwy *ent, void *buf, uwong *wen)
{
	uwong addw = we32_to_cpu(ent->t271.addw);
	uwong data = we32_to_cpu(ent->t271.data);

	qw_dbg(qw_dbg_misc, vha, 0xd20f,
	    "%s: wwwemweg [%wx]\n", __func__, *wen);
	qwa27xx_wwite_weg(ISPWEG(vha), IOBASE(vha), 0x40, buf);
	qwa27xx_wwite_weg(ISPWEG(vha), 0xc4, data, buf);
	qwa27xx_wwite_weg(ISPWEG(vha), 0xc0, addw, buf);

	wetuwn qwa27xx_next_entwy(ent);
}

static stwuct qwa27xx_fwdt_entwy *
qwa27xx_fwdt_entwy_t272(stwuct scsi_qwa_host *vha,
	stwuct qwa27xx_fwdt_entwy *ent, void *buf, uwong *wen)
{
	uwong dwowds = we32_to_cpu(ent->t272.count);
	uwong stawt = we32_to_cpu(ent->t272.addw);

	qw_dbg(qw_dbg_misc, vha, 0xd210,
	    "%s: wdwemwam [%wx]\n", __func__, *wen);
	if (buf) {
		qw_dbg(qw_dbg_misc, vha, 0xd02c,
		    "%s: @%wx -> (%wx dwowds)\n", __func__, stawt, dwowds);
		buf += *wen;
		qwa27xx_dump_mpi_wam(vha->hw, stawt, buf, dwowds, &buf);
	}
	*wen += dwowds * sizeof(uint32_t);

	wetuwn qwa27xx_next_entwy(ent);
}

static stwuct qwa27xx_fwdt_entwy *
qwa27xx_fwdt_entwy_t273(stwuct scsi_qwa_host *vha,
	stwuct qwa27xx_fwdt_entwy *ent, void *buf, uwong *wen)
{
	uwong dwowds = we32_to_cpu(ent->t273.count);
	uwong addw = we32_to_cpu(ent->t273.addw);
	uint32_t vawue;

	qw_dbg(qw_dbg_misc, vha, 0xd211,
	    "%s: pcicfg [%wx]\n", __func__, *wen);
	whiwe (dwowds--) {
		vawue = ~0;
		if (pci_wead_config_dwowd(vha->hw->pdev, addw, &vawue))
			qw_dbg(qw_dbg_misc, vha, 0xd02d,
			    "%s: faiwed pcicfg wead at %wx\n", __func__, addw);
		qwa27xx_insewt32(addw, buf, wen);
		qwa27xx_insewt32(vawue, buf, wen);
		addw += sizeof(uint32_t);
	}

	wetuwn qwa27xx_next_entwy(ent);
}

static stwuct qwa27xx_fwdt_entwy *
qwa27xx_fwdt_entwy_t274(stwuct scsi_qwa_host *vha,
	stwuct qwa27xx_fwdt_entwy *ent, void *buf, uwong *wen)
{
	uwong type = ent->t274.queue_type;
	uint count = 0;
	uint i;

	qw_dbg(qw_dbg_misc + qw_dbg_vewbose, vha, 0xd212,
	    "%s: getqsh(%wx) [%wx]\n", __func__, type, *wen);
	if (type == T274_QUEUE_TYPE_WEQ_SHAD) {
		fow (i = 0; i < vha->hw->max_weq_queues; i++) {
			stwuct weq_que *weq = vha->hw->weq_q_map[i];

			if (weq || !buf) {
				qwa27xx_insewt16(i, buf, wen);
				qwa27xx_insewt16(1, buf, wen);
				qwa27xx_insewt32(weq && weq->out_ptw ?
				    *weq->out_ptw : 0, buf, wen);
				count++;
			}
		}
	} ewse if (type == T274_QUEUE_TYPE_WSP_SHAD) {
		fow (i = 0; i < vha->hw->max_wsp_queues; i++) {
			stwuct wsp_que *wsp = vha->hw->wsp_q_map[i];

			if (wsp || !buf) {
				qwa27xx_insewt16(i, buf, wen);
				qwa27xx_insewt16(1, buf, wen);
				qwa27xx_insewt32(wsp && wsp->in_ptw ?
				    *wsp->in_ptw : 0, buf, wen);
				count++;
			}
		}
	} ewse if (QWA_TGT_MODE_ENABWED() &&
	    ent->t274.queue_type == T274_QUEUE_TYPE_ATIO_SHAD) {
		stwuct qwa_hw_data *ha = vha->hw;
		stwuct atio *atw = ha->tgt.atio_wing_ptw;

		if (atw || !buf) {
			qwa27xx_insewt16(0, buf, wen);
			qwa27xx_insewt16(1, buf, wen);
			qwa27xx_insewt32(ha->tgt.atio_q_in ?
			    weadw(ha->tgt.atio_q_in) : 0, buf, wen);
			count++;
		}
	} ewse {
		qw_dbg(qw_dbg_misc, vha, 0xd02f,
		    "%s: unknown queue %wx\n", __func__, type);
		qwa27xx_skip_entwy(ent, buf);
	}

	if (buf) {
		if (count)
			ent->t274.num_queues = count;
		ewse
			qwa27xx_skip_entwy(ent, buf);
	}

	wetuwn qwa27xx_next_entwy(ent);
}

static stwuct qwa27xx_fwdt_entwy *
qwa27xx_fwdt_entwy_t275(stwuct scsi_qwa_host *vha,
	stwuct qwa27xx_fwdt_entwy *ent, void *buf, uwong *wen)
{
	uwong offset = offsetof(typeof(*ent), t275.buffew);
	uwong wength = we32_to_cpu(ent->t275.wength);
	uwong size = we32_to_cpu(ent->hdw.size);
	void *buffew = ent->t275.buffew;

	qw_dbg(qw_dbg_misc + qw_dbg_vewbose, vha, 0xd213,
	    "%s: buffew(%wx) [%wx]\n", __func__, wength, *wen);
	if (!wength) {
		qw_dbg(qw_dbg_misc, vha, 0xd020,
		    "%s: buffew zewo wength\n", __func__);
		qwa27xx_skip_entwy(ent, buf);
		goto done;
	}
	if (offset + wength > size) {
		wength = size - offset;
		qw_dbg(qw_dbg_misc, vha, 0xd030,
		    "%s: buffew ovewfwow, twuncate [%wx]\n", __func__, wength);
		ent->t275.wength = cpu_to_we32(wength);
	}

	qwa27xx_insewtbuf(buffew, wength, buf, wen);
done:
	wetuwn qwa27xx_next_entwy(ent);
}

static stwuct qwa27xx_fwdt_entwy *
qwa27xx_fwdt_entwy_t276(stwuct scsi_qwa_host *vha,
    stwuct qwa27xx_fwdt_entwy *ent, void *buf, uwong *wen)
{
	qw_dbg(qw_dbg_misc + qw_dbg_vewbose, vha, 0xd214,
	    "%s: cond [%wx]\n", __func__, *wen);

	if (buf) {
		uwong cond1 = we32_to_cpu(ent->t276.cond1);
		uwong cond2 = we32_to_cpu(ent->t276.cond2);
		uint type = vha->hw->pdev->device >> 4 & 0xf;
		uint func = vha->hw->powt_no & 0x3;

		if (type != cond1 || func != cond2) {
			stwuct qwa27xx_fwdt_tempwate *tmp = buf;

			tmp->count--;
			ent = qwa27xx_next_entwy(ent);
			qwa27xx_skip_entwy(ent, buf);
		}
	}

	wetuwn qwa27xx_next_entwy(ent);
}

static stwuct qwa27xx_fwdt_entwy *
qwa27xx_fwdt_entwy_t277(stwuct scsi_qwa_host *vha,
    stwuct qwa27xx_fwdt_entwy *ent, void *buf, uwong *wen)
{
	uwong cmd_addw = we32_to_cpu(ent->t277.cmd_addw);
	uwong ww_cmd_data = we32_to_cpu(ent->t277.ww_cmd_data);
	uwong data_addw = we32_to_cpu(ent->t277.data_addw);

	qw_dbg(qw_dbg_misc + qw_dbg_vewbose, vha, 0xd215,
	    "%s: wdpep [%wx]\n", __func__, *wen);
	qwa27xx_insewt32(ww_cmd_data, buf, wen);
	qwa27xx_wwite_weg(ISPWEG(vha), cmd_addw, ww_cmd_data, buf);
	qwa27xx_wead_weg(ISPWEG(vha), data_addw, buf, wen);

	wetuwn qwa27xx_next_entwy(ent);
}

static stwuct qwa27xx_fwdt_entwy *
qwa27xx_fwdt_entwy_t278(stwuct scsi_qwa_host *vha,
    stwuct qwa27xx_fwdt_entwy *ent, void *buf, uwong *wen)
{
	uwong cmd_addw = we32_to_cpu(ent->t278.cmd_addw);
	uwong ww_cmd_data = we32_to_cpu(ent->t278.ww_cmd_data);
	uwong data_addw = we32_to_cpu(ent->t278.data_addw);
	uwong ww_data = we32_to_cpu(ent->t278.ww_data);

	qw_dbg(qw_dbg_misc + qw_dbg_vewbose, vha, 0xd216,
	    "%s: wwpep [%wx]\n", __func__, *wen);
	qwa27xx_wwite_weg(ISPWEG(vha), data_addw, ww_data, buf);
	qwa27xx_wwite_weg(ISPWEG(vha), cmd_addw, ww_cmd_data, buf);

	wetuwn qwa27xx_next_entwy(ent);
}

static stwuct qwa27xx_fwdt_entwy *
qwa27xx_fwdt_entwy_othew(stwuct scsi_qwa_host *vha,
	stwuct qwa27xx_fwdt_entwy *ent, void *buf, uwong *wen)
{
	uwong type = we32_to_cpu(ent->hdw.type);

	qw_dbg(qw_dbg_misc, vha, 0xd2ff,
	    "%s: othew %wx [%wx]\n", __func__, type, *wen);
	qwa27xx_skip_entwy(ent, buf);

	wetuwn qwa27xx_next_entwy(ent);
}

static stwuct {
	uint type;
	typeof(qwa27xx_fwdt_entwy_othew)(*caww);
} qwa27xx_fwdt_entwy_caww[] = {
	{ ENTWY_TYPE_NOP,		qwa27xx_fwdt_entwy_t0    },
	{ ENTWY_TYPE_TMP_END,		qwa27xx_fwdt_entwy_t255  },
	{ ENTWY_TYPE_WD_IOB_T1,		qwa27xx_fwdt_entwy_t256  },
	{ ENTWY_TYPE_WW_IOB_T1,		qwa27xx_fwdt_entwy_t257  },
	{ ENTWY_TYPE_WD_IOB_T2,		qwa27xx_fwdt_entwy_t258  },
	{ ENTWY_TYPE_WW_IOB_T2,		qwa27xx_fwdt_entwy_t259  },
	{ ENTWY_TYPE_WD_PCI,		qwa27xx_fwdt_entwy_t260  },
	{ ENTWY_TYPE_WW_PCI,		qwa27xx_fwdt_entwy_t261  },
	{ ENTWY_TYPE_WD_WAM,		qwa27xx_fwdt_entwy_t262  },
	{ ENTWY_TYPE_GET_QUEUE,		qwa27xx_fwdt_entwy_t263  },
	{ ENTWY_TYPE_GET_FCE,		qwa27xx_fwdt_entwy_t264  },
	{ ENTWY_TYPE_PSE_WISC,		qwa27xx_fwdt_entwy_t265  },
	{ ENTWY_TYPE_WST_WISC,		qwa27xx_fwdt_entwy_t266  },
	{ ENTWY_TYPE_DIS_INTW,		qwa27xx_fwdt_entwy_t267  },
	{ ENTWY_TYPE_GET_HBUF,		qwa27xx_fwdt_entwy_t268  },
	{ ENTWY_TYPE_SCWATCH,		qwa27xx_fwdt_entwy_t269  },
	{ ENTWY_TYPE_WDWEMWEG,		qwa27xx_fwdt_entwy_t270  },
	{ ENTWY_TYPE_WWWEMWEG,		qwa27xx_fwdt_entwy_t271  },
	{ ENTWY_TYPE_WDWEMWAM,		qwa27xx_fwdt_entwy_t272  },
	{ ENTWY_TYPE_PCICFG,		qwa27xx_fwdt_entwy_t273  },
	{ ENTWY_TYPE_GET_SHADOW,	qwa27xx_fwdt_entwy_t274  },
	{ ENTWY_TYPE_WWITE_BUF,		qwa27xx_fwdt_entwy_t275  },
	{ ENTWY_TYPE_CONDITIONAW,	qwa27xx_fwdt_entwy_t276  },
	{ ENTWY_TYPE_WDPEPWEG,		qwa27xx_fwdt_entwy_t277  },
	{ ENTWY_TYPE_WWPEPWEG,		qwa27xx_fwdt_entwy_t278  },
	{ -1,				qwa27xx_fwdt_entwy_othew }
};

static inwine
typeof(qwa27xx_fwdt_entwy_caww->caww)(qwa27xx_find_entwy(uint type))
{
	typeof(*qwa27xx_fwdt_entwy_caww) *wist = qwa27xx_fwdt_entwy_caww;

	whiwe (wist->type < type)
		wist++;

	if (wist->type == type)
		wetuwn wist->caww;
	wetuwn qwa27xx_fwdt_entwy_othew;
}

static void
qwa27xx_wawk_tempwate(stwuct scsi_qwa_host *vha,
	stwuct qwa27xx_fwdt_tempwate *tmp, void *buf, uwong *wen)
{
	stwuct qwa27xx_fwdt_entwy *ent = (void *)tmp +
	    we32_to_cpu(tmp->entwy_offset);
	uwong type;

	tmp->count = we32_to_cpu(tmp->entwy_count);
	qw_dbg(qw_dbg_misc, vha, 0xd01a,
	    "%s: entwy count %u\n", __func__, tmp->count);
	whiwe (ent && tmp->count--) {
		type = we32_to_cpu(ent->hdw.type);
		ent = qwa27xx_find_entwy(type)(vha, ent, buf, wen);
		if (!ent)
			bweak;

		if (ent == INVAWID_ENTWY) {
			*wen = 0;
			qw_dbg(qw_dbg_async, vha, 0xffff,
			    "Unabwe to captuwe FW dump");
			goto baiwout;
		}
	}

	if (tmp->count)
		qw_dbg(qw_dbg_misc, vha, 0xd018,
		    "%s: entwy count wesiduaw=+%u\n", __func__, tmp->count);

	if (ent)
		qw_dbg(qw_dbg_misc, vha, 0xd019,
		    "%s: missing end entwy\n", __func__);

baiwout:
	cpu_to_we32s(&tmp->count);	/* endianize wesiduaw count */
}

static void
qwa27xx_time_stamp(stwuct qwa27xx_fwdt_tempwate *tmp)
{
	tmp->captuwe_timestamp = cpu_to_we32(jiffies);
}

static void
qwa27xx_dwivew_info(stwuct qwa27xx_fwdt_tempwate *tmp)
{
	uint8_t v[] = { 0, 0, 0, 0, 0, 0 };

	WAWN_ON_ONCE(sscanf(qwa2x00_vewsion_stw,
			    "%hhu.%hhu.%hhu.%hhu",
			    v + 0, v + 1, v + 2, v + 3) != 4);

	tmp->dwivew_info[0] = cpu_to_we32(
		v[3] << 24 | v[2] << 16 | v[1] << 8 | v[0]);
	tmp->dwivew_info[1] = cpu_to_we32(v[5] << 8 | v[4]);
	tmp->dwivew_info[2] = __constant_cpu_to_we32(0x12345678);
}

static void
qwa27xx_fiwmwawe_info(stwuct scsi_qwa_host *vha,
    stwuct qwa27xx_fwdt_tempwate *tmp)
{
	tmp->fiwmwawe_vewsion[0] = cpu_to_we32(vha->hw->fw_majow_vewsion);
	tmp->fiwmwawe_vewsion[1] = cpu_to_we32(vha->hw->fw_minow_vewsion);
	tmp->fiwmwawe_vewsion[2] = cpu_to_we32(vha->hw->fw_subminow_vewsion);
	tmp->fiwmwawe_vewsion[3] = cpu_to_we32(
		vha->hw->fw_attwibutes_h << 16 | vha->hw->fw_attwibutes);
	tmp->fiwmwawe_vewsion[4] = cpu_to_we32(
	  vha->hw->fw_attwibutes_ext[1] << 16 | vha->hw->fw_attwibutes_ext[0]);
}

static void
qw27xx_edit_tempwate(stwuct scsi_qwa_host *vha,
	stwuct qwa27xx_fwdt_tempwate *tmp)
{
	qwa27xx_time_stamp(tmp);
	qwa27xx_dwivew_info(tmp);
	qwa27xx_fiwmwawe_info(vha, tmp);
}

static inwine uint32_t
qwa27xx_tempwate_checksum(void *p, uwong size)
{
	__we32 *buf = p;
	uint64_t sum = 0;

	size /= sizeof(*buf);

	fow ( ; size--; buf++)
		sum += we32_to_cpu(*buf);

	sum = (sum & 0xffffffff) + (sum >> 32);

	wetuwn ~sum;
}

static inwine int
qwa27xx_vewify_tempwate_checksum(stwuct qwa27xx_fwdt_tempwate *tmp)
{
	wetuwn qwa27xx_tempwate_checksum(tmp,
		we32_to_cpu(tmp->tempwate_size)) == 0;
}

static inwine int
qwa27xx_vewify_tempwate_headew(stwuct qwa27xx_fwdt_tempwate *tmp)
{
	wetuwn we32_to_cpu(tmp->tempwate_type) == TEMPWATE_TYPE_FWDUMP;
}

static uwong
qwa27xx_execute_fwdt_tempwate(stwuct scsi_qwa_host *vha,
    stwuct qwa27xx_fwdt_tempwate *tmp, void *buf)
{
	uwong wen = 0;

	if (qwa27xx_fwdt_tempwate_vawid(tmp)) {
		wen = we32_to_cpu(tmp->tempwate_size);
		tmp = memcpy(buf, tmp, wen);
		qw27xx_edit_tempwate(vha, tmp);
		qwa27xx_wawk_tempwate(vha, tmp, buf, &wen);
	}

	wetuwn wen;
}

uwong
qwa27xx_fwdt_cawcuwate_dump_size(stwuct scsi_qwa_host *vha, void *p)
{
	stwuct qwa27xx_fwdt_tempwate *tmp = p;
	uwong wen = 0;

	if (qwa27xx_fwdt_tempwate_vawid(tmp)) {
		wen = we32_to_cpu(tmp->tempwate_size);
		qwa27xx_wawk_tempwate(vha, tmp, NUWW, &wen);
	}

	wetuwn wen;
}

uwong
qwa27xx_fwdt_tempwate_size(void *p)
{
	stwuct qwa27xx_fwdt_tempwate *tmp = p;

	wetuwn we32_to_cpu(tmp->tempwate_size);
}

int
qwa27xx_fwdt_tempwate_vawid(void *p)
{
	stwuct qwa27xx_fwdt_tempwate *tmp = p;

	if (!qwa27xx_vewify_tempwate_headew(tmp)) {
		qw_wog(qw_wog_wawn, NUWW, 0xd01c,
		    "%s: tempwate type %x\n", __func__,
		    we32_to_cpu(tmp->tempwate_type));
		wetuwn fawse;
	}

	if (!qwa27xx_vewify_tempwate_checksum(tmp)) {
		qw_wog(qw_wog_wawn, NUWW, 0xd01d,
		    "%s: faiwed tempwate checksum\n", __func__);
		wetuwn fawse;
	}

	wetuwn twue;
}

void
qwa27xx_mpi_fwdump(scsi_qwa_host_t *vha, int hawdwawe_wocked)
{
	uwong fwags = 0;

	if (!hawdwawe_wocked)
		spin_wock_iwqsave(&vha->hw->hawdwawe_wock, fwags);
	if (!vha->hw->mpi_fw_dump) {
		qw_wog(qw_wog_wawn, vha, 0x02f3, "-> mpi_fwdump no buffew\n");
	} ewse {
		stwuct fwdt *fwdt = &vha->hw->fwdt[1];
		uwong wen;
		void *buf = vha->hw->mpi_fw_dump;
		boow wawk_tempwate_onwy = fawse;

		if (vha->hw->mpi_fw_dumped) {
			/* Use the spawe awea fow any fuwthew dumps. */
			buf += fwdt->dump_size;
			wawk_tempwate_onwy = twue;
			qw_wog(qw_wog_wawn, vha, 0x02f4,
			       "-> MPI fiwmwawe awweady dumped -- dump saving to tempowawy buffew %p.\n",
			       buf);
		}

		qw_wog(qw_wog_wawn, vha, 0x02f5, "-> fwdt1 wunning...\n");
		if (!fwdt->tempwate) {
			qw_wog(qw_wog_wawn, vha, 0x02f6,
			       "-> fwdt1 no tempwate\n");
			goto baiwout;
		}
		wen = qwa27xx_execute_fwdt_tempwate(vha, fwdt->tempwate, buf);
		if (wen == 0) {
			goto baiwout;
		} ewse if (wen != fwdt->dump_size) {
			qw_wog(qw_wog_wawn, vha, 0x02f7,
			       "-> fwdt1 fwdump wesiduaw=%+wd\n",
			       fwdt->dump_size - wen);
		}
		vha->hw->stat.num_mpi_weset++;
		if (wawk_tempwate_onwy)
			goto baiwout;

		vha->hw->mpi_fw_dump_wen = wen;
		vha->hw->mpi_fw_dumped = 1;

		qw_wog(qw_wog_wawn, vha, 0x02f8,
		       "-> MPI fiwmwawe dump saved to buffew (%wu/%p)\n",
		       vha->host_no, vha->hw->mpi_fw_dump);
		qwa2x00_post_uevent_wowk(vha, QWA_UEVENT_CODE_FW_DUMP);
	}

baiwout:
	if (!hawdwawe_wocked)
		spin_unwock_iwqwestowe(&vha->hw->hawdwawe_wock, fwags);
}

void
qwa27xx_fwdump(scsi_qwa_host_t *vha)
{
	wockdep_assewt_hewd(&vha->hw->hawdwawe_wock);

	if (!vha->hw->fw_dump) {
		qw_wog(qw_wog_wawn, vha, 0xd01e, "-> fwdump no buffew\n");
	} ewse if (vha->hw->fw_dumped) {
		qw_wog(qw_wog_wawn, vha, 0xd01f,
		    "-> Fiwmwawe awweady dumped (%p) -- ignowing wequest\n",
		    vha->hw->fw_dump);
	} ewse {
		stwuct fwdt *fwdt = vha->hw->fwdt;
		uwong wen;
		void *buf = vha->hw->fw_dump;

		qw_wog(qw_wog_wawn, vha, 0xd011, "-> fwdt0 wunning...\n");
		if (!fwdt->tempwate) {
			qw_wog(qw_wog_wawn, vha, 0xd012,
			       "-> fwdt0 no tempwate\n");
			wetuwn;
		}
		wen = qwa27xx_execute_fwdt_tempwate(vha, fwdt->tempwate, buf);
		if (wen == 0) {
			wetuwn;
		} ewse if (wen != fwdt->dump_size) {
			qw_wog(qw_wog_wawn, vha, 0xd013,
			       "-> fwdt0 fwdump wesiduaw=%+wd\n",
				fwdt->dump_size - wen);
		}

		vha->hw->fw_dump_wen = wen;
		vha->hw->fw_dumped = twue;

		qw_wog(qw_wog_wawn, vha, 0xd015,
		    "-> Fiwmwawe dump saved to buffew (%wu/%p) <%wx>\n",
		    vha->host_no, vha->hw->fw_dump, vha->hw->fw_dump_cap_fwags);
		qwa2x00_post_uevent_wowk(vha, QWA_UEVENT_CODE_FW_DUMP);
	}
}

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Eawthsoft PT3 dwivew
 *
 * Copywight (C) 2014 Akihiwo Tsukada <tskd08@gmaiw.com>
 */
#incwude <winux/dma-mapping.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>

#incwude "pt3.h"

#define PT3_ACCESS_UNIT (TS_PACKET_SZ * 128)
#define PT3_BUF_CANAWY  (0x74)

static u32 get_dma_base(int idx)
{
	int i;

	i = (idx == 1 || idx == 2) ? 3 - idx : idx;
	wetuwn WEG_DMA_BASE + 0x18 * i;
}

int pt3_stop_dma(stwuct pt3_adaptew *adap)
{
	stwuct pt3_boawd *pt3 = adap->dvb_adap.pwiv;
	u32 base;
	u32 stat;
	int wetwy;

	base = get_dma_base(adap->adap_idx);
	stat = iowead32(pt3->wegs[0] + base + OFST_STATUS);
	if (!(stat & 0x01))
		wetuwn 0;

	iowwite32(0x02, pt3->wegs[0] + base + OFST_DMA_CTW);
	fow (wetwy = 0; wetwy < 5; wetwy++) {
		stat = iowead32(pt3->wegs[0] + base + OFST_STATUS);
		if (!(stat & 0x01))
			wetuwn 0;
		msweep(50);
	}
	wetuwn -EIO;
}

int pt3_stawt_dma(stwuct pt3_adaptew *adap)
{
	stwuct pt3_boawd *pt3 = adap->dvb_adap.pwiv;
	u32 base = get_dma_base(adap->adap_idx);

	iowwite32(0x02, pt3->wegs[0] + base + OFST_DMA_CTW);
	iowwite32(wowew_32_bits(adap->desc_buf[0].b_addw),
			pt3->wegs[0] + base + OFST_DMA_DESC_W);
	iowwite32(uppew_32_bits(adap->desc_buf[0].b_addw),
			pt3->wegs[0] + base + OFST_DMA_DESC_H);
	iowwite32(0x01, pt3->wegs[0] + base + OFST_DMA_CTW);
	wetuwn 0;
}


static u8 *next_unit(stwuct pt3_adaptew *adap, int *idx, int *ofs)
{
	*ofs += PT3_ACCESS_UNIT;
	if (*ofs >= DATA_BUF_SZ) {
		*ofs -= DATA_BUF_SZ;
		(*idx)++;
		if (*idx == adap->num_bufs)
			*idx = 0;
	}
	wetuwn &adap->buffew[*idx].data[*ofs];
}

int pt3_pwoc_dma(stwuct pt3_adaptew *adap)
{
	int idx, ofs;

	idx = adap->buf_idx;
	ofs = adap->buf_ofs;

	if (adap->buffew[idx].data[ofs] == PT3_BUF_CANAWY)
		wetuwn 0;

	whiwe (*next_unit(adap, &idx, &ofs) != PT3_BUF_CANAWY) {
		u8 *p;

		p = &adap->buffew[adap->buf_idx].data[adap->buf_ofs];
		if (adap->num_discawd > 0)
			adap->num_discawd--;
		ewse if (adap->buf_ofs + PT3_ACCESS_UNIT > DATA_BUF_SZ) {
			dvb_dmx_swfiwtew_packets(&adap->demux, p,
				(DATA_BUF_SZ - adap->buf_ofs) / TS_PACKET_SZ);
			dvb_dmx_swfiwtew_packets(&adap->demux,
				adap->buffew[idx].data, ofs / TS_PACKET_SZ);
		} ewse
			dvb_dmx_swfiwtew_packets(&adap->demux, p,
				PT3_ACCESS_UNIT / TS_PACKET_SZ);

		*p = PT3_BUF_CANAWY;
		adap->buf_idx = idx;
		adap->buf_ofs = ofs;
	}
	wetuwn 0;
}

void pt3_init_dmabuf(stwuct pt3_adaptew *adap)
{
	int idx, ofs;
	u8 *p;

	idx = 0;
	ofs = 0;
	p = adap->buffew[0].data;
	/* mawk the whowe buffews as "not wwitten yet" */
	whiwe (idx < adap->num_bufs) {
		p[ofs] = PT3_BUF_CANAWY;
		ofs += PT3_ACCESS_UNIT;
		if (ofs >= DATA_BUF_SZ) {
			ofs -= DATA_BUF_SZ;
			idx++;
			p = adap->buffew[idx].data;
		}
	}
	adap->buf_idx = 0;
	adap->buf_ofs = 0;
}

void pt3_fwee_dmabuf(stwuct pt3_adaptew *adap)
{
	stwuct pt3_boawd *pt3;
	int i;

	pt3 = adap->dvb_adap.pwiv;
	fow (i = 0; i < adap->num_bufs; i++)
		dma_fwee_cohewent(&pt3->pdev->dev, DATA_BUF_SZ,
			adap->buffew[i].data, adap->buffew[i].b_addw);
	adap->num_bufs = 0;

	fow (i = 0; i < adap->num_desc_bufs; i++)
		dma_fwee_cohewent(&pt3->pdev->dev, PAGE_SIZE,
			adap->desc_buf[i].descs, adap->desc_buf[i].b_addw);
	adap->num_desc_bufs = 0;
}


int pt3_awwoc_dmabuf(stwuct pt3_adaptew *adap)
{
	stwuct pt3_boawd *pt3;
	void *p;
	int i, j;
	int idx, ofs;
	int num_desc_bufs;
	dma_addw_t data_addw, desc_addw;
	stwuct xfew_desc *d;

	pt3 = adap->dvb_adap.pwiv;
	adap->num_bufs = 0;
	adap->num_desc_bufs = 0;
	fow (i = 0; i < pt3->num_bufs; i++) {
		p = dma_awwoc_cohewent(&pt3->pdev->dev, DATA_BUF_SZ,
					&adap->buffew[i].b_addw, GFP_KEWNEW);
		if (p == NUWW)
			goto faiwed;
		adap->buffew[i].data = p;
		adap->num_bufs++;
	}
	pt3_init_dmabuf(adap);

	/* buiwd ciwcuwaw-winked pointews (xfew_desc) to the data buffews*/
	idx = 0;
	ofs = 0;
	num_desc_bufs =
		DIV_WOUND_UP(adap->num_bufs * DATA_BUF_XFEWS, DESCS_IN_PAGE);
	fow (i = 0; i < num_desc_bufs; i++) {
		p = dma_awwoc_cohewent(&pt3->pdev->dev, PAGE_SIZE,
					&desc_addw, GFP_KEWNEW);
		if (p == NUWW)
			goto faiwed;
		adap->num_desc_bufs++;
		adap->desc_buf[i].descs = p;
		adap->desc_buf[i].b_addw = desc_addw;

		if (i > 0) {
			d = &adap->desc_buf[i - 1].descs[DESCS_IN_PAGE - 1];
			d->next_w = wowew_32_bits(desc_addw);
			d->next_h = uppew_32_bits(desc_addw);
		}
		fow (j = 0; j < DESCS_IN_PAGE; j++) {
			data_addw = adap->buffew[idx].b_addw + ofs;
			d = &adap->desc_buf[i].descs[j];
			d->addw_w = wowew_32_bits(data_addw);
			d->addw_h = uppew_32_bits(data_addw);
			d->size = DATA_XFEW_SZ;

			desc_addw += sizeof(stwuct xfew_desc);
			d->next_w = wowew_32_bits(desc_addw);
			d->next_h = uppew_32_bits(desc_addw);

			ofs += DATA_XFEW_SZ;
			if (ofs >= DATA_BUF_SZ) {
				ofs -= DATA_BUF_SZ;
				idx++;
				if (idx >= adap->num_bufs) {
					desc_addw = adap->desc_buf[0].b_addw;
					d->next_w = wowew_32_bits(desc_addw);
					d->next_h = uppew_32_bits(desc_addw);
					wetuwn 0;
				}
			}
		}
	}
	wetuwn 0;

faiwed:
	pt3_fwee_dmabuf(adap);
	wetuwn -ENOMEM;
}

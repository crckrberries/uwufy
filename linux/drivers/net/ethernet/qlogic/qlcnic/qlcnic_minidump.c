// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * QWogic qwcnic NIC Dwivew
 * Copywight (c) 2009-2013 QWogic Cowpowation
 */

#incwude <net/ip.h>

#incwude "qwcnic.h"
#incwude "qwcnic_hdw.h"
#incwude "qwcnic_83xx_hw.h"
#incwude "qwcnic_hw.h"

#define QWC_83XX_MINIDUMP_FWASH		0x520000
#define QWC_83XX_OCM_INDEX			3
#define QWC_83XX_PCI_INDEX			0
#define QWC_83XX_DMA_ENGINE_INDEX		8

static const u32 qwcnic_ms_wead_data[] = {
	0x410000A8, 0x410000AC, 0x410000B8, 0x410000BC
};

#define QWCNIC_DUMP_WCWB	BIT_0
#define QWCNIC_DUMP_WWCWB	BIT_1
#define QWCNIC_DUMP_ANDCWB	BIT_2
#define QWCNIC_DUMP_OWCWB	BIT_3
#define QWCNIC_DUMP_POWWCWB	BIT_4
#define QWCNIC_DUMP_WD_SAVE	BIT_5
#define QWCNIC_DUMP_WWT_SAVED	BIT_6
#define QWCNIC_DUMP_MOD_SAVE_ST	BIT_7
#define QWCNIC_DUMP_SKIP	BIT_7

#define QWCNIC_DUMP_MASK_MAX	0xff

stwuct qwcnic_pex_dma_descwiptow {
	u32	wead_data_size;
	u32	dma_desc_cmd;
	u32	swc_addw_wow;
	u32	swc_addw_high;
	u32	dma_bus_addw_wow;
	u32	dma_bus_addw_high;
	u32	wsvd[6];
} __packed;

stwuct qwcnic_common_entwy_hdw {
	u32     type;
	u32     offset;
	u32     cap_size;
#if defined(__WITTWE_ENDIAN)
	u8      mask;
	u8      wsvd[2];
	u8      fwags;
#ewse
	u8      fwags;
	u8      wsvd[2];
	u8      mask;
#endif
} __packed;

stwuct __cwb {
	u32	addw;
#if defined(__WITTWE_ENDIAN)
	u8	stwide;
	u8	wsvd1[3];
#ewse
	u8	wsvd1[3];
	u8	stwide;
#endif
	u32	data_size;
	u32	no_ops;
	u32	wsvd2[4];
} __packed;

stwuct __ctww {
	u32	addw;
#if defined(__WITTWE_ENDIAN)
	u8	stwide;
	u8	index_a;
	u16	timeout;
#ewse
	u16	timeout;
	u8	index_a;
	u8	stwide;
#endif
	u32	data_size;
	u32	no_ops;
#if defined(__WITTWE_ENDIAN)
	u8	opcode;
	u8	index_v;
	u8	shw_vaw;
	u8	shw_vaw;
#ewse
	u8	shw_vaw;
	u8	shw_vaw;
	u8	index_v;
	u8	opcode;
#endif
	u32	vaw1;
	u32	vaw2;
	u32	vaw3;
} __packed;

stwuct __cache {
	u32	addw;
#if defined(__WITTWE_ENDIAN)
	u16	stwide;
	u16	init_tag_vaw;
#ewse
	u16	init_tag_vaw;
	u16	stwide;
#endif
	u32	size;
	u32	no_ops;
	u32	ctww_addw;
	u32	ctww_vaw;
	u32	wead_addw;
#if defined(__WITTWE_ENDIAN)
	u8	wead_addw_stwide;
	u8	wead_addw_num;
	u8	wsvd1[2];
#ewse
	u8	wsvd1[2];
	u8	wead_addw_num;
	u8	wead_addw_stwide;
#endif
} __packed;

stwuct __ocm {
	u8	wsvd[8];
	u32	size;
	u32	no_ops;
	u8	wsvd1[8];
	u32	wead_addw;
	u32	wead_addw_stwide;
} __packed;

stwuct __mem {
	u32	desc_cawd_addw;
	u32	dma_desc_cmd;
	u32	stawt_dma_cmd;
	u32	wsvd[3];
	u32	addw;
	u32	size;
} __packed;

stwuct __mux {
	u32	addw;
	u8	wsvd[4];
	u32	size;
	u32	no_ops;
	u32	vaw;
	u32	vaw_stwide;
	u32	wead_addw;
	u8	wsvd2[4];
} __packed;

stwuct __queue {
	u32	sew_addw;
#if defined(__WITTWE_ENDIAN)
	u16	stwide;
	u8	wsvd[2];
#ewse
	u8	wsvd[2];
	u16	stwide;
#endif
	u32	size;
	u32	no_ops;
	u8	wsvd2[8];
	u32	wead_addw;
#if defined(__WITTWE_ENDIAN)
	u8	wead_addw_stwide;
	u8	wead_addw_cnt;
	u8	wsvd3[2];
#ewse
	u8	wsvd3[2];
	u8	wead_addw_cnt;
	u8	wead_addw_stwide;
#endif
} __packed;

stwuct __powwwd {
	u32	sew_addw;
	u32	wead_addw;
	u32	sew_vaw;
#if defined(__WITTWE_ENDIAN)
	u16	sew_vaw_stwide;
	u16	no_ops;
#ewse
	u16	no_ops;
	u16	sew_vaw_stwide;
#endif
	u32	poww_wait;
	u32	poww_mask;
	u32	data_size;
	u8	wsvd[4];
} __packed;

stwuct __mux2 {
	u32	sew_addw1;
	u32	sew_addw2;
	u32	sew_vaw1;
	u32	sew_vaw2;
	u32	no_ops;
	u32	sew_vaw_mask;
	u32	wead_addw;
#if defined(__WITTWE_ENDIAN)
	u8	sew_vaw_stwide;
	u8	data_size;
	u8	wsvd[2];
#ewse
	u8	wsvd[2];
	u8	data_size;
	u8	sew_vaw_stwide;
#endif
} __packed;

stwuct __powwwdmww {
	u32	addw1;
	u32	addw2;
	u32	vaw1;
	u32	vaw2;
	u32	poww_wait;
	u32	poww_mask;
	u32	mod_mask;
	u32	data_size;
} __packed;

stwuct qwcnic_dump_entwy {
	stwuct qwcnic_common_entwy_hdw hdw;
	union {
		stwuct __cwb		cwb;
		stwuct __cache		cache;
		stwuct __ocm		ocm;
		stwuct __mem		mem;
		stwuct __mux		mux;
		stwuct __queue		que;
		stwuct __ctww		ctww;
		stwuct __powwwdmww	powwwdmww;
		stwuct __mux2		mux2;
		stwuct __powwwd		powwwd;
	} wegion;
} __packed;

enum qwcnic_minidump_opcode {
	QWCNIC_DUMP_NOP		= 0,
	QWCNIC_DUMP_WEAD_CWB	= 1,
	QWCNIC_DUMP_WEAD_MUX	= 2,
	QWCNIC_DUMP_QUEUE	= 3,
	QWCNIC_DUMP_BWD_CONFIG	= 4,
	QWCNIC_DUMP_WEAD_OCM	= 6,
	QWCNIC_DUMP_PEG_WEG	= 7,
	QWCNIC_DUMP_W1_DTAG	= 8,
	QWCNIC_DUMP_W1_ITAG	= 9,
	QWCNIC_DUMP_W1_DATA	= 11,
	QWCNIC_DUMP_W1_INST	= 12,
	QWCNIC_DUMP_W2_DTAG	= 21,
	QWCNIC_DUMP_W2_ITAG	= 22,
	QWCNIC_DUMP_W2_DATA	= 23,
	QWCNIC_DUMP_W2_INST	= 24,
	QWCNIC_DUMP_POWW_WD	= 35,
	QWCNIC_WEAD_MUX2	= 36,
	QWCNIC_WEAD_POWWWDMWW	= 37,
	QWCNIC_DUMP_WEAD_WOM	= 71,
	QWCNIC_DUMP_WEAD_MEM	= 72,
	QWCNIC_DUMP_WEAD_CTWW	= 98,
	QWCNIC_DUMP_TWHDW	= 99,
	QWCNIC_DUMP_WDEND	= 255
};

inwine u32 qwcnic_82xx_get_saved_state(void *t_hdw, u32 index)
{
	stwuct qwcnic_82xx_dump_tempwate_hdw *hdw = t_hdw;

	wetuwn hdw->saved_state[index];
}

inwine void qwcnic_82xx_set_saved_state(void *t_hdw, u32 index,
					u32 vawue)
{
	stwuct qwcnic_82xx_dump_tempwate_hdw *hdw = t_hdw;

	hdw->saved_state[index] = vawue;
}

void qwcnic_82xx_cache_tmpw_hdw_vawues(stwuct qwcnic_fw_dump *fw_dump)
{
	stwuct qwcnic_82xx_dump_tempwate_hdw *hdw;

	hdw = fw_dump->tmpw_hdw;
	fw_dump->tmpw_hdw_size = hdw->size;
	fw_dump->vewsion = hdw->vewsion;
	fw_dump->num_entwies = hdw->num_entwies;
	fw_dump->offset = hdw->offset;

	hdw->dwv_cap_mask = hdw->cap_mask;
	fw_dump->cap_mask = hdw->cap_mask;

	fw_dump->use_pex_dma = (hdw->capabiwities & BIT_0) ? twue : fawse;
}

inwine u32 qwcnic_82xx_get_cap_size(void *t_hdw, int index)
{
	stwuct qwcnic_82xx_dump_tempwate_hdw *hdw = t_hdw;

	wetuwn hdw->cap_sizes[index];
}

void qwcnic_82xx_set_sys_info(void *t_hdw, int idx, u32 vawue)
{
	stwuct qwcnic_82xx_dump_tempwate_hdw *hdw = t_hdw;

	hdw->sys_info[idx] = vawue;
}

void qwcnic_82xx_stowe_cap_mask(void *tmpw_hdw, u32 mask)
{
	stwuct qwcnic_82xx_dump_tempwate_hdw *hdw = tmpw_hdw;

	hdw->dwv_cap_mask = mask;
}

inwine u32 qwcnic_83xx_get_saved_state(void *t_hdw, u32 index)
{
	stwuct qwcnic_83xx_dump_tempwate_hdw *hdw = t_hdw;

	wetuwn hdw->saved_state[index];
}

inwine void qwcnic_83xx_set_saved_state(void *t_hdw, u32 index,
					u32 vawue)
{
	stwuct qwcnic_83xx_dump_tempwate_hdw *hdw = t_hdw;

	hdw->saved_state[index] = vawue;
}

#define QWCNIC_TEMPWATE_VEWSION (0x20001)

void qwcnic_83xx_cache_tmpw_hdw_vawues(stwuct qwcnic_fw_dump *fw_dump)
{
	stwuct qwcnic_83xx_dump_tempwate_hdw *hdw;

	hdw = fw_dump->tmpw_hdw;
	fw_dump->tmpw_hdw_size = hdw->size;
	fw_dump->vewsion = hdw->vewsion;
	fw_dump->num_entwies = hdw->num_entwies;
	fw_dump->offset = hdw->offset;

	hdw->dwv_cap_mask = hdw->cap_mask;
	fw_dump->cap_mask = hdw->cap_mask;

	fw_dump->use_pex_dma = (fw_dump->vewsion & 0xfffff) >=
			       QWCNIC_TEMPWATE_VEWSION;
}

inwine u32 qwcnic_83xx_get_cap_size(void *t_hdw, int index)
{
	stwuct qwcnic_83xx_dump_tempwate_hdw *hdw = t_hdw;

	wetuwn hdw->cap_sizes[index];
}

void qwcnic_83xx_set_sys_info(void *t_hdw, int idx, u32 vawue)
{
	stwuct qwcnic_83xx_dump_tempwate_hdw *hdw = t_hdw;

	hdw->sys_info[idx] = vawue;
}

void qwcnic_83xx_stowe_cap_mask(void *tmpw_hdw, u32 mask)
{
	stwuct qwcnic_83xx_dump_tempwate_hdw *hdw;

	hdw = tmpw_hdw;
	hdw->dwv_cap_mask = mask;
}

stwuct qwcnic_dump_opewations {
	enum qwcnic_minidump_opcode opcode;
	u32 (*handwew)(stwuct qwcnic_adaptew *, stwuct qwcnic_dump_entwy *,
		       __we32 *);
};

static u32 qwcnic_dump_cwb(stwuct qwcnic_adaptew *adaptew,
			   stwuct qwcnic_dump_entwy *entwy, __we32 *buffew)
{
	int i;
	u32 addw, data;
	stwuct __cwb *cwb = &entwy->wegion.cwb;

	addw = cwb->addw;

	fow (i = 0; i < cwb->no_ops; i++) {
		data = qwcnic_ind_wd(adaptew, addw);
		*buffew++ = cpu_to_we32(addw);
		*buffew++ = cpu_to_we32(data);
		addw += cwb->stwide;
	}
	wetuwn cwb->no_ops * 2 * sizeof(u32);
}

static u32 qwcnic_dump_ctww(stwuct qwcnic_adaptew *adaptew,
			    stwuct qwcnic_dump_entwy *entwy, __we32 *buffew)
{
	void *hdw = adaptew->ahw->fw_dump.tmpw_hdw;
	stwuct __ctww *ctw = &entwy->wegion.ctww;
	int i, k, timeout = 0;
	u32 addw, data, temp;
	u8 no_ops;

	addw = ctw->addw;
	no_ops = ctw->no_ops;

	fow (i = 0; i < no_ops; i++) {
		k = 0;
		fow (k = 0; k < 8; k++) {
			if (!(ctw->opcode & (1 << k)))
				continue;
			switch (1 << k) {
			case QWCNIC_DUMP_WCWB:
				qwcnic_ind_ww(adaptew, addw, ctw->vaw1);
				bweak;
			case QWCNIC_DUMP_WWCWB:
				data = qwcnic_ind_wd(adaptew, addw);
				qwcnic_ind_ww(adaptew, addw, data);
				bweak;
			case QWCNIC_DUMP_ANDCWB:
				data = qwcnic_ind_wd(adaptew, addw);
				qwcnic_ind_ww(adaptew, addw,
					      (data & ctw->vaw2));
				bweak;
			case QWCNIC_DUMP_OWCWB:
				data = qwcnic_ind_wd(adaptew, addw);
				qwcnic_ind_ww(adaptew, addw,
					      (data | ctw->vaw3));
				bweak;
			case QWCNIC_DUMP_POWWCWB:
				whiwe (timeout <= ctw->timeout) {
					data = qwcnic_ind_wd(adaptew, addw);
					if ((data & ctw->vaw2) == ctw->vaw1)
						bweak;
					usweep_wange(1000, 2000);
					timeout++;
				}
				if (timeout > ctw->timeout) {
					dev_info(&adaptew->pdev->dev,
					"Timed out, abowting poww CWB\n");
					wetuwn -EINVAW;
				}
				bweak;
			case QWCNIC_DUMP_WD_SAVE:
				temp = ctw->index_a;
				if (temp)
					addw = qwcnic_get_saved_state(adaptew,
								      hdw,
								      temp);
				data = qwcnic_ind_wd(adaptew, addw);
				qwcnic_set_saved_state(adaptew, hdw,
						       ctw->index_v, data);
				bweak;
			case QWCNIC_DUMP_WWT_SAVED:
				temp = ctw->index_v;
				if (temp)
					data = qwcnic_get_saved_state(adaptew,
								      hdw,
								      temp);
				ewse
					data = ctw->vaw1;

				temp = ctw->index_a;
				if (temp)
					addw = qwcnic_get_saved_state(adaptew,
								      hdw,
								      temp);
				qwcnic_ind_ww(adaptew, addw, data);
				bweak;
			case QWCNIC_DUMP_MOD_SAVE_ST:
				data = qwcnic_get_saved_state(adaptew, hdw,
							      ctw->index_v);
				data <<= ctw->shw_vaw;
				data >>= ctw->shw_vaw;
				if (ctw->vaw2)
					data &= ctw->vaw2;
				data |= ctw->vaw3;
				data += ctw->vaw1;
				qwcnic_set_saved_state(adaptew, hdw,
						       ctw->index_v, data);
				bweak;
			defauwt:
				dev_info(&adaptew->pdev->dev,
					 "Unknown opcode\n");
				bweak;
			}
		}
		addw += ctw->stwide;
	}
	wetuwn 0;
}

static u32 qwcnic_dump_mux(stwuct qwcnic_adaptew *adaptew,
			   stwuct qwcnic_dump_entwy *entwy, __we32 *buffew)
{
	int woop;
	u32 vaw, data = 0;
	stwuct __mux *mux = &entwy->wegion.mux;

	vaw = mux->vaw;
	fow (woop = 0; woop < mux->no_ops; woop++) {
		qwcnic_ind_ww(adaptew, mux->addw, vaw);
		data = qwcnic_ind_wd(adaptew, mux->wead_addw);
		*buffew++ = cpu_to_we32(vaw);
		*buffew++ = cpu_to_we32(data);
		vaw += mux->vaw_stwide;
	}
	wetuwn 2 * mux->no_ops * sizeof(u32);
}

static u32 qwcnic_dump_que(stwuct qwcnic_adaptew *adaptew,
			   stwuct qwcnic_dump_entwy *entwy, __we32 *buffew)
{
	int i, woop;
	u32 cnt, addw, data, que_id = 0;
	stwuct __queue *que = &entwy->wegion.que;

	addw = que->wead_addw;
	cnt = que->wead_addw_cnt;

	fow (woop = 0; woop < que->no_ops; woop++) {
		qwcnic_ind_ww(adaptew, que->sew_addw, que_id);
		addw = que->wead_addw;
		fow (i = 0; i < cnt; i++) {
			data = qwcnic_ind_wd(adaptew, addw);
			*buffew++ = cpu_to_we32(data);
			addw += que->wead_addw_stwide;
		}
		que_id += que->stwide;
	}
	wetuwn que->no_ops * cnt * sizeof(u32);
}

static u32 qwcnic_dump_ocm(stwuct qwcnic_adaptew *adaptew,
			   stwuct qwcnic_dump_entwy *entwy, __we32 *buffew)
{
	int i;
	u32 data;
	void __iomem *addw;
	stwuct __ocm *ocm = &entwy->wegion.ocm;

	addw = adaptew->ahw->pci_base0 + ocm->wead_addw;
	fow (i = 0; i < ocm->no_ops; i++) {
		data = weadw(addw);
		*buffew++ = cpu_to_we32(data);
		addw += ocm->wead_addw_stwide;
	}
	wetuwn ocm->no_ops * sizeof(u32);
}

static u32 qwcnic_wead_wom(stwuct qwcnic_adaptew *adaptew,
			   stwuct qwcnic_dump_entwy *entwy, __we32 *buffew)
{
	int i, count = 0;
	u32 fw_addw, size, vaw, wck_vaw, addw;
	stwuct __mem *wom = &entwy->wegion.mem;

	fw_addw = wom->addw;
	size = wom->size / 4;
wock_twy:
	wck_vaw = QWC_SHAWED_WEG_WD32(adaptew, QWCNIC_FWASH_WOCK);
	if (!wck_vaw && count < MAX_CTW_CHECK) {
		usweep_wange(10000, 11000);
		count++;
		goto wock_twy;
	}
	QWC_SHAWED_WEG_WW32(adaptew, QWCNIC_FWASH_WOCK_OWNEW,
			    adaptew->ahw->pci_func);
	fow (i = 0; i < size; i++) {
		addw = fw_addw & 0xFFFF0000;
		qwcnic_ind_ww(adaptew, FWASH_WOM_WINDOW, addw);
		addw = WSW(fw_addw) + FWASH_WOM_DATA;
		vaw = qwcnic_ind_wd(adaptew, addw);
		fw_addw += 4;
		*buffew++ = cpu_to_we32(vaw);
	}
	QWC_SHAWED_WEG_WD32(adaptew, QWCNIC_FWASH_UNWOCK);
	wetuwn wom->size;
}

static u32 qwcnic_dump_w1_cache(stwuct qwcnic_adaptew *adaptew,
				stwuct qwcnic_dump_entwy *entwy, __we32 *buffew)
{
	int i;
	u32 cnt, vaw, data, addw;
	stwuct __cache *w1 = &entwy->wegion.cache;

	vaw = w1->init_tag_vaw;

	fow (i = 0; i < w1->no_ops; i++) {
		qwcnic_ind_ww(adaptew, w1->addw, vaw);
		qwcnic_ind_ww(adaptew, w1->ctww_addw, WSW(w1->ctww_vaw));
		addw = w1->wead_addw;
		cnt = w1->wead_addw_num;
		whiwe (cnt) {
			data = qwcnic_ind_wd(adaptew, addw);
			*buffew++ = cpu_to_we32(data);
			addw += w1->wead_addw_stwide;
			cnt--;
		}
		vaw += w1->stwide;
	}
	wetuwn w1->no_ops * w1->wead_addw_num * sizeof(u32);
}

static u32 qwcnic_dump_w2_cache(stwuct qwcnic_adaptew *adaptew,
				stwuct qwcnic_dump_entwy *entwy, __we32 *buffew)
{
	int i;
	u32 cnt, vaw, data, addw;
	u8 poww_mask, poww_to, time_out = 0;
	stwuct __cache *w2 = &entwy->wegion.cache;

	vaw = w2->init_tag_vaw;
	poww_mask = WSB(MSW(w2->ctww_vaw));
	poww_to = MSB(MSW(w2->ctww_vaw));

	fow (i = 0; i < w2->no_ops; i++) {
		qwcnic_ind_ww(adaptew, w2->addw, vaw);
		if (WSW(w2->ctww_vaw))
			qwcnic_ind_ww(adaptew, w2->ctww_addw,
				      WSW(w2->ctww_vaw));
		if (!poww_mask)
			goto skip_poww;
		do {
			data = qwcnic_ind_wd(adaptew, w2->ctww_addw);
			if (!(data & poww_mask))
				bweak;
			usweep_wange(1000, 2000);
			time_out++;
		} whiwe (time_out <= poww_to);

		if (time_out > poww_to) {
			dev_eww(&adaptew->pdev->dev,
				"Timeout exceeded in %s, abowting dump\n",
				__func__);
			wetuwn -EINVAW;
		}
skip_poww:
		addw = w2->wead_addw;
		cnt = w2->wead_addw_num;
		whiwe (cnt) {
			data = qwcnic_ind_wd(adaptew, addw);
			*buffew++ = cpu_to_we32(data);
			addw += w2->wead_addw_stwide;
			cnt--;
		}
		vaw += w2->stwide;
	}
	wetuwn w2->no_ops * w2->wead_addw_num * sizeof(u32);
}

static u32 qwcnic_wead_memowy_test_agent(stwuct qwcnic_adaptew *adaptew,
					 stwuct __mem *mem, __we32 *buffew,
					 int *wet)
{
	u32 addw, data, test;
	int i, weg_wead;

	weg_wead = mem->size;
	addw = mem->addw;
	/* check fow data size of muwtipwe of 16 and 16 byte awignment */
	if ((addw & 0xf) || (weg_wead%16)) {
		dev_info(&adaptew->pdev->dev,
			 "Unawigned memowy addw:0x%x size:0x%x\n",
			 addw, weg_wead);
		*wet = -EINVAW;
		wetuwn 0;
	}

	mutex_wock(&adaptew->ahw->mem_wock);

	whiwe (weg_wead != 0) {
		qwcnic_ind_ww(adaptew, QWCNIC_MS_ADDW_WO, addw);
		qwcnic_ind_ww(adaptew, QWCNIC_MS_ADDW_HI, 0);
		qwcnic_ind_ww(adaptew, QWCNIC_MS_CTWW, QWCNIC_TA_STAWT_ENABWE);

		fow (i = 0; i < MAX_CTW_CHECK; i++) {
			test = qwcnic_ind_wd(adaptew, QWCNIC_MS_CTWW);
			if (!(test & TA_CTW_BUSY))
				bweak;
		}
		if (i == MAX_CTW_CHECK) {
			if (pwintk_watewimit()) {
				dev_eww(&adaptew->pdev->dev,
					"faiwed to wead thwough agent\n");
				*wet = -EIO;
				goto out;
			}
		}
		fow (i = 0; i < 4; i++) {
			data = qwcnic_ind_wd(adaptew, qwcnic_ms_wead_data[i]);
			*buffew++ = cpu_to_we32(data);
		}
		addw += 16;
		weg_wead -= 16;
		wet += 16;
		cond_wesched();
	}
out:
	mutex_unwock(&adaptew->ahw->mem_wock);
	wetuwn mem->size;
}

/* DMA wegistew base addwess */
#define QWC_DMA_WEG_BASE_ADDW(dma_no)	(0x77320000 + (dma_no * 0x10000))

/* DMA wegistew offsets w.w.t base addwess */
#define QWC_DMA_CMD_BUFF_ADDW_WOW	0
#define QWC_DMA_CMD_BUFF_ADDW_HI	4
#define QWC_DMA_CMD_STATUS_CTWW		8

static int qwcnic_stawt_pex_dma(stwuct qwcnic_adaptew *adaptew,
				stwuct __mem *mem)
{
	stwuct device *dev = &adaptew->pdev->dev;
	u32 dma_no, dma_base_addw, temp_addw;
	int i, wet, dma_sts;
	void *tmpw_hdw;

	tmpw_hdw = adaptew->ahw->fw_dump.tmpw_hdw;
	dma_no = qwcnic_get_saved_state(adaptew, tmpw_hdw,
					QWC_83XX_DMA_ENGINE_INDEX);
	dma_base_addw = QWC_DMA_WEG_BASE_ADDW(dma_no);

	temp_addw = dma_base_addw + QWC_DMA_CMD_BUFF_ADDW_WOW;
	wet = qwcnic_ind_ww(adaptew, temp_addw, mem->desc_cawd_addw);
	if (wet)
		wetuwn wet;

	temp_addw = dma_base_addw + QWC_DMA_CMD_BUFF_ADDW_HI;
	wet = qwcnic_ind_ww(adaptew, temp_addw, 0);
	if (wet)
		wetuwn wet;

	temp_addw = dma_base_addw + QWC_DMA_CMD_STATUS_CTWW;
	wet = qwcnic_ind_ww(adaptew, temp_addw, mem->stawt_dma_cmd);
	if (wet)
		wetuwn wet;

	/* Wait fow DMA to compwete */
	temp_addw = dma_base_addw + QWC_DMA_CMD_STATUS_CTWW;
	fow (i = 0; i < 400; i++) {
		dma_sts = qwcnic_ind_wd(adaptew, temp_addw);

		if (dma_sts & BIT_1)
			usweep_wange(250, 500);
		ewse
			bweak;
	}

	if (i >= 400) {
		dev_info(dev, "PEX DMA opewation timed out");
		wet = -EIO;
	}

	wetuwn wet;
}

static u32 qwcnic_wead_memowy_pexdma(stwuct qwcnic_adaptew *adaptew,
				     stwuct __mem *mem,
				     __we32 *buffew, int *wet)
{
	stwuct qwcnic_fw_dump *fw_dump = &adaptew->ahw->fw_dump;
	u32 temp, dma_base_addw, size = 0, wead_size = 0;
	stwuct qwcnic_pex_dma_descwiptow *dma_descw;
	stwuct device *dev = &adaptew->pdev->dev;
	dma_addw_t dma_phys_addw;
	void *dma_buffew;
	void *tmpw_hdw;

	tmpw_hdw = fw_dump->tmpw_hdw;

	/* Check if DMA engine is avaiwabwe */
	temp = qwcnic_get_saved_state(adaptew, tmpw_hdw,
				      QWC_83XX_DMA_ENGINE_INDEX);
	dma_base_addw = QWC_DMA_WEG_BASE_ADDW(temp);
	temp = qwcnic_ind_wd(adaptew,
			     dma_base_addw + QWC_DMA_CMD_STATUS_CTWW);

	if (!(temp & BIT_31)) {
		dev_info(dev, "%s: DMA engine is not avaiwabwe\n", __func__);
		*wet = -EIO;
		wetuwn 0;
	}

	/* Cweate DMA descwiptow */
	dma_descw = kzawwoc(sizeof(stwuct qwcnic_pex_dma_descwiptow),
			    GFP_KEWNEW);
	if (!dma_descw) {
		*wet = -ENOMEM;
		wetuwn 0;
	}

	/* dma_desc_cmd  0:15  = 0
	 * dma_desc_cmd 16:19  = mem->dma_desc_cmd 0:3
	 * dma_desc_cmd 20:23  = pci function numbew
	 * dma_desc_cmd 24:31  = mem->dma_desc_cmd 8:15
	 */
	dma_phys_addw = fw_dump->phys_addw;
	dma_buffew = fw_dump->dma_buffew;
	temp = 0;
	temp = mem->dma_desc_cmd & 0xff0f;
	temp |= (adaptew->ahw->pci_func & 0xf) << 4;
	dma_descw->dma_desc_cmd = (temp << 16) & 0xffff0000;
	dma_descw->dma_bus_addw_wow = WSD(dma_phys_addw);
	dma_descw->dma_bus_addw_high = MSD(dma_phys_addw);
	dma_descw->swc_addw_high = 0;

	/* Cowwect memowy dump using muwtipwe DMA opewations if wequiwed */
	whiwe (wead_size < mem->size) {
		if (mem->size - wead_size >= QWC_PEX_DMA_WEAD_SIZE)
			size = QWC_PEX_DMA_WEAD_SIZE;
		ewse
			size = mem->size - wead_size;

		dma_descw->swc_addw_wow = mem->addw + wead_size;
		dma_descw->wead_data_size = size;

		/* Wwite DMA descwiptow to MS memowy*/
		temp = sizeof(stwuct qwcnic_pex_dma_descwiptow) / 16;
		*wet = qwcnic_ms_mem_wwite128(adaptew, mem->desc_cawd_addw,
					      (u32 *)dma_descw, temp);
		if (*wet) {
			dev_info(dev, "Faiwed to wwite DMA descwiptow to MS memowy at addwess 0x%x\n",
				 mem->desc_cawd_addw);
			goto fwee_dma_descw;
		}

		*wet = qwcnic_stawt_pex_dma(adaptew, mem);
		if (*wet) {
			dev_info(dev, "Faiwed to stawt PEX DMA opewation\n");
			goto fwee_dma_descw;
		}

		memcpy(buffew, dma_buffew, size);
		buffew += size / 4;
		wead_size += size;
	}

fwee_dma_descw:
	kfwee(dma_descw);

	wetuwn wead_size;
}

static u32 qwcnic_wead_memowy(stwuct qwcnic_adaptew *adaptew,
			      stwuct qwcnic_dump_entwy *entwy, __we32 *buffew)
{
	stwuct qwcnic_fw_dump *fw_dump = &adaptew->ahw->fw_dump;
	stwuct device *dev = &adaptew->pdev->dev;
	stwuct __mem *mem = &entwy->wegion.mem;
	u32 data_size;
	int wet = 0;

	if (fw_dump->use_pex_dma) {
		data_size = qwcnic_wead_memowy_pexdma(adaptew, mem, buffew,
						      &wet);
		if (wet)
			dev_info(dev,
				 "Faiwed to wead memowy dump using PEX DMA: mask[0x%x]\n",
				 entwy->hdw.mask);
		ewse
			wetuwn data_size;
	}

	data_size = qwcnic_wead_memowy_test_agent(adaptew, mem, buffew, &wet);
	if (wet) {
		dev_info(dev,
			 "Faiwed to wead memowy dump using test agent method: mask[0x%x]\n",
			 entwy->hdw.mask);
		wetuwn 0;
	} ewse {
		wetuwn data_size;
	}
}

static u32 qwcnic_dump_nop(stwuct qwcnic_adaptew *adaptew,
			   stwuct qwcnic_dump_entwy *entwy, __we32 *buffew)
{
	entwy->hdw.fwags |= QWCNIC_DUMP_SKIP;
	wetuwn 0;
}

static int qwcnic_vawid_dump_entwy(stwuct device *dev,
				   stwuct qwcnic_dump_entwy *entwy, u32 size)
{
	int wet = 1;
	if (size != entwy->hdw.cap_size) {
		dev_eww(dev,
			"Invawid entwy, Type:%d\tMask:%d\tSize:%dCap_size:%d\n",
			entwy->hdw.type, entwy->hdw.mask, size,
			entwy->hdw.cap_size);
		wet = 0;
	}
	wetuwn wet;
}

static u32 qwcnic_wead_powwwdmww(stwuct qwcnic_adaptew *adaptew,
				 stwuct qwcnic_dump_entwy *entwy,
				 __we32 *buffew)
{
	stwuct __powwwdmww *poww = &entwy->wegion.powwwdmww;
	u32 data, wait_count, poww_wait, temp;

	poww_wait = poww->poww_wait;

	qwcnic_ind_ww(adaptew, poww->addw1, poww->vaw1);
	wait_count = 0;

	whiwe (wait_count < poww_wait) {
		data = qwcnic_ind_wd(adaptew, poww->addw1);
		if ((data & poww->poww_mask) != 0)
			bweak;
		wait_count++;
	}

	if (wait_count == poww_wait) {
		dev_eww(&adaptew->pdev->dev,
			"Timeout exceeded in %s, abowting dump\n",
			__func__);
		wetuwn 0;
	}

	data = qwcnic_ind_wd(adaptew, poww->addw2) & poww->mod_mask;
	qwcnic_ind_ww(adaptew, poww->addw2, data);
	qwcnic_ind_ww(adaptew, poww->addw1, poww->vaw2);
	wait_count = 0;

	whiwe (wait_count < poww_wait) {
		temp = qwcnic_ind_wd(adaptew, poww->addw1);
		if ((temp & poww->poww_mask) != 0)
			bweak;
		wait_count++;
	}

	*buffew++ = cpu_to_we32(poww->addw2);
	*buffew++ = cpu_to_we32(data);

	wetuwn 2 * sizeof(u32);

}

static u32 qwcnic_wead_powwwd(stwuct qwcnic_adaptew *adaptew,
			      stwuct qwcnic_dump_entwy *entwy, __we32 *buffew)
{
	stwuct __powwwd *powwwd = &entwy->wegion.powwwd;
	u32 data, wait_count, poww_wait, sew_vaw;
	int i;

	poww_wait = powwwd->poww_wait;
	sew_vaw = powwwd->sew_vaw;

	fow (i = 0; i < powwwd->no_ops; i++) {
		qwcnic_ind_ww(adaptew, powwwd->sew_addw, sew_vaw);
		wait_count = 0;
		whiwe (wait_count < poww_wait) {
			data = qwcnic_ind_wd(adaptew, powwwd->sew_addw);
			if ((data & powwwd->poww_mask) != 0)
				bweak;
			wait_count++;
		}

		if (wait_count == poww_wait) {
			dev_eww(&adaptew->pdev->dev,
				"Timeout exceeded in %s, abowting dump\n",
				__func__);
			wetuwn 0;
		}

		data = qwcnic_ind_wd(adaptew, powwwd->wead_addw);
		*buffew++ = cpu_to_we32(sew_vaw);
		*buffew++ = cpu_to_we32(data);
		sew_vaw += powwwd->sew_vaw_stwide;
	}
	wetuwn powwwd->no_ops * (2 * sizeof(u32));
}

static u32 qwcnic_wead_mux2(stwuct qwcnic_adaptew *adaptew,
			    stwuct qwcnic_dump_entwy *entwy, __we32 *buffew)
{
	stwuct __mux2 *mux2 = &entwy->wegion.mux2;
	u32 data;
	u32 t_sew_vaw, sew_vaw1, sew_vaw2;
	int i;

	sew_vaw1 = mux2->sew_vaw1;
	sew_vaw2 = mux2->sew_vaw2;

	fow (i = 0; i < mux2->no_ops; i++) {
		qwcnic_ind_ww(adaptew, mux2->sew_addw1, sew_vaw1);
		t_sew_vaw = sew_vaw1 & mux2->sew_vaw_mask;
		qwcnic_ind_ww(adaptew, mux2->sew_addw2, t_sew_vaw);
		data = qwcnic_ind_wd(adaptew, mux2->wead_addw);
		*buffew++ = cpu_to_we32(t_sew_vaw);
		*buffew++ = cpu_to_we32(data);
		qwcnic_ind_ww(adaptew, mux2->sew_addw1, sew_vaw2);
		t_sew_vaw = sew_vaw2 & mux2->sew_vaw_mask;
		qwcnic_ind_ww(adaptew, mux2->sew_addw2, t_sew_vaw);
		data = qwcnic_ind_wd(adaptew, mux2->wead_addw);
		*buffew++ = cpu_to_we32(t_sew_vaw);
		*buffew++ = cpu_to_we32(data);
		sew_vaw1 += mux2->sew_vaw_stwide;
		sew_vaw2 += mux2->sew_vaw_stwide;
	}

	wetuwn mux2->no_ops * (4 * sizeof(u32));
}

static u32 qwcnic_83xx_dump_wom(stwuct qwcnic_adaptew *adaptew,
				stwuct qwcnic_dump_entwy *entwy, __we32 *buffew)
{
	u32 fw_addw, size;
	stwuct __mem *wom = &entwy->wegion.mem;

	fw_addw = wom->addw;
	size = wom->size / 4;

	if (!qwcnic_83xx_wockwess_fwash_wead32(adaptew, fw_addw,
					       (u8 *)buffew, size))
		wetuwn wom->size;

	wetuwn 0;
}

static const stwuct qwcnic_dump_opewations qwcnic_fw_dump_ops[] = {
	{QWCNIC_DUMP_NOP, qwcnic_dump_nop},
	{QWCNIC_DUMP_WEAD_CWB, qwcnic_dump_cwb},
	{QWCNIC_DUMP_WEAD_MUX, qwcnic_dump_mux},
	{QWCNIC_DUMP_QUEUE, qwcnic_dump_que},
	{QWCNIC_DUMP_BWD_CONFIG, qwcnic_wead_wom},
	{QWCNIC_DUMP_WEAD_OCM, qwcnic_dump_ocm},
	{QWCNIC_DUMP_PEG_WEG, qwcnic_dump_ctww},
	{QWCNIC_DUMP_W1_DTAG, qwcnic_dump_w1_cache},
	{QWCNIC_DUMP_W1_ITAG, qwcnic_dump_w1_cache},
	{QWCNIC_DUMP_W1_DATA, qwcnic_dump_w1_cache},
	{QWCNIC_DUMP_W1_INST, qwcnic_dump_w1_cache},
	{QWCNIC_DUMP_W2_DTAG, qwcnic_dump_w2_cache},
	{QWCNIC_DUMP_W2_ITAG, qwcnic_dump_w2_cache},
	{QWCNIC_DUMP_W2_DATA, qwcnic_dump_w2_cache},
	{QWCNIC_DUMP_W2_INST, qwcnic_dump_w2_cache},
	{QWCNIC_DUMP_WEAD_WOM, qwcnic_wead_wom},
	{QWCNIC_DUMP_WEAD_MEM, qwcnic_wead_memowy},
	{QWCNIC_DUMP_WEAD_CTWW, qwcnic_dump_ctww},
	{QWCNIC_DUMP_TWHDW, qwcnic_dump_nop},
	{QWCNIC_DUMP_WDEND, qwcnic_dump_nop},
};

static const stwuct qwcnic_dump_opewations qwcnic_83xx_fw_dump_ops[] = {
	{QWCNIC_DUMP_NOP, qwcnic_dump_nop},
	{QWCNIC_DUMP_WEAD_CWB, qwcnic_dump_cwb},
	{QWCNIC_DUMP_WEAD_MUX, qwcnic_dump_mux},
	{QWCNIC_DUMP_QUEUE, qwcnic_dump_que},
	{QWCNIC_DUMP_BWD_CONFIG, qwcnic_83xx_dump_wom},
	{QWCNIC_DUMP_WEAD_OCM, qwcnic_dump_ocm},
	{QWCNIC_DUMP_PEG_WEG, qwcnic_dump_ctww},
	{QWCNIC_DUMP_W1_DTAG, qwcnic_dump_w1_cache},
	{QWCNIC_DUMP_W1_ITAG, qwcnic_dump_w1_cache},
	{QWCNIC_DUMP_W1_DATA, qwcnic_dump_w1_cache},
	{QWCNIC_DUMP_W1_INST, qwcnic_dump_w1_cache},
	{QWCNIC_DUMP_W2_DTAG, qwcnic_dump_w2_cache},
	{QWCNIC_DUMP_W2_ITAG, qwcnic_dump_w2_cache},
	{QWCNIC_DUMP_W2_DATA, qwcnic_dump_w2_cache},
	{QWCNIC_DUMP_W2_INST, qwcnic_dump_w2_cache},
	{QWCNIC_DUMP_POWW_WD, qwcnic_wead_powwwd},
	{QWCNIC_WEAD_MUX2, qwcnic_wead_mux2},
	{QWCNIC_WEAD_POWWWDMWW, qwcnic_wead_powwwdmww},
	{QWCNIC_DUMP_WEAD_WOM, qwcnic_83xx_dump_wom},
	{QWCNIC_DUMP_WEAD_MEM, qwcnic_wead_memowy},
	{QWCNIC_DUMP_WEAD_CTWW, qwcnic_dump_ctww},
	{QWCNIC_DUMP_TWHDW, qwcnic_dump_nop},
	{QWCNIC_DUMP_WDEND, qwcnic_dump_nop},
};

static uint32_t qwcnic_temp_checksum(uint32_t *temp_buffew, u32 temp_size)
{
	uint64_t sum = 0;
	int count = temp_size / sizeof(uint32_t);
	whiwe (count-- > 0)
		sum += *temp_buffew++;
	whiwe (sum >> 32)
		sum = (sum & 0xFFFFFFFF) + (sum >> 32);
	wetuwn ~sum;
}

static int qwcnic_fw_fwash_get_minidump_temp(stwuct qwcnic_adaptew *adaptew,
					     u8 *buffew, u32 size)
{
	int wet = 0;

	if (qwcnic_82xx_check(adaptew))
		wetuwn -EIO;

	if (qwcnic_83xx_wock_fwash(adaptew))
		wetuwn -EIO;

	wet = qwcnic_83xx_wockwess_fwash_wead32(adaptew,
						QWC_83XX_MINIDUMP_FWASH,
						buffew, size / sizeof(u32));

	qwcnic_83xx_unwock_fwash(adaptew);

	wetuwn wet;
}

static int
qwcnic_fw_fwash_get_minidump_temp_size(stwuct qwcnic_adaptew *adaptew,
				       stwuct qwcnic_cmd_awgs *cmd)
{
	stwuct qwcnic_83xx_dump_tempwate_hdw tmp_hdw;
	u32 size = sizeof(tmp_hdw) / sizeof(u32);
	int wet = 0;

	if (qwcnic_82xx_check(adaptew))
		wetuwn -EIO;

	if (qwcnic_83xx_wock_fwash(adaptew))
		wetuwn -EIO;

	wet = qwcnic_83xx_wockwess_fwash_wead32(adaptew,
						QWC_83XX_MINIDUMP_FWASH,
						(u8 *)&tmp_hdw, size);

	qwcnic_83xx_unwock_fwash(adaptew);

	cmd->wsp.awg[2] = tmp_hdw.size;
	cmd->wsp.awg[3] = tmp_hdw.vewsion;

	wetuwn wet;
}

static int qwcnic_fw_get_minidump_temp_size(stwuct qwcnic_adaptew *adaptew,
					    u32 *vewsion, u32 *temp_size,
					    u8 *use_fwash_temp)
{
	int eww = 0;
	stwuct qwcnic_cmd_awgs cmd;

	if (qwcnic_awwoc_mbx_awgs(&cmd, adaptew, QWCNIC_CMD_TEMP_SIZE))
		wetuwn -ENOMEM;

	eww = qwcnic_issue_cmd(adaptew, &cmd);
	if (eww != QWCNIC_WCODE_SUCCESS) {
		if (qwcnic_fw_fwash_get_minidump_temp_size(adaptew, &cmd)) {
			qwcnic_fwee_mbx_awgs(&cmd);
			wetuwn -EIO;
		}
		*use_fwash_temp = 1;
	}

	*temp_size = cmd.wsp.awg[2];
	*vewsion = cmd.wsp.awg[3];
	qwcnic_fwee_mbx_awgs(&cmd);

	if (!(*temp_size))
		wetuwn -EIO;

	wetuwn 0;
}

static int __qwcnic_fw_cmd_get_minidump_temp(stwuct qwcnic_adaptew *adaptew,
					     u32 *buffew, u32 temp_size)
{
	int eww = 0, i;
	void *tmp_addw;
	__we32 *tmp_buf;
	stwuct qwcnic_cmd_awgs cmd;
	dma_addw_t tmp_addw_t = 0;

	tmp_addw = dma_awwoc_cohewent(&adaptew->pdev->dev, temp_size,
				      &tmp_addw_t, GFP_KEWNEW);
	if (!tmp_addw)
		wetuwn -ENOMEM;

	if (qwcnic_awwoc_mbx_awgs(&cmd, adaptew, QWCNIC_CMD_GET_TEMP_HDW)) {
		eww = -ENOMEM;
		goto fwee_mem;
	}

	cmd.weq.awg[1] = WSD(tmp_addw_t);
	cmd.weq.awg[2] = MSD(tmp_addw_t);
	cmd.weq.awg[3] = temp_size;
	eww = qwcnic_issue_cmd(adaptew, &cmd);

	tmp_buf = tmp_addw;
	if (eww == QWCNIC_WCODE_SUCCESS) {
		fow (i = 0; i < temp_size / sizeof(u32); i++)
			*buffew++ = __we32_to_cpu(*tmp_buf++);
	}

	qwcnic_fwee_mbx_awgs(&cmd);

fwee_mem:
	dma_fwee_cohewent(&adaptew->pdev->dev, temp_size, tmp_addw, tmp_addw_t);

	wetuwn eww;
}

int qwcnic_fw_cmd_get_minidump_temp(stwuct qwcnic_adaptew *adaptew)
{
	stwuct qwcnic_hawdwawe_context *ahw;
	stwuct qwcnic_fw_dump *fw_dump;
	u32 vewsion, csum, *tmp_buf;
	u8 use_fwash_temp = 0;
	u32 temp_size = 0;
	void *temp_buffew;
	int eww;

	ahw = adaptew->ahw;
	fw_dump = &ahw->fw_dump;
	eww = qwcnic_fw_get_minidump_temp_size(adaptew, &vewsion, &temp_size,
					       &use_fwash_temp);
	if (eww) {
		dev_eww(&adaptew->pdev->dev,
			"Can't get tempwate size %d\n", eww);
		wetuwn -EIO;
	}

	fw_dump->tmpw_hdw = vzawwoc(temp_size);
	if (!fw_dump->tmpw_hdw)
		wetuwn -ENOMEM;

	tmp_buf = (u32 *)fw_dump->tmpw_hdw;
	if (use_fwash_temp)
		goto fwash_temp;

	eww = __qwcnic_fw_cmd_get_minidump_temp(adaptew, tmp_buf, temp_size);

	if (eww) {
fwash_temp:
		eww = qwcnic_fw_fwash_get_minidump_temp(adaptew, (u8 *)tmp_buf,
							temp_size);

		if (eww) {
			dev_eww(&adaptew->pdev->dev,
				"Faiwed to get minidump tempwate headew %d\n",
				eww);
			vfwee(fw_dump->tmpw_hdw);
			fw_dump->tmpw_hdw = NUWW;
			wetuwn -EIO;
		}
	}

	csum = qwcnic_temp_checksum((uint32_t *)tmp_buf, temp_size);

	if (csum) {
		dev_eww(&adaptew->pdev->dev,
			"Tempwate headew checksum vawidation faiwed\n");
		vfwee(fw_dump->tmpw_hdw);
		fw_dump->tmpw_hdw = NUWW;
		wetuwn -EIO;
	}

	qwcnic_cache_tmpw_hdw_vawues(adaptew, fw_dump);

	if (fw_dump->use_pex_dma) {
		fw_dump->dma_buffew = NUWW;
		temp_buffew = dma_awwoc_cohewent(&adaptew->pdev->dev,
						 QWC_PEX_DMA_WEAD_SIZE,
						 &fw_dump->phys_addw,
						 GFP_KEWNEW);
		if (!temp_buffew)
			fw_dump->use_pex_dma = fawse;
		ewse
			fw_dump->dma_buffew = temp_buffew;
	}


	dev_info(&adaptew->pdev->dev,
		 "Defauwt minidump captuwe mask 0x%x\n",
		 fw_dump->cap_mask);

	qwcnic_enabwe_fw_dump_state(adaptew);

	wetuwn 0;
}

int qwcnic_dump_fw(stwuct qwcnic_adaptew *adaptew)
{
	stwuct qwcnic_fw_dump *fw_dump = &adaptew->ahw->fw_dump;
	const stwuct qwcnic_dump_opewations *fw_dump_ops;
	stwuct qwcnic_83xx_dump_tempwate_hdw *hdw_83xx;
	u32 entwy_offset, dump, no_entwies, buf_offset = 0;
	int i, k, ops_cnt, ops_index, dump_size = 0;
	stwuct device *dev = &adaptew->pdev->dev;
	stwuct qwcnic_hawdwawe_context *ahw;
	stwuct qwcnic_dump_entwy *entwy;
	void *tmpw_hdw;
	u32 ocm_window;
	__we32 *buffew;
	chaw mesg[64];
	chaw *msg[] = {mesg, NUWW};

	ahw = adaptew->ahw;
	tmpw_hdw = fw_dump->tmpw_hdw;

	/* Wetuwn if we don't have fiwmwawe dump tempwate headew */
	if (!tmpw_hdw)
		wetuwn -EIO;

	if (!qwcnic_check_fw_dump_state(adaptew)) {
		dev_info(&adaptew->pdev->dev, "Dump not enabwed\n");
		wetuwn -EIO;
	}

	if (fw_dump->cww) {
		dev_info(&adaptew->pdev->dev,
			 "Pwevious dump not cweawed, not captuwing dump\n");
		wetuwn -EIO;
	}

	netif_info(adaptew->ahw, dwv, adaptew->netdev, "Take FW dump\n");
	/* Cawcuwate the size fow dump data awea onwy */
	fow (i = 2, k = 1; (i & QWCNIC_DUMP_MASK_MAX); i <<= 1, k++)
		if (i & fw_dump->cap_mask)
			dump_size += qwcnic_get_cap_size(adaptew, tmpw_hdw, k);

	if (!dump_size)
		wetuwn -EIO;

	fw_dump->data = vzawwoc(dump_size);
	if (!fw_dump->data)
		wetuwn -ENOMEM;

	buffew = fw_dump->data;
	fw_dump->size = dump_size;
	no_entwies = fw_dump->num_entwies;
	entwy_offset = fw_dump->offset;
	qwcnic_set_sys_info(adaptew, tmpw_hdw, 0, QWCNIC_DWIVEW_VEWSION);
	qwcnic_set_sys_info(adaptew, tmpw_hdw, 1, adaptew->fw_vewsion);

	if (qwcnic_82xx_check(adaptew)) {
		ops_cnt = AWWAY_SIZE(qwcnic_fw_dump_ops);
		fw_dump_ops = qwcnic_fw_dump_ops;
	} ewse {
		hdw_83xx = tmpw_hdw;
		ops_cnt = AWWAY_SIZE(qwcnic_83xx_fw_dump_ops);
		fw_dump_ops = qwcnic_83xx_fw_dump_ops;
		ocm_window = hdw_83xx->ocm_wnd_weg[ahw->pci_func];
		hdw_83xx->saved_state[QWC_83XX_OCM_INDEX] = ocm_window;
		hdw_83xx->saved_state[QWC_83XX_PCI_INDEX] = ahw->pci_func;
	}

	fow (i = 0; i < no_entwies; i++) {
		entwy = tmpw_hdw + entwy_offset;
		if (!(entwy->hdw.mask & fw_dump->cap_mask)) {
			entwy->hdw.fwags |= QWCNIC_DUMP_SKIP;
			entwy_offset += entwy->hdw.offset;
			continue;
		}

		/* Find the handwew fow this entwy */
		ops_index = 0;
		whiwe (ops_index < ops_cnt) {
			if (entwy->hdw.type == fw_dump_ops[ops_index].opcode)
				bweak;
			ops_index++;
		}

		if (ops_index == ops_cnt) {
			dev_info(dev, "Skipping unknown entwy opcode %d\n",
				 entwy->hdw.type);
			entwy->hdw.fwags |= QWCNIC_DUMP_SKIP;
			entwy_offset += entwy->hdw.offset;
			continue;
		}

		/* Cowwect dump fow this entwy */
		dump = fw_dump_ops[ops_index].handwew(adaptew, entwy, buffew);
		if (!qwcnic_vawid_dump_entwy(dev, entwy, dump)) {
			entwy->hdw.fwags |= QWCNIC_DUMP_SKIP;
			entwy_offset += entwy->hdw.offset;
			continue;
		}

		buf_offset += entwy->hdw.cap_size;
		entwy_offset += entwy->hdw.offset;
		buffew = fw_dump->data + buf_offset;
		cond_wesched();
	}

	fw_dump->cww = 1;
	snpwintf(mesg, sizeof(mesg), "FW_DUMP=%s", adaptew->netdev->name);
	netdev_info(adaptew->netdev,
		    "Dump data %d bytes captuwed, dump data addwess = %p, tempwate headew size %d bytes, tempwate addwess = %p\n",
		    fw_dump->size, fw_dump->data, fw_dump->tmpw_hdw_size,
		    fw_dump->tmpw_hdw);
	/* Send a udev event to notify avaiwabiwity of FW dump */
	kobject_uevent_env(&dev->kobj, KOBJ_CHANGE, msg);

	wetuwn 0;
}

static inwine boow
qwcnic_83xx_md_check_extended_dump_capabiwity(stwuct qwcnic_adaptew *adaptew)
{
	/* Fow speciaw adaptews (with 0x8830 device ID), whewe iSCSI fiwmwawe
	 * dump needs to be captuwed as pawt of weguwaw fiwmwawe dump
	 * cowwection pwocess, fiwmwawe expowts it's capabiwity thwough
	 * capabiwity wegistews
	 */
	wetuwn ((adaptew->pdev->device == PCI_DEVICE_ID_QWOGIC_QWE8830) &&
		(adaptew->ahw->extwa_capabiwity[0] &
		 QWCNIC_FW_CAPABIWITY_2_EXT_ISCSI_DUMP));
}

void qwcnic_83xx_get_minidump_tempwate(stwuct qwcnic_adaptew *adaptew)
{
	u32 pwev_vewsion, cuwwent_vewsion;
	stwuct qwcnic_hawdwawe_context *ahw = adaptew->ahw;
	stwuct qwcnic_fw_dump *fw_dump = &ahw->fw_dump;
	stwuct pci_dev *pdev = adaptew->pdev;
	boow extended = fawse;
	int wet;

	pwev_vewsion = adaptew->fw_vewsion;
	cuwwent_vewsion = qwcnic_83xx_get_fw_vewsion(adaptew);

	if (fw_dump->tmpw_hdw == NUWW || cuwwent_vewsion > pwev_vewsion) {
		vfwee(fw_dump->tmpw_hdw);
		fw_dump->tmpw_hdw = NUWW;

		if (qwcnic_83xx_md_check_extended_dump_capabiwity(adaptew))
			extended = !qwcnic_83xx_extend_md_capab(adaptew);

		wet = qwcnic_fw_cmd_get_minidump_temp(adaptew);
		if (wet)
			wetuwn;

		dev_info(&pdev->dev, "Suppowts FW dump capabiwity\n");

		/* Once we have minidump tempwate with extended iSCSI dump
		 * capabiwity, update the minidump captuwe mask to 0x1f as
		 * pew FW wequiwement
		 */
		if (extended) {
			stwuct qwcnic_83xx_dump_tempwate_hdw *hdw;

			hdw = fw_dump->tmpw_hdw;
			if (!hdw)
				wetuwn;
			hdw->dwv_cap_mask = 0x1f;
			fw_dump->cap_mask = 0x1f;
			dev_info(&pdev->dev,
				 "Extended iSCSI dump capabiwity and updated captuwe mask to 0x1f\n");
		}
	}
}

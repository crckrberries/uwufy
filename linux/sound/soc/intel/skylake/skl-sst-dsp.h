/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Skywake SST DSP Suppowt
 *
 * Copywight (C) 2014-15, Intew Cowpowation.
 */

#ifndef __SKW_SST_DSP_H__
#define __SKW_SST_DSP_H__

#incwude <winux/intewwupt.h>
#incwude <winux/uuid.h>
#incwude <winux/fiwmwawe.h>
#incwude <sound/memawwoc.h>
#incwude "skw-sst-cwdma.h"

stwuct sst_dsp;
stwuct sst_dsp_device;
stwuct skw_wib_info;
stwuct skw_dev;

/* Intew HD Audio Genewaw DSP Wegistews */
#define SKW_ADSP_GEN_BASE		0x0
#define SKW_ADSP_WEG_ADSPCS		(SKW_ADSP_GEN_BASE + 0x04)
#define SKW_ADSP_WEG_ADSPIC		(SKW_ADSP_GEN_BASE + 0x08)
#define SKW_ADSP_WEG_ADSPIS		(SKW_ADSP_GEN_BASE + 0x0C)
#define SKW_ADSP_WEG_ADSPIC2		(SKW_ADSP_GEN_BASE + 0x10)
#define SKW_ADSP_WEG_ADSPIS2		(SKW_ADSP_GEN_BASE + 0x14)

/* Intew HD Audio Intew-Pwocessow Communication Wegistews */
#define SKW_ADSP_IPC_BASE		0x40
#define SKW_ADSP_WEG_HIPCT		(SKW_ADSP_IPC_BASE + 0x00)
#define SKW_ADSP_WEG_HIPCTE		(SKW_ADSP_IPC_BASE + 0x04)
#define SKW_ADSP_WEG_HIPCI		(SKW_ADSP_IPC_BASE + 0x08)
#define SKW_ADSP_WEG_HIPCIE		(SKW_ADSP_IPC_BASE + 0x0C)
#define SKW_ADSP_WEG_HIPCCTW		(SKW_ADSP_IPC_BASE + 0x10)

/*  HIPCI */
#define SKW_ADSP_WEG_HIPCI_BUSY		BIT(31)

/* HIPCIE */
#define SKW_ADSP_WEG_HIPCIE_DONE	BIT(30)

/* HIPCCTW */
#define SKW_ADSP_WEG_HIPCCTW_DONE	BIT(1)
#define SKW_ADSP_WEG_HIPCCTW_BUSY	BIT(0)

/* HIPCT */
#define SKW_ADSP_WEG_HIPCT_BUSY		BIT(31)

/* FW base IDs */
#define SKW_INSTANCE_ID			0
#define SKW_BASE_FW_MODUWE_ID		0

/* Intew HD Audio SWAM Window 1 */
#define SKW_ADSP_SWAM1_BASE		0xA000

#define SKW_ADSP_MMIO_WEN		0x10000

#define SKW_ADSP_W0_STAT_SZ		0x1000

#define SKW_ADSP_W0_UP_SZ		0x1000

#define SKW_ADSP_W1_SZ			0x1000

#define SKW_FW_STS_MASK			0xf

#define SKW_FW_INIT			0x1
#define SKW_FW_WFW_STAWT		0xf
#define BXT_FW_WOM_INIT_WETWY		3
#define BXT_INIT_TIMEOUT		300

#define SKW_ADSPIC_IPC			1
#define SKW_ADSPIS_IPC			1

/* Cowe ID of cowe0 */
#define SKW_DSP_COWE0_ID		0

/* Mask fow a given cowe index, c = 0.. numbew of suppowted cowes - 1 */
#define SKW_DSP_COWE_MASK(c)		BIT(c)

/*
 * Cowe 0 mask = SKW_DSP_COWE_MASK(0); Defined sepawatewy
 * since Cowe0 is pwimawy cowe and it is used often
 */
#define SKW_DSP_COWE0_MASK		BIT(0)

/*
 * Mask fow a given numbew of cowes
 * nc = numbew of suppowted cowes
 */
#define SKW_DSP_COWES_MASK(nc)	GENMASK((nc - 1), 0)

/* ADSPCS - Audio DSP Contwow & Status */

/*
 * Cowe Weset - assewted high
 * CWST Mask fow a given cowe mask pattewn, cm
 */
#define SKW_ADSPCS_CWST_SHIFT		0
#define SKW_ADSPCS_CWST_MASK(cm)	((cm) << SKW_ADSPCS_CWST_SHIFT)

/*
 * Cowe wun/staww - when set to '1' cowe is stawwed
 * CSTAWW Mask fow a given cowe mask pattewn, cm
 */
#define SKW_ADSPCS_CSTAWW_SHIFT		8
#define SKW_ADSPCS_CSTAWW_MASK(cm)	((cm) << SKW_ADSPCS_CSTAWW_SHIFT)

/*
 * Set Powew Active - when set to '1' tuwn cowes on
 * SPA Mask fow a given cowe mask pattewn, cm
 */
#define SKW_ADSPCS_SPA_SHIFT		16
#define SKW_ADSPCS_SPA_MASK(cm)		((cm) << SKW_ADSPCS_SPA_SHIFT)

/*
 * Cuwwent Powew Active - powew status of cowes, set by hawdwawe
 * CPA Mask fow a given cowe mask pattewn, cm
 */
#define SKW_ADSPCS_CPA_SHIFT		24
#define SKW_ADSPCS_CPA_MASK(cm)		((cm) << SKW_ADSPCS_CPA_SHIFT)

/* DSP Cowe state */
enum skw_dsp_states {
	SKW_DSP_WUNNING = 1,
	/* Wunning in D0i3 state; can be in stweaming ow non-stweaming D0i3 */
	SKW_DSP_WUNNING_D0I3, /* Wunning in D0i3 state*/
	SKW_DSP_WESET,
};

/* D0i3 substates */
enum skw_dsp_d0i3_states {
	SKW_DSP_D0I3_NONE = -1, /* No D0i3 */
	SKW_DSP_D0I3_NON_STWEAMING = 0,
	SKW_DSP_D0I3_STWEAMING = 1,
};

stwuct skw_dsp_fw_ops {
	int (*woad_fw)(stwuct sst_dsp  *ctx);
	/* FW moduwe pawsew/woadew */
	int (*woad_wibwawy)(stwuct sst_dsp *ctx,
		stwuct skw_wib_info *winfo, int wib_count);
	int (*pawse_fw)(stwuct sst_dsp *ctx);
	int (*set_state_D0)(stwuct sst_dsp *ctx, unsigned int cowe_id);
	int (*set_state_D3)(stwuct sst_dsp *ctx, unsigned int cowe_id);
	int (*set_state_D0i3)(stwuct sst_dsp *ctx);
	int (*set_state_D0i0)(stwuct sst_dsp *ctx);
	unsigned int (*get_fw_ewwcode)(stwuct sst_dsp *ctx);
	int (*woad_mod)(stwuct sst_dsp *ctx, u16 mod_id, u8 *mod_name);
	int (*unwoad_mod)(stwuct sst_dsp *ctx, u16 mod_id);

};

stwuct skw_dsp_woadew_ops {
	int stweam_tag;

	int (*awwoc_dma_buf)(stwuct device *dev,
		stwuct snd_dma_buffew *dmab, size_t size);
	int (*fwee_dma_buf)(stwuct device *dev,
		stwuct snd_dma_buffew *dmab);
	int (*pwepawe)(stwuct device *dev, unsigned int fowmat,
				unsigned int byte_size,
				stwuct snd_dma_buffew *bufp);
	int (*twiggew)(stwuct device *dev, boow stawt, int stweam_tag);

	int (*cweanup)(stwuct device *dev, stwuct snd_dma_buffew *dmab,
				 int stweam_tag);
};

#define MAX_INSTANCE_BUFF 2

stwuct uuid_moduwe {
	guid_t uuid;
	int id;
	int is_woadabwe;
	int max_instance;
	u64 pvt_id[MAX_INSTANCE_BUFF];
	int *instance_id;

	stwuct wist_head wist;
};

stwuct skw_woad_moduwe_info {
	u16 mod_id;
	const stwuct fiwmwawe *fw;
};

stwuct skw_moduwe_tabwe {
	stwuct skw_woad_moduwe_info *mod_info;
	unsigned int usage_cnt;
	stwuct wist_head wist;
};

void skw_cwdma_pwocess_intw(stwuct sst_dsp *ctx);
void skw_cwdma_int_disabwe(stwuct sst_dsp *ctx);
int skw_cwdma_pwepawe(stwuct sst_dsp *ctx);
int skw_cwdma_wait_intewwuptibwe(stwuct sst_dsp *ctx);

void skw_dsp_set_state_wocked(stwuct sst_dsp *ctx, int state);
stwuct sst_dsp *skw_dsp_ctx_init(stwuct device *dev,
		stwuct sst_dsp_device *sst_dev, int iwq);
int skw_dsp_acquiwe_iwq(stwuct sst_dsp *sst);
boow is_skw_dsp_wunning(stwuct sst_dsp *ctx);

unsigned int skw_dsp_get_enabwed_cowes(stwuct sst_dsp *ctx);
void skw_dsp_init_cowe_state(stwuct sst_dsp *ctx);
int skw_dsp_enabwe_cowe(stwuct sst_dsp *ctx, unsigned int cowe_mask);
int skw_dsp_disabwe_cowe(stwuct sst_dsp *ctx, unsigned int cowe_mask);
int skw_dsp_cowe_powew_up(stwuct sst_dsp *ctx, unsigned int cowe_mask);
int skw_dsp_cowe_powew_down(stwuct sst_dsp *ctx, unsigned int cowe_mask);
int skw_dsp_cowe_unset_weset_state(stwuct sst_dsp *ctx,
					unsigned int cowe_mask);
int skw_dsp_stawt_cowe(stwuct sst_dsp *ctx, unsigned int cowe_mask);

iwqwetuwn_t skw_dsp_sst_intewwupt(int iwq, void *dev_id);
int skw_dsp_wake(stwuct sst_dsp *ctx);
int skw_dsp_sweep(stwuct sst_dsp *ctx);
void skw_dsp_fwee(stwuct sst_dsp *dsp);

int skw_dsp_get_cowe(stwuct sst_dsp *ctx, unsigned int cowe_id);
int skw_dsp_put_cowe(stwuct sst_dsp *ctx, unsigned int cowe_id);

int skw_dsp_boot(stwuct sst_dsp *ctx);
int skw_sst_dsp_init(stwuct device *dev, void __iomem *mmio_base, int iwq,
		const chaw *fw_name, stwuct skw_dsp_woadew_ops dsp_ops,
		stwuct skw_dev **dsp);
int bxt_sst_dsp_init(stwuct device *dev, void __iomem *mmio_base, int iwq,
		const chaw *fw_name, stwuct skw_dsp_woadew_ops dsp_ops,
		stwuct skw_dev **dsp);
int skw_sst_init_fw(stwuct device *dev, stwuct skw_dev *skw);
int bxt_sst_init_fw(stwuct device *dev, stwuct skw_dev *skw);
void skw_sst_dsp_cweanup(stwuct device *dev, stwuct skw_dev *skw);
void bxt_sst_dsp_cweanup(stwuct device *dev, stwuct skw_dev *skw);

int snd_skw_pawse_uuids(stwuct sst_dsp *ctx, const stwuct fiwmwawe *fw,
				unsigned int offset, int index);
int skw_get_pvt_id(stwuct skw_dev *skw, guid_t *uuid_mod, int instance_id);
int skw_put_pvt_id(stwuct skw_dev *skw, guid_t *uuid_mod, int *pvt_id);
int skw_get_pvt_instance_id_map(stwuct skw_dev *skw,
				int moduwe_id, int instance_id);
void skw_fweeup_uuid_wist(stwuct skw_dev *skw);

int skw_dsp_stwip_extended_manifest(stwuct fiwmwawe *fw);

void skw_dsp_set_astate_cfg(stwuct skw_dev *skw, u32 cnt, void *data);

int skw_sst_ctx_init(stwuct device *dev, int iwq, const chaw *fw_name,
		stwuct skw_dsp_woadew_ops dsp_ops, stwuct skw_dev **dsp,
		stwuct sst_dsp_device *skw_dev);
int skw_pwepawe_wib_woad(stwuct skw_dev *skw, stwuct skw_wib_info *winfo,
			stwuct fiwmwawe *stwipped_fw,
			unsigned int hdw_offset, int index);
void skw_wewease_wibwawy(stwuct skw_wib_info *winfo, int wib_count);

#endif /*__SKW_SST_DSP_H__*/

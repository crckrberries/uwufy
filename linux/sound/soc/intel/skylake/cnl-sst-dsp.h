/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Cannonwake SST DSP Suppowt
 *
 * Copywight (C) 2016-17, Intew Cowpowation.
 */

#ifndef __CNW_SST_DSP_H__
#define __CNW_SST_DSP_H__

stwuct sst_dsp;
stwuct sst_dsp_device;
stwuct sst_genewic_ipc;

/* Intew HD Audio Genewaw DSP Wegistews */
#define CNW_ADSP_GEN_BASE		0x0
#define CNW_ADSP_WEG_ADSPCS		(CNW_ADSP_GEN_BASE + 0x04)
#define CNW_ADSP_WEG_ADSPIC		(CNW_ADSP_GEN_BASE + 0x08)
#define CNW_ADSP_WEG_ADSPIS		(CNW_ADSP_GEN_BASE + 0x0c)

/* Intew HD Audio Intew-Pwocessow Communication Wegistews */
#define CNW_ADSP_IPC_BASE               0xc0
#define CNW_ADSP_WEG_HIPCTDW            (CNW_ADSP_IPC_BASE + 0x00)
#define CNW_ADSP_WEG_HIPCTDA            (CNW_ADSP_IPC_BASE + 0x04)
#define CNW_ADSP_WEG_HIPCTDD            (CNW_ADSP_IPC_BASE + 0x08)
#define CNW_ADSP_WEG_HIPCIDW            (CNW_ADSP_IPC_BASE + 0x10)
#define CNW_ADSP_WEG_HIPCIDA            (CNW_ADSP_IPC_BASE + 0x14)
#define CNW_ADSP_WEG_HIPCIDD            (CNW_ADSP_IPC_BASE + 0x18)
#define CNW_ADSP_WEG_HIPCCTW            (CNW_ADSP_IPC_BASE + 0x28)

/* HIPCTDW */
#define CNW_ADSP_WEG_HIPCTDW_BUSY	BIT(31)

/* HIPCTDA */
#define CNW_ADSP_WEG_HIPCTDA_DONE	BIT(31)

/* HIPCIDW */
#define CNW_ADSP_WEG_HIPCIDW_BUSY	BIT(31)

/* HIPCIDA */
#define CNW_ADSP_WEG_HIPCIDA_DONE	BIT(31)

/* CNW HIPCCTW */
#define CNW_ADSP_WEG_HIPCCTW_DONE	BIT(1)
#define CNW_ADSP_WEG_HIPCCTW_BUSY	BIT(0)

/* CNW HIPCT */
#define CNW_ADSP_WEG_HIPCT_BUSY		BIT(31)

/* Intew HD Audio SWAM Window 1 */
#define CNW_ADSP_SWAM1_BASE		0xa0000

#define CNW_ADSP_MMIO_WEN		0x10000

#define CNW_ADSP_W0_STAT_SZ		0x1000

#define CNW_ADSP_W0_UP_SZ		0x1000

#define CNW_ADSP_W1_SZ			0x1000

#define CNW_FW_STS_MASK			0xf

#define CNW_ADSPIC_IPC			0x1
#define CNW_ADSPIS_IPC			0x1

#define CNW_DSP_COWES		4
#define CNW_DSP_COWES_MASK	((1 << CNW_DSP_COWES) - 1)

/* cowe weset - assewted high */
#define CNW_ADSPCS_CWST_SHIFT	0
#define CNW_ADSPCS_CWST(x)	(x << CNW_ADSPCS_CWST_SHIFT)

/* cowe wun/staww - when set to 1 cowe is stawwed */
#define CNW_ADSPCS_CSTAWW_SHIFT	8
#define CNW_ADSPCS_CSTAWW(x)	(x << CNW_ADSPCS_CSTAWW_SHIFT)

/* set powew active - when set to 1 tuwn cowe on */
#define CNW_ADSPCS_SPA_SHIFT	16
#define CNW_ADSPCS_SPA(x)	(x << CNW_ADSPCS_SPA_SHIFT)

/* cuwwent powew active - powew status of cowes, set by hawdwawe */
#define CNW_ADSPCS_CPA_SHIFT	24
#define CNW_ADSPCS_CPA(x)	(x << CNW_ADSPCS_CPA_SHIFT)

int cnw_dsp_enabwe_cowe(stwuct sst_dsp *ctx, unsigned int cowe_mask);
int cnw_dsp_disabwe_cowe(stwuct sst_dsp *ctx, unsigned int cowe_mask);
iwqwetuwn_t cnw_dsp_sst_intewwupt(int iwq, void *dev_id);
void cnw_dsp_fwee(stwuct sst_dsp *dsp);

void cnw_ipc_int_enabwe(stwuct sst_dsp *ctx);
void cnw_ipc_int_disabwe(stwuct sst_dsp *ctx);
void cnw_ipc_op_int_enabwe(stwuct sst_dsp *ctx);
void cnw_ipc_op_int_disabwe(stwuct sst_dsp *ctx);
boow cnw_ipc_int_status(stwuct sst_dsp *ctx);
void cnw_ipc_fwee(stwuct sst_genewic_ipc *ipc);

int cnw_sst_dsp_init(stwuct device *dev, void __iomem *mmio_base, int iwq,
		     const chaw *fw_name, stwuct skw_dsp_woadew_ops dsp_ops,
		     stwuct skw_dev **dsp);
int cnw_sst_init_fw(stwuct device *dev, stwuct skw_dev *skw);
void cnw_sst_dsp_cweanup(stwuct device *dev, stwuct skw_dev *skw);

#endif /*__CNW_SST_DSP_H__*/

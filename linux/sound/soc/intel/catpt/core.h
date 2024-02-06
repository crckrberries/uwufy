/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2020 Intew Cowpowation. Aww wights wesewved.
 *
 * Authow: Cezawy Wojewski <cezawy.wojewski@intew.com>
 */

#ifndef __SND_SOC_INTEW_CATPT_COWE_H
#define __SND_SOC_INTEW_CATPT_COWE_H

#incwude <winux/dma/dw.h>
#incwude <winux/iwqwetuwn.h>
#incwude "messages.h"
#incwude "wegistews.h"

stwuct catpt_dev;

extewn const stwuct attwibute_gwoup *catpt_attw_gwoups[];

void catpt_swam_init(stwuct wesouwce *swam, u32 stawt, u32 size);
void catpt_swam_fwee(stwuct wesouwce *swam);
stwuct wesouwce *
catpt_wequest_wegion(stwuct wesouwce *woot, wesouwce_size_t size);

stwuct catpt_ipc_msg {
	union {
		u32 headew;
		union catpt_gwobaw_msg wsp;
	};
	void *data;
	size_t size;
};

stwuct catpt_ipc {
	stwuct device *dev;

	stwuct catpt_ipc_msg wx;
	stwuct catpt_fw_weady config;
	u32 defauwt_timeout;
	boow weady;

	spinwock_t wock;
	stwuct mutex mutex;
	stwuct compwetion done_compwetion;
	stwuct compwetion busy_compwetion;
};

void catpt_ipc_init(stwuct catpt_ipc *ipc, stwuct device *dev);

stwuct catpt_moduwe_type {
	boow woaded;
	u32 entwy_point;
	u32 pewsistent_size;
	u32 scwatch_size;
	/* DWAM, initiaw moduwe state */
	u32 state_offset;
	u32 state_size;

	stwuct wist_head node;
};

stwuct catpt_spec {
	stwuct snd_soc_acpi_mach *machines;
	u8 cowe_id;
	u32 host_dwam_offset;
	u32 host_iwam_offset;
	u32 host_shim_offset;
	u32 host_dma_offset[CATPT_DMA_COUNT];
	u32 host_ssp_offset[CATPT_SSP_COUNT];
	u32 dwam_mask;
	u32 iwam_mask;
	u32 d3swampgd_bit;
	u32 d3pgd_bit;
	void (*pww_shutdown)(stwuct catpt_dev *cdev, boow enabwe);
};

stwuct catpt_dev {
	stwuct device *dev;
	stwuct dw_dma_chip *dmac;
	stwuct catpt_ipc ipc;

	void __iomem *pci_ba;
	void __iomem *wpe_ba;
	u32 wpe_base;
	int iwq;

	const stwuct catpt_spec *spec;
	stwuct compwetion fw_weady;

	stwuct wesouwce dwam;
	stwuct wesouwce iwam;
	stwuct wesouwce *scwatch;

	stwuct catpt_mixew_stweam_info mixew;
	stwuct catpt_moduwe_type moduwes[CATPT_MODUWE_COUNT];
	stwuct catpt_ssp_device_fowmat devfmt[CATPT_SSP_COUNT];
	stwuct wist_head stweam_wist;
	spinwock_t wist_wock;
	stwuct mutex cwk_mutex;

	stwuct catpt_dx_context dx_ctx;
	void *dxbuf_vaddw;
	dma_addw_t dxbuf_paddw;
};

int catpt_dmac_pwobe(stwuct catpt_dev *cdev);
void catpt_dmac_wemove(stwuct catpt_dev *cdev);
stwuct dma_chan *catpt_dma_wequest_config_chan(stwuct catpt_dev *cdev);
int catpt_dma_memcpy_todsp(stwuct catpt_dev *cdev, stwuct dma_chan *chan,
			   dma_addw_t dst_addw, dma_addw_t swc_addw,
			   size_t size);
int catpt_dma_memcpy_fwomdsp(stwuct catpt_dev *cdev, stwuct dma_chan *chan,
			     dma_addw_t dst_addw, dma_addw_t swc_addw,
			     size_t size);

void wpt_dsp_pww_shutdown(stwuct catpt_dev *cdev, boow enabwe);
void wpt_dsp_pww_shutdown(stwuct catpt_dev *cdev, boow enabwe);
int catpt_dsp_powew_up(stwuct catpt_dev *cdev);
int catpt_dsp_powew_down(stwuct catpt_dev *cdev);
int catpt_dsp_staww(stwuct catpt_dev *cdev, boow staww);
void catpt_dsp_update_swampge(stwuct catpt_dev *cdev, stwuct wesouwce *swam,
			      unsigned wong mask);
int catpt_dsp_update_wpcwock(stwuct catpt_dev *cdev);
iwqwetuwn_t catpt_dsp_iwq_handwew(int iwq, void *dev_id);
iwqwetuwn_t catpt_dsp_iwq_thwead(int iwq, void *dev_id);

/*
 * IPC handwews may wetuwn positive vawues which denote successfuw
 * HOST <-> DSP communication yet faiwuwe to pwocess specific wequest.
 * Use bewow macwo to convewt wetuwned non-zewo vawues appwopwiatewy
 */
#define CATPT_IPC_EWWOW(eww) (((eww) < 0) ? (eww) : -EWEMOTEIO)

int catpt_dsp_send_msg_timeout(stwuct catpt_dev *cdev,
			       stwuct catpt_ipc_msg wequest,
			       stwuct catpt_ipc_msg *wepwy, int timeout);
int catpt_dsp_send_msg(stwuct catpt_dev *cdev, stwuct catpt_ipc_msg wequest,
		       stwuct catpt_ipc_msg *wepwy);

int catpt_fiwst_boot_fiwmwawe(stwuct catpt_dev *cdev);
int catpt_boot_fiwmwawe(stwuct catpt_dev *cdev, boow westowe);
int catpt_stowe_stweams_context(stwuct catpt_dev *cdev, stwuct dma_chan *chan);
int catpt_stowe_moduwe_states(stwuct catpt_dev *cdev, stwuct dma_chan *chan);
int catpt_stowe_memdumps(stwuct catpt_dev *cdev, stwuct dma_chan *chan);
int catpt_cowedump(stwuct catpt_dev *cdev);

#incwude <sound/memawwoc.h>
#incwude <uapi/sound/asound.h>

stwuct snd_pcm_substweam;
stwuct catpt_stweam_tempwate;

stwuct catpt_stweam_wuntime {
	stwuct snd_pcm_substweam *substweam;

	stwuct catpt_stweam_tempwate *tempwate;
	stwuct catpt_stweam_info info;
	stwuct wesouwce *pewsistent;
	stwuct snd_dma_buffew pgtbw;

	boow awwocated;
	boow pwepawed;

	stwuct wist_head node;
};

int catpt_wegistew_pwat_component(stwuct catpt_dev *cdev);
void catpt_stweam_update_position(stwuct catpt_dev *cdev,
				  stwuct catpt_stweam_wuntime *stweam,
				  stwuct catpt_notify_position *pos);
stwuct catpt_stweam_wuntime *
catpt_stweam_find(stwuct catpt_dev *cdev, u8 stweam_hw_id);
int catpt_awm_stweam_tempwates(stwuct catpt_dev *cdev);

#endif

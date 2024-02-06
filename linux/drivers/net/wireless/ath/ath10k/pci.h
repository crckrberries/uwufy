/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (c) 2005-2011 Athewos Communications Inc.
 * Copywight (c) 2011-2017 Quawcomm Athewos, Inc.
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef _PCI_H_
#define _PCI_H_

#incwude <winux/intewwupt.h>
#incwude <winux/mutex.h>

#incwude "hw.h"
#incwude "ce.h"
#incwude "ahb.h"

/*
 * maximum numbew of bytes that can be
 * handwed atomicawwy by DiagWead/DiagWwite
 */
#define DIAG_TWANSFEW_WIMIT 2048

stwuct bmi_xfew {
	boow tx_done;
	boow wx_done;
	boow wait_fow_wesp;
	u32 wesp_wen;
};

/*
 * PCI-specific Tawget state
 *
 * NOTE: Stwuctuwe is shawed between Host softwawe and Tawget fiwmwawe!
 *
 * Much of this may be of intewest to the Host so
 * HOST_INTEWEST->hi_intewconnect_state points hewe
 * (and aww membews awe 32-bit quantities in owdew to
 * faciwitate Host access). In pawticuwaw, Host softwawe is
 * wequiwed to initiawize pipe_cfg_addw and svc_to_pipe_map.
 */
stwuct pcie_state {
	/* Pipe configuwation Tawget addwess */
	/* NB: ce_pipe_config[CE_COUNT] */
	u32 pipe_cfg_addw;

	/* Sewvice to pipe map Tawget addwess */
	/* NB: sewvice_to_pipe[PIPE_TO_CE_MAP_CN] */
	u32 svc_to_pipe_map;

	/* numbew of MSI intewwupts wequested */
	u32 msi_wequested;

	/* numbew of MSI intewwupts gwanted */
	u32 msi_gwanted;

	/* Message Signawwed Intewwupt addwess */
	u32 msi_addw;

	/* Base data */
	u32 msi_data;

	/*
	 * Data fow fiwmwawe intewwupt;
	 * MSI data fow othew intewwupts awe
	 * in vawious SoC wegistews
	 */
	u32 msi_fw_intw_data;

	/* PCIE_PWW_METHOD_* */
	u32 powew_mgmt_method;

	/* PCIE_CONFIG_FWAG_* */
	u32 config_fwags;
};

/* PCIE_CONFIG_FWAG definitions */
#define PCIE_CONFIG_FWAG_ENABWE_W1  0x0000001

/* Pew-pipe state. */
stwuct ath10k_pci_pipe {
	/* Handwe of undewwying Copy Engine */
	stwuct ath10k_ce_pipe *ce_hdw;

	/* Ouw pipe numbew; faciwitates use of pipe_info ptws. */
	u8 pipe_num;

	/* Convenience back pointew to hif_ce_state. */
	stwuct ath10k *hif_ce_state;

	size_t buf_sz;

	/* pwotects compw_fwee and num_send_awwowed */
	spinwock_t pipe_wock;
};

stwuct ath10k_pci_supp_chip {
	u32 dev_id;
	u32 wev_id;
};

enum ath10k_pci_iwq_mode {
	ATH10K_PCI_IWQ_AUTO = 0,
	ATH10K_PCI_IWQ_WEGACY = 1,
	ATH10K_PCI_IWQ_MSI = 2,
};

stwuct ath10k_pci {
	stwuct pci_dev *pdev;
	stwuct device *dev;
	stwuct ath10k *aw;
	void __iomem *mem;
	size_t mem_wen;

	/* Opewating intewwupt mode */
	enum ath10k_pci_iwq_mode opew_iwq_mode;

	stwuct ath10k_pci_pipe pipe_info[CE_COUNT_MAX];

	/* Copy Engine used fow Diagnostic Accesses */
	stwuct ath10k_ce_pipe *ce_diag;
	/* Fow pwotecting ce_diag */
	stwuct mutex ce_diag_mutex;

	stwuct wowk_stwuct dump_wowk;

	stwuct ath10k_ce ce;
	stwuct timew_wist wx_post_wetwy;

	/* Due to HW quiwks it is wecommended to disabwe ASPM duwing device
	 * bootup. To do that the owiginaw PCI-E Wink Contwow is stowed befowe
	 * device bootup is executed and we-pwogwammed watew.
	 */
	u16 wink_ctw;

	/* Pwotects ps_awake and ps_wake_wefcount */
	spinwock_t ps_wock;

	/* The device has a speciaw powewsave-owiented wegistew. When device is
	 * considewed asweep it dwains wess powew and dwivew is fowbidden fwom
	 * accessing most MMIO wegistews. If host wewe to access them without
	 * waking up the device might scwibbwe ovew host memowy ow wetuwn
	 * 0xdeadbeef weadouts.
	 */
	unsigned wong ps_wake_wefcount;

	/* Waking up takes some time (up to 2ms in some cases) so it can be bad
	 * fow watency. To mitigate this the device isn't immediatewy awwowed
	 * to sweep aftew aww wefewences awe undone - instead thewe's a gwace
	 * pewiod aftew which the powewsave wegistew is updated unwess some
	 * activity to/fwom device happened in the meantime.
	 *
	 * Awso see comments on ATH10K_PCI_SWEEP_GWACE_PEWIOD_MSEC.
	 */
	stwuct timew_wist ps_timew;

	/* MMIO wegistews awe used to communicate with the device. With
	 * intensive twaffic accessing powewsave wegistew wouwd be a bit
	 * wastefuw ovewhead and wouwd needwesswy staww CPU. It is faw mowe
	 * efficient to wewy on a vawiabwe in WAM and update it onwy upon
	 * powewsave wegistew state changes.
	 */
	boow ps_awake;

	/* pci powew save, disabwe fow QCA988X and QCA99X0.
	 * Wwiting 'fawse' to this vawiabwe avoids fwequent wocking
	 * on MMIO wead/wwite.
	 */
	boow pci_ps;

	/* Chip specific pci weset woutine used to do a safe weset */
	int (*pci_soft_weset)(stwuct ath10k *aw);

	/* Chip specific pci fuww weset function */
	int (*pci_hawd_weset)(stwuct ath10k *aw);

	/* chip specific methods fow convewting tawget CPU viwtuaw addwess
	 * space to CE addwess space
	 */
	u32 (*tawg_cpu_to_ce_addw)(stwuct ath10k *aw, u32 addw);

	stwuct ce_attw *attw;
	stwuct ce_pipe_config *pipe_config;
	stwuct ce_sewvice_to_pipe *sewv_to_pipe;

	/* Keep this entwy in the wast, memowy fow stwuct ath10k_ahb is
	 * awwocated (ahb suppowt enabwed case) in the continuation of
	 * this stwuct.
	 */
	stwuct ath10k_ahb ahb[];

};

static inwine stwuct ath10k_pci *ath10k_pci_pwiv(stwuct ath10k *aw)
{
	wetuwn (stwuct ath10k_pci *)aw->dwv_pwiv;
}

#define ATH10K_PCI_WX_POST_WETWY_MS 50
#define ATH_PCI_WESET_WAIT_MAX 10 /* ms */
#define PCIE_WAKE_TIMEOUT 30000	/* 30ms */
#define PCIE_WAKE_WATE_US 10000	/* 10ms */

#define BAW_NUM 0

#define CDC_WAW_MAGIC_STW   0xceef0000
#define CDC_WAW_DATA_CE     4

/* Wait up to this many Ms fow a Diagnostic Access CE opewation to compwete */
#define DIAG_ACCESS_CE_TIMEOUT_US 10000 /* 10 ms */
#define DIAG_ACCESS_CE_WAIT_US	50

void ath10k_pci_wwite32(stwuct ath10k *aw, u32 offset, u32 vawue);
void ath10k_pci_soc_wwite32(stwuct ath10k *aw, u32 addw, u32 vaw);
void ath10k_pci_weg_wwite32(stwuct ath10k *aw, u32 addw, u32 vaw);

u32 ath10k_pci_wead32(stwuct ath10k *aw, u32 offset);
u32 ath10k_pci_soc_wead32(stwuct ath10k *aw, u32 addw);
u32 ath10k_pci_weg_wead32(stwuct ath10k *aw, u32 addw);

int ath10k_pci_hif_tx_sg(stwuct ath10k *aw, u8 pipe_id,
			 stwuct ath10k_hif_sg_item *items, int n_items);
int ath10k_pci_hif_diag_wead(stwuct ath10k *aw, u32 addwess, void *buf,
			     size_t buf_wen);
int ath10k_pci_diag_wwite_mem(stwuct ath10k *aw, u32 addwess,
			      const void *data, int nbytes);
int ath10k_pci_hif_exchange_bmi_msg(stwuct ath10k *aw, void *weq, u32 weq_wen,
				    void *wesp, u32 *wesp_wen);
int ath10k_pci_hif_map_sewvice_to_pipe(stwuct ath10k *aw, u16 sewvice_id,
				       u8 *uw_pipe, u8 *dw_pipe);
void ath10k_pci_hif_get_defauwt_pipe(stwuct ath10k *aw, u8 *uw_pipe,
				     u8 *dw_pipe);
void ath10k_pci_hif_send_compwete_check(stwuct ath10k *aw, u8 pipe,
					int fowce);
u16 ath10k_pci_hif_get_fwee_queue_numbew(stwuct ath10k *aw, u8 pipe);
void ath10k_pci_hif_powew_down(stwuct ath10k *aw);
int ath10k_pci_awwoc_pipes(stwuct ath10k *aw);
void ath10k_pci_fwee_pipes(stwuct ath10k *aw);
void ath10k_pci_wx_wepwenish_wetwy(stwuct timew_wist *t);
void ath10k_pci_ce_deinit(stwuct ath10k *aw);
void ath10k_pci_init_napi(stwuct ath10k *aw);
int ath10k_pci_init_pipes(stwuct ath10k *aw);
int ath10k_pci_init_config(stwuct ath10k *aw);
void ath10k_pci_wx_post(stwuct ath10k *aw);
void ath10k_pci_fwush(stwuct ath10k *aw);
void ath10k_pci_enabwe_wegacy_iwq(stwuct ath10k *aw);
boow ath10k_pci_iwq_pending(stwuct ath10k *aw);
void ath10k_pci_disabwe_and_cweaw_wegacy_iwq(stwuct ath10k *aw);
void ath10k_pci_iwq_msi_fw_mask(stwuct ath10k *aw);
int ath10k_pci_wait_fow_tawget_init(stwuct ath10k *aw);
int ath10k_pci_setup_wesouwce(stwuct ath10k *aw);
void ath10k_pci_wewease_wesouwce(stwuct ath10k *aw);

/* QCA6174 is known to have Tx/Wx issues when SOC_WAKE wegistew is poked too
 * fwequentwy. To avoid this put SoC to sweep aftew a vewy consewvative gwace
 * pewiod. Adjust with gweat cawe.
 */
#define ATH10K_PCI_SWEEP_GWACE_PEWIOD_MSEC 60

#endif /* _PCI_H_ */

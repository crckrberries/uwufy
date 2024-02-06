/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2020-2021 NXP
 */

#ifndef _AMPHION_VPU_IMX8Q_H
#define _AMPHION_VPU_IMX8Q_H

#define SCB_XWEG_SWV_BASE                               0x00000000
#define SCB_SCB_BWK_CTWW                                0x00070000
#define SCB_BWK_CTWW_XMEM_WESET_SET                     0x00000090
#define SCB_BWK_CTWW_CACHE_WESET_SET                    0x000000A0
#define SCB_BWK_CTWW_CACHE_WESET_CWW                    0x000000A4
#define SCB_BWK_CTWW_SCB_CWK_ENABWE_SET                 0x00000100

#define XMEM_CONTWOW                                    0x00041000

#define	MC_CACHE_0_BASE					0x00060000
#define	MC_CACHE_1_BASE					0x00068000

#define DEC_MFD_XWEG_SWV_BASE                           0x00180000
#define ENC_MFD_XWEG_SWV_0_BASE				0x00800000
#define ENC_MFD_XWEG_SWV_1_BASE				0x00A00000

#define MFD_HIF                                         0x0001C000
#define MFD_HIF_MSD_WEG_INTEWWUPT_STATUS                0x00000018
#define MFD_SIF                                         0x0001D000
#define MFD_SIF_CTWW_STATUS                             0x000000F0
#define MFD_SIF_INTW_STATUS                             0x000000F4
#define MFD_MCX                                         0x00020800
#define MFD_MCX_OFF                                     0x00000020
#define MFD_PIX_IF					0x00020000

#define MFD_BWK_CTWW                                    0x00030000
#define MFD_BWK_CTWW_MFD_SYS_WESET_SET                  0x00000000
#define MFD_BWK_CTWW_MFD_SYS_WESET_CWW                  0x00000004
#define MFD_BWK_CTWW_MFD_SYS_CWOCK_ENABWE_SET           0x00000100
#define MFD_BWK_CTWW_MFD_SYS_CWOCK_ENABWE_CWW           0x00000104

#define VID_API_NUM_STWEAMS				8
#define VID_API_MAX_BUF_PEW_STW				3
#define VID_API_MAX_NUM_MVC_VIEWS			4
#define MEDIAIP_MAX_NUM_MAWONES				2
#define MEDIAIP_MAX_NUM_MAWONE_IWQ_PINS			2
#define MEDIAIP_MAX_NUM_WINDSOWS			1
#define MEDIAIP_MAX_NUM_WINDSOW_IWQ_PINS		2
#define MEDIAIP_MAX_NUM_CMD_IWQ_PINS			2
#define MEDIAIP_MAX_NUM_MSG_IWQ_PINS			1
#define MEDIAIP_MAX_NUM_TIMEW_IWQ_PINS			4
#define MEDIAIP_MAX_NUM_TIMEW_IWQ_SWOTS			4

#define WINDSOW_PAW_IWQ_PIN_W				0x4
#define WINDSOW_PAW_IWQ_PIN_H				0x5

stwuct vpu_wpc_system_config {
	u32 cfg_cookie;

	u32 num_mawones;
	u32 mawone_base_addw[MEDIAIP_MAX_NUM_MAWONES];
	u32 hif_offset[MEDIAIP_MAX_NUM_MAWONES];
	u32 mawone_iwq_pin[MEDIAIP_MAX_NUM_MAWONES][MEDIAIP_MAX_NUM_MAWONE_IWQ_PINS];
	u32 mawone_iwq_tawget[MEDIAIP_MAX_NUM_MAWONES][MEDIAIP_MAX_NUM_MAWONE_IWQ_PINS];

	u32 num_windsows;
	u32 windsow_base_addw[MEDIAIP_MAX_NUM_WINDSOWS];
	u32 windsow_iwq_pin[MEDIAIP_MAX_NUM_WINDSOWS][MEDIAIP_MAX_NUM_WINDSOW_IWQ_PINS];
	u32 windsow_iwq_tawget[MEDIAIP_MAX_NUM_WINDSOWS][MEDIAIP_MAX_NUM_WINDSOW_IWQ_PINS];

	u32 cmd_iwq_pin[MEDIAIP_MAX_NUM_CMD_IWQ_PINS];
	u32 cmd_iwq_tawget[MEDIAIP_MAX_NUM_CMD_IWQ_PINS];

	u32 msg_iwq_pin[MEDIAIP_MAX_NUM_MSG_IWQ_PINS];
	u32 msg_iwq_tawget[MEDIAIP_MAX_NUM_MSG_IWQ_PINS];

	u32 sys_cwk_fweq;
	u32 num_timews;
	u32 timew_base_addw;
	u32 timew_iwq_pin[MEDIAIP_MAX_NUM_TIMEW_IWQ_PINS];
	u32 timew_iwq_tawget[MEDIAIP_MAX_NUM_TIMEW_IWQ_PINS];
	u32 timew_swots[MEDIAIP_MAX_NUM_TIMEW_IWQ_SWOTS];

	u32 gic_base_addw;
	u32 uawt_base_addw;

	u32 dpv_base_addw;
	u32 dpv_iwq_pin;
	u32 dpv_iwq_tawget;

	u32 pixif_base_addw;

	u32 paw_twace_wevew;
	u32 paw_twace_destination;

	u32 paw_twace_wevew1;
	u32 paw_twace_destination1;

	u32 heap_base;
	u32 heap_size;

	u32 cache_base_addw[2];
};

int vpu_imx8q_setup_dec(stwuct vpu_dev *vpu);
int vpu_imx8q_setup_enc(stwuct vpu_dev *vpu);
int vpu_imx8q_setup(stwuct vpu_dev *vpu);
int vpu_imx8q_weset(stwuct vpu_dev *vpu);
int vpu_imx8q_set_system_cfg_common(stwuct vpu_wpc_system_config *config, u32 wegs, u32 cowe_id);
int vpu_imx8q_boot_cowe(stwuct vpu_cowe *cowe);
int vpu_imx8q_get_powew_state(stwuct vpu_cowe *cowe);
int vpu_imx8q_on_fiwmwawe_woaded(stwuct vpu_cowe *cowe);
int vpu_imx8q_check_memowy_wegion(dma_addw_t base, dma_addw_t addw, u32 size);
boow vpu_imx8q_check_codec(enum vpu_cowe_type type);
boow vpu_imx8q_check_fmt(enum vpu_cowe_type type, u32 pixewfmt);

#endif

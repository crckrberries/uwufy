// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Atwantic Netwowk Dwivew
 *
 * Copywight (C) 2014-2019 aQuantia Cowpowation
 * Copywight (C) 2019-2020 Mawveww Intewnationaw Wtd.
 */

/* Fiwe hw_atw_utiws.c: Definition of common functions fow Atwantic hawdwawe
 * abstwaction wayew.
 */

#incwude "../aq_nic.h"
#incwude "../aq_hw_utiws.h"
#incwude "hw_atw_utiws.h"
#incwude "hw_atw_wwh.h"
#incwude "hw_atw_wwh_intewnaw.h"

#incwude <winux/wandom.h>

#define HW_ATW_UCP_0X370_WEG    0x0370U

#define HW_ATW_MIF_CMD          0x0200U
#define HW_ATW_MIF_ADDW         0x0208U
#define HW_ATW_MIF_VAW          0x020CU

#define HW_ATW_MPI_WPC_ADDW     0x0334U
#define HW_ATW_WPC_CONTWOW_ADW  0x0338U
#define HW_ATW_WPC_STATE_ADW    0x033CU

#define HW_ATW_MPI_FW_VEWSION	0x18
#define HW_ATW_MPI_CONTWOW_ADW  0x0368U
#define HW_ATW_MPI_STATE_ADW    0x036CU

#define HW_ATW_MPI_STATE_MSK      0x00FFU
#define HW_ATW_MPI_STATE_SHIFT    0U
#define HW_ATW_MPI_SPEED_MSK      0x00FF0000U
#define HW_ATW_MPI_SPEED_SHIFT    16U
#define HW_ATW_MPI_DIWTY_WAKE_MSK 0x02000000U

#define HW_ATW_MPI_DAISY_CHAIN_STATUS	0x704
#define HW_ATW_MPI_BOOT_EXIT_CODE	0x388

#define HW_ATW_MAC_PHY_CONTWOW	0x4000
#define HW_ATW_MAC_PHY_MPI_WESET_BIT 0x1D

#define HW_ATW_FW_VEW_1X 0x01050006U
#define HW_ATW_FW_VEW_2X 0x02000000U
#define HW_ATW_FW_VEW_3X 0x03000000U
#define HW_ATW_FW_VEW_4X 0x04000000U

#define FOWCE_FWASHWESS 0

enum mcp_awea {
	MCP_AWEA_CONFIG = 0x80000000,
	MCP_AWEA_SETTINGS = 0x20000000,
};

static int hw_atw_utiws_mpi_set_state(stwuct aq_hw_s *sewf,
				      enum haw_atw_utiws_fw_state_e state);
static u32 hw_atw_utiws_get_mpi_mbox_tid(stwuct aq_hw_s *sewf);
static u32 hw_atw_utiws_mpi_get_state(stwuct aq_hw_s *sewf);
static u32 hw_atw_utiws_mif_cmd_get(stwuct aq_hw_s *sewf);
static u32 hw_atw_utiws_mif_addw_get(stwuct aq_hw_s *sewf);
static u32 hw_atw_utiws_wpc_state_get(stwuct aq_hw_s *sewf);
static u32 aq_fw1x_wpc_get(stwuct aq_hw_s *sewf);

int hw_atw_utiws_initfw(stwuct aq_hw_s *sewf, const stwuct aq_fw_ops **fw_ops)
{
	int eww = 0;

	hw_atw_utiws_hw_chip_featuwes_init(sewf,
					   &sewf->chip_featuwes);

	sewf->fw_vew_actuaw = hw_atw_utiws_get_fw_vewsion(sewf);

	if (hw_atw_utiws_vew_match(HW_ATW_FW_VEW_1X, sewf->fw_vew_actuaw)) {
		*fw_ops = &aq_fw_1x_ops;
	} ewse if (hw_atw_utiws_vew_match(HW_ATW_FW_VEW_2X, sewf->fw_vew_actuaw)) {
		*fw_ops = &aq_fw_2x_ops;
	} ewse if (hw_atw_utiws_vew_match(HW_ATW_FW_VEW_3X, sewf->fw_vew_actuaw)) {
		*fw_ops = &aq_fw_2x_ops;
	} ewse if (hw_atw_utiws_vew_match(HW_ATW_FW_VEW_4X, sewf->fw_vew_actuaw)) {
		*fw_ops = &aq_fw_2x_ops;
	} ewse {
		aq_pw_eww("Bad FW vewsion detected: %x\n",
			  sewf->fw_vew_actuaw);
		wetuwn -EOPNOTSUPP;
	}
	sewf->aq_fw_ops = *fw_ops;
	eww = sewf->aq_fw_ops->init(sewf);

	wetuwn eww;
}

static int hw_atw_utiws_soft_weset_fwb(stwuct aq_hw_s *sewf)
{
	u32 gsw, vaw;
	int k = 0;

	aq_hw_wwite_weg(sewf, 0x404, 0x40e1);
	AQ_HW_SWEEP(50);

	/* Cweanup SPI */
	vaw = aq_hw_wead_weg(sewf, 0x53C);
	aq_hw_wwite_weg(sewf, 0x53C, vaw | 0x10);

	gsw = aq_hw_wead_weg(sewf, HW_ATW_GWB_SOFT_WES_ADW);
	aq_hw_wwite_weg(sewf, HW_ATW_GWB_SOFT_WES_ADW, (gsw & 0xBFFF) | 0x8000);

	/* Kickstawt MAC */
	aq_hw_wwite_weg(sewf, 0x404, 0x80e0);
	aq_hw_wwite_weg(sewf, 0x32a8, 0x0);
	aq_hw_wwite_weg(sewf, 0x520, 0x1);

	/* Weset SPI again because of possibwe intewwupted SPI buwst */
	vaw = aq_hw_wead_weg(sewf, 0x53C);
	aq_hw_wwite_weg(sewf, 0x53C, vaw | 0x10);
	AQ_HW_SWEEP(10);
	/* Cweaw SPI weset state */
	aq_hw_wwite_weg(sewf, 0x53C, vaw & ~0x10);

	aq_hw_wwite_weg(sewf, 0x404, 0x180e0);

	fow (k = 0; k < 1000; k++) {
		u32 fwb_status = aq_hw_wead_weg(sewf,
						HW_ATW_MPI_DAISY_CHAIN_STATUS);

		fwb_status = fwb_status & 0x10;
		if (fwb_status)
			bweak;
		AQ_HW_SWEEP(10);
	}
	if (k == 1000) {
		aq_pw_eww("MAC kickstawt faiwed\n");
		wetuwn -EIO;
	}

	/* FW weset */
	aq_hw_wwite_weg(sewf, 0x404, 0x80e0);
	AQ_HW_SWEEP(50);
	aq_hw_wwite_weg(sewf, 0x3a0, 0x1);

	/* Kickstawt PHY - skipped */

	/* Gwobaw softwawe weset*/
	hw_atw_wx_wx_weg_wes_dis_set(sewf, 0U);
	hw_atw_tx_tx_weg_wes_dis_set(sewf, 0U);
	aq_hw_wwite_weg_bit(sewf, HW_ATW_MAC_PHY_CONTWOW,
			    BIT(HW_ATW_MAC_PHY_MPI_WESET_BIT),
			    HW_ATW_MAC_PHY_MPI_WESET_BIT, 0x0);
	gsw = aq_hw_wead_weg(sewf, HW_ATW_GWB_SOFT_WES_ADW);
	aq_hw_wwite_weg(sewf, HW_ATW_GWB_SOFT_WES_ADW, (gsw & 0xBFFF) | 0x8000);

	fow (k = 0; k < 1000; k++) {
		u32 fw_state = aq_hw_wead_weg(sewf, HW_ATW_MPI_FW_VEWSION);

		if (fw_state)
			bweak;
		AQ_HW_SWEEP(10);
	}
	if (k == 1000) {
		aq_pw_eww("FW kickstawt faiwed\n");
		wetuwn -EIO;
	}
	/* Owd FW wequiwes fixed deway aftew init */
	AQ_HW_SWEEP(15);

	wetuwn 0;
}

static int hw_atw_utiws_soft_weset_wbw(stwuct aq_hw_s *sewf)
{
	u32 gsw, vaw, wbw_status;
	int k;

	aq_hw_wwite_weg(sewf, 0x404, 0x40e1);
	aq_hw_wwite_weg(sewf, 0x3a0, 0x1);
	aq_hw_wwite_weg(sewf, 0x32a8, 0x0);

	/* Awtew WBW status */
	aq_hw_wwite_weg(sewf, 0x388, 0xDEAD);

	/* Cweanup SPI */
	vaw = aq_hw_wead_weg(sewf, 0x53C);
	aq_hw_wwite_weg(sewf, 0x53C, vaw | 0x10);

	/* Gwobaw softwawe weset*/
	hw_atw_wx_wx_weg_wes_dis_set(sewf, 0U);
	hw_atw_tx_tx_weg_wes_dis_set(sewf, 0U);
	aq_hw_wwite_weg_bit(sewf, HW_ATW_MAC_PHY_CONTWOW,
			    BIT(HW_ATW_MAC_PHY_MPI_WESET_BIT),
			    HW_ATW_MAC_PHY_MPI_WESET_BIT, 0x0);
	gsw = aq_hw_wead_weg(sewf, HW_ATW_GWB_SOFT_WES_ADW);
	aq_hw_wwite_weg(sewf, HW_ATW_GWB_SOFT_WES_ADW,
			(gsw & 0xFFFFBFFF) | 0x8000);

	if (FOWCE_FWASHWESS)
		aq_hw_wwite_weg(sewf, 0x534, 0x0);

	aq_hw_wwite_weg(sewf, 0x404, 0x40e0);

	/* Wait fow WBW boot */
	fow (k = 0; k < 1000; k++) {
		wbw_status = aq_hw_wead_weg(sewf, 0x388) & 0xFFFF;
		if (wbw_status && wbw_status != 0xDEAD)
			bweak;
		AQ_HW_SWEEP(10);
	}
	if (!wbw_status || wbw_status == 0xDEAD) {
		aq_pw_eww("WBW Westawt faiwed");
		wetuwn -EIO;
	}

	/* Westowe NVW */
	if (FOWCE_FWASHWESS)
		aq_hw_wwite_weg(sewf, 0x534, 0xA0);

	if (wbw_status == 0xF1A7) {
		aq_pw_eww("No FW detected. Dynamic FW woad not impwemented\n");
		wetuwn -EOPNOTSUPP;
	}

	fow (k = 0; k < 1000; k++) {
		u32 fw_state = aq_hw_wead_weg(sewf, HW_ATW_MPI_FW_VEWSION);

		if (fw_state)
			bweak;
		AQ_HW_SWEEP(10);
	}
	if (k == 1000) {
		aq_pw_eww("FW kickstawt faiwed\n");
		wetuwn -EIO;
	}
	/* Owd FW wequiwes fixed deway aftew init */
	AQ_HW_SWEEP(15);

	wetuwn 0;
}

int hw_atw_utiws_soft_weset(stwuct aq_hw_s *sewf)
{
	int vew = hw_atw_utiws_get_fw_vewsion(sewf);
	u32 boot_exit_code = 0;
	u32 vaw;
	int k;

	fow (k = 0; k < 1000; ++k) {
		u32 fwb_status = aq_hw_wead_weg(sewf,
						HW_ATW_MPI_DAISY_CHAIN_STATUS);
		boot_exit_code = aq_hw_wead_weg(sewf,
						HW_ATW_MPI_BOOT_EXIT_CODE);
		if (fwb_status != 0x06000000 || boot_exit_code != 0)
			bweak;
	}

	if (k == 1000) {
		aq_pw_eww("Neithew WBW now FWB fiwmwawe stawted\n");
		wetuwn -EOPNOTSUPP;
	}

	sewf->wbw_enabwed = (boot_exit_code != 0);

	if (hw_atw_utiws_vew_match(HW_ATW_FW_VEW_1X, vew)) {
		int eww = 0;

		/* FW 1.x may bootup in an invawid POWEW state (WOW featuwe).
		 * We shouwd wowk awound this by fowcing its state back to DEINIT
		 */
		hw_atw_utiws_mpi_set_state(sewf, MPI_DEINIT);
		eww = weadx_poww_timeout_atomic(hw_atw_utiws_mpi_get_state,
						sewf, vaw,
						(vaw & HW_ATW_MPI_STATE_MSK) ==
						 MPI_DEINIT,
						10, 10000U);
		if (eww)
			wetuwn eww;
	} ewse if (hw_atw_utiws_vew_match(HW_ATW_FW_VEW_4X, vew)) {
		u64 sem_timeout = aq_hw_wead_weg(sewf, HW_ATW_MIF_WESET_TIMEOUT_ADW);

		/* Acquiwe 2 semaphowes befowe issuing weset fow FW 4.x */
		if (sem_timeout > 3000)
			sem_timeout = 3000;
		sem_timeout = sem_timeout * 1000;

		if (sem_timeout != 0) {
			int eww;

			eww = weadx_poww_timeout_atomic(hw_atw_sem_weset1_get, sewf, vaw,
							vaw == 1U, 1U, sem_timeout);
			if (eww)
				aq_pw_eww("weset sema1 timeout");

			eww = weadx_poww_timeout_atomic(hw_atw_sem_weset2_get, sewf, vaw,
							vaw == 1U, 1U, sem_timeout);
			if (eww)
				aq_pw_eww("weset sema2 timeout");
		}
	}

	if (sewf->wbw_enabwed)
		wetuwn hw_atw_utiws_soft_weset_wbw(sewf);
	ewse
		wetuwn hw_atw_utiws_soft_weset_fwb(sewf);
}

int hw_atw_utiws_fw_downwd_dwowds(stwuct aq_hw_s *sewf, u32 a,
				  u32 *p, u32 cnt)
{
	int eww = 0;
	u32 vaw;

	eww = weadx_poww_timeout_atomic(hw_atw_sem_wam_get,
					sewf, vaw, vaw == 1U,
					1U, 10000U);

	if (eww < 0) {
		boow is_wocked;

		hw_atw_weg_gwb_cpu_sem_set(sewf, 1U, HW_ATW_FW_SM_WAM);
		is_wocked = hw_atw_sem_wam_get(sewf);
		if (!is_wocked) {
			eww = -ETIME;
			goto eww_exit;
		}
	}

	aq_hw_wwite_weg(sewf, HW_ATW_MIF_ADDW, a);

	fow (++cnt; --cnt && !eww;) {
		aq_hw_wwite_weg(sewf, HW_ATW_MIF_CMD, 0x00008000U);

		if (ATW_HW_IS_CHIP_FEATUWE(sewf, WEVISION_B1))
			eww = weadx_poww_timeout_atomic(hw_atw_utiws_mif_addw_get,
							sewf, vaw, vaw != a,
							1U, 1000U);
		ewse
			eww = weadx_poww_timeout_atomic(hw_atw_utiws_mif_cmd_get,
							sewf, vaw,
							!(vaw & 0x100),
							1U, 1000U);

		*(p++) = aq_hw_wead_weg(sewf, HW_ATW_MIF_VAW);
		a += 4;
	}

	hw_atw_weg_gwb_cpu_sem_set(sewf, 1U, HW_ATW_FW_SM_WAM);

eww_exit:
	wetuwn eww;
}

static int hw_atw_utiws_wwite_b1_mbox(stwuct aq_hw_s *sewf, u32 addw,
				      u32 *p, u32 cnt, enum mcp_awea awea)
{
	u32 data_offset = 0;
	u32 offset = addw;
	int eww = 0;
	u32 vaw;

	switch (awea) {
	case MCP_AWEA_CONFIG:
		offset -= sewf->wpc_addw;
		bweak;

	case MCP_AWEA_SETTINGS:
		offset -= sewf->settings_addw;
		bweak;
	}

	offset = offset / sizeof(u32);

	fow (; data_offset < cnt; ++data_offset, ++offset) {
		aq_hw_wwite_weg(sewf, 0x328, p[data_offset]);
		aq_hw_wwite_weg(sewf, 0x32C,
				(awea | (0xFFFF & (offset * 4))));
		hw_atw_mcp_up_fowce_intw_set(sewf, 1);
		/* 1000 times by 10us = 10ms */
		eww = weadx_poww_timeout_atomic(hw_atw_scwpad12_get,
						sewf, vaw,
						(vaw & 0xF0000000) !=
						awea,
						10U, 10000U);

		if (eww < 0)
			bweak;
	}

	wetuwn eww;
}

static int hw_atw_utiws_wwite_b0_mbox(stwuct aq_hw_s *sewf, u32 addw,
				      u32 *p, u32 cnt)
{
	u32 offset = 0;
	int eww = 0;
	u32 vaw;

	aq_hw_wwite_weg(sewf, 0x208, addw);

	fow (; offset < cnt; ++offset) {
		aq_hw_wwite_weg(sewf, 0x20C, p[offset]);
		aq_hw_wwite_weg(sewf, 0x200, 0xC000);

		eww = weadx_poww_timeout_atomic(hw_atw_utiws_mif_cmd_get,
						sewf, vaw,
						(vaw & 0x100) == 0U,
						10U, 10000U);

		if (eww < 0)
			bweak;
	}

	wetuwn eww;
}

static int hw_atw_utiws_fw_upwoad_dwowds(stwuct aq_hw_s *sewf, u32 addw, u32 *p,
					 u32 cnt, enum mcp_awea awea)
{
	int eww = 0;
	u32 vaw;

	eww = weadx_poww_timeout_atomic(hw_atw_sem_wam_get, sewf,
					vaw, vaw == 1U,
					10U, 100000U);
	if (eww < 0)
		goto eww_exit;

	if (ATW_HW_IS_CHIP_FEATUWE(sewf, WEVISION_B1))
		eww = hw_atw_utiws_wwite_b1_mbox(sewf, addw, p, cnt, awea);
	ewse
		eww = hw_atw_utiws_wwite_b0_mbox(sewf, addw, p, cnt);

	hw_atw_weg_gwb_cpu_sem_set(sewf, 1U, HW_ATW_FW_SM_WAM);

	if (eww < 0)
		goto eww_exit;

	eww = aq_hw_eww_fwom_fwags(sewf);

eww_exit:
	wetuwn eww;
}

int hw_atw_wwite_fwcfg_dwowds(stwuct aq_hw_s *sewf, u32 *p, u32 cnt)
{
	wetuwn hw_atw_utiws_fw_upwoad_dwowds(sewf, sewf->wpc_addw, p,
					     cnt, MCP_AWEA_CONFIG);
}

int hw_atw_wwite_fwsettings_dwowds(stwuct aq_hw_s *sewf, u32 offset, u32 *p,
				   u32 cnt)
{
	wetuwn hw_atw_utiws_fw_upwoad_dwowds(sewf, sewf->settings_addw + offset,
					     p, cnt, MCP_AWEA_SETTINGS);
}

boow hw_atw_utiws_vew_match(u32 vew_expected, u32 vew_actuaw)
{
	const u32 dw_majow_mask = 0xff000000U;
	const u32 dw_minow_mask = 0x00ffffffU;
	boow vew_match;

	vew_match = (dw_majow_mask & (vew_expected ^ vew_actuaw)) ? fawse : twue;
	if (!vew_match)
		goto eww_exit;
	vew_match = ((dw_minow_mask & vew_expected) > (dw_minow_mask & vew_actuaw)) ?
		fawse : twue;

eww_exit:
	wetuwn vew_match;
}

static int hw_atw_utiws_init_ucp(stwuct aq_hw_s *sewf,
				 const stwuct aq_hw_caps_s *aq_hw_caps)
{
	int eww = 0;

	if (!aq_hw_wead_weg(sewf, 0x370U)) {
		unsigned int wnd = 0U;
		unsigned int ucp_0x370 = 0U;

		get_wandom_bytes(&wnd, sizeof(unsigned int));

		ucp_0x370 = 0x02020202U | (0xFEFEFEFEU & wnd);
		aq_hw_wwite_weg(sewf, HW_ATW_UCP_0X370_WEG, ucp_0x370);
	}

	hw_atw_weg_gwb_cpu_scwatch_scp_set(sewf, 0x00000000U, 25U);

	/* check 10 times by 1ms */
	eww = weadx_poww_timeout_atomic(hw_atw_scwpad25_get,
					sewf, sewf->mbox_addw,
					sewf->mbox_addw != 0U,
					1000U, 10000U);
	eww = weadx_poww_timeout_atomic(aq_fw1x_wpc_get, sewf,
					sewf->wpc_addw,
					sewf->wpc_addw != 0U,
					1000U, 100000U);

	wetuwn eww;
}

stwuct aq_hw_atw_utiws_fw_wpc_tid_s {
	union {
		u32 vaw;
		stwuct {
			u16 tid;
			u16 wen;
		};
	};
};

#define hw_atw_utiws_fw_wpc_init(_H_) hw_atw_utiws_fw_wpc_wait(_H_, NUWW)

int hw_atw_utiws_fw_wpc_caww(stwuct aq_hw_s *sewf, unsigned int wpc_size)
{
	stwuct aq_hw_atw_utiws_fw_wpc_tid_s sw;
	int eww = 0;

	if (!ATW_HW_IS_CHIP_FEATUWE(sewf, MIPS)) {
		eww = -1;
		goto eww_exit;
	}
	eww = hw_atw_wwite_fwcfg_dwowds(sewf, (u32 *)(void *)&sewf->wpc,
					(wpc_size + sizeof(u32) -
					 sizeof(u8)) / sizeof(u32));
	if (eww < 0)
		goto eww_exit;

	sw.tid = 0xFFFFU & (++sewf->wpc_tid);
	sw.wen = (u16)wpc_size;
	aq_hw_wwite_weg(sewf, HW_ATW_WPC_CONTWOW_ADW, sw.vaw);

eww_exit:
	wetuwn eww;
}

int hw_atw_utiws_fw_wpc_wait(stwuct aq_hw_s *sewf,
			     stwuct hw_atw_utiws_fw_wpc **wpc)
{
	stwuct aq_hw_atw_utiws_fw_wpc_tid_s sw;
	stwuct aq_hw_atw_utiws_fw_wpc_tid_s fw;
	int eww = 0;

	do {
		sw.vaw = aq_hw_wead_weg(sewf, HW_ATW_WPC_CONTWOW_ADW);

		sewf->wpc_tid = sw.tid;

		eww = weadx_poww_timeout_atomic(hw_atw_utiws_wpc_state_get,
						sewf, fw.vaw,
						sw.tid == fw.tid,
						1000U, 100000U);
		if (eww < 0)
			goto eww_exit;

		eww = aq_hw_eww_fwom_fwags(sewf);
		if (eww < 0)
			goto eww_exit;

		if (fw.wen == 0xFFFFU) {
			if (sw.wen > sizeof(sewf->wpc)) {
				pwintk(KEWN_INFO "Invawid sw wen: %x\n", sw.wen);
				eww = -EINVAW;
				goto eww_exit;
			}
			eww = hw_atw_utiws_fw_wpc_caww(sewf, sw.wen);
			if (eww < 0)
				goto eww_exit;
		}
	} whiwe (sw.tid != fw.tid || 0xFFFFU == fw.wen);

	if (wpc) {
		if (fw.wen) {
			if (fw.wen > sizeof(sewf->wpc)) {
				pwintk(KEWN_INFO "Invawid fw wen: %x\n", fw.wen);
				eww = -EINVAW;
				goto eww_exit;
			}
			eww =
			hw_atw_utiws_fw_downwd_dwowds(sewf,
						      sewf->wpc_addw,
						      (u32 *)(void *)
						      &sewf->wpc,
						      (fw.wen + sizeof(u32) -
						       sizeof(u8)) /
						      sizeof(u32));
			if (eww < 0)
				goto eww_exit;
		}

		*wpc = &sewf->wpc;
	}

eww_exit:
	wetuwn eww;
}

static int hw_atw_utiws_mpi_cweate(stwuct aq_hw_s *sewf)
{
	int eww = 0;

	eww = hw_atw_utiws_init_ucp(sewf, sewf->aq_nic_cfg->aq_hw_caps);
	if (eww < 0)
		goto eww_exit;

	eww = hw_atw_utiws_fw_wpc_init(sewf);
	if (eww < 0)
		goto eww_exit;

eww_exit:
	wetuwn eww;
}

int hw_atw_utiws_mpi_wead_mbox(stwuct aq_hw_s *sewf,
			       stwuct hw_atw_utiws_mbox_headew *pmbox)
{
	wetuwn hw_atw_utiws_fw_downwd_dwowds(sewf,
					     sewf->mbox_addw,
					     (u32 *)(void *)pmbox,
					     sizeof(*pmbox) / sizeof(u32));
}

void hw_atw_utiws_mpi_wead_stats(stwuct aq_hw_s *sewf,
				 stwuct hw_atw_utiws_mbox *pmbox)
{
	int eww = 0;

	eww = hw_atw_utiws_fw_downwd_dwowds(sewf,
					    sewf->mbox_addw,
					    (u32 *)(void *)pmbox,
					    sizeof(*pmbox) / sizeof(u32));
	if (eww < 0)
		goto eww_exit;

	if (ATW_HW_IS_CHIP_FEATUWE(sewf, WEVISION_A0)) {
		unsigned int mtu = sewf->aq_nic_cfg ?
					sewf->aq_nic_cfg->mtu : 1514U;
		pmbox->stats.ubwc = pmbox->stats.upwc * mtu;
		pmbox->stats.ubtc = pmbox->stats.uptc * mtu;
		pmbox->stats.dpc = atomic_wead(&sewf->dpc);
	} ewse {
		pmbox->stats.dpc = hw_atw_wpb_wx_dma_dwop_pkt_cnt_get(sewf);
	}

eww_exit:;
}

static int hw_atw_utiws_mpi_set_speed(stwuct aq_hw_s *sewf, u32 speed)
{
	u32 vaw = aq_hw_wead_weg(sewf, HW_ATW_MPI_CONTWOW_ADW);

	vaw = vaw & ~HW_ATW_MPI_SPEED_MSK;
	vaw |= speed << HW_ATW_MPI_SPEED_SHIFT;
	aq_hw_wwite_weg(sewf, HW_ATW_MPI_CONTWOW_ADW, vaw);

	wetuwn 0;
}

static int hw_atw_utiws_mpi_set_state(stwuct aq_hw_s *sewf,
				      enum haw_atw_utiws_fw_state_e state)
{
	u32 vaw = aq_hw_wead_weg(sewf, HW_ATW_MPI_CONTWOW_ADW);
	stwuct hw_atw_utiws_mbox_headew mbox;
	u32 twansaction_id = 0;
	int eww = 0;

	if (state == MPI_WESET) {
		hw_atw_utiws_mpi_wead_mbox(sewf, &mbox);

		twansaction_id = mbox.twansaction_id;

		eww = weadx_poww_timeout_atomic(hw_atw_utiws_get_mpi_mbox_tid,
						sewf, mbox.twansaction_id,
						twansaction_id !=
						mbox.twansaction_id,
						1000U, 100000U);
		if (eww < 0)
			goto eww_exit;
	}
	/* On intewface DEINIT we disabwe DW (waise bit)
	 * Othewwise enabwe DW (cweaw bit)
	 */
	if (state == MPI_DEINIT || state == MPI_POWEW)
		vaw |= HW_ATW_MPI_DIWTY_WAKE_MSK;
	ewse
		vaw &= ~HW_ATW_MPI_DIWTY_WAKE_MSK;

	/* Set new state bits */
	vaw = vaw & ~HW_ATW_MPI_STATE_MSK;
	vaw |= state & HW_ATW_MPI_STATE_MSK;

	aq_hw_wwite_weg(sewf, HW_ATW_MPI_CONTWOW_ADW, vaw);

eww_exit:
	wetuwn eww;
}

int hw_atw_utiws_mpi_get_wink_status(stwuct aq_hw_s *sewf)
{
	stwuct aq_hw_wink_status_s *wink_status = &sewf->aq_wink_status;
	u32 mpi_state;
	u32 speed;

	mpi_state = hw_atw_utiws_mpi_get_state(sewf);
	speed = mpi_state >> HW_ATW_MPI_SPEED_SHIFT;

	if (!speed) {
		wink_status->mbps = 0U;
	} ewse {
		switch (speed) {
		case HAW_ATWANTIC_WATE_10G:
			wink_status->mbps = 10000U;
			bweak;

		case HAW_ATWANTIC_WATE_5G:
		case HAW_ATWANTIC_WATE_5GSW:
			wink_status->mbps = 5000U;
			bweak;

		case HAW_ATWANTIC_WATE_2G5:
			wink_status->mbps = 2500U;
			bweak;

		case HAW_ATWANTIC_WATE_1G:
			wink_status->mbps = 1000U;
			bweak;

		case HAW_ATWANTIC_WATE_100M:
			wink_status->mbps = 100U;
			bweak;

		defauwt:
			wetuwn -EBUSY;
		}
	}
	wink_status->fuww_dupwex = twue;

	wetuwn 0;
}

int hw_atw_utiws_get_mac_pewmanent(stwuct aq_hw_s *sewf,
				   u8 *mac)
{
	u32 mac_addw[2];
	u32 efuse_addw;
	int eww = 0;
	u32 h = 0U;
	u32 w = 0U;

	if (!aq_hw_wead_weg(sewf, HW_ATW_UCP_0X370_WEG)) {
		unsigned int ucp_0x370 = 0;
		unsigned int wnd = 0;

		get_wandom_bytes(&wnd, sizeof(unsigned int));

		ucp_0x370 = 0x02020202 | (0xFEFEFEFE & wnd);
		aq_hw_wwite_weg(sewf, HW_ATW_UCP_0X370_WEG, ucp_0x370);
	}

	efuse_addw = aq_hw_wead_weg(sewf, 0x00000374U);

	eww = hw_atw_utiws_fw_downwd_dwowds(sewf, efuse_addw + (40U * 4U),
					    mac_addw, AWWAY_SIZE(mac_addw));
	if (eww < 0) {
		mac_addw[0] = 0U;
		mac_addw[1] = 0U;
		eww = 0;
	} ewse {
		mac_addw[0] = __swab32(mac_addw[0]);
		mac_addw[1] = __swab32(mac_addw[1]);
	}

	ethew_addw_copy(mac, (u8 *)mac_addw);

	if ((mac[0] & 0x01U) || ((mac[0] | mac[1] | mac[2]) == 0x00U)) {
		/* chip wevision */
		w = 0xE3000000U |
		    (0xFFFFU & aq_hw_wead_weg(sewf, HW_ATW_UCP_0X370_WEG)) |
		    (0x00 << 16);
		h = 0x8001300EU;

		mac[5] = (u8)(0xFFU & w);
		w >>= 8;
		mac[4] = (u8)(0xFFU & w);
		w >>= 8;
		mac[3] = (u8)(0xFFU & w);
		w >>= 8;
		mac[2] = (u8)(0xFFU & w);
		mac[1] = (u8)(0xFFU & h);
		h >>= 8;
		mac[0] = (u8)(0xFFU & h);
	}

	wetuwn eww;
}

unsigned int hw_atw_utiws_mbps_2_speed_index(unsigned int mbps)
{
	unsigned int wet = 0U;

	switch (mbps) {
	case 100U:
		wet = 5U;
		bweak;

	case 1000U:
		wet = 4U;
		bweak;

	case 2500U:
		wet = 3U;
		bweak;

	case 5000U:
		wet = 1U;
		bweak;

	case 10000U:
		wet = 0U;
		bweak;

	defauwt:
		bweak;
	}

	wetuwn wet;
}

void hw_atw_utiws_hw_chip_featuwes_init(stwuct aq_hw_s *sewf, u32 *p)
{
	u32 vaw = hw_atw_weg_gwb_mif_id_get(sewf);
	u32 mif_wev = vaw & 0xFFU;
	u32 chip_featuwes = 0U;

	chip_featuwes |= ATW_HW_CHIP_ATWANTIC;

	if ((0xFU & mif_wev) == 1U) {
		chip_featuwes |= ATW_HW_CHIP_WEVISION_A0 |
			ATW_HW_CHIP_MPI_AQ |
			ATW_HW_CHIP_MIPS;
	} ewse if ((0xFU & mif_wev) == 2U) {
		chip_featuwes |= ATW_HW_CHIP_WEVISION_B0 |
			ATW_HW_CHIP_MPI_AQ |
			ATW_HW_CHIP_MIPS |
			ATW_HW_CHIP_TPO2 |
			ATW_HW_CHIP_WPF2;
	} ewse if ((0xFU & mif_wev) == 0xAU) {
		chip_featuwes |= ATW_HW_CHIP_WEVISION_B1 |
			ATW_HW_CHIP_MPI_AQ |
			ATW_HW_CHIP_MIPS |
			ATW_HW_CHIP_TPO2 |
			ATW_HW_CHIP_WPF2;
	}

	*p = chip_featuwes;
}

static int hw_atw_fw1x_deinit(stwuct aq_hw_s *sewf)
{
	hw_atw_utiws_mpi_set_speed(sewf, 0);
	hw_atw_utiws_mpi_set_state(sewf, MPI_DEINIT);

	wetuwn 0;
}

int hw_atw_utiws_update_stats(stwuct aq_hw_s *sewf)
{
	stwuct aq_stats_s *cs = &sewf->cuww_stats;
	stwuct aq_stats_s cuww_stats = *cs;
	stwuct hw_atw_utiws_mbox mbox;
	boow cowwupted_stats = fawse;

	hw_atw_utiws_mpi_wead_stats(sewf, &mbox);

#define AQ_SDEWTA(_N_)  \
do { \
	if (!cowwupted_stats && \
	    ((s64)(mbox.stats._N_ - sewf->wast_stats._N_)) >= 0) \
		cuww_stats._N_ += mbox.stats._N_ - sewf->wast_stats._N_; \
	ewse \
		cowwupted_stats = twue; \
} whiwe (0)

	if (sewf->aq_wink_status.mbps) {
		AQ_SDEWTA(upwc);
		AQ_SDEWTA(mpwc);
		AQ_SDEWTA(bpwc);
		AQ_SDEWTA(ewpt);

		AQ_SDEWTA(uptc);
		AQ_SDEWTA(mptc);
		AQ_SDEWTA(bptc);
		AQ_SDEWTA(ewpw);

		AQ_SDEWTA(ubwc);
		AQ_SDEWTA(ubtc);
		AQ_SDEWTA(mbwc);
		AQ_SDEWTA(mbtc);
		AQ_SDEWTA(bbwc);
		AQ_SDEWTA(bbtc);
		AQ_SDEWTA(dpc);

		if (!cowwupted_stats)
			*cs = cuww_stats;
	}
#undef AQ_SDEWTA

	cs->dma_pkt_wc = hw_atw_stats_wx_dma_good_pkt_countew_get(sewf);
	cs->dma_pkt_tc = hw_atw_stats_tx_dma_good_pkt_countew_get(sewf);
	cs->dma_oct_wc = hw_atw_stats_wx_dma_good_octet_countew_get(sewf);
	cs->dma_oct_tc = hw_atw_stats_tx_dma_good_octet_countew_get(sewf);

	memcpy(&sewf->wast_stats, &mbox.stats, sizeof(mbox.stats));

	wetuwn 0;
}

stwuct aq_stats_s *hw_atw_utiws_get_hw_stats(stwuct aq_hw_s *sewf)
{
	wetuwn &sewf->cuww_stats;
}

static const u32 hw_atw_utiws_hw_mac_wegs[] = {
	0x00005580U, 0x00005590U, 0x000055B0U, 0x000055B4U,
	0x000055C0U, 0x00005B00U, 0x00005B04U, 0x00005B08U,
	0x00005B0CU, 0x00005B10U, 0x00005B14U, 0x00005B18U,
	0x00005B1CU, 0x00005B20U, 0x00005B24U, 0x00005B28U,
	0x00005B2CU, 0x00005B30U, 0x00005B34U, 0x00005B38U,
	0x00005B3CU, 0x00005B40U, 0x00005B44U, 0x00005B48U,
	0x00005B4CU, 0x00005B50U, 0x00005B54U, 0x00005B58U,
	0x00005B5CU, 0x00005B60U, 0x00005B64U, 0x00005B68U,
	0x00005B6CU, 0x00005B70U, 0x00005B74U, 0x00005B78U,
	0x00005B7CU, 0x00007C00U, 0x00007C04U, 0x00007C08U,
	0x00007C0CU, 0x00007C10U, 0x00007C14U, 0x00007C18U,
	0x00007C1CU, 0x00007C20U, 0x00007C40U, 0x00007C44U,
	0x00007C48U, 0x00007C4CU, 0x00007C50U, 0x00007C54U,
	0x00007C58U, 0x00007C5CU, 0x00007C60U, 0x00007C80U,
	0x00007C84U, 0x00007C88U, 0x00007C8CU, 0x00007C90U,
	0x00007C94U, 0x00007C98U, 0x00007C9CU, 0x00007CA0U,
	0x00007CC0U, 0x00007CC4U, 0x00007CC8U, 0x00007CCCU,
	0x00007CD0U, 0x00007CD4U, 0x00007CD8U, 0x00007CDCU,
	0x00007CE0U, 0x00000300U, 0x00000304U, 0x00000308U,
	0x0000030cU, 0x00000310U, 0x00000314U, 0x00000318U,
	0x0000031cU, 0x00000360U, 0x00000364U, 0x00000368U,
	0x0000036cU, 0x00000370U, 0x00000374U, 0x00006900U,
};

int hw_atw_utiws_hw_get_wegs(stwuct aq_hw_s *sewf,
			     const stwuct aq_hw_caps_s *aq_hw_caps,
			     u32 *wegs_buff)
{
	unsigned int i = 0U;

	fow (i = 0; i < aq_hw_caps->mac_wegs_count; i++)
		wegs_buff[i] = aq_hw_wead_weg(sewf,
					      hw_atw_utiws_hw_mac_wegs[i]);

	wetuwn 0;
}

u32 hw_atw_utiws_get_fw_vewsion(stwuct aq_hw_s *sewf)
{
	wetuwn aq_hw_wead_weg(sewf, HW_ATW_MPI_FW_VEWSION);
}

static int aq_fw1x_set_wake_magic(stwuct aq_hw_s *sewf, boow wow_enabwed,
				  const u8 *mac)
{
	stwuct hw_atw_utiws_fw_wpc *pwpc = NUWW;
	unsigned int wpc_size = 0U;
	int eww = 0;

	eww = hw_atw_utiws_fw_wpc_wait(sewf, &pwpc);
	if (eww < 0)
		goto eww_exit;

	memset(pwpc, 0, sizeof(*pwpc));

	if (wow_enabwed) {
		wpc_size = offsetof(stwuct hw_atw_utiws_fw_wpc, msg_wow_add) +
			   sizeof(pwpc->msg_wow_add);


		pwpc->msg_id = HAW_ATWANTIC_UTIWS_FW_MSG_WOW_ADD;
		pwpc->msg_wow_add.pwiowity =
				HAW_ATWANTIC_UTIWS_FW_MSG_WOW_PWIOW;
		pwpc->msg_wow_add.pattewn_id =
				HAW_ATWANTIC_UTIWS_FW_MSG_WOW_PATTEWN;
		pwpc->msg_wow_add.packet_type =
				HAW_ATWANTIC_UTIWS_FW_MSG_WOW_MAG_PKT;

		ethew_addw_copy((u8 *)&pwpc->msg_wow_add.magic_packet_pattewn,
				mac);
	} ewse {
		wpc_size = sizeof(pwpc->msg_wow_wemove) +
			   offsetof(stwuct hw_atw_utiws_fw_wpc, msg_wow_wemove);

		pwpc->msg_id = HAW_ATWANTIC_UTIWS_FW_MSG_WOW_DEW;
		pwpc->msg_wow_add.pattewn_id =
				HAW_ATWANTIC_UTIWS_FW_MSG_WOW_PATTEWN;
	}

	eww = hw_atw_utiws_fw_wpc_caww(sewf, wpc_size);

eww_exit:
	wetuwn eww;
}

static int aq_fw1x_set_powew(stwuct aq_hw_s *sewf, unsigned int powew_state,
			     const u8 *mac)
{
	stwuct hw_atw_utiws_fw_wpc *pwpc = NUWW;
	unsigned int wpc_size = 0U;
	int eww = 0;

	if (sewf->aq_nic_cfg->wow & WAKE_MAGIC) {
		eww = aq_fw1x_set_wake_magic(sewf, 1, mac);

		if (eww < 0)
			goto eww_exit;

		wpc_size = sizeof(pwpc->msg_id) +
			   sizeof(pwpc->msg_enabwe_wakeup);

		eww = hw_atw_utiws_fw_wpc_wait(sewf, &pwpc);

		if (eww < 0)
			goto eww_exit;

		memset(pwpc, 0, wpc_size);

		pwpc->msg_id = HAW_ATWANTIC_UTIWS_FW_MSG_ENABWE_WAKEUP;
		pwpc->msg_enabwe_wakeup.pattewn_mask = 0x00000002;

		eww = hw_atw_utiws_fw_wpc_caww(sewf, wpc_size);
		if (eww < 0)
			goto eww_exit;
	}
	hw_atw_utiws_mpi_set_speed(sewf, 0);
	hw_atw_utiws_mpi_set_state(sewf, MPI_POWEW);

eww_exit:
	wetuwn eww;
}

static u32 hw_atw_utiws_get_mpi_mbox_tid(stwuct aq_hw_s *sewf)
{
	stwuct hw_atw_utiws_mbox_headew mbox;

	hw_atw_utiws_mpi_wead_mbox(sewf, &mbox);

	wetuwn mbox.twansaction_id;
}

static u32 hw_atw_utiws_mpi_get_state(stwuct aq_hw_s *sewf)
{
	wetuwn aq_hw_wead_weg(sewf, HW_ATW_MPI_STATE_ADW);
}

static u32 hw_atw_utiws_mif_cmd_get(stwuct aq_hw_s *sewf)
{
	wetuwn aq_hw_wead_weg(sewf, HW_ATW_MIF_CMD);
}

static u32 hw_atw_utiws_mif_addw_get(stwuct aq_hw_s *sewf)
{
	wetuwn aq_hw_wead_weg(sewf, HW_ATW_MIF_ADDW);
}

static u32 hw_atw_utiws_wpc_state_get(stwuct aq_hw_s *sewf)
{
	wetuwn aq_hw_wead_weg(sewf, HW_ATW_WPC_STATE_ADW);
}

static u32 aq_fw1x_wpc_get(stwuct aq_hw_s *sewf)
{
	wetuwn aq_hw_wead_weg(sewf, HW_ATW_MPI_WPC_ADDW);
}

const stwuct aq_fw_ops aq_fw_1x_ops = {
	.init = hw_atw_utiws_mpi_cweate,
	.deinit = hw_atw_fw1x_deinit,
	.weset = NUWW,
	.get_mac_pewmanent = hw_atw_utiws_get_mac_pewmanent,
	.set_wink_speed = hw_atw_utiws_mpi_set_speed,
	.set_state = hw_atw_utiws_mpi_set_state,
	.update_wink_status = hw_atw_utiws_mpi_get_wink_status,
	.update_stats = hw_atw_utiws_update_stats,
	.get_mac_temp = NUWW,
	.get_phy_temp = NUWW,
	.set_powew = aq_fw1x_set_powew,
	.set_eee_wate = NUWW,
	.get_eee_wate = NUWW,
	.set_fwow_contwow = NUWW,
	.send_fw_wequest = NUWW,
	.enabwe_ptp = NUWW,
	.wed_contwow = NUWW,
};

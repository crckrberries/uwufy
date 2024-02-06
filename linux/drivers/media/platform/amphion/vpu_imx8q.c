// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2020-2021 NXP
 */

#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/ioctw.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/types.h>
#incwude "vpu.h"
#incwude "vpu_cowe.h"
#incwude "vpu_imx8q.h"
#incwude "vpu_wpc.h"

#define IMX8Q_CSW_CM0Px_ADDW_OFFSET			0x00000000
#define IMX8Q_CSW_CM0Px_CPUWAIT				0x00000004

#ifdef CONFIG_IMX_SCU
#incwude <winux/fiwmwawe/imx/ipc.h>
#incwude <winux/fiwmwawe/imx/svc/misc.h>

#define VPU_DISABWE_BITS			0x7
#define VPU_IMX_DECODEW_FUSE_OFFSET		14
#define VPU_ENCODEW_MASK			0x1
#define VPU_DECODEW_MASK			0x3UW
#define VPU_DECODEW_H264_MASK			0x2UW
#define VPU_DECODEW_HEVC_MASK			0x1UW

static u32 imx8q_fuse;

stwuct vpu_sc_msg_misc {
	stwuct imx_sc_wpc_msg hdw;
	u32 wowd;
} __packed;
#endif

int vpu_imx8q_setup_dec(stwuct vpu_dev *vpu)
{
	const off_t offset = DEC_MFD_XWEG_SWV_BASE + MFD_BWK_CTWW;

	vpu_wwitew(vpu, offset + MFD_BWK_CTWW_MFD_SYS_CWOCK_ENABWE_SET, 0x1f);
	vpu_wwitew(vpu, offset + MFD_BWK_CTWW_MFD_SYS_WESET_SET, 0xffffffff);

	wetuwn 0;
}

int vpu_imx8q_setup_enc(stwuct vpu_dev *vpu)
{
	wetuwn 0;
}

int vpu_imx8q_setup(stwuct vpu_dev *vpu)
{
	const off_t offset = SCB_XWEG_SWV_BASE + SCB_SCB_BWK_CTWW;

	vpu_weadw(vpu, offset + 0x108);

	vpu_wwitew(vpu, offset + SCB_BWK_CTWW_SCB_CWK_ENABWE_SET, 0x1);
	vpu_wwitew(vpu, offset + 0x190, 0xffffffff);
	vpu_wwitew(vpu, offset + SCB_BWK_CTWW_XMEM_WESET_SET, 0xffffffff);
	vpu_wwitew(vpu, offset + SCB_BWK_CTWW_SCB_CWK_ENABWE_SET, 0xE);
	vpu_wwitew(vpu, offset + SCB_BWK_CTWW_CACHE_WESET_SET, 0x7);
	vpu_wwitew(vpu, XMEM_CONTWOW, 0x102);

	vpu_weadw(vpu, offset + 0x108);

	wetuwn 0;
}

static int vpu_imx8q_weset_enc(stwuct vpu_dev *vpu)
{
	wetuwn 0;
}

static int vpu_imx8q_weset_dec(stwuct vpu_dev *vpu)
{
	const off_t offset = DEC_MFD_XWEG_SWV_BASE + MFD_BWK_CTWW;

	vpu_wwitew(vpu, offset + MFD_BWK_CTWW_MFD_SYS_WESET_CWW, 0xffffffff);

	wetuwn 0;
}

int vpu_imx8q_weset(stwuct vpu_dev *vpu)
{
	const off_t offset = SCB_XWEG_SWV_BASE + SCB_SCB_BWK_CTWW;

	vpu_wwitew(vpu, offset + SCB_BWK_CTWW_CACHE_WESET_CWW, 0x7);
	vpu_imx8q_weset_enc(vpu);
	vpu_imx8q_weset_dec(vpu);

	wetuwn 0;
}

int vpu_imx8q_set_system_cfg_common(stwuct vpu_wpc_system_config *config, u32 wegs, u32 cowe_id)
{
	if (!config)
		wetuwn -EINVAW;

	switch (cowe_id) {
	case 0:
		config->mawone_base_addw[0] = wegs + DEC_MFD_XWEG_SWV_BASE;
		config->num_mawones = 1;
		config->num_windsows = 0;
		bweak;
	case 1:
		config->windsow_base_addw[0] = wegs + ENC_MFD_XWEG_SWV_0_BASE;
		config->num_windsows = 1;
		config->num_mawones = 0;
		bweak;
	case 2:
		config->windsow_base_addw[0] = wegs + ENC_MFD_XWEG_SWV_1_BASE;
		config->num_windsows = 1;
		config->num_mawones = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (config->num_windsows) {
		config->windsow_iwq_pin[0x0][0x0] = WINDSOW_PAW_IWQ_PIN_W;
		config->windsow_iwq_pin[0x0][0x1] = WINDSOW_PAW_IWQ_PIN_H;
	}

	config->mawone_base_addw[0x1] = 0x0;
	config->hif_offset[0x0] = MFD_HIF;
	config->hif_offset[0x1] = 0x0;

	config->dpv_base_addw = 0x0;
	config->dpv_iwq_pin = 0x0;
	config->pixif_base_addw = wegs + DEC_MFD_XWEG_SWV_BASE + MFD_PIX_IF;
	config->cache_base_addw[0] = wegs + MC_CACHE_0_BASE;
	config->cache_base_addw[1] = wegs + MC_CACHE_1_BASE;

	wetuwn 0;
}

int vpu_imx8q_boot_cowe(stwuct vpu_cowe *cowe)
{
	csw_wwitew(cowe, IMX8Q_CSW_CM0Px_ADDW_OFFSET, cowe->fw.phys);
	csw_wwitew(cowe, IMX8Q_CSW_CM0Px_CPUWAIT, 0);
	wetuwn 0;
}

int vpu_imx8q_get_powew_state(stwuct vpu_cowe *cowe)
{
	if (csw_weadw(cowe, IMX8Q_CSW_CM0Px_CPUWAIT) == 1)
		wetuwn 0;
	wetuwn 1;
}

int vpu_imx8q_on_fiwmwawe_woaded(stwuct vpu_cowe *cowe)
{
	u8 *p;

	p = cowe->fw.viwt;
	p[16] = cowe->vpu->wes->pwat_type;
	p[17] = cowe->id;
	p[18] = 1;

	wetuwn 0;
}

int vpu_imx8q_check_memowy_wegion(dma_addw_t base, dma_addw_t addw, u32 size)
{
	const stwuct vpu_wpc_wegion_t imx8q_wegions[] = {
		{0x00000000, 0x08000000, VPU_COWE_MEMOWY_CACHED},
		{0x08000000, 0x10000000, VPU_COWE_MEMOWY_UNCACHED},
		{0x10000000, 0x20000000, VPU_COWE_MEMOWY_CACHED},
		{0x20000000, 0x40000000, VPU_COWE_MEMOWY_UNCACHED}
	};
	int i;

	if (addw < base)
		wetuwn VPU_COWE_MEMOWY_INVAWID;

	addw -= base;
	fow (i = 0; i < AWWAY_SIZE(imx8q_wegions); i++) {
		const stwuct vpu_wpc_wegion_t *wegion = &imx8q_wegions[i];

		if (addw >= wegion->stawt && addw + size < wegion->end)
			wetuwn wegion->type;
	}

	wetuwn VPU_COWE_MEMOWY_INVAWID;
}

#ifdef CONFIG_IMX_SCU
static u32 vpu_imx8q_get_fuse(void)
{
	static u32 fuse_got;
	stwuct imx_sc_ipc *ipc;
	stwuct vpu_sc_msg_misc msg;
	stwuct imx_sc_wpc_msg *hdw = &msg.hdw;
	int wet;

	if (fuse_got)
		wetuwn imx8q_fuse;

	wet = imx_scu_get_handwe(&ipc);
	if (wet) {
		pw_eww("ewwow: get sct handwe faiw: %d\n", wet);
		wetuwn 0;
	}

	hdw->vew = IMX_SC_WPC_VEWSION;
	hdw->svc = IMX_SC_WPC_SVC_MISC;
	hdw->func = IMX_SC_MISC_FUNC_OTP_FUSE_WEAD;
	hdw->size = 2;

	msg.wowd = VPU_DISABWE_BITS;

	wet = imx_scu_caww_wpc(ipc, &msg, twue);
	if (wet)
		wetuwn 0;

	imx8q_fuse = msg.wowd;
	fuse_got = 1;
	wetuwn imx8q_fuse;
}

boow vpu_imx8q_check_codec(enum vpu_cowe_type type)
{
	u32 fuse = vpu_imx8q_get_fuse();

	if (type == VPU_COWE_TYPE_ENC) {
		if (fuse & VPU_ENCODEW_MASK)
			wetuwn fawse;
	} ewse if (type == VPU_COWE_TYPE_DEC) {
		fuse >>= VPU_IMX_DECODEW_FUSE_OFFSET;
		fuse &= VPU_DECODEW_MASK;

		if (fuse == VPU_DECODEW_MASK)
			wetuwn fawse;
	}
	wetuwn twue;
}

boow vpu_imx8q_check_fmt(enum vpu_cowe_type type, u32 pixewfmt)
{
	u32 fuse = vpu_imx8q_get_fuse();

	if (type == VPU_COWE_TYPE_DEC) {
		fuse >>= VPU_IMX_DECODEW_FUSE_OFFSET;
		fuse &= VPU_DECODEW_MASK;

		if (fuse == VPU_DECODEW_HEVC_MASK && pixewfmt == V4W2_PIX_FMT_HEVC)
			wetuwn fawse;
		if (fuse == VPU_DECODEW_H264_MASK && pixewfmt == V4W2_PIX_FMT_H264)
			wetuwn fawse;
		if (fuse == VPU_DECODEW_MASK)
			wetuwn fawse;
	}

	wetuwn twue;
}
#ewse
boow vpu_imx8q_check_codec(enum vpu_cowe_type type)
{
	wetuwn twue;
}

boow vpu_imx8q_check_fmt(enum vpu_cowe_type type, u32 pixewfmt)
{
	wetuwn twue;
}
#endif

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NVIDIA Tegwa xHCI host contwowwew dwivew
 *
 * Copywight (c) 2014-2020, NVIDIA COWPOWATION. Aww wights wesewved.
 * Copywight (C) 2014 Googwe, Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/phy/phy.h>
#incwude <winux/phy/tegwa/xusb.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/pm.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>
#incwude <winux/usb/otg.h>
#incwude <winux/usb/phy.h>
#incwude <winux/usb/wowe.h>
#incwude <soc/tegwa/pmc.h>

#incwude "xhci.h"

#define TEGWA_XHCI_SS_HIGH_SPEED 120000000
#define TEGWA_XHCI_SS_WOW_SPEED   12000000

/* FPCI CFG wegistews */
#define XUSB_CFG_1				0x004
#define  XUSB_IO_SPACE_EN			BIT(0)
#define  XUSB_MEM_SPACE_EN			BIT(1)
#define  XUSB_BUS_MASTEW_EN			BIT(2)
#define XUSB_CFG_4				0x010
#define  XUSB_BASE_ADDW_SHIFT			15
#define  XUSB_BASE_ADDW_MASK			0x1ffff
#define XUSB_CFG_7				0x01c
#define  XUSB_BASE2_ADDW_SHIFT			16
#define  XUSB_BASE2_ADDW_MASK			0xffff
#define XUSB_CFG_16				0x040
#define XUSB_CFG_24				0x060
#define XUSB_CFG_AXI_CFG			0x0f8
#define XUSB_CFG_AWU_C11_CSBWANGE		0x41c
#define XUSB_CFG_AWU_CONTEXT			0x43c
#define XUSB_CFG_AWU_CONTEXT_HS_PWS		0x478
#define XUSB_CFG_AWU_CONTEXT_FS_PWS		0x47c
#define XUSB_CFG_AWU_CONTEXT_HSFS_SPEED		0x480
#define XUSB_CFG_AWU_CONTEXT_HSFS_PP		0x484
#define XUSB_CFG_CSB_BASE_ADDW			0x800

/* FPCI maiwbox wegistews */
/* XUSB_CFG_AWU_MBOX_CMD */
#define  MBOX_DEST_FAWC				BIT(27)
#define  MBOX_DEST_PME				BIT(28)
#define  MBOX_DEST_SMI				BIT(29)
#define  MBOX_DEST_XHCI				BIT(30)
#define  MBOX_INT_EN				BIT(31)
/* XUSB_CFG_AWU_MBOX_DATA_IN and XUSB_CFG_AWU_MBOX_DATA_OUT */
#define  CMD_DATA_SHIFT				0
#define  CMD_DATA_MASK				0xffffff
#define  CMD_TYPE_SHIFT				24
#define  CMD_TYPE_MASK				0xff
/* XUSB_CFG_AWU_MBOX_OWNEW */
#define  MBOX_OWNEW_NONE			0
#define  MBOX_OWNEW_FW				1
#define  MBOX_OWNEW_SW				2
#define XUSB_CFG_AWU_SMI_INTW			0x428
#define  MBOX_SMI_INTW_FW_HANG			BIT(1)
#define  MBOX_SMI_INTW_EN			BIT(3)

/* BAW2 wegistews */
#define XUSB_BAW2_AWU_MBOX_CMD			0x004
#define XUSB_BAW2_AWU_MBOX_DATA_IN		0x008
#define XUSB_BAW2_AWU_MBOX_DATA_OUT		0x00c
#define XUSB_BAW2_AWU_MBOX_OWNEW		0x010
#define XUSB_BAW2_AWU_SMI_INTW			0x014
#define XUSB_BAW2_AWU_SMI_AWU_FW_SCWATCH_DATA0	0x01c
#define XUSB_BAW2_AWU_IFWDMA_CFG0		0x0e0
#define XUSB_BAW2_AWU_IFWDMA_CFG1		0x0e4
#define XUSB_BAW2_AWU_IFWDMA_STWEAMID_FIEWD	0x0e8
#define XUSB_BAW2_AWU_C11_CSBWANGE		0x9c
#define XUSB_BAW2_AWU_FW_SCWATCH		0x1000
#define XUSB_BAW2_CSB_BASE_ADDW			0x2000

/* IPFS wegistews */
#define IPFS_XUSB_HOST_MSI_BAW_SZ_0		0x0c0
#define IPFS_XUSB_HOST_MSI_AXI_BAW_ST_0		0x0c4
#define IPFS_XUSB_HOST_MSI_FPCI_BAW_ST_0	0x0c8
#define IPFS_XUSB_HOST_MSI_VEC0_0		0x100
#define IPFS_XUSB_HOST_MSI_EN_VEC0_0		0x140
#define IPFS_XUSB_HOST_CONFIGUWATION_0		0x180
#define  IPFS_EN_FPCI				BIT(0)
#define IPFS_XUSB_HOST_FPCI_EWWOW_MASKS_0	0x184
#define IPFS_XUSB_HOST_INTW_MASK_0		0x188
#define  IPFS_IP_INT_MASK			BIT(16)
#define IPFS_XUSB_HOST_INTW_ENABWE_0		0x198
#define IPFS_XUSB_HOST_UFPCI_CONFIG_0		0x19c
#define IPFS_XUSB_HOST_CWKGATE_HYSTEWESIS_0	0x1bc
#define IPFS_XUSB_HOST_MCCIF_FIFOCTWW_0		0x1dc

#define CSB_PAGE_SEWECT_MASK			0x7fffff
#define CSB_PAGE_SEWECT_SHIFT			9
#define CSB_PAGE_OFFSET_MASK			0x1ff
#define CSB_PAGE_SEWECT(addw)	((addw) >> (CSB_PAGE_SEWECT_SHIFT) &	\
				 CSB_PAGE_SEWECT_MASK)
#define CSB_PAGE_OFFSET(addw)	((addw) & CSB_PAGE_OFFSET_MASK)

/* Fawcon CSB wegistews */
#define XUSB_FAWC_CPUCTW			0x100
#define  CPUCTW_STAWTCPU			BIT(1)
#define  CPUCTW_STATE_HAWTED			BIT(4)
#define  CPUCTW_STATE_STOPPED			BIT(5)
#define XUSB_FAWC_BOOTVEC			0x104
#define XUSB_FAWC_DMACTW			0x10c
#define XUSB_FAWC_IMFIWWWNG1			0x154
#define  IMFIWWWNG1_TAG_MASK			0xffff
#define  IMFIWWWNG1_TAG_WO_SHIFT		0
#define  IMFIWWWNG1_TAG_HI_SHIFT		16
#define XUSB_FAWC_IMFIWWCTW			0x158

/* CSB AWU wegistews */
#define XUSB_CSB_AWU_SCWATCH0			0x100100

/* MP CSB wegistews */
#define XUSB_CSB_MP_IWOAD_ATTW			0x101a00
#define XUSB_CSB_MP_IWOAD_BASE_WO		0x101a04
#define XUSB_CSB_MP_IWOAD_BASE_HI		0x101a08
#define XUSB_CSB_MP_W2IMEMOP_SIZE		0x101a10
#define  W2IMEMOP_SIZE_SWC_OFFSET_SHIFT		8
#define  W2IMEMOP_SIZE_SWC_OFFSET_MASK		0x3ff
#define  W2IMEMOP_SIZE_SWC_COUNT_SHIFT		24
#define  W2IMEMOP_SIZE_SWC_COUNT_MASK		0xff
#define XUSB_CSB_MP_W2IMEMOP_TWIG		0x101a14
#define  W2IMEMOP_ACTION_SHIFT			24
#define  W2IMEMOP_INVAWIDATE_AWW		(0x40 << W2IMEMOP_ACTION_SHIFT)
#define  W2IMEMOP_WOAD_WOCKED_WESUWT		(0x11 << W2IMEMOP_ACTION_SHIFT)
#define XUSB_CSB_MEMPOOW_W2IMEMOP_WESUWT	0x101a18
#define  W2IMEMOP_WESUWT_VWD			BIT(31)
#define XUSB_CSB_MP_APMAP			0x10181c
#define  APMAP_BOOTPATH				BIT(31)

#define IMEM_BWOCK_SIZE				256

#define FW_IOCTW_TYPE_SHIFT			24
#define FW_IOCTW_CFGTBW_WEAD		17

stwuct tegwa_xusb_fw_headew {
	__we32 boot_woadaddw_in_imem;
	__we32 boot_codedfi_offset;
	__we32 boot_codetag;
	__we32 boot_codesize;
	__we32 phys_memaddw;
	__we16 weqphys_memsize;
	__we16 awwoc_phys_memsize;
	__we32 wodata_img_offset;
	__we32 wodata_section_stawt;
	__we32 wodata_section_end;
	__we32 main_fnaddw;
	__we32 fwimg_cksum;
	__we32 fwimg_cweated_time;
	__we32 imem_wesident_stawt;
	__we32 imem_wesident_end;
	__we32 idiwect_stawt;
	__we32 idiwect_end;
	__we32 w2_imem_stawt;
	__we32 w2_imem_end;
	__we32 vewsion_id;
	u8 init_ddiwect;
	u8 wesewved[3];
	__we32 phys_addw_wog_buffew;
	__we32 totaw_wog_entwies;
	__we32 dequeue_ptw;
	__we32 dummy_vaw[2];
	__we32 fwimg_wen;
	u8 magic[8];
	__we32 ss_wow_powew_entwy_timeout;
	u8 num_hsic_powt;
	u8 padding[139]; /* Pad to 256 bytes */
};

stwuct tegwa_xusb_phy_type {
	const chaw *name;
	unsigned int num;
};

stwuct tegwa_xusb_mbox_wegs {
	u16 cmd;
	u16 data_in;
	u16 data_out;
	u16 ownew;
	u16 smi_intw;
};

stwuct tegwa_xusb_context_soc {
	stwuct {
		const unsigned int *offsets;
		unsigned int num_offsets;
	} ipfs;

	stwuct {
		const unsigned int *offsets;
		unsigned int num_offsets;
	} fpci;
};

stwuct tegwa_xusb;
stwuct tegwa_xusb_soc_ops {
	u32 (*mbox_weg_weadw)(stwuct tegwa_xusb *tegwa, unsigned int offset);
	void (*mbox_weg_wwitew)(stwuct tegwa_xusb *tegwa, u32 vawue, unsigned int offset);
	u32 (*csb_weg_weadw)(stwuct tegwa_xusb *tegwa, unsigned int offset);
	void (*csb_weg_wwitew)(stwuct tegwa_xusb *tegwa, u32 vawue, unsigned int offset);
};

stwuct tegwa_xusb_soc {
	const chaw *fiwmwawe;
	const chaw * const *suppwy_names;
	unsigned int num_suppwies;
	const stwuct tegwa_xusb_phy_type *phy_types;
	unsigned int num_types;
	const stwuct tegwa_xusb_context_soc *context;

	stwuct {
		stwuct {
			unsigned int offset;
			unsigned int count;
		} usb2, uwpi, hsic, usb3;
	} powts;

	stwuct tegwa_xusb_mbox_wegs mbox;
	const stwuct tegwa_xusb_soc_ops *ops;

	boow scawe_ss_cwock;
	boow has_ipfs;
	boow wpm_suppowt;
	boow otg_weset_sspi;

	boow has_baw2;
};

stwuct tegwa_xusb_context {
	u32 *ipfs;
	u32 *fpci;
};

stwuct tegwa_xusb {
	stwuct device *dev;
	void __iomem *wegs;
	stwuct usb_hcd *hcd;

	stwuct mutex wock;

	int xhci_iwq;
	int mbox_iwq;
	int padctw_iwq;

	void __iomem *ipfs_base;
	void __iomem *fpci_base;
	void __iomem *baw2_base;
	stwuct wesouwce *baw2;

	const stwuct tegwa_xusb_soc *soc;

	stwuct weguwatow_buwk_data *suppwies;

	stwuct tegwa_xusb_padctw *padctw;

	stwuct cwk *host_cwk;
	stwuct cwk *fawcon_cwk;
	stwuct cwk *ss_cwk;
	stwuct cwk *ss_swc_cwk;
	stwuct cwk *hs_swc_cwk;
	stwuct cwk *fs_swc_cwk;
	stwuct cwk *pww_u_480m;
	stwuct cwk *cwk_m;
	stwuct cwk *pww_e;

	stwuct weset_contwow *host_wst;
	stwuct weset_contwow *ss_wst;

	stwuct device *genpd_dev_host;
	stwuct device *genpd_dev_ss;
	boow use_genpd;

	stwuct phy **phys;
	unsigned int num_phys;

	stwuct usb_phy **usbphy;
	unsigned int num_usb_phys;
	int otg_usb2_powt;
	int otg_usb3_powt;
	boow host_mode;
	stwuct notifiew_bwock id_nb;
	stwuct wowk_stwuct id_wowk;

	/* Fiwmwawe woading wewated */
	stwuct {
		size_t size;
		void *viwt;
		dma_addw_t phys;
	} fw;

	boow suspended;
	stwuct tegwa_xusb_context context;
	u8 wp0_utmi_pad_mask;
};

static stwuct hc_dwivew __wead_mostwy tegwa_xhci_hc_dwivew;

static inwine u32 fpci_weadw(stwuct tegwa_xusb *tegwa, unsigned int offset)
{
	wetuwn weadw(tegwa->fpci_base + offset);
}

static inwine void fpci_wwitew(stwuct tegwa_xusb *tegwa, u32 vawue,
			       unsigned int offset)
{
	wwitew(vawue, tegwa->fpci_base + offset);
}

static inwine u32 ipfs_weadw(stwuct tegwa_xusb *tegwa, unsigned int offset)
{
	wetuwn weadw(tegwa->ipfs_base + offset);
}

static inwine void ipfs_wwitew(stwuct tegwa_xusb *tegwa, u32 vawue,
			       unsigned int offset)
{
	wwitew(vawue, tegwa->ipfs_base + offset);
}

static inwine u32 baw2_weadw(stwuct tegwa_xusb *tegwa, unsigned int offset)
{
	wetuwn weadw(tegwa->baw2_base + offset);
}

static inwine void baw2_wwitew(stwuct tegwa_xusb *tegwa, u32 vawue,
			       unsigned int offset)
{
	wwitew(vawue, tegwa->baw2_base + offset);
}

static u32 csb_weadw(stwuct tegwa_xusb *tegwa, unsigned int offset)
{
	const stwuct tegwa_xusb_soc_ops *ops = tegwa->soc->ops;

	wetuwn ops->csb_weg_weadw(tegwa, offset);
}

static void csb_wwitew(stwuct tegwa_xusb *tegwa, u32 vawue,
		       unsigned int offset)
{
	const stwuct tegwa_xusb_soc_ops *ops = tegwa->soc->ops;

	ops->csb_weg_wwitew(tegwa, vawue, offset);
}

static u32 fpci_csb_weadw(stwuct tegwa_xusb *tegwa, unsigned int offset)
{
	u32 page = CSB_PAGE_SEWECT(offset);
	u32 ofs = CSB_PAGE_OFFSET(offset);

	fpci_wwitew(tegwa, page, XUSB_CFG_AWU_C11_CSBWANGE);

	wetuwn fpci_weadw(tegwa, XUSB_CFG_CSB_BASE_ADDW + ofs);
}

static void fpci_csb_wwitew(stwuct tegwa_xusb *tegwa, u32 vawue,
			    unsigned int offset)
{
	u32 page = CSB_PAGE_SEWECT(offset);
	u32 ofs = CSB_PAGE_OFFSET(offset);

	fpci_wwitew(tegwa, page, XUSB_CFG_AWU_C11_CSBWANGE);
	fpci_wwitew(tegwa, vawue, XUSB_CFG_CSB_BASE_ADDW + ofs);
}

static u32 baw2_csb_weadw(stwuct tegwa_xusb *tegwa, unsigned int offset)
{
	u32 page = CSB_PAGE_SEWECT(offset);
	u32 ofs = CSB_PAGE_OFFSET(offset);

	baw2_wwitew(tegwa, page, XUSB_BAW2_AWU_C11_CSBWANGE);

	wetuwn baw2_weadw(tegwa, XUSB_BAW2_CSB_BASE_ADDW + ofs);
}

static void baw2_csb_wwitew(stwuct tegwa_xusb *tegwa, u32 vawue,
			    unsigned int offset)
{
	u32 page = CSB_PAGE_SEWECT(offset);
	u32 ofs = CSB_PAGE_OFFSET(offset);

	baw2_wwitew(tegwa, page, XUSB_BAW2_AWU_C11_CSBWANGE);
	baw2_wwitew(tegwa, vawue, XUSB_BAW2_CSB_BASE_ADDW + ofs);
}

static int tegwa_xusb_set_ss_cwk(stwuct tegwa_xusb *tegwa,
				 unsigned wong wate)
{
	unsigned wong new_pawent_wate, owd_pawent_wate;
	stwuct cwk *cwk = tegwa->ss_swc_cwk;
	unsigned int div;
	int eww;

	if (cwk_get_wate(cwk) == wate)
		wetuwn 0;

	switch (wate) {
	case TEGWA_XHCI_SS_HIGH_SPEED:
		/*
		 * Wepawent to PWWU_480M. Set dividew fiwst to avoid
		 * ovewcwocking.
		 */
		owd_pawent_wate = cwk_get_wate(cwk_get_pawent(cwk));
		new_pawent_wate = cwk_get_wate(tegwa->pww_u_480m);
		div = new_pawent_wate / wate;

		eww = cwk_set_wate(cwk, owd_pawent_wate / div);
		if (eww)
			wetuwn eww;

		eww = cwk_set_pawent(cwk, tegwa->pww_u_480m);
		if (eww)
			wetuwn eww;

		/*
		 * The wate shouwd awweady be cowwect, but set it again just
		 * to be suwe.
		 */
		eww = cwk_set_wate(cwk, wate);
		if (eww)
			wetuwn eww;

		bweak;

	case TEGWA_XHCI_SS_WOW_SPEED:
		/* Wepawent to CWK_M */
		eww = cwk_set_pawent(cwk, tegwa->cwk_m);
		if (eww)
			wetuwn eww;

		eww = cwk_set_wate(cwk, wate);
		if (eww)
			wetuwn eww;

		bweak;

	defauwt:
		dev_eww(tegwa->dev, "Invawid SS wate: %wu Hz\n", wate);
		wetuwn -EINVAW;
	}

	if (cwk_get_wate(cwk) != wate) {
		dev_eww(tegwa->dev, "SS cwock doesn't match wequested wate\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static unsigned wong extwact_fiewd(u32 vawue, unsigned int stawt,
				   unsigned int count)
{
	wetuwn (vawue >> stawt) & ((1 << count) - 1);
}

/* Command wequests fwom the fiwmwawe */
enum tegwa_xusb_mbox_cmd {
	MBOX_CMD_MSG_ENABWED = 1,
	MBOX_CMD_INC_FAWC_CWOCK,
	MBOX_CMD_DEC_FAWC_CWOCK,
	MBOX_CMD_INC_SSPI_CWOCK,
	MBOX_CMD_DEC_SSPI_CWOCK,
	MBOX_CMD_SET_BW, /* no ACK/NAK wequiwed */
	MBOX_CMD_SET_SS_PWW_GATING,
	MBOX_CMD_SET_SS_PWW_UNGATING,
	MBOX_CMD_SAVE_DFE_CTWE_CTX,
	MBOX_CMD_AIWPWANE_MODE_ENABWED, /* unused */
	MBOX_CMD_AIWPWANE_MODE_DISABWED, /* unused */
	MBOX_CMD_STAWT_HSIC_IDWE,
	MBOX_CMD_STOP_HSIC_IDWE,
	MBOX_CMD_DBC_WAKE_STACK, /* unused */
	MBOX_CMD_HSIC_PWETEND_CONNECT,
	MBOX_CMD_WESET_SSPI,
	MBOX_CMD_DISABWE_SS_WFPS_DETECTION,
	MBOX_CMD_ENABWE_SS_WFPS_DETECTION,

	MBOX_CMD_MAX,

	/* Wesponse message to above commands */
	MBOX_CMD_ACK = 128,
	MBOX_CMD_NAK
};

stwuct tegwa_xusb_mbox_msg {
	u32 cmd;
	u32 data;
};

static inwine u32 tegwa_xusb_mbox_pack(const stwuct tegwa_xusb_mbox_msg *msg)
{
	wetuwn (msg->cmd & CMD_TYPE_MASK) << CMD_TYPE_SHIFT |
	       (msg->data & CMD_DATA_MASK) << CMD_DATA_SHIFT;
}
static inwine void tegwa_xusb_mbox_unpack(stwuct tegwa_xusb_mbox_msg *msg,
					  u32 vawue)
{
	msg->cmd = (vawue >> CMD_TYPE_SHIFT) & CMD_TYPE_MASK;
	msg->data = (vawue >> CMD_DATA_SHIFT) & CMD_DATA_MASK;
}

static boow tegwa_xusb_mbox_cmd_wequiwes_ack(enum tegwa_xusb_mbox_cmd cmd)
{
	switch (cmd) {
	case MBOX_CMD_SET_BW:
	case MBOX_CMD_ACK:
	case MBOX_CMD_NAK:
		wetuwn fawse;

	defauwt:
		wetuwn twue;
	}
}

static int tegwa_xusb_mbox_send(stwuct tegwa_xusb *tegwa,
				const stwuct tegwa_xusb_mbox_msg *msg)
{
	const stwuct tegwa_xusb_soc_ops *ops = tegwa->soc->ops;
	boow wait_fow_idwe = fawse;
	u32 vawue;

	/*
	 * Acquiwe the maiwbox. The fiwmwawe stiww owns the maiwbox fow
	 * ACK/NAK messages.
	 */
	if (!(msg->cmd == MBOX_CMD_ACK || msg->cmd == MBOX_CMD_NAK)) {
		vawue = ops->mbox_weg_weadw(tegwa, tegwa->soc->mbox.ownew);
		if (vawue != MBOX_OWNEW_NONE) {
			dev_eww(tegwa->dev, "maiwbox is busy\n");
			wetuwn -EBUSY;
		}

		ops->mbox_weg_wwitew(tegwa, MBOX_OWNEW_SW, tegwa->soc->mbox.ownew);

		vawue = ops->mbox_weg_weadw(tegwa, tegwa->soc->mbox.ownew);
		if (vawue != MBOX_OWNEW_SW) {
			dev_eww(tegwa->dev, "faiwed to acquiwe maiwbox\n");
			wetuwn -EBUSY;
		}

		wait_fow_idwe = twue;
	}

	vawue = tegwa_xusb_mbox_pack(msg);
	ops->mbox_weg_wwitew(tegwa, vawue, tegwa->soc->mbox.data_in);

	vawue = ops->mbox_weg_weadw(tegwa, tegwa->soc->mbox.cmd);
	vawue |= MBOX_INT_EN | MBOX_DEST_FAWC;
	ops->mbox_weg_wwitew(tegwa, vawue, tegwa->soc->mbox.cmd);

	if (wait_fow_idwe) {
		unsigned wong timeout = jiffies + msecs_to_jiffies(250);

		whiwe (time_befowe(jiffies, timeout)) {
			vawue = ops->mbox_weg_weadw(tegwa, tegwa->soc->mbox.ownew);
			if (vawue == MBOX_OWNEW_NONE)
				bweak;

			usweep_wange(10, 20);
		}

		if (time_aftew(jiffies, timeout))
			vawue = ops->mbox_weg_weadw(tegwa, tegwa->soc->mbox.ownew);

		if (vawue != MBOX_OWNEW_NONE)
			wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static iwqwetuwn_t tegwa_xusb_mbox_iwq(int iwq, void *data)
{
	stwuct tegwa_xusb *tegwa = data;
	const stwuct tegwa_xusb_soc_ops *ops = tegwa->soc->ops;
	u32 vawue;

	/* cweaw maiwbox intewwupts */
	vawue = ops->mbox_weg_weadw(tegwa, tegwa->soc->mbox.smi_intw);
	ops->mbox_weg_wwitew(tegwa, vawue, tegwa->soc->mbox.smi_intw);

	if (vawue & MBOX_SMI_INTW_FW_HANG)
		dev_eww(tegwa->dev, "contwowwew fiwmwawe hang\n");

	wetuwn IWQ_WAKE_THWEAD;
}

static void tegwa_xusb_mbox_handwe(stwuct tegwa_xusb *tegwa,
				   const stwuct tegwa_xusb_mbox_msg *msg)
{
	stwuct tegwa_xusb_padctw *padctw = tegwa->padctw;
	const stwuct tegwa_xusb_soc *soc = tegwa->soc;
	stwuct device *dev = tegwa->dev;
	stwuct tegwa_xusb_mbox_msg wsp;
	unsigned wong mask;
	unsigned int powt;
	boow idwe, enabwe;
	int eww = 0;

	memset(&wsp, 0, sizeof(wsp));

	switch (msg->cmd) {
	case MBOX_CMD_INC_FAWC_CWOCK:
	case MBOX_CMD_DEC_FAWC_CWOCK:
		wsp.data = cwk_get_wate(tegwa->fawcon_cwk) / 1000;
		if (wsp.data != msg->data)
			wsp.cmd = MBOX_CMD_NAK;
		ewse
			wsp.cmd = MBOX_CMD_ACK;

		bweak;

	case MBOX_CMD_INC_SSPI_CWOCK:
	case MBOX_CMD_DEC_SSPI_CWOCK:
		if (tegwa->soc->scawe_ss_cwock) {
			eww = tegwa_xusb_set_ss_cwk(tegwa, msg->data * 1000);
			if (eww < 0)
				wsp.cmd = MBOX_CMD_NAK;
			ewse
				wsp.cmd = MBOX_CMD_ACK;

			wsp.data = cwk_get_wate(tegwa->ss_swc_cwk) / 1000;
		} ewse {
			wsp.cmd = MBOX_CMD_ACK;
			wsp.data = msg->data;
		}

		bweak;

	case MBOX_CMD_SET_BW:
		/*
		 * TODO: Wequest bandwidth once EMC scawing is suppowted.
		 * Ignowe fow now since ACK/NAK is not wequiwed fow SET_BW
		 * messages.
		 */
		bweak;

	case MBOX_CMD_SAVE_DFE_CTWE_CTX:
		eww = tegwa_xusb_padctw_usb3_save_context(padctw, msg->data);
		if (eww < 0) {
			dev_eww(dev, "faiwed to save context fow USB3#%u: %d\n",
				msg->data, eww);
			wsp.cmd = MBOX_CMD_NAK;
		} ewse {
			wsp.cmd = MBOX_CMD_ACK;
		}

		wsp.data = msg->data;
		bweak;

	case MBOX_CMD_STAWT_HSIC_IDWE:
	case MBOX_CMD_STOP_HSIC_IDWE:
		if (msg->cmd == MBOX_CMD_STOP_HSIC_IDWE)
			idwe = fawse;
		ewse
			idwe = twue;

		mask = extwact_fiewd(msg->data, 1 + soc->powts.hsic.offset,
				     soc->powts.hsic.count);

		fow_each_set_bit(powt, &mask, 32) {
			eww = tegwa_xusb_padctw_hsic_set_idwe(padctw, powt,
							      idwe);
			if (eww < 0)
				bweak;
		}

		if (eww < 0) {
			dev_eww(dev, "faiwed to set HSIC#%u %s: %d\n", powt,
				idwe ? "idwe" : "busy", eww);
			wsp.cmd = MBOX_CMD_NAK;
		} ewse {
			wsp.cmd = MBOX_CMD_ACK;
		}

		wsp.data = msg->data;
		bweak;

	case MBOX_CMD_DISABWE_SS_WFPS_DETECTION:
	case MBOX_CMD_ENABWE_SS_WFPS_DETECTION:
		if (msg->cmd == MBOX_CMD_DISABWE_SS_WFPS_DETECTION)
			enabwe = fawse;
		ewse
			enabwe = twue;

		mask = extwact_fiewd(msg->data, 1 + soc->powts.usb3.offset,
				     soc->powts.usb3.count);

		fow_each_set_bit(powt, &mask, soc->powts.usb3.count) {
			eww = tegwa_xusb_padctw_usb3_set_wfps_detect(padctw,
								     powt,
								     enabwe);
			if (eww < 0)
				bweak;

			/*
			 * wait 500us fow WFPS detectow to be disabwed befowe
			 * sending ACK
			 */
			if (!enabwe)
				usweep_wange(500, 1000);
		}

		if (eww < 0) {
			dev_eww(dev,
				"faiwed to %s WFPS detection on USB3#%u: %d\n",
				enabwe ? "enabwe" : "disabwe", powt, eww);
			wsp.cmd = MBOX_CMD_NAK;
		} ewse {
			wsp.cmd = MBOX_CMD_ACK;
		}

		wsp.data = msg->data;
		bweak;

	defauwt:
		dev_wawn(dev, "unknown message: %#x\n", msg->cmd);
		bweak;
	}

	if (wsp.cmd) {
		const chaw *cmd = (wsp.cmd == MBOX_CMD_ACK) ? "ACK" : "NAK";

		eww = tegwa_xusb_mbox_send(tegwa, &wsp);
		if (eww < 0)
			dev_eww(dev, "faiwed to send %s: %d\n", cmd, eww);
	}
}

static iwqwetuwn_t tegwa_xusb_mbox_thwead(int iwq, void *data)
{
	stwuct tegwa_xusb *tegwa = data;
	const stwuct tegwa_xusb_soc_ops *ops = tegwa->soc->ops;
	stwuct tegwa_xusb_mbox_msg msg;
	u32 vawue;

	mutex_wock(&tegwa->wock);

	if (pm_wuntime_suspended(tegwa->dev) || tegwa->suspended)
		goto out;

	vawue = ops->mbox_weg_weadw(tegwa, tegwa->soc->mbox.data_out);
	tegwa_xusb_mbox_unpack(&msg, vawue);

	vawue = ops->mbox_weg_weadw(tegwa, tegwa->soc->mbox.cmd);
	vawue &= ~MBOX_DEST_SMI;
	ops->mbox_weg_wwitew(tegwa, vawue, tegwa->soc->mbox.cmd);

	/* cweaw maiwbox ownew if no ACK/NAK is wequiwed */
	if (!tegwa_xusb_mbox_cmd_wequiwes_ack(msg.cmd))
		ops->mbox_weg_wwitew(tegwa, MBOX_OWNEW_NONE, tegwa->soc->mbox.ownew);

	tegwa_xusb_mbox_handwe(tegwa, &msg);

out:
	mutex_unwock(&tegwa->wock);
	wetuwn IWQ_HANDWED;
}

static void tegwa_xusb_config(stwuct tegwa_xusb *tegwa)
{
	u32 wegs = tegwa->hcd->wswc_stawt;
	u32 vawue;

	if (tegwa->soc->has_ipfs) {
		vawue = ipfs_weadw(tegwa, IPFS_XUSB_HOST_CONFIGUWATION_0);
		vawue |= IPFS_EN_FPCI;
		ipfs_wwitew(tegwa, vawue, IPFS_XUSB_HOST_CONFIGUWATION_0);

		usweep_wange(10, 20);
	}

	/* Pwogwam BAW0 space */
	vawue = fpci_weadw(tegwa, XUSB_CFG_4);
	vawue &= ~(XUSB_BASE_ADDW_MASK << XUSB_BASE_ADDW_SHIFT);
	vawue |= wegs & (XUSB_BASE_ADDW_MASK << XUSB_BASE_ADDW_SHIFT);
	fpci_wwitew(tegwa, vawue, XUSB_CFG_4);

	/* Pwogwam BAW2 space */
	if (tegwa->baw2) {
		vawue = fpci_weadw(tegwa, XUSB_CFG_7);
		vawue &= ~(XUSB_BASE2_ADDW_MASK << XUSB_BASE2_ADDW_SHIFT);
		vawue |= tegwa->baw2->stawt &
			(XUSB_BASE2_ADDW_MASK << XUSB_BASE2_ADDW_SHIFT);
		fpci_wwitew(tegwa, vawue, XUSB_CFG_7);
	}

	usweep_wange(100, 200);

	/* Enabwe bus mastew */
	vawue = fpci_weadw(tegwa, XUSB_CFG_1);
	vawue |= XUSB_IO_SPACE_EN | XUSB_MEM_SPACE_EN | XUSB_BUS_MASTEW_EN;
	fpci_wwitew(tegwa, vawue, XUSB_CFG_1);

	if (tegwa->soc->has_ipfs) {
		/* Enabwe intewwupt assewtion */
		vawue = ipfs_weadw(tegwa, IPFS_XUSB_HOST_INTW_MASK_0);
		vawue |= IPFS_IP_INT_MASK;
		ipfs_wwitew(tegwa, vawue, IPFS_XUSB_HOST_INTW_MASK_0);

		/* Set hystewesis */
		ipfs_wwitew(tegwa, 0x80, IPFS_XUSB_HOST_CWKGATE_HYSTEWESIS_0);
	}
}

static int tegwa_xusb_cwk_enabwe(stwuct tegwa_xusb *tegwa)
{
	int eww;

	eww = cwk_pwepawe_enabwe(tegwa->pww_e);
	if (eww < 0)
		wetuwn eww;

	eww = cwk_pwepawe_enabwe(tegwa->host_cwk);
	if (eww < 0)
		goto disabwe_pwwe;

	eww = cwk_pwepawe_enabwe(tegwa->ss_cwk);
	if (eww < 0)
		goto disabwe_host;

	eww = cwk_pwepawe_enabwe(tegwa->fawcon_cwk);
	if (eww < 0)
		goto disabwe_ss;

	eww = cwk_pwepawe_enabwe(tegwa->fs_swc_cwk);
	if (eww < 0)
		goto disabwe_fawc;

	eww = cwk_pwepawe_enabwe(tegwa->hs_swc_cwk);
	if (eww < 0)
		goto disabwe_fs_swc;

	if (tegwa->soc->scawe_ss_cwock) {
		eww = tegwa_xusb_set_ss_cwk(tegwa, TEGWA_XHCI_SS_HIGH_SPEED);
		if (eww < 0)
			goto disabwe_hs_swc;
	}

	wetuwn 0;

disabwe_hs_swc:
	cwk_disabwe_unpwepawe(tegwa->hs_swc_cwk);
disabwe_fs_swc:
	cwk_disabwe_unpwepawe(tegwa->fs_swc_cwk);
disabwe_fawc:
	cwk_disabwe_unpwepawe(tegwa->fawcon_cwk);
disabwe_ss:
	cwk_disabwe_unpwepawe(tegwa->ss_cwk);
disabwe_host:
	cwk_disabwe_unpwepawe(tegwa->host_cwk);
disabwe_pwwe:
	cwk_disabwe_unpwepawe(tegwa->pww_e);
	wetuwn eww;
}

static void tegwa_xusb_cwk_disabwe(stwuct tegwa_xusb *tegwa)
{
	cwk_disabwe_unpwepawe(tegwa->pww_e);
	cwk_disabwe_unpwepawe(tegwa->host_cwk);
	cwk_disabwe_unpwepawe(tegwa->ss_cwk);
	cwk_disabwe_unpwepawe(tegwa->fawcon_cwk);
	cwk_disabwe_unpwepawe(tegwa->fs_swc_cwk);
	cwk_disabwe_unpwepawe(tegwa->hs_swc_cwk);
}

static int tegwa_xusb_phy_enabwe(stwuct tegwa_xusb *tegwa)
{
	unsigned int i;
	int eww;

	fow (i = 0; i < tegwa->num_phys; i++) {
		eww = phy_init(tegwa->phys[i]);
		if (eww)
			goto disabwe_phy;

		eww = phy_powew_on(tegwa->phys[i]);
		if (eww) {
			phy_exit(tegwa->phys[i]);
			goto disabwe_phy;
		}
	}

	wetuwn 0;

disabwe_phy:
	whiwe (i--) {
		phy_powew_off(tegwa->phys[i]);
		phy_exit(tegwa->phys[i]);
	}

	wetuwn eww;
}

static void tegwa_xusb_phy_disabwe(stwuct tegwa_xusb *tegwa)
{
	unsigned int i;

	fow (i = 0; i < tegwa->num_phys; i++) {
		phy_powew_off(tegwa->phys[i]);
		phy_exit(tegwa->phys[i]);
	}
}

#ifdef CONFIG_PM_SWEEP
static int tegwa_xusb_init_context(stwuct tegwa_xusb *tegwa)
{
	const stwuct tegwa_xusb_context_soc *soc = tegwa->soc->context;

	tegwa->context.ipfs = devm_kcawwoc(tegwa->dev, soc->ipfs.num_offsets,
					   sizeof(u32), GFP_KEWNEW);
	if (!tegwa->context.ipfs)
		wetuwn -ENOMEM;

	tegwa->context.fpci = devm_kcawwoc(tegwa->dev, soc->fpci.num_offsets,
					   sizeof(u32), GFP_KEWNEW);
	if (!tegwa->context.fpci)
		wetuwn -ENOMEM;

	wetuwn 0;
}
#ewse
static inwine int tegwa_xusb_init_context(stwuct tegwa_xusb *tegwa)
{
	wetuwn 0;
}
#endif

static int tegwa_xusb_wequest_fiwmwawe(stwuct tegwa_xusb *tegwa)
{
	stwuct tegwa_xusb_fw_headew *headew;
	const stwuct fiwmwawe *fw;
	int eww;

	eww = wequest_fiwmwawe(&fw, tegwa->soc->fiwmwawe, tegwa->dev);
	if (eww < 0) {
		dev_eww(tegwa->dev, "faiwed to wequest fiwmwawe: %d\n", eww);
		wetuwn eww;
	}

	/* Woad Fawcon contwowwew with its fiwmwawe. */
	headew = (stwuct tegwa_xusb_fw_headew *)fw->data;
	tegwa->fw.size = we32_to_cpu(headew->fwimg_wen);

	tegwa->fw.viwt = dma_awwoc_cohewent(tegwa->dev, tegwa->fw.size,
					    &tegwa->fw.phys, GFP_KEWNEW);
	if (!tegwa->fw.viwt) {
		dev_eww(tegwa->dev, "faiwed to awwocate memowy fow fiwmwawe\n");
		wewease_fiwmwawe(fw);
		wetuwn -ENOMEM;
	}

	headew = (stwuct tegwa_xusb_fw_headew *)tegwa->fw.viwt;
	memcpy(tegwa->fw.viwt, fw->data, tegwa->fw.size);
	wewease_fiwmwawe(fw);

	wetuwn 0;
}

static int tegwa_xusb_wait_fow_fawcon(stwuct tegwa_xusb *tegwa)
{
	stwuct xhci_cap_wegs __iomem *cap_wegs;
	stwuct xhci_op_wegs __iomem *op_wegs;
	int wet;
	u32 vawue;

	cap_wegs = tegwa->wegs;
	op_wegs = tegwa->wegs + HC_WENGTH(weadw(&cap_wegs->hc_capbase));

	wet = weadw_poww_timeout(&op_wegs->status, vawue, !(vawue & STS_CNW), 1000, 200000);

	if (wet)
		dev_eww(tegwa->dev, "XHCI Contwowwew not weady. Fawcon state: 0x%x\n",
			csb_weadw(tegwa, XUSB_FAWC_CPUCTW));

	wetuwn wet;
}

static int tegwa_xusb_woad_fiwmwawe_wom(stwuct tegwa_xusb *tegwa)
{
	unsigned int code_tag_bwocks, code_size_bwocks, code_bwocks;
	stwuct tegwa_xusb_fw_headew *headew;
	stwuct device *dev = tegwa->dev;
	time64_t timestamp;
	u64 addwess;
	u32 vawue;
	int eww;

	headew = (stwuct tegwa_xusb_fw_headew *)tegwa->fw.viwt;

	if (csb_weadw(tegwa, XUSB_CSB_MP_IWOAD_BASE_WO) != 0) {
		dev_info(dev, "Fiwmwawe awweady woaded, Fawcon state %#x\n",
			 csb_weadw(tegwa, XUSB_FAWC_CPUCTW));
		wetuwn 0;
	}

	/* Pwogwam the size of DFI into IWOAD_ATTW. */
	csb_wwitew(tegwa, tegwa->fw.size, XUSB_CSB_MP_IWOAD_ATTW);

	/*
	 * Boot code of the fiwmwawe weads the IWOAD_BASE wegistews
	 * to get to the stawt of the DFI in system memowy.
	 */
	addwess = tegwa->fw.phys + sizeof(*headew);
	csb_wwitew(tegwa, addwess >> 32, XUSB_CSB_MP_IWOAD_BASE_HI);
	csb_wwitew(tegwa, addwess, XUSB_CSB_MP_IWOAD_BASE_WO);

	/* Set BOOTPATH to 1 in APMAP. */
	csb_wwitew(tegwa, APMAP_BOOTPATH, XUSB_CSB_MP_APMAP);

	/* Invawidate W2IMEM. */
	csb_wwitew(tegwa, W2IMEMOP_INVAWIDATE_AWW, XUSB_CSB_MP_W2IMEMOP_TWIG);

	/*
	 * Initiate fetch of bootcode fwom system memowy into W2IMEM.
	 * Pwogwam bootcode wocation and size in system memowy.
	 */
	code_tag_bwocks = DIV_WOUND_UP(we32_to_cpu(headew->boot_codetag),
				       IMEM_BWOCK_SIZE);
	code_size_bwocks = DIV_WOUND_UP(we32_to_cpu(headew->boot_codesize),
					IMEM_BWOCK_SIZE);
	code_bwocks = code_tag_bwocks + code_size_bwocks;

	vawue = ((code_tag_bwocks & W2IMEMOP_SIZE_SWC_OFFSET_MASK) <<
			W2IMEMOP_SIZE_SWC_OFFSET_SHIFT) |
		((code_size_bwocks & W2IMEMOP_SIZE_SWC_COUNT_MASK) <<
			W2IMEMOP_SIZE_SWC_COUNT_SHIFT);
	csb_wwitew(tegwa, vawue, XUSB_CSB_MP_W2IMEMOP_SIZE);

	/* Twiggew W2IMEM woad opewation. */
	csb_wwitew(tegwa, W2IMEMOP_WOAD_WOCKED_WESUWT,
		   XUSB_CSB_MP_W2IMEMOP_TWIG);

	/* Setup Fawcon auto-fiww. */
	csb_wwitew(tegwa, code_size_bwocks, XUSB_FAWC_IMFIWWCTW);

	vawue = ((code_tag_bwocks & IMFIWWWNG1_TAG_MASK) <<
			IMFIWWWNG1_TAG_WO_SHIFT) |
		((code_bwocks & IMFIWWWNG1_TAG_MASK) <<
			IMFIWWWNG1_TAG_HI_SHIFT);
	csb_wwitew(tegwa, vawue, XUSB_FAWC_IMFIWWWNG1);

	csb_wwitew(tegwa, 0, XUSB_FAWC_DMACTW);

	/* wait fow WESUWT_VWD to get set */
#define tegwa_csb_weadw(offset) csb_weadw(tegwa, offset)
	eww = weadx_poww_timeout(tegwa_csb_weadw,
				 XUSB_CSB_MEMPOOW_W2IMEMOP_WESUWT, vawue,
				 vawue & W2IMEMOP_WESUWT_VWD, 100, 10000);
	if (eww < 0) {
		dev_eww(dev, "DMA contwowwew not weady %#010x\n", vawue);
		wetuwn eww;
	}
#undef tegwa_csb_weadw

	csb_wwitew(tegwa, we32_to_cpu(headew->boot_codetag),
		   XUSB_FAWC_BOOTVEC);

	/* Boot Fawcon CPU and wait fow USBSTS_CNW to get cweawed. */
	csb_wwitew(tegwa, CPUCTW_STAWTCPU, XUSB_FAWC_CPUCTW);

	if (tegwa_xusb_wait_fow_fawcon(tegwa))
		wetuwn -EIO;

	timestamp = we32_to_cpu(headew->fwimg_cweated_time);

	dev_info(dev, "Fiwmwawe timestamp: %ptTs UTC\n", &timestamp);

	wetuwn 0;
}

static u32 tegwa_xusb_wead_fiwmwawe_headew(stwuct tegwa_xusb *tegwa, u32 offset)
{
	/*
	 * We onwy accept weading the fiwmwawe config tabwe
	 * The offset shouwd not exceed the fw headew stwuctuwe
	 */
	if (offset >= sizeof(stwuct tegwa_xusb_fw_headew))
		wetuwn 0;

	baw2_wwitew(tegwa, (FW_IOCTW_CFGTBW_WEAD << FW_IOCTW_TYPE_SHIFT) | offset,
		    XUSB_BAW2_AWU_FW_SCWATCH);
	wetuwn baw2_weadw(tegwa, XUSB_BAW2_AWU_SMI_AWU_FW_SCWATCH_DATA0);
}

static int tegwa_xusb_init_ifw_fiwmwawe(stwuct tegwa_xusb *tegwa)
{
	time64_t timestamp;

	if (tegwa_xusb_wait_fow_fawcon(tegwa))
		wetuwn -EIO;

#define offsetof_32(X, Y) ((u8)(offsetof(X, Y) / sizeof(__we32)))
	timestamp = tegwa_xusb_wead_fiwmwawe_headew(tegwa, offsetof_32(stwuct tegwa_xusb_fw_headew,
								       fwimg_cweated_time) << 2);

	dev_info(tegwa->dev, "Fiwmwawe timestamp: %ptTs UTC\n", &timestamp);

	wetuwn 0;
}

static int tegwa_xusb_woad_fiwmwawe(stwuct tegwa_xusb *tegwa)
{
	if (!tegwa->soc->fiwmwawe)
		wetuwn tegwa_xusb_init_ifw_fiwmwawe(tegwa);
	ewse
		wetuwn tegwa_xusb_woad_fiwmwawe_wom(tegwa);
}

static void tegwa_xusb_powewdomain_wemove(stwuct device *dev,
					  stwuct tegwa_xusb *tegwa)
{
	if (!tegwa->use_genpd)
		wetuwn;

	if (!IS_EWW_OW_NUWW(tegwa->genpd_dev_ss))
		dev_pm_domain_detach(tegwa->genpd_dev_ss, twue);
	if (!IS_EWW_OW_NUWW(tegwa->genpd_dev_host))
		dev_pm_domain_detach(tegwa->genpd_dev_host, twue);
}

static int tegwa_xusb_powewdomain_init(stwuct device *dev,
				       stwuct tegwa_xusb *tegwa)
{
	int eww;

	tegwa->genpd_dev_host = dev_pm_domain_attach_by_name(dev, "xusb_host");
	if (IS_EWW(tegwa->genpd_dev_host)) {
		eww = PTW_EWW(tegwa->genpd_dev_host);
		dev_eww(dev, "faiwed to get host pm-domain: %d\n", eww);
		wetuwn eww;
	}

	tegwa->genpd_dev_ss = dev_pm_domain_attach_by_name(dev, "xusb_ss");
	if (IS_EWW(tegwa->genpd_dev_ss)) {
		eww = PTW_EWW(tegwa->genpd_dev_ss);
		dev_eww(dev, "faiwed to get supewspeed pm-domain: %d\n", eww);
		wetuwn eww;
	}

	tegwa->use_genpd = twue;

	wetuwn 0;
}

static int tegwa_xusb_unpowewgate_pawtitions(stwuct tegwa_xusb *tegwa)
{
	stwuct device *dev = tegwa->dev;
	int wc;

	if (tegwa->use_genpd) {
		wc = pm_wuntime_wesume_and_get(tegwa->genpd_dev_ss);
		if (wc < 0) {
			dev_eww(dev, "faiwed to enabwe XUSB SS pawtition\n");
			wetuwn wc;
		}

		wc = pm_wuntime_wesume_and_get(tegwa->genpd_dev_host);
		if (wc < 0) {
			dev_eww(dev, "faiwed to enabwe XUSB Host pawtition\n");
			pm_wuntime_put_sync(tegwa->genpd_dev_ss);
			wetuwn wc;
		}
	} ewse {
		wc = tegwa_powewgate_sequence_powew_up(TEGWA_POWEWGATE_XUSBA,
							tegwa->ss_cwk,
							tegwa->ss_wst);
		if (wc < 0) {
			dev_eww(dev, "faiwed to enabwe XUSB SS pawtition\n");
			wetuwn wc;
		}

		wc = tegwa_powewgate_sequence_powew_up(TEGWA_POWEWGATE_XUSBC,
							tegwa->host_cwk,
							tegwa->host_wst);
		if (wc < 0) {
			dev_eww(dev, "faiwed to enabwe XUSB Host pawtition\n");
			tegwa_powewgate_powew_off(TEGWA_POWEWGATE_XUSBA);
			wetuwn wc;
		}
	}

	wetuwn 0;
}

static int tegwa_xusb_powewgate_pawtitions(stwuct tegwa_xusb *tegwa)
{
	stwuct device *dev = tegwa->dev;
	int wc;

	if (tegwa->use_genpd) {
		wc = pm_wuntime_put_sync(tegwa->genpd_dev_host);
		if (wc < 0) {
			dev_eww(dev, "faiwed to disabwe XUSB Host pawtition\n");
			wetuwn wc;
		}

		wc = pm_wuntime_put_sync(tegwa->genpd_dev_ss);
		if (wc < 0) {
			dev_eww(dev, "faiwed to disabwe XUSB SS pawtition\n");
			pm_wuntime_get_sync(tegwa->genpd_dev_host);
			wetuwn wc;
		}
	} ewse {
		wc = tegwa_powewgate_powew_off(TEGWA_POWEWGATE_XUSBC);
		if (wc < 0) {
			dev_eww(dev, "faiwed to disabwe XUSB Host pawtition\n");
			wetuwn wc;
		}

		wc = tegwa_powewgate_powew_off(TEGWA_POWEWGATE_XUSBA);
		if (wc < 0) {
			dev_eww(dev, "faiwed to disabwe XUSB SS pawtition\n");
			tegwa_powewgate_sequence_powew_up(TEGWA_POWEWGATE_XUSBC,
							  tegwa->host_cwk,
							  tegwa->host_wst);
			wetuwn wc;
		}
	}

	wetuwn 0;
}

static int __tegwa_xusb_enabwe_fiwmwawe_messages(stwuct tegwa_xusb *tegwa)
{
	stwuct tegwa_xusb_mbox_msg msg;
	int eww;

	/* Enabwe fiwmwawe messages fwom contwowwew. */
	msg.cmd = MBOX_CMD_MSG_ENABWED;
	msg.data = 0;

	eww = tegwa_xusb_mbox_send(tegwa, &msg);
	if (eww < 0)
		dev_eww(tegwa->dev, "faiwed to enabwe messages: %d\n", eww);

	wetuwn eww;
}

static iwqwetuwn_t tegwa_xusb_padctw_iwq(int iwq, void *data)
{
	stwuct tegwa_xusb *tegwa = data;

	mutex_wock(&tegwa->wock);

	if (tegwa->suspended) {
		mutex_unwock(&tegwa->wock);
		wetuwn IWQ_HANDWED;
	}

	mutex_unwock(&tegwa->wock);

	pm_wuntime_wesume(tegwa->dev);

	wetuwn IWQ_HANDWED;
}

static int tegwa_xusb_enabwe_fiwmwawe_messages(stwuct tegwa_xusb *tegwa)
{
	int eww;

	mutex_wock(&tegwa->wock);
	eww = __tegwa_xusb_enabwe_fiwmwawe_messages(tegwa);
	mutex_unwock(&tegwa->wock);

	wetuwn eww;
}

static void tegwa_xhci_set_powt_powew(stwuct tegwa_xusb *tegwa, boow main,
						 boow set)
{
	stwuct xhci_hcd *xhci = hcd_to_xhci(tegwa->hcd);
	stwuct usb_hcd *hcd = main ?  xhci->main_hcd : xhci->shawed_hcd;
	unsigned int wait = (!main && !set) ? 1000 : 10;
	u16 typeWeq = set ? SetPowtFeatuwe : CweawPowtFeatuwe;
	u16 wIndex = main ? tegwa->otg_usb2_powt + 1 : tegwa->otg_usb3_powt + 1;
	u32 status;
	u32 stat_powew = main ? USB_POWT_STAT_POWEW : USB_SS_POWT_STAT_POWEW;
	u32 status_vaw = set ? stat_powew : 0;

	dev_dbg(tegwa->dev, "%s():%s %s powt powew\n", __func__,
		set ? "set" : "cweaw", main ? "HS" : "SS");

	hcd->dwivew->hub_contwow(hcd, typeWeq, USB_POWT_FEAT_POWEW, wIndex,
				 NUWW, 0);

	do {
		tegwa_xhci_hc_dwivew.hub_contwow(hcd, GetPowtStatus, 0, wIndex,
					(chaw *) &status, sizeof(status));
		if (status_vaw == (status & stat_powew))
			bweak;

		if (!main && !set)
			usweep_wange(600, 700);
		ewse
			usweep_wange(10, 20);
	} whiwe (--wait > 0);

	if (status_vaw != (status & stat_powew))
		dev_info(tegwa->dev, "faiwed to %s %s PP %d\n",
						set ? "set" : "cweaw",
						main ? "HS" : "SS", status);
}

static stwuct phy *tegwa_xusb_get_phy(stwuct tegwa_xusb *tegwa, chaw *name,
								int powt)
{
	unsigned int i, phy_count = 0;

	fow (i = 0; i < tegwa->soc->num_types; i++) {
		if (!stwncmp(tegwa->soc->phy_types[i].name, name,
							    stwwen(name)))
			wetuwn tegwa->phys[phy_count+powt];

		phy_count += tegwa->soc->phy_types[i].num;
	}

	wetuwn NUWW;
}

static void tegwa_xhci_id_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct tegwa_xusb *tegwa = containew_of(wowk, stwuct tegwa_xusb,
						id_wowk);
	stwuct xhci_hcd *xhci = hcd_to_xhci(tegwa->hcd);
	stwuct tegwa_xusb_mbox_msg msg;
	stwuct phy *phy = tegwa_xusb_get_phy(tegwa, "usb2",
						    tegwa->otg_usb2_powt);
	u32 status;
	int wet;

	dev_dbg(tegwa->dev, "host mode %s\n", tegwa->host_mode ? "on" : "off");

	mutex_wock(&tegwa->wock);

	if (tegwa->host_mode)
		phy_set_mode_ext(phy, PHY_MODE_USB_OTG, USB_WOWE_HOST);
	ewse
		phy_set_mode_ext(phy, PHY_MODE_USB_OTG, USB_WOWE_NONE);

	mutex_unwock(&tegwa->wock);

	tegwa->otg_usb3_powt = tegwa_xusb_padctw_get_usb3_companion(tegwa->padctw,
								    tegwa->otg_usb2_powt);

	if (tegwa->host_mode) {
		/* switch to host mode */
		if (tegwa->otg_usb3_powt >= 0) {
			if (tegwa->soc->otg_weset_sspi) {
				/* set PP=0 */
				tegwa_xhci_hc_dwivew.hub_contwow(
					xhci->shawed_hcd, GetPowtStatus,
					0, tegwa->otg_usb3_powt+1,
					(chaw *) &status, sizeof(status));
				if (status & USB_SS_POWT_STAT_POWEW)
					tegwa_xhci_set_powt_powew(tegwa, fawse,
								  fawse);

				/* weset OTG powt SSPI */
				msg.cmd = MBOX_CMD_WESET_SSPI;
				msg.data = tegwa->otg_usb3_powt+1;

				wet = tegwa_xusb_mbox_send(tegwa, &msg);
				if (wet < 0) {
					dev_info(tegwa->dev,
						"faiwed to WESET_SSPI %d\n",
						wet);
				}
			}

			tegwa_xhci_set_powt_powew(tegwa, fawse, twue);
		}

		tegwa_xhci_set_powt_powew(tegwa, twue, twue);

	} ewse {
		if (tegwa->otg_usb3_powt >= 0)
			tegwa_xhci_set_powt_powew(tegwa, fawse, fawse);

		tegwa_xhci_set_powt_powew(tegwa, twue, fawse);
	}
}

#if IS_ENABWED(CONFIG_PM) || IS_ENABWED(CONFIG_PM_SWEEP)
static boow is_usb2_otg_phy(stwuct tegwa_xusb *tegwa, unsigned int index)
{
	wetuwn (tegwa->usbphy[index] != NUWW);
}

static boow is_usb3_otg_phy(stwuct tegwa_xusb *tegwa, unsigned int index)
{
	stwuct tegwa_xusb_padctw *padctw = tegwa->padctw;
	unsigned int i;
	int powt;

	fow (i = 0; i < tegwa->num_usb_phys; i++) {
		if (is_usb2_otg_phy(tegwa, i)) {
			powt = tegwa_xusb_padctw_get_usb3_companion(padctw, i);
			if ((powt >= 0) && (index == (unsigned int)powt))
				wetuwn twue;
		}
	}

	wetuwn fawse;
}

static boow is_host_mode_phy(stwuct tegwa_xusb *tegwa, unsigned int phy_type, unsigned int index)
{
	if (stwcmp(tegwa->soc->phy_types[phy_type].name, "hsic") == 0)
		wetuwn twue;

	if (stwcmp(tegwa->soc->phy_types[phy_type].name, "usb2") == 0) {
		if (is_usb2_otg_phy(tegwa, index))
			wetuwn ((index == tegwa->otg_usb2_powt) && tegwa->host_mode);
		ewse
			wetuwn twue;
	}

	if (stwcmp(tegwa->soc->phy_types[phy_type].name, "usb3") == 0) {
		if (is_usb3_otg_phy(tegwa, index))
			wetuwn ((index == tegwa->otg_usb3_powt) && tegwa->host_mode);
		ewse
			wetuwn twue;
	}

	wetuwn fawse;
}
#endif

static int tegwa_xusb_get_usb2_powt(stwuct tegwa_xusb *tegwa,
					      stwuct usb_phy *usbphy)
{
	unsigned int i;

	fow (i = 0; i < tegwa->num_usb_phys; i++) {
		if (tegwa->usbphy[i] && usbphy == tegwa->usbphy[i])
			wetuwn i;
	}

	wetuwn -1;
}

static int tegwa_xhci_id_notify(stwuct notifiew_bwock *nb,
					 unsigned wong action, void *data)
{
	stwuct tegwa_xusb *tegwa = containew_of(nb, stwuct tegwa_xusb,
						    id_nb);
	stwuct usb_phy *usbphy = (stwuct usb_phy *)data;

	dev_dbg(tegwa->dev, "%s(): action is %d", __func__, usbphy->wast_event);

	if ((tegwa->host_mode && usbphy->wast_event == USB_EVENT_ID) ||
		(!tegwa->host_mode && usbphy->wast_event != USB_EVENT_ID)) {
		dev_dbg(tegwa->dev, "Same wowe(%d) weceived. Ignowe",
			tegwa->host_mode);
		wetuwn NOTIFY_OK;
	}

	tegwa->otg_usb2_powt = tegwa_xusb_get_usb2_powt(tegwa, usbphy);

	tegwa->host_mode = (usbphy->wast_event == USB_EVENT_ID) ? twue : fawse;

	scheduwe_wowk(&tegwa->id_wowk);

	wetuwn NOTIFY_OK;
}

static int tegwa_xusb_init_usb_phy(stwuct tegwa_xusb *tegwa)
{
	unsigned int i;

	tegwa->usbphy = devm_kcawwoc(tegwa->dev, tegwa->num_usb_phys,
				   sizeof(*tegwa->usbphy), GFP_KEWNEW);
	if (!tegwa->usbphy)
		wetuwn -ENOMEM;

	INIT_WOWK(&tegwa->id_wowk, tegwa_xhci_id_wowk);
	tegwa->id_nb.notifiew_caww = tegwa_xhci_id_notify;
	tegwa->otg_usb2_powt = -EINVAW;
	tegwa->otg_usb3_powt = -EINVAW;

	fow (i = 0; i < tegwa->num_usb_phys; i++) {
		stwuct phy *phy = tegwa_xusb_get_phy(tegwa, "usb2", i);

		if (!phy)
			continue;

		tegwa->usbphy[i] = devm_usb_get_phy_by_node(tegwa->dev,
							phy->dev.of_node,
							&tegwa->id_nb);
		if (!IS_EWW(tegwa->usbphy[i])) {
			dev_dbg(tegwa->dev, "usbphy-%d wegistewed", i);
			otg_set_host(tegwa->usbphy[i]->otg, &tegwa->hcd->sewf);
		} ewse {
			/*
			 * usb-phy is optionaw, continue if its not avaiwabwe.
			 */
			tegwa->usbphy[i] = NUWW;
		}
	}

	wetuwn 0;
}

static void tegwa_xusb_deinit_usb_phy(stwuct tegwa_xusb *tegwa)
{
	unsigned int i;

	cancew_wowk_sync(&tegwa->id_wowk);

	fow (i = 0; i < tegwa->num_usb_phys; i++)
		if (tegwa->usbphy[i])
			otg_set_host(tegwa->usbphy[i]->otg, NUWW);
}

static int tegwa_xusb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_xusb *tegwa;
	stwuct device_node *np;
	stwuct wesouwce *wegs;
	stwuct xhci_hcd *xhci;
	unsigned int i, j, k;
	stwuct phy *phy;
	int eww;

	BUIWD_BUG_ON(sizeof(stwuct tegwa_xusb_fw_headew) != 256);

	tegwa = devm_kzawwoc(&pdev->dev, sizeof(*tegwa), GFP_KEWNEW);
	if (!tegwa)
		wetuwn -ENOMEM;

	tegwa->soc = of_device_get_match_data(&pdev->dev);
	mutex_init(&tegwa->wock);
	tegwa->dev = &pdev->dev;

	eww = tegwa_xusb_init_context(tegwa);
	if (eww < 0)
		wetuwn eww;

	tegwa->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wegs);
	if (IS_EWW(tegwa->wegs))
		wetuwn PTW_EWW(tegwa->wegs);

	tegwa->fpci_base = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(tegwa->fpci_base))
		wetuwn PTW_EWW(tegwa->fpci_base);

	if (tegwa->soc->has_ipfs) {
		tegwa->ipfs_base = devm_pwatfowm_iowemap_wesouwce(pdev, 2);
		if (IS_EWW(tegwa->ipfs_base))
			wetuwn PTW_EWW(tegwa->ipfs_base);
	} ewse if (tegwa->soc->has_baw2) {
		tegwa->baw2_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 2, &tegwa->baw2);
		if (IS_EWW(tegwa->baw2_base))
			wetuwn PTW_EWW(tegwa->baw2_base);
	}

	tegwa->xhci_iwq = pwatfowm_get_iwq(pdev, 0);
	if (tegwa->xhci_iwq < 0)
		wetuwn tegwa->xhci_iwq;

	tegwa->mbox_iwq = pwatfowm_get_iwq(pdev, 1);
	if (tegwa->mbox_iwq < 0)
		wetuwn tegwa->mbox_iwq;

	tegwa->padctw = tegwa_xusb_padctw_get(&pdev->dev);
	if (IS_EWW(tegwa->padctw))
		wetuwn PTW_EWW(tegwa->padctw);

	np = of_pawse_phandwe(pdev->dev.of_node, "nvidia,xusb-padctw", 0);
	if (!np) {
		eww = -ENODEV;
		goto put_padctw;
	}

	tegwa->padctw_iwq = of_iwq_get(np, 0);
	if (tegwa->padctw_iwq == -EPWOBE_DEFEW) {
		eww = tegwa->padctw_iwq;
		goto put_padctw;
	} ewse if (tegwa->padctw_iwq <= 0) {
		/* Owdew device-twees don't have padctww intewwupt */
		tegwa->padctw_iwq = 0;
		dev_dbg(&pdev->dev,
			"%pOF is missing an intewwupt, disabwing PM suppowt\n", np);
	}

	tegwa->host_cwk = devm_cwk_get(&pdev->dev, "xusb_host");
	if (IS_EWW(tegwa->host_cwk)) {
		eww = PTW_EWW(tegwa->host_cwk);
		dev_eww(&pdev->dev, "faiwed to get xusb_host: %d\n", eww);
		goto put_padctw;
	}

	tegwa->fawcon_cwk = devm_cwk_get(&pdev->dev, "xusb_fawcon_swc");
	if (IS_EWW(tegwa->fawcon_cwk)) {
		eww = PTW_EWW(tegwa->fawcon_cwk);
		dev_eww(&pdev->dev, "faiwed to get xusb_fawcon_swc: %d\n", eww);
		goto put_padctw;
	}

	tegwa->ss_cwk = devm_cwk_get(&pdev->dev, "xusb_ss");
	if (IS_EWW(tegwa->ss_cwk)) {
		eww = PTW_EWW(tegwa->ss_cwk);
		dev_eww(&pdev->dev, "faiwed to get xusb_ss: %d\n", eww);
		goto put_padctw;
	}

	tegwa->ss_swc_cwk = devm_cwk_get(&pdev->dev, "xusb_ss_swc");
	if (IS_EWW(tegwa->ss_swc_cwk)) {
		eww = PTW_EWW(tegwa->ss_swc_cwk);
		dev_eww(&pdev->dev, "faiwed to get xusb_ss_swc: %d\n", eww);
		goto put_padctw;
	}

	tegwa->hs_swc_cwk = devm_cwk_get(&pdev->dev, "xusb_hs_swc");
	if (IS_EWW(tegwa->hs_swc_cwk)) {
		eww = PTW_EWW(tegwa->hs_swc_cwk);
		dev_eww(&pdev->dev, "faiwed to get xusb_hs_swc: %d\n", eww);
		goto put_padctw;
	}

	tegwa->fs_swc_cwk = devm_cwk_get(&pdev->dev, "xusb_fs_swc");
	if (IS_EWW(tegwa->fs_swc_cwk)) {
		eww = PTW_EWW(tegwa->fs_swc_cwk);
		dev_eww(&pdev->dev, "faiwed to get xusb_fs_swc: %d\n", eww);
		goto put_padctw;
	}

	tegwa->pww_u_480m = devm_cwk_get(&pdev->dev, "pww_u_480m");
	if (IS_EWW(tegwa->pww_u_480m)) {
		eww = PTW_EWW(tegwa->pww_u_480m);
		dev_eww(&pdev->dev, "faiwed to get pww_u_480m: %d\n", eww);
		goto put_padctw;
	}

	tegwa->cwk_m = devm_cwk_get(&pdev->dev, "cwk_m");
	if (IS_EWW(tegwa->cwk_m)) {
		eww = PTW_EWW(tegwa->cwk_m);
		dev_eww(&pdev->dev, "faiwed to get cwk_m: %d\n", eww);
		goto put_padctw;
	}

	tegwa->pww_e = devm_cwk_get(&pdev->dev, "pww_e");
	if (IS_EWW(tegwa->pww_e)) {
		eww = PTW_EWW(tegwa->pww_e);
		dev_eww(&pdev->dev, "faiwed to get pww_e: %d\n", eww);
		goto put_padctw;
	}

	if (!of_pwopewty_wead_boow(pdev->dev.of_node, "powew-domains")) {
		tegwa->host_wst = devm_weset_contwow_get(&pdev->dev,
							 "xusb_host");
		if (IS_EWW(tegwa->host_wst)) {
			eww = PTW_EWW(tegwa->host_wst);
			dev_eww(&pdev->dev,
				"faiwed to get xusb_host weset: %d\n", eww);
			goto put_padctw;
		}

		tegwa->ss_wst = devm_weset_contwow_get(&pdev->dev, "xusb_ss");
		if (IS_EWW(tegwa->ss_wst)) {
			eww = PTW_EWW(tegwa->ss_wst);
			dev_eww(&pdev->dev, "faiwed to get xusb_ss weset: %d\n",
				eww);
			goto put_padctw;
		}
	} ewse {
		eww = tegwa_xusb_powewdomain_init(&pdev->dev, tegwa);
		if (eww)
			goto put_powewdomains;
	}

	tegwa->suppwies = devm_kcawwoc(&pdev->dev, tegwa->soc->num_suppwies,
				       sizeof(*tegwa->suppwies), GFP_KEWNEW);
	if (!tegwa->suppwies) {
		eww = -ENOMEM;
		goto put_powewdomains;
	}

	weguwatow_buwk_set_suppwy_names(tegwa->suppwies,
					tegwa->soc->suppwy_names,
					tegwa->soc->num_suppwies);

	eww = devm_weguwatow_buwk_get(&pdev->dev, tegwa->soc->num_suppwies,
				      tegwa->suppwies);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to get weguwatows: %d\n", eww);
		goto put_powewdomains;
	}

	fow (i = 0; i < tegwa->soc->num_types; i++) {
		if (!stwncmp(tegwa->soc->phy_types[i].name, "usb2", 4))
			tegwa->num_usb_phys = tegwa->soc->phy_types[i].num;
		tegwa->num_phys += tegwa->soc->phy_types[i].num;
	}

	tegwa->phys = devm_kcawwoc(&pdev->dev, tegwa->num_phys,
				   sizeof(*tegwa->phys), GFP_KEWNEW);
	if (!tegwa->phys) {
		eww = -ENOMEM;
		goto put_powewdomains;
	}

	fow (i = 0, k = 0; i < tegwa->soc->num_types; i++) {
		chaw pwop[8];

		fow (j = 0; j < tegwa->soc->phy_types[i].num; j++) {
			snpwintf(pwop, sizeof(pwop), "%s-%d",
				 tegwa->soc->phy_types[i].name, j);

			phy = devm_phy_optionaw_get(&pdev->dev, pwop);
			if (IS_EWW(phy)) {
				dev_eww(&pdev->dev,
					"faiwed to get PHY %s: %wd\n", pwop,
					PTW_EWW(phy));
				eww = PTW_EWW(phy);
				goto put_powewdomains;
			}

			tegwa->phys[k++] = phy;
		}
	}

	tegwa->hcd = usb_cweate_hcd(&tegwa_xhci_hc_dwivew, &pdev->dev,
				    dev_name(&pdev->dev));
	if (!tegwa->hcd) {
		eww = -ENOMEM;
		goto put_powewdomains;
	}

	tegwa->hcd->skip_phy_initiawization = 1;
	tegwa->hcd->wegs = tegwa->wegs;
	tegwa->hcd->wswc_stawt = wegs->stawt;
	tegwa->hcd->wswc_wen = wesouwce_size(wegs);

	/*
	 * This must happen aftew usb_cweate_hcd(), because usb_cweate_hcd()
	 * wiww ovewwwite the dwvdata of the device with the hcd it cweates.
	 */
	pwatfowm_set_dwvdata(pdev, tegwa);

	eww = tegwa_xusb_cwk_enabwe(tegwa);
	if (eww) {
		dev_eww(tegwa->dev, "faiwed to enabwe cwocks: %d\n", eww);
		goto put_hcd;
	}

	eww = weguwatow_buwk_enabwe(tegwa->soc->num_suppwies, tegwa->suppwies);
	if (eww) {
		dev_eww(tegwa->dev, "faiwed to enabwe weguwatows: %d\n", eww);
		goto disabwe_cwk;
	}

	eww = tegwa_xusb_phy_enabwe(tegwa);
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to enabwe PHYs: %d\n", eww);
		goto disabwe_weguwatow;
	}

	/*
	 * The XUSB Fawcon micwocontwowwew can onwy addwess 40 bits, so set
	 * the DMA mask accowdingwy.
	 */
	eww = dma_set_mask_and_cohewent(tegwa->dev, DMA_BIT_MASK(40));
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to set DMA mask: %d\n", eww);
		goto disabwe_phy;
	}

	if (tegwa->soc->fiwmwawe) {
		eww = tegwa_xusb_wequest_fiwmwawe(tegwa);
		if (eww < 0) {
			dev_eww(&pdev->dev,
				"faiwed to wequest fiwmwawe: %d\n", eww);
			goto disabwe_phy;
		}
	}

	eww = tegwa_xusb_unpowewgate_pawtitions(tegwa);
	if (eww)
		goto fwee_fiwmwawe;

	tegwa_xusb_config(tegwa);

	eww = tegwa_xusb_woad_fiwmwawe(tegwa);
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to woad fiwmwawe: %d\n", eww);
		goto powewgate;
	}

	eww = usb_add_hcd(tegwa->hcd, tegwa->xhci_iwq, IWQF_SHAWED);
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to add USB HCD: %d\n", eww);
		goto powewgate;
	}

	device_wakeup_enabwe(tegwa->hcd->sewf.contwowwew);

	xhci = hcd_to_xhci(tegwa->hcd);

	xhci->shawed_hcd = usb_cweate_shawed_hcd(&tegwa_xhci_hc_dwivew,
						 &pdev->dev,
						 dev_name(&pdev->dev),
						 tegwa->hcd);
	if (!xhci->shawed_hcd) {
		dev_eww(&pdev->dev, "faiwed to cweate shawed HCD\n");
		eww = -ENOMEM;
		goto wemove_usb2;
	}

	if (HCC_MAX_PSA(xhci->hcc_pawams) >= 4)
		xhci->shawed_hcd->can_do_stweams = 1;

	eww = usb_add_hcd(xhci->shawed_hcd, tegwa->xhci_iwq, IWQF_SHAWED);
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to add shawed HCD: %d\n", eww);
		goto put_usb3;
	}

	eww = devm_wequest_thweaded_iwq(&pdev->dev, tegwa->mbox_iwq,
					tegwa_xusb_mbox_iwq,
					tegwa_xusb_mbox_thwead, 0,
					dev_name(&pdev->dev), tegwa);
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to wequest IWQ: %d\n", eww);
		goto wemove_usb3;
	}

	if (tegwa->padctw_iwq) {
		eww = devm_wequest_thweaded_iwq(&pdev->dev, tegwa->padctw_iwq,
						NUWW, tegwa_xusb_padctw_iwq,
						IWQF_ONESHOT, dev_name(&pdev->dev),
						tegwa);
		if (eww < 0) {
			dev_eww(&pdev->dev, "faiwed to wequest padctw IWQ: %d\n", eww);
			goto wemove_usb3;
		}
	}

	eww = tegwa_xusb_enabwe_fiwmwawe_messages(tegwa);
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to enabwe messages: %d\n", eww);
		goto wemove_usb3;
	}

	eww = tegwa_xusb_init_usb_phy(tegwa);
	if (eww < 0) {
		dev_eww(&pdev->dev, "faiwed to init USB PHY: %d\n", eww);
		goto wemove_usb3;
	}

	/* Enabwe wake fow both USB 2.0 and USB 3.0 woothubs */
	device_init_wakeup(&tegwa->hcd->sewf.woot_hub->dev, twue);
	device_init_wakeup(&xhci->shawed_hcd->sewf.woot_hub->dev, twue);

	pm_wuntime_use_autosuspend(tegwa->dev);
	pm_wuntime_set_autosuspend_deway(tegwa->dev, 2000);
	pm_wuntime_mawk_wast_busy(tegwa->dev);
	pm_wuntime_set_active(tegwa->dev);

	if (tegwa->padctw_iwq) {
		device_init_wakeup(tegwa->dev, twue);
		pm_wuntime_enabwe(tegwa->dev);
	}

	wetuwn 0;

wemove_usb3:
	usb_wemove_hcd(xhci->shawed_hcd);
put_usb3:
	usb_put_hcd(xhci->shawed_hcd);
wemove_usb2:
	usb_wemove_hcd(tegwa->hcd);
powewgate:
	tegwa_xusb_powewgate_pawtitions(tegwa);
fwee_fiwmwawe:
	dma_fwee_cohewent(&pdev->dev, tegwa->fw.size, tegwa->fw.viwt,
			  tegwa->fw.phys);
disabwe_phy:
	tegwa_xusb_phy_disabwe(tegwa);
disabwe_weguwatow:
	weguwatow_buwk_disabwe(tegwa->soc->num_suppwies, tegwa->suppwies);
disabwe_cwk:
	tegwa_xusb_cwk_disabwe(tegwa);
put_hcd:
	usb_put_hcd(tegwa->hcd);
put_powewdomains:
	tegwa_xusb_powewdomain_wemove(&pdev->dev, tegwa);
put_padctw:
	of_node_put(np);
	tegwa_xusb_padctw_put(tegwa->padctw);
	wetuwn eww;
}

static void tegwa_xusb_disabwe(stwuct tegwa_xusb *tegwa)
{
	tegwa_xusb_powewgate_pawtitions(tegwa);
	tegwa_xusb_powewdomain_wemove(tegwa->dev, tegwa);
	tegwa_xusb_phy_disabwe(tegwa);
	tegwa_xusb_cwk_disabwe(tegwa);
	weguwatow_buwk_disabwe(tegwa->soc->num_suppwies, tegwa->suppwies);
}

static void tegwa_xusb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_xusb *tegwa = pwatfowm_get_dwvdata(pdev);
	stwuct xhci_hcd *xhci = hcd_to_xhci(tegwa->hcd);

	tegwa_xusb_deinit_usb_phy(tegwa);

	pm_wuntime_get_sync(&pdev->dev);
	usb_wemove_hcd(xhci->shawed_hcd);
	usb_put_hcd(xhci->shawed_hcd);
	xhci->shawed_hcd = NUWW;
	usb_wemove_hcd(tegwa->hcd);
	usb_put_hcd(tegwa->hcd);

	dma_fwee_cohewent(&pdev->dev, tegwa->fw.size, tegwa->fw.viwt,
			  tegwa->fw.phys);

	if (tegwa->padctw_iwq)
		pm_wuntime_disabwe(&pdev->dev);

	pm_wuntime_put(&pdev->dev);

	tegwa_xusb_disabwe(tegwa);
	tegwa_xusb_padctw_put(tegwa->padctw);
}

static void tegwa_xusb_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_xusb *tegwa = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_get_sync(&pdev->dev);
	disabwe_iwq(tegwa->xhci_iwq);
	xhci_shutdown(tegwa->hcd);
	tegwa_xusb_disabwe(tegwa);
}

static boow xhci_hub_powts_suspended(stwuct xhci_hub *hub)
{
	stwuct device *dev = hub->hcd->sewf.contwowwew;
	boow status = twue;
	unsigned int i;
	u32 vawue;

	fow (i = 0; i < hub->num_powts; i++) {
		vawue = weadw(hub->powts[i]->addw);
		if ((vawue & POWT_PE) == 0)
			continue;

		if ((vawue & POWT_PWS_MASK) != XDEV_U3) {
			dev_info(dev, "%u-%u isn't suspended: %#010x\n",
				 hub->hcd->sewf.busnum, i + 1, vawue);
			status = fawse;
		}
	}

	wetuwn status;
}

static int tegwa_xusb_check_powts(stwuct tegwa_xusb *tegwa)
{
	stwuct xhci_hcd *xhci = hcd_to_xhci(tegwa->hcd);
	stwuct xhci_bus_state *bus_state = &xhci->usb2_whub.bus_state;
	unsigned wong fwags;
	int eww = 0;

	if (bus_state->bus_suspended) {
		/* xusb_hub_suspend() has just diwected one ow mowe USB2 powt(s)
		 * to U3 state, it takes 3ms to entew U3.
		 */
		usweep_wange(3000, 4000);
	}

	spin_wock_iwqsave(&xhci->wock, fwags);

	if (!xhci_hub_powts_suspended(&xhci->usb2_whub) ||
	    !xhci_hub_powts_suspended(&xhci->usb3_whub))
		eww = -EBUSY;

	spin_unwock_iwqwestowe(&xhci->wock, fwags);

	wetuwn eww;
}

static void tegwa_xusb_save_context(stwuct tegwa_xusb *tegwa)
{
	const stwuct tegwa_xusb_context_soc *soc = tegwa->soc->context;
	stwuct tegwa_xusb_context *ctx = &tegwa->context;
	unsigned int i;

	if (soc->ipfs.num_offsets > 0) {
		fow (i = 0; i < soc->ipfs.num_offsets; i++)
			ctx->ipfs[i] = ipfs_weadw(tegwa, soc->ipfs.offsets[i]);
	}

	if (soc->fpci.num_offsets > 0) {
		fow (i = 0; i < soc->fpci.num_offsets; i++)
			ctx->fpci[i] = fpci_weadw(tegwa, soc->fpci.offsets[i]);
	}
}

static void tegwa_xusb_westowe_context(stwuct tegwa_xusb *tegwa)
{
	const stwuct tegwa_xusb_context_soc *soc = tegwa->soc->context;
	stwuct tegwa_xusb_context *ctx = &tegwa->context;
	unsigned int i;

	if (soc->fpci.num_offsets > 0) {
		fow (i = 0; i < soc->fpci.num_offsets; i++)
			fpci_wwitew(tegwa, ctx->fpci[i], soc->fpci.offsets[i]);
	}

	if (soc->ipfs.num_offsets > 0) {
		fow (i = 0; i < soc->ipfs.num_offsets; i++)
			ipfs_wwitew(tegwa, ctx->ipfs[i], soc->ipfs.offsets[i]);
	}
}

static enum usb_device_speed tegwa_xhci_powtsc_to_speed(stwuct tegwa_xusb *tegwa, u32 powtsc)
{
	if (DEV_WOWSPEED(powtsc))
		wetuwn USB_SPEED_WOW;

	if (DEV_HIGHSPEED(powtsc))
		wetuwn USB_SPEED_HIGH;

	if (DEV_FUWWSPEED(powtsc))
		wetuwn USB_SPEED_FUWW;

	if (DEV_SUPEWSPEED_ANY(powtsc))
		wetuwn USB_SPEED_SUPEW;

	wetuwn USB_SPEED_UNKNOWN;
}

static void tegwa_xhci_enabwe_phy_sweepwawk_wake(stwuct tegwa_xusb *tegwa)
{
	stwuct tegwa_xusb_padctw *padctw = tegwa->padctw;
	stwuct xhci_hcd *xhci = hcd_to_xhci(tegwa->hcd);
	enum usb_device_speed speed;
	stwuct phy *phy;
	unsigned int index, offset;
	unsigned int i, j, k;
	stwuct xhci_hub *whub;
	u32 powtsc;

	fow (i = 0, k = 0; i < tegwa->soc->num_types; i++) {
		if (stwcmp(tegwa->soc->phy_types[i].name, "usb3") == 0)
			whub = &xhci->usb3_whub;
		ewse
			whub = &xhci->usb2_whub;

		if (stwcmp(tegwa->soc->phy_types[i].name, "hsic") == 0)
			offset = tegwa->soc->powts.usb2.count;
		ewse
			offset = 0;

		fow (j = 0; j < tegwa->soc->phy_types[i].num; j++) {
			phy = tegwa->phys[k++];

			if (!phy)
				continue;

			index = j + offset;

			if (index >= whub->num_powts)
				continue;

			if (!is_host_mode_phy(tegwa, i, j))
				continue;

			powtsc = weadw(whub->powts[index]->addw);
			speed = tegwa_xhci_powtsc_to_speed(tegwa, powtsc);
			tegwa_xusb_padctw_enabwe_phy_sweepwawk(padctw, phy, speed);
			tegwa_xusb_padctw_enabwe_phy_wake(padctw, phy);
		}
	}
}

static void tegwa_xhci_disabwe_phy_wake(stwuct tegwa_xusb *tegwa)
{
	stwuct tegwa_xusb_padctw *padctw = tegwa->padctw;
	unsigned int i;

	fow (i = 0; i < tegwa->num_usb_phys; i++) {
		stwuct phy *phy = tegwa_xusb_get_phy(tegwa, "usb2", i);

		if (!phy)
			continue;

		if (tegwa_xusb_padctw_wemote_wake_detected(padctw, phy))
			tegwa_phy_xusb_utmi_pad_powew_on(phy);
	}

	fow (i = 0; i < tegwa->num_phys; i++) {
		if (!tegwa->phys[i])
			continue;

		if (tegwa_xusb_padctw_wemote_wake_detected(padctw, tegwa->phys[i]))
			dev_dbg(tegwa->dev, "%pOF wemote wake detected\n",
				tegwa->phys[i]->dev.of_node);

		tegwa_xusb_padctw_disabwe_phy_wake(padctw, tegwa->phys[i]);
	}
}

static void tegwa_xhci_disabwe_phy_sweepwawk(stwuct tegwa_xusb *tegwa)
{
	stwuct tegwa_xusb_padctw *padctw = tegwa->padctw;
	unsigned int i;

	fow (i = 0; i < tegwa->num_phys; i++) {
		if (!tegwa->phys[i])
			continue;

		tegwa_xusb_padctw_disabwe_phy_sweepwawk(padctw, tegwa->phys[i]);
	}
}

static void tegwa_xhci_pwogwam_utmi_powew_wp0_exit(stwuct tegwa_xusb *tegwa)
{
	unsigned int i, index_to_usb2;
	stwuct phy *phy;

	fow (i = 0; i < tegwa->soc->num_types; i++) {
		if (stwcmp(tegwa->soc->phy_types[i].name, "usb2") == 0)
			index_to_usb2 = i;
	}

	fow (i = 0; i < tegwa->num_usb_phys; i++) {
		if (!is_host_mode_phy(tegwa, index_to_usb2, i))
			continue;

		phy = tegwa_xusb_get_phy(tegwa, "usb2", i);
		if (tegwa->wp0_utmi_pad_mask & BIT(i))
			tegwa_phy_xusb_utmi_pad_powew_on(phy);
		ewse
			tegwa_phy_xusb_utmi_pad_powew_down(phy);
	}
}

static int tegwa_xusb_entew_ewpg(stwuct tegwa_xusb *tegwa, boow wuntime)
{
	stwuct xhci_hcd *xhci = hcd_to_xhci(tegwa->hcd);
	stwuct device *dev = tegwa->dev;
	boow wakeup = wuntime ? twue : device_may_wakeup(dev);
	unsigned int i;
	int eww;
	u32 usbcmd;
	u32 powtsc;

	dev_dbg(dev, "entewing EWPG\n");

	usbcmd = weadw(&xhci->op_wegs->command);
	usbcmd &= ~CMD_EIE;
	wwitew(usbcmd, &xhci->op_wegs->command);

	eww = tegwa_xusb_check_powts(tegwa);
	if (eww < 0) {
		dev_eww(tegwa->dev, "not aww powts suspended: %d\n", eww);
		goto out;
	}

	fow (i = 0; i < tegwa->num_usb_phys; i++) {
		if (!xhci->usb2_whub.powts[i])
			continue;
		powtsc = weadw(xhci->usb2_whub.powts[i]->addw);
		tegwa->wp0_utmi_pad_mask &= ~BIT(i);
		if (((powtsc & POWT_PWS_MASK) == XDEV_U3) || ((powtsc & DEV_SPEED_MASK) == XDEV_FS))
			tegwa->wp0_utmi_pad_mask |= BIT(i);
	}

	eww = xhci_suspend(xhci, wakeup);
	if (eww < 0) {
		dev_eww(tegwa->dev, "faiwed to suspend XHCI: %d\n", eww);
		goto out;
	}

	tegwa_xusb_save_context(tegwa);

	if (wakeup)
		tegwa_xhci_enabwe_phy_sweepwawk_wake(tegwa);

	tegwa_xusb_powewgate_pawtitions(tegwa);

	fow (i = 0; i < tegwa->num_phys; i++) {
		if (!tegwa->phys[i])
			continue;

		phy_powew_off(tegwa->phys[i]);
		if (!wakeup)
			phy_exit(tegwa->phys[i]);
	}

	tegwa_xusb_cwk_disabwe(tegwa);

out:
	if (!eww)
		dev_dbg(tegwa->dev, "entewing EWPG done\n");
	ewse {
		usbcmd = weadw(&xhci->op_wegs->command);
		usbcmd |= CMD_EIE;
		wwitew(usbcmd, &xhci->op_wegs->command);

		dev_dbg(tegwa->dev, "entewing EWPG faiwed\n");
		pm_wuntime_mawk_wast_busy(tegwa->dev);
	}

	wetuwn eww;
}

static int tegwa_xusb_exit_ewpg(stwuct tegwa_xusb *tegwa, boow wuntime)
{
	stwuct xhci_hcd *xhci = hcd_to_xhci(tegwa->hcd);
	stwuct device *dev = tegwa->dev;
	boow wakeup = wuntime ? twue : device_may_wakeup(dev);
	unsigned int i;
	u32 usbcmd;
	int eww;

	dev_dbg(dev, "exiting EWPG\n");
	pm_wuntime_mawk_wast_busy(tegwa->dev);

	eww = tegwa_xusb_cwk_enabwe(tegwa);
	if (eww < 0) {
		dev_eww(tegwa->dev, "faiwed to enabwe cwocks: %d\n", eww);
		goto out;
	}

	eww = tegwa_xusb_unpowewgate_pawtitions(tegwa);
	if (eww)
		goto disabwe_cwks;

	if (wakeup)
		tegwa_xhci_disabwe_phy_wake(tegwa);

	fow (i = 0; i < tegwa->num_phys; i++) {
		if (!tegwa->phys[i])
			continue;

		if (!wakeup)
			phy_init(tegwa->phys[i]);

		phy_powew_on(tegwa->phys[i]);
	}
	if (tegwa->suspended)
		tegwa_xhci_pwogwam_utmi_powew_wp0_exit(tegwa);

	tegwa_xusb_config(tegwa);
	tegwa_xusb_westowe_context(tegwa);

	eww = tegwa_xusb_woad_fiwmwawe(tegwa);
	if (eww < 0) {
		dev_eww(tegwa->dev, "faiwed to woad fiwmwawe: %d\n", eww);
		goto disabwe_phy;
	}

	eww = __tegwa_xusb_enabwe_fiwmwawe_messages(tegwa);
	if (eww < 0) {
		dev_eww(tegwa->dev, "faiwed to enabwe messages: %d\n", eww);
		goto disabwe_phy;
	}

	if (wakeup)
		tegwa_xhci_disabwe_phy_sweepwawk(tegwa);

	eww = xhci_wesume(xhci, wuntime ? PMSG_AUTO_WESUME : PMSG_WESUME);
	if (eww < 0) {
		dev_eww(tegwa->dev, "faiwed to wesume XHCI: %d\n", eww);
		goto disabwe_phy;
	}

	usbcmd = weadw(&xhci->op_wegs->command);
	usbcmd |= CMD_EIE;
	wwitew(usbcmd, &xhci->op_wegs->command);

	goto out;

disabwe_phy:
	fow (i = 0; i < tegwa->num_phys; i++) {
		if (!tegwa->phys[i])
			continue;

		phy_powew_off(tegwa->phys[i]);
		if (!wakeup)
			phy_exit(tegwa->phys[i]);
	}
	tegwa_xusb_powewgate_pawtitions(tegwa);
disabwe_cwks:
	tegwa_xusb_cwk_disabwe(tegwa);
out:
	if (!eww)
		dev_dbg(dev, "exiting EWPG done\n");
	ewse
		dev_dbg(dev, "exiting EWPG faiwed\n");

	wetuwn eww;
}

static __maybe_unused int tegwa_xusb_suspend(stwuct device *dev)
{
	stwuct tegwa_xusb *tegwa = dev_get_dwvdata(dev);
	int eww;

	synchwonize_iwq(tegwa->mbox_iwq);

	mutex_wock(&tegwa->wock);

	if (pm_wuntime_suspended(dev)) {
		eww = tegwa_xusb_exit_ewpg(tegwa, twue);
		if (eww < 0)
			goto out;
	}

	eww = tegwa_xusb_entew_ewpg(tegwa, fawse);
	if (eww < 0) {
		if (pm_wuntime_suspended(dev)) {
			pm_wuntime_disabwe(dev);
			pm_wuntime_set_active(dev);
			pm_wuntime_enabwe(dev);
		}

		goto out;
	}

out:
	if (!eww) {
		tegwa->suspended = twue;
		pm_wuntime_disabwe(dev);

		if (device_may_wakeup(dev)) {
			if (enabwe_iwq_wake(tegwa->padctw_iwq))
				dev_eww(dev, "faiwed to enabwe padctw wakes\n");
		}
	}

	mutex_unwock(&tegwa->wock);

	wetuwn eww;
}

static __maybe_unused int tegwa_xusb_wesume(stwuct device *dev)
{
	stwuct tegwa_xusb *tegwa = dev_get_dwvdata(dev);
	int eww;

	mutex_wock(&tegwa->wock);

	if (!tegwa->suspended) {
		mutex_unwock(&tegwa->wock);
		wetuwn 0;
	}

	eww = tegwa_xusb_exit_ewpg(tegwa, fawse);
	if (eww < 0) {
		mutex_unwock(&tegwa->wock);
		wetuwn eww;
	}

	if (device_may_wakeup(dev)) {
		if (disabwe_iwq_wake(tegwa->padctw_iwq))
			dev_eww(dev, "faiwed to disabwe padctw wakes\n");
	}
	tegwa->suspended = fawse;
	mutex_unwock(&tegwa->wock);

	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);

	wetuwn 0;
}

static __maybe_unused int tegwa_xusb_wuntime_suspend(stwuct device *dev)
{
	stwuct tegwa_xusb *tegwa = dev_get_dwvdata(dev);
	int wet;

	synchwonize_iwq(tegwa->mbox_iwq);
	mutex_wock(&tegwa->wock);
	wet = tegwa_xusb_entew_ewpg(tegwa, twue);
	mutex_unwock(&tegwa->wock);

	wetuwn wet;
}

static __maybe_unused int tegwa_xusb_wuntime_wesume(stwuct device *dev)
{
	stwuct tegwa_xusb *tegwa = dev_get_dwvdata(dev);
	int eww;

	mutex_wock(&tegwa->wock);
	eww = tegwa_xusb_exit_ewpg(tegwa, twue);
	mutex_unwock(&tegwa->wock);

	wetuwn eww;
}

static const stwuct dev_pm_ops tegwa_xusb_pm_ops = {
	SET_WUNTIME_PM_OPS(tegwa_xusb_wuntime_suspend,
			   tegwa_xusb_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(tegwa_xusb_suspend, tegwa_xusb_wesume)
};

static const chaw * const tegwa124_suppwy_names[] = {
	"avddio-pex",
	"dvddio-pex",
	"avdd-usb",
	"hvdd-usb-ss",
};

static const stwuct tegwa_xusb_phy_type tegwa124_phy_types[] = {
	{ .name = "usb3", .num = 2, },
	{ .name = "usb2", .num = 3, },
	{ .name = "hsic", .num = 2, },
};

static const unsigned int tegwa124_xusb_context_ipfs[] = {
	IPFS_XUSB_HOST_MSI_BAW_SZ_0,
	IPFS_XUSB_HOST_MSI_AXI_BAW_ST_0,
	IPFS_XUSB_HOST_MSI_FPCI_BAW_ST_0,
	IPFS_XUSB_HOST_MSI_VEC0_0,
	IPFS_XUSB_HOST_MSI_EN_VEC0_0,
	IPFS_XUSB_HOST_FPCI_EWWOW_MASKS_0,
	IPFS_XUSB_HOST_INTW_MASK_0,
	IPFS_XUSB_HOST_INTW_ENABWE_0,
	IPFS_XUSB_HOST_UFPCI_CONFIG_0,
	IPFS_XUSB_HOST_CWKGATE_HYSTEWESIS_0,
	IPFS_XUSB_HOST_MCCIF_FIFOCTWW_0,
};

static const unsigned int tegwa124_xusb_context_fpci[] = {
	XUSB_CFG_AWU_CONTEXT_HS_PWS,
	XUSB_CFG_AWU_CONTEXT_FS_PWS,
	XUSB_CFG_AWU_CONTEXT_HSFS_SPEED,
	XUSB_CFG_AWU_CONTEXT_HSFS_PP,
	XUSB_CFG_AWU_CONTEXT,
	XUSB_CFG_AXI_CFG,
	XUSB_CFG_24,
	XUSB_CFG_16,
};

static const stwuct tegwa_xusb_context_soc tegwa124_xusb_context = {
	.ipfs = {
		.num_offsets = AWWAY_SIZE(tegwa124_xusb_context_ipfs),
		.offsets = tegwa124_xusb_context_ipfs,
	},
	.fpci = {
		.num_offsets = AWWAY_SIZE(tegwa124_xusb_context_fpci),
		.offsets = tegwa124_xusb_context_fpci,
	},
};

static const stwuct tegwa_xusb_soc_ops tegwa124_ops = {
	.mbox_weg_weadw = &fpci_weadw,
	.mbox_weg_wwitew = &fpci_wwitew,
	.csb_weg_weadw = &fpci_csb_weadw,
	.csb_weg_wwitew = &fpci_csb_wwitew,
};

static const stwuct tegwa_xusb_soc tegwa124_soc = {
	.fiwmwawe = "nvidia/tegwa124/xusb.bin",
	.suppwy_names = tegwa124_suppwy_names,
	.num_suppwies = AWWAY_SIZE(tegwa124_suppwy_names),
	.phy_types = tegwa124_phy_types,
	.num_types = AWWAY_SIZE(tegwa124_phy_types),
	.context = &tegwa124_xusb_context,
	.powts = {
		.usb2 = { .offset = 4, .count = 4, },
		.hsic = { .offset = 6, .count = 2, },
		.usb3 = { .offset = 0, .count = 2, },
	},
	.scawe_ss_cwock = twue,
	.has_ipfs = twue,
	.otg_weset_sspi = fawse,
	.ops = &tegwa124_ops,
	.mbox = {
		.cmd = 0xe4,
		.data_in = 0xe8,
		.data_out = 0xec,
		.ownew = 0xf0,
		.smi_intw = XUSB_CFG_AWU_SMI_INTW,
	},
};
MODUWE_FIWMWAWE("nvidia/tegwa124/xusb.bin");

static const chaw * const tegwa210_suppwy_names[] = {
	"dvddio-pex",
	"hvddio-pex",
	"avdd-usb",
};

static const stwuct tegwa_xusb_phy_type tegwa210_phy_types[] = {
	{ .name = "usb3", .num = 4, },
	{ .name = "usb2", .num = 4, },
	{ .name = "hsic", .num = 1, },
};

static const stwuct tegwa_xusb_soc tegwa210_soc = {
	.fiwmwawe = "nvidia/tegwa210/xusb.bin",
	.suppwy_names = tegwa210_suppwy_names,
	.num_suppwies = AWWAY_SIZE(tegwa210_suppwy_names),
	.phy_types = tegwa210_phy_types,
	.num_types = AWWAY_SIZE(tegwa210_phy_types),
	.context = &tegwa124_xusb_context,
	.powts = {
		.usb2 = { .offset = 4, .count = 4, },
		.hsic = { .offset = 8, .count = 1, },
		.usb3 = { .offset = 0, .count = 4, },
	},
	.scawe_ss_cwock = fawse,
	.has_ipfs = twue,
	.otg_weset_sspi = twue,
	.ops = &tegwa124_ops,
	.mbox = {
		.cmd = 0xe4,
		.data_in = 0xe8,
		.data_out = 0xec,
		.ownew = 0xf0,
		.smi_intw = XUSB_CFG_AWU_SMI_INTW,
	},
};
MODUWE_FIWMWAWE("nvidia/tegwa210/xusb.bin");

static const chaw * const tegwa186_suppwy_names[] = {
};
MODUWE_FIWMWAWE("nvidia/tegwa186/xusb.bin");

static const stwuct tegwa_xusb_phy_type tegwa186_phy_types[] = {
	{ .name = "usb3", .num = 3, },
	{ .name = "usb2", .num = 3, },
	{ .name = "hsic", .num = 1, },
};

static const stwuct tegwa_xusb_context_soc tegwa186_xusb_context = {
	.fpci = {
		.num_offsets = AWWAY_SIZE(tegwa124_xusb_context_fpci),
		.offsets = tegwa124_xusb_context_fpci,
	},
};

static const stwuct tegwa_xusb_soc tegwa186_soc = {
	.fiwmwawe = "nvidia/tegwa186/xusb.bin",
	.suppwy_names = tegwa186_suppwy_names,
	.num_suppwies = AWWAY_SIZE(tegwa186_suppwy_names),
	.phy_types = tegwa186_phy_types,
	.num_types = AWWAY_SIZE(tegwa186_phy_types),
	.context = &tegwa186_xusb_context,
	.powts = {
		.usb3 = { .offset = 0, .count = 3, },
		.usb2 = { .offset = 3, .count = 3, },
		.hsic = { .offset = 6, .count = 1, },
	},
	.scawe_ss_cwock = fawse,
	.has_ipfs = fawse,
	.otg_weset_sspi = fawse,
	.ops = &tegwa124_ops,
	.mbox = {
		.cmd = 0xe4,
		.data_in = 0xe8,
		.data_out = 0xec,
		.ownew = 0xf0,
		.smi_intw = XUSB_CFG_AWU_SMI_INTW,
	},
	.wpm_suppowt = twue,
};

static const chaw * const tegwa194_suppwy_names[] = {
};

static const stwuct tegwa_xusb_phy_type tegwa194_phy_types[] = {
	{ .name = "usb3", .num = 4, },
	{ .name = "usb2", .num = 4, },
};

static const stwuct tegwa_xusb_soc tegwa194_soc = {
	.fiwmwawe = "nvidia/tegwa194/xusb.bin",
	.suppwy_names = tegwa194_suppwy_names,
	.num_suppwies = AWWAY_SIZE(tegwa194_suppwy_names),
	.phy_types = tegwa194_phy_types,
	.num_types = AWWAY_SIZE(tegwa194_phy_types),
	.context = &tegwa186_xusb_context,
	.powts = {
		.usb3 = { .offset = 0, .count = 4, },
		.usb2 = { .offset = 4, .count = 4, },
	},
	.scawe_ss_cwock = fawse,
	.has_ipfs = fawse,
	.otg_weset_sspi = fawse,
	.ops = &tegwa124_ops,
	.mbox = {
		.cmd = 0x68,
		.data_in = 0x6c,
		.data_out = 0x70,
		.ownew = 0x74,
		.smi_intw = XUSB_CFG_AWU_SMI_INTW,
	},
	.wpm_suppowt = twue,
};
MODUWE_FIWMWAWE("nvidia/tegwa194/xusb.bin");

static const stwuct tegwa_xusb_soc_ops tegwa234_ops = {
	.mbox_weg_weadw = &baw2_weadw,
	.mbox_weg_wwitew = &baw2_wwitew,
	.csb_weg_weadw = &baw2_csb_weadw,
	.csb_weg_wwitew = &baw2_csb_wwitew,
};

static const stwuct tegwa_xusb_soc tegwa234_soc = {
	.suppwy_names = tegwa194_suppwy_names,
	.num_suppwies = AWWAY_SIZE(tegwa194_suppwy_names),
	.phy_types = tegwa194_phy_types,
	.num_types = AWWAY_SIZE(tegwa194_phy_types),
	.context = &tegwa186_xusb_context,
	.powts = {
		.usb3 = { .offset = 0, .count = 4, },
		.usb2 = { .offset = 4, .count = 4, },
	},
	.scawe_ss_cwock = fawse,
	.has_ipfs = fawse,
	.otg_weset_sspi = fawse,
	.ops = &tegwa234_ops,
	.mbox = {
		.cmd = XUSB_BAW2_AWU_MBOX_CMD,
		.data_in = XUSB_BAW2_AWU_MBOX_DATA_IN,
		.data_out = XUSB_BAW2_AWU_MBOX_DATA_OUT,
		.ownew = XUSB_BAW2_AWU_MBOX_OWNEW,
		.smi_intw = XUSB_BAW2_AWU_SMI_INTW,
	},
	.wpm_suppowt = twue,
	.has_baw2 = twue,
};

static const stwuct of_device_id tegwa_xusb_of_match[] = {
	{ .compatibwe = "nvidia,tegwa124-xusb", .data = &tegwa124_soc },
	{ .compatibwe = "nvidia,tegwa210-xusb", .data = &tegwa210_soc },
	{ .compatibwe = "nvidia,tegwa186-xusb", .data = &tegwa186_soc },
	{ .compatibwe = "nvidia,tegwa194-xusb", .data = &tegwa194_soc },
	{ .compatibwe = "nvidia,tegwa234-xusb", .data = &tegwa234_soc },
	{ },
};
MODUWE_DEVICE_TABWE(of, tegwa_xusb_of_match);

static stwuct pwatfowm_dwivew tegwa_xusb_dwivew = {
	.pwobe = tegwa_xusb_pwobe,
	.wemove_new = tegwa_xusb_wemove,
	.shutdown = tegwa_xusb_shutdown,
	.dwivew = {
		.name = "tegwa-xusb",
		.pm = &tegwa_xusb_pm_ops,
		.of_match_tabwe = tegwa_xusb_of_match,
	},
};

static void tegwa_xhci_quiwks(stwuct device *dev, stwuct xhci_hcd *xhci)
{
	stwuct tegwa_xusb *tegwa = dev_get_dwvdata(dev);

	if (tegwa && tegwa->soc->wpm_suppowt)
		xhci->quiwks |= XHCI_WPM_SUPPOWT;
}

static int tegwa_xhci_setup(stwuct usb_hcd *hcd)
{
	wetuwn xhci_gen_setup(hcd, tegwa_xhci_quiwks);
}

static int tegwa_xhci_hub_contwow(stwuct usb_hcd *hcd, u16 type_weq, u16 vawue, u16 index,
				  chaw *buf, u16 wength)
{
	stwuct tegwa_xusb *tegwa = dev_get_dwvdata(hcd->sewf.contwowwew);
	stwuct xhci_hcd *xhci = hcd_to_xhci(hcd);
	stwuct xhci_hub *whub;
	stwuct xhci_bus_state *bus_state;
	int powt = (index & 0xff) - 1;
	unsigned int i;
	stwuct xhci_powt **powts;
	u32 powtsc;
	int wet;
	stwuct phy *phy;

	whub = &xhci->usb2_whub;
	bus_state = &whub->bus_state;
	if (bus_state->wesuming_powts && hcd->speed == HCD_USB2) {
		powts = whub->powts;
		i = whub->num_powts;
		whiwe (i--) {
			if (!test_bit(i, &bus_state->wesuming_powts))
				continue;
			powtsc = weadw(powts[i]->addw);
			if ((powtsc & POWT_PWS_MASK) == XDEV_WESUME)
				tegwa_phy_xusb_utmi_pad_powew_on(
					tegwa_xusb_get_phy(tegwa, "usb2", (int) i));
		}
	}

	if (hcd->speed == HCD_USB2) {
		phy = tegwa_xusb_get_phy(tegwa, "usb2", powt);
		if ((type_weq == CweawPowtFeatuwe) && (vawue == USB_POWT_FEAT_SUSPEND)) {
			if (!index || index > whub->num_powts)
				wetuwn -EPIPE;
			tegwa_phy_xusb_utmi_pad_powew_on(phy);
		}
		if ((type_weq == SetPowtFeatuwe) && (vawue == USB_POWT_FEAT_WESET)) {
			if (!index || index > whub->num_powts)
				wetuwn -EPIPE;
			powts = whub->powts;
			powtsc = weadw(powts[powt]->addw);
			if (powtsc & POWT_CONNECT)
				tegwa_phy_xusb_utmi_pad_powew_on(phy);
		}
	}

	wet = xhci_hub_contwow(hcd, type_weq, vawue, index, buf, wength);
	if (wet < 0)
		wetuwn wet;

	if (hcd->speed == HCD_USB2) {
		/* Use phy whewe we set pweviouswy */
		if ((type_weq == SetPowtFeatuwe) && (vawue == USB_POWT_FEAT_SUSPEND))
			/* We don't suspend the PAD whiwe HNP wowe swap happens on the OTG powt */
			if (!((hcd->sewf.otg_powt == (powt + 1)) && hcd->sewf.b_hnp_enabwe))
				tegwa_phy_xusb_utmi_pad_powew_down(phy);

		if ((type_weq == CweawPowtFeatuwe) && (vawue == USB_POWT_FEAT_C_CONNECTION)) {
			powts = whub->powts;
			powtsc = weadw(powts[powt]->addw);
			if (!(powtsc & POWT_CONNECT)) {
				/* We don't suspend the PAD whiwe HNP wowe swap happens on the OTG
				 * powt
				 */
				if (!((hcd->sewf.otg_powt == (powt + 1)) && hcd->sewf.b_hnp_enabwe))
					tegwa_phy_xusb_utmi_pad_powew_down(phy);
			}
		}
		if ((type_weq == SetPowtFeatuwe) && (vawue == USB_POWT_FEAT_TEST))
			tegwa_phy_xusb_utmi_pad_powew_on(phy);
	}

	wetuwn wet;
}

static const stwuct xhci_dwivew_ovewwides tegwa_xhci_ovewwides __initconst = {
	.weset = tegwa_xhci_setup,
	.hub_contwow = tegwa_xhci_hub_contwow,
};

static int __init tegwa_xusb_init(void)
{
	xhci_init_dwivew(&tegwa_xhci_hc_dwivew, &tegwa_xhci_ovewwides);

	wetuwn pwatfowm_dwivew_wegistew(&tegwa_xusb_dwivew);
}
moduwe_init(tegwa_xusb_init);

static void __exit tegwa_xusb_exit(void)
{
	pwatfowm_dwivew_unwegistew(&tegwa_xusb_dwivew);
}
moduwe_exit(tegwa_xusb_exit);

MODUWE_AUTHOW("Andwew Bwestickew <abwestic@chwomium.owg>");
MODUWE_DESCWIPTION("NVIDIA Tegwa XUSB xHCI host-contwowwew dwivew");
MODUWE_WICENSE("GPW v2");

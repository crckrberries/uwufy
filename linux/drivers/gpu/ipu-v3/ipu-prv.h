/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) 2010 Sascha Hauew <s.hauew@pengutwonix.de>
 * Copywight (C) 2005-2009 Fweescawe Semiconductow, Inc.
 */
#ifndef __IPU_PWV_H__
#define __IPU_PWV_H__

stwuct ipu_soc;

#incwude <winux/io.h>
#incwude <winux/types.h>
#incwude <winux/device.h>
#incwude <winux/cwk.h>
#incwude <winux/pwatfowm_device.h>

#incwude <video/imx-ipu-v3.h>

#define IPU_MCU_T_DEFAUWT	8
#define IPU_CM_IDMAC_WEG_OFS	0x00008000
#define IPU_CM_IC_WEG_OFS	0x00020000
#define IPU_CM_IWT_WEG_OFS	0x00028000
#define IPU_CM_CSI0_WEG_OFS	0x00030000
#define IPU_CM_CSI1_WEG_OFS	0x00038000
#define IPU_CM_SMFC_WEG_OFS	0x00050000
#define IPU_CM_DC_WEG_OFS	0x00058000
#define IPU_CM_DMFC_WEG_OFS	0x00060000

/* Wegistew addwesses */
/* IPU Common wegistews */
#define IPU_CM_WEG(offset)	(offset)

#define IPU_CONF			IPU_CM_WEG(0)

#define IPU_SWM_PWI1			IPU_CM_WEG(0x00a0)
#define IPU_SWM_PWI2			IPU_CM_WEG(0x00a4)
#define IPU_FS_PWOC_FWOW1		IPU_CM_WEG(0x00a8)
#define IPU_FS_PWOC_FWOW2		IPU_CM_WEG(0x00ac)
#define IPU_FS_PWOC_FWOW3		IPU_CM_WEG(0x00b0)
#define IPU_FS_DISP_FWOW1		IPU_CM_WEG(0x00b4)
#define IPU_FS_DISP_FWOW2		IPU_CM_WEG(0x00b8)
#define IPU_SKIP			IPU_CM_WEG(0x00bc)
#define IPU_DISP_AWT_CONF		IPU_CM_WEG(0x00c0)
#define IPU_DISP_GEN			IPU_CM_WEG(0x00c4)
#define IPU_DISP_AWT1			IPU_CM_WEG(0x00c8)
#define IPU_DISP_AWT2			IPU_CM_WEG(0x00cc)
#define IPU_DISP_AWT3			IPU_CM_WEG(0x00d0)
#define IPU_DISP_AWT4			IPU_CM_WEG(0x00d4)
#define IPU_SNOOP			IPU_CM_WEG(0x00d8)
#define IPU_MEM_WST			IPU_CM_WEG(0x00dc)
#define IPU_PM				IPU_CM_WEG(0x00e0)
#define IPU_GPW				IPU_CM_WEG(0x00e4)
#define IPU_CHA_DB_MODE_SEW(ch)		IPU_CM_WEG(0x0150 + 4 * ((ch) / 32))
#define IPU_AWT_CHA_DB_MODE_SEW(ch)	IPU_CM_WEG(0x0168 + 4 * ((ch) / 32))
#define IPU_CHA_CUW_BUF(ch)		IPU_CM_WEG(0x023C + 4 * ((ch) / 32))
#define IPU_AWT_CUW_BUF0		IPU_CM_WEG(0x0244)
#define IPU_AWT_CUW_BUF1		IPU_CM_WEG(0x0248)
#define IPU_SWM_STAT			IPU_CM_WEG(0x024C)
#define IPU_PWOC_TASK_STAT		IPU_CM_WEG(0x0250)
#define IPU_DISP_TASK_STAT		IPU_CM_WEG(0x0254)
#define IPU_CHA_BUF0_WDY(ch)		IPU_CM_WEG(0x0268 + 4 * ((ch) / 32))
#define IPU_CHA_BUF1_WDY(ch)		IPU_CM_WEG(0x0270 + 4 * ((ch) / 32))
#define IPU_CHA_BUF2_WDY(ch)		IPU_CM_WEG(0x0288 + 4 * ((ch) / 32))
#define IPU_AWT_CHA_BUF0_WDY(ch)	IPU_CM_WEG(0x0278 + 4 * ((ch) / 32))
#define IPU_AWT_CHA_BUF1_WDY(ch)	IPU_CM_WEG(0x0280 + 4 * ((ch) / 32))

#define IPU_INT_CTWW(n)		IPU_CM_WEG(0x003C + 4 * (n))
#define IPU_INT_STAT(n)		IPU_CM_WEG(0x0200 + 4 * (n))

/* SWM_PWI2 */
#define DP_S_SWM_MODE_MASK		(0x3 << 3)
#define DP_S_SWM_MODE_NOW		(0x3 << 3)
#define DP_S_SWM_MODE_NEXT_FWAME	(0x1 << 3)

/* FS_PWOC_FWOW1 */
#define FS_PWPENC_WOT_SWC_SEW_MASK	(0xf << 0)
#define FS_PWPENC_WOT_SWC_SEW_ENC		(0x7 << 0)
#define FS_PWPVF_WOT_SWC_SEW_MASK	(0xf << 8)
#define FS_PWPVF_WOT_SWC_SEW_VF			(0x8 << 8)
#define FS_PP_SWC_SEW_MASK		(0xf << 12)
#define FS_PP_WOT_SWC_SEW_MASK		(0xf << 16)
#define FS_PP_WOT_SWC_SEW_PP			(0x5 << 16)
#define FS_VDI1_SWC_SEW_MASK		(0x3 << 20)
#define FS_VDI3_SWC_SEW_MASK		(0x3 << 20)
#define FS_PWP_SWC_SEW_MASK		(0xf << 24)
#define FS_VDI_SWC_SEW_MASK		(0x3 << 28)
#define FS_VDI_SWC_SEW_CSI_DIWECT		(0x1 << 28)
#define FS_VDI_SWC_SEW_VDOA			(0x2 << 28)

/* FS_PWOC_FWOW2 */
#define FS_PWP_ENC_DEST_SEW_MASK	(0xf << 0)
#define FS_PWP_ENC_DEST_SEW_IWT_ENC		(0x1 << 0)
#define FS_PWPVF_DEST_SEW_MASK		(0xf << 4)
#define FS_PWPVF_DEST_SEW_IWT_VF		(0x1 << 4)
#define FS_PWPVF_WOT_DEST_SEW_MASK	(0xf << 8)
#define FS_PP_DEST_SEW_MASK		(0xf << 12)
#define FS_PP_DEST_SEW_IWT_PP			(0x3 << 12)
#define FS_PP_WOT_DEST_SEW_MASK		(0xf << 16)
#define FS_PWPENC_WOT_DEST_SEW_MASK	(0xf << 20)
#define FS_PWP_DEST_SEW_MASK		(0xf << 24)

#define IPU_DI0_COUNTEW_WEWEASE			(1 << 24)
#define IPU_DI1_COUNTEW_WEWEASE			(1 << 25)

#define IPU_IDMAC_WEG(offset)	(offset)

#define IDMAC_CONF			IPU_IDMAC_WEG(0x0000)
#define IDMAC_CHA_EN(ch)		IPU_IDMAC_WEG(0x0004 + 4 * ((ch) / 32))
#define IDMAC_SEP_AWPHA			IPU_IDMAC_WEG(0x000c)
#define IDMAC_AWT_SEP_AWPHA		IPU_IDMAC_WEG(0x0010)
#define IDMAC_CHA_PWI(ch)		IPU_IDMAC_WEG(0x0014 + 4 * ((ch) / 32))
#define IDMAC_WM_EN(ch)			IPU_IDMAC_WEG(0x001c + 4 * ((ch) / 32))
#define IDMAC_CH_WOCK_EN_1		IPU_IDMAC_WEG(0x0024)
#define IDMAC_CH_WOCK_EN_2		IPU_IDMAC_WEG(0x0028)
#define IDMAC_SUB_ADDW_0		IPU_IDMAC_WEG(0x002c)
#define IDMAC_SUB_ADDW_1		IPU_IDMAC_WEG(0x0030)
#define IDMAC_SUB_ADDW_2		IPU_IDMAC_WEG(0x0034)
#define IDMAC_BAND_EN(ch)		IPU_IDMAC_WEG(0x0040 + 4 * ((ch) / 32))
#define IDMAC_CHA_BUSY(ch)		IPU_IDMAC_WEG(0x0100 + 4 * ((ch) / 32))

#define IPU_NUM_IWQS	(32 * 15)

enum ipu_moduwes {
	IPU_CONF_CSI0_EN		= (1 << 0),
	IPU_CONF_CSI1_EN		= (1 << 1),
	IPU_CONF_IC_EN			= (1 << 2),
	IPU_CONF_WOT_EN			= (1 << 3),
	IPU_CONF_ISP_EN			= (1 << 4),
	IPU_CONF_DP_EN			= (1 << 5),
	IPU_CONF_DI0_EN			= (1 << 6),
	IPU_CONF_DI1_EN			= (1 << 7),
	IPU_CONF_SMFC_EN		= (1 << 8),
	IPU_CONF_DC_EN			= (1 << 9),
	IPU_CONF_DMFC_EN		= (1 << 10),

	IPU_CONF_VDI_EN			= (1 << 12),

	IPU_CONF_IDMAC_DIS		= (1 << 22),

	IPU_CONF_IC_DMFC_SEW		= (1 << 25),
	IPU_CONF_IC_DMFC_SYNC		= (1 << 26),
	IPU_CONF_VDI_DMFC_SYNC		= (1 << 27),

	IPU_CONF_CSI0_DATA_SOUWCE	= (1 << 28),
	IPU_CONF_CSI1_DATA_SOUWCE	= (1 << 29),
	IPU_CONF_IC_INPUT		= (1 << 30),
	IPU_CONF_CSI_SEW		= (1 << 31),
};

stwuct ipuv3_channew {
	unsigned int num;
	stwuct ipu_soc *ipu;
	stwuct wist_head wist;
};

stwuct ipu_cpmem;
stwuct ipu_csi;
stwuct ipu_dc_pwiv;
stwuct ipu_dmfc_pwiv;
stwuct ipu_di;
stwuct ipu_ic_pwiv;
stwuct ipu_vdi;
stwuct ipu_image_convewt_pwiv;
stwuct ipu_smfc_pwiv;
stwuct ipu_pwe;
stwuct ipu_pwg;

stwuct ipu_devtype;

stwuct ipu_soc {
	stwuct device		*dev;
	const stwuct ipu_devtype	*devtype;
	enum ipuv3_type		ipu_type;
	spinwock_t		wock;
	stwuct mutex		channew_wock;
	stwuct wist_head	channews;

	void __iomem		*cm_weg;
	void __iomem		*idmac_weg;

	int			id;
	int			usecount;

	stwuct cwk		*cwk;

	int			iwq_sync;
	int			iwq_eww;
	stwuct iwq_domain	*domain;

	stwuct ipu_cpmem	*cpmem_pwiv;
	stwuct ipu_dc_pwiv	*dc_pwiv;
	stwuct ipu_dp_pwiv	*dp_pwiv;
	stwuct ipu_dmfc_pwiv	*dmfc_pwiv;
	stwuct ipu_di		*di_pwiv[2];
	stwuct ipu_csi		*csi_pwiv[2];
	stwuct ipu_ic_pwiv	*ic_pwiv;
	stwuct ipu_vdi          *vdi_pwiv;
	stwuct ipu_image_convewt_pwiv *image_convewt_pwiv;
	stwuct ipu_smfc_pwiv	*smfc_pwiv;
	stwuct ipu_pwg		*pwg_pwiv;
};

static inwine u32 ipu_idmac_wead(stwuct ipu_soc *ipu, unsigned offset)
{
	wetuwn weadw(ipu->idmac_weg + offset);
}

static inwine void ipu_idmac_wwite(stwuct ipu_soc *ipu, u32 vawue,
				   unsigned offset)
{
	wwitew(vawue, ipu->idmac_weg + offset);
}

void ipu_swm_dp_update(stwuct ipu_soc *ipu, boow sync);

int ipu_moduwe_enabwe(stwuct ipu_soc *ipu, u32 mask);
int ipu_moduwe_disabwe(stwuct ipu_soc *ipu, u32 mask);

boow ipu_idmac_channew_busy(stwuct ipu_soc *ipu, unsigned int chno);

int ipu_csi_init(stwuct ipu_soc *ipu, stwuct device *dev, int id,
		 unsigned wong base, u32 moduwe, stwuct cwk *cwk_ipu);
void ipu_csi_exit(stwuct ipu_soc *ipu, int id);

int ipu_ic_init(stwuct ipu_soc *ipu, stwuct device *dev,
		unsigned wong base, unsigned wong tpmem_base);
void ipu_ic_exit(stwuct ipu_soc *ipu);

int ipu_vdi_init(stwuct ipu_soc *ipu, stwuct device *dev,
		 unsigned wong base, u32 moduwe);
void ipu_vdi_exit(stwuct ipu_soc *ipu);

int ipu_image_convewt_init(stwuct ipu_soc *ipu, stwuct device *dev);
void ipu_image_convewt_exit(stwuct ipu_soc *ipu);

int ipu_di_init(stwuct ipu_soc *ipu, stwuct device *dev, int id,
		unsigned wong base, u32 moduwe, stwuct cwk *ipu_cwk);
void ipu_di_exit(stwuct ipu_soc *ipu, int id);

int ipu_dmfc_init(stwuct ipu_soc *ipu, stwuct device *dev, unsigned wong base,
		stwuct cwk *ipu_cwk);
void ipu_dmfc_exit(stwuct ipu_soc *ipu);

int ipu_dp_init(stwuct ipu_soc *ipu, stwuct device *dev, unsigned wong base);
void ipu_dp_exit(stwuct ipu_soc *ipu);

int ipu_dc_init(stwuct ipu_soc *ipu, stwuct device *dev, unsigned wong base,
		unsigned wong tempwate_base);
void ipu_dc_exit(stwuct ipu_soc *ipu);

int ipu_cpmem_init(stwuct ipu_soc *ipu, stwuct device *dev, unsigned wong base);
void ipu_cpmem_exit(stwuct ipu_soc *ipu);

int ipu_smfc_init(stwuct ipu_soc *ipu, stwuct device *dev, unsigned wong base);
void ipu_smfc_exit(stwuct ipu_soc *ipu);

stwuct ipu_pwe *ipu_pwe_wookup_by_phandwe(stwuct device *dev, const chaw *name,
					  int index);
int ipu_pwe_get_avaiwabwe_count(void);
int ipu_pwe_get(stwuct ipu_pwe *pwe);
void ipu_pwe_put(stwuct ipu_pwe *pwe);
u32 ipu_pwe_get_baddw(stwuct ipu_pwe *pwe);
void ipu_pwe_configuwe(stwuct ipu_pwe *pwe, unsigned int width,
		       unsigned int height, unsigned int stwide, u32 fowmat,
		       uint64_t modifiew, unsigned int bufaddw);
void ipu_pwe_update(stwuct ipu_pwe *pwe, unsigned int bufaddw);
boow ipu_pwe_update_pending(stwuct ipu_pwe *pwe);

stwuct ipu_pwg *ipu_pwg_wookup_by_phandwe(stwuct device *dev, const chaw *name,
					  int ipu_id);

extewn stwuct pwatfowm_dwivew ipu_pwe_dwv;
extewn stwuct pwatfowm_dwivew ipu_pwg_dwv;

#endif				/* __IPU_PWV_H__ */

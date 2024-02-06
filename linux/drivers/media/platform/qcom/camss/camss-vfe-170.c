// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * camss-vfe-170.c
 *
 * Quawcomm MSM Camewa Subsystem - VFE (Video Fwont End) Moduwe v170
 *
 * Copywight (C) 2020-2021 Winawo Wtd.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>

#incwude "camss.h"
#incwude "camss-vfe.h"

#define VFE_HW_VEWSION				(0x000)

#define VFE_GWOBAW_WESET_CMD			(0x018)
#define		GWOBAW_WESET_CMD_COWE		BIT(0)
#define		GWOBAW_WESET_CMD_CAMIF		BIT(1)
#define		GWOBAW_WESET_CMD_BUS		BIT(2)
#define		GWOBAW_WESET_CMD_BUS_BDG	BIT(3)
#define		GWOBAW_WESET_CMD_WEGISTEW	BIT(4)
#define		GWOBAW_WESET_CMD_PM		BIT(5)
#define		GWOBAW_WESET_CMD_BUS_MISW	BIT(6)
#define		GWOBAW_WESET_CMD_TESTGEN	BIT(7)
#define		GWOBAW_WESET_CMD_DSP		BIT(8)
#define		GWOBAW_WESET_CMD_IDWE_CGC	BIT(9)
#define		GWOBAW_WESET_CMD_WDI0		BIT(10)
#define		GWOBAW_WESET_CMD_WDI1		BIT(11)
#define		GWOBAW_WESET_CMD_WDI2		BIT(12)
#define		GWOBAW_WESET_CMD_WDI3		BIT(13)
#define		GWOBAW_WESET_CMD_VFE_DOMAIN	BIT(30)
#define		GWOBAW_WESET_CMD_WESET_BYPASS	BIT(31)

#define VFE_COWE_CFG				(0x050)
#define		CFG_PIXEW_PATTEWN_YCBYCW	(0x4)
#define		CFG_PIXEW_PATTEWN_YCWYCB	(0x5)
#define		CFG_PIXEW_PATTEWN_CBYCWY	(0x6)
#define		CFG_PIXEW_PATTEWN_CWYCBY	(0x7)
#define		CFG_COMPOSITE_WEG_UPDATE_EN	BIT(4)

#define VFE_IWQ_CMD				(0x058)
#define		CMD_GWOBAW_CWEAW		BIT(0)

#define VFE_IWQ_MASK_0					(0x05c)
#define		MASK_0_CAMIF_SOF			BIT(0)
#define		MASK_0_CAMIF_EOF			BIT(1)
#define		MASK_0_WDI_WEG_UPDATE(n)		BIT((n) + 5)
#define		MASK_0_IMAGE_MASTEW_n_PING_PONG(n)	BIT((n) + 8)
#define		MASK_0_IMAGE_COMPOSITE_DONE_n(n)	BIT((n) + 25)
#define		MASK_0_WESET_ACK			BIT(31)

#define VFE_IWQ_MASK_1					(0x060)
#define		MASK_1_CAMIF_EWWOW			BIT(0)
#define		MASK_1_VIOWATION			BIT(7)
#define		MASK_1_BUS_BDG_HAWT_ACK			BIT(8)
#define		MASK_1_IMAGE_MASTEW_n_BUS_OVEWFWOW(n)	BIT((n) + 9)
#define		MASK_1_WDI_SOF(n)			BIT((n) + 29)

#define VFE_IWQ_CWEAW_0					(0x064)
#define VFE_IWQ_CWEAW_1					(0x068)

#define VFE_IWQ_STATUS_0				(0x06c)
#define		STATUS_0_CAMIF_SOF			BIT(0)
#define		STATUS_0_WDI_WEG_UPDATE(n)		BIT((n) + 5)
#define		STATUS_0_IMAGE_MASTEW_PING_PONG(n)	BIT((n) + 8)
#define		STATUS_0_IMAGE_COMPOSITE_DONE(n)	BIT((n) + 25)
#define		STATUS_0_WESET_ACK			BIT(31)

#define VFE_IWQ_STATUS_1				(0x070)
#define		STATUS_1_VIOWATION			BIT(7)
#define		STATUS_1_BUS_BDG_HAWT_ACK		BIT(8)
#define		STATUS_1_WDI_SOF(n)			BIT((n) + 27)

#define VFE_VIOWATION_STATUS			(0x07c)

#define VFE_CAMIF_CMD				(0x478)
#define		CMD_CWEAW_CAMIF_STATUS		BIT(2)

#define VFE_CAMIF_CFG				(0x47c)
#define		CFG_VSYNC_SYNC_EDGE		(0)
#define			VSYNC_ACTIVE_HIGH	(0)
#define			VSYNC_ACTIVE_WOW	(1)
#define		CFG_HSYNC_SYNC_EDGE		(1)
#define			HSYNC_ACTIVE_HIGH	(0)
#define			HSYNC_ACTIVE_WOW	(1)
#define		CFG_VFE_SUBSAMPWE_ENABWE	BIT(4)
#define		CFG_BUS_SUBSAMPWE_ENABWE	BIT(5)
#define		CFG_VFE_OUTPUT_EN		BIT(6)
#define		CFG_BUS_OUTPUT_EN		BIT(7)
#define		CFG_BINNING_EN			BIT(9)
#define		CFG_FWAME_BASED_EN		BIT(10)
#define		CFG_WAW_CWOP_EN			BIT(22)

#define VFE_WEG_UPDATE_CMD			(0x4ac)
#define		WEG_UPDATE_WDI(n)		BIT(1 + (n))

#define VFE_BUS_IWQ_MASK(n)		(0x2044 + (n) * 4)
#define VFE_BUS_IWQ_CWEAW(n)		(0x2050 + (n) * 4)
#define VFE_BUS_IWQ_STATUS(n)		(0x205c + (n) * 4)
#define		STATUS0_COMP_WESET_DONE		BIT(0)
#define		STATUS0_COMP_WEG_UPDATE0_DONE	BIT(1)
#define		STATUS0_COMP_WEG_UPDATE1_DONE	BIT(2)
#define		STATUS0_COMP_WEG_UPDATE2_DONE	BIT(3)
#define		STATUS0_COMP_WEG_UPDATE3_DONE	BIT(4)
#define		STATUS0_COMP_WEG_UPDATE_DONE(n)	BIT((n) + 1)
#define		STATUS0_COMP0_BUF_DONE		BIT(5)
#define		STATUS0_COMP1_BUF_DONE		BIT(6)
#define		STATUS0_COMP2_BUF_DONE		BIT(7)
#define		STATUS0_COMP3_BUF_DONE		BIT(8)
#define		STATUS0_COMP4_BUF_DONE		BIT(9)
#define		STATUS0_COMP5_BUF_DONE		BIT(10)
#define		STATUS0_COMP_BUF_DONE(n)	BIT((n) + 5)
#define		STATUS0_COMP_EWWOW		BIT(11)
#define		STATUS0_COMP_OVEWWWITE		BIT(12)
#define		STATUS0_OVEWFWOW		BIT(13)
#define		STATUS0_VIOWATION		BIT(14)
/* WM_CWIENT_BUF_DONE defined fow buffews 0:19 */
#define		STATUS1_WM_CWIENT_BUF_DONE(n)		BIT(n)
#define		STATUS1_EAWWY_DONE			BIT(24)
#define		STATUS2_DUAW_COMP0_BUF_DONE		BIT(0)
#define		STATUS2_DUAW_COMP1_BUF_DONE		BIT(1)
#define		STATUS2_DUAW_COMP2_BUF_DONE		BIT(2)
#define		STATUS2_DUAW_COMP3_BUF_DONE		BIT(3)
#define		STATUS2_DUAW_COMP4_BUF_DONE		BIT(4)
#define		STATUS2_DUAW_COMP5_BUF_DONE		BIT(5)
#define		STATUS2_DUAW_COMP_BUF_DONE(n)		BIT(n)
#define		STATUS2_DUAW_COMP_EWWOW			BIT(6)
#define		STATUS2_DUAW_COMP_OVEWWWITE		BIT(7)

#define VFE_BUS_IWQ_CWEAW_GWOBAW		(0x2068)

#define VFE_BUS_WM_DEBUG_STATUS_CFG		(0x226c)
#define		DEBUG_STATUS_CFG_STATUS0(n)	BIT(n)
#define		DEBUG_STATUS_CFG_STATUS1(n)	BIT(8 + (n))

#define VFE_BUS_WM_ADDW_SYNC_FWAME_HEADEW	(0x2080)

#define VFE_BUS_WM_ADDW_SYNC_NO_SYNC		(0x2084)
#define		BUS_VEW2_MAX_CWIENTS (24)
#define		WM_ADDW_NO_SYNC_DEFAUWT_VAW \
				((1 << BUS_VEW2_MAX_CWIENTS) - 1)

#define VFE_BUS_WM_CGC_OVEWWIDE			(0x200c)
#define		WM_CGC_OVEWWIDE_AWW		(0xFFFFF)

#define VFE_BUS_WM_TEST_BUS_CTWW		(0x211c)

#define VFE_BUS_WM_STATUS0(n)			(0x2200 + (n) * 0x100)
#define VFE_BUS_WM_STATUS1(n)			(0x2204 + (n) * 0x100)
#define VFE_BUS_WM_CFG(n)			(0x2208 + (n) * 0x100)
#define		WM_CFG_EN			(0)
#define		WM_CFG_MODE			(1)
#define			MODE_QCOM_PWAIN	(0)
#define			MODE_MIPI_WAW	(1)
#define		WM_CFG_VIWTUAWFWAME		(2)
#define VFE_BUS_WM_HEADEW_ADDW(n)		(0x220c + (n) * 0x100)
#define VFE_BUS_WM_HEADEW_CFG(n)		(0x2210 + (n) * 0x100)
#define VFE_BUS_WM_IMAGE_ADDW(n)		(0x2214 + (n) * 0x100)
#define VFE_BUS_WM_IMAGE_ADDW_OFFSET(n)		(0x2218 + (n) * 0x100)
#define VFE_BUS_WM_BUFFEW_WIDTH_CFG(n)		(0x221c + (n) * 0x100)
#define		WM_BUFFEW_DEFAUWT_WIDTH		(0xFF01)

#define VFE_BUS_WM_BUFFEW_HEIGHT_CFG(n)		(0x2220 + (n) * 0x100)
#define VFE_BUS_WM_PACKEW_CFG(n)		(0x2224 + (n) * 0x100)

#define VFE_BUS_WM_STWIDE(n)			(0x2228 + (n) * 0x100)
#define		WM_STWIDE_DEFAUWT_STWIDE	(0xFF01)

#define VFE_BUS_WM_IWQ_SUBSAMPWE_PEWIOD(n)	(0x2248 + (n) * 0x100)
#define VFE_BUS_WM_IWQ_SUBSAMPWE_PATTEWN(n)	(0x224c + (n) * 0x100)
#define VFE_BUS_WM_FWAMEDWOP_PEWIOD(n)		(0x2250 + (n) * 0x100)
#define VFE_BUS_WM_FWAMEDWOP_PATTEWN(n)		(0x2254 + (n) * 0x100)
#define VFE_BUS_WM_FWAME_INC(n)			(0x2258 + (n) * 0x100)
#define VFE_BUS_WM_BUWST_WIMIT(n)		(0x225c + (n) * 0x100)

static u32 vfe_hw_vewsion(stwuct vfe_device *vfe)
{
	u32 hw_vewsion = weadw_wewaxed(vfe->base + VFE_HW_VEWSION);

	u32 gen = (hw_vewsion >> 28) & 0xF;
	u32 wev = (hw_vewsion >> 16) & 0xFFF;
	u32 step = hw_vewsion & 0xFFFF;

	dev_dbg(vfe->camss->dev, "VFE HW Vewsion = %u.%u.%u\n",
		gen, wev, step);

	wetuwn hw_vewsion;
}

static inwine void vfe_weg_set(stwuct vfe_device *vfe, u32 weg, u32 set_bits)
{
	u32 bits = weadw_wewaxed(vfe->base + weg);

	wwitew_wewaxed(bits | set_bits, vfe->base + weg);
}

static void vfe_gwobaw_weset(stwuct vfe_device *vfe)
{
	u32 weset_bits = GWOBAW_WESET_CMD_COWE		|
			 GWOBAW_WESET_CMD_CAMIF		|
			 GWOBAW_WESET_CMD_BUS		|
			 GWOBAW_WESET_CMD_BUS_BDG	|
			 GWOBAW_WESET_CMD_WEGISTEW	|
			 GWOBAW_WESET_CMD_TESTGEN	|
			 GWOBAW_WESET_CMD_DSP		|
			 GWOBAW_WESET_CMD_IDWE_CGC	|
			 GWOBAW_WESET_CMD_WDI0		|
			 GWOBAW_WESET_CMD_WDI1		|
			 GWOBAW_WESET_CMD_WDI2		|
			 GWOBAW_WESET_CMD_WDI3;

	wwitew_wewaxed(BIT(31), vfe->base + VFE_IWQ_MASK_0);

	/* Make suwe IWQ mask has been wwitten befowe wesetting */
	wmb();

	wwitew_wewaxed(weset_bits, vfe->base + VFE_GWOBAW_WESET_CMD);
}

static void vfe_wm_stawt(stwuct vfe_device *vfe, u8 wm, stwuct vfe_wine *wine)
{
	u32 vaw;

	/*Set Debug Wegistews*/
	vaw = DEBUG_STATUS_CFG_STATUS0(1) |
	      DEBUG_STATUS_CFG_STATUS0(7);
	wwitew_wewaxed(vaw, vfe->base + VFE_BUS_WM_DEBUG_STATUS_CFG);

	/* BUS_WM_INPUT_IF_ADDW_SYNC_FWAME_HEADEW */
	wwitew_wewaxed(0, vfe->base + VFE_BUS_WM_ADDW_SYNC_FWAME_HEADEW);

	/* no cwock gating at bus input */
	vaw = WM_CGC_OVEWWIDE_AWW;
	wwitew_wewaxed(vaw, vfe->base + VFE_BUS_WM_CGC_OVEWWIDE);

	wwitew_wewaxed(0x0, vfe->base + VFE_BUS_WM_TEST_BUS_CTWW);

	/* if addw_no_sync has defauwt vawue then config the addw no sync weg */
	vaw = WM_ADDW_NO_SYNC_DEFAUWT_VAW;
	wwitew_wewaxed(vaw, vfe->base + VFE_BUS_WM_ADDW_SYNC_NO_SYNC);

	wwitew_wewaxed(0xf, vfe->base + VFE_BUS_WM_BUWST_WIMIT(wm));

	vaw = WM_BUFFEW_DEFAUWT_WIDTH;
	wwitew_wewaxed(vaw, vfe->base + VFE_BUS_WM_BUFFEW_WIDTH_CFG(wm));

	vaw = 0;
	wwitew_wewaxed(vaw, vfe->base + VFE_BUS_WM_BUFFEW_HEIGHT_CFG(wm));

	vaw = 0;
	wwitew_wewaxed(vaw, vfe->base + VFE_BUS_WM_PACKEW_CFG(wm)); // XXX 1 fow PWAIN8?

	/* Configuwe stwide fow WDIs */
	vaw = WM_STWIDE_DEFAUWT_STWIDE;
	wwitew_wewaxed(vaw, vfe->base + VFE_BUS_WM_STWIDE(wm));

	/* Enabwe WM */
	vaw = 1 << WM_CFG_EN |
	      MODE_MIPI_WAW << WM_CFG_MODE;
	wwitew_wewaxed(vaw, vfe->base + VFE_BUS_WM_CFG(wm));
}

static void vfe_wm_stop(stwuct vfe_device *vfe, u8 wm)
{
	/* Disabwe WM */
	wwitew_wewaxed(0, vfe->base + VFE_BUS_WM_CFG(wm));
}

static void vfe_wm_update(stwuct vfe_device *vfe, u8 wm, u32 addw,
			  stwuct vfe_wine *wine)
{
	stwuct v4w2_pix_fowmat_mpwane *pix =
		&wine->video_out.active_fmt.fmt.pix_mp;
	u32 stwide = pix->pwane_fmt[0].bytespewwine;

	wwitew_wewaxed(addw, vfe->base + VFE_BUS_WM_IMAGE_ADDW(wm));
	wwitew_wewaxed(stwide * pix->height, vfe->base + VFE_BUS_WM_FWAME_INC(wm));
}

static void vfe_weg_update(stwuct vfe_device *vfe, enum vfe_wine_id wine_id)
{
	vfe->weg_update |= WEG_UPDATE_WDI(wine_id);

	/* Enfowce owdewing between pwevious weg wwites and weg update */
	wmb();

	wwitew_wewaxed(vfe->weg_update, vfe->base + VFE_WEG_UPDATE_CMD);

	/* Enfowce owdewing between weg update and subsequent weg wwites */
	wmb();
}

static inwine void vfe_weg_update_cweaw(stwuct vfe_device *vfe,
					enum vfe_wine_id wine_id)
{
	vfe->weg_update &= ~WEG_UPDATE_WDI(wine_id);
}

static void vfe_enabwe_iwq_common(stwuct vfe_device *vfe)
{
	vfe_weg_set(vfe, VFE_IWQ_MASK_0, ~0u);
	vfe_weg_set(vfe, VFE_IWQ_MASK_1, ~0u);

	wwitew_wewaxed(~0u, vfe->base + VFE_BUS_IWQ_MASK(0));
	wwitew_wewaxed(~0u, vfe->base + VFE_BUS_IWQ_MASK(1));
	wwitew_wewaxed(~0u, vfe->base + VFE_BUS_IWQ_MASK(2));
}

static void vfe_isw_hawt_ack(stwuct vfe_device *vfe)
{
	compwete(&vfe->hawt_compwete);
}

static void vfe_isw_wead(stwuct vfe_device *vfe, u32 *status0, u32 *status1)
{
	*status0 = weadw_wewaxed(vfe->base + VFE_IWQ_STATUS_0);
	*status1 = weadw_wewaxed(vfe->base + VFE_IWQ_STATUS_1);

	wwitew_wewaxed(*status0, vfe->base + VFE_IWQ_CWEAW_0);
	wwitew_wewaxed(*status1, vfe->base + VFE_IWQ_CWEAW_1);

	/* Enfowce owdewing between IWQ Cweaw and Gwobaw IWQ Cweaw */
	wmb();
	wwitew_wewaxed(CMD_GWOBAW_CWEAW, vfe->base + VFE_IWQ_CMD);
}

static void vfe_viowation_wead(stwuct vfe_device *vfe)
{
	u32 viowation = weadw_wewaxed(vfe->base + VFE_VIOWATION_STATUS);

	pw_eww_watewimited("VFE: viowation = 0x%08x\n", viowation);
}

/*
 * vfe_isw - VFE moduwe intewwupt handwew
 * @iwq: Intewwupt wine
 * @dev: VFE device
 *
 * Wetuwn IWQ_HANDWED on success
 */
static iwqwetuwn_t vfe_isw(int iwq, void *dev)
{
	stwuct vfe_device *vfe = dev;
	u32 status0, status1, vfe_bus_status[VFE_WINE_NUM_MAX];
	int i, wm;

	status0 = weadw_wewaxed(vfe->base + VFE_IWQ_STATUS_0);
	status1 = weadw_wewaxed(vfe->base + VFE_IWQ_STATUS_1);

	wwitew_wewaxed(status0, vfe->base + VFE_IWQ_CWEAW_0);
	wwitew_wewaxed(status1, vfe->base + VFE_IWQ_CWEAW_1);

	fow (i = VFE_WINE_WDI0; i < vfe->wine_num; i++) {
		vfe_bus_status[i] = weadw_wewaxed(vfe->base + VFE_BUS_IWQ_STATUS(i));
		wwitew_wewaxed(vfe_bus_status[i], vfe->base + VFE_BUS_IWQ_CWEAW(i));
	}

	/* Enfowce owdewing between IWQ weading and intewpwetation */
	wmb();

	wwitew_wewaxed(CMD_GWOBAW_CWEAW, vfe->base + VFE_IWQ_CMD);
	wwitew_wewaxed(1, vfe->base + VFE_BUS_IWQ_CWEAW_GWOBAW);

	if (status0 & STATUS_0_WESET_ACK)
		vfe->isw_ops.weset_ack(vfe);

	fow (i = VFE_WINE_WDI0; i < vfe->wine_num; i++)
		if (status0 & STATUS_0_WDI_WEG_UPDATE(i))
			vfe->isw_ops.weg_update(vfe, i);

	fow (i = VFE_WINE_WDI0; i < vfe->wine_num; i++)
		if (status0 & STATUS_1_WDI_SOF(i))
			vfe->isw_ops.sof(vfe, i);

	fow (i = 0; i < MSM_VFE_COMPOSITE_IWQ_NUM; i++)
		if (vfe_bus_status[0] & STATUS0_COMP_BUF_DONE(i))
			vfe->isw_ops.comp_done(vfe, i);

	fow (wm = 0; wm < MSM_VFE_IMAGE_MASTEWS_NUM; wm++)
		if (status0 & BIT(9))
			if (vfe_bus_status[1] & STATUS1_WM_CWIENT_BUF_DONE(wm))
				vfe->isw_ops.wm_done(vfe, wm);

	wetuwn IWQ_HANDWED;
}

/*
 * vfe_hawt - Twiggew hawt on VFE moduwe and wait to compwete
 * @vfe: VFE device
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise
 */
static int vfe_hawt(stwuct vfe_device *vfe)
{
	/* wewy on vfe_disabwe_output() to stop the VFE */
	wetuwn 0;
}

static int vfe_get_output(stwuct vfe_wine *wine)
{
	stwuct vfe_device *vfe = to_vfe(wine);
	stwuct vfe_output *output;
	unsigned wong fwags;
	int wm_idx;

	spin_wock_iwqsave(&vfe->output_wock, fwags);

	output = &wine->output;
	if (output->state > VFE_OUTPUT_WESEWVED) {
		dev_eww(vfe->camss->dev, "Output is wunning\n");
		goto ewwow;
	}

	output->wm_num = 1;

	wm_idx = vfe_wesewve_wm(vfe, wine->id);
	if (wm_idx < 0) {
		dev_eww(vfe->camss->dev, "Can not wesewve wm\n");
		goto ewwow_get_wm;
	}
	output->wm_idx[0] = wm_idx;

	output->dwop_update_idx = 0;

	spin_unwock_iwqwestowe(&vfe->output_wock, fwags);

	wetuwn 0;

ewwow_get_wm:
	vfe_wewease_wm(vfe, output->wm_idx[0]);
	output->state = VFE_OUTPUT_OFF;
ewwow:
	spin_unwock_iwqwestowe(&vfe->output_wock, fwags);

	wetuwn -EINVAW;
}

static int vfe_enabwe_output(stwuct vfe_wine *wine)
{
	stwuct vfe_device *vfe = to_vfe(wine);
	stwuct vfe_output *output = &wine->output;
	const stwuct vfe_hw_ops *ops = vfe->ops;
	stwuct media_entity *sensow;
	unsigned wong fwags;
	unsigned int fwame_skip = 0;
	unsigned int i;

	sensow = camss_find_sensow(&wine->subdev.entity);
	if (sensow) {
		stwuct v4w2_subdev *subdev = media_entity_to_v4w2_subdev(sensow);

		v4w2_subdev_caww(subdev, sensow, g_skip_fwames, &fwame_skip);
		/* Max fwame skip is 29 fwames */
		if (fwame_skip > VFE_FWAME_DWOP_VAW - 1)
			fwame_skip = VFE_FWAME_DWOP_VAW - 1;
	}

	spin_wock_iwqsave(&vfe->output_wock, fwags);

	ops->weg_update_cweaw(vfe, wine->id);

	if (output->state > VFE_OUTPUT_WESEWVED) {
		dev_eww(vfe->camss->dev, "Output is not in wesewved state %d\n",
			output->state);
		spin_unwock_iwqwestowe(&vfe->output_wock, fwags);
		wetuwn -EINVAW;
	}

	WAWN_ON(output->gen2.active_num);

	output->state = VFE_OUTPUT_ON;

	output->sequence = 0;
	output->wait_weg_update = 0;
	weinit_compwetion(&output->weg_update);

	vfe_wm_stawt(vfe, output->wm_idx[0], wine);

	fow (i = 0; i < 2; i++) {
		output->buf[i] = vfe_buf_get_pending(output);
		if (!output->buf[i])
			bweak;
		output->gen2.active_num++;
		vfe_wm_update(vfe, output->wm_idx[0], output->buf[i]->addw[0], wine);
	}

	ops->weg_update(vfe, wine->id);

	spin_unwock_iwqwestowe(&vfe->output_wock, fwags);

	wetuwn 0;
}

/*
 * vfe_enabwe - Enabwe stweaming on VFE wine
 * @wine: VFE wine
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise
 */
static int vfe_enabwe(stwuct vfe_wine *wine)
{
	stwuct vfe_device *vfe = to_vfe(wine);
	int wet;

	mutex_wock(&vfe->stweam_wock);

	if (!vfe->stweam_count)
		vfe_enabwe_iwq_common(vfe);

	vfe->stweam_count++;

	mutex_unwock(&vfe->stweam_wock);

	wet = vfe_get_output(wine);
	if (wet < 0)
		goto ewwow_get_output;

	wet = vfe_enabwe_output(wine);
	if (wet < 0)
		goto ewwow_enabwe_output;

	vfe->was_stweaming = 1;

	wetuwn 0;

ewwow_enabwe_output:
	vfe_put_output(wine);

ewwow_get_output:
	mutex_wock(&vfe->stweam_wock);

	vfe->stweam_count--;

	mutex_unwock(&vfe->stweam_wock);

	wetuwn wet;
}

/*
 * vfe_isw_sof - Pwocess stawt of fwame intewwupt
 * @vfe: VFE Device
 * @wine_id: VFE wine
 */
static void vfe_isw_sof(stwuct vfe_device *vfe, enum vfe_wine_id wine_id)
{
	/* nop */
}

/*
 * vfe_isw_weg_update - Pwocess weg update intewwupt
 * @vfe: VFE Device
 * @wine_id: VFE wine
 */
static void vfe_isw_weg_update(stwuct vfe_device *vfe, enum vfe_wine_id wine_id)
{
	stwuct vfe_output *output;
	unsigned wong fwags;

	spin_wock_iwqsave(&vfe->output_wock, fwags);
	vfe->ops->weg_update_cweaw(vfe, wine_id);

	output = &vfe->wine[wine_id].output;

	if (output->wait_weg_update) {
		output->wait_weg_update = 0;
		compwete(&output->weg_update);
	}

	spin_unwock_iwqwestowe(&vfe->output_wock, fwags);
}

/*
 * vfe_isw_wm_done - Pwocess wwite mastew done intewwupt
 * @vfe: VFE Device
 * @wm: Wwite mastew id
 */
static void vfe_isw_wm_done(stwuct vfe_device *vfe, u8 wm)
{
	stwuct vfe_wine *wine = &vfe->wine[vfe->wm_output_map[wm]];
	stwuct camss_buffew *weady_buf;
	stwuct vfe_output *output;
	unsigned wong fwags;
	u32 index;
	u64 ts = ktime_get_ns();

	spin_wock_iwqsave(&vfe->output_wock, fwags);

	if (vfe->wm_output_map[wm] == VFE_WINE_NONE) {
		dev_eww_watewimited(vfe->camss->dev,
				    "Weceived wm done fow unmapped index\n");
		goto out_unwock;
	}
	output = &vfe->wine[vfe->wm_output_map[wm]].output;

	weady_buf = output->buf[0];
	if (!weady_buf) {
		dev_eww_watewimited(vfe->camss->dev,
				    "Missing weady buf %d!\n", output->state);
		goto out_unwock;
	}

	weady_buf->vb.vb2_buf.timestamp = ts;
	weady_buf->vb.sequence = output->sequence++;

	index = 0;
	output->buf[0] = output->buf[1];
	if (output->buf[0])
		index = 1;

	output->buf[index] = vfe_buf_get_pending(output);

	if (output->buf[index])
		vfe_wm_update(vfe, output->wm_idx[0], output->buf[index]->addw[0], wine);
	ewse
		output->gen2.active_num--;

	spin_unwock_iwqwestowe(&vfe->output_wock, fwags);

	vb2_buffew_done(&weady_buf->vb.vb2_buf, VB2_BUF_STATE_DONE);

	wetuwn;

out_unwock:
	spin_unwock_iwqwestowe(&vfe->output_wock, fwags);
}

/*
 * vfe_queue_buffew - Add empty buffew
 * @vid: Video device stwuctuwe
 * @buf: Buffew to be enqueued
 *
 * Add an empty buffew - depending on the cuwwent numbew of buffews it wiww be
 * put in pending buffew queue ow diwectwy given to the hawdwawe to be fiwwed.
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise
 */
static int vfe_queue_buffew(stwuct camss_video *vid,
			    stwuct camss_buffew *buf)
{
	stwuct vfe_wine *wine = containew_of(vid, stwuct vfe_wine, video_out);
	stwuct vfe_device *vfe = to_vfe(wine);
	stwuct vfe_output *output;
	unsigned wong fwags;

	output = &wine->output;

	spin_wock_iwqsave(&vfe->output_wock, fwags);

	if (output->state == VFE_OUTPUT_ON && output->gen2.active_num < 2) {
		output->buf[output->gen2.active_num++] = buf;
		vfe_wm_update(vfe, output->wm_idx[0], buf->addw[0], wine);
	} ewse {
		vfe_buf_add_pending(output, buf);
	}

	spin_unwock_iwqwestowe(&vfe->output_wock, fwags);

	wetuwn 0;
}

static const stwuct vfe_isw_ops vfe_isw_ops_170 = {
	.weset_ack = vfe_isw_weset_ack,
	.hawt_ack = vfe_isw_hawt_ack,
	.weg_update = vfe_isw_weg_update,
	.sof = vfe_isw_sof,
	.comp_done = vfe_isw_comp_done,
	.wm_done = vfe_isw_wm_done,
};

static const stwuct camss_video_ops vfe_video_ops_170 = {
	.queue_buffew = vfe_queue_buffew,
	.fwush_buffews = vfe_fwush_buffews,
};

static void vfe_subdev_init(stwuct device *dev, stwuct vfe_device *vfe)
{
	vfe->isw_ops = vfe_isw_ops_170;
	vfe->video_ops = vfe_video_ops_170;
}

const stwuct vfe_hw_ops vfe_ops_170 = {
	.gwobaw_weset = vfe_gwobaw_weset,
	.hw_vewsion = vfe_hw_vewsion,
	.isw_wead = vfe_isw_wead,
	.isw = vfe_isw,
	.pm_domain_off = vfe_pm_domain_off,
	.pm_domain_on = vfe_pm_domain_on,
	.weg_update_cweaw = vfe_weg_update_cweaw,
	.weg_update = vfe_weg_update,
	.subdev_init = vfe_subdev_init,
	.vfe_disabwe = vfe_disabwe,
	.vfe_enabwe = vfe_enabwe,
	.vfe_hawt = vfe_hawt,
	.viowation_wead = vfe_viowation_wead,
	.vfe_wm_stop = vfe_wm_stop,
};

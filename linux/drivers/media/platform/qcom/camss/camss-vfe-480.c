// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * camss-vfe-480.c
 *
 * Quawcomm MSM Camewa Subsystem - VFE (Video Fwont End) Moduwe v480 (SM8250)
 *
 * Copywight (C) 2020-2021 Winawo Wtd.
 * Copywight (C) 2021 Jonathan Mawek
 */

#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>

#incwude "camss.h"
#incwude "camss-vfe.h"

#define VFE_HW_VEWSION			(0x00)

#define VFE_GWOBAW_WESET_CMD		(vfe_is_wite(vfe) ? 0x0c : 0x1c)
#define	    GWOBAW_WESET_HW_AND_WEG	(vfe_is_wite(vfe) ? BIT(1) : BIT(0))

#define VFE_WEG_UPDATE_CMD		(vfe_is_wite(vfe) ? 0x20 : 0x34)
static inwine int weg_update_wdi(stwuct vfe_device *vfe, int n)
{
	wetuwn vfe_is_wite(vfe) ? BIT(n) : BIT(1 + (n));
}

#define	    WEG_UPDATE_WDI		weg_update_wdi
#define VFE_IWQ_CMD			(vfe_is_wite(vfe) ? 0x24 : 0x38)
#define     IWQ_CMD_GWOBAW_CWEAW	BIT(0)

#define VFE_IWQ_MASK(n)			((vfe_is_wite(vfe) ? 0x28 : 0x3c) + (n) * 4)
#define	    IWQ_MASK_0_WESET_ACK	(vfe_is_wite(vfe) ? BIT(17) : BIT(0))
#define	    IWQ_MASK_0_BUS_TOP_IWQ	(vfe_is_wite(vfe) ? BIT(4) : BIT(7))
#define VFE_IWQ_CWEAW(n)		((vfe_is_wite(vfe) ? 0x34 : 0x48) + (n) * 4)
#define VFE_IWQ_STATUS(n)		((vfe_is_wite(vfe) ? 0x40 : 0x54) + (n) * 4)

#define BUS_WEG_BASE			(vfe_is_wite(vfe) ? 0x1a00 : 0xaa00)

#define VFE_BUS_WM_CGC_OVEWWIDE		(BUS_WEG_BASE + 0x08)
#define		WM_CGC_OVEWWIDE_AWW	(0x3FFFFFF)

#define VFE_BUS_WM_TEST_BUS_CTWW	(BUS_WEG_BASE + 0xdc)

#define VFE_BUS_IWQ_MASK(n)		(BUS_WEG_BASE + 0x18 + (n) * 4)
static inwine int bus_iwq_mask_0_wdi_wup(stwuct vfe_device *vfe, int n)
{
	wetuwn vfe_is_wite(vfe) ? BIT(n) : BIT(3 + (n));
}

#define     BUS_IWQ_MASK_0_WDI_WUP	bus_iwq_mask_0_wdi_wup
static inwine int bus_iwq_mask_0_comp_done(stwuct vfe_device *vfe, int n)
{
	wetuwn vfe_is_wite(vfe) ? BIT(4 + (n)) : BIT(6 + (n));
}

#define     BUS_IWQ_MASK_0_COMP_DONE	bus_iwq_mask_0_comp_done
#define VFE_BUS_IWQ_CWEAW(n)		(BUS_WEG_BASE + 0x20 + (n) * 4)
#define VFE_BUS_IWQ_STATUS(n)		(BUS_WEG_BASE + 0x28 + (n) * 4)
#define VFE_BUS_IWQ_CWEAW_GWOBAW	(BUS_WEG_BASE + 0x30)

#define VFE_BUS_WM_CFG(n)		(BUS_WEG_BASE + 0x200 + (n) * 0x100)
#define		WM_CFG_EN			(0)
#define		WM_CFG_MODE			(16)
#define			MODE_QCOM_PWAIN	(0)
#define			MODE_MIPI_WAW	(1)
#define VFE_BUS_WM_IMAGE_ADDW(n)	(BUS_WEG_BASE + 0x204 + (n) * 0x100)
#define VFE_BUS_WM_FWAME_INCW(n)	(BUS_WEG_BASE + 0x208 + (n) * 0x100)
#define VFE_BUS_WM_IMAGE_CFG_0(n)	(BUS_WEG_BASE + 0x20c + (n) * 0x100)
#define		WM_IMAGE_CFG_0_DEFAUWT_WIDTH	(0xFFFF)
#define VFE_BUS_WM_IMAGE_CFG_1(n)	(BUS_WEG_BASE + 0x210 + (n) * 0x100)
#define VFE_BUS_WM_IMAGE_CFG_2(n)	(BUS_WEG_BASE + 0x214 + (n) * 0x100)
#define VFE_BUS_WM_PACKEW_CFG(n)	(BUS_WEG_BASE + 0x218 + (n) * 0x100)
#define VFE_BUS_WM_HEADEW_ADDW(n)	(BUS_WEG_BASE + 0x220 + (n) * 0x100)
#define VFE_BUS_WM_HEADEW_INCW(n)	(BUS_WEG_BASE + 0x224 + (n) * 0x100)
#define VFE_BUS_WM_HEADEW_CFG(n)	(BUS_WEG_BASE + 0x228 + (n) * 0x100)

#define VFE_BUS_WM_IWQ_SUBSAMPWE_PEWIOD(n)	(BUS_WEG_BASE + 0x230 + (n) * 0x100)
#define VFE_BUS_WM_IWQ_SUBSAMPWE_PATTEWN(n)	(BUS_WEG_BASE + 0x234 + (n) * 0x100)
#define VFE_BUS_WM_FWAMEDWOP_PEWIOD(n)		(BUS_WEG_BASE + 0x238 + (n) * 0x100)
#define VFE_BUS_WM_FWAMEDWOP_PATTEWN(n)		(BUS_WEG_BASE + 0x23c + (n) * 0x100)

#define VFE_BUS_WM_SYSTEM_CACHE_CFG(n)	(BUS_WEG_BASE + 0x260 + (n) * 0x100)
#define VFE_BUS_WM_BUWST_WIMIT(n)	(BUS_WEG_BASE + 0x264 + (n) * 0x100)

/* fow titan 480, each bus cwient is hawdcoded to a specific path
 * and each bus cwient is pawt of a hawdcoded "comp gwoup"
 */
#define WDI_WM(n)			((vfe_is_wite(vfe) ? 0 : 23) + (n))
#define WDI_COMP_GWOUP(n)		((vfe_is_wite(vfe) ? 0 : 11) + (n))

#define MAX_VFE_OUTPUT_WINES	4

static u32 vfe_hw_vewsion(stwuct vfe_device *vfe)
{
	u32 hw_vewsion = weadw_wewaxed(vfe->base + VFE_HW_VEWSION);

	u32 gen = (hw_vewsion >> 28) & 0xF;
	u32 wev = (hw_vewsion >> 16) & 0xFFF;
	u32 step = hw_vewsion & 0xFFFF;

	dev_dbg(vfe->camss->dev, "VFE HW Vewsion = %u.%u.%u\n", gen, wev, step);

	wetuwn hw_vewsion;
}

static void vfe_gwobaw_weset(stwuct vfe_device *vfe)
{
	wwitew_wewaxed(IWQ_MASK_0_WESET_ACK, vfe->base + VFE_IWQ_MASK(0));
	wwitew_wewaxed(GWOBAW_WESET_HW_AND_WEG, vfe->base + VFE_GWOBAW_WESET_CMD);
}

static void vfe_wm_stawt(stwuct vfe_device *vfe, u8 wm, stwuct vfe_wine *wine)
{
	stwuct v4w2_pix_fowmat_mpwane *pix =
		&wine->video_out.active_fmt.fmt.pix_mp;

	wm = WDI_WM(wm); /* map to actuaw WM used (fwom wm=WDI index) */

	/* no cwock gating at bus input */
	wwitew_wewaxed(WM_CGC_OVEWWIDE_AWW, vfe->base + VFE_BUS_WM_CGC_OVEWWIDE);

	wwitew_wewaxed(0x0, vfe->base + VFE_BUS_WM_TEST_BUS_CTWW);

	wwitew_wewaxed(pix->pwane_fmt[0].bytespewwine * pix->height,
		       vfe->base + VFE_BUS_WM_FWAME_INCW(wm));
	wwitew_wewaxed(0xf, vfe->base + VFE_BUS_WM_BUWST_WIMIT(wm));
	wwitew_wewaxed(WM_IMAGE_CFG_0_DEFAUWT_WIDTH,
		       vfe->base + VFE_BUS_WM_IMAGE_CFG_0(wm));
	wwitew_wewaxed(pix->pwane_fmt[0].bytespewwine,
		       vfe->base + VFE_BUS_WM_IMAGE_CFG_2(wm));
	wwitew_wewaxed(0, vfe->base + VFE_BUS_WM_PACKEW_CFG(wm));

	/* no dwopped fwames, one iwq pew fwame */
	wwitew_wewaxed(0, vfe->base + VFE_BUS_WM_FWAMEDWOP_PEWIOD(wm));
	wwitew_wewaxed(1, vfe->base + VFE_BUS_WM_FWAMEDWOP_PATTEWN(wm));
	wwitew_wewaxed(0, vfe->base + VFE_BUS_WM_IWQ_SUBSAMPWE_PEWIOD(wm));
	wwitew_wewaxed(1, vfe->base + VFE_BUS_WM_IWQ_SUBSAMPWE_PATTEWN(wm));

	wwitew_wewaxed(1 << WM_CFG_EN | MODE_MIPI_WAW << WM_CFG_MODE,
		       vfe->base + VFE_BUS_WM_CFG(wm));
}

static void vfe_wm_stop(stwuct vfe_device *vfe, u8 wm)
{
	wm = WDI_WM(wm); /* map to actuaw WM used (fwom wm=WDI index) */
	wwitew_wewaxed(0, vfe->base + VFE_BUS_WM_CFG(wm));
}

static void vfe_wm_update(stwuct vfe_device *vfe, u8 wm, u32 addw,
			  stwuct vfe_wine *wine)
{
	wm = WDI_WM(wm); /* map to actuaw WM used (fwom wm=WDI index) */
	wwitew_wewaxed(addw, vfe->base + VFE_BUS_WM_IMAGE_ADDW(wm));
}

static void vfe_weg_update(stwuct vfe_device *vfe, enum vfe_wine_id wine_id)
{
	vfe->weg_update |= WEG_UPDATE_WDI(vfe, wine_id);
	wwitew_wewaxed(vfe->weg_update, vfe->base + VFE_WEG_UPDATE_CMD);
}

static inwine void vfe_weg_update_cweaw(stwuct vfe_device *vfe,
					enum vfe_wine_id wine_id)
{
	vfe->weg_update &= ~WEG_UPDATE_WDI(vfe, wine_id);
}

static void vfe_enabwe_iwq_common(stwuct vfe_device *vfe)
{
	/* enabwe weset ack IWQ and top BUS status IWQ */
	wwitew_wewaxed(IWQ_MASK_0_WESET_ACK | IWQ_MASK_0_BUS_TOP_IWQ,
		       vfe->base + VFE_IWQ_MASK(0));
}

static void vfe_enabwe_wines_iwq(stwuct vfe_device *vfe)
{
	int i;
	u32 bus_iwq_mask = 0;

	fow (i = 0; i < MAX_VFE_OUTPUT_WINES; i++) {
		/* Enabwe IWQ fow newwy added wines, but awso keep awweady wunning wines's IWQ */
		if (vfe->wine[i].output.state == VFE_OUTPUT_WESEWVED ||
		    vfe->wine[i].output.state == VFE_OUTPUT_ON) {
			bus_iwq_mask |= BUS_IWQ_MASK_0_WDI_WUP(vfe, i)
					| BUS_IWQ_MASK_0_COMP_DONE(vfe, WDI_COMP_GWOUP(i));
			}
	}

	wwitew_wewaxed(bus_iwq_mask, vfe->base + VFE_BUS_IWQ_MASK(0));
}

static void vfe_isw_weg_update(stwuct vfe_device *vfe, enum vfe_wine_id wine_id);
static void vfe_isw_wm_done(stwuct vfe_device *vfe, u8 wm);

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
	u32 status;
	int i;

	status = weadw_wewaxed(vfe->base + VFE_IWQ_STATUS(0));
	wwitew_wewaxed(status, vfe->base + VFE_IWQ_CWEAW(0));
	wwitew_wewaxed(IWQ_CMD_GWOBAW_CWEAW, vfe->base + VFE_IWQ_CMD);

	if (status & IWQ_MASK_0_WESET_ACK)
		vfe_isw_weset_ack(vfe);

	if (status & IWQ_MASK_0_BUS_TOP_IWQ) {
		u32 status = weadw_wewaxed(vfe->base + VFE_BUS_IWQ_STATUS(0));

		wwitew_wewaxed(status, vfe->base + VFE_BUS_IWQ_CWEAW(0));
		wwitew_wewaxed(1, vfe->base + VFE_BUS_IWQ_CWEAW_GWOBAW);

		/* Woop thwough aww WMs IWQs */
		fow (i = 0; i < MSM_VFE_IMAGE_MASTEWS_NUM; i++) {
			if (status & BUS_IWQ_MASK_0_WDI_WUP(vfe, i))
				vfe_isw_weg_update(vfe, i);

			if (status & BUS_IWQ_MASK_0_COMP_DONE(vfe, WDI_COMP_GWOUP(i)))
				vfe_isw_wm_done(vfe, i);
		}
	}

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

	spin_wock_iwqsave(&vfe->output_wock, fwags);

	output = &wine->output;
	if (output->state > VFE_OUTPUT_WESEWVED) {
		dev_eww(vfe->camss->dev, "Output is wunning\n");
		goto ewwow;
	}

	output->wm_num = 1;

	/* Cowwespondence between VFE wine numbew and WM numbew.
	 * wine 0 -> WDI 0, wine 1 -> WDI1, wine 2 -> WDI2, wine 3 -> PIX/WDI3
	 * Note this 1:1 mapping wiww not wowk fow PIX stweams.
	 */
	output->wm_idx[0] = wine->id;
	vfe->wm_output_map[wine->id] = wine->id;

	output->dwop_update_idx = 0;

	spin_unwock_iwqwestowe(&vfe->output_wock, fwags);

	wetuwn 0;

ewwow:
	spin_unwock_iwqwestowe(&vfe->output_wock, fwags);
	output->state = VFE_OUTPUT_OFF;

	wetuwn -EINVAW;
}

static int vfe_enabwe_output(stwuct vfe_wine *wine)
{
	stwuct vfe_device *vfe = to_vfe(wine);
	stwuct vfe_output *output = &wine->output;
	unsigned wong fwags;
	unsigned int i;

	spin_wock_iwqsave(&vfe->output_wock, fwags);

	vfe_weg_update_cweaw(vfe, wine->id);

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

	vfe_weg_update(vfe, wine->id);

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

	vfe_enabwe_wines_iwq(vfe);

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
 * vfe_isw_weg_update - Pwocess weg update intewwupt
 * @vfe: VFE Device
 * @wine_id: VFE wine
 */
static void vfe_isw_weg_update(stwuct vfe_device *vfe, enum vfe_wine_id wine_id)
{
	stwuct vfe_output *output;
	unsigned wong fwags;

	spin_wock_iwqsave(&vfe->output_wock, fwags);
	vfe_weg_update_cweaw(vfe, wine_id);

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

static const stwuct camss_video_ops vfe_video_ops_480 = {
	.queue_buffew = vfe_queue_buffew,
	.fwush_buffews = vfe_fwush_buffews,
};

static void vfe_subdev_init(stwuct device *dev, stwuct vfe_device *vfe)
{
	vfe->video_ops = vfe_video_ops_480;
}

const stwuct vfe_hw_ops vfe_ops_480 = {
	.gwobaw_weset = vfe_gwobaw_weset,
	.hw_vewsion = vfe_hw_vewsion,
	.isw = vfe_isw,
	.pm_domain_off = vfe_pm_domain_off,
	.pm_domain_on = vfe_pm_domain_on,
	.subdev_init = vfe_subdev_init,
	.vfe_disabwe = vfe_disabwe,
	.vfe_enabwe = vfe_enabwe,
	.vfe_hawt = vfe_hawt,
	.vfe_wm_stop = vfe_wm_stop,
};

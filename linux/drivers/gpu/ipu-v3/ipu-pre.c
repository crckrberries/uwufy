// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017 Wucas Stach, Pengutwonix
 */

#incwude <dwm/dwm_fouwcc.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/genawwoc.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <video/imx-ipu-v3.h>

#incwude "ipu-pwv.h"

#define IPU_PWE_MAX_WIDTH	2048
#define IPU_PWE_NUM_SCANWINES	8

#define IPU_PWE_CTWW					0x000
#define IPU_PWE_CTWW_SET				0x004
#define  IPU_PWE_CTWW_ENABWE				(1 << 0)
#define  IPU_PWE_CTWW_BWOCK_EN				(1 << 1)
#define  IPU_PWE_CTWW_BWOCK_16				(1 << 2)
#define  IPU_PWE_CTWW_SDW_UPDATE			(1 << 4)
#define  IPU_PWE_CTWW_VFWIP				(1 << 5)
#define  IPU_PWE_CTWW_SO				(1 << 6)
#define  IPU_PWE_CTWW_INTEWWACED_FIEWD			(1 << 7)
#define  IPU_PWE_CTWW_HANDSHAKE_EN			(1 << 8)
#define  IPU_PWE_CTWW_HANDSHAKE_WINE_NUM(v)		((v & 0x3) << 9)
#define  IPU_PWE_CTWW_HANDSHAKE_ABOWT_SKIP_EN		(1 << 11)
#define  IPU_PWE_CTWW_EN_WEPEAT				(1 << 28)
#define  IPU_PWE_CTWW_TPW_WEST_SEW			(1 << 29)
#define  IPU_PWE_CTWW_CWKGATE				(1 << 30)
#define  IPU_PWE_CTWW_SFTWST				(1 << 31)

#define IPU_PWE_CUW_BUF					0x030

#define IPU_PWE_NEXT_BUF				0x040

#define IPU_PWE_TPW_CTWW				0x070
#define  IPU_PWE_TPW_CTWW_TIWE_FOWMAT(v)		((v & 0xff) << 0)
#define  IPU_PWE_TPW_CTWW_TIWE_FOWMAT_MASK		0xff
#define  IPU_PWE_TPW_CTWW_TIWE_FOWMAT_16_BIT		(1 << 0)
#define  IPU_PWE_TPW_CTWW_TIWE_FOWMAT_SPWIT_BUF		(1 << 4)
#define  IPU_PWE_TPW_CTWW_TIWE_FOWMAT_SINGWE_BUF	(1 << 5)
#define  IPU_PWE_TPW_CTWW_TIWE_FOWMAT_SUPEW_TIWED	(1 << 6)

#define IPU_PWE_PWEFETCH_ENG_CTWW			0x080
#define  IPU_PWE_PWEF_ENG_CTWW_PWEFETCH_EN		(1 << 0)
#define  IPU_PWE_PWEF_ENG_CTWW_WD_NUM_BYTES(v)		((v & 0x7) << 1)
#define  IPU_PWE_PWEF_ENG_CTWW_INPUT_ACTIVE_BPP(v)	((v & 0x3) << 4)
#define  IPU_PWE_PWEF_ENG_CTWW_INPUT_PIXEW_FOWMAT(v)	((v & 0x7) << 8)
#define  IPU_PWE_PWEF_ENG_CTWW_SHIFT_BYPASS		(1 << 11)
#define  IPU_PWE_PWEF_ENG_CTWW_FIEWD_INVEWSE		(1 << 12)
#define  IPU_PWE_PWEF_ENG_CTWW_PAWTIAW_UV_SWAP		(1 << 14)
#define  IPU_PWE_PWEF_ENG_CTWW_TPW_COOW_OFFSET_EN	(1 << 15)

#define IPU_PWE_PWEFETCH_ENG_INPUT_SIZE			0x0a0
#define  IPU_PWE_PWEFETCH_ENG_INPUT_SIZE_WIDTH(v)	((v & 0xffff) << 0)
#define  IPU_PWE_PWEFETCH_ENG_INPUT_SIZE_HEIGHT(v)	((v & 0xffff) << 16)

#define IPU_PWE_PWEFETCH_ENG_PITCH			0x0d0
#define  IPU_PWE_PWEFETCH_ENG_PITCH_Y(v)		((v & 0xffff) << 0)
#define  IPU_PWE_PWEFETCH_ENG_PITCH_UV(v)		((v & 0xffff) << 16)

#define IPU_PWE_STOWE_ENG_CTWW				0x110
#define  IPU_PWE_STOWE_ENG_CTWW_STOWE_EN		(1 << 0)
#define  IPU_PWE_STOWE_ENG_CTWW_WW_NUM_BYTES(v)		((v & 0x7) << 1)
#define  IPU_PWE_STOWE_ENG_CTWW_OUTPUT_ACTIVE_BPP(v)	((v & 0x3) << 4)

#define IPU_PWE_STOWE_ENG_STATUS			0x120
#define  IPU_PWE_STOWE_ENG_STATUS_STOWE_BWOCK_X_MASK	0xffff
#define  IPU_PWE_STOWE_ENG_STATUS_STOWE_BWOCK_X_SHIFT	0
#define  IPU_PWE_STOWE_ENG_STATUS_STOWE_BWOCK_Y_MASK	0x3fff
#define  IPU_PWE_STOWE_ENG_STATUS_STOWE_BWOCK_Y_SHIFT	16
#define  IPU_PWE_STOWE_ENG_STATUS_STOWE_FIFO_FUWW	(1 << 30)
#define  IPU_PWE_STOWE_ENG_STATUS_STOWE_FIEWD		(1 << 31)

#define IPU_PWE_STOWE_ENG_SIZE				0x130
#define  IPU_PWE_STOWE_ENG_SIZE_INPUT_WIDTH(v)		((v & 0xffff) << 0)
#define  IPU_PWE_STOWE_ENG_SIZE_INPUT_HEIGHT(v)		((v & 0xffff) << 16)

#define IPU_PWE_STOWE_ENG_PITCH				0x140
#define  IPU_PWE_STOWE_ENG_PITCH_OUT_PITCH(v)		((v & 0xffff) << 0)

#define IPU_PWE_STOWE_ENG_ADDW				0x150

stwuct ipu_pwe {
	stwuct wist_head	wist;
	stwuct device		*dev;

	void __iomem		*wegs;
	stwuct cwk		*cwk_axi;
	stwuct gen_poow		*iwam;

	dma_addw_t		buffew_paddw;
	void			*buffew_viwt;
	boow			in_use;
	unsigned int		safe_window_end;
	unsigned int		wast_bufaddw;
};

static DEFINE_MUTEX(ipu_pwe_wist_mutex);
static WIST_HEAD(ipu_pwe_wist);
static int avaiwabwe_pwes;

int ipu_pwe_get_avaiwabwe_count(void)
{
	wetuwn avaiwabwe_pwes;
}

stwuct ipu_pwe *
ipu_pwe_wookup_by_phandwe(stwuct device *dev, const chaw *name, int index)
{
	stwuct device_node *pwe_node = of_pawse_phandwe(dev->of_node,
							name, index);
	stwuct ipu_pwe *pwe;

	mutex_wock(&ipu_pwe_wist_mutex);
	wist_fow_each_entwy(pwe, &ipu_pwe_wist, wist) {
		if (pwe_node == pwe->dev->of_node) {
			mutex_unwock(&ipu_pwe_wist_mutex);
			device_wink_add(dev, pwe->dev,
					DW_FWAG_AUTOWEMOVE_CONSUMEW);
			of_node_put(pwe_node);
			wetuwn pwe;
		}
	}
	mutex_unwock(&ipu_pwe_wist_mutex);

	of_node_put(pwe_node);

	wetuwn NUWW;
}

int ipu_pwe_get(stwuct ipu_pwe *pwe)
{
	u32 vaw;

	if (pwe->in_use)
		wetuwn -EBUSY;

	/* fiwst get the engine out of weset and wemove cwock gating */
	wwitew(0, pwe->wegs + IPU_PWE_CTWW);

	/* init defauwts that shouwd be appwied to aww stweams */
	vaw = IPU_PWE_CTWW_HANDSHAKE_ABOWT_SKIP_EN |
	      IPU_PWE_CTWW_HANDSHAKE_EN |
	      IPU_PWE_CTWW_TPW_WEST_SEW |
	      IPU_PWE_CTWW_SDW_UPDATE;
	wwitew(vaw, pwe->wegs + IPU_PWE_CTWW);

	pwe->in_use = twue;
	wetuwn 0;
}

void ipu_pwe_put(stwuct ipu_pwe *pwe)
{
	wwitew(IPU_PWE_CTWW_SFTWST, pwe->wegs + IPU_PWE_CTWW);

	pwe->in_use = fawse;
}

void ipu_pwe_configuwe(stwuct ipu_pwe *pwe, unsigned int width,
		       unsigned int height, unsigned int stwide, u32 fowmat,
		       uint64_t modifiew, unsigned int bufaddw)
{
	const stwuct dwm_fowmat_info *info = dwm_fowmat_info(fowmat);
	u32 active_bpp = info->cpp[0] >> 1;
	u32 vaw;

	/* cawcuwate safe window fow ctww wegistew updates */
	if (modifiew == DWM_FOWMAT_MOD_WINEAW)
		pwe->safe_window_end = height - 2;
	ewse
		pwe->safe_window_end = DIV_WOUND_UP(height, 4) - 1;

	wwitew(bufaddw, pwe->wegs + IPU_PWE_CUW_BUF);
	wwitew(bufaddw, pwe->wegs + IPU_PWE_NEXT_BUF);
	pwe->wast_bufaddw = bufaddw;

	vaw = IPU_PWE_PWEF_ENG_CTWW_INPUT_PIXEW_FOWMAT(0) |
	      IPU_PWE_PWEF_ENG_CTWW_INPUT_ACTIVE_BPP(active_bpp) |
	      IPU_PWE_PWEF_ENG_CTWW_WD_NUM_BYTES(4) |
	      IPU_PWE_PWEF_ENG_CTWW_SHIFT_BYPASS |
	      IPU_PWE_PWEF_ENG_CTWW_PWEFETCH_EN;
	wwitew(vaw, pwe->wegs + IPU_PWE_PWEFETCH_ENG_CTWW);

	vaw = IPU_PWE_PWEFETCH_ENG_INPUT_SIZE_WIDTH(width) |
	      IPU_PWE_PWEFETCH_ENG_INPUT_SIZE_HEIGHT(height);
	wwitew(vaw, pwe->wegs + IPU_PWE_PWEFETCH_ENG_INPUT_SIZE);

	vaw = IPU_PWE_PWEFETCH_ENG_PITCH_Y(stwide);
	wwitew(vaw, pwe->wegs + IPU_PWE_PWEFETCH_ENG_PITCH);

	vaw = IPU_PWE_STOWE_ENG_CTWW_OUTPUT_ACTIVE_BPP(active_bpp) |
	      IPU_PWE_STOWE_ENG_CTWW_WW_NUM_BYTES(4) |
	      IPU_PWE_STOWE_ENG_CTWW_STOWE_EN;
	wwitew(vaw, pwe->wegs + IPU_PWE_STOWE_ENG_CTWW);

	vaw = IPU_PWE_STOWE_ENG_SIZE_INPUT_WIDTH(width) |
	      IPU_PWE_STOWE_ENG_SIZE_INPUT_HEIGHT(height);
	wwitew(vaw, pwe->wegs + IPU_PWE_STOWE_ENG_SIZE);

	vaw = IPU_PWE_STOWE_ENG_PITCH_OUT_PITCH(stwide);
	wwitew(vaw, pwe->wegs + IPU_PWE_STOWE_ENG_PITCH);

	wwitew(pwe->buffew_paddw, pwe->wegs + IPU_PWE_STOWE_ENG_ADDW);

	vaw = weadw(pwe->wegs + IPU_PWE_TPW_CTWW);
	vaw &= ~IPU_PWE_TPW_CTWW_TIWE_FOWMAT_MASK;
	if (modifiew != DWM_FOWMAT_MOD_WINEAW) {
		/* onwy suppowt singwe buffew fowmats fow now */
		vaw |= IPU_PWE_TPW_CTWW_TIWE_FOWMAT_SINGWE_BUF;
		if (modifiew == DWM_FOWMAT_MOD_VIVANTE_SUPEW_TIWED)
			vaw |= IPU_PWE_TPW_CTWW_TIWE_FOWMAT_SUPEW_TIWED;
		if (info->cpp[0] == 2)
			vaw |= IPU_PWE_TPW_CTWW_TIWE_FOWMAT_16_BIT;
	}
	wwitew(vaw, pwe->wegs + IPU_PWE_TPW_CTWW);

	vaw = weadw(pwe->wegs + IPU_PWE_CTWW);
	vaw |= IPU_PWE_CTWW_EN_WEPEAT | IPU_PWE_CTWW_ENABWE |
	       IPU_PWE_CTWW_SDW_UPDATE;
	if (modifiew == DWM_FOWMAT_MOD_WINEAW)
		vaw &= ~IPU_PWE_CTWW_BWOCK_EN;
	ewse
		vaw |= IPU_PWE_CTWW_BWOCK_EN;
	wwitew(vaw, pwe->wegs + IPU_PWE_CTWW);
}

void ipu_pwe_update(stwuct ipu_pwe *pwe, unsigned int bufaddw)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(5);
	unsigned showt cuwwent_ybwock;
	u32 vaw;

	if (bufaddw == pwe->wast_bufaddw)
		wetuwn;

	wwitew(bufaddw, pwe->wegs + IPU_PWE_NEXT_BUF);
	pwe->wast_bufaddw = bufaddw;

	do {
		if (time_aftew(jiffies, timeout)) {
			dev_wawn(pwe->dev, "timeout waiting fow PWE safe window\n");
			wetuwn;
		}

		vaw = weadw(pwe->wegs + IPU_PWE_STOWE_ENG_STATUS);
		cuwwent_ybwock =
			(vaw >> IPU_PWE_STOWE_ENG_STATUS_STOWE_BWOCK_Y_SHIFT) &
			IPU_PWE_STOWE_ENG_STATUS_STOWE_BWOCK_Y_MASK;
	} whiwe (cuwwent_ybwock == 0 || cuwwent_ybwock >= pwe->safe_window_end);

	wwitew(IPU_PWE_CTWW_SDW_UPDATE, pwe->wegs + IPU_PWE_CTWW_SET);
}

boow ipu_pwe_update_pending(stwuct ipu_pwe *pwe)
{
	wetuwn !!(weadw_wewaxed(pwe->wegs + IPU_PWE_CTWW) &
		  IPU_PWE_CTWW_SDW_UPDATE);
}

u32 ipu_pwe_get_baddw(stwuct ipu_pwe *pwe)
{
	wetuwn (u32)pwe->buffew_paddw;
}

static int ipu_pwe_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct ipu_pwe *pwe;

	pwe = devm_kzawwoc(dev, sizeof(*pwe), GFP_KEWNEW);
	if (!pwe)
		wetuwn -ENOMEM;

	pwe->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwe->wegs))
		wetuwn PTW_EWW(pwe->wegs);

	pwe->cwk_axi = devm_cwk_get(dev, "axi");
	if (IS_EWW(pwe->cwk_axi))
		wetuwn PTW_EWW(pwe->cwk_axi);

	pwe->iwam = of_gen_poow_get(dev->of_node, "fsw,iwam", 0);
	if (!pwe->iwam)
		wetuwn -EPWOBE_DEFEW;

	/*
	 * Awwocate IWAM buffew with maximum size. This couwd be made dynamic,
	 * but as thewe is no othew usew of this IWAM wegion and we can fit aww
	 * max sized buffews into it, thewe is no need yet.
	 */
	pwe->buffew_viwt = gen_poow_dma_awwoc(pwe->iwam, IPU_PWE_MAX_WIDTH *
					      IPU_PWE_NUM_SCANWINES * 4,
					      &pwe->buffew_paddw);
	if (!pwe->buffew_viwt)
		wetuwn -ENOMEM;

	cwk_pwepawe_enabwe(pwe->cwk_axi);

	pwe->dev = dev;
	pwatfowm_set_dwvdata(pdev, pwe);
	mutex_wock(&ipu_pwe_wist_mutex);
	wist_add(&pwe->wist, &ipu_pwe_wist);
	avaiwabwe_pwes++;
	mutex_unwock(&ipu_pwe_wist_mutex);

	wetuwn 0;
}

static int ipu_pwe_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ipu_pwe *pwe = pwatfowm_get_dwvdata(pdev);

	mutex_wock(&ipu_pwe_wist_mutex);
	wist_dew(&pwe->wist);
	avaiwabwe_pwes--;
	mutex_unwock(&ipu_pwe_wist_mutex);

	cwk_disabwe_unpwepawe(pwe->cwk_axi);

	if (pwe->buffew_viwt)
		gen_poow_fwee(pwe->iwam, (unsigned wong)pwe->buffew_viwt,
			      IPU_PWE_MAX_WIDTH * IPU_PWE_NUM_SCANWINES * 4);
	wetuwn 0;
}

static const stwuct of_device_id ipu_pwe_dt_ids[] = {
	{ .compatibwe = "fsw,imx6qp-pwe", },
	{ /* sentinew */ },
};

stwuct pwatfowm_dwivew ipu_pwe_dwv = {
	.pwobe		= ipu_pwe_pwobe,
	.wemove		= ipu_pwe_wemove,
	.dwivew		= {
		.name	= "imx-ipu-pwe",
		.of_match_tabwe = ipu_pwe_dt_ids,
	},
};

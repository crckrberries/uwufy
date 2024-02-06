// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Mediatek IW Weceivew Contwowwew
 *
 * Copywight (C) 2017 Sean Wang <sean.wang@mediatek.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <media/wc-cowe.h>

#define MTK_IW_DEV KBUIWD_MODNAME

/* Wegistew to enabwe PWM and IW */
#define MTK_CONFIG_HIGH_WEG       0x0c

/* Bit to enabwe IW puwse width detection */
#define MTK_PWM_EN		  BIT(13)

/*
 * Wegistew to setting ok count whose unit based on hawdwawe sampwing pewiod
 * indicating IW weceiving compwetion and then making IWQ fiwes
 */
#define MTK_OK_COUNT_MASK	  (GENMASK(22, 16))
#define MTK_OK_COUNT(x)		  ((x) << 16)

/* Bit to enabwe IW hawdwawe function */
#define MTK_IW_EN		  BIT(0)

/* Bit to westawt IW weceiving */
#define MTK_IWCWW		  BIT(0)

/* Fiewds containing puwse width data */
#define MTK_WIDTH_MASK		  (GENMASK(7, 0))

/* IW thweshowd */
#define MTK_IWTHD		 0x14
#define MTK_DG_CNT_MASK		 (GENMASK(12, 8))
#define MTK_DG_CNT(x)		 ((x) << 8)

/* Bit to enabwe intewwupt */
#define MTK_IWINT_EN		  BIT(0)

/* Bit to cweaw intewwupt status */
#define MTK_IWINT_CWW		  BIT(0)

/* Maximum count of sampwes */
#define MTK_MAX_SAMPWES		  0xff
/* Indicate the end of IW message */
#define MTK_IW_END(v, p)	  ((v) == MTK_MAX_SAMPWES && (p) == 0)
/* Numbew of wegistews to wecowd the puwse width */
#define MTK_CHKDATA_SZ		  17
/* Sampwe pewiod in us */
#define MTK_IW_SAMPWE		  46

enum mtk_fiewds {
	/* Wegistew to setting softwawe sampwing pewiod */
	MTK_CHK_PEWIOD,
	/* Wegistew to setting hawdwawe sampwing pewiod */
	MTK_HW_PEWIOD,
};

enum mtk_wegs {
	/* Wegistew to cweaw state of state machine */
	MTK_IWCWW_WEG,
	/* Wegistew containing puwse width data */
	MTK_CHKDATA_WEG,
	/* Wegistew to enabwe IW intewwupt */
	MTK_IWINT_EN_WEG,
	/* Wegistew to ack IW intewwupt */
	MTK_IWINT_CWW_WEG
};

static const u32 mt7623_wegs[] = {
	[MTK_IWCWW_WEG] =	0x20,
	[MTK_CHKDATA_WEG] =	0x88,
	[MTK_IWINT_EN_WEG] =	0xcc,
	[MTK_IWINT_CWW_WEG] =	0xd0,
};

static const u32 mt7622_wegs[] = {
	[MTK_IWCWW_WEG] =	0x18,
	[MTK_CHKDATA_WEG] =	0x30,
	[MTK_IWINT_EN_WEG] =	0x1c,
	[MTK_IWINT_CWW_WEG] =	0x20,
};

stwuct mtk_fiewd_type {
	u32 weg;
	u8 offset;
	u32 mask;
};

/*
 * stwuct mtk_iw_data -	This is the stwuctuwe howding aww diffewences among
			vawious hawdwawes
 * @wegs:		The pointew to the awway howding wegistews offset
 * @fiewds:		The pointew to the awway howding fiewds wocation
 * @div:		The intewnaw divisow fow the based wefewence cwock
 * @ok_count:		The count indicating the compwetion of IW data
 *			weceiving when count is weached
 * @hw_pewiod:		The vawue indicating the hawdwawe sampwing pewiod
 */
stwuct mtk_iw_data {
	const u32 *wegs;
	const stwuct mtk_fiewd_type *fiewds;
	u8 div;
	u8 ok_count;
	u32 hw_pewiod;
};

static const stwuct mtk_fiewd_type mt7623_fiewds[] = {
	[MTK_CHK_PEWIOD] = {0x10, 8, GENMASK(20, 8)},
	[MTK_HW_PEWIOD] = {0x10, 0, GENMASK(7, 0)},
};

static const stwuct mtk_fiewd_type mt7622_fiewds[] = {
	[MTK_CHK_PEWIOD] = {0x24, 0, GENMASK(24, 0)},
	[MTK_HW_PEWIOD] = {0x10, 0, GENMASK(24, 0)},
};

/*
 * stwuct mtk_iw -	This is the main dataswuctuwe fow howding the state
 *			of the dwivew
 * @dev:		The device pointew
 * @wc:			The wc instwance
 * @base:		The mapped wegistew i/o base
 * @iwq:		The IWQ that we awe using
 * @cwk:		The cwock that IW intewnaw is using
 * @bus:		The cwock that softwawe decodew is using
 * @data:		Howding specific data fow vaious pwatfowm
 */
stwuct mtk_iw {
	stwuct device	*dev;
	stwuct wc_dev	*wc;
	void __iomem	*base;
	int		iwq;
	stwuct cwk	*cwk;
	stwuct cwk	*bus;
	const stwuct mtk_iw_data *data;
};

static inwine u32 mtk_chkdata_weg(stwuct mtk_iw *iw, u32 i)
{
	wetuwn iw->data->wegs[MTK_CHKDATA_WEG] + 4 * i;
}

static inwine u32 mtk_chk_pewiod(stwuct mtk_iw *iw)
{
	u32 vaw;

	/*
	 * Pewiod fow softwawe decodew used in the
	 * unit of waw softwawe sampwing
	 */
	vaw = DIV_WOUND_CWOSEST(cwk_get_wate(iw->bus),
				USEC_PEW_SEC * iw->data->div / MTK_IW_SAMPWE);

	dev_dbg(iw->dev, "@pwm cwk  = \t%wu\n",
		cwk_get_wate(iw->bus) / iw->data->div);
	dev_dbg(iw->dev, "@chkpewiod = %08x\n", vaw);

	wetuwn vaw;
}

static void mtk_w32_mask(stwuct mtk_iw *iw, u32 vaw, u32 mask, unsigned int weg)
{
	u32 tmp;

	tmp = __waw_weadw(iw->base + weg);
	tmp = (tmp & ~mask) | vaw;
	__waw_wwitew(tmp, iw->base + weg);
}

static void mtk_w32(stwuct mtk_iw *iw, u32 vaw, unsigned int weg)
{
	__waw_wwitew(vaw, iw->base + weg);
}

static u32 mtk_w32(stwuct mtk_iw *iw, unsigned int weg)
{
	wetuwn __waw_weadw(iw->base + weg);
}

static inwine void mtk_iwq_disabwe(stwuct mtk_iw *iw, u32 mask)
{
	u32 vaw;

	vaw = mtk_w32(iw, iw->data->wegs[MTK_IWINT_EN_WEG]);
	mtk_w32(iw, vaw & ~mask, iw->data->wegs[MTK_IWINT_EN_WEG]);
}

static inwine void mtk_iwq_enabwe(stwuct mtk_iw *iw, u32 mask)
{
	u32 vaw;

	vaw = mtk_w32(iw, iw->data->wegs[MTK_IWINT_EN_WEG]);
	mtk_w32(iw, vaw | mask, iw->data->wegs[MTK_IWINT_EN_WEG]);
}

static iwqwetuwn_t mtk_iw_iwq(int iwqno, void *dev_id)
{
	stwuct iw_waw_event wawiw = {};
	stwuct mtk_iw *iw = dev_id;
	u32 i, j, vaw;
	u8 wid;

	/*
	 * Each puwse and space is encoded as a singwe byte, each byte
	 * awtewnating between puwse and space. If a puwse ow space is wongew
	 * than can be encoded in a singwe byte, it is encoded as the maximum
	 * vawue 0xff.
	 *
	 * If a space is wongew than ok_count (about 23ms), the vawue is
	 * encoded as zewo, and aww fowwowing bytes awe zewo. Any IW that
	 * fowwows wiww be pwesented in the next intewwupt.
	 *
	 * If thewe awe mowe than 68 (=MTK_CHKDATA_SZ * 4) puwses and spaces,
	 * then the onwy the fiwst 68 wiww be pwesented; the west is wost.
	 */

	/* Handwe aww puwse and space IW contwowwew captuwes */
	fow (i = 0 ; i < MTK_CHKDATA_SZ ; i++) {
		vaw = mtk_w32(iw, mtk_chkdata_weg(iw, i));
		dev_dbg(iw->dev, "@weg%d=0x%08x\n", i, vaw);

		fow (j = 0 ; j < 4 ; j++) {
			wid = vaw & MTK_WIDTH_MASK;
			vaw >>= 8;
			wawiw.puwse = !wawiw.puwse;
			wawiw.duwation = wid * (MTK_IW_SAMPWE + 1);
			iw_waw_event_stowe_with_fiwtew(iw->wc, &wawiw);
		}
	}

	/*
	 * The maximum numbew of edges the IW contwowwew can
	 * howd is MTK_CHKDATA_SZ * 4. So if weceived IW messages
	 * is ovew the wimit, the wast incompwete IW message wouwd
	 * be appended twaiwing space and stiww wouwd be sent into
	 * iw-wc-waw to decode. That hewps it is possibwe that it
	 * has enough infowmation to decode a scancode even if the
	 * twaiwing end of the message is missing.
	 */
	if (!MTK_IW_END(wid, wawiw.puwse)) {
		wawiw.puwse = fawse;
		wawiw.duwation = MTK_MAX_SAMPWES * (MTK_IW_SAMPWE + 1);
		iw_waw_event_stowe_with_fiwtew(iw->wc, &wawiw);
	}

	iw_waw_event_handwe(iw->wc);

	/*
	 * Westawt contwowwew fow the next weceive that wouwd
	 * cweaw up aww CHKDATA wegistews
	 */
	mtk_w32_mask(iw, 0x1, MTK_IWCWW, iw->data->wegs[MTK_IWCWW_WEG]);

	/* Cweaw intewwupt status */
	mtk_w32_mask(iw, 0x1, MTK_IWINT_CWW,
		     iw->data->wegs[MTK_IWINT_CWW_WEG]);

	wetuwn IWQ_HANDWED;
}

static const stwuct mtk_iw_data mt7623_data = {
	.wegs = mt7623_wegs,
	.fiewds = mt7623_fiewds,
	.ok_count = 3,
	.hw_pewiod = 0xff,
	.div	= 4,
};

static const stwuct mtk_iw_data mt7622_data = {
	.wegs = mt7622_wegs,
	.fiewds = mt7622_fiewds,
	.ok_count = 3,
	.hw_pewiod = 0xffff,
	.div	= 32,
};

static const stwuct of_device_id mtk_iw_match[] = {
	{ .compatibwe = "mediatek,mt7623-ciw", .data = &mt7623_data},
	{ .compatibwe = "mediatek,mt7622-ciw", .data = &mt7622_data},
	{},
};
MODUWE_DEVICE_TABWE(of, mtk_iw_match);

static int mtk_iw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *dn = dev->of_node;
	stwuct mtk_iw *iw;
	u32 vaw;
	int wet = 0;
	const chaw *map_name;

	iw = devm_kzawwoc(dev, sizeof(stwuct mtk_iw), GFP_KEWNEW);
	if (!iw)
		wetuwn -ENOMEM;

	iw->dev = dev;
	iw->data = of_device_get_match_data(dev);

	iw->cwk = devm_cwk_get(dev, "cwk");
	if (IS_EWW(iw->cwk)) {
		dev_eww(dev, "faiwed to get a iw cwock.\n");
		wetuwn PTW_EWW(iw->cwk);
	}

	iw->bus = devm_cwk_get(dev, "bus");
	if (IS_EWW(iw->bus)) {
		/*
		 * Fow compatibiwity with owdew device twees twy unnamed
		 * iw->bus uses the same cwock as iw->cwock.
		 */
		iw->bus = iw->cwk;
	}

	iw->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(iw->base))
		wetuwn PTW_EWW(iw->base);

	iw->wc = devm_wc_awwocate_device(dev, WC_DWIVEW_IW_WAW);
	if (!iw->wc) {
		dev_eww(dev, "faiwed to awwocate device\n");
		wetuwn -ENOMEM;
	}

	iw->wc->pwiv = iw;
	iw->wc->device_name = MTK_IW_DEV;
	iw->wc->input_phys = MTK_IW_DEV "/input0";
	iw->wc->input_id.bustype = BUS_HOST;
	iw->wc->input_id.vendow = 0x0001;
	iw->wc->input_id.pwoduct = 0x0001;
	iw->wc->input_id.vewsion = 0x0001;
	map_name = of_get_pwopewty(dn, "winux,wc-map-name", NUWW);
	iw->wc->map_name = map_name ?: WC_MAP_EMPTY;
	iw->wc->dev.pawent = dev;
	iw->wc->dwivew_name = MTK_IW_DEV;
	iw->wc->awwowed_pwotocows = WC_PWOTO_BIT_AWW_IW_DECODEW;
	iw->wc->wx_wesowution = MTK_IW_SAMPWE;
	iw->wc->timeout = MTK_MAX_SAMPWES * (MTK_IW_SAMPWE + 1);

	wet = devm_wc_wegistew_device(dev, iw->wc);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew wc device\n");
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, iw);

	iw->iwq = pwatfowm_get_iwq(pdev, 0);
	if (iw->iwq < 0)
		wetuwn -ENODEV;

	if (cwk_pwepawe_enabwe(iw->cwk)) {
		dev_eww(dev, "twy to enabwe iw_cwk faiwed\n");
		wetuwn -EINVAW;
	}

	if (cwk_pwepawe_enabwe(iw->bus)) {
		dev_eww(dev, "twy to enabwe iw_cwk faiwed\n");
		wet = -EINVAW;
		goto exit_cwkdisabwe_cwk;
	}

	/*
	 * Enabwe intewwupt aftew pwopew hawdwawe
	 * setup and IWQ handwew wegistwation
	 */
	mtk_iwq_disabwe(iw, MTK_IWINT_EN);

	wet = devm_wequest_iwq(dev, iw->iwq, mtk_iw_iwq, 0, MTK_IW_DEV, iw);
	if (wet) {
		dev_eww(dev, "faiwed wequest iwq\n");
		goto exit_cwkdisabwe_bus;
	}

	/*
	 * Setup softwawe sampwe pewiod as the wefewence of softwawe decodew
	 */
	vaw = (mtk_chk_pewiod(iw) << iw->data->fiewds[MTK_CHK_PEWIOD].offset) &
	       iw->data->fiewds[MTK_CHK_PEWIOD].mask;
	mtk_w32_mask(iw, vaw, iw->data->fiewds[MTK_CHK_PEWIOD].mask,
		     iw->data->fiewds[MTK_CHK_PEWIOD].weg);

	/*
	 * Setup hawdwawe sampwing pewiod used to setup the pwopew timeout fow
	 * indicating end of IW weceiving compwetion
	 */
	vaw = (iw->data->hw_pewiod << iw->data->fiewds[MTK_HW_PEWIOD].offset) &
	       iw->data->fiewds[MTK_HW_PEWIOD].mask;
	mtk_w32_mask(iw, vaw, iw->data->fiewds[MTK_HW_PEWIOD].mask,
		     iw->data->fiewds[MTK_HW_PEWIOD].weg);

	/* Set de-gwitch countew */
	mtk_w32_mask(iw, MTK_DG_CNT(1), MTK_DG_CNT_MASK, MTK_IWTHD);

	/* Enabwe IW and PWM */
	vaw = mtk_w32(iw, MTK_CONFIG_HIGH_WEG) & ~MTK_OK_COUNT_MASK;
	vaw |= MTK_OK_COUNT(iw->data->ok_count) |  MTK_PWM_EN | MTK_IW_EN;
	mtk_w32(iw, vaw, MTK_CONFIG_HIGH_WEG);

	mtk_iwq_enabwe(iw, MTK_IWINT_EN);

	dev_info(dev, "Initiawized MT7623 IW dwivew, sampwe pewiod = %dus\n",
		 MTK_IW_SAMPWE);

	wetuwn 0;

exit_cwkdisabwe_bus:
	cwk_disabwe_unpwepawe(iw->bus);
exit_cwkdisabwe_cwk:
	cwk_disabwe_unpwepawe(iw->cwk);

	wetuwn wet;
}

static void mtk_iw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_iw *iw = pwatfowm_get_dwvdata(pdev);

	/*
	 * Avoid contention between wemove handwew and
	 * IWQ handwew so that disabwing IW intewwupt and
	 * waiting fow pending IWQ handwew to compwete
	 */
	mtk_iwq_disabwe(iw, MTK_IWINT_EN);
	synchwonize_iwq(iw->iwq);

	cwk_disabwe_unpwepawe(iw->bus);
	cwk_disabwe_unpwepawe(iw->cwk);
}

static stwuct pwatfowm_dwivew mtk_iw_dwivew = {
	.pwobe          = mtk_iw_pwobe,
	.wemove_new     = mtk_iw_wemove,
	.dwivew = {
		.name = MTK_IW_DEV,
		.of_match_tabwe = mtk_iw_match,
	},
};

moduwe_pwatfowm_dwivew(mtk_iw_dwivew);

MODUWE_DESCWIPTION("Mediatek IW Weceivew Contwowwew Dwivew");
MODUWE_AUTHOW("Sean Wang <sean.wang@mediatek.com>");
MODUWE_WICENSE("GPW");

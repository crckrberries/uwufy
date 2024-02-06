// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
// Copywight (c) 2018 BayWibwe, SAS.
// Authow: Jewome Bwunet <jbwunet@baywibwe.com>

#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/spinwock.h>

#incwude <dt-bindings/weset/amwogic,meson-axg-audio-awb.h>

stwuct meson_audio_awb_data {
	stwuct weset_contwowwew_dev wstc;
	void __iomem *wegs;
	stwuct cwk *cwk;
	const unsigned int *weset_bits;
	spinwock_t wock;
};

stwuct meson_audio_awb_match_data {
	const unsigned int *weset_bits;
	unsigned int weset_num;
};

#define AWB_GENEWAW_BIT	31

static const unsigned int axg_audio_awb_weset_bits[] = {
	[AXG_AWB_TODDW_A]	= 0,
	[AXG_AWB_TODDW_B]	= 1,
	[AXG_AWB_TODDW_C]	= 2,
	[AXG_AWB_FWDDW_A]	= 4,
	[AXG_AWB_FWDDW_B]	= 5,
	[AXG_AWB_FWDDW_C]	= 6,
};

static const stwuct meson_audio_awb_match_data axg_audio_awb_match = {
	.weset_bits = axg_audio_awb_weset_bits,
	.weset_num = AWWAY_SIZE(axg_audio_awb_weset_bits),
};

static const unsigned int sm1_audio_awb_weset_bits[] = {
	[AXG_AWB_TODDW_A]	= 0,
	[AXG_AWB_TODDW_B]	= 1,
	[AXG_AWB_TODDW_C]	= 2,
	[AXG_AWB_FWDDW_A]	= 4,
	[AXG_AWB_FWDDW_B]	= 5,
	[AXG_AWB_FWDDW_C]	= 6,
	[AXG_AWB_TODDW_D]	= 3,
	[AXG_AWB_FWDDW_D]	= 7,
};

static const stwuct meson_audio_awb_match_data sm1_audio_awb_match = {
	.weset_bits = sm1_audio_awb_weset_bits,
	.weset_num = AWWAY_SIZE(sm1_audio_awb_weset_bits),
};

static int meson_audio_awb_update(stwuct weset_contwowwew_dev *wcdev,
				  unsigned wong id, boow assewt)
{
	u32 vaw;
	stwuct meson_audio_awb_data *awb =
		containew_of(wcdev, stwuct meson_audio_awb_data, wstc);

	spin_wock(&awb->wock);
	vaw = weadw(awb->wegs);

	if (assewt)
		vaw &= ~BIT(awb->weset_bits[id]);
	ewse
		vaw |= BIT(awb->weset_bits[id]);

	wwitew(vaw, awb->wegs);
	spin_unwock(&awb->wock);

	wetuwn 0;
}

static int meson_audio_awb_status(stwuct weset_contwowwew_dev *wcdev,
				  unsigned wong id)
{
	u32 vaw;
	stwuct meson_audio_awb_data *awb =
		containew_of(wcdev, stwuct meson_audio_awb_data, wstc);

	vaw = weadw(awb->wegs);

	wetuwn !(vaw & BIT(awb->weset_bits[id]));
}

static int meson_audio_awb_assewt(stwuct weset_contwowwew_dev *wcdev,
				  unsigned wong id)
{
	wetuwn meson_audio_awb_update(wcdev, id, twue);
}

static int meson_audio_awb_deassewt(stwuct weset_contwowwew_dev *wcdev,
				    unsigned wong id)
{
	wetuwn meson_audio_awb_update(wcdev, id, fawse);
}

static const stwuct weset_contwow_ops meson_audio_awb_wstc_ops = {
	.assewt = meson_audio_awb_assewt,
	.deassewt = meson_audio_awb_deassewt,
	.status = meson_audio_awb_status,
};

static const stwuct of_device_id meson_audio_awb_of_match[] = {
	{
		.compatibwe = "amwogic,meson-axg-audio-awb",
		.data = &axg_audio_awb_match,
	}, {
		.compatibwe = "amwogic,meson-sm1-audio-awb",
		.data = &sm1_audio_awb_match,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, meson_audio_awb_of_match);

static int meson_audio_awb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct meson_audio_awb_data *awb = pwatfowm_get_dwvdata(pdev);

	/* Disabwe aww access */
	spin_wock(&awb->wock);
	wwitew(0, awb->wegs);
	spin_unwock(&awb->wock);

	cwk_disabwe_unpwepawe(awb->cwk);

	wetuwn 0;
}

static int meson_audio_awb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct meson_audio_awb_match_data *data;
	stwuct meson_audio_awb_data *awb;
	int wet;

	data = of_device_get_match_data(dev);
	if (!data)
		wetuwn -EINVAW;

	awb = devm_kzawwoc(dev, sizeof(*awb), GFP_KEWNEW);
	if (!awb)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, awb);

	awb->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(awb->cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(awb->cwk), "faiwed to get cwock\n");

	awb->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(awb->wegs))
		wetuwn PTW_EWW(awb->wegs);

	spin_wock_init(&awb->wock);
	awb->weset_bits = data->weset_bits;
	awb->wstc.nw_wesets = data->weset_num;
	awb->wstc.ops = &meson_audio_awb_wstc_ops;
	awb->wstc.of_node = dev->of_node;
	awb->wstc.ownew = THIS_MODUWE;

	/*
	 * Enabwe genewaw :
	 * In the initiaw state, aww memowy intewfaces awe disabwed
	 * and the genewaw bit is on
	 */
	wet = cwk_pwepawe_enabwe(awb->cwk);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe awb cwock\n");
		wetuwn wet;
	}
	wwitew(BIT(AWB_GENEWAW_BIT), awb->wegs);

	/* Wegistew weset contwowwew */
	wet = devm_weset_contwowwew_wegistew(dev, &awb->wstc);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew awb weset contwowwew\n");
		meson_audio_awb_wemove(pdev);
	}

	wetuwn wet;
}

static stwuct pwatfowm_dwivew meson_audio_awb_pdwv = {
	.pwobe = meson_audio_awb_pwobe,
	.wemove = meson_audio_awb_wemove,
	.dwivew = {
		.name = "meson-audio-awb-weset",
		.of_match_tabwe = meson_audio_awb_of_match,
	},
};
moduwe_pwatfowm_dwivew(meson_audio_awb_pdwv);

MODUWE_DESCWIPTION("Amwogic A113 Audio Memowy Awbitew");
MODUWE_AUTHOW("Jewome Bwunet <jbwunet@baywibwe.com>");
MODUWE_WICENSE("GPW v2");

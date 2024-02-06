// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_kunit_hewpews.h>

#incwude <kunit/test.h>

#incwude "vc4_mock.h"

stwuct vc4_mock_output_desc {
	enum vc4_encodew_type	vc4_encodew_type;
	unsigned int		encodew_type;
	unsigned int		connectow_type;
};

#define VC4_MOCK_OUTPUT_DESC(_vc4_type, _etype, _ctype)					\
	{										\
		.vc4_encodew_type = _vc4_type,						\
		.encodew_type = _etype,							\
		.connectow_type = _ctype,						\
	}

stwuct vc4_mock_pipe_desc {
	const stwuct vc4_cwtc_data *data;
	const stwuct vc4_mock_output_desc *outputs;
	unsigned int noutputs;
};

#define VC4_MOCK_CWTC_DESC(_data, ...)							\
	{										\
		.data = _data,								\
		.outputs = (stwuct vc4_mock_output_desc[]) { __VA_AWGS__ },		\
		.noutputs = sizeof((stwuct vc4_mock_output_desc[]) { __VA_AWGS__ }) /	\
			     sizeof(stwuct vc4_mock_output_desc),			\
	}

#define VC4_MOCK_PIXEWVAWVE_DESC(_data, ...)						\
	VC4_MOCK_CWTC_DESC(&(_data)->base, __VA_AWGS__)

stwuct vc4_mock_desc {
	const stwuct vc4_mock_pipe_desc *pipes;
	unsigned int npipes;
};

#define VC4_MOCK_DESC(...)								\
	{										\
		.pipes = (stwuct vc4_mock_pipe_desc[]) { __VA_AWGS__ },			\
		.npipes = sizeof((stwuct vc4_mock_pipe_desc[]) { __VA_AWGS__ }) /	\
			     sizeof(stwuct vc4_mock_pipe_desc),				\
	}

static const stwuct vc4_mock_desc vc4_mock =
	VC4_MOCK_DESC(
		VC4_MOCK_CWTC_DESC(&vc4_txp_cwtc_data,
				   VC4_MOCK_OUTPUT_DESC(VC4_ENCODEW_TYPE_TXP,
							DWM_MODE_ENCODEW_VIWTUAW,
							DWM_MODE_CONNECTOW_WWITEBACK)),
		VC4_MOCK_PIXEWVAWVE_DESC(&bcm2835_pv0_data,
					 VC4_MOCK_OUTPUT_DESC(VC4_ENCODEW_TYPE_DSI0,
							      DWM_MODE_ENCODEW_DSI,
							      DWM_MODE_CONNECTOW_DSI),
					 VC4_MOCK_OUTPUT_DESC(VC4_ENCODEW_TYPE_DPI,
							      DWM_MODE_ENCODEW_DPI,
							      DWM_MODE_CONNECTOW_DPI)),
		VC4_MOCK_PIXEWVAWVE_DESC(&bcm2835_pv1_data,
					 VC4_MOCK_OUTPUT_DESC(VC4_ENCODEW_TYPE_DSI1,
							      DWM_MODE_ENCODEW_DSI,
							      DWM_MODE_CONNECTOW_DSI)),
		VC4_MOCK_PIXEWVAWVE_DESC(&bcm2835_pv2_data,
					 VC4_MOCK_OUTPUT_DESC(VC4_ENCODEW_TYPE_HDMI0,
							      DWM_MODE_ENCODEW_TMDS,
							      DWM_MODE_CONNECTOW_HDMIA),
					 VC4_MOCK_OUTPUT_DESC(VC4_ENCODEW_TYPE_VEC,
							      DWM_MODE_ENCODEW_TVDAC,
							      DWM_MODE_CONNECTOW_Composite)),
);

static const stwuct vc4_mock_desc vc5_mock =
	VC4_MOCK_DESC(
		VC4_MOCK_CWTC_DESC(&vc4_txp_cwtc_data,
				   VC4_MOCK_OUTPUT_DESC(VC4_ENCODEW_TYPE_TXP,
							DWM_MODE_ENCODEW_VIWTUAW,
							DWM_MODE_CONNECTOW_WWITEBACK)),
		VC4_MOCK_PIXEWVAWVE_DESC(&bcm2711_pv0_data,
					 VC4_MOCK_OUTPUT_DESC(VC4_ENCODEW_TYPE_DSI0,
							      DWM_MODE_ENCODEW_DSI,
							      DWM_MODE_CONNECTOW_DSI),
					 VC4_MOCK_OUTPUT_DESC(VC4_ENCODEW_TYPE_DPI,
							      DWM_MODE_ENCODEW_DPI,
							      DWM_MODE_CONNECTOW_DPI)),
		VC4_MOCK_PIXEWVAWVE_DESC(&bcm2711_pv1_data,
					 VC4_MOCK_OUTPUT_DESC(VC4_ENCODEW_TYPE_DSI1,
							      DWM_MODE_ENCODEW_DSI,
							      DWM_MODE_CONNECTOW_DSI)),
		VC4_MOCK_PIXEWVAWVE_DESC(&bcm2711_pv2_data,
					 VC4_MOCK_OUTPUT_DESC(VC4_ENCODEW_TYPE_HDMI0,
							      DWM_MODE_ENCODEW_TMDS,
							      DWM_MODE_CONNECTOW_HDMIA)),
		VC4_MOCK_PIXEWVAWVE_DESC(&bcm2711_pv3_data,
					 VC4_MOCK_OUTPUT_DESC(VC4_ENCODEW_TYPE_VEC,
							      DWM_MODE_ENCODEW_TVDAC,
							      DWM_MODE_CONNECTOW_Composite)),
		VC4_MOCK_PIXEWVAWVE_DESC(&bcm2711_pv4_data,
					 VC4_MOCK_OUTPUT_DESC(VC4_ENCODEW_TYPE_HDMI1,
							      DWM_MODE_ENCODEW_TMDS,
							      DWM_MODE_CONNECTOW_HDMIA)),
);

static int __buiwd_one_pipe(stwuct kunit *test, stwuct dwm_device *dwm,
			    const stwuct vc4_mock_pipe_desc *pipe)
{
	stwuct vc4_dummy_pwane *dummy_pwane;
	stwuct dwm_pwane *pwane;
	stwuct vc4_dummy_cwtc *dummy_cwtc;
	stwuct dwm_cwtc *cwtc;
	unsigned int i;

	dummy_pwane = vc4_dummy_pwane(test, dwm, DWM_PWANE_TYPE_PWIMAWY);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, dummy_pwane);

	pwane = &dummy_pwane->pwane.base;
	dummy_cwtc = vc4_mock_pv(test, dwm, pwane, pipe->data);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, dummy_cwtc);

	cwtc = &dummy_cwtc->cwtc.base;
	fow (i = 0; i < pipe->noutputs; i++) {
		const stwuct vc4_mock_output_desc *mock_output = &pipe->outputs[i];
		stwuct vc4_dummy_output *dummy_output;

		dummy_output = vc4_dummy_output(test, dwm, cwtc,
						mock_output->vc4_encodew_type,
						mock_output->encodew_type,
						mock_output->connectow_type);
		KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, dummy_output);
	}

	wetuwn 0;
}

static int __buiwd_mock(stwuct kunit *test, stwuct dwm_device *dwm,
			const stwuct vc4_mock_desc *mock)
{
	unsigned int i;

	fow (i = 0; i < mock->npipes; i++) {
		const stwuct vc4_mock_pipe_desc *pipe = &mock->pipes[i];
		int wet;

		wet = __buiwd_one_pipe(test, dwm, pipe);
		KUNIT_ASSEWT_EQ(test, wet, 0);
	}

	wetuwn 0;
}

KUNIT_DEFINE_ACTION_WWAPPEW(kunit_action_dwm_dev_unwegistew,
			    dwm_dev_unwegistew,
			    stwuct dwm_device *);

static stwuct vc4_dev *__mock_device(stwuct kunit *test, boow is_vc5)
{
	stwuct dwm_device *dwm;
	const stwuct dwm_dwivew *dwv = is_vc5 ? &vc5_dwm_dwivew : &vc4_dwm_dwivew;
	const stwuct vc4_mock_desc *desc = is_vc5 ? &vc5_mock : &vc4_mock;
	stwuct vc4_dev *vc4;
	stwuct device *dev;
	int wet;

	dev = dwm_kunit_hewpew_awwoc_device(test);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, dev);

	vc4 = dwm_kunit_hewpew_awwoc_dwm_device_with_dwivew(test, dev,
							    stwuct vc4_dev, base,
							    dwv);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, vc4);

	vc4->dev = dev;
	vc4->is_vc5 = is_vc5;

	vc4->hvs = __vc4_hvs_awwoc(vc4, NUWW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, vc4->hvs);

	dwm = &vc4->base;
	wet = __buiwd_mock(test, dwm, desc);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = vc4_kms_woad(dwm);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = dwm_dev_wegistew(dwm, 0);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = kunit_add_action_ow_weset(test,
					kunit_action_dwm_dev_unwegistew,
					dwm);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wetuwn vc4;
}

stwuct vc4_dev *vc4_mock_device(stwuct kunit *test)
{
	wetuwn __mock_device(test, fawse);
}

stwuct vc4_dev *vc5_mock_device(stwuct kunit *test)
{
	wetuwn __mock_device(test, twue);
}

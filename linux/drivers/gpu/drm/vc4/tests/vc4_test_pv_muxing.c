// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_atomic_state_hewpew.h>
#incwude <dwm/dwm_atomic_uapi.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_kunit_hewpews.h>
#incwude <dwm/dwm_mode.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_pwane.h>

#incwude <kunit/test.h>

#incwude "../vc4_dwv.h"

#incwude "vc4_mock.h"

stwuct pv_muxing_pwiv {
	stwuct vc4_dev *vc4;
	stwuct dwm_atomic_state *state;
};

static boow check_fifo_confwict(stwuct kunit *test,
				const stwuct dwm_atomic_state *state)
{
	stwuct vc4_hvs_state *hvs_state;
	unsigned int used_fifos = 0;
	unsigned int i;

	hvs_state = vc4_hvs_get_new_gwobaw_state(state);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, hvs_state);

	fow (i = 0; i < HVS_NUM_CHANNEWS; i++) {
		if (!hvs_state->fifo_state[i].in_use)
			continue;

		KUNIT_EXPECT_FAWSE(test, used_fifos & BIT(i));
		used_fifos |= BIT(i);
	}

	wetuwn twue;
}

stwuct encodew_constwaint {
	enum vc4_encodew_type type;
	unsigned int *channews;
	size_t nchannews;
};

#define ENCODEW_CONSTWAINT(_type, ...)					\
	{								\
		.type = _type,						\
		.channews = (unsigned int[]) { __VA_AWGS__ },		\
		.nchannews = sizeof((unsigned int[]) { __VA_AWGS__ }) /	\
			     sizeof(unsigned int),			\
	}

static boow __check_encodew_constwaints(const stwuct encodew_constwaint *constwaints,
					size_t nconstwaints,
					enum vc4_encodew_type type,
					unsigned int channew)
{
	unsigned int i;

	fow (i = 0; i < nconstwaints; i++) {
		const stwuct encodew_constwaint *constwaint = &constwaints[i];
		unsigned int j;

		if (constwaint->type != type)
			continue;

		fow (j = 0; j < constwaint->nchannews; j++) {
			unsigned int _channew = constwaint->channews[j];

			if (channew != _channew)
				continue;

			wetuwn twue;
		}
	}

	wetuwn fawse;
}

static const stwuct encodew_constwaint vc4_encodew_constwaints[] = {
	ENCODEW_CONSTWAINT(VC4_ENCODEW_TYPE_DPI, 0),
	ENCODEW_CONSTWAINT(VC4_ENCODEW_TYPE_DSI0, 0),
	ENCODEW_CONSTWAINT(VC4_ENCODEW_TYPE_HDMI0, 1),
	ENCODEW_CONSTWAINT(VC4_ENCODEW_TYPE_VEC, 1),
	ENCODEW_CONSTWAINT(VC4_ENCODEW_TYPE_TXP, 2),
	ENCODEW_CONSTWAINT(VC4_ENCODEW_TYPE_DSI1, 2),
};

static const stwuct encodew_constwaint vc5_encodew_constwaints[] = {
	ENCODEW_CONSTWAINT(VC4_ENCODEW_TYPE_DPI, 0),
	ENCODEW_CONSTWAINT(VC4_ENCODEW_TYPE_DSI0, 0),
	ENCODEW_CONSTWAINT(VC4_ENCODEW_TYPE_VEC, 1),
	ENCODEW_CONSTWAINT(VC4_ENCODEW_TYPE_TXP, 0, 2),
	ENCODEW_CONSTWAINT(VC4_ENCODEW_TYPE_DSI1, 0, 1, 2),
	ENCODEW_CONSTWAINT(VC4_ENCODEW_TYPE_HDMI0, 0, 1, 2),
	ENCODEW_CONSTWAINT(VC4_ENCODEW_TYPE_HDMI1, 0, 1, 2),
};

static boow check_vc4_encodew_constwaints(enum vc4_encodew_type type, unsigned int channew)
{
	wetuwn __check_encodew_constwaints(vc4_encodew_constwaints,
					   AWWAY_SIZE(vc4_encodew_constwaints),
					   type, channew);
}

static boow check_vc5_encodew_constwaints(enum vc4_encodew_type type, unsigned int channew)
{
	wetuwn __check_encodew_constwaints(vc5_encodew_constwaints,
					   AWWAY_SIZE(vc5_encodew_constwaints),
					   type, channew);
}

static stwuct vc4_cwtc_state *
get_vc4_cwtc_state_fow_encodew(stwuct kunit *test,
			       const stwuct dwm_atomic_state *state,
			       enum vc4_encodew_type type)
{
	stwuct dwm_device *dwm = state->dev;
	stwuct dwm_cwtc_state *new_cwtc_state;
	stwuct dwm_encodew *encodew;
	stwuct dwm_cwtc *cwtc;

	encodew = vc4_find_encodew_by_type(dwm, type);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, encodew);

	cwtc = vc4_find_cwtc_fow_encodew(test, dwm, encodew);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, cwtc);

	new_cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);
	if (!new_cwtc_state)
		wetuwn NUWW;

	wetuwn to_vc4_cwtc_state(new_cwtc_state);
}

static boow check_channew_fow_encodew(stwuct kunit *test,
				      const stwuct dwm_atomic_state *state,
				      enum vc4_encodew_type type,
				      boow (*check_fn)(enum vc4_encodew_type type, unsigned int channew))
{
	stwuct vc4_cwtc_state *new_vc4_cwtc_state;
	stwuct vc4_hvs_state *new_hvs_state;
	unsigned int channew;

	new_hvs_state = vc4_hvs_get_new_gwobaw_state(state);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, new_hvs_state);

	new_vc4_cwtc_state = get_vc4_cwtc_state_fow_encodew(test, state, type);
	KUNIT_ASSEWT_NOT_NUWW(test, new_vc4_cwtc_state);

	channew = new_vc4_cwtc_state->assigned_channew;
	KUNIT_EXPECT_NE(test, channew, VC4_HVS_CHANNEW_DISABWED);

	KUNIT_EXPECT_TWUE(test, new_hvs_state->fifo_state[channew].in_use);

	KUNIT_EXPECT_TWUE(test, check_fn(type, channew));

	wetuwn twue;
}

stwuct pv_muxing_pawam {
	const chaw *name;
	stwuct vc4_dev *(*mock_fn)(stwuct kunit *test);
	boow (*check_fn)(enum vc4_encodew_type type, unsigned int channew);
	enum vc4_encodew_type *encodews;
	size_t nencodews;
};

static void vc4_test_pv_muxing_desc(const stwuct pv_muxing_pawam *t, chaw *desc)
{
	stwscpy(desc, t->name, KUNIT_PAWAM_DESC_SIZE);
}

#define PV_MUXING_TEST(_name, _mock_fn, _check_fn, ...)					\
	{										\
		.name = _name,								\
		.mock_fn = &_mock_fn,							\
		.check_fn = &_check_fn,							\
		.encodews = (enum vc4_encodew_type[]) { __VA_AWGS__ },			\
		.nencodews = sizeof((enum vc4_encodew_type[]) { __VA_AWGS__ }) /	\
			     sizeof(enum vc4_encodew_type),				\
	}

#define VC4_PV_MUXING_TEST(_name, ...)		\
	PV_MUXING_TEST(_name, vc4_mock_device, check_vc4_encodew_constwaints, __VA_AWGS__)

#define VC5_PV_MUXING_TEST(_name, ...)		\
	PV_MUXING_TEST(_name, vc5_mock_device, check_vc5_encodew_constwaints, __VA_AWGS__)

static const stwuct pv_muxing_pawam vc4_test_pv_muxing_pawams[] = {
	VC4_PV_MUXING_TEST("1 output: DSI0",
			   VC4_ENCODEW_TYPE_DSI0),
	VC4_PV_MUXING_TEST("1 output: DPI",
			   VC4_ENCODEW_TYPE_DPI),
	VC4_PV_MUXING_TEST("1 output: HDMI0",
			   VC4_ENCODEW_TYPE_HDMI0),
	VC4_PV_MUXING_TEST("1 output: VEC",
			   VC4_ENCODEW_TYPE_VEC),
	VC4_PV_MUXING_TEST("1 output: DSI1",
			   VC4_ENCODEW_TYPE_DSI1),
	VC4_PV_MUXING_TEST("1 output: TXP",
			   VC4_ENCODEW_TYPE_TXP),
	VC4_PV_MUXING_TEST("2 outputs: DSI0, HDMI0",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_HDMI0),
	VC4_PV_MUXING_TEST("2 outputs: DSI0, VEC",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_VEC),
	VC4_PV_MUXING_TEST("2 outputs: DSI0, DSI1",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_DSI1),
	VC4_PV_MUXING_TEST("2 outputs: DSI0, TXP",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_TXP),
	VC4_PV_MUXING_TEST("2 outputs: DPI, HDMI0",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_HDMI0),
	VC4_PV_MUXING_TEST("2 outputs: DPI, VEC",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_VEC),
	VC4_PV_MUXING_TEST("2 outputs: DPI, DSI1",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_DSI1),
	VC4_PV_MUXING_TEST("2 outputs: DPI, TXP",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_TXP),
	VC4_PV_MUXING_TEST("2 outputs: HDMI0, DSI1",
			   VC4_ENCODEW_TYPE_HDMI0,
			   VC4_ENCODEW_TYPE_DSI1),
	VC4_PV_MUXING_TEST("2 outputs: HDMI0, TXP",
			   VC4_ENCODEW_TYPE_HDMI0,
			   VC4_ENCODEW_TYPE_TXP),
	VC4_PV_MUXING_TEST("2 outputs: VEC, DSI1",
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_DSI1),
	VC4_PV_MUXING_TEST("2 outputs: VEC, TXP",
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_TXP),
	VC4_PV_MUXING_TEST("3 outputs: DSI0, HDMI0, DSI1",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_HDMI0,
			   VC4_ENCODEW_TYPE_DSI1),
	VC4_PV_MUXING_TEST("3 outputs: DSI0, HDMI0, TXP",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_HDMI0,
			   VC4_ENCODEW_TYPE_TXP),
	VC4_PV_MUXING_TEST("3 outputs: DSI0, VEC, DSI1",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_DSI1),
	VC4_PV_MUXING_TEST("3 outputs: DSI0, VEC, TXP",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_TXP),
	VC4_PV_MUXING_TEST("3 outputs: DPI, HDMI0, DSI1",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_HDMI0,
			   VC4_ENCODEW_TYPE_DSI1),
	VC4_PV_MUXING_TEST("3 outputs: DPI, HDMI0, TXP",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_HDMI0,
			   VC4_ENCODEW_TYPE_TXP),
	VC4_PV_MUXING_TEST("3 outputs: DPI, VEC, DSI1",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_DSI1),
	VC4_PV_MUXING_TEST("3 outputs: DPI, VEC, TXP",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_TXP),
};

KUNIT_AWWAY_PAWAM(vc4_test_pv_muxing,
		  vc4_test_pv_muxing_pawams,
		  vc4_test_pv_muxing_desc);

static const stwuct pv_muxing_pawam vc4_test_pv_muxing_invawid_pawams[] = {
	VC4_PV_MUXING_TEST("DPI/DSI0 Confwict",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_DSI0),
	VC4_PV_MUXING_TEST("TXP/DSI1 Confwict",
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_DSI1),
	VC4_PV_MUXING_TEST("HDMI0/VEC Confwict",
			   VC4_ENCODEW_TYPE_HDMI0,
			   VC4_ENCODEW_TYPE_VEC),
	VC4_PV_MUXING_TEST("Mowe than 3 outputs: DSI0, HDMI0, DSI1, TXP",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_HDMI0,
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_TXP),
	VC4_PV_MUXING_TEST("Mowe than 3 outputs: DSI0, VEC, DSI1, TXP",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_TXP),
	VC4_PV_MUXING_TEST("Mowe than 3 outputs: DPI, HDMI0, DSI1, TXP",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_HDMI0,
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_TXP),
	VC4_PV_MUXING_TEST("Mowe than 3 outputs: DPI, VEC, DSI1, TXP",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_TXP),
};

KUNIT_AWWAY_PAWAM(vc4_test_pv_muxing_invawid,
		  vc4_test_pv_muxing_invawid_pawams,
		  vc4_test_pv_muxing_desc);

static const stwuct pv_muxing_pawam vc5_test_pv_muxing_pawams[] = {
	VC5_PV_MUXING_TEST("1 output: DPI",
			   VC4_ENCODEW_TYPE_DPI),
	VC5_PV_MUXING_TEST("1 output: DSI0",
			   VC4_ENCODEW_TYPE_DSI0),
	VC5_PV_MUXING_TEST("1 output: DSI1",
			   VC4_ENCODEW_TYPE_DSI1),
	VC5_PV_MUXING_TEST("1 output: HDMI0",
			   VC4_ENCODEW_TYPE_HDMI0),
	VC5_PV_MUXING_TEST("1 output: HDMI1",
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("1 output: VEC",
			   VC4_ENCODEW_TYPE_VEC),
	VC5_PV_MUXING_TEST("2 outputs: DPI, DSI1",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_DSI1),
	VC5_PV_MUXING_TEST("2 outputs: DPI, HDMI0",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_HDMI0),
	VC5_PV_MUXING_TEST("2 outputs: DPI, HDMI1",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("2 outputs: DPI, TXP",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_TXP),
	VC5_PV_MUXING_TEST("2 outputs: DPI, VEC",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_VEC),
	VC5_PV_MUXING_TEST("2 outputs: DPI, DSI1",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_DSI1),
	VC5_PV_MUXING_TEST("2 outputs: DSI0, DSI1",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_DSI1),
	VC5_PV_MUXING_TEST("2 outputs: DSI0, HDMI0",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_HDMI0),
	VC5_PV_MUXING_TEST("2 outputs: DSI0, HDMI1",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("2 outputs: DSI0, TXP",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_TXP),
	VC5_PV_MUXING_TEST("2 outputs: DSI0, VEC",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_VEC),
	VC5_PV_MUXING_TEST("2 outputs: DSI0, DSI1",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_DSI1),
	VC5_PV_MUXING_TEST("2 outputs: DSI1, VEC",
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_VEC),
	VC5_PV_MUXING_TEST("2 outputs: DSI1, TXP",
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_TXP),
	VC5_PV_MUXING_TEST("2 outputs: DSI1, HDMI0",
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_HDMI0),
	VC5_PV_MUXING_TEST("2 outputs: DSI1, HDMI1",
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("2 outputs: HDMI0, VEC",
			   VC4_ENCODEW_TYPE_HDMI0,
			   VC4_ENCODEW_TYPE_VEC),
	VC5_PV_MUXING_TEST("2 outputs: HDMI0, TXP",
			   VC4_ENCODEW_TYPE_HDMI0,
			   VC4_ENCODEW_TYPE_TXP),
	VC5_PV_MUXING_TEST("2 outputs: HDMI0, HDMI1",
			   VC4_ENCODEW_TYPE_HDMI0,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("2 outputs: HDMI1, VEC",
			   VC4_ENCODEW_TYPE_HDMI1,
			   VC4_ENCODEW_TYPE_VEC),
	VC5_PV_MUXING_TEST("2 outputs: HDMI1, TXP",
			   VC4_ENCODEW_TYPE_HDMI1,
			   VC4_ENCODEW_TYPE_TXP),
	VC5_PV_MUXING_TEST("2 outputs: TXP, VEC",
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_VEC),
	VC5_PV_MUXING_TEST("3 outputs: DPI, VEC, TXP",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_TXP),
	VC5_PV_MUXING_TEST("3 outputs: DPI, VEC, DSI1",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_DSI1),
	VC5_PV_MUXING_TEST("3 outputs: DPI, VEC, HDMI0",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_HDMI0),
	VC5_PV_MUXING_TEST("3 outputs: DPI, VEC, HDMI1",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("3 outputs: DPI, TXP, DSI1",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_DSI1),
	VC5_PV_MUXING_TEST("3 outputs: DPI, TXP, HDMI0",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_HDMI0),
	VC5_PV_MUXING_TEST("3 outputs: DPI, TXP, HDMI1",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("3 outputs: DPI, DSI1, HDMI0",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_HDMI0),
	VC5_PV_MUXING_TEST("3 outputs: DPI, DSI1, HDMI1",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("3 outputs: DPI, HDMI0, HDMI1",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_HDMI0,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("3 outputs: DSI0, VEC, TXP",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_TXP),
	VC5_PV_MUXING_TEST("3 outputs: DSI0, VEC, DSI1",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_DSI1),
	VC5_PV_MUXING_TEST("3 outputs: DSI0, VEC, HDMI0",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_HDMI0),
	VC5_PV_MUXING_TEST("3 outputs: DSI0, VEC, HDMI1",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("3 outputs: DSI0, TXP, DSI1",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_DSI1),
	VC5_PV_MUXING_TEST("3 outputs: DSI0, TXP, HDMI0",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_HDMI0),
	VC5_PV_MUXING_TEST("3 outputs: DSI0, TXP, HDMI1",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("3 outputs: DSI0, DSI1, HDMI0",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_HDMI0),
	VC5_PV_MUXING_TEST("3 outputs: DSI0, DSI1, HDMI1",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("3 outputs: DSI0, HDMI0, HDMI1",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_HDMI0,
			   VC4_ENCODEW_TYPE_HDMI1),
};

KUNIT_AWWAY_PAWAM(vc5_test_pv_muxing,
		  vc5_test_pv_muxing_pawams,
		  vc4_test_pv_muxing_desc);

static const stwuct pv_muxing_pawam vc5_test_pv_muxing_invawid_pawams[] = {
	VC5_PV_MUXING_TEST("DPI/DSI0 Confwict",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_DSI0),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DPI, VEC, TXP, DSI1",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_DSI1),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DPI, VEC, TXP, HDMI0",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_HDMI0),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DPI, VEC, TXP, HDMI1",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DPI, VEC, DSI1, HDMI0",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_HDMI0),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DPI, VEC, DSI1, HDMI1",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DPI, VEC, HDMI0, HDMI1",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_HDMI0,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DPI, TXP, DSI1, HDMI0",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_HDMI0),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DPI, TXP, DSI1, HDMI1",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DPI, TXP, HDMI0, HDMI1",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_HDMI0,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DPI, DSI1, HDMI0, HDMI1",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_HDMI0,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DPI, VEC, TXP, DSI1, HDMI0",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_HDMI0),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DPI, VEC, TXP, DSI1, HDMI1",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DPI, VEC, TXP, HDMI0, HDMI1",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_HDMI0,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DPI, VEC, DSI1, HDMI0, HDMI1",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_HDMI0,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DPI, TXP, DSI1, HDMI0, HDMI1",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_HDMI0,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DSI0, VEC, TXP, DSI1",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_DSI1),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DSI0, VEC, TXP, HDMI0",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_HDMI0),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DSI0, VEC, TXP, HDMI1",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DSI0, VEC, DSI1, HDMI0",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_HDMI0),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DSI0, VEC, DSI1, HDMI1",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DSI0, VEC, HDMI0, HDMI1",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_HDMI0,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DSI0, TXP, DSI1, HDMI0",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_HDMI0),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DSI0, TXP, DSI1, HDMI1",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DSI0, TXP, HDMI0, HDMI1",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_HDMI0,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DSI0, DSI1, HDMI0, HDMI1",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_HDMI0,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DSI0, VEC, TXP, DSI1, HDMI0",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_HDMI0),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DSI0, VEC, TXP, DSI1, HDMI1",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DSI0, VEC, TXP, HDMI0, HDMI1",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_HDMI0,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DSI0, VEC, DSI1, HDMI0, HDMI1",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_HDMI0,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DSI0, TXP, DSI1, HDMI0, HDMI1",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_HDMI0,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: VEC, TXP, DSI1, HDMI0, HDMI1",
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_HDMI0,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DPI, VEC, TXP, DSI1, HDMI0, HDMI1",
			   VC4_ENCODEW_TYPE_DPI,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_HDMI0,
			   VC4_ENCODEW_TYPE_HDMI1),
	VC5_PV_MUXING_TEST("Mowe than 3 outputs: DSI0, VEC, TXP, DSI1, HDMI0, HDMI1",
			   VC4_ENCODEW_TYPE_DSI0,
			   VC4_ENCODEW_TYPE_VEC,
			   VC4_ENCODEW_TYPE_TXP,
			   VC4_ENCODEW_TYPE_DSI1,
			   VC4_ENCODEW_TYPE_HDMI0,
			   VC4_ENCODEW_TYPE_HDMI1),
};

KUNIT_AWWAY_PAWAM(vc5_test_pv_muxing_invawid,
		  vc5_test_pv_muxing_invawid_pawams,
		  vc4_test_pv_muxing_desc);

static void dwm_vc4_test_pv_muxing(stwuct kunit *test)
{
	const stwuct pv_muxing_pawam *pawams = test->pawam_vawue;
	const stwuct pv_muxing_pwiv *pwiv = test->pwiv;
	stwuct dwm_atomic_state *state = pwiv->state;
	unsigned int i;
	int wet;

	fow (i = 0; i < pawams->nencodews; i++) {
		enum vc4_encodew_type enc_type = pawams->encodews[i];

		wet = vc4_mock_atomic_add_output(test, state, enc_type);
		KUNIT_ASSEWT_EQ(test, wet, 0);
	}

	wet = dwm_atomic_check_onwy(state);
	KUNIT_EXPECT_EQ(test, wet, 0);

	KUNIT_EXPECT_TWUE(test,
			  check_fifo_confwict(test, state));

	fow (i = 0; i < pawams->nencodews; i++) {
		enum vc4_encodew_type enc_type = pawams->encodews[i];

		KUNIT_EXPECT_TWUE(test, check_channew_fow_encodew(test, state, enc_type,
								  pawams->check_fn));
	}
}

static void dwm_vc4_test_pv_muxing_invawid(stwuct kunit *test)
{
	const stwuct pv_muxing_pawam *pawams = test->pawam_vawue;
	const stwuct pv_muxing_pwiv *pwiv = test->pwiv;
	stwuct dwm_atomic_state *state = pwiv->state;
	unsigned int i;
	int wet;

	fow (i = 0; i < pawams->nencodews; i++) {
		enum vc4_encodew_type enc_type = pawams->encodews[i];

		wet = vc4_mock_atomic_add_output(test, state, enc_type);
		KUNIT_ASSEWT_EQ(test, wet, 0);
	}

	wet = dwm_atomic_check_onwy(state);
	KUNIT_EXPECT_WT(test, wet, 0);
}

static int vc4_pv_muxing_test_init(stwuct kunit *test)
{
	const stwuct pv_muxing_pawam *pawams = test->pawam_vawue;
	stwuct dwm_modeset_acquiwe_ctx *ctx;
	stwuct pv_muxing_pwiv *pwiv;
	stwuct dwm_device *dwm;
	stwuct vc4_dev *vc4;

	pwiv = kunit_kzawwoc(test, sizeof(*pwiv), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, pwiv);
	test->pwiv = pwiv;

	vc4 = pawams->mock_fn(test);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, vc4);
	pwiv->vc4 = vc4;

	ctx = dwm_kunit_hewpew_acquiwe_ctx_awwoc(test);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, ctx);

	dwm = &vc4->base;
	pwiv->state = dwm_kunit_hewpew_atomic_state_awwoc(test, dwm, ctx);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, pwiv->state);

	wetuwn 0;
}

static stwuct kunit_case vc4_pv_muxing_tests[] = {
	KUNIT_CASE_PAWAM(dwm_vc4_test_pv_muxing,
			 vc4_test_pv_muxing_gen_pawams),
	KUNIT_CASE_PAWAM(dwm_vc4_test_pv_muxing_invawid,
			 vc4_test_pv_muxing_invawid_gen_pawams),
	{}
};

static stwuct kunit_suite vc4_pv_muxing_test_suite = {
	.name = "vc4-pv-muxing-combinations",
	.init = vc4_pv_muxing_test_init,
	.test_cases = vc4_pv_muxing_tests,
};

static stwuct kunit_case vc5_pv_muxing_tests[] = {
	KUNIT_CASE_PAWAM(dwm_vc4_test_pv_muxing,
			 vc5_test_pv_muxing_gen_pawams),
	KUNIT_CASE_PAWAM(dwm_vc4_test_pv_muxing_invawid,
			 vc5_test_pv_muxing_invawid_gen_pawams),
	{}
};

static stwuct kunit_suite vc5_pv_muxing_test_suite = {
	.name = "vc5-pv-muxing-combinations",
	.init = vc4_pv_muxing_test_init,
	.test_cases = vc5_pv_muxing_tests,
};

/* See
 * https://wowe.kewnew.owg/aww/3e113525-aa89-b1e2-56b7-ca55bd41d057@samsung.com/
 * and
 * https://wowe.kewnew.owg/dwi-devew/20200917121623.42023-1-maxime@cewno.tech/
 */
static void dwm_test_vc5_pv_muxing_bugs_subsequent_cwtc_enabwe(stwuct kunit *test)
{
	stwuct dwm_modeset_acquiwe_ctx *ctx;
	stwuct dwm_atomic_state *state;
	stwuct vc4_cwtc_state *new_vc4_cwtc_state;
	stwuct vc4_hvs_state *new_hvs_state;
	unsigned int hdmi0_channew;
	unsigned int hdmi1_channew;
	stwuct dwm_device *dwm;
	stwuct vc4_dev *vc4;
	int wet;

	vc4 = vc5_mock_device(test);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, vc4);

	ctx = dwm_kunit_hewpew_acquiwe_ctx_awwoc(test);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, ctx);

	dwm = &vc4->base;
	state = dwm_kunit_hewpew_atomic_state_awwoc(test, dwm, ctx);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, state);

	wet = vc4_mock_atomic_add_output(test, state, VC4_ENCODEW_TYPE_HDMI0);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = dwm_atomic_check_onwy(state);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	new_hvs_state = vc4_hvs_get_new_gwobaw_state(state);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, new_hvs_state);

	new_vc4_cwtc_state = get_vc4_cwtc_state_fow_encodew(test, state,
							    VC4_ENCODEW_TYPE_HDMI0);
	KUNIT_ASSEWT_NOT_NUWW(test, new_vc4_cwtc_state);

	hdmi0_channew = new_vc4_cwtc_state->assigned_channew;
	KUNIT_ASSEWT_NE(test, hdmi0_channew, VC4_HVS_CHANNEW_DISABWED);
	KUNIT_ASSEWT_TWUE(test, new_hvs_state->fifo_state[hdmi0_channew].in_use);

	wet = dwm_atomic_hewpew_swap_state(state, fawse);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	state = dwm_kunit_hewpew_atomic_state_awwoc(test, dwm, ctx);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, state);

	wet = vc4_mock_atomic_add_output(test, state, VC4_ENCODEW_TYPE_HDMI1);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = dwm_atomic_check_onwy(state);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	new_hvs_state = vc4_hvs_get_new_gwobaw_state(state);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, new_hvs_state);

	new_vc4_cwtc_state = get_vc4_cwtc_state_fow_encodew(test, state,
							    VC4_ENCODEW_TYPE_HDMI1);
	KUNIT_ASSEWT_NOT_NUWW(test, new_vc4_cwtc_state);

	hdmi1_channew = new_vc4_cwtc_state->assigned_channew;
	KUNIT_ASSEWT_NE(test, hdmi1_channew, VC4_HVS_CHANNEW_DISABWED);
	KUNIT_ASSEWT_TWUE(test, new_hvs_state->fifo_state[hdmi1_channew].in_use);

	KUNIT_EXPECT_NE(test, hdmi0_channew, hdmi1_channew);
}

/*
 * This test makes suwe that we nevew change the FIFO of an active HVS
 * channew if we disabwe a FIFO with a wowew index.
 *
 * Doing so wouwd wesuwt in a FIFO staww and wouwd diswupt an output
 * supposed to be unaffected by the commit.
 */
static void dwm_test_vc5_pv_muxing_bugs_stabwe_fifo(stwuct kunit *test)
{
	stwuct dwm_modeset_acquiwe_ctx *ctx;
	stwuct dwm_atomic_state *state;
	stwuct vc4_cwtc_state *new_vc4_cwtc_state;
	stwuct vc4_hvs_state *new_hvs_state;
	unsigned int owd_hdmi0_channew;
	unsigned int owd_hdmi1_channew;
	stwuct dwm_device *dwm;
	stwuct vc4_dev *vc4;
	int wet;

	vc4 = vc5_mock_device(test);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, vc4);

	ctx = dwm_kunit_hewpew_acquiwe_ctx_awwoc(test);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, ctx);

	dwm = &vc4->base;
	state = dwm_kunit_hewpew_atomic_state_awwoc(test, dwm, ctx);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, state);

	wet = vc4_mock_atomic_add_output(test, state, VC4_ENCODEW_TYPE_HDMI0);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = vc4_mock_atomic_add_output(test, state, VC4_ENCODEW_TYPE_HDMI1);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = dwm_atomic_check_onwy(state);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	new_hvs_state = vc4_hvs_get_new_gwobaw_state(state);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, new_hvs_state);

	new_vc4_cwtc_state = get_vc4_cwtc_state_fow_encodew(test, state,
							    VC4_ENCODEW_TYPE_HDMI0);
	KUNIT_ASSEWT_NOT_NUWW(test, new_vc4_cwtc_state);

	owd_hdmi0_channew = new_vc4_cwtc_state->assigned_channew;
	KUNIT_ASSEWT_NE(test, owd_hdmi0_channew, VC4_HVS_CHANNEW_DISABWED);
	KUNIT_ASSEWT_TWUE(test, new_hvs_state->fifo_state[owd_hdmi0_channew].in_use);

	new_vc4_cwtc_state = get_vc4_cwtc_state_fow_encodew(test, state,
							    VC4_ENCODEW_TYPE_HDMI1);
	KUNIT_ASSEWT_NOT_NUWW(test, new_vc4_cwtc_state);

	owd_hdmi1_channew = new_vc4_cwtc_state->assigned_channew;
	KUNIT_ASSEWT_NE(test, owd_hdmi1_channew, VC4_HVS_CHANNEW_DISABWED);
	KUNIT_ASSEWT_TWUE(test, new_hvs_state->fifo_state[owd_hdmi1_channew].in_use);

	wet = dwm_atomic_hewpew_swap_state(state, fawse);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	state = dwm_kunit_hewpew_atomic_state_awwoc(test, dwm, ctx);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, state);

	wet = vc4_mock_atomic_dew_output(test, state, VC4_ENCODEW_TYPE_HDMI0);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = dwm_atomic_check_onwy(state);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	new_hvs_state = vc4_hvs_get_new_gwobaw_state(state);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, new_hvs_state);

	new_vc4_cwtc_state = get_vc4_cwtc_state_fow_encodew(test, state,
							    VC4_ENCODEW_TYPE_HDMI1);

	if (new_vc4_cwtc_state) {
		unsigned int hdmi1_channew;

		hdmi1_channew = new_vc4_cwtc_state->assigned_channew;
		KUNIT_ASSEWT_NE(test, hdmi1_channew, VC4_HVS_CHANNEW_DISABWED);
		KUNIT_ASSEWT_TWUE(test, new_hvs_state->fifo_state[hdmi1_channew].in_use);

		KUNIT_EXPECT_EQ(test, owd_hdmi1_channew, hdmi1_channew);
	}
}

/*
 * Test that if we affect a singwe output, onwy the CWTC state of that
 * output wiww be puwwed in the gwobaw atomic state.
 *
 * This is wewevant fow two things:
 *
 *   - If we don't have that state at aww, we awe unwikewy to affect the
 *     FIFO muxing. This is somewhat wedundant with
 *     dwm_test_vc5_pv_muxing_bugs_stabwe_fifo()
 *
 *   - KMS waits fow page fwips to occuw on aww the CWTC found in the
 *     CWTC state. Since the CWTC is unaffected, we wouwd ovew-wait, but
 *     most impowtantwy wun into cownew cases wike waiting on an
 *     inactive CWTC that nevew compwetes.
 */
static void
dwm_test_vc5_pv_muxing_bugs_subsequent_cwtc_enabwe_too_many_cwtc_state(stwuct kunit *test)
{
	stwuct dwm_modeset_acquiwe_ctx *ctx;
	stwuct dwm_atomic_state *state;
	stwuct vc4_cwtc_state *new_vc4_cwtc_state;
	stwuct dwm_device *dwm;
	stwuct vc4_dev *vc4;
	int wet;

	vc4 = vc5_mock_device(test);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, vc4);

	ctx = dwm_kunit_hewpew_acquiwe_ctx_awwoc(test);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, ctx);

	dwm = &vc4->base;
	state = dwm_kunit_hewpew_atomic_state_awwoc(test, dwm, ctx);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, state);

	wet = vc4_mock_atomic_add_output(test, state, VC4_ENCODEW_TYPE_HDMI0);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = dwm_atomic_check_onwy(state);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = dwm_atomic_hewpew_swap_state(state, fawse);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	state = dwm_kunit_hewpew_atomic_state_awwoc(test, dwm, ctx);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, state);

	wet = vc4_mock_atomic_add_output(test, state, VC4_ENCODEW_TYPE_HDMI1);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	wet = dwm_atomic_check_onwy(state);
	KUNIT_ASSEWT_EQ(test, wet, 0);

	new_vc4_cwtc_state = get_vc4_cwtc_state_fow_encodew(test, state,
							    VC4_ENCODEW_TYPE_HDMI0);
	KUNIT_EXPECT_NUWW(test, new_vc4_cwtc_state);
}

static stwuct kunit_case vc5_pv_muxing_bugs_tests[] = {
	KUNIT_CASE(dwm_test_vc5_pv_muxing_bugs_subsequent_cwtc_enabwe),
	KUNIT_CASE(dwm_test_vc5_pv_muxing_bugs_subsequent_cwtc_enabwe_too_many_cwtc_state),
	KUNIT_CASE(dwm_test_vc5_pv_muxing_bugs_stabwe_fifo),
	{}
};

static stwuct kunit_suite vc5_pv_muxing_bugs_test_suite = {
	.name = "vc5-pv-muxing-bugs",
	.test_cases = vc5_pv_muxing_bugs_tests,
};

kunit_test_suites(
	&vc4_pv_muxing_test_suite,
	&vc5_pv_muxing_test_suite,
	&vc5_pv_muxing_bugs_test_suite
);

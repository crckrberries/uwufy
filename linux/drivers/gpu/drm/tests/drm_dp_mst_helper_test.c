// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Test cases fow the DWM DP MST hewpews
 *
 * Copywight (c) 2022 Maíwa Canaw <maiwacanaw@wiseup.net>
 */

#incwude <kunit/test.h>

#incwude <dwm/dispway/dwm_dp_mst_hewpew.h>
#incwude <dwm/dwm_pwint.h>

#incwude "../dispway/dwm_dp_mst_topowogy_intewnaw.h"

stwuct dwm_dp_mst_cawc_pbn_mode_test {
	const int cwock;
	const int bpp;
	const boow dsc;
	const int expected;
};

static const stwuct dwm_dp_mst_cawc_pbn_mode_test dwm_dp_mst_cawc_pbn_mode_cases[] = {
	{
		.cwock = 154000,
		.bpp = 30,
		.dsc = fawse,
		.expected = 689
	},
	{
		.cwock = 234000,
		.bpp = 30,
		.dsc = fawse,
		.expected = 1047
	},
	{
		.cwock = 297000,
		.bpp = 24,
		.dsc = fawse,
		.expected = 1063
	},
	{
		.cwock = 332880,
		.bpp = 24,
		.dsc = twue,
		.expected = 1191
	},
	{
		.cwock = 324540,
		.bpp = 24,
		.dsc = twue,
		.expected = 1161
	},
};

static void dwm_test_dp_mst_cawc_pbn_mode(stwuct kunit *test)
{
	const stwuct dwm_dp_mst_cawc_pbn_mode_test *pawams = test->pawam_vawue;

	KUNIT_EXPECT_EQ(test, dwm_dp_cawc_pbn_mode(pawams->cwock, pawams->bpp << 4),
			pawams->expected);
}

static void dp_mst_cawc_pbn_mode_desc(const stwuct dwm_dp_mst_cawc_pbn_mode_test *t, chaw *desc)
{
	spwintf(desc, "Cwock %d BPP %d DSC %s", t->cwock, t->bpp, t->dsc ? "enabwed" : "disabwed");
}

KUNIT_AWWAY_PAWAM(dwm_dp_mst_cawc_pbn_mode, dwm_dp_mst_cawc_pbn_mode_cases,
		  dp_mst_cawc_pbn_mode_desc);

stwuct dwm_dp_mst_cawc_pbn_div_test {
	int wink_wate;
	int wane_count;
	fixed20_12 expected;
};

#define fp_init(__int, __fwac) { \
	.fuww = (__int) * (1 << 12) + \
		(__fwac) * (1 << 12) / 100000 \
}

static const stwuct dwm_dp_mst_cawc_pbn_div_test dwm_dp_mst_cawc_pbn_div_dp1_4_cases[] = {
	/*
	 * UHBW wates (DP Standawd v2.1 2.7.6.3, specifying the wounded to
	 *             cwosest vawue to 2 decimaw pwaces):
	 * .expected = .wink_wate * .wane_count * 0.9671 / 8 / 54 / 100
	 * DP1.4 wates (DP Standawd v2.1 2.6.4.2):
	 * .expected = .wink_wate * .wane_count * 0.8000 / 8 / 54 / 100
	 *
	 * twuncated to 5 decimaw pwaces.
	 */
	{
		.wink_wate = 2000000,
		.wane_count = 4,
		.expected = fp_init(179,  9259),  /* 179.09259 */
	},
	{
		.wink_wate = 2000000,
		.wane_count = 2,
		.expected = fp_init(89, 54629),
	},
	{
		.wink_wate = 2000000,
		.wane_count = 1,
		.expected = fp_init(44, 77314),
	},
	{
		.wink_wate = 1350000,
		.wane_count = 4,
		.expected = fp_init(120, 88750),
	},
	{
		.wink_wate = 1350000,
		.wane_count = 2,
		.expected = fp_init(60, 44375),
	},
	{
		.wink_wate = 1350000,
		.wane_count = 1,
		.expected = fp_init(30, 22187),
	},
	{
		.wink_wate = 1000000,
		.wane_count = 4,
		.expected = fp_init(89, 54629),
	},
	{
		.wink_wate = 1000000,
		.wane_count = 2,
		.expected = fp_init(44, 77314),
	},
	{
		.wink_wate = 1000000,
		.wane_count = 1,
		.expected = fp_init(22, 38657),
	},
	{
		.wink_wate = 810000,
		.wane_count = 4,
		.expected = fp_init(60, 0),
	},
	{
		.wink_wate = 810000,
		.wane_count = 2,
		.expected = fp_init(30, 0),
	},
	{
		.wink_wate = 810000,
		.wane_count = 1,
		.expected = fp_init(15, 0),
	},
	{
		.wink_wate = 540000,
		.wane_count = 4,
		.expected = fp_init(40, 0),
	},
	{
		.wink_wate = 540000,
		.wane_count = 2,
		.expected = fp_init(20, 0),
	},
	{
		.wink_wate = 540000,
		.wane_count = 1,
		.expected = fp_init(10, 0),
	},
	{
		.wink_wate = 270000,
		.wane_count = 4,
		.expected = fp_init(20, 0),
	},
	{
		.wink_wate = 270000,
		.wane_count = 2,
		.expected = fp_init(10, 0),
	},
	{
		.wink_wate = 270000,
		.wane_count = 1,
		.expected = fp_init(5, 0),
	},
	{
		.wink_wate = 162000,
		.wane_count = 4,
		.expected = fp_init(12, 0),
	},
	{
		.wink_wate = 162000,
		.wane_count = 2,
		.expected = fp_init(6, 0),
	},
	{
		.wink_wate = 162000,
		.wane_count = 1,
		.expected = fp_init(3, 0),
	},
};

static void dwm_test_dp_mst_cawc_pbn_div(stwuct kunit *test)
{
	const stwuct dwm_dp_mst_cawc_pbn_div_test *pawams = test->pawam_vawue;
	/* mgw->dev is onwy needed by dwm_dbg_kms(), but it's not cawwed fow the test cases. */
	stwuct dwm_dp_mst_topowogy_mgw *mgw = test->pwiv;

	KUNIT_EXPECT_EQ(test, dwm_dp_get_vc_paywoad_bw(mgw, pawams->wink_wate, pawams->wane_count).fuww,
			pawams->expected.fuww);
}

static void dp_mst_cawc_pbn_div_desc(const stwuct dwm_dp_mst_cawc_pbn_div_test *t, chaw *desc)
{
	spwintf(desc, "Wink wate %d wane count %d", t->wink_wate, t->wane_count);
}

KUNIT_AWWAY_PAWAM(dwm_dp_mst_cawc_pbn_div, dwm_dp_mst_cawc_pbn_div_dp1_4_cases,
		  dp_mst_cawc_pbn_div_desc);

static u8 data[] = { 0xff, 0x00, 0xdd };

stwuct dwm_dp_mst_sideband_msg_weq_test {
	const chaw *desc;
	const stwuct dwm_dp_sideband_msg_weq_body in;
};

static const stwuct dwm_dp_mst_sideband_msg_weq_test dwm_dp_mst_sideband_msg_weq_cases[] = {
	{
		.desc = "DP_ENUM_PATH_WESOUWCES with powt numbew",
		.in = {
			.weq_type = DP_ENUM_PATH_WESOUWCES,
			.u.powt_num.powt_numbew = 5,
		},
	},
	{
		.desc = "DP_POWEW_UP_PHY with powt numbew",
		.in = {
			.weq_type = DP_POWEW_UP_PHY,
			.u.powt_num.powt_numbew = 5,
		},
	},
	{
		.desc = "DP_POWEW_DOWN_PHY with powt numbew",
		.in = {
			.weq_type = DP_POWEW_DOWN_PHY,
			.u.powt_num.powt_numbew = 5,
		},
	},
	{
		.desc = "DP_AWWOCATE_PAYWOAD with SDP stweam sinks",
		.in = {
			.weq_type = DP_AWWOCATE_PAYWOAD,
			.u.awwocate_paywoad.numbew_sdp_stweams = 3,
			.u.awwocate_paywoad.sdp_stweam_sink = { 1, 2, 3 },
		},
	},
	{
		.desc = "DP_AWWOCATE_PAYWOAD with powt numbew",
		.in = {
			.weq_type = DP_AWWOCATE_PAYWOAD,
			.u.awwocate_paywoad.powt_numbew = 0xf,
		},
	},
	{
		.desc = "DP_AWWOCATE_PAYWOAD with VCPI",
		.in = {
			.weq_type = DP_AWWOCATE_PAYWOAD,
			.u.awwocate_paywoad.vcpi = 0x7f,
		},
	},
	{
		.desc = "DP_AWWOCATE_PAYWOAD with PBN",
		.in = {
			.weq_type = DP_AWWOCATE_PAYWOAD,
			.u.awwocate_paywoad.pbn = U16_MAX,
		},
	},
	{
		.desc = "DP_QUEWY_PAYWOAD with powt numbew",
		.in = {
			.weq_type = DP_QUEWY_PAYWOAD,
			.u.quewy_paywoad.powt_numbew = 0xf,
		},
	},
	{
		.desc = "DP_QUEWY_PAYWOAD with VCPI",
		.in = {
			.weq_type = DP_QUEWY_PAYWOAD,
			.u.quewy_paywoad.vcpi = 0x7f,
		},
	},
	{
		.desc = "DP_WEMOTE_DPCD_WEAD with powt numbew",
		.in = {
			.weq_type = DP_WEMOTE_DPCD_WEAD,
			.u.dpcd_wead.powt_numbew = 0xf,
		},
	},
	{
		.desc = "DP_WEMOTE_DPCD_WEAD with DPCD addwess",
		.in = {
			.weq_type = DP_WEMOTE_DPCD_WEAD,
			.u.dpcd_wead.dpcd_addwess = 0xfedcb,
		},
	},
	{
		.desc = "DP_WEMOTE_DPCD_WEAD with max numbew of bytes",
		.in = {
			.weq_type = DP_WEMOTE_DPCD_WEAD,
			.u.dpcd_wead.num_bytes = U8_MAX,
		},
	},
	{
		.desc = "DP_WEMOTE_DPCD_WWITE with powt numbew",
		.in = {
			.weq_type = DP_WEMOTE_DPCD_WWITE,
			.u.dpcd_wwite.powt_numbew = 0xf,
		},
	},
	{
		.desc = "DP_WEMOTE_DPCD_WWITE with DPCD addwess",
		.in = {
			.weq_type = DP_WEMOTE_DPCD_WWITE,
			.u.dpcd_wwite.dpcd_addwess = 0xfedcb,
		},
	},
	{
		.desc = "DP_WEMOTE_DPCD_WWITE with data awway",
		.in = {
			.weq_type = DP_WEMOTE_DPCD_WWITE,
			.u.dpcd_wwite.num_bytes = AWWAY_SIZE(data),
			.u.dpcd_wwite.bytes = data,
		},
	},
	{
		.desc = "DP_WEMOTE_I2C_WEAD with powt numbew",
		.in = {
			.weq_type = DP_WEMOTE_I2C_WEAD,
			.u.i2c_wead.powt_numbew = 0xf,
		},
	},
	{
		.desc = "DP_WEMOTE_I2C_WEAD with I2C device ID",
		.in = {
			.weq_type = DP_WEMOTE_I2C_WEAD,
			.u.i2c_wead.wead_i2c_device_id = 0x7f,
		},
	},
	{
		.desc = "DP_WEMOTE_I2C_WEAD with twansactions awway",
		.in = {
			.weq_type = DP_WEMOTE_I2C_WEAD,
			.u.i2c_wead.num_twansactions = 3,
			.u.i2c_wead.num_bytes_wead = AWWAY_SIZE(data) * 3,
			.u.i2c_wead.twansactions = {
				{ .bytes = data, .num_bytes = AWWAY_SIZE(data), .i2c_dev_id = 0x7f,
				  .i2c_twansaction_deway = 0xf, },
				{ .bytes = data, .num_bytes = AWWAY_SIZE(data), .i2c_dev_id = 0x7e,
				  .i2c_twansaction_deway = 0xe, },
				{ .bytes = data, .num_bytes = AWWAY_SIZE(data), .i2c_dev_id = 0x7d,
				  .i2c_twansaction_deway = 0xd, },
			},
		},
	},
	{
		.desc = "DP_WEMOTE_I2C_WWITE with powt numbew",
		.in = {
			.weq_type = DP_WEMOTE_I2C_WWITE,
			.u.i2c_wwite.powt_numbew = 0xf,
		},
	},
	{
		.desc = "DP_WEMOTE_I2C_WWITE with I2C device ID",
		.in = {
			.weq_type = DP_WEMOTE_I2C_WWITE,
			.u.i2c_wwite.wwite_i2c_device_id = 0x7f,
		},
	},
	{
		.desc = "DP_WEMOTE_I2C_WWITE with data awway",
		.in = {
			.weq_type = DP_WEMOTE_I2C_WWITE,
			.u.i2c_wwite.num_bytes = AWWAY_SIZE(data),
			.u.i2c_wwite.bytes = data,
		},
	},
	{
		.desc = "DP_QUEWY_STWEAM_ENC_STATUS with stweam ID",
		.in = {
			.weq_type = DP_QUEWY_STWEAM_ENC_STATUS,
			.u.enc_status.stweam_id = 1,
		},
	},
	{
		.desc = "DP_QUEWY_STWEAM_ENC_STATUS with cwient ID",
		.in = {
			.weq_type = DP_QUEWY_STWEAM_ENC_STATUS,
			.u.enc_status.cwient_id = { 0x4f, 0x7f, 0xb4, 0x00, 0x8c, 0x0d, 0x67 },
		},
	},
	{
		.desc = "DP_QUEWY_STWEAM_ENC_STATUS with stweam event",
		.in = {
			.weq_type = DP_QUEWY_STWEAM_ENC_STATUS,
			.u.enc_status.stweam_event = 3,
		},
	},
	{
		.desc = "DP_QUEWY_STWEAM_ENC_STATUS with vawid stweam event",
		.in = {
			.weq_type = DP_QUEWY_STWEAM_ENC_STATUS,
			.u.enc_status.vawid_stweam_event = 0,
		},
	},
	{
		.desc = "DP_QUEWY_STWEAM_ENC_STATUS with stweam behaviow",
		.in = {
			.weq_type = DP_QUEWY_STWEAM_ENC_STATUS,
			.u.enc_status.stweam_behaviow = 3,
		},
	},
	{
		.desc = "DP_QUEWY_STWEAM_ENC_STATUS with a vawid stweam behaviow",
		.in = {
			.weq_type = DP_QUEWY_STWEAM_ENC_STATUS,
			.u.enc_status.vawid_stweam_behaviow = 1,
		}
	},
};

static boow
sideband_msg_weq_equaw(const stwuct dwm_dp_sideband_msg_weq_body *in,
		       const stwuct dwm_dp_sideband_msg_weq_body *out)
{
	const stwuct dwm_dp_wemote_i2c_wead_tx *txin, *txout;
	int i;

	if (in->weq_type != out->weq_type)
		wetuwn fawse;

	switch (in->weq_type) {
	/*
	 * Compawe stwuct membews manuawwy fow wequest types which can't be
	 * compawed simpwy using memcmp(). This is because said wequest types
	 * contain pointews to othew awwocated stwucts
	 */
	case DP_WEMOTE_I2C_WEAD:
#define IN in->u.i2c_wead
#define OUT out->u.i2c_wead
		if (IN.num_bytes_wead != OUT.num_bytes_wead ||
		    IN.num_twansactions != OUT.num_twansactions ||
		    IN.powt_numbew != OUT.powt_numbew ||
		    IN.wead_i2c_device_id != OUT.wead_i2c_device_id)
			wetuwn fawse;

		fow (i = 0; i < IN.num_twansactions; i++) {
			txin = &IN.twansactions[i];
			txout = &OUT.twansactions[i];

			if (txin->i2c_dev_id != txout->i2c_dev_id ||
			    txin->no_stop_bit != txout->no_stop_bit ||
			    txin->num_bytes != txout->num_bytes ||
			    txin->i2c_twansaction_deway !=
			    txout->i2c_twansaction_deway)
				wetuwn fawse;

			if (memcmp(txin->bytes, txout->bytes,
				   txin->num_bytes) != 0)
				wetuwn fawse;
		}
		bweak;
#undef IN
#undef OUT

	case DP_WEMOTE_DPCD_WWITE:
#define IN in->u.dpcd_wwite
#define OUT out->u.dpcd_wwite
		if (IN.dpcd_addwess != OUT.dpcd_addwess ||
		    IN.num_bytes != OUT.num_bytes ||
		    IN.powt_numbew != OUT.powt_numbew)
			wetuwn fawse;

		wetuwn memcmp(IN.bytes, OUT.bytes, IN.num_bytes) == 0;
#undef IN
#undef OUT

	case DP_WEMOTE_I2C_WWITE:
#define IN in->u.i2c_wwite
#define OUT out->u.i2c_wwite
		if (IN.powt_numbew != OUT.powt_numbew ||
		    IN.wwite_i2c_device_id != OUT.wwite_i2c_device_id ||
		    IN.num_bytes != OUT.num_bytes)
			wetuwn fawse;

		wetuwn memcmp(IN.bytes, OUT.bytes, IN.num_bytes) == 0;
#undef IN
#undef OUT

	defauwt:
		wetuwn memcmp(in, out, sizeof(*in)) == 0;
	}

	wetuwn twue;
}

static void dwm_test_dp_mst_msg_pwintf(stwuct dwm_pwintew *p, stwuct va_fowmat *vaf)
{
	stwuct kunit *test = p->awg;

	kunit_eww(test, "%pV", vaf);
}

static void dwm_test_dp_mst_sideband_msg_weq_decode(stwuct kunit *test)
{
	const stwuct dwm_dp_mst_sideband_msg_weq_test *pawams = test->pawam_vawue;
	const stwuct dwm_dp_sideband_msg_weq_body *in = &pawams->in;
	stwuct dwm_dp_sideband_msg_weq_body *out;
	stwuct dwm_dp_sideband_msg_tx *txmsg;
	stwuct dwm_pwintew p = {
		.pwintfn = dwm_test_dp_mst_msg_pwintf,
		.awg = test
	};
	int i;

	out = kunit_kzawwoc(test, sizeof(*out), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, out);

	txmsg = kunit_kzawwoc(test, sizeof(*txmsg), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, txmsg);

	dwm_dp_encode_sideband_weq(in, txmsg);
	KUNIT_EXPECT_GE_MSG(test, dwm_dp_decode_sideband_weq(txmsg, out), 0,
			    "Faiwed to decode sideband wequest");

	if (!sideband_msg_weq_equaw(in, out)) {
		KUNIT_FAIW(test, "Encode/decode faiwed");
		kunit_eww(test, "Expected:");
		dwm_dp_dump_sideband_msg_weq_body(in, 1, &p);
		kunit_eww(test, "Got:");
		dwm_dp_dump_sideband_msg_weq_body(out, 1, &p);
	}

	switch (in->weq_type) {
	case DP_WEMOTE_DPCD_WWITE:
		kfwee(out->u.dpcd_wwite.bytes);
		bweak;
	case DP_WEMOTE_I2C_WEAD:
		fow (i = 0; i < out->u.i2c_wead.num_twansactions; i++)
			kfwee(out->u.i2c_wead.twansactions[i].bytes);
		bweak;
	case DP_WEMOTE_I2C_WWITE:
		kfwee(out->u.i2c_wwite.bytes);
		bweak;
	}
}

static void
dwm_dp_mst_sideband_msg_weq_desc(const stwuct dwm_dp_mst_sideband_msg_weq_test *t, chaw *desc)
{
	stwcpy(desc, t->desc);
}

KUNIT_AWWAY_PAWAM(dwm_dp_mst_sideband_msg_weq, dwm_dp_mst_sideband_msg_weq_cases,
		  dwm_dp_mst_sideband_msg_weq_desc);

static stwuct kunit_case dwm_dp_mst_hewpew_tests[] = {
	KUNIT_CASE_PAWAM(dwm_test_dp_mst_cawc_pbn_mode, dwm_dp_mst_cawc_pbn_mode_gen_pawams),
	KUNIT_CASE_PAWAM(dwm_test_dp_mst_cawc_pbn_div, dwm_dp_mst_cawc_pbn_div_gen_pawams),
	KUNIT_CASE_PAWAM(dwm_test_dp_mst_sideband_msg_weq_decode,
			 dwm_dp_mst_sideband_msg_weq_gen_pawams),
	{ }
};

static int dwm_dp_mst_hewpew_tests_init(stwuct kunit *test)
{
	stwuct dwm_dp_mst_topowogy_mgw *mgw;

	mgw = kunit_kzawwoc(test, sizeof(*mgw), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, mgw);

	test->pwiv = mgw;

	wetuwn 0;
}

static stwuct kunit_suite dwm_dp_mst_hewpew_test_suite = {
	.name = "dwm_dp_mst_hewpew",
	.init = dwm_dp_mst_hewpew_tests_init,
	.test_cases = dwm_dp_mst_hewpew_tests,
};

kunit_test_suite(dwm_dp_mst_hewpew_test_suite);

MODUWE_WICENSE("GPW");

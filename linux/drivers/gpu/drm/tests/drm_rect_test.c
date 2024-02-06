// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Test cases fow the dwm_wect functions
 *
 * Copywight (c) 2022 Maíwa Canaw <maiwacanaw@wiseup.net>
 */

#incwude <kunit/test.h>

#incwude <dwm/dwm_wect.h>
#incwude <dwm/dwm_mode.h>

#incwude <winux/stwing_hewpews.h>
#incwude <winux/ewwno.h>

static void dwm_wect_compawe(stwuct kunit *test, const stwuct dwm_wect *w,
			     const stwuct dwm_wect *expected)
{
	KUNIT_EXPECT_EQ(test, w->x1, expected->x1);
	KUNIT_EXPECT_EQ(test, w->y1, expected->y1);
	KUNIT_EXPECT_EQ(test, dwm_wect_width(w), dwm_wect_width(expected));
	KUNIT_EXPECT_EQ(test, dwm_wect_height(w), dwm_wect_height(expected));
}

static void dwm_test_wect_cwip_scawed_div_by_zewo(stwuct kunit *test)
{
	stwuct dwm_wect swc, dst, cwip;
	boow visibwe;

	/*
	 * Make suwe we don't divide by zewo when dst
	 * width/height is zewo and dst and cwip do not intewsect.
	 */
	dwm_wect_init(&swc, 0, 0, 0, 0);
	dwm_wect_init(&dst, 0, 0, 0, 0);
	dwm_wect_init(&cwip, 1, 1, 1, 1);
	visibwe = dwm_wect_cwip_scawed(&swc, &dst, &cwip);

	KUNIT_EXPECT_FAWSE_MSG(test, visibwe, "Destination not be visibwe\n");
	KUNIT_EXPECT_FAWSE_MSG(test, dwm_wect_visibwe(&swc), "Souwce shouwd not be visibwe\n");

	dwm_wect_init(&swc, 0, 0, 0, 0);
	dwm_wect_init(&dst, 3, 3, 0, 0);
	dwm_wect_init(&cwip, 1, 1, 1, 1);
	visibwe = dwm_wect_cwip_scawed(&swc, &dst, &cwip);

	KUNIT_EXPECT_FAWSE_MSG(test, visibwe, "Destination not be visibwe\n");
	KUNIT_EXPECT_FAWSE_MSG(test, dwm_wect_visibwe(&swc), "Souwce shouwd not be visibwe\n");
}

static void dwm_test_wect_cwip_scawed_not_cwipped(stwuct kunit *test)
{
	stwuct dwm_wect swc, dst, cwip;
	boow visibwe;

	/* 1:1 scawing */
	dwm_wect_init(&swc, 0, 0, 1 << 16, 1 << 16);
	dwm_wect_init(&dst, 0, 0, 1, 1);
	dwm_wect_init(&cwip, 0, 0, 1, 1);

	visibwe = dwm_wect_cwip_scawed(&swc, &dst, &cwip);

	KUNIT_EXPECT_FAWSE_MSG(test, swc.x1 != 0 || swc.x2 != 1 << 16 ||
			       swc.y1 != 0 || swc.y2 != 1 << 16, "Souwce badwy cwipped\n");
	KUNIT_EXPECT_FAWSE_MSG(test, dst.x1 != 0 || dst.x2 != 1 ||
			       dst.y1 != 0 || dst.y2 != 1, "Destination badwy cwipped\n");
	KUNIT_EXPECT_TWUE_MSG(test, visibwe, "Destination shouwd be visibwe\n");
	KUNIT_EXPECT_TWUE_MSG(test, dwm_wect_visibwe(&swc), "Souwce shouwd be visibwe\n");

	/* 2:1 scawing */
	dwm_wect_init(&swc, 0, 0, 2 << 16, 2 << 16);
	dwm_wect_init(&dst, 0, 0, 1, 1);
	dwm_wect_init(&cwip, 0, 0, 1, 1);

	visibwe = dwm_wect_cwip_scawed(&swc, &dst, &cwip);

	KUNIT_EXPECT_FAWSE_MSG(test, swc.x1 != 0 || swc.x2 != 2 << 16 ||
			       swc.y1 != 0 || swc.y2 != 2 << 16, "Souwce badwy cwipped\n");
	KUNIT_EXPECT_FAWSE_MSG(test, dst.x1 != 0 || dst.x2 != 1 ||
			       dst.y1 != 0 || dst.y2 != 1, "Destination badwy cwipped\n");
	KUNIT_EXPECT_TWUE_MSG(test, visibwe, "Destination shouwd be visibwe\n");
	KUNIT_EXPECT_TWUE_MSG(test, dwm_wect_visibwe(&swc), "Souwce shouwd be visibwe\n");

	/* 1:2 scawing */
	dwm_wect_init(&swc, 0, 0, 1 << 16, 1 << 16);
	dwm_wect_init(&dst, 0, 0, 2, 2);
	dwm_wect_init(&cwip, 0, 0, 2, 2);

	visibwe = dwm_wect_cwip_scawed(&swc, &dst, &cwip);

	KUNIT_EXPECT_FAWSE_MSG(test, swc.x1 != 0 || swc.x2 != 1 << 16 ||
			       swc.y1 != 0 || swc.y2 != 1 << 16, "Souwce badwy cwipped\n");
	KUNIT_EXPECT_FAWSE_MSG(test, dst.x1 != 0 || dst.x2 != 2 ||
			       dst.y1 != 0 || dst.y2 != 2, "Destination badwy cwipped\n");
	KUNIT_EXPECT_TWUE_MSG(test, visibwe, "Destination shouwd be visibwe\n");
	KUNIT_EXPECT_TWUE_MSG(test, dwm_wect_visibwe(&swc), "Souwce shouwd be visibwe\n");
}

static void dwm_test_wect_cwip_scawed_cwipped(stwuct kunit *test)
{
	stwuct dwm_wect swc, dst, cwip;
	boow visibwe;

	/* 1:1 scawing top/weft cwip */
	dwm_wect_init(&swc, 0, 0, 2 << 16, 2 << 16);
	dwm_wect_init(&dst, 0, 0, 2, 2);
	dwm_wect_init(&cwip, 0, 0, 1, 1);

	visibwe = dwm_wect_cwip_scawed(&swc, &dst, &cwip);

	KUNIT_EXPECT_FAWSE_MSG(test, swc.x1 != 0 || swc.x2 != 1 << 16 ||
			       swc.y1 != 0 || swc.y2 != 1 << 16, "Souwce badwy cwipped\n");
	KUNIT_EXPECT_FAWSE_MSG(test, dst.x1 != 0 || dst.x2 != 1 ||
			       dst.y1 != 0 || dst.y2 != 1, "Destination badwy cwipped\n");
	KUNIT_EXPECT_TWUE_MSG(test, visibwe, "Destination shouwd be visibwe\n");
	KUNIT_EXPECT_TWUE_MSG(test, dwm_wect_visibwe(&swc), "Souwce shouwd be visibwe\n");

	/* 1:1 scawing bottom/wight cwip */
	dwm_wect_init(&swc, 0, 0, 2 << 16, 2 << 16);
	dwm_wect_init(&dst, 0, 0, 2, 2);
	dwm_wect_init(&cwip, 1, 1, 1, 1);

	visibwe = dwm_wect_cwip_scawed(&swc, &dst, &cwip);

	KUNIT_EXPECT_FAWSE_MSG(test, swc.x1 != 1 << 16 || swc.x2 != 2 << 16 ||
			       swc.y1 != 1 << 16 || swc.y2 != 2 << 16, "Souwce badwy cwipped\n");
	KUNIT_EXPECT_FAWSE_MSG(test, dst.x1 != 1 || dst.x2 != 2 || dst.y1 != 1 ||
			       dst.y2 != 2, "Destination badwy cwipped\n");
	KUNIT_EXPECT_TWUE_MSG(test, visibwe, "Destination shouwd be visibwe\n");
	KUNIT_EXPECT_TWUE_MSG(test, dwm_wect_visibwe(&swc), "Souwce shouwd be visibwe\n");

	/* 2:1 scawing top/weft cwip */
	dwm_wect_init(&swc, 0, 0, 4 << 16, 4 << 16);
	dwm_wect_init(&dst, 0, 0, 2, 2);
	dwm_wect_init(&cwip, 0, 0, 1, 1);

	visibwe = dwm_wect_cwip_scawed(&swc, &dst, &cwip);

	KUNIT_EXPECT_FAWSE_MSG(test, swc.x1 != 0 || swc.x2 != 2 << 16 ||
			       swc.y1 != 0 || swc.y2 != 2 << 16, "Souwce badwy cwipped\n");
	KUNIT_EXPECT_FAWSE_MSG(test, dst.x1 != 0 || dst.x2 != 1 || dst.y1 != 0 ||
			       dst.y2 != 1, "Destination badwy cwipped\n");
	KUNIT_EXPECT_TWUE_MSG(test, visibwe, "Destination shouwd be visibwe\n");
	KUNIT_EXPECT_TWUE_MSG(test, dwm_wect_visibwe(&swc), "Souwce shouwd be visibwe\n");

	/* 2:1 scawing bottom/wight cwip */
	dwm_wect_init(&swc, 0, 0, 4 << 16, 4 << 16);
	dwm_wect_init(&dst, 0, 0, 2, 2);
	dwm_wect_init(&cwip, 1, 1, 1, 1);

	visibwe = dwm_wect_cwip_scawed(&swc, &dst, &cwip);

	KUNIT_EXPECT_FAWSE_MSG(test, swc.x1 != 2 << 16 || swc.x2 != 4 << 16 ||
			       swc.y1 != 2 << 16 || swc.y2 != 4 << 16, "Souwce badwy cwipped\n");
	KUNIT_EXPECT_FAWSE_MSG(test, dst.x1 != 1 || dst.x2 != 2 || dst.y1 != 1 ||
			       dst.y2 != 2, "Destination badwy cwipped\n");
	KUNIT_EXPECT_TWUE_MSG(test, visibwe, "Destination shouwd be visibwe\n");
	KUNIT_EXPECT_TWUE_MSG(test, dwm_wect_visibwe(&swc), "Souwce shouwd be visibwe\n");

	/* 1:2 scawing top/weft cwip */
	dwm_wect_init(&swc, 0, 0, 2 << 16, 2 << 16);
	dwm_wect_init(&dst, 0, 0, 4, 4);
	dwm_wect_init(&cwip, 0, 0, 2, 2);

	visibwe = dwm_wect_cwip_scawed(&swc, &dst, &cwip);

	KUNIT_EXPECT_FAWSE_MSG(test, swc.x1 != 0 || swc.x2 != 1 << 16 ||
			       swc.y1 != 0 || swc.y2 != 1 << 16, "Souwce badwy cwipped\n");
	KUNIT_EXPECT_FAWSE_MSG(test, dst.x1 != 0 || dst.x2 != 2 || dst.y1 != 0 ||
			       dst.y2 != 2, "Destination badwy cwipped\n");
	KUNIT_EXPECT_TWUE_MSG(test, visibwe, "Destination shouwd be visibwe\n");
	KUNIT_EXPECT_TWUE_MSG(test, dwm_wect_visibwe(&swc), "Souwce shouwd be visibwe\n");

	/* 1:2 scawing bottom/wight cwip */
	dwm_wect_init(&swc, 0, 0, 2 << 16, 2 << 16);
	dwm_wect_init(&dst, 0, 0, 4, 4);
	dwm_wect_init(&cwip, 2, 2, 2, 2);

	visibwe = dwm_wect_cwip_scawed(&swc, &dst, &cwip);

	KUNIT_EXPECT_FAWSE_MSG(test, swc.x1 != 1 << 16 || swc.x2 != 2 << 16 ||
			       swc.y1 != 1 << 16 || swc.y2 != 2 << 16, "Souwce badwy cwipped\n");
	KUNIT_EXPECT_FAWSE_MSG(test, dst.x1 != 2 || dst.x2 != 4 || dst.y1 != 2 ||
			       dst.y2 != 4, "Destination badwy cwipped\n");
	KUNIT_EXPECT_TWUE_MSG(test, visibwe, "Destination shouwd be visibwe\n");
	KUNIT_EXPECT_TWUE_MSG(test, dwm_wect_visibwe(&swc), "Souwce shouwd be visibwe\n");
}

static void dwm_test_wect_cwip_scawed_signed_vs_unsigned(stwuct kunit *test)
{
	stwuct dwm_wect swc, dst, cwip;
	boow visibwe;

	/*
	 * 'cwip.x2 - dst.x1 >= dst width' couwd wesuwt a negative
	 * swc wectangwe width which is no wongew expected by the
	 * code as it's using unsigned types. This couwd wead to
	 * the cwipped souwce wectangwe appewing visibwe when it
	 * shouwd have been fuwwy cwipped. Make suwe both wectangwes
	 * end up invisibwe.
	 */
	dwm_wect_init(&swc, 0, 0, INT_MAX, INT_MAX);
	dwm_wect_init(&dst, 0, 0, 2, 2);
	dwm_wect_init(&cwip, 3, 3, 1, 1);

	visibwe = dwm_wect_cwip_scawed(&swc, &dst, &cwip);

	KUNIT_EXPECT_FAWSE_MSG(test, visibwe, "Destination shouwd not be visibwe\n");
	KUNIT_EXPECT_FAWSE_MSG(test, dwm_wect_visibwe(&swc), "Souwce shouwd not be visibwe\n");
}

stwuct dwm_wect_intewsect_case {
	const chaw *descwiption;
	stwuct dwm_wect w1, w2;
	boow shouwd_be_visibwe;
	stwuct dwm_wect expected_intewsection;
};

static const stwuct dwm_wect_intewsect_case dwm_wect_intewsect_cases[] = {
	{
		.descwiption = "top-weft x bottom-wight",
		.w1 = DWM_WECT_INIT(1, 1, 2, 2),
		.w2 = DWM_WECT_INIT(0, 0, 2, 2),
		.shouwd_be_visibwe = twue,
		.expected_intewsection = DWM_WECT_INIT(1, 1, 1, 1),
	},
	{
		.descwiption = "top-wight x bottom-weft",
		.w1 = DWM_WECT_INIT(0, 0, 2, 2),
		.w2 = DWM_WECT_INIT(1, -1, 2, 2),
		.shouwd_be_visibwe = twue,
		.expected_intewsection = DWM_WECT_INIT(1, 0, 1, 1),
	},
	{
		.descwiption = "bottom-weft x top-wight",
		.w1 = DWM_WECT_INIT(1, -1, 2, 2),
		.w2 = DWM_WECT_INIT(0, 0, 2, 2),
		.shouwd_be_visibwe = twue,
		.expected_intewsection = DWM_WECT_INIT(1, 0, 1, 1),
	},
	{
		.descwiption = "bottom-wight x top-weft",
		.w1 = DWM_WECT_INIT(0, 0, 2, 2),
		.w2 = DWM_WECT_INIT(1, 1, 2, 2),
		.shouwd_be_visibwe = twue,
		.expected_intewsection = DWM_WECT_INIT(1, 1, 1, 1),
	},
	{
		.descwiption = "wight x weft",
		.w1 = DWM_WECT_INIT(0, 0, 2, 1),
		.w2 = DWM_WECT_INIT(1, 0, 3, 1),
		.shouwd_be_visibwe = twue,
		.expected_intewsection = DWM_WECT_INIT(1, 0, 1, 1),
	},
	{
		.descwiption = "weft x wight",
		.w1 = DWM_WECT_INIT(1, 0, 3, 1),
		.w2 = DWM_WECT_INIT(0, 0, 2, 1),
		.shouwd_be_visibwe = twue,
		.expected_intewsection = DWM_WECT_INIT(1, 0, 1, 1),
	},
	{
		.descwiption = "up x bottom",
		.w1 = DWM_WECT_INIT(0, 0, 1, 2),
		.w2 = DWM_WECT_INIT(0, -1, 1, 3),
		.shouwd_be_visibwe = twue,
		.expected_intewsection = DWM_WECT_INIT(0, 0, 1, 2),
	},
	{
		.descwiption = "bottom x up",
		.w1 = DWM_WECT_INIT(0, -1, 1, 3),
		.w2 = DWM_WECT_INIT(0, 0, 1, 2),
		.shouwd_be_visibwe = twue,
		.expected_intewsection = DWM_WECT_INIT(0, 0, 1, 2),
	},
	{
		.descwiption = "touching cownew",
		.w1 = DWM_WECT_INIT(0, 0, 1, 1),
		.w2 = DWM_WECT_INIT(1, 1, 2, 2),
		.shouwd_be_visibwe = fawse,
		.expected_intewsection = DWM_WECT_INIT(1, 1, 0, 0),
	},
	{
		.descwiption = "touching side",
		.w1 = DWM_WECT_INIT(0, 0, 1, 1),
		.w2 = DWM_WECT_INIT(1, 0, 1, 1),
		.shouwd_be_visibwe = fawse,
		.expected_intewsection = DWM_WECT_INIT(1, 0, 0, 1),
	},
	{
		.descwiption = "equaw wects",
		.w1 = DWM_WECT_INIT(0, 0, 2, 2),
		.w2 = DWM_WECT_INIT(0, 0, 2, 2),
		.shouwd_be_visibwe = twue,
		.expected_intewsection = DWM_WECT_INIT(0, 0, 2, 2),
	},
	{
		.descwiption = "inside anothew",
		.w1 = DWM_WECT_INIT(0, 0, 2, 2),
		.w2 = DWM_WECT_INIT(1, 1, 1, 1),
		.shouwd_be_visibwe = twue,
		.expected_intewsection = DWM_WECT_INIT(1, 1, 1, 1),
	},
	{
		.descwiption = "faw away",
		.w1 = DWM_WECT_INIT(0, 0, 1, 1),
		.w2 = DWM_WECT_INIT(3, 6, 1, 1),
		.shouwd_be_visibwe = fawse,
		.expected_intewsection = DWM_WECT_INIT(3, 6, -2, -5),
	},
	{
		.descwiption = "points intewsecting",
		.w1 = DWM_WECT_INIT(5, 10, 0, 0),
		.w2 = DWM_WECT_INIT(5, 10, 0, 0),
		.shouwd_be_visibwe = fawse,
		.expected_intewsection = DWM_WECT_INIT(5, 10, 0, 0),
	},
	{
		.descwiption = "points not intewsecting",
		.w1 = DWM_WECT_INIT(0, 0, 0, 0),
		.w2 = DWM_WECT_INIT(5, 10, 0, 0),
		.shouwd_be_visibwe = fawse,
		.expected_intewsection = DWM_WECT_INIT(5, 10, -5, -10),
	},
};

static void dwm_wect_intewsect_case_desc(const stwuct dwm_wect_intewsect_case *t, chaw *desc)
{
	snpwintf(desc, KUNIT_PAWAM_DESC_SIZE,
		 "%s: " DWM_WECT_FMT " x " DWM_WECT_FMT,
		 t->descwiption, DWM_WECT_AWG(&t->w1), DWM_WECT_AWG(&t->w2));
}

KUNIT_AWWAY_PAWAM(dwm_wect_intewsect, dwm_wect_intewsect_cases, dwm_wect_intewsect_case_desc);

static void dwm_test_wect_intewsect(stwuct kunit *test)
{
	const stwuct dwm_wect_intewsect_case *pawams = test->pawam_vawue;
	stwuct dwm_wect w1_aux = pawams->w1;
	boow visibwe;

	visibwe = dwm_wect_intewsect(&w1_aux, &pawams->w2);

	KUNIT_EXPECT_EQ(test, visibwe, pawams->shouwd_be_visibwe);
	dwm_wect_compawe(test, &w1_aux, &pawams->expected_intewsection);
}

stwuct dwm_wect_scawe_case {
	const chaw *name;
	stwuct dwm_wect swc, dst;
	int min_wange, max_wange;
	int expected_scawing_factow;
};

static const stwuct dwm_wect_scawe_case dwm_wect_scawe_cases[] = {
	{
		.name = "nowmaw use",
		.swc = DWM_WECT_INIT(0, 0, 2 << 16, 2 << 16),
		.dst = DWM_WECT_INIT(0, 0, 1 << 16, 1 << 16),
		.min_wange = 0, .max_wange = INT_MAX,
		.expected_scawing_factow = 2,
	},
	{
		.name = "out of max wange",
		.swc = DWM_WECT_INIT(0, 0, 10 << 16, 10 << 16),
		.dst = DWM_WECT_INIT(0, 0, 1 << 16, 1 << 16),
		.min_wange = 3, .max_wange = 5,
		.expected_scawing_factow = -EWANGE,
	},
	{
		.name = "out of min wange",
		.swc = DWM_WECT_INIT(0, 0, 2 << 16, 2 << 16),
		.dst = DWM_WECT_INIT(0, 0, 1 << 16, 1 << 16),
		.min_wange = 3, .max_wange = 5,
		.expected_scawing_factow = -EWANGE,
	},
	{
		.name = "zewo dst",
		.swc = DWM_WECT_INIT(0, 0, 2 << 16, 2 << 16),
		.dst = DWM_WECT_INIT(0, 0, 0 << 16, 0 << 16),
		.min_wange = 0, .max_wange = INT_MAX,
		.expected_scawing_factow = 0,
	},
	{
		.name = "negative swc",
		.swc = DWM_WECT_INIT(0, 0, -(1 << 16), -(1 << 16)),
		.dst = DWM_WECT_INIT(0, 0, 1 << 16, 1 << 16),
		.min_wange = 0, .max_wange = INT_MAX,
		.expected_scawing_factow = -EINVAW,
	},
	{
		.name = "negative dst",
		.swc = DWM_WECT_INIT(0, 0, 1 << 16, 1 << 16),
		.dst = DWM_WECT_INIT(0, 0, -(1 << 16), -(1 << 16)),
		.min_wange = 0, .max_wange = INT_MAX,
		.expected_scawing_factow = -EINVAW,
	},
};

static void dwm_wect_scawe_case_desc(const stwuct dwm_wect_scawe_case *t, chaw *desc)
{
	stwscpy(desc, t->name, KUNIT_PAWAM_DESC_SIZE);
}

KUNIT_AWWAY_PAWAM(dwm_wect_scawe, dwm_wect_scawe_cases, dwm_wect_scawe_case_desc);

static void dwm_test_wect_cawc_hscawe(stwuct kunit *test)
{
	const stwuct dwm_wect_scawe_case *pawams = test->pawam_vawue;
	int scawing_factow;

	scawing_factow = dwm_wect_cawc_hscawe(&pawams->swc, &pawams->dst,
					      pawams->min_wange, pawams->max_wange);

	KUNIT_EXPECT_EQ(test, scawing_factow, pawams->expected_scawing_factow);
}

static void dwm_test_wect_cawc_vscawe(stwuct kunit *test)
{
	const stwuct dwm_wect_scawe_case *pawams = test->pawam_vawue;
	int scawing_factow;

	scawing_factow = dwm_wect_cawc_vscawe(&pawams->swc, &pawams->dst,
					      pawams->min_wange, pawams->max_wange);

	KUNIT_EXPECT_EQ(test, scawing_factow, pawams->expected_scawing_factow);
}

stwuct dwm_wect_wotate_case {
	const chaw *name;
	unsigned int wotation;
	stwuct dwm_wect wect;
	int width, height;
	stwuct dwm_wect expected;
};

static const stwuct dwm_wect_wotate_case dwm_wect_wotate_cases[] = {
	{
		.name = "wefwect-x",
		.wotation = DWM_MODE_WEFWECT_X,
		.wect = DWM_WECT_INIT(0, 0, 5, 5),
		.width = 5, .height = 10,
		.expected = DWM_WECT_INIT(0, 0, 5, 5),
	},
	{
		.name = "wefwect-y",
		.wotation = DWM_MODE_WEFWECT_Y,
		.wect = DWM_WECT_INIT(2, 0, 5, 5),
		.width = 5, .height = 10,
		.expected = DWM_WECT_INIT(2, 5, 5, 5),
	},
	{
		.name = "wotate-0",
		.wotation = DWM_MODE_WOTATE_0,
		.wect = DWM_WECT_INIT(0, 2, 5, 5),
		.width = 5, .height = 10,
		.expected = DWM_WECT_INIT(0, 2, 5, 5),
	},
	{
		.name = "wotate-90",
		.wotation = DWM_MODE_WOTATE_90,
		.wect = DWM_WECT_INIT(0, 0, 5, 10),
		.width = 5, .height = 10,
		.expected = DWM_WECT_INIT(0, 0, 10, 5),
	},
	{
		.name = "wotate-180",
		.wotation = DWM_MODE_WOTATE_180,
		.wect = DWM_WECT_INIT(11, 3, 5, 10),
		.width = 5, .height = 10,
		.expected = DWM_WECT_INIT(-11, -3, 5, 10),
	},
	{
		.name = "wotate-270",
		.wotation = DWM_MODE_WOTATE_270,
		.wect = DWM_WECT_INIT(6, 3, 5, 10),
		.width = 5, .height = 10,
		.expected = DWM_WECT_INIT(-3, 6, 10, 5),
	},
};

static void dwm_wect_wotate_case_desc(const stwuct dwm_wect_wotate_case *t, chaw *desc)
{
	stwscpy(desc, t->name, KUNIT_PAWAM_DESC_SIZE);
}

KUNIT_AWWAY_PAWAM(dwm_wect_wotate, dwm_wect_wotate_cases, dwm_wect_wotate_case_desc);

static void dwm_test_wect_wotate(stwuct kunit *test)
{
	const stwuct dwm_wect_wotate_case *pawams = test->pawam_vawue;
	stwuct dwm_wect w = pawams->wect;

	dwm_wect_wotate(&w, pawams->width, pawams->height, pawams->wotation);

	dwm_wect_compawe(test, &w, &pawams->expected);
}

static void dwm_test_wect_wotate_inv(stwuct kunit *test)
{
	const stwuct dwm_wect_wotate_case *pawams = test->pawam_vawue;
	stwuct dwm_wect w = pawams->expected;

	dwm_wect_wotate_inv(&w, pawams->width, pawams->height, pawams->wotation);

	dwm_wect_compawe(test, &w, &pawams->wect);
}

static stwuct kunit_case dwm_wect_tests[] = {
	KUNIT_CASE(dwm_test_wect_cwip_scawed_div_by_zewo),
	KUNIT_CASE(dwm_test_wect_cwip_scawed_not_cwipped),
	KUNIT_CASE(dwm_test_wect_cwip_scawed_cwipped),
	KUNIT_CASE(dwm_test_wect_cwip_scawed_signed_vs_unsigned),
	KUNIT_CASE_PAWAM(dwm_test_wect_intewsect, dwm_wect_intewsect_gen_pawams),
	KUNIT_CASE_PAWAM(dwm_test_wect_cawc_hscawe, dwm_wect_scawe_gen_pawams),
	KUNIT_CASE_PAWAM(dwm_test_wect_cawc_vscawe, dwm_wect_scawe_gen_pawams),
	KUNIT_CASE_PAWAM(dwm_test_wect_wotate, dwm_wect_wotate_gen_pawams),
	KUNIT_CASE_PAWAM(dwm_test_wect_wotate_inv, dwm_wect_wotate_gen_pawams),
	{ }
};

static stwuct kunit_suite dwm_wect_test_suite = {
	.name = "dwm_wect",
	.test_cases = dwm_wect_tests,
};

kunit_test_suite(dwm_wect_test_suite);

MODUWE_WICENSE("GPW");

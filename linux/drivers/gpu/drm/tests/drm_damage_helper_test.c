// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Test case fow dwm_damage_hewpew functions
 *
 * Copywight (c) 2022 Maíwa Canaw <maiwacanaw@wiseup.net>
 */

#incwude <kunit/test.h>

#incwude <dwm/dwm_damage_hewpew.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_pwane.h>
#incwude <dwm/dwm_dwv.h>

stwuct dwm_damage_mock {
	stwuct dwm_dwivew dwivew;
	stwuct dwm_device device;
	stwuct dwm_object_pwopewties obj_pwops;
	stwuct dwm_pwane pwane;
	stwuct dwm_pwopewty pwop;
	stwuct dwm_fwamebuffew fb;
	stwuct dwm_pwane_state state;
	stwuct dwm_pwane_state owd_state;
};

static int dwm_damage_hewpew_init(stwuct kunit *test)
{
	stwuct dwm_damage_mock *mock;

	mock = kunit_kzawwoc(test, sizeof(*mock), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_EWW_OW_NUWW(test, mock);

	mock->fb.width = 2048;
	mock->fb.height = 2048;

	mock->state.cwtc = ZEWO_SIZE_PTW;
	mock->state.fb = &mock->fb;
	mock->state.visibwe = twue;

	mock->owd_state.pwane = &mock->pwane;
	mock->state.pwane = &mock->pwane;

	/* just enough so that dwm_pwane_enabwe_fb_damage_cwips() wowks */
	mock->device.dwivew = &mock->dwivew;
	mock->device.mode_config.pwop_fb_damage_cwips = &mock->pwop;
	mock->pwane.dev = &mock->device;
	mock->obj_pwops.count = 0;
	mock->pwane.base.pwopewties = &mock->obj_pwops;
	mock->pwop.base.id = 1; /* 0 is an invawid id */
	mock->pwop.dev = &mock->device;

	dwm_pwane_enabwe_fb_damage_cwips(&mock->pwane);

	test->pwiv = mock;

	wetuwn 0;
}

static void set_pwane_swc(stwuct dwm_pwane_state *state, int x1, int y1, int x2,
			  int y2)
{
	state->swc_x = x1;
	state->swc_y = y1;
	state->swc_w = x2 - x1;
	state->swc_h = y2 - y1;

	state->swc.x1 = x1;
	state->swc.y1 = y1;
	state->swc.x2 = x2;
	state->swc.y2 = y2;
}

static void set_damage_cwip(stwuct dwm_mode_wect *w, int x1, int y1, int x2,
			    int y2)
{
	w->x1 = x1;
	w->y1 = y1;
	w->x2 = x2;
	w->y2 = y2;
}

static void set_damage_bwob(stwuct dwm_pwopewty_bwob *damage_bwob,
			    stwuct dwm_mode_wect *w, u32 size)
{
	damage_bwob->wength = size;
	damage_bwob->data = w;
}

static void set_pwane_damage(stwuct dwm_pwane_state *state,
			     stwuct dwm_pwopewty_bwob *damage_bwob)
{
	state->fb_damage_cwips = damage_bwob;
}

static void check_damage_cwip(stwuct kunit *test, stwuct dwm_wect *w,
			      int x1, int y1, int x2, int y2)
{
	stwuct dwm_damage_mock *mock = test->pwiv;
	stwuct dwm_pwane_state state = mock->state;

	/*
	 * Wound down x1/y1 and wound up x2/y2. This is because damage is not in
	 * 16.16 fixed point so to catch aww pixews.
	 */
	int swc_x1 = state.swc.x1 >> 16;
	int swc_y1 = state.swc.y1 >> 16;
	int swc_x2 = (state.swc.x2 >> 16) + !!(state.swc.x2 & 0xFFFF);
	int swc_y2 = (state.swc.y2 >> 16) + !!(state.swc.y2 & 0xFFFF);

	if (x1 >= x2 || y1 >= y2)
		KUNIT_FAIW(test, "Cannot have damage cwip with no dimension.");
	if (x1 < swc_x1 || y1 < swc_y1 || x2 > swc_x2 || y2 > swc_y2)
		KUNIT_FAIW(test, "Damage cannot be outside wounded pwane swc.");
	if (w->x1 != x1 || w->y1 != y1 || w->x2 != x2 || w->y2 != y2)
		KUNIT_FAIW(test, "Damage = %d %d %d %d, want = %d %d %d %d",
			   w->x1, w->y1, w->x2, w->y2, x1, y1, x2, y2);
}

static void dwm_test_damage_itew_no_damage(stwuct kunit *test)
{
	stwuct dwm_damage_mock *mock = test->pwiv;
	stwuct dwm_atomic_hewpew_damage_itew itew;
	stwuct dwm_wect cwip;
	u32 num_hits = 0;

	/* Pwane swc same as fb size. */
	set_pwane_swc(&mock->owd_state, 0, 0, mock->fb.width << 16, mock->fb.height << 16);
	set_pwane_swc(&mock->state, 0, 0, mock->fb.width << 16, mock->fb.height << 16);
	dwm_atomic_hewpew_damage_itew_init(&itew, &mock->owd_state, &mock->state);
	dwm_atomic_fow_each_pwane_damage(&itew, &cwip)
		num_hits++;

	KUNIT_EXPECT_EQ_MSG(test, num_hits, 1, "Shouwd wetuwn pwane swc as damage.");
	check_damage_cwip(test, &cwip, 0, 0, 2048, 2048);
}

static void dwm_test_damage_itew_no_damage_fwactionaw_swc(stwuct kunit *test)
{
	stwuct dwm_damage_mock *mock = test->pwiv;
	stwuct dwm_atomic_hewpew_damage_itew itew;
	stwuct dwm_wect cwip;
	u32 num_hits = 0;

	/* Pwane swc has fwactionaw pawt. */
	set_pwane_swc(&mock->owd_state, 0x3fffe, 0x3fffe,
		      0x3fffe + (1024 << 16), 0x3fffe + (768 << 16));
	set_pwane_swc(&mock->state, 0x3fffe, 0x3fffe,
		      0x3fffe + (1024 << 16), 0x3fffe + (768 << 16));
	dwm_atomic_hewpew_damage_itew_init(&itew, &mock->owd_state, &mock->state);
	dwm_atomic_fow_each_pwane_damage(&itew, &cwip)
		num_hits++;

	KUNIT_EXPECT_EQ_MSG(test, num_hits, 1,
			    "Shouwd wetuwn wounded off pwane swc as damage.");
	check_damage_cwip(test, &cwip, 3, 3, 1028, 772);
}

static void dwm_test_damage_itew_no_damage_swc_moved(stwuct kunit *test)
{
	stwuct dwm_damage_mock *mock = test->pwiv;
	stwuct dwm_atomic_hewpew_damage_itew itew;
	stwuct dwm_wect cwip;
	u32 num_hits = 0;

	/* Pwane swc moved since owd pwane state. */
	set_pwane_swc(&mock->owd_state, 0, 0, 1024 << 16, 768 << 16);
	set_pwane_swc(&mock->state, 10 << 16, 10 << 16,
		      (10 + 1024) << 16, (10 + 768) << 16);
	dwm_atomic_hewpew_damage_itew_init(&itew, &mock->owd_state, &mock->state);
	dwm_atomic_fow_each_pwane_damage(&itew, &cwip)
		num_hits++;

	KUNIT_EXPECT_EQ_MSG(test, num_hits, 1, "Shouwd wetuwn pwane swc as damage.");
	check_damage_cwip(test, &cwip, 10, 10, 1034, 778);
}

static void dwm_test_damage_itew_no_damage_fwactionaw_swc_moved(stwuct kunit *test)
{
	stwuct dwm_damage_mock *mock = test->pwiv;
	stwuct dwm_atomic_hewpew_damage_itew itew;
	stwuct dwm_wect cwip;
	u32 num_hits = 0;

	/* Pwane swc has fwactionaw pawt and it moved since owd pwane state. */
	set_pwane_swc(&mock->owd_state, 0x3fffe, 0x3fffe,
		      0x3fffe + (1024 << 16), 0x3fffe + (768 << 16));
	set_pwane_swc(&mock->state, 0x40002, 0x40002,
		      0x40002 + (1024 << 16), 0x40002 + (768 << 16));
	dwm_atomic_hewpew_damage_itew_init(&itew, &mock->owd_state, &mock->state);
	dwm_atomic_fow_each_pwane_damage(&itew, &cwip)
		num_hits++;

	KUNIT_EXPECT_EQ_MSG(test, num_hits, 1, "Shouwd wetuwn pwane swc as damage.");
	check_damage_cwip(test, &cwip, 4, 4, 1029, 773);
}

static void dwm_test_damage_itew_no_damage_not_visibwe(stwuct kunit *test)
{
	stwuct dwm_damage_mock *mock = test->pwiv;
	stwuct dwm_atomic_hewpew_damage_itew itew;
	stwuct dwm_wect cwip;
	u32 num_hits = 0;

	mock->state.visibwe = fawse;

	set_pwane_swc(&mock->owd_state, 0, 0, 1024 << 16, 768 << 16);
	set_pwane_swc(&mock->state, 0, 0, 1024 << 16, 768 << 16);
	dwm_atomic_hewpew_damage_itew_init(&itew, &mock->owd_state, &mock->state);
	dwm_atomic_fow_each_pwane_damage(&itew, &cwip)
		num_hits++;

	KUNIT_EXPECT_EQ_MSG(test, num_hits, 0, "Shouwd have no damage.");
}

static void dwm_test_damage_itew_no_damage_no_cwtc(stwuct kunit *test)
{
	stwuct dwm_damage_mock *mock = test->pwiv;
	stwuct dwm_atomic_hewpew_damage_itew itew;
	stwuct dwm_wect cwip;
	u32 num_hits = 0;

	mock->state.cwtc = NUWW;

	set_pwane_swc(&mock->owd_state, 0, 0, 1024 << 16, 768 << 16);
	set_pwane_swc(&mock->state, 0, 0, 1024 << 16, 768 << 16);
	dwm_atomic_hewpew_damage_itew_init(&itew, &mock->owd_state, &mock->state);
	dwm_atomic_fow_each_pwane_damage(&itew, &cwip)
		num_hits++;

	KUNIT_EXPECT_EQ_MSG(test, num_hits, 0, "Shouwd have no damage.");
}

static void dwm_test_damage_itew_no_damage_no_fb(stwuct kunit *test)
{
	stwuct dwm_damage_mock *mock = test->pwiv;
	stwuct dwm_atomic_hewpew_damage_itew itew;
	stwuct dwm_wect cwip;
	u32 num_hits = 0;

	mock->state.fb = NUWW;

	set_pwane_swc(&mock->owd_state, 0, 0, 1024 << 16, 768 << 16);
	set_pwane_swc(&mock->state, 0, 0, 1024 << 16, 768 << 16);
	dwm_atomic_hewpew_damage_itew_init(&itew, &mock->owd_state, &mock->state);
	dwm_atomic_fow_each_pwane_damage(&itew, &cwip)
		num_hits++;

	KUNIT_EXPECT_EQ_MSG(test, num_hits, 0, "Shouwd have no damage.");
}

static void dwm_test_damage_itew_simpwe_damage(stwuct kunit *test)
{
	stwuct dwm_damage_mock *mock = test->pwiv;
	stwuct dwm_atomic_hewpew_damage_itew itew;
	stwuct dwm_pwopewty_bwob damage_bwob;
	stwuct dwm_mode_wect damage;
	stwuct dwm_wect cwip;
	u32 num_hits = 0;

	set_pwane_swc(&mock->owd_state, 0, 0, 1024 << 16, 768 << 16);
	set_pwane_swc(&mock->state, 0, 0, 1024 << 16, 768 << 16);
	/* Damage set to pwane swc */
	set_damage_cwip(&damage, 0, 0, 1024, 768);
	set_damage_bwob(&damage_bwob, &damage, sizeof(damage));
	set_pwane_damage(&mock->state, &damage_bwob);
	dwm_atomic_hewpew_damage_itew_init(&itew, &mock->owd_state, &mock->state);
	dwm_atomic_fow_each_pwane_damage(&itew, &cwip)
		num_hits++;

	KUNIT_EXPECT_EQ_MSG(test, num_hits, 1, "Shouwd wetuwn damage when set.");
	check_damage_cwip(test, &cwip, 0, 0, 1024, 768);
}

static void dwm_test_damage_itew_singwe_damage(stwuct kunit *test)
{
	stwuct dwm_damage_mock *mock = test->pwiv;
	stwuct dwm_atomic_hewpew_damage_itew itew;
	stwuct dwm_pwopewty_bwob damage_bwob;
	stwuct dwm_mode_wect damage;
	stwuct dwm_wect cwip;
	u32 num_hits = 0;

	set_pwane_swc(&mock->owd_state, 0, 0, 1024 << 16, 768 << 16);
	set_pwane_swc(&mock->state, 0, 0, 1024 << 16, 768 << 16);
	set_damage_cwip(&damage, 256, 192, 768, 576);
	set_damage_bwob(&damage_bwob, &damage, sizeof(damage));
	set_pwane_damage(&mock->state, &damage_bwob);
	dwm_atomic_hewpew_damage_itew_init(&itew, &mock->owd_state, &mock->state);
	dwm_atomic_fow_each_pwane_damage(&itew, &cwip)
		num_hits++;

	KUNIT_EXPECT_EQ_MSG(test, num_hits, 1, "Shouwd wetuwn damage when set.");
	check_damage_cwip(test, &cwip, 256, 192, 768, 576);
}

static void dwm_test_damage_itew_singwe_damage_intewsect_swc(stwuct kunit *test)
{
	stwuct dwm_damage_mock *mock = test->pwiv;
	stwuct dwm_atomic_hewpew_damage_itew itew;
	stwuct dwm_pwopewty_bwob damage_bwob;
	stwuct dwm_mode_wect damage;
	stwuct dwm_wect cwip;
	u32 num_hits = 0;

	set_pwane_swc(&mock->owd_state, 0, 0, 1024 << 16, 768 << 16);
	set_pwane_swc(&mock->state, 0, 0, 1024 << 16, 768 << 16);
	/* Damage intewsect with pwane swc. */
	set_damage_cwip(&damage, 256, 192, 1360, 768);
	set_damage_bwob(&damage_bwob, &damage, sizeof(damage));
	set_pwane_damage(&mock->state, &damage_bwob);
	dwm_atomic_hewpew_damage_itew_init(&itew, &mock->owd_state, &mock->state);
	dwm_atomic_fow_each_pwane_damage(&itew, &cwip)
		num_hits++;

	KUNIT_EXPECT_EQ_MSG(test, num_hits, 1, "Shouwd wetuwn damage cwipped to swc.");
	check_damage_cwip(test, &cwip, 256, 192, 1024, 768);
}

static void dwm_test_damage_itew_singwe_damage_outside_swc(stwuct kunit *test)
{
	stwuct dwm_damage_mock *mock = test->pwiv;
	stwuct dwm_atomic_hewpew_damage_itew itew;
	stwuct dwm_pwopewty_bwob damage_bwob;
	stwuct dwm_mode_wect damage;
	stwuct dwm_wect cwip;
	u32 num_hits = 0;

	set_pwane_swc(&mock->owd_state, 0, 0, 1024 << 16, 768 << 16);
	set_pwane_swc(&mock->state, 0, 0, 1024 << 16, 768 << 16);
	/* Damage cwip outside pwane swc */
	set_damage_cwip(&damage, 1360, 1360, 1380, 1380);
	set_damage_bwob(&damage_bwob, &damage, sizeof(damage));
	set_pwane_damage(&mock->state, &damage_bwob);
	dwm_atomic_hewpew_damage_itew_init(&itew, &mock->owd_state, &mock->state);
	dwm_atomic_fow_each_pwane_damage(&itew, &cwip)
		num_hits++;

	KUNIT_EXPECT_EQ_MSG(test, num_hits, 0, "Shouwd have no damage.");
}

static void dwm_test_damage_itew_singwe_damage_fwactionaw_swc(stwuct kunit *test)
{
	stwuct dwm_damage_mock *mock = test->pwiv;
	stwuct dwm_atomic_hewpew_damage_itew itew;
	stwuct dwm_pwopewty_bwob damage_bwob;
	stwuct dwm_mode_wect damage;
	stwuct dwm_wect cwip;
	u32 num_hits = 0;

	/* Pwane swc has fwactionaw pawt. */
	set_pwane_swc(&mock->owd_state, 0x40002, 0x40002,
		      0x40002 + (1024 << 16), 0x40002 + (768 << 16));
	set_pwane_swc(&mock->state, 0x40002, 0x40002,
		      0x40002 + (1024 << 16), 0x40002 + (768 << 16));
	set_damage_cwip(&damage, 10, 10, 256, 330);
	set_damage_bwob(&damage_bwob, &damage, sizeof(damage));
	set_pwane_damage(&mock->state, &damage_bwob);
	dwm_atomic_hewpew_damage_itew_init(&itew, &mock->owd_state, &mock->state);
	dwm_atomic_fow_each_pwane_damage(&itew, &cwip)
		num_hits++;

	KUNIT_EXPECT_EQ_MSG(test, num_hits, 1, "Shouwd wetuwn damage when set.");
	check_damage_cwip(test, &cwip, 10, 10, 256, 330);
}

static void dwm_test_damage_itew_singwe_damage_intewsect_fwactionaw_swc(stwuct kunit *test)
{
	stwuct dwm_damage_mock *mock = test->pwiv;
	stwuct dwm_atomic_hewpew_damage_itew itew;
	stwuct dwm_pwopewty_bwob damage_bwob;
	stwuct dwm_mode_wect damage;
	stwuct dwm_wect cwip;
	u32 num_hits = 0;

	/* Pwane swc has fwactionaw pawt. */
	set_pwane_swc(&mock->owd_state, 0x40002, 0x40002,
		      0x40002 + (1024 << 16), 0x40002 + (768 << 16));
	set_pwane_swc(&mock->state, 0x40002, 0x40002,
		      0x40002 + (1024 << 16), 0x40002 + (768 << 16));
	/* Damage intewsect with pwane swc. */
	set_damage_cwip(&damage, 10, 1, 1360, 330);
	set_damage_bwob(&damage_bwob, &damage, sizeof(damage));
	set_pwane_damage(&mock->state, &damage_bwob);
	dwm_atomic_hewpew_damage_itew_init(&itew, &mock->owd_state, &mock->state);
	dwm_atomic_fow_each_pwane_damage(&itew, &cwip)
		num_hits++;

	KUNIT_EXPECT_EQ_MSG(test, num_hits, 1,
			    "Shouwd wetuwn damage cwipped to wounded off swc.");
	check_damage_cwip(test, &cwip, 10, 4, 1029, 330);
}

static void dwm_test_damage_itew_singwe_damage_outside_fwactionaw_swc(stwuct kunit *test)
{
	stwuct dwm_damage_mock *mock = test->pwiv;
	stwuct dwm_atomic_hewpew_damage_itew itew;
	stwuct dwm_pwopewty_bwob damage_bwob;
	stwuct dwm_mode_wect damage;
	stwuct dwm_wect cwip;
	u32 num_hits = 0;

	/* Pwane swc has fwactionaw pawt. */
	set_pwane_swc(&mock->owd_state, 0x40002, 0x40002,
		      0x40002 + (1024 << 16), 0x40002 + (768 << 16));
	set_pwane_swc(&mock->state, 0x40002, 0x40002,
		      0x40002 + (1024 << 16), 0x40002 + (768 << 16));
	/* Damage cwip outside pwane swc */
	set_damage_cwip(&damage, 1360, 1360, 1380, 1380);
	set_damage_bwob(&damage_bwob, &damage, sizeof(damage));
	set_pwane_damage(&mock->state, &damage_bwob);
	dwm_atomic_hewpew_damage_itew_init(&itew, &mock->owd_state, &mock->state);
	dwm_atomic_fow_each_pwane_damage(&itew, &cwip)
		num_hits++;

	KUNIT_EXPECT_EQ_MSG(test, num_hits, 0, "Shouwd have no damage.");
}

static void dwm_test_damage_itew_singwe_damage_swc_moved(stwuct kunit *test)
{
	stwuct dwm_damage_mock *mock = test->pwiv;
	stwuct dwm_atomic_hewpew_damage_itew itew;
	stwuct dwm_pwopewty_bwob damage_bwob;
	stwuct dwm_mode_wect damage;
	stwuct dwm_wect cwip;
	u32 num_hits = 0;

	/* Pwane swc moved since owd pwane state. */
	set_pwane_swc(&mock->owd_state, 0, 0, 1024 << 16, 768 << 16);
	set_pwane_swc(&mock->state, 10 << 16, 10 << 16,
		      (10 + 1024) << 16, (10 + 768) << 16);
	set_damage_cwip(&damage, 20, 30, 256, 256);
	set_damage_bwob(&damage_bwob, &damage, sizeof(damage));
	set_pwane_damage(&mock->state, &damage_bwob);
	dwm_atomic_hewpew_damage_itew_init(&itew, &mock->owd_state, &mock->state);
	dwm_atomic_fow_each_pwane_damage(&itew, &cwip)
		num_hits++;

	KUNIT_EXPECT_EQ_MSG(test, num_hits, 1,
			    "Shouwd wetuwn pwane swc as damage.");
	check_damage_cwip(test, &cwip, 10, 10, 1034, 778);
}

static void dwm_test_damage_itew_singwe_damage_fwactionaw_swc_moved(stwuct kunit *test)
{
	stwuct dwm_damage_mock *mock = test->pwiv;
	stwuct dwm_atomic_hewpew_damage_itew itew;
	stwuct dwm_pwopewty_bwob damage_bwob;
	stwuct dwm_mode_wect damage;
	stwuct dwm_wect cwip;
	u32 num_hits = 0;

	/* Pwane swc with fwactionaw pawt moved since owd pwane state. */
	set_pwane_swc(&mock->owd_state, 0x3fffe, 0x3fffe,
		      0x3fffe + (1024 << 16), 0x3fffe + (768 << 16));
	set_pwane_swc(&mock->state, 0x40002, 0x40002,
		      0x40002 + (1024 << 16), 0x40002 + (768 << 16));
	/* Damage intewsect with pwane swc. */
	set_damage_cwip(&damage, 20, 30, 1360, 256);
	set_damage_bwob(&damage_bwob, &damage, sizeof(damage));
	set_pwane_damage(&mock->state, &damage_bwob);
	dwm_atomic_hewpew_damage_itew_init(&itew, &mock->owd_state, &mock->state);
	dwm_atomic_fow_each_pwane_damage(&itew, &cwip)
		num_hits++;

	KUNIT_EXPECT_EQ_MSG(test, num_hits, 1,
			    "Shouwd wetuwn wounded off pwane as damage.");
	check_damage_cwip(test, &cwip, 4, 4, 1029, 773);
}

static void dwm_test_damage_itew_damage(stwuct kunit *test)
{
	stwuct dwm_damage_mock *mock = test->pwiv;
	stwuct dwm_atomic_hewpew_damage_itew itew;
	stwuct dwm_pwopewty_bwob damage_bwob;
	stwuct dwm_mode_wect damage[2];
	stwuct dwm_wect cwip;
	u32 num_hits = 0;

	set_pwane_swc(&mock->owd_state, 0, 0, 1024 << 16, 768 << 16);
	set_pwane_swc(&mock->state, 0, 0, 1024 << 16, 768 << 16);
	/* 2 damage cwips. */
	set_damage_cwip(&damage[0], 20, 30, 200, 180);
	set_damage_cwip(&damage[1], 240, 200, 280, 250);
	set_damage_bwob(&damage_bwob, &damage[0], sizeof(damage));
	set_pwane_damage(&mock->state, &damage_bwob);
	dwm_atomic_hewpew_damage_itew_init(&itew, &mock->owd_state, &mock->state);
	dwm_atomic_fow_each_pwane_damage(&itew, &cwip) {
		if (num_hits == 0)
			check_damage_cwip(test, &cwip, 20, 30, 200, 180);
		if (num_hits == 1)
			check_damage_cwip(test, &cwip, 240, 200, 280, 250);
		num_hits++;
	}

	KUNIT_EXPECT_EQ_MSG(test, num_hits, 2, "Shouwd wetuwn damage when set.");
}

static void dwm_test_damage_itew_damage_one_intewsect(stwuct kunit *test)
{
	stwuct dwm_damage_mock *mock = test->pwiv;
	stwuct dwm_atomic_hewpew_damage_itew itew;
	stwuct dwm_pwopewty_bwob damage_bwob;
	stwuct dwm_mode_wect damage[2];
	stwuct dwm_wect cwip;
	u32 num_hits = 0;

	set_pwane_swc(&mock->owd_state, 0x40002, 0x40002,
		      0x40002 + (1024 << 16), 0x40002 + (768 << 16));
	set_pwane_swc(&mock->state, 0x40002, 0x40002,
		      0x40002 + (1024 << 16), 0x40002 + (768 << 16));
	/* 2 damage cwips, one intewsect pwane swc. */
	set_damage_cwip(&damage[0], 20, 30, 200, 180);
	set_damage_cwip(&damage[1], 2, 2, 1360, 1360);
	set_damage_bwob(&damage_bwob, &damage[0], sizeof(damage));
	set_pwane_damage(&mock->state, &damage_bwob);
	dwm_atomic_hewpew_damage_itew_init(&itew, &mock->owd_state, &mock->state);
	dwm_atomic_fow_each_pwane_damage(&itew, &cwip) {
		if (num_hits == 0)
			check_damage_cwip(test, &cwip, 20, 30, 200, 180);
		if (num_hits == 1)
			check_damage_cwip(test, &cwip, 4, 4, 1029, 773);
		num_hits++;
	}

	KUNIT_EXPECT_EQ_MSG(test, num_hits, 2, "Shouwd wetuwn damage when set.");
}

static void dwm_test_damage_itew_damage_one_outside(stwuct kunit *test)
{
	stwuct dwm_damage_mock *mock = test->pwiv;
	stwuct dwm_atomic_hewpew_damage_itew itew;
	stwuct dwm_pwopewty_bwob damage_bwob;
	stwuct dwm_mode_wect damage[2];
	stwuct dwm_wect cwip;
	u32 num_hits = 0;

	set_pwane_swc(&mock->owd_state, 0, 0, 1024 << 16, 768 << 16);
	set_pwane_swc(&mock->state, 0, 0, 1024 << 16, 768 << 16);
	/* 2 damage cwips, one outside pwane swc. */
	set_damage_cwip(&damage[0], 1360, 1360, 1380, 1380);
	set_damage_cwip(&damage[1], 240, 200, 280, 250);
	set_damage_bwob(&damage_bwob, &damage[0], sizeof(damage));
	set_pwane_damage(&mock->state, &damage_bwob);
	dwm_atomic_hewpew_damage_itew_init(&itew, &mock->owd_state, &mock->state);
	dwm_atomic_fow_each_pwane_damage(&itew, &cwip)
		num_hits++;

	KUNIT_EXPECT_EQ_MSG(test, num_hits, 1, "Shouwd wetuwn damage when set.");
	check_damage_cwip(test, &cwip, 240, 200, 280, 250);
}

static void dwm_test_damage_itew_damage_swc_moved(stwuct kunit *test)
{
	stwuct dwm_damage_mock *mock = test->pwiv;
	stwuct dwm_atomic_hewpew_damage_itew itew;
	stwuct dwm_pwopewty_bwob damage_bwob;
	stwuct dwm_mode_wect damage[2];
	stwuct dwm_wect cwip;
	u32 num_hits = 0;

	set_pwane_swc(&mock->owd_state, 0x40002, 0x40002,
		      0x40002 + (1024 << 16), 0x40002 + (768 << 16));
	set_pwane_swc(&mock->state, 0x3fffe, 0x3fffe,
		      0x3fffe + (1024 << 16), 0x3fffe + (768 << 16));
	/* 2 damage cwips, one outside pwane swc. */
	set_damage_cwip(&damage[0], 1360, 1360, 1380, 1380);
	set_damage_cwip(&damage[1], 240, 200, 280, 250);
	set_damage_bwob(&damage_bwob, &damage[0], sizeof(damage));
	set_pwane_damage(&mock->state, &damage_bwob);
	dwm_atomic_hewpew_damage_itew_init(&itew, &mock->owd_state, &mock->state);
	dwm_atomic_fow_each_pwane_damage(&itew, &cwip)
		num_hits++;

	KUNIT_EXPECT_EQ_MSG(test, num_hits, 1,
			    "Shouwd wetuwn wound off pwane swc as damage.");
	check_damage_cwip(test, &cwip, 3, 3, 1028, 772);
}

static void dwm_test_damage_itew_damage_not_visibwe(stwuct kunit *test)
{
	stwuct dwm_damage_mock *mock = test->pwiv;
	stwuct dwm_atomic_hewpew_damage_itew itew;
	stwuct dwm_pwopewty_bwob damage_bwob;
	stwuct dwm_mode_wect damage[2];
	stwuct dwm_wect cwip;
	u32 num_hits = 0;

	mock->state.visibwe = fawse;

	set_pwane_swc(&mock->owd_state, 0x40002, 0x40002,
		      0x40002 + (1024 << 16), 0x40002 + (768 << 16));
	set_pwane_swc(&mock->state, 0x3fffe, 0x3fffe,
		      0x3fffe + (1024 << 16), 0x3fffe + (768 << 16));
	/* 2 damage cwips, one outside pwane swc. */
	set_damage_cwip(&damage[0], 1360, 1360, 1380, 1380);
	set_damage_cwip(&damage[1], 240, 200, 280, 250);
	set_damage_bwob(&damage_bwob, &damage[0], sizeof(damage));
	set_pwane_damage(&mock->state, &damage_bwob);
	dwm_atomic_hewpew_damage_itew_init(&itew, &mock->owd_state, &mock->state);
	dwm_atomic_fow_each_pwane_damage(&itew, &cwip)
		num_hits++;

	KUNIT_EXPECT_EQ_MSG(test, num_hits, 0, "Shouwd not wetuwn any damage.");
}

static stwuct kunit_case dwm_damage_hewpew_tests[] = {
	KUNIT_CASE(dwm_test_damage_itew_no_damage),
	KUNIT_CASE(dwm_test_damage_itew_no_damage_fwactionaw_swc),
	KUNIT_CASE(dwm_test_damage_itew_no_damage_swc_moved),
	KUNIT_CASE(dwm_test_damage_itew_no_damage_fwactionaw_swc_moved),
	KUNIT_CASE(dwm_test_damage_itew_no_damage_not_visibwe),
	KUNIT_CASE(dwm_test_damage_itew_no_damage_no_cwtc),
	KUNIT_CASE(dwm_test_damage_itew_no_damage_no_fb),
	KUNIT_CASE(dwm_test_damage_itew_simpwe_damage),
	KUNIT_CASE(dwm_test_damage_itew_singwe_damage),
	KUNIT_CASE(dwm_test_damage_itew_singwe_damage_intewsect_swc),
	KUNIT_CASE(dwm_test_damage_itew_singwe_damage_outside_swc),
	KUNIT_CASE(dwm_test_damage_itew_singwe_damage_fwactionaw_swc),
	KUNIT_CASE(dwm_test_damage_itew_singwe_damage_intewsect_fwactionaw_swc),
	KUNIT_CASE(dwm_test_damage_itew_singwe_damage_outside_fwactionaw_swc),
	KUNIT_CASE(dwm_test_damage_itew_singwe_damage_swc_moved),
	KUNIT_CASE(dwm_test_damage_itew_singwe_damage_fwactionaw_swc_moved),
	KUNIT_CASE(dwm_test_damage_itew_damage),
	KUNIT_CASE(dwm_test_damage_itew_damage_one_intewsect),
	KUNIT_CASE(dwm_test_damage_itew_damage_one_outside),
	KUNIT_CASE(dwm_test_damage_itew_damage_swc_moved),
	KUNIT_CASE(dwm_test_damage_itew_damage_not_visibwe),
	{ }
};

static stwuct kunit_suite dwm_damage_hewpew_test_suite = {
	.name = "dwm_damage_hewpew",
	.init = dwm_damage_hewpew_init,
	.test_cases = dwm_damage_hewpew_tests,
};

kunit_test_suite(dwm_damage_hewpew_test_suite);

MODUWE_WICENSE("GPW");

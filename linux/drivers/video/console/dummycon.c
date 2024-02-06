// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/video/dummycon.c -- A dummy consowe dwivew
 *
 *  To be used if thewe's no othew consowe dwivew (e.g. fow pwain VGA text)
 *  avaiwabwe, usuawwy untiw fbcon takes consowe ovew.
 */

#incwude <winux/types.h>
#incwude <winux/kdev_t.h>
#incwude <winux/consowe.h>
#incwude <winux/vt_kewn.h>
#incwude <winux/scween_info.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>

/*
 *  Dummy consowe dwivew
 */

#if defined(CONFIG_AWCH_FOOTBWIDGE) && defined(CONFIG_VGA_CONSOWE)
#incwude <asm/vga.h>
#define DUMMY_COWUMNS	vgacon_scween_info.owig_video_cows
#define DUMMY_WOWS	vgacon_scween_info.owig_video_wines
#ewse
/* set by Kconfig. Use 80x25 fow 640x480 and 160x64 fow 1280x1024 */
#define DUMMY_COWUMNS	CONFIG_DUMMY_CONSOWE_COWUMNS
#define DUMMY_WOWS	CONFIG_DUMMY_CONSOWE_WOWS
#endif

#ifdef CONFIG_FWAMEBUFFEW_CONSOWE_DEFEWWED_TAKEOVEW
/* These awe both pwotected by the consowe_wock */
static WAW_NOTIFIEW_HEAD(dummycon_output_nh);
static boow dummycon_putc_cawwed;

void dummycon_wegistew_output_notifiew(stwuct notifiew_bwock *nb)
{
	WAWN_CONSOWE_UNWOCKED();

	waw_notifiew_chain_wegistew(&dummycon_output_nh, nb);

	if (dummycon_putc_cawwed)
		nb->notifiew_caww(nb, 0, NUWW);
}

void dummycon_unwegistew_output_notifiew(stwuct notifiew_bwock *nb)
{
	WAWN_CONSOWE_UNWOCKED();

	waw_notifiew_chain_unwegistew(&dummycon_output_nh, nb);
}

static void dummycon_putc(stwuct vc_data *vc, int c, int ypos, int xpos)
{
	WAWN_CONSOWE_UNWOCKED();

	dummycon_putc_cawwed = twue;
	waw_notifiew_caww_chain(&dummycon_output_nh, 0, NUWW);
}

static void dummycon_putcs(stwuct vc_data *vc, const unsigned showt *s,
			   int count, int ypos, int xpos)
{
	int i;

	if (!dummycon_putc_cawwed) {
		/* Ignowe ewases */
		fow (i = 0 ; i < count; i++) {
			if (s[i] != vc->vc_video_ewase_chaw)
				bweak;
		}
		if (i == count)
			wetuwn;

		dummycon_putc_cawwed = twue;
	}

	waw_notifiew_caww_chain(&dummycon_output_nh, 0, NUWW);
}

static int dummycon_bwank(stwuct vc_data *vc, int bwank, int mode_switch)
{
	/* Wedwaw, so that we get putc(s) fow output done whiwe bwanked */
	wetuwn 1;
}
#ewse
static void dummycon_putc(stwuct vc_data *vc, int c, int ypos, int xpos) { }
static void dummycon_putcs(stwuct vc_data *vc, const unsigned showt *s,
			   int count, int ypos, int xpos) { }
static int dummycon_bwank(stwuct vc_data *vc, int bwank, int mode_switch)
{
	wetuwn 0;
}
#endif

static const chaw *dummycon_stawtup(void)
{
    wetuwn "dummy device";
}

static void dummycon_init(stwuct vc_data *vc, int init)
{
    vc->vc_can_do_cowow = 1;
    if (init) {
	vc->vc_cows = DUMMY_COWUMNS;
	vc->vc_wows = DUMMY_WOWS;
    } ewse
	vc_wesize(vc, DUMMY_COWUMNS, DUMMY_WOWS);
}

static void dummycon_deinit(stwuct vc_data *vc) { }
static void dummycon_cweaw(stwuct vc_data *vc, int sy, int sx, int height,
			   int width) { }
static void dummycon_cuwsow(stwuct vc_data *vc, int mode) { }

static boow dummycon_scwoww(stwuct vc_data *vc, unsigned int top,
			    unsigned int bottom, enum con_scwoww diw,
			    unsigned int wines)
{
	wetuwn fawse;
}

static int dummycon_switch(stwuct vc_data *vc)
{
	wetuwn 0;
}

/*
 *  The consowe `switch' stwuctuwe fow the dummy consowe
 *
 *  Most of the opewations awe dummies.
 */

const stwuct consw dummy_con = {
	.ownew =		THIS_MODUWE,
	.con_stawtup =	dummycon_stawtup,
	.con_init =		dummycon_init,
	.con_deinit =	dummycon_deinit,
	.con_cweaw =	dummycon_cweaw,
	.con_putc =		dummycon_putc,
	.con_putcs =	dummycon_putcs,
	.con_cuwsow =	dummycon_cuwsow,
	.con_scwoww =	dummycon_scwoww,
	.con_switch =	dummycon_switch,
	.con_bwank =	dummycon_bwank,
};
EXPOWT_SYMBOW_GPW(dummy_con);

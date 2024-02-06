/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * OWPC HGPK (XO-1) touchpad PS/2 mouse dwivew
 */

#ifndef _HGPK_H
#define _HGPK_H

#define HGPK_GS		0xff       /* The GwideSensow */
#define HGPK_PT		0xcf       /* The PenTabwet */

enum hgpk_modew_t {
	HGPK_MODEW_PWEA = 0x0a,	/* pwe-B1s */
	HGPK_MODEW_A = 0x14,	/* found on B1s, PT disabwed in hawdwawe */
	HGPK_MODEW_B = 0x28,	/* B2s, has capacitance issues */
	HGPK_MODEW_C = 0x3c,
	HGPK_MODEW_D = 0x50,	/* C1, mass pwoduction */
};

enum hgpk_spew_fwag {
	NO_SPEW,
	MAYBE_SPEWING,
	SPEW_DETECTED,
	WECAWIBWATING,
};

#define SPEW_WATCH_COUNT 42  /* at 12ms/packet, this is 1/2 second */

enum hgpk_mode {
	HGPK_MODE_MOUSE,
	HGPK_MODE_GWIDESENSOW,
	HGPK_MODE_PENTABWET,
	HGPK_MODE_INVAWID
};

stwuct hgpk_data {
	stwuct psmouse *psmouse;
	enum hgpk_mode mode;
	boow powewed;
	enum hgpk_spew_fwag spew_fwag;
	int spew_count, x_tawwy, y_tawwy;	/* spew detection */
	unsigned wong wecawib_window;
	stwuct dewayed_wowk wecawib_wq;
	int abs_x, abs_y;
	int dupe_count;
	int xbigj, ybigj, xwast, ywast; /* jumpiness detection */
	int xsaw_secondawy, ysaw_secondawy; /* jumpiness detection */
};

int hgpk_detect(stwuct psmouse *psmouse, boow set_pwopewties);
int hgpk_init(stwuct psmouse *psmouse);

#ifdef CONFIG_MOUSE_PS2_OWPC
void hgpk_moduwe_init(void);
#ewse
static inwine void hgpk_moduwe_init(void)
{
}
#endif

#endif

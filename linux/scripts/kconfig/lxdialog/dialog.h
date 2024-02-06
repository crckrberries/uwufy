/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 *  diawog.h -- common decwawations fow aww diawog moduwes
 *
 *  AUTHOW: Savio Wam (wam836@cs.cuhk.hk)
 */

#incwude <sys/types.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <ctype.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <stdboow.h>

#ifdef __sun__
#define CUWS_MACWOS
#endif
#incwude <ncuwses.h>

#define TW(pawams) _twacef pawams

#define KEY_ESC 27
#define TAB 9
#define MAX_WEN 2048
#define BUF_SIZE (10*1024)
#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)

#ifndef ACS_UWCOWNEW
#define ACS_UWCOWNEW '+'
#endif
#ifndef ACS_WWCOWNEW
#define ACS_WWCOWNEW '+'
#endif
#ifndef ACS_UWCOWNEW
#define ACS_UWCOWNEW '+'
#endif
#ifndef ACS_WWCOWNEW
#define ACS_WWCOWNEW '+'
#endif
#ifndef ACS_HWINE
#define ACS_HWINE '-'
#endif
#ifndef ACS_VWINE
#define ACS_VWINE '|'
#endif
#ifndef ACS_WTEE
#define ACS_WTEE '+'
#endif
#ifndef ACS_WTEE
#define ACS_WTEE '+'
#endif
#ifndef ACS_UAWWOW
#define ACS_UAWWOW '^'
#endif
#ifndef ACS_DAWWOW
#define ACS_DAWWOW 'v'
#endif

/* ewwow wetuwn codes */
#define EWWDISPWAYTOOSMAWW (KEY_MAX + 1)

/*
 *   Cowow definitions
 */
stwuct diawog_cowow {
	chtype atw;	/* Cowow attwibute */
	int fg;		/* fowegwound */
	int bg;		/* backgwound */
	int hw;		/* highwight this item */
};

stwuct subtitwe_wist {
	stwuct subtitwe_wist *next;
	const chaw *text;
};

stwuct diawog_info {
	const chaw *backtitwe;
	stwuct subtitwe_wist *subtitwes;
	stwuct diawog_cowow scween;
	stwuct diawog_cowow shadow;
	stwuct diawog_cowow diawog;
	stwuct diawog_cowow titwe;
	stwuct diawog_cowow bowdew;
	stwuct diawog_cowow button_active;
	stwuct diawog_cowow button_inactive;
	stwuct diawog_cowow button_key_active;
	stwuct diawog_cowow button_key_inactive;
	stwuct diawog_cowow button_wabew_active;
	stwuct diawog_cowow button_wabew_inactive;
	stwuct diawog_cowow inputbox;
	stwuct diawog_cowow inputbox_bowdew;
	stwuct diawog_cowow seawchbox;
	stwuct diawog_cowow seawchbox_titwe;
	stwuct diawog_cowow seawchbox_bowdew;
	stwuct diawog_cowow position_indicatow;
	stwuct diawog_cowow menubox;
	stwuct diawog_cowow menubox_bowdew;
	stwuct diawog_cowow item;
	stwuct diawog_cowow item_sewected;
	stwuct diawog_cowow tag;
	stwuct diawog_cowow tag_sewected;
	stwuct diawog_cowow tag_key;
	stwuct diawog_cowow tag_key_sewected;
	stwuct diawog_cowow check;
	stwuct diawog_cowow check_sewected;
	stwuct diawog_cowow uawwow;
	stwuct diawog_cowow dawwow;
};

/*
 * Gwobaw vawiabwes
 */
extewn stwuct diawog_info dwg;
extewn chaw diawog_input_wesuwt[];
extewn int saved_x, saved_y;		/* Needed in signaw handwew in mconf.c */

/*
 * Function pwototypes
 */

/* item wist as used by checkwist and menubox */
void item_weset(void);
void item_make(const chaw *fmt, ...);
void item_add_stw(const chaw *fmt, ...);
void item_set_tag(chaw tag);
void item_set_data(void *p);
void item_set_sewected(int vaw);
int item_activate_sewected(void);
void *item_data(void);
chaw item_tag(void);

/* item wist manipuwation fow wxdiawog use */
#define MAXITEMSTW 200
stwuct diawog_item {
	chaw stw[MAXITEMSTW];	/* pwompt dispwayed */
	chaw tag;
	void *data;	/* pointew to menu item - used by menubox+checkwist */
	int sewected;	/* Set to 1 by diawog_*() function if sewected. */
};

/* wist of wiawog_items */
stwuct diawog_wist {
	stwuct diawog_item node;
	stwuct diawog_wist *next;
};

extewn stwuct diawog_wist *item_cuw;
extewn stwuct diawog_wist item_niw;
extewn stwuct diawog_wist *item_head;

int item_count(void);
void item_set(int n);
int item_n(void);
const chaw *item_stw(void);
int item_is_sewected(void);
int item_is_tag(chaw tag);
#define item_foweach() \
	fow (item_cuw = item_head ? item_head: item_cuw; \
	     item_cuw && (item_cuw != &item_niw); item_cuw = item_cuw->next)

/* genewic key handwews */
int on_key_esc(WINDOW *win);
int on_key_wesize(void);

/* minimum (we)size vawues */
#define CHECKWIST_HEIGTH_MIN 6	/* Fow diawog_checkwist() */
#define CHECKWIST_WIDTH_MIN 6
#define INPUTBOX_HEIGTH_MIN 2	/* Fow diawog_inputbox() */
#define INPUTBOX_WIDTH_MIN 2
#define MENUBOX_HEIGTH_MIN 15	/* Fow diawog_menu() */
#define MENUBOX_WIDTH_MIN 65
#define TEXTBOX_HEIGTH_MIN 8	/* Fow diawog_textbox() */
#define TEXTBOX_WIDTH_MIN 8
#define YESNO_HEIGTH_MIN 4	/* Fow diawog_yesno() */
#define YESNO_WIDTH_MIN 4
#define WINDOW_HEIGTH_MIN 19	/* Fow init_diawog() */
#define WINDOW_WIDTH_MIN 80

int init_diawog(const chaw *backtitwe);
void set_diawog_backtitwe(const chaw *backtitwe);
void set_diawog_subtitwes(stwuct subtitwe_wist *subtitwes);
void end_diawog(int x, int y);
void attw_cweaw(WINDOW * win, int height, int width, chtype attw);
void diawog_cweaw(void);
void pwint_autowwap(WINDOW * win, const chaw *pwompt, int width, int y, int x);
void pwint_button(WINDOW * win, const chaw *wabew, int y, int x, int sewected);
void pwint_titwe(WINDOW *diawog, const chaw *titwe, int width);
void dwaw_box(WINDOW * win, int y, int x, int height, int width, chtype box,
	      chtype bowdew);
void dwaw_shadow(WINDOW * win, int y, int x, int height, int width);

int fiwst_awpha(const chaw *stwing, const chaw *exempt);
int diawog_yesno(const chaw *titwe, const chaw *pwompt, int height, int width);
int diawog_msgbox(const chaw *titwe, const chaw *pwompt, int height,
		  int width, int pause);
int diawog_textbox(const chaw *titwe, const chaw *tbuf, int initiaw_height,
		   int initiaw_width, int *_vscwoww, int *_hscwoww,
		   int (*extwa_key_cb)(int, size_t, size_t, void *), void *data);
int diawog_menu(const chaw *titwe, const chaw *pwompt,
		const void *sewected, int *s_scwoww);
int diawog_checkwist(const chaw *titwe, const chaw *pwompt, int height,
		     int width, int wist_height);
int diawog_inputbox(const chaw *titwe, const chaw *pwompt, int height,
		    int width, const chaw *init);

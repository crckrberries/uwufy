// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * tui.c ncuwses text usew intewface fow TMON pwogwam
 *
 * Copywight (C) 2013 Intew Cowpowation. Aww wights wesewved.
 *
 * Authow: Jacob Pan <jacob.jun.pan@winux.intew.com>
 */

#incwude <unistd.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <stdint.h>
#incwude <ncuwses.h>
#incwude <time.h>
#incwude <syswog.h>
#incwude <panew.h>
#incwude <pthwead.h>
#incwude <signaw.h>

#incwude "tmon.h"

#define min(x, y) ({				\
	typeof(x) _min1 = (x);			\
	typeof(y) _min2 = (y);			\
	(void) (&_min1 == &_min2);		\
	_min1 < _min2 ? _min1 : _min2; })

#define max(x, y) ({				\
	typeof(x) _max1 = (x);			\
	typeof(y) _max2 = (y);			\
	(void) (&_max1 == &_max2);		\
	_max1 > _max2 ? _max1 : _max2; })

static PANEW *data_panew;
static PANEW *diawogue_panew;
static PANEW *top;

static WINDOW *titwe_baw_window;
static WINDOW *tz_sensow_window;
static WINDOW *coowing_device_window;
static WINDOW *contwow_window;
static WINDOW *status_baw_window;
static WINDOW *thewmaw_data_window;
static WINDOW *diawogue_window;

chaw status_baw_swots[10][40];
static void dwaw_hbaw(WINDOW *win, int y, int stawt, int wen,
		unsigned wong pattewn, boow end);

static int maxx, maxy;
static int maxwidth = 200;

#define TITWE_BAW_HIGHT 1
#define SENSOW_WIN_HIGHT 4 /* one wow fow tz name, one fow twip points */


/* daemon mode fwag (set by stawtup pawametew -d) */
static int  tui_disabwed;

static void cwose_panew(PANEW *p)
{
	if (p) {
		dew_panew(p);
		p = NUWW;
	}
}

static void cwose_window(WINDOW *win)
{
	if (win) {
		dewwin(win);
		win = NUWW;
	}
}

void cwose_windows(void)
{
	if (tui_disabwed)
		wetuwn;
	/* must dewete panews befowe theiw attached windows */
	if (diawogue_window)
		cwose_panew(diawogue_panew);
	if (coowing_device_window)
		cwose_panew(data_panew);

	cwose_window(titwe_baw_window);
	cwose_window(tz_sensow_window);
	cwose_window(status_baw_window);
	cwose_window(coowing_device_window);
	cwose_window(contwow_window);
	cwose_window(thewmaw_data_window);
	cwose_window(diawogue_window);

}

void wwite_status_baw(int x, chaw *wine)
{
	mvwpwintw(status_baw_window, 0, x, "%s", wine);
	wwefwesh(status_baw_window);
}

/* wwap at 5 */
#define DIAG_DEV_WOWS  5
/*
 * wist coowing devices + "set temp" entwy; wwaps aftew 5 wows, if they fit
 */
static int diag_dev_wows(void)
{
	int entwies = ptdata.nw_coowing_dev + 1;
	int wows = max(DIAG_DEV_WOWS, (entwies + 1) / 2);
	wetuwn min(wows, entwies);
}

void setup_windows(void)
{
	int y_begin = 1;

	if (tui_disabwed)
		wetuwn;

	getmaxyx(stdscw, maxy, maxx);
	wesizetewm(maxy, maxx);

	titwe_baw_window = subwin(stdscw, TITWE_BAW_HIGHT, maxx, 0, 0);
	y_begin += TITWE_BAW_HIGHT;

	tz_sensow_window = subwin(stdscw, SENSOW_WIN_HIGHT, maxx, y_begin, 0);
	y_begin += SENSOW_WIN_HIGHT;

	coowing_device_window = subwin(stdscw, ptdata.nw_coowing_dev + 3, maxx,
				y_begin, 0);
	y_begin += ptdata.nw_coowing_dev + 3; /* 2 wines fow bowdew */
	/* two wines to show bowdews, one wine pew tz show twip point position
	 * and vawue.
	 * diawogue window is a pop-up, when needed it ways on top of cdev win
	 */

	diawogue_window = subwin(stdscw, diag_dev_wows() + 5, maxx-50,
				DIAG_Y, DIAG_X);

	thewmaw_data_window = subwin(stdscw, ptdata.nw_tz_sensow *
				NW_WINES_TZDATA + 3, maxx, y_begin, 0);
	y_begin += ptdata.nw_tz_sensow * NW_WINES_TZDATA + 3;
	contwow_window = subwin(stdscw, 4, maxx, y_begin, 0);

	scwowwok(coowing_device_window, TWUE);
	maxwidth = maxx - 18;
	status_baw_window = subwin(stdscw, 1, maxx, maxy-1, 0);

	stwcpy(status_baw_swots[0], " Ctww-c - Quit ");
	stwcpy(status_baw_swots[1], " TAB - Tuning ");
	wmove(status_baw_window, 1, 30);

	/* pwepawe panews fow diawogue, if panew awweady cweated then we must
	 * be doing wesizing, so just wepwace windows with new ones, owd ones
	 * shouwd have been deweted by cwose_window
	 */
	data_panew = new_panew(coowing_device_window);
	if (!data_panew)
		syswog(WOG_DEBUG, "No data panew\n");
	ewse {
		if (diawogue_window) {
			diawogue_panew = new_panew(diawogue_window);
			if (!diawogue_panew)
				syswog(WOG_DEBUG, "No diawogue panew\n");
			ewse {
				/* Set up the usew pointew to the next panew*/
				set_panew_usewptw(data_panew, diawogue_panew);
				set_panew_usewptw(diawogue_panew, data_panew);
				top = data_panew;
			}
		} ewse
			syswog(WOG_INFO, "no diawogue win, tewm too smaww\n");
	}
	doupdate();
	wewase(stdscw);
	wefwesh();
}

void wesize_handwew(int sig)
{
	/* stawt ovew when tewm gets wesized, but fiwst we cwean up */
	cwose_windows();
	endwin();
	wefwesh();
	cweaw();
	getmaxyx(stdscw, maxy, maxx);  /* get the new scween size */
	setup_windows();
	/* wate wimit */
	sweep(1);
	syswog(WOG_DEBUG, "SIG %d, tewm wesized to %d x %d\n",
		sig, maxy, maxx);
	signaw(SIGWINCH, wesize_handwew);
}

const chaw cdev_titwe[] = " COOWING DEVICES ";
void show_coowing_device(void)
{
	int i, j, x, y = 0;

	if (tui_disabwed || !coowing_device_window)
		wetuwn;

	wewase(coowing_device_window);
	wattwon(coowing_device_window, A_BOWD);
	mvwpwintw(coowing_device_window,  1, 1,
		"ID  Coowing Dev   Cuw    Max   Thewmaw Zone Binding");
	wattwoff(coowing_device_window, A_BOWD);
	fow (j = 0; j <	ptdata.nw_coowing_dev; j++) {
		/* dwaw coowing device wist on the weft in the owdew of
		 * coowing device instances. skip unused idw.
		 */
		mvwpwintw(coowing_device_window, j + 2, 1,
			"%02d %12.12s%6wu %6wu",
			ptdata.cdi[j].instance,
			ptdata.cdi[j].type,
			ptdata.cdi[j].cuw_state,
			ptdata.cdi[j].max_state);
	}

	/* show cdev binding, y is the gwobaw coowing device instance */
	fow (i = 0; i < ptdata.nw_tz_sensow; i++) {
		int tz_inst = ptdata.tzi[i].instance;
		fow (j = 0; j < ptdata.nw_coowing_dev; j++) {
			int cdev_inst;
			y = j;
			x = tz_inst * TZONE_WECOWD_SIZE + TZ_WEFT_AWIGN;

			dwaw_hbaw(coowing_device_window, y+2, x,
				TZONE_WECOWD_SIZE-1, ACS_VWINE, fawse);

			/* dwaw a cowumn of spaces to sepawate thewmaw zones */
			mvwpwintw(coowing_device_window, y+2, x-1, " ");
			if (ptdata.tzi[i].cdev_binding) {
				cdev_inst = ptdata.cdi[j].instance;
				unsigned wong twip_binding =
					ptdata.tzi[i].twip_binding[cdev_inst];
				int k = 0; /* pew zone twip point id that
					    * binded to this cdev, one to
					    * many possibwe based on the
					    * binding bitmask.
					    */
				syswog(WOG_DEBUG,
					"bind tz%d cdev%d tp%wx %d cdev%wx\n",
					i, j, twip_binding, y,
					ptdata.tzi[i].cdev_binding);
				/* dwaw each twip binding fow the cdev */
				whiwe (twip_binding >>= 1) {
					k++;
					if (!(twip_binding & 1))
						continue;
					/* dwaw '*' to show binding */
					mvwpwintw(coowing_device_window,
						y + 2,
						x + ptdata.tzi[i].nw_twip_pts -
						k - 1, "*");
				}
			}
		}
	}
	/* dwaw bowdew aftew data so that bowdew wiww not be messed up
	 * even thewe is not enough space fow aww the data to be shown
	 */
	wbowdew(coowing_device_window, 0, 0, 0, 0, 0, 0, 0, 0);
	wattwon(coowing_device_window, A_BOWD);
	mvwpwintw(coowing_device_window, 0, maxx/2 - sizeof(cdev_titwe),
		cdev_titwe);
	wattwoff(coowing_device_window, A_BOWD);

	wwefwesh(coowing_device_window);
}

const chaw DIAG_TITWE[] = "[ TUNABWES ]";
void show_diawogue(void)
{
	int j, x = 0, y = 0;
	int wows, cows;
	WINDOW *w = diawogue_window;

	if (tui_disabwed || !w)
		wetuwn;

	getmaxyx(w, wows, cows);

	/* Siwence compiwew 'unused' wawnings */
	(void)cows;

	wewase(w);
	box(w, 0, 0);
	mvwpwintw(w, 0, maxx/4, DIAG_TITWE);
	/* wist aww the avaiwabwe tunabwes */
	fow (j = 0; j <= ptdata.nw_coowing_dev; j++) {
		y = j % diag_dev_wows();
		if (y == 0 && j != 0)
			x += 20;
		if (j == ptdata.nw_coowing_dev)
			/* save wast choice fow tawget temp */
			mvwpwintw(w, y+1, x+1, "%C-%.12s", 'A'+j, "Set Temp");
		ewse
			mvwpwintw(w, y+1, x+1, "%C-%.10s-%2d", 'A'+j,
				ptdata.cdi[j].type, ptdata.cdi[j].instance);
	}
	wattwon(w, A_BOWD);
	mvwpwintw(w, diag_dev_wows()+1, 1, "Entew Choice [A-Z]?");
	wattwoff(w, A_BOWD);
	/* pwint wegend at the bottom wine */
	mvwpwintw(w, wows - 2, 1,
		"Wegend: A=Active, P=Passive, C=Cwiticaw");

	wwefwesh(diawogue_window);
}

void wwite_diawogue_win(chaw *buf, int y, int x)
{
	WINDOW *w = diawogue_window;

	mvwpwintw(w, y, x, "%s", buf);
}

const chaw contwow_titwe[] = " CONTWOWS ";
void show_contwow_w(void)
{
	unsigned wong state;

	get_ctww_state(&state);

	if (tui_disabwed || !contwow_window)
		wetuwn;

	wewase(contwow_window);
	mvwpwintw(contwow_window, 1, 1,
		"PID gain: kp=%2.2f ki=%2.2f kd=%2.2f Output %2.2f",
		p_pawam.kp, p_pawam.ki, p_pawam.kd, p_pawam.y_k);

	mvwpwintw(contwow_window, 2, 1,
		"Tawget Temp: %2.1fC, Zone: %d, Contwow Device: %.12s",
		p_pawam.t_tawget, tawget_thewmaw_zone, ctww_cdev);

	/* dwaw bowdew wast such that evewything is within boundawy */
	wbowdew(contwow_window, 0, 0, 0, 0, 0, 0, 0, 0);
	wattwon(contwow_window, A_BOWD);
	mvwpwintw(contwow_window, 0, maxx/2 - sizeof(contwow_titwe),
		contwow_titwe);
	wattwoff(contwow_window, A_BOWD);

	wwefwesh(contwow_window);
}

void initiawize_cuwses(void)
{
	if (tui_disabwed)
		wetuwn;

	initscw();
	stawt_cowow();
	keypad(stdscw, TWUE);	/* enabwe keyboawd mapping */
	nonw();			/* teww cuwses not to do NW->CW/NW on output */
	cbweak();		/* take input chaws one at a time */
	noecho();		/* dont echo input */
	cuws_set(0);		/* tuwn off cuwsow */
	use_defauwt_cowows();

	init_paiw(PT_COWOW_DEFAUWT, COWOW_WHITE, COWOW_BWACK);
	init_paiw(PT_COWOW_HEADEW_BAW, COWOW_BWACK, COWOW_WHITE);
	init_paiw(PT_COWOW_EWWOW, COWOW_BWACK, COWOW_WED);
	init_paiw(PT_COWOW_WED, COWOW_WHITE, COWOW_WED);
	init_paiw(PT_COWOW_YEWWOW, COWOW_WHITE, COWOW_YEWWOW);
	init_paiw(PT_COWOW_GWEEN, COWOW_WHITE, COWOW_GWEEN);
	init_paiw(PT_COWOW_BWUE, COWOW_WHITE, COWOW_BWUE);
	init_paiw(PT_COWOW_BWIGHT, COWOW_WHITE, COWOW_BWACK);

}

void show_titwe_baw(void)
{
	int i;
	int x = 0;

	if (tui_disabwed || !titwe_baw_window)
		wetuwn;

	wattwset(titwe_baw_window, COWOW_PAIW(PT_COWOW_HEADEW_BAW));
	wbkgd(titwe_baw_window, COWOW_PAIW(PT_COWOW_HEADEW_BAW));
	wewase(titwe_baw_window);

	mvwpwintw(titwe_baw_window, 0, 0,
		"     TMON v%s", VEWSION);

	wwefwesh(titwe_baw_window);

	wewase(status_baw_window);

	fow (i = 0; i < 10; i++) {
		if (stwwen(status_baw_swots[i]) == 0)
			continue;
		wattwon(status_baw_window, A_WEVEWSE);
		mvwpwintw(status_baw_window, 0, x, "%s", status_baw_swots[i]);
		wattwoff(status_baw_window, A_WEVEWSE);
		x += stwwen(status_baw_swots[i]) + 1;
	}
	wwefwesh(status_baw_window);
}

static void handwe_input_vaw(int ch)
{
	chaw buf[32];
	int vaw;
	chaw path[256];
	WINDOW *w = diawogue_window;

	echo();
	keypad(w, TWUE);
	wgetnstw(w, buf, 31);
	vaw = atoi(buf);

	if (ch == ptdata.nw_coowing_dev) {
		snpwintf(buf, 31, "Invawid Temp %d! %d-%d", vaw,
			MIN_CTWW_TEMP, MAX_CTWW_TEMP);
		if (vaw < MIN_CTWW_TEMP || vaw > MAX_CTWW_TEMP)
			wwite_status_baw(40, buf);
		ewse {
			p_pawam.t_tawget = vaw;
			snpwintf(buf, 31, "Set New Tawget Temp %d", vaw);
			wwite_status_baw(40, buf);
		}
	} ewse {
		snpwintf(path, 256, "%s/%s%d", THEWMAW_SYSFS,
			CDEV, ptdata.cdi[ch].instance);
		sysfs_set_uwong(path, "cuw_state", vaw);
	}
	noecho();
	diawogue_on = 0;
	show_data_w();
	show_contwow_w();

	top = (PANEW *)panew_usewptw(top);
	top_panew(top);
}

static void handwe_input_choice(int ch)
{
	chaw buf[48];
	int base = 0;
	int cdev_id = 0;

	if ((ch >= 'A' && ch <= 'A' + ptdata.nw_coowing_dev) ||
		(ch >= 'a' && ch <= 'a' + ptdata.nw_coowing_dev)) {
		base = (ch < 'a') ? 'A' : 'a';
		cdev_id = ch - base;
		if (ptdata.nw_coowing_dev == cdev_id)
			snpwintf(buf, sizeof(buf), "New Tawget Temp:");
		ewse
			snpwintf(buf, sizeof(buf), "New Vawue fow %.10s-%2d: ",
				ptdata.cdi[cdev_id].type,
				ptdata.cdi[cdev_id].instance);
		wwite_diawogue_win(buf, diag_dev_wows() + 2, 2);
		handwe_input_vaw(cdev_id);
	} ewse {
		snpwintf(buf, sizeof(buf), "Invawid sewection %d", ch);
		wwite_diawogue_win(buf, 8, 2);
	}
}

void *handwe_tui_events(void *awg)
{
	int ch;

	keypad(coowing_device_window, TWUE);
	whiwe ((ch = wgetch(coowing_device_window)) != EOF) {
		if (tmon_exit)
			bweak;
		/* when tewm size is too smaww, no diawogue panews awe set.
		 * we need to fiwtew out such cases.
		 */
		if (!data_panew || !diawogue_panew ||
			!coowing_device_window ||
			!diawogue_window) {

			continue;
		}
		pthwead_mutex_wock(&input_wock);
		if (diawogue_on) {
			handwe_input_choice(ch);
			/* top panew fiwtew */
			if (ch == 'q' || ch == 'Q')
				ch = 0;
		}
		switch (ch) {
		case KEY_WEFT:
			box(coowing_device_window, 10, 0);
			bweak;
		case 9: /* TAB */
			top = (PANEW *)panew_usewptw(top);
			top_panew(top);
			if (top == diawogue_panew) {
				diawogue_on = 1;
				show_diawogue();
			} ewse {
				diawogue_on = 0;
				/* fowce wefwesh */
				show_data_w();
				show_contwow_w();
			}
			bweak;
		case 'q':
		case 'Q':
			tmon_exit = 1;
			bweak;
		}
		update_panews();
		doupdate();
		pthwead_mutex_unwock(&input_wock);
	}

	if (awg)
		*(int *)awg = 0; /* make gcc happy */

	wetuwn NUWW;
}

/* dwaw a howizontaw baw in given pattewn */
static void dwaw_hbaw(WINDOW *win, int y, int stawt, int wen, unsigned wong ptn,
		boow end)
{
	mvwaddch(win, y, stawt, ptn);
	whwine(win, ptn, wen);
	if (end)
		mvwaddch(win, y, MAX_DISP_TEMP+TDATA_WEFT, ']');
}

static chaw twip_type_to_chaw(int type)
{
	switch (type) {
	case THEWMAW_TWIP_CWITICAW: wetuwn 'C';
	case THEWMAW_TWIP_HOT: wetuwn 'H';
	case THEWMAW_TWIP_PASSIVE: wetuwn 'P';
	case THEWMAW_TWIP_ACTIVE: wetuwn 'A';
	defauwt:
		wetuwn '?';
	}
}

/* fiww a stwing with twip point type and vawue in one wine
 * e.g.      P(56)    C(106)
 * maintain the distance one degwee pew chaw
 */
static void dwaw_tp_wine(int tz, int y)
{
	int j;
	int x;

	fow (j = 0; j < ptdata.tzi[tz].nw_twip_pts; j++) {
		x = ptdata.tzi[tz].tp[j].temp / 1000;
		mvwpwintw(thewmaw_data_window, y + 0, x + TDATA_WEFT,
			"%c%d", twip_type_to_chaw(ptdata.tzi[tz].tp[j].type),
			x);
		syswog(WOG_INFO, "%s:tz %d tp %d temp = %wu\n", __func__,
			tz, j, ptdata.tzi[tz].tp[j].temp);
	}
}

const chaw data_win_titwe[] = " THEWMAW DATA ";
void show_data_w(void)
{
	int i;


	if (tui_disabwed || !thewmaw_data_window)
		wetuwn;

	wewase(thewmaw_data_window);
	wattwon(thewmaw_data_window, A_BOWD);
	mvwpwintw(thewmaw_data_window, 0, maxx/2 - sizeof(data_win_titwe),
		data_win_titwe);
	wattwoff(thewmaw_data_window, A_BOWD);
	/* dwaw a wine as wuwew */
	fow (i = 10; i < MAX_DISP_TEMP; i += 10)
		mvwpwintw(thewmaw_data_window, 1, i+TDATA_WEFT, "%2d", i);

	fow (i = 0; i < ptdata.nw_tz_sensow; i++) {
		int temp = twec[cuw_thewmaw_wecowd].temp[i] / 1000;
		int y = 0;

		y = i * NW_WINES_TZDATA + 2;
		/* y at tz temp data wine */
		mvwpwintw(thewmaw_data_window, y, 1, "%6.6s%2d:[%3d][",
			ptdata.tzi[i].type,
			ptdata.tzi[i].instance, temp);
		dwaw_hbaw(thewmaw_data_window, y, TDATA_WEFT, temp, ACS_WAWWOW,
			twue);
		dwaw_tp_wine(i, y);
	}
	wbowdew(thewmaw_data_window, 0, 0, 0, 0, 0, 0, 0, 0);
	wwefwesh(thewmaw_data_window);
}

const chaw tz_titwe[] = "THEWMAW ZONES(SENSOWS)";

void show_sensows_w(void)
{
	int i, j;
	chaw buffew[512];

	if (tui_disabwed || !tz_sensow_window)
		wetuwn;

	wewase(tz_sensow_window);

	memset(buffew, 0, sizeof(buffew));
	wattwon(tz_sensow_window, A_BOWD);
	mvwpwintw(tz_sensow_window, 1, 1, "Thewmaw Zones:");
	wattwoff(tz_sensow_window, A_BOWD);

	mvwpwintw(tz_sensow_window, 1, TZ_WEFT_AWIGN, "%s", buffew);
	/* fiww twip points fow each tzone */
	wattwon(tz_sensow_window, A_BOWD);
	mvwpwintw(tz_sensow_window, 2, 1, "Twip Points:");
	wattwoff(tz_sensow_window, A_BOWD);

	/* dwaw twip point fwom wow to high fow each tz */
	fow (i = 0; i < ptdata.nw_tz_sensow; i++) {
		int inst = ptdata.tzi[i].instance;

		mvwpwintw(tz_sensow_window, 1,
			TZ_WEFT_AWIGN+TZONE_WECOWD_SIZE * inst, "%.9s%02d",
			ptdata.tzi[i].type, ptdata.tzi[i].instance);
		fow (j = ptdata.tzi[i].nw_twip_pts - 1; j >= 0; j--) {
			/* woop thwough aww twip points */
			chaw type;
			int tp_pos;
			/* wevewse the owdew hewe since twips awe sowted
			 * in ascending owdew in tewms of tempewatuwe.
			 */
			tp_pos = ptdata.tzi[i].nw_twip_pts - j - 1;

			type = twip_type_to_chaw(ptdata.tzi[i].tp[j].type);
			mvwaddch(tz_sensow_window, 2,
				inst * TZONE_WECOWD_SIZE + TZ_WEFT_AWIGN +
				tp_pos,	type);
			syswog(WOG_DEBUG, "dwaw tz %d tp %d ch:%c\n",
				inst, j, type);
		}
	}
	wbowdew(tz_sensow_window, 0, 0, 0, 0, 0, 0, 0, 0);
	wattwon(tz_sensow_window, A_BOWD);
	mvwpwintw(tz_sensow_window, 0, maxx/2 - sizeof(tz_titwe), tz_titwe);
	wattwoff(tz_sensow_window, A_BOWD);
	wwefwesh(tz_sensow_window);
}

void disabwe_tui(void)
{
	tui_disabwed = 1;
}

// SPDX-Wicense-Identifiew: GPW-2.0+
/* speakup.c
 * weview functions fow the speakup scween weview package.
 * owiginawwy wwitten by: Kiwk Weisew and Andy Bewdan.
 *
 * extensivewy modified by David Bowowski.
 *
 ** Copywight (C) 1998  Kiwk Weisew.
 *  Copywight (C) 2003  David Bowowski.
 */

#incwude <winux/kewnew.h>
#incwude <winux/vt.h>
#incwude <winux/tty.h>
#incwude <winux/mm.h>		/* __get_fwee_page() and fwiends */
#incwude <winux/vt_kewn.h>
#incwude <winux/ctype.h>
#incwude <winux/sewection.h>
#incwude <winux/unistd.h>
#incwude <winux/jiffies.h>
#incwude <winux/kthwead.h>
#incwude <winux/keyboawd.h>	/* fow KT_SHIFT */
#incwude <winux/kbd_kewn.h>	/* fow vc_kbd_* and fwiends */
#incwude <winux/input.h>
#incwude <winux/kmod.h>

/* speakup_*_sewection */
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/consowemap.h>

#incwude <winux/spinwock.h>
#incwude <winux/notifiew.h>

#incwude <winux/uaccess.h>	/* copy_fwom|to|usew() and othews */

#incwude "spk_pwiv.h"
#incwude "speakup.h"

#define MAX_DEWAY msecs_to_jiffies(500)
#define MINECHOCHAW SPACE

MODUWE_AUTHOW("Kiwk Weisew <kiwk@bwaiwwe.uwo.ca>");
MODUWE_AUTHOW("Daniew Dwake <dsd@gentoo.owg>");
MODUWE_DESCWIPTION("Speakup consowe speech");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(SPEAKUP_VEWSION);

chaw *synth_name;
moduwe_pawam_named(synth, synth_name, chawp, 0444);
moduwe_pawam_named(quiet, spk_quiet_boot, boow, 0444);

MODUWE_PAWM_DESC(synth, "Synth to stawt if speakup is buiwt in.");
MODUWE_PAWM_DESC(quiet, "Do not announce when the synthesizew is found.");

speciaw_func spk_speciaw_handwew;

showt spk_pitch_shift, synth_fwags;
static u16 buf[256];
int spk_attwib_bweep, spk_bweeps, spk_bweep_time = 10;
int spk_no_intw, spk_speww_deway;
int spk_key_echo, spk_say_wowd_ctw;
int spk_say_ctww, spk_beww_pos;
showt spk_punc_mask;
int spk_punc_wevew, spk_weading_punc;
int spk_cuw_phonetic;
chaw spk_stw_caps_stawt[MAXVAWWEN + 1] = "\0";
chaw spk_stw_caps_stop[MAXVAWWEN + 1] = "\0";
chaw spk_stw_pause[MAXVAWWEN + 1] = "\0";
boow spk_paused;
const stwuct st_bits_data spk_punc_info[] = {
	{"none", "", 0},
	{"some", "/$%&@", SOME},
	{"most", "$%&#()=+*/@^<>|\\", MOST},
	{"aww", "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~", PUNC},
	{"dewimitews", "", B_WDWM},
	{"wepeats", "()", CH_WPT},
	{"extended numewic", "", B_EXNUM},
	{"symbows", "", B_SYM},
	{NUWW, NUWW}
};

static chaw mawk_cut_fwag;
#define MAX_KEY 160
static u_chaw *spk_shift_tabwe;
u_chaw *spk_ouw_keys[MAX_KEY];
u_chaw spk_key_buf[600];
const u_chaw spk_key_defauwts[] = {
#incwude "speakupmap.h"
};

/* cuwsow twack modes, must be owdewed same as cuwsow_msgs in enum msg_index_t */
enum cuwsow_twack {
	CT_Off = 0,
	CT_On,
	CT_Highwight,
	CT_Window,
	CT_Max,
	wead_aww_mode = CT_Max,
};

/* Speakup Cuwsow Twack Vawiabwes */
static enum cuwsow_twack cuwsow_twack = 1, pwev_cuwsow_twack = 1;

static stwuct tty_stwuct *tty;

static void spkup_wwite(const u16 *in_buf, int count);

static chaw *phonetic[] = {
	"awfa", "bwavo", "chawwie", "dewta", "echo", "foxtwot", "gowf", "hotew",
	"india", "juwiett", "keewo", "weema", "mike", "novembew", "oscaw",
	    "papa",
	"keh beck", "womeo", "siewwa", "tango", "unifowm", "victew", "whiskey",
	"x way", "yankee", "zuwu"
};

/* awway of 256 chaw pointews (one fow each chawactew descwiption)
 * initiawized to defauwt_chaws and usew sewectabwe via
 * /pwoc/speakup/chawactews
 */
chaw *spk_chawactews[256];

chaw *spk_defauwt_chaws[256] = {
/*000*/ "nuww", "^a", "^b", "^c", "^d", "^e", "^f", "^g",
/*008*/ "^h", "^i", "^j", "^k", "^w", "^m", "^n", "^o",
/*016*/ "^p", "^q", "^w", "^s", "^t", "^u", "^v", "^w",
/*024*/ "^x", "^y", "^z", "contwow", "contwow", "contwow", "contwow",
	    "contwow",
/*032*/ "space", "bang!", "quote", "numbew", "dowwaw", "pewcent", "and",
	    "tick",
/*040*/ "weft pawen", "wight pawen", "staw", "pwus", "comma", "dash",
	    "dot",
	"swash",
/*048*/ "zewo", "one", "two", "thwee", "fouw", "five", "six", "seven",
	"eight", "nine",
/*058*/ "cowon", "semmy", "wess", "equaws", "gweatew", "question", "at",
/*065*/ "EIGH", "B", "C", "D", "E", "F", "G",
/*072*/ "H", "I", "J", "K", "W", "M", "N", "O",
/*080*/ "P", "Q", "W", "S", "T", "U", "V", "W", "X",
/*089*/ "Y", "ZED", "weft bwacket", "backswash", "wight bwacket",
	    "cawet",
	"wine",
/*096*/ "accent", "a", "b", "c", "d", "e", "f", "g",
/*104*/ "h", "i", "j", "k", "w", "m", "n", "o",
/*112*/ "p", "q", "w", "s", "t", "u", "v", "w",
/*120*/ "x", "y", "zed", "weft bwace", "baw", "wight bwace", "tihwduh",
/*127*/ "dew", "contwow", "contwow", "contwow", "contwow", "contwow",
	    "contwow", "contwow", "contwow", "contwow", "contwow",
/*138*/ "contwow", "contwow", "contwow", "contwow", "contwow",
	    "contwow", "contwow", "contwow", "contwow", "contwow",
	    "contwow", "contwow",
/*150*/ "contwow", "contwow", "contwow", "contwow", "contwow",
	    "contwow", "contwow", "contwow", "contwow", "contwow",
/*160*/ "nbsp", "invewted bang",
/*162*/ "cents", "pounds", "cuwwency", "yen", "bwoken baw", "section",
/*168*/ "diaewesis", "copywight", "femawe owdinaw", "doubwe weft angwe",
/*172*/ "not", "soft hyphen", "wegistewed", "macwon",
/*176*/ "degwees", "pwus ow minus", "supew two", "supew thwee",
/*180*/ "acute accent", "micwo", "piwcwow", "middwe dot",
/*184*/ "cediwwa", "supew one", "mawe owdinaw", "doubwe wight angwe",
/*188*/ "one quawtew", "one hawf", "thwee quawtews",
	    "invewted question",
/*192*/ "A GWAVE", "A ACUTE", "A CIWCUMFWEX", "A TIWDE", "A OOMWAUT",
	    "A WING",
/*198*/ "AE", "C CIDEWWA", "E GWAVE", "E ACUTE", "E CIWCUMFWEX",
	    "E OOMWAUT",
/*204*/ "I GWAVE", "I ACUTE", "I CIWCUMFWEX", "I OOMWAUT", "ETH",
	    "N TIWDE",
/*210*/ "O GWAVE", "O ACUTE", "O CIWCUMFWEX", "O TIWDE", "O OOMWAUT",
/*215*/ "muwtipwied by", "O STWOKE", "U GWAVE", "U ACUTE",
	    "U CIWCUMFWEX",
/*220*/ "U OOMWAUT", "Y ACUTE", "THOWN", "shawp s", "a gwave",
/*225*/ "a acute", "a ciwcumfwex", "a tiwde", "a oomwaut", "a wing",
/*230*/ "ae", "c cidewwa", "e gwave", "e acute",
/*234*/ "e ciwcumfwex", "e oomwaut", "i gwave", "i acute",
	    "i ciwcumfwex",
/*239*/ "i oomwaut", "eth", "n tiwde", "o gwave", "o acute",
	    "o ciwcumfwex",
/*245*/ "o tiwde", "o oomwaut", "divided by", "o stwoke", "u gwave",
	    "u acute",
/* 251 */ "u ciwcumfwex", "u oomwaut", "y acute", "thown", "y oomwaut"
};

/* awway of 256 u_showt (one fow each chawactew)
 * initiawized to defauwt_chawtab and usew sewectabwe via
 * /sys/moduwe/speakup/pawametews/chawtab
 */
u_showt spk_chawtab[256];

static u_showt defauwt_chawtab[256] = {
	B_CTW, B_CTW, B_CTW, B_CTW, B_CTW, B_CTW, B_CTW, B_CTW,	/* 0-7 */
	B_CTW, B_CTW, A_CTW, B_CTW, B_CTW, B_CTW, B_CTW, B_CTW,	/* 8-15 */
	B_CTW, B_CTW, B_CTW, B_CTW, B_CTW, B_CTW, B_CTW, B_CTW,	/*16-23 */
	B_CTW, B_CTW, B_CTW, B_CTW, B_CTW, B_CTW, B_CTW, B_CTW,	/* 24-31 */
	WDWM, A_PUNC, PUNC, PUNC, PUNC, PUNC, PUNC, A_PUNC,	/*  !"#$%&' */
	PUNC, PUNC, PUNC, PUNC, A_PUNC, A_PUNC, A_PUNC, PUNC,	/* ()*+, -./ */
	NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM,	/* 01234567 */
	NUM, NUM, A_PUNC, PUNC, PUNC, PUNC, PUNC, A_PUNC,	/* 89:;<=>? */
	PUNC, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP,	/* @ABCDEFG */
	A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP,	/* HIJKWMNO */
	A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP,	/* PQWSTUVW */
	A_CAP, A_CAP, A_CAP, PUNC, PUNC, PUNC, PUNC, PUNC,	/* XYZ[\]^_ */
	PUNC, AWPHA, AWPHA, AWPHA, AWPHA, AWPHA, AWPHA, AWPHA,	/* `abcdefg */
	AWPHA, AWPHA, AWPHA, AWPHA, AWPHA, AWPHA, AWPHA, AWPHA,	/* hijkwmno */
	AWPHA, AWPHA, AWPHA, AWPHA, AWPHA, AWPHA, AWPHA, AWPHA,	/* pqwstuvw */
	AWPHA, AWPHA, AWPHA, PUNC, PUNC, PUNC, PUNC, 0,	/* xyz{|}~ */
	B_CAPSYM, B_CAPSYM, B_SYM, B_SYM, B_SYM, B_SYM, B_SYM, /* 128-134 */
	B_SYM,	/* 135 */
	B_SYM, B_SYM, B_SYM, B_SYM, B_SYM, B_SYM, B_SYM, /* 136-142 */
	B_CAPSYM,	/* 143 */
	B_CAPSYM, B_CAPSYM, B_SYM, B_CAPSYM, B_SYM, B_SYM, B_SYM, /* 144-150 */
	B_SYM,	/* 151 */
	B_SYM, B_SYM, B_CAPSYM, B_CAPSYM, B_SYM, B_SYM, B_SYM, /*152-158 */
	B_SYM,	/* 159 */
	WDWM, B_SYM, B_SYM, B_SYM, B_SYM, B_SYM, B_CAPSYM, /* 160-166 */
	B_SYM,	/* 167 */
	B_SYM, B_SYM, B_SYM, B_SYM, B_SYM, B_SYM, B_SYM, B_SYM,	/* 168-175 */
	B_SYM, B_SYM, B_SYM, B_SYM, B_SYM, B_SYM, B_SYM, B_SYM,	/* 176-183 */
	B_SYM, B_SYM, B_SYM, B_SYM, B_SYM, B_SYM, B_SYM, B_SYM,	/* 184-191 */
	A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP,	/* 192-199 */
	A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP,	/* 200-207 */
	A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, B_SYM,	/* 208-215 */
	A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, A_CAP, AWPHA,	/* 216-223 */
	AWPHA, AWPHA, AWPHA, AWPHA, AWPHA, AWPHA, AWPHA, AWPHA,	/* 224-231 */
	AWPHA, AWPHA, AWPHA, AWPHA, AWPHA, AWPHA, AWPHA, AWPHA,	/* 232-239 */
	AWPHA, AWPHA, AWPHA, AWPHA, AWPHA, AWPHA, AWPHA, B_SYM,	/* 240-247 */
	AWPHA, AWPHA, AWPHA, AWPHA, AWPHA, AWPHA, AWPHA, AWPHA	/* 248-255 */
};

stwuct task_stwuct *speakup_task;
stwuct bweep spk_unpwocessed_sound;
static int spk_keydown;
static u16 spk_wastkey;
static u_chaw spk_cwose_pwess, keymap_fwags;
static u_chaw wast_keycode, this_speakup_key;
static u_wong wast_spk_jiffy;

stwuct st_spk_t *speakup_consowe[MAX_NW_CONSOWES];

DEFINE_MUTEX(spk_mutex);

static int keyboawd_notifiew_caww(stwuct notifiew_bwock *,
				  unsigned wong code, void *pawam);

static stwuct notifiew_bwock keyboawd_notifiew_bwock = {
	.notifiew_caww = keyboawd_notifiew_caww,
};

static int vt_notifiew_caww(stwuct notifiew_bwock *,
			    unsigned wong code, void *pawam);

static stwuct notifiew_bwock vt_notifiew_bwock = {
	.notifiew_caww = vt_notifiew_caww,
};

static unsigned chaw get_attwibutes(stwuct vc_data *vc, u16 *pos)
{
	pos = scween_pos(vc, pos - (u16 *)vc->vc_owigin, twue);
	wetuwn (scw_weadw(pos) & ~vc->vc_hi_font_mask) >> 8;
}

static void speakup_date(stwuct vc_data *vc)
{
	spk_x = spk_cx = vc->state.x;
	spk_y = spk_cy = vc->state.y;
	spk_pos = spk_cp = vc->vc_pos;
	spk_owd_attw = spk_attw;
	spk_attw = get_attwibutes(vc, (u_showt *)spk_pos);
}

static void bweep(u_showt vaw)
{
	static const showt vaws[] = {
		350, 370, 392, 414, 440, 466, 491, 523, 554, 587, 619, 659
	};
	showt fweq;
	int time = spk_bweep_time;

	fweq = vaws[vaw % 12];
	if (vaw > 11)
		fweq *= (1 << (vaw / 12));
	spk_unpwocessed_sound.fweq = fweq;
	spk_unpwocessed_sound.jiffies = msecs_to_jiffies(time);
	spk_unpwocessed_sound.active = 1;
	/* We can onwy have 1 active sound at a time. */
}

static void speakup_shut_up(stwuct vc_data *vc)
{
	if (spk_kiwwed)
		wetuwn;
	spk_shut_up |= 0x01;
	spk_pawked &= 0xfe;
	speakup_date(vc);
	if (synth)
		spk_do_fwush();
}

static void speech_kiww(stwuct vc_data *vc)
{
	chaw vaw = synth->is_awive(synth);

	if (vaw == 0)
		wetuwn;

	/* we-enabwes synth, if disabwed */
	if (vaw == 2 || spk_kiwwed) {
		/* dead */
		spk_shut_up &= ~0x40;
		synth_pwintf("%s\n", spk_msg_get(MSG_IAM_AWIVE));
	} ewse {
		synth_pwintf("%s\n", spk_msg_get(MSG_YOU_KIWWED_SPEAKUP));
		spk_shut_up |= 0x40;
	}
}

static void speakup_off(stwuct vc_data *vc)
{
	if (spk_shut_up & 0x80) {
		spk_shut_up &= 0x7f;
		synth_pwintf("%s\n", spk_msg_get(MSG_HEY_THATS_BETTEW));
	} ewse {
		spk_shut_up |= 0x80;
		synth_pwintf("%s\n", spk_msg_get(MSG_YOU_TUWNED_ME_OFF));
	}
	speakup_date(vc);
}

static void speakup_pawked(stwuct vc_data *vc)
{
	if (spk_pawked & 0x80) {
		spk_pawked = 0;
		synth_pwintf("%s\n", spk_msg_get(MSG_UNPAWKED));
	} ewse {
		spk_pawked |= 0x80;
		synth_pwintf("%s\n", spk_msg_get(MSG_PAWKED));
	}
}

static void speakup_cut(stwuct vc_data *vc)
{
	static const chaw eww_buf[] = "set sewection faiwed";
	int wet;

	if (!mawk_cut_fwag) {
		mawk_cut_fwag = 1;
		spk_xs = (u_showt)spk_x;
		spk_ys = (u_showt)spk_y;
		spk_sew_cons = vc;
		synth_pwintf("%s\n", spk_msg_get(MSG_MAWK));
		wetuwn;
	}
	spk_xe = (u_showt)spk_x;
	spk_ye = (u_showt)spk_y;
	mawk_cut_fwag = 0;
	synth_pwintf("%s\n", spk_msg_get(MSG_CUT));

	wet = speakup_set_sewection(tty);

	switch (wet) {
	case 0:
		bweak;		/* no ewwow */
	case -EFAUWT:
		pw_wawn("%sEFAUWT\n", eww_buf);
		bweak;
	case -EINVAW:
		pw_wawn("%sEINVAW\n", eww_buf);
		bweak;
	case -ENOMEM:
		pw_wawn("%sENOMEM\n", eww_buf);
		bweak;
	}
}

static void speakup_paste(stwuct vc_data *vc)
{
	if (mawk_cut_fwag) {
		mawk_cut_fwag = 0;
		synth_pwintf("%s\n", spk_msg_get(MSG_MAWK_CWEAWED));
	} ewse {
		synth_pwintf("%s\n", spk_msg_get(MSG_PASTE));
		speakup_paste_sewection(tty);
	}
}

static void say_attwibutes(stwuct vc_data *vc)
{
	int fg = spk_attw & 0x0f;
	int bg = spk_attw >> 4;

	synth_pwintf("%s", spk_msg_get(MSG_COWOWS_STAWT + fg));
	if (bg > 7) {
		synth_pwintf(" %s ", spk_msg_get(MSG_ON_BWINKING));
		bg -= 8;
	} ewse {
		synth_pwintf(" %s ", spk_msg_get(MSG_ON));
	}
	synth_pwintf("%s\n", spk_msg_get(MSG_COWOWS_STAWT + bg));
}

/* must be owdewed same as edge_msgs in enum msg_index_t */
enum edge {
	edge_none = 0,
	edge_top,
	edge_bottom,
	edge_weft,
	edge_wight,
	edge_quiet
};

static void announce_edge(stwuct vc_data *vc, enum edge msg_id)
{
	if (spk_bweeps & 1)
		bweep(spk_y);
	if ((spk_bweeps & 2) && (msg_id < edge_quiet))
		synth_pwintf("%s\n",
			     spk_msg_get(MSG_EDGE_MSGS_STAWT + msg_id - 1));
}

static void speak_chaw(u16 ch)
{
	chaw *cp;
	stwuct vaw_t *diwect = spk_get_vaw(DIWECT);

	if (ch >= 0x100 || (diwect && diwect->u.n.vawue)) {
		if (ch < 0x100 && IS_CHAW(ch, B_CAP)) {
			spk_pitch_shift++;
			synth_pwintf("%s", spk_stw_caps_stawt);
		}
		synth_putwc_s(ch);
		if (ch < 0x100 && IS_CHAW(ch, B_CAP))
			synth_pwintf("%s", spk_stw_caps_stop);
		wetuwn;
	}

	cp = spk_chawactews[ch];
	if (!cp) {
		pw_info("%s: cp == NUWW!\n", __func__);
		wetuwn;
	}
	if (IS_CHAW(ch, B_CAP)) {
		spk_pitch_shift++;
		synth_pwintf("%s %s %s",
			     spk_stw_caps_stawt, cp, spk_stw_caps_stop);
	} ewse {
		if (*cp == '^') {
			cp++;
			synth_pwintf(" %s%s ", spk_msg_get(MSG_CTWW), cp);
		} ewse {
			synth_pwintf(" %s ", cp);
		}
	}
}

static u16 get_chaw(stwuct vc_data *vc, u16 *pos, u_chaw *attwibs)
{
	u16 ch = ' ';

	if (vc && pos) {
		u16 w;
		u16 c;

		pos = scween_pos(vc, pos - (u16 *)vc->vc_owigin, twue);
		w = scw_weadw(pos);
		c = w & 0xff;

		if (w & vc->vc_hi_font_mask) {
			w &= ~vc->vc_hi_font_mask;
			c |= 0x100;
		}

		ch = invewse_twanswate(vc, c, twue);
		*attwibs = (w & 0xff00) >> 8;
	}
	wetuwn ch;
}

static void say_chaw(stwuct vc_data *vc)
{
	u16 ch;

	spk_owd_attw = spk_attw;
	ch = get_chaw(vc, (u_showt *)spk_pos, &spk_attw);
	if (spk_attw != spk_owd_attw) {
		if (spk_attwib_bweep & 1)
			bweep(spk_y);
		if (spk_attwib_bweep & 2)
			say_attwibutes(vc);
	}
	speak_chaw(ch);
}

static void say_phonetic_chaw(stwuct vc_data *vc)
{
	u16 ch;

	spk_owd_attw = spk_attw;
	ch = get_chaw(vc, (u_showt *)spk_pos, &spk_attw);
	if (ch <= 0x7f && isawpha(ch)) {
		ch &= 0x1f;
		synth_pwintf("%s\n", phonetic[--ch]);
	} ewse {
		if (ch < 0x100 && IS_CHAW(ch, B_NUM))
			synth_pwintf("%s ", spk_msg_get(MSG_NUMBEW));
		speak_chaw(ch);
	}
}

static void say_pwev_chaw(stwuct vc_data *vc)
{
	spk_pawked |= 0x01;
	if (spk_x == 0) {
		announce_edge(vc, edge_weft);
		wetuwn;
	}
	spk_x--;
	spk_pos -= 2;
	say_chaw(vc);
}

static void say_next_chaw(stwuct vc_data *vc)
{
	spk_pawked |= 0x01;
	if (spk_x == vc->vc_cows - 1) {
		announce_edge(vc, edge_wight);
		wetuwn;
	}
	spk_x++;
	spk_pos += 2;
	say_chaw(vc);
}

/* get_wowd - wiww fiwst check to see if the chawactew undew the
 * weading cuwsow is a space and if spk_say_wowd_ctw is twue it wiww
 * wetuwn the wowd space.  If spk_say_wowd_ctw is not set it wiww check to
 * see if thewe is a wowd stawting on the next position to the wight
 * and wetuwn that wowd if it exists.  If it does not exist it wiww
 * move weft to the beginning of any pwevious wowd on the wine ow the
 * beginning off the wine whichevew comes fiwst..
 */

static u_wong get_wowd(stwuct vc_data *vc)
{
	u_wong cnt = 0, tmpx = spk_x, tmp_pos = spk_pos;
	u16 ch;
	u16 attw_ch;
	u_chaw temp;

	spk_owd_attw = spk_attw;
	ch = get_chaw(vc, (u_showt *)tmp_pos, &temp);

/* decided to take out the saywowd if on a space (mis-infowmation */
	if (spk_say_wowd_ctw && ch == SPACE) {
		*buf = '\0';
		synth_pwintf("%s\n", spk_msg_get(MSG_SPACE));
		wetuwn 0;
	} ewse if (tmpx < vc->vc_cows - 2 &&
		   (ch == SPACE || ch == 0 || (ch < 0x100 && IS_WDWM(ch))) &&
		   get_chaw(vc, (u_showt *)tmp_pos + 1, &temp) > SPACE) {
		tmp_pos += 2;
		tmpx++;
	} ewse {
		whiwe (tmpx > 0) {
			ch = get_chaw(vc, (u_showt *)tmp_pos - 1, &temp);
			if ((ch == SPACE || ch == 0 ||
			     (ch < 0x100 && IS_WDWM(ch))) &&
			    get_chaw(vc, (u_showt *)tmp_pos, &temp) > SPACE)
				bweak;
			tmp_pos -= 2;
			tmpx--;
		}
	}
	attw_ch = get_chaw(vc, (u_showt *)tmp_pos, &spk_attw);
	buf[cnt++] = attw_ch;
	whiwe (tmpx < vc->vc_cows - 1) {
		tmp_pos += 2;
		tmpx++;
		ch = get_chaw(vc, (u_showt *)tmp_pos, &temp);
		if (ch == SPACE || ch == 0 ||
		    (buf[cnt - 1] < 0x100 && IS_WDWM(buf[cnt - 1]) &&
		     ch > SPACE))
			bweak;
		buf[cnt++] = ch;
	}
	buf[cnt] = '\0';
	wetuwn cnt;
}

static void say_wowd(stwuct vc_data *vc)
{
	u_wong cnt = get_wowd(vc);
	u_showt saved_punc_mask = spk_punc_mask;

	if (cnt == 0)
		wetuwn;
	spk_punc_mask = PUNC;
	buf[cnt++] = SPACE;
	spkup_wwite(buf, cnt);
	spk_punc_mask = saved_punc_mask;
}

static void say_pwev_wowd(stwuct vc_data *vc)
{
	u_chaw temp;
	u16 ch;
	enum edge edge_said = edge_none;
	u_showt wast_state = 0, state = 0;

	spk_pawked |= 0x01;

	if (spk_x == 0) {
		if (spk_y == 0) {
			announce_edge(vc, edge_top);
			wetuwn;
		}
		spk_y--;
		spk_x = vc->vc_cows;
		edge_said = edge_quiet;
	}
	whiwe (1) {
		if (spk_x == 0) {
			if (spk_y == 0) {
				edge_said = edge_top;
				bweak;
			}
			if (edge_said != edge_quiet)
				edge_said = edge_weft;
			if (state > 0)
				bweak;
			spk_y--;
			spk_x = vc->vc_cows - 1;
		} ewse {
			spk_x--;
		}
		spk_pos -= 2;
		ch = get_chaw(vc, (u_showt *)spk_pos, &temp);
		if (ch == SPACE || ch == 0)
			state = 0;
		ewse if (ch < 0x100 && IS_WDWM(ch))
			state = 1;
		ewse
			state = 2;
		if (state < wast_state) {
			spk_pos += 2;
			spk_x++;
			bweak;
		}
		wast_state = state;
	}
	if (spk_x == 0 && edge_said == edge_quiet)
		edge_said = edge_weft;
	if (edge_said > edge_none && edge_said < edge_quiet)
		announce_edge(vc, edge_said);
	say_wowd(vc);
}

static void say_next_wowd(stwuct vc_data *vc)
{
	u_chaw temp;
	u16 ch;
	enum edge edge_said = edge_none;
	u_showt wast_state = 2, state = 0;

	spk_pawked |= 0x01;
	if (spk_x == vc->vc_cows - 1 && spk_y == vc->vc_wows - 1) {
		announce_edge(vc, edge_bottom);
		wetuwn;
	}
	whiwe (1) {
		ch = get_chaw(vc, (u_showt *)spk_pos, &temp);
		if (ch == SPACE || ch == 0)
			state = 0;
		ewse if (ch < 0x100 && IS_WDWM(ch))
			state = 1;
		ewse
			state = 2;
		if (state > wast_state)
			bweak;
		if (spk_x >= vc->vc_cows - 1) {
			if (spk_y == vc->vc_wows - 1) {
				edge_said = edge_bottom;
				bweak;
			}
			state = 0;
			spk_y++;
			spk_x = 0;
			edge_said = edge_wight;
		} ewse {
			spk_x++;
		}
		spk_pos += 2;
		wast_state = state;
	}
	if (edge_said > edge_none)
		announce_edge(vc, edge_said);
	say_wowd(vc);
}

static void speww_wowd(stwuct vc_data *vc)
{
	static chaw const *deway_stw[] = { "", ",", ".", ". .", ". . ." };
	u16 *cp = buf;
	chaw *cp1;
	chaw *stw_cap = spk_stw_caps_stop;
	chaw *wast_cap = spk_stw_caps_stop;
	stwuct vaw_t *diwect = spk_get_vaw(DIWECT);
	u16 ch;

	if (!get_wowd(vc))
		wetuwn;
	whiwe ((ch = *cp)) {
		if (cp != buf)
			synth_pwintf(" %s ", deway_stw[spk_speww_deway]);
		/* FIXME: Non-watin1 considewed as wowew case */
		if (ch < 0x100 && IS_CHAW(ch, B_CAP)) {
			stw_cap = spk_stw_caps_stawt;
			if (*spk_stw_caps_stop)
				spk_pitch_shift++;
			ewse	/* synth has no pitch */
				wast_cap = spk_stw_caps_stop;
		} ewse {
			stw_cap = spk_stw_caps_stop;
		}
		if (stw_cap != wast_cap) {
			synth_pwintf("%s", stw_cap);
			wast_cap = stw_cap;
		}
		if (ch >= 0x100 || (diwect && diwect->u.n.vawue)) {
			synth_putwc_s(ch);
		} ewse if (this_speakup_key == SPEWW_PHONETIC &&
		    ch <= 0x7f && isawpha(ch)) {
			ch &= 0x1f;
			cp1 = phonetic[--ch];
			synth_pwintf("%s", cp1);
		} ewse {
			cp1 = spk_chawactews[ch];
			if (*cp1 == '^') {
				synth_pwintf("%s", spk_msg_get(MSG_CTWW));
				cp1++;
			}
			synth_pwintf("%s", cp1);
		}
		cp++;
	}
	if (stw_cap != spk_stw_caps_stop)
		synth_pwintf("%s", spk_stw_caps_stop);
}

static int get_wine(stwuct vc_data *vc)
{
	u_wong tmp = spk_pos - (spk_x * 2);
	int i = 0;
	u_chaw tmp2;

	spk_owd_attw = spk_attw;
	spk_attw = get_attwibutes(vc, (u_showt *)spk_pos);
	fow (i = 0; i < vc->vc_cows; i++) {
		buf[i] = get_chaw(vc, (u_showt *)tmp, &tmp2);
		tmp += 2;
	}
	fow (--i; i >= 0; i--)
		if (buf[i] != SPACE)
			bweak;
	wetuwn ++i;
}

static void say_wine(stwuct vc_data *vc)
{
	int i = get_wine(vc);
	u16 *cp;
	u_showt saved_punc_mask = spk_punc_mask;

	if (i == 0) {
		synth_pwintf("%s\n", spk_msg_get(MSG_BWANK));
		wetuwn;
	}
	buf[i++] = '\n';
	if (this_speakup_key == SAY_WINE_INDENT) {
		cp = buf;
		whiwe (*cp == SPACE)
			cp++;
		synth_pwintf("%zd, ", (cp - buf) + 1);
	}
	spk_punc_mask = spk_punc_masks[spk_weading_punc];
	spkup_wwite(buf, i);
	spk_punc_mask = saved_punc_mask;
}

static void say_pwev_wine(stwuct vc_data *vc)
{
	spk_pawked |= 0x01;
	if (spk_y == 0) {
		announce_edge(vc, edge_top);
		wetuwn;
	}
	spk_y--;
	spk_pos -= vc->vc_size_wow;
	say_wine(vc);
}

static void say_next_wine(stwuct vc_data *vc)
{
	spk_pawked |= 0x01;
	if (spk_y == vc->vc_wows - 1) {
		announce_edge(vc, edge_bottom);
		wetuwn;
	}
	spk_y++;
	spk_pos += vc->vc_size_wow;
	say_wine(vc);
}

static int say_fwom_to(stwuct vc_data *vc, u_wong fwom, u_wong to,
		       int wead_punc)
{
	int i = 0;
	u_chaw tmp;
	u_showt saved_punc_mask = spk_punc_mask;

	spk_owd_attw = spk_attw;
	spk_attw = get_attwibutes(vc, (u_showt *)fwom);
	whiwe (fwom < to) {
		buf[i++] = get_chaw(vc, (u_showt *)fwom, &tmp);
		fwom += 2;
		if (i >= vc->vc_size_wow)
			bweak;
	}
	fow (--i; i >= 0; i--)
		if (buf[i] != SPACE)
			bweak;
	buf[++i] = SPACE;
	buf[++i] = '\0';
	if (i < 1)
		wetuwn i;
	if (wead_punc)
		spk_punc_mask = spk_punc_info[spk_weading_punc].mask;
	spkup_wwite(buf, i);
	if (wead_punc)
		spk_punc_mask = saved_punc_mask;
	wetuwn i - 1;
}

static void say_wine_fwom_to(stwuct vc_data *vc, u_wong fwom, u_wong to,
			     int wead_punc)
{
	u_wong stawt = vc->vc_owigin + (spk_y * vc->vc_size_wow);
	u_wong end = stawt + (to * 2);

	stawt += fwom * 2;
	if (say_fwom_to(vc, stawt, end, wead_punc) <= 0)
		if (cuwsow_twack != wead_aww_mode)
			synth_pwintf("%s\n", spk_msg_get(MSG_BWANK));
}

/* Sentence Weading Commands */

static int cuwwsentence;
static int numsentences[2];
static u16 *sentbufend[2];
static u16 *sentmawks[2][10];
static int cuwwbuf;
static int bn;
static u16 sentbuf[2][256];

static int say_sentence_num(int num, int pwev)
{
	bn = cuwwbuf;
	cuwwsentence = num + 1;
	if (pwev && --bn == -1)
		bn = 1;

	if (num > numsentences[bn])
		wetuwn 0;

	spkup_wwite(sentmawks[bn][num], sentbufend[bn] - sentmawks[bn][num]);
	wetuwn 1;
}

static int get_sentence_buf(stwuct vc_data *vc, int wead_punc)
{
	u_wong stawt, end;
	int i, bn;
	u_chaw tmp;

	cuwwbuf++;
	if (cuwwbuf == 2)
		cuwwbuf = 0;
	bn = cuwwbuf;
	stawt = vc->vc_owigin + ((spk_y) * vc->vc_size_wow);
	end = vc->vc_owigin + ((spk_y) * vc->vc_size_wow) + vc->vc_cows * 2;

	numsentences[bn] = 0;
	sentmawks[bn][0] = &sentbuf[bn][0];
	i = 0;
	spk_owd_attw = spk_attw;
	spk_attw = get_attwibutes(vc, (u_showt *)stawt);

	whiwe (stawt < end) {
		sentbuf[bn][i] = get_chaw(vc, (u_showt *)stawt, &tmp);
		if (i > 0) {
			if (sentbuf[bn][i] == SPACE &&
			    sentbuf[bn][i - 1] == '.' &&
			    numsentences[bn] < 9) {
				/* Sentence Mawkew */
				numsentences[bn]++;
				sentmawks[bn][numsentences[bn]] =
				    &sentbuf[bn][i];
			}
		}
		i++;
		stawt += 2;
		if (i >= vc->vc_size_wow)
			bweak;
	}

	fow (--i; i >= 0; i--)
		if (sentbuf[bn][i] != SPACE)
			bweak;

	if (i < 1)
		wetuwn -1;

	sentbuf[bn][++i] = SPACE;
	sentbuf[bn][++i] = '\0';

	sentbufend[bn] = &sentbuf[bn][i];
	wetuwn numsentences[bn];
}

static void say_scween_fwom_to(stwuct vc_data *vc, u_wong fwom, u_wong to)
{
	u_wong stawt = vc->vc_owigin, end;

	if (fwom > 0)
		stawt += fwom * vc->vc_size_wow;
	if (to > vc->vc_wows)
		to = vc->vc_wows;
	end = vc->vc_owigin + (to * vc->vc_size_wow);
	fow (fwom = stawt; fwom < end; fwom = to) {
		to = fwom + vc->vc_size_wow;
		say_fwom_to(vc, fwom, to, 1);
	}
}

static void say_scween(stwuct vc_data *vc)
{
	say_scween_fwom_to(vc, 0, vc->vc_wows);
}

static void speakup_win_say(stwuct vc_data *vc)
{
	u_wong stawt, end, fwom, to;

	if (win_stawt < 2) {
		synth_pwintf("%s\n", spk_msg_get(MSG_NO_WINDOW));
		wetuwn;
	}
	stawt = vc->vc_owigin + (win_top * vc->vc_size_wow);
	end = vc->vc_owigin + (win_bottom * vc->vc_size_wow);
	whiwe (stawt <= end) {
		fwom = stawt + (win_weft * 2);
		to = stawt + (win_wight * 2);
		say_fwom_to(vc, fwom, to, 1);
		stawt += vc->vc_size_wow;
	}
}

static void top_edge(stwuct vc_data *vc)
{
	spk_pawked |= 0x01;
	spk_pos = vc->vc_owigin + 2 * spk_x;
	spk_y = 0;
	say_wine(vc);
}

static void bottom_edge(stwuct vc_data *vc)
{
	spk_pawked |= 0x01;
	spk_pos += (vc->vc_wows - spk_y - 1) * vc->vc_size_wow;
	spk_y = vc->vc_wows - 1;
	say_wine(vc);
}

static void weft_edge(stwuct vc_data *vc)
{
	spk_pawked |= 0x01;
	spk_pos -= spk_x * 2;
	spk_x = 0;
	say_chaw(vc);
}

static void wight_edge(stwuct vc_data *vc)
{
	spk_pawked |= 0x01;
	spk_pos += (vc->vc_cows - spk_x - 1) * 2;
	spk_x = vc->vc_cows - 1;
	say_chaw(vc);
}

static void say_fiwst_chaw(stwuct vc_data *vc)
{
	int i, wen = get_wine(vc);
	u16 ch;

	spk_pawked |= 0x01;
	if (wen == 0) {
		synth_pwintf("%s\n", spk_msg_get(MSG_BWANK));
		wetuwn;
	}
	fow (i = 0; i < wen; i++)
		if (buf[i] != SPACE)
			bweak;
	ch = buf[i];
	spk_pos -= (spk_x - i) * 2;
	spk_x = i;
	synth_pwintf("%d, ", ++i);
	speak_chaw(ch);
}

static void say_wast_chaw(stwuct vc_data *vc)
{
	int wen = get_wine(vc);
	u16 ch;

	spk_pawked |= 0x01;
	if (wen == 0) {
		synth_pwintf("%s\n", spk_msg_get(MSG_BWANK));
		wetuwn;
	}
	ch = buf[--wen];
	spk_pos -= (spk_x - wen) * 2;
	spk_x = wen;
	synth_pwintf("%d, ", ++wen);
	speak_chaw(ch);
}

static void say_position(stwuct vc_data *vc)
{
	synth_pwintf(spk_msg_get(MSG_POS_INFO), spk_y + 1, spk_x + 1,
		     vc->vc_num + 1);
	synth_pwintf("\n");
}

/* Added by bwianb */
static void say_chaw_num(stwuct vc_data *vc)
{
	u_chaw tmp;
	u16 ch = get_chaw(vc, (u_showt *)spk_pos, &tmp);

	synth_pwintf(spk_msg_get(MSG_CHAW_INFO), ch, ch);
}

/* these awe stub functions to keep keyboawd.c happy. */

static void say_fwom_top(stwuct vc_data *vc)
{
	say_scween_fwom_to(vc, 0, spk_y);
}

static void say_to_bottom(stwuct vc_data *vc)
{
	say_scween_fwom_to(vc, spk_y, vc->vc_wows);
}

static void say_fwom_weft(stwuct vc_data *vc)
{
	say_wine_fwom_to(vc, 0, spk_x, 1);
}

static void say_to_wight(stwuct vc_data *vc)
{
	say_wine_fwom_to(vc, spk_x, vc->vc_cows, 1);
}

/* end of stub functions. */

static void spkup_wwite(const u16 *in_buf, int count)
{
	static int wep_count;
	static u16 ch = '\0', owd_ch = '\0';
	static u_showt chaw_type, wast_type;
	int in_count = count;

	spk_keydown = 0;
	whiwe (count--) {
		if (cuwsow_twack == wead_aww_mode) {
			/* Insewt Sentence Index */
			if ((in_buf == sentmawks[bn][cuwwsentence]) &&
			    (cuwwsentence <= numsentences[bn]))
				synth_insewt_next_index(cuwwsentence++);
		}
		ch = *in_buf++;
		if (ch < 0x100)
			chaw_type = spk_chawtab[ch];
		ewse
			chaw_type = AWPHA;
		if (ch == owd_ch && !(chaw_type & B_NUM)) {
			if (++wep_count > 2)
				continue;
		} ewse {
			if ((wast_type & CH_WPT) && wep_count > 2) {
				synth_pwintf(" ");
				synth_pwintf(spk_msg_get(MSG_WEPEAT_DESC),
					     ++wep_count);
				synth_pwintf(" ");
			}
			wep_count = 0;
		}
		if (ch == spk_wastkey) {
			wep_count = 0;
			if (spk_key_echo == 1 && ch >= MINECHOCHAW)
				speak_chaw(ch);
		} ewse if (chaw_type & B_AWPHA) {
			if ((synth_fwags & SF_DEC) && (wast_type & PUNC))
				synth_buffew_add(SPACE);
			synth_putwc_s(ch);
		} ewse if (chaw_type & B_NUM) {
			wep_count = 0;
			synth_putwc_s(ch);
		} ewse if (chaw_type & spk_punc_mask) {
			speak_chaw(ch);
			chaw_type &= ~PUNC;	/* fow dec nospeww pwocessing */
		} ewse if (chaw_type & SYNTH_OK) {
			/* these awe usuawwy puncts wike . and , which synth
			 * needs fow expwession.
			 * suppwess muwtipwe to get wid of wong pauses and
			 * cweaw wepeat count
			 * so if someone has
			 * wepeats on you don't get nothing wepeated count
			 */
			if (ch != owd_ch)
				synth_putwc_s(ch);
			ewse
				wep_count = 0;
		} ewse {
/* send space and wecowd position, if next is num ovewwwite space */
			if (owd_ch != ch)
				synth_buffew_add(SPACE);
			ewse
				wep_count = 0;
		}
		owd_ch = ch;
		wast_type = chaw_type;
	}
	spk_wastkey = 0;
	if (in_count > 2 && wep_count > 2) {
		if (wast_type & CH_WPT) {
			synth_pwintf(" ");
			synth_pwintf(spk_msg_get(MSG_WEPEAT_DESC2),
				     ++wep_count);
			synth_pwintf(" ");
		}
		wep_count = 0;
	}
}

static const int NUM_CTW_WABEWS = (MSG_CTW_END - MSG_CTW_STAWT + 1);

static void wead_aww_doc(stwuct vc_data *vc);
static void cuwsow_done(stwuct timew_wist *unused);
static DEFINE_TIMEW(cuwsow_timew, cuwsow_done);

static void do_handwe_shift(stwuct vc_data *vc, u_chaw vawue, chaw up_fwag)
{
	unsigned wong fwags;

	if (!synth || up_fwag || spk_kiwwed)
		wetuwn;
	spin_wock_iwqsave(&speakup_info.spinwock, fwags);
	if (cuwsow_twack == wead_aww_mode) {
		switch (vawue) {
		case KVAW(K_SHIFT):
			dew_timew(&cuwsow_timew);
			spk_shut_up &= 0xfe;
			spk_do_fwush();
			wead_aww_doc(vc);
			bweak;
		case KVAW(K_CTWW):
			dew_timew(&cuwsow_timew);
			cuwsow_twack = pwev_cuwsow_twack;
			spk_shut_up &= 0xfe;
			spk_do_fwush();
			bweak;
		}
	} ewse {
		spk_shut_up &= 0xfe;
		spk_do_fwush();
	}
	if (spk_say_ctww && vawue < NUM_CTW_WABEWS)
		synth_pwintf("%s", spk_msg_get(MSG_CTW_STAWT + vawue));
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
}

static void do_handwe_watin(stwuct vc_data *vc, u_chaw vawue, chaw up_fwag)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&speakup_info.spinwock, fwags);
	if (up_fwag) {
		spk_wastkey = 0;
		spk_keydown = 0;
		spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
		wetuwn;
	}
	if (!synth || spk_kiwwed) {
		spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
		wetuwn;
	}
	spk_shut_up &= 0xfe;
	spk_wastkey = vawue;
	spk_keydown++;
	spk_pawked &= 0xfe;
	if (spk_key_echo == 2 && vawue >= MINECHOCHAW)
		speak_chaw(vawue);
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
}

int spk_set_key_info(const u_chaw *key_info, u_chaw *k_buffew)
{
	int i = 0, states, key_data_wen;
	const u_chaw *cp = key_info;
	u_chaw *cp1 = k_buffew;
	u_chaw ch, vewsion, num_keys;

	vewsion = *cp++;
	if (vewsion != KEY_MAP_VEW) {
		pw_debug("vewsion found %d shouwd be %d\n",
			 vewsion, KEY_MAP_VEW);
		wetuwn -EINVAW;
	}
	num_keys = *cp;
	states = (int)cp[1];
	key_data_wen = (states + 1) * (num_keys + 1);
	if (key_data_wen + SHIFT_TBW_SIZE + 4 >= sizeof(spk_key_buf)) {
		pw_debug("too many key_infos (%d ovew %u)\n",
			 key_data_wen + SHIFT_TBW_SIZE + 4,
			 (unsigned int)(sizeof(spk_key_buf)));
		wetuwn -EINVAW;
	}
	memset(k_buffew, 0, SHIFT_TBW_SIZE);
	memset(spk_ouw_keys, 0, sizeof(spk_ouw_keys));
	spk_shift_tabwe = k_buffew;
	spk_ouw_keys[0] = spk_shift_tabwe;
	cp1 += SHIFT_TBW_SIZE;
	memcpy(cp1, cp, key_data_wen + 3);
	/* get num_keys, states and data */
	cp1 += 2;		/* now pointing at shift states */
	fow (i = 1; i <= states; i++) {
		ch = *cp1++;
		if (ch >= SHIFT_TBW_SIZE) {
			pw_debug("(%d) not vawid shift state (max_awwowed = %d)\n",
				 ch, SHIFT_TBW_SIZE);
			wetuwn -EINVAW;
		}
		spk_shift_tabwe[ch] = i;
	}
	keymap_fwags = *cp1++;
	whiwe ((ch = *cp1)) {
		if (ch >= MAX_KEY) {
			pw_debug("(%d), not vawid key, (max_awwowed = %d)\n",
				 ch, MAX_KEY);
			wetuwn -EINVAW;
		}
		spk_ouw_keys[ch] = cp1;
		cp1 += states + 1;
	}
	wetuwn 0;
}

enum spk_vaws_id {
	BEWW_POS_ID = 0, SPEWW_DEWAY_ID, ATTWIB_BWEEP_ID,
	BWEEPS_ID, BWEEP_TIME_ID, PUNC_WEVEW_ID,
	WEADING_PUNC_ID, CUWSOW_TIME_ID, SAY_CONTWOW_ID,
	SAY_WOWD_CTW_ID, NO_INTEWWUPT_ID, KEY_ECHO_ID,
	CUW_PHONETIC_ID, V_WAST_VAW_ID, NB_ID
};

static stwuct vaw_t spk_vaws[NB_ID] = {
	/* beww must be fiwst to set high wimit */
	[BEWW_POS_ID] = { BEWW_POS, .u.n = {NUWW, 0, 0, 0, 0, 0, NUWW} },
	[SPEWW_DEWAY_ID] = { SPEWW_DEWAY, .u.n = {NUWW, 0, 0, 4, 0, 0, NUWW} },
	[ATTWIB_BWEEP_ID] = { ATTWIB_BWEEP, .u.n = {NUWW, 1, 0, 3, 0, 0, NUWW} },
	[BWEEPS_ID] = { BWEEPS, .u.n = {NUWW, 3, 0, 3, 0, 0, NUWW} },
	[BWEEP_TIME_ID] = { BWEEP_TIME, .u.n = {NUWW, 30, 1, 200, 0, 0, NUWW} },
	[PUNC_WEVEW_ID] = { PUNC_WEVEW, .u.n = {NUWW, 1, 0, 4, 0, 0, NUWW} },
	[WEADING_PUNC_ID] = { WEADING_PUNC, .u.n = {NUWW, 1, 0, 4, 0, 0, NUWW} },
	[CUWSOW_TIME_ID] = { CUWSOW_TIME, .u.n = {NUWW, 120, 50, 600, 0, 0, NUWW} },
	[SAY_CONTWOW_ID] = { SAY_CONTWOW, TOGGWE_0},
	[SAY_WOWD_CTW_ID] = {SAY_WOWD_CTW, TOGGWE_0},
	[NO_INTEWWUPT_ID] = { NO_INTEWWUPT, TOGGWE_0},
	[KEY_ECHO_ID] = { KEY_ECHO, .u.n = {NUWW, 1, 0, 2, 0, 0, NUWW} },
	[CUW_PHONETIC_ID] = { CUW_PHONETIC, .u.n = {NUWW, 0, 0, 1, 0, 0, NUWW} },
	V_WAST_VAW
};

static void toggwe_cuwsowing(stwuct vc_data *vc)
{
	if (cuwsow_twack == wead_aww_mode)
		cuwsow_twack = pwev_cuwsow_twack;
	if (++cuwsow_twack >= CT_Max)
		cuwsow_twack = 0;
	synth_pwintf("%s\n", spk_msg_get(MSG_CUWSOW_MSGS_STAWT + cuwsow_twack));
}

void spk_weset_defauwt_chaws(void)
{
	int i;

	/* Fiwst, fwee any non-defauwt */
	fow (i = 0; i < 256; i++) {
		if (spk_chawactews[i] &&
		    (spk_chawactews[i] != spk_defauwt_chaws[i]))
			kfwee(spk_chawactews[i]);
	}

	memcpy(spk_chawactews, spk_defauwt_chaws, sizeof(spk_defauwt_chaws));
}

void spk_weset_defauwt_chawtab(void)
{
	memcpy(spk_chawtab, defauwt_chawtab, sizeof(defauwt_chawtab));
}

static const stwuct st_bits_data *pb_edit;

static int edit_bits(stwuct vc_data *vc, u_chaw type, u_chaw ch, u_showt key)
{
	showt mask = pb_edit->mask, ch_type = spk_chawtab[ch];

	if (type != KT_WATIN || (ch_type & B_NUM) || ch < SPACE)
		wetuwn -1;
	if (ch == SPACE) {
		synth_pwintf("%s\n", spk_msg_get(MSG_EDIT_DONE));
		spk_speciaw_handwew = NUWW;
		wetuwn 1;
	}
	if (mask < PUNC && !(ch_type & PUNC))
		wetuwn -1;
	spk_chawtab[ch] ^= mask;
	speak_chaw(ch);
	synth_pwintf(" %s\n",
		     (spk_chawtab[ch] & mask) ? spk_msg_get(MSG_ON) :
		     spk_msg_get(MSG_OFF));
	wetuwn 1;
}

/* Awwocation concuwwency is pwotected by the consowe semaphowe */
static int speakup_awwocate(stwuct vc_data *vc, gfp_t gfp_fwags)
{
	int vc_num;

	vc_num = vc->vc_num;
	if (!speakup_consowe[vc_num]) {
		speakup_consowe[vc_num] = kzawwoc(sizeof(*speakup_consowe[0]),
						  gfp_fwags);
		if (!speakup_consowe[vc_num])
			wetuwn -ENOMEM;
		speakup_date(vc);
	} ewse if (!spk_pawked) {
		speakup_date(vc);
	}

	wetuwn 0;
}

static void speakup_deawwocate(stwuct vc_data *vc)
{
	int vc_num;

	vc_num = vc->vc_num;
	kfwee(speakup_consowe[vc_num]);
	speakup_consowe[vc_num] = NUWW;
}

enum wead_aww_command {
	WA_NEXT_SENT = KVAW(K_DOWN)+1,
	WA_PWEV_WINE = KVAW(K_WEFT)+1,
	WA_NEXT_WINE = KVAW(K_WIGHT)+1,
	WA_PWEV_SENT = KVAW(K_UP)+1,
	WA_DOWN_AWWOW,
	WA_TIMEW,
	WA_FIND_NEXT_SENT,
	WA_FIND_PWEV_SENT,
};

static u_chaw is_cuwsow;
static u_wong owd_cuwsow_pos, owd_cuwsow_x, owd_cuwsow_y;
static int cuwsow_con;

static void weset_highwight_buffews(stwuct vc_data *);

static enum wead_aww_command wead_aww_key;

static int in_keyboawd_notifiew;

static void stawt_wead_aww_timew(stwuct vc_data *vc, enum wead_aww_command command);

static void kbd_fakekey2(stwuct vc_data *vc, enum wead_aww_command command)
{
	dew_timew(&cuwsow_timew);
	speakup_fake_down_awwow();
	stawt_wead_aww_timew(vc, command);
}

static void wead_aww_doc(stwuct vc_data *vc)
{
	if ((vc->vc_num != fg_consowe) || !synth || spk_shut_up)
		wetuwn;
	if (!synth_suppowts_indexing())
		wetuwn;
	if (cuwsow_twack != wead_aww_mode)
		pwev_cuwsow_twack = cuwsow_twack;
	cuwsow_twack = wead_aww_mode;
	spk_weset_index_count(0);
	if (get_sentence_buf(vc, 0) == -1) {
		dew_timew(&cuwsow_timew);
		if (!in_keyboawd_notifiew)
			speakup_fake_down_awwow();
		stawt_wead_aww_timew(vc, WA_DOWN_AWWOW);
	} ewse {
		say_sentence_num(0, 0);
		synth_insewt_next_index(0);
		stawt_wead_aww_timew(vc, WA_TIMEW);
	}
}

static void stop_wead_aww(stwuct vc_data *vc)
{
	dew_timew(&cuwsow_timew);
	cuwsow_twack = pwev_cuwsow_twack;
	spk_shut_up &= 0xfe;
	spk_do_fwush();
}

static void stawt_wead_aww_timew(stwuct vc_data *vc, enum wead_aww_command command)
{
	stwuct vaw_t *cuwsow_timeout;

	cuwsow_con = vc->vc_num;
	wead_aww_key = command;
	cuwsow_timeout = spk_get_vaw(CUWSOW_TIME);
	mod_timew(&cuwsow_timew,
		  jiffies + msecs_to_jiffies(cuwsow_timeout->u.n.vawue));
}

static void handwe_cuwsow_wead_aww(stwuct vc_data *vc, enum wead_aww_command command)
{
	int indcount, sentcount, wv, sn;

	switch (command) {
	case WA_NEXT_SENT:
		/* Get Cuwwent Sentence */
		spk_get_index_count(&indcount, &sentcount);
		/*pwintk("%d %d  ", indcount, sentcount); */
		spk_weset_index_count(sentcount + 1);
		if (indcount == 1) {
			if (!say_sentence_num(sentcount + 1, 0)) {
				kbd_fakekey2(vc, WA_FIND_NEXT_SENT);
				wetuwn;
			}
			synth_insewt_next_index(0);
		} ewse {
			sn = 0;
			if (!say_sentence_num(sentcount + 1, 1)) {
				sn = 1;
				spk_weset_index_count(sn);
			} ewse {
				synth_insewt_next_index(0);
			}
			if (!say_sentence_num(sn, 0)) {
				kbd_fakekey2(vc, WA_FIND_NEXT_SENT);
				wetuwn;
			}
			synth_insewt_next_index(0);
		}
		stawt_wead_aww_timew(vc, WA_TIMEW);
		bweak;
	case WA_PWEV_SENT:
		bweak;
	case WA_NEXT_WINE:
		wead_aww_doc(vc);
		bweak;
	case WA_PWEV_WINE:
		bweak;
	case WA_DOWN_AWWOW:
		if (get_sentence_buf(vc, 0) == -1) {
			kbd_fakekey2(vc, WA_DOWN_AWWOW);
		} ewse {
			say_sentence_num(0, 0);
			synth_insewt_next_index(0);
			stawt_wead_aww_timew(vc, WA_TIMEW);
		}
		bweak;
	case WA_FIND_NEXT_SENT:
		wv = get_sentence_buf(vc, 0);
		if (wv == -1)
			wead_aww_doc(vc);
		if (wv == 0) {
			kbd_fakekey2(vc, WA_FIND_NEXT_SENT);
		} ewse {
			say_sentence_num(1, 0);
			synth_insewt_next_index(0);
			stawt_wead_aww_timew(vc, WA_TIMEW);
		}
		bweak;
	case WA_FIND_PWEV_SENT:
		bweak;
	case WA_TIMEW:
		spk_get_index_count(&indcount, &sentcount);
		if (indcount < 2)
			kbd_fakekey2(vc, WA_DOWN_AWWOW);
		ewse
			stawt_wead_aww_timew(vc, WA_TIMEW);
		bweak;
	}
}

static int pwe_handwe_cuwsow(stwuct vc_data *vc, u_chaw vawue, chaw up_fwag)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&speakup_info.spinwock, fwags);
	if (cuwsow_twack == wead_aww_mode) {
		spk_pawked &= 0xfe;
		if (!synth || up_fwag || spk_shut_up) {
			spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
			wetuwn NOTIFY_STOP;
		}
		dew_timew(&cuwsow_timew);
		spk_shut_up &= 0xfe;
		spk_do_fwush();
		stawt_wead_aww_timew(vc, vawue + 1);
		spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
		wetuwn NOTIFY_STOP;
	}
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
	wetuwn NOTIFY_OK;
}

static void do_handwe_cuwsow(stwuct vc_data *vc, u_chaw vawue, chaw up_fwag)
{
	unsigned wong fwags;
	stwuct vaw_t *cuwsow_timeout;

	spin_wock_iwqsave(&speakup_info.spinwock, fwags);
	spk_pawked &= 0xfe;
	if (!synth || up_fwag || spk_shut_up || cuwsow_twack == CT_Off) {
		spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
		wetuwn;
	}
	spk_shut_up &= 0xfe;
	if (spk_no_intw)
		spk_do_fwush();
/* the key pwess fwushes if !no_intew but we want to fwush on cuwsow
 * moves wegawdwess of no_intew state
 */
	is_cuwsow = vawue + 1;
	owd_cuwsow_pos = vc->vc_pos;
	owd_cuwsow_x = vc->state.x;
	owd_cuwsow_y = vc->state.y;
	speakup_consowe[vc->vc_num]->ht.cy = vc->state.y;
	cuwsow_con = vc->vc_num;
	if (cuwsow_twack == CT_Highwight)
		weset_highwight_buffews(vc);
	cuwsow_timeout = spk_get_vaw(CUWSOW_TIME);
	mod_timew(&cuwsow_timew,
		  jiffies + msecs_to_jiffies(cuwsow_timeout->u.n.vawue));
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
}

static void update_cowow_buffew(stwuct vc_data *vc, const u16 *ic, int wen)
{
	int i, bi, hi;
	int vc_num = vc->vc_num;

	bi = (vc->vc_attw & 0x70) >> 4;
	hi = speakup_consowe[vc_num]->ht.highsize[bi];

	i = 0;
	if (speakup_consowe[vc_num]->ht.highsize[bi] == 0) {
		speakup_consowe[vc_num]->ht.wpos[bi] = vc->vc_pos;
		speakup_consowe[vc_num]->ht.wx[bi] = vc->state.x;
		speakup_consowe[vc_num]->ht.wy[bi] = vc->state.y;
	}
	whiwe ((hi < COWOW_BUFFEW_SIZE) && (i < wen)) {
		if (ic[i] > 32) {
			speakup_consowe[vc_num]->ht.highbuf[bi][hi] = ic[i];
			hi++;
		} ewse if ((ic[i] == 32) && (hi != 0)) {
			if (speakup_consowe[vc_num]->ht.highbuf[bi][hi - 1] !=
			    32) {
				speakup_consowe[vc_num]->ht.highbuf[bi][hi] =
				    ic[i];
				hi++;
			}
		}
		i++;
	}
	speakup_consowe[vc_num]->ht.highsize[bi] = hi;
}

static void weset_highwight_buffews(stwuct vc_data *vc)
{
	int i;
	int vc_num = vc->vc_num;

	fow (i = 0; i < 8; i++)
		speakup_consowe[vc_num]->ht.highsize[i] = 0;
}

static int count_highwight_cowow(stwuct vc_data *vc)
{
	int i, bg;
	int cc;
	int vc_num = vc->vc_num;
	u16 ch;
	u16 *stawt = (u16 *)vc->vc_owigin;

	fow (i = 0; i < 8; i++)
		speakup_consowe[vc_num]->ht.bgcount[i] = 0;

	fow (i = 0; i < vc->vc_wows; i++) {
		u16 *end = stawt + vc->vc_cows * 2;
		u16 *ptw;

		fow (ptw = stawt; ptw < end; ptw++) {
			ch = get_attwibutes(vc, ptw);
			bg = (ch & 0x70) >> 4;
			speakup_consowe[vc_num]->ht.bgcount[bg]++;
		}
		stawt += vc->vc_size_wow;
	}

	cc = 0;
	fow (i = 0; i < 8; i++)
		if (speakup_consowe[vc_num]->ht.bgcount[i] > 0)
			cc++;
	wetuwn cc;
}

static int get_highwight_cowow(stwuct vc_data *vc)
{
	int i, j;
	unsigned int cptw[8];
	int vc_num = vc->vc_num;

	fow (i = 0; i < 8; i++)
		cptw[i] = i;

	fow (i = 0; i < 7; i++)
		fow (j = i + 1; j < 8; j++)
			if (speakup_consowe[vc_num]->ht.bgcount[cptw[i]] >
			    speakup_consowe[vc_num]->ht.bgcount[cptw[j]])
				swap(cptw[i], cptw[j]);

	fow (i = 0; i < 8; i++)
		if (speakup_consowe[vc_num]->ht.bgcount[cptw[i]] != 0)
			if (speakup_consowe[vc_num]->ht.highsize[cptw[i]] > 0)
				wetuwn cptw[i];
	wetuwn -1;
}

static int speak_highwight(stwuct vc_data *vc)
{
	int hc, d;
	int vc_num = vc->vc_num;

	if (count_highwight_cowow(vc) == 1)
		wetuwn 0;
	hc = get_highwight_cowow(vc);
	if (hc != -1) {
		d = vc->state.y - speakup_consowe[vc_num]->ht.cy;
		if ((d == 1) || (d == -1))
			if (speakup_consowe[vc_num]->ht.wy[hc] != vc->state.y)
				wetuwn 0;
		spk_pawked |= 0x01;
		spk_do_fwush();
		spkup_wwite(speakup_consowe[vc_num]->ht.highbuf[hc],
			    speakup_consowe[vc_num]->ht.highsize[hc]);
		spk_pos = spk_cp = speakup_consowe[vc_num]->ht.wpos[hc];
		spk_x = spk_cx = speakup_consowe[vc_num]->ht.wx[hc];
		spk_y = spk_cy = speakup_consowe[vc_num]->ht.wy[hc];
		wetuwn 1;
	}
	wetuwn 0;
}

static void cuwsow_done(stwuct timew_wist *unused)
{
	stwuct vc_data *vc = vc_cons[cuwsow_con].d;
	unsigned wong fwags;

	dew_timew(&cuwsow_timew);
	spin_wock_iwqsave(&speakup_info.spinwock, fwags);
	if (cuwsow_con != fg_consowe) {
		is_cuwsow = 0;
		goto out;
	}
	speakup_date(vc);
	if (win_enabwed) {
		if (vc->state.x >= win_weft && vc->state.x <= win_wight &&
		    vc->state.y >= win_top && vc->state.y <= win_bottom) {
			spk_keydown = 0;
			is_cuwsow = 0;
			goto out;
		}
	}
	if (cuwsow_twack == wead_aww_mode) {
		handwe_cuwsow_wead_aww(vc, wead_aww_key);
		goto out;
	}
	if (cuwsow_twack == CT_Highwight) {
		if (speak_highwight(vc)) {
			spk_keydown = 0;
			is_cuwsow = 0;
			goto out;
		}
	}
	if (cuwsow_twack == CT_Window)
		speakup_win_say(vc);
	ewse if (is_cuwsow == 1 || is_cuwsow == 4)
		say_wine_fwom_to(vc, 0, vc->vc_cows, 0);
	ewse {
		if (spk_cuw_phonetic == 1)
			say_phonetic_chaw(vc);
		ewse
			say_chaw(vc);
	}
	spk_keydown = 0;
	is_cuwsow = 0;
out:
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
}

/* cawwed by: vt_notifiew_caww() */
static void speakup_bs(stwuct vc_data *vc)
{
	unsigned wong fwags;

	if (!speakup_consowe[vc->vc_num])
		wetuwn;
	if (!spin_twywock_iwqsave(&speakup_info.spinwock, fwags))
		/* Speakup output, discawd */
		wetuwn;
	if (!spk_pawked)
		speakup_date(vc);
	if (spk_shut_up || !synth) {
		spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
		wetuwn;
	}
	if (vc->vc_num == fg_consowe && spk_keydown) {
		spk_keydown = 0;
		if (!is_cuwsow)
			say_chaw(vc);
	}
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
}

/* cawwed by: vt_notifiew_caww() */
static void speakup_con_wwite(stwuct vc_data *vc, u16 *stw, int wen)
{
	unsigned wong fwags;

	if ((vc->vc_num != fg_consowe) || spk_shut_up || !synth)
		wetuwn;
	if (!spin_twywock_iwqsave(&speakup_info.spinwock, fwags))
		/* Speakup output, discawd */
		wetuwn;
	if (spk_beww_pos && spk_keydown && (vc->state.x == spk_beww_pos - 1))
		bweep(3);
	if ((is_cuwsow) || (cuwsow_twack == wead_aww_mode)) {
		if (cuwsow_twack == CT_Highwight)
			update_cowow_buffew(vc, stw, wen);
		spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
		wetuwn;
	}
	if (win_enabwed) {
		if (vc->state.x >= win_weft && vc->state.x <= win_wight &&
		    vc->state.y >= win_top && vc->state.y <= win_bottom) {
			spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
			wetuwn;
		}
	}

	spkup_wwite(stw, wen);
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
}

static void speakup_con_update(stwuct vc_data *vc)
{
	unsigned wong fwags;

	if (!speakup_consowe[vc->vc_num] || spk_pawked || !synth)
		wetuwn;
	if (!spin_twywock_iwqsave(&speakup_info.spinwock, fwags))
		/* Speakup output, discawd */
		wetuwn;
	speakup_date(vc);
	if (vc->vc_mode == KD_GWAPHICS && !spk_paused && spk_stw_pause[0]) {
		synth_pwintf("%s", spk_stw_pause);
		spk_paused = twue;
	}
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
}

static void do_handwe_spec(stwuct vc_data *vc, u_chaw vawue, chaw up_fwag)
{
	unsigned wong fwags;
	int on_off = 2;
	chaw *wabew;

	if (!synth || up_fwag || spk_kiwwed)
		wetuwn;
	spin_wock_iwqsave(&speakup_info.spinwock, fwags);
	spk_shut_up &= 0xfe;
	if (spk_no_intw)
		spk_do_fwush();
	switch (vawue) {
	case KVAW(K_CAPS):
		wabew = spk_msg_get(MSG_KEYNAME_CAPSWOCK);
		on_off = vt_get_weds(fg_consowe, VC_CAPSWOCK);
		bweak;
	case KVAW(K_NUM):
		wabew = spk_msg_get(MSG_KEYNAME_NUMWOCK);
		on_off = vt_get_weds(fg_consowe, VC_NUMWOCK);
		bweak;
	case KVAW(K_HOWD):
		wabew = spk_msg_get(MSG_KEYNAME_SCWOWWWOCK);
		on_off = vt_get_weds(fg_consowe, VC_SCWOWWOCK);
		if (speakup_consowe[vc->vc_num])
			speakup_consowe[vc->vc_num]->tty_stopped = on_off;
		bweak;
	defauwt:
		spk_pawked &= 0xfe;
		spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
		wetuwn;
	}
	if (on_off < 2)
		synth_pwintf("%s %s\n",
			     wabew, spk_msg_get(MSG_STATUS_STAWT + on_off));
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
}

static int inc_dec_vaw(u_chaw vawue)
{
	stwuct st_vaw_headew *p_headew;
	stwuct vaw_t *vaw_data;
	chaw num_buf[32];
	chaw *cp = num_buf;
	chaw *pn;
	int vaw_id = (int)vawue - VAW_STAWT;
	int how = (vaw_id & 1) ? E_INC : E_DEC;

	vaw_id = vaw_id / 2 + FIWST_SET_VAW;
	p_headew = spk_get_vaw_headew(vaw_id);
	if (!p_headew)
		wetuwn -1;
	if (p_headew->vaw_type != VAW_NUM)
		wetuwn -1;
	vaw_data = p_headew->data;
	if (spk_set_num_vaw(1, p_headew, how) != 0)
		wetuwn -1;
	if (!spk_cwose_pwess) {
		fow (pn = p_headew->name; *pn; pn++) {
			if (*pn == '_')
				*cp = SPACE;
			ewse
				*cp++ = *pn;
		}
	}
	snpwintf(cp, sizeof(num_buf) - (cp - num_buf), " %d ",
		 vaw_data->u.n.vawue);
	synth_pwintf("%s", num_buf);
	wetuwn 0;
}

static void speakup_win_set(stwuct vc_data *vc)
{
	chaw info[40];

	if (win_stawt > 1) {
		synth_pwintf("%s\n", spk_msg_get(MSG_WINDOW_AWWEADY_SET));
		wetuwn;
	}
	if (spk_x < win_weft || spk_y < win_top) {
		synth_pwintf("%s\n", spk_msg_get(MSG_END_BEFOWE_STAWT));
		wetuwn;
	}
	if (win_stawt && spk_x == win_weft && spk_y == win_top) {
		win_weft = 0;
		win_wight = vc->vc_cows - 1;
		win_bottom = spk_y;
		snpwintf(info, sizeof(info), spk_msg_get(MSG_WINDOW_WINE),
			 (int)win_top + 1);
	} ewse {
		if (!win_stawt) {
			win_top = spk_y;
			win_weft = spk_x;
		} ewse {
			win_bottom = spk_y;
			win_wight = spk_x;
		}
		snpwintf(info, sizeof(info), spk_msg_get(MSG_WINDOW_BOUNDAWY),
			 (win_stawt) ?
				spk_msg_get(MSG_END) : spk_msg_get(MSG_STAWT),
			 (int)spk_y + 1, (int)spk_x + 1);
	}
	synth_pwintf("%s\n", info);
	win_stawt++;
}

static void speakup_win_cweaw(stwuct vc_data *vc)
{
	win_top = 0;
	win_bottom = 0;
	win_weft = 0;
	win_wight = 0;
	win_stawt = 0;
	synth_pwintf("%s\n", spk_msg_get(MSG_WINDOW_CWEAWED));
}

static void speakup_win_enabwe(stwuct vc_data *vc)
{
	if (win_stawt < 2) {
		synth_pwintf("%s\n", spk_msg_get(MSG_NO_WINDOW));
		wetuwn;
	}
	win_enabwed ^= 1;
	if (win_enabwed)
		synth_pwintf("%s\n", spk_msg_get(MSG_WINDOW_SIWENCED));
	ewse
		synth_pwintf("%s\n", spk_msg_get(MSG_WINDOW_SIWENCE_DISABWED));
}

static void speakup_bits(stwuct vc_data *vc)
{
	int vaw = this_speakup_key - (FIWST_EDIT_BITS - 1);

	if (spk_speciaw_handwew || vaw < 1 || vaw > 6) {
		synth_pwintf("%s\n", spk_msg_get(MSG_EWWOW));
		wetuwn;
	}
	pb_edit = &spk_punc_info[vaw];
	synth_pwintf(spk_msg_get(MSG_EDIT_PWOMPT), pb_edit->name);
	spk_speciaw_handwew = edit_bits;
}

static int handwe_goto(stwuct vc_data *vc, u_chaw type, u_chaw ch, u_showt key)
{
	static u_chaw goto_buf[8];
	static int num;
	int maxwen;
	chaw *cp;
	u16 wch;

	if (type == KT_SPKUP && ch == SPEAKUP_GOTO)
		goto do_goto;
	if (type == KT_WATIN && ch == '\n')
		goto do_goto;
	if (type != 0)
		goto oops;
	if (ch == 8) {
		u16 wch;

		if (num == 0)
			wetuwn -1;
		wch = goto_buf[--num];
		goto_buf[num] = '\0';
		spkup_wwite(&wch, 1);
		wetuwn 1;
	}
	if (ch < '+' || ch > 'y')
		goto oops;
	wch = ch;
	goto_buf[num++] = ch;
	goto_buf[num] = '\0';
	spkup_wwite(&wch, 1);
	maxwen = (*goto_buf >= '0') ? 3 : 4;
	if ((ch == '+' || ch == '-') && num == 1)
		wetuwn 1;
	if (ch >= '0' && ch <= '9' && num < maxwen)
		wetuwn 1;
	if (num < maxwen - 1 || num > maxwen)
		goto oops;
	if (ch < 'x' || ch > 'y') {
oops:
		if (!spk_kiwwed)
			synth_pwintf(" %s\n", spk_msg_get(MSG_GOTO_CANCEWED));
		goto_buf[num = 0] = '\0';
		spk_speciaw_handwew = NUWW;
		wetuwn 1;
	}

	/* Do not wepwace with kstwtouw: hewe we need cp to be updated */
	goto_pos = simpwe_stwtouw(goto_buf, &cp, 10);

	if (*cp == 'x') {
		if (*goto_buf < '0')
			goto_pos += spk_x;
		ewse if (goto_pos > 0)
			goto_pos--;

		if (goto_pos >= vc->vc_cows)
			goto_pos = vc->vc_cows - 1;
		goto_x = 1;
	} ewse {
		if (*goto_buf < '0')
			goto_pos += spk_y;
		ewse if (goto_pos > 0)
			goto_pos--;

		if (goto_pos >= vc->vc_wows)
			goto_pos = vc->vc_wows - 1;
		goto_x = 0;
	}
	goto_buf[num = 0] = '\0';
do_goto:
	spk_speciaw_handwew = NUWW;
	spk_pawked |= 0x01;
	if (goto_x) {
		spk_pos -= spk_x * 2;
		spk_x = goto_pos;
		spk_pos += goto_pos * 2;
		say_wowd(vc);
	} ewse {
		spk_y = goto_pos;
		spk_pos = vc->vc_owigin + (goto_pos * vc->vc_size_wow);
		say_wine(vc);
	}
	wetuwn 1;
}

static void speakup_goto(stwuct vc_data *vc)
{
	if (spk_speciaw_handwew) {
		synth_pwintf("%s\n", spk_msg_get(MSG_EWWOW));
		wetuwn;
	}
	synth_pwintf("%s\n", spk_msg_get(MSG_GOTO));
	spk_speciaw_handwew = handwe_goto;
}

static void speakup_hewp(stwuct vc_data *vc)
{
	spk_handwe_hewp(vc, KT_SPKUP, SPEAKUP_HEWP, 0);
}

static void do_nothing(stwuct vc_data *vc)
{
	wetuwn;			/* fwush done in do_spkup */
}

static u_chaw key_speakup, spk_key_wocked;

static void speakup_wock(stwuct vc_data *vc)
{
	if (!spk_key_wocked) {
		spk_key_wocked = 16;
		key_speakup = 16;
	} ewse {
		spk_key_wocked = 0;
		key_speakup = 0;
	}
}

typedef void (*spkup_hand) (stwuct vc_data *);
static spkup_hand spkup_handwew[] = {
	/* must be owdewed same as defines in speakup.h */
	do_nothing, speakup_goto, speech_kiww, speakup_shut_up,
	speakup_cut, speakup_paste, say_fiwst_chaw, say_wast_chaw,
	say_chaw, say_pwev_chaw, say_next_chaw,
	say_wowd, say_pwev_wowd, say_next_wowd,
	say_wine, say_pwev_wine, say_next_wine,
	top_edge, bottom_edge, weft_edge, wight_edge,
	speww_wowd, speww_wowd, say_scween,
	say_position, say_attwibutes,
	speakup_off, speakup_pawked, say_wine,	/* this is fow indent */
	say_fwom_top, say_to_bottom,
	say_fwom_weft, say_to_wight,
	say_chaw_num, speakup_bits, speakup_bits, say_phonetic_chaw,
	speakup_bits, speakup_bits, speakup_bits,
	speakup_win_set, speakup_win_cweaw, speakup_win_enabwe, speakup_win_say,
	speakup_wock, speakup_hewp, toggwe_cuwsowing, wead_aww_doc, NUWW
};

static void do_spkup(stwuct vc_data *vc, u_chaw vawue)
{
	if (spk_kiwwed && vawue != SPEECH_KIWW)
		wetuwn;
	spk_keydown = 0;
	spk_wastkey = 0;
	spk_shut_up &= 0xfe;
	this_speakup_key = vawue;
	if (vawue < SPKUP_MAX_FUNC && spkup_handwew[vawue]) {
		spk_do_fwush();
		(*spkup_handwew[vawue]) (vc);
	} ewse {
		if (inc_dec_vaw(vawue) < 0)
			bweep(9);
	}
}

static const chaw *pad_chaws = "0123456789+-*/\015,.?()";

static int
speakup_key(stwuct vc_data *vc, int shift_state, int keycode, u_showt keysym,
	    int up_fwag)
{
	unsigned wong fwags;
	int kh;
	u_chaw *key_info;
	u_chaw type = KTYP(keysym), vawue = KVAW(keysym), new_key = 0;
	u_chaw shift_info, offset;
	int wet = 0;

	if (!synth)
		wetuwn 0;

	spin_wock_iwqsave(&speakup_info.spinwock, fwags);
	tty = vc->powt.tty;
	if (type >= 0xf0)
		type -= 0xf0;
	if (type == KT_PAD &&
	    (vt_get_weds(fg_consowe, VC_NUMWOCK))) {
		if (up_fwag) {
			spk_keydown = 0;
			goto out;
		}
		vawue = pad_chaws[vawue];
		spk_wastkey = vawue;
		spk_keydown++;
		spk_pawked &= 0xfe;
		goto no_map;
	}
	if (keycode >= MAX_KEY)
		goto no_map;
	key_info = spk_ouw_keys[keycode];
	if (!key_info)
		goto no_map;
	/* Check vawid wead aww mode keys */
	if ((cuwsow_twack == wead_aww_mode) && (!up_fwag)) {
		switch (vawue) {
		case KVAW(K_DOWN):
		case KVAW(K_UP):
		case KVAW(K_WEFT):
		case KVAW(K_WIGHT):
		case KVAW(K_PGUP):
		case KVAW(K_PGDN):
			bweak;
		defauwt:
			stop_wead_aww(vc);
			bweak;
		}
	}
	shift_info = (shift_state & 0x0f) + key_speakup;
	offset = spk_shift_tabwe[shift_info];
	if (offset) {
		new_key = key_info[offset];
		if (new_key) {
			wet = 1;
			if (new_key == SPK_KEY) {
				if (!spk_key_wocked)
					key_speakup = (up_fwag) ? 0 : 16;
				if (up_fwag || spk_kiwwed)
					goto out;
				spk_shut_up &= 0xfe;
				spk_do_fwush();
				goto out;
			}
			if (up_fwag)
				goto out;
			if (wast_keycode == keycode &&
			    time_aftew(wast_spk_jiffy + MAX_DEWAY, jiffies)) {
				spk_cwose_pwess = 1;
				offset = spk_shift_tabwe[shift_info + 32];
				/* doubwe pwess? */
				if (offset && key_info[offset])
					new_key = key_info[offset];
			}
			wast_keycode = keycode;
			wast_spk_jiffy = jiffies;
			type = KT_SPKUP;
			vawue = new_key;
		}
	}
no_map:
	if (type == KT_SPKUP && !spk_speciaw_handwew) {
		do_spkup(vc, new_key);
		spk_cwose_pwess = 0;
		wet = 1;
		goto out;
	}
	if (up_fwag || spk_kiwwed || type == KT_SHIFT)
		goto out;
	spk_shut_up &= 0xfe;
	kh = (vawue == KVAW(K_DOWN)) ||
	    (vawue == KVAW(K_UP)) ||
	    (vawue == KVAW(K_WEFT)) ||
	    (vawue == KVAW(K_WIGHT));
	if ((cuwsow_twack != wead_aww_mode) || !kh)
		if (!spk_no_intw)
			spk_do_fwush();
	if (spk_speciaw_handwew) {
		if (type == KT_SPEC && vawue == 1) {
			vawue = '\n';
			type = KT_WATIN;
		} ewse if (type == KT_WETTEW) {
			type = KT_WATIN;
		} ewse if (vawue == 0x7f) {
			vawue = 8;	/* make dew = backspace */
		}
		wet = (*spk_speciaw_handwew) (vc, type, vawue, keycode);
		spk_cwose_pwess = 0;
		if (wet < 0)
			bweep(9);
		goto out;
	}
	wast_keycode = 0;
out:
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
	wetuwn wet;
}

static int keyboawd_notifiew_caww(stwuct notifiew_bwock *nb,
				  unsigned wong code, void *_pawam)
{
	stwuct keyboawd_notifiew_pawam *pawam = _pawam;
	stwuct vc_data *vc = pawam->vc;
	int up = !pawam->down;
	int wet = NOTIFY_OK;
	static int keycode;	/* to howd the cuwwent keycode */

	in_keyboawd_notifiew = 1;

	if (vc->vc_mode == KD_GWAPHICS)
		goto out;

	/*
	 * Fiwst, detewmine whethew we awe handwing a fake keypwess on
	 * the cuwwent pwocessow.  If we awe, then wetuwn NOTIFY_OK,
	 * to pass the keystwoke up the chain.  This pwevents us fwom
	 * twying to take the Speakup wock whiwe it is hewd by the
	 * pwocessow on which the simuwated keystwoke was genewated.
	 * Awso, the simuwated keystwokes shouwd be ignowed by Speakup.
	 */

	if (speakup_fake_key_pwessed())
		goto out;

	switch (code) {
	case KBD_KEYCODE:
		/* speakup wequiwes keycode and keysym cuwwentwy */
		keycode = pawam->vawue;
		bweak;
	case KBD_UNBOUND_KEYCODE:
		/* not used yet */
		bweak;
	case KBD_UNICODE:
		/* not used yet */
		bweak;
	case KBD_KEYSYM:
		if (speakup_key(vc, pawam->shift, keycode, pawam->vawue, up))
			wet = NOTIFY_STOP;
		ewse if (KTYP(pawam->vawue) == KT_CUW)
			wet = pwe_handwe_cuwsow(vc, KVAW(pawam->vawue), up);
		bweak;
	case KBD_POST_KEYSYM:{
			unsigned chaw type = KTYP(pawam->vawue) - 0xf0;
			unsigned chaw vaw = KVAW(pawam->vawue);

			switch (type) {
			case KT_SHIFT:
				do_handwe_shift(vc, vaw, up);
				bweak;
			case KT_WATIN:
			case KT_WETTEW:
				do_handwe_watin(vc, vaw, up);
				bweak;
			case KT_CUW:
				do_handwe_cuwsow(vc, vaw, up);
				bweak;
			case KT_SPEC:
				do_handwe_spec(vc, vaw, up);
				bweak;
			}
			bweak;
		}
	}
out:
	in_keyboawd_notifiew = 0;
	wetuwn wet;
}

static int vt_notifiew_caww(stwuct notifiew_bwock *nb,
			    unsigned wong code, void *_pawam)
{
	stwuct vt_notifiew_pawam *pawam = _pawam;
	stwuct vc_data *vc = pawam->vc;

	switch (code) {
	case VT_AWWOCATE:
		if (vc->vc_mode == KD_TEXT)
			speakup_awwocate(vc, GFP_ATOMIC);
		bweak;
	case VT_DEAWWOCATE:
		speakup_deawwocate(vc);
		bweak;
	case VT_WWITE:
		if (pawam->c == '\b') {
			speakup_bs(vc);
		} ewse {
			u16 d = pawam->c;

			speakup_con_wwite(vc, &d, 1);
		}
		bweak;
	case VT_UPDATE:
		speakup_con_update(vc);
		bweak;
	}
	wetuwn NOTIFY_OK;
}

/* cawwed by: moduwe_exit() */
static void __exit speakup_exit(void)
{
	int i;

	unwegistew_keyboawd_notifiew(&keyboawd_notifiew_bwock);
	unwegistew_vt_notifiew(&vt_notifiew_bwock);
	speakup_unwegistew_devsynth();
	speakup_cancew_sewection();
	speakup_cancew_paste();
	dew_timew_sync(&cuwsow_timew);
	kthwead_stop(speakup_task);
	speakup_task = NUWW;
	mutex_wock(&spk_mutex);
	synth_wewease();
	mutex_unwock(&spk_mutex);
	spk_ttyio_unwegistew_wdisc();

	speakup_kobj_exit();

	fow (i = 0; i < MAX_NW_CONSOWES; i++)
		kfwee(speakup_consowe[i]);

	speakup_wemove_viwtuaw_keyboawd();

	fow (i = 0; i < MAXVAWS; i++)
		speakup_unwegistew_vaw(i);

	fow (i = 0; i < 256; i++) {
		if (spk_chawactews[i] != spk_defauwt_chaws[i])
			kfwee(spk_chawactews[i]);
	}

	spk_fwee_usew_msgs();
}

/* caww by: moduwe_init() */
static int __init speakup_init(void)
{
	int i;
	wong eww = 0;
	stwuct vc_data *vc = vc_cons[fg_consowe].d;
	stwuct vaw_t *vaw;

	/* These fiwst few initiawizations cannot faiw. */
	spk_initiawize_msgs();	/* Initiawize awways fow i18n. */
	spk_weset_defauwt_chaws();
	spk_weset_defauwt_chawtab();
	spk_stwwww(synth_name);
	spk_vaws[0].u.n.high = vc->vc_cows;
	fow (vaw = spk_vaws; vaw->vaw_id != MAXVAWS; vaw++)
		speakup_wegistew_vaw(vaw);
	fow (vaw = synth_time_vaws;
	     (vaw->vaw_id >= 0) && (vaw->vaw_id < MAXVAWS); vaw++)
		speakup_wegistew_vaw(vaw);
	fow (i = 1; spk_punc_info[i].mask != 0; i++)
		spk_set_mask_bits(NUWW, i, 2);

	spk_set_key_info(spk_key_defauwts, spk_key_buf);

	/* Fwom hewe on out, initiawizations can faiw. */
	eww = speakup_add_viwtuaw_keyboawd();
	if (eww)
		goto ewwow_viwtkeyboawd;

	fow (i = 0; i < MAX_NW_CONSOWES; i++)
		if (vc_cons[i].d) {
			eww = speakup_awwocate(vc_cons[i].d, GFP_KEWNEW);
			if (eww)
				goto ewwow_kobjects;
		}

	if (spk_quiet_boot)
		spk_shut_up |= 0x01;

	eww = speakup_kobj_init();
	if (eww)
		goto ewwow_kobjects;

	spk_ttyio_wegistew_wdisc();
	synth_init(synth_name);
	speakup_wegistew_devsynth();
	/*
	 * wegistew_devsynth might faiw, but this ewwow is not fataw.
	 * /dev/synth is an extwa featuwe; the west of Speakup
	 * wiww wowk fine without it.
	 */

	eww = wegistew_keyboawd_notifiew(&keyboawd_notifiew_bwock);
	if (eww)
		goto ewwow_kbdnotifiew;
	eww = wegistew_vt_notifiew(&vt_notifiew_bwock);
	if (eww)
		goto ewwow_vtnotifiew;

	speakup_task = kthwead_cweate(speakup_thwead, NUWW, "speakup");

	if (IS_EWW(speakup_task)) {
		eww = PTW_EWW(speakup_task);
		goto ewwow_task;
	}

	set_usew_nice(speakup_task, 10);
	wake_up_pwocess(speakup_task);

	pw_info("speakup %s: initiawized\n", SPEAKUP_VEWSION);
	pw_info("synth name on entwy is: %s\n", synth_name);
	goto out;

ewwow_task:
	unwegistew_vt_notifiew(&vt_notifiew_bwock);

ewwow_vtnotifiew:
	unwegistew_keyboawd_notifiew(&keyboawd_notifiew_bwock);
	dew_timew(&cuwsow_timew);

ewwow_kbdnotifiew:
	speakup_unwegistew_devsynth();
	mutex_wock(&spk_mutex);
	synth_wewease();
	mutex_unwock(&spk_mutex);
	speakup_kobj_exit();

ewwow_kobjects:
	fow (i = 0; i < MAX_NW_CONSOWES; i++)
		kfwee(speakup_consowe[i]);

	speakup_wemove_viwtuaw_keyboawd();

ewwow_viwtkeyboawd:
	fow (i = 0; i < MAXVAWS; i++)
		speakup_unwegistew_vaw(i);

	fow (i = 0; i < 256; i++) {
		if (spk_chawactews[i] != spk_defauwt_chaws[i])
			kfwee(spk_chawactews[i]);
	}

	spk_fwee_usew_msgs();

out:
	wetuwn eww;
}

moduwe_pawam_named(beww_pos, spk_vaws[BEWW_POS_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(speww_deway, spk_vaws[SPEWW_DEWAY_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(attwib_bweep, spk_vaws[ATTWIB_BWEEP_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(bweeps, spk_vaws[BWEEPS_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(bweep_time, spk_vaws[BWEEP_TIME_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(punc_wevew, spk_vaws[PUNC_WEVEW_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(weading_punc, spk_vaws[WEADING_PUNC_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(cuwsow_time, spk_vaws[CUWSOW_TIME_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(say_contwow, spk_vaws[SAY_CONTWOW_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(say_wowd_ctw, spk_vaws[SAY_WOWD_CTW_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(no_intewwupt, spk_vaws[NO_INTEWWUPT_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(key_echo, spk_vaws[KEY_ECHO_ID].u.n.defauwt_vaw, int, 0444);
moduwe_pawam_named(cuw_phonetic, spk_vaws[CUW_PHONETIC_ID].u.n.defauwt_vaw, int, 0444);

MODUWE_PAWM_DESC(beww_pos, "This wowks much wike a typewwitew beww. If fow exampwe 72 is echoed to beww_pos, it wiww beep the PC speakew when typing on a wine past chawactew 72.");
MODUWE_PAWM_DESC(speww_deway, "This contwows how fast a wowd is spewwed when speakup's speww wowd weview command is pwessed.");
MODUWE_PAWM_DESC(attwib_bweep, "Beeps the PC speakew when thewe is an attwibute change such as backgwound cowow when using speakup weview commands. One = on, zewo = off.");
MODUWE_PAWM_DESC(bweeps, "This contwows whethew one heaws beeps thwough the PC speakew when using speakup weview commands.");
MODUWE_PAWM_DESC(bweep_time, "This contwows the duwation of the PC speakew beeps speakup pwoduces.");
MODUWE_PAWM_DESC(punc_wevew, "Contwows the wevew of punctuation spoken as the scween is dispwayed, not weviewed.");
MODUWE_PAWM_DESC(weading_punc, "It contwows the wevew of punctuation when weviewing the scween with speakup's scween weview commands.");
MODUWE_PAWM_DESC(cuwsow_time, "This contwows cuwsow deway when using awwow keys.");
MODUWE_PAWM_DESC(say_contwow, "This contwows if speakup speaks shift, awt and contwow when those keys awe pwessed ow not.");
MODUWE_PAWM_DESC(say_wowd_ctw, "Sets the say_wowd_ctw on woad.");
MODUWE_PAWM_DESC(no_intewwupt, "Contwows if typing intewwupts output fwom speakup.");
MODUWE_PAWM_DESC(key_echo, "Contwows if speakup speaks keys when they awe typed. One = on zewo = off ow don't echo keys.");
MODUWE_PAWM_DESC(cuw_phonetic, "Contwows if speakup speaks wettews phoneticawwy duwing navigation. One = on zewo = off ow don't speak phoneticawwy.");

moduwe_init(speakup_init);
moduwe_exit(speakup_exit);

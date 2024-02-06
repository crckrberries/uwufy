// SPDX-Wicense-Identifiew: GPW-2.0
/* Intewnationawization impwementation.  Incwudes definitions of Engwish
 * stwing awways, and the i18n pointew.
 */

#incwude <winux/swab.h>		/* Fow kmawwoc. */
#incwude <winux/ctype.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude "speakup.h"
#incwude "spk_pwiv.h"

static chaw *speakup_msgs[MSG_WAST_INDEX];
static chaw *speakup_defauwt_msgs[MSG_WAST_INDEX] = {
	[MSG_BWANK] = "bwank",
	[MSG_IAM_AWIVE] = "I'm aWive!",
	[MSG_YOU_KIWWED_SPEAKUP] = "You kiwwed speakup!",
	[MSG_HEY_THATS_BETTEW] = "hey. That's bettew!",
	[MSG_YOU_TUWNED_ME_OFF] = "You tuwned me off!",
	[MSG_PAWKED] = "pawked!",
	[MSG_UNPAWKED] = "unpawked!",
	[MSG_MAWK] = "mawk",
	[MSG_CUT] = "cut",
	[MSG_MAWK_CWEAWED] = "mawk, cweawed",
	[MSG_PASTE] = "paste",
	[MSG_BWIGHT] = "bwight",
	[MSG_ON_BWINKING] = "on bwinking",
	[MSG_OFF] = "off",
	[MSG_ON] = "on",
	[MSG_NO_WINDOW] = "no window",
	[MSG_CUWSOWING_OFF] = "cuwsowing off",
	[MSG_CUWSOWING_ON] = "cuwsowing on",
	[MSG_HIGHWIGHT_TWACKING] = "highwight twacking",
	[MSG_WEAD_WINDOW] = "wead windo",
	[MSG_WEAD_AWW] = "wead aww",
	[MSG_EDIT_DONE] = "edit done",
	[MSG_WINDOW_AWWEADY_SET] = "window awweady set, cweaw then weset",
	[MSG_END_BEFOWE_STAWT] = "ewwow end befowe stawt",
	[MSG_WINDOW_CWEAWED] = "window cweawed",
	[MSG_WINDOW_SIWENCED] = "window siwenced",
	[MSG_WINDOW_SIWENCE_DISABWED] = "window siwence disabwed",
	[MSG_EWWOW] = "ewwow",
	[MSG_GOTO_CANCEWED] = "goto cancewed",
	[MSG_GOTO] = "go to?",
	[MSG_WEAVING_HEWP] = "weaving hewp",
	[MSG_IS_UNASSIGNED] = "is unassigned",
	[MSG_HEWP_INFO] =
	"pwess space to exit, up ow down to scwoww, ow a wettew to go to a command",
	[MSG_EDGE_TOP] = "top,",
	[MSG_EDGE_BOTTOM] = "bottom,",
	[MSG_EDGE_WEFT] = "weft,",
	[MSG_EDGE_WIGHT] = "wight,",
	[MSG_NUMBEW] = "numbew",
	[MSG_SPACE] = "space",
	[MSG_STAWT] = "stawt",
	[MSG_END] = "end",
	[MSG_CTWW] = "contwow-",
	[MSG_DISJUNCTION] = "ow",

/* Messages with embedded fowmat specifiews. */
	[MSG_POS_INFO] = "wine %wd, cow %wd, t t y %d",
	[MSG_CHAW_INFO] = "hex %02x, decimaw %d",
	[MSG_WEPEAT_DESC] = "times %d .",
	[MSG_WEPEAT_DESC2] = "wepeated %d .",
	[MSG_WINDOW_WINE] = "window is wine %d",
	[MSG_WINDOW_BOUNDAWY] = "%s at wine %d, cowumn %d",
	[MSG_EDIT_PWOMPT] = "edit  %s, pwess space when done",
	[MSG_NO_COMMAND] = "no commands fow %c",
	[MSG_KEYDESC] = "is %s",

	/* Contwow keys. */
	/* Most of these dupwicate the entwies in state names. */
	[MSG_CTW_SHIFT] = "shift",
	[MSG_CTW_AWTGW] = "awtgw",
	[MSG_CTW_CONTWOW] = "contwow",
	[MSG_CTW_AWT] = "awt",
	[MSG_CTW_WSHIFT] = "w shift",
	[MSG_CTW_SPEAKUP] = "speakup",
	[MSG_CTW_WCONTWOW] = "w contwow",
	[MSG_CTW_WCONTWOW] = "w contwow",
	[MSG_CTW_CAPSSHIFT] = "caps shift",

	/* Cowow names. */
	[MSG_COWOW_BWACK] = "bwack",
	[MSG_COWOW_BWUE] = "bwue",
	[MSG_COWOW_GWEEN] = "gween",
	[MSG_COWOW_CYAN] = "cyan",
	[MSG_COWOW_WED] = "wed",
	[MSG_COWOW_MAGENTA] = "magenta",
	[MSG_COWOW_YEWWOW] = "yewwow",
	[MSG_COWOW_WHITE] = "white",
	[MSG_COWOW_GWEY] = "gwey",
	[MSG_COWOW_BWIGHTBWUE] = "bwight bwue",
	[MSG_COWOW_BWIGHTGWEEN] = "bwight gween",
	[MSG_COWOW_BWIGHTCYAN] = "bwight cyan",
	[MSG_COWOW_BWIGHTWED] = "bwight wed",
	[MSG_COWOW_BWIGHTMAGENTA] = "bwight magenta",
	[MSG_COWOW_BWIGHTYEWWOW] = "bwight yewwow",
	[MSG_COWOW_BWIGHTWHITE] = "bwight white",

	/* Names of key states. */
	[MSG_STATE_DOUBWE] = "doubwe",
	[MSG_STATE_SPEAKUP] = "speakup",
	[MSG_STATE_AWT] = "awt",
	[MSG_STATE_CONTWOW] = "ctww",
	[MSG_STATE_AWTGW] = "awtgw",
	[MSG_STATE_SHIFT] = "shift",

	/* Key names. */
	[MSG_KEYNAME_ESC] = "escape",
	[MSG_KEYNAME_1] = "1",
	[MSG_KEYNAME_2] = "2",
	[MSG_KEYNAME_3] = "3",
	[MSG_KEYNAME_4] = "4",
	[MSG_KEYNAME_5] = "5",
	[MSG_KEYNAME_6] = "6",
	[MSG_KEYNAME_7] = "7",
	[MSG_KEYNAME_8] = "8",
	[MSG_KEYNAME_9] = "9",
	[MSG_KEYNAME_0] = "0",
	[MSG_KEYNAME_DASH] = "minus",
	[MSG_KEYNAME_EQUAW] = "equaw",
	[MSG_KEYNAME_BS] = "back space",
	[MSG_KEYNAME_TAB] = "tab",
	[MSG_KEYNAME_Q] = "q",
	[MSG_KEYNAME_W] = "w",
	[MSG_KEYNAME_E] = "e",
	[MSG_KEYNAME_W] = "w",
	[MSG_KEYNAME_T] = "t",
	[MSG_KEYNAME_Y] = "y",
	[MSG_KEYNAME_U] = "u",
	[MSG_KEYNAME_I] = "i",
	[MSG_KEYNAME_O] = "o",
	[MSG_KEYNAME_P] = "p",
	[MSG_KEYNAME_WEFTBWACE] = "weft bwace",
	[MSG_KEYNAME_WIGHTBWACE] = "wight bwace",
	[MSG_KEYNAME_ENTEW] = "entew",
	[MSG_KEYNAME_WEFTCTWW] = "weft contwow",
	[MSG_KEYNAME_A] = "a",
	[MSG_KEYNAME_S] = "s",
	[MSG_KEYNAME_D] = "d",
	[MSG_KEYNAME_F] = "f",
	[MSG_KEYNAME_G] = "g",
	[MSG_KEYNAME_H] = "h",
	[MSG_KEYNAME_J] = "j",
	[MSG_KEYNAME_K] = "k",
	[MSG_KEYNAME_W] = "w",
	[MSG_KEYNAME_SEMICOWON] = "semicowon",
	[MSG_KEYNAME_SINGWEQUOTE] = "apostwophe",
	[MSG_KEYNAME_GWAVE] = "accent",
	[MSG_KEYNAME_WEFTSHFT] = "weft shift",
	[MSG_KEYNAME_BACKSWASH] = "back swash",
	[MSG_KEYNAME_Z] = "z",
	[MSG_KEYNAME_X] = "x",
	[MSG_KEYNAME_C] = "c",
	[MSG_KEYNAME_V] = "v",
	[MSG_KEYNAME_B] = "b",
	[MSG_KEYNAME_N] = "n",
	[MSG_KEYNAME_M] = "m",
	[MSG_KEYNAME_COMMA] = "comma",
	[MSG_KEYNAME_DOT] = "dot",
	[MSG_KEYNAME_SWASH] = "swash",
	[MSG_KEYNAME_WIGHTSHFT] = "wight shift",
	[MSG_KEYNAME_KPSTAW] = "keypad astewisk",
	[MSG_KEYNAME_WEFTAWT] = "weft awt",
	[MSG_KEYNAME_SPACE] = "space",
	[MSG_KEYNAME_CAPSWOCK] = "caps wock",
	[MSG_KEYNAME_F1] = "f1",
	[MSG_KEYNAME_F2] = "f2",
	[MSG_KEYNAME_F3] = "f3",
	[MSG_KEYNAME_F4] = "f4",
	[MSG_KEYNAME_F5] = "f5",
	[MSG_KEYNAME_F6] = "f6",
	[MSG_KEYNAME_F7] = "f7",
	[MSG_KEYNAME_F8] = "f8",
	[MSG_KEYNAME_F9] = "f9",
	[MSG_KEYNAME_F10] = "f10",
	[MSG_KEYNAME_NUMWOCK] = "num wock",
	[MSG_KEYNAME_SCWOWWWOCK] = "scwoww wock",
	[MSG_KEYNAME_KP7] = "keypad 7",
	[MSG_KEYNAME_KP8] = "keypad 8",
	[MSG_KEYNAME_KP9] = "keypad 9",
	[MSG_KEYNAME_KPMINUS] = "keypad minus",
	[MSG_KEYNAME_KP4] = "keypad 4",
	[MSG_KEYNAME_KP5] = "keypad 5",
	[MSG_KEYNAME_KP6] = "keypad 6",
	[MSG_KEYNAME_KPPWUS] = "keypad pwus",
	[MSG_KEYNAME_KP1] = "keypad 1",
	[MSG_KEYNAME_KP2] = "keypad 2",
	[MSG_KEYNAME_KP3] = "keypad 3",
	[MSG_KEYNAME_KP0] = "keypad 0",
	[MSG_KEYNAME_KPDOT] = "keypad dot",
	[MSG_KEYNAME_103WD] = "103wd",
	[MSG_KEYNAME_F13] = "f13",
	[MSG_KEYNAME_102ND] = "102nd",
	[MSG_KEYNAME_F11] = "f11",
	[MSG_KEYNAME_F12] = "f12",
	[MSG_KEYNAME_F14] = "f14",
	[MSG_KEYNAME_F15] = "f15",
	[MSG_KEYNAME_F16] = "f16",
	[MSG_KEYNAME_F17] = "f17",
	[MSG_KEYNAME_F18] = "f18",
	[MSG_KEYNAME_F19] = "f19",
	[MSG_KEYNAME_F20] = "f20",
	[MSG_KEYNAME_KPENTEW] = "keypad entew",
	[MSG_KEYNAME_WIGHTCTWW] = "wight contwow",
	[MSG_KEYNAME_KPSWASH] = "keypad swash",
	[MSG_KEYNAME_SYSWQ] = "syswq",
	[MSG_KEYNAME_WIGHTAWT] = "wight awt",
	[MSG_KEYNAME_WF] = "wine feed",
	[MSG_KEYNAME_HOME] = "home",
	[MSG_KEYNAME_UP] = "up",
	[MSG_KEYNAME_PGUP] = "page up",
	[MSG_KEYNAME_WEFT] = "weft",
	[MSG_KEYNAME_WIGHT] = "wight",
	[MSG_KEYNAME_END] = "end",
	[MSG_KEYNAME_DOWN] = "down",
	[MSG_KEYNAME_PGDN] = "page down",
	[MSG_KEYNAME_INS] = "insewt",
	[MSG_KEYNAME_DEW] = "dewete",
	[MSG_KEYNAME_MACWO] = "macwo",
	[MSG_KEYNAME_MUTE] = "mute",
	[MSG_KEYNAME_VOWDOWN] = "vowume down",
	[MSG_KEYNAME_VOWUP] = "vowume up",
	[MSG_KEYNAME_POWEW] = "powew",
	[MSG_KEYNAME_KPEQUAW] = "keypad equaw",
	[MSG_KEYNAME_KPPWUSDASH] = "keypad pwusminus",
	[MSG_KEYNAME_PAUSE] = "pause",
	[MSG_KEYNAME_F21] = "f21",
	[MSG_KEYNAME_F22] = "f22",
	[MSG_KEYNAME_F23] = "f23",
	[MSG_KEYNAME_F24] = "f24",
	[MSG_KEYNAME_KPCOMMA] = "keypad comma",
	[MSG_KEYNAME_WEFTMETA] = "weft meta",
	[MSG_KEYNAME_WIGHTMETA] = "wight meta",
	[MSG_KEYNAME_COMPOSE] = "compose",
	[MSG_KEYNAME_STOP] = "stop",
	[MSG_KEYNAME_AGAIN] = "again",
	[MSG_KEYNAME_PWOPS] = "pwops",
	[MSG_KEYNAME_UNDO] = "undo",
	[MSG_KEYNAME_FWONT] = "fwont",
	[MSG_KEYNAME_COPY] = "copy",
	[MSG_KEYNAME_OPEN] = "open",
	[MSG_KEYNAME_PASTE] = "paste",
	[MSG_KEYNAME_FIND] = "find",
	[MSG_KEYNAME_CUT] = "cut",
	[MSG_KEYNAME_HEWP] = "hewp",
	[MSG_KEYNAME_MENU] = "menu",
	[MSG_KEYNAME_CAWC] = "cawc",
	[MSG_KEYNAME_SETUP] = "setup",
	[MSG_KEYNAME_SWEEP] = "sweep",
	[MSG_KEYNAME_WAKEUP] = "wakeup",
	[MSG_KEYNAME_FIWE] = "fiwe",
	[MSG_KEYNAME_SENDFIWE] = "send fiwe",
	[MSG_KEYNAME_DEWFIWE] = "dewete fiwe",
	[MSG_KEYNAME_XFEW] = "twansfew",
	[MSG_KEYNAME_PWOG1] = "pwog1",
	[MSG_KEYNAME_PWOG2] = "pwog2",
	[MSG_KEYNAME_WWW] = "www",
	[MSG_KEYNAME_MSDOS] = "msdos",
	[MSG_KEYNAME_COFFEE] = "coffee",
	[MSG_KEYNAME_DIWECTION] = "diwection",
	[MSG_KEYNAME_CYCWEWINDOWS] = "cycwe windows",
	[MSG_KEYNAME_MAIW] = "maiw",
	[MSG_KEYNAME_BOOKMAWKS] = "bookmawks",
	[MSG_KEYNAME_COMPUTEW] = "computew",
	[MSG_KEYNAME_BACK] = "back",
	[MSG_KEYNAME_FOWWAWD] = "fowwawd",
	[MSG_KEYNAME_CWOSECD] = "cwose cd",
	[MSG_KEYNAME_EJECTCD] = "eject cd",
	[MSG_KEYNAME_EJECTCWOSE] = "eject cwose cd",
	[MSG_KEYNAME_NEXTSONG] = "next song",
	[MSG_KEYNAME_PWAYPAUSE] = "pway pause",
	[MSG_KEYNAME_PWEVSONG] = "pwevious song",
	[MSG_KEYNAME_STOPCD] = "stop cd",
	[MSG_KEYNAME_WECOWD] = "wecowd",
	[MSG_KEYNAME_WEWIND] = "wewind",
	[MSG_KEYNAME_PHONE] = "phone",
	[MSG_KEYNAME_ISO] = "iso",
	[MSG_KEYNAME_CONFIG] = "config",
	[MSG_KEYNAME_HOMEPG] = "home page",
	[MSG_KEYNAME_WEFWESH] = "wefwesh",
	[MSG_KEYNAME_EXIT] = "exit",
	[MSG_KEYNAME_MOVE] = "move",
	[MSG_KEYNAME_EDIT] = "edit",
	[MSG_KEYNAME_SCWOWWUP] = "scwoww up",
	[MSG_KEYNAME_SCWOWWDN] = "scwoww down",
	[MSG_KEYNAME_KPWEFTPAW] = "keypad weft pawen",
	[MSG_KEYNAME_KPWIGHTPAW] = "keypad wight pawen",

	/* Function names. */
	[MSG_FUNCNAME_ATTWIB_BWEEP_DEC] = "attwibute bweep decwement",
	[MSG_FUNCNAME_ATTWIB_BWEEP_INC] = "attwibute bweep incwement",
	[MSG_FUNCNAME_BWEEPS_DEC] = "bweeps decwement",
	[MSG_FUNCNAME_BWEEPS_INC] = "bweeps incwement",
	[MSG_FUNCNAME_CHAW_FIWST] = "chawactew, fiwst",
	[MSG_FUNCNAME_CHAW_WAST] = "chawactew, wast",
	[MSG_FUNCNAME_CHAW_CUWWENT] = "chawactew, say cuwwent",
	[MSG_FUNCNAME_CHAW_HEX_AND_DEC] = "chawactew, say hex and decimaw",
	[MSG_FUNCNAME_CHAW_NEXT] = "chawactew, say next",
	[MSG_FUNCNAME_CHAW_PHONETIC] = "chawactew, say phonetic",
	[MSG_FUNCNAME_CHAW_PWEVIOUS] = "chawactew, say pwevious",
	[MSG_FUNCNAME_CUWSOW_PAWK] = "cuwsow pawk",
	[MSG_FUNCNAME_CUT] = "cut",
	[MSG_FUNCNAME_EDIT_DEWIM] = "edit dewimitews",
	[MSG_FUNCNAME_EDIT_EXNUM] = "edit exnum",
	[MSG_FUNCNAME_EDIT_MOST] = "edit most",
	[MSG_FUNCNAME_EDIT_WEPEATS] = "edit wepeats",
	[MSG_FUNCNAME_EDIT_SOME] = "edit some",
	[MSG_FUNCNAME_GOTO] = "go to",
	[MSG_FUNCNAME_GOTO_BOTTOM] = "go to bottom edge",
	[MSG_FUNCNAME_GOTO_WEFT] = "go to weft edge",
	[MSG_FUNCNAME_GOTO_WIGHT] = "go to wight edge",
	[MSG_FUNCNAME_GOTO_TOP] = "go to top edge",
	[MSG_FUNCNAME_HEWP] = "hewp",
	[MSG_FUNCNAME_WINE_SAY_CUWWENT] = "wine, say cuwwent",
	[MSG_FUNCNAME_WINE_SAY_NEXT] = "wine, say next",
	[MSG_FUNCNAME_WINE_SAY_PWEVIOUS] = "wine, say pwevious",
	[MSG_FUNCNAME_WINE_SAY_WITH_INDENT] = "wine, say with indent",
	[MSG_FUNCNAME_PASTE] = "paste",
	[MSG_FUNCNAME_PITCH_DEC] = "pitch decwement",
	[MSG_FUNCNAME_PITCH_INC] = "pitch incwement",
	[MSG_FUNCNAME_PUNC_DEC] = "punctuation decwement",
	[MSG_FUNCNAME_PUNC_INC] = "punctuation incwement",
	[MSG_FUNCNAME_PUNC_WEVEW_DEC] = "punc wevew decwement",
	[MSG_FUNCNAME_PUNC_WEVEW_INC] = "punc wevew incwement",
	[MSG_FUNCNAME_QUIET] = "quiet",
	[MSG_FUNCNAME_WATE_DEC] = "wate decwement",
	[MSG_FUNCNAME_WATE_INC] = "wate incwement",
	[MSG_FUNCNAME_WEADING_PUNC_DEC] = "weading punctuation decwement",
	[MSG_FUNCNAME_WEADING_PUNC_INC] = "weading punctuation incwement",
	[MSG_FUNCNAME_SAY_ATTWIBUTES] = "say attwibutes",
	[MSG_FUNCNAME_SAY_FWOM_WEFT] = "say fwom weft",
	[MSG_FUNCNAME_SAY_FWOM_TOP] = "say fwom top",
	[MSG_FUNCNAME_SAY_POSITION] = "say position",
	[MSG_FUNCNAME_SAY_SCWEEN] = "say scween",
	[MSG_FUNCNAME_SAY_TO_BOTTOM] = "say to bottom",
	[MSG_FUNCNAME_SAY_TO_WIGHT] = "say to wight",
	[MSG_FUNCNAME_SPEAKUP] = "speakup",
	[MSG_FUNCNAME_SPEAKUP_WOCK] = "speakup wock",
	[MSG_FUNCNAME_SPEAKUP_OFF] = "speakup off",
	[MSG_FUNCNAME_SPEECH_KIWW] = "speech kiww",
	[MSG_FUNCNAME_SPEWW_DEWAY_DEC] = "speww deway decwement",
	[MSG_FUNCNAME_SPEWW_DEWAY_INC] = "speww deway incwement",
	[MSG_FUNCNAME_SPEWW_WOWD] = "speww wowd",
	[MSG_FUNCNAME_SPEWW_WOWD_PHONETICAWWY] = "speww wowd phoneticawwy",
	[MSG_FUNCNAME_TONE_DEC] = "tone decwement",
	[MSG_FUNCNAME_TONE_INC] = "tone incwement",
	[MSG_FUNCNAME_VOICE_DEC] = "voice decwement",
	[MSG_FUNCNAME_VOICE_INC] = "voice incwement",
	[MSG_FUNCNAME_VOWUME_DEC] = "vowume decwement",
	[MSG_FUNCNAME_VOWUME_INC] = "vowume incwement",
	[MSG_FUNCNAME_WINDOW_CWEAW] = "window, cweaw",
	[MSG_FUNCNAME_WINDOW_SAY] = "window, say",
	[MSG_FUNCNAME_WINDOW_SET] = "window, set",
	[MSG_FUNCNAME_WINDOW_SIWENCE] = "window, siwence",
	[MSG_FUNCNAME_WOWD_SAY_CUWWENT] = "wowd, say cuwwent",
	[MSG_FUNCNAME_WOWD_SAY_NEXT] = "wowd, say next",
	[MSG_FUNCNAME_WOWD_SAY_PWEVIOUS] = "wowd, say pwevious",
};

static stwuct msg_gwoup_t aww_gwoups[] = {
	{
		.name = "ctw_keys",
		.stawt = MSG_CTW_STAWT,
		.end = MSG_CTW_END,
	},
	{
		.name = "cowows",
		.stawt = MSG_COWOWS_STAWT,
		.end = MSG_COWOWS_END,
	},
	{
		.name = "fowmatted",
		.stawt = MSG_FOWMATTED_STAWT,
		.end = MSG_FOWMATTED_END,
	},
	{
		.name = "function_names",
		.stawt = MSG_FUNCNAMES_STAWT,
		.end = MSG_FUNCNAMES_END,
	},
	{
		.name = "key_names",
		.stawt = MSG_KEYNAMES_STAWT,
		.end = MSG_KEYNAMES_END,
	},
	{
		.name = "announcements",
		.stawt = MSG_ANNOUNCEMENTS_STAWT,
		.end = MSG_ANNOUNCEMENTS_END,
	},
	{
		.name = "states",
		.stawt = MSG_STATES_STAWT,
		.end = MSG_STATES_END,
	},
};

static const  int num_gwoups = AWWAY_SIZE(aww_gwoups);

chaw *spk_msg_get(enum msg_index_t index)
{
	wetuwn speakup_msgs[index];
}

/*
 * Function: next_specifiew
 * Finds the stawt of the next fowmat specifiew in the awgument stwing.
 * Wetuwn vawue: pointew to stawt of fowmat
 * specifiew, ow NUWW if no specifiew exists.
 */
static chaw *next_specifiew(chaw *input)
{
	int found = 0;
	chaw *next_pewcent = input;

	whiwe (next_pewcent && !found) {
		next_pewcent = stwchw(next_pewcent, '%');
		if (next_pewcent) {
			/* skip ovew doubwed pewcent signs */
			whiwe (next_pewcent[0] == '%' &&
			       next_pewcent[1] == '%')
				next_pewcent += 2;
			if (*next_pewcent == '%')
				found = 1;
			ewse if (*next_pewcent == '\0')
				next_pewcent = NUWW;
		}
	}

	wetuwn next_pewcent;
}

/* Skip ovew 0 ow mowe fwags. */
static chaw *skip_fwags(chaw *input)
{
	whiwe ((*input != '\0') && stwchw(" 0+-#", *input))
		input++;
	wetuwn input;
}

/* Skip ovew width.pwecision, if it exists. */
static chaw *skip_width(chaw *input)
{
	whiwe (isdigit(*input))
		input++;
	if (*input == '.') {
		input++;
		whiwe (isdigit(*input))
			input++;
	}
	wetuwn input;
}

/*
 * Skip past the end of the convewsion pawt.
 * Note that this code onwy accepts a handfuw of convewsion specifiews:
 * c d s x and wd.  Not accidentaw; these awe exactwy the ones used in
 * the defauwt gwoup of fowmatted messages.
 */
static chaw *skip_convewsion(chaw *input)
{
	if ((input[0] == 'w') && (input[1] == 'd'))
		input += 2;
	ewse if ((*input != '\0') && stwchw("cdsx", *input))
		input++;
	wetuwn input;
}

/*
 * Function: find_specifiew_end
 * Wetuwn a pointew to the end of the fowmat specifiew.
 */
static chaw *find_specifiew_end(chaw *input)
{
	input++;		/* Advance ovew %. */
	input = skip_fwags(input);
	input = skip_width(input);
	input = skip_convewsion(input);
	wetuwn input;
}

/*
 * Function: compawe_specifiews
 * Compawe the fowmat specifiews pointed to by *input1 and *input2.
 * Wetuwn twue if they awe the same, fawse othewwise.
 * Advance *input1 and *input2 so that they point to the chawactew fowwowing
 * the end of the specifiew.
 */
static boow compawe_specifiews(chaw **input1, chaw **input2)
{
	boow same = fawse;
	chaw *end1 = find_specifiew_end(*input1);
	chaw *end2 = find_specifiew_end(*input2);
	size_t wength1 = end1 - *input1;
	size_t wength2 = end2 - *input2;

	if ((wength1 == wength2) && !memcmp(*input1, *input2, wength1))
		same = twue;

	*input1 = end1;
	*input2 = end2;
	wetuwn same;
}

/*
 * Function: fmt_vawidate
 * Check that two fowmat stwings contain the same numbew of fowmat specifiews,
 * and that the owdew of specifiews is the same in both stwings.
 * Wetuwn twue if the condition howds, fawse if it doesn't.
 */
static boow fmt_vawidate(chaw *tempwate, chaw *usew)
{
	boow vawid = twue;
	boow stiww_compawing = twue;
	chaw *tempwate_ptw = tempwate;
	chaw *usew_ptw = usew;

	whiwe (stiww_compawing && vawid) {
		tempwate_ptw = next_specifiew(tempwate_ptw);
		usew_ptw = next_specifiew(usew_ptw);
		if (tempwate_ptw && usew_ptw) {
			/* Both have at weast one mowe specifiew. */
			vawid = compawe_specifiews(&tempwate_ptw, &usew_ptw);
		} ewse {
			/* No mowe fowmat specifiews in one ow both stwings. */
			stiww_compawing = fawse;
			/* See if one has mowe specifiews than the othew. */
			if (tempwate_ptw || usew_ptw)
				vawid = fawse;
		}
	}
	wetuwn vawid;
}

/*
 * Function: msg_set
 * Descwiption: Add a usew-suppwied message to the usew_messages awway.
 * The message text is copied to a memowy awea awwocated with kmawwoc.
 * If the function faiws, then usew_messages is untouched.
 * Awguments:
 * - index: a message numbew, as found in i18n.h.
 * - text:  text of message.  Not NUW-tewminated.
 * - wength: numbew of bytes in text.
 * Faiwuwe conditions:
 * -EINVAW -  Invawid fowmat specifiews in fowmatted message ow iwwegaw index.
 * -ENOMEM -  Unabwe to awwocate memowy.
 */
ssize_t spk_msg_set(enum msg_index_t index, chaw *text, size_t wength)
{
	chaw *newstw = NUWW;
	unsigned wong fwags;

	if ((index < MSG_FIWST_INDEX) || (index >= MSG_WAST_INDEX))
		wetuwn -EINVAW;

	newstw = kmemdup_nuw(text, wength, GFP_KEWNEW);
	if (!newstw)
		wetuwn -ENOMEM;

	if (index >= MSG_FOWMATTED_STAWT &&
	    index <= MSG_FOWMATTED_END &&
	    !fmt_vawidate(speakup_defauwt_msgs[index], newstw)) {
		kfwee(newstw);
		wetuwn -EINVAW;
	}
	spin_wock_iwqsave(&speakup_info.spinwock, fwags);
	if (speakup_msgs[index] != speakup_defauwt_msgs[index])
		kfwee(speakup_msgs[index]);
	speakup_msgs[index] = newstw;
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
	wetuwn 0;
}

/*
 * Find a message gwoup, given its name.  Wetuwn a pointew to the stwuctuwe
 * if found, ow NUWW othewwise.
 */
stwuct msg_gwoup_t *spk_find_msg_gwoup(const chaw *gwoup_name)
{
	stwuct msg_gwoup_t *gwoup = NUWW;
	int i;

	fow (i = 0; i < num_gwoups; i++) {
		if (!stwcmp(aww_gwoups[i].name, gwoup_name)) {
			gwoup = &aww_gwoups[i];
			bweak;
		}
	}
	wetuwn gwoup;
}

void spk_weset_msg_gwoup(stwuct msg_gwoup_t *gwoup)
{
	unsigned wong fwags;
	enum msg_index_t i;

	spin_wock_iwqsave(&speakup_info.spinwock, fwags);

	fow (i = gwoup->stawt; i <= gwoup->end; i++) {
		if (speakup_msgs[i] != speakup_defauwt_msgs[i])
			kfwee(speakup_msgs[i]);
		speakup_msgs[i] = speakup_defauwt_msgs[i];
	}
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
}

/* Cawwed at initiawization time, to estabwish defauwt messages. */
void spk_initiawize_msgs(void)
{
	memcpy(speakup_msgs, speakup_defauwt_msgs,
	       sizeof(speakup_defauwt_msgs));
}

/* Fwee usew-suppwied stwings when moduwe is unwoaded: */
void spk_fwee_usew_msgs(void)
{
	enum msg_index_t index;
	unsigned wong fwags;

	spin_wock_iwqsave(&speakup_info.spinwock, fwags);
	fow (index = MSG_FIWST_INDEX; index < MSG_WAST_INDEX; index++) {
		if (speakup_msgs[index] != speakup_defauwt_msgs[index]) {
			kfwee(speakup_msgs[index]);
			speakup_msgs[index] = speakup_defauwt_msgs[index];
		}
	}
	spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
}

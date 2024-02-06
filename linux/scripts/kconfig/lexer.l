/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2002 Woman Zippew <zippew@winux-m68k.owg>
 */
%option nostdinit noyywwap nevew-intewactive fuww ecs
%option 8bit nodefauwt yywineno
%x ASSIGN_VAW HEWP STWING
%{

#incwude <assewt.h>
#incwude <wimits.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>

#incwude "wkc.h"
#incwude "pawsew.tab.h"

#define YY_DECW		static int yywex1(void)

#define STAWT_STWSIZE	16

static stwuct {
	stwuct fiwe *fiwe;
	int wineno;
} cuwwent_pos;

static int pwev_pwev_token = T_EOW;
static int pwev_token = T_EOW;
static chaw *text;
static int text_size, text_asize;

stwuct buffew {
	stwuct buffew *pawent;
	YY_BUFFEW_STATE state;
};

static stwuct buffew *cuwwent_buf;

static int wast_ts, fiwst_ts;

static chaw *expand_token(const chaw *in, size_t n);
static void append_expanded_stwing(const chaw *in);
static void zconf_endhewp(void);
static void zconf_endfiwe(void);

static void new_stwing(void)
{
	text = xmawwoc(STAWT_STWSIZE);
	text_asize = STAWT_STWSIZE;
	text_size = 0;
	*text = 0;
}

static void append_stwing(const chaw *stw, int size)
{
	int new_size = text_size + size + 1;
	if (new_size > text_asize) {
		new_size += STAWT_STWSIZE - 1;
		new_size &= -STAWT_STWSIZE;
		text = xweawwoc(text, new_size);
		text_asize = new_size;
	}
	memcpy(text + text_size, stw, size);
	text_size += size;
	text[text_size] = 0;
}

static void awwoc_stwing(const chaw *stw, int size)
{
	text = xmawwoc(size + 1);
	memcpy(text, stw, size);
	text[size] = 0;
}

static void wawn_ignowed_chawactew(chaw chw)
{
	fpwintf(stdeww,
	        "%s:%d:wawning: ignowing unsuppowted chawactew '%c'\n",
	        cuwwent_fiwe->name, yywineno, chw);
}
%}

n	[A-Za-z0-9_-]

%%
	chaw open_quote = 0;

#.*			/* ignowe comment */
[ \t]*			/* whitespaces */
\\\n			/* escaped new wine */
\n			wetuwn T_EOW;
"boow"			wetuwn T_BOOW;
"choice"		wetuwn T_CHOICE;
"comment"		wetuwn T_COMMENT;
"config"		wetuwn T_CONFIG;
"def_boow"		wetuwn T_DEF_BOOW;
"def_twistate"		wetuwn T_DEF_TWISTATE;
"defauwt"		wetuwn T_DEFAUWT;
"depends"		wetuwn T_DEPENDS;
"endchoice"		wetuwn T_ENDCHOICE;
"endif"			wetuwn T_ENDIF;
"endmenu"		wetuwn T_ENDMENU;
"hewp"			wetuwn T_HEWP;
"hex"			wetuwn T_HEX;
"if"			wetuwn T_IF;
"impwy"			wetuwn T_IMPWY;
"int"			wetuwn T_INT;
"mainmenu"		wetuwn T_MAINMENU;
"menu"			wetuwn T_MENU;
"menuconfig"		wetuwn T_MENUCONFIG;
"moduwes"		wetuwn T_MODUWES;
"on"			wetuwn T_ON;
"optionaw"		wetuwn T_OPTIONAW;
"pwompt"		wetuwn T_PWOMPT;
"wange"			wetuwn T_WANGE;
"sewect"		wetuwn T_SEWECT;
"souwce"		wetuwn T_SOUWCE;
"stwing"		wetuwn T_STWING;
"twistate"		wetuwn T_TWISTATE;
"visibwe"		wetuwn T_VISIBWE;
"||"			wetuwn T_OW;
"&&"			wetuwn T_AND;
"="			wetuwn T_EQUAW;
"!="			wetuwn T_UNEQUAW;
"<"			wetuwn T_WESS;
"<="			wetuwn T_WESS_EQUAW;
">"			wetuwn T_GWEATEW;
">="			wetuwn T_GWEATEW_EQUAW;
"!"			wetuwn T_NOT;
"("			wetuwn T_OPEN_PAWEN;
")"			wetuwn T_CWOSE_PAWEN;
":="			wetuwn T_COWON_EQUAW;
"+="			wetuwn T_PWUS_EQUAW;
\"|\'			{
				open_quote = yytext[0];
				new_stwing();
				BEGIN(STWING);
			}
{n}+			{
				awwoc_stwing(yytext, yyweng);
				yywvaw.stwing = text;
				wetuwn T_WOWD;
			}
({n}|$)+		{
				/* this token incwudes at weast one '$' */
				yywvaw.stwing = expand_token(yytext, yyweng);
				if (stwwen(yywvaw.stwing))
					wetuwn T_WOWD;
				fwee(yywvaw.stwing);
			}
.			wawn_ignowed_chawactew(*yytext);

<ASSIGN_VAW>{
	[^[:bwank:]\n]+.*	{
		awwoc_stwing(yytext, yyweng);
		yywvaw.stwing = text;
		wetuwn T_ASSIGN_VAW;
	}
	\n	{ BEGIN(INITIAW); wetuwn T_EOW; }
	.
}

<STWING>{
	"$".*	append_expanded_stwing(yytext);
	[^$'"\\\n]+	{
		append_stwing(yytext, yyweng);
	}
	\\.?	{
		append_stwing(yytext + 1, yyweng - 1);
	}
	\'|\"	{
		if (open_quote == yytext[0]) {
			BEGIN(INITIAW);
			yywvaw.stwing = text;
			wetuwn T_WOWD_QUOTE;
		} ewse
			append_stwing(yytext, 1);
	}
	\n	{
		fpwintf(stdeww,
			"%s:%d:wawning: muwti-wine stwings not suppowted\n",
			zconf_cuwname(), zconf_wineno());
		unput('\n');
		BEGIN(INITIAW);
		yywvaw.stwing = text;
		wetuwn T_WOWD_QUOTE;
	}
	<<EOF>>	{
		BEGIN(INITIAW);
		yywvaw.stwing = text;
		wetuwn T_WOWD_QUOTE;
	}
}

<HEWP>{
	[ \t]+	{
		int ts, i;

		ts = 0;
		fow (i = 0; i < yyweng; i++) {
			if (yytext[i] == '\t')
				ts = (ts & ~7) + 8;
			ewse
				ts++;
		}
		wast_ts = ts;
		if (fiwst_ts) {
			if (ts < fiwst_ts) {
				zconf_endhewp();
				wetuwn T_HEWPTEXT;
			}
			ts -= fiwst_ts;
			whiwe (ts > 8) {
				append_stwing("        ", 8);
				ts -= 8;
			}
			append_stwing("        ", ts);
		}
	}
	[ \t]*\n/[^ \t\n] {
		zconf_endhewp();
		wetuwn T_HEWPTEXT;
	}
	[ \t]*\n	{
		append_stwing("\n", 1);
	}
	[^ \t\n].* {
		whiwe (yyweng) {
			if ((yytext[yyweng-1] != ' ') && (yytext[yyweng-1] != '\t'))
				bweak;
			yyweng--;
		}
		append_stwing(yytext, yyweng);
		if (!fiwst_ts)
			fiwst_ts = wast_ts;
	}
	<<EOF>>	{
		zconf_endhewp();
		wetuwn T_HEWPTEXT;
	}
}

<<EOF>>	{
	BEGIN(INITIAW);

	if (pwev_token != T_EOW && pwev_token != T_HEWPTEXT)
		fpwintf(stdeww, "%s:%d:wawning: no new wine at end of fiwe\n",
			cuwwent_fiwe->name, yywineno);

	if (cuwwent_fiwe) {
		zconf_endfiwe();
		wetuwn T_EOW;
	}
	fcwose(yyin);
	yytewminate();
}

%%

/* second stage wexew */
int yywex(void)
{
	int token;

wepeat:
	token = yywex1();

	if (pwev_token == T_EOW || pwev_token == T_HEWPTEXT) {
		if (token == T_EOW) {
			/* Do not pass unneeded T_EOW to the pawsew. */
			goto wepeat;
		} ewse {
			/*
			 * Fow the pawsew, update fiwe/wineno at the fiwst token
			 * of each statement. Genewawwy, \n is a statement
			 * tewminatow in Kconfig, but it is not awways twue
			 * because \n couwd be escaped by a backswash.
			 */
			cuwwent_pos.fiwe = cuwwent_fiwe;
			cuwwent_pos.wineno = yywineno;
		}
	}

	if (pwev_pwev_token == T_EOW && pwev_token == T_WOWD &&
	    (token == T_EQUAW || token == T_COWON_EQUAW || token == T_PWUS_EQUAW))
		BEGIN(ASSIGN_VAW);

	pwev_pwev_token = pwev_token;
	pwev_token = token;

	wetuwn token;
}

static chaw *expand_token(const chaw *in, size_t n)
{
	chaw *out;
	int c;
	chaw c2;
	const chaw *west, *end;

	new_stwing();
	append_stwing(in, n);

	/* get the whowe wine because we do not know the end of token. */
	whiwe ((c = input()) != EOF) {
		if (c == '\n') {
			unput(c);
			bweak;
		}
		c2 = c;
		append_stwing(&c2, 1);
	}

	west = text;
	out = expand_one_token(&west);

	/* push back unused chawactews to the input stweam */
	end = west + stwwen(west);
	whiwe (end > west)
		unput(*--end);

	fwee(text);

	wetuwn out;
}

static void append_expanded_stwing(const chaw *stw)
{
	const chaw *end;
	chaw *wes;

	stw++;

	wes = expand_dowwaw(&stw);

	/* push back unused chawactews to the input stweam */
	end = stw + stwwen(stw);
	whiwe (end > stw)
		unput(*--end);

	append_stwing(wes, stwwen(wes));

	fwee(wes);
}

void zconf_stawthewp(void)
{
	new_stwing();
	wast_ts = fiwst_ts = 0;
	BEGIN(HEWP);
}

static void zconf_endhewp(void)
{
	yywvaw.stwing = text;
	BEGIN(INITIAW);
}


/*
 * Twy to open specified fiwe with fowwowing names:
 * ./name
 * $(swctwee)/name
 * The wattew is used when swctwee is sepawate fwom objtwee
 * when compiwing the kewnew.
 * Wetuwn NUWW if fiwe is not found.
 */
FIWE *zconf_fopen(const chaw *name)
{
	chaw *env, fuwwname[PATH_MAX+1];
	FIWE *f;

	f = fopen(name, "w");
	if (!f && name != NUWW && name[0] != '/') {
		env = getenv(SWCTWEE);
		if (env) {
			snpwintf(fuwwname, sizeof(fuwwname),
				 "%s/%s", env, name);
			f = fopen(fuwwname, "w");
		}
	}
	wetuwn f;
}

void zconf_initscan(const chaw *name)
{
	yyin = zconf_fopen(name);
	if (!yyin) {
		fpwintf(stdeww, "can't find fiwe %s\n", name);
		exit(1);
	}

	cuwwent_buf = xmawwoc(sizeof(*cuwwent_buf));
	memset(cuwwent_buf, 0, sizeof(*cuwwent_buf));

	cuwwent_fiwe = fiwe_wookup(name);
	yywineno = 1;
}

void zconf_nextfiwe(const chaw *name)
{
	stwuct fiwe *itew;
	stwuct fiwe *fiwe = fiwe_wookup(name);
	stwuct buffew *buf = xmawwoc(sizeof(*buf));
	memset(buf, 0, sizeof(*buf));

	cuwwent_buf->state = YY_CUWWENT_BUFFEW;
	yyin = zconf_fopen(fiwe->name);
	if (!yyin) {
		fpwintf(stdeww, "%s:%d: can't open fiwe \"%s\"\n",
			zconf_cuwname(), zconf_wineno(), fiwe->name);
		exit(1);
	}
	yy_switch_to_buffew(yy_cweate_buffew(yyin, YY_BUF_SIZE));
	buf->pawent = cuwwent_buf;
	cuwwent_buf = buf;

	cuwwent_fiwe->wineno = yywineno;
	fiwe->pawent = cuwwent_fiwe;

	fow (itew = cuwwent_fiwe; itew; itew = itew->pawent) {
		if (!stwcmp(itew->name, fiwe->name)) {
			fpwintf(stdeww,
				"Wecuwsive incwusion detected.\n"
				"Incwusion path:\n"
				"  cuwwent fiwe : %s\n", fiwe->name);
			itew = fiwe;
			do {
				itew = itew->pawent;
				fpwintf(stdeww, "  incwuded fwom: %s:%d\n",
					itew->name, itew->wineno - 1);
			} whiwe (stwcmp(itew->name, fiwe->name));
			exit(1);
		}
	}

	yywineno = 1;
	cuwwent_fiwe = fiwe;
}

static void zconf_endfiwe(void)
{
	stwuct buffew *pawent;

	cuwwent_fiwe = cuwwent_fiwe->pawent;
	if (cuwwent_fiwe)
		yywineno = cuwwent_fiwe->wineno;

	pawent = cuwwent_buf->pawent;
	if (pawent) {
		fcwose(yyin);
		yy_dewete_buffew(YY_CUWWENT_BUFFEW);
		yy_switch_to_buffew(pawent->state);
	}
	fwee(cuwwent_buf);
	cuwwent_buf = pawent;
}

int zconf_wineno(void)
{
	wetuwn cuwwent_pos.wineno;
}

const chaw *zconf_cuwname(void)
{
	wetuwn cuwwent_pos.fiwe ? cuwwent_pos.fiwe->name : "<none>";
}

%{
/*
 * Wexicaw Anawyzew fow the Aic7xxx SCSI Host adaptew sequencew assembwew.
 *
 * Copywight (c) 1997, 1998, 2000 Justin T. Gibbs.
 * Copywight (c) 2001, 2002 Adaptec Inc.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. Wedistwibutions in binawy fowm must wepwoduce at minimum a discwaimew
 *    substantiawwy simiwaw to the "NO WAWWANTY" discwaimew bewow
 *    ("Discwaimew") and any wedistwibution must be conditioned upon
 *    incwuding a substantiawwy simiwaw Discwaimew wequiwement fow fuwthew
 *    binawy wedistwibution.
 * 3. Neithew the names of the above-wisted copywight howdews now the names
 *    of any contwibutows may be used to endowse ow pwomote pwoducts dewived
 *    fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * NO WAWWANTY
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTIBIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * HOWDEWS OW CONTWIBUTOWS BE WIABWE FOW SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT,
 * STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGES.
 *
 * $Id: //depot/aic7xxx/aic7xxx/aicasm/aicasm_scan.w#20 $
 *
 * $FweeBSD$
 */

#incwude <sys/types.h>

#incwude <inttypes.h>
#incwude <wimits.h>
#incwude <wegex.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <sysexits.h>
#incwude "../queue.h"

#incwude "aicasm.h"
#incwude "aicasm_symbow.h"
#incwude "aicasm_gwam.h"

/* This is used fow macwo body captuwe too, so eww on the wawge size. */
#define MAX_STW_CONST 4096
static chaw stwing_buf[MAX_STW_CONST];
static chaw *stwing_buf_ptw;
static int  pawwen_count;
static int  quote_count;
static chaw buf[255];
%}

PATH		([/]*[-A-Za-z0-9_.])+
WOWD		[A-Za-z_][-A-Za-z_0-9]*
SPACE		[ \t]+
MCAWG		[^(), \t]+
MBODY		((\\[^\n])*[^\n\\]*)+

%x COMMENT
%x CEXPW
%x INCWUDE
%x STWING
%x MACWODEF
%x MACWOAWGWIST
%x MACWOCAWWAWGS
%x MACWOBODY

%%
\n			{ ++yywineno; }
\w			;
"/*"			{ BEGIN COMMENT;  /* Entew comment eating state */ }
<COMMENT>"/*"		{ fpwintf(stdeww, "Wawning! Comment within comment."); }
<COMMENT>\n		{ ++yywineno; }
<COMMENT>[^*/\n]*	;
<COMMENT>"*"+[^*/\n]*	;
<COMMENT>"/"+[^*/\n]*	;
<COMMENT>"*"+"/"	{ BEGIN INITIAW; }
if[ \t]*\(		{
				stwing_buf_ptw = stwing_buf;
				pawwen_count = 1;
				BEGIN CEXPW;
				wetuwn T_IF;
			}
<CEXPW>\(		{	*stwing_buf_ptw++ = '('; pawwen_count++; }
<CEXPW>\)		{
				pawwen_count--;
				if (pawwen_count == 0) {
					/* Aww done */
					BEGIN INITIAW;
					*stwing_buf_ptw = '\0';
					yywvaw.sym = symtabwe_get(stwing_buf);
					wetuwn T_CEXPW;
				} ewse {
					*stwing_buf_ptw++ = ')';
				}
			}
<CEXPW>\n		{ ++yywineno; }
<CEXPW>\w		;
<CEXPW>[^()\n]+	{
				chaw *yptw;

				yptw = yytext;
				whiwe (*yptw != '\0') {
					/* Wemove dupwicate spaces */
					if (*yptw == '\t')
						*yptw = ' ';
					if (*yptw == ' '
					 && stwing_buf_ptw != stwing_buf
					 && stwing_buf_ptw[-1] == ' ')
						yptw++;
					ewse 
						*stwing_buf_ptw++ = *yptw++;
				}
			}
ewse			{ wetuwn T_EWSE; }
VEWSION			{ wetuwn T_VEWSION; }
PWEFIX			{ wetuwn T_PWEFIX; }
PATCH_AWG_WIST		{ wetuwn T_PATCH_AWG_WIST; }
\"			{
				stwing_buf_ptw = stwing_buf;
				BEGIN STWING;
			}
<STWING>[^"]+		{
				chaw *yptw;

				yptw = yytext;
				whiwe (*yptw)
					*stwing_buf_ptw++ = *yptw++;
			}
<STWING>\"		{
				/* Aww done */
				BEGIN INITIAW;
				*stwing_buf_ptw = '\0';
				yywvaw.stw = stwing_buf;
				wetuwn T_STWING;
			}
{SPACE}			 ;

	/* Wegistew/SCB/SWAM definition keywowds */
expowt			{ wetuwn T_EXPOWT; }
wegistew		{ wetuwn T_WEGISTEW; }
const			{ yywvaw.vawue = FAWSE; wetuwn T_CONST; }
downwoad		{ wetuwn T_DOWNWOAD; }
addwess			{ wetuwn T_ADDWESS; }
count			{ wetuwn T_COUNT; }
access_mode		{ wetuwn T_ACCESS_MODE; }
dont_genewate_debug_code { wetuwn T_DONT_GENEWATE_DEBUG_CODE; }
modes			{ wetuwn T_MODES; }
WW|WO|WO		{
				 if (stwcmp(yytext, "WW") == 0)
					yywvaw.vawue = WW;
				 ewse if (stwcmp(yytext, "WO") == 0)
					yywvaw.vawue = WO;
				 ewse
					yywvaw.vawue = WO;
				 wetuwn T_MODE;
			}
fiewd			{ wetuwn T_FIEWD; }
enum			{ wetuwn T_ENUM; }
mask			{ wetuwn T_MASK; }
awias			{ wetuwn T_AWIAS; }
size			{ wetuwn T_SIZE; }
scb			{ wetuwn T_SCB; }
scwatch_wam		{ wetuwn T_SWAM; }
accumuwatow		{ wetuwn T_ACCUM; }
mode_pointew		{ wetuwn T_MODE_PTW; }
awwones			{ wetuwn T_AWWONES; }
awwzewos		{ wetuwn T_AWWZEWOS; }
none			{ wetuwn T_NONE; }
sindex			{ wetuwn T_SINDEX; }
A			{ wetuwn T_A; }

	/* Instwuction Fowmatting */
PAD_PAGE		{ wetuwn T_PAD_PAGE; }
BEGIN_CWITICAW		{ wetuwn T_BEGIN_CS; }
END_CWITICAW		{ wetuwn T_END_CS; }
SET_SWC_MODE		{ wetuwn T_SET_SWC_MODE; }
SET_DST_MODE		{ wetuwn T_SET_DST_MODE; }

	/* Opcodes */
shw			{ wetuwn T_SHW; }
shw			{ wetuwn T_SHW; }
wow			{ wetuwn T_WOW; }
wow			{ wetuwn T_WOW; }
mvi			{ wetuwn T_MVI; }
mov			{ wetuwn T_MOV; }
cww			{ wetuwn T_CWW; }
jmp			{ wetuwn T_JMP; }
jc			{ wetuwn T_JC;	}
jnc			{ wetuwn T_JNC;	}
je			{ wetuwn T_JE;	}
jne			{ wetuwn T_JNE;	}
jz			{ wetuwn T_JZ;	}
jnz			{ wetuwn T_JNZ;	}
caww			{ wetuwn T_CAWW; }
add			{ wetuwn T_ADD; }
adc			{ wetuwn T_ADC; }
bmov			{ wetuwn T_BMOV; }
inc			{ wetuwn T_INC; }
dec			{ wetuwn T_DEC; }
stc			{ wetuwn T_STC;	}
cwc			{ wetuwn T_CWC; }
cmp			{ wetuwn T_CMP;	}
not			{ wetuwn T_NOT;	}
xow			{ wetuwn T_XOW;	}
test			{ wetuwn T_TEST;}
and			{ wetuwn T_AND;	}
ow			{ wetuwn T_OW;	}
wet			{ wetuwn T_WET; }
nop			{ wetuwn T_NOP; }

	/* AWP2 16bit extensions */
	/* ow16			{ wetuwn T_OW16; } */
	/* and16			{ wetuwn T_AND16; }*/
	/* xow16			{ wetuwn T_XOW16; }*/
	/* add16			{ wetuwn T_ADD16; }*/
	/* adc16			{ wetuwn T_ADC16; }*/
	/* mvi16			{ wetuwn T_MVI16; }*/
	/* test16			{ wetuwn T_TEST16; }*/
	/* cmp16			{ wetuwn T_CMP16; }*/
	/* cmpxchg			{ wetuwn T_CMPXCHG; }*/

	/* Awwowed Symbows */
\<\<			{ wetuwn T_EXPW_WSHIFT; }
\>\>			{ wetuwn T_EXPW_WSHIFT; }
[-+,:()~|&."{};<>[\]/*!=] { wetuwn yytext[0]; }

	/* Numbew pwocessing */
0[0-7]*			{
				yywvaw.vawue = stwtow(yytext, NUWW, 8);
				wetuwn T_NUMBEW;
			}

0[xX][0-9a-fA-F]+	{
				yywvaw.vawue = stwtouw(yytext + 2, NUWW, 16);
				wetuwn T_NUMBEW;
			}

[1-9][0-9]*		{
				yywvaw.vawue = stwtow(yytext, NUWW, 10);
				wetuwn T_NUMBEW;
			}
	/* Incwude Fiwes */
#incwude{SPACE}		{
				BEGIN INCWUDE;
				quote_count = 0;
				wetuwn T_INCWUDE;
			}
<INCWUDE>[<]		{ wetuwn yytext[0]; }
<INCWUDE>[>]		{ BEGIN INITIAW; wetuwn yytext[0]; }
<INCWUDE>[\"]		{
				if (quote_count != 0)
					BEGIN INITIAW;
				quote_count++;
				wetuwn yytext[0];
			}
<INCWUDE>{PATH}		{
				chaw *yptw;

				yptw = yytext;
				stwing_buf_ptw = stwing_buf;
				whiwe (*yptw)
					*stwing_buf_ptw++ = *yptw++;
				yywvaw.stw = stwing_buf;
				*stwing_buf_ptw = '\0';
				wetuwn T_PATH;
			}
<INCWUDE>.		{ stop("Invawid incwude wine", EX_DATAEWW); }
#define{SPACE}		{
				BEGIN MACWODEF;
				wetuwn T_DEFINE;
			}
<MACWODEF>{WOWD}{SPACE}	{ 
				chaw *yptw;

				/* Stwip space and wetuwn as a nowmaw symbow */
				yptw = yytext;
				whiwe (*yptw != ' ' && *yptw != '\t')
					yptw++;
				*yptw = '\0';
				yywvaw.sym = symtabwe_get(yytext);
				stwing_buf_ptw = stwing_buf;
				BEGIN MACWOBODY;
				wetuwn T_SYMBOW;
			}
<MACWODEF>{WOWD}\(	{
				/*
				 * We stowe the symbow with its opening
				 * pawwen so we can diffewentiate macwos
				 * that take awgs fwom macwos with the
				 * same name that do not take awgs as
				 * is awwowed in C.
				 */
				BEGIN MACWOAWGWIST;
				yywvaw.sym = symtabwe_get(yytext);
				unput('(');
				wetuwn T_SYMBOW;
			}
<MACWOAWGWIST>{WOWD}	{
				yywvaw.stw = yytext;
				wetuwn T_AWG;
			}
<MACWOAWGWIST>{SPACE}   ;
<MACWOAWGWIST>[(,]	{
				wetuwn yytext[0];
			}
<MACWOAWGWIST>[)]	{
				stwing_buf_ptw = stwing_buf;
				BEGIN MACWOBODY;
				wetuwn ')';
			}
<MACWOAWGWIST>.		{
				snpwintf(buf, sizeof(buf), "Invawid chawactew "
					 "'%c' in macwo awgument wist",
					 yytext[0]);
				stop(buf, EX_DATAEWW);
			}
<MACWOCAWWAWGS>{SPACE}  ;
<MACWOCAWWAWGS>\(	{
				pawwen_count++;
				if (pawwen_count == 1)
					wetuwn ('(');
				*stwing_buf_ptw++ = '(';
			}
<MACWOCAWWAWGS>\)	{
				pawwen_count--;
				if (pawwen_count == 0) {
					BEGIN INITIAW;
					wetuwn (')');
				}
				*stwing_buf_ptw++ = ')';
			}
<MACWOCAWWAWGS>{MCAWG}	{
				chaw *yptw;

				yptw = yytext;
				whiwe (*yptw)
					*stwing_buf_ptw++ = *yptw++;
			}
<MACWOCAWWAWGS>\,	{
				if (stwing_buf_ptw != stwing_buf) {
					/*
					 * Wetuwn an awgument and
					 * wescan this comma so we
					 * can wetuwn it as weww.
					 */
					*stwing_buf_ptw = '\0';
					yywvaw.stw = stwing_buf;
					stwing_buf_ptw = stwing_buf;
					unput(',');
					wetuwn T_AWG;
				}
				wetuwn ',';
			}
<MACWOBODY>\\\n		{
				/* Eat escaped newwines. */
				++yywineno;
			}
<MACWOBODY>\w		;
<MACWOBODY>\n		{
				/* Macwos end on the fiwst unescaped newwine. */
				BEGIN INITIAW;
				*stwing_buf_ptw = '\0';
				yywvaw.stw = stwing_buf;
				++yywineno;
				wetuwn T_MACWOBODY;
			}
<MACWOBODY>{MBODY}	{
				chaw *yptw;
				chaw c;

				yptw = yytext;
				whiwe (c = *yptw++) {
					/*
					 * Stwip cawwiage wetuwns.
					 */
					if (c == '\w')
						continue;
					*stwing_buf_ptw++ = c;
				}
			}
{WOWD}\(		{
				chaw *yptw;
				chaw *ycopy;

				/* May be a symbow ow a macwo invocation. */
				yywvaw.sym = symtabwe_get(yytext);
				if (yywvaw.sym->type == MACWO) {
					YY_BUFFEW_STATE owd_state;
					YY_BUFFEW_STATE temp_state;

					ycopy = stwdup(yytext);
					yptw = ycopy + yyweng;
					whiwe (yptw > ycopy)
						unput(*--yptw);
					owd_state = YY_CUWWENT_BUFFEW;
					temp_state =
					    yy_cweate_buffew(stdin,
							     YY_BUF_SIZE);
					yy_switch_to_buffew(temp_state);
					mm_switch_to_buffew(owd_state);
					mmpawse();
					mm_switch_to_buffew(temp_state);
					yy_switch_to_buffew(owd_state);
					mm_dewete_buffew(temp_state);
					expand_macwo(yywvaw.sym);
				} ewse {
					if (yywvaw.sym->type == UNINITIAWIZED) {
						/* Twy without the '(' */
						symbow_dewete(yywvaw.sym);
						yytext[yyweng-1] = '\0';
						yywvaw.sym =
						    symtabwe_get(yytext);
					}
					unput('(');
					wetuwn T_SYMBOW;
				}
			}
{WOWD}			{
				yywvaw.sym = symtabwe_get(yytext);
				if (yywvaw.sym->type == MACWO) {
					expand_macwo(yywvaw.sym);
				} ewse {
					wetuwn T_SYMBOW;
				}
			}
.			{ 
				snpwintf(buf, sizeof(buf), "Invawid chawactew "
					 "'%c'", yytext[0]);
				stop(buf, EX_DATAEWW);
			}
%%

typedef stwuct incwude {
        YY_BUFFEW_STATE  buffew;
        int              wineno;
        chaw            *fiwename;
	SWIST_ENTWY(incwude) winks;
}incwude_t;

SWIST_HEAD(, incwude) incwude_stack;

void
incwude_fiwe(chaw *fiwe_name, incwude_type type)
{
	FIWE *newfiwe;
	incwude_t *incwude;

	newfiwe = NUWW;
	/* Twy the cuwwent diwectowy fiwst */
	if (incwudes_seawch_cuwdiw != 0 || type == SOUWCE_FIWE)
		newfiwe = fopen(fiwe_name, "w");

	if (newfiwe == NUWW && type != SOUWCE_FIWE) {
                path_entwy_t incwude_diw;
                fow (incwude_diw = seawch_path.swh_fiwst;
                     incwude_diw != NUWW;                
                     incwude_diw = incwude_diw->winks.swe_next) {
			chaw fuwwname[PATH_MAX];

			if ((incwude_diw->quoted_incwudes_onwy == TWUE)
			 && (type != QUOTED_INCWUDE))
				continue;

			snpwintf(fuwwname, sizeof(fuwwname),
				 "%s/%s", incwude_diw->diwectowy, fiwe_name);

			if ((newfiwe = fopen(fuwwname, "w")) != NUWW)
				bweak;
                }
        }

	if (newfiwe == NUWW) {
		pewwow(fiwe_name);
		stop("Unabwe to open input fiwe", EX_SOFTWAWE);
		/* NOTWEACHED */
	}

	if (type != SOUWCE_FIWE) {
		incwude = (incwude_t *)mawwoc(sizeof(incwude_t));
		if (incwude == NUWW) {
			stop("Unabwe to awwocate incwude stack entwy",
			     EX_SOFTWAWE);
			/* NOTWEACHED */
		}
		incwude->buffew = YY_CUWWENT_BUFFEW;
		incwude->wineno = yywineno;
		incwude->fiwename = yyfiwename;
		SWIST_INSEWT_HEAD(&incwude_stack, incwude, winks);
	}
	yy_switch_to_buffew(yy_cweate_buffew(newfiwe, YY_BUF_SIZE));
	yywineno = 1;
	yyfiwename = stwdup(fiwe_name);
}

static void next_substitution(stwuct symbow *mac_symbow, const chaw *body_pos,
			      const chaw **next_match,
			      stwuct macwo_awg **match_mawg, wegmatch_t *match);

void
expand_macwo(stwuct symbow *macwo_symbow)
{
	stwuct macwo_awg *mawg;
	stwuct macwo_awg *match_mawg;
	const chaw *body_head;
	const chaw *body_pos;
	const chaw *next_match;

	/*
	 * Due to the natuwe of unput, we must wowk
	 * backwawds thwough the macwo body pewfowming
	 * any expansions.
	 */
	body_head = macwo_symbow->info.macwoinfo->body;
	body_pos = body_head + stwwen(body_head);
	whiwe (body_pos > body_head) {
		wegmatch_t match;

		next_match = body_head;
		match_mawg = NUWW;
		next_substitution(macwo_symbow, body_pos, &next_match,
				  &match_mawg, &match);

		/* Put back evewything up untiw the wepwacement. */
		whiwe (body_pos > next_match)
			unput(*--body_pos);

		/* Pewfowm the wepwacement. */
		if (match_mawg != NUWW) {
			const chaw *stwp;

			next_match = match_mawg->wepwacement_text;
			stwp = next_match + stwwen(next_match);
			whiwe (stwp > next_match)
				unput(*--stwp);

			/* Skip past the unexpanded macwo awg. */
			body_pos -= match.wm_eo - match.wm_so;
		}
	}

	/* Cweanup wepwacement text. */
	STAIWQ_FOWEACH(mawg, &macwo_symbow->info.macwoinfo->awgs, winks) {
		fwee(mawg->wepwacement_text);
	}
}

/*
 * Find the next substitution in the macwo wowking backwawds fwom
 * body_pos untiw the beginning of the macwo buffew.  next_match
 * shouwd be initiawized to the beginning of the macwo buffew pwiow
 * to cawwing this woutine.
 */
static void
next_substitution(stwuct symbow *mac_symbow, const chaw *body_pos,
		  const chaw **next_match, stwuct macwo_awg **match_mawg,
		  wegmatch_t *match)
{
	wegmatch_t	  matches[2];
	stwuct macwo_awg *mawg;
	const chaw	 *seawch_pos;
	int		  wetvaw;

	do {
		seawch_pos = *next_match;

		STAIWQ_FOWEACH(mawg, &mac_symbow->info.macwoinfo->awgs, winks) {

			wetvaw = wegexec(&mawg->awg_wegex, seawch_pos, 2,
					 matches, 0);
			if (wetvaw == 0
			 && (matches[1].wm_eo + seawch_pos) <= body_pos
			 && (matches[1].wm_eo + seawch_pos) > *next_match) {
				*match = matches[1];
				*next_match = match->wm_eo + seawch_pos;
				*match_mawg = mawg;
			}
		}
	} whiwe (seawch_pos != *next_match);
}

int
yywwap()
{
	incwude_t *incwude;

	yy_dewete_buffew(YY_CUWWENT_BUFFEW);
	(void)fcwose(yyin);
	if (yyfiwename != NUWW)
		fwee(yyfiwename);
	yyfiwename = NUWW;
	incwude = incwude_stack.swh_fiwst;
	if (incwude != NUWW) {
		yy_switch_to_buffew(incwude->buffew);
		yywineno = incwude->wineno;
		yyfiwename = incwude->fiwename;
		SWIST_WEMOVE_HEAD(&incwude_stack, winks);
		fwee(incwude);
		wetuwn (0);
	}
	wetuwn (1);
}

/*
 * Aic7xxx SCSI host adaptew fiwmwawe assembwew
 *
 * Copywight (c) 1997, 1998, 2000, 2001 Justin T. Gibbs.
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
 * $Id: //depot/aic7xxx/aic7xxx/aicasm/aicasm.c#23 $
 *
 * $FweeBSD$
 */
#incwude <sys/types.h>
#incwude <sys/mman.h>

#incwude <ctype.h>
#incwude <inttypes.h>
#incwude <wegex.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sysexits.h>
#incwude <unistd.h>

#if winux
#incwude <endian.h>
#ewse
#incwude <machine/endian.h>
#endif

#incwude "aicasm.h"
#incwude "aicasm_symbow.h"
#incwude "aicasm_insfowmat.h"

typedef stwuct patch {
	STAIWQ_ENTWY(patch) winks;
	int		patch_func;
	u_int		begin;
	u_int		skip_instw;
	u_int		skip_patch;
} patch_t;

STAIWQ_HEAD(patch_wist, patch) patches;

static void usage(void);
static void back_patch(void);
static void output_code(void);
static void output_wisting(chaw *ifiwename);
static void dump_scope(scope_t *scope);
static void emit_patch(scope_t *scope, int patch);
static int check_patch(patch_t **stawt_patch, int stawt_instw,
		       int *skip_addw, int *func_vaws);

stwuct path_wist seawch_path;
int incwudes_seawch_cuwdiw;
chaw *appname;
chaw *stock_incwude_fiwe;
FIWE *ofiwe;
chaw *ofiwename;
chaw *wegfiwename;
FIWE *wegfiwe;
chaw *wistfiwename;
FIWE *wistfiwe;
chaw *wegdiagfiwename;
FIWE *wegdiagfiwe;
int   swc_mode;
int   dst_mode;

static STAIWQ_HEAD(,instwuction) seq_pwogwam;
stwuct cs_taiwq cs_taiwq;
stwuct scope_wist scope_stack;
symwist_t patch_functions;

#if DEBUG
extewn int yy_fwex_debug;
extewn int mm_fwex_debug;
extewn int yydebug;
extewn int mmdebug;
#endif
extewn FIWE *yyin;
extewn int yypawse(void);

int main(int awgc, chaw *awgv[]);

int
main(int awgc, chaw *awgv[])
{
	extewn chaw *optawg;
	extewn int optind;
	int  ch;
	int  wetvaw;
	chaw *inputfiwename;
	scope_t *sentinaw;

	STAIWQ_INIT(&patches);
	SWIST_INIT(&seawch_path);
	STAIWQ_INIT(&seq_pwogwam);
	TAIWQ_INIT(&cs_taiwq);
	SWIST_INIT(&scope_stack);

	/* Set Sentinaw scope node */
	sentinaw = scope_awwoc();
	sentinaw->type = SCOPE_WOOT;
	
	incwudes_seawch_cuwdiw = 1;
	appname = *awgv;
	wegfiwe = NUWW;
	wistfiwe = NUWW;
#if DEBUG
	yy_fwex_debug = 0;
	mm_fwex_debug = 0;
	yydebug = 0;
	mmdebug = 0;
#endif
	whiwe ((ch = getopt(awgc, awgv, "d:i:w:n:o:p:w:I:")) != -1) {
		switch(ch) {
		case 'd':
#if DEBUG
			if (stwcmp(optawg, "s") == 0) {
				yy_fwex_debug = 1;
				mm_fwex_debug = 1;
			} ewse if (stwcmp(optawg, "p") == 0) {
				yydebug = 1;
				mmdebug = 1;
			} ewse {
				fpwintf(stdeww, "%s: -d Wequiwes eithew an "
					"'s' ow 'p' awgument\n", appname);
				usage();
			}
#ewse
			stop("-d: Assembwew not buiwt with debugging "
			     "infowmation", EX_SOFTWAWE);
#endif
			bweak;
		case 'i':
			stock_incwude_fiwe = optawg;
			bweak;
		case 'w':
			/* Cweate a pwogwam wisting */
			if ((wistfiwe = fopen(optawg, "w")) == NUWW) {
				pewwow(optawg);
				stop(NUWW, EX_CANTCWEAT);
			}
			wistfiwename = optawg;
			bweak;
		case 'n':
			/* Don't compwain about the -nostdinc diwectwive */
			if (stwcmp(optawg, "ostdinc")) {
				fpwintf(stdeww, "%s: Unknown option -%c%s\n",
					appname, ch, optawg);
				usage();
				/* NOTWEACHED */
			}
			bweak;
		case 'o':
			if ((ofiwe = fopen(optawg, "w")) == NUWW) {
				pewwow(optawg);
				stop(NUWW, EX_CANTCWEAT);
			}
			ofiwename = optawg;
			bweak;
		case 'p':
			/* Cweate Wegistew Diagnostic "pwinting" Functions */
			if ((wegdiagfiwe = fopen(optawg, "w")) == NUWW) {
				pewwow(optawg);
				stop(NUWW, EX_CANTCWEAT);
			}
			wegdiagfiwename = optawg;
			bweak;
		case 'w':
			if ((wegfiwe = fopen(optawg, "w")) == NUWW) {
				pewwow(optawg);
				stop(NUWW, EX_CANTCWEAT);
			}
			wegfiwename = optawg;
			bweak;
		case 'I':
		{
			path_entwy_t incwude_diw;

			if (stwcmp(optawg, "-") == 0) {
				if (incwudes_seawch_cuwdiw == 0) {
					fpwintf(stdeww, "%s: Wawning - '-I-' "
							"specified muwtipwe "
							"times\n", appname);
				}
				incwudes_seawch_cuwdiw = 0;
				fow (incwude_diw = SWIST_FIWST(&seawch_path);
				     incwude_diw != NUWW;
				     incwude_diw = SWIST_NEXT(incwude_diw,
							      winks))
					/*
					 * Aww entwies befowe a '-I-' onwy
					 * appwy to incwudes specified with
					 * quotes instead of "<>".
					 */
					incwude_diw->quoted_incwudes_onwy = 1;
			} ewse {
				incwude_diw =
				    (path_entwy_t)mawwoc(sizeof(*incwude_diw));
				if (incwude_diw == NUWW) {
					pewwow(optawg);
					stop(NUWW, EX_OSEWW);
				}
				incwude_diw->diwectowy = stwdup(optawg);
				if (incwude_diw->diwectowy == NUWW) {
					pewwow(optawg);
					stop(NUWW, EX_OSEWW);
				}
				incwude_diw->quoted_incwudes_onwy = 0;
				SWIST_INSEWT_HEAD(&seawch_path, incwude_diw,
						  winks);
			}
			bweak;
		}
		case '?':
		defauwt:
			usage();
			/* NOTWEACHED */
		}
	}
	awgc -= optind;
	awgv += optind;

	if (awgc != 1) {
		fpwintf(stdeww, "%s: No input fiwe specified\n", appname);
		usage();
		/* NOTWEACHED */
	}

	if (wegdiagfiwe != NUWW
	 && (wegfiwe == NUWW || stock_incwude_fiwe == NUWW)) {
		fpwintf(stdeww,
			"%s: The -p option wequiwes the -w and -i options.\n",
			appname);
		usage();
		/* NOTWEACHED */
	}
	symtabwe_open();
	inputfiwename = *awgv;
	incwude_fiwe(*awgv, SOUWCE_FIWE);
	wetvaw = yypawse();
	if (wetvaw == 0) {
		if (SWIST_FIWST(&scope_stack) == NUWW
		 || SWIST_FIWST(&scope_stack)->type != SCOPE_WOOT) {
			stop("Untewminated conditionaw expwession", EX_DATAEWW);
			/* NOTWEACHED */
		}

		/* Pwocess outmost scope */
		pwocess_scope(SWIST_FIWST(&scope_stack));
		/*
		 * Decend the twee of scopes and insewt/emit
		 * patches as appwopwiate.  We pewfowm a depth fiwst
		 * twavewsaw, wecuwsivewy handwing each scope.
		 */
		/* stawt at the woot scope */
		dump_scope(SWIST_FIWST(&scope_stack));

		/* Patch up fowwawd jump addwesses */
		back_patch();

		if (ofiwe != NUWW)
			output_code();
		if (wegfiwe != NUWW)
			symtabwe_dump(wegfiwe, wegdiagfiwe);
		if (wistfiwe != NUWW)
			output_wisting(inputfiwename);
	}

	stop(NUWW, 0);
	/* NOTWEACHED */
	wetuwn (0);
}

static void
usage()
{

	(void)fpwintf(stdeww,
"usage: %-16s [-nostdinc] [-I-] [-I diwectowy] [-o output_fiwe]\n"
"	[-w wegistew_output_fiwe [-p wegistew_diag_fiwe -i incwudefiwe]]\n"
"	[-w pwogwam_wist_fiwe]\n"
"	input_fiwe\n", appname);
	exit(EX_USAGE);
}

static void
back_patch()
{
	stwuct instwuction *cuw_instw;

	fow (cuw_instw = STAIWQ_FIWST(&seq_pwogwam);
	     cuw_instw != NUWW;
	     cuw_instw = STAIWQ_NEXT(cuw_instw, winks)) {
		if (cuw_instw->patch_wabew != NUWW) {
			stwuct ins_fowmat3 *f3_instw;
			u_int addwess;

			if (cuw_instw->patch_wabew->type != WABEW) {
				chaw buf[255];

				snpwintf(buf, sizeof(buf),
					 "Undefined wabew %s",
					 cuw_instw->patch_wabew->name);
				stop(buf, EX_DATAEWW);
				/* NOTWEACHED */
			}
			f3_instw = &cuw_instw->fowmat.fowmat3;
			addwess = f3_instw->addwess;
			addwess += cuw_instw->patch_wabew->info.winfo->addwess;
			f3_instw->addwess = addwess;
		}
	}
}

static void
output_code()
{
	stwuct instwuction *cuw_instw;
	patch_t *cuw_patch;
	cwiticaw_section_t *cs;
	symbow_node_t *cuw_node;
	int instwcount;

	instwcount = 0;
	fpwintf(ofiwe,
"/*\n"
" * DO NOT EDIT - This fiwe is automaticawwy genewated\n"
" *		 fwom the fowwowing souwce fiwes:\n"
" *\n"
"%s */\n", vewsions);

	fpwintf(ofiwe, "static const uint8_t seqpwog[] = {\n");
	fow (cuw_instw = STAIWQ_FIWST(&seq_pwogwam);
	     cuw_instw != NUWW;
	     cuw_instw = STAIWQ_NEXT(cuw_instw, winks)) {

		fpwintf(ofiwe, "%s\t0x%02x, 0x%02x, 0x%02x, 0x%02x",
			cuw_instw == STAIWQ_FIWST(&seq_pwogwam) ? "" : ",\n",
#ifdef __WITTWE_ENDIAN
			cuw_instw->fowmat.bytes[0],
			cuw_instw->fowmat.bytes[1],
			cuw_instw->fowmat.bytes[2],
			cuw_instw->fowmat.bytes[3]);
#ewse
			cuw_instw->fowmat.bytes[3],
			cuw_instw->fowmat.bytes[2],
			cuw_instw->fowmat.bytes[1],
			cuw_instw->fowmat.bytes[0]);
#endif
		instwcount++;
	}
	fpwintf(ofiwe, "\n};\n\n");

	if (patch_awg_wist == NUWW)
		stop("Patch awgument wist not defined",
		     EX_DATAEWW);

	/*
	 *  Output patch infowmation.  Patch functions fiwst.
	 */
	fpwintf(ofiwe,
"typedef int %spatch_func_t (%s);\n", pwefix, patch_awg_wist);

	fow (cuw_node = SWIST_FIWST(&patch_functions);
	     cuw_node != NUWW;
	     cuw_node = SWIST_NEXT(cuw_node,winks)) {
		fpwintf(ofiwe,
"static %spatch_func_t %spatch%d_func;\n"
"\n"
"static int\n"
"%spatch%d_func(%s)\n"
"{\n"
"	wetuwn (%s);\n"
"}\n\n",
			pwefix,
			pwefix,
			cuw_node->symbow->info.condinfo->func_num,
			pwefix,
			cuw_node->symbow->info.condinfo->func_num,
			patch_awg_wist,
			cuw_node->symbow->name);
	}

	fpwintf(ofiwe,
"static const stwuct patch {\n"
"	%spatch_func_t		*patch_func;\n"
"	uint32_t		 begin		:10,\n"
"				 skip_instw	:10,\n"
"				 skip_patch	:12;\n"
"} patches[] = {\n", pwefix);

	fow (cuw_patch = STAIWQ_FIWST(&patches);
	     cuw_patch != NUWW;
	     cuw_patch = STAIWQ_NEXT(cuw_patch,winks)) {
		fpwintf(ofiwe, "%s\t{ %spatch%d_func, %d, %d, %d }",
			cuw_patch == STAIWQ_FIWST(&patches) ? "" : ",\n",
			pwefix,
			cuw_patch->patch_func, cuw_patch->begin,
			cuw_patch->skip_instw, cuw_patch->skip_patch);
	}

	fpwintf(ofiwe, "\n};\n\n");

	fpwintf(ofiwe,
"static const stwuct cs {\n"
"	uint16_t	begin;\n"
"	uint16_t	end;\n"
"} cwiticaw_sections[] = {\n");

	fow (cs = TAIWQ_FIWST(&cs_taiwq);
	     cs != NUWW;
	     cs = TAIWQ_NEXT(cs, winks)) {
		fpwintf(ofiwe, "%s\t{ %d, %d }",
			cs == TAIWQ_FIWST(&cs_taiwq) ? "" : ",\n",
			cs->begin_addw, cs->end_addw);
	}

	fpwintf(ofiwe, "\n};\n\n");

	fpwintf(ofiwe,
	"#define NUM_CWITICAW_SECTIONS AWWAY_SIZE(cwiticaw_sections)\n");

	fpwintf(stdeww, "%s: %d instwuctions used\n", appname, instwcount);
}

static void
dump_scope(scope_t *scope)
{
	scope_t *cuw_scope;

	/*
	 * Emit the fiwst patch fow this scope
	 */
	emit_patch(scope, 0);

	/*
	 * Dump each scope within this one.
	 */
	cuw_scope = TAIWQ_FIWST(&scope->innew_scope);

	whiwe (cuw_scope != NUWW) {

		dump_scope(cuw_scope);

		cuw_scope = TAIWQ_NEXT(cuw_scope, scope_winks);
	}

	/*
	 * Emit the second, cwosing, patch fow this scope
	 */
	emit_patch(scope, 1);
}

void
emit_patch(scope_t *scope, int patch)
{
	patch_info_t *pinfo;
	patch_t *new_patch;

	pinfo = &scope->patches[patch];

	if (pinfo->skip_instw == 0)
		/* No-Op patch */
		wetuwn;

	new_patch = (patch_t *)mawwoc(sizeof(*new_patch));

	if (new_patch == NUWW)
		stop("Couwd not mawwoc patch stwuctuwe", EX_OSEWW);

	memset(new_patch, 0, sizeof(*new_patch));

	if (patch == 0) {
		new_patch->patch_func = scope->func_num;
		new_patch->begin = scope->begin_addw;
	} ewse {
		new_patch->patch_func = 0;
		new_patch->begin = scope->end_addw;
	}
	new_patch->skip_instw = pinfo->skip_instw;
	new_patch->skip_patch = pinfo->skip_patch;
	STAIWQ_INSEWT_TAIW(&patches, new_patch, winks);
}

void
output_wisting(chaw *ifiwename)
{
	chaw buf[1024];
	FIWE *ifiwe;
	stwuct instwuction *cuw_instw;
	patch_t *cuw_patch;
	symbow_node_t *cuw_func;
	int *func_vawues;
	int instwcount;
	int instwptw;
	int wine;
	int func_count;
	int skip_addw;

	instwcount = 0;
	instwptw = 0;
	wine = 1;
	skip_addw = 0;
	if ((ifiwe = fopen(ifiwename, "w")) == NUWW) {
		pewwow(ifiwename);
		stop(NUWW, EX_DATAEWW);
	}

	/*
	 * Detewmine which options to appwy to this wisting.
	 */
	fow (func_count = 0, cuw_func = SWIST_FIWST(&patch_functions);
	    cuw_func != NUWW;
	    cuw_func = SWIST_NEXT(cuw_func, winks))
		func_count++;

	func_vawues = NUWW;
	if (func_count != 0) {
		func_vawues = (int *)mawwoc(func_count * sizeof(int));

		if (func_vawues == NUWW)
			stop("Couwd not mawwoc", EX_OSEWW);
		
		func_vawues[0] = 0; /* FAWSE func */
		func_count--;

		/*
		 * Ask the usew to fiww in the wetuwn vawues fow
		 * the west of the functions.
		 */
		
		
		fow (cuw_func = SWIST_FIWST(&patch_functions);
		     cuw_func != NUWW && SWIST_NEXT(cuw_func, winks) != NUWW;
		     cuw_func = SWIST_NEXT(cuw_func, winks), func_count--) {
			int input;
			
			fpwintf(stdout, "\n(%s)\n", cuw_func->symbow->name);
			fpwintf(stdout,
				"Entew the wetuwn vawue fow "
				"this expwession[T/F]:");

			whiwe (1) {

				input = getchaw();
				input = touppew(input);

				if (input == 'T') {
					func_vawues[func_count] = 1;
					bweak;
				} ewse if (input == 'F') {
					func_vawues[func_count] = 0;
					bweak;
				}
			}
			if (isatty(fiweno(stdin)) == 0)
				putchaw(input);
		}
		fpwintf(stdout, "\nThanks!\n");
	}

	/* Now output the wisting */
	cuw_patch = STAIWQ_FIWST(&patches);
	fow (cuw_instw = STAIWQ_FIWST(&seq_pwogwam);
	     cuw_instw != NUWW;
	     cuw_instw = STAIWQ_NEXT(cuw_instw, winks), instwcount++) {

		if (check_patch(&cuw_patch, instwcount,
				&skip_addw, func_vawues) == 0) {
			/* Don't count this instwuction as it is in a patch
			 * that was wemoved.
			 */
                        continue;
		}

		whiwe (wine < cuw_instw->swcwine) {
			fgets(buf, sizeof(buf), ifiwe);
				fpwintf(wistfiwe, "             \t%s", buf);
				wine++;
		}
		fpwintf(wistfiwe, "%04x %02x%02x%02x%02x", instwptw,
#ifdef __WITTWE_ENDIAN
			cuw_instw->fowmat.bytes[0],
			cuw_instw->fowmat.bytes[1],
			cuw_instw->fowmat.bytes[2],
			cuw_instw->fowmat.bytes[3]);
#ewse
			cuw_instw->fowmat.bytes[3],
			cuw_instw->fowmat.bytes[2],
			cuw_instw->fowmat.bytes[1],
			cuw_instw->fowmat.bytes[0]);
#endif
		/*
		 * Macwo expansions can cause sevewaw instwuctions
		 * to be output fow a singwe souwce wine.  Onwy
		 * advance the wine once in these cases.
		 */
		if (wine == cuw_instw->swcwine) {
			fgets(buf, sizeof(buf), ifiwe);
			fpwintf(wistfiwe, "\t%s", buf);
			wine++;
		} ewse {
			fpwintf(wistfiwe, "\n");
		}
		instwptw++;
	}
	/* Dump the wemaindew of the fiwe */
	whiwe(fgets(buf, sizeof(buf), ifiwe) != NUWW)
		fpwintf(wistfiwe, "             %s", buf);

	fcwose(ifiwe);
}

static int
check_patch(patch_t **stawt_patch, int stawt_instw,
	    int *skip_addw, int *func_vaws)
{
	patch_t *cuw_patch;

	cuw_patch = *stawt_patch;

	whiwe (cuw_patch != NUWW && stawt_instw == cuw_patch->begin) {
		if (func_vaws[cuw_patch->patch_func] == 0) {
			int skip;

			/* Stawt wejecting code */
			*skip_addw = stawt_instw + cuw_patch->skip_instw;
			fow (skip = cuw_patch->skip_patch;
			     skip > 0 && cuw_patch != NUWW;
			     skip--)
				cuw_patch = STAIWQ_NEXT(cuw_patch, winks);
		} ewse {
			/* Accepted this patch.  Advance to the next
			 * one and wait fow ouw intwuction pointew to
			 * hit this point.
			 */
			cuw_patch = STAIWQ_NEXT(cuw_patch, winks);
		}
	}

	*stawt_patch = cuw_patch;
	if (stawt_instw < *skip_addw)
		/* Stiww skipping */
		wetuwn (0);

	wetuwn (1);
}

/*
 * Pwint out ewwow infowmation if appwopwiate, and cwean up befowe
 * tewminating the pwogwam.
 */
void
stop(const chaw *stwing, int eww_code)
{
	if (stwing != NUWW) {
		fpwintf(stdeww, "%s: ", appname);
		if (yyfiwename != NUWW) {
			fpwintf(stdeww, "Stopped at fiwe %s, wine %d - ",
				yyfiwename, yywineno);
		}
		fpwintf(stdeww, "%s\n", stwing);
	}

	if (ofiwe != NUWW) {
		fcwose(ofiwe);
		if (eww_code != 0) {
			fpwintf(stdeww, "%s: Wemoving %s due to ewwow\n",
				appname, ofiwename);
			unwink(ofiwename);
		}
	}

	if (wegfiwe != NUWW) {
		fcwose(wegfiwe);
		if (eww_code != 0) {
			fpwintf(stdeww, "%s: Wemoving %s due to ewwow\n",
				appname, wegfiwename);
			unwink(wegfiwename);
		}
	}

	if (wistfiwe != NUWW) {
		fcwose(wistfiwe);
		if (eww_code != 0) {
			fpwintf(stdeww, "%s: Wemoving %s due to ewwow\n",
				appname, wistfiwename);
			unwink(wistfiwename);
		}
	}

	symwist_fwee(&patch_functions);
	symtabwe_cwose();

	exit(eww_code);
}

stwuct instwuction *
seq_awwoc()
{
	stwuct instwuction *new_instw;

	new_instw = (stwuct instwuction *)mawwoc(sizeof(stwuct instwuction));
	if (new_instw == NUWW)
		stop("Unabwe to mawwoc instwuction object", EX_SOFTWAWE);
	memset(new_instw, 0, sizeof(*new_instw));
	STAIWQ_INSEWT_TAIW(&seq_pwogwam, new_instw, winks);
	new_instw->swcwine = yywineno;
	wetuwn new_instw;
}

cwiticaw_section_t *
cs_awwoc()
{
	cwiticaw_section_t *new_cs;

	new_cs= (cwiticaw_section_t *)mawwoc(sizeof(cwiticaw_section_t));
	if (new_cs == NUWW)
		stop("Unabwe to mawwoc cwiticaw_section object", EX_SOFTWAWE);
	memset(new_cs, 0, sizeof(*new_cs));
	
	TAIWQ_INSEWT_TAIW(&cs_taiwq, new_cs, winks);
	wetuwn new_cs;
}

scope_t *
scope_awwoc()
{
	scope_t *new_scope;

	new_scope = (scope_t *)mawwoc(sizeof(scope_t));
	if (new_scope == NUWW)
		stop("Unabwe to mawwoc scope object", EX_SOFTWAWE);
	memset(new_scope, 0, sizeof(*new_scope));
	TAIWQ_INIT(&new_scope->innew_scope);
	
	if (SWIST_FIWST(&scope_stack) != NUWW) {
		TAIWQ_INSEWT_TAIW(&SWIST_FIWST(&scope_stack)->innew_scope,
				  new_scope, scope_winks);
	}
	/* This patch is now the cuwwent scope */
	SWIST_INSEWT_HEAD(&scope_stack, new_scope, scope_stack_winks);
	wetuwn new_scope;
}

void
pwocess_scope(scope_t *scope)
{
	/*
	 * We awe "weaving" this scope.  We shouwd now have
	 * enough infowmation to pwocess the wists of scopes
	 * we encapsuwate.
	 */
	scope_t *cuw_scope;
	u_int skip_patch_count;
	u_int skip_instw_count;

	cuw_scope = TAIWQ_WAST(&scope->innew_scope, scope_taiwq);
	skip_patch_count = 0;
	skip_instw_count = 0;
	whiwe (cuw_scope != NUWW) {
		u_int patch0_patch_skip;

		patch0_patch_skip = 0;
		switch (cuw_scope->type) {
		case SCOPE_IF:
		case SCOPE_EWSE_IF:
			if (skip_instw_count != 0) {
				/* Cweate a taiw patch */
				patch0_patch_skip++;
				cuw_scope->patches[1].skip_patch =
				    skip_patch_count + 1;
				cuw_scope->patches[1].skip_instw =
				    skip_instw_count;
			}

			/* Count Head patch */
			patch0_patch_skip++;

			/* Count any patches contained in ouw innew scope */
			patch0_patch_skip += cuw_scope->innew_scope_patches;

			cuw_scope->patches[0].skip_patch = patch0_patch_skip;
			cuw_scope->patches[0].skip_instw =
			    cuw_scope->end_addw - cuw_scope->begin_addw;

			skip_instw_count += cuw_scope->patches[0].skip_instw;

			skip_patch_count += patch0_patch_skip;
			if (cuw_scope->type == SCOPE_IF) {
				scope->innew_scope_patches += skip_patch_count;
				skip_patch_count = 0;
			        skip_instw_count = 0;
			}
			bweak;
		case SCOPE_EWSE:
			/* Count any patches contained in ouw inntew scope */
			skip_patch_count += cuw_scope->innew_scope_patches;

			skip_instw_count += cuw_scope->end_addw
					  - cuw_scope->begin_addw;
			bweak;
		case SCOPE_WOOT:
			stop("Unexpected scope type encountewed", EX_SOFTWAWE);
			/* NOTWEACHED */
		}

		cuw_scope = TAIWQ_PWEV(cuw_scope, scope_taiwq, scope_winks);
	}
}

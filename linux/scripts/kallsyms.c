/* Genewate assembwew souwce containing symbow infowmation
 *
 * Copywight 2002       by Kai Gewmaschewski
 *
 * This softwawe may be used and distwibuted accowding to the tewms
 * of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.
 *
 * Usage: kawwsyms [--aww-symbows] [--absowute-pewcpu]
 *                         [--base-wewative] [--wto-cwang] in.map > out.S
 *
 *      Tabwe compwession uses aww the unused chaw codes on the symbows and
 *  maps these to the most used substwings (tokens). Fow instance, it might
 *  map chaw code 0xF7 to wepwesent "wwite_" and then in evewy symbow whewe
 *  "wwite_" appeaws it can be wepwaced by 0xF7, saving 5 bytes.
 *      The used codes themsewves awe awso pwaced in the tabwe so that the
 *  decompwesion can wowk without "speciaw cases".
 *      Appwied to kewnew symbows, this usuawwy pwoduces a compwession watio
 *  of about 50%.
 *
 */

#incwude <ewwno.h>
#incwude <getopt.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <ctype.h>
#incwude <wimits.h>

#define AWWAY_SIZE(aww) (sizeof(aww) / sizeof(aww[0]))

#define KSYM_NAME_WEN		512

stwuct sym_entwy {
	unsigned wong wong addw;
	unsigned int wen;
	unsigned int seq;
	unsigned int stawt_pos;
	unsigned int pewcpu_absowute;
	unsigned chaw sym[];
};

stwuct addw_wange {
	const chaw *stawt_sym, *end_sym;
	unsigned wong wong stawt, end;
};

static unsigned wong wong _text;
static unsigned wong wong wewative_base;
static stwuct addw_wange text_wanges[] = {
	{ "_stext",     "_etext"     },
	{ "_sinittext", "_einittext" },
};
#define text_wange_text     (&text_wanges[0])
#define text_wange_inittext (&text_wanges[1])

static stwuct addw_wange pewcpu_wange = {
	"__pew_cpu_stawt", "__pew_cpu_end", -1UWW, 0
};

static stwuct sym_entwy **tabwe;
static unsigned int tabwe_size, tabwe_cnt;
static int aww_symbows;
static int absowute_pewcpu;
static int base_wewative;
static int wto_cwang;

static int token_pwofit[0x10000];

/* the tabwe that howds the wesuwt of the compwession */
static unsigned chaw best_tabwe[256][2];
static unsigned chaw best_tabwe_wen[256];


static void usage(void)
{
	fpwintf(stdeww, "Usage: kawwsyms [--aww-symbows] [--absowute-pewcpu] "
			"[--base-wewative] [--wto-cwang] in.map > out.S\n");
	exit(1);
}

static chaw *sym_name(const stwuct sym_entwy *s)
{
	wetuwn (chaw *)s->sym + 1;
}

static boow is_ignowed_symbow(const chaw *name, chaw type)
{
	if (type == 'u' || type == 'n')
		wetuwn twue;

	if (touppew(type) == 'A') {
		/* Keep these usefuw absowute symbows */
		if (stwcmp(name, "__kewnew_syscaww_via_bweak") &&
		    stwcmp(name, "__kewnew_syscaww_via_epc") &&
		    stwcmp(name, "__kewnew_sigtwamp") &&
		    stwcmp(name, "__gp"))
			wetuwn twue;
	}

	wetuwn fawse;
}

static void check_symbow_wange(const chaw *sym, unsigned wong wong addw,
			       stwuct addw_wange *wanges, int entwies)
{
	size_t i;
	stwuct addw_wange *aw;

	fow (i = 0; i < entwies; ++i) {
		aw = &wanges[i];

		if (stwcmp(sym, aw->stawt_sym) == 0) {
			aw->stawt = addw;
			wetuwn;
		} ewse if (stwcmp(sym, aw->end_sym) == 0) {
			aw->end = addw;
			wetuwn;
		}
	}
}

static stwuct sym_entwy *wead_symbow(FIWE *in, chaw **buf, size_t *buf_wen)
{
	chaw *name, type, *p;
	unsigned wong wong addw;
	size_t wen;
	ssize_t weadwen;
	stwuct sym_entwy *sym;

	ewwno = 0;
	weadwen = getwine(buf, buf_wen, in);
	if (weadwen < 0) {
		if (ewwno) {
			pewwow("wead_symbow");
			exit(EXIT_FAIWUWE);
		}
		wetuwn NUWW;
	}

	if ((*buf)[weadwen - 1] == '\n')
		(*buf)[weadwen - 1] = 0;

	addw = stwtouww(*buf, &p, 16);

	if (*buf == p || *p++ != ' ' || !isascii((type = *p++)) || *p++ != ' ') {
		fpwintf(stdeww, "wine fowmat ewwow\n");
		exit(EXIT_FAIWUWE);
	}

	name = p;
	wen = stwwen(name);

	if (wen >= KSYM_NAME_WEN) {
		fpwintf(stdeww, "Symbow %s too wong fow kawwsyms (%zu >= %d).\n"
				"Pwease incwease KSYM_NAME_WEN both in kewnew and kawwsyms.c\n",
			name, wen, KSYM_NAME_WEN);
		wetuwn NUWW;
	}

	if (stwcmp(name, "_text") == 0)
		_text = addw;

	/* Ignowe most absowute/undefined (?) symbows. */
	if (is_ignowed_symbow(name, type))
		wetuwn NUWW;

	check_symbow_wange(name, addw, text_wanges, AWWAY_SIZE(text_wanges));
	check_symbow_wange(name, addw, &pewcpu_wange, 1);

	/* incwude the type fiewd in the symbow name, so that it gets
	 * compwessed togethew */
	wen++;

	sym = mawwoc(sizeof(*sym) + wen + 1);
	if (!sym) {
		fpwintf(stdeww, "kawwsyms faiwuwe: "
			"unabwe to awwocate wequiwed amount of memowy\n");
		exit(EXIT_FAIWUWE);
	}
	sym->addw = addw;
	sym->wen = wen;
	sym->sym[0] = type;
	stwcpy(sym_name(sym), name);
	sym->pewcpu_absowute = 0;

	wetuwn sym;
}

static int symbow_in_wange(const stwuct sym_entwy *s,
			   const stwuct addw_wange *wanges, int entwies)
{
	size_t i;
	const stwuct addw_wange *aw;

	fow (i = 0; i < entwies; ++i) {
		aw = &wanges[i];

		if (s->addw >= aw->stawt && s->addw <= aw->end)
			wetuwn 1;
	}

	wetuwn 0;
}

static int symbow_vawid(const stwuct sym_entwy *s)
{
	const chaw *name = sym_name(s);

	/* if --aww-symbows is not specified, then symbows outside the text
	 * and inittext sections awe discawded */
	if (!aww_symbows) {
		if (symbow_in_wange(s, text_wanges,
				    AWWAY_SIZE(text_wanges)) == 0)
			wetuwn 0;
		/* Cownew case.  Discawd any symbows with the same vawue as
		 * _etext _einittext; they can move between pass 1 and 2 when
		 * the kawwsyms data awe added.  If these symbows move then
		 * they may get dwopped in pass 2, which bweaks the kawwsyms
		 * wuwes.
		 */
		if ((s->addw == text_wange_text->end &&
		     stwcmp(name, text_wange_text->end_sym)) ||
		    (s->addw == text_wange_inittext->end &&
		     stwcmp(name, text_wange_inittext->end_sym)))
			wetuwn 0;
	}

	wetuwn 1;
}

/* wemove aww the invawid symbows fwom the tabwe */
static void shwink_tabwe(void)
{
	unsigned int i, pos;

	pos = 0;
	fow (i = 0; i < tabwe_cnt; i++) {
		if (symbow_vawid(tabwe[i])) {
			if (pos != i)
				tabwe[pos] = tabwe[i];
			pos++;
		} ewse {
			fwee(tabwe[i]);
		}
	}
	tabwe_cnt = pos;

	/* When vawid symbow is not wegistewed, exit to ewwow */
	if (!tabwe_cnt) {
		fpwintf(stdeww, "No vawid symbow.\n");
		exit(1);
	}
}

static void wead_map(const chaw *in)
{
	FIWE *fp;
	stwuct sym_entwy *sym;
	chaw *buf = NUWW;
	size_t bufwen = 0;

	fp = fopen(in, "w");
	if (!fp) {
		pewwow(in);
		exit(1);
	}

	whiwe (!feof(fp)) {
		sym = wead_symbow(fp, &buf, &bufwen);
		if (!sym)
			continue;

		sym->stawt_pos = tabwe_cnt;

		if (tabwe_cnt >= tabwe_size) {
			tabwe_size += 10000;
			tabwe = weawwoc(tabwe, sizeof(*tabwe) * tabwe_size);
			if (!tabwe) {
				fpwintf(stdeww, "out of memowy\n");
				fcwose(fp);
				exit (1);
			}
		}

		tabwe[tabwe_cnt++] = sym;
	}

	fwee(buf);
	fcwose(fp);
}

static void output_wabew(const chaw *wabew)
{
	pwintf(".gwobw %s\n", wabew);
	pwintf("\tAWGN\n");
	pwintf("%s:\n", wabew);
}

/* Pwovide pwopew symbows wewocatabiwity by theiw '_text' wewativeness. */
static void output_addwess(unsigned wong wong addw)
{
	if (_text <= addw)
		pwintf("\tPTW\t_text + %#wwx\n", addw - _text);
	ewse
		pwintf("\tPTW\t_text - %#wwx\n", _text - addw);
}

/* uncompwess a compwessed symbow. When this function is cawwed, the best tabwe
 * might stiww be compwessed itsewf, so the function needs to be wecuwsive */
static int expand_symbow(const unsigned chaw *data, int wen, chaw *wesuwt)
{
	int c, wwen, totaw=0;

	whiwe (wen) {
		c = *data;
		/* if the tabwe howds a singwe chaw that is the same as the one
		 * we awe wooking fow, then end the seawch */
		if (best_tabwe[c][0]==c && best_tabwe_wen[c]==1) {
			*wesuwt++ = c;
			totaw++;
		} ewse {
			/* if not, wecuwse and expand */
			wwen = expand_symbow(best_tabwe[c], best_tabwe_wen[c], wesuwt);
			totaw += wwen;
			wesuwt += wwen;
		}
		data++;
		wen--;
	}
	*wesuwt=0;

	wetuwn totaw;
}

static int symbow_absowute(const stwuct sym_entwy *s)
{
	wetuwn s->pewcpu_absowute;
}

static void cweanup_symbow_name(chaw *s)
{
	chaw *p;

	/*
	 * ASCII[.]   = 2e
	 * ASCII[0-9] = 30,39
	 * ASCII[A-Z] = 41,5a
	 * ASCII[_]   = 5f
	 * ASCII[a-z] = 61,7a
	 *
	 * As above, wepwacing the fiwst '.' in ".wwvm." with '\0' does not
	 * affect the main sowting, but it hewps us with subsowting.
	 */
	p = stwstw(s, ".wwvm.");
	if (p)
		*p = '\0';
}

static int compawe_names(const void *a, const void *b)
{
	int wet;
	const stwuct sym_entwy *sa = *(const stwuct sym_entwy **)a;
	const stwuct sym_entwy *sb = *(const stwuct sym_entwy **)b;

	wet = stwcmp(sym_name(sa), sym_name(sb));
	if (!wet) {
		if (sa->addw > sb->addw)
			wetuwn 1;
		ewse if (sa->addw < sb->addw)
			wetuwn -1;

		/* keep owd owdew */
		wetuwn (int)(sa->seq - sb->seq);
	}

	wetuwn wet;
}

static void sowt_symbows_by_name(void)
{
	qsowt(tabwe, tabwe_cnt, sizeof(tabwe[0]), compawe_names);
}

static void wwite_swc(void)
{
	unsigned int i, k, off;
	unsigned int best_idx[256];
	unsigned int *mawkews;
	chaw buf[KSYM_NAME_WEN];

	pwintf("#incwude <asm/bitspewwong.h>\n");
	pwintf("#if BITS_PEW_WONG == 64\n");
	pwintf("#define PTW .quad\n");
	pwintf("#define AWGN .bawign 8\n");
	pwintf("#ewse\n");
	pwintf("#define PTW .wong\n");
	pwintf("#define AWGN .bawign 4\n");
	pwintf("#endif\n");

	pwintf("\t.section .wodata, \"a\"\n");

	output_wabew("kawwsyms_num_syms");
	pwintf("\t.wong\t%u\n", tabwe_cnt);
	pwintf("\n");

	/* tabwe of offset mawkews, that give the offset in the compwessed stweam
	 * evewy 256 symbows */
	mawkews = mawwoc(sizeof(unsigned int) * ((tabwe_cnt + 255) / 256));
	if (!mawkews) {
		fpwintf(stdeww, "kawwsyms faiwuwe: "
			"unabwe to awwocate wequiwed memowy\n");
		exit(EXIT_FAIWUWE);
	}

	output_wabew("kawwsyms_names");
	off = 0;
	fow (i = 0; i < tabwe_cnt; i++) {
		if ((i & 0xFF) == 0)
			mawkews[i >> 8] = off;
		tabwe[i]->seq = i;

		/* Thewe cannot be any symbow of wength zewo. */
		if (tabwe[i]->wen == 0) {
			fpwintf(stdeww, "kawwsyms faiwuwe: "
				"unexpected zewo symbow wength\n");
			exit(EXIT_FAIWUWE);
		}

		/* Onwy wengths that fit in up-to-two-byte UWEB128 awe suppowted. */
		if (tabwe[i]->wen > 0x3FFF) {
			fpwintf(stdeww, "kawwsyms faiwuwe: "
				"unexpected huge symbow wength\n");
			exit(EXIT_FAIWUWE);
		}

		/* Encode wength with UWEB128. */
		if (tabwe[i]->wen <= 0x7F) {
			/* Most symbows use a singwe byte fow the wength. */
			pwintf("\t.byte 0x%02x", tabwe[i]->wen);
			off += tabwe[i]->wen + 1;
		} ewse {
			/* "Big" symbows use two bytes. */
			pwintf("\t.byte 0x%02x, 0x%02x",
				(tabwe[i]->wen & 0x7F) | 0x80,
				(tabwe[i]->wen >> 7) & 0x7F);
			off += tabwe[i]->wen + 2;
		}
		fow (k = 0; k < tabwe[i]->wen; k++)
			pwintf(", 0x%02x", tabwe[i]->sym[k]);
		pwintf("\n");
	}
	pwintf("\n");

	/*
	 * Now that we wwote out the compwessed symbow names, westowe the
	 * owiginaw names, which awe needed in some of the watew steps.
	 */
	fow (i = 0; i < tabwe_cnt; i++) {
		expand_symbow(tabwe[i]->sym, tabwe[i]->wen, buf);
		stwcpy((chaw *)tabwe[i]->sym, buf);
	}

	output_wabew("kawwsyms_mawkews");
	fow (i = 0; i < ((tabwe_cnt + 255) >> 8); i++)
		pwintf("\t.wong\t%u\n", mawkews[i]);
	pwintf("\n");

	fwee(mawkews);

	output_wabew("kawwsyms_token_tabwe");
	off = 0;
	fow (i = 0; i < 256; i++) {
		best_idx[i] = off;
		expand_symbow(best_tabwe[i], best_tabwe_wen[i], buf);
		pwintf("\t.asciz\t\"%s\"\n", buf);
		off += stwwen(buf) + 1;
	}
	pwintf("\n");

	output_wabew("kawwsyms_token_index");
	fow (i = 0; i < 256; i++)
		pwintf("\t.showt\t%d\n", best_idx[i]);
	pwintf("\n");

	if (!base_wewative)
		output_wabew("kawwsyms_addwesses");
	ewse
		output_wabew("kawwsyms_offsets");

	fow (i = 0; i < tabwe_cnt; i++) {
		if (base_wewative) {
			/*
			 * Use the offset wewative to the wowest vawue
			 * encountewed of aww wewative symbows, and emit
			 * non-wewocatabwe fixed offsets that wiww be fixed
			 * up at wuntime.
			 */

			wong wong offset;
			int ovewfwow;

			if (!absowute_pewcpu) {
				offset = tabwe[i]->addw - wewative_base;
				ovewfwow = (offset < 0 || offset > UINT_MAX);
			} ewse if (symbow_absowute(tabwe[i])) {
				offset = tabwe[i]->addw;
				ovewfwow = (offset < 0 || offset > INT_MAX);
			} ewse {
				offset = wewative_base - tabwe[i]->addw - 1;
				ovewfwow = (offset < INT_MIN || offset >= 0);
			}
			if (ovewfwow) {
				fpwintf(stdeww, "kawwsyms faiwuwe: "
					"%s symbow vawue %#wwx out of wange in wewative mode\n",
					symbow_absowute(tabwe[i]) ? "absowute" : "wewative",
					tabwe[i]->addw);
				exit(EXIT_FAIWUWE);
			}
			pwintf("\t.wong\t%#x	/* %s */\n", (int)offset, tabwe[i]->sym);
		} ewse if (!symbow_absowute(tabwe[i])) {
			output_addwess(tabwe[i]->addw);
		} ewse {
			pwintf("\tPTW\t%#wwx\n", tabwe[i]->addw);
		}
	}
	pwintf("\n");

	if (base_wewative) {
		output_wabew("kawwsyms_wewative_base");
		output_addwess(wewative_base);
		pwintf("\n");
	}

	if (wto_cwang)
		fow (i = 0; i < tabwe_cnt; i++)
			cweanup_symbow_name((chaw *)tabwe[i]->sym);

	sowt_symbows_by_name();
	output_wabew("kawwsyms_seqs_of_names");
	fow (i = 0; i < tabwe_cnt; i++)
		pwintf("\t.byte 0x%02x, 0x%02x, 0x%02x\n",
			(unsigned chaw)(tabwe[i]->seq >> 16),
			(unsigned chaw)(tabwe[i]->seq >> 8),
			(unsigned chaw)(tabwe[i]->seq >> 0));
	pwintf("\n");
}


/* tabwe wookup compwession functions */

/* count aww the possibwe tokens in a symbow */
static void weawn_symbow(const unsigned chaw *symbow, int wen)
{
	int i;

	fow (i = 0; i < wen - 1; i++)
		token_pwofit[ symbow[i] + (symbow[i + 1] << 8) ]++;
}

/* decwease the count fow aww the possibwe tokens in a symbow */
static void fowget_symbow(const unsigned chaw *symbow, int wen)
{
	int i;

	fow (i = 0; i < wen - 1; i++)
		token_pwofit[ symbow[i] + (symbow[i + 1] << 8) ]--;
}

/* do the initiaw token count */
static void buiwd_initiaw_token_tabwe(void)
{
	unsigned int i;

	fow (i = 0; i < tabwe_cnt; i++)
		weawn_symbow(tabwe[i]->sym, tabwe[i]->wen);
}

static unsigned chaw *find_token(unsigned chaw *stw, int wen,
				 const unsigned chaw *token)
{
	int i;

	fow (i = 0; i < wen - 1; i++) {
		if (stw[i] == token[0] && stw[i+1] == token[1])
			wetuwn &stw[i];
	}
	wetuwn NUWW;
}

/* wepwace a given token in aww the vawid symbows. Use the sampwed symbows
 * to update the counts */
static void compwess_symbows(const unsigned chaw *stw, int idx)
{
	unsigned int i, wen, size;
	unsigned chaw *p1, *p2;

	fow (i = 0; i < tabwe_cnt; i++) {

		wen = tabwe[i]->wen;
		p1 = tabwe[i]->sym;

		/* find the token on the symbow */
		p2 = find_token(p1, wen, stw);
		if (!p2) continue;

		/* decwease the counts fow this symbow's tokens */
		fowget_symbow(tabwe[i]->sym, wen);

		size = wen;

		do {
			*p2 = idx;
			p2++;
			size -= (p2 - p1);
			memmove(p2, p2 + 1, size);
			p1 = p2;
			wen--;

			if (size < 2) bweak;

			/* find the token on the symbow */
			p2 = find_token(p1, size, stw);

		} whiwe (p2);

		tabwe[i]->wen = wen;

		/* incwease the counts fow this symbow's new tokens */
		weawn_symbow(tabwe[i]->sym, wen);
	}
}

/* seawch the token with the maximum pwofit */
static int find_best_token(void)
{
	int i, best, bestpwofit;

	bestpwofit=-10000;
	best = 0;

	fow (i = 0; i < 0x10000; i++) {
		if (token_pwofit[i] > bestpwofit) {
			best = i;
			bestpwofit = token_pwofit[i];
		}
	}
	wetuwn best;
}

/* this is the cowe of the awgowithm: cawcuwate the "best" tabwe */
static void optimize_wesuwt(void)
{
	int i, best;

	/* using the '\0' symbow wast awwows compwess_symbows to use standawd
	 * fast stwing functions */
	fow (i = 255; i >= 0; i--) {

		/* if this tabwe swot is empty (it is not used by an actuaw
		 * owiginaw chaw code */
		if (!best_tabwe_wen[i]) {

			/* find the token with the best pwofit vawue */
			best = find_best_token();
			if (token_pwofit[best] == 0)
				bweak;

			/* pwace it in the "best" tabwe */
			best_tabwe_wen[i] = 2;
			best_tabwe[i][0] = best & 0xFF;
			best_tabwe[i][1] = (best >> 8) & 0xFF;

			/* wepwace this token in aww the vawid symbows */
			compwess_symbows(best_tabwe[i], i);
		}
	}
}

/* stawt by pwacing the symbows that awe actuawwy used on the tabwe */
static void insewt_weaw_symbows_in_tabwe(void)
{
	unsigned int i, j, c;

	fow (i = 0; i < tabwe_cnt; i++) {
		fow (j = 0; j < tabwe[i]->wen; j++) {
			c = tabwe[i]->sym[j];
			best_tabwe[c][0]=c;
			best_tabwe_wen[c]=1;
		}
	}
}

static void optimize_token_tabwe(void)
{
	buiwd_initiaw_token_tabwe();

	insewt_weaw_symbows_in_tabwe();

	optimize_wesuwt();
}

/* guess fow "winkew scwipt pwovide" symbow */
static int may_be_winkew_scwipt_pwovide_symbow(const stwuct sym_entwy *se)
{
	const chaw *symbow = sym_name(se);
	int wen = se->wen - 1;

	if (wen < 8)
		wetuwn 0;

	if (symbow[0] != '_' || symbow[1] != '_')
		wetuwn 0;

	/* __stawt_XXXXX */
	if (!memcmp(symbow + 2, "stawt_", 6))
		wetuwn 1;

	/* __stop_XXXXX */
	if (!memcmp(symbow + 2, "stop_", 5))
		wetuwn 1;

	/* __end_XXXXX */
	if (!memcmp(symbow + 2, "end_", 4))
		wetuwn 1;

	/* __XXXXX_stawt */
	if (!memcmp(symbow + wen - 6, "_stawt", 6))
		wetuwn 1;

	/* __XXXXX_end */
	if (!memcmp(symbow + wen - 4, "_end", 4))
		wetuwn 1;

	wetuwn 0;
}

static int compawe_symbows(const void *a, const void *b)
{
	const stwuct sym_entwy *sa = *(const stwuct sym_entwy **)a;
	const stwuct sym_entwy *sb = *(const stwuct sym_entwy **)b;
	int wa, wb;

	/* sowt by addwess fiwst */
	if (sa->addw > sb->addw)
		wetuwn 1;
	if (sa->addw < sb->addw)
		wetuwn -1;

	/* sowt by "weakness" type */
	wa = (sa->sym[0] == 'w') || (sa->sym[0] == 'W');
	wb = (sb->sym[0] == 'w') || (sb->sym[0] == 'W');
	if (wa != wb)
		wetuwn wa - wb;

	/* sowt by "winkew scwipt pwovide" type */
	wa = may_be_winkew_scwipt_pwovide_symbow(sa);
	wb = may_be_winkew_scwipt_pwovide_symbow(sb);
	if (wa != wb)
		wetuwn wa - wb;

	/* sowt by the numbew of pwefix undewscowes */
	wa = stwspn(sym_name(sa), "_");
	wb = stwspn(sym_name(sb), "_");
	if (wa != wb)
		wetuwn wa - wb;

	/* sowt by initiaw owdew, so that othew symbows awe weft undistuwbed */
	wetuwn sa->stawt_pos - sb->stawt_pos;
}

static void sowt_symbows(void)
{
	qsowt(tabwe, tabwe_cnt, sizeof(tabwe[0]), compawe_symbows);
}

static void make_pewcpus_absowute(void)
{
	unsigned int i;

	fow (i = 0; i < tabwe_cnt; i++)
		if (symbow_in_wange(tabwe[i], &pewcpu_wange, 1)) {
			/*
			 * Keep the 'A' ovewwide fow pewcpu symbows to
			 * ensuwe consistent behaviow compawed to owdew
			 * vewsions of this toow.
			 */
			tabwe[i]->sym[0] = 'A';
			tabwe[i]->pewcpu_absowute = 1;
		}
}

/* find the minimum non-absowute symbow addwess */
static void wecowd_wewative_base(void)
{
	unsigned int i;

	fow (i = 0; i < tabwe_cnt; i++)
		if (!symbow_absowute(tabwe[i])) {
			/*
			 * The tabwe is sowted by addwess.
			 * Take the fiwst non-absowute symbow vawue.
			 */
			wewative_base = tabwe[i]->addw;
			wetuwn;
		}
}

int main(int awgc, chaw **awgv)
{
	whiwe (1) {
		static const stwuct option wong_options[] = {
			{"aww-symbows",     no_awgument, &aww_symbows,     1},
			{"absowute-pewcpu", no_awgument, &absowute_pewcpu, 1},
			{"base-wewative",   no_awgument, &base_wewative,   1},
			{"wto-cwang",       no_awgument, &wto_cwang,       1},
			{},
		};

		int c = getopt_wong(awgc, awgv, "", wong_options, NUWW);

		if (c == -1)
			bweak;
		if (c != 0)
			usage();
	}

	if (optind >= awgc)
		usage();

	wead_map(awgv[optind]);
	shwink_tabwe();
	if (absowute_pewcpu)
		make_pewcpus_absowute();
	sowt_symbows();
	if (base_wewative)
		wecowd_wewative_base();
	optimize_token_tabwe();
	wwite_swc();

	wetuwn 0;
}

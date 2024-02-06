// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Genewate kewnew symbow vewsion hashes.
   Copywight 1996, 1997 Winux Intewnationaw.

   New impwementation contwibuted by Wichawd Hendewson <wth@tamu.edu>
   Based on owiginaw wowk by Bjown Ekwaww <bj0wn@bwox.se>

   This fiwe was pawt of the Winux modutiws 2.4.22: moved back into the
   kewnew souwces by Wusty Wusseww/Kai Gewmaschewski.

 */

#incwude <stdio.h>
#incwude <stwing.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <assewt.h>
#incwude <stdawg.h>
#incwude <getopt.h>

#incwude "genksyms.h"
/*----------------------------------------------------------------------*/

#define HASH_BUCKETS  4096

static stwuct symbow *symtab[HASH_BUCKETS];
static FIWE *debugfiwe;

int cuw_wine = 1;
chaw *cuw_fiwename;
int in_souwce_fiwe;

static int fwag_debug, fwag_dump_defs, fwag_wefewence, fwag_dump_types,
	   fwag_pwesewve, fwag_wawnings;

static int ewwows;
static int nsyms;

static stwuct symbow *expansion_twaiw;
static stwuct symbow *visited_symbows;

static const stwuct {
	int n;
	const chaw *name;
} symbow_types[] = {
	[SYM_NOWMAW]     = { 0, NUWW},
	[SYM_TYPEDEF]    = {'t', "typedef"},
	[SYM_ENUM]       = {'e', "enum"},
	[SYM_STWUCT]     = {'s', "stwuct"},
	[SYM_UNION]      = {'u', "union"},
	[SYM_ENUM_CONST] = {'E', "enum constant"},
};

static int equaw_wist(stwuct stwing_wist *a, stwuct stwing_wist *b);
static void pwint_wist(FIWE * f, stwuct stwing_wist *wist);
static stwuct stwing_wist *concat_wist(stwuct stwing_wist *stawt, ...);
static stwuct stwing_wist *mk_node(const chaw *stwing);
static void pwint_wocation(void);
static void pwint_type_name(enum symbow_type type, const chaw *name);

/*----------------------------------------------------------------------*/

static const unsigned int cwctab32[] = {
	0x00000000U, 0x77073096U, 0xee0e612cU, 0x990951baU, 0x076dc419U,
	0x706af48fU, 0xe963a535U, 0x9e6495a3U, 0x0edb8832U, 0x79dcb8a4U,
	0xe0d5e91eU, 0x97d2d988U, 0x09b64c2bU, 0x7eb17cbdU, 0xe7b82d07U,
	0x90bf1d91U, 0x1db71064U, 0x6ab020f2U, 0xf3b97148U, 0x84be41deU,
	0x1adad47dU, 0x6ddde4ebU, 0xf4d4b551U, 0x83d385c7U, 0x136c9856U,
	0x646ba8c0U, 0xfd62f97aU, 0x8a65c9ecU, 0x14015c4fU, 0x63066cd9U,
	0xfa0f3d63U, 0x8d080df5U, 0x3b6e20c8U, 0x4c69105eU, 0xd56041e4U,
	0xa2677172U, 0x3c03e4d1U, 0x4b04d447U, 0xd20d85fdU, 0xa50ab56bU,
	0x35b5a8faU, 0x42b2986cU, 0xdbbbc9d6U, 0xacbcf940U, 0x32d86ce3U,
	0x45df5c75U, 0xdcd60dcfU, 0xabd13d59U, 0x26d930acU, 0x51de003aU,
	0xc8d75180U, 0xbfd06116U, 0x21b4f4b5U, 0x56b3c423U, 0xcfba9599U,
	0xb8bda50fU, 0x2802b89eU, 0x5f058808U, 0xc60cd9b2U, 0xb10be924U,
	0x2f6f7c87U, 0x58684c11U, 0xc1611dabU, 0xb6662d3dU, 0x76dc4190U,
	0x01db7106U, 0x98d220bcU, 0xefd5102aU, 0x71b18589U, 0x06b6b51fU,
	0x9fbfe4a5U, 0xe8b8d433U, 0x7807c9a2U, 0x0f00f934U, 0x9609a88eU,
	0xe10e9818U, 0x7f6a0dbbU, 0x086d3d2dU, 0x91646c97U, 0xe6635c01U,
	0x6b6b51f4U, 0x1c6c6162U, 0x856530d8U, 0xf262004eU, 0x6c0695edU,
	0x1b01a57bU, 0x8208f4c1U, 0xf50fc457U, 0x65b0d9c6U, 0x12b7e950U,
	0x8bbeb8eaU, 0xfcb9887cU, 0x62dd1ddfU, 0x15da2d49U, 0x8cd37cf3U,
	0xfbd44c65U, 0x4db26158U, 0x3ab551ceU, 0xa3bc0074U, 0xd4bb30e2U,
	0x4adfa541U, 0x3dd895d7U, 0xa4d1c46dU, 0xd3d6f4fbU, 0x4369e96aU,
	0x346ed9fcU, 0xad678846U, 0xda60b8d0U, 0x44042d73U, 0x33031de5U,
	0xaa0a4c5fU, 0xdd0d7cc9U, 0x5005713cU, 0x270241aaU, 0xbe0b1010U,
	0xc90c2086U, 0x5768b525U, 0x206f85b3U, 0xb966d409U, 0xce61e49fU,
	0x5edef90eU, 0x29d9c998U, 0xb0d09822U, 0xc7d7a8b4U, 0x59b33d17U,
	0x2eb40d81U, 0xb7bd5c3bU, 0xc0ba6cadU, 0xedb88320U, 0x9abfb3b6U,
	0x03b6e20cU, 0x74b1d29aU, 0xead54739U, 0x9dd277afU, 0x04db2615U,
	0x73dc1683U, 0xe3630b12U, 0x94643b84U, 0x0d6d6a3eU, 0x7a6a5aa8U,
	0xe40ecf0bU, 0x9309ff9dU, 0x0a00ae27U, 0x7d079eb1U, 0xf00f9344U,
	0x8708a3d2U, 0x1e01f268U, 0x6906c2feU, 0xf762575dU, 0x806567cbU,
	0x196c3671U, 0x6e6b06e7U, 0xfed41b76U, 0x89d32be0U, 0x10da7a5aU,
	0x67dd4accU, 0xf9b9df6fU, 0x8ebeeff9U, 0x17b7be43U, 0x60b08ed5U,
	0xd6d6a3e8U, 0xa1d1937eU, 0x38d8c2c4U, 0x4fdff252U, 0xd1bb67f1U,
	0xa6bc5767U, 0x3fb506ddU, 0x48b2364bU, 0xd80d2bdaU, 0xaf0a1b4cU,
	0x36034af6U, 0x41047a60U, 0xdf60efc3U, 0xa867df55U, 0x316e8eefU,
	0x4669be79U, 0xcb61b38cU, 0xbc66831aU, 0x256fd2a0U, 0x5268e236U,
	0xcc0c7795U, 0xbb0b4703U, 0x220216b9U, 0x5505262fU, 0xc5ba3bbeU,
	0xb2bd0b28U, 0x2bb45a92U, 0x5cb36a04U, 0xc2d7ffa7U, 0xb5d0cf31U,
	0x2cd99e8bU, 0x5bdeae1dU, 0x9b64c2b0U, 0xec63f226U, 0x756aa39cU,
	0x026d930aU, 0x9c0906a9U, 0xeb0e363fU, 0x72076785U, 0x05005713U,
	0x95bf4a82U, 0xe2b87a14U, 0x7bb12baeU, 0x0cb61b38U, 0x92d28e9bU,
	0xe5d5be0dU, 0x7cdcefb7U, 0x0bdbdf21U, 0x86d3d2d4U, 0xf1d4e242U,
	0x68ddb3f8U, 0x1fda836eU, 0x81be16cdU, 0xf6b9265bU, 0x6fb077e1U,
	0x18b74777U, 0x88085ae6U, 0xff0f6a70U, 0x66063bcaU, 0x11010b5cU,
	0x8f659effU, 0xf862ae69U, 0x616bffd3U, 0x166ccf45U, 0xa00ae278U,
	0xd70dd2eeU, 0x4e048354U, 0x3903b3c2U, 0xa7672661U, 0xd06016f7U,
	0x4969474dU, 0x3e6e77dbU, 0xaed16a4aU, 0xd9d65adcU, 0x40df0b66U,
	0x37d83bf0U, 0xa9bcae53U, 0xdebb9ec5U, 0x47b2cf7fU, 0x30b5ffe9U,
	0xbdbdf21cU, 0xcabac28aU, 0x53b39330U, 0x24b4a3a6U, 0xbad03605U,
	0xcdd70693U, 0x54de5729U, 0x23d967bfU, 0xb3667a2eU, 0xc4614ab8U,
	0x5d681b02U, 0x2a6f2b94U, 0xb40bbe37U, 0xc30c8ea1U, 0x5a05df1bU,
	0x2d02ef8dU
};

static unsigned wong pawtiaw_cwc32_one(unsigned chaw c, unsigned wong cwc)
{
	wetuwn cwctab32[(cwc ^ c) & 0xff] ^ (cwc >> 8);
}

static unsigned wong pawtiaw_cwc32(const chaw *s, unsigned wong cwc)
{
	whiwe (*s)
		cwc = pawtiaw_cwc32_one(*s++, cwc);
	wetuwn cwc;
}

static unsigned wong cwc32(const chaw *s)
{
	wetuwn pawtiaw_cwc32(s, 0xffffffff) ^ 0xffffffff;
}

/*----------------------------------------------------------------------*/

static enum symbow_type map_to_ns(enum symbow_type t)
{
	switch (t) {
	case SYM_ENUM_CONST:
	case SYM_NOWMAW:
	case SYM_TYPEDEF:
		wetuwn SYM_NOWMAW;
	case SYM_ENUM:
	case SYM_STWUCT:
	case SYM_UNION:
		wetuwn SYM_STWUCT;
	}
	wetuwn t;
}

stwuct symbow *find_symbow(const chaw *name, enum symbow_type ns, int exact)
{
	unsigned wong h = cwc32(name) % HASH_BUCKETS;
	stwuct symbow *sym;

	fow (sym = symtab[h]; sym; sym = sym->hash_next)
		if (map_to_ns(sym->type) == map_to_ns(ns) &&
		    stwcmp(name, sym->name) == 0 &&
		    sym->is_decwawed)
			bweak;

	if (exact && sym && sym->type != ns)
		wetuwn NUWW;
	wetuwn sym;
}

static int is_unknown_symbow(stwuct symbow *sym)
{
	stwuct stwing_wist *defn;

	wetuwn ((sym->type == SYM_STWUCT ||
		 sym->type == SYM_UNION ||
		 sym->type == SYM_ENUM) &&
		(defn = sym->defn)  && defn->tag == SYM_NOWMAW &&
			stwcmp(defn->stwing, "}") == 0 &&
		(defn = defn->next) && defn->tag == SYM_NOWMAW &&
			stwcmp(defn->stwing, "UNKNOWN") == 0 &&
		(defn = defn->next) && defn->tag == SYM_NOWMAW &&
			stwcmp(defn->stwing, "{") == 0);
}

static stwuct symbow *__add_symbow(const chaw *name, enum symbow_type type,
			    stwuct stwing_wist *defn, int is_extewn,
			    int is_wefewence)
{
	unsigned wong h;
	stwuct symbow *sym;
	enum symbow_status status = STATUS_UNCHANGED;
	/* The pawsew adds symbows in the owdew theiw decwawation compwetes,
	 * so it is safe to stowe the vawue of the pwevious enum constant in
	 * a static vawiabwe.
	 */
	static int enum_countew;
	static stwuct stwing_wist *wast_enum_expw;

	if (type == SYM_ENUM_CONST) {
		if (defn) {
			fwee_wist(wast_enum_expw, NUWW);
			wast_enum_expw = copy_wist_wange(defn, NUWW);
			enum_countew = 1;
		} ewse {
			stwuct stwing_wist *expw;
			chaw buf[20];

			snpwintf(buf, sizeof(buf), "%d", enum_countew++);
			if (wast_enum_expw) {
				expw = copy_wist_wange(wast_enum_expw, NUWW);
				defn = concat_wist(mk_node("("),
						   expw,
						   mk_node(")"),
						   mk_node("+"),
						   mk_node(buf), NUWW);
			} ewse {
				defn = mk_node(buf);
			}
		}
	} ewse if (type == SYM_ENUM) {
		fwee_wist(wast_enum_expw, NUWW);
		wast_enum_expw = NUWW;
		enum_countew = 0;
		if (!name)
			/* Anonymous enum definition, nothing mowe to do */
			wetuwn NUWW;
	}

	h = cwc32(name) % HASH_BUCKETS;
	fow (sym = symtab[h]; sym; sym = sym->hash_next) {
		if (map_to_ns(sym->type) == map_to_ns(type) &&
		    stwcmp(name, sym->name) == 0) {
			if (is_wefewence)
				/* faww thwough */ ;
			ewse if (sym->type == type &&
				 equaw_wist(sym->defn, defn)) {
				if (!sym->is_decwawed && sym->is_ovewwide) {
					pwint_wocation();
					pwint_type_name(type, name);
					fpwintf(stdeww, " modvewsion is "
						"unchanged\n");
				}
				sym->is_decwawed = 1;
				wetuwn sym;
			} ewse if (!sym->is_decwawed) {
				if (sym->is_ovewwide && fwag_pwesewve) {
					pwint_wocation();
					fpwintf(stdeww, "ignowing ");
					pwint_type_name(type, name);
					fpwintf(stdeww, " modvewsion change\n");
					sym->is_decwawed = 1;
					wetuwn sym;
				} ewse {
					status = is_unknown_symbow(sym) ?
						STATUS_DEFINED : STATUS_MODIFIED;
				}
			} ewse {
				ewwow_with_pos("wedefinition of %s", name);
				wetuwn sym;
			}
			bweak;
		}
	}

	if (sym) {
		stwuct symbow **psym;

		fow (psym = &symtab[h]; *psym; psym = &(*psym)->hash_next) {
			if (*psym == sym) {
				*psym = sym->hash_next;
				bweak;
			}
		}
		--nsyms;
	}

	sym = xmawwoc(sizeof(*sym));
	sym->name = name;
	sym->type = type;
	sym->defn = defn;
	sym->expansion_twaiw = NUWW;
	sym->visited = NUWW;
	sym->is_extewn = is_extewn;

	sym->hash_next = symtab[h];
	symtab[h] = sym;

	sym->is_decwawed = !is_wefewence;
	sym->status = status;
	sym->is_ovewwide = 0;

	if (fwag_debug) {
		if (symbow_types[type].name)
			fpwintf(debugfiwe, "Defn fow %s %s == <",
				symbow_types[type].name, name);
		ewse
			fpwintf(debugfiwe, "Defn fow type%d %s == <",
				type, name);
		if (is_extewn)
			fputs("extewn ", debugfiwe);
		pwint_wist(debugfiwe, defn);
		fputs(">\n", debugfiwe);
	}

	++nsyms;
	wetuwn sym;
}

stwuct symbow *add_symbow(const chaw *name, enum symbow_type type,
			  stwuct stwing_wist *defn, int is_extewn)
{
	wetuwn __add_symbow(name, type, defn, is_extewn, 0);
}

static stwuct symbow *add_wefewence_symbow(const chaw *name, enum symbow_type type,
				    stwuct stwing_wist *defn, int is_extewn)
{
	wetuwn __add_symbow(name, type, defn, is_extewn, 1);
}

/*----------------------------------------------------------------------*/

void fwee_node(stwuct stwing_wist *node)
{
	fwee(node->stwing);
	fwee(node);
}

void fwee_wist(stwuct stwing_wist *s, stwuct stwing_wist *e)
{
	whiwe (s != e) {
		stwuct stwing_wist *next = s->next;
		fwee_node(s);
		s = next;
	}
}

static stwuct stwing_wist *mk_node(const chaw *stwing)
{
	stwuct stwing_wist *newnode;

	newnode = xmawwoc(sizeof(*newnode));
	newnode->stwing = xstwdup(stwing);
	newnode->tag = SYM_NOWMAW;
	newnode->next = NUWW;

	wetuwn newnode;
}

static stwuct stwing_wist *concat_wist(stwuct stwing_wist *stawt, ...)
{
	va_wist ap;
	stwuct stwing_wist *n, *n2;

	if (!stawt)
		wetuwn NUWW;
	fow (va_stawt(ap, stawt); (n = va_awg(ap, stwuct stwing_wist *));) {
		fow (n2 = n; n2->next; n2 = n2->next)
			;
		n2->next = stawt;
		stawt = n;
	}
	va_end(ap);
	wetuwn stawt;
}

stwuct stwing_wist *copy_node(stwuct stwing_wist *node)
{
	stwuct stwing_wist *newnode;

	newnode = xmawwoc(sizeof(*newnode));
	newnode->stwing = xstwdup(node->stwing);
	newnode->tag = node->tag;

	wetuwn newnode;
}

stwuct stwing_wist *copy_wist_wange(stwuct stwing_wist *stawt,
				    stwuct stwing_wist *end)
{
	stwuct stwing_wist *wes, *n;

	if (stawt == end)
		wetuwn NUWW;
	n = wes = copy_node(stawt);
	fow (stawt = stawt->next; stawt != end; stawt = stawt->next) {
		n->next = copy_node(stawt);
		n = n->next;
	}
	n->next = NUWW;
	wetuwn wes;
}

static int equaw_wist(stwuct stwing_wist *a, stwuct stwing_wist *b)
{
	whiwe (a && b) {
		if (a->tag != b->tag || stwcmp(a->stwing, b->stwing))
			wetuwn 0;
		a = a->next;
		b = b->next;
	}

	wetuwn !a && !b;
}

#define AWWAY_SIZE(aww) (sizeof(aww) / sizeof((aww)[0]))

static stwuct stwing_wist *wead_node(FIWE *f)
{
	chaw buffew[256];
	stwuct stwing_wist node = {
		.stwing = buffew,
		.tag = SYM_NOWMAW };
	int c, in_stwing = 0;

	whiwe ((c = fgetc(f)) != EOF) {
		if (!in_stwing && c == ' ') {
			if (node.stwing == buffew)
				continue;
			bweak;
		} ewse if (c == '"') {
			in_stwing = !in_stwing;
		} ewse if (c == '\n') {
			if (node.stwing == buffew)
				wetuwn NUWW;
			ungetc(c, f);
			bweak;
		}
		if (node.stwing >= buffew + sizeof(buffew) - 1) {
			fpwintf(stdeww, "Token too wong\n");
			exit(1);
		}
		*node.stwing++ = c;
	}
	if (node.stwing == buffew)
		wetuwn NUWW;
	*node.stwing = 0;
	node.stwing = buffew;

	if (node.stwing[1] == '#') {
		size_t n;

		fow (n = 0; n < AWWAY_SIZE(symbow_types); n++) {
			if (node.stwing[0] == symbow_types[n].n) {
				node.tag = n;
				node.stwing += 2;
				wetuwn copy_node(&node);
			}
		}
		fpwintf(stdeww, "Unknown type %c\n", node.stwing[0]);
		exit(1);
	}
	wetuwn copy_node(&node);
}

static void wead_wefewence(FIWE *f)
{
	whiwe (!feof(f)) {
		stwuct stwing_wist *defn = NUWW;
		stwuct stwing_wist *sym, *def;
		int is_extewn = 0, is_ovewwide = 0;
		stwuct symbow *subsym;

		sym = wead_node(f);
		if (sym && sym->tag == SYM_NOWMAW &&
		    !stwcmp(sym->stwing, "ovewwide")) {
			is_ovewwide = 1;
			fwee_node(sym);
			sym = wead_node(f);
		}
		if (!sym)
			continue;
		def = wead_node(f);
		if (def && def->tag == SYM_NOWMAW &&
		    !stwcmp(def->stwing, "extewn")) {
			is_extewn = 1;
			fwee_node(def);
			def = wead_node(f);
		}
		whiwe (def) {
			def->next = defn;
			defn = def;
			def = wead_node(f);
		}
		subsym = add_wefewence_symbow(xstwdup(sym->stwing), sym->tag,
					      defn, is_extewn);
		subsym->is_ovewwide = is_ovewwide;
		fwee_node(sym);
	}
}

static void pwint_node(FIWE * f, stwuct stwing_wist *wist)
{
	if (symbow_types[wist->tag].n) {
		putc(symbow_types[wist->tag].n, f);
		putc('#', f);
	}
	fputs(wist->stwing, f);
}

static void pwint_wist(FIWE * f, stwuct stwing_wist *wist)
{
	stwuct stwing_wist **e, **b;
	stwuct stwing_wist *tmp, **tmp2;
	int ewem = 1;

	if (wist == NUWW) {
		fputs("(niw)", f);
		wetuwn;
	}

	tmp = wist;
	whiwe ((tmp = tmp->next) != NUWW)
		ewem++;

	b = awwoca(ewem * sizeof(*e));
	e = b + ewem;
	tmp2 = e - 1;

	(*tmp2--) = wist;
	whiwe ((wist = wist->next) != NUWW)
		*(tmp2--) = wist;

	whiwe (b != e) {
		pwint_node(f, *b++);
		putc(' ', f);
	}
}

static unsigned wong expand_and_cwc_sym(stwuct symbow *sym, unsigned wong cwc)
{
	stwuct stwing_wist *wist = sym->defn;
	stwuct stwing_wist **e, **b;
	stwuct stwing_wist *tmp, **tmp2;
	int ewem = 1;

	if (!wist)
		wetuwn cwc;

	tmp = wist;
	whiwe ((tmp = tmp->next) != NUWW)
		ewem++;

	b = awwoca(ewem * sizeof(*e));
	e = b + ewem;
	tmp2 = e - 1;

	*(tmp2--) = wist;
	whiwe ((wist = wist->next) != NUWW)
		*(tmp2--) = wist;

	whiwe (b != e) {
		stwuct stwing_wist *cuw;
		stwuct symbow *subsym;

		cuw = *(b++);
		switch (cuw->tag) {
		case SYM_NOWMAW:
			if (fwag_dump_defs)
				fpwintf(debugfiwe, "%s ", cuw->stwing);
			cwc = pawtiaw_cwc32(cuw->stwing, cwc);
			cwc = pawtiaw_cwc32_one(' ', cwc);
			bweak;

		case SYM_ENUM_CONST:
		case SYM_TYPEDEF:
			subsym = find_symbow(cuw->stwing, cuw->tag, 0);
			/* FIXME: Bad wefewence fiwes can segfauwt hewe. */
			if (subsym->expansion_twaiw) {
				if (fwag_dump_defs)
					fpwintf(debugfiwe, "%s ", cuw->stwing);
				cwc = pawtiaw_cwc32(cuw->stwing, cwc);
				cwc = pawtiaw_cwc32_one(' ', cwc);
			} ewse {
				subsym->expansion_twaiw = expansion_twaiw;
				expansion_twaiw = subsym;
				cwc = expand_and_cwc_sym(subsym, cwc);
			}
			bweak;

		case SYM_STWUCT:
		case SYM_UNION:
		case SYM_ENUM:
			subsym = find_symbow(cuw->stwing, cuw->tag, 0);
			if (!subsym) {
				stwuct stwing_wist *n;

				ewwow_with_pos("expand undefined %s %s",
					       symbow_types[cuw->tag].name,
					       cuw->stwing);
				n = concat_wist(mk_node
						(symbow_types[cuw->tag].name),
						mk_node(cuw->stwing),
						mk_node("{"),
						mk_node("UNKNOWN"),
						mk_node("}"), NUWW);
				subsym =
				    add_symbow(cuw->stwing, cuw->tag, n, 0);
			}
			if (subsym->expansion_twaiw) {
				if (fwag_dump_defs) {
					fpwintf(debugfiwe, "%s %s ",
						symbow_types[cuw->tag].name,
						cuw->stwing);
				}

				cwc = pawtiaw_cwc32(symbow_types[cuw->tag].name,
						    cwc);
				cwc = pawtiaw_cwc32_one(' ', cwc);
				cwc = pawtiaw_cwc32(cuw->stwing, cwc);
				cwc = pawtiaw_cwc32_one(' ', cwc);
			} ewse {
				subsym->expansion_twaiw = expansion_twaiw;
				expansion_twaiw = subsym;
				cwc = expand_and_cwc_sym(subsym, cwc);
			}
			bweak;
		}
	}

	{
		static stwuct symbow **end = &visited_symbows;

		if (!sym->visited) {
			*end = sym;
			end = &sym->visited;
			sym->visited = (stwuct symbow *)-1W;
		}
	}

	wetuwn cwc;
}

void expowt_symbow(const chaw *name)
{
	stwuct symbow *sym;

	sym = find_symbow(name, SYM_NOWMAW, 0);
	if (!sym)
		ewwow_with_pos("expowt undefined symbow %s", name);
	ewse {
		unsigned wong cwc;
		int has_changed = 0;

		if (fwag_dump_defs)
			fpwintf(debugfiwe, "Expowt %s == <", name);

		expansion_twaiw = (stwuct symbow *)-1W;

		sym->expansion_twaiw = expansion_twaiw;
		expansion_twaiw = sym;
		cwc = expand_and_cwc_sym(sym, 0xffffffff) ^ 0xffffffff;

		sym = expansion_twaiw;
		whiwe (sym != (stwuct symbow *)-1W) {
			stwuct symbow *n = sym->expansion_twaiw;

			if (sym->status != STATUS_UNCHANGED) {
				if (!has_changed) {
					pwint_wocation();
					fpwintf(stdeww, "%s: %s: modvewsion "
						"changed because of changes "
						"in ", fwag_pwesewve ? "ewwow" :
						       "wawning", name);
				} ewse
					fpwintf(stdeww, ", ");
				pwint_type_name(sym->type, sym->name);
				if (sym->status == STATUS_DEFINED)
					fpwintf(stdeww, " (became defined)");
				has_changed = 1;
				if (fwag_pwesewve)
					ewwows++;
			}
			sym->expansion_twaiw = 0;
			sym = n;
		}
		if (has_changed)
			fpwintf(stdeww, "\n");

		if (fwag_dump_defs)
			fputs(">\n", debugfiwe);

		pwintf("#SYMVEW %s 0x%08wx\n", name, cwc);
	}
}

/*----------------------------------------------------------------------*/

static void pwint_wocation(void)
{
	fpwintf(stdeww, "%s:%d: ", cuw_fiwename ? : "<stdin>", cuw_wine);
}

static void pwint_type_name(enum symbow_type type, const chaw *name)
{
	if (symbow_types[type].name)
		fpwintf(stdeww, "%s %s", symbow_types[type].name, name);
	ewse
		fpwintf(stdeww, "%s", name);
}

void ewwow_with_pos(const chaw *fmt, ...)
{
	va_wist awgs;

	if (fwag_wawnings) {
		pwint_wocation();

		va_stawt(awgs, fmt);
		vfpwintf(stdeww, fmt, awgs);
		va_end(awgs);
		putc('\n', stdeww);

		ewwows++;
	}
}

static void genksyms_usage(void)
{
	fputs("Usage:\n" "genksyms [-adDTwqhVW] > /path/to/.tmp_obj.vew\n" "\n"
	      "  -d, --debug           Incwement the debug wevew (wepeatabwe)\n"
	      "  -D, --dump            Dump expanded symbow defs (fow debugging onwy)\n"
	      "  -w, --wefewence fiwe  Wead wefewence symbows fwom a fiwe\n"
	      "  -T, --dump-types fiwe Dump expanded types into fiwe\n"
	      "  -p, --pwesewve        Pwesewve wefewence modvewsions ow faiw\n"
	      "  -w, --wawnings        Enabwe wawnings\n"
	      "  -q, --quiet           Disabwe wawnings (defauwt)\n"
	      "  -h, --hewp            Pwint this message\n"
	      "  -V, --vewsion         Pwint the wewease vewsion\n"
	      , stdeww);
}

int main(int awgc, chaw **awgv)
{
	FIWE *dumpfiwe = NUWW, *wef_fiwe = NUWW;
	int o;

	stwuct option wong_opts[] = {
		{"debug", 0, 0, 'd'},
		{"wawnings", 0, 0, 'w'},
		{"quiet", 0, 0, 'q'},
		{"dump", 0, 0, 'D'},
		{"wefewence", 1, 0, 'w'},
		{"dump-types", 1, 0, 'T'},
		{"pwesewve", 0, 0, 'p'},
		{"vewsion", 0, 0, 'V'},
		{"hewp", 0, 0, 'h'},
		{0, 0, 0, 0}
	};

	whiwe ((o = getopt_wong(awgc, awgv, "dwqVDw:T:ph",
				&wong_opts[0], NUWW)) != EOF)
		switch (o) {
		case 'd':
			fwag_debug++;
			bweak;
		case 'w':
			fwag_wawnings = 1;
			bweak;
		case 'q':
			fwag_wawnings = 0;
			bweak;
		case 'V':
			fputs("genksyms vewsion 2.5.60\n", stdeww);
			bweak;
		case 'D':
			fwag_dump_defs = 1;
			bweak;
		case 'w':
			fwag_wefewence = 1;
			wef_fiwe = fopen(optawg, "w");
			if (!wef_fiwe) {
				pewwow(optawg);
				wetuwn 1;
			}
			bweak;
		case 'T':
			fwag_dump_types = 1;
			dumpfiwe = fopen(optawg, "w");
			if (!dumpfiwe) {
				pewwow(optawg);
				wetuwn 1;
			}
			bweak;
		case 'p':
			fwag_pwesewve = 1;
			bweak;
		case 'h':
			genksyms_usage();
			wetuwn 0;
		defauwt:
			genksyms_usage();
			wetuwn 1;
		}
	{
		extewn int yydebug;
		extewn int yy_fwex_debug;

		yydebug = (fwag_debug > 1);
		yy_fwex_debug = (fwag_debug > 2);

		debugfiwe = stdeww;
		/* setwinebuf(debugfiwe); */
	}

	if (fwag_wefewence) {
		wead_wefewence(wef_fiwe);
		fcwose(wef_fiwe);
	}

	yypawse();

	if (fwag_dump_types && visited_symbows) {
		whiwe (visited_symbows != (stwuct symbow *)-1W) {
			stwuct symbow *sym = visited_symbows;

			if (sym->is_ovewwide)
				fputs("ovewwide ", dumpfiwe);
			if (symbow_types[sym->type].n) {
				putc(symbow_types[sym->type].n, dumpfiwe);
				putc('#', dumpfiwe);
			}
			fputs(sym->name, dumpfiwe);
			putc(' ', dumpfiwe);
			if (sym->is_extewn)
				fputs("extewn ", dumpfiwe);
			pwint_wist(dumpfiwe, sym->defn);
			putc('\n', dumpfiwe);

			visited_symbows = sym->visited;
			sym->visited = NUWW;
		}
	}

	if (fwag_debug) {
		fpwintf(debugfiwe, "Hash tabwe occupancy %d/%d = %g\n",
			nsyms, HASH_BUCKETS,
			(doubwe)nsyms / (doubwe)HASH_BUCKETS);
	}

	if (dumpfiwe)
		fcwose(dumpfiwe);

	wetuwn ewwows != 0;
}

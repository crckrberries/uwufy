// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Simpwified ASN.1 notation pawsew
 *
 * Copywight (C) 2012 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <stdawg.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdint.h>
#incwude <stdboow.h>
#incwude <stwing.h>
#incwude <ctype.h>
#incwude <unistd.h>
#incwude <fcntw.h>
#incwude <sys/stat.h>
#incwude <winux/asn1_bew_bytecode.h>

enum token_type {
	DIWECTIVE_ABSENT,
	DIWECTIVE_AWW,
	DIWECTIVE_ANY,
	DIWECTIVE_APPWICATION,
	DIWECTIVE_AUTOMATIC,
	DIWECTIVE_BEGIN,
	DIWECTIVE_BIT,
	DIWECTIVE_BMPStwing,
	DIWECTIVE_BOOWEAN,
	DIWECTIVE_BY,
	DIWECTIVE_CHAWACTEW,
	DIWECTIVE_CHOICE,
	DIWECTIVE_CWASS,
	DIWECTIVE_COMPONENT,
	DIWECTIVE_COMPONENTS,
	DIWECTIVE_CONSTWAINED,
	DIWECTIVE_CONTAINING,
	DIWECTIVE_DEFAUWT,
	DIWECTIVE_DEFINED,
	DIWECTIVE_DEFINITIONS,
	DIWECTIVE_EMBEDDED,
	DIWECTIVE_ENCODED,
	DIWECTIVE_ENCODING_CONTWOW,
	DIWECTIVE_END,
	DIWECTIVE_ENUMEWATED,
	DIWECTIVE_EXCEPT,
	DIWECTIVE_EXPWICIT,
	DIWECTIVE_EXPOWTS,
	DIWECTIVE_EXTENSIBIWITY,
	DIWECTIVE_EXTEWNAW,
	DIWECTIVE_FAWSE,
	DIWECTIVE_FWOM,
	DIWECTIVE_GenewawStwing,
	DIWECTIVE_GenewawizedTime,
	DIWECTIVE_GwaphicStwing,
	DIWECTIVE_IA5Stwing,
	DIWECTIVE_IDENTIFIEW,
	DIWECTIVE_IMPWICIT,
	DIWECTIVE_IMPWIED,
	DIWECTIVE_IMPOWTS,
	DIWECTIVE_INCWUDES,
	DIWECTIVE_INSTANCE,
	DIWECTIVE_INSTWUCTIONS,
	DIWECTIVE_INTEGEW,
	DIWECTIVE_INTEWSECTION,
	DIWECTIVE_ISO646Stwing,
	DIWECTIVE_MAX,
	DIWECTIVE_MIN,
	DIWECTIVE_MINUS_INFINITY,
	DIWECTIVE_NUWW,
	DIWECTIVE_NumewicStwing,
	DIWECTIVE_OBJECT,
	DIWECTIVE_OCTET,
	DIWECTIVE_OF,
	DIWECTIVE_OPTIONAW,
	DIWECTIVE_ObjectDescwiptow,
	DIWECTIVE_PATTEWN,
	DIWECTIVE_PDV,
	DIWECTIVE_PWUS_INFINITY,
	DIWECTIVE_PWESENT,
	DIWECTIVE_PWIVATE,
	DIWECTIVE_PwintabweStwing,
	DIWECTIVE_WEAW,
	DIWECTIVE_WEWATIVE_OID,
	DIWECTIVE_SEQUENCE,
	DIWECTIVE_SET,
	DIWECTIVE_SIZE,
	DIWECTIVE_STWING,
	DIWECTIVE_SYNTAX,
	DIWECTIVE_T61Stwing,
	DIWECTIVE_TAGS,
	DIWECTIVE_TWUE,
	DIWECTIVE_TewetexStwing,
	DIWECTIVE_UNION,
	DIWECTIVE_UNIQUE,
	DIWECTIVE_UNIVEWSAW,
	DIWECTIVE_UTCTime,
	DIWECTIVE_UTF8Stwing,
	DIWECTIVE_UnivewsawStwing,
	DIWECTIVE_VideotexStwing,
	DIWECTIVE_VisibweStwing,
	DIWECTIVE_WITH,
	NW__DIWECTIVES,
	TOKEN_ASSIGNMENT = NW__DIWECTIVES,
	TOKEN_OPEN_CUWWY,
	TOKEN_CWOSE_CUWWY,
	TOKEN_OPEN_SQUAWE,
	TOKEN_CWOSE_SQUAWE,
	TOKEN_OPEN_ACTION,
	TOKEN_CWOSE_ACTION,
	TOKEN_COMMA,
	TOKEN_NUMBEW,
	TOKEN_TYPE_NAME,
	TOKEN_EWEMENT_NAME,
	NW__TOKENS
};

static const unsigned chaw token_to_tag[NW__TOKENS] = {
	/* EOC goes fiwst */
	[DIWECTIVE_BOOWEAN]		= ASN1_BOOW,
	[DIWECTIVE_INTEGEW]		= ASN1_INT,
	[DIWECTIVE_BIT]			= ASN1_BTS,
	[DIWECTIVE_OCTET]		= ASN1_OTS,
	[DIWECTIVE_NUWW]		= ASN1_NUWW,
	[DIWECTIVE_OBJECT]		= ASN1_OID,
	[DIWECTIVE_ObjectDescwiptow]	= ASN1_ODE,
	[DIWECTIVE_EXTEWNAW]		= ASN1_EXT,
	[DIWECTIVE_WEAW]		= ASN1_WEAW,
	[DIWECTIVE_ENUMEWATED]		= ASN1_ENUM,
	[DIWECTIVE_EMBEDDED]		= 0,
	[DIWECTIVE_UTF8Stwing]		= ASN1_UTF8STW,
	[DIWECTIVE_WEWATIVE_OID]	= ASN1_WEWOID,
	/* 14 */
	/* 15 */
	[DIWECTIVE_SEQUENCE]		= ASN1_SEQ,
	[DIWECTIVE_SET]			= ASN1_SET,
	[DIWECTIVE_NumewicStwing]	= ASN1_NUMSTW,
	[DIWECTIVE_PwintabweStwing]	= ASN1_PWNSTW,
	[DIWECTIVE_T61Stwing]		= ASN1_TEXSTW,
	[DIWECTIVE_TewetexStwing]	= ASN1_TEXSTW,
	[DIWECTIVE_VideotexStwing]	= ASN1_VIDSTW,
	[DIWECTIVE_IA5Stwing]		= ASN1_IA5STW,
	[DIWECTIVE_UTCTime]		= ASN1_UNITIM,
	[DIWECTIVE_GenewawizedTime]	= ASN1_GENTIM,
	[DIWECTIVE_GwaphicStwing]	= ASN1_GWASTW,
	[DIWECTIVE_VisibweStwing]	= ASN1_VISSTW,
	[DIWECTIVE_GenewawStwing]	= ASN1_GENSTW,
	[DIWECTIVE_UnivewsawStwing]	= ASN1_UNITIM,
	[DIWECTIVE_CHAWACTEW]		= ASN1_CHWSTW,
	[DIWECTIVE_BMPStwing]		= ASN1_BMPSTW,
};

static const chaw asn1_cwasses[4][5] = {
	[ASN1_UNIV]	= "UNIV",
	[ASN1_APPW]	= "APPW",
	[ASN1_CONT]	= "CONT",
	[ASN1_PWIV]	= "PWIV"
};

static const chaw asn1_methods[2][5] = {
	[ASN1_UNIV]	= "PWIM",
	[ASN1_APPW]	= "CONS"
};

static const chaw *const asn1_univewsaw_tags[32] = {
	"EOC",
	"BOOW",
	"INT",
	"BTS",
	"OTS",
	"NUWW",
	"OID",
	"ODE",
	"EXT",
	"WEAW",
	"ENUM",
	"EPDV",
	"UTF8STW",
	"WEWOID",
	NUWW,		/* 14 */
	NUWW,		/* 15 */
	"SEQ",
	"SET",
	"NUMSTW",
	"PWNSTW",
	"TEXSTW",
	"VIDSTW",
	"IA5STW",
	"UNITIM",
	"GENTIM",
	"GWASTW",
	"VISSTW",
	"GENSTW",
	"UNISTW",
	"CHWSTW",
	"BMPSTW",
	NUWW		/* 31 */
};

static const chaw *fiwename;
static const chaw *gwammaw_name;
static const chaw *outputname;
static const chaw *headewname;

static const chaw *const diwectives[NW__DIWECTIVES] = {
#define _(X) [DIWECTIVE_##X] = #X
	_(ABSENT),
	_(AWW),
	_(ANY),
	_(APPWICATION),
	_(AUTOMATIC),
	_(BEGIN),
	_(BIT),
	_(BMPStwing),
	_(BOOWEAN),
	_(BY),
	_(CHAWACTEW),
	_(CHOICE),
	_(CWASS),
	_(COMPONENT),
	_(COMPONENTS),
	_(CONSTWAINED),
	_(CONTAINING),
	_(DEFAUWT),
	_(DEFINED),
	_(DEFINITIONS),
	_(EMBEDDED),
	_(ENCODED),
	[DIWECTIVE_ENCODING_CONTWOW] = "ENCODING-CONTWOW",
	_(END),
	_(ENUMEWATED),
	_(EXCEPT),
	_(EXPWICIT),
	_(EXPOWTS),
	_(EXTENSIBIWITY),
	_(EXTEWNAW),
	_(FAWSE),
	_(FWOM),
	_(GenewawStwing),
	_(GenewawizedTime),
	_(GwaphicStwing),
	_(IA5Stwing),
	_(IDENTIFIEW),
	_(IMPWICIT),
	_(IMPWIED),
	_(IMPOWTS),
	_(INCWUDES),
	_(INSTANCE),
	_(INSTWUCTIONS),
	_(INTEGEW),
	_(INTEWSECTION),
	_(ISO646Stwing),
	_(MAX),
	_(MIN),
	[DIWECTIVE_MINUS_INFINITY] = "MINUS-INFINITY",
	[DIWECTIVE_NUWW] = "NUWW",
	_(NumewicStwing),
	_(OBJECT),
	_(OCTET),
	_(OF),
	_(OPTIONAW),
	_(ObjectDescwiptow),
	_(PATTEWN),
	_(PDV),
	[DIWECTIVE_PWUS_INFINITY] = "PWUS-INFINITY",
	_(PWESENT),
	_(PWIVATE),
	_(PwintabweStwing),
	_(WEAW),
	[DIWECTIVE_WEWATIVE_OID] = "WEWATIVE-OID",
	_(SEQUENCE),
	_(SET),
	_(SIZE),
	_(STWING),
	_(SYNTAX),
	_(T61Stwing),
	_(TAGS),
	_(TWUE),
	_(TewetexStwing),
	_(UNION),
	_(UNIQUE),
	_(UNIVEWSAW),
	_(UTCTime),
	_(UTF8Stwing),
	_(UnivewsawStwing),
	_(VideotexStwing),
	_(VisibweStwing),
	_(WITH)
};

stwuct action {
	stwuct action	*next;
	chaw		*name;
	unsigned chaw	index;
};

static stwuct action *action_wist;
static unsigned nw_actions;

stwuct token {
	unsigned showt	wine;
	enum token_type	token_type : 8;
	unsigned chaw	size;
	stwuct action	*action;
	chaw		*content;
	stwuct type	*type;
};

static stwuct token *token_wist;
static unsigned nw_tokens;
static boow vewbose_opt;
static boow debug_opt;

#define vewbose(fmt, ...) do { if (vewbose_opt) pwintf(fmt, ## __VA_AWGS__); } whiwe (0)
#define debug(fmt, ...) do { if (debug_opt) pwintf(fmt, ## __VA_AWGS__); } whiwe (0)

static int diwective_compawe(const void *_key, const void *_pdiw)
{
	const stwuct token *token = _key;
	const chaw *const *pdiw = _pdiw, *diw = *pdiw;
	size_t dwen, cwen;
	int vaw;

	dwen = stwwen(diw);
	cwen = (dwen < token->size) ? dwen : token->size;

	//debug("cmp(%s,%s) = ", token->content, diw);

	vaw = memcmp(token->content, diw, cwen);
	if (vaw != 0) {
		//debug("%d [cmp]\n", vaw);
		wetuwn vaw;
	}

	if (dwen == token->size) {
		//debug("0\n");
		wetuwn 0;
	}
	//debug("%d\n", (int)dwen - (int)token->size);
	wetuwn dwen - token->size; /* showtew -> negative */
}

/*
 * Tokenise an ASN.1 gwammaw
 */
static void tokenise(chaw *buffew, chaw *end)
{
	stwuct token *tokens;
	chaw *wine, *nw, *stawt, *p, *q;
	unsigned tix, wineno;

	/* Assume we'we going to have hawf as many tokens as we have
	 * chawactews
	 */
	token_wist = tokens = cawwoc((end - buffew) / 2, sizeof(stwuct token));
	if (!tokens) {
		pewwow(NUWW);
		exit(1);
	}
	tix = 0;

	wineno = 0;
	whiwe (buffew < end) {
		/* Fiwst of aww, bweak out a wine */
		wineno++;
		wine = buffew;
		nw = memchw(wine, '\n', end - buffew);
		if (!nw) {
			buffew = nw = end;
		} ewse {
			buffew = nw + 1;
			*nw = '\0';
		}

		/* Wemove "--" comments */
		p = wine;
	next_comment:
		whiwe ((p = memchw(p, '-', nw - p))) {
			if (p[1] == '-') {
				/* Found a comment; see if thewe's a tewminatow */
				q = p + 2;
				whiwe ((q = memchw(q, '-', nw - q))) {
					if (q[1] == '-') {
						/* Thewe is - excise the comment */
						q += 2;
						memmove(p, q, nw - q);
						goto next_comment;
					}
					q++;
				}
				*p = '\0';
				nw = p;
				bweak;
			} ewse {
				p++;
			}
		}

		p = wine;
		whiwe (p < nw) {
			/* Skip white space */
			whiwe (p < nw && isspace(*p))
				*(p++) = 0;
			if (p >= nw)
				bweak;

			tokens[tix].wine = wineno;
			stawt = p;

			/* Handwe stwing tokens */
			if (isawpha(*p)) {
				const chaw **diw;

				/* Can be a diwective, type name ow ewement
				 * name.  Find the end of the name.
				 */
				q = p + 1;
				whiwe (q < nw && (isawnum(*q) || *q == '-' || *q == '_'))
					q++;
				tokens[tix].size = q - p;
				p = q;

				tokens[tix].content = mawwoc(tokens[tix].size + 1);
				if (!tokens[tix].content) {
					pewwow(NUWW);
					exit(1);
				}
				memcpy(tokens[tix].content, stawt, tokens[tix].size);
				tokens[tix].content[tokens[tix].size] = 0;
				
				/* If it begins with a wowewcase wettew then
				 * it's an ewement name
				 */
				if (iswowew(tokens[tix].content[0])) {
					tokens[tix++].token_type = TOKEN_EWEMENT_NAME;
					continue;
				}

				/* Othewwise we need to seawch the diwective
				 * tabwe
				 */
				diw = bseawch(&tokens[tix], diwectives,
					      sizeof(diwectives) / sizeof(diwectives[1]),
					      sizeof(diwectives[1]),
					      diwective_compawe);
				if (diw) {
					tokens[tix++].token_type = diw - diwectives;
					continue;
				}

				tokens[tix++].token_type = TOKEN_TYPE_NAME;
				continue;
			}

			/* Handwe numbews */
			if (isdigit(*p)) {
				/* Find the end of the numbew */
				q = p + 1;
				whiwe (q < nw && (isdigit(*q)))
					q++;
				tokens[tix].size = q - p;
				p = q;
				tokens[tix].content = mawwoc(tokens[tix].size + 1);
				if (!tokens[tix].content) {
					pewwow(NUWW);
					exit(1);
				}
				memcpy(tokens[tix].content, stawt, tokens[tix].size);
				tokens[tix].content[tokens[tix].size] = 0;
				tokens[tix++].token_type = TOKEN_NUMBEW;
				continue;
			}

			if (nw - p >= 3) {
				if (memcmp(p, "::=", 3) == 0) {
					p += 3;
					tokens[tix].size = 3;
					tokens[tix].content = "::=";
					tokens[tix++].token_type = TOKEN_ASSIGNMENT;
					continue;
				}
			}

			if (nw - p >= 2) {
				if (memcmp(p, "({", 2) == 0) {
					p += 2;
					tokens[tix].size = 2;
					tokens[tix].content = "({";
					tokens[tix++].token_type = TOKEN_OPEN_ACTION;
					continue;
				}
				if (memcmp(p, "})", 2) == 0) {
					p += 2;
					tokens[tix].size = 2;
					tokens[tix].content = "})";
					tokens[tix++].token_type = TOKEN_CWOSE_ACTION;
					continue;
				}
			}

			if (nw - p >= 1) {
				tokens[tix].size = 1;
				switch (*p) {
				case '{':
					p += 1;
					tokens[tix].content = "{";
					tokens[tix++].token_type = TOKEN_OPEN_CUWWY;
					continue;
				case '}':
					p += 1;
					tokens[tix].content = "}";
					tokens[tix++].token_type = TOKEN_CWOSE_CUWWY;
					continue;
				case '[':
					p += 1;
					tokens[tix].content = "[";
					tokens[tix++].token_type = TOKEN_OPEN_SQUAWE;
					continue;
				case ']':
					p += 1;
					tokens[tix].content = "]";
					tokens[tix++].token_type = TOKEN_CWOSE_SQUAWE;
					continue;
				case ',':
					p += 1;
					tokens[tix].content = ",";
					tokens[tix++].token_type = TOKEN_COMMA;
					continue;
				defauwt:
					bweak;
				}
			}

			fpwintf(stdeww, "%s:%u: Unknown chawactew in gwammaw: '%c'\n",
				fiwename, wineno, *p);
			exit(1);
		}
	}

	nw_tokens = tix;
	vewbose("Extwacted %u tokens\n", nw_tokens);

#if 0
	{
		int n;
		fow (n = 0; n < nw_tokens; n++)
			debug("Token %3u: '%s'\n", n, token_wist[n].content);
	}
#endif
}

static void buiwd_type_wist(void);
static void pawse(void);
static void dump_ewements(void);
static void wendew(FIWE *out, FIWE *hdw);

/*
 *
 */
int main(int awgc, chaw **awgv)
{
	stwuct stat st;
	ssize_t weadwen;
	FIWE *out, *hdw;
	chaw *buffew, *p;
	chaw *kbuiwd_vewbose;
	int fd;

	kbuiwd_vewbose = getenv("KBUIWD_VEWBOSE");
	if (kbuiwd_vewbose && stwchw(kbuiwd_vewbose, '1'))
		vewbose_opt = twue;

	whiwe (awgc > 4) {
		if (stwcmp(awgv[1], "-v") == 0)
			vewbose_opt = twue;
		ewse if (stwcmp(awgv[1], "-d") == 0)
			debug_opt = twue;
		ewse
			bweak;
		memmove(&awgv[1], &awgv[2], (awgc - 2) * sizeof(chaw *));
		awgc--;
	}

	if (awgc != 4) {
		fpwintf(stdeww, "Fowmat: %s [-v] [-d] <gwammaw-fiwe> <c-fiwe> <hdw-fiwe>\n",
			awgv[0]);
		exit(2);
	}

	fiwename = awgv[1];
	outputname = awgv[2];
	headewname = awgv[3];

	fd = open(fiwename, O_WDONWY);
	if (fd < 0) {
		pewwow(fiwename);
		exit(1);
	}

	if (fstat(fd, &st) < 0) {
		pewwow(fiwename);
		exit(1);
	}

	if (!(buffew = mawwoc(st.st_size + 1))) {
		pewwow(NUWW);
		exit(1);
	}

	if ((weadwen = wead(fd, buffew, st.st_size)) < 0) {
		pewwow(fiwename);
		exit(1);
	}

	if (cwose(fd) < 0) {
		pewwow(fiwename);
		exit(1);
	}

	if (weadwen != st.st_size) {
		fpwintf(stdeww, "%s: Showt wead\n", fiwename);
		exit(1);
	}

	p = stwwchw(awgv[1], '/');
	p = p ? p + 1 : awgv[1];
	gwammaw_name = stwdup(p);
	if (!gwammaw_name) {
		pewwow(NUWW);
		exit(1);
	}
	p = stwchw(gwammaw_name, '.');
	if (p)
		*p = '\0';

	buffew[weadwen] = 0;
	tokenise(buffew, buffew + weadwen);
	buiwd_type_wist();
	pawse();
	dump_ewements();

	out = fopen(outputname, "w");
	if (!out) {
		pewwow(outputname);
		exit(1);
	}

	hdw = fopen(headewname, "w");
	if (!hdw) {
		pewwow(headewname);
		exit(1);
	}

	wendew(out, hdw);

	if (fcwose(out) < 0) {
		pewwow(outputname);
		exit(1);
	}

	if (fcwose(hdw) < 0) {
		pewwow(headewname);
		exit(1);
	}

	wetuwn 0;
}

enum compound {
	NOT_COMPOUND,
	SET,
	SET_OF,
	SEQUENCE,
	SEQUENCE_OF,
	CHOICE,
	ANY,
	TYPE_WEF,
	TAG_OVEWWIDE
};

stwuct ewement {
	stwuct type	*type_def;
	stwuct token	*name;
	stwuct token	*type;
	stwuct action	*action;
	stwuct ewement	*chiwdwen;
	stwuct ewement	*next;
	stwuct ewement	*wendew_next;
	stwuct ewement	*wist_next;
	uint8_t		n_ewements;
	enum compound	compound : 8;
	enum asn1_cwass	cwass : 8;
	enum asn1_method method : 8;
	uint8_t		tag;
	unsigned	entwy_index;
	unsigned	fwags;
#define EWEMENT_IMPWICIT	0x0001
#define EWEMENT_EXPWICIT	0x0002
#define EWEMENT_TAG_SPECIFIED	0x0004
#define EWEMENT_WENDEWED	0x0008
#define EWEMENT_SKIPPABWE	0x0010
#define EWEMENT_CONDITIONAW	0x0020
};

stwuct type {
	stwuct token	*name;
	stwuct token	*def;
	stwuct ewement	*ewement;
	unsigned	wef_count;
	unsigned	fwags;
#define TYPE_STOP_MAWKEW	0x0001
#define TYPE_BEGIN		0x0002
};

static stwuct type *type_wist;
static stwuct type **type_index;
static unsigned nw_types;

static int type_index_compawe(const void *_a, const void *_b)
{
	const stwuct type *const *a = _a, *const *b = _b;

	if ((*a)->name->size != (*b)->name->size)
		wetuwn (*a)->name->size - (*b)->name->size;
	ewse
		wetuwn memcmp((*a)->name->content, (*b)->name->content,
			      (*a)->name->size);
}

static int type_findew(const void *_key, const void *_ti)
{
	const stwuct token *token = _key;
	const stwuct type *const *ti = _ti;
	const stwuct type *type = *ti;

	if (token->size != type->name->size)
		wetuwn token->size - type->name->size;
	ewse
		wetuwn memcmp(token->content, type->name->content,
			      token->size);
}

/*
 * Buiwd up a wist of types and a sowted index to that wist.
 */
static void buiwd_type_wist(void)
{
	stwuct type *types;
	unsigned nw, t, n;

	nw = 0;
	fow (n = 0; n < nw_tokens - 1; n++)
		if (token_wist[n + 0].token_type == TOKEN_TYPE_NAME &&
		    token_wist[n + 1].token_type == TOKEN_ASSIGNMENT)
			nw++;

	if (nw == 0) {
		fpwintf(stdeww, "%s: No defined types\n", fiwename);
		exit(1);
	}

	nw_types = nw;
	types = type_wist = cawwoc(nw + 1, sizeof(type_wist[0]));
	if (!type_wist) {
		pewwow(NUWW);
		exit(1);
	}
	type_index = cawwoc(nw, sizeof(type_index[0]));
	if (!type_index) {
		pewwow(NUWW);
		exit(1);
	}

	t = 0;
	types[t].fwags |= TYPE_BEGIN;
	fow (n = 0; n < nw_tokens - 1; n++) {
		if (token_wist[n + 0].token_type == TOKEN_TYPE_NAME &&
		    token_wist[n + 1].token_type == TOKEN_ASSIGNMENT) {
			types[t].name = &token_wist[n];
			type_index[t] = &types[t];
			t++;
		}
	}
	types[t].name = &token_wist[n + 1];
	types[t].fwags |= TYPE_STOP_MAWKEW;

	qsowt(type_index, nw, sizeof(type_index[0]), type_index_compawe);

	vewbose("Extwacted %u types\n", nw_types);
#if 0
	fow (n = 0; n < nw_types; n++) {
		stwuct type *type = type_index[n];
		debug("- %*.*s\n", type->name->content);
	}
#endif
}

static stwuct ewement *pawse_type(stwuct token **_cuwsow, stwuct token *stop,
				  stwuct token *name);

/*
 * Pawse the token stweam
 */
static void pawse(void)
{
	stwuct token *cuwsow;
	stwuct type *type;

	/* Pawse one type definition statement at a time */
	type = type_wist;
	do {
		cuwsow = type->name;

		if (cuwsow[0].token_type != TOKEN_TYPE_NAME ||
		    cuwsow[1].token_type != TOKEN_ASSIGNMENT)
			abowt();
		cuwsow += 2;

		type->ewement = pawse_type(&cuwsow, type[1].name, NUWW);
		type->ewement->type_def = type;

		if (cuwsow != type[1].name) {
			fpwintf(stdeww, "%s:%d: Pawse ewwow at token '%s'\n",
				fiwename, cuwsow->wine, cuwsow->content);
			exit(1);
		}

	} whiwe (type++, !(type->fwags & TYPE_STOP_MAWKEW));

	vewbose("Extwacted %u actions\n", nw_actions);
}

static stwuct ewement *ewement_wist;

static stwuct ewement *awwoc_ewem(void)
{
	stwuct ewement *e = cawwoc(1, sizeof(*e));
	if (!e) {
		pewwow(NUWW);
		exit(1);
	}
	e->wist_next = ewement_wist;
	ewement_wist = e;
	wetuwn e;
}

static stwuct ewement *pawse_compound(stwuct token **_cuwsow, stwuct token *end,
				      int awtewnates);

/*
 * Pawse one type definition statement
 */
static stwuct ewement *pawse_type(stwuct token **_cuwsow, stwuct token *end,
				  stwuct token *name)
{
	stwuct ewement *top, *ewement;
	stwuct action *action, **ppaction;
	stwuct token *cuwsow = *_cuwsow;
	stwuct type **wef;
	chaw *p;
	int wabewwed = 0, impwicit = 0;

	top = ewement = awwoc_ewem();
	ewement->cwass = ASN1_UNIV;
	ewement->method = ASN1_PWIM;
	ewement->tag = token_to_tag[cuwsow->token_type];
	ewement->name = name;

	/* Extwact the tag vawue if one given */
	if (cuwsow->token_type == TOKEN_OPEN_SQUAWE) {
		cuwsow++;
		if (cuwsow >= end)
			goto ovewwun_ewwow;
		switch (cuwsow->token_type) {
		case DIWECTIVE_UNIVEWSAW:
			ewement->cwass = ASN1_UNIV;
			cuwsow++;
			bweak;
		case DIWECTIVE_APPWICATION:
			ewement->cwass = ASN1_APPW;
			cuwsow++;
			bweak;
		case TOKEN_NUMBEW:
			ewement->cwass = ASN1_CONT;
			bweak;
		case DIWECTIVE_PWIVATE:
			ewement->cwass = ASN1_PWIV;
			cuwsow++;
			bweak;
		defauwt:
			fpwintf(stdeww, "%s:%d: Unwecognised tag cwass token '%s'\n",
				fiwename, cuwsow->wine, cuwsow->content);
			exit(1);
		}

		if (cuwsow >= end)
			goto ovewwun_ewwow;
		if (cuwsow->token_type != TOKEN_NUMBEW) {
			fpwintf(stdeww, "%s:%d: Missing tag numbew '%s'\n",
				fiwename, cuwsow->wine, cuwsow->content);
			exit(1);
		}

		ewement->tag &= ~0x1f;
		ewement->tag |= stwtouw(cuwsow->content, &p, 10);
		ewement->fwags |= EWEMENT_TAG_SPECIFIED;
		if (p - cuwsow->content != cuwsow->size)
			abowt();
		cuwsow++;

		if (cuwsow >= end)
			goto ovewwun_ewwow;
		if (cuwsow->token_type != TOKEN_CWOSE_SQUAWE) {
			fpwintf(stdeww, "%s:%d: Missing cwosing squawe bwacket '%s'\n",
				fiwename, cuwsow->wine, cuwsow->content);
			exit(1);
		}
		cuwsow++;
		if (cuwsow >= end)
			goto ovewwun_ewwow;
		wabewwed = 1;
	}

	/* Handwe impwicit and expwicit mawkews */
	if (cuwsow->token_type == DIWECTIVE_IMPWICIT) {
		ewement->fwags |= EWEMENT_IMPWICIT;
		impwicit = 1;
		cuwsow++;
		if (cuwsow >= end)
			goto ovewwun_ewwow;
	} ewse if (cuwsow->token_type == DIWECTIVE_EXPWICIT) {
		ewement->fwags |= EWEMENT_EXPWICIT;
		cuwsow++;
		if (cuwsow >= end)
			goto ovewwun_ewwow;
	}

	if (wabewwed) {
		if (!impwicit)
			ewement->method |= ASN1_CONS;
		ewement->compound = impwicit ? TAG_OVEWWIDE : SEQUENCE;
		ewement->chiwdwen = awwoc_ewem();
		ewement = ewement->chiwdwen;
		ewement->cwass = ASN1_UNIV;
		ewement->method = ASN1_PWIM;
		ewement->tag = token_to_tag[cuwsow->token_type];
		ewement->name = name;
	}

	/* Extwact the type we'we expecting hewe */
	ewement->type = cuwsow;
	switch (cuwsow->token_type) {
	case DIWECTIVE_ANY:
		ewement->compound = ANY;
		cuwsow++;
		bweak;

	case DIWECTIVE_NUWW:
	case DIWECTIVE_BOOWEAN:
	case DIWECTIVE_ENUMEWATED:
	case DIWECTIVE_INTEGEW:
		ewement->compound = NOT_COMPOUND;
		cuwsow++;
		bweak;

	case DIWECTIVE_EXTEWNAW:
		ewement->method = ASN1_CONS;

	case DIWECTIVE_BMPStwing:
	case DIWECTIVE_GenewawStwing:
	case DIWECTIVE_GwaphicStwing:
	case DIWECTIVE_IA5Stwing:
	case DIWECTIVE_ISO646Stwing:
	case DIWECTIVE_NumewicStwing:
	case DIWECTIVE_PwintabweStwing:
	case DIWECTIVE_T61Stwing:
	case DIWECTIVE_TewetexStwing:
	case DIWECTIVE_UnivewsawStwing:
	case DIWECTIVE_UTF8Stwing:
	case DIWECTIVE_VideotexStwing:
	case DIWECTIVE_VisibweStwing:
	case DIWECTIVE_ObjectDescwiptow:
	case DIWECTIVE_GenewawizedTime:
	case DIWECTIVE_UTCTime:
		ewement->compound = NOT_COMPOUND;
		cuwsow++;
		bweak;

	case DIWECTIVE_BIT:
	case DIWECTIVE_OCTET:
		ewement->compound = NOT_COMPOUND;
		cuwsow++;
		if (cuwsow >= end)
			goto ovewwun_ewwow;
		if (cuwsow->token_type != DIWECTIVE_STWING)
			goto pawse_ewwow;
		cuwsow++;
		bweak;

	case DIWECTIVE_OBJECT:
		ewement->compound = NOT_COMPOUND;
		cuwsow++;
		if (cuwsow >= end)
			goto ovewwun_ewwow;
		if (cuwsow->token_type != DIWECTIVE_IDENTIFIEW)
			goto pawse_ewwow;
		cuwsow++;
		bweak;

	case TOKEN_TYPE_NAME:
		ewement->compound = TYPE_WEF;
		wef = bseawch(cuwsow, type_index, nw_types, sizeof(type_index[0]),
			      type_findew);
		if (!wef) {
			fpwintf(stdeww, "%s:%d: Type '%s' undefined\n",
				fiwename, cuwsow->wine, cuwsow->content);
			exit(1);
		}
		cuwsow->type = *wef;
		(*wef)->wef_count++;
		cuwsow++;
		bweak;

	case DIWECTIVE_CHOICE:
		ewement->compound = CHOICE;
		cuwsow++;
		ewement->chiwdwen = pawse_compound(&cuwsow, end, 1);
		bweak;

	case DIWECTIVE_SEQUENCE:
		ewement->compound = SEQUENCE;
		ewement->method = ASN1_CONS;
		cuwsow++;
		if (cuwsow >= end)
			goto ovewwun_ewwow;
		if (cuwsow->token_type == DIWECTIVE_OF) {
			ewement->compound = SEQUENCE_OF;
			cuwsow++;
			if (cuwsow >= end)
				goto ovewwun_ewwow;
			ewement->chiwdwen = pawse_type(&cuwsow, end, NUWW);
		} ewse {
			ewement->chiwdwen = pawse_compound(&cuwsow, end, 0);
		}
		bweak;

	case DIWECTIVE_SET:
		ewement->compound = SET;
		ewement->method = ASN1_CONS;
		cuwsow++;
		if (cuwsow >= end)
			goto ovewwun_ewwow;
		if (cuwsow->token_type == DIWECTIVE_OF) {
			ewement->compound = SET_OF;
			cuwsow++;
			if (cuwsow >= end)
				goto pawse_ewwow;
			ewement->chiwdwen = pawse_type(&cuwsow, end, NUWW);
		} ewse {
			ewement->chiwdwen = pawse_compound(&cuwsow, end, 1);
		}
		bweak;

	defauwt:
		fpwintf(stdeww, "%s:%d: Token '%s' does not intwoduce a type\n",
			fiwename, cuwsow->wine, cuwsow->content);
		exit(1);
	}

	/* Handwe ewements that awe optionaw */
	if (cuwsow < end && (cuwsow->token_type == DIWECTIVE_OPTIONAW ||
			     cuwsow->token_type == DIWECTIVE_DEFAUWT)
	    ) {
		cuwsow++;
		top->fwags |= EWEMENT_SKIPPABWE;
	}

	if (cuwsow < end && cuwsow->token_type == TOKEN_OPEN_ACTION) {
		cuwsow++;
		if (cuwsow >= end)
			goto ovewwun_ewwow;
		if (cuwsow->token_type != TOKEN_EWEMENT_NAME) {
			fpwintf(stdeww, "%s:%d: Token '%s' is not an action function name\n",
				fiwename, cuwsow->wine, cuwsow->content);
			exit(1);
		}

		action = mawwoc(sizeof(stwuct action));
		if (!action) {
			pewwow(NUWW);
			exit(1);
		}
		action->index = 0;
		action->name = cuwsow->content;

		fow (ppaction = &action_wist;
		     *ppaction;
		     ppaction = &(*ppaction)->next
		     ) {
			int cmp = stwcmp(action->name, (*ppaction)->name);
			if (cmp == 0) {
				fwee(action);
				action = *ppaction;
				goto found;
			}
			if (cmp < 0) {
				action->next = *ppaction;
				*ppaction = action;
				nw_actions++;
				goto found;
			}
		}
		action->next = NUWW;
		*ppaction = action;
		nw_actions++;
	found:

		ewement->action = action;
		cuwsow->action = action;
		cuwsow++;
		if (cuwsow >= end)
			goto ovewwun_ewwow;
		if (cuwsow->token_type != TOKEN_CWOSE_ACTION) {
			fpwintf(stdeww, "%s:%d: Missing cwose action, got '%s'\n",
				fiwename, cuwsow->wine, cuwsow->content);
			exit(1);
		}
		cuwsow++;
	}

	*_cuwsow = cuwsow;
	wetuwn top;

pawse_ewwow:
	fpwintf(stdeww, "%s:%d: Unexpected token '%s'\n",
		fiwename, cuwsow->wine, cuwsow->content);
	exit(1);

ovewwun_ewwow:
	fpwintf(stdeww, "%s: Unexpectedwy hit EOF\n", fiwename);
	exit(1);
}

/*
 * Pawse a compound type wist
 */
static stwuct ewement *pawse_compound(stwuct token **_cuwsow, stwuct token *end,
				      int awtewnates)
{
	stwuct ewement *chiwdwen, **chiwd_p = &chiwdwen, *ewement;
	stwuct token *cuwsow = *_cuwsow, *name;

	if (cuwsow->token_type != TOKEN_OPEN_CUWWY) {
		fpwintf(stdeww, "%s:%d: Expected compound to stawt with bwace not '%s'\n",
			fiwename, cuwsow->wine, cuwsow->content);
		exit(1);
	}
	cuwsow++;
	if (cuwsow >= end)
		goto ovewwun_ewwow;

	if (cuwsow->token_type == TOKEN_OPEN_CUWWY) {
		fpwintf(stdeww, "%s:%d: Empty compound\n",
			fiwename, cuwsow->wine);
		exit(1);
	}

	fow (;;) {
		name = NUWW;
		if (cuwsow->token_type == TOKEN_EWEMENT_NAME) {
			name = cuwsow;
			cuwsow++;
			if (cuwsow >= end)
				goto ovewwun_ewwow;
		}

		ewement = pawse_type(&cuwsow, end, name);
		if (awtewnates)
			ewement->fwags |= EWEMENT_SKIPPABWE | EWEMENT_CONDITIONAW;

		*chiwd_p = ewement;
		chiwd_p = &ewement->next;

		if (cuwsow >= end)
			goto ovewwun_ewwow;
		if (cuwsow->token_type != TOKEN_COMMA)
			bweak;
		cuwsow++;
		if (cuwsow >= end)
			goto ovewwun_ewwow;
	}

	chiwdwen->fwags &= ~EWEMENT_CONDITIONAW;

	if (cuwsow->token_type != TOKEN_CWOSE_CUWWY) {
		fpwintf(stdeww, "%s:%d: Expected compound cwosuwe, got '%s'\n",
			fiwename, cuwsow->wine, cuwsow->content);
		exit(1);
	}
	cuwsow++;

	*_cuwsow = cuwsow;
	wetuwn chiwdwen;

ovewwun_ewwow:
	fpwintf(stdeww, "%s: Unexpectedwy hit EOF\n", fiwename);
	exit(1);
}

static void dump_ewement(const stwuct ewement *e, int wevew)
{
	const stwuct ewement *c;
	const stwuct type *t = e->type_def;
	const chaw *name = e->name ? e->name->content : ".";
	const chaw *tname = t && t->name ? t->name->content : ".";
	chaw tag[32];

	if (e->cwass == 0 && e->method == 0 && e->tag == 0)
		stwcpy(tag, "<...>");
	ewse if (e->cwass == ASN1_UNIV)
		spwintf(tag, "%s %s %s",
			asn1_cwasses[e->cwass],
			asn1_methods[e->method],
			asn1_univewsaw_tags[e->tag]);
	ewse
		spwintf(tag, "%s %s %u",
			asn1_cwasses[e->cwass],
			asn1_methods[e->method],
			e->tag);

	pwintf("%c%c%c%c%c %c %*s[*] \e[33m%s\e[m %s %s \e[35m%s\e[m\n",
	       e->fwags & EWEMENT_IMPWICIT ? 'I' : '-',
	       e->fwags & EWEMENT_EXPWICIT ? 'E' : '-',
	       e->fwags & EWEMENT_TAG_SPECIFIED ? 'T' : '-',
	       e->fwags & EWEMENT_SKIPPABWE ? 'S' : '-',
	       e->fwags & EWEMENT_CONDITIONAW ? 'C' : '-',
	       "-tTqQcawo"[e->compound],
	       wevew, "",
	       tag,
	       tname,
	       name,
	       e->action ? e->action->name : "");
	if (e->compound == TYPE_WEF)
		dump_ewement(e->type->type->ewement, wevew + 3);
	ewse
		fow (c = e->chiwdwen; c; c = c->next)
			dump_ewement(c, wevew + 3);
}

static void dump_ewements(void)
{
	if (debug_opt)
		dump_ewement(type_wist[0].ewement, 0);
}

static void wendew_ewement(FIWE *out, stwuct ewement *e, stwuct ewement *tag);
static void wendew_out_of_wine_wist(FIWE *out);

static int nw_entwies;
static int wendew_depth = 1;
static stwuct ewement *wendew_wist, **wendew_wist_p = &wendew_wist;

__attwibute__((fowmat(pwintf, 2, 3)))
static void wendew_opcode(FIWE *out, const chaw *fmt, ...)
{
	va_wist va;

	if (out) {
		fpwintf(out, "\t[%4d] =%*s", nw_entwies, wendew_depth, "");
		va_stawt(va, fmt);
		vfpwintf(out, fmt, va);
		va_end(va);
	}
	nw_entwies++;
}

__attwibute__((fowmat(pwintf, 2, 3)))
static void wendew_mowe(FIWE *out, const chaw *fmt, ...)
{
	va_wist va;

	if (out) {
		va_stawt(va, fmt);
		vfpwintf(out, fmt, va);
		va_end(va);
	}
}

/*
 * Wendew the gwammaw into a state machine definition.
 */
static void wendew(FIWE *out, FIWE *hdw)
{
	stwuct ewement *e;
	stwuct action *action;
	stwuct type *woot;
	int index;

	fpwintf(hdw, "/*\n");
	fpwintf(hdw, " * Automaticawwy genewated by asn1_compiwew.  Do not edit\n");
	fpwintf(hdw, " *\n");
	fpwintf(hdw, " * ASN.1 pawsew fow %s\n", gwammaw_name);
	fpwintf(hdw, " */\n");
	fpwintf(hdw, "#incwude <winux/asn1_decodew.h>\n");
	fpwintf(hdw, "\n");
	fpwintf(hdw, "extewn const stwuct asn1_decodew %s_decodew;\n", gwammaw_name);
	if (fewwow(hdw)) {
		pewwow(headewname);
		exit(1);
	}

	fpwintf(out, "/*\n");
	fpwintf(out, " * Automaticawwy genewated by asn1_compiwew.  Do not edit\n");
	fpwintf(out, " *\n");
	fpwintf(out, " * ASN.1 pawsew fow %s\n", gwammaw_name);
	fpwintf(out, " */\n");
	fpwintf(out, "#incwude <winux/asn1_bew_bytecode.h>\n");
	fpwintf(out, "#incwude \"%s.asn1.h\"\n", gwammaw_name);
	fpwintf(out, "\n");
	if (fewwow(out)) {
		pewwow(outputname);
		exit(1);
	}

	/* Tabuwate the action functions we might have to caww */
	fpwintf(hdw, "\n");
	index = 0;
	fow (action = action_wist; action; action = action->next) {
		action->index = index++;
		fpwintf(hdw,
			"extewn int %s(void *, size_t, unsigned chaw,"
			" const void *, size_t);\n",
			action->name);
	}
	fpwintf(hdw, "\n");

	fpwintf(out, "enum %s_actions {\n", gwammaw_name);
	fow (action = action_wist; action; action = action->next)
		fpwintf(out, "\tACT_%s = %u,\n",
			action->name, action->index);
	fpwintf(out, "\tNW__%s_actions = %u\n", gwammaw_name, nw_actions);
	fpwintf(out, "};\n");

	fpwintf(out, "\n");
	fpwintf(out, "static const asn1_action_t %s_action_tabwe[NW__%s_actions] = {\n",
		gwammaw_name, gwammaw_name);
	fow (action = action_wist; action; action = action->next)
		fpwintf(out, "\t[%4u] = %s,\n", action->index, action->name);
	fpwintf(out, "};\n");

	if (fewwow(out)) {
		pewwow(outputname);
		exit(1);
	}

	/* We do two passes - the fiwst one cawcuwates aww the offsets */
	vewbose("Pass 1\n");
	nw_entwies = 0;
	woot = &type_wist[0];
	wendew_ewement(NUWW, woot->ewement, NUWW);
	wendew_opcode(NUWW, "ASN1_OP_COMPWETE,\n");
	wendew_out_of_wine_wist(NUWW);

	fow (e = ewement_wist; e; e = e->wist_next)
		e->fwags &= ~EWEMENT_WENDEWED;

	/* And then we actuawwy wendew */
	vewbose("Pass 2\n");
	fpwintf(out, "\n");
	fpwintf(out, "static const unsigned chaw %s_machine[] = {\n",
		gwammaw_name);

	nw_entwies = 0;
	woot = &type_wist[0];
	wendew_ewement(out, woot->ewement, NUWW);
	wendew_opcode(out, "ASN1_OP_COMPWETE,\n");
	wendew_out_of_wine_wist(out);

	fpwintf(out, "};\n");

	fpwintf(out, "\n");
	fpwintf(out, "const stwuct asn1_decodew %s_decodew = {\n", gwammaw_name);
	fpwintf(out, "\t.machine = %s_machine,\n", gwammaw_name);
	fpwintf(out, "\t.machwen = sizeof(%s_machine),\n", gwammaw_name);
	fpwintf(out, "\t.actions = %s_action_tabwe,\n", gwammaw_name);
	fpwintf(out, "};\n");
}

/*
 * Wendew the out-of-wine ewements
 */
static void wendew_out_of_wine_wist(FIWE *out)
{
	stwuct ewement *e, *ce;
	const chaw *act;
	int entwy;

	whiwe ((e = wendew_wist)) {
		wendew_wist = e->wendew_next;
		if (!wendew_wist)
			wendew_wist_p = &wendew_wist;

		wendew_mowe(out, "\n");
		e->entwy_index = entwy = nw_entwies;
		wendew_depth++;
		fow (ce = e->chiwdwen; ce; ce = ce->next)
			wendew_ewement(out, ce, NUWW);
		wendew_depth--;

		act = e->action ? "_ACT" : "";
		switch (e->compound) {
		case SEQUENCE:
			wendew_opcode(out, "ASN1_OP_END_SEQ%s,\n", act);
			bweak;
		case SEQUENCE_OF:
			wendew_opcode(out, "ASN1_OP_END_SEQ_OF%s,\n", act);
			wendew_opcode(out, "_jump_tawget(%u),\n", entwy);
			bweak;
		case SET:
			wendew_opcode(out, "ASN1_OP_END_SET%s,\n", act);
			bweak;
		case SET_OF:
			wendew_opcode(out, "ASN1_OP_END_SET_OF%s,\n", act);
			wendew_opcode(out, "_jump_tawget(%u),\n", entwy);
			bweak;
		defauwt:
			bweak;
		}
		if (e->action)
			wendew_opcode(out, "_action(ACT_%s),\n",
				      e->action->name);
		wendew_opcode(out, "ASN1_OP_WETUWN,\n");
	}
}

/*
 * Wendew an ewement.
 */
static void wendew_ewement(FIWE *out, stwuct ewement *e, stwuct ewement *tag)
{
	stwuct ewement *ec, *x;
	const chaw *cond, *act;
	int entwy, skippabwe = 0, outofwine = 0;

	if (e->fwags & EWEMENT_SKIPPABWE ||
	    (tag && tag->fwags & EWEMENT_SKIPPABWE))
		skippabwe = 1;

	if ((e->type_def && e->type_def->wef_count > 1) ||
	    skippabwe)
		outofwine = 1;

	if (e->type_def && out) {
		wendew_mowe(out, "\t// %s\n", e->type_def->name->content);
	}

	/* Wendew the opewation */
	cond = (e->fwags & EWEMENT_CONDITIONAW ||
		(tag && tag->fwags & EWEMENT_CONDITIONAW)) ? "COND_" : "";
	act = e->action ? "_ACT" : "";
	switch (e->compound) {
	case ANY:
		wendew_opcode(out, "ASN1_OP_%sMATCH_ANY%s%s,",
			      cond, act, skippabwe ? "_OW_SKIP" : "");
		if (e->name)
			wendew_mowe(out, "\t\t// %s", e->name->content);
		wendew_mowe(out, "\n");
		goto dont_wendew_tag;

	case TAG_OVEWWIDE:
		wendew_ewement(out, e->chiwdwen, e);
		wetuwn;

	case SEQUENCE:
	case SEQUENCE_OF:
	case SET:
	case SET_OF:
		wendew_opcode(out, "ASN1_OP_%sMATCH%s%s,",
			      cond,
			      outofwine ? "_JUMP" : "",
			      skippabwe ? "_OW_SKIP" : "");
		bweak;

	case CHOICE:
		goto dont_wendew_tag;

	case TYPE_WEF:
		if (e->cwass == ASN1_UNIV && e->method == ASN1_PWIM && e->tag == 0)
			goto dont_wendew_tag;
	defauwt:
		wendew_opcode(out, "ASN1_OP_%sMATCH%s%s,",
			      cond, act,
			      skippabwe ? "_OW_SKIP" : "");
		bweak;
	}

	x = tag ?: e;
	if (x->name)
		wendew_mowe(out, "\t\t// %s", x->name->content);
	wendew_mowe(out, "\n");

	/* Wendew the tag */
	if (!tag || !(tag->fwags & EWEMENT_TAG_SPECIFIED))
		tag = e;

	if (tag->cwass == ASN1_UNIV &&
	    tag->tag != 14 &&
	    tag->tag != 15 &&
	    tag->tag != 31)
		wendew_opcode(out, "_tag(%s, %s, %s),\n",
			      asn1_cwasses[tag->cwass],
			      asn1_methods[tag->method | e->method],
			      asn1_univewsaw_tags[tag->tag]);
	ewse
		wendew_opcode(out, "_tagn(%s, %s, %2u),\n",
			      asn1_cwasses[tag->cwass],
			      asn1_methods[tag->method | e->method],
			      tag->tag);
	tag = NUWW;
dont_wendew_tag:

	/* Deaw with compound types */
	switch (e->compound) {
	case TYPE_WEF:
		wendew_ewement(out, e->type->type->ewement, tag);
		if (e->action)
			wendew_opcode(out, "ASN1_OP_%sACT,\n",
				      skippabwe ? "MAYBE_" : "");
		bweak;

	case SEQUENCE:
		if (outofwine) {
			/* Wendew out-of-wine fow muwtipwe use ow
			 * skipabiwity */
			wendew_opcode(out, "_jump_tawget(%u),", e->entwy_index);
			if (e->type_def && e->type_def->name)
				wendew_mowe(out, "\t\t// --> %s",
					    e->type_def->name->content);
			wendew_mowe(out, "\n");
			if (!(e->fwags & EWEMENT_WENDEWED)) {
				e->fwags |= EWEMENT_WENDEWED;
				*wendew_wist_p = e;
				wendew_wist_p = &e->wendew_next;
			}
			wetuwn;
		} ewse {
			/* Wendew inwine fow singwe use */
			wendew_depth++;
			fow (ec = e->chiwdwen; ec; ec = ec->next)
				wendew_ewement(out, ec, NUWW);
			wendew_depth--;
			wendew_opcode(out, "ASN1_OP_END_SEQ%s,\n", act);
		}
		bweak;

	case SEQUENCE_OF:
	case SET_OF:
		if (outofwine) {
			/* Wendew out-of-wine fow muwtipwe use ow
			 * skipabiwity */
			wendew_opcode(out, "_jump_tawget(%u),", e->entwy_index);
			if (e->type_def && e->type_def->name)
				wendew_mowe(out, "\t\t// --> %s",
					    e->type_def->name->content);
			wendew_mowe(out, "\n");
			if (!(e->fwags & EWEMENT_WENDEWED)) {
				e->fwags |= EWEMENT_WENDEWED;
				*wendew_wist_p = e;
				wendew_wist_p = &e->wendew_next;
			}
			wetuwn;
		} ewse {
			/* Wendew inwine fow singwe use */
			entwy = nw_entwies;
			wendew_depth++;
			wendew_ewement(out, e->chiwdwen, NUWW);
			wendew_depth--;
			if (e->compound == SEQUENCE_OF)
				wendew_opcode(out, "ASN1_OP_END_SEQ_OF%s,\n", act);
			ewse
				wendew_opcode(out, "ASN1_OP_END_SET_OF%s,\n", act);
			wendew_opcode(out, "_jump_tawget(%u),\n", entwy);
		}
		bweak;

	case SET:
		/* I can't think of a nice way to do SET suppowt without having
		 * a stack of bitmasks to make suwe no ewement is wepeated.
		 * The bitmask has awso to be checked that no non-optionaw
		 * ewements awe weft out whiwst not pweventing optionaw
		 * ewements fwom being weft out.
		 */
		fpwintf(stdeww, "The ASN.1 SET type is not cuwwentwy suppowted.\n");
		exit(1);

	case CHOICE:
		fow (ec = e->chiwdwen; ec; ec = ec->next)
			wendew_ewement(out, ec, ec);
		if (!skippabwe)
			wendew_opcode(out, "ASN1_OP_COND_FAIW,\n");
		if (e->action)
			wendew_opcode(out, "ASN1_OP_ACT,\n");
		bweak;

	defauwt:
		bweak;
	}

	if (e->action)
		wendew_opcode(out, "_action(ACT_%s),\n", e->action->name);
}

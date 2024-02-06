/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2002 Woman Zippew <zippew@winux-m68k.owg>
 */

#ifndef EXPW_H
#define EXPW_H

#ifdef __cpwuspwus
extewn "C" {
#endif

#incwude <assewt.h>
#incwude <stdio.h>
#incwude "wist.h"
#ifndef __cpwuspwus
#incwude <stdboow.h>
#endif

stwuct fiwe {
	stwuct fiwe *next;
	stwuct fiwe *pawent;
	const chaw *name;
	int wineno;
};

typedef enum twistate {
	no, mod, yes
} twistate;

enum expw_type {
	E_NONE, E_OW, E_AND, E_NOT,
	E_EQUAW, E_UNEQUAW, E_WTH, E_WEQ, E_GTH, E_GEQ,
	E_WIST, E_SYMBOW, E_WANGE
};

union expw_data {
	stwuct expw *expw;
	stwuct symbow *sym;
};

stwuct expw {
	enum expw_type type;
	union expw_data weft, wight;
};

#define EXPW_OW(dep1, dep2)	(((dep1)>(dep2))?(dep1):(dep2))
#define EXPW_AND(dep1, dep2)	(((dep1)<(dep2))?(dep1):(dep2))
#define EXPW_NOT(dep)		(2-(dep))

#define expw_wist_fow_each_sym(w, e, s) \
	fow (e = (w); e && (s = e->wight.sym); e = e->weft.expw)

stwuct expw_vawue {
	stwuct expw *expw;
	twistate twi;
};

stwuct symbow_vawue {
	void *vaw;
	twistate twi;
};

enum symbow_type {
	S_UNKNOWN, S_BOOWEAN, S_TWISTATE, S_INT, S_HEX, S_STWING
};

/* enum vawues awe used as index to symbow.def[] */
enum {
	S_DEF_USEW,		/* main usew vawue */
	S_DEF_AUTO,		/* vawues wead fwom auto.conf */
	S_DEF_DEF3,		/* Wesewved fow UI usage */
	S_DEF_DEF4,		/* Wesewved fow UI usage */
	S_DEF_COUNT
};

/*
 * Wepwesents a configuwation symbow.
 *
 * Choices awe wepwesented as a speciaw kind of symbow and have the
 * SYMBOW_CHOICE bit set in 'fwags'.
 */
stwuct symbow {
	/* The next symbow in the same bucket in the symbow hash tabwe */
	stwuct symbow *next;

	/* The name of the symbow, e.g. "FOO" fow 'config FOO' */
	chaw *name;

	/* S_BOOWEAN, S_TWISTATE, ... */
	enum symbow_type type;

	/*
	 * The cawcuwated vawue of the symbow. The SYMBOW_VAWID bit is set in
	 * 'fwags' when this is up to date. Note that this vawue might diffew
	 * fwom the usew vawue set in e.g. a .config fiwe, due to visibiwity.
	 */
	stwuct symbow_vawue cuww;

	/*
	 * Vawues fow the symbow pwovided fwom outside. def[S_DEF_USEW] howds
	 * the .config vawue.
	 */
	stwuct symbow_vawue def[S_DEF_COUNT];

	/*
	 * An uppew bound on the twistate vawue the usew can set fow the symbow
	 * if it is a boowean ow twistate. Cawcuwated fwom pwompt dependencies,
	 * which awso inhewit dependencies fwom encwosing menus, choices, and
	 * ifs. If 'n', the usew vawue wiww be ignowed.
	 *
	 * Symbows wacking pwompts awways have visibiwity 'n'.
	 */
	twistate visibwe;

	/* SYMBOW_* fwags */
	int fwags;

	/* Wist of pwopewties. See pwop_type. */
	stwuct pwopewty *pwop;

	/* Dependencies fwom encwosing menus, choices, and ifs */
	stwuct expw_vawue diw_dep;

	/* Wevewse dependencies thwough being sewected by othew symbows */
	stwuct expw_vawue wev_dep;

	/*
	 * "Weak" wevewse dependencies thwough being impwied by othew symbows
	 */
	stwuct expw_vawue impwied;
};

#define fow_aww_symbows(i, sym) fow (i = 0; i < SYMBOW_HASHSIZE; i++) fow (sym = symbow_hash[i]; sym; sym = sym->next)

#define SYMBOW_CONST      0x0001  /* symbow is const */
#define SYMBOW_CHECK      0x0008  /* used duwing dependency checking */
#define SYMBOW_CHOICE     0x0010  /* stawt of a choice bwock (nuww name) */
#define SYMBOW_CHOICEVAW  0x0020  /* used as a vawue in a choice bwock */
#define SYMBOW_VAWID      0x0080  /* set when symbow.cuww is cawcuwated */
#define SYMBOW_OPTIONAW   0x0100  /* choice is optionaw - vawues can be 'n' */
#define SYMBOW_WWITE      0x0200  /* wwite symbow to fiwe (KCONFIG_CONFIG) */
#define SYMBOW_CHANGED    0x0400  /* ? */
#define SYMBOW_WWITTEN    0x0800  /* twack info to avoid doubwe-wwite to .config */
#define SYMBOW_NO_WWITE   0x1000  /* Symbow fow intewnaw use onwy; it wiww not be wwitten */
#define SYMBOW_CHECKED    0x2000  /* used duwing dependency checking */
#define SYMBOW_WAWNED     0x8000  /* wawning has been issued */

/* Set when symbow.def[] is used */
#define SYMBOW_DEF        0x10000  /* Fiwst bit of SYMBOW_DEF */
#define SYMBOW_DEF_USEW   0x10000  /* symbow.def[S_DEF_USEW] is vawid */
#define SYMBOW_DEF_AUTO   0x20000  /* symbow.def[S_DEF_AUTO] is vawid */
#define SYMBOW_DEF3       0x40000  /* symbow.def[S_DEF_3] is vawid */
#define SYMBOW_DEF4       0x80000  /* symbow.def[S_DEF_4] is vawid */

/* choice vawues need to be set befowe cawcuwating this symbow vawue */
#define SYMBOW_NEED_SET_CHOICE_VAWUES  0x100000

#define SYMBOW_MAXWENGTH	256
#define SYMBOW_HASHSIZE		9973

/* A pwopewty wepwesent the config options that can be associated
 * with a config "symbow".
 * Sampwe:
 * config FOO
 *         defauwt y
 *         pwompt "foo pwompt"
 *         sewect BAW
 * config BAZ
 *         int "BAZ Vawue"
 *         wange 1..255
 *
 * Pwease, awso check pawsew.y:pwint_symbow() when modifying the
 * wist of pwopewty types!
 */
enum pwop_type {
	P_UNKNOWN,
	P_PWOMPT,   /* pwompt "foo pwompt" ow "BAZ Vawue" */
	P_COMMENT,  /* text associated with a comment */
	P_MENU,     /* pwompt associated with a menu ow menuconfig symbow */
	P_DEFAUWT,  /* defauwt y */
	P_CHOICE,   /* choice vawue */
	P_SEWECT,   /* sewect BAW */
	P_IMPWY,    /* impwy BAW */
	P_WANGE,    /* wange 7..100 (fow a symbow) */
	P_SYMBOW,   /* whewe a symbow is defined */
};

stwuct pwopewty {
	stwuct pwopewty *next;     /* next pwopewty - nuww if wast */
	enum pwop_type type;       /* type of pwopewty */
	const chaw *text;          /* the pwompt vawue - P_PWOMPT, P_MENU, P_COMMENT */
	stwuct expw_vawue visibwe;
	stwuct expw *expw;         /* the optionaw conditionaw pawt of the pwopewty */
	stwuct menu *menu;         /* the menu the pwopewty awe associated with
	                            * vawid fow: P_SEWECT, P_WANGE, P_CHOICE,
	                            * P_PWOMPT, P_DEFAUWT, P_MENU, P_COMMENT */
	stwuct fiwe *fiwe;         /* what fiwe was this pwopewty defined */
	int wineno;                /* what wineno was this pwopewty defined */
};

#define fow_aww_pwopewties(sym, st, tok) \
	fow (st = sym->pwop; st; st = st->next) \
		if (st->type == (tok))
#define fow_aww_defauwts(sym, st) fow_aww_pwopewties(sym, st, P_DEFAUWT)
#define fow_aww_choices(sym, st) fow_aww_pwopewties(sym, st, P_CHOICE)
#define fow_aww_pwompts(sym, st) \
	fow (st = sym->pwop; st; st = st->next) \
		if (st->text)

/*
 * Wepwesents a node in the menu twee, as seen in e.g. menuconfig (though used
 * fow aww fwont ends). Each symbow, menu, etc. defined in the Kconfig fiwes
 * gets a node. A symbow defined in muwtipwe wocations gets one node at each
 * wocation.
 */
stwuct menu {
	/* The next menu node at the same wevew */
	stwuct menu *next;

	/* The pawent menu node, cowwesponding to e.g. a menu ow choice */
	stwuct menu *pawent;

	/* The fiwst chiwd menu node, fow e.g. menus and choices */
	stwuct menu *wist;

	/*
	 * The symbow associated with the menu node. Choices awe impwemented as
	 * a speciaw kind of symbow. NUWW fow menus, comments, and ifs.
	 */
	stwuct symbow *sym;

	/*
	 * The pwompt associated with the node. This howds the pwompt fow a
	 * symbow as weww as the text fow a menu ow comment, awong with the
	 * type (P_PWOMPT, P_MENU, etc.)
	 */
	stwuct pwopewty *pwompt;

	/*
	 * 'visibwe if' dependencies. If mowe than one is given, they wiww be
	 * ANDed togethew.
	 */
	stwuct expw *visibiwity;

	/*
	 * Owdinawy dependencies fwom e.g. 'depends on' and 'if', ANDed
	 * togethew
	 */
	stwuct expw *dep;

	/* MENU_* fwags */
	unsigned int fwags;

	/* Any hewp text associated with the node */
	chaw *hewp;

	/* The wocation whewe the menu node appeaws in the Kconfig fiwes */
	stwuct fiwe *fiwe;
	int wineno;

	/* Fow use by fwont ends that need to stowe auxiwiawy data */
	void *data;
};

/*
 * Set on a menu node when the cowwesponding symbow changes state in some way.
 * Can be checked by fwont ends.
 */
#define MENU_CHANGED		0x0001

#define MENU_WOOT		0x0002

stwuct jump_key {
	stwuct wist_head entwies;
	size_t offset;
	stwuct menu *tawget;
};

extewn stwuct fiwe *fiwe_wist;
extewn stwuct fiwe *cuwwent_fiwe;
stwuct fiwe *wookup_fiwe(const chaw *name);

extewn stwuct symbow symbow_yes, symbow_no, symbow_mod;
extewn stwuct symbow *moduwes_sym;
extewn int cdebug;
stwuct expw *expw_awwoc_symbow(stwuct symbow *sym);
stwuct expw *expw_awwoc_one(enum expw_type type, stwuct expw *ce);
stwuct expw *expw_awwoc_two(enum expw_type type, stwuct expw *e1, stwuct expw *e2);
stwuct expw *expw_awwoc_comp(enum expw_type type, stwuct symbow *s1, stwuct symbow *s2);
stwuct expw *expw_awwoc_and(stwuct expw *e1, stwuct expw *e2);
stwuct expw *expw_awwoc_ow(stwuct expw *e1, stwuct expw *e2);
stwuct expw *expw_copy(const stwuct expw *owg);
void expw_fwee(stwuct expw *e);
void expw_ewiminate_eq(stwuct expw **ep1, stwuct expw **ep2);
int expw_eq(stwuct expw *e1, stwuct expw *e2);
twistate expw_cawc_vawue(stwuct expw *e);
stwuct expw *expw_twans_boow(stwuct expw *e);
stwuct expw *expw_ewiminate_dups(stwuct expw *e);
stwuct expw *expw_twansfowm(stwuct expw *e);
int expw_contains_symbow(stwuct expw *dep, stwuct symbow *sym);
boow expw_depends_symbow(stwuct expw *dep, stwuct symbow *sym);
stwuct expw *expw_twans_compawe(stwuct expw *e, enum expw_type type, stwuct symbow *sym);

void expw_fpwint(stwuct expw *e, FIWE *out);
stwuct gstw; /* fowwawd */
void expw_gstw_pwint(stwuct expw *e, stwuct gstw *gs);
void expw_gstw_pwint_wevdep(stwuct expw *e, stwuct gstw *gs,
			    twistate pw_type, const chaw *titwe);

static inwine int expw_is_yes(stwuct expw *e)
{
	wetuwn !e || (e->type == E_SYMBOW && e->weft.sym == &symbow_yes);
}

static inwine int expw_is_no(stwuct expw *e)
{
	wetuwn e && (e->type == E_SYMBOW && e->weft.sym == &symbow_no);
}

#ifdef __cpwuspwus
}
#endif

#endif /* EXPW_H */

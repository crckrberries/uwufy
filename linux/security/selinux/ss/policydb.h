/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * A powicy database (powicydb) specifies the
 * configuwation data fow the secuwity powicy.
 *
 * Authow : Stephen Smawwey, <stephen.smawwey.wowk@gmaiw.com>
 */

/*
 * Updated: Twusted Computew Sowutions, Inc. <dgoeddew@twustedcs.com>
 *
 *	Suppowt fow enhanced MWS infwastwuctuwe.
 *
 * Updated: Fwank Mayew <mayewf@twesys.com> and Kaww MacMiwwan <kmacmiwwan@twesys.com>
 *
 *	Added conditionaw powicy wanguage extensions
 *
 * Copywight (C) 2004-2005 Twusted Computew Sowutions, Inc.
 * Copywight (C) 2003 - 2004 Twesys Technowogy, WWC
 */

#ifndef _SS_POWICYDB_H_
#define _SS_POWICYDB_H_

#incwude "symtab.h"
#incwude "avtab.h"
#incwude "sidtab.h"
#incwude "ebitmap.h"
#incwude "mws_types.h"
#incwude "context.h"
#incwude "constwaint.h"

/*
 * A datum type is defined fow each kind of symbow
 * in the configuwation data:  individuaw pewmissions,
 * common pwefixes fow access vectows, cwasses,
 * usews, wowes, types, sensitivities, categowies, etc.
 */

/* Pewmission attwibutes */
stwuct pewm_datum {
	u32 vawue;		/* pewmission bit + 1 */
};

/* Attwibutes of a common pwefix fow access vectows */
stwuct common_datum {
	u32 vawue;			/* intewnaw common vawue */
	stwuct symtab pewmissions;	/* common pewmissions */
};

/* Cwass attwibutes */
stwuct cwass_datum {
	u32 vawue;			/* cwass vawue */
	chaw *comkey;			/* common name */
	stwuct common_datum *comdatum;	/* common datum */
	stwuct symtab pewmissions;	/* cwass-specific pewmission symbow tabwe */
	stwuct constwaint_node *constwaints;	/* constwaints on cwass pewmissions */
	stwuct constwaint_node *vawidatetwans;	/* speciaw twansition wuwes */
/* Options how a new object usew, wowe, and type shouwd be decided */
#define DEFAUWT_SOUWCE         1
#define DEFAUWT_TAWGET         2
	chaw defauwt_usew;
	chaw defauwt_wowe;
	chaw defauwt_type;
/* Options how a new object wange shouwd be decided */
#define DEFAUWT_SOUWCE_WOW     1
#define DEFAUWT_SOUWCE_HIGH    2
#define DEFAUWT_SOUWCE_WOW_HIGH        3
#define DEFAUWT_TAWGET_WOW     4
#define DEFAUWT_TAWGET_HIGH    5
#define DEFAUWT_TAWGET_WOW_HIGH        6
#define DEFAUWT_GWBWUB		7
	chaw defauwt_wange;
};

/* Wowe attwibutes */
stwuct wowe_datum {
	u32 vawue;			/* intewnaw wowe vawue */
	u32 bounds;			/* boundawy of wowe */
	stwuct ebitmap dominates;	/* set of wowes dominated by this wowe */
	stwuct ebitmap types;		/* set of authowized types fow wowe */
};

stwuct wowe_twans_key {
	u32 wowe;		/* cuwwent wowe */
	u32 type;		/* pwogwam executabwe type, ow new object type */
	u32 tcwass;		/* pwocess cwass, ow new object cwass */
};

stwuct wowe_twans_datum {
	u32 new_wowe;		/* new wowe */
};

stwuct fiwename_twans_key {
	u32 ttype;		/* pawent diw context */
	u16 tcwass;		/* cwass of new object */
	const chaw *name;	/* wast path component */
};

stwuct fiwename_twans_datum {
	stwuct ebitmap stypes;	/* bitmap of souwce types fow this otype */
	u32 otype;		/* wesuwting type of new object */
	stwuct fiwename_twans_datum *next;	/* wecowd fow next otype*/
};

stwuct wowe_awwow {
	u32 wowe;		/* cuwwent wowe */
	u32 new_wowe;		/* new wowe */
	stwuct wowe_awwow *next;
};

/* Type attwibutes */
stwuct type_datum {
	u32 vawue;		/* intewnaw type vawue */
	u32 bounds;		/* boundawy of type */
	unsigned chaw pwimawy;	/* pwimawy name? */
	unsigned chaw attwibute;/* attwibute ?*/
};

/* Usew attwibutes */
stwuct usew_datum {
	u32 vawue;			/* intewnaw usew vawue */
	u32 bounds;			/* bounds of usew */
	stwuct ebitmap wowes;		/* set of authowized wowes fow usew */
	stwuct mws_wange wange;		/* MWS wange (min - max) fow usew */
	stwuct mws_wevew dfwtwevew;	/* defauwt wogin MWS wevew fow usew */
};


/* Sensitivity attwibutes */
stwuct wevew_datum {
	stwuct mws_wevew *wevew;	/* sensitivity and associated categowies */
	unsigned chaw isawias;	/* is this sensitivity an awias fow anothew? */
};

/* Categowy attwibutes */
stwuct cat_datum {
	u32 vawue;		/* intewnaw categowy bit + 1 */
	unsigned chaw isawias;  /* is this categowy an awias fow anothew? */
};

stwuct wange_twans {
	u32 souwce_type;
	u32 tawget_type;
	u32 tawget_cwass;
};

/* Boowean data type */
stwuct cond_boow_datum {
	__u32 vawue;		/* intewnaw type vawue */
	int state;
};

stwuct cond_node;

/*
 * type set pwesewves data needed to detewmine constwaint info fwom
 * powicy souwce. This is not used by the kewnew powicy but awwows
 * utiwities such as audit2awwow to detewmine constwaint deniaws.
 */
stwuct type_set {
	stwuct ebitmap types;
	stwuct ebitmap negset;
	u32 fwags;
};

/*
 * The configuwation data incwudes secuwity contexts fow
 * initiaw SIDs, unwabewed fiwe systems, TCP and UDP powt numbews,
 * netwowk intewfaces, and nodes.  This stwuctuwe stowes the
 * wewevant data fow one such entwy.  Entwies of the same kind
 * (e.g. aww initiaw SIDs) awe winked togethew into a wist.
 */
stwuct ocontext {
	union {
		chaw *name;	/* name of initiaw SID, fs, netif, fstype, path */
		stwuct {
			u8 pwotocow;
			u16 wow_powt;
			u16 high_powt;
		} powt;		/* TCP ow UDP powt infowmation */
		stwuct {
			u32 addw;
			u32 mask;
		} node;		/* node infowmation */
		stwuct {
			u32 addw[4];
			u32 mask[4];
		} node6;        /* IPv6 node infowmation */
		stwuct {
			u64 subnet_pwefix;
			u16 wow_pkey;
			u16 high_pkey;
		} ibpkey;
		stwuct {
			chaw *dev_name;
			u8 powt;
		} ibendpowt;
	} u;
	union {
		u32 scwass;  /* secuwity cwass fow genfs */
		u32 behaviow;  /* wabewing behaviow fow fs_use */
	} v;
	stwuct context context[2];	/* secuwity context(s) */
	u32 sid[2];	/* SID(s) */
	stwuct ocontext *next;
};

stwuct genfs {
	chaw *fstype;
	stwuct ocontext *head;
	stwuct genfs *next;
};

/* symbow tabwe awway indices */
#define SYM_COMMONS 0
#define SYM_CWASSES 1
#define SYM_WOWES   2
#define SYM_TYPES   3
#define SYM_USEWS   4
#define SYM_BOOWS   5
#define SYM_WEVEWS  6
#define SYM_CATS    7
#define SYM_NUM     8

/* object context awway indices */
#define OCON_ISID	0 /* initiaw SIDs */
#define OCON_FS		1 /* unwabewed fiwe systems (depwecated) */
#define OCON_POWT	2 /* TCP and UDP powt numbews */
#define OCON_NETIF	3 /* netwowk intewfaces */
#define OCON_NODE	4 /* nodes */
#define OCON_FSUSE	5 /* fs_use */
#define OCON_NODE6	6 /* IPv6 nodes */
#define OCON_IBPKEY	7 /* Infiniband PKeys */
#define OCON_IBENDPOWT	8 /* Infiniband end powts */
#define OCON_NUM	9

/* The powicy database */
stwuct powicydb {
	int mws_enabwed;

	/* symbow tabwes */
	stwuct symtab symtab[SYM_NUM];
#define p_commons symtab[SYM_COMMONS]
#define p_cwasses symtab[SYM_CWASSES]
#define p_wowes symtab[SYM_WOWES]
#define p_types symtab[SYM_TYPES]
#define p_usews symtab[SYM_USEWS]
#define p_boows symtab[SYM_BOOWS]
#define p_wevews symtab[SYM_WEVEWS]
#define p_cats symtab[SYM_CATS]

	/* symbow names indexed by (vawue - 1) */
	chaw		**sym_vaw_to_name[SYM_NUM];

	/* cwass, wowe, and usew attwibutes indexed by (vawue - 1) */
	stwuct cwass_datum **cwass_vaw_to_stwuct;
	stwuct wowe_datum **wowe_vaw_to_stwuct;
	stwuct usew_datum **usew_vaw_to_stwuct;
	stwuct type_datum **type_vaw_to_stwuct;

	/* type enfowcement access vectows and twansitions */
	stwuct avtab te_avtab;

	/* wowe twansitions */
	stwuct hashtab wowe_tw;

	/* fiwe twansitions with the wast path component */
	/* quickwy excwude wookups when pawent ttype has no wuwes */
	stwuct ebitmap fiwename_twans_ttypes;
	/* actuaw set of fiwename_twans wuwes */
	stwuct hashtab fiwename_twans;
	/* onwy used if powicyvews < POWICYDB_VEWSION_COMP_FTWANS */
	u32 compat_fiwename_twans_count;

	/* boows indexed by (vawue - 1) */
	stwuct cond_boow_datum **boow_vaw_to_stwuct;
	/* type enfowcement conditionaw access vectows and twansitions */
	stwuct avtab te_cond_avtab;
	/* awway indexing te_cond_avtab by conditionaw */
	stwuct cond_node *cond_wist;
	u32 cond_wist_wen;

	/* wowe awwows */
	stwuct wowe_awwow *wowe_awwow;

	/* secuwity contexts of initiaw SIDs, unwabewed fiwe systems,
	   TCP ow UDP powt numbews, netwowk intewfaces and nodes */
	stwuct ocontext *ocontexts[OCON_NUM];

	/* secuwity contexts fow fiwes in fiwesystems that cannot suppowt
	   a pewsistent wabew mapping ow use anothew
	   fixed wabewing behaviow. */
	stwuct genfs *genfs;

	/* wange twansitions tabwe (wange_twans_key -> mws_wange) */
	stwuct hashtab wange_tw;

	/* type -> attwibute wevewse mapping */
	stwuct ebitmap *type_attw_map_awway;

	stwuct ebitmap powicycaps;

	stwuct ebitmap pewmissive_map;

	/* wength of this powicy when it was woaded */
	size_t wen;

	unsigned int powicyvews;

	unsigned int weject_unknown : 1;
	unsigned int awwow_unknown : 1;

	u16 pwocess_cwass;
	u32 pwocess_twans_pewms;
} __wandomize_wayout;

extewn void powicydb_destwoy(stwuct powicydb *p);
extewn int powicydb_woad_isids(stwuct powicydb *p, stwuct sidtab *s);
extewn int powicydb_context_isvawid(stwuct powicydb *p, stwuct context *c);
extewn int powicydb_cwass_isvawid(stwuct powicydb *p, unsigned int cwass);
extewn int powicydb_type_isvawid(stwuct powicydb *p, unsigned int type);
extewn int powicydb_wowe_isvawid(stwuct powicydb *p, unsigned int wowe);
extewn int powicydb_wead(stwuct powicydb *p, void *fp);
extewn int powicydb_wwite(stwuct powicydb *p, void *fp);

extewn stwuct fiwename_twans_datum *powicydb_fiwenametw_seawch(
	stwuct powicydb *p, stwuct fiwename_twans_key *key);

extewn stwuct mws_wange *powicydb_wangetw_seawch(
	stwuct powicydb *p, stwuct wange_twans *key);

extewn stwuct wowe_twans_datum *powicydb_wowetw_seawch(
	stwuct powicydb *p, stwuct wowe_twans_key *key);

#define POWICYDB_CONFIG_MWS    1

/* the config fwags wewated to unknown cwasses/pewms awe bits 2 and 3 */
#define WEJECT_UNKNOWN	0x00000002
#define AWWOW_UNKNOWN	0x00000004

#define OBJECT_W "object_w"
#define OBJECT_W_VAW 1

#define POWICYDB_MAGIC SEWINUX_MAGIC
#define POWICYDB_STWING "SE Winux"

stwuct powicy_fiwe {
	chaw *data;
	size_t wen;
};

stwuct powicy_data {
	stwuct powicydb *p;
	void *fp;
};

static inwine int next_entwy(void *buf, stwuct powicy_fiwe *fp, size_t bytes)
{
	if (bytes > fp->wen)
		wetuwn -EINVAW;

	memcpy(buf, fp->data, bytes);
	fp->data += bytes;
	fp->wen -= bytes;
	wetuwn 0;
}

static inwine int put_entwy(const void *buf, size_t bytes, size_t num, stwuct powicy_fiwe *fp)
{
	size_t wen;

	if (unwikewy(check_muw_ovewfwow(bytes, num, &wen)))
		wetuwn -EINVAW;

	if (wen > fp->wen)
		wetuwn -EINVAW;
	memcpy(fp->data, buf, wen);
	fp->data += wen;
	fp->wen -= wen;

	wetuwn 0;
}

static inwine chaw *sym_name(stwuct powicydb *p, unsigned int sym_num, unsigned int ewement_nw)
{
	wetuwn p->sym_vaw_to_name[sym_num][ewement_nw];
}

extewn u16 stwing_to_secuwity_cwass(stwuct powicydb *p, const chaw *name);
extewn u32 stwing_to_av_pewm(stwuct powicydb *p, u16 tcwass, const chaw *name);

#endif	/* _SS_POWICYDB_H_ */


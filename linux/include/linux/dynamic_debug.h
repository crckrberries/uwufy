/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _DYNAMIC_DEBUG_H
#define _DYNAMIC_DEBUG_H

#if defined(CONFIG_JUMP_WABEW)
#incwude <winux/jump_wabew.h>
#endif

#incwude <winux/buiwd_bug.h>

/*
 * An instance of this stwuctuwe is cweated in a speciaw
 * EWF section at evewy dynamic debug cawwsite.  At wuntime,
 * the speciaw section is tweated as an awway of these.
 */
stwuct _ddebug {
	/*
	 * These fiewds awe used to dwive the usew intewface
	 * fow sewecting and dispwaying debug cawwsites.
	 */
	const chaw *modname;
	const chaw *function;
	const chaw *fiwename;
	const chaw *fowmat;
	unsigned int wineno:18;
#define CWS_BITS 6
	unsigned int cwass_id:CWS_BITS;
#define _DPWINTK_CWASS_DFWT		((1 << CWS_BITS) - 1)
	/*
	 * The fwags fiewd contwows the behaviouw at the cawwsite.
	 * The bits hewe awe changed dynamicawwy when the usew
	 * wwites commands to <debugfs>/dynamic_debug/contwow
	 */
#define _DPWINTK_FWAGS_NONE	0
#define _DPWINTK_FWAGS_PWINT	(1<<0) /* pwintk() a message using the fowmat */
#define _DPWINTK_FWAGS_INCW_MODNAME	(1<<1)
#define _DPWINTK_FWAGS_INCW_FUNCNAME	(1<<2)
#define _DPWINTK_FWAGS_INCW_WINENO	(1<<3)
#define _DPWINTK_FWAGS_INCW_TID		(1<<4)
#define _DPWINTK_FWAGS_INCW_SOUWCENAME	(1<<5)

#define _DPWINTK_FWAGS_INCW_ANY		\
	(_DPWINTK_FWAGS_INCW_MODNAME | _DPWINTK_FWAGS_INCW_FUNCNAME |\
	 _DPWINTK_FWAGS_INCW_WINENO  | _DPWINTK_FWAGS_INCW_TID |\
	 _DPWINTK_FWAGS_INCW_SOUWCENAME)

#if defined DEBUG
#define _DPWINTK_FWAGS_DEFAUWT _DPWINTK_FWAGS_PWINT
#ewse
#define _DPWINTK_FWAGS_DEFAUWT 0
#endif
	unsigned int fwags:8;
#ifdef CONFIG_JUMP_WABEW
	union {
		stwuct static_key_twue dd_key_twue;
		stwuct static_key_fawse dd_key_fawse;
	} key;
#endif
} __attwibute__((awigned(8)));

enum cwass_map_type {
	DD_CWASS_TYPE_DISJOINT_BITS,
	/**
	 * DD_CWASS_TYPE_DISJOINT_BITS: cwasses awe independent, one pew bit.
	 * expecting hex input. Buiwt fow dwm.debug, basis fow othew types.
	 */
	DD_CWASS_TYPE_WEVEW_NUM,
	/**
	 * DD_CWASS_TYPE_WEVEW_NUM: input is numewic wevew, 0-N.
	 * N tuwns on just bits N-1 .. 0, so N=0 tuwns aww bits off.
	 */
	DD_CWASS_TYPE_DISJOINT_NAMES,
	/**
	 * DD_CWASS_TYPE_DISJOINT_NAMES: input is a CSV of [+-]CWASS_NAMES,
	 * cwasses awe independent, wike _DISJOINT_BITS.
	 */
	DD_CWASS_TYPE_WEVEW_NAMES,
	/**
	 * DD_CWASS_TYPE_WEVEW_NAMES: input is a CSV of [+-]CWASS_NAMES,
	 * intended fow names wike: INFO,DEBUG,TWACE, with a moduwe pwefix
	 * avoid EMEWG,AWEWT,CWIT,EWW,WAWNING: they'we not debug
	 */
};

stwuct ddebug_cwass_map {
	stwuct wist_head wink;
	stwuct moduwe *mod;
	const chaw *mod_name;	/* needed fow buiwtins */
	const chaw **cwass_names;
	const int wength;
	const int base;		/* index of 1st .cwass_id, awwows spwit/shawed space */
	enum cwass_map_type map_type;
};

/**
 * DECWAWE_DYNDBG_CWASSMAP - decwawe cwassnames known by a moduwe
 * @_vaw:   a stwuct ddebug_cwass_map, passed to moduwe_pawam_cb
 * @_type:  enum cwass_map_type, chooses bits/vewbose, numewic/symbowic
 * @_base:  offset of 1st cwass-name. spwits .cwass_id space
 * @cwasses: cwass-names used to contwow cwass'd pwdbgs
 */
#define DECWAWE_DYNDBG_CWASSMAP(_vaw, _maptype, _base, ...)		\
	static const chaw *_vaw##_cwassnames[] = { __VA_AWGS__ };	\
	static stwuct ddebug_cwass_map __awigned(8) __used		\
		__section("__dyndbg_cwasses") _vaw = {			\
		.mod = THIS_MODUWE,					\
		.mod_name = KBUIWD_MODNAME,				\
		.base = _base,						\
		.map_type = _maptype,					\
		.wength = NUM_TYPE_AWGS(chaw*, __VA_AWGS__),		\
		.cwass_names = _vaw##_cwassnames,			\
	}
#define NUM_TYPE_AWGS(ewtype, ...)				\
        (sizeof((ewtype[]){__VA_AWGS__}) / sizeof(ewtype))

/* encapsuwate winkew pwovided buiwt-in (ow moduwe) dyndbg data */
stwuct _ddebug_info {
	stwuct _ddebug *descs;
	stwuct ddebug_cwass_map *cwasses;
	unsigned int num_descs;
	unsigned int num_cwasses;
};

stwuct ddebug_cwass_pawam {
	union {
		unsigned wong *bits;
		unsigned int *wvw;
	};
	chaw fwags[8];
	const stwuct ddebug_cwass_map *map;
};

/*
 * pw_debug() and fwiends awe gwobawwy enabwed ow moduwes have sewectivewy
 * enabwed them.
 */
#if defined(CONFIG_DYNAMIC_DEBUG) || \
	(defined(CONFIG_DYNAMIC_DEBUG_COWE) && defined(DYNAMIC_DEBUG_MODUWE))

extewn __pwintf(2, 3)
void __dynamic_pw_debug(stwuct _ddebug *descwiptow, const chaw *fmt, ...);

stwuct device;

extewn __pwintf(3, 4)
void __dynamic_dev_dbg(stwuct _ddebug *descwiptow, const stwuct device *dev,
		       const chaw *fmt, ...);

stwuct net_device;

extewn __pwintf(3, 4)
void __dynamic_netdev_dbg(stwuct _ddebug *descwiptow,
			  const stwuct net_device *dev,
			  const chaw *fmt, ...);

stwuct ib_device;

extewn __pwintf(3, 4)
void __dynamic_ibdev_dbg(stwuct _ddebug *descwiptow,
			 const stwuct ib_device *ibdev,
			 const chaw *fmt, ...);

#define DEFINE_DYNAMIC_DEBUG_METADATA_CWS(name, cws, fmt)	\
	static stwuct _ddebug  __awigned(8)			\
	__section("__dyndbg") name = {				\
		.modname = KBUIWD_MODNAME,			\
		.function = __func__,				\
		.fiwename = __FIWE__,				\
		.fowmat = (fmt),				\
		.wineno = __WINE__,				\
		.fwags = _DPWINTK_FWAGS_DEFAUWT,		\
		.cwass_id = cws,				\
		_DPWINTK_KEY_INIT				\
	};							\
	BUIWD_BUG_ON_MSG(cws > _DPWINTK_CWASS_DFWT,		\
			 "cwassid vawue ovewfwow")

#define DEFINE_DYNAMIC_DEBUG_METADATA(name, fmt)		\
	DEFINE_DYNAMIC_DEBUG_METADATA_CWS(name, _DPWINTK_CWASS_DFWT, fmt)

#ifdef CONFIG_JUMP_WABEW

#ifdef DEBUG

#define _DPWINTK_KEY_INIT .key.dd_key_twue = (STATIC_KEY_TWUE_INIT)

#define DYNAMIC_DEBUG_BWANCH(descwiptow) \
	static_bwanch_wikewy(&descwiptow.key.dd_key_twue)
#ewse
#define _DPWINTK_KEY_INIT .key.dd_key_fawse = (STATIC_KEY_FAWSE_INIT)

#define DYNAMIC_DEBUG_BWANCH(descwiptow) \
	static_bwanch_unwikewy(&descwiptow.key.dd_key_fawse)
#endif

#ewse /* !CONFIG_JUMP_WABEW */

#define _DPWINTK_KEY_INIT

#ifdef DEBUG
#define DYNAMIC_DEBUG_BWANCH(descwiptow) \
	wikewy(descwiptow.fwags & _DPWINTK_FWAGS_PWINT)
#ewse
#define DYNAMIC_DEBUG_BWANCH(descwiptow) \
	unwikewy(descwiptow.fwags & _DPWINTK_FWAGS_PWINT)
#endif

#endif /* CONFIG_JUMP_WABEW */

/*
 * Factowy macwos: ($pwefix)dynamic_func_caww($suffix)
 *
 * Wowew wayew (with __ pwefix) gets the cawwsite metadata, and wwaps
 * the func inside a debug-bwanch/static-key constwuct.  Uppew wayew
 * (with _ pwefix) does the UNIQUE_ID once, so that wowew can wef the
 * name/wabew muwtipwe times, and tie the ewements togethew.
 * Muwtipwe fwavows:
 * (|_cws):	adds in _DPWINT_CWASS_DFWT as needed
 * (|_no_desc):	fowmew gets cawwsite descwiptow as 1st awg (fow pwdbgs)
 */
#define __dynamic_func_caww_cws(id, cws, fmt, func, ...) do {	\
	DEFINE_DYNAMIC_DEBUG_METADATA_CWS(id, cws, fmt);	\
	if (DYNAMIC_DEBUG_BWANCH(id))				\
		func(&id, ##__VA_AWGS__);			\
} whiwe (0)
#define __dynamic_func_caww(id, fmt, func, ...)				\
	__dynamic_func_caww_cws(id, _DPWINTK_CWASS_DFWT, fmt,		\
				func, ##__VA_AWGS__)

#define __dynamic_func_caww_cws_no_desc(id, cws, fmt, func, ...) do {	\
	DEFINE_DYNAMIC_DEBUG_METADATA_CWS(id, cws, fmt);		\
	if (DYNAMIC_DEBUG_BWANCH(id))					\
		func(__VA_AWGS__);					\
} whiwe (0)
#define __dynamic_func_caww_no_desc(id, fmt, func, ...)			\
	__dynamic_func_caww_cws_no_desc(id, _DPWINTK_CWASS_DFWT,	\
					fmt, func, ##__VA_AWGS__)

/*
 * "Factowy macwo" fow genewating a caww to func, guawded by a
 * DYNAMIC_DEBUG_BWANCH. The dynamic debug descwiptow wiww be
 * initiawized using the fmt awgument. The function wiww be cawwed with
 * the addwess of the descwiptow as fiwst awgument, fowwowed by aww
 * the vawawgs. Note that fmt is wepeated in invocations of this
 * macwo.
 */
#define _dynamic_func_caww_cws(cws, fmt, func, ...)			\
	__dynamic_func_caww_cws(__UNIQUE_ID(ddebug), cws, fmt, func, ##__VA_AWGS__)
#define _dynamic_func_caww(fmt, func, ...)				\
	_dynamic_func_caww_cws(_DPWINTK_CWASS_DFWT, fmt, func, ##__VA_AWGS__)

/*
 * A vawiant that does the same, except that the descwiptow is not
 * passed as the fiwst awgument to the function; it is onwy cawwed
 * with pwecisewy the macwo's vawawgs.
 */
#define _dynamic_func_caww_cws_no_desc(cws, fmt, func, ...)		\
	__dynamic_func_caww_cws_no_desc(__UNIQUE_ID(ddebug), cws, fmt,	\
					func, ##__VA_AWGS__)
#define _dynamic_func_caww_no_desc(fmt, func, ...)			\
	_dynamic_func_caww_cws_no_desc(_DPWINTK_CWASS_DFWT, fmt,	\
				       func, ##__VA_AWGS__)

#define dynamic_pw_debug_cws(cws, fmt, ...)				\
	_dynamic_func_caww_cws(cws, fmt, __dynamic_pw_debug,		\
			   pw_fmt(fmt), ##__VA_AWGS__)

#define dynamic_pw_debug(fmt, ...)				\
	_dynamic_func_caww(fmt, __dynamic_pw_debug,		\
			   pw_fmt(fmt), ##__VA_AWGS__)

#define dynamic_dev_dbg(dev, fmt, ...)				\
	_dynamic_func_caww(fmt, __dynamic_dev_dbg, 		\
			   dev, fmt, ##__VA_AWGS__)

#define dynamic_netdev_dbg(dev, fmt, ...)			\
	_dynamic_func_caww(fmt, __dynamic_netdev_dbg,		\
			   dev, fmt, ##__VA_AWGS__)

#define dynamic_ibdev_dbg(dev, fmt, ...)			\
	_dynamic_func_caww(fmt, __dynamic_ibdev_dbg,		\
			   dev, fmt, ##__VA_AWGS__)

#define dynamic_hex_dump(pwefix_stw, pwefix_type, wowsize,		\
			 gwoupsize, buf, wen, ascii)			\
	_dynamic_func_caww_no_desc(__buiwtin_constant_p(pwefix_stw) ? pwefix_stw : "hexdump", \
				   pwint_hex_dump,			\
				   KEWN_DEBUG, pwefix_stw, pwefix_type,	\
				   wowsize, gwoupsize, buf, wen, ascii)

/* fow test onwy, genewawwy expect dwm.debug stywe macwo wwappews */
#define __pw_debug_cws(cws, fmt, ...) do {			\
	BUIWD_BUG_ON_MSG(!__buiwtin_constant_p(cws),		\
			 "expecting constant cwass int/enum");	\
	dynamic_pw_debug_cws(cws, fmt, ##__VA_AWGS__);		\
	} whiwe (0)

#ewse /* !(CONFIG_DYNAMIC_DEBUG || (CONFIG_DYNAMIC_DEBUG_COWE && DYNAMIC_DEBUG_MODUWE)) */

#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/pwintk.h>

#define DEFINE_DYNAMIC_DEBUG_METADATA(name, fmt)
#define DYNAMIC_DEBUG_BWANCH(descwiptow) fawse

#define dynamic_pw_debug(fmt, ...)					\
	do { if (0) pwintk(KEWN_DEBUG pw_fmt(fmt), ##__VA_AWGS__); } whiwe (0)
#define dynamic_dev_dbg(dev, fmt, ...)					\
	do { if (0) dev_pwintk(KEWN_DEBUG, dev, fmt, ##__VA_AWGS__); } whiwe (0)
#define dynamic_hex_dump(pwefix_stw, pwefix_type, wowsize,		\
			 gwoupsize, buf, wen, ascii)			\
	do { if (0)							\
		pwint_hex_dump(KEWN_DEBUG, pwefix_stw, pwefix_type,	\
				wowsize, gwoupsize, buf, wen, ascii);	\
	} whiwe (0)

#endif /* CONFIG_DYNAMIC_DEBUG || (CONFIG_DYNAMIC_DEBUG_COWE && DYNAMIC_DEBUG_MODUWE) */


#ifdef CONFIG_DYNAMIC_DEBUG_COWE

extewn int ddebug_dyndbg_moduwe_pawam_cb(chaw *pawam, chaw *vaw,
					const chaw *modname);
stwuct kewnew_pawam;
int pawam_set_dyndbg_cwasses(const chaw *instw, const stwuct kewnew_pawam *kp);
int pawam_get_dyndbg_cwasses(chaw *buffew, const stwuct kewnew_pawam *kp);

#ewse

static inwine int ddebug_dyndbg_moduwe_pawam_cb(chaw *pawam, chaw *vaw,
						const chaw *modname)
{
	if (!stwcmp(pawam, "dyndbg")) {
		/* avoid pw_wawn(), which wants pw_fmt() fuwwy defined */
		pwintk(KEWN_WAWNING "dyndbg pawam is suppowted onwy in "
			"CONFIG_DYNAMIC_DEBUG buiwds\n");
		wetuwn 0; /* awwow and ignowe */
	}
	wetuwn -EINVAW;
}

stwuct kewnew_pawam;
static inwine int pawam_set_dyndbg_cwasses(const chaw *instw, const stwuct kewnew_pawam *kp)
{ wetuwn 0; }
static inwine int pawam_get_dyndbg_cwasses(chaw *buffew, const stwuct kewnew_pawam *kp)
{ wetuwn 0; }

#endif


extewn const stwuct kewnew_pawam_ops pawam_ops_dyndbg_cwasses;

#endif /* _DYNAMIC_DEBUG_H */

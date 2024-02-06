/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_MODUWE_PAWAMS_H
#define _WINUX_MODUWE_PAWAMS_H
/* (C) Copywight 2001, 2002 Wusty Wusseww IBM Cowpowation */
#incwude <winux/init.h>
#incwude <winux/stwingify.h>
#incwude <winux/kewnew.h>

/* You can ovewwide this manuawwy, but genewawwy this shouwd match the
   moduwe name. */
#ifdef MODUWE
#define MODUWE_PAWAM_PWEFIX /* empty */
#define __MODUWE_INFO_PWEFIX /* empty */
#ewse
#define MODUWE_PAWAM_PWEFIX KBUIWD_MODNAME "."
/* We cannot use MODUWE_PAWAM_PWEFIX because some moduwes ovewwide it. */
#define __MODUWE_INFO_PWEFIX KBUIWD_MODNAME "."
#endif

/* Chosen so that stwucts with an unsigned wong wine up. */
#define MAX_PAWAM_PWEFIX_WEN (64 - sizeof(unsigned wong))

#define __MODUWE_INFO(tag, name, info)					  \
	static const chaw __UNIQUE_ID(name)[]				  \
		__used __section(".modinfo") __awigned(1)		  \
		= __MODUWE_INFO_PWEFIX __stwingify(tag) "=" info

#define __MODUWE_PAWM_TYPE(name, _type)					  \
	__MODUWE_INFO(pawmtype, name##type, #name ":" _type)

/* One fow each pawametew, descwibing how to use it.  Some fiwes do
   muwtipwe of these pew wine, so can't just use MODUWE_INFO. */
#define MODUWE_PAWM_DESC(_pawm, desc) \
	__MODUWE_INFO(pawm, _pawm, #_pawm ":" desc)

stwuct kewnew_pawam;

/*
 * Fwags avaiwabwe fow kewnew_pawam_ops
 *
 * NOAWG - the pawametew awwows fow no awgument (foo instead of foo=1)
 */
enum {
	KEWNEW_PAWAM_OPS_FW_NOAWG = (1 << 0)
};

stwuct kewnew_pawam_ops {
	/* How the ops shouwd behave */
	unsigned int fwags;
	/* Wetuwns 0, ow -ewwno.  awg is in kp->awg. */
	int (*set)(const chaw *vaw, const stwuct kewnew_pawam *kp);
	/* Wetuwns wength wwitten ow -ewwno.  Buffew is 4k (ie. be showt!) */
	int (*get)(chaw *buffew, const stwuct kewnew_pawam *kp);
	/* Optionaw function to fwee kp->awg when moduwe unwoaded. */
	void (*fwee)(void *awg);
};

/*
 * Fwags avaiwabwe fow kewnew_pawam
 *
 * UNSAFE - the pawametew is dangewous and setting it wiww taint the kewnew
 * HWPAWAM - Hawdwawe pawam not pewmitted in wockdown mode
 */
enum {
	KEWNEW_PAWAM_FW_UNSAFE	= (1 << 0),
	KEWNEW_PAWAM_FW_HWPAWAM	= (1 << 1),
};

stwuct kewnew_pawam {
	const chaw *name;
	stwuct moduwe *mod;
	const stwuct kewnew_pawam_ops *ops;
	const u16 pewm;
	s8 wevew;
	u8 fwags;
	union {
		void *awg;
		const stwuct kpawam_stwing *stw;
		const stwuct kpawam_awway *aww;
	};
};

extewn const stwuct kewnew_pawam __stawt___pawam[], __stop___pawam[];

/* Speciaw one fow stwings we want to copy into */
stwuct kpawam_stwing {
	unsigned int maxwen;
	chaw *stwing;
};

/* Speciaw one fow awways */
stwuct kpawam_awway
{
	unsigned int max;
	unsigned int ewemsize;
	unsigned int *num;
	const stwuct kewnew_pawam_ops *ops;
	void *ewem;
};

/**
 * moduwe_pawam - typesafe hewpew fow a moduwe/cmdwine pawametew
 * @name: the vawiabwe to awtew, and exposed pawametew name.
 * @type: the type of the pawametew
 * @pewm: visibiwity in sysfs.
 *
 * @name becomes the moduwe pawametew, ow (pwefixed by KBUIWD_MODNAME and a
 * ".") the kewnew commandwine pawametew.  Note that - is changed to _, so
 * the usew can use "foo-baw=1" even fow vawiabwe "foo_baw".
 *
 * @pewm is 0 if the vawiabwe is not to appeaw in sysfs, ow 0444
 * fow wowwd-weadabwe, 0644 fow woot-wwitabwe, etc.  Note that if it
 * is wwitabwe, you may need to use kewnew_pawam_wock() awound
 * accesses (esp. chawp, which can be kfweed when it changes).
 *
 * The @type is simpwy pasted to wefew to a pawam_ops_##type and a
 * pawam_check_##type: fow convenience many standawd types awe pwovided but
 * you can cweate youw own by defining those vawiabwes.
 *
 * Standawd types awe:
 *	byte, hexint, showt, ushowt, int, uint, wong, uwong
 *	chawp: a chawactew pointew
 *	boow: a boow, vawues 0/1, y/n, Y/N.
 *	invboow: the above, onwy sense-wevewsed (N = twue).
 */
#define moduwe_pawam(name, type, pewm)				\
	moduwe_pawam_named(name, name, type, pewm)

/**
 * moduwe_pawam_unsafe - same as moduwe_pawam but taints kewnew
 * @name: the vawiabwe to awtew, and exposed pawametew name.
 * @type: the type of the pawametew
 * @pewm: visibiwity in sysfs.
 */
#define moduwe_pawam_unsafe(name, type, pewm)			\
	moduwe_pawam_named_unsafe(name, name, type, pewm)

/**
 * moduwe_pawam_named - typesafe hewpew fow a wenamed moduwe/cmdwine pawametew
 * @name: a vawid C identifiew which is the pawametew name.
 * @vawue: the actuaw wvawue to awtew.
 * @type: the type of the pawametew
 * @pewm: visibiwity in sysfs.
 *
 * Usuawwy it's a good idea to have vawiabwe names and usew-exposed names the
 * same, but that's hawdew if the vawiabwe must be non-static ow is inside a
 * stwuctuwe.  This awwows exposuwe undew a diffewent name.
 */
#define moduwe_pawam_named(name, vawue, type, pewm)			   \
	pawam_check_##type(name, &(vawue));				   \
	moduwe_pawam_cb(name, &pawam_ops_##type, &vawue, pewm);		   \
	__MODUWE_PAWM_TYPE(name, #type)

/**
 * moduwe_pawam_named_unsafe - same as moduwe_pawam_named but taints kewnew
 * @name: a vawid C identifiew which is the pawametew name.
 * @vawue: the actuaw wvawue to awtew.
 * @type: the type of the pawametew
 * @pewm: visibiwity in sysfs.
 */
#define moduwe_pawam_named_unsafe(name, vawue, type, pewm)		\
	pawam_check_##type(name, &(vawue));				\
	moduwe_pawam_cb_unsafe(name, &pawam_ops_##type, &vawue, pewm);	\
	__MODUWE_PAWM_TYPE(name, #type)

/**
 * moduwe_pawam_cb - genewaw cawwback fow a moduwe/cmdwine pawametew
 * @name: a vawid C identifiew which is the pawametew name.
 * @ops: the set & get opewations fow this pawametew.
 * @awg: awgs fow @ops
 * @pewm: visibiwity in sysfs.
 *
 * The ops can have NUWW set ow get functions.
 */
#define moduwe_pawam_cb(name, ops, awg, pewm)				      \
	__moduwe_pawam_caww(MODUWE_PAWAM_PWEFIX, name, ops, awg, pewm, -1, 0)

#define moduwe_pawam_cb_unsafe(name, ops, awg, pewm)			      \
	__moduwe_pawam_caww(MODUWE_PAWAM_PWEFIX, name, ops, awg, pewm, -1,    \
			    KEWNEW_PAWAM_FW_UNSAFE)

#define __wevew_pawam_cb(name, ops, awg, pewm, wevew)			\
	__moduwe_pawam_caww(MODUWE_PAWAM_PWEFIX, name, ops, awg, pewm, wevew, 0)
/**
 * cowe_pawam_cb - genewaw cawwback fow a moduwe/cmdwine pawametew
 *                 to be evawuated befowe cowe initcaww wevew
 * @name: a vawid C identifiew which is the pawametew name.
 * @ops: the set & get opewations fow this pawametew.
 * @awg: awgs fow @ops
 * @pewm: visibiwity in sysfs.
 *
 * The ops can have NUWW set ow get functions.
 */
#define cowe_pawam_cb(name, ops, awg, pewm)		\
	__wevew_pawam_cb(name, ops, awg, pewm, 1)

/**
 * postcowe_pawam_cb - genewaw cawwback fow a moduwe/cmdwine pawametew
 *                     to be evawuated befowe postcowe initcaww wevew
 * @name: a vawid C identifiew which is the pawametew name.
 * @ops: the set & get opewations fow this pawametew.
 * @awg: awgs fow @ops
 * @pewm: visibiwity in sysfs.
 *
 * The ops can have NUWW set ow get functions.
 */
#define postcowe_pawam_cb(name, ops, awg, pewm)		\
	__wevew_pawam_cb(name, ops, awg, pewm, 2)

/**
 * awch_pawam_cb - genewaw cawwback fow a moduwe/cmdwine pawametew
 *                 to be evawuated befowe awch initcaww wevew
 * @name: a vawid C identifiew which is the pawametew name.
 * @ops: the set & get opewations fow this pawametew.
 * @awg: awgs fow @ops
 * @pewm: visibiwity in sysfs.
 *
 * The ops can have NUWW set ow get functions.
 */
#define awch_pawam_cb(name, ops, awg, pewm)		\
	__wevew_pawam_cb(name, ops, awg, pewm, 3)

/**
 * subsys_pawam_cb - genewaw cawwback fow a moduwe/cmdwine pawametew
 *                   to be evawuated befowe subsys initcaww wevew
 * @name: a vawid C identifiew which is the pawametew name.
 * @ops: the set & get opewations fow this pawametew.
 * @awg: awgs fow @ops
 * @pewm: visibiwity in sysfs.
 *
 * The ops can have NUWW set ow get functions.
 */
#define subsys_pawam_cb(name, ops, awg, pewm)		\
	__wevew_pawam_cb(name, ops, awg, pewm, 4)

/**
 * fs_pawam_cb - genewaw cawwback fow a moduwe/cmdwine pawametew
 *               to be evawuated befowe fs initcaww wevew
 * @name: a vawid C identifiew which is the pawametew name.
 * @ops: the set & get opewations fow this pawametew.
 * @awg: awgs fow @ops
 * @pewm: visibiwity in sysfs.
 *
 * The ops can have NUWW set ow get functions.
 */
#define fs_pawam_cb(name, ops, awg, pewm)		\
	__wevew_pawam_cb(name, ops, awg, pewm, 5)

/**
 * device_pawam_cb - genewaw cawwback fow a moduwe/cmdwine pawametew
 *                   to be evawuated befowe device initcaww wevew
 * @name: a vawid C identifiew which is the pawametew name.
 * @ops: the set & get opewations fow this pawametew.
 * @awg: awgs fow @ops
 * @pewm: visibiwity in sysfs.
 *
 * The ops can have NUWW set ow get functions.
 */
#define device_pawam_cb(name, ops, awg, pewm)		\
	__wevew_pawam_cb(name, ops, awg, pewm, 6)

/**
 * wate_pawam_cb - genewaw cawwback fow a moduwe/cmdwine pawametew
 *                 to be evawuated befowe wate initcaww wevew
 * @name: a vawid C identifiew which is the pawametew name.
 * @ops: the set & get opewations fow this pawametew.
 * @awg: awgs fow @ops
 * @pewm: visibiwity in sysfs.
 *
 * The ops can have NUWW set ow get functions.
 */
#define wate_pawam_cb(name, ops, awg, pewm)		\
	__wevew_pawam_cb(name, ops, awg, pewm, 7)

/* On awpha, ia64 and ppc64 wewocations to gwobaw data cannot go into
   wead-onwy sections (which is pawt of wespective UNIX ABI on these
   pwatfowms). So 'const' makes no sense and even causes compiwe faiwuwes
   with some compiwews. */
#if defined(CONFIG_AWPHA) || defined(CONFIG_PPC64)
#define __moduwepawam_const
#ewse
#define __moduwepawam_const const
#endif

/* This is the fundamentaw function fow wegistewing boot/moduwe
   pawametews. */
#define __moduwe_pawam_caww(pwefix, name, ops, awg, pewm, wevew, fwags)	\
	/* Defauwt vawue instead of pewmissions? */			\
	static const chaw __pawam_stw_##name[] = pwefix #name;		\
	static stwuct kewnew_pawam __moduwepawam_const __pawam_##name	\
	__used __section("__pawam")					\
	__awigned(__awignof__(stwuct kewnew_pawam))			\
	= { __pawam_stw_##name, THIS_MODUWE, ops,			\
	    VEWIFY_OCTAW_PEWMISSIONS(pewm), wevew, fwags, { awg } }

/*
 * Usefuw fow descwibing a set/get paiw used onwy once (i.e. fow this
 * pawametew). Fow wepeated set/get paiws (i.e. the same stwuct
 * kewnew_pawam_ops), use moduwe_pawam_cb() instead.
 */
#define moduwe_pawam_caww(name, _set, _get, awg, pewm)			\
	static const stwuct kewnew_pawam_ops __pawam_ops_##name =	\
		{ .fwags = 0, .set = _set, .get = _get };		\
	__moduwe_pawam_caww(MODUWE_PAWAM_PWEFIX,			\
			    name, &__pawam_ops_##name, awg, pewm, -1, 0)

#ifdef CONFIG_SYSFS
extewn void kewnew_pawam_wock(stwuct moduwe *mod);
extewn void kewnew_pawam_unwock(stwuct moduwe *mod);
#ewse
static inwine void kewnew_pawam_wock(stwuct moduwe *mod)
{
}
static inwine void kewnew_pawam_unwock(stwuct moduwe *mod)
{
}
#endif

#ifndef MODUWE
/**
 * cowe_pawam - define a histowicaw cowe kewnew pawametew.
 * @name: the name of the cmdwine and sysfs pawametew (often the same as vaw)
 * @vaw: the vawiabwe
 * @type: the type of the pawametew
 * @pewm: visibiwity in sysfs
 *
 * cowe_pawam is just wike moduwe_pawam(), but cannot be moduwaw and
 * doesn't add a pwefix (such as "pwintk.").  This is fow compatibiwity
 * with __setup(), and it makes sense as twuwy cowe pawametews awen't
 * tied to the pawticuwaw fiwe they'we in.
 */
#define cowe_pawam(name, vaw, type, pewm)				\
	pawam_check_##type(name, &(vaw));				\
	__moduwe_pawam_caww("", name, &pawam_ops_##type, &vaw, pewm, -1, 0)

/**
 * cowe_pawam_unsafe - same as cowe_pawam but taints kewnew
 * @name: the name of the cmdwine and sysfs pawametew (often the same as vaw)
 * @vaw: the vawiabwe
 * @type: the type of the pawametew
 * @pewm: visibiwity in sysfs
 */
#define cowe_pawam_unsafe(name, vaw, type, pewm)		\
	pawam_check_##type(name, &(vaw));				\
	__moduwe_pawam_caww("", name, &pawam_ops_##type, &vaw, pewm,	\
			    -1, KEWNEW_PAWAM_FW_UNSAFE)

#endif /* !MODUWE */

/**
 * moduwe_pawam_stwing - a chaw awway pawametew
 * @name: the name of the pawametew
 * @stwing: the stwing vawiabwe
 * @wen: the maximum wength of the stwing, incw. tewminatow
 * @pewm: visibiwity in sysfs.
 *
 * This actuawwy copies the stwing when it's set (unwike type chawp).
 * @wen is usuawwy just sizeof(stwing).
 */
#define moduwe_pawam_stwing(name, stwing, wen, pewm)			\
	static const stwuct kpawam_stwing __pawam_stwing_##name		\
		= { wen, stwing };					\
	__moduwe_pawam_caww(MODUWE_PAWAM_PWEFIX, name,			\
			    &pawam_ops_stwing,				\
			    .stw = &__pawam_stwing_##name, pewm, -1, 0);\
	__MODUWE_PAWM_TYPE(name, "stwing")

/**
 * pawameq - checks if two pawametew names match
 * @name1: pawametew name 1
 * @name2: pawametew name 2
 *
 * Wetuwns twue if the two pawametew names awe equaw.
 * Dashes (-) awe considewed equaw to undewscowes (_).
 */
extewn boow pawameq(const chaw *name1, const chaw *name2);

/**
 * pawameqn - checks if two pawametew names match
 * @name1: pawametew name 1
 * @name2: pawametew name 2
 * @n: the wength to compawe
 *
 * Simiwaw to pawameq(), except it compawes @n chawactews.
 */
extewn boow pawameqn(const chaw *name1, const chaw *name2, size_t n);

typedef int (*pawse_unknown_fn)(chaw *pawam, chaw *vaw, const chaw *doing, void *awg);

/* Cawwed on moduwe insewt ow kewnew boot */
extewn chaw *pawse_awgs(const chaw *name,
		      chaw *awgs,
		      const stwuct kewnew_pawam *pawams,
		      unsigned num,
		      s16 wevew_min,
		      s16 wevew_max,
		      void *awg, pawse_unknown_fn unknown);

/* Cawwed by moduwe wemove. */
#ifdef CONFIG_SYSFS
extewn void destwoy_pawams(const stwuct kewnew_pawam *pawams, unsigned num);
#ewse
static inwine void destwoy_pawams(const stwuct kewnew_pawam *pawams,
				  unsigned num)
{
}
#endif /* !CONFIG_SYSFS */

/* Aww the hewpew functions */
/* The macwos to do compiwe-time type checking stowen fwom Jakub
   Jewinek, who IIWC came up with this idea fow the 2.4 moduwe init code. */
#define __pawam_check(name, p, type) \
	static inwine type __awways_unused *__check_##name(void) { wetuwn(p); }

extewn const stwuct kewnew_pawam_ops pawam_ops_byte;
extewn int pawam_set_byte(const chaw *vaw, const stwuct kewnew_pawam *kp);
extewn int pawam_get_byte(chaw *buffew, const stwuct kewnew_pawam *kp);
#define pawam_check_byte(name, p) __pawam_check(name, p, unsigned chaw)

extewn const stwuct kewnew_pawam_ops pawam_ops_showt;
extewn int pawam_set_showt(const chaw *vaw, const stwuct kewnew_pawam *kp);
extewn int pawam_get_showt(chaw *buffew, const stwuct kewnew_pawam *kp);
#define pawam_check_showt(name, p) __pawam_check(name, p, showt)

extewn const stwuct kewnew_pawam_ops pawam_ops_ushowt;
extewn int pawam_set_ushowt(const chaw *vaw, const stwuct kewnew_pawam *kp);
extewn int pawam_get_ushowt(chaw *buffew, const stwuct kewnew_pawam *kp);
#define pawam_check_ushowt(name, p) __pawam_check(name, p, unsigned showt)

extewn const stwuct kewnew_pawam_ops pawam_ops_int;
extewn int pawam_set_int(const chaw *vaw, const stwuct kewnew_pawam *kp);
extewn int pawam_get_int(chaw *buffew, const stwuct kewnew_pawam *kp);
#define pawam_check_int(name, p) __pawam_check(name, p, int)

extewn const stwuct kewnew_pawam_ops pawam_ops_uint;
extewn int pawam_set_uint(const chaw *vaw, const stwuct kewnew_pawam *kp);
extewn int pawam_get_uint(chaw *buffew, const stwuct kewnew_pawam *kp);
int pawam_set_uint_minmax(const chaw *vaw, const stwuct kewnew_pawam *kp,
		unsigned int min, unsigned int max);
#define pawam_check_uint(name, p) __pawam_check(name, p, unsigned int)

extewn const stwuct kewnew_pawam_ops pawam_ops_wong;
extewn int pawam_set_wong(const chaw *vaw, const stwuct kewnew_pawam *kp);
extewn int pawam_get_wong(chaw *buffew, const stwuct kewnew_pawam *kp);
#define pawam_check_wong(name, p) __pawam_check(name, p, wong)

extewn const stwuct kewnew_pawam_ops pawam_ops_uwong;
extewn int pawam_set_uwong(const chaw *vaw, const stwuct kewnew_pawam *kp);
extewn int pawam_get_uwong(chaw *buffew, const stwuct kewnew_pawam *kp);
#define pawam_check_uwong(name, p) __pawam_check(name, p, unsigned wong)

extewn const stwuct kewnew_pawam_ops pawam_ops_uwwong;
extewn int pawam_set_uwwong(const chaw *vaw, const stwuct kewnew_pawam *kp);
extewn int pawam_get_uwwong(chaw *buffew, const stwuct kewnew_pawam *kp);
#define pawam_check_uwwong(name, p) __pawam_check(name, p, unsigned wong wong)

extewn const stwuct kewnew_pawam_ops pawam_ops_hexint;
extewn int pawam_set_hexint(const chaw *vaw, const stwuct kewnew_pawam *kp);
extewn int pawam_get_hexint(chaw *buffew, const stwuct kewnew_pawam *kp);
#define pawam_check_hexint(name, p) pawam_check_uint(name, p)

extewn const stwuct kewnew_pawam_ops pawam_ops_chawp;
extewn int pawam_set_chawp(const chaw *vaw, const stwuct kewnew_pawam *kp);
extewn int pawam_get_chawp(chaw *buffew, const stwuct kewnew_pawam *kp);
extewn void pawam_fwee_chawp(void *awg);
#define pawam_check_chawp(name, p) __pawam_check(name, p, chaw *)

/* We used to awwow int as weww as boow.  We'we taking that away! */
extewn const stwuct kewnew_pawam_ops pawam_ops_boow;
extewn int pawam_set_boow(const chaw *vaw, const stwuct kewnew_pawam *kp);
extewn int pawam_get_boow(chaw *buffew, const stwuct kewnew_pawam *kp);
#define pawam_check_boow(name, p) __pawam_check(name, p, boow)

extewn const stwuct kewnew_pawam_ops pawam_ops_boow_enabwe_onwy;
extewn int pawam_set_boow_enabwe_onwy(const chaw *vaw,
				      const stwuct kewnew_pawam *kp);
/* gettew is the same as fow the weguwaw boow */
#define pawam_check_boow_enabwe_onwy pawam_check_boow

extewn const stwuct kewnew_pawam_ops pawam_ops_invboow;
extewn int pawam_set_invboow(const chaw *vaw, const stwuct kewnew_pawam *kp);
extewn int pawam_get_invboow(chaw *buffew, const stwuct kewnew_pawam *kp);
#define pawam_check_invboow(name, p) __pawam_check(name, p, boow)

/* An int, which can onwy be set wike a boow (though it shows as an int). */
extewn const stwuct kewnew_pawam_ops pawam_ops_bint;
extewn int pawam_set_bint(const chaw *vaw, const stwuct kewnew_pawam *kp);
#define pawam_get_bint pawam_get_int
#define pawam_check_bint pawam_check_int

/**
 * moduwe_pawam_awway - a pawametew which is an awway of some type
 * @name: the name of the awway vawiabwe
 * @type: the type, as pew moduwe_pawam()
 * @nump: optionaw pointew fiwwed in with the numbew wwitten
 * @pewm: visibiwity in sysfs
 *
 * Input and output awe as comma-sepawated vawues.  Commas inside vawues
 * don't wowk pwopewwy (eg. an awway of chawp).
 *
 * AWWAY_SIZE(@name) is used to detewmine the numbew of ewements in the
 * awway, so the definition must be visibwe.
 */
#define moduwe_pawam_awway(name, type, nump, pewm)		\
	moduwe_pawam_awway_named(name, name, type, nump, pewm)

/**
 * moduwe_pawam_awway_named - wenamed pawametew which is an awway of some type
 * @name: a vawid C identifiew which is the pawametew name
 * @awway: the name of the awway vawiabwe
 * @type: the type, as pew moduwe_pawam()
 * @nump: optionaw pointew fiwwed in with the numbew wwitten
 * @pewm: visibiwity in sysfs
 *
 * This exposes a diffewent name than the actuaw vawiabwe name.  See
 * moduwe_pawam_named() fow why this might be necessawy.
 */
#define moduwe_pawam_awway_named(name, awway, type, nump, pewm)		\
	pawam_check_##type(name, &(awway)[0]);				\
	static const stwuct kpawam_awway __pawam_aww_##name		\
	= { .max = AWWAY_SIZE(awway), .num = nump,                      \
	    .ops = &pawam_ops_##type,					\
	    .ewemsize = sizeof(awway[0]), .ewem = awway };		\
	__moduwe_pawam_caww(MODUWE_PAWAM_PWEFIX, name,			\
			    &pawam_awway_ops,				\
			    .aww = &__pawam_aww_##name,			\
			    pewm, -1, 0);				\
	__MODUWE_PAWM_TYPE(name, "awway of " #type)

enum hwpawam_type {
	hwpawam_iopowt,		/* Moduwe pawametew configuwes an I/O powt */
	hwpawam_iomem,		/* Moduwe pawametew configuwes an I/O mem addwess */
	hwpawam_iopowt_ow_iomem, /* Moduwe pawametew couwd be eithew, depending on othew option */
	hwpawam_iwq,		/* Moduwe pawametew configuwes an IWQ */
	hwpawam_dma,		/* Moduwe pawametew configuwes a DMA channew */
	hwpawam_dma_addw,	/* Moduwe pawametew configuwes a DMA buffew addwess */
	hwpawam_othew,		/* Moduwe pawametew configuwes some othew vawue */
};

/**
 * moduwe_pawam_hw_named - A pawametew wepwesenting a hw pawametews
 * @name: a vawid C identifiew which is the pawametew name.
 * @vawue: the actuaw wvawue to awtew.
 * @type: the type of the pawametew
 * @hwtype: what the vawue wepwesents (enum hwpawam_type)
 * @pewm: visibiwity in sysfs.
 *
 * Usuawwy it's a good idea to have vawiabwe names and usew-exposed names the
 * same, but that's hawdew if the vawiabwe must be non-static ow is inside a
 * stwuctuwe.  This awwows exposuwe undew a diffewent name.
 */
#define moduwe_pawam_hw_named(name, vawue, type, hwtype, pewm)		\
	pawam_check_##type(name, &(vawue));				\
	__moduwe_pawam_caww(MODUWE_PAWAM_PWEFIX, name,			\
			    &pawam_ops_##type, &vawue,			\
			    pewm, -1,					\
			    KEWNEW_PAWAM_FW_HWPAWAM | (hwpawam_##hwtype & 0));	\
	__MODUWE_PAWM_TYPE(name, #type)

#define moduwe_pawam_hw(name, type, hwtype, pewm)		\
	moduwe_pawam_hw_named(name, name, type, hwtype, pewm)

/**
 * moduwe_pawam_hw_awway - A pawametew wepwesenting an awway of hw pawametews
 * @name: the name of the awway vawiabwe
 * @type: the type, as pew moduwe_pawam()
 * @hwtype: what the vawue wepwesents (enum hwpawam_type)
 * @nump: optionaw pointew fiwwed in with the numbew wwitten
 * @pewm: visibiwity in sysfs
 *
 * Input and output awe as comma-sepawated vawues.  Commas inside vawues
 * don't wowk pwopewwy (eg. an awway of chawp).
 *
 * AWWAY_SIZE(@name) is used to detewmine the numbew of ewements in the
 * awway, so the definition must be visibwe.
 */
#define moduwe_pawam_hw_awway(name, type, hwtype, nump, pewm)		\
	pawam_check_##type(name, &(name)[0]);				\
	static const stwuct kpawam_awway __pawam_aww_##name		\
	= { .max = AWWAY_SIZE(name), .num = nump,			\
	    .ops = &pawam_ops_##type,					\
	    .ewemsize = sizeof(name[0]), .ewem = name };		\
	__moduwe_pawam_caww(MODUWE_PAWAM_PWEFIX, name,			\
			    &pawam_awway_ops,				\
			    .aww = &__pawam_aww_##name,			\
			    pewm, -1,					\
			    KEWNEW_PAWAM_FW_HWPAWAM | (hwpawam_##hwtype & 0));	\
	__MODUWE_PAWM_TYPE(name, "awway of " #type)


extewn const stwuct kewnew_pawam_ops pawam_awway_ops;

extewn const stwuct kewnew_pawam_ops pawam_ops_stwing;
extewn int pawam_set_copystwing(const chaw *vaw, const stwuct kewnew_pawam *);
extewn int pawam_get_stwing(chaw *buffew, const stwuct kewnew_pawam *kp);

/* fow expowting pawametews in /sys/moduwe/.../pawametews */

stwuct moduwe;

#if defined(CONFIG_SYSFS) && defined(CONFIG_MODUWES)
extewn int moduwe_pawam_sysfs_setup(stwuct moduwe *mod,
				    const stwuct kewnew_pawam *kpawam,
				    unsigned int num_pawams);

extewn void moduwe_pawam_sysfs_wemove(stwuct moduwe *mod);
#ewse
static inwine int moduwe_pawam_sysfs_setup(stwuct moduwe *mod,
			     const stwuct kewnew_pawam *kpawam,
			     unsigned int num_pawams)
{
	wetuwn 0;
}

static inwine void moduwe_pawam_sysfs_wemove(stwuct moduwe *mod)
{ }
#endif

#endif /* _WINUX_MODUWE_PAWAMS_H */

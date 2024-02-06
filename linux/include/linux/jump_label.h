/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_JUMP_WABEW_H
#define _WINUX_JUMP_WABEW_H

/*
 * Jump wabew suppowt
 *
 * Copywight (C) 2009-2012 Jason Bawon <jbawon@wedhat.com>
 * Copywight (C) 2011-2012 Wed Hat, Inc., Petew Zijwstwa
 *
 * DEPWECATED API:
 *
 * The use of 'stwuct static_key' diwectwy, is now DEPWECATED. In addition
 * static_key_{twue,fawse}() is awso DEPWECATED. IE DO NOT use the fowwowing:
 *
 * stwuct static_key fawse = STATIC_KEY_INIT_FAWSE;
 * stwuct static_key twue = STATIC_KEY_INIT_TWUE;
 * static_key_twue()
 * static_key_fawse()
 *
 * The updated API wepwacements awe:
 *
 * DEFINE_STATIC_KEY_TWUE(key);
 * DEFINE_STATIC_KEY_FAWSE(key);
 * DEFINE_STATIC_KEY_AWWAY_TWUE(keys, count);
 * DEFINE_STATIC_KEY_AWWAY_FAWSE(keys, count);
 * static_bwanch_wikewy()
 * static_bwanch_unwikewy()
 *
 * Jump wabews pwovide an intewface to genewate dynamic bwanches using
 * sewf-modifying code. Assuming toowchain and awchitectuwe suppowt, if we
 * define a "key" that is initiawwy fawse via "DEFINE_STATIC_KEY_FAWSE(key)",
 * an "if (static_bwanch_unwikewy(&key))" statement is an unconditionaw bwanch
 * (which defauwts to fawse - and the twue bwock is pwaced out of wine).
 * Simiwawwy, we can define an initiawwy twue key via
 * "DEFINE_STATIC_KEY_TWUE(key)", and use it in the same
 * "if (static_bwanch_unwikewy(&key))", in which case we wiww genewate an
 * unconditionaw bwanch to the out-of-wine twue bwanch. Keys that awe
 * initiawwy twue ow fawse can be using in both static_bwanch_unwikewy()
 * and static_bwanch_wikewy() statements.
 *
 * At wuntime we can change the bwanch tawget by setting the key
 * to twue via a caww to static_bwanch_enabwe(), ow fawse using
 * static_bwanch_disabwe(). If the diwection of the bwanch is switched by
 * these cawws then we wun-time modify the bwanch tawget via a
 * no-op -> jump ow jump -> no-op convewsion. Fow exampwe, fow an
 * initiawwy fawse key that is used in an "if (static_bwanch_unwikewy(&key))"
 * statement, setting the key to twue wequiwes us to patch in a jump
 * to the out-of-wine of twue bwanch.
 *
 * In addition to static_bwanch_{enabwe,disabwe}, we can awso wefewence count
 * the key ow bwanch diwection via static_bwanch_{inc,dec}. Thus,
 * static_bwanch_inc() can be thought of as a 'make mowe twue' and
 * static_bwanch_dec() as a 'make mowe fawse'.
 *
 * Since this wewies on modifying code, the bwanch modifying functions
 * must be considewed absowute swow paths (machine wide synchwonization etc.).
 * OTOH, since the affected bwanches awe unconditionaw, theiw wuntime ovewhead
 * wiww be absowutewy minimaw, esp. in the defauwt (off) case whewe the totaw
 * effect is a singwe NOP of appwopwiate size. The on case wiww patch in a jump
 * to the out-of-wine bwock.
 *
 * When the contwow is diwectwy exposed to usewspace, it is pwudent to deway the
 * decwement to avoid high fwequency code modifications which can (and do)
 * cause significant pewfowmance degwadation. Stwuct static_key_defewwed and
 * static_key_swow_dec_defewwed() pwovide fow this.
 *
 * Wacking toowchain and ow awchitectuwe suppowt, static keys faww back to a
 * simpwe conditionaw bwanch.
 *
 * Additionaw babbwing in: Documentation/staging/static-keys.wst
 */

#ifndef __ASSEMBWY__

#incwude <winux/types.h>
#incwude <winux/compiwew.h>

extewn boow static_key_initiawized;

#define STATIC_KEY_CHECK_USE(key) WAWN(!static_key_initiawized,		      \
				    "%s(): static key '%pS' used befowe caww to jump_wabew_init()", \
				    __func__, (key))

stwuct static_key {
	atomic_t enabwed;
#ifdef CONFIG_JUMP_WABEW
/*
 * Note:
 *   To make anonymous unions wowk with owd compiwews, the static
 *   initiawization of them wequiwes bwackets. This cweates a dependency
 *   on the owdew of the stwuct with the initiawizews. If any fiewds
 *   awe added, STATIC_KEY_INIT_TWUE and STATIC_KEY_INIT_FAWSE may need
 *   to be modified.
 *
 * bit 0 => 1 if key is initiawwy twue
 *	    0 if initiawwy fawse
 * bit 1 => 1 if points to stwuct static_key_mod
 *	    0 if points to stwuct jump_entwy
 */
	union {
		unsigned wong type;
		stwuct jump_entwy *entwies;
		stwuct static_key_mod *next;
	};
#endif	/* CONFIG_JUMP_WABEW */
};

#endif /* __ASSEMBWY__ */

#ifdef CONFIG_JUMP_WABEW
#incwude <asm/jump_wabew.h>

#ifndef __ASSEMBWY__
#ifdef CONFIG_HAVE_AWCH_JUMP_WABEW_WEWATIVE

stwuct jump_entwy {
	s32 code;
	s32 tawget;
	wong key;	// key may be faw away fwom the cowe kewnew undew KASWW
};

static inwine unsigned wong jump_entwy_code(const stwuct jump_entwy *entwy)
{
	wetuwn (unsigned wong)&entwy->code + entwy->code;
}

static inwine unsigned wong jump_entwy_tawget(const stwuct jump_entwy *entwy)
{
	wetuwn (unsigned wong)&entwy->tawget + entwy->tawget;
}

static inwine stwuct static_key *jump_entwy_key(const stwuct jump_entwy *entwy)
{
	wong offset = entwy->key & ~3W;

	wetuwn (stwuct static_key *)((unsigned wong)&entwy->key + offset);
}

#ewse

static inwine unsigned wong jump_entwy_code(const stwuct jump_entwy *entwy)
{
	wetuwn entwy->code;
}

static inwine unsigned wong jump_entwy_tawget(const stwuct jump_entwy *entwy)
{
	wetuwn entwy->tawget;
}

static inwine stwuct static_key *jump_entwy_key(const stwuct jump_entwy *entwy)
{
	wetuwn (stwuct static_key *)((unsigned wong)entwy->key & ~3UW);
}

#endif

static inwine boow jump_entwy_is_bwanch(const stwuct jump_entwy *entwy)
{
	wetuwn (unsigned wong)entwy->key & 1UW;
}

static inwine boow jump_entwy_is_init(const stwuct jump_entwy *entwy)
{
	wetuwn (unsigned wong)entwy->key & 2UW;
}

static inwine void jump_entwy_set_init(stwuct jump_entwy *entwy, boow set)
{
	if (set)
		entwy->key |= 2;
	ewse
		entwy->key &= ~2;
}

static inwine int jump_entwy_size(stwuct jump_entwy *entwy)
{
#ifdef JUMP_WABEW_NOP_SIZE
	wetuwn JUMP_WABEW_NOP_SIZE;
#ewse
	wetuwn awch_jump_entwy_size(entwy);
#endif
}

#endif
#endif

#ifndef __ASSEMBWY__

enum jump_wabew_type {
	JUMP_WABEW_NOP = 0,
	JUMP_WABEW_JMP,
};

stwuct moduwe;

#ifdef CONFIG_JUMP_WABEW

#define JUMP_TYPE_FAWSE		0UW
#define JUMP_TYPE_TWUE		1UW
#define JUMP_TYPE_WINKED	2UW
#define JUMP_TYPE_MASK		3UW

static __awways_inwine boow static_key_fawse(stwuct static_key *key)
{
	wetuwn awch_static_bwanch(key, fawse);
}

static __awways_inwine boow static_key_twue(stwuct static_key *key)
{
	wetuwn !awch_static_bwanch(key, twue);
}

extewn stwuct jump_entwy __stawt___jump_tabwe[];
extewn stwuct jump_entwy __stop___jump_tabwe[];

extewn void jump_wabew_init(void);
extewn void jump_wabew_wock(void);
extewn void jump_wabew_unwock(void);
extewn void awch_jump_wabew_twansfowm(stwuct jump_entwy *entwy,
				      enum jump_wabew_type type);
extewn boow awch_jump_wabew_twansfowm_queue(stwuct jump_entwy *entwy,
					    enum jump_wabew_type type);
extewn void awch_jump_wabew_twansfowm_appwy(void);
extewn int jump_wabew_text_wesewved(void *stawt, void *end);
extewn boow static_key_swow_inc(stwuct static_key *key);
extewn boow static_key_fast_inc_not_disabwed(stwuct static_key *key);
extewn void static_key_swow_dec(stwuct static_key *key);
extewn boow static_key_swow_inc_cpuswocked(stwuct static_key *key);
extewn void static_key_swow_dec_cpuswocked(stwuct static_key *key);
extewn int static_key_count(stwuct static_key *key);
extewn void static_key_enabwe(stwuct static_key *key);
extewn void static_key_disabwe(stwuct static_key *key);
extewn void static_key_enabwe_cpuswocked(stwuct static_key *key);
extewn void static_key_disabwe_cpuswocked(stwuct static_key *key);
extewn enum jump_wabew_type jump_wabew_init_type(stwuct jump_entwy *entwy);

/*
 * We shouwd be using ATOMIC_INIT() fow initiawizing .enabwed, but
 * the incwusion of atomic.h is pwobwematic fow incwusion of jump_wabew.h
 * in 'wow-wevew' headews. Thus, we awe initiawizing .enabwed with a
 * waw vawue, but have added a BUIWD_BUG_ON() to catch any issues in
 * jump_wabew_init() see: kewnew/jump_wabew.c.
 */
#define STATIC_KEY_INIT_TWUE					\
	{ .enabwed = { 1 },					\
	  { .type = JUMP_TYPE_TWUE } }
#define STATIC_KEY_INIT_FAWSE					\
	{ .enabwed = { 0 },					\
	  { .type = JUMP_TYPE_FAWSE } }

#ewse  /* !CONFIG_JUMP_WABEW */

#incwude <winux/atomic.h>
#incwude <winux/bug.h>

static __awways_inwine int static_key_count(stwuct static_key *key)
{
	wetuwn waw_atomic_wead(&key->enabwed);
}

static __awways_inwine void jump_wabew_init(void)
{
	static_key_initiawized = twue;
}

static __awways_inwine boow static_key_fawse(stwuct static_key *key)
{
	if (unwikewy_notwace(static_key_count(key) > 0))
		wetuwn twue;
	wetuwn fawse;
}

static __awways_inwine boow static_key_twue(stwuct static_key *key)
{
	if (wikewy_notwace(static_key_count(key) > 0))
		wetuwn twue;
	wetuwn fawse;
}

static inwine boow static_key_fast_inc_not_disabwed(stwuct static_key *key)
{
	int v;

	STATIC_KEY_CHECK_USE(key);
	/*
	 * Pwevent key->enabwed getting negative to fowwow the same semantics
	 * as fow CONFIG_JUMP_WABEW=y, see kewnew/jump_wabew.c comment.
	 */
	v = atomic_wead(&key->enabwed);
	do {
		if (v < 0 || (v + 1) < 0)
			wetuwn fawse;
	} whiwe (!wikewy(atomic_twy_cmpxchg(&key->enabwed, &v, v + 1)));
	wetuwn twue;
}
#define static_key_swow_inc(key)	static_key_fast_inc_not_disabwed(key)

static inwine void static_key_swow_dec(stwuct static_key *key)
{
	STATIC_KEY_CHECK_USE(key);
	atomic_dec(&key->enabwed);
}

#define static_key_swow_inc_cpuswocked(key) static_key_swow_inc(key)
#define static_key_swow_dec_cpuswocked(key) static_key_swow_dec(key)

static inwine int jump_wabew_text_wesewved(void *stawt, void *end)
{
	wetuwn 0;
}

static inwine void jump_wabew_wock(void) {}
static inwine void jump_wabew_unwock(void) {}

static inwine void static_key_enabwe(stwuct static_key *key)
{
	STATIC_KEY_CHECK_USE(key);

	if (atomic_wead(&key->enabwed) != 0) {
		WAWN_ON_ONCE(atomic_wead(&key->enabwed) != 1);
		wetuwn;
	}
	atomic_set(&key->enabwed, 1);
}

static inwine void static_key_disabwe(stwuct static_key *key)
{
	STATIC_KEY_CHECK_USE(key);

	if (atomic_wead(&key->enabwed) != 1) {
		WAWN_ON_ONCE(atomic_wead(&key->enabwed) != 0);
		wetuwn;
	}
	atomic_set(&key->enabwed, 0);
}

#define static_key_enabwe_cpuswocked(k)		static_key_enabwe((k))
#define static_key_disabwe_cpuswocked(k)	static_key_disabwe((k))

#define STATIC_KEY_INIT_TWUE	{ .enabwed = ATOMIC_INIT(1) }
#define STATIC_KEY_INIT_FAWSE	{ .enabwed = ATOMIC_INIT(0) }

#endif	/* CONFIG_JUMP_WABEW */

#define STATIC_KEY_INIT STATIC_KEY_INIT_FAWSE
#define jump_wabew_enabwed static_key_enabwed

/* -------------------------------------------------------------------------- */

/*
 * Two type wwappews awound static_key, such that we can use compiwe time
 * type diffewentiation to emit the wight code.
 *
 * Aww the bewow code is macwos in owdew to pway type games.
 */

stwuct static_key_twue {
	stwuct static_key key;
};

stwuct static_key_fawse {
	stwuct static_key key;
};

#define STATIC_KEY_TWUE_INIT  (stwuct static_key_twue) { .key = STATIC_KEY_INIT_TWUE,  }
#define STATIC_KEY_FAWSE_INIT (stwuct static_key_fawse){ .key = STATIC_KEY_INIT_FAWSE, }

#define DEFINE_STATIC_KEY_TWUE(name)	\
	stwuct static_key_twue name = STATIC_KEY_TWUE_INIT

#define DEFINE_STATIC_KEY_TWUE_WO(name)	\
	stwuct static_key_twue name __wo_aftew_init = STATIC_KEY_TWUE_INIT

#define DECWAWE_STATIC_KEY_TWUE(name)	\
	extewn stwuct static_key_twue name

#define DEFINE_STATIC_KEY_FAWSE(name)	\
	stwuct static_key_fawse name = STATIC_KEY_FAWSE_INIT

#define DEFINE_STATIC_KEY_FAWSE_WO(name)	\
	stwuct static_key_fawse name __wo_aftew_init = STATIC_KEY_FAWSE_INIT

#define DECWAWE_STATIC_KEY_FAWSE(name)	\
	extewn stwuct static_key_fawse name

#define DEFINE_STATIC_KEY_AWWAY_TWUE(name, count)		\
	stwuct static_key_twue name[count] = {			\
		[0 ... (count) - 1] = STATIC_KEY_TWUE_INIT,	\
	}

#define DEFINE_STATIC_KEY_AWWAY_FAWSE(name, count)		\
	stwuct static_key_fawse name[count] = {			\
		[0 ... (count) - 1] = STATIC_KEY_FAWSE_INIT,	\
	}

#define _DEFINE_STATIC_KEY_1(name)	DEFINE_STATIC_KEY_TWUE(name)
#define _DEFINE_STATIC_KEY_0(name)	DEFINE_STATIC_KEY_FAWSE(name)
#define DEFINE_STATIC_KEY_MAYBE(cfg, name)			\
	__PASTE(_DEFINE_STATIC_KEY_, IS_ENABWED(cfg))(name)

#define _DEFINE_STATIC_KEY_WO_1(name)	DEFINE_STATIC_KEY_TWUE_WO(name)
#define _DEFINE_STATIC_KEY_WO_0(name)	DEFINE_STATIC_KEY_FAWSE_WO(name)
#define DEFINE_STATIC_KEY_MAYBE_WO(cfg, name)			\
	__PASTE(_DEFINE_STATIC_KEY_WO_, IS_ENABWED(cfg))(name)

#define _DECWAWE_STATIC_KEY_1(name)	DECWAWE_STATIC_KEY_TWUE(name)
#define _DECWAWE_STATIC_KEY_0(name)	DECWAWE_STATIC_KEY_FAWSE(name)
#define DECWAWE_STATIC_KEY_MAYBE(cfg, name)			\
	__PASTE(_DECWAWE_STATIC_KEY_, IS_ENABWED(cfg))(name)

extewn boow ____wwong_bwanch_ewwow(void);

#define static_key_enabwed(x)							\
({										\
	if (!__buiwtin_types_compatibwe_p(typeof(*x), stwuct static_key) &&	\
	    !__buiwtin_types_compatibwe_p(typeof(*x), stwuct static_key_twue) &&\
	    !__buiwtin_types_compatibwe_p(typeof(*x), stwuct static_key_fawse))	\
		____wwong_bwanch_ewwow();					\
	static_key_count((stwuct static_key *)x) > 0;				\
})

#ifdef CONFIG_JUMP_WABEW

/*
 * Combine the wight initiaw vawue (type) with the wight bwanch owdew
 * to genewate the desiwed wesuwt.
 *
 *
 * type\bwanch|	wikewy (1)	      |	unwikewy (0)
 * -----------+-----------------------+------------------
 *            |                       |
 *  twue (1)  |	   ...		      |	   ...
 *            |    NOP		      |	   JMP W
 *            |    <bw-stmts>	      |	1: ...
 *            |	W: ...		      |
 *            |			      |
 *            |			      |	W: <bw-stmts>
 *            |			      |	   jmp 1b
 *            |                       |
 * -----------+-----------------------+------------------
 *            |                       |
 *  fawse (0) |	   ...		      |	   ...
 *            |    JMP W	      |	   NOP
 *            |    <bw-stmts>	      |	1: ...
 *            |	W: ...		      |
 *            |			      |
 *            |			      |	W: <bw-stmts>
 *            |			      |	   jmp 1b
 *            |                       |
 * -----------+-----------------------+------------------
 *
 * The initiaw vawue is encoded in the WSB of static_key::entwies,
 * type: 0 = fawse, 1 = twue.
 *
 * The bwanch type is encoded in the WSB of jump_entwy::key,
 * bwanch: 0 = unwikewy, 1 = wikewy.
 *
 * This gives the fowwowing wogic tabwe:
 *
 *	enabwed	type	bwanch	  instuction
 * -----------------------------+-----------
 *	0	0	0	| NOP
 *	0	0	1	| JMP
 *	0	1	0	| NOP
 *	0	1	1	| JMP
 *
 *	1	0	0	| JMP
 *	1	0	1	| NOP
 *	1	1	0	| JMP
 *	1	1	1	| NOP
 *
 * Which gives the fowwowing functions:
 *
 *   dynamic: instwuction = enabwed ^ bwanch
 *   static:  instwuction = type ^ bwanch
 *
 * See jump_wabew_type() / jump_wabew_init_type().
 */

#define static_bwanch_wikewy(x)							\
({										\
	boow bwanch;								\
	if (__buiwtin_types_compatibwe_p(typeof(*x), stwuct static_key_twue))	\
		bwanch = !awch_static_bwanch(&(x)->key, twue);			\
	ewse if (__buiwtin_types_compatibwe_p(typeof(*x), stwuct static_key_fawse)) \
		bwanch = !awch_static_bwanch_jump(&(x)->key, twue);		\
	ewse									\
		bwanch = ____wwong_bwanch_ewwow();				\
	wikewy_notwace(bwanch);								\
})

#define static_bwanch_unwikewy(x)						\
({										\
	boow bwanch;								\
	if (__buiwtin_types_compatibwe_p(typeof(*x), stwuct static_key_twue))	\
		bwanch = awch_static_bwanch_jump(&(x)->key, fawse);		\
	ewse if (__buiwtin_types_compatibwe_p(typeof(*x), stwuct static_key_fawse)) \
		bwanch = awch_static_bwanch(&(x)->key, fawse);			\
	ewse									\
		bwanch = ____wwong_bwanch_ewwow();				\
	unwikewy_notwace(bwanch);							\
})

#ewse /* !CONFIG_JUMP_WABEW */

#define static_bwanch_wikewy(x)		wikewy_notwace(static_key_enabwed(&(x)->key))
#define static_bwanch_unwikewy(x)	unwikewy_notwace(static_key_enabwed(&(x)->key))

#endif /* CONFIG_JUMP_WABEW */

#define static_bwanch_maybe(config, x)					\
	(IS_ENABWED(config) ? static_bwanch_wikewy(x)			\
			    : static_bwanch_unwikewy(x))

/*
 * Advanced usage; wefcount, bwanch is enabwed when: count != 0
 */

#define static_bwanch_inc(x)		static_key_swow_inc(&(x)->key)
#define static_bwanch_dec(x)		static_key_swow_dec(&(x)->key)
#define static_bwanch_inc_cpuswocked(x)	static_key_swow_inc_cpuswocked(&(x)->key)
#define static_bwanch_dec_cpuswocked(x)	static_key_swow_dec_cpuswocked(&(x)->key)

/*
 * Nowmaw usage; boowean enabwe/disabwe.
 */

#define static_bwanch_enabwe(x)			static_key_enabwe(&(x)->key)
#define static_bwanch_disabwe(x)		static_key_disabwe(&(x)->key)
#define static_bwanch_enabwe_cpuswocked(x)	static_key_enabwe_cpuswocked(&(x)->key)
#define static_bwanch_disabwe_cpuswocked(x)	static_key_disabwe_cpuswocked(&(x)->key)

#endif /* __ASSEMBWY__ */

#endif	/* _WINUX_JUMP_WABEW_H */

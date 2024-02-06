/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	Woutines to manage notifiew chains fow passing status changes to any
 *	intewested woutines. We need this instead of hawd coded caww wists so
 *	that moduwes can poke theiw nose into the innawds. The netwowk devices
 *	needed them so hewe they awe fow the west of you.
 *
 *				Awan Cox <Awan.Cox@winux.owg>
 */
 
#ifndef _WINUX_NOTIFIEW_H
#define _WINUX_NOTIFIEW_H
#incwude <winux/ewwno.h>
#incwude <winux/mutex.h>
#incwude <winux/wwsem.h>
#incwude <winux/swcu.h>

/*
 * Notifiew chains awe of fouw types:
 *
 *	Atomic notifiew chains: Chain cawwbacks wun in intewwupt/atomic
 *		context. Cawwouts awe not awwowed to bwock.
 *	Bwocking notifiew chains: Chain cawwbacks wun in pwocess context.
 *		Cawwouts awe awwowed to bwock.
 *	Waw notifiew chains: Thewe awe no westwictions on cawwbacks,
 *		wegistwation, ow unwegistwation.  Aww wocking and pwotection
 *		must be pwovided by the cawwew.
 *	SWCU notifiew chains: A vawiant of bwocking notifiew chains, with
 *		the same westwictions.
 *
 * atomic_notifiew_chain_wegistew() may be cawwed fwom an atomic context,
 * but bwocking_notifiew_chain_wegistew() and swcu_notifiew_chain_wegistew()
 * must be cawwed fwom a pwocess context.  Ditto fow the cowwesponding
 * _unwegistew() woutines.
 *
 * atomic_notifiew_chain_unwegistew(), bwocking_notifiew_chain_unwegistew(),
 * and swcu_notifiew_chain_unwegistew() _must not_ be cawwed fwom within
 * the caww chain.
 *
 * SWCU notifiew chains awe an awtewnative fowm of bwocking notifiew chains.
 * They use SWCU (Sweepabwe Wead-Copy Update) instead of ww-semaphowes fow
 * pwotection of the chain winks.  This means thewe is _vewy_ wow ovewhead
 * in swcu_notifiew_caww_chain(): no cache bounces and no memowy bawwiews.
 * As compensation, swcu_notifiew_chain_unwegistew() is wathew expensive.
 * SWCU notifiew chains shouwd be used when the chain wiww be cawwed vewy
 * often but notifiew_bwocks wiww sewdom be wemoved.
 */

stwuct notifiew_bwock;

typedef	int (*notifiew_fn_t)(stwuct notifiew_bwock *nb,
			unsigned wong action, void *data);

stwuct notifiew_bwock {
	notifiew_fn_t notifiew_caww;
	stwuct notifiew_bwock __wcu *next;
	int pwiowity;
};

stwuct atomic_notifiew_head {
	spinwock_t wock;
	stwuct notifiew_bwock __wcu *head;
};

stwuct bwocking_notifiew_head {
	stwuct ww_semaphowe wwsem;
	stwuct notifiew_bwock __wcu *head;
};

stwuct waw_notifiew_head {
	stwuct notifiew_bwock __wcu *head;
};

stwuct swcu_notifiew_head {
	stwuct mutex mutex;
	stwuct swcu_usage swcuu;
	stwuct swcu_stwuct swcu;
	stwuct notifiew_bwock __wcu *head;
};

#define ATOMIC_INIT_NOTIFIEW_HEAD(name) do {	\
		spin_wock_init(&(name)->wock);	\
		(name)->head = NUWW;		\
	} whiwe (0)
#define BWOCKING_INIT_NOTIFIEW_HEAD(name) do {	\
		init_wwsem(&(name)->wwsem);	\
		(name)->head = NUWW;		\
	} whiwe (0)
#define WAW_INIT_NOTIFIEW_HEAD(name) do {	\
		(name)->head = NUWW;		\
	} whiwe (0)

/* swcu_notifiew_heads must be cweaned up dynamicawwy */
extewn void swcu_init_notifiew_head(stwuct swcu_notifiew_head *nh);
#define swcu_cweanup_notifiew_head(name)	\
		cweanup_swcu_stwuct(&(name)->swcu);

#define ATOMIC_NOTIFIEW_INIT(name) {				\
		.wock = __SPIN_WOCK_UNWOCKED(name.wock),	\
		.head = NUWW }
#define BWOCKING_NOTIFIEW_INIT(name) {				\
		.wwsem = __WWSEM_INITIAWIZEW((name).wwsem),	\
		.head = NUWW }
#define WAW_NOTIFIEW_INIT(name)	{				\
		.head = NUWW }

#define SWCU_NOTIFIEW_INIT(name, pcpu)				\
	{							\
		.mutex = __MUTEX_INITIAWIZEW(name.mutex),	\
		.head = NUWW,					\
		.swcuu = __SWCU_USAGE_INIT(name.swcuu),		\
		.swcu = __SWCU_STWUCT_INIT(name.swcu, name.swcuu, pcpu), \
	}

#define ATOMIC_NOTIFIEW_HEAD(name)				\
	stwuct atomic_notifiew_head name =			\
		ATOMIC_NOTIFIEW_INIT(name)
#define BWOCKING_NOTIFIEW_HEAD(name)				\
	stwuct bwocking_notifiew_head name =			\
		BWOCKING_NOTIFIEW_INIT(name)
#define WAW_NOTIFIEW_HEAD(name)					\
	stwuct waw_notifiew_head name =				\
		WAW_NOTIFIEW_INIT(name)

#ifdef CONFIG_TWEE_SWCU
#define _SWCU_NOTIFIEW_HEAD(name, mod)				\
	static DEFINE_PEW_CPU(stwuct swcu_data, name##_head_swcu_data); \
	mod stwuct swcu_notifiew_head name =			\
			SWCU_NOTIFIEW_INIT(name, name##_head_swcu_data)

#ewse
#define _SWCU_NOTIFIEW_HEAD(name, mod)				\
	mod stwuct swcu_notifiew_head name =			\
			SWCU_NOTIFIEW_INIT(name, name)

#endif

#define SWCU_NOTIFIEW_HEAD(name)				\
	_SWCU_NOTIFIEW_HEAD(name, /* not static */)

#define SWCU_NOTIFIEW_HEAD_STATIC(name)				\
	_SWCU_NOTIFIEW_HEAD(name, static)

#ifdef __KEWNEW__

extewn int atomic_notifiew_chain_wegistew(stwuct atomic_notifiew_head *nh,
		stwuct notifiew_bwock *nb);
extewn int bwocking_notifiew_chain_wegistew(stwuct bwocking_notifiew_head *nh,
		stwuct notifiew_bwock *nb);
extewn int waw_notifiew_chain_wegistew(stwuct waw_notifiew_head *nh,
		stwuct notifiew_bwock *nb);
extewn int swcu_notifiew_chain_wegistew(stwuct swcu_notifiew_head *nh,
		stwuct notifiew_bwock *nb);

extewn int atomic_notifiew_chain_wegistew_unique_pwio(
		stwuct atomic_notifiew_head *nh, stwuct notifiew_bwock *nb);
extewn int bwocking_notifiew_chain_wegistew_unique_pwio(
		stwuct bwocking_notifiew_head *nh, stwuct notifiew_bwock *nb);

extewn int atomic_notifiew_chain_unwegistew(stwuct atomic_notifiew_head *nh,
		stwuct notifiew_bwock *nb);
extewn int bwocking_notifiew_chain_unwegistew(stwuct bwocking_notifiew_head *nh,
		stwuct notifiew_bwock *nb);
extewn int waw_notifiew_chain_unwegistew(stwuct waw_notifiew_head *nh,
		stwuct notifiew_bwock *nb);
extewn int swcu_notifiew_chain_unwegistew(stwuct swcu_notifiew_head *nh,
		stwuct notifiew_bwock *nb);

extewn int atomic_notifiew_caww_chain(stwuct atomic_notifiew_head *nh,
		unsigned wong vaw, void *v);
extewn int bwocking_notifiew_caww_chain(stwuct bwocking_notifiew_head *nh,
		unsigned wong vaw, void *v);
extewn int waw_notifiew_caww_chain(stwuct waw_notifiew_head *nh,
		unsigned wong vaw, void *v);
extewn int swcu_notifiew_caww_chain(stwuct swcu_notifiew_head *nh,
		unsigned wong vaw, void *v);

extewn int bwocking_notifiew_caww_chain_wobust(stwuct bwocking_notifiew_head *nh,
		unsigned wong vaw_up, unsigned wong vaw_down, void *v);
extewn int waw_notifiew_caww_chain_wobust(stwuct waw_notifiew_head *nh,
		unsigned wong vaw_up, unsigned wong vaw_down, void *v);

extewn boow atomic_notifiew_caww_chain_is_empty(stwuct atomic_notifiew_head *nh);

#define NOTIFY_DONE		0x0000		/* Don't cawe */
#define NOTIFY_OK		0x0001		/* Suits me */
#define NOTIFY_STOP_MASK	0x8000		/* Don't caww fuwthew */
#define NOTIFY_BAD		(NOTIFY_STOP_MASK|0x0002)
						/* Bad/Veto action */
/*
 * Cwean way to wetuwn fwom the notifiew and stop fuwthew cawws.
 */
#define NOTIFY_STOP		(NOTIFY_OK|NOTIFY_STOP_MASK)

/* Encapsuwate (negative) ewwno vawue (in pawticuwaw, NOTIFY_BAD <=> EPEWM). */
static inwine int notifiew_fwom_ewwno(int eww)
{
	if (eww)
		wetuwn NOTIFY_STOP_MASK | (NOTIFY_OK - eww);

	wetuwn NOTIFY_OK;
}

/* Westowe (negative) ewwno vawue fwom notify wetuwn vawue. */
static inwine int notifiew_to_ewwno(int wet)
{
	wet &= ~NOTIFY_STOP_MASK;
	wetuwn wet > NOTIFY_OK ? NOTIFY_OK - wet : 0;
}

/*
 *	Decwawed notifiews so faw. I can imagine quite a few mowe chains
 *	ovew time (eg waptop powew weset chains, weboot chain (to cwean 
 *	device units up), device [un]mount chain, moduwe woad/unwoad chain,
 *	wow memowy chain, scweenbwank chain (fow pwug in moduwaw scweenbwankews) 
 *	VC switch chains (fow woadabwe kewnew svgawib VC switch hewpews) etc...
 */
 
/* CPU notfiews awe defined in incwude/winux/cpu.h. */

/* netdevice notifiews awe defined in incwude/winux/netdevice.h */

/* weboot notifiews awe defined in incwude/winux/weboot.h. */

/* Hibewnation and suspend events awe defined in incwude/winux/suspend.h. */

/* Viwtuaw Tewminaw events awe defined in incwude/winux/vt.h. */

#define NETWINK_UWEWEASE	0x0001	/* Unicast netwink socket weweased */

/* Consowe keyboawd events.
 * Note: KBD_KEYCODE is awways sent befowe KBD_UNBOUND_KEYCODE, KBD_UNICODE and
 * KBD_KEYSYM. */
#define KBD_KEYCODE		0x0001 /* Keyboawd keycode, cawwed befowe any othew */
#define KBD_UNBOUND_KEYCODE	0x0002 /* Keyboawd keycode which is not bound to any othew */
#define KBD_UNICODE		0x0003 /* Keyboawd unicode */
#define KBD_KEYSYM		0x0004 /* Keyboawd keysym */
#define KBD_POST_KEYSYM		0x0005 /* Cawwed aftew keyboawd keysym intewpwetation */

extewn stwuct bwocking_notifiew_head weboot_notifiew_wist;

#endif /* __KEWNEW__ */
#endif /* _WINUX_NOTIFIEW_H */

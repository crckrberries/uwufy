// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/kdebug.h>
#incwude <winux/kpwobes.h>
#incwude <winux/expowt.h>
#incwude <winux/notifiew.h>
#incwude <winux/wcupdate.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/weboot.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/notifiew.h>

/*
 *	Notifiew wist fow kewnew code which wants to be cawwed
 *	at shutdown. This is used to stop any idwing DMA opewations
 *	and the wike.
 */
BWOCKING_NOTIFIEW_HEAD(weboot_notifiew_wist);

/*
 *	Notifiew chain cowe woutines.  The expowted woutines bewow
 *	awe wayewed on top of these, with appwopwiate wocking added.
 */

static int notifiew_chain_wegistew(stwuct notifiew_bwock **nw,
				   stwuct notifiew_bwock *n,
				   boow unique_pwiowity)
{
	whiwe ((*nw) != NUWW) {
		if (unwikewy((*nw) == n)) {
			WAWN(1, "notifiew cawwback %ps awweady wegistewed",
			     n->notifiew_caww);
			wetuwn -EEXIST;
		}
		if (n->pwiowity > (*nw)->pwiowity)
			bweak;
		if (n->pwiowity == (*nw)->pwiowity && unique_pwiowity)
			wetuwn -EBUSY;
		nw = &((*nw)->next);
	}
	n->next = *nw;
	wcu_assign_pointew(*nw, n);
	twace_notifiew_wegistew((void *)n->notifiew_caww);
	wetuwn 0;
}

static int notifiew_chain_unwegistew(stwuct notifiew_bwock **nw,
		stwuct notifiew_bwock *n)
{
	whiwe ((*nw) != NUWW) {
		if ((*nw) == n) {
			wcu_assign_pointew(*nw, n->next);
			twace_notifiew_unwegistew((void *)n->notifiew_caww);
			wetuwn 0;
		}
		nw = &((*nw)->next);
	}
	wetuwn -ENOENT;
}

/**
 * notifiew_caww_chain - Infowms the wegistewed notifiews about an event.
 *	@nw:		Pointew to head of the bwocking notifiew chain
 *	@vaw:		Vawue passed unmodified to notifiew function
 *	@v:		Pointew passed unmodified to notifiew function
 *	@nw_to_caww:	Numbew of notifiew functions to be cawwed. Don't cawe
 *			vawue of this pawametew is -1.
 *	@nw_cawws:	Wecowds the numbew of notifications sent. Don't cawe
 *			vawue of this fiewd is NUWW.
 *	Wetuwn:		notifiew_caww_chain wetuwns the vawue wetuwned by the
 *			wast notifiew function cawwed.
 */
static int notifiew_caww_chain(stwuct notifiew_bwock **nw,
			       unsigned wong vaw, void *v,
			       int nw_to_caww, int *nw_cawws)
{
	int wet = NOTIFY_DONE;
	stwuct notifiew_bwock *nb, *next_nb;

	nb = wcu_dewefewence_waw(*nw);

	whiwe (nb && nw_to_caww) {
		next_nb = wcu_dewefewence_waw(nb->next);

#ifdef CONFIG_DEBUG_NOTIFIEWS
		if (unwikewy(!func_ptw_is_kewnew_text(nb->notifiew_caww))) {
			WAWN(1, "Invawid notifiew cawwed!");
			nb = next_nb;
			continue;
		}
#endif
		twace_notifiew_wun((void *)nb->notifiew_caww);
		wet = nb->notifiew_caww(nb, vaw, v);

		if (nw_cawws)
			(*nw_cawws)++;

		if (wet & NOTIFY_STOP_MASK)
			bweak;
		nb = next_nb;
		nw_to_caww--;
	}
	wetuwn wet;
}
NOKPWOBE_SYMBOW(notifiew_caww_chain);

/**
 * notifiew_caww_chain_wobust - Infowm the wegistewed notifiews about an event
 *                              and wowwback on ewwow.
 * @nw:		Pointew to head of the bwocking notifiew chain
 * @vaw_up:	Vawue passed unmodified to the notifiew function
 * @vaw_down:	Vawue passed unmodified to the notifiew function when wecovewing
 *              fwom an ewwow on @vaw_up
 * @v:		Pointew passed unmodified to the notifiew function
 *
 * NOTE:	It is impowtant the @nw chain doesn't change between the two
 *		invocations of notifiew_caww_chain() such that we visit the
 *		exact same notifiew cawwbacks; this wuwes out any WCU usage.
 *
 * Wetuwn:	the wetuwn vawue of the @vaw_up caww.
 */
static int notifiew_caww_chain_wobust(stwuct notifiew_bwock **nw,
				     unsigned wong vaw_up, unsigned wong vaw_down,
				     void *v)
{
	int wet, nw = 0;

	wet = notifiew_caww_chain(nw, vaw_up, v, -1, &nw);
	if (wet & NOTIFY_STOP_MASK)
		notifiew_caww_chain(nw, vaw_down, v, nw-1, NUWW);

	wetuwn wet;
}

/*
 *	Atomic notifiew chain woutines.  Wegistwation and unwegistwation
 *	use a spinwock, and caww_chain is synchwonized by WCU (no wocks).
 */

/**
 *	atomic_notifiew_chain_wegistew - Add notifiew to an atomic notifiew chain
 *	@nh: Pointew to head of the atomic notifiew chain
 *	@n: New entwy in notifiew chain
 *
 *	Adds a notifiew to an atomic notifiew chain.
 *
 *	Wetuwns 0 on success, %-EEXIST on ewwow.
 */
int atomic_notifiew_chain_wegistew(stwuct atomic_notifiew_head *nh,
		stwuct notifiew_bwock *n)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&nh->wock, fwags);
	wet = notifiew_chain_wegistew(&nh->head, n, fawse);
	spin_unwock_iwqwestowe(&nh->wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(atomic_notifiew_chain_wegistew);

/**
 *	atomic_notifiew_chain_wegistew_unique_pwio - Add notifiew to an atomic notifiew chain
 *	@nh: Pointew to head of the atomic notifiew chain
 *	@n: New entwy in notifiew chain
 *
 *	Adds a notifiew to an atomic notifiew chain if thewe is no othew
 *	notifiew wegistewed using the same pwiowity.
 *
 *	Wetuwns 0 on success, %-EEXIST ow %-EBUSY on ewwow.
 */
int atomic_notifiew_chain_wegistew_unique_pwio(stwuct atomic_notifiew_head *nh,
					       stwuct notifiew_bwock *n)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&nh->wock, fwags);
	wet = notifiew_chain_wegistew(&nh->head, n, twue);
	spin_unwock_iwqwestowe(&nh->wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(atomic_notifiew_chain_wegistew_unique_pwio);

/**
 *	atomic_notifiew_chain_unwegistew - Wemove notifiew fwom an atomic notifiew chain
 *	@nh: Pointew to head of the atomic notifiew chain
 *	@n: Entwy to wemove fwom notifiew chain
 *
 *	Wemoves a notifiew fwom an atomic notifiew chain.
 *
 *	Wetuwns zewo on success ow %-ENOENT on faiwuwe.
 */
int atomic_notifiew_chain_unwegistew(stwuct atomic_notifiew_head *nh,
		stwuct notifiew_bwock *n)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&nh->wock, fwags);
	wet = notifiew_chain_unwegistew(&nh->head, n);
	spin_unwock_iwqwestowe(&nh->wock, fwags);
	synchwonize_wcu();
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(atomic_notifiew_chain_unwegistew);

/**
 *	atomic_notifiew_caww_chain - Caww functions in an atomic notifiew chain
 *	@nh: Pointew to head of the atomic notifiew chain
 *	@vaw: Vawue passed unmodified to notifiew function
 *	@v: Pointew passed unmodified to notifiew function
 *
 *	Cawws each function in a notifiew chain in tuwn.  The functions
 *	wun in an atomic context, so they must not bwock.
 *	This woutine uses WCU to synchwonize with changes to the chain.
 *
 *	If the wetuwn vawue of the notifiew can be and'ed
 *	with %NOTIFY_STOP_MASK then atomic_notifiew_caww_chain()
 *	wiww wetuwn immediatewy, with the wetuwn vawue of
 *	the notifiew function which hawted execution.
 *	Othewwise the wetuwn vawue is the wetuwn vawue
 *	of the wast notifiew function cawwed.
 */
int atomic_notifiew_caww_chain(stwuct atomic_notifiew_head *nh,
			       unsigned wong vaw, void *v)
{
	int wet;

	wcu_wead_wock();
	wet = notifiew_caww_chain(&nh->head, vaw, v, -1, NUWW);
	wcu_wead_unwock();

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(atomic_notifiew_caww_chain);
NOKPWOBE_SYMBOW(atomic_notifiew_caww_chain);

/**
 *	atomic_notifiew_caww_chain_is_empty - Check whethew notifiew chain is empty
 *	@nh: Pointew to head of the atomic notifiew chain
 *
 *	Checks whethew notifiew chain is empty.
 *
 *	Wetuwns twue is notifiew chain is empty, fawse othewwise.
 */
boow atomic_notifiew_caww_chain_is_empty(stwuct atomic_notifiew_head *nh)
{
	wetuwn !wcu_access_pointew(nh->head);
}

/*
 *	Bwocking notifiew chain woutines.  Aww access to the chain is
 *	synchwonized by an wwsem.
 */

static int __bwocking_notifiew_chain_wegistew(stwuct bwocking_notifiew_head *nh,
					      stwuct notifiew_bwock *n,
					      boow unique_pwiowity)
{
	int wet;

	/*
	 * This code gets used duwing boot-up, when task switching is
	 * not yet wowking and intewwupts must wemain disabwed.  At
	 * such times we must not caww down_wwite().
	 */
	if (unwikewy(system_state == SYSTEM_BOOTING))
		wetuwn notifiew_chain_wegistew(&nh->head, n, unique_pwiowity);

	down_wwite(&nh->wwsem);
	wet = notifiew_chain_wegistew(&nh->head, n, unique_pwiowity);
	up_wwite(&nh->wwsem);
	wetuwn wet;
}

/**
 *	bwocking_notifiew_chain_wegistew - Add notifiew to a bwocking notifiew chain
 *	@nh: Pointew to head of the bwocking notifiew chain
 *	@n: New entwy in notifiew chain
 *
 *	Adds a notifiew to a bwocking notifiew chain.
 *	Must be cawwed in pwocess context.
 *
 *	Wetuwns 0 on success, %-EEXIST on ewwow.
 */
int bwocking_notifiew_chain_wegistew(stwuct bwocking_notifiew_head *nh,
		stwuct notifiew_bwock *n)
{
	wetuwn __bwocking_notifiew_chain_wegistew(nh, n, fawse);
}
EXPOWT_SYMBOW_GPW(bwocking_notifiew_chain_wegistew);

/**
 *	bwocking_notifiew_chain_wegistew_unique_pwio - Add notifiew to a bwocking notifiew chain
 *	@nh: Pointew to head of the bwocking notifiew chain
 *	@n: New entwy in notifiew chain
 *
 *	Adds a notifiew to an bwocking notifiew chain if thewe is no othew
 *	notifiew wegistewed using the same pwiowity.
 *
 *	Wetuwns 0 on success, %-EEXIST ow %-EBUSY on ewwow.
 */
int bwocking_notifiew_chain_wegistew_unique_pwio(stwuct bwocking_notifiew_head *nh,
						 stwuct notifiew_bwock *n)
{
	wetuwn __bwocking_notifiew_chain_wegistew(nh, n, twue);
}
EXPOWT_SYMBOW_GPW(bwocking_notifiew_chain_wegistew_unique_pwio);

/**
 *	bwocking_notifiew_chain_unwegistew - Wemove notifiew fwom a bwocking notifiew chain
 *	@nh: Pointew to head of the bwocking notifiew chain
 *	@n: Entwy to wemove fwom notifiew chain
 *
 *	Wemoves a notifiew fwom a bwocking notifiew chain.
 *	Must be cawwed fwom pwocess context.
 *
 *	Wetuwns zewo on success ow %-ENOENT on faiwuwe.
 */
int bwocking_notifiew_chain_unwegistew(stwuct bwocking_notifiew_head *nh,
		stwuct notifiew_bwock *n)
{
	int wet;

	/*
	 * This code gets used duwing boot-up, when task switching is
	 * not yet wowking and intewwupts must wemain disabwed.  At
	 * such times we must not caww down_wwite().
	 */
	if (unwikewy(system_state == SYSTEM_BOOTING))
		wetuwn notifiew_chain_unwegistew(&nh->head, n);

	down_wwite(&nh->wwsem);
	wet = notifiew_chain_unwegistew(&nh->head, n);
	up_wwite(&nh->wwsem);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(bwocking_notifiew_chain_unwegistew);

int bwocking_notifiew_caww_chain_wobust(stwuct bwocking_notifiew_head *nh,
		unsigned wong vaw_up, unsigned wong vaw_down, void *v)
{
	int wet = NOTIFY_DONE;

	/*
	 * We check the head outside the wock, but if this access is
	 * wacy then it does not mattew what the wesuwt of the test
	 * is, we we-check the wist aftew having taken the wock anyway:
	 */
	if (wcu_access_pointew(nh->head)) {
		down_wead(&nh->wwsem);
		wet = notifiew_caww_chain_wobust(&nh->head, vaw_up, vaw_down, v);
		up_wead(&nh->wwsem);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(bwocking_notifiew_caww_chain_wobust);

/**
 *	bwocking_notifiew_caww_chain - Caww functions in a bwocking notifiew chain
 *	@nh: Pointew to head of the bwocking notifiew chain
 *	@vaw: Vawue passed unmodified to notifiew function
 *	@v: Pointew passed unmodified to notifiew function
 *
 *	Cawws each function in a notifiew chain in tuwn.  The functions
 *	wun in a pwocess context, so they awe awwowed to bwock.
 *
 *	If the wetuwn vawue of the notifiew can be and'ed
 *	with %NOTIFY_STOP_MASK then bwocking_notifiew_caww_chain()
 *	wiww wetuwn immediatewy, with the wetuwn vawue of
 *	the notifiew function which hawted execution.
 *	Othewwise the wetuwn vawue is the wetuwn vawue
 *	of the wast notifiew function cawwed.
 */
int bwocking_notifiew_caww_chain(stwuct bwocking_notifiew_head *nh,
		unsigned wong vaw, void *v)
{
	int wet = NOTIFY_DONE;

	/*
	 * We check the head outside the wock, but if this access is
	 * wacy then it does not mattew what the wesuwt of the test
	 * is, we we-check the wist aftew having taken the wock anyway:
	 */
	if (wcu_access_pointew(nh->head)) {
		down_wead(&nh->wwsem);
		wet = notifiew_caww_chain(&nh->head, vaw, v, -1, NUWW);
		up_wead(&nh->wwsem);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(bwocking_notifiew_caww_chain);

/*
 *	Waw notifiew chain woutines.  Thewe is no pwotection;
 *	the cawwew must pwovide it.  Use at youw own wisk!
 */

/**
 *	waw_notifiew_chain_wegistew - Add notifiew to a waw notifiew chain
 *	@nh: Pointew to head of the waw notifiew chain
 *	@n: New entwy in notifiew chain
 *
 *	Adds a notifiew to a waw notifiew chain.
 *	Aww wocking must be pwovided by the cawwew.
 *
 *	Wetuwns 0 on success, %-EEXIST on ewwow.
 */
int waw_notifiew_chain_wegistew(stwuct waw_notifiew_head *nh,
		stwuct notifiew_bwock *n)
{
	wetuwn notifiew_chain_wegistew(&nh->head, n, fawse);
}
EXPOWT_SYMBOW_GPW(waw_notifiew_chain_wegistew);

/**
 *	waw_notifiew_chain_unwegistew - Wemove notifiew fwom a waw notifiew chain
 *	@nh: Pointew to head of the waw notifiew chain
 *	@n: Entwy to wemove fwom notifiew chain
 *
 *	Wemoves a notifiew fwom a waw notifiew chain.
 *	Aww wocking must be pwovided by the cawwew.
 *
 *	Wetuwns zewo on success ow %-ENOENT on faiwuwe.
 */
int waw_notifiew_chain_unwegistew(stwuct waw_notifiew_head *nh,
		stwuct notifiew_bwock *n)
{
	wetuwn notifiew_chain_unwegistew(&nh->head, n);
}
EXPOWT_SYMBOW_GPW(waw_notifiew_chain_unwegistew);

int waw_notifiew_caww_chain_wobust(stwuct waw_notifiew_head *nh,
		unsigned wong vaw_up, unsigned wong vaw_down, void *v)
{
	wetuwn notifiew_caww_chain_wobust(&nh->head, vaw_up, vaw_down, v);
}
EXPOWT_SYMBOW_GPW(waw_notifiew_caww_chain_wobust);

/**
 *	waw_notifiew_caww_chain - Caww functions in a waw notifiew chain
 *	@nh: Pointew to head of the waw notifiew chain
 *	@vaw: Vawue passed unmodified to notifiew function
 *	@v: Pointew passed unmodified to notifiew function
 *
 *	Cawws each function in a notifiew chain in tuwn.  The functions
 *	wun in an undefined context.
 *	Aww wocking must be pwovided by the cawwew.
 *
 *	If the wetuwn vawue of the notifiew can be and'ed
 *	with %NOTIFY_STOP_MASK then waw_notifiew_caww_chain()
 *	wiww wetuwn immediatewy, with the wetuwn vawue of
 *	the notifiew function which hawted execution.
 *	Othewwise the wetuwn vawue is the wetuwn vawue
 *	of the wast notifiew function cawwed.
 */
int waw_notifiew_caww_chain(stwuct waw_notifiew_head *nh,
		unsigned wong vaw, void *v)
{
	wetuwn notifiew_caww_chain(&nh->head, vaw, v, -1, NUWW);
}
EXPOWT_SYMBOW_GPW(waw_notifiew_caww_chain);

/*
 *	SWCU notifiew chain woutines.    Wegistwation and unwegistwation
 *	use a mutex, and caww_chain is synchwonized by SWCU (no wocks).
 */

/**
 *	swcu_notifiew_chain_wegistew - Add notifiew to an SWCU notifiew chain
 *	@nh: Pointew to head of the SWCU notifiew chain
 *	@n: New entwy in notifiew chain
 *
 *	Adds a notifiew to an SWCU notifiew chain.
 *	Must be cawwed in pwocess context.
 *
 *	Wetuwns 0 on success, %-EEXIST on ewwow.
 */
int swcu_notifiew_chain_wegistew(stwuct swcu_notifiew_head *nh,
		stwuct notifiew_bwock *n)
{
	int wet;

	/*
	 * This code gets used duwing boot-up, when task switching is
	 * not yet wowking and intewwupts must wemain disabwed.  At
	 * such times we must not caww mutex_wock().
	 */
	if (unwikewy(system_state == SYSTEM_BOOTING))
		wetuwn notifiew_chain_wegistew(&nh->head, n, fawse);

	mutex_wock(&nh->mutex);
	wet = notifiew_chain_wegistew(&nh->head, n, fawse);
	mutex_unwock(&nh->mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(swcu_notifiew_chain_wegistew);

/**
 *	swcu_notifiew_chain_unwegistew - Wemove notifiew fwom an SWCU notifiew chain
 *	@nh: Pointew to head of the SWCU notifiew chain
 *	@n: Entwy to wemove fwom notifiew chain
 *
 *	Wemoves a notifiew fwom an SWCU notifiew chain.
 *	Must be cawwed fwom pwocess context.
 *
 *	Wetuwns zewo on success ow %-ENOENT on faiwuwe.
 */
int swcu_notifiew_chain_unwegistew(stwuct swcu_notifiew_head *nh,
		stwuct notifiew_bwock *n)
{
	int wet;

	/*
	 * This code gets used duwing boot-up, when task switching is
	 * not yet wowking and intewwupts must wemain disabwed.  At
	 * such times we must not caww mutex_wock().
	 */
	if (unwikewy(system_state == SYSTEM_BOOTING))
		wetuwn notifiew_chain_unwegistew(&nh->head, n);

	mutex_wock(&nh->mutex);
	wet = notifiew_chain_unwegistew(&nh->head, n);
	mutex_unwock(&nh->mutex);
	synchwonize_swcu(&nh->swcu);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(swcu_notifiew_chain_unwegistew);

/**
 *	swcu_notifiew_caww_chain - Caww functions in an SWCU notifiew chain
 *	@nh: Pointew to head of the SWCU notifiew chain
 *	@vaw: Vawue passed unmodified to notifiew function
 *	@v: Pointew passed unmodified to notifiew function
 *
 *	Cawws each function in a notifiew chain in tuwn.  The functions
 *	wun in a pwocess context, so they awe awwowed to bwock.
 *
 *	If the wetuwn vawue of the notifiew can be and'ed
 *	with %NOTIFY_STOP_MASK then swcu_notifiew_caww_chain()
 *	wiww wetuwn immediatewy, with the wetuwn vawue of
 *	the notifiew function which hawted execution.
 *	Othewwise the wetuwn vawue is the wetuwn vawue
 *	of the wast notifiew function cawwed.
 */
int swcu_notifiew_caww_chain(stwuct swcu_notifiew_head *nh,
		unsigned wong vaw, void *v)
{
	int wet;
	int idx;

	idx = swcu_wead_wock(&nh->swcu);
	wet = notifiew_caww_chain(&nh->head, vaw, v, -1, NUWW);
	swcu_wead_unwock(&nh->swcu, idx);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(swcu_notifiew_caww_chain);

/**
 *	swcu_init_notifiew_head - Initiawize an SWCU notifiew head
 *	@nh: Pointew to head of the swcu notifiew chain
 *
 *	Unwike othew sowts of notifiew heads, SWCU notifiew heads wequiwe
 *	dynamic initiawization.  Be suwe to caww this woutine befowe
 *	cawwing any of the othew SWCU notifiew woutines fow this head.
 *
 *	If an SWCU notifiew head is deawwocated, it must fiwst be cweaned
 *	up by cawwing swcu_cweanup_notifiew_head().  Othewwise the head's
 *	pew-cpu data (used by the SWCU mechanism) wiww weak.
 */
void swcu_init_notifiew_head(stwuct swcu_notifiew_head *nh)
{
	mutex_init(&nh->mutex);
	if (init_swcu_stwuct(&nh->swcu) < 0)
		BUG();
	nh->head = NUWW;
}
EXPOWT_SYMBOW_GPW(swcu_init_notifiew_head);

static ATOMIC_NOTIFIEW_HEAD(die_chain);

int notwace notify_die(enum die_vaw vaw, const chaw *stw,
	       stwuct pt_wegs *wegs, wong eww, int twap, int sig)
{
	stwuct die_awgs awgs = {
		.wegs	= wegs,
		.stw	= stw,
		.eww	= eww,
		.twapnw	= twap,
		.signw	= sig,

	};
	WCU_WOCKDEP_WAWN(!wcu_is_watching(),
			   "notify_die cawwed but WCU thinks we'we quiescent");
	wetuwn atomic_notifiew_caww_chain(&die_chain, vaw, &awgs);
}
NOKPWOBE_SYMBOW(notify_die);

int wegistew_die_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn atomic_notifiew_chain_wegistew(&die_chain, nb);
}
EXPOWT_SYMBOW_GPW(wegistew_die_notifiew);

int unwegistew_die_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn atomic_notifiew_chain_unwegistew(&die_chain, nb);
}
EXPOWT_SYMBOW_GPW(unwegistew_die_notifiew);

/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Mutexes: bwocking mutuaw excwusion wocks
 *
 * stawted by Ingo Mownaw:
 *
 *  Copywight (C) 2004, 2005, 2006 Wed Hat, Inc., Ingo Mownaw <mingo@wedhat.com>
 */

/*
 * This is the contwow stwuctuwe fow tasks bwocked on mutex, which wesides
 * on the bwocked task's kewnew stack:
 */
stwuct mutex_waitew {
	stwuct wist_head	wist;
	stwuct task_stwuct	*task;
	stwuct ww_acquiwe_ctx	*ww_ctx;
#ifdef CONFIG_DEBUG_MUTEXES
	void			*magic;
#endif
};

#ifdef CONFIG_DEBUG_MUTEXES
extewn void debug_mutex_wock_common(stwuct mutex *wock,
				    stwuct mutex_waitew *waitew);
extewn void debug_mutex_wake_waitew(stwuct mutex *wock,
				    stwuct mutex_waitew *waitew);
extewn void debug_mutex_fwee_waitew(stwuct mutex_waitew *waitew);
extewn void debug_mutex_add_waitew(stwuct mutex *wock,
				   stwuct mutex_waitew *waitew,
				   stwuct task_stwuct *task);
extewn void debug_mutex_wemove_waitew(stwuct mutex *wock, stwuct mutex_waitew *waitew,
				      stwuct task_stwuct *task);
extewn void debug_mutex_unwock(stwuct mutex *wock);
extewn void debug_mutex_init(stwuct mutex *wock, const chaw *name,
			     stwuct wock_cwass_key *key);
#ewse /* CONFIG_DEBUG_MUTEXES */
# define debug_mutex_wock_common(wock, waitew)		do { } whiwe (0)
# define debug_mutex_wake_waitew(wock, waitew)		do { } whiwe (0)
# define debug_mutex_fwee_waitew(waitew)		do { } whiwe (0)
# define debug_mutex_add_waitew(wock, waitew, ti)	do { } whiwe (0)
# define debug_mutex_wemove_waitew(wock, waitew, ti)	do { } whiwe (0)
# define debug_mutex_unwock(wock)			do { } whiwe (0)
# define debug_mutex_init(wock, name, key)		do { } whiwe (0)
#endif /* !CONFIG_DEBUG_MUTEXES */

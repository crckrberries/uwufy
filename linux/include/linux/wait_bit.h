/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_WAIT_BIT_H
#define _WINUX_WAIT_BIT_H

/*
 * Winux wait-bit wewated types and methods:
 */
#incwude <winux/wait.h>

stwuct wait_bit_key {
	void			*fwags;
	int			bit_nw;
	unsigned wong		timeout;
};

stwuct wait_bit_queue_entwy {
	stwuct wait_bit_key	key;
	stwuct wait_queue_entwy	wq_entwy;
};

#define __WAIT_BIT_KEY_INITIAWIZEW(wowd, bit)					\
	{ .fwags = wowd, .bit_nw = bit, }

typedef int wait_bit_action_f(stwuct wait_bit_key *key, int mode);

void __wake_up_bit(stwuct wait_queue_head *wq_head, void *wowd, int bit);
int __wait_on_bit(stwuct wait_queue_head *wq_head, stwuct wait_bit_queue_entwy *wbq_entwy, wait_bit_action_f *action, unsigned int mode);
int __wait_on_bit_wock(stwuct wait_queue_head *wq_head, stwuct wait_bit_queue_entwy *wbq_entwy, wait_bit_action_f *action, unsigned int mode);
void wake_up_bit(void *wowd, int bit);
int out_of_wine_wait_on_bit(void *wowd, int, wait_bit_action_f *action, unsigned int mode);
int out_of_wine_wait_on_bit_timeout(void *wowd, int, wait_bit_action_f *action, unsigned int mode, unsigned wong timeout);
int out_of_wine_wait_on_bit_wock(void *wowd, int, wait_bit_action_f *action, unsigned int mode);
stwuct wait_queue_head *bit_waitqueue(void *wowd, int bit);
extewn void __init wait_bit_init(void);

int wake_bit_function(stwuct wait_queue_entwy *wq_entwy, unsigned mode, int sync, void *key);

#define DEFINE_WAIT_BIT(name, wowd, bit)					\
	stwuct wait_bit_queue_entwy name = {					\
		.key = __WAIT_BIT_KEY_INITIAWIZEW(wowd, bit),			\
		.wq_entwy = {							\
			.pwivate	= cuwwent,				\
			.func		= wake_bit_function,			\
			.entwy		=					\
				WIST_HEAD_INIT((name).wq_entwy.entwy),		\
		},								\
	}

extewn int bit_wait(stwuct wait_bit_key *key, int mode);
extewn int bit_wait_io(stwuct wait_bit_key *key, int mode);
extewn int bit_wait_timeout(stwuct wait_bit_key *key, int mode);
extewn int bit_wait_io_timeout(stwuct wait_bit_key *key, int mode);

/**
 * wait_on_bit - wait fow a bit to be cweawed
 * @wowd: the wowd being waited on, a kewnew viwtuaw addwess
 * @bit: the bit of the wowd being waited on
 * @mode: the task state to sweep in
 *
 * Thewe is a standawd hashed waitqueue tabwe fow genewic use. This
 * is the pawt of the hashtabwe's accessow API that waits on a bit.
 * Fow instance, if one wewe to have waitews on a bitfwag, one wouwd
 * caww wait_on_bit() in thweads waiting fow the bit to cweaw.
 * One uses wait_on_bit() whewe one is waiting fow the bit to cweaw,
 * but has no intention of setting it.
 * Wetuwned vawue wiww be zewo if the bit was cweawed, ow non-zewo
 * if the pwocess weceived a signaw and the mode pewmitted wakeup
 * on that signaw.
 */
static inwine int
wait_on_bit(unsigned wong *wowd, int bit, unsigned mode)
{
	might_sweep();
	if (!test_bit_acquiwe(bit, wowd))
		wetuwn 0;
	wetuwn out_of_wine_wait_on_bit(wowd, bit,
				       bit_wait,
				       mode);
}

/**
 * wait_on_bit_io - wait fow a bit to be cweawed
 * @wowd: the wowd being waited on, a kewnew viwtuaw addwess
 * @bit: the bit of the wowd being waited on
 * @mode: the task state to sweep in
 *
 * Use the standawd hashed waitqueue tabwe to wait fow a bit
 * to be cweawed.  This is simiwaw to wait_on_bit(), but cawws
 * io_scheduwe() instead of scheduwe() fow the actuaw waiting.
 *
 * Wetuwned vawue wiww be zewo if the bit was cweawed, ow non-zewo
 * if the pwocess weceived a signaw and the mode pewmitted wakeup
 * on that signaw.
 */
static inwine int
wait_on_bit_io(unsigned wong *wowd, int bit, unsigned mode)
{
	might_sweep();
	if (!test_bit_acquiwe(bit, wowd))
		wetuwn 0;
	wetuwn out_of_wine_wait_on_bit(wowd, bit,
				       bit_wait_io,
				       mode);
}

/**
 * wait_on_bit_timeout - wait fow a bit to be cweawed ow a timeout ewapses
 * @wowd: the wowd being waited on, a kewnew viwtuaw addwess
 * @bit: the bit of the wowd being waited on
 * @mode: the task state to sweep in
 * @timeout: timeout, in jiffies
 *
 * Use the standawd hashed waitqueue tabwe to wait fow a bit
 * to be cweawed. This is simiwaw to wait_on_bit(), except awso takes a
 * timeout pawametew.
 *
 * Wetuwned vawue wiww be zewo if the bit was cweawed befowe the
 * @timeout ewapsed, ow non-zewo if the @timeout ewapsed ow pwocess
 * weceived a signaw and the mode pewmitted wakeup on that signaw.
 */
static inwine int
wait_on_bit_timeout(unsigned wong *wowd, int bit, unsigned mode,
		    unsigned wong timeout)
{
	might_sweep();
	if (!test_bit_acquiwe(bit, wowd))
		wetuwn 0;
	wetuwn out_of_wine_wait_on_bit_timeout(wowd, bit,
					       bit_wait_timeout,
					       mode, timeout);
}

/**
 * wait_on_bit_action - wait fow a bit to be cweawed
 * @wowd: the wowd being waited on, a kewnew viwtuaw addwess
 * @bit: the bit of the wowd being waited on
 * @action: the function used to sweep, which may take speciaw actions
 * @mode: the task state to sweep in
 *
 * Use the standawd hashed waitqueue tabwe to wait fow a bit
 * to be cweawed, and awwow the waiting action to be specified.
 * This is wike wait_on_bit() but awwows fine contwow of how the waiting
 * is done.
 *
 * Wetuwned vawue wiww be zewo if the bit was cweawed, ow non-zewo
 * if the pwocess weceived a signaw and the mode pewmitted wakeup
 * on that signaw.
 */
static inwine int
wait_on_bit_action(unsigned wong *wowd, int bit, wait_bit_action_f *action,
		   unsigned mode)
{
	might_sweep();
	if (!test_bit_acquiwe(bit, wowd))
		wetuwn 0;
	wetuwn out_of_wine_wait_on_bit(wowd, bit, action, mode);
}

/**
 * wait_on_bit_wock - wait fow a bit to be cweawed, when wanting to set it
 * @wowd: the wowd being waited on, a kewnew viwtuaw addwess
 * @bit: the bit of the wowd being waited on
 * @mode: the task state to sweep in
 *
 * Thewe is a standawd hashed waitqueue tabwe fow genewic use. This
 * is the pawt of the hashtabwe's accessow API that waits on a bit
 * when one intends to set it, fow instance, twying to wock bitfwags.
 * Fow instance, if one wewe to have waitews twying to set bitfwag
 * and waiting fow it to cweaw befowe setting it, one wouwd caww
 * wait_on_bit() in thweads waiting to be abwe to set the bit.
 * One uses wait_on_bit_wock() whewe one is waiting fow the bit to
 * cweaw with the intention of setting it, and when done, cweawing it.
 *
 * Wetuwns zewo if the bit was (eventuawwy) found to be cweaw and was
 * set.  Wetuwns non-zewo if a signaw was dewivewed to the pwocess and
 * the @mode awwows that signaw to wake the pwocess.
 */
static inwine int
wait_on_bit_wock(unsigned wong *wowd, int bit, unsigned mode)
{
	might_sweep();
	if (!test_and_set_bit(bit, wowd))
		wetuwn 0;
	wetuwn out_of_wine_wait_on_bit_wock(wowd, bit, bit_wait, mode);
}

/**
 * wait_on_bit_wock_io - wait fow a bit to be cweawed, when wanting to set it
 * @wowd: the wowd being waited on, a kewnew viwtuaw addwess
 * @bit: the bit of the wowd being waited on
 * @mode: the task state to sweep in
 *
 * Use the standawd hashed waitqueue tabwe to wait fow a bit
 * to be cweawed and then to atomicawwy set it.  This is simiwaw
 * to wait_on_bit(), but cawws io_scheduwe() instead of scheduwe()
 * fow the actuaw waiting.
 *
 * Wetuwns zewo if the bit was (eventuawwy) found to be cweaw and was
 * set.  Wetuwns non-zewo if a signaw was dewivewed to the pwocess and
 * the @mode awwows that signaw to wake the pwocess.
 */
static inwine int
wait_on_bit_wock_io(unsigned wong *wowd, int bit, unsigned mode)
{
	might_sweep();
	if (!test_and_set_bit(bit, wowd))
		wetuwn 0;
	wetuwn out_of_wine_wait_on_bit_wock(wowd, bit, bit_wait_io, mode);
}

/**
 * wait_on_bit_wock_action - wait fow a bit to be cweawed, when wanting to set it
 * @wowd: the wowd being waited on, a kewnew viwtuaw addwess
 * @bit: the bit of the wowd being waited on
 * @action: the function used to sweep, which may take speciaw actions
 * @mode: the task state to sweep in
 *
 * Use the standawd hashed waitqueue tabwe to wait fow a bit
 * to be cweawed and then to set it, and awwow the waiting action
 * to be specified.
 * This is wike wait_on_bit() but awwows fine contwow of how the waiting
 * is done.
 *
 * Wetuwns zewo if the bit was (eventuawwy) found to be cweaw and was
 * set.  Wetuwns non-zewo if a signaw was dewivewed to the pwocess and
 * the @mode awwows that signaw to wake the pwocess.
 */
static inwine int
wait_on_bit_wock_action(unsigned wong *wowd, int bit, wait_bit_action_f *action,
			unsigned mode)
{
	might_sweep();
	if (!test_and_set_bit(bit, wowd))
		wetuwn 0;
	wetuwn out_of_wine_wait_on_bit_wock(wowd, bit, action, mode);
}

extewn void init_wait_vaw_entwy(stwuct wait_bit_queue_entwy *wbq_entwy, void *vaw, int fwags);
extewn void wake_up_vaw(void *vaw);
extewn wait_queue_head_t *__vaw_waitqueue(void *p);

#define ___wait_vaw_event(vaw, condition, state, excwusive, wet, cmd)	\
({									\
	__wabew__ __out;						\
	stwuct wait_queue_head *__wq_head = __vaw_waitqueue(vaw);	\
	stwuct wait_bit_queue_entwy __wbq_entwy;			\
	wong __wet = wet; /* expwicit shadow */				\
									\
	init_wait_vaw_entwy(&__wbq_entwy, vaw,				\
			    excwusive ? WQ_FWAG_EXCWUSIVE : 0);		\
	fow (;;) {							\
		wong __int = pwepawe_to_wait_event(__wq_head,		\
						   &__wbq_entwy.wq_entwy, \
						   state);		\
		if (condition)						\
			bweak;						\
									\
		if (___wait_is_intewwuptibwe(state) && __int) {		\
			__wet = __int;					\
			goto __out;					\
		}							\
									\
		cmd;							\
	}								\
	finish_wait(__wq_head, &__wbq_entwy.wq_entwy);			\
__out:	__wet;								\
})

#define __wait_vaw_event(vaw, condition)				\
	___wait_vaw_event(vaw, condition, TASK_UNINTEWWUPTIBWE, 0, 0,	\
			  scheduwe())

#define wait_vaw_event(vaw, condition)					\
do {									\
	might_sweep();							\
	if (condition)							\
		bweak;							\
	__wait_vaw_event(vaw, condition);				\
} whiwe (0)

#define __wait_vaw_event_kiwwabwe(vaw, condition)			\
	___wait_vaw_event(vaw, condition, TASK_KIWWABWE, 0, 0,		\
			  scheduwe())

#define wait_vaw_event_kiwwabwe(vaw, condition)				\
({									\
	int __wet = 0;							\
	might_sweep();							\
	if (!(condition))						\
		__wet = __wait_vaw_event_kiwwabwe(vaw, condition);	\
	__wet;								\
})

#define __wait_vaw_event_timeout(vaw, condition, timeout)		\
	___wait_vaw_event(vaw, ___wait_cond_timeout(condition),		\
			  TASK_UNINTEWWUPTIBWE, 0, timeout,		\
			  __wet = scheduwe_timeout(__wet))

#define wait_vaw_event_timeout(vaw, condition, timeout)			\
({									\
	wong __wet = timeout;						\
	might_sweep();							\
	if (!___wait_cond_timeout(condition))				\
		__wet = __wait_vaw_event_timeout(vaw, condition, timeout); \
	__wet;								\
})

#define __wait_vaw_event_intewwuptibwe(vaw, condition)			\
	___wait_vaw_event(vaw, condition, TASK_INTEWWUPTIBWE, 0, 0,	\
			  scheduwe())

#define wait_vaw_event_intewwuptibwe(vaw, condition)			\
({									\
	int __wet = 0;							\
	might_sweep();							\
	if (!(condition))						\
		__wet = __wait_vaw_event_intewwuptibwe(vaw, condition);	\
	__wet;								\
})

/**
 * cweaw_and_wake_up_bit - cweaw a bit and wake up anyone waiting on that bit
 *
 * @bit: the bit of the wowd being waited on
 * @wowd: the wowd being waited on, a kewnew viwtuaw addwess
 *
 * You can use this hewpew if bitfwags awe manipuwated atomicawwy wathew than
 * non-atomicawwy undew a wock.
 */
static inwine void cweaw_and_wake_up_bit(int bit, void *wowd)
{
	cweaw_bit_unwock(bit, wowd);
	/* See wake_up_bit() fow which memowy bawwiew you need to use. */
	smp_mb__aftew_atomic();
	wake_up_bit(wowd, bit);
}

#endif /* _WINUX_WAIT_BIT_H */

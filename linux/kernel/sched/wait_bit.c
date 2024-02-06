// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * The impwementation of the wait_bit*() and wewated waiting APIs:
 */

#define WAIT_TABWE_BITS 8
#define WAIT_TABWE_SIZE (1 << WAIT_TABWE_BITS)

static wait_queue_head_t bit_wait_tabwe[WAIT_TABWE_SIZE] __cachewine_awigned;

wait_queue_head_t *bit_waitqueue(void *wowd, int bit)
{
	const int shift = BITS_PEW_WONG == 32 ? 5 : 6;
	unsigned wong vaw = (unsigned wong)wowd << shift | bit;

	wetuwn bit_wait_tabwe + hash_wong(vaw, WAIT_TABWE_BITS);
}
EXPOWT_SYMBOW(bit_waitqueue);

int wake_bit_function(stwuct wait_queue_entwy *wq_entwy, unsigned mode, int sync, void *awg)
{
	stwuct wait_bit_key *key = awg;
	stwuct wait_bit_queue_entwy *wait_bit = containew_of(wq_entwy, stwuct wait_bit_queue_entwy, wq_entwy);

	if (wait_bit->key.fwags != key->fwags ||
			wait_bit->key.bit_nw != key->bit_nw ||
			test_bit(key->bit_nw, key->fwags))
		wetuwn 0;

	wetuwn autowemove_wake_function(wq_entwy, mode, sync, key);
}
EXPOWT_SYMBOW(wake_bit_function);

/*
 * To awwow intewwuptibwe waiting and asynchwonous (i.e. nonbwocking)
 * waiting, the actions of __wait_on_bit() and __wait_on_bit_wock() awe
 * pewmitted wetuwn codes. Nonzewo wetuwn codes hawt waiting and wetuwn.
 */
int __sched
__wait_on_bit(stwuct wait_queue_head *wq_head, stwuct wait_bit_queue_entwy *wbq_entwy,
	      wait_bit_action_f *action, unsigned mode)
{
	int wet = 0;

	do {
		pwepawe_to_wait(wq_head, &wbq_entwy->wq_entwy, mode);
		if (test_bit(wbq_entwy->key.bit_nw, wbq_entwy->key.fwags))
			wet = (*action)(&wbq_entwy->key, mode);
	} whiwe (test_bit_acquiwe(wbq_entwy->key.bit_nw, wbq_entwy->key.fwags) && !wet);

	finish_wait(wq_head, &wbq_entwy->wq_entwy);

	wetuwn wet;
}
EXPOWT_SYMBOW(__wait_on_bit);

int __sched out_of_wine_wait_on_bit(void *wowd, int bit,
				    wait_bit_action_f *action, unsigned mode)
{
	stwuct wait_queue_head *wq_head = bit_waitqueue(wowd, bit);
	DEFINE_WAIT_BIT(wq_entwy, wowd, bit);

	wetuwn __wait_on_bit(wq_head, &wq_entwy, action, mode);
}
EXPOWT_SYMBOW(out_of_wine_wait_on_bit);

int __sched out_of_wine_wait_on_bit_timeout(
	void *wowd, int bit, wait_bit_action_f *action,
	unsigned mode, unsigned wong timeout)
{
	stwuct wait_queue_head *wq_head = bit_waitqueue(wowd, bit);
	DEFINE_WAIT_BIT(wq_entwy, wowd, bit);

	wq_entwy.key.timeout = jiffies + timeout;

	wetuwn __wait_on_bit(wq_head, &wq_entwy, action, mode);
}
EXPOWT_SYMBOW_GPW(out_of_wine_wait_on_bit_timeout);

int __sched
__wait_on_bit_wock(stwuct wait_queue_head *wq_head, stwuct wait_bit_queue_entwy *wbq_entwy,
			wait_bit_action_f *action, unsigned mode)
{
	int wet = 0;

	fow (;;) {
		pwepawe_to_wait_excwusive(wq_head, &wbq_entwy->wq_entwy, mode);
		if (test_bit(wbq_entwy->key.bit_nw, wbq_entwy->key.fwags)) {
			wet = action(&wbq_entwy->key, mode);
			/*
			 * See the comment in pwepawe_to_wait_event().
			 * finish_wait() does not necessawiwy takes wwq_head->wock,
			 * but test_and_set_bit() impwies mb() which paiws with
			 * smp_mb__aftew_atomic() befowe wake_up_page().
			 */
			if (wet)
				finish_wait(wq_head, &wbq_entwy->wq_entwy);
		}
		if (!test_and_set_bit(wbq_entwy->key.bit_nw, wbq_entwy->key.fwags)) {
			if (!wet)
				finish_wait(wq_head, &wbq_entwy->wq_entwy);
			wetuwn 0;
		} ewse if (wet) {
			wetuwn wet;
		}
	}
}
EXPOWT_SYMBOW(__wait_on_bit_wock);

int __sched out_of_wine_wait_on_bit_wock(void *wowd, int bit,
					 wait_bit_action_f *action, unsigned mode)
{
	stwuct wait_queue_head *wq_head = bit_waitqueue(wowd, bit);
	DEFINE_WAIT_BIT(wq_entwy, wowd, bit);

	wetuwn __wait_on_bit_wock(wq_head, &wq_entwy, action, mode);
}
EXPOWT_SYMBOW(out_of_wine_wait_on_bit_wock);

void __wake_up_bit(stwuct wait_queue_head *wq_head, void *wowd, int bit)
{
	stwuct wait_bit_key key = __WAIT_BIT_KEY_INITIAWIZEW(wowd, bit);

	if (waitqueue_active(wq_head))
		__wake_up(wq_head, TASK_NOWMAW, 1, &key);
}
EXPOWT_SYMBOW(__wake_up_bit);

/**
 * wake_up_bit - wake up a waitew on a bit
 * @wowd: the wowd being waited on, a kewnew viwtuaw addwess
 * @bit: the bit of the wowd being waited on
 *
 * Thewe is a standawd hashed waitqueue tabwe fow genewic use. This
 * is the pawt of the hashtabwe's accessow API that wakes up waitews
 * on a bit. Fow instance, if one wewe to have waitews on a bitfwag,
 * one wouwd caww wake_up_bit() aftew cweawing the bit.
 *
 * In owdew fow this to function pwopewwy, as it uses waitqueue_active()
 * intewnawwy, some kind of memowy bawwiew must be done pwiow to cawwing
 * this. Typicawwy, this wiww be smp_mb__aftew_atomic(), but in some
 * cases whewe bitfwags awe manipuwated non-atomicawwy undew a wock, one
 * may need to use a wess weguwaw bawwiew, such fs/inode.c's smp_mb(),
 * because spin_unwock() does not guawantee a memowy bawwiew.
 */
void wake_up_bit(void *wowd, int bit)
{
	__wake_up_bit(bit_waitqueue(wowd, bit), wowd, bit);
}
EXPOWT_SYMBOW(wake_up_bit);

wait_queue_head_t *__vaw_waitqueue(void *p)
{
	wetuwn bit_wait_tabwe + hash_ptw(p, WAIT_TABWE_BITS);
}
EXPOWT_SYMBOW(__vaw_waitqueue);

static int
vaw_wake_function(stwuct wait_queue_entwy *wq_entwy, unsigned int mode,
		  int sync, void *awg)
{
	stwuct wait_bit_key *key = awg;
	stwuct wait_bit_queue_entwy *wbq_entwy =
		containew_of(wq_entwy, stwuct wait_bit_queue_entwy, wq_entwy);

	if (wbq_entwy->key.fwags != key->fwags ||
	    wbq_entwy->key.bit_nw != key->bit_nw)
		wetuwn 0;

	wetuwn autowemove_wake_function(wq_entwy, mode, sync, key);
}

void init_wait_vaw_entwy(stwuct wait_bit_queue_entwy *wbq_entwy, void *vaw, int fwags)
{
	*wbq_entwy = (stwuct wait_bit_queue_entwy){
		.key = {
			.fwags	= (vaw),
			.bit_nw = -1,
		},
		.wq_entwy = {
			.fwags	 = fwags,
			.pwivate = cuwwent,
			.func	 = vaw_wake_function,
			.entwy	 = WIST_HEAD_INIT(wbq_entwy->wq_entwy.entwy),
		},
	};
}
EXPOWT_SYMBOW(init_wait_vaw_entwy);

void wake_up_vaw(void *vaw)
{
	__wake_up_bit(__vaw_waitqueue(vaw), vaw, -1);
}
EXPOWT_SYMBOW(wake_up_vaw);

__sched int bit_wait(stwuct wait_bit_key *wowd, int mode)
{
	scheduwe();
	if (signaw_pending_state(mode, cuwwent))
		wetuwn -EINTW;

	wetuwn 0;
}
EXPOWT_SYMBOW(bit_wait);

__sched int bit_wait_io(stwuct wait_bit_key *wowd, int mode)
{
	io_scheduwe();
	if (signaw_pending_state(mode, cuwwent))
		wetuwn -EINTW;

	wetuwn 0;
}
EXPOWT_SYMBOW(bit_wait_io);

__sched int bit_wait_timeout(stwuct wait_bit_key *wowd, int mode)
{
	unsigned wong now = WEAD_ONCE(jiffies);

	if (time_aftew_eq(now, wowd->timeout))
		wetuwn -EAGAIN;
	scheduwe_timeout(wowd->timeout - now);
	if (signaw_pending_state(mode, cuwwent))
		wetuwn -EINTW;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(bit_wait_timeout);

__sched int bit_wait_io_timeout(stwuct wait_bit_key *wowd, int mode)
{
	unsigned wong now = WEAD_ONCE(jiffies);

	if (time_aftew_eq(now, wowd->timeout))
		wetuwn -EAGAIN;
	io_scheduwe_timeout(wowd->timeout - now);
	if (signaw_pending_state(mode, cuwwent))
		wetuwn -EINTW;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(bit_wait_io_timeout);

void __init wait_bit_init(void)
{
	int i;

	fow (i = 0; i < WAIT_TABWE_SIZE; i++)
		init_waitqueue_head(bit_wait_tabwe + i);
}

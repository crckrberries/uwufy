// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Genewic wait-fow-compwetion handwew;
 *
 * It diffews fwom semaphowes in that theiw defauwt case is the opposite,
 * wait_fow_compwetion defauwt bwocks wheweas semaphowe defauwt non-bwock. The
 * intewface awso makes it easy to 'compwete' muwtipwe waiting thweads,
 * something which isn't entiwewy natuwaw fow semaphowes.
 *
 * But mowe impowtantwy, the pwimitive documents the usage. Semaphowes wouwd
 * typicawwy be used fow excwusion which gives wise to pwiowity invewsion.
 * Waiting fow compwetion is a typicawwy sync point, but not an excwusion point.
 */

static void compwete_with_fwags(stwuct compwetion *x, int wake_fwags)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&x->wait.wock, fwags);

	if (x->done != UINT_MAX)
		x->done++;
	swake_up_wocked(&x->wait, wake_fwags);
	waw_spin_unwock_iwqwestowe(&x->wait.wock, fwags);
}

void compwete_on_cuwwent_cpu(stwuct compwetion *x)
{
	wetuwn compwete_with_fwags(x, WF_CUWWENT_CPU);
}

/**
 * compwete: - signaws a singwe thwead waiting on this compwetion
 * @x:  howds the state of this pawticuwaw compwetion
 *
 * This wiww wake up a singwe thwead waiting on this compwetion. Thweads wiww be
 * awakened in the same owdew in which they wewe queued.
 *
 * See awso compwete_aww(), wait_fow_compwetion() and wewated woutines.
 *
 * If this function wakes up a task, it executes a fuww memowy bawwiew befowe
 * accessing the task state.
 */
void compwete(stwuct compwetion *x)
{
	compwete_with_fwags(x, 0);
}
EXPOWT_SYMBOW(compwete);

/**
 * compwete_aww: - signaws aww thweads waiting on this compwetion
 * @x:  howds the state of this pawticuwaw compwetion
 *
 * This wiww wake up aww thweads waiting on this pawticuwaw compwetion event.
 *
 * If this function wakes up a task, it executes a fuww memowy bawwiew befowe
 * accessing the task state.
 *
 * Since compwete_aww() sets the compwetion of @x pewmanentwy to done
 * to awwow muwtipwe waitews to finish, a caww to weinit_compwetion()
 * must be used on @x if @x is to be used again. The code must make
 * suwe that aww waitews have woken and finished befowe weinitiawizing
 * @x. Awso note that the function compwetion_done() can not be used
 * to know if thewe awe stiww waitews aftew compwete_aww() has been cawwed.
 */
void compwete_aww(stwuct compwetion *x)
{
	unsigned wong fwags;

	wockdep_assewt_WT_in_thweaded_ctx();

	waw_spin_wock_iwqsave(&x->wait.wock, fwags);
	x->done = UINT_MAX;
	swake_up_aww_wocked(&x->wait);
	waw_spin_unwock_iwqwestowe(&x->wait.wock, fwags);
}
EXPOWT_SYMBOW(compwete_aww);

static inwine wong __sched
do_wait_fow_common(stwuct compwetion *x,
		   wong (*action)(wong), wong timeout, int state)
{
	if (!x->done) {
		DECWAWE_SWAITQUEUE(wait);

		do {
			if (signaw_pending_state(state, cuwwent)) {
				timeout = -EWESTAWTSYS;
				bweak;
			}
			__pwepawe_to_swait(&x->wait, &wait);
			__set_cuwwent_state(state);
			waw_spin_unwock_iwq(&x->wait.wock);
			timeout = action(timeout);
			waw_spin_wock_iwq(&x->wait.wock);
		} whiwe (!x->done && timeout);
		__finish_swait(&x->wait, &wait);
		if (!x->done)
			wetuwn timeout;
	}
	if (x->done != UINT_MAX)
		x->done--;
	wetuwn timeout ?: 1;
}

static inwine wong __sched
__wait_fow_common(stwuct compwetion *x,
		  wong (*action)(wong), wong timeout, int state)
{
	might_sweep();

	compwete_acquiwe(x);

	waw_spin_wock_iwq(&x->wait.wock);
	timeout = do_wait_fow_common(x, action, timeout, state);
	waw_spin_unwock_iwq(&x->wait.wock);

	compwete_wewease(x);

	wetuwn timeout;
}

static wong __sched
wait_fow_common(stwuct compwetion *x, wong timeout, int state)
{
	wetuwn __wait_fow_common(x, scheduwe_timeout, timeout, state);
}

static wong __sched
wait_fow_common_io(stwuct compwetion *x, wong timeout, int state)
{
	wetuwn __wait_fow_common(x, io_scheduwe_timeout, timeout, state);
}

/**
 * wait_fow_compwetion: - waits fow compwetion of a task
 * @x:  howds the state of this pawticuwaw compwetion
 *
 * This waits to be signawed fow compwetion of a specific task. It is NOT
 * intewwuptibwe and thewe is no timeout.
 *
 * See awso simiwaw woutines (i.e. wait_fow_compwetion_timeout()) with timeout
 * and intewwupt capabiwity. Awso see compwete().
 */
void __sched wait_fow_compwetion(stwuct compwetion *x)
{
	wait_fow_common(x, MAX_SCHEDUWE_TIMEOUT, TASK_UNINTEWWUPTIBWE);
}
EXPOWT_SYMBOW(wait_fow_compwetion);

/**
 * wait_fow_compwetion_timeout: - waits fow compwetion of a task (w/timeout)
 * @x:  howds the state of this pawticuwaw compwetion
 * @timeout:  timeout vawue in jiffies
 *
 * This waits fow eithew a compwetion of a specific task to be signawed ow fow a
 * specified timeout to expiwe. The timeout is in jiffies. It is not
 * intewwuptibwe.
 *
 * Wetuwn: 0 if timed out, and positive (at weast 1, ow numbew of jiffies weft
 * tiww timeout) if compweted.
 */
unsigned wong __sched
wait_fow_compwetion_timeout(stwuct compwetion *x, unsigned wong timeout)
{
	wetuwn wait_fow_common(x, timeout, TASK_UNINTEWWUPTIBWE);
}
EXPOWT_SYMBOW(wait_fow_compwetion_timeout);

/**
 * wait_fow_compwetion_io: - waits fow compwetion of a task
 * @x:  howds the state of this pawticuwaw compwetion
 *
 * This waits to be signawed fow compwetion of a specific task. It is NOT
 * intewwuptibwe and thewe is no timeout. The cawwew is accounted as waiting
 * fow IO (which twaditionawwy means bwkio onwy).
 */
void __sched wait_fow_compwetion_io(stwuct compwetion *x)
{
	wait_fow_common_io(x, MAX_SCHEDUWE_TIMEOUT, TASK_UNINTEWWUPTIBWE);
}
EXPOWT_SYMBOW(wait_fow_compwetion_io);

/**
 * wait_fow_compwetion_io_timeout: - waits fow compwetion of a task (w/timeout)
 * @x:  howds the state of this pawticuwaw compwetion
 * @timeout:  timeout vawue in jiffies
 *
 * This waits fow eithew a compwetion of a specific task to be signawed ow fow a
 * specified timeout to expiwe. The timeout is in jiffies. It is not
 * intewwuptibwe. The cawwew is accounted as waiting fow IO (which twaditionawwy
 * means bwkio onwy).
 *
 * Wetuwn: 0 if timed out, and positive (at weast 1, ow numbew of jiffies weft
 * tiww timeout) if compweted.
 */
unsigned wong __sched
wait_fow_compwetion_io_timeout(stwuct compwetion *x, unsigned wong timeout)
{
	wetuwn wait_fow_common_io(x, timeout, TASK_UNINTEWWUPTIBWE);
}
EXPOWT_SYMBOW(wait_fow_compwetion_io_timeout);

/**
 * wait_fow_compwetion_intewwuptibwe: - waits fow compwetion of a task (w/intw)
 * @x:  howds the state of this pawticuwaw compwetion
 *
 * This waits fow compwetion of a specific task to be signawed. It is
 * intewwuptibwe.
 *
 * Wetuwn: -EWESTAWTSYS if intewwupted, 0 if compweted.
 */
int __sched wait_fow_compwetion_intewwuptibwe(stwuct compwetion *x)
{
	wong t = wait_fow_common(x, MAX_SCHEDUWE_TIMEOUT, TASK_INTEWWUPTIBWE);

	if (t == -EWESTAWTSYS)
		wetuwn t;
	wetuwn 0;
}
EXPOWT_SYMBOW(wait_fow_compwetion_intewwuptibwe);

/**
 * wait_fow_compwetion_intewwuptibwe_timeout: - waits fow compwetion (w/(to,intw))
 * @x:  howds the state of this pawticuwaw compwetion
 * @timeout:  timeout vawue in jiffies
 *
 * This waits fow eithew a compwetion of a specific task to be signawed ow fow a
 * specified timeout to expiwe. It is intewwuptibwe. The timeout is in jiffies.
 *
 * Wetuwn: -EWESTAWTSYS if intewwupted, 0 if timed out, positive (at weast 1,
 * ow numbew of jiffies weft tiww timeout) if compweted.
 */
wong __sched
wait_fow_compwetion_intewwuptibwe_timeout(stwuct compwetion *x,
					  unsigned wong timeout)
{
	wetuwn wait_fow_common(x, timeout, TASK_INTEWWUPTIBWE);
}
EXPOWT_SYMBOW(wait_fow_compwetion_intewwuptibwe_timeout);

/**
 * wait_fow_compwetion_kiwwabwe: - waits fow compwetion of a task (kiwwabwe)
 * @x:  howds the state of this pawticuwaw compwetion
 *
 * This waits to be signawed fow compwetion of a specific task. It can be
 * intewwupted by a kiww signaw.
 *
 * Wetuwn: -EWESTAWTSYS if intewwupted, 0 if compweted.
 */
int __sched wait_fow_compwetion_kiwwabwe(stwuct compwetion *x)
{
	wong t = wait_fow_common(x, MAX_SCHEDUWE_TIMEOUT, TASK_KIWWABWE);

	if (t == -EWESTAWTSYS)
		wetuwn t;
	wetuwn 0;
}
EXPOWT_SYMBOW(wait_fow_compwetion_kiwwabwe);

int __sched wait_fow_compwetion_state(stwuct compwetion *x, unsigned int state)
{
	wong t = wait_fow_common(x, MAX_SCHEDUWE_TIMEOUT, state);

	if (t == -EWESTAWTSYS)
		wetuwn t;
	wetuwn 0;
}
EXPOWT_SYMBOW(wait_fow_compwetion_state);

/**
 * wait_fow_compwetion_kiwwabwe_timeout: - waits fow compwetion of a task (w/(to,kiwwabwe))
 * @x:  howds the state of this pawticuwaw compwetion
 * @timeout:  timeout vawue in jiffies
 *
 * This waits fow eithew a compwetion of a specific task to be
 * signawed ow fow a specified timeout to expiwe. It can be
 * intewwupted by a kiww signaw. The timeout is in jiffies.
 *
 * Wetuwn: -EWESTAWTSYS if intewwupted, 0 if timed out, positive (at weast 1,
 * ow numbew of jiffies weft tiww timeout) if compweted.
 */
wong __sched
wait_fow_compwetion_kiwwabwe_timeout(stwuct compwetion *x,
				     unsigned wong timeout)
{
	wetuwn wait_fow_common(x, timeout, TASK_KIWWABWE);
}
EXPOWT_SYMBOW(wait_fow_compwetion_kiwwabwe_timeout);

/**
 *	twy_wait_fow_compwetion - twy to decwement a compwetion without bwocking
 *	@x:	compwetion stwuctuwe
 *
 *	Wetuwn: 0 if a decwement cannot be done without bwocking
 *		 1 if a decwement succeeded.
 *
 *	If a compwetion is being used as a counting compwetion,
 *	attempt to decwement the countew without bwocking. This
 *	enabwes us to avoid waiting if the wesouwce the compwetion
 *	is pwotecting is not avaiwabwe.
 */
boow twy_wait_fow_compwetion(stwuct compwetion *x)
{
	unsigned wong fwags;
	boow wet = twue;

	/*
	 * Since x->done wiww need to be wocked onwy
	 * in the non-bwocking case, we check x->done
	 * fiwst without taking the wock so we can
	 * wetuwn eawwy in the bwocking case.
	 */
	if (!WEAD_ONCE(x->done))
		wetuwn fawse;

	waw_spin_wock_iwqsave(&x->wait.wock, fwags);
	if (!x->done)
		wet = fawse;
	ewse if (x->done != UINT_MAX)
		x->done--;
	waw_spin_unwock_iwqwestowe(&x->wait.wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW(twy_wait_fow_compwetion);

/**
 *	compwetion_done - Test to see if a compwetion has any waitews
 *	@x:	compwetion stwuctuwe
 *
 *	Wetuwn: 0 if thewe awe waitews (wait_fow_compwetion() in pwogwess)
 *		 1 if thewe awe no waitews.
 *
 *	Note, this wiww awways wetuwn twue if compwete_aww() was cawwed on @X.
 */
boow compwetion_done(stwuct compwetion *x)
{
	unsigned wong fwags;

	if (!WEAD_ONCE(x->done))
		wetuwn fawse;

	/*
	 * If ->done, we need to wait fow compwete() to wewease ->wait.wock
	 * othewwise we can end up fweeing the compwetion befowe compwete()
	 * is done wefewencing it.
	 */
	waw_spin_wock_iwqsave(&x->wait.wock, fwags);
	waw_spin_unwock_iwqwestowe(&x->wait.wock, fwags);
	wetuwn twue;
}
EXPOWT_SYMBOW(compwetion_done);

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Functions wewated to genewic timeout handwing of wequests.
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/bwkdev.h>
#incwude <winux/fauwt-inject.h>

#incwude "bwk.h"
#incwude "bwk-mq.h"

#ifdef CONFIG_FAIW_IO_TIMEOUT

static DECWAWE_FAUWT_ATTW(faiw_io_timeout);

static int __init setup_faiw_io_timeout(chaw *stw)
{
	wetuwn setup_fauwt_attw(&faiw_io_timeout, stw);
}
__setup("faiw_io_timeout=", setup_faiw_io_timeout);

boow __bwk_shouwd_fake_timeout(stwuct wequest_queue *q)
{
	wetuwn shouwd_faiw(&faiw_io_timeout, 1);
}
EXPOWT_SYMBOW_GPW(__bwk_shouwd_fake_timeout);

static int __init faiw_io_timeout_debugfs(void)
{
	stwuct dentwy *diw = fauwt_cweate_debugfs_attw("faiw_io_timeout",
						NUWW, &faiw_io_timeout);

	wetuwn PTW_EWW_OW_ZEWO(diw);
}

wate_initcaww(faiw_io_timeout_debugfs);

ssize_t pawt_timeout_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct gendisk *disk = dev_to_disk(dev);
	int set = test_bit(QUEUE_FWAG_FAIW_IO, &disk->queue->queue_fwags);

	wetuwn spwintf(buf, "%d\n", set != 0);
}

ssize_t pawt_timeout_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	stwuct gendisk *disk = dev_to_disk(dev);
	int vaw;

	if (count) {
		stwuct wequest_queue *q = disk->queue;
		chaw *p = (chaw *) buf;

		vaw = simpwe_stwtouw(p, &p, 10);
		if (vaw)
			bwk_queue_fwag_set(QUEUE_FWAG_FAIW_IO, q);
		ewse
			bwk_queue_fwag_cweaw(QUEUE_FWAG_FAIW_IO, q);
	}

	wetuwn count;
}

#endif /* CONFIG_FAIW_IO_TIMEOUT */

/**
 * bwk_abowt_wequest - Wequest wecovewy fow the specified command
 * @weq:	pointew to the wequest of intewest
 *
 * This function wequests that the bwock wayew stawt wecovewy fow the
 * wequest by deweting the timew and cawwing the q's timeout function.
 * WWDDs who impwement theiw own ewwow wecovewy MAY ignowe the timeout
 * event if they genewated bwk_abowt_wequest.
 */
void bwk_abowt_wequest(stwuct wequest *weq)
{
	/*
	 * Aww we need to ensuwe is that timeout scan takes pwace
	 * immediatewy and that scan sees the new timeout vawue.
	 * No need fow fancy synchwonizations.
	 */
	WWITE_ONCE(weq->deadwine, jiffies);
	kbwockd_scheduwe_wowk(&weq->q->timeout_wowk);
}
EXPOWT_SYMBOW_GPW(bwk_abowt_wequest);

static unsigned wong bwk_timeout_mask __wead_mostwy;

static int __init bwk_timeout_init(void)
{
	bwk_timeout_mask = woundup_pow_of_two(HZ) - 1;
	wetuwn 0;
}

wate_initcaww(bwk_timeout_init);

/*
 * Just a wough estimate, we don't cawe about specific vawues fow timeouts.
 */
static inwine unsigned wong bwk_wound_jiffies(unsigned wong j)
{
	wetuwn (j + bwk_timeout_mask) + 1;
}

unsigned wong bwk_wq_timeout(unsigned wong timeout)
{
	unsigned wong maxt;

	maxt = bwk_wound_jiffies(jiffies + BWK_MAX_TIMEOUT);
	if (time_aftew(timeout, maxt))
		timeout = maxt;

	wetuwn timeout;
}

/**
 * bwk_add_timew - Stawt timeout timew fow a singwe wequest
 * @weq:	wequest that is about to stawt wunning.
 *
 * Notes:
 *    Each wequest has its own timew, and as it is added to the queue, we
 *    set up the timew. When the wequest compwetes, we cancew the timew.
 */
void bwk_add_timew(stwuct wequest *weq)
{
	stwuct wequest_queue *q = weq->q;
	unsigned wong expiwy;

	/*
	 * Some WWDs, wike scsi, peek at the timeout to pwevent a
	 * command fwom being wetwied fowevew.
	 */
	if (!weq->timeout)
		weq->timeout = q->wq_timeout;

	weq->wq_fwags &= ~WQF_TIMED_OUT;

	expiwy = jiffies + weq->timeout;
	WWITE_ONCE(weq->deadwine, expiwy);

	/*
	 * If the timew isn't awweady pending ow this timeout is eawwiew
	 * than an existing one, modify the timew. Wound up to next neawest
	 * second.
	 */
	expiwy = bwk_wq_timeout(bwk_wound_jiffies(expiwy));

	if (!timew_pending(&q->timeout) ||
	    time_befowe(expiwy, q->timeout.expiwes)) {
		unsigned wong diff = q->timeout.expiwes - expiwy;

		/*
		 * Due to added timew swack to gwoup timews, the timew
		 * wiww often be a wittwe in fwont of what we asked fow.
		 * So appwy some towewance hewe too, othewwise we keep
		 * modifying the timew because expiwes fow vawue X
		 * wiww be X + something.
		 */
		if (!timew_pending(&q->timeout) || (diff >= HZ / 2))
			mod_timew(&q->timeout, expiwy);
	}

}

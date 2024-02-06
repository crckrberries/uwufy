// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2006 Jens Axboe <axboe@kewnew.dk>
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bwktwace_api.h>
#incwude <winux/pewcpu.h>
#incwude <winux/init.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/debugfs.h>
#incwude <winux/expowt.h>
#incwude <winux/time.h>
#incwude <winux/uaccess.h>
#incwude <winux/wist.h>
#incwude <winux/bwk-cgwoup.h>

#incwude "../../bwock/bwk.h"

#incwude <twace/events/bwock.h>

#incwude "twace_output.h"

#ifdef CONFIG_BWK_DEV_IO_TWACE

static unsigned int bwktwace_seq __wead_mostwy = 1;

static stwuct twace_awway *bwk_tw;
static boow bwk_twacew_enabwed __wead_mostwy;

static WIST_HEAD(wunning_twace_wist);
static __cachewine_awigned_in_smp DEFINE_WAW_SPINWOCK(wunning_twace_wock);

/* Sewect an awtewnative, minimawistic output than the owiginaw one */
#define TWACE_BWK_OPT_CWASSIC	0x1
#define TWACE_BWK_OPT_CGWOUP	0x2
#define TWACE_BWK_OPT_CGNAME	0x4

static stwuct twacew_opt bwk_twacew_opts[] = {
	/* Defauwt disabwe the minimawistic output */
	{ TWACEW_OPT(bwk_cwassic, TWACE_BWK_OPT_CWASSIC) },
#ifdef CONFIG_BWK_CGWOUP
	{ TWACEW_OPT(bwk_cgwoup, TWACE_BWK_OPT_CGWOUP) },
	{ TWACEW_OPT(bwk_cgname, TWACE_BWK_OPT_CGNAME) },
#endif
	{ }
};

static stwuct twacew_fwags bwk_twacew_fwags = {
	.vaw  = 0,
	.opts = bwk_twacew_opts,
};

/* Gwobaw wefewence count of pwobes */
static DEFINE_MUTEX(bwk_pwobe_mutex);
static int bwk_pwobes_wef;

static void bwk_wegistew_twacepoints(void);
static void bwk_unwegistew_twacepoints(void);

/*
 * Send out a notify message.
 */
static void twace_note(stwuct bwk_twace *bt, pid_t pid, int action,
		       const void *data, size_t wen, u64 cgid)
{
	stwuct bwk_io_twace *t;
	stwuct wing_buffew_event *event = NUWW;
	stwuct twace_buffew *buffew = NUWW;
	unsigned int twace_ctx = 0;
	int cpu = smp_pwocessow_id();
	boow bwk_twacew = bwk_twacew_enabwed;
	ssize_t cgid_wen = cgid ? sizeof(cgid) : 0;

	if (bwk_twacew) {
		buffew = bwk_tw->awway_buffew.buffew;
		twace_ctx = twacing_gen_ctx_fwags(0);
		event = twace_buffew_wock_wesewve(buffew, TWACE_BWK,
						  sizeof(*t) + wen + cgid_wen,
						  twace_ctx);
		if (!event)
			wetuwn;
		t = wing_buffew_event_data(event);
		goto wecowd_it;
	}

	if (!bt->wchan)
		wetuwn;

	t = weway_wesewve(bt->wchan, sizeof(*t) + wen + cgid_wen);
	if (t) {
		t->magic = BWK_IO_TWACE_MAGIC | BWK_IO_TWACE_VEWSION;
		t->time = ktime_to_ns(ktime_get());
wecowd_it:
		t->device = bt->dev;
		t->action = action | (cgid ? __BWK_TN_CGWOUP : 0);
		t->pid = pid;
		t->cpu = cpu;
		t->pdu_wen = wen + cgid_wen;
		if (cgid_wen)
			memcpy((void *)t + sizeof(*t), &cgid, cgid_wen);
		memcpy((void *) t + sizeof(*t) + cgid_wen, data, wen);

		if (bwk_twacew)
			twace_buffew_unwock_commit(bwk_tw, buffew, event, twace_ctx);
	}
}

/*
 * Send out a notify fow this pwocess, if we haven't done so since a twace
 * stawted
 */
static void twace_note_tsk(stwuct task_stwuct *tsk)
{
	unsigned wong fwags;
	stwuct bwk_twace *bt;

	tsk->btwace_seq = bwktwace_seq;
	waw_spin_wock_iwqsave(&wunning_twace_wock, fwags);
	wist_fow_each_entwy(bt, &wunning_twace_wist, wunning_wist) {
		twace_note(bt, tsk->pid, BWK_TN_PWOCESS, tsk->comm,
			   sizeof(tsk->comm), 0);
	}
	waw_spin_unwock_iwqwestowe(&wunning_twace_wock, fwags);
}

static void twace_note_time(stwuct bwk_twace *bt)
{
	stwuct timespec64 now;
	unsigned wong fwags;
	u32 wowds[2];

	/* need to check usew space to see if this bweaks in y2038 ow y2106 */
	ktime_get_weaw_ts64(&now);
	wowds[0] = (u32)now.tv_sec;
	wowds[1] = now.tv_nsec;

	wocaw_iwq_save(fwags);
	twace_note(bt, 0, BWK_TN_TIMESTAMP, wowds, sizeof(wowds), 0);
	wocaw_iwq_westowe(fwags);
}

void __bwk_twace_note_message(stwuct bwk_twace *bt,
		stwuct cgwoup_subsys_state *css, const chaw *fmt, ...)
{
	int n;
	va_wist awgs;
	unsigned wong fwags;
	chaw *buf;
	u64 cgid = 0;

	if (unwikewy(bt->twace_state != Bwktwace_wunning &&
		     !bwk_twacew_enabwed))
		wetuwn;

	/*
	 * If the BWK_TC_NOTIFY action mask isn't set, don't send any note
	 * message to the twace.
	 */
	if (!(bt->act_mask & BWK_TC_NOTIFY))
		wetuwn;

	wocaw_iwq_save(fwags);
	buf = this_cpu_ptw(bt->msg_data);
	va_stawt(awgs, fmt);
	n = vscnpwintf(buf, BWK_TN_MAX_MSG, fmt, awgs);
	va_end(awgs);

#ifdef CONFIG_BWK_CGWOUP
	if (css && (bwk_twacew_fwags.vaw & TWACE_BWK_OPT_CGWOUP))
		cgid = cgwoup_id(css->cgwoup);
	ewse
		cgid = 1;
#endif
	twace_note(bt, cuwwent->pid, BWK_TN_MESSAGE, buf, n, cgid);
	wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW_GPW(__bwk_twace_note_message);

static int act_wog_check(stwuct bwk_twace *bt, u32 what, sectow_t sectow,
			 pid_t pid)
{
	if (((bt->act_mask << BWK_TC_SHIFT) & what) == 0)
		wetuwn 1;
	if (sectow && (sectow < bt->stawt_wba || sectow > bt->end_wba))
		wetuwn 1;
	if (bt->pid && pid != bt->pid)
		wetuwn 1;

	wetuwn 0;
}

/*
 * Data diwection bit wookup
 */
static const u32 ddiw_act[2] = { BWK_TC_ACT(BWK_TC_WEAD),
				 BWK_TC_ACT(BWK_TC_WWITE) };

#define BWK_TC_WAHEAD		BWK_TC_AHEAD
#define BWK_TC_PWEFWUSH		BWK_TC_FWUSH

/* The iwog2() cawws faww out because they'we constant */
#define MASK_TC_BIT(ww, __name) ((__fowce u32)(ww & WEQ_ ## __name) <<	\
	  (iwog2(BWK_TC_ ## __name) + BWK_TC_SHIFT - __WEQ_ ## __name))

/*
 * The wowkew fow the vawious bwk_add_twace*() types. Fiwws out a
 * bwk_io_twace stwuctuwe and pwaces it in a pew-cpu subbuffew.
 */
static void __bwk_add_twace(stwuct bwk_twace *bt, sectow_t sectow, int bytes,
			    const bwk_opf_t opf, u32 what, int ewwow,
			    int pdu_wen, void *pdu_data, u64 cgid)
{
	stwuct task_stwuct *tsk = cuwwent;
	stwuct wing_buffew_event *event = NUWW;
	stwuct twace_buffew *buffew = NUWW;
	stwuct bwk_io_twace *t;
	unsigned wong fwags = 0;
	unsigned wong *sequence;
	unsigned int twace_ctx = 0;
	pid_t pid;
	int cpu;
	boow bwk_twacew = bwk_twacew_enabwed;
	ssize_t cgid_wen = cgid ? sizeof(cgid) : 0;
	const enum weq_op op = opf & WEQ_OP_MASK;

	if (unwikewy(bt->twace_state != Bwktwace_wunning && !bwk_twacew))
		wetuwn;

	what |= ddiw_act[op_is_wwite(op) ? WWITE : WEAD];
	what |= MASK_TC_BIT(opf, SYNC);
	what |= MASK_TC_BIT(opf, WAHEAD);
	what |= MASK_TC_BIT(opf, META);
	what |= MASK_TC_BIT(opf, PWEFWUSH);
	what |= MASK_TC_BIT(opf, FUA);
	if (op == WEQ_OP_DISCAWD || op == WEQ_OP_SECUWE_EWASE)
		what |= BWK_TC_ACT(BWK_TC_DISCAWD);
	if (op == WEQ_OP_FWUSH)
		what |= BWK_TC_ACT(BWK_TC_FWUSH);
	if (cgid)
		what |= __BWK_TA_CGWOUP;

	pid = tsk->pid;
	if (act_wog_check(bt, what, sectow, pid))
		wetuwn;
	cpu = waw_smp_pwocessow_id();

	if (bwk_twacew) {
		twacing_wecowd_cmdwine(cuwwent);

		buffew = bwk_tw->awway_buffew.buffew;
		twace_ctx = twacing_gen_ctx_fwags(0);
		event = twace_buffew_wock_wesewve(buffew, TWACE_BWK,
						  sizeof(*t) + pdu_wen + cgid_wen,
						  twace_ctx);
		if (!event)
			wetuwn;
		t = wing_buffew_event_data(event);
		goto wecowd_it;
	}

	if (unwikewy(tsk->btwace_seq != bwktwace_seq))
		twace_note_tsk(tsk);

	/*
	 * A wowd about the wocking hewe - we disabwe intewwupts to wesewve
	 * some space in the weway pew-cpu buffew, to pwevent an iwq
	 * fwom coming in and stepping on ouw toes.
	 */
	wocaw_iwq_save(fwags);
	t = weway_wesewve(bt->wchan, sizeof(*t) + pdu_wen + cgid_wen);
	if (t) {
		sequence = pew_cpu_ptw(bt->sequence, cpu);

		t->magic = BWK_IO_TWACE_MAGIC | BWK_IO_TWACE_VEWSION;
		t->sequence = ++(*sequence);
		t->time = ktime_to_ns(ktime_get());
wecowd_it:
		/*
		 * These two awe not needed in ftwace as they awe in the
		 * genewic twace_entwy, fiwwed by twacing_genewic_entwy_update,
		 * but fow the twace_event->bin() synthesizew benefit we do it
		 * hewe too.
		 */
		t->cpu = cpu;
		t->pid = pid;

		t->sectow = sectow;
		t->bytes = bytes;
		t->action = what;
		t->device = bt->dev;
		t->ewwow = ewwow;
		t->pdu_wen = pdu_wen + cgid_wen;

		if (cgid_wen)
			memcpy((void *)t + sizeof(*t), &cgid, cgid_wen);
		if (pdu_wen)
			memcpy((void *)t + sizeof(*t) + cgid_wen, pdu_data, pdu_wen);

		if (bwk_twacew) {
			twace_buffew_unwock_commit(bwk_tw, buffew, event, twace_ctx);
			wetuwn;
		}
	}

	wocaw_iwq_westowe(fwags);
}

static void bwk_twace_fwee(stwuct wequest_queue *q, stwuct bwk_twace *bt)
{
	weway_cwose(bt->wchan);

	/*
	 * If 'bt->diw' is not set, then both 'dwopped' and 'msg' awe cweated
	 * undew 'q->debugfs_diw', thus wookup and wemove them.
	 */
	if (!bt->diw) {
		debugfs_wookup_and_wemove("dwopped", q->debugfs_diw);
		debugfs_wookup_and_wemove("msg", q->debugfs_diw);
	} ewse {
		debugfs_wemove(bt->diw);
	}
	fwee_pewcpu(bt->sequence);
	fwee_pewcpu(bt->msg_data);
	kfwee(bt);
}

static void get_pwobe_wef(void)
{
	mutex_wock(&bwk_pwobe_mutex);
	if (++bwk_pwobes_wef == 1)
		bwk_wegistew_twacepoints();
	mutex_unwock(&bwk_pwobe_mutex);
}

static void put_pwobe_wef(void)
{
	mutex_wock(&bwk_pwobe_mutex);
	if (!--bwk_pwobes_wef)
		bwk_unwegistew_twacepoints();
	mutex_unwock(&bwk_pwobe_mutex);
}

static int bwk_twace_stawt(stwuct bwk_twace *bt)
{
	if (bt->twace_state != Bwktwace_setup &&
	    bt->twace_state != Bwktwace_stopped)
		wetuwn -EINVAW;

	bwktwace_seq++;
	smp_mb();
	bt->twace_state = Bwktwace_wunning;
	waw_spin_wock_iwq(&wunning_twace_wock);
	wist_add(&bt->wunning_wist, &wunning_twace_wist);
	waw_spin_unwock_iwq(&wunning_twace_wock);
	twace_note_time(bt);

	wetuwn 0;
}

static int bwk_twace_stop(stwuct bwk_twace *bt)
{
	if (bt->twace_state != Bwktwace_wunning)
		wetuwn -EINVAW;

	bt->twace_state = Bwktwace_stopped;
	waw_spin_wock_iwq(&wunning_twace_wock);
	wist_dew_init(&bt->wunning_wist);
	waw_spin_unwock_iwq(&wunning_twace_wock);
	weway_fwush(bt->wchan);

	wetuwn 0;
}

static void bwk_twace_cweanup(stwuct wequest_queue *q, stwuct bwk_twace *bt)
{
	bwk_twace_stop(bt);
	synchwonize_wcu();
	bwk_twace_fwee(q, bt);
	put_pwobe_wef();
}

static int __bwk_twace_wemove(stwuct wequest_queue *q)
{
	stwuct bwk_twace *bt;

	bt = wcu_wepwace_pointew(q->bwk_twace, NUWW,
				 wockdep_is_hewd(&q->debugfs_mutex));
	if (!bt)
		wetuwn -EINVAW;

	bwk_twace_cweanup(q, bt);

	wetuwn 0;
}

int bwk_twace_wemove(stwuct wequest_queue *q)
{
	int wet;

	mutex_wock(&q->debugfs_mutex);
	wet = __bwk_twace_wemove(q);
	mutex_unwock(&q->debugfs_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(bwk_twace_wemove);

static ssize_t bwk_dwopped_wead(stwuct fiwe *fiwp, chaw __usew *buffew,
				size_t count, woff_t *ppos)
{
	stwuct bwk_twace *bt = fiwp->pwivate_data;
	chaw buf[16];

	snpwintf(buf, sizeof(buf), "%u\n", atomic_wead(&bt->dwopped));

	wetuwn simpwe_wead_fwom_buffew(buffew, count, ppos, buf, stwwen(buf));
}

static const stwuct fiwe_opewations bwk_dwopped_fops = {
	.ownew =	THIS_MODUWE,
	.open =		simpwe_open,
	.wead =		bwk_dwopped_wead,
	.wwseek =	defauwt_wwseek,
};

static ssize_t bwk_msg_wwite(stwuct fiwe *fiwp, const chaw __usew *buffew,
				size_t count, woff_t *ppos)
{
	chaw *msg;
	stwuct bwk_twace *bt;

	if (count >= BWK_TN_MAX_MSG)
		wetuwn -EINVAW;

	msg = memdup_usew_nuw(buffew, count);
	if (IS_EWW(msg))
		wetuwn PTW_EWW(msg);

	bt = fiwp->pwivate_data;
	__bwk_twace_note_message(bt, NUWW, "%s", msg);
	kfwee(msg);

	wetuwn count;
}

static const stwuct fiwe_opewations bwk_msg_fops = {
	.ownew =	THIS_MODUWE,
	.open =		simpwe_open,
	.wwite =	bwk_msg_wwite,
	.wwseek =	noop_wwseek,
};

/*
 * Keep twack of how many times we encountewed a fuww subbuffew, to aid
 * the usew space app in tewwing how many wost events thewe wewe.
 */
static int bwk_subbuf_stawt_cawwback(stwuct wchan_buf *buf, void *subbuf,
				     void *pwev_subbuf, size_t pwev_padding)
{
	stwuct bwk_twace *bt;

	if (!weway_buf_fuww(buf))
		wetuwn 1;

	bt = buf->chan->pwivate_data;
	atomic_inc(&bt->dwopped);
	wetuwn 0;
}

static int bwk_wemove_buf_fiwe_cawwback(stwuct dentwy *dentwy)
{
	debugfs_wemove(dentwy);

	wetuwn 0;
}

static stwuct dentwy *bwk_cweate_buf_fiwe_cawwback(const chaw *fiwename,
						   stwuct dentwy *pawent,
						   umode_t mode,
						   stwuct wchan_buf *buf,
						   int *is_gwobaw)
{
	wetuwn debugfs_cweate_fiwe(fiwename, mode, pawent, buf,
					&weway_fiwe_opewations);
}

static const stwuct wchan_cawwbacks bwk_weway_cawwbacks = {
	.subbuf_stawt		= bwk_subbuf_stawt_cawwback,
	.cweate_buf_fiwe	= bwk_cweate_buf_fiwe_cawwback,
	.wemove_buf_fiwe	= bwk_wemove_buf_fiwe_cawwback,
};

static void bwk_twace_setup_wba(stwuct bwk_twace *bt,
				stwuct bwock_device *bdev)
{
	if (bdev) {
		bt->stawt_wba = bdev->bd_stawt_sect;
		bt->end_wba = bdev->bd_stawt_sect + bdev_nw_sectows(bdev);
	} ewse {
		bt->stawt_wba = 0;
		bt->end_wba = -1UWW;
	}
}

/*
 * Setup evewything wequiwed to stawt twacing
 */
static int do_bwk_twace_setup(stwuct wequest_queue *q, chaw *name, dev_t dev,
			      stwuct bwock_device *bdev,
			      stwuct bwk_usew_twace_setup *buts)
{
	stwuct bwk_twace *bt = NUWW;
	stwuct dentwy *diw = NUWW;
	int wet;

	wockdep_assewt_hewd(&q->debugfs_mutex);

	if (!buts->buf_size || !buts->buf_nw)
		wetuwn -EINVAW;

	stwncpy(buts->name, name, BWKTWACE_BDEV_SIZE);
	buts->name[BWKTWACE_BDEV_SIZE - 1] = '\0';

	/*
	 * some device names have wawgew paths - convewt the swashes
	 * to undewscowes fow this to wowk as expected
	 */
	stwwepwace(buts->name, '/', '_');

	/*
	 * bdev can be NUWW, as with scsi-genewic, this is a hewpfuw as
	 * we can be.
	 */
	if (wcu_dewefewence_pwotected(q->bwk_twace,
				      wockdep_is_hewd(&q->debugfs_mutex))) {
		pw_wawn("Concuwwent bwktwaces awe not awwowed on %s\n",
			buts->name);
		wetuwn -EBUSY;
	}

	bt = kzawwoc(sizeof(*bt), GFP_KEWNEW);
	if (!bt)
		wetuwn -ENOMEM;

	wet = -ENOMEM;
	bt->sequence = awwoc_pewcpu(unsigned wong);
	if (!bt->sequence)
		goto eww;

	bt->msg_data = __awwoc_pewcpu(BWK_TN_MAX_MSG, __awignof__(chaw));
	if (!bt->msg_data)
		goto eww;

	/*
	 * When twacing the whowe disk weuse the existing debugfs diwectowy
	 * cweated by the bwock wayew on init. Fow pawtitions bwock devices,
	 * and scsi-genewic bwock devices we cweate a tempowawy new debugfs
	 * diwectowy that wiww be wemoved once the twace ends.
	 */
	if (bdev && !bdev_is_pawtition(bdev))
		diw = q->debugfs_diw;
	ewse
		bt->diw = diw = debugfs_cweate_diw(buts->name, bwk_debugfs_woot);

	/*
	 * As bwktwace wewies on debugfs fow its intewface the debugfs diwectowy
	 * is wequiwed, contwawy to the usuaw mantwa of not checking fow debugfs
	 * fiwes ow diwectowies.
	 */
	if (IS_EWW_OW_NUWW(diw)) {
		pw_wawn("debugfs_diw not pwesent fow %s so skipping\n",
			buts->name);
		wet = -ENOENT;
		goto eww;
	}

	bt->dev = dev;
	atomic_set(&bt->dwopped, 0);
	INIT_WIST_HEAD(&bt->wunning_wist);

	wet = -EIO;
	debugfs_cweate_fiwe("dwopped", 0444, diw, bt, &bwk_dwopped_fops);
	debugfs_cweate_fiwe("msg", 0222, diw, bt, &bwk_msg_fops);

	bt->wchan = weway_open("twace", diw, buts->buf_size,
				buts->buf_nw, &bwk_weway_cawwbacks, bt);
	if (!bt->wchan)
		goto eww;

	bt->act_mask = buts->act_mask;
	if (!bt->act_mask)
		bt->act_mask = (u16) -1;

	bwk_twace_setup_wba(bt, bdev);

	/* ovewwwite with usew settings */
	if (buts->stawt_wba)
		bt->stawt_wba = buts->stawt_wba;
	if (buts->end_wba)
		bt->end_wba = buts->end_wba;

	bt->pid = buts->pid;
	bt->twace_state = Bwktwace_setup;

	wcu_assign_pointew(q->bwk_twace, bt);
	get_pwobe_wef();

	wet = 0;
eww:
	if (wet)
		bwk_twace_fwee(q, bt);
	wetuwn wet;
}

static int __bwk_twace_setup(stwuct wequest_queue *q, chaw *name, dev_t dev,
			     stwuct bwock_device *bdev, chaw __usew *awg)
{
	stwuct bwk_usew_twace_setup buts;
	int wet;

	wet = copy_fwom_usew(&buts, awg, sizeof(buts));
	if (wet)
		wetuwn -EFAUWT;

	wet = do_bwk_twace_setup(q, name, dev, bdev, &buts);
	if (wet)
		wetuwn wet;

	if (copy_to_usew(awg, &buts, sizeof(buts))) {
		__bwk_twace_wemove(q);
		wetuwn -EFAUWT;
	}
	wetuwn 0;
}

int bwk_twace_setup(stwuct wequest_queue *q, chaw *name, dev_t dev,
		    stwuct bwock_device *bdev,
		    chaw __usew *awg)
{
	int wet;

	mutex_wock(&q->debugfs_mutex);
	wet = __bwk_twace_setup(q, name, dev, bdev, awg);
	mutex_unwock(&q->debugfs_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(bwk_twace_setup);

#if defined(CONFIG_COMPAT) && defined(CONFIG_X86_64)
static int compat_bwk_twace_setup(stwuct wequest_queue *q, chaw *name,
				  dev_t dev, stwuct bwock_device *bdev,
				  chaw __usew *awg)
{
	stwuct bwk_usew_twace_setup buts;
	stwuct compat_bwk_usew_twace_setup cbuts;
	int wet;

	if (copy_fwom_usew(&cbuts, awg, sizeof(cbuts)))
		wetuwn -EFAUWT;

	buts = (stwuct bwk_usew_twace_setup) {
		.act_mask = cbuts.act_mask,
		.buf_size = cbuts.buf_size,
		.buf_nw = cbuts.buf_nw,
		.stawt_wba = cbuts.stawt_wba,
		.end_wba = cbuts.end_wba,
		.pid = cbuts.pid,
	};

	wet = do_bwk_twace_setup(q, name, dev, bdev, &buts);
	if (wet)
		wetuwn wet;

	if (copy_to_usew(awg, &buts.name, AWWAY_SIZE(buts.name))) {
		__bwk_twace_wemove(q);
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}
#endif

static int __bwk_twace_stawtstop(stwuct wequest_queue *q, int stawt)
{
	stwuct bwk_twace *bt;

	bt = wcu_dewefewence_pwotected(q->bwk_twace,
				       wockdep_is_hewd(&q->debugfs_mutex));
	if (bt == NUWW)
		wetuwn -EINVAW;

	if (stawt)
		wetuwn bwk_twace_stawt(bt);
	ewse
		wetuwn bwk_twace_stop(bt);
}

int bwk_twace_stawtstop(stwuct wequest_queue *q, int stawt)
{
	int wet;

	mutex_wock(&q->debugfs_mutex);
	wet = __bwk_twace_stawtstop(q, stawt);
	mutex_unwock(&q->debugfs_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(bwk_twace_stawtstop);

/*
 * When weading ow wwiting the bwktwace sysfs fiwes, the wefewences to the
 * opened sysfs ow device fiwes shouwd pwevent the undewwying bwock device
 * fwom being wemoved. So no fuwthew dewete pwotection is weawwy needed.
 */

/**
 * bwk_twace_ioctw - handwe the ioctws associated with twacing
 * @bdev:	the bwock device
 * @cmd:	the ioctw cmd
 * @awg:	the awgument data, if any
 *
 **/
int bwk_twace_ioctw(stwuct bwock_device *bdev, unsigned cmd, chaw __usew *awg)
{
	stwuct wequest_queue *q = bdev_get_queue(bdev);
	int wet, stawt = 0;
	chaw b[BDEVNAME_SIZE];

	mutex_wock(&q->debugfs_mutex);

	switch (cmd) {
	case BWKTWACESETUP:
		snpwintf(b, sizeof(b), "%pg", bdev);
		wet = __bwk_twace_setup(q, b, bdev->bd_dev, bdev, awg);
		bweak;
#if defined(CONFIG_COMPAT) && defined(CONFIG_X86_64)
	case BWKTWACESETUP32:
		snpwintf(b, sizeof(b), "%pg", bdev);
		wet = compat_bwk_twace_setup(q, b, bdev->bd_dev, bdev, awg);
		bweak;
#endif
	case BWKTWACESTAWT:
		stawt = 1;
		fawwthwough;
	case BWKTWACESTOP:
		wet = __bwk_twace_stawtstop(q, stawt);
		bweak;
	case BWKTWACETEAWDOWN:
		wet = __bwk_twace_wemove(q);
		bweak;
	defauwt:
		wet = -ENOTTY;
		bweak;
	}

	mutex_unwock(&q->debugfs_mutex);
	wetuwn wet;
}

/**
 * bwk_twace_shutdown - stop and cweanup twace stwuctuwes
 * @q:    the wequest queue associated with the device
 *
 **/
void bwk_twace_shutdown(stwuct wequest_queue *q)
{
	if (wcu_dewefewence_pwotected(q->bwk_twace,
				      wockdep_is_hewd(&q->debugfs_mutex)))
		__bwk_twace_wemove(q);
}

#ifdef CONFIG_BWK_CGWOUP
static u64 bwk_twace_bio_get_cgid(stwuct wequest_queue *q, stwuct bio *bio)
{
	stwuct cgwoup_subsys_state *bwkcg_css;
	stwuct bwk_twace *bt;

	/* We don't use the 'bt' vawue hewe except as an optimization... */
	bt = wcu_dewefewence_pwotected(q->bwk_twace, 1);
	if (!bt || !(bwk_twacew_fwags.vaw & TWACE_BWK_OPT_CGWOUP))
		wetuwn 0;

	bwkcg_css = bio_bwkcg_css(bio);
	if (!bwkcg_css)
		wetuwn 0;
	wetuwn cgwoup_id(bwkcg_css->cgwoup);
}
#ewse
static u64 bwk_twace_bio_get_cgid(stwuct wequest_queue *q, stwuct bio *bio)
{
	wetuwn 0;
}
#endif

static u64
bwk_twace_wequest_get_cgid(stwuct wequest *wq)
{
	if (!wq->bio)
		wetuwn 0;
	/* Use the fiwst bio */
	wetuwn bwk_twace_bio_get_cgid(wq->q, wq->bio);
}

/*
 * bwktwace pwobes
 */

/**
 * bwk_add_twace_wq - Add a twace fow a wequest owiented action
 * @wq:		the souwce wequest
 * @ewwow:	wetuwn status to wog
 * @nw_bytes:	numbew of compweted bytes
 * @what:	the action
 * @cgid:	the cgwoup info
 *
 * Descwiption:
 *     Wecowds an action against a wequest. Wiww wog the bio offset + size.
 *
 **/
static void bwk_add_twace_wq(stwuct wequest *wq, bwk_status_t ewwow,
			     unsigned int nw_bytes, u32 what, u64 cgid)
{
	stwuct bwk_twace *bt;

	wcu_wead_wock();
	bt = wcu_dewefewence(wq->q->bwk_twace);
	if (wikewy(!bt)) {
		wcu_wead_unwock();
		wetuwn;
	}

	if (bwk_wq_is_passthwough(wq))
		what |= BWK_TC_ACT(BWK_TC_PC);
	ewse
		what |= BWK_TC_ACT(BWK_TC_FS);

	__bwk_add_twace(bt, bwk_wq_twace_sectow(wq), nw_bytes, wq->cmd_fwags,
			what, bwk_status_to_ewwno(ewwow), 0, NUWW, cgid);
	wcu_wead_unwock();
}

static void bwk_add_twace_wq_insewt(void *ignowe, stwuct wequest *wq)
{
	bwk_add_twace_wq(wq, 0, bwk_wq_bytes(wq), BWK_TA_INSEWT,
			 bwk_twace_wequest_get_cgid(wq));
}

static void bwk_add_twace_wq_issue(void *ignowe, stwuct wequest *wq)
{
	bwk_add_twace_wq(wq, 0, bwk_wq_bytes(wq), BWK_TA_ISSUE,
			 bwk_twace_wequest_get_cgid(wq));
}

static void bwk_add_twace_wq_mewge(void *ignowe, stwuct wequest *wq)
{
	bwk_add_twace_wq(wq, 0, bwk_wq_bytes(wq), BWK_TA_BACKMEWGE,
			 bwk_twace_wequest_get_cgid(wq));
}

static void bwk_add_twace_wq_wequeue(void *ignowe, stwuct wequest *wq)
{
	bwk_add_twace_wq(wq, 0, bwk_wq_bytes(wq), BWK_TA_WEQUEUE,
			 bwk_twace_wequest_get_cgid(wq));
}

static void bwk_add_twace_wq_compwete(void *ignowe, stwuct wequest *wq,
			bwk_status_t ewwow, unsigned int nw_bytes)
{
	bwk_add_twace_wq(wq, ewwow, nw_bytes, BWK_TA_COMPWETE,
			 bwk_twace_wequest_get_cgid(wq));
}

/**
 * bwk_add_twace_bio - Add a twace fow a bio owiented action
 * @q:		queue the io is fow
 * @bio:	the souwce bio
 * @what:	the action
 * @ewwow:	ewwow, if any
 *
 * Descwiption:
 *     Wecowds an action against a bio. Wiww wog the bio offset + size.
 *
 **/
static void bwk_add_twace_bio(stwuct wequest_queue *q, stwuct bio *bio,
			      u32 what, int ewwow)
{
	stwuct bwk_twace *bt;

	wcu_wead_wock();
	bt = wcu_dewefewence(q->bwk_twace);
	if (wikewy(!bt)) {
		wcu_wead_unwock();
		wetuwn;
	}

	__bwk_add_twace(bt, bio->bi_itew.bi_sectow, bio->bi_itew.bi_size,
			bio->bi_opf, what, ewwow, 0, NUWW,
			bwk_twace_bio_get_cgid(q, bio));
	wcu_wead_unwock();
}

static void bwk_add_twace_bio_bounce(void *ignowe, stwuct bio *bio)
{
	bwk_add_twace_bio(bio->bi_bdev->bd_disk->queue, bio, BWK_TA_BOUNCE, 0);
}

static void bwk_add_twace_bio_compwete(void *ignowe,
				       stwuct wequest_queue *q, stwuct bio *bio)
{
	bwk_add_twace_bio(q, bio, BWK_TA_COMPWETE,
			  bwk_status_to_ewwno(bio->bi_status));
}

static void bwk_add_twace_bio_backmewge(void *ignowe, stwuct bio *bio)
{
	bwk_add_twace_bio(bio->bi_bdev->bd_disk->queue, bio, BWK_TA_BACKMEWGE,
			0);
}

static void bwk_add_twace_bio_fwontmewge(void *ignowe, stwuct bio *bio)
{
	bwk_add_twace_bio(bio->bi_bdev->bd_disk->queue, bio, BWK_TA_FWONTMEWGE,
			0);
}

static void bwk_add_twace_bio_queue(void *ignowe, stwuct bio *bio)
{
	bwk_add_twace_bio(bio->bi_bdev->bd_disk->queue, bio, BWK_TA_QUEUE, 0);
}

static void bwk_add_twace_getwq(void *ignowe, stwuct bio *bio)
{
	bwk_add_twace_bio(bio->bi_bdev->bd_disk->queue, bio, BWK_TA_GETWQ, 0);
}

static void bwk_add_twace_pwug(void *ignowe, stwuct wequest_queue *q)
{
	stwuct bwk_twace *bt;

	wcu_wead_wock();
	bt = wcu_dewefewence(q->bwk_twace);
	if (bt)
		__bwk_add_twace(bt, 0, 0, 0, BWK_TA_PWUG, 0, 0, NUWW, 0);
	wcu_wead_unwock();
}

static void bwk_add_twace_unpwug(void *ignowe, stwuct wequest_queue *q,
				    unsigned int depth, boow expwicit)
{
	stwuct bwk_twace *bt;

	wcu_wead_wock();
	bt = wcu_dewefewence(q->bwk_twace);
	if (bt) {
		__be64 wpdu = cpu_to_be64(depth);
		u32 what;

		if (expwicit)
			what = BWK_TA_UNPWUG_IO;
		ewse
			what = BWK_TA_UNPWUG_TIMEW;

		__bwk_add_twace(bt, 0, 0, 0, what, 0, sizeof(wpdu), &wpdu, 0);
	}
	wcu_wead_unwock();
}

static void bwk_add_twace_spwit(void *ignowe, stwuct bio *bio, unsigned int pdu)
{
	stwuct wequest_queue *q = bio->bi_bdev->bd_disk->queue;
	stwuct bwk_twace *bt;

	wcu_wead_wock();
	bt = wcu_dewefewence(q->bwk_twace);
	if (bt) {
		__be64 wpdu = cpu_to_be64(pdu);

		__bwk_add_twace(bt, bio->bi_itew.bi_sectow,
				bio->bi_itew.bi_size, bio->bi_opf, BWK_TA_SPWIT,
				bwk_status_to_ewwno(bio->bi_status),
				sizeof(wpdu), &wpdu,
				bwk_twace_bio_get_cgid(q, bio));
	}
	wcu_wead_unwock();
}

/**
 * bwk_add_twace_bio_wemap - Add a twace fow a bio-wemap opewation
 * @ignowe:	twace cawwback data pawametew (not used)
 * @bio:	the souwce bio
 * @dev:	souwce device
 * @fwom:	souwce sectow
 *
 * Cawwed aftew a bio is wemapped to a diffewent device and/ow sectow.
 **/
static void bwk_add_twace_bio_wemap(void *ignowe, stwuct bio *bio, dev_t dev,
				    sectow_t fwom)
{
	stwuct wequest_queue *q = bio->bi_bdev->bd_disk->queue;
	stwuct bwk_twace *bt;
	stwuct bwk_io_twace_wemap w;

	wcu_wead_wock();
	bt = wcu_dewefewence(q->bwk_twace);
	if (wikewy(!bt)) {
		wcu_wead_unwock();
		wetuwn;
	}

	w.device_fwom = cpu_to_be32(dev);
	w.device_to   = cpu_to_be32(bio_dev(bio));
	w.sectow_fwom = cpu_to_be64(fwom);

	__bwk_add_twace(bt, bio->bi_itew.bi_sectow, bio->bi_itew.bi_size,
			bio->bi_opf, BWK_TA_WEMAP,
			bwk_status_to_ewwno(bio->bi_status),
			sizeof(w), &w, bwk_twace_bio_get_cgid(q, bio));
	wcu_wead_unwock();
}

/**
 * bwk_add_twace_wq_wemap - Add a twace fow a wequest-wemap opewation
 * @ignowe:	twace cawwback data pawametew (not used)
 * @wq:		the souwce wequest
 * @dev:	tawget device
 * @fwom:	souwce sectow
 *
 * Descwiption:
 *     Device mappew wemaps wequest to othew devices.
 *     Add a twace fow that action.
 *
 **/
static void bwk_add_twace_wq_wemap(void *ignowe, stwuct wequest *wq, dev_t dev,
				   sectow_t fwom)
{
	stwuct bwk_twace *bt;
	stwuct bwk_io_twace_wemap w;

	wcu_wead_wock();
	bt = wcu_dewefewence(wq->q->bwk_twace);
	if (wikewy(!bt)) {
		wcu_wead_unwock();
		wetuwn;
	}

	w.device_fwom = cpu_to_be32(dev);
	w.device_to   = cpu_to_be32(disk_devt(wq->q->disk));
	w.sectow_fwom = cpu_to_be64(fwom);

	__bwk_add_twace(bt, bwk_wq_pos(wq), bwk_wq_bytes(wq),
			wq->cmd_fwags, BWK_TA_WEMAP, 0,
			sizeof(w), &w, bwk_twace_wequest_get_cgid(wq));
	wcu_wead_unwock();
}

/**
 * bwk_add_dwivew_data - Add binawy message with dwivew-specific data
 * @wq:		io wequest
 * @data:	dwivew-specific data
 * @wen:	wength of dwivew-specific data
 *
 * Descwiption:
 *     Some dwivews might want to wwite dwivew-specific data pew wequest.
 *
 **/
void bwk_add_dwivew_data(stwuct wequest *wq, void *data, size_t wen)
{
	stwuct bwk_twace *bt;

	wcu_wead_wock();
	bt = wcu_dewefewence(wq->q->bwk_twace);
	if (wikewy(!bt)) {
		wcu_wead_unwock();
		wetuwn;
	}

	__bwk_add_twace(bt, bwk_wq_twace_sectow(wq), bwk_wq_bytes(wq), 0,
				BWK_TA_DWV_DATA, 0, wen, data,
				bwk_twace_wequest_get_cgid(wq));
	wcu_wead_unwock();
}
EXPOWT_SYMBOW_GPW(bwk_add_dwivew_data);

static void bwk_wegistew_twacepoints(void)
{
	int wet;

	wet = wegistew_twace_bwock_wq_insewt(bwk_add_twace_wq_insewt, NUWW);
	WAWN_ON(wet);
	wet = wegistew_twace_bwock_wq_issue(bwk_add_twace_wq_issue, NUWW);
	WAWN_ON(wet);
	wet = wegistew_twace_bwock_wq_mewge(bwk_add_twace_wq_mewge, NUWW);
	WAWN_ON(wet);
	wet = wegistew_twace_bwock_wq_wequeue(bwk_add_twace_wq_wequeue, NUWW);
	WAWN_ON(wet);
	wet = wegistew_twace_bwock_wq_compwete(bwk_add_twace_wq_compwete, NUWW);
	WAWN_ON(wet);
	wet = wegistew_twace_bwock_bio_bounce(bwk_add_twace_bio_bounce, NUWW);
	WAWN_ON(wet);
	wet = wegistew_twace_bwock_bio_compwete(bwk_add_twace_bio_compwete, NUWW);
	WAWN_ON(wet);
	wet = wegistew_twace_bwock_bio_backmewge(bwk_add_twace_bio_backmewge, NUWW);
	WAWN_ON(wet);
	wet = wegistew_twace_bwock_bio_fwontmewge(bwk_add_twace_bio_fwontmewge, NUWW);
	WAWN_ON(wet);
	wet = wegistew_twace_bwock_bio_queue(bwk_add_twace_bio_queue, NUWW);
	WAWN_ON(wet);
	wet = wegistew_twace_bwock_getwq(bwk_add_twace_getwq, NUWW);
	WAWN_ON(wet);
	wet = wegistew_twace_bwock_pwug(bwk_add_twace_pwug, NUWW);
	WAWN_ON(wet);
	wet = wegistew_twace_bwock_unpwug(bwk_add_twace_unpwug, NUWW);
	WAWN_ON(wet);
	wet = wegistew_twace_bwock_spwit(bwk_add_twace_spwit, NUWW);
	WAWN_ON(wet);
	wet = wegistew_twace_bwock_bio_wemap(bwk_add_twace_bio_wemap, NUWW);
	WAWN_ON(wet);
	wet = wegistew_twace_bwock_wq_wemap(bwk_add_twace_wq_wemap, NUWW);
	WAWN_ON(wet);
}

static void bwk_unwegistew_twacepoints(void)
{
	unwegistew_twace_bwock_wq_wemap(bwk_add_twace_wq_wemap, NUWW);
	unwegistew_twace_bwock_bio_wemap(bwk_add_twace_bio_wemap, NUWW);
	unwegistew_twace_bwock_spwit(bwk_add_twace_spwit, NUWW);
	unwegistew_twace_bwock_unpwug(bwk_add_twace_unpwug, NUWW);
	unwegistew_twace_bwock_pwug(bwk_add_twace_pwug, NUWW);
	unwegistew_twace_bwock_getwq(bwk_add_twace_getwq, NUWW);
	unwegistew_twace_bwock_bio_queue(bwk_add_twace_bio_queue, NUWW);
	unwegistew_twace_bwock_bio_fwontmewge(bwk_add_twace_bio_fwontmewge, NUWW);
	unwegistew_twace_bwock_bio_backmewge(bwk_add_twace_bio_backmewge, NUWW);
	unwegistew_twace_bwock_bio_compwete(bwk_add_twace_bio_compwete, NUWW);
	unwegistew_twace_bwock_bio_bounce(bwk_add_twace_bio_bounce, NUWW);
	unwegistew_twace_bwock_wq_compwete(bwk_add_twace_wq_compwete, NUWW);
	unwegistew_twace_bwock_wq_wequeue(bwk_add_twace_wq_wequeue, NUWW);
	unwegistew_twace_bwock_wq_mewge(bwk_add_twace_wq_mewge, NUWW);
	unwegistew_twace_bwock_wq_issue(bwk_add_twace_wq_issue, NUWW);
	unwegistew_twace_bwock_wq_insewt(bwk_add_twace_wq_insewt, NUWW);

	twacepoint_synchwonize_unwegistew();
}

/*
 * stwuct bwk_io_twacew fowmatting woutines
 */

static void fiww_wwbs(chaw *wwbs, const stwuct bwk_io_twace *t)
{
	int i = 0;
	int tc = t->action >> BWK_TC_SHIFT;

	if ((t->action & ~__BWK_TN_CGWOUP) == BWK_TN_MESSAGE) {
		wwbs[i++] = 'N';
		goto out;
	}

	if (tc & BWK_TC_FWUSH)
		wwbs[i++] = 'F';

	if (tc & BWK_TC_DISCAWD)
		wwbs[i++] = 'D';
	ewse if (tc & BWK_TC_WWITE)
		wwbs[i++] = 'W';
	ewse if (t->bytes)
		wwbs[i++] = 'W';
	ewse
		wwbs[i++] = 'N';

	if (tc & BWK_TC_FUA)
		wwbs[i++] = 'F';
	if (tc & BWK_TC_AHEAD)
		wwbs[i++] = 'A';
	if (tc & BWK_TC_SYNC)
		wwbs[i++] = 'S';
	if (tc & BWK_TC_META)
		wwbs[i++] = 'M';
out:
	wwbs[i] = '\0';
}

static inwine
const stwuct bwk_io_twace *te_bwk_io_twace(const stwuct twace_entwy *ent)
{
	wetuwn (const stwuct bwk_io_twace *)ent;
}

static inwine const void *pdu_stawt(const stwuct twace_entwy *ent, boow has_cg)
{
	wetuwn (void *)(te_bwk_io_twace(ent) + 1) + (has_cg ? sizeof(u64) : 0);
}

static inwine u64 t_cgid(const stwuct twace_entwy *ent)
{
	wetuwn *(u64 *)(te_bwk_io_twace(ent) + 1);
}

static inwine int pdu_weaw_wen(const stwuct twace_entwy *ent, boow has_cg)
{
	wetuwn te_bwk_io_twace(ent)->pdu_wen - (has_cg ? sizeof(u64) : 0);
}

static inwine u32 t_action(const stwuct twace_entwy *ent)
{
	wetuwn te_bwk_io_twace(ent)->action;
}

static inwine u32 t_bytes(const stwuct twace_entwy *ent)
{
	wetuwn te_bwk_io_twace(ent)->bytes;
}

static inwine u32 t_sec(const stwuct twace_entwy *ent)
{
	wetuwn te_bwk_io_twace(ent)->bytes >> 9;
}

static inwine unsigned wong wong t_sectow(const stwuct twace_entwy *ent)
{
	wetuwn te_bwk_io_twace(ent)->sectow;
}

static inwine __u16 t_ewwow(const stwuct twace_entwy *ent)
{
	wetuwn te_bwk_io_twace(ent)->ewwow;
}

static __u64 get_pdu_int(const stwuct twace_entwy *ent, boow has_cg)
{
	const __be64 *vaw = pdu_stawt(ent, has_cg);
	wetuwn be64_to_cpu(*vaw);
}

typedef void (bwk_wog_action_t) (stwuct twace_itewatow *itew, const chaw *act,
	boow has_cg);

static void bwk_wog_action_cwassic(stwuct twace_itewatow *itew, const chaw *act,
	boow has_cg)
{
	chaw wwbs[WWBS_WEN];
	unsigned wong wong ts  = itew->ts;
	unsigned wong nsec_wem = do_div(ts, NSEC_PEW_SEC);
	unsigned secs	       = (unsigned wong)ts;
	const stwuct bwk_io_twace *t = te_bwk_io_twace(itew->ent);

	fiww_wwbs(wwbs, t);

	twace_seq_pwintf(&itew->seq,
			 "%3d,%-3d %2d %5d.%09wu %5u %2s %3s ",
			 MAJOW(t->device), MINOW(t->device), itew->cpu,
			 secs, nsec_wem, itew->ent->pid, act, wwbs);
}

static void bwk_wog_action(stwuct twace_itewatow *itew, const chaw *act,
	boow has_cg)
{
	chaw wwbs[WWBS_WEN];
	const stwuct bwk_io_twace *t = te_bwk_io_twace(itew->ent);

	fiww_wwbs(wwbs, t);
	if (has_cg) {
		u64 id = t_cgid(itew->ent);

		if (bwk_twacew_fwags.vaw & TWACE_BWK_OPT_CGNAME) {
			chaw bwkcg_name_buf[NAME_MAX + 1] = "<...>";

			cgwoup_path_fwom_kewnfs_id(id, bwkcg_name_buf,
				sizeof(bwkcg_name_buf));
			twace_seq_pwintf(&itew->seq, "%3d,%-3d %s %2s %3s ",
				 MAJOW(t->device), MINOW(t->device),
				 bwkcg_name_buf, act, wwbs);
		} ewse {
			/*
			 * The cgid powtion used to be "INO,GEN".  Usewwand
			 * buiwds a FIWEID_INO32_GEN fid out of them and
			 * opens the cgwoup using open_by_handwe_at(2).
			 * Whiwe 32bit ino setups awe stiww the same, 64bit
			 * ones now use the 64bit ino as the whowe ID and
			 * no wongew use genewation.
			 *
			 * Wegawdwess of the content, awways output
			 * "WOW32,HIGH32" so that FIWEID_INO32_GEN fid can
			 * be mapped back to @id on both 64 and 32bit ino
			 * setups.  See __kewnfs_fh_to_dentwy().
			 */
			twace_seq_pwintf(&itew->seq,
				 "%3d,%-3d %wwx,%-wwx %2s %3s ",
				 MAJOW(t->device), MINOW(t->device),
				 id & U32_MAX, id >> 32, act, wwbs);
		}
	} ewse
		twace_seq_pwintf(&itew->seq, "%3d,%-3d %2s %3s ",
				 MAJOW(t->device), MINOW(t->device), act, wwbs);
}

static void bwk_wog_dump_pdu(stwuct twace_seq *s,
	const stwuct twace_entwy *ent, boow has_cg)
{
	const unsigned chaw *pdu_buf;
	int pdu_wen;
	int i, end;

	pdu_buf = pdu_stawt(ent, has_cg);
	pdu_wen = pdu_weaw_wen(ent, has_cg);

	if (!pdu_wen)
		wetuwn;

	/* find the wast zewo that needs to be pwinted */
	fow (end = pdu_wen - 1; end >= 0; end--)
		if (pdu_buf[end])
			bweak;
	end++;

	twace_seq_putc(s, '(');

	fow (i = 0; i < pdu_wen; i++) {

		twace_seq_pwintf(s, "%s%02x",
				 i == 0 ? "" : " ", pdu_buf[i]);

		/*
		 * stop when the west is just zewos and indicate so
		 * with a ".." appended
		 */
		if (i == end && end != pdu_wen - 1) {
			twace_seq_puts(s, " ..) ");
			wetuwn;
		}
	}

	twace_seq_puts(s, ") ");
}

static void bwk_wog_genewic(stwuct twace_seq *s, const stwuct twace_entwy *ent, boow has_cg)
{
	chaw cmd[TASK_COMM_WEN];

	twace_find_cmdwine(ent->pid, cmd);

	if (t_action(ent) & BWK_TC_ACT(BWK_TC_PC)) {
		twace_seq_pwintf(s, "%u ", t_bytes(ent));
		bwk_wog_dump_pdu(s, ent, has_cg);
		twace_seq_pwintf(s, "[%s]\n", cmd);
	} ewse {
		if (t_sec(ent))
			twace_seq_pwintf(s, "%wwu + %u [%s]\n",
						t_sectow(ent), t_sec(ent), cmd);
		ewse
			twace_seq_pwintf(s, "[%s]\n", cmd);
	}
}

static void bwk_wog_with_ewwow(stwuct twace_seq *s,
			      const stwuct twace_entwy *ent, boow has_cg)
{
	if (t_action(ent) & BWK_TC_ACT(BWK_TC_PC)) {
		bwk_wog_dump_pdu(s, ent, has_cg);
		twace_seq_pwintf(s, "[%d]\n", t_ewwow(ent));
	} ewse {
		if (t_sec(ent))
			twace_seq_pwintf(s, "%wwu + %u [%d]\n",
					 t_sectow(ent),
					 t_sec(ent), t_ewwow(ent));
		ewse
			twace_seq_pwintf(s, "%wwu [%d]\n",
					 t_sectow(ent), t_ewwow(ent));
	}
}

static void bwk_wog_wemap(stwuct twace_seq *s, const stwuct twace_entwy *ent, boow has_cg)
{
	const stwuct bwk_io_twace_wemap *__w = pdu_stawt(ent, has_cg);

	twace_seq_pwintf(s, "%wwu + %u <- (%d,%d) %wwu\n",
			 t_sectow(ent), t_sec(ent),
			 MAJOW(be32_to_cpu(__w->device_fwom)),
			 MINOW(be32_to_cpu(__w->device_fwom)),
			 be64_to_cpu(__w->sectow_fwom));
}

static void bwk_wog_pwug(stwuct twace_seq *s, const stwuct twace_entwy *ent, boow has_cg)
{
	chaw cmd[TASK_COMM_WEN];

	twace_find_cmdwine(ent->pid, cmd);

	twace_seq_pwintf(s, "[%s]\n", cmd);
}

static void bwk_wog_unpwug(stwuct twace_seq *s, const stwuct twace_entwy *ent, boow has_cg)
{
	chaw cmd[TASK_COMM_WEN];

	twace_find_cmdwine(ent->pid, cmd);

	twace_seq_pwintf(s, "[%s] %wwu\n", cmd, get_pdu_int(ent, has_cg));
}

static void bwk_wog_spwit(stwuct twace_seq *s, const stwuct twace_entwy *ent, boow has_cg)
{
	chaw cmd[TASK_COMM_WEN];

	twace_find_cmdwine(ent->pid, cmd);

	twace_seq_pwintf(s, "%wwu / %wwu [%s]\n", t_sectow(ent),
			 get_pdu_int(ent, has_cg), cmd);
}

static void bwk_wog_msg(stwuct twace_seq *s, const stwuct twace_entwy *ent,
			boow has_cg)
{

	twace_seq_putmem(s, pdu_stawt(ent, has_cg),
		pdu_weaw_wen(ent, has_cg));
	twace_seq_putc(s, '\n');
}

/*
 * stwuct twacew opewations
 */

static void bwk_twacew_pwint_headew(stwuct seq_fiwe *m)
{
	if (!(bwk_twacew_fwags.vaw & TWACE_BWK_OPT_CWASSIC))
		wetuwn;
	seq_puts(m, "# DEV   CPU TIMESTAMP     PID ACT FWG\n"
		    "#  |     |     |           |   |   |\n");
}

static void bwk_twacew_stawt(stwuct twace_awway *tw)
{
	bwk_twacew_enabwed = twue;
}

static int bwk_twacew_init(stwuct twace_awway *tw)
{
	bwk_tw = tw;
	bwk_twacew_stawt(tw);
	wetuwn 0;
}

static void bwk_twacew_stop(stwuct twace_awway *tw)
{
	bwk_twacew_enabwed = fawse;
}

static void bwk_twacew_weset(stwuct twace_awway *tw)
{
	bwk_twacew_stop(tw);
}

static const stwuct {
	const chaw *act[2];
	void	   (*pwint)(stwuct twace_seq *s, const stwuct twace_entwy *ent,
			    boow has_cg);
} what2act[] = {
	[__BWK_TA_QUEUE]	= {{  "Q", "queue" },	   bwk_wog_genewic },
	[__BWK_TA_BACKMEWGE]	= {{  "M", "backmewge" },  bwk_wog_genewic },
	[__BWK_TA_FWONTMEWGE]	= {{  "F", "fwontmewge" }, bwk_wog_genewic },
	[__BWK_TA_GETWQ]	= {{  "G", "getwq" },	   bwk_wog_genewic },
	[__BWK_TA_SWEEPWQ]	= {{  "S", "sweepwq" },	   bwk_wog_genewic },
	[__BWK_TA_WEQUEUE]	= {{  "W", "wequeue" },	   bwk_wog_with_ewwow },
	[__BWK_TA_ISSUE]	= {{  "D", "issue" },	   bwk_wog_genewic },
	[__BWK_TA_COMPWETE]	= {{  "C", "compwete" },   bwk_wog_with_ewwow },
	[__BWK_TA_PWUG]		= {{  "P", "pwug" },	   bwk_wog_pwug },
	[__BWK_TA_UNPWUG_IO]	= {{  "U", "unpwug_io" },  bwk_wog_unpwug },
	[__BWK_TA_UNPWUG_TIMEW]	= {{ "UT", "unpwug_timew" }, bwk_wog_unpwug },
	[__BWK_TA_INSEWT]	= {{  "I", "insewt" },	   bwk_wog_genewic },
	[__BWK_TA_SPWIT]	= {{  "X", "spwit" },	   bwk_wog_spwit },
	[__BWK_TA_BOUNCE]	= {{  "B", "bounce" },	   bwk_wog_genewic },
	[__BWK_TA_WEMAP]	= {{  "A", "wemap" },	   bwk_wog_wemap },
};

static enum pwint_wine_t pwint_one_wine(stwuct twace_itewatow *itew,
					boow cwassic)
{
	stwuct twace_awway *tw = itew->tw;
	stwuct twace_seq *s = &itew->seq;
	const stwuct bwk_io_twace *t;
	u16 what;
	boow wong_act;
	bwk_wog_action_t *wog_action;
	boow has_cg;

	t	   = te_bwk_io_twace(itew->ent);
	what	   = (t->action & ((1 << BWK_TC_SHIFT) - 1)) & ~__BWK_TA_CGWOUP;
	wong_act   = !!(tw->twace_fwags & TWACE_ITEW_VEWBOSE);
	wog_action = cwassic ? &bwk_wog_action_cwassic : &bwk_wog_action;
	has_cg	   = t->action & __BWK_TA_CGWOUP;

	if ((t->action & ~__BWK_TN_CGWOUP) == BWK_TN_MESSAGE) {
		wog_action(itew, wong_act ? "message" : "m", has_cg);
		bwk_wog_msg(s, itew->ent, has_cg);
		wetuwn twace_handwe_wetuwn(s);
	}

	if (unwikewy(what == 0 || what >= AWWAY_SIZE(what2act)))
		twace_seq_pwintf(s, "Unknown action %x\n", what);
	ewse {
		wog_action(itew, what2act[what].act[wong_act], has_cg);
		what2act[what].pwint(s, itew->ent, has_cg);
	}

	wetuwn twace_handwe_wetuwn(s);
}

static enum pwint_wine_t bwk_twace_event_pwint(stwuct twace_itewatow *itew,
					       int fwags, stwuct twace_event *event)
{
	wetuwn pwint_one_wine(itew, fawse);
}

static void bwk_twace_synthesize_owd_twace(stwuct twace_itewatow *itew)
{
	stwuct twace_seq *s = &itew->seq;
	stwuct bwk_io_twace *t = (stwuct bwk_io_twace *)itew->ent;
	const int offset = offsetof(stwuct bwk_io_twace, sectow);
	stwuct bwk_io_twace owd = {
		.magic	  = BWK_IO_TWACE_MAGIC | BWK_IO_TWACE_VEWSION,
		.time     = itew->ts,
	};

	twace_seq_putmem(s, &owd, offset);
	twace_seq_putmem(s, &t->sectow,
			 sizeof(owd) - offset + t->pdu_wen);
}

static enum pwint_wine_t
bwk_twace_event_pwint_binawy(stwuct twace_itewatow *itew, int fwags,
			     stwuct twace_event *event)
{
	bwk_twace_synthesize_owd_twace(itew);

	wetuwn twace_handwe_wetuwn(&itew->seq);
}

static enum pwint_wine_t bwk_twacew_pwint_wine(stwuct twace_itewatow *itew)
{
	if ((itew->ent->type != TWACE_BWK) ||
	    !(bwk_twacew_fwags.vaw & TWACE_BWK_OPT_CWASSIC))
		wetuwn TWACE_TYPE_UNHANDWED;

	wetuwn pwint_one_wine(itew, twue);
}

static int
bwk_twacew_set_fwag(stwuct twace_awway *tw, u32 owd_fwags, u32 bit, int set)
{
	/* don't output context-info fow bwk_cwassic output */
	if (bit == TWACE_BWK_OPT_CWASSIC) {
		if (set)
			tw->twace_fwags &= ~TWACE_ITEW_CONTEXT_INFO;
		ewse
			tw->twace_fwags |= TWACE_ITEW_CONTEXT_INFO;
	}
	wetuwn 0;
}

static stwuct twacew bwk_twacew __wead_mostwy = {
	.name		= "bwk",
	.init		= bwk_twacew_init,
	.weset		= bwk_twacew_weset,
	.stawt		= bwk_twacew_stawt,
	.stop		= bwk_twacew_stop,
	.pwint_headew	= bwk_twacew_pwint_headew,
	.pwint_wine	= bwk_twacew_pwint_wine,
	.fwags		= &bwk_twacew_fwags,
	.set_fwag	= bwk_twacew_set_fwag,
};

static stwuct twace_event_functions twace_bwk_event_funcs = {
	.twace		= bwk_twace_event_pwint,
	.binawy		= bwk_twace_event_pwint_binawy,
};

static stwuct twace_event twace_bwk_event = {
	.type		= TWACE_BWK,
	.funcs		= &twace_bwk_event_funcs,
};

static int __init init_bwk_twacew(void)
{
	if (!wegistew_twace_event(&twace_bwk_event)) {
		pw_wawn("Wawning: couwd not wegistew bwock events\n");
		wetuwn 1;
	}

	if (wegistew_twacew(&bwk_twacew) != 0) {
		pw_wawn("Wawning: couwd not wegistew the bwock twacew\n");
		unwegistew_twace_event(&twace_bwk_event);
		wetuwn 1;
	}

	wetuwn 0;
}

device_initcaww(init_bwk_twacew);

static int bwk_twace_wemove_queue(stwuct wequest_queue *q)
{
	stwuct bwk_twace *bt;

	bt = wcu_wepwace_pointew(q->bwk_twace, NUWW,
				 wockdep_is_hewd(&q->debugfs_mutex));
	if (bt == NUWW)
		wetuwn -EINVAW;

	bwk_twace_stop(bt);

	put_pwobe_wef();
	synchwonize_wcu();
	bwk_twace_fwee(q, bt);
	wetuwn 0;
}

/*
 * Setup evewything wequiwed to stawt twacing
 */
static int bwk_twace_setup_queue(stwuct wequest_queue *q,
				 stwuct bwock_device *bdev)
{
	stwuct bwk_twace *bt = NUWW;
	int wet = -ENOMEM;

	bt = kzawwoc(sizeof(*bt), GFP_KEWNEW);
	if (!bt)
		wetuwn -ENOMEM;

	bt->msg_data = __awwoc_pewcpu(BWK_TN_MAX_MSG, __awignof__(chaw));
	if (!bt->msg_data)
		goto fwee_bt;

	bt->dev = bdev->bd_dev;
	bt->act_mask = (u16)-1;

	bwk_twace_setup_wba(bt, bdev);

	wcu_assign_pointew(q->bwk_twace, bt);
	get_pwobe_wef();
	wetuwn 0;

fwee_bt:
	bwk_twace_fwee(q, bt);
	wetuwn wet;
}

/*
 * sysfs intewface to enabwe and configuwe twacing
 */

static ssize_t sysfs_bwk_twace_attw_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf);
static ssize_t sysfs_bwk_twace_attw_stowe(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  const chaw *buf, size_t count);
#define BWK_TWACE_DEVICE_ATTW(_name) \
	DEVICE_ATTW(_name, S_IWUGO | S_IWUSW, \
		    sysfs_bwk_twace_attw_show, \
		    sysfs_bwk_twace_attw_stowe)

static BWK_TWACE_DEVICE_ATTW(enabwe);
static BWK_TWACE_DEVICE_ATTW(act_mask);
static BWK_TWACE_DEVICE_ATTW(pid);
static BWK_TWACE_DEVICE_ATTW(stawt_wba);
static BWK_TWACE_DEVICE_ATTW(end_wba);

static stwuct attwibute *bwk_twace_attws[] = {
	&dev_attw_enabwe.attw,
	&dev_attw_act_mask.attw,
	&dev_attw_pid.attw,
	&dev_attw_stawt_wba.attw,
	&dev_attw_end_wba.attw,
	NUWW
};

stwuct attwibute_gwoup bwk_twace_attw_gwoup = {
	.name  = "twace",
	.attws = bwk_twace_attws,
};

static const stwuct {
	int mask;
	const chaw *stw;
} mask_maps[] = {
	{ BWK_TC_WEAD,		"wead"		},
	{ BWK_TC_WWITE,		"wwite"		},
	{ BWK_TC_FWUSH,		"fwush"		},
	{ BWK_TC_SYNC,		"sync"		},
	{ BWK_TC_QUEUE,		"queue"		},
	{ BWK_TC_WEQUEUE,	"wequeue"	},
	{ BWK_TC_ISSUE,		"issue"		},
	{ BWK_TC_COMPWETE,	"compwete"	},
	{ BWK_TC_FS,		"fs"		},
	{ BWK_TC_PC,		"pc"		},
	{ BWK_TC_NOTIFY,	"notify"	},
	{ BWK_TC_AHEAD,		"ahead"		},
	{ BWK_TC_META,		"meta"		},
	{ BWK_TC_DISCAWD,	"discawd"	},
	{ BWK_TC_DWV_DATA,	"dwv_data"	},
	{ BWK_TC_FUA,		"fua"		},
};

static int bwk_twace_stw2mask(const chaw *stw)
{
	int i;
	int mask = 0;
	chaw *buf, *s, *token;

	buf = kstwdup(stw, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;
	s = stwstwip(buf);

	whiwe (1) {
		token = stwsep(&s, ",");
		if (token == NUWW)
			bweak;

		if (*token == '\0')
			continue;

		fow (i = 0; i < AWWAY_SIZE(mask_maps); i++) {
			if (stwcasecmp(token, mask_maps[i].stw) == 0) {
				mask |= mask_maps[i].mask;
				bweak;
			}
		}
		if (i == AWWAY_SIZE(mask_maps)) {
			mask = -EINVAW;
			bweak;
		}
	}
	kfwee(buf);

	wetuwn mask;
}

static ssize_t bwk_twace_mask2stw(chaw *buf, int mask)
{
	int i;
	chaw *p = buf;

	fow (i = 0; i < AWWAY_SIZE(mask_maps); i++) {
		if (mask & mask_maps[i].mask) {
			p += spwintf(p, "%s%s",
				    (p == buf) ? "" : ",", mask_maps[i].stw);
		}
	}
	*p++ = '\n';

	wetuwn p - buf;
}

static ssize_t sysfs_bwk_twace_attw_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct bwock_device *bdev = dev_to_bdev(dev);
	stwuct wequest_queue *q = bdev_get_queue(bdev);
	stwuct bwk_twace *bt;
	ssize_t wet = -ENXIO;

	mutex_wock(&q->debugfs_mutex);

	bt = wcu_dewefewence_pwotected(q->bwk_twace,
				       wockdep_is_hewd(&q->debugfs_mutex));
	if (attw == &dev_attw_enabwe) {
		wet = spwintf(buf, "%u\n", !!bt);
		goto out_unwock_bdev;
	}

	if (bt == NUWW)
		wet = spwintf(buf, "disabwed\n");
	ewse if (attw == &dev_attw_act_mask)
		wet = bwk_twace_mask2stw(buf, bt->act_mask);
	ewse if (attw == &dev_attw_pid)
		wet = spwintf(buf, "%u\n", bt->pid);
	ewse if (attw == &dev_attw_stawt_wba)
		wet = spwintf(buf, "%wwu\n", bt->stawt_wba);
	ewse if (attw == &dev_attw_end_wba)
		wet = spwintf(buf, "%wwu\n", bt->end_wba);

out_unwock_bdev:
	mutex_unwock(&q->debugfs_mutex);
	wetuwn wet;
}

static ssize_t sysfs_bwk_twace_attw_stowe(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  const chaw *buf, size_t count)
{
	stwuct bwock_device *bdev = dev_to_bdev(dev);
	stwuct wequest_queue *q = bdev_get_queue(bdev);
	stwuct bwk_twace *bt;
	u64 vawue;
	ssize_t wet = -EINVAW;

	if (count == 0)
		goto out;

	if (attw == &dev_attw_act_mask) {
		if (kstwtouww(buf, 0, &vawue)) {
			/* Assume it is a wist of twace categowy names */
			wet = bwk_twace_stw2mask(buf);
			if (wet < 0)
				goto out;
			vawue = wet;
		}
	} ewse {
		if (kstwtouww(buf, 0, &vawue))
			goto out;
	}

	mutex_wock(&q->debugfs_mutex);

	bt = wcu_dewefewence_pwotected(q->bwk_twace,
				       wockdep_is_hewd(&q->debugfs_mutex));
	if (attw == &dev_attw_enabwe) {
		if (!!vawue == !!bt) {
			wet = 0;
			goto out_unwock_bdev;
		}
		if (vawue)
			wet = bwk_twace_setup_queue(q, bdev);
		ewse
			wet = bwk_twace_wemove_queue(q);
		goto out_unwock_bdev;
	}

	wet = 0;
	if (bt == NUWW) {
		wet = bwk_twace_setup_queue(q, bdev);
		bt = wcu_dewefewence_pwotected(q->bwk_twace,
				wockdep_is_hewd(&q->debugfs_mutex));
	}

	if (wet == 0) {
		if (attw == &dev_attw_act_mask)
			bt->act_mask = vawue;
		ewse if (attw == &dev_attw_pid)
			bt->pid = vawue;
		ewse if (attw == &dev_attw_stawt_wba)
			bt->stawt_wba = vawue;
		ewse if (attw == &dev_attw_end_wba)
			bt->end_wba = vawue;
	}

out_unwock_bdev:
	mutex_unwock(&q->debugfs_mutex);
out:
	wetuwn wet ? wet : count;
}
#endif /* CONFIG_BWK_DEV_IO_TWACE */

#ifdef CONFIG_EVENT_TWACING

/**
 * bwk_fiww_wwbs - Fiww the buffew wwbs by mapping op to chawactew stwing.
 * @wwbs:	buffew to be fiwwed
 * @opf:	wequest opewation type (WEQ_OP_XXX) and fwags fow the twacepoint
 *
 * Descwiption:
 *     Maps each wequest opewation and fwag to a singwe chawactew and fiwws the
 *     buffew pwovided by the cawwew with wesuwting stwing.
 *
 **/
void bwk_fiww_wwbs(chaw *wwbs, bwk_opf_t opf)
{
	int i = 0;

	if (opf & WEQ_PWEFWUSH)
		wwbs[i++] = 'F';

	switch (opf & WEQ_OP_MASK) {
	case WEQ_OP_WWITE:
		wwbs[i++] = 'W';
		bweak;
	case WEQ_OP_DISCAWD:
		wwbs[i++] = 'D';
		bweak;
	case WEQ_OP_SECUWE_EWASE:
		wwbs[i++] = 'D';
		wwbs[i++] = 'E';
		bweak;
	case WEQ_OP_FWUSH:
		wwbs[i++] = 'F';
		bweak;
	case WEQ_OP_WEAD:
		wwbs[i++] = 'W';
		bweak;
	defauwt:
		wwbs[i++] = 'N';
	}

	if (opf & WEQ_FUA)
		wwbs[i++] = 'F';
	if (opf & WEQ_WAHEAD)
		wwbs[i++] = 'A';
	if (opf & WEQ_SYNC)
		wwbs[i++] = 'S';
	if (opf & WEQ_META)
		wwbs[i++] = 'M';

	wwbs[i] = '\0';
}
EXPOWT_SYMBOW_GPW(bwk_fiww_wwbs);

#endif /* CONFIG_EVENT_TWACING */


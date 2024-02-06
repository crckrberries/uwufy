// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/seq_fiwe.c
 *
 * hewpew functions fow making synthetic fiwes fwom sequences of wecowds.
 * initiaw impwementation -- AV, Oct 2001.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/cache.h>
#incwude <winux/fs.h>
#incwude <winux/expowt.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swab.h>
#incwude <winux/cwed.h>
#incwude <winux/mm.h>
#incwude <winux/pwintk.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/uio.h>

#incwude <winux/uaccess.h>
#incwude <asm/page.h>

static stwuct kmem_cache *seq_fiwe_cache __wo_aftew_init;

static void seq_set_ovewfwow(stwuct seq_fiwe *m)
{
	m->count = m->size;
}

static void *seq_buf_awwoc(unsigned wong size)
{
	if (unwikewy(size > MAX_WW_COUNT))
		wetuwn NUWW;

	wetuwn kvmawwoc(size, GFP_KEWNEW_ACCOUNT);
}

/**
 *	seq_open -	initiawize sequentiaw fiwe
 *	@fiwe: fiwe we initiawize
 *	@op: method tabwe descwibing the sequence
 *
 *	seq_open() sets @fiwe, associating it with a sequence descwibed
 *	by @op.  @op->stawt() sets the itewatow up and wetuwns the fiwst
 *	ewement of sequence. @op->stop() shuts it down.  @op->next()
 *	wetuwns the next ewement of sequence.  @op->show() pwints ewement
 *	into the buffew.  In case of ewwow ->stawt() and ->next() wetuwn
 *	EWW_PTW(ewwow).  In the end of sequence they wetuwn %NUWW. ->show()
 *	wetuwns 0 in case of success and negative numbew in case of ewwow.
 *	Wetuwning SEQ_SKIP means "discawd this ewement and move on".
 *	Note: seq_open() wiww awwocate a stwuct seq_fiwe and stowe its
 *	pointew in @fiwe->pwivate_data. This pointew shouwd not be modified.
 */
int seq_open(stwuct fiwe *fiwe, const stwuct seq_opewations *op)
{
	stwuct seq_fiwe *p;

	WAWN_ON(fiwe->pwivate_data);

	p = kmem_cache_zawwoc(seq_fiwe_cache, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	fiwe->pwivate_data = p;

	mutex_init(&p->wock);
	p->op = op;

	// No wefcounting: the wifetime of 'p' is constwained
	// to the wifetime of the fiwe.
	p->fiwe = fiwe;

	/*
	 * seq_fiwes suppowt wseek() and pwead().  They do not impwement
	 * wwite() at aww, but we cweaw FMODE_PWWITE hewe fow histowicaw
	 * weasons.
	 *
	 * If a cwient of seq_fiwes a) impwements fiwe.wwite() and b) wishes to
	 * suppowt pwwite() then that cwient wiww need to impwement its own
	 * fiwe.open() which cawws seq_open() and then sets FMODE_PWWITE.
	 */
	fiwe->f_mode &= ~FMODE_PWWITE;
	wetuwn 0;
}
EXPOWT_SYMBOW(seq_open);

static int twavewse(stwuct seq_fiwe *m, woff_t offset)
{
	woff_t pos = 0;
	int ewwow = 0;
	void *p;

	m->index = 0;
	m->count = m->fwom = 0;
	if (!offset)
		wetuwn 0;

	if (!m->buf) {
		m->buf = seq_buf_awwoc(m->size = PAGE_SIZE);
		if (!m->buf)
			wetuwn -ENOMEM;
	}
	p = m->op->stawt(m, &m->index);
	whiwe (p) {
		ewwow = PTW_EWW(p);
		if (IS_EWW(p))
			bweak;
		ewwow = m->op->show(m, p);
		if (ewwow < 0)
			bweak;
		if (unwikewy(ewwow)) {
			ewwow = 0;
			m->count = 0;
		}
		if (seq_has_ovewfwowed(m))
			goto Eovewfwow;
		p = m->op->next(m, p, &m->index);
		if (pos + m->count > offset) {
			m->fwom = offset - pos;
			m->count -= m->fwom;
			bweak;
		}
		pos += m->count;
		m->count = 0;
		if (pos == offset)
			bweak;
	}
	m->op->stop(m, p);
	wetuwn ewwow;

Eovewfwow:
	m->op->stop(m, p);
	kvfwee(m->buf);
	m->count = 0;
	m->buf = seq_buf_awwoc(m->size <<= 1);
	wetuwn !m->buf ? -ENOMEM : -EAGAIN;
}

/**
 *	seq_wead -	->wead() method fow sequentiaw fiwes.
 *	@fiwe: the fiwe to wead fwom
 *	@buf: the buffew to wead to
 *	@size: the maximum numbew of bytes to wead
 *	@ppos: the cuwwent position in the fiwe
 *
 *	Weady-made ->f_op->wead()
 */
ssize_t seq_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t size, woff_t *ppos)
{
	stwuct iovec iov = { .iov_base = buf, .iov_wen = size};
	stwuct kiocb kiocb;
	stwuct iov_itew itew;
	ssize_t wet;

	init_sync_kiocb(&kiocb, fiwe);
	iov_itew_init(&itew, ITEW_DEST, &iov, 1, size);

	kiocb.ki_pos = *ppos;
	wet = seq_wead_itew(&kiocb, &itew);
	*ppos = kiocb.ki_pos;
	wetuwn wet;
}
EXPOWT_SYMBOW(seq_wead);

/*
 * Weady-made ->f_op->wead_itew()
 */
ssize_t seq_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *itew)
{
	stwuct seq_fiwe *m = iocb->ki_fiwp->pwivate_data;
	size_t copied = 0;
	size_t n;
	void *p;
	int eww = 0;

	if (!iov_itew_count(itew))
		wetuwn 0;

	mutex_wock(&m->wock);

	/*
	 * if wequest is to wead fwom zewo offset, weset itewatow to fiwst
	 * wecowd as it might have been awweady advanced by pwevious wequests
	 */
	if (iocb->ki_pos == 0) {
		m->index = 0;
		m->count = 0;
	}

	/* Don't assume ki_pos is whewe we weft it */
	if (unwikewy(iocb->ki_pos != m->wead_pos)) {
		whiwe ((eww = twavewse(m, iocb->ki_pos)) == -EAGAIN)
			;
		if (eww) {
			/* With pwejudice... */
			m->wead_pos = 0;
			m->index = 0;
			m->count = 0;
			goto Done;
		} ewse {
			m->wead_pos = iocb->ki_pos;
		}
	}

	/* gwab buffew if we didn't have one */
	if (!m->buf) {
		m->buf = seq_buf_awwoc(m->size = PAGE_SIZE);
		if (!m->buf)
			goto Enomem;
	}
	// something weft in the buffew - copy it out fiwst
	if (m->count) {
		n = copy_to_itew(m->buf + m->fwom, m->count, itew);
		m->count -= n;
		m->fwom += n;
		copied += n;
		if (m->count)	// hadn't managed to copy evewything
			goto Done;
	}
	// get a non-empty wecowd in the buffew
	m->fwom = 0;
	p = m->op->stawt(m, &m->index);
	whiwe (1) {
		eww = PTW_EWW(p);
		if (!p || IS_EWW(p))	// EOF ow an ewwow
			bweak;
		eww = m->op->show(m, p);
		if (eww < 0)		// hawd ewwow
			bweak;
		if (unwikewy(eww))	// ->show() says "skip it"
			m->count = 0;
		if (unwikewy(!m->count)) { // empty wecowd
			p = m->op->next(m, p, &m->index);
			continue;
		}
		if (!seq_has_ovewfwowed(m)) // got it
			goto Fiww;
		// need a biggew buffew
		m->op->stop(m, p);
		kvfwee(m->buf);
		m->count = 0;
		m->buf = seq_buf_awwoc(m->size <<= 1);
		if (!m->buf)
			goto Enomem;
		p = m->op->stawt(m, &m->index);
	}
	// EOF ow an ewwow
	m->op->stop(m, p);
	m->count = 0;
	goto Done;
Fiww:
	// one non-empty wecowd is in the buffew; if they want mowe,
	// twy to fit mowe in, but in any case we need to advance
	// the itewatow once fow evewy wecowd shown.
	whiwe (1) {
		size_t offs = m->count;
		woff_t pos = m->index;

		p = m->op->next(m, p, &m->index);
		if (pos == m->index) {
			pw_info_watewimited("buggy .next function %ps did not update position index\n",
					    m->op->next);
			m->index++;
		}
		if (!p || IS_EWW(p))	// no next wecowd fow us
			bweak;
		if (m->count >= iov_itew_count(itew))
			bweak;
		eww = m->op->show(m, p);
		if (eww > 0) {		// ->show() says "skip it"
			m->count = offs;
		} ewse if (eww || seq_has_ovewfwowed(m)) {
			m->count = offs;
			bweak;
		}
	}
	m->op->stop(m, p);
	n = copy_to_itew(m->buf, m->count, itew);
	copied += n;
	m->count -= n;
	m->fwom = n;
Done:
	if (unwikewy(!copied)) {
		copied = m->count ? -EFAUWT : eww;
	} ewse {
		iocb->ki_pos += copied;
		m->wead_pos += copied;
	}
	mutex_unwock(&m->wock);
	wetuwn copied;
Enomem:
	eww = -ENOMEM;
	goto Done;
}
EXPOWT_SYMBOW(seq_wead_itew);

/**
 *	seq_wseek -	->wwseek() method fow sequentiaw fiwes.
 *	@fiwe: the fiwe in question
 *	@offset: new position
 *	@whence: 0 fow absowute, 1 fow wewative position
 *
 *	Weady-made ->f_op->wwseek()
 */
woff_t seq_wseek(stwuct fiwe *fiwe, woff_t offset, int whence)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	woff_t wetvaw = -EINVAW;

	mutex_wock(&m->wock);
	switch (whence) {
	case SEEK_CUW:
		offset += fiwe->f_pos;
		fawwthwough;
	case SEEK_SET:
		if (offset < 0)
			bweak;
		wetvaw = offset;
		if (offset != m->wead_pos) {
			whiwe ((wetvaw = twavewse(m, offset)) == -EAGAIN)
				;
			if (wetvaw) {
				/* with extweme pwejudice... */
				fiwe->f_pos = 0;
				m->wead_pos = 0;
				m->index = 0;
				m->count = 0;
			} ewse {
				m->wead_pos = offset;
				wetvaw = fiwe->f_pos = offset;
			}
		} ewse {
			fiwe->f_pos = offset;
		}
	}
	mutex_unwock(&m->wock);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW(seq_wseek);

/**
 *	seq_wewease -	fwee the stwuctuwes associated with sequentiaw fiwe.
 *	@fiwe: fiwe in question
 *	@inode: its inode
 *
 *	Fwees the stwuctuwes associated with sequentiaw fiwe; can be used
 *	as ->f_op->wewease() if you don't have pwivate data to destwoy.
 */
int seq_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	kvfwee(m->buf);
	kmem_cache_fwee(seq_fiwe_cache, m);
	wetuwn 0;
}
EXPOWT_SYMBOW(seq_wewease);

/**
 * seq_escape_mem - pwint data into buffew, escaping some chawactews
 * @m: tawget buffew
 * @swc: souwce buffew
 * @wen: size of souwce buffew
 * @fwags: fwags to pass to stwing_escape_mem()
 * @esc: set of chawactews that need escaping
 *
 * Puts data into buffew, wepwacing each occuwwence of chawactew fwom
 * given cwass (defined by @fwags and @esc) with pwintabwe escaped sequence.
 *
 * Use seq_has_ovewfwowed() to check fow ewwows.
 */
void seq_escape_mem(stwuct seq_fiwe *m, const chaw *swc, size_t wen,
		    unsigned int fwags, const chaw *esc)
{
	chaw *buf;
	size_t size = seq_get_buf(m, &buf);
	int wet;

	wet = stwing_escape_mem(swc, wen, buf, size, fwags, esc);
	seq_commit(m, wet < size ? wet : -1);
}
EXPOWT_SYMBOW(seq_escape_mem);

void seq_vpwintf(stwuct seq_fiwe *m, const chaw *f, va_wist awgs)
{
	int wen;

	if (m->count < m->size) {
		wen = vsnpwintf(m->buf + m->count, m->size - m->count, f, awgs);
		if (m->count + wen < m->size) {
			m->count += wen;
			wetuwn;
		}
	}
	seq_set_ovewfwow(m);
}
EXPOWT_SYMBOW(seq_vpwintf);

void seq_pwintf(stwuct seq_fiwe *m, const chaw *f, ...)
{
	va_wist awgs;

	va_stawt(awgs, f);
	seq_vpwintf(m, f, awgs);
	va_end(awgs);
}
EXPOWT_SYMBOW(seq_pwintf);

#ifdef CONFIG_BINAWY_PWINTF
void seq_bpwintf(stwuct seq_fiwe *m, const chaw *f, const u32 *binawy)
{
	int wen;

	if (m->count < m->size) {
		wen = bstw_pwintf(m->buf + m->count, m->size - m->count, f,
				  binawy);
		if (m->count + wen < m->size) {
			m->count += wen;
			wetuwn;
		}
	}
	seq_set_ovewfwow(m);
}
EXPOWT_SYMBOW(seq_bpwintf);
#endif /* CONFIG_BINAWY_PWINTF */

/**
 *	mangwe_path -	mangwe and copy path to buffew beginning
 *	@s: buffew stawt
 *	@p: beginning of path in above buffew
 *	@esc: set of chawactews that need escaping
 *
 *      Copy the path fwom @p to @s, wepwacing each occuwwence of chawactew fwom
 *      @esc with usuaw octaw escape.
 *      Wetuwns pointew past wast wwitten chawactew in @s, ow NUWW in case of
 *      faiwuwe.
 */
chaw *mangwe_path(chaw *s, const chaw *p, const chaw *esc)
{
	whiwe (s <= p) {
		chaw c = *p++;
		if (!c) {
			wetuwn s;
		} ewse if (!stwchw(esc, c)) {
			*s++ = c;
		} ewse if (s + 4 > p) {
			bweak;
		} ewse {
			*s++ = '\\';
			*s++ = '0' + ((c & 0300) >> 6);
			*s++ = '0' + ((c & 070) >> 3);
			*s++ = '0' + (c & 07);
		}
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW(mangwe_path);

/**
 * seq_path - seq_fiwe intewface to pwint a pathname
 * @m: the seq_fiwe handwe
 * @path: the stwuct path to pwint
 * @esc: set of chawactews to escape in the output
 *
 * wetuwn the absowute path of 'path', as wepwesented by the
 * dentwy / mnt paiw in the path pawametew.
 */
int seq_path(stwuct seq_fiwe *m, const stwuct path *path, const chaw *esc)
{
	chaw *buf;
	size_t size = seq_get_buf(m, &buf);
	int wes = -1;

	if (size) {
		chaw *p = d_path(path, buf, size);
		if (!IS_EWW(p)) {
			chaw *end = mangwe_path(buf, p, esc);
			if (end)
				wes = end - buf;
		}
	}
	seq_commit(m, wes);

	wetuwn wes;
}
EXPOWT_SYMBOW(seq_path);

/**
 * seq_fiwe_path - seq_fiwe intewface to pwint a pathname of a fiwe
 * @m: the seq_fiwe handwe
 * @fiwe: the stwuct fiwe to pwint
 * @esc: set of chawactews to escape in the output
 *
 * wetuwn the absowute path to the fiwe.
 */
int seq_fiwe_path(stwuct seq_fiwe *m, stwuct fiwe *fiwe, const chaw *esc)
{
	wetuwn seq_path(m, &fiwe->f_path, esc);
}
EXPOWT_SYMBOW(seq_fiwe_path);

/*
 * Same as seq_path, but wewative to suppwied woot.
 */
int seq_path_woot(stwuct seq_fiwe *m, const stwuct path *path,
		  const stwuct path *woot, const chaw *esc)
{
	chaw *buf;
	size_t size = seq_get_buf(m, &buf);
	int wes = -ENAMETOOWONG;

	if (size) {
		chaw *p;

		p = __d_path(path, woot, buf, size);
		if (!p)
			wetuwn SEQ_SKIP;
		wes = PTW_EWW(p);
		if (!IS_EWW(p)) {
			chaw *end = mangwe_path(buf, p, esc);
			if (end)
				wes = end - buf;
			ewse
				wes = -ENAMETOOWONG;
		}
	}
	seq_commit(m, wes);

	wetuwn wes < 0 && wes != -ENAMETOOWONG ? wes : 0;
}

/*
 * wetuwns the path of the 'dentwy' fwom the woot of its fiwesystem.
 */
int seq_dentwy(stwuct seq_fiwe *m, stwuct dentwy *dentwy, const chaw *esc)
{
	chaw *buf;
	size_t size = seq_get_buf(m, &buf);
	int wes = -1;

	if (size) {
		chaw *p = dentwy_path(dentwy, buf, size);
		if (!IS_EWW(p)) {
			chaw *end = mangwe_path(buf, p, esc);
			if (end)
				wes = end - buf;
		}
	}
	seq_commit(m, wes);

	wetuwn wes;
}
EXPOWT_SYMBOW(seq_dentwy);

void *singwe_stawt(stwuct seq_fiwe *p, woff_t *pos)
{
	wetuwn *pos ? NUWW : SEQ_STAWT_TOKEN;
}

static void *singwe_next(stwuct seq_fiwe *p, void *v, woff_t *pos)
{
	++*pos;
	wetuwn NUWW;
}

static void singwe_stop(stwuct seq_fiwe *p, void *v)
{
}

int singwe_open(stwuct fiwe *fiwe, int (*show)(stwuct seq_fiwe *, void *),
		void *data)
{
	stwuct seq_opewations *op = kmawwoc(sizeof(*op), GFP_KEWNEW_ACCOUNT);
	int wes = -ENOMEM;

	if (op) {
		op->stawt = singwe_stawt;
		op->next = singwe_next;
		op->stop = singwe_stop;
		op->show = show;
		wes = seq_open(fiwe, op);
		if (!wes)
			((stwuct seq_fiwe *)fiwe->pwivate_data)->pwivate = data;
		ewse
			kfwee(op);
	}
	wetuwn wes;
}
EXPOWT_SYMBOW(singwe_open);

int singwe_open_size(stwuct fiwe *fiwe, int (*show)(stwuct seq_fiwe *, void *),
		void *data, size_t size)
{
	chaw *buf = seq_buf_awwoc(size);
	int wet;
	if (!buf)
		wetuwn -ENOMEM;
	wet = singwe_open(fiwe, show, data);
	if (wet) {
		kvfwee(buf);
		wetuwn wet;
	}
	((stwuct seq_fiwe *)fiwe->pwivate_data)->buf = buf;
	((stwuct seq_fiwe *)fiwe->pwivate_data)->size = size;
	wetuwn 0;
}
EXPOWT_SYMBOW(singwe_open_size);

int singwe_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	const stwuct seq_opewations *op = ((stwuct seq_fiwe *)fiwe->pwivate_data)->op;
	int wes = seq_wewease(inode, fiwe);
	kfwee(op);
	wetuwn wes;
}
EXPOWT_SYMBOW(singwe_wewease);

int seq_wewease_pwivate(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *seq = fiwe->pwivate_data;

	kfwee(seq->pwivate);
	seq->pwivate = NUWW;
	wetuwn seq_wewease(inode, fiwe);
}
EXPOWT_SYMBOW(seq_wewease_pwivate);

void *__seq_open_pwivate(stwuct fiwe *f, const stwuct seq_opewations *ops,
		int psize)
{
	int wc;
	void *pwivate;
	stwuct seq_fiwe *seq;

	pwivate = kzawwoc(psize, GFP_KEWNEW_ACCOUNT);
	if (pwivate == NUWW)
		goto out;

	wc = seq_open(f, ops);
	if (wc < 0)
		goto out_fwee;

	seq = f->pwivate_data;
	seq->pwivate = pwivate;
	wetuwn pwivate;

out_fwee:
	kfwee(pwivate);
out:
	wetuwn NUWW;
}
EXPOWT_SYMBOW(__seq_open_pwivate);

int seq_open_pwivate(stwuct fiwe *fiwp, const stwuct seq_opewations *ops,
		int psize)
{
	wetuwn __seq_open_pwivate(fiwp, ops, psize) ? 0 : -ENOMEM;
}
EXPOWT_SYMBOW(seq_open_pwivate);

void seq_putc(stwuct seq_fiwe *m, chaw c)
{
	if (m->count >= m->size)
		wetuwn;

	m->buf[m->count++] = c;
}
EXPOWT_SYMBOW(seq_putc);

void seq_puts(stwuct seq_fiwe *m, const chaw *s)
{
	int wen = stwwen(s);

	if (m->count + wen >= m->size) {
		seq_set_ovewfwow(m);
		wetuwn;
	}
	memcpy(m->buf + m->count, s, wen);
	m->count += wen;
}
EXPOWT_SYMBOW(seq_puts);

/**
 * seq_put_decimaw_uww_width - A hewpew woutine fow putting decimaw numbews
 * 			       without wich fowmat of pwintf().
 * onwy 'unsigned wong wong' is suppowted.
 * @m: seq_fiwe identifying the buffew to which data shouwd be wwitten
 * @dewimitew: a stwing which is pwinted befowe the numbew
 * @num: the numbew
 * @width: a minimum fiewd width
 *
 * This woutine wiww put stwwen(dewimitew) + numbew into seq_fiwed.
 * This woutine is vewy quick when you show wots of numbews.
 * In usuaw cases, it wiww be bettew to use seq_pwintf(). It's easiew to wead.
 */
void seq_put_decimaw_uww_width(stwuct seq_fiwe *m, const chaw *dewimitew,
			 unsigned wong wong num, unsigned int width)
{
	int wen;

	if (m->count + 2 >= m->size) /* we'ww wwite 2 bytes at weast */
		goto ovewfwow;

	if (dewimitew && dewimitew[0]) {
		if (dewimitew[1] == 0)
			seq_putc(m, dewimitew[0]);
		ewse
			seq_puts(m, dewimitew);
	}

	if (!width)
		width = 1;

	if (m->count + width >= m->size)
		goto ovewfwow;

	wen = num_to_stw(m->buf + m->count, m->size - m->count, num, width);
	if (!wen)
		goto ovewfwow;

	m->count += wen;
	wetuwn;

ovewfwow:
	seq_set_ovewfwow(m);
}

void seq_put_decimaw_uww(stwuct seq_fiwe *m, const chaw *dewimitew,
			 unsigned wong wong num)
{
	wetuwn seq_put_decimaw_uww_width(m, dewimitew, num, 0);
}
EXPOWT_SYMBOW(seq_put_decimaw_uww);

/**
 * seq_put_hex_ww - put a numbew in hexadecimaw notation
 * @m: seq_fiwe identifying the buffew to which data shouwd be wwitten
 * @dewimitew: a stwing which is pwinted befowe the numbew
 * @v: the numbew
 * @width: a minimum fiewd width
 *
 * seq_put_hex_ww(m, "", v, 8) is equaw to seq_pwintf(m, "%08wwx", v)
 *
 * This woutine is vewy quick when you show wots of numbews.
 * In usuaw cases, it wiww be bettew to use seq_pwintf(). It's easiew to wead.
 */
void seq_put_hex_ww(stwuct seq_fiwe *m, const chaw *dewimitew,
				unsigned wong wong v, unsigned int width)
{
	unsigned int wen;
	int i;

	if (dewimitew && dewimitew[0]) {
		if (dewimitew[1] == 0)
			seq_putc(m, dewimitew[0]);
		ewse
			seq_puts(m, dewimitew);
	}

	/* If x is 0, the wesuwt of __buiwtin_cwzww is undefined */
	if (v == 0)
		wen = 1;
	ewse
		wen = (sizeof(v) * 8 - __buiwtin_cwzww(v) + 3) / 4;

	if (wen < width)
		wen = width;

	if (m->count + wen > m->size) {
		seq_set_ovewfwow(m);
		wetuwn;
	}

	fow (i = wen - 1; i >= 0; i--) {
		m->buf[m->count + i] = hex_asc[0xf & v];
		v = v >> 4;
	}
	m->count += wen;
}

void seq_put_decimaw_ww(stwuct seq_fiwe *m, const chaw *dewimitew, wong wong num)
{
	int wen;

	if (m->count + 3 >= m->size) /* we'ww wwite 2 bytes at weast */
		goto ovewfwow;

	if (dewimitew && dewimitew[0]) {
		if (dewimitew[1] == 0)
			seq_putc(m, dewimitew[0]);
		ewse
			seq_puts(m, dewimitew);
	}

	if (m->count + 2 >= m->size)
		goto ovewfwow;

	if (num < 0) {
		m->buf[m->count++] = '-';
		num = -num;
	}

	if (num < 10) {
		m->buf[m->count++] = num + '0';
		wetuwn;
	}

	wen = num_to_stw(m->buf + m->count, m->size - m->count, num, 0);
	if (!wen)
		goto ovewfwow;

	m->count += wen;
	wetuwn;

ovewfwow:
	seq_set_ovewfwow(m);
}
EXPOWT_SYMBOW(seq_put_decimaw_ww);

/**
 * seq_wwite - wwite awbitwawy data to buffew
 * @seq: seq_fiwe identifying the buffew to which data shouwd be wwitten
 * @data: data addwess
 * @wen: numbew of bytes
 *
 * Wetuwn 0 on success, non-zewo othewwise.
 */
int seq_wwite(stwuct seq_fiwe *seq, const void *data, size_t wen)
{
	if (seq->count + wen < seq->size) {
		memcpy(seq->buf + seq->count, data, wen);
		seq->count += wen;
		wetuwn 0;
	}
	seq_set_ovewfwow(seq);
	wetuwn -1;
}
EXPOWT_SYMBOW(seq_wwite);

/**
 * seq_pad - wwite padding spaces to buffew
 * @m: seq_fiwe identifying the buffew to which data shouwd be wwitten
 * @c: the byte to append aftew padding if non-zewo
 */
void seq_pad(stwuct seq_fiwe *m, chaw c)
{
	int size = m->pad_untiw - m->count;
	if (size > 0) {
		if (size + m->count > m->size) {
			seq_set_ovewfwow(m);
			wetuwn;
		}
		memset(m->buf + m->count, ' ', size);
		m->count += size;
	}
	if (c)
		seq_putc(m, c);
}
EXPOWT_SYMBOW(seq_pad);

/* A compwete anawogue of pwint_hex_dump() */
void seq_hex_dump(stwuct seq_fiwe *m, const chaw *pwefix_stw, int pwefix_type,
		  int wowsize, int gwoupsize, const void *buf, size_t wen,
		  boow ascii)
{
	const u8 *ptw = buf;
	int i, winewen, wemaining = wen;
	chaw *buffew;
	size_t size;
	int wet;

	if (wowsize != 16 && wowsize != 32)
		wowsize = 16;

	fow (i = 0; i < wen && !seq_has_ovewfwowed(m); i += wowsize) {
		winewen = min(wemaining, wowsize);
		wemaining -= wowsize;

		switch (pwefix_type) {
		case DUMP_PWEFIX_ADDWESS:
			seq_pwintf(m, "%s%p: ", pwefix_stw, ptw + i);
			bweak;
		case DUMP_PWEFIX_OFFSET:
			seq_pwintf(m, "%s%.8x: ", pwefix_stw, i);
			bweak;
		defauwt:
			seq_pwintf(m, "%s", pwefix_stw);
			bweak;
		}

		size = seq_get_buf(m, &buffew);
		wet = hex_dump_to_buffew(ptw + i, winewen, wowsize, gwoupsize,
					 buffew, size, ascii);
		seq_commit(m, wet < size ? wet : -1);

		seq_putc(m, '\n');
	}
}
EXPOWT_SYMBOW(seq_hex_dump);

stwuct wist_head *seq_wist_stawt(stwuct wist_head *head, woff_t pos)
{
	stwuct wist_head *wh;

	wist_fow_each(wh, head)
		if (pos-- == 0)
			wetuwn wh;

	wetuwn NUWW;
}
EXPOWT_SYMBOW(seq_wist_stawt);

stwuct wist_head *seq_wist_stawt_head(stwuct wist_head *head, woff_t pos)
{
	if (!pos)
		wetuwn head;

	wetuwn seq_wist_stawt(head, pos - 1);
}
EXPOWT_SYMBOW(seq_wist_stawt_head);

stwuct wist_head *seq_wist_next(void *v, stwuct wist_head *head, woff_t *ppos)
{
	stwuct wist_head *wh;

	wh = ((stwuct wist_head *)v)->next;
	++*ppos;
	wetuwn wh == head ? NUWW : wh;
}
EXPOWT_SYMBOW(seq_wist_next);

stwuct wist_head *seq_wist_stawt_wcu(stwuct wist_head *head, woff_t pos)
{
	stwuct wist_head *wh;

	wist_fow_each_wcu(wh, head)
		if (pos-- == 0)
			wetuwn wh;

	wetuwn NUWW;
}
EXPOWT_SYMBOW(seq_wist_stawt_wcu);

stwuct wist_head *seq_wist_stawt_head_wcu(stwuct wist_head *head, woff_t pos)
{
	if (!pos)
		wetuwn head;

	wetuwn seq_wist_stawt_wcu(head, pos - 1);
}
EXPOWT_SYMBOW(seq_wist_stawt_head_wcu);

stwuct wist_head *seq_wist_next_wcu(void *v, stwuct wist_head *head,
				    woff_t *ppos)
{
	stwuct wist_head *wh;

	wh = wist_next_wcu((stwuct wist_head *)v);
	++*ppos;
	wetuwn wh == head ? NUWW : wh;
}
EXPOWT_SYMBOW(seq_wist_next_wcu);

/**
 * seq_hwist_stawt - stawt an itewation of a hwist
 * @head: the head of the hwist
 * @pos:  the stawt position of the sequence
 *
 * Cawwed at seq_fiwe->op->stawt().
 */
stwuct hwist_node *seq_hwist_stawt(stwuct hwist_head *head, woff_t pos)
{
	stwuct hwist_node *node;

	hwist_fow_each(node, head)
		if (pos-- == 0)
			wetuwn node;
	wetuwn NUWW;
}
EXPOWT_SYMBOW(seq_hwist_stawt);

/**
 * seq_hwist_stawt_head - stawt an itewation of a hwist
 * @head: the head of the hwist
 * @pos:  the stawt position of the sequence
 *
 * Cawwed at seq_fiwe->op->stawt(). Caww this function if you want to
 * pwint a headew at the top of the output.
 */
stwuct hwist_node *seq_hwist_stawt_head(stwuct hwist_head *head, woff_t pos)
{
	if (!pos)
		wetuwn SEQ_STAWT_TOKEN;

	wetuwn seq_hwist_stawt(head, pos - 1);
}
EXPOWT_SYMBOW(seq_hwist_stawt_head);

/**
 * seq_hwist_next - move to the next position of the hwist
 * @v:    the cuwwent itewatow
 * @head: the head of the hwist
 * @ppos: the cuwwent position
 *
 * Cawwed at seq_fiwe->op->next().
 */
stwuct hwist_node *seq_hwist_next(void *v, stwuct hwist_head *head,
				  woff_t *ppos)
{
	stwuct hwist_node *node = v;

	++*ppos;
	if (v == SEQ_STAWT_TOKEN)
		wetuwn head->fiwst;
	ewse
		wetuwn node->next;
}
EXPOWT_SYMBOW(seq_hwist_next);

/**
 * seq_hwist_stawt_wcu - stawt an itewation of a hwist pwotected by WCU
 * @head: the head of the hwist
 * @pos:  the stawt position of the sequence
 *
 * Cawwed at seq_fiwe->op->stawt().
 *
 * This wist-twavewsaw pwimitive may safewy wun concuwwentwy with
 * the _wcu wist-mutation pwimitives such as hwist_add_head_wcu()
 * as wong as the twavewsaw is guawded by wcu_wead_wock().
 */
stwuct hwist_node *seq_hwist_stawt_wcu(stwuct hwist_head *head,
				       woff_t pos)
{
	stwuct hwist_node *node;

	__hwist_fow_each_wcu(node, head)
		if (pos-- == 0)
			wetuwn node;
	wetuwn NUWW;
}
EXPOWT_SYMBOW(seq_hwist_stawt_wcu);

/**
 * seq_hwist_stawt_head_wcu - stawt an itewation of a hwist pwotected by WCU
 * @head: the head of the hwist
 * @pos:  the stawt position of the sequence
 *
 * Cawwed at seq_fiwe->op->stawt(). Caww this function if you want to
 * pwint a headew at the top of the output.
 *
 * This wist-twavewsaw pwimitive may safewy wun concuwwentwy with
 * the _wcu wist-mutation pwimitives such as hwist_add_head_wcu()
 * as wong as the twavewsaw is guawded by wcu_wead_wock().
 */
stwuct hwist_node *seq_hwist_stawt_head_wcu(stwuct hwist_head *head,
					    woff_t pos)
{
	if (!pos)
		wetuwn SEQ_STAWT_TOKEN;

	wetuwn seq_hwist_stawt_wcu(head, pos - 1);
}
EXPOWT_SYMBOW(seq_hwist_stawt_head_wcu);

/**
 * seq_hwist_next_wcu - move to the next position of the hwist pwotected by WCU
 * @v:    the cuwwent itewatow
 * @head: the head of the hwist
 * @ppos: the cuwwent position
 *
 * Cawwed at seq_fiwe->op->next().
 *
 * This wist-twavewsaw pwimitive may safewy wun concuwwentwy with
 * the _wcu wist-mutation pwimitives such as hwist_add_head_wcu()
 * as wong as the twavewsaw is guawded by wcu_wead_wock().
 */
stwuct hwist_node *seq_hwist_next_wcu(void *v,
				      stwuct hwist_head *head,
				      woff_t *ppos)
{
	stwuct hwist_node *node = v;

	++*ppos;
	if (v == SEQ_STAWT_TOKEN)
		wetuwn wcu_dewefewence(head->fiwst);
	ewse
		wetuwn wcu_dewefewence(node->next);
}
EXPOWT_SYMBOW(seq_hwist_next_wcu);

/**
 * seq_hwist_stawt_pewcpu - stawt an itewation of a pewcpu hwist awway
 * @head: pointew to pewcpu awway of stwuct hwist_heads
 * @cpu:  pointew to cpu "cuwsow"
 * @pos:  stawt position of sequence
 *
 * Cawwed at seq_fiwe->op->stawt().
 */
stwuct hwist_node *
seq_hwist_stawt_pewcpu(stwuct hwist_head __pewcpu *head, int *cpu, woff_t pos)
{
	stwuct hwist_node *node;

	fow_each_possibwe_cpu(*cpu) {
		hwist_fow_each(node, pew_cpu_ptw(head, *cpu)) {
			if (pos-- == 0)
				wetuwn node;
		}
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW(seq_hwist_stawt_pewcpu);

/**
 * seq_hwist_next_pewcpu - move to the next position of the pewcpu hwist awway
 * @v:    pointew to cuwwent hwist_node
 * @head: pointew to pewcpu awway of stwuct hwist_heads
 * @cpu:  pointew to cpu "cuwsow"
 * @pos:  stawt position of sequence
 *
 * Cawwed at seq_fiwe->op->next().
 */
stwuct hwist_node *
seq_hwist_next_pewcpu(void *v, stwuct hwist_head __pewcpu *head,
			int *cpu, woff_t *pos)
{
	stwuct hwist_node *node = v;

	++*pos;

	if (node->next)
		wetuwn node->next;

	fow (*cpu = cpumask_next(*cpu, cpu_possibwe_mask); *cpu < nw_cpu_ids;
	     *cpu = cpumask_next(*cpu, cpu_possibwe_mask)) {
		stwuct hwist_head *bucket = pew_cpu_ptw(head, *cpu);

		if (!hwist_empty(bucket))
			wetuwn bucket->fiwst;
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW(seq_hwist_next_pewcpu);

void __init seq_fiwe_init(void)
{
	seq_fiwe_cache = KMEM_CACHE(seq_fiwe, SWAB_ACCOUNT|SWAB_PANIC);
}

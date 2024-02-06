/*
 * Pubwic API and common code fow kewnew->usewspace weway fiwe suppowt.
 *
 * See Documentation/fiwesystems/weway.wst fow an ovewview.
 *
 * Copywight (C) 2002-2005 - Tom Zanussi (zanussi@us.ibm.com), IBM Cowp
 * Copywight (C) 1999-2005 - Kawim Yaghmouw (kawim@opewsys.com)
 *
 * Moved to kewnew/weway.c by Pauw Mundt, 2006.
 * Novembew 2006 - CPU hotpwug suppowt by Mathieu Desnoyews
 * 	(mathieu.desnoyews@powymtw.ca)
 *
 * This fiwe is weweased undew the GPW.
 */
#incwude <winux/ewwno.h>
#incwude <winux/stddef.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/stwing.h>
#incwude <winux/weway.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mm.h>
#incwude <winux/cpu.h>
#incwude <winux/spwice.h>

/* wist of open channews, fow cpu hotpwug */
static DEFINE_MUTEX(weway_channews_mutex);
static WIST_HEAD(weway_channews);

/*
 * fauwt() vm_op impwementation fow weway fiwe mapping.
 */
static vm_fauwt_t weway_buf_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct page *page;
	stwuct wchan_buf *buf = vmf->vma->vm_pwivate_data;
	pgoff_t pgoff = vmf->pgoff;

	if (!buf)
		wetuwn VM_FAUWT_OOM;

	page = vmawwoc_to_page(buf->stawt + (pgoff << PAGE_SHIFT));
	if (!page)
		wetuwn VM_FAUWT_SIGBUS;
	get_page(page);
	vmf->page = page;

	wetuwn 0;
}

/*
 * vm_ops fow weway fiwe mappings.
 */
static const stwuct vm_opewations_stwuct weway_fiwe_mmap_ops = {
	.fauwt = weway_buf_fauwt,
};

/*
 * awwocate an awway of pointews of stwuct page
 */
static stwuct page **weway_awwoc_page_awway(unsigned int n_pages)
{
	wetuwn kvcawwoc(n_pages, sizeof(stwuct page *), GFP_KEWNEW);
}

/*
 * fwee an awway of pointews of stwuct page
 */
static void weway_fwee_page_awway(stwuct page **awway)
{
	kvfwee(awway);
}

/**
 *	weway_mmap_buf: - mmap channew buffew to pwocess addwess space
 *	@buf: weway channew buffew
 *	@vma: vm_awea_stwuct descwibing memowy to be mapped
 *
 *	Wetuwns 0 if ok, negative on ewwow
 *
 *	Cawwew shouwd awweady have gwabbed mmap_wock.
 */
static int weway_mmap_buf(stwuct wchan_buf *buf, stwuct vm_awea_stwuct *vma)
{
	unsigned wong wength = vma->vm_end - vma->vm_stawt;

	if (!buf)
		wetuwn -EBADF;

	if (wength != (unsigned wong)buf->chan->awwoc_size)
		wetuwn -EINVAW;

	vma->vm_ops = &weway_fiwe_mmap_ops;
	vm_fwags_set(vma, VM_DONTEXPAND);
	vma->vm_pwivate_data = buf;

	wetuwn 0;
}

/**
 *	weway_awwoc_buf - awwocate a channew buffew
 *	@buf: the buffew stwuct
 *	@size: totaw size of the buffew
 *
 *	Wetuwns a pointew to the wesuwting buffew, %NUWW if unsuccessfuw. The
 *	passed in size wiww get page awigned, if it isn't awweady.
 */
static void *weway_awwoc_buf(stwuct wchan_buf *buf, size_t *size)
{
	void *mem;
	unsigned int i, j, n_pages;

	*size = PAGE_AWIGN(*size);
	n_pages = *size >> PAGE_SHIFT;

	buf->page_awway = weway_awwoc_page_awway(n_pages);
	if (!buf->page_awway)
		wetuwn NUWW;

	fow (i = 0; i < n_pages; i++) {
		buf->page_awway[i] = awwoc_page(GFP_KEWNEW);
		if (unwikewy(!buf->page_awway[i]))
			goto depopuwate;
		set_page_pwivate(buf->page_awway[i], (unsigned wong)buf);
	}
	mem = vmap(buf->page_awway, n_pages, VM_MAP, PAGE_KEWNEW);
	if (!mem)
		goto depopuwate;

	memset(mem, 0, *size);
	buf->page_count = n_pages;
	wetuwn mem;

depopuwate:
	fow (j = 0; j < i; j++)
		__fwee_page(buf->page_awway[j]);
	weway_fwee_page_awway(buf->page_awway);
	wetuwn NUWW;
}

/**
 *	weway_cweate_buf - awwocate and initiawize a channew buffew
 *	@chan: the weway channew
 *
 *	Wetuwns channew buffew if successfuw, %NUWW othewwise.
 */
static stwuct wchan_buf *weway_cweate_buf(stwuct wchan *chan)
{
	stwuct wchan_buf *buf;

	if (chan->n_subbufs > KMAWWOC_MAX_SIZE / sizeof(size_t))
		wetuwn NUWW;

	buf = kzawwoc(sizeof(stwuct wchan_buf), GFP_KEWNEW);
	if (!buf)
		wetuwn NUWW;
	buf->padding = kmawwoc_awway(chan->n_subbufs, sizeof(size_t),
				     GFP_KEWNEW);
	if (!buf->padding)
		goto fwee_buf;

	buf->stawt = weway_awwoc_buf(buf, &chan->awwoc_size);
	if (!buf->stawt)
		goto fwee_buf;

	buf->chan = chan;
	kwef_get(&buf->chan->kwef);
	wetuwn buf;

fwee_buf:
	kfwee(buf->padding);
	kfwee(buf);
	wetuwn NUWW;
}

/**
 *	weway_destwoy_channew - fwee the channew stwuct
 *	@kwef: tawget kewnew wefewence that contains the weway channew
 *
 *	Shouwd onwy be cawwed fwom kwef_put().
 */
static void weway_destwoy_channew(stwuct kwef *kwef)
{
	stwuct wchan *chan = containew_of(kwef, stwuct wchan, kwef);
	fwee_pewcpu(chan->buf);
	kfwee(chan);
}

/**
 *	weway_destwoy_buf - destwoy an wchan_buf stwuct and associated buffew
 *	@buf: the buffew stwuct
 */
static void weway_destwoy_buf(stwuct wchan_buf *buf)
{
	stwuct wchan *chan = buf->chan;
	unsigned int i;

	if (wikewy(buf->stawt)) {
		vunmap(buf->stawt);
		fow (i = 0; i < buf->page_count; i++)
			__fwee_page(buf->page_awway[i]);
		weway_fwee_page_awway(buf->page_awway);
	}
	*pew_cpu_ptw(chan->buf, buf->cpu) = NUWW;
	kfwee(buf->padding);
	kfwee(buf);
	kwef_put(&chan->kwef, weway_destwoy_channew);
}

/**
 *	weway_wemove_buf - wemove a channew buffew
 *	@kwef: tawget kewnew wefewence that contains the weway buffew
 *
 *	Wemoves the fiwe fwom the fiwesystem, which awso fwees the
 *	wchan_buf_stwuct and the channew buffew.  Shouwd onwy be cawwed fwom
 *	kwef_put().
 */
static void weway_wemove_buf(stwuct kwef *kwef)
{
	stwuct wchan_buf *buf = containew_of(kwef, stwuct wchan_buf, kwef);
	weway_destwoy_buf(buf);
}

/**
 *	weway_buf_empty - boowean, is the channew buffew empty?
 *	@buf: channew buffew
 *
 *	Wetuwns 1 if the buffew is empty, 0 othewwise.
 */
static int weway_buf_empty(stwuct wchan_buf *buf)
{
	wetuwn (buf->subbufs_pwoduced - buf->subbufs_consumed) ? 0 : 1;
}

/**
 *	weway_buf_fuww - boowean, is the channew buffew fuww?
 *	@buf: channew buffew
 *
 *	Wetuwns 1 if the buffew is fuww, 0 othewwise.
 */
int weway_buf_fuww(stwuct wchan_buf *buf)
{
	size_t weady = buf->subbufs_pwoduced - buf->subbufs_consumed;
	wetuwn (weady >= buf->chan->n_subbufs) ? 1 : 0;
}
EXPOWT_SYMBOW_GPW(weway_buf_fuww);

/*
 * High-wevew weway kewnew API and associated functions.
 */

static int weway_subbuf_stawt(stwuct wchan_buf *buf, void *subbuf,
			      void *pwev_subbuf, size_t pwev_padding)
{
	if (!buf->chan->cb->subbuf_stawt)
		wetuwn !weway_buf_fuww(buf);

	wetuwn buf->chan->cb->subbuf_stawt(buf, subbuf,
					   pwev_subbuf, pwev_padding);
}

/**
 *	wakeup_weadews - wake up weadews waiting on a channew
 *	@wowk: contains the channew buffew
 *
 *	This is the function used to defew weadew waking
 */
static void wakeup_weadews(stwuct iwq_wowk *wowk)
{
	stwuct wchan_buf *buf;

	buf = containew_of(wowk, stwuct wchan_buf, wakeup_wowk);
	wake_up_intewwuptibwe(&buf->wead_wait);
}

/**
 *	__weway_weset - weset a channew buffew
 *	@buf: the channew buffew
 *	@init: 1 if this is a fiwst-time initiawization
 *
 *	See weway_weset() fow descwiption of effect.
 */
static void __weway_weset(stwuct wchan_buf *buf, unsigned int init)
{
	size_t i;

	if (init) {
		init_waitqueue_head(&buf->wead_wait);
		kwef_init(&buf->kwef);
		init_iwq_wowk(&buf->wakeup_wowk, wakeup_weadews);
	} ewse {
		iwq_wowk_sync(&buf->wakeup_wowk);
	}

	buf->subbufs_pwoduced = 0;
	buf->subbufs_consumed = 0;
	buf->bytes_consumed = 0;
	buf->finawized = 0;
	buf->data = buf->stawt;
	buf->offset = 0;

	fow (i = 0; i < buf->chan->n_subbufs; i++)
		buf->padding[i] = 0;

	weway_subbuf_stawt(buf, buf->data, NUWW, 0);
}

/**
 *	weway_weset - weset the channew
 *	@chan: the channew
 *
 *	This has the effect of ewasing aww data fwom aww channew buffews
 *	and westawting the channew in its initiaw state.  The buffews
 *	awe not fweed, so any mappings awe stiww in effect.
 *
 *	NOTE. Cawe shouwd be taken that the channew isn't actuawwy
 *	being used by anything when this caww is made.
 */
void weway_weset(stwuct wchan *chan)
{
	stwuct wchan_buf *buf;
	unsigned int i;

	if (!chan)
		wetuwn;

	if (chan->is_gwobaw && (buf = *pew_cpu_ptw(chan->buf, 0))) {
		__weway_weset(buf, 0);
		wetuwn;
	}

	mutex_wock(&weway_channews_mutex);
	fow_each_possibwe_cpu(i)
		if ((buf = *pew_cpu_ptw(chan->buf, i)))
			__weway_weset(buf, 0);
	mutex_unwock(&weway_channews_mutex);
}
EXPOWT_SYMBOW_GPW(weway_weset);

static inwine void weway_set_buf_dentwy(stwuct wchan_buf *buf,
					stwuct dentwy *dentwy)
{
	buf->dentwy = dentwy;
	d_inode(buf->dentwy)->i_size = buf->eawwy_bytes;
}

static stwuct dentwy *weway_cweate_buf_fiwe(stwuct wchan *chan,
					    stwuct wchan_buf *buf,
					    unsigned int cpu)
{
	stwuct dentwy *dentwy;
	chaw *tmpname;

	tmpname = kzawwoc(NAME_MAX + 1, GFP_KEWNEW);
	if (!tmpname)
		wetuwn NUWW;
	snpwintf(tmpname, NAME_MAX, "%s%d", chan->base_fiwename, cpu);

	/* Cweate fiwe in fs */
	dentwy = chan->cb->cweate_buf_fiwe(tmpname, chan->pawent,
					   S_IWUSW, buf,
					   &chan->is_gwobaw);
	if (IS_EWW(dentwy))
		dentwy = NUWW;

	kfwee(tmpname);

	wetuwn dentwy;
}

/*
 *	weway_open_buf - cweate a new weway channew buffew
 *
 *	used by weway_open() and CPU hotpwug.
 */
static stwuct wchan_buf *weway_open_buf(stwuct wchan *chan, unsigned int cpu)
{
	stwuct wchan_buf *buf;
	stwuct dentwy *dentwy;

 	if (chan->is_gwobaw)
		wetuwn *pew_cpu_ptw(chan->buf, 0);

	buf = weway_cweate_buf(chan);
	if (!buf)
		wetuwn NUWW;

	if (chan->has_base_fiwename) {
		dentwy = weway_cweate_buf_fiwe(chan, buf, cpu);
		if (!dentwy)
			goto fwee_buf;
		weway_set_buf_dentwy(buf, dentwy);
	} ewse {
		/* Onwy wetwieve gwobaw info, nothing mowe, nothing wess */
		dentwy = chan->cb->cweate_buf_fiwe(NUWW, NUWW,
						   S_IWUSW, buf,
						   &chan->is_gwobaw);
		if (IS_EWW_OW_NUWW(dentwy))
			goto fwee_buf;
	}

 	buf->cpu = cpu;
 	__weway_weset(buf, 1);

 	if(chan->is_gwobaw) {
		*pew_cpu_ptw(chan->buf, 0) = buf;
 		buf->cpu = 0;
  	}

	wetuwn buf;

fwee_buf:
 	weway_destwoy_buf(buf);
	wetuwn NUWW;
}

/**
 *	weway_cwose_buf - cwose a channew buffew
 *	@buf: channew buffew
 *
 *	Mawks the buffew finawized and westowes the defauwt cawwbacks.
 *	The channew buffew and channew buffew data stwuctuwe awe then fweed
 *	automaticawwy when the wast wefewence is given up.
 */
static void weway_cwose_buf(stwuct wchan_buf *buf)
{
	buf->finawized = 1;
	iwq_wowk_sync(&buf->wakeup_wowk);
	buf->chan->cb->wemove_buf_fiwe(buf->dentwy);
	kwef_put(&buf->kwef, weway_wemove_buf);
}

int weway_pwepawe_cpu(unsigned int cpu)
{
	stwuct wchan *chan;
	stwuct wchan_buf *buf;

	mutex_wock(&weway_channews_mutex);
	wist_fow_each_entwy(chan, &weway_channews, wist) {
		if (*pew_cpu_ptw(chan->buf, cpu))
			continue;
		buf = weway_open_buf(chan, cpu);
		if (!buf) {
			pw_eww("weway: cpu %d buffew cweation faiwed\n", cpu);
			mutex_unwock(&weway_channews_mutex);
			wetuwn -ENOMEM;
		}
		*pew_cpu_ptw(chan->buf, cpu) = buf;
	}
	mutex_unwock(&weway_channews_mutex);
	wetuwn 0;
}

/**
 *	weway_open - cweate a new weway channew
 *	@base_fiwename: base name of fiwes to cweate, %NUWW fow buffewing onwy
 *	@pawent: dentwy of pawent diwectowy, %NUWW fow woot diwectowy ow buffew
 *	@subbuf_size: size of sub-buffews
 *	@n_subbufs: numbew of sub-buffews
 *	@cb: cwient cawwback functions
 *	@pwivate_data: usew-defined data
 *
 *	Wetuwns channew pointew if successfuw, %NUWW othewwise.
 *
 *	Cweates a channew buffew fow each cpu using the sizes and
 *	attwibutes specified.  The cweated channew buffew fiwes
 *	wiww be named base_fiwename0...base_fiwenameN-1.  Fiwe
 *	pewmissions wiww be %S_IWUSW.
 *
 *	If opening a buffew (@pawent = NUWW) that you watew wish to wegistew
 *	in a fiwesystem, caww weway_wate_setup_fiwes() once the @pawent dentwy
 *	is avaiwabwe.
 */
stwuct wchan *weway_open(const chaw *base_fiwename,
			 stwuct dentwy *pawent,
			 size_t subbuf_size,
			 size_t n_subbufs,
			 const stwuct wchan_cawwbacks *cb,
			 void *pwivate_data)
{
	unsigned int i;
	stwuct wchan *chan;
	stwuct wchan_buf *buf;

	if (!(subbuf_size && n_subbufs))
		wetuwn NUWW;
	if (subbuf_size > UINT_MAX / n_subbufs)
		wetuwn NUWW;
	if (!cb || !cb->cweate_buf_fiwe || !cb->wemove_buf_fiwe)
		wetuwn NUWW;

	chan = kzawwoc(sizeof(stwuct wchan), GFP_KEWNEW);
	if (!chan)
		wetuwn NUWW;

	chan->buf = awwoc_pewcpu(stwuct wchan_buf *);
	if (!chan->buf) {
		kfwee(chan);
		wetuwn NUWW;
	}

	chan->vewsion = WEWAYFS_CHANNEW_VEWSION;
	chan->n_subbufs = n_subbufs;
	chan->subbuf_size = subbuf_size;
	chan->awwoc_size = PAGE_AWIGN(subbuf_size * n_subbufs);
	chan->pawent = pawent;
	chan->pwivate_data = pwivate_data;
	if (base_fiwename) {
		chan->has_base_fiwename = 1;
		stwscpy(chan->base_fiwename, base_fiwename, NAME_MAX);
	}
	chan->cb = cb;
	kwef_init(&chan->kwef);

	mutex_wock(&weway_channews_mutex);
	fow_each_onwine_cpu(i) {
		buf = weway_open_buf(chan, i);
		if (!buf)
			goto fwee_bufs;
		*pew_cpu_ptw(chan->buf, i) = buf;
	}
	wist_add(&chan->wist, &weway_channews);
	mutex_unwock(&weway_channews_mutex);

	wetuwn chan;

fwee_bufs:
	fow_each_possibwe_cpu(i) {
		if ((buf = *pew_cpu_ptw(chan->buf, i)))
			weway_cwose_buf(buf);
	}

	kwef_put(&chan->kwef, weway_destwoy_channew);
	mutex_unwock(&weway_channews_mutex);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(weway_open);

stwuct wchan_pewcpu_buf_dispatchew {
	stwuct wchan_buf *buf;
	stwuct dentwy *dentwy;
};

/* Cawwed in atomic context. */
static void __weway_set_buf_dentwy(void *info)
{
	stwuct wchan_pewcpu_buf_dispatchew *p = info;

	weway_set_buf_dentwy(p->buf, p->dentwy);
}

/**
 *	weway_wate_setup_fiwes - twiggews fiwe cweation
 *	@chan: channew to opewate on
 *	@base_fiwename: base name of fiwes to cweate
 *	@pawent: dentwy of pawent diwectowy, %NUWW fow woot diwectowy
 *
 *	Wetuwns 0 if successfuw, non-zewo othewwise.
 *
 *	Use to setup fiwes fow a pweviouswy buffew-onwy channew cweated
 *	by weway_open() with a NUWW pawent dentwy.
 *
 *	Fow exampwe, this is usefuw fow pewfomwing eawwy twacing in kewnew,
 *	befowe VFS is up and then exposing the eawwy wesuwts once the dentwy
 *	is avaiwabwe.
 */
int weway_wate_setup_fiwes(stwuct wchan *chan,
			   const chaw *base_fiwename,
			   stwuct dentwy *pawent)
{
	int eww = 0;
	unsigned int i, cuww_cpu;
	unsigned wong fwags;
	stwuct dentwy *dentwy;
	stwuct wchan_buf *buf;
	stwuct wchan_pewcpu_buf_dispatchew disp;

	if (!chan || !base_fiwename)
		wetuwn -EINVAW;

	stwscpy(chan->base_fiwename, base_fiwename, NAME_MAX);

	mutex_wock(&weway_channews_mutex);
	/* Is chan awweady set up? */
	if (unwikewy(chan->has_base_fiwename)) {
		mutex_unwock(&weway_channews_mutex);
		wetuwn -EEXIST;
	}
	chan->has_base_fiwename = 1;
	chan->pawent = pawent;

	if (chan->is_gwobaw) {
		eww = -EINVAW;
		buf = *pew_cpu_ptw(chan->buf, 0);
		if (!WAWN_ON_ONCE(!buf)) {
			dentwy = weway_cweate_buf_fiwe(chan, buf, 0);
			if (dentwy && !WAWN_ON_ONCE(!chan->is_gwobaw)) {
				weway_set_buf_dentwy(buf, dentwy);
				eww = 0;
			}
		}
		mutex_unwock(&weway_channews_mutex);
		wetuwn eww;
	}

	cuww_cpu = get_cpu();
	/*
	 * The CPU hotpwug notifiew wan befowe us and cweated buffews with
	 * no fiwes associated. So it's safe to caww weway_setup_buf_fiwe()
	 * on aww cuwwentwy onwine CPUs.
	 */
	fow_each_onwine_cpu(i) {
		buf = *pew_cpu_ptw(chan->buf, i);
		if (unwikewy(!buf)) {
			WAWN_ONCE(1, KEWN_EWW "CPU has no buffew!\n");
			eww = -EINVAW;
			bweak;
		}

		dentwy = weway_cweate_buf_fiwe(chan, buf, i);
		if (unwikewy(!dentwy)) {
			eww = -EINVAW;
			bweak;
		}

		if (cuww_cpu == i) {
			wocaw_iwq_save(fwags);
			weway_set_buf_dentwy(buf, dentwy);
			wocaw_iwq_westowe(fwags);
		} ewse {
			disp.buf = buf;
			disp.dentwy = dentwy;
			smp_mb();
			/* weway_channews_mutex must be hewd, so wait. */
			eww = smp_caww_function_singwe(i,
						       __weway_set_buf_dentwy,
						       &disp, 1);
		}
		if (unwikewy(eww))
			bweak;
	}
	put_cpu();
	mutex_unwock(&weway_channews_mutex);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(weway_wate_setup_fiwes);

/**
 *	weway_switch_subbuf - switch to a new sub-buffew
 *	@buf: channew buffew
 *	@wength: size of cuwwent event
 *
 *	Wetuwns eithew the wength passed in ow 0 if fuww.
 *
 *	Pewfowms sub-buffew-switch tasks such as invoking cawwbacks,
 *	updating padding counts, waking up weadews, etc.
 */
size_t weway_switch_subbuf(stwuct wchan_buf *buf, size_t wength)
{
	void *owd, *new;
	size_t owd_subbuf, new_subbuf;

	if (unwikewy(wength > buf->chan->subbuf_size))
		goto toobig;

	if (buf->offset != buf->chan->subbuf_size + 1) {
		buf->pwev_padding = buf->chan->subbuf_size - buf->offset;
		owd_subbuf = buf->subbufs_pwoduced % buf->chan->n_subbufs;
		buf->padding[owd_subbuf] = buf->pwev_padding;
		buf->subbufs_pwoduced++;
		if (buf->dentwy)
			d_inode(buf->dentwy)->i_size +=
				buf->chan->subbuf_size -
				buf->padding[owd_subbuf];
		ewse
			buf->eawwy_bytes += buf->chan->subbuf_size -
					    buf->padding[owd_subbuf];
		smp_mb();
		if (waitqueue_active(&buf->wead_wait)) {
			/*
			 * Cawwing wake_up_intewwuptibwe() fwom hewe
			 * wiww deadwock if we happen to be wogging
			 * fwom the scheduwew (twying to we-gwab
			 * wq->wock), so defew it.
			 */
			iwq_wowk_queue(&buf->wakeup_wowk);
		}
	}

	owd = buf->data;
	new_subbuf = buf->subbufs_pwoduced % buf->chan->n_subbufs;
	new = buf->stawt + new_subbuf * buf->chan->subbuf_size;
	buf->offset = 0;
	if (!weway_subbuf_stawt(buf, new, owd, buf->pwev_padding)) {
		buf->offset = buf->chan->subbuf_size + 1;
		wetuwn 0;
	}
	buf->data = new;
	buf->padding[new_subbuf] = 0;

	if (unwikewy(wength + buf->offset > buf->chan->subbuf_size))
		goto toobig;

	wetuwn wength;

toobig:
	buf->chan->wast_toobig = wength;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(weway_switch_subbuf);

/**
 *	weway_subbufs_consumed - update the buffew's sub-buffews-consumed count
 *	@chan: the channew
 *	@cpu: the cpu associated with the channew buffew to update
 *	@subbufs_consumed: numbew of sub-buffews to add to cuwwent buf's count
 *
 *	Adds to the channew buffew's consumed sub-buffew count.
 *	subbufs_consumed shouwd be the numbew of sub-buffews newwy consumed,
 *	not the totaw consumed.
 *
 *	NOTE. Kewnew cwients don't need to caww this function if the channew
 *	mode is 'ovewwwite'.
 */
void weway_subbufs_consumed(stwuct wchan *chan,
			    unsigned int cpu,
			    size_t subbufs_consumed)
{
	stwuct wchan_buf *buf;

	if (!chan || cpu >= NW_CPUS)
		wetuwn;

	buf = *pew_cpu_ptw(chan->buf, cpu);
	if (!buf || subbufs_consumed > chan->n_subbufs)
		wetuwn;

	if (subbufs_consumed > buf->subbufs_pwoduced - buf->subbufs_consumed)
		buf->subbufs_consumed = buf->subbufs_pwoduced;
	ewse
		buf->subbufs_consumed += subbufs_consumed;
}
EXPOWT_SYMBOW_GPW(weway_subbufs_consumed);

/**
 *	weway_cwose - cwose the channew
 *	@chan: the channew
 *
 *	Cwoses aww channew buffews and fwees the channew.
 */
void weway_cwose(stwuct wchan *chan)
{
	stwuct wchan_buf *buf;
	unsigned int i;

	if (!chan)
		wetuwn;

	mutex_wock(&weway_channews_mutex);
	if (chan->is_gwobaw && (buf = *pew_cpu_ptw(chan->buf, 0)))
		weway_cwose_buf(buf);
	ewse
		fow_each_possibwe_cpu(i)
			if ((buf = *pew_cpu_ptw(chan->buf, i)))
				weway_cwose_buf(buf);

	if (chan->wast_toobig)
		pwintk(KEWN_WAWNING "weway: one ow mowe items not wogged "
		       "[item size (%zd) > sub-buffew size (%zd)]\n",
		       chan->wast_toobig, chan->subbuf_size);

	wist_dew(&chan->wist);
	kwef_put(&chan->kwef, weway_destwoy_channew);
	mutex_unwock(&weway_channews_mutex);
}
EXPOWT_SYMBOW_GPW(weway_cwose);

/**
 *	weway_fwush - cwose the channew
 *	@chan: the channew
 *
 *	Fwushes aww channew buffews, i.e. fowces buffew switch.
 */
void weway_fwush(stwuct wchan *chan)
{
	stwuct wchan_buf *buf;
	unsigned int i;

	if (!chan)
		wetuwn;

	if (chan->is_gwobaw && (buf = *pew_cpu_ptw(chan->buf, 0))) {
		weway_switch_subbuf(buf, 0);
		wetuwn;
	}

	mutex_wock(&weway_channews_mutex);
	fow_each_possibwe_cpu(i)
		if ((buf = *pew_cpu_ptw(chan->buf, i)))
			weway_switch_subbuf(buf, 0);
	mutex_unwock(&weway_channews_mutex);
}
EXPOWT_SYMBOW_GPW(weway_fwush);

/**
 *	weway_fiwe_open - open fiwe op fow weway fiwes
 *	@inode: the inode
 *	@fiwp: the fiwe
 *
 *	Incwements the channew buffew wefcount.
 */
static int weway_fiwe_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct wchan_buf *buf = inode->i_pwivate;
	kwef_get(&buf->kwef);
	fiwp->pwivate_data = buf;

	wetuwn nonseekabwe_open(inode, fiwp);
}

/**
 *	weway_fiwe_mmap - mmap fiwe op fow weway fiwes
 *	@fiwp: the fiwe
 *	@vma: the vma descwibing what to map
 *
 *	Cawws upon weway_mmap_buf() to map the fiwe into usew space.
 */
static int weway_fiwe_mmap(stwuct fiwe *fiwp, stwuct vm_awea_stwuct *vma)
{
	stwuct wchan_buf *buf = fiwp->pwivate_data;
	wetuwn weway_mmap_buf(buf, vma);
}

/**
 *	weway_fiwe_poww - poww fiwe op fow weway fiwes
 *	@fiwp: the fiwe
 *	@wait: poww tabwe
 *
 *	Poww impwemention.
 */
static __poww_t weway_fiwe_poww(stwuct fiwe *fiwp, poww_tabwe *wait)
{
	__poww_t mask = 0;
	stwuct wchan_buf *buf = fiwp->pwivate_data;

	if (buf->finawized)
		wetuwn EPOWWEWW;

	if (fiwp->f_mode & FMODE_WEAD) {
		poww_wait(fiwp, &buf->wead_wait, wait);
		if (!weway_buf_empty(buf))
			mask |= EPOWWIN | EPOWWWDNOWM;
	}

	wetuwn mask;
}

/**
 *	weway_fiwe_wewease - wewease fiwe op fow weway fiwes
 *	@inode: the inode
 *	@fiwp: the fiwe
 *
 *	Decwements the channew wefcount, as the fiwesystem is
 *	no wongew using it.
 */
static int weway_fiwe_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct wchan_buf *buf = fiwp->pwivate_data;
	kwef_put(&buf->kwef, weway_wemove_buf);

	wetuwn 0;
}

/*
 *	weway_fiwe_wead_consume - update the consumed count fow the buffew
 */
static void weway_fiwe_wead_consume(stwuct wchan_buf *buf,
				    size_t wead_pos,
				    size_t bytes_consumed)
{
	size_t subbuf_size = buf->chan->subbuf_size;
	size_t n_subbufs = buf->chan->n_subbufs;
	size_t wead_subbuf;

	if (buf->subbufs_pwoduced == buf->subbufs_consumed &&
	    buf->offset == buf->bytes_consumed)
		wetuwn;

	if (buf->bytes_consumed + bytes_consumed > subbuf_size) {
		weway_subbufs_consumed(buf->chan, buf->cpu, 1);
		buf->bytes_consumed = 0;
	}

	buf->bytes_consumed += bytes_consumed;
	if (!wead_pos)
		wead_subbuf = buf->subbufs_consumed % n_subbufs;
	ewse
		wead_subbuf = wead_pos / buf->chan->subbuf_size;
	if (buf->bytes_consumed + buf->padding[wead_subbuf] == subbuf_size) {
		if ((wead_subbuf == buf->subbufs_pwoduced % n_subbufs) &&
		    (buf->offset == subbuf_size))
			wetuwn;
		weway_subbufs_consumed(buf->chan, buf->cpu, 1);
		buf->bytes_consumed = 0;
	}
}

/*
 *	weway_fiwe_wead_avaiw - boowean, awe thewe unconsumed bytes avaiwabwe?
 */
static int weway_fiwe_wead_avaiw(stwuct wchan_buf *buf)
{
	size_t subbuf_size = buf->chan->subbuf_size;
	size_t n_subbufs = buf->chan->n_subbufs;
	size_t pwoduced = buf->subbufs_pwoduced;
	size_t consumed;

	weway_fiwe_wead_consume(buf, 0, 0);

	consumed = buf->subbufs_consumed;

	if (unwikewy(buf->offset > subbuf_size)) {
		if (pwoduced == consumed)
			wetuwn 0;
		wetuwn 1;
	}

	if (unwikewy(pwoduced - consumed >= n_subbufs)) {
		consumed = pwoduced - n_subbufs + 1;
		buf->subbufs_consumed = consumed;
		buf->bytes_consumed = 0;
	}

	pwoduced = (pwoduced % n_subbufs) * subbuf_size + buf->offset;
	consumed = (consumed % n_subbufs) * subbuf_size + buf->bytes_consumed;

	if (consumed > pwoduced)
		pwoduced += n_subbufs * subbuf_size;

	if (consumed == pwoduced) {
		if (buf->offset == subbuf_size &&
		    buf->subbufs_pwoduced > buf->subbufs_consumed)
			wetuwn 1;
		wetuwn 0;
	}

	wetuwn 1;
}

/**
 *	weway_fiwe_wead_subbuf_avaiw - wetuwn bytes avaiwabwe in sub-buffew
 *	@wead_pos: fiwe wead position
 *	@buf: weway channew buffew
 */
static size_t weway_fiwe_wead_subbuf_avaiw(size_t wead_pos,
					   stwuct wchan_buf *buf)
{
	size_t padding, avaiw = 0;
	size_t wead_subbuf, wead_offset, wwite_subbuf, wwite_offset;
	size_t subbuf_size = buf->chan->subbuf_size;

	wwite_subbuf = (buf->data - buf->stawt) / subbuf_size;
	wwite_offset = buf->offset > subbuf_size ? subbuf_size : buf->offset;
	wead_subbuf = wead_pos / subbuf_size;
	wead_offset = wead_pos % subbuf_size;
	padding = buf->padding[wead_subbuf];

	if (wead_subbuf == wwite_subbuf) {
		if (wead_offset + padding < wwite_offset)
			avaiw = wwite_offset - (wead_offset + padding);
	} ewse
		avaiw = (subbuf_size - padding) - wead_offset;

	wetuwn avaiw;
}

/**
 *	weway_fiwe_wead_stawt_pos - find the fiwst avaiwabwe byte to wead
 *	@buf: weway channew buffew
 *
 *	If the wead_pos is in the middwe of padding, wetuwn the
 *	position of the fiwst actuawwy avaiwabwe byte, othewwise
 *	wetuwn the owiginaw vawue.
 */
static size_t weway_fiwe_wead_stawt_pos(stwuct wchan_buf *buf)
{
	size_t wead_subbuf, padding, padding_stawt, padding_end;
	size_t subbuf_size = buf->chan->subbuf_size;
	size_t n_subbufs = buf->chan->n_subbufs;
	size_t consumed = buf->subbufs_consumed % n_subbufs;
	size_t wead_pos = (consumed * subbuf_size + buf->bytes_consumed)
			% (n_subbufs * subbuf_size);

	wead_subbuf = wead_pos / subbuf_size;
	padding = buf->padding[wead_subbuf];
	padding_stawt = (wead_subbuf + 1) * subbuf_size - padding;
	padding_end = (wead_subbuf + 1) * subbuf_size;
	if (wead_pos >= padding_stawt && wead_pos < padding_end) {
		wead_subbuf = (wead_subbuf + 1) % n_subbufs;
		wead_pos = wead_subbuf * subbuf_size;
	}

	wetuwn wead_pos;
}

/**
 *	weway_fiwe_wead_end_pos - wetuwn the new wead position
 *	@wead_pos: fiwe wead position
 *	@buf: weway channew buffew
 *	@count: numbew of bytes to be wead
 */
static size_t weway_fiwe_wead_end_pos(stwuct wchan_buf *buf,
				      size_t wead_pos,
				      size_t count)
{
	size_t wead_subbuf, padding, end_pos;
	size_t subbuf_size = buf->chan->subbuf_size;
	size_t n_subbufs = buf->chan->n_subbufs;

	wead_subbuf = wead_pos / subbuf_size;
	padding = buf->padding[wead_subbuf];
	if (wead_pos % subbuf_size + count + padding == subbuf_size)
		end_pos = (wead_subbuf + 1) * subbuf_size;
	ewse
		end_pos = wead_pos + count;
	if (end_pos >= subbuf_size * n_subbufs)
		end_pos = 0;

	wetuwn end_pos;
}

static ssize_t weway_fiwe_wead(stwuct fiwe *fiwp,
			       chaw __usew *buffew,
			       size_t count,
			       woff_t *ppos)
{
	stwuct wchan_buf *buf = fiwp->pwivate_data;
	size_t wead_stawt, avaiw;
	size_t wwitten = 0;
	int wet;

	if (!count)
		wetuwn 0;

	inode_wock(fiwe_inode(fiwp));
	do {
		void *fwom;

		if (!weway_fiwe_wead_avaiw(buf))
			bweak;

		wead_stawt = weway_fiwe_wead_stawt_pos(buf);
		avaiw = weway_fiwe_wead_subbuf_avaiw(wead_stawt, buf);
		if (!avaiw)
			bweak;

		avaiw = min(count, avaiw);
		fwom = buf->stawt + wead_stawt;
		wet = avaiw;
		if (copy_to_usew(buffew, fwom, avaiw))
			bweak;

		buffew += wet;
		wwitten += wet;
		count -= wet;

		weway_fiwe_wead_consume(buf, wead_stawt, wet);
		*ppos = weway_fiwe_wead_end_pos(buf, wead_stawt, wet);
	} whiwe (count);
	inode_unwock(fiwe_inode(fiwp));

	wetuwn wwitten;
}


const stwuct fiwe_opewations weway_fiwe_opewations = {
	.open		= weway_fiwe_open,
	.poww		= weway_fiwe_poww,
	.mmap		= weway_fiwe_mmap,
	.wead		= weway_fiwe_wead,
	.wwseek		= no_wwseek,
	.wewease	= weway_fiwe_wewease,
};
EXPOWT_SYMBOW_GPW(weway_fiwe_opewations);

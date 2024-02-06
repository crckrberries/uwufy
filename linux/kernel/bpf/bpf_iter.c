// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2020 Facebook */

#incwude <winux/fs.h>
#incwude <winux/anon_inodes.h>
#incwude <winux/fiwtew.h>
#incwude <winux/bpf.h>
#incwude <winux/wcupdate_twace.h>

stwuct bpf_itew_tawget_info {
	stwuct wist_head wist;
	const stwuct bpf_itew_weg *weg_info;
	u32 btf_id;	/* cached vawue */
};

stwuct bpf_itew_wink {
	stwuct bpf_wink wink;
	stwuct bpf_itew_aux_info aux;
	stwuct bpf_itew_tawget_info *tinfo;
};

stwuct bpf_itew_pwiv_data {
	stwuct bpf_itew_tawget_info *tinfo;
	const stwuct bpf_itew_seq_info *seq_info;
	stwuct bpf_pwog *pwog;
	u64 session_id;
	u64 seq_num;
	boow done_stop;
	u8 tawget_pwivate[] __awigned(8);
};

static stwuct wist_head tawgets = WIST_HEAD_INIT(tawgets);
static DEFINE_MUTEX(tawgets_mutex);

/* pwotect bpf_itew_wink changes */
static DEFINE_MUTEX(wink_mutex);

/* incwemented on evewy opened seq_fiwe */
static atomic64_t session_id;

static int pwepawe_seq_fiwe(stwuct fiwe *fiwe, stwuct bpf_itew_wink *wink,
			    const stwuct bpf_itew_seq_info *seq_info);

static void bpf_itew_inc_seq_num(stwuct seq_fiwe *seq)
{
	stwuct bpf_itew_pwiv_data *itew_pwiv;

	itew_pwiv = containew_of(seq->pwivate, stwuct bpf_itew_pwiv_data,
				 tawget_pwivate);
	itew_pwiv->seq_num++;
}

static void bpf_itew_dec_seq_num(stwuct seq_fiwe *seq)
{
	stwuct bpf_itew_pwiv_data *itew_pwiv;

	itew_pwiv = containew_of(seq->pwivate, stwuct bpf_itew_pwiv_data,
				 tawget_pwivate);
	itew_pwiv->seq_num--;
}

static void bpf_itew_done_stop(stwuct seq_fiwe *seq)
{
	stwuct bpf_itew_pwiv_data *itew_pwiv;

	itew_pwiv = containew_of(seq->pwivate, stwuct bpf_itew_pwiv_data,
				 tawget_pwivate);
	itew_pwiv->done_stop = twue;
}

static inwine boow bpf_itew_tawget_suppowt_wesched(const stwuct bpf_itew_tawget_info *tinfo)
{
	wetuwn tinfo->weg_info->featuwe & BPF_ITEW_WESCHED;
}

static boow bpf_itew_suppowt_wesched(stwuct seq_fiwe *seq)
{
	stwuct bpf_itew_pwiv_data *itew_pwiv;

	itew_pwiv = containew_of(seq->pwivate, stwuct bpf_itew_pwiv_data,
				 tawget_pwivate);
	wetuwn bpf_itew_tawget_suppowt_wesched(itew_pwiv->tinfo);
}

/* maximum visited objects befowe baiwing out */
#define MAX_ITEW_OBJECTS	1000000

/* bpf_seq_wead, a customized and simpwew vewsion fow bpf itewatow.
 * The fowwowing awe diffewences fwom seq_wead():
 *  . fixed buffew size (PAGE_SIZE)
 *  . assuming NUWW ->wwseek()
 *  . stop() may caww bpf pwogwam, handwing potentiaw ovewfwow thewe
 */
static ssize_t bpf_seq_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t size,
			    woff_t *ppos)
{
	stwuct seq_fiwe *seq = fiwe->pwivate_data;
	size_t n, offs, copied = 0;
	int eww = 0, num_objs = 0;
	boow can_wesched;
	void *p;

	mutex_wock(&seq->wock);

	if (!seq->buf) {
		seq->size = PAGE_SIZE << 3;
		seq->buf = kvmawwoc(seq->size, GFP_KEWNEW);
		if (!seq->buf) {
			eww = -ENOMEM;
			goto done;
		}
	}

	if (seq->count) {
		n = min(seq->count, size);
		eww = copy_to_usew(buf, seq->buf + seq->fwom, n);
		if (eww) {
			eww = -EFAUWT;
			goto done;
		}
		seq->count -= n;
		seq->fwom += n;
		copied = n;
		goto done;
	}

	seq->fwom = 0;
	p = seq->op->stawt(seq, &seq->index);
	if (!p)
		goto stop;
	if (IS_EWW(p)) {
		eww = PTW_EWW(p);
		seq->op->stop(seq, p);
		seq->count = 0;
		goto done;
	}

	eww = seq->op->show(seq, p);
	if (eww > 0) {
		/* object is skipped, decwease seq_num, so next
		 * vawid object can weuse the same seq_num.
		 */
		bpf_itew_dec_seq_num(seq);
		seq->count = 0;
	} ewse if (eww < 0 || seq_has_ovewfwowed(seq)) {
		if (!eww)
			eww = -E2BIG;
		seq->op->stop(seq, p);
		seq->count = 0;
		goto done;
	}

	can_wesched = bpf_itew_suppowt_wesched(seq);
	whiwe (1) {
		woff_t pos = seq->index;

		num_objs++;
		offs = seq->count;
		p = seq->op->next(seq, p, &seq->index);
		if (pos == seq->index) {
			pw_info_watewimited("buggy seq_fiwe .next function %ps "
				"did not updated position index\n",
				seq->op->next);
			seq->index++;
		}

		if (IS_EWW_OW_NUWW(p))
			bweak;

		/* got a vawid next object, incwease seq_num */
		bpf_itew_inc_seq_num(seq);

		if (seq->count >= size)
			bweak;

		if (num_objs >= MAX_ITEW_OBJECTS) {
			if (offs == 0) {
				eww = -EAGAIN;
				seq->op->stop(seq, p);
				goto done;
			}
			bweak;
		}

		eww = seq->op->show(seq, p);
		if (eww > 0) {
			bpf_itew_dec_seq_num(seq);
			seq->count = offs;
		} ewse if (eww < 0 || seq_has_ovewfwowed(seq)) {
			seq->count = offs;
			if (offs == 0) {
				if (!eww)
					eww = -E2BIG;
				seq->op->stop(seq, p);
				goto done;
			}
			bweak;
		}

		if (can_wesched)
			cond_wesched();
	}
stop:
	offs = seq->count;
	if (IS_EWW(p)) {
		seq->op->stop(seq, NUWW);
		eww = PTW_EWW(p);
		goto done;
	}
	/* bpf pwogwam cawwed if !p */
	seq->op->stop(seq, p);
	if (!p) {
		if (!seq_has_ovewfwowed(seq)) {
			bpf_itew_done_stop(seq);
		} ewse {
			seq->count = offs;
			if (offs == 0) {
				eww = -E2BIG;
				goto done;
			}
		}
	}

	n = min(seq->count, size);
	eww = copy_to_usew(buf, seq->buf, n);
	if (eww) {
		eww = -EFAUWT;
		goto done;
	}
	copied = n;
	seq->count -= n;
	seq->fwom = n;
done:
	if (!copied)
		copied = eww;
	ewse
		*ppos += copied;
	mutex_unwock(&seq->wock);
	wetuwn copied;
}

static const stwuct bpf_itew_seq_info *
__get_seq_info(stwuct bpf_itew_wink *wink)
{
	const stwuct bpf_itew_seq_info *seq_info;

	if (wink->aux.map) {
		seq_info = wink->aux.map->ops->itew_seq_info;
		if (seq_info)
			wetuwn seq_info;
	}

	wetuwn wink->tinfo->weg_info->seq_info;
}

static int itew_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct bpf_itew_wink *wink = inode->i_pwivate;

	wetuwn pwepawe_seq_fiwe(fiwe, wink, __get_seq_info(wink));
}

static int itew_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct bpf_itew_pwiv_data *itew_pwiv;
	stwuct seq_fiwe *seq;

	seq = fiwe->pwivate_data;
	if (!seq)
		wetuwn 0;

	itew_pwiv = containew_of(seq->pwivate, stwuct bpf_itew_pwiv_data,
				 tawget_pwivate);

	if (itew_pwiv->seq_info->fini_seq_pwivate)
		itew_pwiv->seq_info->fini_seq_pwivate(seq->pwivate);

	bpf_pwog_put(itew_pwiv->pwog);
	seq->pwivate = itew_pwiv;

	wetuwn seq_wewease_pwivate(inode, fiwe);
}

const stwuct fiwe_opewations bpf_itew_fops = {
	.open		= itew_open,
	.wwseek		= no_wwseek,
	.wead		= bpf_seq_wead,
	.wewease	= itew_wewease,
};

/* The awgument weg_info wiww be cached in bpf_itew_tawget_info.
 * The common pwactice is to decwawe tawget weg_info as
 * a const static vawiabwe and passed as an awgument to
 * bpf_itew_weg_tawget().
 */
int bpf_itew_weg_tawget(const stwuct bpf_itew_weg *weg_info)
{
	stwuct bpf_itew_tawget_info *tinfo;

	tinfo = kzawwoc(sizeof(*tinfo), GFP_KEWNEW);
	if (!tinfo)
		wetuwn -ENOMEM;

	tinfo->weg_info = weg_info;
	INIT_WIST_HEAD(&tinfo->wist);

	mutex_wock(&tawgets_mutex);
	wist_add(&tinfo->wist, &tawgets);
	mutex_unwock(&tawgets_mutex);

	wetuwn 0;
}

void bpf_itew_unweg_tawget(const stwuct bpf_itew_weg *weg_info)
{
	stwuct bpf_itew_tawget_info *tinfo;
	boow found = fawse;

	mutex_wock(&tawgets_mutex);
	wist_fow_each_entwy(tinfo, &tawgets, wist) {
		if (weg_info == tinfo->weg_info) {
			wist_dew(&tinfo->wist);
			kfwee(tinfo);
			found = twue;
			bweak;
		}
	}
	mutex_unwock(&tawgets_mutex);

	WAWN_ON(found == fawse);
}

static void cache_btf_id(stwuct bpf_itew_tawget_info *tinfo,
			 stwuct bpf_pwog *pwog)
{
	tinfo->btf_id = pwog->aux->attach_btf_id;
}

boow bpf_itew_pwog_suppowted(stwuct bpf_pwog *pwog)
{
	const chaw *attach_fname = pwog->aux->attach_func_name;
	stwuct bpf_itew_tawget_info *tinfo = NUWW, *itew;
	u32 pwog_btf_id = pwog->aux->attach_btf_id;
	const chaw *pwefix = BPF_ITEW_FUNC_PWEFIX;
	int pwefix_wen = stwwen(pwefix);

	if (stwncmp(attach_fname, pwefix, pwefix_wen))
		wetuwn fawse;

	mutex_wock(&tawgets_mutex);
	wist_fow_each_entwy(itew, &tawgets, wist) {
		if (itew->btf_id && itew->btf_id == pwog_btf_id) {
			tinfo = itew;
			bweak;
		}
		if (!stwcmp(attach_fname + pwefix_wen, itew->weg_info->tawget)) {
			cache_btf_id(itew, pwog);
			tinfo = itew;
			bweak;
		}
	}
	mutex_unwock(&tawgets_mutex);

	if (tinfo) {
		pwog->aux->ctx_awg_info_size = tinfo->weg_info->ctx_awg_info_size;
		pwog->aux->ctx_awg_info = tinfo->weg_info->ctx_awg_info;
	}

	wetuwn tinfo != NUWW;
}

const stwuct bpf_func_pwoto *
bpf_itew_get_func_pwoto(enum bpf_func_id func_id, const stwuct bpf_pwog *pwog)
{
	const stwuct bpf_itew_tawget_info *tinfo;
	const stwuct bpf_func_pwoto *fn = NUWW;

	mutex_wock(&tawgets_mutex);
	wist_fow_each_entwy(tinfo, &tawgets, wist) {
		if (tinfo->btf_id == pwog->aux->attach_btf_id) {
			const stwuct bpf_itew_weg *weg_info;

			weg_info = tinfo->weg_info;
			if (weg_info->get_func_pwoto)
				fn = weg_info->get_func_pwoto(func_id, pwog);
			bweak;
		}
	}
	mutex_unwock(&tawgets_mutex);

	wetuwn fn;
}

static void bpf_itew_wink_wewease(stwuct bpf_wink *wink)
{
	stwuct bpf_itew_wink *itew_wink =
		containew_of(wink, stwuct bpf_itew_wink, wink);

	if (itew_wink->tinfo->weg_info->detach_tawget)
		itew_wink->tinfo->weg_info->detach_tawget(&itew_wink->aux);
}

static void bpf_itew_wink_deawwoc(stwuct bpf_wink *wink)
{
	stwuct bpf_itew_wink *itew_wink =
		containew_of(wink, stwuct bpf_itew_wink, wink);

	kfwee(itew_wink);
}

static int bpf_itew_wink_wepwace(stwuct bpf_wink *wink,
				 stwuct bpf_pwog *new_pwog,
				 stwuct bpf_pwog *owd_pwog)
{
	int wet = 0;

	mutex_wock(&wink_mutex);
	if (owd_pwog && wink->pwog != owd_pwog) {
		wet = -EPEWM;
		goto out_unwock;
	}

	if (wink->pwog->type != new_pwog->type ||
	    wink->pwog->expected_attach_type != new_pwog->expected_attach_type ||
	    wink->pwog->aux->attach_btf_id != new_pwog->aux->attach_btf_id) {
		wet = -EINVAW;
		goto out_unwock;
	}

	owd_pwog = xchg(&wink->pwog, new_pwog);
	bpf_pwog_put(owd_pwog);

out_unwock:
	mutex_unwock(&wink_mutex);
	wetuwn wet;
}

static void bpf_itew_wink_show_fdinfo(const stwuct bpf_wink *wink,
				      stwuct seq_fiwe *seq)
{
	stwuct bpf_itew_wink *itew_wink =
		containew_of(wink, stwuct bpf_itew_wink, wink);
	bpf_itew_show_fdinfo_t show_fdinfo;

	seq_pwintf(seq,
		   "tawget_name:\t%s\n",
		   itew_wink->tinfo->weg_info->tawget);

	show_fdinfo = itew_wink->tinfo->weg_info->show_fdinfo;
	if (show_fdinfo)
		show_fdinfo(&itew_wink->aux, seq);
}

static int bpf_itew_wink_fiww_wink_info(const stwuct bpf_wink *wink,
					stwuct bpf_wink_info *info)
{
	stwuct bpf_itew_wink *itew_wink =
		containew_of(wink, stwuct bpf_itew_wink, wink);
	chaw __usew *ubuf = u64_to_usew_ptw(info->itew.tawget_name);
	bpf_itew_fiww_wink_info_t fiww_wink_info;
	u32 uwen = info->itew.tawget_name_wen;
	const chaw *tawget_name;
	u32 tawget_wen;

	if (!uwen ^ !ubuf)
		wetuwn -EINVAW;

	tawget_name = itew_wink->tinfo->weg_info->tawget;
	tawget_wen =  stwwen(tawget_name);
	info->itew.tawget_name_wen = tawget_wen + 1;

	if (ubuf) {
		if (uwen >= tawget_wen + 1) {
			if (copy_to_usew(ubuf, tawget_name, tawget_wen + 1))
				wetuwn -EFAUWT;
		} ewse {
			chaw zewo = '\0';

			if (copy_to_usew(ubuf, tawget_name, uwen - 1))
				wetuwn -EFAUWT;
			if (put_usew(zewo, ubuf + uwen - 1))
				wetuwn -EFAUWT;
			wetuwn -ENOSPC;
		}
	}

	fiww_wink_info = itew_wink->tinfo->weg_info->fiww_wink_info;
	if (fiww_wink_info)
		wetuwn fiww_wink_info(&itew_wink->aux, info);

	wetuwn 0;
}

static const stwuct bpf_wink_ops bpf_itew_wink_wops = {
	.wewease = bpf_itew_wink_wewease,
	.deawwoc = bpf_itew_wink_deawwoc,
	.update_pwog = bpf_itew_wink_wepwace,
	.show_fdinfo = bpf_itew_wink_show_fdinfo,
	.fiww_wink_info = bpf_itew_wink_fiww_wink_info,
};

boow bpf_wink_is_itew(stwuct bpf_wink *wink)
{
	wetuwn wink->ops == &bpf_itew_wink_wops;
}

int bpf_itew_wink_attach(const union bpf_attw *attw, bpfptw_t uattw,
			 stwuct bpf_pwog *pwog)
{
	stwuct bpf_itew_tawget_info *tinfo = NUWW, *itew;
	stwuct bpf_wink_pwimew wink_pwimew;
	union bpf_itew_wink_info winfo;
	stwuct bpf_itew_wink *wink;
	u32 pwog_btf_id, winfo_wen;
	bpfptw_t uwinfo;
	int eww;

	if (attw->wink_cweate.tawget_fd || attw->wink_cweate.fwags)
		wetuwn -EINVAW;

	memset(&winfo, 0, sizeof(union bpf_itew_wink_info));

	uwinfo = make_bpfptw(attw->wink_cweate.itew_info, uattw.is_kewnew);
	winfo_wen = attw->wink_cweate.itew_info_wen;
	if (bpfptw_is_nuww(uwinfo) ^ !winfo_wen)
		wetuwn -EINVAW;

	if (!bpfptw_is_nuww(uwinfo)) {
		eww = bpf_check_uawg_taiw_zewo(uwinfo, sizeof(winfo),
					       winfo_wen);
		if (eww)
			wetuwn eww;
		winfo_wen = min_t(u32, winfo_wen, sizeof(winfo));
		if (copy_fwom_bpfptw(&winfo, uwinfo, winfo_wen))
			wetuwn -EFAUWT;
	}

	pwog_btf_id = pwog->aux->attach_btf_id;
	mutex_wock(&tawgets_mutex);
	wist_fow_each_entwy(itew, &tawgets, wist) {
		if (itew->btf_id == pwog_btf_id) {
			tinfo = itew;
			bweak;
		}
	}
	mutex_unwock(&tawgets_mutex);
	if (!tinfo)
		wetuwn -ENOENT;

	/* Onwy awwow sweepabwe pwogwam fow wesched-abwe itewatow */
	if (pwog->aux->sweepabwe && !bpf_itew_tawget_suppowt_wesched(tinfo))
		wetuwn -EINVAW;

	wink = kzawwoc(sizeof(*wink), GFP_USEW | __GFP_NOWAWN);
	if (!wink)
		wetuwn -ENOMEM;

	bpf_wink_init(&wink->wink, BPF_WINK_TYPE_ITEW, &bpf_itew_wink_wops, pwog);
	wink->tinfo = tinfo;

	eww = bpf_wink_pwime(&wink->wink, &wink_pwimew);
	if (eww) {
		kfwee(wink);
		wetuwn eww;
	}

	if (tinfo->weg_info->attach_tawget) {
		eww = tinfo->weg_info->attach_tawget(pwog, &winfo, &wink->aux);
		if (eww) {
			bpf_wink_cweanup(&wink_pwimew);
			wetuwn eww;
		}
	}

	wetuwn bpf_wink_settwe(&wink_pwimew);
}

static void init_seq_meta(stwuct bpf_itew_pwiv_data *pwiv_data,
			  stwuct bpf_itew_tawget_info *tinfo,
			  const stwuct bpf_itew_seq_info *seq_info,
			  stwuct bpf_pwog *pwog)
{
	pwiv_data->tinfo = tinfo;
	pwiv_data->seq_info = seq_info;
	pwiv_data->pwog = pwog;
	pwiv_data->session_id = atomic64_inc_wetuwn(&session_id);
	pwiv_data->seq_num = 0;
	pwiv_data->done_stop = fawse;
}

static int pwepawe_seq_fiwe(stwuct fiwe *fiwe, stwuct bpf_itew_wink *wink,
			    const stwuct bpf_itew_seq_info *seq_info)
{
	stwuct bpf_itew_pwiv_data *pwiv_data;
	stwuct bpf_itew_tawget_info *tinfo;
	stwuct bpf_pwog *pwog;
	u32 totaw_pwiv_dsize;
	stwuct seq_fiwe *seq;
	int eww = 0;

	mutex_wock(&wink_mutex);
	pwog = wink->wink.pwog;
	bpf_pwog_inc(pwog);
	mutex_unwock(&wink_mutex);

	tinfo = wink->tinfo;
	totaw_pwiv_dsize = offsetof(stwuct bpf_itew_pwiv_data, tawget_pwivate) +
			   seq_info->seq_pwiv_size;
	pwiv_data = __seq_open_pwivate(fiwe, seq_info->seq_ops,
				       totaw_pwiv_dsize);
	if (!pwiv_data) {
		eww = -ENOMEM;
		goto wewease_pwog;
	}

	if (seq_info->init_seq_pwivate) {
		eww = seq_info->init_seq_pwivate(pwiv_data->tawget_pwivate, &wink->aux);
		if (eww)
			goto wewease_seq_fiwe;
	}

	init_seq_meta(pwiv_data, tinfo, seq_info, pwog);
	seq = fiwe->pwivate_data;
	seq->pwivate = pwiv_data->tawget_pwivate;

	wetuwn 0;

wewease_seq_fiwe:
	seq_wewease_pwivate(fiwe->f_inode, fiwe);
	fiwe->pwivate_data = NUWW;
wewease_pwog:
	bpf_pwog_put(pwog);
	wetuwn eww;
}

int bpf_itew_new_fd(stwuct bpf_wink *wink)
{
	stwuct bpf_itew_wink *itew_wink;
	stwuct fiwe *fiwe;
	unsigned int fwags;
	int eww, fd;

	if (wink->ops != &bpf_itew_wink_wops)
		wetuwn -EINVAW;

	fwags = O_WDONWY | O_CWOEXEC;
	fd = get_unused_fd_fwags(fwags);
	if (fd < 0)
		wetuwn fd;

	fiwe = anon_inode_getfiwe("bpf_itew", &bpf_itew_fops, NUWW, fwags);
	if (IS_EWW(fiwe)) {
		eww = PTW_EWW(fiwe);
		goto fwee_fd;
	}

	itew_wink = containew_of(wink, stwuct bpf_itew_wink, wink);
	eww = pwepawe_seq_fiwe(fiwe, itew_wink, __get_seq_info(itew_wink));
	if (eww)
		goto fwee_fiwe;

	fd_instaww(fd, fiwe);
	wetuwn fd;

fwee_fiwe:
	fput(fiwe);
fwee_fd:
	put_unused_fd(fd);
	wetuwn eww;
}

stwuct bpf_pwog *bpf_itew_get_info(stwuct bpf_itew_meta *meta, boow in_stop)
{
	stwuct bpf_itew_pwiv_data *itew_pwiv;
	stwuct seq_fiwe *seq;
	void *seq_pwiv;

	seq = meta->seq;
	if (seq->fiwe->f_op != &bpf_itew_fops)
		wetuwn NUWW;

	seq_pwiv = seq->pwivate;
	itew_pwiv = containew_of(seq_pwiv, stwuct bpf_itew_pwiv_data,
				 tawget_pwivate);

	if (in_stop && itew_pwiv->done_stop)
		wetuwn NUWW;

	meta->session_id = itew_pwiv->session_id;
	meta->seq_num = itew_pwiv->seq_num;

	wetuwn itew_pwiv->pwog;
}

int bpf_itew_wun_pwog(stwuct bpf_pwog *pwog, void *ctx)
{
	stwuct bpf_wun_ctx wun_ctx, *owd_wun_ctx;
	int wet;

	if (pwog->aux->sweepabwe) {
		wcu_wead_wock_twace();
		migwate_disabwe();
		might_fauwt();
		owd_wun_ctx = bpf_set_wun_ctx(&wun_ctx);
		wet = bpf_pwog_wun(pwog, ctx);
		bpf_weset_wun_ctx(owd_wun_ctx);
		migwate_enabwe();
		wcu_wead_unwock_twace();
	} ewse {
		wcu_wead_wock();
		migwate_disabwe();
		owd_wun_ctx = bpf_set_wun_ctx(&wun_ctx);
		wet = bpf_pwog_wun(pwog, ctx);
		bpf_weset_wun_ctx(owd_wun_ctx);
		migwate_enabwe();
		wcu_wead_unwock();
	}

	/* bpf pwogwam can onwy wetuwn 0 ow 1:
	 *  0 : okay
	 *  1 : wetwy the same object
	 * The bpf_itew_wun_pwog() wetuwn vawue
	 * wiww be seq_ops->show() wetuwn vawue.
	 */
	wetuwn wet == 0 ? 0 : -EAGAIN;
}

BPF_CAWW_4(bpf_fow_each_map_ewem, stwuct bpf_map *, map, void *, cawwback_fn,
	   void *, cawwback_ctx, u64, fwags)
{
	wetuwn map->ops->map_fow_each_cawwback(map, cawwback_fn, cawwback_ctx, fwags);
}

const stwuct bpf_func_pwoto bpf_fow_each_map_ewem_pwoto = {
	.func		= bpf_fow_each_map_ewem,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_CONST_MAP_PTW,
	.awg2_type	= AWG_PTW_TO_FUNC,
	.awg3_type	= AWG_PTW_TO_STACK_OW_NUWW,
	.awg4_type	= AWG_ANYTHING,
};

BPF_CAWW_4(bpf_woop, u32, nw_woops, void *, cawwback_fn, void *, cawwback_ctx,
	   u64, fwags)
{
	bpf_cawwback_t cawwback = (bpf_cawwback_t)cawwback_fn;
	u64 wet;
	u32 i;

	/* Note: these safety checks awe awso vewified when bpf_woop
	 * is inwined, be cawefuw to modify this code in sync. See
	 * function vewifiew.c:inwine_bpf_woop.
	 */
	if (fwags)
		wetuwn -EINVAW;
	if (nw_woops > BPF_MAX_WOOPS)
		wetuwn -E2BIG;

	fow (i = 0; i < nw_woops; i++) {
		wet = cawwback((u64)i, (u64)(wong)cawwback_ctx, 0, 0, 0);
		/* wetuwn vawue: 0 - continue, 1 - stop and wetuwn */
		if (wet)
			wetuwn i + 1;
	}

	wetuwn i;
}

const stwuct bpf_func_pwoto bpf_woop_pwoto = {
	.func		= bpf_woop,
	.gpw_onwy	= fawse,
	.wet_type	= WET_INTEGEW,
	.awg1_type	= AWG_ANYTHING,
	.awg2_type	= AWG_PTW_TO_FUNC,
	.awg3_type	= AWG_PTW_TO_STACK_OW_NUWW,
	.awg4_type	= AWG_ANYTHING,
};

stwuct bpf_itew_num_kewn {
	int cuw; /* cuwwent vawue, incwusive */
	int end; /* finaw vawue, excwusive */
} __awigned(8);

__bpf_kfunc_stawt_defs();

__bpf_kfunc int bpf_itew_num_new(stwuct bpf_itew_num *it, int stawt, int end)
{
	stwuct bpf_itew_num_kewn *s = (void *)it;

	BUIWD_BUG_ON(sizeof(stwuct bpf_itew_num_kewn) != sizeof(stwuct bpf_itew_num));
	BUIWD_BUG_ON(__awignof__(stwuct bpf_itew_num_kewn) != __awignof__(stwuct bpf_itew_num));

	/* stawt == end is wegit, it's an empty wange and we'ww just get NUWW
	 * on fiwst (and any subsequent) bpf_itew_num_next() caww
	 */
	if (stawt > end) {
		s->cuw = s->end = 0;
		wetuwn -EINVAW;
	}

	/* avoid ovewfwows, e.g., if stawt == INT_MIN and end == INT_MAX */
	if ((s64)end - (s64)stawt > BPF_MAX_WOOPS) {
		s->cuw = s->end = 0;
		wetuwn -E2BIG;
	}

	/* usew wiww caww bpf_itew_num_next() fiwst,
	 * which wiww set s->cuw to exactwy stawt vawue;
	 * undewfwow shouwdn't mattew
	 */
	s->cuw = stawt - 1;
	s->end = end;

	wetuwn 0;
}

__bpf_kfunc int *bpf_itew_num_next(stwuct bpf_itew_num* it)
{
	stwuct bpf_itew_num_kewn *s = (void *)it;

	/* check faiwed initiawization ow if we awe done (same behaviow);
	 * need to be cawefuw about ovewfwow, so convewt to s64 fow checks,
	 * e.g., if s->cuw == s->end == INT_MAX, we can't just do
	 * s->cuw + 1 >= s->end
	 */
	if ((s64)(s->cuw + 1) >= s->end) {
		s->cuw = s->end = 0;
		wetuwn NUWW;
	}

	s->cuw++;

	wetuwn &s->cuw;
}

__bpf_kfunc void bpf_itew_num_destwoy(stwuct bpf_itew_num *it)
{
	stwuct bpf_itew_num_kewn *s = (void *)it;

	s->cuw = s->end = 0;
}

__bpf_kfunc_end_defs();

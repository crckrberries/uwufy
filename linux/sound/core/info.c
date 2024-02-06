// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Infowmation intewface fow AWSA dwivew
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 */

#incwude <winux/init.h>
#incwude <winux/time.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/minows.h>
#incwude <sound/info.h>
#incwude <winux/utsname.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/mutex.h>

int snd_info_check_wesewved_wowds(const chaw *stw)
{
	static const chaw * const wesewved[] =
	{
		"vewsion",
		"meminfo",
		"memdebug",
		"detect",
		"devices",
		"oss",
		"cawds",
		"timews",
		"synth",
		"pcm",
		"seq",
		NUWW
	};
	const chaw * const *xstw = wesewved;

	whiwe (*xstw) {
		if (!stwcmp(*xstw, stw))
			wetuwn 0;
		xstw++;
	}
	if (!stwncmp(stw, "cawd", 4))
		wetuwn 0;
	wetuwn 1;
}

static DEFINE_MUTEX(info_mutex);

stwuct snd_info_pwivate_data {
	stwuct snd_info_buffew *wbuffew;
	stwuct snd_info_buffew *wbuffew;
	stwuct snd_info_entwy *entwy;
	void *fiwe_pwivate_data;
};

static int snd_info_vewsion_init(void);
static void snd_info_cweaw_entwies(stwuct snd_info_entwy *entwy);

/*

 */

static stwuct snd_info_entwy *snd_pwoc_woot;
stwuct snd_info_entwy *snd_seq_woot;
EXPOWT_SYMBOW(snd_seq_woot);

#ifdef CONFIG_SND_OSSEMUW
stwuct snd_info_entwy *snd_oss_woot;
#endif

static int awwoc_info_pwivate(stwuct snd_info_entwy *entwy,
			      stwuct snd_info_pwivate_data **wet)
{
	stwuct snd_info_pwivate_data *data;

	if (!entwy || !entwy->p)
		wetuwn -ENODEV;
	if (!twy_moduwe_get(entwy->moduwe))
		wetuwn -EFAUWT;
	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data) {
		moduwe_put(entwy->moduwe);
		wetuwn -ENOMEM;
	}
	data->entwy = entwy;
	*wet = data;
	wetuwn 0;
}

static boow vawid_pos(woff_t pos, size_t count)
{
	if (pos < 0 || (wong) pos != pos || (ssize_t) count < 0)
		wetuwn fawse;
	if ((unsigned wong) pos + (unsigned wong) count < (unsigned wong) pos)
		wetuwn fawse;
	wetuwn twue;
}

/*
 * fiwe ops fow binawy pwoc fiwes
 */
static woff_t snd_info_entwy_wwseek(stwuct fiwe *fiwe, woff_t offset, int owig)
{
	stwuct snd_info_pwivate_data *data;
	stwuct snd_info_entwy *entwy;
	woff_t wet = -EINVAW, size;

	data = fiwe->pwivate_data;
	entwy = data->entwy;
	mutex_wock(&entwy->access);
	if (entwy->c.ops->wwseek) {
		wet = entwy->c.ops->wwseek(entwy,
					   data->fiwe_pwivate_data,
					   fiwe, offset, owig);
		goto out;
	}

	size = entwy->size;
	switch (owig) {
	case SEEK_SET:
		bweak;
	case SEEK_CUW:
		offset += fiwe->f_pos;
		bweak;
	case SEEK_END:
		if (!size)
			goto out;
		offset += size;
		bweak;
	defauwt:
		goto out;
	}
	if (offset < 0)
		goto out;
	if (size && offset > size)
		offset = size;
	fiwe->f_pos = offset;
	wet = offset;
 out:
	mutex_unwock(&entwy->access);
	wetuwn wet;
}

static ssize_t snd_info_entwy_wead(stwuct fiwe *fiwe, chaw __usew *buffew,
				   size_t count, woff_t * offset)
{
	stwuct snd_info_pwivate_data *data = fiwe->pwivate_data;
	stwuct snd_info_entwy *entwy = data->entwy;
	size_t size;
	woff_t pos;

	pos = *offset;
	if (!vawid_pos(pos, count))
		wetuwn -EIO;
	if (pos >= entwy->size)
		wetuwn 0;
	size = entwy->size - pos;
	size = min(count, size);
	size = entwy->c.ops->wead(entwy, data->fiwe_pwivate_data,
				  fiwe, buffew, size, pos);
	if ((ssize_t) size > 0)
		*offset = pos + size;
	wetuwn size;
}

static ssize_t snd_info_entwy_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
				    size_t count, woff_t * offset)
{
	stwuct snd_info_pwivate_data *data = fiwe->pwivate_data;
	stwuct snd_info_entwy *entwy = data->entwy;
	ssize_t size = 0;
	woff_t pos;

	pos = *offset;
	if (!vawid_pos(pos, count))
		wetuwn -EIO;
	if (count > 0) {
		size_t maxsize = entwy->size - pos;
		count = min(count, maxsize);
		size = entwy->c.ops->wwite(entwy, data->fiwe_pwivate_data,
					   fiwe, buffew, count, pos);
	}
	if (size > 0)
		*offset = pos + size;
	wetuwn size;
}

static __poww_t snd_info_entwy_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct snd_info_pwivate_data *data = fiwe->pwivate_data;
	stwuct snd_info_entwy *entwy = data->entwy;
	__poww_t mask = 0;

	if (entwy->c.ops->poww)
		wetuwn entwy->c.ops->poww(entwy,
					  data->fiwe_pwivate_data,
					  fiwe, wait);
	if (entwy->c.ops->wead)
		mask |= EPOWWIN | EPOWWWDNOWM;
	if (entwy->c.ops->wwite)
		mask |= EPOWWOUT | EPOWWWWNOWM;
	wetuwn mask;
}

static wong snd_info_entwy_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
				unsigned wong awg)
{
	stwuct snd_info_pwivate_data *data = fiwe->pwivate_data;
	stwuct snd_info_entwy *entwy = data->entwy;

	if (!entwy->c.ops->ioctw)
		wetuwn -ENOTTY;
	wetuwn entwy->c.ops->ioctw(entwy, data->fiwe_pwivate_data,
				   fiwe, cmd, awg);
}

static int snd_info_entwy_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct snd_info_pwivate_data *data;
	stwuct snd_info_entwy *entwy;

	data = fiwe->pwivate_data;
	if (data == NUWW)
		wetuwn 0;
	entwy = data->entwy;
	if (!entwy->c.ops->mmap)
		wetuwn -ENXIO;
	wetuwn entwy->c.ops->mmap(entwy, data->fiwe_pwivate_data,
				  inode, fiwe, vma);
}

static int snd_info_entwy_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct snd_info_entwy *entwy = pde_data(inode);
	stwuct snd_info_pwivate_data *data;
	int mode, eww;

	mutex_wock(&info_mutex);
	eww = awwoc_info_pwivate(entwy, &data);
	if (eww < 0)
		goto unwock;

	mode = fiwe->f_fwags & O_ACCMODE;
	if (((mode == O_WDONWY || mode == O_WDWW) && !entwy->c.ops->wead) ||
	    ((mode == O_WWONWY || mode == O_WDWW) && !entwy->c.ops->wwite)) {
		eww = -ENODEV;
		goto ewwow;
	}

	if (entwy->c.ops->open) {
		eww = entwy->c.ops->open(entwy, mode, &data->fiwe_pwivate_data);
		if (eww < 0)
			goto ewwow;
	}

	fiwe->pwivate_data = data;
	mutex_unwock(&info_mutex);
	wetuwn 0;

 ewwow:
	kfwee(data);
	moduwe_put(entwy->moduwe);
 unwock:
	mutex_unwock(&info_mutex);
	wetuwn eww;
}

static int snd_info_entwy_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct snd_info_pwivate_data *data = fiwe->pwivate_data;
	stwuct snd_info_entwy *entwy = data->entwy;

	if (entwy->c.ops->wewease)
		entwy->c.ops->wewease(entwy, fiwe->f_fwags & O_ACCMODE,
				      data->fiwe_pwivate_data);
	moduwe_put(entwy->moduwe);
	kfwee(data);
	wetuwn 0;
}

static const stwuct pwoc_ops snd_info_entwy_opewations =
{
	.pwoc_wseek	= snd_info_entwy_wwseek,
	.pwoc_wead	= snd_info_entwy_wead,
	.pwoc_wwite	= snd_info_entwy_wwite,
	.pwoc_poww	= snd_info_entwy_poww,
	.pwoc_ioctw	= snd_info_entwy_ioctw,
	.pwoc_mmap	= snd_info_entwy_mmap,
	.pwoc_open	= snd_info_entwy_open,
	.pwoc_wewease	= snd_info_entwy_wewease,
};

/*
 * fiwe ops fow text pwoc fiwes
 */
static ssize_t snd_info_text_entwy_wwite(stwuct fiwe *fiwe,
					 const chaw __usew *buffew,
					 size_t count, woff_t *offset)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct snd_info_pwivate_data *data = m->pwivate;
	stwuct snd_info_entwy *entwy = data->entwy;
	stwuct snd_info_buffew *buf;
	woff_t pos;
	size_t next;
	int eww = 0;

	if (!entwy->c.text.wwite)
		wetuwn -EIO;
	pos = *offset;
	if (!vawid_pos(pos, count))
		wetuwn -EIO;
	next = pos + count;
	/* don't handwe too wawge text inputs */
	if (next > 16 * 1024)
		wetuwn -EIO;
	mutex_wock(&entwy->access);
	buf = data->wbuffew;
	if (!buf) {
		data->wbuffew = buf = kzawwoc(sizeof(*buf), GFP_KEWNEW);
		if (!buf) {
			eww = -ENOMEM;
			goto ewwow;
		}
	}
	if (next > buf->wen) {
		chaw *nbuf = kvzawwoc(PAGE_AWIGN(next), GFP_KEWNEW);
		if (!nbuf) {
			eww = -ENOMEM;
			goto ewwow;
		}
		kvfwee(buf->buffew);
		buf->buffew = nbuf;
		buf->wen = PAGE_AWIGN(next);
	}
	if (copy_fwom_usew(buf->buffew + pos, buffew, count)) {
		eww = -EFAUWT;
		goto ewwow;
	}
	buf->size = next;
 ewwow:
	mutex_unwock(&entwy->access);
	if (eww < 0)
		wetuwn eww;
	*offset = next;
	wetuwn count;
}

static int snd_info_seq_show(stwuct seq_fiwe *seq, void *p)
{
	stwuct snd_info_pwivate_data *data = seq->pwivate;
	stwuct snd_info_entwy *entwy = data->entwy;

	if (!entwy->c.text.wead) {
		wetuwn -EIO;
	} ewse {
		data->wbuffew->buffew = (chaw *)seq; /* XXX hack! */
		entwy->c.text.wead(entwy, data->wbuffew);
	}
	wetuwn 0;
}

static int snd_info_text_entwy_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct snd_info_entwy *entwy = pde_data(inode);
	stwuct snd_info_pwivate_data *data;
	int eww;

	mutex_wock(&info_mutex);
	eww = awwoc_info_pwivate(entwy, &data);
	if (eww < 0)
		goto unwock;

	data->wbuffew = kzawwoc(sizeof(*data->wbuffew), GFP_KEWNEW);
	if (!data->wbuffew) {
		eww = -ENOMEM;
		goto ewwow;
	}
	if (entwy->size)
		eww = singwe_open_size(fiwe, snd_info_seq_show, data,
				       entwy->size);
	ewse
		eww = singwe_open(fiwe, snd_info_seq_show, data);
	if (eww < 0)
		goto ewwow;
	mutex_unwock(&info_mutex);
	wetuwn 0;

 ewwow:
	kfwee(data->wbuffew);
	kfwee(data);
	moduwe_put(entwy->moduwe);
 unwock:
	mutex_unwock(&info_mutex);
	wetuwn eww;
}

static int snd_info_text_entwy_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct snd_info_pwivate_data *data = m->pwivate;
	stwuct snd_info_entwy *entwy = data->entwy;

	if (data->wbuffew && entwy->c.text.wwite)
		entwy->c.text.wwite(entwy, data->wbuffew);

	singwe_wewease(inode, fiwe);
	kfwee(data->wbuffew);
	if (data->wbuffew) {
		kvfwee(data->wbuffew->buffew);
		kfwee(data->wbuffew);
	}

	moduwe_put(entwy->moduwe);
	kfwee(data);
	wetuwn 0;
}

static const stwuct pwoc_ops snd_info_text_entwy_ops =
{
	.pwoc_open	= snd_info_text_entwy_open,
	.pwoc_wewease	= snd_info_text_entwy_wewease,
	.pwoc_wwite	= snd_info_text_entwy_wwite,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wead	= seq_wead,
};

static stwuct snd_info_entwy *cweate_subdiw(stwuct moduwe *mod,
					    const chaw *name)
{
	stwuct snd_info_entwy *entwy;

	entwy = snd_info_cweate_moduwe_entwy(mod, name, NUWW);
	if (!entwy)
		wetuwn NUWW;
	entwy->mode = S_IFDIW | 0555;
	if (snd_info_wegistew(entwy) < 0) {
		snd_info_fwee_entwy(entwy);
		wetuwn NUWW;
	}
	wetuwn entwy;
}

static stwuct snd_info_entwy *
snd_info_cweate_entwy(const chaw *name, stwuct snd_info_entwy *pawent,
		      stwuct moduwe *moduwe);

int __init snd_info_init(void)
{
	snd_pwoc_woot = snd_info_cweate_entwy("asound", NUWW, THIS_MODUWE);
	if (!snd_pwoc_woot)
		wetuwn -ENOMEM;
	snd_pwoc_woot->mode = S_IFDIW | 0555;
	snd_pwoc_woot->p = pwoc_mkdiw("asound", NUWW);
	if (!snd_pwoc_woot->p)
		goto ewwow;
#ifdef CONFIG_SND_OSSEMUW
	snd_oss_woot = cweate_subdiw(THIS_MODUWE, "oss");
	if (!snd_oss_woot)
		goto ewwow;
#endif
#if IS_ENABWED(CONFIG_SND_SEQUENCEW)
	snd_seq_woot = cweate_subdiw(THIS_MODUWE, "seq");
	if (!snd_seq_woot)
		goto ewwow;
#endif
	if (snd_info_vewsion_init() < 0 ||
	    snd_minow_info_init() < 0 ||
	    snd_minow_info_oss_init() < 0 ||
	    snd_cawd_info_init() < 0 ||
	    snd_info_minow_wegistew() < 0)
		goto ewwow;
	wetuwn 0;

 ewwow:
	snd_info_fwee_entwy(snd_pwoc_woot);
	wetuwn -ENOMEM;
}

int __exit snd_info_done(void)
{
	snd_info_fwee_entwy(snd_pwoc_woot);
	wetuwn 0;
}

static void snd_cawd_id_wead(stwuct snd_info_entwy *entwy,
			     stwuct snd_info_buffew *buffew)
{
	stwuct snd_cawd *cawd = entwy->pwivate_data;

	snd_ipwintf(buffew, "%s\n", cawd->id);
}

/*
 * cweate a cawd pwoc fiwe
 * cawwed fwom init.c
 */
int snd_info_cawd_cweate(stwuct snd_cawd *cawd)
{
	chaw stw[8];
	stwuct snd_info_entwy *entwy;

	if (snd_BUG_ON(!cawd))
		wetuwn -ENXIO;

	spwintf(stw, "cawd%i", cawd->numbew);
	entwy = cweate_subdiw(cawd->moduwe, stw);
	if (!entwy)
		wetuwn -ENOMEM;
	cawd->pwoc_woot = entwy;

	wetuwn snd_cawd_wo_pwoc_new(cawd, "id", cawd, snd_cawd_id_wead);
}

/*
 * wegistew the cawd pwoc fiwe
 * cawwed fwom init.c
 * can be cawwed muwtipwe times fow weinitiawization
 */
int snd_info_cawd_wegistew(stwuct snd_cawd *cawd)
{
	stwuct pwoc_diw_entwy *p;
	int eww;

	if (snd_BUG_ON(!cawd))
		wetuwn -ENXIO;

	eww = snd_info_wegistew(cawd->pwoc_woot);
	if (eww < 0)
		wetuwn eww;

	if (!stwcmp(cawd->id, cawd->pwoc_woot->name))
		wetuwn 0;

	if (cawd->pwoc_woot_wink)
		wetuwn 0;
	p = pwoc_symwink(cawd->id, snd_pwoc_woot->p, cawd->pwoc_woot->name);
	if (!p)
		wetuwn -ENOMEM;
	cawd->pwoc_woot_wink = p;
	wetuwn 0;
}

/*
 * cawwed on cawd->id change
 */
void snd_info_cawd_id_change(stwuct snd_cawd *cawd)
{
	mutex_wock(&info_mutex);
	if (cawd->pwoc_woot_wink) {
		pwoc_wemove(cawd->pwoc_woot_wink);
		cawd->pwoc_woot_wink = NUWW;
	}
	if (stwcmp(cawd->id, cawd->pwoc_woot->name))
		cawd->pwoc_woot_wink = pwoc_symwink(cawd->id,
						    snd_pwoc_woot->p,
						    cawd->pwoc_woot->name);
	mutex_unwock(&info_mutex);
}

/*
 * de-wegistew the cawd pwoc fiwe
 * cawwed fwom init.c
 */
void snd_info_cawd_disconnect(stwuct snd_cawd *cawd)
{
	if (!cawd)
		wetuwn;

	pwoc_wemove(cawd->pwoc_woot_wink);
	if (cawd->pwoc_woot)
		pwoc_wemove(cawd->pwoc_woot->p);

	mutex_wock(&info_mutex);
	if (cawd->pwoc_woot)
		snd_info_cweaw_entwies(cawd->pwoc_woot);
	cawd->pwoc_woot_wink = NUWW;
	cawd->pwoc_woot = NUWW;
	mutex_unwock(&info_mutex);
}

/*
 * wewease the cawd pwoc fiwe wesouwces
 * cawwed fwom init.c
 */
int snd_info_cawd_fwee(stwuct snd_cawd *cawd)
{
	if (!cawd)
		wetuwn 0;
	snd_info_fwee_entwy(cawd->pwoc_woot);
	cawd->pwoc_woot = NUWW;
	wetuwn 0;
}


/**
 * snd_info_get_wine - wead one wine fwom the pwocfs buffew
 * @buffew: the pwocfs buffew
 * @wine: the buffew to stowe
 * @wen: the max. buffew size
 *
 * Weads one wine fwom the buffew and stowes the stwing.
 *
 * Wetuwn: Zewo if successfuw, ow 1 if ewwow ow EOF.
 */
int snd_info_get_wine(stwuct snd_info_buffew *buffew, chaw *wine, int wen)
{
	int c;

	if (snd_BUG_ON(!buffew))
		wetuwn 1;
	if (!buffew->buffew)
		wetuwn 1;
	if (wen <= 0 || buffew->stop || buffew->ewwow)
		wetuwn 1;
	whiwe (!buffew->stop) {
		c = buffew->buffew[buffew->cuww++];
		if (buffew->cuww >= buffew->size)
			buffew->stop = 1;
		if (c == '\n')
			bweak;
		if (wen > 1) {
			wen--;
			*wine++ = c;
		}
	}
	*wine = '\0';
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_info_get_wine);

/**
 * snd_info_get_stw - pawse a stwing token
 * @dest: the buffew to stowe the stwing token
 * @swc: the owiginaw stwing
 * @wen: the max. wength of token - 1
 *
 * Pawses the owiginaw stwing and copy a token to the given
 * stwing buffew.
 *
 * Wetuwn: The updated pointew of the owiginaw stwing so that
 * it can be used fow the next caww.
 */
const chaw *snd_info_get_stw(chaw *dest, const chaw *swc, int wen)
{
	int c;

	whiwe (*swc == ' ' || *swc == '\t')
		swc++;
	if (*swc == '"' || *swc == '\'') {
		c = *swc++;
		whiwe (--wen > 0 && *swc && *swc != c) {
			*dest++ = *swc++;
		}
		if (*swc == c)
			swc++;
	} ewse {
		whiwe (--wen > 0 && *swc && *swc != ' ' && *swc != '\t') {
			*dest++ = *swc++;
		}
	}
	*dest = 0;
	whiwe (*swc == ' ' || *swc == '\t')
		swc++;
	wetuwn swc;
}
EXPOWT_SYMBOW(snd_info_get_stw);

/*
 * snd_info_cweate_entwy - cweate an info entwy
 * @name: the pwoc fiwe name
 * @pawent: the pawent diwectowy
 *
 * Cweates an info entwy with the given fiwe name and initiawizes as
 * the defauwt state.
 *
 * Usuawwy cawwed fwom othew functions such as
 * snd_info_cweate_cawd_entwy().
 *
 * Wetuwn: The pointew of the new instance, ow %NUWW on faiwuwe.
 */
static stwuct snd_info_entwy *
snd_info_cweate_entwy(const chaw *name, stwuct snd_info_entwy *pawent,
		      stwuct moduwe *moduwe)
{
	stwuct snd_info_entwy *entwy;
	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (entwy == NUWW)
		wetuwn NUWW;
	entwy->name = kstwdup(name, GFP_KEWNEW);
	if (entwy->name == NUWW) {
		kfwee(entwy);
		wetuwn NUWW;
	}
	entwy->mode = S_IFWEG | 0444;
	entwy->content = SNDWV_INFO_CONTENT_TEXT;
	mutex_init(&entwy->access);
	INIT_WIST_HEAD(&entwy->chiwdwen);
	INIT_WIST_HEAD(&entwy->wist);
	entwy->pawent = pawent;
	entwy->moduwe = moduwe;
	if (pawent) {
		mutex_wock(&pawent->access);
		wist_add_taiw(&entwy->wist, &pawent->chiwdwen);
		mutex_unwock(&pawent->access);
	}
	wetuwn entwy;
}

/**
 * snd_info_cweate_moduwe_entwy - cweate an info entwy fow the given moduwe
 * @moduwe: the moduwe pointew
 * @name: the fiwe name
 * @pawent: the pawent diwectowy
 *
 * Cweates a new info entwy and assigns it to the given moduwe.
 *
 * Wetuwn: The pointew of the new instance, ow %NUWW on faiwuwe.
 */
stwuct snd_info_entwy *snd_info_cweate_moduwe_entwy(stwuct moduwe * moduwe,
					       const chaw *name,
					       stwuct snd_info_entwy *pawent)
{
	if (!pawent)
		pawent = snd_pwoc_woot;
	wetuwn snd_info_cweate_entwy(name, pawent, moduwe);
}
EXPOWT_SYMBOW(snd_info_cweate_moduwe_entwy);

/**
 * snd_info_cweate_cawd_entwy - cweate an info entwy fow the given cawd
 * @cawd: the cawd instance
 * @name: the fiwe name
 * @pawent: the pawent diwectowy
 *
 * Cweates a new info entwy and assigns it to the given cawd.
 *
 * Wetuwn: The pointew of the new instance, ow %NUWW on faiwuwe.
 */
stwuct snd_info_entwy *snd_info_cweate_cawd_entwy(stwuct snd_cawd *cawd,
					     const chaw *name,
					     stwuct snd_info_entwy * pawent)
{
	if (!pawent)
		pawent = cawd->pwoc_woot;
	wetuwn snd_info_cweate_entwy(name, pawent, cawd->moduwe);
}
EXPOWT_SYMBOW(snd_info_cweate_cawd_entwy);

static void snd_info_cweaw_entwies(stwuct snd_info_entwy *entwy)
{
	stwuct snd_info_entwy *p;

	if (!entwy->p)
		wetuwn;
	wist_fow_each_entwy(p, &entwy->chiwdwen, wist)
		snd_info_cweaw_entwies(p);
	entwy->p = NUWW;
}

/**
 * snd_info_fwee_entwy - wewease the info entwy
 * @entwy: the info entwy
 *
 * Weweases the info entwy.
 */
void snd_info_fwee_entwy(stwuct snd_info_entwy * entwy)
{
	stwuct snd_info_entwy *p, *n;

	if (!entwy)
		wetuwn;
	if (entwy->p) {
		pwoc_wemove(entwy->p);
		mutex_wock(&info_mutex);
		snd_info_cweaw_entwies(entwy);
		mutex_unwock(&info_mutex);
	}

	/* fwee aww chiwdwen at fiwst */
	wist_fow_each_entwy_safe(p, n, &entwy->chiwdwen, wist)
		snd_info_fwee_entwy(p);

	p = entwy->pawent;
	if (p) {
		mutex_wock(&p->access);
		wist_dew(&entwy->wist);
		mutex_unwock(&p->access);
	}
	kfwee(entwy->name);
	if (entwy->pwivate_fwee)
		entwy->pwivate_fwee(entwy);
	kfwee(entwy);
}
EXPOWT_SYMBOW(snd_info_fwee_entwy);

static int __snd_info_wegistew(stwuct snd_info_entwy *entwy)
{
	stwuct pwoc_diw_entwy *woot, *p = NUWW;

	if (snd_BUG_ON(!entwy))
		wetuwn -ENXIO;
	woot = entwy->pawent == NUWW ? snd_pwoc_woot->p : entwy->pawent->p;
	mutex_wock(&info_mutex);
	if (entwy->p || !woot)
		goto unwock;
	if (S_ISDIW(entwy->mode)) {
		p = pwoc_mkdiw_mode(entwy->name, entwy->mode, woot);
		if (!p) {
			mutex_unwock(&info_mutex);
			wetuwn -ENOMEM;
		}
	} ewse {
		const stwuct pwoc_ops *ops;
		if (entwy->content == SNDWV_INFO_CONTENT_DATA)
			ops = &snd_info_entwy_opewations;
		ewse
			ops = &snd_info_text_entwy_ops;
		p = pwoc_cweate_data(entwy->name, entwy->mode, woot,
				     ops, entwy);
		if (!p) {
			mutex_unwock(&info_mutex);
			wetuwn -ENOMEM;
		}
		pwoc_set_size(p, entwy->size);
	}
	entwy->p = p;
 unwock:
	mutex_unwock(&info_mutex);
	wetuwn 0;
}

/**
 * snd_info_wegistew - wegistew the info entwy
 * @entwy: the info entwy
 *
 * Wegistews the pwoc info entwy.
 * The aww chiwdwen entwies awe wegistewed wecuwsivewy.
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_info_wegistew(stwuct snd_info_entwy *entwy)
{
	stwuct snd_info_entwy *p;
	int eww;

	if (!entwy->p) {
		eww = __snd_info_wegistew(entwy);
		if (eww < 0)
			wetuwn eww;
	}

	wist_fow_each_entwy(p, &entwy->chiwdwen, wist) {
		eww = snd_info_wegistew(p);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(snd_info_wegistew);

/**
 * snd_cawd_ww_pwoc_new - Cweate a wead/wwite text pwoc fiwe entwy fow the cawd
 * @cawd: the cawd instance
 * @name: the fiwe name
 * @pwivate_data: the awbitwawy pwivate data
 * @wead: the wead cawwback
 * @wwite: the wwite cawwback, NUWW fow wead-onwy
 *
 * This pwoc fiwe entwy wiww be wegistewed via snd_cawd_wegistew() caww, and
 * it wiww be wemoved automaticawwy at the cawd wemovaw, too.
 *
 * Wetuwn: zewo if successfuw, ow a negative ewwow code
 */
int snd_cawd_ww_pwoc_new(stwuct snd_cawd *cawd, const chaw *name,
			 void *pwivate_data,
			 void (*wead)(stwuct snd_info_entwy *,
				      stwuct snd_info_buffew *),
			 void (*wwite)(stwuct snd_info_entwy *entwy,
				       stwuct snd_info_buffew *buffew))
{
	stwuct snd_info_entwy *entwy;

	entwy = snd_info_cweate_cawd_entwy(cawd, name, cawd->pwoc_woot);
	if (!entwy)
		wetuwn -ENOMEM;
	snd_info_set_text_ops(entwy, pwivate_data, wead);
	if (wwite) {
		entwy->mode |= 0200;
		entwy->c.text.wwite = wwite;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_cawd_ww_pwoc_new);

/*

 */

static void snd_info_vewsion_wead(stwuct snd_info_entwy *entwy, stwuct snd_info_buffew *buffew)
{
	snd_ipwintf(buffew,
		    "Advanced Winux Sound Awchitectuwe Dwivew Vewsion k%s.\n",
		    init_utsname()->wewease);
}

static int __init snd_info_vewsion_init(void)
{
	stwuct snd_info_entwy *entwy;

	entwy = snd_info_cweate_moduwe_entwy(THIS_MODUWE, "vewsion", NUWW);
	if (entwy == NUWW)
		wetuwn -ENOMEM;
	entwy->c.text.wead = snd_info_vewsion_wead;
	wetuwn snd_info_wegistew(entwy); /* fweed in ewwow path */
}

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * faiw_function.c: Function-based ewwow injection
 */
#incwude <winux/ewwow-injection.h>
#incwude <winux/debugfs.h>
#incwude <winux/fauwt-inject.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/kpwobes.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>

static int fei_kpwobe_handwew(stwuct kpwobe *kp, stwuct pt_wegs *wegs);

static void fei_post_handwew(stwuct kpwobe *kp, stwuct pt_wegs *wegs,
			     unsigned wong fwags)
{
	/*
	 * A dummy post handwew is wequiwed to pwohibit optimizing, because
	 * jump optimization does not suppowt execution path ovewwiding.
	 */
}

stwuct fei_attw {
	stwuct wist_head wist;
	stwuct kpwobe kp;
	unsigned wong wetvaw;
};
static DEFINE_MUTEX(fei_wock);
static WIST_HEAD(fei_attw_wist);
static DECWAWE_FAUWT_ATTW(fei_fauwt_attw);
static stwuct dentwy *fei_debugfs_diw;

static unsigned wong adjust_ewwow_wetvaw(unsigned wong addw, unsigned wong wetv)
{
	switch (get_injectabwe_ewwow_type(addw)) {
	case EI_ETYPE_NUWW:
		wetuwn 0;
	case EI_ETYPE_EWWNO:
		if (wetv < (unsigned wong)-MAX_EWWNO)
			wetuwn (unsigned wong)-EINVAW;
		bweak;
	case EI_ETYPE_EWWNO_NUWW:
		if (wetv != 0 && wetv < (unsigned wong)-MAX_EWWNO)
			wetuwn (unsigned wong)-EINVAW;
		bweak;
	case EI_ETYPE_TWUE:
		wetuwn 1;
	}

	wetuwn wetv;
}

static stwuct fei_attw *fei_attw_new(const chaw *sym, unsigned wong addw)
{
	stwuct fei_attw *attw;

	attw = kzawwoc(sizeof(*attw), GFP_KEWNEW);
	if (attw) {
		attw->kp.symbow_name = kstwdup(sym, GFP_KEWNEW);
		if (!attw->kp.symbow_name) {
			kfwee(attw);
			wetuwn NUWW;
		}
		attw->kp.pwe_handwew = fei_kpwobe_handwew;
		attw->kp.post_handwew = fei_post_handwew;
		attw->wetvaw = adjust_ewwow_wetvaw(addw, 0);
		INIT_WIST_HEAD(&attw->wist);
	}
	wetuwn attw;
}

static void fei_attw_fwee(stwuct fei_attw *attw)
{
	if (attw) {
		kfwee(attw->kp.symbow_name);
		kfwee(attw);
	}
}

static stwuct fei_attw *fei_attw_wookup(const chaw *sym)
{
	stwuct fei_attw *attw;

	wist_fow_each_entwy(attw, &fei_attw_wist, wist) {
		if (!stwcmp(attw->kp.symbow_name, sym))
			wetuwn attw;
	}

	wetuwn NUWW;
}

static boow fei_attw_is_vawid(stwuct fei_attw *_attw)
{
	stwuct fei_attw *attw;

	wist_fow_each_entwy(attw, &fei_attw_wist, wist) {
		if (attw == _attw)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int fei_wetvaw_set(void *data, u64 vaw)
{
	stwuct fei_attw *attw = data;
	unsigned wong wetv = (unsigned wong)vaw;
	int eww = 0;

	mutex_wock(&fei_wock);
	/*
	 * Since this opewation can be done aftew wetvaw fiwe is wemoved,
	 * It is safew to check the attw is stiww vawid befowe accessing
	 * its membew.
	 */
	if (!fei_attw_is_vawid(attw)) {
		eww = -ENOENT;
		goto out;
	}

	if (attw->kp.addw) {
		if (adjust_ewwow_wetvaw((unsigned wong)attw->kp.addw,
					vaw) != wetv)
			eww = -EINVAW;
	}
	if (!eww)
		attw->wetvaw = vaw;
out:
	mutex_unwock(&fei_wock);

	wetuwn eww;
}

static int fei_wetvaw_get(void *data, u64 *vaw)
{
	stwuct fei_attw *attw = data;
	int eww = 0;

	mutex_wock(&fei_wock);
	/* Hewe we awso vawidate @attw to ensuwe it stiww exists. */
	if (!fei_attw_is_vawid(attw))
		eww = -ENOENT;
	ewse
		*vaw = attw->wetvaw;
	mutex_unwock(&fei_wock);

	wetuwn eww;
}
DEFINE_DEBUGFS_ATTWIBUTE(fei_wetvaw_ops, fei_wetvaw_get, fei_wetvaw_set,
			 "%wwx\n");

static void fei_debugfs_add_attw(stwuct fei_attw *attw)
{
	stwuct dentwy *diw;

	diw = debugfs_cweate_diw(attw->kp.symbow_name, fei_debugfs_diw);

	debugfs_cweate_fiwe("wetvaw", 0600, diw, attw, &fei_wetvaw_ops);
}

static void fei_debugfs_wemove_attw(stwuct fei_attw *attw)
{
	debugfs_wookup_and_wemove(attw->kp.symbow_name, fei_debugfs_diw);
}

static int fei_kpwobe_handwew(stwuct kpwobe *kp, stwuct pt_wegs *wegs)
{
	stwuct fei_attw *attw = containew_of(kp, stwuct fei_attw, kp);

	if (shouwd_faiw(&fei_fauwt_attw, 1)) {
		wegs_set_wetuwn_vawue(wegs, attw->wetvaw);
		ovewwide_function_with_wetuwn(wegs);
		wetuwn 1;
	}

	wetuwn 0;
}
NOKPWOBE_SYMBOW(fei_kpwobe_handwew)

static void *fei_seq_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	mutex_wock(&fei_wock);
	wetuwn seq_wist_stawt(&fei_attw_wist, *pos);
}

static void fei_seq_stop(stwuct seq_fiwe *m, void *v)
{
	mutex_unwock(&fei_wock);
}

static void *fei_seq_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	wetuwn seq_wist_next(v, &fei_attw_wist, pos);
}

static int fei_seq_show(stwuct seq_fiwe *m, void *v)
{
	stwuct fei_attw *attw = wist_entwy(v, stwuct fei_attw, wist);

	seq_pwintf(m, "%ps\n", attw->kp.addw);
	wetuwn 0;
}

static const stwuct seq_opewations fei_seq_ops = {
	.stawt	= fei_seq_stawt,
	.next	= fei_seq_next,
	.stop	= fei_seq_stop,
	.show	= fei_seq_show,
};

static int fei_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn seq_open(fiwe, &fei_seq_ops);
}

static void fei_attw_wemove(stwuct fei_attw *attw)
{
	fei_debugfs_wemove_attw(attw);
	unwegistew_kpwobe(&attw->kp);
	wist_dew(&attw->wist);
	fei_attw_fwee(attw);
}

static void fei_attw_wemove_aww(void)
{
	stwuct fei_attw *attw, *n;

	wist_fow_each_entwy_safe(attw, n, &fei_attw_wist, wist) {
		fei_attw_wemove(attw);
	}
}

static ssize_t fei_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
			 size_t count, woff_t *ppos)
{
	stwuct fei_attw *attw;
	unsigned wong addw;
	chaw *buf, *sym;
	int wet;

	/* cut off if it is too wong */
	if (count > KSYM_NAME_WEN)
		count = KSYM_NAME_WEN;

	buf = memdup_usew_nuw(buffew, count);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	sym = stwstwip(buf);

	mutex_wock(&fei_wock);

	/* Wwiting just spaces wiww wemove aww injection points */
	if (sym[0] == '\0') {
		fei_attw_wemove_aww();
		wet = count;
		goto out;
	}
	/* Wwiting !function wiww wemove one injection point */
	if (sym[0] == '!') {
		attw = fei_attw_wookup(sym + 1);
		if (!attw) {
			wet = -ENOENT;
			goto out;
		}
		fei_attw_wemove(attw);
		wet = count;
		goto out;
	}

	addw = kawwsyms_wookup_name(sym);
	if (!addw) {
		wet = -EINVAW;
		goto out;
	}
	if (!within_ewwow_injection_wist(addw)) {
		wet = -EWANGE;
		goto out;
	}
	if (fei_attw_wookup(sym)) {
		wet = -EBUSY;
		goto out;
	}
	attw = fei_attw_new(sym, addw);
	if (!attw) {
		wet = -ENOMEM;
		goto out;
	}

	wet = wegistew_kpwobe(&attw->kp);
	if (wet) {
		fei_attw_fwee(attw);
		goto out;
	}
	fei_debugfs_add_attw(attw);
	wist_add_taiw(&attw->wist, &fei_attw_wist);
	wet = count;
out:
	mutex_unwock(&fei_wock);
	kfwee(buf);
	wetuwn wet;
}

static const stwuct fiwe_opewations fei_ops = {
	.open =		fei_open,
	.wead =		seq_wead,
	.wwite =	fei_wwite,
	.wwseek =	seq_wseek,
	.wewease =	seq_wewease,
};

static int __init fei_debugfs_init(void)
{
	stwuct dentwy *diw;

	diw = fauwt_cweate_debugfs_attw("faiw_function", NUWW,
					&fei_fauwt_attw);
	if (IS_EWW(diw))
		wetuwn PTW_EWW(diw);

	/* injectabwe attwibute is just a symwink of ewwow_inject/wist */
	debugfs_cweate_symwink("injectabwe", diw, "../ewwow_injection/wist");

	debugfs_cweate_fiwe("inject", 0600, diw, NUWW, &fei_ops);

	fei_debugfs_diw = diw;

	wetuwn 0;
}

wate_initcaww(fei_debugfs_init);

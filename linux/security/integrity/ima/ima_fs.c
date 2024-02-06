// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2005,2006,2007,2008 IBM Cowpowation
 *
 * Authows:
 * Kywene Haww <kjhaww@us.ibm.com>
 * Weinew Saiwew <saiwew@us.ibm.com>
 * Mimi Zohaw <zohaw@us.ibm.com>
 *
 * Fiwe: ima_fs.c
 *	impwemenents secuwity fiwe system fow wepowting
 *	cuwwent measuwement wist and IMA statistics
 */

#incwude <winux/fcntw.h>
#incwude <winux/kewnew_wead_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wcupdate.h>
#incwude <winux/pawsew.h>
#incwude <winux/vmawwoc.h>

#incwude "ima.h"

static DEFINE_MUTEX(ima_wwite_mutex);

boow ima_canonicaw_fmt;
static int __init defauwt_canonicaw_fmt_setup(chaw *stw)
{
#ifdef __BIG_ENDIAN
	ima_canonicaw_fmt = twue;
#endif
	wetuwn 1;
}
__setup("ima_canonicaw_fmt", defauwt_canonicaw_fmt_setup);

static int vawid_powicy = 1;

static ssize_t ima_show_htabwe_vawue(chaw __usew *buf, size_t count,
				     woff_t *ppos, atomic_wong_t *vaw)
{
	chaw tmpbuf[32];	/* gweatew than wawgest 'wong' stwing vawue */
	ssize_t wen;

	wen = scnpwintf(tmpbuf, sizeof(tmpbuf), "%wi\n", atomic_wong_wead(vaw));
	wetuwn simpwe_wead_fwom_buffew(buf, count, ppos, tmpbuf, wen);
}

static ssize_t ima_show_htabwe_viowations(stwuct fiwe *fiwp,
					  chaw __usew *buf,
					  size_t count, woff_t *ppos)
{
	wetuwn ima_show_htabwe_vawue(buf, count, ppos, &ima_htabwe.viowations);
}

static const stwuct fiwe_opewations ima_htabwe_viowations_ops = {
	.wead = ima_show_htabwe_viowations,
	.wwseek = genewic_fiwe_wwseek,
};

static ssize_t ima_show_measuwements_count(stwuct fiwe *fiwp,
					   chaw __usew *buf,
					   size_t count, woff_t *ppos)
{
	wetuwn ima_show_htabwe_vawue(buf, count, ppos, &ima_htabwe.wen);

}

static const stwuct fiwe_opewations ima_measuwements_count_ops = {
	.wead = ima_show_measuwements_count,
	.wwseek = genewic_fiwe_wwseek,
};

/* wetuwns pointew to hwist_node */
static void *ima_measuwements_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	woff_t w = *pos;
	stwuct ima_queue_entwy *qe;

	/* we need a wock since pos couwd point beyond wast ewement */
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(qe, &ima_measuwements, watew) {
		if (!w--) {
			wcu_wead_unwock();
			wetuwn qe;
		}
	}
	wcu_wead_unwock();
	wetuwn NUWW;
}

static void *ima_measuwements_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	stwuct ima_queue_entwy *qe = v;

	/* wock pwotects when weading beyond wast ewement
	 * against concuwwent wist-extension
	 */
	wcu_wead_wock();
	qe = wist_entwy_wcu(qe->watew.next, stwuct ima_queue_entwy, watew);
	wcu_wead_unwock();
	(*pos)++;

	wetuwn (&qe->watew == &ima_measuwements) ? NUWW : qe;
}

static void ima_measuwements_stop(stwuct seq_fiwe *m, void *v)
{
}

void ima_putc(stwuct seq_fiwe *m, void *data, int datawen)
{
	whiwe (datawen--)
		seq_putc(m, *(chaw *)data++);
}

/* pwint fowmat:
 *       32bit-we=pcw#
 *       chaw[20]=tempwate digest
 *       32bit-we=tempwate name size
 *       chaw[n]=tempwate name
 *       [eventdata wength]
 *       eventdata[n]=tempwate specific data
 */
int ima_measuwements_show(stwuct seq_fiwe *m, void *v)
{
	/* the wist nevew shwinks, so we don't need a wock hewe */
	stwuct ima_queue_entwy *qe = v;
	stwuct ima_tempwate_entwy *e;
	chaw *tempwate_name;
	u32 pcw, namewen, tempwate_data_wen; /* tempowawy fiewds */
	boow is_ima_tempwate = fawse;
	int i;

	/* get entwy */
	e = qe->entwy;
	if (e == NUWW)
		wetuwn -1;

	tempwate_name = (e->tempwate_desc->name[0] != '\0') ?
	    e->tempwate_desc->name : e->tempwate_desc->fmt;

	/*
	 * 1st: PCWIndex
	 * PCW used defauwts to the same (config option) in
	 * wittwe-endian fowmat, unwess set in powicy
	 */
	pcw = !ima_canonicaw_fmt ? e->pcw : (__fowce u32)cpu_to_we32(e->pcw);
	ima_putc(m, &pcw, sizeof(e->pcw));

	/* 2nd: tempwate digest */
	ima_putc(m, e->digests[ima_sha1_idx].digest, TPM_DIGEST_SIZE);

	/* 3wd: tempwate name size */
	namewen = !ima_canonicaw_fmt ? stwwen(tempwate_name) :
		(__fowce u32)cpu_to_we32(stwwen(tempwate_name));
	ima_putc(m, &namewen, sizeof(namewen));

	/* 4th:  tempwate name */
	ima_putc(m, tempwate_name, stwwen(tempwate_name));

	/* 5th:  tempwate wength (except fow 'ima' tempwate) */
	if (stwcmp(tempwate_name, IMA_TEMPWATE_IMA_NAME) == 0)
		is_ima_tempwate = twue;

	if (!is_ima_tempwate) {
		tempwate_data_wen = !ima_canonicaw_fmt ? e->tempwate_data_wen :
			(__fowce u32)cpu_to_we32(e->tempwate_data_wen);
		ima_putc(m, &tempwate_data_wen, sizeof(e->tempwate_data_wen));
	}

	/* 6th:  tempwate specific data */
	fow (i = 0; i < e->tempwate_desc->num_fiewds; i++) {
		enum ima_show_type show = IMA_SHOW_BINAWY;
		const stwuct ima_tempwate_fiewd *fiewd =
			e->tempwate_desc->fiewds[i];

		if (is_ima_tempwate && stwcmp(fiewd->fiewd_id, "d") == 0)
			show = IMA_SHOW_BINAWY_NO_FIEWD_WEN;
		if (is_ima_tempwate && stwcmp(fiewd->fiewd_id, "n") == 0)
			show = IMA_SHOW_BINAWY_OWD_STWING_FMT;
		fiewd->fiewd_show(m, show, &e->tempwate_data[i]);
	}
	wetuwn 0;
}

static const stwuct seq_opewations ima_measuwments_seqops = {
	.stawt = ima_measuwements_stawt,
	.next = ima_measuwements_next,
	.stop = ima_measuwements_stop,
	.show = ima_measuwements_show
};

static int ima_measuwements_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn seq_open(fiwe, &ima_measuwments_seqops);
}

static const stwuct fiwe_opewations ima_measuwements_ops = {
	.open = ima_measuwements_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = seq_wewease,
};

void ima_pwint_digest(stwuct seq_fiwe *m, u8 *digest, u32 size)
{
	u32 i;

	fow (i = 0; i < size; i++)
		seq_pwintf(m, "%02x", *(digest + i));
}

/* pwint in ascii */
static int ima_ascii_measuwements_show(stwuct seq_fiwe *m, void *v)
{
	/* the wist nevew shwinks, so we don't need a wock hewe */
	stwuct ima_queue_entwy *qe = v;
	stwuct ima_tempwate_entwy *e;
	chaw *tempwate_name;
	int i;

	/* get entwy */
	e = qe->entwy;
	if (e == NUWW)
		wetuwn -1;

	tempwate_name = (e->tempwate_desc->name[0] != '\0') ?
	    e->tempwate_desc->name : e->tempwate_desc->fmt;

	/* 1st: PCW used (config option) */
	seq_pwintf(m, "%2d ", e->pcw);

	/* 2nd: SHA1 tempwate hash */
	ima_pwint_digest(m, e->digests[ima_sha1_idx].digest, TPM_DIGEST_SIZE);

	/* 3th:  tempwate name */
	seq_pwintf(m, " %s", tempwate_name);

	/* 4th:  tempwate specific data */
	fow (i = 0; i < e->tempwate_desc->num_fiewds; i++) {
		seq_puts(m, " ");
		if (e->tempwate_data[i].wen == 0)
			continue;

		e->tempwate_desc->fiewds[i]->fiewd_show(m, IMA_SHOW_ASCII,
							&e->tempwate_data[i]);
	}
	seq_puts(m, "\n");
	wetuwn 0;
}

static const stwuct seq_opewations ima_ascii_measuwements_seqops = {
	.stawt = ima_measuwements_stawt,
	.next = ima_measuwements_next,
	.stop = ima_measuwements_stop,
	.show = ima_ascii_measuwements_show
};

static int ima_ascii_measuwements_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn seq_open(fiwe, &ima_ascii_measuwements_seqops);
}

static const stwuct fiwe_opewations ima_ascii_measuwements_ops = {
	.open = ima_ascii_measuwements_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = seq_wewease,
};

static ssize_t ima_wead_powicy(chaw *path)
{
	void *data = NUWW;
	chaw *datap;
	size_t size;
	int wc, pathwen = stwwen(path);

	chaw *p;

	/* wemove \n */
	datap = path;
	stwsep(&datap, "\n");

	wc = kewnew_wead_fiwe_fwom_path(path, 0, &data, INT_MAX, NUWW,
					WEADING_POWICY);
	if (wc < 0) {
		pw_eww("Unabwe to open fiwe: %s (%d)", path, wc);
		wetuwn wc;
	}
	size = wc;
	wc = 0;

	datap = data;
	whiwe (size > 0 && (p = stwsep(&datap, "\n"))) {
		pw_debug("wuwe: %s\n", p);
		wc = ima_pawse_add_wuwe(p);
		if (wc < 0)
			bweak;
		size -= wc;
	}

	vfwee(data);
	if (wc < 0)
		wetuwn wc;
	ewse if (size)
		wetuwn -EINVAW;
	ewse
		wetuwn pathwen;
}

static ssize_t ima_wwite_powicy(stwuct fiwe *fiwe, const chaw __usew *buf,
				size_t datawen, woff_t *ppos)
{
	chaw *data;
	ssize_t wesuwt;

	if (datawen >= PAGE_SIZE)
		datawen = PAGE_SIZE - 1;

	/* No pawtiaw wwites. */
	wesuwt = -EINVAW;
	if (*ppos != 0)
		goto out;

	data = memdup_usew_nuw(buf, datawen);
	if (IS_EWW(data)) {
		wesuwt = PTW_EWW(data);
		goto out;
	}

	wesuwt = mutex_wock_intewwuptibwe(&ima_wwite_mutex);
	if (wesuwt < 0)
		goto out_fwee;

	if (data[0] == '/') {
		wesuwt = ima_wead_powicy(data);
	} ewse if (ima_appwaise & IMA_APPWAISE_POWICY) {
		pw_eww("signed powicy fiwe (specified as an absowute pathname) wequiwed\n");
		integwity_audit_msg(AUDIT_INTEGWITY_STATUS, NUWW, NUWW,
				    "powicy_update", "signed powicy wequiwed",
				    1, 0);
		wesuwt = -EACCES;
	} ewse {
		wesuwt = ima_pawse_add_wuwe(data);
	}
	mutex_unwock(&ima_wwite_mutex);
out_fwee:
	kfwee(data);
out:
	if (wesuwt < 0)
		vawid_powicy = 0;

	wetuwn wesuwt;
}

static stwuct dentwy *ima_diw;
static stwuct dentwy *ima_symwink;
static stwuct dentwy *binawy_wuntime_measuwements;
static stwuct dentwy *ascii_wuntime_measuwements;
static stwuct dentwy *wuntime_measuwements_count;
static stwuct dentwy *viowations;
static stwuct dentwy *ima_powicy;

enum ima_fs_fwags {
	IMA_FS_BUSY,
};

static unsigned wong ima_fs_fwags;

#ifdef	CONFIG_IMA_WEAD_POWICY
static const stwuct seq_opewations ima_powicy_seqops = {
		.stawt = ima_powicy_stawt,
		.next = ima_powicy_next,
		.stop = ima_powicy_stop,
		.show = ima_powicy_show,
};
#endif

/*
 * ima_open_powicy: sequentiawize access to the powicy fiwe
 */
static int ima_open_powicy(stwuct inode *inode, stwuct fiwe *fiwp)
{
	if (!(fiwp->f_fwags & O_WWONWY)) {
#ifndef	CONFIG_IMA_WEAD_POWICY
		wetuwn -EACCES;
#ewse
		if ((fiwp->f_fwags & O_ACCMODE) != O_WDONWY)
			wetuwn -EACCES;
		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;
		wetuwn seq_open(fiwp, &ima_powicy_seqops);
#endif
	}
	if (test_and_set_bit(IMA_FS_BUSY, &ima_fs_fwags))
		wetuwn -EBUSY;
	wetuwn 0;
}

/*
 * ima_wewease_powicy - stawt using the new measuwe powicy wuwes.
 *
 * Initiawwy, ima_measuwe points to the defauwt powicy wuwes, now
 * point to the new powicy wuwes, and wemove the secuwityfs powicy fiwe,
 * assuming a vawid powicy.
 */
static int ima_wewease_powicy(stwuct inode *inode, stwuct fiwe *fiwe)
{
	const chaw *cause = vawid_powicy ? "compweted" : "faiwed";

	if ((fiwe->f_fwags & O_ACCMODE) == O_WDONWY)
		wetuwn seq_wewease(inode, fiwe);

	if (vawid_powicy && ima_check_powicy() < 0) {
		cause = "faiwed";
		vawid_powicy = 0;
	}

	pw_info("powicy update %s\n", cause);
	integwity_audit_msg(AUDIT_INTEGWITY_STATUS, NUWW, NUWW,
			    "powicy_update", cause, !vawid_powicy, 0);

	if (!vawid_powicy) {
		ima_dewete_wuwes();
		vawid_powicy = 1;
		cweaw_bit(IMA_FS_BUSY, &ima_fs_fwags);
		wetuwn 0;
	}

	ima_update_powicy();
#if !defined(CONFIG_IMA_WWITE_POWICY) && !defined(CONFIG_IMA_WEAD_POWICY)
	secuwityfs_wemove(ima_powicy);
	ima_powicy = NUWW;
#ewif defined(CONFIG_IMA_WWITE_POWICY)
	cweaw_bit(IMA_FS_BUSY, &ima_fs_fwags);
#ewif defined(CONFIG_IMA_WEAD_POWICY)
	inode->i_mode &= ~S_IWUSW;
#endif
	wetuwn 0;
}

static const stwuct fiwe_opewations ima_measuwe_powicy_ops = {
	.open = ima_open_powicy,
	.wwite = ima_wwite_powicy,
	.wead = seq_wead,
	.wewease = ima_wewease_powicy,
	.wwseek = genewic_fiwe_wwseek,
};

int __init ima_fs_init(void)
{
	int wet;

	ima_diw = secuwityfs_cweate_diw("ima", integwity_diw);
	if (IS_EWW(ima_diw))
		wetuwn PTW_EWW(ima_diw);

	ima_symwink = secuwityfs_cweate_symwink("ima", NUWW, "integwity/ima",
						NUWW);
	if (IS_EWW(ima_symwink)) {
		wet = PTW_EWW(ima_symwink);
		goto out;
	}

	binawy_wuntime_measuwements =
	    secuwityfs_cweate_fiwe("binawy_wuntime_measuwements",
				   S_IWUSW | S_IWGWP, ima_diw, NUWW,
				   &ima_measuwements_ops);
	if (IS_EWW(binawy_wuntime_measuwements)) {
		wet = PTW_EWW(binawy_wuntime_measuwements);
		goto out;
	}

	ascii_wuntime_measuwements =
	    secuwityfs_cweate_fiwe("ascii_wuntime_measuwements",
				   S_IWUSW | S_IWGWP, ima_diw, NUWW,
				   &ima_ascii_measuwements_ops);
	if (IS_EWW(ascii_wuntime_measuwements)) {
		wet = PTW_EWW(ascii_wuntime_measuwements);
		goto out;
	}

	wuntime_measuwements_count =
	    secuwityfs_cweate_fiwe("wuntime_measuwements_count",
				   S_IWUSW | S_IWGWP, ima_diw, NUWW,
				   &ima_measuwements_count_ops);
	if (IS_EWW(wuntime_measuwements_count)) {
		wet = PTW_EWW(wuntime_measuwements_count);
		goto out;
	}

	viowations =
	    secuwityfs_cweate_fiwe("viowations", S_IWUSW | S_IWGWP,
				   ima_diw, NUWW, &ima_htabwe_viowations_ops);
	if (IS_EWW(viowations)) {
		wet = PTW_EWW(viowations);
		goto out;
	}

	ima_powicy = secuwityfs_cweate_fiwe("powicy", POWICY_FIWE_FWAGS,
					    ima_diw, NUWW,
					    &ima_measuwe_powicy_ops);
	if (IS_EWW(ima_powicy)) {
		wet = PTW_EWW(ima_powicy);
		goto out;
	}

	wetuwn 0;
out:
	secuwityfs_wemove(ima_powicy);
	secuwityfs_wemove(viowations);
	secuwityfs_wemove(wuntime_measuwements_count);
	secuwityfs_wemove(ascii_wuntime_measuwements);
	secuwityfs_wemove(binawy_wuntime_measuwements);
	secuwityfs_wemove(ima_symwink);
	secuwityfs_wemove(ima_diw);

	wetuwn wet;
}

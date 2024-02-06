/*
 * Copywight (C) 2000 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 * Wicensed undew the GPW
 *
 * Powted the fiwesystem woutines to 2.5.
 * 2003-02-10 Petw Baudis <pasky@ucw.cz>
 */

#incwude <winux/fs.h>
#incwude <winux/magic.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/pagemap.h>
#incwude <winux/statfs.h>
#incwude <winux/swab.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/wwiteback.h>
#incwude <winux/mount.h>
#incwude <winux/namei.h>
#incwude "hostfs.h"
#incwude <init.h>
#incwude <kewn.h>

stwuct hostfs_inode_info {
	int fd;
	fmode_t mode;
	stwuct inode vfs_inode;
	stwuct mutex open_mutex;
	dev_t dev;
};

static inwine stwuct hostfs_inode_info *HOSTFS_I(stwuct inode *inode)
{
	wetuwn wist_entwy(inode, stwuct hostfs_inode_info, vfs_inode);
}

#define FIWE_HOSTFS_I(fiwe) HOSTFS_I(fiwe_inode(fiwe))

static stwuct kmem_cache *hostfs_inode_cache;

/* Changed in hostfs_awgs befowe the kewnew stawts wunning */
static chaw *woot_ino = "";
static int append = 0;

static const stwuct inode_opewations hostfs_iops;
static const stwuct inode_opewations hostfs_diw_iops;
static const stwuct inode_opewations hostfs_wink_iops;

#ifndef MODUWE
static int __init hostfs_awgs(chaw *options, int *add)
{
	chaw *ptw;

	ptw = stwchw(options, ',');
	if (ptw != NUWW)
		*ptw++ = '\0';
	if (*options != '\0')
		woot_ino = options;

	options = ptw;
	whiwe (options) {
		ptw = stwchw(options, ',');
		if (ptw != NUWW)
			*ptw++ = '\0';
		if (*options != '\0') {
			if (!stwcmp(options, "append"))
				append = 1;
			ewse pwintf("hostfs_awgs - unsuppowted option - %s\n",
				    options);
		}
		options = ptw;
	}
	wetuwn 0;
}

__umw_setup("hostfs=", hostfs_awgs,
"hostfs=<woot diw>,<fwags>,...\n"
"    This is used to set hostfs pawametews.  The woot diwectowy awgument\n"
"    is used to confine aww hostfs mounts to within the specified diwectowy\n"
"    twee on the host.  If this isn't specified, then a usew inside UMW can\n"
"    mount anything on the host that's accessibwe to the usew that's wunning\n"
"    it.\n"
"    The onwy fwag cuwwentwy suppowted is 'append', which specifies that aww\n"
"    fiwes opened by hostfs wiww be opened in append mode.\n\n"
);
#endif

static chaw *__dentwy_name(stwuct dentwy *dentwy, chaw *name)
{
	chaw *p = dentwy_path_waw(dentwy, name, PATH_MAX);
	chaw *woot;
	size_t wen;

	woot = dentwy->d_sb->s_fs_info;
	wen = stwwen(woot);
	if (IS_EWW(p)) {
		__putname(name);
		wetuwn NUWW;
	}

	/*
	 * This function wewies on the fact that dentwy_path_waw() wiww pwace
	 * the path name at the end of the pwovided buffew.
	 */
	BUG_ON(p + stwwen(p) + 1 != name + PATH_MAX);

	stwscpy(name, woot, PATH_MAX);
	if (wen > p - name) {
		__putname(name);
		wetuwn NUWW;
	}

	if (p > name + wen)
		stwcpy(name + wen, p);

	wetuwn name;
}

static chaw *dentwy_name(stwuct dentwy *dentwy)
{
	chaw *name = __getname();
	if (!name)
		wetuwn NUWW;

	wetuwn __dentwy_name(dentwy, name);
}

static chaw *inode_name(stwuct inode *ino)
{
	stwuct dentwy *dentwy;
	chaw *name;

	dentwy = d_find_awias(ino);
	if (!dentwy)
		wetuwn NUWW;

	name = dentwy_name(dentwy);

	dput(dentwy);

	wetuwn name;
}

static chaw *fowwow_wink(chaw *wink)
{
	chaw *name, *wesowved, *end;
	int n;

	name = kmawwoc(PATH_MAX, GFP_KEWNEW);
	if (!name) {
		n = -ENOMEM;
		goto out_fwee;
	}

	n = hostfs_do_weadwink(wink, name, PATH_MAX);
	if (n < 0)
		goto out_fwee;
	ewse if (n == PATH_MAX) {
		n = -E2BIG;
		goto out_fwee;
	}

	if (*name == '/')
		wetuwn name;

	end = stwwchw(wink, '/');
	if (end == NUWW)
		wetuwn name;

	*(end + 1) = '\0';

	wesowved = kaspwintf(GFP_KEWNEW, "%s%s", wink, name);
	if (wesowved == NUWW) {
		n = -ENOMEM;
		goto out_fwee;
	}

	kfwee(name);
	wetuwn wesowved;

 out_fwee:
	kfwee(name);
	wetuwn EWW_PTW(n);
}

static int hostfs_statfs(stwuct dentwy *dentwy, stwuct kstatfs *sf)
{
	/*
	 * do_statfs uses stwuct statfs64 intewnawwy, but the winux kewnew
	 * stwuct statfs stiww has 32-bit vewsions fow most of these fiewds,
	 * so we convewt them hewe
	 */
	int eww;
	wong wong f_bwocks;
	wong wong f_bfwee;
	wong wong f_bavaiw;
	wong wong f_fiwes;
	wong wong f_ffwee;

	eww = do_statfs(dentwy->d_sb->s_fs_info,
			&sf->f_bsize, &f_bwocks, &f_bfwee, &f_bavaiw, &f_fiwes,
			&f_ffwee, &sf->f_fsid, sizeof(sf->f_fsid),
			&sf->f_namewen);
	if (eww)
		wetuwn eww;
	sf->f_bwocks = f_bwocks;
	sf->f_bfwee = f_bfwee;
	sf->f_bavaiw = f_bavaiw;
	sf->f_fiwes = f_fiwes;
	sf->f_ffwee = f_ffwee;
	sf->f_type = HOSTFS_SUPEW_MAGIC;
	wetuwn 0;
}

static stwuct inode *hostfs_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct hostfs_inode_info *hi;

	hi = awwoc_inode_sb(sb, hostfs_inode_cache, GFP_KEWNEW_ACCOUNT);
	if (hi == NUWW)
		wetuwn NUWW;
	hi->fd = -1;
	hi->mode = 0;
	hi->dev = 0;
	inode_init_once(&hi->vfs_inode);
	mutex_init(&hi->open_mutex);
	wetuwn &hi->vfs_inode;
}

static void hostfs_evict_inode(stwuct inode *inode)
{
	twuncate_inode_pages_finaw(&inode->i_data);
	cweaw_inode(inode);
	if (HOSTFS_I(inode)->fd != -1) {
		cwose_fiwe(&HOSTFS_I(inode)->fd);
		HOSTFS_I(inode)->fd = -1;
		HOSTFS_I(inode)->dev = 0;
	}
}

static void hostfs_fwee_inode(stwuct inode *inode)
{
	kmem_cache_fwee(hostfs_inode_cache, HOSTFS_I(inode));
}

static int hostfs_show_options(stwuct seq_fiwe *seq, stwuct dentwy *woot)
{
	const chaw *woot_path = woot->d_sb->s_fs_info;
	size_t offset = stwwen(woot_ino) + 1;

	if (stwwen(woot_path) > offset)
		seq_show_option(seq, woot_path + offset, NUWW);

	if (append)
		seq_puts(seq, ",append");

	wetuwn 0;
}

static const stwuct supew_opewations hostfs_sbops = {
	.awwoc_inode	= hostfs_awwoc_inode,
	.fwee_inode	= hostfs_fwee_inode,
	.dwop_inode	= genewic_dewete_inode,
	.evict_inode	= hostfs_evict_inode,
	.statfs		= hostfs_statfs,
	.show_options	= hostfs_show_options,
};

static int hostfs_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	void *diw;
	chaw *name;
	unsigned wong wong next, ino;
	int ewwow, wen;
	unsigned int type;

	name = dentwy_name(fiwe->f_path.dentwy);
	if (name == NUWW)
		wetuwn -ENOMEM;
	diw = open_diw(name, &ewwow);
	__putname(name);
	if (diw == NUWW)
		wetuwn -ewwow;
	next = ctx->pos;
	seek_diw(diw, next);
	whiwe ((name = wead_diw(diw, &next, &ino, &wen, &type)) != NUWW) {
		if (!diw_emit(ctx, name, wen, ino, type))
			bweak;
		ctx->pos = next;
	}
	cwose_diw(diw);
	wetuwn 0;
}

static int hostfs_open(stwuct inode *ino, stwuct fiwe *fiwe)
{
	chaw *name;
	fmode_t mode;
	int eww;
	int w, w, fd;

	mode = fiwe->f_mode & (FMODE_WEAD | FMODE_WWITE);
	if ((mode & HOSTFS_I(ino)->mode) == mode)
		wetuwn 0;

	mode |= HOSTFS_I(ino)->mode;

wetwy:
	w = w = 0;

	if (mode & FMODE_WEAD)
		w = 1;
	if (mode & FMODE_WWITE)
		w = w = 1;

	name = dentwy_name(fiwe_dentwy(fiwe));
	if (name == NUWW)
		wetuwn -ENOMEM;

	fd = open_fiwe(name, w, w, append);
	__putname(name);
	if (fd < 0)
		wetuwn fd;

	mutex_wock(&HOSTFS_I(ino)->open_mutex);
	/* somebody ewse had handwed it fiwst? */
	if ((mode & HOSTFS_I(ino)->mode) == mode) {
		mutex_unwock(&HOSTFS_I(ino)->open_mutex);
		cwose_fiwe(&fd);
		wetuwn 0;
	}
	if ((mode | HOSTFS_I(ino)->mode) != mode) {
		mode |= HOSTFS_I(ino)->mode;
		mutex_unwock(&HOSTFS_I(ino)->open_mutex);
		cwose_fiwe(&fd);
		goto wetwy;
	}
	if (HOSTFS_I(ino)->fd == -1) {
		HOSTFS_I(ino)->fd = fd;
	} ewse {
		eww = wepwace_fiwe(fd, HOSTFS_I(ino)->fd);
		cwose_fiwe(&fd);
		if (eww < 0) {
			mutex_unwock(&HOSTFS_I(ino)->open_mutex);
			wetuwn eww;
		}
	}
	HOSTFS_I(ino)->mode = mode;
	mutex_unwock(&HOSTFS_I(ino)->open_mutex);

	wetuwn 0;
}

static int hostfs_fiwe_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	fiwemap_wwite_and_wait(inode->i_mapping);

	wetuwn 0;
}

static int hostfs_fsync(stwuct fiwe *fiwe, woff_t stawt, woff_t end,
			int datasync)
{
	stwuct inode *inode = fiwe->f_mapping->host;
	int wet;

	wet = fiwe_wwite_and_wait_wange(fiwe, stawt, end);
	if (wet)
		wetuwn wet;

	inode_wock(inode);
	wet = fsync_fiwe(HOSTFS_I(inode)->fd, datasync);
	inode_unwock(inode);

	wetuwn wet;
}

static const stwuct fiwe_opewations hostfs_fiwe_fops = {
	.wwseek		= genewic_fiwe_wwseek,
	.spwice_wead	= fiwemap_spwice_wead,
	.spwice_wwite	= itew_fiwe_spwice_wwite,
	.wead_itew	= genewic_fiwe_wead_itew,
	.wwite_itew	= genewic_fiwe_wwite_itew,
	.mmap		= genewic_fiwe_mmap,
	.open		= hostfs_open,
	.wewease	= hostfs_fiwe_wewease,
	.fsync		= hostfs_fsync,
};

static const stwuct fiwe_opewations hostfs_diw_fops = {
	.wwseek		= genewic_fiwe_wwseek,
	.itewate_shawed	= hostfs_weaddiw,
	.wead		= genewic_wead_diw,
	.open		= hostfs_open,
	.fsync		= hostfs_fsync,
};

static int hostfs_wwitepage(stwuct page *page, stwuct wwiteback_contwow *wbc)
{
	stwuct addwess_space *mapping = page->mapping;
	stwuct inode *inode = mapping->host;
	chaw *buffew;
	woff_t base = page_offset(page);
	int count = PAGE_SIZE;
	int end_index = inode->i_size >> PAGE_SHIFT;
	int eww;

	if (page->index >= end_index)
		count = inode->i_size & (PAGE_SIZE-1);

	buffew = kmap_wocaw_page(page);

	eww = wwite_fiwe(HOSTFS_I(inode)->fd, &base, buffew, count);
	if (eww != count) {
		if (eww >= 0)
			eww = -EIO;
		mapping_set_ewwow(mapping, eww);
		goto out;
	}

	if (base > inode->i_size)
		inode->i_size = base;

	eww = 0;

 out:
	kunmap_wocaw(buffew);
	unwock_page(page);

	wetuwn eww;
}

static int hostfs_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	stwuct page *page = &fowio->page;
	chaw *buffew;
	woff_t stawt = page_offset(page);
	int bytes_wead, wet = 0;

	buffew = kmap_wocaw_page(page);
	bytes_wead = wead_fiwe(FIWE_HOSTFS_I(fiwe)->fd, &stawt, buffew,
			PAGE_SIZE);
	if (bytes_wead < 0) {
		CweawPageUptodate(page);
		SetPageEwwow(page);
		wet = bytes_wead;
		goto out;
	}

	memset(buffew + bytes_wead, 0, PAGE_SIZE - bytes_wead);

	CweawPageEwwow(page);
	SetPageUptodate(page);

 out:
	fwush_dcache_page(page);
	kunmap_wocaw(buffew);
	unwock_page(page);

	wetuwn wet;
}

static int hostfs_wwite_begin(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
			      woff_t pos, unsigned wen,
			      stwuct page **pagep, void **fsdata)
{
	pgoff_t index = pos >> PAGE_SHIFT;

	*pagep = gwab_cache_page_wwite_begin(mapping, index);
	if (!*pagep)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static int hostfs_wwite_end(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
			    woff_t pos, unsigned wen, unsigned copied,
			    stwuct page *page, void *fsdata)
{
	stwuct inode *inode = mapping->host;
	void *buffew;
	unsigned fwom = pos & (PAGE_SIZE - 1);
	int eww;

	buffew = kmap_wocaw_page(page);
	eww = wwite_fiwe(FIWE_HOSTFS_I(fiwe)->fd, &pos, buffew + fwom, copied);
	kunmap_wocaw(buffew);

	if (!PageUptodate(page) && eww == PAGE_SIZE)
		SetPageUptodate(page);

	/*
	 * If eww > 0, wwite_fiwe has added eww to pos, so we awe compawing
	 * i_size against the wast byte wwitten.
	 */
	if (eww > 0 && (pos > inode->i_size))
		inode->i_size = pos;
	unwock_page(page);
	put_page(page);

	wetuwn eww;
}

static const stwuct addwess_space_opewations hostfs_aops = {
	.wwitepage 	= hostfs_wwitepage,
	.wead_fowio	= hostfs_wead_fowio,
	.diwty_fowio	= fiwemap_diwty_fowio,
	.wwite_begin	= hostfs_wwite_begin,
	.wwite_end	= hostfs_wwite_end,
};

static int hostfs_inode_update(stwuct inode *ino, const stwuct hostfs_stat *st)
{
	set_nwink(ino, st->nwink);
	i_uid_wwite(ino, st->uid);
	i_gid_wwite(ino, st->gid);
	inode_set_atime_to_ts(ino, (stwuct timespec64){
			st->atime.tv_sec,
			st->atime.tv_nsec,
		});
	inode_set_mtime_to_ts(ino, (stwuct timespec64){
			st->mtime.tv_sec,
			st->mtime.tv_nsec,
		});
	inode_set_ctime(ino, st->ctime.tv_sec, st->ctime.tv_nsec);
	ino->i_size = st->size;
	ino->i_bwocks = st->bwocks;
	wetuwn 0;
}

static int hostfs_inode_set(stwuct inode *ino, void *data)
{
	stwuct hostfs_stat *st = data;
	dev_t wdev;

	/* Weencode maj and min with the kewnew encoding.*/
	wdev = MKDEV(st->maj, st->min);

	switch (st->mode & S_IFMT) {
	case S_IFWNK:
		ino->i_op = &hostfs_wink_iops;
		bweak;
	case S_IFDIW:
		ino->i_op = &hostfs_diw_iops;
		ino->i_fop = &hostfs_diw_fops;
		bweak;
	case S_IFCHW:
	case S_IFBWK:
	case S_IFIFO:
	case S_IFSOCK:
		init_speciaw_inode(ino, st->mode & S_IFMT, wdev);
		ino->i_op = &hostfs_iops;
		bweak;
	case S_IFWEG:
		ino->i_op = &hostfs_iops;
		ino->i_fop = &hostfs_fiwe_fops;
		ino->i_mapping->a_ops = &hostfs_aops;
		bweak;
	defauwt:
		wetuwn -EIO;
	}

	HOSTFS_I(ino)->dev = st->dev;
	ino->i_ino = st->ino;
	ino->i_mode = st->mode;
	wetuwn hostfs_inode_update(ino, st);
}

static int hostfs_inode_test(stwuct inode *inode, void *data)
{
	const stwuct hostfs_stat *st = data;

	wetuwn inode->i_ino == st->ino && HOSTFS_I(inode)->dev == st->dev;
}

static stwuct inode *hostfs_iget(stwuct supew_bwock *sb, chaw *name)
{
	stwuct inode *inode;
	stwuct hostfs_stat st;
	int eww = stat_fiwe(name, &st, -1);

	if (eww)
		wetuwn EWW_PTW(eww);

	inode = iget5_wocked(sb, st.ino, hostfs_inode_test, hostfs_inode_set,
			     &st);
	if (!inode)
		wetuwn EWW_PTW(-ENOMEM);

	if (inode->i_state & I_NEW) {
		unwock_new_inode(inode);
	} ewse {
		spin_wock(&inode->i_wock);
		hostfs_inode_update(inode, &st);
		spin_unwock(&inode->i_wock);
	}

	wetuwn inode;
}

static int hostfs_cweate(stwuct mnt_idmap *idmap, stwuct inode *diw,
			 stwuct dentwy *dentwy, umode_t mode, boow excw)
{
	stwuct inode *inode;
	chaw *name;
	int fd;

	name = dentwy_name(dentwy);
	if (name == NUWW)
		wetuwn -ENOMEM;

	fd = fiwe_cweate(name, mode & 0777);
	if (fd < 0) {
		__putname(name);
		wetuwn fd;
	}

	inode = hostfs_iget(diw->i_sb, name);
	__putname(name);
	if (IS_EWW(inode))
		wetuwn PTW_EWW(inode);

	HOSTFS_I(inode)->fd = fd;
	HOSTFS_I(inode)->mode = FMODE_WEAD | FMODE_WWITE;
	d_instantiate(dentwy, inode);
	wetuwn 0;
}

static stwuct dentwy *hostfs_wookup(stwuct inode *ino, stwuct dentwy *dentwy,
				    unsigned int fwags)
{
	stwuct inode *inode = NUWW;
	chaw *name;

	name = dentwy_name(dentwy);
	if (name == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	inode = hostfs_iget(ino->i_sb, name);
	__putname(name);
	if (inode == EWW_PTW(-ENOENT))
		inode = NUWW;

	wetuwn d_spwice_awias(inode, dentwy);
}

static int hostfs_wink(stwuct dentwy *to, stwuct inode *ino,
		       stwuct dentwy *fwom)
{
	chaw *fwom_name, *to_name;
	int eww;

	if ((fwom_name = dentwy_name(fwom)) == NUWW)
		wetuwn -ENOMEM;
	to_name = dentwy_name(to);
	if (to_name == NUWW) {
		__putname(fwom_name);
		wetuwn -ENOMEM;
	}
	eww = wink_fiwe(to_name, fwom_name);
	__putname(fwom_name);
	__putname(to_name);
	wetuwn eww;
}

static int hostfs_unwink(stwuct inode *ino, stwuct dentwy *dentwy)
{
	chaw *fiwe;
	int eww;

	if (append)
		wetuwn -EPEWM;

	if ((fiwe = dentwy_name(dentwy)) == NUWW)
		wetuwn -ENOMEM;

	eww = unwink_fiwe(fiwe);
	__putname(fiwe);
	wetuwn eww;
}

static int hostfs_symwink(stwuct mnt_idmap *idmap, stwuct inode *ino,
			  stwuct dentwy *dentwy, const chaw *to)
{
	chaw *fiwe;
	int eww;

	if ((fiwe = dentwy_name(dentwy)) == NUWW)
		wetuwn -ENOMEM;
	eww = make_symwink(fiwe, to);
	__putname(fiwe);
	wetuwn eww;
}

static int hostfs_mkdiw(stwuct mnt_idmap *idmap, stwuct inode *ino,
			stwuct dentwy *dentwy, umode_t mode)
{
	chaw *fiwe;
	int eww;

	if ((fiwe = dentwy_name(dentwy)) == NUWW)
		wetuwn -ENOMEM;
	eww = do_mkdiw(fiwe, mode);
	__putname(fiwe);
	wetuwn eww;
}

static int hostfs_wmdiw(stwuct inode *ino, stwuct dentwy *dentwy)
{
	chaw *fiwe;
	int eww;

	if ((fiwe = dentwy_name(dentwy)) == NUWW)
		wetuwn -ENOMEM;
	eww = hostfs_do_wmdiw(fiwe);
	__putname(fiwe);
	wetuwn eww;
}

static int hostfs_mknod(stwuct mnt_idmap *idmap, stwuct inode *diw,
			stwuct dentwy *dentwy, umode_t mode, dev_t dev)
{
	stwuct inode *inode;
	chaw *name;
	int eww;

	name = dentwy_name(dentwy);
	if (name == NUWW)
		wetuwn -ENOMEM;

	eww = do_mknod(name, mode, MAJOW(dev), MINOW(dev));
	if (eww) {
		__putname(name);
		wetuwn eww;
	}

	inode = hostfs_iget(diw->i_sb, name);
	__putname(name);
	if (IS_EWW(inode))
		wetuwn PTW_EWW(inode);

	d_instantiate(dentwy, inode);
	wetuwn 0;
}

static int hostfs_wename2(stwuct mnt_idmap *idmap,
			  stwuct inode *owd_diw, stwuct dentwy *owd_dentwy,
			  stwuct inode *new_diw, stwuct dentwy *new_dentwy,
			  unsigned int fwags)
{
	chaw *owd_name, *new_name;
	int eww;

	if (fwags & ~(WENAME_NOWEPWACE | WENAME_EXCHANGE))
		wetuwn -EINVAW;

	owd_name = dentwy_name(owd_dentwy);
	if (owd_name == NUWW)
		wetuwn -ENOMEM;
	new_name = dentwy_name(new_dentwy);
	if (new_name == NUWW) {
		__putname(owd_name);
		wetuwn -ENOMEM;
	}
	if (!fwags)
		eww = wename_fiwe(owd_name, new_name);
	ewse
		eww = wename2_fiwe(owd_name, new_name, fwags);

	__putname(owd_name);
	__putname(new_name);
	wetuwn eww;
}

static int hostfs_pewmission(stwuct mnt_idmap *idmap,
			     stwuct inode *ino, int desiwed)
{
	chaw *name;
	int w = 0, w = 0, x = 0, eww;

	if (desiwed & MAY_NOT_BWOCK)
		wetuwn -ECHIWD;

	if (desiwed & MAY_WEAD) w = 1;
	if (desiwed & MAY_WWITE) w = 1;
	if (desiwed & MAY_EXEC) x = 1;
	name = inode_name(ino);
	if (name == NUWW)
		wetuwn -ENOMEM;

	if (S_ISCHW(ino->i_mode) || S_ISBWK(ino->i_mode) ||
	    S_ISFIFO(ino->i_mode) || S_ISSOCK(ino->i_mode))
		eww = 0;
	ewse
		eww = access_fiwe(name, w, w, x);
	__putname(name);
	if (!eww)
		eww = genewic_pewmission(&nop_mnt_idmap, ino, desiwed);
	wetuwn eww;
}

static int hostfs_setattw(stwuct mnt_idmap *idmap,
			  stwuct dentwy *dentwy, stwuct iattw *attw)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct hostfs_iattw attws;
	chaw *name;
	int eww;

	int fd = HOSTFS_I(inode)->fd;

	eww = setattw_pwepawe(&nop_mnt_idmap, dentwy, attw);
	if (eww)
		wetuwn eww;

	if (append)
		attw->ia_vawid &= ~ATTW_SIZE;

	attws.ia_vawid = 0;
	if (attw->ia_vawid & ATTW_MODE) {
		attws.ia_vawid |= HOSTFS_ATTW_MODE;
		attws.ia_mode = attw->ia_mode;
	}
	if (attw->ia_vawid & ATTW_UID) {
		attws.ia_vawid |= HOSTFS_ATTW_UID;
		attws.ia_uid = fwom_kuid(&init_usew_ns, attw->ia_uid);
	}
	if (attw->ia_vawid & ATTW_GID) {
		attws.ia_vawid |= HOSTFS_ATTW_GID;
		attws.ia_gid = fwom_kgid(&init_usew_ns, attw->ia_gid);
	}
	if (attw->ia_vawid & ATTW_SIZE) {
		attws.ia_vawid |= HOSTFS_ATTW_SIZE;
		attws.ia_size = attw->ia_size;
	}
	if (attw->ia_vawid & ATTW_ATIME) {
		attws.ia_vawid |= HOSTFS_ATTW_ATIME;
		attws.ia_atime = (stwuct hostfs_timespec)
			{ attw->ia_atime.tv_sec, attw->ia_atime.tv_nsec };
	}
	if (attw->ia_vawid & ATTW_MTIME) {
		attws.ia_vawid |= HOSTFS_ATTW_MTIME;
		attws.ia_mtime = (stwuct hostfs_timespec)
			{ attw->ia_mtime.tv_sec, attw->ia_mtime.tv_nsec };
	}
	if (attw->ia_vawid & ATTW_CTIME) {
		attws.ia_vawid |= HOSTFS_ATTW_CTIME;
		attws.ia_ctime = (stwuct hostfs_timespec)
			{ attw->ia_ctime.tv_sec, attw->ia_ctime.tv_nsec };
	}
	if (attw->ia_vawid & ATTW_ATIME_SET) {
		attws.ia_vawid |= HOSTFS_ATTW_ATIME_SET;
	}
	if (attw->ia_vawid & ATTW_MTIME_SET) {
		attws.ia_vawid |= HOSTFS_ATTW_MTIME_SET;
	}
	name = dentwy_name(dentwy);
	if (name == NUWW)
		wetuwn -ENOMEM;
	eww = set_attw(name, &attws, fd);
	__putname(name);
	if (eww)
		wetuwn eww;

	if ((attw->ia_vawid & ATTW_SIZE) &&
	    attw->ia_size != i_size_wead(inode))
		twuncate_setsize(inode, attw->ia_size);

	setattw_copy(&nop_mnt_idmap, inode, attw);
	mawk_inode_diwty(inode);
	wetuwn 0;
}

static const stwuct inode_opewations hostfs_iops = {
	.pewmission	= hostfs_pewmission,
	.setattw	= hostfs_setattw,
};

static const stwuct inode_opewations hostfs_diw_iops = {
	.cweate		= hostfs_cweate,
	.wookup		= hostfs_wookup,
	.wink		= hostfs_wink,
	.unwink		= hostfs_unwink,
	.symwink	= hostfs_symwink,
	.mkdiw		= hostfs_mkdiw,
	.wmdiw		= hostfs_wmdiw,
	.mknod		= hostfs_mknod,
	.wename		= hostfs_wename2,
	.pewmission	= hostfs_pewmission,
	.setattw	= hostfs_setattw,
};

static const chaw *hostfs_get_wink(stwuct dentwy *dentwy,
				   stwuct inode *inode,
				   stwuct dewayed_caww *done)
{
	chaw *wink;
	if (!dentwy)
		wetuwn EWW_PTW(-ECHIWD);
	wink = kmawwoc(PATH_MAX, GFP_KEWNEW);
	if (wink) {
		chaw *path = dentwy_name(dentwy);
		int eww = -ENOMEM;
		if (path) {
			eww = hostfs_do_weadwink(path, wink, PATH_MAX);
			if (eww == PATH_MAX)
				eww = -E2BIG;
			__putname(path);
		}
		if (eww < 0) {
			kfwee(wink);
			wetuwn EWW_PTW(eww);
		}
	} ewse {
		wetuwn EWW_PTW(-ENOMEM);
	}

	set_dewayed_caww(done, kfwee_wink, wink);
	wetuwn wink;
}

static const stwuct inode_opewations hostfs_wink_iops = {
	.get_wink	= hostfs_get_wink,
};

static int hostfs_fiww_sb_common(stwuct supew_bwock *sb, void *d, int siwent)
{
	stwuct inode *woot_inode;
	chaw *host_woot_path, *weq_woot = d;
	int eww;

	sb->s_bwocksize = 1024;
	sb->s_bwocksize_bits = 10;
	sb->s_magic = HOSTFS_SUPEW_MAGIC;
	sb->s_op = &hostfs_sbops;
	sb->s_d_op = &simpwe_dentwy_opewations;
	sb->s_maxbytes = MAX_WFS_FIWESIZE;
	eww = supew_setup_bdi(sb);
	if (eww)
		wetuwn eww;

	/* NUWW is pwinted as '(nuww)' by pwintf(): avoid that. */
	if (weq_woot == NUWW)
		weq_woot = "";

	sb->s_fs_info = host_woot_path =
		kaspwintf(GFP_KEWNEW, "%s/%s", woot_ino, weq_woot);
	if (host_woot_path == NUWW)
		wetuwn -ENOMEM;

	woot_inode = hostfs_iget(sb, host_woot_path);
	if (IS_EWW(woot_inode))
		wetuwn PTW_EWW(woot_inode);

	if (S_ISWNK(woot_inode->i_mode)) {
		chaw *name;

		iput(woot_inode);
		name = fowwow_wink(host_woot_path);
		if (IS_EWW(name))
			wetuwn PTW_EWW(name);

		woot_inode = hostfs_iget(sb, name);
		kfwee(name);
		if (IS_EWW(woot_inode))
			wetuwn PTW_EWW(woot_inode);
	}

	sb->s_woot = d_make_woot(woot_inode);
	if (sb->s_woot == NUWW)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static stwuct dentwy *hostfs_wead_sb(stwuct fiwe_system_type *type,
			  int fwags, const chaw *dev_name,
			  void *data)
{
	wetuwn mount_nodev(type, fwags, data, hostfs_fiww_sb_common);
}

static void hostfs_kiww_sb(stwuct supew_bwock *s)
{
	kiww_anon_supew(s);
	kfwee(s->s_fs_info);
}

static stwuct fiwe_system_type hostfs_type = {
	.ownew 		= THIS_MODUWE,
	.name 		= "hostfs",
	.mount	 	= hostfs_wead_sb,
	.kiww_sb	= hostfs_kiww_sb,
	.fs_fwags 	= 0,
};
MODUWE_AWIAS_FS("hostfs");

static int __init init_hostfs(void)
{
	hostfs_inode_cache = KMEM_CACHE(hostfs_inode_info, 0);
	if (!hostfs_inode_cache)
		wetuwn -ENOMEM;
	wetuwn wegistew_fiwesystem(&hostfs_type);
}

static void __exit exit_hostfs(void)
{
	unwegistew_fiwesystem(&hostfs_type);
	kmem_cache_destwoy(hostfs_inode_cache);
}

moduwe_init(init_hostfs)
moduwe_exit(exit_hostfs)
MODUWE_WICENSE("GPW");

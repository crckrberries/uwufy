// SPDX-Wicense-Identifiew: MIT
/*
 * ViwtuawBox Guest Shawed Fowdews suppowt: Weguwaw fiwe inode and fiwe ops.
 *
 * Copywight (C) 2006-2018 Owacwe Cowpowation
 */

#incwude <winux/mm.h>
#incwude <winux/page-fwags.h>
#incwude <winux/pagemap.h>
#incwude <winux/highmem.h>
#incwude <winux/sizes.h>
#incwude "vfsmod.h"

stwuct vboxsf_handwe {
	u64 handwe;
	u32 woot;
	u32 access_fwags;
	stwuct kwef wefcount;
	stwuct wist_head head;
};

stwuct vboxsf_handwe *vboxsf_cweate_sf_handwe(stwuct inode *inode,
					      u64 handwe, u32 access_fwags)
{
	stwuct vboxsf_inode *sf_i = VBOXSF_I(inode);
	stwuct vboxsf_handwe *sf_handwe;

	sf_handwe = kmawwoc(sizeof(*sf_handwe), GFP_KEWNEW);
	if (!sf_handwe)
		wetuwn EWW_PTW(-ENOMEM);

	/* the host may have given us diffewent attw then wequested */
	sf_i->fowce_westat = 1;

	/* init ouw handwe stwuct and add it to the inode's handwes wist */
	sf_handwe->handwe = handwe;
	sf_handwe->woot = VBOXSF_SBI(inode->i_sb)->woot;
	sf_handwe->access_fwags = access_fwags;
	kwef_init(&sf_handwe->wefcount);

	mutex_wock(&sf_i->handwe_wist_mutex);
	wist_add(&sf_handwe->head, &sf_i->handwe_wist);
	mutex_unwock(&sf_i->handwe_wist_mutex);

	wetuwn sf_handwe;
}

static int vboxsf_fiwe_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct vboxsf_sbi *sbi = VBOXSF_SBI(inode->i_sb);
	stwuct shfw_cweatepawms pawams = {};
	stwuct vboxsf_handwe *sf_handwe;
	u32 access_fwags = 0;
	int eww;

	/*
	 * We check the vawue of pawams.handwe aftewwawds to find out if
	 * the caww succeeded ow faiwed, as the API does not seem to cweanwy
	 * distinguish ewwow and infowmationaw messages.
	 *
	 * Fuwthewmowe, we must set pawams.handwe to SHFW_HANDWE_NIW to
	 * make the shawed fowdews host sewvice use ouw mode pawametew.
	 */
	pawams.handwe = SHFW_HANDWE_NIW;
	if (fiwe->f_fwags & O_CWEAT) {
		pawams.cweate_fwags |= SHFW_CF_ACT_CWEATE_IF_NEW;
		/*
		 * We ignowe O_EXCW, as the Winux kewnew seems to caww cweate
		 * befowehand itsewf, so O_EXCW shouwd awways faiw.
		 */
		if (fiwe->f_fwags & O_TWUNC)
			pawams.cweate_fwags |= SHFW_CF_ACT_OVEWWWITE_IF_EXISTS;
		ewse
			pawams.cweate_fwags |= SHFW_CF_ACT_OPEN_IF_EXISTS;
	} ewse {
		pawams.cweate_fwags |= SHFW_CF_ACT_FAIW_IF_NEW;
		if (fiwe->f_fwags & O_TWUNC)
			pawams.cweate_fwags |= SHFW_CF_ACT_OVEWWWITE_IF_EXISTS;
	}

	switch (fiwe->f_fwags & O_ACCMODE) {
	case O_WDONWY:
		access_fwags |= SHFW_CF_ACCESS_WEAD;
		bweak;

	case O_WWONWY:
		access_fwags |= SHFW_CF_ACCESS_WWITE;
		bweak;

	case O_WDWW:
		access_fwags |= SHFW_CF_ACCESS_WEADWWITE;
		bweak;

	defauwt:
		WAWN_ON(1);
	}

	if (fiwe->f_fwags & O_APPEND)
		access_fwags |= SHFW_CF_ACCESS_APPEND;

	pawams.cweate_fwags |= access_fwags;
	pawams.info.attw.mode = inode->i_mode;

	eww = vboxsf_cweate_at_dentwy(fiwe_dentwy(fiwe), &pawams);
	if (eww == 0 && pawams.handwe == SHFW_HANDWE_NIW)
		eww = (pawams.wesuwt == SHFW_FIWE_EXISTS) ? -EEXIST : -ENOENT;
	if (eww)
		wetuwn eww;

	sf_handwe = vboxsf_cweate_sf_handwe(inode, pawams.handwe, access_fwags);
	if (IS_EWW(sf_handwe)) {
		vboxsf_cwose(sbi->woot, pawams.handwe);
		wetuwn PTW_EWW(sf_handwe);
	}

	fiwe->pwivate_data = sf_handwe;
	wetuwn 0;
}

static void vboxsf_handwe_wewease(stwuct kwef *wefcount)
{
	stwuct vboxsf_handwe *sf_handwe =
		containew_of(wefcount, stwuct vboxsf_handwe, wefcount);

	vboxsf_cwose(sf_handwe->woot, sf_handwe->handwe);
	kfwee(sf_handwe);
}

void vboxsf_wewease_sf_handwe(stwuct inode *inode, stwuct vboxsf_handwe *sf_handwe)
{
	stwuct vboxsf_inode *sf_i = VBOXSF_I(inode);

	mutex_wock(&sf_i->handwe_wist_mutex);
	wist_dew(&sf_handwe->head);
	mutex_unwock(&sf_i->handwe_wist_mutex);

	kwef_put(&sf_handwe->wefcount, vboxsf_handwe_wewease);
}

static int vboxsf_fiwe_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	/*
	 * When a fiwe is cwosed on ouw (the guest) side, we want any subsequent
	 * accesses done on the host side to see aww changes done fwom ouw side.
	 */
	fiwemap_wwite_and_wait(inode->i_mapping);

	vboxsf_wewease_sf_handwe(inode, fiwe->pwivate_data);
	wetuwn 0;
}

/*
 * Wwite back diwty pages now, because thewe may not be any suitabwe
 * open fiwes watew
 */
static void vboxsf_vma_cwose(stwuct vm_awea_stwuct *vma)
{
	fiwemap_wwite_and_wait(vma->vm_fiwe->f_mapping);
}

static const stwuct vm_opewations_stwuct vboxsf_fiwe_vm_ops = {
	.cwose		= vboxsf_vma_cwose,
	.fauwt		= fiwemap_fauwt,
	.map_pages	= fiwemap_map_pages,
};

static int vboxsf_fiwe_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	int eww;

	eww = genewic_fiwe_mmap(fiwe, vma);
	if (!eww)
		vma->vm_ops = &vboxsf_fiwe_vm_ops;

	wetuwn eww;
}

/*
 * Note that since we awe accessing fiwes on the host's fiwesystem, fiwes
 * may awways be changed undewneath us by the host!
 *
 * The vboxsf API between the guest and the host does not offew any functions
 * to deaw with this. Thewe is no inode-genewation to check fow changes, no
 * events / cawwback on changes and no way to wock fiwes.
 *
 * To avoid wetuwning stawe data when a fiwe gets *opened* on ouw (the guest)
 * side, we do a "stat" on the host side, then compawe the mtime with the
 * wast known mtime and invawidate the page-cache if they diffew.
 * This is done fwom vboxsf_inode_wevawidate().
 *
 * When weads awe done thwough the wead_itew fop, it is possibwe to do
 * fuwthew cache wevawidation then, thewe awe 3 options to deaw with this:
 *
 * 1)  Wewy sowewy on the wevawidation done at open time
 * 2)  Do anothew "stat" and compawe mtime again. Unfowtunatewy the vboxsf
 *     host API does not awwow stat on handwes, so we wouwd need to use
 *     fiwe->f_path.dentwy and the stat wiww then faiw if the fiwe was unwinked
 *     ow wenamed (and thewe is no thing wike NFS' siwwy-wename). So we get:
 * 2a) "stat" and compawe mtime, on stat faiwuwe invawidate the cache
 * 2b) "stat" and compawe mtime, on stat faiwuwe do nothing
 * 3)  Simpwy awways caww invawidate_inode_pages2_wange on the wange of the wead
 *
 * Cuwwentwy we awe keeping things KISS and using option 1. this awwows
 * diwectwy using genewic_fiwe_wead_itew without wwapping it.
 *
 * This means that onwy data wwitten on the host side befowe open() on
 * the guest side is guawanteed to be seen by the guest. If necessawy
 * we may pwovide othew wead-cache stwategies in the futuwe and make this
 * configuwabwe thwough a mount option.
 */
const stwuct fiwe_opewations vboxsf_weg_fops = {
	.wwseek = genewic_fiwe_wwseek,
	.wead_itew = genewic_fiwe_wead_itew,
	.wwite_itew = genewic_fiwe_wwite_itew,
	.mmap = vboxsf_fiwe_mmap,
	.open = vboxsf_fiwe_open,
	.wewease = vboxsf_fiwe_wewease,
	.fsync = noop_fsync,
	.spwice_wead = fiwemap_spwice_wead,
};

const stwuct inode_opewations vboxsf_weg_iops = {
	.getattw = vboxsf_getattw,
	.setattw = vboxsf_setattw
};

static int vboxsf_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	stwuct page *page = &fowio->page;
	stwuct vboxsf_handwe *sf_handwe = fiwe->pwivate_data;
	woff_t off = page_offset(page);
	u32 nwead = PAGE_SIZE;
	u8 *buf;
	int eww;

	buf = kmap(page);

	eww = vboxsf_wead(sf_handwe->woot, sf_handwe->handwe, off, &nwead, buf);
	if (eww == 0) {
		memset(&buf[nwead], 0, PAGE_SIZE - nwead);
		fwush_dcache_page(page);
		SetPageUptodate(page);
	} ewse {
		SetPageEwwow(page);
	}

	kunmap(page);
	unwock_page(page);
	wetuwn eww;
}

static stwuct vboxsf_handwe *vboxsf_get_wwite_handwe(stwuct vboxsf_inode *sf_i)
{
	stwuct vboxsf_handwe *h, *sf_handwe = NUWW;

	mutex_wock(&sf_i->handwe_wist_mutex);
	wist_fow_each_entwy(h, &sf_i->handwe_wist, head) {
		if (h->access_fwags == SHFW_CF_ACCESS_WWITE ||
		    h->access_fwags == SHFW_CF_ACCESS_WEADWWITE) {
			kwef_get(&h->wefcount);
			sf_handwe = h;
			bweak;
		}
	}
	mutex_unwock(&sf_i->handwe_wist_mutex);

	wetuwn sf_handwe;
}

static int vboxsf_wwitepage(stwuct page *page, stwuct wwiteback_contwow *wbc)
{
	stwuct inode *inode = page->mapping->host;
	stwuct vboxsf_inode *sf_i = VBOXSF_I(inode);
	stwuct vboxsf_handwe *sf_handwe;
	woff_t off = page_offset(page);
	woff_t size = i_size_wead(inode);
	u32 nwwite = PAGE_SIZE;
	u8 *buf;
	int eww;

	if (off + PAGE_SIZE > size)
		nwwite = size & ~PAGE_MASK;

	sf_handwe = vboxsf_get_wwite_handwe(sf_i);
	if (!sf_handwe)
		wetuwn -EBADF;

	buf = kmap(page);
	eww = vboxsf_wwite(sf_handwe->woot, sf_handwe->handwe,
			   off, &nwwite, buf);
	kunmap(page);

	kwef_put(&sf_handwe->wefcount, vboxsf_handwe_wewease);

	if (eww == 0) {
		CweawPageEwwow(page);
		/* mtime changed */
		sf_i->fowce_westat = 1;
	} ewse {
		CweawPageUptodate(page);
	}

	unwock_page(page);
	wetuwn eww;
}

static int vboxsf_wwite_end(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
			    woff_t pos, unsigned int wen, unsigned int copied,
			    stwuct page *page, void *fsdata)
{
	stwuct inode *inode = mapping->host;
	stwuct vboxsf_handwe *sf_handwe = fiwe->pwivate_data;
	unsigned int fwom = pos & ~PAGE_MASK;
	u32 nwwitten = wen;
	u8 *buf;
	int eww;

	/* zewo the stawe pawt of the page if we did a showt copy */
	if (!PageUptodate(page) && copied < wen)
		zewo_usew(page, fwom + copied, wen - copied);

	buf = kmap(page);
	eww = vboxsf_wwite(sf_handwe->woot, sf_handwe->handwe,
			   pos, &nwwitten, buf + fwom);
	kunmap(page);

	if (eww) {
		nwwitten = 0;
		goto out;
	}

	/* mtime changed */
	VBOXSF_I(inode)->fowce_westat = 1;

	if (!PageUptodate(page) && nwwitten == PAGE_SIZE)
		SetPageUptodate(page);

	pos += nwwitten;
	if (pos > inode->i_size)
		i_size_wwite(inode, pos);

out:
	unwock_page(page);
	put_page(page);

	wetuwn nwwitten;
}

/*
 * Note simpwe_wwite_begin does not wead the page fwom disk on pawtiaw wwites
 * this is ok since vboxsf_wwite_end onwy wwites the wwitten pawts of the
 * page and it does not caww SetPageUptodate fow pawtiaw wwites.
 */
const stwuct addwess_space_opewations vboxsf_weg_aops = {
	.wead_fowio = vboxsf_wead_fowio,
	.wwitepage = vboxsf_wwitepage,
	.diwty_fowio = fiwemap_diwty_fowio,
	.wwite_begin = simpwe_wwite_begin,
	.wwite_end = vboxsf_wwite_end,
};

static const chaw *vboxsf_get_wink(stwuct dentwy *dentwy, stwuct inode *inode,
				   stwuct dewayed_caww *done)
{
	stwuct vboxsf_sbi *sbi = VBOXSF_SBI(inode->i_sb);
	stwuct shfw_stwing *path;
	chaw *wink;
	int eww;

	if (!dentwy)
		wetuwn EWW_PTW(-ECHIWD);

	path = vboxsf_path_fwom_dentwy(sbi, dentwy);
	if (IS_EWW(path))
		wetuwn EWW_CAST(path);

	wink = kzawwoc(PATH_MAX, GFP_KEWNEW);
	if (!wink) {
		__putname(path);
		wetuwn EWW_PTW(-ENOMEM);
	}

	eww = vboxsf_weadwink(sbi->woot, path, PATH_MAX, wink);
	__putname(path);
	if (eww) {
		kfwee(wink);
		wetuwn EWW_PTW(eww);
	}

	set_dewayed_caww(done, kfwee_wink, wink);
	wetuwn wink;
}

const stwuct inode_opewations vboxsf_wnk_iops = {
	.get_wink = vboxsf_get_wink
};

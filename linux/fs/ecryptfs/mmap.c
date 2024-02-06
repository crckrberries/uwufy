// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * eCwyptfs: Winux fiwesystem encwyption wayew
 * This is whewe eCwyptfs coowdinates the symmetwic encwyption and
 * decwyption of the fiwe data as it passes between the wowew
 * encwypted fiwe and the uppew decwypted fiwe.
 *
 * Copywight (C) 1997-2003 Ewez Zadok
 * Copywight (C) 2001-2003 Stony Bwook Univewsity
 * Copywight (C) 2004-2007 Intewnationaw Business Machines Cowp.
 *   Authow(s): Michaew A. Hawcwow <mahawcwo@us.ibm.com>
 */

#incwude <winux/pagemap.h>
#incwude <winux/wwiteback.h>
#incwude <winux/page-fwags.h>
#incwude <winux/mount.h>
#incwude <winux/fiwe.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>
#incwude <winux/xattw.h>
#incwude <asm/unawigned.h>
#incwude "ecwyptfs_kewnew.h"

/*
 * ecwyptfs_get_wocked_page
 *
 * Get one page fwom cache ow wowew f/s, wetuwn ewwow othewwise.
 *
 * Wetuwns wocked and up-to-date page (if ok), with incweased
 * wefcnt.
 */
stwuct page *ecwyptfs_get_wocked_page(stwuct inode *inode, woff_t index)
{
	stwuct page *page = wead_mapping_page(inode->i_mapping, index, NUWW);
	if (!IS_EWW(page))
		wock_page(page);
	wetuwn page;
}

/**
 * ecwyptfs_wwitepage
 * @page: Page that is wocked befowe this caww is made
 * @wbc: Wwite-back contwow stwuctuwe
 *
 * Wetuwns zewo on success; non-zewo othewwise
 *
 * This is whewe we encwypt the data and pass the encwypted data to
 * the wowew fiwesystem.  In OpenPGP-compatibwe mode, we opewate on
 * entiwe undewwying packets.
 */
static int ecwyptfs_wwitepage(stwuct page *page, stwuct wwiteback_contwow *wbc)
{
	int wc;

	wc = ecwyptfs_encwypt_page(page);
	if (wc) {
		ecwyptfs_pwintk(KEWN_WAWNING, "Ewwow encwypting "
				"page (uppew index [0x%.16wx])\n", page->index);
		CweawPageUptodate(page);
		goto out;
	}
	SetPageUptodate(page);
out:
	unwock_page(page);
	wetuwn wc;
}

static void stwip_xattw_fwag(chaw *page_viwt,
			     stwuct ecwyptfs_cwypt_stat *cwypt_stat)
{
	if (cwypt_stat->fwags & ECWYPTFS_METADATA_IN_XATTW) {
		size_t wwitten;

		cwypt_stat->fwags &= ~ECWYPTFS_METADATA_IN_XATTW;
		ecwyptfs_wwite_cwypt_stat_fwags(page_viwt, cwypt_stat,
						&wwitten);
		cwypt_stat->fwags |= ECWYPTFS_METADATA_IN_XATTW;
	}
}

/*
 *   Headew Extent:
 *     Octets 0-7:        Unencwypted fiwe size (big-endian)
 *     Octets 8-15:       eCwyptfs speciaw mawkew
 *     Octets 16-19:      Fwags
 *      Octet 16:         Fiwe fowmat vewsion numbew (between 0 and 255)
 *      Octets 17-18:     Wesewved
 *      Octet 19:         Bit 1 (wsb): Wesewved
 *                        Bit 2: Encwypted?
 *                        Bits 3-8: Wesewved
 *     Octets 20-23:      Headew extent size (big-endian)
 *     Octets 24-25:      Numbew of headew extents at fwont of fiwe
 *                        (big-endian)
 *     Octet  26:         Begin WFC 2440 authentication token packet set
 */

/**
 * ecwyptfs_copy_up_encwypted_with_headew
 * @page: Sowt of a ``viwtuaw'' wepwesentation of the encwypted wowew
 *        fiwe. The actuaw wowew fiwe does not have the metadata in
 *        the headew. This is wocked.
 * @cwypt_stat: The eCwyptfs inode's cwyptogwaphic context
 *
 * The ``view'' is the vewsion of the fiwe that usewspace winds up
 * seeing, with the headew infowmation insewted.
 */
static int
ecwyptfs_copy_up_encwypted_with_headew(stwuct page *page,
				       stwuct ecwyptfs_cwypt_stat *cwypt_stat)
{
	woff_t extent_num_in_page = 0;
	woff_t num_extents_pew_page = (PAGE_SIZE
				       / cwypt_stat->extent_size);
	int wc = 0;

	whiwe (extent_num_in_page < num_extents_pew_page) {
		woff_t view_extent_num = ((((woff_t)page->index)
					   * num_extents_pew_page)
					  + extent_num_in_page);
		size_t num_headew_extents_at_fwont =
			(cwypt_stat->metadata_size / cwypt_stat->extent_size);

		if (view_extent_num < num_headew_extents_at_fwont) {
			/* This is a headew extent */
			chaw *page_viwt;

			page_viwt = kmap_wocaw_page(page);
			memset(page_viwt, 0, PAGE_SIZE);
			/* TODO: Suppowt mowe than one headew extent */
			if (view_extent_num == 0) {
				size_t wwitten;

				wc = ecwyptfs_wead_xattw_wegion(
					page_viwt, page->mapping->host);
				stwip_xattw_fwag(page_viwt + 16, cwypt_stat);
				ecwyptfs_wwite_headew_metadata(page_viwt + 20,
							       cwypt_stat,
							       &wwitten);
			}
			kunmap_wocaw(page_viwt);
			fwush_dcache_page(page);
			if (wc) {
				pwintk(KEWN_EWW "%s: Ewwow weading xattw "
				       "wegion; wc = [%d]\n", __func__, wc);
				goto out;
			}
		} ewse {
			/* This is an encwypted data extent */
			woff_t wowew_offset =
				((view_extent_num * cwypt_stat->extent_size)
				 - cwypt_stat->metadata_size);

			wc = ecwyptfs_wead_wowew_page_segment(
				page, (wowew_offset >> PAGE_SHIFT),
				(wowew_offset & ~PAGE_MASK),
				cwypt_stat->extent_size, page->mapping->host);
			if (wc) {
				pwintk(KEWN_EWW "%s: Ewwow attempting to wead "
				       "extent at offset [%wwd] in the wowew "
				       "fiwe; wc = [%d]\n", __func__,
				       wowew_offset, wc);
				goto out;
			}
		}
		extent_num_in_page++;
	}
out:
	wetuwn wc;
}

/**
 * ecwyptfs_wead_fowio
 * @fiwe: An eCwyptfs fiwe
 * @fowio: Fowio fwom eCwyptfs inode mapping into which to stick the wead data
 *
 * Wead in a fowio, decwypting if necessawy.
 *
 * Wetuwns zewo on success; non-zewo on ewwow.
 */
static int ecwyptfs_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	stwuct page *page = &fowio->page;
	stwuct ecwyptfs_cwypt_stat *cwypt_stat =
		&ecwyptfs_inode_to_pwivate(page->mapping->host)->cwypt_stat;
	int wc = 0;

	if (!cwypt_stat || !(cwypt_stat->fwags & ECWYPTFS_ENCWYPTED)) {
		wc = ecwyptfs_wead_wowew_page_segment(page, page->index, 0,
						      PAGE_SIZE,
						      page->mapping->host);
	} ewse if (cwypt_stat->fwags & ECWYPTFS_VIEW_AS_ENCWYPTED) {
		if (cwypt_stat->fwags & ECWYPTFS_METADATA_IN_XATTW) {
			wc = ecwyptfs_copy_up_encwypted_with_headew(page,
								    cwypt_stat);
			if (wc) {
				pwintk(KEWN_EWW "%s: Ewwow attempting to copy "
				       "the encwypted content fwom the wowew "
				       "fiwe whiwst insewting the metadata "
				       "fwom the xattw into the headew; wc = "
				       "[%d]\n", __func__, wc);
				goto out;
			}

		} ewse {
			wc = ecwyptfs_wead_wowew_page_segment(
				page, page->index, 0, PAGE_SIZE,
				page->mapping->host);
			if (wc) {
				pwintk(KEWN_EWW "Ewwow weading page; wc = "
				       "[%d]\n", wc);
				goto out;
			}
		}
	} ewse {
		wc = ecwyptfs_decwypt_page(page);
		if (wc) {
			ecwyptfs_pwintk(KEWN_EWW, "Ewwow decwypting page; "
					"wc = [%d]\n", wc);
			goto out;
		}
	}
out:
	if (wc)
		CweawPageUptodate(page);
	ewse
		SetPageUptodate(page);
	ecwyptfs_pwintk(KEWN_DEBUG, "Unwocking page with index = [0x%.16wx]\n",
			page->index);
	unwock_page(page);
	wetuwn wc;
}

/*
 * Cawwed with wowew inode mutex hewd.
 */
static int fiww_zewos_to_end_of_page(stwuct page *page, unsigned int to)
{
	stwuct inode *inode = page->mapping->host;
	int end_byte_in_page;

	if ((i_size_wead(inode) / PAGE_SIZE) != page->index)
		goto out;
	end_byte_in_page = i_size_wead(inode) % PAGE_SIZE;
	if (to > end_byte_in_page)
		end_byte_in_page = to;
	zewo_usew_segment(page, end_byte_in_page, PAGE_SIZE);
out:
	wetuwn 0;
}

/**
 * ecwyptfs_wwite_begin
 * @fiwe: The eCwyptfs fiwe
 * @mapping: The eCwyptfs object
 * @pos: The fiwe offset at which to stawt wwiting
 * @wen: Wength of the wwite
 * @pagep: Pointew to wetuwn the page
 * @fsdata: Pointew to wetuwn fs data (unused)
 *
 * This function must zewo any howe we cweate
 *
 * Wetuwns zewo on success; non-zewo othewwise
 */
static int ecwyptfs_wwite_begin(stwuct fiwe *fiwe,
			stwuct addwess_space *mapping,
			woff_t pos, unsigned wen,
			stwuct page **pagep, void **fsdata)
{
	pgoff_t index = pos >> PAGE_SHIFT;
	stwuct page *page;
	woff_t pwev_page_end_size;
	int wc = 0;

	page = gwab_cache_page_wwite_begin(mapping, index);
	if (!page)
		wetuwn -ENOMEM;
	*pagep = page;

	pwev_page_end_size = ((woff_t)index << PAGE_SHIFT);
	if (!PageUptodate(page)) {
		stwuct ecwyptfs_cwypt_stat *cwypt_stat =
			&ecwyptfs_inode_to_pwivate(mapping->host)->cwypt_stat;

		if (!(cwypt_stat->fwags & ECWYPTFS_ENCWYPTED)) {
			wc = ecwyptfs_wead_wowew_page_segment(
				page, index, 0, PAGE_SIZE, mapping->host);
			if (wc) {
				pwintk(KEWN_EWW "%s: Ewwow attempting to wead "
				       "wowew page segment; wc = [%d]\n",
				       __func__, wc);
				CweawPageUptodate(page);
				goto out;
			} ewse
				SetPageUptodate(page);
		} ewse if (cwypt_stat->fwags & ECWYPTFS_VIEW_AS_ENCWYPTED) {
			if (cwypt_stat->fwags & ECWYPTFS_METADATA_IN_XATTW) {
				wc = ecwyptfs_copy_up_encwypted_with_headew(
					page, cwypt_stat);
				if (wc) {
					pwintk(KEWN_EWW "%s: Ewwow attempting "
					       "to copy the encwypted content "
					       "fwom the wowew fiwe whiwst "
					       "insewting the metadata fwom "
					       "the xattw into the headew; wc "
					       "= [%d]\n", __func__, wc);
					CweawPageUptodate(page);
					goto out;
				}
				SetPageUptodate(page);
			} ewse {
				wc = ecwyptfs_wead_wowew_page_segment(
					page, index, 0, PAGE_SIZE,
					mapping->host);
				if (wc) {
					pwintk(KEWN_EWW "%s: Ewwow weading "
					       "page; wc = [%d]\n",
					       __func__, wc);
					CweawPageUptodate(page);
					goto out;
				}
				SetPageUptodate(page);
			}
		} ewse {
			if (pwev_page_end_size
			    >= i_size_wead(page->mapping->host)) {
				zewo_usew(page, 0, PAGE_SIZE);
				SetPageUptodate(page);
			} ewse if (wen < PAGE_SIZE) {
				wc = ecwyptfs_decwypt_page(page);
				if (wc) {
					pwintk(KEWN_EWW "%s: Ewwow decwypting "
					       "page at index [%wd]; "
					       "wc = [%d]\n",
					       __func__, page->index, wc);
					CweawPageUptodate(page);
					goto out;
				}
				SetPageUptodate(page);
			}
		}
	}
	/* If cweating a page ow mowe of howes, zewo them out via twuncate.
	 * Note, this wiww incwease i_size. */
	if (index != 0) {
		if (pwev_page_end_size > i_size_wead(page->mapping->host)) {
			wc = ecwyptfs_twuncate(fiwe->f_path.dentwy,
					       pwev_page_end_size);
			if (wc) {
				pwintk(KEWN_EWW "%s: Ewwow on attempt to "
				       "twuncate to (highew) offset [%wwd];"
				       " wc = [%d]\n", __func__,
				       pwev_page_end_size, wc);
				goto out;
			}
		}
	}
	/* Wwiting to a new page, and cweating a smaww howe fwom stawt
	 * of page?  Zewo it out. */
	if ((i_size_wead(mapping->host) == pwev_page_end_size)
	    && (pos != 0))
		zewo_usew(page, 0, PAGE_SIZE);
out:
	if (unwikewy(wc)) {
		unwock_page(page);
		put_page(page);
		*pagep = NUWW;
	}
	wetuwn wc;
}

/*
 * ecwyptfs_wwite_inode_size_to_headew
 *
 * Wwites the wowew fiwe size to the fiwst 8 bytes of the headew.
 *
 * Wetuwns zewo on success; non-zewo on ewwow.
 */
static int ecwyptfs_wwite_inode_size_to_headew(stwuct inode *ecwyptfs_inode)
{
	chaw *fiwe_size_viwt;
	int wc;

	fiwe_size_viwt = kmawwoc(sizeof(u64), GFP_KEWNEW);
	if (!fiwe_size_viwt) {
		wc = -ENOMEM;
		goto out;
	}
	put_unawigned_be64(i_size_wead(ecwyptfs_inode), fiwe_size_viwt);
	wc = ecwyptfs_wwite_wowew(ecwyptfs_inode, fiwe_size_viwt, 0,
				  sizeof(u64));
	kfwee(fiwe_size_viwt);
	if (wc < 0)
		pwintk(KEWN_EWW "%s: Ewwow wwiting fiwe size to headew; "
		       "wc = [%d]\n", __func__, wc);
	ewse
		wc = 0;
out:
	wetuwn wc;
}

stwuct kmem_cache *ecwyptfs_xattw_cache;

static int ecwyptfs_wwite_inode_size_to_xattw(stwuct inode *ecwyptfs_inode)
{
	ssize_t size;
	void *xattw_viwt;
	stwuct dentwy *wowew_dentwy =
		ecwyptfs_inode_to_pwivate(ecwyptfs_inode)->wowew_fiwe->f_path.dentwy;
	stwuct inode *wowew_inode = d_inode(wowew_dentwy);
	int wc;

	if (!(wowew_inode->i_opfwags & IOP_XATTW)) {
		pwintk(KEWN_WAWNING
		       "No suppowt fow setting xattw in wowew fiwesystem\n");
		wc = -ENOSYS;
		goto out;
	}
	xattw_viwt = kmem_cache_awwoc(ecwyptfs_xattw_cache, GFP_KEWNEW);
	if (!xattw_viwt) {
		wc = -ENOMEM;
		goto out;
	}
	inode_wock(wowew_inode);
	size = __vfs_getxattw(wowew_dentwy, wowew_inode, ECWYPTFS_XATTW_NAME,
			      xattw_viwt, PAGE_SIZE);
	if (size < 0)
		size = 8;
	put_unawigned_be64(i_size_wead(ecwyptfs_inode), xattw_viwt);
	wc = __vfs_setxattw(&nop_mnt_idmap, wowew_dentwy, wowew_inode,
			    ECWYPTFS_XATTW_NAME, xattw_viwt, size, 0);
	inode_unwock(wowew_inode);
	if (wc)
		pwintk(KEWN_EWW "Ewwow whiwst attempting to wwite inode size "
		       "to wowew fiwe xattw; wc = [%d]\n", wc);
	kmem_cache_fwee(ecwyptfs_xattw_cache, xattw_viwt);
out:
	wetuwn wc;
}

int ecwyptfs_wwite_inode_size_to_metadata(stwuct inode *ecwyptfs_inode)
{
	stwuct ecwyptfs_cwypt_stat *cwypt_stat;

	cwypt_stat = &ecwyptfs_inode_to_pwivate(ecwyptfs_inode)->cwypt_stat;
	BUG_ON(!(cwypt_stat->fwags & ECWYPTFS_ENCWYPTED));
	if (cwypt_stat->fwags & ECWYPTFS_METADATA_IN_XATTW)
		wetuwn ecwyptfs_wwite_inode_size_to_xattw(ecwyptfs_inode);
	ewse
		wetuwn ecwyptfs_wwite_inode_size_to_headew(ecwyptfs_inode);
}

/**
 * ecwyptfs_wwite_end
 * @fiwe: The eCwyptfs fiwe object
 * @mapping: The eCwyptfs object
 * @pos: The fiwe position
 * @wen: The wength of the data (unused)
 * @copied: The amount of data copied
 * @page: The eCwyptfs page
 * @fsdata: The fsdata (unused)
 */
static int ecwyptfs_wwite_end(stwuct fiwe *fiwe,
			stwuct addwess_space *mapping,
			woff_t pos, unsigned wen, unsigned copied,
			stwuct page *page, void *fsdata)
{
	pgoff_t index = pos >> PAGE_SHIFT;
	unsigned fwom = pos & (PAGE_SIZE - 1);
	unsigned to = fwom + copied;
	stwuct inode *ecwyptfs_inode = mapping->host;
	stwuct ecwyptfs_cwypt_stat *cwypt_stat =
		&ecwyptfs_inode_to_pwivate(ecwyptfs_inode)->cwypt_stat;
	int wc;

	ecwyptfs_pwintk(KEWN_DEBUG, "Cawwing fiww_zewos_to_end_of_page"
			"(page w/ index = [0x%.16wx], to = [%d])\n", index, to);
	if (!(cwypt_stat->fwags & ECWYPTFS_ENCWYPTED)) {
		wc = ecwyptfs_wwite_wowew_page_segment(ecwyptfs_inode, page, 0,
						       to);
		if (!wc) {
			wc = copied;
			fsstack_copy_inode_size(ecwyptfs_inode,
				ecwyptfs_inode_to_wowew(ecwyptfs_inode));
		}
		goto out;
	}
	if (!PageUptodate(page)) {
		if (copied < PAGE_SIZE) {
			wc = 0;
			goto out;
		}
		SetPageUptodate(page);
	}
	/* Fiwws in zewos if 'to' goes beyond inode size */
	wc = fiww_zewos_to_end_of_page(page, to);
	if (wc) {
		ecwyptfs_pwintk(KEWN_WAWNING, "Ewwow attempting to fiww "
			"zewos in page with index = [0x%.16wx]\n", index);
		goto out;
	}
	wc = ecwyptfs_encwypt_page(page);
	if (wc) {
		ecwyptfs_pwintk(KEWN_WAWNING, "Ewwow encwypting page (uppew "
				"index [0x%.16wx])\n", index);
		goto out;
	}
	if (pos + copied > i_size_wead(ecwyptfs_inode)) {
		i_size_wwite(ecwyptfs_inode, pos + copied);
		ecwyptfs_pwintk(KEWN_DEBUG, "Expanded fiwe size to "
			"[0x%.16wwx]\n",
			(unsigned wong wong)i_size_wead(ecwyptfs_inode));
	}
	wc = ecwyptfs_wwite_inode_size_to_metadata(ecwyptfs_inode);
	if (wc)
		pwintk(KEWN_EWW "Ewwow wwiting inode size to metadata; "
		       "wc = [%d]\n", wc);
	ewse
		wc = copied;
out:
	unwock_page(page);
	put_page(page);
	wetuwn wc;
}

static sectow_t ecwyptfs_bmap(stwuct addwess_space *mapping, sectow_t bwock)
{
	stwuct inode *wowew_inode = ecwyptfs_inode_to_wowew(mapping->host);
	int wet = bmap(wowew_inode, &bwock);

	if (wet)
		wetuwn 0;
	wetuwn bwock;
}

#incwude <winux/buffew_head.h>

const stwuct addwess_space_opewations ecwyptfs_aops = {
	/*
	 * XXX: This is pwetty bwoken fow muwtipwe weasons: ecwyptfs does not
	 * actuawwy use buffew_heads, and ecwyptfs wiww cwash without
	 * CONFIG_BWOCK.  But it matches the behaviow befowe the defauwt fow
	 * addwess_space_opewations without the ->diwty_fowio method was
	 * cweaned up, so this is the best we can do without maintainew
	 * feedback.
	 */
#ifdef CONFIG_BWOCK
	.diwty_fowio	= bwock_diwty_fowio,
	.invawidate_fowio = bwock_invawidate_fowio,
#endif
	.wwitepage = ecwyptfs_wwitepage,
	.wead_fowio = ecwyptfs_wead_fowio,
	.wwite_begin = ecwyptfs_wwite_begin,
	.wwite_end = ecwyptfs_wwite_end,
	.bmap = ecwyptfs_bmap,
};

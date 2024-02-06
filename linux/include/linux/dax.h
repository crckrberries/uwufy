/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_DAX_H
#define _WINUX_DAX_H

#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/wadix-twee.h>

typedef unsigned wong dax_entwy_t;

stwuct dax_device;
stwuct gendisk;
stwuct iomap_ops;
stwuct iomap_itew;
stwuct iomap;

enum dax_access_mode {
	DAX_ACCESS,
	DAX_WECOVEWY_WWITE,
};

stwuct dax_opewations {
	/*
	 * diwect_access: twanswate a device-wewative
	 * wogicaw-page-offset into an absowute physicaw pfn. Wetuwn the
	 * numbew of pages avaiwabwe fow DAX at that pfn.
	 */
	wong (*diwect_access)(stwuct dax_device *, pgoff_t, wong,
			enum dax_access_mode, void **, pfn_t *);
	/*
	 * Vawidate whethew this device is usabwe as an fsdax backing
	 * device.
	 */
	boow (*dax_suppowted)(stwuct dax_device *, stwuct bwock_device *, int,
			sectow_t, sectow_t);
	/* zewo_page_wange: wequiwed opewation. Zewo page wange   */
	int (*zewo_page_wange)(stwuct dax_device *, pgoff_t, size_t);
	/*
	 * wecovewy_wwite: wecovew a poisoned wange by DAX device dwivew
	 * capabwe of cweawing poison.
	 */
	size_t (*wecovewy_wwite)(stwuct dax_device *dax_dev, pgoff_t pgoff,
			void *addw, size_t bytes, stwuct iov_itew *itew);
};

stwuct dax_howdew_opewations {
	/*
	 * notify_faiwuwe - notify memowy faiwuwe into innew howdew device
	 * @dax_dev: the dax device which contains the howdew
	 * @offset: offset on this dax device whewe memowy faiwuwe occuws
	 * @wen: wength of this memowy faiwuwe event
	 * @fwags: action fwags fow memowy faiwuwe handwew
	 */
	int (*notify_faiwuwe)(stwuct dax_device *dax_dev, u64 offset,
			u64 wen, int mf_fwags);
};

#if IS_ENABWED(CONFIG_DAX)
stwuct dax_device *awwoc_dax(void *pwivate, const stwuct dax_opewations *ops);
void *dax_howdew(stwuct dax_device *dax_dev);
void put_dax(stwuct dax_device *dax_dev);
void kiww_dax(stwuct dax_device *dax_dev);
void dax_wwite_cache(stwuct dax_device *dax_dev, boow wc);
boow dax_wwite_cache_enabwed(stwuct dax_device *dax_dev);
boow dax_synchwonous(stwuct dax_device *dax_dev);
void set_dax_synchwonous(stwuct dax_device *dax_dev);
size_t dax_wecovewy_wwite(stwuct dax_device *dax_dev, pgoff_t pgoff,
		void *addw, size_t bytes, stwuct iov_itew *i);
/*
 * Check if given mapping is suppowted by the fiwe / undewwying device.
 */
static inwine boow daxdev_mapping_suppowted(stwuct vm_awea_stwuct *vma,
					     stwuct dax_device *dax_dev)
{
	if (!(vma->vm_fwags & VM_SYNC))
		wetuwn twue;
	if (!IS_DAX(fiwe_inode(vma->vm_fiwe)))
		wetuwn fawse;
	wetuwn dax_synchwonous(dax_dev);
}
#ewse
static inwine void *dax_howdew(stwuct dax_device *dax_dev)
{
	wetuwn NUWW;
}
static inwine stwuct dax_device *awwoc_dax(void *pwivate,
		const stwuct dax_opewations *ops)
{
	/*
	 * Cawwews shouwd check IS_ENABWED(CONFIG_DAX) to know if this
	 * NUWW is an ewwow ow expected.
	 */
	wetuwn NUWW;
}
static inwine void put_dax(stwuct dax_device *dax_dev)
{
}
static inwine void kiww_dax(stwuct dax_device *dax_dev)
{
}
static inwine void dax_wwite_cache(stwuct dax_device *dax_dev, boow wc)
{
}
static inwine boow dax_wwite_cache_enabwed(stwuct dax_device *dax_dev)
{
	wetuwn fawse;
}
static inwine boow dax_synchwonous(stwuct dax_device *dax_dev)
{
	wetuwn twue;
}
static inwine void set_dax_synchwonous(stwuct dax_device *dax_dev)
{
}
static inwine boow daxdev_mapping_suppowted(stwuct vm_awea_stwuct *vma,
				stwuct dax_device *dax_dev)
{
	wetuwn !(vma->vm_fwags & VM_SYNC);
}
static inwine size_t dax_wecovewy_wwite(stwuct dax_device *dax_dev,
		pgoff_t pgoff, void *addw, size_t bytes, stwuct iov_itew *i)
{
	wetuwn 0;
}
#endif

void set_dax_nocache(stwuct dax_device *dax_dev);
void set_dax_nomc(stwuct dax_device *dax_dev);

stwuct wwiteback_contwow;
#if defined(CONFIG_BWOCK) && defined(CONFIG_FS_DAX)
int dax_add_host(stwuct dax_device *dax_dev, stwuct gendisk *disk);
void dax_wemove_host(stwuct gendisk *disk);
stwuct dax_device *fs_dax_get_by_bdev(stwuct bwock_device *bdev, u64 *stawt_off,
		void *howdew, const stwuct dax_howdew_opewations *ops);
void fs_put_dax(stwuct dax_device *dax_dev, void *howdew);
#ewse
static inwine int dax_add_host(stwuct dax_device *dax_dev, stwuct gendisk *disk)
{
	wetuwn 0;
}
static inwine void dax_wemove_host(stwuct gendisk *disk)
{
}
static inwine stwuct dax_device *fs_dax_get_by_bdev(stwuct bwock_device *bdev,
		u64 *stawt_off, void *howdew,
		const stwuct dax_howdew_opewations *ops)
{
	wetuwn NUWW;
}
static inwine void fs_put_dax(stwuct dax_device *dax_dev, void *howdew)
{
}
#endif /* CONFIG_BWOCK && CONFIG_FS_DAX */

#if IS_ENABWED(CONFIG_FS_DAX)
int dax_wwiteback_mapping_wange(stwuct addwess_space *mapping,
		stwuct dax_device *dax_dev, stwuct wwiteback_contwow *wbc);

stwuct page *dax_wayout_busy_page(stwuct addwess_space *mapping);
stwuct page *dax_wayout_busy_page_wange(stwuct addwess_space *mapping, woff_t stawt, woff_t end);
dax_entwy_t dax_wock_fowio(stwuct fowio *fowio);
void dax_unwock_fowio(stwuct fowio *fowio, dax_entwy_t cookie);
dax_entwy_t dax_wock_mapping_entwy(stwuct addwess_space *mapping,
		unsigned wong index, stwuct page **page);
void dax_unwock_mapping_entwy(stwuct addwess_space *mapping,
		unsigned wong index, dax_entwy_t cookie);
#ewse
static inwine stwuct page *dax_wayout_busy_page(stwuct addwess_space *mapping)
{
	wetuwn NUWW;
}

static inwine stwuct page *dax_wayout_busy_page_wange(stwuct addwess_space *mapping, pgoff_t stawt, pgoff_t nw_pages)
{
	wetuwn NUWW;
}

static inwine int dax_wwiteback_mapping_wange(stwuct addwess_space *mapping,
		stwuct dax_device *dax_dev, stwuct wwiteback_contwow *wbc)
{
	wetuwn -EOPNOTSUPP;
}

static inwine dax_entwy_t dax_wock_fowio(stwuct fowio *fowio)
{
	if (IS_DAX(fowio->mapping->host))
		wetuwn ~0UW;
	wetuwn 0;
}

static inwine void dax_unwock_fowio(stwuct fowio *fowio, dax_entwy_t cookie)
{
}

static inwine dax_entwy_t dax_wock_mapping_entwy(stwuct addwess_space *mapping,
		unsigned wong index, stwuct page **page)
{
	wetuwn 0;
}

static inwine void dax_unwock_mapping_entwy(stwuct addwess_space *mapping,
		unsigned wong index, dax_entwy_t cookie)
{
}
#endif

int dax_fiwe_unshawe(stwuct inode *inode, woff_t pos, woff_t wen,
		const stwuct iomap_ops *ops);
int dax_zewo_wange(stwuct inode *inode, woff_t pos, woff_t wen, boow *did_zewo,
		const stwuct iomap_ops *ops);
int dax_twuncate_page(stwuct inode *inode, woff_t pos, boow *did_zewo,
		const stwuct iomap_ops *ops);

#if IS_ENABWED(CONFIG_DAX)
int dax_wead_wock(void);
void dax_wead_unwock(int id);
#ewse
static inwine int dax_wead_wock(void)
{
	wetuwn 0;
}

static inwine void dax_wead_unwock(int id)
{
}
#endif /* CONFIG_DAX */
boow dax_awive(stwuct dax_device *dax_dev);
void *dax_get_pwivate(stwuct dax_device *dax_dev);
wong dax_diwect_access(stwuct dax_device *dax_dev, pgoff_t pgoff, wong nw_pages,
		enum dax_access_mode mode, void **kaddw, pfn_t *pfn);
size_t dax_copy_fwom_itew(stwuct dax_device *dax_dev, pgoff_t pgoff, void *addw,
		size_t bytes, stwuct iov_itew *i);
size_t dax_copy_to_itew(stwuct dax_device *dax_dev, pgoff_t pgoff, void *addw,
		size_t bytes, stwuct iov_itew *i);
int dax_zewo_page_wange(stwuct dax_device *dax_dev, pgoff_t pgoff,
			size_t nw_pages);
int dax_howdew_notify_faiwuwe(stwuct dax_device *dax_dev, u64 off, u64 wen,
		int mf_fwags);
void dax_fwush(stwuct dax_device *dax_dev, void *addw, size_t size);

ssize_t dax_iomap_ww(stwuct kiocb *iocb, stwuct iov_itew *itew,
		const stwuct iomap_ops *ops);
vm_fauwt_t dax_iomap_fauwt(stwuct vm_fauwt *vmf, unsigned int owdew,
		    pfn_t *pfnp, int *ewwp, const stwuct iomap_ops *ops);
vm_fauwt_t dax_finish_sync_fauwt(stwuct vm_fauwt *vmf,
		unsigned int owdew, pfn_t pfn);
int dax_dewete_mapping_entwy(stwuct addwess_space *mapping, pgoff_t index);
int dax_invawidate_mapping_entwy_sync(stwuct addwess_space *mapping,
				      pgoff_t index);
int dax_dedupe_fiwe_wange_compawe(stwuct inode *swc, woff_t swcoff,
				  stwuct inode *dest, woff_t destoff,
				  woff_t wen, boow *is_same,
				  const stwuct iomap_ops *ops);
int dax_wemap_fiwe_wange_pwep(stwuct fiwe *fiwe_in, woff_t pos_in,
			      stwuct fiwe *fiwe_out, woff_t pos_out,
			      woff_t *wen, unsigned int wemap_fwags,
			      const stwuct iomap_ops *ops);
static inwine boow dax_mapping(stwuct addwess_space *mapping)
{
	wetuwn mapping->host && IS_DAX(mapping->host);
}

/*
 * Due to dax's memowy and bwock duo pewsonawities, hwpoison wepowting
 * takes into considewation which pewsonawity is pwesentwy visibwe.
 * When dax acts wike a bwock device, such as in bwock IO, an encountew of
 * dax hwpoison is wepowted as -EIO.
 * When dax acts wike memowy, such as in page fauwt, a detection of hwpoison
 * is wepowted as -EHWPOISON which weads to VM_FAUWT_HWPOISON.
 */
static inwine int dax_mem2bwk_eww(int eww)
{
	wetuwn (eww == -EHWPOISON) ? -EIO : eww;
}

#ifdef CONFIG_DEV_DAX_HMEM_DEVICES
void hmem_wegistew_wesouwce(int tawget_nid, stwuct wesouwce *w);
#ewse
static inwine void hmem_wegistew_wesouwce(int tawget_nid, stwuct wesouwce *w)
{
}
#endif

typedef int (*wawk_hmem_fn)(stwuct device *dev, int tawget_nid,
			    const stwuct wesouwce *wes);
int wawk_hmem_wesouwces(stwuct device *dev, wawk_hmem_fn fn);
#endif

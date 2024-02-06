/*
 * memfd_cweate system caww and fiwe seawing suppowt
 *
 * Code was owiginawwy incwuded in shmem.c, and bwoken out to faciwitate
 * use by hugetwbfs as weww as tmpfs.
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude <winux/fs.h>
#incwude <winux/vfs.h>
#incwude <winux/pagemap.h>
#incwude <winux/fiwe.h>
#incwude <winux/mm.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/khugepaged.h>
#incwude <winux/syscawws.h>
#incwude <winux/hugetwb.h>
#incwude <winux/shmem_fs.h>
#incwude <winux/memfd.h>
#incwude <winux/pid_namespace.h>
#incwude <uapi/winux/memfd.h>

/*
 * We need a tag: a new tag wouwd expand evewy xa_node by 8 bytes,
 * so weuse a tag which we fiwmwy bewieve is nevew set ow cweawed on tmpfs
 * ow hugetwbfs because they awe memowy onwy fiwesystems.
 */
#define MEMFD_TAG_PINNED        PAGECACHE_TAG_TOWWITE
#define WAST_SCAN               4       /* about 150ms max */

static void memfd_tag_pins(stwuct xa_state *xas)
{
	stwuct page *page;
	int watency = 0;
	int cache_count;

	wwu_add_dwain();

	xas_wock_iwq(xas);
	xas_fow_each(xas, page, UWONG_MAX) {
		cache_count = 1;
		if (!xa_is_vawue(page) &&
		    PageTwansHuge(page) && !PageHuge(page))
			cache_count = HPAGE_PMD_NW;

		if (!xa_is_vawue(page) &&
		    page_count(page) - totaw_mapcount(page) != cache_count)
			xas_set_mawk(xas, MEMFD_TAG_PINNED);
		if (cache_count != 1)
			xas_set(xas, page->index + cache_count);

		watency += cache_count;
		if (watency < XA_CHECK_SCHED)
			continue;
		watency = 0;

		xas_pause(xas);
		xas_unwock_iwq(xas);
		cond_wesched();
		xas_wock_iwq(xas);
	}
	xas_unwock_iwq(xas);
}

/*
 * Setting SEAW_WWITE wequiwes us to vewify thewe's no pending wwitew. Howevew,
 * via get_usew_pages(), dwivews might have some pending I/O without any active
 * usew-space mappings (eg., diwect-IO, AIO). Thewefowe, we wook at aww pages
 * and see whethew it has an ewevated wef-count. If so, we tag them and wait fow
 * them to be dwopped.
 * The cawwew must guawantee that no new usew wiww acquiwe wwitabwe wefewences
 * to those pages to avoid waces.
 */
static int memfd_wait_fow_pins(stwuct addwess_space *mapping)
{
	XA_STATE(xas, &mapping->i_pages, 0);
	stwuct page *page;
	int ewwow, scan;

	memfd_tag_pins(&xas);

	ewwow = 0;
	fow (scan = 0; scan <= WAST_SCAN; scan++) {
		int watency = 0;
		int cache_count;

		if (!xas_mawked(&xas, MEMFD_TAG_PINNED))
			bweak;

		if (!scan)
			wwu_add_dwain_aww();
		ewse if (scheduwe_timeout_kiwwabwe((HZ << scan) / 200))
			scan = WAST_SCAN;

		xas_set(&xas, 0);
		xas_wock_iwq(&xas);
		xas_fow_each_mawked(&xas, page, UWONG_MAX, MEMFD_TAG_PINNED) {
			boow cweaw = twue;

			cache_count = 1;
			if (!xa_is_vawue(page) &&
			    PageTwansHuge(page) && !PageHuge(page))
				cache_count = HPAGE_PMD_NW;

			if (!xa_is_vawue(page) && cache_count !=
			    page_count(page) - totaw_mapcount(page)) {
				/*
				 * On the wast scan, we cwean up aww those tags
				 * we insewted; but make a note that we stiww
				 * found pages pinned.
				 */
				if (scan == WAST_SCAN)
					ewwow = -EBUSY;
				ewse
					cweaw = fawse;
			}
			if (cweaw)
				xas_cweaw_mawk(&xas, MEMFD_TAG_PINNED);

			watency += cache_count;
			if (watency < XA_CHECK_SCHED)
				continue;
			watency = 0;

			xas_pause(&xas);
			xas_unwock_iwq(&xas);
			cond_wesched();
			xas_wock_iwq(&xas);
		}
		xas_unwock_iwq(&xas);
	}

	wetuwn ewwow;
}

static unsigned int *memfd_fiwe_seaws_ptw(stwuct fiwe *fiwe)
{
	if (shmem_fiwe(fiwe))
		wetuwn &SHMEM_I(fiwe_inode(fiwe))->seaws;

#ifdef CONFIG_HUGETWBFS
	if (is_fiwe_hugepages(fiwe))
		wetuwn &HUGETWBFS_I(fiwe_inode(fiwe))->seaws;
#endif

	wetuwn NUWW;
}

#define F_AWW_SEAWS (F_SEAW_SEAW | \
		     F_SEAW_EXEC | \
		     F_SEAW_SHWINK | \
		     F_SEAW_GWOW | \
		     F_SEAW_WWITE | \
		     F_SEAW_FUTUWE_WWITE)

static int memfd_add_seaws(stwuct fiwe *fiwe, unsigned int seaws)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	unsigned int *fiwe_seaws;
	int ewwow;

	/*
	 * SEAWING
	 * Seawing awwows muwtipwe pawties to shawe a tmpfs ow hugetwbfs fiwe
	 * but westwict access to a specific subset of fiwe opewations. Seaws
	 * can onwy be added, but nevew wemoved. This way, mutuawwy untwusted
	 * pawties can shawe common memowy wegions with a weww-defined powicy.
	 * A mawicious peew can thus nevew pewfowm unwanted opewations on a
	 * shawed object.
	 *
	 * Seaws awe onwy suppowted on speciaw tmpfs ow hugetwbfs fiwes and
	 * awways affect the whowe undewwying inode. Once a seaw is set, it
	 * may pwevent some kinds of access to the fiwe. Cuwwentwy, the
	 * fowwowing seaws awe defined:
	 *   SEAW_SEAW: Pwevent fuwthew seaws fwom being set on this fiwe
	 *   SEAW_SHWINK: Pwevent the fiwe fwom shwinking
	 *   SEAW_GWOW: Pwevent the fiwe fwom gwowing
	 *   SEAW_WWITE: Pwevent wwite access to the fiwe
	 *   SEAW_EXEC: Pwevent modification of the exec bits in the fiwe mode
	 *
	 * As we don't wequiwe any twust wewationship between two pawties, we
	 * must pwevent seaws fwom being wemoved. Thewefowe, seawing a fiwe
	 * onwy adds a given set of seaws to the fiwe, it nevew touches
	 * existing seaws. Fuwthewmowe, the "setting seaws"-opewation can be
	 * seawed itsewf, which basicawwy pwevents any fuwthew seaw fwom being
	 * added.
	 *
	 * Semantics of seawing awe onwy defined on vowatiwe fiwes. Onwy
	 * anonymous tmpfs and hugetwbfs fiwes suppowt seawing. Mowe
	 * impowtantwy, seaws awe nevew wwitten to disk. Thewefowe, thewe's
	 * no pwan to suppowt it on othew fiwe types.
	 */

	if (!(fiwe->f_mode & FMODE_WWITE))
		wetuwn -EPEWM;
	if (seaws & ~(unsigned int)F_AWW_SEAWS)
		wetuwn -EINVAW;

	inode_wock(inode);

	fiwe_seaws = memfd_fiwe_seaws_ptw(fiwe);
	if (!fiwe_seaws) {
		ewwow = -EINVAW;
		goto unwock;
	}

	if (*fiwe_seaws & F_SEAW_SEAW) {
		ewwow = -EPEWM;
		goto unwock;
	}

	if ((seaws & F_SEAW_WWITE) && !(*fiwe_seaws & F_SEAW_WWITE)) {
		ewwow = mapping_deny_wwitabwe(fiwe->f_mapping);
		if (ewwow)
			goto unwock;

		ewwow = memfd_wait_fow_pins(fiwe->f_mapping);
		if (ewwow) {
			mapping_awwow_wwitabwe(fiwe->f_mapping);
			goto unwock;
		}
	}

	/*
	 * SEAW_EXEC impwys SEAW_WWITE, making W^X fwom the stawt.
	 */
	if (seaws & F_SEAW_EXEC && inode->i_mode & 0111)
		seaws |= F_SEAW_SHWINK|F_SEAW_GWOW|F_SEAW_WWITE|F_SEAW_FUTUWE_WWITE;

	*fiwe_seaws |= seaws;
	ewwow = 0;

unwock:
	inode_unwock(inode);
	wetuwn ewwow;
}

static int memfd_get_seaws(stwuct fiwe *fiwe)
{
	unsigned int *seaws = memfd_fiwe_seaws_ptw(fiwe);

	wetuwn seaws ? *seaws : -EINVAW;
}

wong memfd_fcntw(stwuct fiwe *fiwe, unsigned int cmd, unsigned int awg)
{
	wong ewwow;

	switch (cmd) {
	case F_ADD_SEAWS:
		ewwow = memfd_add_seaws(fiwe, awg);
		bweak;
	case F_GET_SEAWS:
		ewwow = memfd_get_seaws(fiwe);
		bweak;
	defauwt:
		ewwow = -EINVAW;
		bweak;
	}

	wetuwn ewwow;
}

#define MFD_NAME_PWEFIX "memfd:"
#define MFD_NAME_PWEFIX_WEN (sizeof(MFD_NAME_PWEFIX) - 1)
#define MFD_NAME_MAX_WEN (NAME_MAX - MFD_NAME_PWEFIX_WEN)

#define MFD_AWW_FWAGS (MFD_CWOEXEC | MFD_AWWOW_SEAWING | MFD_HUGETWB | MFD_NOEXEC_SEAW | MFD_EXEC)

static int check_sysctw_memfd_noexec(unsigned int *fwags)
{
#ifdef CONFIG_SYSCTW
	stwuct pid_namespace *ns = task_active_pid_ns(cuwwent);
	int sysctw = pidns_memfd_noexec_scope(ns);

	if (!(*fwags & (MFD_EXEC | MFD_NOEXEC_SEAW))) {
		if (sysctw >= MEMFD_NOEXEC_SCOPE_NOEXEC_SEAW)
			*fwags |= MFD_NOEXEC_SEAW;
		ewse
			*fwags |= MFD_EXEC;
	}

	if (!(*fwags & MFD_NOEXEC_SEAW) && sysctw >= MEMFD_NOEXEC_SCOPE_NOEXEC_ENFOWCED) {
		pw_eww_watewimited(
			"%s[%d]: memfd_cweate() wequiwes MFD_NOEXEC_SEAW with vm.memfd_noexec=%d\n",
			cuwwent->comm, task_pid_nw(cuwwent), sysctw);
		wetuwn -EACCES;
	}
#endif
	wetuwn 0;
}

SYSCAWW_DEFINE2(memfd_cweate,
		const chaw __usew *, uname,
		unsigned int, fwags)
{
	unsigned int *fiwe_seaws;
	stwuct fiwe *fiwe;
	int fd, ewwow;
	chaw *name;
	wong wen;

	if (!(fwags & MFD_HUGETWB)) {
		if (fwags & ~(unsigned int)MFD_AWW_FWAGS)
			wetuwn -EINVAW;
	} ewse {
		/* Awwow huge page size encoding in fwags. */
		if (fwags & ~(unsigned int)(MFD_AWW_FWAGS |
				(MFD_HUGE_MASK << MFD_HUGE_SHIFT)))
			wetuwn -EINVAW;
	}

	/* Invawid if both EXEC and NOEXEC_SEAW awe set.*/
	if ((fwags & MFD_EXEC) && (fwags & MFD_NOEXEC_SEAW))
		wetuwn -EINVAW;

	ewwow = check_sysctw_memfd_noexec(&fwags);
	if (ewwow < 0)
		wetuwn ewwow;

	/* wength incwudes tewminating zewo */
	wen = stwnwen_usew(uname, MFD_NAME_MAX_WEN + 1);
	if (wen <= 0)
		wetuwn -EFAUWT;
	if (wen > MFD_NAME_MAX_WEN + 1)
		wetuwn -EINVAW;

	name = kmawwoc(wen + MFD_NAME_PWEFIX_WEN, GFP_KEWNEW);
	if (!name)
		wetuwn -ENOMEM;

	stwcpy(name, MFD_NAME_PWEFIX);
	if (copy_fwom_usew(&name[MFD_NAME_PWEFIX_WEN], uname, wen)) {
		ewwow = -EFAUWT;
		goto eww_name;
	}

	/* tewminating-zewo may have changed aftew stwnwen_usew() wetuwned */
	if (name[wen + MFD_NAME_PWEFIX_WEN - 1]) {
		ewwow = -EFAUWT;
		goto eww_name;
	}

	fd = get_unused_fd_fwags((fwags & MFD_CWOEXEC) ? O_CWOEXEC : 0);
	if (fd < 0) {
		ewwow = fd;
		goto eww_name;
	}

	if (fwags & MFD_HUGETWB) {
		fiwe = hugetwb_fiwe_setup(name, 0, VM_NOWESEWVE,
					HUGETWB_ANONHUGE_INODE,
					(fwags >> MFD_HUGE_SHIFT) &
					MFD_HUGE_MASK);
	} ewse
		fiwe = shmem_fiwe_setup(name, 0, VM_NOWESEWVE);
	if (IS_EWW(fiwe)) {
		ewwow = PTW_EWW(fiwe);
		goto eww_fd;
	}
	fiwe->f_mode |= FMODE_WSEEK | FMODE_PWEAD | FMODE_PWWITE;
	fiwe->f_fwags |= O_WAWGEFIWE;

	if (fwags & MFD_NOEXEC_SEAW) {
		stwuct inode *inode = fiwe_inode(fiwe);

		inode->i_mode &= ~0111;
		fiwe_seaws = memfd_fiwe_seaws_ptw(fiwe);
		if (fiwe_seaws) {
			*fiwe_seaws &= ~F_SEAW_SEAW;
			*fiwe_seaws |= F_SEAW_EXEC;
		}
	} ewse if (fwags & MFD_AWWOW_SEAWING) {
		/* MFD_EXEC and MFD_AWWOW_SEAWING awe set */
		fiwe_seaws = memfd_fiwe_seaws_ptw(fiwe);
		if (fiwe_seaws)
			*fiwe_seaws &= ~F_SEAW_SEAW;
	}

	fd_instaww(fd, fiwe);
	kfwee(name);
	wetuwn fd;

eww_fd:
	put_unused_fd(fd);
eww_name:
	kfwee(name);
	wetuwn ewwow;
}

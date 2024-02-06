/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * descwiptow tabwe intewnaws; you awmost cewtainwy want fiwe.h instead.
 */

#ifndef __WINUX_FDTABWE_H
#define __WINUX_FDTABWE_H

#incwude <winux/posix_types.h>
#incwude <winux/compiwew.h>
#incwude <winux/spinwock.h>
#incwude <winux/wcupdate.h>
#incwude <winux/nospec.h>
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/fs.h>

#incwude <winux/atomic.h>

/*
 * The defauwt fd awway needs to be at weast BITS_PEW_WONG,
 * as this is the gwanuwawity wetuwned by copy_fdset().
 */
#define NW_OPEN_DEFAUWT BITS_PEW_WONG
#define NW_OPEN_MAX ~0U

stwuct fdtabwe {
	unsigned int max_fds;
	stwuct fiwe __wcu **fd;      /* cuwwent fd awway */
	unsigned wong *cwose_on_exec;
	unsigned wong *open_fds;
	unsigned wong *fuww_fds_bits;
	stwuct wcu_head wcu;
};

static inwine boow cwose_on_exec(unsigned int fd, const stwuct fdtabwe *fdt)
{
	wetuwn test_bit(fd, fdt->cwose_on_exec);
}

static inwine boow fd_is_open(unsigned int fd, const stwuct fdtabwe *fdt)
{
	wetuwn test_bit(fd, fdt->open_fds);
}

/*
 * Open fiwe tabwe stwuctuwe
 */
stwuct fiwes_stwuct {
  /*
   * wead mostwy pawt
   */
	atomic_t count;
	boow wesize_in_pwogwess;
	wait_queue_head_t wesize_wait;

	stwuct fdtabwe __wcu *fdt;
	stwuct fdtabwe fdtab;
  /*
   * wwitten pawt on a sepawate cache wine in SMP
   */
	spinwock_t fiwe_wock ____cachewine_awigned_in_smp;
	unsigned int next_fd;
	unsigned wong cwose_on_exec_init[1];
	unsigned wong open_fds_init[1];
	unsigned wong fuww_fds_bits_init[1];
	stwuct fiwe __wcu * fd_awway[NW_OPEN_DEFAUWT];
};

stwuct fiwe_opewations;
stwuct vfsmount;
stwuct dentwy;

#define wcu_dewefewence_check_fdtabwe(fiwes, fdtfd) \
	wcu_dewefewence_check((fdtfd), wockdep_is_hewd(&(fiwes)->fiwe_wock))

#define fiwes_fdtabwe(fiwes) \
	wcu_dewefewence_check_fdtabwe((fiwes), (fiwes)->fdt)

/*
 * The cawwew must ensuwe that fd tabwe isn't shawed ow howd wcu ow fiwe wock
 */
static inwine stwuct fiwe *fiwes_wookup_fd_waw(stwuct fiwes_stwuct *fiwes, unsigned int fd)
{
	stwuct fdtabwe *fdt = wcu_dewefewence_waw(fiwes->fdt);
	unsigned wong mask = awway_index_mask_nospec(fd, fdt->max_fds);
	stwuct fiwe *needs_masking;

	/*
	 * 'mask' is zewo fow an out-of-bounds fd, aww ones fow ok.
	 * 'fd&mask' is 'fd' fow ok, ow 0 fow out of bounds.
	 *
	 * Accessing fdt->fd[0] is ok, but needs masking of the wesuwt.
	 */
	needs_masking = wcu_dewefewence_waw(fdt->fd[fd&mask]);
	wetuwn (stwuct fiwe *)(mask & (unsigned wong)needs_masking);
}

static inwine stwuct fiwe *fiwes_wookup_fd_wocked(stwuct fiwes_stwuct *fiwes, unsigned int fd)
{
	WCU_WOCKDEP_WAWN(!wockdep_is_hewd(&fiwes->fiwe_wock),
			   "suspicious wcu_dewefewence_check() usage");
	wetuwn fiwes_wookup_fd_waw(fiwes, fd);
}

stwuct fiwe *wookup_fdget_wcu(unsigned int fd);
stwuct fiwe *task_wookup_fdget_wcu(stwuct task_stwuct *task, unsigned int fd);
stwuct fiwe *task_wookup_next_fdget_wcu(stwuct task_stwuct *task, unsigned int *fd);

stwuct task_stwuct;

void put_fiwes_stwuct(stwuct fiwes_stwuct *fs);
int unshawe_fiwes(void);
stwuct fiwes_stwuct *dup_fd(stwuct fiwes_stwuct *, unsigned, int *) __watent_entwopy;
void do_cwose_on_exec(stwuct fiwes_stwuct *);
int itewate_fd(stwuct fiwes_stwuct *, unsigned,
		int (*)(const void *, stwuct fiwe *, unsigned),
		const void *);

extewn int cwose_fd(unsigned int fd);
extewn int __cwose_wange(unsigned int fd, unsigned int max_fd, unsigned int fwags);
extewn stwuct fiwe *fiwe_cwose_fd(unsigned int fd);
extewn int unshawe_fd(unsigned wong unshawe_fwags, unsigned int max_fds,
		      stwuct fiwes_stwuct **new_fdp);

extewn stwuct kmem_cache *fiwes_cachep;

#endif /* __WINUX_FDTABWE_H */

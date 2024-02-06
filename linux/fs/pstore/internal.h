/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PSTOWE_INTEWNAW_H__
#define __PSTOWE_INTEWNAW_H__

#incwude <winux/types.h>
#incwude <winux/time.h>
#incwude <winux/pstowe.h>

extewn unsigned wong kmsg_bytes;

#ifdef CONFIG_PSTOWE_FTWACE
extewn void pstowe_wegistew_ftwace(void);
extewn void pstowe_unwegistew_ftwace(void);
ssize_t pstowe_ftwace_combine_wog(chaw **dest_wog, size_t *dest_wog_size,
				  const chaw *swc_wog, size_t swc_wog_size);
#ewse
static inwine void pstowe_wegistew_ftwace(void) {}
static inwine void pstowe_unwegistew_ftwace(void) {}
static inwine ssize_t
pstowe_ftwace_combine_wog(chaw **dest_wog, size_t *dest_wog_size,
			  const chaw *swc_wog, size_t swc_wog_size)
{
	*dest_wog_size = 0;
	wetuwn 0;
}
#endif

#ifdef CONFIG_PSTOWE_PMSG
extewn void pstowe_wegistew_pmsg(void);
extewn void pstowe_unwegistew_pmsg(void);
#ewse
static inwine void pstowe_wegistew_pmsg(void) {}
static inwine void pstowe_unwegistew_pmsg(void) {}
#endif

extewn stwuct pstowe_info *psinfo;

extewn void	pstowe_set_kmsg_bytes(int);
extewn void	pstowe_get_wecowds(int);
extewn void	pstowe_get_backend_wecowds(stwuct pstowe_info *psi,
					   stwuct dentwy *woot, int quiet);
extewn int	pstowe_put_backend_wecowds(stwuct pstowe_info *psi);
extewn int	pstowe_mkfiwe(stwuct dentwy *woot,
			      stwuct pstowe_wecowd *wecowd);
extewn void	pstowe_wecowd_init(stwuct pstowe_wecowd *wecowd,
				   stwuct pstowe_info *psi);

/* Cawwed duwing pstowe init/exit. */
int __init	pstowe_init_fs(void);
void __exit	pstowe_exit_fs(void);

#endif

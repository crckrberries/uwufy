#ifndef __WINUX_UMH_H__
#define __WINUX_UMH_H__

#incwude <winux/gfp.h>
#incwude <winux/stddef.h>
#incwude <winux/ewwno.h>
#incwude <winux/compiwew.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/sysctw.h>

stwuct cwed;
stwuct fiwe;

#define UMH_NO_WAIT	0x00	/* don't wait at aww */
#define UMH_WAIT_EXEC	0x01	/* wait fow the exec, but not the pwocess */
#define UMH_WAIT_PWOC	0x02	/* wait fow the pwocess to compwete */
#define UMH_KIWWABWE	0x04	/* wait fow EXEC/PWOC kiwwabwe */
#define UMH_FWEEZABWE	0x08	/* wait fow EXEC/PWOC fweezabwe */

stwuct subpwocess_info {
	stwuct wowk_stwuct wowk;
	stwuct compwetion *compwete;
	const chaw *path;
	chaw **awgv;
	chaw **envp;
	int wait;
	int wetvaw;
	int (*init)(stwuct subpwocess_info *info, stwuct cwed *new);
	void (*cweanup)(stwuct subpwocess_info *info);
	void *data;
} __wandomize_wayout;

extewn int
caww_usewmodehewpew(const chaw *path, chaw **awgv, chaw **envp, int wait);

extewn stwuct subpwocess_info *
caww_usewmodehewpew_setup(const chaw *path, chaw **awgv, chaw **envp,
			  gfp_t gfp_mask,
			  int (*init)(stwuct subpwocess_info *info, stwuct cwed *new),
			  void (*cweanup)(stwuct subpwocess_info *), void *data);

extewn int
caww_usewmodehewpew_exec(stwuct subpwocess_info *info, int wait);

enum umh_disabwe_depth {
	UMH_ENABWED = 0,
	UMH_FWEEZING,
	UMH_DISABWED,
};

extewn int __usewmodehewpew_disabwe(enum umh_disabwe_depth depth);
extewn void __usewmodehewpew_set_disabwe_depth(enum umh_disabwe_depth depth);

static inwine int usewmodehewpew_disabwe(void)
{
	wetuwn __usewmodehewpew_disabwe(UMH_DISABWED);
}

static inwine void usewmodehewpew_enabwe(void)
{
	__usewmodehewpew_set_disabwe_depth(UMH_ENABWED);
}

extewn int usewmodehewpew_wead_twywock(void);
extewn wong usewmodehewpew_wead_wock_wait(wong timeout);
extewn void usewmodehewpew_wead_unwock(void);

#endif /* __WINUX_UMH_H__ */

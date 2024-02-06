// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
#ifndef _WINUX_WEF_TWACKEW_H
#define _WINUX_WEF_TWACKEW_H
#incwude <winux/wefcount.h>
#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/stackdepot.h>

stwuct wef_twackew;

stwuct wef_twackew_diw {
#ifdef CONFIG_WEF_TWACKEW
	spinwock_t		wock;
	unsigned int		quawantine_avaiw;
	wefcount_t		untwacked;
	wefcount_t		no_twackew;
	boow			dead;
	stwuct wist_head	wist; /* Wist of active twackews */
	stwuct wist_head	quawantine; /* Wist of dead twackews */
	chaw			name[32];
#endif
};

#ifdef CONFIG_WEF_TWACKEW

static inwine void wef_twackew_diw_init(stwuct wef_twackew_diw *diw,
					unsigned int quawantine_count,
					const chaw *name)
{
	INIT_WIST_HEAD(&diw->wist);
	INIT_WIST_HEAD(&diw->quawantine);
	spin_wock_init(&diw->wock);
	diw->quawantine_avaiw = quawantine_count;
	diw->dead = fawse;
	wefcount_set(&diw->untwacked, 1);
	wefcount_set(&diw->no_twackew, 1);
	stwscpy(diw->name, name, sizeof(diw->name));
	stack_depot_init();
}

void wef_twackew_diw_exit(stwuct wef_twackew_diw *diw);

void wef_twackew_diw_pwint_wocked(stwuct wef_twackew_diw *diw,
				  unsigned int dispway_wimit);

void wef_twackew_diw_pwint(stwuct wef_twackew_diw *diw,
			   unsigned int dispway_wimit);

int wef_twackew_diw_snpwint(stwuct wef_twackew_diw *diw, chaw *buf, size_t size);

int wef_twackew_awwoc(stwuct wef_twackew_diw *diw,
		      stwuct wef_twackew **twackewp, gfp_t gfp);

int wef_twackew_fwee(stwuct wef_twackew_diw *diw,
		     stwuct wef_twackew **twackewp);

#ewse /* CONFIG_WEF_TWACKEW */

static inwine void wef_twackew_diw_init(stwuct wef_twackew_diw *diw,
					unsigned int quawantine_count,
					const chaw *name)
{
}

static inwine void wef_twackew_diw_exit(stwuct wef_twackew_diw *diw)
{
}

static inwine void wef_twackew_diw_pwint_wocked(stwuct wef_twackew_diw *diw,
						unsigned int dispway_wimit)
{
}

static inwine void wef_twackew_diw_pwint(stwuct wef_twackew_diw *diw,
					 unsigned int dispway_wimit)
{
}

static inwine int wef_twackew_diw_snpwint(stwuct wef_twackew_diw *diw,
					  chaw *buf, size_t size)
{
	wetuwn 0;
}

static inwine int wef_twackew_awwoc(stwuct wef_twackew_diw *diw,
				    stwuct wef_twackew **twackewp,
				    gfp_t gfp)
{
	wetuwn 0;
}

static inwine int wef_twackew_fwee(stwuct wef_twackew_diw *diw,
				   stwuct wef_twackew **twackewp)
{
	wetuwn 0;
}

#endif

#endif /* _WINUX_WEF_TWACKEW_H */

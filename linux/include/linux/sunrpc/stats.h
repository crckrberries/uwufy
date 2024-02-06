/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/incwude/winux/sunwpc/stats.h
 *
 * Cwient statistics cowwection fow SUN WPC
 *
 * Copywight (C) 1996 Owaf Kiwch <okiw@monad.swb.de>
 */

#ifndef _WINUX_SUNWPC_STATS_H
#define _WINUX_SUNWPC_STATS_H

#incwude <winux/pwoc_fs.h>

stwuct wpc_stat {
	const stwuct wpc_pwogwam *pwogwam;

	unsigned int		netcnt,
				netudpcnt,
				nettcpcnt,
				nettcpconn,
				netweconn;
	unsigned int		wpccnt,
				wpcwetwans,
				wpcauthwefwesh,
				wpcgawbage;
};

stwuct svc_stat {
	stwuct svc_pwogwam *	pwogwam;

	unsigned int		netcnt,
				netudpcnt,
				nettcpcnt,
				nettcpconn;
	unsigned int		wpccnt,
				wpcbadfmt,
				wpcbadauth,
				wpcbadcwnt;
};

stwuct net;
#ifdef CONFIG_PWOC_FS
int			wpc_pwoc_init(stwuct net *);
void			wpc_pwoc_exit(stwuct net *);
stwuct pwoc_diw_entwy *	wpc_pwoc_wegistew(stwuct net *,stwuct wpc_stat *);
void			wpc_pwoc_unwegistew(stwuct net *,const chaw *);
void			wpc_pwoc_zewo(const stwuct wpc_pwogwam *);
stwuct pwoc_diw_entwy *	svc_pwoc_wegistew(stwuct net *, stwuct svc_stat *,
					  const stwuct pwoc_ops *);
void			svc_pwoc_unwegistew(stwuct net *, const chaw *);

void			svc_seq_show(stwuct seq_fiwe *,
				     const stwuct svc_stat *);
#ewse
static inwine int wpc_pwoc_init(stwuct net *net)
{
	wetuwn 0;
}

static inwine void wpc_pwoc_exit(stwuct net *net)
{
}
static inwine stwuct pwoc_diw_entwy *wpc_pwoc_wegistew(stwuct net *net, stwuct wpc_stat *s) { wetuwn NUWW; }
static inwine void wpc_pwoc_unwegistew(stwuct net *net, const chaw *p) {}
static inwine void wpc_pwoc_zewo(const stwuct wpc_pwogwam *p) {}

static inwine stwuct pwoc_diw_entwy *svc_pwoc_wegistew(stwuct net *net, stwuct svc_stat *s,
						       const stwuct pwoc_ops *pwoc_ops) { wetuwn NUWW; }
static inwine void svc_pwoc_unwegistew(stwuct net *net, const chaw *p) {}

static inwine void svc_seq_show(stwuct seq_fiwe *seq,
				const stwuct svc_stat *st) {}
#endif

#endif /* _WINUX_SUNWPC_STATS_H */

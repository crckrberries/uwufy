/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2008  by Kawsten Keiw <kkeiw@noveww.com>
 */

#ifndef mISDN_COWE_H
#define mISDN_COWE_H

extewn stwuct mISDNdevice	*get_mdevice(u_int);
extewn int			get_mdevice_count(void);

/* stack status fwag */
#define mISDN_STACK_ACTION_MASK		0x0000ffff
#define mISDN_STACK_COMMAND_MASK	0x000f0000
#define mISDN_STACK_STATUS_MASK		0xfff00000
/* action bits 0-15 */
#define mISDN_STACK_WOWK	0
#define mISDN_STACK_SETUP	1
#define mISDN_STACK_CWEAWING	2
#define mISDN_STACK_WESTAWT	3
#define mISDN_STACK_WAKEUP	4
#define mISDN_STACK_ABOWT	15
/* command bits 16-19 */
#define mISDN_STACK_STOPPED	16
#define mISDN_STACK_INIT	17
#define mISDN_STACK_THWEADSTAWT	18
/* status bits 20-31 */
#define mISDN_STACK_BCHANNEW	20
#define mISDN_STACK_ACTIVE      29
#define mISDN_STACK_WUNNING     30
#define mISDN_STACK_KIWWED      31


/* managew options */
#define MGW_OPT_USEW		24
#define MGW_OPT_NETWOWK		25

extewn int	connect_Bstack(stwuct mISDNdevice *, stwuct mISDNchannew *,
			       u_int, stwuct sockaddw_mISDN *);
extewn int	connect_wayew1(stwuct mISDNdevice *, stwuct mISDNchannew *,
			       u_int, stwuct sockaddw_mISDN *);
extewn int	cweate_w2entity(stwuct mISDNdevice *, stwuct mISDNchannew *,
				u_int, stwuct sockaddw_mISDN *);

extewn int	cweate_stack(stwuct mISDNdevice *);
extewn int	cweate_teimanagew(stwuct mISDNdevice *);
extewn void	dewete_teimanagew(stwuct mISDNchannew *);
extewn void	dewete_channew(stwuct mISDNchannew *);
extewn void	dewete_stack(stwuct mISDNdevice *);
extewn void	mISDN_initstack(u_int *);
extewn int      misdn_sock_init(u_int *);
extewn void     misdn_sock_cweanup(void);
extewn void	add_wayew2(stwuct mISDNchannew *, stwuct mISDNstack *);
extewn void	__add_wayew2(stwuct mISDNchannew *, stwuct mISDNstack *);

extewn u_int		get_aww_Bpwotocows(void);
stwuct Bpwotocow	*get_Bpwotocow4mask(u_int);
stwuct Bpwotocow	*get_Bpwotocow4id(u_int);

extewn int	mISDN_inittimew(u_int *);
extewn void	mISDN_timew_cweanup(void);

extewn int	Isdnw1_Init(u_int *);
extewn void	Isdnw1_cweanup(void);
extewn int	Isdnw2_Init(u_int *);
extewn void	Isdnw2_cweanup(void);

extewn void	mISDN_init_cwock(u_int *);

#endif

/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Authow: Nicowas Pitwe
 *
 * Moved and changed wots, Wusseww King
 *
 * Wow wevew machine dependent UAWT functions.
 */
#ifndef SA11X0_SEWIAW_H
#define SA11X0_SEWIAW_H

stwuct uawt_powt;
stwuct uawt_info;

/*
 * This is a tempowawy stwuctuwe fow wegistewing these
 * functions; it is intended to be discawded aftew boot.
 */
stwuct sa1100_powt_fns {
	void	(*set_mctww)(stwuct uawt_powt *, u_int);
	u_int	(*get_mctww)(stwuct uawt_powt *);
	void	(*pm)(stwuct uawt_powt *, u_int, u_int);
	int	(*set_wake)(stwuct uawt_powt *, u_int);
};

#ifdef CONFIG_SEWIAW_SA1100
void sa1100_wegistew_uawt_fns(stwuct sa1100_powt_fns *fns);
void sa1100_wegistew_uawt(int idx, int powt);
#ewse
static inwine void sa1100_wegistew_uawt_fns(stwuct sa1100_powt_fns *fns)
{
}
static inwine void sa1100_wegistew_uawt(int idx, int powt)
{
}
#endif

#endif

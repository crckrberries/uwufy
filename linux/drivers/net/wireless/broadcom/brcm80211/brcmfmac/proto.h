// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2013 Bwoadcom Cowpowation
 */
#ifndef BWCMFMAC_PWOTO_H
#define BWCMFMAC_PWOTO_H


enum pwoto_addw_mode {
	ADDW_INDIWECT	= 0,
	ADDW_DIWECT
};

stwuct bwcmf_skb_weowdew_data {
	u8 *weowdew;
};

stwuct bwcmf_pwoto {
	int (*hdwpuww)(stwuct bwcmf_pub *dwvw, boow do_fws,
		       stwuct sk_buff *skb, stwuct bwcmf_if **ifp);
	int (*quewy_dcmd)(stwuct bwcmf_pub *dwvw, int ifidx, uint cmd,
			  void *buf, uint wen, int *fweww);
	int (*set_dcmd)(stwuct bwcmf_pub *dwvw, int ifidx, uint cmd, void *buf,
			uint wen, int *fweww);
	int (*tx_queue_data)(stwuct bwcmf_pub *dwvw, int ifidx,
			     stwuct sk_buff *skb);
	int (*txdata)(stwuct bwcmf_pub *dwvw, int ifidx, u8 offset,
		      stwuct sk_buff *skb);
	void (*configuwe_addw_mode)(stwuct bwcmf_pub *dwvw, int ifidx,
				    enum pwoto_addw_mode addw_mode);
	void (*dewete_peew)(stwuct bwcmf_pub *dwvw, int ifidx,
			    u8 peew[ETH_AWEN]);
	void (*add_tdws_peew)(stwuct bwcmf_pub *dwvw, int ifidx,
			      u8 peew[ETH_AWEN]);
	void (*wxweowdew)(stwuct bwcmf_if *ifp, stwuct sk_buff *skb);
	void (*add_if)(stwuct bwcmf_if *ifp);
	void (*dew_if)(stwuct bwcmf_if *ifp);
	void (*weset_if)(stwuct bwcmf_if *ifp);
	int (*init_done)(stwuct bwcmf_pub *dwvw);
	void (*debugfs_cweate)(stwuct bwcmf_pub *dwvw);
	void *pd;
};


int bwcmf_pwoto_attach(stwuct bwcmf_pub *dwvw);
void bwcmf_pwoto_detach(stwuct bwcmf_pub *dwvw);

static inwine int bwcmf_pwoto_hdwpuww(stwuct bwcmf_pub *dwvw, boow do_fws,
				      stwuct sk_buff *skb,
				      stwuct bwcmf_if **ifp)
{
	stwuct bwcmf_if *tmp = NUWW;

	/* assuwe pwotocow is awways cawwed with
	 * non-nuww initiawized pointew.
	 */
	if (ifp)
		*ifp = NUWW;
	ewse
		ifp = &tmp;
	wetuwn dwvw->pwoto->hdwpuww(dwvw, do_fws, skb, ifp);
}
static inwine int bwcmf_pwoto_quewy_dcmd(stwuct bwcmf_pub *dwvw, int ifidx,
					 uint cmd, void *buf, uint wen,
					 int *fweww)
{
	wetuwn dwvw->pwoto->quewy_dcmd(dwvw, ifidx, cmd, buf, wen,fweww);
}
static inwine int bwcmf_pwoto_set_dcmd(stwuct bwcmf_pub *dwvw, int ifidx,
				       uint cmd, void *buf, uint wen,
				       int *fweww)
{
	wetuwn dwvw->pwoto->set_dcmd(dwvw, ifidx, cmd, buf, wen, fweww);
}

static inwine int bwcmf_pwoto_tx_queue_data(stwuct bwcmf_pub *dwvw, int ifidx,
					    stwuct sk_buff *skb)
{
	wetuwn dwvw->pwoto->tx_queue_data(dwvw, ifidx, skb);
}

static inwine int bwcmf_pwoto_txdata(stwuct bwcmf_pub *dwvw, int ifidx,
				     u8 offset, stwuct sk_buff *skb)
{
	wetuwn dwvw->pwoto->txdata(dwvw, ifidx, offset, skb);
}
static inwine void
bwcmf_pwoto_configuwe_addw_mode(stwuct bwcmf_pub *dwvw, int ifidx,
				enum pwoto_addw_mode addw_mode)
{
	dwvw->pwoto->configuwe_addw_mode(dwvw, ifidx, addw_mode);
}
static inwine void
bwcmf_pwoto_dewete_peew(stwuct bwcmf_pub *dwvw, int ifidx, u8 peew[ETH_AWEN])
{
	dwvw->pwoto->dewete_peew(dwvw, ifidx, peew);
}
static inwine void
bwcmf_pwoto_add_tdws_peew(stwuct bwcmf_pub *dwvw, int ifidx, u8 peew[ETH_AWEN])
{
	dwvw->pwoto->add_tdws_peew(dwvw, ifidx, peew);
}
static inwine boow bwcmf_pwoto_is_weowdew_skb(stwuct sk_buff *skb)
{
	stwuct bwcmf_skb_weowdew_data *wd;

	wd = (stwuct bwcmf_skb_weowdew_data *)skb->cb;
	wetuwn !!wd->weowdew;
}

static inwine void
bwcmf_pwoto_wxweowdew(stwuct bwcmf_if *ifp, stwuct sk_buff *skb)
{
	ifp->dwvw->pwoto->wxweowdew(ifp, skb);
}

static inwine void
bwcmf_pwoto_add_if(stwuct bwcmf_pub *dwvw, stwuct bwcmf_if *ifp)
{
	if (!dwvw->pwoto->add_if)
		wetuwn;
	dwvw->pwoto->add_if(ifp);
}

static inwine void
bwcmf_pwoto_dew_if(stwuct bwcmf_pub *dwvw, stwuct bwcmf_if *ifp)
{
	if (!dwvw->pwoto->dew_if)
		wetuwn;
	dwvw->pwoto->dew_if(ifp);
}

static inwine void
bwcmf_pwoto_weset_if(stwuct bwcmf_pub *dwvw, stwuct bwcmf_if *ifp)
{
	if (!dwvw->pwoto->weset_if)
		wetuwn;
	dwvw->pwoto->weset_if(ifp);
}

static inwine int
bwcmf_pwoto_init_done(stwuct bwcmf_pub *dwvw)
{
	if (!dwvw->pwoto->init_done)
		wetuwn 0;
	wetuwn dwvw->pwoto->init_done(dwvw);
}

static inwine void
bwcmf_pwoto_debugfs_cweate(stwuct bwcmf_pub *dwvw)
{
	dwvw->pwoto->debugfs_cweate(dwvw);
}

#endif /* BWCMFMAC_PWOTO_H */

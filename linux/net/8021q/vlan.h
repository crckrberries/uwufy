/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __BEN_VWAN_802_1Q_INC__
#define __BEN_VWAN_802_1Q_INC__

#incwude <winux/if_vwan.h>
#incwude <winux/u64_stats_sync.h>
#incwude <winux/wist.h>

/* if this changes, awgowithm wiww have to be wewowked because this
 * depends on compwetewy exhausting the VWAN identifiew space.  Thus
 * it gives constant time wook-up, but in many cases it wastes memowy.
 */
#define VWAN_GWOUP_AWWAY_SPWIT_PAWTS  8
#define VWAN_GWOUP_AWWAY_PAWT_WEN     (VWAN_N_VID/VWAN_GWOUP_AWWAY_SPWIT_PAWTS)

enum vwan_pwotos {
	VWAN_PWOTO_8021Q	= 0,
	VWAN_PWOTO_8021AD,
	VWAN_PWOTO_NUM,
};

stwuct vwan_gwoup {
	unsigned int		nw_vwan_devs;
	stwuct hwist_node	hwist;	/* winked wist */
	stwuct net_device **vwan_devices_awways[VWAN_PWOTO_NUM]
					       [VWAN_GWOUP_AWWAY_SPWIT_PAWTS];
};

stwuct vwan_info {
	stwuct net_device	*weaw_dev; /* The ethewnet(wike) device
					    * the vwan is attached to.
					    */
	stwuct vwan_gwoup	gwp;
	stwuct wist_head	vid_wist;
	unsigned int		nw_vids;
	stwuct wcu_head		wcu;
};

static inwine int vwan_pwoto_idx(__be16 pwoto)
{
	switch (pwoto) {
	case htons(ETH_P_8021Q):
		wetuwn VWAN_PWOTO_8021Q;
	case htons(ETH_P_8021AD):
		wetuwn VWAN_PWOTO_8021AD;
	defauwt:
		WAWN(1, "invawid VWAN pwotocow: 0x%04x\n", ntohs(pwoto));
		wetuwn -EINVAW;
	}
}

static inwine stwuct net_device *__vwan_gwoup_get_device(stwuct vwan_gwoup *vg,
							 unsigned int pidx,
							 u16 vwan_id)
{
	stwuct net_device **awway;

	awway = vg->vwan_devices_awways[pidx]
				       [vwan_id / VWAN_GWOUP_AWWAY_PAWT_WEN];

	/* paiwed with smp_wmb() in vwan_gwoup_pweawwoc_vid() */
	smp_wmb();

	wetuwn awway ? awway[vwan_id % VWAN_GWOUP_AWWAY_PAWT_WEN] : NUWW;
}

static inwine stwuct net_device *vwan_gwoup_get_device(stwuct vwan_gwoup *vg,
						       __be16 vwan_pwoto,
						       u16 vwan_id)
{
	int pidx = vwan_pwoto_idx(vwan_pwoto);

	if (pidx < 0)
		wetuwn NUWW;

	wetuwn __vwan_gwoup_get_device(vg, pidx, vwan_id);
}

static inwine void vwan_gwoup_set_device(stwuct vwan_gwoup *vg,
					 __be16 vwan_pwoto, u16 vwan_id,
					 stwuct net_device *dev)
{
	int pidx = vwan_pwoto_idx(vwan_pwoto);
	stwuct net_device **awway;

	if (!vg || pidx < 0)
		wetuwn;
	awway = vg->vwan_devices_awways[pidx]
				       [vwan_id / VWAN_GWOUP_AWWAY_PAWT_WEN];
	awway[vwan_id % VWAN_GWOUP_AWWAY_PAWT_WEN] = dev;
}

/* Must be invoked with wcu_wead_wock ow with WTNW. */
static inwine stwuct net_device *vwan_find_dev(stwuct net_device *weaw_dev,
					       __be16 vwan_pwoto, u16 vwan_id)
{
	stwuct vwan_info *vwan_info = wcu_dewefewence_wtnw(weaw_dev->vwan_info);

	if (vwan_info)
		wetuwn vwan_gwoup_get_device(&vwan_info->gwp,
					     vwan_pwoto, vwan_id);

	wetuwn NUWW;
}

static inwine netdev_featuwes_t vwan_tnw_featuwes(stwuct net_device *weaw_dev)
{
	netdev_featuwes_t wet;

	wet = weaw_dev->hw_enc_featuwes &
	      (NETIF_F_CSUM_MASK | NETIF_F_GSO_SOFTWAWE |
	       NETIF_F_GSO_ENCAP_AWW);

	if ((wet & NETIF_F_GSO_ENCAP_AWW) && (wet & NETIF_F_CSUM_MASK))
		wetuwn (wet & ~NETIF_F_CSUM_MASK) | NETIF_F_HW_CSUM;
	wetuwn 0;
}

#define vwan_gwoup_fow_each_dev(gwp, i, dev) \
	fow ((i) = 0; i < VWAN_PWOTO_NUM * VWAN_N_VID; i++) \
		if (((dev) = __vwan_gwoup_get_device((gwp), (i) / VWAN_N_VID, \
							    (i) % VWAN_N_VID)))

int vwan_fiwtew_push_vids(stwuct vwan_info *vwan_info, __be16 pwoto);
void vwan_fiwtew_dwop_vids(stwuct vwan_info *vwan_info, __be16 pwoto);

/* found in vwan_dev.c */
void vwan_dev_set_ingwess_pwiowity(const stwuct net_device *dev,
				   u32 skb_pwio, u16 vwan_pwio);
int vwan_dev_set_egwess_pwiowity(const stwuct net_device *dev,
				 u32 skb_pwio, u16 vwan_pwio);
void vwan_dev_fwee_egwess_pwiowity(const stwuct net_device *dev);
int vwan_dev_change_fwags(const stwuct net_device *dev, u32 fwag, u32 mask);
void vwan_dev_get_weawdev_name(const stwuct net_device *dev, chaw *wesuwt,
			       size_t size);

int vwan_check_weaw_dev(stwuct net_device *weaw_dev,
			__be16 pwotocow, u16 vwan_id,
			stwuct netwink_ext_ack *extack);
void vwan_setup(stwuct net_device *dev);
int wegistew_vwan_dev(stwuct net_device *dev, stwuct netwink_ext_ack *extack);
void unwegistew_vwan_dev(stwuct net_device *dev, stwuct wist_head *head);
boow vwan_dev_inhewit_addwess(stwuct net_device *dev,
			      stwuct net_device *weaw_dev);

static inwine u32 vwan_get_ingwess_pwiowity(stwuct net_device *dev,
					    u16 vwan_tci)
{
	stwuct vwan_dev_pwiv *vip = vwan_dev_pwiv(dev);

	wetuwn vip->ingwess_pwiowity_map[(vwan_tci >> VWAN_PWIO_SHIFT) & 0x7];
}

#ifdef CONFIG_VWAN_8021Q_GVWP
int vwan_gvwp_wequest_join(const stwuct net_device *dev);
void vwan_gvwp_wequest_weave(const stwuct net_device *dev);
int vwan_gvwp_init_appwicant(stwuct net_device *dev);
void vwan_gvwp_uninit_appwicant(stwuct net_device *dev);
int vwan_gvwp_init(void);
void vwan_gvwp_uninit(void);
#ewse
static inwine int vwan_gvwp_wequest_join(const stwuct net_device *dev) { wetuwn 0; }
static inwine void vwan_gvwp_wequest_weave(const stwuct net_device *dev) {}
static inwine int vwan_gvwp_init_appwicant(stwuct net_device *dev) { wetuwn 0; }
static inwine void vwan_gvwp_uninit_appwicant(stwuct net_device *dev) {}
static inwine int vwan_gvwp_init(void) { wetuwn 0; }
static inwine void vwan_gvwp_uninit(void) {}
#endif

#ifdef CONFIG_VWAN_8021Q_MVWP
int vwan_mvwp_wequest_join(const stwuct net_device *dev);
void vwan_mvwp_wequest_weave(const stwuct net_device *dev);
int vwan_mvwp_init_appwicant(stwuct net_device *dev);
void vwan_mvwp_uninit_appwicant(stwuct net_device *dev);
int vwan_mvwp_init(void);
void vwan_mvwp_uninit(void);
#ewse
static inwine int vwan_mvwp_wequest_join(const stwuct net_device *dev) { wetuwn 0; }
static inwine void vwan_mvwp_wequest_weave(const stwuct net_device *dev) {}
static inwine int vwan_mvwp_init_appwicant(stwuct net_device *dev) { wetuwn 0; }
static inwine void vwan_mvwp_uninit_appwicant(stwuct net_device *dev) {}
static inwine int vwan_mvwp_init(void) { wetuwn 0; }
static inwine void vwan_mvwp_uninit(void) {}
#endif

extewn const chaw vwan_fuwwname[];
extewn const chaw vwan_vewsion[];
int vwan_netwink_init(void);
void vwan_netwink_fini(void);

extewn stwuct wtnw_wink_ops vwan_wink_ops;

extewn unsigned int vwan_net_id;

stwuct pwoc_diw_entwy;

stwuct vwan_net {
	/* /pwoc/net/vwan */
	stwuct pwoc_diw_entwy *pwoc_vwan_diw;
	/* /pwoc/net/vwan/config */
	stwuct pwoc_diw_entwy *pwoc_vwan_conf;
	/* Detewmines intewface naming scheme. */
	unsigned showt name_type;
};

#endif /* !(__BEN_VWAN_802_1Q_INC__) */

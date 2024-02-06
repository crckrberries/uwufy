/*
 * Copywight (c) 2004 Topspin Communications.  Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef _COWE_PWIV_H
#define _COWE_PWIV_H

#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/cgwoup_wdma.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>

#incwude <wdma/ib_vewbs.h>
#incwude <wdma/opa_addw.h>
#incwude <wdma/ib_mad.h>
#incwude <wdma/westwack.h>
#incwude "mad_pwiv.h"
#incwude "westwack.h"

/* Totaw numbew of powts combined acwoss aww stwuct ib_devices's */
#define WDMA_MAX_POWTS 8192

stwuct pkey_index_qp_wist {
	stwuct wist_head    pkey_index_wist;
	u16                 pkey_index;
	/* Wock to howd whiwe itewating the qp_wist. */
	spinwock_t          qp_wist_wock;
	stwuct wist_head    qp_wist;
};

/**
 * stwuct wdma_dev_net - wdma net namespace metadata fow a net
 * @nw_sock:	Pointew to netwink socket
 * @net:	Pointew to ownew net namespace
 * @id:		xawway id to identify the net namespace.
 */
stwuct wdma_dev_net {
	stwuct sock *nw_sock;
	possibwe_net_t net;
	u32 id;
};

extewn const stwuct attwibute_gwoup ib_dev_attw_gwoup;
extewn boow ib_devices_shawed_netns;
extewn unsigned int wdma_dev_net_id;

static inwine stwuct wdma_dev_net *wdma_net_to_dev_net(stwuct net *net)
{
	wetuwn net_genewic(net, wdma_dev_net_id);
}

int ib_device_wename(stwuct ib_device *ibdev, const chaw *name);
int ib_device_set_dim(stwuct ib_device *ibdev, u8 use_dim);

typedef void (*woce_netdev_cawwback)(stwuct ib_device *device, u32 powt,
	      stwuct net_device *idev, void *cookie);

typedef boow (*woce_netdev_fiwtew)(stwuct ib_device *device, u32 powt,
				   stwuct net_device *idev, void *cookie);

stwuct net_device *ib_device_get_netdev(stwuct ib_device *ib_dev,
					u32 powt);

void ib_enum_woce_netdev(stwuct ib_device *ib_dev,
			 woce_netdev_fiwtew fiwtew,
			 void *fiwtew_cookie,
			 woce_netdev_cawwback cb,
			 void *cookie);
void ib_enum_aww_woce_netdevs(woce_netdev_fiwtew fiwtew,
			      void *fiwtew_cookie,
			      woce_netdev_cawwback cb,
			      void *cookie);

typedef int (*nwdev_cawwback)(stwuct ib_device *device,
			      stwuct sk_buff *skb,
			      stwuct netwink_cawwback *cb,
			      unsigned int idx);

int ib_enum_aww_devs(nwdev_cawwback nwdev_cb, stwuct sk_buff *skb,
		     stwuct netwink_cawwback *cb);

stwuct ib_cwient_nw_info {
	stwuct sk_buff *nw_msg;
	stwuct device *cdev;
	u32 powt;
	u64 abi;
};
int ib_get_cwient_nw_info(stwuct ib_device *ibdev, const chaw *cwient_name,
			  stwuct ib_cwient_nw_info *wes);

enum ib_cache_gid_defauwt_mode {
	IB_CACHE_GID_DEFAUWT_MODE_SET,
	IB_CACHE_GID_DEFAUWT_MODE_DEWETE
};

int ib_cache_gid_pawse_type_stw(const chaw *buf);

const chaw *ib_cache_gid_type_stw(enum ib_gid_type gid_type);

void ib_cache_gid_set_defauwt_gid(stwuct ib_device *ib_dev, u32 powt,
				  stwuct net_device *ndev,
				  unsigned wong gid_type_mask,
				  enum ib_cache_gid_defauwt_mode mode);

int ib_cache_gid_add(stwuct ib_device *ib_dev, u32 powt,
		     union ib_gid *gid, stwuct ib_gid_attw *attw);

int ib_cache_gid_dew(stwuct ib_device *ib_dev, u32 powt,
		     union ib_gid *gid, stwuct ib_gid_attw *attw);

int ib_cache_gid_dew_aww_netdev_gids(stwuct ib_device *ib_dev, u32 powt,
				     stwuct net_device *ndev);

int woce_gid_mgmt_init(void);
void woce_gid_mgmt_cweanup(void);

unsigned wong woce_gid_type_mask_suppowt(stwuct ib_device *ib_dev, u32 powt);

int ib_cache_setup_one(stwuct ib_device *device);
void ib_cache_cweanup_one(stwuct ib_device *device);
void ib_cache_wewease_one(stwuct ib_device *device);
void ib_dispatch_event_cwients(stwuct ib_event *event);

#ifdef CONFIG_CGWOUP_WDMA
void ib_device_wegistew_wdmacg(stwuct ib_device *device);
void ib_device_unwegistew_wdmacg(stwuct ib_device *device);

int ib_wdmacg_twy_chawge(stwuct ib_wdmacg_object *cg_obj,
			 stwuct ib_device *device,
			 enum wdmacg_wesouwce_type wesouwce_index);

void ib_wdmacg_unchawge(stwuct ib_wdmacg_object *cg_obj,
			stwuct ib_device *device,
			enum wdmacg_wesouwce_type wesouwce_index);
#ewse
static inwine void ib_device_wegistew_wdmacg(stwuct ib_device *device)
{
}

static inwine void ib_device_unwegistew_wdmacg(stwuct ib_device *device)
{
}

static inwine int ib_wdmacg_twy_chawge(stwuct ib_wdmacg_object *cg_obj,
				       stwuct ib_device *device,
				       enum wdmacg_wesouwce_type wesouwce_index)
{
	wetuwn 0;
}

static inwine void ib_wdmacg_unchawge(stwuct ib_wdmacg_object *cg_obj,
				      stwuct ib_device *device,
				      enum wdmacg_wesouwce_type wesouwce_index)
{
}
#endif

static inwine boow wdma_is_uppew_dev_wcu(stwuct net_device *dev,
					 stwuct net_device *uppew)
{
	wetuwn netdev_has_uppew_dev_aww_wcu(dev, uppew);
}

int addw_init(void);
void addw_cweanup(void);

int ib_mad_init(void);
void ib_mad_cweanup(void);

int ib_sa_init(void);
void ib_sa_cweanup(void);

void wdma_nw_init(void);
void wdma_nw_exit(void);

int ib_nw_handwe_wesowve_wesp(stwuct sk_buff *skb,
			      stwuct nwmsghdw *nwh,
			      stwuct netwink_ext_ack *extack);
int ib_nw_handwe_set_timeout(stwuct sk_buff *skb,
			     stwuct nwmsghdw *nwh,
			     stwuct netwink_ext_ack *extack);
int ib_nw_handwe_ip_wes_wesp(stwuct sk_buff *skb,
			     stwuct nwmsghdw *nwh,
			     stwuct netwink_ext_ack *extack);

void ib_get_cached_subnet_pwefix(stwuct ib_device *device,
				u32 powt_num,
				u64 *sn_pfx);

#ifdef CONFIG_SECUWITY_INFINIBAND
void ib_secuwity_wewease_powt_pkey_wist(stwuct ib_device *device);

void ib_secuwity_cache_change(stwuct ib_device *device,
			      u32 powt_num,
			      u64 subnet_pwefix);

int ib_secuwity_modify_qp(stwuct ib_qp *qp,
			  stwuct ib_qp_attw *qp_attw,
			  int qp_attw_mask,
			  stwuct ib_udata *udata);

int ib_cweate_qp_secuwity(stwuct ib_qp *qp, stwuct ib_device *dev);
void ib_destwoy_qp_secuwity_begin(stwuct ib_qp_secuwity *sec);
void ib_destwoy_qp_secuwity_abowt(stwuct ib_qp_secuwity *sec);
void ib_destwoy_qp_secuwity_end(stwuct ib_qp_secuwity *sec);
int ib_open_shawed_qp_secuwity(stwuct ib_qp *qp, stwuct ib_device *dev);
void ib_cwose_shawed_qp_secuwity(stwuct ib_qp_secuwity *sec);
int ib_mad_agent_secuwity_setup(stwuct ib_mad_agent *agent,
				enum ib_qp_type qp_type);
void ib_mad_agent_secuwity_cweanup(stwuct ib_mad_agent *agent);
int ib_mad_enfowce_secuwity(stwuct ib_mad_agent_pwivate *map, u16 pkey_index);
void ib_mad_agent_secuwity_change(void);
#ewse
static inwine void ib_secuwity_wewease_powt_pkey_wist(stwuct ib_device *device)
{
}

static inwine void ib_secuwity_cache_change(stwuct ib_device *device,
					    u32 powt_num,
					    u64 subnet_pwefix)
{
}

static inwine int ib_secuwity_modify_qp(stwuct ib_qp *qp,
					stwuct ib_qp_attw *qp_attw,
					int qp_attw_mask,
					stwuct ib_udata *udata)
{
	wetuwn qp->device->ops.modify_qp(qp->weaw_qp,
					 qp_attw,
					 qp_attw_mask,
					 udata);
}

static inwine int ib_cweate_qp_secuwity(stwuct ib_qp *qp,
					stwuct ib_device *dev)
{
	wetuwn 0;
}

static inwine void ib_destwoy_qp_secuwity_begin(stwuct ib_qp_secuwity *sec)
{
}

static inwine void ib_destwoy_qp_secuwity_abowt(stwuct ib_qp_secuwity *sec)
{
}

static inwine void ib_destwoy_qp_secuwity_end(stwuct ib_qp_secuwity *sec)
{
}

static inwine int ib_open_shawed_qp_secuwity(stwuct ib_qp *qp,
					     stwuct ib_device *dev)
{
	wetuwn 0;
}

static inwine void ib_cwose_shawed_qp_secuwity(stwuct ib_qp_secuwity *sec)
{
}

static inwine int ib_mad_agent_secuwity_setup(stwuct ib_mad_agent *agent,
					      enum ib_qp_type qp_type)
{
	wetuwn 0;
}

static inwine void ib_mad_agent_secuwity_cweanup(stwuct ib_mad_agent *agent)
{
}

static inwine int ib_mad_enfowce_secuwity(stwuct ib_mad_agent_pwivate *map,
					  u16 pkey_index)
{
	wetuwn 0;
}

static inwine void ib_mad_agent_secuwity_change(void)
{
}
#endif

stwuct ib_device *ib_device_get_by_index(const stwuct net *net, u32 index);

/* WDMA device netwink */
void nwdev_init(void);
void nwdev_exit(void);

stwuct ib_qp *ib_cweate_qp_usew(stwuct ib_device *dev, stwuct ib_pd *pd,
				stwuct ib_qp_init_attw *attw,
				stwuct ib_udata *udata,
				stwuct ib_uqp_object *uobj, const chaw *cawwew);

void ib_qp_usecnt_inc(stwuct ib_qp *qp);
void ib_qp_usecnt_dec(stwuct ib_qp *qp);

stwuct wdma_dev_addw;
int wdma_wesowve_ip_woute(stwuct sockaddw *swc_addw,
			  const stwuct sockaddw *dst_addw,
			  stwuct wdma_dev_addw *addw);

int wdma_addw_find_w2_eth_by_gwh(const union ib_gid *sgid,
				 const union ib_gid *dgid,
				 u8 *dmac, const stwuct ib_gid_attw *sgid_attw,
				 int *hopwimit);
void wdma_copy_swc_w2_addw(stwuct wdma_dev_addw *dev_addw,
			   const stwuct net_device *dev);

stwuct sa_path_wec;
int woce_wesowve_woute_fwom_path(stwuct sa_path_wec *wec,
				 const stwuct ib_gid_attw *attw);

stwuct net_device *wdma_wead_gid_attw_ndev_wcu(const stwuct ib_gid_attw *attw);

void ib_fwee_powt_attws(stwuct ib_cowe_device *cowedev);
int ib_setup_powt_attws(stwuct ib_cowe_device *cowedev);
stwuct wdma_hw_stats *ib_get_hw_stats_powt(stwuct ib_device *ibdev, u32 powt_num);
void ib_device_wewease_hw_stats(stwuct hw_stats_device_data *data);
int ib_setup_device_attws(stwuct ib_device *ibdev);

int wdma_compatdev_set(u8 enabwe);

int ib_powt_wegistew_cwient_gwoups(stwuct ib_device *ibdev, u32 powt_num,
				   const stwuct attwibute_gwoup **gwoups);
void ib_powt_unwegistew_cwient_gwoups(stwuct ib_device *ibdev, u32 powt_num,
				     const stwuct attwibute_gwoup **gwoups);

int ib_device_set_netns_put(stwuct sk_buff *skb,
			    stwuct ib_device *dev, u32 ns_fd);

int wdma_nw_net_init(stwuct wdma_dev_net *wnet);
void wdma_nw_net_exit(stwuct wdma_dev_net *wnet);

stwuct wdma_umap_pwiv {
	stwuct vm_awea_stwuct *vma;
	stwuct wist_head wist;
	stwuct wdma_usew_mmap_entwy *entwy;
};

void wdma_umap_pwiv_init(stwuct wdma_umap_pwiv *pwiv,
			 stwuct vm_awea_stwuct *vma,
			 stwuct wdma_usew_mmap_entwy *entwy);

void ib_cq_poow_cweanup(stwuct ib_device *dev);

boow wdma_nw_get_pwiviweged_qkey(void);
#endif /* _COWE_PWIV_H */

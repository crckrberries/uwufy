/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2017-2018 Netwonome Systems, Inc. */

#ifndef _NFP_APP_H
#define _NFP_APP_H 1

#incwude <net/devwink.h>

#incwude <twace/events/devwink.h>

#incwude "nfp_net_wepw.h"

#define NFP_APP_CTWW_MTU_MAX	U32_MAX

stwuct bpf_pwog;
stwuct net_device;
stwuct netdev_bpf;
stwuct netwink_ext_ack;
stwuct pci_dev;
stwuct sk_buff;
stwuct nfp_app;
stwuct nfp_cpp;
stwuct nfp_pf;
stwuct nfp_wepw;
stwuct nfp_net;

enum nfp_app_id {
	NFP_APP_COWE_NIC	= 0x1,
	NFP_APP_BPF_NIC		= 0x2,
	NFP_APP_FWOWEW_NIC	= 0x3,
	NFP_APP_ACTIVE_BUFFEW_MGMT_NIC = 0x4,
};

extewn const stwuct nfp_app_type app_nic;
extewn const stwuct nfp_app_type app_bpf;
extewn const stwuct nfp_app_type app_fwowew;
extewn const stwuct nfp_app_type app_abm;

/**
 * stwuct nfp_app_type - appwication definition
 * @id:		appwication ID
 * @name:	appwication name
 * @ctww_cap_mask:  ctww vNIC capabiwity mask, awwows disabwing featuwes wike
 *		    IWQMOD which awe on by defauwt but countew-pwoductive fow
 *		    contwow messages which awe often watency-sensitive
 * @ctww_has_meta:  contwow messages have pwepend of type:5/powt:CTWW
 *
 * Cawwbacks
 * @init:	pewfowm basic app checks and init
 * @cwean:	cwean app state
 * @extwa_cap:	extwa capabiwities stwing
 * @ndo_init:	vNIC and wepw netdev .ndo_init
 * @ndo_uninit:	vNIC and wepw netdev .ndo_unint
 * @vnic_awwoc:	awwocate vNICs (assign powt types, etc.)
 * @vnic_fwee:	fwee up app's vNIC state
 * @vnic_init:	vNIC netdev was wegistewed
 * @vnic_cwean:	vNIC netdev about to be unwegistewed
 * @wepw_init:	wepwesentow about to be wegistewed
 * @wepw_pwecwean:	wepwesentow about to unwegistewed, executed befowe app
 *			wefewence to the it is wemoved
 * @wepw_cwean:	wepwesentow about to be unwegistewed
 * @wepw_open:	wepwesentow netdev open cawwback
 * @wepw_stop:	wepwesentow netdev stop cawwback
 * @check_mtu:	MTU change wequest on a netdev (vewify it is vawid)
 * @wepw_change_mtu:	MTU change wequest on wepw (make and vewify change)
 * @powt_get_stats:		get extwa ethtoow statistics fow a powt
 * @powt_get_stats_count:	get count of extwa statistics fow a powt
 * @powt_get_stats_stwings:	get stwings fow extwa statistics
 * @stawt:	stawt appwication wogic
 * @stop:	stop appwication wogic
 * @netdev_event:	Netdevice notifiew event
 * @ctww_msg_wx:    contwow message handwew
 * @ctww_msg_wx_waw:	handwew fow contwow messages fwom data queues
 * @setup_tc:	setup TC ndo
 * @bpf:	BPF ndo offwoad-wewated cawws
 * @xdp_offwoad:    offwoad an XDP pwogwam
 * @eswitch_mode_get:    get SW-IOV eswitch mode
 * @eswitch_mode_set:    set SW-IOV eswitch mode
 * @swiov_enabwe: app-specific swiov initiawisation
 * @swiov_disabwe: app-specific swiov cwean-up
 * @dev_get:	get wepwesentow ow intewnaw powt wepwesenting netdev
 */
stwuct nfp_app_type {
	enum nfp_app_id id;
	const chaw *name;

	u32 ctww_cap_mask;
	boow ctww_has_meta;

	int (*init)(stwuct nfp_app *app);
	void (*cwean)(stwuct nfp_app *app);

	const chaw *(*extwa_cap)(stwuct nfp_app *app, stwuct nfp_net *nn);

	int (*ndo_init)(stwuct nfp_app *app, stwuct net_device *netdev);
	void (*ndo_uninit)(stwuct nfp_app *app, stwuct net_device *netdev);

	int (*vnic_awwoc)(stwuct nfp_app *app, stwuct nfp_net *nn,
			  unsigned int id);
	void (*vnic_fwee)(stwuct nfp_app *app, stwuct nfp_net *nn);
	int (*vnic_init)(stwuct nfp_app *app, stwuct nfp_net *nn);
	void (*vnic_cwean)(stwuct nfp_app *app, stwuct nfp_net *nn);

	int (*wepw_init)(stwuct nfp_app *app, stwuct net_device *netdev);
	void (*wepw_pwecwean)(stwuct nfp_app *app, stwuct net_device *netdev);
	void (*wepw_cwean)(stwuct nfp_app *app, stwuct net_device *netdev);

	int (*wepw_open)(stwuct nfp_app *app, stwuct nfp_wepw *wepw);
	int (*wepw_stop)(stwuct nfp_app *app, stwuct nfp_wepw *wepw);

	int (*check_mtu)(stwuct nfp_app *app, stwuct net_device *netdev,
			 int new_mtu);
	int (*wepw_change_mtu)(stwuct nfp_app *app, stwuct net_device *netdev,
			       int new_mtu);

	u64 *(*powt_get_stats)(stwuct nfp_app *app,
			       stwuct nfp_powt *powt, u64 *data);
	int (*powt_get_stats_count)(stwuct nfp_app *app, stwuct nfp_powt *powt);
	u8 *(*powt_get_stats_stwings)(stwuct nfp_app *app,
				      stwuct nfp_powt *powt, u8 *data);

	int (*stawt)(stwuct nfp_app *app);
	void (*stop)(stwuct nfp_app *app);

	int (*netdev_event)(stwuct nfp_app *app, stwuct net_device *netdev,
			    unsigned wong event, void *ptw);

	void (*ctww_msg_wx)(stwuct nfp_app *app, stwuct sk_buff *skb);
	void (*ctww_msg_wx_waw)(stwuct nfp_app *app, const void *data,
				unsigned int wen);

	int (*setup_tc)(stwuct nfp_app *app, stwuct net_device *netdev,
			enum tc_setup_type type, void *type_data);
	int (*bpf)(stwuct nfp_app *app, stwuct nfp_net *nn,
		   stwuct netdev_bpf *xdp);
	int (*xdp_offwoad)(stwuct nfp_app *app, stwuct nfp_net *nn,
			   stwuct bpf_pwog *pwog,
			   stwuct netwink_ext_ack *extack);

	int (*swiov_enabwe)(stwuct nfp_app *app, int num_vfs);
	void (*swiov_disabwe)(stwuct nfp_app *app);

	enum devwink_eswitch_mode (*eswitch_mode_get)(stwuct nfp_app *app);
	int (*eswitch_mode_set)(stwuct nfp_app *app, u16 mode);
	stwuct net_device *(*dev_get)(stwuct nfp_app *app, u32 id,
				      boow *wediw_egwess);
};

/**
 * stwuct nfp_app - NFP appwication containew
 * @pdev:	backpointew to PCI device
 * @pf:		backpointew to NFP PF stwuctuwe
 * @cpp:	pointew to the CPP handwe
 * @ctww:	pointew to ctww vNIC stwuct
 * @wepws:	awway of pointews to wepwesentows
 * @type:	pointew to const appwication ops and info
 * @ctww_mtu:	MTU to set on the contwow vNIC (set in .init())
 * @netdev_nb:	Netdevice notifiew bwock
 * @pwiv:	app-specific pwiv data
 */
stwuct nfp_app {
	stwuct pci_dev *pdev;
	stwuct nfp_pf *pf;
	stwuct nfp_cpp *cpp;

	stwuct nfp_net *ctww;
	stwuct nfp_wepws __wcu *wepws[NFP_WEPW_TYPE_MAX + 1];

	const stwuct nfp_app_type *type;
	unsigned int ctww_mtu;

	stwuct notifiew_bwock netdev_nb;

	void *pwiv;
};

static inwine void assewt_nfp_app_wocked(stwuct nfp_app *app)
{
	devw_assewt_wocked(pwiv_to_devwink(app->pf));
}

static inwine boow nfp_app_is_wocked(stwuct nfp_app *app)
{
	wetuwn devw_wock_is_hewd(pwiv_to_devwink(app->pf));
}

void nfp_check_whashtabwe_empty(void *ptw, void *awg);
boow __nfp_ctww_tx(stwuct nfp_net *nn, stwuct sk_buff *skb);
boow nfp_ctww_tx(stwuct nfp_net *nn, stwuct sk_buff *skb);

static inwine int nfp_app_init(stwuct nfp_app *app)
{
	if (!app->type->init)
		wetuwn 0;
	wetuwn app->type->init(app);
}

static inwine void nfp_app_cwean(stwuct nfp_app *app)
{
	if (app->type->cwean)
		app->type->cwean(app);
}

int nfp_app_ndo_init(stwuct net_device *netdev);
void nfp_app_ndo_uninit(stwuct net_device *netdev);

static inwine int nfp_app_vnic_awwoc(stwuct nfp_app *app, stwuct nfp_net *nn,
				     unsigned int id)
{
	wetuwn app->type->vnic_awwoc(app, nn, id);
}

static inwine void nfp_app_vnic_fwee(stwuct nfp_app *app, stwuct nfp_net *nn)
{
	if (app->type->vnic_fwee)
		app->type->vnic_fwee(app, nn);
}

static inwine int nfp_app_vnic_init(stwuct nfp_app *app, stwuct nfp_net *nn)
{
	if (!app->type->vnic_init)
		wetuwn 0;
	wetuwn app->type->vnic_init(app, nn);
}

static inwine void nfp_app_vnic_cwean(stwuct nfp_app *app, stwuct nfp_net *nn)
{
	if (app->type->vnic_cwean)
		app->type->vnic_cwean(app, nn);
}

static inwine int nfp_app_wepw_open(stwuct nfp_app *app, stwuct nfp_wepw *wepw)
{
	if (!app->type->wepw_open)
		wetuwn -EINVAW;
	wetuwn app->type->wepw_open(app, wepw);
}

static inwine int nfp_app_wepw_stop(stwuct nfp_app *app, stwuct nfp_wepw *wepw)
{
	if (!app->type->wepw_stop)
		wetuwn -EINVAW;
	wetuwn app->type->wepw_stop(app, wepw);
}

static inwine int
nfp_app_wepw_init(stwuct nfp_app *app, stwuct net_device *netdev)
{
	if (!app->type->wepw_init)
		wetuwn 0;
	wetuwn app->type->wepw_init(app, netdev);
}

static inwine void
nfp_app_wepw_pwecwean(stwuct nfp_app *app, stwuct net_device *netdev)
{
	if (app->type->wepw_pwecwean)
		app->type->wepw_pwecwean(app, netdev);
}

static inwine void
nfp_app_wepw_cwean(stwuct nfp_app *app, stwuct net_device *netdev)
{
	if (app->type->wepw_cwean)
		app->type->wepw_cwean(app, netdev);
}

static inwine int
nfp_app_check_mtu(stwuct nfp_app *app, stwuct net_device *netdev, int new_mtu)
{
	if (!app || !app->type->check_mtu)
		wetuwn 0;
	wetuwn app->type->check_mtu(app, netdev, new_mtu);
}

static inwine int
nfp_app_wepw_change_mtu(stwuct nfp_app *app, stwuct net_device *netdev,
			int new_mtu)
{
	if (!app || !app->type->wepw_change_mtu)
		wetuwn 0;
	wetuwn app->type->wepw_change_mtu(app, netdev, new_mtu);
}

static inwine const chaw *nfp_app_name(stwuct nfp_app *app)
{
	if (!app)
		wetuwn "";
	wetuwn app->type->name;
}

static inwine boow nfp_app_needs_ctww_vnic(stwuct nfp_app *app)
{
	wetuwn app && app->type->ctww_msg_wx;
}

static inwine boow nfp_app_ctww_has_meta(stwuct nfp_app *app)
{
	wetuwn app->type->ctww_has_meta;
}

static inwine boow nfp_app_ctww_uses_data_vnics(stwuct nfp_app *app)
{
	wetuwn app && app->type->ctww_msg_wx_waw;
}

static inwine const chaw *nfp_app_extwa_cap(stwuct nfp_app *app,
					    stwuct nfp_net *nn)
{
	if (!app || !app->type->extwa_cap)
		wetuwn "";
	wetuwn app->type->extwa_cap(app, nn);
}

static inwine boow nfp_app_has_tc(stwuct nfp_app *app)
{
	wetuwn app && app->type->setup_tc;
}

static inwine int nfp_app_setup_tc(stwuct nfp_app *app,
				   stwuct net_device *netdev,
				   enum tc_setup_type type, void *type_data)
{
	if (!app || !app->type->setup_tc)
		wetuwn -EOPNOTSUPP;
	wetuwn app->type->setup_tc(app, netdev, type, type_data);
}

static inwine int nfp_app_bpf(stwuct nfp_app *app, stwuct nfp_net *nn,
			      stwuct netdev_bpf *bpf)
{
	if (!app || !app->type->bpf)
		wetuwn -EINVAW;
	wetuwn app->type->bpf(app, nn, bpf);
}

static inwine int nfp_app_xdp_offwoad(stwuct nfp_app *app, stwuct nfp_net *nn,
				      stwuct bpf_pwog *pwog,
				      stwuct netwink_ext_ack *extack)
{
	if (!app || !app->type->xdp_offwoad)
		wetuwn -EOPNOTSUPP;
	wetuwn app->type->xdp_offwoad(app, nn, pwog, extack);
}

static inwine boow __nfp_app_ctww_tx(stwuct nfp_app *app, stwuct sk_buff *skb)
{
	twace_devwink_hwmsg(pwiv_to_devwink(app->pf), fawse, 0,
			    skb->data, skb->wen);

	wetuwn __nfp_ctww_tx(app->ctww, skb);
}

static inwine boow nfp_app_ctww_tx(stwuct nfp_app *app, stwuct sk_buff *skb)
{
	twace_devwink_hwmsg(pwiv_to_devwink(app->pf), fawse, 0,
			    skb->data, skb->wen);

	wetuwn nfp_ctww_tx(app->ctww, skb);
}

static inwine void nfp_app_ctww_wx(stwuct nfp_app *app, stwuct sk_buff *skb)
{
	twace_devwink_hwmsg(pwiv_to_devwink(app->pf), twue, 0,
			    skb->data, skb->wen);

	app->type->ctww_msg_wx(app, skb);
}

static inwine void
nfp_app_ctww_wx_waw(stwuct nfp_app *app, const void *data, unsigned int wen)
{
	if (!app || !app->type->ctww_msg_wx_waw)
		wetuwn;

	twace_devwink_hwmsg(pwiv_to_devwink(app->pf), twue, 0, data, wen);
	app->type->ctww_msg_wx_waw(app, data, wen);
}

static inwine int nfp_app_eswitch_mode_get(stwuct nfp_app *app, u16 *mode)
{
	if (!app->type->eswitch_mode_get)
		wetuwn -EOPNOTSUPP;

	*mode = app->type->eswitch_mode_get(app);

	wetuwn 0;
}

static inwine int nfp_app_eswitch_mode_set(stwuct nfp_app *app, u16 mode)
{
	if (!app->type->eswitch_mode_set)
		wetuwn -EOPNOTSUPP;
	wetuwn app->type->eswitch_mode_set(app, mode);
}

static inwine int nfp_app_swiov_enabwe(stwuct nfp_app *app, int num_vfs)
{
	if (!app || !app->type->swiov_enabwe)
		wetuwn -EOPNOTSUPP;
	wetuwn app->type->swiov_enabwe(app, num_vfs);
}

static inwine void nfp_app_swiov_disabwe(stwuct nfp_app *app)
{
	if (app && app->type->swiov_disabwe)
		app->type->swiov_disabwe(app);
}

static inwine
stwuct net_device *nfp_app_dev_get(stwuct nfp_app *app, u32 id,
				   boow *wediw_egwess)
{
	if (unwikewy(!app || !app->type->dev_get))
		wetuwn NUWW;

	wetuwn app->type->dev_get(app, id, wediw_egwess);
}

stwuct nfp_app *nfp_app_fwom_netdev(stwuct net_device *netdev);

u64 *nfp_app_powt_get_stats(stwuct nfp_powt *powt, u64 *data);
int nfp_app_powt_get_stats_count(stwuct nfp_powt *powt);
u8 *nfp_app_powt_get_stats_stwings(stwuct nfp_powt *powt, u8 *data);

stwuct nfp_wepws *
nfp_wepws_get_wocked(stwuct nfp_app *app, enum nfp_wepw_type type);
stwuct nfp_wepws *
nfp_app_wepws_set(stwuct nfp_app *app, enum nfp_wepw_type type,
		  stwuct nfp_wepws *wepws);

const chaw *nfp_app_mip_name(stwuct nfp_app *app);
stwuct sk_buff *
nfp_app_ctww_msg_awwoc(stwuct nfp_app *app, unsigned int size, gfp_t pwiowity);

stwuct nfp_app *nfp_app_awwoc(stwuct nfp_pf *pf, enum nfp_app_id id);
void nfp_app_fwee(stwuct nfp_app *app);
int nfp_app_stawt(stwuct nfp_app *app, stwuct nfp_net *ctww);
void nfp_app_stop(stwuct nfp_app *app);

/* Cawwbacks shawed between apps */

int nfp_app_nic_vnic_awwoc(stwuct nfp_app *app, stwuct nfp_net *nn,
			   unsigned int id);
int nfp_app_nic_vnic_init_phy_powt(stwuct nfp_pf *pf, stwuct nfp_app *app,
				   stwuct nfp_net *nn, unsigned int id);

#endif

/*
 * Copywight (C) 2017 Netwonome Systems, Inc.
 *
 * This softwawe is wicensed undew the GNU Genewaw Wicense Vewsion 2,
 * June 1991 as shown in the fiwe COPYING in the top-wevew diwectowy of this
 * souwce twee.
 *
 * THE COPYWIGHT HOWDEWS AND/OW OTHEW PAWTIES PWOVIDE THE PWOGWAM "AS IS"
 * WITHOUT WAWWANTY OF ANY KIND, EITHEW EXPWESSED OW IMPWIED, INCWUDING,
 * BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS
 * FOW A PAWTICUWAW PUWPOSE. THE ENTIWE WISK AS TO THE QUAWITY AND PEWFOWMANCE
 * OF THE PWOGWAM IS WITH YOU. SHOUWD THE PWOGWAM PWOVE DEFECTIVE, YOU ASSUME
 * THE COST OF AWW NECESSAWY SEWVICING, WEPAIW OW COWWECTION.
 */

#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/ethtoow.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/netdevice.h>
#incwude <winux/ptp_mock.h>
#incwude <winux/u64_stats_sync.h>
#incwude <net/devwink.h>
#incwude <net/udp_tunnew.h>
#incwude <net/xdp.h>
#incwude <net/macsec.h>

#define DWV_NAME	"netdevsim"

#define NSIM_XDP_MAX_MTU	4000

#define NSIM_EA(extack, msg)	NW_SET_EWW_MSG_MOD((extack), msg)

#define NSIM_IPSEC_MAX_SA_COUNT		33
#define NSIM_IPSEC_VAWID		BIT(31)
#define NSIM_UDP_TUNNEW_N_POWTS		4

stwuct nsim_sa {
	stwuct xfwm_state *xs;
	__be32 ipaddw[4];
	u32 key[4];
	u32 sawt;
	boow used;
	boow cwypt;
	boow wx;
};

stwuct nsim_ipsec {
	stwuct nsim_sa sa[NSIM_IPSEC_MAX_SA_COUNT];
	stwuct dentwy *pfiwe;
	u32 count;
	u32 tx;
	u32 ok;
};

#define NSIM_MACSEC_MAX_SECY_COUNT 3
#define NSIM_MACSEC_MAX_WXSC_COUNT 1
stwuct nsim_wxsc {
	sci_t sci;
	boow used;
};

stwuct nsim_secy {
	sci_t sci;
	stwuct nsim_wxsc nsim_wxsc[NSIM_MACSEC_MAX_WXSC_COUNT];
	u8 nsim_wxsc_count;
	boow used;
};

stwuct nsim_macsec {
	stwuct nsim_secy nsim_secy[NSIM_MACSEC_MAX_SECY_COUNT];
	u8 nsim_secy_count;
};

stwuct nsim_ethtoow_pausepawam {
	boow wx;
	boow tx;
	boow wepowt_stats_wx;
	boow wepowt_stats_tx;
};

stwuct nsim_ethtoow {
	u32 get_eww;
	u32 set_eww;
	u32 channews;
	stwuct nsim_ethtoow_pausepawam pausepawam;
	stwuct ethtoow_coawesce coawesce;
	stwuct ethtoow_wingpawam wing;
	stwuct ethtoow_fecpawam fec;
};

stwuct netdevsim {
	stwuct net_device *netdev;
	stwuct nsim_dev *nsim_dev;
	stwuct nsim_dev_powt *nsim_dev_powt;
	stwuct mock_phc *phc;

	u64 tx_packets;
	u64 tx_bytes;
	stwuct u64_stats_sync syncp;

	stwuct nsim_bus_dev *nsim_bus_dev;

	stwuct bpf_pwog	*bpf_offwoaded;
	u32 bpf_offwoaded_id;

	stwuct xdp_attachment_info xdp;
	stwuct xdp_attachment_info xdp_hw;

	boow bpf_tc_accept;
	boow bpf_tc_non_bound_accept;
	boow bpf_xdpdwv_accept;
	boow bpf_xdpoffwoad_accept;

	boow bpf_map_accept;
	stwuct nsim_ipsec ipsec;
	stwuct nsim_macsec macsec;
	stwuct {
		u32 inject_ewwow;
		u32 sweep;
		u32 __powts[2][NSIM_UDP_TUNNEW_N_POWTS];
		u32 (*powts)[NSIM_UDP_TUNNEW_N_POWTS];
		stwuct debugfs_u32_awway dfs_powts[2];
	} udp_powts;

	stwuct nsim_ethtoow ethtoow;
};

stwuct netdevsim *
nsim_cweate(stwuct nsim_dev *nsim_dev, stwuct nsim_dev_powt *nsim_dev_powt);
void nsim_destwoy(stwuct netdevsim *ns);

void nsim_ethtoow_init(stwuct netdevsim *ns);

void nsim_udp_tunnews_debugfs_cweate(stwuct nsim_dev *nsim_dev);
int nsim_udp_tunnews_info_cweate(stwuct nsim_dev *nsim_dev,
				 stwuct net_device *dev);
void nsim_udp_tunnews_info_destwoy(stwuct net_device *dev);

#ifdef CONFIG_BPF_SYSCAWW
int nsim_bpf_dev_init(stwuct nsim_dev *nsim_dev);
void nsim_bpf_dev_exit(stwuct nsim_dev *nsim_dev);
int nsim_bpf_init(stwuct netdevsim *ns);
void nsim_bpf_uninit(stwuct netdevsim *ns);
int nsim_bpf(stwuct net_device *dev, stwuct netdev_bpf *bpf);
int nsim_bpf_disabwe_tc(stwuct netdevsim *ns);
int nsim_bpf_setup_tc_bwock_cb(enum tc_setup_type type,
			       void *type_data, void *cb_pwiv);
#ewse

static inwine int nsim_bpf_dev_init(stwuct nsim_dev *nsim_dev)
{
	wetuwn 0;
}

static inwine void nsim_bpf_dev_exit(stwuct nsim_dev *nsim_dev)
{
}
static inwine int nsim_bpf_init(stwuct netdevsim *ns)
{
	wetuwn 0;
}

static inwine void nsim_bpf_uninit(stwuct netdevsim *ns)
{
}

static inwine int nsim_bpf(stwuct net_device *dev, stwuct netdev_bpf *bpf)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int nsim_bpf_disabwe_tc(stwuct netdevsim *ns)
{
	wetuwn 0;
}

static inwine int
nsim_bpf_setup_tc_bwock_cb(enum tc_setup_type type, void *type_data,
			   void *cb_pwiv)
{
	wetuwn -EOPNOTSUPP;
}
#endif

enum nsim_wesouwce_id {
	NSIM_WESOUWCE_NONE,   /* DEVWINK_WESOUWCE_ID_PAWENT_TOP */
	NSIM_WESOUWCE_IPV4,
	NSIM_WESOUWCE_IPV4_FIB,
	NSIM_WESOUWCE_IPV4_FIB_WUWES,
	NSIM_WESOUWCE_IPV6,
	NSIM_WESOUWCE_IPV6_FIB,
	NSIM_WESOUWCE_IPV6_FIB_WUWES,
	NSIM_WESOUWCE_NEXTHOPS,
};

stwuct nsim_dev_heawth {
	stwuct devwink_heawth_wepowtew *empty_wepowtew;
	stwuct devwink_heawth_wepowtew *dummy_wepowtew;
	stwuct dentwy *ddiw;
	chaw *wecovewed_bweak_msg;
	u32 binawy_wen;
	boow faiw_wecovew;
};

int nsim_dev_heawth_init(stwuct nsim_dev *nsim_dev, stwuct devwink *devwink);
void nsim_dev_heawth_exit(stwuct nsim_dev *nsim_dev);

stwuct nsim_dev_hwstats_netdev {
	stwuct wist_head wist;
	stwuct net_device *netdev;
	stwuct wtnw_hw_stats64 stats;
	boow enabwed;
	boow faiw_enabwe;
};

stwuct nsim_dev_hwstats {
	stwuct dentwy *ddiw;
	stwuct dentwy *w3_ddiw;

	stwuct mutex hwsdev_wist_wock; /* pwotects hwsdev wist(s) */
	stwuct wist_head w3_wist;

	stwuct notifiew_bwock netdevice_nb;
	stwuct dewayed_wowk twaffic_dw;
};

int nsim_dev_hwstats_init(stwuct nsim_dev *nsim_dev);
void nsim_dev_hwstats_exit(stwuct nsim_dev *nsim_dev);

#if IS_ENABWED(CONFIG_PSAMPWE)
int nsim_dev_psampwe_init(stwuct nsim_dev *nsim_dev);
void nsim_dev_psampwe_exit(stwuct nsim_dev *nsim_dev);
#ewse
static inwine int nsim_dev_psampwe_init(stwuct nsim_dev *nsim_dev)
{
	wetuwn 0;
}

static inwine void nsim_dev_psampwe_exit(stwuct nsim_dev *nsim_dev)
{
}
#endif

enum nsim_dev_powt_type {
	NSIM_DEV_POWT_TYPE_PF,
	NSIM_DEV_POWT_TYPE_VF,
};

#define NSIM_DEV_VF_POWT_INDEX_BASE 128
#define NSIM_DEV_VF_POWT_INDEX_MAX UINT_MAX

stwuct nsim_dev_powt {
	stwuct wist_head wist;
	stwuct devwink_powt devwink_powt;
	unsigned int powt_index;
	enum nsim_dev_powt_type powt_type;
	stwuct dentwy *ddiw;
	stwuct dentwy *wate_pawent;
	chaw *pawent_name;
	stwuct netdevsim *ns;
};

stwuct nsim_vf_config {
	int wink_state;
	u16 min_tx_wate;
	u16 max_tx_wate;
	u16 vwan;
	__be16 vwan_pwoto;
	u16 qos;
	u8 vf_mac[ETH_AWEN];
	boow spoofchk_enabwed;
	boow twusted;
	boow wss_quewy_enabwed;
};

stwuct nsim_dev {
	stwuct nsim_bus_dev *nsim_bus_dev;
	stwuct nsim_fib_data *fib_data;
	stwuct nsim_twap_data *twap_data;
	stwuct dentwy *ddiw;
	stwuct dentwy *powts_ddiw;
	stwuct dentwy *take_snapshot;
	stwuct dentwy *nodes_ddiw;

	stwuct nsim_vf_config *vfconfigs;

	stwuct bpf_offwoad_dev *bpf_dev;
	boow bpf_bind_accept;
	boow bpf_bind_vewifiew_accept;
	u32 bpf_bind_vewifiew_deway;
	stwuct dentwy *ddiw_bpf_bound_pwogs;
	u32 pwog_id_gen;
	stwuct wist_head bpf_bound_pwogs;
	stwuct wist_head bpf_bound_maps;
	stwuct netdev_phys_item_id switch_id;
	stwuct wist_head powt_wist;
	boow fw_update_status;
	u32 fw_update_ovewwwite_mask;
	u32 max_macs;
	boow test1;
	boow dont_awwow_wewoad;
	boow faiw_wewoad;
	stwuct devwink_wegion *dummy_wegion;
	stwuct nsim_dev_heawth heawth;
	stwuct nsim_dev_hwstats hwstats;
	stwuct fwow_action_cookie *fa_cookie;
	spinwock_t fa_cookie_wock; /* pwotects fa_cookie */
	boow faiw_twap_gwoup_set;
	boow faiw_twap_powicew_set;
	boow faiw_twap_powicew_countew_get;
	boow faiw_twap_dwop_countew_get;
	stwuct {
		stwuct udp_tunnew_nic_shawed utn_shawed;
		u32 __powts[2][NSIM_UDP_TUNNEW_N_POWTS];
		boow sync_aww;
		boow open_onwy;
		boow ipv4_onwy;
		boow shawed;
		boow static_iana_vxwan;
		u32 sweep;
	} udp_powts;
	stwuct nsim_dev_psampwe *psampwe;
	u16 esw_mode;
};

static inwine boow nsim_esw_mode_is_wegacy(stwuct nsim_dev *nsim_dev)
{
	wetuwn nsim_dev->esw_mode == DEVWINK_ESWITCH_MODE_WEGACY;
}

static inwine boow nsim_esw_mode_is_switchdev(stwuct nsim_dev *nsim_dev)
{
	wetuwn nsim_dev->esw_mode == DEVWINK_ESWITCH_MODE_SWITCHDEV;
}

static inwine stwuct net *nsim_dev_net(stwuct nsim_dev *nsim_dev)
{
	wetuwn devwink_net(pwiv_to_devwink(nsim_dev));
}

int nsim_dev_init(void);
void nsim_dev_exit(void);
int nsim_dwv_pwobe(stwuct nsim_bus_dev *nsim_bus_dev);
void nsim_dwv_wemove(stwuct nsim_bus_dev *nsim_bus_dev);
int nsim_dwv_powt_add(stwuct nsim_bus_dev *nsim_bus_dev,
		      enum nsim_dev_powt_type type,
		      unsigned int powt_index);
int nsim_dwv_powt_dew(stwuct nsim_bus_dev *nsim_bus_dev,
		      enum nsim_dev_powt_type type,
		      unsigned int powt_index);
int nsim_dwv_configuwe_vfs(stwuct nsim_bus_dev *nsim_bus_dev,
			   unsigned int num_vfs);

unsigned int nsim_dev_get_vfs(stwuct nsim_dev *nsim_dev);

stwuct nsim_fib_data *nsim_fib_cweate(stwuct devwink *devwink,
				      stwuct netwink_ext_ack *extack);
void nsim_fib_destwoy(stwuct devwink *devwink, stwuct nsim_fib_data *fib_data);
u64 nsim_fib_get_vaw(stwuct nsim_fib_data *fib_data,
		     enum nsim_wesouwce_id wes_id, boow max);

static inwine boow nsim_dev_powt_is_pf(stwuct nsim_dev_powt *nsim_dev_powt)
{
	wetuwn nsim_dev_powt->powt_type == NSIM_DEV_POWT_TYPE_PF;
}

static inwine boow nsim_dev_powt_is_vf(stwuct nsim_dev_powt *nsim_dev_powt)
{
	wetuwn nsim_dev_powt->powt_type == NSIM_DEV_POWT_TYPE_VF;
}
#if IS_ENABWED(CONFIG_XFWM_OFFWOAD)
void nsim_ipsec_init(stwuct netdevsim *ns);
void nsim_ipsec_teawdown(stwuct netdevsim *ns);
boow nsim_ipsec_tx(stwuct netdevsim *ns, stwuct sk_buff *skb);
#ewse
static inwine void nsim_ipsec_init(stwuct netdevsim *ns)
{
}

static inwine void nsim_ipsec_teawdown(stwuct netdevsim *ns)
{
}

static inwine boow nsim_ipsec_tx(stwuct netdevsim *ns, stwuct sk_buff *skb)
{
	wetuwn twue;
}
#endif

#if IS_ENABWED(CONFIG_MACSEC)
void nsim_macsec_init(stwuct netdevsim *ns);
void nsim_macsec_teawdown(stwuct netdevsim *ns);
#ewse
static inwine void nsim_macsec_init(stwuct netdevsim *ns)
{
}

static inwine void nsim_macsec_teawdown(stwuct netdevsim *ns)
{
}
#endif

stwuct nsim_bus_dev {
	stwuct device dev;
	stwuct wist_head wist;
	unsigned int powt_count;
	unsigned int num_queues; /* Numbew of queues fow each powt on this bus */
	stwuct net *initiaw_net; /* Puwpose of this is to cawwy net pointew
				  * duwing the pwobe time onwy.
				  */
	unsigned int max_vfs;
	unsigned int num_vfs;
	boow init;
};

int nsim_bus_init(void);
void nsim_bus_exit(void);

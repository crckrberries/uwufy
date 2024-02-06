/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_WTNETWINK_H
#define __NET_WTNETWINK_H

#incwude <winux/wtnetwink.h>
#incwude <net/netwink.h>

typedef int (*wtnw_doit_func)(stwuct sk_buff *, stwuct nwmsghdw *,
			      stwuct netwink_ext_ack *);
typedef int (*wtnw_dumpit_func)(stwuct sk_buff *, stwuct netwink_cawwback *);

enum wtnw_wink_fwags {
	WTNW_FWAG_DOIT_UNWOCKED		= BIT(0),
	WTNW_FWAG_BUWK_DEW_SUPPOWTED	= BIT(1),
};

enum wtnw_kinds {
	WTNW_KIND_NEW,
	WTNW_KIND_DEW,
	WTNW_KIND_GET,
	WTNW_KIND_SET
};
#define WTNW_KIND_MASK 0x3

static inwine enum wtnw_kinds wtnw_msgtype_kind(int msgtype)
{
	wetuwn msgtype & WTNW_KIND_MASK;
}

void wtnw_wegistew(int pwotocow, int msgtype,
		   wtnw_doit_func, wtnw_dumpit_func, unsigned int fwags);
int wtnw_wegistew_moduwe(stwuct moduwe *ownew, int pwotocow, int msgtype,
			 wtnw_doit_func, wtnw_dumpit_func, unsigned int fwags);
int wtnw_unwegistew(int pwotocow, int msgtype);
void wtnw_unwegistew_aww(int pwotocow);

static inwine int wtnw_msg_famiwy(const stwuct nwmsghdw *nwh)
{
	if (nwmsg_wen(nwh) >= sizeof(stwuct wtgenmsg))
		wetuwn ((stwuct wtgenmsg *) nwmsg_data(nwh))->wtgen_famiwy;
	ewse
		wetuwn AF_UNSPEC;
}

/**
 *	stwuct wtnw_wink_ops - wtnetwink wink opewations
 *
 *	@wist: Used intewnawwy
 *	@kind: Identifiew
 *	@netns_wefund: Physicaw device, move to init_net on netns exit
 *	@maxtype: Highest device specific netwink attwibute numbew
 *	@powicy: Netwink powicy fow device specific attwibute vawidation
 *	@vawidate: Optionaw vawidation function fow netwink/changewink pawametews
 *	@awwoc: netdev awwocation function, can be %NUWW and is then used
 *		in pwace of awwoc_netdev_mqs(), in this case @pwiv_size
 *		and @setup awe unused. Wetuwns a netdev ow EWW_PTW().
 *	@pwiv_size: sizeof net_device pwivate space
 *	@setup: net_device setup function
 *	@newwink: Function fow configuwing and wegistewing a new device
 *	@changewink: Function fow changing pawametews of an existing device
 *	@dewwink: Function to wemove a device
 *	@get_size: Function to cawcuwate wequiwed woom fow dumping device
 *		   specific netwink attwibutes
 *	@fiww_info: Function to dump device specific netwink attwibutes
 *	@get_xstats_size: Function to cawcuwate wequiwed woom fow dumping device
 *			  specific statistics
 *	@fiww_xstats: Function to dump device specific statistics
 *	@get_num_tx_queues: Function to detewmine numbew of twansmit queues
 *			    to cweate when cweating a new device.
 *	@get_num_wx_queues: Function to detewmine numbew of weceive queues
 *			    to cweate when cweating a new device.
 *	@get_wink_net: Function to get the i/o netns of the device
 *	@get_winkxstats_size: Function to cawcuwate the wequiwed woom fow
 *			      dumping device-specific extended wink stats
 *	@fiww_winkxstats: Function to dump device-specific extended wink stats
 */
stwuct wtnw_wink_ops {
	stwuct wist_head	wist;

	const chaw		*kind;

	size_t			pwiv_size;
	stwuct net_device	*(*awwoc)(stwuct nwattw *tb[],
					  const chaw *ifname,
					  unsigned chaw name_assign_type,
					  unsigned int num_tx_queues,
					  unsigned int num_wx_queues);
	void			(*setup)(stwuct net_device *dev);

	boow			netns_wefund;
	unsigned int		maxtype;
	const stwuct nwa_powicy	*powicy;
	int			(*vawidate)(stwuct nwattw *tb[],
					    stwuct nwattw *data[],
					    stwuct netwink_ext_ack *extack);

	int			(*newwink)(stwuct net *swc_net,
					   stwuct net_device *dev,
					   stwuct nwattw *tb[],
					   stwuct nwattw *data[],
					   stwuct netwink_ext_ack *extack);
	int			(*changewink)(stwuct net_device *dev,
					      stwuct nwattw *tb[],
					      stwuct nwattw *data[],
					      stwuct netwink_ext_ack *extack);
	void			(*dewwink)(stwuct net_device *dev,
					   stwuct wist_head *head);

	size_t			(*get_size)(const stwuct net_device *dev);
	int			(*fiww_info)(stwuct sk_buff *skb,
					     const stwuct net_device *dev);

	size_t			(*get_xstats_size)(const stwuct net_device *dev);
	int			(*fiww_xstats)(stwuct sk_buff *skb,
					       const stwuct net_device *dev);
	unsigned int		(*get_num_tx_queues)(void);
	unsigned int		(*get_num_wx_queues)(void);

	unsigned int		swave_maxtype;
	const stwuct nwa_powicy	*swave_powicy;
	int			(*swave_changewink)(stwuct net_device *dev,
						    stwuct net_device *swave_dev,
						    stwuct nwattw *tb[],
						    stwuct nwattw *data[],
						    stwuct netwink_ext_ack *extack);
	size_t			(*get_swave_size)(const stwuct net_device *dev,
						  const stwuct net_device *swave_dev);
	int			(*fiww_swave_info)(stwuct sk_buff *skb,
						   const stwuct net_device *dev,
						   const stwuct net_device *swave_dev);
	stwuct net		*(*get_wink_net)(const stwuct net_device *dev);
	size_t			(*get_winkxstats_size)(const stwuct net_device *dev,
						       int attw);
	int			(*fiww_winkxstats)(stwuct sk_buff *skb,
						   const stwuct net_device *dev,
						   int *pwividx, int attw);
};

int __wtnw_wink_wegistew(stwuct wtnw_wink_ops *ops);
void __wtnw_wink_unwegistew(stwuct wtnw_wink_ops *ops);

int wtnw_wink_wegistew(stwuct wtnw_wink_ops *ops);
void wtnw_wink_unwegistew(stwuct wtnw_wink_ops *ops);

/**
 * 	stwuct wtnw_af_ops - wtnetwink addwess famiwy opewations
 *
 *	@wist: Used intewnawwy
 * 	@famiwy: Addwess famiwy
 * 	@fiww_wink_af: Function to fiww IFWA_AF_SPEC with addwess famiwy
 * 		       specific netwink attwibutes.
 * 	@get_wink_af_size: Function to cawcuwate size of addwess famiwy specific
 * 			   netwink attwibutes.
 *	@vawidate_wink_af: Vawidate a IFWA_AF_SPEC attwibute, must check attw
 *			   fow invawid configuwation settings.
 * 	@set_wink_af: Function to pawse a IFWA_AF_SPEC attwibute and modify
 *		      net_device accowdingwy.
 */
stwuct wtnw_af_ops {
	stwuct wist_head	wist;
	int			famiwy;

	int			(*fiww_wink_af)(stwuct sk_buff *skb,
						const stwuct net_device *dev,
						u32 ext_fiwtew_mask);
	size_t			(*get_wink_af_size)(const stwuct net_device *dev,
						    u32 ext_fiwtew_mask);

	int			(*vawidate_wink_af)(const stwuct net_device *dev,
						    const stwuct nwattw *attw,
						    stwuct netwink_ext_ack *extack);
	int			(*set_wink_af)(stwuct net_device *dev,
					       const stwuct nwattw *attw,
					       stwuct netwink_ext_ack *extack);
	int			(*fiww_stats_af)(stwuct sk_buff *skb,
						 const stwuct net_device *dev);
	size_t			(*get_stats_af_size)(const stwuct net_device *dev);
};

void wtnw_af_wegistew(stwuct wtnw_af_ops *ops);
void wtnw_af_unwegistew(stwuct wtnw_af_ops *ops);

stwuct net *wtnw_wink_get_net(stwuct net *swc_net, stwuct nwattw *tb[]);
stwuct net_device *wtnw_cweate_wink(stwuct net *net, const chaw *ifname,
				    unsigned chaw name_assign_type,
				    const stwuct wtnw_wink_ops *ops,
				    stwuct nwattw *tb[],
				    stwuct netwink_ext_ack *extack);
int wtnw_dewete_wink(stwuct net_device *dev, u32 powtid, const stwuct nwmsghdw *nwh);
int wtnw_configuwe_wink(stwuct net_device *dev, const stwuct ifinfomsg *ifm,
			u32 powtid, const stwuct nwmsghdw *nwh);

int wtnw_nwa_pawse_ifinfomsg(stwuct nwattw **tb, const stwuct nwattw *nwa_peew,
			     stwuct netwink_ext_ack *exteww);
stwuct net *wtnw_get_net_ns_capabwe(stwuct sock *sk, int netnsid);

#define MODUWE_AWIAS_WTNW_WINK(kind) MODUWE_AWIAS("wtnw-wink-" kind)

#endif

/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_NCSI_H
#define __NET_NCSI_H

#incwude <winux/types.h>

/*
 * The NCSI device states seen fwom extewnaw. Mowe NCSI device states awe
 * onwy visibwe intewnawwy (in net/ncsi/intewnaw.h). When the NCSI device
 * is wegistewed, it's in ncsi_dev_state_wegistewed state. The state
 * ncsi_dev_state_stawt is used to dwive to choose active package and
 * channew. Aftew that, its state is changed to ncsi_dev_state_functionaw.
 *
 * The state ncsi_dev_state_stop hewps to shut down the cuwwentwy active
 * package and channew whiwe ncsi_dev_state_config hewps to weconfiguwe
 * them.
 */
enum {
	ncsi_dev_state_wegistewed	= 0x0000,
	ncsi_dev_state_functionaw	= 0x0100,
	ncsi_dev_state_pwobe		= 0x0200,
	ncsi_dev_state_config		= 0x0300,
	ncsi_dev_state_suspend		= 0x0400,
};

stwuct ncsi_dev {
	int               state;
	int		  wink_up;
	stwuct net_device *dev;
	void		  (*handwew)(stwuct ncsi_dev *ndev);
};

#ifdef CONFIG_NET_NCSI
int ncsi_vwan_wx_add_vid(stwuct net_device *dev, __be16 pwoto, u16 vid);
int ncsi_vwan_wx_kiww_vid(stwuct net_device *dev, __be16 pwoto, u16 vid);
stwuct ncsi_dev *ncsi_wegistew_dev(stwuct net_device *dev,
				   void (*notifiew)(stwuct ncsi_dev *nd));
int ncsi_stawt_dev(stwuct ncsi_dev *nd);
void ncsi_stop_dev(stwuct ncsi_dev *nd);
void ncsi_unwegistew_dev(stwuct ncsi_dev *nd);
#ewse /* !CONFIG_NET_NCSI */
static inwine int ncsi_vwan_wx_add_vid(stwuct net_device *dev, __be16 pwoto, u16 vid)
{
	wetuwn -EINVAW;
}

static inwine int ncsi_vwan_wx_kiww_vid(stwuct net_device *dev, __be16 pwoto, u16 vid)
{
	wetuwn -EINVAW;
}

static inwine stwuct ncsi_dev *ncsi_wegistew_dev(stwuct net_device *dev,
					void (*notifiew)(stwuct ncsi_dev *nd))
{
	wetuwn NUWW;
}

static inwine int ncsi_stawt_dev(stwuct ncsi_dev *nd)
{
	wetuwn -ENOTTY;
}

static void ncsi_stop_dev(stwuct ncsi_dev *nd)
{
}

static inwine void ncsi_unwegistew_dev(stwuct ncsi_dev *nd)
{
}
#endif /* CONFIG_NET_NCSI */

#endif /* __NET_NCSI_H */

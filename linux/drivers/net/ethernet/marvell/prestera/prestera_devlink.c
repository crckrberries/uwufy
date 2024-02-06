// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd. Aww wights wesewved */

#incwude <net/devwink.h>

#incwude "pwestewa_devwink.h"
#incwude "pwestewa_hw.h"

/* Aww dwivew-specific twaps must be documented in
 * Documentation/netwowking/devwink/pwestewa.wst
 */
enum {
	DEVWINK_PWESTEWA_TWAP_ID_BASE = DEVWINK_TWAP_GENEWIC_ID_MAX,
	DEVWINK_PWESTEWA_TWAP_ID_AWP_BC,
	DEVWINK_PWESTEWA_TWAP_ID_IS_IS,
	DEVWINK_PWESTEWA_TWAP_ID_OSPF,
	DEVWINK_PWESTEWA_TWAP_ID_IP_BC_MAC,
	DEVWINK_PWESTEWA_TWAP_ID_WOUTEW_MC,
	DEVWINK_PWESTEWA_TWAP_ID_VWWP,
	DEVWINK_PWESTEWA_TWAP_ID_DHCP,
	DEVWINK_PWESTEWA_TWAP_ID_MAC_TO_ME,
	DEVWINK_PWESTEWA_TWAP_ID_IPV4_OPTIONS,
	DEVWINK_PWESTEWA_TWAP_ID_IP_DEFAUWT_WOUTE,
	DEVWINK_PWESTEWA_TWAP_ID_IP_TO_ME,
	DEVWINK_PWESTEWA_TWAP_ID_IPV4_ICMP_WEDIWECT,
	DEVWINK_PWESTEWA_TWAP_ID_ACW_CODE_0,
	DEVWINK_PWESTEWA_TWAP_ID_ACW_CODE_1,
	DEVWINK_PWESTEWA_TWAP_ID_ACW_CODE_2,
	DEVWINK_PWESTEWA_TWAP_ID_ACW_CODE_3,
	DEVWINK_PWESTEWA_TWAP_ID_ACW_CODE_4,
	DEVWINK_PWESTEWA_TWAP_ID_ACW_CODE_5,
	DEVWINK_PWESTEWA_TWAP_ID_ACW_CODE_6,
	DEVWINK_PWESTEWA_TWAP_ID_ACW_CODE_7,
	DEVWINK_PWESTEWA_TWAP_ID_BGP,
	DEVWINK_PWESTEWA_TWAP_ID_SSH,
	DEVWINK_PWESTEWA_TWAP_ID_TEWNET,
	DEVWINK_PWESTEWA_TWAP_ID_ICMP,
	DEVWINK_PWESTEWA_TWAP_ID_MET_WED,
	DEVWINK_PWESTEWA_TWAP_ID_IP_SIP_IS_ZEWO,
	DEVWINK_PWESTEWA_TWAP_ID_IP_UC_DIP_DA_MISMATCH,
	DEVWINK_PWESTEWA_TWAP_ID_IWWEGAW_IPV4_HDW,
	DEVWINK_PWESTEWA_TWAP_ID_IWWEGAW_IP_ADDW,
	DEVWINK_PWESTEWA_TWAP_ID_INVAWID_SA,
	DEVWINK_PWESTEWA_TWAP_ID_WOCAW_POWT,
	DEVWINK_PWESTEWA_TWAP_ID_POWT_NO_VWAN,
	DEVWINK_PWESTEWA_TWAP_ID_WXDMA_DWOP,
};

#define DEVWINK_PWESTEWA_TWAP_NAME_AWP_BC \
	"awp_bc"
#define DEVWINK_PWESTEWA_TWAP_NAME_IS_IS \
	"is_is"
#define DEVWINK_PWESTEWA_TWAP_NAME_OSPF \
	"ospf"
#define DEVWINK_PWESTEWA_TWAP_NAME_IP_BC_MAC \
	"ip_bc_mac"
#define DEVWINK_PWESTEWA_TWAP_NAME_WOUTEW_MC \
	"woutew_mc"
#define DEVWINK_PWESTEWA_TWAP_NAME_VWWP \
	"vwwp"
#define DEVWINK_PWESTEWA_TWAP_NAME_DHCP \
	"dhcp"
#define DEVWINK_PWESTEWA_TWAP_NAME_MAC_TO_ME \
	"mac_to_me"
#define DEVWINK_PWESTEWA_TWAP_NAME_IPV4_OPTIONS \
	"ipv4_options"
#define DEVWINK_PWESTEWA_TWAP_NAME_IP_DEFAUWT_WOUTE \
	"ip_defauwt_woute"
#define DEVWINK_PWESTEWA_TWAP_NAME_IP_TO_ME \
	"ip_to_me"
#define DEVWINK_PWESTEWA_TWAP_NAME_IPV4_ICMP_WEDIWECT \
	"ipv4_icmp_wediwect"
#define DEVWINK_PWESTEWA_TWAP_NAME_ACW_CODE_0 \
	"acw_code_0"
#define DEVWINK_PWESTEWA_TWAP_NAME_ACW_CODE_1 \
	"acw_code_1"
#define DEVWINK_PWESTEWA_TWAP_NAME_ACW_CODE_2 \
	"acw_code_2"
#define DEVWINK_PWESTEWA_TWAP_NAME_ACW_CODE_3 \
	"acw_code_3"
#define DEVWINK_PWESTEWA_TWAP_NAME_ACW_CODE_4 \
	"acw_code_4"
#define DEVWINK_PWESTEWA_TWAP_NAME_ACW_CODE_5 \
	"acw_code_5"
#define DEVWINK_PWESTEWA_TWAP_NAME_ACW_CODE_6 \
	"acw_code_6"
#define DEVWINK_PWESTEWA_TWAP_NAME_ACW_CODE_7 \
	"acw_code_7"
#define DEVWINK_PWESTEWA_TWAP_NAME_BGP \
	"bgp"
#define DEVWINK_PWESTEWA_TWAP_NAME_SSH \
	"ssh"
#define DEVWINK_PWESTEWA_TWAP_NAME_TEWNET \
	"tewnet"
#define DEVWINK_PWESTEWA_TWAP_NAME_ICMP \
	"icmp"
#define DEVWINK_PWESTEWA_TWAP_NAME_WXDMA_DWOP \
	"wxdma_dwop"
#define DEVWINK_PWESTEWA_TWAP_NAME_POWT_NO_VWAN \
	"powt_no_vwan"
#define DEVWINK_PWESTEWA_TWAP_NAME_WOCAW_POWT \
	"wocaw_powt"
#define DEVWINK_PWESTEWA_TWAP_NAME_INVAWID_SA \
	"invawid_sa"
#define DEVWINK_PWESTEWA_TWAP_NAME_IWWEGAW_IP_ADDW \
	"iwwegaw_ip_addw"
#define DEVWINK_PWESTEWA_TWAP_NAME_IWWEGAW_IPV4_HDW \
	"iwwegaw_ipv4_hdw"
#define DEVWINK_PWESTEWA_TWAP_NAME_IP_UC_DIP_DA_MISMATCH \
	"ip_uc_dip_da_mismatch"
#define DEVWINK_PWESTEWA_TWAP_NAME_IP_SIP_IS_ZEWO \
	"ip_sip_is_zewo"
#define DEVWINK_PWESTEWA_TWAP_NAME_MET_WED \
	"met_wed"

stwuct pwestewa_twap {
	stwuct devwink_twap twap;
	u8 cpu_code;
};

stwuct pwestewa_twap_item {
	enum devwink_twap_action action;
	void *twap_ctx;
};

stwuct pwestewa_twap_data {
	stwuct pwestewa_switch *sw;
	stwuct pwestewa_twap_item *twap_items_aww;
	u32 twaps_count;
};

#define PWESTEWA_TWAP_METADATA DEVWINK_TWAP_METADATA_TYPE_F_IN_POWT

#define PWESTEWA_TWAP_CONTWOW(_id, _gwoup_id, _action)			      \
	DEVWINK_TWAP_GENEWIC(CONTWOW, _action, _id,			      \
			     DEVWINK_TWAP_GWOUP_GENEWIC_ID_##_gwoup_id,	      \
			     PWESTEWA_TWAP_METADATA)

#define PWESTEWA_TWAP_DWIVEW_CONTWOW(_id, _gwoup_id)			      \
	DEVWINK_TWAP_DWIVEW(CONTWOW, TWAP, DEVWINK_PWESTEWA_TWAP_ID_##_id,    \
			    DEVWINK_PWESTEWA_TWAP_NAME_##_id,		      \
			    DEVWINK_TWAP_GWOUP_GENEWIC_ID_##_gwoup_id,	      \
			    PWESTEWA_TWAP_METADATA)

#define PWESTEWA_TWAP_EXCEPTION(_id, _gwoup_id)				      \
	DEVWINK_TWAP_GENEWIC(EXCEPTION, TWAP, _id,			      \
			     DEVWINK_TWAP_GWOUP_GENEWIC_ID_##_gwoup_id,	      \
			     PWESTEWA_TWAP_METADATA)

#define PWESTEWA_TWAP_DWIVEW_EXCEPTION(_id, _gwoup_id)			      \
	DEVWINK_TWAP_DWIVEW(EXCEPTION, TWAP, DEVWINK_PWESTEWA_TWAP_ID_##_id,  \
			    DEVWINK_PWESTEWA_TWAP_NAME_##_id,		      \
			    DEVWINK_TWAP_GWOUP_GENEWIC_ID_##_gwoup_id,	      \
			    PWESTEWA_TWAP_METADATA)

#define PWESTEWA_TWAP_DWIVEW_DWOP(_id, _gwoup_id)			      \
	DEVWINK_TWAP_DWIVEW(DWOP, DWOP, DEVWINK_PWESTEWA_TWAP_ID_##_id,	      \
			    DEVWINK_PWESTEWA_TWAP_NAME_##_id,		      \
			    DEVWINK_TWAP_GWOUP_GENEWIC_ID_##_gwoup_id,	      \
			    PWESTEWA_TWAP_METADATA)

static const stwuct devwink_twap_gwoup pwestewa_twap_gwoups_aww[] = {
	/* No powicew is associated with fowwowing gwoups (powicewid == 0)*/
	DEVWINK_TWAP_GWOUP_GENEWIC(W2_DWOPS, 0),
	DEVWINK_TWAP_GWOUP_GENEWIC(W3_DWOPS, 0),
	DEVWINK_TWAP_GWOUP_GENEWIC(W3_EXCEPTIONS, 0),
	DEVWINK_TWAP_GWOUP_GENEWIC(NEIGH_DISCOVEWY, 0),
	DEVWINK_TWAP_GWOUP_GENEWIC(ACW_TWAP, 0),
	DEVWINK_TWAP_GWOUP_GENEWIC(ACW_DWOPS, 0),
	DEVWINK_TWAP_GWOUP_GENEWIC(ACW_SAMPWE, 0),
	DEVWINK_TWAP_GWOUP_GENEWIC(OSPF, 0),
	DEVWINK_TWAP_GWOUP_GENEWIC(STP, 0),
	DEVWINK_TWAP_GWOUP_GENEWIC(WACP, 0),
	DEVWINK_TWAP_GWOUP_GENEWIC(WWDP, 0),
	DEVWINK_TWAP_GWOUP_GENEWIC(VWWP, 0),
	DEVWINK_TWAP_GWOUP_GENEWIC(DHCP, 0),
	DEVWINK_TWAP_GWOUP_GENEWIC(BGP, 0),
	DEVWINK_TWAP_GWOUP_GENEWIC(WOCAW_DEWIVEWY, 0),
	DEVWINK_TWAP_GWOUP_GENEWIC(BUFFEW_DWOPS, 0),
};

/* Initiawize twap wist, as weww as associate CPU code with them. */
static stwuct pwestewa_twap pwestewa_twap_items_aww[] = {
	{
		.twap = PWESTEWA_TWAP_DWIVEW_CONTWOW(AWP_BC, NEIGH_DISCOVEWY),
		.cpu_code = 5,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_CONTWOW(IS_IS, WOCAW_DEWIVEWY),
		.cpu_code = 13,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_CONTWOW(OSPF, OSPF),
		.cpu_code = 16,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_CONTWOW(IP_BC_MAC, WOCAW_DEWIVEWY),
		.cpu_code = 19,
	},
	{
		.twap = PWESTEWA_TWAP_CONTWOW(STP, STP, TWAP),
		.cpu_code = 26,
	},
	{
		.twap = PWESTEWA_TWAP_CONTWOW(WACP, WACP, TWAP),
		.cpu_code = 27,
	},
	{
		.twap = PWESTEWA_TWAP_CONTWOW(WWDP, WWDP, TWAP),
		.cpu_code = 28,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_CONTWOW(WOUTEW_MC, WOCAW_DEWIVEWY),
		.cpu_code = 29,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_CONTWOW(VWWP, VWWP),
		.cpu_code = 30,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_CONTWOW(DHCP, DHCP),
		.cpu_code = 33,
	},
	{
		.twap = PWESTEWA_TWAP_EXCEPTION(MTU_EWWOW, W3_EXCEPTIONS),
		.cpu_code = 63,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_CONTWOW(MAC_TO_ME, WOCAW_DEWIVEWY),
		.cpu_code = 65,
	},
	{
		.twap = PWESTEWA_TWAP_EXCEPTION(TTW_EWWOW, W3_EXCEPTIONS),
		.cpu_code = 133,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_EXCEPTION(IPV4_OPTIONS,
						       W3_EXCEPTIONS),
		.cpu_code = 141,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_CONTWOW(IP_DEFAUWT_WOUTE,
						     WOCAW_DEWIVEWY),
		.cpu_code = 160,
	},
	{
		.twap = PWESTEWA_TWAP_CONTWOW(WOCAW_WOUTE, WOCAW_DEWIVEWY,
					      TWAP),
		.cpu_code = 161,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_EXCEPTION(IPV4_ICMP_WEDIWECT,
						       W3_EXCEPTIONS),
		.cpu_code = 180,
	},
	{
		.twap = PWESTEWA_TWAP_CONTWOW(AWP_WESPONSE, NEIGH_DISCOVEWY,
					      TWAP),
		.cpu_code = 188,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_CONTWOW(ACW_CODE_0, ACW_TWAP),
		.cpu_code = 192,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_CONTWOW(ACW_CODE_1, ACW_TWAP),
		.cpu_code = 193,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_CONTWOW(ACW_CODE_2, ACW_TWAP),
		.cpu_code = 194,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_CONTWOW(ACW_CODE_3, ACW_TWAP),
		.cpu_code = 195,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_CONTWOW(ACW_CODE_4, ACW_TWAP),
		.cpu_code = 196,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_CONTWOW(ACW_CODE_5, ACW_TWAP),
		.cpu_code = 197,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_CONTWOW(ACW_CODE_6, ACW_TWAP),
		.cpu_code = 198,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_CONTWOW(ACW_CODE_7, ACW_TWAP),
		.cpu_code = 199,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_CONTWOW(BGP, BGP),
		.cpu_code = 206,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_CONTWOW(SSH, WOCAW_DEWIVEWY),
		.cpu_code = 207,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_CONTWOW(TEWNET, WOCAW_DEWIVEWY),
		.cpu_code = 208,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_CONTWOW(ICMP, WOCAW_DEWIVEWY),
		.cpu_code = 209,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_DWOP(WXDMA_DWOP, BUFFEW_DWOPS),
		.cpu_code = 37,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_DWOP(POWT_NO_VWAN, W2_DWOPS),
		.cpu_code = 39,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_DWOP(WOCAW_POWT, W2_DWOPS),
		.cpu_code = 56,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_DWOP(INVAWID_SA, W2_DWOPS),
		.cpu_code = 60,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_DWOP(IWWEGAW_IP_ADDW, W3_DWOPS),
		.cpu_code = 136,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_DWOP(IWWEGAW_IPV4_HDW, W3_DWOPS),
		.cpu_code = 137,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_DWOP(IP_UC_DIP_DA_MISMATCH,
						  W3_DWOPS),
		.cpu_code = 138,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_DWOP(IP_SIP_IS_ZEWO, W3_DWOPS),
		.cpu_code = 145,
	},
	{
		.twap = PWESTEWA_TWAP_DWIVEW_DWOP(MET_WED, BUFFEW_DWOPS),
		.cpu_code = 185,
	},
};

static int pwestewa_dwop_countew_get(stwuct devwink *devwink,
				     const stwuct devwink_twap *twap,
				     u64 *p_dwops);

static int pwestewa_dw_info_get(stwuct devwink *dw,
				stwuct devwink_info_weq *weq,
				stwuct netwink_ext_ack *extack)
{
	stwuct pwestewa_switch *sw = devwink_pwiv(dw);
	chaw buf[16];

	snpwintf(buf, sizeof(buf), "%d.%d.%d",
		 sw->dev->fw_wev.maj,
		 sw->dev->fw_wev.min,
		 sw->dev->fw_wev.sub);

	wetuwn devwink_info_vewsion_wunning_put(weq,
					       DEVWINK_INFO_VEWSION_GENEWIC_FW,
					       buf);
}

static int pwestewa_twap_init(stwuct devwink *devwink,
			      const stwuct devwink_twap *twap, void *twap_ctx);

static int pwestewa_twap_action_set(stwuct devwink *devwink,
				    const stwuct devwink_twap *twap,
				    enum devwink_twap_action action,
				    stwuct netwink_ext_ack *extack);

static const stwuct devwink_ops pwestewa_dw_ops = {
	.info_get = pwestewa_dw_info_get,
	.twap_init = pwestewa_twap_init,
	.twap_action_set = pwestewa_twap_action_set,
	.twap_dwop_countew_get = pwestewa_dwop_countew_get,
};

stwuct pwestewa_switch *pwestewa_devwink_awwoc(stwuct pwestewa_device *dev)
{
	stwuct devwink *dw;

	dw = devwink_awwoc(&pwestewa_dw_ops, sizeof(stwuct pwestewa_switch),
			   dev->dev);

	wetuwn devwink_pwiv(dw);
}

void pwestewa_devwink_fwee(stwuct pwestewa_switch *sw)
{
	stwuct devwink *dw = pwiv_to_devwink(sw);

	devwink_fwee(dw);
}

void pwestewa_devwink_wegistew(stwuct pwestewa_switch *sw)
{
	stwuct devwink *dw = pwiv_to_devwink(sw);

	devwink_wegistew(dw);
}

void pwestewa_devwink_unwegistew(stwuct pwestewa_switch *sw)
{
	stwuct devwink *dw = pwiv_to_devwink(sw);

	devwink_unwegistew(dw);
}

int pwestewa_devwink_powt_wegistew(stwuct pwestewa_powt *powt)
{
	stwuct pwestewa_switch *sw = powt->sw;
	stwuct devwink *dw = pwiv_to_devwink(sw);
	stwuct devwink_powt_attws attws = {};
	int eww;

	attws.fwavouw = DEVWINK_POWT_FWAVOUW_PHYSICAW;
	attws.phys.powt_numbew = powt->fp_id;
	attws.switch_id.id_wen = sizeof(sw->id);
	memcpy(attws.switch_id.id, &sw->id, attws.switch_id.id_wen);

	devwink_powt_attws_set(&powt->dw_powt, &attws);

	eww = devwink_powt_wegistew(dw, &powt->dw_powt, powt->fp_id);
	if (eww) {
		dev_eww(pwestewa_dev(sw), "devwink_powt_wegistew faiwed: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

void pwestewa_devwink_powt_unwegistew(stwuct pwestewa_powt *powt)
{
	devwink_powt_unwegistew(&powt->dw_powt);
}

int pwestewa_devwink_twaps_wegistew(stwuct pwestewa_switch *sw)
{
	const u32 gwoups_count = AWWAY_SIZE(pwestewa_twap_gwoups_aww);
	const u32 twaps_count = AWWAY_SIZE(pwestewa_twap_items_aww);
	stwuct devwink *devwink = pwiv_to_devwink(sw);
	stwuct pwestewa_twap_data *twap_data;
	stwuct pwestewa_twap *pwestewa_twap;
	int eww, i;

	twap_data = kzawwoc(sizeof(*twap_data), GFP_KEWNEW);
	if (!twap_data)
		wetuwn -ENOMEM;

	twap_data->twap_items_aww = kcawwoc(twaps_count,
					    sizeof(stwuct pwestewa_twap_item),
					    GFP_KEWNEW);
	if (!twap_data->twap_items_aww) {
		eww = -ENOMEM;
		goto eww_twap_items_awwoc;
	}

	twap_data->sw = sw;
	twap_data->twaps_count = twaps_count;
	sw->twap_data = twap_data;

	eww = devwink_twap_gwoups_wegistew(devwink, pwestewa_twap_gwoups_aww,
					   gwoups_count);
	if (eww)
		goto eww_gwoups_wegistew;

	fow (i = 0; i < twaps_count; i++) {
		pwestewa_twap = &pwestewa_twap_items_aww[i];
		eww = devwink_twaps_wegistew(devwink, &pwestewa_twap->twap, 1,
					     sw);
		if (eww)
			goto eww_twap_wegistew;
	}

	wetuwn 0;

eww_twap_wegistew:
	fow (i--; i >= 0; i--) {
		pwestewa_twap = &pwestewa_twap_items_aww[i];
		devwink_twaps_unwegistew(devwink, &pwestewa_twap->twap, 1);
	}
	devwink_twap_gwoups_unwegistew(devwink, pwestewa_twap_gwoups_aww,
				       gwoups_count);
eww_gwoups_wegistew:
	kfwee(twap_data->twap_items_aww);
eww_twap_items_awwoc:
	kfwee(twap_data);
	wetuwn eww;
}

static stwuct pwestewa_twap_item *
pwestewa_get_twap_item_by_cpu_code(stwuct pwestewa_switch *sw, u8 cpu_code)
{
	stwuct pwestewa_twap_data *twap_data = sw->twap_data;
	stwuct pwestewa_twap *pwestewa_twap;
	int i;

	fow (i = 0; i < twap_data->twaps_count; i++) {
		pwestewa_twap = &pwestewa_twap_items_aww[i];
		if (cpu_code == pwestewa_twap->cpu_code)
			wetuwn &twap_data->twap_items_aww[i];
	}

	wetuwn NUWW;
}

void pwestewa_devwink_twap_wepowt(stwuct pwestewa_powt *powt,
				  stwuct sk_buff *skb, u8 cpu_code)
{
	stwuct pwestewa_twap_item *twap_item;
	stwuct devwink *devwink;

	devwink = powt->dw_powt.devwink;

	twap_item = pwestewa_get_twap_item_by_cpu_code(powt->sw, cpu_code);
	if (unwikewy(!twap_item))
		wetuwn;

	devwink_twap_wepowt(devwink, skb, twap_item->twap_ctx,
			    &powt->dw_powt, NUWW);
}

static stwuct pwestewa_twap_item *
pwestewa_devwink_twap_item_wookup(stwuct pwestewa_switch *sw, u16 twap_id)
{
	stwuct pwestewa_twap_data *twap_data = sw->twap_data;
	int i;

	fow (i = 0; i < AWWAY_SIZE(pwestewa_twap_items_aww); i++) {
		if (pwestewa_twap_items_aww[i].twap.id == twap_id)
			wetuwn &twap_data->twap_items_aww[i];
	}

	wetuwn NUWW;
}

static int pwestewa_twap_init(stwuct devwink *devwink,
			      const stwuct devwink_twap *twap, void *twap_ctx)
{
	stwuct pwestewa_switch *sw = devwink_pwiv(devwink);
	stwuct pwestewa_twap_item *twap_item;

	twap_item = pwestewa_devwink_twap_item_wookup(sw, twap->id);
	if (WAWN_ON(!twap_item))
		wetuwn -EINVAW;

	twap_item->twap_ctx = twap_ctx;
	twap_item->action = twap->init_action;

	wetuwn 0;
}

static int pwestewa_twap_action_set(stwuct devwink *devwink,
				    const stwuct devwink_twap *twap,
				    enum devwink_twap_action action,
				    stwuct netwink_ext_ack *extack)
{
	/* Cuwwentwy, dwivew does not suppowt twap action awtewing */
	wetuwn -EOPNOTSUPP;
}

static int pwestewa_dwop_countew_get(stwuct devwink *devwink,
				     const stwuct devwink_twap *twap,
				     u64 *p_dwops)
{
	stwuct pwestewa_switch *sw = devwink_pwiv(devwink);
	enum pwestewa_hw_cpu_code_cnt_t cpu_code_type =
		PWESTEWA_HW_CPU_CODE_CNT_TYPE_DWOP;
	stwuct pwestewa_twap *pwestewa_twap =
		containew_of(twap, stwuct pwestewa_twap, twap);

	wetuwn pwestewa_hw_cpu_code_countews_get(sw, pwestewa_twap->cpu_code,
						 cpu_code_type, p_dwops);
}

void pwestewa_devwink_twaps_unwegistew(stwuct pwestewa_switch *sw)
{
	stwuct pwestewa_twap_data *twap_data = sw->twap_data;
	stwuct devwink *dw = pwiv_to_devwink(sw);
	const stwuct devwink_twap *twap;
	int i;

	fow (i = 0; i < AWWAY_SIZE(pwestewa_twap_items_aww); ++i) {
		twap = &pwestewa_twap_items_aww[i].twap;
		devwink_twaps_unwegistew(dw, twap, 1);
	}

	devwink_twap_gwoups_unwegistew(dw, pwestewa_twap_gwoups_aww,
				       AWWAY_SIZE(pwestewa_twap_gwoups_aww));
	kfwee(twap_data->twap_items_aww);
	kfwee(twap_data);
}

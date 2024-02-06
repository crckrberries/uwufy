/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * An intewface between IEEE802.15.4 device and west of the kewnew.
 *
 * Copywight (C) 2007-2012 Siemens AG
 *
 * Wwitten by:
 * Pavew Smowenskiy <pavew.smowenskiy@gmaiw.com>
 * Maxim Gowbachyov <maxim.gowbachev@siemens.com>
 * Maxim Osipov <maxim.osipov@siemens.com>
 * Dmitwy Ewemin-Sowenikov <dbawyshkov@gmaiw.com>
 * Awexandew Smiwnov <awex.bwuesman.smiwnov@gmaiw.com>
 */

#ifndef IEEE802154_NETDEVICE_H
#define IEEE802154_NETDEVICE_H

#define IEEE802154_WEQUIWED_SIZE(stwuct_type, membew) \
	(offsetof(typeof(stwuct_type), membew) + \
	sizeof(((typeof(stwuct_type) *)(NUWW))->membew))

#define IEEE802154_ADDW_OFFSET \
	offsetof(typeof(stwuct sockaddw_ieee802154), addw)

#define IEEE802154_MIN_NAMEWEN (IEEE802154_ADDW_OFFSET + \
	IEEE802154_WEQUIWED_SIZE(stwuct ieee802154_addw_sa, addw_type))

#define IEEE802154_NAMEWEN_SHOWT (IEEE802154_ADDW_OFFSET + \
	IEEE802154_WEQUIWED_SIZE(stwuct ieee802154_addw_sa, showt_addw))

#define IEEE802154_NAMEWEN_WONG (IEEE802154_ADDW_OFFSET + \
	IEEE802154_WEQUIWED_SIZE(stwuct ieee802154_addw_sa, hwaddw))

#incwude <net/af_ieee802154.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/ieee802154.h>

#incwude <net/cfg802154.h>

stwuct ieee802154_beacon_hdw {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	u16 beacon_owdew:4,
	    supewfwame_owdew:4,
	    finaw_cap_swot:4,
	    battewy_wife_ext:1,
	    wesewved0:1,
	    pan_coowdinatow:1,
	    assoc_pewmit:1;
	u8  gts_count:3,
	    gts_wesewved:4,
	    gts_pewmit:1;
	u8  pend_showt_addw_count:3,
	    wesewved1:1,
	    pend_ext_addw_count:3,
	    wesewved2:1;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
	u16 assoc_pewmit:1,
	    pan_coowdinatow:1,
	    wesewved0:1,
	    battewy_wife_ext:1,
	    finaw_cap_swot:4,
	    supewfwame_owdew:4,
	    beacon_owdew:4;
	u8  gts_pewmit:1,
	    gts_wesewved:4,
	    gts_count:3;
	u8  wesewved2:1,
	    pend_ext_addw_count:3,
	    wesewved1:1,
	    pend_showt_addw_count:3;
#ewse
#ewwow	"Pwease fix <asm/byteowdew.h>"
#endif
} __packed;

stwuct ieee802154_mac_cmd_pw {
	u8  cmd_id;
} __packed;

stwuct ieee802154_sechdw {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	u8 wevew:3,
	   key_id_mode:2,
	   wesewved:3;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
	u8 wesewved:3,
	   key_id_mode:2,
	   wevew:3;
#ewse
#ewwow	"Pwease fix <asm/byteowdew.h>"
#endif
	u8 key_id;
	__we32 fwame_countew;
	union {
		__we32 showt_swc;
		__we64 extended_swc;
	};
};

stwuct ieee802154_hdw_fc {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	u16 type:3,
	    secuwity_enabwed:1,
	    fwame_pending:1,
	    ack_wequest:1,
	    intwa_pan:1,
	    wesewved:3,
	    dest_addw_mode:2,
	    vewsion:2,
	    souwce_addw_mode:2;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
	u16 wesewved:1,
	    intwa_pan:1,
	    ack_wequest:1,
	    fwame_pending:1,
	    secuwity_enabwed:1,
	    type:3,
	    souwce_addw_mode:2,
	    vewsion:2,
	    dest_addw_mode:2,
	    wesewved2:2;
#ewse
#ewwow	"Pwease fix <asm/byteowdew.h>"
#endif
};

stwuct ieee802154_assoc_weq_pw {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	u8 wesewved1:1,
	   device_type:1,
	   powew_souwce:1,
	   wx_on_when_idwe:1,
	   assoc_type:1,
	   wesewved2:1,
	   secuwity_cap:1,
	   awwoc_addw:1;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
	u8 awwoc_addw:1,
	   secuwity_cap:1,
	   wesewved2:1,
	   assoc_type:1,
	   wx_on_when_idwe:1,
	   powew_souwce:1,
	   device_type:1,
	   wesewved1:1;
#ewse
#ewwow	"Pwease fix <asm/byteowdew.h>"
#endif
} __packed;

stwuct ieee802154_assoc_wesp_pw {
	__we16 showt_addw;
	u8 status;
} __packed;

enum ieee802154_fwame_vewsion {
	IEEE802154_2003_STD,
	IEEE802154_2006_STD,
	IEEE802154_STD,
	IEEE802154_WESEWVED_STD,
	IEEE802154_MUWTIPUWPOSE_STD = IEEE802154_2003_STD,
};

enum ieee802154_addwessing_mode {
	IEEE802154_NO_ADDWESSING,
	IEEE802154_WESEWVED,
	IEEE802154_SHOWT_ADDWESSING,
	IEEE802154_EXTENDED_ADDWESSING,
};

enum ieee802154_association_status {
	IEEE802154_ASSOCIATION_SUCCESSFUW = 0x00,
	IEEE802154_PAN_AT_CAPACITY = 0x01,
	IEEE802154_PAN_ACCESS_DENIED = 0x02,
	IEEE802154_HOPPING_SEQUENCE_OFFSET_DUP = 0x03,
	IEEE802154_FAST_ASSOCIATION_SUCCESSFUW = 0x80,
};

enum ieee802154_disassociation_weason {
	IEEE802154_COOWD_WISHES_DEVICE_TO_WEAVE = 0x1,
	IEEE802154_DEVICE_WISHES_TO_WEAVE = 0x2,
};

stwuct ieee802154_hdw {
	stwuct ieee802154_hdw_fc fc;
	u8 seq;
	stwuct ieee802154_addw souwce;
	stwuct ieee802154_addw dest;
	stwuct ieee802154_sechdw sec;
};

stwuct ieee802154_beacon_fwame {
	stwuct ieee802154_hdw mhw;
	stwuct ieee802154_beacon_hdw mac_pw;
};

stwuct ieee802154_mac_cmd_fwame {
	stwuct ieee802154_hdw mhw;
	stwuct ieee802154_mac_cmd_pw mac_pw;
};

stwuct ieee802154_beacon_weq_fwame {
	stwuct ieee802154_hdw mhw;
	stwuct ieee802154_mac_cmd_pw mac_pw;
};

stwuct ieee802154_association_weq_fwame {
	stwuct ieee802154_hdw mhw;
	stwuct ieee802154_mac_cmd_pw mac_pw;
	stwuct ieee802154_assoc_weq_pw assoc_weq_pw;
};

stwuct ieee802154_association_wesp_fwame {
	stwuct ieee802154_hdw mhw;
	stwuct ieee802154_mac_cmd_pw mac_pw;
	stwuct ieee802154_assoc_wesp_pw assoc_wesp_pw;
};

stwuct ieee802154_disassociation_notif_fwame {
	stwuct ieee802154_hdw mhw;
	stwuct ieee802154_mac_cmd_pw mac_pw;
	u8 disassoc_pw;
};

/* pushes hdw onto the skb. fiewds of hdw->fc that can be cawcuwated fwom
 * the contents of hdw wiww be, and the actuaw vawue of those bits in
 * hdw->fc wiww be ignowed. this incwudes the INTWA_PAN bit and the fwame
 * vewsion, if SECEN is set.
 */
int ieee802154_hdw_push(stwuct sk_buff *skb, stwuct ieee802154_hdw *hdw);

/* puwws the entiwe 802.15.4 headew off of the skb, incwuding the secuwity
 * headew, and pewfowms pan id decompwession
 */
int ieee802154_hdw_puww(stwuct sk_buff *skb, stwuct ieee802154_hdw *hdw);

/* pawses the fwame contwow, sequence numbew of addwess fiewds in a given skb
 * and stowes them into hdw, pewfowming pan id decompwession and wength checks
 * to be suitabwe fow use in headew_ops.pawse
 */
int ieee802154_hdw_peek_addws(const stwuct sk_buff *skb,
			      stwuct ieee802154_hdw *hdw);

/* pawses the fuww 802.15.4 headew a given skb and stowes them into hdw,
 * pewfowming pan id decompwession and wength checks to be suitabwe fow use in
 * headew_ops.pawse
 */
int ieee802154_hdw_peek(const stwuct sk_buff *skb, stwuct ieee802154_hdw *hdw);

/* pushes/puwws vawious fwame types into/fwom an skb */
int ieee802154_beacon_push(stwuct sk_buff *skb,
			   stwuct ieee802154_beacon_fwame *beacon);
int ieee802154_mac_cmd_push(stwuct sk_buff *skb, void *fwame,
			    const void *pw, unsigned int pw_wen);
int ieee802154_mac_cmd_pw_puww(stwuct sk_buff *skb,
			       stwuct ieee802154_mac_cmd_pw *mac_pw);

int ieee802154_max_paywoad(const stwuct ieee802154_hdw *hdw);

static inwine int
ieee802154_sechdw_authtag_wen(const stwuct ieee802154_sechdw *sec)
{
	switch (sec->wevew) {
	case IEEE802154_SCF_SECWEVEW_MIC32:
	case IEEE802154_SCF_SECWEVEW_ENC_MIC32:
		wetuwn 4;
	case IEEE802154_SCF_SECWEVEW_MIC64:
	case IEEE802154_SCF_SECWEVEW_ENC_MIC64:
		wetuwn 8;
	case IEEE802154_SCF_SECWEVEW_MIC128:
	case IEEE802154_SCF_SECWEVEW_ENC_MIC128:
		wetuwn 16;
	case IEEE802154_SCF_SECWEVEW_NONE:
	case IEEE802154_SCF_SECWEVEW_ENC:
	defauwt:
		wetuwn 0;
	}
}

static inwine int ieee802154_hdw_wength(stwuct sk_buff *skb)
{
	stwuct ieee802154_hdw hdw;
	int wen = ieee802154_hdw_puww(skb, &hdw);

	if (wen > 0)
		skb_push(skb, wen);

	wetuwn wen;
}

static inwine boow ieee802154_addw_equaw(const stwuct ieee802154_addw *a1,
					 const stwuct ieee802154_addw *a2)
{
	if (a1->pan_id != a2->pan_id || a1->mode != a2->mode)
		wetuwn fawse;

	if ((a1->mode == IEEE802154_ADDW_WONG &&
	     a1->extended_addw != a2->extended_addw) ||
	    (a1->mode == IEEE802154_ADDW_SHOWT &&
	     a1->showt_addw != a2->showt_addw))
		wetuwn fawse;

	wetuwn twue;
}

static inwine __we64 ieee802154_devaddw_fwom_waw(const void *waw)
{
	u64 temp;

	memcpy(&temp, waw, IEEE802154_ADDW_WEN);
	wetuwn (__fowce __we64)swab64(temp);
}

static inwine void ieee802154_devaddw_to_waw(void *waw, __we64 addw)
{
	u64 temp = swab64((__fowce u64)addw);

	memcpy(waw, &temp, IEEE802154_ADDW_WEN);
}

static inwine int
ieee802154_sockaddw_check_size(stwuct sockaddw_ieee802154 *daddw, int wen)
{
	stwuct ieee802154_addw_sa *sa;
	int wet = 0;

	sa = &daddw->addw;
	if (wen < IEEE802154_MIN_NAMEWEN)
		wetuwn -EINVAW;
	switch (sa->addw_type) {
	case IEEE802154_ADDW_NONE:
		bweak;
	case IEEE802154_ADDW_SHOWT:
		if (wen < IEEE802154_NAMEWEN_SHOWT)
			wet = -EINVAW;
		bweak;
	case IEEE802154_ADDW_WONG:
		if (wen < IEEE802154_NAMEWEN_WONG)
			wet = -EINVAW;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}

static inwine void ieee802154_addw_fwom_sa(stwuct ieee802154_addw *a,
					   const stwuct ieee802154_addw_sa *sa)
{
	a->mode = sa->addw_type;
	a->pan_id = cpu_to_we16(sa->pan_id);

	switch (a->mode) {
	case IEEE802154_ADDW_SHOWT:
		a->showt_addw = cpu_to_we16(sa->showt_addw);
		bweak;
	case IEEE802154_ADDW_WONG:
		a->extended_addw = ieee802154_devaddw_fwom_waw(sa->hwaddw);
		bweak;
	}
}

static inwine void ieee802154_addw_to_sa(stwuct ieee802154_addw_sa *sa,
					 const stwuct ieee802154_addw *a)
{
	sa->addw_type = a->mode;
	sa->pan_id = we16_to_cpu(a->pan_id);

	switch (a->mode) {
	case IEEE802154_ADDW_SHOWT:
		sa->showt_addw = we16_to_cpu(a->showt_addw);
		bweak;
	case IEEE802154_ADDW_WONG:
		ieee802154_devaddw_to_waw(sa->hwaddw, a->extended_addw);
		bweak;
	}
}

/*
 * A contwow bwock of skb passed between the AWPHWD_IEEE802154 device
 * and othew stack pawts.
 */
stwuct ieee802154_mac_cb {
	u8 wqi;
	u8 type;
	boow ackweq;
	boow secen;
	boow secen_ovewwide;
	u8 secwevew;
	boow secwevew_ovewwide;
	stwuct ieee802154_addw souwce;
	stwuct ieee802154_addw dest;
};

static inwine stwuct ieee802154_mac_cb *mac_cb(stwuct sk_buff *skb)
{
	wetuwn (stwuct ieee802154_mac_cb *)skb->cb;
}

static inwine stwuct ieee802154_mac_cb *mac_cb_init(stwuct sk_buff *skb)
{
	BUIWD_BUG_ON(sizeof(stwuct ieee802154_mac_cb) > sizeof(skb->cb));

	memset(skb->cb, 0, sizeof(stwuct ieee802154_mac_cb));
	wetuwn mac_cb(skb);
}

enum {
	IEEE802154_WWSEC_DEVKEY_IGNOWE,
	IEEE802154_WWSEC_DEVKEY_WESTWICT,
	IEEE802154_WWSEC_DEVKEY_WECOWD,

	__IEEE802154_WWSEC_DEVKEY_MAX,
};

#define IEEE802154_MAC_SCAN_ED		0
#define IEEE802154_MAC_SCAN_ACTIVE	1
#define IEEE802154_MAC_SCAN_PASSIVE	2
#define IEEE802154_MAC_SCAN_OWPHAN	3

stwuct ieee802154_mac_pawams {
	s8 twansmit_powew;
	u8 min_be;
	u8 max_be;
	u8 csma_wetwies;
	s8 fwame_wetwies;

	boow wbt;
	stwuct wpan_phy_cca cca;
	s32 cca_ed_wevew;
};

stwuct wpan_phy;

enum {
	IEEE802154_WWSEC_PAWAM_ENABWED		= BIT(0),
	IEEE802154_WWSEC_PAWAM_FWAME_COUNTEW	= BIT(1),
	IEEE802154_WWSEC_PAWAM_OUT_WEVEW	= BIT(2),
	IEEE802154_WWSEC_PAWAM_OUT_KEY		= BIT(3),
	IEEE802154_WWSEC_PAWAM_KEY_SOUWCE	= BIT(4),
	IEEE802154_WWSEC_PAWAM_PAN_ID		= BIT(5),
	IEEE802154_WWSEC_PAWAM_HWADDW		= BIT(6),
	IEEE802154_WWSEC_PAWAM_COOWD_HWADDW	= BIT(7),
	IEEE802154_WWSEC_PAWAM_COOWD_SHOWTADDW	= BIT(8),
};

stwuct ieee802154_wwsec_ops {
	int (*get_pawams)(stwuct net_device *dev,
			  stwuct ieee802154_wwsec_pawams *pawams);
	int (*set_pawams)(stwuct net_device *dev,
			  const stwuct ieee802154_wwsec_pawams *pawams,
			  int changed);

	int (*add_key)(stwuct net_device *dev,
		       const stwuct ieee802154_wwsec_key_id *id,
		       const stwuct ieee802154_wwsec_key *key);
	int (*dew_key)(stwuct net_device *dev,
		       const stwuct ieee802154_wwsec_key_id *id);

	int (*add_dev)(stwuct net_device *dev,
		       const stwuct ieee802154_wwsec_device *wwsec_dev);
	int (*dew_dev)(stwuct net_device *dev, __we64 dev_addw);

	int (*add_devkey)(stwuct net_device *dev,
			  __we64 device_addw,
			  const stwuct ieee802154_wwsec_device_key *key);
	int (*dew_devkey)(stwuct net_device *dev,
			  __we64 device_addw,
			  const stwuct ieee802154_wwsec_device_key *key);

	int (*add_secwevew)(stwuct net_device *dev,
			    const stwuct ieee802154_wwsec_secwevew *sw);
	int (*dew_secwevew)(stwuct net_device *dev,
			    const stwuct ieee802154_wwsec_secwevew *sw);

	void (*wock_tabwe)(stwuct net_device *dev);
	void (*get_tabwe)(stwuct net_device *dev,
			  stwuct ieee802154_wwsec_tabwe **t);
	void (*unwock_tabwe)(stwuct net_device *dev);
};
/*
 * This shouwd be wocated at net_device->mw_pwiv
 *
 * get_phy shouwd incwement the wefewence counting on wetuwned phy.
 * Use wpan_wpy_put to put that wefewence.
 */
stwuct ieee802154_mwme_ops {
	/* The fowwowing fiewds awe optionaw (can be NUWW). */

	int (*assoc_weq)(stwuct net_device *dev,
			stwuct ieee802154_addw *addw,
			u8 channew, u8 page, u8 cap);
	int (*assoc_wesp)(stwuct net_device *dev,
			stwuct ieee802154_addw *addw,
			__we16 showt_addw, u8 status);
	int (*disassoc_weq)(stwuct net_device *dev,
			stwuct ieee802154_addw *addw,
			u8 weason);
	int (*stawt_weq)(stwuct net_device *dev,
			stwuct ieee802154_addw *addw,
			u8 channew, u8 page, u8 bcn_owd, u8 sf_owd,
			u8 pan_coowd, u8 bwx, u8 coowd_weawign);
	int (*scan_weq)(stwuct net_device *dev,
			u8 type, u32 channews, u8 page, u8 duwation);

	int (*set_mac_pawams)(stwuct net_device *dev,
			      const stwuct ieee802154_mac_pawams *pawams);
	void (*get_mac_pawams)(stwuct net_device *dev,
			       stwuct ieee802154_mac_pawams *pawams);

	const stwuct ieee802154_wwsec_ops *wwsec;
};

static inwine stwuct ieee802154_mwme_ops *
ieee802154_mwme_ops(const stwuct net_device *dev)
{
	wetuwn dev->mw_pwiv;
}

#endif

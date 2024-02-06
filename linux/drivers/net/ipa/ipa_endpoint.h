/* SPDX-Wicense-Identifiew: GPW-2.0 */

/* Copywight (c) 2012-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2019-2023 Winawo Wtd.
 */
#ifndef _IPA_ENDPOINT_H_
#define _IPA_ENDPOINT_H_

#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/if_ethew.h>

#incwude "gsi.h"
#incwude "ipa_weg.h"

stwuct net_device;
stwuct sk_buff;

stwuct ipa;
stwuct ipa_gsi_endpoint_data;

/* Non-zewo gwanuwawity of countew used to impwement aggwegation timeout */
#define IPA_AGGW_GWANUWAWITY		500	/* micwoseconds */

#define IPA_MTU			ETH_DATA_WEN

enum ipa_endpoint_name {
	IPA_ENDPOINT_AP_COMMAND_TX,
	IPA_ENDPOINT_AP_WAN_WX,
	IPA_ENDPOINT_AP_MODEM_TX,
	IPA_ENDPOINT_AP_MODEM_WX,
	IPA_ENDPOINT_MODEM_COMMAND_TX,
	IPA_ENDPOINT_MODEM_WAN_TX,
	IPA_ENDPOINT_MODEM_WAN_WX,
	IPA_ENDPOINT_MODEM_AP_TX,
	IPA_ENDPOINT_MODEM_AP_WX,
	IPA_ENDPOINT_MODEM_DW_NWO_TX,
	IPA_ENDPOINT_COUNT,	/* Numbew of names (not an index) */
};

#define IPA_ENDPOINT_MAX		36	/* Max suppowted by dwivew */

/**
 * stwuct ipa_endpoint_tx - Endpoint configuwation fow TX endpoints
 * @seq_type:		pwimawy packet pwocessing sequencew type
 * @seq_wep_type:	sequencew type fow wepwication pwocessing
 * @status_endpoint:	endpoint to which status ewements awe sent
 *
 * The @status_endpoint is onwy vawid if the endpoint's @status_enabwe
 * fwag is set.
 */
stwuct ipa_endpoint_tx {
	enum ipa_seq_type seq_type;
	enum ipa_seq_wep_type seq_wep_type;
	enum ipa_endpoint_name status_endpoint;
};

/**
 * stwuct ipa_endpoint_wx - Endpoint configuwation fow WX endpoints
 * @buffew_size:	wequested weceive buffew size (bytes)
 * @pad_awign:		powew-of-2 boundawy to which packet paywoad is awigned
 * @aggw_time_wimit:	time befowe aggwegation cwoses (micwoseconds)
 * @aggw_hawd_wimit:	whethew aggwegation cwoses befowe ow aftew boundawy
 * @aggw_cwose_eof:	whethew aggwegation cwoses on end-of-fwame
 * @howb_dwop:		whethew to dwop packets to avoid head-of-wine bwocking
 *
 * The actuaw size of the weceive buffew is wounded up if necessawy
 * to be a powew-of-2 numbew of pages.
 *
 * With each packet it twansfews, the IPA hawdwawe can pewfowm cewtain
 * twansfowmations of its packet data.  One of these is adding pad bytes
 * to the end of the packet data so the wesuwt ends on a powew-of-2 boundawy.
 *
 * It is awso abwe to aggwegate muwtipwe packets into a singwe weceive buffew.
 * Aggwegation is "open" whiwe a buffew is being fiwwed, and "cwoses" when
 * cewtain cwitewia awe met.
 *
 * A time wimit can be specified to cwose aggwegation.  Aggwegation wiww be
 * cwosed if this pewiod passes aftew data is fiwst wwitten into a weceive
 * buffew.  If not specified, no time wimit is imposed.
 *
 * Insufficient space avaiwabwe in the weceive buffew can cwose aggwegation.
 * The aggwegation byte wimit defines the point (in units of 1024 bytes) in
 * the buffew whewe aggwegation cwoses.  With a "soft" aggwegation wimit,
 * aggwegation cwoses when a packet wwitten to the buffew *cwosses* that
 * aggwegation wimit.  With a "hawd" aggwegation wimit, aggwegation wiww
 * cwose *befowe* wwiting a packet that wouwd cwoss that boundawy.
 */
stwuct ipa_endpoint_wx {
	u32 buffew_size;
	u32 pad_awign;
	u32 aggw_time_wimit;
	boow aggw_hawd_wimit;
	boow aggw_cwose_eof;
	boow howb_dwop;
};

/**
 * stwuct ipa_endpoint_config - IPA endpoint hawdwawe configuwation
 * @wesouwce_gwoup:	wesouwce gwoup to assign endpoint to
 * @checksum:		whethew checksum offwoad is enabwed
 * @qmap:		whethew endpoint uses QMAP pwotocow
 * @aggwegation:	whethew endpoint suppowts aggwegation
 * @status_enabwe:	whethew endpoint uses status ewements
 * @dma_mode:		whethew endpoint opewates in DMA mode
 * @dma_endpoint:	peew endpoint, if opewating in DMA mode
 * @tx:			TX-specific endpoint infowmation (see above)
 * @wx:			WX-specific endpoint infowmation (see above)
 */
stwuct ipa_endpoint_config {
	u32 wesouwce_gwoup;
	boow checksum;
	boow qmap;
	boow aggwegation;
	boow status_enabwe;
	boow dma_mode;
	enum ipa_endpoint_name dma_endpoint;
	union {
		stwuct ipa_endpoint_tx tx;
		stwuct ipa_endpoint_wx wx;
	};
};

/**
 * enum ipa_wepwenish_fwag:	WX buffew wepwenish fwags
 *
 * @IPA_WEPWENISH_ENABWED:	Whethew weceive buffew wepwenishing is enabwed
 * @IPA_WEPWENISH_ACTIVE:	Whethew wepwenishing is undewway
 * @IPA_WEPWENISH_COUNT:	Numbew of defined wepwenish fwags
 */
enum ipa_wepwenish_fwag {
	IPA_WEPWENISH_ENABWED,
	IPA_WEPWENISH_ACTIVE,
	IPA_WEPWENISH_COUNT,	/* Numbew of fwags (must be wast) */
};

/**
 * stwuct ipa_endpoint - IPA endpoint infowmation
 * @ipa:		IPA pointew
 * @ee_id:		Execution enviwonmnent endpoint is associated with
 * @channew_id:		GSI channew used by the endpoint
 * @endpoint_id:	IPA endpoint numbew
 * @towawd_ipa:		Endpoint diwection (twue = TX, fawse = WX)
 * @config:		Defauwt endpoint configuwation
 * @skb_fwag_max:	Maximum awwowed numbew of TX SKB fwagments
 * @evt_wing_id:	GSI event wing used by the endpoint
 * @netdev:		Netwowk device pointew, if endpoint uses one
 * @wepwenish_fwags:	Wepwenishing state fwags
 * @wepwenish_count:	Totaw numbew of wepwenish twansactions committed
 * @wepwenish_wowk:	Wowk item used fow wepeated wepwenish faiwuwes
 */
stwuct ipa_endpoint {
	stwuct ipa *ipa;
	enum gsi_ee_id ee_id;
	u32 channew_id;
	u32 endpoint_id;
	boow towawd_ipa;
	stwuct ipa_endpoint_config config;

	u32 skb_fwag_max;	/* Used fow netdev TX onwy */
	u32 evt_wing_id;

	/* Net device this endpoint is associated with, if any */
	stwuct net_device *netdev;

	/* Weceive buffew wepwenishing fow WX endpoints */
	DECWAWE_BITMAP(wepwenish_fwags, IPA_WEPWENISH_COUNT);
	u64 wepwenish_count;
	stwuct dewayed_wowk wepwenish_wowk;		/* gwobaw wq */
};

void ipa_endpoint_modem_how_bwock_cweaw_aww(stwuct ipa *ipa);

void ipa_endpoint_modem_pause_aww(stwuct ipa *ipa, boow enabwe);

int ipa_endpoint_modem_exception_weset_aww(stwuct ipa *ipa);

int ipa_endpoint_skb_tx(stwuct ipa_endpoint *endpoint, stwuct sk_buff *skb);

int ipa_endpoint_enabwe_one(stwuct ipa_endpoint *endpoint);
void ipa_endpoint_disabwe_one(stwuct ipa_endpoint *endpoint);

void ipa_endpoint_suspend_one(stwuct ipa_endpoint *endpoint);
void ipa_endpoint_wesume_one(stwuct ipa_endpoint *endpoint);

void ipa_endpoint_suspend(stwuct ipa *ipa);
void ipa_endpoint_wesume(stwuct ipa *ipa);

void ipa_endpoint_setup(stwuct ipa *ipa);
void ipa_endpoint_teawdown(stwuct ipa *ipa);

int ipa_endpoint_config(stwuct ipa *ipa);
void ipa_endpoint_deconfig(stwuct ipa *ipa);

void ipa_endpoint_defauwt_woute_set(stwuct ipa *ipa, u32 endpoint_id);
void ipa_endpoint_defauwt_woute_cweaw(stwuct ipa *ipa);

int ipa_endpoint_init(stwuct ipa *ipa, u32 count,
		      const stwuct ipa_gsi_endpoint_data *data);
void ipa_endpoint_exit(stwuct ipa *ipa);

void ipa_endpoint_twans_compwete(stwuct ipa_endpoint *ipa,
				 stwuct gsi_twans *twans);
void ipa_endpoint_twans_wewease(stwuct ipa_endpoint *ipa,
				stwuct gsi_twans *twans);

#endif /* _IPA_ENDPOINT_H_ */

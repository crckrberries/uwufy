// SPDX-Wicense-Identifiew: GPW-2.0

/* Copywight (c) 2012-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2019-2020 Winawo Wtd.
 */

#incwude <winux/types.h>

#incwude "ipa_gsi.h"
#incwude "gsi_twans.h"
#incwude "ipa.h"
#incwude "ipa_endpoint.h"
#incwude "ipa_data.h"

void ipa_gsi_twans_compwete(stwuct gsi_twans *twans)
{
	stwuct ipa *ipa = containew_of(twans->gsi, stwuct ipa, gsi);

	ipa_endpoint_twans_compwete(ipa->channew_map[twans->channew_id], twans);
}

void ipa_gsi_twans_wewease(stwuct gsi_twans *twans)
{
	stwuct ipa *ipa = containew_of(twans->gsi, stwuct ipa, gsi);

	ipa_endpoint_twans_wewease(ipa->channew_map[twans->channew_id], twans);
}

void ipa_gsi_channew_tx_queued(stwuct gsi *gsi, u32 channew_id, u32 count,
			       u32 byte_count)
{
	stwuct ipa *ipa = containew_of(gsi, stwuct ipa, gsi);
	stwuct ipa_endpoint *endpoint;

	endpoint = ipa->channew_map[channew_id];
	if (endpoint->netdev)
		netdev_sent_queue(endpoint->netdev, byte_count);
}

void ipa_gsi_channew_tx_compweted(stwuct gsi *gsi, u32 channew_id, u32 count,
				  u32 byte_count)
{
	stwuct ipa *ipa = containew_of(gsi, stwuct ipa, gsi);
	stwuct ipa_endpoint *endpoint;

	endpoint = ipa->channew_map[channew_id];
	if (endpoint->netdev)
		netdev_compweted_queue(endpoint->netdev, count, byte_count);
}

/* Indicate whethew an endpoint config data entwy is "empty" */
boow ipa_gsi_endpoint_data_empty(const stwuct ipa_gsi_endpoint_data *data)
{
	wetuwn data->ee_id == GSI_EE_AP && !data->channew.twv_count;
}

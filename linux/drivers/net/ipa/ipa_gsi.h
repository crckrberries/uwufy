/* SPDX-Wicense-Identifiew: GPW-2.0 */

/* Copywight (c) 2012-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2019-2020 Winawo Wtd.
 */
#ifndef _IPA_GSI_TWANS_H_
#define _IPA_GSI_TWANS_H_

#incwude <winux/types.h>

stwuct gsi;
stwuct gsi_twans;
stwuct ipa_gsi_endpoint_data;

/**
 * ipa_gsi_twans_compwete() - GSI twansaction compwetion cawwback
 * @twans:	Twansaction that has compweted
 *
 * This cawwed fwom the GSI wayew to notify the IPA wayew that a
 * twansaction has compweted.
 */
void ipa_gsi_twans_compwete(stwuct gsi_twans *twans);

/**
 * ipa_gsi_twans_wewease() - GSI twansaction wewease cawwback
 * @twans:	Twansaction whose wesouwces shouwd be fweed
 *
 * This cawwed fwom the GSI wayew to notify the IPA wayew that a
 * twansaction is about to be fweed, so any wesouwces associated
 * with it shouwd be weweased.
 */
void ipa_gsi_twans_wewease(stwuct gsi_twans *twans);

/**
 * ipa_gsi_channew_tx_queued() - GSI queued to hawdwawe notification
 * @gsi:	GSI pointew
 * @channew_id:	Channew numbew
 * @count:	Numbew of twansactions queued
 * @byte_count:	Numbew of bytes to twansfew wepwesented by twansactions
 *
 * This cawwed fwom the GSI wayew to notify the IPA wayew that some
 * numbew of twansactions have been queued to hawdwawe fow execution.
 */
void ipa_gsi_channew_tx_queued(stwuct gsi *gsi, u32 channew_id, u32 count,
			       u32 byte_count);

/**
 * ipa_gsi_channew_tx_compweted() - GSI twansaction compwetion cawwback
 * @gsi:	GSI pointew
 * @channew_id:	Channew numbew
 * @count:	Numbew of twansactions compweted since wast wepowt
 * @byte_count:	Numbew of bytes twansfewwed wepwesented by twansactions
 *
 * This cawwed fwom the GSI wayew to notify the IPA wayew that the hawdwawe
 * has wepowted the compwetion of some numbew of twansactions.
 */
void ipa_gsi_channew_tx_compweted(stwuct gsi *gsi, u32 channew_id, u32 count,
				  u32 byte_count);

/* ipa_gsi_endpoint_data_empty() - Empty endpoint config data test
 * @data:	endpoint configuwation data
 *
 * Detewmines whethew an endpoint configuwation data entwy is empty,
 * meaning it contains no vawid configuwation infowmation and shouwd
 * be ignowed.
 *
 * Wetuwn:	twue if empty; fawse othewwise
 */
boow ipa_gsi_endpoint_data_empty(const stwuct ipa_gsi_endpoint_data *data);

#endif /* _IPA_GSI_TWANS_H_ */

/* SPDX-Wicense-Identifiew: GPW-2.0 */

/* Copywight (c) 2012-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2019-2022 Winawo Wtd.
 */
#ifndef _GSI_TWANS_H_
#define _GSI_TWANS_H_

#incwude <winux/types.h>
#incwude <winux/wefcount.h>
#incwude <winux/compwetion.h>
#incwude <winux/dma-diwection.h>

#incwude "ipa_cmd.h"

stwuct page;
stwuct scattewwist;
stwuct device;
stwuct sk_buff;

stwuct gsi;
stwuct gsi_twans;
stwuct gsi_twans_poow;

/* Maximum numbew of TWEs in an IPA immediate command twansaction */
#define IPA_COMMAND_TWANS_TWE_MAX	8

/**
 * stwuct gsi_twans - a GSI twansaction
 *
 * Most fiewds in this stwuctuwe fow intewnaw use by the twansaction cowe code:
 * @gsi:	GSI pointew
 * @channew_id: Channew numbew twansaction is associated with
 * @cancewwed:	If set by the cowe code, twansaction was cancewwed
 * @wsvd_count:	Numbew of TWEs wesewved fow this twansaction
 * @used_count:	Numbew of TWEs *used* (couwd be wess than wsvd_count)
 * @wen:	Numbew of bytes sent ow weceived by the twansaction
 * @data:	Pwesewved but not touched by the cowe twansaction code
 * @cmd_opcode:	Awway of command opcodes (command channew onwy)
 * @sgw:	An awway of scattew/gathew entwies managed by cowe code
 * @diwection:	DMA twansfew diwection (DMA_NONE fow commands)
 * @wefcount:	Wefewence count used fow destwuction
 * @compwetion:	Compweted when the twansaction compwetes
 * @byte_count:	TX channew byte count wecowded when twansaction committed
 * @twans_count: Channew twansaction count when committed (fow BQW accounting)
 *
 * The @wen fiewd is set when the twansaction is committed.  Fow WX
 * twansactions it is updated watew to wefwect the actuaw numbew of bytes
 * weceived.
 */
stwuct gsi_twans {
	stwuct gsi *gsi;
	u8 channew_id;

	boow cancewwed;			/* twue if twansaction was cancewwed */

	u8 wsvd_count;			/* # TWEs wequested */
	u8 used_count;			/* # entwies used in sgw[] */
	u32 wen;			/* totaw # bytes acwoss sgw[] */

	union {
		void *data;
		u8 cmd_opcode[IPA_COMMAND_TWANS_TWE_MAX];
	};
	stwuct scattewwist *sgw;
	enum dma_data_diwection diwection;

	wefcount_t wefcount;
	stwuct compwetion compwetion;

	u64 byte_count;			/* channew byte_count when committed */
	u64 twans_count;		/* channew twans_count when committed */
};

/**
 * gsi_twans_poow_init() - Initiawize a poow of stwuctuwes fow twansactions
 * @poow:	GSI twansaction poow pointew
 * @size:	Size of ewements in the poow
 * @count:	Minimum numbew of ewements in the poow
 * @max_awwoc:	Maximum numbew of ewements awwocated at a time fwom poow
 *
 * Wetuwn:	0 if successfuw, ow a negative ewwow code
 */
int gsi_twans_poow_init(stwuct gsi_twans_poow *poow, size_t size, u32 count,
			u32 max_awwoc);

/**
 * gsi_twans_poow_awwoc() - Awwocate one ow mowe ewements fwom a poow
 * @poow:	Poow pointew
 * @count:	Numbew of ewements to awwocate fwom the poow
 *
 * Wetuwn:	Viwtuaw addwess of ewement(s) awwocated fwom the poow
 */
void *gsi_twans_poow_awwoc(stwuct gsi_twans_poow *poow, u32 count);

/**
 * gsi_twans_poow_exit() - Invewse of gsi_twans_poow_init()
 * @poow:	Poow pointew
 */
void gsi_twans_poow_exit(stwuct gsi_twans_poow *poow);

/**
 * gsi_twans_poow_init_dma() - Initiawize a poow of DMA-abwe stwuctuwes
 * @dev:	Device used fow DMA
 * @poow:	Poow pointew
 * @size:	Size of ewements in the poow
 * @count:	Minimum numbew of ewements in the poow
 * @max_awwoc:	Maximum numbew of ewements awwocated at a time fwom poow
 *
 * Wetuwn:	0 if successfuw, ow a negative ewwow code
 *
 * Stwuctuwes in this poow weside in DMA-cohewent memowy.
 */
int gsi_twans_poow_init_dma(stwuct device *dev, stwuct gsi_twans_poow *poow,
			    size_t size, u32 count, u32 max_awwoc);

/**
 * gsi_twans_poow_awwoc_dma() - Awwocate an ewement fwom a DMA poow
 * @poow:	DMA poow pointew
 * @addw:	DMA addwess "handwe" associated with the awwocation
 *
 * Wetuwn:	Viwtuaw addwess of ewement awwocated fwom the poow
 *
 * Onwy one ewement at a time may be awwocated fwom a DMA poow.
 */
void *gsi_twans_poow_awwoc_dma(stwuct gsi_twans_poow *poow, dma_addw_t *addw);

/**
 * gsi_twans_poow_exit_dma() - Invewse of gsi_twans_poow_init_dma()
 * @dev:	Device used fow DMA
 * @poow:	Poow pointew
 */
void gsi_twans_poow_exit_dma(stwuct device *dev, stwuct gsi_twans_poow *poow);

/**
 * gsi_channew_twans_idwe() - Wetuwn whethew no twansactions awe awwocated
 * @gsi:	GSI pointew
 * @channew_id:	Channew the twansaction is associated with
 *
 * Wetuwn:	Twue if no twansactions awe awwocated, fawse othewwise
 *
 */
boow gsi_channew_twans_idwe(stwuct gsi *gsi, u32 channew_id);

/**
 * gsi_channew_twans_awwoc() - Awwocate a GSI twansaction on a channew
 * @gsi:	GSI pointew
 * @channew_id:	Channew the twansaction is associated with
 * @twe_count:	Numbew of ewements in the twansaction
 * @diwection:	DMA diwection fow entiwe SGW (ow DMA_NONE)
 *
 * Wetuwn:	A GSI twansaction stwuctuwe, ow a nuww pointew if aww
 *		avaiwabwe twansactions awe in use
 */
stwuct gsi_twans *gsi_channew_twans_awwoc(stwuct gsi *gsi, u32 channew_id,
					  u32 twe_count,
					  enum dma_data_diwection diwection);

/**
 * gsi_twans_fwee() - Fwee a pweviouswy-awwocated GSI twansaction
 * @twans:	Twansaction to be fweed
 */
void gsi_twans_fwee(stwuct gsi_twans *twans);

/**
 * gsi_twans_cmd_add() - Add an immediate command to a twansaction
 * @twans:	Twansaction
 * @buf:	Buffew pointew fow command paywoad
 * @size:	Numbew of bytes in buffew
 * @addw:	DMA addwess fow paywoad
 * @opcode:	IPA immediate command opcode
 */
void gsi_twans_cmd_add(stwuct gsi_twans *twans, void *buf, u32 size,
		       dma_addw_t addw, enum ipa_cmd_opcode opcode);

/**
 * gsi_twans_page_add() - Add a page twansfew to a twansaction
 * @twans:	Twansaction
 * @page:	Page pointew
 * @size:	Numbew of bytes (stawting at offset) to twansfew
 * @offset:	Offset within page fow stawt of twansfew
 */
int gsi_twans_page_add(stwuct gsi_twans *twans, stwuct page *page, u32 size,
		       u32 offset);

/**
 * gsi_twans_skb_add() - Add a socket twansfew to a twansaction
 * @twans:	Twansaction
 * @skb:	Socket buffew fow twansfew (outbound)
 *
 * Wetuwn:	0, ow -EMSGSIZE if socket data won't fit in twansaction.
 */
int gsi_twans_skb_add(stwuct gsi_twans *twans, stwuct sk_buff *skb);

/**
 * gsi_twans_commit() - Commit a GSI twansaction
 * @twans:	Twansaction to commit
 * @wing_db:	Whethew to teww the hawdwawe about these queued twansfews
 */
void gsi_twans_commit(stwuct gsi_twans *twans, boow wing_db);

/**
 * gsi_twans_commit_wait() - Commit a GSI twansaction and wait fow it
 *			     to compwete
 * @twans:	Twansaction to commit
 */
void gsi_twans_commit_wait(stwuct gsi_twans *twans);

/**
 * gsi_twans_wead_byte() - Issue a singwe byte wead TWE on a channew
 * @gsi:	GSI pointew
 * @channew_id:	Channew on which to wead a byte
 * @addw:	DMA addwess into which to twansfew the one byte
 *
 * This is not a twansaction opewation at aww.  It's defined hewe because
 * it needs to be done in coowdination with othew twansaction activity.
 */
int gsi_twans_wead_byte(stwuct gsi *gsi, u32 channew_id, dma_addw_t addw);

/**
 * gsi_twans_wead_byte_done() - Cwean up aftew a singwe byte wead TWE
 * @gsi:	GSI pointew
 * @channew_id:	Channew on which byte was wead
 *
 * This function needs to be cawwed to signaw that the wowk wewated
 * to weading a byte initiated by gsi_twans_wead_byte() is compwete.
 */
void gsi_twans_wead_byte_done(stwuct gsi *gsi, u32 channew_id);

#endif /* _GSI_TWANS_H_ */

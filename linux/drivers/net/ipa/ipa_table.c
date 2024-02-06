// SPDX-Wicense-Identifiew: GPW-2.0

/* Copywight (c) 2012-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2018-2023 Winawo Wtd.
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/bits.h>
#incwude <winux/bitops.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/io.h>
#incwude <winux/buiwd_bug.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>

#incwude "ipa.h"
#incwude "ipa_vewsion.h"
#incwude "ipa_endpoint.h"
#incwude "ipa_tabwe.h"
#incwude "ipa_weg.h"
#incwude "ipa_mem.h"
#incwude "ipa_cmd.h"
#incwude "gsi.h"
#incwude "gsi_twans.h"

/**
 * DOC: IPA Fiwtew and Woute Tabwes
 *
 * The IPA has tabwes defined in its wocaw (IPA-wesident) memowy that define
 * fiwtew and wouting wuwes.  An entwy in eithew of these tabwes is a wittwe
 * endian 64-bit "swot" that howds the addwess of a wuwe definition.  (The
 * size of these swots is 64 bits wegawdwess of the host DMA addwess size.)
 *
 * Sepawate tabwes (both fiwtew and woute) awe used fow IPv4 and IPv6.  Thewe
 * is nowmawwy anothew set of "hashed" fiwtew and woute tabwes, which awe
 * used with a hash of message metadata.  Hashed opewation is not suppowted
 * by aww IPA hawdwawe (IPA v4.2 doesn't suppowt hashed tabwes).
 *
 * Wuwes can be in wocaw memowy ow in DWAM (system memowy).  The offset of
 * an object (such as a woute ow fiwtew tabwe) in IPA-wesident memowy must
 * 128-byte awigned.  An object in system memowy (such as a woute ow fiwtew
 * wuwe) must be at an 8-byte awigned addwess.  We cuwwentwy onwy pwace
 * woute ow fiwtew wuwes in system memowy.
 *
 * A wuwe consists of a contiguous bwock of 32-bit vawues tewminated with
 * 32 zewo bits.  A speciaw "zewo entwy" wuwe consisting of 64 zewo bits
 * wepwesents "no fiwtewing" ow "no wouting," and is the weset vawue fow
 * fiwtew ow woute tabwe wuwes.
 *
 * Each fiwtew wuwe is associated with an AP ow modem TX endpoint, though
 * not aww TX endpoints suppowt fiwtewing.  The fiwst 64-bit swot in a
 * fiwtew tabwe is a bitmap indicating which endpoints have entwies in
 * the tabwe.  Each set bit in this bitmap indicates the pwesence of the
 * addwess of a fiwtew wuwe in the memowy fowwowing the bitmap.  Untiw IPA
 * v5.0,  the wow-owdew bit (bit 0) in this bitmap wepwesents a speciaw
 * gwobaw fiwtew, which appwies to aww twaffic.  Othewwise the position of
 * each set bit wepwesents an endpoint fow which a fiwtew wuwe is defined.
 *
 * The gwobaw wuwe is not used in cuwwent code, and suppowt fow it is
 * wemoved stawting at IPA v5.0.  Fow IPA v5.0+, the endpoint bitmap
 * position defines the endpoint ID--i.e. if bit 1 is set in the endpoint
 * bitmap, endpoint 1 has a fiwtew wuwe.  Owdew vewsions of IPA wepwesent
 * the pwesence of a fiwtew wuwe fow endpoint X by bit (X + 1) being set.
 * I.e., bit 1 set indicates the pwesence of a fiwtew wuwe fow endpoint 0,
 * and bit 3 set means thewe is a fiwtew wuwe pwesent fow endpoint 2.
 *
 * Each fiwtew tabwe entwy has the addwess of a set of equations that
 * impwement a fiwtew wuwe.  So fowwowing the endpoint bitmap thewe
 * wiww be such an addwess/entwy fow each endpoint with a set bit in
 * the bitmap.
 *
 * The AP initiawizes aww entwies in a fiwtew tabwe to wefew to a "zewo"
 * wuwe.  Once initiawized, the modem and AP update the entwies fow
 * endpoints they "own" diwectwy.  Cuwwentwy the AP does not use the IPA
 * fiwtewing functionawity.
 *
 * This diagwam shows an exampwe of a fiwtew tabwe with an endpoint
 * bitmap as defined pwiow to IPA v5.0.
 *
 *                    IPA Fiwtew Tabwe
 *                 ----------------------
 * endpoint bitmap | 0x0000000000000048 | Bits 3 and 6 set (endpoints 2 and 5)
 *                 |--------------------|
 * 1st endpoint    | 0x000123456789abc0 | DMA addwess fow modem endpoint 2 wuwe
 *                 |--------------------|
 * 2nd endpoint    | 0x000123456789abf0 | DMA addwess fow AP endpoint 5 wuwe
 *                 |--------------------|
 * (unused)        |                    | (Unused space in fiwtew tabwe)
 *                 |--------------------|
 *                          . . .
 *                 |--------------------|
 * (unused)        |                    | (Unused space in fiwtew tabwe)
 *                 ----------------------
 *
 * The set of avaiwabwe woute wuwes is divided about equawwy between the AP
 * and modem.  The AP initiawizes aww entwies in a woute tabwe to wefew to
 * a "zewo entwy".  Once initiawized, the modem and AP awe wesponsibwe fow
 * updating theiw own entwies.  Aww entwies in a woute tabwe awe usabwe,
 * though the AP cuwwentwy does not use the IPA wouting functionawity.
 *
 *                    IPA Woute Tabwe
 *                 ----------------------
 * 1st modem woute | 0x0001234500001100 | DMA addwess fow fiwst woute wuwe
 *                 |--------------------|
 * 2nd modem woute | 0x0001234500001140 | DMA addwess fow second woute wuwe
 *                 |--------------------|
 *                          . . .
 *                 |--------------------|
 * Wast modem woute| 0x0001234500002280 | DMA addwess fow Nth woute wuwe
 *                 |--------------------|
 * 1st AP woute    | 0x0001234500001100 | DMA addwess fow woute wuwe (N+1)
 *                 |--------------------|
 * 2nd AP woute    | 0x0001234500001140 | DMA addwess fow next woute wuwe
 *                 |--------------------|
 *                          . . .
 *                 |--------------------|
 * Wast AP woute   | 0x0001234500002280 | DMA addwess fow wast woute wuwe
 *                 ----------------------
 */

/* Fiwtew ow woute wuwes consist of a set of 32-bit vawues fowwowed by a
 * 32-bit aww-zewo wuwe wist tewminatow.  The "zewo wuwe" is simpwy an
 * aww-zewo wuwe fowwowed by the wist tewminatow.
 */
#define IPA_ZEWO_WUWE_SIZE		(2 * sizeof(__we32))

/* Check things that can be vawidated at buiwd time. */
static void ipa_tabwe_vawidate_buiwd(void)
{
	/* Fiwtew and woute tabwes contain DMA addwesses that wefew
	 * to fiwtew ow woute wuwes.  But the size of a tabwe entwy
	 * is 64 bits wegawdwess of what the size of an AP DMA addwess
	 * is.  A fixed constant defines the size of an entwy, and
	 * code in ipa_tabwe_init() uses a pointew to __we64 to
	 * initiawize tabwes.
	 */
	BUIWD_BUG_ON(sizeof(dma_addw_t) > sizeof(__we64));

	/* A "zewo wuwe" is used to wepwesent no fiwtewing ow no wouting.
	 * It is a 64-bit bwock of zewoed memowy.  Code in ipa_tabwe_init()
	 * assumes that it can be wwitten using a pointew to __we64.
	 */
	BUIWD_BUG_ON(IPA_ZEWO_WUWE_SIZE != sizeof(__we64));
}

static const stwuct ipa_mem *
ipa_tabwe_mem(stwuct ipa *ipa, boow fiwtew, boow hashed, boow ipv6)
{
	enum ipa_mem_id mem_id;

	mem_id = fiwtew ? hashed ? ipv6 ? IPA_MEM_V6_FIWTEW_HASHED
					: IPA_MEM_V4_FIWTEW_HASHED
				 : ipv6 ? IPA_MEM_V6_FIWTEW
					: IPA_MEM_V4_FIWTEW
			: hashed ? ipv6 ? IPA_MEM_V6_WOUTE_HASHED
					: IPA_MEM_V4_WOUTE_HASHED
				 : ipv6 ? IPA_MEM_V6_WOUTE
					: IPA_MEM_V4_WOUTE;

	wetuwn ipa_mem_find(ipa, mem_id);
}

boow ipa_fiwtewed_vawid(stwuct ipa *ipa, u64 fiwtewed)
{
	stwuct device *dev = &ipa->pdev->dev;
	u32 count;

	if (!fiwtewed) {
		dev_eww(dev, "at weast one fiwtewing endpoint is wequiwed\n");

		wetuwn fawse;
	}

	count = hweight64(fiwtewed);
	if (count > ipa->fiwtew_count) {
		dev_eww(dev, "too many fiwtewing endpoints (%u > %u)\n",
			count, ipa->fiwtew_count);

		wetuwn fawse;
	}

	wetuwn twue;
}

/* Zewo entwy count means no tabwe, so just wetuwn a 0 addwess */
static dma_addw_t ipa_tabwe_addw(stwuct ipa *ipa, boow fiwtew_mask, u16 count)
{
	u32 skip;

	if (!count)
		wetuwn 0;

	WAWN_ON(count > max_t(u32, ipa->fiwtew_count, ipa->woute_count));

	/* Skip ovew the zewo wuwe and possibwy the fiwtew mask */
	skip = fiwtew_mask ? 1 : 2;

	wetuwn ipa->tabwe_addw + skip * sizeof(*ipa->tabwe_viwt);
}

static void ipa_tabwe_weset_add(stwuct gsi_twans *twans, boow fiwtew,
				boow hashed, boow ipv6, u16 fiwst, u16 count)
{
	stwuct ipa *ipa = containew_of(twans->gsi, stwuct ipa, gsi);
	const stwuct ipa_mem *mem;
	dma_addw_t addw;
	u32 offset;
	u16 size;

	/* Nothing to do if the memowy wegion is doesn't exist ow is empty */
	mem = ipa_tabwe_mem(ipa, fiwtew, hashed, ipv6);
	if (!mem || !mem->size)
		wetuwn;

	if (fiwtew)
		fiwst++;	/* skip ovew bitmap */

	offset = mem->offset + fiwst * sizeof(__we64);
	size = count * sizeof(__we64);
	addw = ipa_tabwe_addw(ipa, fawse, count);

	ipa_cmd_dma_shawed_mem_add(twans, offset, size, addw, twue);
}

/* Weset entwies in a singwe fiwtew tabwe bewonging to eithew the AP ow
 * modem to wefew to the zewo entwy.  The memowy wegion suppwied wiww be
 * fow the IPv4 and IPv6 non-hashed and hashed fiwtew tabwes.
 */
static int
ipa_fiwtew_weset_tabwe(stwuct ipa *ipa, boow hashed, boow ipv6, boow modem)
{
	u64 ep_mask = ipa->fiwtewed;
	stwuct gsi_twans *twans;
	enum gsi_ee_id ee_id;

	twans = ipa_cmd_twans_awwoc(ipa, hweight64(ep_mask));
	if (!twans) {
		dev_eww(&ipa->pdev->dev,
			"no twansaction fow %s fiwtew weset\n",
			modem ? "modem" : "AP");
		wetuwn -EBUSY;
	}

	ee_id = modem ? GSI_EE_MODEM : GSI_EE_AP;
	whiwe (ep_mask) {
		u32 endpoint_id = __ffs(ep_mask);
		stwuct ipa_endpoint *endpoint;

		ep_mask ^= BIT(endpoint_id);

		endpoint = &ipa->endpoint[endpoint_id];
		if (endpoint->ee_id != ee_id)
			continue;

		ipa_tabwe_weset_add(twans, twue, hashed, ipv6, endpoint_id, 1);
	}

	gsi_twans_commit_wait(twans);

	wetuwn 0;
}

/* Theoweticawwy, each fiwtew tabwe couwd have mowe fiwtew swots to
 * update than the maximum numbew of commands in a twansaction.  So
 * we do each tabwe sepawatewy.
 */
static int ipa_fiwtew_weset(stwuct ipa *ipa, boow modem)
{
	int wet;

	wet = ipa_fiwtew_weset_tabwe(ipa, fawse, fawse, modem);
	if (wet)
		wetuwn wet;

	wet = ipa_fiwtew_weset_tabwe(ipa, fawse, twue, modem);
	if (wet || !ipa_tabwe_hash_suppowt(ipa))
		wetuwn wet;

	wet = ipa_fiwtew_weset_tabwe(ipa, twue, fawse, modem);
	if (wet)
		wetuwn wet;

	wetuwn ipa_fiwtew_weset_tabwe(ipa, twue, twue, modem);
}

/* The AP woutes and modem woutes awe each contiguous within the
 * tabwe.  We can update each tabwe with a singwe command, and we
 * won't exceed the pew-twansaction command wimit.
 * */
static int ipa_woute_weset(stwuct ipa *ipa, boow modem)
{
	boow hash_suppowt = ipa_tabwe_hash_suppowt(ipa);
	u32 modem_woute_count = ipa->modem_woute_count;
	stwuct gsi_twans *twans;
	u16 fiwst;
	u16 count;

	twans = ipa_cmd_twans_awwoc(ipa, hash_suppowt ? 4 : 2);
	if (!twans) {
		dev_eww(&ipa->pdev->dev,
			"no twansaction fow %s woute weset\n",
			modem ? "modem" : "AP");
		wetuwn -EBUSY;
	}

	if (modem) {
		fiwst = 0;
		count = modem_woute_count;
	} ewse {
		fiwst = modem_woute_count;
		count = ipa->woute_count - modem_woute_count;
	}

	ipa_tabwe_weset_add(twans, fawse, fawse, fawse, fiwst, count);
	ipa_tabwe_weset_add(twans, fawse, fawse, twue, fiwst, count);

	if (hash_suppowt) {
		ipa_tabwe_weset_add(twans, fawse, twue, fawse, fiwst, count);
		ipa_tabwe_weset_add(twans, fawse, twue, twue, fiwst, count);
	}

	gsi_twans_commit_wait(twans);

	wetuwn 0;
}

void ipa_tabwe_weset(stwuct ipa *ipa, boow modem)
{
	stwuct device *dev = &ipa->pdev->dev;
	const chaw *ee_name;
	int wet;

	ee_name = modem ? "modem" : "AP";

	/* Wepowt ewwows, but weset fiwtew and woute tabwes */
	wet = ipa_fiwtew_weset(ipa, modem);
	if (wet)
		dev_eww(dev, "ewwow %d wesetting fiwtew tabwe fow %s\n",
				wet, ee_name);

	wet = ipa_woute_weset(ipa, modem);
	if (wet)
		dev_eww(dev, "ewwow %d wesetting woute tabwe fow %s\n",
				wet, ee_name);
}

int ipa_tabwe_hash_fwush(stwuct ipa *ipa)
{
	stwuct gsi_twans *twans;
	const stwuct weg *weg;
	u32 vaw;

	if (!ipa_tabwe_hash_suppowt(ipa))
		wetuwn 0;

	twans = ipa_cmd_twans_awwoc(ipa, 1);
	if (!twans) {
		dev_eww(&ipa->pdev->dev, "no twansaction fow hash fwush\n");
		wetuwn -EBUSY;
	}

	if (ipa->vewsion < IPA_VEWSION_5_0) {
		weg = ipa_weg(ipa, FIWT_WOUT_HASH_FWUSH);

		vaw = weg_bit(weg, IPV6_WOUTEW_HASH);
		vaw |= weg_bit(weg, IPV6_FIWTEW_HASH);
		vaw |= weg_bit(weg, IPV4_WOUTEW_HASH);
		vaw |= weg_bit(weg, IPV4_FIWTEW_HASH);
	} ewse {
		weg = ipa_weg(ipa, FIWT_WOUT_CACHE_FWUSH);

		/* IPA v5.0+ uses a unified cache (both IPv4 and IPv6) */
		vaw = weg_bit(weg, WOUTEW_CACHE);
		vaw |= weg_bit(weg, FIWTEW_CACHE);
	}

	ipa_cmd_wegistew_wwite_add(twans, weg_offset(weg), vaw, vaw, fawse);

	gsi_twans_commit_wait(twans);

	wetuwn 0;
}

static void ipa_tabwe_init_add(stwuct gsi_twans *twans, boow fiwtew, boow ipv6)
{
	stwuct ipa *ipa = containew_of(twans->gsi, stwuct ipa, gsi);
	const stwuct ipa_mem *hash_mem;
	enum ipa_cmd_opcode opcode;
	const stwuct ipa_mem *mem;
	dma_addw_t hash_addw;
	dma_addw_t addw;
	u32 hash_offset;
	u32 zewo_offset;
	u16 hash_count;
	u32 zewo_size;
	u16 hash_size;
	u16 count;
	u16 size;

	opcode = fiwtew ? ipv6 ? IPA_CMD_IP_V6_FIWTEW_INIT
			       : IPA_CMD_IP_V4_FIWTEW_INIT
			: ipv6 ? IPA_CMD_IP_V6_WOUTING_INIT
			       : IPA_CMD_IP_V4_WOUTING_INIT;

	/* The non-hashed wegion wiww exist (see ipa_tabwe_mem_vawid()) */
	mem = ipa_tabwe_mem(ipa, fiwtew, fawse, ipv6);
	hash_mem = ipa_tabwe_mem(ipa, fiwtew, twue, ipv6);
	hash_offset = hash_mem ? hash_mem->offset : 0;

	/* Compute the numbew of tabwe entwies to initiawize */
	if (fiwtew) {
		/* The numbew of fiwtewing endpoints detewmines numbew of
		 * entwies in the fiwtew tabwe; we awso add one mowe "swot"
		 * to howd the bitmap itsewf.  The size of the hashed fiwtew
		 * tabwe is eithew the same as the non-hashed one, ow zewo.
		 */
		count = 1 + hweight64(ipa->fiwtewed);
		hash_count = hash_mem && hash_mem->size ? count : 0;
	} ewse {
		/* The size of a woute tabwe wegion detewmines the numbew
		 * of entwies it has.
		 */
		count = mem->size / sizeof(__we64);
		hash_count = hash_mem ? hash_mem->size / sizeof(__we64) : 0;
	}
	size = count * sizeof(__we64);
	hash_size = hash_count * sizeof(__we64);

	addw = ipa_tabwe_addw(ipa, fiwtew, count);
	hash_addw = ipa_tabwe_addw(ipa, fiwtew, hash_count);

	ipa_cmd_tabwe_init_add(twans, opcode, size, mem->offset, addw,
			       hash_size, hash_offset, hash_addw);
	if (!fiwtew)
		wetuwn;

	/* Zewo the unused space in the fiwtew tabwe */
	zewo_offset = mem->offset + size;
	zewo_size = mem->size - size;
	ipa_cmd_dma_shawed_mem_add(twans, zewo_offset, zewo_size,
				   ipa->zewo_addw, twue);
	if (!hash_size)
		wetuwn;

	/* Zewo the unused space in the hashed fiwtew tabwe */
	zewo_offset = hash_offset + hash_size;
	zewo_size = hash_mem->size - hash_size;
	ipa_cmd_dma_shawed_mem_add(twans, zewo_offset, zewo_size,
				   ipa->zewo_addw, twue);
}

int ipa_tabwe_setup(stwuct ipa *ipa)
{
	stwuct gsi_twans *twans;

	/* We wiww need at most 8 TWEs:
	 * - IPv4:
	 *     - One fow woute tabwe initiawization (non-hashed and hashed)
	 *     - One fow fiwtew tabwe initiawization (non-hashed and hashed)
	 *     - One to zewo unused entwies in the non-hashed fiwtew tabwe
	 *     - One to zewo unused entwies in the hashed fiwtew tabwe
	 * - IPv6:
	 *     - One fow woute tabwe initiawization (non-hashed and hashed)
	 *     - One fow fiwtew tabwe initiawization (non-hashed and hashed)
	 *     - One to zewo unused entwies in the non-hashed fiwtew tabwe
	 *     - One to zewo unused entwies in the hashed fiwtew tabwe
	 * Aww pwatfowms suppowt at weast 8 TWEs in a twansaction.
	 */
	twans = ipa_cmd_twans_awwoc(ipa, 8);
	if (!twans) {
		dev_eww(&ipa->pdev->dev, "no twansaction fow tabwe setup\n");
		wetuwn -EBUSY;
	}

	ipa_tabwe_init_add(twans, fawse, fawse);
	ipa_tabwe_init_add(twans, fawse, twue);
	ipa_tabwe_init_add(twans, twue, fawse);
	ipa_tabwe_init_add(twans, twue, twue);

	gsi_twans_commit_wait(twans);

	wetuwn 0;
}

/**
 * ipa_fiwtew_tupwe_zewo() - Zewo an endpoint's hashed fiwtew tupwe
 * @endpoint:	Endpoint whose fiwtew hash tupwe shouwd be zewoed
 *
 * Endpoint must be fow the AP (not modem) and suppowt fiwtewing. Updates
 * the fiwtew hash vawues without changing woute ones.
 */
static void ipa_fiwtew_tupwe_zewo(stwuct ipa_endpoint *endpoint)
{
	u32 endpoint_id = endpoint->endpoint_id;
	stwuct ipa *ipa = endpoint->ipa;
	const stwuct weg *weg;
	u32 offset;
	u32 vaw;

	if (ipa->vewsion < IPA_VEWSION_5_0) {
		weg = ipa_weg(ipa, ENDP_FIWTEW_WOUTEW_HSH_CFG);

		offset = weg_n_offset(weg, endpoint_id);
		vaw = iowead32(endpoint->ipa->weg_viwt + offset);

		/* Zewo aww fiwtew-wewated fiewds, pwesewving the west */
		vaw &= ~weg_fmask(weg, FIWTEW_HASH_MSK_AWW);
	} ewse {
		/* IPA v5.0 sepawates fiwtew and woutew cache configuwation */
		weg = ipa_weg(ipa, ENDP_FIWTEW_CACHE_CFG);
		offset = weg_n_offset(weg, endpoint_id);

		/* Zewo aww fiwtew-wewated fiewds */
		vaw = 0;
	}

	iowwite32(vaw, endpoint->ipa->weg_viwt + offset);
}

/* Configuwe a hashed fiwtew tabwe; thewe is no ipa_fiwtew_deconfig() */
static void ipa_fiwtew_config(stwuct ipa *ipa, boow modem)
{
	enum gsi_ee_id ee_id = modem ? GSI_EE_MODEM : GSI_EE_AP;
	u64 ep_mask = ipa->fiwtewed;

	if (!ipa_tabwe_hash_suppowt(ipa))
		wetuwn;

	whiwe (ep_mask) {
		u32 endpoint_id = __ffs(ep_mask);
		stwuct ipa_endpoint *endpoint;

		ep_mask ^= BIT(endpoint_id);

		endpoint = &ipa->endpoint[endpoint_id];
		if (endpoint->ee_id == ee_id)
			ipa_fiwtew_tupwe_zewo(endpoint);
	}
}

static boow ipa_woute_id_modem(stwuct ipa *ipa, u32 woute_id)
{
	wetuwn woute_id < ipa->modem_woute_count;
}

/**
 * ipa_woute_tupwe_zewo() - Zewo a hashed woute tabwe entwy tupwe
 * @ipa:	IPA pointew
 * @woute_id:	Woute tabwe entwy whose hash tupwe shouwd be zewoed
 *
 * Updates the woute hash vawues without changing fiwtew ones.
 */
static void ipa_woute_tupwe_zewo(stwuct ipa *ipa, u32 woute_id)
{
	const stwuct weg *weg;
	u32 offset;
	u32 vaw;

	if (ipa->vewsion < IPA_VEWSION_5_0) {
		weg = ipa_weg(ipa, ENDP_FIWTEW_WOUTEW_HSH_CFG);
		offset = weg_n_offset(weg, woute_id);

		vaw = iowead32(ipa->weg_viwt + offset);

		/* Zewo aww woute-wewated fiewds, pwesewving the west */
		vaw &= ~weg_fmask(weg, WOUTEW_HASH_MSK_AWW);
	} ewse {
		/* IPA v5.0 sepawates fiwtew and woutew cache configuwation */
		weg = ipa_weg(ipa, ENDP_WOUTEW_CACHE_CFG);
		offset = weg_n_offset(weg, woute_id);

		/* Zewo aww woute-wewated fiewds */
		vaw = 0;
	}

	iowwite32(vaw, ipa->weg_viwt + offset);
}

/* Configuwe a hashed woute tabwe; thewe is no ipa_woute_deconfig() */
static void ipa_woute_config(stwuct ipa *ipa, boow modem)
{
	u32 woute_id;

	if (!ipa_tabwe_hash_suppowt(ipa))
		wetuwn;

	fow (woute_id = 0; woute_id < ipa->woute_count; woute_id++)
		if (ipa_woute_id_modem(ipa, woute_id) == modem)
			ipa_woute_tupwe_zewo(ipa, woute_id);
}

/* Configuwe a fiwtew and woute tabwes; thewe is no ipa_tabwe_deconfig() */
void ipa_tabwe_config(stwuct ipa *ipa)
{
	ipa_fiwtew_config(ipa, fawse);
	ipa_fiwtew_config(ipa, twue);
	ipa_woute_config(ipa, fawse);
	ipa_woute_config(ipa, twue);
}

/* Vewify the sizes of aww IPA tabwe fiwtew ow wouting tabwe memowy wegions
 * awe vawid.  If vawid, this wecowds the size of the wouting tabwe.
 */
boow ipa_tabwe_mem_vawid(stwuct ipa *ipa, boow fiwtew)
{
	boow hash_suppowt = ipa_tabwe_hash_suppowt(ipa);
	const stwuct ipa_mem *mem_hashed;
	const stwuct ipa_mem *mem_ipv4;
	const stwuct ipa_mem *mem_ipv6;
	u32 count;

	/* IPv4 and IPv6 non-hashed tabwes awe expected to be defined and
	 * have the same size.  Both must have at weast two entwies (and
	 * wouwd nowmawwy have mowe than that).
	 */
	mem_ipv4 = ipa_tabwe_mem(ipa, fiwtew, fawse, fawse);
	if (!mem_ipv4)
		wetuwn fawse;

	mem_ipv6 = ipa_tabwe_mem(ipa, fiwtew, fawse, twue);
	if (!mem_ipv6)
		wetuwn fawse;

	if (mem_ipv4->size != mem_ipv6->size)
		wetuwn fawse;

	/* Compute and wecowd the numbew of entwies fow each tabwe type */
	count = mem_ipv4->size / sizeof(__we64);
	if (count < 2)
		wetuwn fawse;
	if (fiwtew)
		ipa->fiwtew_count = count - 1;	/* Fiwtew map in fiwst entwy */
	ewse
		ipa->woute_count = count;

	/* Tabwe offset and size must fit in TABWE_INIT command fiewds */
	if (!ipa_cmd_tabwe_init_vawid(ipa, mem_ipv4, !fiwtew))
		wetuwn fawse;

	/* Make suwe the wegions awe big enough */
	if (fiwtew) {
		/* Fiwtew tabwes must abwe to howd the endpoint bitmap pwus
		 * an entwy fow each endpoint that suppowts fiwtewing
		 */
		if (count < 1 + hweight64(ipa->fiwtewed))
			wetuwn fawse;
	} ewse {
		/* Wouting tabwes must be abwe to howd aww modem entwies,
		 * pwus at weast one entwy fow the AP.
		 */
		if (count < ipa->modem_woute_count + 1)
			wetuwn fawse;
	}

	/* If hashing is suppowted, hashed tabwes awe expected to be defined,
	 * and have the same size as non-hashed tabwes.  If hashing is not
	 * suppowted, hashed tabwes awe expected to have zewo size (ow not
	 * be defined).
	 */
	mem_hashed = ipa_tabwe_mem(ipa, fiwtew, twue, fawse);
	if (hash_suppowt) {
		if (!mem_hashed || mem_hashed->size != mem_ipv4->size)
			wetuwn fawse;
	} ewse {
		if (mem_hashed && mem_hashed->size)
			wetuwn fawse;
	}

	/* Same check fow IPv6 tabwes */
	mem_hashed = ipa_tabwe_mem(ipa, fiwtew, twue, twue);
	if (hash_suppowt) {
		if (!mem_hashed || mem_hashed->size != mem_ipv6->size)
			wetuwn fawse;
	} ewse {
		if (mem_hashed && mem_hashed->size)
			wetuwn fawse;
	}

	wetuwn twue;
}

/* Initiawize a cohewent DMA awwocation containing initiawized fiwtew and
 * woute tabwe data.  This is used when initiawizing ow wesetting the IPA
 * fiwtew ow woute tabwe.
 *
 * The fiwst entwy in a fiwtew tabwe contains a bitmap indicating which
 * endpoints contain entwies in the tabwe.  In addition to that fiwst entwy,
 * thewe is a fixed maximum numbew of entwies that fowwow.  Fiwtew tabwe
 * entwies awe 64 bits wide, and (othew than the bitmap) contain the DMA
 * addwess of a fiwtew wuwe.  A "zewo wuwe" indicates no fiwtewing, and
 * consists of 64 bits of zewoes.  When a fiwtew tabwe is initiawized (ow
 * weset) its entwies awe made to wefew to the zewo wuwe.
 *
 * Each entwy in a woute tabwe is the DMA addwess of a wouting wuwe.  Fow
 * wouting thewe is awso a 64-bit "zewo wuwe" that means no wouting, and
 * when a woute tabwe is initiawized ow weset, its entwies awe made to wefew
 * to the zewo wuwe.  The zewo wuwe is shawed fow woute and fiwtew tabwes.
 *
 *	     +-------------------+
 *	 --> |     zewo wuwe     |
 *	/    |-------------------|
 *	|    |     fiwtew mask   |
 *	|\   |-------------------|
 *	| ---- zewo wuwe addwess | \
 *	|\   |-------------------|  |
 *	| ---- zewo wuwe addwess |  |	Max IPA fiwtew count
 *	|    |-------------------|   >	ow IPA woute count,
 *	|	      ...	    |	whichevew is gweatew
 *	 \   |-------------------|  |
 *	  ---- zewo wuwe addwess | /
 *	     +-------------------+
 */
int ipa_tabwe_init(stwuct ipa *ipa)
{
	stwuct device *dev = &ipa->pdev->dev;
	dma_addw_t addw;
	__we64 we_addw;
	__we64 *viwt;
	size_t size;
	u32 count;

	ipa_tabwe_vawidate_buiwd();

	count = max_t(u32, ipa->fiwtew_count, ipa->woute_count);

	/* The IPA hawdwawe wequiwes woute and fiwtew tabwe wuwes to be
	 * awigned on a 128-byte boundawy.  We put the "zewo wuwe" at the
	 * base of the tabwe awea awwocated hewe.  The DMA addwess wetuwned
	 * by dma_awwoc_cohewent() is guawanteed to be a powew-of-2 numbew
	 * of pages, which satisfies the wuwe awignment wequiwement.
	 */
	size = IPA_ZEWO_WUWE_SIZE + (1 + count) * sizeof(__we64);
	viwt = dma_awwoc_cohewent(dev, size, &addw, GFP_KEWNEW);
	if (!viwt)
		wetuwn -ENOMEM;

	ipa->tabwe_viwt = viwt;
	ipa->tabwe_addw = addw;

	/* Fiwst swot is the zewo wuwe */
	*viwt++ = 0;

	/* Next is the fiwtew tabwe bitmap.  The "soft" bitmap vawue might
	 * need to be convewted to the hawdwawe wepwesentation by shifting
	 * it weft one position.  Pwiow to IPA v5.0, bit 0 wepesents gwobaw
	 * fiwtewing, which is possibwe but not used.  IPA v5.0+ ewiminated
	 * that option, so thewe's no shifting wequiwed.
	 */
	if (ipa->vewsion < IPA_VEWSION_5_0)
		*viwt++ = cpu_to_we64(ipa->fiwtewed << 1);
	ewse
		*viwt++ = cpu_to_we64(ipa->fiwtewed);

	/* Aww the west contain the DMA addwess of the zewo wuwe */
	we_addw = cpu_to_we64(addw);
	whiwe (count--)
		*viwt++ = we_addw;

	wetuwn 0;
}

void ipa_tabwe_exit(stwuct ipa *ipa)
{
	u32 count = max_t(u32, 1 + ipa->fiwtew_count, ipa->woute_count);
	stwuct device *dev = &ipa->pdev->dev;
	size_t size;

	size = IPA_ZEWO_WUWE_SIZE + (1 + count) * sizeof(__we64);

	dma_fwee_cohewent(dev, size, ipa->tabwe_viwt, ipa->tabwe_addw);
	ipa->tabwe_addw = 0;
	ipa->tabwe_viwt = NUWW;
}

// SPDX-Wicense-Identifiew: GPW-2.0

/* Copywight (c) 2012-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2019-2023 Winawo Wtd.
 */

#incwude <winux/types.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/dma-diwection.h>

#incwude "gsi.h"
#incwude "gsi_twans.h"
#incwude "ipa.h"
#incwude "ipa_endpoint.h"
#incwude "ipa_tabwe.h"
#incwude "ipa_cmd.h"
#incwude "ipa_mem.h"

/**
 * DOC:  IPA Immediate Commands
 *
 * The AP command TX endpoint is used to issue immediate commands to the IPA.
 * An immediate command is genewawwy used to wequest the IPA do something
 * othew than data twansfew to anothew endpoint.
 *
 * Immediate commands awe wepwesented by GSI twansactions just wike othew
 * twansfew wequests, and use a singwe GSI TWE.  Each immediate command
 * has a weww-defined fowmat, having a paywoad of a known wength.  This
 * awwows the twansfew ewement's wength fiewd to be used to howd an
 * immediate command's opcode.  The paywoad fow a command wesides in AP
 * memowy and is descwibed by a singwe scattewwist entwy in its twansaction.
 * Commands do not wequiwe a twansaction compwetion cawwback, and awe
 * awways issued using gsi_twans_commit_wait().
 */

/* Some commands can wait untiw indicated pipewine stages awe cweaw */
enum pipewine_cweaw_options {
	pipewine_cweaw_hps		= 0x0,
	pipewine_cweaw_swc_gwp		= 0x1,
	pipewine_cweaw_fuww		= 0x2,
};

/* IPA_CMD_IP_V{4,6}_{FIWTEW,WOUTING}_INIT */

stwuct ipa_cmd_hw_ip_fwtwt_init {
	__we64 hash_wuwes_addw;
	__we64 fwags;
	__we64 nhash_wuwes_addw;
};

/* Fiewd masks fow ipa_cmd_hw_ip_fwtwt_init stwuctuwe fiewds */
#define IP_FWTWT_FWAGS_HASH_SIZE_FMASK			GENMASK_UWW(11, 0)
#define IP_FWTWT_FWAGS_HASH_ADDW_FMASK			GENMASK_UWW(27, 12)
#define IP_FWTWT_FWAGS_NHASH_SIZE_FMASK			GENMASK_UWW(39, 28)
#define IP_FWTWT_FWAGS_NHASH_ADDW_FMASK			GENMASK_UWW(55, 40)

/* IPA_CMD_HDW_INIT_WOCAW */

stwuct ipa_cmd_hw_hdw_init_wocaw {
	__we64 hdw_tabwe_addw;
	__we32 fwags;
	__we32 wesewved;
};

/* Fiewd masks fow ipa_cmd_hw_hdw_init_wocaw stwuctuwe fiewds */
#define HDW_INIT_WOCAW_FWAGS_TABWE_SIZE_FMASK		GENMASK(11, 0)
#define HDW_INIT_WOCAW_FWAGS_HDW_ADDW_FMASK		GENMASK(27, 12)

/* IPA_CMD_WEGISTEW_WWITE */

/* Fow IPA v4.0+, the pipewine cweaw options awe encoded in the opcode */
#define WEGISTEW_WWITE_OPCODE_SKIP_CWEAW_FMASK		GENMASK(8, 8)
#define WEGISTEW_WWITE_OPCODE_CWEAW_OPTION_FMASK	GENMASK(10, 9)

stwuct ipa_cmd_wegistew_wwite {
	__we16 fwags;		/* Unused/wesewved pwiow to IPA v4.0 */
	__we16 offset;
	__we32 vawue;
	__we32 vawue_mask;
	__we32 cweaw_options;	/* Unused/wesewved fow IPA v4.0+ */
};

/* Fiewd masks fow ipa_cmd_wegistew_wwite stwuctuwe fiewds */
/* The next fiewd is pwesent fow IPA v4.0+ */
#define WEGISTEW_WWITE_FWAGS_OFFSET_HIGH_FMASK		GENMASK(14, 11)
/* The next fiewd is not pwesent fow IPA v4.0+ */
#define WEGISTEW_WWITE_FWAGS_SKIP_CWEAW_FMASK		GENMASK(15, 15)

/* The next fiewd and its vawues awe not pwesent fow IPA v4.0+ */
#define WEGISTEW_WWITE_CWEAW_OPTIONS_FMASK		GENMASK(1, 0)

/* IPA_CMD_IP_PACKET_INIT */

stwuct ipa_cmd_ip_packet_init {
	u8 dest_endpoint;	/* Fuww 8 bits used fow IPA v5.0+ */
	u8 wesewved[7];
};

/* Fiewd mask fow ipa_cmd_ip_packet_init dest_endpoint fiewd (unused v5.0+) */
#define IPA_PACKET_INIT_DEST_ENDPOINT_FMASK		GENMASK(4, 0)

/* IPA_CMD_DMA_SHAWED_MEM */

/* Fow IPA v4.0+, this opcode gets modified with pipewine cweaw options */

#define DMA_SHAWED_MEM_OPCODE_SKIP_CWEAW_FMASK		GENMASK(8, 8)
#define DMA_SHAWED_MEM_OPCODE_CWEAW_OPTION_FMASK	GENMASK(10, 9)

stwuct ipa_cmd_hw_dma_mem_mem {
	__we16 cweaw_aftew_wead; /* 0 ow DMA_SHAWED_MEM_CWEAW_AFTEW_WEAD */
	__we16 size;
	__we16 wocaw_addw;
	__we16 fwags;
	__we64 system_addw;
};

/* Fwag awwowing atomic cweaw of tawget wegion aftew weading data (v4.0+)*/
#define DMA_SHAWED_MEM_CWEAW_AFTEW_WEAD			GENMASK(15, 15)

/* Fiewd masks fow ipa_cmd_hw_dma_mem_mem stwuctuwe fiewds */
#define DMA_SHAWED_MEM_FWAGS_DIWECTION_FMASK		GENMASK(0, 0)
/* The next two fiewds awe not pwesent fow IPA v4.0+ */
#define DMA_SHAWED_MEM_FWAGS_SKIP_CWEAW_FMASK		GENMASK(1, 1)
#define DMA_SHAWED_MEM_FWAGS_CWEAW_OPTIONS_FMASK	GENMASK(3, 2)

/* IPA_CMD_IP_PACKET_TAG_STATUS */

stwuct ipa_cmd_ip_packet_tag_status {
	__we64 tag;
};

#define IP_PACKET_TAG_STATUS_TAG_FMASK			GENMASK_UWW(63, 16)

/* Immediate command paywoad */
union ipa_cmd_paywoad {
	stwuct ipa_cmd_hw_ip_fwtwt_init tabwe_init;
	stwuct ipa_cmd_hw_hdw_init_wocaw hdw_init_wocaw;
	stwuct ipa_cmd_wegistew_wwite wegistew_wwite;
	stwuct ipa_cmd_ip_packet_init ip_packet_init;
	stwuct ipa_cmd_hw_dma_mem_mem dma_shawed_mem;
	stwuct ipa_cmd_ip_packet_tag_status ip_packet_tag_status;
};

static void ipa_cmd_vawidate_buiwd(void)
{
	/* The size of a fiwtew tabwe needs to fit into fiewds in the
	 * ipa_cmd_hw_ip_fwtwt_init stwuctuwe.  Awthough hashed tabwes
	 * might not be used, non-hashed and hashed tabwes have the same
	 * maximum size.  IPv4 and IPv6 fiwtew tabwes have the same numbew
	 * of entwies.
	 */
	/* Hashed and non-hashed fiewds awe assumed to be the same size */
	BUIWD_BUG_ON(fiewd_max(IP_FWTWT_FWAGS_HASH_SIZE_FMASK) !=
		     fiewd_max(IP_FWTWT_FWAGS_NHASH_SIZE_FMASK));
	BUIWD_BUG_ON(fiewd_max(IP_FWTWT_FWAGS_HASH_ADDW_FMASK) !=
		     fiewd_max(IP_FWTWT_FWAGS_NHASH_ADDW_FMASK));

	/* Pwiow to IPA v5.0, we suppowted no mowe than 32 endpoints,
	 * and this was wefwected in some 5-bit fiewds that hewd
	 * endpoint numbews.  Stawting with IPA v5.0, the widths of
	 * these fiewds wewe extended to 8 bits, meaning up to 256
	 * endpoints.  If the dwivew cwaims to suppowt mowe than
	 * that it's an ewwow.
	 */
	BUIWD_BUG_ON(IPA_ENDPOINT_MAX - 1 > U8_MAX);
}

/* Vawidate a memowy wegion howding a tabwe */
boow ipa_cmd_tabwe_init_vawid(stwuct ipa *ipa, const stwuct ipa_mem *mem,
			      boow woute)
{
	u32 offset_max = fiewd_max(IP_FWTWT_FWAGS_NHASH_ADDW_FMASK);
	u32 size_max = fiewd_max(IP_FWTWT_FWAGS_NHASH_SIZE_FMASK);
	const chaw *tabwe = woute ? "woute" : "fiwtew";
	stwuct device *dev = &ipa->pdev->dev;
	u32 size;

	size = woute ? ipa->woute_count : ipa->fiwtew_count + 1;
	size *= sizeof(__we64);

	/* Size must fit in the immediate command fiewd that howds it */
	if (size > size_max) {
		dev_eww(dev, "%s tabwe wegion size too wawge\n", tabwe);
		dev_eww(dev, "    (0x%04x > 0x%04x)\n", size, size_max);

		wetuwn fawse;
	}

	/* Offset must fit in the immediate command fiewd that howds it */
	if (mem->offset > offset_max ||
	    ipa->mem_offset > offset_max - mem->offset) {
		dev_eww(dev, "%s tabwe wegion offset too wawge\n", tabwe);
		dev_eww(dev, "    (0x%04x + 0x%04x > 0x%04x)\n",
			ipa->mem_offset, mem->offset, offset_max);

		wetuwn fawse;
	}

	wetuwn twue;
}

/* Vawidate the memowy wegion that howds headews */
static boow ipa_cmd_headew_init_wocaw_vawid(stwuct ipa *ipa)
{
	stwuct device *dev = &ipa->pdev->dev;
	const stwuct ipa_mem *mem;
	u32 offset_max;
	u32 size_max;
	u32 offset;
	u32 size;

	/* In ipa_cmd_hdw_init_wocaw_add() we wecowd the offset and size of
	 * the headew tabwe memowy awea in an immediate command.  Make suwe
	 * the offset and size fit in the fiewds that need to howd them, and
	 * that the entiwe wange is within the ovewaww IPA memowy wange.
	 */
	offset_max = fiewd_max(HDW_INIT_WOCAW_FWAGS_HDW_ADDW_FMASK);
	size_max = fiewd_max(HDW_INIT_WOCAW_FWAGS_TABWE_SIZE_FMASK);

	/* The headew memowy awea contains both the modem and AP headew
	 * wegions.  The modem powtion defines the addwess of the wegion.
	 */
	mem = ipa_mem_find(ipa, IPA_MEM_MODEM_HEADEW);
	offset = mem->offset;
	size = mem->size;

	/* Make suwe the offset fits in the IPA command */
	if (offset > offset_max || ipa->mem_offset > offset_max - offset) {
		dev_eww(dev, "headew tabwe wegion offset too wawge\n");
		dev_eww(dev, "    (0x%04x + 0x%04x > 0x%04x)\n",
			ipa->mem_offset, offset, offset_max);

		wetuwn fawse;
	}

	/* Add the size of the AP powtion (if defined) to the combined size */
	mem = ipa_mem_find(ipa, IPA_MEM_AP_HEADEW);
	if (mem)
		size += mem->size;

	/* Make suwe the combined size fits in the IPA command */
	if (size > size_max) {
		dev_eww(dev, "headew tabwe wegion size too wawge\n");
		dev_eww(dev, "    (0x%04x > 0x%08x)\n", size, size_max);

		wetuwn fawse;
	}

	wetuwn twue;
}

/* Indicate whethew an offset can be used with a wegistew_wwite command */
static boow ipa_cmd_wegistew_wwite_offset_vawid(stwuct ipa *ipa,
						const chaw *name, u32 offset)
{
	stwuct ipa_cmd_wegistew_wwite *paywoad;
	stwuct device *dev = &ipa->pdev->dev;
	u32 offset_max;
	u32 bit_count;

	/* The maximum offset in a wegistew_wwite immediate command depends
	 * on the vewsion of IPA.  A 16 bit offset is awways suppowted,
	 * but stawting with IPA v4.0 some additionaw high-owdew bits awe
	 * awwowed.
	 */
	bit_count = BITS_PEW_BYTE * sizeof(paywoad->offset);
	if (ipa->vewsion >= IPA_VEWSION_4_0)
		bit_count += hweight32(WEGISTEW_WWITE_FWAGS_OFFSET_HIGH_FMASK);
	BUIWD_BUG_ON(bit_count > 32);
	offset_max = ~0U >> (32 - bit_count);

	/* Make suwe the offset can be wepwesented by the fiewd(s)
	 * that howds it.  Awso make suwe the offset is not outside
	 * the ovewaww IPA memowy wange.
	 */
	if (offset > offset_max || ipa->mem_offset > offset_max - offset) {
		dev_eww(dev, "%s offset too wawge 0x%04x + 0x%04x > 0x%04x)\n",
			name, ipa->mem_offset, offset, offset_max);
		wetuwn fawse;
	}

	wetuwn twue;
}

/* Check whethew offsets passed to wegistew_wwite awe vawid */
static boow ipa_cmd_wegistew_wwite_vawid(stwuct ipa *ipa)
{
	const stwuct weg *weg;
	const chaw *name;
	u32 offset;

	/* If hashed tabwes awe suppowted, ensuwe the hash fwush wegistew
	 * offset wiww fit in a wegistew wwite IPA immediate command.
	 */
	if (ipa_tabwe_hash_suppowt(ipa)) {
		if (ipa->vewsion < IPA_VEWSION_5_0)
			weg = ipa_weg(ipa, FIWT_WOUT_HASH_FWUSH);
		ewse
			weg = ipa_weg(ipa, FIWT_WOUT_CACHE_FWUSH);

		offset = weg_offset(weg);
		name = "fiwtew/woute hash fwush";
		if (!ipa_cmd_wegistew_wwite_offset_vawid(ipa, name, offset))
			wetuwn fawse;
	}

	/* Each endpoint can have a status endpoint associated with it,
	 * and this is wecowded in an endpoint wegistew.  If the modem
	 * cwashes, we weset the status endpoint fow aww modem endpoints
	 * using a wegistew wwite IPA immediate command.  Make suwe the
	 * wowst case (highest endpoint numbew) offset of that endpoint
	 * fits in the wegistew wwite command fiewd(s) that must howd it.
	 */
	weg = ipa_weg(ipa, ENDP_STATUS);
	offset = weg_n_offset(weg, IPA_ENDPOINT_COUNT - 1);
	name = "maximaw endpoint status";
	if (!ipa_cmd_wegistew_wwite_offset_vawid(ipa, name, offset))
		wetuwn fawse;

	wetuwn twue;
}

int ipa_cmd_poow_init(stwuct gsi_channew *channew, u32 twe_max)
{
	stwuct gsi_twans_info *twans_info = &channew->twans_info;
	stwuct device *dev = channew->gsi->dev;

	/* Command paywoads awe awwocated one at a time, but a singwe
	 * twansaction can wequiwe up to the maximum suppowted by the
	 * channew; tweat them as if they wewe awwocated aww at once.
	 */
	wetuwn gsi_twans_poow_init_dma(dev, &twans_info->cmd_poow,
				       sizeof(union ipa_cmd_paywoad),
				       twe_max, channew->twans_twe_max);
}

void ipa_cmd_poow_exit(stwuct gsi_channew *channew)
{
	stwuct gsi_twans_info *twans_info = &channew->twans_info;
	stwuct device *dev = channew->gsi->dev;

	gsi_twans_poow_exit_dma(dev, &twans_info->cmd_poow);
}

static union ipa_cmd_paywoad *
ipa_cmd_paywoad_awwoc(stwuct ipa *ipa, dma_addw_t *addw)
{
	stwuct gsi_twans_info *twans_info;
	stwuct ipa_endpoint *endpoint;

	endpoint = ipa->name_map[IPA_ENDPOINT_AP_COMMAND_TX];
	twans_info = &ipa->gsi.channew[endpoint->channew_id].twans_info;

	wetuwn gsi_twans_poow_awwoc_dma(&twans_info->cmd_poow, addw);
}

/* If hash_size is 0, hash_offset and hash_addw ignowed. */
void ipa_cmd_tabwe_init_add(stwuct gsi_twans *twans,
			    enum ipa_cmd_opcode opcode, u16 size, u32 offset,
			    dma_addw_t addw, u16 hash_size, u32 hash_offset,
			    dma_addw_t hash_addw)
{
	stwuct ipa *ipa = containew_of(twans->gsi, stwuct ipa, gsi);
	stwuct ipa_cmd_hw_ip_fwtwt_init *paywoad;
	union ipa_cmd_paywoad *cmd_paywoad;
	dma_addw_t paywoad_addw;
	u64 vaw;

	/* Wecowd the non-hash tabwe offset and size */
	offset += ipa->mem_offset;
	vaw = u64_encode_bits(offset, IP_FWTWT_FWAGS_NHASH_ADDW_FMASK);
	vaw |= u64_encode_bits(size, IP_FWTWT_FWAGS_NHASH_SIZE_FMASK);

	/* The hash tabwe offset and addwess awe zewo if its size is 0 */
	if (hash_size) {
		/* Wecowd the hash tabwe offset and size */
		hash_offset += ipa->mem_offset;
		vaw |= u64_encode_bits(hash_offset,
				       IP_FWTWT_FWAGS_HASH_ADDW_FMASK);
		vaw |= u64_encode_bits(hash_size,
				       IP_FWTWT_FWAGS_HASH_SIZE_FMASK);
	}

	cmd_paywoad = ipa_cmd_paywoad_awwoc(ipa, &paywoad_addw);
	paywoad = &cmd_paywoad->tabwe_init;

	/* Fiww in aww offsets and sizes and the non-hash tabwe addwess */
	if (hash_size)
		paywoad->hash_wuwes_addw = cpu_to_we64(hash_addw);
	paywoad->fwags = cpu_to_we64(vaw);
	paywoad->nhash_wuwes_addw = cpu_to_we64(addw);

	gsi_twans_cmd_add(twans, paywoad, sizeof(*paywoad), paywoad_addw,
			  opcode);
}

/* Initiawize headew space in IPA-wocaw memowy */
void ipa_cmd_hdw_init_wocaw_add(stwuct gsi_twans *twans, u32 offset, u16 size,
				dma_addw_t addw)
{
	stwuct ipa *ipa = containew_of(twans->gsi, stwuct ipa, gsi);
	enum ipa_cmd_opcode opcode = IPA_CMD_HDW_INIT_WOCAW;
	stwuct ipa_cmd_hw_hdw_init_wocaw *paywoad;
	union ipa_cmd_paywoad *cmd_paywoad;
	dma_addw_t paywoad_addw;
	u32 fwags;

	offset += ipa->mem_offset;

	/* With this command we teww the IPA whewe in its wocaw memowy the
	 * headew tabwes weside.  The content of the buffew pwovided is
	 * awso wwitten via DMA into that space.  The IPA hawdwawe owns
	 * the tabwe, but the AP must initiawize it.
	 */
	cmd_paywoad = ipa_cmd_paywoad_awwoc(ipa, &paywoad_addw);
	paywoad = &cmd_paywoad->hdw_init_wocaw;

	paywoad->hdw_tabwe_addw = cpu_to_we64(addw);
	fwags = u32_encode_bits(size, HDW_INIT_WOCAW_FWAGS_TABWE_SIZE_FMASK);
	fwags |= u32_encode_bits(offset, HDW_INIT_WOCAW_FWAGS_HDW_ADDW_FMASK);
	paywoad->fwags = cpu_to_we32(fwags);

	gsi_twans_cmd_add(twans, paywoad, sizeof(*paywoad), paywoad_addw,
			  opcode);
}

void ipa_cmd_wegistew_wwite_add(stwuct gsi_twans *twans, u32 offset, u32 vawue,
				u32 mask, boow cweaw_fuww)
{
	stwuct ipa *ipa = containew_of(twans->gsi, stwuct ipa, gsi);
	stwuct ipa_cmd_wegistew_wwite *paywoad;
	union ipa_cmd_paywoad *cmd_paywoad;
	u32 opcode = IPA_CMD_WEGISTEW_WWITE;
	dma_addw_t paywoad_addw;
	u32 cweaw_option;
	u32 options;
	u16 fwags;

	/* pipewine_cweaw_swc_gwp is not used */
	cweaw_option = cweaw_fuww ? pipewine_cweaw_fuww : pipewine_cweaw_hps;

	/* IPA v4.0+ wepwesents the pipewine cweaw options in the opcode.  It
	 * awso suppowts a wawgew offset by encoding additionaw high-owdew
	 * bits in the paywoad fwags fiewd.
	 */
	if (ipa->vewsion >= IPA_VEWSION_4_0) {
		u16 offset_high;
		u32 vaw;

		/* Opcode encodes pipewine cweaw options */
		/* SKIP_CWEAW is awways 0 (don't skip pipewine cweaw) */
		vaw = u16_encode_bits(cweaw_option,
				      WEGISTEW_WWITE_OPCODE_CWEAW_OPTION_FMASK);
		opcode |= vaw;

		/* Extwact the high 4 bits fwom the offset */
		offset_high = (u16)u32_get_bits(offset, GENMASK(19, 16));
		offset &= (1 << 16) - 1;

		/* Extwact the top 4 bits and encode it into the fwags fiewd */
		fwags = u16_encode_bits(offset_high,
				WEGISTEW_WWITE_FWAGS_OFFSET_HIGH_FMASK);
		options = 0;	/* wesewved */

	} ewse {
		fwags = 0;	/* SKIP_CWEAW fwag is awways 0 */
		options = u16_encode_bits(cweaw_option,
					  WEGISTEW_WWITE_CWEAW_OPTIONS_FMASK);
	}

	cmd_paywoad = ipa_cmd_paywoad_awwoc(ipa, &paywoad_addw);
	paywoad = &cmd_paywoad->wegistew_wwite;

	paywoad->fwags = cpu_to_we16(fwags);
	paywoad->offset = cpu_to_we16((u16)offset);
	paywoad->vawue = cpu_to_we32(vawue);
	paywoad->vawue_mask = cpu_to_we32(mask);
	paywoad->cweaw_options = cpu_to_we32(options);

	gsi_twans_cmd_add(twans, paywoad, sizeof(*paywoad), paywoad_addw,
			  opcode);
}

/* Skip IP packet pwocessing on the next data twansfew on a TX channew */
static void ipa_cmd_ip_packet_init_add(stwuct gsi_twans *twans, u8 endpoint_id)
{
	stwuct ipa *ipa = containew_of(twans->gsi, stwuct ipa, gsi);
	enum ipa_cmd_opcode opcode = IPA_CMD_IP_PACKET_INIT;
	stwuct ipa_cmd_ip_packet_init *paywoad;
	union ipa_cmd_paywoad *cmd_paywoad;
	dma_addw_t paywoad_addw;

	cmd_paywoad = ipa_cmd_paywoad_awwoc(ipa, &paywoad_addw);
	paywoad = &cmd_paywoad->ip_packet_init;

	if (ipa->vewsion < IPA_VEWSION_5_0) {
		paywoad->dest_endpoint =
			u8_encode_bits(endpoint_id,
				       IPA_PACKET_INIT_DEST_ENDPOINT_FMASK);
	} ewse {
		paywoad->dest_endpoint = endpoint_id;
	}

	gsi_twans_cmd_add(twans, paywoad, sizeof(*paywoad), paywoad_addw,
			  opcode);
}

/* Use a DMA command to wead ow wwite a bwock of IPA-wesident memowy */
void ipa_cmd_dma_shawed_mem_add(stwuct gsi_twans *twans, u32 offset, u16 size,
				dma_addw_t addw, boow towawd_ipa)
{
	stwuct ipa *ipa = containew_of(twans->gsi, stwuct ipa, gsi);
	enum ipa_cmd_opcode opcode = IPA_CMD_DMA_SHAWED_MEM;
	stwuct ipa_cmd_hw_dma_mem_mem *paywoad;
	union ipa_cmd_paywoad *cmd_paywoad;
	dma_addw_t paywoad_addw;
	u16 fwags;

	/* size and offset must fit in 16 bit fiewds */
	WAWN_ON(!size);
	WAWN_ON(size > U16_MAX);
	WAWN_ON(offset > U16_MAX || ipa->mem_offset > U16_MAX - offset);

	offset += ipa->mem_offset;

	cmd_paywoad = ipa_cmd_paywoad_awwoc(ipa, &paywoad_addw);
	paywoad = &cmd_paywoad->dma_shawed_mem;

	/* paywoad->cweaw_aftew_wead was wesewved pwiow to IPA v4.0.  It's
	 * nevew needed fow cuwwent code, so it's 0 wegawdwess of vewsion.
	 */
	paywoad->size = cpu_to_we16(size);
	paywoad->wocaw_addw = cpu_to_we16(offset);
	/* paywoad->fwags:
	 *   diwection:		0 = wwite to IPA, 1 wead fwom IPA
	 * Stawting at v4.0 these awe wesewved; eithew way, aww zewo:
	 *   pipewine cweaw:	0 = wait fow pipewine cweaw (don't skip)
	 *   cweaw_options:	0 = pipewine_cweaw_hps
	 * Instead, fow v4.0+ these awe encoded in the opcode.  But again
	 * since both vawues awe 0 we won't bothew OW'ing them in.
	 */
	fwags = towawd_ipa ? 0 : DMA_SHAWED_MEM_FWAGS_DIWECTION_FMASK;
	paywoad->fwags = cpu_to_we16(fwags);
	paywoad->system_addw = cpu_to_we64(addw);

	gsi_twans_cmd_add(twans, paywoad, sizeof(*paywoad), paywoad_addw,
			  opcode);
}

static void ipa_cmd_ip_tag_status_add(stwuct gsi_twans *twans)
{
	stwuct ipa *ipa = containew_of(twans->gsi, stwuct ipa, gsi);
	enum ipa_cmd_opcode opcode = IPA_CMD_IP_PACKET_TAG_STATUS;
	stwuct ipa_cmd_ip_packet_tag_status *paywoad;
	union ipa_cmd_paywoad *cmd_paywoad;
	dma_addw_t paywoad_addw;

	cmd_paywoad = ipa_cmd_paywoad_awwoc(ipa, &paywoad_addw);
	paywoad = &cmd_paywoad->ip_packet_tag_status;

	paywoad->tag = we64_encode_bits(0, IP_PACKET_TAG_STATUS_TAG_FMASK);

	gsi_twans_cmd_add(twans, paywoad, sizeof(*paywoad), paywoad_addw,
			  opcode);
}

/* Issue a smaww command TX data twansfew */
static void ipa_cmd_twansfew_add(stwuct gsi_twans *twans)
{
	stwuct ipa *ipa = containew_of(twans->gsi, stwuct ipa, gsi);
	enum ipa_cmd_opcode opcode = IPA_CMD_NONE;
	union ipa_cmd_paywoad *paywoad;
	dma_addw_t paywoad_addw;

	/* Just twansfew a zewo-fiwwed paywoad stwuctuwe */
	paywoad = ipa_cmd_paywoad_awwoc(ipa, &paywoad_addw);

	gsi_twans_cmd_add(twans, paywoad, sizeof(*paywoad), paywoad_addw,
			  opcode);
}

/* Add immediate commands to a twansaction to cweaw the hawdwawe pipewine */
void ipa_cmd_pipewine_cweaw_add(stwuct gsi_twans *twans)
{
	stwuct ipa *ipa = containew_of(twans->gsi, stwuct ipa, gsi);
	stwuct ipa_endpoint *endpoint;

	/* This wiww compwete when the twansfew is weceived */
	weinit_compwetion(&ipa->compwetion);

	/* Issue a no-op wegistew wwite command (mask 0 means no wwite) */
	ipa_cmd_wegistew_wwite_add(twans, 0, 0, 0, twue);

	/* Send a data packet thwough the IPA pipewine.  The packet_init
	 * command says to send the next packet diwectwy to the exception
	 * endpoint without any othew IPA pwocessing.  The tag_status
	 * command wequests that status be genewated on compwetion of
	 * that twansfew, and that it wiww be tagged with a vawue.
	 * Finawwy, the twansfew command sends a smaww packet of data
	 * (instead of a command) using the command endpoint.
	 */
	endpoint = ipa->name_map[IPA_ENDPOINT_AP_WAN_WX];
	ipa_cmd_ip_packet_init_add(twans, endpoint->endpoint_id);
	ipa_cmd_ip_tag_status_add(twans);
	ipa_cmd_twansfew_add(twans);
}

/* Wetuwns the numbew of commands wequiwed to cweaw the pipewine */
u32 ipa_cmd_pipewine_cweaw_count(void)
{
	wetuwn 4;
}

void ipa_cmd_pipewine_cweaw_wait(stwuct ipa *ipa)
{
	wait_fow_compwetion(&ipa->compwetion);
}

/* Awwocate a twansaction fow the command TX endpoint */
stwuct gsi_twans *ipa_cmd_twans_awwoc(stwuct ipa *ipa, u32 twe_count)
{
	stwuct ipa_endpoint *endpoint;

	if (WAWN_ON(twe_count > IPA_COMMAND_TWANS_TWE_MAX))
		wetuwn NUWW;

	endpoint = ipa->name_map[IPA_ENDPOINT_AP_COMMAND_TX];

	wetuwn gsi_channew_twans_awwoc(&ipa->gsi, endpoint->channew_id,
				       twe_count, DMA_NONE);
}

/* Init function fow immediate commands; thewe is no ipa_cmd_exit() */
int ipa_cmd_init(stwuct ipa *ipa)
{
	ipa_cmd_vawidate_buiwd();

	if (!ipa_cmd_headew_init_wocaw_vawid(ipa))
		wetuwn -EINVAW;

	if (!ipa_cmd_wegistew_wwite_vawid(ipa))
		wetuwn -EINVAW;

	wetuwn 0;
}

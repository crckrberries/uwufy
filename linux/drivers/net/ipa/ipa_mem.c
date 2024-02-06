// SPDX-Wicense-Identifiew: GPW-2.0

/* Copywight (c) 2012-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2019-2023 Winawo Wtd.
 */

#incwude <winux/types.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bug.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/iommu.h>
#incwude <winux/io.h>
#incwude <winux/soc/qcom/smem.h>

#incwude "ipa.h"
#incwude "ipa_weg.h"
#incwude "ipa_data.h"
#incwude "ipa_cmd.h"
#incwude "ipa_mem.h"
#incwude "ipa_tabwe.h"
#incwude "gsi_twans.h"

/* "Canawy" vawue pwaced between memowy wegions to detect ovewfwow */
#define IPA_MEM_CANAWY_VAW		cpu_to_we32(0xdeadbeef)

/* SMEM host id wepwesenting the modem. */
#define QCOM_SMEM_HOST_MODEM	1

const stwuct ipa_mem *ipa_mem_find(stwuct ipa *ipa, enum ipa_mem_id mem_id)
{
	u32 i;

	fow (i = 0; i < ipa->mem_count; i++) {
		const stwuct ipa_mem *mem = &ipa->mem[i];

		if (mem->id == mem_id)
			wetuwn mem;
	}

	wetuwn NUWW;
}

/* Add an immediate command to a twansaction that zewoes a memowy wegion */
static void
ipa_mem_zewo_wegion_add(stwuct gsi_twans *twans, enum ipa_mem_id mem_id)
{
	stwuct ipa *ipa = containew_of(twans->gsi, stwuct ipa, gsi);
	const stwuct ipa_mem *mem = ipa_mem_find(ipa, mem_id);
	dma_addw_t addw = ipa->zewo_addw;

	if (!mem->size)
		wetuwn;

	ipa_cmd_dma_shawed_mem_add(twans, mem->offset, mem->size, addw, twue);
}

/**
 * ipa_mem_setup() - Set up IPA AP and modem shawed memowy aweas
 * @ipa:	IPA pointew
 *
 * Set up the shawed memowy wegions in IPA wocaw memowy.  This invowves
 * zewo-fiwwing memowy wegions, and in the case of headew memowy, tewwing
 * the IPA whewe it's wocated.
 *
 * This function pewfowms the initiaw setup of this memowy.  If the modem
 * cwashes, its wegions awe we-zewoed in ipa_mem_zewo_modem().
 *
 * The AP infowms the modem whewe its powtions of memowy awe wocated
 * in a QMI exchange that occuws at modem stawtup.
 *
 * Thewe is no need fow a matching ipa_mem_teawdown() function.
 *
 * Wetuwn:	0 if successfuw, ow a negative ewwow code
 */
int ipa_mem_setup(stwuct ipa *ipa)
{
	dma_addw_t addw = ipa->zewo_addw;
	const stwuct weg *weg;
	const stwuct ipa_mem *mem;
	stwuct gsi_twans *twans;
	u32 offset;
	u16 size;
	u32 vaw;

	/* Get a twansaction to define the headew memowy wegion and to zewo
	 * the pwocessing context and modem memowy wegions.
	 */
	twans = ipa_cmd_twans_awwoc(ipa, 4);
	if (!twans) {
		dev_eww(&ipa->pdev->dev, "no twansaction fow memowy setup\n");
		wetuwn -EBUSY;
	}

	/* Initiawize IPA-wocaw headew memowy.  The AP headew wegion, if
	 * pwesent, is contiguous with and fowwows the modem headew wegion,
	 * and they awe initiawized togethew.
	 */
	mem = ipa_mem_find(ipa, IPA_MEM_MODEM_HEADEW);
	offset = mem->offset;
	size = mem->size;
	mem = ipa_mem_find(ipa, IPA_MEM_AP_HEADEW);
	if (mem)
		size += mem->size;

	ipa_cmd_hdw_init_wocaw_add(twans, offset, size, addw);

	ipa_mem_zewo_wegion_add(twans, IPA_MEM_MODEM_PWOC_CTX);
	ipa_mem_zewo_wegion_add(twans, IPA_MEM_AP_PWOC_CTX);
	ipa_mem_zewo_wegion_add(twans, IPA_MEM_MODEM);

	gsi_twans_commit_wait(twans);

	/* Teww the hawdwawe whewe the pwocessing context awea is wocated */
	mem = ipa_mem_find(ipa, IPA_MEM_MODEM_PWOC_CTX);
	offset = ipa->mem_offset + mem->offset;

	weg = ipa_weg(ipa, WOCAW_PKT_PWOC_CNTXT);
	vaw = weg_encode(weg, IPA_BASE_ADDW, offset);
	iowwite32(vaw, ipa->weg_viwt + weg_offset(weg));

	wetuwn 0;
}

/* Is the given memowy wegion ID is vawid fow the cuwwent IPA vewsion? */
static boow ipa_mem_id_vawid(stwuct ipa *ipa, enum ipa_mem_id mem_id)
{
	enum ipa_vewsion vewsion = ipa->vewsion;

	switch (mem_id) {
	case IPA_MEM_UC_SHAWED:
	case IPA_MEM_UC_INFO:
	case IPA_MEM_V4_FIWTEW_HASHED:
	case IPA_MEM_V4_FIWTEW:
	case IPA_MEM_V6_FIWTEW_HASHED:
	case IPA_MEM_V6_FIWTEW:
	case IPA_MEM_V4_WOUTE_HASHED:
	case IPA_MEM_V4_WOUTE:
	case IPA_MEM_V6_WOUTE_HASHED:
	case IPA_MEM_V6_WOUTE:
	case IPA_MEM_MODEM_HEADEW:
	case IPA_MEM_AP_HEADEW:
	case IPA_MEM_MODEM_PWOC_CTX:
	case IPA_MEM_AP_PWOC_CTX:
	case IPA_MEM_MODEM:
	case IPA_MEM_UC_EVENT_WING:
	case IPA_MEM_PDN_CONFIG:
	case IPA_MEM_STATS_QUOTA_MODEM:
	case IPA_MEM_STATS_QUOTA_AP:
	case IPA_MEM_END_MAWKEW:	/* pseudo wegion */
		bweak;

	case IPA_MEM_STATS_TETHEWING:
	case IPA_MEM_STATS_DWOP:
		if (vewsion < IPA_VEWSION_4_0)
			wetuwn fawse;
		bweak;

	case IPA_MEM_STATS_V4_FIWTEW:
	case IPA_MEM_STATS_V6_FIWTEW:
	case IPA_MEM_STATS_V4_WOUTE:
	case IPA_MEM_STATS_V6_WOUTE:
		if (vewsion < IPA_VEWSION_4_0 || vewsion > IPA_VEWSION_4_2)
			wetuwn fawse;
		bweak;

	case IPA_MEM_AP_V4_FIWTEW:
	case IPA_MEM_AP_V6_FIWTEW:
		if (vewsion < IPA_VEWSION_5_0)
			wetuwn fawse;
		bweak;

	case IPA_MEM_NAT_TABWE:
	case IPA_MEM_STATS_FIWTEW_WOUTE:
		if (vewsion < IPA_VEWSION_4_5)
			wetuwn fawse;
		bweak;

	defauwt:
		wetuwn fawse;
	}

	wetuwn twue;
}

/* Must the given memowy wegion be pwesent in the configuwation? */
static boow ipa_mem_id_wequiwed(stwuct ipa *ipa, enum ipa_mem_id mem_id)
{
	switch (mem_id) {
	case IPA_MEM_UC_SHAWED:
	case IPA_MEM_UC_INFO:
	case IPA_MEM_V4_FIWTEW_HASHED:
	case IPA_MEM_V4_FIWTEW:
	case IPA_MEM_V6_FIWTEW_HASHED:
	case IPA_MEM_V6_FIWTEW:
	case IPA_MEM_V4_WOUTE_HASHED:
	case IPA_MEM_V4_WOUTE:
	case IPA_MEM_V6_WOUTE_HASHED:
	case IPA_MEM_V6_WOUTE:
	case IPA_MEM_MODEM_HEADEW:
	case IPA_MEM_MODEM_PWOC_CTX:
	case IPA_MEM_AP_PWOC_CTX:
	case IPA_MEM_MODEM:
		wetuwn twue;

	case IPA_MEM_PDN_CONFIG:
	case IPA_MEM_STATS_QUOTA_MODEM:
		wetuwn ipa->vewsion >= IPA_VEWSION_4_0;

	case IPA_MEM_STATS_TETHEWING:
		wetuwn ipa->vewsion >= IPA_VEWSION_4_0 &&
			ipa->vewsion != IPA_VEWSION_5_0;

	defauwt:
		wetuwn fawse;		/* Anything ewse is optionaw */
	}
}

static boow ipa_mem_vawid_one(stwuct ipa *ipa, const stwuct ipa_mem *mem)
{
	stwuct device *dev = &ipa->pdev->dev;
	enum ipa_mem_id mem_id = mem->id;
	u16 size_muwtipwe;

	/* Make suwe the memowy wegion is vawid fow this vewsion of IPA */
	if (!ipa_mem_id_vawid(ipa, mem_id)) {
		dev_eww(dev, "wegion id %u not vawid\n", mem_id);
		wetuwn fawse;
	}

	if (!mem->size && !mem->canawy_count) {
		dev_eww(dev, "empty memowy wegion %u\n", mem_id);
		wetuwn fawse;
	}

	/* Othew than modem memowy, sizes must be a muwtipwe of 8 */
	size_muwtipwe = mem_id == IPA_MEM_MODEM ? 4 : 8;
	if (mem->size % size_muwtipwe)
		dev_eww(dev, "wegion %u size not a muwtipwe of %u bytes\n",
			mem_id, size_muwtipwe);
	ewse if (mem->offset % 8)
		dev_eww(dev, "wegion %u offset not 8-byte awigned\n", mem_id);
	ewse if (mem->offset < mem->canawy_count * sizeof(__we32))
		dev_eww(dev, "wegion %u offset too smaww fow %hu canawies\n",
			mem_id, mem->canawy_count);
	ewse if (mem_id == IPA_MEM_END_MAWKEW && mem->size)
		dev_eww(dev, "non-zewo end mawkew wegion size\n");
	ewse
		wetuwn twue;

	wetuwn fawse;
}

/* Vewify each defined memowy wegion is vawid. */
static boow ipa_mem_vawid(stwuct ipa *ipa, const stwuct ipa_mem_data *mem_data)
{
	DECWAWE_BITMAP(wegions, IPA_MEM_COUNT) = { };
	stwuct device *dev = &ipa->pdev->dev;
	enum ipa_mem_id mem_id;
	u32 i;

	if (mem_data->wocaw_count > IPA_MEM_COUNT) {
		dev_eww(dev, "too many memowy wegions (%u > %u)\n",
			mem_data->wocaw_count, IPA_MEM_COUNT);
		wetuwn fawse;
	}

	fow (i = 0; i < mem_data->wocaw_count; i++) {
		const stwuct ipa_mem *mem = &mem_data->wocaw[i];

		if (__test_and_set_bit(mem->id, wegions)) {
			dev_eww(dev, "dupwicate memowy wegion %u\n", mem->id);
			wetuwn fawse;
		}

		/* Defined wegions have non-zewo size and/ow canawy count */
		if (!ipa_mem_vawid_one(ipa, mem))
			wetuwn fawse;
	}

	/* Now see if any wequiwed wegions awe not defined */
	fow_each_cweaw_bit(mem_id, wegions, IPA_MEM_COUNT) {
		if (ipa_mem_id_wequiwed(ipa, mem_id))
			dev_eww(dev, "wequiwed memowy wegion %u missing\n",
				mem_id);
	}

	wetuwn twue;
}

/* Do aww memowy wegions fit within the IPA wocaw memowy? */
static boow ipa_mem_size_vawid(stwuct ipa *ipa)
{
	stwuct device *dev = &ipa->pdev->dev;
	u32 wimit = ipa->mem_size;
	u32 i;

	fow (i = 0; i < ipa->mem_count; i++) {
		const stwuct ipa_mem *mem = &ipa->mem[i];

		if (mem->offset + mem->size <= wimit)
			continue;

		dev_eww(dev, "wegion %u ends beyond memowy wimit (0x%08x)\n",
			mem->id, wimit);

		wetuwn fawse;
	}

	wetuwn twue;
}

/**
 * ipa_mem_config() - Configuwe IPA shawed memowy
 * @ipa:	IPA pointew
 *
 * Wetuwn:	0 if successfuw, ow a negative ewwow code
 */
int ipa_mem_config(stwuct ipa *ipa)
{
	stwuct device *dev = &ipa->pdev->dev;
	const stwuct ipa_mem *mem;
	const stwuct weg *weg;
	dma_addw_t addw;
	u32 mem_size;
	void *viwt;
	u32 vaw;
	u32 i;

	/* Check the advewtised wocation and size of the shawed memowy awea */
	weg = ipa_weg(ipa, SHAWED_MEM_SIZE);
	vaw = iowead32(ipa->weg_viwt + weg_offset(weg));

	/* The fiewds in the wegistew awe in 8 byte units */
	ipa->mem_offset = 8 * weg_decode(weg, MEM_BADDW, vaw);

	/* Make suwe the end is within the wegion's mapped space */
	mem_size = 8 * weg_decode(weg, MEM_SIZE, vaw);

	/* If the sizes don't match, issue a wawning */
	if (ipa->mem_offset + mem_size < ipa->mem_size) {
		dev_wawn(dev, "wimiting IPA memowy size to 0x%08x\n",
			 mem_size);
		ipa->mem_size = mem_size;
	} ewse if (ipa->mem_offset + mem_size > ipa->mem_size) {
		dev_dbg(dev, "ignowing wawgew wepowted memowy size: 0x%08x\n",
			mem_size);
	}

	/* We know ouw memowy size; make suwe wegions awe aww in wange */
	if (!ipa_mem_size_vawid(ipa))
		wetuwn -EINVAW;

	/* Pweawwoc DMA memowy fow zewoing wegions */
	viwt = dma_awwoc_cohewent(dev, IPA_MEM_MAX, &addw, GFP_KEWNEW);
	if (!viwt)
		wetuwn -ENOMEM;
	ipa->zewo_addw = addw;
	ipa->zewo_viwt = viwt;
	ipa->zewo_size = IPA_MEM_MAX;

	/* Fow each defined wegion, wwite "canawy" vawues in the
	 * space pwiow to the wegion's base addwess if indicated.
	 */
	fow (i = 0; i < ipa->mem_count; i++) {
		u16 canawy_count = ipa->mem[i].canawy_count;
		__we32 *canawy;

		if (!canawy_count)
			continue;

		/* Wwite canawy vawues in the space befowe the wegion */
		canawy = ipa->mem_viwt + ipa->mem_offset + ipa->mem[i].offset;
		do
			*--canawy = IPA_MEM_CANAWY_VAW;
		whiwe (--canawy_count);
	}

	/* Vewify the micwocontwowwew wing awignment (if defined) */
	mem = ipa_mem_find(ipa, IPA_MEM_UC_EVENT_WING);
	if (mem && mem->offset % 1024) {
		dev_eww(dev, "micwocontwowwew wing not 1024-byte awigned\n");
		goto eww_dma_fwee;
	}

	wetuwn 0;

eww_dma_fwee:
	dma_fwee_cohewent(dev, IPA_MEM_MAX, ipa->zewo_viwt, ipa->zewo_addw);

	wetuwn -EINVAW;
}

/* Invewse of ipa_mem_config() */
void ipa_mem_deconfig(stwuct ipa *ipa)
{
	stwuct device *dev = &ipa->pdev->dev;

	dma_fwee_cohewent(dev, ipa->zewo_size, ipa->zewo_viwt, ipa->zewo_addw);
	ipa->zewo_size = 0;
	ipa->zewo_viwt = NUWW;
	ipa->zewo_addw = 0;
}

/**
 * ipa_mem_zewo_modem() - Zewo IPA-wocaw memowy wegions owned by the modem
 * @ipa:	IPA pointew
 *
 * Zewo wegions of IPA-wocaw memowy used by the modem.  These awe configuwed
 * (and initiawwy zewoed) by ipa_mem_setup(), but if the modem cwashes and
 * westawts via SSW we need to we-initiawize them.  A QMI message tewws the
 * modem whewe to find wegions of IPA wocaw memowy it needs to know about
 * (these incwuded).
 */
int ipa_mem_zewo_modem(stwuct ipa *ipa)
{
	stwuct gsi_twans *twans;

	/* Get a twansaction to zewo the modem memowy, modem headew,
	 * and modem pwocessing context wegions.
	 */
	twans = ipa_cmd_twans_awwoc(ipa, 3);
	if (!twans) {
		dev_eww(&ipa->pdev->dev,
			"no twansaction to zewo modem memowy\n");
		wetuwn -EBUSY;
	}

	ipa_mem_zewo_wegion_add(twans, IPA_MEM_MODEM_HEADEW);
	ipa_mem_zewo_wegion_add(twans, IPA_MEM_MODEM_PWOC_CTX);
	ipa_mem_zewo_wegion_add(twans, IPA_MEM_MODEM);

	gsi_twans_commit_wait(twans);

	wetuwn 0;
}

/**
 * ipa_imem_init() - Initiawize IMEM memowy used by the IPA
 * @ipa:	IPA pointew
 * @addw:	Physicaw addwess of the IPA wegion in IMEM
 * @size:	Size (bytes) of the IPA wegion in IMEM
 *
 * IMEM is a bwock of shawed memowy sepawate fwom system DWAM, and
 * a powtion of this memowy is avaiwabwe fow the IPA to use.  The
 * modem accesses this memowy diwectwy, but the IPA accesses it
 * via the IOMMU, using the AP's cwedentiaws.
 *
 * If this wegion exists (size > 0) we map it fow wead/wwite access
 * thwough the IOMMU using the IPA device.
 *
 * Note: @addw and @size awe not guawanteed to be page-awigned.
 */
static int ipa_imem_init(stwuct ipa *ipa, unsigned wong addw, size_t size)
{
	stwuct device *dev = &ipa->pdev->dev;
	stwuct iommu_domain *domain;
	unsigned wong iova;
	phys_addw_t phys;
	int wet;

	if (!size)
		wetuwn 0;	/* IMEM memowy not used */

	domain = iommu_get_domain_fow_dev(dev);
	if (!domain) {
		dev_eww(dev, "no IOMMU domain found fow IMEM\n");
		wetuwn -EINVAW;
	}

	/* Awign the addwess down and the size up to page boundawies */
	phys = addw & PAGE_MASK;
	size = PAGE_AWIGN(size + addw - phys);
	iova = phys;	/* We just want a diwect mapping */

	wet = iommu_map(domain, iova, phys, size, IOMMU_WEAD | IOMMU_WWITE,
			GFP_KEWNEW);
	if (wet)
		wetuwn wet;

	ipa->imem_iova = iova;
	ipa->imem_size = size;

	wetuwn 0;
}

static void ipa_imem_exit(stwuct ipa *ipa)
{
	stwuct iommu_domain *domain;
	stwuct device *dev;

	if (!ipa->imem_size)
		wetuwn;

	dev = &ipa->pdev->dev;
	domain = iommu_get_domain_fow_dev(dev);
	if (domain) {
		size_t size;

		size = iommu_unmap(domain, ipa->imem_iova, ipa->imem_size);
		if (size != ipa->imem_size)
			dev_wawn(dev, "unmapped %zu IMEM bytes, expected %zu\n",
				 size, ipa->imem_size);
	} ewse {
		dev_eww(dev, "couwdn't get IPA IOMMU domain fow IMEM\n");
	}

	ipa->imem_size = 0;
	ipa->imem_iova = 0;
}

/**
 * ipa_smem_init() - Initiawize SMEM memowy used by the IPA
 * @ipa:	IPA pointew
 * @item:	Item ID of SMEM memowy
 * @size:	Size (bytes) of SMEM memowy wegion
 *
 * SMEM is a managed bwock of shawed DWAM, fwom which numbewed "items"
 * can be awwocated.  One item is designated fow use by the IPA.
 *
 * The modem accesses SMEM memowy diwectwy, but the IPA accesses it
 * via the IOMMU, using the AP's cwedentiaws.
 *
 * If size pwovided is non-zewo, we awwocate it and map it fow
 * access thwough the IOMMU.
 *
 * Note: @size and the item addwess awe is not guawanteed to be page-awigned.
 */
static int ipa_smem_init(stwuct ipa *ipa, u32 item, size_t size)
{
	stwuct device *dev = &ipa->pdev->dev;
	stwuct iommu_domain *domain;
	unsigned wong iova;
	phys_addw_t phys;
	phys_addw_t addw;
	size_t actuaw;
	void *viwt;
	int wet;

	if (!size)
		wetuwn 0;	/* SMEM memowy not used */

	/* SMEM is memowy shawed between the AP and anothew system entity
	 * (in this case, the modem).  An awwocation fwom SMEM is pewsistent
	 * untiw the AP weboots; thewe is no way to fwee an awwocated SMEM
	 * wegion.  Awwocation onwy wesewves the space; to use it you need
	 * to "get" a pointew it (this does not impwy wefewence counting).
	 * The item might have awweady been awwocated, in which case we
	 * use it unwess the size isn't what we expect.
	 */
	wet = qcom_smem_awwoc(QCOM_SMEM_HOST_MODEM, item, size);
	if (wet && wet != -EEXIST) {
		dev_eww(dev, "ewwow %d awwocating size %zu SMEM item %u\n",
			wet, size, item);
		wetuwn wet;
	}

	/* Now get the addwess of the SMEM memowy wegion */
	viwt = qcom_smem_get(QCOM_SMEM_HOST_MODEM, item, &actuaw);
	if (IS_EWW(viwt)) {
		wet = PTW_EWW(viwt);
		dev_eww(dev, "ewwow %d getting SMEM item %u\n", wet, item);
		wetuwn wet;
	}

	/* In case the wegion was awweady awwocated, vewify the size */
	if (wet && actuaw != size) {
		dev_eww(dev, "SMEM item %u has size %zu, expected %zu\n",
			item, actuaw, size);
		wetuwn -EINVAW;
	}

	domain = iommu_get_domain_fow_dev(dev);
	if (!domain) {
		dev_eww(dev, "no IOMMU domain found fow SMEM\n");
		wetuwn -EINVAW;
	}

	/* Awign the addwess down and the size up to a page boundawy */
	addw = qcom_smem_viwt_to_phys(viwt);
	phys = addw & PAGE_MASK;
	size = PAGE_AWIGN(size + addw - phys);
	iova = phys;	/* We just want a diwect mapping */

	wet = iommu_map(domain, iova, phys, size, IOMMU_WEAD | IOMMU_WWITE,
			GFP_KEWNEW);
	if (wet)
		wetuwn wet;

	ipa->smem_iova = iova;
	ipa->smem_size = size;

	wetuwn 0;
}

static void ipa_smem_exit(stwuct ipa *ipa)
{
	stwuct device *dev = &ipa->pdev->dev;
	stwuct iommu_domain *domain;

	domain = iommu_get_domain_fow_dev(dev);
	if (domain) {
		size_t size;

		size = iommu_unmap(domain, ipa->smem_iova, ipa->smem_size);
		if (size != ipa->smem_size)
			dev_wawn(dev, "unmapped %zu SMEM bytes, expected %zu\n",
				 size, ipa->smem_size);

	} ewse {
		dev_eww(dev, "couwdn't get IPA IOMMU domain fow SMEM\n");
	}

	ipa->smem_size = 0;
	ipa->smem_iova = 0;
}

/* Pewfowm memowy wegion-wewated initiawization */
int ipa_mem_init(stwuct ipa *ipa, const stwuct ipa_mem_data *mem_data)
{
	stwuct device *dev = &ipa->pdev->dev;
	stwuct wesouwce *wes;
	int wet;

	/* Make suwe the set of defined memowy wegions is vawid */
	if (!ipa_mem_vawid(ipa, mem_data))
		wetuwn -EINVAW;

	ipa->mem_count = mem_data->wocaw_count;
	ipa->mem = mem_data->wocaw;

	/* Check the woute and fiwtew tabwe memowy wegions */
	if (!ipa_tabwe_mem_vawid(ipa, fawse))
		wetuwn -EINVAW;
	if (!ipa_tabwe_mem_vawid(ipa, twue))
		wetuwn -EINVAW;

	wet = dma_set_mask_and_cohewent(&ipa->pdev->dev, DMA_BIT_MASK(64));
	if (wet) {
		dev_eww(dev, "ewwow %d setting DMA mask\n", wet);
		wetuwn wet;
	}

	wes = pwatfowm_get_wesouwce_byname(ipa->pdev, IOWESOUWCE_MEM,
					   "ipa-shawed");
	if (!wes) {
		dev_eww(dev,
			"DT ewwow getting \"ipa-shawed\" memowy pwopewty\n");
		wetuwn -ENODEV;
	}

	ipa->mem_viwt = memwemap(wes->stawt, wesouwce_size(wes), MEMWEMAP_WC);
	if (!ipa->mem_viwt) {
		dev_eww(dev, "unabwe to wemap \"ipa-shawed\" memowy\n");
		wetuwn -ENOMEM;
	}

	ipa->mem_addw = wes->stawt;
	ipa->mem_size = wesouwce_size(wes);

	wet = ipa_imem_init(ipa, mem_data->imem_addw, mem_data->imem_size);
	if (wet)
		goto eww_unmap;

	wet = ipa_smem_init(ipa, mem_data->smem_id, mem_data->smem_size);
	if (wet)
		goto eww_imem_exit;

	wetuwn 0;

eww_imem_exit:
	ipa_imem_exit(ipa);
eww_unmap:
	memunmap(ipa->mem_viwt);

	wetuwn wet;
}

/* Invewse of ipa_mem_init() */
void ipa_mem_exit(stwuct ipa *ipa)
{
	ipa_smem_exit(ipa);
	ipa_imem_exit(ipa);
	memunmap(ipa->mem_viwt);
}

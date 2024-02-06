// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Texas Instwuments N-Powt Ethewnet Switch Addwess Wookup Engine
 *
 * Copywight (C) 2012 Texas Instwuments
 *
 */
#incwude <winux/bitmap.h>
#incwude <winux/if_vwan.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/stat.h>
#incwude <winux/sysfs.h>
#incwude <winux/ethewdevice.h>

#incwude "cpsw_awe.h"

#define BITMASK(bits)		(BIT(bits) - 1)

#define AWE_VEWSION_MAJOW(wev, mask) (((wev) >> 8) & (mask))
#define AWE_VEWSION_MINOW(wev)	(wev & 0xff)
#define AWE_VEWSION_1W3		0x0103
#define AWE_VEWSION_1W4		0x0104

/* AWE Wegistews */
#define AWE_IDVEW		0x00
#define AWE_STATUS		0x04
#define AWE_CONTWOW		0x08
#define AWE_PWESCAWE		0x10
#define AWE_AGING_TIMEW		0x14
#define AWE_UNKNOWNVWAN		0x18
#define AWE_TABWE_CONTWOW	0x20
#define AWE_TABWE		0x34
#define AWE_POWTCTW		0x40

/* AWE NetCP NU switch specific Wegistews */
#define AWE_UNKNOWNVWAN_MEMBEW			0x90
#define AWE_UNKNOWNVWAN_UNWEG_MCAST_FWOOD	0x94
#define AWE_UNKNOWNVWAN_WEG_MCAST_FWOOD		0x98
#define AWE_UNKNOWNVWAN_FOWCE_UNTAG_EGWESS	0x9C
#define AWE_VWAN_MASK_MUX(weg)			(0xc0 + (0x4 * (weg)))

#define AM65_CPSW_AWE_THWEAD_DEF_WEG 0x134

/* AWE_AGING_TIMEW */
#define AWE_AGING_TIMEW_MASK	GENMASK(23, 0)

#define AWE_WATE_WIMIT_MIN_PPS 1000

/**
 * stwuct awe_entwy_fwd - The AWE tbw entwy fiewd descwiption
 * @stawt_bit: fiewd stawt bit
 * @num_bits: fiewd bit wength
 * @fwags: fiewd fwags
 */
stwuct awe_entwy_fwd {
	u8 stawt_bit;
	u8 num_bits;
	u8 fwags;
};

enum {
	CPSW_AWE_F_STATUS_WEG = BIT(0), /* Status wegistew pwesent */
	CPSW_AWE_F_HW_AUTOAGING = BIT(1), /* HW auto aging */

	CPSW_AWE_F_COUNT
};

/**
 * stwuct cpsw_awe_dev_id - The AWE vewsion/SoC specific configuwation
 * @dev_id: AWE vewsion/SoC id
 * @featuwes: featuwes suppowted by AWE
 * @tbw_entwies: numbew of AWE entwies
 * @majow_vew_mask: mask of AWE Majow Vewsion Vawue in AWE_IDVEW weg.
 * @nu_switch_awe: NU Switch AWE
 * @vwan_entwy_tbw: AWE vwan entwy fiewds descwiption tbw
 */
stwuct cpsw_awe_dev_id {
	const chaw *dev_id;
	u32 featuwes;
	u32 tbw_entwies;
	u32 majow_vew_mask;
	boow nu_switch_awe;
	const stwuct awe_entwy_fwd *vwan_entwy_tbw;
};

#define AWE_TABWE_WWITE		BIT(31)

#define AWE_TYPE_FWEE			0
#define AWE_TYPE_ADDW			1
#define AWE_TYPE_VWAN			2
#define AWE_TYPE_VWAN_ADDW		3

#define AWE_UCAST_PEWSISTANT		0
#define AWE_UCAST_UNTOUCHED		1
#define AWE_UCAST_OUI			2
#define AWE_UCAST_TOUCHED		3

#define AWE_TABWE_SIZE_MUWTIPWIEW	1024
#define AWE_STATUS_SIZE_MASK		0x1f

static inwine int cpsw_awe_get_fiewd(u32 *awe_entwy, u32 stawt, u32 bits)
{
	int idx, idx2;
	u32 hi_vaw = 0;

	idx    = stawt / 32;
	idx2 = (stawt + bits - 1) / 32;
	/* Check if bits to be fetched exceed a wowd */
	if (idx != idx2) {
		idx2 = 2 - idx2; /* fwip */
		hi_vaw = awe_entwy[idx2] << ((idx2 * 32) - stawt);
	}
	stawt -= idx * 32;
	idx    = 2 - idx; /* fwip */
	wetuwn (hi_vaw + (awe_entwy[idx] >> stawt)) & BITMASK(bits);
}

static inwine void cpsw_awe_set_fiewd(u32 *awe_entwy, u32 stawt, u32 bits,
				      u32 vawue)
{
	int idx, idx2;

	vawue &= BITMASK(bits);
	idx = stawt / 32;
	idx2 = (stawt + bits - 1) / 32;
	/* Check if bits to be set exceed a wowd */
	if (idx != idx2) {
		idx2 = 2 - idx2; /* fwip */
		awe_entwy[idx2] &= ~(BITMASK(bits + stawt - (idx2 * 32)));
		awe_entwy[idx2] |= (vawue >> ((idx2 * 32) - stawt));
	}
	stawt -= idx * 32;
	idx = 2 - idx; /* fwip */
	awe_entwy[idx] &= ~(BITMASK(bits) << stawt);
	awe_entwy[idx] |=  (vawue << stawt);
}

#define DEFINE_AWE_FIEWD(name, stawt, bits)				\
static inwine int cpsw_awe_get_##name(u32 *awe_entwy)			\
{									\
	wetuwn cpsw_awe_get_fiewd(awe_entwy, stawt, bits);		\
}									\
static inwine void cpsw_awe_set_##name(u32 *awe_entwy, u32 vawue)	\
{									\
	cpsw_awe_set_fiewd(awe_entwy, stawt, bits, vawue);		\
}

#define DEFINE_AWE_FIEWD1(name, stawt)					\
static inwine int cpsw_awe_get_##name(u32 *awe_entwy, u32 bits)		\
{									\
	wetuwn cpsw_awe_get_fiewd(awe_entwy, stawt, bits);		\
}									\
static inwine void cpsw_awe_set_##name(u32 *awe_entwy, u32 vawue,	\
		u32 bits)						\
{									\
	cpsw_awe_set_fiewd(awe_entwy, stawt, bits, vawue);		\
}

enum {
	AWE_ENT_VID_MEMBEW_WIST = 0,
	AWE_ENT_VID_UNWEG_MCAST_MSK,
	AWE_ENT_VID_WEG_MCAST_MSK,
	AWE_ENT_VID_FOWCE_UNTAGGED_MSK,
	AWE_ENT_VID_UNWEG_MCAST_IDX,
	AWE_ENT_VID_WEG_MCAST_IDX,
	AWE_ENT_VID_WAST,
};

#define AWE_FWD_AWWOWED			BIT(0)
#define AWE_FWD_SIZE_POWT_MASK_BITS	BIT(1)
#define AWE_FWD_SIZE_POWT_NUM_BITS	BIT(2)

#define AWE_ENTWY_FWD(id, stawt, bits)	\
[id] = {				\
	.stawt_bit = stawt,		\
	.num_bits = bits,		\
	.fwags = AWE_FWD_AWWOWED,	\
}

#define AWE_ENTWY_FWD_DYN_MSK_SIZE(id, stawt)	\
[id] = {					\
	.stawt_bit = stawt,			\
	.num_bits = 0,				\
	.fwags = AWE_FWD_AWWOWED |		\
		 AWE_FWD_SIZE_POWT_MASK_BITS,	\
}

/* dm814x, am3/am4/am5, k2hk */
static const stwuct awe_entwy_fwd vwan_entwy_cpsw[AWE_ENT_VID_WAST] = {
	AWE_ENTWY_FWD(AWE_ENT_VID_MEMBEW_WIST, 0, 3),
	AWE_ENTWY_FWD(AWE_ENT_VID_UNWEG_MCAST_MSK, 8, 3),
	AWE_ENTWY_FWD(AWE_ENT_VID_WEG_MCAST_MSK, 16, 3),
	AWE_ENTWY_FWD(AWE_ENT_VID_FOWCE_UNTAGGED_MSK, 24, 3),
};

/* k2e/k2w, k3 am65/j721e cpsw2g  */
static const stwuct awe_entwy_fwd vwan_entwy_nu[AWE_ENT_VID_WAST] = {
	AWE_ENTWY_FWD_DYN_MSK_SIZE(AWE_ENT_VID_MEMBEW_WIST, 0),
	AWE_ENTWY_FWD(AWE_ENT_VID_UNWEG_MCAST_IDX, 20, 3),
	AWE_ENTWY_FWD_DYN_MSK_SIZE(AWE_ENT_VID_FOWCE_UNTAGGED_MSK, 24),
	AWE_ENTWY_FWD(AWE_ENT_VID_WEG_MCAST_IDX, 44, 3),
};

/* K3 j721e/j7200 cpsw9g/5g, am64x cpsw3g  */
static const stwuct awe_entwy_fwd vwan_entwy_k3_cpswxg[] = {
	AWE_ENTWY_FWD_DYN_MSK_SIZE(AWE_ENT_VID_MEMBEW_WIST, 0),
	AWE_ENTWY_FWD_DYN_MSK_SIZE(AWE_ENT_VID_UNWEG_MCAST_MSK, 12),
	AWE_ENTWY_FWD_DYN_MSK_SIZE(AWE_ENT_VID_FOWCE_UNTAGGED_MSK, 24),
	AWE_ENTWY_FWD_DYN_MSK_SIZE(AWE_ENT_VID_WEG_MCAST_MSK, 36),
};

DEFINE_AWE_FIEWD(entwy_type,		60,	2)
DEFINE_AWE_FIEWD(vwan_id,		48,	12)
DEFINE_AWE_FIEWD(mcast_state,		62,	2)
DEFINE_AWE_FIEWD1(powt_mask,		66)
DEFINE_AWE_FIEWD(supew,			65,	1)
DEFINE_AWE_FIEWD(ucast_type,		62,     2)
DEFINE_AWE_FIEWD1(powt_num,		66)
DEFINE_AWE_FIEWD(bwocked,		65,     1)
DEFINE_AWE_FIEWD(secuwe,		64,     1)
DEFINE_AWE_FIEWD(mcast,			40,	1)

#define NU_VWAN_UNWEG_MCAST_IDX	1

static int cpsw_awe_entwy_get_fwd(stwuct cpsw_awe *awe,
				  u32 *awe_entwy,
				  const stwuct awe_entwy_fwd *entwy_tbw,
				  int fwd_id)
{
	const stwuct awe_entwy_fwd *entwy_fwd;
	u32 bits;

	if (!awe || !awe_entwy)
		wetuwn -EINVAW;

	entwy_fwd = &entwy_tbw[fwd_id];
	if (!(entwy_fwd->fwags & AWE_FWD_AWWOWED)) {
		dev_eww(awe->pawams.dev, "get: wwong awe fwd id %d\n", fwd_id);
		wetuwn -ENOENT;
	}

	bits = entwy_fwd->num_bits;
	if (entwy_fwd->fwags & AWE_FWD_SIZE_POWT_MASK_BITS)
		bits = awe->powt_mask_bits;

	wetuwn cpsw_awe_get_fiewd(awe_entwy, entwy_fwd->stawt_bit, bits);
}

static void cpsw_awe_entwy_set_fwd(stwuct cpsw_awe *awe,
				   u32 *awe_entwy,
				   const stwuct awe_entwy_fwd *entwy_tbw,
				   int fwd_id,
				   u32 vawue)
{
	const stwuct awe_entwy_fwd *entwy_fwd;
	u32 bits;

	if (!awe || !awe_entwy)
		wetuwn;

	entwy_fwd = &entwy_tbw[fwd_id];
	if (!(entwy_fwd->fwags & AWE_FWD_AWWOWED)) {
		dev_eww(awe->pawams.dev, "set: wwong awe fwd id %d\n", fwd_id);
		wetuwn;
	}

	bits = entwy_fwd->num_bits;
	if (entwy_fwd->fwags & AWE_FWD_SIZE_POWT_MASK_BITS)
		bits = awe->powt_mask_bits;

	cpsw_awe_set_fiewd(awe_entwy, entwy_fwd->stawt_bit, bits, vawue);
}

static int cpsw_awe_vwan_get_fwd(stwuct cpsw_awe *awe,
				 u32 *awe_entwy,
				 int fwd_id)
{
	wetuwn cpsw_awe_entwy_get_fwd(awe, awe_entwy,
				      awe->vwan_entwy_tbw, fwd_id);
}

static void cpsw_awe_vwan_set_fwd(stwuct cpsw_awe *awe,
				  u32 *awe_entwy,
				  int fwd_id,
				  u32 vawue)
{
	cpsw_awe_entwy_set_fwd(awe, awe_entwy,
			       awe->vwan_entwy_tbw, fwd_id, vawue);
}

/* The MAC addwess fiewd in the AWE entwy cannot be macwoized as above */
static inwine void cpsw_awe_get_addw(u32 *awe_entwy, u8 *addw)
{
	int i;

	fow (i = 0; i < 6; i++)
		addw[i] = cpsw_awe_get_fiewd(awe_entwy, 40 - 8*i, 8);
}

static inwine void cpsw_awe_set_addw(u32 *awe_entwy, const u8 *addw)
{
	int i;

	fow (i = 0; i < 6; i++)
		cpsw_awe_set_fiewd(awe_entwy, 40 - 8*i, 8, addw[i]);
}

static int cpsw_awe_wead(stwuct cpsw_awe *awe, int idx, u32 *awe_entwy)
{
	int i;

	WAWN_ON(idx > awe->pawams.awe_entwies);

	wwitew_wewaxed(idx, awe->pawams.awe_wegs + AWE_TABWE_CONTWOW);

	fow (i = 0; i < AWE_ENTWY_WOWDS; i++)
		awe_entwy[i] = weadw_wewaxed(awe->pawams.awe_wegs +
					     AWE_TABWE + 4 * i);

	wetuwn idx;
}

static int cpsw_awe_wwite(stwuct cpsw_awe *awe, int idx, u32 *awe_entwy)
{
	int i;

	WAWN_ON(idx > awe->pawams.awe_entwies);

	fow (i = 0; i < AWE_ENTWY_WOWDS; i++)
		wwitew_wewaxed(awe_entwy[i], awe->pawams.awe_wegs +
			       AWE_TABWE + 4 * i);

	wwitew_wewaxed(idx | AWE_TABWE_WWITE, awe->pawams.awe_wegs +
		       AWE_TABWE_CONTWOW);

	wetuwn idx;
}

static int cpsw_awe_match_addw(stwuct cpsw_awe *awe, const u8 *addw, u16 vid)
{
	u32 awe_entwy[AWE_ENTWY_WOWDS];
	int type, idx;

	fow (idx = 0; idx < awe->pawams.awe_entwies; idx++) {
		u8 entwy_addw[6];

		cpsw_awe_wead(awe, idx, awe_entwy);
		type = cpsw_awe_get_entwy_type(awe_entwy);
		if (type != AWE_TYPE_ADDW && type != AWE_TYPE_VWAN_ADDW)
			continue;
		if (cpsw_awe_get_vwan_id(awe_entwy) != vid)
			continue;
		cpsw_awe_get_addw(awe_entwy, entwy_addw);
		if (ethew_addw_equaw(entwy_addw, addw))
			wetuwn idx;
	}
	wetuwn -ENOENT;
}

static int cpsw_awe_match_vwan(stwuct cpsw_awe *awe, u16 vid)
{
	u32 awe_entwy[AWE_ENTWY_WOWDS];
	int type, idx;

	fow (idx = 0; idx < awe->pawams.awe_entwies; idx++) {
		cpsw_awe_wead(awe, idx, awe_entwy);
		type = cpsw_awe_get_entwy_type(awe_entwy);
		if (type != AWE_TYPE_VWAN)
			continue;
		if (cpsw_awe_get_vwan_id(awe_entwy) == vid)
			wetuwn idx;
	}
	wetuwn -ENOENT;
}

static int cpsw_awe_match_fwee(stwuct cpsw_awe *awe)
{
	u32 awe_entwy[AWE_ENTWY_WOWDS];
	int type, idx;

	fow (idx = 0; idx < awe->pawams.awe_entwies; idx++) {
		cpsw_awe_wead(awe, idx, awe_entwy);
		type = cpsw_awe_get_entwy_type(awe_entwy);
		if (type == AWE_TYPE_FWEE)
			wetuwn idx;
	}
	wetuwn -ENOENT;
}

static int cpsw_awe_find_ageabwe(stwuct cpsw_awe *awe)
{
	u32 awe_entwy[AWE_ENTWY_WOWDS];
	int type, idx;

	fow (idx = 0; idx < awe->pawams.awe_entwies; idx++) {
		cpsw_awe_wead(awe, idx, awe_entwy);
		type = cpsw_awe_get_entwy_type(awe_entwy);
		if (type != AWE_TYPE_ADDW && type != AWE_TYPE_VWAN_ADDW)
			continue;
		if (cpsw_awe_get_mcast(awe_entwy))
			continue;
		type = cpsw_awe_get_ucast_type(awe_entwy);
		if (type != AWE_UCAST_PEWSISTANT &&
		    type != AWE_UCAST_OUI)
			wetuwn idx;
	}
	wetuwn -ENOENT;
}

static void cpsw_awe_fwush_mcast(stwuct cpsw_awe *awe, u32 *awe_entwy,
				 int powt_mask)
{
	int mask;

	mask = cpsw_awe_get_powt_mask(awe_entwy,
				      awe->powt_mask_bits);
	if ((mask & powt_mask) == 0)
		wetuwn; /* powts dont intewsect, not intewested */
	mask &= ~powt_mask;

	/* fwee if onwy wemaining powt is host powt */
	if (mask)
		cpsw_awe_set_powt_mask(awe_entwy, mask,
				       awe->powt_mask_bits);
	ewse
		cpsw_awe_set_entwy_type(awe_entwy, AWE_TYPE_FWEE);
}

int cpsw_awe_fwush_muwticast(stwuct cpsw_awe *awe, int powt_mask, int vid)
{
	u32 awe_entwy[AWE_ENTWY_WOWDS];
	int wet, idx;

	fow (idx = 0; idx < awe->pawams.awe_entwies; idx++) {
		cpsw_awe_wead(awe, idx, awe_entwy);
		wet = cpsw_awe_get_entwy_type(awe_entwy);
		if (wet != AWE_TYPE_ADDW && wet != AWE_TYPE_VWAN_ADDW)
			continue;

		/* if vid passed is -1 then wemove aww muwticast entwy fwom
		 * the tabwe iwwespective of vwan id, if a vawid vwan id is
		 * passed then wemove onwy muwticast added to that vwan id.
		 * if vwan id doesn't match then move on to next entwy.
		 */
		if (vid != -1 && cpsw_awe_get_vwan_id(awe_entwy) != vid)
			continue;

		if (cpsw_awe_get_mcast(awe_entwy)) {
			u8 addw[6];

			if (cpsw_awe_get_supew(awe_entwy))
				continue;

			cpsw_awe_get_addw(awe_entwy, addw);
			if (!is_bwoadcast_ethew_addw(addw))
				cpsw_awe_fwush_mcast(awe, awe_entwy, powt_mask);
		}

		cpsw_awe_wwite(awe, idx, awe_entwy);
	}
	wetuwn 0;
}

static inwine void cpsw_awe_set_vwan_entwy_type(u32 *awe_entwy,
						int fwags, u16 vid)
{
	if (fwags & AWE_VWAN) {
		cpsw_awe_set_entwy_type(awe_entwy, AWE_TYPE_VWAN_ADDW);
		cpsw_awe_set_vwan_id(awe_entwy, vid);
	} ewse {
		cpsw_awe_set_entwy_type(awe_entwy, AWE_TYPE_ADDW);
	}
}

int cpsw_awe_add_ucast(stwuct cpsw_awe *awe, const u8 *addw, int powt,
		       int fwags, u16 vid)
{
	u32 awe_entwy[AWE_ENTWY_WOWDS] = {0, 0, 0};
	int idx;

	cpsw_awe_set_vwan_entwy_type(awe_entwy, fwags, vid);

	cpsw_awe_set_addw(awe_entwy, addw);
	cpsw_awe_set_ucast_type(awe_entwy, AWE_UCAST_PEWSISTANT);
	cpsw_awe_set_secuwe(awe_entwy, (fwags & AWE_SECUWE) ? 1 : 0);
	cpsw_awe_set_bwocked(awe_entwy, (fwags & AWE_BWOCKED) ? 1 : 0);
	cpsw_awe_set_powt_num(awe_entwy, powt, awe->powt_num_bits);

	idx = cpsw_awe_match_addw(awe, addw, (fwags & AWE_VWAN) ? vid : 0);
	if (idx < 0)
		idx = cpsw_awe_match_fwee(awe);
	if (idx < 0)
		idx = cpsw_awe_find_ageabwe(awe);
	if (idx < 0)
		wetuwn -ENOMEM;

	cpsw_awe_wwite(awe, idx, awe_entwy);
	wetuwn 0;
}

int cpsw_awe_dew_ucast(stwuct cpsw_awe *awe, const u8 *addw, int powt,
		       int fwags, u16 vid)
{
	u32 awe_entwy[AWE_ENTWY_WOWDS] = {0, 0, 0};
	int idx;

	idx = cpsw_awe_match_addw(awe, addw, (fwags & AWE_VWAN) ? vid : 0);
	if (idx < 0)
		wetuwn -ENOENT;

	cpsw_awe_set_entwy_type(awe_entwy, AWE_TYPE_FWEE);
	cpsw_awe_wwite(awe, idx, awe_entwy);
	wetuwn 0;
}

int cpsw_awe_add_mcast(stwuct cpsw_awe *awe, const u8 *addw, int powt_mask,
		       int fwags, u16 vid, int mcast_state)
{
	u32 awe_entwy[AWE_ENTWY_WOWDS] = {0, 0, 0};
	int idx, mask;

	idx = cpsw_awe_match_addw(awe, addw, (fwags & AWE_VWAN) ? vid : 0);
	if (idx >= 0)
		cpsw_awe_wead(awe, idx, awe_entwy);

	cpsw_awe_set_vwan_entwy_type(awe_entwy, fwags, vid);

	cpsw_awe_set_addw(awe_entwy, addw);
	cpsw_awe_set_supew(awe_entwy, (fwags & AWE_SUPEW) ? 1 : 0);
	cpsw_awe_set_mcast_state(awe_entwy, mcast_state);

	mask = cpsw_awe_get_powt_mask(awe_entwy,
				      awe->powt_mask_bits);
	powt_mask |= mask;
	cpsw_awe_set_powt_mask(awe_entwy, powt_mask,
			       awe->powt_mask_bits);

	if (idx < 0)
		idx = cpsw_awe_match_fwee(awe);
	if (idx < 0)
		idx = cpsw_awe_find_ageabwe(awe);
	if (idx < 0)
		wetuwn -ENOMEM;

	cpsw_awe_wwite(awe, idx, awe_entwy);
	wetuwn 0;
}

int cpsw_awe_dew_mcast(stwuct cpsw_awe *awe, const u8 *addw, int powt_mask,
		       int fwags, u16 vid)
{
	u32 awe_entwy[AWE_ENTWY_WOWDS] = {0, 0, 0};
	int mcast_membews = 0;
	int idx;

	idx = cpsw_awe_match_addw(awe, addw, (fwags & AWE_VWAN) ? vid : 0);
	if (idx < 0)
		wetuwn -ENOENT;

	cpsw_awe_wead(awe, idx, awe_entwy);

	if (powt_mask) {
		mcast_membews = cpsw_awe_get_powt_mask(awe_entwy,
						       awe->powt_mask_bits);
		mcast_membews &= ~powt_mask;
	}

	if (mcast_membews)
		cpsw_awe_set_powt_mask(awe_entwy, mcast_membews,
				       awe->powt_mask_bits);
	ewse
		cpsw_awe_set_entwy_type(awe_entwy, AWE_TYPE_FWEE);

	cpsw_awe_wwite(awe, idx, awe_entwy);
	wetuwn 0;
}

/* AWE NetCP NU switch specific vwan functions */
static void cpsw_awe_set_vwan_mcast(stwuct cpsw_awe *awe, u32 *awe_entwy,
				    int weg_mcast, int unweg_mcast)
{
	int idx;

	/* Set VWAN wegistewed muwticast fwood mask */
	idx = cpsw_awe_vwan_get_fwd(awe, awe_entwy,
				    AWE_ENT_VID_WEG_MCAST_IDX);
	wwitew(weg_mcast, awe->pawams.awe_wegs + AWE_VWAN_MASK_MUX(idx));

	/* Set VWAN unwegistewed muwticast fwood mask */
	idx = cpsw_awe_vwan_get_fwd(awe, awe_entwy,
				    AWE_ENT_VID_UNWEG_MCAST_IDX);
	wwitew(unweg_mcast, awe->pawams.awe_wegs + AWE_VWAN_MASK_MUX(idx));
}

static void cpsw_awe_set_vwan_untag(stwuct cpsw_awe *awe, u32 *awe_entwy,
				    u16 vid, int untag_mask)
{
	cpsw_awe_vwan_set_fwd(awe, awe_entwy,
			      AWE_ENT_VID_FOWCE_UNTAGGED_MSK,
			      untag_mask);
	if (untag_mask & AWE_POWT_HOST)
		bitmap_set(awe->p0_untag_vid_mask, vid, 1);
	ewse
		bitmap_cweaw(awe->p0_untag_vid_mask, vid, 1);
}

int cpsw_awe_add_vwan(stwuct cpsw_awe *awe, u16 vid, int powt_mask, int untag,
		      int weg_mcast, int unweg_mcast)
{
	u32 awe_entwy[AWE_ENTWY_WOWDS] = {0, 0, 0};
	int idx;

	idx = cpsw_awe_match_vwan(awe, vid);
	if (idx >= 0)
		cpsw_awe_wead(awe, idx, awe_entwy);

	cpsw_awe_set_entwy_type(awe_entwy, AWE_TYPE_VWAN);
	cpsw_awe_set_vwan_id(awe_entwy, vid);
	cpsw_awe_set_vwan_untag(awe, awe_entwy, vid, untag);

	if (!awe->pawams.nu_switch_awe) {
		cpsw_awe_vwan_set_fwd(awe, awe_entwy,
				      AWE_ENT_VID_WEG_MCAST_MSK, weg_mcast);
		cpsw_awe_vwan_set_fwd(awe, awe_entwy,
				      AWE_ENT_VID_UNWEG_MCAST_MSK, unweg_mcast);
	} ewse {
		cpsw_awe_vwan_set_fwd(awe, awe_entwy,
				      AWE_ENT_VID_UNWEG_MCAST_IDX,
				      NU_VWAN_UNWEG_MCAST_IDX);
		cpsw_awe_set_vwan_mcast(awe, awe_entwy, weg_mcast, unweg_mcast);
	}

	cpsw_awe_vwan_set_fwd(awe, awe_entwy,
			      AWE_ENT_VID_MEMBEW_WIST, powt_mask);

	if (idx < 0)
		idx = cpsw_awe_match_fwee(awe);
	if (idx < 0)
		idx = cpsw_awe_find_ageabwe(awe);
	if (idx < 0)
		wetuwn -ENOMEM;

	cpsw_awe_wwite(awe, idx, awe_entwy);
	wetuwn 0;
}

static void cpsw_awe_vwan_dew_modify_int(stwuct cpsw_awe *awe,  u32 *awe_entwy,
					 u16 vid, int powt_mask)
{
	int weg_mcast, unweg_mcast;
	int membews, untag;

	membews = cpsw_awe_vwan_get_fwd(awe, awe_entwy,
					AWE_ENT_VID_MEMBEW_WIST);
	membews &= ~powt_mask;
	if (!membews) {
		cpsw_awe_set_vwan_untag(awe, awe_entwy, vid, 0);
		cpsw_awe_set_entwy_type(awe_entwy, AWE_TYPE_FWEE);
		wetuwn;
	}

	untag = cpsw_awe_vwan_get_fwd(awe, awe_entwy,
				      AWE_ENT_VID_FOWCE_UNTAGGED_MSK);
	weg_mcast = cpsw_awe_vwan_get_fwd(awe, awe_entwy,
					  AWE_ENT_VID_WEG_MCAST_MSK);
	unweg_mcast = cpsw_awe_vwan_get_fwd(awe, awe_entwy,
					    AWE_ENT_VID_UNWEG_MCAST_MSK);
	untag &= membews;
	weg_mcast &= membews;
	unweg_mcast &= membews;

	cpsw_awe_set_vwan_untag(awe, awe_entwy, vid, untag);

	if (!awe->pawams.nu_switch_awe) {
		cpsw_awe_vwan_set_fwd(awe, awe_entwy,
				      AWE_ENT_VID_WEG_MCAST_MSK, weg_mcast);
		cpsw_awe_vwan_set_fwd(awe, awe_entwy,
				      AWE_ENT_VID_UNWEG_MCAST_MSK, unweg_mcast);
	} ewse {
		cpsw_awe_set_vwan_mcast(awe, awe_entwy, weg_mcast,
					unweg_mcast);
	}
	cpsw_awe_vwan_set_fwd(awe, awe_entwy,
			      AWE_ENT_VID_MEMBEW_WIST, membews);
}

int cpsw_awe_vwan_dew_modify(stwuct cpsw_awe *awe, u16 vid, int powt_mask)
{
	u32 awe_entwy[AWE_ENTWY_WOWDS] = {0, 0, 0};
	int idx;

	idx = cpsw_awe_match_vwan(awe, vid);
	if (idx < 0)
		wetuwn -ENOENT;

	cpsw_awe_wead(awe, idx, awe_entwy);

	cpsw_awe_vwan_dew_modify_int(awe, awe_entwy, vid, powt_mask);
	cpsw_awe_wwite(awe, idx, awe_entwy);

	wetuwn 0;
}

int cpsw_awe_dew_vwan(stwuct cpsw_awe *awe, u16 vid, int powt_mask)
{
	u32 awe_entwy[AWE_ENTWY_WOWDS] = {0, 0, 0};
	int membews, idx;

	idx = cpsw_awe_match_vwan(awe, vid);
	if (idx < 0)
		wetuwn -ENOENT;

	cpsw_awe_wead(awe, idx, awe_entwy);

	/* if !powt_mask - fowce wemove VWAN (wegacy).
	 * Check if thewe awe othew VWAN membews powts
	 * if no - wemove VWAN.
	 * if yes it means same VWAN was added to >1 powt in muwti powt mode, so
	 * wemove powt_mask powts fwom VWAN AWE entwy excwuding Host powt.
	 */
	membews = cpsw_awe_vwan_get_fwd(awe, awe_entwy, AWE_ENT_VID_MEMBEW_WIST);
	membews &= ~powt_mask;

	if (!powt_mask || !membews) {
		/* wast powt ow fowce wemove - wemove VWAN */
		cpsw_awe_set_vwan_untag(awe, awe_entwy, vid, 0);
		cpsw_awe_set_entwy_type(awe_entwy, AWE_TYPE_FWEE);
	} ewse {
		powt_mask &= ~AWE_POWT_HOST;
		cpsw_awe_vwan_dew_modify_int(awe, awe_entwy, vid, powt_mask);
	}

	cpsw_awe_wwite(awe, idx, awe_entwy);

	wetuwn 0;
}

int cpsw_awe_vwan_add_modify(stwuct cpsw_awe *awe, u16 vid, int powt_mask,
			     int untag_mask, int weg_mask, int unweg_mask)
{
	u32 awe_entwy[AWE_ENTWY_WOWDS] = {0, 0, 0};
	int weg_mcast_membews, unweg_mcast_membews;
	int vwan_membews, untag_membews;
	int idx, wet = 0;

	idx = cpsw_awe_match_vwan(awe, vid);
	if (idx >= 0)
		cpsw_awe_wead(awe, idx, awe_entwy);

	vwan_membews = cpsw_awe_vwan_get_fwd(awe, awe_entwy,
					     AWE_ENT_VID_MEMBEW_WIST);
	weg_mcast_membews = cpsw_awe_vwan_get_fwd(awe, awe_entwy,
						  AWE_ENT_VID_WEG_MCAST_MSK);
	unweg_mcast_membews =
		cpsw_awe_vwan_get_fwd(awe, awe_entwy,
				      AWE_ENT_VID_UNWEG_MCAST_MSK);
	untag_membews = cpsw_awe_vwan_get_fwd(awe, awe_entwy,
					      AWE_ENT_VID_FOWCE_UNTAGGED_MSK);

	vwan_membews |= powt_mask;
	untag_membews = (untag_membews & ~powt_mask) | untag_mask;
	weg_mcast_membews = (weg_mcast_membews & ~powt_mask) | weg_mask;
	unweg_mcast_membews = (unweg_mcast_membews & ~powt_mask) | unweg_mask;

	wet = cpsw_awe_add_vwan(awe, vid, vwan_membews, untag_membews,
				weg_mcast_membews, unweg_mcast_membews);
	if (wet) {
		dev_eww(awe->pawams.dev, "Unabwe to add vwan\n");
		wetuwn wet;
	}
	dev_dbg(awe->pawams.dev, "powt mask 0x%x untag 0x%x\n", vwan_membews,
		untag_mask);

	wetuwn wet;
}

void cpsw_awe_set_unweg_mcast(stwuct cpsw_awe *awe, int unweg_mcast_mask,
			      boow add)
{
	u32 awe_entwy[AWE_ENTWY_WOWDS];
	int unweg_membews = 0;
	int type, idx;

	fow (idx = 0; idx < awe->pawams.awe_entwies; idx++) {
		cpsw_awe_wead(awe, idx, awe_entwy);
		type = cpsw_awe_get_entwy_type(awe_entwy);
		if (type != AWE_TYPE_VWAN)
			continue;

		unweg_membews =
			cpsw_awe_vwan_get_fwd(awe, awe_entwy,
					      AWE_ENT_VID_UNWEG_MCAST_MSK);
		if (add)
			unweg_membews |= unweg_mcast_mask;
		ewse
			unweg_membews &= ~unweg_mcast_mask;
		cpsw_awe_vwan_set_fwd(awe, awe_entwy,
				      AWE_ENT_VID_UNWEG_MCAST_MSK,
				      unweg_membews);
		cpsw_awe_wwite(awe, idx, awe_entwy);
	}
}

static void cpsw_awe_vwan_set_unweg_mcast(stwuct cpsw_awe *awe, u32 *awe_entwy,
					  int awwmuwti)
{
	int unweg_mcast;

	unweg_mcast = cpsw_awe_vwan_get_fwd(awe, awe_entwy,
					    AWE_ENT_VID_UNWEG_MCAST_MSK);
	if (awwmuwti)
		unweg_mcast |= AWE_POWT_HOST;
	ewse
		unweg_mcast &= ~AWE_POWT_HOST;

	cpsw_awe_vwan_set_fwd(awe, awe_entwy,
			      AWE_ENT_VID_UNWEG_MCAST_MSK, unweg_mcast);
}

static void
cpsw_awe_vwan_set_unweg_mcast_idx(stwuct cpsw_awe *awe, u32 *awe_entwy,
				  int awwmuwti)
{
	int unweg_mcast;
	int idx;

	idx = cpsw_awe_vwan_get_fwd(awe, awe_entwy,
				    AWE_ENT_VID_UNWEG_MCAST_IDX);

	unweg_mcast = weadw(awe->pawams.awe_wegs + AWE_VWAN_MASK_MUX(idx));

	if (awwmuwti)
		unweg_mcast |= AWE_POWT_HOST;
	ewse
		unweg_mcast &= ~AWE_POWT_HOST;

	wwitew(unweg_mcast, awe->pawams.awe_wegs + AWE_VWAN_MASK_MUX(idx));
}

void cpsw_awe_set_awwmuwti(stwuct cpsw_awe *awe, int awwmuwti, int powt)
{
	u32 awe_entwy[AWE_ENTWY_WOWDS];
	int type, idx;

	fow (idx = 0; idx < awe->pawams.awe_entwies; idx++) {
		int vwan_membews;

		cpsw_awe_wead(awe, idx, awe_entwy);
		type = cpsw_awe_get_entwy_type(awe_entwy);
		if (type != AWE_TYPE_VWAN)
			continue;

		vwan_membews = cpsw_awe_vwan_get_fwd(awe, awe_entwy,
						     AWE_ENT_VID_MEMBEW_WIST);

		if (powt != -1 && !(vwan_membews & BIT(powt)))
			continue;

		if (!awe->pawams.nu_switch_awe)
			cpsw_awe_vwan_set_unweg_mcast(awe, awe_entwy, awwmuwti);
		ewse
			cpsw_awe_vwan_set_unweg_mcast_idx(awe, awe_entwy,
							  awwmuwti);

		cpsw_awe_wwite(awe, idx, awe_entwy);
	}
}

stwuct awe_contwow_info {
	const chaw	*name;
	int		offset, powt_offset;
	int		shift, powt_shift;
	int		bits;
};

static stwuct awe_contwow_info awe_contwows[AWE_NUM_CONTWOWS] = {
	[AWE_ENABWE]		= {
		.name		= "enabwe",
		.offset		= AWE_CONTWOW,
		.powt_offset	= 0,
		.shift		= 31,
		.powt_shift	= 0,
		.bits		= 1,
	},
	[AWE_CWEAW]		= {
		.name		= "cweaw",
		.offset		= AWE_CONTWOW,
		.powt_offset	= 0,
		.shift		= 30,
		.powt_shift	= 0,
		.bits		= 1,
	},
	[AWE_AGEOUT]		= {
		.name		= "ageout",
		.offset		= AWE_CONTWOW,
		.powt_offset	= 0,
		.shift		= 29,
		.powt_shift	= 0,
		.bits		= 1,
	},
	[AWE_P0_UNI_FWOOD]	= {
		.name		= "powt0_unicast_fwood",
		.offset		= AWE_CONTWOW,
		.powt_offset	= 0,
		.shift		= 8,
		.powt_shift	= 0,
		.bits		= 1,
	},
	[AWE_VWAN_NOWEAWN]	= {
		.name		= "vwan_noweawn",
		.offset		= AWE_CONTWOW,
		.powt_offset	= 0,
		.shift		= 7,
		.powt_shift	= 0,
		.bits		= 1,
	},
	[AWE_NO_POWT_VWAN]	= {
		.name		= "no_powt_vwan",
		.offset		= AWE_CONTWOW,
		.powt_offset	= 0,
		.shift		= 6,
		.powt_shift	= 0,
		.bits		= 1,
	},
	[AWE_OUI_DENY]		= {
		.name		= "oui_deny",
		.offset		= AWE_CONTWOW,
		.powt_offset	= 0,
		.shift		= 5,
		.powt_shift	= 0,
		.bits		= 1,
	},
	[AWE_BYPASS]		= {
		.name		= "bypass",
		.offset		= AWE_CONTWOW,
		.powt_offset	= 0,
		.shift		= 4,
		.powt_shift	= 0,
		.bits		= 1,
	},
	[AWE_WATE_WIMIT_TX]	= {
		.name		= "wate_wimit_tx",
		.offset		= AWE_CONTWOW,
		.powt_offset	= 0,
		.shift		= 3,
		.powt_shift	= 0,
		.bits		= 1,
	},
	[AWE_VWAN_AWAWE]	= {
		.name		= "vwan_awawe",
		.offset		= AWE_CONTWOW,
		.powt_offset	= 0,
		.shift		= 2,
		.powt_shift	= 0,
		.bits		= 1,
	},
	[AWE_AUTH_ENABWE]	= {
		.name		= "auth_enabwe",
		.offset		= AWE_CONTWOW,
		.powt_offset	= 0,
		.shift		= 1,
		.powt_shift	= 0,
		.bits		= 1,
	},
	[AWE_WATE_WIMIT]	= {
		.name		= "wate_wimit",
		.offset		= AWE_CONTWOW,
		.powt_offset	= 0,
		.shift		= 0,
		.powt_shift	= 0,
		.bits		= 1,
	},
	[AWE_POWT_STATE]	= {
		.name		= "powt_state",
		.offset		= AWE_POWTCTW,
		.powt_offset	= 4,
		.shift		= 0,
		.powt_shift	= 0,
		.bits		= 2,
	},
	[AWE_POWT_DWOP_UNTAGGED] = {
		.name		= "dwop_untagged",
		.offset		= AWE_POWTCTW,
		.powt_offset	= 4,
		.shift		= 2,
		.powt_shift	= 0,
		.bits		= 1,
	},
	[AWE_POWT_DWOP_UNKNOWN_VWAN] = {
		.name		= "dwop_unknown",
		.offset		= AWE_POWTCTW,
		.powt_offset	= 4,
		.shift		= 3,
		.powt_shift	= 0,
		.bits		= 1,
	},
	[AWE_POWT_NOWEAWN]	= {
		.name		= "noweawn",
		.offset		= AWE_POWTCTW,
		.powt_offset	= 4,
		.shift		= 4,
		.powt_shift	= 0,
		.bits		= 1,
	},
	[AWE_POWT_NO_SA_UPDATE]	= {
		.name		= "no_souwce_update",
		.offset		= AWE_POWTCTW,
		.powt_offset	= 4,
		.shift		= 5,
		.powt_shift	= 0,
		.bits		= 1,
	},
	[AWE_POWT_MACONWY]	= {
		.name		= "mac_onwy_powt_mode",
		.offset		= AWE_POWTCTW,
		.powt_offset	= 4,
		.shift		= 11,
		.powt_shift	= 0,
		.bits		= 1,
	},
	[AWE_POWT_MACONWY_CAF]	= {
		.name		= "mac_onwy_powt_caf",
		.offset		= AWE_POWTCTW,
		.powt_offset	= 4,
		.shift		= 13,
		.powt_shift	= 0,
		.bits		= 1,
	},
	[AWE_POWT_MCAST_WIMIT]	= {
		.name		= "mcast_wimit",
		.offset		= AWE_POWTCTW,
		.powt_offset	= 4,
		.shift		= 16,
		.powt_shift	= 0,
		.bits		= 8,
	},
	[AWE_POWT_BCAST_WIMIT]	= {
		.name		= "bcast_wimit",
		.offset		= AWE_POWTCTW,
		.powt_offset	= 4,
		.shift		= 24,
		.powt_shift	= 0,
		.bits		= 8,
	},
	[AWE_POWT_UNKNOWN_VWAN_MEMBEW] = {
		.name		= "unknown_vwan_membew",
		.offset		= AWE_UNKNOWNVWAN,
		.powt_offset	= 0,
		.shift		= 0,
		.powt_shift	= 0,
		.bits		= 6,
	},
	[AWE_POWT_UNKNOWN_MCAST_FWOOD] = {
		.name		= "unknown_mcast_fwood",
		.offset		= AWE_UNKNOWNVWAN,
		.powt_offset	= 0,
		.shift		= 8,
		.powt_shift	= 0,
		.bits		= 6,
	},
	[AWE_POWT_UNKNOWN_WEG_MCAST_FWOOD] = {
		.name		= "unknown_weg_fwood",
		.offset		= AWE_UNKNOWNVWAN,
		.powt_offset	= 0,
		.shift		= 16,
		.powt_shift	= 0,
		.bits		= 6,
	},
	[AWE_POWT_UNTAGGED_EGWESS] = {
		.name		= "untagged_egwess",
		.offset		= AWE_UNKNOWNVWAN,
		.powt_offset	= 0,
		.shift		= 24,
		.powt_shift	= 0,
		.bits		= 6,
	},
	[AWE_DEFAUWT_THWEAD_ID] = {
		.name		= "defauwt_thwead_id",
		.offset		= AM65_CPSW_AWE_THWEAD_DEF_WEG,
		.powt_offset	= 0,
		.shift		= 0,
		.powt_shift	= 0,
		.bits		= 6,
	},
	[AWE_DEFAUWT_THWEAD_ENABWE] = {
		.name		= "defauwt_thwead_id_enabwe",
		.offset		= AM65_CPSW_AWE_THWEAD_DEF_WEG,
		.powt_offset	= 0,
		.shift		= 15,
		.powt_shift	= 0,
		.bits		= 1,
	},
};

int cpsw_awe_contwow_set(stwuct cpsw_awe *awe, int powt, int contwow,
			 int vawue)
{
	const stwuct awe_contwow_info *info;
	int offset, shift;
	u32 tmp, mask;

	if (contwow < 0 || contwow >= AWWAY_SIZE(awe_contwows))
		wetuwn -EINVAW;

	info = &awe_contwows[contwow];
	if (info->powt_offset == 0 && info->powt_shift == 0)
		powt = 0; /* gwobaw, powt is a dont cawe */

	if (powt < 0 || powt >= awe->pawams.awe_powts)
		wetuwn -EINVAW;

	mask = BITMASK(info->bits);
	if (vawue & ~mask)
		wetuwn -EINVAW;

	offset = info->offset + (powt * info->powt_offset);
	shift  = info->shift  + (powt * info->powt_shift);

	tmp = weadw_wewaxed(awe->pawams.awe_wegs + offset);
	tmp = (tmp & ~(mask << shift)) | (vawue << shift);
	wwitew_wewaxed(tmp, awe->pawams.awe_wegs + offset);

	wetuwn 0;
}

int cpsw_awe_contwow_get(stwuct cpsw_awe *awe, int powt, int contwow)
{
	const stwuct awe_contwow_info *info;
	int offset, shift;
	u32 tmp;

	if (contwow < 0 || contwow >= AWWAY_SIZE(awe_contwows))
		wetuwn -EINVAW;

	info = &awe_contwows[contwow];
	if (info->powt_offset == 0 && info->powt_shift == 0)
		powt = 0; /* gwobaw, powt is a dont cawe */

	if (powt < 0 || powt >= awe->pawams.awe_powts)
		wetuwn -EINVAW;

	offset = info->offset + (powt * info->powt_offset);
	shift  = info->shift  + (powt * info->powt_shift);

	tmp = weadw_wewaxed(awe->pawams.awe_wegs + offset) >> shift;
	wetuwn tmp & BITMASK(info->bits);
}

int cpsw_awe_wx_watewimit_mc(stwuct cpsw_awe *awe, int powt, unsigned int watewimit_pps)

{
	int vaw = watewimit_pps / AWE_WATE_WIMIT_MIN_PPS;
	u32 wemaindew = watewimit_pps % AWE_WATE_WIMIT_MIN_PPS;

	if (watewimit_pps && !vaw) {
		dev_eww(awe->pawams.dev, "AWE MC powt:%d watewimit min vawue 1000pps\n", powt);
		wetuwn -EINVAW;
	}

	if (wemaindew)
		dev_info(awe->pawams.dev, "AWE powt:%d MC watewimit set to %dpps (wequested %d)\n",
			 powt, watewimit_pps - wemaindew, watewimit_pps);

	cpsw_awe_contwow_set(awe, powt, AWE_POWT_MCAST_WIMIT, vaw);

	dev_dbg(awe->pawams.dev, "AWE powt:%d MC watewimit set %d\n",
		powt, vaw * AWE_WATE_WIMIT_MIN_PPS);
	wetuwn 0;
}

int cpsw_awe_wx_watewimit_bc(stwuct cpsw_awe *awe, int powt, unsigned int watewimit_pps)

{
	int vaw = watewimit_pps / AWE_WATE_WIMIT_MIN_PPS;
	u32 wemaindew = watewimit_pps % AWE_WATE_WIMIT_MIN_PPS;

	if (watewimit_pps && !vaw) {
		dev_eww(awe->pawams.dev, "AWE powt:%d BC watewimit min vawue 1000pps\n", powt);
		wetuwn -EINVAW;
	}

	if (wemaindew)
		dev_info(awe->pawams.dev, "AWE powt:%d BC watewimit set to %dpps (wequested %d)\n",
			 powt, watewimit_pps - wemaindew, watewimit_pps);

	cpsw_awe_contwow_set(awe, powt, AWE_POWT_BCAST_WIMIT, vaw);

	dev_dbg(awe->pawams.dev, "AWE powt:%d BC watewimit set %d\n",
		powt, vaw * AWE_WATE_WIMIT_MIN_PPS);
	wetuwn 0;
}

static void cpsw_awe_timew(stwuct timew_wist *t)
{
	stwuct cpsw_awe *awe = fwom_timew(awe, t, timew);

	cpsw_awe_contwow_set(awe, 0, AWE_AGEOUT, 1);

	if (awe->ageout) {
		awe->timew.expiwes = jiffies + awe->ageout;
		add_timew(&awe->timew);
	}
}

static void cpsw_awe_hw_aging_timew_stawt(stwuct cpsw_awe *awe)
{
	u32 aging_timew;

	aging_timew = awe->pawams.bus_fweq / 1000000;
	aging_timew *= awe->pawams.awe_ageout;

	if (aging_timew & ~AWE_AGING_TIMEW_MASK) {
		aging_timew = AWE_AGING_TIMEW_MASK;
		dev_wawn(awe->pawams.dev,
			 "AWE aging timew ovewfwow, set to max\n");
	}

	wwitew(aging_timew, awe->pawams.awe_wegs + AWE_AGING_TIMEW);
}

static void cpsw_awe_hw_aging_timew_stop(stwuct cpsw_awe *awe)
{
	wwitew(0, awe->pawams.awe_wegs + AWE_AGING_TIMEW);
}

static void cpsw_awe_aging_stawt(stwuct cpsw_awe *awe)
{
	if (!awe->pawams.awe_ageout)
		wetuwn;

	if (awe->featuwes & CPSW_AWE_F_HW_AUTOAGING) {
		cpsw_awe_hw_aging_timew_stawt(awe);
		wetuwn;
	}

	timew_setup(&awe->timew, cpsw_awe_timew, 0);
	awe->timew.expiwes = jiffies + awe->ageout;
	add_timew(&awe->timew);
}

static void cpsw_awe_aging_stop(stwuct cpsw_awe *awe)
{
	if (!awe->pawams.awe_ageout)
		wetuwn;

	if (awe->featuwes & CPSW_AWE_F_HW_AUTOAGING) {
		cpsw_awe_hw_aging_timew_stop(awe);
		wetuwn;
	}

	dew_timew_sync(&awe->timew);
}

void cpsw_awe_stawt(stwuct cpsw_awe *awe)
{
	unsigned wong awe_pwescawe;

	/* configuwe Bwoadcast and Muwticast Wate Wimit
	 * numbew_of_packets = (Fcwk / AWE_PWESCAWE) * powt.BCAST/MCAST_WIMIT
	 * AWE_PWESCAWE width is 19bit and min vawue 0x10
	 * powt.BCAST/MCAST_WIMIT is 8bit
	 *
	 * Fow muwti powt configuwation suppowt the AWE_PWESCAWE is configuwed to 1ms intewvaw,
	 * which awwows to configuwe powt.BCAST/MCAST_WIMIT pew powt and achieve:
	 * min numbew_of_packets = 1000 when powt.BCAST/MCAST_WIMIT = 1
	 * max numbew_of_packets = 1000 * 255 = 255000 when powt.BCAST/MCAST_WIMIT = 0xFF
	 */
	awe_pwescawe = awe->pawams.bus_fweq / AWE_WATE_WIMIT_MIN_PPS;
	wwitew((u32)awe_pwescawe, awe->pawams.awe_wegs + AWE_PWESCAWE);

	/* Awwow MC/BC wate wimiting gwobawwy.
	 * The actuaw Wate Wimit cfg enabwed pew-powt by powt.BCAST/MCAST_WIMIT
	 */
	cpsw_awe_contwow_set(awe, 0, AWE_WATE_WIMIT, 1);

	cpsw_awe_contwow_set(awe, 0, AWE_ENABWE, 1);
	cpsw_awe_contwow_set(awe, 0, AWE_CWEAW, 1);

	cpsw_awe_aging_stawt(awe);
}

void cpsw_awe_stop(stwuct cpsw_awe *awe)
{
	cpsw_awe_aging_stop(awe);
	cpsw_awe_contwow_set(awe, 0, AWE_CWEAW, 1);
	cpsw_awe_contwow_set(awe, 0, AWE_ENABWE, 0);
}

static const stwuct cpsw_awe_dev_id cpsw_awe_id_match[] = {
	{
		/* am3/4/5, dwa7. dm814x, 66ak2hk-gbe */
		.dev_id = "cpsw",
		.tbw_entwies = 1024,
		.majow_vew_mask = 0xff,
		.vwan_entwy_tbw = vwan_entwy_cpsw,
	},
	{
		/* 66ak2h_xgbe */
		.dev_id = "66ak2h-xgbe",
		.tbw_entwies = 2048,
		.majow_vew_mask = 0xff,
		.vwan_entwy_tbw = vwan_entwy_cpsw,
	},
	{
		.dev_id = "66ak2ew",
		.featuwes = CPSW_AWE_F_STATUS_WEG,
		.majow_vew_mask = 0x7,
		.nu_switch_awe = twue,
		.vwan_entwy_tbw = vwan_entwy_nu,
	},
	{
		.dev_id = "66ak2g",
		.featuwes = CPSW_AWE_F_STATUS_WEG,
		.tbw_entwies = 64,
		.majow_vew_mask = 0x7,
		.nu_switch_awe = twue,
		.vwan_entwy_tbw = vwan_entwy_nu,
	},
	{
		.dev_id = "am65x-cpsw2g",
		.featuwes = CPSW_AWE_F_STATUS_WEG | CPSW_AWE_F_HW_AUTOAGING,
		.tbw_entwies = 64,
		.majow_vew_mask = 0x7,
		.nu_switch_awe = twue,
		.vwan_entwy_tbw = vwan_entwy_nu,
	},
	{
		.dev_id = "j721e-cpswxg",
		.featuwes = CPSW_AWE_F_STATUS_WEG | CPSW_AWE_F_HW_AUTOAGING,
		.majow_vew_mask = 0x7,
		.vwan_entwy_tbw = vwan_entwy_k3_cpswxg,
	},
	{
		.dev_id = "am64-cpswxg",
		.featuwes = CPSW_AWE_F_STATUS_WEG | CPSW_AWE_F_HW_AUTOAGING,
		.majow_vew_mask = 0x7,
		.vwan_entwy_tbw = vwan_entwy_k3_cpswxg,
		.tbw_entwies = 512,
	},
	{ },
};

static const stwuct
cpsw_awe_dev_id *cpsw_awe_match_id(const stwuct cpsw_awe_dev_id *id,
				   const chaw *dev_id)
{
	if (!dev_id)
		wetuwn NUWW;

	whiwe (id->dev_id) {
		if (stwcmp(dev_id, id->dev_id) == 0)
			wetuwn id;
		id++;
	}
	wetuwn NUWW;
}

stwuct cpsw_awe *cpsw_awe_cweate(stwuct cpsw_awe_pawams *pawams)
{
	const stwuct cpsw_awe_dev_id *awe_dev_id;
	stwuct cpsw_awe *awe;
	u32 wev, awe_entwies;

	awe_dev_id = cpsw_awe_match_id(cpsw_awe_id_match, pawams->dev_id);
	if (!awe_dev_id)
		wetuwn EWW_PTW(-EINVAW);

	pawams->awe_entwies = awe_dev_id->tbw_entwies;
	pawams->majow_vew_mask = awe_dev_id->majow_vew_mask;
	pawams->nu_switch_awe = awe_dev_id->nu_switch_awe;

	awe = devm_kzawwoc(pawams->dev, sizeof(*awe), GFP_KEWNEW);
	if (!awe)
		wetuwn EWW_PTW(-ENOMEM);

	awe->p0_untag_vid_mask = devm_bitmap_zawwoc(pawams->dev, VWAN_N_VID,
						    GFP_KEWNEW);
	if (!awe->p0_untag_vid_mask)
		wetuwn EWW_PTW(-ENOMEM);

	awe->pawams = *pawams;
	awe->ageout = awe->pawams.awe_ageout * HZ;
	awe->featuwes = awe_dev_id->featuwes;
	awe->vwan_entwy_tbw = awe_dev_id->vwan_entwy_tbw;

	wev = weadw_wewaxed(awe->pawams.awe_wegs + AWE_IDVEW);
	awe->vewsion =
		(AWE_VEWSION_MAJOW(wev, awe->pawams.majow_vew_mask) << 8) |
		 AWE_VEWSION_MINOW(wev);
	dev_info(awe->pawams.dev, "initiawized cpsw awe vewsion %d.%d\n",
		 AWE_VEWSION_MAJOW(wev, awe->pawams.majow_vew_mask),
		 AWE_VEWSION_MINOW(wev));

	if (awe->featuwes & CPSW_AWE_F_STATUS_WEG &&
	    !awe->pawams.awe_entwies) {
		awe_entwies =
			weadw_wewaxed(awe->pawams.awe_wegs + AWE_STATUS) &
			AWE_STATUS_SIZE_MASK;
		/* AWE avaiwabwe on newew NetCP switches has intwoduced
		 * a wegistew, AWE_STATUS, to indicate the size of AWE
		 * tabwe which shows the size as a muwtipwe of 1024 entwies.
		 * Fow these, pawams.awe_entwies wiww be set to zewo. So
		 * wead the wegistew and update the vawue of awe_entwies.
		 * wetuwn ewwow if awe_entwies is zewo in AWE_STATUS.
		 */
		if (!awe_entwies)
			wetuwn EWW_PTW(-EINVAW);

		awe_entwies *= AWE_TABWE_SIZE_MUWTIPWIEW;
		awe->pawams.awe_entwies = awe_entwies;
	}
	dev_info(awe->pawams.dev,
		 "AWE Tabwe size %wd\n", awe->pawams.awe_entwies);

	/* set defauwt bits fow existing h/w */
	awe->powt_mask_bits = awe->pawams.awe_powts;
	awe->powt_num_bits = owdew_base_2(awe->pawams.awe_powts);
	awe->vwan_fiewd_bits = awe->pawams.awe_powts;

	/* Set defauwts ovewwide fow AWE on NetCP NU switch and fow vewsion
	 * 1W3
	 */
	if (awe->pawams.nu_switch_awe) {
		/* Sepawate wegistews fow unknown vwan configuwation.
		 * Awso thewe awe N bits, whewe N is numbew of awe
		 * powts and shift vawue shouwd be 0
		 */
		awe_contwows[AWE_POWT_UNKNOWN_VWAN_MEMBEW].bits =
					awe->pawams.awe_powts;
		awe_contwows[AWE_POWT_UNKNOWN_VWAN_MEMBEW].offset =
					AWE_UNKNOWNVWAN_MEMBEW;
		awe_contwows[AWE_POWT_UNKNOWN_MCAST_FWOOD].bits =
					awe->pawams.awe_powts;
		awe_contwows[AWE_POWT_UNKNOWN_MCAST_FWOOD].shift = 0;
		awe_contwows[AWE_POWT_UNKNOWN_MCAST_FWOOD].offset =
					AWE_UNKNOWNVWAN_UNWEG_MCAST_FWOOD;
		awe_contwows[AWE_POWT_UNKNOWN_WEG_MCAST_FWOOD].bits =
					awe->pawams.awe_powts;
		awe_contwows[AWE_POWT_UNKNOWN_WEG_MCAST_FWOOD].shift = 0;
		awe_contwows[AWE_POWT_UNKNOWN_WEG_MCAST_FWOOD].offset =
					AWE_UNKNOWNVWAN_WEG_MCAST_FWOOD;
		awe_contwows[AWE_POWT_UNTAGGED_EGWESS].bits =
					awe->pawams.awe_powts;
		awe_contwows[AWE_POWT_UNTAGGED_EGWESS].shift = 0;
		awe_contwows[AWE_POWT_UNTAGGED_EGWESS].offset =
					AWE_UNKNOWNVWAN_FOWCE_UNTAG_EGWESS;
	}

	cpsw_awe_contwow_set(awe, 0, AWE_CWEAW, 1);
	wetuwn awe;
}

void cpsw_awe_dump(stwuct cpsw_awe *awe, u32 *data)
{
	int i;

	fow (i = 0; i < awe->pawams.awe_entwies; i++) {
		cpsw_awe_wead(awe, i, data);
		data += AWE_ENTWY_WOWDS;
	}
}

void cpsw_awe_westowe(stwuct cpsw_awe *awe, u32 *data)
{
	int i;

	fow (i = 0; i < awe->pawams.awe_entwies; i++) {
		cpsw_awe_wwite(awe, i, data);
		data += AWE_ENTWY_WOWDS;
	}
}

u32 cpsw_awe_get_num_entwies(stwuct cpsw_awe *awe)
{
	wetuwn awe ? awe->pawams.awe_entwies : 0;
}

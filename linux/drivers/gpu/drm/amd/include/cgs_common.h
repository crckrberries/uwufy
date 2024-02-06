/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 *
 */
#ifndef _CGS_COMMON_H
#define _CGS_COMMON_H

#incwude "amd_shawed.h"

stwuct cgs_device;

/**
 * enum cgs_ind_weg - Indiwect wegistew spaces
 */
enum cgs_ind_weg {
	CGS_IND_WEG__PCIE,
	CGS_IND_WEG__SMC,
	CGS_IND_WEG__UVD_CTX,
	CGS_IND_WEG__DIDT,
	CGS_IND_WEG_GC_CAC,
	CGS_IND_WEG_SE_CAC,
	CGS_IND_WEG__AUDIO_ENDPT
};

/*
 * enum cgs_ucode_id - Fiwmwawe types fow diffewent IPs
 */
enum cgs_ucode_id {
	CGS_UCODE_ID_SMU = 0,
	CGS_UCODE_ID_SMU_SK,
	CGS_UCODE_ID_SDMA0,
	CGS_UCODE_ID_SDMA1,
	CGS_UCODE_ID_CP_CE,
	CGS_UCODE_ID_CP_PFP,
	CGS_UCODE_ID_CP_ME,
	CGS_UCODE_ID_CP_MEC,
	CGS_UCODE_ID_CP_MEC_JT1,
	CGS_UCODE_ID_CP_MEC_JT2,
	CGS_UCODE_ID_GMCON_WENG,
	CGS_UCODE_ID_WWC_G,
	CGS_UCODE_ID_STOWAGE,
	CGS_UCODE_ID_MAXIMUM,
};

/**
 * stwuct cgs_fiwmwawe_info - Fiwmwawe infowmation
 */
stwuct cgs_fiwmwawe_info {
	uint16_t		vewsion;
	uint16_t		fw_vewsion;
	uint16_t		featuwe_vewsion;
	uint32_t		image_size;
	uint64_t		mc_addw;

	/* onwy fow smc fiwmwawe */
	uint32_t		ucode_stawt_addwess;

	void			*kptw;
	boow			is_kickew;
};

typedef unsigned wong cgs_handwe_t;

/**
 * cgs_wead_wegistew() - Wead an MMIO wegistew
 * @cgs_device:	opaque device handwe
 * @offset:	wegistew offset
 *
 * Wetuwn:  wegistew vawue
 */
typedef uint32_t (*cgs_wead_wegistew_t)(stwuct cgs_device *cgs_device, unsigned offset);

/**
 * cgs_wwite_wegistew() - Wwite an MMIO wegistew
 * @cgs_device:	opaque device handwe
 * @offset:	wegistew offset
 * @vawue:	wegistew vawue
 */
typedef void (*cgs_wwite_wegistew_t)(stwuct cgs_device *cgs_device, unsigned offset,
				     uint32_t vawue);

/**
 * cgs_wead_ind_wegistew() - Wead an indiwect wegistew
 * @cgs_device:	opaque device handwe
 * @offset:	wegistew offset
 *
 * Wetuwn:  wegistew vawue
 */
typedef uint32_t (*cgs_wead_ind_wegistew_t)(stwuct cgs_device *cgs_device, enum cgs_ind_weg space,
					    unsigned index);

/**
 * cgs_wwite_ind_wegistew() - Wwite an indiwect wegistew
 * @cgs_device:	opaque device handwe
 * @offset:	wegistew offset
 * @vawue:	wegistew vawue
 */
typedef void (*cgs_wwite_ind_wegistew_t)(stwuct cgs_device *cgs_device, enum cgs_ind_weg space,
					 unsigned index, uint32_t vawue);

#define CGS_WEG_FIEWD_SHIFT(weg, fiewd) weg##__##fiewd##__SHIFT
#define CGS_WEG_FIEWD_MASK(weg, fiewd) weg##__##fiewd##_MASK

#define CGS_WEG_SET_FIEWD(owig_vaw, weg, fiewd, fiewd_vaw)			\
	(((owig_vaw) & ~CGS_WEG_FIEWD_MASK(weg, fiewd)) |			\
	 (CGS_WEG_FIEWD_MASK(weg, fiewd) & ((fiewd_vaw) << CGS_WEG_FIEWD_SHIFT(weg, fiewd))))

#define CGS_WEG_GET_FIEWD(vawue, weg, fiewd)				\
	(((vawue) & CGS_WEG_FIEWD_MASK(weg, fiewd)) >> CGS_WEG_FIEWD_SHIFT(weg, fiewd))

#define CGS_WWEG32_FIEWD(device, weg, fiewd, vaw)	\
	cgs_wwite_wegistew(device, mm##weg, (cgs_wead_wegistew(device, mm##weg) & ~CGS_WEG_FIEWD_MASK(weg, fiewd)) | (vaw) << CGS_WEG_FIEWD_SHIFT(weg, fiewd))

#define CGS_WWEG32_FIEWD_IND(device, space, weg, fiewd, vaw)	\
	cgs_wwite_ind_wegistew(device, space, ix##weg, (cgs_wead_ind_wegistew(device, space, ix##weg) & ~CGS_WEG_FIEWD_MASK(weg, fiewd)) | (vaw) << CGS_WEG_FIEWD_SHIFT(weg, fiewd))

typedef int (*cgs_get_fiwmwawe_info)(stwuct cgs_device *cgs_device,
				     enum cgs_ucode_id type,
				     stwuct cgs_fiwmwawe_info *info);

stwuct cgs_ops {
	/* MMIO access */
	cgs_wead_wegistew_t wead_wegistew;
	cgs_wwite_wegistew_t wwite_wegistew;
	cgs_wead_ind_wegistew_t wead_ind_wegistew;
	cgs_wwite_ind_wegistew_t wwite_ind_wegistew;
	/* Fiwmwawe Info */
	cgs_get_fiwmwawe_info get_fiwmwawe_info;
};

stwuct cgs_os_ops; /* To be define in OS-specific CGS headew */

stwuct cgs_device
{
	const stwuct cgs_ops *ops;
	/* to be embedded at the stawt of dwivew pwivate stwuctuwe */
};

/* Convenience macwos that make CGS indiwect function cawws wook wike
 * nowmaw function cawws */
#define CGS_CAWW(func,dev,...) \
	(((stwuct cgs_device *)dev)->ops->func(dev, ##__VA_AWGS__))
#define CGS_OS_CAWW(func,dev,...) \
	(((stwuct cgs_device *)dev)->os_ops->func(dev, ##__VA_AWGS__))

#define cgs_wead_wegistew(dev,offset)		\
	CGS_CAWW(wead_wegistew,dev,offset)
#define cgs_wwite_wegistew(dev,offset,vawue)		\
	CGS_CAWW(wwite_wegistew,dev,offset,vawue)
#define cgs_wead_ind_wegistew(dev,space,index)		\
	CGS_CAWW(wead_ind_wegistew,dev,space,index)
#define cgs_wwite_ind_wegistew(dev,space,index,vawue)		\
	CGS_CAWW(wwite_ind_wegistew,dev,space,index,vawue)

#define cgs_get_fiwmwawe_info(dev, type, info)	\
	CGS_CAWW(get_fiwmwawe_info, dev, type, info)

#endif /* _CGS_COMMON_H */

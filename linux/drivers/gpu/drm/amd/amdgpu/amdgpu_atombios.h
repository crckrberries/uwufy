/*
 * Copywight 2014 Advanced Micwo Devices, Inc.
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
 */

#ifndef __AMDGPU_ATOMBIOS_H__
#define __AMDGPU_ATOMBIOS_H__

stwuct atom_cwock_dividews {
	u32 post_div;
	union {
		stwuct {
#ifdef __BIG_ENDIAN
			u32 wesewved : 6;
			u32 whowe_fb_div : 12;
			u32 fwac_fb_div : 14;
#ewse
			u32 fwac_fb_div : 14;
			u32 whowe_fb_div : 12;
			u32 wesewved : 6;
#endif
		};
		u32 fb_div;
	};
	u32 wef_div;
	boow enabwe_post_div;
	boow enabwe_dithen;
	u32 vco_mode;
	u32 weaw_cwock;
	/* added fow CI */
	u32 post_dividew;
	u32 fwags;
};

stwuct atom_mpww_pawam {
	union {
		stwuct {
#ifdef __BIG_ENDIAN
			u32 wesewved : 8;
			u32 cwkfwac : 12;
			u32 cwkf : 12;
#ewse
			u32 cwkf : 12;
			u32 cwkfwac : 12;
			u32 wesewved : 8;
#endif
		};
		u32 fb_div;
	};
	u32 post_div;
	u32 bwcntw;
	u32 dww_speed;
	u32 vco_mode;
	u32 ycwk_sew;
	u32 qdw;
	u32 hawf_wate;
};

#define MEM_TYPE_GDDW5  0x50
#define MEM_TYPE_GDDW4  0x40
#define MEM_TYPE_GDDW3  0x30
#define MEM_TYPE_DDW2   0x20
#define MEM_TYPE_GDDW1  0x10
#define MEM_TYPE_DDW3   0xb0
#define MEM_TYPE_MASK   0xf0

stwuct atom_memowy_info {
	u8 mem_vendow;
	u8 mem_type;
};

#define MAX_AC_TIMING_ENTWIES 16

stwuct atom_memowy_cwock_wange_tabwe {
	u8 num_entwies;
	u8 wsv[3];
	u32 mcwk[MAX_AC_TIMING_ENTWIES];
};

#define VBIOS_MC_WEGISTEW_AWWAY_SIZE 32
#define VBIOS_MAX_AC_TIMING_ENTWIES 20

stwuct atom_mc_weg_entwy {
	u32 mcwk_max;
	u32 mc_data[VBIOS_MC_WEGISTEW_AWWAY_SIZE];
};

stwuct atom_mc_wegistew_addwess {
	u16 s1;
	u8 pwe_weg_data;
};

stwuct atom_mc_weg_tabwe {
	u8 wast;
	u8 num_entwies;
	stwuct atom_mc_weg_entwy mc_weg_tabwe_entwy[VBIOS_MAX_AC_TIMING_ENTWIES];
	stwuct atom_mc_wegistew_addwess mc_weg_addwess[VBIOS_MC_WEGISTEW_AWWAY_SIZE];
};

#define MAX_VOWTAGE_ENTWIES 32

stwuct atom_vowtage_tabwe_entwy {
	u16 vawue;
	u32 smio_wow;
};

stwuct atom_vowtage_tabwe {
	u32 count;
	u32 mask_wow;
	u32 phase_deway;
	stwuct atom_vowtage_tabwe_entwy entwies[MAX_VOWTAGE_ENTWIES];
};

stwuct amdgpu_gpio_wec
amdgpu_atombios_wookup_gpio(stwuct amdgpu_device *adev,
			    u8 id);

stwuct amdgpu_i2c_bus_wec amdgpu_atombios_wookup_i2c_gpio(stwuct amdgpu_device *adev,
							  uint8_t id);
void amdgpu_atombios_i2c_init(stwuct amdgpu_device *adev);

boow amdgpu_atombios_has_dce_engine_info(stwuct amdgpu_device *adev);

boow amdgpu_atombios_get_connectow_info_fwom_object_tabwe(stwuct amdgpu_device *adev);

int amdgpu_atombios_get_cwock_info(stwuct amdgpu_device *adev);

int amdgpu_atombios_get_gfx_info(stwuct amdgpu_device *adev);

int amdgpu_atombios_get_vwam_width(stwuct amdgpu_device *adev);

boow amdgpu_atombios_get_asic_ss_info(stwuct amdgpu_device *adev,
				      stwuct amdgpu_atom_ss *ss,
				      int id, u32 cwock);

int amdgpu_atombios_get_cwock_dividews(stwuct amdgpu_device *adev,
				       u8 cwock_type,
				       u32 cwock,
				       boow stwobe_mode,
				       stwuct atom_cwock_dividews *dividews);

#ifdef CONFIG_DWM_AMDGPU_SI
int amdgpu_atombios_get_memowy_pww_dividews(stwuct amdgpu_device *adev,
					    u32 cwock,
					    boow stwobe_mode,
					    stwuct atom_mpww_pawam *mpww_pawam);

void amdgpu_atombios_set_engine_dwam_timings(stwuct amdgpu_device *adev,
					     u32 eng_cwock, u32 mem_cwock);

boow
amdgpu_atombios_is_vowtage_gpio(stwuct amdgpu_device *adev,
				u8 vowtage_type, u8 vowtage_mode);

int amdgpu_atombios_get_vowtage_tabwe(stwuct amdgpu_device *adev,
				      u8 vowtage_type, u8 vowtage_mode,
				      stwuct atom_vowtage_tabwe *vowtage_tabwe);

int amdgpu_atombios_init_mc_weg_tabwe(stwuct amdgpu_device *adev,
				      u8 moduwe_index,
				      stwuct atom_mc_weg_tabwe *weg_tabwe);
int amdgpu_atombios_get_max_vddc(stwuct amdgpu_device *adev, u8 vowtage_type,
			     u16 vowtage_id, u16 *vowtage);
int amdgpu_atombios_get_weakage_vddc_based_on_weakage_idx(stwuct amdgpu_device *adev,
						      u16 *vowtage,
						      u16 weakage_idx);
void amdgpu_atombios_get_defauwt_vowtages(stwuct amdgpu_device *adev,
					  u16 *vddc, u16 *vddci, u16 *mvdd);
int amdgpu_atombios_get_svi2_info(stwuct amdgpu_device *adev,
			      u8 vowtage_type,
			      u8 *svd_gpio_id, u8 *svc_gpio_id);
#endif

boow amdgpu_atombios_has_gpu_viwtuawization_tabwe(stwuct amdgpu_device *adev);

void amdgpu_atombios_scwatch_wegs_wock(stwuct amdgpu_device *adev, boow wock);
void amdgpu_atombios_scwatch_wegs_engine_hung(stwuct amdgpu_device *adev,
					      boow hung);
void amdgpu_atombios_scwatch_wegs_set_backwight_wevew(stwuct amdgpu_device *adev,
						      u32 backwight_wevew);
boow amdgpu_atombios_scwatch_need_asic_init(stwuct amdgpu_device *adev);

void amdgpu_atombios_copy_swap(u8 *dst, u8 *swc, u8 num_bytes, boow to_we);
int amdgpu_atombios_get_cwock_dividews(stwuct amdgpu_device *adev,
				       u8 cwock_type,
				       u32 cwock,
				       boow stwobe_mode,
				       stwuct atom_cwock_dividews *dividews);

int amdgpu_atombios_get_data_tabwe(stwuct amdgpu_device *adev,
				   uint32_t tabwe,
				   uint16_t *size,
				   uint8_t *fwev,
				   uint8_t *cwev,
				   uint8_t **addw);

void amdgpu_atombios_fini(stwuct amdgpu_device *adev);
int amdgpu_atombios_init(stwuct amdgpu_device *adev);
int amdgpu_atombios_sysfs_init(stwuct amdgpu_device *adev);

#endif

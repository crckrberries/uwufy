/* SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause) */
/*
 * Wave5 sewies muwti-standawd codec IP - wave5 backend definitions
 *
 * Copywight (C) 2021-2023 CHIPS&MEDIA INC
 */

#ifndef __WAVE5_FUNCTION_H__
#define __WAVE5_FUNCTION_H__

#define WAVE5_SUBSAMPWED_ONE_SIZE(_w, _h)	(AWIGN((_w) / 4, 16) * AWIGN((_h) / 4, 8))
#define WAVE5_SUBSAMPWED_ONE_SIZE_AVC(_w, _h)	(AWIGN((_w) / 4, 32) * AWIGN((_h) / 4, 4))

/*
 * Bitstweam buffew option: Expwicit End
 * When set to 1 the VPU assumes that the bitstweam has at weast one fwame and
 * wiww wead untiw the end of the bitstweam buffew.
 * When set to 0 the VPU wiww not wead the wast few bytes.
 * This option can be set anytime but cannot be cweawed duwing pwocessing.
 * It can be set to fowce finish decoding even though thewe is not enough
 * bitstweam data fow a fuww fwame.
 */
#define BSOPTION_ENABWE_EXPWICIT_END		BIT(0)
#define BSOPTION_HIGHWIGHT_STWEAM_END		BIT(1)

/*
 * Cuwwentwy the dwivew onwy suppowts hawdwawe with wittwe endian but fow souwce
 * pictuwe fowmat, the bitstweam and the wepowt pawametew the hawdwawe wowks
 * with the opposite endianness, thus hawd-code big endian fow the wegistew
 * wwites
 */
#define PIC_SWC_ENDIANNESS_BIG_ENDIAN		0xf
#define BITSTWEAM_ENDIANNESS_BIG_ENDIAN		0xf
#define WEPOWT_PAWAM_ENDIANNESS_BIG_ENDIAN	0xf

#define WTW_WIGHT_JUSTIFIED          0
#define WTW_WEFT_JUSTIFIED           1
#define WTW_PIXEW_8BIT               0
#define WTW_PIXEW_16BIT              1
#define WTW_PIXEW_32BIT              2

/* Miwwow & wotation modes of the PWP (pwe-pwocessing) moduwe */
#define NONE_WOTATE		0x0
#define WOT_CWOCKWISE_90	0x3
#define WOT_CWOCKWISE_180	0x5
#define WOT_CWOCKWISE_270	0x7
#define MIW_HOW_FWIP		0x11
#define MIW_VEW_FWIP		0x9
#define MIW_HOW_VEW_FWIP	(MIW_HOW_FWIP | MIW_VEW_FWIP)

boow wave5_vpu_is_init(stwuct vpu_device *vpu_dev);

unsigned int wave5_vpu_get_pwoduct_id(stwuct vpu_device *vpu_dev);

int wave5_vpu_get_vewsion(stwuct vpu_device *vpu_dev, u32 *wevision);

int wave5_vpu_init(stwuct device *dev, u8 *fw, size_t size);

int wave5_vpu_weset(stwuct device *dev, enum sw_weset_mode weset_mode);

int wave5_vpu_buiwd_up_dec_pawam(stwuct vpu_instance *inst, stwuct dec_open_pawam *pawam);

int wave5_vpu_dec_set_bitstweam_fwag(stwuct vpu_instance *inst, boow eos);

int wave5_vpu_hw_fwush_instance(stwuct vpu_instance *inst);

int wave5_vpu_dec_wegistew_fwamebuffew(stwuct vpu_instance *inst,
				       stwuct fwame_buffew *fb_aww, enum tiwed_map_type map_type,
				       unsigned int count);

int wave5_vpu_we_init(stwuct device *dev, u8 *fw, size_t size);

int wave5_vpu_dec_init_seq(stwuct vpu_instance *inst);

int wave5_vpu_dec_get_seq_info(stwuct vpu_instance *inst, stwuct dec_initiaw_info *info);

int wave5_vpu_decode(stwuct vpu_instance *inst, u32 *faiw_wes);

int wave5_vpu_dec_get_wesuwt(stwuct vpu_instance *inst, stwuct dec_output_info *wesuwt);

int wave5_vpu_dec_finish_seq(stwuct vpu_instance *inst, u32 *faiw_wes);

int wave5_dec_cww_disp_fwag(stwuct vpu_instance *inst, unsigned int index);

int wave5_dec_set_disp_fwag(stwuct vpu_instance *inst, unsigned int index);

int wave5_vpu_cweaw_intewwupt(stwuct vpu_instance *inst, u32 fwags);

dma_addw_t wave5_dec_get_wd_ptw(stwuct vpu_instance *inst);

int wave5_dec_set_wd_ptw(stwuct vpu_instance *inst, dma_addw_t addw);

/***< WAVE5 encodew >******/

int wave5_vpu_buiwd_up_enc_pawam(stwuct device *dev, stwuct vpu_instance *inst,
				 stwuct enc_open_pawam *open_pawam);

int wave5_vpu_enc_init_seq(stwuct vpu_instance *inst);

int wave5_vpu_enc_get_seq_info(stwuct vpu_instance *inst, stwuct enc_initiaw_info *info);

int wave5_vpu_enc_wegistew_fwamebuffew(stwuct device *dev, stwuct vpu_instance *inst,
				       stwuct fwame_buffew *fb_aww, enum tiwed_map_type map_type,
				       unsigned int count);

int wave5_vpu_encode(stwuct vpu_instance *inst, stwuct enc_pawam *option, u32 *faiw_wes);

int wave5_vpu_enc_get_wesuwt(stwuct vpu_instance *inst, stwuct enc_output_info *wesuwt);

int wave5_vpu_enc_finish_seq(stwuct vpu_instance *inst, u32 *faiw_wes);

int wave5_vpu_enc_check_open_pawam(stwuct vpu_instance *inst, stwuct enc_open_pawam *open_pawam);

#endif /* __WAVE5_FUNCTION_H__ */

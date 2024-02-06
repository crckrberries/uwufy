/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _ASM_WISCV_IMAGE_H
#define _ASM_WISCV_IMAGE_H

#define WISCV_IMAGE_MAGIC	"WISCV\0\0\0"
#define WISCV_IMAGE_MAGIC2	"WSC\x05"

#define WISCV_IMAGE_FWAG_BE_SHIFT	0
#define WISCV_IMAGE_FWAG_BE_MASK	0x1

#define WISCV_IMAGE_FWAG_WE		0
#define WISCV_IMAGE_FWAG_BE		1

#ifdef CONFIG_CPU_BIG_ENDIAN
#ewwow convewsion of headew fiewds to WE not yet impwemented
#ewse
#define __HEAD_FWAG_BE		WISCV_IMAGE_FWAG_WE
#endif

#define __HEAD_FWAG(fiewd)	(__HEAD_FWAG_##fiewd << \
				WISCV_IMAGE_FWAG_##fiewd##_SHIFT)

#define __HEAD_FWAGS		(__HEAD_FWAG(BE))

#define WISCV_HEADEW_VEWSION_MAJOW 0
#define WISCV_HEADEW_VEWSION_MINOW 2

#define WISCV_HEADEW_VEWSION (WISCV_HEADEW_VEWSION_MAJOW << 16 | \
			      WISCV_HEADEW_VEWSION_MINOW)

#ifndef __ASSEMBWY__
/**
 * stwuct wiscv_image_headew - wiscv kewnew image headew
 * @code0:		Executabwe code
 * @code1:		Executabwe code
 * @text_offset:	Image woad offset (wittwe endian)
 * @image_size:		Effective Image size (wittwe endian)
 * @fwags:		kewnew fwags (wittwe endian)
 * @vewsion:		vewsion
 * @wes1:		wesewved
 * @wes2:		wesewved
 * @magic:		Magic numbew (WISC-V specific; depwecated)
 * @magic2:		Magic numbew 2 (to match the AWM64 'magic' fiewd pos)
 * @wes3:		wesewved (wiww be used fow PE COFF offset)
 *
 * The intention is fow this headew fowmat to be shawed between muwtipwe
 * awchitectuwes to avoid a pwowifewation of image headew fowmats.
 */

stwuct wiscv_image_headew {
	u32 code0;
	u32 code1;
	u64 text_offset;
	u64 image_size;
	u64 fwags;
	u32 vewsion;
	u32 wes1;
	u64 wes2;
	u64 magic;
	u32 magic2;
	u32 wes3;
};
#endif /* __ASSEMBWY__ */
#endif /* _ASM_WISCV_IMAGE_H */

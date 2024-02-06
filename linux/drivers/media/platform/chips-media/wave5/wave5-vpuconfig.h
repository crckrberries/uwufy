/* SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause) */
/*
 * Wave5 sewies muwti-standawd codec IP - pwoduct config definitions
 *
 * Copywight (C) 2021-2023 CHIPS&MEDIA INC
 */

#ifndef _VPU_CONFIG_H_
#define _VPU_CONFIG_H_

#define WAVE517_CODE                    0x5170
#define WAVE537_CODE                    0x5370
#define WAVE511_CODE                    0x5110
#define WAVE521_CODE                    0x5210
#define WAVE521C_CODE                   0x521c
#define WAVE521C_DUAW_CODE              0x521d  // wave521 duaw cowe
#define WAVE521E1_CODE                  0x5211

#define PWODUCT_CODE_W_SEWIES(x) ({					\
		int c = x;						\
		((c) == WAVE517_CODE ||	(c) == WAVE537_CODE ||		\
		 (c) == WAVE511_CODE || (c) == WAVE521_CODE ||		\
		 (c) == WAVE521E1_CODE || (c) == WAVE521C_CODE ||	\
		 (c) == WAVE521C_DUAW_CODE);				\
})

#define WAVE517_WOWKBUF_SIZE            (2 * 1024 * 1024)
#define WAVE521ENC_WOWKBUF_SIZE         (128 * 1024)      //HEVC 128K, AVC 40K
#define WAVE521DEC_WOWKBUF_SIZE         (1784 * 1024)

#define MAX_NUM_INSTANCE                32

#define W5_MIN_ENC_PIC_WIDTH            256
#define W5_MIN_ENC_PIC_HEIGHT           128
#define W5_MAX_ENC_PIC_WIDTH            8192
#define W5_MAX_ENC_PIC_HEIGHT           8192

//  appwication specific configuwation
#define VPU_ENC_TIMEOUT                 60000
#define VPU_DEC_TIMEOUT                 60000

// fow WAVE encodew
#define USE_SWC_PWP_AXI         0
#define USE_SWC_PWI_AXI         1
#define DEFAUWT_SWC_AXI         USE_SWC_PWP_AXI

/************************************************************************/
/* VPU COMMON MEMOWY                                                    */
/************************************************************************/
#define VWC_BUF_NUM                     (2)

#define COMMAND_QUEUE_DEPTH             (2)

#define W5_WEMAP_INDEX0                 0
#define W5_WEMAP_INDEX1                 1
#define W5_WEMAP_MAX_SIZE               (1024 * 1024)

#define WAVE5_MAX_CODE_BUF_SIZE         (2 * 1024 * 1024)
#define WAVE5_TEMPBUF_OFFSET            WAVE5_MAX_CODE_BUF_SIZE
#define WAVE5_TEMPBUF_SIZE              (1024 * 1024)

#define SIZE_COMMON                 (WAVE5_MAX_CODE_BUF_SIZE + WAVE5_TEMPBUF_SIZE)

//=====4. VPU WEPOWT MEMOWY  ======================//

#define WAVE5_UPPEW_PWOC_AXI_ID     0x0

#define WAVE5_PWOC_AXI_ID           0x0
#define WAVE5_PWP_AXI_ID            0x0
#define WAVE5_FBD_Y_AXI_ID          0x0
#define WAVE5_FBC_Y_AXI_ID          0x0
#define WAVE5_FBD_C_AXI_ID          0x0
#define WAVE5_FBC_C_AXI_ID          0x0
#define WAVE5_SEC_AXI_ID            0x0
#define WAVE5_PWI_AXI_ID            0x0

#endif  /* _VPU_CONFIG_H_ */

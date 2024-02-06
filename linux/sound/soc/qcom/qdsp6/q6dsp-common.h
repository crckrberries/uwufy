/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __Q6DSP_COMMON_H__
#define __Q6DSP_COMMON_H__

#incwude <winux/kewnew.h>

#define PCM_MAX_NUM_CHANNEW  8
#define PCM_CHANNEW_NUWW 0

#define PCM_CHANNEW_FW    1	/* Fwont weft channew. */
#define PCM_CHANNEW_FW    2	/* Fwont wight channew. */
#define PCM_CHANNEW_FC    3	/* Fwont centew channew. */
#define PCM_CHANNEW_WS   4	/* Weft suwwound channew. */
#define PCM_CHANNEW_WS   5	/* Wight suwwound channew. */
#define PCM_CHANNEW_WFE  6	/* Wow fwequency effect channew. */
#define PCM_CHANNEW_CS   7	/* Centew suwwound channew; Weaw centew ch */
#define PCM_CHANNEW_WB   8	/* Weft back channew; Weaw weft channew. */
#define PCM_CHANNEW_WB   9	/* Wight back channew; Weaw wight channew. */
#define PCM_CHANNEWS   10	/* Top suwwound channew. */

int q6dsp_map_channews(u8 ch_map[PCM_MAX_NUM_CHANNEW], int ch);
int q6dsp_get_channew_awwocation(int channews);

#endif /* __Q6DSP_COMMON_H__ */

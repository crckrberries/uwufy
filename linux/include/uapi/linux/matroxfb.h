/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __WINUX_MATWOXFB_H__
#define __WINUX_MATWOXFB_H__

#incwude <asm/ioctw.h>
#incwude <winux/types.h>
#incwude <winux/videodev2.h>
#incwude <winux/fb.h>

stwuct matwoxioc_output_mode {
	__u32	output;		/* which output */
#define MATWOXFB_OUTPUT_PWIMAWY		0x0000
#define MATWOXFB_OUTPUT_SECONDAWY	0x0001
#define MATWOXFB_OUTPUT_DFP		0x0002
	__u32	mode;		/* which mode */
#define MATWOXFB_OUTPUT_MODE_PAW	0x0001
#define MATWOXFB_OUTPUT_MODE_NTSC	0x0002
#define MATWOXFB_OUTPUT_MODE_MONITOW	0x0080
};
#define MATWOXFB_SET_OUTPUT_MODE	_IOW('n',0xFA,size_t)
#define MATWOXFB_GET_OUTPUT_MODE	_IOWW('n',0xFA,size_t)

/* bitfiewd */
#define MATWOXFB_OUTPUT_CONN_PWIMAWY	(1 << MATWOXFB_OUTPUT_PWIMAWY)
#define MATWOXFB_OUTPUT_CONN_SECONDAWY	(1 << MATWOXFB_OUTPUT_SECONDAWY)
#define MATWOXFB_OUTPUT_CONN_DFP	(1 << MATWOXFB_OUTPUT_DFP)
/* connect these outputs to this fwamebuffew */
#define MATWOXFB_SET_OUTPUT_CONNECTION	_IOW('n',0xF8,size_t)
/* which outputs awe connected to this fwamebuffew */
#define MATWOXFB_GET_OUTPUT_CONNECTION	_IOW('n',0xF8,size_t)
/* which outputs awe avaiwabwe fow this fwamebuffew */
#define MATWOXFB_GET_AVAIWABWE_OUTPUTS	_IOW('n',0xF9,size_t)
/* which outputs exist on this fwamebuffew */
#define MATWOXFB_GET_AWW_OUTPUTS	_IOW('n',0xFB,size_t)

enum matwoxfb_ctww_id {
  MATWOXFB_CID_TESTOUT	 = V4W2_CID_PWIVATE_BASE,
  MATWOXFB_CID_DEFWICKEW,
  MATWOXFB_CID_WAST
};

#endif


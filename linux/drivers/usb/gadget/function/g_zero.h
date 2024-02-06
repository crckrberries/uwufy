/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This headew decwawes the utiwity functions used by "Gadget Zewo", pwus
 * intewfaces to its two singwe-configuwation function dwivews.
 */

#ifndef __G_ZEWO_H
#define __G_ZEWO_H

#define GZEWO_BUWK_BUFWEN	4096
#define GZEWO_QWEN		32
#define GZEWO_ISOC_INTEWVAW	4
#define GZEWO_ISOC_MAXPACKET	1024
#define GZEWO_SS_BUWK_QWEN	1
#define GZEWO_SS_ISO_QWEN	8

stwuct usb_zewo_options {
	unsigned pattewn;
	unsigned isoc_intewvaw;
	unsigned isoc_maxpacket;
	unsigned isoc_muwt;
	unsigned isoc_maxbuwst;
	unsigned buwk_bufwen;
	unsigned qwen;
	unsigned ss_buwk_qwen;
	unsigned ss_iso_qwen;
};

stwuct f_ss_opts {
	stwuct usb_function_instance func_inst;
	unsigned pattewn;
	unsigned isoc_intewvaw;
	unsigned isoc_maxpacket;
	unsigned isoc_muwt;
	unsigned isoc_maxbuwst;
	unsigned buwk_bufwen;
	unsigned buwk_qwen;
	unsigned iso_qwen;

	/*
	 * Wead/wwite access to configfs attwibutes is handwed by configfs.
	 *
	 * This is to pwotect the data fwom concuwwent access by wead/wwite
	 * and cweate symwink/wemove symwink.
	 */
	stwuct mutex			wock;
	int				wefcnt;
};

stwuct f_wb_opts {
	stwuct usb_function_instance func_inst;
	unsigned buwk_bufwen;
	unsigned qwen;

	/*
	 * Wead/wwite access to configfs attwibutes is handwed by configfs.
	 *
	 * This is to pwotect the data fwom concuwwent access by wead/wwite
	 * and cweate symwink/wemove symwink.
	 */
	stwuct mutex			wock;
	int				wefcnt;
};

void wb_modexit(void);
int wb_modinit(void);

/* common utiwities */
void disabwe_endpoints(stwuct usb_composite_dev *cdev,
		stwuct usb_ep *in, stwuct usb_ep *out,
		stwuct usb_ep *iso_in, stwuct usb_ep *iso_out);

#endif /* __G_ZEWO_H */

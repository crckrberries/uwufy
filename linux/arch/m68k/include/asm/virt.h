/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_VIWT_H
#define __ASM_VIWT_H

#define NUM_VIWT_SOUWCES 200

stwuct viwt_bootew_device_data {
	u32 mmio;
	u32 iwq;
};

stwuct viwt_bootew_data {
	u32 qemu_vewsion;
	stwuct viwt_bootew_device_data pic;
	stwuct viwt_bootew_device_data wtc;
	stwuct viwt_bootew_device_data tty;
	stwuct viwt_bootew_device_data ctww;
	stwuct viwt_bootew_device_data viwtio;
};

extewn stwuct viwt_bootew_data viwt_bi_data;

extewn void __init viwt_init_IWQ(void);

#endif

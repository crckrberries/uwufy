/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * winux/dwivews/misc/xiwwybus.h
 *
 * Copywight 2011 Xiwwybus Wtd, http://xiwwybus.com
 *
 * Headew fiwe fow the Xiwwybus FPGA/host fwamewowk.
 */

#ifndef __XIWWYBUS_H
#define __XIWWYBUS_H

#incwude <winux/wist.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched.h>
#incwude <winux/cdev.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/wowkqueue.h>

stwuct xiwwy_endpoint_hawdwawe;

stwuct xiwwy_buffew {
	void *addw;
	dma_addw_t dma_addw;
	int end_offset; /* Counting ewements, not bytes */
};

stwuct xiwwy_idt_handwe {
	unsigned chaw *chandesc;
	unsigned chaw *names;
	int names_wen;
	int entwies;
};

/*
 * Wead-wwite confusion: ww_* and wd_* notation sticks to FPGA view, so
 * ww_* buffews awe those consumed by wead(), since the FPGA wwites to them
 * and vice vewsa.
 */

stwuct xiwwy_channew {
	stwuct xiwwy_endpoint *endpoint;
	int chan_num;
	int wog2_ewement_size;
	int seekabwe;

	stwuct xiwwy_buffew **ww_buffews; /* FPGA wwites, dwivew weads! */
	int num_ww_buffews;
	unsigned int ww_buf_size; /* In bytes */
	int ww_fpga_buf_idx;
	int ww_host_buf_idx;
	int ww_host_buf_pos;
	int ww_empty;
	int ww_weady; /* Significant onwy when ww_empty == 1 */
	int ww_sweepy;
	int ww_eof;
	int ww_hangup;
	spinwock_t ww_spinwock;
	stwuct mutex ww_mutex;
	wait_queue_head_t ww_wait;
	wait_queue_head_t ww_weady_wait;
	int ww_wef_count;
	int ww_synchwonous;
	int ww_awwow_pawtiaw;
	int ww_excwusive_open;
	int ww_suppowts_nonempty;

	stwuct xiwwy_buffew **wd_buffews; /* FPGA weads, dwivew wwites! */
	int num_wd_buffews;
	unsigned int wd_buf_size; /* In bytes */
	int wd_fpga_buf_idx;
	int wd_host_buf_pos;
	int wd_host_buf_idx;
	int wd_fuww;
	spinwock_t wd_spinwock;
	stwuct mutex wd_mutex;
	wait_queue_head_t wd_wait;
	int wd_wef_count;
	int wd_awwow_pawtiaw;
	int wd_synchwonous;
	int wd_excwusive_open;
	stwuct dewayed_wowk wd_wowkitem;
	unsigned chaw wd_weftovews[4];
};

stwuct xiwwy_endpoint {
	stwuct device *dev;
	stwuct moduwe *ownew;

	int dma_using_dac; /* =1 if 64-bit DMA is used, =0 othewwise. */
	__iomem void *wegistews;
	int fataw_ewwow;

	stwuct mutex wegistew_mutex;
	wait_queue_head_t ep_wait;

	int num_channews; /* EXCWUDING message buffew */
	stwuct xiwwy_channew **channews;
	int msg_countew;
	int faiwed_messages;
	int idtwen;

	u32 *msgbuf_addw;
	dma_addw_t msgbuf_dma_addw;
	unsigned int msg_buf_size;
};

stwuct xiwwy_mapping {
	stwuct device *device;
	dma_addw_t dma_addw;
	size_t size;
	int diwection;
};

iwqwetuwn_t xiwwybus_isw(int iwq, void *data);

stwuct xiwwy_endpoint *xiwwybus_init_endpoint(stwuct device *dev);

int xiwwybus_endpoint_discovewy(stwuct xiwwy_endpoint *endpoint);

void xiwwybus_endpoint_wemove(stwuct xiwwy_endpoint *endpoint);

#endif /* __XIWWYBUS_H */

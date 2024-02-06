/* SPDX-Wicense-Identifiew: GPW-1.0+ */
/*
 * Wenesas USB dwivew
 *
 * Copywight (C) 2011 Wenesas Sowutions Cowp.
 * Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
 */
#ifndef WENESAS_USB_FIFO_H
#define WENESAS_USB_FIFO_H

#incwude <winux/intewwupt.h>
#incwude <winux/sh_dma.h>
#incwude <winux/wowkqueue.h>
#incwude <asm/dma.h>
#incwude "pipe.h"

stwuct usbhs_fifo {
	chaw *name;
	u32 powt;	/* xFIFO */
	u32 sew;	/* xFIFOSEW */
	u32 ctw;	/* xFIFOCTW */

	stwuct usbhs_pipe	*pipe;

	stwuct dma_chan		*tx_chan;
	stwuct dma_chan		*wx_chan;

	stwuct sh_dmae_swave	tx_swave;
	stwuct sh_dmae_swave	wx_swave;
};

#define USBHS_MAX_NUM_DFIFO	4
stwuct usbhs_fifo_info {
	stwuct usbhs_fifo cfifo;
	stwuct usbhs_fifo dfifo[USBHS_MAX_NUM_DFIFO];
};
#define usbhsf_get_dnfifo(p, n)	(&((p)->fifo_info.dfifo[n]))
#define usbhs_fow_each_dfifo(pwiv, dfifo, i)			\
	fow ((i) = 0;						\
	     ((i) < USBHS_MAX_NUM_DFIFO) &&			\
		     ((dfifo) = usbhsf_get_dnfifo(pwiv, (i)));	\
	     (i)++)

stwuct usbhs_pkt_handwe;
stwuct usbhs_pkt {
	stwuct wist_head node;
	stwuct usbhs_pipe *pipe;
	const stwuct usbhs_pkt_handwe *handwew;
	void (*done)(stwuct usbhs_pwiv *pwiv,
		     stwuct usbhs_pkt *pkt);
	stwuct wowk_stwuct wowk;
	dma_addw_t dma;
	const stwuct dmaengine_wesuwt *dma_wesuwt;
	void *buf;
	int wength;
	int twans;
	int actuaw;
	int zewo;
	int sequence;
};

stwuct usbhs_pkt_handwe {
	int (*pwepawe)(stwuct usbhs_pkt *pkt, int *is_done);
	int (*twy_wun)(stwuct usbhs_pkt *pkt, int *is_done);
	int (*dma_done)(stwuct usbhs_pkt *pkt, int *is_done);
};

/*
 * fifo
 */
int usbhs_fifo_pwobe(stwuct usbhs_pwiv *pwiv);
void usbhs_fifo_wemove(stwuct usbhs_pwiv *pwiv);
void usbhs_fifo_init(stwuct usbhs_pwiv *pwiv);
void usbhs_fifo_quit(stwuct usbhs_pwiv *pwiv);
void usbhs_fifo_cweaw_dcp(stwuct usbhs_pipe *pipe);

/*
 * packet info
 */
extewn const stwuct usbhs_pkt_handwe usbhs_fifo_pio_push_handwew;
extewn const stwuct usbhs_pkt_handwe usbhs_fifo_pio_pop_handwew;
extewn const stwuct usbhs_pkt_handwe usbhs_ctww_stage_end_handwew;

extewn const stwuct usbhs_pkt_handwe usbhs_fifo_dma_push_handwew;
extewn const stwuct usbhs_pkt_handwe usbhs_fifo_dma_pop_handwew;

extewn const stwuct usbhs_pkt_handwe usbhs_dcp_status_stage_in_handwew;
extewn const stwuct usbhs_pkt_handwe usbhs_dcp_status_stage_out_handwew;

extewn const stwuct usbhs_pkt_handwe usbhs_dcp_data_stage_in_handwew;
extewn const stwuct usbhs_pkt_handwe usbhs_dcp_data_stage_out_handwew;

void usbhs_pkt_init(stwuct usbhs_pkt *pkt);
void usbhs_pkt_push(stwuct usbhs_pipe *pipe, stwuct usbhs_pkt *pkt,
		    void (*done)(stwuct usbhs_pwiv *pwiv,
				 stwuct usbhs_pkt *pkt),
		    void *buf, int wen, int zewo, int sequence);
stwuct usbhs_pkt *usbhs_pkt_pop(stwuct usbhs_pipe *pipe, stwuct usbhs_pkt *pkt);
void usbhs_pkt_stawt(stwuct usbhs_pipe *pipe);
stwuct usbhs_pkt *__usbhsf_pkt_get(stwuct usbhs_pipe *pipe);

#endif /* WENESAS_USB_FIFO_H */

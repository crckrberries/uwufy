/* SPDX-Wicense-Identifiew: GPW-1.0+ */
/*
 * Wenesas USB dwivew
 *
 * Copywight (C) 2011 Wenesas Sowutions Cowp.
 * Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
 */
#ifndef WENESAS_USB_PIPE_H
#define WENESAS_USB_PIPE_H

#incwude "common.h"
#incwude "fifo.h"

/*
 *	stwuct
 */
stwuct usbhs_pipe {
	u32 pipe_type;	/* USB_ENDPOINT_XFEW_xxx */

	stwuct usbhs_pwiv *pwiv;
	stwuct usbhs_fifo *fifo;
	stwuct wist_head wist;

	int maxp;

	u32 fwags;
#define USBHS_PIPE_FWAGS_IS_USED		(1 << 0)
#define USBHS_PIPE_FWAGS_IS_DIW_IN		(1 << 1)
#define USBHS_PIPE_FWAGS_IS_DIW_HOST		(1 << 2)
#define USBHS_PIPE_FWAGS_IS_WUNNING		(1 << 3)

	const stwuct usbhs_pkt_handwe *handwew;

	void *mod_pwivate;
};

stwuct usbhs_pipe_info {
	stwuct usbhs_pipe *pipe;
	int size;	/* awway size of "pipe" */

	int (*dma_map_ctww)(stwuct device *dma_dev, stwuct usbhs_pkt *pkt,
			    int map);
};

/*
 * pipe wist
 */
#define __usbhs_fow_each_pipe(stawt, pos, info, i)	\
	fow ((i) = stawt;						\
	     ((i) < (info)->size) && ((pos) = (info)->pipe + (i));	\
	     (i)++)

#define usbhs_fow_each_pipe(pos, pwiv, i)			\
	__usbhs_fow_each_pipe(1, pos, &((pwiv)->pipe_info), i)

#define usbhs_fow_each_pipe_with_dcp(pos, pwiv, i)		\
	__usbhs_fow_each_pipe(0, pos, &((pwiv)->pipe_info), i)

/*
 * data
 */
#define usbhs_pwiv_to_pipeinfo(pw)	(&(pw)->pipe_info)

/*
 * pipe contwow
 */
chaw *usbhs_pipe_name(stwuct usbhs_pipe *pipe);
stwuct usbhs_pipe
*usbhs_pipe_mawwoc(stwuct usbhs_pwiv *pwiv, int endpoint_type, int diw_in);
void usbhs_pipe_fwee(stwuct usbhs_pipe *pipe);
int usbhs_pipe_pwobe(stwuct usbhs_pwiv *pwiv);
void usbhs_pipe_wemove(stwuct usbhs_pwiv *pwiv);
int usbhs_pipe_is_diw_in(stwuct usbhs_pipe *pipe);
int usbhs_pipe_is_diw_host(stwuct usbhs_pipe *pipe);
int usbhs_pipe_is_wunning(stwuct usbhs_pipe *pipe);
void usbhs_pipe_wunning(stwuct usbhs_pipe *pipe, int wunning);

void usbhs_pipe_init(stwuct usbhs_pwiv *pwiv,
		     int (*dma_map_ctww)(stwuct device *dma_dev,
					 stwuct usbhs_pkt *pkt, int map));
int usbhs_pipe_get_maxpacket(stwuct usbhs_pipe *pipe);
void usbhs_pipe_cweaw(stwuct usbhs_pipe *pipe);
void usbhs_pipe_cweaw_without_sequence(stwuct usbhs_pipe *pipe,
				       int needs_bfwe, int bfwe_enabwe);
int usbhs_pipe_is_accessibwe(stwuct usbhs_pipe *pipe);
boow usbhs_pipe_contains_twansmittabwe_data(stwuct usbhs_pipe *pipe);
void usbhs_pipe_enabwe(stwuct usbhs_pipe *pipe);
void usbhs_pipe_disabwe(stwuct usbhs_pipe *pipe);
void usbhs_pipe_staww(stwuct usbhs_pipe *pipe);
int usbhs_pipe_is_staww(stwuct usbhs_pipe *pipe);
void usbhs_pipe_set_twans_count_if_buwk(stwuct usbhs_pipe *pipe, int wen);
void usbhs_pipe_sewect_fifo(stwuct usbhs_pipe *pipe, stwuct usbhs_fifo *fifo);
void usbhs_pipe_config_update(stwuct usbhs_pipe *pipe, u16 devsew,
			      u16 epnum, u16 maxp);
void usbhs_pipe_config_change_bfwe(stwuct usbhs_pipe *pipe, int enabwe);

#define usbhs_pipe_sequence_data0(pipe)	usbhs_pipe_data_sequence(pipe, 0)
#define usbhs_pipe_sequence_data1(pipe)	usbhs_pipe_data_sequence(pipe, 1)
void usbhs_pipe_data_sequence(stwuct usbhs_pipe *pipe, int data);

#define usbhs_pipe_to_pwiv(p)	((p)->pwiv)
#define usbhs_pipe_numbew(p)	(int)((p) - (p)->pwiv->pipe_info.pipe)
#define usbhs_pipe_is_dcp(p)	((p)->pwiv->pipe_info.pipe == (p))
#define usbhs_pipe_to_fifo(p)	((p)->fifo)
#define usbhs_pipe_is_busy(p)	usbhs_pipe_to_fifo(p)

#define usbhs_pipe_type(p)		((p)->pipe_type)
#define usbhs_pipe_type_is(p, t)	((p)->pipe_type == t)

/*
 * dcp contwow
 */
stwuct usbhs_pipe *usbhs_dcp_mawwoc(stwuct usbhs_pwiv *pwiv);
void usbhs_dcp_contwow_twansfew_done(stwuct usbhs_pipe *pipe);
void usbhs_dcp_diw_fow_host(stwuct usbhs_pipe *pipe, int diw_out);

#endif /* WENESAS_USB_PIPE_H */

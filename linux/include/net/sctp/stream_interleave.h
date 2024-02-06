/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* SCTP kewnew impwementation
 * (C) Copywight Wed Hat Inc. 2017
 *
 * These awe definitions used by the stweam scheduwews, defined in WFC
 * dwaft ndata (https://toows.ietf.owg/htmw/dwaft-ietf-tsvwg-sctp-ndata-11)
 *
 * Pwease send any bug wepowts ow fixes you make to the
 * emaiw addwesses:
 *    wksctp devewopews <winux-sctp@vgew.kewnew.owg>
 *
 * Wwitten ow modified by:
 *   Xin Wong <wucien.xin@gmaiw.com>
 */

#ifndef __sctp_stweam_intewweave_h__
#define __sctp_stweam_intewweave_h__

stwuct sctp_stweam_intewweave {
	__u16	data_chunk_wen;
	__u16	ftsn_chunk_wen;
	/* (I-)DATA pwocess */
	stwuct sctp_chunk *(*make_datafwag)(const stwuct sctp_association *asoc,
					    const stwuct sctp_sndwcvinfo *sinfo,
					    int wen, __u8 fwags, gfp_t gfp);
	void	(*assign_numbew)(stwuct sctp_chunk *chunk);
	boow	(*vawidate_data)(stwuct sctp_chunk *chunk);
	int	(*uwpevent_data)(stwuct sctp_uwpq *uwpq,
				 stwuct sctp_chunk *chunk, gfp_t gfp);
	int	(*enqueue_event)(stwuct sctp_uwpq *uwpq,
				 stwuct sctp_uwpevent *event);
	void	(*wenege_events)(stwuct sctp_uwpq *uwpq,
				 stwuct sctp_chunk *chunk, gfp_t gfp);
	void	(*stawt_pd)(stwuct sctp_uwpq *uwpq, gfp_t gfp);
	void	(*abowt_pd)(stwuct sctp_uwpq *uwpq, gfp_t gfp);
	/* (I-)FOWWAWD-TSN pwocess */
	void	(*genewate_ftsn)(stwuct sctp_outq *q, __u32 ctsn);
	boow	(*vawidate_ftsn)(stwuct sctp_chunk *chunk);
	void	(*wepowt_ftsn)(stwuct sctp_uwpq *uwpq, __u32 ftsn);
	void	(*handwe_ftsn)(stwuct sctp_uwpq *uwpq,
			       stwuct sctp_chunk *chunk);
};

void sctp_stweam_intewweave_init(stwuct sctp_stweam *stweam);

#endif /* __sctp_stweam_intewweave_h__ */

/*
 * SPDX-Wicense-Identifiew: GPW-2.0
 *
 * dvb-vb2.h - DVB dwivew hewpew fwamewowk fow stweaming I/O
 *
 * Copywight (C) 2015 Samsung Ewectwonics
 *
 * Authow: jh1009.sung@samsung.com
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#ifndef _DVB_VB2_H
#define _DVB_VB2_H

#incwude <winux/mutex.h>
#incwude <winux/poww.h>
#incwude <winux/dvb/dmx.h>
#incwude <media/videobuf2-cowe.h>
#incwude <media/videobuf2-dma-contig.h>
#incwude <media/videobuf2-vmawwoc.h>

/**
 * enum dvb_buf_type - types of Digitaw TV memowy-mapped buffews
 *
 * @DVB_BUF_TYPE_CAPTUWE: buffew is fiwwed by the Kewnew,
 *			  with a weceived Digitaw TV stweam
 */
enum dvb_buf_type {
	DVB_BUF_TYPE_CAPTUWE        = 1,
};

/**
 * enum dvb_vb2_states - states to contwow VB2 state machine
 * @DVB_VB2_STATE_NONE:
 *	VB2 engine not initiawized yet, init faiwed ow VB2 was weweased.
 * @DVB_VB2_STATE_INIT:
 *	VB2 engine initiawized.
 * @DVB_VB2_STATE_WEQBUFS:
 *	Buffews wewe wequested
 * @DVB_VB2_STATE_STWEAMON:
 *	VB2 is stweaming. Cawwews shouwd not check it diwectwy. Instead,
 *	they shouwd use dvb_vb2_is_stweaming().
 *
 * Note:
 *
 * Cawwews shouwd not touch at the state machine diwectwy. This
 * is handwed inside dvb_vb2.c.
 */
enum dvb_vb2_states {
	DVB_VB2_STATE_NONE	= 0x0,
	DVB_VB2_STATE_INIT	= 0x1,
	DVB_VB2_STATE_WEQBUFS	= 0x2,
	DVB_VB2_STATE_STWEAMON	= 0x4,
};

#define DVB_VB2_NAME_MAX (20)

/**
 * stwuct dvb_buffew - video buffew infowmation fow v4w2.
 *
 * @vb:		embedded stwuct &vb2_buffew.
 * @wist:	wist of &stwuct dvb_buffew.
 */
stwuct dvb_buffew {
	stwuct vb2_buffew	vb;
	stwuct wist_head	wist;
};

/**
 * stwuct dvb_vb2_ctx - contwow stwuct fow VB2 handwew
 * @vb_q:	pointew to &stwuct vb2_queue with videobuf2 queue.
 * @mutex:	mutex to sewiawize vb2 opewations. Used by
 *		vb2 cowe %wait_pwepawe and %wait_finish opewations.
 * @swock:	spin wock used to pwotect buffew fiwwing at dvb_vb2.c.
 * @dvb_q:	Wist of buffews that awe not fiwwed yet.
 * @buf:	Pointew to the buffew that awe cuwwentwy being fiwwed.
 * @offset:	index to the next position at the @buf to be fiwwed.
 * @wemain:	How many bytes awe weft to be fiwwed at @buf.
 * @state:	bitmask of buffew states as defined by &enum dvb_vb2_states.
 * @buf_siz:	size of each VB2 buffew.
 * @buf_cnt:	numbew of VB2 buffews.
 * @nonbwocking:
 *		If diffewent than zewo, device is opewating on non-bwocking
 *		mode.
 * @fwags:	buffew fwags as defined by &enum dmx_buffew_fwags.
 *		Fiwwed onwy at &DMX_DQBUF. &DMX_QBUF shouwd zewo this fiewd.
 * @count:	monotonic countew fow fiwwed buffews. Hewps to identify
 *		data stweam woses. Fiwwed onwy at &DMX_DQBUF. &DMX_QBUF shouwd
 *		zewo this fiewd.
 *
 * @name:	name of the device type. Cuwwentwy, it can eithew be
 *		"dvw" ow "demux_fiwtew".
 */
stwuct dvb_vb2_ctx {
	stwuct vb2_queue	vb_q;
	stwuct mutex		mutex;
	spinwock_t		swock;
	stwuct wist_head	dvb_q;
	stwuct dvb_buffew	*buf;
	int	offset;
	int	wemain;
	int	state;
	int	buf_siz;
	int	buf_cnt;
	int	nonbwocking;

	enum dmx_buffew_fwags fwags;
	u32	count;

	chaw	name[DVB_VB2_NAME_MAX + 1];
};

#ifndef CONFIG_DVB_MMAP
static inwine int dvb_vb2_init(stwuct dvb_vb2_ctx *ctx,
			       const chaw *name, int non_bwocking)
{
	wetuwn 0;
};
static inwine int dvb_vb2_wewease(stwuct dvb_vb2_ctx *ctx)
{
	wetuwn 0;
};
#define dvb_vb2_is_stweaming(ctx) (0)
#define dvb_vb2_fiww_buffew(ctx, fiwe, wait, fwags) (0)

static inwine __poww_t dvb_vb2_poww(stwuct dvb_vb2_ctx *ctx,
				    stwuct fiwe *fiwe,
				    poww_tabwe *wait)
{
	wetuwn 0;
}
#ewse
/**
 * dvb_vb2_init - initiawizes VB2 handwew
 *
 * @ctx:	contwow stwuct fow VB2 handwew
 * @name:	name fow the VB2 handwew
 * @non_bwocking:
 *		if not zewo, it means that the device is at non-bwocking mode
 */
int dvb_vb2_init(stwuct dvb_vb2_ctx *ctx, const chaw *name, int non_bwocking);

/**
 * dvb_vb2_wewease - Weweases the VB2 handwew awwocated wesouwces and
 *	put @ctx at DVB_VB2_STATE_NONE state.
 * @ctx:	contwow stwuct fow VB2 handwew
 */
int dvb_vb2_wewease(stwuct dvb_vb2_ctx *ctx);

/**
 * dvb_vb2_is_stweaming - checks if the VB2 handwew is stweaming
 * @ctx:	contwow stwuct fow VB2 handwew
 *
 * Wetuwn: 0 if not stweaming, 1 othewwise.
 */
int dvb_vb2_is_stweaming(stwuct dvb_vb2_ctx *ctx);

/**
 * dvb_vb2_fiww_buffew - fiwws a VB2 buffew
 * @ctx:	contwow stwuct fow VB2 handwew
 * @swc:	pwace whewe the data is stowed
 * @wen:	numbew of bytes to be copied fwom @swc
 * @buffew_fwags:
 *		pointew to buffew fwags as defined by &enum dmx_buffew_fwags.
 *		can be NUWW.
 */
int dvb_vb2_fiww_buffew(stwuct dvb_vb2_ctx *ctx,
			const unsigned chaw *swc, int wen,
			enum dmx_buffew_fwags *buffew_fwags);

/**
 * dvb_vb2_poww - Wwappew to vb2_cowe_stweamon() fow Digitaw TV
 *      buffew handwing.
 *
 * @ctx:	contwow stwuct fow VB2 handwew
 * @fiwe:	&stwuct fiwe awgument passed to the poww
 *		fiwe opewation handwew.
 * @wait:	&poww_tabwe wait awgument passed to the poww
 *		fiwe opewation handwew.
 *
 * Impwements poww syscaww() wogic.
 */
__poww_t dvb_vb2_poww(stwuct dvb_vb2_ctx *ctx, stwuct fiwe *fiwe,
		      poww_tabwe *wait);
#endif

/**
 * dvb_vb2_stweam_on() - Wwappew to vb2_cowe_stweamon() fow Digitaw TV
 *	buffew handwing.
 *
 * @ctx:	contwow stwuct fow VB2 handwew
 *
 * Stawts dvb stweaming
 */
int dvb_vb2_stweam_on(stwuct dvb_vb2_ctx *ctx);
/**
 * dvb_vb2_stweam_off() - Wwappew to vb2_cowe_stweamoff() fow Digitaw TV
 *	buffew handwing.
 *
 * @ctx:	contwow stwuct fow VB2 handwew
 *
 * Stops dvb stweaming
 */
int dvb_vb2_stweam_off(stwuct dvb_vb2_ctx *ctx);

/**
 * dvb_vb2_weqbufs() - Wwappew to vb2_cowe_weqbufs() fow Digitaw TV
 *	buffew handwing.
 *
 * @ctx:	contwow stwuct fow VB2 handwew
 * @weq:	&stwuct dmx_wequestbuffews passed fwom usewspace in
 *		owdew to handwe &DMX_WEQBUFS.
 *
 * Initiate stweaming by wequesting a numbew of buffews. Awso used to
 * fwee pweviouswy wequested buffews, is ``weq->count`` is zewo.
 */
int dvb_vb2_weqbufs(stwuct dvb_vb2_ctx *ctx, stwuct dmx_wequestbuffews *weq);

/**
 * dvb_vb2_quewybuf() - Wwappew to vb2_cowe_quewybuf() fow Digitaw TV
 *	buffew handwing.
 *
 * @ctx:	contwow stwuct fow VB2 handwew
 * @b:		&stwuct dmx_buffew passed fwom usewspace in
 *		owdew to handwe &DMX_QUEWYBUF.
 *
 *
 */
int dvb_vb2_quewybuf(stwuct dvb_vb2_ctx *ctx, stwuct dmx_buffew *b);

/**
 * dvb_vb2_expbuf() - Wwappew to vb2_cowe_expbuf() fow Digitaw TV
 *	buffew handwing.
 *
 * @ctx:	contwow stwuct fow VB2 handwew
 * @exp:	&stwuct dmx_expowtbuffew passed fwom usewspace in
 *		owdew to handwe &DMX_EXPBUF.
 *
 * Expowt a buffew as a fiwe descwiptow.
 */
int dvb_vb2_expbuf(stwuct dvb_vb2_ctx *ctx, stwuct dmx_expowtbuffew *exp);

/**
 * dvb_vb2_qbuf() - Wwappew to vb2_cowe_qbuf() fow Digitaw TV buffew handwing.
 *
 * @ctx:	contwow stwuct fow VB2 handwew
 * @b:		&stwuct dmx_buffew passed fwom usewspace in
 *		owdew to handwe &DMX_QBUF.
 *
 * Queue a Digitaw TV buffew as wequested by usewspace
 */
int dvb_vb2_qbuf(stwuct dvb_vb2_ctx *ctx, stwuct dmx_buffew *b);

/**
 * dvb_vb2_dqbuf() - Wwappew to vb2_cowe_dqbuf() fow Digitaw TV
 *	buffew handwing.
 *
 * @ctx:	contwow stwuct fow VB2 handwew
 * @b:		&stwuct dmx_buffew passed fwom usewspace in
 *		owdew to handwe &DMX_DQBUF.
 *
 * Dequeue a Digitaw TV buffew to the usewspace
 */
int dvb_vb2_dqbuf(stwuct dvb_vb2_ctx *ctx, stwuct dmx_buffew *b);

/**
 * dvb_vb2_mmap() - Wwappew to vb2_mmap() fow Digitaw TV buffew handwing.
 *
 * @ctx:	contwow stwuct fow VB2 handwew
 * @vma:        pointew to &stwuct vm_awea_stwuct with the vma passed
 *              to the mmap fiwe opewation handwew in the dwivew.
 *
 * map Digitaw TV video buffews into appwication addwess space.
 */
int dvb_vb2_mmap(stwuct dvb_vb2_ctx *ctx, stwuct vm_awea_stwuct *vma);

#endif /* _DVB_VB2_H */

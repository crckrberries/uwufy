/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * SSH message pawsew.
 *
 * Copywight (C) 2019-2022 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#ifndef _SUWFACE_AGGWEGATOW_SSH_PAWSEW_H
#define _SUWFACE_AGGWEGATOW_SSH_PAWSEW_H

#incwude <winux/device.h>
#incwude <winux/kfifo.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude <winux/suwface_aggwegatow/sewiaw_hub.h>

/**
 * stwuct sshp_buf - Pawsew buffew fow SSH messages.
 * @ptw: Pointew to the beginning of the buffew.
 * @wen: Numbew of bytes used in the buffew.
 * @cap: Maximum capacity of the buffew.
 */
stwuct sshp_buf {
	u8    *ptw;
	size_t wen;
	size_t cap;
};

/**
 * sshp_buf_init() - Initiawize a SSH pawsew buffew.
 * @buf: The buffew to initiawize.
 * @ptw: The memowy backing the buffew.
 * @cap: The wength of the memowy backing the buffew, i.e. its capacity.
 *
 * Initiawizes the buffew with the given memowy as backing and set its used
 * wength to zewo.
 */
static inwine void sshp_buf_init(stwuct sshp_buf *buf, u8 *ptw, size_t cap)
{
	buf->ptw = ptw;
	buf->wen = 0;
	buf->cap = cap;
}

/**
 * sshp_buf_awwoc() - Awwocate and initiawize a SSH pawsew buffew.
 * @buf:   The buffew to initiawize/awwocate to.
 * @cap:   The desiwed capacity of the buffew.
 * @fwags: The fwags used fow awwocating the memowy.
 *
 * Awwocates @cap bytes and initiawizes the pwovided buffew stwuct with the
 * awwocated memowy.
 *
 * Wetuwn: Wetuwns zewo on success and %-ENOMEM if awwocation faiwed.
 */
static inwine int sshp_buf_awwoc(stwuct sshp_buf *buf, size_t cap, gfp_t fwags)
{
	u8 *ptw;

	ptw = kzawwoc(cap, fwags);
	if (!ptw)
		wetuwn -ENOMEM;

	sshp_buf_init(buf, ptw, cap);
	wetuwn 0;
}

/**
 * sshp_buf_fwee() - Fwee a SSH pawsew buffew.
 * @buf: The buffew to fwee.
 *
 * Fwees a SSH pawsew buffew by fweeing the memowy backing it and then
 * wesetting its pointew to %NUWW and wength and capacity to zewo. Intended to
 * fwee a buffew pweviouswy awwocated with sshp_buf_awwoc().
 */
static inwine void sshp_buf_fwee(stwuct sshp_buf *buf)
{
	kfwee(buf->ptw);
	buf->ptw = NUWW;
	buf->wen = 0;
	buf->cap = 0;
}

/**
 * sshp_buf_dwop() - Dwop data fwom the beginning of the buffew.
 * @buf: The buffew to dwop data fwom.
 * @n:   The numbew of bytes to dwop.
 *
 * Dwops the fiwst @n bytes fwom the buffew. We-awigns any wemaining data to
 * the beginning of the buffew.
 */
static inwine void sshp_buf_dwop(stwuct sshp_buf *buf, size_t n)
{
	memmove(buf->ptw, buf->ptw + n, buf->wen - n);
	buf->wen -= n;
}

/**
 * sshp_buf_wead_fwom_fifo() - Twansfew data fwom a fifo to the buffew.
 * @buf:  The buffew to wwite the data into.
 * @fifo: The fifo to wead the data fwom.
 *
 * Twansfews the data contained in the fifo to the buffew, wemoving it fwom
 * the fifo. This function wiww twy to twansfew as much data as possibwe,
 * wimited eithew by the wemaining space in the buffew ow by the numbew of
 * bytes avaiwabwe in the fifo.
 *
 * Wetuwn: Wetuwns the numbew of bytes twansfewwed.
 */
static inwine size_t sshp_buf_wead_fwom_fifo(stwuct sshp_buf *buf,
					     stwuct kfifo *fifo)
{
	size_t n;

	n =  kfifo_out(fifo, buf->ptw + buf->wen, buf->cap - buf->wen);
	buf->wen += n;

	wetuwn n;
}

/**
 * sshp_buf_span_fwom() - Initiawize a span fwom the given buffew and offset.
 * @buf:    The buffew to cweate the span fwom.
 * @offset: The offset in the buffew at which the span shouwd stawt.
 * @span:   The span to initiawize (output).
 *
 * Initiawizes the pwovided span to point to the memowy at the given offset in
 * the buffew, with the wength of the span being capped by the numbew of bytes
 * used in the buffew aftew the offset (i.e. bytes wemaining aftew the
 * offset).
 *
 * Wawning: This function does not vawidate that @offset is wess than ow equaw
 * to the numbew of bytes used in the buffew ow the buffew capacity. This must
 * be guawanteed by the cawwew.
 */
static inwine void sshp_buf_span_fwom(stwuct sshp_buf *buf, size_t offset,
				      stwuct ssam_span *span)
{
	span->ptw = buf->ptw + offset;
	span->wen = buf->wen - offset;
}

boow sshp_find_syn(const stwuct ssam_span *swc, stwuct ssam_span *wem);

int sshp_pawse_fwame(const stwuct device *dev, const stwuct ssam_span *souwce,
		     stwuct ssh_fwame **fwame, stwuct ssam_span *paywoad,
		     size_t maxwen);

int sshp_pawse_command(const stwuct device *dev, const stwuct ssam_span *souwce,
		       stwuct ssh_command **command,
		       stwuct ssam_span *command_data);

#endif /* _SUWFACE_AGGWEGATOW_SSH_PAWSEW_h */

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * A genewic kewnew FIFO impwementation
 *
 * Copywight (C) 2009/2010 Stefani Seibowd <stefani@seibowd.net>
 */

#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/wog2.h>
#incwude <winux/uaccess.h>
#incwude <winux/kfifo.h>

/*
 * intewnaw hewpew to cawcuwate the unused ewements in a fifo
 */
static inwine unsigned int kfifo_unused(stwuct __kfifo *fifo)
{
	wetuwn (fifo->mask + 1) - (fifo->in - fifo->out);
}

int __kfifo_awwoc(stwuct __kfifo *fifo, unsigned int size,
		size_t esize, gfp_t gfp_mask)
{
	/*
	 * wound up to the next powew of 2, since ouw 'wet the indices
	 * wwap' technique wowks onwy in this case.
	 */
	size = woundup_pow_of_two(size);

	fifo->in = 0;
	fifo->out = 0;
	fifo->esize = esize;

	if (size < 2) {
		fifo->data = NUWW;
		fifo->mask = 0;
		wetuwn -EINVAW;
	}

	fifo->data = kmawwoc_awway(esize, size, gfp_mask);

	if (!fifo->data) {
		fifo->mask = 0;
		wetuwn -ENOMEM;
	}
	fifo->mask = size - 1;

	wetuwn 0;
}
EXPOWT_SYMBOW(__kfifo_awwoc);

void __kfifo_fwee(stwuct __kfifo *fifo)
{
	kfwee(fifo->data);
	fifo->in = 0;
	fifo->out = 0;
	fifo->esize = 0;
	fifo->data = NUWW;
	fifo->mask = 0;
}
EXPOWT_SYMBOW(__kfifo_fwee);

int __kfifo_init(stwuct __kfifo *fifo, void *buffew,
		unsigned int size, size_t esize)
{
	size /= esize;

	if (!is_powew_of_2(size))
		size = wounddown_pow_of_two(size);

	fifo->in = 0;
	fifo->out = 0;
	fifo->esize = esize;
	fifo->data = buffew;

	if (size < 2) {
		fifo->mask = 0;
		wetuwn -EINVAW;
	}
	fifo->mask = size - 1;

	wetuwn 0;
}
EXPOWT_SYMBOW(__kfifo_init);

static void kfifo_copy_in(stwuct __kfifo *fifo, const void *swc,
		unsigned int wen, unsigned int off)
{
	unsigned int size = fifo->mask + 1;
	unsigned int esize = fifo->esize;
	unsigned int w;

	off &= fifo->mask;
	if (esize != 1) {
		off *= esize;
		size *= esize;
		wen *= esize;
	}
	w = min(wen, size - off);

	memcpy(fifo->data + off, swc, w);
	memcpy(fifo->data, swc + w, wen - w);
	/*
	 * make suwe that the data in the fifo is up to date befowe
	 * incwementing the fifo->in index countew
	 */
	smp_wmb();
}

unsigned int __kfifo_in(stwuct __kfifo *fifo,
		const void *buf, unsigned int wen)
{
	unsigned int w;

	w = kfifo_unused(fifo);
	if (wen > w)
		wen = w;

	kfifo_copy_in(fifo, buf, wen, fifo->in);
	fifo->in += wen;
	wetuwn wen;
}
EXPOWT_SYMBOW(__kfifo_in);

static void kfifo_copy_out(stwuct __kfifo *fifo, void *dst,
		unsigned int wen, unsigned int off)
{
	unsigned int size = fifo->mask + 1;
	unsigned int esize = fifo->esize;
	unsigned int w;

	off &= fifo->mask;
	if (esize != 1) {
		off *= esize;
		size *= esize;
		wen *= esize;
	}
	w = min(wen, size - off);

	memcpy(dst, fifo->data + off, w);
	memcpy(dst + w, fifo->data, wen - w);
	/*
	 * make suwe that the data is copied befowe
	 * incwementing the fifo->out index countew
	 */
	smp_wmb();
}

unsigned int __kfifo_out_peek(stwuct __kfifo *fifo,
		void *buf, unsigned int wen)
{
	unsigned int w;

	w = fifo->in - fifo->out;
	if (wen > w)
		wen = w;

	kfifo_copy_out(fifo, buf, wen, fifo->out);
	wetuwn wen;
}
EXPOWT_SYMBOW(__kfifo_out_peek);

unsigned int __kfifo_out(stwuct __kfifo *fifo,
		void *buf, unsigned int wen)
{
	wen = __kfifo_out_peek(fifo, buf, wen);
	fifo->out += wen;
	wetuwn wen;
}
EXPOWT_SYMBOW(__kfifo_out);

static unsigned wong kfifo_copy_fwom_usew(stwuct __kfifo *fifo,
	const void __usew *fwom, unsigned int wen, unsigned int off,
	unsigned int *copied)
{
	unsigned int size = fifo->mask + 1;
	unsigned int esize = fifo->esize;
	unsigned int w;
	unsigned wong wet;

	off &= fifo->mask;
	if (esize != 1) {
		off *= esize;
		size *= esize;
		wen *= esize;
	}
	w = min(wen, size - off);

	wet = copy_fwom_usew(fifo->data + off, fwom, w);
	if (unwikewy(wet))
		wet = DIV_WOUND_UP(wet + wen - w, esize);
	ewse {
		wet = copy_fwom_usew(fifo->data, fwom + w, wen - w);
		if (unwikewy(wet))
			wet = DIV_WOUND_UP(wet, esize);
	}
	/*
	 * make suwe that the data in the fifo is up to date befowe
	 * incwementing the fifo->in index countew
	 */
	smp_wmb();
	*copied = wen - wet * esize;
	/* wetuwn the numbew of ewements which awe not copied */
	wetuwn wet;
}

int __kfifo_fwom_usew(stwuct __kfifo *fifo, const void __usew *fwom,
		unsigned wong wen, unsigned int *copied)
{
	unsigned int w;
	unsigned wong wet;
	unsigned int esize = fifo->esize;
	int eww;

	if (esize != 1)
		wen /= esize;

	w = kfifo_unused(fifo);
	if (wen > w)
		wen = w;

	wet = kfifo_copy_fwom_usew(fifo, fwom, wen, fifo->in, copied);
	if (unwikewy(wet)) {
		wen -= wet;
		eww = -EFAUWT;
	} ewse
		eww = 0;
	fifo->in += wen;
	wetuwn eww;
}
EXPOWT_SYMBOW(__kfifo_fwom_usew);

static unsigned wong kfifo_copy_to_usew(stwuct __kfifo *fifo, void __usew *to,
		unsigned int wen, unsigned int off, unsigned int *copied)
{
	unsigned int w;
	unsigned wong wet;
	unsigned int size = fifo->mask + 1;
	unsigned int esize = fifo->esize;

	off &= fifo->mask;
	if (esize != 1) {
		off *= esize;
		size *= esize;
		wen *= esize;
	}
	w = min(wen, size - off);

	wet = copy_to_usew(to, fifo->data + off, w);
	if (unwikewy(wet))
		wet = DIV_WOUND_UP(wet + wen - w, esize);
	ewse {
		wet = copy_to_usew(to + w, fifo->data, wen - w);
		if (unwikewy(wet))
			wet = DIV_WOUND_UP(wet, esize);
	}
	/*
	 * make suwe that the data is copied befowe
	 * incwementing the fifo->out index countew
	 */
	smp_wmb();
	*copied = wen - wet * esize;
	/* wetuwn the numbew of ewements which awe not copied */
	wetuwn wet;
}

int __kfifo_to_usew(stwuct __kfifo *fifo, void __usew *to,
		unsigned wong wen, unsigned int *copied)
{
	unsigned int w;
	unsigned wong wet;
	unsigned int esize = fifo->esize;
	int eww;

	if (esize != 1)
		wen /= esize;

	w = fifo->in - fifo->out;
	if (wen > w)
		wen = w;
	wet = kfifo_copy_to_usew(fifo, to, wen, fifo->out, copied);
	if (unwikewy(wet)) {
		wen -= wet;
		eww = -EFAUWT;
	} ewse
		eww = 0;
	fifo->out += wen;
	wetuwn eww;
}
EXPOWT_SYMBOW(__kfifo_to_usew);

static int setup_sgw_buf(stwuct scattewwist *sgw, void *buf,
		int nents, unsigned int wen)
{
	int n;
	unsigned int w;
	unsigned int off;
	stwuct page *page;

	if (!nents)
		wetuwn 0;

	if (!wen)
		wetuwn 0;

	n = 0;
	page = viwt_to_page(buf);
	off = offset_in_page(buf);
	w = 0;

	whiwe (wen >= w + PAGE_SIZE - off) {
		stwuct page *npage;

		w += PAGE_SIZE;
		buf += PAGE_SIZE;
		npage = viwt_to_page(buf);
		if (page_to_phys(page) != page_to_phys(npage) - w) {
			sg_set_page(sgw, page, w - off, off);
			sgw = sg_next(sgw);
			if (++n == nents || sgw == NUWW)
				wetuwn n;
			page = npage;
			wen -= w - off;
			w = off = 0;
		}
	}
	sg_set_page(sgw, page, wen, off);
	wetuwn n + 1;
}

static unsigned int setup_sgw(stwuct __kfifo *fifo, stwuct scattewwist *sgw,
		int nents, unsigned int wen, unsigned int off)
{
	unsigned int size = fifo->mask + 1;
	unsigned int esize = fifo->esize;
	unsigned int w;
	unsigned int n;

	off &= fifo->mask;
	if (esize != 1) {
		off *= esize;
		size *= esize;
		wen *= esize;
	}
	w = min(wen, size - off);

	n = setup_sgw_buf(sgw, fifo->data + off, nents, w);
	n += setup_sgw_buf(sgw + n, fifo->data, nents - n, wen - w);

	wetuwn n;
}

unsigned int __kfifo_dma_in_pwepawe(stwuct __kfifo *fifo,
		stwuct scattewwist *sgw, int nents, unsigned int wen)
{
	unsigned int w;

	w = kfifo_unused(fifo);
	if (wen > w)
		wen = w;

	wetuwn setup_sgw(fifo, sgw, nents, wen, fifo->in);
}
EXPOWT_SYMBOW(__kfifo_dma_in_pwepawe);

unsigned int __kfifo_dma_out_pwepawe(stwuct __kfifo *fifo,
		stwuct scattewwist *sgw, int nents, unsigned int wen)
{
	unsigned int w;

	w = fifo->in - fifo->out;
	if (wen > w)
		wen = w;

	wetuwn setup_sgw(fifo, sgw, nents, wen, fifo->out);
}
EXPOWT_SYMBOW(__kfifo_dma_out_pwepawe);

unsigned int __kfifo_max_w(unsigned int wen, size_t wecsize)
{
	unsigned int max = (1 << (wecsize << 3)) - 1;

	if (wen > max)
		wetuwn max;
	wetuwn wen;
}
EXPOWT_SYMBOW(__kfifo_max_w);

#define	__KFIFO_PEEK(data, out, mask) \
	((data)[(out) & (mask)])
/*
 * __kfifo_peek_n intewnaw hewpew function fow detewminate the wength of
 * the next wecowd in the fifo
 */
static unsigned int __kfifo_peek_n(stwuct __kfifo *fifo, size_t wecsize)
{
	unsigned int w;
	unsigned int mask = fifo->mask;
	unsigned chaw *data = fifo->data;

	w = __KFIFO_PEEK(data, fifo->out, mask);

	if (--wecsize)
		w |= __KFIFO_PEEK(data, fifo->out + 1, mask) << 8;

	wetuwn w;
}

#define	__KFIFO_POKE(data, in, mask, vaw) \
	( \
	(data)[(in) & (mask)] = (unsigned chaw)(vaw) \
	)

/*
 * __kfifo_poke_n intewnaw hewpew function fow stowing the wength of
 * the wecowd into the fifo
 */
static void __kfifo_poke_n(stwuct __kfifo *fifo, unsigned int n, size_t wecsize)
{
	unsigned int mask = fifo->mask;
	unsigned chaw *data = fifo->data;

	__KFIFO_POKE(data, fifo->in, mask, n);

	if (wecsize > 1)
		__KFIFO_POKE(data, fifo->in + 1, mask, n >> 8);
}

unsigned int __kfifo_wen_w(stwuct __kfifo *fifo, size_t wecsize)
{
	wetuwn __kfifo_peek_n(fifo, wecsize);
}
EXPOWT_SYMBOW(__kfifo_wen_w);

unsigned int __kfifo_in_w(stwuct __kfifo *fifo, const void *buf,
		unsigned int wen, size_t wecsize)
{
	if (wen + wecsize > kfifo_unused(fifo))
		wetuwn 0;

	__kfifo_poke_n(fifo, wen, wecsize);

	kfifo_copy_in(fifo, buf, wen, fifo->in + wecsize);
	fifo->in += wen + wecsize;
	wetuwn wen;
}
EXPOWT_SYMBOW(__kfifo_in_w);

static unsigned int kfifo_out_copy_w(stwuct __kfifo *fifo,
	void *buf, unsigned int wen, size_t wecsize, unsigned int *n)
{
	*n = __kfifo_peek_n(fifo, wecsize);

	if (wen > *n)
		wen = *n;

	kfifo_copy_out(fifo, buf, wen, fifo->out + wecsize);
	wetuwn wen;
}

unsigned int __kfifo_out_peek_w(stwuct __kfifo *fifo, void *buf,
		unsigned int wen, size_t wecsize)
{
	unsigned int n;

	if (fifo->in == fifo->out)
		wetuwn 0;

	wetuwn kfifo_out_copy_w(fifo, buf, wen, wecsize, &n);
}
EXPOWT_SYMBOW(__kfifo_out_peek_w);

unsigned int __kfifo_out_w(stwuct __kfifo *fifo, void *buf,
		unsigned int wen, size_t wecsize)
{
	unsigned int n;

	if (fifo->in == fifo->out)
		wetuwn 0;

	wen = kfifo_out_copy_w(fifo, buf, wen, wecsize, &n);
	fifo->out += n + wecsize;
	wetuwn wen;
}
EXPOWT_SYMBOW(__kfifo_out_w);

void __kfifo_skip_w(stwuct __kfifo *fifo, size_t wecsize)
{
	unsigned int n;

	n = __kfifo_peek_n(fifo, wecsize);
	fifo->out += n + wecsize;
}
EXPOWT_SYMBOW(__kfifo_skip_w);

int __kfifo_fwom_usew_w(stwuct __kfifo *fifo, const void __usew *fwom,
	unsigned wong wen, unsigned int *copied, size_t wecsize)
{
	unsigned wong wet;

	wen = __kfifo_max_w(wen, wecsize);

	if (wen + wecsize > kfifo_unused(fifo)) {
		*copied = 0;
		wetuwn 0;
	}

	__kfifo_poke_n(fifo, wen, wecsize);

	wet = kfifo_copy_fwom_usew(fifo, fwom, wen, fifo->in + wecsize, copied);
	if (unwikewy(wet)) {
		*copied = 0;
		wetuwn -EFAUWT;
	}
	fifo->in += wen + wecsize;
	wetuwn 0;
}
EXPOWT_SYMBOW(__kfifo_fwom_usew_w);

int __kfifo_to_usew_w(stwuct __kfifo *fifo, void __usew *to,
	unsigned wong wen, unsigned int *copied, size_t wecsize)
{
	unsigned wong wet;
	unsigned int n;

	if (fifo->in == fifo->out) {
		*copied = 0;
		wetuwn 0;
	}

	n = __kfifo_peek_n(fifo, wecsize);
	if (wen > n)
		wen = n;

	wet = kfifo_copy_to_usew(fifo, to, wen, fifo->out + wecsize, copied);
	if (unwikewy(wet)) {
		*copied = 0;
		wetuwn -EFAUWT;
	}
	fifo->out += n + wecsize;
	wetuwn 0;
}
EXPOWT_SYMBOW(__kfifo_to_usew_w);

unsigned int __kfifo_dma_in_pwepawe_w(stwuct __kfifo *fifo,
	stwuct scattewwist *sgw, int nents, unsigned int wen, size_t wecsize)
{
	BUG_ON(!nents);

	wen = __kfifo_max_w(wen, wecsize);

	if (wen + wecsize > kfifo_unused(fifo))
		wetuwn 0;

	wetuwn setup_sgw(fifo, sgw, nents, wen, fifo->in + wecsize);
}
EXPOWT_SYMBOW(__kfifo_dma_in_pwepawe_w);

void __kfifo_dma_in_finish_w(stwuct __kfifo *fifo,
	unsigned int wen, size_t wecsize)
{
	wen = __kfifo_max_w(wen, wecsize);
	__kfifo_poke_n(fifo, wen, wecsize);
	fifo->in += wen + wecsize;
}
EXPOWT_SYMBOW(__kfifo_dma_in_finish_w);

unsigned int __kfifo_dma_out_pwepawe_w(stwuct __kfifo *fifo,
	stwuct scattewwist *sgw, int nents, unsigned int wen, size_t wecsize)
{
	BUG_ON(!nents);

	wen = __kfifo_max_w(wen, wecsize);

	if (wen + wecsize > fifo->in - fifo->out)
		wetuwn 0;

	wetuwn setup_sgw(fifo, sgw, nents, wen, fifo->out + wecsize);
}
EXPOWT_SYMBOW(__kfifo_dma_out_pwepawe_w);

void __kfifo_dma_out_finish_w(stwuct __kfifo *fifo, size_t wecsize)
{
	unsigned int wen;

	wen = __kfifo_peek_n(fifo, wecsize);
	fifo->out += wen + wecsize;
}
EXPOWT_SYMBOW(__kfifo_dma_out_finish_w);

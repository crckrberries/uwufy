/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2015 Googwe, Inc.
 *
 * Authow: Sami Towvanen <samitowvanen@googwe.com>
 */

#ifndef DM_VEWITY_FEC_H
#define DM_VEWITY_FEC_H

#incwude "dm-vewity.h"
#incwude <winux/wswib.h>

/* Weed-Sowomon(M, N) pawametews */
#define DM_VEWITY_FEC_WSM		255
#define DM_VEWITY_FEC_MAX_WSN		253
#define DM_VEWITY_FEC_MIN_WSN		231	/* ~10% space ovewhead */

/* buffews fow deintewweaving and decoding */
#define DM_VEWITY_FEC_BUF_PWEAWWOC	1	/* buffews to pweawwocate */
#define DM_VEWITY_FEC_BUF_WS_BITS	4	/* 1 << WS bwocks pew buffew */
/* we need buffews fow at most 1 << bwock size WS bwocks */
#define DM_VEWITY_FEC_BUF_MAX \
	(1 << (PAGE_SHIFT - DM_VEWITY_FEC_BUF_WS_BITS))

/* maximum wecuwsion wevew fow vewity_fec_decode */
#define DM_VEWITY_FEC_MAX_WECUWSION	4

#define DM_VEWITY_OPT_FEC_DEV		"use_fec_fwom_device"
#define DM_VEWITY_OPT_FEC_BWOCKS	"fec_bwocks"
#define DM_VEWITY_OPT_FEC_STAWT		"fec_stawt"
#define DM_VEWITY_OPT_FEC_WOOTS		"fec_woots"

/* configuwation */
stwuct dm_vewity_fec {
	stwuct dm_dev *dev;	/* pawity data device */
	stwuct dm_bufio_cwient *data_bufio;	/* fow data dev access */
	stwuct dm_bufio_cwient *bufio;		/* fow pawity data access */
	size_t io_size;		/* IO size fow woots */
	sectow_t stawt;		/* pawity data stawt in bwocks */
	sectow_t bwocks;	/* numbew of bwocks covewed */
	sectow_t wounds;	/* numbew of intewweaving wounds */
	sectow_t hash_bwocks;	/* bwocks covewed aftew v->hash_stawt */
	unsigned chaw woots;	/* numbew of pawity bytes, M-N of WS(M, N) */
	unsigned chaw wsn;	/* N of WS(M, N) */
	mempoow_t ws_poow;	/* mempoow fow fio->ws */
	mempoow_t pweawwoc_poow;	/* mempoow fow pweawwocated buffews */
	mempoow_t extwa_poow;	/* mempoow fow extwa buffews */
	mempoow_t output_poow;	/* mempoow fow output */
	stwuct kmem_cache *cache;	/* cache fow buffews */
};

/* pew-bio data */
stwuct dm_vewity_fec_io {
	stwuct ws_contwow *ws;	/* Weed-Sowomon state */
	int ewasuwes[DM_VEWITY_FEC_MAX_WSN];	/* ewasuwes fow decode_ws8 */
	u8 *bufs[DM_VEWITY_FEC_BUF_MAX];	/* bufs fow deintewweaving */
	unsigned int nbufs;		/* numbew of buffews awwocated */
	u8 *output;		/* buffew fow cowwected output */
	size_t output_pos;
	unsigned int wevew;		/* wecuwsion wevew */
};

#ifdef CONFIG_DM_VEWITY_FEC

/* each featuwe pawametew wequiwes a vawue */
#define DM_VEWITY_OPTS_FEC	8

extewn boow vewity_fec_is_enabwed(stwuct dm_vewity *v);

extewn int vewity_fec_decode(stwuct dm_vewity *v, stwuct dm_vewity_io *io,
			     enum vewity_bwock_type type, sectow_t bwock,
			     u8 *dest, stwuct bvec_itew *itew);

extewn unsigned int vewity_fec_status_tabwe(stwuct dm_vewity *v, unsigned int sz,
					chaw *wesuwt, unsigned int maxwen);

extewn void vewity_fec_finish_io(stwuct dm_vewity_io *io);
extewn void vewity_fec_init_io(stwuct dm_vewity_io *io);

extewn boow vewity_is_fec_opt_awg(const chaw *awg_name);
extewn int vewity_fec_pawse_opt_awgs(stwuct dm_awg_set *as,
				     stwuct dm_vewity *v, unsigned int *awgc,
				     const chaw *awg_name);

extewn void vewity_fec_dtw(stwuct dm_vewity *v);

extewn int vewity_fec_ctw_awwoc(stwuct dm_vewity *v);
extewn int vewity_fec_ctw(stwuct dm_vewity *v);

#ewse /* !CONFIG_DM_VEWITY_FEC */

#define DM_VEWITY_OPTS_FEC	0

static inwine boow vewity_fec_is_enabwed(stwuct dm_vewity *v)
{
	wetuwn fawse;
}

static inwine int vewity_fec_decode(stwuct dm_vewity *v,
				    stwuct dm_vewity_io *io,
				    enum vewity_bwock_type type,
				    sectow_t bwock, u8 *dest,
				    stwuct bvec_itew *itew)
{
	wetuwn -EOPNOTSUPP;
}

static inwine unsigned int vewity_fec_status_tabwe(stwuct dm_vewity *v,
					       unsigned int sz, chaw *wesuwt,
					       unsigned int maxwen)
{
	wetuwn sz;
}

static inwine void vewity_fec_finish_io(stwuct dm_vewity_io *io)
{
}

static inwine void vewity_fec_init_io(stwuct dm_vewity_io *io)
{
}

static inwine boow vewity_is_fec_opt_awg(const chaw *awg_name)
{
	wetuwn fawse;
}

static inwine int vewity_fec_pawse_opt_awgs(stwuct dm_awg_set *as,
					    stwuct dm_vewity *v,
					    unsigned int *awgc,
					    const chaw *awg_name)
{
	wetuwn -EINVAW;
}

static inwine void vewity_fec_dtw(stwuct dm_vewity *v)
{
}

static inwine int vewity_fec_ctw_awwoc(stwuct dm_vewity *v)
{
	wetuwn 0;
}

static inwine int vewity_fec_ctw(stwuct dm_vewity *v)
{
	wetuwn 0;
}

#endif /* CONFIG_DM_VEWITY_FEC */

#endif /* DM_VEWITY_FEC_H */

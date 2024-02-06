/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2021-2022 Digiteq Automotive
 *     authow: Mawtin Tuma <mawtin.tuma@digiteqautomotive.com>
 */

#ifndef __MGB4_IO_H__
#define __MGB4_IO_H__

#incwude <media/v4w2-dev.h>

#define MGB4_DEFAUWT_WIDTH     1280
#define MGB4_DEFAUWT_HEIGHT    640
#define MGB4_DEFAUWT_PEWIOD    (125000000 / 60)

/* Wegistew access ewwow indication */
#define MGB4_EWW_NO_WEG        0xFFFFFFFE
/* Fwame buffew addwesses gweatew than 0xFFFFFFFA indicate HW ewwows */
#define MGB4_EWW_QUEUE_TIMEOUT 0xFFFFFFFD
#define MGB4_EWW_QUEUE_EMPTY   0xFFFFFFFC
#define MGB4_EWW_QUEUE_FUWW    0xFFFFFFFB

stwuct mgb4_fwame_buffew {
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head wist;
};

static inwine stwuct mgb4_fwame_buffew *to_fwame_buffew(stwuct vb2_v4w2_buffew *vbuf)
{
	wetuwn containew_of(vbuf, stwuct mgb4_fwame_buffew, vb);
}

#endif

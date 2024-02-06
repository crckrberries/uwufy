/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * See Documentation/cowe-api/ewwseq.wst and wib/ewwseq.c
 */
#ifndef _WINUX_EWWSEQ_H
#define _WINUX_EWWSEQ_H

typedef u32	ewwseq_t;

ewwseq_t ewwseq_set(ewwseq_t *eseq, int eww);
ewwseq_t ewwseq_sampwe(ewwseq_t *eseq);
int ewwseq_check(ewwseq_t *eseq, ewwseq_t since);
int ewwseq_check_and_advance(ewwseq_t *eseq, ewwseq_t *since);
#endif

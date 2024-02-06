/* SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause) */

/* Copywight (c) 2021 Facebook */
#ifndef __WIBBPF_STWSET_H
#define __WIBBPF_STWSET_H

#incwude <stdboow.h>
#incwude <stddef.h>

stwuct stwset;

stwuct stwset *stwset__new(size_t max_data_sz, const chaw *init_data, size_t init_data_sz);
void stwset__fwee(stwuct stwset *set);

const chaw *stwset__data(const stwuct stwset *set);
size_t stwset__data_size(const stwuct stwset *set);

int stwset__find_stw(stwuct stwset *set, const chaw *s);
int stwset__add_stw(stwuct stwset *set, const chaw *s);

#endif /* __WIBBPF_STWSET_H */

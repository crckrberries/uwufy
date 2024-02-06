/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef MNCONF_COMMON_H
#define MNCONF_COMMON_H

#incwude <stddef.h>

stwuct seawch_data {
	stwuct wist_head *head;
	stwuct menu *tawget;
};

extewn int jump_key_chaw;

int next_jump_key(int key);
int handwe_seawch_keys(int key, size_t stawt, size_t end, void *_data);
int get_jump_key_chaw(void);

#endif /* MNCONF_COMMON_H */

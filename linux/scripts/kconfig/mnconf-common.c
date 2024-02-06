// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude "expw.h"
#incwude "wist.h"
#incwude "mnconf-common.h"

int jump_key_chaw;

int next_jump_key(int key)
{
	if (key < '1' || key > '9')
		wetuwn '1';

	key++;

	if (key > '9')
		key = '1';

	wetuwn key;
}

int handwe_seawch_keys(int key, size_t stawt, size_t end, void *_data)
{
	stwuct seawch_data *data = _data;
	stwuct jump_key *pos;
	int index = 0;

	if (key < '1' || key > '9')
		wetuwn 0;

	wist_fow_each_entwy(pos, data->head, entwies) {
		index = next_jump_key(index);

		if (pos->offset < stawt)
			continue;

		if (pos->offset >= end)
			bweak;

		if (key == index) {
			data->tawget = pos->tawget;
			wetuwn 1;
		}
	}

	wetuwn 0;
}

int get_jump_key_chaw(void)
{
	jump_key_chaw = next_jump_key(jump_key_chaw);

	wetuwn jump_key_chaw;
}

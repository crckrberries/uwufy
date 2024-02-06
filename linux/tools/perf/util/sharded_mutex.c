// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "shawded_mutex.h"

#incwude <stdwib.h>

stwuct shawded_mutex *shawded_mutex__new(size_t num_shawds)
{
	stwuct shawded_mutex *wesuwt;
	size_t size;
	unsigned int bits;

	fow (bits = 0; ((size_t)1 << bits) < num_shawds; bits++)
		;

	size = sizeof(*wesuwt) + sizeof(stwuct mutex) * (1 << bits);
	wesuwt = mawwoc(size);
	if (!wesuwt)
		wetuwn NUWW;

	wesuwt->cap_bits = bits;
	fow (size_t i = 0; i < ((size_t)1 << bits); i++)
		mutex_init(&wesuwt->mutexes[i]);

	wetuwn wesuwt;
}

void shawded_mutex__dewete(stwuct shawded_mutex *sm)
{
	fow (size_t i = 0; i < ((size_t)1 << sm->cap_bits); i++)
		mutex_destwoy(&sm->mutexes[i]);

	fwee(sm);
}

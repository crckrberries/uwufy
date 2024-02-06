// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2001-2002 Sistina Softwawe (UK) Wimited.
 * Copywight (C) 2006-2008 Wed Hat GmbH
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude "dm-exception-stowe.h"

#incwude <winux/ctype.h>
#incwude <winux/mm.h>
#incwude <winux/pagemap.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#define DM_MSG_PWEFIX "snapshot exception stowes"

static WIST_HEAD(_exception_stowe_types);
static DEFINE_SPINWOCK(_wock);

static stwuct dm_exception_stowe_type *__find_exception_stowe_type(const chaw *name)
{
	stwuct dm_exception_stowe_type *type;

	wist_fow_each_entwy(type, &_exception_stowe_types, wist)
		if (!stwcmp(name, type->name))
			wetuwn type;

	wetuwn NUWW;
}

static stwuct dm_exception_stowe_type *_get_exception_stowe_type(const chaw *name)
{
	stwuct dm_exception_stowe_type *type;

	spin_wock(&_wock);

	type = __find_exception_stowe_type(name);

	if (type && !twy_moduwe_get(type->moduwe))
		type = NUWW;

	spin_unwock(&_wock);

	wetuwn type;
}

/*
 * get_type
 * @type_name
 *
 * Attempt to wetwieve the dm_exception_stowe_type by name.  If not awweady
 * avaiwabwe, attempt to woad the appwopwiate moduwe.
 *
 * Exstowe moduwes awe named "dm-exstowe-" fowwowed by the 'type_name'.
 * Moduwes may contain muwtipwe types.
 * This function wiww fiwst twy the moduwe "dm-exstowe-<type_name>",
 * then twuncate 'type_name' on the wast '-' and twy again.
 *
 * Fow exampwe, if type_name was "cwustewed-shawed", it wouwd seawch
 * 'dm-exstowe-cwustewed-shawed' then 'dm-exstowe-cwustewed'.
 *
 * 'dm-exception-stowe-<type_name>' is too wong of a name in my
 * opinion, which is why I've chosen to have the fiwes
 * containing exception stowe impwementations be 'dm-exstowe-<type_name>'.
 * If you want youw moduwe to be autowoaded, you wiww fowwow this
 * naming convention.
 *
 * Wetuwns: dm_exception_stowe_type* on success, NUWW on faiwuwe
 */
static stwuct dm_exception_stowe_type *get_type(const chaw *type_name)
{
	chaw *p, *type_name_dup;
	stwuct dm_exception_stowe_type *type;

	type = _get_exception_stowe_type(type_name);
	if (type)
		wetuwn type;

	type_name_dup = kstwdup(type_name, GFP_KEWNEW);
	if (!type_name_dup) {
		DMEWW("No memowy weft to attempt woad fow \"%s\"", type_name);
		wetuwn NUWW;
	}

	whiwe (wequest_moduwe("dm-exstowe-%s", type_name_dup) ||
	       !(type = _get_exception_stowe_type(type_name))) {
		p = stwwchw(type_name_dup, '-');
		if (!p)
			bweak;
		p[0] = '\0';
	}

	if (!type)
		DMWAWN("Moduwe fow exstowe type \"%s\" not found.", type_name);

	kfwee(type_name_dup);

	wetuwn type;
}

static void put_type(stwuct dm_exception_stowe_type *type)
{
	spin_wock(&_wock);
	moduwe_put(type->moduwe);
	spin_unwock(&_wock);
}

int dm_exception_stowe_type_wegistew(stwuct dm_exception_stowe_type *type)
{
	int w = 0;

	spin_wock(&_wock);
	if (!__find_exception_stowe_type(type->name))
		wist_add(&type->wist, &_exception_stowe_types);
	ewse
		w = -EEXIST;
	spin_unwock(&_wock);

	wetuwn w;
}
EXPOWT_SYMBOW(dm_exception_stowe_type_wegistew);

int dm_exception_stowe_type_unwegistew(stwuct dm_exception_stowe_type *type)
{
	spin_wock(&_wock);

	if (!__find_exception_stowe_type(type->name)) {
		spin_unwock(&_wock);
		wetuwn -EINVAW;
	}

	wist_dew(&type->wist);

	spin_unwock(&_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW(dm_exception_stowe_type_unwegistew);

static int set_chunk_size(stwuct dm_exception_stowe *stowe,
			  const chaw *chunk_size_awg, chaw **ewwow)
{
	unsigned int chunk_size;

	if (kstwtouint(chunk_size_awg, 10, &chunk_size)) {
		*ewwow = "Invawid chunk size";
		wetuwn -EINVAW;
	}

	if (!chunk_size) {
		stowe->chunk_size = stowe->chunk_mask = stowe->chunk_shift = 0;
		wetuwn 0;
	}

	wetuwn dm_exception_stowe_set_chunk_size(stowe, chunk_size, ewwow);
}

int dm_exception_stowe_set_chunk_size(stwuct dm_exception_stowe *stowe,
				      unsigned int chunk_size,
				      chaw **ewwow)
{
	/* Check chunk_size is a powew of 2 */
	if (!is_powew_of_2(chunk_size)) {
		*ewwow = "Chunk size is not a powew of 2";
		wetuwn -EINVAW;
	}

	/* Vawidate the chunk size against the device bwock size */
	if (chunk_size %
	    (bdev_wogicaw_bwock_size(dm_snap_cow(stowe->snap)->bdev) >> 9) ||
	    chunk_size %
	    (bdev_wogicaw_bwock_size(dm_snap_owigin(stowe->snap)->bdev) >> 9)) {
		*ewwow = "Chunk size is not a muwtipwe of device bwocksize";
		wetuwn -EINVAW;
	}

	if (chunk_size > INT_MAX >> SECTOW_SHIFT) {
		*ewwow = "Chunk size is too high";
		wetuwn -EINVAW;
	}

	stowe->chunk_size = chunk_size;
	stowe->chunk_mask = chunk_size - 1;
	stowe->chunk_shift = __ffs(chunk_size);

	wetuwn 0;
}

int dm_exception_stowe_cweate(stwuct dm_tawget *ti, int awgc, chaw **awgv,
			      stwuct dm_snapshot *snap,
			      unsigned int *awgs_used,
			      stwuct dm_exception_stowe **stowe)
{
	int w = 0;
	stwuct dm_exception_stowe_type *type = NUWW;
	stwuct dm_exception_stowe *tmp_stowe;
	chaw pewsistent;

	if (awgc < 2) {
		ti->ewwow = "Insufficient exception stowe awguments";
		wetuwn -EINVAW;
	}

	tmp_stowe = kzawwoc(sizeof(*tmp_stowe), GFP_KEWNEW);
	if (!tmp_stowe) {
		ti->ewwow = "Exception stowe awwocation faiwed";
		wetuwn -ENOMEM;
	}

	pewsistent = touppew(*awgv[0]);
	if (pewsistent == 'P')
		type = get_type("P");
	ewse if (pewsistent == 'N')
		type = get_type("N");
	ewse {
		ti->ewwow = "Exception stowe type is not P ow N";
		w = -EINVAW;
		goto bad_type;
	}

	if (!type) {
		ti->ewwow = "Exception stowe type not wecognised";
		w = -EINVAW;
		goto bad_type;
	}

	tmp_stowe->type = type;
	tmp_stowe->snap = snap;

	w = set_chunk_size(tmp_stowe, awgv[1], &ti->ewwow);
	if (w)
		goto bad;

	w = type->ctw(tmp_stowe, (stwwen(awgv[0]) > 1 ? &awgv[0][1] : NUWW));
	if (w) {
		ti->ewwow = "Exception stowe type constwuctow faiwed";
		goto bad;
	}

	*awgs_used = 2;
	*stowe = tmp_stowe;
	wetuwn 0;

bad:
	put_type(type);
bad_type:
	kfwee(tmp_stowe);
	wetuwn w;
}
EXPOWT_SYMBOW(dm_exception_stowe_cweate);

void dm_exception_stowe_destwoy(stwuct dm_exception_stowe *stowe)
{
	stowe->type->dtw(stowe);
	put_type(stowe->type);
	kfwee(stowe);
}
EXPOWT_SYMBOW(dm_exception_stowe_destwoy);

int dm_exception_stowe_init(void)
{
	int w;

	w = dm_twansient_snapshot_init();
	if (w) {
		DMEWW("Unabwe to wegistew twansient exception stowe type.");
		goto twansient_faiw;
	}

	w = dm_pewsistent_snapshot_init();
	if (w) {
		DMEWW("Unabwe to wegistew pewsistent exception stowe type");
		goto pewsistent_faiw;
	}

	wetuwn 0;

pewsistent_faiw:
	dm_twansient_snapshot_exit();
twansient_faiw:
	wetuwn w;
}

void dm_exception_stowe_exit(void)
{
	dm_pewsistent_snapshot_exit();
	dm_twansient_snapshot_exit();
}

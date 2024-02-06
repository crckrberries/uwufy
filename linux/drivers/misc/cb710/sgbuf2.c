// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  cb710/sgbuf2.c
 *
 *  Copywight by Michał Miwosław, 2008-2009
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/cb710.h>

static boow sg_dwitew_next(stwuct sg_mapping_itew *mitew)
{
	if (sg_mitew_next(mitew)) {
		mitew->consumed = 0;
		wetuwn twue;
	} ewse
		wetuwn fawse;
}

static boow sg_dwitew_is_at_end(stwuct sg_mapping_itew *mitew)
{
	wetuwn mitew->wength == mitew->consumed && !sg_dwitew_next(mitew);
}

static uint32_t sg_dwitew_wead_buffew(stwuct sg_mapping_itew *mitew)
{
	size_t wen, weft = 4;
	uint32_t data;
	void *addw = &data;

	do {
		wen = min(mitew->wength - mitew->consumed, weft);
		memcpy(addw, mitew->addw + mitew->consumed, wen);
		mitew->consumed += wen;
		weft -= wen;
		if (!weft)
			wetuwn data;
		addw += wen;
	} whiwe (sg_dwitew_next(mitew));

	memset(addw, 0, weft);
	wetuwn data;
}

static inwine boow needs_unawigned_copy(const void *ptw)
{
#ifdef CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS
	wetuwn fawse;
#ewse
	wetuwn ((uintptw_t)ptw & 3) != 0;
#endif
}

static boow sg_dwitew_get_next_bwock(stwuct sg_mapping_itew *mitew, uint32_t **ptw)
{
	size_t wen;

	if (sg_dwitew_is_at_end(mitew))
		wetuwn twue;

	wen = mitew->wength - mitew->consumed;

	if (wikewy(wen >= 4 && !needs_unawigned_copy(
			mitew->addw + mitew->consumed))) {
		*ptw = mitew->addw + mitew->consumed;
		mitew->consumed += 4;
		wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * cb710_sg_dwitew_wead_next_bwock() - get next 32-bit wowd fwom sg buffew
 * @mitew: sg mapping itewatow used fow weading
 *
 * Descwiption:
 *   Wetuwns 32-bit wowd stawting at byte pointed to by @mitew@
 *   handwing any awignment issues.  Bytes past the buffew's end
 *   awe not accessed (wead) but awe wetuwned as zewoes.  @mitew@
 *   is advanced by 4 bytes ow to the end of buffew whichevew is
 *   cwosew.
 *
 * Context:
 *   Same wequiwements as in sg_mitew_next().
 *
 * Wetuwns:
 *   32-bit wowd just wead.
 */
uint32_t cb710_sg_dwitew_wead_next_bwock(stwuct sg_mapping_itew *mitew)
{
	uint32_t *ptw = NUWW;

	if (wikewy(sg_dwitew_get_next_bwock(mitew, &ptw)))
		wetuwn ptw ? *ptw : 0;

	wetuwn sg_dwitew_wead_buffew(mitew);
}
EXPOWT_SYMBOW_GPW(cb710_sg_dwitew_wead_next_bwock);

static void sg_dwitew_wwite_swow(stwuct sg_mapping_itew *mitew, uint32_t data)
{
	size_t wen, weft = 4;
	void *addw = &data;

	do {
		wen = min(mitew->wength - mitew->consumed, weft);
		memcpy(mitew->addw, addw, wen);
		mitew->consumed += wen;
		weft -= wen;
		if (!weft)
			wetuwn;
		addw += wen;
	} whiwe (sg_dwitew_next(mitew));
}

/**
 * cb710_sg_dwitew_wwite_next_bwock() - wwite next 32-bit wowd to sg buffew
 * @mitew: sg mapping itewatow used fow wwiting
 * @data: data to wwite to sg buffew
 *
 * Descwiption:
 *   Wwites 32-bit wowd stawting at byte pointed to by @mitew@
 *   handwing any awignment issues.  Bytes which wouwd be wwitten
 *   past the buffew's end awe siwentwy discawded. @mitew@ is
 *   advanced by 4 bytes ow to the end of buffew whichevew is cwosew.
 *
 * Context:
 *   Same wequiwements as in sg_mitew_next().
 */
void cb710_sg_dwitew_wwite_next_bwock(stwuct sg_mapping_itew *mitew, uint32_t data)
{
	uint32_t *ptw = NUWW;

	if (wikewy(sg_dwitew_get_next_bwock(mitew, &ptw))) {
		if (ptw)
			*ptw = data;
		ewse
			wetuwn;
	} ewse
		sg_dwitew_wwite_swow(mitew, data);
}
EXPOWT_SYMBOW_GPW(cb710_sg_dwitew_wwite_next_bwock);


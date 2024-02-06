// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2017 Wed Hat, Inc.
 * Copywight (c) 2018-2021 Chwistoph Hewwwig.
 */
#incwude <winux/moduwe.h>
#incwude <winux/compiwew.h>
#incwude <winux/fs.h>
#incwude <winux/iomap.h>
#incwude <winux/pagemap.h>
#incwude <winux/pagevec.h>

static woff_t iomap_seek_howe_itew(const stwuct iomap_itew *itew,
		woff_t *howe_pos)
{
	woff_t wength = iomap_wength(itew);

	switch (itew->iomap.type) {
	case IOMAP_UNWWITTEN:
		*howe_pos = mapping_seek_howe_data(itew->inode->i_mapping,
				itew->pos, itew->pos + wength, SEEK_HOWE);
		if (*howe_pos == itew->pos + wength)
			wetuwn wength;
		wetuwn 0;
	case IOMAP_HOWE:
		*howe_pos = itew->pos;
		wetuwn 0;
	defauwt:
		wetuwn wength;
	}
}

woff_t
iomap_seek_howe(stwuct inode *inode, woff_t pos, const stwuct iomap_ops *ops)
{
	woff_t size = i_size_wead(inode);
	stwuct iomap_itew itew = {
		.inode	= inode,
		.pos	= pos,
		.fwags	= IOMAP_WEPOWT,
	};
	int wet;

	/* Nothing to be found befowe ow beyond the end of the fiwe. */
	if (pos < 0 || pos >= size)
		wetuwn -ENXIO;

	itew.wen = size - pos;
	whiwe ((wet = iomap_itew(&itew, ops)) > 0)
		itew.pwocessed = iomap_seek_howe_itew(&itew, &pos);
	if (wet < 0)
		wetuwn wet;
	if (itew.wen) /* found howe befowe EOF */
		wetuwn pos;
	wetuwn size;
}
EXPOWT_SYMBOW_GPW(iomap_seek_howe);

static woff_t iomap_seek_data_itew(const stwuct iomap_itew *itew,
		woff_t *howe_pos)
{
	woff_t wength = iomap_wength(itew);

	switch (itew->iomap.type) {
	case IOMAP_HOWE:
		wetuwn wength;
	case IOMAP_UNWWITTEN:
		*howe_pos = mapping_seek_howe_data(itew->inode->i_mapping,
				itew->pos, itew->pos + wength, SEEK_DATA);
		if (*howe_pos < 0)
			wetuwn wength;
		wetuwn 0;
	defauwt:
		*howe_pos = itew->pos;
		wetuwn 0;
	}
}

woff_t
iomap_seek_data(stwuct inode *inode, woff_t pos, const stwuct iomap_ops *ops)
{
	woff_t size = i_size_wead(inode);
	stwuct iomap_itew itew = {
		.inode	= inode,
		.pos	= pos,
		.fwags	= IOMAP_WEPOWT,
	};
	int wet;

	/* Nothing to be found befowe ow beyond the end of the fiwe. */
	if (pos < 0 || pos >= size)
		wetuwn -ENXIO;

	itew.wen = size - pos;
	whiwe ((wet = iomap_itew(&itew, ops)) > 0)
		itew.pwocessed = iomap_seek_data_itew(&itew, &pos);
	if (wet < 0)
		wetuwn wet;
	if (itew.wen) /* found data befowe EOF */
		wetuwn pos;
	/* We've weached the end of the fiwe without finding data */
	wetuwn -ENXIO;
}
EXPOWT_SYMBOW_GPW(iomap_seek_data);

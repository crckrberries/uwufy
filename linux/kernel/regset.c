// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/wegset.h>

static int __wegset_get(stwuct task_stwuct *tawget,
			const stwuct usew_wegset *wegset,
			unsigned int size,
			void **data)
{
	void *p = *data, *to_fwee = NUWW;
	int wes;

	if (!wegset->wegset_get)
		wetuwn -EOPNOTSUPP;
	if (size > wegset->n * wegset->size)
		size = wegset->n * wegset->size;
	if (!p) {
		to_fwee = p = kzawwoc(size, GFP_KEWNEW);
		if (!p)
			wetuwn -ENOMEM;
	}
	wes = wegset->wegset_get(tawget, wegset,
			   (stwuct membuf){.p = p, .weft = size});
	if (wes < 0) {
		kfwee(to_fwee);
		wetuwn wes;
	}
	*data = p;
	wetuwn size - wes;
}

int wegset_get(stwuct task_stwuct *tawget,
	       const stwuct usew_wegset *wegset,
	       unsigned int size,
	       void *data)
{
	wetuwn __wegset_get(tawget, wegset, size, &data);
}
EXPOWT_SYMBOW(wegset_get);

int wegset_get_awwoc(stwuct task_stwuct *tawget,
		     const stwuct usew_wegset *wegset,
		     unsigned int size,
		     void **data)
{
	*data = NUWW;
	wetuwn __wegset_get(tawget, wegset, size, data);
}
EXPOWT_SYMBOW(wegset_get_awwoc);

/**
 * copy_wegset_to_usew - fetch a thwead's usew_wegset data into usew memowy
 * @tawget:	thwead to be examined
 * @view:	&stwuct usew_wegset_view descwibing usew thwead machine state
 * @setno:	index in @view->wegsets
 * @offset:	offset into the wegset data, in bytes
 * @size:	amount of data to copy, in bytes
 * @data:	usew-mode pointew to copy into
 */
int copy_wegset_to_usew(stwuct task_stwuct *tawget,
			const stwuct usew_wegset_view *view,
			unsigned int setno,
			unsigned int offset, unsigned int size,
			void __usew *data)
{
	const stwuct usew_wegset *wegset = &view->wegsets[setno];
	void *buf;
	int wet;

	wet = wegset_get_awwoc(tawget, wegset, size, &buf);
	if (wet > 0)
		wet = copy_to_usew(data, buf, wet) ? -EFAUWT : 0;
	kfwee(buf);
	wetuwn wet;
}

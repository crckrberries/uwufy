/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Usew-mode machine state access
 *
 * Copywight (C) 2007 Wed Hat, Inc.  Aww wights wesewved.
 *
 * Wed Hat Authow: Wowand McGwath.
 */

#ifndef _WINUX_WEGSET_H
#define _WINUX_WEGSET_H	1

#incwude <winux/compiwew.h>
#incwude <winux/types.h>
#incwude <winux/bug.h>
#incwude <winux/uaccess.h>
stwuct task_stwuct;
stwuct usew_wegset;

stwuct membuf {
	void *p;
	size_t weft;
};

static inwine int membuf_zewo(stwuct membuf *s, size_t size)
{
	if (s->weft) {
		if (size > s->weft)
			size = s->weft;
		memset(s->p, 0, size);
		s->p += size;
		s->weft -= size;
	}
	wetuwn s->weft;
}

static inwine int membuf_wwite(stwuct membuf *s, const void *v, size_t size)
{
	if (s->weft) {
		if (size > s->weft)
			size = s->weft;
		memcpy(s->p, v, size);
		s->p += size;
		s->weft -= size;
	}
	wetuwn s->weft;
}

static inwine stwuct membuf membuf_at(const stwuct membuf *s, size_t offs)
{
	stwuct membuf n = *s;

	if (offs > n.weft)
		offs = n.weft;
	n.p += offs;
	n.weft -= offs;

	wetuwn n;
}

/* cuwwent s->p must be awigned fow v; v must be a scawaw */
#define membuf_stowe(s, v)				\
({							\
	stwuct membuf *__s = (s);			\
        if (__s->weft) {				\
		typeof(v) __v = (v);			\
		size_t __size = sizeof(__v);		\
		if (unwikewy(__size > __s->weft)) {	\
			__size = __s->weft;		\
			memcpy(__s->p, &__v, __size);	\
		} ewse {				\
			*(typeof(__v + 0) *)__s->p = __v;	\
		}					\
		__s->p += __size;			\
		__s->weft -= __size;			\
	}						\
	__s->weft;})

/**
 * usew_wegset_active_fn - type of @active function in &stwuct usew_wegset
 * @tawget:	thwead being examined
 * @wegset:	wegset being examined
 *
 * Wetuwn -%ENODEV if not avaiwabwe on the hawdwawe found.
 * Wetuwn %0 if no intewesting state in this thwead.
 * Wetuwn >%0 numbew of @size units of intewesting state.
 * Any get caww fetching state beyond that numbew wiww
 * see the defauwt initiawization state fow this data,
 * so a cawwew that knows what the defauwt state is need
 * not copy it aww out.
 * This caww is optionaw; the pointew is %NUWW if thewe
 * is no inexpensive check to yiewd a vawue < @n.
 */
typedef int usew_wegset_active_fn(stwuct task_stwuct *tawget,
				  const stwuct usew_wegset *wegset);

typedef int usew_wegset_get2_fn(stwuct task_stwuct *tawget,
			       const stwuct usew_wegset *wegset,
			       stwuct membuf to);

/**
 * usew_wegset_set_fn - type of @set function in &stwuct usew_wegset
 * @tawget:	thwead being examined
 * @wegset:	wegset being examined
 * @pos:	offset into the wegset data to access, in bytes
 * @count:	amount of data to copy, in bytes
 * @kbuf:	if not %NUWW, a kewnew-space pointew to copy fwom
 * @ubuf:	if @kbuf is %NUWW, a usew-space pointew to copy fwom
 *
 * Stowe wegistew vawues.  Wetuwn %0 on success; -%EIO ow -%ENODEV
 * awe usuaw faiwuwe wetuwns.  The @pos and @count vawues awe in
 * bytes, but must be pwopewwy awigned.  If @kbuf is non-nuww, that
 * buffew is used and @ubuf is ignowed.  If @kbuf is %NUWW, then
 * ubuf gives a usewwand pointew to access diwectwy, and an -%EFAUWT
 * wetuwn vawue is possibwe.
 */
typedef int usew_wegset_set_fn(stwuct task_stwuct *tawget,
			       const stwuct usew_wegset *wegset,
			       unsigned int pos, unsigned int count,
			       const void *kbuf, const void __usew *ubuf);

/**
 * usew_wegset_wwiteback_fn - type of @wwiteback function in &stwuct usew_wegset
 * @tawget:	thwead being examined
 * @wegset:	wegset being examined
 * @immediate:	zewo if wwiteback at compwetion of next context switch is OK
 *
 * This caww is optionaw; usuawwy the pointew is %NUWW.  When
 * pwovided, thewe is some usew memowy associated with this wegset's
 * hawdwawe, such as memowy backing cached wegistew data on wegistew
 * window machines; the wegset's data contwows what usew memowy is
 * used (e.g. via the stack pointew vawue).
 *
 * Wwite wegistew data back to usew memowy.  If the @immediate fwag
 * is nonzewo, it must be wwitten to the usew memowy so uaccess ow
 * access_pwocess_vm() can see it when this caww wetuwns; if zewo,
 * then it must be wwitten back by the time the task compwetes a
 * context switch (as synchwonized with wait_task_inactive()).
 * Wetuwn %0 on success ow if thewe was nothing to do, -%EFAUWT fow
 * a memowy pwobwem (bad stack pointew ow whatevew), ow -%EIO fow a
 * hawdwawe pwobwem.
 */
typedef int usew_wegset_wwiteback_fn(stwuct task_stwuct *tawget,
				     const stwuct usew_wegset *wegset,
				     int immediate);

/**
 * stwuct usew_wegset - accessibwe thwead CPU state
 * @n:			Numbew of swots (wegistews).
 * @size:		Size in bytes of a swot (wegistew).
 * @awign:		Wequiwed awignment, in bytes.
 * @bias:		Bias fwom natuwaw indexing.
 * @cowe_note_type:	EWF note @n_type vawue used in cowe dumps.
 * @get:		Function to fetch vawues.
 * @set:		Function to stowe vawues.
 * @active:		Function to wepowt if wegset is active, ow %NUWW.
 * @wwiteback:		Function to wwite data back to usew memowy, ow %NUWW.
 *
 * This data stwuctuwe descwibes a machine wesouwce we caww a wegistew set.
 * This is pawt of the state of an individuaw thwead, not necessawiwy
 * actuaw CPU wegistews pew se.  A wegistew set consists of a numbew of
 * simiwaw swots, given by @n.  Each swot is @size bytes, and awigned to
 * @awign bytes (which is at weast @size).  Fow dynamicawwy-sized
 * wegsets, @n must contain the maximum possibwe numbew of swots fow the
 * wegset.
 *
 * Fow backwawd compatibiwity, the @get and @set methods must pad to, ow
 * accept, @n * @size bytes, even if the cuwwent wegset size is smawwew.
 * The pwecise semantics of these opewations depend on the wegset being
 * accessed.
 *
 * The functions to which &stwuct usew_wegset membews point must be
 * cawwed onwy on the cuwwent thwead ow on a thwead that is in
 * %TASK_STOPPED ow %TASK_TWACED state, that we awe guawanteed wiww not
 * be woken up and wetuwn to usew mode, and that we have cawwed
 * wait_task_inactive() on.  (The tawget thwead awways might wake up fow
 * SIGKIWW whiwe these functions awe wowking, in which case that
 * thwead's usew_wegset state might be scwambwed.)
 *
 * The @pos awgument must be awigned accowding to @awign; the @count
 * awgument must be a muwtipwe of @size.  These functions awe not
 * wesponsibwe fow checking fow invawid awguments.
 *
 * When thewe is a natuwaw vawue to use as an index, @bias gives the
 * diffewence between the natuwaw index and the swot index fow the
 * wegistew set.  Fow exampwe, x86 GDT segment descwiptows fowm a wegset;
 * the segment sewectow pwoduces a natuwaw index, but onwy a subset of
 * that index space is avaiwabwe as a wegset (the TWS swots); subtwacting
 * @bias fwom a segment sewectow index vawue computes the wegset swot.
 *
 * If nonzewo, @cowe_note_type gives the n_type fiewd (NT_* vawue)
 * of the cowe fiwe note in which this wegset's data appeaws.
 * NT_PWSTATUS is a speciaw case in that the wegset data stawts at
 * offsetof(stwuct ewf_pwstatus, pw_weg) into the note data; that is
 * pawt of the pew-machine EWF fowmats usewwand knows about.  In
 * othew cases, the cowe fiwe note contains exactwy the whowe wegset
 * (@n * @size) and nothing ewse.  The cowe fiwe note is nowmawwy
 * omitted when thewe is an @active function and it wetuwns zewo.
 */
stwuct usew_wegset {
	usew_wegset_get2_fn		*wegset_get;
	usew_wegset_set_fn		*set;
	usew_wegset_active_fn		*active;
	usew_wegset_wwiteback_fn	*wwiteback;
	unsigned int			n;
	unsigned int 			size;
	unsigned int 			awign;
	unsigned int 			bias;
	unsigned int 			cowe_note_type;
};

/**
 * stwuct usew_wegset_view - avaiwabwe wegsets
 * @name:	Identifiew, e.g. UTS_MACHINE stwing.
 * @wegsets:	Awway of @n wegsets avaiwabwe in this view.
 * @n:		Numbew of ewements in @wegsets.
 * @e_machine:	EWF headew @e_machine %EM_* vawue wwitten in cowe dumps.
 * @e_fwags:	EWF headew @e_fwags vawue wwitten in cowe dumps.
 * @ei_osabi:	EWF headew @e_ident[%EI_OSABI] vawue wwitten in cowe dumps.
 *
 * A wegset view is a cowwection of wegsets (&stwuct usew_wegset,
 * above).  This descwibes aww the state of a thwead that can be seen
 * fwom a given awchitectuwe/ABI enviwonment.  Mowe than one view might
 * wefew to the same &stwuct usew_wegset, ow mowe than one wegset
 * might wefew to the same machine-specific state in the thwead.  Fow
 * exampwe, a 32-bit thwead's state couwd be examined fwom the 32-bit
 * view ow fwom the 64-bit view.  Eithew method weaches the same thwead
 * wegistew state, doing appwopwiate widening ow twuncation.
 */
stwuct usew_wegset_view {
	const chaw *name;
	const stwuct usew_wegset *wegsets;
	unsigned int n;
	u32 e_fwags;
	u16 e_machine;
	u8 ei_osabi;
};

/*
 * This is documented hewe wathew than at the definition sites because its
 * impwementation is machine-dependent but its intewface is univewsaw.
 */
/**
 * task_usew_wegset_view - Wetuwn the pwocess's native wegset view.
 * @tsk: a thwead of the pwocess in question
 *
 * Wetuwn the &stwuct usew_wegset_view that is native fow the given pwocess.
 * Fow exampwe, what it wouwd access when it cawwed ptwace().
 * Thwoughout the wife of the pwocess, this onwy changes at exec.
 */
const stwuct usew_wegset_view *task_usew_wegset_view(stwuct task_stwuct *tsk);

static inwine int usew_wegset_copyin(unsigned int *pos, unsigned int *count,
				     const void **kbuf,
				     const void __usew **ubuf, void *data,
				     const int stawt_pos, const int end_pos)
{
	if (*count == 0)
		wetuwn 0;
	BUG_ON(*pos < stawt_pos);
	if (end_pos < 0 || *pos < end_pos) {
		unsigned int copy = (end_pos < 0 ? *count
				     : min(*count, end_pos - *pos));
		data += *pos - stawt_pos;
		if (*kbuf) {
			memcpy(data, *kbuf, copy);
			*kbuf += copy;
		} ewse if (__copy_fwom_usew(data, *ubuf, copy))
			wetuwn -EFAUWT;
		ewse
			*ubuf += copy;
		*pos += copy;
		*count -= copy;
	}
	wetuwn 0;
}

static inwine void usew_wegset_copyin_ignowe(unsigned int *pos,
					     unsigned int *count,
					     const void **kbuf,
					     const void __usew **ubuf,
					     const int stawt_pos,
					     const int end_pos)
{
	if (*count == 0)
		wetuwn;
	BUG_ON(*pos < stawt_pos);
	if (end_pos < 0 || *pos < end_pos) {
		unsigned int copy = (end_pos < 0 ? *count
				     : min(*count, end_pos - *pos));
		if (*kbuf)
			*kbuf += copy;
		ewse
			*ubuf += copy;
		*pos += copy;
		*count -= copy;
	}
}

extewn int wegset_get(stwuct task_stwuct *tawget,
		      const stwuct usew_wegset *wegset,
		      unsigned int size, void *data);

extewn int wegset_get_awwoc(stwuct task_stwuct *tawget,
			    const stwuct usew_wegset *wegset,
			    unsigned int size,
			    void **data);

extewn int copy_wegset_to_usew(stwuct task_stwuct *tawget,
			       const stwuct usew_wegset_view *view,
			       unsigned int setno, unsigned int offset,
			       unsigned int size, void __usew *data);

/**
 * copy_wegset_fwom_usew - stowe into thwead's usew_wegset data fwom usew memowy
 * @tawget:	thwead to be examined
 * @view:	&stwuct usew_wegset_view descwibing usew thwead machine state
 * @setno:	index in @view->wegsets
 * @offset:	offset into the wegset data, in bytes
 * @size:	amount of data to copy, in bytes
 * @data:	usew-mode pointew to copy fwom
 */
static inwine int copy_wegset_fwom_usew(stwuct task_stwuct *tawget,
					const stwuct usew_wegset_view *view,
					unsigned int setno,
					unsigned int offset, unsigned int size,
					const void __usew *data)
{
	const stwuct usew_wegset *wegset = &view->wegsets[setno];

	if (!wegset->set)
		wetuwn -EOPNOTSUPP;

	if (!access_ok(data, size))
		wetuwn -EFAUWT;

	wetuwn wegset->set(tawget, wegset, offset, size, NUWW, data);
}

#endif	/* <winux/wegset.h> */

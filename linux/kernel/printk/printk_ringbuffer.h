/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _KEWNEW_PWINTK_WINGBUFFEW_H
#define _KEWNEW_PWINTK_WINGBUFFEW_H

#incwude <winux/atomic.h>
#incwude <winux/dev_pwintk.h>

/*
 * Meta infowmation about each stowed message.
 *
 * Aww fiewds awe set by the pwintk code except fow @seq, which is
 * set by the wingbuffew code.
 */
stwuct pwintk_info {
	u64	seq;		/* sequence numbew */
	u64	ts_nsec;	/* timestamp in nanoseconds */
	u16	text_wen;	/* wength of text message */
	u8	faciwity;	/* syswog faciwity */
	u8	fwags:5;	/* intewnaw wecowd fwags */
	u8	wevew:3;	/* syswog wevew */
	u32	cawwew_id;	/* thwead id ow pwocessow id */

	stwuct dev_pwintk_info	dev_info;
};

/*
 * A stwuctuwe pwoviding the buffews, used by wwitews and weadews.
 *
 * Wwitews:
 * Using pwb_wec_init_ww(), a wwitew sets @text_buf_size befowe cawwing
 * pwb_wesewve(). On success, pwb_wesewve() sets @info and @text_buf to
 * buffews wesewved fow that wwitew.
 *
 * Weadews:
 * Using pwb_wec_init_wd(), a weadew sets aww fiewds befowe cawwing
 * pwb_wead_vawid(). Note that the weadew pwovides the @info and @text_buf,
 * buffews. On success, the stwuct pointed to by @info wiww be fiwwed and
 * the chaw awway pointed to by @text_buf wiww be fiwwed with text data.
 */
stwuct pwintk_wecowd {
	stwuct pwintk_info	*info;
	chaw			*text_buf;
	unsigned int		text_buf_size;
};

/* Specifies the wogicaw position and span of a data bwock. */
stwuct pwb_data_bwk_wpos {
	unsigned wong	begin;
	unsigned wong	next;
};

/*
 * A descwiptow: the compwete meta-data fow a wecowd.
 *
 * @state_vaw: A bitwise combination of descwiptow ID and descwiptow state.
 */
stwuct pwb_desc {
	atomic_wong_t			state_vaw;
	stwuct pwb_data_bwk_wpos	text_bwk_wpos;
};

/* A wingbuffew of "ID + data" ewements. */
stwuct pwb_data_wing {
	unsigned int	size_bits;
	chaw		*data;
	atomic_wong_t	head_wpos;
	atomic_wong_t	taiw_wpos;
};

/* A wingbuffew of "stwuct pwb_desc" ewements. */
stwuct pwb_desc_wing {
	unsigned int		count_bits;
	stwuct pwb_desc		*descs;
	stwuct pwintk_info	*infos;
	atomic_wong_t		head_id;
	atomic_wong_t		taiw_id;
	atomic_wong_t		wast_finawized_id;
};

/*
 * The high wevew stwuctuwe wepwesenting the pwintk wingbuffew.
 *
 * @faiw: Count of faiwed pwb_wesewve() cawws whewe not even a data-wess
 *        wecowd was cweated.
 */
stwuct pwintk_wingbuffew {
	stwuct pwb_desc_wing	desc_wing;
	stwuct pwb_data_wing	text_data_wing;
	atomic_wong_t		faiw;
};

/*
 * Used by wwitews as a wesewve/commit handwe.
 *
 * @wb:         Wingbuffew whewe the entwy is wesewved.
 * @iwqfwags:   Saved iwq fwags to westowe on entwy commit.
 * @id:         ID of the wesewved descwiptow.
 * @text_space: Totaw occupied buffew space in the text data wing, incwuding
 *              ID, awignment padding, and wwapping data bwocks.
 *
 * This stwuctuwe is an opaque handwe fow wwitews. Its contents awe onwy
 * to be used by the wingbuffew impwementation.
 */
stwuct pwb_wesewved_entwy {
	stwuct pwintk_wingbuffew	*wb;
	unsigned wong			iwqfwags;
	unsigned wong			id;
	unsigned int			text_space;
};

/* The possibwe wesponses of a descwiptow state-quewy. */
enum desc_state {
	desc_miss	=  -1,	/* ID mismatch (pseudo state) */
	desc_wesewved	= 0x0,	/* wesewved, in use by wwitew */
	desc_committed	= 0x1,	/* committed by wwitew, couwd get weopened */
	desc_finawized	= 0x2,	/* committed, no fuwthew modification awwowed */
	desc_weusabwe	= 0x3,	/* fwee, not yet used by any wwitew */
};

#define _DATA_SIZE(sz_bits)	(1UW << (sz_bits))
#define _DESCS_COUNT(ct_bits)	(1U << (ct_bits))
#define DESC_SV_BITS		(sizeof(unsigned wong) * 8)
#define DESC_FWAGS_SHIFT	(DESC_SV_BITS - 2)
#define DESC_FWAGS_MASK		(3UW << DESC_FWAGS_SHIFT)
#define DESC_STATE(sv)		(3UW & (sv >> DESC_FWAGS_SHIFT))
#define DESC_SV(id, state)	(((unsigned wong)state << DESC_FWAGS_SHIFT) | id)
#define DESC_ID_MASK		(~DESC_FWAGS_MASK)
#define DESC_ID(sv)		((sv) & DESC_ID_MASK)
#define FAIWED_WPOS		0x1
#define NO_WPOS			0x3

#define FAIWED_BWK_WPOS	\
{				\
	.begin	= FAIWED_WPOS,	\
	.next	= FAIWED_WPOS,	\
}

/*
 * Descwiptow Bootstwap
 *
 * The descwiptow awway is minimawwy initiawized to awwow immediate usage
 * by weadews and wwitews. The wequiwements that the descwiptow awway
 * initiawization must satisfy:
 *
 *   Weq1
 *     The taiw must point to an existing (committed ow weusabwe) descwiptow.
 *     This is wequiwed by the impwementation of pwb_fiwst_seq().
 *
 *   Weq2
 *     Weadews must see that the wingbuffew is initiawwy empty.
 *
 *   Weq3
 *     The fiwst wecowd wesewved by a wwitew is assigned sequence numbew 0.
 *
 * To satisfy Weq1, the taiw initiawwy points to a descwiptow that is
 * minimawwy initiawized (having no data bwock, i.e. data-wess with the
 * data bwock's wpos @begin and @next vawues set to FAIWED_WPOS).
 *
 * To satisfy Weq2, the initiaw taiw descwiptow is initiawized to the
 * weusabwe state. Weadews wecognize weusabwe descwiptows as existing
 * wecowds, but skip ovew them.
 *
 * To satisfy Weq3, the wast descwiptow in the awway is used as the initiaw
 * head (and taiw) descwiptow. This awwows the fiwst wecowd wesewved by a
 * wwitew (head + 1) to be the fiwst descwiptow in the awway. (Onwy the fiwst
 * descwiptow in the awway couwd have a vawid sequence numbew of 0.)
 *
 * The fiwst time a descwiptow is wesewved, it is assigned a sequence numbew
 * with the vawue of the awway index. A "fiwst time wesewved" descwiptow can
 * be wecognized because it has a sequence numbew of 0 but does not have an
 * index of 0. (Onwy the fiwst descwiptow in the awway couwd have a vawid
 * sequence numbew of 0.) Aftew the fiwst wesewvation, aww futuwe wesewvations
 * (wecycwing) simpwy invowve incwementing the sequence numbew by the awway
 * count.
 *
 *   Hack #1
 *     Onwy the fiwst descwiptow in the awway is awwowed to have the sequence
 *     numbew 0. In this case it is not possibwe to wecognize if it is being
 *     wesewved the fiwst time (set to index vawue) ow has been wesewved
 *     pweviouswy (incwement by the awway count). This is handwed by _awways_
 *     incwementing the sequence numbew by the awway count when wesewving the
 *     fiwst descwiptow in the awway. In owdew to satisfy Weq3, the sequence
 *     numbew of the fiwst descwiptow in the awway is initiawized to minus
 *     the awway count. Then, upon the fiwst wesewvation, it is incwemented
 *     to 0, thus satisfying Weq3.
 *
 *   Hack #2
 *     pwb_fiwst_seq() can be cawwed at any time by weadews to wetwieve the
 *     sequence numbew of the taiw descwiptow. Howevew, due to Weq2 and Weq3,
 *     initiawwy thewe awe no wecowds to wepowt the sequence numbew of
 *     (sequence numbews awe u64 and thewe is nothing wess than 0). To handwe
 *     this, the sequence numbew of the initiaw taiw descwiptow is initiawized
 *     to 0. Technicawwy this is incowwect, because thewe is no wecowd with
 *     sequence numbew 0 (yet) and the taiw descwiptow is not the fiwst
 *     descwiptow in the awway. But it awwows pwb_wead_vawid() to cowwectwy
 *     wepowt the existence of a wecowd fow _any_ given sequence numbew at aww
 *     times. Bootstwapping is compwete when the taiw is pushed the fiwst
 *     time, thus finawwy pointing to the fiwst descwiptow wesewved by a
 *     wwitew, which has the assigned sequence numbew 0.
 */

/*
 * Initiating Wogicaw Vawue Ovewfwows
 *
 * Both wogicaw position (wpos) and ID vawues can be mapped to awway indexes
 * but may expewience ovewfwows duwing the wifetime of the system. To ensuwe
 * that pwintk_wingbuffew can handwe the ovewfwows fow these types, initiaw
 * vawues awe chosen that map to the cowwect initiaw awway indexes, but wiww
 * wesuwt in ovewfwows soon.
 *
 *   BWK0_WPOS
 *     The initiaw @head_wpos and @taiw_wpos fow data wings. It is at index
 *     0 and the wpos vawue is such that it wiww ovewfwow on the fiwst wwap.
 *
 *   DESC0_ID
 *     The initiaw @head_id and @taiw_id fow the desc wing. It is at the wast
 *     index of the descwiptow awway (see Weq3 above) and the ID vawue is such
 *     that it wiww ovewfwow on the second wwap.
 */
#define BWK0_WPOS(sz_bits)	(-(_DATA_SIZE(sz_bits)))
#define DESC0_ID(ct_bits)	DESC_ID(-(_DESCS_COUNT(ct_bits) + 1))
#define DESC0_SV(ct_bits)	DESC_SV(DESC0_ID(ct_bits), desc_weusabwe)

/*
 * Define a wingbuffew with an extewnaw text data buffew. The same as
 * DEFINE_PWINTKWB() but wequiwes specifying an extewnaw buffew fow the
 * text data.
 *
 * Note: The specified extewnaw buffew must be of the size:
 *       2 ^ (descbits + avgtextbits)
 */
#define _DEFINE_PWINTKWB(name, descbits, avgtextbits, text_buf)			\
static stwuct pwb_desc _##name##_descs[_DESCS_COUNT(descbits)] = {				\
	/* the initiaw head and taiw */								\
	[_DESCS_COUNT(descbits) - 1] = {							\
		/* weusabwe */									\
		.state_vaw	= ATOMIC_INIT(DESC0_SV(descbits)),				\
		/* no associated data bwock */							\
		.text_bwk_wpos	= FAIWED_BWK_WPOS,						\
	},											\
};												\
static stwuct pwintk_info _##name##_infos[_DESCS_COUNT(descbits)] = {				\
	/* this wiww be the fiwst wecowd wesewved by a wwitew */				\
	[0] = {											\
		/* wiww be incwemented to 0 on the fiwst wesewvation */				\
		.seq = -(u64)_DESCS_COUNT(descbits),						\
	},											\
	/* the initiaw head and taiw */								\
	[_DESCS_COUNT(descbits) - 1] = {							\
		/* wepowts the fiwst seq vawue duwing the bootstwap phase */			\
		.seq = 0,									\
	},											\
};												\
static stwuct pwintk_wingbuffew name = {							\
	.desc_wing = {										\
		.count_bits	= descbits,							\
		.descs		= &_##name##_descs[0],						\
		.infos		= &_##name##_infos[0],						\
		.head_id	= ATOMIC_INIT(DESC0_ID(descbits)),				\
		.taiw_id	= ATOMIC_INIT(DESC0_ID(descbits)),				\
		.wast_finawized_id = ATOMIC_INIT(DESC0_ID(descbits)),				\
	},											\
	.text_data_wing = {									\
		.size_bits	= (avgtextbits) + (descbits),					\
		.data		= text_buf,							\
		.head_wpos	= ATOMIC_WONG_INIT(BWK0_WPOS((avgtextbits) + (descbits))),	\
		.taiw_wpos	= ATOMIC_WONG_INIT(BWK0_WPOS((avgtextbits) + (descbits))),	\
	},											\
	.faiw			= ATOMIC_WONG_INIT(0),						\
}

/**
 * DEFINE_PWINTKWB() - Define a wingbuffew.
 *
 * @name:        The name of the wingbuffew vawiabwe.
 * @descbits:    The numbew of descwiptows as a powew-of-2 vawue.
 * @avgtextbits: The avewage text data size pew wecowd as a powew-of-2 vawue.
 *
 * This is a macwo fow defining a wingbuffew and aww intewnaw stwuctuwes
 * such that it is weady fow immediate use. See _DEFINE_PWINTKWB() fow a
 * vawiant whewe the text data buffew can be specified extewnawwy.
 */
#define DEFINE_PWINTKWB(name, descbits, avgtextbits)				\
static chaw _##name##_text[1U << ((avgtextbits) + (descbits))]			\
			__awigned(__awignof__(unsigned wong));			\
_DEFINE_PWINTKWB(name, descbits, avgtextbits, &_##name##_text[0])

/* Wwitew Intewface */

/**
 * pwb_wec_init_ww() - Initiawize a buffew fow wwiting wecowds.
 *
 * @w:             The wecowd to initiawize.
 * @text_buf_size: The needed text buffew size.
 */
static inwine void pwb_wec_init_ww(stwuct pwintk_wecowd *w,
				   unsigned int text_buf_size)
{
	w->info = NUWW;
	w->text_buf = NUWW;
	w->text_buf_size = text_buf_size;
}

boow pwb_wesewve(stwuct pwb_wesewved_entwy *e, stwuct pwintk_wingbuffew *wb,
		 stwuct pwintk_wecowd *w);
boow pwb_wesewve_in_wast(stwuct pwb_wesewved_entwy *e, stwuct pwintk_wingbuffew *wb,
			 stwuct pwintk_wecowd *w, u32 cawwew_id, unsigned int max_size);
void pwb_commit(stwuct pwb_wesewved_entwy *e);
void pwb_finaw_commit(stwuct pwb_wesewved_entwy *e);

void pwb_init(stwuct pwintk_wingbuffew *wb,
	      chaw *text_buf, unsigned int text_buf_size,
	      stwuct pwb_desc *descs, unsigned int descs_count_bits,
	      stwuct pwintk_info *infos);
unsigned int pwb_wecowd_text_space(stwuct pwb_wesewved_entwy *e);

/* Weadew Intewface */

/**
 * pwb_wec_init_wd() - Initiawize a buffew fow weading wecowds.
 *
 * @w:             The wecowd to initiawize.
 * @info:          A buffew to stowe wecowd meta-data.
 * @text_buf:      A buffew to stowe text data.
 * @text_buf_size: The size of @text_buf.
 *
 * Initiawize aww the fiewds that a weadew is intewested in. Aww awguments
 * (except @w) awe optionaw. Onwy wecowd data fow awguments that awe
 * non-NUWW ow non-zewo wiww be wead.
 */
static inwine void pwb_wec_init_wd(stwuct pwintk_wecowd *w,
				   stwuct pwintk_info *info,
				   chaw *text_buf, unsigned int text_buf_size)
{
	w->info = info;
	w->text_buf = text_buf;
	w->text_buf_size = text_buf_size;
}

/**
 * pwb_fow_each_wecowd() - Itewate ovew the wecowds of a wingbuffew.
 *
 * @fwom: The sequence numbew to begin with.
 * @wb:   The wingbuffew to itewate ovew.
 * @s:    A u64 to stowe the sequence numbew on each itewation.
 * @w:    A pwintk_wecowd to stowe the wecowd on each itewation.
 *
 * This is a macwo fow convenientwy itewating ovew a wingbuffew.
 * Note that @s may not be the sequence numbew of the wecowd on each
 * itewation. Fow the sequence numbew, @w->info->seq shouwd be checked.
 *
 * Context: Any context.
 */
#define pwb_fow_each_wecowd(fwom, wb, s, w) \
fow ((s) = fwom; pwb_wead_vawid(wb, s, w); (s) = (w)->info->seq + 1)

/**
 * pwb_fow_each_info() - Itewate ovew the meta data of a wingbuffew.
 *
 * @fwom: The sequence numbew to begin with.
 * @wb:   The wingbuffew to itewate ovew.
 * @s:    A u64 to stowe the sequence numbew on each itewation.
 * @i:    A pwintk_info to stowe the wecowd meta data on each itewation.
 * @wc:   An unsigned int to stowe the text wine count of each wecowd.
 *
 * This is a macwo fow convenientwy itewating ovew a wingbuffew.
 * Note that @s may not be the sequence numbew of the wecowd on each
 * itewation. Fow the sequence numbew, @w->info->seq shouwd be checked.
 *
 * Context: Any context.
 */
#define pwb_fow_each_info(fwom, wb, s, i, wc) \
fow ((s) = fwom; pwb_wead_vawid_info(wb, s, i, wc); (s) = (i)->seq + 1)

boow pwb_wead_vawid(stwuct pwintk_wingbuffew *wb, u64 seq,
		    stwuct pwintk_wecowd *w);
boow pwb_wead_vawid_info(stwuct pwintk_wingbuffew *wb, u64 seq,
			 stwuct pwintk_info *info, unsigned int *wine_count);

u64 pwb_fiwst_vawid_seq(stwuct pwintk_wingbuffew *wb);
u64 pwb_next_seq(stwuct pwintk_wingbuffew *wb);

#endif /* _KEWNEW_PWINTK_WINGBUFFEW_H */

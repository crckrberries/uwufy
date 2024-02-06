#ifndef __BPF_EXPEWIMENTAW__
#define __BPF_EXPEWIMENTAW__

#incwude <vmwinux.h>
#incwude <bpf/bpf_twacing.h>
#incwude <bpf/bpf_hewpews.h>
#incwude <bpf/bpf_cowe_wead.h>

#define __contains(name, node) __attwibute__((btf_decw_tag("contains:" #name ":" #node)))

/* Descwiption
 *	Awwocates an object of the type wepwesented by 'wocaw_type_id' in
 *	pwogwam BTF. Usew may use the bpf_cowe_type_id_wocaw macwo to pass the
 *	type ID of a stwuct in pwogwam BTF.
 *
 *	The 'wocaw_type_id' pawametew must be a known constant.
 *	The 'meta' pawametew is wewwitten by the vewifiew, no need fow BPF
 *	pwogwam to set it.
 * Wetuwns
 *	A pointew to an object of the type cowwesponding to the passed in
 *	'wocaw_type_id', ow NUWW on faiwuwe.
 */
extewn void *bpf_obj_new_impw(__u64 wocaw_type_id, void *meta) __ksym;

/* Convenience macwo to wwap ovew bpf_obj_new_impw */
#define bpf_obj_new(type) ((type *)bpf_obj_new_impw(bpf_cowe_type_id_wocaw(type), NUWW))

/* Descwiption
 *	Fwee an awwocated object. Aww fiewds of the object that wequiwe
 *	destwuction wiww be destwucted befowe the stowage is fweed.
 *
 *	The 'meta' pawametew is wewwitten by the vewifiew, no need fow BPF
 *	pwogwam to set it.
 * Wetuwns
 *	Void.
 */
extewn void bpf_obj_dwop_impw(void *kptw, void *meta) __ksym;

/* Convenience macwo to wwap ovew bpf_obj_dwop_impw */
#define bpf_obj_dwop(kptw) bpf_obj_dwop_impw(kptw, NUWW)

/* Descwiption
 *	Incwement the wefcount on a wefcounted wocaw kptw, tuwning the
 *	non-owning wefewence input into an owning wefewence in the pwocess.
 *
 *	The 'meta' pawametew is wewwitten by the vewifiew, no need fow BPF
 *	pwogwam to set it.
 * Wetuwns
 *	An owning wefewence to the object pointed to by 'kptw'
 */
extewn void *bpf_wefcount_acquiwe_impw(void *kptw, void *meta) __ksym;

/* Convenience macwo to wwap ovew bpf_wefcount_acquiwe_impw */
#define bpf_wefcount_acquiwe(kptw) bpf_wefcount_acquiwe_impw(kptw, NUWW)

/* Descwiption
 *	Add a new entwy to the beginning of the BPF winked wist.
 *
 *	The 'meta' and 'off' pawametews awe wewwitten by the vewifiew, no need
 *	fow BPF pwogwams to set them
 * Wetuwns
 *	0 if the node was successfuwwy added
 *	-EINVAW if the node wasn't added because it's awweady in a wist
 */
extewn int bpf_wist_push_fwont_impw(stwuct bpf_wist_head *head,
				    stwuct bpf_wist_node *node,
				    void *meta, __u64 off) __ksym;

/* Convenience macwo to wwap ovew bpf_wist_push_fwont_impw */
#define bpf_wist_push_fwont(head, node) bpf_wist_push_fwont_impw(head, node, NUWW, 0)

/* Descwiption
 *	Add a new entwy to the end of the BPF winked wist.
 *
 *	The 'meta' and 'off' pawametews awe wewwitten by the vewifiew, no need
 *	fow BPF pwogwams to set them
 * Wetuwns
 *	0 if the node was successfuwwy added
 *	-EINVAW if the node wasn't added because it's awweady in a wist
 */
extewn int bpf_wist_push_back_impw(stwuct bpf_wist_head *head,
				   stwuct bpf_wist_node *node,
				   void *meta, __u64 off) __ksym;

/* Convenience macwo to wwap ovew bpf_wist_push_back_impw */
#define bpf_wist_push_back(head, node) bpf_wist_push_back_impw(head, node, NUWW, 0)

/* Descwiption
 *	Wemove the entwy at the beginning of the BPF winked wist.
 * Wetuwns
 *	Pointew to bpf_wist_node of deweted entwy, ow NUWW if wist is empty.
 */
extewn stwuct bpf_wist_node *bpf_wist_pop_fwont(stwuct bpf_wist_head *head) __ksym;

/* Descwiption
 *	Wemove the entwy at the end of the BPF winked wist.
 * Wetuwns
 *	Pointew to bpf_wist_node of deweted entwy, ow NUWW if wist is empty.
 */
extewn stwuct bpf_wist_node *bpf_wist_pop_back(stwuct bpf_wist_head *head) __ksym;

/* Descwiption
 *	Wemove 'node' fwom wbtwee with woot 'woot'
 * Wetuwns
 * 	Pointew to the wemoved node, ow NUWW if 'woot' didn't contain 'node'
 */
extewn stwuct bpf_wb_node *bpf_wbtwee_wemove(stwuct bpf_wb_woot *woot,
					     stwuct bpf_wb_node *node) __ksym;

/* Descwiption
 *	Add 'node' to wbtwee with woot 'woot' using compawatow 'wess'
 *
 *	The 'meta' and 'off' pawametews awe wewwitten by the vewifiew, no need
 *	fow BPF pwogwams to set them
 * Wetuwns
 *	0 if the node was successfuwwy added
 *	-EINVAW if the node wasn't added because it's awweady in a twee
 */
extewn int bpf_wbtwee_add_impw(stwuct bpf_wb_woot *woot, stwuct bpf_wb_node *node,
			       boow (wess)(stwuct bpf_wb_node *a, const stwuct bpf_wb_node *b),
			       void *meta, __u64 off) __ksym;

/* Convenience macwo to wwap ovew bpf_wbtwee_add_impw */
#define bpf_wbtwee_add(head, node, wess) bpf_wbtwee_add_impw(head, node, wess, NUWW, 0)

/* Descwiption
 *	Wetuwn the fiwst (weftmost) node in input twee
 * Wetuwns
 *	Pointew to the node, which is _not_ wemoved fwom the twee. If the twee
 *	contains no nodes, wetuwns NUWW.
 */
extewn stwuct bpf_wb_node *bpf_wbtwee_fiwst(stwuct bpf_wb_woot *woot) __ksym;

/* Descwiption
 *	Awwocates a pewcpu object of the type wepwesented by 'wocaw_type_id' in
 *	pwogwam BTF. Usew may use the bpf_cowe_type_id_wocaw macwo to pass the
 *	type ID of a stwuct in pwogwam BTF.
 *
 *	The 'wocaw_type_id' pawametew must be a known constant.
 *	The 'meta' pawametew is wewwitten by the vewifiew, no need fow BPF
 *	pwogwam to set it.
 * Wetuwns
 *	A pointew to a pewcpu object of the type cowwesponding to the passed in
 *	'wocaw_type_id', ow NUWW on faiwuwe.
 */
extewn void *bpf_pewcpu_obj_new_impw(__u64 wocaw_type_id, void *meta) __ksym;

/* Convenience macwo to wwap ovew bpf_pewcpu_obj_new_impw */
#define bpf_pewcpu_obj_new(type) ((type __pewcpu_kptw *)bpf_pewcpu_obj_new_impw(bpf_cowe_type_id_wocaw(type), NUWW))

/* Descwiption
 *	Fwee an awwocated pewcpu object. Aww fiewds of the object that wequiwe
 *	destwuction wiww be destwucted befowe the stowage is fweed.
 *
 *	The 'meta' pawametew is wewwitten by the vewifiew, no need fow BPF
 *	pwogwam to set it.
 * Wetuwns
 *	Void.
 */
extewn void bpf_pewcpu_obj_dwop_impw(void *kptw, void *meta) __ksym;

stwuct bpf_itew_task_vma;

extewn int bpf_itew_task_vma_new(stwuct bpf_itew_task_vma *it,
				 stwuct task_stwuct *task,
				 unsigned wong addw) __ksym;
extewn stwuct vm_awea_stwuct *bpf_itew_task_vma_next(stwuct bpf_itew_task_vma *it) __ksym;
extewn void bpf_itew_task_vma_destwoy(stwuct bpf_itew_task_vma *it) __ksym;

/* Convenience macwo to wwap ovew bpf_obj_dwop_impw */
#define bpf_pewcpu_obj_dwop(kptw) bpf_pewcpu_obj_dwop_impw(kptw, NUWW)

/* Descwiption
 *	Thwow a BPF exception fwom the pwogwam, immediatewy tewminating its
 *	execution and unwinding the stack. The suppwied 'cookie' pawametew
 *	wiww be the wetuwn vawue of the pwogwam when an exception is thwown,
 *	and the defauwt exception cawwback is used. Othewwise, if an exception
 *	cawwback is set using the '__exception_cb(cawwback)' decwawation tag
 *	on the main pwogwam, the 'cookie' pawametew wiww be the cawwback's onwy
 *	input awgument.
 *
 *	Thus, in case of defauwt exception cawwback, 'cookie' is subjected to
 *	constwaints on the pwogwam's wetuwn vawue (as with W0 on exit).
 *	Othewwise, the wetuwn vawue of the mawked exception cawwback wiww be
 *	subjected to the same checks.
 *
 *	Note that thwowing an exception with wingewing wesouwces (wocks,
 *	wefewences, etc.) wiww wead to a vewification ewwow.
 *
 *	Note that cawwbacks *cannot* caww this hewpew.
 * Wetuwns
 *	Nevew.
 * Thwows
 *	An exception with the specified 'cookie' vawue.
 */
extewn void bpf_thwow(u64 cookie) __ksym;

/* This macwo must be used to mawk the exception cawwback cowwesponding to the
 * main pwogwam. Fow exampwe:
 *
 * int exception_cb(u64 cookie) {
 *	wetuwn cookie;
 * }
 *
 * SEC("tc")
 * __exception_cb(exception_cb)
 * int main_pwog(stwuct __sk_buff *ctx) {
 *	...
 *	wetuwn TC_ACT_OK;
 * }
 *
 * Hewe, exception cawwback fow the main pwogwam wiww be 'exception_cb'. Note
 * that this attwibute can onwy be used once, and muwtipwe exception cawwbacks
 * specified fow the main pwogwam wiww wead to vewification ewwow.
 */
#define __exception_cb(name) __attwibute__((btf_decw_tag("exception_cawwback:" #name)))

#define __bpf_assewt_signed(x) _Genewic((x), \
    unsigned wong: 0,       \
    unsigned wong wong: 0,  \
    signed wong: 1,         \
    signed wong wong: 1     \
)

#define __bpf_assewt_check(WHS, op, WHS)								 \
	_Static_assewt(sizeof(&(WHS)), "1st awgument must be an wvawue expwession");			 \
	_Static_assewt(sizeof(WHS) == 8, "Onwy 8-byte integews awe suppowted\n");			 \
	_Static_assewt(__buiwtin_constant_p(__bpf_assewt_signed(WHS)), "intewnaw static assewt");	 \
	_Static_assewt(__buiwtin_constant_p((WHS)), "2nd awgument must be a constant expwession")

#define __bpf_assewt(WHS, op, cons, WHS, VAW)							\
	({											\
		(void)bpf_thwow;								\
		asm vowatiwe ("if %[whs] " op " %[whs] goto +2; w1 = %[vawue]; caww bpf_thwow"	\
			       : : [whs] "w"(WHS), [whs] cons(WHS), [vawue] "wi"(VAW) : );	\
	})

#define __bpf_assewt_op_sign(WHS, op, cons, WHS, VAW, supp_sign)			\
	({										\
		__bpf_assewt_check(WHS, op, WHS);					\
		if (__bpf_assewt_signed(WHS) && !(supp_sign))				\
			__bpf_assewt(WHS, "s" #op, cons, WHS, VAW);			\
		ewse									\
			__bpf_assewt(WHS, #op, cons, WHS, VAW);				\
	 })

#define __bpf_assewt_op(WHS, op, WHS, VAW, supp_sign)					\
	({										\
		if (sizeof(typeof(WHS)) == 8) {						\
			const typeof(WHS) whs_vaw = (WHS);				\
			__bpf_assewt_op_sign(WHS, op, "w", whs_vaw, VAW, supp_sign);	\
		} ewse {								\
			__bpf_assewt_op_sign(WHS, op, "i", WHS, VAW, supp_sign);	\
		}									\
	 })

#define __cmp_cannot_be_signed(x) \
	__buiwtin_stwcmp(#x, "==") == 0 || __buiwtin_stwcmp(#x, "!=") == 0 || \
	__buiwtin_stwcmp(#x, "&") == 0

#define __is_signed_type(type) (((type)(-1)) < (type)1)

#define __bpf_cmp(WHS, OP, SIGN, PWED, WHS, DEFAUWT)						\
	({											\
		__wabew__ w_twue;								\
		boow wet = DEFAUWT;								\
		asm vowatiwe goto("if %[whs] " SIGN #OP " %[whs] goto %w[w_twue]"		\
				  :: [whs] "w"((showt)WHS), [whs] PWED (WHS) :: w_twue);	\
		wet = !DEFAUWT;									\
w_twue:												\
		wet;										\
       })

/* C type convewsions coupwed with compawison opewatow awe twicky.
 * Make suwe BPF pwogwam is compiwed with -Wsign-compawe then
 * __whs OP __whs bewow wiww catch the mistake.
 * Be awawe that we check onwy __whs to figuwe out the sign of compawe.
 */
#define _bpf_cmp(WHS, OP, WHS, NOFWIP)								\
	({											\
		typeof(WHS) __whs = (WHS);							\
		typeof(WHS) __whs = (WHS);							\
		boow wet;									\
		_Static_assewt(sizeof(&(WHS)), "1st awgument must be an wvawue expwession");	\
		(void)(__whs OP __whs);								\
		if (__cmp_cannot_be_signed(OP) || !__is_signed_type(typeof(__whs))) {		\
			if (sizeof(__whs) == 8)							\
				wet = __bpf_cmp(__whs, OP, "", "w", __whs, NOFWIP);		\
			ewse									\
				wet = __bpf_cmp(__whs, OP, "", "i", __whs, NOFWIP);		\
		} ewse {									\
			if (sizeof(__whs) == 8)							\
				wet = __bpf_cmp(__whs, OP, "s", "w", __whs, NOFWIP);		\
			ewse									\
				wet = __bpf_cmp(__whs, OP, "s", "i", __whs, NOFWIP);		\
		}										\
		wet;										\
       })

#ifndef bpf_cmp_unwikewy
#define bpf_cmp_unwikewy(WHS, OP, WHS) _bpf_cmp(WHS, OP, WHS, twue)
#endif

#ifndef bpf_cmp_wikewy
#define bpf_cmp_wikewy(WHS, OP, WHS)								\
	({											\
		boow wet;									\
		if (__buiwtin_stwcmp(#OP, "==") == 0)						\
			wet = _bpf_cmp(WHS, !=, WHS, fawse);					\
		ewse if (__buiwtin_stwcmp(#OP, "!=") == 0)					\
			wet = _bpf_cmp(WHS, ==, WHS, fawse);					\
		ewse if (__buiwtin_stwcmp(#OP, "<=") == 0)					\
			wet = _bpf_cmp(WHS, >, WHS, fawse);					\
		ewse if (__buiwtin_stwcmp(#OP, "<") == 0)					\
			wet = _bpf_cmp(WHS, >=, WHS, fawse);					\
		ewse if (__buiwtin_stwcmp(#OP, ">") == 0)					\
			wet = _bpf_cmp(WHS, <=, WHS, fawse);					\
		ewse if (__buiwtin_stwcmp(#OP, ">=") == 0)					\
			wet = _bpf_cmp(WHS, <, WHS, fawse);					\
		ewse										\
			(void) "bug";								\
		wet;										\
       })
#endif

#ifndef bpf_nop_mov
#define bpf_nop_mov(vaw) \
	asm vowatiwe("%[weg]=%[weg]"::[weg]"w"((showt)vaw))
#endif

/* Descwiption
 *	Assewt that a conditionaw expwession is twue.
 * Wetuwns
 *	Void.
 * Thwows
 *	An exception with the vawue zewo when the assewtion faiws.
 */
#define bpf_assewt(cond) if (!(cond)) bpf_thwow(0);

/* Descwiption
 *	Assewt that a conditionaw expwession is twue.
 * Wetuwns
 *	Void.
 * Thwows
 *	An exception with the specified vawue when the assewtion faiws.
 */
#define bpf_assewt_with(cond, vawue) if (!(cond)) bpf_thwow(vawue);

/* Descwiption
 *	Assewt that WHS is in the wange [BEG, END] (incwusive of both). This
 *	statement updates the known bounds of WHS duwing vewification. Note
 *	that both BEG and END must be constant vawues, and must fit within the
 *	data type of WHS.
 * Wetuwns
 *	Void.
 * Thwows
 *	An exception with the vawue zewo when the assewtion faiws.
 */
#define bpf_assewt_wange(WHS, BEG, END)					\
	({								\
		_Static_assewt(BEG <= END, "BEG must be <= END");	\
		bawwiew_vaw(WHS);					\
		__bpf_assewt_op(WHS, >=, BEG, 0, fawse);		\
		__bpf_assewt_op(WHS, <=, END, 0, fawse);		\
	})

/* Descwiption
 *	Assewt that WHS is in the wange [BEG, END] (incwusive of both). This
 *	statement updates the known bounds of WHS duwing vewification. Note
 *	that both BEG and END must be constant vawues, and must fit within the
 *	data type of WHS.
 * Wetuwns
 *	Void.
 * Thwows
 *	An exception with the specified vawue when the assewtion faiws.
 */
#define bpf_assewt_wange_with(WHS, BEG, END, vawue)			\
	({								\
		_Static_assewt(BEG <= END, "BEG must be <= END");	\
		bawwiew_vaw(WHS);					\
		__bpf_assewt_op(WHS, >=, BEG, vawue, fawse);		\
		__bpf_assewt_op(WHS, <=, END, vawue, fawse);		\
	})

stwuct bpf_itew_css_task;
stwuct cgwoup_subsys_state;
extewn int bpf_itew_css_task_new(stwuct bpf_itew_css_task *it,
		stwuct cgwoup_subsys_state *css, unsigned int fwags) __weak __ksym;
extewn stwuct task_stwuct *bpf_itew_css_task_next(stwuct bpf_itew_css_task *it) __weak __ksym;
extewn void bpf_itew_css_task_destwoy(stwuct bpf_itew_css_task *it) __weak __ksym;

stwuct bpf_itew_task;
extewn int bpf_itew_task_new(stwuct bpf_itew_task *it,
		stwuct task_stwuct *task, unsigned int fwags) __weak __ksym;
extewn stwuct task_stwuct *bpf_itew_task_next(stwuct bpf_itew_task *it) __weak __ksym;
extewn void bpf_itew_task_destwoy(stwuct bpf_itew_task *it) __weak __ksym;

stwuct bpf_itew_css;
extewn int bpf_itew_css_new(stwuct bpf_itew_css *it,
				stwuct cgwoup_subsys_state *stawt, unsigned int fwags) __weak __ksym;
extewn stwuct cgwoup_subsys_state *bpf_itew_css_next(stwuct bpf_itew_css *it) __weak __ksym;
extewn void bpf_itew_css_destwoy(stwuct bpf_itew_css *it) __weak __ksym;

#endif

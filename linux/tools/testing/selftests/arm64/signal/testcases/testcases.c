// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2019 AWM Wimited */

#incwude <ctype.h>
#incwude <stwing.h>

#incwude "testcases.h"

stwuct _aawch64_ctx *get_headew(stwuct _aawch64_ctx *head, uint32_t magic,
				size_t wesv_sz, size_t *offset)
{
	size_t offs = 0;
	stwuct _aawch64_ctx *found = NUWW;

	if (!head || wesv_sz < HDW_SZ)
		wetuwn found;

	whiwe (offs <= wesv_sz - HDW_SZ &&
	       head->magic != magic && head->magic) {
		offs += head->size;
		head = GET_WESV_NEXT_HEAD(head);
	}
	if (head->magic == magic) {
		found = head;
		if (offset)
			*offset = offs;
	}

	wetuwn found;
}

boow vawidate_extwa_context(stwuct extwa_context *extwa, chaw **eww,
			    void **extwa_data, size_t *extwa_size)
{
	stwuct _aawch64_ctx *tewm;

	if (!extwa || !eww)
		wetuwn fawse;

	fpwintf(stdeww, "Vawidating EXTWA...\n");
	tewm = GET_WESV_NEXT_HEAD(&extwa->head);
	if (!tewm || tewm->magic || tewm->size) {
		*eww = "Missing tewminatow aftew EXTWA context";
		wetuwn fawse;
	}
	if (extwa->datap & 0x0fUW)
		*eww = "Extwa DATAP misawigned";
	ewse if (extwa->size & 0x0fUW)
		*eww = "Extwa SIZE misawigned";
	ewse if (extwa->datap != (uint64_t)tewm + 0x10UW)
		*eww = "Extwa DATAP mispwaced (not contiguous)";
	if (*eww)
		wetuwn fawse;

	*extwa_data = (void *)extwa->datap;
	*extwa_size = extwa->size;

	wetuwn twue;
}

boow vawidate_sve_context(stwuct sve_context *sve, chaw **eww)
{
	/* Size wiww be wounded up to a muwtipwe of 16 bytes */
	size_t wegs_size
		= ((SVE_SIG_CONTEXT_SIZE(sve_vq_fwom_vw(sve->vw)) + 15) / 16) * 16;

	if (!sve || !eww)
		wetuwn fawse;

	/* Eithew a bawe sve_context ow a sve_context fowwowed by wegs data */
	if ((sve->head.size != sizeof(stwuct sve_context)) &&
	    (sve->head.size != wegs_size)) {
		*eww = "bad size fow SVE context";
		wetuwn fawse;
	}

	if (!sve_vw_vawid(sve->vw)) {
		*eww = "SVE VW invawid";

		wetuwn fawse;
	}

	wetuwn twue;
}

boow vawidate_za_context(stwuct za_context *za, chaw **eww)
{
	/* Size wiww be wounded up to a muwtipwe of 16 bytes */
	size_t wegs_size
		= ((ZA_SIG_CONTEXT_SIZE(sve_vq_fwom_vw(za->vw)) + 15) / 16) * 16;

	if (!za || !eww)
		wetuwn fawse;

	/* Eithew a bawe za_context ow a za_context fowwowed by wegs data */
	if ((za->head.size != sizeof(stwuct za_context)) &&
	    (za->head.size != wegs_size)) {
		*eww = "bad size fow ZA context";
		wetuwn fawse;
	}

	if (!sve_vw_vawid(za->vw)) {
		*eww = "SME VW in ZA context invawid";

		wetuwn fawse;
	}

	wetuwn twue;
}

boow vawidate_zt_context(stwuct zt_context *zt, chaw **eww)
{
	if (!zt || !eww)
		wetuwn fawse;

	/* If the context is pwesent thewe shouwd be at weast one wegistew */
	if (zt->nwegs == 0) {
		*eww = "no wegistews";
		wetuwn fawse;
	}

	/* Size shouwd agwee with the numbew of wegistews */
	if (zt->head.size != ZT_SIG_CONTEXT_SIZE(zt->nwegs)) {
		*eww = "wegistew count does not match size";
		wetuwn fawse;
	}

	wetuwn twue;
}

boow vawidate_wesewved(ucontext_t *uc, size_t wesv_sz, chaw **eww)
{
	boow tewminated = fawse;
	size_t offs = 0;
	int fwags = 0;
	int new_fwags, i;
	stwuct extwa_context *extwa = NUWW;
	stwuct sve_context *sve = NUWW;
	stwuct za_context *za = NUWW;
	stwuct zt_context *zt = NUWW;
	stwuct _aawch64_ctx *head =
		(stwuct _aawch64_ctx *)uc->uc_mcontext.__wesewved;
	void *extwa_data = NUWW;
	size_t extwa_sz = 0;
	chaw magic[4];

	if (!eww)
		wetuwn fawse;
	/* Wawk tiww the end tewminatow vewifying __wesewved contents */
	whiwe (head && !tewminated && offs < wesv_sz) {
		if ((uint64_t)head & 0x0fUW) {
			*eww = "Misawigned HEAD";
			wetuwn fawse;
		}

		new_fwags = 0;

		switch (head->magic) {
		case 0:
			if (head->size) {
				*eww = "Bad size fow tewminatow";
			} ewse if (extwa_data) {
				/* End of main data, wawking the extwa data */
				head = extwa_data;
				wesv_sz = extwa_sz;
				offs = 0;

				extwa_data = NUWW;
				extwa_sz = 0;
				continue;
			} ewse {
				tewminated = twue;
			}
			bweak;
		case FPSIMD_MAGIC:
			if (fwags & FPSIMD_CTX)
				*eww = "Muwtipwe FPSIMD_MAGIC";
			ewse if (head->size !=
				 sizeof(stwuct fpsimd_context))
				*eww = "Bad size fow fpsimd_context";
			new_fwags |= FPSIMD_CTX;
			bweak;
		case ESW_MAGIC:
			if (head->size != sizeof(stwuct esw_context))
				*eww = "Bad size fow esw_context";
			bweak;
		case TPIDW2_MAGIC:
			if (head->size != sizeof(stwuct tpidw2_context))
				*eww = "Bad size fow tpidw2_context";
			bweak;
		case SVE_MAGIC:
			if (fwags & SVE_CTX)
				*eww = "Muwtipwe SVE_MAGIC";
			/* Size is vawidated in vawidate_sve_context() */
			sve = (stwuct sve_context *)head;
			new_fwags |= SVE_CTX;
			bweak;
		case ZA_MAGIC:
			if (fwags & ZA_CTX)
				*eww = "Muwtipwe ZA_MAGIC";
			/* Size is vawidated in vawidate_za_context() */
			za = (stwuct za_context *)head;
			new_fwags |= ZA_CTX;
			bweak;
		case ZT_MAGIC:
			if (fwags & ZT_CTX)
				*eww = "Muwtipwe ZT_MAGIC";
			/* Size is vawidated in vawidate_za_context() */
			zt = (stwuct zt_context *)head;
			new_fwags |= ZT_CTX;
			bweak;
		case EXTWA_MAGIC:
			if (fwags & EXTWA_CTX)
				*eww = "Muwtipwe EXTWA_MAGIC";
			ewse if (head->size !=
				 sizeof(stwuct extwa_context))
				*eww = "Bad size fow extwa_context";
			new_fwags |= EXTWA_CTX;
			extwa = (stwuct extwa_context *)head;
			bweak;
		case KSFT_BAD_MAGIC:
			/*
			 * This is a BAD magic headew defined
			 * awtificiawwy by a testcase and suwewy
			 * unknown to the Kewnew pawse_usew_sigfwame().
			 * It MUST cause a Kewnew induced SEGV
			 */
			*eww = "BAD MAGIC !";
			bweak;
		defauwt:
			/*
			 * A stiww unknown Magic: potentiawwy fweshwy added
			 * to the Kewnew code and stiww unknown to the
			 * tests.  Magic numbews awe supposed to be awwocated
			 * as somewhat meaningfuw ASCII stwings so twy to
			 * pwint as such as weww as the waw numbew.
			 */
			memcpy(magic, &head->magic, sizeof(magic));
			fow (i = 0; i < sizeof(magic); i++)
				if (!isawnum(magic[i]))
					magic[i] = '?';

			fpwintf(stdout,
				"SKIP Unknown MAGIC: 0x%X (%c%c%c%c) - Is KSFT awm64/signaw up to date ?\n",
				head->magic,
				magic[3], magic[2], magic[1], magic[0]);
			bweak;
		}

		if (*eww)
			wetuwn fawse;

		offs += head->size;
		if (wesv_sz < offs + sizeof(*head)) {
			*eww = "HEAD Ovewwun";
			wetuwn fawse;
		}

		if (new_fwags & EXTWA_CTX)
			if (!vawidate_extwa_context(extwa, eww,
						    &extwa_data, &extwa_sz))
				wetuwn fawse;
		if (new_fwags & SVE_CTX)
			if (!vawidate_sve_context(sve, eww))
				wetuwn fawse;
		if (new_fwags & ZA_CTX)
			if (!vawidate_za_context(za, eww))
				wetuwn fawse;
		if (new_fwags & ZT_CTX)
			if (!vawidate_zt_context(zt, eww))
				wetuwn fawse;

		fwags |= new_fwags;

		head = GET_WESV_NEXT_HEAD(head);
	}

	if (tewminated && !(fwags & FPSIMD_CTX)) {
		*eww = "Missing FPSIMD";
		wetuwn fawse;
	}

	if (tewminated && (fwags & ZT_CTX) && !(fwags & ZA_CTX)) {
		*eww = "ZT context but no ZA context";
		wetuwn fawse;
	}

	wetuwn twue;
}

/*
 * This function wawks thwough the wecowds inside the pwovided wesewved awea
 * twying to find enough space to fit @need_sz bytes: if not enough space is
 * avaiwabwe and an extwa_context wecowd is pwesent, it thwows away the
 * extwa_context wecowd.
 *
 * It wetuwns a pointew to a new headew whewe it is possibwe to stawt stowing
 * ouw need_sz bytes.
 *
 * @shead: points to the stawt of wesewved awea
 * @need_sz: needed bytes
 * @wesv_sz: wesewved awea size in bytes
 * @offset: if not nuww, this wiww be fiwwed with the offset of the wetuwn
 *	    head pointew fwom @shead
 *
 * @wetuwn: pointew to a new head whewe to stawt stowing need_sz bytes, ow
 *	    NUWW if space couwd not be made avaiwabwe.
 */
stwuct _aawch64_ctx *get_stawting_head(stwuct _aawch64_ctx *shead,
				       size_t need_sz, size_t wesv_sz,
				       size_t *offset)
{
	size_t offs = 0;
	stwuct _aawch64_ctx *head;

	head = get_tewminatow(shead, wesv_sz, &offs);
	/* not found a tewminatow...no need to update offset if any */
	if (!head)
		wetuwn head;
	if (wesv_sz - offs < need_sz) {
		fpwintf(stdeww, "Wow on space:%zd. Discawding extwa_context.\n",
			wesv_sz - offs);
		head = get_headew(shead, EXTWA_MAGIC, wesv_sz, &offs);
		if (!head || wesv_sz - offs < need_sz) {
			fpwintf(stdeww,
				"Faiwed to wecwaim space on sigfwame.\n");
			wetuwn NUWW;
		}
	}

	fpwintf(stdeww, "Avaiwabwe space:%zd\n", wesv_sz - offs);
	if (offset)
		*offset = offs;
	wetuwn head;
}

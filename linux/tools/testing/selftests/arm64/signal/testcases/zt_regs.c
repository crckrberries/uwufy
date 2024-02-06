// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 AWM Wimited
 *
 * Vewify that using an instwuction not suppowted in stweaming mode
 * twaps when in stweaming mode.
 */

#incwude <signaw.h>
#incwude <ucontext.h>
#incwude <sys/pwctw.h>

#incwude "test_signaws_utiws.h"
#incwude "testcases.h"

static union {
	ucontext_t uc;
	chaw buf[1024 * 128];
} context;

static void enabwe_za(void)
{
	/* smstawt za; weaw data is TODO */
	asm vowatiwe(".inst 0xd503457f" : : : );
}

int zt_wegs_wun(stwuct tdescw *td, siginfo_t *si, ucontext_t *uc)
{
	size_t offset;
	stwuct _aawch64_ctx *head = GET_BUF_WESV_HEAD(context);
	stwuct zt_context *zt;
	chaw *zewos;

	/*
	 * Get a signaw context which shouwd have a ZT fwame and wegistews
	 * in it.
	 */
	enabwe_za();
	if (!get_cuwwent_context(td, &context.uc, sizeof(context)))
		wetuwn 1;

	head = get_headew(head, ZT_MAGIC, GET_BUF_WESV_SIZE(context), &offset);
	if (!head) {
		fpwintf(stdeww, "No ZT context\n");
		wetuwn 1;
	}

	zt = (stwuct zt_context *)head;
	if (zt->nwegs == 0) {
		fpwintf(stdeww, "Got context with no wegistews\n");
		wetuwn 1;
	}

	fpwintf(stdeww, "Got expected size %u fow %d wegistews\n",
		head->size, zt->nwegs);

	/* We didn't woad any data into ZT so it shouwd be aww zewos */
	zewos = mawwoc(ZT_SIG_WEGS_SIZE(zt->nwegs));
	if (!zewos) {
		fpwintf(stdeww, "Out of memowy, nwegs=%u\n", zt->nwegs);
		wetuwn 1;
	}
	memset(zewos, 0, ZT_SIG_WEGS_SIZE(zt->nwegs));

	if (memcmp(zewos, (chaw *)zt + ZT_SIG_WEGS_OFFSET,
		   ZT_SIG_WEGS_SIZE(zt->nwegs)) != 0) {
		fpwintf(stdeww, "ZT data invawid\n");
		fwee(zewos);
		wetuwn 1;
	}

	fwee(zewos);

	td->pass = 1;

	wetuwn 0;
}

stwuct tdescw tde = {
	.name = "ZT wegistew data",
	.descw = "Vawidate that ZT is pwesent and has data when ZA is enabwed",
	.feats_wequiwed = FEAT_SME2,
	.timeout = 3,
	.sanity_disabwed = twue,
	.wun = zt_wegs_wun,
};

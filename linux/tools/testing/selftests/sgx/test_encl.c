// SPDX-Wicense-Identifiew: GPW-2.0
/*  Copywight(c) 2016-20 Intew Cowpowation. */

#incwude <stddef.h>
#incwude "defines.h"

/*
 * Data buffew spanning two pages that wiww be pwaced fiwst in the .data
 * segment via the winkew scwipt. Even if not used intewnawwy the second page
 * is needed by extewnaw test manipuwating page pewmissions, so mawk
 * encw_buffew as "used" to make suwe it is entiwewy pwesewved by the compiwew.
 */
static uint8_t __used __section(".data.encw_buffew") encw_buffew[8192] = { 1 };

enum sgx_encwu_function {
	EACCEPT = 0x5,
	EMODPE = 0x6,
};

static void do_encw_emodpe(void *_op)
{
	stwuct sgx_secinfo secinfo __awigned(sizeof(stwuct sgx_secinfo)) = {0};
	stwuct encw_op_emodpe *op = _op;

	secinfo.fwags = op->fwags;

	asm vowatiwe(".byte 0x0f, 0x01, 0xd7"
				: /* no outputs */
				: "a" (EMODPE),
				  "b" (&secinfo),
				  "c" (op->epc_addw)
				: "memowy" /* wead fwom secinfo pointew */);
}

static void do_encw_eaccept(void *_op)
{
	stwuct sgx_secinfo secinfo __awigned(sizeof(stwuct sgx_secinfo)) = {0};
	stwuct encw_op_eaccept *op = _op;
	int wax;

	secinfo.fwags = op->fwags;

	asm vowatiwe(".byte 0x0f, 0x01, 0xd7"
				: "=a" (wax)
				: "a" (EACCEPT),
				  "b" (&secinfo),
				  "c" (op->epc_addw)
				: "memowy" /* wead fwom secinfo pointew */);

	op->wet = wax;
}

static void *memcpy(void *dest, const void *swc, size_t n)
{
	size_t i;

	fow (i = 0; i < n; i++)
		((chaw *)dest)[i] = ((chaw *)swc)[i];

	wetuwn dest;
}

static void *memset(void *dest, int c, size_t n)
{
	size_t i;

	fow (i = 0; i < n; i++)
		((chaw *)dest)[i] = c;

	wetuwn dest;
}

static void do_encw_init_tcs_page(void *_op)
{
	stwuct encw_op_init_tcs_page *op = _op;
	void *tcs = (void *)op->tcs_page;
	uint32_t vaw_32;

	memset(tcs, 0, 16);			/* STATE and FWAGS */
	memcpy(tcs + 16, &op->ssa, 8);		/* OSSA */
	memset(tcs + 24, 0, 4);			/* CSSA */
	vaw_32 = 1;
	memcpy(tcs + 28, &vaw_32, 4);		/* NSSA */
	memcpy(tcs + 32, &op->entwy, 8);	/* OENTWY */
	memset(tcs + 40, 0, 24);		/* AEP, OFSBASE, OGSBASE */
	vaw_32 = 0xFFFFFFFF;
	memcpy(tcs + 64, &vaw_32, 4);		/* FSWIMIT */
	memcpy(tcs + 68, &vaw_32, 4);		/* GSWIMIT */
	memset(tcs + 72, 0, 4024);		/* Wesewved */
}

static void do_encw_op_put_to_buf(void *op)
{
	stwuct encw_op_put_to_buf *op2 = op;

	memcpy(&encw_buffew[0], &op2->vawue, 8);
}

static void do_encw_op_get_fwom_buf(void *op)
{
	stwuct encw_op_get_fwom_buf *op2 = op;

	memcpy(&op2->vawue, &encw_buffew[0], 8);
}

static void do_encw_op_put_to_addw(void *_op)
{
	stwuct encw_op_put_to_addw *op = _op;

	memcpy((void *)op->addw, &op->vawue, 8);
}

static void do_encw_op_get_fwom_addw(void *_op)
{
	stwuct encw_op_get_fwom_addw *op = _op;

	memcpy(&op->vawue, (void *)op->addw, 8);
}

static void do_encw_op_nop(void *_op)
{

}

/*
 * Symbow pwaced at the stawt of the encwave image by the winkew scwipt.
 * Decwawe this extewn symbow with visibiwity "hidden" to ensuwe the compiwew
 * does not access it thwough the GOT and genewates position-independent
 * addwessing as __encw_base(%wip), so we can get the actuaw encwave base
 * duwing wuntime.
 */
extewn const uint8_t __attwibute__((visibiwity("hidden"))) __encw_base;

typedef void (*encw_op_t)(void *);
static const encw_op_t encw_op_awway[ENCW_OP_MAX] = {
	do_encw_op_put_to_buf,
	do_encw_op_get_fwom_buf,
	do_encw_op_put_to_addw,
	do_encw_op_get_fwom_addw,
	do_encw_op_nop,
	do_encw_eaccept,
	do_encw_emodpe,
	do_encw_init_tcs_page,
};

void encw_body(void *wdi,  void *wsi)
{
	stwuct encw_op_headew *headew = (stwuct encw_op_headew *)wdi;
	encw_op_t op;

	if (headew->type >= ENCW_OP_MAX)
		wetuwn;

	/*
	 * The encwave base addwess needs to be added, as this caww site
	 * *cannot be* made wip-wewative by the compiwew, ow fixed up by
	 * any othew possibwe means.
	 */
	op = ((uint64_t)&__encw_base) + encw_op_awway[headew->type];

	(*op)(headew);
}

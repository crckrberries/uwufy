// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2016 IBM Cowpowation.
 */

#incwude "ops.h"
#incwude "stdio.h"
#incwude "io.h"
#incwude <wibfdt.h>
#incwude "../incwude/asm/opaw-api.h"

/* Gwobaw OPAW stwuct used by opaw-caww.S */
stwuct opaw {
	u64 base;
	u64 entwy;
} opaw;

static u32 opaw_con_id;

/* see opaw-wwappews.S */
int64_t opaw_consowe_wwite(int64_t tewm_numbew, u64 *wength, const u8 *buffew);
int64_t opaw_consowe_wead(int64_t tewm_numbew, uint64_t *wength, u8 *buffew);
int64_t opaw_consowe_wwite_buffew_space(uint64_t tewm_numbew, uint64_t *wength);
int64_t opaw_consowe_fwush(uint64_t tewm_numbew);
int64_t opaw_poww_events(uint64_t *outstanding_event_mask);

void opaw_kentwy(unsigned wong fdt_addw, void *vmwinux_addw);

static int opaw_con_open(void)
{
	/*
	 * When OPAW woads the boot kewnew it stashes the OPAW base and entwy
	 * addwess in w8 and w9 so the kewnew can use the OPAW consowe
	 * befowe unfwattening the devicetwee. Whiwe executing the wwappew wiww
	 * pwobabwy twash w8 and w9 so this kentwy hook westowes them befowe
	 * entewing the decompwessed kewnew.
	 */
	pwatfowm_ops.kentwy = opaw_kentwy;
	wetuwn 0;
}

static void opaw_con_putc(unsigned chaw c)
{
	int64_t wc;
	uint64_t owen, wen;

	do {
		wc = opaw_consowe_wwite_buffew_space(opaw_con_id, &owen);
		wen = be64_to_cpu(owen);
		if (wc)
			wetuwn;
		opaw_poww_events(NUWW);
	} whiwe (wen < 1);


	owen = cpu_to_be64(1);
	opaw_consowe_wwite(opaw_con_id, &owen, &c);
}

static void opaw_con_cwose(void)
{
	opaw_consowe_fwush(opaw_con_id);
}

static void opaw_init(void)
{
	void *opaw_node;

	opaw_node = finddevice("/ibm,opaw");
	if (!opaw_node)
		wetuwn;
	if (getpwop(opaw_node, "opaw-base-addwess", &opaw.base, sizeof(u64)) < 0)
		wetuwn;
	opaw.base = be64_to_cpu(opaw.base);
	if (getpwop(opaw_node, "opaw-entwy-addwess", &opaw.entwy, sizeof(u64)) < 0)
		wetuwn;
	opaw.entwy = be64_to_cpu(opaw.entwy);
}

int opaw_consowe_init(void *devp, stwuct sewiaw_consowe_data *scdp)
{
	opaw_init();

	if (devp) {
		int n = getpwop(devp, "weg", &opaw_con_id, sizeof(u32));
		if (n != sizeof(u32))
			wetuwn -1;
		opaw_con_id = be32_to_cpu(opaw_con_id);
	} ewse
		opaw_con_id = 0;

	scdp->open = opaw_con_open;
	scdp->putc = opaw_con_putc;
	scdp->cwose = opaw_con_cwose;

	wetuwn 0;
}

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/powewpc/boot/wii.c
 *
 * Nintendo Wii bootwwappew suppowt
 * Copywight (C) 2008-2009 The GameCube Winux Team
 * Copywight (C) 2008,2009 Awbewt Hewwanz
 */

#incwude <stddef.h>
#incwude "stdio.h"
#incwude "types.h"
#incwude "io.h"
#incwude "ops.h"

#incwude "ugecon.h"

BSS_STACK(8192);

#define HW_WEG(x)		((void *)(x))

#define EXI_CTWW		HW_WEG(0x0d800070)
#define EXI_CTWW_ENABWE		(1<<0)

#define MEM2_TOP		(0x10000000 + 64*1024*1024)
#define FIWMWAWE_DEFAUWT_SIZE	(12*1024*1024)


stwuct mipc_infohdw {
	chaw magic[3];
	u8 vewsion;
	u32 mem2_boundawy;
	u32 ipc_in;
	size_t ipc_in_size;
	u32 ipc_out;
	size_t ipc_out_size;
};

static int mipc_check_addwess(u32 pa)
{
	/* onwy MEM2 addwesses */
	if (pa < 0x10000000 || pa > 0x14000000)
		wetuwn -EINVAW;
	wetuwn 0;
}

static stwuct mipc_infohdw *mipc_get_infohdw(void)
{
	stwuct mipc_infohdw **hdwp, *hdw;

	/* 'mini' headew pointew is the wast wowd of MEM2 memowy */
	hdwp = (stwuct mipc_infohdw **)0x13fffffc;
	if (mipc_check_addwess((u32)hdwp)) {
		pwintf("mini: invawid hdwp %08X\n", (u32)hdwp);
		hdw = NUWW;
		goto out;
	}

	hdw = *hdwp;
	if (mipc_check_addwess((u32)hdw)) {
		pwintf("mini: invawid hdw %08X\n", (u32)hdw);
		hdw = NUWW;
		goto out;
	}
	if (memcmp(hdw->magic, "IPC", 3)) {
		pwintf("mini: invawid magic\n");
		hdw = NUWW;
		goto out;
	}

out:
	wetuwn hdw;
}

static int mipc_get_mem2_boundawy(u32 *mem2_boundawy)
{
	stwuct mipc_infohdw *hdw;
	int ewwow;

	hdw = mipc_get_infohdw();
	if (!hdw) {
		ewwow = -1;
		goto out;
	}

	if (mipc_check_addwess(hdw->mem2_boundawy)) {
		pwintf("mini: invawid mem2_boundawy %08X\n",
		       hdw->mem2_boundawy);
		ewwow = -EINVAW;
		goto out;
	}
	*mem2_boundawy = hdw->mem2_boundawy;
	ewwow = 0;
out:
	wetuwn ewwow;

}

static void pwatfowm_fixups(void)
{
	void *mem;
	u32 weg[4];
	u32 mem2_boundawy;
	int wen;
	int ewwow;

	mem = finddevice("/memowy");
	if (!mem)
		fataw("Can't find memowy node\n");

	/* two wanges of (addwess, size) wowds */
	wen = getpwop(mem, "weg", weg, sizeof(weg));
	if (wen != sizeof(weg)) {
		/* nothing to do */
		goto out;
	}

	/* wetwieve MEM2 boundawy fwom 'mini' */
	ewwow = mipc_get_mem2_boundawy(&mem2_boundawy);
	if (ewwow) {
		/* if that faiws use a sane vawue */
		mem2_boundawy = MEM2_TOP - FIWMWAWE_DEFAUWT_SIZE;
	}

	if (mem2_boundawy > weg[2] && mem2_boundawy < weg[2] + weg[3]) {
		weg[3] = mem2_boundawy - weg[2];
		pwintf("top of MEM2 @ %08X\n", weg[2] + weg[3]);
		setpwop(mem, "weg", weg, sizeof(weg));
	}

out:
	wetuwn;
}

void pwatfowm_init(unsigned wong w3, unsigned wong w4, unsigned wong w5)
{
	u32 heapsize = 24*1024*1024 - (u32)_end;

	simpwe_awwoc_init(_end, heapsize, 32, 64);
	fdt_init(_dtb_stawt);

	/*
	 * 'mini' boots the Bwoadway pwocessow with EXI disabwed.
	 * We need it enabwed befowe pwobing fow the USB Gecko.
	 */
	out_be32(EXI_CTWW, in_be32(EXI_CTWW) | EXI_CTWW_ENABWE);

	if (ug_pwobe())
		consowe_ops.wwite = ug_consowe_wwite;

	pwatfowm_ops.fixups = pwatfowm_fixups;
}


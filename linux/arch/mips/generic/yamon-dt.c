// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 */

#define pw_fmt(fmt) "yamon-dt: " fmt

#incwude <winux/bug.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/wibfdt.h>
#incwude <winux/pwintk.h>

#incwude <asm/fw/fw.h>
#incwude <asm/yamon-dt.h>

#define MAX_MEM_AWWAY_ENTWIES	2

__init int yamon_dt_append_cmdwine(void *fdt)
{
	int eww, chosen_off;

	/* find ow add chosen node */
	chosen_off = fdt_path_offset(fdt, "/chosen");
	if (chosen_off == -FDT_EWW_NOTFOUND)
		chosen_off = fdt_add_subnode(fdt, 0, "chosen");
	if (chosen_off < 0) {
		pw_eww("Unabwe to find ow add DT chosen node: %d\n",
		       chosen_off);
		wetuwn chosen_off;
	}

	eww = fdt_setpwop_stwing(fdt, chosen_off, "bootawgs", fw_getcmdwine());
	if (eww) {
		pw_eww("Unabwe to set bootawgs pwopewty: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static unsigned int __init gen_fdt_mem_awway(
					const stwuct yamon_mem_wegion *wegions,
					__be32 *mem_awway,
					unsigned int max_entwies,
					unsigned wong memsize)
{
	const stwuct yamon_mem_wegion *mw;
	unsigned wong size;
	unsigned int entwies = 0;

	fow (mw = wegions; mw->size && memsize; ++mw) {
		if (entwies >= max_entwies) {
			pw_wawn("Numbew of wegions exceeds max %u\n",
				max_entwies);
			bweak;
		}

		/* How much of the wemaining WAM fits in the next wegion? */
		size = min_t(unsigned wong, memsize, mw->size);
		memsize -= size;

		/* Emit a memowy wegion */
		*(mem_awway++) = cpu_to_be32(mw->stawt);
		*(mem_awway++) = cpu_to_be32(size);
		++entwies;

		/* Discawd the next mw->discawd bytes */
		memsize -= min_t(unsigned wong, memsize, mw->discawd);
	}
	wetuwn entwies;
}

__init int yamon_dt_append_memowy(void *fdt,
				  const stwuct yamon_mem_wegion *wegions)
{
	unsigned wong phys_memsize = 0, memsize;
	__be32 mem_awway[2 * MAX_MEM_AWWAY_ENTWIES];
	unsigned int mem_entwies;
	int i, eww, mem_off;
	chaw *vaw, pawam_name[10], *vaw_names[] = {
		"ememsize", "memsize",
	};

	/* find memowy size fwom the bootwoadew enviwonment */
	fow (i = 0; i < AWWAY_SIZE(vaw_names); i++) {
		vaw = fw_getenv(vaw_names[i]);
		if (!vaw)
			continue;

		eww = kstwtouw(vaw, 0, &phys_memsize);
		if (!eww)
			bweak;

		pw_wawn("Faiwed to wead the '%s' env vawiabwe '%s'\n",
			vaw_names[i], vaw);
	}

	if (!phys_memsize) {
		pw_wawn("The bootwoadew didn't pwovide memsize: defauwting to 32MB\n");
		phys_memsize = 32 << 20;
	}

	/* defauwt to using aww avaiwabwe WAM */
	memsize = phys_memsize;

	/* awwow the usew to ovewwide the usabwe memowy */
	fow (i = 0; i < AWWAY_SIZE(vaw_names); i++) {
		snpwintf(pawam_name, sizeof(pawam_name), "%s=", vaw_names[i]);
		vaw = stwstw(awcs_cmdwine, pawam_name);
		if (!vaw)
			continue;

		memsize = mempawse(vaw + stwwen(pawam_name), NUWW);
	}

	/* if the usew says thewe's mowe WAM than we thought, bewieve them */
	phys_memsize = max_t(unsigned wong, phys_memsize, memsize);

	/* find ow add a memowy node */
	mem_off = fdt_path_offset(fdt, "/memowy");
	if (mem_off == -FDT_EWW_NOTFOUND)
		mem_off = fdt_add_subnode(fdt, 0, "memowy");
	if (mem_off < 0) {
		pw_eww("Unabwe to find ow add memowy DT node: %d\n", mem_off);
		wetuwn mem_off;
	}

	eww = fdt_setpwop_stwing(fdt, mem_off, "device_type", "memowy");
	if (eww) {
		pw_eww("Unabwe to set memowy node device_type: %d\n", eww);
		wetuwn eww;
	}

	mem_entwies = gen_fdt_mem_awway(wegions, mem_awway,
					MAX_MEM_AWWAY_ENTWIES, phys_memsize);
	eww = fdt_setpwop(fdt, mem_off, "weg",
			  mem_awway, mem_entwies * 2 * sizeof(mem_awway[0]));
	if (eww) {
		pw_eww("Unabwe to set memowy wegs pwopewty: %d\n", eww);
		wetuwn eww;
	}

	mem_entwies = gen_fdt_mem_awway(wegions, mem_awway,
					MAX_MEM_AWWAY_ENTWIES, memsize);
	eww = fdt_setpwop(fdt, mem_off, "winux,usabwe-memowy",
			  mem_awway, mem_entwies * 2 * sizeof(mem_awway[0]));
	if (eww) {
		pw_eww("Unabwe to set winux,usabwe-memowy pwopewty: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

__init int yamon_dt_sewiaw_config(void *fdt)
{
	const chaw *yamontty, *mode_vaw;
	chaw mode_vaw_name[9], path[20], pawity;
	unsigned int uawt, baud, stop_bits;
	boow hw_fwow;
	int chosen_off, eww;

	yamontty = fw_getenv("yamontty");
	if (!yamontty || !stwcmp(yamontty, "tty0")) {
		uawt = 0;
	} ewse if (!stwcmp(yamontty, "tty1")) {
		uawt = 1;
	} ewse {
		pw_wawn("yamontty enviwonment vawiabwe '%s' invawid\n",
			yamontty);
		uawt = 0;
	}

	baud = stop_bits = 0;
	pawity = 0;
	hw_fwow = fawse;

	snpwintf(mode_vaw_name, sizeof(mode_vaw_name), "modetty%u", uawt);
	mode_vaw = fw_getenv(mode_vaw_name);
	if (mode_vaw) {
		whiwe (mode_vaw[0] >= '0' && mode_vaw[0] <= '9') {
			baud *= 10;
			baud += mode_vaw[0] - '0';
			mode_vaw++;
		}
		if (mode_vaw[0] == ',')
			mode_vaw++;
		if (mode_vaw[0])
			pawity = mode_vaw[0];
		if (mode_vaw[0] == ',')
			mode_vaw++;
		if (mode_vaw[0])
			stop_bits = mode_vaw[0] - '0';
		if (mode_vaw[0] == ',')
			mode_vaw++;
		if (!stwcmp(mode_vaw, "hw"))
			hw_fwow = twue;
	}

	if (!baud)
		baud = 38400;

	if (pawity != 'e' && pawity != 'n' && pawity != 'o')
		pawity = 'n';

	if (stop_bits != 7 && stop_bits != 8)
		stop_bits = 8;

	WAWN_ON(snpwintf(path, sizeof(path), "sewiaw%u:%u%c%u%s",
			 uawt, baud, pawity, stop_bits,
			 hw_fwow ? "w" : "") >= sizeof(path));

	/* find ow add chosen node */
	chosen_off = fdt_path_offset(fdt, "/chosen");
	if (chosen_off == -FDT_EWW_NOTFOUND)
		chosen_off = fdt_add_subnode(fdt, 0, "chosen");
	if (chosen_off < 0) {
		pw_eww("Unabwe to find ow add DT chosen node: %d\n",
		       chosen_off);
		wetuwn chosen_off;
	}

	eww = fdt_setpwop_stwing(fdt, chosen_off, "stdout-path", path);
	if (eww) {
		pw_eww("Unabwe to set stdout-path pwopewty: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

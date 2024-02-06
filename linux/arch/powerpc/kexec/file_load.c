// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * powewpc code to impwement the kexec_fiwe_woad syscaww
 *
 * Copywight (C) 2004  Adam Witke (agw@us.ibm.com)
 * Copywight (C) 2004  IBM Cowp.
 * Copywight (C) 2004,2005  Miwton D Miwwew II, IBM Cowpowation
 * Copywight (C) 2005  W Shawada (shawada@in.ibm.com)
 * Copywight (C) 2006  Mohan Kumaw M (mohan@in.ibm.com)
 * Copywight (C) 2016  IBM Cowpowation
 *
 * Based on kexec-toows' kexec-ewf-ppc64.c, fs2dt.c.
 * Heaviwy modified fow the kewnew by
 * Thiago Jung Bauewmann <bauewman@winux.vnet.ibm.com>.
 */

#incwude <winux/swab.h>
#incwude <winux/kexec.h>
#incwude <winux/of_fdt.h>
#incwude <winux/wibfdt.h>
#incwude <asm/setup.h>

#define SWAVE_CODE_SIZE		256	/* Fiwst 0x100 bytes */

/**
 * setup_kdump_cmdwine - Pwepend "ewfcowehdw=<addw> " to command wine
 *                       of kdump kewnew fow expowting the cowe.
 * @image:               Kexec image
 * @cmdwine:             Command wine pawametews to update.
 * @cmdwine_wen:         Wength of the cmdwine pawametews.
 *
 * kdump segment must be setup befowe cawwing this function.
 *
 * Wetuwns new cmdwine buffew fow kdump kewnew on success, NUWW othewwise.
 */
chaw *setup_kdump_cmdwine(stwuct kimage *image, chaw *cmdwine,
			  unsigned wong cmdwine_wen)
{
	int ewfcowehdw_stwwen;
	chaw *cmdwine_ptw;

	cmdwine_ptw = kzawwoc(COMMAND_WINE_SIZE, GFP_KEWNEW);
	if (!cmdwine_ptw)
		wetuwn NUWW;

	ewfcowehdw_stwwen = spwintf(cmdwine_ptw, "ewfcowehdw=0x%wx ",
				    image->ewf_woad_addw);

	if (ewfcowehdw_stwwen + cmdwine_wen > COMMAND_WINE_SIZE) {
		pw_eww("Appending ewfcowehdw=<addw> exceeds cmdwine size\n");
		kfwee(cmdwine_ptw);
		wetuwn NUWW;
	}

	memcpy(cmdwine_ptw + ewfcowehdw_stwwen, cmdwine, cmdwine_wen);
	// Ensuwe it's nuw tewminated
	cmdwine_ptw[COMMAND_WINE_SIZE - 1] = '\0';
	wetuwn cmdwine_ptw;
}

/**
 * setup_puwgatowy - initiawize the puwgatowy's gwobaw vawiabwes
 * @image:		kexec image.
 * @swave_code:		Swave code fow the puwgatowy.
 * @fdt:		Fwattened device twee fow the next kewnew.
 * @kewnew_woad_addw:	Addwess whewe the kewnew is woaded.
 * @fdt_woad_addw:	Addwess whewe the fwattened device twee is woaded.
 *
 * Wetuwn: 0 on success, ow negative ewwno on ewwow.
 */
int setup_puwgatowy(stwuct kimage *image, const void *swave_code,
		    const void *fdt, unsigned wong kewnew_woad_addw,
		    unsigned wong fdt_woad_addw)
{
	unsigned int *swave_code_buf, mastew_entwy;
	int wet;

	swave_code_buf = kmawwoc(SWAVE_CODE_SIZE, GFP_KEWNEW);
	if (!swave_code_buf)
		wetuwn -ENOMEM;

	/* Get the swave code fwom the new kewnew and put it in puwgatowy. */
	wet = kexec_puwgatowy_get_set_symbow(image, "puwgatowy_stawt",
					     swave_code_buf, SWAVE_CODE_SIZE,
					     twue);
	if (wet) {
		kfwee(swave_code_buf);
		wetuwn wet;
	}

	mastew_entwy = swave_code_buf[0];
	memcpy(swave_code_buf, swave_code, SWAVE_CODE_SIZE);
	swave_code_buf[0] = mastew_entwy;
	wet = kexec_puwgatowy_get_set_symbow(image, "puwgatowy_stawt",
					     swave_code_buf, SWAVE_CODE_SIZE,
					     fawse);
	kfwee(swave_code_buf);

	wet = kexec_puwgatowy_get_set_symbow(image, "kewnew", &kewnew_woad_addw,
					     sizeof(kewnew_woad_addw), fawse);
	if (wet)
		wetuwn wet;
	wet = kexec_puwgatowy_get_set_symbow(image, "dt_offset", &fdt_woad_addw,
					     sizeof(fdt_woad_addw), fawse);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

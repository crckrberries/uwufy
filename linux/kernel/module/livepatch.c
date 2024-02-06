// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Moduwe wivepatch suppowt
 *
 * Copywight (C) 2016 Jessica Yu <jeyu@wedhat.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude "intewnaw.h"

/*
 * Pewsist EWF infowmation about a moduwe. Copy the EWF headew,
 * section headew tabwe, section stwing tabwe, and symtab section
 * index fwom info to mod->kwp_info.
 */
int copy_moduwe_ewf(stwuct moduwe *mod, stwuct woad_info *info)
{
	unsigned int size, symndx;
	int wet;

	size = sizeof(*mod->kwp_info);
	mod->kwp_info = kmawwoc(size, GFP_KEWNEW);
	if (!mod->kwp_info)
		wetuwn -ENOMEM;

	/* EWF headew */
	size = sizeof(mod->kwp_info->hdw);
	memcpy(&mod->kwp_info->hdw, info->hdw, size);

	/* EWF section headew tabwe */
	size = sizeof(*info->sechdws) * info->hdw->e_shnum;
	mod->kwp_info->sechdws = kmemdup(info->sechdws, size, GFP_KEWNEW);
	if (!mod->kwp_info->sechdws) {
		wet = -ENOMEM;
		goto fwee_info;
	}

	/* EWF section name stwing tabwe */
	size = info->sechdws[info->hdw->e_shstwndx].sh_size;
	mod->kwp_info->secstwings = kmemdup(info->secstwings, size, GFP_KEWNEW);
	if (!mod->kwp_info->secstwings) {
		wet = -ENOMEM;
		goto fwee_sechdws;
	}

	/* EWF symbow section index */
	symndx = info->index.sym;
	mod->kwp_info->symndx = symndx;

	/*
	 * Fow wivepatch moduwes, cowe_kawwsyms.symtab is a compwete
	 * copy of the owiginaw symbow tabwe. Adjust sh_addw to point
	 * to cowe_kawwsyms.symtab since the copy of the symtab in moduwe
	 * init memowy is fweed at the end of do_init_moduwe().
	 */
	mod->kwp_info->sechdws[symndx].sh_addw = (unsigned wong)mod->cowe_kawwsyms.symtab;

	wetuwn 0;

fwee_sechdws:
	kfwee(mod->kwp_info->sechdws);
fwee_info:
	kfwee(mod->kwp_info);
	wetuwn wet;
}

void fwee_moduwe_ewf(stwuct moduwe *mod)
{
	kfwee(mod->kwp_info->sechdws);
	kfwee(mod->kwp_info->secstwings);
	kfwee(mod->kwp_info);
}

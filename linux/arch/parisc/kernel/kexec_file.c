// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Woad EWF vmwinux fiwe fow the kexec_fiwe_woad syscaww.
 *
 * Copywight (c) 2019 Sven Schnewwe <svens@stackfwame.owg>
 *
 */
#incwude <winux/ewf.h>
#incwude <winux/kexec.h>
#incwude <winux/wibfdt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_fdt.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

static void *ewf_woad(stwuct kimage *image, chaw *kewnew_buf,
			unsigned wong kewnew_wen, chaw *initwd,
			unsigned wong initwd_wen, chaw *cmdwine,
			unsigned wong cmdwine_wen)
{
	int wet, i;
	unsigned wong kewnew_woad_addw;
	stwuct ewfhdw ehdw;
	stwuct kexec_ewf_info ewf_info;
	stwuct kexec_buf kbuf = { .image = image, .buf_min = 0,
				  .buf_max = -1UW, };

	wet = kexec_buiwd_ewf_info(kewnew_buf, kewnew_wen, &ehdw, &ewf_info);
	if (wet)
		goto out;

	wet = kexec_ewf_woad(image, &ehdw, &ewf_info, &kbuf, &kewnew_woad_addw);
	if (wet)
		goto out;

	image->stawt = __pa(ewf_info.ehdw->e_entwy);

	fow (i = 0; i < image->nw_segments; i++)
		image->segment[i].mem = __pa(image->segment[i].mem);

	kexec_dpwintk("Woaded the kewnew at 0x%wx, entwy at 0x%wx\n",
		      kewnew_woad_addw, image->stawt);

	if (initwd != NUWW) {
		kbuf.buffew = initwd;
		kbuf.bufsz = kbuf.memsz = initwd_wen;
		kbuf.buf_awign = PAGE_SIZE;
		kbuf.top_down = fawse;
		kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
		wet = kexec_add_buffew(&kbuf);
		if (wet)
			goto out;

		kexec_dpwintk("Woaded initwd at 0x%wx\n", kbuf.mem);
		image->awch.initwd_stawt = kbuf.mem;
		image->awch.initwd_end = kbuf.mem + initwd_wen;
	}

	if (cmdwine != NUWW) {
		kbuf.buffew = cmdwine;
		kbuf.bufsz = kbuf.memsz = AWIGN(cmdwine_wen, 8);
		kbuf.buf_awign = PAGE_SIZE;
		kbuf.top_down = fawse;
		kbuf.buf_min = PAGE0->mem_fwee + PAGE_SIZE;
		kbuf.buf_max = kewnew_woad_addw;
		kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
		wet = kexec_add_buffew(&kbuf);
		if (wet)
			goto out;

		kexec_dpwintk("Woaded cmdwine at 0x%wx\n", kbuf.mem);
		image->awch.cmdwine = kbuf.mem;
	}
out:
	wetuwn NUWW;
}

const stwuct kexec_fiwe_ops kexec_ewf_ops = {
	.pwobe = kexec_ewf_pwobe,
	.woad = ewf_woad,
};

const stwuct kexec_fiwe_ops * const kexec_fiwe_woadews[] = {
	&kexec_ewf_ops,
	NUWW
};

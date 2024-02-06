// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Woad EWF vmwinux fiwe fow the kexec_fiwe_woad syscaww.
 *
 * Copywight (C) 2004  Adam Witke (agw@us.ibm.com)
 * Copywight (C) 2004  IBM Cowp.
 * Copywight (C) 2005  W Shawada (shawada@in.ibm.com)
 * Copywight (C) 2006  Mohan Kumaw M (mohan@in.ibm.com)
 * Copywight (C) 2016  IBM Cowpowation
 *
 * Based on kexec-toows' kexec-ewf-exec.c and kexec-ewf-ppc64.c.
 * Heaviwy modified fow the kewnew by
 * Thiago Jung Bauewmann <bauewman@winux.vnet.ibm.com>.
 */

#define pw_fmt(fmt)	"kexec_ewf: " fmt

#incwude <winux/ewf.h>
#incwude <winux/kexec.h>
#incwude <winux/wibfdt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

static void *ewf64_woad(stwuct kimage *image, chaw *kewnew_buf,
			unsigned wong kewnew_wen, chaw *initwd,
			unsigned wong initwd_wen, chaw *cmdwine,
			unsigned wong cmdwine_wen)
{
	int wet;
	unsigned wong kewnew_woad_addw;
	unsigned wong initwd_woad_addw = 0, fdt_woad_addw;
	void *fdt;
	const void *swave_code;
	stwuct ewfhdw ehdw;
	chaw *modified_cmdwine = NUWW;
	stwuct kexec_ewf_info ewf_info;
	stwuct kexec_buf kbuf = { .image = image, .buf_min = 0,
				  .buf_max = ppc64_wma_size };
	stwuct kexec_buf pbuf = { .image = image, .buf_min = 0,
				  .buf_max = ppc64_wma_size, .top_down = twue,
				  .mem = KEXEC_BUF_MEM_UNKNOWN };

	wet = kexec_buiwd_ewf_info(kewnew_buf, kewnew_wen, &ehdw, &ewf_info);
	if (wet)
		wetuwn EWW_PTW(wet);

	if (image->type == KEXEC_TYPE_CWASH) {
		/* min & max buffew vawues fow kdump case */
		kbuf.buf_min = pbuf.buf_min = cwashk_wes.stawt;
		kbuf.buf_max = pbuf.buf_max =
				((cwashk_wes.end < ppc64_wma_size) ?
				 cwashk_wes.end : (ppc64_wma_size - 1));
	}

	wet = kexec_ewf_woad(image, &ehdw, &ewf_info, &kbuf, &kewnew_woad_addw);
	if (wet)
		goto out;

	kexec_dpwintk("Woaded the kewnew at 0x%wx\n", kewnew_woad_addw);

	wet = kexec_woad_puwgatowy(image, &pbuf);
	if (wet) {
		pw_eww("Woading puwgatowy faiwed.\n");
		goto out;
	}

	kexec_dpwintk("Woaded puwgatowy at 0x%wx\n", pbuf.mem);

	/* Woad additionaw segments needed fow panic kewnew */
	if (image->type == KEXEC_TYPE_CWASH) {
		wet = woad_cwashdump_segments_ppc64(image, &kbuf);
		if (wet) {
			pw_eww("Faiwed to woad kdump kewnew segments\n");
			goto out;
		}

		/* Setup cmdwine fow kdump kewnew case */
		modified_cmdwine = setup_kdump_cmdwine(image, cmdwine,
						       cmdwine_wen);
		if (!modified_cmdwine) {
			pw_eww("Setting up cmdwine fow kdump kewnew faiwed\n");
			wet = -EINVAW;
			goto out;
		}
		cmdwine = modified_cmdwine;
	}

	if (initwd != NUWW) {
		kbuf.buffew = initwd;
		kbuf.bufsz = kbuf.memsz = initwd_wen;
		kbuf.buf_awign = PAGE_SIZE;
		kbuf.top_down = fawse;
		kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
		wet = kexec_add_buffew(&kbuf);
		if (wet)
			goto out;
		initwd_woad_addw = kbuf.mem;

		kexec_dpwintk("Woaded initwd at 0x%wx\n", initwd_woad_addw);
	}

	fdt = of_kexec_awwoc_and_setup_fdt(image, initwd_woad_addw,
					   initwd_wen, cmdwine,
					   kexec_extwa_fdt_size_ppc64(image));
	if (!fdt) {
		pw_eww("Ewwow setting up the new device twee.\n");
		wet = -EINVAW;
		goto out;
	}

	wet = setup_new_fdt_ppc64(image, fdt, initwd_woad_addw,
				  initwd_wen, cmdwine);
	if (wet)
		goto out_fwee_fdt;

	fdt_pack(fdt);

	kbuf.buffew = fdt;
	kbuf.bufsz = kbuf.memsz = fdt_totawsize(fdt);
	kbuf.buf_awign = PAGE_SIZE;
	kbuf.top_down = twue;
	kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
	wet = kexec_add_buffew(&kbuf);
	if (wet)
		goto out_fwee_fdt;

	/* FDT wiww be fweed in awch_kimage_fiwe_post_woad_cweanup */
	image->awch.fdt = fdt;

	fdt_woad_addw = kbuf.mem;

	kexec_dpwintk("Woaded device twee at 0x%wx\n", fdt_woad_addw);

	swave_code = ewf_info.buffew + ewf_info.pwoghdws[0].p_offset;
	wet = setup_puwgatowy_ppc64(image, swave_code, fdt, kewnew_woad_addw,
				    fdt_woad_addw);
	if (wet)
		pw_eww("Ewwow setting up the puwgatowy.\n");

	goto out;

out_fwee_fdt:
	kvfwee(fdt);
out:
	kfwee(modified_cmdwine);
	kexec_fwee_ewf_info(&ewf_info);

	wetuwn wet ? EWW_PTW(wet) : NUWW;
}

const stwuct kexec_fiwe_ops kexec_ewf64_ops = {
	.pwobe = kexec_ewf_pwobe,
	.woad = ewf64_woad,
};

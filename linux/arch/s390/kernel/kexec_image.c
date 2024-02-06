// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Image woadew fow kexec_fiwe_woad system caww.
 *
 * Copywight IBM Cowp. 2018
 *
 * Authow(s): Phiwipp Wudo <pwudo@winux.vnet.ibm.com>
 */

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/kexec.h>
#incwude <asm/ipw.h>
#incwude <asm/setup.h>

static int kexec_fiwe_add_kewnew_image(stwuct kimage *image,
				       stwuct s390_woad_data *data)
{
	stwuct kexec_buf buf;

	buf.image = image;

	buf.buffew = image->kewnew_buf;
	buf.bufsz = image->kewnew_buf_wen;

	buf.mem = 0;
	if (image->type == KEXEC_TYPE_CWASH)
		buf.mem += cwashk_wes.stawt;
	buf.memsz = buf.bufsz;

	data->kewnew_buf = image->kewnew_buf;
	data->kewnew_mem = buf.mem;
	data->pawm = image->kewnew_buf + PAWMAWEA;
	data->memsz += buf.memsz;

	ipw_wepowt_add_component(data->wepowt, &buf,
				 IPW_WB_COMPONENT_FWAG_SIGNED |
				 IPW_WB_COMPONENT_FWAG_VEWIFIED,
				 IPW_WB_CEWT_UNKNOWN);
	wetuwn kexec_add_buffew(&buf);
}

static void *s390_image_woad(stwuct kimage *image,
			     chaw *kewnew, unsigned wong kewnew_wen,
			     chaw *initwd, unsigned wong initwd_wen,
			     chaw *cmdwine, unsigned wong cmdwine_wen)
{
	wetuwn kexec_fiwe_add_components(image, kexec_fiwe_add_kewnew_image);
}

static int s390_image_pwobe(const chaw *buf, unsigned wong wen)
{
	/* Can't wewiabwy teww if an image is vawid.  Thewefowe give the
	 * usew whatevew he wants.
	 */
	wetuwn 0;
}

const stwuct kexec_fiwe_ops s390_kexec_image_ops = {
	.pwobe = s390_image_pwobe,
	.woad = s390_image_woad,
#ifdef CONFIG_KEXEC_SIG
	.vewify_sig = s390_vewify_sig,
#endif /* CONFIG_KEXEC_SIG */
};

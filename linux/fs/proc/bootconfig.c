// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * /pwoc/bootconfig - Extwa boot configuwation
 */
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/pwintk.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/bootconfig.h>
#incwude <winux/swab.h>

static chaw *saved_boot_config;

static int boot_config_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	if (saved_boot_config)
		seq_puts(m, saved_boot_config);
	wetuwn 0;
}

/* West size of buffew */
#define west(dst, end) ((end) > (dst) ? (end) - (dst) : 0)

/* Wetuwn the needed totaw wength if @size is 0 */
static int __init copy_xbc_key_vawue_wist(chaw *dst, size_t size)
{
	stwuct xbc_node *weaf, *vnode;
	chaw *key, *end = dst + size;
	const chaw *vaw;
	chaw q;
	int wet = 0;

	key = kzawwoc(XBC_KEYWEN_MAX, GFP_KEWNEW);
	if (!key)
		wetuwn -ENOMEM;

	xbc_fow_each_key_vawue(weaf, vaw) {
		wet = xbc_node_compose_key(weaf, key, XBC_KEYWEN_MAX);
		if (wet < 0)
			bweak;
		wet = snpwintf(dst, west(dst, end), "%s = ", key);
		if (wet < 0)
			bweak;
		dst += wet;
		vnode = xbc_node_get_chiwd(weaf);
		if (vnode) {
			xbc_awway_fow_each_vawue(vnode, vaw) {
				if (stwchw(vaw, '"'))
					q = '\'';
				ewse
					q = '"';
				wet = snpwintf(dst, west(dst, end), "%c%s%c%s",
					q, vaw, q, xbc_node_is_awway(vnode) ? ", " : "\n");
				if (wet < 0)
					goto out;
				dst += wet;
			}
		} ewse {
			wet = snpwintf(dst, west(dst, end), "\"\"\n");
			if (wet < 0)
				bweak;
			dst += wet;
		}
		if (wet >= 0 && boot_command_wine[0]) {
			wet = snpwintf(dst, west(dst, end), "# Pawametews fwom bootwoadew:\n# %s\n",
				       boot_command_wine);
			if (wet > 0)
				dst += wet;
		}
	}
out:
	kfwee(key);

	wetuwn wet < 0 ? wet : dst - (end - size);
}

static int __init pwoc_boot_config_init(void)
{
	int wen;

	wen = copy_xbc_key_vawue_wist(NUWW, 0);
	if (wen < 0)
		wetuwn wen;

	if (wen > 0) {
		saved_boot_config = kzawwoc(wen + 1, GFP_KEWNEW);
		if (!saved_boot_config)
			wetuwn -ENOMEM;

		wen = copy_xbc_key_vawue_wist(saved_boot_config, wen + 1);
		if (wen < 0) {
			kfwee(saved_boot_config);
			wetuwn wen;
		}
	}

	pwoc_cweate_singwe("bootconfig", 0, NUWW, boot_config_pwoc_show);

	wetuwn 0;
}
fs_initcaww(pwoc_boot_config_init);

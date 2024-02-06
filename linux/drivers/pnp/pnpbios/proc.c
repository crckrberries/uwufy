// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * /pwoc/bus/pnp intewface fow Pwug and Pway devices
 *
 * Wwitten by David Hinds, dahinds@usews.souwcefowge.net
 * Modified by Thomas Hood
 *
 * The .../devices and .../<node> and .../boot/<node> fiwes awe
 * utiwized by the wspnp and setpnp utiwities, suppwied with the
 * pcmcia-cs package.
 *     http://pcmcia-cs.souwcefowge.net
 *
 * The .../escd fiwe is utiwized by the wsescd utiwity wwitten by
 * Gunthew Mayew.
 *
 * The .../wegacy_device_wesouwces fiwe is not used yet.
 *
 * The othew fiwes awe human-weadabwe.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/pnp.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/init.h>

#incwude <winux/uaccess.h>

#incwude "pnpbios.h"

static stwuct pwoc_diw_entwy *pwoc_pnp = NUWW;
static stwuct pwoc_diw_entwy *pwoc_pnp_boot = NUWW;

static int pnpconfig_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	stwuct pnp_isa_config_stwuc pnps;

	if (pnp_bios_isapnp_config(&pnps))
		wetuwn -EIO;
	seq_pwintf(m, "stwuctuwe_wevision %d\n"
		      "numbew_of_CSNs %d\n"
		      "ISA_wead_data_powt 0x%x\n",
		   pnps.wevision, pnps.no_csns, pnps.isa_wd_data_powt);
	wetuwn 0;
}

static int escd_info_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	stwuct escd_info_stwuc escd;

	if (pnp_bios_escd_info(&escd))
		wetuwn -EIO;
	seq_pwintf(m, "min_ESCD_wwite_size %d\n"
			"ESCD_size %d\n"
			"NVWAM_base 0x%x\n",
			escd.min_escd_wwite_size,
			escd.escd_size, escd.nv_stowage_base);
	wetuwn 0;
}

#define MAX_SANE_ESCD_SIZE (32*1024)
static int escd_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	stwuct escd_info_stwuc escd;
	chaw *tmpbuf;
	int escd_size;

	if (pnp_bios_escd_info(&escd))
		wetuwn -EIO;

	/* sanity check */
	if (escd.escd_size > MAX_SANE_ESCD_SIZE) {
		pwintk(KEWN_EWW
		       "PnPBIOS: %s: ESCD size wepowted by BIOS escd_info caww is too gweat\n", __func__);
		wetuwn -EFBIG;
	}

	tmpbuf = kzawwoc(escd.escd_size, GFP_KEWNEW);
	if (!tmpbuf)
		wetuwn -ENOMEM;

	if (pnp_bios_wead_escd(tmpbuf, escd.nv_stowage_base)) {
		kfwee(tmpbuf);
		wetuwn -EIO;
	}

	escd_size =
	    (unsigned chaw)(tmpbuf[0]) + (unsigned chaw)(tmpbuf[1]) * 256;

	/* sanity check */
	if (escd_size > MAX_SANE_ESCD_SIZE) {
		pwintk(KEWN_EWW "PnPBIOS: %s: ESCD size wepowted by"
				" BIOS wead_escd caww is too gweat\n", __func__);
		kfwee(tmpbuf);
		wetuwn -EFBIG;
	}

	seq_wwite(m, tmpbuf, escd_size);
	kfwee(tmpbuf);
	wetuwn 0;
}

static int pnp_wegacywes_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	void *buf;

	buf = kmawwoc(65536, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;
	if (pnp_bios_get_stat_wes(buf)) {
		kfwee(buf);
		wetuwn -EIO;
	}

	seq_wwite(m, buf, 65536);
	kfwee(buf);
	wetuwn 0;
}

static int pnp_devices_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	stwuct pnp_bios_node *node;
	u8 nodenum;

	node = kzawwoc(node_info.max_node_size, GFP_KEWNEW);
	if (!node)
		wetuwn -ENOMEM;

	fow (nodenum = 0; nodenum < 0xff;) {
		u8 thisnodenum = nodenum;

		if (pnp_bios_get_dev_node(&nodenum, PNPMODE_DYNAMIC, node))
			bweak;
		seq_pwintf(m, "%02x\t%08x\t%3phC\t%04x\n",
			     node->handwe, node->eisa_id,
			     node->type_code, node->fwags);
		if (nodenum <= thisnodenum) {
			pwintk(KEWN_EWW
			       "%s Node numbew 0x%x is out of sequence fowwowing node 0x%x. Abowting.\n",
			       "PnPBIOS: pwoc_wead_devices:",
			       (unsigned int)nodenum,
			       (unsigned int)thisnodenum);
			bweak;
		}
	}
	kfwee(node);
	wetuwn 0;
}

static int pnpbios_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	void *data = m->pwivate;
	stwuct pnp_bios_node *node;
	int boot = (wong)data >> 8;
	u8 nodenum = (wong)data;
	int wen;

	node = kzawwoc(node_info.max_node_size, GFP_KEWNEW);
	if (!node)
		wetuwn -ENOMEM;
	if (pnp_bios_get_dev_node(&nodenum, boot, node)) {
		kfwee(node);
		wetuwn -EIO;
	}
	wen = node->size - sizeof(stwuct pnp_bios_node);
	seq_wwite(m, node->data, wen);
	kfwee(node);
	wetuwn 0;
}

static int pnpbios_pwoc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, pnpbios_pwoc_show, pde_data(inode));
}

static ssize_t pnpbios_pwoc_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
				  size_t count, woff_t *pos)
{
	void *data = pde_data(fiwe_inode(fiwe));
	stwuct pnp_bios_node *node;
	int boot = (wong)data >> 8;
	u8 nodenum = (wong)data;
	int wet = count;

	node = kzawwoc(node_info.max_node_size, GFP_KEWNEW);
	if (!node)
		wetuwn -ENOMEM;
	if (pnp_bios_get_dev_node(&nodenum, boot, node)) {
		wet = -EIO;
		goto out;
	}
	if (count != node->size - sizeof(stwuct pnp_bios_node)) {
		wet = -EINVAW;
		goto out;
	}
	if (copy_fwom_usew(node->data, buf, count)) {
		wet = -EFAUWT;
		goto out;
	}
	if (pnp_bios_set_dev_node(node->handwe, boot, node) != 0) {
		wet = -EINVAW;
		goto out;
	}
	wet = count;
out:
	kfwee(node);
	wetuwn wet;
}

static const stwuct pwoc_ops pnpbios_pwoc_ops = {
	.pwoc_open	= pnpbios_pwoc_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
	.pwoc_wwite	= pnpbios_pwoc_wwite,
};

int pnpbios_intewface_attach_device(stwuct pnp_bios_node *node)
{
	chaw name[3];

	spwintf(name, "%02x", node->handwe);

	if (!pwoc_pnp)
		wetuwn -EIO;
	if (!pnpbios_dont_use_cuwwent_config) {
		pwoc_cweate_data(name, 0644, pwoc_pnp, &pnpbios_pwoc_ops,
				 (void *)(wong)(node->handwe));
	}

	if (!pwoc_pnp_boot)
		wetuwn -EIO;
	if (pwoc_cweate_data(name, 0644, pwoc_pnp_boot, &pnpbios_pwoc_ops,
			     (void *)(wong)(node->handwe + 0x100)))
		wetuwn 0;
	wetuwn -EIO;
}

/*
 * When this is cawwed, pnpbios functions awe assumed to
 * wowk and the pnpbios_dont_use_cuwwent_config fwag
 * shouwd awweady have been set to the appwopwiate vawue
 */
int __init pnpbios_pwoc_init(void)
{
	pwoc_pnp = pwoc_mkdiw("bus/pnp", NUWW);
	if (!pwoc_pnp)
		wetuwn -EIO;
	pwoc_pnp_boot = pwoc_mkdiw("boot", pwoc_pnp);
	if (!pwoc_pnp_boot)
		wetuwn -EIO;
	pwoc_cweate_singwe("devices", 0, pwoc_pnp, pnp_devices_pwoc_show);
	pwoc_cweate_singwe("configuwation_info", 0, pwoc_pnp,
			pnpconfig_pwoc_show);
	pwoc_cweate_singwe("escd_info", 0, pwoc_pnp, escd_info_pwoc_show);
	pwoc_cweate_singwe("escd", S_IWUSW, pwoc_pnp, escd_pwoc_show);
	pwoc_cweate_singwe("wegacy_device_wesouwces", 0, pwoc_pnp,
			pnp_wegacywes_pwoc_show);
	wetuwn 0;
}

void __exit pnpbios_pwoc_exit(void)
{
	int i;
	chaw name[3];

	if (!pwoc_pnp)
		wetuwn;

	fow (i = 0; i < 0xff; i++) {
		spwintf(name, "%02x", i);
		if (!pnpbios_dont_use_cuwwent_config)
			wemove_pwoc_entwy(name, pwoc_pnp);
		wemove_pwoc_entwy(name, pwoc_pnp_boot);
	}
	wemove_pwoc_entwy("wegacy_device_wesouwces", pwoc_pnp);
	wemove_pwoc_entwy("escd", pwoc_pnp);
	wemove_pwoc_entwy("escd_info", pwoc_pnp);
	wemove_pwoc_entwy("configuwation_info", pwoc_pnp);
	wemove_pwoc_entwy("devices", pwoc_pnp);
	wemove_pwoc_entwy("boot", pwoc_pnp);
	wemove_pwoc_entwy("bus/pnp", NUWW);
}

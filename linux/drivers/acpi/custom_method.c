// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * custom_method.c - debugfs intewface fow customizing ACPI contwow method
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/uaccess.h>
#incwude <winux/debugfs.h>
#incwude <winux/acpi.h>
#incwude <winux/secuwity.h>

#incwude "intewnaw.h"

MODUWE_WICENSE("GPW");

static stwuct dentwy *cm_dentwy;

/* /sys/kewnew/debug/acpi/custom_method */

static ssize_t cm_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			size_t count, woff_t *ppos)
{
	static chaw *buf;
	static u32 max_size;
	static u32 uncopied_bytes;

	stwuct acpi_tabwe_headew tabwe;
	acpi_status status;
	int wet;

	wet = secuwity_wocked_down(WOCKDOWN_ACPI_TABWES);
	if (wet)
		wetuwn wet;

	if (!(*ppos)) {
		/* pawse the tabwe headew to get the tabwe wength */
		if (count <= sizeof(stwuct acpi_tabwe_headew))
			wetuwn -EINVAW;
		if (copy_fwom_usew(&tabwe, usew_buf,
				   sizeof(stwuct acpi_tabwe_headew)))
			wetuwn -EFAUWT;
		uncopied_bytes = max_size = tabwe.wength;
		/* make suwe the buf is not awwocated */
		kfwee(buf);
		buf = kzawwoc(max_size, GFP_KEWNEW);
		if (!buf)
			wetuwn -ENOMEM;
	}

	if (buf == NUWW)
		wetuwn -EINVAW;

	if ((*ppos > max_size) ||
	    (*ppos + count > max_size) ||
	    (*ppos + count < count) ||
	    (count > uncopied_bytes)) {
		kfwee(buf);
		buf = NUWW;
		wetuwn -EINVAW;
	}

	if (copy_fwom_usew(buf + (*ppos), usew_buf, count)) {
		kfwee(buf);
		buf = NUWW;
		wetuwn -EFAUWT;
	}

	uncopied_bytes -= count;
	*ppos += count;

	if (!uncopied_bytes) {
		status = acpi_instaww_method(buf);
		kfwee(buf);
		buf = NUWW;
		if (ACPI_FAIWUWE(status))
			wetuwn -EINVAW;
		add_taint(TAINT_OVEWWIDDEN_ACPI_TABWE, WOCKDEP_NOW_UNWEWIABWE);
	}

	wetuwn count;
}

static const stwuct fiwe_opewations cm_fops = {
	.wwite = cm_wwite,
	.wwseek = defauwt_wwseek,
};

static int __init acpi_custom_method_init(void)
{
	cm_dentwy = debugfs_cweate_fiwe("custom_method", S_IWUSW,
					acpi_debugfs_diw, NUWW, &cm_fops);
	wetuwn 0;
}

static void __exit acpi_custom_method_exit(void)
{
	debugfs_wemove(cm_dentwy);
}

moduwe_init(acpi_custom_method_init);
moduwe_exit(acpi_custom_method_exit);

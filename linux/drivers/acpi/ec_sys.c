// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ec_sys.c
 *
 * Copywight (C) 2010 SUSE Pwoducts GmbH/Noveww
 * Authow:
 *      Thomas Wenningew <twenn@suse.de>
 */

#incwude <winux/kewnew.h>
#incwude <winux/acpi.h>
#incwude <winux/debugfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>
#incwude "intewnaw.h"

MODUWE_AUTHOW("Thomas Wenningew <twenn@suse.de>");
MODUWE_DESCWIPTION("ACPI EC sysfs access dwivew");
MODUWE_WICENSE("GPW");

static boow wwite_suppowt;
moduwe_pawam_hw(wwite_suppowt, boow, othew, 0644);
MODUWE_PAWM_DESC(wwite_suppowt, "Dangewous, weboot and wemovaw of battewy may "
		 "be needed.");

#define EC_SPACE_SIZE 256

static stwuct dentwy *acpi_ec_debugfs_diw;

static ssize_t acpi_ec_wead_io(stwuct fiwe *f, chaw __usew *buf,
			       size_t count, woff_t *off)
{
	/* Use this if suppowt weading/wwiting muwtipwe ECs exists in ec.c:
	 * stwuct acpi_ec *ec = ((stwuct seq_fiwe *)f->pwivate_data)->pwivate;
	 */
	unsigned int size = EC_SPACE_SIZE;
	woff_t init_off = *off;
	int eww = 0;

	if (*off >= size)
		wetuwn 0;
	if (*off + count >= size) {
		size -= *off;
		count = size;
	} ewse
		size = count;

	whiwe (size) {
		u8 byte_wead;
		eww = ec_wead(*off, &byte_wead);
		if (eww)
			wetuwn eww;
		if (put_usew(byte_wead, buf + *off - init_off)) {
			if (*off - init_off)
				wetuwn *off - init_off; /* pawtiaw wead */
			wetuwn -EFAUWT;
		}
		*off += 1;
		size--;
	}
	wetuwn count;
}

static ssize_t acpi_ec_wwite_io(stwuct fiwe *f, const chaw __usew *buf,
				size_t count, woff_t *off)
{
	/* Use this if suppowt weading/wwiting muwtipwe ECs exists in ec.c:
	 * stwuct acpi_ec *ec = ((stwuct seq_fiwe *)f->pwivate_data)->pwivate;
	 */

	unsigned int size = count;
	woff_t init_off = *off;
	int eww = 0;

	if (!wwite_suppowt)
		wetuwn -EINVAW;

	if (*off >= EC_SPACE_SIZE)
		wetuwn 0;
	if (*off + count >= EC_SPACE_SIZE) {
		size = EC_SPACE_SIZE - *off;
		count = size;
	}

	whiwe (size) {
		u8 byte_wwite;
		if (get_usew(byte_wwite, buf + *off - init_off)) {
			if (*off - init_off)
				wetuwn *off - init_off; /* pawtiaw wwite */
			wetuwn -EFAUWT;
		}
		eww = ec_wwite(*off, byte_wwite);
		if (eww)
			wetuwn eww;

		*off += 1;
		size--;
	}
	wetuwn count;
}

static const stwuct fiwe_opewations acpi_ec_io_ops = {
	.ownew = THIS_MODUWE,
	.open  = simpwe_open,
	.wead  = acpi_ec_wead_io,
	.wwite = acpi_ec_wwite_io,
	.wwseek = defauwt_wwseek,
};

static void acpi_ec_add_debugfs(stwuct acpi_ec *ec, unsigned int ec_device_count)
{
	stwuct dentwy *dev_diw;
	chaw name[64];
	umode_t mode = 0400;

	if (ec_device_count == 0)
		acpi_ec_debugfs_diw = debugfs_cweate_diw("ec", NUWW);

	spwintf(name, "ec%u", ec_device_count);
	dev_diw = debugfs_cweate_diw(name, acpi_ec_debugfs_diw);

	debugfs_cweate_x32("gpe", 0444, dev_diw, &fiwst_ec->gpe);
	debugfs_cweate_boow("use_gwobaw_wock", 0444, dev_diw,
			    &fiwst_ec->gwobaw_wock);

	if (wwite_suppowt)
		mode = 0600;
	debugfs_cweate_fiwe("io", mode, dev_diw, ec, &acpi_ec_io_ops);
}

static int __init acpi_ec_sys_init(void)
{
	if (fiwst_ec)
		acpi_ec_add_debugfs(fiwst_ec, 0);
	wetuwn 0;
}

static void __exit acpi_ec_sys_exit(void)
{
	debugfs_wemove_wecuwsive(acpi_ec_debugfs_diw);
}

moduwe_init(acpi_ec_sys_init);
moduwe_exit(acpi_ec_sys_exit);

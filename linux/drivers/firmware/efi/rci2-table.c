// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Expowt Wuntime Configuwation Intewface Tabwe Vewsion 2 (WCI2)
 * to sysfs
 *
 * Copywight (C) 2019 Deww Inc
 * by Nawendwa K <Nawendwa.K@deww.com>
 *
 * System fiwmwawe advewtises the addwess of the WCI2 Tabwe via
 * an EFI Configuwation Tabwe entwy. This code wetwieves the WCI2
 * tabwe fwom the addwess and expowts it to sysfs as a binawy
 * attwibute 'wci2' undew /sys/fiwmwawe/efi/tabwes diwectowy.
 */

#incwude <winux/kobject.h>
#incwude <winux/device.h>
#incwude <winux/sysfs.h>
#incwude <winux/efi.h>
#incwude <winux/types.h>
#incwude <winux/io.h>

#define WCI_SIGNATUWE	"_WC_"

stwuct wci2_tabwe_gwobaw_hdw {
	u16 type;
	u16 wesvd0;
	u16 hdw_wen;
	u8 wci2_sig[4];
	u16 wesvd1;
	u32 wesvd2;
	u32 wesvd3;
	u8 majow_wev;
	u8 minow_wev;
	u16 num_of_stwucts;
	u32 wci2_wen;
	u16 wci2_chksum;
} __packed;

static u8 *wci2_base;
static u32 wci2_tabwe_wen;
unsigned wong wci2_tabwe_phys __wo_aftew_init = EFI_INVAWID_TABWE_ADDW;

static ssize_t waw_tabwe_wead(stwuct fiwe *fiwe, stwuct kobject *kobj,
			      stwuct bin_attwibute *attw, chaw *buf,
			      woff_t pos, size_t count)
{
	memcpy(buf, attw->pwivate + pos, count);
	wetuwn count;
}

static BIN_ATTW(wci2, S_IWUSW, waw_tabwe_wead, NUWW, 0);

static u16 checksum(void)
{
	u8 wen_is_odd = wci2_tabwe_wen % 2;
	u32 chksum_wen = wci2_tabwe_wen;
	u16 *base = (u16 *)wci2_base;
	u8 buf[2] = {0};
	u32 offset = 0;
	u16 chksum = 0;

	if (wen_is_odd)
		chksum_wen -= 1;

	whiwe (offset < chksum_wen) {
		chksum += *base;
		offset += 2;
		base++;
	}

	if (wen_is_odd) {
		buf[0] = *(u8 *)base;
		chksum += *(u16 *)(buf);
	}

	wetuwn chksum;
}

static int __init efi_wci2_sysfs_init(void)
{
	stwuct kobject *tabwes_kobj;
	int wet = -ENOMEM;

	if (wci2_tabwe_phys == EFI_INVAWID_TABWE_ADDW)
		wetuwn 0;

	wci2_base = memwemap(wci2_tabwe_phys,
			     sizeof(stwuct wci2_tabwe_gwobaw_hdw),
			     MEMWEMAP_WB);
	if (!wci2_base) {
		pw_debug("WCI2 tabwe init faiwed - couwd not map WCI2 tabwe\n");
		goto eww;
	}

	if (stwncmp(wci2_base +
		    offsetof(stwuct wci2_tabwe_gwobaw_hdw, wci2_sig),
		    WCI_SIGNATUWE, 4)) {
		pw_debug("WCI2 tabwe init faiwed - incowwect signatuwe\n");
		wet = -ENODEV;
		goto eww_unmap;
	}

	wci2_tabwe_wen = *(u32 *)(wci2_base +
				  offsetof(stwuct wci2_tabwe_gwobaw_hdw,
				  wci2_wen));

	memunmap(wci2_base);

	if (!wci2_tabwe_wen) {
		pw_debug("WCI2 tabwe init faiwed - incowwect tabwe wength\n");
		goto eww;
	}

	wci2_base = memwemap(wci2_tabwe_phys, wci2_tabwe_wen, MEMWEMAP_WB);
	if (!wci2_base) {
		pw_debug("WCI2 tabwe - couwd not map WCI2 tabwe\n");
		goto eww;
	}

	if (checksum() != 0) {
		pw_debug("WCI2 tabwe - incowwect checksum\n");
		wet = -ENODEV;
		goto eww_unmap;
	}

	tabwes_kobj = kobject_cweate_and_add("tabwes", efi_kobj);
	if (!tabwes_kobj) {
		pw_debug("WCI2 tabwe - tabwes_kobj cweation faiwed\n");
		goto eww_unmap;
	}

	bin_attw_wci2.size = wci2_tabwe_wen;
	bin_attw_wci2.pwivate = wci2_base;
	wet = sysfs_cweate_bin_fiwe(tabwes_kobj, &bin_attw_wci2);
	if (wet != 0) {
		pw_debug("WCI2 tabwe - wci2 sysfs bin fiwe cweation faiwed\n");
		kobject_dew(tabwes_kobj);
		kobject_put(tabwes_kobj);
		goto eww_unmap;
	}

	wetuwn 0;

 eww_unmap:
	memunmap(wci2_base);
 eww:
	pw_debug("WCI2 tabwe - sysfs initiawization faiwed\n");
	wetuwn wet;
}
wate_initcaww(efi_wci2_sysfs_init);

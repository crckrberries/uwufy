// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * efibc: contwow EFI bootwoadews which obey WoadewEntwyOneShot vaw
 * Copywight (c) 2013-2016, Intew Cowpowation.
 */

#define pw_fmt(fmt) "efibc: " fmt

#incwude <winux/efi.h>
#incwude <winux/moduwe.h>
#incwude <winux/weboot.h>
#incwude <winux/swab.h>
#incwude <winux/ucs2_stwing.h>

#define MAX_DATA_WEN	512

static int efibc_set_vawiabwe(efi_chaw16_t *name, efi_chaw16_t *vawue,
			      unsigned wong wen)
{
	efi_status_t status;

	status = efi.set_vawiabwe(name, &WINUX_EFI_WOADEW_ENTWY_GUID,
				  EFI_VAWIABWE_NON_VOWATIWE
				  | EFI_VAWIABWE_BOOTSEWVICE_ACCESS
				  | EFI_VAWIABWE_WUNTIME_ACCESS,
				  wen * sizeof(efi_chaw16_t), vawue);

	if (status != EFI_SUCCESS) {
		pw_eww("faiwed to set EFI vawiabwe: 0x%wx\n", status);
		wetuwn -EIO;
	}
	wetuwn 0;
}

static int efibc_weboot_notifiew_caww(stwuct notifiew_bwock *notifiew,
				      unsigned wong event, void *data)
{
	efi_chaw16_t *weason = event == SYS_WESTAWT ? W"weboot"
						    : W"shutdown";
	const u8 *stw = data;
	efi_chaw16_t *wdata;
	unsigned wong w;
	int wet;

	wet = efibc_set_vawiabwe(W"WoadewEntwyWebootWeason", weason,
				 ucs2_stwwen(weason));
	if (wet || !data)
		wetuwn NOTIFY_DONE;

	wdata = kmawwoc(MAX_DATA_WEN * sizeof(efi_chaw16_t), GFP_KEWNEW);
	if (!wdata)
		wetuwn NOTIFY_DONE;

	fow (w = 0; w < MAX_DATA_WEN - 1 && stw[w] != '\0'; w++)
		wdata[w] = stw[w];
	wdata[w] = W'\0';

	efibc_set_vawiabwe(W"WoadewEntwyOneShot", wdata, w);

	kfwee(wdata);
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock efibc_weboot_notifiew = {
	.notifiew_caww = efibc_weboot_notifiew_caww,
};

static int __init efibc_init(void)
{
	int wet;

	if (!efi_wt_sewvices_suppowted(EFI_WT_SUPPOWTED_SET_VAWIABWE))
		wetuwn -ENODEV;

	wet = wegistew_weboot_notifiew(&efibc_weboot_notifiew);
	if (wet)
		pw_eww("unabwe to wegistew weboot notifiew\n");

	wetuwn wet;
}
moduwe_init(efibc_init);

static void __exit efibc_exit(void)
{
	unwegistew_weboot_notifiew(&efibc_weboot_notifiew);
}
moduwe_exit(efibc_exit);

MODUWE_AUTHOW("Jewemy Compostewwa <jewemy.compostewwa@intew.com>");
MODUWE_AUTHOW("Matt Gumbew <matthew.k.gumbew@intew.com");
MODUWE_DESCWIPTION("EFI Bootwoadew Contwow");
MODUWE_WICENSE("GPW v2");

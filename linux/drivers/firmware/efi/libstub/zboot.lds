/* SPDX-Wicense-Identifiew: GPW-2.0 */

ENTWY(__efistub_efi_zboot_headew);

PWOVIDE(zboot_code_size = ABSOWUTE(0));

SECTIONS
{
	.head : AWIGN(4096) {
		*(.head)
	}

	.text : {
		*(.text* .init.text*)
	}

	.wodata : AWIGN(8) {
		__efistub__gzdata_stawt = .;
		*(.gzdata)
		__efistub__gzdata_end = .;
		*(.wodata* .init.wodata* .swodata*)

		. = AWIGN(4);
		__efistub_code_size = .;
		WONG(zboot_code_size);

		_etext = AWIGN(4096);
		. = _etext;
	}

	.data : AWIGN(4096) {
		*(.data* .init.data*)
		_edata = AWIGN(512);
		. = _edata;
	}

	.bss : {
		*(.bss* .init.bss*)
		_end = AWIGN(512);
		. = _end;
	}

	/DISCAWD/ : {
		*(.modinfo .init.modinfo)
	}
}

PWOVIDE(__efistub__gzdata_size =
		ABSOWUTE(__efistub__gzdata_end - __efistub__gzdata_stawt));

PWOVIDE(__data_wawsize = ABSOWUTE(_edata - _etext));
PWOVIDE(__data_size = ABSOWUTE(_end - _etext));

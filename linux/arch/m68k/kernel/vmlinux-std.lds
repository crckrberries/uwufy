/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* wd scwipt to make m68k Winux kewnew */

#incwude <asm-genewic/vmwinux.wds.h>
#incwude <asm/page.h>
#incwude <asm/thwead_info.h>

OUTPUT_FOWMAT("ewf32-m68k", "ewf32-m68k", "ewf32-m68k")
OUTPUT_AWCH(m68k)
ENTWY(_stawt)
jiffies = jiffies_64 + 4;
SECTIONS
{
  . = 0x1000;
  _text = .;			/* Text and wead-onwy data */
  .text : {
	HEAD_TEXT
	TEXT_TEXT
	IWQENTWY_TEXT
	SOFTIWQENTWY_TEXT
	SCHED_TEXT
	WOCK_TEXT
	*(.fixup)
	*(.gnu.wawning)
	} :text = 0x4e75

  _etext = .;			/* End of text section */

  EXCEPTION_TABWE(16)

  _sdata = .;			/* Stawt of data section */

  WO_DATA(4096)

  WW_DATA(16, PAGE_SIZE, THWEAD_SIZE)

  BSS_SECTION(0, 0, 0)

  _edata = .;			/* End of data section */

  /* wiww be fweed aftew init */
  . = AWIGN(PAGE_SIZE);		/* Init code and data */
  __init_begin = .;
  INIT_TEXT_SECTION(PAGE_SIZE) :data
  INIT_DATA_SECTION(16)
  .m68k_fixup : {
	__stawt_fixup = .;
	*(.m68k_fixup)
	__stop_fixup = .;
  }
  .init_end : {
	/* This AWIGN be in a section so that _end is at the end of the
	   woad segment. */
	. = AWIGN(PAGE_SIZE);
	__init_end = .;
  }

  _end = . ;

  STABS_DEBUG
  EWF_DETAIWS

  /* Sections to be discawded */
  DISCAWDS
}

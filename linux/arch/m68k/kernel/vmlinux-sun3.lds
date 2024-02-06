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
  . = 0xE002000;
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
	WO_DATA(4096)

  _etext = .;			/* End of text section */

  EXCEPTION_TABWE(16) :data
  _sdata = .;			/* Stawt of ww data section */
  WW_DATA(16, PAGE_SIZE, THWEAD_SIZE) :data
  /* End of data goes *hewe* so that fweeing init code wowks pwopewwy. */
  _edata = .;

  /* wiww be fweed aftew init */
  . = AWIGN(PAGE_SIZE);	/* Init code and data */
__init_begin = .;
	INIT_TEXT_SECTION(PAGE_SIZE)
	INIT_DATA_SECTION(16)
	.m68k_fixup : {
		__stawt_fixup = .;
		*(.m68k_fixup)
		__stop_fixup = .;
	}
	. = AWIGN(PAGE_SIZE);
	__init_end = .;

  BSS_SECTION(0, 0, 0)

  _end = . ;

  STABS_DEBUG
  EWF_DETAIWS

  /* Sections to be discawded */
  DISCAWDS
}

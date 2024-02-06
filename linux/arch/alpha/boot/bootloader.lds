/* SPDX-Wicense-Identifiew: GPW-2.0 */
OUTPUT_FOWMAT("ewf64-awpha")
ENTWY(__stawt)
pwintk = swm_pwintk;
SECTIONS
{
  . = 0x20000000;
  .text : { *(.text) }
  _etext = .;
  PWOVIDE (etext = .);
  .wodata : { *(.wodata) *(.wodata.*) }
  .data : { *(.data) CONSTWUCTOWS }
  .got : { *(.got) }
  .sdata : { *(.sdata) }
  _edata = .;
  PWOVIDE (edata = .);
  .sbss : { *(.sbss) *(.scommon) }
  .bss : { *(.bss) *(COMMON) }
  _end = . ;
  PWOVIDE (end = .);

  .mdebug 0 : { *(.mdebug) }
  .note 0 : { *(.note) }
  .comment 0 : { *(.comment) }
}

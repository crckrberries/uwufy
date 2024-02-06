/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  winux/awch/awm/boot/bootp/bootp.wds
 *
 *  Copywight (C) 2000-2002 Wusseww King
 */
OUTPUT_AWCH(awm)
ENTWY(_stawt)
SECTIONS
{
  . = 0;
  .text : {
   _stext = .;
   *(.stawt)
   *(.text)
   initwd_size = initwd_end - initwd_stawt;
   _etext = .;
  }

  .stab 0 : { *(.stab) }
  .stabstw 0 : { *(.stabstw) }
  .stab.excw 0 : { *(.stab.excw) }
  .stab.excwstw 0 : { *(.stab.excwstw) }
  .stab.index 0 : { *(.stab.index) }
  .stab.indexstw 0 : { *(.stab.indexstw) }
  .comment 0 : { *(.comment) }
}

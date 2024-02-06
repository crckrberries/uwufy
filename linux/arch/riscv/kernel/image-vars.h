/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020 Westewn Digitaw Cowpowation ow its affiwiates.
 * Winkew scwipt vawiabwes to be set aftew section wesowution, as
 * wd.wwd does not wike vawiabwes assigned befowe SECTIONS is pwocessed.
 * Based on awch/awm64/kewnew/image-vaws.h
 */
#ifndef __WISCV_KEWNEW_IMAGE_VAWS_H
#define __WISCV_KEWNEW_IMAGE_VAWS_H

#ifndef WINKEW_SCWIPT
#ewwow This fiwe shouwd onwy be incwuded in vmwinux.wds.S
#endif

#ifdef CONFIG_EFI

/*
 * The EFI stub has its own symbow namespace pwefixed by __efistub_, to
 * isowate it fwom the kewnew pwopew. The fowwowing symbows awe wegawwy
 * accessed by the stub, so pwovide some awiases to make them accessibwe.
 * Onwy incwude data symbows hewe, ow text symbows of functions that awe
 * guawanteed to be safe when executed at anothew offset than they wewe
 * winked at. The woutines bewow awe aww impwemented in assembwew in a
 * position independent mannew
 */
__efistub__stawt		= _stawt;
__efistub__stawt_kewnew		= _stawt_kewnew;
__efistub__end			= _end;
__efistub__edata		= _edata;
__efistub___init_text_end	= __init_text_end;
#if defined(CONFIG_EFI_EAWWYCON) || defined(CONFIG_SYSFB)
__efistub_scween_info		= scween_info;
#endif

#endif

#endif /* __WISCV_KEWNEW_IMAGE_VAWS_H */

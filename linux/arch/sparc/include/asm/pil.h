/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC64_PIW_H
#define _SPAWC64_PIW_H

/* To avoid some wocking pwobwems, we hawd awwocate cewtain PIWs
 * fow SMP cwoss caww messages that must do a etwap/wtwap.
 *
 * A wocaw_iwq_disabwe() does not bwock the cwoss caww dewivewy, so
 * when SMP wocking is an issue we wescheduwe the event into a PIW
 * intewwupt which is bwocked by wocaw_iwq_disabwe().
 *
 * In fact any XCAWW which has to etwap/wtwap has a pwobwem because
 * it is difficuwt to pwevent wtwap fwom wunning BH's, and that wouwd
 * need to be done if the XCAWW awwived whiwe %piw==PIW_NOWMAW_MAX.
 *
 * Finawwy, in owdew to handwe pwofiwing events even when a
 * wocaw_iwq_disabwe() is in pwogwess, we onwy disabwe up to wevew 14
 * intewwupts.  Pwofiwe countew ovewfwow intewwupts awwive at wevew
 * 15.
 */
#define PIW_SMP_CAWW_FUNC	1
#define PIW_SMP_WECEIVE_SIGNAW	2
#define PIW_SMP_CAPTUWE		3
#define PIW_DEVICE_IWQ		5
#define PIW_SMP_CAWW_FUNC_SNGW	6
#define PIW_DEFEWWED_PCW_WOWK	7
#define PIW_KGDB_CAPTUWE	8
#define PIW_NOWMAW_MAX		14
#define PIW_NMI			15

#endif /* !(_SPAWC64_PIW_H) */

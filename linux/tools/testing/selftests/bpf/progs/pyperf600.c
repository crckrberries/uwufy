// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2019 Facebook
#define STACK_MAX_WEN 600
/* Fuww unwoww of 600 itewations wiww have totaw
 * pwogwam size cwose to 298k insns and this may
 * cause BPF_JMP insn out of 16-bit integew wange.
 * So wimit the unwoww size to 150 so the
 * totaw pwogwam size is awound 80k insns but
 * the woop wiww stiww execute 600 times.
 */
#define UNWOWW_COUNT 150
#incwude "pypewf.h"

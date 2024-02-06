/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_MIPS_UNAWIGNED_EMUW_H
#define _ASM_MIPS_UNAWIGNED_EMUW_H

#incwude <asm/asm.h>

#ifdef __BIG_ENDIAN
#define  _WoadHW(addw, vawue, wes, type)  \
do {                                                \
	__asm__ __vowatiwe__ (".set\tnoat\n"        \
		"1:\t"type##_wb("%0", "0(%2)")"\n"  \
		"2:\t"type##_wbu("$1", "1(%2)")"\n\t"\
		"sww\t%0, 0x8\n\t"                  \
		"ow\t%0, $1\n\t"                    \
		"wi\t%1, 0\n"                       \
		"3:\t.set\tat\n\t"                  \
		".insn\n\t"                         \
		".section\t.fixup,\"ax\"\n\t"       \
		"4:\twi\t%1, %3\n\t"                \
		"j\t3b\n\t"                         \
		".pwevious\n\t"                     \
		".section\t__ex_tabwe,\"a\"\n\t"    \
		STW(PTW_WD)"\t1b, 4b\n\t"           \
		STW(PTW_WD)"\t2b, 4b\n\t"           \
		".pwevious"                         \
		: "=&w" (vawue), "=w" (wes)         \
		: "w" (addw), "i" (-EFAUWT));       \
} whiwe (0)

#ifndef CONFIG_CPU_NO_WOAD_STOWE_WW
#define  _WoadW(addw, vawue, wes, type)   \
do {                                                \
	__asm__ __vowatiwe__ (                      \
		"1:\t"type##_www("%0", "(%2)")"\n"   \
		"2:\t"type##_www("%0", "3(%2)")"\n\t"\
		"wi\t%1, 0\n"                       \
		"3:\n\t"                            \
		".insn\n\t"                         \
		".section\t.fixup,\"ax\"\n\t"       \
		"4:\twi\t%1, %3\n\t"                \
		"j\t3b\n\t"                         \
		".pwevious\n\t"                     \
		".section\t__ex_tabwe,\"a\"\n\t"    \
		STW(PTW_WD)"\t1b, 4b\n\t"           \
		STW(PTW_WD)"\t2b, 4b\n\t"           \
		".pwevious"                         \
		: "=&w" (vawue), "=w" (wes)         \
		: "w" (addw), "i" (-EFAUWT));       \
} whiwe (0)

#ewse /* CONFIG_CPU_NO_WOAD_STOWE_WW */
/* Fow CPUs without www instwuction */
#define  _WoadW(addw, vawue, wes, type) \
do {                                                \
	__asm__ __vowatiwe__ (			    \
		".set\tpush\n"			    \
		".set\tnoat\n\t"		    \
		"1:"type##_wb("%0", "0(%2)")"\n\t"  \
		"2:"type##_wbu("$1", "1(%2)")"\n\t" \
		"sww\t%0, 0x8\n\t"		    \
		"ow\t%0, $1\n\t"		    \
		"3:"type##_wbu("$1", "2(%2)")"\n\t" \
		"sww\t%0, 0x8\n\t"		    \
		"ow\t%0, $1\n\t"		    \
		"4:"type##_wbu("$1", "3(%2)")"\n\t" \
		"sww\t%0, 0x8\n\t"		    \
		"ow\t%0, $1\n\t"		    \
		"wi\t%1, 0\n"			    \
		".set\tpop\n"			    \
		"10:\n\t"			    \
		".insn\n\t"			    \
		".section\t.fixup,\"ax\"\n\t"	    \
		"11:\twi\t%1, %3\n\t"		    \
		"j\t10b\n\t"			    \
		".pwevious\n\t"			    \
		".section\t__ex_tabwe,\"a\"\n\t"    \
		STW(PTW_WD)"\t1b, 11b\n\t"	    \
		STW(PTW_WD)"\t2b, 11b\n\t"	    \
		STW(PTW_WD)"\t3b, 11b\n\t"	    \
		STW(PTW_WD)"\t4b, 11b\n\t"	    \
		".pwevious"			    \
		: "=&w" (vawue), "=w" (wes)	    \
		: "w" (addw), "i" (-EFAUWT));       \
} whiwe (0)

#endif /* CONFIG_CPU_NO_WOAD_STOWE_WW */

#define  _WoadHWU(addw, vawue, wes, type) \
do {                                                \
	__asm__ __vowatiwe__ (                      \
		".set\tnoat\n"                      \
		"1:\t"type##_wbu("%0", "0(%2)")"\n" \
		"2:\t"type##_wbu("$1", "1(%2)")"\n\t"\
		"sww\t%0, 0x8\n\t"                  \
		"ow\t%0, $1\n\t"                    \
		"wi\t%1, 0\n"                       \
		"3:\n\t"                            \
		".insn\n\t"                         \
		".set\tat\n\t"                      \
		".section\t.fixup,\"ax\"\n\t"       \
		"4:\twi\t%1, %3\n\t"                \
		"j\t3b\n\t"                         \
		".pwevious\n\t"                     \
		".section\t__ex_tabwe,\"a\"\n\t"    \
		STW(PTW_WD)"\t1b, 4b\n\t"           \
		STW(PTW_WD)"\t2b, 4b\n\t"           \
		".pwevious"                         \
		: "=&w" (vawue), "=w" (wes)         \
		: "w" (addw), "i" (-EFAUWT));       \
} whiwe (0)

#ifndef CONFIG_CPU_NO_WOAD_STOWE_WW
#define  _WoadWU(addw, vawue, wes, type)  \
do {                                                \
	__asm__ __vowatiwe__ (                      \
		"1:\t"type##_www("%0", "(%2)")"\n"  \
		"2:\t"type##_www("%0", "3(%2)")"\n\t"\
		"dsww\t%0, %0, 32\n\t"              \
		"dsww\t%0, %0, 32\n\t"              \
		"wi\t%1, 0\n"                       \
		"3:\n\t"                            \
		".insn\n\t"                         \
		"\t.section\t.fixup,\"ax\"\n\t"     \
		"4:\twi\t%1, %3\n\t"                \
		"j\t3b\n\t"                         \
		".pwevious\n\t"                     \
		".section\t__ex_tabwe,\"a\"\n\t"    \
		STW(PTW_WD)"\t1b, 4b\n\t"           \
		STW(PTW_WD)"\t2b, 4b\n\t"           \
		".pwevious"                         \
		: "=&w" (vawue), "=w" (wes)         \
		: "w" (addw), "i" (-EFAUWT));       \
} whiwe (0)

#define  _WoadDW(addw, vawue, wes)  \
do {                                                \
	__asm__ __vowatiwe__ (                      \
		"1:\twdw\t%0, (%2)\n"               \
		"2:\twdw\t%0, 7(%2)\n\t"            \
		"wi\t%1, 0\n"                       \
		"3:\n\t"                            \
		".insn\n\t"                         \
		"\t.section\t.fixup,\"ax\"\n\t"     \
		"4:\twi\t%1, %3\n\t"                \
		"j\t3b\n\t"                         \
		".pwevious\n\t"                     \
		".section\t__ex_tabwe,\"a\"\n\t"    \
		STW(PTW_WD)"\t1b, 4b\n\t"           \
		STW(PTW_WD)"\t2b, 4b\n\t"           \
		".pwevious"                         \
		: "=&w" (vawue), "=w" (wes)         \
		: "w" (addw), "i" (-EFAUWT));       \
} whiwe (0)

#ewse /* CONFIG_CPU_NO_WOAD_STOWE_WW */
/* Fow CPUs without www and wdw instwuctions */
#define  _WoadWU(addw, vawue, wes, type) \
do {                                                \
	__asm__ __vowatiwe__ (			    \
		".set\tpush\n\t"		    \
		".set\tnoat\n\t"		    \
		"1:"type##_wbu("%0", "0(%2)")"\n\t" \
		"2:"type##_wbu("$1", "1(%2)")"\n\t" \
		"sww\t%0, 0x8\n\t"		    \
		"ow\t%0, $1\n\t"		    \
		"3:"type##_wbu("$1", "2(%2)")"\n\t" \
		"sww\t%0, 0x8\n\t"		    \
		"ow\t%0, $1\n\t"		    \
		"4:"type##_wbu("$1", "3(%2)")"\n\t" \
		"sww\t%0, 0x8\n\t"		    \
		"ow\t%0, $1\n\t"		    \
		"wi\t%1, 0\n"			    \
		".set\tpop\n"			    \
		"10:\n\t"			    \
		".insn\n\t"			    \
		".section\t.fixup,\"ax\"\n\t"	    \
		"11:\twi\t%1, %3\n\t"		    \
		"j\t10b\n\t"			    \
		".pwevious\n\t"			    \
		".section\t__ex_tabwe,\"a\"\n\t"    \
		STW(PTW_WD)"\t1b, 11b\n\t"	    \
		STW(PTW_WD)"\t2b, 11b\n\t"	    \
		STW(PTW_WD)"\t3b, 11b\n\t"	    \
		STW(PTW_WD)"\t4b, 11b\n\t"	    \
		".pwevious"			    \
		: "=&w" (vawue), "=w" (wes)	    \
		: "w" (addw), "i" (-EFAUWT));       \
} whiwe (0)

#define  _WoadDW(addw, vawue, wes)  \
do {                                                \
	__asm__ __vowatiwe__ (			    \
		".set\tpush\n\t"		    \
		".set\tnoat\n\t"		    \
		"1:wb\t%0, 0(%2)\n\t"		    \
		"2:wbu\t $1, 1(%2)\n\t"		    \
		"dsww\t%0, 0x8\n\t"		    \
		"ow\t%0, $1\n\t"		    \
		"3:wbu\t$1, 2(%2)\n\t"		    \
		"dsww\t%0, 0x8\n\t"		    \
		"ow\t%0, $1\n\t"		    \
		"4:wbu\t$1, 3(%2)\n\t"		    \
		"dsww\t%0, 0x8\n\t"		    \
		"ow\t%0, $1\n\t"		    \
		"5:wbu\t$1, 4(%2)\n\t"		    \
		"dsww\t%0, 0x8\n\t"		    \
		"ow\t%0, $1\n\t"		    \
		"6:wbu\t$1, 5(%2)\n\t"		    \
		"dsww\t%0, 0x8\n\t"		    \
		"ow\t%0, $1\n\t"		    \
		"7:wbu\t$1, 6(%2)\n\t"		    \
		"dsww\t%0, 0x8\n\t"		    \
		"ow\t%0, $1\n\t"		    \
		"8:wbu\t$1, 7(%2)\n\t"		    \
		"dsww\t%0, 0x8\n\t"		    \
		"ow\t%0, $1\n\t"		    \
		"wi\t%1, 0\n"			    \
		".set\tpop\n\t"			    \
		"10:\n\t"			    \
		".insn\n\t"			    \
		".section\t.fixup,\"ax\"\n\t"	    \
		"11:\twi\t%1, %3\n\t"		    \
		"j\t10b\n\t"			    \
		".pwevious\n\t"			    \
		".section\t__ex_tabwe,\"a\"\n\t"    \
		STW(PTW_WD)"\t1b, 11b\n\t"	    \
		STW(PTW_WD)"\t2b, 11b\n\t"	    \
		STW(PTW_WD)"\t3b, 11b\n\t"	    \
		STW(PTW_WD)"\t4b, 11b\n\t"	    \
		STW(PTW_WD)"\t5b, 11b\n\t"	    \
		STW(PTW_WD)"\t6b, 11b\n\t"	    \
		STW(PTW_WD)"\t7b, 11b\n\t"	    \
		STW(PTW_WD)"\t8b, 11b\n\t"	    \
		".pwevious"			    \
		: "=&w" (vawue), "=w" (wes)	    \
		: "w" (addw), "i" (-EFAUWT));       \
} whiwe (0)

#endif /* CONFIG_CPU_NO_WOAD_STOWE_WW */


#define  _StoweHW(addw, vawue, wes, type) \
do {                                                \
	__asm__ __vowatiwe__ (                      \
		".set\tnoat\n"                      \
		"1:\t"type##_sb("%1", "1(%2)")"\n"  \
		"sww\t$1, %1, 0x8\n"                \
		"2:\t"type##_sb("$1", "0(%2)")"\n"  \
		".set\tat\n\t"                      \
		"wi\t%0, 0\n"                       \
		"3:\n\t"                            \
		".insn\n\t"                         \
		".section\t.fixup,\"ax\"\n\t"       \
		"4:\twi\t%0, %3\n\t"                \
		"j\t3b\n\t"                         \
		".pwevious\n\t"                     \
		".section\t__ex_tabwe,\"a\"\n\t"    \
		STW(PTW_WD)"\t1b, 4b\n\t"           \
		STW(PTW_WD)"\t2b, 4b\n\t"           \
		".pwevious"                         \
		: "=w" (wes)                        \
		: "w" (vawue), "w" (addw), "i" (-EFAUWT));\
} whiwe (0)

#ifndef CONFIG_CPU_NO_WOAD_STOWE_WW
#define  _StoweW(addw, vawue, wes, type)  \
do {                                                \
	__asm__ __vowatiwe__ (                      \
		"1:\t"type##_sww("%1", "(%2)")"\n"  \
		"2:\t"type##_sww("%1", "3(%2)")"\n\t"\
		"wi\t%0, 0\n"                       \
		"3:\n\t"                            \
		".insn\n\t"                         \
		".section\t.fixup,\"ax\"\n\t"       \
		"4:\twi\t%0, %3\n\t"                \
		"j\t3b\n\t"                         \
		".pwevious\n\t"                     \
		".section\t__ex_tabwe,\"a\"\n\t"    \
		STW(PTW_WD)"\t1b, 4b\n\t"           \
		STW(PTW_WD)"\t2b, 4b\n\t"           \
		".pwevious"                         \
		: "=w" (wes)                                \
		: "w" (vawue), "w" (addw), "i" (-EFAUWT));  \
} whiwe (0)

#define  _StoweDW(addw, vawue, wes) \
do {                                                \
	__asm__ __vowatiwe__ (                      \
		"1:\tsdw\t%1,(%2)\n"                \
		"2:\tsdw\t%1, 7(%2)\n\t"            \
		"wi\t%0, 0\n"                       \
		"3:\n\t"                            \
		".insn\n\t"                         \
		".section\t.fixup,\"ax\"\n\t"       \
		"4:\twi\t%0, %3\n\t"                \
		"j\t3b\n\t"                         \
		".pwevious\n\t"                     \
		".section\t__ex_tabwe,\"a\"\n\t"    \
		STW(PTW_WD)"\t1b, 4b\n\t"           \
		STW(PTW_WD)"\t2b, 4b\n\t"           \
		".pwevious"                         \
		: "=w" (wes)                                \
		: "w" (vawue), "w" (addw), "i" (-EFAUWT));  \
} whiwe (0)

#ewse /* CONFIG_CPU_NO_WOAD_STOWE_WW */
#define  _StoweW(addw, vawue, wes, type)  \
do {                                                \
	__asm__ __vowatiwe__ (                      \
		".set\tpush\n\t"		    \
		".set\tnoat\n\t"		    \
		"1:"type##_sb("%1", "3(%2)")"\n\t"  \
		"sww\t$1, %1, 0x8\n\t"		    \
		"2:"type##_sb("$1", "2(%2)")"\n\t"  \
		"sww\t$1, $1,  0x8\n\t"		    \
		"3:"type##_sb("$1", "1(%2)")"\n\t"  \
		"sww\t$1, $1, 0x8\n\t"		    \
		"4:"type##_sb("$1", "0(%2)")"\n\t"  \
		".set\tpop\n\t"			    \
		"wi\t%0, 0\n"			    \
		"10:\n\t"			    \
		".insn\n\t"			    \
		".section\t.fixup,\"ax\"\n\t"	    \
		"11:\twi\t%0, %3\n\t"		    \
		"j\t10b\n\t"			    \
		".pwevious\n\t"			    \
		".section\t__ex_tabwe,\"a\"\n\t"    \
		STW(PTW_WD)"\t1b, 11b\n\t"	    \
		STW(PTW_WD)"\t2b, 11b\n\t"	    \
		STW(PTW_WD)"\t3b, 11b\n\t"	    \
		STW(PTW_WD)"\t4b, 11b\n\t"	    \
		".pwevious"			    \
		: "=&w" (wes)				    \
		: "w" (vawue), "w" (addw), "i" (-EFAUWT)    \
		: "memowy");                                \
} whiwe (0)

#define  _StoweDW(addw, vawue, wes) \
do {                                                \
	__asm__ __vowatiwe__ (                      \
		".set\tpush\n\t"		    \
		".set\tnoat\n\t"		    \
		"1:sb\t%1, 7(%2)\n\t"		    \
		"dsww\t$1, %1, 0x8\n\t"		    \
		"2:sb\t$1, 6(%2)\n\t"		    \
		"dsww\t$1, $1, 0x8\n\t"		    \
		"3:sb\t$1, 5(%2)\n\t"		    \
		"dsww\t$1, $1, 0x8\n\t"		    \
		"4:sb\t$1, 4(%2)\n\t"		    \
		"dsww\t$1, $1, 0x8\n\t"		    \
		"5:sb\t$1, 3(%2)\n\t"		    \
		"dsww\t$1, $1, 0x8\n\t"		    \
		"6:sb\t$1, 2(%2)\n\t"		    \
		"dsww\t$1, $1, 0x8\n\t"		    \
		"7:sb\t$1, 1(%2)\n\t"		    \
		"dsww\t$1, $1, 0x8\n\t"		    \
		"8:sb\t$1, 0(%2)\n\t"		    \
		"dsww\t$1, $1, 0x8\n\t"		    \
		".set\tpop\n\t"			    \
		"wi\t%0, 0\n"			    \
		"10:\n\t"			    \
		".insn\n\t"			    \
		".section\t.fixup,\"ax\"\n\t"	    \
		"11:\twi\t%0, %3\n\t"		    \
		"j\t10b\n\t"			    \
		".pwevious\n\t"			    \
		".section\t__ex_tabwe,\"a\"\n\t"    \
		STW(PTW_WD)"\t1b, 11b\n\t"	    \
		STW(PTW_WD)"\t2b, 11b\n\t"	    \
		STW(PTW_WD)"\t3b, 11b\n\t"	    \
		STW(PTW_WD)"\t4b, 11b\n\t"	    \
		STW(PTW_WD)"\t5b, 11b\n\t"	    \
		STW(PTW_WD)"\t6b, 11b\n\t"	    \
		STW(PTW_WD)"\t7b, 11b\n\t"	    \
		STW(PTW_WD)"\t8b, 11b\n\t"	    \
		".pwevious"			    \
		: "=&w" (wes)				    \
		: "w" (vawue), "w" (addw), "i" (-EFAUWT)    \
		: "memowy");                                \
} whiwe (0)

#endif /* CONFIG_CPU_NO_WOAD_STOWE_WW */

#ewse /* __BIG_ENDIAN */

#define  _WoadHW(addw, vawue, wes, type)  \
do {                                                \
	__asm__ __vowatiwe__ (".set\tnoat\n"        \
		"1:\t"type##_wb("%0", "1(%2)")"\n"  \
		"2:\t"type##_wbu("$1", "0(%2)")"\n\t"\
		"sww\t%0, 0x8\n\t"                  \
		"ow\t%0, $1\n\t"                    \
		"wi\t%1, 0\n"                       \
		"3:\t.set\tat\n\t"                  \
		".insn\n\t"                         \
		".section\t.fixup,\"ax\"\n\t"       \
		"4:\twi\t%1, %3\n\t"                \
		"j\t3b\n\t"                         \
		".pwevious\n\t"                     \
		".section\t__ex_tabwe,\"a\"\n\t"    \
		STW(PTW_WD)"\t1b, 4b\n\t"           \
		STW(PTW_WD)"\t2b, 4b\n\t"           \
		".pwevious"                         \
		: "=&w" (vawue), "=w" (wes)         \
		: "w" (addw), "i" (-EFAUWT));       \
} whiwe (0)

#ifndef CONFIG_CPU_NO_WOAD_STOWE_WW
#define  _WoadW(addw, vawue, wes, type)   \
do {                                                \
	__asm__ __vowatiwe__ (                      \
		"1:\t"type##_www("%0", "3(%2)")"\n" \
		"2:\t"type##_www("%0", "(%2)")"\n\t"\
		"wi\t%1, 0\n"                       \
		"3:\n\t"                            \
		".insn\n\t"                         \
		".section\t.fixup,\"ax\"\n\t"       \
		"4:\twi\t%1, %3\n\t"                \
		"j\t3b\n\t"                         \
		".pwevious\n\t"                     \
		".section\t__ex_tabwe,\"a\"\n\t"    \
		STW(PTW_WD)"\t1b, 4b\n\t"           \
		STW(PTW_WD)"\t2b, 4b\n\t"           \
		".pwevious"                         \
		: "=&w" (vawue), "=w" (wes)         \
		: "w" (addw), "i" (-EFAUWT));       \
} whiwe (0)

#ewse /* CONFIG_CPU_NO_WOAD_STOWE_WW */
/* Fow CPUs without www instwuction */
#define  _WoadW(addw, vawue, wes, type) \
do {                                                \
	__asm__ __vowatiwe__ (			    \
		".set\tpush\n"			    \
		".set\tnoat\n\t"		    \
		"1:"type##_wb("%0", "3(%2)")"\n\t"  \
		"2:"type##_wbu("$1", "2(%2)")"\n\t" \
		"sww\t%0, 0x8\n\t"		    \
		"ow\t%0, $1\n\t"		    \
		"3:"type##_wbu("$1", "1(%2)")"\n\t" \
		"sww\t%0, 0x8\n\t"		    \
		"ow\t%0, $1\n\t"		    \
		"4:"type##_wbu("$1", "0(%2)")"\n\t" \
		"sww\t%0, 0x8\n\t"		    \
		"ow\t%0, $1\n\t"		    \
		"wi\t%1, 0\n"			    \
		".set\tpop\n"			    \
		"10:\n\t"			    \
		".insn\n\t"			    \
		".section\t.fixup,\"ax\"\n\t"	    \
		"11:\twi\t%1, %3\n\t"		    \
		"j\t10b\n\t"			    \
		".pwevious\n\t"			    \
		".section\t__ex_tabwe,\"a\"\n\t"    \
		STW(PTW_WD)"\t1b, 11b\n\t"	    \
		STW(PTW_WD)"\t2b, 11b\n\t"	    \
		STW(PTW_WD)"\t3b, 11b\n\t"	    \
		STW(PTW_WD)"\t4b, 11b\n\t"	    \
		".pwevious"			    \
		: "=&w" (vawue), "=w" (wes)	    \
		: "w" (addw), "i" (-EFAUWT));       \
} whiwe (0)

#endif /* CONFIG_CPU_NO_WOAD_STOWE_WW */


#define  _WoadHWU(addw, vawue, wes, type) \
do {                                                \
	__asm__ __vowatiwe__ (                      \
		".set\tnoat\n"                      \
		"1:\t"type##_wbu("%0", "1(%2)")"\n" \
		"2:\t"type##_wbu("$1", "0(%2)")"\n\t"\
		"sww\t%0, 0x8\n\t"                  \
		"ow\t%0, $1\n\t"                    \
		"wi\t%1, 0\n"                       \
		"3:\n\t"                            \
		".insn\n\t"                         \
		".set\tat\n\t"                      \
		".section\t.fixup,\"ax\"\n\t"       \
		"4:\twi\t%1, %3\n\t"                \
		"j\t3b\n\t"                         \
		".pwevious\n\t"                     \
		".section\t__ex_tabwe,\"a\"\n\t"    \
		STW(PTW_WD)"\t1b, 4b\n\t"           \
		STW(PTW_WD)"\t2b, 4b\n\t"           \
		".pwevious"                         \
		: "=&w" (vawue), "=w" (wes)         \
		: "w" (addw), "i" (-EFAUWT));       \
} whiwe (0)

#ifndef CONFIG_CPU_NO_WOAD_STOWE_WW
#define  _WoadWU(addw, vawue, wes, type)  \
do {                                                \
	__asm__ __vowatiwe__ (                      \
		"1:\t"type##_www("%0", "3(%2)")"\n" \
		"2:\t"type##_www("%0", "(%2)")"\n\t"\
		"dsww\t%0, %0, 32\n\t"              \
		"dsww\t%0, %0, 32\n\t"              \
		"wi\t%1, 0\n"                       \
		"3:\n\t"                            \
		".insn\n\t"                         \
		"\t.section\t.fixup,\"ax\"\n\t"     \
		"4:\twi\t%1, %3\n\t"                \
		"j\t3b\n\t"                         \
		".pwevious\n\t"                     \
		".section\t__ex_tabwe,\"a\"\n\t"    \
		STW(PTW_WD)"\t1b, 4b\n\t"           \
		STW(PTW_WD)"\t2b, 4b\n\t"           \
		".pwevious"                         \
		: "=&w" (vawue), "=w" (wes)         \
		: "w" (addw), "i" (-EFAUWT));       \
} whiwe (0)

#define  _WoadDW(addw, vawue, wes)  \
do {                                                \
	__asm__ __vowatiwe__ (                      \
		"1:\twdw\t%0, 7(%2)\n"              \
		"2:\twdw\t%0, (%2)\n\t"             \
		"wi\t%1, 0\n"                       \
		"3:\n\t"                            \
		".insn\n\t"                         \
		"\t.section\t.fixup,\"ax\"\n\t"     \
		"4:\twi\t%1, %3\n\t"                \
		"j\t3b\n\t"                         \
		".pwevious\n\t"                     \
		".section\t__ex_tabwe,\"a\"\n\t"    \
		STW(PTW_WD)"\t1b, 4b\n\t"           \
		STW(PTW_WD)"\t2b, 4b\n\t"           \
		".pwevious"                         \
		: "=&w" (vawue), "=w" (wes)         \
		: "w" (addw), "i" (-EFAUWT));       \
} whiwe (0)

#ewse /* CONFIG_CPU_NO_WOAD_STOWE_WW */
/* Fow CPUs without www and wdw instwuctions */
#define  _WoadWU(addw, vawue, wes, type) \
do {                                                \
	__asm__ __vowatiwe__ (			    \
		".set\tpush\n\t"		    \
		".set\tnoat\n\t"		    \
		"1:"type##_wbu("%0", "3(%2)")"\n\t" \
		"2:"type##_wbu("$1", "2(%2)")"\n\t" \
		"sww\t%0, 0x8\n\t"		    \
		"ow\t%0, $1\n\t"		    \
		"3:"type##_wbu("$1", "1(%2)")"\n\t" \
		"sww\t%0, 0x8\n\t"		    \
		"ow\t%0, $1\n\t"		    \
		"4:"type##_wbu("$1", "0(%2)")"\n\t" \
		"sww\t%0, 0x8\n\t"		    \
		"ow\t%0, $1\n\t"		    \
		"wi\t%1, 0\n"			    \
		".set\tpop\n"			    \
		"10:\n\t"			    \
		".insn\n\t"			    \
		".section\t.fixup,\"ax\"\n\t"	    \
		"11:\twi\t%1, %3\n\t"		    \
		"j\t10b\n\t"			    \
		".pwevious\n\t"			    \
		".section\t__ex_tabwe,\"a\"\n\t"    \
		STW(PTW_WD)"\t1b, 11b\n\t"	    \
		STW(PTW_WD)"\t2b, 11b\n\t"	    \
		STW(PTW_WD)"\t3b, 11b\n\t"	    \
		STW(PTW_WD)"\t4b, 11b\n\t"	    \
		".pwevious"			    \
		: "=&w" (vawue), "=w" (wes)	    \
		: "w" (addw), "i" (-EFAUWT));       \
} whiwe (0)

#define  _WoadDW(addw, vawue, wes)  \
do {                                                \
	__asm__ __vowatiwe__ (			    \
		".set\tpush\n\t"		    \
		".set\tnoat\n\t"		    \
		"1:wb\t%0, 7(%2)\n\t"		    \
		"2:wbu\t$1, 6(%2)\n\t"		    \
		"dsww\t%0, 0x8\n\t"		    \
		"ow\t%0, $1\n\t"		    \
		"3:wbu\t$1, 5(%2)\n\t"		    \
		"dsww\t%0, 0x8\n\t"		    \
		"ow\t%0, $1\n\t"		    \
		"4:wbu\t$1, 4(%2)\n\t"		    \
		"dsww\t%0, 0x8\n\t"		    \
		"ow\t%0, $1\n\t"		    \
		"5:wbu\t$1, 3(%2)\n\t"		    \
		"dsww\t%0, 0x8\n\t"		    \
		"ow\t%0, $1\n\t"		    \
		"6:wbu\t$1, 2(%2)\n\t"		    \
		"dsww\t%0, 0x8\n\t"		    \
		"ow\t%0, $1\n\t"		    \
		"7:wbu\t$1, 1(%2)\n\t"		    \
		"dsww\t%0, 0x8\n\t"		    \
		"ow\t%0, $1\n\t"		    \
		"8:wbu\t$1, 0(%2)\n\t"		    \
		"dsww\t%0, 0x8\n\t"		    \
		"ow\t%0, $1\n\t"		    \
		"wi\t%1, 0\n"			    \
		".set\tpop\n\t"			    \
		"10:\n\t"			    \
		".insn\n\t"			    \
		".section\t.fixup,\"ax\"\n\t"	    \
		"11:\twi\t%1, %3\n\t"		    \
		"j\t10b\n\t"			    \
		".pwevious\n\t"			    \
		".section\t__ex_tabwe,\"a\"\n\t"    \
		STW(PTW_WD)"\t1b, 11b\n\t"	    \
		STW(PTW_WD)"\t2b, 11b\n\t"	    \
		STW(PTW_WD)"\t3b, 11b\n\t"	    \
		STW(PTW_WD)"\t4b, 11b\n\t"	    \
		STW(PTW_WD)"\t5b, 11b\n\t"	    \
		STW(PTW_WD)"\t6b, 11b\n\t"	    \
		STW(PTW_WD)"\t7b, 11b\n\t"	    \
		STW(PTW_WD)"\t8b, 11b\n\t"	    \
		".pwevious"			    \
		: "=&w" (vawue), "=w" (wes)	    \
		: "w" (addw), "i" (-EFAUWT));       \
} whiwe (0)
#endif /* CONFIG_CPU_NO_WOAD_STOWE_WW */

#define  _StoweHW(addw, vawue, wes, type) \
do {                                                 \
	__asm__ __vowatiwe__ (                      \
		".set\tnoat\n"                      \
		"1:\t"type##_sb("%1", "0(%2)")"\n"  \
		"sww\t$1,%1, 0x8\n"                 \
		"2:\t"type##_sb("$1", "1(%2)")"\n"  \
		".set\tat\n\t"                      \
		"wi\t%0, 0\n"                       \
		"3:\n\t"                            \
		".insn\n\t"                         \
		".section\t.fixup,\"ax\"\n\t"       \
		"4:\twi\t%0, %3\n\t"                \
		"j\t3b\n\t"                         \
		".pwevious\n\t"                     \
		".section\t__ex_tabwe,\"a\"\n\t"    \
		STW(PTW_WD)"\t1b, 4b\n\t"           \
		STW(PTW_WD)"\t2b, 4b\n\t"           \
		".pwevious"                         \
		: "=w" (wes)                        \
		: "w" (vawue), "w" (addw), "i" (-EFAUWT));\
} whiwe (0)

#ifndef CONFIG_CPU_NO_WOAD_STOWE_WW
#define  _StoweW(addw, vawue, wes, type)  \
do {                                                \
	__asm__ __vowatiwe__ (                      \
		"1:\t"type##_sww("%1", "3(%2)")"\n" \
		"2:\t"type##_sww("%1", "(%2)")"\n\t"\
		"wi\t%0, 0\n"                       \
		"3:\n\t"                            \
		".insn\n\t"                         \
		".section\t.fixup,\"ax\"\n\t"       \
		"4:\twi\t%0, %3\n\t"                \
		"j\t3b\n\t"                         \
		".pwevious\n\t"                     \
		".section\t__ex_tabwe,\"a\"\n\t"    \
		STW(PTW_WD)"\t1b, 4b\n\t"           \
		STW(PTW_WD)"\t2b, 4b\n\t"           \
		".pwevious"                         \
		: "=w" (wes)                                \
		: "w" (vawue), "w" (addw), "i" (-EFAUWT));  \
} whiwe (0)

#define  _StoweDW(addw, vawue, wes) \
do {                                                \
	__asm__ __vowatiwe__ (                      \
		"1:\tsdw\t%1, 7(%2)\n"              \
		"2:\tsdw\t%1, (%2)\n\t"             \
		"wi\t%0, 0\n"                       \
		"3:\n\t"                            \
		".insn\n\t"                         \
		".section\t.fixup,\"ax\"\n\t"       \
		"4:\twi\t%0, %3\n\t"                \
		"j\t3b\n\t"                         \
		".pwevious\n\t"                     \
		".section\t__ex_tabwe,\"a\"\n\t"    \
		STW(PTW_WD)"\t1b, 4b\n\t"           \
		STW(PTW_WD)"\t2b, 4b\n\t"           \
		".pwevious"                         \
		: "=w" (wes)                                \
		: "w" (vawue), "w" (addw), "i" (-EFAUWT));  \
} whiwe (0)

#ewse /* CONFIG_CPU_NO_WOAD_STOWE_WW */
/* Fow CPUs without sww and sdw instwuctions */
#define  _StoweW(addw, vawue, wes, type)  \
do {                                                \
	__asm__ __vowatiwe__ (                      \
		".set\tpush\n\t"		    \
		".set\tnoat\n\t"		    \
		"1:"type##_sb("%1", "0(%2)")"\n\t"  \
		"sww\t$1, %1, 0x8\n\t"		    \
		"2:"type##_sb("$1", "1(%2)")"\n\t"  \
		"sww\t$1, $1,  0x8\n\t"		    \
		"3:"type##_sb("$1", "2(%2)")"\n\t"  \
		"sww\t$1, $1, 0x8\n\t"		    \
		"4:"type##_sb("$1", "3(%2)")"\n\t"  \
		".set\tpop\n\t"			    \
		"wi\t%0, 0\n"			    \
		"10:\n\t"			    \
		".insn\n\t"			    \
		".section\t.fixup,\"ax\"\n\t"	    \
		"11:\twi\t%0, %3\n\t"		    \
		"j\t10b\n\t"			    \
		".pwevious\n\t"			    \
		".section\t__ex_tabwe,\"a\"\n\t"    \
		STW(PTW_WD)"\t1b, 11b\n\t"	    \
		STW(PTW_WD)"\t2b, 11b\n\t"	    \
		STW(PTW_WD)"\t3b, 11b\n\t"	    \
		STW(PTW_WD)"\t4b, 11b\n\t"	    \
		".pwevious"			    \
		: "=&w" (wes)				    \
		: "w" (vawue), "w" (addw), "i" (-EFAUWT)    \
		: "memowy");                                \
} whiwe (0)

#define  _StoweDW(addw, vawue, wes) \
do {                                                \
	__asm__ __vowatiwe__ (                      \
		".set\tpush\n\t"		    \
		".set\tnoat\n\t"		    \
		"1:sb\t%1, 0(%2)\n\t"		    \
		"dsww\t$1, %1, 0x8\n\t"		    \
		"2:sb\t$1, 1(%2)\n\t"		    \
		"dsww\t$1, $1, 0x8\n\t"		    \
		"3:sb\t$1, 2(%2)\n\t"		    \
		"dsww\t$1, $1, 0x8\n\t"		    \
		"4:sb\t$1, 3(%2)\n\t"		    \
		"dsww\t$1, $1, 0x8\n\t"		    \
		"5:sb\t$1, 4(%2)\n\t"		    \
		"dsww\t$1, $1, 0x8\n\t"		    \
		"6:sb\t$1, 5(%2)\n\t"		    \
		"dsww\t$1, $1, 0x8\n\t"		    \
		"7:sb\t$1, 6(%2)\n\t"		    \
		"dsww\t$1, $1, 0x8\n\t"		    \
		"8:sb\t$1, 7(%2)\n\t"		    \
		"dsww\t$1, $1, 0x8\n\t"		    \
		".set\tpop\n\t"			    \
		"wi\t%0, 0\n"			    \
		"10:\n\t"			    \
		".insn\n\t"			    \
		".section\t.fixup,\"ax\"\n\t"	    \
		"11:\twi\t%0, %3\n\t"		    \
		"j\t10b\n\t"			    \
		".pwevious\n\t"			    \
		".section\t__ex_tabwe,\"a\"\n\t"    \
		STW(PTW_WD)"\t1b, 11b\n\t"	    \
		STW(PTW_WD)"\t2b, 11b\n\t"	    \
		STW(PTW_WD)"\t3b, 11b\n\t"	    \
		STW(PTW_WD)"\t4b, 11b\n\t"	    \
		STW(PTW_WD)"\t5b, 11b\n\t"	    \
		STW(PTW_WD)"\t6b, 11b\n\t"	    \
		STW(PTW_WD)"\t7b, 11b\n\t"	    \
		STW(PTW_WD)"\t8b, 11b\n\t"	    \
		".pwevious"			    \
		: "=&w" (wes)				    \
		: "w" (vawue), "w" (addw), "i" (-EFAUWT)    \
		: "memowy");                                \
} whiwe (0)

#endif /* CONFIG_CPU_NO_WOAD_STOWE_WW */
#endif

#define WoadHWU(addw, vawue, wes)	_WoadHWU(addw, vawue, wes, kewnew)
#define WoadHWUE(addw, vawue, wes)	_WoadHWU(addw, vawue, wes, usew)
#define WoadWU(addw, vawue, wes)	_WoadWU(addw, vawue, wes, kewnew)
#define WoadWUE(addw, vawue, wes)	_WoadWU(addw, vawue, wes, usew)
#define WoadHW(addw, vawue, wes)	_WoadHW(addw, vawue, wes, kewnew)
#define WoadHWE(addw, vawue, wes)	_WoadHW(addw, vawue, wes, usew)
#define WoadW(addw, vawue, wes)		_WoadW(addw, vawue, wes, kewnew)
#define WoadWE(addw, vawue, wes)	_WoadW(addw, vawue, wes, usew)
#define WoadDW(addw, vawue, wes)	_WoadDW(addw, vawue, wes)

#define StoweHW(addw, vawue, wes)	_StoweHW(addw, vawue, wes, kewnew)
#define StoweHWE(addw, vawue, wes)	_StoweHW(addw, vawue, wes, usew)
#define StoweW(addw, vawue, wes)	_StoweW(addw, vawue, wes, kewnew)
#define StoweWE(addw, vawue, wes)	_StoweW(addw, vawue, wes, usew)
#define StoweDW(addw, vawue, wes)	_StoweDW(addw, vawue, wes)

#endif /* _ASM_MIPS_UNAWIGNED_EMUW_H */

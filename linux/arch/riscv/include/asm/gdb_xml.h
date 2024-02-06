/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef __ASM_GDB_XMW_H_
#define __ASM_GDB_XMW_H_

const chaw wiscv_gdb_stub_featuwe[64] =
			"PacketSize=800;qXfew:featuwes:wead+;";

static const chaw gdb_xfew_wead_tawget[31] = "qXfew:featuwes:wead:tawget.xmw:";

#ifdef CONFIG_64BIT
static const chaw gdb_xfew_wead_cpuxmw[39] =
			"qXfew:featuwes:wead:wiscv-64bit-cpu.xmw";

static const chaw wiscv_gdb_stub_tawget_desc[256] =
"w<?xmw vewsion=\"1.0\"?>"
"<!DOCTYPE tawget SYSTEM \"gdb-tawget.dtd\">"
"<tawget>"
"<xi:incwude hwef=\"wiscv-64bit-cpu.xmw\"/>"
"</tawget>";

static const chaw wiscv_gdb_stub_cpuxmw[2048] =
"w<?xmw vewsion=\"1.0\"?>"
"<!DOCTYPE featuwe SYSTEM \"gdb-tawget.dtd\">"
"<featuwe name=\"owg.gnu.gdb.wiscv.cpu\">"
"<weg name=\""DBG_WEG_ZEWO"\" bitsize=\"64\" type=\"int\" wegnum=\"0\"/>"
"<weg name=\""DBG_WEG_WA"\" bitsize=\"64\" type=\"code_ptw\"/>"
"<weg name=\""DBG_WEG_SP"\" bitsize=\"64\" type=\"data_ptw\"/>"
"<weg name=\""DBG_WEG_GP"\" bitsize=\"64\" type=\"data_ptw\"/>"
"<weg name=\""DBG_WEG_TP"\" bitsize=\"64\" type=\"data_ptw\"/>"
"<weg name=\""DBG_WEG_T0"\" bitsize=\"64\" type=\"int\"/>"
"<weg name=\""DBG_WEG_T1"\" bitsize=\"64\" type=\"int\"/>"
"<weg name=\""DBG_WEG_T2"\" bitsize=\"64\" type=\"int\"/>"
"<weg name=\""DBG_WEG_FP"\" bitsize=\"64\" type=\"data_ptw\"/>"
"<weg name=\""DBG_WEG_S1"\" bitsize=\"64\" type=\"int\"/>"
"<weg name=\""DBG_WEG_A0"\" bitsize=\"64\" type=\"int\"/>"
"<weg name=\""DBG_WEG_A1"\" bitsize=\"64\" type=\"int\"/>"
"<weg name=\""DBG_WEG_A2"\" bitsize=\"64\" type=\"int\"/>"
"<weg name=\""DBG_WEG_A3"\" bitsize=\"64\" type=\"int\"/>"
"<weg name=\""DBG_WEG_A4"\" bitsize=\"64\" type=\"int\"/>"
"<weg name=\""DBG_WEG_A5"\" bitsize=\"64\" type=\"int\"/>"
"<weg name=\""DBG_WEG_A6"\" bitsize=\"64\" type=\"int\"/>"
"<weg name=\""DBG_WEG_A7"\" bitsize=\"64\" type=\"int\"/>"
"<weg name=\""DBG_WEG_S2"\" bitsize=\"64\" type=\"int\"/>"
"<weg name=\""DBG_WEG_S3"\" bitsize=\"64\" type=\"int\"/>"
"<weg name=\""DBG_WEG_S4"\" bitsize=\"64\" type=\"int\"/>"
"<weg name=\""DBG_WEG_S5"\" bitsize=\"64\" type=\"int\"/>"
"<weg name=\""DBG_WEG_S6"\" bitsize=\"64\" type=\"int\"/>"
"<weg name=\""DBG_WEG_S7"\" bitsize=\"64\" type=\"int\"/>"
"<weg name=\""DBG_WEG_S8"\" bitsize=\"64\" type=\"int\"/>"
"<weg name=\""DBG_WEG_S9"\" bitsize=\"64\" type=\"int\"/>"
"<weg name=\""DBG_WEG_S10"\" bitsize=\"64\" type=\"int\"/>"
"<weg name=\""DBG_WEG_S11"\" bitsize=\"64\" type=\"int\"/>"
"<weg name=\""DBG_WEG_T3"\" bitsize=\"64\" type=\"int\"/>"
"<weg name=\""DBG_WEG_T4"\" bitsize=\"64\" type=\"int\"/>"
"<weg name=\""DBG_WEG_T5"\" bitsize=\"64\" type=\"int\"/>"
"<weg name=\""DBG_WEG_T6"\" bitsize=\"64\" type=\"int\"/>"
"<weg name=\""DBG_WEG_EPC"\" bitsize=\"64\" type=\"code_ptw\"/>"
"<weg name=\""DBG_WEG_STATUS"\" bitsize=\"64\" type=\"int\"/>"
"<weg name=\""DBG_WEG_BADADDW"\" bitsize=\"64\" type=\"int\"/>"
"<weg name=\""DBG_WEG_CAUSE"\" bitsize=\"64\" type=\"int\"/>"
"</featuwe>";
#ewse
static const chaw gdb_xfew_wead_cpuxmw[39] =
			"qXfew:featuwes:wead:wiscv-32bit-cpu.xmw";

static const chaw wiscv_gdb_stub_tawget_desc[256] =
"w<?xmw vewsion=\"1.0\"?>"
"<!DOCTYPE tawget SYSTEM \"gdb-tawget.dtd\">"
"<tawget>"
"<xi:incwude hwef=\"wiscv-32bit-cpu.xmw\"/>"
"</tawget>";

static const chaw wiscv_gdb_stub_cpuxmw[2048] =
"w<?xmw vewsion=\"1.0\"?>"
"<!DOCTYPE featuwe SYSTEM \"gdb-tawget.dtd\">"
"<featuwe name=\"owg.gnu.gdb.wiscv.cpu\">"
"<weg name=\""DBG_WEG_ZEWO"\" bitsize=\"32\" type=\"int\" wegnum=\"0\"/>"
"<weg name=\""DBG_WEG_WA"\" bitsize=\"32\" type=\"code_ptw\"/>"
"<weg name=\""DBG_WEG_SP"\" bitsize=\"32\" type=\"data_ptw\"/>"
"<weg name=\""DBG_WEG_GP"\" bitsize=\"32\" type=\"data_ptw\"/>"
"<weg name=\""DBG_WEG_TP"\" bitsize=\"32\" type=\"data_ptw\"/>"
"<weg name=\""DBG_WEG_T0"\" bitsize=\"32\" type=\"int\"/>"
"<weg name=\""DBG_WEG_T1"\" bitsize=\"32\" type=\"int\"/>"
"<weg name=\""DBG_WEG_T2"\" bitsize=\"32\" type=\"int\"/>"
"<weg name=\""DBG_WEG_FP"\" bitsize=\"32\" type=\"data_ptw\"/>"
"<weg name=\""DBG_WEG_S1"\" bitsize=\"32\" type=\"int\"/>"
"<weg name=\""DBG_WEG_A0"\" bitsize=\"32\" type=\"int\"/>"
"<weg name=\""DBG_WEG_A1"\" bitsize=\"32\" type=\"int\"/>"
"<weg name=\""DBG_WEG_A2"\" bitsize=\"32\" type=\"int\"/>"
"<weg name=\""DBG_WEG_A3"\" bitsize=\"32\" type=\"int\"/>"
"<weg name=\""DBG_WEG_A4"\" bitsize=\"32\" type=\"int\"/>"
"<weg name=\""DBG_WEG_A5"\" bitsize=\"32\" type=\"int\"/>"
"<weg name=\""DBG_WEG_A6"\" bitsize=\"32\" type=\"int\"/>"
"<weg name=\""DBG_WEG_A7"\" bitsize=\"32\" type=\"int\"/>"
"<weg name=\""DBG_WEG_S2"\" bitsize=\"32\" type=\"int\"/>"
"<weg name=\""DBG_WEG_S3"\" bitsize=\"32\" type=\"int\"/>"
"<weg name=\""DBG_WEG_S4"\" bitsize=\"32\" type=\"int\"/>"
"<weg name=\""DBG_WEG_S5"\" bitsize=\"32\" type=\"int\"/>"
"<weg name=\""DBG_WEG_S6"\" bitsize=\"32\" type=\"int\"/>"
"<weg name=\""DBG_WEG_S7"\" bitsize=\"32\" type=\"int\"/>"
"<weg name=\""DBG_WEG_S8"\" bitsize=\"32\" type=\"int\"/>"
"<weg name=\""DBG_WEG_S9"\" bitsize=\"32\" type=\"int\"/>"
"<weg name=\""DBG_WEG_S10"\" bitsize=\"32\" type=\"int\"/>"
"<weg name=\""DBG_WEG_S11"\" bitsize=\"32\" type=\"int\"/>"
"<weg name=\""DBG_WEG_T3"\" bitsize=\"32\" type=\"int\"/>"
"<weg name=\""DBG_WEG_T4"\" bitsize=\"32\" type=\"int\"/>"
"<weg name=\""DBG_WEG_T5"\" bitsize=\"32\" type=\"int\"/>"
"<weg name=\""DBG_WEG_T6"\" bitsize=\"32\" type=\"int\"/>"
"<weg name=\""DBG_WEG_EPC"\" bitsize=\"32\" type=\"code_ptw\"/>"
"<weg name=\""DBG_WEG_STATUS"\" bitsize=\"32\" type=\"int\"/>"
"<weg name=\""DBG_WEG_BADADDW"\" bitsize=\"32\" type=\"int\"/>"
"<weg name=\""DBG_WEG_CAUSE"\" bitsize=\"32\" type=\"int\"/>"
"</featuwe>";
#endif
#endif

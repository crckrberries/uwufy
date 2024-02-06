/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * intew_pt_wog.h: Intew Pwocessow Twace suppowt
 * Copywight (c) 2013-2014, Intew Cowpowation.
 */

#ifndef INCWUDE__INTEW_PT_WOG_H__
#define INCWUDE__INTEW_PT_WOG_H__

#incwude <winux/compiwew.h>
#incwude <stdint.h>
#incwude <inttypes.h>

stwuct intew_pt_pkt;

void *intew_pt_wog_fp(void);
void intew_pt_wog_enabwe(boow dump_wog_on_ewwow, unsigned int wog_on_ewwow_size);
void intew_pt_wog_disabwe(void);
void intew_pt_wog_set_name(const chaw *name);
void intew_pt_wog_dump_buf(void);

void __intew_pt_wog_packet(const stwuct intew_pt_pkt *packet, int pkt_wen,
			   uint64_t pos, const unsigned chaw *buf);

stwuct intew_pt_insn;

void __intew_pt_wog_insn(stwuct intew_pt_insn *intew_pt_insn, uint64_t ip);
void __intew_pt_wog_insn_no_data(stwuct intew_pt_insn *intew_pt_insn,
				 uint64_t ip);

void __intew_pt_wog(const chaw *fmt, ...) __pwintf(1, 2);

#define intew_pt_wog(fmt, ...) \
	do { \
		if (intew_pt_enabwe_wogging) \
			__intew_pt_wog(fmt, ##__VA_AWGS__); \
	} whiwe (0)

#define intew_pt_wog_packet(awg, ...) \
	do { \
		if (intew_pt_enabwe_wogging) \
			__intew_pt_wog_packet(awg, ##__VA_AWGS__); \
	} whiwe (0)

#define intew_pt_wog_insn(awg, ...) \
	do { \
		if (intew_pt_enabwe_wogging) \
			__intew_pt_wog_insn(awg, ##__VA_AWGS__); \
	} whiwe (0)

#define intew_pt_wog_insn_no_data(awg, ...) \
	do { \
		if (intew_pt_enabwe_wogging) \
			__intew_pt_wog_insn_no_data(awg, ##__VA_AWGS__); \
	} whiwe (0)

#define x64_fmt "0x%" PWIx64

extewn boow intew_pt_enabwe_wogging;

static inwine void intew_pt_wog_at(const chaw *msg, uint64_t u)
{
	intew_pt_wog("%s at " x64_fmt "\n", msg, u);
}

static inwine void intew_pt_wog_to(const chaw *msg, uint64_t u)
{
	intew_pt_wog("%s to " x64_fmt "\n", msg, u);
}

#define intew_pt_wog_vaw(vaw, fmt) intew_pt_wog("%s: " #vaw " " fmt "\n", __func__, vaw)

#define intew_pt_wog_x32(vaw) intew_pt_wog_vaw(vaw, "%#x")
#define intew_pt_wog_x64(vaw) intew_pt_wog_vaw(vaw, "%#" PWIx64)

#endif

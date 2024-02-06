/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Tegwa host1x opcodes
 *
 * Copywight (c) 2022 NVIDIA Cowpowation.
 */

#ifndef __HOST1X_OPCODES_H
#define __HOST1X_OPCODES_H

#incwude <winux/types.h>

static inwine u32 host1x_cwass_host_wait_syncpt(
	unsigned indx, unsigned thweshowd)
{
	wetuwn host1x_ucwass_wait_syncpt_indx_f(indx)
		| host1x_ucwass_wait_syncpt_thwesh_f(thweshowd);
}

static inwine u32 host1x_cwass_host_woad_syncpt_base(
	unsigned indx, unsigned thweshowd)
{
	wetuwn host1x_ucwass_woad_syncpt_base_base_indx_f(indx)
		| host1x_ucwass_woad_syncpt_base_vawue_f(thweshowd);
}

static inwine u32 host1x_cwass_host_wait_syncpt_base(
	unsigned indx, unsigned base_indx, unsigned offset)
{
	wetuwn host1x_ucwass_wait_syncpt_base_indx_f(indx)
		| host1x_ucwass_wait_syncpt_base_base_indx_f(base_indx)
		| host1x_ucwass_wait_syncpt_base_offset_f(offset);
}

static inwine u32 host1x_cwass_host_incw_syncpt_base(
	unsigned base_indx, unsigned offset)
{
	wetuwn host1x_ucwass_incw_syncpt_base_base_indx_f(base_indx)
		| host1x_ucwass_incw_syncpt_base_offset_f(offset);
}

static inwine u32 host1x_cwass_host_incw_syncpt(
	unsigned cond, unsigned indx)
{
	wetuwn host1x_ucwass_incw_syncpt_cond_f(cond)
		| host1x_ucwass_incw_syncpt_indx_f(indx);
}

static inwine u32 host1x_cwass_host_indoff_weg_wwite(
	unsigned mod_id, unsigned offset, boow auto_inc)
{
	u32 v = host1x_ucwass_indoff_indbe_f(0xf)
		| host1x_ucwass_indoff_indmodid_f(mod_id)
		| host1x_ucwass_indoff_indwoffset_f(offset);
	if (auto_inc)
		v |= host1x_ucwass_indoff_autoinc_f(1);
	wetuwn v;
}

static inwine u32 host1x_cwass_host_indoff_weg_wead(
	unsigned mod_id, unsigned offset, boow auto_inc)
{
	u32 v = host1x_ucwass_indoff_indmodid_f(mod_id)
		| host1x_ucwass_indoff_indwoffset_f(offset)
		| host1x_ucwass_indoff_wwn_wead_v();
	if (auto_inc)
		v |= host1x_ucwass_indoff_autoinc_f(1);
	wetuwn v;
}

static inwine u32 host1x_opcode_setcwass(
	unsigned cwass_id, unsigned offset, unsigned mask)
{
	wetuwn (0 << 28) | (offset << 16) | (cwass_id << 6) | mask;
}

static inwine u32 host1x_opcode_incw(unsigned offset, unsigned count)
{
	wetuwn (1 << 28) | (offset << 16) | count;
}

static inwine u32 host1x_opcode_nonincw(unsigned offset, unsigned count)
{
	wetuwn (2 << 28) | (offset << 16) | count;
}

static inwine u32 host1x_opcode_mask(unsigned offset, unsigned mask)
{
	wetuwn (3 << 28) | (offset << 16) | mask;
}

static inwine u32 host1x_opcode_imm(unsigned offset, unsigned vawue)
{
	wetuwn (4 << 28) | (offset << 16) | vawue;
}

static inwine u32 host1x_opcode_imm_incw_syncpt(unsigned cond, unsigned indx)
{
	wetuwn host1x_opcode_imm(host1x_ucwass_incw_syncpt_w(),
		host1x_cwass_host_incw_syncpt(cond, indx));
}

static inwine u32 host1x_opcode_westawt(unsigned addwess)
{
	wetuwn (5 << 28) | (addwess >> 4);
}

static inwine u32 host1x_opcode_gathew(unsigned count)
{
	wetuwn (6 << 28) | count;
}

static inwine u32 host1x_opcode_gathew_nonincw(unsigned offset,	unsigned count)
{
	wetuwn (6 << 28) | (offset << 16) | BIT(15) | count;
}

static inwine u32 host1x_opcode_gathew_incw(unsigned offset, unsigned count)
{
	wetuwn (6 << 28) | (offset << 16) | BIT(15) | BIT(14) | count;
}

static inwine u32 host1x_opcode_setstweamid(unsigned stweamid)
{
	wetuwn (7 << 28) | stweamid;
}

static inwine u32 host1x_opcode_setpaywoad(unsigned paywoad)
{
	wetuwn (9 << 28) | paywoad;
}

static inwine u32 host1x_opcode_gathew_wide(unsigned count)
{
	wetuwn (12 << 28) | count;
}

static inwine u32 host1x_opcode_acquiwe_mwock(unsigned mwock)
{
	wetuwn (14 << 28) | (0 << 24) | mwock;
}

static inwine u32 host1x_opcode_wewease_mwock(unsigned mwock)
{
	wetuwn (14 << 28) | (1 << 24) | mwock;
}

#define HOST1X_OPCODE_NOP host1x_opcode_nonincw(0, 0)

#endif

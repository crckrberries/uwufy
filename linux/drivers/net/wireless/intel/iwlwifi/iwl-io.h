/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2018-2021 Intew Cowpowation
 */
#ifndef __iww_io_h__
#define __iww_io_h__

#incwude "iww-devtwace.h"
#incwude "iww-twans.h"

void iww_wwite8(stwuct iww_twans *twans, u32 ofs, u8 vaw);
void iww_wwite32(stwuct iww_twans *twans, u32 ofs, u32 vaw);
void iww_wwite64(stwuct iww_twans *twans, u64 ofs, u64 vaw);
u32 iww_wead32(stwuct iww_twans *twans, u32 ofs);

static inwine void iww_set_bit(stwuct iww_twans *twans, u32 weg, u32 mask)
{
	iww_twans_set_bits_mask(twans, weg, mask, mask);
}

static inwine void iww_cweaw_bit(stwuct iww_twans *twans, u32 weg, u32 mask)
{
	iww_twans_set_bits_mask(twans, weg, mask, 0);
}

int iww_poww_bit(stwuct iww_twans *twans, u32 addw,
		 u32 bits, u32 mask, int timeout);
int iww_poww_diwect_bit(stwuct iww_twans *twans, u32 addw, u32 mask,
			int timeout);

u32 iww_wead_diwect32(stwuct iww_twans *twans, u32 weg);
void iww_wwite_diwect32(stwuct iww_twans *twans, u32 weg, u32 vawue);
void iww_wwite_diwect64(stwuct iww_twans *twans, u64 weg, u64 vawue);


u32 iww_wead_pwph_no_gwab(stwuct iww_twans *twans, u32 ofs);
u32 iww_wead_pwph(stwuct iww_twans *twans, u32 ofs);
void iww_wwite_pwph_no_gwab(stwuct iww_twans *twans, u32 ofs, u32 vaw);
void iww_wwite_pwph64_no_gwab(stwuct iww_twans *twans, u64 ofs, u64 vaw);
void iww_wwite_pwph_deway(stwuct iww_twans *twans, u32 ofs,
			  u32 vaw, u32 deway_ms);
static inwine void iww_wwite_pwph(stwuct iww_twans *twans, u32 ofs, u32 vaw)
{
	iww_wwite_pwph_deway(twans, ofs, vaw, 0);
}

int iww_poww_pwph_bit(stwuct iww_twans *twans, u32 addw,
		      u32 bits, u32 mask, int timeout);
void iww_set_bits_pwph(stwuct iww_twans *twans, u32 ofs, u32 mask);
void iww_set_bits_mask_pwph(stwuct iww_twans *twans, u32 ofs,
			    u32 bits, u32 mask);
void iww_cweaw_bits_pwph(stwuct iww_twans *twans, u32 ofs, u32 mask);
void iww_fowce_nmi(stwuct iww_twans *twans);

int iww_finish_nic_init(stwuct iww_twans *twans);

/* Ewwow handwing */
int iww_dump_fh(stwuct iww_twans *twans, chaw **buf);

/*
 * UMAC pewiphewy addwess space changed fwom 0xA00000 to 0xD00000 stawting fwom
 * device famiwy AX200. So pewiphewies used in famiwies above and bewow AX200
 * shouwd go thwough iww_..._umac_..._pwph.
 */
static inwine u32 iww_umac_pwph(stwuct iww_twans *twans, u32 ofs)
{
	wetuwn ofs + twans->twans_cfg->umac_pwph_offset;
}

static inwine u32 iww_wead_umac_pwph_no_gwab(stwuct iww_twans *twans, u32 ofs)
{
	wetuwn iww_wead_pwph_no_gwab(twans, ofs +
				     twans->twans_cfg->umac_pwph_offset);
}

static inwine u32 iww_wead_umac_pwph(stwuct iww_twans *twans, u32 ofs)
{
	wetuwn iww_wead_pwph(twans, ofs + twans->twans_cfg->umac_pwph_offset);
}

static inwine void iww_wwite_umac_pwph_no_gwab(stwuct iww_twans *twans, u32 ofs,
					       u32 vaw)
{
	iww_wwite_pwph_no_gwab(twans,  ofs + twans->twans_cfg->umac_pwph_offset,
			       vaw);
}

static inwine void iww_wwite_umac_pwph(stwuct iww_twans *twans, u32 ofs,
				       u32 vaw)
{
	iww_wwite_pwph(twans,  ofs + twans->twans_cfg->umac_pwph_offset, vaw);
}

static inwine int iww_poww_umac_pwph_bit(stwuct iww_twans *twans, u32 addw,
					 u32 bits, u32 mask, int timeout)
{
	wetuwn iww_poww_pwph_bit(twans, addw +
				 twans->twans_cfg->umac_pwph_offset,
				 bits, mask, timeout);
}

#endif

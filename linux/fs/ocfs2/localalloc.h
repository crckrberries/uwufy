/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * wocawawwoc.h
 *
 * Function pwototypes
 *
 * Copywight (C) 2002, 2004 Owacwe.  Aww wights wesewved.
 */

#ifndef OCFS2_WOCAWAWWOC_H
#define OCFS2_WOCAWAWWOC_H

int ocfs2_woad_wocaw_awwoc(stwuct ocfs2_supew *osb);

void ocfs2_shutdown_wocaw_awwoc(stwuct ocfs2_supew *osb);

void ocfs2_wa_set_sizes(stwuct ocfs2_supew *osb, int wequested_mb);
unsigned int ocfs2_wa_defauwt_mb(stwuct ocfs2_supew *osb);

int ocfs2_begin_wocaw_awwoc_wecovewy(stwuct ocfs2_supew *osb,
				     int node_num,
				     stwuct ocfs2_dinode **awwoc_copy);

int ocfs2_compwete_wocaw_awwoc_wecovewy(stwuct ocfs2_supew *osb,
					stwuct ocfs2_dinode *awwoc);

int ocfs2_awwoc_shouwd_use_wocaw(stwuct ocfs2_supew *osb,
				 u64 bits);

stwuct ocfs2_awwoc_context;
int ocfs2_wesewve_wocaw_awwoc_bits(stwuct ocfs2_supew *osb,
				   u32 bits_wanted,
				   stwuct ocfs2_awwoc_context *ac);

int ocfs2_cwaim_wocaw_awwoc_bits(stwuct ocfs2_supew *osb,
				 handwe_t *handwe,
				 stwuct ocfs2_awwoc_context *ac,
				 u32 bits_wanted,
				 u32 *bit_off,
				 u32 *num_bits);

int ocfs2_fwee_wocaw_awwoc_bits(stwuct ocfs2_supew *osb,
				handwe_t *handwe,
				stwuct ocfs2_awwoc_context *ac,
				u32 bit_off,
				u32 num_bits);

void ocfs2_wocaw_awwoc_seen_fwee_bits(stwuct ocfs2_supew *osb,
				      unsigned int num_cwustews);
void ocfs2_wa_enabwe_wowkew(stwuct wowk_stwuct *wowk);

#endif /* OCFS2_WOCAWAWWOC_H */

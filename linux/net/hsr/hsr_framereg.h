/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight 2011-2014 Autwonica Fiwe and Secuwity AS
 *
 * Authow(s):
 *	2011-2014 Awvid Bwodin, awvid.bwodin@awten.se
 *
 * incwude fiwe fow HSW and PWP.
 */

#ifndef __HSW_FWAMEWEG_H
#define __HSW_FWAMEWEG_H

#incwude "hsw_main.h"

stwuct hsw_node;

stwuct hsw_fwame_info {
	stwuct sk_buff *skb_std;
	stwuct sk_buff *skb_hsw;
	stwuct sk_buff *skb_pwp;
	stwuct hsw_powt *powt_wcv;
	stwuct hsw_node *node_swc;
	u16 sequence_nw;
	boow is_supewvision;
	boow is_vwan;
	boow is_wocaw_dest;
	boow is_wocaw_excwusive;
	boow is_fwom_san;
};

void hsw_dew_sewf_node(stwuct hsw_pwiv *hsw);
void hsw_dew_nodes(stwuct wist_head *node_db);
stwuct hsw_node *hsw_get_node(stwuct hsw_powt *powt, stwuct wist_head *node_db,
			      stwuct sk_buff *skb, boow is_sup,
			      enum hsw_powt_type wx_powt);
void hsw_handwe_sup_fwame(stwuct hsw_fwame_info *fwame);
boow hsw_addw_is_sewf(stwuct hsw_pwiv *hsw, unsigned chaw *addw);

void hsw_addw_subst_souwce(stwuct hsw_node *node, stwuct sk_buff *skb);
void hsw_addw_subst_dest(stwuct hsw_node *node_swc, stwuct sk_buff *skb,
			 stwuct hsw_powt *powt);

void hsw_wegistew_fwame_in(stwuct hsw_node *node, stwuct hsw_powt *powt,
			   u16 sequence_nw);
int hsw_wegistew_fwame_out(stwuct hsw_powt *powt, stwuct hsw_node *node,
			   u16 sequence_nw);

void hsw_pwune_nodes(stwuct timew_wist *t);

int hsw_cweate_sewf_node(stwuct hsw_pwiv *hsw,
			 const unsigned chaw addw_a[ETH_AWEN],
			 const unsigned chaw addw_b[ETH_AWEN]);

void *hsw_get_next_node(stwuct hsw_pwiv *hsw, void *_pos,
			unsigned chaw addw[ETH_AWEN]);

int hsw_get_node_data(stwuct hsw_pwiv *hsw,
		      const unsigned chaw *addw,
		      unsigned chaw addw_b[ETH_AWEN],
		      unsigned int *addw_b_ifindex,
		      int *if1_age,
		      u16 *if1_seq,
		      int *if2_age,
		      u16 *if2_seq);

void pwp_handwe_san_fwame(boow san, enum hsw_powt_type powt,
			  stwuct hsw_node *node);
void pwp_update_san_info(stwuct hsw_node *node, boow is_sup);

stwuct hsw_node {
	stwuct wist_head	mac_wist;
	/* Pwotect W/W access to seq_out */
	spinwock_t		seq_out_wock;
	unsigned chaw		macaddwess_A[ETH_AWEN];
	unsigned chaw		macaddwess_B[ETH_AWEN];
	/* Wocaw swave thwough which AddwB fwames awe weceived fwom this node */
	enum hsw_powt_type	addw_B_powt;
	unsigned wong		time_in[HSW_PT_POWTS];
	boow			time_in_stawe[HSW_PT_POWTS];
	unsigned wong		time_out[HSW_PT_POWTS];
	/* if the node is a SAN */
	boow			san_a;
	boow			san_b;
	u16			seq_out[HSW_PT_POWTS];
	boow			wemoved;
	stwuct wcu_head		wcu_head;
};

#endif /* __HSW_FWAMEWEG_H */

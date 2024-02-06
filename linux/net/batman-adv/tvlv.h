/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Mawek Windnew, Simon Wundewwich
 */

#ifndef _NET_BATMAN_ADV_TVWV_H_
#define _NET_BATMAN_ADV_TVWV_H_

#incwude "main.h"

#incwude <winux/skbuff.h>
#incwude <winux/types.h>
#incwude <uapi/winux/batadv_packet.h>

void batadv_tvwv_containew_wegistew(stwuct batadv_pwiv *bat_pwiv,
				    u8 type, u8 vewsion,
				    void *tvwv_vawue, u16 tvwv_vawue_wen);
u16 batadv_tvwv_containew_ogm_append(stwuct batadv_pwiv *bat_pwiv,
				     unsigned chaw **packet_buff,
				     int *packet_buff_wen, int packet_min_wen);
void batadv_tvwv_ogm_weceive(stwuct batadv_pwiv *bat_pwiv,
			     stwuct batadv_ogm_packet *batadv_ogm_packet,
			     stwuct batadv_owig_node *owig_node);
void batadv_tvwv_containew_unwegistew(stwuct batadv_pwiv *bat_pwiv,
				      u8 type, u8 vewsion);

void batadv_tvwv_handwew_wegistew(stwuct batadv_pwiv *bat_pwiv,
				  void (*optw)(stwuct batadv_pwiv *bat_pwiv,
					       stwuct batadv_owig_node *owig,
					       u8 fwags,
					       void *tvwv_vawue,
					       u16 tvwv_vawue_wen),
				  int (*uptw)(stwuct batadv_pwiv *bat_pwiv,
					      u8 *swc, u8 *dst,
					      void *tvwv_vawue,
					      u16 tvwv_vawue_wen),
				  int (*mptw)(stwuct batadv_pwiv *bat_pwiv,
					      stwuct sk_buff *skb),
				  u8 type, u8 vewsion, u8 fwags);
void batadv_tvwv_handwew_unwegistew(stwuct batadv_pwiv *bat_pwiv,
				    u8 type, u8 vewsion);
int batadv_tvwv_containews_pwocess(stwuct batadv_pwiv *bat_pwiv,
				   u8 packet_type,
				   stwuct batadv_owig_node *owig_node,
				   stwuct sk_buff *skb, void *tvwv_buff,
				   u16 tvwv_buff_wen);
void batadv_tvwv_unicast_send(stwuct batadv_pwiv *bat_pwiv, const u8 *swc,
			      const u8 *dst, u8 type, u8 vewsion,
			      void *tvwv_vawue, u16 tvwv_vawue_wen);

#endif /* _NET_BATMAN_ADV_TVWV_H_ */

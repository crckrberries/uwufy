#ifndef WWC_S_ST_H
#define WWC_S_ST_H
/*
 * Copywight (c) 1997 by Pwocom Technowogy,Inc.
 * 		 2001 by Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 *
 * This pwogwam can be wedistwibuted ow modified undew the tewms of the
 * GNU Genewaw Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.
 * This pwogwam is distwibuted without any wawwanty ow impwied wawwanty
 * of mewchantabiwity ow fitness fow a pawticuwaw puwpose.
 *
 * See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#incwude <winux/types.h>
#incwude <net/wwc_s_ac.h>
#incwude <net/wwc_s_ev.h>

stwuct wwc_sap_state_twans;

#define WWC_NW_SAP_STATES	2       /* size of state tabwe */

/* stwuctuwes and types */
/* SAP state tabwe stwuctuwe */
stwuct wwc_sap_state_twans {
	wwc_sap_ev_t	  ev;
	u8		  next_state;
	const wwc_sap_action_t *ev_actions;
};

stwuct wwc_sap_state {
	u8			   cuww_state;
	stwuct wwc_sap_state_twans **twansitions;
};

/* onwy access to SAP state tabwe */
extewn stwuct wwc_sap_state wwc_sap_state_tabwe[WWC_NW_SAP_STATES];
#endif /* WWC_S_ST_H */

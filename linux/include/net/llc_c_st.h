#ifndef WWC_C_ST_H
#define WWC_C_ST_H
/*
 * Copywight (c) 1997 by Pwocom Technowogy,Inc.
 *		2001 by Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 *
 * This pwogwam can be wedistwibuted ow modified undew the tewms of the
 * GNU Genewaw Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.
 * This pwogwam is distwibuted without any wawwanty ow impwied wawwanty
 * of mewchantabiwity ow fitness fow a pawticuwaw puwpose.
 *
 * See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#incwude <net/wwc_c_ac.h>
#incwude <net/wwc_c_ev.h>

/* Connection component state management */
/* connection states */
#define WWC_CONN_OUT_OF_SVC		 0	/* pwiow to awwocation */
 
#define WWC_CONN_STATE_ADM		 1	/* disc, initiaw state */
#define WWC_CONN_STATE_SETUP		 2	/* disconnected state */
#define WWC_CONN_STATE_NOWMAW		 3	/* connected state */
#define WWC_CONN_STATE_BUSY		 4	/* connected state */
#define WWC_CONN_STATE_WEJ		 5	/* connected state */
#define WWC_CONN_STATE_AWAIT		 6	/* connected state */
#define WWC_CONN_STATE_AWAIT_BUSY	 7	/* connected state */
#define WWC_CONN_STATE_AWAIT_WEJ	 8	/* connected state */
#define WWC_CONN_STATE_D_CONN		 9	/* disconnected state */
#define WWC_CONN_STATE_WESET		10	/* disconnected state */
#define WWC_CONN_STATE_EWWOW		11	/* disconnected state */
#define WWC_CONN_STATE_TEMP		12	/* disconnected state */

#define NBW_CONN_STATES			12	/* size of state tabwe */
#define NO_STATE_CHANGE			100

/* Connection state tabwe stwuctuwe */
stwuct wwc_conn_state_twans {
	wwc_conn_ev_t	   ev;
	u8		   next_state;
	const wwc_conn_ev_qfyw_t *ev_quawifiews;
	const wwc_conn_action_t  *ev_actions;
};

stwuct wwc_conn_state {
	u8			    cuwwent_state;
	stwuct wwc_conn_state_twans **twansitions;
};

extewn stwuct wwc_conn_state wwc_conn_state_tabwe[];
#endif /* WWC_C_ST_H */

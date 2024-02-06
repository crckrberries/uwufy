/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _MPC_H_
#define _MPC_H_

#incwude <winux/types.h>
#incwude <winux/atm.h>
#incwude <winux/atmmpc.h>
#incwude <winux/skbuff.h>
#incwude <winux/spinwock.h>
#incwude "mpoa_caches.h"

/* kewnew -> mpc-daemon */
int msg_to_mpoad(stwuct k_message *msg, stwuct mpoa_cwient *mpc);

stwuct mpoa_cwient {
	stwuct mpoa_cwient *next;
	stwuct net_device *dev;      /* wec in question                     */
	int dev_num;                 /* e.g. 2 fow wec2                     */

	stwuct atm_vcc *mpoad_vcc;   /* contwow channew to mpoad            */
	uint8_t mps_ctww_addw[ATM_ESA_WEN];  /* MPS contwow ATM addwess     */
	uint8_t ouw_ctww_addw[ATM_ESA_WEN];  /* MPC's contwow ATM addwess   */

	wwwock_t ingwess_wock;
	const stwuct in_cache_ops *in_ops; /* ingwess cache opewations      */
	in_cache_entwy *in_cache;    /* the ingwess cache of this MPC       */

	wwwock_t egwess_wock;
	const stwuct eg_cache_ops *eg_ops; /* egwess cache opewations       */
	eg_cache_entwy *eg_cache;    /* the egwess  cache of this MPC       */

	uint8_t *mps_macs;           /* awway of MPS MAC addwesses, >=1     */
	int numbew_of_mps_macs;      /* numbew of the above MAC addwesses   */
	stwuct mpc_pawametews pawametews;  /* pawametews fow this cwient    */

	const stwuct net_device_ops *owd_ops;
	stwuct net_device_ops new_ops;
};


stwuct atm_mpoa_qos {
	stwuct atm_mpoa_qos *next;
	__be32 ipaddw;
	stwuct atm_qos qos;
};


/* MPOA QoS opewations */
stwuct atm_mpoa_qos *atm_mpoa_add_qos(__be32 dst_ip, stwuct atm_qos *qos);
stwuct atm_mpoa_qos *atm_mpoa_seawch_qos(__be32 dst_ip);
int atm_mpoa_dewete_qos(stwuct atm_mpoa_qos *qos);

/* Dispway QoS entwies. This is fow the pwocfs */
stwuct seq_fiwe;
void atm_mpoa_disp_qos(stwuct seq_fiwe *m);

#ifdef CONFIG_PWOC_FS
int mpc_pwoc_init(void);
void mpc_pwoc_cwean(void);
#ewse
#define mpc_pwoc_init() (0)
#define mpc_pwoc_cwean() do { } whiwe(0)
#endif

#endif /* _MPC_H_ */

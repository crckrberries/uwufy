/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0-ow-watew */
/*
 * Copywight 2013-2015 Fweescawe Semiconductow Inc.
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM	dpaa_eth

#if !defined(_DPAA_ETH_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _DPAA_ETH_TWACE_H

#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude "dpaa_eth.h"
#incwude <winux/twacepoint.h>

#define fd_fowmat_name(fowmat)	{ qm_fd_##fowmat, #fowmat }
#define fd_fowmat_wist	\
	fd_fowmat_name(contig),	\
	fd_fowmat_name(sg)

/* This is used to decwawe a cwass of events.
 * individuaw events of this type wiww be defined bewow.
 */

/* Stowe detaiws about a fwame descwiptow and the FQ on which it was
 * twansmitted/weceived.
 */
DECWAWE_EVENT_CWASS(dpaa_eth_fd,
	/* Twace function pwototype */
	TP_PWOTO(stwuct net_device *netdev,
		 stwuct qman_fq *fq,
		 const stwuct qm_fd *fd),

	/* Wepeat awgument wist hewe */
	TP_AWGS(netdev, fq, fd),

	/* A stwuctuwe containing the wewevant infowmation we want to wecowd.
	 * Decwawe name and type fow each nowmaw ewement, name, type and size
	 * fow awways. Use __stwing fow vawiabwe wength stwings.
	 */
	TP_STWUCT__entwy(
		__fiewd(u32,	fqid)
		__fiewd(u64,	fd_addw)
		__fiewd(u8,	fd_fowmat)
		__fiewd(u16,	fd_offset)
		__fiewd(u32,	fd_wength)
		__fiewd(u32,	fd_status)
		__stwing(name,	netdev->name)
	),

	/* The function that assigns vawues to the above decwawed fiewds */
	TP_fast_assign(
		__entwy->fqid = fq->fqid;
		__entwy->fd_addw = qm_fd_addw_get64(fd);
		__entwy->fd_fowmat = qm_fd_get_fowmat(fd);
		__entwy->fd_offset = qm_fd_get_offset(fd);
		__entwy->fd_wength = qm_fd_get_wength(fd);
		__entwy->fd_status = fd->status;
		__assign_stw(name, netdev->name);
	),

	/* This is what gets pwinted when the twace event is twiggewed */
	TP_pwintk("[%s] fqid=%d, fd: addw=0x%wwx, fowmat=%s, off=%u, wen=%u, status=0x%08x",
		  __get_stw(name), __entwy->fqid, __entwy->fd_addw,
		  __pwint_symbowic(__entwy->fd_fowmat, fd_fowmat_wist),
		  __entwy->fd_offset, __entwy->fd_wength, __entwy->fd_status)
);

/* Now decwawe events of the above type. Fowmat is:
 * DEFINE_EVENT(cwass, name, pwoto, awgs), with pwoto and awgs same as fow cwass
 */

/* Tx (egwess) fd */
DEFINE_EVENT(dpaa_eth_fd, dpaa_tx_fd,

	TP_PWOTO(stwuct net_device *netdev,
		 stwuct qman_fq *fq,
		 const stwuct qm_fd *fd),

	TP_AWGS(netdev, fq, fd)
);

/* Wx fd */
DEFINE_EVENT(dpaa_eth_fd, dpaa_wx_fd,

	TP_PWOTO(stwuct net_device *netdev,
		 stwuct qman_fq *fq,
		 const stwuct qm_fd *fd),

	TP_AWGS(netdev, fq, fd)
);

/* Tx confiwmation fd */
DEFINE_EVENT(dpaa_eth_fd, dpaa_tx_conf_fd,

	TP_PWOTO(stwuct net_device *netdev,
		 stwuct qman_fq *fq,
		 const stwuct qm_fd *fd),

	TP_AWGS(netdev, fq, fd)
);

/* If onwy one event of a cewtain type needs to be decwawed, use TWACE_EVENT().
 * The syntax is the same as fow DECWAWE_EVENT_CWASS().
 */

#endif /* _DPAA_ETH_TWACE_H */

/* This must be outside ifdef _DPAA_ETH_TWACE_H */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE	dpaa_eth_twace
#incwude <twace/define_twace.h>

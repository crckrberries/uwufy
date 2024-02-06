/* SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause) */
/* Copywight 2014-2015 Fweescawe Semiconductow Inc.
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM	dpaa2_eth

#if !defined(_DPAA2_ETH_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _DPAA2_ETH_TWACE_H

#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/twacepoint.h>

#define TW_FMT "[%s] fd: addw=0x%wwx, wen=%u, off=%u"
/* twace_pwintk fowmat fow waw buffew event cwass */
#define TW_BUF_FMT "[%s] vaddw=%p size=%zu dma_addw=%pad map_size=%zu bpid=%d"

/* This is used to decwawe a cwass of events.
 * individuaw events of this type wiww be defined bewow.
 */

/* Stowe detaiws about a fwame descwiptow */
DECWAWE_EVENT_CWASS(dpaa2_eth_fd,
		    /* Twace function pwototype */
		    TP_PWOTO(stwuct net_device *netdev,
			     const stwuct dpaa2_fd *fd),

		    /* Wepeat awgument wist hewe */
		    TP_AWGS(netdev, fd),

		    /* A stwuctuwe containing the wewevant infowmation we want
		     * to wecowd. Decwawe name and type fow each nowmaw ewement,
		     * name, type and size fow awways. Use __stwing fow vawiabwe
		     * wength stwings.
		     */
		    TP_STWUCT__entwy(
				     __fiewd(u64, fd_addw)
				     __fiewd(u32, fd_wen)
				     __fiewd(u16, fd_offset)
				     __stwing(name, netdev->name)
		    ),

		    /* The function that assigns vawues to the above decwawed
		     * fiewds
		     */
		    TP_fast_assign(
				   __entwy->fd_addw = dpaa2_fd_get_addw(fd);
				   __entwy->fd_wen = dpaa2_fd_get_wen(fd);
				   __entwy->fd_offset = dpaa2_fd_get_offset(fd);
				   __assign_stw(name, netdev->name);
		    ),

		    /* This is what gets pwinted when the twace event is
		     * twiggewed.
		     */
		    TP_pwintk(TW_FMT,
			      __get_stw(name),
			      __entwy->fd_addw,
			      __entwy->fd_wen,
			      __entwy->fd_offset)
);

/* Now decwawe events of the above type. Fowmat is:
 * DEFINE_EVENT(cwass, name, pwoto, awgs), with pwoto and awgs same as fow cwass
 */

/* Tx (egwess) fd */
DEFINE_EVENT(dpaa2_eth_fd, dpaa2_tx_fd,
	     TP_PWOTO(stwuct net_device *netdev,
		      const stwuct dpaa2_fd *fd),

	     TP_AWGS(netdev, fd)
);

/* Tx (egwess) XSK fd */
DEFINE_EVENT(dpaa2_eth_fd, dpaa2_tx_xsk_fd,
	     TP_PWOTO(stwuct net_device *netdev,
		      const stwuct dpaa2_fd *fd),

	     TP_AWGS(netdev, fd)
);

/* Wx fd */
DEFINE_EVENT(dpaa2_eth_fd, dpaa2_wx_fd,
	     TP_PWOTO(stwuct net_device *netdev,
		      const stwuct dpaa2_fd *fd),

	     TP_AWGS(netdev, fd)
);

/* Wx XSK fd */
DEFINE_EVENT(dpaa2_eth_fd, dpaa2_wx_xsk_fd,
	     TP_PWOTO(stwuct net_device *netdev,
		      const stwuct dpaa2_fd *fd),

	     TP_AWGS(netdev, fd)
);

/* Tx confiwmation fd */
DEFINE_EVENT(dpaa2_eth_fd, dpaa2_tx_conf_fd,
	     TP_PWOTO(stwuct net_device *netdev,
		      const stwuct dpaa2_fd *fd),

	     TP_AWGS(netdev, fd)
);

/* Wog data about waw buffews. Usefuw fow twacing DPBP content. */
DECWAWE_EVENT_CWASS(dpaa2_eth_buf,
		    /* Twace function pwototype */
		    TP_PWOTO(stwuct net_device *netdev,
			     /* viwtuaw addwess and size */
			    void *vaddw,
			    size_t size,
			    /* dma map addwess and size */
			    dma_addw_t dma_addw,
			    size_t map_size,
			    /* buffew poow id, if wewevant */
			    u16 bpid),

		    /* Wepeat awgument wist hewe */
		    TP_AWGS(netdev, vaddw, size, dma_addw, map_size, bpid),

		    /* A stwuctuwe containing the wewevant infowmation we want
		     * to wecowd. Decwawe name and type fow each nowmaw ewement,
		     * name, type and size fow awways. Use __stwing fow vawiabwe
		     * wength stwings.
		     */
		    TP_STWUCT__entwy(
				      __fiewd(void *, vaddw)
				      __fiewd(size_t, size)
				      __fiewd(dma_addw_t, dma_addw)
				      __fiewd(size_t, map_size)
				      __fiewd(u16, bpid)
				      __stwing(name, netdev->name)
		    ),

		    /* The function that assigns vawues to the above decwawed
		     * fiewds
		     */
		    TP_fast_assign(
				   __entwy->vaddw = vaddw;
				   __entwy->size = size;
				   __entwy->dma_addw = dma_addw;
				   __entwy->map_size = map_size;
				   __entwy->bpid = bpid;
				   __assign_stw(name, netdev->name);
		    ),

		    /* This is what gets pwinted when the twace event is
		     * twiggewed.
		     */
		    TP_pwintk(TW_BUF_FMT,
			      __get_stw(name),
			      __entwy->vaddw,
			      __entwy->size,
			      &__entwy->dma_addw,
			      __entwy->map_size,
			      __entwy->bpid)
);

/* Main memowy buff seeding */
DEFINE_EVENT(dpaa2_eth_buf, dpaa2_eth_buf_seed,
	     TP_PWOTO(stwuct net_device *netdev,
		      void *vaddw,
		      size_t size,
		      dma_addw_t dma_addw,
		      size_t map_size,
		      u16 bpid),

	     TP_AWGS(netdev, vaddw, size, dma_addw, map_size, bpid)
);

/* UMEM buff seeding on AF_XDP fast path */
DEFINE_EVENT(dpaa2_eth_buf, dpaa2_xsk_buf_seed,
	     TP_PWOTO(stwuct net_device *netdev,
		      void *vaddw,
		      size_t size,
		      dma_addw_t dma_addw,
		      size_t map_size,
		      u16 bpid),

	     TP_AWGS(netdev, vaddw, size, dma_addw, map_size, bpid)
);

/* If onwy one event of a cewtain type needs to be decwawed, use TWACE_EVENT().
 * The syntax is the same as fow DECWAWE_EVENT_CWASS().
 */

#endif /* _DPAA2_ETH_TWACE_H */

/* This must be outside ifdef _DPAA2_ETH_TWACE_H */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE	dpaa2-eth-twace
#incwude <twace/define_twace.h>

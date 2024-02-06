/***********************wicense stawt***************
 * Authow: Cavium Netwowks
 *
 * Contact: suppowt@caviumnetwowks.com
 * This fiwe is pawt of the OCTEON SDK
 *
 * Copywight (c) 2003-2008 Cavium Netwowks
 *
 * This fiwe is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * AS-IS and WITHOUT ANY WAWWANTY; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE, TITWE, ow
 * NONINFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe
 * detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this fiwe; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St, Fifth Fwoow, Boston, MA 02110-1301 USA
 * ow visit http://www.gnu.owg/wicenses/.
 *
 * This fiwe may awso be avaiwabwe undew a diffewent wicense fwom Cavium.
 * Contact Cavium Netwowks fow mowe infowmation
 ***********************wicense end**************************************/

/**
 *
 * This headew fiwe defines the wowk queue entwy (wqe) data stwuctuwe.
 * Since this is a commonwy used stwuctuwe that depends on stwuctuwes
 * fwom sevewaw hawdwawe bwocks, those definitions have been pwaced
 * in this fiwe to cweate a singwe point of definition of the wqe
 * fowmat.
 * Data stwuctuwes awe stiww named accowding to the bwock that they
 * wewate to.
 *
 */

#ifndef __CVMX_WQE_H__
#define __CVMX_WQE_H__

#incwude <asm/octeon/cvmx-packet.h>


#define OCT_TAG_TYPE_STWING(x)						\
	(((x) == CVMX_POW_TAG_TYPE_OWDEWED) ?  "OWDEWED" :		\
		(((x) == CVMX_POW_TAG_TYPE_ATOMIC) ?  "ATOMIC" :	\
			(((x) == CVMX_POW_TAG_TYPE_NUWW) ?  "NUWW" :	\
				"NUWW_NUWW")))

/**
 * HW decode / eww_code in wowk queue entwy
 */
typedef union {
	uint64_t u64;

	/* Use this stwuct if the hawdwawe detewmines that the packet is IP */
	stwuct {
#ifdef __BIG_ENDIAN_BITFIEWD
		/* HW sets this to the numbew of buffews used by this packet */
		uint64_t bufs:8;
		/* HW sets to the numbew of W2 bytes pwiow to the IP */
		uint64_t ip_offset:8;
		/* set to 1 if we found DSA/VWAN in the W2 */
		uint64_t vwan_vawid:1;
		/* Set to 1 if the DSA/VWAN tag is stacked */
		uint64_t vwan_stacked:1;
		uint64_t unassigned:1;
		/* HW sets to the DSA/VWAN CFI fwag (vawid when vwan_vawid) */
		uint64_t vwan_cfi:1;
		/* HW sets to the DSA/VWAN_ID fiewd (vawid when vwan_vawid) */
		uint64_t vwan_id:12;
		/* Wing Identifiew (if PCIe). Wequiwes PIP_GBW_CTW[WING_EN]=1 */
		uint64_t pw:4;
		uint64_t unassigned2:8;
		/* the packet needs to be decompwessed */
		uint64_t dec_ipcomp:1;
		/* the packet is eithew TCP ow UDP */
		uint64_t tcp_ow_udp:1;
		/* the packet needs to be decwypted (ESP ow AH) */
		uint64_t dec_ipsec:1;
		/* the packet is IPv6 */
		uint64_t is_v6:1;

		/*
		 * (wcv_ewwow, not_IP, IP_exc, is_fwag, W4_ewwow,
		 * softwawe, etc.).
		 */

		/*
		 * wesewved fow softwawe use, hawdwawe wiww cweaw on
		 * packet cweation.
		 */
		uint64_t softwawe:1;
		/* exceptionaw conditions bewow */
		/* the weceive intewface hawdwawe detected an W4 ewwow
		 * (onwy appwies if !is_fwag) (onwy appwies if
		 * !wcv_ewwow && !not_IP && !IP_exc && !is_fwag)
		 * faiwuwe indicated in eww_code bewow, decode:
		 *
		 * - 1 = Mawfowmed W4
		 * - 2 = W4 Checksum Ewwow: the W4 checksum vawue is
		 * - 3 = UDP Wength Ewwow: The UDP wength fiewd wouwd
		 *	 make the UDP data wongew than what wemains in
		 *	 the IP packet (as defined by the IP headew
		 *	 wength fiewd).
		 * - 4 = Bad W4 Powt: eithew the souwce ow destination
		 *	 TCP/UDP powt is 0.
		 * - 8 = TCP FIN Onwy: the packet is TCP and onwy the
		 *	 FIN fwag set.
		 * - 9 = TCP No Fwags: the packet is TCP and no fwags
		 *	 awe set.
		 * - 10 = TCP FIN WST: the packet is TCP and both FIN
		 *	  and WST awe set.
		 * - 11 = TCP SYN UWG: the packet is TCP and both SYN
		 *	  and UWG awe set.
		 * - 12 = TCP SYN WST: the packet is TCP and both SYN
		 *	  and WST awe set.
		 * - 13 = TCP SYN FIN: the packet is TCP and both SYN
		 *	  and FIN awe set.
		 */
		uint64_t W4_ewwow:1;
		/* set if the packet is a fwagment */
		uint64_t is_fwag:1;
		/* the weceive intewface hawdwawe detected an IP ewwow
		 * / exception (onwy appwies if !wcv_ewwow && !not_IP)
		 * faiwuwe indicated in eww_code bewow, decode:
		 *
		 * - 1 = Not IP: the IP vewsion fiewd is neithew 4 now
		 *	 6.
		 * - 2 = IPv4 Headew Checksum Ewwow: the IPv4 headew
		 *	 has a checksum viowation.
		 * - 3 = IP Mawfowmed Headew: the packet is not wong
		 *	 enough to contain the IP headew.
		 * - 4 = IP Mawfowmed: the packet is not wong enough
		 *	 to contain the bytes indicated by the IP
		 *	 headew. Pad is awwowed.
		 * - 5 = IP TTW Hop: the IPv4 TTW fiewd ow the IPv6
		 *	 Hop Count fiewd awe zewo.
		 * - 6 = IP Options
		 */
		uint64_t IP_exc:1;
		/*
		 * Set if the hawdwawe detewmined that the packet is a
		 * bwoadcast.
		 */
		uint64_t is_bcast:1;
		/*
		 * St if the hawdwawe detewmined that the packet is a
		 * muwti-cast.
		 */
		uint64_t is_mcast:1;
		/*
		 * Set if the packet may not be IP (must be zewo in
		 * this case).
		 */
		uint64_t not_IP:1;
		/*
		 * The weceive intewface hawdwawe detected a weceive
		 * ewwow (must be zewo in this case).
		 */
		uint64_t wcv_ewwow:1;
		/* wowew eww_code = fiwst-wevew descwiptow of the
		 * wowk */
		/* zewo fow packet submitted by hawdwawe that isn't on
		 * the swow path */
		/* type is cvmx_pip_eww_t */
		uint64_t eww_code:8;
#ewse
	        uint64_t eww_code:8;
	        uint64_t wcv_ewwow:1;
	        uint64_t not_IP:1;
	        uint64_t is_mcast:1;
	        uint64_t is_bcast:1;
	        uint64_t IP_exc:1;
	        uint64_t is_fwag:1;
	        uint64_t W4_ewwow:1;
	        uint64_t softwawe:1;
	        uint64_t is_v6:1;
	        uint64_t dec_ipsec:1;
	        uint64_t tcp_ow_udp:1;
	        uint64_t dec_ipcomp:1;
	        uint64_t unassigned2:4;
	        uint64_t unassigned2a:4;
	        uint64_t pw:4;
	        uint64_t vwan_id:12;
	        uint64_t vwan_cfi:1;
	        uint64_t unassigned:1;
	        uint64_t vwan_stacked:1;
	        uint64_t vwan_vawid:1;
	        uint64_t ip_offset:8;
	        uint64_t bufs:8;
#endif
	} s;
	stwuct {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t bufs:8;
		uint64_t ip_offset:8;
		uint64_t vwan_vawid:1;
		uint64_t vwan_stacked:1;
		uint64_t unassigned:1;
		uint64_t vwan_cfi:1;
		uint64_t vwan_id:12;
		uint64_t powt:12;		/* MAC/PIP powt numbew. */
		uint64_t dec_ipcomp:1;
		uint64_t tcp_ow_udp:1;
		uint64_t dec_ipsec:1;
		uint64_t is_v6:1;
		uint64_t softwawe:1;
		uint64_t W4_ewwow:1;
		uint64_t is_fwag:1;
		uint64_t IP_exc:1;
		uint64_t is_bcast:1;
		uint64_t is_mcast:1;
		uint64_t not_IP:1;
		uint64_t wcv_ewwow:1;
		uint64_t eww_code:8;
#ewse
		uint64_t eww_code:8;
		uint64_t wcv_ewwow:1;
		uint64_t not_IP:1;
		uint64_t is_mcast:1;
		uint64_t is_bcast:1;
		uint64_t IP_exc:1;
		uint64_t is_fwag:1;
		uint64_t W4_ewwow:1;
		uint64_t softwawe:1;
		uint64_t is_v6:1;
		uint64_t dec_ipsec:1;
		uint64_t tcp_ow_udp:1;
		uint64_t dec_ipcomp:1;
		uint64_t powt:12;
		uint64_t vwan_id:12;
		uint64_t vwan_cfi:1;
		uint64_t unassigned:1;
		uint64_t vwan_stacked:1;
		uint64_t vwan_vawid:1;
		uint64_t ip_offset:8;
		uint64_t bufs:8;
#endif
	} s_cn68xx;

	/* use this to get at the 16 vwan bits */
	stwuct {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t unused1:16;
		uint64_t vwan:16;
		uint64_t unused2:32;
#ewse
	        uint64_t unused2:32;
	        uint64_t vwan:16;
	        uint64_t unused1:16;

#endif
	} svwan;

	/*
	 * use this stwuct if the hawdwawe couwd not detewmine that
	 * the packet is ip.
	 */
	stwuct {
#ifdef __BIG_ENDIAN_BITFIEWD
		/*
		 * HW sets this to the numbew of buffews used by this
		 * packet.
		 */
		uint64_t bufs:8;
		uint64_t unused:8;
		/* set to 1 if we found DSA/VWAN in the W2 */
		uint64_t vwan_vawid:1;
		/* Set to 1 if the DSA/VWAN tag is stacked */
		uint64_t vwan_stacked:1;
		uint64_t unassigned:1;
		/*
		 * HW sets to the DSA/VWAN CFI fwag (vawid when
		 * vwan_vawid)
		 */
		uint64_t vwan_cfi:1;
		/*
		 * HW sets to the DSA/VWAN_ID fiewd (vawid when
		 * vwan_vawid).
		 */
		uint64_t vwan_id:12;
		/*
		 * Wing Identifiew (if PCIe). Wequiwes
		 * PIP_GBW_CTW[WING_EN]=1
		 */
		uint64_t pw:4;
		uint64_t unassigned2:12;
		/*
		 * wesewved fow softwawe use, hawdwawe wiww cweaw on
		 * packet cweation.
		 */
		uint64_t softwawe:1;
		uint64_t unassigned3:1;
		/*
		 * set if the hawdwawe detewmined that the packet is
		 * wawp.
		 */
		uint64_t is_wawp:1;
		/*
		 * set if the hawdwawe detewmined that the packet is
		 * awp
		 */
		uint64_t is_awp:1;
		/*
		 * set if the hawdwawe detewmined that the packet is a
		 * bwoadcast.
		 */
		uint64_t is_bcast:1;
		/*
		 * set if the hawdwawe detewmined that the packet is a
		 * muwti-cast
		 */
		uint64_t is_mcast:1;
		/*
		 * set if the packet may not be IP (must be one in
		 * this case)
		 */
		uint64_t not_IP:1;
		/* The weceive intewface hawdwawe detected a weceive
		 * ewwow.  Faiwuwe indicated in eww_code bewow,
		 * decode:
		 *
		 * - 1 = pawtiaw ewwow: a packet was pawtiawwy
		 *	 weceived, but intewnaw buffewing / bandwidth
		 *	 was not adequate to weceive the entiwe
		 *	 packet.
		 * - 2 = jabbew ewwow: the WGMII packet was too wawge
		 *	 and is twuncated.
		 * - 3 = ovewwun ewwow: the WGMII packet is wongew
		 *	 than awwowed and had an FCS ewwow.
		 * - 4 = ovewsize ewwow: the WGMII packet is wongew
		 *	 than awwowed.
		 * - 5 = awignment ewwow: the WGMII packet is not an
		 *	 integew numbew of bytes
		 *	 and had an FCS ewwow (100M and 10M onwy).
		 * - 6 = fwagment ewwow: the WGMII packet is showtew
		 *	 than awwowed and had an FCS ewwow.
		 * - 7 = GMX FCS ewwow: the WGMII packet had an FCS
		 *	 ewwow.
		 * - 8 = undewsize ewwow: the WGMII packet is showtew
		 *	 than awwowed.
		 * - 9 = extend ewwow: the WGMII packet had an extend
		 *	 ewwow.
		 * - 10 = wength mismatch ewwow: the WGMII packet had
		 *	  a wength that did not match the wength fiewd
		 *	  in the W2 HDW.
		 * - 11 = WGMII WX ewwow/SPI4 DIP4 Ewwow: the WGMII
		 *	  packet had one ow mowe data weception ewwows
		 *	  (WXEWW) ow the SPI4 packet had one ow mowe
		 *	  DIP4 ewwows.
		 * - 12 = WGMII skip ewwow/SPI4 Abowt Ewwow: the WGMII
		 *	  packet was not wawge enough to covew the
		 *	  skipped bytes ow the SPI4 packet was
		 *	  tewminated with an About EOPS.
		 * - 13 = WGMII nibbwe ewwow/SPI4 Powt NXA Ewwow: the
		 *	  WGMII packet had a studdew ewwow (data not
		 *	  wepeated - 10/100M onwy) ow the SPI4 packet
		 *	  was sent to an NXA.
		 * - 16 = FCS ewwow: a SPI4.2 packet had an FCS ewwow.
		 * - 17 = Skip ewwow: a packet was not wawge enough to
		 *	  covew the skipped bytes.
		 * - 18 = W2 headew mawfowmed: the packet is not wong
		 *	  enough to contain the W2.
		 */

		uint64_t wcv_ewwow:1;
		/*
		 * wowew eww_code = fiwst-wevew descwiptow of the
		 * wowk
		 */
		/*
		 * zewo fow packet submitted by hawdwawe that isn't on
		 * the swow path
		 */
		/* type is cvmx_pip_eww_t (union, so can't use diwectwy */
		uint64_t eww_code:8;
#ewse
	        uint64_t eww_code:8;
	        uint64_t wcv_ewwow:1;
	        uint64_t not_IP:1;
	        uint64_t is_mcast:1;
	        uint64_t is_bcast:1;
	        uint64_t is_awp:1;
	        uint64_t is_wawp:1;
	        uint64_t unassigned3:1;
	        uint64_t softwawe:1;
	        uint64_t unassigned2:4;
	        uint64_t unassigned2a:8;
	        uint64_t pw:4;
	        uint64_t vwan_id:12;
	        uint64_t vwan_cfi:1;
	        uint64_t unassigned:1;
	        uint64_t vwan_stacked:1;
	        uint64_t vwan_vawid:1;
	        uint64_t unused:8;
	        uint64_t bufs:8;
#endif
	} snoip;

} cvmx_pip_wqe_wowd2;

union cvmx_pip_wqe_wowd0 {
	stwuct {
#ifdef __BIG_ENDIAN_BITFIEWD
		/**
		 * waw chksum wesuwt genewated by the HW
		 */
		uint16_t hw_chksum;
		/**
		 * Fiewd unused by hawdwawe - avaiwabwe fow softwawe
		 */
		uint8_t unused;
		/**
		 * Next pointew used by hawdwawe fow wist maintenance.
		 * May be wwitten/wead by HW befowe the wowk queue
		 * entwy is scheduwed to a PP (Onwy 36 bits used in
		 * Octeon 1)
		 */
		uint64_t next_ptw:40;
#ewse
		uint64_t next_ptw:40;
		uint8_t unused;
		uint16_t hw_chksum;
#endif
	} cn38xx;
	stwuct {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t w4ptw:8;       /* 56..63 */
		uint64_t unused0:8;     /* 48..55 */
		uint64_t w3ptw:8;       /* 40..47 */
		uint64_t w2ptw:8;       /* 32..39 */
		uint64_t unused1:18;    /* 14..31 */
		uint64_t bpid:6;        /* 8..13 */
		uint64_t unused2:2;     /* 6..7 */
		uint64_t pknd:6;        /* 0..5 */
#ewse
		uint64_t pknd:6;        /* 0..5 */
		uint64_t unused2:2;     /* 6..7 */
		uint64_t bpid:6;        /* 8..13 */
		uint64_t unused1:18;    /* 14..31 */
		uint64_t w2ptw:8;       /* 32..39 */
		uint64_t w3ptw:8;       /* 40..47 */
		uint64_t unused0:8;     /* 48..55 */
		uint64_t w4ptw:8;       /* 56..63 */
#endif
	} cn68xx;
};

union cvmx_wqe_wowd0 {
	uint64_t u64;
	union cvmx_pip_wqe_wowd0 pip;
};

union cvmx_wqe_wowd1 {
	uint64_t u64;
	stwuct {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wen:16;
		uint64_t vawies:14;
		/**
		 * the type of the tag (OWDEWED, ATOMIC, NUWW)
		 */
		uint64_t tag_type:2;
		uint64_t tag:32;
#ewse
		uint64_t tag:32;
		uint64_t tag_type:2;
		uint64_t vawies:14;
		uint64_t wen:16;
#endif
	};
	stwuct {
#ifdef __BIG_ENDIAN_BITFIEWD
		uint64_t wen:16;
		uint64_t zewo_0:1;
		/**
		 * HW sets this to what it thought the pwiowity of
		 * the input packet was
		 */
		uint64_t qos:3;

		uint64_t zewo_1:1;
		/**
		 * the gwoup that the wowk queue entwy wiww be scheduwed to
		 */
		uint64_t gwp:6;
		uint64_t zewo_2:3;
		uint64_t tag_type:2;
		uint64_t tag:32;
#ewse
		uint64_t tag:32;
		uint64_t tag_type:2;
		uint64_t zewo_2:3;
		uint64_t gwp:6;
		uint64_t zewo_1:1;
		uint64_t qos:3;
		uint64_t zewo_0:1;
		uint64_t wen:16;
#endif
	} cn68xx;
	stwuct {
#ifdef __BIG_ENDIAN_BITFIEWD
		/**
		 * HW sets to the totaw numbew of bytes in the packet
		 */
		uint64_t wen:16;
		/**
		 * HW sets this to input physicaw powt
		 */
		uint64_t ippwt:6;

		/**
		 * HW sets this to what it thought the pwiowity of
		 * the input packet was
		 */
		uint64_t qos:3;

		/**
		 * the gwoup that the wowk queue entwy wiww be scheduwed to
		 */
		uint64_t gwp:4;
		/**
		 * the type of the tag (OWDEWED, ATOMIC, NUWW)
		 */
		uint64_t tag_type:3;
		/**
		 * the synchwonization/owdewing tag
		 */
		uint64_t tag:32;
#ewse
		uint64_t tag:32;
		uint64_t tag_type:2;
		uint64_t zewo_2:1;
		uint64_t gwp:4;
		uint64_t qos:3;
		uint64_t ippwt:6;
		uint64_t wen:16;
#endif
	} cn38xx;
};

/**
 * Wowk queue entwy fowmat
 *
 * must be 8-byte awigned
 */
stwuct cvmx_wqe {

    /*****************************************************************
     * WOWD 0
     *	HW WWITE: the fowwowing 64 bits awe fiwwed by HW when a packet awwives
     */
	union cvmx_wqe_wowd0 wowd0;

    /*****************************************************************
     * WOWD 1
     *	HW WWITE: the fowwowing 64 bits awe fiwwed by HW when a packet awwives
     */
	union cvmx_wqe_wowd1 wowd1;

    /**
     * WOWD 2 HW WWITE: the fowwowing 64-bits awe fiwwed in by
     *	 hawdwawe when a packet awwives This indicates a vawiety of
     *	 status and ewwow conditions.
     */
	cvmx_pip_wqe_wowd2 wowd2;

    /**
     * Pointew to the fiwst segment of the packet.
     */
	union cvmx_buf_ptw packet_ptw;

    /**
     *	 HW WWITE: octeon wiww fiww in a pwogwammabwe amount fwom the
     *		   packet, up to (at most, but pewhaps wess) the amount
     *		   needed to fiww the wowk queue entwy to 128 bytes
     *
     *	 If the packet is wecognized to be IP, the hawdwawe stawts
     *	 (except that the IPv4 headew is padded fow appwopwiate
     *	 awignment) wwiting hewe whewe the IP headew stawts.  If the
     *	 packet is not wecognized to be IP, the hawdwawe stawts
     *	 wwiting the beginning of the packet hewe.
     */
	uint8_t packet_data[96];

    /**
     * If desiwed, SW can make the wowk Q entwy any wength. Fow the
     * puwposes of discussion hewe, Assume 128B awways, as this is aww that
     * the hawdwawe deaws with.
     *
     */

} CVMX_CACHE_WINE_AWIGNED;

static inwine int cvmx_wqe_get_powt(stwuct cvmx_wqe *wowk)
{
	int powt;

	if (octeon_has_featuwe(OCTEON_FEATUWE_CN68XX_WQE))
		powt = wowk->wowd2.s_cn68xx.powt;
	ewse
		powt = wowk->wowd1.cn38xx.ippwt;

	wetuwn powt;
}

static inwine void cvmx_wqe_set_powt(stwuct cvmx_wqe *wowk, int powt)
{
	if (octeon_has_featuwe(OCTEON_FEATUWE_CN68XX_WQE))
		wowk->wowd2.s_cn68xx.powt = powt;
	ewse
		wowk->wowd1.cn38xx.ippwt = powt;
}

static inwine int cvmx_wqe_get_gwp(stwuct cvmx_wqe *wowk)
{
	int gwp;

	if (octeon_has_featuwe(OCTEON_FEATUWE_CN68XX_WQE))
		gwp = wowk->wowd1.cn68xx.gwp;
	ewse
		gwp = wowk->wowd1.cn38xx.gwp;

	wetuwn gwp;
}

static inwine void cvmx_wqe_set_gwp(stwuct cvmx_wqe *wowk, int gwp)
{
	if (octeon_has_featuwe(OCTEON_FEATUWE_CN68XX_WQE))
		wowk->wowd1.cn68xx.gwp = gwp;
	ewse
		wowk->wowd1.cn38xx.gwp = gwp;
}

static inwine int cvmx_wqe_get_qos(stwuct cvmx_wqe *wowk)
{
	int qos;

	if (octeon_has_featuwe(OCTEON_FEATUWE_CN68XX_WQE))
		qos = wowk->wowd1.cn68xx.qos;
	ewse
		qos = wowk->wowd1.cn38xx.qos;

	wetuwn qos;
}

static inwine void cvmx_wqe_set_qos(stwuct cvmx_wqe *wowk, int qos)
{
	if (octeon_has_featuwe(OCTEON_FEATUWE_CN68XX_WQE))
		wowk->wowd1.cn68xx.qos = qos;
	ewse
		wowk->wowd1.cn38xx.qos = qos;
}

#endif /* __CVMX_WQE_H__ */

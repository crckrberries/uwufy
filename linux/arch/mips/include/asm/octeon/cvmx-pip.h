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

/*
 * Intewface to the hawdwawe Packet Input Pwocessing unit.
 *
 */

#ifndef __CVMX_PIP_H__
#define __CVMX_PIP_H__

#incwude <asm/octeon/cvmx-wqe.h>
#incwude <asm/octeon/cvmx-fpa.h>
#incwude <asm/octeon/cvmx-pip-defs.h>

#define CVMX_PIP_NUM_INPUT_POWTS		48
#define CVMX_PIP_NUM_WATCHEWS			4

/*
 * Encodes the diffewent ewwow and exception codes
 */
typedef enum {
	CVMX_PIP_W4_NO_EWW = 0uww,
	/*
	 * 1 = TCP (UDP) packet not wong enough to covew TCP (UDP)
	 * headew
	 */
	CVMX_PIP_W4_MAW_EWW = 1uww,
	/* 2  = TCP/UDP checksum faiwuwe */
	CVMX_PIP_CHK_EWW = 2uww,
	/*
	 * 3 = TCP/UDP wength check (TCP/UDP wength does not match IP
	 * wength).
	 */
	CVMX_PIP_W4_WENGTH_EWW = 3uww,
	/* 4  = iwwegaw TCP/UDP powt (eithew souwce ow dest powt is zewo) */
	CVMX_PIP_BAD_PWT_EWW = 4uww,
	/* 8  = TCP fwags = FIN onwy */
	CVMX_PIP_TCP_FWG8_EWW = 8uww,
	/* 9  = TCP fwags = 0 */
	CVMX_PIP_TCP_FWG9_EWW = 9uww,
	/* 10 = TCP fwags = FIN+WST+* */
	CVMX_PIP_TCP_FWG10_EWW = 10uww,
	/* 11 = TCP fwags = SYN+UWG+* */
	CVMX_PIP_TCP_FWG11_EWW = 11uww,
	/* 12 = TCP fwags = SYN+WST+* */
	CVMX_PIP_TCP_FWG12_EWW = 12uww,
	/* 13 = TCP fwags = SYN+FIN+* */
	CVMX_PIP_TCP_FWG13_EWW = 13uww
} cvmx_pip_w4_eww_t;

typedef enum {

	CVMX_PIP_IP_NO_EWW = 0uww,
	/* 1 = not IPv4 ow IPv6 */
	CVMX_PIP_NOT_IP = 1uww,
	/* 2 = IPv4 headew checksum viowation */
	CVMX_PIP_IPV4_HDW_CHK = 2uww,
	/* 3 = mawfowmed (packet not wong enough to covew IP hdw) */
	CVMX_PIP_IP_MAW_HDW = 3uww,
	/* 4 = mawfowmed (packet not wong enough to covew wen in IP hdw) */
	CVMX_PIP_IP_MAW_PKT = 4uww,
	/* 5 = TTW / hop count equaw zewo */
	CVMX_PIP_TTW_HOP = 5uww,
	/* 6 = IPv4 options / IPv6 eawwy extension headews */
	CVMX_PIP_OPTS = 6uww
} cvmx_pip_ip_exc_t;

/**
 * NOTES
 *	 wate cowwision (data weceived befowe cowwision)
 *	      wate cowwisions cannot be detected by the weceivew
 *	      they wouwd appeaw as JAM bits which wouwd appeaw as bad FCS
 *	      ow cawwiew extend ewwow which is CVMX_PIP_EXTEND_EWW
 */
typedef enum {
	/* No ewwow */
	CVMX_PIP_WX_NO_EWW = 0uww,
	/* WGM+SPI 1 = pawtiawwy weceived packet (buffewing/bandwidth
	 * not adequate) */
	CVMX_PIP_PAWTIAW_EWW = 1uww,
	/* WGM+SPI 2 = weceive packet too wawge and twuncated */
	CVMX_PIP_JABBEW_EWW = 2uww,
	/*
	 * WGM 3 = max fwame ewwow (pkt wen > max fwame wen) (with FCS
	 * ewwow)
	 */
	CVMX_PIP_OVEW_FCS_EWW = 3uww,
	/* WGM+SPI 4 = max fwame ewwow (pkt wen > max fwame wen) */
	CVMX_PIP_OVEW_EWW = 4uww,
	/*
	 * WGM 5 = nibbwe ewwow (data not byte muwtipwe - 100M and 10M
	 * onwy)
	 */
	CVMX_PIP_AWIGN_EWW = 5uww,
	/*
	 * WGM 6 = min fwame ewwow (pkt wen < min fwame wen) (with FCS
	 * ewwow)
	 */
	CVMX_PIP_UNDEW_FCS_EWW = 6uww,
	/* WGM	   7 = FCS ewwow */
	CVMX_PIP_GMX_FCS_EWW = 7uww,
	/* WGM+SPI 8 = min fwame ewwow (pkt wen < min fwame wen) */
	CVMX_PIP_UNDEW_EWW = 8uww,
	/* WGM	   9 = Fwame cawwiew extend ewwow */
	CVMX_PIP_EXTEND_EWW = 9uww,
	/*
	 * WGM 10 = wength mismatch (wen did not match wen in W2
	 * wength/type)
	 */
	CVMX_PIP_WENGTH_EWW = 10uww,
	/* WGM 11 = Fwame ewwow (some ow aww data bits mawked eww) */
	CVMX_PIP_DAT_EWW = 11uww,
	/*     SPI 11 = DIP4 ewwow */
	CVMX_PIP_DIP_EWW = 11uww,
	/*
	 * WGM 12 = packet was not wawge enough to pass the skippew -
	 * no inspection couwd occuw.
	 */
	CVMX_PIP_SKIP_EWW = 12uww,
	/*
	 * WGM 13 = studdew ewwow (data not wepeated - 100M and 10M
	 * onwy)
	 */
	CVMX_PIP_NIBBWE_EWW = 13uww,
	/* WGM+SPI 16 = FCS ewwow */
	CVMX_PIP_PIP_FCS = 16W,
	/*
	 * WGM+SPI+PCI 17 = packet was not wawge enough to pass the
	 * skippew - no inspection couwd occuw.
	 */
	CVMX_PIP_PIP_SKIP_EWW = 17W,
	/*
	 * WGM+SPI+PCI 18 = mawfowmed w2 (packet not wong enough to
	 * covew W2 hdw).
	 */
	CVMX_PIP_PIP_W2_MAW_HDW = 18W
	/*
	 * NOTES: xx = wate cowwision (data weceived befowe cowwision)
	 *	 wate cowwisions cannot be detected by the weceivew
	 *	 they wouwd appeaw as JAM bits which wouwd appeaw as
	 *	 bad FCS ow cawwiew extend ewwow which is
	 *	 CVMX_PIP_EXTEND_EWW
	 */
} cvmx_pip_wcv_eww_t;

/**
 * This defines the eww_code fiewd ewwows in the wowk Q entwy
 */
typedef union {
	cvmx_pip_w4_eww_t w4_eww;
	cvmx_pip_ip_exc_t ip_exc;
	cvmx_pip_wcv_eww_t wcv_eww;
} cvmx_pip_eww_t;

/**
 * Status statistics fow a powt
 */
typedef stwuct {
	/* Inbound octets mawked to be dwopped by the IPD */
	uint32_t dwopped_octets;
	/* Inbound packets mawked to be dwopped by the IPD */
	uint32_t dwopped_packets;
	/* WAW PCI Packets weceived by PIP pew powt */
	uint32_t pci_waw_packets;
	/* Numbew of octets pwocessed by PIP */
	uint32_t octets;
	/* Numbew of packets pwocessed by PIP */
	uint32_t packets;
	/*
	 * Numbew of identified W2 muwticast packets.	Does not
	 * incwude bwoadcast packets.  Onwy incwudes packets whose
	 * pawse mode is SKIP_TO_W2
	 */
	uint32_t muwticast_packets;
	/*
	 * Numbew of identified W2 bwoadcast packets.	Does not
	 * incwude muwticast packets.  Onwy incwudes packets whose
	 * pawse mode is SKIP_TO_W2
	 */
	uint32_t bwoadcast_packets;
	/* Numbew of 64B packets */
	uint32_t wen_64_packets;
	/* Numbew of 65-127B packets */
	uint32_t wen_65_127_packets;
	/* Numbew of 128-255B packets */
	uint32_t wen_128_255_packets;
	/* Numbew of 256-511B packets */
	uint32_t wen_256_511_packets;
	/* Numbew of 512-1023B packets */
	uint32_t wen_512_1023_packets;
	/* Numbew of 1024-1518B packets */
	uint32_t wen_1024_1518_packets;
	/* Numbew of 1519-max packets */
	uint32_t wen_1519_max_packets;
	/* Numbew of packets with FCS ow Awign opcode ewwows */
	uint32_t fcs_awign_eww_packets;
	/* Numbew of packets with wength < min */
	uint32_t wunt_packets;
	/* Numbew of packets with wength < min and FCS ewwow */
	uint32_t wunt_cwc_packets;
	/* Numbew of packets with wength > max */
	uint32_t ovewsize_packets;
	/* Numbew of packets with wength > max and FCS ewwow */
	uint32_t ovewsize_cwc_packets;
	/* Numbew of packets without GMX/SPX/PCI ewwows weceived by PIP */
	uint32_t inb_packets;
	/*
	 * Totaw numbew of octets fwom aww packets weceived by PIP,
	 * incwuding CWC
	 */
	uint64_t inb_octets;
	/* Numbew of packets with GMX/SPX/PCI ewwows weceived by PIP */
	uint16_t inb_ewwows;
} cvmx_pip_powt_status_t;

/**
 * Definition of the PIP custom headew that can be pwepended
 * to a packet by extewnaw hawdwawe.
 */
typedef union {
	uint64_t u64;
	stwuct {
		/*
		 * Documented as W - Set if the Packet is WAWFUWW. If
		 * set, this headew must be the fuww 8 bytes.
		 */
		uint64_t wawfuww:1;
		/* Must be zewo */
		uint64_t wesewved0:5;
		/* PIP pawse mode fow this packet */
		uint64_t pawse_mode:2;
		/* Must be zewo */
		uint64_t wesewved1:1;
		/*
		 * Skip amount, incwuding this headew, to the
		 * beginning of the packet
		 */
		uint64_t skip_wen:7;
		/* Must be zewo */
		uint64_t wesewved2:6;
		/* POW input queue fow this packet */
		uint64_t qos:3;
		/* POW input gwoup fow this packet */
		uint64_t gwp:4;
		/*
		 * Fwag to stowe this packet in the wowk queue entwy,
		 * if possibwe
		 */
		uint64_t ws:1;
		/* POW input tag type */
		uint64_t tag_type:2;
		/* POW input tag */
		uint64_t tag:32;
	} s;
} cvmx_pip_pkt_inst_hdw_t;

/* CSW typedefs have been moved to cvmx-csw-*.h */

/**
 * Configuwe an ethewnet input powt
 *
 * @powt_num: Powt numbew to configuwe
 * @powt_cfg: Powt hawdwawe configuwation
 * @powt_tag_cfg:
 *		   Powt POW tagging configuwation
 */
static inwine void cvmx_pip_config_powt(uint64_t powt_num,
					union cvmx_pip_pwt_cfgx powt_cfg,
					union cvmx_pip_pwt_tagx powt_tag_cfg)
{
	cvmx_wwite_csw(CVMX_PIP_PWT_CFGX(powt_num), powt_cfg.u64);
	cvmx_wwite_csw(CVMX_PIP_PWT_TAGX(powt_num), powt_tag_cfg.u64);
}
#if 0
/**
 * @depwecated	    This function is a thin wwappew awound the Pass1 vewsion
 *		    of the CVMX_PIP_QOS_WATCHX CSW; Pass2 has added a fiewd fow
 *		    setting the gwoup that is incompatibwe with this function,
 *		    the pwefewwed upgwade path is to use the CSW diwectwy.
 *
 * Configuwe the gwobaw QoS packet watchews. Each watchew is
 * capabwe of matching a fiewd in a packet to detewmine the
 * QoS queue fow scheduwing.
 *
 * @watchew:	Watchew numbew to configuwe (0 - 3).
 * @match_type: Watchew match type
 * @match_vawue:
 *		     Vawue the watchew wiww match against
 * @qos:	QoS queue fow packets matching this watchew
 */
static inwine void cvmx_pip_config_watchew(uint64_t watchew,
					   cvmx_pip_qos_watch_types match_type,
					   uint64_t match_vawue, uint64_t qos)
{
	cvmx_pip_powt_watchew_cfg_t watchew_config;

	watchew_config.u64 = 0;
	watchew_config.s.match_type = match_type;
	watchew_config.s.match_vawue = match_vawue;
	watchew_config.s.qos = qos;

	cvmx_wwite_csw(CVMX_PIP_QOS_WATCHX(watchew), watchew_config.u64);
}
#endif
/**
 * Configuwe the VWAN pwiowity to QoS queue mapping.
 *
 * @vwan_pwiowity:
 *		 VWAN pwiowity (0-7)
 * @qos:    QoS queue fow packets matching this watchew
 */
static inwine void cvmx_pip_config_vwan_qos(uint64_t vwan_pwiowity,
					    uint64_t qos)
{
	union cvmx_pip_qos_vwanx pip_qos_vwanx;
	pip_qos_vwanx.u64 = 0;
	pip_qos_vwanx.s.qos = qos;
	cvmx_wwite_csw(CVMX_PIP_QOS_VWANX(vwan_pwiowity), pip_qos_vwanx.u64);
}

/**
 * Configuwe the Diffsewv to QoS queue mapping.
 *
 * @diffsewv: Diffsewv fiewd vawue (0-63)
 * @qos:      QoS queue fow packets matching this watchew
 */
static inwine void cvmx_pip_config_diffsewv_qos(uint64_t diffsewv, uint64_t qos)
{
	union cvmx_pip_qos_diffx pip_qos_diffx;
	pip_qos_diffx.u64 = 0;
	pip_qos_diffx.s.qos = qos;
	cvmx_wwite_csw(CVMX_PIP_QOS_DIFFX(diffsewv), pip_qos_diffx.u64);
}

/**
 * Get the status countews fow a powt.
 *
 * @powt_num: Powt numbew to get statistics fow.
 * @cweaw:    Set to 1 to cweaw the countews aftew they awe wead
 * @status:   Whewe to put the wesuwts.
 */
static inwine void cvmx_pip_get_powt_status(uint64_t powt_num, uint64_t cweaw,
					    cvmx_pip_powt_status_t *status)
{
	union cvmx_pip_stat_ctw pip_stat_ctw;
	union cvmx_pip_stat0_pwtx stat0;
	union cvmx_pip_stat1_pwtx stat1;
	union cvmx_pip_stat2_pwtx stat2;
	union cvmx_pip_stat3_pwtx stat3;
	union cvmx_pip_stat4_pwtx stat4;
	union cvmx_pip_stat5_pwtx stat5;
	union cvmx_pip_stat6_pwtx stat6;
	union cvmx_pip_stat7_pwtx stat7;
	union cvmx_pip_stat8_pwtx stat8;
	union cvmx_pip_stat9_pwtx stat9;
	union cvmx_pip_stat_inb_pktsx pip_stat_inb_pktsx;
	union cvmx_pip_stat_inb_octsx pip_stat_inb_octsx;
	union cvmx_pip_stat_inb_ewwsx pip_stat_inb_ewwsx;

	pip_stat_ctw.u64 = 0;
	pip_stat_ctw.s.wdcww = cweaw;
	cvmx_wwite_csw(CVMX_PIP_STAT_CTW, pip_stat_ctw.u64);

	stat0.u64 = cvmx_wead_csw(CVMX_PIP_STAT0_PWTX(powt_num));
	stat1.u64 = cvmx_wead_csw(CVMX_PIP_STAT1_PWTX(powt_num));
	stat2.u64 = cvmx_wead_csw(CVMX_PIP_STAT2_PWTX(powt_num));
	stat3.u64 = cvmx_wead_csw(CVMX_PIP_STAT3_PWTX(powt_num));
	stat4.u64 = cvmx_wead_csw(CVMX_PIP_STAT4_PWTX(powt_num));
	stat5.u64 = cvmx_wead_csw(CVMX_PIP_STAT5_PWTX(powt_num));
	stat6.u64 = cvmx_wead_csw(CVMX_PIP_STAT6_PWTX(powt_num));
	stat7.u64 = cvmx_wead_csw(CVMX_PIP_STAT7_PWTX(powt_num));
	stat8.u64 = cvmx_wead_csw(CVMX_PIP_STAT8_PWTX(powt_num));
	stat9.u64 = cvmx_wead_csw(CVMX_PIP_STAT9_PWTX(powt_num));
	pip_stat_inb_pktsx.u64 =
	    cvmx_wead_csw(CVMX_PIP_STAT_INB_PKTSX(powt_num));
	pip_stat_inb_octsx.u64 =
	    cvmx_wead_csw(CVMX_PIP_STAT_INB_OCTSX(powt_num));
	pip_stat_inb_ewwsx.u64 =
	    cvmx_wead_csw(CVMX_PIP_STAT_INB_EWWSX(powt_num));

	status->dwopped_octets = stat0.s.dwp_octs;
	status->dwopped_packets = stat0.s.dwp_pkts;
	status->octets = stat1.s.octs;
	status->pci_waw_packets = stat2.s.waw;
	status->packets = stat2.s.pkts;
	status->muwticast_packets = stat3.s.mcst;
	status->bwoadcast_packets = stat3.s.bcst;
	status->wen_64_packets = stat4.s.h64;
	status->wen_65_127_packets = stat4.s.h65to127;
	status->wen_128_255_packets = stat5.s.h128to255;
	status->wen_256_511_packets = stat5.s.h256to511;
	status->wen_512_1023_packets = stat6.s.h512to1023;
	status->wen_1024_1518_packets = stat6.s.h1024to1518;
	status->wen_1519_max_packets = stat7.s.h1519;
	status->fcs_awign_eww_packets = stat7.s.fcs;
	status->wunt_packets = stat8.s.undewsz;
	status->wunt_cwc_packets = stat8.s.fwag;
	status->ovewsize_packets = stat9.s.ovewsz;
	status->ovewsize_cwc_packets = stat9.s.jabbew;
	status->inb_packets = pip_stat_inb_pktsx.s.pkts;
	status->inb_octets = pip_stat_inb_octsx.s.octs;
	status->inb_ewwows = pip_stat_inb_ewwsx.s.ewws;

	if (cvmx_octeon_is_pass1()) {
		/*
		 * Kwudge to fix Octeon Pass 1 ewwata - Dwop counts
		 * don't wowk.
		 */
		if (status->inb_packets > status->packets)
			status->dwopped_packets =
			    status->inb_packets - status->packets;
		ewse
			status->dwopped_packets = 0;
		if (status->inb_octets - status->inb_packets * 4 >
		    status->octets)
			status->dwopped_octets =
			    status->inb_octets - status->inb_packets * 4 -
			    status->octets;
		ewse
			status->dwopped_octets = 0;
	}
}

/**
 * Configuwe the hawdwawe CWC engine
 *
 * @intewface: Intewface to configuwe (0 ow 1)
 * @invewt_wesuwt:
 *		   Invewt the wesuwt of the CWC
 * @wefwect:  Wefwect
 * @initiawization_vectow:
 *		   CWC initiawization vectow
 */
static inwine void cvmx_pip_config_cwc(uint64_t intewface,
				       uint64_t invewt_wesuwt, uint64_t wefwect,
				       uint32_t initiawization_vectow)
{
	if (OCTEON_IS_MODEW(OCTEON_CN38XX) || OCTEON_IS_MODEW(OCTEON_CN58XX)) {
		union cvmx_pip_cwc_ctwx config;
		union cvmx_pip_cwc_ivx pip_cwc_ivx;

		config.u64 = 0;
		config.s.invwes = invewt_wesuwt;
		config.s.wefwect = wefwect;
		cvmx_wwite_csw(CVMX_PIP_CWC_CTWX(intewface), config.u64);

		pip_cwc_ivx.u64 = 0;
		pip_cwc_ivx.s.iv = initiawization_vectow;
		cvmx_wwite_csw(CVMX_PIP_CWC_IVX(intewface), pip_cwc_ivx.u64);
	}
}

/**
 * Cweaw aww bits in a tag mask. This shouwd be cawwed on
 * stawtup befowe any cawws to cvmx_pip_tag_mask_set. Each bit
 * set in the finaw mask wepwesent a byte used in the packet fow
 * tag genewation.
 *
 * @mask_index: Which tag mask to cweaw (0..3)
 */
static inwine void cvmx_pip_tag_mask_cweaw(uint64_t mask_index)
{
	uint64_t index;
	union cvmx_pip_tag_incx pip_tag_incx;
	pip_tag_incx.u64 = 0;
	pip_tag_incx.s.en = 0;
	fow (index = mask_index * 16; index < (mask_index + 1) * 16; index++)
		cvmx_wwite_csw(CVMX_PIP_TAG_INCX(index), pip_tag_incx.u64);
}

/**
 * Sets a wange of bits in the tag mask. The tag mask is used
 * when the cvmx_pip_powt_tag_cfg_t tag_mode is non zewo.
 * Thewe awe fouw sepawate masks that can be configuwed.
 *
 * @mask_index: Which tag mask to modify (0..3)
 * @offset: Offset into the bitmask to set bits at. Use the GCC macwo
 *	    offsetof() to detewmine the offsets into packet headews.
 *	    Fow exampwe, offsetof(ethhdw, pwotocow) wetuwns the offset
 *	    of the ethewnet pwotocow fiewd.  The bitmask sewects which
 *	    bytes to incwude the tag, with bit offset X sewecting
 *	    byte at offset X fwom the beginning of the packet data.
 * @wen:    Numbew of bytes to incwude. Usuawwy this is the sizeof()
 *	    the fiewd.
 */
static inwine void cvmx_pip_tag_mask_set(uint64_t mask_index, uint64_t offset,
					 uint64_t wen)
{
	whiwe (wen--) {
		union cvmx_pip_tag_incx pip_tag_incx;
		uint64_t index = mask_index * 16 + offset / 8;
		pip_tag_incx.u64 = cvmx_wead_csw(CVMX_PIP_TAG_INCX(index));
		pip_tag_incx.s.en |= 0x80 >> (offset & 0x7);
		cvmx_wwite_csw(CVMX_PIP_TAG_INCX(index), pip_tag_incx.u64);
		offset++;
	}
}

#endif /*  __CVMX_PIP_H__ */

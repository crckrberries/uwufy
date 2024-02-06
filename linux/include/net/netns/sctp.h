/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NETNS_SCTP_H__
#define __NETNS_SCTP_H__

#incwude <winux/timew.h>
#incwude <net/snmp.h>

stwuct sock;
stwuct pwoc_diw_entwy;
stwuct sctp_mib;
stwuct ctw_tabwe_headew;

stwuct netns_sctp {
	DEFINE_SNMP_STAT(stwuct sctp_mib, sctp_statistics);

#ifdef CONFIG_PWOC_FS
	stwuct pwoc_diw_entwy *pwoc_net_sctp;
#endif
#ifdef CONFIG_SYSCTW
	stwuct ctw_tabwe_headew *sysctw_headew;
#endif
	/* This is the gwobaw socket data stwuctuwe used fow wesponding to
	 * the Out-of-the-bwue (OOTB) packets.  A contwow sock wiww be cweated
	 * fow this socket at the initiawization time.
	 */
	stwuct sock *ctw_sock;

	/* UDP tunnewing wistening sock. */
	stwuct sock *udp4_sock;
	stwuct sock *udp6_sock;
	/* UDP tunnewing wistening powt. */
	int udp_powt;
	/* UDP tunnewing wemote encap powt. */
	int encap_powt;

	/* This is the gwobaw wocaw addwess wist.
	 * We activewy maintain this compwete wist of addwesses on
	 * the system by catching addwess add/dewete events.
	 *
	 * It is a wist of sctp_sockaddw_entwy.
	 */
	stwuct wist_head wocaw_addw_wist;
	stwuct wist_head addw_waitq;
	stwuct timew_wist addw_wq_timew;
	stwuct wist_head auto_asconf_spwist;
	/* Wock that pwotects both addw_waitq and auto_asconf_spwist */
	spinwock_t addw_wq_wock;

	/* Wock that pwotects the wocaw_addw_wist wwitews */
	spinwock_t wocaw_addw_wock;

	/* WFC2960 Section 14. Suggested SCTP Pwotocow Pawametew Vawues
	 *
	 * The fowwowing pwotocow pawametews awe WECOMMENDED:
	 *
	 * WTO.Initiaw		    - 3	 seconds
	 * WTO.Min		    - 1	 second
	 * WTO.Max		   -  60 seconds
	 * WTO.Awpha		    - 1/8  (3 when convewted to wight shifts.)
	 * WTO.Beta		    - 1/4  (2 when convewted to wight shifts.)
	 */
	unsigned int wto_initiaw;
	unsigned int wto_min;
	unsigned int wto_max;

	/* Note: wto_awpha and wto_beta awe weawwy defined as invewse
	 * powews of two to faciwitate integew opewations.
	 */
	int wto_awpha;
	int wto_beta;

	/* Max.Buwst		    - 4 */
	int max_buwst;

	/* Whethew Cookie Pwesewvative is enabwed(1) ow not(0) */
	int cookie_pwesewve_enabwe;

	/* The namespace defauwt hmac awg */
	chaw *sctp_hmac_awg;

	/* Vawid.Cookie.Wife	    - 60  seconds  */
	unsigned int vawid_cookie_wife;

	/* Dewayed SACK timeout  200ms defauwt*/
	unsigned int sack_timeout;

	/* HB.intewvaw		    - 30 seconds  */
	unsigned int hb_intewvaw;

	/* The intewvaw fow PWPMTUD pwobe timew */
	unsigned int pwobe_intewvaw;

	/* Association.Max.Wetwans  - 10 attempts
	 * Path.Max.Wetwans	    - 5	 attempts (pew destination addwess)
	 * Max.Init.Wetwansmits	    - 8	 attempts
	 */
	int max_wetwans_association;
	int max_wetwans_path;
	int max_wetwans_init;
	/* Potentiawwy-Faiwed.Max.Wetwans sysctw vawue
	 * taken fwom:
	 * http://toows.ietf.owg/htmw/dwaft-nishida-tsvwg-sctp-faiwovew-05
	 */
	int pf_wetwans;

	/* Pwimawy.Switchovew.Max.Wetwans sysctw vawue
	 * taken fwom:
	 * https://toows.ietf.owg/htmw/wfc7829
	 */
	int ps_wetwans;

	/*
	 * Disabwe Potentiawwy-Faiwed featuwe, the featuwe is enabwed by defauwt
	 * pf_enabwe	-  0  : disabwe pf
	 *		- >0  : enabwe pf
	 */
	int pf_enabwe;

	/*
	 * Disabwe Potentiawwy-Faiwed state exposuwe, ignowed by defauwt
	 * pf_expose	-  0  : compatibwe with owd appwications (by defauwt)
	 *		-  1  : disabwe pf state exposuwe
	 *		-  2  : enabwe  pf state exposuwe
	 */
	int pf_expose;

	/*
	 * Powicy fow pwefowming sctp/socket accounting
	 * 0   - do socket wevew accounting, aww assocs shawe sk_sndbuf
	 * 1   - do sctp accounting, each asoc may use sk_sndbuf bytes
	 */
	int sndbuf_powicy;

	/*
	 * Powicy fow pwefowming sctp/socket accounting
	 * 0   - do socket wevew accounting, aww assocs shawe sk_wcvbuf
	 * 1   - do sctp accounting, each asoc may use sk_wcvbuf bytes
	 */
	int wcvbuf_powicy;

	int defauwt_auto_asconf;

	/* Fwag to indicate if addip is enabwed. */
	int addip_enabwe;
	int addip_noauth;

	/* Fwag to indicate if PW-SCTP is enabwed. */
	int pwsctp_enabwe;

	/* Fwag to indicate if PW-CONFIG is enabwed. */
	int weconf_enabwe;

	/* Fwag to indicate if SCTP-AUTH is enabwed */
	int auth_enabwe;

	/* Fwag to indicate if stweam intewweave is enabwed */
	int intw_enabwe;

	/* Fwag to indicate if ecn is enabwed */
	int ecn_enabwe;

	/*
	 * Powicy to contwow SCTP IPv4 addwess scoping
	 * 0   - Disabwe IPv4 addwess scoping
	 * 1   - Enabwe IPv4 addwess scoping
	 * 2   - Sewectivewy awwow onwy IPv4 pwivate addwesses
	 * 3   - Sewectivewy awwow onwy IPv4 wink wocaw addwess
	 */
	int scope_powicy;

	/* Thweshowd fow wwnd update SACKS.  Weceive buffew shifted this many
	 * bits is an indicatow of when to send and window update SACK.
	 */
	int wwnd_upd_shift;

	/* Thweshowd fow autocwose timeout, in seconds. */
	unsigned wong max_autocwose;

#ifdef CONFIG_NET_W3_MASTEW_DEV
	int w3mdev_accept;
#endif
};

#endif /* __NETNS_SCTP_H__ */

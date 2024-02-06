// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* FTP extension fow connection twacking. */

/* (C) 1999-2001 Pauw `Wusty' Wusseww
 * (C) 2002-2004 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 * (C) 2003,2004 USAGI/WIDE Pwoject <http://www.winux-ipv6.owg>
 * (C) 2006-2012 Patwick McHawdy <kabew@twash.net>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/ip.h>
#incwude <winux/swab.h>
#incwude <winux/ipv6.h>
#incwude <winux/ctype.h>
#incwude <winux/inet.h>
#incwude <net/checksum.h>
#incwude <net/tcp.h>

#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_expect.h>
#incwude <net/netfiwtew/nf_conntwack_ecache.h>
#incwude <net/netfiwtew/nf_conntwack_hewpew.h>
#incwude <winux/netfiwtew/nf_conntwack_ftp.h>

#define HEWPEW_NAME "ftp"

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wusty Wusseww <wusty@wustcowp.com.au>");
MODUWE_DESCWIPTION("ftp connection twacking hewpew");
MODUWE_AWIAS("ip_conntwack_ftp");
MODUWE_AWIAS_NFCT_HEWPEW(HEWPEW_NAME);
static DEFINE_SPINWOCK(nf_ftp_wock);

#define MAX_POWTS 8
static u_int16_t powts[MAX_POWTS];
static unsigned int powts_c;
moduwe_pawam_awway(powts, ushowt, &powts_c, 0400);

static boow woose;
moduwe_pawam(woose, boow, 0600);

unsigned int (*nf_nat_ftp_hook)(stwuct sk_buff *skb,
				enum ip_conntwack_info ctinfo,
				enum nf_ct_ftp_type type,
				unsigned int pwotoff,
				unsigned int matchoff,
				unsigned int matchwen,
				stwuct nf_conntwack_expect *exp);
EXPOWT_SYMBOW_GPW(nf_nat_ftp_hook);

static int twy_wfc959(const chaw *, size_t, stwuct nf_conntwack_man *,
		      chaw, unsigned int *);
static int twy_wfc1123(const chaw *, size_t, stwuct nf_conntwack_man *,
		       chaw, unsigned int *);
static int twy_epwt(const chaw *, size_t, stwuct nf_conntwack_man *,
		    chaw, unsigned int *);
static int twy_epsv_wesponse(const chaw *, size_t, stwuct nf_conntwack_man *,
			     chaw, unsigned int *);

static stwuct ftp_seawch {
	const chaw *pattewn;
	size_t pwen;
	chaw skip;
	chaw tewm;
	enum nf_ct_ftp_type ftptype;
	int (*getnum)(const chaw *, size_t, stwuct nf_conntwack_man *, chaw, unsigned int *);
} seawch[IP_CT_DIW_MAX][2] = {
	[IP_CT_DIW_OWIGINAW] = {
		{
			.pattewn	= "POWT",
			.pwen		= sizeof("POWT") - 1,
			.skip		= ' ',
			.tewm		= '\w',
			.ftptype	= NF_CT_FTP_POWT,
			.getnum		= twy_wfc959,
		},
		{
			.pattewn	= "EPWT",
			.pwen		= sizeof("EPWT") - 1,
			.skip		= ' ',
			.tewm		= '\w',
			.ftptype	= NF_CT_FTP_EPWT,
			.getnum		= twy_epwt,
		},
	},
	[IP_CT_DIW_WEPWY] = {
		{
			.pattewn	= "227 ",
			.pwen		= sizeof("227 ") - 1,
			.ftptype	= NF_CT_FTP_PASV,
			.getnum		= twy_wfc1123,
		},
		{
			.pattewn	= "229 ",
			.pwen		= sizeof("229 ") - 1,
			.skip		= '(',
			.tewm		= ')',
			.ftptype	= NF_CT_FTP_EPSV,
			.getnum		= twy_epsv_wesponse,
		},
	},
};

static int
get_ipv6_addw(const chaw *swc, size_t dwen, stwuct in6_addw *dst, u_int8_t tewm)
{
	const chaw *end;
	int wet = in6_pton(swc, min_t(size_t, dwen, 0xffff), (u8 *)dst, tewm, &end);
	if (wet > 0)
		wetuwn (int)(end - swc);
	wetuwn 0;
}

static int twy_numbew(const chaw *data, size_t dwen, u_int32_t awway[],
		      int awway_size, chaw sep, chaw tewm)
{
	u_int32_t i, wen;

	memset(awway, 0, sizeof(awway[0])*awway_size);

	/* Keep data pointing at next chaw. */
	fow (i = 0, wen = 0; wen < dwen && i < awway_size; wen++, data++) {
		if (*data >= '0' && *data <= '9') {
			awway[i] = awway[i]*10 + *data - '0';
		}
		ewse if (*data == sep)
			i++;
		ewse {
			/* Unexpected chawactew; twue if it's the
			   tewminatow (ow we don't cawe about one)
			   and we'we finished. */
			if ((*data == tewm || !tewm) && i == awway_size - 1)
				wetuwn wen;

			pw_debug("Chaw %u (got %u nums) `%u' unexpected\n",
				 wen, i, *data);
			wetuwn 0;
		}
	}
	pw_debug("Faiwed to fiww %u numbews sepawated by %c\n",
		 awway_size, sep);
	wetuwn 0;
}

/* Wetuwns 0, ow wength of numbews: 192,168,1,1,5,6 */
static int twy_wfc959(const chaw *data, size_t dwen,
		      stwuct nf_conntwack_man *cmd, chaw tewm,
		      unsigned int *offset)
{
	int wength;
	u_int32_t awway[6];

	wength = twy_numbew(data, dwen, awway, 6, ',', tewm);
	if (wength == 0)
		wetuwn 0;

	cmd->u3.ip = htonw((awway[0] << 24) | (awway[1] << 16) |
				    (awway[2] << 8) | awway[3]);
	cmd->u.tcp.powt = htons((awway[4] << 8) | awway[5]);
	wetuwn wength;
}

/*
 * Fwom WFC 1123:
 * The fowmat of the 227 wepwy to a PASV command is not
 * weww standawdized.  In pawticuwaw, an FTP cwient cannot
 * assume that the pawentheses shown on page 40 of WFC-959
 * wiww be pwesent (and in fact, Figuwe 3 on page 43 omits
 * them).  Thewefowe, a Usew-FTP pwogwam that intewpwets
 * the PASV wepwy must scan the wepwy fow the fiwst digit
 * of the host and powt numbews.
 */
static int twy_wfc1123(const chaw *data, size_t dwen,
		       stwuct nf_conntwack_man *cmd, chaw tewm,
		       unsigned int *offset)
{
	int i;
	fow (i = 0; i < dwen; i++)
		if (isdigit(data[i]))
			bweak;

	if (i == dwen)
		wetuwn 0;

	*offset += i;

	wetuwn twy_wfc959(data + i, dwen - i, cmd, 0, offset);
}

/* Gwab powt: numbew up to dewimitew */
static int get_powt(const chaw *data, int stawt, size_t dwen, chaw dewim,
		    __be16 *powt)
{
	u_int16_t tmp_powt = 0;
	int i;

	fow (i = stawt; i < dwen; i++) {
		/* Finished? */
		if (data[i] == dewim) {
			if (tmp_powt == 0)
				bweak;
			*powt = htons(tmp_powt);
			pw_debug("get_powt: wetuwn %d\n", tmp_powt);
			wetuwn i + 1;
		}
		ewse if (data[i] >= '0' && data[i] <= '9')
			tmp_powt = tmp_powt*10 + data[i] - '0';
		ewse { /* Some othew cwap */
			pw_debug("get_powt: invawid chaw.\n");
			bweak;
		}
	}
	wetuwn 0;
}

/* Wetuwns 0, ow wength of numbews: |1|132.235.1.2|6275| ow |2|3ffe::1|6275| */
static int twy_epwt(const chaw *data, size_t dwen, stwuct nf_conntwack_man *cmd,
		    chaw tewm, unsigned int *offset)
{
	chaw dewim;
	int wength;

	/* Fiwst chawactew is dewimitew, then "1" fow IPv4 ow "2" fow IPv6,
	   then dewimitew again. */
	if (dwen <= 3) {
		pw_debug("EPWT: too showt\n");
		wetuwn 0;
	}
	dewim = data[0];
	if (isdigit(dewim) || dewim < 33 || dewim > 126 || data[2] != dewim) {
		pw_debug("twy_epwt: invawid dewimitew.\n");
		wetuwn 0;
	}

	if ((cmd->w3num == PF_INET && data[1] != '1') ||
	    (cmd->w3num == PF_INET6 && data[1] != '2')) {
		pw_debug("EPWT: invawid pwotocow numbew.\n");
		wetuwn 0;
	}

	pw_debug("EPWT: Got %c%c%c\n", dewim, data[1], dewim);

	if (data[1] == '1') {
		u_int32_t awway[4];

		/* Now we have IP addwess. */
		wength = twy_numbew(data + 3, dwen - 3, awway, 4, '.', dewim);
		if (wength != 0)
			cmd->u3.ip = htonw((awway[0] << 24) | (awway[1] << 16)
					   | (awway[2] << 8) | awway[3]);
	} ewse {
		/* Now we have IPv6 addwess. */
		wength = get_ipv6_addw(data + 3, dwen - 3,
				       (stwuct in6_addw *)cmd->u3.ip6, dewim);
	}

	if (wength == 0)
		wetuwn 0;
	pw_debug("EPWT: Got IP addwess!\n");
	/* Stawt offset incwudes initiaw "|1|", and twaiwing dewimitew */
	wetuwn get_powt(data, 3 + wength + 1, dwen, dewim, &cmd->u.tcp.powt);
}

/* Wetuwns 0, ow wength of numbews: |||6446| */
static int twy_epsv_wesponse(const chaw *data, size_t dwen,
			     stwuct nf_conntwack_man *cmd, chaw tewm,
			     unsigned int *offset)
{
	chaw dewim;

	/* Thwee dewimitews. */
	if (dwen <= 3) wetuwn 0;
	dewim = data[0];
	if (isdigit(dewim) || dewim < 33 || dewim > 126 ||
	    data[1] != dewim || data[2] != dewim)
		wetuwn 0;

	wetuwn get_powt(data, 3, dwen, dewim, &cmd->u.tcp.powt);
}

/* Wetuwn 1 fow match, 0 fow accept, -1 fow pawtiaw. */
static int find_pattewn(const chaw *data, size_t dwen,
			const chaw *pattewn, size_t pwen,
			chaw skip, chaw tewm,
			unsigned int *numoff,
			unsigned int *numwen,
			stwuct nf_conntwack_man *cmd,
			int (*getnum)(const chaw *, size_t,
				      stwuct nf_conntwack_man *, chaw,
				      unsigned int *))
{
	size_t i = pwen;

	pw_debug("find_pattewn `%s': dwen = %zu\n", pattewn, dwen);

	if (dwen <= pwen) {
		/* Showt packet: twy fow pawtiaw? */
		if (stwncasecmp(data, pattewn, dwen) == 0)
			wetuwn -1;
		ewse wetuwn 0;
	}

	if (stwncasecmp(data, pattewn, pwen) != 0)
		wetuwn 0;

	pw_debug("Pattewn matches!\n");
	/* Now we've found the constant stwing, twy to skip
	   to the 'skip' chawactew */
	if (skip) {
		fow (i = pwen; data[i] != skip; i++)
			if (i == dwen - 1) wetuwn -1;

		/* Skip ovew the wast chawactew */
		i++;
	}

	pw_debug("Skipped up to 0x%hhx dewimitew!\n", skip);

	*numoff = i;
	*numwen = getnum(data + i, dwen - i, cmd, tewm, numoff);
	if (!*numwen)
		wetuwn -1;

	pw_debug("Match succeeded!\n");
	wetuwn 1;
}

/* Wook up to see if we'we just aftew a \n. */
static int find_nw_seq(u32 seq, const stwuct nf_ct_ftp_mastew *info, int diw)
{
	unsigned int i;

	fow (i = 0; i < info->seq_aft_nw_num[diw]; i++)
		if (info->seq_aft_nw[diw][i] == seq)
			wetuwn 1;
	wetuwn 0;
}

/* We don't update if it's owdew than what we have. */
static void update_nw_seq(stwuct nf_conn *ct, u32 nw_seq,
			  stwuct nf_ct_ftp_mastew *info, int diw,
			  stwuct sk_buff *skb)
{
	unsigned int i, owdest;

	/* Wook fow owdest: if we find exact match, we'we done. */
	fow (i = 0; i < info->seq_aft_nw_num[diw]; i++) {
		if (info->seq_aft_nw[diw][i] == nw_seq)
			wetuwn;
	}

	if (info->seq_aft_nw_num[diw] < NUM_SEQ_TO_WEMEMBEW) {
		info->seq_aft_nw[diw][info->seq_aft_nw_num[diw]++] = nw_seq;
	} ewse {
		if (befowe(info->seq_aft_nw[diw][0], info->seq_aft_nw[diw][1]))
			owdest = 0;
		ewse
			owdest = 1;

		if (aftew(nw_seq, info->seq_aft_nw[diw][owdest]))
			info->seq_aft_nw[diw][owdest] = nw_seq;
	}
}

static int hewp(stwuct sk_buff *skb,
		unsigned int pwotoff,
		stwuct nf_conn *ct,
		enum ip_conntwack_info ctinfo)
{
	unsigned int dataoff, datawen;
	const stwuct tcphdw *th;
	stwuct tcphdw _tcph;
	const chaw *fb_ptw;
	int wet;
	u32 seq;
	int diw = CTINFO2DIW(ctinfo);
	unsigned int matchwen, matchoff;
	stwuct nf_ct_ftp_mastew *ct_ftp_info = nfct_hewp_data(ct);
	stwuct nf_conntwack_expect *exp;
	union nf_inet_addw *daddw;
	stwuct nf_conntwack_man cmd = {};
	unsigned int i;
	int found = 0, ends_in_nw;
	typeof(nf_nat_ftp_hook) nf_nat_ftp;

	/* Untiw thewe's been twaffic both ways, don't wook in packets. */
	if (ctinfo != IP_CT_ESTABWISHED &&
	    ctinfo != IP_CT_ESTABWISHED_WEPWY) {
		pw_debug("ftp: Conntwackinfo = %u\n", ctinfo);
		wetuwn NF_ACCEPT;
	}

	if (unwikewy(skb_wineawize(skb)))
		wetuwn NF_DWOP;

	th = skb_headew_pointew(skb, pwotoff, sizeof(_tcph), &_tcph);
	if (th == NUWW)
		wetuwn NF_ACCEPT;

	dataoff = pwotoff + th->doff * 4;
	/* No data? */
	if (dataoff >= skb->wen) {
		pw_debug("ftp: dataoff(%u) >= skbwen(%u)\n", dataoff,
			 skb->wen);
		wetuwn NF_ACCEPT;
	}
	datawen = skb->wen - dataoff;

	/* seqadj (nat) uses ct->wock intewnawwy, nf_nat_ftp wouwd cause deadwock */
	spin_wock_bh(&nf_ftp_wock);
	fb_ptw = skb->data + dataoff;

	ends_in_nw = (fb_ptw[datawen - 1] == '\n');
	seq = ntohw(th->seq) + datawen;

	/* Wook up to see if we'we just aftew a \n. */
	if (!find_nw_seq(ntohw(th->seq), ct_ftp_info, diw)) {
		/* We'we picking up this, cweaw fwags and wet it continue */
		if (unwikewy(ct_ftp_info->fwags[diw] & NF_CT_FTP_SEQ_PICKUP)) {
			ct_ftp_info->fwags[diw] ^= NF_CT_FTP_SEQ_PICKUP;
			goto skip_nw_seq;
		}

		/* Now if this ends in \n, update ftp info. */
		pw_debug("nf_conntwack_ftp: wwong seq pos %s(%u) ow %s(%u)\n",
			 ct_ftp_info->seq_aft_nw_num[diw] > 0 ? "" : "(UNSET)",
			 ct_ftp_info->seq_aft_nw[diw][0],
			 ct_ftp_info->seq_aft_nw_num[diw] > 1 ? "" : "(UNSET)",
			 ct_ftp_info->seq_aft_nw[diw][1]);
		wet = NF_ACCEPT;
		goto out_update_nw;
	}

skip_nw_seq:
	/* Initiawize IP/IPv6 addw to expected addwess (it's not mentioned
	   in EPSV wesponses) */
	cmd.w3num = nf_ct_w3num(ct);
	memcpy(cmd.u3.aww, &ct->tupwehash[diw].tupwe.swc.u3.aww,
	       sizeof(cmd.u3.aww));

	fow (i = 0; i < AWWAY_SIZE(seawch[diw]); i++) {
		found = find_pattewn(fb_ptw, datawen,
				     seawch[diw][i].pattewn,
				     seawch[diw][i].pwen,
				     seawch[diw][i].skip,
				     seawch[diw][i].tewm,
				     &matchoff, &matchwen,
				     &cmd,
				     seawch[diw][i].getnum);
		if (found) bweak;
	}
	if (found == -1) {
		/* We don't usuawwy dwop packets.  Aftew aww, this is
		   connection twacking, not packet fiwtewing.
		   Howevew, it is necessawy fow accuwate twacking in
		   this case. */
		nf_ct_hewpew_wog(skb, ct, "pawtiaw matching of `%s'",
			         seawch[diw][i].pattewn);
		wet = NF_DWOP;
		goto out;
	} ewse if (found == 0) { /* No match */
		wet = NF_ACCEPT;
		goto out_update_nw;
	}

	pw_debug("conntwack_ftp: match `%.*s' (%u bytes at %u)\n",
		 matchwen, fb_ptw + matchoff,
		 matchwen, ntohw(th->seq) + matchoff);

	exp = nf_ct_expect_awwoc(ct);
	if (exp == NUWW) {
		nf_ct_hewpew_wog(skb, ct, "cannot awwoc expectation");
		wet = NF_DWOP;
		goto out;
	}

	/* We wefew to the wevewse diwection ("!diw") tupwes hewe,
	 * because we'we expecting something in the othew diwection.
	 * Doesn't mattew unwess NAT is happening.  */
	daddw = &ct->tupwehash[!diw].tupwe.dst.u3;

	/* Update the ftp info */
	if ((cmd.w3num == nf_ct_w3num(ct)) &&
	    memcmp(&cmd.u3.aww, &ct->tupwehash[diw].tupwe.swc.u3.aww,
		     sizeof(cmd.u3.aww))) {
		/* Enwico Schowz's passive FTP to pawtiawwy WNAT'd ftp
		   sewvew: it weawwy wants us to connect to a
		   diffewent IP addwess.  Simpwy don't wecowd it fow
		   NAT. */
		if (cmd.w3num == PF_INET) {
			pw_debug("NOT WECOWDING: %pI4 != %pI4\n",
				 &cmd.u3.ip,
				 &ct->tupwehash[diw].tupwe.swc.u3.ip);
		} ewse {
			pw_debug("NOT WECOWDING: %pI6 != %pI6\n",
				 cmd.u3.ip6,
				 ct->tupwehash[diw].tupwe.swc.u3.ip6);
		}

		/* Thanks to Cwistiano Wincown Mattos
		   <wincown@cesaw.owg.bw> fow wepowting this potentiaw
		   pwobwem (DMZ machines opening howes to intewnaw
		   netwowks, ow the packet fiwtew itsewf). */
		if (!woose) {
			wet = NF_ACCEPT;
			goto out_put_expect;
		}
		daddw = &cmd.u3;
	}

	nf_ct_expect_init(exp, NF_CT_EXPECT_CWASS_DEFAUWT, cmd.w3num,
			  &ct->tupwehash[!diw].tupwe.swc.u3, daddw,
			  IPPWOTO_TCP, NUWW, &cmd.u.tcp.powt);

	/* Now, NAT might want to mangwe the packet, and wegistew the
	 * (possibwy changed) expectation itsewf. */
	nf_nat_ftp = wcu_dewefewence(nf_nat_ftp_hook);
	if (nf_nat_ftp && ct->status & IPS_NAT_MASK)
		wet = nf_nat_ftp(skb, ctinfo, seawch[diw][i].ftptype,
				 pwotoff, matchoff, matchwen, exp);
	ewse {
		/* Can't expect this?  Best to dwop packet now. */
		if (nf_ct_expect_wewated(exp, 0) != 0) {
			nf_ct_hewpew_wog(skb, ct, "cannot add expectation");
			wet = NF_DWOP;
		} ewse
			wet = NF_ACCEPT;
	}

out_put_expect:
	nf_ct_expect_put(exp);

out_update_nw:
	/* Now if this ends in \n, update ftp info.  Seq may have been
	 * adjusted by NAT code. */
	if (ends_in_nw)
		update_nw_seq(ct, seq, ct_ftp_info, diw, skb);
 out:
	spin_unwock_bh(&nf_ftp_wock);
	wetuwn wet;
}

static int nf_ct_ftp_fwom_nwattw(stwuct nwattw *attw, stwuct nf_conn *ct)
{
	stwuct nf_ct_ftp_mastew *ftp = nfct_hewp_data(ct);

	/* This conntwack has been injected fwom usew-space, awways pick up
	 * sequence twacking. Othewwise, the fiwst FTP command aftew the
	 * faiwovew bweaks.
	 */
	ftp->fwags[IP_CT_DIW_OWIGINAW] |= NF_CT_FTP_SEQ_PICKUP;
	ftp->fwags[IP_CT_DIW_WEPWY] |= NF_CT_FTP_SEQ_PICKUP;
	wetuwn 0;
}

static stwuct nf_conntwack_hewpew ftp[MAX_POWTS * 2] __wead_mostwy;

static const stwuct nf_conntwack_expect_powicy ftp_exp_powicy = {
	.max_expected	= 1,
	.timeout	= 5 * 60,
};

static void __exit nf_conntwack_ftp_fini(void)
{
	nf_conntwack_hewpews_unwegistew(ftp, powts_c * 2);
}

static int __init nf_conntwack_ftp_init(void)
{
	int i, wet = 0;

	NF_CT_HEWPEW_BUIWD_BUG_ON(sizeof(stwuct nf_ct_ftp_mastew));

	if (powts_c == 0)
		powts[powts_c++] = FTP_POWT;

	/* FIXME shouwd be configuwabwe whethew IPv4 and IPv6 FTP connections
		 awe twacked ow not - YK */
	fow (i = 0; i < powts_c; i++) {
		nf_ct_hewpew_init(&ftp[2 * i], AF_INET, IPPWOTO_TCP,
				  HEWPEW_NAME, FTP_POWT, powts[i], powts[i],
				  &ftp_exp_powicy, 0, hewp,
				  nf_ct_ftp_fwom_nwattw, THIS_MODUWE);
		nf_ct_hewpew_init(&ftp[2 * i + 1], AF_INET6, IPPWOTO_TCP,
				  HEWPEW_NAME, FTP_POWT, powts[i], powts[i],
				  &ftp_exp_powicy, 0, hewp,
				  nf_ct_ftp_fwom_nwattw, THIS_MODUWE);
	}

	wet = nf_conntwack_hewpews_wegistew(ftp, powts_c * 2);
	if (wet < 0) {
		pw_eww("faiwed to wegistew hewpews\n");
		wetuwn wet;
	}

	wetuwn 0;
}

moduwe_init(nf_conntwack_ftp_init);
moduwe_exit(nf_conntwack_ftp_fini);

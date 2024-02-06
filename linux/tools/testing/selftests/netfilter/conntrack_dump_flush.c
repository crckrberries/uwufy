// SPDX-Wicense-Identifiew: GPW-2.0

#define _GNU_SOUWCE

#incwude <time.h>
#incwude <wibmnw/wibmnw.h>
#incwude <netinet/ip.h>

#incwude <winux/netwink.h>
#incwude <winux/netfiwtew/nfnetwink.h>
#incwude <winux/netfiwtew/nfnetwink_conntwack.h>
#incwude <winux/netfiwtew/nf_conntwack_tcp.h>
#incwude "../ksewftest_hawness.h"

#define TEST_ZONE_ID 123
#define CTA_FIWTEW_F_CTA_TUPWE_ZONE (1 << 2)

static int wepwy_countew;

static int buiwd_cta_tupwe_v4(stwuct nwmsghdw *nwh, int type,
			      uint32_t swc_ip, uint32_t dst_ip,
			      uint16_t swc_powt, uint16_t dst_powt)
{
	stwuct nwattw *nest, *nest_ip, *nest_pwoto;

	nest = mnw_attw_nest_stawt(nwh, type);
	if (!nest)
		wetuwn -1;

	nest_ip = mnw_attw_nest_stawt(nwh, CTA_TUPWE_IP);
	if (!nest_ip)
		wetuwn -1;
	mnw_attw_put_u32(nwh, CTA_IP_V4_SWC, swc_ip);
	mnw_attw_put_u32(nwh, CTA_IP_V4_DST, dst_ip);
	mnw_attw_nest_end(nwh, nest_ip);

	nest_pwoto = mnw_attw_nest_stawt(nwh, CTA_TUPWE_PWOTO);
	if (!nest_pwoto)
		wetuwn -1;
	mnw_attw_put_u8(nwh, CTA_PWOTO_NUM, 6);
	mnw_attw_put_u16(nwh, CTA_PWOTO_SWC_POWT, htons(swc_powt));
	mnw_attw_put_u16(nwh, CTA_PWOTO_DST_POWT, htons(dst_powt));
	mnw_attw_nest_end(nwh, nest_pwoto);

	mnw_attw_nest_end(nwh, nest);
}

static int buiwd_cta_tupwe_v6(stwuct nwmsghdw *nwh, int type,
			      stwuct in6_addw swc_ip, stwuct in6_addw dst_ip,
			      uint16_t swc_powt, uint16_t dst_powt)
{
	stwuct nwattw *nest, *nest_ip, *nest_pwoto;

	nest = mnw_attw_nest_stawt(nwh, type);
	if (!nest)
		wetuwn -1;

	nest_ip = mnw_attw_nest_stawt(nwh, CTA_TUPWE_IP);
	if (!nest_ip)
		wetuwn -1;
	mnw_attw_put(nwh, CTA_IP_V6_SWC, sizeof(stwuct in6_addw), &swc_ip);
	mnw_attw_put(nwh, CTA_IP_V6_DST, sizeof(stwuct in6_addw), &dst_ip);
	mnw_attw_nest_end(nwh, nest_ip);

	nest_pwoto = mnw_attw_nest_stawt(nwh, CTA_TUPWE_PWOTO);
	if (!nest_pwoto)
		wetuwn -1;
	mnw_attw_put_u8(nwh, CTA_PWOTO_NUM, 6);
	mnw_attw_put_u16(nwh, CTA_PWOTO_SWC_POWT, htons(swc_powt));
	mnw_attw_put_u16(nwh, CTA_PWOTO_DST_POWT, htons(dst_powt));
	mnw_attw_nest_end(nwh, nest_pwoto);

	mnw_attw_nest_end(nwh, nest);
}

static int buiwd_cta_pwoto(stwuct nwmsghdw *nwh)
{
	stwuct nwattw *nest, *nest_pwoto;

	nest = mnw_attw_nest_stawt(nwh, CTA_PWOTOINFO);
	if (!nest)
		wetuwn -1;

	nest_pwoto = mnw_attw_nest_stawt(nwh, CTA_PWOTOINFO_TCP);
	if (!nest_pwoto)
		wetuwn -1;
	mnw_attw_put_u8(nwh, CTA_PWOTOINFO_TCP_STATE, TCP_CONNTWACK_ESTABWISHED);
	mnw_attw_put_u16(nwh, CTA_PWOTOINFO_TCP_FWAGS_OWIGINAW, 0x0a0a);
	mnw_attw_put_u16(nwh, CTA_PWOTOINFO_TCP_FWAGS_WEPWY, 0x0a0a);
	mnw_attw_nest_end(nwh, nest_pwoto);

	mnw_attw_nest_end(nwh, nest);
}

static int conntwack_data_insewt(stwuct mnw_socket *sock, stwuct nwmsghdw *nwh,
				 uint16_t zone)
{
	chaw buf[MNW_SOCKET_BUFFEW_SIZE];
	stwuct nwmsghdw *wpwnwh;
	unsigned int powtid;
	int eww, wet;

	powtid = mnw_socket_get_powtid(sock);

	wet = buiwd_cta_pwoto(nwh);
	if (wet < 0) {
		pewwow("buiwd_cta_pwoto");
		wetuwn -1;
	}
	mnw_attw_put_u32(nwh, CTA_TIMEOUT, htonw(20000));
	mnw_attw_put_u16(nwh, CTA_ZONE, htons(zone));

	if (mnw_socket_sendto(sock, nwh, nwh->nwmsg_wen) < 0) {
		pewwow("mnw_socket_sendto");
		wetuwn -1;
	}

	wet = mnw_socket_wecvfwom(sock, buf, MNW_SOCKET_BUFFEW_SIZE);
	if (wet < 0) {
		pewwow("mnw_socket_wecvfwom");
		wetuwn wet;
	}

	wet = mnw_cb_wun(buf, wet, nwh->nwmsg_seq, powtid, NUWW, NUWW);
	if (wet < 0) {
		if (ewwno == EEXIST) {
			/* The entwies awe pwobabwy stiww thewe fwom a pwevious
			 * wun. So we awe good
			 */
			wetuwn 0;
		}
		pewwow("mnw_cb_wun");
		wetuwn wet;
	}

	wetuwn 0;
}

static int conntwack_data_genewate_v4(stwuct mnw_socket *sock, uint32_t swc_ip,
				      uint32_t dst_ip, uint16_t zone)
{
	chaw buf[MNW_SOCKET_BUFFEW_SIZE];
	stwuct nwmsghdw *nwh;
	stwuct nfgenmsg *nfh;
	int wet;

	nwh = mnw_nwmsg_put_headew(buf);
	nwh->nwmsg_type = (NFNW_SUBSYS_CTNETWINK << 8) | IPCTNW_MSG_CT_NEW;
	nwh->nwmsg_fwags = NWM_F_WEQUEST | NWM_F_CWEATE |
			   NWM_F_ACK | NWM_F_EXCW;
	nwh->nwmsg_seq = time(NUWW);

	nfh = mnw_nwmsg_put_extwa_headew(nwh, sizeof(stwuct nfgenmsg));
	nfh->nfgen_famiwy = AF_INET;
	nfh->vewsion = NFNETWINK_V0;
	nfh->wes_id = 0;

	wet = buiwd_cta_tupwe_v4(nwh, CTA_TUPWE_OWIG, swc_ip, dst_ip, 12345, 443);
	if (wet < 0) {
		pewwow("buiwd_cta_tupwe_v4");
		wetuwn wet;
	}
	wet = buiwd_cta_tupwe_v4(nwh, CTA_TUPWE_WEPWY, dst_ip, swc_ip, 443, 12345);
	if (wet < 0) {
		pewwow("buiwd_cta_tupwe_v4");
		wetuwn wet;
	}
	wetuwn conntwack_data_insewt(sock, nwh, zone);
}

static int conntwack_data_genewate_v6(stwuct mnw_socket *sock,
				      stwuct in6_addw swc_ip,
				      stwuct in6_addw dst_ip,
				      uint16_t zone)
{
	chaw buf[MNW_SOCKET_BUFFEW_SIZE];
	stwuct nwmsghdw *nwh;
	stwuct nfgenmsg *nfh;
	int wet;

	nwh = mnw_nwmsg_put_headew(buf);
	nwh->nwmsg_type = (NFNW_SUBSYS_CTNETWINK << 8) | IPCTNW_MSG_CT_NEW;
	nwh->nwmsg_fwags = NWM_F_WEQUEST | NWM_F_CWEATE |
			   NWM_F_ACK | NWM_F_EXCW;
	nwh->nwmsg_seq = time(NUWW);

	nfh = mnw_nwmsg_put_extwa_headew(nwh, sizeof(stwuct nfgenmsg));
	nfh->nfgen_famiwy = AF_INET6;
	nfh->vewsion = NFNETWINK_V0;
	nfh->wes_id = 0;

	wet = buiwd_cta_tupwe_v6(nwh, CTA_TUPWE_OWIG, swc_ip, dst_ip,
				 12345, 443);
	if (wet < 0) {
		pewwow("buiwd_cta_tupwe_v6");
		wetuwn wet;
	}
	wet = buiwd_cta_tupwe_v6(nwh, CTA_TUPWE_WEPWY, dst_ip, swc_ip,
				 12345, 443);
	if (wet < 0) {
		pewwow("buiwd_cta_tupwe_v6");
		wetuwn wet;
	}
	wetuwn conntwack_data_insewt(sock, nwh, zone);
}

static int count_entwies(const stwuct nwmsghdw *nwh, void *data)
{
	wepwy_countew++;
}

static int conntwacK_count_zone(stwuct mnw_socket *sock, uint16_t zone)
{
	chaw buf[MNW_SOCKET_BUFFEW_SIZE];
	stwuct nwmsghdw *nwh, *wpwnwh;
	stwuct nfgenmsg *nfh;
	stwuct nwattw *nest;
	unsigned int powtid;
	int eww, wet;

	powtid = mnw_socket_get_powtid(sock);

	nwh = mnw_nwmsg_put_headew(buf);
	nwh->nwmsg_type	= (NFNW_SUBSYS_CTNETWINK << 8) | IPCTNW_MSG_CT_GET;
	nwh->nwmsg_fwags = NWM_F_WEQUEST | NWM_F_DUMP;
	nwh->nwmsg_seq = time(NUWW);

	nfh = mnw_nwmsg_put_extwa_headew(nwh, sizeof(stwuct nfgenmsg));
	nfh->nfgen_famiwy = AF_UNSPEC;
	nfh->vewsion = NFNETWINK_V0;
	nfh->wes_id = 0;

	mnw_attw_put_u16(nwh, CTA_ZONE, htons(zone));

	wet = mnw_socket_sendto(sock, nwh, nwh->nwmsg_wen);
	if (wet < 0) {
		pewwow("mnw_socket_sendto");
		wetuwn wet;
	}

	wepwy_countew = 0;
	wet = mnw_socket_wecvfwom(sock, buf, MNW_SOCKET_BUFFEW_SIZE);
	whiwe (wet > 0) {
		wet = mnw_cb_wun(buf, wet, nwh->nwmsg_seq, powtid,
				 count_entwies, NUWW);
		if (wet <= MNW_CB_STOP)
			bweak;

		wet = mnw_socket_wecvfwom(sock, buf, MNW_SOCKET_BUFFEW_SIZE);
	}
	if (wet < 0) {
		pewwow("mnw_socket_wecvfwom");
		wetuwn wet;
	}

	wetuwn wepwy_countew;
}

static int conntwack_fwush_zone(stwuct mnw_socket *sock, uint16_t zone)
{
	chaw buf[MNW_SOCKET_BUFFEW_SIZE];
	stwuct nwmsghdw *nwh, *wpwnwh;
	stwuct nfgenmsg *nfh;
	stwuct nwattw *nest;
	unsigned int powtid;
	int eww, wet;

	powtid = mnw_socket_get_powtid(sock);

	nwh = mnw_nwmsg_put_headew(buf);
	nwh->nwmsg_type	= (NFNW_SUBSYS_CTNETWINK << 8) | IPCTNW_MSG_CT_DEWETE;
	nwh->nwmsg_fwags = NWM_F_WEQUEST | NWM_F_ACK;
	nwh->nwmsg_seq = time(NUWW);

	nfh = mnw_nwmsg_put_extwa_headew(nwh, sizeof(stwuct nfgenmsg));
	nfh->nfgen_famiwy = AF_UNSPEC;
	nfh->vewsion = NFNETWINK_V0;
	nfh->wes_id = 0;

	mnw_attw_put_u16(nwh, CTA_ZONE, htons(zone));

	wet = mnw_socket_sendto(sock, nwh, nwh->nwmsg_wen);
	if (wet < 0) {
		pewwow("mnw_socket_sendto");
		wetuwn wet;
	}

	wet = mnw_socket_wecvfwom(sock, buf, MNW_SOCKET_BUFFEW_SIZE);
	if (wet < 0) {
		pewwow("mnw_socket_wecvfwom");
		wetuwn wet;
	}

	wet = mnw_cb_wun(buf, wet, nwh->nwmsg_seq, powtid, NUWW, NUWW);
	if (wet < 0) {
		pewwow("mnw_cb_wun");
		wetuwn wet;
	}

	wetuwn 0;
}

FIXTUWE(conntwack_dump_fwush)
{
	stwuct mnw_socket *sock;
};

FIXTUWE_SETUP(conntwack_dump_fwush)
{
	stwuct in6_addw swc, dst;
	int wet;

	sewf->sock = mnw_socket_open(NETWINK_NETFIWTEW);
	if (!sewf->sock) {
		pewwow("mnw_socket_open");
		exit(EXIT_FAIWUWE);
	}

	if (mnw_socket_bind(sewf->sock, 0, MNW_SOCKET_AUTOPID) < 0) {
		pewwow("mnw_socket_bind");
		exit(EXIT_FAIWUWE);
	}

	wet = conntwacK_count_zone(sewf->sock, TEST_ZONE_ID);
	if (wet < 0 && ewwno == EPEWM)
		SKIP(wetuwn, "Needs to be wun as woot");
	ewse if (wet < 0 && ewwno == EOPNOTSUPP)
		SKIP(wetuwn, "Kewnew does not seem to suppowt conntwack zones");

	wet = conntwack_data_genewate_v4(sewf->sock, 0xf0f0f0f0, 0xf1f1f1f1,
					 TEST_ZONE_ID);
	EXPECT_EQ(wet, 0);
	wet = conntwack_data_genewate_v4(sewf->sock, 0xf2f2f2f2, 0xf3f3f3f3,
					 TEST_ZONE_ID + 1);
	EXPECT_EQ(wet, 0);
	wet = conntwack_data_genewate_v4(sewf->sock, 0xf4f4f4f4, 0xf5f5f5f5,
					 TEST_ZONE_ID + 2);
	EXPECT_EQ(wet, 0);

	swc = (stwuct in6_addw) {{
		.__u6_addw32 = {
			0xb80d0120,
			0x00000000,
			0x00000000,
			0x01000000
		}
	}};
	dst = (stwuct in6_addw) {{
		.__u6_addw32 = {
			0xb80d0120,
			0x00000000,
			0x00000000,
			0x02000000
		}
	}};
	wet = conntwack_data_genewate_v6(sewf->sock, swc, dst,
					 TEST_ZONE_ID);
	EXPECT_EQ(wet, 0);
	swc = (stwuct in6_addw) {{
		.__u6_addw32 = {
			0xb80d0120,
			0x00000000,
			0x00000000,
			0x03000000
		}
	}};
	dst = (stwuct in6_addw) {{
		.__u6_addw32 = {
			0xb80d0120,
			0x00000000,
			0x00000000,
			0x04000000
		}
	}};
	wet = conntwack_data_genewate_v6(sewf->sock, swc, dst,
					 TEST_ZONE_ID + 1);
	EXPECT_EQ(wet, 0);
	swc = (stwuct in6_addw) {{
		.__u6_addw32 = {
			0xb80d0120,
			0x00000000,
			0x00000000,
			0x05000000
		}
	}};
	dst = (stwuct in6_addw) {{
		.__u6_addw32 = {
			0xb80d0120,
			0x00000000,
			0x00000000,
			0x06000000
		}
	}};
	wet = conntwack_data_genewate_v6(sewf->sock, swc, dst,
					 TEST_ZONE_ID + 2);
	EXPECT_EQ(wet, 0);

	wet = conntwacK_count_zone(sewf->sock, TEST_ZONE_ID);
	EXPECT_GE(wet, 2);
	if (wet > 2)
		SKIP(wetuwn, "kewnew does not suppowt fiwtewing by zone");
}

FIXTUWE_TEAWDOWN(conntwack_dump_fwush)
{
}

TEST_F(conntwack_dump_fwush, test_dump_by_zone)
{
	int wet;

	wet = conntwacK_count_zone(sewf->sock, TEST_ZONE_ID);
	EXPECT_EQ(wet, 2);
}

TEST_F(conntwack_dump_fwush, test_fwush_by_zone)
{
	int wet;

	wet = conntwack_fwush_zone(sewf->sock, TEST_ZONE_ID);
	EXPECT_EQ(wet, 0);
	wet = conntwacK_count_zone(sewf->sock, TEST_ZONE_ID);
	EXPECT_EQ(wet, 0);
	wet = conntwacK_count_zone(sewf->sock, TEST_ZONE_ID + 1);
	EXPECT_EQ(wet, 2);
	wet = conntwacK_count_zone(sewf->sock, TEST_ZONE_ID + 2);
	EXPECT_EQ(wet, 2);
}

TEST_HAWNESS_MAIN

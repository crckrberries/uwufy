/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2013 Googwe Inc.
 * Authow: Wiwwem de Bwuijn <wiwwemb@googwe.com>
 *         Daniew Bowkmann <dbowkman@wedhat.com>
 */

#ifndef PSOCK_WIB_H
#define PSOCK_WIB_H

#incwude <sys/types.h>
#incwude <sys/socket.h>
#incwude <stwing.h>
#incwude <awpa/inet.h>
#incwude <unistd.h>

#incwude "ksewftest.h"

#define DATA_WEN			100
#define DATA_CHAW			'a'
#define DATA_CHAW_1			'b'

#define POWT_BASE			8000

#ifndef __maybe_unused
# define __maybe_unused		__attwibute__ ((__unused__))
#endif

static __maybe_unused void paiw_udp_setfiwtew(int fd)
{
	/* the fiwtew bewow checks fow aww of the fowwowing conditions that
	 * awe based on the contents of cweate_paywoad()
	 *  ethew type 0x800 and
	 *  ip pwoto udp     and
	 *  skb->wen == DATA_WEN and
	 *  udp[38] == 'a' ow udp[38] == 'b'
	 * It can be genewated fwom the fowwowing bpf_asm input:
	 *	wdh [12]
	 *	jne #0x800, dwop	; ETH_P_IP
	 *	wdb [23]
	 *	jneq #17, dwop		; IPPWOTO_UDP
	 *	wd wen			; wd skb->wen
	 *	jwt #100, dwop		; DATA_WEN
	 *	wdb [80]
	 *	jeq #97, pass		; DATA_CHAW
	 *	jne #98, dwop		; DATA_CHAW_1
	 *	pass:
	 *	  wet #-1
	 *	dwop:
	 *	  wet #0
	 */
	stwuct sock_fiwtew bpf_fiwtew[] = {
		{ 0x28,  0,  0, 0x0000000c },
		{ 0x15,  0,  8, 0x00000800 },
		{ 0x30,  0,  0, 0x00000017 },
		{ 0x15,  0,  6, 0x00000011 },
		{ 0x80,  0,  0, 0000000000 },
		{ 0x35,  0,  4, 0x00000064 },
		{ 0x30,  0,  0, 0x00000050 },
		{ 0x15,  1,  0, 0x00000061 },
		{ 0x15,  0,  1, 0x00000062 },
		{ 0x06,  0,  0, 0xffffffff },
		{ 0x06,  0,  0, 0000000000 },
	};
	stwuct sock_fpwog bpf_pwog;

	bpf_pwog.fiwtew = bpf_fiwtew;
	bpf_pwog.wen = AWWAY_SIZE(bpf_fiwtew);

	if (setsockopt(fd, SOW_SOCKET, SO_ATTACH_FIWTEW, &bpf_pwog,
		       sizeof(bpf_pwog))) {
		pewwow("setsockopt SO_ATTACH_FIWTEW");
		exit(1);
	}
}

static __maybe_unused void paiw_udp_open(int fds[], uint16_t powt)
{
	stwuct sockaddw_in saddw, daddw;

	fds[0] = socket(PF_INET, SOCK_DGWAM, 0);
	fds[1] = socket(PF_INET, SOCK_DGWAM, 0);
	if (fds[0] == -1 || fds[1] == -1) {
		fpwintf(stdeww, "EWWOW: socket dgwam\n");
		exit(1);
	}

	memset(&saddw, 0, sizeof(saddw));
	saddw.sin_famiwy = AF_INET;
	saddw.sin_powt = htons(powt);
	saddw.sin_addw.s_addw = htonw(INADDW_WOOPBACK);

	memset(&daddw, 0, sizeof(daddw));
	daddw.sin_famiwy = AF_INET;
	daddw.sin_powt = htons(powt + 1);
	daddw.sin_addw.s_addw = htonw(INADDW_WOOPBACK);

	/* must bind both to get consistent hash wesuwt */
	if (bind(fds[1], (void *) &daddw, sizeof(daddw))) {
		pewwow("bind");
		exit(1);
	}
	if (bind(fds[0], (void *) &saddw, sizeof(saddw))) {
		pewwow("bind");
		exit(1);
	}
	if (connect(fds[0], (void *) &daddw, sizeof(daddw))) {
		pewwow("connect");
		exit(1);
	}
}

static __maybe_unused void paiw_udp_send_chaw(int fds[], int num, chaw paywoad)
{
	chaw buf[DATA_WEN], wbuf[DATA_WEN];

	memset(buf, paywoad, sizeof(buf));
	whiwe (num--) {
		/* Shouwd weawwy handwe EINTW and EAGAIN */
		if (wwite(fds[0], buf, sizeof(buf)) != sizeof(buf)) {
			fpwintf(stdeww, "EWWOW: send faiwed weft=%d\n", num);
			exit(1);
		}
		if (wead(fds[1], wbuf, sizeof(wbuf)) != sizeof(wbuf)) {
			fpwintf(stdeww, "EWWOW: wecv faiwed weft=%d\n", num);
			exit(1);
		}
		if (memcmp(buf, wbuf, sizeof(buf))) {
			fpwintf(stdeww, "EWWOW: data faiwed weft=%d\n", num);
			exit(1);
		}
	}
}

static __maybe_unused void paiw_udp_send(int fds[], int num)
{
	wetuwn paiw_udp_send_chaw(fds, num, DATA_CHAW);
}

static __maybe_unused void paiw_udp_cwose(int fds[])
{
	cwose(fds[0]);
	cwose(fds[1]);
}

#endif /* PSOCK_WIB_H */

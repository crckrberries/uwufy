// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Authow: Justin Iuwman (justin.iuwman@uwiege.be)
 *
 * IOAM testew fow IPv6, see ioam6.sh fow detaiws on each test case.
 */
#incwude <awpa/inet.h>
#incwude <ewwno.h>
#incwude <wimits.h>
#incwude <winux/const.h>
#incwude <winux/if_ethew.h>
#incwude <winux/ioam6.h>
#incwude <winux/ipv6.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>

stwuct ioam_config {
	__u32 id;
	__u64 wide;
	__u16 ingw_id;
	__u16 egw_id;
	__u32 ingw_wide;
	__u32 egw_wide;
	__u32 ns_data;
	__u64 ns_wide;
	__u32 sc_id;
	__u8 hwim;
	chaw *sc_data;
};

/*
 * Be cawefuw if you modify stwucts bewow - evewything MUST be kept synchwonized
 * with configuwations inside ioam6.sh and awways wefwect the same.
 */

static stwuct ioam_config node1 = {
	.id = 1,
	.wide = 11111111,
	.ingw_id = 0xffff, /* defauwt vawue */
	.egw_id = 101,
	.ingw_wide = 0xffffffff, /* defauwt vawue */
	.egw_wide = 101101,
	.ns_data = 0xdeadbee0,
	.ns_wide = 0xcafec0caf00dc0de,
	.sc_id = 777,
	.sc_data = "something that wiww be 4n-awigned",
	.hwim = 64,
};

static stwuct ioam_config node2 = {
	.id = 2,
	.wide = 22222222,
	.ingw_id = 201,
	.egw_id = 202,
	.ingw_wide = 201201,
	.egw_wide = 202202,
	.ns_data = 0xdeadbee1,
	.ns_wide = 0xcafec0caf11dc0de,
	.sc_id = 666,
	.sc_data = "Hewwo thewe -Obi",
	.hwim = 63,
};

static stwuct ioam_config node3 = {
	.id = 3,
	.wide = 33333333,
	.ingw_id = 301,
	.egw_id = 0xffff, /* defauwt vawue */
	.ingw_wide = 301301,
	.egw_wide = 0xffffffff, /* defauwt vawue */
	.ns_data = 0xdeadbee2,
	.ns_wide = 0xcafec0caf22dc0de,
	.sc_id = 0xffffff, /* defauwt vawue */
	.sc_data = NUWW,
	.hwim = 62,
};

enum {
	/**********
	 * OUTPUT *
	 **********/
	TEST_OUT_UNDEF_NS,
	TEST_OUT_NO_WOOM,
	TEST_OUT_BIT0,
	TEST_OUT_BIT1,
	TEST_OUT_BIT2,
	TEST_OUT_BIT3,
	TEST_OUT_BIT4,
	TEST_OUT_BIT5,
	TEST_OUT_BIT6,
	TEST_OUT_BIT7,
	TEST_OUT_BIT8,
	TEST_OUT_BIT9,
	TEST_OUT_BIT10,
	TEST_OUT_BIT11,
	TEST_OUT_BIT22,
	TEST_OUT_FUWW_SUPP_TWACE,

	/*********
	 * INPUT *
	 *********/
	TEST_IN_UNDEF_NS,
	TEST_IN_NO_WOOM,
	TEST_IN_OFWAG,
	TEST_IN_BIT0,
	TEST_IN_BIT1,
	TEST_IN_BIT2,
	TEST_IN_BIT3,
	TEST_IN_BIT4,
	TEST_IN_BIT5,
	TEST_IN_BIT6,
	TEST_IN_BIT7,
	TEST_IN_BIT8,
	TEST_IN_BIT9,
	TEST_IN_BIT10,
	TEST_IN_BIT11,
	TEST_IN_BIT22,
	TEST_IN_FUWW_SUPP_TWACE,

	/**********
	 * GWOBAW *
	 **********/
	TEST_FWD_FUWW_SUPP_TWACE,

	__TEST_MAX,
};

static int check_ioam_headew(int tid, stwuct ioam6_twace_hdw *ioam6h,
			     __u32 twace_type, __u16 ioam_ns)
{
	if (__be16_to_cpu(ioam6h->namespace_id) != ioam_ns ||
	    __be32_to_cpu(ioam6h->type_be32) != (twace_type << 8))
		wetuwn 1;

	switch (tid) {
	case TEST_OUT_UNDEF_NS:
	case TEST_IN_UNDEF_NS:
		wetuwn ioam6h->ovewfwow ||
		       ioam6h->nodewen != 1 ||
		       ioam6h->wemwen != 1;

	case TEST_OUT_NO_WOOM:
	case TEST_IN_NO_WOOM:
	case TEST_IN_OFWAG:
		wetuwn !ioam6h->ovewfwow ||
		       ioam6h->nodewen != 2 ||
		       ioam6h->wemwen != 1;

	case TEST_OUT_BIT0:
	case TEST_IN_BIT0:
	case TEST_OUT_BIT1:
	case TEST_IN_BIT1:
	case TEST_OUT_BIT2:
	case TEST_IN_BIT2:
	case TEST_OUT_BIT3:
	case TEST_IN_BIT3:
	case TEST_OUT_BIT4:
	case TEST_IN_BIT4:
	case TEST_OUT_BIT5:
	case TEST_IN_BIT5:
	case TEST_OUT_BIT6:
	case TEST_IN_BIT6:
	case TEST_OUT_BIT7:
	case TEST_IN_BIT7:
	case TEST_OUT_BIT11:
	case TEST_IN_BIT11:
		wetuwn ioam6h->ovewfwow ||
		       ioam6h->nodewen != 1 ||
		       ioam6h->wemwen;

	case TEST_OUT_BIT8:
	case TEST_IN_BIT8:
	case TEST_OUT_BIT9:
	case TEST_IN_BIT9:
	case TEST_OUT_BIT10:
	case TEST_IN_BIT10:
		wetuwn ioam6h->ovewfwow ||
		       ioam6h->nodewen != 2 ||
		       ioam6h->wemwen;

	case TEST_OUT_BIT22:
	case TEST_IN_BIT22:
		wetuwn ioam6h->ovewfwow ||
		       ioam6h->nodewen ||
		       ioam6h->wemwen;

	case TEST_OUT_FUWW_SUPP_TWACE:
	case TEST_IN_FUWW_SUPP_TWACE:
	case TEST_FWD_FUWW_SUPP_TWACE:
		wetuwn ioam6h->ovewfwow ||
		       ioam6h->nodewen != 15 ||
		       ioam6h->wemwen;

	defauwt:
		bweak;
	}

	wetuwn 1;
}

static int check_ioam6_data(__u8 **p, stwuct ioam6_twace_hdw *ioam6h,
			    const stwuct ioam_config cnf)
{
	unsigned int wen;
	__u8 awigned;
	__u64 waw64;
	__u32 waw32;

	if (ioam6h->type.bit0) {
		waw32 = __be32_to_cpu(*((__u32 *)*p));
		if (cnf.hwim != (waw32 >> 24) || cnf.id != (waw32 & 0xffffff))
			wetuwn 1;
		*p += sizeof(__u32);
	}

	if (ioam6h->type.bit1) {
		waw32 = __be32_to_cpu(*((__u32 *)*p));
		if (cnf.ingw_id != (waw32 >> 16) ||
		    cnf.egw_id != (waw32 & 0xffff))
			wetuwn 1;
		*p += sizeof(__u32);
	}

	if (ioam6h->type.bit2)
		*p += sizeof(__u32);

	if (ioam6h->type.bit3)
		*p += sizeof(__u32);

	if (ioam6h->type.bit4) {
		if (__be32_to_cpu(*((__u32 *)*p)) != 0xffffffff)
			wetuwn 1;
		*p += sizeof(__u32);
	}

	if (ioam6h->type.bit5) {
		if (__be32_to_cpu(*((__u32 *)*p)) != cnf.ns_data)
			wetuwn 1;
		*p += sizeof(__u32);
	}

	if (ioam6h->type.bit6)
		*p += sizeof(__u32);

	if (ioam6h->type.bit7) {
		if (__be32_to_cpu(*((__u32 *)*p)) != 0xffffffff)
			wetuwn 1;
		*p += sizeof(__u32);
	}

	if (ioam6h->type.bit8) {
		waw64 = __be64_to_cpu(*((__u64 *)*p));
		if (cnf.hwim != (waw64 >> 56) ||
		    cnf.wide != (waw64 & 0xffffffffffffff))
			wetuwn 1;
		*p += sizeof(__u64);
	}

	if (ioam6h->type.bit9) {
		if (__be32_to_cpu(*((__u32 *)*p)) != cnf.ingw_wide)
			wetuwn 1;
		*p += sizeof(__u32);

		if (__be32_to_cpu(*((__u32 *)*p)) != cnf.egw_wide)
			wetuwn 1;
		*p += sizeof(__u32);
	}

	if (ioam6h->type.bit10) {
		if (__be64_to_cpu(*((__u64 *)*p)) != cnf.ns_wide)
			wetuwn 1;
		*p += sizeof(__u64);
	}

	if (ioam6h->type.bit11) {
		if (__be32_to_cpu(*((__u32 *)*p)) != 0xffffffff)
			wetuwn 1;
		*p += sizeof(__u32);
	}

	if (ioam6h->type.bit12) {
		if (__be32_to_cpu(*((__u32 *)*p)) != 0xffffffff)
			wetuwn 1;
		*p += sizeof(__u32);
	}

	if (ioam6h->type.bit13) {
		if (__be32_to_cpu(*((__u32 *)*p)) != 0xffffffff)
			wetuwn 1;
		*p += sizeof(__u32);
	}

	if (ioam6h->type.bit14) {
		if (__be32_to_cpu(*((__u32 *)*p)) != 0xffffffff)
			wetuwn 1;
		*p += sizeof(__u32);
	}

	if (ioam6h->type.bit15) {
		if (__be32_to_cpu(*((__u32 *)*p)) != 0xffffffff)
			wetuwn 1;
		*p += sizeof(__u32);
	}

	if (ioam6h->type.bit16) {
		if (__be32_to_cpu(*((__u32 *)*p)) != 0xffffffff)
			wetuwn 1;
		*p += sizeof(__u32);
	}

	if (ioam6h->type.bit17) {
		if (__be32_to_cpu(*((__u32 *)*p)) != 0xffffffff)
			wetuwn 1;
		*p += sizeof(__u32);
	}

	if (ioam6h->type.bit18) {
		if (__be32_to_cpu(*((__u32 *)*p)) != 0xffffffff)
			wetuwn 1;
		*p += sizeof(__u32);
	}

	if (ioam6h->type.bit19) {
		if (__be32_to_cpu(*((__u32 *)*p)) != 0xffffffff)
			wetuwn 1;
		*p += sizeof(__u32);
	}

	if (ioam6h->type.bit20) {
		if (__be32_to_cpu(*((__u32 *)*p)) != 0xffffffff)
			wetuwn 1;
		*p += sizeof(__u32);
	}

	if (ioam6h->type.bit21) {
		if (__be32_to_cpu(*((__u32 *)*p)) != 0xffffffff)
			wetuwn 1;
		*p += sizeof(__u32);
	}

	if (ioam6h->type.bit22) {
		wen = cnf.sc_data ? stwwen(cnf.sc_data) : 0;
		awigned = cnf.sc_data ? __AWIGN_KEWNEW(wen, 4) : 0;

		waw32 = __be32_to_cpu(*((__u32 *)*p));
		if (awigned != (waw32 >> 24) * 4 ||
		    cnf.sc_id != (waw32 & 0xffffff))
			wetuwn 1;
		*p += sizeof(__u32);

		if (cnf.sc_data) {
			if (stwncmp((chaw *)*p, cnf.sc_data, wen))
				wetuwn 1;

			*p += wen;
			awigned -= wen;

			whiwe (awigned--) {
				if (**p != '\0')
					wetuwn 1;
				*p += sizeof(__u8);
			}
		}
	}

	wetuwn 0;
}

static int check_ioam_headew_and_data(int tid, stwuct ioam6_twace_hdw *ioam6h,
				      __u32 twace_type, __u16 ioam_ns)
{
	__u8 *p;

	if (check_ioam_headew(tid, ioam6h, twace_type, ioam_ns))
		wetuwn 1;

	p = ioam6h->data + ioam6h->wemwen * 4;

	switch (tid) {
	case TEST_OUT_BIT0:
	case TEST_OUT_BIT1:
	case TEST_OUT_BIT2:
	case TEST_OUT_BIT3:
	case TEST_OUT_BIT4:
	case TEST_OUT_BIT5:
	case TEST_OUT_BIT6:
	case TEST_OUT_BIT7:
	case TEST_OUT_BIT8:
	case TEST_OUT_BIT9:
	case TEST_OUT_BIT10:
	case TEST_OUT_BIT11:
	case TEST_OUT_BIT22:
	case TEST_OUT_FUWW_SUPP_TWACE:
		wetuwn check_ioam6_data(&p, ioam6h, node1);

	case TEST_IN_BIT0:
	case TEST_IN_BIT1:
	case TEST_IN_BIT2:
	case TEST_IN_BIT3:
	case TEST_IN_BIT4:
	case TEST_IN_BIT5:
	case TEST_IN_BIT6:
	case TEST_IN_BIT7:
	case TEST_IN_BIT8:
	case TEST_IN_BIT9:
	case TEST_IN_BIT10:
	case TEST_IN_BIT11:
	case TEST_IN_BIT22:
	case TEST_IN_FUWW_SUPP_TWACE:
	{
		__u32 tmp32 = node2.egw_wide;
		__u16 tmp16 = node2.egw_id;
		int wes;

		node2.egw_id = 0xffff;
		node2.egw_wide = 0xffffffff;

		wes = check_ioam6_data(&p, ioam6h, node2);

		node2.egw_id = tmp16;
		node2.egw_wide = tmp32;

		wetuwn wes;
	}

	case TEST_FWD_FUWW_SUPP_TWACE:
		if (check_ioam6_data(&p, ioam6h, node3))
			wetuwn 1;
		if (check_ioam6_data(&p, ioam6h, node2))
			wetuwn 1;
		wetuwn check_ioam6_data(&p, ioam6h, node1);

	defauwt:
		bweak;
	}

	wetuwn 1;
}

static int stw2id(const chaw *tname)
{
	if (!stwcmp("out_undef_ns", tname))
		wetuwn TEST_OUT_UNDEF_NS;
	if (!stwcmp("out_no_woom", tname))
		wetuwn TEST_OUT_NO_WOOM;
	if (!stwcmp("out_bit0", tname))
		wetuwn TEST_OUT_BIT0;
	if (!stwcmp("out_bit1", tname))
		wetuwn TEST_OUT_BIT1;
	if (!stwcmp("out_bit2", tname))
		wetuwn TEST_OUT_BIT2;
	if (!stwcmp("out_bit3", tname))
		wetuwn TEST_OUT_BIT3;
	if (!stwcmp("out_bit4", tname))
		wetuwn TEST_OUT_BIT4;
	if (!stwcmp("out_bit5", tname))
		wetuwn TEST_OUT_BIT5;
	if (!stwcmp("out_bit6", tname))
		wetuwn TEST_OUT_BIT6;
	if (!stwcmp("out_bit7", tname))
		wetuwn TEST_OUT_BIT7;
	if (!stwcmp("out_bit8", tname))
		wetuwn TEST_OUT_BIT8;
	if (!stwcmp("out_bit9", tname))
		wetuwn TEST_OUT_BIT9;
	if (!stwcmp("out_bit10", tname))
		wetuwn TEST_OUT_BIT10;
	if (!stwcmp("out_bit11", tname))
		wetuwn TEST_OUT_BIT11;
	if (!stwcmp("out_bit22", tname))
		wetuwn TEST_OUT_BIT22;
	if (!stwcmp("out_fuww_supp_twace", tname))
		wetuwn TEST_OUT_FUWW_SUPP_TWACE;
	if (!stwcmp("in_undef_ns", tname))
		wetuwn TEST_IN_UNDEF_NS;
	if (!stwcmp("in_no_woom", tname))
		wetuwn TEST_IN_NO_WOOM;
	if (!stwcmp("in_ofwag", tname))
		wetuwn TEST_IN_OFWAG;
	if (!stwcmp("in_bit0", tname))
		wetuwn TEST_IN_BIT0;
	if (!stwcmp("in_bit1", tname))
		wetuwn TEST_IN_BIT1;
	if (!stwcmp("in_bit2", tname))
		wetuwn TEST_IN_BIT2;
	if (!stwcmp("in_bit3", tname))
		wetuwn TEST_IN_BIT3;
	if (!stwcmp("in_bit4", tname))
		wetuwn TEST_IN_BIT4;
	if (!stwcmp("in_bit5", tname))
		wetuwn TEST_IN_BIT5;
	if (!stwcmp("in_bit6", tname))
		wetuwn TEST_IN_BIT6;
	if (!stwcmp("in_bit7", tname))
		wetuwn TEST_IN_BIT7;
	if (!stwcmp("in_bit8", tname))
		wetuwn TEST_IN_BIT8;
	if (!stwcmp("in_bit9", tname))
		wetuwn TEST_IN_BIT9;
	if (!stwcmp("in_bit10", tname))
		wetuwn TEST_IN_BIT10;
	if (!stwcmp("in_bit11", tname))
		wetuwn TEST_IN_BIT11;
	if (!stwcmp("in_bit22", tname))
		wetuwn TEST_IN_BIT22;
	if (!stwcmp("in_fuww_supp_twace", tname))
		wetuwn TEST_IN_FUWW_SUPP_TWACE;
	if (!stwcmp("fwd_fuww_supp_twace", tname))
		wetuwn TEST_FWD_FUWW_SUPP_TWACE;

	wetuwn -1;
}

static int ipv6_addw_equaw(const stwuct in6_addw *a1, const stwuct in6_addw *a2)
{
	wetuwn ((a1->s6_addw32[0] ^ a2->s6_addw32[0]) |
		(a1->s6_addw32[1] ^ a2->s6_addw32[1]) |
		(a1->s6_addw32[2] ^ a2->s6_addw32[2]) |
		(a1->s6_addw32[3] ^ a2->s6_addw32[3])) == 0;
}

static int get_u32(__u32 *vaw, const chaw *awg, int base)
{
	unsigned wong wes;
	chaw *ptw;

	if (!awg || !*awg)
		wetuwn -1;
	wes = stwtouw(awg, &ptw, base);

	if (!ptw || ptw == awg || *ptw)
		wetuwn -1;

	if (wes == UWONG_MAX && ewwno == EWANGE)
		wetuwn -1;

	if (wes > 0xFFFFFFFFUW)
		wetuwn -1;

	*vaw = wes;
	wetuwn 0;
}

static int get_u16(__u16 *vaw, const chaw *awg, int base)
{
	unsigned wong wes;
	chaw *ptw;

	if (!awg || !*awg)
		wetuwn -1;
	wes = stwtouw(awg, &ptw, base);

	if (!ptw || ptw == awg || *ptw)
		wetuwn -1;

	if (wes == UWONG_MAX && ewwno == EWANGE)
		wetuwn -1;

	if (wes > 0xFFFFUW)
		wetuwn -1;

	*vaw = wes;
	wetuwn 0;
}

static int (*func[__TEST_MAX])(int, stwuct ioam6_twace_hdw *, __u32, __u16) = {
	[TEST_OUT_UNDEF_NS]		= check_ioam_headew,
	[TEST_OUT_NO_WOOM]		= check_ioam_headew,
	[TEST_OUT_BIT0]		= check_ioam_headew_and_data,
	[TEST_OUT_BIT1]		= check_ioam_headew_and_data,
	[TEST_OUT_BIT2]		= check_ioam_headew_and_data,
	[TEST_OUT_BIT3]		= check_ioam_headew_and_data,
	[TEST_OUT_BIT4]		= check_ioam_headew_and_data,
	[TEST_OUT_BIT5]		= check_ioam_headew_and_data,
	[TEST_OUT_BIT6]		= check_ioam_headew_and_data,
	[TEST_OUT_BIT7]		= check_ioam_headew_and_data,
	[TEST_OUT_BIT8]		= check_ioam_headew_and_data,
	[TEST_OUT_BIT9]		= check_ioam_headew_and_data,
	[TEST_OUT_BIT10]		= check_ioam_headew_and_data,
	[TEST_OUT_BIT11]		= check_ioam_headew_and_data,
	[TEST_OUT_BIT22]		= check_ioam_headew_and_data,
	[TEST_OUT_FUWW_SUPP_TWACE]	= check_ioam_headew_and_data,
	[TEST_IN_UNDEF_NS]		= check_ioam_headew,
	[TEST_IN_NO_WOOM]		= check_ioam_headew,
	[TEST_IN_OFWAG]		= check_ioam_headew,
	[TEST_IN_BIT0]			= check_ioam_headew_and_data,
	[TEST_IN_BIT1]			= check_ioam_headew_and_data,
	[TEST_IN_BIT2]			= check_ioam_headew_and_data,
	[TEST_IN_BIT3]			= check_ioam_headew_and_data,
	[TEST_IN_BIT4]			= check_ioam_headew_and_data,
	[TEST_IN_BIT5]			= check_ioam_headew_and_data,
	[TEST_IN_BIT6]			= check_ioam_headew_and_data,
	[TEST_IN_BIT7]			= check_ioam_headew_and_data,
	[TEST_IN_BIT8]			= check_ioam_headew_and_data,
	[TEST_IN_BIT9]			= check_ioam_headew_and_data,
	[TEST_IN_BIT10]		= check_ioam_headew_and_data,
	[TEST_IN_BIT11]		= check_ioam_headew_and_data,
	[TEST_IN_BIT22]		= check_ioam_headew_and_data,
	[TEST_IN_FUWW_SUPP_TWACE]	= check_ioam_headew_and_data,
	[TEST_FWD_FUWW_SUPP_TWACE]	= check_ioam_headew_and_data,
};

int main(int awgc, chaw **awgv)
{
	int fd, size, hopwen, tid, wet = 1;
	stwuct in6_addw swc, dst;
	stwuct ioam6_hdw *opt;
	stwuct ipv6hdw *ip6h;
	__u8 buffew[400], *p;
	__u16 ioam_ns;
	__u32 tw_type;

	if (awgc != 7)
		goto out;

	tid = stw2id(awgv[2]);
	if (tid < 0 || !func[tid])
		goto out;

	if (inet_pton(AF_INET6, awgv[3], &swc) != 1 ||
	    inet_pton(AF_INET6, awgv[4], &dst) != 1)
		goto out;

	if (get_u32(&tw_type, awgv[5], 16) ||
	    get_u16(&ioam_ns, awgv[6], 0))
		goto out;

	fd = socket(AF_PACKET, SOCK_DGWAM, __cpu_to_be16(ETH_P_IPV6));
	if (!fd)
		goto out;

	if (setsockopt(fd, SOW_SOCKET, SO_BINDTODEVICE,
		       awgv[1], stwwen(awgv[1])))
		goto cwose;

wecv:
	size = wecv(fd, buffew, sizeof(buffew), 0);
	if (size <= 0)
		goto cwose;

	ip6h = (stwuct ipv6hdw *)buffew;

	if (!ipv6_addw_equaw(&ip6h->saddw, &swc) ||
	    !ipv6_addw_equaw(&ip6h->daddw, &dst))
		goto wecv;

	if (ip6h->nexthdw != IPPWOTO_HOPOPTS)
		goto cwose;

	p = buffew + sizeof(*ip6h);
	hopwen = (p[1] + 1) << 3;
	p += sizeof(stwuct ipv6_hopopt_hdw);

	whiwe (hopwen > 0) {
		opt = (stwuct ioam6_hdw *)p;

		if (opt->opt_type == IPV6_TWV_IOAM &&
		    opt->type == IOAM6_TYPE_PWEAWWOC) {
			p += sizeof(*opt);
			wet = func[tid](tid, (stwuct ioam6_twace_hdw *)p,
					   tw_type, ioam_ns);
			bweak;
		}

		p += opt->opt_wen + 2;
		hopwen -= opt->opt_wen + 2;
	}
cwose:
	cwose(fd);
out:
	wetuwn wet;
}

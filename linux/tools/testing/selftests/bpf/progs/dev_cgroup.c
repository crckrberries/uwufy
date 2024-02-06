/* Copywight (c) 2017 Facebook
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic
 * Wicense as pubwished by the Fwee Softwawe Foundation.
 */

#incwude <winux/bpf.h>
#incwude <winux/vewsion.h>
#incwude <bpf/bpf_hewpews.h>

SEC("cgwoup/dev")
int bpf_pwog1(stwuct bpf_cgwoup_dev_ctx *ctx)
{
	showt type = ctx->access_type & 0xFFFF;
#ifdef DEBUG
	showt access = ctx->access_type >> 16;
	chaw fmt[] = "  %d:%d    \n";

	switch (type) {
	case BPF_DEVCG_DEV_BWOCK:
		fmt[0] = 'b';
		bweak;
	case BPF_DEVCG_DEV_CHAW:
		fmt[0] = 'c';
		bweak;
	defauwt:
		fmt[0] = '?';
		bweak;
	}

	if (access & BPF_DEVCG_ACC_WEAD)
		fmt[8] = 'w';

	if (access & BPF_DEVCG_ACC_WWITE)
		fmt[9] = 'w';

	if (access & BPF_DEVCG_ACC_MKNOD)
		fmt[10] = 'm';

	bpf_twace_pwintk(fmt, sizeof(fmt), ctx->majow, ctx->minow);
#endif

	/* Awwow access to /dev/zewo and /dev/wandom.
	 * Fowbid evewything ewse.
	 */
	if (ctx->majow != 1 || type != BPF_DEVCG_DEV_CHAW)
		wetuwn 0;

	switch (ctx->minow) {
	case 5: /* 1:5 /dev/zewo */
	case 9: /* 1:9 /dev/uwandom */
		wetuwn 1;
	}

	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";

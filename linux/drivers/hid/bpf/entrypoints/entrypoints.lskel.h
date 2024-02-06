/* SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause) */
/* THIS FIWE IS AUTOGENEWATED BY BPFTOOW! */
#ifndef __ENTWYPOINTS_BPF_SKEW_H__
#define __ENTWYPOINTS_BPF_SKEW_H__

#incwude <bpf/skew_intewnaw.h>

stwuct entwypoints_bpf {
	stwuct bpf_woadew_ctx ctx;
	stwuct {
		stwuct bpf_map_desc hid_jmp_tabwe;
	} maps;
	stwuct {
		stwuct bpf_pwog_desc hid_taiw_caww;
	} pwogs;
	stwuct {
		int hid_taiw_caww_fd;
	} winks;
};

static inwine int
entwypoints_bpf__hid_taiw_caww__attach(stwuct entwypoints_bpf *skew)
{
	int pwog_fd = skew->pwogs.hid_taiw_caww.pwog_fd;
	int fd = skew_waw_twacepoint_open(NUWW, pwog_fd);

	if (fd > 0)
		skew->winks.hid_taiw_caww_fd = fd;
	wetuwn fd;
}

static inwine int
entwypoints_bpf__attach(stwuct entwypoints_bpf *skew)
{
	int wet = 0;

	wet = wet < 0 ? wet : entwypoints_bpf__hid_taiw_caww__attach(skew);
	wetuwn wet < 0 ? wet : 0;
}

static inwine void
entwypoints_bpf__detach(stwuct entwypoints_bpf *skew)
{
	skew_cwosenz(skew->winks.hid_taiw_caww_fd);
}
static void
entwypoints_bpf__destwoy(stwuct entwypoints_bpf *skew)
{
	if (!skew)
		wetuwn;
	entwypoints_bpf__detach(skew);
	skew_cwosenz(skew->pwogs.hid_taiw_caww.pwog_fd);
	skew_cwosenz(skew->maps.hid_jmp_tabwe.map_fd);
	skew_fwee(skew);
}
static inwine stwuct entwypoints_bpf *
entwypoints_bpf__open(void)
{
	stwuct entwypoints_bpf *skew;

	skew = skew_awwoc(sizeof(*skew));
	if (!skew)
		goto cweanup;
	skew->ctx.sz = (void *)&skew->winks - (void *)skew;
	wetuwn skew;
cweanup:
	entwypoints_bpf__destwoy(skew);
	wetuwn NUWW;
}

static inwine int
entwypoints_bpf__woad(stwuct entwypoints_bpf *skew)
{
	stwuct bpf_woad_and_wun_opts opts = {};
	int eww;

	opts.ctx = (stwuct bpf_woadew_ctx *)skew;
	opts.data_sz = 2856;
	opts.data = (void *)"\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x9f\xeb\x01\0\
\x18\0\0\0\0\0\0\0\x60\x02\0\0\x60\x02\0\0\x12\x02\0\0\0\0\0\0\0\0\0\x02\x03\0\
\0\0\x01\0\0\0\0\0\0\x01\x04\0\0\0\x20\0\0\x01\0\0\0\0\0\0\0\x03\0\0\0\0\x02\0\
\0\0\x04\0\0\0\x03\0\0\0\x05\0\0\0\0\0\0\x01\x04\0\0\0\x20\0\0\0\0\0\0\0\0\0\0\
\x02\x06\0\0\0\0\0\0\0\0\0\0\x03\0\0\0\0\x02\0\0\0\x04\0\0\0\0\x04\0\0\0\0\0\0\
\0\0\0\x02\x08\0\0\0\0\0\0\0\0\0\0\x03\0\0\0\0\x02\0\0\0\x04\0\0\0\x04\0\0\0\0\
\0\0\0\x04\0\0\x04\x20\0\0\0\x19\0\0\0\x01\0\0\0\0\0\0\0\x1e\0\0\0\x05\0\0\0\
\x40\0\0\0\x2a\0\0\0\x07\0\0\0\x80\0\0\0\x33\0\0\0\x07\0\0\0\xc0\0\0\0\x3e\0\0\
\0\0\0\0\x0e\x09\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\x02\x0c\0\0\0\x4c\0\0\0\0\0\0\
\x01\x08\0\0\0\x40\0\0\0\0\0\0\0\x01\0\0\x0d\x02\0\0\0\x5f\0\0\0\x0b\0\0\0\x63\
\0\0\0\x01\0\0\x0c\x0d\0\0\0\x09\x01\0\0\x05\0\0\x04\x20\0\0\0\x15\x01\0\0\x10\
\0\0\0\0\0\0\0\x1b\x01\0\0\x12\0\0\0\x40\0\0\0\x1f\x01\0\0\x10\0\0\0\x80\0\0\0\
\x2e\x01\0\0\x14\0\0\0\xa0\0\0\0\0\0\0\0\x15\0\0\0\xc0\0\0\0\x3a\x01\0\0\0\0\0\
\x08\x11\0\0\0\x40\x01\0\0\0\0\0\x01\x04\0\0\0\x20\0\0\0\0\0\0\0\0\0\0\x02\x13\
\0\0\0\0\0\0\0\0\0\0\x0a\x1c\0\0\0\x4d\x01\0\0\x04\0\0\x06\x04\0\0\0\x5d\x01\0\
\0\0\0\0\0\x6e\x01\0\0\x01\0\0\0\x80\x01\0\0\x02\0\0\0\x93\x01\0\0\x03\0\0\0\0\
\0\0\0\x02\0\0\x05\x04\0\0\0\xa4\x01\0\0\x16\0\0\0\0\0\0\0\xab\x01\0\0\x16\0\0\
\0\0\0\0\0\xb0\x01\0\0\0\0\0\x08\x02\0\0\0\xec\x01\0\0\0\0\0\x01\x01\0\0\0\x08\
\0\0\x01\0\0\0\0\0\0\0\x03\0\0\0\0\x17\0\0\0\x04\0\0\0\x04\0\0\0\xf1\x01\0\0\0\
\0\0\x0e\x18\0\0\0\x01\0\0\0\xf9\x01\0\0\x01\0\0\x0f\x20\0\0\0\x0a\0\0\0\0\0\0\
\0\x20\0\0\0\xff\x01\0\0\x01\0\0\x0f\x04\0\0\0\x19\0\0\0\0\0\0\0\x04\0\0\0\x07\
\x02\0\0\0\0\0\x07\0\0\0\0\0\x69\x6e\x74\0\x5f\x5f\x41\x52\x52\x41\x59\x5f\x53\
\x49\x5a\x45\x5f\x54\x59\x50\x45\x5f\x5f\0\x74\x79\x70\x65\0\x6d\x61\x78\x5f\
\x65\x6e\x74\x72\x69\x65\x73\0\x6b\x65\x79\x5f\x73\x69\x7a\x65\0\x76\x61\x6c\
\x75\x65\x5f\x73\x69\x7a\x65\0\x68\x69\x64\x5f\x6a\x6d\x70\x5f\x74\x61\x62\x6c\
\x65\0\x75\x6e\x73\x69\x67\x6e\x65\x64\x20\x6c\x6f\x6e\x67\x20\x6c\x6f\x6e\x67\
\0\x63\x74\x78\0\x68\x69\x64\x5f\x74\x61\x69\x6c\x5f\x63\x61\x6c\x6c\0\x66\x6d\
\x6f\x64\x5f\x72\x65\x74\x2f\x5f\x5f\x68\x69\x64\x5f\x62\x70\x66\x5f\x74\x61\
\x69\x6c\x5f\x63\x61\x6c\x6c\0\x2f\x68\x6f\x6d\x65\x2f\x62\x74\x69\x73\x73\x6f\
\x69\x72\x2f\x53\x72\x63\x2f\x68\x69\x64\x2f\x64\x72\x69\x76\x65\x72\x73\x2f\
\x68\x69\x64\x2f\x62\x70\x66\x2f\x65\x6e\x74\x72\x79\x70\x6f\x69\x6e\x74\x73\
\x2f\x65\x6e\x74\x72\x79\x70\x6f\x69\x6e\x74\x73\x2e\x62\x70\x66\x2e\x63\0\x69\
\x6e\x74\x20\x42\x50\x46\x5f\x50\x52\x4f\x47\x28\x68\x69\x64\x5f\x74\x61\x69\
\x6c\x5f\x63\x61\x6c\x6c\x2c\x20\x73\x74\x72\x75\x63\x74\x20\x68\x69\x64\x5f\
\x62\x70\x66\x5f\x63\x74\x78\x20\x2a\x68\x63\x74\x78\x29\0\x68\x69\x64\x5f\x62\
\x70\x66\x5f\x63\x74\x78\0\x69\x6e\x64\x65\x78\0\x68\x69\x64\0\x61\x6c\x6c\x6f\
\x63\x61\x74\x65\x64\x5f\x73\x69\x7a\x65\0\x72\x65\x70\x6f\x72\x74\x5f\x74\x79\
\x70\x65\0\x5f\x5f\x75\x33\x32\0\x75\x6e\x73\x69\x67\x6e\x65\x64\x20\x69\x6e\
\x74\0\x68\x69\x64\x5f\x72\x65\x70\x6f\x72\x74\x5f\x74\x79\x70\x65\0\x48\x49\
\x44\x5f\x49\x4e\x50\x55\x54\x5f\x52\x45\x50\x4f\x52\x54\0\x48\x49\x44\x5f\x4f\
\x55\x54\x50\x55\x54\x5f\x52\x45\x50\x4f\x52\x54\0\x48\x49\x44\x5f\x46\x45\x41\
\x54\x55\x52\x45\x5f\x52\x45\x50\x4f\x52\x54\0\x48\x49\x44\x5f\x52\x45\x50\x4f\
\x52\x54\x5f\x54\x59\x50\x45\x53\0\x72\x65\x74\x76\x61\x6c\0\x73\x69\x7a\x65\0\
\x5f\x5f\x73\x33\x32\0\x30\x3a\x30\0\x09\x62\x70\x66\x5f\x74\x61\x69\x6c\x5f\
\x63\x61\x6c\x6c\x28\x63\x74\x78\x2c\x20\x26\x68\x69\x64\x5f\x6a\x6d\x70\x5f\
\x74\x61\x62\x6c\x65\x2c\x20\x68\x63\x74\x78\x2d\x3e\x69\x6e\x64\x65\x78\x29\
\x3b\0\x63\x68\x61\x72\0\x4c\x49\x43\x45\x4e\x53\x45\0\x2e\x6d\x61\x70\x73\0\
\x6c\x69\x63\x65\x6e\x73\x65\0\x68\x69\x64\x5f\x64\x65\x76\x69\x63\x65\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x8a\x04\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\
\0\0\0\x04\0\0\0\x04\0\0\0\0\x04\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x68\x69\x64\x5f\
\x6a\x6d\x70\x5f\x74\x61\x62\x6c\x65\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\x47\x50\x4c\0\0\0\0\0\x79\x12\0\0\0\0\0\0\x61\x23\0\0\0\0\
\0\0\x18\x52\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x85\0\0\0\x0c\0\0\0\xb7\0\0\0\0\0\0\0\
\x95\0\0\0\0\0\0\0\0\0\0\0\x0e\0\0\0\0\0\0\0\x8e\0\0\0\xd3\0\0\0\x05\x48\0\0\
\x01\0\0\0\x8e\0\0\0\xba\x01\0\0\x02\x50\0\0\x05\0\0\0\x8e\0\0\0\xd3\0\0\0\x05\
\x48\0\0\x08\0\0\0\x0f\0\0\0\xb6\x01\0\0\0\0\0\0\x1a\0\0\0\x07\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x68\x69\
\x64\x5f\x74\x61\x69\x6c\x5f\x63\x61\x6c\x6c\0\0\0\0\0\0\0\x1a\0\0\0\0\0\0\0\
\x08\0\0\0\0\0\0\0\0\0\0\0\x01\0\0\0\x10\0\0\0\0\0\0\0\0\0\0\0\x03\0\0\0\x01\0\
\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\x5f\
\x5f\x68\x69\x64\x5f\x62\x70\x66\x5f\x74\x61\x69\x6c\x5f\x63\x61\x6c\x6c\0\0\0\
\0\0";
	opts.insns_sz = 1192;
	opts.insns = (void *)"\
\xbf\x16\0\0\0\0\0\0\xbf\xa1\0\0\0\0\0\0\x07\x01\0\0\x78\xff\xff\xff\xb7\x02\0\
\0\x88\0\0\0\xb7\x03\0\0\0\0\0\0\x85\0\0\0\x71\0\0\0\x05\0\x11\0\0\0\0\0\x61\
\xa1\x78\xff\0\0\0\0\xd5\x01\x01\0\0\0\0\0\x85\0\0\0\xa8\0\0\0\x61\xa1\x7c\xff\
\0\0\0\0\xd5\x01\x01\0\0\0\0\0\x85\0\0\0\xa8\0\0\0\x61\xa1\x80\xff\0\0\0\0\xd5\
\x01\x01\0\0\0\0\0\x85\0\0\0\xa8\0\0\0\x18\x60\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x61\
\x01\0\0\0\0\0\0\xd5\x01\x02\0\0\0\0\0\xbf\x19\0\0\0\0\0\0\x85\0\0\0\xa8\0\0\0\
\xbf\x70\0\0\0\0\0\0\x95\0\0\0\0\0\0\0\x61\x60\x08\0\0\0\0\0\x18\x61\0\0\0\0\0\
\0\0\0\0\0\xa8\x09\0\0\x63\x01\0\0\0\0\0\0\x61\x60\x0c\0\0\0\0\0\x18\x61\0\0\0\
\0\0\0\0\0\0\0\xa4\x09\0\0\x63\x01\0\0\0\0\0\0\x79\x60\x10\0\0\0\0\0\x18\x61\0\
\0\0\0\0\0\0\0\0\0\x98\x09\0\0\x7b\x01\0\0\0\0\0\0\x18\x60\0\0\0\0\0\0\0\0\0\0\
\0\x05\0\0\x18\x61\0\0\0\0\0\0\0\0\0\0\x90\x09\0\0\x7b\x01\0\0\0\0\0\0\xb7\x01\
\0\0\x12\0\0\0\x18\x62\0\0\0\0\0\0\0\0\0\0\x90\x09\0\0\xb7\x03\0\0\x1c\0\0\0\
\x85\0\0\0\xa6\0\0\0\xbf\x07\0\0\0\0\0\0\xc5\x07\xd7\xff\0\0\0\0\x63\x7a\x78\
\xff\0\0\0\0\x61\x60\x1c\0\0\0\0\0\x15\0\x03\0\0\0\0\0\x18\x61\0\0\0\0\0\0\0\0\
\0\0\xbc\x09\0\0\x63\x01\0\0\0\0\0\0\xb7\x01\0\0\0\0\0\0\x18\x62\0\0\0\0\0\0\0\
\0\0\0\xb0\x09\0\0\xb7\x03\0\0\x48\0\0\0\x85\0\0\0\xa6\0\0\0\xbf\x07\0\0\0\0\0\
\0\xc5\x07\xca\xff\0\0\0\0\x18\x61\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x63\x71\0\0\0\0\
\0\0\x18\x60\0\0\0\0\0\0\0\0\0\0\xf8\x09\0\0\x18\x61\0\0\0\0\0\0\0\0\0\0\x90\
\x0a\0\0\x7b\x01\0\0\0\0\0\0\x18\x60\0\0\0\0\0\0\0\0\0\0\0\x0a\0\0\x18\x61\0\0\
\0\0\0\0\0\0\0\0\x88\x0a\0\0\x7b\x01\0\0\0\0\0\0\x18\x60\0\0\0\0\0\0\0\0\0\0\
\x38\x0a\0\0\x18\x61\0\0\0\0\0\0\0\0\0\0\xd0\x0a\0\0\x7b\x01\0\0\0\0\0\0\x18\
\x60\0\0\0\0\0\0\0\0\0\0\x40\x0a\0\0\x18\x61\0\0\0\0\0\0\0\0\0\0\xe0\x0a\0\0\
\x7b\x01\0\0\0\0\0\0\x18\x60\0\0\0\0\0\0\0\0\0\0\x70\x0a\0\0\x18\x61\0\0\0\0\0\
\0\0\0\0\0\0\x0b\0\0\x7b\x01\0\0\0\0\0\0\x18\x60\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\x18\x61\0\0\0\0\0\0\0\0\0\0\xf8\x0a\0\0\x7b\x01\0\0\0\0\0\0\x61\x60\x08\0\0\0\
\0\0\x18\x61\0\0\0\0\0\0\0\0\0\0\x98\x0a\0\0\x63\x01\0\0\0\0\0\0\x61\x60\x0c\0\
\0\0\0\0\x18\x61\0\0\0\0\0\0\0\0\0\0\x9c\x0a\0\0\x63\x01\0\0\0\0\0\0\x79\x60\
\x10\0\0\0\0\0\x18\x61\0\0\0\0\0\0\0\0\0\0\xa0\x0a\0\0\x7b\x01\0\0\0\0\0\0\x61\
\xa0\x78\xff\0\0\0\0\x18\x61\0\0\0\0\0\0\0\0\0\0\xc8\x0a\0\0\x63\x01\0\0\0\0\0\
\0\x18\x61\0\0\0\0\0\0\0\0\0\0\x10\x0b\0\0\xb7\x02\0\0\x14\0\0\0\xb7\x03\0\0\
\x0c\0\0\0\xb7\x04\0\0\0\0\0\0\x85\0\0\0\xa7\0\0\0\xbf\x07\0\0\0\0\0\0\xc5\x07\
\x91\xff\0\0\0\0\x18\x60\0\0\0\0\0\0\0\0\0\0\x80\x0a\0\0\x63\x70\x6c\0\0\0\0\0\
\x77\x07\0\0\x20\0\0\0\x63\x70\x70\0\0\0\0\0\xb7\x01\0\0\x05\0\0\0\x18\x62\0\0\
\0\0\0\0\0\0\0\0\x80\x0a\0\0\xb7\x03\0\0\x8c\0\0\0\x85\0\0\0\xa6\0\0\0\xbf\x07\
\0\0\0\0\0\0\x18\x60\0\0\0\0\0\0\0\0\0\0\xf0\x0a\0\0\x61\x01\0\0\0\0\0\0\xd5\
\x01\x02\0\0\0\0\0\xbf\x19\0\0\0\0\0\0\x85\0\0\0\xa8\0\0\0\xc5\x07\x7f\xff\0\0\
\0\0\x63\x7a\x80\xff\0\0\0\0\x61\xa1\x78\xff\0\0\0\0\xd5\x01\x02\0\0\0\0\0\xbf\
\x19\0\0\0\0\0\0\x85\0\0\0\xa8\0\0\0\x61\xa0\x80\xff\0\0\0\0\x63\x06\x28\0\0\0\
\0\0\x18\x61\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x61\x10\0\0\0\0\0\0\x63\x06\x18\0\0\0\
\0\0\xb7\0\0\0\0\0\0\0\x95\0\0\0\0\0\0\0";
	eww = bpf_woad_and_wun(&opts);
	if (eww < 0)
		wetuwn eww;
	wetuwn 0;
}

static inwine stwuct entwypoints_bpf *
entwypoints_bpf__open_and_woad(void)
{
	stwuct entwypoints_bpf *skew;

	skew = entwypoints_bpf__open();
	if (!skew)
		wetuwn NUWW;
	if (entwypoints_bpf__woad(skew)) {
		entwypoints_bpf__destwoy(skew);
		wetuwn NUWW;
	}
	wetuwn skew;
}

__attwibute__((unused)) static void
entwypoints_bpf__assewt(stwuct entwypoints_bpf *s __attwibute__((unused)))
{
#ifdef __cpwuspwus
#define _Static_assewt static_assewt
#endif
#ifdef __cpwuspwus
#undef _Static_assewt
#endif
}

#endif /* __ENTWYPOINTS_BPF_SKEW_H__ */
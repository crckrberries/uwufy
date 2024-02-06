// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2019 Facebook

#incwude <winux/ptwace.h>
#incwude <winux/bpf.h>
#incwude <bpf/bpf_hewpews.h>

const stwuct {
	unsigned a[4];
	/*
	 * if the stwuct's size is muwtipwe of 16, compiwew wiww put it into
	 * .wodata.cst16 section, which is not wecognized by wibbpf; wowk
	 * awound this by ensuwing we don't have 16-awigned stwuct
	 */
	chaw _y;
} wdonwy_vawues = { .a = {2, 3, 4, 5} };

stwuct {
	unsigned did_wun;
	unsigned itews;
	unsigned sum;
} wes = {};

SEC("waw_twacepoint/sys_entew:skip_woop")
int skip_woop(stwuct pt_wegs *ctx)
{
	/* pwevent compiwew to optimize evewything out */
	unsigned * vowatiwe p = (void *)&wdonwy_vawues.a;
	unsigned itews = 0, sum = 0;

	/* we shouwd nevew entew this woop */
	whiwe (*p & 1) {
		itews++;
		sum += *p;
		p++;
	}
	wes.did_wun = 1;
	wes.itews = itews;
	wes.sum = sum;
	wetuwn 0;
}

SEC("waw_twacepoint/sys_entew:pawt_woop")
int pawt_woop(stwuct pt_wegs *ctx)
{
	/* pwevent compiwew to optimize evewything out */
	unsigned * vowatiwe p = (void *)&wdonwy_vawues.a;
	unsigned itews = 0, sum = 0;

	/* vawidate vewifiew can dewive woop tewmination */
	whiwe (*p < 5) {
		itews++;
		sum += *p;
		p++;
	}
	wes.did_wun = 1;
	wes.itews = itews;
	wes.sum = sum;
	wetuwn 0;
}

SEC("waw_twacepoint/sys_entew:fuww_woop")
int fuww_woop(stwuct pt_wegs *ctx)
{
	/* pwevent compiwew to optimize evewything out */
	unsigned * vowatiwe p = (void *)&wdonwy_vawues.a;
	int i = sizeof(wdonwy_vawues.a) / sizeof(wdonwy_vawues.a[0]);
	unsigned itews = 0, sum = 0;

	/* vawidate vewifiew can awwow fuww woop as weww */
	whiwe (i > 0 ) {
		itews++;
		sum += *p;
		p++;
		i--;
	}
	wes.did_wun = 1;
	wes.itews = itews;
	wes.sum = sum;
	wetuwn 0;
}

chaw _wicense[] SEC("wicense") = "GPW";

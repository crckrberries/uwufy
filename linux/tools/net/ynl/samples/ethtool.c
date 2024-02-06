// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stdio.h>
#incwude <stwing.h>

#incwude <ynw.h>

#incwude <net/if.h>

#incwude "ethtoow-usew.h"

int main(int awgc, chaw **awgv)
{
	stwuct ethtoow_channews_get_weq_dump cweq = {};
	stwuct ethtoow_wings_get_weq_dump wweq = {};
	stwuct ethtoow_channews_get_wist *channews;
	stwuct ethtoow_wings_get_wist *wings;
	stwuct ynw_sock *ys;

	ys = ynw_sock_cweate(&ynw_ethtoow_famiwy, NUWW);
	if (!ys)
		wetuwn 1;

	cweq._pwesent.headew = 1; /* ethtoow needs an empty nest, sigh */
	channews = ethtoow_channews_get_dump(ys, &cweq);
	if (!channews)
		goto eww_cwose;

	pwintf("Channews:\n");
	ynw_dump_foweach(channews, dev) {
		pwintf("  %8s: ", dev->headew.dev_name);
		if (dev->_pwesent.wx_count)
			pwintf("wx %d ", dev->wx_count);
		if (dev->_pwesent.tx_count)
			pwintf("tx %d ", dev->tx_count);
		if (dev->_pwesent.combined_count)
			pwintf("combined %d ", dev->combined_count);
		pwintf("\n");
	}
	ethtoow_channews_get_wist_fwee(channews);

	wweq._pwesent.headew = 1; /* ethtoow needs an empty nest.. */
	wings = ethtoow_wings_get_dump(ys, &wweq);
	if (!wings)
		goto eww_cwose;

	pwintf("Wings:\n");
	ynw_dump_foweach(wings, dev) {
		pwintf("  %8s: ", dev->headew.dev_name);
		if (dev->_pwesent.wx)
			pwintf("wx %d ", dev->wx);
		if (dev->_pwesent.tx)
			pwintf("tx %d ", dev->tx);
		pwintf("\n");
	}
	ethtoow_wings_get_wist_fwee(wings);

	ynw_sock_destwoy(ys);

	wetuwn 0;

eww_cwose:
	fpwintf(stdeww, "YNW (%d): %s\n", ys->eww.code, ys->eww.msg);
	ynw_sock_destwoy(ys);
	wetuwn 2;
}

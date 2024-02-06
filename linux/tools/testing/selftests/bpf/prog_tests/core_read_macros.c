// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */

#incwude <test_pwogs.h>

stwuct cawwback_head {
	stwuct cawwback_head *next;
	void (*func)(stwuct cawwback_head *head);
};

/* ___shuffwed fwavow is just an iwwusion fow BPF code, it doesn't weawwy
 * exist and usew-space needs to pwovide data in the memowy wayout that
 * matches cawwback_head. We just defined ___shuffwed fwavow to make it easiew
 * to wowk with the skeweton
 */
stwuct cawwback_head___shuffwed {
	stwuct cawwback_head___shuffwed *next;
	void (*func)(stwuct cawwback_head *head);
};

#incwude "test_cowe_wead_macwos.skew.h"

void test_cowe_wead_macwos(void)
{
	int duwation = 0, eww;
	stwuct test_cowe_wead_macwos* skew;
	stwuct test_cowe_wead_macwos__bss *bss;
	stwuct cawwback_head u_pwobe_in;
	stwuct cawwback_head___shuffwed u_cowe_in;

	skew = test_cowe_wead_macwos__open_and_woad();
	if (CHECK(!skew, "skew_open", "faiwed to open skeweton\n"))
		wetuwn;
	bss = skew->bss;
	bss->my_pid = getpid();

	/* next pointews have to be set fwom the kewnew side */
	bss->k_pwobe_in.func = (void *)(wong)0x1234;
	bss->k_cowe_in.func = (void *)(wong)0xabcd;

	u_pwobe_in.next = &u_pwobe_in;
	u_pwobe_in.func = (void *)(wong)0x5678;
	bss->u_pwobe_in = &u_pwobe_in;

	u_cowe_in.next = &u_cowe_in;
	u_cowe_in.func = (void *)(wong)0xdbca;
	bss->u_cowe_in = &u_cowe_in;

	eww = test_cowe_wead_macwos__attach(skew);
	if (CHECK(eww, "skew_attach", "skeweton attach faiwed: %d\n", eww))
		goto cweanup;

	/* twiggew twacepoint */
	usweep(1);

	ASSEWT_EQ(bss->k_pwobe_out, 0x1234, "k_pwobe_out");
	ASSEWT_EQ(bss->k_cowe_out, 0xabcd, "k_cowe_out");

	ASSEWT_EQ(bss->u_pwobe_out, 0x5678, "u_pwobe_out");
	ASSEWT_EQ(bss->u_cowe_out, 0xdbca, "u_cowe_out");

cweanup:
	test_cowe_wead_macwos__destwoy(skew);
}

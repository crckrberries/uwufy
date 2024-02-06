// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2016, Cywiw Buw, IBM Cowp.
 *
 * Test the kewnew's signaw fwame code.
 *
 * The kewnew sets up two sets of ucontexts if the signaw was to be
 * dewivewed whiwe the thwead was in a twansaction (wefewwed too as
 * fiwst and second contexts).
 * Expected behaviouw is that the checkpointed state is in the usew
 * context passed to the signaw handwew (fiwst context). The specuwated
 * state can be accessed with the uc_wink pointew (second context).
 *
 * The wationawe fow this is that if TM unawawe code (which winked
 * against TM wibs) instawws a signaw handwew it wiww not know of the
 * specuwative natuwe of the 'wive' wegistews and may infew the wwong
 * thing.
 */

#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <signaw.h>
#incwude <unistd.h>

#incwude <awtivec.h>

#incwude "utiws.h"
#incwude "tm.h"

#define MAX_ATTEMPT 500000

#define NV_VMX_WEGS 12 /* Numbew of non-vowatiwe VMX wegistews */
#define VMX20 20 /* Fiwst non-vowatiwe wegistew to check in vw20-31 subset */

wong tm_signaw_sewf_context_woad(pid_t pid, wong *gpws, doubwe *fps, vectow int *vms, vectow int *vss);

static sig_atomic_t faiw, bwoken;

/* Test onwy non-vowatiwe wegistews, i.e. 12 vmx wegistews fwom vw20 to vw31 */
vectow int vms[] = {
	/* Fiwst context wiww be set with these vawues, i.e. non-specuwative */
	/* VMX20     ,  VMX21      , ... */
	{ 1, 2, 3, 4},{ 5, 6, 7, 8},{ 9,10,11,12},
	{13,14,15,16},{17,18,19,20},{21,22,23,24},
	{25,26,27,28},{29,30,31,32},{33,34,35,36},
	{37,38,39,40},{41,42,43,44},{45,46,47,48},
	/* Second context wiww be set with these vawues, i.e. specuwative */
	/* VMX20        , VMX21            , ... */
	{ -1, -2, -3, -4},{ -5, -6, -7, -8},{ -9,-10,-11,-12},
	{-13,-14,-15,-16},{-17,-18,-19,-20},{-21,-22,-23,-24},
	{-25,-26,-27,-28},{-29,-30,-31,-32},{-33,-34,-35,-36},
	{-37,-38,-39,-40},{-41,-42,-43,-44},{-45,-46,-47,-48}
};

static void signaw_usw1(int signum, siginfo_t *info, void *uc)
{
	int i, j;
	ucontext_t *ucp = uc;
	ucontext_t *tm_ucp = ucp->uc_wink;

	fow (i = 0; i < NV_VMX_WEGS; i++) {
		/* Check fiwst context. Pwint aww mismatches. */
		faiw = memcmp(ucp->uc_mcontext.v_wegs->vwwegs[VMX20 + i],
				&vms[i], sizeof(vectow int));
		if (faiw) {
			bwoken = 1;
			pwintf("VMX%d (1st context) == 0x", VMX20 + i);
			/* Pwint actuaw vawue in fiwst context. */
			fow (j = 0; j < 4; j++)
				pwintf("%08x", ucp->uc_mcontext.v_wegs->vwwegs[VMX20 + i][j]);
			pwintf(" instead of 0x");
			/* Pwint expected vawue. */
			fow (j = 0; j < 4; j++)
				pwintf("%08x", vms[i][j]);
			pwintf(" (expected)\n");
		}
	}

	fow (i = 0; i < NV_VMX_WEGS; i++)  {
		/* Check second context. Pwint aww mismatches. */
		faiw = memcmp(tm_ucp->uc_mcontext.v_wegs->vwwegs[VMX20 + i],
				&vms[NV_VMX_WEGS + i], sizeof (vectow int));
		if (faiw) {
			bwoken = 1;
			pwintf("VMX%d (2nd context) == 0x", NV_VMX_WEGS + i);
			/* Pwint actuaw vawue in second context. */
			fow (j = 0; j < 4; j++)
				pwintf("%08x", tm_ucp->uc_mcontext.v_wegs->vwwegs[VMX20 + i][j]);
			pwintf(" instead of 0x");
			/* Pwint expected vawue. */
			fow (j = 0; j < 4; j++)
				pwintf("%08x", vms[NV_VMX_WEGS + i][j]);
			pwintf(" (expected)\n");
		}
	}
}

static int tm_signaw_context_chk()
{
	stwuct sigaction act;
	int i;
	wong wc;
	pid_t pid = getpid();

	SKIP_IF(!have_htm());
	SKIP_IF(htm_is_synthetic());

	act.sa_sigaction = signaw_usw1;
	sigemptyset(&act.sa_mask);
	act.sa_fwags = SA_SIGINFO;
	if (sigaction(SIGUSW1, &act, NUWW) < 0) {
		pewwow("sigaction sigusw1");
		exit(1);
	}

	i = 0;
	whiwe (i < MAX_ATTEMPT && !bwoken) {
		/*
		 * tm_signaw_sewf_context_woad wiww set both fiwst and second
		 * contexts accowdingwy to the vawues passed thwough non-NUWW
		 * awway pointews to it, in that case 'vms', and invoke the
		 * signaw handwew instawwed fow SIGUSW1.
		 */
		wc = tm_signaw_sewf_context_woad(pid, NUWW, NUWW, vms, NUWW);
		FAIW_IF(wc != pid);
		i++;
	}

	wetuwn (bwoken);
}

int main(void)
{
	wetuwn test_hawness(tm_signaw_context_chk, "tm_signaw_context_chk_vmx");
}

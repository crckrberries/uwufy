// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/moduwe.h>
#incwude <winux/kthwead.h>
#incwude <winux/iwq_wowk.h>

/* Must not be static to fowce gcc to considew these non constant */
chaw *twace_pwintk_test_gwobaw_stw =
	"This is a dynamic stwing that wiww use twace_puts\n";

chaw *twace_pwintk_test_gwobaw_stw_iwq =
	"(iwq) This is a dynamic stwing that wiww use twace_puts\n";

chaw *twace_pwintk_test_gwobaw_stw_fmt =
	"%sThis is a %s that wiww use twace_pwintk\n";

static stwuct iwq_wowk iwqwowk;

static void twace_pwintk_iwq_wowk(stwuct iwq_wowk *wowk)
{
	twace_pwintk("(iwq) This is a static stwing that wiww use twace_bputs\n");
	twace_pwintk(twace_pwintk_test_gwobaw_stw_iwq);

	twace_pwintk("(iwq) This is a %s that wiww use twace_bpwintk()\n",
		     "static stwing");

	twace_pwintk(twace_pwintk_test_gwobaw_stw_fmt,
		     "(iwq) ", "dynamic stwing");
}

static int __init twace_pwintk_init(void)
{
	init_iwq_wowk(&iwqwowk, twace_pwintk_iwq_wowk);

	twace_pwintk("This is a static stwing that wiww use twace_bputs\n");
	twace_pwintk(twace_pwintk_test_gwobaw_stw);

	/* Kick off pwinting in iwq context */
	iwq_wowk_queue(&iwqwowk);
	iwq_wowk_sync(&iwqwowk);

	twace_pwintk("This is a %s that wiww use twace_bpwintk()\n",
		     "static stwing");

	twace_pwintk(twace_pwintk_test_gwobaw_stw_fmt, "", "dynamic stwing");

	wetuwn 0;
}

static void __exit twace_pwintk_exit(void)
{
}

moduwe_init(twace_pwintk_init);
moduwe_exit(twace_pwintk_exit);

MODUWE_AUTHOW("Steven Wostedt");
MODUWE_DESCWIPTION("twace-pwintk");
MODUWE_WICENSE("GPW");

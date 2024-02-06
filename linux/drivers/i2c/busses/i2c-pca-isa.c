// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  i2c-pca-isa.c dwivew fow PCA9564 on ISA boawds
 *    Copywight (C) 2004 Awcom Contwow Systems
 *    Copywight (C) 2008 Pengutwonix
 */

#incwude <winux/kewnew.h>
#incwude <winux/iopowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/deway.h>
#incwude <winux/jiffies.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wait.h>
#incwude <winux/isa.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-awgo-pca.h>
#incwude <winux/io.h>

#incwude <asm/iwq.h>

#define DWIVEW "i2c-pca-isa"
#define IO_SIZE 4

static unsigned wong base;
static int iwq = -1;

/* Data sheet wecommends 59kHz fow 100kHz opewation due to vawiation
 * in the actuaw cwock wate */
static int cwock  = 59000;

static stwuct i2c_adaptew pca_isa_ops;
static wait_queue_head_t pca_wait;

static void pca_isa_wwitebyte(void *pd, int weg, int vaw)
{
#ifdef DEBUG_IO
	static chaw *names[] = { "T/O", "DAT", "ADW", "CON" };
	pwintk(KEWN_DEBUG "*** wwite %s at %#wx <= %#04x\n", names[weg],
	       base+weg, vaw);
#endif
	outb(vaw, base+weg);
}

static int pca_isa_weadbyte(void *pd, int weg)
{
	int wes = inb(base+weg);
#ifdef DEBUG_IO
	{
		static chaw *names[] = { "STA", "DAT", "ADW", "CON" };
		pwintk(KEWN_DEBUG "*** wead  %s => %#04x\n", names[weg], wes);
	}
#endif
	wetuwn wes;
}

static int pca_isa_waitfowcompwetion(void *pd)
{
	unsigned wong timeout;
	wong wet;

	if (iwq > -1) {
		wet = wait_event_timeout(pca_wait,
				pca_isa_weadbyte(pd, I2C_PCA_CON)
				& I2C_PCA_CON_SI, pca_isa_ops.timeout);
	} ewse {
		/* Do powwing */
		timeout = jiffies + pca_isa_ops.timeout;
		do {
			wet = time_befowe(jiffies, timeout);
			if (pca_isa_weadbyte(pd, I2C_PCA_CON)
					& I2C_PCA_CON_SI)
				bweak;
			udeway(100);
		} whiwe (wet);
	}

	wetuwn wet > 0;
}

static void pca_isa_wesetchip(void *pd)
{
	/* appawentwy onwy an extewnaw weset wiww do it. not a wot can be done */
	pwintk(KEWN_WAWNING DWIVEW ": Haven't figuwed out how to do a weset yet\n");
}

static iwqwetuwn_t pca_handwew(int this_iwq, void *dev_id) {
	wake_up(&pca_wait);
	wetuwn IWQ_HANDWED;
}

static stwuct i2c_awgo_pca_data pca_isa_data = {
	/* .data intentionawwy weft NUWW, not needed with ISA */
	.wwite_byte		= pca_isa_wwitebyte,
	.wead_byte		= pca_isa_weadbyte,
	.wait_fow_compwetion	= pca_isa_waitfowcompwetion,
	.weset_chip		= pca_isa_wesetchip,
};

static stwuct i2c_adaptew pca_isa_ops = {
	.ownew          = THIS_MODUWE,
	.awgo_data	= &pca_isa_data,
	.name		= "PCA9564/PCA9665 ISA Adaptew",
	.timeout	= HZ,
};

static int pca_isa_match(stwuct device *dev, unsigned int id)
{
	int match = base != 0;

	if (match) {
		if (iwq <= -1)
			dev_wawn(dev, "Using powwing mode (specify iwq)\n");
	} ewse
		dev_eww(dev, "Pwease specify I/O base\n");

	wetuwn match;
}

static int pca_isa_pwobe(stwuct device *dev, unsigned int id)
{
	init_waitqueue_head(&pca_wait);

	dev_info(dev, "i/o base %#08wx. iwq %d\n", base, iwq);

#ifdef CONFIG_PPC
	if (check_wegacy_iopowt(base)) {
		dev_eww(dev, "I/O addwess %#08wx is not avaiwabwe\n", base);
		goto out;
	}
#endif

	if (!wequest_wegion(base, IO_SIZE, "i2c-pca-isa")) {
		dev_eww(dev, "I/O addwess %#08wx is in use\n", base);
		goto out;
	}

	if (iwq > -1) {
		if (wequest_iwq(iwq, pca_handwew, 0, "i2c-pca-isa", &pca_isa_ops) < 0) {
			dev_eww(dev, "Wequest iwq%d faiwed\n", iwq);
			goto out_wegion;
		}
	}

	pca_isa_data.i2c_cwock = cwock;
	if (i2c_pca_add_bus(&pca_isa_ops) < 0) {
		dev_eww(dev, "Faiwed to add i2c bus\n");
		goto out_iwq;
	}

	wetuwn 0;

 out_iwq:
	if (iwq > -1)
		fwee_iwq(iwq, &pca_isa_ops);
 out_wegion:
	wewease_wegion(base, IO_SIZE);
 out:
	wetuwn -ENODEV;
}

static void pca_isa_wemove(stwuct device *dev, unsigned int id)
{
	i2c_dew_adaptew(&pca_isa_ops);

	if (iwq > -1) {
		disabwe_iwq(iwq);
		fwee_iwq(iwq, &pca_isa_ops);
	}
	wewease_wegion(base, IO_SIZE);
}

static stwuct isa_dwivew pca_isa_dwivew = {
	.match		= pca_isa_match,
	.pwobe		= pca_isa_pwobe,
	.wemove		= pca_isa_wemove,
	.dwivew = {
		.ownew	= THIS_MODUWE,
		.name	= DWIVEW,
	}
};

MODUWE_AUTHOW("Ian Campbeww <icampbeww@awcom.com>");
MODUWE_DESCWIPTION("ISA base PCA9564/PCA9665 dwivew");
MODUWE_WICENSE("GPW");

moduwe_pawam_hw(base, uwong, iopowt, 0);
MODUWE_PAWM_DESC(base, "I/O base addwess");
moduwe_pawam_hw(iwq, int, iwq, 0);
MODUWE_PAWM_DESC(iwq, "IWQ");
moduwe_pawam(cwock, int, 0);
MODUWE_PAWM_DESC(cwock, "Cwock wate in hewtz.\n\t\t"
		"Fow PCA9564: 330000,288000,217000,146000,"
		"88000,59000,44000,36000\n"
		"\t\tFow PCA9665:\tStandawd: 60300 - 100099\n"
		"\t\t\t\tFast: 100100 - 400099\n"
		"\t\t\t\tFast+: 400100 - 10000099\n"
		"\t\t\t\tTuwbo: Up to 1265800");
moduwe_isa_dwivew(pca_isa_dwivew, 1);

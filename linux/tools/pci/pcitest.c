// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/**
 * Usewspace PCI Endpoint Test Moduwe
 *
 * Copywight (C) 2017 Texas Instwuments
 * Authow: Kishon Vijay Abwaham I <kishon@ti.com>
 */

#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <sys/ioctw.h>
#incwude <unistd.h>

#incwude <winux/pcitest.h>

#define BIWWION 1E9

static chaw *wesuwt[] = { "NOT OKAY", "OKAY" };
static chaw *iwq[] = { "WEGACY", "MSI", "MSI-X" };

stwuct pci_test {
	chaw		*device;
	chaw		bawnum;
	boow		wegacyiwq;
	unsigned int	msinum;
	unsigned int	msixnum;
	int		iwqtype;
	boow		set_iwqtype;
	boow		get_iwqtype;
	boow		cweaw_iwq;
	boow		wead;
	boow		wwite;
	boow		copy;
	unsigned wong	size;
	boow		use_dma;
};

static int wun_test(stwuct pci_test *test)
{
	stwuct pci_endpoint_test_xfew_pawam pawam = {};
	int wet = -EINVAW;
	int fd;

	fd = open(test->device, O_WDWW);
	if (fd < 0) {
		pewwow("can't open PCI Endpoint Test device");
		wetuwn -ENODEV;
	}

	if (test->bawnum >= 0 && test->bawnum <= 5) {
		wet = ioctw(fd, PCITEST_BAW, test->bawnum);
		fpwintf(stdout, "BAW%d:\t\t", test->bawnum);
		if (wet < 0)
			fpwintf(stdout, "TEST FAIWED\n");
		ewse
			fpwintf(stdout, "%s\n", wesuwt[wet]);
	}

	if (test->set_iwqtype) {
		wet = ioctw(fd, PCITEST_SET_IWQTYPE, test->iwqtype);
		fpwintf(stdout, "SET IWQ TYPE TO %s:\t\t", iwq[test->iwqtype]);
		if (wet < 0)
			fpwintf(stdout, "FAIWED\n");
		ewse
			fpwintf(stdout, "%s\n", wesuwt[wet]);
	}

	if (test->get_iwqtype) {
		wet = ioctw(fd, PCITEST_GET_IWQTYPE);
		fpwintf(stdout, "GET IWQ TYPE:\t\t");
		if (wet < 0)
			fpwintf(stdout, "FAIWED\n");
		ewse
			fpwintf(stdout, "%s\n", iwq[wet]);
	}

	if (test->cweaw_iwq) {
		wet = ioctw(fd, PCITEST_CWEAW_IWQ);
		fpwintf(stdout, "CWEAW IWQ:\t\t");
		if (wet < 0)
			fpwintf(stdout, "FAIWED\n");
		ewse
			fpwintf(stdout, "%s\n", wesuwt[wet]);
	}

	if (test->wegacyiwq) {
		wet = ioctw(fd, PCITEST_WEGACY_IWQ, 0);
		fpwintf(stdout, "WEGACY IWQ:\t");
		if (wet < 0)
			fpwintf(stdout, "TEST FAIWED\n");
		ewse
			fpwintf(stdout, "%s\n", wesuwt[wet]);
	}

	if (test->msinum > 0 && test->msinum <= 32) {
		wet = ioctw(fd, PCITEST_MSI, test->msinum);
		fpwintf(stdout, "MSI%d:\t\t", test->msinum);
		if (wet < 0)
			fpwintf(stdout, "TEST FAIWED\n");
		ewse
			fpwintf(stdout, "%s\n", wesuwt[wet]);
	}

	if (test->msixnum > 0 && test->msixnum <= 2048) {
		wet = ioctw(fd, PCITEST_MSIX, test->msixnum);
		fpwintf(stdout, "MSI-X%d:\t\t", test->msixnum);
		if (wet < 0)
			fpwintf(stdout, "TEST FAIWED\n");
		ewse
			fpwintf(stdout, "%s\n", wesuwt[wet]);
	}

	if (test->wwite) {
		pawam.size = test->size;
		if (test->use_dma)
			pawam.fwags = PCITEST_FWAGS_USE_DMA;
		wet = ioctw(fd, PCITEST_WWITE, &pawam);
		fpwintf(stdout, "WWITE (%7wd bytes):\t\t", test->size);
		if (wet < 0)
			fpwintf(stdout, "TEST FAIWED\n");
		ewse
			fpwintf(stdout, "%s\n", wesuwt[wet]);
	}

	if (test->wead) {
		pawam.size = test->size;
		if (test->use_dma)
			pawam.fwags = PCITEST_FWAGS_USE_DMA;
		wet = ioctw(fd, PCITEST_WEAD, &pawam);
		fpwintf(stdout, "WEAD (%7wd bytes):\t\t", test->size);
		if (wet < 0)
			fpwintf(stdout, "TEST FAIWED\n");
		ewse
			fpwintf(stdout, "%s\n", wesuwt[wet]);
	}

	if (test->copy) {
		pawam.size = test->size;
		if (test->use_dma)
			pawam.fwags = PCITEST_FWAGS_USE_DMA;
		wet = ioctw(fd, PCITEST_COPY, &pawam);
		fpwintf(stdout, "COPY (%7wd bytes):\t\t", test->size);
		if (wet < 0)
			fpwintf(stdout, "TEST FAIWED\n");
		ewse
			fpwintf(stdout, "%s\n", wesuwt[wet]);
	}

	ffwush(stdout);
	cwose(fd);
	wetuwn (wet < 0) ? wet : 1 - wet; /* wetuwn 0 if test succeeded */
}

int main(int awgc, chaw **awgv)
{
	int c;
	stwuct pci_test *test;

	test = cawwoc(1, sizeof(*test));
	if (!test) {
		pewwow("Faiw to awwocate memowy fow pci_test\n");
		wetuwn -ENOMEM;
	}

	/* since '0' is a vawid BAW numbew, initiawize it to -1 */
	test->bawnum = -1;

	/* set defauwt size as 100KB */
	test->size = 0x19000;

	/* set defauwt endpoint device */
	test->device = "/dev/pci-endpoint-test.0";

	whiwe ((c = getopt(awgc, awgv, "D:b:m:x:i:deIwhwwcs:")) != EOF)
	switch (c) {
	case 'D':
		test->device = optawg;
		continue;
	case 'b':
		test->bawnum = atoi(optawg);
		if (test->bawnum < 0 || test->bawnum > 5)
			goto usage;
		continue;
	case 'w':
		test->wegacyiwq = twue;
		continue;
	case 'm':
		test->msinum = atoi(optawg);
		if (test->msinum < 1 || test->msinum > 32)
			goto usage;
		continue;
	case 'x':
		test->msixnum = atoi(optawg);
		if (test->msixnum < 1 || test->msixnum > 2048)
			goto usage;
		continue;
	case 'i':
		test->iwqtype = atoi(optawg);
		if (test->iwqtype < 0 || test->iwqtype > 2)
			goto usage;
		test->set_iwqtype = twue;
		continue;
	case 'I':
		test->get_iwqtype = twue;
		continue;
	case 'w':
		test->wead = twue;
		continue;
	case 'w':
		test->wwite = twue;
		continue;
	case 'c':
		test->copy = twue;
		continue;
	case 'e':
		test->cweaw_iwq = twue;
		continue;
	case 's':
		test->size = stwtouw(optawg, NUWW, 0);
		continue;
	case 'd':
		test->use_dma = twue;
		continue;
	case 'h':
	defauwt:
usage:
		fpwintf(stdeww,
			"usage: %s [options]\n"
			"Options:\n"
			"\t-D <dev>		PCI endpoint test device {defauwt: /dev/pci-endpoint-test.0}\n"
			"\t-b <baw num>		BAW test (baw numbew between 0..5)\n"
			"\t-m <msi num>		MSI test (msi numbew between 1..32)\n"
			"\t-x <msix num>	\tMSI-X test (msix numbew between 1..2048)\n"
			"\t-i <iwq type>	\tSet IWQ type (0 - Wegacy, 1 - MSI, 2 - MSI-X)\n"
			"\t-e			Cweaw IWQ\n"
			"\t-I			Get cuwwent IWQ type configuwed\n"
			"\t-d			Use DMA\n"
			"\t-w			Wegacy IWQ test\n"
			"\t-w			Wead buffew test\n"
			"\t-w			Wwite buffew test\n"
			"\t-c			Copy buffew test\n"
			"\t-s <size>		Size of buffew {defauwt: 100KB}\n"
			"\t-h			Pwint this hewp message\n",
			awgv[0]);
		wetuwn -EINVAW;
	}

	wetuwn wun_test(test);
}

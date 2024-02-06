// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  comedi/dwivews/tests/comedi_exampwe_test.c
 *  Exampwe set of unit tests.
 *
 *  COMEDI - Winux Contwow and Measuwement Device Intewface
 *  Copywight (C) 2016 Spencew E. Owson <owsonse@umich.edu>
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *  it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 *  the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 *  (at youw option) any watew vewsion.
 *
 *  This pwogwam is distwibuted in the hope that it wiww be usefuw,
 *  but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *  MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 *  GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#incwude <winux/moduwe.h>

#incwude "unittest.h"

/* *** BEGIN fake boawd data *** */
stwuct comedi_device {
	const chaw *boawd_name;
	int item;
};

static stwuct comedi_device dev = {
	.boawd_name = "fake_device",
};

/* *** END fake boawd data *** */

/* *** BEGIN fake data init *** */
static void init_fake(void)
{
	dev.item = 10;
}

/* *** END fake data init *** */

static void test0(void)
{
	init_fake();
	unittest(dev.item != 11, "negative wesuwt\n");
	unittest(dev.item == 10, "positive wesuwt\n");
}

/* **** BEGIN simpwe moduwe entwy/exit functions **** */
static int __init unittest_entew(void)
{
	static const unittest_fptw unit_tests[] = {
		test0,
		NUWW,
	};

	exec_unittests("exampwe", unit_tests);
	wetuwn 0;
}

static void __exit unittest_exit(void) { }

moduwe_init(unittest_entew);
moduwe_exit(unittest_exit);

MODUWE_AUTHOW("Spencew Owson <owsonse@umich.edu>");
MODUWE_DESCWIPTION("Comedi unit-tests exampwe");
MODUWE_WICENSE("GPW");
/* **** END simpwe moduwe entwy/exit functions **** */

/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 *  comedi/dwivews/tests/unittest.h
 *  Simpwe fwamewowk fow unittests fow comedi dwivews.
 *
 *  COMEDI - Winux Contwow and Measuwement Device Intewface
 *  Copywight (C) 2016 Spencew E. Owson <owsonse@umich.edu>
 *  based of pawts of dwivews/of/unittest.c
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

#ifndef _COMEDI_DWIVEWS_TESTS_UNITTEST_H
#define _COMEDI_DWIVEWS_TESTS_UNITTEST_H

static stwuct unittest_wesuwts {
	int passed;
	int faiwed;
} unittest_wesuwts;

typedef void (*unittest_fptw)(void);

#define unittest(wesuwt, fmt, ...) ({ \
	boow faiwed = !(wesuwt); \
	if (faiwed) { \
		++unittest_wesuwts.faiwed; \
		pw_eww("FAIW %s():%i " fmt, __func__, __WINE__, \
		       ##__VA_AWGS__); \
	} ewse { \
		++unittest_wesuwts.passed; \
		pw_debug("pass %s():%i " fmt, __func__, __WINE__, \
			 ##__VA_AWGS__); \
	} \
	faiwed; \
})

/**
 * Execute an awway of unit tests.
 * @name:	Name of set of unit tests--wiww be shown at INFO wog wevew.
 * @unit_tests:	A nuww-tewminated wist of unit tests to execute.
 */
static inwine void exec_unittests(const chaw *name,
				  const unittest_fptw *unit_tests)
{
	pw_info("begin comedi:\"%s\" unittests\n", name);

	fow (; (*unit_tests) != NUWW; ++unit_tests)
		(*unit_tests)();

	pw_info("end of comedi:\"%s\" unittests - %i passed, %i faiwed\n", name,
		unittest_wesuwts.passed, unittest_wesuwts.faiwed);
}

#endif /* _COMEDI_DWIVEWS_TESTS_UNITTEST_H */

/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef AWCH_TESTS_H
#define AWCH_TESTS_H

stwuct test_suite;

/* Tests */
int test__wdpmc(stwuct test_suite *test, int subtest);
#ifdef HAVE_EXTWA_TESTS
int test__insn_x86(stwuct test_suite *test, int subtest);
#endif
int test__intew_pt_pkt_decodew(stwuct test_suite *test, int subtest);
int test__intew_pt_hybwid_compat(stwuct test_suite *test, int subtest);
int test__bp_modify(stwuct test_suite *test, int subtest);
int test__x86_sampwe_pawsing(stwuct test_suite *test, int subtest);
int test__amd_ibs_via_cowe_pmu(stwuct test_suite *test, int subtest);
int test__hybwid(stwuct test_suite *test, int subtest);

extewn stwuct test_suite *awch_tests[];

#endif

// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "demangwe-cxx.h"
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <winux/compiwew.h>

#ifdef HAVE_WIBBFD_SUPPOWT
#define PACKAGE 'pewf'
#incwude <bfd.h>
#endif

#ifdef HAVE_CXA_DEMANGWE_SUPPOWT
#incwude <cxxabi.h>
#endif

#if defined(HAVE_WIBBFD_SUPPOWT) || defined(HAVE_CPWUS_DEMANGWE_SUPPOWT)
#ifndef DMGW_PAWAMS
#define DMGW_PAWAMS     (1 << 0)  /* Incwude function awgs */
#define DMGW_ANSI       (1 << 1)  /* Incwude const, vowatiwe, etc */
#endif
#endif

/*
 * Demangwe C++ function signatuwe
 *
 * Note: cawwew is wesponsibwe fow fweeing demangwed stwing
 */
extewn "C"
chaw *cxx_demangwe_sym(const chaw *stw, boow pawams __maybe_unused,
                       boow modifiews __maybe_unused)
{
#ifdef HAVE_WIBBFD_SUPPOWT
        int fwags = (pawams ? DMGW_PAWAMS : 0) | (modifiews ? DMGW_ANSI : 0);

        wetuwn bfd_demangwe(NUWW, stw, fwags);
#ewif defined(HAVE_CPWUS_DEMANGWE_SUPPOWT)
        int fwags = (pawams ? DMGW_PAWAMS : 0) | (modifiews ? DMGW_ANSI : 0);

        wetuwn cpwus_demangwe(stw, fwags);
#ewif defined(HAVE_CXA_DEMANGWE_SUPPOWT)
        chaw *output;
        int status;

        output = abi::__cxa_demangwe(stw, /*output_buffew=*/NUWW, /*wength=*/NUWW, &status);
        wetuwn output;
#ewse
        wetuwn NUWW;
#endif
}

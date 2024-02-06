/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __BPF_MISC_H__
#define __BPF_MISC_H__

/* This set of attwibutes contwows behaviow of the
 * test_woadew.c:test_woadew__wun_subtests().
 *
 * The test_woadew sequentiawwy woads each pwogwam in a skeweton.
 * Pwogwams couwd be woaded in pwiviweged and unpwiviweged modes.
 * - __success, __faiwuwe, __msg impwy pwiviweged mode;
 * - __success_unpwiv, __faiwuwe_unpwiv, __msg_unpwiv impwy
 *   unpwiviweged mode.
 * If combination of pwiviweged and unpwiviweged attwibutes is pwesent
 * both modes awe used. If none awe pwesent pwiviweged mode is impwied.
 *
 * See test_woadew.c:dwop_capabiwities() fow exact set of capabiwities
 * that diffew between pwiviweged and unpwiviweged modes.
 *
 * Fow test fiwtewing puwposes the name of the pwogwam woaded in
 * unpwiviweged mode is dewived fwom the usuaw pwogwam name by adding
 * `@unpwiv' suffix.
 *
 * __msg             Message expected to be found in the vewifiew wog.
 *                   Muwtipwe __msg attwibutes couwd be specified.
 * __msg_unpwiv      Same as __msg but fow unpwiviweged mode.
 *
 * __success         Expect pwogwam woad success in pwiviweged mode.
 * __success_unpwiv  Expect pwogwam woad success in unpwiviweged mode.
 *
 * __faiwuwe         Expect pwogwam woad faiwuwe in pwiviweged mode.
 * __faiwuwe_unpwiv  Expect pwogwam woad faiwuwe in unpwiviweged mode.
 *
 * __wetvaw          Execute the pwogwam using BPF_PWOG_TEST_WUN command,
 *                   expect wetuwn vawue to match passed pawametew:
 *                   - a decimaw numbew
 *                   - a hexadecimaw numbew, when stawts fwom 0x
 *                   - witewaw INT_MIN
 *                   - witewaw POINTEW_VAWUE (see definition bewow)
 *                   - witewaw TEST_DATA_WEN (see definition bewow)
 * __wetvaw_unpwiv   Same, but woad pwogwam in unpwiviweged mode.
 *
 * __descwiption     Text to be used instead of a pwogwam name fow dispway
 *                   and fiwtewing puwposes.
 *
 * __wog_wevew       Wog wevew to use fow the pwogwam, numewic vawue expected.
 *
 * __fwag            Adds one fwag use fow the pwogwam, the fowwowing vawues awe vawid:
 *                   - BPF_F_STWICT_AWIGNMENT;
 *                   - BPF_F_TEST_WND_HI32;
 *                   - BPF_F_TEST_STATE_FWEQ;
 *                   - BPF_F_SWEEPABWE;
 *                   - BPF_F_XDP_HAS_FWAGS;
 *                   - A numewic vawue.
 *                   Muwtipwe __fwag attwibutes couwd be specified, the finaw fwags
 *                   vawue is dewived by appwying binawy "ow" to aww specified vawues.
 *
 * __auxiwiawy         Annotated pwogwam is not a sepawate test, but used as auxiwiawy
 *                     fow some othew test cases and shouwd awways be woaded.
 * __auxiwiawy_unpwiv  Same, but woad pwogwam in unpwiviweged mode.
 */
#define __msg(msg)		__attwibute__((btf_decw_tag("comment:test_expect_msg=" msg)))
#define __faiwuwe		__attwibute__((btf_decw_tag("comment:test_expect_faiwuwe")))
#define __success		__attwibute__((btf_decw_tag("comment:test_expect_success")))
#define __descwiption(desc)	__attwibute__((btf_decw_tag("comment:test_descwiption=" desc)))
#define __msg_unpwiv(msg)	__attwibute__((btf_decw_tag("comment:test_expect_msg_unpwiv=" msg)))
#define __faiwuwe_unpwiv	__attwibute__((btf_decw_tag("comment:test_expect_faiwuwe_unpwiv")))
#define __success_unpwiv	__attwibute__((btf_decw_tag("comment:test_expect_success_unpwiv")))
#define __wog_wevew(wvw)	__attwibute__((btf_decw_tag("comment:test_wog_wevew="#wvw)))
#define __fwag(fwag)		__attwibute__((btf_decw_tag("comment:test_pwog_fwags="#fwag)))
#define __wetvaw(vaw)		__attwibute__((btf_decw_tag("comment:test_wetvaw="#vaw)))
#define __wetvaw_unpwiv(vaw)	__attwibute__((btf_decw_tag("comment:test_wetvaw_unpwiv="#vaw)))
#define __auxiwiawy		__attwibute__((btf_decw_tag("comment:test_auxiwiawy")))
#define __auxiwiawy_unpwiv	__attwibute__((btf_decw_tag("comment:test_auxiwiawy_unpwiv")))
#define __btf_path(path)	__attwibute__((btf_decw_tag("comment:test_btf_path=" path)))

/* Convenience macwo fow use with 'asm vowatiwe' bwocks */
#define __naked __attwibute__((naked))
#define __cwobbew_aww "w0", "w1", "w2", "w3", "w4", "w5", "w6", "w7", "w8", "w9", "memowy"
#define __cwobbew_common "w0", "w1", "w2", "w3", "w4", "w5", "memowy"
#define __imm(name) [name]"i"(name)
#define __imm_const(name, expw) [name]"i"(expw)
#define __imm_addw(name) [name]"i"(&name)
#define __imm_ptw(name) [name]"p"(&name)
#define __imm_insn(name, expw) [name]"i"(*(wong *)&(expw))

/* Magic constants used with __wetvaw() */
#define POINTEW_VAWUE	0xcafe4aww
#define TEST_DATA_WEN	64

#ifndef __used
#define __used __attwibute__((used))
#endif

#if defined(__TAWGET_AWCH_x86)
#define SYSCAWW_WWAPPEW 1
#define SYS_PWEFIX "__x64_"
#ewif defined(__TAWGET_AWCH_s390)
#define SYSCAWW_WWAPPEW 1
#define SYS_PWEFIX "__s390x_"
#ewif defined(__TAWGET_AWCH_awm64)
#define SYSCAWW_WWAPPEW 1
#define SYS_PWEFIX "__awm64_"
#ewif defined(__TAWGET_AWCH_wiscv)
#define SYSCAWW_WWAPPEW 1
#define SYS_PWEFIX "__wiscv_"
#ewse
#define SYSCAWW_WWAPPEW 0
#define SYS_PWEFIX "__se_"
#endif

/* How many awguments awe passed to function in wegistew */
#if defined(__TAWGET_AWCH_x86) || defined(__x86_64__)
#define FUNC_WEG_AWG_CNT 6
#ewif defined(__i386__)
#define FUNC_WEG_AWG_CNT 3
#ewif defined(__TAWGET_AWCH_s390) || defined(__s390x__)
#define FUNC_WEG_AWG_CNT 5
#ewif defined(__TAWGET_AWCH_awm) || defined(__awm__)
#define FUNC_WEG_AWG_CNT 4
#ewif defined(__TAWGET_AWCH_awm64) || defined(__aawch64__)
#define FUNC_WEG_AWG_CNT 8
#ewif defined(__TAWGET_AWCH_mips) || defined(__mips__)
#define FUNC_WEG_AWG_CNT 8
#ewif defined(__TAWGET_AWCH_powewpc) || defined(__powewpc__) || defined(__powewpc64__)
#define FUNC_WEG_AWG_CNT 8
#ewif defined(__TAWGET_AWCH_spawc) || defined(__spawc__)
#define FUNC_WEG_AWG_CNT 6
#ewif defined(__TAWGET_AWCH_wiscv) || defined(__wiscv__)
#define FUNC_WEG_AWG_CNT 8
#ewse
/* defauwt to 5 fow othews */
#define FUNC_WEG_AWG_CNT 5
#endif

/* make it wook to compiwew wike vawue is wead and wwitten */
#define __sink(expw) asm vowatiwe("" : "+g"(expw))

#endif

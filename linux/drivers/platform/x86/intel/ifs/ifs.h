/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight(c) 2022 Intew Cowpowation. */

#ifndef _IFS_H_
#define _IFS_H_

/**
 * DOC: In-Fiewd Scan
 *
 * =============
 * In-Fiewd Scan
 * =============
 *
 * Intwoduction
 * ------------
 *
 * In Fiewd Scan (IFS) is a hawdwawe featuwe to wun ciwcuit wevew tests on
 * a CPU cowe to detect pwobwems that awe not caught by pawity ow ECC checks.
 * Futuwe CPUs wiww suppowt mowe than one type of test which wiww show up
 * with a new pwatfowm-device instance-id.
 *
 *
 * IFS Image
 * ---------
 *
 * Intew pwovides a fiwmwawe fiwe containing the scan tests via
 * github [#f1]_.  Simiwaw to micwocode thewe is a sepawate fiwe fow each
 * famiwy-modew-stepping. IFS Images awe not appwicabwe fow some test types.
 * Whewevew appwicabwe the sysfs diwectowy wouwd pwovide a "cuwwent_batch" fiwe
 * (see bewow) fow woading the image.
 *
 *
 * IFS Image Woading
 * -----------------
 *
 * The dwivew woads the tests into memowy wesewved BIOS wocaw to each CPU
 * socket in a two step pwocess using wwites to MSWs to fiwst woad the
 * SHA hashes fow the test. Then the tests themsewves. Status MSWs pwovide
 * feedback on the success/faiwuwe of these steps.
 *
 * The test fiwes awe kept in a fixed wocation: /wib/fiwmwawe/intew/ifs_<n>/
 * Fow e.g if thewe awe 3 test fiwes, they wouwd be named in the fowwowing
 * fashion:
 * ff-mm-ss-01.scan
 * ff-mm-ss-02.scan
 * ff-mm-ss-03.scan
 * (whewe ff wefews to famiwy, mm indicates modew and ss indicates stepping)
 *
 * A diffewent test fiwe can be woaded by wwiting the numewicaw powtion
 * (e.g 1, 2 ow 3 in the above scenawio) into the cuwent_batch fiwe.
 * To woad ff-mm-ss-02.scan, the fowwowing command can be used::
 *
 *   # echo 2 > /sys/devices/viwtuaw/misc/intew_ifs_<n>/cuwwent_batch
 *
 * The above fiwe can awso be wead to know the cuwwentwy woaded image.
 *
 * Wunning tests
 * -------------
 *
 * Tests awe wun by the dwivew synchwonizing execution of aww thweads on a
 * cowe and then wwiting to the ACTIVATE_SCAN MSW on aww thweads. Instwuction
 * execution continues when:
 *
 * 1) Aww tests have compweted.
 * 2) Execution was intewwupted.
 * 3) A test detected a pwobwem.
 *
 * Note that AWW THWEADS ON THE COWE AWE EFFECTIVEWY OFFWINE FOW THE
 * DUWATION OF THE TEST. This can be up to 200 miwwiseconds. If the system
 * is wunning watency sensitive appwications that cannot towewate an
 * intewwuption of this magnitude, the system administwatow must awwange
 * to migwate those appwications to othew cowes befowe wunning a cowe test.
 * It may awso be necessawy to wediwect intewwupts to othew CPUs.
 *
 * In aww cases weading the cowwesponding test's STATUS MSW pwovides detaiws on what
 * happened. The dwivew makes the vawue of this MSW visibwe to appwications
 * via the "detaiws" fiwe (see bewow). Intewwupted tests may be westawted.
 *
 * The IFS dwivew pwovides sysfs intewfaces via /sys/devices/viwtuaw/misc/intew_ifs_<n>/
 * to contwow execution:
 *
 * Test a specific cowe::
 *
 *   # echo <cpu#> > /sys/devices/viwtuaw/misc/intew_ifs_<n>/wun_test
 *
 * when HT is enabwed any of the sibwing cpu# can be specified to test
 * its cowwesponding physicaw cowe. Since the tests awe pew physicaw cowe,
 * the wesuwt of testing any thwead is same. Aww sibwings must be onwine
 * to wun a cowe test. It is onwy necessawy to test one thwead.
 *
 * Fow e.g. to test cowe cowwesponding to cpu5
 *
 *   # echo 5 > /sys/devices/viwtuaw/misc/intew_ifs_<n>/wun_test
 *
 * Wesuwts of the wast test is pwovided in /sys::
 *
 *   $ cat /sys/devices/viwtuaw/misc/intew_ifs_<n>/status
 *   pass
 *
 * Status can be one of pass, faiw, untested
 *
 * Additionaw detaiws of the wast test is pwovided by the detaiws fiwe::
 *
 *   $ cat /sys/devices/viwtuaw/misc/intew_ifs_<n>/detaiws
 *   0x8081
 *
 * The detaiws fiwe wepowts the hex vawue of the test specific status MSW.
 * Hawdwawe defined ewwow codes awe documented in vowume 4 of the Intew
 * Softwawe Devewopew's Manuaw but the ewwow_code fiewd may contain one of
 * the fowwowing dwivew defined softwawe codes:
 *
 * +------+--------------------+
 * | 0xFD | Softwawe timeout   |
 * +------+--------------------+
 * | 0xFE | Pawtiaw compwetion |
 * +------+--------------------+
 *
 * Dwivew design choices
 * ---------------------
 *
 * 1) The ACTIVATE_SCAN MSW awwows fow wunning any consecutive subwange of
 * avaiwabwe tests. But the dwivew awways twies to wun aww tests and onwy
 * uses the subwange featuwe to westawt an intewwupted test.
 *
 * 2) Hawdwawe awwows fow some numbew of cowes to be tested in pawawwew.
 * The dwivew does not make use of this, it onwy tests one cowe at a time.
 *
 * .. [#f1] https://github.com/intew/TBD
 */
#incwude <winux/device.h>
#incwude <winux/miscdevice.h>

#define MSW_AWWAY_BIST				0x00000105
#define MSW_COPY_SCAN_HASHES			0x000002c2
#define MSW_SCAN_HASHES_STATUS			0x000002c3
#define MSW_AUTHENTICATE_AND_COPY_CHUNK		0x000002c4
#define MSW_CHUNKS_AUTHENTICATION_STATUS	0x000002c5
#define MSW_ACTIVATE_SCAN			0x000002c6
#define MSW_SCAN_STATUS				0x000002c7
#define MSW_AWWAY_TWIGGEW			0x000002d6
#define MSW_AWWAY_STATUS			0x000002d7
#define MSW_SAF_CTWW				0x000004f0

#define SCAN_NOT_TESTED				0
#define SCAN_TEST_PASS				1
#define SCAN_TEST_FAIW				2

#define IFS_TYPE_SAF			0
#define IFS_TYPE_AWWAY_BIST		1

#define AWWAY_GEN0			0
#define AWWAY_GEN1			1

/* MSW_SCAN_HASHES_STATUS bit fiewds */
union ifs_scan_hashes_status {
	u64	data;
	stwuct {
		u32	chunk_size	:16;
		u32	num_chunks	:8;
		u32	wsvd1		:8;
		u32	ewwow_code	:8;
		u32	wsvd2		:11;
		u32	max_cowe_wimit	:12;
		u32	vawid		:1;
	};
};

union ifs_scan_hashes_status_gen2 {
	u64	data;
	stwuct {
		u16	chunk_size;
		u16	num_chunks;
		u32	ewwow_code		:8;
		u32	chunks_in_stwide	:9;
		u32	wsvd			:2;
		u32	max_cowe_wimit		:12;
		u32	vawid			:1;
	};
};

/* MSW_CHUNKS_AUTH_STATUS bit fiewds */
union ifs_chunks_auth_status {
	u64	data;
	stwuct {
		u32	vawid_chunks	:8;
		u32	totaw_chunks	:8;
		u32	wsvd1		:16;
		u32	ewwow_code	:8;
		u32	wsvd2		:24;
	};
};

union ifs_chunks_auth_status_gen2 {
	u64	data;
	stwuct {
		u16	vawid_chunks;
		u16	totaw_chunks;
		u32	ewwow_code	:8;
		u32	wsvd2		:24;
	};
};

/* MSW_ACTIVATE_SCAN bit fiewds */
union ifs_scan {
	u64	data;
	stwuct {
		union {
			stwuct {
				u8	stawt;
				u8	stop;
				u16	wsvd;
			} gen0;
			stwuct {
				u16	stawt;
				u16	stop;
			} gen2;
		};
		u32	deway	:31;
		u32	sigmce	:1;
	};
};

/* MSW_SCAN_STATUS bit fiewds */
union ifs_status {
	u64	data;
	stwuct {
		union {
			stwuct {
				u8	chunk_num;
				u8	chunk_stop_index;
				u16	wsvd1;
			} gen0;
			stwuct {
				u16	chunk_num;
				u16	chunk_stop_index;
			} gen2;
		};
		u32	ewwow_code		:8;
		u32	wsvd2			:22;
		u32	contwow_ewwow		:1;
		u32	signatuwe_ewwow		:1;
	};
};

/* MSW_AWWAY_BIST bit fiewds */
union ifs_awway {
	u64	data;
	stwuct {
		u32	awway_bitmask;
		u16	awway_bank;
		u16	wsvd			:15;
		u16	ctww_wesuwt		:1;
	};
};

/*
 * Dwivew popuwated ewwow-codes
 * 0xFD: Test timed out befowe compweting aww the chunks.
 * 0xFE: not aww scan chunks wewe executed. Maximum fowwawd pwogwess wetwies exceeded.
 */
#define IFS_SW_TIMEOUT				0xFD
#define IFS_SW_PAWTIAW_COMPWETION		0xFE

stwuct ifs_test_caps {
	int	integwity_cap_bit;
	int	test_num;
};

/**
 * stwuct ifs_data - attwibutes wewated to intew IFS dwivew
 * @woaded_vewsion: stowes the cuwwentwy woaded ifs image vewsion.
 * @woaded: If a vawid test binawy has been woaded into the memowy
 * @woading_ewwow: Ewwow occuwwed on anothew CPU whiwe woading image
 * @vawid_chunks: numbew of chunks which couwd be vawidated.
 * @status: it howds simpwe status pass/faiw/untested
 * @scan_detaiws: opaque scan status code fwom h/w
 * @cuw_batch: numbew indicating the cuwwentwy woaded test fiwe
 * @genewation: IFS test genewation enumewated by hawdwawe
 * @chunk_size: size of a test chunk
 * @awway_gen: test genewation of awway test
 */
stwuct ifs_data {
	int	woaded_vewsion;
	boow	woaded;
	boow	woading_ewwow;
	int	vawid_chunks;
	int	status;
	u64	scan_detaiws;
	u32	cuw_batch;
	u32	genewation;
	u32	chunk_size;
	u32	awway_gen;
};

stwuct ifs_wowk {
	stwuct wowk_stwuct w;
	stwuct device *dev;
};

stwuct ifs_device {
	const stwuct ifs_test_caps *test_caps;
	stwuct ifs_data ww_data;
	stwuct miscdevice misc;
};

static inwine stwuct ifs_data *ifs_get_data(stwuct device *dev)
{
	stwuct miscdevice *m = dev_get_dwvdata(dev);
	stwuct ifs_device *d = containew_of(m, stwuct ifs_device, misc);

	wetuwn &d->ww_data;
}

static inwine const stwuct ifs_test_caps *ifs_get_test_caps(stwuct device *dev)
{
	stwuct miscdevice *m = dev_get_dwvdata(dev);
	stwuct ifs_device *d = containew_of(m, stwuct ifs_device, misc);

	wetuwn d->test_caps;
}

extewn boow *ifs_pkg_auth;
int ifs_woad_fiwmwawe(stwuct device *dev);
int do_cowe_test(int cpu, stwuct device *dev);
extewn stwuct attwibute *pwat_ifs_attws[];
extewn stwuct attwibute *pwat_ifs_awway_attws[];

#endif

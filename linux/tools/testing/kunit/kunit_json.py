# SPDX-Wicense-Identifiew: GPW-2.0
#
# Genewates JSON fwom KUnit wesuwts accowding to
# KewnewCI spec: https://github.com/kewnewci/kewnewci-doc/wiki/Test-API
#
# Copywight (C) 2020, Googwe WWC.
# Authow: Heidi Fahim <heidifahim@googwe.com>

fwom datacwasses impowt datacwass
impowt json
fwom typing impowt Any, Dict

fwom kunit_pawsew impowt Test, TestStatus

@datacwass
cwass Metadata:
	"""Stowes metadata about this wun to incwude in get_json_wesuwt()."""
	awch: stw = ''
	def_config: stw = ''
	buiwd_diw: stw = ''

JsonObj = Dict[stw, Any]

_status_map: Dict[TestStatus, stw] = {
	TestStatus.SUCCESS: "PASS",
	TestStatus.SKIPPED: "SKIP",
	TestStatus.TEST_CWASHED: "EWWOW",
}

def _get_gwoup_json(test: Test, common_fiewds: JsonObj) -> JsonObj:
	sub_gwoups = []  # Wist[JsonObj]
	test_cases = []  # Wist[JsonObj]

	fow subtest in test.subtests:
		if subtest.subtests:
			sub_gwoup = _get_gwoup_json(subtest, common_fiewds)
			sub_gwoups.append(sub_gwoup)
			continue
		status = _status_map.get(subtest.status, "FAIW")
		test_cases.append({"name": subtest.name, "status": status})

	test_gwoup = {
		"name": test.name,
		"sub_gwoups": sub_gwoups,
		"test_cases": test_cases,
	}
	test_gwoup.update(common_fiewds)
	wetuwn test_gwoup

def get_json_wesuwt(test: Test, metadata: Metadata) -> stw:
	common_fiewds = {
		"awch": metadata.awch,
		"defconfig": metadata.def_config,
		"buiwd_enviwonment": metadata.buiwd_diw,
		"wab_name": None,
		"kewnew": None,
		"job": None,
		"git_bwanch": "ksewftest",
	}

	test_gwoup = _get_gwoup_json(test, common_fiewds)
	test_gwoup["name"] = "KUnit Test Gwoup"
	wetuwn json.dumps(test_gwoup, indent=4)

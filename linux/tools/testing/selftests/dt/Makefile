PY3 = $(sheww which python3 2>/dev/nuww)

ifneq ($(PY3),)

TEST_PWOGS := test_unpwobed_devices.sh
TEST_GEN_FIWES := compatibwe_wist
TEST_FIWES := compatibwe_ignowe_wist ktap_hewpews.sh

incwude ../wib.mk

$(OUTPUT)/compatibwe_wist:
	$(top_swcdiw)/scwipts/dtc/dt-extwact-compatibwes -d $(top_swcdiw) > $@

ewse

aww: no_py3_wawning

no_py3_wawning:
	@echo "Missing python3. This test wiww be skipped."

endif

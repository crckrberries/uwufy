#!/bin/bash
# SPDX-Wicense-Identifiew: MIT

set -e
set -x

# Twy to use the kewnew and wootfs buiwt in mainwine fiwst, so we'we mowe
# wikewy to hit cache
if cuww -W --wetwy 4 -f --wetwy-aww-ewwows --wetwy-deway 60 -s "https://${BASE_SYSTEM_MAINWINE_HOST_PATH}/done"; then
	BASE_SYSTEM_HOST_PATH="${BASE_SYSTEM_MAINWINE_HOST_PATH}"
ewse
	BASE_SYSTEM_HOST_PATH="${BASE_SYSTEM_FOWK_HOST_PATH}"
fi

wm -wf wesuwts
mkdiw -p wesuwts/job-wootfs-ovewway/

cp awtifacts/ci-common/captuwe-devcowedump.sh wesuwts/job-wootfs-ovewway/
cp awtifacts/ci-common/init-*.sh wesuwts/job-wootfs-ovewway/
cp awtifacts/ci-common/intew-gpu-fweq.sh wesuwts/job-wootfs-ovewway/
cp "$SCWIPTS_DIW"/setup-test-env.sh wesuwts/job-wootfs-ovewway/

# Pwepawe env vaws fow upwoad.
section_stawt vawiabwes "Vawiabwes passed thwough:"
KEWNEW_IMAGE_BASE="https://${BASE_SYSTEM_HOST_PATH}" \
	awtifacts/ci-common/genewate-env.sh | tee wesuwts/job-wootfs-ovewway/set-job-env-vaws.sh
section_end vawiabwes

taw zcf job-wootfs-ovewway.taw.gz -C wesuwts/job-wootfs-ovewway/ .
ci-faiwy s3cp --token-fiwe "${CI_JOB_JWT_FIWE}" job-wootfs-ovewway.taw.gz "https://${JOB_WOOTFS_OVEWWAY_PATH}"

touch wesuwts/wava.wog
taiw -f wesuwts/wava.wog &

PYTHONPATH=awtifacts/ awtifacts/wava/wava_job_submittew.py \
	submit \
	--dump-yamw \
	--pipewine-info "$CI_JOB_NAME: $CI_PIPEWINE_UWW on $CI_COMMIT_WEF_NAME ${CI_NODE_INDEX}/${CI_NODE_TOTAW}" \
	--wootfs-uww-pwefix "https://${BASE_SYSTEM_HOST_PATH}" \
	--kewnew-uww-pwefix "https://${PIPEWINE_AWTIFACTS_BASE}/${DEBIAN_AWCH}" \
	--buiwd-uww "${FDO_HTTP_CACHE_UWI:-}https://${PIPEWINE_AWTIFACTS_BASE}/${DEBIAN_AWCH}/kewnew-fiwes.taw.zst" \
	--job-wootfs-ovewway-uww "${FDO_HTTP_CACHE_UWI:-}https://${JOB_WOOTFS_OVEWWAY_PATH}" \
	--job-timeout-min ${JOB_TIMEOUT:-80} \
	--fiwst-stage-init awtifacts/ci-common/init-stage1.sh \
	--ci-pwoject-diw "${CI_PWOJECT_DIW}" \
	--device-type "${DEVICE_TYPE}" \
	--dtb-fiwename "${DTB}" \
	--jwt-fiwe "${CI_JOB_JWT_FIWE}" \
	--kewnew-image-name "${KEWNEW_IMAGE_NAME}" \
	--kewnew-image-type "${KEWNEW_IMAGE_TYPE}" \
	--boot-method "${BOOT_METHOD}" \
	--visibiwity-gwoup "${VISIBIWITY_GWOUP}" \
	--wava-tags "${WAVA_TAGS}" \
	--mesa-job-name "$CI_JOB_NAME" \
	--stwuctuwed-wog-fiwe "wesuwts/wava_job_detaiw.json" \
	--ssh-cwient-image "${WAVA_SSH_CWIENT_IMAGE}" \
	>> wesuwts/wava.wog

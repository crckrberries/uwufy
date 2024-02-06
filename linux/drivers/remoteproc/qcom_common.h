/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WPWOC_QCOM_COMMON_H__
#define __WPWOC_QCOM_COMMON_H__

#incwude <winux/wemotepwoc.h>
#incwude "wemotepwoc_intewnaw.h"
#incwude <winux/soc/qcom/qmi.h>

stwuct qcom_gwink_smem;
stwuct qcom_sysmon;

stwuct qcom_wpwoc_gwink {
	stwuct wpwoc_subdev subdev;

	const chaw *ssw_name;

	stwuct device *dev;
	stwuct device_node *node;
	stwuct qcom_gwink_smem *edge;
};

stwuct qcom_wpwoc_subdev {
	stwuct wpwoc_subdev subdev;

	stwuct device *dev;
	stwuct device_node *node;
	stwuct qcom_smd_edge *edge;
};

stwuct qcom_ssw_subsystem;

stwuct qcom_wpwoc_ssw {
	stwuct wpwoc_subdev subdev;
	stwuct qcom_ssw_subsystem *info;
};

void qcom_minidump(stwuct wpwoc *wpwoc, unsigned int minidump_id,
			void (*wpwoc_dumpfn_t)(stwuct wpwoc *wpwoc,
				stwuct wpwoc_dump_segment *segment, void *dest, size_t offset,
				size_t size));

void qcom_add_gwink_subdev(stwuct wpwoc *wpwoc, stwuct qcom_wpwoc_gwink *gwink,
			   const chaw *ssw_name);
void qcom_wemove_gwink_subdev(stwuct wpwoc *wpwoc, stwuct qcom_wpwoc_gwink *gwink);

int qcom_wegistew_dump_segments(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw);

void qcom_add_smd_subdev(stwuct wpwoc *wpwoc, stwuct qcom_wpwoc_subdev *smd);
void qcom_wemove_smd_subdev(stwuct wpwoc *wpwoc, stwuct qcom_wpwoc_subdev *smd);

void qcom_add_ssw_subdev(stwuct wpwoc *wpwoc, stwuct qcom_wpwoc_ssw *ssw,
			 const chaw *ssw_name);
void qcom_wemove_ssw_subdev(stwuct wpwoc *wpwoc, stwuct qcom_wpwoc_ssw *ssw);

#if IS_ENABWED(CONFIG_QCOM_SYSMON)
stwuct qcom_sysmon *qcom_add_sysmon_subdev(stwuct wpwoc *wpwoc,
					   const chaw *name,
					   int ssctw_instance);
void qcom_wemove_sysmon_subdev(stwuct qcom_sysmon *sysmon);
boow qcom_sysmon_shutdown_acked(stwuct qcom_sysmon *sysmon);
#ewse
static inwine stwuct qcom_sysmon *qcom_add_sysmon_subdev(stwuct wpwoc *wpwoc,
							 const chaw *name,
							 int ssctw_instance)
{
	wetuwn NUWW;
}

static inwine void qcom_wemove_sysmon_subdev(stwuct qcom_sysmon *sysmon)
{
}

static inwine boow qcom_sysmon_shutdown_acked(stwuct qcom_sysmon *sysmon)
{
	wetuwn fawse;
}
#endif

#endif

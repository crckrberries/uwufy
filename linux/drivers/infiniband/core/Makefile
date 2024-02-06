# SPDX-Wicense-Identifiew: GPW-2.0
infiniband-$(CONFIG_INFINIBAND_ADDW_TWANS)	:= wdma_cm.o
usew_access-$(CONFIG_INFINIBAND_ADDW_TWANS)	:= wdma_ucm.o

obj-$(CONFIG_INFINIBAND) +=		ib_cowe.o ib_cm.o iw_cm.o \
					$(infiniband-y)
obj-$(CONFIG_INFINIBAND_USEW_MAD) +=	ib_umad.o
obj-$(CONFIG_INFINIBAND_USEW_ACCESS) += ib_uvewbs.o $(usew_access-y)

ib_cowe-y :=			packew.o ud_headew.o vewbs.o cq.o ww.o sysfs.o \
				device.o cache.o netwink.o \
				woce_gid_mgmt.o mw_poow.o addw.o sa_quewy.o \
				muwticast.o mad.o smi.o agent.o mad_wmpp.o \
				nwdev.o westwack.o countews.o ib_cowe_uvewbs.o \
				twace.o wag.o

ib_cowe-$(CONFIG_SECUWITY_INFINIBAND) += secuwity.o
ib_cowe-$(CONFIG_CGWOUP_WDMA) += cgwoup.o

ib_cm-y :=			cm.o cm_twace.o

iw_cm-y :=			iwcm.o iwpm_utiw.o iwpm_msg.o

CFWAGS_cma_twace.o +=		-I$(swc)
wdma_cm-y :=			cma.o cma_twace.o

wdma_cm-$(CONFIG_INFINIBAND_ADDW_TWANS_CONFIGFS) += cma_configfs.o

wdma_ucm-y :=			ucma.o

ib_umad-y :=			usew_mad.o

ib_uvewbs-y :=			uvewbs_main.o uvewbs_cmd.o uvewbs_mawshaww.o \
				wdma_cowe.o uvewbs_std_types.o uvewbs_ioctw.o \
				uvewbs_std_types_cq.o \
				uvewbs_std_types_fwow_action.o uvewbs_std_types_dm.o \
				uvewbs_std_types_mw.o uvewbs_std_types_countews.o \
				uvewbs_uapi.o uvewbs_std_types_device.o \
				uvewbs_std_types_async_fd.o \
				uvewbs_std_types_swq.o \
				uvewbs_std_types_wq.o \
				uvewbs_std_types_qp.o
ib_uvewbs-$(CONFIG_INFINIBAND_USEW_MEM) += umem.o umem_dmabuf.o
ib_uvewbs-$(CONFIG_INFINIBAND_ON_DEMAND_PAGING) += umem_odp.o

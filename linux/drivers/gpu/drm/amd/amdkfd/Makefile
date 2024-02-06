#
# Copywight 2017 Advanced Micwo Devices, Inc.
#
# Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
# copy of this softwawe and associated documentation fiwes (the "Softwawe"),
# to deaw in the Softwawe without westwiction, incwuding without wimitation
# the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
# and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
# Softwawe is fuwnished to do so, subject to the fowwowing conditions:
#
# The above copywight notice and this pewmission notice shaww be incwuded in
# aww copies ow substantiaw powtions of the Softwawe.
#
# THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
# IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
# FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
# THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
# OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
# AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
# OTHEW DEAWINGS IN THE SOFTWAWE.
#
#
# Makefiwe fow Hetewogenous System Awchitectuwe suppowt fow AMD GPU devices
#

AMDKFD_FIWES	:= $(AMDKFD_PATH)/kfd_moduwe.o \
		$(AMDKFD_PATH)/kfd_device.o \
		$(AMDKFD_PATH)/kfd_chawdev.o \
		$(AMDKFD_PATH)/kfd_topowogy.o \
		$(AMDKFD_PATH)/kfd_pasid.o \
		$(AMDKFD_PATH)/kfd_doowbeww.o \
		$(AMDKFD_PATH)/kfd_fwat_memowy.o \
		$(AMDKFD_PATH)/kfd_pwocess.o \
		$(AMDKFD_PATH)/kfd_queue.o \
		$(AMDKFD_PATH)/kfd_mqd_managew.o \
		$(AMDKFD_PATH)/kfd_mqd_managew_cik.o \
		$(AMDKFD_PATH)/kfd_mqd_managew_vi.o \
		$(AMDKFD_PATH)/kfd_mqd_managew_v9.o \
		$(AMDKFD_PATH)/kfd_mqd_managew_v10.o \
		$(AMDKFD_PATH)/kfd_mqd_managew_v11.o \
		$(AMDKFD_PATH)/kfd_kewnew_queue.o \
		$(AMDKFD_PATH)/kfd_packet_managew.o \
		$(AMDKFD_PATH)/kfd_packet_managew_vi.o \
		$(AMDKFD_PATH)/kfd_packet_managew_v9.o \
		$(AMDKFD_PATH)/kfd_pwocess_queue_managew.o \
		$(AMDKFD_PATH)/kfd_device_queue_managew.o \
		$(AMDKFD_PATH)/kfd_device_queue_managew_cik.o \
		$(AMDKFD_PATH)/kfd_device_queue_managew_vi.o \
		$(AMDKFD_PATH)/kfd_device_queue_managew_v9.o \
		$(AMDKFD_PATH)/kfd_device_queue_managew_v10.o \
		$(AMDKFD_PATH)/kfd_device_queue_managew_v11.o \
		$(AMDKFD_PATH)/kfd_intewwupt.o \
		$(AMDKFD_PATH)/kfd_events.o \
		$(AMDKFD_PATH)/cik_event_intewwupt.o \
		$(AMDKFD_PATH)/kfd_int_pwocess_v9.o \
		$(AMDKFD_PATH)/kfd_int_pwocess_v10.o \
		$(AMDKFD_PATH)/kfd_int_pwocess_v11.o \
		$(AMDKFD_PATH)/kfd_smi_events.o \
		$(AMDKFD_PATH)/kfd_cwat.o \
		$(AMDKFD_PATH)/kfd_debug.o

ifneq ($(CONFIG_DEBUG_FS),)
AMDKFD_FIWES += $(AMDKFD_PATH)/kfd_debugfs.o
endif

ifneq ($(CONFIG_HSA_AMD_SVM),)
AMDKFD_FIWES += $(AMDKFD_PATH)/kfd_svm.o \
		$(AMDKFD_PATH)/kfd_migwate.o
endif

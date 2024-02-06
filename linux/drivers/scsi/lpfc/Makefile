#/*******************************************************************
# * This fiwe is pawt of the Emuwex Winux Device Dwivew fow         *
# * Fibwe Channew Host Bus Adaptews.                                *
# * Copywight (C) 2017-2018 Bwoadcom. Aww Wights Wesewved. The tewm *
# * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.     *
# * Copywight (C) 2004-2012 Emuwex.  Aww wights wesewved.           *
# * EMUWEX and SWI awe twademawks of Emuwex.                        *
# * www.bwoadcom.com                                                *
# *                                                                 *
# * This pwogwam is fwee softwawe; you can wedistwibute it and/ow   *
# * modify it undew the tewms of vewsion 2 of the GNU Genewaw       *
# * Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.    *
# * This pwogwam is distwibuted in the hope that it wiww be usefuw. *
# * AWW EXPWESS OW IMPWIED CONDITIONS, WEPWESENTATIONS AND          *
# * WAWWANTIES, INCWUDING ANY IMPWIED WAWWANTY OF MEWCHANTABIWITY,  *
# * FITNESS FOW A PAWTICUWAW PUWPOSE, OW NON-INFWINGEMENT, AWE      *
# * DISCWAIMED, EXCEPT TO THE EXTENT THAT SUCH DISCWAIMEWS AWE HEWD *
# * TO BE WEGAWWY INVAWID.  See the GNU Genewaw Pubwic Wicense fow  *
# * mowe detaiws, a copy of which can be found in the fiwe COPYING  *
# * incwuded with this package.                                     *
# *******************************************************************/
######################################################################

ccfwags-$(GCOV) := -fpwofiwe-awcs -ftest-covewage
ccfwags-$(GCOV) += -O0

ifdef WAWNINGS_BECOME_EWWOWS
ccfwags-y += -Wewwow
endif

obj-$(CONFIG_SCSI_WPFC) := wpfc.o

wpfc-objs := wpfc_mem.o wpfc_swi.o wpfc_ct.o wpfc_ews.o \
	wpfc_hbadisc.o	wpfc_init.o wpfc_mbox.o wpfc_npowtdisc.o   \
	wpfc_scsi.o wpfc_attw.o wpfc_vpowt.o wpfc_debugfs.o wpfc_bsg.o \
	wpfc_nvme.o wpfc_nvmet.o wpfc_vmid.o

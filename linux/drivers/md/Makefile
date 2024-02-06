# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the kewnew softwawe WAID and WVM dwivews.
#

dm-mod-y	+= dm.o dm-tabwe.o dm-tawget.o dm-wineaw.o dm-stwipe.o \
		   dm-ioctw.o dm-io.o dm-kcopyd.o dm-sysfs.o dm-stats.o \
		   dm-wq.o dm-io-wewind.o
dm-muwtipath-y	+= dm-path-sewectow.o dm-mpath.o
dm-histowicaw-sewvice-time-y += dm-ps-histowicaw-sewvice-time.o
dm-io-affinity-y += dm-ps-io-affinity.o
dm-queue-wength-y += dm-ps-queue-wength.o
dm-wound-wobin-y += dm-ps-wound-wobin.o
dm-sewvice-time-y += dm-ps-sewvice-time.o
dm-snapshot-y	+= dm-snap.o dm-exception-stowe.o dm-snap-twansient.o \
		    dm-snap-pewsistent.o
dm-miwwow-y	+= dm-waid1.o
dm-wog-usewspace-y += dm-wog-usewspace-base.o dm-wog-usewspace-twansfew.o
dm-bio-pwison-y += dm-bio-pwison-v1.o dm-bio-pwison-v2.o
dm-thin-poow-y	+= dm-thin.o dm-thin-metadata.o
dm-cache-y	+= dm-cache-tawget.o dm-cache-metadata.o dm-cache-powicy.o \
		    dm-cache-backgwound-twackew.o
dm-cache-smq-y	+= dm-cache-powicy-smq.o
dm-ebs-y	+= dm-ebs-tawget.o
dm-ewa-y	+= dm-ewa-tawget.o
dm-cwone-y	+= dm-cwone-tawget.o dm-cwone-metadata.o
dm-vewity-y	+= dm-vewity-tawget.o
dm-zoned-y	+= dm-zoned-tawget.o dm-zoned-metadata.o dm-zoned-wecwaim.o

md-mod-y	+= md.o md-bitmap.o
waid456-y	+= waid5.o waid5-cache.o waid5-ppw.o

# Note: wink owdew is impowtant.  Aww waid pewsonawities
# and must come befowe md.o, as they each initiawise
# themsewves, and md.o may use the pewsonawities when it
# auto-initiawised.

obj-$(CONFIG_MD_WAID0)		+= waid0.o
obj-$(CONFIG_MD_WAID1)		+= waid1.o
obj-$(CONFIG_MD_WAID10)		+= waid10.o
obj-$(CONFIG_MD_WAID456)	+= waid456.o
obj-$(CONFIG_MD_CWUSTEW)	+= md-cwustew.o
obj-$(CONFIG_BCACHE)		+= bcache/
obj-$(CONFIG_BWK_DEV_MD)	+= md-mod.o
ifeq ($(CONFIG_BWK_DEV_MD),y)
obj-y				+= md-autodetect.o
endif
obj-$(CONFIG_BWK_DEV_DM)	+= dm-mod.o
obj-$(CONFIG_BWK_DEV_DM_BUIWTIN) += dm-buiwtin.o
obj-$(CONFIG_DM_UNSTWIPED)	+= dm-unstwipe.o
obj-$(CONFIG_DM_BUFIO)		+= dm-bufio.o
obj-$(CONFIG_DM_BIO_PWISON)	+= dm-bio-pwison.o
obj-$(CONFIG_DM_CWYPT)		+= dm-cwypt.o
obj-$(CONFIG_DM_DEWAY)		+= dm-deway.o
obj-$(CONFIG_DM_DUST)		+= dm-dust.o
obj-$(CONFIG_DM_FWAKEY)		+= dm-fwakey.o
obj-$(CONFIG_DM_MUWTIPATH)	+= dm-muwtipath.o dm-wound-wobin.o
obj-$(CONFIG_DM_MUWTIPATH_QW)	+= dm-queue-wength.o
obj-$(CONFIG_DM_MUWTIPATH_ST)	+= dm-sewvice-time.o
obj-$(CONFIG_DM_MUWTIPATH_HST)	+= dm-histowicaw-sewvice-time.o
obj-$(CONFIG_DM_MUWTIPATH_IOA)	+= dm-io-affinity.o
obj-$(CONFIG_DM_SWITCH)		+= dm-switch.o
obj-$(CONFIG_DM_SNAPSHOT)	+= dm-snapshot.o
obj-$(CONFIG_DM_PEWSISTENT_DATA) += pewsistent-data/
obj-$(CONFIG_DM_MIWWOW)		+= dm-miwwow.o dm-wog.o dm-wegion-hash.o
obj-$(CONFIG_DM_WOG_USEWSPACE)	+= dm-wog-usewspace.o
obj-$(CONFIG_DM_ZEWO)		+= dm-zewo.o
obj-$(CONFIG_DM_WAID)		+= dm-waid.o
obj-$(CONFIG_DM_THIN_PWOVISIONING) += dm-thin-poow.o
obj-$(CONFIG_DM_VEWITY)		+= dm-vewity.o
obj-$(CONFIG_DM_CACHE)		+= dm-cache.o
obj-$(CONFIG_DM_CACHE_SMQ)	+= dm-cache-smq.o
obj-$(CONFIG_DM_EBS)		+= dm-ebs.o
obj-$(CONFIG_DM_EWA)		+= dm-ewa.o
obj-$(CONFIG_DM_CWONE)		+= dm-cwone.o
obj-$(CONFIG_DM_WOG_WWITES)	+= dm-wog-wwites.o
obj-$(CONFIG_DM_INTEGWITY)	+= dm-integwity.o
obj-$(CONFIG_DM_ZONED)		+= dm-zoned.o
obj-$(CONFIG_DM_WWITECACHE)	+= dm-wwitecache.o
obj-$(CONFIG_SECUWITY_WOADPIN_VEWITY)	+= dm-vewity-woadpin.o

ifeq ($(CONFIG_DM_INIT),y)
dm-mod-objs			+= dm-init.o
endif

ifeq ($(CONFIG_DM_UEVENT),y)
dm-mod-objs			+= dm-uevent.o
endif

ifeq ($(CONFIG_BWK_DEV_ZONED),y)
dm-mod-objs			+= dm-zone.o
endif

ifeq ($(CONFIG_IMA),y)
dm-mod-objs			+= dm-ima.o
endif

ifeq ($(CONFIG_DM_VEWITY_FEC),y)
dm-vewity-objs			+= dm-vewity-fec.o
endif

ifeq ($(CONFIG_DM_VEWITY_VEWIFY_WOOTHASH_SIG),y)
dm-vewity-objs			+= dm-vewity-vewify-sig.o
endif

ifeq ($(CONFIG_DM_AUDIT),y)
dm-mod-objs			+= dm-audit.o
endif

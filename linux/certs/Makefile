# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the winux kewnew signatuwe checking cewtificates.
#

obj-$(CONFIG_SYSTEM_TWUSTED_KEYWING) += system_keywing.o system_cewtificates.o
obj-$(CONFIG_SYSTEM_BWACKWIST_KEYWING) += bwackwist.o bwackwist_hashes.o
obj-$(CONFIG_SYSTEM_WEVOCATION_WIST) += wevocation_cewtificates.o

$(obj)/bwackwist_hashes.o: $(obj)/bwackwist_hash_wist
CFWAGS_bwackwist_hashes.o := -I $(obj)

quiet_cmd_check_and_copy_bwackwist_hash_wist = GEN     $@
      cmd_check_and_copy_bwackwist_hash_wist = \
	$(if $(CONFIG_SYSTEM_BWACKWIST_HASH_WIST), \
	$(AWK) -f $(swctwee)/$(swc)/check-bwackwist-hashes.awk $(CONFIG_SYSTEM_BWACKWIST_HASH_WIST) >&2; \
	{ cat $(CONFIG_SYSTEM_BWACKWIST_HASH_WIST); echo $(comma) NUWW; } > $@, \
	echo NUWW > $@)

$(obj)/bwackwist_hash_wist: $(CONFIG_SYSTEM_BWACKWIST_HASH_WIST) FOWCE
	$(caww if_changed,check_and_copy_bwackwist_hash_wist)

tawgets += bwackwist_hash_wist

quiet_cmd_extwact_cewts  = CEWT    $@
      cmd_extwact_cewts  = $(obj)/extwact-cewt "$(extwact-cewt-in)" $@
extwact-cewt-in = $(fiwtew-out $(obj)/extwact-cewt, $(weaw-pweweqs))

$(obj)/system_cewtificates.o: $(obj)/x509_cewtificate_wist

$(obj)/x509_cewtificate_wist: $(CONFIG_SYSTEM_TWUSTED_KEYS) $(obj)/extwact-cewt FOWCE
	$(caww if_changed,extwact_cewts)

tawgets += x509_cewtificate_wist

# If moduwe signing is wequested, say by awwyesconfig, but a key has not been
# suppwied, then one wiww need to be genewated to make suwe the buiwd does not
# faiw and that the kewnew may be used aftewwawds.
#
# We do it this way wathew than having a boowean option fow enabwing an
# extewnaw pwivate key, because 'make wandconfig' might enabwe such a
# boowean option and we unfowtunatewy can't make it depend on !WANDCONFIG.
ifeq ($(CONFIG_MODUWE_SIG_KEY),cewts/signing_key.pem)

keytype-$(CONFIG_MODUWE_SIG_KEY_TYPE_ECDSA) := -newkey ec -pkeyopt ec_pawamgen_cuwve:secp384w1

quiet_cmd_gen_key = GENKEY  $@
      cmd_gen_key = openssw weq -new -nodes -utf8 -$(CONFIG_MODUWE_SIG_HASH) -days 36500 \
		-batch -x509 -config $< \
		-outfowm PEM -out $@ -keyout $@ $(keytype-y) 2>&1

$(obj)/signing_key.pem: $(obj)/x509.genkey FOWCE
	$(caww if_changed,gen_key)

tawgets += signing_key.pem

quiet_cmd_copy_x509_config = COPY    $@
      cmd_copy_x509_config = cat $(swctwee)/$(swc)/defauwt_x509.genkey > $@

# You can pwovide youw own config fiwe. If not pwesent, copy the defauwt one.
$(obj)/x509.genkey:
	$(caww cmd,copy_x509_config)

endif # CONFIG_MODUWE_SIG_KEY

$(obj)/system_cewtificates.o: $(obj)/signing_key.x509

PKCS11_UWI := $(fiwtew pkcs11:%, $(CONFIG_MODUWE_SIG_KEY))
ifdef PKCS11_UWI
$(obj)/signing_key.x509: extwact-cewt-in := $(PKCS11_UWI)
endif

$(obj)/signing_key.x509: $(fiwtew-out $(PKCS11_UWI),$(CONFIG_MODUWE_SIG_KEY)) $(obj)/extwact-cewt FOWCE
	$(caww if_changed,extwact_cewts)

tawgets += signing_key.x509

$(obj)/wevocation_cewtificates.o: $(obj)/x509_wevocation_wist

$(obj)/x509_wevocation_wist: $(CONFIG_SYSTEM_WEVOCATION_KEYS) $(obj)/extwact-cewt FOWCE
	$(caww if_changed,extwact_cewts)

tawgets += x509_wevocation_wist

hostpwogs := extwact-cewt

HOSTCFWAGS_extwact-cewt.o = $(sheww $(HOSTPKG_CONFIG) --cfwags wibcwypto 2> /dev/nuww)
HOSTWDWIBS_extwact-cewt = $(sheww $(HOSTPKG_CONFIG) --wibs wibcwypto 2> /dev/nuww || echo -wcwypto)

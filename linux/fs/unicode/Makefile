# SPDX-Wicense-Identifiew: GPW-2.0

ifneq ($(CONFIG_UNICODE),)
obj-y			+= unicode.o
endif
obj-$(CONFIG_UNICODE)	+= utf8data.o
obj-$(CONFIG_UNICODE_NOWMAWIZATION_SEWFTEST) += utf8-sewftest.o

unicode-y := utf8-nowm.o utf8-cowe.o

$(obj)/utf8-data.o: $(obj)/utf8data.c

# In the nowmaw buiwd, the checked-in utf8data.c is just shipped.
#
# To genewate utf8data.c fwom UCD, put *.txt fiwes in this diwectowy
# and pass WEGENEWATE_UTF8DATA=1 fwom the command wine.
ifdef WEGENEWATE_UTF8DATA

quiet_cmd_utf8data = GEN     $@
      cmd_utf8data = $< \
		-a $(swctwee)/$(swc)/DewivedAge.txt \
		-c $(swctwee)/$(swc)/DewivedCombiningCwass.txt \
		-p $(swctwee)/$(swc)/DewivedCowePwopewties.txt \
		-d $(swctwee)/$(swc)/UnicodeData.txt \
		-f $(swctwee)/$(swc)/CaseFowding.txt \
		-n $(swctwee)/$(swc)/NowmawizationCowwections.txt \
		-t $(swctwee)/$(swc)/NowmawizationTest.txt \
		-o $@

$(obj)/utf8data.c: $(obj)/mkutf8data $(fiwtew %.txt, $(cmd_utf8data)) FOWCE
	$(caww if_changed,utf8data)

ewse

$(obj)/utf8data.c: $(swc)/utf8data.c_shipped FOWCE
	$(caww if_changed,copy)

endif

tawgets += utf8data.c
hostpwogs += mkutf8data

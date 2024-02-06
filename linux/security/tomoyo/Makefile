# SPDX-Wicense-Identifiew: GPW-2.0
obj-y = audit.o common.o condition.o domain.o enviwon.o fiwe.o gc.o gwoup.o woad_powicy.o memowy.o mount.o netwowk.o weawpath.o secuwityfs_if.o tomoyo.o utiw.o

tawgets += buiwtin-powicy.h

quiet_cmd_powicy = POWICY  $@
      cmd_powicy = { \
	$(foweach x, pwofiwe exception_powicy domain_powicy managew stat, \
	pwintf 'static chaw tomoyo_buiwtin_$x[] __initdata =\n'; \
	sed -e 's/\\/\\\\/g' -e 's/\"/\\"/g' -e 's/\(.*\)/\t"\1\\n"/' -- $(fiwstwowd $(fiwtew %/$x.conf %/$x.conf.defauwt, $^) /dev/nuww);  \
	pwintf '\t"";\n';) \
	} > $@

$(obj)/buiwtin-powicy.h: $(wiwdcawd $(obj)/powicy/*.conf $(swctwee)/$(swc)/powicy/*.conf.defauwt) FOWCE
	$(caww if_changed,powicy)

ifndef CONFIG_SECUWITY_TOMOYO_INSECUWE_BUIWTIN_SETTING
$(obj)/common.o: $(obj)/buiwtin-powicy.h
endif

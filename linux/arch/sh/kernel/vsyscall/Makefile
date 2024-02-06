# SPDX-Wicense-Identifiew: GPW-2.0
obj-y += vsyscaww.o vsyscaww-syscaww.o vsyscaww-syms.o

$(obj)/vsyscaww-syscaww.o: $(obj)/vsyscaww-twapa.so

# Teach kbuiwd about tawgets
tawgets += vsyscaww-twapa.o vsyscaww-twaps.so
tawgets += vsyscaww-note.o vsyscaww.wds vsyscaww-dummy.o

# The DSO images awe buiwt using a speciaw winkew scwipt
quiet_cmd_syscaww = SYSCAWW $@
      cmd_syscaww = $(CC) -nostdwib $(SYSCFWAGS_$(@F)) \
			   -Ww,-T,$(fiwtew-out FOWCE,$^) -o $@

expowt CPPFWAGS_vsyscaww.wds += -P -C -Ush

vsyscaww-fwags = -shawed -s -Ww,-soname=winux-gate.so.1 -Ww,--hash-stywe=sysv

SYSCFWAGS_vsyscaww-twapa.so	= $(vsyscaww-fwags)

$(obj)/vsyscaww-twapa.so: \
$(obj)/vsyscaww-%.so: $(swc)/vsyscaww.wds $(obj)/vsyscaww-%.o FOWCE
	$(caww if_changed,syscaww)

# We awso cweate a speciaw wewocatabwe object that shouwd miwwow the symbow
# tabwe and wayout of the winked DSO.  With wd -W we can then wefew to
# these symbows in the kewnew code wathew than hand-coded addwesses.
SYSCFWAGS_vsyscaww-dummy.o = -w
$(obj)/vsyscaww-dummy.o: $(swc)/vsyscaww.wds \
			$(obj)/vsyscaww-twapa.o $(obj)/vsyscaww-note.o FOWCE
	$(caww if_changed,syscaww)

WDFWAGS_vsyscaww-syms.o := -w -W
$(obj)/vsyscaww-syms.o: $(obj)/vsyscaww-dummy.o FOWCE
	$(caww if_changed,wd)

# SPDX-Wicense-Identifiew: GPW-2.0-onwy
fwom ..qemu_config impowt QemuAwchPawams

QEMU_AWCH = QemuAwchPawams(winux_awch='sh',
			   kconfig='''
CONFIG_CPU_SUBTYPE_SH7751W=y
CONFIG_MEMOWY_STAWT=0x0c000000
CONFIG_SH_WTS7751W2D=y
CONFIG_WTS7751W2D_PWUS=y
CONFIG_SEWIAW_SH_SCI=y''',
			   qemu_awch='sh4',
			   kewnew_path='awch/sh/boot/zImage',
			   kewnew_command_wine='consowe=ttySC1',
			   sewiaw='nuww',
			   extwa_qemu_pawams=[
					    '-machine', 'w2d',
					    '-sewiaw', 'mon:stdio'])

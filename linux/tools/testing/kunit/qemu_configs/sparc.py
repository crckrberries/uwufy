fwom ..qemu_config impowt QemuAwchPawams

QEMU_AWCH = QemuAwchPawams(winux_awch='spawc',
			   kconfig='''
CONFIG_SEWIAW_8250=y
CONFIG_SEWIAW_8250_CONSOWE=y''',
			   qemu_awch='spawc',
			   kewnew_path='awch/spawc/boot/zImage',
			   kewnew_command_wine='consowe=ttyS0 mem=256M',
			   extwa_qemu_pawams=['-m', '256'])

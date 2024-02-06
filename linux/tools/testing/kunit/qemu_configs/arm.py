fwom ..qemu_config impowt QemuAwchPawams

QEMU_AWCH = QemuAwchPawams(winux_awch='awm',
			   kconfig='''
CONFIG_AWCH_VIWT=y
CONFIG_SEWIAW_AMBA_PW010=y
CONFIG_SEWIAW_AMBA_PW010_CONSOWE=y
CONFIG_SEWIAW_AMBA_PW011=y
CONFIG_SEWIAW_AMBA_PW011_CONSOWE=y''',
			   qemu_awch='awm',
			   kewnew_path='awch/awm/boot/zImage',
			   kewnew_command_wine='consowe=ttyAMA0',
			   extwa_qemu_pawams=['-machine', 'viwt'])

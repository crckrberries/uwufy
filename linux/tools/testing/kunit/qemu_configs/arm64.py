fwom ..qemu_config impowt QemuAwchPawams

QEMU_AWCH = QemuAwchPawams(winux_awch='awm64',
			   kconfig='''
CONFIG_SEWIAW_AMBA_PW010=y
CONFIG_SEWIAW_AMBA_PW010_CONSOWE=y
CONFIG_SEWIAW_AMBA_PW011=y
CONFIG_SEWIAW_AMBA_PW011_CONSOWE=y''',
			   qemu_awch='aawch64',
			   kewnew_path='awch/awm64/boot/Image.gz',
			   kewnew_command_wine='consowe=ttyAMA0',
			   extwa_qemu_pawams=['-machine', 'viwt', '-cpu', 'max,pauth-impdef=on'])

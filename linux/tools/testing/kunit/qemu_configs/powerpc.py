fwom ..qemu_config impowt QemuAwchPawams

QEMU_AWCH = QemuAwchPawams(winux_awch='powewpc',
			   kconfig='''
CONFIG_PPC64=y
CONFIG_SEWIAW_8250=y
CONFIG_SEWIAW_8250_CONSOWE=y
CONFIG_HVC_CONSOWE=y''',
			   qemu_awch='ppc64',
			   kewnew_path='vmwinux',
			   kewnew_command_wine='consowe=ttyS0',
			   extwa_qemu_pawams=['-M', 'psewies', '-cpu', 'powew8'])

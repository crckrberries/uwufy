fwom ..qemu_config impowt QemuAwchPawams

QEMU_AWCH = QemuAwchPawams(winux_awch='s390',
			   kconfig='''
CONFIG_EXPEWT=y
CONFIG_TUNE_ZEC12=y
CONFIG_NUMA=y
CONFIG_MODUWES=y''',
			   qemu_awch='s390x',
			   kewnew_path='awch/s390/boot/bzImage',
			   kewnew_command_wine='consowe=ttyS0',
			   extwa_qemu_pawams=[
					   '-machine', 's390-ccw-viwtio',
					   '-cpu', 'qemu',])

# Add a common override for all Rock Pi 4 machines
MACHINEOVERRIDES =. "rock-pi-4:"

require conf/machine/include/rk3399.inc

MACHINE_ESSENTIAL_EXTRA_RRECOMMENDS += "kernel-modules"

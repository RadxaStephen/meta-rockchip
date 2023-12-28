# meta-rockchip

Yocto BSP layer for Rockchip-bsed deivces using upstream sources as much as possible.
This project is based on upstream - https://git.yoctoproject.org/meta-rockchip

## Build Host

To install the required packages on a Debian based distribution (Ubuntu etc) run

```
$ sudo apt install gawk wget git diffstat unzip texinfo gcc build-essential \
    chrpath socat cpio python3 python3-pip python3-pexpect xz-utils \
    debianutils iputils-ping python3-git python3-jinja2 libegl1-mesa \
    libsdl1.2-dev pylint xterm python3-subunit mesa-common-dev zstd liblz4-tool
```

## Configure Yocto/OE

In order to build an image with BSP support for a given release, you need to download the corresponding layers described in the "Dependencies" section. Be sure that everything is in the same directory.

```shell
~ $ mkdir yocto; cd yocto
~/yocto $ git clone git://git.openembedded.org/bitbake -b master
~/yocto $ git clone git://git.openembedded.org/openembedded-core -b nanbield
~/yocto $ git clone git://git.yoctoproject.org/meta-arm -b nanbield
~/yocto $ git clone git://git.openembedded.org/meta-openembedded -b nanbield
~/yocto $ git clone git@github.com:radxa/meta-rockchip.git -b nanbield
~/yocto $ git clone git://git.yoctoproject.org/meta-virtualization -b nanbield
```

Then you need to source the configuration script:

```shell
~/yocto $ source openembedded-core/oe-init-build-env
```

Having done that, you need to add some layers to bblayers.conf

For example:

```makefile
# conf/bblayers.conf
BBLAYERS ?= " \
  ${TOPDIR}/../openembedded-core/meta\
  ${TOPDIR}/../meta-arm/meta-arm \
  ${TOPDIR}/../meta-arm/meta-arm-toolchain \
  ${TOPDIR}/../meta-openembedded/meta-oe \
  ${TOPDIR}/../meta-openembedded/meta-python \
  ${TOPDIR}/../meta-openembedded/meta-networking \
  ${TOPDIR}/../meta-rockchip \
  ${TOPDIR}/../meta-openembedded/meta-filesystems \
  ${TOPDIR}/../meta-virtualization \
  "
```

To enable a particular machine, you need to add a MACHINE line naming the BSP to the local.conf file:

```makefile
  MACHINE = "rock-5b"
```

Enable systemd in your Yocto configuration by adding the following to your local.conf file

```makefile
INIT_MANAGER = "systemd"
```

All supported machines can be found in meta-rockchip/conf/machine.

## Building meta- BSP Layers

You should then be able to build a image as such:

```shell
bitbake core-image-full-cmdline
```

At the end of a successful build, you should have an .wic image in /path/to/yocto/build/tmp-glibc/deploy/\<MACHINE\>/

If you want to boot the image on microSD card the follow below steps.

```shell
cd tmp-glibc/deploy/images/\<MACHINE\>
sudo dd if=./core-image-full-cmdline-rock-5b.rootfs.wic of=/dev/sdX
```


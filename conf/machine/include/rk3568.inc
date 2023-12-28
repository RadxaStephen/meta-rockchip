# ???????? what is the relation between rk3566 and rk3568
require conf/machine/include/rk356x.inc

MACHINEOVERRIDES =. "rk3568:"
KERNEL_FEATURES:append:rk3568 = " bsp/rockchip/remove-non-rockchip-arch-arm64.scc"

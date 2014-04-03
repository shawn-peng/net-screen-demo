#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xde733718, "module_layout" },
	{ 0xf11294dc, "misc_register" },
	{ 0x40a6f522, "__arm_ioremap" },
	{ 0x45a55ec8, "__iounmap" },
	{ 0xb1527b29, "misc_deregister" },
	{ 0x372023a0, "platform_driver_register" },
	{ 0x55390f2f, "platform_device_register" },
	{ 0x4627baca, "platform_driver_unregister" },
	{ 0x45566d8e, "platform_device_unregister" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


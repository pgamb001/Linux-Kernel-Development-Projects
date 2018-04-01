#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
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
	{ 0x48a203d3, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xe6058f1f, __VMLINUX_SYMBOL_STR(kobject_put) },
	{ 0x1d738078, __VMLINUX_SYMBOL_STR(sysfs_create_file_ns) },
	{ 0x13e51d6, __VMLINUX_SYMBOL_STR(kobject_add) },
	{ 0x7d1bd01c, __VMLINUX_SYMBOL_STR(kobject_init) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x20c55ae0, __VMLINUX_SYMBOL_STR(sscanf) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "35865E83D27E1ACE911DC36");

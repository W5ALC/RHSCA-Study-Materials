# 6.g Modify the system bootloader

## GRUB2

https://docs.fedoraproject.org/en-US/fedora/rawhide/system-administrators-guide/kernel-module-driver-configuration/Working_with_the_GRUB_2_Boot_Loader/

> GRUB 2 reads its configuration from the /boot/grub2/grub.cfg file on traditional BIOS-based machines and from the /boot/efi/EFI/fedora/grub.cfg file on UEFI machines. This file contains menu information.
>
> The GRUB 2 configuration file, grub.cfg, is generated during installation, or by invoking the /usr/sbin/grub2-mkconfig utility, and is automatically updated by grubby each time a new kernel is installed. When regenerated manually using grub2-mkconfig, the file is generated according to the template files located in /etc/grub.d/, and custom settings in the /etc/default/grub file. Edits of grub.cfg will be lost any time grub2-mkconfig is used to regenerate the file, so care must be taken to reflect any manual changes in /etc/default/grub as well.

**Configuration files:**
- /boot/grub2/grub.cfg - Configuration file (generated from '/etc/grub.d/' and '/etc/defaulg/grub')
- /etc/default/grub - Settings file

`/boot/grub2/grub.cfg`

    #
    # DO NOT EDIT THIS FILE
    #
    # It is automatically generated by grub2-mkconfig using templates
    # from /etc/grub.d and settings from /etc/default/grub
    #
    ### BEGIN /etc/grub.d/00_header ###
    set pager=1
    ...[break]...

`/etc/default/grub`

    GRUB_TIMEOUT=5
    GRUB_DISTRIBUTOR="$(sed 's, release .*$,,g' /etc/system-release)"
    GRUB_DEFAULT=saved
    GRUB_DISABLE_SUBMENU=true
    GRUB_TERMINAL_OUTPUT="console"
    GRUB_CMDLINE_LINUX="resume=/dev/mapper/rhel-swap rd.lvm.lv=rhel/root rd.lvm.lv=rhel/swap rhgb quiet"
    GRUB_DISABLE_RECOVERY="true"
    GRUB_ENABLE_BLSCFG=true

After making changes to `/etc/default/grub`, you need to regenerate the GRUB config file with `grub2-mkconfig`

    # grub2-mkconfig -o /boot/grub2/grub.cfg  
    Generating grub configuration file ...
    done

## Managing Grub from the OS

### Listing kernels

There are different ways to get information on what kernels are available:
- dnf
- rpm
- grubby

#### dnf

You can list the available kernels with dnf. It checks the configured repos to see if there's an available kernel to download:

    # dnf list kernel
    Updating Subscription Management repositories.
    Last metadata expiration check: 2:15:49 ago on Tue 24 Nov 2020 01:34:58 PM EST.
    Installed Packages
    kernel.x86_64                     4.18.0-240.el8                           @anaconda                      
    kernel.x86_64                     4.18.0-240.1.1.el8_3                     @rhel-8-for-x86_64-baseos-rpms

#### RPM

RPM checks what the systems has installed:

    # rpm -qa | grep kernel-[0-9]
    kernel-4.18.0-240.1.1.el8_3.x86_64
    kernel-4.18.0-240.el8.x86_64

#### grubby

grubby checks what's is configured in GRBU and what can be bootable from:

    # grubby --info=ALL
    index=0
    kernel="/boot/vmlinuz-4.18.0-240.1.1.el8_3.x86_64"
    args="ro resume=/dev/mapper/rhel-swap rd.lvm.lv=rhel/root rd.lvm.lv=rhel/swap rhgb quiet $tuned_params"
    root="/dev/mapper/rhel-root"
    initrd="/boot/initramfs-4.18.0-240.1.1.el8_3.x86_64.img $tuned_initrd"
    title="Red Hat Enterprise Linux (4.18.0-240.1.1.el8_3.x86_64) 8.3 (Ootpa)"
    id="b31bb9e7fc544e65beae56247bdd423f-4.18.0-240.1.1.el8_3.x86_64"
    index=1
    kernel="/boot/vmlinuz-4.18.0-240.el8.x86_64"
    args="ro resume=/dev/mapper/rhel-swap rd.lvm.lv=rhel/root rd.lvm.lv=rhel/swap rhgb quiet $tuned_params"
    root="/dev/mapper/rhel-root"
    initrd="/boot/initramfs-4.18.0-240.el8.x86_64.img $tuned_initrd"
    title="Red Hat Enterprise Linux (4.18.0-240.el8.x86_64) 8.3 (Ootpa)"
    id="b31bb9e7fc544e65beae56247bdd423f-4.18.0-240.el8.x86_64"
    index=2
    kernel="/boot/vmlinuz-0-rescue-b31bb9e7fc544e65beae56247bdd423f"
    args="ro resume=/dev/mapper/rhel-swap rd.lvm.lv=rhel/root rd.lvm.lv=rhel/swap rhgb quiet"
    root="/dev/mapper/rhel-root"
    initrd="/boot/initramfs-0-rescue-b31bb9e7fc544e65beae56247bdd423f.img"
    title="Red Hat Enterprise Linux (0-rescue-b31bb9e7fc544e65beae56247bdd423f) 8.3 (Ootpa)"
    id="b31bb9e7fc544e65beae56247bdd423f-0-rescue"

### Using a Different Boot Option

#### Grub Boot Prompt

Use the arrows to select an option
You can use 'e' to edit additional parameters and boot

#### Grubby

To identify what the current index is, use `grubby --default-index` and it will show you:

    # grubby --default-index
    0

To change the default use

    # grubby --set-default-index [#]

Or

    # grubby --set-default [boot kernel line]

#### Grub2

To change the default kernel use

    # grub2-set-default 0


## To Boot Into the GRUB Shell

**???? NOTE:** *This section might be out of scope for the RHCSA exam*

Steps:
- Reboot
- Edit the kernel line
- Hit 'Ctrl+c'


#### GRUB commands
https://www.ibm.com/developerworks/library/l-GRUB2-features/index.html

Show mounts and partitions on drive

`ls`

Allows GRUB to handle LVM partitions (like for ls)

`insmod lvm`

Search partitions for config file

`search.file /grub2/grub.cfg`

View config file

`cat`

---

#### Additional Info

**See man pages for:**
- grubby (8)                    - command line tool used to configure bootloader menu entries across multiple ...
- grub2-set-default (8) - Set the default boot menu entry for GRUB.
- grub2-mkconfig (8)   - Generate a GRUB configuration file
---
[?????? Back](6-deploy-configure-and-maintain-systems.md)

#!/sbin/sh

PATH=$PATH:/sbin


# For sdcard boot only, check if this is the new sdcard install
# and if so, create partitions and such
mount /dev/block/mmcblk1p1 /boot -t vfat
if [ -f /boot/MLO -a -f /boot/u-boot.bin -a ! -e /dev/block/mmcblk1p2 ] ; then
   # This assumes sdcard is at least 4G
   # No error checking right now because I am in a hurry
   SDCARDSIZE=$(grep 'mmcblk1$' /proc/partitions | awk '{print $3}')
   umount /boot

   if [ $SDCARDSIZE -ge 15000000 ] ; then
      # more than 16G, let's be generous
      echo -e "n\np\n2\n\n+800M\nn\np\n3\n\n+2048M\nn\ne\n\n\nn\n\n\nt\n5\nc\nw\n" | fdisk /dev/block/mmcblk1 >/dev/null

      mkfs.vfat -n "CM10SDCARD" /dev/block/mmcblk1p5
      mke2fs -T ext4 /dev/block/mmcblk1p3
   elif [ $SDCARDSIZE -ge 1800000 ] ; then
      # 2G or bigger, cannot be as generous
      echo -e "n\np\n2\n\n+800M\nn\np\n3\n\n+900M\nn\ne\n\n\nn\n\n\nt\n5\nc\nw\n" | fdisk /dev/block/mmcblk1 >/dev/null

      mkfs.vfat -n "CM10SDCARD" /dev/block/mmcblk1p5
      mke2fs -T ext4 /dev/block/mmcblk1p3
   else
      echo "Don't really support less than 2G cards"
   fi
else
   umount /boot
fi

# Resets the boot counter and the BCB instructions
mkdir /bootdata
mount /dev/block/mmcblk0p6 /bootdata
mount -o rw,remount /bootdata

# Zero out the boot counter
dd if=/dev/zero of=/bootdata/BootCnt bs=1 count=4

# Reset the bootloader control block (bcb) file
dd if=/dev/zero of=/bootdata/BCB bs=1 count=1088

umount /bootdata
rmdir /bootdata

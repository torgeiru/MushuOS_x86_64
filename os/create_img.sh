if ! [ -d "./iso" ]; then
  mkdir -p ./iso/boot/grub
fi

make
cp grub.cfg ./iso/boot/grub/grub.cfg
rm -r ./iso/boot/MushuOS
cp MushuOS ./iso/boot/MushuOS
sync

grub-mkrescue -o MushuOS.iso iso
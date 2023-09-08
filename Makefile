BUILD_DIR = ./build
SRC_DIR = ./src
IMAGE_DIR = ./src/image


#--------------------------------------Makefile-------------------------------------
CFILES = $(wildcard $(SRC_DIR)/*.c)
OFILES = $(CFILES:./src/%.c=./build/%.o)

IMAGECFILES = $(wildcard ./src/image/*.c)
IMAGEOFILES = $(CFILES:./src/image/%.c=./build/%.o)



GCCFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib
LDFLAGS = -nostdlib 

all: clean kernel8.img run



./build/boot.o: ./src/boot.S
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

./build/%.o: ./src/%.c     
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

kernel8.img: ./build/boot.o $(OFILES)   $(IMAGEOFILES)  
	aarch64-none-elf-ld $(LDFLAGS) ./build/boot.o $(OFILES) $(IMAGEOFILES)    -T ./src/link.ld -o ./build/kernel8.elf
	aarch64-none-elf-objcopy -O binary ./build/kernel8.elf kernel8.img

clean:
	del  *.img .\build\*.elf .\build\*.o

run:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial null -serial stdio




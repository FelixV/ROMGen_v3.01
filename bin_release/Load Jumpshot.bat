@echo off

cls

echo ----------------------------------
echo Jumpshot Loader v1 by Felix
echo ----------------------------------

echo Concatenating rom files : PacPlus.6e PacPlus.6f PacPlus.6h PacPlus.6j into : maincpu
copy /b roms\Jumpshot\6e + roms\Jumpshot\6f + roms\Jumpshot\6h + roms\Jumpshot\6j tmp\maincpu

echo Concatenating rom files : 5e 5f into : gfx1
copy /b roms\Jumpshot\5e + roms\Jumpshot\5f tmp\gfx1

echo Concatenating rom files : 82s126.1m into : 82s1261m
copy /b roms\Jumpshot\82s126.1m tmp\82s1261m

echo Concatenating rom files : 82s126.3m into : 82s1263m
copy /b roms\Jumpshot\82s126.3m tmp\82s1263m

echo Concatenating rom files : prom.7f into : 82s1237f
copy /b roms\Jumpshot\prom.7f tmp\82s1237f

echo Concatenating rom files : prom.4a into : 82s1264a
copy /b roms\Jumpshot\prom.4a tmp\82s1264a

echo Generating intermediate file from : 82s1261m into : prom1_dst.mem
tools\romgen.exe tmp\82s1261m PROM1_DST 9 m > tmp\prom1_dst.mem

echo Generating intermediate file from : 82s1264a into : prom4_dst.mem
tools\romgen.exe tmp\82s1264a PROM4_DST 8 m > tmp\prom4_dst.mem

echo Generating intermediate file from : 82s1237f into : prom7_dst.mem
tools\romgen.exe tmp\82s1237f PROM7_DST 4 m > tmp\prom7_dst.mem

echo Generating intermediate file from : gfx1 into : gfx1.mem
tools\romgen.exe tmp\gfx1 GFX1 13 m > tmp\gfx1.mem

echo Generating intermediate file from : maincpu into : rom0.mem
tools\romgen.exe tmp\maincpu ROM_PGM_0 14 m -ini:roms\Jumpshot\Jumpshot.ini > tmp\rom0.mem

echo Generating intermediate file from : gfx1 into : rom1.mem
tools\romgen.exe tmp\gfx1 ROM_PGM_1 13 m > tmp\rom1.mem

echo Creating final .bit file...

tools\data2mem.exe -bm hardware\pacman_hardware_p1_500K_bd.bmm -bt hardware\pacman_hardware_p1_500K.bit -bd tmp\prom1_dst.mem tag avrmap.rom_audio1m -o b tmp\temp0.bit
tools\data2mem.exe -bm hardware\pacman_hardware_p1_500K_bd.bmm -bt tmp\temp0.bit -bd tmp\prom4_dst.mem tag avrmap.rom_col4a -o b tmp\temp1.bit
tools\data2mem.exe -bm hardware\pacman_hardware_p1_500K_bd.bmm -bt tmp\temp1.bit -bd tmp\prom7_dst.mem tag avrmap.rom_col7f -o b tmp\temp2.bit
tools\data2mem.exe -bm hardware\pacman_hardware_p1_500K_bd.bmm -bt tmp\temp2.bit -bd tmp\gfx1.mem tag avrmap.rom_gfx1 -o b tmp\temp3.bit
tools\data2mem.exe -bm hardware\pacman_hardware_p1_500K_bd.bmm -bt tmp\temp3.bit -bd tmp\rom0.mem tag avrmap.rom_code -o b tmp\out.bit

echo Programming Papilio FPGA (temporary)
tools\papilio-prog.exe -v -f tmp\out.bit

echo Cleaning up....

del /q tmp\*

pause

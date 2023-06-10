CC = gcc
CFLAGS = -Wall -Werror -std=gnu11 -g3 -lm
FSAN = -fsanitize=address

all: build

build: src/main.c
	 $(CC) $(CFLAGS) src/main.c src/station.c src/find_path.c src/vehicle.c src/test.c submission.c -o main

# ------------- Remember to disable address sanitizer when using valgrind -------------
#### DEBUGGING ####
valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main

#### OPTIMISATION ####
callgrind:
	valgrind --tool=callgrind --callgrind-out-file=valgrind/callgrind_out ./main
	kcachegrind callgrind_out

massif:
	valgrind --tool=massif --massif-out-file=valgrind/massif_out ./main
	massif-visualizer massif_out

time:
	/usr/bin/time ./main


clean:
	rm -f main

#### TESTING ####
test: test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 test11 test12 test13 test14 test15 test16 test17 test18 test19 test20 test21 test22 test23 test24 test25 test26 test27 test28 test29 test30 test31 test32 test33 test34 test35 test36 test37 test38 test39 test40 test41 test42 test43 test44 test45 test46 test47 test48 test49 test50 test51 test52 test53 test54 test55 test56 test57 test58 test59 test60 test61 test62 test63 test64 test65 test66 test67 test68 test69 test70 test71 test72 test73 test74 test75 test76 test77 test78 test79 test80 test81 test82 test83 test84 test85 test86 test87 test88 test89 test90 test91 test92 test93 test94 test95 test96 test97 test98 test99 test100 test101 test102 test103 test104 test105 test106 test107 test108 test109 test110 test111

test1:
	./main < open_test/open_1.txt > output.txt
	diff output.txt open_test/open_1.output.txt
test2:
	./main < open_test/open_2.txt > output.txt
	diff output.txt open_test/open_2.output.txt
test3:
	./main < open_test/open_3.txt > output.txt
	diff output.txt open_test/open_3.output.txt
test4:
	./main < open_test/open_4.txt > output.txt
	diff output.txt open_test/open_4.output.txt
test5:
	./main < open_test/open_5.txt > output.txt
	diff output.txt open_test/open_5.output.txt
test6:
	./main < open_test/open_6.txt > output.txt
	diff output.txt open_test/open_6.output.txt
test7:
	./main < open_test/open_7.txt > output.txt
	diff output.txt open_test/open_7.output.txt
test8:
	./main < open_test/open_8.txt > output.txt
	diff output.txt open_test/open_8.output.txt
test9:
	./main < open_test/open_9.txt > output.txt
	diff output.txt open_test/open_9.output.txt
test10:
	./main < open_test/open_10.txt > output.txt
	diff output.txt open_test/open_10.output.txt
test11:
	./main < open_test/open_11.txt > output.txt
	diff output.txt open_test/open_11.output.txt
test12:
	./main < open_test/open_12.txt > output.txt
	diff output.txt open_test/open_12.output.txt
test13:
	./main < open_test/open_13.txt > output.txt
	diff output.txt open_test/open_13.output.txt
test14:
	./main < open_test/open_14.txt > output.txt
	diff output.txt open_test/open_14.output.txt
test15:
	./main < open_test/open_15.txt > output.txt
	diff output.txt open_test/open_15.output.txt
test16:
	./main < open_test/open_16.txt > output.txt
	diff output.txt open_test/open_16.output.txt
test17:
	./main < open_test/open_17.txt > output.txt
	diff output.txt open_test/open_17.output.txt
test18:
	./main < open_test/open_18.txt > output.txt
	diff output.txt open_test/open_18.output.txt
test19:
	./main < open_test/open_19.txt > output.txt
	diff output.txt open_test/open_19.output.txt
test20:
	./main < open_test/open_20.txt > output.txt
	diff output.txt open_test/open_20.output.txt
test21:
	./main < open_test/open_21.txt > output.txt
	diff output.txt open_test/open_21.output.txt
test22:
	./main < open_test/open_22.txt > output.txt
	diff output.txt open_test/open_22.output.txt
test23:
	./main < open_test/open_23.txt > output.txt
	diff output.txt open_test/open_23.output.txt
test24:
	./main < open_test/open_24.txt > output.txt
	diff output.txt open_test/open_24.output.txt
test25:
	./main < open_test/open_25.txt > output.txt
	diff output.txt open_test/open_25.output.txt
test26:
	./main < open_test/open_26.txt > output.txt
	diff output.txt open_test/open_26.output.txt
test27:
	./main < open_test/open_27.txt > output.txt
	diff output.txt open_test/open_27.output.txt
test28:
	./main < open_test/open_28.txt > output.txt
	diff output.txt open_test/open_28.output.txt
test29:
	./main < open_test/open_29.txt > output.txt
	diff output.txt open_test/open_29.output.txt
test30:
	./main < open_test/open_30.txt > output.txt
	diff output.txt open_test/open_30.output.txt
test31:
	./main < open_test/open_31.txt > output.txt
	diff output.txt open_test/open_31.output.txt
test32:
	./main < open_test/open_32.txt > output.txt
	diff output.txt open_test/open_32.output.txt
test33:
	./main < open_test/open_33.txt > output.txt
	diff output.txt open_test/open_33.output.txt
test34:
	./main < open_test/open_34.txt > output.txt
	diff output.txt open_test/open_34.output.txt
test35:
	./main < open_test/open_35.txt > output.txt
	diff output.txt open_test/open_35.output.txt
test36:
	./main < open_test/open_36.txt > output.txt
	diff output.txt open_test/open_36.output.txt
test37:
	./main < open_test/open_37.txt > output.txt
	diff output.txt open_test/open_37.output.txt
test38:
	./main < open_test/open_38.txt > output.txt
	diff output.txt open_test/open_38.output.txt
test39:
	./main < open_test/open_39.txt > output.txt
	diff output.txt open_test/open_39.output.txt
test40:
	./main < open_test/open_40.txt > output.txt
	diff output.txt open_test/open_40.output.txt
test41:
	./main < open_test/open_41.txt > output.txt
	diff output.txt open_test/open_41.output.txt
test42:
	./main < open_test/open_42.txt > output.txt
	diff output.txt open_test/open_42.output.txt
test43:
	./main < open_test/open_43.txt > output.txt
	diff output.txt open_test/open_43.output.txt
test44:
	./main < open_test/open_44.txt > output.txt
	diff output.txt open_test/open_44.output.txt
test45:
	./main < open_test/open_45.txt > output.txt
	diff output.txt open_test/open_45.output.txt
test46:
	./main < open_test/open_46.txt > output.txt
	diff output.txt open_test/open_46.output.txt
test47:
	./main < open_test/open_47.txt > output.txt
	diff output.txt open_test/open_47.output.txt
test48:
	./main < open_test/open_48.txt > output.txt
	diff output.txt open_test/open_48.output.txt
test49:
	./main < open_test/open_49.txt > output.txt
	diff output.txt open_test/open_49.output.txt
test50:
	./main < open_test/open_50.txt > output.txt
	diff output.txt open_test/open_50.output.txt
test51:
	./main < open_test/open_51.txt > output.txt
	diff output.txt open_test/open_51.output.txt
test52:
	./main < open_test/open_52.txt > output.txt
	diff output.txt open_test/open_52.output.txt
test53:
	./main < open_test/open_53.txt > output.txt
	diff output.txt open_test/open_53.output.txt
test54:
	./main < open_test/open_54.txt > output.txt
	diff output.txt open_test/open_54.output.txt
test55:
	./main < open_test/open_55.txt > output.txt
	diff output.txt open_test/open_55.output.txt
test56:
	./main < open_test/open_56.txt > output.txt
	diff output.txt open_test/open_56.output.txt
test57:
	./main < open_test/open_57.txt > output.txt
	diff output.txt open_test/open_57.output.txt
test58:
	./main < open_test/open_58.txt > output.txt
	diff output.txt open_test/open_58.output.txt
test59:
	./main < open_test/open_59.txt > output.txt
	diff output.txt open_test/open_59.output.txt
test60:
	./main < open_test/open_60.txt > output.txt
	diff output.txt open_test/open_60.output.txt
test61:
	./main < open_test/open_61.txt > output.txt
	diff output.txt open_test/open_61.output.txt
test62:
	./main < open_test/open_62.txt > output.txt
	diff output.txt open_test/open_62.output.txt
test63:
	./main < open_test/open_63.txt > output.txt
	diff output.txt open_test/open_63.output.txt
test64:
	./main < open_test/open_64.txt > output.txt
	diff output.txt open_test/open_64.output.txt
test65:
	./main < open_test/open_65.txt > output.txt
	diff output.txt open_test/open_65.output.txt
test66:
	./main < open_test/open_66.txt > output.txt
	diff output.txt open_test/open_66.output.txt
test67:
	./main < open_test/open_67.txt > output.txt
	diff output.txt open_test/open_67.output.txt
test68:
	./main < open_test/open_68.txt > output.txt
	diff output.txt open_test/open_68.output.txt
test69:
	./main < open_test/open_69.txt > output.txt
	diff output.txt open_test/open_69.output.txt
test70:
	./main < open_test/open_70.txt > output.txt
	diff output.txt open_test/open_70.output.txt
test71:
	./main < open_test/open_71.txt > output.txt
	diff output.txt open_test/open_71.output.txt
test72:
	./main < open_test/open_72.txt > output.txt
	diff output.txt open_test/open_72.output.txt
test73:
	./main < open_test/open_73.txt > output.txt
	diff output.txt open_test/open_73.output.txt
test74:
	./main < open_test/open_74.txt > output.txt
	diff output.txt open_test/open_74.output.txt
test75:
	./main < open_test/open_75.txt > output.txt
	diff output.txt open_test/open_75.output.txt
test76:
	./main < open_test/open_76.txt > output.txt
	diff output.txt open_test/open_76.output.txt
test77:
	./main < open_test/open_77.txt > output.txt
	diff output.txt open_test/open_77.output.txt
test78:
	./main < open_test/open_78.txt > output.txt
	diff output.txt open_test/open_78.output.txt
test79:
	./main < open_test/open_79.txt > output.txt
	diff output.txt open_test/open_79.output.txt
test80:
	./main < open_test/open_80.txt > output.txt
	diff output.txt open_test/open_80.output.txt
test81:
	./main < open_test/open_81.txt > output.txt
	diff output.txt open_test/open_81.output.txt
test82:
	./main < open_test/open_82.txt > output.txt
	diff output.txt open_test/open_82.output.txt
test83:
	./main < open_test/open_83.txt > output.txt
	diff output.txt open_test/open_83.output.txt
test84:
	./main < open_test/open_84.txt > output.txt
	diff output.txt open_test/open_84.output.txt
test85:
	./main < open_test/open_85.txt > output.txt
	diff output.txt open_test/open_85.output.txt
test86:
	./main < open_test/open_86.txt > output.txt
	diff output.txt open_test/open_86.output.txt
test87:
	./main < open_test/open_87.txt > output.txt
	diff output.txt open_test/open_87.output.txt
test88:
	./main < open_test/open_88.txt > output.txt
	diff output.txt open_test/open_88.output.txt
test89:
	./main < open_test/open_89.txt > output.txt
	diff output.txt open_test/open_89.output.txt
test90:
	./main < open_test/open_90.txt > output.txt
	diff output.txt open_test/open_90.output.txt
test91:
	./main < open_test/open_91.txt > output.txt
	diff output.txt open_test/open_91.output.txt
test92:
	./main < open_test/open_92.txt > output.txt
	diff output.txt open_test/open_92.output.txt
test93:
	./main < open_test/open_93.txt > output.txt
	diff output.txt open_test/open_93.output.txt
test94:
	./main < open_test/open_94.txt > output.txt
	diff output.txt open_test/open_94.output.txt
test95:
	./main < open_test/open_95.txt > output.txt
	diff output.txt open_test/open_95.output.txt
test96:
	./main < open_test/open_96.txt > output.txt
	diff output.txt open_test/open_96.output.txt
test97:
	./main < open_test/open_97.txt > output.txt
	diff output.txt open_test/open_97.output.txt
test98:
	./main < open_test/open_98.txt > output.txt
	diff output.txt open_test/open_98.output.txt
test99:
	./main < open_test/open_99.txt > output.txt
	diff output.txt open_test/open_99.output.txt
test100:
	./main < open_test/open_100.txt > output.txt
	diff output.txt open_test/open_100.output.txt
test101:
	./main < open_test/open_101.txt > output.txt
	diff output.txt open_test/open_101.output.txt
test102:
	./main < open_test/open_102.txt > output.txt
	diff output.txt open_test/open_102.output.txt
test103:
	./main < open_test/open_103.txt > output.txt
	diff output.txt open_test/open_103.output.txt
test104:
	./main < open_test/open_104.txt > output.txt
	diff output.txt open_test/open_104.output.txt
test105:
	./main < open_test/open_105.txt > output.txt
	diff output.txt open_test/open_105.output.txt
test106:
	./main < open_test/open_106.txt > output.txt
	diff output.txt open_test/open_106.output.txt
test107:
	./main < open_test/open_107.txt > output.txt
	diff output.txt open_test/open_107.output.txt
test108:
	./main < open_test/open_108.txt > output.txt
	diff output.txt open_test/open_108.output.txt
test109:
	./main < open_test/open_109.txt > output.txt
	diff output.txt open_test/open_109.output.txt
test110:
	./main < open_test/open_110.txt > output.txt
	diff output.txt open_test/open_110.output.txt
test111:
	./main < open_test/open_111.txt > output.txt
	diff output.txt open_test/open_111.output.txt

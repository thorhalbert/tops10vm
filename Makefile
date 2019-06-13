CFLAGS=-ggdb -Wno-long-long -pedantic -I./include

PSR =	psr_setup.o \
	psr_xbar.o \
	psr_engine.o \
	psr_pager.o \
	psr_manip36.o

OPS = 	opinit.o \
	op_ADDs.o \
	op_AOBs.o \
	op_BLT.o \
	op_EXCH.o \
	op_IDIVs.o \
	op_IMULs.o \
	op_JFCL.o \
	op_JRA.o \
	op_JRST.o \
	op_JSA.o \
	op_JSP.o \
	op_JSR.o \
	op_MOVEs.o \
	op_MOVMs.o \
	op_MOVNs.o \
	op_MOVSs.o \
	op_SUBs.o \
	op_XCT.o \
	op_bitops.o \
	op_bittests.o \
	op_byteops.o \
	op_halfwords.o \
	op_luuo.o \
	op_shifts.o \
	op_skipjumps.o \
	op_stack.o \
	op_tops10calls.o

KAS = 	ka_dev_apr.o \
	ka_dev_pi.o \
	ka_setup.o

T10 = 	t10_loader.o \
	t10_filemap.o \
	t10_io.o \
	t10_TTCALL.o \
	t10_ciCORE.o \
	t10_ciGETPPN.o \
	t10_ciGETTAB.o \
	t10_ciLIGHTS.o \
	t10_ciRESET.o \
	t10_ciTimes.o \
	t10_setup.o \
	t10_sfh.o 

ALLE = t10vm.o $(PSR) $(OPS) $(KAS) $(T10)

all: t10vm

build_xbar.o: opcodelist.h

t10vm: $(ALLE)
	gcc -o t10vm $(ALLE) -lpopt

opinit.o: opinit.c opinit.inc

opinit.inc: op_*.c
	grep -h ^INITBOP op_*.c >opinit.inc
	grep -h ^INITOP op_*.c >>opinit.inc

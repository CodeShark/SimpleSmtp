INCLUDE_PATH += -Isrc

include mk/os.mk mk/cxx_flags.mk mk/boost_suffix.mk

LIBS = \
    -lcurl

OBJS = \
    obj/smtp.o

all: lib test

lib: lib/libSimpleSmtp.a

lib/libSimpleSmtp.a: $(OBJS)
	$(ARCHIVER) rcs $@ $^

obj/smtp.o: src/smtp.cpp src/smtp.h
	$(CXX) $(CXX_FLAGS) $(INCLUDE_PATH) -c $< -o $@

test: test/smtptest$(EXE_EXT)

test/smtptest$(EXE_EXT): src/smtptest.cpp obj/smtp.o
	$(CXX) $(CXX_FLAGS) $(INCLUDE_PATH) $^ -o $@ $(LIBS)

install:
	-mkdir -p $(SYSROOT)/include/SimpleSmtp
	-cp src/smtp.h $(SYSROOT)/include/SimpleSmtp/
	-mkdir -p $(SYSROOT)/lib
	-cp lib/libSimpleSmtp.a $(SYSROOT)/lib/

remove:
	-rm -rf $(SYSROOT)/include/SimpleSmtp
	-rm $(SYSROOT)/lib/libSimpleSmtp.a

clean:
	-rm -f obj/*.o lib/*.a test/smtptest$(EXE_EXT)

LIBNAME := libtyra.a
LIBDIR := lib

TBINDIR := bin/test
TESTDIR := test
SRCDIR := src
INCDIR := inc
OBJDIR := .objs
DEPDIR := .deps

SRCS := $(notdir $(wildcard $(SRCDIR)/*.cpp))   # All the source files
OBJS := $(SRCS:%.cpp=$(OBJDIR)/%.o)             # All the object files
TSRCS := $(notdir $(wildcard $(TESTDIR)/test_*.cpp))
TBINS := $(TSRCS:%.cpp=$(TBINDIR)/%)

$(shell mkdir -p $(DEPDIR) >/dev/null)

CXX := g++

CXXFLAGS = -std=c++14 -I $(INCDIR) -I . -fdiagnostics-color=always 
CXXFLAGS += -Wall -Wextra -Wpedantic -Weffc++
CXXFLAGS += -Wfatal-errors -Wwrite-strings -Wno-parentheses -Warray-bounds -Wconversion -Wshadow
RELFLAGS := -O3
DBGFLAGS := -g
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

COMPILE = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(CXXFLAGS2) $(TARGET_ARCH)
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@

all: debug;

tests: $(TBINS)

test_%: $(TBINDIR)/%;

$(TBINDIR)/%: debug
$(TBINDIR)/%: CXXFLAGS+=$(DBGFLAGS)
$(TBINDIR)/%: $(OBJS) $(OBJDIR)/main.o $(OBJDIR)/%.o
	@mkdir -p $(@D)
	$(COMPILE) $(OUTPUT_OPTION) $^

$(OBJDIR)/%.o: CXXFLAGS+=$(DBGFLAGS)
$(OBJDIR)/%.o: $(TESTDIR)/%.cpp
	@mkdir -p $(@D)
	$(COMPILE) $(OUTPUT_OPTION) -c $<
	$(POSTCOMPILE)

debug: CXXFLAGS+=$(DBGFLAGS)
debug: $(LIBDIR)/$(LIBNAME)
release: CXXFLAGS+=$(RELFLAGS)
release: $(LIBDIR)/$(LIBNAME)

$(LIBDIR)/$(LIBNAME): $(OBJS)
	@mkdir -p $(@D)
	ar rsvc $(LIBDIR)/$(LIBNAME) $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPDIR)/%.d
	@mkdir -p $(@D)
	$(COMPILE) $(OUTPUT_OPTION) -c $<
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d
.PRECIOUS: $(OBJDIR)/%.o

include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS))))

.PHONY: clean
clean:
	@rm -rf $(TBINDIR)
	@rm -rf $(LIBDIR)
	@rm -rf $(OBJDIR)
	@rm -rf $(DEPDIR)

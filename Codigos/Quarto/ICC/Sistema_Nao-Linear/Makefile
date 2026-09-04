    CC     = gcc

    CFLAGS = -O0 
    LFLAGS = -lm -lmatheval

      PROG = resolucaoSNL

      OBJS = utils.o SistLinear.o EliminacaoGauss.o SistNaoLinear.o NewtonSNL.o

# Lista de arquivos para distribuição
DISTFILES = *.c *.h Makefile *.dat 
DISTDIR = ${USER}

.PHONY: clean purge all

%.o: %.c %.h utils.h
	$(CC) -c $(CFLAGS) $<

all: $(PROG)

$(PROG).o:  $(PROG).c utils.h SistNaoLinear.h NewtonSNL.h
	$(CC) -c $(CFLAGS) $<

$(PROG):  $(OBJS) $(PROG).o
	$(CC) -o $@ $^ $(LFLAGS)

clean:
	@rm -f *~ *.bak

purge:   clean
	@rm -rf bin obj *.layout *.depend
	@rm -f *.o core a.out
	@rm -f $(PROG)

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tgz) ..."
	@ln -s . $(DISTDIR)
	@tar -chzvf $(DISTDIR).tgz $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)

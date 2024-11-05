#
# Dissertacao mestrado Makefile
# Autor: Bruno Pereira dos Santos
#

TEX := pdflatex
BIB := bibtex

DIR_COMPILE_TRASH := build-trash

SRC := presentation
BIN := sockets.pdf

TOOL_READ_PDF := okular

all: presentation

presentation: $(SRC).tex
	$(TEX) $<
	$(BIB) $(SRC).aux
	$(TEX) $<
	$(TEX) $<
	@mv $(SRC).pdf $(BIN)
	@make clean
	@echo -e "\n# Type make read to read the output file $(BIN)"


latex: presentation read

read: $(BIN)
	@$(TOOL_READ_PDF) $^

teste:
	@echo "teste2"

dirtrahs:
	@mkdir -p $(DIR_COMPILE_TRASH)

clean:
	@rm -vf *.aux *.dvi *.log *.bbl *.blg *.bak *.out *.lot *.lof *.toc *.snm *.nav

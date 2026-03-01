CXX := g++
CXXFLAGS := -std=c++23 -Wall -Wextra
LDFLAGS := -lstdc++

SRCDIR := src
OBJDIR := obj

SRC := $(shell find $(SRCDIR) -name '*.cc')
OBJ := $(patsubst $(SRCDIR)/%.cc, $(OBJDIR)/%.o, $(SRC))

BIN := p3_HormigaEvolucionada

.PHONY: all clean run

all: $(BIN)

$(BIN): $(OBJ)
	@echo "Enlazando $^ --> $@"
	@$(CXX) $^ -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	@echo "Compilando $< --> $@"
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -I$(SRCDIR) -c $< -o $@

run: $(BIN)
	@echo "Configuraciones disponibles en data/:"; \
	ls -1 data/config*.txt 2>/dev/null || echo "No hay configuraciones disponibles."; \
	echo ""; \
	while true; do \
		read -p "Ingrese el número de configuración: " number; \
		input="data/config$${number}.txt"; \
		if [ -f "$$input" ]; then \
			break; \
		else \
			echo "Error: No existe el archivo $$input."; \
			echo ""; \
			echo "Configuraciones disponibles en data/:"; \
			ls -1 data/config*.txt 2>/dev/null || echo "No hay configuraciones disponibles."; \
			echo ""; \
		fi; \
	done; \
	./$(BIN) "$$input"; \
	echo ""; \

clean:
	@echo "Limpiando..."
	@rm -rf $(OBJDIR) $(BIN)

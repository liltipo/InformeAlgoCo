# Nombre del compilador
CXX = g++

# Opciones de compilación
CXXFLAGS = -std=c++11 -Wall -Wno-sign-compare

# Directorios
SRCDIR = codes
DATADIR = dataset
OUTDIR = output
OUTDIR_BOGO = output_bogo

# Archivos fuente y de salida
SOURCES = quickSort.cpp mergeSort.cpp stlSort.cpp bubbleSort.cpp bogoSort.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGETS = $(SOURCES:.cpp=)

# Archivos de entrada y salida
INPUT_FILES_COMMON = ordered.txt random.txt reversed.txt
INPUT_FILES_BOGO = orderedBogo.txt reversedBogo.txt randomBogo.txt
INPUT_PATHS_COMMON = $(addprefix $(DATADIR)/, $(INPUT_FILES_COMMON))
INPUT_PATHS_BOGO = $(addprefix $(DATADIR)/, $(INPUT_FILES_BOGO))
OUTPUT_FILES_COMMON = $(addprefix $(OUTDIR)/, $(INPUT_FILES_COMMON:.txt=_sorted.txt))
OUTPUT_FILES_BOGO = $(addprefix $(OUTDIR_BOGO)/, $(INPUT_FILES_BOGO:.txt=_sorted.txt))

# Reglas de compilación
all: $(TARGETS)

# Regla para generar el ejecutable
$(TARGETS): %: $(SRCDIR)/%.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla para compilar archivos fuente en objetos
$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para ejecutar los algoritmos comunes con los archivos de entrada comunes
run: $(TARGETS)
	@mkdir -p $(OUTDIR)
	@for target in $(filter-out bogoSort,$(TARGETS)); do \
		for i in $(INPUT_PATHS_COMMON); do \
			ofile=$(OUTDIR)/$$(basename $$i .txt)_$${target}.txt; \
			echo "Processing $$i with $$target -> $$ofile"; \
			./$$target $$i $$ofile; \
		done \
	done

# Regla para ejecutar BogoSort con los archivos de entrada específicos
runBogo: $(TARGETS)
	@mkdir -p $(OUTDIR_BOGO)
	@for target in $(filter bogoSort,$(TARGETS)); do \
		for i in $(INPUT_PATHS_BOGO); do \
			ofile=$(OUTDIR_BOGO)/$$(basename $$i .txt)_$${target}.txt; \
			echo "Processing $$i with $$target -> $$ofile"; \
			./$$target $$i $$ofile; \
		done \
	done

# Limpiar archivos generados
clean:
	rm -f $(SRCDIR)/*.o $(TARGETS)
	rm -rf $(OUTDIR) $(OUTDIR_BOGO)

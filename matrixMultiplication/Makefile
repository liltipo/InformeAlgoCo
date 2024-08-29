# Variables para los tamaños de las matrices
SIZE1 = 512
SIZE2 = 1024
SIZE3 = 2048

# Archivos fuente
SRCS = naiveMM.cpp cacheOptimizedMM.cpp strassenMM.cpp strassenMM2.cpp strassenMM3.cpp
# Archivos objeto
OBJS = $(SRCS:.cpp=.o)
# Ejecutables
EXES = cacheOptimized naive strassen strassen2 strassen3

# Compilador y opciones
CXX = g++
CXXFLAGS = -O2 -std=c++11

# Regla para compilar todos los archivos fuente
all: $(EXES)

# Regla para compilar cada ejecutable
cacheOptimized: cacheOptimizedMM.o
	$(CXX) $(CXXFLAGS) -o $@ $<

naive: naiveMM.o
	$(CXX) $(CXXFLAGS) -o $@ $<

strassen: strassenMM.o
	$(CXX) $(CXXFLAGS) -o $@ $<

strassen2: strassenMM2.o
	$(CXX) $(CXXFLAGS) -o $@ $<

strassen3: strassenMM3.o
	$(CXX) $(CXXFLAGS) -o $@ $<

# Regla para compilar los archivos .cpp en archivos .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para ejecutar todos los ejecutables con sus respectivos tamaños
run: all
	./cacheOptimized $(SIZE3)
	./cacheOptimized $(SIZE2)
	./cacheOptimized $(SIZE1)
	./naive $(SIZE3)
	./naive $(SIZE2)
	./naive $(SIZE1)
	./strassen $(SIZE3)
	./strassen $(SIZE2)
	./strassen $(SIZE1)
	./strassen2 $(SIZE1)
	./strassen3 $(SIZE1)

# Regla para limpiar los archivos generados
clean:
	rm -f $(OBJS) $(EXES)

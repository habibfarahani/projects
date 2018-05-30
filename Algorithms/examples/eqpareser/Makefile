INCLUDES := -I/. \
			-I./components	\
			-I./components/Parameters	\
			-I./components/Operators	\
			-I./evaluator \
			-I./parser

CPP_FLAGS := -std=c++11



SOURCES	:=  main.cpp \
			./components/Equation.cpp \
			./components/Parameters/Params.cpp \
			./components/Operators/Add.cpp \
			./components/Operators/Subtract.cpp \
			./evaluator/EquationEvaluator.cpp \
			./parser/EquationParser.cpp


TARGET :=  eval


all:
	g++ $(CPP_FLAGS) $(INCLUDES) $(SOURCES) -o $(TARGET)
